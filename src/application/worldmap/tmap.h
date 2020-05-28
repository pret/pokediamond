/**
 *	@file	tmap.h
 *	@brief	タウンマップモジュール内でだけ公開するヘッダ
 *	@date	05.11.02
 *	@author	Miyuki Iwasawa
 */
#ifndef _TMAP_H_
#define _TMAP_H_

#include "townmap.dat"
#include "tmap_def.h"
#include "tmap_gra.naix"	//アーカイブファイル
#include "tmap_sub.h"	//サブ


//================================================================
///データ型定義エリア
//================================================================
typedef struct _TMAP_SCROLLPRM{
	int	scrX;
	int	scrY;
	int	difX;
	int	difY;
}TMAP_SCROLLPRM;

///プロトタイプ
struct TMAP_MAIN_DAT;
///サブプロセス定義用関数型
//typedef int (*TMapSubProc)(TMAP_MAIN_DAT* pMain);

///メインワーク
typedef struct TMAP_MAIN_DAT{
	u8	mode;	///<動作モード取得
	u8	forcus;	///<上下画面どちらに制御がいるか？
	u16	mapView;	///<配布マップ描画制御フラグ
	int	heapID;	///<HeapID
	int	main_seq;	///<シーケンス
	int	sub_seq;	///<シーケンス
	int seq;
	int	wipe_f;		///<ワイプフラグ

	int	cposX;
	int cposZ;
	int	gx;
	int gz;
	
	GF_BGL_INI *bgl;	///<BGLデータ
	TOWNMAP_PARAM* param;	///<外部引継ぎパラメータIO
	FMZ_PTR	pZone;		///<ゾーンデータ取得ポインタ
	void*	pSwork;			///<サブワーク確保ポインタ
	int (*keyFunc)(struct TMAP_MAIN_DAT*);

	TMAP_VIEW_DAT*	pVDat;
	TMAP_GDAT_LIST* pBDat;
	TMAP_FOOT	foot[TMAP_FVIEW_MAX];
	
	///メッセージリソース
	MSGDATA_MANAGER*	pMsgMap;
	MSGDATA_MANAGER*	pMsgTMap;
	STRBUF				*placeName;
	
	///VBlank転送用保存パラメータ
	int	vb_trans;
	int	vb_zoneID;
	TMAP_GDAT*	vb_block;
	
	///グラフィックリソース
	void*	pScrBuf01;
	void*	pScrBuf01_back;
	void*	pScrBuf01_dis;
	void*	pScrBuf02_dm;
	void*	pScrBuf02_dr;
	void*	pScrBuf02_dswm;
	void*	pScrBuf02_sw;
	void*	pScrBuf02_dis;
	
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr01_back;
	NNSG2dScreenData*	pScr01_dis;
	NNSG2dScreenData*	pScr02_dm;
	NNSG2dScreenData*	pScr02_dr;
	NNSG2dScreenData*	pScr02_dswm;
	NNSG2dScreenData*	pScr02_sw;
	NNSG2dScreenData*	pScr02_dis;

	CATS_SYS_PTR	pCActSys;	///<セルアクターシステム
	CATS_RES_PTR	pCActRes;	///<セルアクターリソース
	CATS_ACT_PTR	pCAct;		///<アクト
}TMAP_MAIN_DAT;

///サブプロセス定義用関数型
typedef int (*TMapSubProc)(TMAP_MAIN_DAT* pMain);

typedef struct _TMAP_SUB_PROC{
	TMapSubProc	init;
	TMapSubProc	build;
	TMapSubProc	fadein;
	TMapSubProc	fadeout;
	TMapSubProc	keyIO;
	TMapSubProc	main;
	TMapSubProc	draw;
	TMapSubProc	release;
	TMapSubProc	vBlank;
}TMAP_SUB_PROC;

///==============================================================
//タウンマップモジュール内グローバル関数
///==============================================================

#endif	//_TMAP_H_
