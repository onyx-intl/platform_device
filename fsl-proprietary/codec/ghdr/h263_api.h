///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007-2008 Oriole Software Pvt. Ltd.
//
//! \file h263_api.h
//! \brief Defines Public API for H263 decoder
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////
#ifndef _H263_API_H_
#define _H263_API_H_

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif



#ifndef NALU_BUF_T
#define NALU_BUF_T
//! \brief NALU buffer
typedef struct {
    unsigned char *buf; //!< Pointer to allocated NALU buffer
    int len;            //!< len of data from buf ptr into NALU buffer
    int max_len;        //!< allocated size of NALU buffer
} NAL_BUF_T;
#endif

#ifndef INFO_STRUCT_
#define INFO_STRUCT_
typedef struct {
    short width;    //!< Actual width of decoded frame
    short height;   //!< Actual width of decoded frame
    short stride;   //!< number of luma bytes to skip after width
}INFO_STRUCT_T;
#endif


/* The callback functions used for getting frame buffers is defined below; it will get one frame buffer for decoder */
typedef unsigned char * (*cbGetOneFrameBuffer)( void* pvAppContext);

/* It is possible that the gotten frame buffer for decoding the current frame still stored the reference data 
   so the decoder has to reject the buffer. After the rejection by calling this callback function, 
   the decoder will invoke cbGetOneFrameBuffer to ask for frame buffer again */
typedef void (*cbRejectOneFrameBuffer)( unsigned char * mem_ptr, void* pvAppContext);

typedef void (*cbReleaseOneFrameBuffer)( unsigned char * mem_ptr, void* pvAppContext);

/* the above callback functions are grouped into a structure named FrameManager */
typedef struct _sSorensonDecFrameManager
{
    cbGetOneFrameBuffer 	 GetterBuffer;
    cbRejectOneFrameBuffer 	 RejectorBuffer;
    cbReleaseOneFrameBuffer ReleaseBuffer;
    void*			              pvAppContext ;
}sSorensonDecFrameManager; 

#define ALIGN16(x) ( ( ((x)+15)/16 )*16 )
#define MIN_FRAME_BUFFERS   15
#define SUCCESS             0
#define ENABLE_DEBLOCKING   1
#define ERROR_PARAM         -1
#define NO_DATA             -2
///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

EXTERN int h263_get_resolution (NAL_BUF_T *pNalBuf,int *width, int *height);

///////////////////////////////////////////////////////////////////////////////
//! \brief Provodes decoder memory details
// 
//! \param [in] i32ActualWidth       Actual frame width of input frame
//! \param [in] i32ActualHeight      Actual frame height of input frame
//! \param [out] pFLVDecStructSize Pointer size of FLV Decoder memory
//! \param [out] pi32FrameBufSize  Single frame buffer size
//! \param [out] pi32MinFrameBufferCount Minimum number of frame buffers required
//! \retval -1 in case of invalid parameters
//! \retval 0 in case of SUCCESS
///////////////////////////////////////////////////////////////////////////////
EXTERN int H263_GetMemoryInfo(int i32ActualWidth, int i32ActualHeight,
    int *pFLVDecStructSize ,int *pi32FrameBufSize, int *pi32MinFrameBufferCount);

///////////////////////////////////////////////////////////////////////////////
//! \brief Initializes H263 decoder.
//
//! \param [in] i32ActualWidth       Actual frame width of input frame
//! \param [in] i32ActualHeight      Actual frame height of input frame
//! \param [in] pFLVDecStruct    Pointer to FLV decoder memory
//! \param [in] pFrameBufferBase Pointer to frame buffer base address
//! \param [in] FrameBufferCount Number of frame buffer allocated
//! \param [out] pInfo           Info about layout of frame
//! \retval -1 in case of invalid parameters
//! \retval 0 in case of SUCCESS
///////////////////////////////////////////////////////////////////////////////
EXTERN int H263_InitDecoder(int i32ActualWidth, int i32ActualHeight,void *pFLVDecStruct, sSorensonDecFrameManager* pFrameManager, 
         /*void *pFrameBufferBase[15], int FrameBufferCount, */INFO_STRUCT_T *pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief Decodes a frame and provides yuv output pointers into pFrame
//
//! \param [in] pNalBuf        Pointer to NAL buffer
//! \param [in] pFLVDecStruct  Pointer to FLV decoder memory
//! \param [in] option         Set to ENABLE_DEBLOCKING to enable deblocking
//! \param [out] pCurrentYUVFrame  pointer to beginign of decoded frame
//! \retval 0 when all frames are decoded
//! \retval -1 when unsupported FLV packet is passed
//! \retval 1 when valid FLV packet is found
///////////////////////////////////////////////////////////////////////////////
EXTERN int H263_DecodeFrame(NAL_BUF_T *pNalBuf, void *pFLVDecStruct,int option, 
                     unsigned char **pCurrentYUVFrame);

///////////////////////////////////////////////////////////////////////////////
//! \brief Resets H263 decoder
//! \param [in] pFLVDecStruct  Pointer to FLV decoder memory
//! \retval -1 in case of invalid pointer
//! \retval 0 in case of success
///////////////////////////////////////////////////////////////////////////////
//EXTERN int H263_ResetDecoder(void *pFLVDecStruct);

#endif//_H263_API_H_
