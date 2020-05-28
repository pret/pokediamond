//============================================================================================
/**
 * @file	b_bag_bmp.c
 * @brief	戦闘用バッグ画面 BMP関連
 * @author	Hiroyuki Nakamura
 * @date	05.02.10
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/pmfprint.h"
#include "system/buflen.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_b_bag.h"
#include "itemtool/item.h"
#include "b_app_tool.h"


#define	B_BAG_BMP_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_bmp.h"
#include "b_bag_bmp_def.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	PCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// フォントカラー：黒
#define	PCOL_N_WHITE	( PCOL_N_BLACK )						// フォントカラー：白
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 7, 8, 0 ) )		// フォントカラー：青
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：赤

#define	PCOL_BTN		( GF_PRINTCOLOR_MAKE( 3, 2, 1 ) )		// ボタンフォント


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BBAG_Page1BmpWrite( BBAG_WORK * wk );
static void BBAG_Page2BmpWrite( BBAG_WORK * wk );
static void BBAG_Page3BmpWrite( BBAG_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// 会話ウィンドウデータ
static const BMPWIN_DAT CommBmpData = {
	WIN_TALK_FRM, WIN_TALK_PX, WIN_TALK_PY,
	WIN_TALK_SX, WIN_TALK_SY, WIN_TALK_PAL, WIN_TALK_CGX
};

// ページ１のウィンドウデータ
static const BMPWIN_DAT Page1_BmpData[] =
{
	{	// 「HP/PPかいふく」
		WIN_P1_HP_FRM, WIN_P1_HP_PX, WIN_P1_HP_PY,
		WIN_P1_HP_SX, WIN_P1_HP_SY, WIN_P1_HP_PAL, WIN_P1_HP_CGX
	},
	{	// 「じょうたいかいふく」
		WIN_P1_ZYOUTAI_FRM, WIN_P1_ZYOUTAI_PX, WIN_P1_ZYOUTAI_PY,
		WIN_P1_ZYOUTAI_SX, WIN_P1_ZYOUTAI_SY, WIN_P1_ZYOUTAI_PAL, WIN_P1_ZYOUTAI_CGX
	},
	{	// 「ボール」
		WIN_P1_BALL_FRM, WIN_P1_BALL_PX, WIN_P1_BALL_PY,
		WIN_P1_BALL_SX, WIN_P1_BALL_SY, WIN_P1_BALL_PAL, WIN_P1_BALL_CGX
	},
	{	// 「せんとうよう」
		WIN_P1_BATTLE_FRM, WIN_P1_BATTLE_PX, WIN_P1_BATTLE_PY,
		WIN_P1_BATTLE_SX, WIN_P1_BATTLE_SY, WIN_P1_BATTLE_PAL, WIN_P1_BATTLE_CGX
	},
	{	// 「さいごにつかったどうぐ」
		WIN_P1_LASTITEM_FRM, WIN_P1_LASTITEM_PX, WIN_P1_LASTITEM_PY,
		WIN_P1_LASTITEM_SX, WIN_P1_LASTITEM_SY, WIN_P1_LASTITEM_PAL, WIN_P1_LASTITEM_CGX
	}
};

// ページ２のウィンドウデータ
static const BMPWIN_DAT Page2_BmpData[] =
{
	{	// 道具名１
		WIN_P2_NAME1_FRM, WIN_P2_NAME1_PX, WIN_P2_NAME1_PY,
		WIN_P2_NAME1_SX, WIN_P2_NAME1_SY, WIN_P2_NAME1_PAL, WIN_P2_NAME1_CGX
	},
	{	// 道具数１
		WIN_P2_NUM1_FRM, WIN_P2_NUM1_PX, WIN_P2_NUM1_PY,
		WIN_P2_NUM1_SX, WIN_P2_NUM1_SY, WIN_P2_NUM1_PAL, WIN_P2_NUM1_CGX
	},
	{	// 道具名２
		WIN_P2_NAME2_FRM, WIN_P2_NAME2_PX, WIN_P2_NAME2_PY,
		WIN_P2_NAME2_SX, WIN_P2_NAME2_SY, WIN_P2_NAME2_PAL, WIN_P2_NAME2_CGX
	},
	{	// 道具数２
		WIN_P2_NUM2_FRM, WIN_P2_NUM2_PX, WIN_P2_NUM2_PY,
		WIN_P2_NUM2_SX, WIN_P2_NUM2_SY, WIN_P2_NUM2_PAL, WIN_P2_NUM2_CGX
	},
	{	// 道具名３
		WIN_P2_NAME3_FRM, WIN_P2_NAME3_PX, WIN_P2_NAME3_PY,
		WIN_P2_NAME3_SX, WIN_P2_NAME3_SY, WIN_P2_NAME3_PAL, WIN_P2_NAME3_CGX
	},
	{	// 道具数３
		WIN_P2_NUM3_FRM, WIN_P2_NUM3_PX, WIN_P2_NUM3_PY,
		WIN_P2_NUM3_SX, WIN_P2_NUM3_SY, WIN_P2_NUM3_PAL, WIN_P2_NUM3_CGX
	},
	{	// 道具名４
		WIN_P2_NAME4_FRM, WIN_P2_NAME4_PX, WIN_P2_NAME4_PY,
		WIN_P2_NAME4_SX, WIN_P2_NAME4_SY, WIN_P2_NAME4_PAL, WIN_P2_NAME4_CGX
	},
	{	// 道具数４
		WIN_P2_NUM4_FRM, WIN_P2_NUM4_PX, WIN_P2_NUM4_PY,
		WIN_P2_NUM4_SX, WIN_P2_NUM4_SY, WIN_P2_NUM4_PAL, WIN_P2_NUM4_CGX
	},
	{	// 道具名５
		WIN_P2_NAME5_FRM, WIN_P2_NAME5_PX, WIN_P2_NAME5_PY,
		WIN_P2_NAME5_SX, WIN_P2_NAME5_SY, WIN_P2_NAME5_PAL, WIN_P2_NAME5_CGX
	},
	{	// 道具数５
		WIN_P2_NUM5_FRM, WIN_P2_NUM5_PX, WIN_P2_NUM5_PY,
		WIN_P2_NUM5_SX, WIN_P2_NUM5_SY, WIN_P2_NUM5_PAL, WIN_P2_NUM5_CGX
	},
	{	// 道具名６
		WIN_P2_NAME6_FRM, WIN_P2_NAME6_PX, WIN_P2_NAME6_PY,
		WIN_P2_NAME6_SX, WIN_P2_NAME6_SY, WIN_P2_NAME6_PAL, WIN_P2_NAME6_CGX
	},
	{	// 道具数６
		WIN_P2_NUM6_FRM, WIN_P2_NUM6_PX, WIN_P2_NUM6_PY,
		WIN_P2_NUM6_SX, WIN_P2_NUM6_SY, WIN_P2_NUM6_PAL, WIN_P2_NUM6_CGX
	},
	{	// 道具名１（スワップ用）
		WIN_P2_NAME1_FRM, WIN_P2_NAME1_PX, WIN_P2_NAME1_PY,
		WIN_P2_NAME1_SX, WIN_P2_NAME1_SY, WIN_P2_NAME1_PAL, WIN_P2_NAME1_S_CGX
	},
	{	// 道具数１（スワップ用）
		WIN_P2_NUM1_FRM, WIN_P2_NUM1_PX, WIN_P2_NUM1_PY,
		WIN_P2_NUM1_SX, WIN_P2_NUM1_SY, WIN_P2_NUM1_PAL, WIN_P2_NUM1_S_CGX
	},
	{	// 道具名２（スワップ用）
		WIN_P2_NAME2_FRM, WIN_P2_NAME2_PX, WIN_P2_NAME2_PY,
		WIN_P2_NAME2_SX, WIN_P2_NAME2_SY, WIN_P2_NAME2_PAL, WIN_P2_NAME2_S_CGX
	},
	{	// 道具数２（スワップ用）
		WIN_P2_NUM2_FRM, WIN_P2_NUM2_PX, WIN_P2_NUM2_PY,
		WIN_P2_NUM2_SX, WIN_P2_NUM2_SY, WIN_P2_NUM2_PAL, WIN_P2_NUM2_S_CGX
	},
	{	// 道具名３（スワップ用）
		WIN_P2_NAME3_FRM, WIN_P2_NAME3_PX, WIN_P2_NAME3_PY,
		WIN_P2_NAME3_SX, WIN_P2_NAME3_SY, WIN_P2_NAME3_PAL, WIN_P2_NAME3_S_CGX
	},
	{	// 道具数３（スワップ用）
		WIN_P2_NUM3_FRM, WIN_P2_NUM3_PX, WIN_P2_NUM3_PY,
		WIN_P2_NUM3_SX, WIN_P2_NUM3_SY, WIN_P2_NUM3_PAL, WIN_P2_NUM3_S_CGX
	},
	{	// 道具名４（スワップ用）
		WIN_P2_NAME4_FRM, WIN_P2_NAME4_PX, WIN_P2_NAME4_PY,
		WIN_P2_NAME4_SX, WIN_P2_NAME4_SY, WIN_P2_NAME4_PAL, WIN_P2_NAME4_S_CGX
	},
	{	// 道具数４（スワップ用）
		WIN_P2_NUM4_FRM, WIN_P2_NUM4_PX, WIN_P2_NUM4_PY,
		WIN_P2_NUM4_SX, WIN_P2_NUM4_SY, WIN_P2_NUM4_PAL, WIN_P2_NUM4_S_CGX
	},
	{	// 道具名５（スワップ用）
		WIN_P2_NAME5_FRM, WIN_P2_NAME5_PX, WIN_P2_NAME5_PY,
		WIN_P2_NAME5_SX, WIN_P2_NAME5_SY, WIN_P2_NAME5_PAL, WIN_P2_NAME5_S_CGX
	},
	{	// 道具数５（スワップ用）
		WIN_P2_NUM5_FRM, WIN_P2_NUM5_PX, WIN_P2_NUM5_PY,
		WIN_P2_NUM5_SX, WIN_P2_NUM5_SY, WIN_P2_NUM5_PAL, WIN_P2_NUM5_S_CGX
	},
	{	// 道具名６（スワップ用）
		WIN_P2_NAME6_FRM, WIN_P2_NAME6_PX, WIN_P2_NAME6_PY,
		WIN_P2_NAME6_SX, WIN_P2_NAME6_SY, WIN_P2_NAME6_PAL, WIN_P2_NAME6_S_CGX
	},
	{	// 道具数６（スワップ用）
		WIN_P2_NUM6_FRM, WIN_P2_NUM6_PX, WIN_P2_NUM6_PY,
		WIN_P2_NUM6_SX, WIN_P2_NUM6_SY, WIN_P2_NUM6_PAL, WIN_P2_NUM6_S_CGX
	},
	{	// ポケット名
		WIN_P2_POCKET_FRM, WIN_P2_POCKET_PX, WIN_P2_POCKET_PY,
		WIN_P2_POCKET_SX, WIN_P2_POCKET_SY, WIN_P2_POCKET_PAL, WIN_P2_POCKET_CGX
	},
	{	// ページ数（アイテム数）
		WIN_P2_PAGENUM_FRM, WIN_P2_PAGENUM_PX, WIN_P2_PAGENUM_PY,
		WIN_P2_PAGENUM_SX, WIN_P2_PAGENUM_SY, WIN_P2_PAGENUM_PAL, WIN_P2_PAGENUM_CGX
	}
};

// ページ３のウィンドウデータ
static const BMPWIN_DAT Page3_BmpData[] =
{
	{	// 道具名
		WIN_P3_NAME_FRM, WIN_P3_NAME_PX, WIN_P3_NAME_PY,
		WIN_P3_NAME_SX, WIN_P3_NAME_SY, WIN_P3_NAME_PAL, WIN_P3_NAME_CGX
	},
	{	// 個数
		WIN_P3_NUM_FRM, WIN_P3_NUM_PX, WIN_P3_NUM_PY,
		WIN_P3_NUM_SX, WIN_P3_NUM_SY, WIN_P3_NUM_PAL, WIN_P3_NUM_CGX
	},
	{	// 説明
		WIN_P3_INFO_FRM, WIN_P3_INFO_PX, WIN_P3_INFO_PY,
		WIN_P3_INFO_SX, WIN_P3_INFO_SY, WIN_P3_INFO_PAL, WIN_P3_INFO_CGX
	},
	{	// 「つかう」
		WIN_P3_USE_FRM, WIN_P3_USE_PX, WIN_P3_USE_PY,
		WIN_P3_USE_SX, WIN_P3_USE_SY, WIN_P3_USE_PAL, WIN_P3_USE_CGX
	}
};



//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_BmpInit( BBAG_WORK * wk )
{
//	OS_Printf( "BBAG2 : %d\n", WIN_P2_POCKET_CGX+WIN_P2_POCKET_SX*WIN_P2_POCKET_SY );
//	OS_Printf( "BBAG3 : %d\n", WIN_P3_USE_CGX+WIN_P3_USE_SX*WIN_P3_USE_SY );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->talk_win, &CommBmpData );
	BattleBag_BmpAdd( wk, wk->page );
}

//--------------------------------------------------------------------------------------------
/**
 * ページごとのBMPウィンドウ追加
 *
 * @param	wk		ワーク
 * @param	page	ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_BmpAdd( BBAG_WORK * wk, u32 page )
{
	const BMPWIN_DAT * dat;
	u8	i;

	switch( page ){
	case BBAG_PAGE_POCKET:	// ポケット選択ページ
		dat = Page1_BmpData;
		wk->bmp_add_max = WIN_P1_MAX;
		break;
	case BBAG_PAGE_MAIN:	// アイテム選択ページ
		dat = Page2_BmpData;
		wk->bmp_add_max = WIN_P2_MAX;
		break;
	case BBAG_PAGE_ITEM:	// アイテム使用ページ
		dat = Page3_BmpData;
		wk->bmp_add_max = WIN_P3_MAX;
		break;
	}

	wk->add_win = GF_BGL_BmpWinAllocGet( wk->dat->heap, wk->bmp_add_max );
	for( i=0; i<wk->bmp_add_max; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->add_win[i], &dat[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 追加BMPウィンドウ削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_BmpFree( BBAG_WORK * wk )
{
	GF_BGL_BmpWinFree( wk->add_win, wk->bmp_add_max );
}

//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ全削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_BmpFreeAll( BBAG_WORK * wk )
{
	u32	i;

	GF_BGL_BmpWinFree( wk->add_win, wk->bmp_add_max );
	GF_BGL_BmpWinDel( &wk->talk_win );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP書き込み
 *
 * @param	wk		ワーク
 * @param	page	ページ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_BmpWrite( BBAG_WORK * wk, u32 page )
{
	switch( page ){
	case BBAG_PAGE_POCKET:	// ポケット選択ページ
		BBAG_Page1BmpWrite( wk );
		break;
	case BBAG_PAGE_MAIN:	// アイテム選択ページ
		BBAG_Page2BmpWrite( wk );
		break;
	case BBAG_PAGE_ITEM:	// アイテム使用ページ
		BBAG_Page3BmpWrite( wk );
		break;
	}
}



static void BBAG_StrPut( BBAG_WORK * wk, u32 widx, u32 midx, u32 fidx, u32 py, u32 col )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;
	u32	px;

	win = &wk->add_win[widx];
	str = MSGMAN_AllocString( wk->mman, midx );
	siz = FontProc_GetPrintStrWidth( fidx, str, 0 );
	px = ( GF_BGL_BmpWinGet_SizeX(win) * 8 - siz ) / 2;
	GF_STR_PrintColor( win, fidx, str, px, py, MSG_NO_PUT, col, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

#define	P1_KAIFUKU1_PY	( 24 )
#define	P1_ZYOUTAI_PY	( 8 )
#define	P1_KAIFUKU2_PY	( 24 )
#define	P1_HP_PY		( 8 )
#define	P1_KAIFUKU3_PY	( 24 )
#define	P1_BATTLE_PY	( 8 )
#define	P1_BALL_PY		( 8 )
#define	P1_LASTITEM_PY	( 6 )

// ポケット選択ページ
static void BBAG_Page1BmpWrite( BBAG_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_P1_MAX; i++ ){
		GF_BGL_BmpWinDataFill( &wk->add_win[i], 0 );
	}

	BBAG_StrPut( wk, WIN_P1_HP, mes_b_bag_01_000, FONT_BUTTON, P1_HP_PY, PCOL_BTN );
	BBAG_StrPut( wk, WIN_P1_HP, mes_b_bag_01_001, FONT_BUTTON, P1_KAIFUKU3_PY, PCOL_BTN );
	BBAG_StrPut( wk, WIN_P1_ZYOUTAI, mes_b_bag_01_100, FONT_BUTTON, P1_ZYOUTAI_PY, PCOL_BTN );
	BBAG_StrPut( wk, WIN_P1_ZYOUTAI, mes_b_bag_01_101, FONT_BUTTON, P1_KAIFUKU2_PY, PCOL_BTN );
	BBAG_StrPut( wk, WIN_P1_BALL, mes_b_bag_01_500, FONT_BUTTON, P1_BALL_PY, PCOL_BTN );
	BBAG_StrPut( wk, WIN_P1_BATTLE, mes_b_bag_01_400, FONT_BUTTON, P1_BATTLE_PY, PCOL_BTN );
	if( wk->dat->used_item != 0 ){
		STRBUF * str = MSGMAN_AllocString( wk->mman, mes_b_bag_01_600 );
//		BBAG_StrPut(
//			wk, WIN_P1_LASTITEM, mes_b_bag_01_600, FONT_BUTTON, P1_LASTITEM_PY, PCOL_BTN );
		GF_STR_PrintColor(
			&wk->add_win[WIN_P1_LASTITEM], FONT_BUTTON,
			str, 0, P1_LASTITEM_PY, MSG_NO_PUT, PCOL_BTN, NULL );
		STRBUF_Delete( str );
		GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P1_LASTITEM] );
	}
}



static const u32 ItemStrGmm[][2] =
{	// 名前、x???
	{ mes_b_bag_02_000, mes_b_bag_02_001 },
	{ mes_b_bag_02_100, mes_b_bag_02_101 },
	{ mes_b_bag_02_200, mes_b_bag_02_201 },
	{ mes_b_bag_02_300, mes_b_bag_02_301 },
	{ mes_b_bag_02_400, mes_b_bag_02_401 },
	{ mes_b_bag_02_500, mes_b_bag_02_501 }
};

#define	P2_ITEMNAME_PY	( 8 )

static void BBAG_ItemNamePut(
				BBAG_WORK * wk, u32 dat_pos, u32 put_pos, u32 widx, u32 fidx, u32 col )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;
	u32	px;

	win = &wk->add_win[widx];
	GF_BGL_BmpWinDataFill( win, 0 );

	if( wk->pocket[wk->poke_id][dat_pos].id != 0 ){
		str = MSGMAN_AllocString( wk->mman, ItemStrGmm[put_pos][0] );
		WORDSET_RegisterItemName( wk->wset, 0, wk->pocket[wk->poke_id][dat_pos].id );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );

		siz = FontProc_GetPrintStrWidth( fidx, wk->msg_buf, 0 );
		px  = ( GF_BGL_BmpWinGet_SizeX(win) * 8 - siz ) / 2;

		GF_STR_PrintColor( win, fidx, wk->msg_buf, px, P2_ITEMNAME_PY, MSG_NO_PUT, col, NULL );
		STRBUF_Delete( str );
	}

	GF_BGL_BmpWinOnVReq( win );
}

static void BBAG_ItemNumPut(
				BBAG_WORK * wk, u32 dat_pos, u32 put_pos, u32 widx, u32 fidx, u32 py, u32 col )
{
	STRBUF * str;
	GF_BGL_BMPWIN * win;

	win = &wk->add_win[widx];
	GF_BGL_BmpWinDataFill( win, 0 );

	if( wk->pocket[wk->poke_id][dat_pos].no != 0 ){
		str = MSGMAN_AllocString( wk->mman, ItemStrGmm[put_pos][1] );

		WORDSET_RegisterNumber(
			wk->wset, 0, wk->pocket[wk->poke_id][dat_pos].no,
			3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );

		GF_STR_PrintColor( win, fidx, wk->msg_buf, 0, py, MSG_NO_PUT, col, NULL );
		STRBUF_Delete( str );
	}

	GF_BGL_BmpWinOnVReq( win );
}

#define	P2_ITEMNUM_PY	( 4 )

static void BBAG_P2_ItemPut( BBAG_WORK * wk, u32 pos )
{
	u32	win_pos;
	u32	dat_pos;

	dat_pos = wk->dat->item_scr[wk->poke_id]*6+pos;

	if( wk->p2_swap == 0 ){
		win_pos = WIN_P2_NAME1;
	}else{
		win_pos = WIN_P2_NAME1_S;
	}

	BBAG_ItemNamePut( wk, dat_pos, pos, win_pos+pos*2, FONT_BUTTON, PCOL_BTN );
	BBAG_ItemNumPut(
		wk, dat_pos, pos, win_pos+1+pos*2, FONT_SYSTEM, P2_ITEMNUM_PY, PCOL_N_BLACK );
}

void BattleBag_Page2_StrItemPut( BBAG_WORK * wk )
{
	u16	i;

	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, 32, 19, GF_BGL_SCRWRT_PALIN );

	for( i=0; i<6; i++ ){
		BBAG_P2_ItemPut( wk, i );
	}

	wk->p2_swap ^= 1;
}


#define	P2_PAGE_NUM_PY	( 4 )

void BattleBag_Page2_StrPageNumPut( BBAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;
	u32	px;

	GF_BGL_BmpWinDataFill( &wk->add_win[WIN_P2_PAGENUM], 0 );

	win = &wk->add_win[WIN_P2_PAGENUM];

	str = MSGMAN_AllocString( wk->mman, mes_b_bag_02_800 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px  = ( GF_BGL_BmpWinGet_SizeX(win) * 8 - siz ) / 2;
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, px, P2_PAGE_NUM_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	str = MSGMAN_AllocString( wk->mman, mes_b_bag_02_801 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->scr_max[wk->poke_id]+1,
		2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, px+siz, P2_PAGE_NUM_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	str = MSGMAN_AllocString( wk->mman, mes_b_bag_02_802 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->dat->item_scr[wk->poke_id]+1,
		2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, px-siz, P2_PAGE_NUM_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}


#define	P2_NEXT_PY		( 8 )
#define	P2_POCKET_HP1_PY	( 4 )
#define	P2_POCKET_HP2_PY	( P2_POCKET_HP1_PY+16 )
#define	P2_POCKET_ST1_PY	( 4 )
#define	P2_POCKET_ST2_PY	( P2_POCKET_ST1_PY+16 )
#define	P2_POCKET_BALL_PY	( 12 )
#define	P2_POCKET_BATL_PY	( 12 )

static void BBAG_Page2PocketNamePut( BBAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[WIN_P2_POCKET], 0 );

	switch( wk->poke_id ){
	case BBAG_POKE_HPRCV:	// HP回復ポケット
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_700, FONT_SYSTEM, P2_POCKET_HP1_PY, PCOL_N_WHITE );
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_701, FONT_SYSTEM, P2_POCKET_HP2_PY, PCOL_N_WHITE );
		break;
	case BBAG_POKE_STRCV:	// 状態回復ポケット
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_702, FONT_SYSTEM, P2_POCKET_ST1_PY, PCOL_N_WHITE );
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_703, FONT_SYSTEM, P2_POCKET_ST2_PY, PCOL_N_WHITE );
		break;
	case BBAG_POKE_BALL:	// ボールポケット
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_704, FONT_SYSTEM, P2_POCKET_BALL_PY, PCOL_N_WHITE );
		break;
	case BBAG_POKE_BATTLE:	// 戦闘用ポケット
		BBAG_StrPut(
			wk, WIN_P2_POCKET, mes_b_bag_02_705, FONT_SYSTEM, P2_POCKET_BATL_PY, PCOL_N_WHITE );
		break;
	}
}

// アイテム選択ページ
static void BBAG_Page2BmpWrite( BBAG_WORK * wk )
{
	BattleBag_Page2_StrItemPut( wk );
	BBAG_Page2PocketNamePut( wk );
	BattleBag_Page2_StrPageNumPut( wk );
}

#define	P3_ITEMNAME_PY	( 0 )
#define	P3_ITEMINFO_PX	( 4 )
#define	P3_ITEMINFO_PY	( 0 )
#define	P3_ITEMNUM_PY	( 0 )

static void BBAG_P3_ItemNamePut( BBAG_WORK * wk, u32 dat_pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->add_win[WIN_P3_NAME];
	str = MSGMAN_AllocString( wk->mman, ItemStrGmm[0][0] );
	WORDSET_RegisterItemName( wk->wset, 0, wk->pocket[wk->poke_id][dat_pos].id );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );

	GF_BGL_BmpWinDataFill( win, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, 0, P3_ITEMNAME_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

static void BBAG_P3_ItemInfoPut( BBAG_WORK * wk, u32 dat_pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * buf;
	
	win = &wk->add_win[WIN_P3_INFO];
	buf = STRBUF_Create( BUFLEN_ITEM_INFO, wk->dat->heap );
	ItemInfoGet( buf, wk->pocket[wk->poke_id][dat_pos].id, wk->dat->heap );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf, P3_ITEMINFO_PX, P3_ITEMINFO_PY, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( buf );

	GF_BGL_BmpWinOnVReq( win );
}

#define	P3_USE_PY	( 6 )

// アイテム使用ページ
static void BBAG_Page3BmpWrite( BBAG_WORK * wk )
{
	u32	i;
	u32	dat_pos;

	for( i=0; i<WIN_P3_MAX; i++ ){
		GF_BGL_BmpWinDataFill( &wk->add_win[i], 0 );
	}

	dat_pos = wk->dat->item_scr[wk->poke_id]*6+wk->dat->item_pos[wk->poke_id];

	BBAG_P3_ItemNamePut( wk, dat_pos );
	BBAG_ItemNumPut( wk, dat_pos, 0, WIN_P3_NUM, FONT_SYSTEM, P3_ITEMNUM_PY, PCOL_N_BLACK );
	BBAG_P3_ItemInfoPut( wk, dat_pos );
	BBAG_StrPut( wk, WIN_P3_USE, mes_b_bag_03_000, FONT_BUTTON, P3_USE_PY, PCOL_BTN );
}

//--------------------------------------------------------------------------------------------
/**
 * メッセージ表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_TalkMsgSet( BBAG_WORK * wk )
{
	BmpTalkWinWrite( &wk->talk_win, WINDOW_TRANS_OFF, TALK_WIN_CGX_POS, BBAG_PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( &wk->talk_win, FBMP_COL_WHITE );
	BattleBag_TalkMsgStart( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * メッセージ表示開始
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_TalkMsgStart( BBAG_WORK * wk )
{
	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	wk->midx = GF_STR_PrintSimple(
				&wk->talk_win, FONT_TALK, wk->msg_buf,
				0, 0, BattleWorkConfigMsgSpeedGet(wk->dat->bw), NULL );
}



void BattleBag_ItemUseMsgSet( BBAG_WORK * wk )
{
	POKEMON_PARAM * pp;
	void * item;
	STRBUF * str;
	int	smn;
	
	item = GetItemArcData( wk->dat->ret_item, ITEM_GET_DATA, wk->dat->heap );
	smn  = BattleBag_SelMonsNoGet( wk );
	pp   = BattleWorkPokemonParamGet( wk->dat->bw, wk->dat->client_no, smn );

	// 能力ガード
	if( ItemBufParamGet( item, ITEM_PRM_ABILITY_GUARD ) != 0 ){
		MSGMAN_GetString( wk->mman, mes_b_bag_m02, wk->msg_buf );
	// 攻撃力アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_ATTACK_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m04 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 防御力アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_DEFENCE_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m08 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 特攻アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_SP_ATTACK_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m05 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 特防アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_SP_DEFENCE_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m07 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 素早さアップ
	}else if( ItemBufParamGet( item, ITEM_PRM_AGILITY_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m06 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 命中率アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_HIT_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m09 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// クリティカル率アップ
	}else if( ItemBufParamGet( item, ITEM_PRM_CRITICAL_UP ) != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m03 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}else{
		str = MSGMAN_AllocString( wk->mman, mes_b_bag_m10 );
		WORDSET_RegisterItemName( wk->wset, 0, wk->dat->ret_item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}

	sys_FreeMemoryEz( item );
}
