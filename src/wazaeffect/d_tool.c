//==============================================================================
/**
 * @file	d_tool.h
 * @brief	戦闘用デバッグ画面
 * @author	goto
 * @date	2005.10.25(火)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "str_tool.h"
#include "wazaeffect/we_mana.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"


#include "system/bmp_list.h"
#include "ball_effect.h"
#include "battle_particle.h"

#include "d_tool.h"
#include "d_we.h"
#include "ball_effect.h"


//--------------------------------------------------------------
/**
 * @brief	ウィンドウの作成
 *
 * @param	bgl	
 * @param	win	
 * @param	frm	
 * @param	x	
 * @param	y	
 * @param	sx	
 * @param	sy	
 * @param	pal	
 * @param	ofs	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_WinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, u8 frm, u8 x, u8 y, u8 sx, u8 sy, u8 pal, u16 ofs)
{
	GF_BGL_BmpWinAdd(bgl, win, frm, x, y, sx, sy, pal, ofs);
}


//--------------------------------------------------------------
/**
 * @brief	メッセージ領域初期化
 *
 * @param	bgl	
 * @param	index
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_MsgClear(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win)
{
	GF_BGL_BmpWinDataFill(win, 0x11);
	GF_BGL_ScrClear(bgl, BATTLE_FRAME_EFFECT);
}


//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @param	bgl
 * @param	index	
 * @param	str	
 * @param	x
 * @param	y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DT_MsgPrint(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, STRBUF* str, u16 x, u16 y, int flag)
{	
	MSG_PRINT_HEADER	mph;
	STRBUF* strbuf = (STRBUF*)str;
	
	mph.msg			= (const u16*)strbuf;	///< 文字列
	mph.bmpwin		= win;					///< 描画ウィンドウ
	mph.msg_index	= 0;					///< メッセージインデックス(イマイチ謎
	mph.fnt_index	= FONT_SYSTEM;			///< フォント

	mph.start_x		= x;					///< ウインドウ内表示開始Ｘオフセット
	mph.start_y		= y;					///< ウインドウ内表示開始Ｙオフセット
	mph.write_x		= x;					///< ウインドウ内描画Ｘオフセット(初期値はstart_xと同じ)
	mph.write_y		= y;					///< ウインドウ内描画Ｙオフセット(初期値はstart_yと同じ)
	mph.space_x		= 0;					///< 文字間隔Ｘ
	mph.space_y		= 0;					///< 文字間隔Ｙ
	mph.style		= 0;					///< フォントスタイル
	if (flag == 1){
		mph.f_col	= 4;					///< 文字色ナンバー
		mph.b_col	= 1;					///< 背景色ナンバー
		mph.s_col	= 2;					///< 影色　ナンバー
	}
	else if (flag == 2){
		mph.f_col	= 6;					///< 文字色ナンバー
		mph.b_col	= 1;					///< 背景色ナンバー
		mph.s_col	= 1;					///< 影色　ナンバー
	}
	else {
		mph.f_col	= 3;					///< 文字色ナンバー
		mph.b_col	= 1;					///< 背景色ナンバー
		mph.s_col	= 1;					///< 影色　ナンバー
	}
	mph.dot_tbl		= 0;					///< 拡大用ドットテーブル
	mph.dot_wy		= 0;					///< 拡大時のY座標の描画補正値	

	GF_STR_Print( &mph, 0, NULL );
}

