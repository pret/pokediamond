//============================================================================================
/**
 * @file	b_plist_bmp.c
 * @brief	戦闘用ポケモンリスト画面BMP関連
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/pmfprint.h"
#include "system/buflen.h"
#include "system/clact_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_b_plist.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "battle/wazano_def.h"
#include "poketool/pokeparty.h"
#include "poketool/waza_tool.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "itemtool/item.h"
#include "application/app_tool.h"
#include "application/p_status.h"
#include "b_app_tool.h"

#define	B_PLIST_BMP_H_GLOBAL
#include "b_plist.h"
#include "b_plist_bmp_def.h"
#include "b_plist_main.h"
#include "b_plist_bmp.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	PCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// フォントカラー：黒
#define	PCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：白
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 7, 8, 0 ) )		// フォントカラー：青
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：赤

#define	PCOL_BTN		( GF_PRINTCOLOR_MAKE( 7, 8, 9 ) )		// フォントカラー：ボタン
#define	PCOL_B_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：ボタン用白
#define	PCOL_B_BLUE		( GF_PRINTCOLOR_MAKE( 10, 11, 0 ) )		// フォントカラー：ボタン用青
#define	PCOL_B_RED		( GF_PRINTCOLOR_MAKE( 12, 13, 0 ) )		// フォントカラー：ボタン用赤

#define	HP_GAGE_COL_G1	( 1 )	// HPゲージカラー緑１
#define	HP_GAGE_COL_G2	( 2 )	// HPゲージカラー緑２
#define	HP_GAGE_COL_Y1	( 3 )	// HPゲージカラー黄１
#define	HP_GAGE_COL_Y2	( 4 )	// HPゲージカラー黄２
#define	HP_GAGE_COL_R1	( 5 )	// HPゲージカラー赤１
#define	HP_GAGE_COL_R2	( 6 )	// HPゲージカラー赤２


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BPL_Page1BmpWrite( BPLIST_WORK * wk );
static void BPL_ChgPageBmpWrite( BPLIST_WORK * wk );
static void BPL_StMainPageBmpWrite( BPLIST_WORK * wk );
static void BPL_StWazaSelPageBmpWrite( BPLIST_WORK * wk );
static void BPL_StWazaInfoPageBmpWrite( BPLIST_WORK * wk );
static void BPL_PPRcvPageBmpWrite( BPLIST_WORK * wk );
static void BPL_WazaDelSelPageBmpWrite( BPLIST_WORK * wk );
static void BPL_Page6BmpWrite( BPLIST_WORK * wk );
static void BPL_Page8BmpWrite( BPLIST_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// 共通デフォルトウィンドウデータ
static const BMPWIN_DAT CommBmpData[] =
{
	{	// コメント表示
		GF_BGL_FRAME0_S, WIN_P1_COMMENT_PX, WIN_P1_COMMENT_PY,
		WIN_P1_COMMENT_SX, WIN_P1_COMMENT_SY, WIN_P1_COMMENT_PAL, WIN_P1_COMMENT_CGX
	},
	{	// メッセージ表示
		GF_BGL_FRAME0_S, WIN_TALK_PX, WIN_TALK_PY,
		WIN_TALK_SX, WIN_TALK_SY, WIN_TALK_PAL, WIN_TALK_CGX
	}
};

// ページ１のBMPウィンドウデータ
static const BMPWIN_DAT Page1_BmpData[] =
{
	{	// ポケモン１
		GF_BGL_FRAME1_S, WIN_P1_POKE1_PX, WIN_P1_POKE1_PY,
		WIN_P1_POKE1_SX, WIN_P1_POKE1_SY, WIN_P1_POKE1_PAL, WIN_P1_POKE1_CGX
	},
	{	// ポケモン２
		GF_BGL_FRAME1_S, WIN_P1_POKE2_PX, WIN_P1_POKE2_PY,
		WIN_P1_POKE2_SX, WIN_P1_POKE2_SY, WIN_P1_POKE2_PAL, WIN_P1_POKE2_CGX
	},
	{	// ポケモン３
		GF_BGL_FRAME1_S, WIN_P1_POKE3_PX, WIN_P1_POKE3_PY,
		WIN_P1_POKE3_SX, WIN_P1_POKE3_SY, WIN_P1_POKE3_PAL, WIN_P1_POKE3_CGX
	},
	{	// ポケモン４
		GF_BGL_FRAME1_S, WIN_P1_POKE4_PX, WIN_P1_POKE4_PY,
		WIN_P1_POKE4_SX, WIN_P1_POKE4_SY, WIN_P1_POKE4_PAL, WIN_P1_POKE4_CGX
	},
	{	// ポケモン５
		GF_BGL_FRAME1_S, WIN_P1_POKE5_PX, WIN_P1_POKE5_PY,
		WIN_P1_POKE5_SX, WIN_P1_POKE5_SY, WIN_P1_POKE5_PAL, WIN_P1_POKE5_CGX
	},
	{	// ポケモン６
		GF_BGL_FRAME1_S, WIN_P1_POKE6_PX, WIN_P1_POKE6_PY,
		WIN_P1_POKE6_SX, WIN_P1_POKE6_SY, WIN_P1_POKE6_PAL, WIN_P1_POKE6_CGX
	},
};

// 入れ替えページのBMPウィンドウデータ
static const BMPWIN_DAT ChgPage_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME1_S, WIN_CHG_NAME_PX, WIN_CHG_NAME_PY,
		WIN_CHG_NAME_SX, WIN_CHG_NAME_SY, WIN_CHG_NAME_PAL, WIN_CHG_NAME_CGX
	},
	{	// 「いれかえる」
		GF_BGL_FRAME1_S, WIN_CHG_IREKAE_PX, WIN_CHG_IREKAE_PY,
		WIN_CHG_IREKAE_SX, WIN_CHG_IREKAE_SY, WIN_CHG_IREKAE_PAL, WIN_CHG_IREKAE_CGX
	},
	{	// 「つよさをみる」
		GF_BGL_FRAME1_S, WIN_CHG_STATUS_PX, WIN_CHG_STATUS_PY,
		WIN_CHG_STATUS_SX, WIN_CHG_STATUS_SY, WIN_CHG_STATUS_PAL, WIN_CHG_STATUS_CGX
	},
	{	// 「わざをみる」
		GF_BGL_FRAME1_S, WIN_CHG_WAZACHECK_PX, WIN_CHG_WAZACHECK_PY,
		WIN_CHG_WAZACHECK_SX, WIN_CHG_WAZACHECK_SY, WIN_CHG_WAZACHECK_PAL, WIN_CHG_WAZACHECK_CGX
	}
};

// ステータス技選択ページのBMPウィンドウデータ
static const BMPWIN_DAT StWazaSelPage_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME1_S, WIN_ST_NAME_PX, WIN_ST_NAME_PY,
		WIN_ST_NAME_SX, WIN_ST_NAME_SY, WIN_ST_NAME_PAL, WIN_ST_NAME_CGX
	},
	{	// 技１
		GF_BGL_FRAME1_S, WIN_STW_SKILL1_PX, WIN_STW_SKILL1_PY,
		WIN_STW_SKILL1_SX, WIN_STW_SKILL1_SY, WIN_STW_SKILL1_PAL, WIN_STW_SKILL1_CGX
	},
	{	// 技２
		GF_BGL_FRAME1_S, WIN_STW_SKILL2_PX, WIN_STW_SKILL2_PY,
		WIN_STW_SKILL2_SX, WIN_STW_SKILL2_SY, WIN_STW_SKILL2_PAL, WIN_STW_SKILL2_CGX
	},
	{	// 技３
		GF_BGL_FRAME1_S, WIN_STW_SKILL3_PX, WIN_STW_SKILL3_PY,
		WIN_STW_SKILL3_SX, WIN_STW_SKILL3_SY, WIN_STW_SKILL3_PAL, WIN_STW_SKILL3_CGX
	},
	{	// 技４
		GF_BGL_FRAME1_S, WIN_STW_SKILL4_PX, WIN_STW_SKILL4_PY,
		WIN_STW_SKILL4_SX, WIN_STW_SKILL4_SY, WIN_STW_SKILL4_PAL, WIN_STW_SKILL4_CGX
	},

	{	// 「つよさをみる」
		GF_BGL_FRAME1_S, WIN_STW_STATUS_PX, WIN_STW_STATUS_PY,
		WIN_STW_STATUS_SX, WIN_STW_STATUS_SY, WIN_STW_STATUS_PAL, WIN_STW_STATUS_CGX
	},

	{	// 名前（スワップ）
		GF_BGL_FRAME1_S, WIN_ST_NAME_PX, WIN_ST_NAME_PY,
		WIN_ST_NAME_SX, WIN_ST_NAME_SY, WIN_ST_NAME_PAL, WIN_ST_NAME_S_CGX
	},
	{	// 技１（スワップ）
		GF_BGL_FRAME1_S, WIN_STW_SKILL1_PX, WIN_STW_SKILL1_PY,
		WIN_STW_SKILL1_SX, WIN_STW_SKILL1_SY, WIN_STW_SKILL1_PAL, WIN_STW_SKILL1_S_CGX
	},
	{	// 技２（スワップ）
		GF_BGL_FRAME1_S, WIN_STW_SKILL2_PX, WIN_STW_SKILL2_PY,
		WIN_STW_SKILL2_SX, WIN_STW_SKILL2_SY, WIN_STW_SKILL2_PAL, WIN_STW_SKILL2_S_CGX
	},
	{	// 技３（スワップ）
		GF_BGL_FRAME1_S, WIN_STW_SKILL3_PX, WIN_STW_SKILL3_PY,
		WIN_STW_SKILL3_SX, WIN_STW_SKILL3_SY, WIN_STW_SKILL3_PAL, WIN_STW_SKILL3_S_CGX
	},
	{	// 技４（スワップ）
		GF_BGL_FRAME1_S, WIN_STW_SKILL4_PX, WIN_STW_SKILL4_PY,
		WIN_STW_SKILL4_SX, WIN_STW_SKILL4_SY, WIN_STW_SKILL4_PAL, WIN_STW_SKILL4_S_CGX
	},
};

// ステータスメインページのBMPウィンドウデータ
static const BMPWIN_DAT StMainPage_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME1_S, WIN_ST_NAME_PX, WIN_ST_NAME_PY,
		WIN_ST_NAME_SX, WIN_ST_NAME_SY, WIN_ST_NAME_PAL, WIN_ST_NAME_CGX
	},
	{	// 特性名
		GF_BGL_FRAME1_S, WIN_STM_SPANAME_PX, WIN_STM_SPANAME_PY,
		WIN_STM_SPANAME_SX, WIN_STM_SPANAME_SY, WIN_STM_SPANAME_PAL, WIN_STM_SPANAME_CGX
	},
	{	// 特性説明
		GF_BGL_FRAME1_S, WIN_STM_SPAINFO_PX, WIN_STM_SPAINFO_PY,
		WIN_STM_SPAINFO_SX, WIN_STM_SPAINFO_SY, WIN_STM_SPAINFO_PAL, WIN_STM_SPAINFO_CGX
	},
	{	// 道具名
		GF_BGL_FRAME1_S, WIN_STM_ITEMNAME_PX, WIN_STM_ITEMNAME_PY,
		WIN_STM_ITEMNAME_SX, WIN_STM_ITEMNAME_SY, WIN_STM_ITEMNAME_PAL, WIN_STM_ITEMNAME_CGX
	},
	{	// HP値
		GF_BGL_FRAME1_S, WIN_STM_HPNUM_PX, WIN_STM_HPNUM_PY,
		WIN_STM_HPNUM_SX, WIN_STM_HPNUM_SY, WIN_STM_HPNUM_PAL, WIN_STM_HPNUM_CGX
	},
	{	// 攻撃値
		GF_BGL_FRAME1_S, WIN_STM_POWNUM_PX, WIN_STM_POWNUM_PY,
		WIN_STM_POWNUM_SX, WIN_STM_POWNUM_SY, WIN_STM_POWNUM_PAL, WIN_STM_POWNUM_CGX
	},
	{	// 防御値
		GF_BGL_FRAME1_S, WIN_STM_DEFNUM_PX, WIN_STM_DEFNUM_PY,
		WIN_STM_DEFNUM_SX, WIN_STM_DEFNUM_SY, WIN_STM_DEFNUM_PAL, WIN_STM_DEFNUM_CGX
	},
	{	// 素早さ値
		GF_BGL_FRAME1_S, WIN_STM_AGINUM_PX, WIN_STM_AGINUM_PY,
		WIN_STM_AGINUM_SX, WIN_STM_AGINUM_SY, WIN_STM_AGINUM_PAL, WIN_STM_AGINUM_CGX
	},
	{	// 特攻値
		GF_BGL_FRAME1_S, WIN_STM_SPPNUM_PX, WIN_STM_SPPNUM_PY,
		WIN_STM_SPPNUM_SX, WIN_STM_SPPNUM_SY, WIN_STM_SPPNUM_PAL, WIN_STM_SPPNUM_CGX
	},
	{	// 特防値
		GF_BGL_FRAME1_S, WIN_STM_SPDNUM_PX, WIN_STM_SPDNUM_PY,
		WIN_STM_SPDNUM_SX, WIN_STM_SPDNUM_SY, WIN_STM_SPDNUM_PAL, WIN_STM_SPDNUM_CGX
	},
	{	// HPゲージ
		GF_BGL_FRAME1_S, WIN_STM_HPGAGE_PX, WIN_STM_HPGAGE_PY,
		WIN_STM_HPGAGE_SX, WIN_STM_HPGAGE_SY, WIN_STM_HPGAGE_PAL, WIN_STM_HPGAGE_CGX
	},
	{	// レベル値
		GF_BGL_FRAME1_S, WIN_STM_LVNUM_PX, WIN_STM_LVNUM_PY,
		WIN_STM_LVNUM_SX, WIN_STM_LVNUM_SY, WIN_STM_LVNUM_PAL, WIN_STM_LVNUM_CGX
	},
	{	// 次のレベル値
		GF_BGL_FRAME1_S, WIN_STM_NEXTNUM_PX, WIN_STM_NEXTNUM_PY,
		WIN_STM_NEXTNUM_SX, WIN_STM_NEXTNUM_SY, WIN_STM_NEXTNUM_PAL, WIN_STM_NEXTNUM_CGX
	},

	{	// 「HP」
		GF_BGL_FRAME1_S, WIN_STM_HP_PX, WIN_STM_HP_PY,
		WIN_STM_HP_SX, WIN_STM_HP_SY, WIN_STM_HP_PAL, WIN_STM_HP_CGX
	},
	{	// 「こうげき」
		GF_BGL_FRAME1_S, WIN_STM_POW_PX, WIN_STM_POW_PY,
		WIN_STM_POW_SX, WIN_STM_POW_SY, WIN_STM_POW_PAL, WIN_STM_POW_CGX
	},
	{	// 「ぼうぎょ」
		GF_BGL_FRAME1_S, WIN_STM_DEF_PX, WIN_STM_DEF_PY,
		WIN_STM_DEF_SX, WIN_STM_DEF_SY, WIN_STM_DEF_PAL, WIN_STM_DEF_CGX
	},
	{	// 「すばやさ」
		GF_BGL_FRAME1_S, WIN_STM_AGI_PX, WIN_STM_AGI_PY,
		WIN_STM_AGI_SX, WIN_STM_AGI_SY, WIN_STM_AGI_PAL, WIN_STM_AGI_CGX
	},
	{	// 「とくこう」
		GF_BGL_FRAME1_S, WIN_STM_SPP_PX, WIN_STM_SPP_PY,
		WIN_STM_SPP_SX, WIN_STM_SPP_SY, WIN_STM_SPP_PAL, WIN_STM_SPP_CGX
	},
	{	// 「とくぼう」
		GF_BGL_FRAME1_S, WIN_STM_SPD_PX, WIN_STM_SPD_PY,
		WIN_STM_SPD_SX, WIN_STM_SPD_SY, WIN_STM_SPD_PAL, WIN_STM_SPD_CGX
	},
	{	// 「Lv.」
		GF_BGL_FRAME1_S, WIN_STM_LV_PX, WIN_STM_LV_PY,
		WIN_STM_LV_SX, WIN_STM_LV_SY, WIN_STM_LV_PAL, WIN_STM_LV_CGX
	},
	{	// 「つぎのレベルまで」
		GF_BGL_FRAME1_S, WIN_STM_NEXT_PX, WIN_STM_NEXT_PY,
		WIN_STM_NEXT_SX, WIN_STM_NEXT_SY, WIN_STM_NEXT_PAL, WIN_STM_NEXT_CGX
	},
	{	// 「わざをみる」
		GF_BGL_FRAME1_S, WIN_STM_WAZACHECK_PX, WIN_STM_WAZACHECK_PY,
		WIN_STM_WAZACHECK_SX, WIN_STM_WAZACHECK_SY, WIN_STM_WAZACHECK_PAL, WIN_STM_WAZACHECK_CGX
	},

	{	// 名前（スワップ）
		GF_BGL_FRAME1_S, WIN_ST_NAME_PX, WIN_ST_NAME_PY,
		WIN_ST_NAME_SX, WIN_ST_NAME_SY, WIN_ST_NAME_PAL, WIN_ST_NAME_S_CGX
	},
	{	// 特性名（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_SPANAME_PX, WIN_STM_SPANAME_PY,
		WIN_STM_SPANAME_SX, WIN_STM_SPANAME_SY, WIN_STM_SPANAME_PAL, WIN_STM_SPANAME_S_CGX
	},
	{	// 特性説明（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_SPAINFO_PX, WIN_STM_SPAINFO_PY,
		WIN_STM_SPAINFO_SX, WIN_STM_SPAINFO_SY, WIN_STM_SPAINFO_PAL, WIN_STM_SPAINFO_S_CGX
	},
	{	// 道具名（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_ITEMNAME_PX, WIN_STM_ITEMNAME_PY,
		WIN_STM_ITEMNAME_SX, WIN_STM_ITEMNAME_SY, WIN_STM_ITEMNAME_PAL, WIN_STM_ITEMNAME_S_CGX
	},
	{	// HP値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_HPNUM_PX, WIN_STM_HPNUM_PY,
		WIN_STM_HPNUM_SX, WIN_STM_HPNUM_SY, WIN_STM_HPNUM_PAL, WIN_STM_HPNUM_S_CGX
	},
	{	// 攻撃値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_POWNUM_PX, WIN_STM_POWNUM_PY,
		WIN_STM_POWNUM_SX, WIN_STM_POWNUM_SY, WIN_STM_POWNUM_PAL, WIN_STM_POWNUM_S_CGX
	},
	{	// 防御値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_DEFNUM_PX, WIN_STM_DEFNUM_PY,
		WIN_STM_DEFNUM_SX, WIN_STM_DEFNUM_SY, WIN_STM_DEFNUM_PAL, WIN_STM_DEFNUM_S_CGX
	},
	{	// 素早さ値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_AGINUM_PX, WIN_STM_AGINUM_PY,
		WIN_STM_AGINUM_SX, WIN_STM_AGINUM_SY, WIN_STM_AGINUM_PAL, WIN_STM_AGINUM_S_CGX
	},
	{	// 特攻値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_SPPNUM_PX, WIN_STM_SPPNUM_PY,
		WIN_STM_SPPNUM_SX, WIN_STM_SPPNUM_SY, WIN_STM_SPPNUM_PAL, WIN_STM_SPPNUM_S_CGX
	},
	{	// 特防値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_SPDNUM_PX, WIN_STM_SPDNUM_PY,
		WIN_STM_SPDNUM_SX, WIN_STM_SPDNUM_SY, WIN_STM_SPDNUM_PAL, WIN_STM_SPDNUM_S_CGX
	},
	{	// HPゲージ（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_HPGAGE_PX, WIN_STM_HPGAGE_PY,
		WIN_STM_HPGAGE_SX, WIN_STM_HPGAGE_SY, WIN_STM_HPGAGE_PAL, WIN_STM_HPGAGE_S_CGX
	},
	{	// レベル値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_LVNUM_PX, WIN_STM_LVNUM_PY,
		WIN_STM_LVNUM_SX, WIN_STM_LVNUM_SY, WIN_STM_LVNUM_PAL, WIN_STM_LVNUM_S_CGX
	},
	{	// 次のレベル値（スワップ）
		GF_BGL_FRAME1_S, WIN_STM_NEXTNUM_PX, WIN_STM_NEXTNUM_PY,
		WIN_STM_NEXTNUM_SX, WIN_STM_NEXTNUM_SY, WIN_STM_NEXTNUM_PAL, WIN_STM_NEXTNUM_S_CGX
	}
};

// ステータス技詳細ページのBMPウィンドウデータ
static const BMPWIN_DAT StWazaInfoPage_BmpData[] =
{
	{	// 技名
		GF_BGL_FRAME0_S, WIN_P4_SKILL_PX, WIN_P4_SKILL_PY,
		WIN_P4_SKILL_SX, WIN_P4_SKILL_SY, WIN_P4_SKILL_PAL, WIN_P4_SKILL_CGX
	},
	{	// PP/PP
		GF_BGL_FRAME0_S, WIN_P4_PPNUM_PX, WIN_P4_PPNUM_PY,
		WIN_P4_PPNUM_SX, WIN_P4_PPNUM_SY, WIN_P4_PPNUM_PAL, WIN_P4_PPNUM_CGX
	},
	{	// 命中値
		GF_BGL_FRAME0_S, WIN_P4_HITNUM_PX, WIN_P4_HITNUM_PY,
		WIN_P4_HITNUM_SX, WIN_P4_HITNUM_SY, WIN_P4_HITNUM_PAL, WIN_P4_HITNUM_CGX
	},
	{	// 威力値
		GF_BGL_FRAME0_S, WIN_P4_POWNUM_PX, WIN_P4_POWNUM_PY,
		WIN_P4_POWNUM_SX, WIN_P4_POWNUM_SY, WIN_P4_POWNUM_PAL, WIN_P4_POWNUM_CGX
	},
	{	// 技説明
		GF_BGL_FRAME0_S, WIN_P4_INFO_PX, WIN_P4_INFO_PY,
		WIN_P4_INFO_SX, WIN_P4_INFO_SY, WIN_P4_INFO_PAL, WIN_P4_INFO_CGX
	},
	{	// 分類名
		GF_BGL_FRAME0_S, WIN_P4_BRNAME_PX, WIN_P4_BRNAME_PY,
		WIN_P4_BRNAME_SX, WIN_P4_BRNAME_SY, WIN_P4_BRNAME_PAL, WIN_P4_BRNAME_CGX
	},

	{	// 名前
		GF_BGL_FRAME0_S, WIN_P4_NAME_PX, WIN_P4_NAME_PY,
		WIN_P4_NAME_SX, WIN_P4_NAME_SY, WIN_P4_NAME_PAL, WIN_P4_NAME_CGX
	},
	{	// PP
		GF_BGL_FRAME0_S, WIN_P4_PP_PX, WIN_P4_PP_PY,
		WIN_P4_PP_SX, WIN_P4_PP_SY, WIN_P4_PP_PAL, WIN_P4_PP_CGX
	},
	{	// 「めいちゅう」
		GF_BGL_FRAME0_S, WIN_P4_HIT_PX, WIN_P4_HIT_PY,
		WIN_P4_HIT_SX, WIN_P4_HIT_SY, WIN_P4_HIT_PAL, WIN_P4_HIT_CGX
	},
	{	// 「いりょく」
		GF_BGL_FRAME0_S, WIN_P4_POW_PX, WIN_P4_POW_PY,
		WIN_P4_POW_SX, WIN_P4_POW_SY, WIN_P4_POW_PAL, WIN_P4_POW_CGX
	},
	{	// 「ぶんるい」
		GF_BGL_FRAME0_S, WIN_P4_BUNRUI_PX, WIN_P4_BUNRUI_PY,
		WIN_P4_BUNRUI_SX, WIN_P4_BUNRUI_SY, WIN_P4_BUNRUI_PAL, WIN_P4_BUNRUI_CGX
	},

	{	// 技名（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_SKILL_PX, WIN_P4_SKILL_PY,
		WIN_P4_SKILL_SX, WIN_P4_SKILL_SY, WIN_P4_SKILL_PAL, WIN_P4_SKILL_S_CGX
	},
	{	// PP/PP（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_PPNUM_PX, WIN_P4_PPNUM_PY,
		WIN_P4_PPNUM_SX, WIN_P4_PPNUM_SY, WIN_P4_PPNUM_PAL, WIN_P4_PPNUM_S_CGX
	},
	{	// 命中値（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_HITNUM_PX, WIN_P4_HITNUM_PY,
		WIN_P4_HITNUM_SX, WIN_P4_HITNUM_SY, WIN_P4_HITNUM_PAL, WIN_P4_HITNUM_S_CGX
	},
	{	// 威力値（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_POWNUM_PX, WIN_P4_POWNUM_PY,
		WIN_P4_POWNUM_SX, WIN_P4_POWNUM_SY, WIN_P4_POWNUM_PAL, WIN_P4_POWNUM_S_CGX
	},
	{	// 技説明（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_INFO_PX, WIN_P4_INFO_PY,
		WIN_P4_INFO_SX, WIN_P4_INFO_SY, WIN_P4_INFO_PAL, WIN_P4_INFO_S_CGX
	},
	{	// 分類名（スワップ）
		GF_BGL_FRAME0_S, WIN_P4_BRNAME_PX, WIN_P4_BRNAME_PY,
		WIN_P4_BRNAME_SX, WIN_P4_BRNAME_SY, WIN_P4_BRNAME_PAL, WIN_P4_BRNAME_S_CGX
	},
};

// ページ５のBMPウィンドウデータ
static const BMPWIN_DAT Page5_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME0_S, WIN_P5_NAME_PX, WIN_P5_NAME_PY,
		WIN_P5_NAME_SX, WIN_P5_NAME_SY, WIN_P5_NAME_PAL, WIN_P5_NAME_CGX
	},
	{	// 技１
		GF_BGL_FRAME0_S, WIN_P5_SKILL1_PX, WIN_P5_SKILL1_PY,
		WIN_P5_SKILL1_SX, WIN_P5_SKILL1_SY, WIN_P5_SKILL1_PAL, WIN_P5_SKILL1_CGX
	},
	{	// 技２
		GF_BGL_FRAME0_S, WIN_P5_SKILL2_PX, WIN_P5_SKILL2_PY,
		WIN_P5_SKILL2_SX, WIN_P5_SKILL2_SY, WIN_P5_SKILL2_PAL, WIN_P5_SKILL2_CGX
	},
	{	// 技３
		GF_BGL_FRAME0_S, WIN_P5_SKILL3_PX, WIN_P5_SKILL3_PY,
		WIN_P5_SKILL3_SX, WIN_P5_SKILL3_SY, WIN_P5_SKILL3_PAL, WIN_P5_SKILL3_CGX
	},
	{	// 技４
		GF_BGL_FRAME0_S, WIN_P5_SKILL4_PX, WIN_P5_SKILL4_PY,
		WIN_P5_SKILL4_SX, WIN_P5_SKILL4_SY, WIN_P5_SKILL4_PAL, WIN_P5_SKILL4_CGX
	},
	{	// 技５
		GF_BGL_FRAME0_S, WIN_P5_SKILL5_PX, WIN_P5_SKILL5_PY,
		WIN_P5_SKILL5_SX, WIN_P5_SKILL5_SY, WIN_P5_SKILL5_PAL, WIN_P5_SKILL5_CGX
	},
};

// ページ６のBMPウィンドウデータ
static const BMPWIN_DAT Page6_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME1_S, WIN_P6_NAME_PX, WIN_P6_NAME_PY,
		WIN_P6_NAME_SX, WIN_P6_NAME_SY, WIN_P6_NAME_PAL, WIN_P6_NAME_CGX
	},
	{	// 技名
		GF_BGL_FRAME1_S, WIN_P6_SKILL_PX, WIN_P6_SKILL_PY,
		WIN_P6_SKILL_SX, WIN_P6_SKILL_SY, WIN_P6_SKILL_PAL, WIN_P6_SKILL_CGX
	},
	{	// PP
		GF_BGL_FRAME1_S, WIN_P6_PP_PX, WIN_P6_PP_PY,
		WIN_P6_PP_SX, WIN_P6_PP_SY, WIN_P6_PP_PAL, WIN_P6_PP_CGX
	},
	{	// PP/PP
		GF_BGL_FRAME1_S, WIN_P6_PPNUM_PX, WIN_P6_PPNUM_PY,
		WIN_P6_PPNUM_SX, WIN_P6_PPNUM_SY, WIN_P6_PPNUM_PAL, WIN_P6_PPNUM_CGX
	},
	{	// 「めいちゅう」
		GF_BGL_FRAME1_S, WIN_P6_HIT_PX, WIN_P6_HIT_PY,
		WIN_P6_HIT_SX, WIN_P6_HIT_SY, WIN_P6_HIT_PAL, WIN_P6_HIT_CGX
	},
	{	// 「いりょく」
		GF_BGL_FRAME1_S, WIN_P6_POW_PX, WIN_P6_POW_PY,
		WIN_P6_POW_SX, WIN_P6_POW_SY, WIN_P6_POW_PAL, WIN_P6_POW_CGX
	},
	{	// 命中値
		GF_BGL_FRAME1_S, WIN_P6_HITNUM_PX, WIN_P6_HITNUM_PY,
		WIN_P6_HITNUM_SX, WIN_P6_HITNUM_SY, WIN_P6_HITNUM_PAL, WIN_P6_HITNUM_CGX
	},
	{	// 威力値
		GF_BGL_FRAME1_S, WIN_P6_POWNUM_PX, WIN_P6_POWNUM_PY,
		WIN_P6_POWNUM_SX, WIN_P6_POWNUM_SY, WIN_P6_POWNUM_PAL, WIN_P6_POWNUM_CGX
	},
	{	// 技説明
		GF_BGL_FRAME1_S, WIN_P6_INFO_PX, WIN_P6_INFO_PY,
		WIN_P6_INFO_SX, WIN_P6_INFO_SY, WIN_P6_INFO_PAL, WIN_P6_INFO_CGX
	},
	{	// 「ぶんるい」
		GF_BGL_FRAME1_S, WIN_P6_BUNRUI_PX, WIN_P6_BUNRUI_PY,
		WIN_P6_BUNRUI_SX, WIN_P6_BUNRUI_SY, WIN_P6_BUNRUI_PAL, WIN_P6_BUNRUI_CGX
	},
	{	// 分類名
		GF_BGL_FRAME1_S, WIN_P6_BRNAME_PX, WIN_P6_BRNAME_PY,
		WIN_P6_BRNAME_SX, WIN_P6_BRNAME_SY, WIN_P6_BRNAME_PAL, WIN_P6_BRNAME_CGX
	},
	{	// 「わすれる」
		GF_BGL_FRAME1_S, WIN_P6_WASURERU_PX, WIN_P6_WASURERU_PY,
		WIN_P6_WASURERU_SX, WIN_P6_WASURERU_SY, WIN_P6_WASURERU_PAL, WIN_P6_WASURERU_CGX
	}
};

// 技回復ページのBMPウィンドウデータ
static const BMPWIN_DAT PPRcvPage_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME0_S, WIN_P7_NAME_PX, WIN_P7_NAME_PY,
		WIN_P7_NAME_SX, WIN_P7_NAME_SY, WIN_P7_NAME_PAL, WIN_P7_NAME_CGX
	},
	{	// 技１
		GF_BGL_FRAME0_S, WIN_P7_SKILL1_PX, WIN_P7_SKILL1_PY,
		WIN_P7_SKILL1_SX, WIN_P7_SKILL1_SY, WIN_P7_SKILL1_PAL, WIN_P7_SKILL1_CGX
	},
	{	// 技２
		GF_BGL_FRAME0_S, WIN_P7_SKILL2_PX, WIN_P7_SKILL2_PY,
		WIN_P7_SKILL2_SX, WIN_P7_SKILL2_SY, WIN_P7_SKILL2_PAL, WIN_P7_SKILL2_CGX
	},
	{	// 技３
		GF_BGL_FRAME0_S, WIN_P7_SKILL3_PX, WIN_P7_SKILL3_PY,
		WIN_P7_SKILL3_SX, WIN_P7_SKILL3_SY, WIN_P7_SKILL3_PAL, WIN_P7_SKILL3_CGX
	},
	{	// 技４
		GF_BGL_FRAME0_S, WIN_P7_SKILL4_PX, WIN_P7_SKILL4_PY,
		WIN_P7_SKILL4_SX, WIN_P7_SKILL4_SY, WIN_P7_SKILL4_PAL, WIN_P7_SKILL4_CGX
	},
};

// ページ８のBMPウィンドウデータ
static const BMPWIN_DAT Page8_BmpData[] =
{
	{	// 名前
		GF_BGL_FRAME1_S, WIN_P8_NAME_PX, WIN_P8_NAME_PY,
		WIN_P8_NAME_SX, WIN_P8_NAME_SY, WIN_P8_NAME_PAL, WIN_P8_NAME_CGX
	},
	{	// 技名
		GF_BGL_FRAME1_S, WIN_P8_SKILL_PX, WIN_P8_SKILL_PY,
		WIN_P8_SKILL_SX, WIN_P8_SKILL_SY, WIN_P8_SKILL_PAL, WIN_P8_SKILL_CGX
	},
	{	// PP
		GF_BGL_FRAME1_S, WIN_P8_PP_PX, WIN_P8_PP_PY,
		WIN_P8_PP_SX, WIN_P8_PP_SY, WIN_P8_PP_PAL, WIN_P8_PP_CGX
	},
	{	// PP/PP
		GF_BGL_FRAME1_S, WIN_P8_PPNUM_PX, WIN_P8_PPNUM_PY,
		WIN_P8_PPNUM_SX, WIN_P8_PPNUM_SY, WIN_P8_PPNUM_PAL, WIN_P8_PPNUM_CGX
	},
	{	// 「アピールポイント」
		GF_BGL_FRAME1_S, WIN_P8_APP_PX, WIN_P8_APP_PY,
		WIN_P8_APP_SX, WIN_P8_APP_SY, WIN_P8_APP_PAL, WIN_P8_APP_CGX
	},
	{	// 技説明
		GF_BGL_FRAME1_S, WIN_P8_INFO_PX, WIN_P8_INFO_PY,
		WIN_P8_INFO_SX, WIN_P8_INFO_SY, WIN_P8_INFO_PAL, WIN_P8_INFO_CGX
	},
	{	// 「わすれる」
		GF_BGL_FRAME1_S, WIN_P8_WASURERU_PX, WIN_P8_WASURERU_PY,
		WIN_P8_WASURERU_SX, WIN_P8_WASURERU_SY, WIN_P8_WASURERU_PAL, WIN_P8_WASURERU_CGX
	},
};


// ポケモン名のメッセージID
static const u32 NameMsgID_Tbl[] = {
	mes_b_plist_01_001,
	mes_b_plist_01_101,
	mes_b_plist_01_201,
	mes_b_plist_01_301,
	mes_b_plist_01_401,
	mes_b_plist_01_501
};

// 技名のメッセージID
static const u32 WazaMsgID_Tbl[] = {
	mes_b_plist_05_100,
	mes_b_plist_05_200,
	mes_b_plist_05_300,
	mes_b_plist_05_400,
	mes_b_plist_05_500
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
void BattlePokeList_BmpInit( BPLIST_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &CommBmpData[i] );
	}
	BattlePokeList_BmpAdd( wk, wk->page );

/*
	OS_Printf( "WIN_PS_CGX_START : %d\n", WIN_PS_CGX_START );
	OS_Printf( "WIN_P1_POKE6_CGX : %d\n", WIN_P1_POKE6_CGX+WIN_P1_POKE6_SX*WIN_P1_POKE6_SY );
	OS_Printf( "WIN_STW_SKILL4_S_CGX : %d\n", WIN_STW_SKILL4_S_CGX+WIN_STW_SKILL4_SX*WIN_STW_SKILL4_SY );
	OS_Printf( "WIN_STM_NEXTNUM_CGX : %d\n", WIN_STM_NEXTNUM_CGX+WIN_STM_NEXTNUM_SX+WIN_STM_NEXTNUM_SY );
	OS_Printf( "WIN_STM_NEXTNUM_S_CGX : %d\n", WIN_STM_NEXTNUM_S_CGX+WIN_STM_NEXTNUM_SX+WIN_STM_NEXTNUM_SY );
	OS_Printf( "WIN_P4_BRNAME_S_CGX : %d\n", WIN_P4_BRNAME_S_CGX+WIN_P4_BRNAME_SX*WIN_P4_BRNAME_SY );
	OS_Printf( "WIN_P7_SKILL4_CGX : %d\n", WIN_P7_SKILL4_CGX + WIN_P7_SKILL4_SX * WIN_P7_SKILL4_SY );
	OS_Printf( "WIN_P5_SKILL5_CGX : %d\n", WIN_P5_SKILL5_CGX + WIN_P5_SKILL5_SX * WIN_P5_SKILL5_SY );
	OS_Printf( "WIN_P6_BRNAME_CGX : %d\n", WIN_P6_BRNAME_CGX + WIN_P6_BRNAME_SX * WIN_P6_BRNAME_SY );
	OS_Printf( "WIN_P8_INFO_CGX : %d\n", WIN_P8_INFO_CGX + WIN_P8_INFO_SX * WIN_P8_INFO_SY );
*/
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
void BattlePokeList_BmpAdd( BPLIST_WORK * wk, u32 page )
{
	const BMPWIN_DAT * dat;
	u8	i;

	switch( page ){
	case BPLIST_PAGE_SELECT:		// ポケモン選択ページ
		dat = Page1_BmpData;
		wk->bmp_add_max = WIN_P1_MAX;
		break;

	case BPLIST_PAGE_POKE_CHG:		// ポケモン入れ替えページ
		dat = ChgPage_BmpData;
		wk->bmp_add_max = WIN_CHG_MAX;
		break;

	case BPLIST_PAGE_MAIN:			// ステータスメインページ
		dat = StMainPage_BmpData;
		wk->bmp_add_max = WIN_P3_MAX;
		break;

	case BPLIST_PAGE_WAZA_SEL:		// ステータス技選択ページ
		dat = StWazaSelPage_BmpData;
		wk->bmp_add_max = WIN_STW_MAX;
		break;

	case BPLIST_PAGE_SKILL:			// ステータス技ページ
		dat = StWazaInfoPage_BmpData;
		wk->bmp_add_max = WIN_P4_MAX;
		break;

	case BPLIST_PAGE_PP_RCV:		// PP回復技選択ページ
		dat = PPRcvPage_BmpData;
		wk->bmp_add_max = WIN_P7_MAX;
		break;

	case BPLIST_PAGE_WAZASET_BS:	// ステータス技忘れ１ページ（戦闘技選択）
	case BPLIST_PAGE_WAZASET_CS:	// ステータス技忘れ４ページ（コンテスト技選択）
		dat = Page5_BmpData;
		wk->bmp_add_max = WIN_P5_MAX;
		break;

	case BPLIST_PAGE_WAZASET_BI:	// ステータス技忘れ２ページ（戦闘技詳細）
		dat = Page6_BmpData;
		wk->bmp_add_max = WIN_P6_MAX;
		break;

	case BPLIST_PAGE_WAZASET_CI:	// ステータス技忘れ３ページ（コンテスト技詳細）
		dat = Page8_BmpData;
		wk->bmp_add_max = WIN_P8_MAX;
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
void BattlePokeList_BmpFree( BPLIST_WORK * wk )
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
void BattlePokeList_BmpFreeAll( BPLIST_WORK * wk )
{
	u32	i;

	GF_BGL_BmpWinFree( wk->add_win, wk->bmp_add_max );
	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
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
void BattlePokeList_BmpWrite( BPLIST_WORK * wk, u32 page )
{
	switch( page ){
	case BPLIST_PAGE_SELECT:		// ポケモン選択ページ
		BPL_Page1BmpWrite( wk );
		break;
	case BPLIST_PAGE_POKE_CHG:		// ポケモン入れ替えページ
		BPL_ChgPageBmpWrite( wk );
		break;
	case BPLIST_PAGE_MAIN:			// ステータスメインページ
		BPL_StMainPageBmpWrite( wk );
		break;
	case BPLIST_PAGE_WAZA_SEL:		// ステータス技選択ページ
		BPL_StWazaSelPageBmpWrite( wk );
		break;
	case BPLIST_PAGE_SKILL:			// ステータス技詳細ページ
		BPL_StWazaInfoPageBmpWrite( wk );
		break;

	case BPLIST_PAGE_PP_RCV:		// PP回復技選択ページ
		BPL_PPRcvPageBmpWrite( wk );
		break;

	case BPLIST_PAGE_WAZASET_BS:	// ステータス技忘れ１ページ（戦闘技選択）
	case BPLIST_PAGE_WAZASET_CS:	// ステータス技忘れ４ページ（コンテスト技選択）
		BPL_WazaDelSelPageBmpWrite( wk );
		break;

	case BPLIST_PAGE_WAZASET_BI:	// ステータス技忘れ２ページ（戦闘技詳細）
		BPL_Page6BmpWrite( wk );
		break;

	case BPLIST_PAGE_WAZASET_CI:	// ステータス技忘れ３ページ（コンテスト技詳細）
		BPL_Page8BmpWrite( wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン名表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_NamePut( BPLIST_WORK * wk, u32 idx, u32 fidx, u16 pos, u8 px, u8 py )
{
	GF_BGL_BMPWIN * win;
	BPL_POKEDATA * pd;
	STRBUF * exp;
	STRBUF * str;
	u32	sex_px;

	win = &wk->add_win[idx];
	pd  = &wk->poke[pos];
	exp = STRBUF_Create( BUFLEN_POKEMON_NAME, wk->dat->heap );
	str = MSGMAN_AllocString( wk->mman, NameMsgID_Tbl[pos] );

	WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pd->pp) );
	WORDSET_ExpandStr( wk->wset, exp, str );

	if( fidx == FONT_SYSTEM ){
		GF_STR_PrintColor( win, fidx, exp, px, py, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	}else{
		GF_STR_PrintColor( win, fidx, exp, px, py, MSG_NO_PUT, PCOL_BTN, NULL );
	}

	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	// 性別
	if( pd->sex_put == 0 && pd->egg == 0 ){
		if( pd->sex == PARA_MALE ){
			str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_502 );
			sex_px = GF_BGL_BmpWinGet_SizeX(win)*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,str,0);
			if( fidx == FONT_SYSTEM ){
				GF_STR_PrintColor(
					win, FONT_SYSTEM, str, sex_px, py, MSG_NO_PUT, PCOL_N_BLUE, NULL );
			}else{
				GF_STR_PrintColor(
					win, FONT_SYSTEM, str, sex_px, py, MSG_NO_PUT, PCOL_B_BLUE, NULL );
			}
			STRBUF_Delete( str );
		}else if( pd->sex == PARA_FEMALE ){
			str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_503 );
			sex_px = GF_BGL_BmpWinGet_SizeX(win)*8-FontProc_GetPrintStrWidth(FONT_SYSTEM,str,0);
			if( fidx == FONT_SYSTEM ){
				GF_STR_PrintColor(
					win, FONT_SYSTEM, str, sex_px, py, MSG_NO_PUT, PCOL_N_RED, NULL );
			}else{
				GF_STR_PrintColor(
					win, FONT_SYSTEM, str, sex_px, py, MSG_NO_PUT, PCOL_B_RED, NULL );
			}
			STRBUF_Delete( str );
		}
	}

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * レベル表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_LvPut( BPLIST_WORK * wk, u32 idx, u16 pos, u8 px, u8 py )
{
	BPL_POKEDATA * pd = &wk->poke[pos];

	NUMFONT_WriteSet(
		wk->nfnt, NUMFONT_MARK_LV, pd->lv, 3, NUMFONT_MODE_LEFT, &wk->add_win[idx], px+8, py );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * HP表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_HPPut( BPLIST_WORK * wk, u32 idx, u16 pos, u8 px, u8 py )
{
	BPL_POKEDATA * pd = &wk->poke[pos];

	NUMFONT_WriteNumber(
		wk->nfnt, pd->hp, 3, NUMFONT_MODE_SPACE, &wk->add_win[idx], px, py );
	NUMFONT_WriteMark(
		wk->nfnt, NUMFONT_MARK_SLASH, &wk->add_win[idx], px+NUMFONT_NUM_WIDTH*3, py );
	NUMFONT_WriteNumber(
		wk->nfnt, pd->mhp, 3, NUMFONT_MODE_LEFT,
		&wk->add_win[idx], px+NUMFONT_NUM_WIDTH*3+8, py );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * HPゲージ表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_HPGagePut( BPLIST_WORK * wk, u32 idx, u16 pos, u8 px, u8 py )
{
	BPL_POKEDATA * pd;
	u8	col=1;
	u8	dot;

	pd  = &wk->poke[pos];
	col = 1;
	dot = GetNumDotto( pd->hp, pd->mhp, BPL_HP_DOTTO_MAX );

	switch( GetHPGaugeDottoColor( pd->hp, pd->mhp, BPL_HP_DOTTO_MAX ) ){
	case HP_DOTTO_NULL:
		GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
		return;
	case HP_DOTTO_MAX:		// 緑
	case HP_DOTTO_GREEN:
		col = HP_GAGE_COL_G1;
		break;
	case HP_DOTTO_YELLOW:	// 黄
		col = HP_GAGE_COL_Y1;
		break;
	case HP_DOTTO_RED:		// 赤
		col = HP_GAGE_COL_R1;
		break;
	}

	GF_BGL_BmpWinFill( &wk->add_win[idx], col+1, px, py+1, dot, 1 );
	GF_BGL_BmpWinFill( &wk->add_win[idx], col,   px, py+2, dot, 2 );
	GF_BGL_BmpWinFill( &wk->add_win[idx], col+1, px, py+4, dot, 1 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * 特性表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_TokuseiPut( BPLIST_WORK * wk, u32 idx, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * exp;
	STRBUF * str;

	pd  = &wk->poke[pos];
	exp = STRBUF_Create( BUFLEN_POKEMON_ABILITY_NAME, wk->dat->heap );
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_000 );

	WORDSET_RegisterTokuseiName( wk->wset, 0, pd->spa );
	WORDSET_ExpandStr( wk->wset, exp, str );

	GF_STR_PrintColor(
		&wk->add_win[idx], FONT_SYSTEM, exp, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ItemPut( BPLIST_WORK * wk, u32 idx, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * exp;
	STRBUF * str;

	pd  = &wk->poke[pos];
	if( pd->item == 0 ){
		exp = MSGMAN_AllocString( wk->mman, mes_b_plist_02_600 );
	}else{
		exp = STRBUF_Create( BUFLEN_ITEM_NAME, wk->dat->heap );
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_001 );
		WORDSET_RegisterItemName( wk->wset, 0, pd->item );
		WORDSET_ExpandStr( wk->wset, exp, str );
		STRBUF_Delete( str );
	}
	GF_STR_PrintColor(
		&wk->add_win[idx], FONT_SYSTEM, exp, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );

	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * 技名表示
 *
 * @param	wk		ワーク
 * @param	waza	技番号
 * @param	widx	ウィンドウインデックス
 * @param	midx	メッセージインデックス
 * @param	fidx	フォントインデックス
 * @param	py		Y座標
 * @param	col		カラー
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaNamePut(
				BPLIST_WORK * wk, u32 waza, u32 widx, u32 midx, u16 fidx, u16 py, u32 col )
{
	GF_BGL_BMPWIN * win;
	STRBUF * exp;
	STRBUF * str;
	u32	px;

	win = &wk->add_win[widx];

	exp = STRBUF_Create( BUFLEN_WAZA_NAME, wk->dat->heap );
	str = MSGMAN_AllocString( wk->mman, midx );

	WORDSET_RegisterWazaName( wk->wset, 0, waza );
	WORDSET_ExpandStr( wk->wset, exp, str );
	if( fidx == FONT_BUTTON ){
		px = (GF_BGL_BmpWinGet_SizeX(win)*8-FontProc_GetPrintStrWidth(fidx,exp,0))/2;
	}else{
		px = 0;
	}

	GF_STR_PrintColor( win, fidx, exp, px, py, MSG_NO_PUT, col, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 「PP」表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PPPut( BPLIST_WORK * wk, u16 idx, u8 px, u8 py )
{
	STRBUF * str;

	str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_500 );
	GF_STR_PrintColor(
		&wk->add_win[idx], FONT_SYSTEM, str, px, py, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * PP値表示
 *
 * @param	wk		ワーク
 * @param	waza	技データ
 * @param	idx		ウィンドウインデックス
 * @param	px		表示X座標
 * @param	py		表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PPNumPut( BPLIST_WORK * wk, BPL_POKEWAZA * waza, u16 idx, u8 px, u8 py )
{
	NUMFONT_WriteNumber(
		wk->nfnt, waza->pp, 2, NUMFONT_MODE_SPACE, &wk->add_win[idx], px, py );
	NUMFONT_WriteMark(
		wk->nfnt, NUMFONT_MARK_SLASH, &wk->add_win[idx], px+NUMFONT_NUM_WIDTH*2, py );
	NUMFONT_WriteNumber(
		wk->nfnt, waza->mpp, 2, NUMFONT_MODE_LEFT,
		&wk->add_win[idx], px+NUMFONT_NUM_WIDTH*2+8, py );

	GF_BGL_BmpWinOnVReq( &wk->add_win[idx] );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン選択ページコメント表示
 *
 * @param	wk		ワーク
 * @param	midx	メッセージインデックス
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeSelStrPut( BPLIST_WORK * wk, u32 midx )
{
	STRBUF * str;

	BmpTalkWinWrite(
		&wk->win[WIN_COMMENT], WINDOW_TRANS_OFF, TALK_WIN_CGX_POS, BPL_PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_COMMENT], 15 );

	str = MSGMAN_AllocString( wk->mman, midx );
	GF_STR_PrintColor(
		&wk->win[WIN_COMMENT], FONT_TALK, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_COMMENT] );
}

//--------------------------------------------------------------------------------------------
/**
 * 「いれかえ」表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	IREKAE_PY	( 8 )

static void BPL_StrIrekaePut( BPLIST_WORK * wk )
{
	STRBUF * str;
	u32	siz;

	str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_501 );
	siz = FontProc_GetPrintStrWidth( FONT_BUTTON, str, 0 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_CHG_IREKAE], FONT_BUTTON, str,
		(WIN_CHG_IREKAE_SX*8-siz)/2, IREKAE_PY, MSG_NO_PUT, PCOL_BTN, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_CHG_IREKAE] );
}

//--------------------------------------------------------------------------------------------
/**
 * コマンド表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	COMMAND_STR_PY	( 6 )

static void BPL_StrCommandPut( BPLIST_WORK * wk, u32 wid, u32 mid )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->add_win[wid];
	str = MSGMAN_AllocString( wk->mman, mid );
	siz = FontProc_GetPrintStrWidth( FONT_BUTTON, str, 0 );
	GF_STR_PrintColor(
		win, FONT_BUTTON, str,
		(GF_BGL_BmpWinGet_SizeX(win)*8-siz)/2, COMMAND_STR_PY, MSG_NO_PUT, PCOL_BTN, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３のレベル表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_LvPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	px;
	u16	swap;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「Lv.」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_000 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_LV], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// レベル値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_001 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_LVNUM+swap], FONT_SYSTEM, exp, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	// 「つぎのレベルまで」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_100 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_NEXT], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 次のレベル値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_101 );
	exp = STRBUF_Create( (6+1)*2, wk->dat->heap );	// (6桁+EOM_)x2(ローカライズ用に一応)
/* ルビサファの育て屋でLv100以上の経験値になるため、マイナス表示になってしまう不具合対処 */
#if T1653_060815_FIX	// 対処後
	if( pd->lv < 100 ){
		WORDSET_RegisterNumber(
			wk->wset, 0, pd->next_lv_exp - pd->now_exp,
			6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	}else{
		WORDSET_RegisterNumber(
			wk->wset, 0, 0, 6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	}
#else					// 対処前
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->next_lv_exp - pd->now_exp, 
		6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
#endif	// T1653_060815_FIX
	WORDSET_ExpandStr( wk->wset, exp, str );
	px = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_NEXTNUM+swap] ) * 8
			- FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_NEXTNUM+swap],
		FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_LV] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_LVNUM+swap] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_NEXT] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_NEXTNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の攻撃表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_PowPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	swap;
	u8	siz;
	u8	px;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「こうげき」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_400 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_POW], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 攻撃値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_401 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->pow, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	px  = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_POWNUM+swap] ) * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_POWNUM+swap], FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_POW] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_POWNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の防御表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_DefPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	swap;
	u8	siz;
	u8	px;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「ぼうぎょ」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_500 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_DEF], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 防御値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_501 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->def, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	px  = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_DEFNUM+swap] ) * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_DEFNUM+swap], FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_DEF] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_DEFNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の素早さ表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_AgiPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	swap;
	u8	siz;
	u8	px;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「すばやさ」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_800 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_AGI], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 素早さ値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_801 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->agi, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	px  = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_AGINUM+swap] ) * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_AGINUM+swap], FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_AGI] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_AGINUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の特攻表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_SppPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	swap;
	u8	siz;
	u8	px;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「とくこう」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_600 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_SPP], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 特攻値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_601 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->spp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	px  = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_SPPNUM+swap] ) * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_SPPNUM+swap], FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_SPP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_SPPNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の特防表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_SpdPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u16	swap;
	u8	siz;
	u8	px;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「とくぼう」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_700 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_SPD], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 特防値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_701 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->spd, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	px  = GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_SPDNUM+swap] ) * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_SPDNUM+swap], FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_SPD] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_SPDNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３のHP表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_HPPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	STRBUF * str;
	STRBUF * exp;
	u32	sra_siz, tmp_siz;
	u16	px;
	u16	swap;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	// 「HP」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_300 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_HP], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// 「/」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_303 );
	sra_siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px = (GF_BGL_BmpWinGet_SizeX( &wk->add_win[WIN_P3_HPNUM] )*8-sra_siz)/2;
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_HPNUM+swap], FONT_SYSTEM, str, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	// HP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_301 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->hp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	tmp_siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_HPNUM+swap], FONT_SYSTEM, exp,
		px-tmp_siz, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	// 最大HP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_03_302 );
	exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, pd->mhp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_HPNUM+swap], FONT_SYSTEM, exp,
		px+sra_siz, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_HP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_HPNUM+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ３の特性表示
 *
 * @param	wk		ワーク
 * @param	pos		ポケモン位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_P3_TokuseiInfoPut( BPLIST_WORK * wk, u32 pos )
{
	BPL_POKEDATA * pd;
	MSGDATA_MANAGER * man;
	STRBUF * str;
	u32	swap;

	pd   = &wk->poke[pos];
	swap = WIN_P3_NAME_S * wk->bmp_swap;

	man = MSGMAN_Create(
			MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_tokuseiinfo_dat, wk->dat->heap );
	str = MSGMAN_AllocString( man, pd->spa );
	GF_STR_PrintColor(
		&wk->add_win[WIN_P3_SPAINFO+swap],
		FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	MSGMAN_Delete( man );
	GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P3_SPAINFO+swap] );
}

//--------------------------------------------------------------------------------------------
/**
 * 「めいちゅう」表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaHitStrPut( BPLIST_WORK * wk, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->add_win[idx];
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_200 );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 技の命中値表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	hit		命中値
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaHitNumPut( BPLIST_WORK * wk, u32 idx, u32 hit )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u16	siz;
	u16	px;

	win = &wk->add_win[idx];

	if( hit == 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_102 );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
		px  = GF_BGL_BmpWinGet_SizeX(win) * 8 - siz;
		GF_STR_PrintColor( win, FONT_SYSTEM, str, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
		STRBUF_Delete( str );
	}else{
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_201 );
		exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
		WORDSET_RegisterNumber(
			wk->wset, 0, hit, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, exp, str );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
		px  = GF_BGL_BmpWinGet_SizeX(win) * 8 - siz;
		GF_STR_PrintColor( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
		STRBUF_Delete( str );
		STRBUF_Delete( exp );
	}

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 「いりょく」表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaPowStrPut( BPLIST_WORK * wk, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->add_win[idx];
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_100 );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 技の威力値表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	pow		威力値
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaPowNumPut( BPLIST_WORK * wk, u32 idx, u32 pow )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u16	siz;
	u16	px;

	win = &wk->add_win[idx];

	if( pow <= 1 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_102 );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
		px  = GF_BGL_BmpWinGet_SizeX(win) * 8 - siz;
		GF_STR_PrintColor( win, FONT_SYSTEM, str, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
		STRBUF_Delete( str );
	}else{
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_101 );
		exp = STRBUF_Create( (3+1)*2, wk->dat->heap );	// (3桁+EOM_)x2(ローカライズ用に一応)
		WORDSET_RegisterNumber(
			wk->wset, 0, pow, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, exp, str );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
		px  = GF_BGL_BmpWinGet_SizeX(win) * 8 - siz;
		GF_STR_PrintColor( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
		STRBUF_Delete( str );
		STRBUF_Delete( exp );
	}

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 技説明表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	waza	技ID
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaInfoPut( BPLIST_WORK * wk, u32 idx, u32 waza )
{
	MSGDATA_MANAGER * man;
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->add_win[idx];
	man = MSGMAN_Create(
			MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazainfo_dat, wk->dat->heap );
	str = MSGMAN_AllocString( man, waza );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	MSGMAN_Delete( man );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * コンテスト技説明表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	waza	技ID
 *
 * @return	none
 *
 *	ページ８で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_ContestWazaInfoPut( BPLIST_WORK * wk, u32 idx, u32 waza )
{
	MSGDATA_MANAGER * man;
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	ap_no;
	u32	msg_id;

	win = &wk->add_win[idx];

	ap_no  = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
	msg_id = ConTool_GetListAPSetumeiMsgID( ap_no );

	man = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_wazaexplain_dat, wk->dat->heap );

	str = MSGMAN_AllocString( man, msg_id );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	MSGMAN_Delete( man );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 「ぶんるい」表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaBunruiStrPut( BPLIST_WORK * wk, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u16	siz;
	u16	px;

	win = &wk->add_win[idx];
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_300 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px  = ( GF_BGL_BmpWinGet_SizeX(win) * 8 - siz ) / 2;
	GF_STR_PrintColor( win, FONT_SYSTEM, str, px, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 分類種類表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	kind	分類種類
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaKindPut( BPLIST_WORK * wk, u32 idx, u32 kind )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->add_win[idx];

	switch( kind ){
	case 0:		// 物理
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_301 );
		break;
	case 1:		// 変化
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_303 );
		break;
	case 2:		// 特殊
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_302 );
	}
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 技PP表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 * @param	npp		現在のPP
 * @param	mpp		最大PP
 *
 * @return	none
 *
 *	ページ４・６で使用
 */
//--------------------------------------------------------------------------------------------
static void BPL_WazaPPPut( BPLIST_WORK * wk, u32 idx, u32 npp, u32 mpp )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u32	sra_siz, tmp_siz;
	u32	px;

	win = &wk->add_win[idx];

	// 「/」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_004 );
	sra_siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px = ( GF_BGL_BmpWinGet_SizeX(win) * 8 - sra_siz ) / 2;
	GF_STR_PrintColor( win, FONT_SYSTEM, str, px, 0, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );
	// PP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_002 );
	exp = STRBUF_Create( (2+1)*2, wk->dat->heap );	// (2桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, npp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	tmp_siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, px-tmp_siz, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	// 最大PP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_003 );
	exp = STRBUF_Create( (2+1)*2, wk->dat->heap );	// (2桁+EOM_)x2(ローカライズ用に一応)
	WORDSET_RegisterNumber(
		wk->wset, 0, mpp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, px+sra_siz, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ５のPP値表示
 *
 * @param	wk		ワーク
 * @param	waza	技ID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P5_PPNUM5_PX	( 56 )
#define	P5_PPNUM5_PY	( 32 )

static void BPL_P5_PPNumPut( BPLIST_WORK * wk, u32 waza )
{
	GF_BGL_BMPWIN * win;
	u32	pp;

	win = &wk->add_win[WIN_P5_SKILL5];
	pp  = WT_WazaDataParaGet( waza, ID_WTD_pp );

	NUMFONT_WriteNumber( wk->nfnt, pp, 2, NUMFONT_MODE_SPACE, win, P5_PPNUM5_PX, P5_PPNUM5_PY );
	NUMFONT_WriteNumber(
		wk->nfnt, pp, 2, NUMFONT_MODE_LEFT,
		win, P5_PPNUM5_PX+NUMFONT_NUM_WIDTH*2+8, P5_PPNUM5_PY );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * 「わすれる」表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 *
 * @return	none
 *
 *	ページ６で使用
 */
//--------------------------------------------------------------------------------------------
#define	P6_WASURERU_PY	( 6 )

static void BPL_WasureruStrPut( BPLIST_WORK * wk, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->add_win[idx];

	if( wk->dat->sel_wp == 4 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_05_001 );
	}else{
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_05_000 );
	}
	siz = FontProc_GetPrintStrWidth( FONT_BUTTON, str, 0 );
	GF_STR_PrintColor(
		win, FONT_BUTTON, str,
		(WIN_P6_WASURERU_SX*8-siz)/2, P6_WASURERU_PY, MSG_NO_PUT, PCOL_BTN, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

void BPL_HidenMsgPut( BPLIST_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	if( wk->page == BPLIST_PAGE_WAZASET_BI ){
		win = &wk->add_win[WIN_P6_INFO];
	}else{
		win = &wk->add_win[WIN_P8_INFO];
	}
	GF_BGL_BmpWinDataFill( win, 0 );
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_05_002 );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}



//--------------------------------------------------------------------------------------------
/**
 * ボタン上のPPを表示
 *
 * @param	wk		ワーク
 * @param	idx		ウィンドウインデックス
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	BTN_PP_PX		( 40 )
#define	BTN_PP_PY		( 24 )
#define	BTN_PPSRA_PX	( 80 )
#define	BTN_PPSRA_PY	( 24 )

static void BPL_WazaButtonPPPut( BPLIST_WORK * wk, BPL_POKEWAZA * waza, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u32	siz;

	win = &wk->add_win[idx];
	exp = STRBUF_Create( (2+1)*2, wk->dat->heap );	// (2桁+EOM_)x2(ローカライズ用に一応)

	// 「PP」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_001 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, BTN_PP_PX, BTN_PP_PY, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );
	
	// 「/」
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_004 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, BTN_PPSRA_PX, BTN_PPSRA_PY, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );

	// 最大PP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_003 );
	WORDSET_RegisterNumber(
		wk->wset, 0, waza->mpp, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, BTN_PPSRA_PX+siz, BTN_PPSRA_PY, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );

	// PP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_002 );
	WORDSET_RegisterNumber(
		wk->wset, 0, waza->pp, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, BTN_PPSRA_PX-siz, BTN_PPSRA_PY, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );

	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( win );
}

static void BPL_WazaButtonPPRcv( BPLIST_WORK * wk, BPL_POKEWAZA * waza, u32 idx )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u32	siz;

	win = &wk->add_win[idx];
	exp = STRBUF_Create( (2+1)*2, wk->dat->heap );	// (2桁+EOM_)x2(ローカライズ用に一応)

	// クリア
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_001 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	STRBUF_Delete( str );
	GF_BGL_BmpWinFill( win, 0, BTN_PP_PX+siz, BTN_PPSRA_PY, BTN_PPSRA_PX-(BTN_PP_PX+siz), 16 );

	// PP値
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_002 );
	WORDSET_RegisterNumber(
		wk->wset, 0, waza->pp, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, BTN_PPSRA_PX-siz, BTN_PPSRA_PY, MSG_NO_PUT, PCOL_B_WHITE, NULL );
	STRBUF_Delete( str );

	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( win );
}


//--------------------------------------------------------------------------------------------
/**
 * ページ１のBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P1_NAME_PX		( 32 )
#define	P1_NAME_PY		( 8 )
#define	P1_HP_PX		( 56 )
#define	P1_HP_PY		( 32 )
#define	P1_HP_SX		( 24 )
#define	P1_HP_SY		( 8 )
#define	P1_HPGAGE_PX	( 48+16 )
#define	P1_HPGAGE_PY	( 24 )
#define	P1_HPGAGE_SX	( 64 )
#define	P1_HPGAGE_SY	( 8 )
#define	P1_LV_PX		( 0 )
#define	P1_LV_PY		( 32 )

static void BPL_Page1BmpWrite( BPLIST_WORK * wk )
{
	s32	i;

	for( i=0; i<PokeParty_GetPokeCount(wk->dat->pp); i++ ){
		GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P1_POKE1+i ], 0 );

		if( wk->poke[i].mons == 0 ){ continue; }

		BPL_NamePut( wk, WIN_P1_POKE1+i, FONT_BUTTON, i, P1_NAME_PX, P1_NAME_PY );

		if( wk->poke[i].egg == 0 ){
			BattlePokeList_P1_HPPut( wk, i );
		}

		if( BadStatusIconAnmGet( wk->poke[i].pp ) != ST_ICON_NONE ){
			continue;
		}

		BattlePokeList_P1_LvPut( wk, i );
	}

	if( wk->dat->mode == BPL_MODE_ITEMUSE ){
		BPL_PokeSelStrPut( wk, mes_b_plist_01_601 );
	}else{
		BPL_PokeSelStrPut( wk, mes_b_plist_01_600 );
	}
}

void BattlePokeList_P1_HPPut( BPLIST_WORK * wk, u8 pos )
{
	GF_BGL_BmpWinFill(
		&wk->add_win[WIN_P1_POKE1+pos], 0, P1_HP_PX, P1_HP_PY, P1_HP_SX, P1_HP_SY );
	GF_BGL_BmpWinFill(
		&wk->add_win[WIN_P1_POKE1+pos], 0,
		P1_HPGAGE_PX, P1_HPGAGE_PY, P1_HPGAGE_SX, P1_HPGAGE_SY );

	BPL_HPPut( wk, WIN_P1_POKE1+pos, pos, P1_HP_PX, P1_HP_PY );
	BPL_HPGagePut( wk, WIN_P1_POKE1+pos, pos, P1_HPGAGE_PX, P1_HPGAGE_PY );
}

void BattlePokeList_P1_LvPut( BPLIST_WORK * wk, u8 pos )
{
	if( wk->poke[pos].egg == 0 ){
		BPL_LvPut( wk, WIN_P1_POKE1+pos, pos, P1_LV_PX, P1_LV_PY );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替えページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//-------------------------------------------------------------------------------------------
#define	P_CHG_NAME_PX	( 0 )
#define	P_CHG_NAME_PY	( 8 )
static void BPL_IrekaeNamePut( BPLIST_WORK * wk, u32 pos );

static void BPL_ChgPageBmpWrite( BPLIST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_CHG_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_CHG_IREKAE ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_CHG_STATUS ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_CHG_WAZACHECK ], 0 );

//	BPL_NamePut(
//		wk, WIN_CHG_NAME, FONT_BUTTON, wk->dat->sel_poke, P_CHG_NAME_PX, P_CHG_NAME_PY );

	BPL_IrekaeNamePut( wk, wk->dat->sel_poke );


	BPL_StrCommandPut( wk, WIN_CHG_IREKAE, mes_b_plist_02_501 );

	if( wk->poke[wk->dat->sel_poke].egg == 0 ){
		BPL_StrCommandPut( wk, WIN_CHG_STATUS, mes_b_plist_02_504 );
		BPL_StrCommandPut( wk, WIN_CHG_WAZACHECK, mes_b_plist_02_505 );
	}else{
		GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_CHG_STATUS ] );
		GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_CHG_WAZACHECK ] );
	}
}

#define	NAME_CENTER_SPC_SX		( 8 )

static void BPL_IrekaeNamePut( BPLIST_WORK * wk, u32 pos )
{
	GF_BGL_BMPWIN * win;
	BPL_POKEDATA * pd;
	STRBUF * exp;
	STRBUF * str;
	u8	name_siz;
	u8	sex_siz;
	u8	spc_siz;
	u8	px;

	win = &wk->add_win[WIN_CHG_NAME];
	pd  = &wk->poke[pos];
	exp = STRBUF_Create( BUFLEN_POKEMON_NAME, wk->dat->heap );
	str = MSGMAN_AllocString( wk->mman, NameMsgID_Tbl[pos] );

	WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pd->pp) );
	WORDSET_ExpandStr( wk->wset, exp, str );
	STRBUF_Delete( str );

	str = NULL;
	if( pd->sex_put == 0 && pd->egg == 0 ){
		if( pd->sex == PARA_MALE ){
			str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_502 );
		}else if( pd->sex == PARA_FEMALE ){
			str = MSGMAN_AllocString( wk->mman, mes_b_plist_02_503 );
		}
	}

	name_siz = FontProc_GetPrintStrWidth( FONT_BUTTON, exp, 0 );
	if( str == NULL ){
		sex_siz = 0;
		spc_siz = 0;
	}else{
		sex_siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
		spc_siz = NAME_CENTER_SPC_SX;
	}
	px = (GF_BGL_BmpWinGet_SizeX(win)*8-name_siz-sex_siz-spc_siz)/2;

	GF_STR_PrintColor( win, FONT_BUTTON, exp, px, P_CHG_NAME_PY, MSG_NO_PUT, PCOL_BTN, NULL );
	STRBUF_Delete( exp );

	if( str != NULL ){
		if( pd->sex == PARA_MALE ){
			GF_STR_PrintColor(
				win, FONT_SYSTEM, str, px+name_siz+spc_siz,
				P_CHG_NAME_PY, MSG_NO_PUT, PCOL_B_BLUE, NULL );
		}else{
			GF_STR_PrintColor(
				win, FONT_SYSTEM, str, px+name_siz+spc_siz,
				P_CHG_NAME_PY, MSG_NO_PUT, PCOL_B_RED, NULL );
		}
		STRBUF_Delete( str );
	}

	GF_BGL_BmpWinOnVReq( win );
}




//--------------------------------------------------------------------------------------------
/**
 * ステータス技選択ページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	STW_NAME_PX		( 0 )
#define	STW_NAME_PY		( 0 )
#define	STW_WAZANAME_PY	( 8 )
#define	P2_PPNUM_PX		( 0 )
#define	P2_PPNUM_PY		( 0 )
#define	P2_PP_PX		( 0 )
#define	P2_PP_PY		( 0 )

static void BPL_StWazaSelPageBmpWrite( BPLIST_WORK * wk )
{
	BPL_POKEWAZA * waza;
	u16	i, swap;

	swap = WIN_STW_NAME_S * wk->bmp_swap;

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_NAME+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_SKILL1+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_SKILL2+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_SKILL3+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_SKILL4+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_STW_STATUS ], 0 );

	BPL_NamePut(
		wk, WIN_STW_NAME+swap, FONT_SYSTEM, wk->dat->sel_poke, STW_NAME_PX, STW_NAME_PY );

	for( i=0; i<4; i++ ){
		waza = &wk->poke[wk->dat->sel_poke].waza[i];
		if( waza->id == 0 ){ continue; }

		BPL_WazaNamePut(
			wk, waza->id, WIN_STW_SKILL1+swap+i,
			WazaMsgID_Tbl[i], FONT_BUTTON, STW_WAZANAME_PY, PCOL_BTN );

		BPL_WazaButtonPPPut( wk, waza, WIN_STW_SKILL1+swap+i );
	}

	BPL_StrCommandPut( wk, WIN_STW_STATUS, mes_b_plist_02_504 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_STW_SKILL1+swap ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_STW_SKILL2+swap ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_STW_SKILL3+swap ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_STW_SKILL4+swap ] );

	wk->bmp_swap ^= 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ステータスメインページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P3_NAME_PX		( 0 )
#define	P3_NAME_PY		( 0 )
#define	P3_HPGAGE_PX	( 0 )
#define	P3_HPGAGE_PY	( 0 )

static void BPL_StMainPageBmpWrite( BPLIST_WORK * wk )
{
	u32	swap;

	swap = WIN_P3_NAME_S * wk->bmp_swap;

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_LV ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_NEXT ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_POW ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_DEF ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_AGI ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPD ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_HP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_WAZACHECK ], 0 );

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_NAME+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_HPGAGE+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_LVNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_NEXTNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_POWNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_DEFNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_AGINUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPPNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPDNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_HPNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPANAME+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_SPAINFO+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P3_ITEMNAME+swap ], 0 );

	BPL_NamePut(
		wk, WIN_P3_NAME+swap, FONT_SYSTEM,
		wk->dat->sel_poke, P3_NAME_PX, P3_NAME_PY );
	BPL_P3_HPPut( wk, wk->dat->sel_poke );
	BPL_HPGagePut( wk, WIN_P3_HPGAGE+swap, wk->dat->sel_poke, P3_HPGAGE_PX, P3_HPGAGE_PY );
	BPL_P3_LvPut( wk, wk->dat->sel_poke );
	BPL_P3_PowPut( wk, wk->dat->sel_poke );
	BPL_P3_DefPut( wk, wk->dat->sel_poke );
	BPL_P3_AgiPut( wk, wk->dat->sel_poke );
	BPL_P3_SppPut( wk, wk->dat->sel_poke );
	BPL_P3_SpdPut( wk, wk->dat->sel_poke );
	BPL_TokuseiPut( wk, WIN_P3_SPANAME+swap, wk->dat->sel_poke );
	BPL_ItemPut( wk, WIN_P3_ITEMNAME+swap, wk->dat->sel_poke );
	BPL_P3_TokuseiInfoPut( wk, wk->dat->sel_poke );
	BPL_StrCommandPut( wk, WIN_P3_WAZACHECK, mes_b_plist_02_505 );

	wk->bmp_swap ^= 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ステータス技詳細ページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P4_NAME_PX		( 0 )
#define	P4_NAME_PY		( 0 )
#define	P4_WAZANAME_PY	( 0 )
#define	P4_PP_PX		( 0 )
#define	P4_PP_PY		( 0 )

static void BPL_StWazaInfoPageBmpWrite( BPLIST_WORK * wk )
{
	BPL_POKEWAZA * waza;
	u32	swap;

	swap = WIN_P4_SKILL_S * wk->bmp_swap;

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_PP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_HIT ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_POW ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_BUNRUI ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_PPNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_SKILL+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_HITNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_POWNUM+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_BRNAME+swap ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P4_INFO+swap ], 0 );

	waza = &wk->poke[wk->dat->sel_poke].waza[wk->dat->sel_wp];

	BPL_NamePut(
		wk, WIN_P4_NAME, FONT_SYSTEM, wk->dat->sel_poke, P4_NAME_PX, P4_NAME_PY );
	BPL_PPPut( wk, WIN_P4_PP, P4_PP_PX, P4_PP_PY );
	BPL_WazaNamePut(
		wk, waza->id, WIN_P4_SKILL+swap, 
		WazaMsgID_Tbl[wk->dat->sel_wp], FONT_SYSTEM, P4_WAZANAME_PY, PCOL_N_WHITE );
	BPL_WazaHitStrPut( wk, WIN_P4_HIT );
	BPL_WazaHitNumPut( wk, WIN_P4_HITNUM+swap, waza->hit );
	BPL_WazaPowStrPut( wk, WIN_P4_POW );
	BPL_WazaPowNumPut( wk, WIN_P4_POWNUM+swap, waza->pow );
	BPL_WazaInfoPut( wk, WIN_P4_INFO+swap, waza->id );
	BPL_WazaBunruiStrPut( wk, WIN_P4_BUNRUI );
	BPL_WazaKindPut( wk, WIN_P4_BRNAME+swap, waza->kind );
	BPL_WazaPPPut( wk, WIN_P4_PPNUM+swap, waza->pp, waza->mpp );

	wk->bmp_swap ^= 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 技忘れ選択ページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P5_NAME_PX		( 0 )
#define	P5_NAME_PY		( 0 )
#define	P5_WAZANAME_PY	( 8 )

static void BPL_WazaDelSelPageBmpWrite( BPLIST_WORK * wk )
{
	BPL_POKEWAZA * waza;
	u32	i;

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_SKILL1 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_SKILL2 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_SKILL3 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_SKILL4 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P5_SKILL5 ], 0 );

	BPL_NamePut(
		wk, WIN_P5_NAME, FONT_SYSTEM, wk->dat->sel_poke, P5_NAME_PX, P5_NAME_PY );

	for( i=0; i<4; i++ ){
		waza = &wk->poke[wk->dat->sel_poke].waza[i];
		if( waza->id == 0 ){ continue; }

		BPL_WazaNamePut(
			wk, waza->id, WIN_P5_SKILL1+i, 
			WazaMsgID_Tbl[i], FONT_BUTTON, P5_WAZANAME_PY, PCOL_BTN );

		BPL_WazaButtonPPPut( wk, waza, WIN_P5_SKILL1+i );
	}

	BPL_WazaNamePut(
		wk, wk->dat->chg_waza, WIN_P5_SKILL5, 
		WazaMsgID_Tbl[4], FONT_BUTTON, P5_WAZANAME_PY, PCOL_BTN );
	{
		BPL_POKEWAZA	tmp;

		tmp.pp  = WT_WazaDataParaGet( wk->dat->chg_waza, ID_WTD_pp );
		tmp.mpp = tmp.pp;
		BPL_WazaButtonPPPut( wk, &tmp, WIN_P5_SKILL5 );
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P5_SKILL1 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P5_SKILL2 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P5_SKILL3 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P5_SKILL4 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P5_SKILL5 ] );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ６のBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P6_NAME_PX		( 0 )
#define	P6_NAME_PY		( 0 )
#define	P6_WAZANAME_PY	( 0 )
#define	P6_PP_PX		( 0 )
#define	P6_PP_PY		( 0 )

static void BPL_Page6BmpWrite( BPLIST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_PP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_PPNUM ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_SKILL ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_HIT ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_HITNUM ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_POW ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_POWNUM ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_BUNRUI ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_BRNAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_INFO ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P6_WASURERU ], 0 );

	BPL_NamePut(
		wk, WIN_P6_NAME, FONT_SYSTEM, wk->dat->sel_poke, P6_NAME_PX, P6_NAME_PY );
	BPL_PPPut( wk, WIN_P6_PP, P6_PP_PX, P6_PP_PY );
	BPL_WazaHitStrPut( wk, WIN_P6_HIT );
	BPL_WazaPowStrPut( wk, WIN_P6_POW );
	BPL_WazaBunruiStrPut( wk, WIN_P6_BUNRUI );

	if( wk->dat->sel_wp < 4 ){
		BPL_POKEWAZA * waza = &wk->poke[wk->dat->sel_poke].waza[wk->dat->sel_wp];

		BPL_WazaNamePut(
			wk, waza->id, WIN_P6_SKILL, 
			WazaMsgID_Tbl[wk->dat->sel_wp], FONT_SYSTEM, P6_WAZANAME_PY, PCOL_N_WHITE );
		BPL_WazaHitNumPut( wk, WIN_P6_HITNUM, waza->hit );
		BPL_WazaPowNumPut( wk, WIN_P6_POWNUM, waza->pow );
		BPL_WazaInfoPut( wk, WIN_P6_INFO, waza->id );
		BPL_WazaKindPut( wk, WIN_P6_BRNAME, waza->kind );
		BPL_WazaPPPut( wk, WIN_P6_PPNUM, waza->pp, waza->mpp );
	}else{
		u32	pp = WT_WazaDataParaGet( wk->dat->chg_waza, ID_WTD_pp );

		BPL_WazaNamePut(
			wk, wk->dat->chg_waza, WIN_P6_SKILL, 
			WazaMsgID_Tbl[4], FONT_SYSTEM, P6_WAZANAME_PY, PCOL_N_WHITE );
		BPL_WazaInfoPut( wk, WIN_P6_INFO, wk->dat->chg_waza );
		BPL_WazaHitNumPut(
			wk, WIN_P6_HITNUM, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_hitprobability) );
		BPL_WazaPowNumPut(
			wk, WIN_P6_POWNUM, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_damage) );
		BPL_WazaKindPut(
			wk, WIN_P6_BRNAME, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_kind) );
		BPL_WazaPPPut( wk, WIN_P6_PPNUM, pp, pp );
	}

	BPL_WasureruStrPut( wk, WIN_P6_WASURERU );
}

//--------------------------------------------------------------------------------------------
/**
 * 技回復選択ページのBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P7_NAME_PX		( 0 )
#define	P7_NAME_PY		( 0 )
#define	P7_WAZANAME_PY	( 8 )

static void BPL_PPRcvPageBmpWrite( BPLIST_WORK * wk )
{
	BPL_POKEWAZA * waza;
	u32	i;

	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P7_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P7_SKILL1 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P7_SKILL2 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P7_SKILL3 ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P7_SKILL4 ], 0 );

	BPL_NamePut(
		wk, WIN_P7_NAME, FONT_SYSTEM, wk->dat->sel_poke, P7_NAME_PX, P7_NAME_PY );

	for( i=0; i<4; i++ ){
		waza = &wk->poke[wk->dat->sel_poke].waza[i];
		if( waza->id == 0 ){ continue; }

		BPL_WazaNamePut(
			wk, waza->id, WIN_P7_SKILL1+i, 
			WazaMsgID_Tbl[i], FONT_BUTTON, P7_WAZANAME_PY, PCOL_BTN );
		BPL_WazaButtonPPPut( wk, waza, WIN_P7_SKILL1+i );
	}

	if( ItemParamGet( wk->dat->item, ITEM_PRM_ALL_PP_RCV, wk->dat->heap ) == 0 ){
		BPL_PokeSelStrPut( wk, mes_b_plist_m19 );
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P7_SKILL1 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P7_SKILL2 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P7_SKILL3 ] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ WIN_P7_SKILL4 ] );
}

void BattlePokeList_PPRcv( BPLIST_WORK * wk, u16 widx, u16 pos )
{
/*
	BPL_POKEWAZA * waza;

	GF_BGL_BmpWinDataFill( &wk->add_win[ widx ], 0 );
	waza = &wk->poke[wk->dat->sel_poke].waza[pos];
	BPL_WazaNamePut(
		wk, waza->id, widx, 
		WazaMsgID_Tbl[pos], FONT_BUTTON, P7_WAZANAME_PY, PCOL_BTN );
	BPL_WazaButtonPPPut( wk, waza, widx );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ widx ] );
*/
	BPL_POKEWAZA * waza = &wk->poke[wk->dat->sel_poke].waza[pos];

	BPL_WazaButtonPPRcv( wk, waza, widx );
}

//--------------------------------------------------------------------------------------------
/**
 * ページ８のBMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P8_NAME_PX		( 0 )
#define	P8_NAME_PY		( 0 )
#define	P8_WAZANAME_PY	( 0 )
#define	P8_PP_PX		( 0 )
#define	P8_PP_PY		( 0 )

static void BPL_Page8BmpWrite( BPLIST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_NAME ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_PP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_PPNUM ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_SKILL ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_APP ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_INFO ], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ WIN_P8_WASURERU ], 0 );

	BPL_NamePut(
		wk, WIN_P8_NAME, FONT_SYSTEM, wk->dat->sel_poke, P8_NAME_PX, P8_NAME_PY );
	BPL_PPPut( wk, WIN_P8_PP, P8_PP_PX, P8_PP_PY );

	{
		STRBUF * str;

		str = MSGMAN_AllocString( wk->mman, mes_b_plist_04_400 );
		GF_STR_PrintColor(
			&wk->add_win[WIN_P8_APP], FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
		STRBUF_Delete( str );
		GF_BGL_BmpWinOnVReq( &wk->add_win[WIN_P8_APP] );
	}

	if( wk->dat->sel_wp < 4 ){
		BPL_POKEWAZA * waza = &wk->poke[wk->dat->sel_poke].waza[wk->dat->sel_wp];

		BPL_WazaNamePut(
			wk, waza->id, WIN_P8_SKILL, 
			WazaMsgID_Tbl[wk->dat->sel_wp], FONT_SYSTEM, P8_WAZANAME_PY, PCOL_N_WHITE );
		BPL_ContestWazaInfoPut( wk, WIN_P8_INFO, waza->id );

/*
		BPL_WazaHitNumPut( wk, WIN_P6_HITNUM, waza->hit );
		BPL_WazaPowNumPut( wk, WIN_P6_POWNUM, waza->pow );
		BPL_WazaKindPut( wk, WIN_P6_BRNAME, waza->kind );
*/
		BPL_WazaPPPut( wk, WIN_P8_PPNUM, waza->pp, waza->mpp );

	}else{
		u32	pp = WT_WazaDataParaGet( wk->dat->chg_waza, ID_WTD_pp );

		BPL_WazaNamePut(
			wk, wk->dat->chg_waza, WIN_P8_SKILL, 
			WazaMsgID_Tbl[4], FONT_SYSTEM, P8_WAZANAME_PY, PCOL_N_WHITE );
		BPL_ContestWazaInfoPut( wk, WIN_P8_INFO, wk->dat->chg_waza );

/*
		BPL_WazaHitNumPut(
			wk, WIN_P6_HITNUM, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_hitprobability) );
		BPL_WazaPowNumPut(
			wk, WIN_P6_POWNUM, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_damage) );
		BPL_WazaKindPut(
			wk, WIN_P6_BRNAME, WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_kind) );
*/
		BPL_WazaPPPut( wk, WIN_P8_PPNUM, pp, pp );
	}

	BPL_WasureruStrPut( wk, WIN_P8_WASURERU );
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
void BattlePokeList_TalkMsgSet( BPLIST_WORK * wk )
{
	BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_OFF, TALK_WIN_CGX_POS, BPL_PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], FBMP_COL_WHITE );
	BattlePokeList_TalkMsgStart( wk );
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
void BattlePokeList_TalkMsgStart( BPLIST_WORK * wk )
{
	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	wk->midx = GF_STR_PrintSimple(
				&wk->win[WIN_TALK], FONT_TALK, wk->msg_buf,
				0, 0, BattleWorkConfigMsgSpeedGet(wk->dat->bw), NULL );
}





#define	BPL_RCV_SLEEP		( 0x01 )	// 眠り
#define	BPL_RCV_POISON		( 0x02 )	// 毒
#define	BPL_RCV_BURN		( 0x04 )	// 火傷
#define	BPL_RCV_ICE			( 0x08 )	// 氷
#define	BPL_RCV_PARALYZE	( 0x10 )	// 麻痺
#define	BPL_RCV_PANIC		( 0x20 )	// 混乱
#define	BPL_RCV_MEROMERO	( 0x40 )	// メロメロ
#define	BPL_RCV_ALL			( 0x7f )	// 全快


void BattlePokeList_ItemUseMsgSet( BPLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	BPLIST_DATA * dat;
	void * item;
	STRBUF * str;
	u16	hp;
	u8	prm;
	u8	i;

	dat  = wk->dat;
	item = GetItemArcData( dat->item, ITEM_GET_DATA, dat->heap );
	pp   = BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
	hp   = PokeParaGet( pp, ID_PARA_hp, NULL );
	prm  = 0;
	if( ItemBufParamGet( item, ITEM_PRM_SLEEP_RCV ) != 0 ){
		prm |= BPL_RCV_SLEEP;
	}
	if( ItemBufParamGet( item, ITEM_PRM_POISON_RCV ) != 0 ){
		prm |= BPL_RCV_POISON;
	}
	if( ItemBufParamGet( item, ITEM_PRM_BURN_RCV ) != 0 ){
		prm |= BPL_RCV_BURN;
	}
	if( ItemBufParamGet( item, ITEM_PRM_ICE_RCV ) != 0 ){
		prm |= BPL_RCV_ICE;
	}
	if( ItemBufParamGet( item, ITEM_PRM_PARALYZE_RCV ) != 0 ){
		prm |= BPL_RCV_PARALYZE;
	}
	if( ItemBufParamGet( item, ITEM_PRM_PANIC_RCV ) != 0 ){
		prm |= BPL_RCV_PANIC;
	}
	if( ItemBufParamGet( item, ITEM_PRM_MEROMERO_RCV ) != 0 ){
		prm |= BPL_RCV_MEROMERO;
	}

	// 瀕死回復
	if( wk->poke[dat->sel_poke].hp == 0 && hp != 0 ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m13 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// HP回復
	}else if( wk->poke[dat->sel_poke].hp != hp ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m07 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_RegisterNumber(
			wk->wset, 1, hp-wk->poke[dat->sel_poke].hp, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// PP回復
	}else if( ItemBufParamGet( item, ITEM_PRM_PP_RCV ) != 0 ||
		ItemBufParamGet( item, ITEM_PRM_ALL_PP_RCV ) != 0 ){

		MSGMAN_GetString( wk->mman, mes_b_plist_m12, wk->msg_buf );
	// 眠り
	}else if( prm == BPL_RCV_SLEEP ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m17 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 毒
	}else if( prm == BPL_RCV_POISON ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m08 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 火傷
	}else if( prm == BPL_RCV_BURN ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m10 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 氷
	}else if( prm == BPL_RCV_ICE ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m11 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 麻痺
	}else if( prm == BPL_RCV_PARALYZE ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m09 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// 混乱
	}else if( prm == BPL_RCV_PANIC ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m15 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// メロメロ
	}else if( prm == BPL_RCV_MEROMERO ){
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m16 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	// ステータス全快
//	}else if( prm == BPL_RCV_ALL ){
	}else{
		str = MSGMAN_AllocString( wk->mman, mes_b_plist_m14 );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}

	sys_FreeMemoryEz( item );
}

void BattlePokeList_ItemUseSkillErrMsgSet( BPLIST_WORK * wk )
{
	POKEMON_PARAM * pp;
	BPLIST_DATA * dat;
	STRBUF * str;

	dat = wk->dat;
	pp  = BattleWorkPokemonParamGet( dat->bw, dat->client_no, dat->list_row[dat->sel_poke] );
	str = MSGMAN_AllocString( wk->mman, mes_b_plist_m20 );
	WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
	WORDSET_RegisterWazaName( wk->wset, 1, WAZANO_SASIOSAE );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
}
