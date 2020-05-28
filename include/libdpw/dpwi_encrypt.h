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
	@brief	DPW internal encryption module
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#ifndef _DPWI_COMMON_ENC_H_
#define _DPWI_COMMON_ENC_H_


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/

// 以下乱数生成用
#define MYRAND_A 69					// 8の倍数＋5 の数
#define MYRAND_C 4369				// 奇数
#define MYRAND_M 0x80000000			// 2^n　の数
#define CHECKSUM_MASK 0x4a3b2c1d	// checksum mask


//! DpwiCommon 関数の戻り値
typedef enum {
	DPWI_COMMON_ENC_SUCCESS,		//!<	成功
	DPWI_COMMON_ENC_ERROR_NOMEMORY,	//!<	メモリー確保エラー
	DPWI_COMMON_ENC_ERROR_NOBUFFER	//!<	渡されたバッファの容量不足
} DpwiEncResult;



/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/

DpwiEncResult DpwiEncrypt(u32 pid, const u8* src, int srclen, u8* outbuf, int outlen);

u32 DpwiB64Size( u32 len );

#ifdef __cplusplus
}
#endif


#endif
