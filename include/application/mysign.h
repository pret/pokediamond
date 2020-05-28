//============================================================================================
/**
 * @file	mysign.h
 * @bfief	自分サイン作成処理
 * @author	Akito Mori
 * @date	06.03.11
 */
//============================================================================================
#ifndef _MYSIGN_H_
#define _MYSIGN_H_

//============================================================================================
//	定義
//============================================================================================

// プロセス定義データ
extern PROC_RESULT MySignProc_Init( PROC * proc, int * seq );
extern PROC_RESULT MySignProc_Main( PROC * proc, int * seq );
extern PROC_RESULT MySignProc_End( PROC * proc, int * seq );

// ポインタ参照だけできるお絵かきボードワーク構造体
typedef struct MYSIGN_WORK MYSIGN_WORK;	



#endif