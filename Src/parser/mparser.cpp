/******************************************************************************
FileName: 		mparser.cpp
Description:   	Implimentation of parser
Author:   		Round Bridge
Date: 			2020.10.31
Modification History:
                    2020.10.31 create file
Version: 		0.0.1
******************************************************************************/

#include <iostream>
#include "mparser.h"
#include "string.h"
#include <cstdio>

using std::cout;
using std::endl;

namespace mparser
{
    uint64 _Parser::get_file_length(const char* file)
    {
        uint64 len = 0;
        if (file == NULL) {
            return len;
        }
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, file, "rb");
        if (0 != err || fp == NULL) {
            cout << "[_PARSER] get_file_length: Open file " << file << " failed!" << endl;
            return len;
        }
        fseek(fp, 0, SEEK_END);
        len = ftell(fp);
        fclose(fp);
        
        return len;
    }

    uint64 _Parser::read_file(const char* file, puint8 buf, uint64 len)
    {
        uint64 l = 0;
        if (file == NULL || buf == NULL || len == 0) {
            return l;
        }
        FILE* fp;
        errno_t err;
        err = fopen_s(&fp, file, "rb");
        if (0 != err || fp == NULL) {
            cout << "[_PARSER] read_file: Open file " << file << " failed!" << endl;
            return l;
        }

        l = fread(buf, 1, len, fp);
        if (l != len) {
            cout << "[_PARSER] read_file: read " << l << " byte, but the length of file " << file << " is " << len << endl << endl;
        }
        fclose(fp);
        return l;
    }

    /*----------------------------------------- ������H264��������� -----------------------------------------*/
    /*
        ��data��(������len)��������Ҫ��flag�����ݵ�λ�ü����ȣ�λ����out���أ�������outLen���أ���������״̬��
    */
    state_code H264Parser::get_data(const puint8 data, uint64 len, ppuint8 out, puint64 outLen, uint32 flag) {
        const puint8 dataIdx = data;
        uint64 pos1 = 0, pos2 = 0, skip = 0;

        if (out == NULL || data == NULL || outLen == NULL) {
            return NULL_PTR;
        }
        if (len == 0) {
            return PARAM_ERR;
        }
        if (0x01000000 == flag || 0x010000 == flag) {    // ��ʾ��data��ʼ�����ȡ������ʼ����0x01000000����0x010000��һ��NALU��Ԫ����
            if (0x01000000 == flag) {
                skip = 4;
            }
            else {
                skip = 3;
            }
            if (OK == find_start_code(dataIdx, len, flag, &pos1)) {
                if (OK == find_start_code(dataIdx + pos1 + skip, len - pos1 - skip, flag, &pos2)) {  // �ҵ�������ʼ�룬��������ʼ��֮����������һ������
                    *out = dataIdx + pos1;
                    *outLen = pos2 - pos1;
                    return OK;
                }
                else {  // ֻ�ҵ�һ����ʼ�룬��ܿ��ܴӸ���ʼ��ֱ�����������ǲ�������
                    *out = dataIdx + pos1;
                    *outLen = len - pos1;
                    return DATA_NOTENOUGH;
                }
            }
            else {
                return FAILED;
            }
        }
        return PARAM_ERR;
    }

    state_code H264Parser::parse_nalu_type(uint8 naluHeader, H264ParseOut* parseOut) {
        enH264SliceType enType;

        enType = (enH264SliceType)(naluHeader & 0x1F);

        if (parseOut == NULL) {
            return NULL_PTR;
        }

        if (enH264SliceType::SLICE_SLICE == enType
            || enH264SliceType::SLICE_DPA == enType
            || enH264SliceType::SLICE_DPB == enType
            || enH264SliceType::SLICE_DPC == enType) {
            parseOut->nbP++;
        }
        else if (enH264SliceType::SLICE_IDR == enType) {
            parseOut->nbIdr++;
        }
        else if (enH264SliceType::SLICE_SPS == enType) {
            parseOut->nbSps++;
        }
        else if (enH264SliceType::SLICE_PPS == enType) {
            parseOut->nbPps++;
        }
        else if (enH264SliceType::SLICE_SEI == enType) {
            parseOut->nbSei++;
        }
        else if (enH264SliceType::SLICE_DEM == enType) {
            parseOut->nbDem++;
        }
        else {
            parseOut->nbUnknownNalu++;
        }
        parseOut->nbTotalNalu++;

        return OK;
    }

    state_code H264Parser::parse(const puint8 data, uint64 len, pvoid out, uint32 outLen, uint32 flag) {
        uint64 skip = 0, l = len;
        uint64 getLen = 0;
        puint8 pos = data;
        puint8 dataIdx = data;
        state_code ret = FAILED;
        H264ParseOut* pOut = (H264ParseOut*)out;

        if (pOut == NULL || data == NULL) {
            return NULL_PTR;
        }
        if (outLen < sizeof(H264ParseOut) || len == 0 || (0x01000000 != flag && 0x010000 != flag)) {
            return PARAM_ERR;
        }
        
        memset((void*)pOut, 0, sizeof(H264ParseOut));

        if (0x01000000 == flag) {
            skip = 4;
        }
        else {
            skip = 3;
        }
        do {
            ret = get_data(dataIdx, l, &pos, &getLen, flag);
            if (ret == OK || ret == DATA_NOTENOUGH) {
                parse_nalu_type(*(pos + skip), pOut);
                l = l - ((uint32)(pos - dataIdx) + getLen);
                dataIdx = pos + getLen;
            }
        } while (l > 0);
        return OK;
    }

    void H264Parser::print_parse_result(pvoid out)
    {
        H264ParseOut* pOut = (H264ParseOut*)out;

        if (pOut == NULL) {
            
        }
        else {
            cout << "------------------------------------------------------------ NOTICE ------------------------------------------------------------" << endl;
            cout << "!!!!!!Ŀǰ��ʱ���ֲ���P֡��B֡�Լ���IDR���͵�I֡����Щ���͵�֡ͳһ�鵽P(B)slice��!!!!!!" << endl;
            cout << "!!֧����ʼ����000001��00000001���������͵�H264�ļ�������֧��ͬʱ����������ʼ����ļ�!!!" << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Type: IDR\tP(B)slice\tSPSslice\tPPSslice\tSEIslice\tDEMslice\tUNKNOWNslice\tTOTALslice" << endl;
            cout << "num : " <<pOut->nbIdr << "\t" << pOut->nbP << "\t\t" << pOut->nbSps << "\t\t" << pOut->nbPps << "\t\t" << pOut->nbSei << "\t\t" << pOut->nbDem << "\t\t" << pOut->nbUnknownNalu << "\t\t" << pOut->nbTotalNalu << endl;
        }
        return;
    }

    state_code H264Parser::find_start_code(const puint8 data, uint64 len, uint32 startCode, puint64 pos)
    {
        if (data == NULL || pos == NULL) {
            return NULL_PTR;
        }
        if (len == 0) {
            return PARAM_ERR;
        }
        puint8 dataIdx = data;
        puint8 dataEnd = data + len;
        puint32 pNaluToken = NULL;
        uint32 startCodeLen = 4;
        uint32 startCodeMask = 0xFFFFFFFF;

        if (startCode == 0x01000000) {
            startCodeLen = 4;
            startCodeMask = 0xFFFFFFFF;
        }
        else if (startCode == 0x010000) {
            startCodeLen = 3;
            startCodeMask = 0xFFFFFF;  // ���������00 00 01 67������Ҫͨ������ȥ��67��Ӱ�죬�����Ҳ������ֽڵ���ʼ��
        }
        else {
            return PARAM_ERR;
        }
        for (; dataIdx <= dataEnd - startCodeLen; dataIdx++)
        {
            pNaluToken = (puint32)dataIdx;
            //��Ѱnalu��ʼ��־0x01000000���ҵ�nalu��ʼλ��
            if (startCode == (*pNaluToken & startCodeMask))
            {
                *pos = (uint64)(dataIdx - data);
                return OK;
            }
        }
        return FAILED;
    }

    _Parser* H264ParserFactory::CreateParser() {
        return new H264Parser();
    }


    /*----------------------------------------- ͨ�ý�������� -----------------------------------------*/
    state_code Parser::start_parse(const char* file, pvoid out, uint32 outLen, uint32 flag) {
        state_code ret;

        if (NULL == file || NULL == parser) {
            cout << "[PARSER] NULL PTR!" << endl;
            return NULL_PTR;
        }        
        uint64 fileLen = parser->get_file_length(file);
        uint8* buf = new uint8[fileLen];

        parser->read_file(file, buf, fileLen);
        ret = parser->parse(buf, fileLen, out, outLen, flag);
        delete[] buf;

        return ret;
    }

    void Parser::print(pvoid out)
    {
        if (NULL == out || NULL == parser) {
            cout << "[PARSER] NULL PTR!" << endl;
            return;
        }
        parser->print_parse_result(out);
        return;
    }

}