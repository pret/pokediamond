/**
 *	@file	fld_nmixer.c
 *	@brief	フィールド用　ナッツミキサーソース
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "application/nutmixer.h"

///プロトタイプ
NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID, FNOTE_DATA * fnote);
NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID);

/**
 *	@brief	ナッツミキサー呼び出しワークデータ作成
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	一人プレイモード
 *					NUTMIXER_CALL_COMM:1	通信モード
 */
NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID, FNOTE_DATA * fnote)
{
	NUTMIXER_PARAM* wk;
	
	wk = sys_AllocMemory(heapID,sizeof(NUTMIXER_PARAM));
	MI_CpuClear8(wk,sizeof(NUTMIXER_PARAM));

	//セーブデータブロック取得
	wk->SaveData = savedata;
	wk->poruSave = SaveData_GetPorutoBlock(savedata);
	wk->mySave = SaveData_GetMyStatus(savedata);
	wk->itemSave = SaveData_GetMyItem(savedata);
	wk->configSave = SaveData_GetConfig(savedata);
	wk->fnote = fnote;

	//動作モード取得
	wk->sys_mode = mode;

	return wk;
}

//-----------------------------------------------------------------------------
/**
*	ナッツミキサー関連
*/
//-----------------------------------------------------------------------------
/**
 *	@brief	ナッツミキサーサブプロセス登録
 */
static void NutMixer_SetProc(FIELDSYS_WORK* fsys,NUTMIXER_PARAM* np)
{
	GameSystem_StartSubProc(fsys, &NutMixerProcData,np);
}

/**
 *	@brief	ナッツミキサー呼び出し
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	一人プレイモード
 *					NUTMIXER_CALL_COMM:1	通信モード
 */
NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID)
{
	NUTMIXER_PARAM* np;
	
	np = NutMixer_CreateCallWork(mode,GameSystem_GetSaveData(fsys),heapID,fsys->fnote);	
	NutMixer_SetProc(fsys,np);
	
	return np;
}

