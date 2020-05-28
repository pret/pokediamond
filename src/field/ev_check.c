//============================================================================================
/**
 * @file	ev_check.c	
 * @brief	イベント発動チェックシステム
 * @author	Sousuke Tamada
 * @date	01.03.29
 *
 * 05.07.04 Hiroyuki Nakamura
 */
//============================================================================================
#include "common.h"

#include "system/snd_tool.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "fieldsys.h"
#include "field_clact.h"
#include "fld_menu.h"
#include "sxy.h"
#include "script.h"

#define EV_CHECK_H_GLOBAL
#include "ev_check.h"
#include "eventdata.h"		//ゾーン毎のイベントデータ参照のため

#include "fld_debug.h"

#include "field_event.h"
#include "field_encount.h"
#include "player_event_arrowmat.h"

#include "ev_mapchange.h"

#include "script.h"
#include "zonedata.h"
#include "mapdefine.h"
#include "poketool/pokeparty.h"

#include "fieldobj.h"

#include "ev_trainer.h"
#include "communication/wh_config.h"
#include "communication/wh.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_field.h"
#include "comm_direct_counter.h"
#include "comm_field_state.h"
#include "comm_vsroom.h"
#include "comm_player.h"
#include "underground/ug_manager.h"
#include "honey_tree_enc.h"

#include "map_attr.h"
#include "ev_pokemon.h"		//EvPoke_Enable2vs2Battle

#include "field\eventflag.h"

#include "..\fielddata\script\common_scr_def.h"
#include "..\fielddata\script\hiden_def.h"
#include "..\fielddata\script\bg_attr_def.h"
#include "..\fielddata\script\r201_def.h"
#include "..\fielddata\script\safari_def.h"
#include "..\fielddata\script\battle_room_def.h"
#include "..\fielddata\script\tv_def.h"
#include "../fielddata/script/union_def.h"

#define	SCRID_COMMON_MSG	0

#include "field_3d_anime_ev.h"

#include "map_jump_def.h"
#include "map_jump.h"

#include "situation_local.h"

#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/sodateyadata.h"
#include "savedata/record.h"
#include "sodateya.h"

#include "syswork.h"
#include "sysflag.h"

#include "gym.h"
#include "poison_effect.h"
#include "fieldmap_work.h"

#include "battle\wazano_def.h"
#include "comm_union_beacon.h"

#include "btl_searcher.h"

#include "system/debug_flag.h"

#include "sway_grass_enc.h"

#include "spray.h"
#include "pokepark_sys.h"
#include "field_poketch.h"


//#define	DEBUG_ALL_EXIT_CONNECT
//============================================================================================
//	定数定義
//============================================================================================
#define	ALL_KEY		( PAD_KEY_UP | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT )

#define	PAD_BUTTON_MENU		( PAD_BUTTON_X )		// メニューボタン
#define	PAD_BUTTON_BENRI	( PAD_BUTTON_Y )		// 便利ボタン


///毒ダメージを受ける歩数
#define	POISON_STEP_MAX		(4)

///なつき度計算する歩数
#define FRIENDCALC_STEP_MAX	(128)

//============================================================================================
//
//
//
//============================================================================================
static BOOL EvCheck_ExitByPush(FIELDSYS_WORK * fsys, const EV_REQUEST * req);
static  u16 EvCheck_TalkMapAttr(FIELDSYS_WORK * repw, MATR matr);

static BOOL CheckEncountEvent(FIELDSYS_WORK * fsys);
static BOOL CheckMoveEvent(FIELDSYS_WORK * fsys);// 一歩ごとのイベント起動チェック
static BOOL CheckPosEvent(FIELDSYS_WORK * fsys);
static BOOL CheckExit(FIELDSYS_WORK * fsys, const int x, const int z, const u8 inAttr);
static BOOL CheckSodateya( FIELDSYS_WORK *fsys );
static BOOL CheckPoison(FIELDSYS_WORK * fsys);
static BOOL CheckSafariStep(FIELDSYS_WORK * fsys);
static BOOL CheckBtlSearcher(FIELDSYS_WORK * fsys);
static BOOL CheckPokeSearcher(FIELDSYS_WORK * fsys);
static BOOL CheckBoardStart( FIELDSYS_WORK * repw );
static BOOL CheckSpray( FIELDSYS_WORK *fsys );

static BOOL CheckFriendCalcStepCount( FIELDSYS_WORK *fsys );
static void DoFriendCalcStepCount( FIELDSYS_WORK *fsys );

//ツール関数
static void GetNowPos(const FIELDSYS_WORK * fsys, int *x, int *z);
static void GetFrontPos(const FIELDSYS_WORK * fsys, int * x, int * z);
static void GetMovePos(const FIELDSYS_WORK * fsys, int dir, int * x, int * z);
static u8 GetNowAttr(const FIELDSYS_WORK * fsys);
static u8 GetFrontAttr(const FIELDSYS_WORK * fsys);

static BOOL GetConnectData(const FIELDSYS_WORK * fsys, int x, int z, LOCATION_WORK * next);

static void SetEscapeData(FIELDSYS_WORK * fsys);

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * イベントチェックリクエストの初期化
 *
 * @param	req		イベントチェックリクエスト構造体
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearRequest( EV_REQUEST * req )
{
	req->TalkCheck  = FALSE;
	req->StepCheck  = FALSE;
	req->MenuOpen   = FALSE;
	req->CnvButton  = FALSE;
	req->MatCheck   = FALSE;
	req->PushCheck  = FALSE;
	req->MoveCheck  = FALSE;
	req->FloatCheck = FALSE;

	req->DebugMenu   = FALSE;
	req->DebugBattle = FALSE;

	req->DebugHook = FALSE;
	req->DebugKeyPush = FALSE;
	
	req->Site = DIR_NOT;
	req->PushSite = DIR_NOT;
}

//--------------------------------------------------------------------------------------------
/**
 * イベントチェックリクエストのセット
 *
 * @param	req		イベントチェックリクエスト構造体
 * @param	trg		キートリガー情報
 * @param	cont	キー押し情報
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetRequest( EV_REQUEST * req, FIELDSYS_WORK * repw, u16 trg, u16 cont )
{

	int	st;
	int	val;
	int dir;

	ClearRequest(req);

	st  = Player_MoveStateGet( repw->player );		// 自機の状態
	val = Player_MoveValueGet( repw->player );		// 自機の移動状態
	dir = Player_DirGet( repw->player );			// 自機の方向
	req->trg = trg;
	req->cont = cont;



	if( st == OBJ_MOVE_STATE_END || st == OBJ_MOVE_STATE_OFF ){
//		if( GetHeroMoveSpeed() != HERO_MOVE_SPEED_MAX ){
			if( trg & PAD_BUTTON_MENU ){
				req->MenuOpen = TRUE;
			}
			if( trg & PAD_BUTTON_BENRI ){
				req->CnvButton = TRUE;
			}
			if( trg & PAD_BUTTON_DECIDE ){
				req->TalkCheck = TRUE;
			}
			if( trg & PAD_BUTTON_CANCEL ){
				req->FloatCheck = TRUE;
			}
//		}
		if( cont & ALL_KEY ){
			req->MatCheck = TRUE;
		}
		if( cont & ALL_KEY ){
			req->PushCheck = TRUE;
		}
	}

	if( st == OBJ_MOVE_STATE_END && val == OBJ_MOVE_VALUE_WALK ){
		req->MoveCheck = TRUE;
	}

	// 一歩移動終了タイミングか？
	if (st == OBJ_MOVE_STATE_END) {
		req->StepCheck = TRUE;
	}

	if ((dir == DIR_UP && (cont & PAD_KEY_UP))
			|| ((dir == DIR_DOWN) && (cont & PAD_KEY_DOWN))
			|| ((dir == DIR_LEFT) && (cont & PAD_KEY_LEFT))
			|| ((dir == DIR_RIGHT) && (cont & PAD_KEY_RIGHT))
	   ) {
		req->PushSite = dir;
	} else {
		req->PushSite = DIR_NOT;
	}
	
//上下優先のとり方から自機独自のキー入力関数に変更 060317 kaga
#if 0
	// 移動方向のリクエスト
	if( cont & PAD_KEY_UP ){
		req->Site = DIR_UP;
	}else if( cont & PAD_KEY_DOWN ){
		req->Site = DIR_DOWN;
	}else if( cont & PAD_KEY_LEFT ){
		req->Site = DIR_LEFT;
	}else if( cont & PAD_KEY_RIGHT ){
		req->Site = DIR_RIGHT;
	}
#else
	req->Site = Player_KeyDirGet( repw->player, trg, cont );
#endif
	
	// 以下はデバッグ機能の発動チェック
#ifdef	PM_DEBUG
	if( cont & PAD_BUTTON_R ){
		req->DebugKeyPush = TRUE;
		
		//Rボタンを押しているときは各種イベントの発動を抑える
		req->MoveCheck = FALSE;
		req->StepCheck = FALSE;
		req->MatCheck = FALSE;
		req->PushCheck = FALSE;

		if( req->MenuOpen ){
			req->MenuOpen = FALSE;
			req->DebugMenu = TRUE;
		}
	}

/*
	if( st == OBJ_MOVE_STATE_END || st == OBJ_MOVE_STATE_OFF ){
		if( cont & PAD_BUTTON_R ){
			// デバッグバトル
			if( (cont & PAD_BUTTON_START) && !(req->DebugMenu) ){ 
				req->DebugBattle = TRUE;
			}
		}
	}
*/
#endif	// PM_DEBUG

}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @breif	草むらに入れないイベントチェック
 * @param	req		リクエスト構造体へのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @retval	TRUE	イベント発動した
 * @retval	FALSE	イベント発動しなかった
 *
 *
 * R201でのイベント専用。非常にきちゃない記述の関数なので
 * あとでもう少しまともな書き換えを考え中
 */
//--------------------------------------------------------------------------------------------
static BOOL GrassStepInCheck(const EV_REQUEST * req, FIELDSYS_WORK * fsys)
{
	int st  = Player_MoveStateGet( fsys->player );		// 自機の状態
	if (fsys->location->zone_id != ZONE_ID_R201) {
		return FALSE;
	}
	if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata)) == FALSE) {
		return FALSE;
	}
	if (st == OBJ_MOVE_STATE_OFF) {
#if 0	//自機の状態からキー入力を見る様にする 060317 kaga
		if (req->PushSite != DIR_NOT && MATR_IsGrass(GetFrontAttr(fsys))) {
			return TRUE;
		}
#elif 1
		{
			int val = Player_MoveValueGet( fsys->player );	//自機動作状態を取得
			
			if( (s8)req->Site != DIR_NOT &&					//キーが押されている
				val == OBJ_MOVE_VALUE_WALK ){				//自機の状態は移動である
				int x,z;
				GetMovePos( fsys, req->Site, &x, &z );		//移動先のアトリビュート取得
				if (MATR_IsGrass(GetAttributeLSB(fsys, x, z))) {
					return TRUE;
				}
			}else{
				if( (s8)req->PushSite != DIR_NOT &&			//自機の向きにキーが押されている
					MATR_IsGrass(GetFrontAttr(fsys))) {		//向きの先のアトリビュートを取得
					return TRUE;
				}
			}
		}
#endif
	} else if (st == OBJ_MOVE_STATE_END) {
		int x, z;
		GetMovePos(fsys, req->Site, &x, &z);
		if (MATR_IsGrass(GetAttributeLSB(fsys, x, z))) {
			return TRUE;
		}
	}
	
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * イベント起動チェック
 *
 * @param	req		イベントチェックリクエスト
 *
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 *
 *	リクエストを元にチェックプログラムを呼び出し、イベントを起動する
 */
//--------------------------------------------------------------------------------------------
int CheckRequest(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{

	//特殊スクリプト（シーン起動スクリプト）チェック
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}
	
	//トレーナー視線チェック
	{
		if( req->DebugKeyPush == FALSE ){
			BOOL flag = EvPoke_Enable2vs2Battle(SaveData_GetTemotiPokemon(repw->savedata));
			
			if( SysFlag_PairCheck(SaveData_GetEventWork(repw->savedata)) == 1 ){
				flag = TRUE;		//連れ歩き中ならダブル可能
			}
			
			if( EvTrainerEyeCheck(repw,flag) == TRUE ){
				Player_MoveStateClear( repw->player );
				FieldOBJSys_MovePauseAll( repw->fldobjsys );
				return TRUE;
			}
		}
	}
	
	//一歩移動チェック
	if (req->MoveCheck) {
		//一歩動いたかどうかフラグの更新
		SysFlag_OneStepReset( SaveData_GetEventWork(repw->savedata) );
		//IncRecord( CNT_WALK );
		if( CheckMoveEvent( repw ) == TRUE ){
			return TRUE;
		}
	}
	//草むらに入れないイベントチェック
	if (GrassStepInCheck(req, repw)) {
		EventSet_Script( repw, SCRID_POS_R201_STOP, NULL );
		return TRUE;
	}

	//自機イベントチェック
	{
		HERO_EVBIT evbit = HERO_EVBIT_NON;
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
		
		if (SysFlag_KairikiCheck( SaveData_GetEventWork(repw->savedata) )) {
			evbit |= HERO_EVBIT_PERMIT_KAIRIKI;
		}
		
		if( EvPoke_CheckWaza(SaveData_GetTemotiPokemon(repw->savedata),
					WAZANO_TAKINOBORI) != 0xff) {
			evbit |= HERO_EVBIT_PREMIT_TAKINOBORI;
		}
		
		if( Player_EventMoveCheck(repw,repw->player,dir,evbit) == TRUE ){
			return( TRUE );
		}
	}
	
	//自機動作チェック（一歩移動 あるいは 振り向き）
	if(req->StepCheck ){
		// エンカウント
		if (CheckEncountEvent(repw)) {
			return TRUE;
		}


		// 看板チェック
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	//方向転換でうまく動作しないので、ここでも看板チェック ( FR/LG のマネ )
	if( req->MatCheck && Player_DirGet(repw->player) == req->Site ){
		// 看板チェック
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	// 会話
	if( req->TalkCheck ){

		{	// OBJとの会話チェック
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;

				if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
					Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
				}
				if (FieldOBJ_EventTypeGet(obj) != EV_TYPE_MSG) {
					EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
				} else {
					EventSet_Script( repw, SCRID_COMMON_MSG, obj );
				}
				return TRUE;
			}
		}

		{	// BGの話しかけチェック
			int	id;
			
			id = TalkBgEventCheck(
					repw,
					(void *)EventData_GetNowBgTalkData( repw ),
					EventData_GetNowBgTalkDataSize( repw ) );

			if( id != EVENT_ID_NONE ){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}

		{	// 蜜塗り木チェック
			int id;
			if (HTE_CheckHoneyTree(repw,&id)){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}

		{
			int id;
			id = EvCheck_TalkMapAttr(repw, GetFrontAttr(repw));
			if (id != EVENT_ID_NONE) {
				EventSet_Script(repw, id, NULL);
				return TRUE;
			}

		}
	}

	if (req->PushCheck) {
		if (EvCheck_ExitByPush(repw, req) == TRUE) {
			SetEscapeData(repw);
			return TRUE;
		}
	}

	// 以下は、主人公の位置が無関係なイベント
	//
	// 便利ボタンチェック
	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	}

	// メニューチェック
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
        FieldMenuInit( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	// 戦闘テストへ
	if( req->DebugBattle ){
		DebugFieldEncount( repw );	//無条件でエンカウントセット
		return TRUE;
	}

	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板のイベント起動チェック
 * @param	reqw	フィールドデータ
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckBoardStart( FIELDSYS_WORK * repw )
{
	FIELD_OBJ_PTR obj;
	int	id;

	// OBJ看板チェック
	if( TalkAutoObjBoardEventCheck( repw, &obj ) == TRUE ){
		EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
		return TRUE;
	}

	// BG看板チェック
	id = TalkAutoBgBoardEventCheck(
			repw,(void *)EventData_GetNowBgTalkData(repw),EventData_GetNowBgTalkDataSize(repw));
	if( id != EVENT_ID_NONE ){
		EventSet_Script( repw, id, NULL );
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * 炭鉱時のイベント起動チェック  by k.ohno
 * @param	req		イベントチェックリクエスト
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 */
//--------------------------------------------------------------------------------------------

BOOL CheckRequestUG( EV_REQUEST * req, FIELDSYS_WORK * repw )
{
    u8 bTalkCheck = FALSE;
    //06.04.06 地下に初めて降りた時の強制イベント発動のために追加
	//特殊スクリプト（シーン起動スクリプト）チェック
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID()))){
        return FALSE;
    }
    UgMgrKeyCountDown();
    if( req->TalkCheck ){    // 会話--> 炭鉱専用メニュー
        UgMgrTalkCheck(bTalkCheck);
        return FALSE;
    }
    if( req->MenuOpen ){	// 主人公の位置が無関係なイベント
        UgMgrMenuCheck();
        return FALSE;
    }

    if(UgMgrTouchCheck()){ //タッチパネルの操作に関するもの
        return FALSE;
    }
	
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return FALSE;
	}
#endif	PM_DEBUG
	return FALSE;
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * 対戦部屋時のイベント起動チェック  by k.ohno
 * @param	req		イベントチェックリクエスト
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 */
//--------------------------------------------------------------------------------------------

BOOL CheckRequestVSRoom( EV_REQUEST * req, FIELDSYS_WORK * repw )
{
	if (req->PushCheck) {  // 出口
		if (req->PushSite == DIR_DOWN && MATR_IsDownMat(GetNowAttr(repw))) {
            EventSet_Script( repw, SCRID_BATTLE_ROOM_EXIT, NULL );
			return TRUE;
		}
	}
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID())) ||
       !CommDirectIsMoveState()){
        return FALSE;
    }
    
	// 会話  会話に関してはクライアントだけで処理が可能なので上と同じになる
    // ただしCommPlayerは除く
	if( req->TalkCheck ){
		{	// OBJとの会話チェック
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;
                if(MV_PLAYER != FieldOBJ_MoveCodeGet(obj)){ // 他のプレーヤーの場合
                    if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
                        Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
                    }
                    EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
                    return TRUE;
                }
			}
		}
	}
    if( req->TalkCheck ){    // 会話--> 
        EventCmd_VSRoomTrainer(repw);
        return TRUE;
    }
	// 便利ボタンチェック
/*	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	} */
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
	    FieldMenuInitVS( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return FALSE;
	}
#endif	PM_DEBUG
	return FALSE;
}


static int MyStatusCheck( void );

static int MyStatusCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;
	for(i=1;i<5;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return (result>=1);
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	ユニオンルーム専用イベント起動チェック
 * @param	req		イベントチェックリクエスト
 * @param	repw	ゲーム制御ワークへのポインタ
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 */
//--------------------------------------------------------------------------------------------
BOOL CheckRequestUnion(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{
	//話しかけられ
	//（追加予定）

	// 通信接続があった場合は絶対にイベントを開始させない
//	if(CommStateIsUnionParentConnectSuccess()){
	if(WH_GetBitmap()&0xfe){
		OS_Printf("接続中なので、イベントは発生させない bitmap=%02x status=%d connectnum=%d\n", WH_GetBitmap(), MyStatusCheck(), CommGetConnectNum());
		if(MyStatusCheck() && CommGetConnectNum()>1){

			// ●●に話しかけられました
			EventSet_Script( repw, SCRID_CONNECT_UNION_RECEIVE_OBJ, NULL );
			return TRUE;
		}
		return FALSE;
	}

	//ユニオンルームイベントチェック：会話（NPCへ）
	if( req->TalkCheck ){
		// OBJとの会話チェック
		FIELD_OBJ_PTR obj;
		if( TalkObjEventCheck( repw, &obj ) == TRUE ){
			if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
				Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
			}
            CommStateChildReserve(); // 子機としてつながるので親機にはならない
			EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
			return TRUE;
		}
	}

	//ユニオンルームイベントチェック：出入口
	if (req->MoveCheck && MATR_IsWarpPoint(GetNowAttr(repw))) {
		EventSet_UnionRoomMapChangeOut(repw);
		return TRUE;
	}

	//ユニオンルームイベントチェック：メニュー（デバッグ含む）
	//	便利ボタンがあるならばチェックはこのあたり
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
	    FieldMenuInitUnion( repw );

		// 今忙しいにビーコン書き換え
		Union_BeaconChange( UNION_PARENT_MODE_BUSY );	
		CommStateUnionPause();

		OS_TPrintf("MENU OPEN\n");
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * バトルタワー専用イベント起動チェック
 *
 * @param	req		イベントチェックリクエスト
 *
 * @retval	"TRUE = イベント発動"
 * @retval	"FALSE = イベント発動なし"
 *
 *	リクエストを元にチェックプログラムを呼び出し、イベントを起動する
 */
//--------------------------------------------------------------------------------------------
int CheckRequestBTower(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{

	//特殊スクリプト（シーン起動スクリプト）チェック
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}

#if 0
	//トレーナー視線チェック
	{
		if( req->DebugKeyPush == FALSE ){
			BOOL flag = EvPoke_Enable2vs2Battle(SaveData_GetTemotiPokemon(repw->savedata));
			
			if( SysFlag_PairCheck(SaveData_GetEventWork(repw->savedata)) == 1 ){
				flag = TRUE;		//連れ歩き中ならダブル可能
			}
			
			if( EvTrainerEyeCheck(repw,flag) == TRUE ){
				return TRUE;
			}
		}
	}
	
	//一歩移動チェック
	if (req->MoveCheck) {
		//一歩動いたかどうかフラグの更新
		SysFlag_OneStepReset( SaveData_GetEventWork(repw->savedata) );
		//IncRecord( CNT_WALK );
		if( CheckMoveEvent( repw ) == TRUE ){
			return TRUE;
		}
		//鋼ジムチェック
		if ( GYM_CheckSteelLift(repw) ){
			return TRUE;
		}
	}
	//草むらに入れないイベントチェック
	if (GrassStepInCheck(req, repw)) {
		EventSet_Script( repw, SCRID_POS_R201_STOP, NULL );
		return TRUE;
	}

	//自機イベントチェック
	{
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
		HERO_EVBIT evbit;
		evbit = HERO_EVBIT_NON;
		if (SysFlag_KairikiCheck( SaveData_GetEventWork(repw->savedata) )) {
			evbit |= HERO_EVBIT_PERMIT_KAIRIKI;
		}
		if( Player_EventMoveCheck(repw,repw->player,dir,evbit) == TRUE ){
			return( TRUE );
		}
	}
	
	//自機動作チェック（一歩移動 あるいは 振り向き）
	if(req->StepCheck ){
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
        if( JikiEventCheck_ArrowMat(repw,repw->player,dir) == TRUE ){
            return( TRUE );
        }
        
		// エンカウント
		if (CheckEncountEvent(repw)) {
			return TRUE;
		}


		// 看板チェック
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	//方向転換でうまく動作しないので、ここでも看板チェック ( FR/LG のマネ )
	if( req->MatCheck && Player_DirGet(repw->player) == req->Site ){
		// 看板チェック
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}
#endif
	// 会話
	if( req->TalkCheck ){

		{	// OBJとの会話チェック
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;

				if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
					Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
				}
				if (FieldOBJ_EventTypeGet(obj) != EV_TYPE_MSG) {
					EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
				} else {
					EventSet_Script( repw, SCRID_COMMON_MSG, obj );
				}
				return TRUE;
			}
		}

		{	// BGの話しかけチェック
			int	id;
			
			id = TalkBgEventCheck(
					repw,
					(void *)EventData_GetNowBgTalkData( repw ),
					EventData_GetNowBgTalkDataSize( repw ) );

			if( id != EVENT_ID_NONE ){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}
#if 0
		{	// 蜜塗り木チェック
			int id;
			if (HTE_CheckHoneyTree(repw,&id)){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}
#endif
		{
			int id;
			id = EvCheck_TalkMapAttr(repw, GetFrontAttr(repw));
			if (id != EVENT_ID_NONE) {
				EventSet_Script(repw, id, NULL);
				return TRUE;
			}

		}
	}

	if (req->PushCheck) {
		if (EvCheck_ExitByPush(repw, req) == TRUE) {
			return TRUE;
		}
	}

	// 以下は、主人公の位置が無関係なイベント
	//
	// 便利ボタンチェック
	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	}

	// メニューチェック
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
        FieldMenuInit( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}


//============================================================================================
//
//
//				イベント起動チェック：個別チェックルーチン
//
//
//============================================================================================

//------------------------------------------------------------------
//------------------------------------------------------------------
static BOOL CheckEncountEvent(FIELDSYS_WORK * fsys)
{
	int x, z;
	GetNowPos(fsys, &x, &z);
	if (SysFlag_PokeParkCheck(SaveData_GetEventWork(fsys->savedata)) == TRUE) {
		if (PokeParkSys_CheckEncount(fsys, x, z) == TRUE) {
			EventSet_PokeParkBattle(fsys, PokeParkSys_SetBattleParam(fsys));
			return TRUE;
		} else {
			return FALSE;
		}
	}
#ifdef	PM_DEBUG
	if( DebugFlagData.encount_flag == 0 &&
		ZoneData_GetEncountFlag(fsys->location->zone_id) &&
		FieldEncount_Check( fsys ) == TRUE) {
		return TRUE;
	}
#else
	// エンカウント
	if( ZoneData_GetEncountFlag(fsys->location->zone_id) &&
		FieldEncount_Check( fsys ) == TRUE) {
		return TRUE;
	}
#endif	PM_DEBUG
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	イベント起動チェック：出入口（押し込み）
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param	req		リクエスト構造体へのポインタ
 * @retval	TRUE	イベント起動あり
 * @retval	FALSE	イベント起動なし
 */
//------------------------------------------------------------------
static BOOL EvCheck_ExitByPush(FIELDSYS_WORK * fsys, const EV_REQUEST * req)
{
	int door_id;
	int x;
	int z;
	int dir;
	u8	attr;
	LOCATION_WORK cnct;

	//押し込み操作をしていない場合、チェックしない
	if (req->PushSite == DIR_NOT) {
		return FALSE;
	}

	//格闘ジムプッシュ判定
	if (GYM_CheckCombatWall(fsys)){
		return TRUE;
	}

	//進行方向一歩前が進行不能でない場合、チェックはしない
	GetFrontPos(fsys, &x, &z);
	if (GetHitAttr(fsys, x, z) == 0) {
		return FALSE;
	}

	//進行方向一歩前の出入口チェック
	if (GetConnectData(fsys, x, z, &cnct) && req->PushSite != DIR_NOT) {
		attr = GetAttributeLSB(fsys, x, z);
		if (MATR_IsDoor(attr)) {
			MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
							0, 0, req->PushSite, M_JUMP_DOOR);
			return TRUE;
		}
#ifdef	DEBUG_ALL_EXIT_CONNECT
		//2006.03.04
		//現状は、ドア以外でも接続が存在する場合はとりあえずつないでしまう。
		//そのうちちゃんとアトリビュートが入るので廃止する予定
		EventSet_EasyMapChange(fsys, cnct.zone_id, cnct.door_id,
				0,0, Player_DirGet(fsys->player));
		return TRUE;
#endif
	}

	//現在の足元位置の出入口チェック
	GetNowPos(fsys, &x, &z);

	// マットチェック
	attr = GetAttributeLSB( fsys, x, z );
	if( MATR_IsRightMat(attr)||MATR_IsRightNoArrowMat(attr) ){
		if( req->PushSite != DIR_RIGHT ){
			return FALSE;
		}
	}else if( MATR_IsLeftMat(attr)||MATR_IsLeftNoArrowMat(attr) ){
		if( req->PushSite != DIR_LEFT ){
			return FALSE;
		}
	}else if( MATR_IsDownMat(attr)||MATR_IsDownNoArrowMat(attr) ){
		if( req->PushSite != DIR_DOWN ){
			return FALSE;
		}
	}else if( MATR_IsRightStairs(attr) ){	//右階段
		if( req->PushSite != DIR_RIGHT ){
			return FALSE;
		}
	}else if( MATR_IsLeftStairs(attr) ){	//左階段
		if( req->PushSite != DIR_LEFT ){
			return FALSE;
		}
	}

	if (GetConnectData(fsys, x, z, &cnct) == FALSE) {
		return FALSE;
	}


	{
		int type;
		if (MATR_IsDoor(attr)){					//ドア
			type = M_JUMP_DOOR;
		}else if(MATR_IsRightStairs(attr)){		//階段
			type = M_JUMP_STAIRS;
		}else if(MATR_IsLeftStairs(attr)){		//階段
			type = M_JUMP_STAIRS;
		}else if (MATR_IsRightMat(attr) || MATR_IsRightNoArrowMat(attr)
				|| MATR_IsLeftMat(attr) || MATR_IsLeftNoArrowMat(attr)
				|| MATR_IsDownMat(attr) || MATR_IsDownNoArrowMat(attr)){
			MJUMP_ChangeMapByLocation(	fsys, cnct.zone_id, cnct.door_id,
										0, 0, req->PushSite);
			return TRUE;
		}else{
			return FALSE;
		}

		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, req->PushSite, type);
	}
	
	return TRUE;
}



//--------------------------------------------------------------------------------------------
/**
 * @brief	マップアトリビュート話しかけイベントチェック
 * @param	repw	ゲーム制御ワークへのポインタ
 * @param	matr	マップアトリビュートの値
 * @retval	EVENT_ID_NONE	
 * @retval	それ以外		スクリプトのID指定
 */
//--------------------------------------------------------------------------------------------
u16 EvCheck_TalkMapAttr(FIELDSYS_WORK * repw, MATR matr)
{
	int dir = Player_DirGet(repw->player);

	if (MATR_IsPC(matr) && dir == DIR_UP) {
		return SCRID_PC_ON;
	}else if (MATR_IsLittleBookRack01(matr)) {
		return SCRID_LITTLE_RACK1;
	}else if (MATR_IsLittleBookRack02(matr)) {
		return SCRID_LITTLE_RACK2;
	}else if (MATR_IsBookRack01(matr)) {
		return SCRID_RACK1;
	}else if (MATR_IsBookRack02(matr)) {
		return SCRID_RACK2;
	}else if (MATR_IsTrashBox(matr)) {
		return SCRID_TRASH_BOX;
	}else if (MATR_IsShopBookRack01(matr)) {
		return SCRID_SHOP_RACK1;
	}else if (MATR_IsShopBookRack02(matr)) {
		return SCRID_SHOP_RACK2;
	}else if (MATR_IsShopBookRack03(matr)) {
		return SCRID_SHOP_RACK3;
	}else if (MATR_IsWaterFall(matr)) {
		return SCRID_HIDEN_TAKINOBORI;
	}else if (MATR_IsMap(matr)) {
		return SCRID_TMAP_BG;
	}else if (MATR_IsBumpPost(matr)) {
		return SCRID_BUMP_POST;
	}else if (MATR_IsTV(matr) && dir == DIR_UP) {
		return SCRID_TV;
	}

	if( Player_EventAttrCheck_KabeNobori(matr,dir) ){
		return SCRID_HIDEN_KABENOBORI;
	}

	if( Player_FormGet(repw->player) != HERO_FORM_SWIM ){
		MYSTATUS * my = SaveData_GetMyStatus(repw->savedata);
		int	gx = Player_NowGPosXGet(repw->player);
		int	gz = Player_NowGPosZGet(repw->player);
		int	natr = GetAttributeLSB(repw, gx, gz);
		if( Player_EventAttrCheck_Naminori(repw->player,natr,matr)
				&& MyStatus_GetBadgeFlag(my, BADGE_ID_C05)){
			if( EvPoke_CheckWaza(SaveData_GetTemotiPokemon(repw->savedata),
						WAZANO_NAMINORI) != 0xff) {
				return SCRID_HIDEN_NAMINORI;
			}
		}
	}

	return EVENT_ID_NONE;
}

//-------------------------------------------------------------
/**
 * @brief	一歩ごとのイベント起動チェック
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param
 * 
 * @retval	BOOL		TRUE:発見	FALSE:ない
 */
//-------------------------------------------------------------
static BOOL CheckMoveEvent(FIELDSYS_WORK * fsys)
{
	u8	attr;
	int x,z;
	int dir;

	//鋼ジムチェック
	if ( GYM_CheckSteelLift(fsys) ){
		return TRUE;
	}
	
	//強制移動床チェック
	dir = Player_DirGet( fsys->player );
	if( JikiEventCheck_ArrowMat(fsys,fsys->player,dir) == TRUE ){
		return( TRUE );
	}
        
	x = Player_NowGPosXGet(fsys->player);
	z = Player_NowGPosZGet(fsys->player);
	
	attr = GetAttributeLSB( fsys, x, z );
	
	if ( CheckPosEvent(fsys) == TRUE ) return TRUE;		// 座標発動イベントチェック
	if ( CheckExit( fsys, x, z, attr) == TRUE ){
		SetEscapeData(fsys);
		return TRUE;	// 出入り口チェック
	}
///	if ( PosAttrCheck(attr) == TRUE ) return TRUE;		// アトリビュート発動チェック
	if ( Player_MoveBitCheck_Force(fsys->player) ) {
		//自機が強制移動中は歩数がかかわる処理はフックされる
		return FALSE;
	}

	Field_SendPoketchInfo( fsys, POKETCH_SEND_PEDOMATER, 1 );

	if ( CheckPoison( fsys ) == TRUE ) return TRUE;		// 毒ダメージ処理
	if ( CheckSafariStep(fsys) == TRUE ) return TRUE;	// サファリ歩数チェック
	if ( CheckSodateya( fsys )==TRUE ) return TRUE;		// 育て屋処理
	if ( CheckBtlSearcher( fsys )==TRUE ) return TRUE;	// バトルサーチャー処理
	if ( CheckPokeSearcher( fsys )==TRUE ) return TRUE;	// ポケサーチャー処理
///	if ( StepCountCheck(attr) == TRUE ) return TRUE;	// 歩数カウント関連チェック
	if ( CheckSpray( fsys ) == TRUE )	return	TRUE;	// スプレー処理チェック

	// 128歩歩くごとに1回なつきど計算
	if( CheckFriendCalcStepCount( fsys ) ){
		DoFriendCalcStepCount( fsys );
	}

	SysWork_ParkWalkCountPlus(SaveData_GetEventWork(fsys->savedata));
	return FALSE;
}

//-------------------------------------------------------------
/**
 * @brief	POSイベントチェック
 * @param	fsys	ゲーム制御ワークへのポインタ
 * 
 * @retval	BOOL		TRUE:発見	FALSE:ない
 */
//-------------------------------------------------------------
static BOOL CheckPosEvent(FIELDSYS_WORK * fsys)
{
	u16	id;
	id = PosEventCheck(
			fsys,
			(void *)EventData_GetNowPosEventData( fsys ),
			EventData_GetNowPosEventDataSize( fsys ) );
	if( id != EVENT_ID_NONE ){
		EventSet_Script( fsys, id, NULL );
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------
//	 出入り口のチェック＆データセット
//-------------------------------------------------------------
static BOOL CheckExit(FIELDSYS_WORK * fsys, const int x, const int z, const u8 inAttr)
{
	LOCATION_WORK cnct;

	if (GetConnectData(fsys, x, z, &cnct) == FALSE) {
		return FALSE;
	}
	
	//エスカレーター
	if( MATR_IsEscalator(inAttr) == TRUE ){
		int dir = Player_DirGet( fsys->player );
		if (dir == DIR_LEFT){	//左向き
			dir = DIR_RIGHT;	//フェードイン時は右向き
		}else if (dir == DIR_RIGHT){	//右向き
			dir = DIR_LEFT;	//フェードイン時は左向き
		}else{
			GF_ASSERT(0&&"自機の向きが不正");
			return FALSE;
		}
		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, dir, M_JUMP_ESCA);
		return TRUE;
	}else if ( MATR_IsEscalatorNonRet(inAttr) == TRUE ){
		int dir = Player_DirGet( fsys->player );
		if ( (dir!=DIR_LEFT)&&(dir!=DIR_RIGHT) ){
			GF_ASSERT( 0&&"自機の向きが不正" );
			return FALSE;
		}
		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, dir, M_JUMP_ESCA);
		return TRUE;
	}
	//上向き踏み込みマット
	if (MATR_IsUpMat(inAttr)||MATR_IsUpNoArrowMat(inAttr)){
		MJUMP_ChangeMapByLocation(	fsys, cnct.zone_id, cnct.door_id,
										0, 0, DIR_UP);
		return TRUE;
	}
    // ワープポイント
    if(MATR_IsWarpPoint(inAttr)){
        EventCmd_WarpPoint(fsys, cnct.zone_id, cnct.door_id);
		return TRUE;
    }
	
#ifdef	DEBUG_ALL_EXIT_CONNECT
	//2006.03.04
	//アトリビュートがないが出入口がある場合、とりあえずつなぐ
	//最終的にはこの処理は全てのアトリビュートがそろえば不要となる
	if (
			MATR_IsLeftStairs(inAttr) ||
			MATR_IsRightStairs(inAttr) ||
			MATR_IsDownMat(inAttr) ||
//			MATR_IsUpMat(inAttr) ||
			MATR_IsLeftMat(inAttr) ||
			MATR_IsRightMat(inAttr) ||
			MATR_IsDownNoArrowMat(inAttr) ||
//			MATR_IsUpNoArrowMat(inAttr) ||
			MATR_IsLeftNoArrowMat(inAttr) ||
			MATR_IsRightNoArrowMat(inAttr)) {
		//上にのって押し込むタイプのアトリビュートの場合は無視する
		return FALSE;
	}
	EventSet_EasyMapChange(fsys, cnct.zone_id, cnct.door_id,
			0,0, Player_DirGet(fsys->player));
	
	return TRUE;
#endif

/**	
			//温泉
			//隠し落とし穴
			//ワープポイント
			//落とし穴
			//OBJ位置保持ワープポイント
*/	

	return FALSE;
}

//==============================================================================
/**
 * $brief   育て屋チェック呼び出し
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckSodateya( FIELDSYS_WORK *fsys )
{
	POKEPARTY     *myparty  = SaveData_GetTemotiPokemon(fsys->savedata);
	SODATEYA_WORK *sodateya = SaveData_GetSodateyaWork(fsys->savedata);
	
	// 育て屋１歩歩き処理
	if (PokeSodateya( sodateya, myparty, fsys ) == TRUE) {
		RECORD *record = SaveData_GetRecord(fsys->savedata);
		
		// タマゴが生まれた回数を＋１
		RECORD_Inc( record, RECID_TAMAGO_HATCHING );
		// スコア加算
		RECORD_Score_Add( record, SCORE_ID_EGG_HATCHING );
		
		// タマゴが孵化したイベント発動
		EventSet_Script(fsys, SCRID_EGG_HATCHING, NULL);
		

		return TRUE;
	} else {
		return FALSE;
	}
}

//==============================================================================
/**
 * $brief   バトルサーチャーチェック呼び出し
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckBtlSearcher( FIELDSYS_WORK *fsys )
{
	BS_StepCountUp( fsys );
	return FALSE;
}

//==============================================================================
/**
 * $brief   ポケサーチャーチェック呼び出し
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckPokeSearcher( FIELDSYS_WORK *fsys )
{
	SwayGrass_ChargePokeSearcher(fsys);
	return FALSE;
}

//==============================================================================
/**
 * $brief   スプレー処理
 *
 * @param   fsys		
 *
 * @retval  BOOL		TRUEだったら、スプレー効果切れたメッセージ表示
 */
//==============================================================================
static BOOL CheckSpray( FIELDSYS_WORK *fsys )
{
	return Spray_DecSpray(fsys->savedata, fsys);
}

//----------------------------------------------------------------------------
/**
 *	@brief	連れ歩き　なつき度検査
 *
 *	@param	fsys	フィールドシステム
 *
 *	@retval	TRUE	なつき度計算する
 *	@retval	FALSE	なつき度計算しない
 */
//-----------------------------------------------------------------------------
static BOOL CheckFriendCalcStepCount( FIELDSYS_WORK *fsys )
{
	u16 step;
	EVENTWORK* ev;
	BOOL ret = FALSE;

	ev = SaveData_GetEventWork( fsys->savedata );
	step = SysWork_FriendlyStepCountGet( ev );
	step ++;
	if( step >= FRIENDCALC_STEP_MAX ){
		step = 0;
		ret = TRUE;
	}
	SysWork_FriendlyStepCountSet( ev, step );
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	なつき度計算を行う
 *
 *	@param	fsys	フィールドシステム
 */
//-----------------------------------------------------------------------------
static void DoFriendCalcStepCount( FIELDSYS_WORK *fsys )
{
	int i, max;
	POKEMON_PARAM * pp;
	POKEPARTY *party  = SaveData_GetTemotiPokemon(fsys->savedata);
	u16 placeID = ZoneData_GetPlaceNameID(fsys->location->zone_id);

	max = PokeParty_GetPokeCount(party);

	for( i=0; i<max; i++ ){
		pp = PokeParty_GetMemberPointer(party, i);
		FriendCalc( pp, FRIEND_TSUREARUKI, placeID );
	}
}



//==============================================================================
//==============================================================================
//-------------------------------------------------------------
/**
 * @brief	毒ダメージチェック
 * @param	fsys		フィールド制御データへのポインタ
 * @return	BOOL	TRUEのとき毒による死亡ダメージ発動
 *
 * 内部で毒エフェクトの呼び出しを行っている
 */
//-------------------------------------------------------------
static BOOL CheckPoison(FIELDSYS_WORK * fsys)
{
	POKEPARTY     *myparty  = SaveData_GetTemotiPokemon(fsys->savedata);
	u16 *poison_step = Situation_GetPoisonStepCount(SaveData_GetSituation(fsys->savedata));
	(*poison_step) ++;
	(*poison_step) %= POISON_STEP_MAX;
	if (*poison_step != 0) {
		return FALSE;
	}

	switch (EvPoke_PoisonDamage(myparty, ZoneData_GetPlaceNameID(fsys->location->zone_id))){
	case FLD_POISON_NODAMAGE:
		return FALSE;
	case FLD_POISON_DAMAGE:
		POISON_EFFE_Start(fsys->fldmap->poisoneffect);
		return FALSE;
	case FLD_POISON_DEAD:
		POISON_EFFE_Start(fsys->fldmap->poisoneffect);
		EventSet_Script(fsys, SCRID_POISON_DEAD, NULL);
		return TRUE;
	}
	return FALSE;
}
//==============================================================================
//==============================================================================
//-------------------------------------------------------------
/**
 * @brief	サファリ歩数チェック
 * @param	fsys		フィールド制御データへのポインタ
 * @return	BOOL	TRUEのとき歩数終了イベント発動
 *
 */
//-------------------------------------------------------------
static BOOL CheckSafariStep(FIELDSYS_WORK * fsys)
{
	u16 * safari_ball;
	u16 * safari_step;
	//サファリモードでなければチェックしない
	if (SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) == FALSE) {
		return FALSE;
	}

	safari_ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));
	if (*safari_ball == 0) {
		EventSet_Script(fsys, SCRID_SAFARI_ANNOUNCE_BALL, NULL);
		return TRUE;
	}

	safari_step = Situation_GetSafariStepCount(SaveData_GetSituation(fsys->savedata));
	(*safari_step) ++;
	OS_Printf("SAFARI STEP=%d\n",*safari_step);
	if (*safari_step >= 500) {
		EventSet_Script(fsys, SCRID_SAFARI_ANNOUNCE_TIME, NULL);
		return TRUE;
	}

	return FALSE;
}

//============================================================================================
//
//
//		イベント起動チェック用ツール関数
//
//
//============================================================================================
//-------------------------------------------------------------
//-------------------------------------------------------------
static void GetNowPos(const FIELDSYS_WORK * fsys, int *x, int *z)
{
	*x = Player_NowGPosXGet(fsys->player);
	*z = Player_NowGPosZGet(fsys->player);
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static void GetFrontPos(const FIELDSYS_WORK * fsys, int * x, int * z)
{
	int dir;
	dir = Player_DirGet(fsys->player);
	GetMovePos(fsys, dir, x, z);
}

//-------------------------------------------------------------
//-------------------------------------------------------------
static void GetMovePos(const FIELDSYS_WORK * fsys, int dir, int * x, int * z)
{
	GetNowPos(fsys, x, z);
	switch (dir) {
	case DIR_UP:
		*z -= 1;
		break;
	case DIR_DOWN:
		*z += 1;
		break;
	case DIR_LEFT:
		*x -= 1;
		break;
	case DIR_RIGHT:
		*x += 1;
		break;
	default:
		GF_ASSERT_MSG("自機の方向がおかしい\n",0);
	}
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static u8 GetNowAttr(const FIELDSYS_WORK * fsys)
{
	int x,z;
	GetNowPos(fsys, &x, &z);
	return GetAttributeLSB(fsys, x, z);
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static u8 GetFrontAttr(const FIELDSYS_WORK * fsys)
{
	int x,z;
	GetFrontPos(fsys, &x, &z);
	return GetAttributeLSB(fsys, x, z);
}


//-------------------------------------------------------------
/**
 * @brief	接続データの取得
 * @param	fsys		フィールド制御データへのポインタ
 * @param	x			接続データを探すX位置（グリッド単位）
 * @param	z			接続データを探すY位置（グリッド単位）
 * @retval	CONNECT_DATA	接続データのアドレス
 * @retval	NULL			接続データがなかった場合
 */
//-------------------------------------------------------------
static BOOL GetConnectData(const FIELDSYS_WORK * fsys, int x, int z,
		LOCATION_WORK * next)
{
	const CONNECT_DATA * connect;
	int door_id;
	door_id = EventData_SearchNowConnectIDByXZ(fsys, x, z);
	if (door_id == -1) {
		return FALSE;
	}
	connect = EventData_GetNowConnectDataByID(fsys, door_id);
	if (connect == NULL) {
		return FALSE;
	}
	if (connect->link_door_id == SPECIAL_SPEXIT01) {
		GF_ASSERT(connect->link_zone_id == ZONE_ID_SPECIAL);
		*next = *(Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata)));
	} else {
		SetLocation(next, connect->link_zone_id, connect->link_door_id,
				connect->x, connect->z, DIR_DOWN);
	}
	{
		//今入ることになる出入口の情報を覚えておく
		LOCATION_WORK * ent = Situation_GetEntranceLocation(SaveData_GetSituation(fsys->savedata));
		SetLocation(ent, fsys->location->zone_id, door_id, x, z, Player_DirGet(fsys->player));
	}
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * エスケープデータセット
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inX				復帰Ｘ座用
 * @param	inZ				復帰Ｚ座標
 * @param	inDir			入った時の向き
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetEscapeDataCore(FIELDSYS_WORK * fsys, const int inX, const int inZ, const int inDir)
{
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);
	(*escape) = *(fsys->location);
	escape->dir = inDir;
	escape->grid_x = inX;
	escape->grid_z = inZ;
	if (inDir == DIR_UP){
		(escape->grid_z)++;
	}
	escape->zone_id = fsys->location->zone_id;
	escape->door_id = DOOR_ID_JUMP_CODE;
}

//--------------------------------------------------------------------------------------------
/**
 * エスケープデータセット
 *
 * @param	fsys			フィールドシステムポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetEscapeData(FIELDSYS_WORK * fsys)
{
	int x,z;
	LOCATION_WORK cnct;
	
	GetNowPos(fsys, &x, &z);
	if ( GetConnectData(fsys, x, z, &cnct) ) {
		if (ZoneData_IsSinouField(fsys->location->zone_id) == TRUE
				&& ZoneData_IsSinouField(cnct.zone_id) == FALSE) {
			SetEscapeDataCore(fsys, x, z, Player_DirGet(fsys->player));
		}
	}else{
		GetFrontPos(fsys, &x, &z);
		if ( GetConnectData(fsys, x, z, &cnct) ) {
			if (ZoneData_IsSinouField(fsys->location->zone_id) == TRUE
					&& ZoneData_IsSinouField(cnct.zone_id) == FALSE) {
				SetEscapeDataCore(fsys, x, z, Player_DirGet(fsys->player));
			}
		}
	}
}

