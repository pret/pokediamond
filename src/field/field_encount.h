//============================================================================================
/**
 * @file	field_encount.h
 * @brief
 * @date	2005.07.28
 */
//============================================================================================

#ifndef	__FIELD_ENCOUNT_H__
#define __FIELD_ENCOUNT_H__

#include "battle/battle_common.h"
#include "poketool/pokeparty.h"
#include "field_event.h"
#include "b_tower_scr.h"

extern void FieldEncount_Set(FIELDSYS_WORK * fsys, BATTLE_PARAM * param);
extern void FieldEncount_Change(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event, BATTLE_PARAM * param);
extern BOOL FieldEncount_Check(FIELDSYS_WORK * fsys);
extern void FieldBattle_SetProc(FIELDSYS_WORK * fsys, BATTLE_PARAM * param);

extern void EventCmd_NormalLose(GMEVENT_CONTROL * event);
extern void EventCmd_BattleProc(GMEVENT_CONTROL * event, BATTLE_PARAM * battle_param);
extern void EventCmd_TrainerBattle(GMEVENT_CONTROL * event, int tr_id_0, int tr_id_1, int partner_id,
		int heapID, int * win_flag);
extern void EventCmd_HoneyTreeBattle(GMEVENT_CONTROL * event, int * win_flag);
extern void EventCmd_WildBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level, int * win_flag,BOOL densetsu);
extern void EventCmd_FirstBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level);

extern void EventCmd_CommBattle(GMEVENT_CONTROL * event);
extern void EventCmd_TemotiListBattle(GMEVENT_CONTROL * event,const u8* temotiList, int fightType);
extern void EventCmd_WifiBattle(GMEVENT_CONTROL * event,int targetID, int lvLimit,BOOL bSingle);
extern void EventSet_CommDirectBattle(FIELDSYS_WORK * fsys, const u8 * temotilist, int fightType);
extern void EventSet_CommDirectMixBattle(FIELDSYS_WORK * fsys, const POKEPARTY* party, int fightType);

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：バトルタワーローカル対戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	trainer_id	トレーナー指定データ
 * @param	fight_type	戦闘種別
 * @param	heapID		ヒープID
 * @param	win_flag	戦闘結果を受け取るフラグ
 */
//-----------------------------------------------------------------------------
extern void EventCmd_TowerLocalBattle(GMEVENT_CONTROL * event,BTOWER_SCRWORK* wk, int * win_flag);


//イベントコマンド：ポケパークエンカウント
extern void EventSet_PokeParkBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM * btlprm);

//イベントコマンド：捕獲デモ呼び出し
extern void EventCmd_CaptureDemo(GMEVENT_CONTROL * event);

#ifdef	PM_DEBUG
extern BOOL DebugFieldEncount(FIELDSYS_WORK * fsys);
extern BOOL DebugFieldEncount2vs2(FIELDSYS_WORK * fsys);
extern BOOL DebugFieldTrainerEncount(FIELDSYS_WORK * fsys);
#endif
#endif	/* __FIELD_ENCOUNT_H__ */

