//============================================================================================
/**
 * @file	ev_mapchange.c
 * @brief	フィールドマップ切替のイベントとその生成チェック
 * @date	2005.08.01
 * @author	tamada / saito
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "field_event.h"

#include "fieldmap.h"
#include "field/location.h"

#include "ev_mapchange.h"

#include "worldmap.h"

#include "zonedata.h"
#include "mapdefine.h"
#include "eventdata.h"		//ゾーン毎のイベントデータ参照のため

#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "system/brightness.h"
#include "system/pm_overlay.h"  // 地下接続のため
#include "comm_player.h"  // 地下接続のため
#include "communication/communication.h"
#include "../fielddata/script/common_scr_def.h"		//SCRID_REPORT

#include "map_tool.h"

#include "field_3d_anime_ev.h"

#include "system/wipe.h"
#include "field_cutin.h"
#include "field_ananuke.h"
#include "effect_warppoint.h"

//↓地下
#include "effect_uground.h"
#include "comm_field_state.h"  // 地下通信用
#include "underground/ug_manager.h"  // 地下用
//
#include "script.h"

#include "savedata/mystatus.h"	//MyStatus_GetMySex
#include "savedata/gimmickwork.h"
#include "savedata/undergrounddata.h"
#include "field/situation_local.h"	//Situation_GetTMFootMark
#include "townmap_footmark.h"		//TMFootMark_SetNoDir
#include "mapdata_warp.h"			//WARPDATA_SearchByRoomID
#include "field_subscreen.h"
#include "report.h"
#include "mapdata_weather.h"		//WeatherData_Get
#include "weather_sys.h"
#include "savedata/fnote_mem.h"		//FNOTE_DATA
#include "itemtool/itemsym.h"
#include "savedata/savedata.h"
#include "sysflag.h"
#include "syswork.h"
#include "ev_time.h"				//EVTIME_Update

#include "savedata/encount.h"
#include "fieldmap_mem.h"			//FIELD_HEIGHT_DATA_SIZE

#include "fld_flg_init.h"
#include "place_name.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_connect.h"

#include "system/window.h"
#include "system/bmp_menu.h"
#include "talk_msg.h"
#include "fld_bmp.h"


FS_EXTERN_OVERLAY(ol_underground);

static BOOL GMEVENT_MapChange(GMEVENT_CONTROL * event);
static BOOL GMEVENT_FirstMapIn(GMEVENT_CONTROL * event);
static BOOL GMEVENT_FieldChange_FadeIn(GMEVENT_CONTROL * event);

static void MapChg_SetNewLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next);
static void MapChg_SetupMapTools(FIELDSYS_WORK * fsys);
static void MapChg_RemoveMapTools(FIELDSYS_WORK * fsys);
static void MapChg_FieldOBJ_Create(FIELDSYS_WORK * fsys);
static void MapChg_FieldOBJ_Delete(FIELDSYS_WORK * fsys);

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベント用制御ワーク
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<シーケンス保持ワーク
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
	FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
}EVENT_MAPCHG_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief	マップシステムの初期化パラメータ
 */
//-----------------------------------------------------------------------------
static const MAP_MODE_DATA MapModeData[] = {
	///MAP_MODE_GROUND		通常フィールド
	{
		FIELD_SUBSCRN_POKETCH,		//サブ画面：ポケッチ
		DIV_MAP_MODE_GROUND,		//マップ分割転送システム指定：通常
		MAP_TOOL_MODE_GROUND,		//マップツール指定：通常
		DISP_3D_TO_MAIN,			//上画面が3D
		FALSE,						//特殊アトリビュートシステム：使わない
		TRUE,						//サブオーバーレイ：自動読み込み
		0,							//特殊アトリビュート用に保持するデータ数
		0xc4000,					//フィールドで確保するヒープのサイズ
	},
	///MAP_MODE_UNDER		炭鉱
	{
		FIELD_SUBSCRN_UNDER,		//サブ画面：レーダー
		DIV_MAP_MODE_UNDER,			//マップ分割転送システム指定：地下用
		MAP_TOOL_MODE_UNDER,		//マップツール指定：地下用
		DISP_3D_TO_SUB,				//下画面が3D
		TRUE,						//特殊アトリビュートシステム：使う
		FALSE,						//サブオーバーレイ：読み込まない
		16,							//特殊アトリビュート用に保持するデータ数
		0xc4000,					//フィールドで確保するヒープのサイズ
	},
	///MAP_MODE_UNION		ユニオンルーム
	{
		FIELD_SUBSCRN_UNION,		//サブ画面：ユニオンボード
		DIV_MAP_MODE_GROUND,		//マップ分割転送システム指定：通常
		MAP_TOOL_MODE_GROUND,		//マップツール指定：通常
		DISP_3D_TO_MAIN,			//上画面が3D
		FALSE,						//特殊アトリビュートシステム：使わない
		TRUE,						//サブオーバーレイ：自動読み込み
		0,							//特殊アトリビュート用に保持するデータ数
		0xc4000,					//フィールドで確保するヒープのサイズ
	},
	///MAP_MODE_COLOSSEUM	通信対戦部屋
	{
		FIELD_SUBSCRN_NO_POKETCH,	//サブ画面：モンスターボール表示だけ
		DIV_MAP_MODE_UNDER,			//マップ分割転送システム指定：地下用
		MAP_TOOL_MODE_UNDER,		//マップツール指定：地下用
		DISP_3D_TO_MAIN,			//上画面が3D
		TRUE,						//特殊アトリビュートシステム：使う
		TRUE,						//サブオーバーレイ：自動読み込み
		1,							//特殊アトリビュート用に保持するデータ数
		0xc4000,					//フィールドで確保するヒープのサイズ
	},
	///MAP_MODE_BTOWER		バトルタワー
	{
		FIELD_SUBSCRN_POKETCH,		//サブ画面：ポケッチ
		DIV_MAP_MODE_UNDER,			//マップ分割転送システム指定：地下用
		MAP_TOOL_MODE_UNDER,		//マップツール指定：地下用
		DISP_3D_TO_MAIN,			//上画面が3D
		TRUE,						//特殊アトリビュートシステム：使う
		TRUE,						//サブオーバーレイ：自動読み込み
		1,							//特殊アトリビュート用に保持するデータ数
		0xc4000 - FIELD_HEIGHT_DATA_SIZE * 4,	//フィールドで確保するヒープのサイズ
	},
};

//============================================================================================
//
//
//	ツール関数
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	マップモード修正処理
 * @param	fsys		フィールド制御ワークへのポインタ
 *
 * バトルタワーでは通信をおこなうとメモリが不足するために、特殊アトリビュートを
 * 使用する。本来はバトルタワーの出入りで明示的にMapModeの指定を行うべきであるが
 * 時期的な判断から、特殊処理でMapModeの切替を行う。06.05.16 tamada
 */
//-----------------------------------------------------------------------------
static void MapChg_MapModeControl(FIELDSYS_WORK * fsys)
{
	BOOL IsBtower;

	switch (fsys->location->zone_id) {
	case ZONE_ID_D31R0201:
	case ZONE_ID_D31R0202:
	case ZONE_ID_D31R0203:
	case ZONE_ID_D31R0204:
	case ZONE_ID_D31R0205:
	case ZONE_ID_D31R0206:
	case ZONE_ID_D31R0207:
		IsBtower = TRUE;
		break;
	default:
		IsBtower = FALSE;
	}
	if (!IsBtower && fsys->MapMode == MAP_MODE_BTOWER) {
	//バトルタワー以外でマップモードがBTOWERのとき、通常モードに修正する
		fsys->MapMode = MAP_MODE_GROUND;
	} 
	if (IsBtower) {
	//バトルタワーのとき、マップモードをBTOWERにする
		fsys->MapMode = MAP_MODE_BTOWER;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ指定更新
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	next		次の遷移先を指すLOCATION_WORKへのポインタ
 */
//-----------------------------------------------------------------------------
static void MapChg_SetNewLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next)
{
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * before = Situation_GetBeforeLocation(sit);
///	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);
	//ロケーション更新
	if (next != NULL) {
		*before = *fsys->location;
		*(fsys->location) = *next;
	}
	//ゾーン別データの読み込み
	EventData_LoadZoneData(fsys, fsys->location->zone_id);

	if (fsys->location->door_id != DOOR_ID_JUMP_CODE){
		//出入口接続の場合の処理
		const CONNECT_DATA* connect;
		connect = EventData_GetNowConnectDataByID(fsys, fsys->location->door_id);
		fsys->location->grid_x = connect->x;
		fsys->location->grid_z = connect->z;
		//特殊接続先に出た場合は、特殊接続先を保持するようにしておく
		if (connect->link_door_id == SPECIAL_SPEXIT01) {
			LOCATION_WORK *sp, *ent;
			sp = Situation_GetSpecialLocation(sit);
			ent = Situation_GetEntranceLocation(sit);
			*sp = *ent;
		}
	}
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_Printf("ZONE:%d X:%d Z:%d\n",fsys->location->zone_id,
			fsys->location->grid_x, fsys->location->grid_z);
#endif
}

//-----------------------------------------------------------------------------
/**
 * @brief	システムフラグを見て3D面をセット
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void MapChg_Set3DDisplay(FIELDSYS_WORK *fsys)
{
	GF_ASSERT(fsys->MapMode < MAP_MODE_MAX);
	sys.disp3DSW = fsys->MapModeData->disp3DSW;
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移時のデータ更新処理
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	walk_flag	TRUEのとき、あるいて接続
 *						FALSEのとき、マップ切替で接続
 */
//-----------------------------------------------------------------------------
void MapChg_UpdateGameData(FIELDSYS_WORK * fsys, BOOL walk_flag)
{
	int zone_id = fsys->location->zone_id;
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);

	//--マップ内限定BGM指定をクリア
	Snd_FieldBgmClearSpecial( fsys );

	//--スクリプトのマップ内限定フラグ＆ワークのクリア
	LocalEventFlagClear(fsys);

	//--フラグクリア
	if (!walk_flag) {
		FldFlgInit_MapJump(fsys);	//マップジャンプでのフラグ落とし処理
	}else{
		FldFlgInit_Walk(fsys);		//地続きでのゾーンまたぎフラグ落とし処理
	}
	
	//--バトルサーチャーリセット
	Sys_BtlSearcherReset( SaveData_GetEventWork(fsys->savedata) );

	//--時間イベント更新処理
	if (!walk_flag) {
		EVTIME_Update(fsys);
	}

	//--マップ限定の仕掛け用ワークのクリア
	if (!walk_flag){
		//マップジャンプのときのみ初期化する（歩いてゾーンが切り替わった場合は初期化しない）
		GIMMICKWORK_Init(SaveData_GetGimmickWork(fsys->savedata));
	}
	
	//--天候情報を更新
	{
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		u16 id = WeatherData_Get(fsys, zone_id);
		if ((id == WEATHER_SYS_MIST1 && SysFlag_KiribaraiCheck(ev) == TRUE)
				|| (id == WEATHER_SYS_FLASH && SysFlag_FlashCheck(ev) == TRUE)
		   ) {
			id = WEATHER_SYS_SUNNY;
		}
		Situation_SetWeatherID(sit, id);
	}

	//--カメラ
	if (walk_flag) {
		int old_camera = Situation_GetCameraID(sit);
		int new_camera = ZoneData_GetCameraID(zone_id);
		//歩いてゾーンが切り替わったのにカメラが変わってはまずい
		GF_ASSERT(old_camera == new_camera);
	} else {
		//カメラ指定を更新
		Situation_SetCameraID(sit, ZoneData_GetCameraID(zone_id));
	}

	//--ワープ先登録
	if (!walk_flag){
		u16 warp_id;
		//ワープデータに登録されているマップならば、戻り先として登録しておく
		warp_id = WARPDATA_SearchByRoomID(zone_id);
		if (warp_id != 0) {
			Situation_SetWarpID(sit, warp_id);
		}
	}

	//--特殊スクリプト
	SpScriptSearch(fsys, SP_SCRID_FLAG_CHANGE);


	//エンカウント関連初期化
	fsys->encount.walk_count = 0;
	fsys->encount.WinPokeCount = 0;
#if 0
	//サファリにいないときの処理
	if ( !SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		//ゾーン変更があった場合は、ゾーン履歴を更新
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		
		//歩いて移動した場合は移動ポケモンの移動処理
		if (walk_flag){
			//移動ポケモン隣接移動
			MP_MovePokemonNeighboring(data);
		}
	}
#endif	
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ開始時のフィールドOBJ関連処理
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Create(FIELDSYS_WORK * fsys)
{
	int sex;
	int form;
	SITUATION *situ;
	PLAYER_SAVE_DATA *jikisave;
	
	//フィールドOBJ初期化 現状,値は適当
	fsys->fldobjsys = FieldOBJSys_Init( fsys, FLDOBJ_ENTRY_MAX, FLDMAP_PRI_OBJSYS );
	
	//自機追加処理
	sex = MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata));
	situ = SaveData_GetSituation( fsys->savedata );
	jikisave = Situation_GetPlayerSaveData( situ );
	fsys->player = Player_Init( fsys->fldobjsys,
			fsys->location->grid_x,
			fsys->location->grid_z,
			fsys->location->dir,
			jikisave->form, sex, jikisave );
	
	//最初のゾーン全フィールドOBJ追加
	EventData_SetFieldOBJ( fsys );

	//フィールドOBJ動作処理ポーズ
	FieldOBJSys_MoveStopAll( fsys->fldobjsys );
}
//-----------------------------------------------------------------------------
/**
 * @brief	マップ終了時のフィールドOBJ関連処理
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Delete(FIELDSYS_WORK * fsys)
{
    CommPlayerManagerReset();               // 通信相手自機解放
    Player_Delete( fsys->player );			// 自機解放
	FieldOBJ_DeleteAll(fsys->fldobjsys);	// FieldOBJ全解放
	FieldOBJSys_Delete(fsys->fldobjsys);	// FieldOBJシステム解放
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Continue(FIELDSYS_WORK * fsys)
{
	//フィールドOBJ初期化 現状,値は適当
	fsys->fldobjsys = FieldOBJSys_Init( fsys, FLDOBJ_ENTRY_MAX, FLDMAP_PRI_OBJSYS );
	

	Field_LoadFieldObj(fsys);
	//自機追加処理
	
	{
		SITUATION *situ = SaveData_GetSituation( fsys->savedata );
		PLAYER_SAVE_DATA *jikisave = Situation_GetPlayerSaveData( situ );
		int sex = MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata));
		fsys->player = Player_FieldOBJUseRecover(fsys->fldobjsys,jikisave,sex);
	}

	//フィールドOBJ動作処理ポーズ
	FieldOBJSys_MoveStopAll( fsys->fldobjsys );
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップツール（高さ、アトリビュート、etc.）の設定
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	type		ツールのタイプ指定
 */
//-----------------------------------------------------------------------------
static void MapChg_SetupMapTools(FIELDSYS_WORK * fsys)
{
	//バトルタワーのためにマップモードの修正を行っている
	MapChg_MapModeControl(fsys);

	GF_ASSERT(fsys->map_tool_list == NULL);
	//ワールドセットアップ
	SetUpWorldMatrix( fsys->location->zone_id, fsys->World );
	//マップマトリクスを上書き：R224
	if (SysWork_HideMapWorkCheck(SaveData_GetEventWork(fsys->savedata),HIDEMAP_ID_D18)) {
		World_Overwrite_R224(fsys->World);
	}
	//マップマトリクスを上書き：L04
	if (!SysWork_HideMapWorkCheck(SaveData_GetEventWork(fsys->savedata),HIDEMAP_ID_L04)) {
		World_Overwrite_L04(fsys->World);
	}
	
	GF_ASSERT(fsys->MapMode < MAP_MODE_MAX);
	fsys->MapModeData = &MapModeData[fsys->MapMode];
	fsys->DivMapMode = fsys->MapModeData->DivMapMode;
	fsys->subscreen = fsys->MapModeData->subscreen;
	SetUpMapToolList(&fsys->map_tool_list, fsys->MapModeData->MapToolMode);

	if (fsys->MapModeData->SpecialAttrFlag) {
		//アトリビュート読み込み
		SPATTR_SetUpGroundAttr(fsys, fsys->MapModeData->SpecialAttrNum);
	}
	
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップツール（高さ、アトリビュート、etc.）の廃棄
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	type		ツールのタイプ指定
 */
//-----------------------------------------------------------------------------
static void MapChg_RemoveMapTools(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->map_tool_list != NULL);
	fsys->map_tool_list = NULL;
	fsys->subscreen = FIELD_SUBSCRN_MAX;

	if (fsys->MapModeData->SpecialAttrFlag) {
		//地下アトリビュート破棄
		SPATTR_FreeGroundAttr(fsys);
	}
	fsys->MapModeData = NULL;
}

//-----------------------------------------------------------------------------
/**
 * @brief	冒険ノートの開始データ作成
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void FNoteStartDataSet( FIELDSYS_WORK * fsys )
{
	if( fsys->fnote != NULL ){
		void * dat;

		dat = FNOTE_StartDataMake( fsys->location->zone_id, HEAPID_WORLD );
		FNOTE_DataSave( fsys->fnote, dat, FNOTE_TYPE_START );
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	現在位置をLOCATION_WORKにセットする
 * @param	loc			LOCATION_WORKへのポインタ
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void SetLocationHere(LOCATION_WORK * loc, const FIELDSYS_WORK * fsys)
{
	SetLocation(loc, fsys->location->zone_id, DOOR_ID_JUMP_CODE,
			Player_NowGPosXGet(fsys->player), Player_NowGPosZGet(fsys->player), DIR_DOWN);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL IsUnionRoomSave(const FIELDSYS_WORK * fsys)
{
	if (ZoneData_IsPokecen2F(fsys->location->zone_id)
		&& fsys->location->grid_x == 7
		&& fsys->location->grid_z == 6) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void SetUnionExit(FIELDSYS_WORK * fsys)
{
	//ポケセン２Fから開始の場合は特殊接続先を設定
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	SetLocation(sp, fsys->location->zone_id, DOOR_ID_JUMP_CODE, 8, 2, DIR_DOWN);
}
//============================================================================================
//
//
//							ゲーム開始
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント：ゲーム開始
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FirstMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		MapChg_SetNewLocation(fsys, fsys->location);

		//高さ、アトリビュート、マップロードの方法を決定
		MapChg_SetupMapTools(fsys);

		MapChg_UpdateGameData(fsys, FALSE);

		MapChg_FieldOBJ_Create(fsys);

		(*seq) ++;
		break;
	case 1:
		EventCmd_StartField_FadeIn(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	ゲーム開始イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventSet_FirstMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;

	fsys->MapMode = MAP_MODE_GROUND;	//始めは地上からスタート
	GameStartScriptInit(fsys);				//ゲーム開始時の特殊スクリプト動作
	event = FieldEvent_Set(fsys, GMEVENT_FirstMapIn, NULL);
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント：コンティニュー
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_ContinueMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
        //ロード直後に呼ぶ地下データ処理
        UnderGroundDataLoadUpdate(fsys->savedata);
        // 冒険ノート表示チェック
		if( FNOTE_GameStartOpenCheck(SaveData_GetFNote(fsys->savedata),SysFlag_FNoteCheck(ev)) ){
			FieldFantasyNote_SetProc( fsys, NULL );
			(*seq) = 4;
			break;
		}
		OS_Printf( "FNOTE_FLAG : %d\n", SysFlag_FNoteCheck(ev) );

	case 1:		// フィールド処理
		fsys->fnote = FNOTE_SavePageGet(SaveData_GetFNote(fsys->savedata),
				SysFlag_FNoteCheck(ev));//冒険ノートページ初期化

		if (SysFlag_CommCounterCheck(ev)) {
		//特殊な状況からの復帰を行うコンティニュー
			SITUATION * sit = SaveData_GetSituation(fsys->savedata);
			//ポケセン２Fから開始の場合は特殊接続先を設定
			if (IsUnionRoomSave(fsys)) {
				SetUnionExit(fsys);
			}
			SysFlag_CommCounterReset(ev);
			MapChg_SetNewLocation(fsys, Situation_GetSpecialLocation(sit));
			//高さ、アトリビュート、マップロードの方法を決定
			MapChg_SetupMapTools(fsys);
			MapChg_UpdateGameData(fsys, FALSE);
			MapChg_FieldOBJ_Create(fsys);
		} else {
		//通常のコンティニュー
			MapChg_SetNewLocation(fsys, NULL);
			//高さ、アトリビュート、マップロードの方法を決定
			MapChg_SetupMapTools(fsys);
			//MapChg_UpdateGameData(fsys, FALSE);	コンティニューではこれは呼ばない
			EVTIME_Update(fsys);
			MapChg_FieldOBJ_Continue(fsys);
		}

		FNoteStartDataSet( fsys );		//冒険ノートの開始データ作成

		FldFlgInit_Continue(fsys);		//コンティニュー時固有フラグ落とし処理

		(*seq) = 2;
		break;

	case 2:		// フェードセット
		EventCmd_StartField_FadeIn(event);
		(*seq) = 3;
		break;

	case 3:		// 終了
		return TRUE;

	case 4:		// 冒険ノート終了待ち
		if( !( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) ) {
			(*seq) = 1;
		}
		break;
	}

	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	ゲーム開始イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventSet_ContinueMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;

	fsys->MapMode = MAP_MODE_GROUND;	//始めは地上からスタート
	event = FieldEvent_Set(fsys, GMEVENT_ContinueMapIn, NULL);
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
typedef struct {
	BOOL WarpEffEnd;
	LOCATION_WORK union_loc;
}ERROR_CONTINUE_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_ErrorContinueMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	ERROR_CONTINUE_WORK * ecw = FieldEvent_GetSpecialWork(event);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

        //ロード直後に呼ぶ地下データ処理
        UnderGroundDataLoadUpdate(fsys->savedata);

		fsys->fnote = FNOTE_SavePageGet(SaveData_GetFNote(fsys->savedata),
				SysFlag_FNoteCheck(ev));//冒険ノートページ初期化

		(*seq) ++;
		break;

	case 1:
		MapChg_SetNewLocation(fsys, &ecw->union_loc);
		//高さ、アトリビュート、マップロードの方法を決定
		MapChg_SetupMapTools(fsys);
		MapChg_UpdateGameData(fsys, FALSE);
		MapChg_FieldOBJ_Create(fsys);
		(*seq) ++;
		break;

	case 2:
		// ユニオンルーム通信開始
		fsys->union_work = Comm_UnionRoomInit(fsys);
		// ユニオンルームOBJ制御タスク起動
		fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;

	case 3:
		ecw->WarpEffEnd = FALSE;
        StartJumpPointEffect(fsys, FALSE, &ecw->WarpEffEnd);
		(*seq) ++;
		break;

	case 4:
		if (ecw->WarpEffEnd) {
			(*seq) ++;
		}
		break;
	case 5:
		sys_FreeMemoryEz(ecw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゲーム開始イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventSet_ErrorContinueMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;
	ERROR_CONTINUE_WORK * ecw;

	if (ZoneData_IsUnionRoom(fsys->location->zone_id)) {
		/* 専用処理なし */
	} else if (IsUnionRoomSave(fsys)) {
		//ポケセン２Fから開始の場合は特殊接続先を設定
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		SetUnionExit(fsys);
		SysFlag_CommCounterSet(ev);

	} else {

		//通信エラーでもユニオン以外の場合は通常コンティニュー処理へ分岐
		EventSet_ContinueMapIn(fsys);
		return;
	}

	ecw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(ERROR_CONTINUE_WORK));
	ecw->WarpEffEnd = FALSE;
	SetLocation(&ecw->union_loc, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);

	fsys->MapMode = MAP_MODE_UNION;
	FieldEvent_Set(fsys, GMEVENT_ErrorContinueMapIn, ecw);
}


//============================================================================================
//
//
//							ゲーム終了
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	イベント：ゲーム終了
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_GameEnd(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq) ++;
		break;

	case 1:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;

	case 2:
		MapChg_FieldOBJ_Delete(fsys);
		MapChg_RemoveMapTools(fsys);

		GameSystem_FinishGame(fsys);

		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	ゲーム終了処理
 *
 * ゲームメイン処理を終了させる。
 * デバッグ用でメモリリークチェックのため作成した。
 * ポケモンではユーザー操作でゲーム終了させることがないので、製品版では
 * 使用されないはず。
 */
//-----------------------------------------------------------------------------
void EventSet_ReturnToTitle(FIELDSYS_WORK * fsys)
{
	FieldEvent_Set(fsys, GMEVENT_GameEnd, NULL);
}



//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント(アニメ無し即ジャンプ)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChange(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
		EventCmd_FadeOut_FinishField(event);	//サブイベント呼び出し＆このイベントはウェイト
		(mcw->seq) ++;
		break;
	case 1:
		//サブイベント呼び出し＆このイベントはウェイト
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生
		EventCmd_StartField_FadeIn(event);	//サブイベント呼び出し＆このイベントはウェイト
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	next		遷移先マップ指定
 */
//-----------------------------------------------------------------------------
void EventSet_EasyMapChangeByLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next)
{
	EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	mcw->seq = 0;
	mcw->next = *next;
	FieldEvent_Set(fsys, GMEVENT_MapChange, mcw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	x			遷移先マップでのXグリッド位置
 * @param	z			遷移先マップでのYグリッド位置
 * @param	dir			遷移先マップでの初期方向
 *
 * 遷移先マップのどこに出現するかの情報は次のマップを読み込むまではわからないはずなので
 * 本当は座標指定は無駄かもしれないけど、念のため。またエリアとゾーンの関係は再考されるので
 * エリア指定もいらなくなる可能性がある。
 */
//-----------------------------------------------------------------------------
void EventSet_EasyMapChange(FIELDSYS_WORK * fsys, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	EventSet_EasyMapChangeByLocation(fsys, &next);
}

//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントコマンド
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	next		遷移先マップ指定
 */
//-----------------------------------------------------------------------------
void EventCmd_EasyMapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	mcw->seq = 0;
	mcw->next = *next;
	FieldEvent_Call(event, GMEVENT_MapChange, mcw);
}
//-----------------------------------------------------------------------------
/**
 * @brief	マップ遷移イベントコマンド
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	x			遷移先マップでのXグリッド位置
 * @param	z			遷移先マップでのYグリッド位置
 * @param	dir			遷移先マップでの初期方向
 */
//-----------------------------------------------------------------------------
void EventCmd_EasyMapChange(GMEVENT_CONTROL * event, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	EventCmd_EasyMapChangeByLocation(event, &next);
}

//============================================================================================
//
//
//	イベント擬似コマンド：マップ遷移関連
//
//	サブイベントはFieldEvent_Callで呼び出すことで使用する。
//	現在のイベントを停止して、代わりにサブイベントをよびだす。
//	サブイベントが終了すると現在のイベントが呼び出される。
//
//	内部的にはFieldEvent_Callを呼び出してサブイベント実行を行っているが、
//	イベント側からは単純なコマンド呼び出しで実行できるような形に整えていく予定。
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	擬似コマンド用ワーク定義
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	LOCATION_WORK next;
}SIMPLE_MAPCHG_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief	サブイベント：マップ遷移
 * @param	event	イベント制御ワークへのポインタ
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続中
 *
 * サブイベントはFieldEvent_Callで呼び出すことで使用する。
 * 現在のイベントを停止して、代わりにサブイベントをよびだす。
 * サブイベントが終了すると現在のイベントが呼び出される。
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_MapChange(GMEVENT_CONTROL * event)
{
	u16 bgm_no;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = FieldEvent_GetSpecialWork(event);

	switch (smw->seq) {
	case 0:
		//--------終了処理--------
		MapChg_FieldOBJ_Delete(fsys);
		MapChg_RemoveMapTools(fsys);
		(smw->seq) ++;
		break;
		
	case 1:
		//--------開始処理--------
		MapChg_SetNewLocation(fsys, &smw->next);

		//高さ、アトリビュート、マップロードの方法を決定
		MapChg_SetupMapTools(fsys);

		MapChg_UpdateGameData(fsys, FALSE);

		SwayGrass_InitSwayGrass(fsys->SwayGrass);	//揺れ草初期化
		(smw->seq) ++;
		break;
		
	case 2:
		MapChg_FieldOBJ_Create(fsys);
		sys_FreeMemoryEz(smw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：マップ遷移
 * @param	event		イベント制御ワークへのポインタ
 * @param	next		遷移先を指定するLOCATION_WORK型へのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	if (GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがあるのにマップ遷移処理\n" && 0);
		return;
	}
	smw->seq = 0;
	smw->next = *next;
	FieldEvent_Call(event, GMEVENT_Sub_MapChange, smw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：マップ遷移
 * @param	event		イベント制御ワークへのポインタ
 * @param	zone_id		遷移先ゾーンID指定
 * @param	door_id		遷移先出入口指定
 * @param	x			遷移先X座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	z			遷移先Z座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	dir			出現先での方向指定
 *
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChange(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir)
{
	LOCATION_WORK next;
	SetLocation(&next, zone_id, door_id, x, z, dir);
	EventCmd_MapChangeByLocation(event, &next);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_MapChangeFull(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;

	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;
	case 1:
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：マップ切替
 * @param	event		イベント制御ワークへのポインタ
 * @param	zone_id		遷移先ゾーンID指定
 * @param	door_id		遷移先出入口指定
 * @param	x			遷移先X座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	z			遷移先Z座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	dir			出現先での方向指定
 *
 * フィールドマップ終了→マップ切替処理→フィールドマップ再開までの処理を一連で行う
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChangeFull(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir)
{
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	smw->seq = 0;
	SetLocation(&smw->next, zone_id, door_id, x, z, dir);
	FieldEvent_Call(event, GMEVENT_Sub_MapChangeFull, smw);
}

//============================================================================================
//
//
//			ひでんわざ　そらをとぶ用マップ移動
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	空を飛ぶ専用マップ遷移イベント用制御ワーク
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<シーケンス保持ワーク
	TCB_PTR tcb_sky;					///<空を飛ぶ動作TCB_PTR
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
	FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
}EVENT_MAPCHG_WORK_SKY;

static BOOL GMEVENT_MapChangeBySky(GMEVENT_CONTROL * event);
static void EventCmd_Sky_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_Sky_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_StartField_FadeInSky(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_StartField_FadeInSky(GMEVENT_CONTROL * event);
static void EventCmd_FieldFadeInSky(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_WaitFadeSky(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 * @brief	そらを飛ぶ用マップ遷移イベントセット
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	x			遷移先マップでのXグリッド位置
 * @param	z			遷移先マップでのYグリッド位置
 * @param	dir			遷移先マップでの初期方向
 */
//-----------------------------------------------------------------------------
void EventSet_MapChangeBySky(
		FIELDSYS_WORK * fsys, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	
	{
		EVENT_MAPCHG_WORK_SKY * mcw =
			sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_SKY));
		mcw->seq = 0;
		mcw->tcb_sky = NULL;
		mcw->next = next;
		FieldEvent_Set(fsys, GMEVENT_MapChangeBySky, mcw);
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	そらを飛ぶ用マップ遷移イベントセット　イベントチェンジ型
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone		遷移先マップのゾーン指定
 * @param	door_id		遷移先マップでの出現出入口指定
 * @param	x			遷移先マップでのXグリッド位置
 * @param	z			遷移先マップでのYグリッド位置
 * @param	dir			遷移先マップでの初期方向
 */
//-----------------------------------------------------------------------------
void EventChange_MapChangeBySky(
		GMEVENT_CONTROL *event, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	
	{
		EVENT_MAPCHG_WORK_SKY * mcw =
			sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_SKY));
		mcw->seq = 0;
		mcw->tcb_sky = NULL;
		mcw->next = next;
		FieldEvent_Change(event, GMEVENT_MapChangeBySky, mcw);
	}
}

//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント(そらをとぶ)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeBySky(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
		EventCmd_Sky_FinishField(event);	//サブイベント呼び出し＆このイベントはウェイト
		(mcw->seq) ++;
		break;
	case 1:
		//自機状態を二足歩行にする
		Player_FormSet(fsys->player, HERO_FORM_NORMAL);
		//サブイベント呼び出し＆このイベントはウェイト
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生

		//空を飛ぶ固有フラグ落とし処理
		FldFlgInit_FlySky(fsys);

		EventCmd_StartField_FadeInSky(event);	//サブイベント呼び出し＆このイベントはウェイト
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス終了　そらをとぶ
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_Sky_FinishField(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_Sky_FinishField, NULL);
}

//-----------------------------------------------------------------------------
// @brief	フィールド終了(そらをとぶ)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_Sky_FinishField(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス開始→フェードイン　そらをとぶ
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_StartField_FadeInSky(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	FieldEvent_Call(event, GMEVENT_Sub_StartField_FadeInSky, mcw);
}

//-----------------------------------------------------------------------------
// @brief	フィールドフェードイン　そらをとぶ
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_StartField_FadeInSky(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);	
	switch (*seq) {
	case 0:
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		//地名表示
		PlaceNameRequestByFsys(fsys);
		
		EventCmd_FieldFadeInSky(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フェードイン　そらをとぶ
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_FieldFadeInSky(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがないのにフェードを実行\n" && 0);
		return;
	}
	
	//ここにカットイン専用のものをあてる　フェードインはその中で
	{
#if 0
		WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
#else
		mcw->tcb_sky = FieldHidenSkyLanding_Init( fsys, Player_SexGet(fsys->player) );
#endif
		FieldEvent_Call(event, GMEVENT_Sub_WaitFadeSky, mcw);
	}
}

//-----------------------------------------------------------------------------
// @brief	フィールドフェードイン待ち　そらをとぶ。
// ここに空を飛ぶ終了エフェクト待ちを当てる
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_WaitFadeSky(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	
	if( FieldHidenSkyLanding_EndCheck(mcw->tcb_sky) == TRUE ){
		FieldHidenSkyLanding_End( mcw->tcb_sky );
		return( TRUE );
	}
	
	return FALSE;
}

//============================================================================================
//
//
//			あなぬけのひも、あなをほる、テレポート用マップ移動
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	あなぬけ専用マップ遷移イベント用制御ワーク
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<シーケンス保持ワーク
	ANATYPE ana_type;					///<ANATYPE
	TCB_PTR tcb_jiki;					///<動作TCB_PTR
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
}EVENT_MAPCHG_WORK_ANANUKE;

static BOOL GMEVENT_MapChangeByAnanuke(GMEVENT_CONTROL * event);
static void EventCmd_Ananuke_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_Ananuke_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_StartField_FadeInAnanuke(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_StartField_FadeInAnanuke(GMEVENT_CONTROL * event);
static void EventCmd_FieldFadeInAnanuke(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_WaitFadeAnanuke(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 * @brief	穴抜け、穴掘り、テレポートマップ遷移イベントチェンジ
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	escape		遷移先
 * @param	type		ANATYPE
 */
//-----------------------------------------------------------------------------
void EventChange_MapChangeByAnanuke(
	GMEVENT_CONTROL *event, const LOCATION_WORK *escape, u32 ana_type )
{
	EVENT_MAPCHG_WORK_ANANUKE * mcw =
		sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_ANANUKE));
	mcw->seq = 0;
	mcw->ana_type = ana_type;
	mcw->tcb_jiki = NULL;
	mcw->next = *escape;
	FieldEvent_Change( event, GMEVENT_MapChangeByAnanuke, mcw );
}

//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント(あなぬけのひも)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeByAnanuke(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE* mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
		EventCmd_Ananuke_FinishField(event);	//サブイベント呼び出し
		(mcw->seq) ++;
		break;
	case 1:
		//自機状態を二足歩行にする
		Player_FormSet(fsys->player, HERO_FORM_NORMAL);
		//サブイベント呼び出し＆このイベントはウェイト
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生

		//テレポート・穴抜け・穴掘り固有フラグ落とし処理
		if (mcw->ana_type == ANATYPE_TEL){
			FldFlgInit_Teleport(fsys);
		}else if( (mcw->ana_type == ANATYPE_ANA)||
					(mcw->ana_type == ANATYPE_ANAHORI) ){
			FldFlgInit_Escape(fsys);
		}else{
			GF_ASSERT(0&&"脱出方法が不明");
		}

		EventCmd_StartField_FadeInAnanuke(event);	//サブイベント呼び出し
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス終了　あなぬけのひも
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_Ananuke_FinishField(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_Ananuke_FinishField, NULL);
}

//-----------------------------------------------------------------------------
// @brief	フィールド終了(あなぬけのひも)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_Ananuke_FinishField(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フィールドプロセス開始→フェードイン　あなぬけのひも
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_StartField_FadeInAnanuke(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_ANANUKE * mcw = FieldEvent_GetSpecialWork(event);
	FieldEvent_Call(event, GMEVENT_Sub_StartField_FadeInAnanuke, mcw);
}

//-----------------------------------------------------------------------------
// @brief	フィールドフェードイン　あなぬけのひも
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_StartField_FadeInAnanuke(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE* mcw = FieldEvent_GetSpecialWork(event);
	switch (*seq) {
	case 0:
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		//地名表示
		PlaceNameRequestByFsys(fsys);
		
		EventCmd_FieldFadeInAnanuke(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：フェードイン　あなぬけのひも
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void EventCmd_FieldFadeInAnanuke(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE * mcw = FieldEvent_GetSpecialWork(event);
	
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがないのにフェードを実行\n" && 0);
		return;
	}
	
	//ここにカットイン専用のものをあてる　フェードインはその中で
	{
		void *wk = EventWorkSet_AnanukeMapIn( fsys, HEAPID_FIELD, mcw->ana_type );
		FieldEvent_Call( event, GMEVENT_AnanukeMapIn, wk );
	}
}

//============================================================================================
//			ワープポイント
//============================================================================================
//-----------------------------------------------------------------------------
//          ワープポイント専用マップ遷移イベント用制御ワーク
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<シーケンス保持ワーク
    BOOL bEnd;
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
} EVENT_MAPCHG_WARP_WORK;



//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeWorpPoint(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_WARP_WORK* mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
      case 0:
        StartJumpPointEffect( fsys, TRUE, &mcw->bEnd);
        mcw->seq++;
		break;
      case 1:
        if(mcw->bEnd){
			Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
            EventCmd_FinishFieldMap(event);
            mcw->seq++;
        }
        break;
      case 2:
		//サブイベント呼び出し＆このイベントはウェイト
        EventCmd_MapChangeByLocation(event, &mcw->next);
        mcw->seq++;
        break;
      case 3:
		if( Snd_FadeCheck() != 0 ){									//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );			//フィールドBGM再生
		EventCmd_StartFieldMap(event);
        mcw->seq++;
		break;
      case 4:
        mcw->bEnd = FALSE;
        StartJumpPointEffect( fsys, FALSE, &mcw->bEnd);
        mcw->seq++;
		break;
      case 5:
        if(mcw->bEnd){
            mcw->seq++;
        }
        break;
      case 6:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	ワープポイント
//-----------------------------------------------------------------------------
void EventCmd_WarpPoint(FIELDSYS_WORK * fsys, int zone, int door_id)
{
	LOCATION_WORK next;
	EVENT_MAPCHG_WARP_WORK* mcw =
		sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WARP_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_MAPCHG_WARP_WORK));
    
    SetLocation(&next, zone, door_id, 0, 0, Player_DirGet(fsys->player));

	mcw->next = next;
	FieldEvent_Set( fsys, GMEVENT_MapChangeWorpPoint, mcw );
}

///*************************************************************************************
//
//		↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
//		地上のマップ移動処理
//
//
//
//
//		地下のマップ移動処理
//		↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//
///*************************************************************************************


//============================================================================================
//
//
//			地下ジャンプ
//
//
//============================================================================================
static BOOL GMEVENT_UgJump(GMEVENT_CONTROL * event);	//地下＜＞地下
static BOOL UgChg_SubCall(GMEVENT_CONTROL * event, int no);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	int subseq;
	int next_zone_id;
	int next_door_id;
	int next_x;
	int next_z;
	BOOL brightness;
    u16 saveResult;
	void * infowin;			// セーブ情報ウィンドウ用ポインタ
	GF_BGL_BMPWIN	win;	// メッセージウィンドウ
	STRBUF * str;			// 通信開始メッセージバッファ
	u8	midx;				// メッセージインデックス
	BMPMENU_WORK * mw;		// はい・いいえメニューワーク
}EVENT_UGCHG_WORK;


//-----------------------------------------------------------------------------
/**
 * @brief	地下と地上を行き来するイベント用ワークの生成
 */
//-----------------------------------------------------------------------------
void * MakeUGChangeWork(FIELDSYS_WORK * fsys)
{
	EVENT_UGCHG_WORK * mcw;
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	//イベント生成
	mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
	mcw->seq = 0;
	mcw->subseq = 0;
	
	if (fsys->MapMode == MAP_MODE_UNDER){	//現在地下の場合
		//地上へジャンプ
		mcw->next_zone_id = sp->zone_id;
		mcw->next_door_id = DOOR_ID_JUMP_CODE;
		mcw->next_x = sp->grid_x;
		mcw->next_z = sp->grid_z;
	}else{
		SetLocationHere(sp, fsys);			//切り替わる前の場所を覚えておく
		mcw->next_zone_id = ZONE_ID_UG;
		mcw->next_door_id = DOOR_ID_JUMP_CODE;
		//--ジャンプ先の選出方法--
		//ブロック内座標8,8の場所にジャンプするようにする
		//(炭鉱サイズは地上の1/4)<<確かにそうだがジャンプできる部分だけを考えると大ウソ
		
		//30ｘ30地上の炭鉱ジャンプ有効ブロックは縦23ブロック、横28ブロック
		//（縦開始6ブロックと最下1ブロックは範囲外。横は両サイド1ブロックずつが範囲外）
		//15ｘ15地下のフリームーブ有効ブロックは縦13ブロック、横14ブロック
		//（縦開始2ブロックは秘密基地、横は、左1ブロック側面が秘密基地）
		//企画意図で地下フリームーブ上1ブロックにはジャンプできないようにすると縦12ブロック
		//地上縦23ブロックでは、計算誤差が出るので、最下範囲外1ブロックもジャンプ対象とすると縦24ブロック
		//よって、地下ジャンプ先のブロックは、
		//縦に関しては、
		//(現在の地上ブロック-縦オフセット6ブロック)/2+秘密基地オフセット2ブロック+ジャンプ拒否1ブロック
		//横に関しては、
		//(現在の地上ブロック-横オフセット1ブロック)/2+秘密基地オフセット1ブロック
		//
		//ジャンプ場所は、1ブロック（32ｘ32）の内側に向かって、上下左右8グリッド進んだ所
		{
			int x_ofs,z_ofs;
			int block_x,block_z;
			block_x = (sp->grid_x/32)-1;
			block_z = (sp->grid_z/32)-6;

			GF_ASSERT(block_x>=0);
			GF_ASSERT(block_z>=0);	
			
			if (block_x%2 == 0){
				x_ofs = 8;
			}else{
				x_ofs = 23;
			}
			if (block_z%2 == 0){
				z_ofs = 8;
			}else{
				z_ofs = 23;
			}

			block_x = (block_x/2)+1;
			block_z = (block_z/2)+2+1;
			mcw->next_x = block_x*32+x_ofs;
			mcw->next_z = block_z*32+z_ofs;
		}
	}
	return mcw;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ChangeUnderGroundDirect(FIELDSYS_WORK * fsys)
{
	EVENT_UGCHG_WORK * mcw = MakeUGChangeWork(fsys);
	if (mcw == NULL) {
		return;
	}
	FieldEvent_Set(fsys, MapChg_GetUgChangeEvent(fsys), mcw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント：地上から地下へ
 */
//-----------------------------------------------------------------------------
enum {
	UGCHG_SEQ_SIO_INIT = 0,		// 通信開始メッセージセット
	UGCHG_SEQ_SIO_YNINIT,		// メッセージ待ち＆はい・いいえ初期化
	UGCHG_SEQ_SIO_YNWAIT,		// はい・いいえ待ち

	UGCHG_SEQ_REPORT_INIT,		// レポート初期化
	UGCHG_SEQ_REPORT_WAIT,		// レポート終了待ち

	UGCHG_SEQ_CANCEL,			// イベントキャンセル

	// ↓エフェクト
	UGCHG_SEQ_0,
	UGCHG_SEQ_1,
	UGCHG_SEQ_2,
	UGCHG_SEQ_3,
	UGCHG_SEQ_4,
	UGCHG_SEQ_5,
	UGCHG_SEQ_6,
};

// はい・いいえウィンドウデータ
static const BMPWIN_DAT YesNoBmpDat = {
	FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
	FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
};


BOOL GMEVENT_GroundToUnderGround(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	
	switch (mcw->seq) {
	case UGCHG_SEQ_SIO_INIT:
		{
			MSGDATA_MANAGER * mman = MSGMAN_Create(
										MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_connect_dat,HEAPID_WORLD );
			mcw->str = MSGMAN_AllocString( mman, msg_connect_common_01 );
			MSGMAN_Delete( mman );
		}
		FldTalkBmpAdd( fsys->bgl, &mcw->win, FLD_MBGFRM_FONT );
		FieldTalkWinPut( &mcw->win, SaveData_GetConfig(fsys->savedata) );
		mcw->midx = FieldTalkMsgStart(
						&mcw->win, mcw->str, SaveData_GetConfig(fsys->savedata), 1 );
		mcw->seq = UGCHG_SEQ_SIO_YNINIT;
		break;

	case UGCHG_SEQ_SIO_YNINIT:
		if( FldTalkMsgEndCheck( mcw->midx ) == 1 ){
			STRBUF_Delete( mcw->str );
			MenuWinGraphicSet(
				fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_WORLD );
			mcw->mw = BmpYesNoSelectInit(
						fsys->bgl, &YesNoBmpDat, MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_WORLD );
			mcw->seq = UGCHG_SEQ_SIO_YNWAIT;
		}
		break;

	case UGCHG_SEQ_SIO_YNWAIT:
		switch( BmpYesNoSelectMain( mcw->mw, HEAPID_WORLD ) ){
		case 0:
			BmpTalkWinClear( &mcw->win, WINDOW_TRANS_ON );
			GF_BGL_BmpWinDel( &mcw->win );
			mcw->seq = UGCHG_SEQ_REPORT_INIT;
			break;

		case BMPMENU_CANCEL:
			BmpTalkWinClear( &mcw->win, WINDOW_TRANS_ON );
			GF_BGL_BmpWinDel( &mcw->win );
			mcw->seq = UGCHG_SEQ_CANCEL;
		}
		break;


	case UGCHG_SEQ_REPORT_INIT:		// レポート呼び出し
		if( SaveData_IsOverwritingOtherData(fsys->savedata) ) {
			EventCall_Script( event, SCRID_REPORT_NG, NULL, NULL );
		}else{
            // 地下に入る前のフラグ制御
            UnderGroundDataBeforeUGSave(fsys->savedata);
			//レポート情報生成
			mcw->infowin = ReportInfo_Create( fsys, HEAPID_WORLD, FLD_MBGFRM_FONT );
			ReportInfo_WriteWindow( mcw->infowin );
			mcw->saveResult = FALSE;	// 結果受け取り用ワーク初期化
			EventCall_Script( event, SCRID_REPORT, NULL, &mcw->saveResult );
		}
		mcw->seq = UGCHG_SEQ_REPORT_WAIT;
		break;

	case UGCHG_SEQ_REPORT_WAIT:		// レポート待ち
		if( SaveData_IsOverwritingOtherData(fsys->savedata) ){
			mcw->seq = UGCHG_SEQ_CANCEL;
		}else{
			ReportInfo_EraseWindow( mcw->infowin );
			ReportInfo_Delete( mcw->infowin );
			if( mcw->saveResult == FALSE ){		//セーブしていない
				mcw->seq = UGCHG_SEQ_CANCEL;
			}else{								//セーブした
				mcw->seq = UGCHG_SEQ_0;
			}
		}
		break;




	case UGCHG_SEQ_CANCEL:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		sys_FreeMemoryEz(mcw);
		return TRUE;

	case UGCHG_SEQ_0:
		Snd_BgmFadeOut( 0, BGM_FADE_UG_TIME );	//BGMフェードアウト
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_1:
		if (UgChg_SubCall(event, EFCT_UG_DOWN00)) {
			(mcw->seq) ++;
		}
		break;

	case UGCHG_SEQ_2:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_3:
		fsys->MapMode = MAP_MODE_UNDER;
        Overlay_Load( FS_OVERLAY_ID( ol_underground ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
		//fsys->DivMapMode = DIV_MAP_MODE_UNDER;
		// 通信開始処理へ
		CommFieldStateEnterUnderGround(fsys); // 通信ステートを地下開始に変更
		EventCmd_MapChange(event,
								mcw->next_zone_id,
								DOOR_ID_JUMP_CODE,
								mcw->next_x,
								mcw->next_z,
								DIR_DOWN);

		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_4:
		if( Snd_FadeCheck() != 0 ){				//BGMフェード待ち
			break;
		}
		Snd_SceneSet( SND_SCENE_DUMMY );		//サウンドシーンクリア
		Snd_FieldBgmClearSpecial( fsys );		//マップ内限定のBGM指定クリア

		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_5:
		if (UgChg_SubCall(event, EFCT_UG_DOWN01)) {
			CommFieldStateArrivalUnderGround(); // 地下に到着
			fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//炭鉱レーダー画面ＯＮ
            ChangeBrightnessRequest(30,BRIGHTNESS_NORMAL,BRIGHTNESS_BLACK,
                                    PLANEMASK_BG0|PLANEMASK_BG3|PLANEMASK_OBJ,MASK_SUB_DISPLAY);
            (mcw->seq) ++;
		}
		break;
	case UGCHG_SEQ_6:
		if (IsFinishedBrightnessChg(MASK_SUB_DISPLAY)) {
            UgSecretBaseBootOn(TRUE); // 秘密基地の動作をON
            sys_FreeMemoryEz(mcw);
			return TRUE;
		}
		break;
	
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	イベント：地下から地上へ
 */
//-----------------------------------------------------------------------------
BOOL GMEVENT_UnderGroundToGround(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	int end_flg = 0;
		
	
	switch (mcw->seq) {
	case 0:
        // 通信終了処理へ
        UgSecretBaseBootOn(FALSE); // 秘密基地の動作をOFF
        CommFieldStateExitUnderGround();  // 通信ステートを地下終了に変更
		//地下の時はレーダーを先に解放する
		UnderGround_RadarEnd(fsys->UnderGroundRadar);
		ChangeBrightnessRequest(30,BRIGHTNESS_BLACK,BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_SUB_DISPLAY);
		mcw->seq++;
		break;
	case 1:
		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){
            if((fsys->UnderGroundRadar==NULL) && !CommIsInitialize()){
				Snd_BgmFadeOut( 0, BGM_FADE_UG_TIME );	//BGMフェードアウト
                mcw->seq++;
            }
        }
		break;
	case 2:
		if (UgChg_SubCall(event, EFCT_UG_UP00)) {
			(mcw->seq) ++;
		}
		break;
	case 3:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;

	case 4:
		fsys->MapMode = MAP_MODE_GROUND;
	    Overlay_UnloadID( FS_OVERLAY_ID(ol_underground) );
	//fsys->DivMapMode = DIV_MAP_MODE_GROUND;
		EventCmd_MapChange(event,
								mcw->next_zone_id,
								DOOR_ID_JUMP_CODE,
								mcw->next_x,
								mcw->next_z,
								DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 5:
		if( Snd_FadeCheck() != 0 ){				//BGMフェード待ち
			break;
		}
		Snd_SceneSet( SND_SCENE_DUMMY );		//サウンドシーンクリア
		Snd_FieldBgmClearSpecial( fsys );		//マップ内限定のBGM指定クリア

		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
    case 6:
		if (UgChg_SubCall(event, EFCT_UG_UP01)) {
     		(mcw->seq) ++;
        }
        break;
    case 7:
        sys_FreeMemoryEz(mcw);
        return TRUE;
		break;
	
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
GMEVENT_FUNC MapChg_GetUgChangeEvent(const FIELDSYS_WORK * fsys)
{
	if (fsys->MapMode == MAP_MODE_GROUND) {
		return GMEVENT_GroundToUnderGround;
	} else if (fsys->MapMode == MAP_MODE_UNDER) {
		return GMEVENT_UnderGroundToGround;
	} else {
		GF_ASSERT_MSG(0,"Unknown MAP_MODE %d\n",fsys->MapMode);
		return NULL;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL UgChg_SubCall(GMEVENT_CONTROL * event, int no)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	BOOL	ret = FALSE;

	switch(mcw->subseq){
	case 0:		// スタート
		mcw->brightness = 0;
		StartUnderGroundEffect(fsys, no, &mcw->brightness);
		mcw->subseq++;
		break;
	case 1:		// 終了待ち
		if(mcw->brightness){
			mcw->subseq = 0;
			ret = TRUE;
		}
		break;
	}
	return ret;
}


//============================================================================================
//
//
//			イベントコマンド：地下～地下のマップ移動
//
//
//============================================================================================
static void EventCmd_UgJump(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UgJump(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	int end_flg = 0;
		
	
	switch (mcw->seq) {
	case 0:
        UgSecretBaseBootOn(FALSE);
            //レーダーを先に解放する
		UnderGround_RadarEnd(fsys->UnderGroundRadar);
		CommStateJumpUnderGround();   // 移動する場合の通信関連処理
		mcw->seq++;
		break;

	case 1:
		if(fsys->UnderGroundRadar==NULL){
			mcw->seq++;
		}
		break;
	case 2:
		(mcw->seq) ++;
		break;
	case 3:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;
	case 4:
		
		EventCmd_UgJump(event,
						mcw->next_zone_id,
						DOOR_ID_JUMP_CODE,
						mcw->next_x,
						mcw->next_z,
						DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 5:
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 6:
        UgSecretBaseBootOn(TRUE);
		CommStateJumpEndUnderGround(); // 移動終了する場合の通信関連処理
		fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//炭鉱レーダー画面ＯＮ
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void JumpUnderGroundDirect(FIELDSYS_WORK * fsys, const int inX, const int inZ)
{
	EVENT_UGCHG_WORK * mcw;
	
	//イベント生成
	mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
	mcw->seq = 0;
	mcw->subseq = 0;
	mcw->next_zone_id = ZONE_ID_UG;
	mcw->next_door_id = DOOR_ID_JUMP_CODE;
	//ここで、ジャンプ先を決定します
	mcw->next_x = inX;
	mcw->next_z  = inZ;
	
	FieldEvent_Set(fsys, GMEVENT_UgJump, mcw);
	return;
}


//-----------------------------------------------------------------------------
/**
 * @brief	サブイベント：マップ遷移(地下～地下)
 * @param	event	イベント制御ワークへのポインタ
 * @retval	TRUE	イベント終了
 * @retval	FALSE	イベント継続中
 *
 * サブイベントはFieldEvent_Callで呼び出すことで使用する。
 * 現在のイベントを停止して、代わりにサブイベントをよびだす。
 * サブイベントが終了すると現在のイベントが呼び出される。
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_UgJump(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = FieldEvent_GetSpecialWork(event);

	switch (smw->seq) {
	case 0:
		//--------終了処理--------
		MapChg_FieldOBJ_Delete(fsys);
		(smw->seq) ++;
		break;
		
	case 1:
		//--------開始処理--------
		MapChg_SetNewLocation(fsys, &smw->next);
        //--特殊スクリプトのみ実行  k.ohno & saito
        SpScriptSearch(fsys, SP_SCRID_FLAG_CHANGE);
        
		(smw->seq) ++;
		break;
		
	case 2:
		MapChg_FieldOBJ_Create(fsys);
		sys_FreeMemoryEz(smw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：マップ遷移(地下～地下)
 * @param	event		イベント制御ワークへのポインタ
 * @param	next		遷移先を指定するLOCATION_WORK型へのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_UgJumpByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	if (GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainprocがあるのにマップ遷移処理\n" && 0);
		return;
	}
	smw->seq = 0;
	smw->next = *next;
	FieldEvent_Call(event, GMEVENT_Sub_UgJump, smw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：マップ遷移(地下～地下)
 * @param	event		イベント制御ワークへのポインタ
 * @param	zone_id		遷移先ゾーンID指定
 * @param	door_id		遷移先出入口指定
 * @param	x			遷移先X座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	z			遷移先Z座標指定（door_id == DOOR_ID_JUMP_CODEのときのみ有効）
 * @param	dir			出現先での方向指定
 *
 */
//-----------------------------------------------------------------------------
static void EventCmd_UgJump(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir)
{
	LOCATION_WORK next;
	SetLocation(&next, zone_id, door_id, x, z, dir);
	EventCmd_UgJumpByLocation(event, &next);
}



//============================================================================================
//
//
//			ユニオンルーム用マップ移動
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//          ユニオン専用マップ遷移イベント用制御ワーク
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<シーケンス保持ワーク
    BOOL bEnd;
	LOCATION_WORK next;					///<マップ遷移先指定用ワーク
}EVENT_MAPCHG_UNION_WORK;



//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UnionRoomOut(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_UNION_WORK* emuw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	
	switch (*seq) {
      case 0:
        //"マップ遷移専用"フェードアウト → BGM再生
		{
			//ポケセン２階とユニオンは同じBGMなのでサウンドロード処理は何もしていない！
			LOCATION_WORK* location = &emuw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
        StartJumpPointEffect( fsys, TRUE, &emuw->bEnd);
        (*seq)++;
		break;
      case 1:
        if(emuw->bEnd){
            EventCmd_FinishFieldMap(event);
            (*seq)++;
        }
        break;
      case 2:
		//サブイベント呼び出し＆このイベントはウェイト
        EventCmd_MapChangeByLocation(event, &emuw->next);
        (*seq)++;
        break;
      case 3:
		EventCmd_StartFieldMap(event);
        (*seq)++;
		break;
      case 4:
		EventCmd_FieldFadeIn(event);
        (*seq)++;
		break;
      case 5:
		sys_FreeMemoryEz(emuw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// イベントセット：ユニオンルーム用マップ遷移：抜ける
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChangeOut(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENT_MAPCHG_UNION_WORK* emuw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_UNION_WORK));
    MI_CpuClear8(emuw, sizeof(EVENT_MAPCHG_UNION_WORK));
    
	emuw->next = *sp;
	
	// ユニオンルーム通信解放
	Comm_UnionFinalize(fsys);
	// ユニオンルーム表示処理用ワーク解放
	Comm_UnionRoomViewEnd(fsys->union_view);

	fsys->MapMode = MAP_MODE_GROUND;

	FieldEvent_Set(fsys, GMEVENT_UnionRoomOut, emuw);
	fsys->union_work = NULL;
}

//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UnionRoomIn(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_UNION_WORK* emuw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	
	switch (*seq) {
      case 0:
        //"マップ遷移専用"フェードアウト → BGM再生
		{
			//ポケセン２階とユニオンは同じBGMなのでサウンドロード処理は何もしていない！
			LOCATION_WORK* location = &emuw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
		EventCmd_FieldFadeOut(event);
        (*seq)++;
		break;
      case 1:
		EventCmd_FinishFieldMap(event);
		(*seq)++;
        break;
      case 2:
		//サブイベント呼び出し＆このイベントはウェイト
        EventCmd_MapChangeByLocation(event, &emuw->next);
        (*seq)++;
        break;
      case 3:
		EventCmd_StartFieldMap(event);
        (*seq)++;
		break;
      case 4:
        emuw->bEnd = FALSE;
        StartJumpPointEffect( fsys, FALSE, &emuw->bEnd);
        (*seq)++;
		break;
      case 5:
        if(emuw->bEnd){
            (*seq)++;
        }
        break;
      case 6:
		sys_FreeMemoryEz(emuw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// イベントセット：ユニオンルーム用マップ遷移：入る
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChangeIn(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	SetLocationHere(sp, fsys);			//切り替わる前の場所を覚えておく

	// ユニオンルーム通信開始
	fsys->union_work = Comm_UnionRoomInit(fsys);
	// ユニオンルームOBJ制御タスク起動
	fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

	fsys->MapMode = MAP_MODE_UNION;
	EventSet_EasyMapChange(fsys, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 9, 12, DIR_DOWN);
}

//-----------------------------------------------------------------------------
// イベントコマンド：ユニオンルーム用マップ遷移：出入り両方（デバッグ用）
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChange(FIELDSYS_WORK * fsys)
{
	if (fsys->location->zone_id == ZONE_ID_UNION) {
		EventSet_UnionRoomMapChangeOut(fsys);

		// 通信セーブの前のおまじない解除
		SysFlag_CommCounterReset( SaveData_GetEventWork(fsys->savedata) );
	} else {
		// 通信セーブの前のおまじない
		SysFlag_CommCounterSet( SaveData_GetEventWork(fsys->savedata) );

		EventSet_UnionRoomMapChangeIn(fsys);
	}
}

#if 0
//-----------------------------------------------------------------------------
/// イベントコマンド：ユニオンルーム用マップ遷移：抜ける
//-----------------------------------------------------------------------------
void EventCmd_UnionRoomMapChangeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	// ユニオンルーム通信解放
	Comm_UnionFinalize(fsys);
	// ユニオンルーム表示処理用ワーク解放
	Comm_UnionRoomViewEnd(fsys->union_view);
	// UnionBoardが監視してるからNULLにしないと誤動作する
	fsys->union_view = NULL;

	fsys->MapMode = MAP_MODE_GROUND;
	EventCmd_EasyMapChangeByLocation(fsys->event, sp);
	fsys->union_work = NULL;
}
#endif
//-----------------------------------------------------------------------------
/// イベントコマンド：ユニオンルーム用マップ遷移：入る
//-----------------------------------------------------------------------------
void EventCmd_UnionRoomMapChangeIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENT_MAPCHG_UNION_WORK* emuw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_UNION_WORK));
    MI_CpuClear8(emuw, sizeof(EVENT_MAPCHG_UNION_WORK));

	SetLocationHere(sp, fsys);			//切り替わる前の場所を覚えておく

	SetLocation(&emuw->next, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);

	// ユニオンルーム通信開始
	fsys->union_work = Comm_UnionRoomInit(fsys);
	// ユニオンルームOBJ制御タスク起動
	fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

	fsys->MapMode = MAP_MODE_UNION;
	FieldEvent_Call(event, GMEVENT_UnionRoomIn, emuw);
//	EventCmd_EasyMapChange(fsys->event, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);
}


//============================================================================================
//
//
//		通信対戦部屋用マップ移動
//
//
//============================================================================================
//-----------------------------------------------------------------------------
// @brief	マップ遷移イベント(対戦部屋に入る専用)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeColosseum(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//フィールドBGMフェードアウト
		EventCmd_FadeOut_FinishField(event);	//サブイベント呼び出し＆このイベントはウェイト
		(mcw->seq) ++;
		break;
	case 1:
		//サブイベント呼び出し＆このイベントはウェイト
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//サウンドフェード中
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//フィールドBGM再生
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
///	イベントコマンド：通信対戦部屋用マップ遷移：入る
//-----------------------------------------------------------------------------
void EventCmd_ColosseumMapChangeIn(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir)
{
    LOCATION_WORK next;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	SetLocationHere(sp, fsys);			//切り替わる前の場所を覚えておく

	fsys->MapMode = MAP_MODE_COLOSSEUM;	//マップモードを通信対戦部屋用に

    {
        EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
        
        SetLocation(&next, zone_id, door_id, x, z, dir);
        mcw->seq = 0;
        mcw->next = next;
        FieldEvent_Call(event, GMEVENT_MapChangeColosseum, mcw);
    }
}


//-----------------------------------------------------------------------------
///	イベントコマンド：通信対戦部屋用マップ遷移：抜ける
//-----------------------------------------------------------------------------
void EventCmd_ColosseumMapChangeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	fsys->MapMode = MAP_MODE_GROUND;		//マップモードを通常に
	EventCmd_EasyMapChangeByLocation(fsys->event, sp);
}

//-----------------------------------------------------------------------------
// イベントセット：通信対戦部屋用マップ遷移：抜ける
//-----------------------------------------------------------------------------
void EventSet_ColosseumMapChangeOut(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	fsys->MapMode = MAP_MODE_GROUND;
	EventSet_EasyMapChangeByLocation(fsys, sp);
}

#ifdef PM_DEBUG
//-----------------------------------------------------------------------------
//  地下に任意の位置に降りる為に作成 デバッグ用 2006.02.08
//-----------------------------------------------------------------------------
void Debug_ChangeUnderGroundDirect(FIELDSYS_WORK * fsys, int x, int z)
{
	EVENT_UGCHG_WORK * mcw = MakeUGChangeWork(fsys);
	if (mcw == NULL) {
		return;
	}
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->seq = UGCHG_SEQ_0;
	FieldEvent_Set(fsys, MapChg_GetUgChangeEvent(fsys), mcw);
}
#endif //PM_DEBUG
