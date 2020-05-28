//============================================================================================
/**
 * @file	fld_flg_init.c
 * @brief	フィールド移動でのフラグオフ・値クリアとか（気付いたやつだけ入れときます）
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================
#include "common.h"
#include "savedata/savedata.h"
#include "savedata/encount.h"
#include "savedata/vidro_type.h"
#include "sysflag.h"
#include "fieldsys.h"
#include "mapdata_warp.h"
#include "move_pokemon.h"
#include "zonedata.h"
#include "situation_local.h"
#include "sysflag.h"
#include "syswork.h"

#include "fld_flg_init.h"


static BOOL FldFlgInit_FnoteTownDataSet( FIELDSYS_WORK * fsys );
static BOOL FldFlgInit_FnoteMapChgDataSet( FIELDSYS_WORK * fsys );

//----------------------------------------------------------------------------
/**
 * @brief	望遠鏡モードのセット
 * @param	fsys		フィールドシステムポインタ
 * @param	flag		TRUEのとき、望遠鏡モードにセット
 *
 * あるマップから他のマップを見せたいだけの場合のときに、
 * 各種フラグの更新をフックする必要がある。その場合は、
 * イベント開始時にこの関数を使って望遠鏡モードに移行し、
 * マップ遷移が終わったら望遠鏡モードを終了する。
 */
//----------------------------------------------------------------------------
void FldFlg_SetScopeMode(FIELDSYS_WORK * fsys, BOOL flag)
{
	fsys->scope_mode_flag = flag;
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：歩いてゾーンをまたいだとき（必ず呼ばれる）
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Walk(FIELDSYS_WORK * fsys)
{
	//--冒険ノート用更新処理
	FldFlgInit_FnoteTownDataSet( fsys );

	//かいりきフラグのクリア
	SysFlag_KairikiReset( SaveData_GetEventWork(fsys->savedata) );
	//到着フラグのセット
	ARRIVEDATA_SetArriveFlag(fsys, fsys->location->zone_id);
	//ビードロクリア
	EncDataSave_SetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata), VIDRO_NONE );
	//エンカウント歩数クリア
	fsys->encount.walk_count = 0;
	//サファリにいないときの処理
	if ( !SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		//移動ポケモン処理(サファリ内ゾーン切り替えのときは履歴を積まない)
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		//ゾーン履歴を更新
		//歩いて移動した場合は移動ポケモンの移動処理
		MP_MovePokemonNeighboring(data);//移動ポケモン隣接移動
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：ワイプのはいるマップジャンプのとき(必ず呼ばれる)
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_MapJump(FIELDSYS_WORK * fsys)
{
	if (fsys->scope_mode_flag == TRUE) {
		//望遠鏡モードの場合は更新処理を行わない
		return;
	}

	//--冒険ノート用更新処理
	if( FldFlgInit_FnoteTownDataSet( fsys ) == FALSE ){
		FldFlgInit_FnoteMapChgDataSet( fsys );
	}

	//サイクリングロードモードのクリア
	SysFlag_CyclingRoadReset( SaveData_GetEventWork(fsys->savedata) );
	//かいりきフラグのクリア
	SysFlag_KairikiReset( SaveData_GetEventWork(fsys->savedata) );
	//到着フラグのセット
	ARRIVEDATA_SetArriveFlag(fsys, fsys->location->zone_id);
	//ビードロクリア
	EncDataSave_SetVidro( EncDataSave_GetSaveDataPtr(fsys->savedata), VIDRO_NONE );
	//エンカウント歩数クリア
	fsys->encount.walk_count = 0;
	//移動ポケモン処理
	{
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		//ゾーン履歴を更新
	}
	//ダンジョンでない場合、フラッシュ状態フラグと霧払い状態フラグをクリア
	if (!ZoneData_IsDungeon(fsys->location->zone_id)) {
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		SysFlag_FlashReset(ev);
		SysFlag_KiribaraiReset(ev);
	}
	//自機状態の設定
	{
		PLAYER_SAVE_DATA * jikisave = Situation_GetPlayerSaveData(SaveData_GetSituation(fsys->savedata));
		if (jikisave->form == HERO_FORM_CYCLE
				&& ZoneData_GetEnableBicycleFlag(fsys->location->zone_id) == FALSE) {
			jikisave->form = HERO_FORM_NORMAL;
		} else if (jikisave->form == HERO_FORM_SWIM) {
			jikisave->form = HERO_FORM_NORMAL;
		}
	}

	//--タウンマップ足跡
	if (ZoneData_IsSinouField(fsys->location->zone_id)) {
		//フィールド以外では足跡の更新はない！
		TOWN_MAP_FOOTMARK * footmark;
		footmark = Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
		TMFootMark_SetNoDir(footmark, fsys->location->grid_x, fsys->location->grid_z);
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：空を飛ぶを使ったとき固有で行うもの
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_FlySky(FIELDSYS_WORK * fsys)
{
	//サファリフラグクリア
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
	//移動ポケモン全部ジャンプ
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：テレポートを使ったとき固有で行うもの
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Teleport(FIELDSYS_WORK * fsys)
{
	//サファリフラグクリア
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
	//移動ポケモン全部ジャンプ
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：あなぬけのひも・あなをほるを使ったとき固有で行うもの
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Escape(FIELDSYS_WORK * fsys)
{
	//サファリフラグクリア
	SysFlag_SafariReset( SaveData_GetEventWork(fsys->savedata) );
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：ゲームオーバー
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_GameOver(FIELDSYS_WORK * fsys)
{
	EVENTWORK* ev = SaveData_GetEventWork( fsys->savedata );

	//連れ歩きフラグ、トレーナーID格納ワークのクリア
	SysFlag_PairReset( ev );
	SysWork_PairTrainerIDSet( ev, 0 );
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：コンティニュー
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_Continue(FIELDSYS_WORK * fsys)
{
	//移動ポケモン全部ジャンプ
	MP_JumpMovePokemonAll(EncDataSave_GetSaveDataPtr(fsys->savedata));
}

//----------------------------------------------------------------------------
/**
 * @brief	フラグ初期化：地下へいく
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void FldFlgInit_UnderGround(FIELDSYS_WORK * fsys)
{
	;
}


//----------------------------------------------------------------------------
/**
 * @brief	冒険ノート作成：町に到着
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval	"TURE = 作成された"
 * @retval	"FALSE = 作成されなかった"
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldFlgInit_FnoteTownDataSet( FIELDSYS_WORK * fsys )
{
	int warp_id = WARPDATA_SearchByFieldID( fsys->location->zone_id );

	if( warp_id != 0 && ARRIVEDATA_GetArriveFlag( fsys, warp_id ) == FALSE ){
		FNOTE_DataMakeSaveCity( fsys->fnote, fsys->location->zone_id, HEAPID_EVENT );
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * @brief	冒険ノート作成：マップ切り替え
 *
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval	"TURE = 作成された"
 * @retval	"FALSE = 作成されなかった"
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldFlgInit_FnoteMapChgDataSet( FIELDSYS_WORK * fsys )
{
	LOCATION_WORK * before = Situation_GetBeforeLocation( SaveData_GetSituation(fsys->savedata) );

	if( before->zone_id != fsys->location->zone_id ){
		FNOTE_DataMakeSaveMapChg(
			SaveData_GetMyStatus( fsys->savedata ),
			fsys->fnote, fsys->location->zone_id, before->zone_id, HEAPID_EVENT );
		return TRUE;
	}
	return FALSE;
}
