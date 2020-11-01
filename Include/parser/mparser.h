/******************************************************************************
FileName: 		mparser.h
Description:   	header file
Author:   		Round Bridge
Date: 			2020.10.31
Modification History:
                    2020.10.31 create file
Version: 		0.0.1
******************************************************************************/
#pragma once

#ifndef _MPARSER_H_
#define _MPARSER_H_

#include "types.h"
#include "av_common.h"

using std::cout;
using std::endl;

namespace mparser
{
    /*
        �ڲ��������ӿ���
    */
    class _Parser {
    public:
        /*
            ��data��(������len)��������Ҫ��flag�����ݵ�λ�ü����ȣ�λ����out���أ�������outLen���أ���������״̬��
        */
        virtual state_code get_data(const puint8 data, uint64 len, ppuint8 out, puint64 outLen, uint32 flag) = 0;
        /*
            ��data�е����ݽ��н��������ݳ�����len�����������out���أ��������������outLen���أ�flag��ʾ������ʽ����������״̬��
        */
        virtual state_code parse(const puint8 data, uint64 len, pvoid out, uint32 outLen, uint32 flag) = 0;
        /*
            ��ӡ�������out�е���Ϣ
        */
        virtual void print_parse_result(pvoid out) = 0;
        /*
            �����ļ�file�ĳ��ȣ���λ�ǣ�byte
        */
        virtual uint64 get_file_length(const char* file);
        /*
            ��ȡָ������len���ļ����ݵ�buf��
        */
        virtual uint64 read_file(const char* file, puint8 buf, uint64 len);
        virtual ~_Parser() {}
    };

    /*
        �����������ӿ���
    */
    class ParserFactory {
    public:
        virtual _Parser* CreateParser() = 0;
        virtual ~ParserFactory() {}
    };

    /*
        H264������������
    */
    class H264ParseOut {
    public:
        uint32 isH264;  // �ǲ���h264����
        uint32 nbTotalNalu; // �ܵ�NALU��Ԫ��
        uint32 w, h;    // ���
        // �����Ǹ���NALU�ĸ���
        uint32 nbIdr;
        uint32 nbP;
        uint32 nbSps;
        uint32 nbPps;
        uint32 nbSei;
        uint32 nbDem;
        uint32 nbUnknownNalu;
    };

    /*
        H264��������
        ��ʱֻ֧��AnnexB��ʽ����ʼǰ׺��00000001��000001) + NALU����
    */
    class H264Parser : public _Parser {
    public:
        virtual state_code get_data(const puint8 data, uint64 len, ppuint8 out, puint64 outLen, uint32 flag);
        virtual state_code parse(const puint8 data, uint64 len, pvoid out, uint32 outLen, uint32 flag);
        virtual void print_parse_result(pvoid out);
    private:
        /*
            ��data��ʼ������ʼ�룬λ����pos(�����data��ƫ����)���أ���������״̬��
        */
        state_code find_start_code(const puint8 data, uint64 len, uint32 startCode, puint64 pos);
        state_code parse_nalu_type(uint8 naluHeader, H264ParseOut* parseOut);
    };

    /*
        ����H264�������Ĺ�����
    */
    class H264ParserFactory : public ParserFactory {
    public:
        virtual _Parser* CreateParser();
    };


    /*
        �ⲿͨ�ý�������
    */
    class Parser {
    public:
        virtual ~Parser() {
            delete parser;
            parser = NULL;
            cout << "[PARSER] Deconstructed!" << endl;
        }
        Parser(ParserFactory* factory) {
            this->factory = factory;
            parser = factory->CreateParser();
        }
        /*
            ��file���н��������������out���أ��ռ��ⲿ���룬�ⲿ�ͷţ���outLen��ʾout�Ŀռ��С��flag��ʾ������ʽ����������״̬��
        */
        state_code start_parse(const char* file, pvoid out, uint32 outLen, uint32 flag);
        void print(pvoid out);

    private:
        ParserFactory* factory;
        _Parser* parser;
    };
}
#endif
