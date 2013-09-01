
 /************************************************************************
  * Copyright 2005-2010 by Freescale Semiconductor, Inc.
  * All modifications are confidential and proprietary information
  * of Freescale Semiconductor, Inc. ALL RIGHTS RESERVED.
  ************************************************************************/

#ifndef LOG_API_H
#define LOG_API_H
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////////
//
//
//
//  File Description:   Logging API's defined
//
//  Author(s):          (1) Vijay PY (vijaypy@motorola.com)
//
//  Version History:    29/Sep/2004 - Vijay PY Created
//
//
///////////////////////////////////////////////////////////////////////////

//APIS for logging.
// All the codec libraries will use the below function name symbols to
// implement debug logs. These function symbols will be implemented
// by the logger library or task.

int DebugLogData(short int msgid,void *ptr,int size);
int DebugLogText(short int msgid,char *fmt,...);

#ifdef VC_PLUS_PLUS

int DebugLogTextVC(int id1, int id2,char *fmt,...);

#endif

#endif

