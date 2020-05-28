//============================================================================================
/**
 * @file	record_corner.h
 * @bfief	レコードコーナー処理
 * @author	Akito Mori
 * @date	06.03.26
 */
//============================================================================================
#ifndef _RECORD_CORNER_H_
#define _RECORD_CORNER_H_

#include "savedata/savedata_def.h"
#include "field/comm_union_view_common.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"
//============================================================================================
//	定義
//============================================================================================

// プロセス定義データ
extern PROC_RESULT RecordCornerProc_Init( PROC * proc, int * seq );
extern PROC_RESULT RecordCornerProc_Main( PROC * proc, int * seq );
extern PROC_RESULT RecordCornerProc_End( PROC * proc, int * seq );

// ポインタ参照だけできるレコードコーナーワーク構造体
typedef struct RECORD_WORK RECORD_WORK;	

///	外部から受け取るレコードコーナー処理に必要なワーク
typedef struct {
	SAVEDATA 			*sv;
	COMM_UNIONROOM_VIEW *union_view;
	CONFIG				*config;
	RECORD				*record;
	FNOTE_DATA			*fnote;
}RECORD_INPUT_PARAM;


#endif
