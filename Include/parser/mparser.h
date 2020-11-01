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
        内部解析器接口类
    */
    class _Parser {
    public:
        /*
            从data中(长度是len)查找满足要求flag的数据的位置及长度，位置用out返回，长度用outLen返回，函数返回状态码
        */
        virtual state_code get_data(const puint8 data, uint64 len, ppuint8 out, puint64 outLen, uint32 flag) = 0;
        /*
            对data中的数据进行解析，数据长度是len，解析结果用out返回，解析结果长度用outLen返回，flag表示解析方式，函数返回状态码
        */
        virtual state_code parse(const puint8 data, uint64 len, pvoid out, uint32 outLen, uint32 flag) = 0;
        /*
            打印解析结果out中的信息
        */
        virtual void print_parse_result(pvoid out) = 0;
        /*
            返回文件file的长度，单位是：byte
        */
        virtual uint64 get_file_length(const char* file);
        /*
            读取指定长度len的文件数据到buf中
        */
        virtual uint64 read_file(const char* file, puint8 buf, uint64 len);
        virtual ~_Parser() {}
    };

    /*
        解析器工厂接口类
    */
    class ParserFactory {
    public:
        virtual _Parser* CreateParser() = 0;
        virtual ~ParserFactory() {}
    };

    /*
        H264解析结果输出类
    */
    class H264ParseOut {
    public:
        uint32 isH264;  // 是不是h264码流
        uint32 nbTotalNalu; // 总的NALU单元数
        uint32 w, h;    // 宽高
        // 以下是各种NALU的个数
        uint32 nbIdr;
        uint32 nbP;
        uint32 nbSps;
        uint32 nbPps;
        uint32 nbSei;
        uint32 nbDem;
        uint32 nbUnknownNalu;
    };

    /*
        H264解析器类
        暂时只支持AnnexB格式：开始前缀（00000001或000001) + NALU数据
    */
    class H264Parser : public _Parser {
    public:
        virtual state_code get_data(const puint8 data, uint64 len, ppuint8 out, puint64 outLen, uint32 flag);
        virtual state_code parse(const puint8 data, uint64 len, pvoid out, uint32 outLen, uint32 flag);
        virtual void print_parse_result(pvoid out);
    private:
        /*
            从data开始查找起始码，位置用pos(相对于data的偏移量)返回，函数返回状态码
        */
        state_code find_start_code(const puint8 data, uint64 len, uint32 startCode, puint64 pos);
        state_code parse_nalu_type(uint8 naluHeader, H264ParseOut* parseOut);
    };

    /*
        生产H264解析器的工厂类
    */
    class H264ParserFactory : public ParserFactory {
    public:
        virtual _Parser* CreateParser();
    };


    /*
        外部通用解析器类
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
            对file进行解析，解析结果用out返回（空间外部申请，外部释放），outLen表示out的空间大小，flag表示解析方式，函数返回状态码
        */
        state_code start_parse(const char* file, pvoid out, uint32 outLen, uint32 flag);
        void print(pvoid out);

    private:
        ParserFactory* factory;
        _Parser* parser;
    };
}
#endif
