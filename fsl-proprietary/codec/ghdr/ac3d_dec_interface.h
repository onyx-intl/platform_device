/*
 ***************************************************************************
 *  Copyright (c) 2007-2012, Freescale Semiconductor Inc.,
 *  All Rights Reserved.
 * All modifications are confidential and proprietary information
 * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
 ***************************************************************************

****************************************************************************
* ANSI C source code
*
* Project Name : ac-3 Decoder
*
* FREESCALE CONFIDENTIAL PROPRIETARY
***************************************************************************/
/***************************************************************************
 *
 *   (C) 2007 FREESCALE SEMICONDUCTOR.
 *
 *   CHANGE HISTORY
 *    dd/mm/yy        Code Ver     Description         CR            Author
 *    --------        -------      -----------        ----           ------
 *   07/08/2007       0.1 	   created file                    Baofeng Tian
 *   11/22/2007       01.03.00     transfer debug function         Wang Shengjiu
 *                                 from pointer to decoder
 *   11/29/2007       01.04.00     add version info                Wang Shengjiu
 *   12/11/2007       02.01.00     add extern "c"                  Wang Shengjiu
 *
 **************************************************************************/

#if !defined(AC3D_DEC_INTERFACE_H)
#define AC3D_DEC_INTERFACE_H


#define         KCAPABLE                1			/* Enables karaoke capable code */
#define         MAXDBGFILE	64				/* Max # of debug files in table	*/


typedef unsigned char     AC3D_UINT8;
typedef char              AC3D_INT8;
typedef unsigned short    AC3D_UINT16;
typedef short             AC3D_INT16;
typedef unsigned int      AC3D_UINT32;
typedef int               AC3D_INT32;


/* uniform Error types both for decoder and interface */
typedef enum
{
        /* Sucess */
        AC3D_OK = 0,			   /* no error 	*/
        AC3D_ERR_WARNING,                  /* warning error type */
        /* fatal error, cause decoder stop decode */
        AC3D_ERR_SYNC,	                   /* invalid sync word */
        AC3D_ERR_SAMPRATE,                 /* invalid sample rate */
        AC3D_ERR_DATARATE,                 /* invalid data rate */
        AC3D_ERR_REV,                      /* invalid bitstream revision */
        /* waning error */
        AC3D_ERR_BLK,                      /* block size error */
        AC3D_ERR_RPT,	                   /* user block repeat request */
        AC3D_ERR_MUTE,	                   /* user mute request */
        AC3D_ERR_CHANS,                    /* too many channels in data stream */
        AC3D_ERR_MISC,	                   /* miscellaneous data error */
        AC3D_ERR_FATAL,                    /* fatal error boundary, below all fatal error */
        AC3D_ERR_PARAMETERS,               /* input parameters invalid */
        AC3D_ERR_PHSCORTI,                 /* PHSCOR table index out of range */
        AC3D_ERR_BND,                      /* expand_delta: delta bit alloc past end of array */
        AC3D_ERR_XDALL,                    /* xdall subroutine fatal error */
	/* Warning : End of bitstream */
        AC3D_END_OF_STREAM,                 /* end of bit stream */
	AC3D_ERR_INPUTLENGTH		   /* input length less than need*/
} AC3D_RET_TYPE;


/* basic information */
#define AC3D_TRUE	                      1
#define AC3D_INPUT_BUF_SIZE               3840              /* byte count */
#define AC3D_FAST_MEMORY                  1
#define AC3D_SLOW_MEMORY                  0
#define AC3D_MAX_NUM_MEM_REQS             1
#define AC3D_DATA_ALIGN_IN_BYTES          16
#define AC3D_MEM_TYPE                     AC3D_FAST_MEMORY  /* can be changed */
#define AC3D_FRAME_SIZE                   1536              /* No of stereo samples outputed per\
                                                               call to the decode frame */
#define AC3D_MEMDESC                      0
#define AC3D_MEMPRIORITY                  0


/**********************************************************************************/


typedef struct
{
        char       *ac3fname ;
        char       *pcmfname ;
	char       *debugdir ;
        AC3D_INT16 pcmoff[6];
        AC3D_INT16 pcmmod[6];

        void      *pcmptr[6];
        AC3D_INT32 numchans ;
        AC3D_INT32 chanptr[6] ;
        AC3D_INT16 wordsize ;					/* output word size code */
        AC3D_INT32 dynrngscalelow ;				/* dynamic range scale factor (low) */
        AC3D_INT32 dynrngscalehi ;				/* dynamic range scale factor (high) */
        AC3D_INT32 pcmscalefac  ;				/* PCM scale factor */
        AC3D_INT32 compmode ;					/* compression mode */
        AC3D_INT32 stereomode ;					/* stereo downmix mode */
        AC3D_INT32 dualmonomode ;				/* dual mono reproduction mode */
        AC3D_INT32 outputmode ;					/* output channel configuration */
        AC3D_INT16 outlfeon ;					/* output subwoofer present flag */
        AC3D_INT32 outputflg ;					/* enable output file flag */
        AC3D_INT32 framecount ;					/* frame counter */
        AC3D_INT32 blockcount ;					/* block counter */
        AC3D_INT32 framestart ;					/* starting frame */
        AC3D_INT32 frameend ;					/* ending frame */
        AC3D_INT32 useverbose ;					/* verbose messages flag */
        AC3D_INT32 debug_arg ;					/* debug argument */

#ifdef KCAPABLE
        AC3D_INT32 kcapablemode ;				/* karaoke capable mode */
#endif
	AC3D_INT16 ac3d_endianmode;				/* 0 Ledian; 1 Bedian; 2 check by decoder it self; others Ledian */
	AC3D_INT32 ac3d_sampling_freq;				/* Sampling frequency of the current frame in Khz */
	AC3D_INT32 ac3d_num_channels;				/* Number of channels decoded in current frame */
	AC3D_UINT32 ac3d_frame_size;				/* Number of stereo samples being outputted for this*/
	AC3D_INT32 ac3d_acmod;					/* ac3 acmod */
	AC3D_INT32 ac3d_bitrate;         			/* ac3 bitrate */
	AC3D_INT16 ac3d_outputmask;         			/* ac3 outputmask */
        AC3D_INT16 dsurmod;					/* Dolby surround mode */
        AC3D_INT16 dmixmod;					/* preferred downmix mode */
        AC3D_INT16 dsurexmod;					/* Surround EX mode flag */
        AC3D_INT16 dheadphonmod;				/* Dolby Headphone encoded flag */
        AC3D_INT16 adconvtyp;					/* Advanced converter flag */
        AC3D_INT16 outstereomode;                               /* 0--represent Lt/Rt mode, 2--Lo/Ro mode, -1 --- invalid mode */
        AC3D_INT16 ac3d_lfeon;                                  /* lfe flag , if lfe is on, ac3d_lfeon = 1; else ac3d_lfeon = 0.*/
}AC3D_PARAM;




/* requery memeory data structure */
typedef enum
{
    AC3D_STATIC_MEM,                                        	/* 0 for static memory */
    AC3D_SCRATCH_MEM                                        	/* 1 for scratch memory */
} AC3D_MEM_DESC;

typedef struct {
	AC3D_INT32		 s32AC3DSize;                   /* Size in bytes */
	AC3D_INT32 	         s32AC3DType;                   /* Memory type Fast or Slow */
	AC3D_MEM_DESC		 s32AC3DMemDesc;                /* to indicate if it is scratch memory */
	AC3D_INT32               s32AC3DPriority;               /* In case of fast memory, specify the priority */
	void 	                 *app_base_ptr;                 /* PoDSPinter to the base memory , which will be allocated and                                                             * filled by the  application */
} AC3DMemAllocInfoSub;


typedef struct {
	AC3D_INT32 		 s32NumReqs;                    /*  Number of valid memory requests */
	AC3DMemAllocInfoSub	 sMemInfoSub[AC3D_MAX_NUM_MEM_REQS];
} AC3DMemAllocInfo;

/* end memory data structrue */

typedef struct AC3DDecoderConfig
{
	AC3DMemAllocInfo	sAC3DMemInfo;
	void			*psAC3DecodeInfoStructPtr;        /* Global_struct, poDSPint to bs info, like sample rate?*/
	                                                          /* perserved first for application parser use.*/


	AC3D_PARAM         	*pAC3param;
	void                	*pContext;


#ifdef DEBUG_AC3
	void (*filetw_func)(char *filename, char *text);
	void (*filefw_func)(char *filename, AC3D_INT32 *buf, AC3D_INT32 start, AC3D_INT32 count);
	void (*filesw_func)(char *filename, AC3D_INT16 *buf, AC3D_INT32 start, AC3D_INT32 count);
	void (*fileinit_func)(char *filename,int useverbose,int * filecnt, char files[][128]);
	int  (*sprintf_ext)( char * str, const char * format, ... );
#endif

} AC3DDecoderConfig;

/* api part */

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN AC3D_RET_TYPE AC3D_QueryMem(AC3DDecoderConfig *ac3decconfig);

EXTERN AC3D_RET_TYPE AC3D_dec_init(AC3DDecoderConfig *ac3decconfig,AC3D_UINT8 *input_buf_ptr,AC3D_INT32 input_buf_length);

EXTERN AC3D_RET_TYPE AC3D_dec_Frame(AC3DDecoderConfig *ac3deccfg,AC3D_INT32 *output_pcm_buf,AC3D_INT16 *input_buf_ptr,AC3D_INT32 ILength);

EXTERN const char *AC3D_get_version_info(void);

#endif
