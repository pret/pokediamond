//******************************************************************************
/**
 * 
 * @file	d_kaga.c
 * @brief	フィールドデバッグメニュー　かがや
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
//----
#ifdef PM_DEBUG
//----
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "player.h"

#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_kaga.h"

#include "field_cutin.h"
#include "field_fishing.h"
#include "field_ananuke.h"

#include "system/wipe.h"

//==============================================================================
//	define
//==============================================================================
#define HEAPID_D_KAGA (HEAPID_FIELD)

#define MENU_LIST_MAX (20)		//リスト数

#define MENU_X_CHAR_SIZE (12)	//横幅

#define MENU_Y_CHAR_ONE (2)		//１文字 2
#define MENU_Y_CHAR_SIZE (11*MENU_Y_CHAR_ONE)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
//	メニュー呼び出し関数
//--------------------------------------------------------------
typedef void (*MENU_PROC)(void*);

//--------------------------------------------------------------
//	メッセージリスト
//--------------------------------------------------------------
typedef struct{
	u32  str_id;
	u32  param;
}DEBUG_MENU_LIST;

//--------------------------------------------------------------
//	デバッグワーク
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	MENU_PROC select_func;
	FIELDSYS_WORK *fsys;
	GF_BGL_BMPWIN bmpwin;
	BMPLIST_WORK *bmplist;
	BMPLIST_DATA *menulist;
	MSGDATA_MANAGER* msgman;						//メッセージマネージャー
	WORDSET* wordset;								//単語セット
}D_KAGA_WORK;

//==============================================================================
//	プロトタイプ
//==============================================================================
void DebugKagayaMenuInit( FIELDSYS_WORK *fsys );
static void D_KagaMenuMain( TCB_PTR tcb, void *wk );
static void D_KagaMenuEnd( D_KAGA_WORK *work, TCB_PTR tcb );

static void * D_KagaAllocMemory( int size );
static void D_KagaFreeMemory( void *mem );

static const DEBUG_MENU_LIST DATA_MenuList[MENU_LIST_MAX];
static const BMPLIST_HEADER DATA_MenuListHeader;

//==============================================================================
//	デバッグメニュー
//==============================================================================
//--------------------------------------------------------------
///	メニュー初期化
//--------------------------------------------------------------
void DebugKagayaMenuInit( FIELDSYS_WORK *fsys )
{
	BMPLIST_HEADER	list_h;
	GF_BGL_INI *bgl = FieldBglIniGet( fsys );
	D_KAGA_WORK *work = D_KagaAllocMemory( sizeof(D_KAGA_WORK) );
	
	memset( work, 0, sizeof(D_KAGA_WORK) );
	
	work->fsys = fsys;
	
	GF_BGL_BmpWinAdd( bgl, &work->bmpwin, FLD_MBGFRM_FONT,
			1, 1, MENU_X_CHAR_SIZE, MENU_Y_CHAR_SIZE, 13, 1 );
	
	work->menulist = BMP_MENULIST_Create( NELEMS(DATA_MenuList), HEAPID_D_KAGA );
	
	work->wordset = WORDSET_Create( HEAPID_D_KAGA );
	
	work->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_kaga_dat, HEAPID_D_KAGA );
	{
		int i;
		
		for( i = 0; i < MENU_LIST_MAX; i++ ){
			BMP_MENULIST_AddArchiveString( work->menulist, work->msgman, 
							DATA_MenuList[i].str_id, DATA_MenuList[i].param );
		}
	}
	
	list_h = DATA_MenuListHeader;
	list_h.list = work->menulist;
	list_h.win = &work->bmpwin;
	work->bmplist = BmpListSet( &list_h, 0, 0, HEAPID_D_KAGA );
	
	GF_BGL_BmpWinOn( &work->bmpwin );
	TCB_Add( D_KagaMenuMain, work, 0 );
}

//--------------------------------------------------------------
//	メイン
//--------------------------------------------------------------
static void D_KagaMenuMain( TCB_PTR tcb, void *wk )
{
	u32 ret;
	D_KAGA_WORK *work = wk;
	
	switch( work->seq_no ){
	case 0:
		ret = BmpListMain( work->bmplist );
		
		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			D_KagaMenuEnd( work, tcb );
			FieldSystemProc_SeqHoldEnd();
			break;
		default:
			work->select_func = (MENU_PROC)ret;
			work->seq_no++;
		}
		
		break;
	case 1:
		work->select_func( work );
		D_KagaMenuEnd( work, tcb );
		FieldSystemProc_SeqHoldEnd();
		break;
	}
}

//--------------------------------------------------------------
//	メニュー終了
//--------------------------------------------------------------
static void D_KagaMenuEnd( D_KAGA_WORK *work, TCB_PTR tcb )
{
	MSGMAN_Delete( work->msgman );
	WORDSET_Delete( work->wordset );
	
	BMP_MENULIST_Delete( work->menulist );
	BmpListExit( work->bmplist, NULL, NULL );
	
	GF_BGL_BmpWinOff( &work->bmpwin );
	GF_BGL_BmpWinDel( &work->bmpwin );
	
	D_KagaFreeMemory( work );
	TCB_Delete( tcb );
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
//	メモリ確保
//--------------------------------------------------------------
static void * D_KagaAllocMemory( int size )
{
	void *mem = sys_AllocMemory( HEAPID_D_KAGA, size );
	memset( mem, 0, size );
	return( mem );
}

//--------------------------------------------------------------
//	メモリ開放
//--------------------------------------------------------------
static void D_KagaFreeMemory( void *mem )
{
	sys_FreeMemory( HEAPID_D_KAGA, mem );
}

//==============================================================================
//	アニメコマンドテスト
//==============================================================================
//--------------------------------------------------------------
///	コマンドテスト　ワーク
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	TCB_PTR tcb;
	FIELDSYS_WORK *fsys;
}D_ACMD_TEST_WORK;

//--------------------------------------------------------------
//	コードテーブル
//--------------------------------------------------------------
static const FIELD_OBJ_ACMD_LIST DATA_DEBUG_AcmdList[] =
{
	{AC_MARK_GYOE,1},{ACMD_END,0},
	
	{AC_JUMPHI_L_1G_16F,1},
	{AC_JUMPHI_R_1G_16F,1},
	{AC_JUMPHI_L_3G_32F,1},
	{AC_JUMPHI_R_3G_32F,1},
	{ACMD_END,0},
//	{AC_MARK_GYOE,1},{ACMD_END,0},
//	{AC_WARP_UP,1},{AC_WAIT_1F,16},{AC_WARP_DOWN,1},{ACMD_END,0},
	
	{AC_STAY_JUMP_U_16F,1},
//	{AC_DIR_PAUSE_ON,1},{AC_ANM_PAUSE_ON,1},
	{AC_STAY_JUMP_D_16F,1},{AC_STAY_JUMP_L_16F,1},{AC_STAY_JUMP_R_16F,1},
	{AC_STAY_JUMP_U_8F,1},{AC_STAY_JUMP_D_8F,1},{AC_STAY_JUMP_L_8F,1},{AC_STAY_JUMP_R_8F,1},
	{AC_JUMP_U_1G_8F,1},{AC_JUMP_D_1G_8F,2},{AC_JUMP_U_1G_8F,1},
	{AC_JUMP_L_1G_8F,1},{AC_JUMP_R_1G_8F,2},{AC_JUMP_L_1G_8F,1},
	{AC_JUMP_U_2G_16F,1},{AC_JUMP_D_2G_16F,2},{AC_JUMP_U_2G_16F,1},
	{AC_JUMP_L_2G_16F,1},{AC_JUMP_R_2G_16F,2},{AC_JUMP_L_2G_16F,1},
	{AC_STAY_JUMP_D_8F,1},{ACMD_END,0},
	
	{ACMD_END,0},
};

//--------------------------------------------------------------
//	コマンドテストイベント
//--------------------------------------------------------------
static BOOL D_KagaEvent_AcmdTest( GMEVENT_CONTROL *ev )
{
	D_ACMD_TEST_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->fsys->player );
	
	switch( work->seq_no ){
	case 0:
		if( FieldOBJ_AcmdListEndCheck(work->tcb) == FALSE ){
			break;
		}
		
		FieldOBJ_AcmdListEnd( work->tcb );
		D_KagaFreeMemory( work );
		OS_Printf( "コマンドテスト終了\n" );
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
//	コマンドテスト初期化
//--------------------------------------------------------------
static void D_KagaAcmdTestInit( D_KAGA_WORK *kaga )
{
	FIELD_OBJ_PTR fldobj;
	D_ACMD_TEST_WORK *work = D_KagaAllocMemory( sizeof(D_ACMD_TEST_WORK) );
	
	work->fsys = kaga->fsys;
	fldobj = Player_FieldOBJGet( work->fsys->player );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){
		D_KagaFreeMemory( work );
		OS_Printf( "コマンドテスト出来ません\n" );
		return;
	}
	
	work->tcb = FieldOBJ_AcmdListSet( fldobj, DATA_DEBUG_AcmdList );
	FieldEvent_Set( work->fsys, D_KagaEvent_AcmdTest, work );
	OS_Printf( "コマンドテスト開始\n" );
}

//==============================================================================
//	うつりこみ表示
//==============================================================================
//--------------------------------------------------------------
//	映り込み初期化
//--------------------------------------------------------------
static void D_KagaReflectInit( D_KAGA_WORK *kaga )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( kaga->fsys->player );
	FE_FldOBJReflect_Add( fldobj, REFTYPE_POOL );
	OS_Printf( "映り込みをセット\n" );
}

//==============================================================================
//	自機自由移動
//==============================================================================
//--------------------------------------------------------------
///	自由移動　ワーク
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
}D_JIKI_FREE_MOVE_WORK;

#define D_JIKI_FREE_MOVE_WORK_SIZE (sizeof(D_JIKI_FREE_MOVE_WORK))

#define FREE_X_SPEED (FX32_ONE * 2)
#define FREE_Z_SPEED (FX32_ONE * 2)
#define FREE_Y_SPEED (FX32_ONE * 2)
#define FREE_SPEED_UP (4)

//--------------------------------------------------------------
//	自由移動イベント
//--------------------------------------------------------------
static BOOL D_KagaEvent_FreeMove( GMEVENT_CONTROL *ev )
{
	D_JIKI_FREE_MOVE_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
	u16 trg = sys.trg;
	u16 prs = sys.cont;
	int speed = 1;
	VecFx32 vec;
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){
		return( FALSE );
	}
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	
	if( (trg & PAD_BUTTON_B) ){
		Player_HeightGet_ON_OFF( work->jiki, TRUE );
		D_KagaFreeMemory( work );
		OS_Printf( "自由移動終了\n" );
		return( TRUE );
	}
	
	if( (prs & PAD_BUTTON_R) ){
		speed = FREE_SPEED_UP;
	}
	
	if( (prs & PAD_BUTTON_Y) ){
		if( (prs & PAD_KEY_UP) ){
			vec.y -= FREE_Y_SPEED * speed;
			OS_Printf( "デバッグ自機高さ y = 0x%x, grid y = 0x%x\n",
					vec.y, SIZE_H_GRID_FX32(vec.y) );
		}else if( (prs & PAD_KEY_DOWN) ){
			vec.y += FREE_Y_SPEED * speed;
			OS_Printf( "デバッグ自機高さ y = 0x%x, grid y = 0x%x\n",
					vec.y, SIZE_H_GRID_FX32(vec.y) );
		}
		
		FieldOBJ_VecPosSet( fldobj, &vec );
	}else{
		int ac = ACMD_NOT;
		
		if( (prs & PAD_KEY_UP) ){
			if( speed == FREE_SPEED_UP ){ ac = AC_WALK_U_2F; }
			else{ ac = AC_WALK_U_8F; }
		}else if( (prs & PAD_KEY_DOWN) ){
			if( speed == FREE_SPEED_UP ){ ac = AC_WALK_D_2F; }
			else{ ac = AC_WALK_D_8F; }
		}else if( (prs & PAD_KEY_LEFT) ){
			if( speed == FREE_SPEED_UP ){ ac = AC_WALK_L_2F; }
			else{ ac = AC_WALK_L_8F; }
		}else if( (prs & PAD_KEY_RIGHT) ){
			if( speed == FREE_SPEED_UP ){ ac = AC_WALK_R_2F; }
			else{ ac = AC_WALK_R_8F; }
		}
		
		if( ac != ACMD_NOT ){
			FieldOBJ_AcmdSet( fldobj, ac );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
//	自由移動
//--------------------------------------------------------------
static void D_KagaJikiFreeMoveInit( D_KAGA_WORK *kaga )
{
	D_JIKI_FREE_MOVE_WORK *work = D_KagaAllocMemory( sizeof(D_ACMD_TEST_WORK) );
	
	work->fsys = kaga->fsys;
	work->jiki = kaga->fsys->player;
	
	Player_HeightGet_ON_OFF( work->jiki, FALSE );
	FieldEvent_Set( work->fsys, D_KagaEvent_FreeMove, work );
	OS_Printf( "自由移動開始\n" );
}

//==============================================================================
//	なみのり
//==============================================================================
//--------------------------------------------------------------
//	なみのり
//--------------------------------------------------------------
static void D_KagaNaminoriInit( D_KAGA_WORK *kaga )
{
	int dir = Player_DirGet( kaga->fsys->player );

#if 1
	Player_EventNaminoriStart( dir, kaga->fsys, kaga->fsys->player );
#else
	{
		PLAYER_STATE_PTR jiki = kaga->fsys->player;
		int gx = Player_NowGPosXGet( jiki );
		int gz = Player_NowGPosZGet( jiki );
		FE_FldOBJNamiPokeSet( Player_FieldOBJGet(jiki), gx, gz, dir, FALSE );
	}
#endif
	
	OS_Printf( "なみのり開始\n" );
}

/*
#ifndef DEBUG_NAMIPOKE_ROT
	if( (prs & DEBUG_WALK_PAD) == 0 ){
		return( FALSE );
	}
	
	if( (trg & PAD_BUTTON_SELECT) == 0 ){
		return( FALSE );
	}
	
	EOA_Delete( DEBUG_namipoke );
	DEBUG_namipoke = NULL;
	OS_Printf( "波乗りポケモンを削除\n" );
	return( FALSE );
#endif
	
#ifdef DEBUG_NAMIPOKE_ROT
	{
		int x=0,y=0,z=0;
		
		if( (prs & DEBUG_WALK_PAD) == 0 ){
			return( FALSE );
		}
		
		if( (prs & PAD_KEY_LEFT) ){ x = -4; }
		if( (prs & PAD_KEY_RIGHT) ){ x = 4; }
		if( (prs & PAD_KEY_UP) ){ y = -4; }
		if( (prs & PAD_KEY_DOWN) ){ y = 4; }
		if( (prs & PAD_BUTTON_B) ){ z = -4; }
		if( (prs & PAD_BUTTON_A) ){ z = 4; }
		
		DEBUG_NamiPoke_Rot( DEBUG_namipoke, x, y, z );
		return( TRUE );
	}
#endif	
*/

//==============================================================================
//	電灯
//==============================================================================
static void D_KagaCutInEndCheck( TCB_PTR tcb, void *work );

typedef struct
{
	TCB_PTR tcb_cutin;
}D_KAGA_CUTIN_WORK;

//--------------------------------------------------------------
//	電灯テスト
//--------------------------------------------------------------
static void D_KagaELightInit( D_KAGA_WORK *kaga )
{
	TCB_PTR tcb;
	POKEMON_PARAM *param = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(kaga->fsys->savedata), 0 );
	D_KAGA_CUTIN_WORK *work = sys_AllocMemoryLo( HEAPID_FIELD, sizeof(D_KAGA_CUTIN_WORK) );
	
	work->tcb_cutin = FieldCutIn_Init(
		kaga->fsys, CUTIN_TYPE_HIDEN, param, Player_SexGet(kaga->fsys->player) );
	
	TCB_Add( D_KagaCutInEndCheck, work, 0xff );
}

//--------------------------------------------------------------
//　カットイン終了監視TCB
//--------------------------------------------------------------
static void D_KagaCutInEndCheck( TCB_PTR tcb, void *wk )
{
	D_KAGA_CUTIN_WORK *work = wk;
	
	if( FieldCutIn_EndCheck(work->tcb_cutin) == TRUE ){
		FieldCutIn_End( work->tcb_cutin );
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
	}
}

#if 0
static void D_KagaELightInit( D_KAGA_WORK *kaga )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( kaga->fsys->player );
	FE_FldOBJELight_Add( fldobj );
	OS_Printf( "電灯表示\n" );
}
#endif

//==============================================================================
//	ゆきだま
//==============================================================================
//--------------------------------------------------------------
///	雪玉
//--------------------------------------------------------------
static void D_KagaSnowBallInit( D_KAGA_WORK *kaga )
{
	PLAYER_STATE_PTR jiki = kaga->fsys->player;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int dir = Player_DirGet( jiki );
	int gx = Player_NowGPosXGet( jiki ) + FieldOBJ_DirAddValueGX( dir );
	int gz = Player_NowGPosZGet( jiki ) + FieldOBJ_DirAddValueGZ( dir );
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	FIELD_OBJ_PTR front_obj = FieldOBJ_SearchGPos( fos, gx, gz );
		
	if( front_obj == NULL ){
		FieldOBJ_AddHMake( fos, gx, gz, dir, SNOWBALL, MV_DMY, 0 );
		OS_Printf( "雪玉を埋めました\n" );
	}else{
		OS_Printf( "OBJがいる為雪玉配置不可\n" );
	}
}

//==============================================================================
//	じてんしゃ
//==============================================================================
//--------------------------------------------------------------
///	自転車
//--------------------------------------------------------------
static void D_KagaJikiCycleInit( D_KAGA_WORK *kaga )
{
	PLAYER_STATE_PTR jiki = kaga->fsys->player;
	
	if( Player_FormGet(jiki) == HERO_FORM_CYCLE ){
		Player_RequestSet( jiki, HERO_REQBIT_NORMAL );
	}else{
		Player_RequestSet( jiki, HERO_REQBIT_CYCLE );
	}
}

//==============================================================================
//	かべのぼり
//==============================================================================
//--------------------------------------------------------------
///	かべのぼり
//--------------------------------------------------------------
static void D_KagaKabeNoboriInit( D_KAGA_WORK *kaga )
{
	int dir = Player_DirGet( kaga->fsys->player );
#if 1
	Player_EventKabeNoboriStart( dir, kaga->fsys, kaga->fsys->player );
	OS_Printf( "壁上り開始\n" );
#else
	{
		PLAYER_STATE_PTR jiki = kaga->fsys->player;
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		int gx = Player_NowGPosXGet( jiki );
		int gz = Player_NowGPosZGet( jiki );
		int dir = Player_DirGet( jiki );
		EOA_PTR eoa = FE_FldOBJRockRidePoke_Add( fldobj, gx, gz, dir, FALSE );
	}
#endif
}

//==============================================================================
//	つれあるき
//==============================================================================
//--------------------------------------------------------------
///	連れ歩き
//--------------------------------------------------------------
static void D_KagaTureInit( D_KAGA_WORK *kaga )
{
	PLAYER_STATE_PTR jiki = kaga->fsys->player;
	int gx = Player_NowGPosXGet( jiki );
//	int gz = Player_NowGPosZGet( jiki ) + GRID_ONE;
	int gz = Player_NowGPosZGet( jiki );
	int dir = DIR_DOWN;
	FIELD_OBJ_PTR fldobj = FieldOBJ_AddHMake(
		kaga->fsys->fldobjsys, gx, gz, dir, BABYBOY1, MV_PAIR, 0 );
}

//==============================================================================
//	みずやり
//==============================================================================
//--------------------------------------------------------------
///	みずやり
//--------------------------------------------------------------
static void D_KagaWaterInit( D_KAGA_WORK *kaga )
{
	u32 code;
	PLAYER_STATE_PTR jiki = kaga->fsys->player;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( code == WATERHERO || code == WATERHEROINE ){
		Player_RequestSet( jiki, HERO_REQBIT_NORMAL );
	}else{
		Player_RequestSet( jiki, HERO_REQBIT_WATER );
	}
	
	Player_Request( jiki );
}

//==============================================================================
//	滝登り
//==============================================================================
//--------------------------------------------------------------
///	滝登り
//--------------------------------------------------------------
static void D_KagaTakiNoboriInit( D_KAGA_WORK *kaga )
{
	int dir = Player_DirGet( kaga->fsys->player );
	
	if( dir == DIR_UP || dir == DIR_DOWN ){
		Player_EventTakiNoboriStart( kaga->fsys, dir );
		OS_Printf( "滝上り開始\n" );
	}else{
		OS_Printf( "滝登り　方向が違う\n" );
	}
}

//==============================================================================
//	サイクリングロード
//==============================================================================
//--------------------------------------------------------------
///	サイクリングロード
//--------------------------------------------------------------
static void D_KagaCyclingRoadInit( D_KAGA_WORK *kaga )
{
	PLAYER_STATE_PTR jiki = kaga->fsys->player;
	
	if( Player_MoveBitCheck_CyclingRoad(jiki) == TRUE ){
		Player_MoveBitSet_CyclingRoad( jiki, FALSE );
	}else{
		Player_MoveBitSet_CyclingRoad( jiki, TRUE );
	}
}

//==============================================================================
//	ダッシュフラグ
//==============================================================================
//--------------------------------------------------------------
///	ダッシュフラグ
//--------------------------------------------------------------
static void D_KagaDashFlagInit( D_KAGA_WORK *kaga )
{
	PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( kaga->fsys->player );
	Player_SaveDataDashSet( save, TRUE );
}

//==============================================================================
//	コンテスト着替え
//==============================================================================
//--------------------------------------------------------------
///	コンテスト着替え
//--------------------------------------------------------------
static void D_KagaContestChangeInit( D_KAGA_WORK *kaga )
{
	Player_EventContestHeroChangeStart( kaga->fsys );
}

//==============================================================================
//	つり
//==============================================================================
//--------------------------------------------------------------
///	つり発動
//--------------------------------------------------------------
static void D_KagaFishingInit( D_KAGA_WORK *kaga )
{
	void *work = EventWorkSet_Fishing( kaga->fsys, HEAPID_D_KAGA, FISHINGROD_GREAT );
	FieldEvent_Set( kaga->fsys, GMEVENT_Fishing, work );
}

//==============================================================================
//	あなぬけ
//==============================================================================
//--------------------------------------------------------------
///	穴抜け発動
//--------------------------------------------------------------
static void D_KagaAnanukeInit( D_KAGA_WORK *kaga )
{
	void *work = EventWorkSet_AnanukeMapChange( kaga->fsys, HEAPID_D_KAGA );
	FieldEvent_Set( kaga->fsys, GMEVENT_AnanukeMapChange, work );
}

//==============================================================================
//	あなほり
//==============================================================================
//--------------------------------------------------------------
///	あなほり発動
//--------------------------------------------------------------
static void D_KagaAnawohoruInit( D_KAGA_WORK *kaga )
{
	POKEMON_PARAM *param = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(kaga->fsys->savedata), 0 );
	void *work = EventWorkSet_AnawohoruMapChange( kaga->fsys, param, HEAPID_D_KAGA );
	FieldEvent_Set( kaga->fsys, GMEVENT_AnawohoruMapChange, work );
}

//==============================================================================
//	テレポート
//==============================================================================
//--------------------------------------------------------------
///	テレポート発動
//--------------------------------------------------------------
static void D_KagaTeleportInit( D_KAGA_WORK *kaga )
{
	POKEMON_PARAM *param = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(kaga->fsys->savedata), 0 );
	void *work = EventWorkSet_TeleportMapChange( kaga->fsys, param, HEAPID_D_KAGA );
	FieldEvent_Set( kaga->fsys, GMEVENT_TeleportMapChange, work );
}

//==============================================================================
//	スロット
//==============================================================================
static void D_KagaSlotChangeTCB( TCB_PTR tcb, void *work );

//--------------------------------------------------------------
//	SLOTCHG
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	FIELDSYS_WORK *fsys;
}SLOTCHG;

//--------------------------------------------------------------
///	スロット発動
//--------------------------------------------------------------
static void D_KagaSlotInit( D_KAGA_WORK *kaga )
{
	SLOTCHG *work = sys_AllocMemory( HEAPID_WORLD, sizeof(SLOTCHG) );
	memset( work, 0, sizeof(SLOTCHG) );
	work->fsys = kaga->fsys;
	TCB_Add( D_KagaSlotChangeTCB, work, 0xffff );
}

//--------------------------------------------------------------
///	スロット移行 tcb
//--------------------------------------------------------------
static void D_KagaSlotChangeTCB( TCB_PTR tcb, void *wk )
{
	SLOTCHG *work = wk;
	
	switch( work->seq_no ){
	case 0:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				0,
				8,2,
				HEAPID_FIELD );
		work->seq_no++;
		break;
	case 1:
		if( WIPE_SYS_EndCheck() == 0 ){
			break;
		}
		
		FieldSlot_SetProc( work->fsys, NULL );
		work->seq_no++;
	case 2:
		if( GameSystem_CheckSubProcExists(work->fsys) == FALSE ){
			GameSystem_CreateFieldProc( work->fsys );
			work->seq_no++;
		}
		break;
	case 3:
		if( GameSystem_CheckFieldProcExists(work->fsys) ){
			WIPE_SYS_Start( 
					WIPE_PATTERN_FSAM,
					WIPE_TYPE_FADEIN,
					WIPE_TYPE_FADEIN,
					WIPE_FADE_OUTCOLOR,
					8,2,
					HEAPID_FIELD );
			work->seq_no++;
		}
		break;
	case 4:
		if( WIPE_SYS_EndCheck() ){
			sys_FreeMemoryEz( work );
			TCB_Delete( tcb );
		}
	}
}

//==============================================================================
//	data
//==============================================================================
static const DEBUG_MENU_LIST DATA_MenuList[MENU_LIST_MAX] =
{
	{ debug_kaga_msg_00, (u32)D_KagaAcmdTestInit },
	{ debug_kaga_msg_01, (u32)D_KagaReflectInit },
	{ debug_kaga_msg_02, (u32)D_KagaJikiFreeMoveInit },
	{ debug_kaga_msg_03, (u32)D_KagaNaminoriInit },
	{ debug_kaga_msg_04, (u32)D_KagaELightInit },
	{ debug_kaga_msg_05, (u32)D_KagaSnowBallInit },
	{ debug_kaga_msg_06, (u32)D_KagaJikiCycleInit },
	{ debug_kaga_msg_07, (u32)D_KagaKabeNoboriInit },
	{ debug_kaga_msg_08, (u32)D_KagaTureInit },
	{ debug_kaga_msg_09, (u32)D_KagaWaterInit },
	{ debug_kaga_msg_10, (u32)D_KagaTakiNoboriInit },
	{ debug_kaga_msg_11, (u32)D_KagaCyclingRoadInit },
	{ debug_kaga_msg_12, (u32)D_KagaDashFlagInit },
	{ debug_kaga_msg_13, (u32)D_KagaContestChangeInit },
	{ debug_kaga_msg_14, (u32)D_KagaELightInit },
	{ debug_kaga_msg_15, (u32)D_KagaFishingInit },
	{ debug_kaga_msg_16, (u32)D_KagaAnanukeInit },
	{ debug_kaga_msg_17, (u32)D_KagaAnawohoruInit },
	{ debug_kaga_msg_18, (u32)D_KagaTeleportInit},
	{ debug_kaga_msg_19, (u32)D_KagaSlotInit},
};

static const BMPLIST_HEADER DATA_MenuListHeader =
{
	NULL,			// 表示文字データポインタ
	NULL,					// カーソル移動ごとのコールバック関数
	NULL,					// 一列表示ごとのコールバック関数
	NULL,
	NELEMS(DATA_MenuList),	// リスト項目数
	11,						// 表示最大項目数
	0,						// ラベル表示Ｘ座標
	12,						// 項目表示Ｘ座標
	0,						// カーソル表示Ｘ座標
	0,						// 表示Ｙ座標
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						// 文字間隔Ｘ
	16,						// 文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
	FONT_SYSTEM,			// 文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//----
#endif	//PM_DEBUG
//----
