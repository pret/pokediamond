//==============================================================================================
/**
 * @file	d_nohara.c
 * @brief	デバックソース
 * @author	Satoshi Nohara
 * @date	2005.07.26
 */
//==============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/get_text.h"

#include "system/snd_tool.h"
#include "system/snd_perap.h"

#include "system/savedata.h"
#include "savedata/mystatus.h"
#include "savedata/zukanwork.h"

#include "fld_bgm.h"
#include "poketool/monsno.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "fld_bmp.h"
#include "mapdefine.h"						//ZONE_ID_C01
#include "script.h"							//EventSet_Script
#include "guinness_win.h"					//
#include "ev_mapchange.h"					//

#include "sysflag.h"
#include "syswork.h"

#include "btl_searcher.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_nohara.h"

#include "..\fielddata\script\t01r0202_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\common_scr_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\connect_def.h"		//SCRID_CONNECT_COLOSSEUM
#include "..\fielddata\script\trainer_def.h"		//SCRID_TANPAN_01
#include "..\fielddata\script\r201_def.h"			//SCRID_R201_FLAG_CHANGE
#include "..\fielddata\script\hiden_def.h"			//SCRID_R201_FLAG_CHANGE
#include "..\fielddata\script\con_reception_def.h"	//
#include "..\fielddata\script\pc_ug_def.h"	//
#include "..\fielddata\script\perap_def.h"	//
#include "..\fielddata\script\saisen_def.h"	//
#include "..\fielddata\script\debug_scr_def.h"	//

#include "itemtool/myitem.h"
#include "itemtool/itemsym.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define D_NOHARA_BMPWIN_MAX	(1)				//BMPウィンドウデータ最大数

typedef void (*voidFunc)(void* func);		//関数ポインタ型


//==============================================================================================
//
//	変数
//
//==============================================================================================
static NNSSndCaptureOutputEffectType stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;

//static s16 d_buf[ 32*100 ] ATTRIBUTE_ALIGN(32);	//波形格納バッファ(何かの企画？)


//==============================================================================================
//
//	デバック構造体
//
//==============================================================================================
typedef struct{
	u8	seq;										//処理ナンバー
	u8	wave_buf_flag:1;							//波形格納バッファを確保したフラグ
	u8	waveout_flag:1;								//鳴き声再生中フラグ
	u8	play_flag:6;								//再生中フラグ
	s16 work;										//汎用ワーク

	u16 list_bak;									//リスト位置バックアップ
	u16 cursor_bak;									//カーソル位置バックアップ

	u32 sel;
	u32 count;										//カウンター
	u32 count2;										//カウンター

	FIELDSYS_WORK* fsys;							//

	GF_BGL_BMPWIN bmpwin[D_NOHARA_BMPWIN_MAX];		//BMPウィンドウデータ
	BMPLIST_WORK* lw;								//BMPリストデータ

	BMPLIST_DATA* menulist;							//

//	s16* wave_buf;									//波形格納バッファのポインタ

	//STRBUF* msg_buf[EV_WIN_MENU_MAX];				//メッセージデータのポインタ
	MSGDATA_MANAGER* msgman;						//メッセージマネージャー
	WORDSET* wordset;								//単語セット

}D_NOHARA_WORK;


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void DebugNoharaMenuInit( FIELDSYS_WORK* fsys );

static void DebugNoharaMenuMain( TCB_PTR tcb, void * work );
static void TcbBmpDel( TCB_PTR tcb, void * work );
static void BmpDel( TCB_PTR tcb );
static void NumMsgSet( D_NOHARA_WORK* wk, GF_BGL_BMPWIN* win, int num, u8 x, u8 y );

void DebugBgmMenuInit( FIELDSYS_WORK* fsys );
void DebugScriptMenuInit( FIELDSYS_WORK* fsys );

static void D_Nohara_01( TCB_PTR tcb, void * work );
static void D_Nohara_02( TCB_PTR tcb, void * work );
static void D_Nohara_03( TCB_PTR tcb, void * work );
static void D_Nohara_04( TCB_PTR tcb, void * work );
static void D_Nohara_05( TCB_PTR tcb, void * work );
static void D_Nohara_06( TCB_PTR tcb, void * work );
static void D_Nohara_07( TCB_PTR tcb, void * work );
static void D_Nohara_08( TCB_PTR tcb, void * work );
static void D_Nohara_09( TCB_PTR tcb, void * work );
static void D_Nohara_10( TCB_PTR tcb, void * work );
static void D_Nohara_11( TCB_PTR tcb, void * work );
static void D_Nohara_12( TCB_PTR tcb, void * work );
static void D_Nohara_13( TCB_PTR tcb, void * work );
static void D_Nohara_14( TCB_PTR tcb, void * work );
static void D_Nohara_15( TCB_PTR tcb, void * work );
static void D_Nohara_16( TCB_PTR tcb, void * work );
static void D_Nohara_17( TCB_PTR tcb, void * work );
static void D_Nohara_18( TCB_PTR tcb, void * work );
static void D_Nohara_19( TCB_PTR tcb, void * work );
static void D_Nohara_20( TCB_PTR tcb, void * work );
static void D_Nohara_21( TCB_PTR tcb, void * work );
static void D_Nohara_22( TCB_PTR tcb, void * work );
static void D_Nohara_23( TCB_PTR tcb, void * work );
static void D_Nohara_24( TCB_PTR tcb, void * work );
static void D_Nohara_25( TCB_PTR tcb, void * work );
static void D_Nohara_26( TCB_PTR tcb, void * work );


//==============================================================================================
//
//	リストデータ
//
//==============================================================================================
static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList[] = {
	{ msg_debug_nohara_24, (u32)D_Nohara_24 },		//バトルサーチャー
	{ msg_debug_nohara_01, (u32)D_Nohara_01 },
	{ msg_debug_nohara_02, (u32)D_Nohara_02 },
	//{ msg_debug_nohara_03, (u32)D_Nohara_03 },
	{ msg_debug_nohara_04, (u32)D_Nohara_04 },
	{ msg_debug_nohara_05, (u32)D_Nohara_05 },
	{ msg_debug_nohara_06, (u32)D_Nohara_06 },
	{ msg_debug_nohara_07, (u32)D_Nohara_07 },
	{ msg_debug_nohara_08, (u32)D_Nohara_08 },
	//{ msg_debug_nohara_09, (u32)D_Nohara_09 },
	//{ msg_debug_nohara_10, (u32)D_Nohara_10 },
	{ msg_debug_nohara_11, (u32)D_Nohara_11 },
	//{ msg_debug_nohara_12, (u32)D_Nohara_12 },
	//{ msg_debug_nohara_13, (u32)D_Nohara_13 },
	{ msg_debug_nohara_14, (u32)D_Nohara_14 },
	{ msg_debug_nohara_15, (u32)D_Nohara_15 },		//波形テスト
	//{ msg_debug_nohara_16, (u32)D_Nohara_16 },	//メインシナリオ進行
	{ msg_debug_nohara_17, (u32)D_Nohara_17 },		//バッジフラグセット
	{ msg_debug_nohara_18, (u32)D_Nohara_18 },		//隠しアイテムリスト
	{ msg_debug_nohara_19, (u32)D_Nohara_19 },		//キャプチャチェック
	{ msg_debug_nohara_20, (u32)D_Nohara_20 },		//ギネスウィンドウ
	{ msg_debug_nohara_21, (u32)D_Nohara_21 },		//デバックジャンプ
	{ msg_debug_nohara_22, (u32)D_Nohara_22 },		//ポケッチ波形テスト
	//{ msg_debug_nohara_23, (u32)D_Nohara_23 },		//図鑑、バッグシステムフラグセット
};

static const BMPLIST_HEADER DebugListH = {
	NULL,					//表示文字データポインタ

	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList),	//リスト項目数
	9,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};


//==============================================================================================
//
//	BMPウィンドウ
//
//==============================================================================================
enum{
	D_NOHARA_BMPWIN_FRAME	= GF_BGL_FRAME3_M,
	D_NOHARA_BMPWIN_PX1		= 1,
	D_NOHARA_BMPWIN_PY1		= 1,
	D_NOHARA_BMPWIN_SX		= 16,
	D_NOHARA_BMPWIN_SY		= 20,
	D_NOHARA_BMPWIN_PL		= FLD_SYSFONT_PAL,
	D_NOHARA_BMPWIN_CH		= 1,
};

static const BMPWIN_DAT	DebugNoharaWinData = {
	D_NOHARA_BMPWIN_FRAME,					//ウインドウ使用フレーム
	D_NOHARA_BMPWIN_PX1,D_NOHARA_BMPWIN_PY1,//ウインドウ領域の左上のX,Y座標（キャラ単位で指定）
	D_NOHARA_BMPWIN_SX,	D_NOHARA_BMPWIN_SY,	//ウインドウ領域のX,Yサイズ（キャラ単位で指定）
	D_NOHARA_BMPWIN_PL,						//ウインドウ領域のパレットナンバー	
	D_NOHARA_BMPWIN_CH						//ウインドウキャラ領域の開始キャラクタナンバー
};


//==============================================================================================
//
//	プログラム
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	デバックメニュー呼び出し(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugNoharaMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//波形格納バッファを確保したフラグOFF
	wk->waveout_flag	= 0;								//鳴き声再生中フラグOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList), HEAPID_BASE_DEBUG );


	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList[i].str_id, DebugMenuList[i].param );
	}

	list_h			= DebugListH;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	デバックメニューメイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void DebugNoharaMenuMain( TCB_PTR tcb, void * work )
{
	u32	ret;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->seq ){
	case 0:
		ret = BmpListMain( wk->lw );

		switch( ret ){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			TcbBmpDel( tcb, work );				//TCBBMP開放

			//波形再生用チャンネルを開放する
			Snd_DebugNormalChannelFree();

			break;
		default:
			wk->sel = ret;
			wk->seq++;
			break;
		};

		//BMPリストのリスト位置、カーソル位置を取得
		BmpListPosGet( wk->lw, &wk->list_bak, &wk->cursor_bak );
		break;

	case 1:
		{
			voidFunc func = (voidFunc)wk->sel;
			TCB_ChangeFunc( tcb, (void*)func );	//TCBの動作関数切り替え
		}
		break;

	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	TCB,BMP開放
 *
 * @param	tcb		TCB_PTR型
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void TcbBmpDel( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	MSGMAN_Delete( wk->msgman );
	WORDSET_Delete( wk->wordset );

#if 0
	//波形格納バッファを確保したフラグONだったら
	if( wk->wave_buf_flag == 1 ){
		sys_FreeMemoryEz( wk->wave_buf );	//バッファ開放
	}
#endif

	BmpDel( tcb );						//BMP開放
	PMDS_taskDel( tcb );				//TCB開放
	FieldSystemProc_SeqHoldEnd();
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP開放
 *
 * @param	tcb		TCB_PTR型
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpDel( TCB_PTR tcb )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)TCB_GetWork(tcb);

	//BMP
	BMP_MENULIST_Delete( wk->menulist );
	BmpListExit( wk->lw, &wk->list_bak, &wk->cursor_bak );
	GF_BGL_BmpWinOff( &wk->bmpwin[0] );
	GF_BGL_BmpWinDel( &wk->bmpwin[0] );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	数字メッセージ表示
 *
 * @param	win_index	ビットマップINDEX
 * @param	num			数値
 * @param	x			表示位置X
 * @param	y			表示位置Y
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void NumMsgSet( D_NOHARA_WORK* wk, GF_BGL_BMPWIN* win, int num, u8 x, u8 y )
{
	STRBUF* tmp_buf	= STRBUF_Create( 12, HEAPID_BASE_DEBUG );
	STRBUF* tmp_buf2= STRBUF_Create( 12, HEAPID_BASE_DEBUG );

	MSGMAN_GetString( wk->msgman, msg_debug_nohara_num, tmp_buf );
	WORDSET_RegisterNumber(wk->wordset, 1, num, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

	//登録された単語を使って文字列展開する
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( win, FONT_SYSTEM, tmp_buf2, x, y, MSG_NO_PUT, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}


//==============================================================================================
//
//	01	逆再生関連
//
//==============================================================================================
static void D_Nohara_01_Main( TCB_PTR tcb, void * work );

//extern BOOL Snd_ArcStrmStart( u16 no );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_01( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= MONSNO_HUSIGIDANE;

#if 0
	Snd_CtrlBgmFlagSet( 1 );
	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
#endif

	//BGMを止める
	Snd_Stop();

#if 0
	Snd_PerapVoiceWazaParamGet( 0 );
	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
#endif

#if 0
	//ストリーム再生実験
	//Snd_ArcStrmStart( STRM_PV001 );
	Snd_ArcStrmStart( STRM_PV009 );
	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
#endif

#if 0
	//フラグチェック
	OS_Printf( "===============\n " );
	OS_Printf( "===============\n " );
	for( i=0; i < 10 ;i++ ){
		OS_Printf( "flag %d = %d\n ", i ,CheckEventFlag( wk->fsys, i) );
	}
	TcbBmpDel( tcb, work );		//TCBBMP開放
#else
	TCB_ChangeFunc( tcb, D_Nohara_01_Main );	//TCBの動作関数切り替え
#endif
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_01_Main( TCB_PTR tcb, void * work )
{
	int ret,flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( wk->waveout_flag == 0 ){					//鳴き声再生中フラグOFFだったら

		//鳴き声再生
		if( sys.trg == PAD_BUTTON_A ){
			wk->waveout_flag = 1;					//鳴き声再生中フラグON
			return;		//注意！
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= MONSNO_MAX ){
				wk->work = 1;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			wk->work--;
			if( wk->work <= 0 ){
				wk->work = (MONSNO_MAX - 1);
			}
		}

		//書き換えフラグが立っていたら
		if( flag == 1 ){
			//指定範囲を塗りつぶし
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//ポケモンナンバー表示
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//終了
		if( sys.cont == PAD_BUTTON_B ){
			TcbBmpDel( tcb, work );				//TCBBMP開放
		}

		return;	//注意！
	}


	switch( wk->seq ){
	case 0:
		ret = Snd_PMVoicePlay( wk->work );		//通常再生
		//OS_Printf( "normal play = %d\n", ret );
		wk->seq++;
		break;
	case 1:
		if( Snd_PMVoicePlayCheck() == 0 ){
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 2:
		wk->count++;
		if( wk->count >= 15 ){							//間を入れる
			Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );//波形再生用チャンネルを確保する
			ret = Snd_WaveOutStartReverse( wk->work, 60, 64, WAVEOUT_CH_NORMAL, 
											HEAPID_BASE_DEBUG );//逆再生
			//OS_Printf( "reverse play = %d\n", ret );
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 3:
		//波形再生中かチェック
		if( Snd_WaveOutIsPlaying( WAVEOUT_CH_NORMAL ) == FALSE ){
			Snd_WaveOutStopReverse( WAVEOUT_CH_NORMAL );//逆再生停止buf開放
			Snd_WaveOutFreeChannel( WAVEOUT_CH_NORMAL );//波形再生用チャンネルを開放する
			wk->seq = 0;
			wk->count = 0;
			wk->waveout_flag = 0;				//鳴き声再生中フラグOFF
		}
		break;
	};

	return;
}


//==============================================================================================
//
//	02	リバーブ関連
//
//==============================================================================================
static void D_Nohara_02_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_02( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_02_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_02_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 64 ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 63;
		}
	}

	//書き換えフラグが立っていたら
	if( flag == 1 ){
		if( Snd_CaptureStartReverb( wk->work ) == FALSE ){
			OS_Printf( "リバーブ失敗！\n" );
		}
	
		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*7, 8*2, 
								8*8, 8*2 );
	
		//リバーブ値表示
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*7, 8*2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//終了
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP開放
	}

	return;
}


//==============================================================================================
//
//	03	トラックフェード関連
//
//==============================================================================================
static void D_Nohara_03_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_03( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_03_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_03_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->seq ){
	case 0:
		ret = Snd_TrackFadeCall(wk->fsys, Snd_FieldBgmNoGet(wk->fsys,wk->fsys->location->zone_id));	
		//OS_Printf( "track fade moon = %d\n", ret );
		wk->count	= 0;
		wk->seq++;
		break;
	case 1:
		wk->count++;
		if( wk->count >= 300 ){
			wk->count = 0;
			wk->seq++;
		}
		break;
	case 2:
		ret = Snd_TrackFadeCall(wk->fsys, Snd_FieldBgmNoGet(wk->fsys,wk->fsys->location->zone_id));
		//OS_Printf( "track fade night = %d\n", ret );
		wk->count	= 0;
		wk->seq++;
		break;
	case 3:
		wk->count++;
		if( wk->count >= 200 ){
			TcbBmpDel( tcb, work );		//TCBBMP開放
		}
		break;
	};
#else
	TcbBmpDel( tcb, work );		//TCBBMP開放
#endif
	return;
}


//==============================================================================================
//
//	04	FIELD BGM 音量関連
//
//==============================================================================================
static void D_Nohara_04_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_04( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_04_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_04_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 128 ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 127;
		}
	}

	//書き換えフラグが立っていたら
	if( flag == 1 ){
		Snd_PlayerSetInitialVolume( SND_HANDLE_FIELD, wk->work );
	
		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 8*6, 8*8, 8*2 );
	
		//音量表示
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 8*6 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//終了
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP開放
	}

	return;
}


//==============================================================================================
//
//	05	鳴き声パターン関連
//
//==============================================================================================
static void D_Nohara_05_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList05[] = {
	{ msg_debug_nohara_05_01, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_02, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_03, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_04, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_05, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_06, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_07, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_08, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_09, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_10, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_11, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_12, (u32)D_Nohara_05_Main },
	{ msg_debug_nohara_05_13, (u32)D_Nohara_05_Main },
};

static const BMPLIST_HEADER ListH05 = {
	NULL,					//表示文字データポインタ
	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList05),//リスト項目数
	9,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_05( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP開放

	wk->seq		= 0;
	wk->sel		= 0;
	wk->count	= MONSNO_HUSIGIDANE;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList05), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList05); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList05[i].str_id, DebugMenuList05[i].param );
	}

	list_h			= ListH05;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_05_Main );	//TCBの動作関数切り替え
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_05_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	if( sys.cont & PAD_BUTTON_L ){
		wk->count--;
	}else if( sys.cont & PAD_BUTTON_R ){
		wk->count++;
	}

	//ポケモン鳴き声パターンセット
	//monsno,pan,vol,ptn
	Snd_PMVoicePlayEx( (wk->cursor_bak+wk->list_bak),
						wk->count, 0, 127, 
						//MONSNO_HUSIGIDANE, 0, 127, 
						//MONSNO_HIKOZARU, (gf_rand() % 127), 127, 
						HEAPID_BASE_DEBUG ); 

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCBの動作関数切り替え
	return;
}


//==============================================================================================
//
//	06	出力エフェクト関連
//
//==============================================================================================
static void D_Nohara_06_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList06[] = {
	{ msg_debug_nohara_06_01, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_02, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_03, (u32)D_Nohara_06_Main },
	{ msg_debug_nohara_06_04, (u32)D_Nohara_06_Main },
};

static const BMPLIST_HEADER ListH06 = {
	NULL,					//表示文字データポインタ
	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList06),//リスト項目数
	5,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_06( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP開放

	//Snd_CaptureCreateThread();

	wk->seq		= 0;
	wk->sel		= 0;
	wk->count	= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList06), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList06); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList06[i].str_id, DebugMenuList06[i].param );
	}

	list_h			= ListH06;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_06_Main );	//TCBの動作関数切り替え
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_06_Main( TCB_PTR tcb, void * work )
{
	NNSSndCaptureOutputEffectType stereo_mono;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 1:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_MONO;
		break;
	case 2:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_SURROUND;
		break;
	case 3:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_HEADPHONE;
		break;
	default:
		stereo_mono = NNS_SND_CAPTURE_OUTPUT_EFFECT_NORMAL;
		break;
	}

	Snd_CaptureStartOutputEffect( stereo_mono );
	//Snd_CaptureChangeOutputEffect( stereo_mono );

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	07	マイク関連
//
//==============================================================================================
static void D_Nohara_07_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList07[] = {
	{ msg_debug_nohara_07_01, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_02, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_03, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_04, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_05, (u32)D_Nohara_07_Main },
	{ msg_debug_nohara_07_06, (u32)D_Nohara_07_Main },
};

static const BMPLIST_HEADER ListH07 = {
	NULL,					//表示文字データポインタ
	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList07),//リスト項目数
	6,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_07( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP開放

#if 0
	//バッファ確保
	wk->wave_buf = sys_AllocMemory( HEAPID_BASE_DEBUG, WAVE_SAMPLE );
	if( wk->wave_buf == NULL ){
		GF_ASSERT( (0) && "メモリ確保に失敗しました！" );
	}
	memset( wk->wave_buf, 0, WAVE_SAMPLE );
#endif

	//波形再生用チャンネルを確保する
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;
	wk->wave_buf_flag	= 1;					//波形格納バッファを確保したフラグON

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList07), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList07); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList07[i].str_id, DebugMenuList07[i].param );
	}

	list_h			= ListH07;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_07_Main );	//TCBの動作関数切り替え
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCBの動作関数切り替え
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_07_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 0:
		//録音開始
		Snd_PerapVoiceRecStart();
		break;

	case 1:
		//録音停止
		Snd_PerapVoiceRecStop();
		break;

	case 2:
		//自分のぺラップの録音したデータを再生
		Snd_PerapVoicePlay( SaveData_GetPerapVoice(wk->fsys->savedata), PM_MALE, 127, 64 );
		break;

	case 3:
		Snd_PMVoiceStop( 0 );
		break;

	case 4:
		//録音したデータを自分のぺラップデータにコピー
		Snd_PerapVoiceDataSave( SaveData_GetPerapVoice(wk->fsys->savedata) );
		break;

	default:
		//起動
		EventSet_Script( wk->fsys, SCRID_PERAP, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP開放
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCBの動作関数切り替え
	return;
}


//==============================================================================================
//
//	08	FIELD TEMPO 音量関連
//
//==============================================================================================
static void D_Nohara_08_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_08( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 256;
	TCB_ChangeFunc( tcb, D_Nohara_08_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_08_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= 512 ){
			wk->work = 64;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 64 ){
			wk->work = 512;
		}
	}

	//書き換えフラグが立っていたら
	if( flag == 1 ){
		Snd_PlayerSetTempoRatio( SND_HANDLE_FIELD, wk->work );
	
		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 8*14, 8*8, 8*2 );
	
		//テンポ表示
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 8*14 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//終了
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP開放
	}

	return;
}


//==============================================================================================
//
//	09	スクリプト関連
//
//==============================================================================================
static void D_Nohara_09_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_09( TCB_PTR tcb, void * work )
{
	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	10	トラックフェードフラグ操作
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_10( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//切り替え
	//debug_track_fade_flag = 1;

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	11	スクリプト実行関連
//
//==============================================================================================
static void D_Nohara_11_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList11[] = {
	{ msg_debug_nohara_11_01, (u32)D_Nohara_11_Main },
	{ msg_debug_nohara_11_02, (u32)D_Nohara_11_Main },
	{ msg_debug_nohara_11_03, (u32)D_Nohara_11_Main },
};

static const BMPLIST_HEADER ListH11 = {
	NULL,					//表示文字データポインタ
	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList11),//リスト項目数
	10,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_11( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP開放

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList11), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList11); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList11[i].str_id, DebugMenuList11[i].param );
	}

	list_h			= ListH11;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_11_Main );	//TCBの動作関数切り替え
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCBの動作関数切り替え
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_11_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	switch( wk->cursor_bak ){
	case 0:
		//C07の倉庫の鍵出現させる
		SpScriptStart( wk->fsys, SCRID_DEBUG_C07_SOUKONOKAGI );
		break;

	case 1:
		//３つの湖イベント開始
		SpScriptStart( wk->fsys, SCRID_DEBUG_L01_L02_L03_LAKE );
		break;

	case 2:
		//ポケセン地下ストッパー削除、ともだち手帳イベント無効
		SpScriptStart( wk->fsys, SCRID_DEBUG_PC_UG );
		break;

	default:
		//EventSet_Script( wk->fsys, SCRID_TANPAN_01, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP開放
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCBの動作関数切り替え
	return;
}


//==============================================================================================
//
//	12	調律乱れ
//
//==============================================================================================
static void D_Nohara_12_Main( TCB_PTR tcb, void * work );

#define D_NOHARA_12_PITCH_MAX	(128)					//64で半音、全音が128
#define D_NOHARA_12_PTN_MAX		(5)						//パターン数
#define D_NOHARA_12_SEQ_NO		(SEQ_SE_DP_BADGE_C)		//シーケンスナンバー
#define D_NOHARA_12_WAIT		(30)					//ウェイト

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_12( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;

	Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );

	TCB_ChangeFunc( tcb, D_Nohara_12_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_12_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret,flag,pitch,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//フェード終了待ち
	if( Snd_FadeCheck() != 0 ){
		return; //何もしない
	}

	flag = 0;	//書き換えフラグ

	if( wk->play_flag == 0 ){						//再生中フラグOFFだったら

		//再生
		if( sys.trg == PAD_BUTTON_A ){
			wk->play_flag = 1;					//再生中フラグON
			return;		//注意！
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= D_NOHARA_12_PITCH_MAX ){
				wk->work = 0;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			if( wk->work <= 0 ){
				wk->work = D_NOHARA_12_PITCH_MAX;
			}
			wk->work--;
		}

		//書き換えフラグが立っていたら
		if( flag == 1 ){
			//指定範囲を塗りつぶし
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//ポケモンナンバー表示
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//終了
		if( sys.cont == PAD_BUTTON_B ){
			Snd_BgmFadeIn( BGM_VOL_MAX, 0, BGM_FADEIN_START_VOL_NOW );
			TcbBmpDel( tcb, work );				//TCBBMP開放
		}

		return;	//注意！
	}

	switch( wk->seq ){
	case 0:
		Snd_SePlay( D_NOHARA_12_SEQ_NO );

		//最後の音は、調律を乱さない
		if( wk->count < 4 ){
			//wk->work							= 音程変化最大値
			//wk->work / D_NOHARA_12_PTN_MAX	= 音程変化1つ分の値
			//D_NOHARA_12_PTN_MAX - wk->count	= 何パターン目か(DEBUG_PTN_MAXに近いほど乱れている)
			pitch = ( (wk->work/D_NOHARA_12_PTN_MAX) * (D_NOHARA_12_PTN_MAX-wk->count) );

			//プレイヤーが決まっていないので、全SEプレイヤーに対して操作する
			for( i=0; i < SE_HANDLE_MAX ;i++ ){
				Snd_PlayerSetTrackPitch( SND_HANDLE_SE_1+i, 0xffff, pitch );
			}
		}

		wk->count2 = 0;							//ウェイトカウンタークリア
		wk->seq++;
		break;
	case 1:
		if( Snd_SePlayCheck( D_NOHARA_12_SEQ_NO ) == 0 ){

			//ウェイトチェック
			wk->count2++;
			if( wk->count2 < D_NOHARA_12_WAIT ){
				return;
			}

			wk->count++;						//パターンインクリメント
			wk->seq = 0;						//シーケンスを戻す

			if( wk->count >= D_NOHARA_12_PTN_MAX ){
				wk->seq = 0;
				wk->count = 0;
				wk->play_flag = 0;				//再生中フラグOFF
			}
		}
		break;
	};
#endif

	return;
}


//==============================================================================================
//
//	13	調律乱れ2
//
//==============================================================================================
static void D_Nohara_13_Main( TCB_PTR tcb, void * work );

#define D_NOHARA_13_SEQ_NO		(SEQ_SE_DP_BADGE_C)		//シーケンスナンバー
#define D_NOHARA_13_WAIT		(1)//(5)//(10)//(30)					//ウェイト

//ずれの段階
enum{
	P_0 = 0,			//音程のずれなし
	P_1 = 16,			//
	P_2 = 32,			//
	P_3 = 64,			//半音ずれ
	P_4 = 96,			//
};

//基本音程
enum{
	P_C = 0,			//C
	P_D = (64*2),		//D
	P_E = (64*4),		//E
	P_F = (64*5),		//F
	P_G = (64*7),		//G
	P_A = (64*9),		//A
	P_B = (64*11),		//B
	PCC = (64*12),		//C
};

//音程テーブル
static const u16 pitch_tbl[][8] = {
	{ P_C, P_D,	P_E, P_F, P_G, P_A, P_B, PCC },							//音程ずれなし
	{ P_C+P_3, P_D, P_E+P_2, P_F, P_G+P_3, P_A+P_2, P_B+P_4, PCC },		//大きくずれ
	{ P_C+P_1, P_D, P_E+P_1, P_F, P_G+P_1, P_A+P_1, P_B+P_1, PCC+P_1 },	//少しずれ
};
#define D_NOHARA_13_PITCH_TBL_MAX	( NELEMS(pitch_tbl) )

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_13( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;

	Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );

	TCB_ChangeFunc( tcb, D_Nohara_13_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_13_Main( TCB_PTR tcb, void * work )
{
#if 0
	int ret,flag,pitch,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	//フェード終了待ち
	if( Snd_FadeCheck() != 0 ){
		return; //何もしない
	}

	flag = 0;	//書き換えフラグ

	if( wk->play_flag == 0 ){						//再生中フラグOFFだったら

		//再生
		if( sys.trg == PAD_BUTTON_A ){
			wk->play_flag = 1;					//再生中フラグON
			return;		//注意！
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= D_NOHARA_13_PITCH_TBL_MAX ){
				wk->work = 0;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			if( wk->work <= 0 ){
				wk->work = D_NOHARA_13_PITCH_TBL_MAX;
			}
			wk->work--;
		}

		//書き換えフラグが立っていたら
		if( flag == 1 ){
			//指定範囲を塗りつぶし
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//ポケモンナンバー表示
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//終了
		if( sys.cont == PAD_BUTTON_B ){
			Snd_BgmFadeIn( BGM_VOL_MAX, 0, BGM_FADEIN_START_VOL_NOW );
			TcbBmpDel( tcb, work );				//TCBBMP開放
		}

		return;	//注意！
	}

	switch( wk->seq ){
	case 0:
		//if( Snd_SePlayCheck( D_NOHARA_13_SEQ_NO ) == 0 ){

			//特殊な再生！
			//再生するハンドル、プレイヤーを操作している！
			//Snd_SePlay( D_NOHARA_13_SEQ_NO );
			Snd_ArcPlayerStartSeqEx( SND_HANDLE_SE_1+(wk->count&0x3), 
										PLAYER_SE_1+(wk->count&0x3), D_NOHARA_13_SEQ_NO );

			//プレイヤーが決まっていないので、全SEプレイヤーに対して操作する
			for( i=0; i < SE_HANDLE_MAX ;i++ ){
				Snd_PlayerSetTrackPitch( SND_HANDLE_SE_1+i, 0xffff,pitch_tbl[wk->work][wk->count] );
			}

			wk->count2 = 0;								//ウェイトカウンタークリア
			wk->count++;
			wk->seq++;

			if( wk->count >= 8 ){
				wk->seq = 0;
				wk->count = 0;
				wk->play_flag = 0;						//再生中フラグOFF
				return;
			}
		//}
		break;
	case 1:
		//ウェイトチェック
		wk->count2++;
		if( wk->count2 < D_NOHARA_13_WAIT ){
			return;
		}

		wk->count2 = 0;									//ウェイトカウンタークリア
		wk->seq = 0;									//シーケンスを戻す
		break;
	};

#endif
	return;
}


//==============================================================================================
//
//	14	サウンドエフェクト
//
//==============================================================================================
static void D_Nohara_14_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_14( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->count2	= 0;
	wk->work	= 0;
	Snd_CaptureStartEffect();
	TCB_ChangeFunc( tcb, D_Nohara_14_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_14_Main( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	int flag = 0;

	wk = (D_NOHARA_WORK*)work;

	//再生
	//if( sys.trg == PAD_BUTTON_A ){
	//	Snd_CaptureStartEffect();
	//	return;
	//}
	
	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work > 8 ){
			wk->work = 8;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = 0;
		}
	}

	//書き換えフラグが立っていたら
	if( flag == 1 ){
		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );

		//ポケモンナンバー表示
		NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );

		//エフェクトレベルセット
		Snd_CaptureEffectLevel( wk->work );
	}

	//停止、終了
	if( sys.cont == PAD_BUTTON_B ){
		Snd_CaptureStopEffect();
		TcbBmpDel( tcb, work );				//TCBBMP開放
		return;
	}

	return;
}


//==============================================================================================
//
//	15	鳴き声波形関連
//
//==============================================================================================
static void D_Nohara_15_Main( TCB_PTR tcb, void * work );

u32 now_tick;									//現在のティック数

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_15( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= MONSNO_HUSIGIDANE;
	TCB_ChangeFunc( tcb, D_Nohara_15_Main );	//TCBの動作関数切り替え
	return;
}

u8 test_buf[9];	//
const SNDWaveData* pw_data;
//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_15_Main( TCB_PTR tcb, void * work )
{
	int ret,flag,i;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( wk->waveout_flag == 0 ){					//鳴き声再生中フラグOFFだったら

		//鳴き声再生
		if( sys.trg == PAD_BUTTON_A ){
			wk->waveout_flag = 1;					//鳴き声再生中フラグON
			return;		//注意！
		}

		if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
			flag = 1;
			wk->work++;
			if( wk->work >= MONSNO_MAX ){
				wk->work = 1;
			}
		}

		if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
			flag = 1;
			wk->work--;
			if( wk->work <= 0 ){
				wk->work = (MONSNO_MAX - 1);
			}
		}

		//書き換えフラグが立っていたら
		if( flag == 1 ){
			//指定範囲を塗りつぶし
			GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*11, 0, 8*6, 8*2 );
	
			//ポケモンナンバー表示
			NumMsgSet( wk, &wk->bmpwin[0], wk->work, 8*11, 2 );
			GF_BGL_BmpWinOn( &wk->bmpwin[0] );
		}

		//終了
		if( sys.cont == PAD_BUTTON_B ){
			TcbBmpDel( tcb, work );				//TCBBMP開放
		}

		return;	//注意！
	}

	switch( wk->seq ){
	case 0:
#if 1
		now_tick = 0;
		//Snd_ZukanWaveDataSet( wk->work );							//波形データのアドレス取得
		pw_data = Snd_ZukanWaveDataSet( wk->work );					//波形データのアドレス取得
		OS_Printf( "pw_data size = %d\n", Snd_WaveDataSampleSizeGet( pw_data ) );
		//Snd_DebugWaveDataPut( 0, 1000 );							//波形データ表示
		
		for( i=0; i < 9 ;i++ ){
			test_buf[i] = 0;
		}

		ret = Snd_PMVoicePlay( wk->work );							//通常再生

		//音程操作
		if( sys.cont & PAD_BUTTON_L ){
			//Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, -64 * 12 );
			Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, 64 * 12 );
		}
#endif

		//pw_data = Snd_ZukanWaveDataSet( wk->work );					//波形データのアドレス取得
		//Snd_PMVoicePlayPtn_ZukanChorus( 1, 0 );
		//Snd_PMVoicePlayPtn_ZukanChorus( 1, 80 );

		wk->seq++;
		break;
	case 1:
		if( Snd_PMVoicePlayCheck() == 0 ){
			wk->count = 0;
			wk->seq++;
		}else{
			{
				u32 tmp,old_tick;

#if 0
				old_tick = now_tick;								//退避
				//now_tick = Snd_ZukanPlayerGetTick();				//ティック数取得
				now_tick = Snd_PlayerGetSampleTick( SND_HANDLE_PMVOICE, pw_data );	//ティック数取得

				//240(今) - 180(前) = 60(差)
				//60 / 2 = 30
				//240 - 30 = 210(中間)
				tmp = (now_tick - ((now_tick-old_tick) / 2));
				Snd_DebugWaveDataPut( pw_data, tmp, tmp+1 );					//前回との中間位置

				Snd_DebugWaveDataPut( pw_data, now_tick, now_tick+1 );		//現在の位置
				Snd_DebugWaveLevelGet( now_tick );					//レベル
#endif

				//レベル取得
				Snd_ZukanWaveLevelSet_New( pw_data, test_buf, 9, 0 );
			}
		}
		break;
	case 2:
		wk->seq = 0;
		wk->count = 0;
		wk->waveout_flag = 0;				//鳴き声再生中フラグOFF
		break;
	};

	return;
}


//==============================================================================================
//
//	16	メインシナリオ関連
//
//	現在のゾーンのスクリプトとメッセージを読み込むようにしているので、
//	デバックでスクリプトのIDを指定するだけでは出来ない！
//
//	まだスクリプトしか作成していないものは、common_scr.evに追加して試す。。。
//	とも思ったが、メッセージもないので、無理そう。。。
//
//==============================================================================================
static void D_Nohara_16_Main( TCB_PTR tcb, void * work );

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_16( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_16_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_16_Main( TCB_PTR tcb, void * work )
{
	//終了
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP開放
	}

	return;
}


//==============================================================================================
//
//	17	バッジフラグセット
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_17( TCB_PTR tcb, void * work )
{
	int i;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;
	MYSTATUS* my = SaveData_GetMyStatus( wk->fsys->savedata );

	for( i=0; i < 8; i++ ){
		MyStatus_SetBadgeFlag( my, i );
	}

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	18	隠しアイテム検索
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_18( TCB_PTR tcb, void * work )
{
	int i,count;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;
	MYSTATUS* my = SaveData_GetMyStatus( wk->fsys->savedata );
	HIDE_ITEM_LIST* p = HideItem_CreateList( wk->fsys, HEAPID_BASE_DEBUG );

	count = 0;

	while( 1 ){
		if( p[count].response == HIDE_LIST_RESPONSE_NONE ){
			if( count == 0 ){
				OS_Printf( "隠しアイテムは見つかりませんでした！\n" );
			}
			break;
		}

		OS_Printf( "\nresponse = %d\n", p[count].response );
		OS_Printf( "gx = %d\n", p[count].gx );
		OS_Printf( "gz = %d\n", p[count].gz );
		count++;
	};

	sys_FreeMemoryEz( p );

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	19	隠しアイテム検索
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_19( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	Snd_CaptureIsActive();

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	20	ギネスウィンドウ
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_20( TCB_PTR tcb, void * work )
{
	int type,ret;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	EventSet_Script( wk->fsys, SCRID_GUINNESS_WIN, NULL );
	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}

//==============================================================================================
//
//	21	デバックジャンプ
//
//==============================================================================================
static void D_Nohara_21_Main( TCB_PTR tcb, void * work );

typedef struct{
	u32 zone_id;
	u32 num;
	u32 x;
	u32 z;
}DEBUG_JUMP_WORK;

static const DEBUG_JUMP_WORK debug_jump_work[] = {
	{ ZONE_ID_T02,		2,		160,	846 },			//マサゴタウン
	{ ZONE_ID_T03,		3,		176,	624 },			//ソノオタウン
	{ ZONE_ID_R201,		201,	110,	856 },			//
	{ ZONE_ID_R205A,	2051,	208,	592 },			//
	{ ZONE_ID_R205B,	2052,	272,	528 },			//
	{ ZONE_ID_C05R1101,	511,	5,		5 },			//コンテスト受付
	{ ZONE_ID_D27R0101, 2701,	46,		53 },			//
};
#define DEBUG_JUMP_WORK_MAX	( NELEMS(debug_jump_work) )

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_21( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;
	TCB_ChangeFunc( tcb, D_Nohara_21_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_21_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ

	if( (sys.repeat == PAD_KEY_UP) || (sys.cont == PAD_KEY_RIGHT) ){
		flag = 1;
		wk->work++;
		if( wk->work >= DEBUG_JUMP_WORK_MAX ){
			wk->work = 0;
		}
	}

	if( (sys.repeat == PAD_KEY_DOWN) || (sys.cont == PAD_KEY_LEFT) ){
		flag = 1;
		wk->work--;
		if( wk->work < 0 ){
			wk->work = (DEBUG_JUMP_WORK_MAX - 1);
		}
	}

	//書き換えフラグが立っていたら
	if( flag == 1 ){
		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin[0], FBMP_COL_BLACK, 8*7, 8*2, 
								8*8, 8*2 );
	
		//値表示
		NumMsgSet( wk, &wk->bmpwin[0], debug_jump_work[wk->work].num, 8*7, 8*2 );
		GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	}

	//ジャンプ
	if( sys.trg == PAD_BUTTON_A ){

		EventSet_EasyMapChange( wk->fsys, debug_jump_work[wk->work].zone_id, DOOR_ID_JUMP_CODE, 
							debug_jump_work[wk->work].x , debug_jump_work[wk->work].z, DIR_DOWN );

		TcbBmpDel( tcb, work );		//TCBBMP開放
		return;
	}

	//終了
	if( sys.cont == PAD_BUTTON_B ){
		TcbBmpDel( tcb, work );		//TCBBMP開放
		return;
	}

	return;
}


//==============================================================================================
//
//	22	ポケッチ波形テスト
//
//==============================================================================================
static void D_Nohara_22_Main( TCB_PTR tcb, void * work );
static void Snd_DebugWaveBufWrite( u32 no );

static s8 d_sWaveBuffer[ 64 ] ATTRIBUTE_ALIGN(32);	//波形格納バッファ

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_22( TCB_PTR tcb, void * work )
{
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;
	wk->seq		= 0;
	wk->count	= 0;
	wk->work	= 0;

	//波形再生用チャンネルを確保する
	Snd_WaveOutAllocChannel( WAVEOUT_CH_NORMAL );

	TCB_ChangeFunc( tcb, D_Nohara_22_Main );	//TCBの動作関数切り替え
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_22_Main( TCB_PTR tcb, void * work )
{
	int flag;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	flag = 0;	//書き換えフラグ


	switch( wk->seq ){
	case 0:
		//呼び出すパターンを切り替える
		if( sys.trg & PAD_KEY_UP ){
			Snd_DebugWaveBufWrite( 0 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_DOWN ){
			Snd_DebugWaveBufWrite( 1 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_RIGHT ){
			Snd_DebugWaveBufWrite( 2 );
			wk->seq++;
		}else if( sys.trg & PAD_KEY_LEFT ){
			Snd_DebugWaveBufWrite( 3 );
			wk->seq++;
		}

		//終了
		if( sys.cont == PAD_BUTTON_B ){
			//波形再生用チャンネルを開放する
			Snd_DebugNormalChannelFree();

			TcbBmpDel( tcb, work );		//TCBBMP開放
			return;
		}

		break;

	case 1:
		//波形再生
		{
			WAVEOUT_WORK waveout_wk;

			waveout_wk.handle			= Snd_WaveOutHandleGet(WAVEOUT_CH_NORMAL);//波形再生ハンドル
			waveout_wk.format			= NNS_SND_WAVE_FORMAT_PCM8;//波形データフォーマット
			waveout_wk.dataaddr			= &d_sWaveBuffer[0];//波形データの先頭アドレス
			waveout_wk.loopFlag			= TRUE;					//ループフラグ
			waveout_wk.loopStartSample	= 0;						//ループ開始サンプル位置
			waveout_wk.samples			= 64;				//波形データのサンプル数
			//waveout_wk.samples		= WAVE_SAMPLE;				//波形データのサンプル数
			waveout_wk.sampleRate		= 16000;					//波形データのサンプリングレート
			waveout_wk.volume			= 127;						//音量
			waveout_wk.speed			= 32768;					//再生スピード
			//waveout_wk.speed			= 32768*3;					//再生スピード
			//waveout_wk.speed			= 32768/3;					//再生スピード
			waveout_wk.pan				= 64;						//パン(0-127)

			Snd_WaveOutStart( &waveout_wk, WAVEOUT_CH_NORMAL );		//波形再生
		}
		wk->count = 0;
		wk->seq++;
		break;

	case 2:
		wk->count++;

		if( wk->count == 16 ){					//フレーム数なので注意！
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, (32768 * 2) );
		}

		if( wk->count == 24 ){					//フレーム数なので注意！
			Snd_WaveOutSetSpeed( WAVEOUT_CH_NORMAL, (32768 / 2) );
		}

		if( wk->count >= 32 ){					//フレーム数なので注意！
			Snd_WaveOutStop( WAVEOUT_CH_NORMAL );	//波形停止
			wk->seq = 0;
		}
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	適当な波形を書き込む
 *
 * @param	no		パターン
 *
 * @retval	none
 */
//--------------------------------------------------------------
#define TEST_START	(0)
#define TEST_ADD	(64)
//#define TEST_LOOP	(40)
#define TEST_LOOP	(1)

static void Snd_DebugWaveBufWrite( u32 no )
{
	u8 add;
	int i,j;

	switch( no ){

	case 0:

		//「■」
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			for( i=0+add; i < 32+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
			for( i=32+add; i < 64+add ;i++ ){
				d_sWaveBuffer[i] = -120;
			}
		}
		break;

	case 1:

		//「■」
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			for( i=0+add; i < 10+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=10+add; i < 20+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
			for( i=20+add; i < 30+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=30+add; i < 40+add ;i++ ){
				d_sWaveBuffer[i] = -120;
				}
			for( i=40+add; i < 50+add ;i++ ){
				d_sWaveBuffer[i] = 0;
			}
			for( i=50+add; i < 64+add ;i++ ){
				d_sWaveBuffer[i] = 120;
			}
		}

	case 2:

		//「▲」
		//マイナスなし
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			d_sWaveBuffer[0+add] = 0;
			d_sWaveBuffer[1+add] = 4;
			d_sWaveBuffer[2+add] = 8;
			d_sWaveBuffer[3+add] = 12;
			d_sWaveBuffer[4+add] = 16;
			d_sWaveBuffer[5+add] = 20;
			d_sWaveBuffer[6+add] = 24;
			d_sWaveBuffer[7+add] = 28;
			d_sWaveBuffer[8+add] = 32;
			d_sWaveBuffer[9+add] = 36;
			d_sWaveBuffer[10+add] = 40;
			d_sWaveBuffer[11+add] = 44;
			d_sWaveBuffer[12+add] = 48;
			d_sWaveBuffer[13+add] = 52;
			d_sWaveBuffer[14+add] = 56;
			d_sWaveBuffer[15+add] = 60;
			d_sWaveBuffer[16+add] = 64;
			d_sWaveBuffer[17+add] = 68;
			d_sWaveBuffer[18+add] = 72;
			d_sWaveBuffer[19+add] = 76;
			d_sWaveBuffer[20+add] = 80;
			d_sWaveBuffer[21+add] = 84;
			d_sWaveBuffer[22+add] = 88;
			d_sWaveBuffer[23+add] = 92;
			d_sWaveBuffer[24+add] = 96;
			d_sWaveBuffer[25+add] = 100;
			d_sWaveBuffer[26+add] = 104;
			d_sWaveBuffer[27+add] = 108;
			d_sWaveBuffer[28+add] = 112;
			d_sWaveBuffer[29+add] = 116;
			d_sWaveBuffer[30+add] = 120;
			d_sWaveBuffer[31+add] = 124;
			d_sWaveBuffer[32+add] = 128;
			d_sWaveBuffer[33+add] = 124;
			d_sWaveBuffer[34+add] = 120;
			d_sWaveBuffer[35+add] = 116;
			d_sWaveBuffer[36+add] = 112;
			d_sWaveBuffer[37+add] = 108;
			d_sWaveBuffer[38+add] = 104;
			d_sWaveBuffer[39+add] = 100;
			d_sWaveBuffer[40+add] = 96;
			d_sWaveBuffer[41+add] = 92;
			d_sWaveBuffer[42+add] = 88;
			d_sWaveBuffer[43+add] = 84;
			d_sWaveBuffer[44+add] = 80;
			d_sWaveBuffer[45+add] = 76;
			d_sWaveBuffer[46+add] = 72;
			d_sWaveBuffer[47+add] = 68;
			d_sWaveBuffer[48+add] = 64;
			d_sWaveBuffer[49+add] = 60;
			d_sWaveBuffer[50+add] = 56;
			d_sWaveBuffer[51+add] = 52;
			d_sWaveBuffer[52+add] = 48;
			d_sWaveBuffer[53+add] = 44;
			d_sWaveBuffer[54+add] = 40;
			d_sWaveBuffer[55+add] = 36;
			d_sWaveBuffer[56+add] = 32;
			d_sWaveBuffer[57+add] = 28;
			d_sWaveBuffer[58+add] = 24;
			d_sWaveBuffer[59+add] = 20;
			d_sWaveBuffer[60+add] = 16;
			d_sWaveBuffer[61+add] = 12;
			d_sWaveBuffer[62+add] = 8;
			d_sWaveBuffer[63+add] = 4;
		};

		break;

	case 3:

		//「▲」
		//マイナスあり
		
		for( j=0; j < TEST_LOOP ;j++ ){

			add = TEST_ADD * j;

			d_sWaveBuffer[0+add] = -127;
			d_sWaveBuffer[1+add] = -119;
			d_sWaveBuffer[2+add] = -111;
			d_sWaveBuffer[3+add] = -103;
			d_sWaveBuffer[4+add] = -95;
			d_sWaveBuffer[5+add] = -87;
			d_sWaveBuffer[6+add] = -79;
			d_sWaveBuffer[7+add] = -71;
			d_sWaveBuffer[8+add] = -63;
			d_sWaveBuffer[9+add] = -55;
			d_sWaveBuffer[10+add] = -47;
			d_sWaveBuffer[11+add] = -39;
			d_sWaveBuffer[12+add] = -31;
			d_sWaveBuffer[13+add] = -23;
			d_sWaveBuffer[14+add] = -15;
			d_sWaveBuffer[15+add] = -7;
			d_sWaveBuffer[16+add] = 1;
			d_sWaveBuffer[17+add] = 9;
			d_sWaveBuffer[18+add] = 17;
			d_sWaveBuffer[19+add] = 25;
			d_sWaveBuffer[20+add] = 33;
			d_sWaveBuffer[21+add] = 41;
			d_sWaveBuffer[22+add] = 49;
			d_sWaveBuffer[23+add] = 57;
			d_sWaveBuffer[24+add] = 65;
			d_sWaveBuffer[25+add] = 73;
			d_sWaveBuffer[26+add] = 81;
			d_sWaveBuffer[27+add] = 89;
			d_sWaveBuffer[28+add] = 97;
			d_sWaveBuffer[29+add] = 105;
			d_sWaveBuffer[30+add] = 113;
			d_sWaveBuffer[31+add] = 121;
			d_sWaveBuffer[32+add] = 127;
			d_sWaveBuffer[33+add] = 121;
			d_sWaveBuffer[34+add] = 113;
			d_sWaveBuffer[35+add] = 105;
			d_sWaveBuffer[36+add] = 97;
			d_sWaveBuffer[37+add] = 89;
			d_sWaveBuffer[38+add] = 81;
			d_sWaveBuffer[39+add] = 73;
			d_sWaveBuffer[40+add] = 65;
			d_sWaveBuffer[41+add] = 57;
			d_sWaveBuffer[42+add] = 49;
			d_sWaveBuffer[43+add] = 41;
			d_sWaveBuffer[44+add] = 33;
			d_sWaveBuffer[45+add] = 25;
			d_sWaveBuffer[46+add] = 17;
			d_sWaveBuffer[47+add] = 9;
			d_sWaveBuffer[48+add] = 1;
			d_sWaveBuffer[49+add] = -7;
			d_sWaveBuffer[50+add] = -15;
			d_sWaveBuffer[51+add] = -23;
			d_sWaveBuffer[52+add] = -31;
			d_sWaveBuffer[53+add] = -39;
			d_sWaveBuffer[54+add] = -47;
			d_sWaveBuffer[55+add] = -55;
			d_sWaveBuffer[56+add] = -63;
			d_sWaveBuffer[57+add] = -71;
			d_sWaveBuffer[58+add] = -79;
			d_sWaveBuffer[59+add] = -87;
			d_sWaveBuffer[60+add] = -95;
			d_sWaveBuffer[61+add] = -103;
			d_sWaveBuffer[62+add] = -111;
			d_sWaveBuffer[63+add] = -119;
		};

		break;

	default:
		break;
	};

	//テスト表示
	for( j=0; j < 64*10 ;j++ ){
		OS_Printf( "d_sWaveBuffer[%d] = %d\n", j, d_sWaveBuffer[j] );
	}

	return;
}


//==============================================================================================
//
//	23	図鑑、バッグシステムフラグセット
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_23( TCB_PTR tcb, void * work )
{
	int type,ret;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	{
		//メニュー「図鑑」
		ZUKAN_WORK* zw = SaveData_GetZukanWork( wk->fsys->savedata );
		ZukanWork_SetZukanGetFlag( zw );

		//メニュー「バッグ」
		SysFlag_BagSet( SaveData_GetEventWork(wk->fsys->savedata) );

		//メニュー「ポケモン」
		SysWork_FirstPokeNoSet( SaveData_GetEventWork(wk->fsys->savedata), MONSNO_HUSIGIDANE );
	}

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	24	バトルサーチャー関連
//
//==============================================================================================
static void D_Nohara_24_Main( TCB_PTR tcb, void * work );

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList24[] = {
	{ msg_debug_nohara_24_01, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_02, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_03, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_04, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_05, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_06, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_07, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_08, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_09, (u32)D_Nohara_24_Main },
	{ msg_debug_nohara_24_10, (u32)D_Nohara_24_Main },
};

static const BMPLIST_HEADER ListH24 = {
	NULL,					//表示文字データポインタ
	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList24),//リスト項目数
	10,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_24( TCB_PTR tcb, void * work )
{
	int i;
	BMPLIST_HEADER list_h;
	GF_BGL_BMPWIN* win;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	BmpDel( tcb );								//BMP開放

	wk->seq				= 0;
	wk->sel				= 0;
	wk->count			= 0;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList24), HEAPID_BASE_DEBUG );

	for( i=0; i < NELEMS(DebugMenuList24); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList24[i].str_id, DebugMenuList24[i].param );
	}

	list_h			= ListH24;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );

	//TCB_ChangeFunc( tcb, D_Nohara_24_Main );	//TCBの動作関数切り替え
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );	//TCBの動作関数切り替え
	return;
}
 
//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	tcb		TCB_PTR型
 * @param	work	ワーク
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_24_Main( TCB_PTR tcb, void * work )
{
	EVENTWORK* ev;
	D_NOHARA_WORK* wk;
	wk = (D_NOHARA_WORK*)work;

	ev = SaveData_GetEventWork( wk->fsys->savedata );

	switch( wk->cursor_bak ){
	case 0:
		//バッテリーMAX
		SysWork_BtlSearcherBatterySet( ev, BS_BATTERY_MAX );
		break;

	case 1:
		//バッテリーCLR
		SysWork_BtlSearcherBatterySet( ev, 0 );
		break;

	case 2:
		//クリアーMAX
		SysWork_BtlSearcherClearSet( ev, BS_CLEAR_MAX );
		break;

	case 3:
		//クリアーCLR
		SysWork_BtlSearcherClearSet( ev, 0 );
		break;

	case 4:
		//起動
		EventSet_Script( wk->fsys, SCRID_BTL_SEARCHER, NULL );
		TcbBmpDel( tcb, work );		//TCBBMP開放
		return;						//注意！

	case 5:
		//レベル１セット
		SysFlag_BsLvSet( ev, 1 );

		MyItem_AddItem( SaveData_GetMyItem(wk->fsys->savedata),
						ITEM_BATORUSAATYAA, 1, HEAPID_BASE_DEBUG);
		break;

	case 6:
		//レベル２セット
		SysFlag_BsLvSet( ev, 2 );
		break;

	case 7:
		//レベル３セット
		SysFlag_BsLvSet( ev, 3 );
		break;

	case 8:
		//レベル４セット
		SysFlag_BsLvSet( ev, 4 );
		break;

	case 9:
		//レベル５セット
		SysFlag_BsLvSet( ev, 5 );
		break;

	default:
		return;
	};

	wk->seq = 0;
	TCB_ChangeFunc( tcb, DebugNoharaMenuMain );		//TCBの動作関数切り替え
	return;
}


//==============================================================================================
//
//	25	BGMオフ
//
//==============================================================================================
extern void Snd_DebugBgmFlagSet( u8 sw );

//--------------------------------------------------------------
/**
 * @brief	BGMオフ
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_25( TCB_PTR tcb, void * work )
{
#ifdef PM_DEBUG
	Snd_DebugBgmFlagSet( 1 );
	Snd_Stop();
#endif

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}


//==============================================================================================
//
//	26	BGMオン
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BGMオン
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_26( TCB_PTR tcb, void * work )
{
#ifdef PM_DEBUG
	u16 bgm_no;
	D_NOHARA_WORK* wk = (D_NOHARA_WORK*)work;

	Snd_DebugBgmFlagSet( 0 );

	//サウンドデータセット(シーンが変更されない時は何もしない)
	Snd_SceneSet( SND_SCENE_DUMMY );
	bgm_no = Snd_FieldBgmNoGet( wk->fsys, wk->fsys->location->zone_id );
	Snd_ZoneBgmSet(Snd_FieldBgmNoGetNonBasicBank(wk->fsys,wk->fsys->location->zone_id));//zone set

	Snd_DataSetByScene( SND_SCENE_FIELD, bgm_no, 1 );
#endif

	TcbBmpDel( tcb, work );		//TCBBMP開放
	return;
}






//--------------------------------------------------------------
/**
 * @brief	バイナリメッセージファイル読み込み、表示テスト
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_89(void)
{
#if 1
	return;
#else
	static u16 * pMsg = NULL;

	//debug_msg.datはcvsに登録していないので注意！
	pMsg = (u16 *)sys_LoadFile( HEAPID_BASE_DEBUG, "/data/script/debug_msg.dat" );
	FieldTalkWinPut();
	msg_no_print( pMsg );
	FieldTalkMsgStart( pMsg, 1 );					//第2引数=skip
	sys_FreeMemoryEz( pMsg );

	return;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	トラックミュートテスト
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void D_Nohara_72(void)
{
	Snd_PlayerSetTrackMute( SND_HANDLE_FIELD, ( (1 << 0) | (2 << 0) ), TRUE );
	return;
}


















//==============================================================================================
//
//
//
//==============================================================================================

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList2[] = {
	{ msg_debug_nohara_25, (u32)D_Nohara_25 },
	{ msg_debug_nohara_26, (u32)D_Nohara_26 },
};

static const BMPLIST_HEADER DebugListH2 = {
	NULL,					//表示文字データポインタ

	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList2),	//リスト項目数
	9,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	BGMデバックメニュー呼び出し(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugBgmMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//波形格納バッファを確保したフラグOFF
	wk->waveout_flag	= 0;								//鳴き声再生中フラグOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList2), HEAPID_BASE_DEBUG );

	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList2); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList2[i].str_id, DebugMenuList2[i].param );
	}

	list_h			= DebugListH2;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}


//==============================================================================================
//
//	デバック「のはら」ではない所からの「デバックスクリプト」呼び出し
//
//==============================================================================================

static const struct{
	u32  str_id;
	u32  param;
}DebugMenuList3[] = {
	{ msg_debug_nohara_11, (u32)D_Nohara_11 },
};

static const BMPLIST_HEADER DebugListH3 = {
	NULL,					//表示文字データポインタ

	NULL,					//カーソル移動ごとのコールバック関数
	NULL,					//一列表示ごとのコールバック関数

	NULL,					//GF_BGL_BMPWINのポインタ

	NELEMS(DebugMenuList3),	//リスト項目数
	9,						//表示最大項目数

	0,						//ラベル表示Ｘ座標
	8,						//項目表示Ｘ座標
	0,						//カーソル表示Ｘ座標
	0,						//表示Ｙ座標
/*
	FBMP_COL_BLACK,			//文字色
	FBMP_COL_WHITE,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
*/
	FBMP_COL_WHITE,			//文字色
	FBMP_COL_BLACK,			//背景色
	FBMP_COL_BLK_SDW,		//文字影色
	0,						//文字間隔Ｘ
	16,						//文字間隔Ｙ
	BMPLIST_LRKEY_SKIP,		//ページスキップタイプ
	FONT_SYSTEM,			//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	0						//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
};

//--------------------------------------------------------------
/**
 * @brief	BGMデバックメニュー呼び出し(fld_debug.c)
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void DebugScriptMenuInit( FIELDSYS_WORK* fsys )
{
	int i;
	BMPLIST_HEADER list_h;
	D_NOHARA_WORK* wk;

	wk = (D_NOHARA_WORK*)TCB_GetWork( PMDS_taskAdd(DebugNoharaMenuMain, sizeof(D_NOHARA_WORK), 0, HEAPID_BASE_DEBUG) );

	wk->seq				= 0;
	wk->sel				= 0;
	wk->work			= 0;
	wk->wave_buf_flag	= 0;								//波形格納バッファを確保したフラグOFF
	wk->waveout_flag	= 0;								//鳴き声再生中フラグOFF
	wk->fsys			= fsys;

	GF_BGL_BmpWinAddEx( wk->fsys->bgl, &wk->bmpwin[0], &DebugNoharaWinData );	//ビットマップ追加

	wk->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList3), HEAPID_BASE_DEBUG );

	wk->wordset = WORDSET_Create( HEAPID_BASE_DEBUG );

	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, 
								NARC_msg_debug_nohara_dat, HEAPID_BASE_DEBUG);

	for( i=0; i < NELEMS(DebugMenuList3); i++ ){
		BMP_MENULIST_AddArchiveString( wk->menulist, wk->msgman, 
										DebugMenuList3[i].str_id, DebugMenuList3[i].param );
	}

	list_h			= DebugListH3;
	list_h.list		= wk->menulist;
	list_h.win		= &wk->bmpwin[0];
	wk->lw			= BmpListSet( &list_h, 0, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinOn( &wk->bmpwin[0] );
	return;
}


