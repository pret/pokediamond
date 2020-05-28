/**
 *  @file	poruto.h
 *	@brief	ポルト　セーブデータ構造定義　グローバルヘッダ
 *	@date	06.02.28
 *	@author	Miyuki Iwasawa
 *	
 *	＊データ実体を定義する箇所以外では参照してはいけません
 *	仮想ポインタ経由でデータアクセスできれば良い箇所では
 *	savedata/poruto_util.hをincludeしてください
 */

#ifndef __H_PORUTO_H__
#define __H_PORUTO_H__

///ポルトデータ型
//=============================================================
//	外部公開していますが、直接構造体メンバへアクセスすることは
//	許可していません。
//
//	メンバアクセスはsavedata/poruto_util.hに定義された
//	アクセス系関数を介してください
//
//=============================================================
typedef struct _PORUTO_DATA{
 union{
	struct{		
	u8	flavor;		///<味の種類
	u8	spicy;		///<辛み値
	u8	astringent;	///<渋み値
	u8	sweet;		///<甘味
	u8	bitter;		///<苦味
	u8	sour;		///<酸味
	u8	taste;		///<旨味値
	u8	pad_dmy;	///<パディング用ダミー
	};
	u8 param[8];
 };
}_PORUTO_DATA;

//============================================================
///ポルトデータアクセス系関数
//============================================================
#include "savedata/poruto_util.h"

#endif	//__H_PORUTO_H__
