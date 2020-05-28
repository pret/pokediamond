//==============================================================================================
/**
 * @file	ev_win.c
 * @brief	イベントウィンドウ(BMPメニュー、BMPリスト)
 * @author	Satoshi Nohara
 * @date	2005.07.29
 */
//==============================================================================================
#include "common.h"
#include "gflib/msg_print.h"			//STRCODE
#include "system/msgdata.h"				//MSGMAN_TYPE_DIRECT
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/pm_str.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/wordset.h"				//WORDSET_ExpandStr
#include "system/wipe.h"				//WIPE_SYS_EndCheck
#include "system/window.h"
#include "savedata/coin.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "mapdefine.h"					//ZONE_ID_C01FS0101
#include "ev_win.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_ev_win.h"			//msg_ev_win_016
#include "msgdata/msg_shop.h"


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
static void EvWin_Init( FIELDSYS_WORK* fsys, EV_WIN_WORK* wk, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//BMPメニュー
EV_WIN_WORK * CmdEvBmpMenu_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );
void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  );
void CmdEvBmpMenu_Start( EV_WIN_WORK* wk );

//BMPメニュー縦横
void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max );
static void BmpMenuHV_h_default_set( EV_WIN_WORK* wk, u8 x_max, u8 y_max );

static void BmpMenu_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 param  );
static u32 BmpMenu_length_get( EV_WIN_WORK* wk );
static void BmpMenu_h_default_set(EV_WIN_WORK* wk);
static void EvBmpMenu_MainTCB( TCB_PTR tcb, void* wk );


//BMPリスト
EV_WIN_WORK * CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );
void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );
void CmdEvBmpList_Start( EV_WIN_WORK* wk );

static void BmpList_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );
static u32 BmpList_length_get( EV_WIN_WORK* wk );
static void BmpList_h_default_set(EV_WIN_WORK* wk);
static void	BmpList_CallBack( BMPLIST_WORK* lw, u32 param, u8 y );
static void EvBmpList_MainTCB( TCB_PTR tcb, void* wk );
static void EvBmpList_Del( EV_WIN_WORK* wk );
static void talk_msg_print( EV_WIN_WORK* wk, u16 talk_msg_id, u32 wait );
static void talk_msg_update( EV_WIN_WORK* wk );


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define EV_WIN_FONT		(FONT_SYSTEM)			//フォント指定
//#define EV_WIN_FONT	(FONT_TALK)				//フォント指定

//#define EVWIN_MSG_BUF_SIZE	(32*2)			//メッセージバッファサイズ
#define EVWIN_MSG_BUF_SIZE		(40*2)			//メッセージバッファサイズ

//BMPメニュー
#define EV_WIN_MENU_MAX			(28)			//メニュー項目の最大数

//BMPリスト
#define EV_WIN_LIST_MAX			(28)			//リスト項目の最大数

#define	EV_WIN_MSG_MAX			(28)			//MSGバッファの最大数

//BMPリストヘッダー定義
#define EV_LIST_LINE			(8)				//表示最大項目数
#define EV_LIST_RABEL_X			(1)				//ラベル表示Ｘ座標
#define EV_LIST_DATA_X			(12)			//項目表示Ｘ座標
#define EV_LIST_CURSOR_X		(2)				//カーソル表示Ｘ座標
#define EV_LIST_LINE_Y			(1)				//表示Ｙ座標

//カーソル幅
#define EV_WIN_CURSOR_WIDTH		(12)			//カーソル幅

#define EV_WIN_DEFAULT_WAIT		(3)				//キー操作がすぐに入らないように基本ウェイト


// おこずかいウィンドウ定義
#define	EVWIN_GOLD_SX		( 10 )								// 所持金ウィンドウXサイズ
#define	EVWIN_GOLD_SY		( 4 )								// 所持金ウィンドウYサイズ
#define	EVWIN_GOLD_FRM		( SHOP_FRM_WINDOW )					// 所持金ウィンドウBGフレーム
#define	EVWIN_GOLD_PAL		( FLD_SYSFONT_PAL )					// 所持金ウィンドウパレット
#define	EVWIN_GOLD_CGX		( 1 )								// 所持金ウィンドウキャラ使用位置
#define	EVWIN_GOLD_CGX_SIZ	( EVWIN_GOLD_SX * EVWIN_GOLD_SY )	// 所持金ウィンドウキャラサイズ

#define	GOLD_BUFLEN			( 16 )					// 所持金文字数 ( (6桁+円+EOM)*2 )
#define	EVWIN_GOLD_SX_DOT	( EVWIN_GOLD_SX * 8 )	// 所持金ウィンドウXサイズ（ドット）
#define	EVWIN_GOLD_VAL_PY	( 16 )					// 所持金表示Y座標

// コインウィンドウ定義
#define	EVWIN_COIN_SX		( 10 )									// コインウィンドウXサイズ
#define	EVWIN_COIN_SY		( 2 )									// コインウィンドウYサイズ
#define	EVWIN_COIN_FRM		( SHOP_FRM_WINDOW )						// コインウィンドウBGフレーム
#define	EVWIN_COIN_PAL		( FLD_SYSFONT_PAL )						// コインウィンドウパレット
#define	EVWIN_COIN_CGX		( EVWIN_GOLD_CGX+EVWIN_GOLD_CGX_SIZ )	// コインウィンドウキャラ使用位置
#define	EVWIN_COIN_CGX_SIZ	( EVWIN_COIN_SX * EVWIN_COIN_SY )		// コインウィンドウキャラサイズ

#define	COIN_BUFLEN			( 16 )					// コイン文字数 ( (4桁+円+EOM)*2 )
#define	EVWIN_COIN_SX_DOT	( EVWIN_COIN_SX * 8 )	// コインウィンドウXサイズ（ドット）

#define BP_BUFLEN			((4+2+1)*2)	//バトルポイント文字数((4桁+BP+EOM)*2)

// ↓ここから使って下さい！！
#define	EVWIN_FREE_CGX		( EVWIN_COIN_CGX+EVWIN_COIN_CGX_SIZ )	// フリーのキャラ位置



//==============================================================================================
//
//	構造体
//
//==============================================================================================
struct _EV_WIN_WORK{
	FIELDSYS_WORK * fsys;						//FIELDSYS_WORKのポインタ
	TCB_PTR	tcb;

 	GF_BGL_BMPWIN bmpwin;						//BMPウィンドウデータ
 	GF_BGL_BMPWIN* talk_bmpwin;					//BMP会話ウィンドウデータ
	
	STRBUF* msg_buf[EV_WIN_MSG_MAX];			//メッセージデータのポインタ
	MSGDATA_MANAGER* msgman;					//メッセージマネージャー
	WORDSET* wordset;							//単語セット

	u8  wait;									//ウェイト
	u8  menu_id;								//BMPメニューID
	u8  cursor_pos;								//カーソル位置
	u8  cancel:1;								//キャンセル
	u8  msgman_del_flag:1;						//メッセージマネージャー削除フラグ
	u8  dmy:6;									//

	u8  x;										//ウィンドウ位置X
	u8  y;										//ウィンドウ位置Y
	u8  dmyy;									//メニューナンバー
	u8  list_no;								//メニュー項目の何番目か

	u16* pMsg;									//メッセージデータ
	u16* work;									//結果取得ワーク
 
	//BMPメニュー(bmp_menu.h)
	BMPMENU_HEADER MenuH;						//BMPメニューヘッダー
	BMPMENU_WORK * mw;							//BMPメニューワーク
	BMPMENU_DATA Data[EV_WIN_MENU_MAX];			//BMPメニューデータ

	//BMPリスト
	BMPLIST_HEADER ListH;						//BMPリストヘッダー
	BMPLIST_WORK* lw;							//BMPリストデータ
	u16 list_bak;								//リスト位置バックアップ
	u16 cursor_bak;								//カーソル位置バックアップ
	BMPLIST_DATA list_Data[EV_WIN_LIST_MAX];	//リストデータ
	u16 talk_msg_id[EV_WIN_LIST_MAX];			//リストデータに対になる会話メッセージID

	u16 pos_bak;
};


//==============================================================================================
//
//	関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	イベントウィンドウ　ワーク初期化
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvWin_Init( FIELDSYS_WORK* fsys, EV_WIN_WORK* wk, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	int i;

	if( msgman == NULL ){
		//メッセージデータマネージャー作成
		wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD);
		wk->msgman_del_flag = 1;
	}else{
		wk->msgman = msgman;	//引継ぎ
		wk->msgman_del_flag = 0;
	}

	//wk->wordset = WORDSET_Create( HEAPID_FIELD );
	wk->wordset		= wordset;		//スクリプトを引き継ぐ

	wk->fsys		= fsys;
	wk->work		= work;
	wk->cancel		= cancel;
	wk->cursor_pos	= cursor;
	wk->x			= x;
	wk->y			= y;
	wk->list_no		= 0;
	wk->talk_bmpwin	= talk_bmpwin;
	wk->wait		= EV_WIN_DEFAULT_WAIT;
	wk->pos_bak		= cursor;

	for( i=0; i < EV_WIN_MENU_MAX ;i++ ){
		wk->Data[i].str			= NULL;
		wk->Data[i].param		= 0;
	}

	for( i=0; i < EV_WIN_LIST_MAX ;i++ ){
		wk->list_Data[i].str	= NULL;
		wk->list_Data[i].param	= 0;
		wk->talk_msg_id[i] = EV_WIN_TALK_MSG_NONE;
	}

	//MSGMAN_Createの後に処理
	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		wk->msg_buf[i] = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	}

	//選択した値を取得するワークを初期化
	*wk->work = EV_WIN_NOTHING;

	return;
}


//==============================================================================================
//
//	BMPメニュー関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　初期化
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	"EV_WIN_WORK型のアドレス、NULLは失敗"
 */
//--------------------------------------------------------------
EV_WIN_WORK * CmdEvBmpMenu_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	EV_WIN_WORK* wk;
	int i;

	wk = sys_AllocMemory( HEAPID_FIELD, sizeof(EV_WIN_WORK) );
	if( wk == NULL ){
		OS_Printf( "ev_win.c Alloc ERROR!" );
		return NULL;
	}
	memset( wk, 0, sizeof(EV_WIN_WORK) );

	//ワーク初期化	
	EvWin_Init( fsys, wk, x, y, cursor, cancel, work, wordset, talk_bmpwin, msgman );

	return wk;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPMENUパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	BmpMenu_list_make( wk, msg_id, param  );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPMENUパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenu_Start( EV_WIN_WORK* wk )
{
	u32 len;

	//(最大文字数＋カーソル) * フォントサイズ
	//len = (BmpMenu_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpMenu_length_get(wk);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, wk->list_no*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );

	//メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//メニューウィンドウを描画
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);


	//メニューヘッダー初期設定
	BmpMenu_h_default_set(wk);
	wk->mw = BmpMenuAdd( &wk->MenuH, wk->cursor_pos, HEAPID_FIELD );

	//TCB追加
	wk->tcb	= TCB_Add( EvBmpMenu_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPMENUパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenu_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < EV_WIN_MENU_MAX, "メニュー項目数オーバー！" );

#if 1
	{
		//展開込み
		
		STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );	//コピー用バッファ

		MSGMAN_GetString( wk->msgman, msg_id, tmp_buf2 );
		WORDSET_ExpandStr( wk->wordset, wk->msg_buf[wk->list_no], tmp_buf2 );	//展開
		wk->Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];

		STRBUF_Delete( tmp_buf2 );
	}
#else
	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
#endif

	wk->Data[ wk->list_no ].param = param;
	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	項目の中から最大文字数を取得
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static u32 BmpMenu_length_get( EV_WIN_WORK* wk )
{
	int i;
	u32 ret,tmp_ret;

	ret		= 0;
	tmp_ret = 0;

	for( i=0; i < wk->list_no ;i++ ){
		if( wk->Data[i].str == NULL ){
			break;
		}

		//ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, wk->msg_buf[i], 0 );
		ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, (STRBUF*)wk->Data[i].str, 0 );

		if( tmp_ret < ret ){
			tmp_ret = ret;
		}
	}

	return tmp_ret + EV_WIN_CURSOR_WIDTH;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュ	ヘッダー初期設定
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenu_h_default_set(EV_WIN_WORK* wk)
{
	wk->MenuH.menu		= wk->Data;

	wk->MenuH.win		= &wk->bmpwin;

	wk->MenuH.font		= EV_WIN_FONT;
	wk->MenuH.x_max		= 1;
	wk->MenuH.y_max		= wk->list_no;
	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;

	//メニュー項目が4種類以上だった時はカーソルのループ有りにする
	if( wk->list_no >= 4 ){
		wk->MenuH.loop_f	= 1;			//有
	}else{
		wk->MenuH.loop_f	= 0;			//無
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　メイン
 *
 * @param	tcb			TCB_PTR
 * @param	wk			ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvBmpMenu_MainTCB( TCB_PTR tcb, void* wk )
{
	u32 ret;
	EV_WIN_WORK *swk;
	swk = (EV_WIN_WORK *)wk;

	//ウェイト
	if( swk->wait != 0 ){
		swk->wait--;
		return;
	}

	//ワイプ中は処理しない
	if( WIPE_SYS_EndCheck() == FALSE ){
		return;
	}

	ret = BmpMenuMain( swk->mw );
	switch( ret ){
	case BMPMENU_NULL:
		break;
	case BMPMENU_CANCEL:
		if( swk->cancel == TRUE ){			//TRUE = Bキャンセル有効
			*swk->work = EV_WIN_B_CANCEL;	//選択した値をワークに代入
			EvBmpMenu_Del(wk);
		}
		break;
	default:
		*swk->work = ret;					//選択した値をワークに代入
		EvBmpMenu_Del(wk);
		break;
	};

	return;
};

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー　終了
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 *
 * SEQ_SE_DP_SELECTを鳴らしている！
 */
//--------------------------------------------------------------
void EvBmpMenu_Del( EV_WIN_WORK* wk )
{
	int i;

	Snd_SePlay(SEQ_SE_DP_SELECT);	//注意！

	BmpMenuExit( wk->mw, NULL );
	BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( wk->MenuH.win );

	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	if( wk->msgman_del_flag == 1 ){
		//WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
	}

	TCB_Delete( wk->tcb );
	sys_FreeMemoryEz( wk );
	return;
}


//==============================================================================================
//
//	BMPリスト関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　初期化
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	"EV_WIN_WORK型のアドレス、NULLは失敗"
 */
//--------------------------------------------------------------
EV_WIN_WORK * CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	return CmdEvBmpMenu_Init( fsys, x, y, cursor, cancel, work, wordset, talk_bmpwin, msgman  );
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	talk_msg_id	会話メッセージID
 * @param	param		BMPLISTパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  )
{
	BmpList_list_make( wk, msg_id, talk_msg_id, param  );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpList_Start( EV_WIN_WORK* wk )
{
	u32 len;

	//(最大文字数＋カーソル) * フォントサイズ
	//len = (BmpList_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpList_length_get(wk);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	//表示最大項目数チェック
	if( wk->list_no > EV_LIST_LINE ){
		GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, EV_LIST_LINE*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );
	}else{
		GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, wk->list_no*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );
	}

	//メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//メニューウィンドウを描画
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//リストヘッダー初期設定
	BmpList_h_default_set(wk);

	wk->lw = BmpListSet( (const BMPLIST_HEADER*)&wk->ListH, 0, wk->cursor_pos, HEAPID_FIELD );

	//会話ウィンドウ更新
	talk_msg_update( wk );

	//TCB追加
	wk->tcb	= TCB_Add( EvBmpList_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	リスト作成
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	talk_msg_id	会話メッセージID
 * @param	param		BMPLISTパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < EV_WIN_LIST_MAX, "リスト項目数オーバー！" );

#if 1
	{
		//展開込み
		
		STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );	//コピー用バッファ

		MSGMAN_GetString( wk->msgman, msg_id, tmp_buf2 );
		WORDSET_ExpandStr( wk->wordset, wk->msg_buf[wk->list_no], tmp_buf2 );	//展開
		wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];

		STRBUF_Delete( tmp_buf2 );
	}
#else

	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
	//*st = (const void *)&wk->msg_buf[wk->list_no][0];
#endif
	if( param == EV_WIN_LIST_LABEL ){
		wk->list_Data[ wk->list_no ].param = BMPLIST_RABEL;
		//*pa = BMPLIST_RABEL;
	}else{
		wk->list_Data[ wk->list_no ].param = param;
		//*pa = param;
	}

	wk->talk_msg_id[ wk->list_no ] = talk_msg_id;
	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	項目の中から最大文字数を取得
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static u32 BmpList_length_get( EV_WIN_WORK* wk )
{
	int i;
	u32 ret,tmp_ret;

	ret		= 0;
	tmp_ret = 0;

	for( i=0; i < wk->list_no ;i++ ){
		if( wk->list_Data[i].str == NULL ){
			break;
		}

		//ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, wk->msg_buf[i], 0 );
		ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, (STRBUF*)wk->list_Data[i].str, 0 );
		
		if( tmp_ret < ret ){
			tmp_ret = ret;
		}
	}

	return tmp_ret + EV_WIN_CURSOR_WIDTH;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	ヘッダー初期設定
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_h_default_set(EV_WIN_WORK* wk)
{
	wk->ListH.list		= wk->list_Data;
	wk->ListH.call_back = NULL;
	wk->ListH.icon		= BmpList_CallBack;
	wk->ListH.win		= &wk->bmpwin;

	wk->ListH.count		= wk->list_no;
	wk->ListH.line		= EV_LIST_LINE;

	wk->ListH.rabel_x	= EV_LIST_RABEL_X;
	wk->ListH.data_x	= EV_LIST_DATA_X;
	wk->ListH.cursor_x	= EV_LIST_CURSOR_X;
	wk->ListH.line_y	= EV_LIST_LINE_Y;

	wk->ListH.f_col		= FBMP_COL_BLACK;
	wk->ListH.b_col		= FBMP_COL_WHITE;		
	wk->ListH.s_col		= FBMP_COL_BLK_SDW;

	wk->ListH.msg_spc	= 0;
	wk->ListH.line_spc	= 16;
	wk->ListH.page_skip	= BMPLIST_LRKEY_SKIP;
	wk->ListH.font		= EV_WIN_FONT;
	wk->ListH.c_disp_f	= 0;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	リストシステムからのコールバック※一行表示ごと
 *
 * @param	lw			BMPLIST_WORK型のポインタ
 * @param	param		選択時リターンパラメータ
 * @param	y			
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void	BmpList_CallBack(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if( param == BMPLIST_RABEL ){
		BmpListTmpColorChange( lw, FBMP_COL_RED, FBMP_COL_WHITE, FBMP_COL_RED_SDW );
	}else{
		BmpListTmpColorChange( lw, FBMP_COL_BLACK, FBMP_COL_WHITE, FBMP_COL_BLK_SDW );
	}
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　リストメイン
 *
 * @param	tcb			TCB_PTR
 * @param	wk			ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvBmpList_MainTCB( TCB_PTR tcb, void* wk )
{
	u16 tmp_pos_bak;
	u32	ret;
	EV_WIN_WORK* swk;
	swk = (EV_WIN_WORK*)wk;

	//ウェイト
	if( swk->wait != 0 ){
		swk->wait--;
		return;
	}

	//ワイプ中は処理しない
	if( WIPE_SYS_EndCheck() == FALSE ){
		return;
	}

	ret = BmpListMain( swk->lw );

	//BMPリストの全体位置を取得
	tmp_pos_bak = swk->pos_bak;		//退避
	BmpListDirectPosGet( swk->lw, &swk->pos_bak );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != swk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	//会話ウィンドウのメッセージ更新
	if( (sys.repeat & PAD_KEY_UP) || (sys.repeat & PAD_KEY_DOWN) ||
		(sys.repeat & PAD_KEY_LEFT) || (sys.repeat & PAD_KEY_RIGHT) ){
		talk_msg_update( swk );
	}

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		if( swk->cancel == TRUE ){			//TRUE = Bキャンセル有効
			Snd_SePlay( SEQ_SE_DP_SELECT );
			*swk->work = EV_WIN_B_CANCEL;	//選択した値をワークに代入
			EvBmpList_Del(wk);
		}
		break;
	default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
		*swk->work = ret;					//選択した値をワークに代入
		EvBmpList_Del(wk);
		break;
	};

	return;
};

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　リスト終了
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 *
 * @retval	none
 *
 * SEQ_SE_DP_SELECTを鳴らしている！
 */
//--------------------------------------------------------------
static void EvBmpList_Del( EV_WIN_WORK* wk )
{
	int i;

	Snd_SePlay(SEQ_SE_DP_SELECT);	//注意！

	BmpListExit( wk->lw, NULL, NULL );
	BmpMenuWinClear( wk->ListH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->bmpwin );

	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	if( wk->msgman_del_flag == 1 ){
		//WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
	}

	TCB_Delete( wk->tcb );
	sys_FreeMemoryEz( wk );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	会話ウィンドウにメッセージを一括表示
 *
 * @param	wk			EV_WIN_WORK型のアドレス
 * @param	talk_msg_id	会話メッセージID
 * @param	wait		メッセージウェイト
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_print( EV_WIN_WORK* wk, u16 talk_msg_id, u32 wait )
{
	STRBUF* tmp_buf = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );

	//メッセージクリア
	GF_BGL_BmpWinDataFill( wk->talk_bmpwin, (FBMP_COL_WHITE) );

	MSGMAN_GetString( wk->msgman, talk_msg_id, tmp_buf );

	//登録された単語を使って文字列展開する
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( wk->talk_bmpwin, FONT_TALK, tmp_buf2, 0, 0, wait, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	会話ウィンドウにメッセージを一括表示
 *
 * @param	wk			EV_WIN_WORK型のアドレス
 * @param	talk_msg_id	会話メッセージID
 * @param	wait		メッセージウェイト
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_update( EV_WIN_WORK* wk )
{
	BmpListDirectPosGet( wk->lw, &wk->cursor_bak );		//カーソル座標取得
	if( wk->talk_msg_id[wk->cursor_bak] != EV_WIN_TALK_MSG_NONE ){
		talk_msg_print( wk, wk->talk_msg_id[wk->cursor_bak], MSG_ALLPUT );
	}
	return;
}


//==============================================================================================
//
//	エレベータフロア関連
//
//==============================================================================================
#define FLOOR_WIN_SIZE_X			(8)		//フロアウィンドウのＸサイズ
#define FLOOR_WIN_SIZE_Y			(4)		//フロアウィンドウのＹサイズ
#define FLOOR_TITLE_X				(0)		//「げんざいの　フロア」の表示位置
#define FLOOR_TITLE_Y				(0)
#define FLOOR_TITLE_X2				(8*4)	//「○かい」の表示位置
#define FLOOR_TITLE_Y2				(16)
#define EV_WIN_SIZE_X				(16)	//左側に表示される選択ウィンドウのＸサイズ
#define EV_WIN_SIZE_Y				(10)	//左側に表示される選択ウィンドウのＹサイズ

static void ElevatorFloorMainTCB( TCB_PTR tcb, void* wk );
void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset);
static void ev_win_msg_print( EV_WIN_WORK* wk, u16 msg_id, u8 x, u8 y );


//--------------------------------------------------------------
/**
 * @brief	フロアウィンドウ表示
 *
 * @param	fsys		FIELDSYS_WORK型のポインタ
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	work		結果を代入するワークのポインタ
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset)
{
	u32 len;
	EV_WIN_WORK* wk;

	//BMPメニュー初期化(ev_win.gmm固定)
	wk = CmdEvBmpMenu_Init( fsys, x, y, 0, 0, work, wordset, NULL, NULL );

	//(最大文字数) * フォントサイズ
	len = (FLOOR_WIN_SIZE_X) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	//左側に表示するイベントウィンドウのオフセットを入れる！
	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
						len, FLOOR_WIN_SIZE_Y, FLD_SYSFONT_PAL, EVWIN_FREE_CGX + (EV_WIN_SIZE_X*EV_WIN_SIZE_Y) );

	//メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet(wk->fsys->bgl,FLD_MBGFRM_FONT,MENU_WIN_CGX_NUM,MENU_WIN_PAL,0,HEAPID_FIELD);

	//メニューウィンドウを描画
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//指定範囲を塗りつぶし
	GF_BGL_BmpWinFill( &wk->bmpwin, FBMP_COL_WHITE, 0, 0, (len*8), (FLOOR_WIN_SIZE_Y*8) );
	
	ev_win_msg_print( wk, msg_ev_win_016, FLOOR_TITLE_X, FLOOR_TITLE_Y );	//「げんざいの　フロア」
	ev_win_msg_print( wk, msg_ev_win_017, FLOOR_TITLE_X2, FLOOR_TITLE_Y2 );	//「○かい」

	wk->MenuH.win = &wk->bmpwin;
	GF_BGL_BmpWinOn( &wk->bmpwin );
	
	//TCB追加
	wk->tcb	= TCB_Add( ElevatorFloorMainTCB, wk, 0 );

	return;
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
static void ev_win_msg_print( EV_WIN_WORK* wk, u16 msg_id, u8 x, u8 y )
{
	STRBUF* tmp_buf = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );
	GF_STR_PrintSimple( &wk->bmpwin, EV_WIN_FONT, tmp_buf2, x, y, MSG_NO_PUT, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	フロアウィンドウ表示 メイン
 *
 * @param	tcb			TCB_PTR
 * @param	wk			ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ElevatorFloorMainTCB( TCB_PTR tcb, void* wk )
{
	int i;
	EV_WIN_WORK *swk;
	swk = (EV_WIN_WORK *)wk;

	//通常、WK_ELEVATOR_FLOORの値が"FLOOR_NOTHING"になるまで監視している処理
	if( *swk->work == FLOOR_NOTHING ){
		BmpMenuWinClear( swk->MenuH.win, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( swk->MenuH.win );

		for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
			STRBUF_Delete( swk->msg_buf[i] );
		}

		if( swk->msgman_del_flag == 1 ){
			//WORDSET_Delete( swk->wordset );
			MSGMAN_Delete( swk->msgman );
		}

		TCB_Delete( swk->tcb );
		sys_FreeMemoryEz( swk );
	}

	return;
};

//--------------------------------------------------------------
/**
 * 特殊接続先から、現在のフロアナンバーを取得
 *
 * @param   zone_id		ゾーンID
 *
 * @retval  "フロアナンバー"
 *
 * エレベータマップが増えたら対応していく！
 */
//--------------------------------------------------------------
u16 ElevatorNowFloorGet( int zone_id )
{
	u16 floor;

	switch( zone_id ){

	//-------------------------------
	case ZONE_ID_C05R0101:
		floor = FLOOR_C05R0103_1F;
		break;

	case ZONE_ID_C05R0102:
		floor = FLOOR_C05R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_C08R0801:
		floor = FLOOR_C08R0802_2F;
		break;

	case ZONE_ID_C08:
		floor = FLOOR_C08R0802_1F;
		break;

	//-------------------------------
	case ZONE_ID_C05R0801:
		floor = FLOOR_C05R0103_1F;
		break;

	case ZONE_ID_C05R0802:
		floor = FLOOR_C05R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_T07R0101:
		floor = FLOOR_T07R0103_1F;
		break;

	case ZONE_ID_T07R0102:
		floor = FLOOR_T07R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_C07R0201:
		floor = FLOOR_C07R0206_1F;
		break;

	case ZONE_ID_C07R0202:
		floor = FLOOR_C07R0206_2F;
		break;

	case ZONE_ID_C07R0203:
		floor = FLOOR_C07R0206_3F;
		break;

	case ZONE_ID_C07R0204:
		floor = FLOOR_C07R0206_4F;
		break;

	case ZONE_ID_C07R0205:
		floor = FLOOR_C07R0206_5F;
		break;

	//-------------------------------
	case ZONE_ID_C01R0201:
		floor = FLOOR_C01R0208_1F;
		break;

	case ZONE_ID_C01R0202:
		floor = FLOOR_C01R0208_2F;
		break;

	case ZONE_ID_C01R0203:
		floor = FLOOR_C01R0208_3F;
		break;

	case ZONE_ID_C01R0204:
		floor = FLOOR_C01R0208_4F;
		break;

	//追加する
	//case

	default:
		floor = FLOOR_C05R0103_1F;
	};

	return floor;
}


//==============================================================================================
//
//	BMPメニュー縦横関連
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー縦横　開始
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	x_max		横方向項目最大数(必ず1以上)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max )
{
	u32 len;
	u8 y_max;

	//(最大文字数＋カーソル) * フォントサイズ
	//len = (BmpMenu_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpMenu_length_get(wk);
	//OS_Printf( "len = %d\n", len );

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	y_max = (wk->list_no / x_max);			//Yサイズ
	if( (wk->list_no % x_max) != 0 ){		//余りがあったら補正
		y_max++;
	}

	//OS_Printf( "len = %d\n", len );
	//OS_Printf( "x_max = %d\n", x_max );
	//OS_Printf( "len*x_max = %d\n", (len*x_max) );

	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
								(len * x_max), y_max*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );

	//注意！
	//最大文字数で、横方向の文字を描画しているので、
	//「せつめいをきく　いいえ　　　　」みたくなる
	//
	//「せつめいをきく　いいえ　　　　」
	//「はい　　　　　　　　　　　　　」は出来ないので、
	//ダミーの空白文字を入れる必要がある！
	
	//メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//メニューウィンドウを描画
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//メニューヘッダー初期設定
	BmpMenuHV_h_default_set( wk, x_max, y_max );
	wk->mw = BmpMenuAdd( &wk->MenuH, wk->cursor_pos, HEAPID_FIELD );

	//TCB追加
	wk->tcb	= TCB_Add( EvBmpMenu_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー縦横	ヘッダー初期設定
 *
 * @param	wk			EV_WIN_WORK型のポインタ
 * @param	x_max		横方向項目最大数(必ず1以上)
 * @param	y_max		縦方向項目最大数(必ず1以上)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenuHV_h_default_set( EV_WIN_WORK* wk, u8 x_max, u8 y_max )
{
	wk->MenuH.menu		= wk->Data;

	wk->MenuH.win		= &wk->bmpwin;

	wk->MenuH.font		= EV_WIN_FONT;
	wk->MenuH.x_max		= x_max;
	wk->MenuH.y_max		= y_max;

	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;

#if 0
	//メニュー項目が4種類以上だった時はカーソルのループ有りにする
	if( wk->list_no >= 4 ){
		wk->MenuH.loop_f	= 1;			//有
	}else{
		wk->MenuH.loop_f	= 0;			//無
	}
#endif

	return;
}




//==============================================================================================
//
//	所持金ウィンドウ
//	所持コインウィンドウ
//
//==============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_GoldWinDelで削除すること！
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_GoldWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_GOLD_SX, EVWIN_GOLD_SY, EVWIN_GOLD_PAL, EVWIN_GOLD_CGX );

	// メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// メニューウィンドウを描画
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// 指定範囲を塗りつぶし
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	{	// 「おこずかい」
		MSGDATA_MANAGER * man;
		STRBUF * str;

		man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_shop_dat, HEAPID_FIELD );
		str = MSGMAN_AllocString( man, mes_shop_05_01 );
		GF_STR_PrintSimple( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, NULL );
		MSGMAN_Delete( man );
		STRBUF_Delete( str );
	}
	EvWin_GoldWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ削除
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_GoldWinDel( GF_BGL_BMPWIN * win )
{
	BmpMenuWinClear( win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinFree( win, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * 所持金描画
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_GoldWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u32	gold;
	u32	px;

	GF_BGL_BmpWinFill(
		win, FBMP_COL_WHITE, 0, EVWIN_GOLD_VAL_PY,
		EVWIN_GOLD_SX*8, EVWIN_GOLD_SY*8-EVWIN_GOLD_VAL_PY );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_shop_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( GOLD_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, mes_shop_05_02 );
	gold = MyStatus_GetGold( SaveData_GetMyStatus(fsys->savedata) );

	WORDSET_RegisterNumber( wset, 0, gold, 6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_GOLD_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, EVWIN_GOLD_VAL_PY, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}


//--------------------------------------------------------------------------------------------
/**
 * 所持コインウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_CoinWinDelで削除すること！
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_CoinWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_COIN_SX, EVWIN_COIN_SY, EVWIN_COIN_PAL, EVWIN_COIN_CGX );

	// メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// メニューウィンドウを描画
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// 指定範囲を塗りつぶし
//	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	EvWin_CoinWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * 所持コインウィンドウ削除
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_CoinWinDel( GF_BGL_BMPWIN * win )
{
	BmpMenuWinClear( win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinFree( win, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * 所持コイン描画
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_CoinWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u32	coin;
	u32	px;

	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( COIN_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, msg_ev_win_168 );
	coin = COIN_GetValue( SaveData_GetMyCoin(fsys->savedata) );

	WORDSET_RegisterNumber( wset, 0, coin, 5, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_COIN_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 所持バトルポイントウィンドウ表示
 *
 * @param	fsys
 * @param	wk
 * @param	x		表示X座標
 * @param	y		表示Y座標
 *
 * @return	確保したBMPウィンドウ
 *
 *	EvWin_CoinWinDel(共有で使える)で削除すること！
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_BtlPointWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_COIN_SX, EVWIN_COIN_SY, EVWIN_COIN_PAL, EVWIN_COIN_CGX );

	// メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// メニューウィンドウを描画
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// 指定範囲を塗りつぶし
//	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	EvWin_BtlPointWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * 所持バトルポイント描画
 *
 * @param	fsys
 * @param	wk
 */
//--------------------------------------------------------------------------------------------
void EvWin_BtlPointWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u16	bp;
	u32	px;

	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( COIN_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, msg_bpgift_00 );
	bp	 = TowerScoreData_SetBattlePoint(
				SaveData_GetTowerScoreData(fsys->savedata),0,BTWR_DATA_get);

	WORDSET_RegisterNumber( wset, 0, bp, 5, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_COIN_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}
