//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		scr_nagisa_scope.c
 *	@brief		ナギサシティ　灯台望遠鏡
 *	@author		tomoya takahashi
 *	@data		2006.07.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "map_jump.h"		//for wipe
#include "fieldmap_work.h"	//for hblamk wipe
#include "sysflag.h"

#include "fielddata/maptable/zone_id.h"

#include "fld_flg_init.h"


#define __SCR_NAGISA_SCOPE_H_GLOBAL
#include "scr_nagisa_scope.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define WAIT_KEY	( PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	スコープデータ
//=====================================
typedef struct
{
	FIELDSYS_WORK * fsys;
	u16 pos_x;	// 戻り先X
	u16 pos_z;	// 戻り先Z

	u8 seq;
	u8 dummy[3];
}SCOPE_EVENT_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NagisaScope( GMEVENT_CONTROL * event );
static void NagisaScope_PlayerVanish( PLAYER_STATE_PTR jiki, BOOL vanish );
static void NagisaScope_CameraSet( FIELDSYS_WORK* p_fsys );


//----------------------------------------------------------------------------
/**
 *	@brief	ナギサシティ　望遠鏡　イベントコール
 *
 *	@param	fsys	フィールドシステム
 */
//-----------------------------------------------------------------------------
void CallNagisaScopeEvent(FIELDSYS_WORK * fsys)
{
	SCOPE_EVENT_WORK * sew = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SCOPE_EVENT_WORK));

	memset( sew, 0, sizeof(SCOPE_EVENT_WORK) );
	
	//マップジャンプイベントを作成
	FieldEvent_Call(fsys->event, GMEVENT_NagisaScope, sew);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ナギサシティー　望遠鏡　イベント
 *
 *	@param	event	イベントポインタ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NagisaScope( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	SCOPE_EVENT_WORK * p_work = FieldEvent_GetSpecialWork(event);
	EVENTWORK* p_sv_event = SaveData_GetEventWork( p_fsys->savedata );

	switch( p_work->seq ){
	case 0:
		// 自分の位置を保存
		p_work->pos_x = Player_NowGPosXGet( p_fsys->player );
		p_work->pos_z = Player_NowGPosZGet( p_fsys->player );

		// 望遠鏡ﾓｰﾄﾞ設定
		FldFlg_SetScopeMode( p_fsys, TRUE );

		// フェードアウト
		EventCmd_FieldFadeOut(event);			//フェードアウト
		p_work->seq ++;
		break;

	case 1:	// フィールドプロセス	終了
		EventCmd_FinishFieldMap(event);
		p_work->seq ++;
		break;

	case 2:	// マップ遷移
		// ポケッチOFF
		SysFlag_PoketchHookSet( p_sv_event );
		{
			LOCATION_WORK location;
			SetLocation( &location, ZONE_ID_C10, DOOR_ID_JUMP_CODE, 847, 561, DIR_DOWN );
			EventCmd_MapChangeByLocation(event, &location);
		}
		p_work->seq ++;
		break;

	case 3:	// フィールド開始
		EventCmd_StartFieldMap(event);
		p_work->seq ++;
		break;

	case 4:	// ワイプIN
		NagisaScope_PlayerVanish( p_fsys->player, TRUE );
		NagisaScope_CameraSet( p_fsys );
		MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEIN,
					0xffff,0x0000,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_WORLD);
		Snd_SePlay( SEQ_SE_DP_KASYA );		//覗いたときの音

		p_work->seq ++;
		break;

	case 5:	// キー待ち
		if( (sys.trg & WAIT_KEY) ){
			p_work->seq ++;
		}
		break;

	case 6:	// ワイプアウト
		MJUMP_RequestWipe( event,WIPE_PATTERN_M, WIPE_TYPE_HOLEOUT,
					0xffff,0x0000,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_WORLD);
		Snd_SePlay( SEQ_SE_DP_KASYA );		//閉じたときの音

		p_work->seq ++;
		break;

	case 7:
		EventCmd_FinishFieldMap(event);
		p_work->seq ++;
		break;

	case 8:	// 画面復帰
		// ポケッチOFF
		SysFlag_PoketchHookReset( p_sv_event );
		{
			LOCATION_WORK location;
			SetLocation( &location, ZONE_ID_C08R0801,DOOR_ID_JUMP_CODE,p_work->pos_x,p_work->pos_z,DIR_UP );
			EventCmd_MapChangeByLocation(event, &location);
		}
		p_work->seq ++;
		break;

	case 9:
		EventCmd_StartFieldMap(event);
		p_work->seq ++;
		break;

	case 10:
		NagisaScope_PlayerVanish( p_fsys->player, FALSE );
		EventCmd_FieldFadeIn(event);		//フェードイン
		p_work->seq ++;
		break;

	case 11:	// 終了処理
		sys_FreeMemoryEz( p_work );

		// 望遠鏡ﾓｰﾄﾞ設定
		FldFlg_SetScopeMode( p_fsys, FALSE );
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	プレイヤーのバニッシュ
 *
 *	@param	jiki	プレイヤー
 *	@param	vanish	TRUE	非表示
 */
//-----------------------------------------------------------------------------
static void NagisaScope_PlayerVanish( PLAYER_STATE_PTR jiki, BOOL vanish )
{
	FIELD_OBJ_PTR player = Player_FieldOBJGet( jiki );
	FieldOBJ_StatusBitSet_Vanish( player, vanish );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カメラ設定
 */
//-----------------------------------------------------------------------------
static void NagisaScope_CameraSet( FIELDSYS_WORK* p_fsys )
{
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0x8c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xf81b8, p_fsys->camera_ptr );
	matrix.x = 0x350523d;
	matrix.y = 0x15edb7;
	matrix.z = 0x23da40e;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x823;
	angle.y = 0x520;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );
	GFC_SetCameraClip( 12*FX32_ONE, 1564*FX32_ONE, p_fsys->camera_ptr );
}
