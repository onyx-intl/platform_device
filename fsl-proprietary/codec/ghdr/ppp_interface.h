/*
 ***************************************************************************
 * Copyright 2007-2010 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***************************************************************************
 ****************************************************************************
 * ANSI C source code
 *
 * Project Name : fsl_mad_multimedia PPP
 * File Name    : ppp_interface.h
 *
 ***************************************************************************/
 /***************************************************************************
 *
 *
 *   CHANGE HISTORY
 *    dd/mm/yy        Code Ver      CR          Author     Description
 *    --------        -------      -------      ------     -----------
 *   06/11/2007       0.1         engr55894     Tao Jun    1.add a new line at the
 *                                                         end of the file;
 *                                                         2.add file header
 *
 **************************************************************************/
#ifndef __PPP_INTERFACE_H__
#define __PPP_INTERFACE_H__

#ifdef _WIN32
typedef __int64 PPP_I64;
#else
typedef long long PPP_I64;
#endif
typedef unsigned char  PPP_U8;
typedef char           PPP_I8;
typedef unsigned short PPP_U16;
typedef short          PPP_I16;
typedef unsigned int   PPP_U32;
typedef int            PPP_I32;
typedef PPP_U32        PPP_BOOL;
typedef void           PPP_VOID;

#define SPEAKER_FRONT_LEFT             PPP_SPEAKER_FRONT_LEFT
#define SPEAKER_FRONT_RIGHT            PPP_SPEAKER_FRONT_RIGHT
#define SPEAKER_FRONT_CENTER           PPP_SPEAKER_FRONT_CENTER
#define SPEAKER_LOW_FREQUENCY          PPP_SPEAKER_LOW_FREQUENCY
#define SPEAKER_BACK_LEFT              PPP_SPEAKER_BACK_LEFT
#define SPEAKER_BACK_RIGHT             PPP_SPEAKER_BACK_RIGHT
#define SPEAKER_FRONT_LEFT_OF_CENTER   PPP_SPEAKER_FRONT_LEFT_OF_CENTER
#define SPEAKER_FRONT_RIGHT_OF_CENTER  PPP_SPEAKER_FRONT_RIGHT_OF_CENTER
#define SPEAKER_BACK_CENTER            PPP_SPEAKER_BACK_CENTER
#define SPEAKER_SIDE_LEFT              PPP_SPEAKER_SIDE_LEFT
#define SPEAKER_SIDE_RIGHT             PPP_SPEAKER_SIDE_RIGHT
#define SPEAKER_TOP_CENTER             PPP_SPEAKER_TOP_CENTER
#define SPEAKER_TOP_FRONT_LEFT         PPP_SPEAKER_TOP_FRONT_LEFT
#define SPEAKER_TOP_FRONT_CENTER       PPP_SPEAKER_TOP_FRONT_CENTER
#define SPEAKER_TOP_FRONT_RIGHT        PPP_SPEAKER_TOP_FRONT_RIGHT
#define SPEAKER_TOP_BACK_LEFT          PPP_SPEAKER_TOP_BACK_LEFT
#define SPEAKER_TOP_BACK_CENTER        PPP_SPEAKER_TOP_BACK_CENTER
#define SPEAKER_TOP_BACK_RIGHT         PPP_SPEAKER_TOP_BACK_RIGHT

#define CHANNUM_MAX 8

/*Speaker Positions for ChannelMask*/
#define PPP_SPEAKER_FRONT_LEFT              0x1
#define PPP_SPEAKER_FRONT_RIGHT             0x2
#define PPP_SPEAKER_FRONT_CENTER            0x4
#define PPP_SPEAKER_LOW_FREQUENCY           0x8
#define PPP_SPEAKER_BACK_LEFT               0x10
#define PPP_SPEAKER_BACK_RIGHT              0x20
#define PPP_SPEAKER_FRONT_LEFT_OF_CENTER    0x40
#define PPP_SPEAKER_FRONT_RIGHT_OF_CENTER   0x80
#define PPP_SPEAKER_BACK_CENTER             0x100
#define PPP_SPEAKER_SIDE_LEFT               0x200
#define PPP_SPEAKER_SIDE_RIGHT              0x400
#define PPP_SPEAKER_TOP_CENTER              0x800
#define PPP_SPEAKER_TOP_FRONT_LEFT          0x1000
#define PPP_SPEAKER_TOP_FRONT_CENTER        0x2000
#define PPP_SPEAKER_TOP_FRONT_RIGHT         0x4000
#define PPP_SPEAKER_TOP_BACK_LEFT           0x8000
#define PPP_SPEAKER_TOP_BACK_CENTER         0x10000
#define PPP_SPEAKER_TOP_BACK_RIGHT          0x20000

typedef enum{
  DecoderTypeAuto = 0,
  DecoderTypeNoise,
  DecoderTypePCM,
  DecoderTypeAC3,
  DecoderTypeDTS,
  DecoderTypeMP3,
  DecoderTypeMLP,
  DecoderTypeLPCM,
  DecoderTypeAAC,
  DecoderTypeTrueHD,
  DecoderTypeEAC3,
  DecoderTypeWMA,
  DecoderTypeDTSHD,
  DecoderTypeMAuto,
  DecoderTypeMPCM,
  DecoderTypeUnused = 0x100
} DEC_TYPE_PPP;

typedef enum{
  PPP_INTERLEAVE = 0,
  PPP_BLOCK
} MODE_TYPE_PPP;

typedef struct{
 /* common input data*/
 void *iptr;
 void *optr;
 int inputsamples; /*samples per channel*/
 int outputsamples;
 int bitwidth;
 MODE_TYPE_PPP blockmode;
 DEC_TYPE_PPP decodertype;
 int channelmask;
 int samplerate;
 int VOR[CHANNUM_MAX];/*in 0.1 db*/
 int pppcontrolsize;
}PPP_INPUTPARA;


typedef struct{
 int channelmask;
 int samplerate;
 int outputsamples; /*samples per channel*/
 int VOR[CHANNUM_MAX];/*in 0.1 db*/
 DEC_TYPE_PPP decodertype;
 int pppinfosize;
}PPP_INFO;

#endif
