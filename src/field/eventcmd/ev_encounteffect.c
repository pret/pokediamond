//============================================================================================
/**
 * @file	ev_encounteffect.c
 * @brief	フィールドエンカウントエフェクト
 * @date	2005.12.17
 * @author	tamada
 *
 * 2005.07.28	encount_effect.cから切り離す
 */
//============================================================================================

#include "common.h"
#include "../field_common.h"
#include "../field_event.h"

#include "system/snd_tool.h"
#include "../encount_effect.h"
#if 0
#include "system/brightness.h"
#include "field_encount.h"

#include "map_tool.h"
#include "fieldmap.h"

#include "encount_set.h"

#include "mapdefine.h"
#include "poketool/monsno.h"
#include "eventdata.h"

#include "ev_mapchange.h"

#include "sway_grass_enc.h"
#include "map_attr.h"
#endif

//============================================================================================
//
//
//	イベント擬似コマンド：エンカウントエフェクト処理
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	BOOL end_flag;
	int effect_no;
	int bgm_no;
}EV_ENC_EFF_WORK;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_EncountEffect(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_ENC_EFF_WORK * eeew;
	fsys = FieldEvent_GetFieldSysWork(event);
	eeew = FieldEvent_GetSpecialWork(event);
	switch (eeew->seq) {
	case 0:
		//エンカウントエフェクト呼び出し
		EncountEffectStart(eeew->effect_no, fsys, &eeew->end_flag);

		Snd_DataSetByScene( SND_SCENE_BATTLE, eeew->bgm_no, 1 );	//バトル曲再生
	
		//フェードアウト前にバトルBGMを読み込む
		//Snd_BattleBgmSet( eeew->bgm_no, 1 );

		//フェードアウト後に、バトルSEを読み込む(仮)
		//Snd_BattleSeSet();	//あとで、移動させる。。。
		eeew->seq ++;
		break;
	case 1:
		if(eeew->end_flag == TRUE){
			sys_FreeMemoryEz(eeew);
			return TRUE;
		}
		break;

	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：エンカウントエフェクト呼び出し
 * @param	event		イベント制御ワークへのポインタ
 * @param	effect_no	エフェクト指定
 * @param	bgm_no		ＢＧＭ指定
 */
//-----------------------------------------------------------------------------
void EventCmd_EncountEffect(GMEVENT_CONTROL * event, int effect_no, int bgm_no)
{
	EV_ENC_EFF_WORK * eeew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_ENC_EFF_WORK));
	eeew->seq = 0;
	eeew->end_flag = FALSE;
	eeew->effect_no = effect_no;
	eeew->bgm_no = bgm_no;
	FieldEvent_Call(event, GMEVENT_EncountEffect, eeew);
}

