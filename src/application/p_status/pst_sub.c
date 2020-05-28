//============================================================================================
/**
 * @file	pst_sub.c
 * @brief	ポケモンステータス画面　下画面のボタン処理
 * @author	Hiroyuki Nakamura
 * @date	2006.03.03
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/procsys.h"
#include "system/clact_tool.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "poketool/pokeparty.h"
/*
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/window.h"
#include "system/bmp_menu.h"
#include "system/buflen.h"
#include "battle/battle_common.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/waza_tool.h"
#include "application/app_tool.h"
#include "battle/wazatype_icon.h"
*/

#define	PST_SUB_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
/*
#include "application/pst_gra.naix"
*/
#include "pst_sub.h"
#include "pst_snd_def.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	PST_SUB_OFF		( 0x0f )	// 下ボタン表示なし


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void SubPokeButtonBgInit( PST_WORK * wk );
static int SubPokeButtonCheck( PST_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
typedef struct {
	u8	page;		// ページID
	u8	pal;		// パレット
	u8	px;			// 表示座標X
	u8	py;			// 表示座標Y
}PST_SUB_BUTTON;

static const PST_SUB_BUTTON SubButtonType1[] =
{
	{ PST_PAGE_INFO, 1, 1, 4 },
	{ PST_PAGE_MEMO, 1, 2, 10 },
	{ PST_PAGE_PARAM, 2, 5, 15 },
	{ PST_PAGE_B_SKILL, 3, 10, 18 },
	{ PST_PAGE_CONDITION, 2, 17, 18 },
	{ PST_PAGE_C_SKILL, 3, 22, 15 },
	{ PST_PAGE_RIBBON, 4, 25, 10 },
	{ PST_PAGE_RET, 4, 26, 4 },
	{ 0xff, 0xff, 0xff, 0xff }
};

static const PST_SUB_BUTTON SubButtonType2[] =
{
/*
	{ PST_PAGE_INFO, 1, 5, 15 },
	{ PST_PAGE_MEMO, 1, 10, 18 },
	{ PST_PAGE_PARAM, 2, 17, 18 },
	{ PST_PAGE_B_SKILL, 3, 22, 15 },
	{ PST_PAGE_RET, 4, 25, 10 },
*/
	{ PST_PAGE_INFO, 1, 2, 9 },
	{ PST_PAGE_MEMO, 1, 6, 15 },
	{ PST_PAGE_PARAM, 2, 14, 18 },
	{ PST_PAGE_B_SKILL, 3, 22, 15 },
	{ PST_PAGE_RET, 4, 26, 9 },
	{ 0xff, 0xff, 0xff, 0xff }
};

static const PST_SUB_BUTTON SubButtonType3[] =
{
	{ PST_PAGE_B_SKILL, 3, 10, 18 },
	{ PST_PAGE_C_SKILL, 3, 17, 18 },
	{ 0xff, 0xff, 0xff, 0xff }
};

static const PST_SUB_BUTTON * SubButtonTypeTbl[] = {
	SubButtonType1,
	SubButtonType2,
	SubButtonType3
};


static const RECT_HIT_TBL SubButtonRect1[] =
{
	{ 4*8,	9*8-1,	1*8,  6*8-1 },
	{ 10*8,	15*8-1,	2*8,  7*8-1 },
	{ 15*8,	20*8-1,	5*8,  10*8-1 },
	{ 18*8,	23*8-1,	10*8, 15*8-1 },
	{ 18*8,	23*8-1,	17*8, 22*8-1 },
	{ 15*8,	20*8-1, 22*8, 27*8-1 },
	{ 10*8,	15*8-1, 25*8, 30*8-1 },
	{ 4*8,	9*8-1,	26*8, 31*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL SubButtonRect2[] =
{
/*
	{ 15*8,	20*8-1,	5*8,  10*8-1 },
	{ 18*8,	23*8-1,	10*8, 15*8-1 },
	{ 18*8,	23*8-1,	17*8, 22*8-1 },
	{ 15*8,	20*8-1, 22*8, 27*8-1 },
	{ 10*8,	15*8-1, 25*8, 30*8-1 },
*/
	{  9*8,	14*8-1,	 2*8-4,  7*8-1-4 },
	{ 15*8,	20*8-1,	 6*8-4, 11*8-1-4 },
	{ 18*8,	23*8-1,	14*8-4, 19*8-1-4 },
	{ 15*8,	20*8-1, 22*8-4, 27*8-1-4 },
	{  9*8,	14*8-1, 26*8-4, 31*8-1-4 },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL SubButtonRect3[] =
{
	{ 18*8,	23*8-1,	10*8, 15*8-1 },
	{ 18*8,	23*8-1,	17*8, 22*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

static const RECT_HIT_TBL * SubButtonRectTbl[] = {
	SubButtonRect1,
	SubButtonRect2,
	SubButtonRect3,
};







void PokeStatus_SubButtonMake( PST_WORK * wk )
{
	switch( wk->dat->mode ){
	case PST_MODE_NORMAL:		// 通常
	case PST_MODE_NO_WAZACHG:	// 技入れ替え不可
		if( wk->dat->ev_contest != 0 ){
			wk->sub_type = 0;
		}else{
			wk->sub_type = 1;
			GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME0_S, GF_BGL_SCROLL_X_SET, 4 );
		}
		break;

	case PST_MODE_WAZAADD:		// 技覚え/技忘れ
	case PST_MODE_PORUTO:		// ポルト使用
	default:
		wk->sub_type = PST_SUB_OFF;
	}

	PokeStatus_SubButtonBgInit( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * ボタンBG書き換え
 *
 * @param	wk		バッグ画面のワーク
 * @param	num		ボタン番号
 * @param	anm		アニメ番号
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	BUTTON_CGX_SIZE		( 5 )
#define	BUTTON_CGX_WIDE		( 30 )

#define	BUTTON_CGX_XNEXT	( 15 )
#define	BUTTON_CGX_YNEXT	( BUTTON_CGX_WIDE * BUTTON_CGX_SIZE )


static void SubPokeButtonBgChg( PST_WORK * wk, const PST_SUB_BUTTON * tbl, u8 anm )
{
	u16 * buf;
	u16	start;
	u8	type;
	u8	i, j;
	
	buf   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_S );
//	start = ((tbl->page&1)^1)*BUTTON_CGX_XNEXT + ((tbl->page+1)/2)*BUTTON_CGX_YNEXT
//				+ anm*BUTTON_CGX_SIZE;
	start = (tbl->page&1)*BUTTON_CGX_XNEXT + (tbl->page/2)*BUTTON_CGX_YNEXT
				+ anm*BUTTON_CGX_SIZE + BUTTON_CGX_WIDE;

	for( i=0; i<BUTTON_CGX_SIZE; i++ ){
		for( j=0; j<BUTTON_CGX_SIZE; j++ ){
			buf[ (i+tbl->py)*32 + j+tbl->px ] = start+i*BUTTON_CGX_WIDE+j + (tbl->pal<<12);
		}
	}
}

void PokeStatus_SubButtonBgInit( PST_WORK * wk )
{
	const PST_SUB_BUTTON * tbl;
	u8	i;

	if( wk->sub_type == PST_SUB_OFF ){
		return;
	}

	tbl = SubButtonTypeTbl[wk->sub_type];
	i   = 0;

	while(1){
		if( tbl[i].page == 0xff ){
			break;
		}
		SubPokeButtonBgChg( wk, &tbl[i], 0 );
		i++;
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
}




u8 PokeStatus_SubBottonPageGet( PST_WORK * wk )
{
//	const PST_SUB_BUTTON * tbl;
	int	ret;
	
	ret = SubPokeButtonCheck( wk );

	if( ret != RECT_HIT_NONE ){
//		tbl = SubButtonTypeTbl[wk->sub_type];
//		return tbl[ret].page;
		return ret;
	}
	return 0xff;
}



//--------------------------------------------------------------------------------------------
/**
 * タッチパネルのボタン押し判定
 *
 * @param	wk		ワーク
 *
 * @retval	"RECT_HIT_NONE = 押されていない"
 * @retval	"RECT_HIT_NONE != 押したボタン番号"
 */
//--------------------------------------------------------------------------------------------
static int SubPokeButtonCheck( PST_WORK * wk )
{
	int	ret;

	if( wk->sub_type == PST_SUB_OFF ){
		return RECT_HIT_NONE;
	}
	
	ret = GF_TP_RectHitTrg( SubButtonRectTbl[wk->sub_type] );
/*
	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}

	}
*/
	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * タッチパネルのボタン放し判定
 *
 * @param	wk		ワーク
 *
 * @retval	"RECT_HIT_NONE = 放した"
 * @retval	"RECT_HIT_NONE != 押されている"
 */
//--------------------------------------------------------------------------------------------
static int SubPokeButtonEndCheck( PST_WORK * wk )
{
	int	ret;

	if( wk->sub_type == PST_SUB_OFF ){
		return RECT_HIT_NONE;
	}
	
	ret = GF_TP_RectHitCont( SubButtonRectTbl[wk->sub_type] );

	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}
	}
	return ret;
}


u8 PokeStatus_SubButtonAnm( PST_WORK * wk )
{
	const PST_SUB_BUTTON * tbl = SubButtonTypeTbl[wk->sub_type];

	switch( wk->btn_seq ){
	case 0:
		Snd_SePlay( PST_SE_SUB_BUTTON );
		PokeStatus_SubButtonBgInit( wk );
		SubPokeButtonBgChg( wk, &tbl[wk->btn_pos], 2 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		PokeStatus_ButtonEffInit( wk );
		wk->btn_cnt = 0;
		wk->btn_seq = 1;
		break;

	case 1:
		wk->btn_seq = 2;
		break;

	case 2:
		if( wk->btn_cnt != 3 ){
			wk->btn_cnt++;
			break;
		}

		PokeStatus_ButtonEffEnd( wk );
		if( SubPokeButtonEndCheck( wk ) != wk->btn_pos ){
			if( wk->pp.tamago != 0 &&
				tbl[wk->btn_pos].page != PST_PAGE_MEMO && tbl[wk->btn_pos].page != PST_PAGE_RET ){
				SubPokeButtonBgChg( wk, &tbl[wk->btn_pos], 0 );
			}else{
				SubPokeButtonBgChg( wk, &tbl[wk->btn_pos], 1 );
			}
			GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
			return TRUE;
		}
	}

	return FALSE;
}


void PokeStatus_ButtonPosGet( PST_WORK * wk, s16 * x, s16 * y )
{
	const PST_SUB_BUTTON * tbl = SubButtonTypeTbl[wk->sub_type];

	*x = tbl[wk->btn_pos].px * 8 + ( BUTTON_CGX_SIZE * 8 ) / 2;
	*y = tbl[wk->btn_pos].py * 8 + ( BUTTON_CGX_SIZE * 8 ) / 2;
}


u8 PokeStatus_ButtonPosPageGet( PST_WORK * wk, u8 pos )
{
	const PST_SUB_BUTTON * tbl = SubButtonTypeTbl[wk->sub_type];
	return tbl[pos].page;
}
