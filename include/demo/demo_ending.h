//============================================================================================
/**
 * @file	demo_ending.h
 * @brief	エンディングデモ
 * @author	taya
 * @date	2006.06.01
 */
//============================================================================================
#ifndef __DEMO_ENDING_H__
#define __DEMO_ENDING_H__



typedef struct {

	int					playerSex;	///< プレイヤー性別
	BOOL				clearFlag;	///< 一度でもエンディングを見たことがあるか？
	const ZUKAN_WORK*	zukanWork;	///< 図鑑ワークポインタ

}ENDING_PROC_PARAM;



extern PROC_RESULT EndingDemoProc_Init( PROC * proc, int * seq );
extern PROC_RESULT EndingDemoProc_Main( PROC * proc, int * seq );
extern PROC_RESULT EndingDemoProc_Quit( PROC * proc, int * seq );


#endif
