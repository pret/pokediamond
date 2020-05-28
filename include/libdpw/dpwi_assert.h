/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_encrypt.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DPW internal assert
	
	@author	kitayama(kitayama_shigetoshi@nintendo.co.jp)
	
	@version
		@li
*/

#ifndef _DPWI_COMMON_ASSERT_H_
#define _DPWI_COMMON_ASSERT_H_


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

//! SDK_TASSERTMSGと異なり、FINALROM以外でワーニングを行う

#ifndef  SDK_FINALROM
#define DPW_TASSERTMSG(exp, ...) \
    (void) ((exp) || (OSi_TPanic(__FILE__, __LINE__, __VA_ARGS__), 0))
#else  // SDK_FINALROM
#define DPW_TASSERTMSG(exp, ...)    ((void) 0)
#endif // SDK_FINALROM


#ifndef  SDK_FINALROM
#define DPW_NULL_TASSERT(exp) \
             (void) ((exp != NULL) || (OSi_TPanic(__FILE__, __LINE__, "Pointer must not be NULL ("#exp")"), 0))
#else  // SDK_FINALROM
#define DPW_NULL_TASSERT(exp)           ((void) 0)
#endif // SDK_FINALROM


#ifndef  SDK_FINALROM
#define DPW_MINMAX_TASSERT(exp, min, max) \
             (void) (((exp) >= (min) && (exp) <= (max)) || \
                     (OSi_TPanic(__FILE__, __LINE__, #exp " is out of bounds(%d)\n%d <= "#exp" <= %d not satisfied.", exp, min, max), 0))
#else  // SDK_FINALROM
#define DPW_MINMAX_TASSERT(exp, min, max)           ((void) 0)
#endif // SDK_FINALROM



/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/




#ifdef __cplusplus
}
#endif


#endif
