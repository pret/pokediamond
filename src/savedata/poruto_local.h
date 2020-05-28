/**
 *	@file	poruto_local.h
 *	@brief	ポルトセーブデータブロック 構造体定義
 *	@author	Miyuki Iwasawa
 *	@date	06.3.10
 */

#ifndef __H_PORUTO_LOCAL_H__
#define __H_PORUTO_LOCAL_H__

#include "savedata/poruto.h"

///ポルトセーブデータブロック定義
typedef struct _PORUTO_BLOCK{
 PORUTO_DATA	poruto[PORUTO_STOCK_MAX];
}_PORUTO_BLOCK;

#endif //__H_PORUTO_LOCAL_H__

