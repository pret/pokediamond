//============================================================================================
/**
 * @file	b_bag_anm.c
 * @brief	戦闘用バッグ画面 ボタン制御
 * @author	Hiroyuki Nakamura
 * @date	05.03.15
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "b_app_tool.h"

#define	B_BAG_ANM_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_item.h"
#include "b_bag_anm.h"


//============================================================================================
//	定数定義
//============================================================================================
// ボタンアニメパターン
enum {
	BBAG_BANM_PAT0 = 0,	// 通常
	BBAG_BANM_PAT1,		// アニメ１
	BBAG_BANM_PAT2,		// アニメ２
	BBAG_BANM_NONE,		// 押せない
};

// ポケットボタン
#define	DAT_PX_POCKET_1	( 0 )
#define	DAT_PY_POCKET_1	( 0 )
#define	DAT_PX_POCKET_2	( 0 )
#define	DAT_PY_POCKET_2	( DAT_PY_POCKET_1+BBAG_BSY_POCKET )
#define	DAT_PX_POCKET_3	( 0 )
#define	DAT_PY_POCKET_3	( DAT_PY_POCKET_2+BBAG_BSY_POCKET )
// 使用ボタン
#define	DAT_PX_USE_1	( 0 )
#define	DAT_PY_USE_1	( 27 )
#define	DAT_PX_USE_2	( 0 )
#define	DAT_PY_USE_2	( DAT_PY_USE_1+BBAG_BSY_USE )
#define	DAT_PX_USE_3	( 0 )
#define	DAT_PY_USE_3	( DAT_PY_USE_2+BBAG_BSY_USE )
#define	DAT_PX_USE_4	( 0 )
#define	DAT_PY_USE_4	( DAT_PY_USE_3+BBAG_BSY_USE )
// 戻るボタン
#define	DAT_PX_RET_1	( 0 )
#define	DAT_PY_RET_1	( 57 )
#define	DAT_PX_RET_2	( DAT_PX_RET_1+BBAG_BSX_RET )
#define	DAT_PY_RET_2	( 57 )
#define	DAT_PX_RET_3	( DAT_PX_RET_2+BBAG_BSX_RET )
#define	DAT_PY_RET_3	( 57 )
// アイテム
#define	DAT_PX_ITEM_1	( 16 )
#define	DAT_PY_ITEM_1	( 0 )
#define	DAT_PX_ITEM_2	( 16 )
#define	DAT_PY_ITEM_2	( DAT_PY_ITEM_1+BBAG_BSY_ITEM )
#define	DAT_PX_ITEM_3	( 16 )
#define	DAT_PY_ITEM_3	( DAT_PY_ITEM_2+BBAG_BSY_ITEM )
#define	DAT_PX_ITEM_4	( 16 )
#define	DAT_PY_ITEM_4	( DAT_PY_ITEM_3+BBAG_BSY_ITEM )
// 前のページへ
#define	DAT_PX_UP_1		( 0 )
#define	DAT_PY_UP_1		( 47 )
#define	DAT_PX_UP_2		( DAT_PX_UP_1+BBAG_BSX_UP )
#define	DAT_PY_UP_2		( 47 )
#define	DAT_PX_UP_3		( DAT_PX_UP_2+BBAG_BSX_UP )
#define	DAT_PY_UP_3		( 47 )
#define	DAT_PX_UP_4		( DAT_PX_UP_3+BBAG_BSX_UP )
#define	DAT_PY_UP_4		( 47 )
// 次のページへ
#define	DAT_PX_DOWN_1	( 0 )
#define	DAT_PY_DOWN_1	( 52 )
#define	DAT_PX_DOWN_2	( DAT_PX_DOWN_1+BBAG_BSX_DOWN )
#define	DAT_PY_DOWN_2	( 52 )
#define	DAT_PX_DOWN_3	( DAT_PX_DOWN_2+BBAG_BSX_DOWN )
#define	DAT_PY_DOWN_3	( 52 )
#define	DAT_PX_DOWN_4	( DAT_PX_DOWN_3+BBAG_BSX_DOWN )
#define	DAT_PY_DOWN_4	( 52 )
// ポケットボタンアイコン HP/PP回復
#define	DAT_PX_HP_1		( 20 )
#define	DAT_PY_HP_1		( 47 )
#define	DAT_PX_HP_2		( DAT_PX_HP_1+BBAG_BSX_ICON )
#define	DAT_PY_HP_2		( 47 )
#define	DAT_PX_HP_3		( DAT_PX_HP_2+BBAG_BSX_ICON )
#define	DAT_PY_HP_3		( 47 )
// ポケットボタンアイコン 状態異常回復
#define	DAT_PX_ST_1		( 20 )
#define	DAT_PY_ST_1		( DAT_PY_HP_1+BBAG_BSY_ICON )
#define	DAT_PX_ST_2		( DAT_PX_ST_1+BBAG_BSX_ICON )
#define	DAT_PY_ST_2		( DAT_PY_ST_1 )
#define	DAT_PX_ST_3		( DAT_PX_ST_2+BBAG_BSX_ICON )
#define	DAT_PY_ST_3		( DAT_PY_ST_1 )
// ポケットボタンアイコン ボール
#define	DAT_PX_BALL_1	( 20 )
#define	DAT_PY_BALL_1	( DAT_PY_ST_1+BBAG_BSY_ICON )
#define	DAT_PX_BALL_2	( DAT_PX_BALL_1+BBAG_BSX_ICON )
#define	DAT_PY_BALL_2	( DAT_PY_BALL_1 )
#define	DAT_PX_BALL_3	( DAT_PX_BALL_2+BBAG_BSX_ICON )
#define	DAT_PY_BALL_3	( DAT_PY_BALL_1 )
// ポケットボタンアイコン 戦闘用
#define	DAT_PX_BATL_1	( 20 )
#define	DAT_PY_BATL_1	( DAT_PY_BALL_1+BBAG_BSY_ICON )
#define	DAT_PX_BATL_2	( DAT_PX_BATL_1+BBAG_BSX_ICON )
#define	DAT_PY_BATL_2	( DAT_PY_BATL_1 )
#define	DAT_PX_BATL_3	( DAT_PX_BATL_2+BBAG_BSX_ICON )
#define	DAT_PY_BATL_3	( DAT_PY_BATL_1 )

// １ページ目のボタン座標
#define	P1_PAGE1_SCR_PX		( 0 )
#define	P1_PAGE1_SCR_PY		( 1 )
#define	P1_PAGE2_SCR_PX		( 0 )
#define	P1_PAGE2_SCR_PY		( P1_PAGE1_SCR_PY + BBAG_BSY_POCKET )
#define	P1_PAGE3_SCR_PX		( BBAG_BSX_POCKET )
#define	P1_PAGE3_SCR_PY		( 1 )
#define	P1_PAGE4_SCR_PX		( BBAG_BSX_POCKET )
#define	P1_PAGE4_SCR_PY		( P1_PAGE3_SCR_PY + BBAG_BSY_POCKET )
#define	P1_LASTITEM_SCR_PX	( 0 )
#define	P1_LASTITEM_SCR_PY	( 19 )
#define	P1_RETURN_SCR_PX	( 27 )
#define	P1_RETURN_SCR_PY	( 19 )
// ２ページ目のボタン座標
#define	P2_ITEM1_SCR_PX		( 32 )
#define	P2_ITEM1_SCR_PY		( 1 )
#define	P2_ITEM2_SCR_PX		( 48 )
#define	P2_ITEM2_SCR_PY		( 1 )
#define	P2_ITEM3_SCR_PX		( 32 )
#define	P2_ITEM3_SCR_PY		( 7 )
#define	P2_ITEM4_SCR_PX		( 48 )
#define	P2_ITEM4_SCR_PY		( 7 )
#define	P2_ITEM5_SCR_PX		( 32 )
#define	P2_ITEM5_SCR_PY		( 13 )
#define	P2_ITEM6_SCR_PX		( 48 )
#define	P2_ITEM6_SCR_PY		( 13 )
#define	P2_UP_SCR_PX		( 32 )
#define	P2_UP_SCR_PY		( 19 )
#define	P2_DOWN_SCR_PX		( 37 )
#define	P2_DOWN_SCR_PY		( 19 )
#define	P2_RETURN_SCR_PX	( 59 )
#define	P2_RETURN_SCR_PY	( 19 )
// ３ページ目のボタン座標
#define	P3_USE_SCR_PX		( 0 )
#define	P3_USE_SCR_PY		( 51 )
#define	P3_RETURN_SCR_PX	( 27 )
#define	P3_RETURN_SCR_PY	( 51 )


typedef struct {
	u8	px;
	u8	py;
	u8	sx;
	u8	sy;
}BUTTON_ANM;

static void BBAG_ScrnCopy( u16 * buf, u16 * scrn, u8 px, u8 py, u8 sx, u8 sy );



static const BUTTON_ANM ButtonScreenAnm[] =
{
	{ P1_PAGE1_SCR_PX, P1_PAGE1_SCR_PY, BBAG_BSX_POCKET, BBAG_BSY_POCKET },
	{ P1_PAGE2_SCR_PX, P1_PAGE2_SCR_PY, BBAG_BSX_POCKET, BBAG_BSY_POCKET },
	{ P1_PAGE3_SCR_PX, P1_PAGE3_SCR_PY, BBAG_BSX_POCKET, BBAG_BSY_POCKET },
	{ P1_PAGE4_SCR_PX, P1_PAGE4_SCR_PY, BBAG_BSX_POCKET, BBAG_BSY_POCKET },
	{ P1_LASTITEM_SCR_PX, P1_LASTITEM_SCR_PY, BBAG_BSX_USE, BBAG_BSY_USE },
	{ P1_RETURN_SCR_PX, P1_RETURN_SCR_PY, BBAG_BSX_RET, BBAG_BSY_RET },

	{ P2_ITEM1_SCR_PX, P2_ITEM1_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_ITEM2_SCR_PX, P2_ITEM2_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_ITEM3_SCR_PX, P2_ITEM3_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_ITEM4_SCR_PX, P2_ITEM4_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_ITEM5_SCR_PX, P2_ITEM5_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_ITEM6_SCR_PX, P2_ITEM6_SCR_PY, BBAG_BSX_ITEM, BBAG_BSY_ITEM },
	{ P2_UP_SCR_PX, P2_UP_SCR_PY, BBAG_BSX_UP, BBAG_BSY_UP },
	{ P2_DOWN_SCR_PX, P2_DOWN_SCR_PY, BBAG_BSX_DOWN, BBAG_BSY_DOWN },
	{ P2_RETURN_SCR_PX, P2_RETURN_SCR_PY, BBAG_BSX_RET, BBAG_BSY_RET },

	{ P3_USE_SCR_PX, P3_USE_SCR_PY, BBAG_BSX_USE, BBAG_BSY_USE },
	{ P3_RETURN_SCR_PX, P3_RETURN_SCR_PY, BBAG_BSX_RET, BBAG_BSY_RET },
};

static const u8 BtnBmpWin_Page1[] = { WIN_P1_HP, 0xff };		// 「PPかいふく」
static const u8 BtnBmpWin_Page2[] = { WIN_P1_ZYOUTAI, 0xff };	// 「じょうたいかいふく」
static const u8 BtnBmpWin_Page3[] = { WIN_P1_BALL, 0xff };		// 「ボール」
static const u8 BtnBmpWin_Page4[] = { WIN_P1_BATTLE, 0xff };	// 「せんとうよう」
static const u8 BtnBmpWin_Last[]  = { WIN_P1_LASTITEM, 0xff };	// 「さいごにつかったどうぐ」
static const u8 BtnBmpWin_Item1[] = { WIN_P2_NAME1, WIN_P2_NUM1, 0xff };
static const u8 BtnBmpWin_Item2[] = { WIN_P2_NAME2, WIN_P2_NUM2, 0xff };
static const u8 BtnBmpWin_Item3[] = { WIN_P2_NAME3, WIN_P2_NUM3, 0xff };
static const u8 BtnBmpWin_Item4[] = { WIN_P2_NAME4, WIN_P2_NUM4, 0xff };
static const u8 BtnBmpWin_Item5[] = { WIN_P2_NAME5, WIN_P2_NUM5, 0xff };
static const u8 BtnBmpWin_Item6[] = { WIN_P2_NAME6, WIN_P2_NUM6, 0xff };
static const u8 BtnBmpWin_Item1_S[] = { WIN_P2_NAME1_S, WIN_P2_NUM1_S, 0xff };
static const u8 BtnBmpWin_Item2_S[] = { WIN_P2_NAME2_S, WIN_P2_NUM2_S, 0xff };
static const u8 BtnBmpWin_Item3_S[] = { WIN_P2_NAME3_S, WIN_P2_NUM3_S, 0xff };
static const u8 BtnBmpWin_Item4_S[] = { WIN_P2_NAME4_S, WIN_P2_NUM4_S, 0xff };
static const u8 BtnBmpWin_Item5_S[] = { WIN_P2_NAME5_S, WIN_P2_NUM5_S, 0xff };
static const u8 BtnBmpWin_Item6_S[] = { WIN_P2_NAME6_S, WIN_P2_NUM6_S, 0xff };
static const u8 BtnBmpWin_Use[] = { WIN_P3_USE, 0xff };

static const u8 * const ButtonBmpWinIndex[] = {
	BtnBmpWin_Page1,	// 「HPかいふく」
	BtnBmpWin_Page2,	// 「じょうたいかいふく」
	BtnBmpWin_Page3,	// 「ボール」
	BtnBmpWin_Page4,	// 「せんとうよう」
	BtnBmpWin_Last,		// 「さいごにつかったどうぐ」
	NULL,				// 戻る

	BtnBmpWin_Item1,
	BtnBmpWin_Item2,
	BtnBmpWin_Item3,
	BtnBmpWin_Item4,
	BtnBmpWin_Item5,
	BtnBmpWin_Item6,
	NULL,				// 前へ
	NULL,				// 次へ
	NULL,				// 戻る

	BtnBmpWin_Use,		// 「つかう」
	NULL,

	BtnBmpWin_Item1_S,
	BtnBmpWin_Item2_S,
	BtnBmpWin_Item3_S,
	BtnBmpWin_Item4_S,
	BtnBmpWin_Item5_S,
	BtnBmpWin_Item6_S,
};

#define	SWAP_BMP_POS	( BBAG_BTNANM_RET3+1 )



void BattleBag_ButtonScreenMake( BBAG_WORK * wk, u16 * scrn )
{
	// ポケットボタン
	BBAG_ScrnCopy(
		wk->btn_pocket[BBAG_BANM_PAT0], scrn,
		DAT_PX_POCKET_1, DAT_PY_POCKET_1, BBAG_BSX_POCKET, BBAG_BSY_POCKET );
	BBAG_ScrnCopy(
		wk->btn_pocket[BBAG_BANM_PAT1], scrn,
		DAT_PX_POCKET_2, DAT_PY_POCKET_2, BBAG_BSX_POCKET, BBAG_BSY_POCKET );
	BBAG_ScrnCopy(
		wk->btn_pocket[BBAG_BANM_PAT2], scrn,
		DAT_PX_POCKET_3, DAT_PY_POCKET_3, BBAG_BSX_POCKET, BBAG_BSY_POCKET );

	// 使用ボタン
	BBAG_ScrnCopy(
		wk->btn_use[BBAG_BANM_PAT0], scrn,
		DAT_PX_USE_1, DAT_PY_USE_1, BBAG_BSX_USE, BBAG_BSY_USE );
	BBAG_ScrnCopy(
		wk->btn_use[BBAG_BANM_PAT1], scrn,
		DAT_PX_USE_2, DAT_PY_USE_2, BBAG_BSX_USE, BBAG_BSY_USE );
	BBAG_ScrnCopy(
		wk->btn_use[BBAG_BANM_PAT2], scrn,
		DAT_PX_USE_3, DAT_PY_USE_3, BBAG_BSX_USE, BBAG_BSY_USE );
	BBAG_ScrnCopy(
		wk->btn_use[BBAG_BANM_NONE], scrn,
		DAT_PX_USE_3, DAT_PY_USE_3, BBAG_BSX_USE, BBAG_BSY_USE );

	// 戻るボタン
	BBAG_ScrnCopy(
		wk->btn_ret[BBAG_BANM_PAT0], scrn,
		DAT_PX_RET_1, DAT_PY_RET_1, BBAG_BSX_RET, BBAG_BSY_RET );
	BBAG_ScrnCopy(
		wk->btn_ret[BBAG_BANM_PAT1], scrn,
		DAT_PX_RET_2, DAT_PY_RET_2, BBAG_BSX_RET, BBAG_BSY_RET );
	BBAG_ScrnCopy(
		wk->btn_ret[BBAG_BANM_PAT2], scrn,
		DAT_PX_RET_3, DAT_PY_RET_3, BBAG_BSX_RET, BBAG_BSY_RET );

	// アイテム
	BBAG_ScrnCopy(
		wk->btn_item[BBAG_BANM_PAT0], scrn,
		DAT_PX_ITEM_1, DAT_PY_ITEM_1, BBAG_BSX_ITEM, BBAG_BSY_ITEM );
	BBAG_ScrnCopy(
		wk->btn_item[BBAG_BANM_PAT1], scrn,
		DAT_PX_ITEM_2, DAT_PY_ITEM_2, BBAG_BSX_ITEM, BBAG_BSY_ITEM );
	BBAG_ScrnCopy(
		wk->btn_item[BBAG_BANM_PAT2], scrn,
		DAT_PX_ITEM_3, DAT_PY_ITEM_3, BBAG_BSX_ITEM, BBAG_BSY_ITEM );
	BBAG_ScrnCopy(
		wk->btn_item[BBAG_BANM_NONE], scrn,
		DAT_PX_ITEM_4, DAT_PY_ITEM_4, BBAG_BSX_ITEM, BBAG_BSY_ITEM );

	// 前のページへ
	BBAG_ScrnCopy(
		wk->btn_up[BBAG_BANM_PAT0], scrn, DAT_PX_UP_1, DAT_PY_UP_1, BBAG_BSX_UP, BBAG_BSY_UP );
	BBAG_ScrnCopy(
		wk->btn_up[BBAG_BANM_PAT1], scrn, DAT_PX_UP_2, DAT_PY_UP_2, BBAG_BSX_UP, BBAG_BSY_UP );
	BBAG_ScrnCopy(
		wk->btn_up[BBAG_BANM_PAT2], scrn, DAT_PX_UP_3, DAT_PY_UP_3, BBAG_BSX_UP, BBAG_BSY_UP );
	BBAG_ScrnCopy(
		wk->btn_up[BBAG_BANM_NONE], scrn, DAT_PX_UP_4, DAT_PY_UP_4, BBAG_BSX_UP, BBAG_BSY_UP );

	// 次のページへ
	BBAG_ScrnCopy(
		wk->btn_down[BBAG_BANM_PAT0], scrn,
		DAT_PX_DOWN_1, DAT_PY_DOWN_1, BBAG_BSX_DOWN, BBAG_BSY_DOWN );
	BBAG_ScrnCopy(
		wk->btn_down[BBAG_BANM_PAT1], scrn,
		DAT_PX_DOWN_2, DAT_PY_DOWN_2, BBAG_BSX_DOWN, BBAG_BSY_DOWN );
	BBAG_ScrnCopy(
		wk->btn_down[BBAG_BANM_PAT2], scrn,
		DAT_PX_DOWN_3, DAT_PY_DOWN_3, BBAG_BSX_DOWN, BBAG_BSY_DOWN );
	BBAG_ScrnCopy(
		wk->btn_down[BBAG_BANM_NONE], scrn,
		DAT_PX_DOWN_4, DAT_PY_DOWN_4, BBAG_BSX_DOWN, BBAG_BSY_DOWN );

	// ポケットボタンアイコン HP/PP回復
	BBAG_ScrnCopy(
		wk->btn_icon_hp[BBAG_BANM_PAT0], scrn,
		DAT_PX_HP_1, DAT_PY_HP_1, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_hp[BBAG_BANM_PAT1], scrn,
		DAT_PX_HP_2, DAT_PY_HP_2, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_hp[BBAG_BANM_PAT2], scrn,
		DAT_PX_HP_3, DAT_PY_HP_3, BBAG_BSX_ICON, BBAG_BSY_ICON );

	// ポケットボタンアイコン 状態異常回復
	BBAG_ScrnCopy(
		wk->btn_icon_st[BBAG_BANM_PAT0], scrn,
		DAT_PX_ST_1, DAT_PY_ST_1, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_st[BBAG_BANM_PAT1], scrn,
		DAT_PX_ST_2, DAT_PY_ST_2, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_st[BBAG_BANM_PAT2], scrn,
		DAT_PX_ST_3, DAT_PY_ST_3, BBAG_BSX_ICON, BBAG_BSY_ICON );

	// ポケットボタンアイコン ボール
	BBAG_ScrnCopy(
		wk->btn_icon_ball[BBAG_BANM_PAT0], scrn,
		DAT_PX_BALL_1, DAT_PY_BALL_1, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_ball[BBAG_BANM_PAT1], scrn,
		DAT_PX_BALL_2, DAT_PY_BALL_2, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_ball[BBAG_BANM_PAT2], scrn,
		DAT_PX_BALL_3, DAT_PY_BALL_3, BBAG_BSX_ICON, BBAG_BSY_ICON );

	// ポケットボタンアイコン 戦闘用
	BBAG_ScrnCopy(
		wk->btn_icon_batl[BBAG_BANM_PAT0], scrn,
		DAT_PX_BATL_1, DAT_PY_BATL_1, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_batl[BBAG_BANM_PAT1], scrn,
		DAT_PX_BATL_2, DAT_PY_BATL_2, BBAG_BSX_ICON, BBAG_BSY_ICON );
	BBAG_ScrnCopy(
		wk->btn_icon_batl[BBAG_BANM_PAT2], scrn,
		DAT_PX_BATL_3, DAT_PY_BATL_3, BBAG_BSX_ICON, BBAG_BSY_ICON );
}


static void BBAG_ScrnCopy( u16 * buf, u16 * scrn, u8 px, u8 py, u8 sx, u8 sy )
{
	u16	i, j;

	for( i=0; i<sy; i++ ){
		for( j=0; j<sx; j++ ){
			buf[i*sx+j] = scrn[ (py+i)*32 + px+j ];
		}
	}
}


static u16 * BBAG_ButtonScreenBufGet( BBAG_WORK * wk, u8 id, u8 num )
{
	switch( id ){
	case BBAG_BTNANM_PAGE1:
	case BBAG_BTNANM_PAGE2:
	case BBAG_BTNANM_PAGE3:
	case BBAG_BTNANM_PAGE4:
		return wk->btn_pocket[num];

	case BBAG_BTNANM_LAST:
		return wk->btn_use[num];

	case BBAG_BTNANM_RET1:
	case BBAG_BTNANM_RET2:
	case BBAG_BTNANM_RET3:
		return wk->btn_ret[num];

	case BBAG_BTNANM_ITEM1:
	case BBAG_BTNANM_ITEM2:
	case BBAG_BTNANM_ITEM3:
	case BBAG_BTNANM_ITEM4:
	case BBAG_BTNANM_ITEM5:
	case BBAG_BTNANM_ITEM6:
		return wk->btn_item[num];

	case BBAG_BTNANM_UP:
		return wk->btn_up[num];

	case BBAG_BTNANM_DOWN:
		return wk->btn_down[num];

	case BBAG_BTNANM_USE:
		return wk->btn_use[num];
	}
	return NULL;
}

static u16 BBAG_ButtonPalGet( BBAG_WORK * wk, u8 id, u8 anm, u8 page )
{
	if( anm == BBAG_BANM_NONE ){
		return 5;
	}

	switch( id ){
	case BBAG_BTNANM_PAGE1:
	case BBAG_BTNANM_PAGE2:
	case BBAG_BTNANM_PAGE3:
	case BBAG_BTNANM_PAGE4:
		return 0;

	case BBAG_BTNANM_LAST:
		return 3;

	case BBAG_BTNANM_RET1:
	case BBAG_BTNANM_RET2:
	case BBAG_BTNANM_RET3:
	case BBAG_BTNANM_UP:
	case BBAG_BTNANM_DOWN:
		return 2;

	case BBAG_BTNANM_ITEM1:
	case BBAG_BTNANM_ITEM2:
	case BBAG_BTNANM_ITEM3:
	case BBAG_BTNANM_ITEM4:
	case BBAG_BTNANM_ITEM5:
	case BBAG_BTNANM_ITEM6:
		return 8+wk->poke_id;

	case BBAG_BTNANM_USE:
		if( page == BBAG_PAGE_ITEM ){
			return 8+wk->poke_id;
		}else{
			return 1;
		}
	}
	return 0;
}

#define	PAGE_ICON_BPX	( 6 )
#define	PAGE_ICON_BPY	( 0 )

static void BBAG_ButtonPageIconSet( BBAG_WORK * wk, u16 * buf, u8 id, u8 anm )
{
	u16 * icon;
	u16	i, j;

	if( id == BBAG_BTNANM_PAGE1 ){
		icon = wk->btn_icon_hp[anm];
	}else if( id == BBAG_BTNANM_PAGE2 ){
		icon = wk->btn_icon_st[anm];
	}else if( id == BBAG_BTNANM_PAGE3 ){
		icon = wk->btn_icon_ball[anm];
	}else if( id == BBAG_BTNANM_PAGE4 ){
		icon = wk->btn_icon_batl[anm];
	}else{
		return;
	}

	for( i=0; i<BBAG_BSY_ICON; i++ ){
		for( j=0; j<BBAG_BSX_ICON; j++ ){
			buf[BBAG_BSX_POCKET*(PAGE_ICON_BPY+i)+PAGE_ICON_BPX+j] = icon[BBAG_BSX_ICON*i+j];
		}
	}
}

static void BBAG_ButtonBufMake( BBAG_WORK * wk, u16 * buf, u8 id, u8 anm, u8 page )
{
	u16 * get;
	u16	pal;
	u16	i;

	get = BBAG_ButtonScreenBufGet( wk, id, anm );
	pal = BBAG_ButtonPalGet( wk, id, anm, page ) << 12;

	for( i=0; i<ButtonScreenAnm[id].sx*ButtonScreenAnm[id].sy; i++ ){
		buf[i] = pal | ( get[i] & 0xfff );
	}

	BBAG_ButtonPageIconSet( wk, buf, id, anm );
}

static void BBAG_ButtonScreenWrite( BBAG_WORK * wk, u8 id, u8 anm, u8 page )
{
	u16 * buf;

	buf = sys_AllocMemory( wk->dat->heap, ButtonScreenAnm[id].sx*ButtonScreenAnm[id].sy*2 );

	BBAG_ButtonBufMake( wk, buf, id, anm, page );

	GF_BGL_ScrWrite(
		wk->bgl, GF_BGL_FRAME2_S, buf,
		ButtonScreenAnm[id].px, ButtonScreenAnm[id].py,
		ButtonScreenAnm[id].sx, ButtonScreenAnm[id].sy );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_S );

	sys_FreeMemoryEz( buf );
}

static void BBAG_ButtonBmpWinShift( BBAG_WORK * wk, u8 id, u8 anm )
{
	const u8 * tbl;
	u16	i;
	u8	dir, ofs;

	if( id >= BBAG_BTNANM_ITEM1 && id <= BBAG_BTNANM_ITEM6 && wk->p2_swap == 0 ){
		tbl = ButtonBmpWinIndex[SWAP_BMP_POS+id-BBAG_BTNANM_ITEM1];
	}else{
		tbl = ButtonBmpWinIndex[id];
	}
	if( tbl == NULL ){ return; }

	switch( anm ){
	case 0:
	case 2:
		dir = GF_BGL_BMPWIN_SHIFT_D;
		ofs = 2;
		break;
	case 1:
		dir = GF_BGL_BMPWIN_SHIFT_U;
		ofs = 4;
		break;
	}

	for( i=0; i<8; i++ ){
		if( tbl[i] == 0xff ){ break; }
		GF_BGL_BmpWinShift( &wk->add_win[tbl[i]], dir, ofs, 0 );
		GF_BGL_BmpWinOnVReq( &wk->add_win[tbl[i]] );
	}
}

static void BBAG_ButtonObjMove( BBAG_WORK * wk, u8 id, u8 anm )
{
	CATS_ACT_PTR cap;
	u8	i;

	if( id >= BBAG_BTNANM_ITEM1 && id <= BBAG_BTNANM_ITEM6 ){
		cap = wk->cap[id-BBAG_BTNANM_ITEM1];
	}else if( id == BBAG_BTNANM_LAST ){
		for( i=0; i<6; i++ ){
			cap = wk->cap[i];
			if( CATS_ObjectEnableGetCap(cap) != 0 ){
				break;
			}
		}
	}else{
		return;
	}

	switch( anm ){
	case 0:
	case 2:
		CATS_ObjectPosMoveCap( cap, 0, 2 );
		break;
	case 1:
		CATS_ObjectPosMoveCap( cap, 0, -4 );
		break;
	}
}


void BattleBag_ButtonAnmInit( BBAG_WORK * wk, u8 id, u8 mode )
{
	wk->btn_seq  = 0;
	wk->btn_cnt  = 0;
	wk->btn_id   = id;
	wk->btn_mode = mode;
	wk->btn_flg  = 1;
}

void BattleBag_ButtonAnmMain( BBAG_WORK * wk )
{
	if( wk->btn_flg == 0 ){ return; }

	switch( wk->btn_seq ){
	case 0:
		BBAG_ButtonScreenWrite( wk, wk->btn_id, 1, wk->page );
		BBAG_ButtonBmpWinShift( wk, wk->btn_id, 1 );
		BBAG_ButtonObjMove( wk, wk->btn_id, 1 );
		wk->btn_cnt = 0;
		wk->btn_seq = 1;
		break;

	case 1:
/*
		if( wk->btn_cnt < 1 ){
			wk->btn_cnt++;
			return;
		}
*/
		BBAG_ButtonScreenWrite( wk, wk->btn_id, 2, wk->page );
		BBAG_ButtonBmpWinShift( wk, wk->btn_id, 2 );
		BBAG_ButtonObjMove( wk, wk->btn_id, 2 );
		wk->btn_cnt = 0;
		wk->btn_seq = 2;
		break;

	case 2:
/*
		if( wk->btn_cnt < 1 ){
			wk->btn_cnt++;
			return;
		}
*/
		BBAG_ButtonScreenWrite( wk, wk->btn_id, 0, wk->page );
		BBAG_ButtonBmpWinShift( wk, wk->btn_id, 0 );
		BBAG_ButtonObjMove( wk, wk->btn_id, 0 );
		wk->btn_cnt = 0;
//		wk->btn_seq = 3;
		wk->btn_seq = 0;
		wk->btn_flg = 0;
		break;
/*
	case 3:
		wk->btn_flg = 0;
		break;
*/
	}
}

void BattleBag_ButtonPageScreenInit( BBAG_WORK * wk, u8 page )
{
	switch( page ){
	case BBAG_PAGE_POCKET:	// ポケット選択ページ
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_PAGE1, 0, page );
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_PAGE2, 0, page );
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_PAGE3, 0, page );
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_PAGE4, 0, page );
		if( wk->dat->used_item == 0 ){
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_LAST, BBAG_BANM_NONE, page );
		}else{
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_LAST, BBAG_BANM_PAT0, page );
		}
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_RET1, BBAG_BANM_PAT0, page );
		break;

	case BBAG_PAGE_MAIN:	// アイテム選択ページ
		{
			u32	i;

			for( i=0; i<6; i++ ){
				if( BattleBag_PosItemCheck( wk, i ) == 0 ){
					BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_ITEM1+i, BBAG_BANM_NONE, page );
				}else{
					BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_ITEM1+i, BBAG_BANM_PAT0, page );
				}
			}
		}
		if( wk->scr_max[wk->poke_id] == 0 ){
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_UP, BBAG_BANM_NONE, page );
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_DOWN, BBAG_BANM_NONE, page );
		}else{
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_UP, BBAG_BANM_PAT0, page );
			BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_DOWN, BBAG_BANM_PAT0, page );
		}
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_RET2, 0, page );
		break;

	case BBAG_PAGE_ITEM:	// アイテム使用ページ
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_USE, 0, page );
		BBAG_ButtonScreenWrite( wk, BBAG_BTNANM_RET3, 0, page );
	}
}
