/**
 *	@file	porudemo.h
 *	@brief	ポルトデモヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#ifndef __H_PORUDEMO_H__
#define __H_PORUDEMO_H__

#include "poketool/poke_tool.h"
#include "savedata/poruto_util.h"

//======================================================
//データ継承構造体定義
//======================================================
typedef struct _PORUDEMO_PARAM{
	POKEMON_PARAM*	pp;	///<ポケモン
	PORUTO_DATA*	poruto;	///<ポルトデータ
	u16	flavor;		///<ポルトの種類
	u8	msg_spd;	///<メッセージスピード
	u8	win_type;	///<ウィンドウタイプ
}PORUDEMO_PARAM;

//======================================================
//オーバーレイプロセス定義
//======================================================
extern PROC_RESULT PoruDemo_Init(PROC* proc,int *seq);
extern PROC_RESULT PoruDemo_Main(PROC* proc,int *seq);
extern PROC_RESULT PoruDemo_End(PROC* proc,int *seq);

#endif	//__H_PORUDEMO_H__
