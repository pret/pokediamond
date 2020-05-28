//============================================================================================
/**
 * @file	pst_obj.c
 * @brief	ポケモンステータス画面OBJ
 * @author	Hiroyuki Nakamura
 * @date	2005.10.27
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/window.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "system/buflen.h"
#include "battle/battle_common.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "application/app_tool.h"
#include "battle/wazatype_icon.h"
#include "ribbon.h"

#define	PST_OBJ_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
#include "pst_sub.h"
#include "pst_snd_def.h"
#include "application/pst_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================

enum {
	PST_CHR_ID_BALL = 0,
	PST_CHR_ID_TAB,
	PST_CHR_ID_WAZACURSOR,

	PST_CHR_ID_POKETYPE1,
	PST_CHR_ID_POKETYPE2,
	PST_CHR_ID_WAZATYPE1,
	PST_CHR_ID_WAZATYPE2,
	PST_CHR_ID_WAZATYPE3,
	PST_CHR_ID_WAZATYPE4,
	PST_CHR_ID_WAZATYPE5,
	PST_CHR_ID_WAZAKIND,

	PST_CHR_ID_POKEICON,

	PST_CHR_ID_STIZYO,
	PST_CHR_ID_FLASH,
	PST_CHR_ID_ARROW,

	PST_CHR_ID_BUTTON_EF,

	PST_CHR_ID_CNDITION_UP,

	PST_CHR_ID_A_BUTTON,

	PST_CHR_ID_MARK01,
	PST_CHR_ID_MARK02,
	PST_CHR_ID_MARK03,
	PST_CHR_ID_MARK04,
	PST_CHR_ID_MARK05,
	PST_CHR_ID_MARK06,
	PST_CHR_ID_MARK07,	// ポケルス・レアカラー

	PST_CHR_ID_EZCND,

	PST_CHR_ID_RIBBON01,
	PST_CHR_ID_RIBBON02,
	PST_CHR_ID_RIBBON03,
	PST_CHR_ID_RIBBON04,
	PST_CHR_ID_RIBBON05,
	PST_CHR_ID_RIBBON06,
	PST_CHR_ID_RIBBON07,
	PST_CHR_ID_RIBBON08,
	PST_CHR_ID_RIBBON09,
	PST_CHR_ID_RIBBON10,
	PST_CHR_ID_RIBBON11,
	PST_CHR_ID_RIBBON12,
	PST_CHR_ID_RIBBON_CUR,

	PST_CHR_ID_RIBBON_ARROW,
	PST_CHR_ID_RIBBON_FLASH,
	PST_CHR_ID_CON_FLASH,
	PST_CHR_ID_POKERUS,
};

#define	PT_ICON_P1_PX	( 199 )
#define	PT_ICON_P1_PY	( 80 )
#define	PT_ICON_P4_PX	( 63 )
#define	PT_ICON_P4_PY	( 52 )
#define	WT_ICON_P4_PX	( 151 )
#define	WT_ICON_P4_PY	( 43 )
#define	KT_ICON_P4_PX	( 92+16 )
#define	KT_ICON_P4_PY	( 72 )
#define	POKE_ICON_PX		( 24 )
#define	POKE_ICON_PY		( 48 )
#define	CON_POKE_ICON_PX	( 32 )
#define	CON_POKE_ICON_PY	( 68 )

#define	TAB_PX	( 128 )		// ページタブ表示X座標
#define	TAB_PY	( 24 )		// ページタブ表示Y座標

#define	BALL_PX	( 16 )		// ボール表示X座標
#define	BALL_PY	( 32 )		// ボール表示Y座標

#define	WAZACURSOR_PX	( 194 )		// 技カーソル表示X座標
#define	WAZACURSOR_PY	( 48 )		// 技カーソル表示Y座標

#define	ST_ICON_PX	( 80 )			// 状態異常アイコン表示X座標
#define	ST_ICON_PY	( 52 )			// 状態異常アイコン表示Y座標

#define	ST_ICON_POKERUS_PX	( 76 )	// ポケルスアイコン表示X座標
#define	ST_ICON_POKERUS_PY	( 48 )	// ポケルスアイコン表示Y座標

#define	TAB_ARROW_PY	( 24 )		// ページタブ切り替え矢印表示Y座標

#define	BOX_MARK_PX	( 48 )			// ボックスマーク表示X座標
#define	BOX_MARK_PY	( 150 )			// ボックスマーク表示Y座標

#define	FLASH_PX	( 152 )			// けづや表示X座標
#define	FLASH_PY	( 168 )			// けづや表示Y座標

#define	RARE_MARK_PX		( 98 )		// レアマーク表示X座標
#define	RARE_MARK_PY		( 72 )		// レアマーク表示Y座標
#define	POKERUS_MARK_PX		( 98 )		// ポケルスマーク表示X座標
#define	POKERUS_MARK_PY		( 132 )		// ポケルスマーク表示Y座標

#define	RIBBON_MX	( 32 )				// リボン表示X間隔
#define	RIBBON_MY	( 40 )				// リボン表示Y間隔

#define	RIBON_PX1	( 132 )						// リボン表示X座標（１列目）
#define	RIBON_PX2	( RIBON_PX1 + RIBBON_MX )	// リボン表示X座標（２列目）
#define	RIBON_PX3	( RIBON_PX2 + RIBBON_MX )	// リボン表示X座標（３列目）
#define	RIBON_PX4	( RIBON_PX3 + RIBBON_MX )	// リボン表示X座標（４列目）

#define	RIBON_PY1	( 56 )						// リボン表示Y座標（１行目）
#define	RIBON_PY2	( RIBON_PY1 + RIBBON_MY )	// リボン表示Y座標（２行目）
#define	RIBON_PY3	( RIBON_PY2 + RIBBON_MY )	// リボン表示Y座標（３行目）

#define	RIBBON_ARROW_PX		( 180 )				// リボン切り替え矢印表示X座標
#define	RIBBON_ARROW_UPY	( 32 )				// リボン切り替え上矢印表示Y座標
#define	RIBBON_ARROW_DPY	( 120 )				// リボン切り替え下矢印表示Y座標

#define	TAB_CENTER_PX	( 23 * 8 + 4 )	// タブ表示中心X座標
#define	TAB_SEL_SX		( 24 )			// 選択中のタブXサイズ
#define	TAB_NOSEL_SX	( 16 )			// その他のタブXサイズ
#define	TAB_L_ARROW_PSX	( -12 )			// タブ切り替え左矢印の表示X座標補正値
#define	TAB_R_ARROW_PSX	( -4 )			// タブ切り替え右矢印の表示X座標補正値

#define	KEDUYA_ANM_MAX	( 12 )		// けづや表示最大数

#define	A_BUTTON_PY		( 8 )	///< Aボタンマーク表示Y座標

#define	PST_POKEICON_PAL	( 7 )	// ポケモンアイコンで使用するパレット番号
#define	PST_RIBBON_PAL	( 7 )		// リボンで使用するパレット番号


//============================================================================================
//============================================================================================
static void AddCellActMake( PST_WORK * wk );
static void PokeStatus_TypeIconChange( PST_WORK * wk, u8 act_num, u8 res_id, u8 type );
static void InitObjCharPalChg( PST_WORK * wk );


//============================================================================================
//============================================================================================
static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
{
	{
		PST_CHR_ID_TAB, TAB_PX, TAB_PY, 0,
		0, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+16, TAB_PY, 0,
		1, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+32, TAB_PY, 0,
		2, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+48, TAB_PY, 0,
		3, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+64, TAB_PY, 0,
		4, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+80, TAB_PY, 0,
		5, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+96, TAB_PY, 0,
		6, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{
		PST_CHR_ID_TAB, TAB_PX+112, TAB_PY, 0,
		7, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// モンスターボール
		PST_CHR_ID_BALL, BALL_PX, BALL_PY, 0,
		0, 0, 12, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{
		PST_CHR_ID_WAZACURSOR, WAZACURSOR_PX, WAZACURSOR_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{
		PST_CHR_ID_WAZACURSOR, WAZACURSOR_PX, WAZACURSOR_PY, 0,
		1, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ポケモンタイプ１
		PST_CHR_ID_POKETYPE1, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ポケモンタイプ２
		PST_CHR_ID_POKETYPE2, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技タイプ１
		PST_CHR_ID_WAZATYPE1, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技タイプ２
		PST_CHR_ID_WAZATYPE2, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技タイプ３
		PST_CHR_ID_WAZATYPE3, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技タイプ４
		PST_CHR_ID_WAZATYPE4, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技タイプ５
		PST_CHR_ID_WAZATYPE5, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 技分類
		PST_CHR_ID_WAZAKIND, 0, 0, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// ポケモンアイコン
		PST_CHR_ID_POKEICON, POKE_ICON_PX, POKE_ICON_PY, 0,
		0, 0, 4, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// 状態異常アイコン
		PST_CHR_ID_STIZYO, ST_ICON_PX, ST_ICON_PY, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// タブ切り替え矢印・左
		PST_CHR_ID_ARROW, 0, TAB_ARROW_PY, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// タブ切り替え矢印・右
		PST_CHR_ID_ARROW, 0, TAB_ARROW_PY, 0,
		1, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク１
		PST_CHR_ID_MARK01, BOX_MARK_PX, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク２
		PST_CHR_ID_MARK02, BOX_MARK_PX+8, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク３
		PST_CHR_ID_MARK03, BOX_MARK_PX+16, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク４
		PST_CHR_ID_MARK04, BOX_MARK_PX+24, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク５
		PST_CHR_ID_MARK05, BOX_MARK_PX+32, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボックスマーク６
		PST_CHR_ID_MARK06, BOX_MARK_PX+40, BOX_MARK_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや１
		PST_CHR_ID_FLASH, FLASH_PX, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや２
		PST_CHR_ID_FLASH, FLASH_PX+8, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや３
		PST_CHR_ID_FLASH, FLASH_PX+16, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや４
		PST_CHR_ID_FLASH, FLASH_PX+24, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや５
		PST_CHR_ID_FLASH, FLASH_PX+32, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや６
		PST_CHR_ID_FLASH, FLASH_PX+40, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや７
		PST_CHR_ID_FLASH, FLASH_PX+48, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや８
		PST_CHR_ID_FLASH, FLASH_PX+56, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや９
		PST_CHR_ID_FLASH, FLASH_PX+64, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや１０
		PST_CHR_ID_FLASH, FLASH_PX+72, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや１１
		PST_CHR_ID_FLASH, FLASH_PX+80, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// けづや１２
		PST_CHR_ID_FLASH, FLASH_PX+88, FLASH_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ボタンエフェクト
		PST_CHR_ID_BUTTON_EF, 0, 0, 0, 
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 「UP」１
		PST_CHR_ID_CNDITION_UP, 26*8, 6*8, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 「UP」２
		PST_CHR_ID_CNDITION_UP, 28*8, 11*8, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 「UP」３
		PST_CHR_ID_CNDITION_UP, 27*8, 15*8, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 「UP」４
		PST_CHR_ID_CNDITION_UP, 18*8, 15*8, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 「UP」５
		PST_CHR_ID_CNDITION_UP, 17*8, 11*8, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// Aボタンマーク
		PST_CHR_ID_A_BUTTON, 0, 0, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 簡易コンディション（かっこよさ）
		PST_CHR_ID_EZCND, 0, 0, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 簡易コンディション（うつくしさ）
		PST_CHR_ID_EZCND, 0, 0, 0,
		1, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 簡易コンディション（かわいさ）
		PST_CHR_ID_EZCND, 0, 0, 0,
		3, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 簡易コンディション（かしこさ）
		PST_CHR_ID_EZCND, 0, 0, 0,
		2, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// 簡易コンディション（たくましさ）
		PST_CHR_ID_EZCND, 0, 0, 0,
		4, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// レアカラーマーク
		PST_CHR_ID_MARK07, RARE_MARK_PX, RARE_MARK_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ポケルスマーク
		PST_CHR_ID_MARK07, POKERUS_MARK_PX, POKERUS_MARK_PY, 0,
		1, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// リボン１
		PST_CHR_ID_RIBBON01, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン２
		PST_CHR_ID_RIBBON02, RIBON_PX2, RIBON_PY1, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン３
		PST_CHR_ID_RIBBON03, RIBON_PX3, RIBON_PY1, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン４
		PST_CHR_ID_RIBBON04, RIBON_PX4, RIBON_PY1, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン５
		PST_CHR_ID_RIBBON05, RIBON_PX1, RIBON_PY2, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン６
		PST_CHR_ID_RIBBON06, RIBON_PX2, RIBON_PY2, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン７
		PST_CHR_ID_RIBBON07, RIBON_PX3, RIBON_PY2, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン８
		PST_CHR_ID_RIBBON08, RIBON_PX4, RIBON_PY2, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン９
		PST_CHR_ID_RIBBON09, RIBON_PX1, RIBON_PY3, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン１０
		PST_CHR_ID_RIBBON10, RIBON_PX2, RIBON_PY3, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン１１
		PST_CHR_ID_RIBBON11, RIBON_PX3, RIBON_PY3, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン１２
		PST_CHR_ID_RIBBON12, RIBON_PX4, RIBON_PY3, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボンカーソル
		PST_CHR_ID_RIBBON_CUR, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},

	{	// リボンスクロール矢印・上
		PST_CHR_ID_RIBBON_ARROW, RIBBON_ARROW_PX, RIBBON_ARROW_UPY, 0,
		1, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボンスクロール矢印・下
		PST_CHR_ID_RIBBON_ARROW, RIBBON_ARROW_PX, RIBBON_ARROW_DPY, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// リボン光
		PST_CHR_ID_RIBBON_FLASH, 8, 132, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// コンディション光１
		PST_CHR_ID_CON_FLASH, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// コンディション光２
		PST_CHR_ID_CON_FLASH, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// コンディション光３
		PST_CHR_ID_CON_FLASH, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// コンディション光４
		PST_CHR_ID_CON_FLASH, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// コンディション光５
		PST_CHR_ID_CON_FLASH, RIBON_PX1, RIBON_PY1, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
	{	// ポケルス用状態異常アイコン
		PST_CHR_ID_POKERUS, ST_ICON_POKERUS_PX, ST_ICON_POKERUS_PY, 0,
		0, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 0, 0, 0
	},
};

// モンスターボールパレット（配列０はダミー）
static const u8 BallPalTbl[] = { 2,0,2,2,0,1,1,1,1,2,2,2,2,3,3,2,0 };



//---------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
void PokeStatusCellActInit( PST_WORK * wk )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// SUB DISP OBJ ON

	initVramTransferManagerHeap( 32, HEAPID_POKESTATUS );

	wk->csp = CATS_AllocMemory( HEAPID_POKESTATUS );
	wk->crp = CATS_ResourceCreate( wk->csp );

	{
		TCATS_OAM_INIT	coi = {
			0, 128,
			0, 32,
			0, 128,
			0, 32,
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			PST_OBJ_MAX,
			1024,
			1024,
			GX_OBJVRAMMODE_CHAR_1D_32K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit( wk->csp, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->csp, wk->crp, PST_OBJ_MAX );
	}

	{
		TCATS_RESOURCE_FILE_LIST list = {
			"data/pst_chr.resdat",		// キャラクタ
			"data/pst_pal.resdat",		// パレット
			"data/pst_cell.resdat",		// セル
			"data/pst_canm.resdat",		// セルアニメ
			NULL,						// マルチセル
			NULL,						// マルチセルアニメ
			"data/pst_h.cldat"			// ヘッダー
		};
		CATS_ResourceLoadBinary( wk->csp, wk->crp, &list );
	}
}

//---------------------------------------------------------------------------------------------
/**
 * セルアクター削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
void PokeStatusCellActRerease( PST_WORK * wk )
{
	CATS_ResourceDestructor( wk->csp, wk->crp );
	CATS_FreeMemory( wk->csp );
}


void PokeStatus_CellActAnm( PST_WORK * wk )
{
	CLACT_AnmFrameChg( wk->awp[PST_OBJ_ARROW_L], FX32_ONE );
	CLACT_AnmFrameChg( wk->awp[PST_OBJ_ARROW_R], FX32_ONE );
	CLACT_AnmFrameChg( wk->awp[PST_OBJ_BUTTON_EF], FX32_ONE );
	CLACT_AnmFrameChg( wk->awp[PST_OBJ_RIBBON_AU], FX32_ONE );
	CLACT_AnmFrameChg( wk->awp[PST_OBJ_RIBBON_AD], FX32_ONE );
}






void PokeStatusCellActSet( PST_WORK * wk )
{
	u16	i;

	for( i=0; i<PST_OBJ_MAX; i++ ){
		wk->awp[i] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[i] );
	}

	InitObjCharPalChg( wk );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR1], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR2], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_BUTTON_EF], 0 );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP1], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP2], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP3], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP4], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP5], 0 );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_A_BUTTON], 0 );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STYLE], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_BEAUTIFUL], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CUTE], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CLEVER], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STRONG], 0 );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH1], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH2], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH3], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH4], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH5], 0 );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_POKERUS], 0 );
}




static u8 PST_TabPosXGet( PST_WORK * wk )
{
	u8	i, num=0;

	//	タブ数チェック
	for( i=0; i<PST_PAGE_MAX; i++ ){
		if( PokeStatus_PageCheck( wk, i ) != 0 ){
			num++;
		}
	}
	return ( TAB_CENTER_PX - ( TAB_SEL_SX + (num-1)*TAB_NOSEL_SX ) / 2 );
}


void PokeStatusTabPosChg( PST_WORK * wk )
{
	CLACT_WORK_PTR * awp;
	s16	x, y;
	s16	px;
	u16	anm;
	u8	i;
	u8	num=0;

	px = PST_TabPosXGet( wk );

	awp = &wk->awp[PST_OBJ_TAB_INFO];
	num = 0;
	for( i=0; i<PST_PAGE_MAX; i++ ){
		if( PokeStatus_PageCheck( wk, i ) == 0 ){
			CLACT_SetDrawFlag( awp[i], 0 );
			continue;
		}

		anm = CLACT_AnmGet( awp[i] );
		if( wk->page == i ){
			if( anm < 8 ){
				CLACT_AnmChg( awp[i], anm + 8 );
			}
		}else{
			if( anm >= 8 ){
				CLACT_AnmChg( awp[i], anm-8 );
			}
		}

		CATS_ObjectPosGet( awp[i], &x, &y );
		if( wk->page >= i ){
			x = px + num * TAB_NOSEL_SX;
		}else{
			x = px + TAB_SEL_SX + (num-1)*TAB_NOSEL_SX;
		}
		CATS_ObjectPosSet( wk->awp[i], x, y );
		CLACT_SetDrawFlag( awp[i], 1 );
		num++;
	}
}


void PokeStatus_TabArrowPut( PST_WORK * wk )
{
	u8	px;

	if( PokeStatus_PageNumGet( wk ) <= 1 ){
		PokeStatus_TabArrowVanish( wk, 0 );
	}

	px = PST_TabPosXGet( wk );

	CATS_ObjectPosSet( wk->awp[PST_OBJ_ARROW_L], px+TAB_L_ARROW_PSX, TAB_ARROW_PY );
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_ARROW_R], TAB_CENTER_PX+(TAB_CENTER_PX-px)+TAB_R_ARROW_PSX, TAB_ARROW_PY );
}

void PokeStatus_TabArrowVanish( PST_WORK * wk, u8 flg )
{
	if( PokeStatus_PageNumGet( wk ) <= 1 ){
		flg = 0;
	}
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_ARROW_L], flg );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_ARROW_R], flg );
}


void PokeStatusBallAnmChg( PST_WORK * wk )
{
	u32	chr;

	if( wk->pp.ball == 0 ){
		chr = NARC_pst_gra_ball00_NCGR;
	}else{
		chr = NARC_pst_gra_ball00_NCGR + wk->pp.ball - 1;
	}

	CATS_ChangeResourceCharArc( wk->csp, wk->crp, ARC_PSTATUS_GRA, chr, 0, PST_CHR_ID_BALL );

	CATS_ChangeResourcePlttArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA,
		NARC_pst_gra_ball00_NCLR+BallPalTbl[wk->pp.ball], 0, 6 );
}

void PokeStatus_StIconChg( PST_WORK * wk )
{
	if( wk->pp.st == ST_ICON_NONE ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_STIZYO], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_POKERUS], 0 );
	}else if( wk->pp.st != ST_ICON_POKERUS ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_POKERUS], 0 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_STIZYO], 1 );
		CLACT_AnmChg( wk->awp[PST_OBJ_STIZYO], wk->pp.st );
	}else{
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_POKERUS], 1 );
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_STIZYO], 0 );
	}
}





//--------------------------------------------------------------------------------------------
/**
 * 技アイコンOBJセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------

static void InitObjCharPalChg( PST_WORK * wk )
{
	u16	i;

	// ポケモンの属性アイコン
	PokeStatus_PokeTypeChange( wk );
	// 技属性
	for( i=0; i<4; i++ ){
		if( wk->pp.waza[i] == 0 ){ continue; }
		PokeStatus_TypeIconChange(
			wk, PST_OBJ_TYPE_WAZA1+i, PST_CHR_ID_WAZATYPE1+i,
			WT_WazaDataParaGet(wk->pp.waza[i],ID_WTD_wazatype) );
	}
	// ポケモンアイコン
	PokeStasus_PokeIconChange( wk );
}



void PokeStatus_PageTypeIconDrow( PST_WORK * wk )
{
	u16	i;

	for( i=PST_OBJ_TYPE_POKE1; i<=PST_OBJ_POKEICON; i++ ){
		CATS_ObjectEnable( wk->awp[i], 0 );
	}

	switch( wk->page ){
	case PST_PAGE_INFO:
		CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE1], 1 );
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_POKE1], PT_ICON_P1_PX, PT_ICON_P1_PY );
		if( wk->pp.type1 != wk->pp.type2 ){
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_POKE2], 1 );
			CATS_ObjectPosSet(
				wk->awp[PST_OBJ_TYPE_POKE2], PT_ICON_P1_PX+34, PT_ICON_P1_PY );
		}
		break;

	case PST_PAGE_B_SKILL:
		for( i=0; i<4; i++ ){
			if( wk->pp.waza[i] == 0 ){ continue; }
			PokeStatus_TypeIconChange(
				wk, PST_OBJ_TYPE_WAZA1+i, PST_CHR_ID_WAZATYPE1+i,
				WT_WazaDataParaGet(wk->pp.waza[i],ID_WTD_wazatype) );
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_WAZA1+i], 1 );
			CATS_ObjectPosSet(
				wk->awp[PST_OBJ_TYPE_WAZA1+i], WT_ICON_P4_PX, WT_ICON_P4_PY+i*32 );
		}
		if( wk->dat->waza != 0 ){
			PokeStatus_TypeIconChange(
				wk, PST_OBJ_TYPE_WAZA1+4, PST_CHR_ID_WAZATYPE1+4,
				WT_WazaDataParaGet(wk->dat->waza,ID_WTD_wazatype) );
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_WAZA1+4], 1 );
			CATS_ObjectPosSet(
				wk->awp[PST_OBJ_TYPE_WAZA1+4], WT_ICON_P4_PX, WT_ICON_P4_PY+4*32 );
		}
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_POKE1], PT_ICON_P4_PX, PT_ICON_P4_PY );
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_POKE2], PT_ICON_P4_PX+34, PT_ICON_P4_PY );
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_KIND], KT_ICON_P4_PX, KT_ICON_P4_PY );
		break;

	case PST_PAGE_C_SKILL:
		for( i=0; i<4; i++ ){
			if( wk->pp.waza[i] == 0 ){ continue; }
			PokeStatus_TypeIconChange(
				wk, PST_OBJ_TYPE_WAZA1+i, PST_CHR_ID_WAZATYPE1+i,
				WT_WazaDataParaGet(wk->pp.waza[i],ID_WTD_contype)+ICONTYPE_STYLE );
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_WAZA1+i], 1 );
			CATS_ObjectPosSet(
				wk->awp[PST_OBJ_TYPE_WAZA1+i], WT_ICON_P4_PX, WT_ICON_P4_PY+i*32 );
		}
		if( wk->dat->waza != 0 ){
			PokeStatus_TypeIconChange(
				wk, PST_OBJ_TYPE_WAZA1+4, PST_CHR_ID_WAZATYPE1+4,
				WT_WazaDataParaGet(wk->dat->waza,ID_WTD_contype)+ICONTYPE_STYLE );
			CATS_ObjectEnable( wk->awp[PST_OBJ_TYPE_WAZA1+4], 1 );
			CATS_ObjectPosSet(
				wk->awp[PST_OBJ_TYPE_WAZA1+4], WT_ICON_P4_PX, WT_ICON_P4_PY+4*32 );
		}
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_POKE1], PT_ICON_P4_PX, PT_ICON_P4_PY );
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_POKE2], PT_ICON_P4_PX+34, PT_ICON_P4_PY );
		CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_KIND], KT_ICON_P4_PX, KT_ICON_P4_PY );
		break;
	}
}

void PokeStatus_PokeTypeChange( PST_WORK * wk )
{
	PokeStatus_TypeIconChange( wk, PST_OBJ_TYPE_POKE1, PST_CHR_ID_POKETYPE1, wk->pp.type1 );
	PokeStatus_TypeIconChange( wk, PST_OBJ_TYPE_POKE2, PST_CHR_ID_POKETYPE2, wk->pp.type2 );
}

static void PokeStatus_TypeIconChange( PST_WORK * wk, u8 act_num, u8 res_id, u8 type )
{
	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaTypeIcon_ArcIDGet(),
		WazaTypeIcon_CgrIDGet(type), WAZATYPEICON_COMP_CHAR, res_id );

	CATS_ObjectPaletteSet( wk->awp[act_num], WazaTypeIcon_PlttOffsetGet(type)+3 );

}


static void WazaTypeChgPosGet( PST_WORK * wk, u8 * pos, s16 * x, s16 * y )
{
	s16	i, py;

	py = WT_ICON_P4_PY+*pos*32;

	for( i=0; i<4; i++ ){
		CATS_ObjectPosGet( wk->awp[PST_OBJ_TYPE_WAZA1+i], x, y );
		if( py == *y ){
			*pos = (u8)i;
			break;
		}
	}
}

void PokeStatus_WazaTypePosChange( PST_WORK * wk, u8 pos1, u8 pos2 )
{
	s16	x1, y1, x2, y2;

	WazaTypeChgPosGet( wk, &pos1, &x1, &y1 );
	WazaTypeChgPosGet( wk, &pos2, &x2, &y2 );

	CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_WAZA1+pos1], x2, y2 );
	CATS_ObjectPosSet( wk->awp[PST_OBJ_TYPE_WAZA1+pos2], x1, y1 );
}

void PokeStatus_KindIconChange( PST_WORK * wk, u32 waza )
{
	u32	kind = WT_WazaDataParaGet( waza, ID_WTD_kind );

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaKindIcon_ArcIDGet(),
		WazaKindIcon_CgrIDGet(kind), WAZAKINDICON_COMP_CHAR, PST_CHR_ID_WAZAKIND );

	CATS_ObjectPaletteSet( wk->awp[PST_OBJ_TYPE_KIND], WazaKindIcon_PlttOffsetGet(kind)+3 );
}



//--------------------------------------------------------------------------------------------
/**
 * 技カーソル移動
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_WazaCursorMove( PST_WORK * wk )
{
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_WAZACURSOR1], WAZACURSOR_PX, WAZACURSOR_PY + wk->cur_pos*32 );
}

void PokeStatus_SubWazaCursorSet( PST_WORK * wk )
{
	s16	x, y;

	CATS_ObjectPosGet( wk->awp[PST_OBJ_WAZACURSOR1], &x, &y );
	CATS_ObjectPosSet( wk->awp[PST_OBJ_WAZACURSOR2], x, y );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_WAZACURSOR2], 1 );
}



void PokeStatus_KezuyaInit( PST_WORK * wk )
{
	u32	i;

	wk->flash_seq = 0;
	wk->flash_cnt = 0;
	wk->flash_pos = 0;

	if( wk->pp.fur == 0 ){
		wk->flash_max = 0;
	}else if( wk->pp.fur == PST_KEDUYA_MAX ){
		wk->flash_max = KEDUYA_ANM_MAX;
	}else{
//		wk->flash_max = wk->pp.fur/(((PST_KEDUYA_MAX<<8)/12)>>8);
		wk->flash_max = (((KEDUYA_ANM_MAX<<8)/PST_KEDUYA_MAX)*wk->pp.fur)>>8;
	}

//	wk->flash_max = KEDUYA_ANM_MAX;

	for( i=PST_OBJ_FLASH1; i<=PST_OBJ_FLASH12; i++ ){
		CLACT_SetDrawFlag( wk->awp[i], 0 );
		CLACT_AnmFrameSet( wk->awp[i], 0 );
	}
}

void PokeStatus_KezuyaAnm( PST_WORK * wk )
{
	u32	i;

	if( wk->page != PST_PAGE_CONDITION ){
		return;
	}

	if( wk->flash_max == 0 ){ return; }

	switch( wk->flash_seq ){
	case 0:
		wk->flash_cnt++;
		if( wk->flash_cnt == 8 ){
			wk->flash_seq = 1;
			wk->flash_cnt = 0;
			wk->flash_pos = 0;
		}
		break;

	case 1:
		if( wk->flash_cnt == 0 ){
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_FLASH1+wk->flash_pos], 1 );
			CLACT_AnmFrameSet( wk->awp[PST_OBJ_FLASH1+wk->flash_pos], 0 );
			CLACT_AnmChg( wk->awp[PST_OBJ_FLASH1+wk->flash_pos], 0 );
			wk->flash_pos++;
			if( wk->flash_pos == wk->flash_max ){
				wk->flash_seq = 2;
				break;
			}
		}
//		wk->flash_cnt = (wk->flash_cnt+1) & 7;
		wk->flash_cnt = (wk->flash_cnt+1) % 10;
		break;

	case 2:
		if( CLACT_GetDrawFlag( wk->awp[PST_OBJ_FLASH1+wk->flash_max-1] ) == 0 ){
//		if( CLACT_AnmFrameGet( wk->awp[wk->flash_max-1] ) == 5 ){
			wk->flash_cnt = 0;
			wk->flash_seq = 3;
			break;
		}
		break;

	case 3:
		wk->flash_cnt++;
		if( wk->flash_cnt == 32 ){
			for( i=PST_OBJ_FLASH1; i<PST_OBJ_FLASH1+wk->flash_max; i++ ){
				CLACT_SetDrawFlag( wk->awp[i], 1 );
				CLACT_AnmFrameSet( wk->awp[i], 0 );
				CLACT_AnmChg( wk->awp[i], 0 );
			}
			wk->flash_cnt = 0;
			wk->flash_seq = 4;
		}
		break;

	case 4:
		wk->flash_cnt++;
		if( wk->flash_cnt == 32 ){
			wk->flash_seq = 0;
			wk->flash_cnt = 0;
			wk->flash_pos = 0;
		}
		break;
	}

	for( i=PST_OBJ_FLASH1; i<PST_OBJ_FLASH1+wk->flash_max; i++ ){
		if( CLACT_GetDrawFlag( wk->awp[i] ) == 0 ){ continue; }
		CLACT_AnmFrameChg( wk->awp[i], FX32_ONE );

		if( CLACT_AnmFrameGet( wk->awp[i] ) == 6 ){
			CLACT_SetDrawFlag( wk->awp[i], 0 );
		}
	}
}


void PokeStatus_MarkChg( PST_WORK * wk )
{
	u32	i;

	// ボックスマーク
	for( i=0; i<6; i++ ){
		if( wk->pp.mark & (1<<i) ){
			CLACT_AnmChg( wk->awp[PST_OBJ_MARK1+i], 1 );
		}else{
			CLACT_AnmChg( wk->awp[PST_OBJ_MARK1+i], 0 );
		}
	}

	// レアカラー
	if( wk->pp.rare == 1 && wk->pp.tamago == 0 ){
		CATS_ObjectEnable( wk->awp[PST_OBJ_RARE_MARK], 1 );
	}else{
		CATS_ObjectEnable( wk->awp[PST_OBJ_RARE_MARK], 0 );
	}

	// ポケルス
	if( wk->pp.pokerus == 2 ){
		CATS_ObjectEnable( wk->awp[PST_OBJ_POKERUS_MARK], 1 );
	}else{
		CATS_ObjectEnable( wk->awp[PST_OBJ_POKERUS_MARK], 0 );
	}
}



void PokeStatus_ButtonEffInit( PST_WORK * wk )
{
	s16	x, y;

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_BUTTON_EF], 1 );
	CLACT_AnmFrameSet( wk->awp[PST_OBJ_BUTTON_EF], 0 );
	CLACT_AnmChg( wk->awp[PST_OBJ_BUTTON_EF], 0 );

	PokeStatus_ButtonPosGet( wk, &x, &y );
	if( wk->sub_type == 0 ){
		CATS_ObjectPosSet( wk->awp[PST_OBJ_BUTTON_EF], x, y+192 );
	}else{
		CATS_ObjectPosSet( wk->awp[PST_OBJ_BUTTON_EF], x-4, y+192 );
	}
}

void PokeStatus_ButtonEffEnd( PST_WORK * wk )
{
	if( CLACT_AnmFrameGet( wk->awp[PST_OBJ_BUTTON_EF] ) == 2 ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_BUTTON_EF], 0 );
	}
}



void PokeStatus_CondUpObjPut( PST_WORK * wk )
{
	u8	i;

	for( i=0; i<5; i++ ){
		if( ( wk->sub_seq & (1<<i) ) ){
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_UP1+i], 1 );
		}
	}
}


//============================================================================================
//	Aボタンマーク
//============================================================================================

void PokeStatus_A_ButtonMarkPut( PST_WORK * wk, GF_BGL_BMPWIN * win )
{
	if( win == NULL ){
		CLACT_SetDrawFlag( wk->awp[PST_OBJ_A_BUTTON], 0 );
		return;
	}

	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_A_BUTTON], GF_BGL_BmpWinGet_PosX(win)*8-10, A_BUTTON_PY );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_A_BUTTON], 1 );
}



//============================================================================================
//	ポケモンアイコン
//============================================================================================

void PokeStasus_PokeIconChange( PST_WORK * wk )
{
	void * pp = PokeStatusPokeParamGet( wk );
	u32	cgx_arc;

	if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
		cgx_arc = PokeIconCgxArcIndexGet( pp );
	}else{
		cgx_arc = PokeIconCgxArcIndexGetByPP( pp );
	}

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, ARC_POKEICON, cgx_arc, 0, PST_CHR_ID_POKEICON );

	CATS_ObjectPaletteSet(
		wk->awp[PST_OBJ_POKEICON],
		PokeIconPalNumGet(wk->pp.mons,wk->pp.form,wk->pp.tamago)+PST_POKEICON_PAL );

	CLACT_SetFlip(
		wk->awp[PST_OBJ_POKEICON],
		(PokePersonalParaGet( wk->pp.mons, ID_PER_reverse )^1) );
}

void PokeStatus_PokeIconSet( PST_WORK * wk )
{
	CATS_ChangeResourcePlttArc(
		wk->csp, wk->crp, ARC_POKEICON, PokeIconPalArcIndexGet(), 0, 5 );

	if( wk->page == PST_PAGE_B_SKILL ){
		CATS_ObjectPosSet( wk->awp[PST_OBJ_POKEICON], POKE_ICON_PX, POKE_ICON_PY );
	}else{
		CATS_ObjectPosSet( wk->awp[PST_OBJ_POKEICON], CON_POKE_ICON_PX, CON_POKE_ICON_PY );
	}
	CATS_ObjectEnable( wk->awp[PST_OBJ_POKEICON], 1 );
}



//============================================================================================
//	簡易コンディション
//============================================================================================
#define	EZCON1_MIN_X	( 88 )
#define	EZCON1_MAX_X	( 88 )
#define	EZCON1_MIN_Y	( 73 )
#define	EZCON1_MAX_Y	( 49 )

#define	EZCON2_MIN_X	( 88 )
#define	EZCON2_MAX_X	( 110 )
#define	EZCON2_MIN_Y	( 73 )
#define	EZCON2_MAX_Y	( 65 )

#define	EZCON3_MIN_X	( 88 )
#define	EZCON3_MAX_X	( 103 )
#define	EZCON3_MIN_Y	( 73 )
#define	EZCON3_MAX_Y	( 92 )

#define	EZCON4_MIN_X	( 87 )
#define	EZCON4_MAX_X	( 72 )
#define	EZCON4_MIN_Y	( 73 )
#define	EZCON4_MAX_Y	( 92 )

#define	EZCON5_MIN_X	( 87 )
#define	EZCON5_MAX_X	( 65 )
#define	EZCON5_MIN_Y	( 73 )
#define	EZCON5_MAX_Y	( 65 )

#define	EZCND_MAX_RPM	( 300 )
#define	EZCND_DEF_RPM	( 44 )		// 300 = 256 + EZCND_DEF_RPM

/*
#define	EZCON_PX	( 88 )
#define	EZCON_PY	( 72 )
*/

static s16 PST_EzCndPosGet( u32 prm, s16 max, s16 min )
{
	u32	dot;

	prm += EZCND_DEF_RPM;

	if( min > max ){
		dot = ( ( min - max ) * prm ) << 16;
		dot = ( dot / EZCND_MAX_RPM ) >> 16;
		return min + (s16)dot * -1;
	}
	
	dot = ( ( max - min ) * prm ) << 16;
	dot = ( dot / EZCND_MAX_RPM ) >> 16;
	return min + (s16)dot;
}


void PokeStatus_EzConditionPut( PST_WORK * wk )
{
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_EZC_STYLE],
		PST_EzCndPosGet( wk->pp.style, EZCON1_MAX_X, EZCON1_MIN_X ),
		PST_EzCndPosGet( wk->pp.style, EZCON1_MAX_Y, EZCON1_MIN_Y ) );
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_EZC_BEAUTIFUL],
		PST_EzCndPosGet( wk->pp.beautiful, EZCON2_MAX_X, EZCON2_MIN_X ),
		PST_EzCndPosGet( wk->pp.beautiful, EZCON2_MAX_Y, EZCON2_MIN_Y ) );
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_EZC_CUTE],
		PST_EzCndPosGet( wk->pp.cute, EZCON3_MAX_X, EZCON3_MIN_X ),
		PST_EzCndPosGet( wk->pp.cute, EZCON3_MAX_Y, EZCON3_MIN_Y ) );
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_EZC_CLEVER],
		PST_EzCndPosGet( wk->pp.clever, EZCON4_MAX_X, EZCON4_MIN_X ),
		PST_EzCndPosGet( wk->pp.clever, EZCON4_MAX_Y, EZCON4_MIN_Y ) );
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_EZC_STRONG],
		PST_EzCndPosGet( wk->pp.strong, EZCON5_MAX_X, EZCON5_MIN_X ),
		PST_EzCndPosGet( wk->pp.strong, EZCON5_MAX_Y, EZCON5_MIN_Y ) );

	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STYLE], 1 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_BEAUTIFUL], 1 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CUTE], 1 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CLEVER], 1 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STRONG], 1 );
}

void PokeStatus_EzConditionOff( PST_WORK * wk )
{
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STYLE], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_BEAUTIFUL], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CUTE], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_CLEVER], 0 );
	CLACT_SetDrawFlag( wk->awp[PST_OBJ_EZC_STRONG], 0 );
}



//============================================================================================
//	リボン
//============================================================================================

static void PST_RibbonGraSet( PST_WORK * wk, u8 id, u8 pos )
{
	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA,
		RIBBON_DataGet(id,RIBBON_PARA_GRAPHIC), 0, PST_CHR_ID_RIBBON01+pos );

	CATS_ObjectPaletteSet(
		wk->awp[PST_OBJ_RIBBON01+pos],
		RIBBON_DataGet(id,RIBBON_PARA_PALNUM)+PST_RIBBON_PAL );
}

void PokeStatus_RibbonInit( PST_WORK * wk )
{
	u16	i;

	for( i=PST_OBJ_RIBBON01; i<=PST_OBJ_RIBBON_FLASH; i++ ){
		CLACT_SetDrawFlag( wk->awp[i], 0 );
	}

	if( wk->page != PST_PAGE_RIBBON ){ return; }

	CATS_ChangeResourcePlttArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA, NARC_pst_gra_ribon_NCLR, 0, 5 );

	for( i=0; i<12; i++ ){
		if( i < wk->ribbon_max ){
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON01+i], 1 );
			PST_RibbonGraSet( wk, PokeStatus_RibbonPosIDGet(wk,i), i );
		}
	}
	CLACT_AnmChg( wk->awp[PST_OBJ_RIBBON_FLASH], 0 );
}

void PokeStatus_RibbonChange( PST_WORK * wk )
{
	u16	i;

	for( i=0; i<8; i++ ){
		if( ( wk->ribbon_scr*4+i ) < wk->ribbon_max ){
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON01+i], 1 );
			PST_RibbonGraSet( wk, PokeStatus_RibbonPosIDGet(wk,i), i );
		}else{
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_RIBBON01+i], 0 );
		}
	}
}


void PokeStatus_RibbonCursorMove( PST_WORK * wk )
{
	CATS_ObjectPosSet(
		wk->awp[PST_OBJ_RIBBON_CUR],
		RIBON_PX1 + ( wk->ribbon_pos & 3 ) * RIBBON_MX,
		RIBON_PY1 + ( wk->ribbon_pos / 4 ) * RIBBON_MY );
}

void PokeStatus_RibbonFlashAnm( PST_WORK * wk )
{
	if( CLACT_GetDrawFlag( wk->awp[PST_OBJ_RIBBON_FLASH] ) == 1 ){
		CLACT_AnmFrameChg( wk->awp[PST_OBJ_RIBBON_FLASH], FX32_ONE );
	}
}


//============================================================================================
//	コンディションの光
//============================================================================================
#define	CONFLASH_CX		( 180 )
#define	CONFLASH_CY		( 94 )
#define	CONFLASH_X1_MAX	( 180 )
#define	CONFLASH_Y1_MAX	( 57 )
#define	CONFLASH_X1_MIN	( CONFLASH_CX + (CONFLASH_X1_MAX-CONFLASH_CX)/8 )
#define	CONFLASH_Y1_MIN	( CONFLASH_CY + (CONFLASH_Y1_MAX-CONFLASH_CY)/8 )
#define	CONFLASH_X2_MAX	( 213 )
#define	CONFLASH_Y2_MAX	( 85 )
#define	CONFLASH_X2_MIN	( CONFLASH_CX + (CONFLASH_X2_MAX-CONFLASH_CX)/8 )
#define	CONFLASH_Y2_MIN	( CONFLASH_CY + (CONFLASH_Y2_MAX-CONFLASH_CY)/8 )
#define	CONFLASH_X3_MAX	( 200 )
#define	CONFLASH_Y3_MAX	( 125 )
#define	CONFLASH_X3_MIN	( CONFLASH_CX + (CONFLASH_X3_MAX-CONFLASH_CX)/8 )
#define	CONFLASH_Y3_MIN	( CONFLASH_CY + (CONFLASH_Y3_MAX-CONFLASH_CY)/8 )
#define	CONFLASH_X4_MAX	( 159 )
#define	CONFLASH_Y4_MAX	( 125 )
#define	CONFLASH_X4_MIN	( CONFLASH_CX + (CONFLASH_X4_MAX-CONFLASH_CX)/8 )
#define	CONFLASH_Y4_MIN	( CONFLASH_CY + (CONFLASH_Y4_MAX-CONFLASH_CY)/8 )
#define	CONFLASH_X5_MAX	( 146 )
#define	CONFLASH_Y5_MAX	( 85 )
#define	CONFLASH_X5_MIN	( CONFLASH_CX + (CONFLASH_X5_MAX-CONFLASH_CX)/8 )
#define	CONFLASH_Y5_MIN	( CONFLASH_CY + (CONFLASH_Y5_MAX-CONFLASH_CY)/8 )

enum {
	CONFLASH_MAX_X = 0,
	CONFLASH_MAX_Y,
	CONFLASH_MIN_X,
	CONFLASH_MIN_Y,
};

static const s16 ConFlashPosTbl[][4] =
{	// x_max, y_max, x_min, y_min
	{ CONFLASH_X1_MAX, CONFLASH_Y1_MAX, CONFLASH_X1_MIN, CONFLASH_Y1_MIN },
	{ CONFLASH_X2_MAX, CONFLASH_Y2_MAX, CONFLASH_X2_MIN, CONFLASH_Y2_MIN },
	{ CONFLASH_X3_MAX, CONFLASH_Y3_MAX, CONFLASH_X3_MIN, CONFLASH_Y3_MIN },
	{ CONFLASH_X4_MAX, CONFLASH_Y4_MAX, CONFLASH_X4_MIN, CONFLASH_Y4_MIN },
	{ CONFLASH_X5_MAX, CONFLASH_Y5_MAX, CONFLASH_X5_MIN, CONFLASH_Y5_MIN }
};

static void PST_ConditionFlashPut( CLACT_WORK_PTR awp, u32 prm, u32 max, const s16 * pos );


void PokeStatus_ConditionFlash( PST_WORK * wk, u8 flg )
{
	u16	i, max;

	if( flg == 0 ){
		for( i=0; i<5; i++ ){
			CLACT_SetDrawFlag( wk->awp[PST_OBJ_CON_FLASH1+i], 0 );
		}
	}else{
		max = wk->pp.style;
		if( max < wk->pp.beautiful ){
			max = wk->pp.beautiful;
		}
		if( max < wk->pp.cute ){
			max = wk->pp.cute;
		}
		if( max < wk->pp.clever ){
			max = wk->pp.clever;
		}
		if( max < wk->pp.strong ){
			max = wk->pp.strong;
		}

		PST_ConditionFlashPut( wk->awp[PST_OBJ_CON_FLASH1], wk->pp.style, max, ConFlashPosTbl[0] );
		PST_ConditionFlashPut( wk->awp[PST_OBJ_CON_FLASH2], wk->pp.beautiful, max, ConFlashPosTbl[1] );
		PST_ConditionFlashPut( wk->awp[PST_OBJ_CON_FLASH3], wk->pp.cute, max, ConFlashPosTbl[2] );
		PST_ConditionFlashPut( wk->awp[PST_OBJ_CON_FLASH4], wk->pp.clever, max, ConFlashPosTbl[3] );
		PST_ConditionFlashPut( wk->awp[PST_OBJ_CON_FLASH5], wk->pp.strong, max, ConFlashPosTbl[4] );
	}
}

static void PST_ConditionFlashPut( CLACT_WORK_PTR awp, u32 prm, u32 max, const s16 * pos )
{
	s32	px, py;

	if( prm == 0 || prm != max ){
		CLACT_SetDrawFlag( awp, 0 );
		return;
	}

	CLACT_SetDrawFlag( awp, 1 );

	if( pos[CONFLASH_MAX_X] >= pos[CONFLASH_MIN_X] ){
		px = pos[CONFLASH_MIN_X]+(((((pos[CONFLASH_MAX_X]-pos[CONFLASH_MIN_X])<<8)/256)*prm)>>8);
	}else{
		px = pos[CONFLASH_MIN_X]-(((((pos[CONFLASH_MIN_X]-pos[CONFLASH_MAX_X])<<8)/256)*prm)>>8);
	}
	if( pos[CONFLASH_MAX_Y] >= pos[CONFLASH_MIN_Y] ){
		py = pos[CONFLASH_MIN_Y]+(((((pos[CONFLASH_MAX_Y]-pos[CONFLASH_MIN_Y])<<8)/256)*prm)>>8);
	}else{
		py = pos[CONFLASH_MIN_Y]-(((((pos[CONFLASH_MIN_Y]-pos[CONFLASH_MAX_Y])<<8)/256)*prm)>>8);
	}

	CATS_ObjectPosSet( awp, px, py );
	CLACT_AnmFrameSet( awp, 0 );
	CLACT_AnmChg( awp, 0 );
}

void PokeStatus_ConditionFlashAnm( PST_WORK * wk )
{
	u32	i;

	for( i=0; i<5; i++ ){
		CLACT_AnmFrameChg( wk->awp[PST_OBJ_CON_FLASH1+i], FX32_ONE );
	}
}
