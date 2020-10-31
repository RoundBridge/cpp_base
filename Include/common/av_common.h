#pragma once
/******************************************************************************
FileName: 		av_common.h
Description:   	something about audio, video, picture
Author:   		Round Bridge
Date: 			2020.10.31
Modification History:
                    2020.10.31 create file
Version: 		0.0.1
******************************************************************************/
#ifndef _AV_COMMON_H_
#define _AV_COMMON_H_

enum class enEncodeMode { 
    MODE_INVALID = 0, 
    MODE_H264, 
    MODE_H265,
    MODE_JPEG,
    MODE_AAC,
    MODE_G711A,
    MODE_G711U,
    MODE_G726,
    MODE_ADPCM,
    MODE_PCM,
    MODE_MP3 = 10,
    MODE_BUTT
};

enum class enH264SliceType {
    SLICE_UNDEF = 0,
    // VCL UNIT��ͼ�����㵥Ԫ��
    SLICE_SLICE,
    SLICE_DPA,
    SLICE_DPB,
    SLICE_DPC,
    SLICE_IDR,
    // NON VCL UNIT����ͼ�����㵥Ԫ��
    SLICE_SEI,
    SLICE_SPS,
    SLICE_PPS,
    SLICE_DEM,  // ���ʵ�Ԫ�ָ���
    SLICE_SEQEND = 10, // ���н�β
    SLICE_STMEND, // ����β
    SLICE_PAD,  // �������
    SLICE_SPS_EX,   // ���в�������չ
    SLICE_RESERVED = 14,
    SLICE_BUTT = 32
};
#endif
