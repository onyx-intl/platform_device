/*
***********************************************************************
* Copyright 2009-2010 by Freescale Semiconductor, Inc.
* All modifications are confidential and proprietary information
* of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
***********************************************************************
*
*  History :
*  Date             Author              Version    Description
*
*  Aug,2009         B18987              0.1        Initial Version
*
*/
#ifndef FSL_MEDIA_STREAM_H
#define FSL_MEDIA_STREAM_H

/* Deprecated API, to be replaced by the new one. */
typedef void* file_handle_t;

typedef struct file_stream_s
{
    file_handle_t 	file_handle;
     uint8 * 	file_path; 
    
    int32	(*pf_fopen)( struct file_stream_s *stream, const uint8 * mode, void * context); 
    uint32  (*pf_fread)( struct file_stream_s *stream, void * buffer, uint32 nb, void * context);
    int64  	(*pf_fseek)( struct file_stream_s *stream, int64 offset, int32 whence, void * context); /* whence: SEEK_SET, SEEK_CUR, or SEEK_END */
    int64  	(*pf_ftell)( struct file_stream_s *stream, void * context); /* get current pointer postion of the stream */
    int64 	(*pf_fsize)( struct file_stream_s *stream, void * context); /* get size of the entire file size */
    int32 	(*pf_fclose)( struct file_stream_s *stream, void * context);
   
} file_stream_t;


#endif
  
