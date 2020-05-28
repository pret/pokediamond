//============================================================================================
/**
 * @file	oekaki.h
 * @bfief	お絵かきボード画面処理
 * @author	Akito Mori
 * @date	06.02.13
 */
//============================================================================================
#ifndef _OEKAKI_H_
#define _OEKAKI_H_

//============================================================================================
//	定義
//============================================================================================

// プロセス定義データ
extern PROC_RESULT OekakiProc_Init( PROC * proc, int * seq );
extern PROC_RESULT OekakiProc_Main( PROC * proc, int * seq );
extern PROC_RESULT OekakiProc_End( PROC * proc, int * seq );

// ポインタ参照だけできるお絵かきボードワーク構造体
typedef struct OEKAKI_WORK OEKAKI_WORK;	

typedef struct{
	COMM_UNIONROOM_VIEW *view;
	FNOTE_DATA			*fnote;
	CONFIG				*config;
}OEKAKI_PARAM;

#endif