/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_encrypt.c

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

#include <dwc.h>

#include <nonport.h>
#include "include/libdpw/dpwi_encrypt.h"

#ifdef _NITRO
#include "include/libdpw/dpwi_define.h"
#endif


/*-----------------------------------------------------------------------*
					型・定数宣言
 *-----------------------------------------------------------------------*/
#define SIZE_CHECKSUM	4
#define SIZE_PID		4

/*-----------------------------------------------------------------------*
					グローバル変数定義
 *-----------------------------------------------------------------------*/

static int s_local_seed;


/*-----------------------------------------------------------------------*
					関数プロトタイプ宣言
 *-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*
					乱数生成ルーチン
 *-----------------------------------------------------------------------*/
static void my_randinit(unsigned long seed) {
	s_local_seed = (int)(seed | (seed << 16));
}

static unsigned char my_rand(void) {

	s_local_seed = (int)((MYRAND_A * s_local_seed + MYRAND_C) % MYRAND_M);

	return (unsigned char)((s_local_seed >> 16) & 0xff);
}



/*-----------------------------------------------------------------------*
					外部公開関数
 *-----------------------------------------------------------------------*/

/*!
	データを暗号化してバッファに書き出します。
	
	独自のストリーム暗号方式でデータを暗号化します。outbufには最低でも
	ROUNDUP((len+4)/3)*4+1のサイズが必要です。
	
	@param[in] src			暗号化するソース
	@param[in] len			srcのサイズ
	@param[in,out] outbuf	暗号化されたデータを書き込むバッファ
	@param[in] outlen		outbufのサイズ
*/
DpwiEncResult DpwiEncrypt(u32 pid, const u8* src, int len, u8* outbuf, int outlen){

	unsigned char* tmpbuf;
	u32 sum = 0;
	int i;

	// outbufのサイズを調べる
	if( outlen < (int)DpwiB64Size((u32)(len + SIZE_CHECKSUM + SIZE_PID)) + 1 )
		return DPWI_COMMON_ENC_ERROR_NOBUFFER;

	// ワークバッファを確保
	tmpbuf = (unsigned char*)DWC_Alloc( (DWCAllocType)DPWI_ALLOC, (unsigned long)(len + SIZE_CHECKSUM + SIZE_PID) );
	if( tmpbuf == NULL )
		return DPWI_COMMON_ENC_ERROR_NOMEMORY;

	// チェックサムを計算
	sum += (u8)((pid >> 24) & 0xff);
	sum += (u8)((pid >> 16) & 0xff);
	sum += (u8)((pid >>  8) & 0xff);
	sum += (u8)((pid      ) & 0xff);

	for( i=0; i<len; i++ )
		sum += src[i];

	// チェックサムを乱数の種とする。
	my_randinit( sum );

	// 先頭４バイトから暗号化されたPIDを格納する
	tmpbuf[4] = (u8)(((pid      ) & 0xff) ^ my_rand());
	tmpbuf[5] = (u8)(((pid >>  8) & 0xff) ^ my_rand());
	tmpbuf[6] = (u8)(((pid >> 16) & 0xff) ^ my_rand());
	tmpbuf[7] = (u8)(((pid >> 24) & 0xff) ^ my_rand());

	// スコア・ＩＤを乱数でマスクをかけていく。
	for( i=0; i<len; i++ )
		tmpbuf[ SIZE_CHECKSUM+SIZE_PID + i ] = (u8)(src[i] ^ my_rand());

	// チェックサムにマスクをかける
	sum ^= CHECKSUM_MASK;


	// 先頭４バイトにマスクをかけたチェックサムを格納する
	tmpbuf[0] = (u8)((sum >> 24) & 0xff);
	tmpbuf[1] = (u8)((sum >> 16) & 0xff);
	tmpbuf[2] = (u8)((sum >>  8) & 0xff);
	tmpbuf[3] = (u8)((sum      ) & 0xff);

	// base64 でエンコードする
	B64Encode(	(const char*)tmpbuf,
				(char*)outbuf,
				(int)(len + SIZE_CHECKSUM + SIZE_PID),
				2 /* url safe */ );

	// NULL終端する
	((char*)outbuf)[DpwiB64Size((u32)(len + SIZE_CHECKSUM + SIZE_PID))] = '\0';

	// ワークバッファを開放
	DWC_Free( (DWCAllocType)DPWI_ALLOC, tmpbuf, (u32)0 );

	return DPWI_COMMON_ENC_SUCCESS;
}


/*!
	BASE64エンコード後のサイズを求めます
	
	@param[in] len			エンコードするデータサイズ

	@return	エンコード後のサイズ
*/
u32 DpwiB64Size( u32 len ){

	u32 i;

	i = (len) % 3 != 0 ? (u32)1 : (u32)0;

	return (((u32)(len / 3)) + i) * 4;
}
