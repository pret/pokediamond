//============================================================================================
/**
 * @file	pst_bmp.c
 * @brief	ポケモンステータス画面BMP
 * @author	Hiroyuki Nakamura
 * @date	2005.11.15
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "system/buflen.h"
#include "system/window.h"
#include "battle/battle_common.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/poke_number.h"
#include "poketool/poke_memo.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokestatus.h"
#include "itemtool/item.h"
#include "ribbon.h"

#define	PST_BMP_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
#include "pst_bmp.h"
#include "pst_bmp_def.h"
#include "pst_snd_def.h"


//============================================================================================
//	定数定義
//============================================================================================
// 文字列表示モード
enum {
	STR_MODE_LEFT = 0,	// 左詰め
	STR_MODE_RIGHT,		// 右詰め
	STR_MODE_CENTER,	// 中央
};

/*
#define	TMP_MSG_STR_SIZ		( 32 )		// 展開文字サイズ ( 16x2 )
#define	TMP_NUM_STR_SIZ		( 16 )		// 展開数字サイズ ( 8x2 )
*/

#define	PSTCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// フォントカラー：黒
#define	PSTCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// フォントカラー：白
#define	PSTCOL_N_BLUE	( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// フォントカラー：青
#define	PSTCOL_N_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// フォントカラー：赤
#define	PSTCOL_W_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 15 ) )		// フォントカラー：黒


#define	P5_WAZA_PX	( 1 )
#define	P5_WAZA_PY	( 2 )
#define	P5_PP_PX	( 16 )
#define	P5_PP_PY	( 16 )
#define	P5_PPNUM_PX	( 40+20 )
#define	P5_PPNUM_PY	( 16 )


#define	FILL_TITLE_PX	( 0 )		// ページタイトルクリアX座標
#define	FILL_TITLE_PY	( 0 )		// ページタイトルクリアY座標
#define	FILL_TITLE_SX	( 32 )		// ページタイトルクリアXサイズ
#define	FILL_TITLE_SY	( 2 )		// ページタイトルクリアYサイズ

#define	FILL_PARAM_PX	( 14 )		// ページパラメータクリアX座標
#define	FILL_PARAM_PY	( 2 )		// ページパラメータクリアY座標
#define	FILL_PARAM_SX	( 18 )		// ページパラメータクリアXサイズ
#define	FILL_PARAM_SY	( 22 )		// ページパラメータクリアYサイズ

#define	CND_TASTE_PY	( 16 )		// 味表示X座標

#define	P2_MEMO_PX		( 0 )	// トレーナーメモ表示X座標
#define	P2_MEMO_PY		( 0 )	// トレーナーメモ表示Y座標


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void StrPut( PST_WORK * wk, GF_BGL_BMPWIN * win, u32 col, u32 mode );
static void DefStr( PST_WORK * wk, u32 widx, u32 midx, u32 col, u32 mode );
static void PST_DefaultStrPut( PST_WORK * wk );
static void WazaPut( PST_WORK * wk, u32 pos );

static void PST_Page1BmpPut( PST_WORK * wk );
static void PST_Page2BmpPut( PST_WORK * wk );
static void PST_Page3BmpPut( PST_WORK * wk );
static void PST_Page4BmpPut( PST_WORK * wk );
static void PST_Page5BmpPut( PST_WORK * wk );
static void PST_Page6BmpPut( PST_WORK * wk );
static void PST_Page7BmpPut( PST_WORK * wk );
static void PST_Page8BmpPut( PST_WORK * wk );


//============================================================================================
//	グローバル変数
//============================================================================================
// 基本文字列のBMPデータ
static const BMPWIN_DAT DefaultBmpData[] =
{
	{	// 「ポケモンじょうほう」
		GF_BGL_FRAME1_M, WIN_P1_TITLE_PX, WIN_P1_TITLE_PY,
		WIN_P1_TITLE_SX, WIN_P1_TITLE_SY, WIN_P1_TITLE_PAL, WIN_P1_TITLE_CGX
	},
	{	// 「トレーナーメモ」
		GF_BGL_FRAME1_M, WIN_P2_TITLE_PX, WIN_P2_TITLE_PY,
		WIN_P2_TITLE_SX, WIN_P2_TITLE_SY, WIN_P2_TITLE_PAL, WIN_P2_TITLE_CGX
	},
	{	// 「ポケモンのうりょく」
		GF_BGL_FRAME1_M, WIN_P3_TITLE_PX, WIN_P3_TITLE_PY,
		WIN_P3_TITLE_SX, WIN_P3_TITLE_SY, WIN_P3_TITLE_PAL, WIN_P3_TITLE_CGX
	},
	{	// 「コンディション」
		GF_BGL_FRAME1_M, WIN_P4_TITLE_PX, WIN_P4_TITLE_PY,
		WIN_P4_TITLE_SX, WIN_P4_TITLE_SY, WIN_P4_TITLE_PAL, WIN_P4_TITLE_CGX
	},
	{	// 「たたかうわざ」
		GF_BGL_FRAME1_M, WIN_P5_TITLE_PX, WIN_P5_TITLE_PY,
		WIN_P5_TITLE_SX, WIN_P5_TITLE_SY, WIN_P5_TITLE_PAL, WIN_P5_TITLE_CGX
	},
	{	// 「コンテストわざ」
		GF_BGL_FRAME1_M, WIN_P6_TITLE_PX, WIN_P6_TITLE_PY,
		WIN_P6_TITLE_SX, WIN_P6_TITLE_SY, WIN_P6_TITLE_PAL, WIN_P6_TITLE_CGX
	},
	{	// 「もちもの」
		GF_BGL_FRAME1_M, WIN_MOTIMONO_PX, WIN_MOTIMONO_PY,
		WIN_MOTIMONO_SX, WIN_MOTIMONO_SY, WIN_MOTIMONO_PAL, WIN_MOTIMONO_CGX
	},
	{	// 「ずかんNo.」
		GF_BGL_FRAME1_M, WIN_P1_ZUKANNO_PX, WIN_P1_ZUKANNO_PY,
		WIN_P1_ZUKANNO_SX, WIN_P1_ZUKANNO_SY, WIN_P1_ZUKANNO_PAL, WIN_P1_ZUKANNO_CGX
	},
	{	// 「なまえ」
		GF_BGL_FRAME1_M, WIN_P1_NAME_PX, WIN_P1_NAME_PY,
		WIN_P1_NAME_SX, WIN_P1_NAME_SY, WIN_P1_NAME_PAL, WIN_P1_NAME_CGX
	},
	{	// 「タイプ」
		GF_BGL_FRAME1_M, WIN_P1_TYPE_PX, WIN_P1_TYPE_PY,
		WIN_P1_TYPE_SX, WIN_P1_TYPE_SY, WIN_P1_TYPE_PAL, WIN_P1_TYPE_CGX
	},
	{	// 「おや」
		GF_BGL_FRAME1_M, WIN_P1_OYA_PX, WIN_P1_OYA_PY,
		WIN_P1_OYA_SX, WIN_P1_OYA_SY, WIN_P1_OYA_PAL, WIN_P1_OYA_CGX
	},
	{	// 「IDNo.」
		GF_BGL_FRAME1_M, WIN_P1_IDNO_PX, WIN_P1_IDNO_PY,
		WIN_P1_IDNO_SX, WIN_P1_IDNO_SY, WIN_P1_IDNO_PAL, WIN_P1_IDNO_CGX
	},
	{	// 「げんざいの　けいけんち」
		GF_BGL_FRAME1_M, WIN_P1_NOWEXP_PX, WIN_P1_NOWEXP_PY,
		WIN_P1_NOWEXP_SX, WIN_P1_NOWEXP_SY, WIN_P1_NOWEXP_PAL, WIN_P1_NOWEXP_CGX
	},
	{	// 「つぎのレベルまで」
		GF_BGL_FRAME1_M, WIN_P1_NEXTLV_PX, WIN_P1_NEXTLV_PY,
		WIN_P1_NEXTLV_SX, WIN_P1_NEXTLV_SY, WIN_P1_NEXTLV_PAL, WIN_P1_NEXTLV_CGX
	},
	{	// 「あと」
		GF_BGL_FRAME1_M, WIN_P1_ATO_PX, WIN_P1_ATO_PY,
		WIN_P1_ATO_SX, WIN_P1_ATO_SY, WIN_P1_ATO_PAL, WIN_P1_ATO_CGX
	},
	{	// 「HP」
		GF_BGL_FRAME1_M, WIN_P3_HP_PX, WIN_P3_HP_PY,
		WIN_P3_HP_SX, WIN_P3_HP_SY, WIN_P3_HP_PAL, WIN_P3_HP_CGX
	},
	{	// 「こうげき」
		GF_BGL_FRAME1_M, WIN_P3_POW_PX, WIN_P3_POW_PY,
		WIN_P3_POW_SX, WIN_P3_POW_SY, WIN_P3_POW_PAL, WIN_P3_POW_CGX
	},
	{	// 「ぼうぎょ」
		GF_BGL_FRAME1_M, WIN_P3_DEF_PX, WIN_P3_DEF_PY,
		WIN_P3_DEF_SX, WIN_P3_DEF_SY, WIN_P3_DEF_PAL, WIN_P3_DEF_CGX
	},
	{	// 「とくこう」
		GF_BGL_FRAME1_M, WIN_P3_SPP_PX, WIN_P3_SPP_PY,
		WIN_P3_SPP_SX, WIN_P3_SPP_SY, WIN_P3_SPP_PAL, WIN_P3_SPP_CGX
	},
	{	// 「とくぼう」
		GF_BGL_FRAME1_M, WIN_P3_SPD_PX, WIN_P3_SPD_PY,
		WIN_P3_SPD_SX, WIN_P3_SPD_SY, WIN_P3_SPD_PAL, WIN_P3_SPD_CGX
	},
	{	// 「すばやさ」
		GF_BGL_FRAME1_M, WIN_P3_AGI_PX, WIN_P3_AGI_PY,
		WIN_P3_AGI_SX, WIN_P3_AGI_SY, WIN_P3_AGI_PAL, WIN_P3_AGI_CGX
	},
	{	// 「とくせい」
		GF_BGL_FRAME1_M, WIN_P3_SPA_PX, WIN_P3_SPA_PY,
		WIN_P3_SPA_SX, WIN_P3_SPA_SY, WIN_P3_SPA_PAL, WIN_P3_SPA_CGX
	},
	{	// 「けづや」
		GF_BGL_FRAME1_M, WIN_P4_KEDUYA_PX, WIN_P4_KEDUYA_PY,
		WIN_P4_KEDUYA_SX, WIN_P4_KEDUYA_SY, WIN_P4_KEDUYA_PAL, WIN_P4_KEDUYA_CGX
	},
	{	// 「せいかく」
		GF_BGL_FRAME1_M, WIN_P4_SEIKAKU_PX, WIN_P4_SEIKAKU_PY,
		WIN_P4_SEIKAKU_SX, WIN_P4_SEIKAKU_SY, WIN_P4_SEIKAKU_PAL, WIN_P4_SEIKAKU_CGX
	},
	{	// 「もどる」
		GF_BGL_FRAME1_M, WIN_P5_MODORU_PX, WIN_P5_MODORU_PY,
		WIN_P5_MODORU_SX, WIN_P5_MODORU_SY, WIN_P5_MODORU_PAL, WIN_P5_MODORU_CGX
	},
	{	// 「ぶんるい」
		GF_BGL_FRAME1_M, WIN_P5_BUNRUI_PX, WIN_P5_BUNRUI_PY,
		WIN_P5_BUNRUI_SX, WIN_P5_BUNRUI_SY, WIN_P5_BUNRUI_PAL, WIN_P5_BUNRUI_CGX
	},
	{	// 「いりょく
		GF_BGL_FRAME1_M, WIN_P5_IRYOKU_PX, WIN_P5_IRYOKU_PY,
		WIN_P5_IRYOKU_SX, WIN_P5_IRYOKU_SY, WIN_P5_IRYOKU_PAL, WIN_P5_IRYOKU_CGX
	},
	{	// 「めいちゅう」
		GF_BGL_FRAME1_M, WIN_P5_HIT_PX, WIN_P5_HIT_PY,
		WIN_P5_HIT_SX, WIN_P5_HIT_SY, WIN_P5_HIT_PAL, WIN_P5_HIT_CGX
	},
	{	// 「もどります」
		GF_BGL_FRAME1_M, WIN_P8_MODORIMASU_PX, WIN_P8_MODORIMASU_PY,
		WIN_P8_MODORIMASU_SX, WIN_P8_MODORIMASU_SY, WIN_P8_MODORIMASU_PAL, WIN_P8_MODORIMASU_CGX
	},
	{	// 「アピールポイント」
		GF_BGL_FRAME1_M, WIN_P6_AP_POINT_PX, WIN_P6_AP_POINT_PY,
		WIN_P6_AP_POINT_SX, WIN_P6_AP_POINT_SY, WIN_P6_AP_POINT_PAL, WIN_P6_AP_POINT_CGX
	},
	{	// 「もっているかず」
		GF_BGL_FRAME1_M, WIN_P7_MOTTEIRU_PX, WIN_P7_MOTTEIRU_PY,
		WIN_P7_MOTTEIRU_SX, WIN_P7_MOTTEIRU_SY, WIN_P7_MOTTEIRU_PAL, WIN_P7_MOTTEIRU_CGX
	},
	{	// 「きねんリボン」
		GF_BGL_FRAME1_M, WIN_P7_TITLE_PX, WIN_P7_TITLE_PY,
		WIN_P7_TITLE_SX, WIN_P7_TITLE_SY, WIN_P7_TITLE_PAL, WIN_P7_TITLE_CGX
	},
	{	// アイテム名
		GF_BGL_FRAME1_M, WIN_ITEMNAME_PX, WIN_ITEMNAME_PY,
		WIN_ITEMNAME_SX, WIN_ITEMNAME_SY, WIN_ITEMNAME_PAL, WIN_ITEMNAME_CGX
	},
	{	// レベル
		GF_BGL_FRAME1_M, WIN_LV_PX, WIN_LV_PY,
		WIN_LV_SX, WIN_LV_SY, WIN_LV_PAL, WIN_LV_CGX
	},
	{	// ニックネーム
		GF_BGL_FRAME1_M, WIN_NICKNAME_PX, WIN_NICKNAME_PY,
		WIN_NICKNAME_SX, WIN_NICKNAME_SY, WIN_NICKNAME_PAL, WIN_NICKNAME_CGX
	},
	{	// ガイドメッセージ
		GF_BGL_FRAME1_M, WIN_GUIDE_PX, WIN_GUIDE_PY,
		WIN_GUIDE_SX, WIN_GUIDE_SY, WIN_GUIDE_PAL, WIN_GUIDE_CGX
	}
};

/*
	{	// 「くわしく」
		GF_BGL_FRAME1_M, WIN_P5_KUWASIKU_PX, WIN_P5_KUWASIKU_PY,
		WIN_P5_KUWASIKU_SX, WIN_P5_KUWASIKU_SY, WIN_P5_KUWASIKU_PAL, WIN_P5_KUWASIKU_CGX
	},
	{	// 「いれかえ」
		GF_BGL_FRAME1_M, WIN_P5_IREKAE_PX, WIN_P5_IREKAE_PY,
		WIN_P5_IREKAE_SX, WIN_P5_IREKAE_SY, WIN_P5_IREKAE_PAL, WIN_P5_IREKAE_CGX
	},
	{	// 「けってい」
		GF_BGL_FRAME1_M, WIN_P5_KETTEI_PX, WIN_P5_KETTEI_PY,
		WIN_P5_KETTEI_SX, WIN_P5_KETTEI_SY, WIN_P5_KETTEI_PAL, WIN_P5_KETTEI_CGX
	},
	{	// 「もどる」
		GF_BGL_FRAME1_M, WIN_P8_MODORU_PX, WIN_P8_MODORU_PY,
		WIN_P8_MODORU_SX, WIN_P8_MODORU_SY, WIN_P8_MODORU_PAL, WIN_P8_MODORU_CGX
	},
*/

// ページ１（ポケモン情報）
static const BMPWIN_DAT Page1BmpData[] =
{
	{	// 図鑑No.
		GF_BGL_FRAME1_M, A_WIN_P1_LIBNUM_PX, A_WIN_P1_LIBNUM_PY,
		A_WIN_P1_LIBNUM_SX, A_WIN_P1_LIBNUM_SY, A_WIN_P1_LIBNUM_PAL, A_WIN_P1_LIBNUM_CGX
	},
	{	// 名前
		GF_BGL_FRAME1_M, A_WIN_P1_NAME_PX, A_WIN_P1_NAME_PY,
		A_WIN_P1_NAME_SX, A_WIN_P1_NAME_SY, A_WIN_P1_NAME_PAL, A_WIN_P1_NAME_CGX
	},
	{	// 親名
		GF_BGL_FRAME1_M, A_WIN_P1_OYANAME_PX, A_WIN_P1_OYANAME_PY,
		A_WIN_P1_OYANAME_SX, A_WIN_P1_OYANAME_SY, A_WIN_P1_OYANAME_PAL, A_WIN_P1_OYANAME_CGX
	},
	{	// IDNo.
		GF_BGL_FRAME1_M, A_WIN_P1_IDNO_PX, A_WIN_P1_IDNO_PY,
		A_WIN_P1_IDNO_SX, A_WIN_P1_IDNO_SY, A_WIN_P1_IDNO_PAL, A_WIN_P1_IDNO_CGX
	},
	{	// 現在の経験値
		GF_BGL_FRAME1_M, A_WIN_P1_NOWEXP_PX, A_WIN_P1_NOWEXP_PY,
		A_WIN_P1_NOWEXP_SX, A_WIN_P1_NOWEXP_SY, A_WIN_P1_NOWEXP_PAL, A_WIN_P1_NOWEXP_CGX
	},
	{	// 次のレベルまで@
		GF_BGL_FRAME1_M, A_WIN_P1_NEXTEXP_PX, A_WIN_P1_NEXTEXP_PY,
		A_WIN_P1_NEXTEXP_SX, A_WIN_P1_NEXTEXP_SY, A_WIN_P1_NEXTEXP_PAL, A_WIN_P1_NEXTEXP_CGX
	}
};

// ページ２（トレーナーメモ）
static const BMPWIN_DAT Page2BmpData[] =
{
	{	// トレーナーメモ
		GF_BGL_FRAME1_M, A_WIN_P2_TMEMO_PX, A_WIN_P2_TMEMO_PY,
		A_WIN_P2_TMEMO_SX, A_WIN_P2_TMEMO_SY, A_WIN_P2_TMEMO_PAL, A_WIN_P2_TMEMO_CGX
	}
};

// ページ３（ポケモン能力）
static const BMPWIN_DAT Page3BmpData[] =
{
	{	// HP/MHP
		GF_BGL_FRAME1_M, A_WIN_P3_HP_PX, A_WIN_P3_HP_PY,
		A_WIN_P3_HP_SX, A_WIN_P3_HP_SY, A_WIN_P3_HP_PAL, A_WIN_P3_HP_CGX
	},
	{	// 攻撃
		GF_BGL_FRAME1_M, A_WIN_P3_POW_PX, A_WIN_P3_POW_PY,
		A_WIN_P3_POW_SX, A_WIN_P3_POW_SY, A_WIN_P3_POW_PAL, A_WIN_P3_POW_CGX
	},
	{	// 防御
		GF_BGL_FRAME1_M, A_WIN_P3_DEF_PX, A_WIN_P3_DEF_PY,
		A_WIN_P3_DEF_SX, A_WIN_P3_DEF_SY, A_WIN_P3_DEF_PAL, A_WIN_P3_DEF_CGX
	},
	{	// 特攻
		GF_BGL_FRAME1_M, A_WIN_P3_SPP_PX, A_WIN_P3_SPP_PY,
		A_WIN_P3_SPP_SX, A_WIN_P3_SPP_SY, A_WIN_P3_SPP_PAL, A_WIN_P3_SPP_CGX
	},
	{	// 特防
		GF_BGL_FRAME1_M, A_WIN_P3_SPD_PX, A_WIN_P3_SPD_PY,
		A_WIN_P3_SPD_SX, A_WIN_P3_SPD_SY, A_WIN_P3_SPD_PAL, A_WIN_P3_SPD_CGX
	},
	{	// 素早さ
		GF_BGL_FRAME1_M, A_WIN_P3_AGI_PX, A_WIN_P3_AGI_PY,
		A_WIN_P3_AGI_SX, A_WIN_P3_AGI_SY, A_WIN_P3_AGI_PAL, A_WIN_P3_AGI_CGX
	},
	{	// 特性名
		GF_BGL_FRAME1_M, A_WIN_P3_SPANAME_PX, A_WIN_P3_SPANAME_PY,
		A_WIN_P3_SPANAME_SX, A_WIN_P3_SPANAME_SY, A_WIN_P3_SPANAME_PAL, A_WIN_P3_SPANAME_CGX
	},
	{	// 特性説明
		GF_BGL_FRAME1_M, A_WIN_P3_SPAINFO_PX, A_WIN_P3_SPAINFO_PY,
		A_WIN_P3_SPAINFO_SX, A_WIN_P3_SPAINFO_SY, A_WIN_P3_SPAINFO_PAL, A_WIN_P3_SPAINFO_CGX
	}
};

// ページ５（技）
static const BMPWIN_DAT Page5BmpData[] =
{
	{	// 技名１
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA1_PX, A_WIN_P5_WAZA1_PY,
		A_WIN_P5_WAZA1_SX, A_WIN_P5_WAZA1_SY, A_WIN_P5_WAZA1_PAL, A_WIN_P5_WAZA1_CGX
	},
	{	// 技名２
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA2_PX, A_WIN_P5_WAZA2_PY,
		A_WIN_P5_WAZA2_SX, A_WIN_P5_WAZA2_SY, A_WIN_P5_WAZA2_PAL, A_WIN_P5_WAZA2_CGX
	},
	{	// 技名３
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA3_PX, A_WIN_P5_WAZA3_PY,
		A_WIN_P5_WAZA3_SX, A_WIN_P5_WAZA3_SY, A_WIN_P5_WAZA3_PAL, A_WIN_P5_WAZA3_CGX
	},
	{	// 技名４
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA4_PX, A_WIN_P5_WAZA4_PY,
		A_WIN_P5_WAZA4_SX, A_WIN_P5_WAZA4_SY, A_WIN_P5_WAZA4_PAL, A_WIN_P5_WAZA4_CGX
	},
	{	// 技名５
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA5_PX, A_WIN_P5_WAZA5_PY,
		A_WIN_P5_WAZA5_SX, A_WIN_P5_WAZA5_SY, A_WIN_P5_WAZA5_PAL, A_WIN_P5_WAZA5_CGX
	},
	{	// 威力
		GF_BGL_FRAME1_M, A_WIN_P5_ATC_PX, A_WIN_P5_ATC_PY,
		A_WIN_P5_ATC_SX, A_WIN_P5_ATC_SY, A_WIN_P5_ATC_PAL, A_WIN_P5_ATC_CGX
	},
	{	// 命中
		GF_BGL_FRAME1_M, A_WIN_P5_HIT_PX, A_WIN_P5_HIT_PY,
		A_WIN_P5_HIT_SX, A_WIN_P5_HIT_SY, A_WIN_P5_HIT_PAL, A_WIN_P5_HIT_CGX
	},
	{	// 技説明
		GF_BGL_FRAME1_M, A_WIN_P5_INFO_PX, A_WIN_P5_INFO_PY,
		A_WIN_P5_INFO_SX, A_WIN_P5_INFO_SY, A_WIN_P5_INFO_PAL, A_WIN_P5_INFO_CGX
	}
};

// ページ６（コンテスト技）
static const BMPWIN_DAT Page6BmpData[] =
{
	{	// 技名１
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA1_PX, A_WIN_P5_WAZA1_PY,
		A_WIN_P5_WAZA1_SX, A_WIN_P5_WAZA1_SY, A_WIN_P5_WAZA1_PAL, A_WIN_P5_WAZA1_CGX
	},
	{	// 技名２
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA2_PX, A_WIN_P5_WAZA2_PY,
		A_WIN_P5_WAZA2_SX, A_WIN_P5_WAZA2_SY, A_WIN_P5_WAZA2_PAL, A_WIN_P5_WAZA2_CGX
	},
	{	// 技名３
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA3_PX, A_WIN_P5_WAZA3_PY,
		A_WIN_P5_WAZA3_SX, A_WIN_P5_WAZA3_SY, A_WIN_P5_WAZA3_PAL, A_WIN_P5_WAZA3_CGX
	},
	{	// 技名４
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA4_PX, A_WIN_P5_WAZA4_PY,
		A_WIN_P5_WAZA4_SX, A_WIN_P5_WAZA4_SY, A_WIN_P5_WAZA4_PAL, A_WIN_P5_WAZA4_CGX
	},
	{	// 技名５
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA5_PX, A_WIN_P5_WAZA5_PY,
		A_WIN_P5_WAZA5_SX, A_WIN_P5_WAZA5_SY, A_WIN_P5_WAZA5_PAL, A_WIN_P5_WAZA5_CGX
	},
	{	// 技説明
		GF_BGL_FRAME1_M, A_WIN_P6_INFO_PX, A_WIN_P6_INFO_PY,
		A_WIN_P6_INFO_SX, A_WIN_P6_INFO_SY, A_WIN_P6_INFO_PAL, A_WIN_P6_INFO_CGX
	}
};

// ページ７（記念リボン）
static const BMPWIN_DAT Page7BmpData[] =
{
	{	// ???こ
		GF_BGL_FRAME1_M, A_WIN_P7_NUM_PX, A_WIN_P7_NUM_PY,
		A_WIN_P7_NUM_SX, A_WIN_P7_NUM_SY, A_WIN_P7_NUM_PAL, A_WIN_P7_NUM_CGX
	},
	{	// ???/???
		GF_BGL_FRAME1_M, A_WIN_P7_MAX_PX, A_WIN_P7_MAX_PY,
		A_WIN_P7_MAX_SX, A_WIN_P7_MAX_SY, A_WIN_P7_MAX_PAL, A_WIN_P7_MAX_CGX
	},
	{	// リボン名
		GF_BGL_FRAME1_M, A_WIN_P7_NAME_PX, A_WIN_P7_NAME_PY,
		A_WIN_P7_NAME_SX, A_WIN_P7_NAME_SY, A_WIN_P7_NAME_PAL, A_WIN_P7_NAME_CGX
	},
	{	// リボン説明
		GF_BGL_FRAME1_M, A_WIN_P7_INFO_PX, A_WIN_P7_INFO_PY,
		A_WIN_P7_INFO_SX, A_WIN_P7_INFO_SY, A_WIN_P7_INFO_PAL, A_WIN_P7_INFO_CGX
	}
};



// ポルト関連のコンディションページ
static const BMPWIN_DAT PorutoCndBmpData[] =
{
	{	// 「けってい」
		GF_BGL_FRAME1_M, A_WIN_COND_KETTEI_PX, A_WIN_COND_KETTEI_PY,
		A_WIN_COND_KETTEI_SX, A_WIN_COND_KETTEI_SY, A_WIN_COND_KETTEI_PAL, A_WIN_COND_KETTEI_CGX
	},
	{	// 「すきなたべもの」
		GF_BGL_FRAME1_M, A_WIN_COND_LIKE_PX, A_WIN_COND_LIKE_PY,
		A_WIN_COND_LIKE_SX, A_WIN_COND_LIKE_SY, A_WIN_COND_LIKE_PAL, A_WIN_COND_LIKE_CGX
	},
	{	// メッセージ
		GF_BGL_FRAME1_M, A_WIN_COND_MSG_PX, A_WIN_COND_MSG_PY,
		A_WIN_COND_MSG_SX, A_WIN_COND_MSG_SY, A_WIN_COND_MSG_PAL, A_WIN_COND_MSG_CGX
	}
/*
	{	// 「もどる」
		GF_BGL_FRAME1_M, A_WIN_COND_MODORU_PX, A_WIN_COND_MODORU_PY,
		A_WIN_COND_MODORU_SX, A_WIN_COND_MODORU_SY, A_WIN_COND_MODORU_PAL, A_WIN_COND_MODORU_CGX
	},
*/
};













void PokeStatus_DefaultBmpAdd( PST_WORK * wk )
{
	u16	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->def_win[i], &DefaultBmpData[i] );
		GF_BGL_BmpWinDataFill( &wk->def_win[i], 0 );
	}
	PST_DefaultStrPut( wk );
	PokeStatus_NickNamePut( wk );
	PokeStatus_LvPut( wk );
	PokeStatus_ItemPut( wk );

/*
	OS_Printf( "PST_ADD_WIN : %d\n", ADD_WIN_PAGE_CGX );

	OS_Printf(
		"PST BMP -トレーナーメモ : %d\n",
		A_WIN_P2_TMEMO_CGX+A_WIN_P2_TMEMO_SX*A_WIN_P2_TMEMO_SY );
	OS_Printf(
		"PST BMP -技 : %d\n",
		A_WIN_P6_INFO_CGX+A_WIN_P6_INFO_SX*A_WIN_P6_INFO_SY );
*/
/*
	OS_Printf(
		"PST BMP -デフォルト : %d\n", WIN_NICKNAME_CGX+WIN_NICKNAME_SX*WIN_NICKNAME_SY );
	OS_Printf(
		"PST BMP -ポケモン情報 : %d\n",
		A_WIN_P1_NEXTEXP_CGX+A_WIN_P1_NEXTEXP_SX*A_WIN_P1_NEXTEXP_SY );
	OS_Printf(
		"PST BMP -トレーナーメモ : %d\n",
		A_WIN_P2_TMEMO_CGX+A_WIN_P2_TMEMO_SX*A_WIN_P2_TMEMO_SY );
	OS_Printf(
		"PST BMP -ポケモン能力 : %d\n",
		A_WIN_P3_SPAINFO_CGX+A_WIN_P3_SPAINFO_SX*A_WIN_P3_SPAINFO_SY );
	OS_Printf(
		"PST BMP -技 : %d\n",
		A_WIN_P5_WAZA5_CGX+A_WIN_P5_WAZA5_SX*A_WIN_P5_WAZA5_SY );
*/
}

void PokeStatus_PageBmpAdd( PST_WORK * wk )
{
	const BMPWIN_DAT * dat;
	u32	i;

	switch( wk->page ){
	case PST_PAGE_INFO:
		dat = Page1BmpData;
		wk->add_win_max = ADD_WIN_P1_MAX;
		break;
	case PST_PAGE_MEMO:
		dat = Page2BmpData;
		wk->add_win_max = ADD_WIN_P2_MAX;
		break;
	case PST_PAGE_PARAM:
		dat = Page3BmpData;
		wk->add_win_max = ADD_WIN_P3_MAX;
		break;
	case PST_PAGE_B_SKILL:
		dat = Page5BmpData;
		wk->add_win_max = ADD_WIN_P5_MAX;
		break;
	case PST_PAGE_C_SKILL:
		dat = Page6BmpData;
		wk->add_win_max = ADD_WIN_P6_MAX;
		break;
	case PST_PAGE_RIBBON:
		dat = Page7BmpData;
		wk->add_win_max = ADD_WIN_P7_MAX;
		break;

	case PST_PAGE_CONDITION:
	case PST_PAGE_RET:
		if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
			return;
		}
		dat = PorutoCndBmpData;
		wk->add_win_max = ADD_WIN_COND_MAX;
		break;

	default:
		return;
	}

	wk->add_win = GF_BGL_BmpWinAllocGet( HEAPID_POKESTATUS, wk->add_win_max );
	for( i=0; i<wk->add_win_max; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->add_win[i], &dat[i] );
	}
}

void PokeStatus_PageBmpFree( PST_WORK * wk )
{
	switch( wk->page ){
	case PST_PAGE_INFO:
	case PST_PAGE_MEMO:
	case PST_PAGE_PARAM:
	case PST_PAGE_B_SKILL:
	case PST_PAGE_C_SKILL:
	case PST_PAGE_RIBBON:
		break;

	case PST_PAGE_CONDITION:
	case PST_PAGE_RET:
		if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
			return;
		}
		break;

	default:
		return;
	}

	GF_BGL_BmpWinFree( wk->add_win, wk->add_win_max );
}

void PokeStatus_BmpFreeAll( PST_WORK * wk )
{
	u32	i;

	PokeStatus_PageBmpFree( wk );
	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->def_win[i] );
	}
}


//============================================================================================
//	ニックネーム＆性別
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ニックネーム・性別表示
 *
 * @param	wk		ステータス画面ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_NickNamePut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	u32	siz;

	win = &wk->def_win[WIN_NICKNAME];

	GF_BGL_BmpWinDataFill( win, 0 );

	// ニックネーム
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->pp.nickname, 0, 0, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );

	// 性別
	if( wk->pp.sex_put == 0 ){
		if( wk->pp.sex == PARA_MALE ){
			MSGMAN_GetString( wk->msg_man, mes_status_01_02, wk->msg_buf );
			StrPut( wk, win, PSTCOL_N_BLUE, STR_MODE_RIGHT );
		}else if( wk->pp.sex == PARA_FEMALE ){
			MSGMAN_GetString( wk->msg_man, mes_status_01_03, wk->msg_buf );
			StrPut( wk, win, PSTCOL_N_RED, STR_MODE_RIGHT );
		}
	}

	GF_BGL_BmpWinOnVReq( win );
}


//============================================================================================
//	レベル
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * レベル表示
 *
 * @param	wk		ステータス画面ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_LvPut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->def_win[WIN_LV];

	GF_BGL_BmpWinDataFill( win, 0 );

	if( wk->pp.tamago == 0 ){
		NUMFONT_WriteMark( wk->num_font, NUMFONT_MARK_LV, win, 0, 5 );

		str = MSGMAN_AllocString( wk->msg_man, mes_status_01_04 );
		WORDSET_RegisterNumber(
			wk->wset, 0, wk->pp.lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );

		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			NUMFONT_MARK_WIDTH, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	}

	GF_BGL_BmpWinOnVReq( win );
}

//============================================================================================
//	アイテム
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * アイテム表示
 *
 * @param	wk		ステータス画面ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_ItemPut( PST_WORK * wk )
{
	STRBUF * str;

	GF_BGL_BmpWinDataFill( &wk->def_win[WIN_ITEMNAME], 0 );

	if( wk->pp.item != 0 ){
		WORDSET_RegisterItemName( wk->wset, 0, wk->pp.item );
		str = MSGMAN_AllocString( wk->msg_man, mes_status_01_06 );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_status_01_07, wk->msg_buf );
	}
	StrPut( wk, &wk->def_win[WIN_ITEMNAME], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
}

//--------------------------------------------------------------------------------------------
/**
 * ガイドメッセージ表示
 *
 * @param	wk		ステータス画面ワーク
 * @param	midx	メッセージインデックス
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_GuideStrPut( PST_WORK * wk, u32 midx )
{
	GF_BGL_BmpWinDataFill( &wk->def_win[WIN_GUIDE], 0 );
	DefStr( wk, WIN_GUIDE, midx, PSTCOL_N_WHITE, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_GUIDE] );
}





//--------------------------------------------------------------------------------------------
/**
 * 自分のポケモンかチェック
 *
 * @param	wk		ステータス画面ワーク
 *
 * @retval	"TRUE = 自分のポケモン"
 * @retval	"FALSE = 他人のポケモン"
 */
//--------------------------------------------------------------------------------------------
static BOOL PST_PokeOyaCheck( PST_WORK * wk )
{
	if( ( wk->pp.id == wk->dat->player_id ) &&
		( wk->pp.oya_sex == wk->dat->player_sex ) &&
		( STRBUF_Compare( wk->pp.oya, wk->player_name ) == 0 ) ){

		return TRUE;
	}
	return FALSE;
}








static void StrPut( PST_WORK * wk, GF_BGL_BMPWIN * win, u32 col, u32 mode )
{
	u8	siz;
	u8	wsx;
	u8	px;

	switch( mode ){
	case STR_MODE_LEFT:		// 左詰め
		px = 0;
		break;
	case STR_MODE_RIGHT:	// 右詰め
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( win ) * 8;
		px  = wsx - siz;
		break;
	case STR_MODE_CENTER:	// 中央
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( win ) * 8;
		px  = (wsx-siz)/2;
		break;
	}
	GF_STR_PrintColor( win, FONT_SYSTEM, wk->msg_buf, px, 0, MSG_NO_PUT, col, NULL );
}

static void DefStr( PST_WORK * wk, u32 widx, u32 midx, u32 col, u32 mode )
{
	u8	siz;
	u8	wsx;
	u8	px;

	MSGMAN_GetString( wk->msg_man, midx, wk->msg_buf );
	StrPut( wk, &wk->def_win[widx], col, mode );
}




static void NumPrmSet( PST_WORK * wk, u32 msg_id, u32 num, u8 keta, u8 type )
{
	STRBUF * str_buf;

	str_buf = MSGMAN_AllocString( wk->msg_man, msg_id );
	WORDSET_RegisterNumber( wk->wset, 0, num, keta, type, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str_buf );
	STRBUF_Delete( str_buf );
}

//--------------------------------------------------------------------------------------------
/**
 * "??/??"表示
 *
 * @param	wk			ステータス画面ワーク
 * @param	widx		ウィンドウインデックス
 * @param	sra_id		"/"のメッセージID
 * @param	now_id		現在値のメッセージID
 * @param	max_id		最大値のメッセージID
 * @param	now_prm		現在値
 * @param	max_prm		最大値
 * @param	keta		表示桁数
 * @param	px			表示X座標（中心）
 * @param	py			表示Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NumSraMaxStrPut(
				PST_WORK * wk, u32 widx,
				u32 sra_id, u32 now_id, u32 max_id,
				u16 now_prm, u16 max_prm, u8 keta, u8 px, u8 py )
{
	GF_BGL_BMPWIN * win;
	u32	siz;
	u16	spx;
	u16	mpx;

	win = &wk->add_win[widx];

	MSGMAN_GetString( wk->msg_man, sra_id, wk->msg_buf );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	spx = px - siz / 2;
	mpx = spx + siz;

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, spx, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	NumPrmSet( wk, now_id, now_prm, keta, NUM_MODE_LEFT );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, spx-siz, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	NumPrmSet( wk, max_id, max_prm, keta, NUM_MODE_LEFT );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, mpx, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
}



static void PST_DefaultStrPut( PST_WORK * wk )
{
	// 「ポケモンじょうほう」
	DefStr( wk, WIN_P1_TITLE, mes_status_02_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「トレーナーメモ」
	DefStr( wk, WIN_P2_TITLE, mes_status_03_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「ポケモンのうりょく」
	DefStr( wk, WIN_P3_TITLE, mes_status_04_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「コンディション」
	DefStr( wk, WIN_P4_TITLE, mes_status_05_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「たたかうわざ」
	DefStr( wk, WIN_P5_TITLE, mes_status_06_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「コンテストわざ」
	DefStr( wk, WIN_P6_TITLE, mes_status_07_01, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// 「もちもの」
	DefStr( wk, WIN_MOTIMONO, mes_status_01_05, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// 「ずかんNo.」
	DefStr( wk, WIN_P1_ZUKANNO, mes_status_02_02, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「なまえ」
	DefStr( wk, WIN_P1_NAME, mes_status_02_04, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「タイプ」
	DefStr( wk, WIN_P1_TYPE, mes_status_02_06, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「おや」
	DefStr( wk, WIN_P1_OYA, mes_status_02_07, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「IDNo.」
	DefStr( wk, WIN_P1_IDNO, mes_status_02_09, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「げんざいの　けいけんち」
	DefStr( wk, WIN_P1_NOWEXP, mes_status_02_11, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「つぎのレベルまで」
	DefStr( wk, WIN_P1_NEXTLV, mes_status_02_13, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「あと」
	DefStr( wk, WIN_P1_ATO, mes_status_02_14, PSTCOL_N_BLACK, STR_MODE_LEFT );

	// 「HP」
	DefStr( wk, WIN_P3_HP, mes_status_04_02, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「こうげき」
	DefStr( wk, WIN_P3_POW, mes_status_04_03, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「ぼうぎょ」
	DefStr( wk, WIN_P3_DEF, mes_status_04_04, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「とくこう」
	DefStr( wk, WIN_P3_SPP, mes_status_04_05, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「とくぼう」
	DefStr( wk, WIN_P3_SPD, mes_status_04_06, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「すばやさ」
	DefStr( wk, WIN_P3_AGI, mes_status_04_07, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// 「とくせい」
	DefStr( wk, WIN_P3_SPA, mes_status_04_08, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// 「けづや」
	DefStr( wk, WIN_P4_KEDUYA, mes_status_05_02, PSTCOL_N_WHITE, STR_MODE_LEFT );

//	WIN_P4_SEIKAKU,		// 「せいかく」

	// 「もどる」
//	DefStr( wk, WIN_P5_MODORU, mes_status_06_19, PSTCOL_N_WHITE, STR_MODE_LEFT );
	{
		MSGMAN_GetString( wk->msg_man, mes_status_06_19, wk->msg_buf );
		GF_STR_PrintColor(
			&wk->def_win[WIN_P5_MODORU], FONT_SYSTEM,
			wk->msg_buf, 0, P5_WAZA_PY, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );
	}

	// ぶんるい
	DefStr( wk, WIN_P5_BUNRUI, mes_status_06_22, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// いりょく
	DefStr( wk, WIN_P5_IRYOKU, mes_status_06_20, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// めいちゅう
	DefStr( wk, WIN_P5_HIT, mes_status_06_21, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// 「もどります」
	DefStr( wk, WIN_P8_MODORIMASU, mes_status_08_02, PSTCOL_N_WHITE, STR_MODE_CENTER );

	// 「アピールポイント」
	DefStr( wk, WIN_P6_AP_POINT, mes_status_07_04, PSTCOL_N_BLACK, STR_MODE_CENTER );

	// 「もっているかず」
	DefStr( wk, WIN_P7_MOTTEIRU, mes_status_10_04, PSTCOL_N_BLACK, STR_MODE_LEFT );
	// 「きねんリボン」
	DefStr( wk, WIN_P7_TITLE, mes_status_10_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
}



void PokeStatus_PageBmpPut( PST_WORK * wk )
{
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0,
		FILL_TITLE_PX, FILL_TITLE_PY, FILL_TITLE_SX, FILL_TITLE_SY, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0,
		FILL_PARAM_PX, FILL_PARAM_PY, FILL_PARAM_SX, FILL_PARAM_SY, GF_BGL_SCRWRT_PALNL );

	switch( wk->page ){
	case PST_PAGE_INFO:
		PST_Page1BmpPut( wk );
		break;
	case PST_PAGE_MEMO:
		PST_Page2BmpPut( wk );
		break;
	case PST_PAGE_PARAM:
		PST_Page3BmpPut( wk );
		break;
	case PST_PAGE_CONDITION:
		PST_Page4BmpPut( wk );
		break;
	case PST_PAGE_B_SKILL:
		PST_Page5BmpPut( wk );
		break;
	case PST_PAGE_C_SKILL:
		PST_Page6BmpPut( wk );
		break;
	case PST_PAGE_RIBBON:
		PST_Page7BmpPut( wk );
		break;
	case PST_PAGE_RET:
		PST_Page8BmpPut( wk );
		break;
	}
}


static void PST_Page1BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_TITLE] );		// 「ポケモンじょうほう」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_ZUKANNO] );	// 「ずかんNo.」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NAME] );		// 「なまえ」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_TYPE] );		// 「タイプ」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_OYA] );		// 「おや」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_IDNO] );		// 「IDNo.」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NOWEXP] );		// 「げんざいの　けいけんち」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NEXTLV] );		// 「つぎのレベルまで」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_ATO] );		// 「あと」

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_LIBNUM], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_OYANAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_IDNO], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NOWEXP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NEXTEXP], 0 );

	{	// 図鑑No.
		u32	num = PMNumber_GetPokeNumber( wk->dat->zukan_mode, wk->pp.mons );

		if( num != 0 ){
			NumPrmSet( wk, mes_status_02_03, num, 3, NUM_MODE_ZERO );
		}else{
			MSGMAN_GetString( wk->msg_man, mes_status_02_16, wk->msg_buf );
		}
	}

	if( wk->pp.rare == 0 ){
		StrPut( wk, &wk->add_win[ADD_WIN_P1_LIBNUM], PSTCOL_N_BLACK, STR_MODE_LEFT );
	}else{
		StrPut( wk, &wk->add_win[ADD_WIN_P1_LIBNUM], PSTCOL_N_RED, STR_MODE_LEFT );
	}

	// 名前
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P1_NAME], FONT_SYSTEM,
		wk->pp.monsname, 0, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	// 親名
	if( wk->pp.oya_sex == 0 ){
		GF_STR_PrintColor(
			&wk->add_win[ADD_WIN_P1_OYANAME], FONT_SYSTEM,
			wk->pp.oya, 0, 0, MSG_NO_PUT, PSTCOL_N_BLUE, NULL );
	}else{
		GF_STR_PrintColor(
			&wk->add_win[ADD_WIN_P1_OYANAME], FONT_SYSTEM,
			wk->pp.oya, 0, 0, MSG_NO_PUT, PSTCOL_N_RED, NULL );
	}

	// IDNo.
	NumPrmSet( wk, mes_status_02_10, ( wk->pp.id & 0xffff ), 5, NUM_MODE_ZERO );
	StrPut( wk, &wk->add_win[ADD_WIN_P1_IDNO], PSTCOL_N_BLACK, STR_MODE_LEFT );

	// 現在の経験値
	NumPrmSet( wk, mes_status_02_12, wk->pp.now_exp, 7, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P1_NOWEXP], PSTCOL_N_BLACK, STR_MODE_LEFT );

	// 次のレベルまで@
/* ルビサファの育て屋でLv100以上の経験値になるため、マイナス表示になってしまう不具合対処 */
#if T1653_060815_FIX	// 対処後
	if( wk->pp.lv < 100 ){
		NumPrmSet( wk, mes_status_02_15, wk->pp.next_lv_exp-wk->pp.now_exp, 7, NUM_MODE_LEFT );
	}else{
		NumPrmSet( wk, mes_status_02_15, 0, 7, NUM_MODE_LEFT );
	}
#else					// 対処前
	NumPrmSet( wk, mes_status_02_15, wk->pp.next_lv_exp-wk->pp.now_exp, 7, NUM_MODE_LEFT );
#endif	// T1653_060815_FIX
	StrPut( wk, &wk->add_win[ADD_WIN_P1_NEXTEXP], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_LIBNUM] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_OYANAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_IDNO] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NOWEXP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NEXTEXP] );
}


#define	TRMEMO_MSGWRITE( msgdata ){												\
	if( msgdata.msg != NULL	){													\
		GF_STR_PrintColor(	win, FONT_SYSTEM, msgdata.msg,						\
							P2_MEMO_PX, P2_MEMO_PY + (msgdata.line-1) * 16,		\
							MSG_NO_PUT, PSTCOL_N_BLACK, NULL );					\
	}																			\
}

static void PST_Page2MemoPut( GF_BGL_BMPWIN* win, POKEMON_PARAM* pp, BOOL mine )
{
	TRMEMO_DATA* trdata = TrainerMemoGet( pp, mine, HEAPID_POKESTATUS );

	TRMEMO_MSGWRITE( trdata->character1 )
	TRMEMO_MSGWRITE( trdata->encount )
	TRMEMO_MSGWRITE( trdata->character2 )
	TRMEMO_MSGWRITE( trdata->palate )
	TRMEMO_MSGWRITE( trdata->eggstatus )

	TrainerMemoFree( trdata );
}

static void PST_Page2BmpPut( PST_WORK * wk )
{
	STRBUF * str;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P2_TITLE] );		// 「トレーナーメモ」

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P2_TMEMO], 0 );

	{
		void* pp = PokeStatusPokeParamGet( wk );	//ポケモンデータポインタ取得
		BOOL	orner_flag = PST_PokeOyaCheck( wk );

		//ポケモンデータの種類判別
		if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
			{
				//パソコンの場合、手持ち用データにコンバートしてから
				POKEMON_PARAM* pp_tmp = PokemonParam_AllocWork( HEAPID_POKESTATUS );

				PokeReplace( pp, pp_tmp );
				PST_Page2MemoPut( &wk->add_win[ADD_WIN_P2_TMEMO], pp_tmp, orner_flag );
		
				sys_FreeMemoryEz( pp_tmp );
			}
		} else {
			//その他通常
			PST_Page2MemoPut( &wk->add_win[ADD_WIN_P2_TMEMO], pp, orner_flag );
		}
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P2_TMEMO] );
}

static void PST_Page3BmpPut( PST_WORK * wk )
{
	u32	siz;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_TITLE] );		// 「ポケモンのうりょく」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_HP] );			// 「HP」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_POW] );		// 「こうげき」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_DEF] );		// 「ぼうぎょ」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPP] );		// 「とくこう」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPD] );		// 「とくぼう」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_AGI] );		// 「すばやさ」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPA] );		// 「とくせい」

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_HP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_POW], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_DEF], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPD], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_AGI], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPANAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPAINFO], 0 );

	// HP/MHP
	siz = GF_BGL_BmpWinGet_SizeX( &wk->add_win[ADD_WIN_P3_HP] ) * 8;
	NumSraMaxStrPut(
		wk, ADD_WIN_P3_HP, mes_status_04_09,
		mes_status_04_11, mes_status_04_10,
		wk->pp.hp, wk->pp.mhp, 3, siz/2, 0 );

	// 攻撃
	NumPrmSet( wk, mes_status_04_12, wk->pp.atc, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_POW], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 防御
	NumPrmSet( wk, mes_status_04_13, wk->pp.def, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_DEF], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 特攻
	NumPrmSet( wk, mes_status_04_14, wk->pp.spa, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_SPP], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 特防
	NumPrmSet( wk, mes_status_04_15, wk->pp.spd, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_SPD], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 素早さ
	NumPrmSet( wk, mes_status_04_16, wk->pp.agi, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_AGI], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	{
		MSGDATA_MANAGER * man;
		STRBUF * str;
		
		// 特性名
		WORDSET_RegisterTokuseiName( wk->wset, 0, wk->pp.tokusei );
		str = MSGMAN_AllocString( wk->msg_man, mes_status_04_17 );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		StrPut( wk, &wk->add_win[ADD_WIN_P3_SPANAME], PSTCOL_N_BLACK, STR_MODE_LEFT );

		// 特性説明
		man = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_tokuseiinfo_dat, HEAPID_POKESTATUS );
		MSGMAN_GetString( man, wk->pp.tokusei, wk->msg_buf );
		MSGMAN_Delete( man );
		StrPut( wk, &wk->add_win[ADD_WIN_P3_SPAINFO], PSTCOL_N_BLACK, STR_MODE_LEFT );
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_HP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_POW] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_DEF] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPD] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_AGI] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPANAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPAINFO] );
}


static void PST_Page4BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P4_TITLE] );			// 「コンディション」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P4_KEDUYA] );			// 「けづや」

	if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_LIKE], 0 );

	MSGMAN_GetString( wk->msg_man, mes_status_09_03, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_COND_LIKE], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->msg_man, mes_status_09_04+wk->pp.like, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_COND_LIKE], FONT_SYSTEM,
		wk->msg_buf, 0, CND_TASTE_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_LIKE] );

	if( wk->dat->mode == PST_MODE_PORUTO ){
		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_KETTEI], 0 );
//		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_MODORU], 0 );

		MSGMAN_GetString( wk->msg_man, mes_status_09_01, wk->msg_buf );
		StrPut( wk, &wk->add_win[ADD_WIN_COND_KETTEI], PSTCOL_N_WHITE, STR_MODE_LEFT );

//		MSGMAN_GetString( wk->msg_man, mes_status_09_02, wk->msg_buf );
//		StrPut( wk, &wk->add_win[ADD_WIN_COND_MODORU], PSTCOL_N_WHITE, STR_MODE_LEFT );

		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_KETTEI] );
//		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_MODORU] );

		PokeStatus_A_ButtonMarkPut( wk, &wk->add_win[ADD_WIN_COND_KETTEI] );
	}
}

static void PST_Page5BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_TITLE] );			// 「たたかうわざ」

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PokeStatus_GuideStrPut( wk, mes_status_06_29 );		// 「けってい」
	}else{
		PokeStatus_GuideStrPut( wk, mes_status_06_02 );		// 「くわしく」
	}
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA2], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA3], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA4], 0 );

	WazaPut( wk, 0 );
	WazaPut( wk, 1 );
	WazaPut( wk, 2 );
	WazaPut( wk, 3 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA2] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA3] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA4] );
}

static void PST_Page6BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P6_TITLE] );			// 「コンテストわざ」

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PokeStatus_GuideStrPut( wk, mes_status_07_03 );			// 「けってい」
	}else{
		PokeStatus_GuideStrPut( wk, mes_status_07_02 );			// 「くわしく」
	}
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA1], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA2], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA3], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA4], 0 );

	WazaPut( wk, 0 );
	WazaPut( wk, 1 );
	WazaPut( wk, 2 );
	WazaPut( wk, 3 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA1] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA2] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA3] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA4] );
}

static void PST_Page7BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P7_TITLE] );			// 「きねんリボン」
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P7_MOTTEIRU] );		// 「もっているかず」

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_NUM], 0 );
	NumPrmSet( wk, mes_status_10_05, wk->ribbon_max, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_NUM], PSTCOL_N_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_NUM] );

	if( wk->ribbon_max != 0 ){
		PokeStatus_GuideStrPut( wk, mes_status_10_02 );				// 「くわしく」
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
	}
}

static void PST_Page8BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P8_MODORIMASU] );		// 「もどります」
	PokeStatus_GuideStrPut( wk, mes_status_08_01 );				// 「もどる」
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_LIKE], 0 );

	MSGMAN_GetString( wk->msg_man, mes_status_09_03, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_COND_LIKE], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->msg_man, mes_status_09_04+wk->pp.like, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_COND_LIKE], FONT_SYSTEM,
		wk->msg_buf, 0, CND_TASTE_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_LIKE] );
}


void PokeStatus_RibbonPosNumPut( PST_WORK * wk )
{
	STRBUF * str;
	u8	px;
	u8	siz;

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_MAXNUM], 0 );

	// 最大数
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_08 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->ribbon_max, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	px  = A_WIN_P7_MAX_SX * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		wk->msg_buf, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	// スラッシュ
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_07 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px -= siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		str, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	// カーソル位置
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_06 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->ribbon_pos+wk->ribbon_scr*4+1,
		3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	px -= siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		wk->msg_buf, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_MAXNUM] );
}

void PokeStatus_RibbonInfoPut( PST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_NAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_INFO], 0 );

	MSGMAN_GetString( wk->rbn_man, RIBBON_DataGet(wk->ribbon_num,RIBBON_PARA_NAME), wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_NAME], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->rbn_man, RIBBON_InfoGet(wk->dat->ribbon,wk->ribbon_num), wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_INFO], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_NAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_INFO] );
}



static void WazaPut( PST_WORK * wk, u32 pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;
	u16	waza;
	u8	npp, mpp;

	win = &wk->add_win[ADD_WIN_P5_WAZA1+pos];

	if( pos != 4 ){
		waza = wk->pp.waza[pos];
		npp  = wk->pp.wpp[pos];
		mpp  = wk->pp.mpp[pos];
	}else{
		waza = wk->dat->waza;
		npp  = WT_PPMaxGet( waza, 0 );
		mpp  = npp;
	}

	// 技名
	MSGMAN_GetString( wk->wman, waza, wk->msg_buf );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf,
		P5_WAZA_PX, P5_WAZA_PY, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );

	// PP
	if( waza != 0 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_08, wk->msg_buf );
		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			P5_PP_PX, P5_PP_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
		NumSraMaxStrPut(
			wk, ADD_WIN_P5_WAZA1+pos, mes_status_04_09,
			mes_status_06_09+pos, mes_status_06_14+pos,
			npp, mpp, 2, P5_PPNUM_PX, P5_PPNUM_PY );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_status_06_27, wk->msg_buf );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			P5_PPNUM_PX-siz/2, P5_PP_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	}
}


void PokeStatus_WazaInfoPut( PST_WORK * wk, u32 waza )
{
	MSGDATA_MANAGER * man;
	u32	siz;
	u32	prm;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_BUNRUI] );	// ぶんるい
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_IRYOKU] );	// いりょく
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_HIT] );	// めいちゅう

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_ATC], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_HIT], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_INFO], 0 );

	// 威力
	prm = WT_WazaDataParaGet( waza, ID_WTD_damage );
	if( prm <= 1 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_28, wk->msg_buf );
	}else{
		NumPrmSet( wk, mes_status_06_23, prm, 3, NUM_MODE_LEFT );
	}
	StrPut( wk, &wk->add_win[ADD_WIN_P5_ATC], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 命中
	prm = WT_WazaDataParaGet(waza,ID_WTD_hitprobability);
	if( prm == 0 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_28, wk->msg_buf );
	}else{
		NumPrmSet( wk, mes_status_06_24, prm, 3, NUM_MODE_LEFT );
	}
	StrPut( wk, &wk->add_win[ADD_WIN_P5_HIT], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// 説明
	man = MSGMAN_Create(
			MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazainfo_dat, HEAPID_POKESTATUS );
	MSGMAN_GetString( man, waza, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P5_INFO], PSTCOL_N_BLACK, STR_MODE_LEFT );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_ATC] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_HIT] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_INFO] );
}

void PokeStatus_WazaInfoOff( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_BUNRUI] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_IRYOKU] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_HIT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_ATC] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_HIT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_INFO] );
}

void PokeStatus_SkillCancelPut( PST_WORK * wk )
{
	if( wk->dat->waza != 0 ){
		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA5], 0 );
		WazaPut( wk, 4 );
		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA5] );
	}else{
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_MODORU] );
	}
}

void PokeStatus_SkillCancelDel( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_MODORU] );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );
}




void PokeStatus_SkillChgRewrite( PST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1+wk->cur_pos], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1+wk->sub_cur], 0 );

	WazaPut( wk, wk->cur_pos );
	WazaPut( wk, wk->sub_cur );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1+wk->cur_pos] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1+wk->sub_cur] );
}


void PokeStatus_WazaOboeErrorMsgPut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;

	if( wk->page == PST_PAGE_B_SKILL ){
//		PokeStatus_WazaInfoOff( wk );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_ATC] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_HIT] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_INFO] );
		win = &wk->add_win[ADD_WIN_P5_INFO];
	}else{
//		PokeStatus_ContestWazaInfoOff( wk );
		win = &wk->add_win[ADD_WIN_P6_INFO];
	}
	GF_BGL_BmpWinDataFill( win, 0 );
	MSGMAN_GetString( wk->msg_man, mes_status_06_30, wk->msg_buf );
	StrPut( wk, win, PSTCOL_N_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( win );
}


void PokeStatus_ContestWazaInfoPut( PST_WORK * wk, u32 waza )
{
	MSGDATA_MANAGER * man;
	u32	ap_no;
	u32	msg_id;

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_INFO], 0 );

	ap_no  = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
	msg_id = ConTool_GetListAPSetumeiMsgID( ap_no );

	man = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_wazaexplain_dat, HEAPID_POKESTATUS );

	MSGMAN_GetString( man, msg_id, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P6_INFO], FONT_SYSTEM,
		wk->msg_buf, 0, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P6_AP_POINT] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_INFO] );
}

void PokeStatus_ContestWazaInfoOff( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P6_AP_POINT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P6_INFO] );
}





void PokeStatus_CondUpMsgPut( PST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	u32	midx;

	switch( num ){
	case 0:		// かっこよさ
		midx = mes_status_09_09_01;
		break;
	case 1:		// うつくしさ
		midx = mes_status_09_09_03;
		break;
	case 2:		// かわいさ
		midx = mes_status_09_09_04;
		break;
	case 3:		// かしこさ
		midx = mes_status_09_09_05;
		break;
	case 4:		// たくましさ
		midx = mes_status_09_09_02;
		break;
	case PST_MSG_PRMNONE:	// 変化なし
		midx = mes_status_09_09_06;
		break;
	default:	// 食べられない
		midx = mes_status_09_09_07;
	}

	win = &wk->add_win[ADD_WIN_COND_MSG];
	BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PST_CGX_TALKWIN, PST_PAL_TALKWIN );
	GF_BGL_BmpWinDataFill( win, 15 );
	MSGMAN_GetString( wk->msg_man, midx, wk->msg_buf );
	GF_STR_PrintColor( win, FONT_TALK, wk->msg_buf, 0, 0, MSG_NO_PUT, PSTCOL_W_BLACK, NULL );
	GF_BGL_BmpWinOnVReq( win );
}
