//============================================================================================
/**
 * @file	field_encount.c
 * @brief	フィールドエンカウントチェック＆起動
 * @date	2005.07.28
 * @author	tamada		引き継いだ人が直してね
 *
 * 2005.12.18	エンカウントチェック部分を削除、encount_set.cに移動した
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"

#include "field_encount.h"
#include "eventcmd.h"
#include "encount_effect.h"
#include "encount_set.h"
#include "field_battle.h"

#include "ev_mapchange.h"

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "sway_grass_enc.h"
#include "system/wipe.h"

#include "poketool/tr_tool.h"

#include "mapdata_warp.h"			//WARPDATA_GetRevivalLocation
#include "situation_local.h"		//Situation_Get～
#include "system/brightness.h"
#include "script.h"
#include "scr_tool.h"
#include "mapdefine.h"
#include "..\fielddata\script\common_scr_def.h"		//SCRID_GAME_OVER_RECOVER_PC
#include "sysflag.h"
#include "communication/communication.h"   // ともだち手帳への記録のため
//#include "comm_direct_counter.h"
#include "comm_field_state.h"
#include "b_tower_fld.h"
#include "fld_move_poke.h"
#include "pokepark_sys.h"

#include "battle/trno_def.h"

#include "savedata/tv_work.h"
#include "tv_topic.h"		//TVTOPIC_Entry_Watch_Capture
#include "field/tvtopic_extern.h"
#include "fld_enceff_data.h"
#include "field/b_tower_ev.h"

#include "savedata/record.h"
#include "poketool/poke_number.h"
#include "poketool/status_rcv.h"
#include "syswork.h"

#include "battle/attr_def.h"

//============================================================================================
//============================================================================================
static void AddScoreByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam );
static void WriteFNoteByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static inline int DmyEffNo(void)
{
	return gf_mtRand() % ENCOUNT_NUM;
}

//============================================================================================
//
//
//	イベント擬似コマンド：戦闘
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_BattleProc(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	BATTLE_PARAM * battle_param = FieldEvent_GetSpecialWork(event);
	int *seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		//戦闘プロセス登録
		FieldBattle_SetProc(fsys, battle_param);
		(*seq) ++;
		break;
	case 1:
		//サブプロセス（戦闘）終了待ち
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			break;
		}
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：戦闘呼び出し
 * @param	event			イベント制御ワークへのポインタ
 * @param	battle_param	戦闘用パラメータへのポインタ
 * 
 * 引数として受け取ったBATTLE_PARAMは解放しません。
 * 呼び出し側で管理してください。
 */
//-----------------------------------------------------------------------------
void EventCmd_BattleProc(GMEVENT_CONTROL * event, BATTLE_PARAM * battle_param)
{
	FieldEvent_Call(event, GMEVENT_Sub_BattleProc, battle_param);
}


//============================================================================================
//
//
//	イベントコマンド：ポケモンエンカウント呼び出し
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
typedef struct {
	int * winlose_flag;
	int effect_no;
	int bgm_no;
    int netTargetID;
	BATTLE_PARAM	*battle_param;
}EV_BATTLE_WORK;

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static EV_BATTLE_WORK * EBW_Create(BATTLE_PARAM * btlprm, int effect_no, int bgm_no,
		int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_BATTLE_WORK));
	ebw->winlose_flag = winlose_flag;
	if (winlose_flag != NULL) {
		*winlose_flag = 0;
	}
	ebw->effect_no = effect_no;
	ebw->bgm_no = bgm_no;
	ebw->battle_param = btlprm;
	return ebw;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static void EBW_Delete(EV_BATTLE_WORK * ebw)
{
	//バトルパラメータ破棄
	BattleParam_Delete(ebw->battle_param);

	sys_FreeMemoryEz(ebw);
}
#if 0	//<<20060609 del
//-----------------------------------------------------------------------------
/**
 * @brief	FIGHT_TYPEとトレーナーIDからBGMを決定する
 */
//-----------------------------------------------------------------------------
static u16 GetBGMID(const BATTLE_PARAM * bp)
{
	return Snd_BattleBgmGet(bp->fight_type,bp->trainer_id[CLIENT_NO_ENEMY]); 
}
#endif
//-----------------------------------------------------------------------------
/**
 * @brief
 * @param	ebw			戦闘シーケンスワークへのポインタ
 */
//-----------------------------------------------------------------------------
static BOOL EBW_CheckResult(EV_BATTLE_WORK * ebw)
{
	BOOL win_flag;

	if (ebw->winlose_flag != NULL) {
		*(ebw->winlose_flag) = ebw->battle_param->win_lose_flag;
	}

	win_flag = BattleParam_IsWinResult(ebw->battle_param->win_lose_flag);
	return win_flag;
}

//-----------------------------------------------------------------------------
/**
 * @brief	バトル後のパラメータ反映
 * @param	event		イベント制御ワークへのポインタ
 * @param	ebw			戦闘シーケンスワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void BattleParam_RefrectResult(const BATTLE_PARAM * btlprm, FIELDSYS_WORK * fsys)
{
	if (btlprm->fight_type & FIGHT_TYPE_DEBUG) {
		//デバッグ対戦では手持ちの情報を書き換えない
		return;
	}
	BattleParam_UpdateGameData(btlprm, fsys);
#if 0
	if (BattleParam_IsWinResult(btlprm->win_lose_flag)) {
		//勝利した場合
		BattleParam_UpdateGameData(btlprm, fsys);
	} else {
		//敗北した場合
	}
#endif

}

//-----------------------------------------------------------------------------
/**
 * @brief	通常戦闘イベントシーケンス
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 *
 * エンカウントエフェクト→戦闘→フィールド復帰を行う。
 * ゲームオーバー処理への分岐も入る（予定）
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NormalBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		//ＯＢＪポーズ
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//戦闘結果反映（ずかん、手持ちポケモン状態、etc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		if ( (ebw->battle_param->fight_type == FIGHT_TYPE_1vs1_YASEI)||
			 (ebw->battle_param->fight_type == FIGHT_TYPE_MOVE)||
			 (ebw->battle_param->fight_type == FIGHT_TYPE_2vs2_YASEI) ){			//野生戦
			TVTOPIC_Entry_Watch_Capture(fsys,ebw->battle_param->TVWatchBattleWork,
					ebw->battle_param->win_lose_flag);
		}
		//戦闘終了後の処理
		if (EBW_CheckResult(ebw) == FALSE) {
			//全滅の場合はここで終了させる
			EBW_Delete(ebw);
			return TRUE;
		}

		//連れ歩き戦闘後は手持ちを回復
		if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){
			//連れ歩きなので手持ち回復
			PokeParty_RecoverAll(SaveData_GetTemotiPokemon(fsys->savedata));
		}

		//スコア加算
		AddScoreByBattle(fsys, ebw->battle_param);
		//冒険ノート記入
		WriteFNoteByBattle(fsys, ebw->battle_param);
		
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//ＯＢＪポーズクリア
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void EventCmd_NormalBattle(GMEVENT_CONTROL * event,
		BATTLE_PARAM * btlprm, int effect_no, int bgm_no, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create(btlprm, effect_no, bgm_no, winlose_flag);
	FieldEvent_Call(event, GMEVENT_NormalBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦い結果を登録
 * @param	status  win_lose_flag
 * @retval	なし
 */
//-----------------------------------------------------------------------------

static void wifiFriendWriteBattleResult(int status,FIELDSYS_WORK* fsys)
{
    switch(status & 0x0f){
      case FIGHT_WIN:		///戦闘勝利
      case FIGHT_ENEMY_ESCAPE:		///相手が逃げた
        CommInfoSetBattleResult(fsys->savedata,1);
        break;
      case FIGHT_LOSE:		///戦闘負け
      case FIGHT_ESCAPE:		///逃げた
        CommInfoSetBattleResult(fsys->savedata,-1);
        break;
    }
}

//-----------------------------------------------------------------------------
/**
 * @brief	通信戦闘イベントシーケンス
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CommBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//戦闘終了後の処理
        // ともだち手帳に勝敗を書き込み
        wifiFriendWriteBattleResult(ebw->battle_param->win_lose_flag,fsys);

		//仮想対戦用のゲームデータアップデート処理（ずかんとか）
		BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);
        {
            RECORD* pRecord = SaveData_GetRecord(fsys->savedata);
            RECORD_Score_Add(pRecord, SCORE_ID_COMM_BATTLE_COUNT);
        }
#if 0
		if (EBW_CheckResult(ebw) == FALSE) {
			/* 負けたときの処理 */
		}
#endif

		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//イベントコマンド：フェードイン
//		EventCmd_FieldFadeIn(event);
//		(*seq) ++;
//		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	WIFI戦闘イベントシーケンス    k.ohno作成
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_WiFiBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:

		Snd_DataSetByScene( SND_SCENE_BATTLE, ebw->bgm_no, 1 );	//バトル曲再生
        
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;
	case 1:
        {
            // ともだち手帳に勝敗を書き込み
            wifiFriendWriteBattleResult(ebw->battle_param->win_lose_flag, fsys);

            //仮想対戦用のゲームデータアップデート処理（ずかんとか）
			BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);

        }
        {
            RECORD* pRecord = SaveData_GetRecord(fsys->savedata);
            RECORD_Score_Add(pRecord, SCORE_ID_COMM_BATTLE_COUNT);
        }
        
#if 0	//通信対戦なので敗北時の分岐はいらないはず	2006.04.24 tamada
		//戦闘終了後の処理
		if (EBW_CheckResult(ebw) == FALSE) {

			//全滅の場合はここで終了させる
			EBW_Delete(ebw);
			return TRUE;
		}
		BattleParam_RefrectResult(ebw->battle_param, fsys);
#endif

		(*seq) ++;
		break;
	case 2:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	バトルタワーローカル戦闘イベントシーケンス by iwasawa
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 *
 * エンカウントエフェクト→バトルタワー戦闘→フィールド復帰を行う。
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_TowerLocalBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//仮想対戦用のゲームデータアップデート処理（ずかんとか）
		BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);
		//タワー用対戦結果アップデート処理
		BtlTower_BattleRecordUpdate(fsys,&(ebw->battle_param->btr));

		//戦闘終了後の処理
		if (EBW_CheckResult(ebw) == FALSE) {
			//敗戦処理
		}else{
			
//			UpdateBattleResult(event, ebw);		
		}

		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	バトルタワー　ローカルバトルイベント登録
 */
static void EventCmd_TowerLocalBattleCall(GMEVENT_CONTROL * event,
		BATTLE_PARAM * param, int effect_no, int bgm_no, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create(param, effect_no, bgm_no, winlose_flag);
	FieldEvent_Call(event, GMEVENT_TowerLocalBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：バトルタワーローカル対戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	trainer_id	トレーナー指定データ
 * @param	fight_type	戦闘種別
 * @param	heapID		ヒープID
 * @param	winlose_flag	戦闘結果を受け取るフラグ
 */
//-----------------------------------------------------------------------------
void EventCmd_TowerLocalBattle(GMEVENT_CONTROL * event,BTOWER_SCRWORK* wk, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *param;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//バトルデータ初期化
	param = BtlTower_CreateBattleParam(wk,fsys);
	
	//呼び出し＆イベント登録
	EventCmd_TowerLocalBattleCall( event,param,
								   FLD_EncEffSpDataEffectNoPackGet( param ),
								   FLD_EncEffSpDataBgmNoPackGet( param ),
								   winlose_flag);
}





















//============================================================================================
//
//
//				野生エンカウント
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	int effect_no;
	int bgm_no;
	int *winlose_flag;
	BATTLE_PARAM	*battle_param;
}EV_WILD_BATTLE_WORK;


static BOOL GMEVENT_NormalWildBattle(GMEVENT_CONTROL * event);
static BOOL GMEVENT_SafariBattle(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static EV_WILD_BATTLE_WORK* EWBW_Create( BATTLE_PARAM * btlprm, int effect_no, int bgm_no,
		int * winlose_flag )
{
	EV_WILD_BATTLE_WORK	* ewbw;
	ewbw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_WILD_BATTLE_WORK));
	ewbw->winlose_flag = winlose_flag;
	if (winlose_flag != NULL) {
		*winlose_flag = 0;
	}
	ewbw->effect_no = effect_no;
	ewbw->bgm_no = bgm_no;
	ewbw->battle_param = btlprm;
	ewbw->seq = 0;
	return ewbw;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static void EWBW_Delete(EV_WILD_BATTLE_WORK * ewbw)
{
	//バトルパラメータ破棄
	BattleParam_Delete(ewbw->battle_param);

	sys_FreeMemoryEz(ewbw);
}

//-----------------------------------------------------------------------------
/**
 * フィールドエンカウントイベントセット
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	ioBattleParam	バトルパラメータ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FieldEncount_Set(FIELDSYS_WORK * fsys, BATTLE_PARAM *ioBattleParam)
{

	if ( SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		EV_BATTLE_WORK * ebw;
		ebw = EBW_Create(	ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Set(fsys, GMEVENT_SafariBattle,ebw);
	}else{
		EV_WILD_BATTLE_WORK *ewbw;
		
		ewbw = EWBW_Create( ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Set(fsys, GMEVENT_NormalWildBattle,ewbw);
	}
}

//-----------------------------------------------------------------------------
/**
 * フィールドエンカウントイベントチェンジ
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	ioBattleParam	バトルパラメータ
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FieldEncount_Change(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event, BATTLE_PARAM *ioBattleParam)
{

	if ( SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		EV_BATTLE_WORK * ebw;
		ebw = EBW_Create(	ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Change(event, GMEVENT_SafariBattle,ebw);
	}else{
		EV_WILD_BATTLE_WORK *ewbw;
		ewbw = EWBW_Create( ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Change(event, GMEVENT_NormalWildBattle,ewbw);
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	通常野生戦イベントシーケンス
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 *
 * サブイベントとして、通常戦闘イベントシーケンスをコールする
 * 
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NormalWildBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_WILD_BATTLE_WORK *ewbw;
	fsys = FieldEvent_GetFieldSysWork(event);
	ewbw = FieldEvent_GetSpecialWork(event);

	switch (ewbw->seq) {
	case 0:
		//ＯＢＪポーズ
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//野生戦戦カウントアップ
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event,ewbw->effect_no, ewbw->bgm_no);
		ewbw->seq++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		ewbw->seq++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ewbw->battle_param);
		ewbw->seq++;
		break;

	case 3:
		//戦闘結果反映（ずかん、手持ちポケモン状態、etc...)
		BattleParam_RefrectResult(ewbw->battle_param, fsys);
		TVTOPIC_Entry_Watch_Capture(fsys,ewbw->battle_param->TVWatchBattleWork,
				ewbw->battle_param->win_lose_flag);
		//戦闘終了後の処理
		if (BattleParam_IsWinResult(ewbw->battle_param->win_lose_flag) == FALSE) {
			//全滅の場合はここで終了させる
			EWBW_Delete(ewbw);
			//揺れ草リセット
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
			FieldEvent_Change(event, GMEVENT_NormalGameOver, NULL);
			return FALSE;
		}

		//連れ歩き戦闘後は手持ちを回復
		if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){
			//連れ歩きなので手持ち回復
			PokeParty_RecoverAll(SaveData_GetTemotiPokemon(fsys->savedata));
		}

		//スコア加算
		AddScoreByBattle(fsys, ewbw->battle_param);
		//冒険ノート記入
		WriteFNoteByBattle(fsys, ewbw->battle_param);
		
		//戦闘終了後揺れ草継続チェック
		if (SwayGrass_CheckValid( fsys->SwayGrass )){
			if (SwayGrass_IsSwayEncRetern(fsys->SwayGrass)){	//揺れ草エンカウント復帰
				if ( ( !(ewbw->battle_param->win_lose_flag==FIGHT_WIN) ) &&
						( !(ewbw->battle_param->win_lose_flag==FIGHT_POKE_GET) ) ){		//逃げた
					//揺れ草リセット
					SwayGrass_InitSwayGrass(fsys->SwayGrass);
				}
			}else{//通常先頭復帰もしくは、揺れ草打ち止め復帰のとき
				//揺れ草リセット
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
			}
		}
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		ewbw->seq++;
		break;
	case 4:
		//移動ポケモン処理
		FLD_MP_SetAfferBattle(fsys, ewbw->battle_param);
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		ewbw->seq++;
		break;
	case 5:
		if (SwayGrass_CheckValid( fsys->SwayGrass )){	//揺れ草エンカウント復帰
			SwayGrass_SetChain(	fsys, ewbw->battle_param->win_lose_flag, fsys->SwayGrass);
			//草セット
			SwayGrass_SetSwayGrassAnime(fsys, fsys->SwayGrass);
		}
		ewbw->seq++;
		break;
	case 6:
		if (SwayGrass_CheckSwayGrassAnimeEnd(fsys->SwayGrass)){
			//ＯＢＪポーズクリア
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			EWBW_Delete(ewbw);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

#include "../fielddata/script/safari_def.h"
//-----------------------------------------------------------------------------
/**
 * @brief	サファリイベントシーケンス
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 *
 * サブイベントとして、サファリイベントシーケンスをコールする
 * 
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_SafariBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	u16 *safari_ball;

	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);
	safari_ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));

    switch (*seq) {
	case 0:
		//ＯＢＪポーズ
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//野生戦戦カウントアップ
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//戦闘結果反映（ずかん、手持ちポケモン状態、etc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		if (ebw->battle_param->win_lose_flag == FIGHT_POKE_GET) {
			TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
			POKEMON_PARAM * pp = PokeParty_GetMemberPointer(
					ebw->battle_param->poke_party[CLIENT_NO_ENEMY], 0);
			TVTOPIC_SafariTemp_Set(tvwk, pp);
		}

		//連れ歩きはない
		
		//スコア加算
		AddScoreByBattle(fsys, ebw->battle_param);
		
		//戦闘終了後の処理
		if ((*safari_ball) == 0 && ebw->battle_param->win_lose_flag != FIGHT_POKE_GET){
			//サファリボールがなくなったらサファリゲートへ戻す
			LOCATION_WORK *next;
			next = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
			EventCmd_MapChangeByLocation(event, next);
			//サファリボール無くなった
///			OS_Printf("サファリボールがなくなりました\n");
		}
		//冒険ノート記述
		WriteFNoteByBattle( fsys, ebw->battle_param );

		(*seq) ++;
		break;

	case 4:
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//ＯＢＪポーズクリア
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		if ((*safari_ball) == 0){
			if (ebw->battle_param->win_lose_flag == FIGHT_POKE_GET) {
				//フィールドでアナウンスしてからゲートへ移動、終了
				EventCall_Script(event, SCRID_SAFARI_ANNOUNCE_BALL, NULL, NULL);
			} else {
				//戦闘画面内でアナウンス済みなので直接ゲートへ移動、終了
				EventCall_Script(event, SCRID_SAFARI_END_GATE, NULL, NULL);
			}
		} else {
			BOX_DATA * box = SaveData_GetBoxData(fsys->savedata);
			POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
			if (BOXDAT_GetEmptyTrayNumber(box) == BOXDAT_TRAYNUM_ERROR
					&& PokeParty_GetPokeCount(party) == 6) {
				EventCall_Script(event, SCRID_SAFARI_ANNOUNCE_BOX_FULL, NULL, NULL);
			}
		}
		(*seq) ++;
		break;
	case 7:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//============================================================================================
//
//
//				蜜塗りエンカウント
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：蜜塗りエンカウント戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	winlose_flag	戦闘結果を受け取るフラグ
 */
//-----------------------------------------------------------------------------
void EventCmd_HoneyTreeBattle(GMEVENT_CONTROL * event, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//揺れ草リセット
	SwayGrass_InitSwayGrass(fsys->SwayGrass);
	
	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->bg_id = BG_ID_BASIC;		//基本背景指定
	btlprm->ground_id = GROUND_ID_GRAVEL;	//基本地面指定
	//蜜塗りエンカウントデータをセット
	SetHoneyTreeEncountData(fsys, btlprm);
	
	//野生戦戦カウントアップ
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);

	EventCmd_NormalBattle( event, btlprm,
						   FLD_EncEffSpDataEffectNoPackGet( btlprm ),
						   FLD_EncEffSpDataBgmNoPackGet( btlprm ),
						   winlose_flag);
}


//============================================================================================
//
//
//				ポケモンナンバーとレベルを指定して野生戦(スクリプトで使用)
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：ポケモンナンバーとレベルを指定して野生戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	monsno		ポケモンナンバー
 * @param	level		レベル
 * @param	winlose_flag	戦闘結果を受け取るフラグ
 * @param	densetsu		伝説ポケモンエンカウントかどうかのフラグ
 *
 * ＊densetsuフラグにTRUEを渡すとエンカウントメッセージが
 * 「●●が飛び出した」ではなく「●●が現れた」になります
 */
//-----------------------------------------------------------------------------
void EventCmd_WildBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level, int * winlose_flag,BOOL densetsu)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//揺れ草リセット
	SwayGrass_InitSwayGrass(fsys->SwayGrass);

	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);

	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	//エンカウントデータをセット
	SetWildEncountData(fsys, monsno, level, btlprm);

	/*
	//　battle_status_flag
	//	にセットするようにする！
	*/
	if(densetsu){
		//伝説ポケモンエンカウトならフラグを立ててエンカウントメッセージを変える
		btlprm->battle_status_flag |= BATTLE_STATUS_FLAG_DENSETSU_BATTLE;
	}
	/*
		持たせるアイテムの指定が必要かも？
	*/

	//野生戦戦カウントアップ
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
	
	EventCmd_NormalBattle(event, btlprm, FLD_EncEffSpDataEffectNoPackGet( btlprm ), FLD_EncEffSpDataBgmNoPackGet( btlprm ), winlose_flag);
}

//============================================================================================
//============================================================================================
#include "../fielddata/script/d10r0101_def.h"		//SCRID_D10R0101_FINISH
//-----------------------------------------------------------------------------
/**
 * @brief		イベント：ポケパーク戦闘
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_PokeParkBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;

	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		//ＯＢＪポーズ
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//野生戦戦カウントアップ
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//戦闘結果反映（ずかん、手持ちポケモン状態、etc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		//ポケパーク用の戦闘結果反映
		PokeParkSys_ReflectBattleResult(fsys, ebw->battle_param);
		
		//連れ歩きはない
		
		//スコア加算
		AddScoreByBattle(fsys, ebw->battle_param);
		//戦闘終了後の処理
		(*seq) ++;
		break;

	case 4:
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//ＯＢＪポーズクリア
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		EBW_Delete(ebw);
		if (PokeParkSys_GetBallCount(fsys) == 0) {
			EventChange_Script(event, SCRID_D10R0101_FINISH, NULL);
			return FALSE;
		} else {
			return TRUE;
		}
		break;
	}
	return FALSE;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void EventSet_PokeParkBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM * btlprm)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create( btlprm,
				      FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet(btlprm),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_PokeParkBattle, ebw);
}


//============================================================================================
//
//
//						最初のイベント戦(スクリプトで使用)
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：最初のイベント戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	monsno		ポケモンナンバー
 * @param	level		レベル
 */
//-----------------------------------------------------------------------------
void EventCmd_FirstBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level)
{
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);

	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	//エンカウントデータをセット
	SetWildEncountData(fsys, monsno, level, btlprm);

	//戦闘内分岐用フラグ
	btlprm->battle_status_flag = BATTLE_STATUS_FLAG_FIRST_BATTLE;

	/*
		持たせるアイテムの指定が必要かも？
	*/

	//野生戦戦カウントアップ
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);

	EventCmd_NormalBattle( event, btlprm,
						   FLD_EncEffSpDataEffectNoPackGet( btlprm ),
						   FLD_EncEffSpDataBgmNoPackGet( btlprm ),
						   NULL);
}

//============================================================================================
//
//
//			捕獲デモ
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント：捕獲デモ
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CaptureDemo(GMEVENT_CONTROL * event)
{
	EV_BATTLE_WORK * ebw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		//ＯＢＪポーズ
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		// イベントコマンド：エンカウントエフェクト呼び出し
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//イベントコマンド：戦闘プロセス
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//戦闘結果反映（ずかん、手持ちポケモン状態、etc...)
		//なにも反映しない。
		(*seq) ++;
		break;

	case 4:
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//ＯＢＪポーズクリア
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//イベントコマンド：フェードイン
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	サブイベント呼び出し：捕獲デモ
 * @param	fsys			フィールドシステムポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_CaptureDemo(GMEVENT_CONTROL * event)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM * btlprm;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	btlprm = BattleParam_CreateForGetDemo(HEAPID_WORLD, fsys);
	ebw = EBW_Create( btlprm,
				      FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet(btlprm),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CaptureDemo, ebw);
}

//============================================================================================
//
//
//				トレーナー対戦
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：トレーナー対戦
 * @param	event		イベント制御ワークへのポインタ
 * @param	trainer_id	トレーナー指定データ
 * @param	fight_type	戦闘種別
 * @param	heapID		ヒープID
 * @param	winlose_flag	戦闘結果を受け取るフラグ
 */
//-----------------------------------------------------------------------------
void EventCmd_TrainerBattle(GMEVENT_CONTROL * event, int tr_id_0, int tr_id_1, int partner_id,
		 int heapID, int * winlose_flag)
{
	u32 fight_type;
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	if( (tr_id_1 != 0) && (tr_id_0 != tr_id_1) ){
		if (partner_id == 0) {
			fight_type = FIGHT_TYPE_TAG_BATTLE;
		} else {
		//連れ歩き中なら、必ずAIマルチ
			fight_type = FIGHT_TYPE_AI_MULTI;
		}

	//ダブル
	}else if( tr_id_0 == tr_id_1 ){
		fight_type = FIGHT_TYPE_2vs2_TRAINER;

	}else{
		fight_type = FIGHT_TYPE_TRAINER;
	}
	//揺れ草リセット
	SwayGrass_InitSwayGrass(fsys->SwayGrass);

	/* トレーナー戦なので野生戦のパラメータで色々上書き */

	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_WORLD, fight_type);

	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->trainer_id[CLIENT_NO_ENEMY] = tr_id_0;
	btlprm->trainer_id[CLIENT_NO_ENEMY2] = tr_id_1;
	btlprm->trainer_id[CLIENT_NO_MINE2] = partner_id;

	//トレーナーデータ生成
	TT_EncountTrainerDataMake( btlprm, fsys->savedata, heapID );

	//トレーナー戦カウントアップ
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_TRAINER);

	EventCmd_NormalBattle(event, btlprm, FLD_EncEffSpDataEffectNoPackGet( btlprm ), FLD_EncEffSpDataBgmNoPackGet( btlprm ), winlose_flag);
}

//============================================================================================
//
//
//				通信対戦
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	通信対戦イベントセット
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_CommBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化

    btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_SIO);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦う手持ちの配列を持った対戦イベントセット
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_TemotiListBattle(GMEVENT_CONTROL * event,const u8* temotiList, int fightType)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);
	//手持ちポケモンなどセット
	BattleParam_SetTemotiListParamGameData(btlprm, fsys, temotiList);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	WIFI通信対戦イベントセット
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_WifiBattle(GMEVENT_CONTROL * event,int targetID, int lvLimit,BOOL bSingle)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化
    if(bSingle){
        btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_SIO);
    }
    else{
        btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_SIO);
    }
	//手持ちポケモンなどセット
	BattleParam_SetParamByWiFiGameData(btlprm, fsys, lvLimit);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
    ebw->netTargetID = targetID;
	FieldEvent_Call(event, GMEVENT_WiFiBattle, ebw);
}


//-----------------------------------------------------------------------------
/**
 * @brief	通信対戦部屋での対戦イベント
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CommDirectBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
		(*seq) ++;
		break;
	case 1:
		CommFieldStateEnterBattleRoom( fsys );
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	通信対戦部屋での対戦イベント起動
 * @param	fsys
 * @param	temotilist
 * @param	fightType
 */
//-----------------------------------------------------------------------------
void EventSet_CommDirectBattle(FIELDSYS_WORK * fsys, const u8 * temotiList, int fightType)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);
	//手持ちポケモンなどセット
	BattleParam_SetTemotiListParamGameData(btlprm, fsys, temotiList);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_CommDirectBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	通信対戦部屋での対戦イベント起動（任意のPOKEPARTYをセットできる）
 *
 * @param	fsys
 * @param	temotilist
 * @param	fightType
 */
//-----------------------------------------------------------------------------
void EventSet_CommDirectMixBattle(FIELDSYS_WORK * fsys, const POKEPARTY* party, int fightType)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);

	//手持ちポケモンなどセット
	BattleParam_SetCommBattle( btlprm, fsys, party, NULL );

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_CommDirectBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * 戦闘スコア加算(タワー・通信未対応)
 * 
 * @param	fsys			フィールドシステムポインタ
 * @param	inBattleParam	バトルパラム
 * 
 * @return	none
 * 
 */
//-----------------------------------------------------------------------------
static void AddScoreByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam )
{
	POKEMON_PARAM * pp;
	u32 fight_type = inBattleParam->fight_type;
	int win_lose_flg = inBattleParam->win_lose_flag;
	
	if (fight_type&FIGHT_TYPE_SIO){
		return;
	}

	if (fight_type&FIGHT_TYPE_TOWER){
		return;
	}

	if ( (fight_type == FIGHT_TYPE_1vs1_YASEI)||
		 (fight_type == FIGHT_TYPE_MOVE)||
		 (fight_type == FIGHT_TYPE_2vs2_YASEI) ){			//野生戦
		if (win_lose_flg == FIGHT_WIN){	//勝ったとき
			//スコア加算：野生戦勝利
			RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_WILD_BATTLE_WIN );
		}else if(win_lose_flg == FIGHT_POKE_GET){		//捕まえたとき
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
			
			//シンオウ図鑑ポケモンか？
			if ( PMNumber_GetPokeNumber( PM_NUMBER_SHINOU, PokeParaGet(pp,ID_PARA_monsno,0) ) ){
				//スコア加算：シンオウ図鑑ポケモンゲット
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_SINOU );
			}else{
				//スコア加算：シンオウ図鑑外ポケモンゲット
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_WORLD );
			}
		}
	}else if ( (fight_type&FIGHT_TYPE_TRAINER)||
			   (fight_type&FIGHT_TYPE_TAG) ){			//トレーナー戦
		//勝ったら加算
		if (win_lose_flg == FIGHT_WIN){
			//スコア加算：トレーナー戦勝利
			RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_TRAINER_BATTLE_WIN );
		}
	}else if ( (fight_type&FIGHT_TYPE_SAFARI)||
			   (fight_type&FIGHT_TYPE_POKE_PARK) ){	//サファリ・ポケパーク
		//捕まえたら加算
		if (win_lose_flg == FIGHT_POKE_GET){
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
			//シンオウ図鑑ポケモンか？
			if ( PMNumber_GetPokeNumber( PM_NUMBER_SHINOU, PokeParaGet(pp,ID_PARA_monsno,0) ) ){
				//スコア加算：シンオウ図鑑ポケモンゲット
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_SINOU );
			}else{
				//スコア加算：シンオウ図鑑外ポケモンゲット
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_WORLD );
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * 戦闘後冒険ノート記入(タワー・通信・ポケパーク未対応)
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inBattleParam	バトルパラム
 * 
 * @return	none
 * 
 */
//-----------------------------------------------------------------------------
static void WriteFNoteByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam )
{
	POKEMON_PARAM * pp;
	u32 fight_type = inBattleParam->fight_type;
	int win_lose_flg = inBattleParam->win_lose_flag;
	
	if (fight_type&FIGHT_TYPE_SIO){
		return;
	}

	if (fight_type&FIGHT_TYPE_TOWER){
		return;
	}

	if ( fight_type&FIGHT_TYPE_POKE_PARK ){
		return;
	}

	if ( (fight_type == FIGHT_TYPE_1vs1_YASEI)||
		 (fight_type == FIGHT_TYPE_MOVE)||
		 (fight_type == FIGHT_TYPE_2vs2_YASEI)||
		 (fight_type == FIGHT_TYPE_SAFARI)){			//野生戦
		FNOTE_WK_POKE *wk;
		if (win_lose_flg == FIGHT_WIN){	//勝ったとき
			//カウントアップ
			fsys->encount.WinPokeCount++;//値の振り切れは加味してないです
			//5匹以上でノート記入
			if (fsys->encount.WinPokeCount >= 5){
				pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
				wk = FNOTE_PokemonDownDataMake(
						SaveData_GetPlayTime(fsys->savedata),
						PokeParaGet(pp,ID_PARA_monsno,0),
						PokeParaGet(pp,ID_PARA_sex,0),
						inBattleParam->time_zone, HEAPID_WORLD );
/*
				wk = FNOTE_PokemonDownDataMake( PokeParaGet(pp,ID_PARA_monsno,0),
									    		PokeParaGet(pp,ID_PARA_sex,0),
											    inBattleParam->time_zone, HEAPID_WORLD );
*/
				FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_POKEMON );
			}
		}else if(win_lose_flg == FIGHT_POKE_GET){		//捕まえたとき
			int client;
			//捕まえたポケモンの位置を取得
			client = inBattleParam->get_pokemon_client;
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[client], 0);
			//ノート記入
			wk = FNOTE_PokemonGetDataMake(
					SaveData_GetPlayTime(fsys->savedata),
					PokeParaGet(pp,ID_PARA_monsno,0),
					PokeParaGet(pp,ID_PARA_sex,0),
					inBattleParam->time_zone, HEAPID_WORLD );
//
/*
			wk = FNOTE_PokemonGetDataMake( PokeParaGet(pp,ID_PARA_monsno,0),
				    					   PokeParaGet(pp,ID_PARA_sex,0),
										   inBattleParam->time_zone, HEAPID_WORLD );
*/
			FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_POKEMON );
		}
	}else if ( (fight_type&FIGHT_TYPE_TRAINER)||
			   (fight_type&FIGHT_TYPE_TAG) ){			//トレーナー戦
		if (win_lose_flg == FIGHT_WIN){
			//ノート記入
			FNOTE_DataMakeSaveTrainer(
				fsys->fnote,
				fsys->location->zone_id,
				inBattleParam->trainer_id[CLIENT_NO_ENEMY],
				HEAPID_WORLD );
/*
			FNOTE_WK_TRAINER *wk;
			wk = FNOTE_TrainerDataMake( fsys->location->zone_id,
										inBattleParam->trainer_id[CLIENT_NO_ENEMY],
										HEAPID_WORLD );
			FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_TRAINER );
*/
		}
	}

}

#ifdef PM_DEBUG

//============================================================================================
//
//
//			デバッグ用
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 *	デバッグ用
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldEncount(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_EVENT, FIGHT_TYPE_DEBUG|FIGHT_TYPE_1vs1);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);
	
	//ここに地上エンカウントデータをセット
	DebugSetEncountData( NULL, GROUND_ENCOUNT, btlprm );
	
	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}
//-----------------------------------------------------------------------------
/**
 *	デバッグ用
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldEncount2vs2(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_EVENT, FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_DEBUG);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->trainer_id[CLIENT_NO_ENEMY]=gf_rand()%16+1;
	//トレーナーデータ生成
	TT_EncountTrainerDataMake(btlprm,fsys->savedata,HEAPID_WORLD);

	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}
//-----------------------------------------------------------------------------
/**
 *	デバッグ用
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldTrainerEncount(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//バトルパラメータのアロケーションとポケモンパーティの初期化
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_TRAINER|FIGHT_TYPE_DEBUG);
	//手持ちポケモンなどセット
	BattleParam_SetParamByGameData(btlprm, fsys);
	
	btlprm->trainer_id[CLIENT_NO_ENEMY]=gf_rand()%247+1;
	//トレーナーデータ生成
	TT_EncountTrainerDataMake(btlprm,fsys->savedata,HEAPID_WORLD);
	
	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}

#endif	//PM_DEBUG

