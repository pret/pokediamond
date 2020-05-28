/**
 *	@file	fld_nmixer.c
 *	@brief	フィールド用　ナッツミキサーヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_FLD_NUTMIXER_H__
#define __H_FLD_NUTMIXER_H__


#include "application/nutmixer.h"

///プレイモード定義
#define NUTMIXER_CALL_LOCAL	(0)	///<一人プレイモード
#define NUTMIXER_CALL_COMM	(1)	///<通信プレイモード

/**
 *	@brief	ナッツミキサー呼び出しワークデータ作成
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	一人プレイモード
 *					NUTMIXER_CALL_COMM:1	通信モード
 */
extern NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID);

/**
 *	@brief	ナッツミキサー呼び出し
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	一人プレイモード
 *					NUTMIXER_CALL_COMM:1	通信モード
 */
extern NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID);


#endif	//__H_FLD_NUTMIXER_H__
