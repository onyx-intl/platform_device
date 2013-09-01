/*
 ***************************************************************************
 * Copyright 2007-2010 by Freescale Semiconductor, Inc.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***************************************************************************
 ****************************************************************************
 * ANSI C source code
 *
 * Project Name : Parametric EQ PPP
 * File Name    : peq_ppp_interface.h
 *
 ***************************************************************************/
 /***************************************************************************
 *   CHANGE HISTORY
 *    dd/mm/yy        Code Ver      CR          Author     Description
 *    --------        -------      -------      ------     -----------
 *   17/09/2007       0.1     	  engr49841     Tao Jun    Created file
 *   09/11/2007       0.2         engr55894     Tao Jun    Add _TCHAR definition
 *   14/11/2007       0.3         engr56706     Tao Jun    Add attenuation definition
 *   19/12/2007       0.4         engr59199     Tao Jun    Change PCMBLKSZ to 256
 *   04/01/2008       0.5         engr61453     Tao Jun    Delete redundant definition
 *   20/05/2008       0.6         engr76819     Tao Jun    Added version API
 *   12/12/2008       0.7         engr102467    Tao Jun    Added zero phase API
 *
 **************************************************************************/
#ifndef __PEQ_PPP_INTERFACE_H
#define __PEQ_PPP_INTERFACE_H

#include "ppp_interface.h"

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

#define PEQ_FAST_MEMORY                 1
#define PEQ_SLOW_MEMORY                 2
#define PEQ_MAX_NUM_MEM_REQS            1       /* presently we need seperate chunk of memory for scratch_lf */
#define LONG_BOUNDARY                   4
#define NPCMCHANS                       8       /*total channels*/
#define BANDSINGRP			10
/*#define PEQ_INPUT_BUFFER_SIZE           (PCMBUFSZ*NPCMCHANS)*/
#define PEQ_TRUE			1
#define PEQ_FALSE			0
#define PEQ_MAX_SAMPLES                 1024

/* Data type */
#ifdef _WIN32
typedef __int64 PEQ_I64;
#else
typedef long long PEQ_I64;
#endif
typedef unsigned char PEQ_U8;
typedef char PEQ_I8;
typedef unsigned short PEQ_U16;
typedef short PEQ_I16;
typedef unsigned int PEQ_U32;
typedef int PEQ_I32;
typedef PEQ_U32 PEQ_BOOL;
typedef void PEQ_VOID;
#define PEQ_FILE FILE
#ifdef __WINCE
#define  PEQ_TCHAR _TCHAR
#endif
/* Define NULL pointer value*/
#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((PEQ_VOID *)0)
#endif
#endif
#define	PEQ_NULL NULL

/**** PEQ structure declarations ****/
typedef struct {
	PEQ_I32 Fc;
	PEQ_I32 Gain;
	PEQ_I32 Q_value;
	PEQ_I32 FilterType;
						/*****
						FilterType = 0 : peak filter
						FilterType = 1 : low shelving filter
						FilterType = 2 : Hi- shelving filter
						FilterType = 3 : lowpass crossover filter
						FilterType = 4 : Hignpass crossover filter
						******/
	} FILTER_PARA;

typedef struct {
	/* PPP common data */
	PPP_INPUTPARA ppp_inputpara;
	/* PEQ private data */
	PEQ_I32 channelnumber;			/* total channel number */
	PEQ_I32 peqenablemask;			/* channel mask */
	PEQ_I32 chennelfilterselect;		/* channel filter Selection */
	PEQ_I32 premode;			/* predetermined mode bit */
	PEQ_I32 calbandsperfrm;			/* calculate bands number per frame */
	PEQ_I32 bandspergroup[BANDSINGRP];	/* every group¡¯s bands number,default value is 4*/
        FILTER_PARA group_band[NPCMCHANS][BANDSINGRP];
						/* group m band n input parameters*/
	PEQ_I32 attenuation;			/* attenuation factor in dB*/
        PEQ_BOOL zerophaseflag;                  /* zero phase flag */
        } PEQ_PL;

typedef struct{
	PPP_INFO ppp_info;
	PEQ_I32 volumeregi[NPCMCHANS];		/* volume output register*/
	PEQ_I32 chennelfilterselect;		/* channel filter Selection*/
	PEQ_I32 bandspergroup[BANDSINGRP];	/* every group¡¯s bands number,default value is 4*/
        FILTER_PARA group_band[NPCMCHANS][BANDSINGRP];
						/* group m band n input parameters*/
	PEQ_I32 attenuation;			/* attenuation factor in dB*/
	} PEQ_INFO;

/* Error types */
typedef enum {
        PEQ_OK = 0,                             /* Success,no error */
        PEQ_END_OF_STREAM,                      /* end of bit stream */
        PEQ_ERROR_INIT = 51,                    /* initialization error */
        PEQ_ERROR_INVALID_PARAM = 52            /* invalid Parameters to decode frame */
        /*any other errors need to add*/
        } PEQ_RET_TYPE;

typedef enum{
        PEQ_STATIC_MEM,                         /* 0 for static memory */
        PEQ_SCRATCH_MEM                         /* 1 for scratch memory */
        } PEQ_MEM_DESC;

/*chunk¡¯s memory configuration parameters*/
typedef struct {
        PEQ_I32 peq_size;                       /* Size in bytes */
        PEQ_I32 peq_type;                       /* Memory type Fast or Slow */
        PEQ_MEM_DESC peq_mem_desc;              /* to indicate if it is scratch memory */
        PEQ_I32 peq_priority;                   /* In case of fast memory, specify the priority */
        void *app_base_ptr;                     /* Pointer to the base memory , which will be allocated and
                                                filled by the  application */
        } PEQ_Mem_Alloc_Info_Sub;

/*Memory information structure array*/
typedef struct {
        PEQ_I32 peq_num_reqs;
        PEQ_Mem_Alloc_Info_Sub mem_info_sub [PEQ_MAX_NUM_MEM_REQS];
        } PEQ_Mem_Alloc_Info;

/* PPP parameter  structure */
struct PEQ_Dec_Config;
typedef struct PEQ_Dec_Config{
        PEQ_Mem_Alloc_Info peq_mem_info;
        void *peq_decode_info_struct_ptr;	/*point to Global_struct*/
        int WM;
        } PEQ_PPP_Config;


EXTERN PEQ_RET_TYPE peq_query_ppp_mem(PEQ_PPP_Config *dec_config);
EXTERN PEQ_RET_TYPE peq_ppp_init(PEQ_PPP_Config *dec_config);
EXTERN PEQ_RET_TYPE peq_ppp_frame(PEQ_PPP_Config *dec_config,PEQ_PL *peq_list_ptr,PEQ_INFO *peq_info_ptr);
EXTERN const char *PEQPPPVersionInfo();
#endif
