//==============================================================================================
/**
 * @file	opneing_bmp.c
 * @brief	オープニング BMP
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "common.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/wordset.h"
#include "opening_bmp.h"


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================
extern u8 TalkWinNumGet(void);


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define OP_FONT_KIND		(FONT_SYSTEM)	//フォント種類

//「ぼうけん　とは？」
#define WIN_SEL1_PX			(1)
#define WIN_SEL1_PY			(4)
#define WIN_SEL1_SX			(15)
#define WIN_SEL1_SY			(6)
#define WIN_SEL1_CGX		(1)

//操作、ゲーム説明
#define WIN_GUIDE_PX		(1)
#define WIN_GUIDE_PY		(2)
#define WIN_GUIDE_SX		(32)		// タッチパネル説明が入りきっていなかったので29->32に変更 tomoya takahashi 2005/12/22
#define WIN_GUIDE_SY		(20)
#define WIN_GUIDE_CGX		(WIN_SEL1_CGX + WIN_SEL1_SX * WIN_SEL1_SY)
//1+15*6=91

//「おとこのこ」
#define WIN_SEL2_PX			(12)
#define WIN_SEL2_PY			(8)
#define WIN_SEL2_SX			(8)
#define WIN_SEL2_SY			(4)
#define WIN_SEL2_CGX		(WIN_GUIDE_CGX + WIN_GUIDE_SX * WIN_GUIDE_SY)
//91+28*20=656

//「オーキド会話」
#define WIN_OOKIDO_PX		(2)
#define WIN_OOKIDO_PY		(19)
#define WIN_OOKIDO_SX		(27)
#define WIN_OOKIDO_SY		(4)
#define WIN_OOKIDO_CGX		(WIN_SEL2_CGX + WIN_SEL2_SX * WIN_SEL2_SY)
//656+8*4=688

//「はい・いいえ」
#define WIN_YESNO_PX		(4)
#define WIN_YESNO_PY		(6)//(13)
#define WIN_YESNO_SX		(6)
#define WIN_YESNO_SY		(4)
#define WIN_YESNO_CGX		(WIN_OOKIDO_CGX + WIN_OOKIDO_SX * WIN_OOKIDO_SY)
//688+27*4=796

//「つぎをえらぶ」
#define WIN_IDSEL_PX		(1)
#define WIN_IDSEL_PY		(4)//(13)
#define WIN_IDSEL_SX		(10)
#define WIN_IDSEL_SY		(4)
#define WIN_IDSEL_CGX		(WIN_YESNO_CGX + WIN_YESNO_SX * WIN_YESNO_SY)
//796+6*4=820

//メニューウィンドウキャラ
#define OP_MENU_CGX_NUM		(1024-MENU_WIN_CGX_SIZ)

//会話ウィンドウキャラ
#define	OP_TALKWIN_CGX_SIZE	(TALK_WIN_CGX_SIZ	)
//#define	OP_TALKWIN_CGX_NUM	(512 - OP_TALKWIN_CGX_SIZE)
#define	OP_TALKWIN_CGX_NUM	(OP_MENU_CGX_NUM - OP_TALKWIN_CGX_SIZE)


//==============================================================================================
//
//	データ
//
//==============================================================================================
static const BMPWIN_DAT OpeningBmpData[] =
{
	
	{	// 0:「ぼうけん　とは？」
		OP_FRM_FONT, WIN_SEL1_PX, WIN_SEL1_PY,
		WIN_SEL1_SX, WIN_SEL1_SY, OP_FONT_PAL, WIN_SEL1_CGX
	},	
	{	// 1:操作、ゲーム説明
		OP_FRM_FONT, WIN_GUIDE_PX, WIN_GUIDE_PY,
		WIN_GUIDE_SX, WIN_GUIDE_SY, OP_FONT_PAL, WIN_GUIDE_CGX
	},
	{	// 2:「おとこのこ」
		OP_FRM_FONT, WIN_SEL2_PX, WIN_SEL2_PY,
		WIN_SEL2_SX, WIN_SEL2_SY, OP_FONT_PAL, WIN_SEL2_CGX
	},
	{	// 3:「オーキド会話」
		OP_FRM_FONT, WIN_OOKIDO_PX, WIN_OOKIDO_PY,
		WIN_OOKIDO_SX, WIN_OOKIDO_SY, OP_MSGFONT_PAL, WIN_OOKIDO_CGX
	},
	{	// 4:「はい・いいえ」
		OP_FRM_FONT, WIN_YESNO_PX, WIN_YESNO_PY,
		WIN_YESNO_SX, WIN_YESNO_SY, OP_FONT_PAL, WIN_YESNO_CGX
	},
	{	// 5:「つぎをえらぶ」
		OP_FRM_FONT, WIN_IDSEL_PX, WIN_IDSEL_PY,
		WIN_IDSEL_SX, WIN_IDSEL_SY, OP_FONT_PAL, WIN_IDSEL_CGX
	},
};


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void OpeningAddBmpWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );
void OpeningExitBmpWin( GF_BGL_BMPWIN* win );
void OpeningOffBmpWin( GF_BGL_BMPWIN* win );
u8 OpeningWriteMsg(OPENING_WORK* wk, GF_BGL_BMPWIN* win, int msg_id, u32 x, u32 y, u32 wait, u8 f_col, u8 s_col, u8 b_col, u8 font);
void OpeningWriteMenuWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win );
void OpeningInitMenu( OPENING_WORK* wk, GF_BGL_BMPWIN* win, u8 y_max );
void OpeningSetMenuData( OPENING_WORK* wk, u8 no, u8 param, int msg_id  );
void OpeningTalkWinPut( GF_BGL_BMPWIN * win, WINTYPE wintype );


//==============================================================================================
//
//	関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	ビットマップ追加
 *
 * @param	ini		BGLデータ
 * @param	win		ビットマップウィンドウ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningAddBmpWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	u8 i;
	const BMPWIN_DAT* dat =OpeningBmpData;

	//ビットマップ追加
	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( bgl, &win[i], &dat[i] );
		GF_BGL_BmpWinDataFill( &win[i], FBMP_COL_NULL );		//塗りつぶし
	}

	//先頭キャラをクリア(スクリーンクリアされてるところは、このキャラで埋まる)
	//GF_BGL_CharFill( bgl, OP_FRM_FONT, 0, 1, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	ビットマップウィンドウ破棄	
 *
 * @param	win		ビットマップウィンドウ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningExitBmpWin( GF_BGL_BMPWIN* win )
{
	u16	i;

	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &win[i] );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	ビットマップウィンドウオフ
 *
 * @param	win		ビットマップウィンドウ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningOffBmpWin( GF_BGL_BMPWIN* win )
{
	u16	i;

	for( i=0; i < OPENING_BMPWIN_MAX; i++ ){
		GF_BGL_BmpWinOff( &win[i] );
	}
	return;
}

//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @param	wk		OPENING_WORK型のポインタ
 * @param	win		ビットマップウィンドウ
 * @param	msg_id	メッセージID
 * @param	x		X座標(ドット単位)
 * @param	y		Y座標(ドット単位)
 * @param	wait	文字表示ウェイト
 * @param	f_col	文字色ナンバー(塗りつぶしカラーコード)
 * @param	s_col	影色ナンバー
 * @param	b_col	背景色ナンバー
 * @param	font	フォント種類
 *
 * @return	"文字描画ルーチンのインデックス"
 */
//--------------------------------------------------------------
u8 OpeningWriteMsg(OPENING_WORK* wk, GF_BGL_BMPWIN* win, int msg_id, u32 x, u32 y, u32 wait, u8 f_col, u8 s_col, u8 b_col, u8 font)
{
#if 0
	GF_BGL_BmpWinDataFill( win, b_col );			//塗りつぶし
	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf );
	//return GF_STR_PrintSimple( win, OP_FONT_KIND, wk->msg_buf, x, y, wait, NULL );
	return GF_STR_PrintColor( win, OP_FONT_KIND, wk->msg_buf, x, y, wait, 
								GF_PRINTCOLOR_MAKE(f_col,s_col,b_col), NULL );
#else
	GF_BGL_BmpWinDataFill( win, b_col );			//塗りつぶし
	MSGMAN_GetString( wk->msgman, msg_id, wk->tmp_buf );

	//登録された単語を使って文字列展開する
	WORDSET_ExpandStr( wk->wordset, wk->msg_buf, wk->tmp_buf );

	return GF_STR_PrintColor( win, font, wk->msg_buf, x, y, wait, 
								GF_PRINTCOLOR_MAKE(f_col,s_col,b_col), NULL );
#endif
}

//--------------------------------------------------------------
/**
 * @brief	メニューウィンドウ表示
 *
 * @param	ini		BGLデータ
 * @param	win		ビットマップウィンドウ
 *
 * @return	none
 */
//--------------------------------------------------------------
void OpeningWriteMenuWin( GF_BGL_INI* bgl, GF_BGL_BMPWIN* win )
{
	//メニューウィンドウのグラフィックをセット
	MenuWinGraphicSet( bgl, OP_FRM_FONT, OP_MENU_CGX_NUM, OP_MENU_PAL, 0, HEAPID_OPENING );

	//メニューウィンドウを描画
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, OP_MENU_CGX_NUM, OP_MENU_PAL );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	ヘッダー初期設定
 *
 * @param	wk		OPENING_WORK型のポインタ
 * @param	y_max	項目最大数
 *
 * @retval	none
 */
//--------------------------------------------------------------
void OpeningInitMenu( OPENING_WORK* wk, GF_BGL_BMPWIN* win, u8 y_max )
{
	int i;

	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		wk->Data[i].str	  = NULL;
		wk->Data[i].param = 0;
	}

	wk->MenuH.menu		= wk->Data;
	wk->MenuH.win		= win;
	wk->MenuH.font		= OP_FONT_KIND;
	wk->MenuH.x_max		= 1;
	wk->MenuH.y_max		= y_max;
	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;
	wk->MenuH.loop_f	= 0;			//無
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	データセット
 *
 * @param	wk		OPENING_WORK型のポインタ
 * @param	no		セットする場所(戻り値)
 * @param	param	戻り値
 * @param	msg_id	メッセージID
 *
 * @retval	none
 */
//--------------------------------------------------------------
void OpeningSetMenuData( OPENING_WORK* wk, u8 no, u8 param, int msg_id  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( no < OPENING_MENU_MAX, "メニュー項目数オーバー！" );

	MSGMAN_GetString( wk->msgman, msg_id, wk->menu_buf[no] );

	wk->Data[ no ].str = (const void *)wk->menu_buf[no];
	wk->Data[ no ].param = param;
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話ウィンドウ表示
 *
 * @param	win		BMPデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void OpeningTalkWinPut( GF_BGL_BMPWIN * win, WINTYPE wintype )
{
	TalkWinGraphicSet( win->ini, GF_BGL_BmpWinGet_Frame(win), OP_TALKWIN_CGX_NUM,
						OP_TALKWIN_PAL, wintype, HEAPID_OPENING );

	GF_BGL_BmpWinDataFill( win, 15 );
	BmpTalkWinWrite( win, WINDOW_TRANS_ON, OP_TALKWIN_CGX_NUM, OP_TALKWIN_PAL );
	return;
}






//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @param	wk		OPENING_WORK型のポインタ
 * @param	win		ビットマップウィンドウ
 * @param	msg_id	メッセージID
 * @param	x		X座標(ドット単位)
 * @param	y		Y座標(ドット単位)
 * @param	wait	文字表示ウェイト
 * @param	f_col	文字色ナンバー(塗りつぶしカラーコード)
 * @param	s_col	影色ナンバー
 * @param	b_col	背景色ナンバー
 *
 * @return	"文字描画ルーチンのインデックス"
 */
//--------------------------------------------------------------
#define OPENING_TEMP_BUF_SIZE	(100)

