//============================================================================================
/**
 * @file	box.h
 * @brief	ボックス画面の呼び出しに必要な定数・関数
 * @author	taya
 * @date	2005.09.09
 */
//============================================================================================
#ifndef __BOX_H__
#define __BOX_H__

#include "system\procsys.h"
#include "savedata\savedata_def.h"


#include "box_mode.h"

typedef int BOX_MODE;


//------------------------------------------------------
/**
 * ボックス画面PROCパラメータ
 */
//------------------------------------------------------
typedef struct {
	// [in] 
	SAVEDATA*  savedata;
	BOX_MODE   mode;

	// [out]
	BOOL       modifiedFlag;	///< ボックス内容が変更されたらTRUEが入る

}BOX_PROC_PARAM;


//------------------------------------------------------
/**
 * ボックス画面PROC関数
 */
//------------------------------------------------------
extern PROC_RESULT BoxProc_Init( PROC * proc, int * seq );
extern PROC_RESULT BoxProc_Main( PROC* proc, int* seq );
extern PROC_RESULT BoxProc_End( PROC* proc, int* seq );


#endif
