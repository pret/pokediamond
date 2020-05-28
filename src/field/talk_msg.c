//============================================================================================
/**
 * @file	talk_msg.c
 * @brief	メッセージ表示処理
 * @author	Hiroyuki Nakamura
 * @date	2004.10.28
 */
//============================================================================================
#define TALK_MSG_H_GLOBAL

#include "common.h"
#include "fntsys.h"

#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/arc_util.h"
#include "fld_bmp.h"
#include "system/lib_pack.h"
#include "system/pmfprint.h"
#include "system/window.h"

#include "talk_msg.h"
#include "fieldmap.h"
#include "system/palanm.h"


//============================================================================================
//	シンボル定義
//============================================================================================


//============================================================================================
//	プロトタイプ宣言
//============================================================================================


//============================================================================================
//	グローバル変数
//============================================================================================




//--------------------------------------------------------------------------------------------
/**
 * メッセージ表示システム初期化
 *
 * @param	type	パレット転送タイプ
 * @param	init	メッセージプリント初期化フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMsgPrintInit( u32 type, u32 init )
{
	if( init == MSG_PRINT_INIT_ON ){
		MSG_PrintInit();
	}
	SystemFontPaletteLoad( type, FLD_MENU_WIN_PAL * 32, HEAPID_FIELD );
	TalkFontPaletteLoad( type, FLD_MSG_WIN_PAL * 32, HEAPID_FIELD );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話用BMP取得
 *
 * @param	ini		BGLデータ
 * @param	win		BMPデータ格納場所
 * @param	frmnum	BGフレーム
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldTalkBmpAdd( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u32 frmnum )
{
	if( frmnum == FLD_MBGFRM_FONT ){
		GF_BGL_BmpWinAdd(
			ini, win, FLD_MBGFRM_FONT, FLD_MSG_WIN_PX, FLD_MSG_WIN_PY,
			FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, FLD_MSG_WIN_PAL, FLD_MSG_WIN_CGX );
	}else{
		GF_BGL_BmpWinAdd(
			ini, win, FLD_SBGFRM_FONT, FLD_MSG_WIN_S_PX, FLD_MSG_WIN_S_PY,
			FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, FLD_MSG_WIN_S_PAL, FLD_MSG_WIN_S_CGX );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話ウィンドウ表示
 *
 * @param	win		BMPデータ
 * @param	cfg		コンフィグデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldTalkWinPut( GF_BGL_BMPWIN * win, const CONFIG * cfg )
{
	TalkWinGraphicSet(
		win->ini, GF_BGL_BmpWinGet_Frame( win ),
		TALK_WIN_CGX_NUM, TALK_WIN_PAL, CONFIG_GetWindowType(cfg), HEAPID_FIELD );

	FieldTalkWinClear( win );

	BmpTalkWinWrite( win, WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALK_WIN_PAL );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話ウィンドウ領域クリア
 *
 * @param   win		
 *
 */
//--------------------------------------------------------------------------------------------
void FieldTalkWinClear( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinDataFill( win, 15 );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話スタート
 *
 * @param	win		BMPデータ
 * @param	msg		メッセージ
 * @param	cfg		コンフィグデータ
 * @param	skip	スキップ許可フラグ
 *
 * @return	メッセージインデックス
 */
//--------------------------------------------------------------------------------------------
u8 FieldTalkMsgStart( GF_BGL_BMPWIN * win, STRBUF * msg, const CONFIG * cfg, u8 skip )
{
	u8	idx;

	MsgPrintSkipFlagSet( skip );
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );
	MsgPrintTouchPanelFlagSet( MSG_TP_OFF );
	idx = GF_STR_PrintSimple( win, FONT_TALK, msg, 0, 0, CONFIG_GetMsgPrintSpeed(cfg), NULL );

	return idx;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話スタート(ちょっと拡張版)
 *
 * @param	win		BMPデータ
 * @param	msg		メッセージ
 * @param	skip	スキップ許可フラグ
 *
 * @return	メッセージインデックス
 */
//--------------------------------------------------------------------------------------------
u8 FieldTalkMsgStartEx( GF_BGL_BMPWIN * win, STRBUF * msg, int font, int msg_speed, u8 skip, int auto_flag )
{
	MsgPrintSkipFlagSet( skip );
	MsgPrintAutoFlagSet( auto_flag );
	MsgPrintTouchPanelFlagSet( MSG_TP_OFF );
	return GF_STR_PrintSimple( win, font, msg, 0, 0, msg_speed, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド会話終了待ち
 *
 * @param	msg_index	メッセージインデックス
 *
 * @retval	"0 = 会話中"
 * @retval	"1 = 終了"
 */
//--------------------------------------------------------------------------------------------
u8 FldTalkMsgEndCheck( u8 msg_index )
{
	if( GF_MSG_PrintEndCheck( msg_index ) == 0 ){
		return 1;
	}
	return 0;
}




//--------------------------------------------------------------------------------------------
/**
 * フィールド看板用用BMP取得
 *
 * @param	ini		BGLデータ
 * @param	win		BMPデータ格納場所
 * @param	type	看板タイプ
 * @param	frmnum	BGフレーム
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldBoardBmpAdd( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, u16 type, u16 frmnum )
{
	u16	px, sx;

	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		px = FLD_BOARD_WIN_PX;
		sx = FLD_BOARD_WIN_SX;
	}else{
		px = FLD_MSG_WIN_PX;
		sx = FLD_MSG_WIN_SX;
	}

	if( frmnum == FLD_MBGFRM_FONT ){
		GF_BGL_BmpWinAdd(
			ini, win, FLD_MBGFRM_FONT, px, FLD_BOARD_WIN_PY,
			sx, FLD_BOARD_WIN_SY, FLD_BOARD_WIN_PAL, FLD_BOARD_WIN_CGX );
	}else{
		GF_BGL_BmpWinAdd(
			ini, win, FLD_SBGFRM_FONT, px, FLD_BOARD_WIN_S_PY,
			sx, FLD_BOARD_WIN_S_SY, FLD_BOARD_WIN_S_PAL, FLD_BOARD_WIN_S_CGX );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド看板ウィンドウ表示
 *
 * @param	win		BMPデータ
 * @param	type	看板タイプ
 * @param	map		マップ番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldBoardWinPut( GF_BGL_BMPWIN * win, u16 type, u16 map )
{
	BoardWinGraphicSet(
		win->ini, GF_BGL_BmpWinGet_Frame( win ),
		BOARD_WIN_CGX_NUM, BOARD_WIN_PAL, type, map, HEAPID_FIELD );

	GF_BGL_BmpWinDataFill( win, 15 );
	BmpBoardWinWrite( win, WINDOW_TRANS_ON, BOARD_WIN_CGX_NUM, BOARD_WIN_PAL, type );
}
