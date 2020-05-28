//==============================================================================================
/**
 * @file	opening_call.c
 * @brief
 * @date	2006.02.17
 * @author	nohara
 *
 */
//==============================================================================================

#include "system/procsys.h"
#include "opening_sys.h"

FS_EXTERN_OVERLAY(opening);
//==============================================================================================
//
//	グローバル変数
//
//==============================================================================================
extern PROC_RESULT Intro_Init( PROC * proc, int * seq );
extern PROC_RESULT Intro_Main( PROC * proc, int * seq );
extern PROC_RESULT Intro_Exit( PROC * proc, int * seq );

//プロセス定義データ
const PROC_DATA OpeningProcData = {
#if 0
	OpeningProc_Init,
	OpeningProc_Main,
	OpeningProc_End,
	FS_OVERLAY_ID(opening),
#else
	Intro_Init,
	Intro_Main,
	Intro_Exit,
	FS_OVERLAY_ID(opening),
#endif
};

