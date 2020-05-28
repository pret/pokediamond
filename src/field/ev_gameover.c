//============================================================================================
/**
 * @file	ev_gameover.c
 * @brief
 * @date	2006.04.18
 * @author	tamada GAME FREAK inc.
 *
 * scr_tool.c,field_encount.cからゲームオーバー処理を持ってきて再構成した
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"

#include "ev_mapchange.h"

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "system/window.h"
#include "system/wipe.h"

#include "mapdata_warp.h"			//WARPDATA_GetRevivalLocation
#include "situation_local.h"		//Situation_Get～
#include "system/brightness.h"
#include "script.h"
#include "scr_tool.h"
#include "mapdefine.h"
#include "..\fielddata\script\common_scr_def.h"		//SCRID_GAME_OVER_RECOVER_PC
#include "sysflag.h"
#include "fld_flg_init.h"			//FldFlgInit_GameOver

//==============================================================================================
//
//	全滅関連
//
//==============================================================================================
#include "system/fontproc.h"						
#include "system/msgdata.h"							//MSGMAN_TYPE_DIRECT
#include "system/wordset.h"							//WORDSET_Create

#include "fld_bmp.h"						

#include "msgdata/msg.naix"							//NARC_msg_??_dat
#include "msgdata/msg_gameover.h"					//msg_all_dead_??

#include "system/arc_util.h"
#include "system/font_arc.h"

//----------------------------------------------------------------------------------------------
//	構造体宣言
//----------------------------------------------------------------------------------------------
typedef struct{
	int seq;

	FIELDSYS_WORK* fsys;

	GF_BGL_INI* bgl;								//BGLデータ

	GF_BGL_BMPWIN bmpwin;							//BMPウィンドウデータ

	//STRBUF* msg_buf[EV_WIN_MENU_MAX];				//メッセージデータのポインタ
	MSGDATA_MANAGER* msgman;						//メッセージマネージャー
	WORDSET* wordset;								//単語セット

	//PALETTE_FADE_PTR pfd;							//パレットフェード
}GAME_OVER_WORK;

#define GAME_OVER_MSG_BUF_SIZE		(1024)			//メッセージバッファサイズ
#define GAME_OVER_FADE_SYNC			(8)				//フェードsync数

//----------------------------------------------------------------------------------------------
//	BMPウィンドウ
//----------------------------------------------------------------------------------------------
enum{
	GAME_OVER_BMPWIN_FRAME	= GF_BGL_FRAME3_M,
	//GAME_OVER_BMPWIN_PX1	= 1,//2,
	//GAME_OVER_BMPWIN_PY1	= 1,//2,
	//GAME_OVER_BMPWIN_SX		= 29,//25,
	//GAME_OVER_BMPWIN_SY		= 19,//18,
	GAME_OVER_BMPWIN_PX1	= 4,
	GAME_OVER_BMPWIN_PY1	= 5,
	GAME_OVER_BMPWIN_SX		= 25,
	GAME_OVER_BMPWIN_SY		= 15,
	GAME_OVER_BMPWIN_PL		= FLD_SYSFONT_PAL,
	GAME_OVER_BMPWIN_CH		= 1,
};

static const BMPWIN_DAT	GameOverWinData = {
	GAME_OVER_BMPWIN_FRAME,						//ウインドウ使用フレーム
	GAME_OVER_BMPWIN_PX1,GAME_OVER_BMPWIN_PY1,	//ウインドウ領域の左上のX,Y座標（キャラ単位で指定）
	GAME_OVER_BMPWIN_SX, GAME_OVER_BMPWIN_SY,	//ウインドウ領域のX,Yサイズ（キャラ単位で指定）
	GAME_OVER_BMPWIN_PL,						//ウインドウ領域のパレットナンバー	
	GAME_OVER_BMPWIN_CH							//ウインドウキャラ領域の開始キャラクタナンバー
};

//----------------------------------------------------------------------------------------------
//	プロトタイプ宣言
//----------------------------------------------------------------------------------------------
static void GameOverCall( FIELDSYS_WORK* fsys, GMEVENT_CONTROL* event );
static BOOL GMEVENT_GameOver( GMEVENT_CONTROL* event );
static void scr_msg_print( GAME_OVER_WORK* wk, u16 msg_id, u8 x, u8 y );

static void SetBgHeader( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini );


static void setup_bg_sys( GF_BGL_INI* bgl )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GF_Disp_SetBank( &SetBankData );
	GF_BGL_InitBG( &BGsys_data );
	GF_BGL_BGControlSet( bgl, GAME_OVER_BMPWIN_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_PalSet( ARC_FONT, NARC_font_system_ncrl, PALTYPE_MAIN_BG, 
		GAME_OVER_BMPWIN_PL*0x20, 0x20, HEAPID_WORLD );
}

//--------------------------------------------------------------
/**
 * @brief	ゲームオーバー画面呼び出し
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GameOverCall( FIELDSYS_WORK* fsys, GMEVENT_CONTROL* event )
{
	GAME_OVER_WORK* wk;

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(GAME_OVER_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "メモリ確保に失敗しました！" );
	}
	memset( wk, 0, sizeof(GAME_OVER_WORK) );

	wk->seq			= 0;
	wk->fsys		= fsys;
	wk->bgl 		= GF_BGL_BglIniAlloc( HEAPID_WORLD );

	setup_bg_sys( wk->bgl );

	//メッセージデータマネージャー作成
	wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_gameover_dat, HEAPID_WORLD);
	wk->wordset = WORDSET_Create( HEAPID_WORLD );

	//ビットマップ追加
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin, &GameOverWinData );

	//主人公名セット
	WORDSET_RegisterPlayerName(wk->wordset, 0, SaveData_GetMyStatus(GameSystem_GetSaveData(fsys)));

	//マップ管理表からBGMナンバーを返す
	if( fsys->location->zone_id == ZONE_ID_T01R0201 ){
		OS_Printf( "05 zone_id = %d\n", fsys->location->zone_id );
		scr_msg_print( wk, msg_all_dead_05, 0, 0 );
	}else{
		OS_Printf( "04 zone_id = %d\n", fsys->location->zone_id );
		scr_msg_print( wk, msg_all_dead_04, 0, 0 );
	}

	GF_BGL_BmpWinOn( &wk->bmpwin );

	FieldEvent_Call( event, GMEVENT_GameOver, wk );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ゲームオーバー画面メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static BOOL GMEVENT_GameOver( GMEVENT_CONTROL* event )
{
	GAME_OVER_WORK * wk = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){

	case 0:

		WIPE_SYS_Start(WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_MAX,
				WIPE_FADE_BLACK, GAME_OVER_FADE_SYNC, WIPE_DEF_SYNC, HEAPID_EVENT);
		wk->seq++;
		break;

	case 1:
		if (WIPE_SYS_EndCheck()) {
			wk->seq++;
		}
		break;

	//キー待ち
	case 2:
		if( (sys.trg & PAD_BUTTON_A) || (sys.trg & PAD_BUTTON_B) ){
			WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
					WIPE_FADE_BLACK, GAME_OVER_FADE_SYNC, WIPE_DEF_SYNC, HEAPID_EVENT);
			wk->seq++;
		}
		break;

	//メイン画面ブラックアウト待ち
	case 3:
		if (WIPE_SYS_EndCheck()) {

			GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_NULL );		//塗りつぶし

			wk->seq++;
		}
		break;

	//終了開放
	case 4:
		BmpTalkWinClear( &wk->bmpwin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->bmpwin );

		WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
		GF_BGL_BGControlExit( wk->bgl, GAME_OVER_BMPWIN_FRAME );
		sys_FreeMemoryEz( wk->bgl );

		sys_FreeMemoryEz( wk );

		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @param	wk			EV_WIN_WORK型のアドレス
 * @param	msg_id		メッセージID
 * @param	x			表示Ｘ座標
 * @param	y			表示Ｙ座標
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void scr_msg_print( GAME_OVER_WORK* wk, u16 msg_id, u8 x, u8 y )
{
	STRBUF* tmp_buf = STRBUF_Create( GAME_OVER_MSG_BUF_SIZE, HEAPID_WORLD );
	STRBUF* tmp_buf2= STRBUF_Create( GAME_OVER_MSG_BUF_SIZE, HEAPID_WORLD );

	GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_NULL );			//塗りつぶし

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );
	GF_STR_PrintColor( &wk->bmpwin, FONT_SYSTEM, tmp_buf2, x, y, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL), NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	通常戦闘：全滅シーケンス
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 *
 */
//-----------------------------------------------------------------------------
BOOL GMEVENT_NormalGameOver(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		//ワープIDで指定された戻り先へ
		{
			LOCATION_WORK next;
			SITUATION * sit = SaveData_GetSituation(fsys->savedata);
			u16 warp_id = Situation_GetWarpID(sit);
			WARPDATA_GetRevivalLocation(warp_id, &next);
			//エスケープポイントをワープポイントに再設定
			WARPDATA_GetWarpLocation(warp_id,Situation_GetEscapeLocation(sit));
			//マップチェンジ
			EventCmd_MapChangeByLocation(event, &next);
			//ゲームオーバー時のフラグのクリア
			FldFlgInit_GameOver(fsys);
		}
		(*seq) ++;
		break;

	case 1:
		//BGMフェードアウト
		Snd_BgmFadeOut( 0, 20 );
		(*seq) ++;
		break;

	case 2:
		//BGMフェードアウト待ち
		if( Snd_FadeCheck() == 0 ){

			//サウンドゲームオーバー処理
			Snd_GameOverSet();

			(*seq) ++;
		}
		break;

	case 3:
		//警告BG以外を表示オフ
		SetBrightness( BRIGHTNESS_BLACK, (PLANEMASK_ALL^PLANEMASK_BG3), MASK_MAIN_DISPLAY);
		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY);

		//ゲームオーバー警告
		GameOverCall( fsys, event );
		(*seq) ++;
		break;

	case 4:
		//イベントコマンド：フィールドマッププロセス復帰
		EventCmd_StartFieldMap(event);
		(*seq)++;
		break;

	case 5:
		//表示オフ解除
		SetBrightness( BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);

		//気をつけてねスクリプト
		
		//話しかけ対象のOBJを取得する処理が必要になる
		//OS_Printf( "field_encount zone_id = %d\n", fsys->location->zone_id );
		if(	WARPDATA_GetInitializeID()
				== Situation_GetWarpID(SaveData_GetSituation(fsys->savedata))) {
			//初期値のワープID＝＝最初の戻り先なので自分の家
			EventCall_Script( event, SCRID_GAME_OVER_RECOVER_MYHOME, NULL, NULL );
		}else{
			//それ以外＝＝ポケセンのはず
			EventCall_Script( event, SCRID_GAME_OVER_RECOVER_PC, NULL, NULL );
		}
		(*seq) ++;
		break;

	case 6:
		//サウンドリスタート処理(06/07/10いらないので削除)
		//Snd_RestartSet( fsys );

		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 * @brief	イベントコマンド：通常全滅処理
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_NormalLose(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_NormalGameOver, NULL);
}



