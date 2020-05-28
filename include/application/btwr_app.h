/**
 *	@file	btwr_app.h
 *	@brief	バトルタワー関連アプリ
 *	@author	Miyuki Iwasawa
 *	@date	06.05.26
 */

#ifndef __H_BTWR_APP_H__
#define __H_BTWR_APP_H__

#include "savedata/savedata_def.h"
///外部公開パラメータ引継ぎワーク
typedef struct _BTOWER_APP_PARAM{
	SAVEDATA* save;
	u16	mainMode;
	u16	subMode;
}BTOWER_APP_PARAM;

extern PROC_RESULT BTowerAppProc_Init( PROC *proc,int *seq);
extern PROC_RESULT BTowerAppProc_Main( PROC *proc,int *seq);
extern PROC_RESULT BTowerAppProc_End( PROC *proc,int *seq);

#endif	//__H_BTWR_APP_H__

