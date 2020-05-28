//============================================================================================
/**
 * @file	plist_bmp.c
 * @brief	ポケモンリスト画面BMP関連
 * @author	Hiroyuki Nakamura
 * @date	05.09.29
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/pmfprint.h"
//#include "system/arc_tool.h"
//#include "system/arc_util.h"
#include "system/clact_tool.h"
//#include "system/brightness.h"
#include "system/buflen.h"
#include "system/snd_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokelist.h"
#include "poketool/monsno.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_regulation.h"
#include "application/app_tool.h"
#include "battle/battle_common.h"

#define	PLIST_BMP_H_GLOBAL
#include "application/pokelist.h"
#include "plist_sys.h"
#include "plist_bmp.h"
#include "plist_obj.h"
#include "plist_menu.h"
#include "plist_item.h"


//============================================================================================
//	定数定義
//============================================================================================
// BMPウィンドウ定義
// ニックネーム：１体目
#define	WIN_NAME1_PX	( 6 )
#define	WIN_NAME1_PY	( 1 )
#define	WIN_NAME1_SX	( 9 )
#define	WIN_NAME1_SY	( 2 )
#define	WIN_NAME1_PAL	( PAL_FONT )
#define	WIN_NAME1_CGX	( PL_TALK_WIN_CGX + TALK_WIN_CGX_SIZ )
// レベル：１体目
#define	WIN_LV1_PX		( 0 )
#define	WIN_LV1_PY		( 4 )
#define	WIN_LV1_SX		( 6 )
#define	WIN_LV1_SY		( 2 )
#define	WIN_LV1_PAL		( PAL_FONT )
#define	WIN_LV1_CGX		( WIN_NAME1_CGX + WIN_NAME1_SX * WIN_NAME1_SY )
// HP/MHP：１体目
#define	WIN_HP1_PX		( 7 )
#define	WIN_HP1_PY		( 4 )
#define	WIN_HP1_SX		( 8 )
#define	WIN_HP1_SY		( 2 )
#define	WIN_HP1_PAL		( PAL_FONT )
#define	WIN_HP1_CGX		( WIN_LV1_CGX + WIN_LV1_SX * WIN_LV1_SY )
// HPゲージ：１体目
#define	WIN_HPBAR1_PX	( 8 )
#define	WIN_HPBAR1_PY	( 3 )
#define	WIN_HPBAR1_SX	( 6 )
#define	WIN_HPBAR1_SY	( 1 )
#define	WIN_HPBAR1_PAL	( PAL_PANEL_0 )
#define	WIN_HPBAR1_CGX	( WIN_HP1_CGX + WIN_HP1_SX * WIN_HP1_SY )
// コメント：１体目
#define	WIN_COMM1_PX	( 6 )
#define	WIN_COMM1_PY	( 4 )
#define	WIN_COMM1_SX	( 10 )
#define	WIN_COMM1_SY	( 2 )
#define	WIN_COMM1_PAL	( PAL_FONT )
#define	WIN_COMM1_CGX	( WIN_LV1_CGX + WIN_LV1_SX * WIN_LV1_SY )

// ニックネーム：２体目（通常）
#define	WIN_NAME2_PX	( 22 )
#define	WIN_NAME2_PY	( 2 )
#define	WIN_NAME2_SX	( 9 )
#define	WIN_NAME2_SY	( 2 )
#define	WIN_NAME2_PAL	( PAL_FONT )
#define	WIN_NAME2_CGX	( WIN_HPBAR1_CGX + WIN_HPBAR1_SX * WIN_HPBAR1_SY )
// レベル：２体目（通常）
#define	WIN_LV2_PX		( 16 )
#define	WIN_LV2_PY		( 5 )
#define	WIN_LV2_SX		( 6 )
#define	WIN_LV2_SY		( 2 )
#define	WIN_LV2_PAL		( PAL_FONT )
#define	WIN_LV2_CGX		( WIN_NAME2_CGX + WIN_NAME2_SX * WIN_NAME2_SY )
// HP/MHP：２体目（通常）
#define	WIN_HP2_PX		( 23 )
#define	WIN_HP2_PY		( 5 )
#define	WIN_HP2_SX		( 8 )
#define	WIN_HP2_SY		( 2 )
#define	WIN_HP2_PAL		( PAL_FONT )
#define	WIN_HP2_CGX		( WIN_LV2_CGX + WIN_LV2_SX * WIN_LV2_SY )
// HPゲージ：２体目（通常）
#define	WIN_HPBAR2_PX	( 24 )
#define	WIN_HPBAR2_PY	( 4 )
#define	WIN_HPBAR2_SX	( 6 )
#define	WIN_HPBAR2_SY	( 1 )
#define	WIN_HPBAR2_PAL	( PAL_PANEL_1 )
#define	WIN_HPBAR2_CGX	( WIN_HP2_CGX + WIN_HP2_SX * WIN_HP2_SY )
// コメント：２体目
#define	WIN_COMM2_PX	( 22 )
#define	WIN_COMM2_PY	( 5 )
#define	WIN_COMM2_SX	( 10 )
#define	WIN_COMM2_SY	( 2 )
#define	WIN_COMM2_PAL	( PAL_FONT )
#define	WIN_COMM2_CGX	( WIN_LV2_CGX + WIN_LV2_SX * WIN_LV2_SY )

// ニックネーム：３体目
#define	WIN_NAME3_PX	( 6 )
#define	WIN_NAME3_PY	( 7 )
#define	WIN_NAME3_SX	( 9 )
#define	WIN_NAME3_SY	( 2 )
#define	WIN_NAME3_PAL	( PAL_FONT )
#define	WIN_NAME3_CGX	( WIN_HPBAR2_CGX + WIN_HPBAR2_SX * WIN_HPBAR2_SY )
// レベル：３体目
#define	WIN_LV3_PX		( 0 )
#define	WIN_LV3_PY		( 10 )
#define	WIN_LV3_SX		( 6 )
#define	WIN_LV3_SY		( 2 )
#define	WIN_LV3_PAL		( PAL_FONT )
#define	WIN_LV3_CGX		( WIN_NAME3_CGX + WIN_NAME3_SX * WIN_NAME3_SY )
// HP/MHP：３体目
#define	WIN_HP3_PX		( 7 )
#define	WIN_HP3_PY		( 10 )
#define	WIN_HP3_SX		( 8 )
#define	WIN_HP3_SY		( 2 )
#define	WIN_HP3_PAL		( PAL_FONT )
#define	WIN_HP3_CGX		( WIN_LV3_CGX + WIN_LV3_SX * WIN_LV3_SY )
// HPゲージ：３体目
#define	WIN_HPBAR3_PX	( 8 )
#define	WIN_HPBAR3_PY	( 9 )
#define	WIN_HPBAR3_SX	( 6 )
#define	WIN_HPBAR3_SY	( 1 )
#define	WIN_HPBAR3_PAL	( PAL_PANEL_2 )
#define	WIN_HPBAR3_CGX	( WIN_HP3_CGX + WIN_HP3_SX * WIN_HP3_SY )
// コメント：３体目
#define	WIN_COMM3_PX	( 6 )
#define	WIN_COMM3_PY	( 10 )
#define	WIN_COMM3_SX	( 10 )
#define	WIN_COMM3_SY	( 2 )
#define	WIN_COMM3_PAL	( PAL_FONT )
#define	WIN_COMM3_CGX	( WIN_LV3_CGX + WIN_LV3_SX * WIN_LV3_SY )

// ニックネーム：４体目（通常）
#define	WIN_NAME4_PX	( 22 )
#define	WIN_NAME4_PY	( 8 )
#define	WIN_NAME4_SX	( 9 )
#define	WIN_NAME4_SY	( 2 )
#define	WIN_NAME4_PAL	( PAL_FONT )
#define	WIN_NAME4_CGX	( WIN_HPBAR3_CGX + WIN_HPBAR3_SX * WIN_HPBAR3_SY )
// レベル：４体目（通常）
#define	WIN_LV4_PX		( 16 )
#define	WIN_LV4_PY		( 11 )
#define	WIN_LV4_SX		( 6 )
#define	WIN_LV4_SY		( 2 )
#define	WIN_LV4_PAL		( PAL_FONT )
#define	WIN_LV4_CGX		( WIN_NAME4_CGX + WIN_NAME4_SX * WIN_NAME4_SY )
// HP/MHP：４体目（通常）
#define	WIN_HP4_PX		( 23 )
#define	WIN_HP4_PY		( 11 )
#define	WIN_HP4_SX		( 8 )
#define	WIN_HP4_SY		( 2 )
#define	WIN_HP4_PAL		( PAL_FONT )
#define	WIN_HP4_CGX		( WIN_LV4_CGX + WIN_LV4_SX * WIN_LV4_SY )
// HPゲージ：４体目（通常）
#define	WIN_HPBAR4_PX	( 24 )
#define	WIN_HPBAR4_PY	( 10 )
#define	WIN_HPBAR4_SX	( 6 )
#define	WIN_HPBAR4_SY	( 1 )
#define	WIN_HPBAR4_PAL	( PAL_PANEL_3 )
#define	WIN_HPBAR4_CGX	( WIN_HP4_CGX + WIN_HP4_SX * WIN_HP4_SY )
// コメント：４体目
#define	WIN_COMM4_PX	( 22 )
#define	WIN_COMM4_PY	( 11 )
#define	WIN_COMM4_SX	( 10 )
#define	WIN_COMM4_SY	( 2 )
#define	WIN_COMM4_PAL	( PAL_FONT )
#define	WIN_COMM4_CGX	( WIN_LV4_CGX + WIN_LV4_SX * WIN_LV4_SY )

// ニックネーム：５体目
#define	WIN_NAME5_PX	( 6 )
#define	WIN_NAME5_PY	( 13 )
#define	WIN_NAME5_SX	( 9 )
#define	WIN_NAME5_SY	( 2 )
#define	WIN_NAME5_PAL	( PAL_FONT )
#define	WIN_NAME5_CGX	( WIN_HPBAR4_CGX + WIN_HPBAR4_SX * WIN_HPBAR4_SY )
// レベル：５体目
#define	WIN_LV5_PX		( 0 )
#define	WIN_LV5_PY		( 16 )
#define	WIN_LV5_SX		( 6 )
#define	WIN_LV5_SY		( 2 )
#define	WIN_LV5_PAL		( PAL_FONT )
#define	WIN_LV5_CGX		( WIN_NAME5_CGX + WIN_NAME5_SX * WIN_NAME5_SY )
// HP/MHP：５体目
#define	WIN_HP5_PX		( 7 )
#define	WIN_HP5_PY		( 16 )
#define	WIN_HP5_SX		( 8 )
#define	WIN_HP5_SY		( 2 )
#define	WIN_HP5_PAL		( PAL_FONT )
#define	WIN_HP5_CGX		( WIN_LV5_CGX + WIN_LV5_SX * WIN_LV5_SY )
// HPゲージ：５体目
#define	WIN_HPBAR5_PX	( 8 )
#define	WIN_HPBAR5_PY	( 15 )
#define	WIN_HPBAR5_SX	( 6 )
#define	WIN_HPBAR5_SY	( 1 )
#define	WIN_HPBAR5_PAL	( PAL_PANEL_4 )
#define	WIN_HPBAR5_CGX	( WIN_HP5_CGX + WIN_HP5_SX * WIN_HP5_SY )
// コメント：５体目
#define	WIN_COMM5_PX	( 6 )
#define	WIN_COMM5_PY	( 16 )
#define	WIN_COMM5_SX	( 10 )
#define	WIN_COMM5_SY	( 2 )
#define	WIN_COMM5_PAL	( PAL_FONT )
#define	WIN_COMM5_CGX	( WIN_LV5_CGX + WIN_LV5_SX * WIN_LV5_SY )

// ニックネーム：６体目（通常）
#define	WIN_NAME6_PX	( 22 )
#define	WIN_NAME6_PY	( 14 )
#define	WIN_NAME6_SX	( 9 )
#define	WIN_NAME6_SY	( 2 )
#define	WIN_NAME6_PAL	( PAL_FONT )
#define	WIN_NAME6_CGX	( WIN_HPBAR5_CGX + WIN_HPBAR5_SX * WIN_HPBAR5_SY )
// レベル：６体目（通常）
#define	WIN_LV6_PX		( 16 )
#define	WIN_LV6_PY		( 17 )
#define	WIN_LV6_SX		( 6 )
#define	WIN_LV6_SY		( 2 )
#define	WIN_LV6_PAL		( PAL_FONT )
#define	WIN_LV6_CGX		( WIN_NAME6_CGX + WIN_NAME6_SX * WIN_NAME6_SY )
// HP/MHP：６体目（通常）
#define	WIN_HP6_PX		( 23 )
#define	WIN_HP6_PY		( 17 )
#define	WIN_HP6_SX		( 8 )
#define	WIN_HP6_SY		( 2 )
#define	WIN_HP6_PAL		( PAL_FONT )
#define	WIN_HP6_CGX		( WIN_LV6_CGX + WIN_LV6_SX * WIN_LV6_SY )
// HPゲージ：６体目（通常）
#define	WIN_HPBAR6_PX	( 24 )
#define	WIN_HPBAR6_PY	( 16 )
#define	WIN_HPBAR6_SX	( 6 )
#define	WIN_HPBAR6_SY	( 1 )
#define	WIN_HPBAR6_PAL	( PAL_PANEL_5 )
#define	WIN_HPBAR6_CGX	( WIN_HP6_CGX + WIN_HP6_SX * WIN_HP6_SY )
// コメント：６体目
#define	WIN_COMM6_PX	( 22 )
#define	WIN_COMM6_PY	( 17 )
#define	WIN_COMM6_SX	( 10 )
#define	WIN_COMM6_SY	( 2 )
#define	WIN_COMM6_PAL	( PAL_FONT )
#define	WIN_COMM6_CGX	( WIN_LV6_CGX + WIN_LV6_SX * WIN_LV6_SY )

// ニックネーム：２体目（マルチ）
#define	WIN_NAME2_MULTI_PX		( 22 )
#define	WIN_NAME2_MULTI_PY		( 1 )
#define	WIN_NAME2_MULTI_SX		( 9 )
#define	WIN_NAME2_MULTI_SY		( 2 )
#define	WIN_NAME2_MULTI_PAL		( PAL_FONT )
#define	WIN_NAME2_MULTI_CGX		( WIN_NAME2_CGX )
// レベル：２体目（マルチ）
#define	WIN_LV2_MULTI_PX		( 17 )
#define	WIN_LV2_MULTI_PY		( 5 )
#define	WIN_LV2_MULTI_SX		( 5 )
#define	WIN_LV2_MULTI_SY		( 2 )
#define	WIN_LV2_MULTI_PAL		( PAL_FONT )
#define	WIN_LV2_MULTI_CGX		( WIN_LV2_CGX )
// HP/MHP：２体目（マルチ）
#define	WIN_HP2_MULTI_PX		( 23 )
#define	WIN_HP2_MULTI_PY		( 5 )
#define	WIN_HP2_MULTI_SX		( 8 )
#define	WIN_HP2_MULTI_SY		( 2 )
#define	WIN_HP2_MULTI_PAL		( PAL_FONT )
#define	WIN_HP2_MULTI_CGX		( WIN_HP2_CGX )
// HPゲージ：２体目（マルチ）
#define	WIN_HPBAR2_MULTI_PX		( 24 )
#define	WIN_HPBAR2_MULTI_PY		( 4 )
#define	WIN_HPBAR2_MULTI_SX		( 6 )
#define	WIN_HPBAR2_MULTI_SY		( 1 )
#define	WIN_HPBAR2_MULTI_PAL	( PAL_PANEL_1 )
#define	WIN_HPBAR2_MULTI_CGX	( WIN_HPBAR2_CGX )

// ニックネーム：４体目（マルチ）
#define	WIN_NAME4_MULTI_PX		( 22 )
#define	WIN_NAME4_MULTI_PY		( 8 )
#define	WIN_NAME4_MULTI_SX		( 9 )
#define	WIN_NAME4_MULTI_SY		( 2 )
#define	WIN_NAME4_MULTI_PAL		( PAL_FONT )
#define	WIN_NAME4_MULTI_CGX		( WIN_NAME4_CGX )
// レベル：４体目（マルチ）
#define	WIN_LV4_MULTI_PX		( 17 )
#define	WIN_LV4_MULTI_PY		( 11 )
#define	WIN_LV4_MULTI_SX		( 5 )
#define	WIN_LV4_MULTI_SY		( 2 )
#define	WIN_LV4_MULTI_PAL		( PAL_FONT )
#define	WIN_LV4_MULTI_CGX		( WIN_LV4_CGX )
// HP/MHP：４体目（マルチ）
#define	WIN_HP4_MULTI_PX		( 23 )
#define	WIN_HP4_MULTI_PY		( 11 )
#define	WIN_HP4_MULTI_SX		( 8 )
#define	WIN_HP4_MULTI_SY		( 2 )
#define	WIN_HP4_MULTI_PAL		( PAL_FONT )
#define	WIN_HP4_MULTI_CGX		( WIN_HP4_CGX )
// HPゲージ：４体目（マルチ）
#define	WIN_HPBAR4_MULTI_PX		( 24 )
#define	WIN_HPBAR4_MULTI_PY		( 10 )
#define	WIN_HPBAR4_MULTI_SX		( 6 )
#define	WIN_HPBAR4_MULTI_SY		( 1 )
#define	WIN_HPBAR4_MULTI_PAL	( PAL_PANEL_3 )
#define	WIN_HPBAR4_MULTI_CGX	( WIN_HPBAR4_CGX )

// ニックネーム：６体目（マルチ）
#define	WIN_NAME6_MULTI_PX		( 22 )
#define	WIN_NAME6_MULTI_PY		( 14 )
#define	WIN_NAME6_MULTI_SX		( 9 )
#define	WIN_NAME6_MULTI_SY		( 2 )
#define	WIN_NAME6_MULTI_PAL		( PAL_FONT )
#define	WIN_NAME6_MULTI_CGX		( WIN_NAME6_CGX )
// レベル：６体目（マルチ）
#define	WIN_LV6_MULTI_PX		( 17 )
#define	WIN_LV6_MULTI_PY		( 17 )
#define	WIN_LV6_MULTI_SX		( 5 )
#define	WIN_LV6_MULTI_SY		( 2 )
#define	WIN_LV6_MULTI_PAL		( PAL_FONT )
#define	WIN_LV6_MULTI_CGX		( WIN_LV6_CGX )
// HP/MHP：６体目（マルチ）
#define	WIN_HP6_MULTI_PX		( 23 )
#define	WIN_HP6_MULTI_PY		( 17 )
#define	WIN_HP6_MULTI_SX		( 8 )
#define	WIN_HP6_MULTI_SY		( 2 )
#define	WIN_HP6_MULTI_PAL		( PAL_FONT )
#define	WIN_HP6_MULTI_CGX		( WIN_HP6_CGX )
// HPゲージ：６体目（マルチ）
#define	WIN_HPBAR6_MULTI_PX		( 24 )
#define	WIN_HPBAR6_MULTI_PY		( 16 )
#define	WIN_HPBAR6_MULTI_SX		( 6 )
#define	WIN_HPBAR6_MULTI_SY		( 1 )
#define	WIN_HPBAR6_MULTI_PAL	( PAL_PANEL_5 )
#define	WIN_HPBAR6_MULTI_CGX	( WIN_HPBAR6_CGX )

// 「もどる」（通常）
#define	WIN_EXIT_N_PX		( 26 )
#define	WIN_EXIT_N_PY		( 21 )
#define	WIN_EXIT_N_SX		( 5 )
#define	WIN_EXIT_N_SY		( 2 )
#define	WIN_EXIT_N_PAL		( PAL_FONT )
#define	WIN_EXIT_N_CGX		( WIN_HPBAR6_CGX + WIN_HPBAR6_SX * WIN_HPBAR6_SY )
// 「もどる」（決定あり）
#define	WIN_EXIT_E_PY		( 22 )
// 「けってい」
#define	WIN_ENTER_PX		( 25 )
#define	WIN_ENTER_PY		( 20 )
#define	WIN_ENTER_SX		( 7 )
#define	WIN_ENTER_SY		( 2 )
#define	WIN_ENTER_PAL		( PAL_FONT )
#define	WIN_ENTER_CGX		( WIN_EXIT_N_CGX + WIN_EXIT_N_SX * WIN_EXIT_N_SY )
// １行メッセージ
#define	WIN_S_MSG_PX		( 2 )
#define	WIN_S_MSG_PY		( 21 )
#define	WIN_S_MSG_SX		( 20 )
#define	WIN_S_MSG_SY		( 2 )
#define	WIN_S_MSG_PAL		( PAL_TALK_FONT )
#define	WIN_S_MSG_CGX		( WIN_ENTER_CGX + WIN_ENTER_SX * WIN_ENTER_SY )
// ２行メッセージ（メニュー表示時）
#define	WIN_M_MSG_PX		( 2 )
#define	WIN_M_MSG_PY		( 19 )
#define	WIN_M_MSG_SX		( 13 )
#define	WIN_M_MSG_SY		( 4 )
#define	WIN_M_MSG_PAL		( PAL_TALK_FONT )
#define	WIN_M_MSG_CGX		( WIN_S_MSG_CGX + WIN_S_MSG_SX * WIN_S_MSG_SY )
// ２行メッセージ（通常）
#define	WIN_L_MSG_PX		( 2 )
#define	WIN_L_MSG_PY		( 19 )
#define	WIN_L_MSG_SX		( 27 )
#define	WIN_L_MSG_SY		( 4 )
#define	WIN_L_MSG_PAL		( PAL_TALK_FONT )
#define	WIN_L_MSG_CGX		( WIN_M_MSG_CGX + WIN_M_MSG_SX * WIN_M_MSG_SY )

// メニュー（もちもの＆メール）
#define	WIN_ITEM_MENU_PX	( 19 )
#define	WIN_ITEM_MENU_PY	( 17 )
#define	WIN_ITEM_MENU_SX	( 12 )
#define	WIN_ITEM_MENU_SY	( 6 )
#define	WIN_ITEM_MENU_PAL	( PAL_FONT )
#define	WIN_ITEM_MENU_CGX	( WIN_L_MSG_CGX + WIN_L_MSG_SX * WIN_L_MSG_SY )

// メニュー（技回復）
#define	WIN_WAZA_MENU_PX	( 19 )
#define	WIN_WAZA_MENU_PY	( 15 )
#define	WIN_WAZA_MENU_SX	( 12 )
#define	WIN_WAZA_MENU_SY	( 8 )
#define	WIN_WAZA_MENU_PAL	( PAL_FONT )
#define	WIN_WAZA_MENU_CGX	( WIN_ITEM_MENU_CGX )

// メニュー（通常）
#define	ADD_WIN_MENU_PX		( 19 )
#define	ADD_WIN_MENU_PY		( 1 )
#define	ADD_WIN_MENU_SX		( 12 )
#define	ADD_WIN_MENU_SY		( 10 )				// 22MAX
#define	ADD_WIN_MENU_PAL	( PAL_FONT )
#define	ADD_WIN_MENU_CGX	( WIN_ITEM_MENU_CGX )

// はい・いいえ
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( PAL_FONT )
#define	BMP_YESNO_CGX	( ADD_WIN_MENU_CGX )

// レベルアップウィンドウ
#define	ADD_WIN_LVUP_PX		( 1 )
#define	ADD_WIN_LVUP_PY		( 1 )
#define	ADD_WIN_LVUP_SX		( 14 )
#define	ADD_WIN_LVUP_SY		( 12 )
#define	ADD_WIN_LVUP_PAL	( PAL_FONT )
#define	ADD_WIN_LVUP_CGX	( ADD_WIN_MENU_CGX )

#define	LV_DOT_PX			( 5 )
#define	LV_DOT_PY			( 2 )
#define	SLASH_DOT_PX		( 28 )
#define	SLASH_DOT_PY		( 2 )
#define	SLASH_DOT_SX		( 8 )
//#define	HP_DOT_MAX			( 28 )
#define	HP_DOT_MAX			( 24 )
#define	HP_DOT_PX			( SLASH_DOT_PX-HP_DOT_MAX )
#define	HP_DOT_PY			( 2 )
#define	MHP_DOT_PX			( SLASH_DOT_PX+8 )
#define	MHP_DOT_PY			( 2 )


#define	SEX_DOT_SX			( 8 )
#define	SEX_DOT_PX			( WIN_NAME1_SX * 8 - SEX_DOT_SX )


#define	POKE1_BMPWIN_DATA_POS	( 0 )
#define	POKE2_BMPWIN_DATA_POS	( 5 )
#define	POKE3_BMPWIN_DATA_POS	( 10 )
#define	POKE4_BMPWIN_DATA_POS	( 15 )
#define	POKE5_BMPWIN_DATA_POS	( 20 )
#define	POKE6_BMPWIN_DATA_POS	( 25 )
#define	POKE2M_BMPWIN_DATA_POS	( 30 )
#define	POKE4M_BMPWIN_DATA_POS	( 35 )
#define	POKE6M_BMPWIN_DATA_POS	( 40 )

#define	PCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// フォントカラー：黒
#define	PCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：白
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：青
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// フォントカラー：赤
#define	PCOL_W_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 15 ) )		// フォントカラー：黒


static void PL_PanelCommShinka( PLIST_WORK * wk, u8 pos, u8 type );
static void PL_PanelCommWazaOboe( PLIST_WORK * wk, u8 pos, u8 type );
static void PL_PanelCommEventIn( PLIST_WORK * wk, u8 pos, u8 type );
static void PL_PanelCommBattleIn( PLIST_WORK * wk, u8 pos, u8 type );

static BOOL PokeList_TalkMsgCallBack( MSG_PRINT_HEADER *mph, u16 value );



static const BMPWIN_DAT PokePanelBmpData[] =
{
	// １体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME1_PX, WIN_NAME1_PY,
		WIN_NAME1_SX, WIN_NAME1_SY, WIN_NAME1_PAL, WIN_NAME1_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV1_PX, WIN_LV1_PY,
		WIN_LV1_SX, WIN_LV1_SY, WIN_LV1_PAL, WIN_LV1_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP1_PX, WIN_HP1_PY,
		WIN_HP1_SX, WIN_HP1_SY, WIN_HP1_PAL, WIN_HP1_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR1_PX, WIN_HPBAR1_PY,
		WIN_HPBAR1_SX, WIN_HPBAR1_SY, WIN_HPBAR1_PAL, WIN_HPBAR1_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM1_PX, WIN_COMM1_PY,
		WIN_COMM1_SX, WIN_COMM1_SY, WIN_COMM1_PAL, WIN_COMM1_CGX
	},

	// ２体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME2_PX, WIN_NAME2_PY,
		WIN_NAME2_SX, WIN_NAME2_SY, WIN_NAME2_PAL, WIN_NAME2_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV2_PX, WIN_LV2_PY,
		WIN_LV2_SX, WIN_LV2_SY, WIN_LV2_PAL, WIN_LV2_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP2_PX, WIN_HP2_PY,
		WIN_HP2_SX, WIN_HP2_SY, WIN_HP2_PAL, WIN_HP2_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR2_PX, WIN_HPBAR2_PY,
		WIN_HPBAR2_SX, WIN_HPBAR2_SY, WIN_HPBAR2_PAL, WIN_HPBAR2_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM2_PX, WIN_COMM2_PY,
		WIN_COMM2_SX, WIN_COMM2_SY, WIN_COMM2_PAL, WIN_COMM2_CGX
	},

	// ３体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME3_PX, WIN_NAME3_PY,
		WIN_NAME3_SX, WIN_NAME3_SY, WIN_NAME3_PAL, WIN_NAME3_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV3_PX, WIN_LV3_PY,
		WIN_LV3_SX, WIN_LV3_SY, WIN_LV3_PAL, WIN_LV3_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP3_PX, WIN_HP3_PY,
		WIN_HP3_SX, WIN_HP3_SY, WIN_HP3_PAL, WIN_HP3_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR3_PX, WIN_HPBAR3_PY,
		WIN_HPBAR3_SX, WIN_HPBAR3_SY, WIN_HPBAR3_PAL, WIN_HPBAR3_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM3_PX, WIN_COMM3_PY,
		WIN_COMM3_SX, WIN_COMM3_SY, WIN_COMM3_PAL, WIN_COMM3_CGX
	},

	// ４体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME4_PX, WIN_NAME4_PY,
		WIN_NAME4_SX, WIN_NAME4_SY, WIN_NAME4_PAL, WIN_NAME4_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV4_PX, WIN_LV4_PY,
		WIN_LV4_SX, WIN_LV4_SY, WIN_LV4_PAL, WIN_LV4_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP4_PX, WIN_HP4_PY,
		WIN_HP4_SX, WIN_HP4_SY, WIN_HP4_PAL, WIN_HP4_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR4_PX, WIN_HPBAR4_PY,
		WIN_HPBAR4_SX, WIN_HPBAR4_SY, WIN_HPBAR4_PAL, WIN_HPBAR4_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM4_PX, WIN_COMM4_PY,
		WIN_COMM4_SX, WIN_COMM4_SY, WIN_COMM4_PAL, WIN_COMM4_CGX
	},

	// ５体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME5_PX, WIN_NAME5_PY,
		WIN_NAME5_SX, WIN_NAME5_SY, WIN_NAME5_PAL, WIN_NAME5_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV5_PX, WIN_LV5_PY,
		WIN_LV5_SX, WIN_LV5_SY, WIN_LV5_PAL, WIN_LV5_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP5_PX, WIN_HP5_PY,
		WIN_HP5_SX, WIN_HP5_SY, WIN_HP5_PAL, WIN_HP5_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR5_PX, WIN_HPBAR5_PY,
		WIN_HPBAR5_SX, WIN_HPBAR5_SY, WIN_HPBAR5_PAL, WIN_HPBAR5_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM5_PX, WIN_COMM5_PY,
		WIN_COMM5_SX, WIN_COMM5_SY, WIN_COMM5_PAL, WIN_COMM5_CGX
	},

	// ６体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME6_PX, WIN_NAME6_PY,
		WIN_NAME6_SX, WIN_NAME6_SY, WIN_NAME6_PAL, WIN_NAME6_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV6_PX, WIN_LV6_PY,
		WIN_LV6_SX, WIN_LV6_SY, WIN_LV6_PAL, WIN_LV6_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP6_PX, WIN_HP6_PY,
		WIN_HP6_SX, WIN_HP6_SY, WIN_HP6_PAL, WIN_HP6_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR6_PX, WIN_HPBAR6_PY,
		WIN_HPBAR6_SX, WIN_HPBAR6_SY, WIN_HPBAR6_PAL, WIN_HPBAR6_CGX
	},
	{	// コメント
		GF_BGL_FRAME1_M, WIN_COMM6_PX, WIN_COMM6_PY,
		WIN_COMM6_SX, WIN_COMM6_SY, WIN_COMM6_PAL, WIN_COMM6_CGX
	},

	// マルチ用
	// ２体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME2_MULTI_PX, WIN_NAME2_MULTI_PY,
		WIN_NAME2_MULTI_SX, WIN_NAME2_MULTI_SY, WIN_NAME2_MULTI_PAL, WIN_NAME2_MULTI_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV2_MULTI_PX, WIN_LV2_MULTI_PY,
		WIN_LV2_MULTI_SX, WIN_LV2_MULTI_SY, WIN_LV2_MULTI_PAL, WIN_LV2_MULTI_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP2_MULTI_PX, WIN_HP2_MULTI_PY,
		WIN_HP2_MULTI_SX, WIN_HP2_MULTI_SY, WIN_HP2_MULTI_PAL, WIN_HP2_MULTI_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR2_MULTI_PX, WIN_HPBAR2_MULTI_PY,
		WIN_HPBAR2_MULTI_SX, WIN_HPBAR2_MULTI_SY, WIN_HPBAR2_MULTI_PAL, WIN_HPBAR2_MULTI_CGX
	},
	{	// ダミー
		GF_BGL_FRAME1_M, WIN_HPBAR2_MULTI_PX, WIN_HPBAR2_MULTI_PY,
		WIN_HPBAR2_MULTI_SX, WIN_HPBAR2_MULTI_SY, WIN_HPBAR2_MULTI_PAL, WIN_HPBAR2_MULTI_CGX
	},

	// ４体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME4_MULTI_PX, WIN_NAME4_MULTI_PY,
		WIN_NAME4_MULTI_SX, WIN_NAME4_MULTI_SY, WIN_NAME4_MULTI_PAL, WIN_NAME4_MULTI_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV4_MULTI_PX, WIN_LV4_MULTI_PY,
		WIN_LV4_MULTI_SX, WIN_LV4_MULTI_SY, WIN_LV4_MULTI_PAL, WIN_LV4_MULTI_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP4_MULTI_PX, WIN_HP4_MULTI_PY,
		WIN_HP4_MULTI_SX, WIN_HP4_MULTI_SY, WIN_HP4_MULTI_PAL, WIN_HP4_MULTI_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR4_MULTI_PX, WIN_HPBAR4_MULTI_PY,
		WIN_HPBAR4_MULTI_SX, WIN_HPBAR4_MULTI_SY, WIN_HPBAR4_MULTI_PAL, WIN_HPBAR4_MULTI_CGX
	},
	{	// ダミー
		GF_BGL_FRAME1_M, WIN_HPBAR2_MULTI_PX, WIN_HPBAR2_MULTI_PY,
		WIN_HPBAR2_MULTI_SX, WIN_HPBAR2_MULTI_SY, WIN_HPBAR2_MULTI_PAL, WIN_HPBAR2_MULTI_CGX
	},

	// ６体目のポケモン
	{	// 名前
		GF_BGL_FRAME1_M, WIN_NAME6_MULTI_PX, WIN_NAME6_MULTI_PY,
		WIN_NAME6_MULTI_SX, WIN_NAME6_MULTI_SY, WIN_NAME6_MULTI_PAL, WIN_NAME6_MULTI_CGX
	},
	{	// Lv
		GF_BGL_FRAME1_M, WIN_LV6_MULTI_PX, WIN_LV6_MULTI_PY,
		WIN_LV6_MULTI_SX, WIN_LV6_MULTI_SY, WIN_LV6_MULTI_PAL, WIN_LV6_MULTI_CGX
	},
	{	// HP/MHP
		GF_BGL_FRAME1_M, WIN_HP6_MULTI_PX, WIN_HP6_MULTI_PY,
		WIN_HP6_MULTI_SX, WIN_HP6_MULTI_SY, WIN_HP6_MULTI_PAL, WIN_HP6_MULTI_CGX
	},
	{	// HPバー
		GF_BGL_FRAME1_M, WIN_HPBAR6_MULTI_PX, WIN_HPBAR6_MULTI_PY,
		WIN_HPBAR6_MULTI_SX, WIN_HPBAR6_MULTI_SY, WIN_HPBAR6_MULTI_PAL, WIN_HPBAR6_MULTI_CGX
	},
	{	// ダミー
		GF_BGL_FRAME1_M, WIN_HPBAR2_MULTI_PX, WIN_HPBAR2_MULTI_PY,
		WIN_HPBAR2_MULTI_SX, WIN_HPBAR2_MULTI_SY, WIN_HPBAR2_MULTI_PAL, WIN_HPBAR2_MULTI_CGX
	},
};


static const BMPWIN_DAT PokeListBmpData[] =
{
	{	// 「もどる」（通常）
		GF_BGL_FRAME1_M, WIN_EXIT_N_PX, WIN_EXIT_N_PY,
		WIN_EXIT_N_SX, WIN_EXIT_N_SY, WIN_EXIT_N_PAL, WIN_EXIT_N_CGX
	},
	{	// 「けってい」
		GF_BGL_FRAME1_M, WIN_ENTER_PX, WIN_ENTER_PY,
		WIN_ENTER_SX, WIN_ENTER_SY, WIN_ENTER_PAL, WIN_ENTER_CGX
	},
	{	// １行メッセージ
		GF_BGL_FRAME0_M, WIN_S_MSG_PX, WIN_S_MSG_PY,
		WIN_S_MSG_SX, WIN_S_MSG_SY, WIN_S_MSG_PAL, WIN_S_MSG_CGX,
	},
	{	// ２行メッセージ（メニュー表示時）
		GF_BGL_FRAME0_M, WIN_M_MSG_PX, WIN_M_MSG_PY,
		WIN_M_MSG_SX, WIN_M_MSG_SY, WIN_M_MSG_PAL, WIN_M_MSG_CGX
	},
	{	// ２行メッセージ（通常）
		GF_BGL_FRAME0_M, WIN_L_MSG_PX, WIN_L_MSG_PY,
		WIN_L_MSG_SX, WIN_L_MSG_SY, WIN_L_MSG_PAL, WIN_L_MSG_CGX
	},
	{	// メニュー（もちもの＆メール）
		GF_BGL_FRAME0_M, WIN_ITEM_MENU_PX, WIN_ITEM_MENU_PY,
		WIN_ITEM_MENU_SX, WIN_ITEM_MENU_SY, WIN_ITEM_MENU_PAL, WIN_ITEM_MENU_CGX
	},
	{	// メニュー（技回復）
		GF_BGL_FRAME0_M, WIN_WAZA_MENU_PX, WIN_WAZA_MENU_PY,
		WIN_WAZA_MENU_SX, WIN_WAZA_MENU_SY, WIN_WAZA_MENU_PAL, WIN_WAZA_MENU_CGX
	}
};

// はい・いいえ
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME0_M, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, BMP_YESNO_CGX
};




static void PokeParamBmpAdd( GF_BGL_INI * ini, GF_BGL_BMPWIN * win, const BMPWIN_DAT * dat )
{
	GF_BGL_BmpWinAddEx( ini, &win[0], &dat[0] );
	GF_BGL_BmpWinAddEx( ini, &win[1], &dat[1] );
	GF_BGL_BmpWinAddEx( ini, &win[2], &dat[2] );
	GF_BGL_BmpWinAddEx( ini, &win[3], &dat[3] );
	GF_BGL_BmpWinAddEx( ini, &win[4], &dat[4] );
}



void PokeListBmpAdd( PLIST_WORK * wk )
{
	const BMPWIN_DAT * dat = PokePanelBmpData;
	u16	i;

	// ポケモンのパラメータ関係のBMPセット
	PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE1_NAME], &dat[POKE1_BMPWIN_DATA_POS] );
	PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE3_NAME], &dat[POKE3_BMPWIN_DATA_POS] );
	PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE5_NAME], &dat[POKE5_BMPWIN_DATA_POS] );

	if( wk->dat->type == PL_TYPE_MULTI ){
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE2_NAME], &dat[POKE2M_BMPWIN_DATA_POS] );
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE4_NAME], &dat[POKE4M_BMPWIN_DATA_POS] );
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE6_NAME], &dat[POKE6M_BMPWIN_DATA_POS] );
	}else{
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE2_NAME], &dat[POKE2_BMPWIN_DATA_POS] );
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE4_NAME], &dat[POKE4_BMPWIN_DATA_POS] );
		PokeParamBmpAdd( wk->bgl, &wk->win[WIN_POKE6_NAME], &dat[POKE6_BMPWIN_DATA_POS] );
	}

	if( wk->dat->mode == PL_MODE_SELECT || wk->dat->mode == PL_MODE_BATTLE_TOWER ){
		BMPWIN_DAT	dat;
		dat = PokeListBmpData[0];
		dat.pos_y = WIN_EXIT_E_PY;
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_EXIT], &dat );
	}else{
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_EXIT], &PokeListBmpData[0] );
	}
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_ENTER], &PokeListBmpData[1] );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_S_MSG], &PokeListBmpData[2] );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_M_MSG], &PokeListBmpData[3] );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_L_MSG], &PokeListBmpData[4] );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_ITEM_MENU], &PokeListBmpData[5] );
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[WIN_WAZA_MENU], &PokeListBmpData[6] );
}


//--------------------------------------------------------------------------------------------
/**
 * BMPウィンドウ破棄
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListBmpWinExit( PLIST_WORK * wk )
{
	u16	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
	for( i=0; i<ADD_WIN_MAX; i++ ){
		if( GF_BGL_BmpWinAddCheck( &wk->add_win[i] ) == TRUE ){
			GF_BGL_BmpWinDel( &wk->add_win[i] );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * メニュー項目文字列取得
 *
 * @param	win		BMPウィンドウデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------

void PokeListMenuStrMake( PLIST_WORK * wk )
{
	// ならびかえ
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_01, wk->menu_str[MENU_ROW] );
	// つよさをみる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_02, wk->menu_str[MENU_STATUS] );
	// もちもの
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_03, wk->menu_str[MENU_ITEM] );
	// もちものメニュー：もたせる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_16, wk->menu_str[MENU_ITEM_S] );
	// もちものメニュー：あずかる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_17, wk->menu_str[MENU_ITEM_G] );
	// メール
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_04, wk->menu_str[MENU_MAIL] );
	// メールを　よむ
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_05, wk->menu_str[MENU_MAIL_R] );
	// メールを　とる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_06, wk->menu_str[MENU_MAIL_G] );
	// あずける
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_07, wk->menu_str[MENU_AZUKERU] );
	// やめる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_08, wk->menu_str[MENU_CANCEL] );
	// いれかえる
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_09, wk->menu_str[MENU_CHANGE] );
	// さんかする（戦闘参加選択）
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_10, wk->menu_str[MENU_BATTLE_IN] );
	// さんかしない
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_11, wk->menu_str[MENU_OUT] );
	// さんかする（コンテスト参加）
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_10, wk->menu_str[MENU_CONTEST_IN] );
	// セットする
	MSGMAN_GetString( wk->msg_man, mes_pokelist_05_22, wk->menu_str[MENU_KAPSEL_SET] );
}

void PokeList_WazaMenuStrGet( PLIST_WORK * wk, u16 waza, u8 pos )
{
	STRBUF * mstr;

	// 技
	mstr = MSGMAN_AllocString( wk->msg_man, mes_pokelist_05_12+pos );

	WORDSET_RegisterWazaName( wk->wset, 0, waza );
	WORDSET_ExpandStr( wk->wset, wk->menu_str[MENU_W_IAIGIRI+pos], mstr );

	STRBUF_Delete( mstr );
}


void PokeListMenuDataMake( PLIST_WORK * wk, const u8 * prm, u8 siz )
{
	BMPMENU_HEADER	mh;
	u16	i, j;

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->add_win[ADD_WIN_MENU], GF_BGL_FRAME0_M,
		ADD_WIN_MENU_PX, 23-siz*2,
		ADD_WIN_MENU_SX, siz * 2, ADD_WIN_MENU_PAL, ADD_WIN_MENU_CGX );

	wk->md = BMP_MENULIST_Create( siz, HEAPID_POKELIST );

	j = 0;
	for( i=0; i<siz; i++ ){
		if( prm[i] >= MENU_W_IAIGIRI ){
			BMP_MENULIST_AddString(
				wk->md, wk->menu_str[MENU_W_IAIGIRI+j], PokeListMenuParamGet( (u8)prm[i] ) );
			j++;
		}else{
			BMP_MENULIST_AddString(
				wk->md, wk->menu_str[prm[i]], PokeListMenuParamGet( (u8)prm[i] ) );
		}
	}

	mh.menu  = wk->md;
	mh.win   = &wk->add_win[ADD_WIN_MENU];
	mh.font  = FONT_SYSTEM;
	mh.x_max = 1;
	mh.y_max = siz;
	mh.line_spc = 0;
	mh.c_disp_f = 0;
	if( siz >= 4 ){
		mh.loop_f = 1;
	}else{
		mh.loop_f = 0;
	}

	BmpMenuWinWrite( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );
	wk->mw = BmpMenuAddEx( &mh, 8, 0, 0, HEAPID_POKELIST, PAD_BUTTON_CANCEL );
}

void PokeListMenuMsgMake( PLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	STRBUF * str;

	if( wk->dat->mode == PL_MODE_KAPSEL_SET ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_03_06, wk->msg_buf );
	}else{
		pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_03_01 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}
}






static const u16 ParamStrTbl[6][4] =
{	// ニックネーム, Lv, HP, MHP
	{ mes_pokelist_01_09, mes_pokelist_01_03, mes_pokelist_01_21, mes_pokelist_01_15 },
	{ mes_pokelist_01_10, mes_pokelist_01_04, mes_pokelist_01_22, mes_pokelist_01_16 },
	{ mes_pokelist_01_11, mes_pokelist_01_05, mes_pokelist_01_23, mes_pokelist_01_17 },
	{ mes_pokelist_01_12, mes_pokelist_01_06, mes_pokelist_01_24, mes_pokelist_01_18 },
	{ mes_pokelist_01_13, mes_pokelist_01_07, mes_pokelist_01_25, mes_pokelist_01_19 },
	{ mes_pokelist_01_14, mes_pokelist_01_08, mes_pokelist_01_26, mes_pokelist_01_20 }
};

enum {
	PRM_STRTBL_NAME = 0,
	PRM_STRTBL_LV,
	PRM_STRTBL_HP,
	PRM_STRTBL_MHP
};


static void ParamMarkPut( PLIST_WORK * wk, u8 num )
{
	// HPとMHPのスラッシュ
/*	システムフォント版
	MSGMAN_GetString( wk->msg_man, mes_pokelist_01_27, wk->str_buf );
	GF_STR_PrintColor(
		&wk->win[WIN_POKE1_HP+num*5], FONT_SYSTEM,
		wk->str_buf, SLASH_DOT_PX, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
*/
	NUMFONT_WriteMark(
		wk->num_font, NUMFONT_MARK_SLASH, &wk->win[WIN_POKE1_HP+num*5], SLASH_DOT_PX, SLASH_DOT_PY );

}

void PokeListNameMake( PLIST_WORK * wk, POKEMON_PARAM * pp, u32 pos )
{
	STRBUF * str;

	str = MSGMAN_AllocString( wk->msg_man, ParamStrTbl[pos][PRM_STRTBL_NAME] );

	WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
	WORDSET_ExpandStr( wk->wset, wk->panel[pos].name, str );
	STRBUF_Delete( str );
}

void PokeListNamePut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	POKEMON_PARAM * pp;

	win = &wk->win[WIN_POKE1_NAME+num*5];

//	GF_BGL_BmpWinDataFill( win, 0 );

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->panel[num].name, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );

	if( wk->panel[num].egg == 1 ){
		GF_BGL_BmpWinOnVReq( win );
		return;
	}

	// 性別
	if( wk->panel[num].sex_put == 0 ){
		if( wk->panel[num].sex == PARA_MALE ){
			MSGMAN_GetString( wk->msg_man, mes_pokelist_01_28, wk->str_buf );
			GF_STR_PrintColor(
				win, FONT_SYSTEM, wk->str_buf, SEX_DOT_PX, 0, MSG_NO_PUT, PCOL_N_BLUE, NULL );
		}else if( wk->panel[num].sex == PARA_FEMALE ){
			MSGMAN_GetString( wk->msg_man, mes_pokelist_01_29, wk->str_buf );
			GF_STR_PrintColor(
				win, FONT_SYSTEM, wk->str_buf, SEX_DOT_PX, 0, MSG_NO_PUT, PCOL_N_RED, NULL );
		}
	}
	GF_BGL_BmpWinOnVReq( win );
}

void PokeListLvPut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_LV+num*5];

//	GF_BGL_BmpWinFill( win, 0, 0, 0, WIN_LV1_SX*8, WIN_LV1_SY*8 );

//	PokeList_StatusIconChg( wk, num, wk->panel[num].st );
	if( wk->panel[num].st != PL_ST_NONE ){
		GF_BGL_BmpWinOnVReq( win );
		return;
	}

	// Lv
/*	システムフォント版
	NUMFONT_WriteMark(
		wk->num_font, NUMFONT_MARK_LV, &wk->win[WIN_POKE1_LV+num*5], 0, 5 );

	str = MSGMAN_AllocString( wk->msg_man, ParamStrTbl[num][PRM_STRTBL_LV] );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->panel[num].lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->str_buf, str );

	STRBUF_Delete( str );

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->str_buf, NUMFONT_MARK_WIDTH, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	GF_BGL_BmpWinOnVReq( win );
*/
	NUMFONT_WriteSet(
		wk->num_font, NUMFONT_MARK_LV, wk->panel[num].lv,
		3, NUMFONT_MODE_LEFT, win, LV_DOT_PX, LV_DOT_PY );
	GF_BGL_BmpWinOnVReq( win );
}

void PokeListHPPut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[WIN_POKE1_HP+num*5];

/*	システムフォント版
	str = MSGMAN_AllocString( wk->msg_man, ParamStrTbl[num][PRM_STRTBL_HP] );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->panel[num].hp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->str_buf, str );
	STRBUF_Delete( str );

	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->str_buf, 0 );

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->str_buf, SLASH_DOT_PX-siz, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	GF_BGL_BmpWinOnVReq( win );
*/
	NUMFONT_WriteNumber(
		wk->num_font, wk->panel[num].hp, 3, NUMFONT_MODE_SPACE, win, HP_DOT_PX, HP_DOT_PY );
	GF_BGL_BmpWinOnVReq( win );
}

void PokeListHPClear( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[WIN_POKE1_HP+num*5];

	GF_BGL_BmpWinFill( win, 0, HP_DOT_PX, 0, HP_DOT_MAX, WIN_HP1_SY*8 );
	GF_BGL_BmpWinOnVReq( win );
}


static void PokeListMHPPut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_HP+num*5];

/*	システムフォント版
	str = MSGMAN_AllocString( wk->msg_man, ParamStrTbl[num][PRM_STRTBL_MHP] );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->panel[num].mhp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->str_buf, str );
	STRBUF_Delete( str );

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->str_buf,
		SLASH_DOT_PX+SLASH_DOT_SX, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	GF_BGL_BmpWinOnVReq( win );
*/
	NUMFONT_WriteNumber(
		wk->num_font, wk->panel[num].mhp, 3, NUMFONT_MODE_LEFT, win, MHP_DOT_PX, MHP_DOT_PY );
	GF_BGL_BmpWinOnVReq( win );
}


#define	PL_COL_HPGAUGE1		( 9 )
#define	PL_COL_HPGAUGE2		( 10 )
#define	PL_PALPOS_GREEN		( 9 )
#define	PL_PALPOS_YELLOW	( 16+9 )
#define	PL_PALPOS_RED		( 32+9 )

void PokeListHPBerPut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	u8	now_dot;

	win = &wk->win[WIN_POKE1_HPBAR+num*5];

//	GF_BGL_BmpWinDataFill( win, 0 );

	switch( GetHPGaugeDottoColor( wk->panel[num].hp, wk->panel[num].mhp, PL_HP_DOTTO_MAX ) ){
	case HP_DOTTO_NULL:
		GF_BGL_BmpWinOnVReq( win );
		return;
	case HP_DOTTO_MAX:		// 緑
	case HP_DOTTO_GREEN:
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PL_PALPOS_GREEN],
			2*2, (win->palnum*16+PL_COL_HPGAUGE1)*2 );
		break;
	case HP_DOTTO_YELLOW:	// 黄
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PL_PALPOS_YELLOW],
			2*2, (win->palnum*16+PL_COL_HPGAUGE1)*2 );
		break;
	case HP_DOTTO_RED:		// 赤
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PL_PALPOS_RED],
			2*2, (win->palnum*16+PL_COL_HPGAUGE1)*2 );
		break;
	}

	now_dot = GetNumDotto( wk->panel[num].hp, wk->panel[num].mhp, PL_HP_DOTTO_MAX );

	GF_BGL_BmpWinFill( win, PL_COL_HPGAUGE2, 0, 2, now_dot, 1 );
	GF_BGL_BmpWinFill( win, PL_COL_HPGAUGE1, 0, 3, now_dot, 2 );
	GF_BGL_BmpWinFill( win, PL_COL_HPGAUGE2, 0, 5, now_dot, 1 );

	GF_BGL_BmpWinOnVReq( win );
}

void PokeListParamPut( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_NAME+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_LV+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_HP+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_HPBAR+num*5], 0 );

	PokeListNamePut( wk, num );

	if( wk->panel[num].egg == 1 ){
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_POKE1_NAME+num*5] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_POKE1_LV+num*5] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_POKE1_HP+num*5] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_POKE1_HPBAR+num*5] );
		return;
	}

	ParamMarkPut( wk, num );

	PokeListLvPut( wk, num );
	PokeListHPPut( wk, num );
	PokeListMHPPut( wk, num );
	PokeListHPBerPut( wk, num );
}

void PokeListParamBmpCgxOn( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BmpWinCgxOn( &wk->win[WIN_POKE1_NAME+num*5] );
	GF_BGL_BmpWinCgxOn( &wk->win[WIN_POKE1_LV+num*5] );
	GF_BGL_BmpWinCgxOn( &wk->win[WIN_POKE1_HP+num*5] );
	GF_BGL_BmpWinCgxOn( &wk->win[WIN_POKE1_HPBAR+num*5] );
}

void PokeListParamBmpWinOff( PLIST_WORK * wk, u8 num )
{
	GF_BGL_BmpWinOffVReq( &wk->win[WIN_POKE1_NAME+num*5] );
	GF_BGL_BmpWinOffVReq( &wk->win[WIN_POKE1_LV+num*5] );
	GF_BGL_BmpWinOffVReq( &wk->win[WIN_POKE1_HP+num*5] );
	GF_BGL_BmpWinOffVReq( &wk->win[WIN_POKE1_HPBAR+num*5] );
}

void PokeList_PanelShinkaCommPut( PLIST_WORK * wk, u8 num )
{
	POKEMON_PARAM * pp;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_NAME+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_LV+num*5], 0 );

	PokeListNamePut( wk, num );

	if( wk->panel[num].egg == 1 ){
		PL_PanelCommShinka( wk, num, 1 );
		return;
	}

	PokeListLvPut( wk, num );

	pp  = PokeParty_GetMemberPointer( wk->dat->pp, num );
	if( PokeShinkaCheck( NULL, pp, ITEM_SHINKA_CHECK, wk->dat->item, NULL ) == 0 ){
		PL_PanelCommShinka( wk, num, 1 );
	}else{
		PL_PanelCommShinka( wk, num, 0 );
	}
}

void PokeList_PanelWazaOboeCommPut( PLIST_WORK * wk, u8 num )
{
	POKEMON_PARAM * pp;
	u8	ret;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_NAME+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_LV+num*5], 0 );

	PokeListNamePut( wk, num );

	if( wk->panel[num].egg == 1 ){
		PL_PanelCommWazaOboe( wk, num, 1 );
		return;
	}

	PokeListLvPut( wk, num );

	pp  = PokeParty_GetMemberPointer( wk->dat->pp, num );
	ret = PokeList_WazaOboeCheck( wk, pp );
	if( ret == 0xff ){
		PL_PanelCommWazaOboe( wk, num, 1 );
	}else if( ret == 0xfd ){
		PL_PanelCommWazaOboe( wk, num, 2 );
	}else{
		PL_PanelCommWazaOboe( wk, num, 0 );
	}
}

void PokeList_PanelContestCommPut( PLIST_WORK * wk, u8 num )
{
	POKEMON_PARAM * pp;
	u8	ret;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_NAME+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_LV+num*5], 0 );

	PokeListNamePut( wk, num );

	if( wk->panel[num].egg != 1 ){
		PokeListLvPut( wk, num );
	}

	PL_PanelCommEventIn( wk, num, (u8)wk->panel[num].contest );
}

void PokeList_PanelBattleInNamePut( PLIST_WORK * wk, u8 num )
{
	POKEMON_PARAM * pp;
	u8	ret;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_NAME+num*5], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_POKE1_LV+num*5], 0 );

	PokeListNamePut( wk, num );

	if( wk->panel[num].egg != 1 ){
		PokeListLvPut( wk, num );
	}
}

void PokeList_PanelBattleInCommPut( PLIST_WORK * wk, u8 num )
{
	u8	i;

	for( i=0; i<wk->dat->in_max; i++ ){
		if( wk->dat->in_num[i] == num+1 ){
			PL_PanelCommBattleIn( wk, num, i );
			return;
		}
	}

//	if( wk->panel[num].egg == 1 || wk->panel[num].lv > wk->dat->in_lv ){
	if( PokeList_BattleInCheck( wk, num ) == 0 ){
		PL_PanelCommBattleIn( wk, num, 8 );
		return;
	}

	PL_PanelCommBattleIn( wk, num, 7 );
}


static u32 MsgCenterPutPosGet( FONT_TYPE font, const STRBUF * str, u32 win_sx )
{
	u32	str_siz = FontProc_GetPrintStrWidth( font, str, 0 );

	return ((win_sx-str_siz)>>1);
}

//--------------------------------------------------------------------------------------------
/**
 * 「けってい」「もどる」表示
 *
 * @param	wk		ポケモンリストワーク
 * @param	flg		表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListSelectMsgPut( PLIST_WORK * wk, u8 flg )
{
	u32	px;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_ENTER], FBMP_COL_NULL );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_EXIT], FBMP_COL_NULL );

	if( flg & 1 ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_01_01, wk->str_buf );
		px = MsgCenterPutPosGet( FONT_SYSTEM, wk->str_buf, wk->win[WIN_ENTER].sizx * 8 );
		GF_STR_PrintColor(
			&wk->win[WIN_ENTER], FONT_SYSTEM,
			wk->str_buf, px, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_ENTER] );
	}
	if( flg & 2 ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_01_02, wk->str_buf );
		px = MsgCenterPutPosGet( FONT_SYSTEM, wk->str_buf, wk->win[WIN_EXIT].sizx * 8 );
		GF_STR_PrintColor(
			&wk->win[WIN_EXIT], FONT_SYSTEM,
			wk->str_buf, px, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_EXIT] );
	}
}




static void PokeListMsgPut( PLIST_WORK * wk, GF_BGL_BMPWIN * win, u32 id, u8 flg )
{
	if( flg == 1 ){
//		BmpMenuWinWrite( win, WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );
		BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PL_TALK_WIN_CGX, PAL_TALK_WIN );
	}
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );
	if( id != PL_MSG_COMP_EXPAND ){
		MSGMAN_GetString( wk->msg_man, id, wk->msg_buf );
	}
	GF_STR_PrintSimple( win, FONT_TALK, wk->msg_buf, 0, 0, MSG_NO_PUT, NULL );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * １行メッセージ表示
 *
 * @param	wk		ポケモンリストワーク
 * @param	id		メッセージID
 * @param	flg		ウィンドウ表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListSmallMsgPut( PLIST_WORK * wk, u32 id, u8 flg )
{
	PokeListMsgPut( wk, &wk->win[WIN_S_MSG], id, flg );
}

//--------------------------------------------------------------------------------------------
/**
 * ２行メッセージ表示
 *
 * @param	wk		ポケモンリストワーク
 * @param	id		メッセージID
 * @param	flg		ウィンドウ表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListMiddleMsgPut( PLIST_WORK * wk, u32 id, u8 flg )
{
	PokeListMsgPut( wk, &wk->win[WIN_M_MSG], id, flg );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話（風）メッセージ表示
 *
 * @param	wk		ポケモンリストワーク
 * @param	id		メッセージID
 * @param	flg		ウィンドウ表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListLargeMsgPut( PLIST_WORK * wk, u32 id, u8 flg )
{
	GF_BGL_BMPWIN * win = &wk->win[WIN_L_MSG];

	if( flg == 1 ){
//		BmpMenuWinWrite( win, WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );
		BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PL_TALK_WIN_CGX, PAL_TALK_WIN );
	}
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );
	if( id != PL_MSG_COMP_EXPAND ){
		MSGMAN_GetString( wk->msg_man, id, wk->msg_buf );
	}
	PokeList_TalkMsgStart( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話（風）メッセージスタート
 *
 * @param	wk		ポケモンリストワーク
 * @param	id		メッセージID
 * @param	flg		ウィンドウ表示フラグ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeList_TalkMsgStart( PLIST_WORK * wk )
{
	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );
	wk->msg_index = GF_STR_PrintSimple(
						&wk->win[WIN_L_MSG], FONT_TALK, wk->msg_buf, 0, 0,
						CONFIG_GetMsgPrintSpeed(wk->dat->cfg), PokeList_TalkMsgCallBack );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話（風）メッセージコールバック
 *
 * @param	mph		メッセージ描画データ
 * @param	value	コールバックナンバ
 *
 * @retval	"TRUE = 待ち"
 * @retval	"FALSE = 次の処理へ"
 */
//--------------------------------------------------------------------------------------------
static BOOL PokeList_TalkMsgCallBack( MSG_PRINT_HEADER * mph, u16 value )
{
	switch( value ){
	case 1:		// SE終了待ち
		return Snd_SePlayCheckAll();

	case 2:		// ME終了待ち
		return Snd_MePlayCheckBgmPlay();
/*
	case 2:
		Snd_MePlay( SEQ_FANFA5 );
		break;
*/
	case 3:		// "ポカン"
		Snd_SePlay( SEQ_SE_DP_KON );
		break;

	case 4:		// "おぼえた"
		Snd_MePlay( SEQ_FANFA1 );
		break;

	case 5:		// "ポカン"のSE終了待ち
		return Snd_SePlayCheck( SEQ_SE_DP_KON );
	}

	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * はい・いいえ表示
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeList_YesNoSelectInit( PLIST_WORK * wk )
{
	wk->mw = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, PL_MENU_WIN_CGX, PAL_MENU_WIN, HEAPID_POKELIST );
}


//--------------------------------------------------------------------------------------------
/**
 * パネルコメント：進化できるか
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PL_PanelCommShinka( PLIST_WORK * wk, u8 pos, u8 type )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_COMM+pos*5];

	GF_BGL_BmpWinDataFill( win, 0 );

	switch( type ){
	case 0:		// 可
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_10 );
		break;
	case 1:		// 不可
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_11 );
		break;
	}

	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * パネルコメント：技を覚えられるか
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PL_PanelCommWazaOboe( PLIST_WORK * wk, u8 pos, u8 type )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_COMM+pos*5];

	GF_BGL_BmpWinDataFill( win, 0 );

	switch( type ){
	case 0:		// 覚えられる
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_07 );
		break;
	case 1:		// 覚えられない
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_08 );
		break;
	case 2:		// 覚えいる
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_09 );
		break;
	}

	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * パネルコメント：参加できるか
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PL_PanelCommEventIn( PLIST_WORK * wk, u8 pos, u8 type )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_COMM+pos*5];

	GF_BGL_BmpWinDataFill( win, 0 );
	if( type == 0 ){
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_13 );
	}else{
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_12 );
	}
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}


//--------------------------------------------------------------------------------------------
/**
 * パネルコメント：参加するか
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PL_PanelCommBattleIn( PLIST_WORK * wk, u8 pos, u8 type )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_POKE1_COMM+pos*5];

	GF_BGL_BmpWinDataFill( win, 0 );
	if( type < 6 ){
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_03+type );
	}else if( type == 7 ){
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_01 );
	}else{
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_06_02 );
	}
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}


//============================================================================================
//	レベルアップウィンドウ
//============================================================================================
#define	LVUP_PLUS_PX	( 80 )
#define	LVUP_UP_PX		( 94 )
#define	LVUP_PRM_PX		( 72 )
#define	LVUP_PRM_SX		( 32 )

void PokeList_LvWinPut( PLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	STRBUF * str;
	STRBUF * plus;
	u32	i;
	u16	now[6];

	pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );

	now[0] = (u16)PokeParaGet( pp, ID_PARA_hpmax, NULL );
	now[1] = (u16)PokeParaGet( pp, ID_PARA_pow, NULL );
	now[2] = (u16)PokeParaGet( pp, ID_PARA_def, NULL );
	now[3] = (u16)PokeParaGet( pp, ID_PARA_spepow, NULL );
	now[4] = (u16)PokeParaGet( pp, ID_PARA_spedef, NULL );
	now[5] = (u16)PokeParaGet( pp, ID_PARA_agi, NULL );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->add_win[ADD_WIN_MENU], GF_BGL_FRAME0_M, ADD_WIN_LVUP_PX,
		ADD_WIN_LVUP_PY, ADD_WIN_LVUP_SX, ADD_WIN_LVUP_SY, ADD_WIN_LVUP_PAL, ADD_WIN_LVUP_CGX );

	BmpMenuWinWrite( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_MENU], 15 );

	plus = MSGMAN_AllocString( wk->msg_man, mes_pokelist_08_07 );
	for( i=0; i<6; i++ ){
		// 項目
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_08_01+i );
		GF_STR_PrintSimple(
			&wk->add_win[ADD_WIN_MENU], FONT_SYSTEM, str, 0, 16*i, MSG_NO_PUT, NULL );
		STRBUF_Delete( str );
		
		// 「＋」
		GF_STR_PrintSimple(
			&wk->add_win[ADD_WIN_MENU], FONT_SYSTEM, plus, LVUP_PLUS_PX, 16*i, MSG_NO_PUT, NULL );

		// パラメータ
		str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_08_08 );
		WORDSET_RegisterNumber(
			wk->wset, 0, now[i]-wk->tmp[i], 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		GF_STR_PrintSimple(
			&wk->add_win[ADD_WIN_MENU], FONT_SYSTEM,
			wk->msg_buf, LVUP_UP_PX, 16*i, MSG_NO_PUT, NULL );

		wk->tmp[i] = now[i];
	}
	STRBUF_Delete( plus );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_MENU] );
}

void PokeList_LvUpParamPut( PLIST_WORK * wk )
{
	STRBUF * str;
	u32	siz;
	u32	i;

	GF_BGL_BmpWinFill(
		&wk->add_win[ADD_WIN_MENU], 15, LVUP_PLUS_PX, 0, LVUP_PRM_SX, ADD_WIN_LVUP_SX*8 );

	str = MSGMAN_AllocString( wk->msg_man, mes_pokelist_08_08 );
	for( i=0; i<6; i++ ){
		WORDSET_RegisterNumber(
			wk->wset, 0, wk->tmp[i], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		GF_STR_PrintSimple(
			&wk->add_win[ADD_WIN_MENU], FONT_SYSTEM,
			wk->msg_buf, ADD_WIN_LVUP_SX*8-siz-8, 16*i, MSG_NO_PUT, NULL );
	}
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_MENU] );
}

void PokeList_LvUpWinExit( PLIST_WORK * wk )
{
	BmpMenuWinClear( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->add_win[ADD_WIN_MENU] );
}
