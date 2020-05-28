//============================================================================================
/**
 * @file	vs_demo.c
 * @brief	通信対戦デモ
 * @author	Hiroyuki Nakamura
 * @date	06.04.26
 */
//============================================================================================
#include "common.h"
#include "gflib/strbuf_family.h"
#include "system/procsys.h"
#include "system/palanm.h"
#include "system/lib_pack.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/fontoam.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/wipe.h"
#include "system/particle.h"
#include "system/snd_tool.h"
#include "system/buflen.h"
#include "poketool/pokeparty.h"
#include "poketool/pokeicon.h"
#include "poketool/tr_tool.h"
#include "itemtool/item.h"
#include "application/app_tool.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokelist.h"
#include "communication/wm_icon.h"
#include "communication/comm_system.h"
#include "communication/comm_def.h"
#include "communication/comm_state.h"

#include "battle_input.h"
#include "graphic/batt_obj_def.h"
#include "../particledata/particledata.h"
#include "../particledata/particledata.naix"
#include "../field/zonedata.h"

#include "vs_demo.h"
#include "vs_demo_def.h"
#include "vs_demo_gra.naix"
#include "application/plist_gra.naix"
#include "application/pst_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================
typedef struct _VSD_WORK	VSD_WORK;
typedef u8 (*VSD_FUNC)(VSD_WORK*);

// マルチ確認用ポケモンワーク
typedef struct {
	u32	chr_arc;	// キャラデータのアークID
	u16 mons;		// ポケモン番号
	u16	hp;			// HP
	u16	mhp;		// MHP
	u16	item;		// アイテム
	u8	lv;			// レベル
	u8	sex;		// 性別
	u8	sex_put;	// 性別表示
	u8	egg;		// タマゴフラグ
	u8	cb;			// カスタムボール
	u8	form;		// フォルムNo
	u32	st;			// 状態異常
}VSD_POKE;

// デモ画面ワーク
struct _VSD_WORK {
	VS_DEMO_DATA * dat;		// 外部設定データ
	const VSD_FUNC * func;	// 処理テーブル

	PALETTE_FADE_PTR pfd;	// パレットフェードデータ

	GF_BGL_INI * bgl;					// BGLデータ
	GF_BGL_BMPWIN	win[VSD_BMP_MAX];	// BMPウィンドウ

	// セルアクター
	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap[VS_CLA_PLMAX];
	u32	cap_max;				// 使用しているセルアクター数

	/******************************* マルチ確認用 *************************************/
	VSD_POKE	poke[6];	// ポケモンワーク

	u16	plate_top[PL_PANEL_SX*PL_PANEL_SY];		// 先頭のプレートのスクリーンデータ
	u16	plate_normal[PL_PANEL_SX*PL_PANEL_SY];	// 通常のプレートのスクリーンデータ
	u16	plate_none[PL_PANEL_SX*PL_PANEL_SY];	// いない場合のプレートのスクリーンデータ

	u16	pal[16*3];						// パレット保存
	u16	plate_bg[2][PL_PANEL_SX*24];	// スクロールのためのBGスクリーン保存領域

	/******************************* VS画面用 *************************************/
	FONTOAM_SYS_PTR fsp;		// フォントOAMシステム
	FONTOAM_OBJ_PTR	fop[4];		// フォントOAMデータ

	GF_G3DMAN * g3dm;
	PTC_PTR	ptc;		// パーティクルシステム
	void * ptm;			// パーティクルで使用するヒープエリア

	u8	ball_gx[4];		// 手持ちボールの基本X座標(0,1=自分側、2,3=敵側)
	u8	ball_gy[4];		// 手持ちボールの基本Y座標(0,1=自分側、2,3=敵側)
	u8	name_gx[4];		// トレーナー名の基本X座標(0,1=自分側、2,3=敵側)
	u8	name_gy[4];		// トレーナー名の基本Y座標(0,1=自分側、2,3=敵側)

	s32	scr_spd;		// スクロール速度

	s16	old_sx;			// 画面のX揺れ幅記憶
	s16	old_sy;			// 画面のY揺れ幅記憶

	s8	shake_x;		// 画面のX揺れ幅
	s8	shake_y;		// 画面のY揺れ幅

	u8	push_mv;		// プレート押し出し方向

	/******************************************************************************/

	u8	seq;		// メインシーケンス
	u8	func_seq;	// 処理シーケンス
	u8	wait;		// ウェイト
	u8	cnt;		// 汎用カウンタ
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void VSDemo_Main( TCB_PTR tcb, void * work );
static void VSD_VramSet(void);

static u8 VSD_SeqInit( VSD_WORK * wk );
static u8 VSD_SeqWait( VSD_WORK * wk );
static u8 VSD_SeqScrInMain( VSD_WORK * wk );
static u8 VSD_SeqShake( VSD_WORK * wk );
static u8 VSD_SeqScrOut( VSD_WORK * wk );
static u8 VSD_SeqShakeWaitSet( VSD_WORK * wk );
static u8 VSD_SeqPushCheck( VSD_WORK * wk );
static u8 VSD_SeqPush( VSD_WORK * wk );
static u8 VSD_SeqLeftPush( VSD_WORK * wk );
static u8 VSD_SeqRightPush( VSD_WORK * wk );
static u8 VSD_SeqEndSet( VSD_WORK * wk );
static u8 VSD_SeqEnd( TCB_PTR tcb, VSD_WORK * wk );
static u8 VSD_SeqPuchWaitSet( VSD_WORK * wk );
static u8 VSD_SeqResultOpen( VSD_WORK * wk );
static u8 VSD_SeqResultPut( VSD_WORK * wk );
static u8 VSD_SeqDrawPut( VSD_WORK * wk );
static u8 VSD_SeqPlatePalChg( VSD_WORK * wk );
static u8 VSD_SeqVsStartInit( VSD_WORK * wk );
static u8 VSD_SeqVsEndInit( VSD_WORK * wk );
static u8 VSD_SeqPokeCheckInit( VSD_WORK * wk );
static u8 VSD_PokeCheckMove( VSD_WORK * wk );
static BOOL VSD_GetStandID(void);

static void VSD_ClactResManInit( VSD_WORK * wk, TCATS_RESOURCE_NUM_LIST * crnl, int max );
static CATS_ACT_PTR VSD_ClactAdd( VSD_WORK * wk, const u32 * id );
static void VSD_ObjFree( VSD_WORK * wk );
static void VSD_ObjAnm( VSD_WORK * wk );

static void VSD_VsVBlank( void * work );
static void VSD_3DBgInit( VSD_WORK * wk );
static void VSD_3DBgExit( VSD_WORK * wk );
static void VSD_VsBgGraphicSet( VSD_WORK * wk );
static void VSD_VsAlphaSet(void);
static void VSD_VsObjMake( VSD_WORK * wk );
static void VSD_VsObjGlobalPosSet( VSD_WORK * wk );
static void VSD_VsBallObjMake( VSD_WORK * wk );
static void VSD_VsBallObjMove( VSD_WORK * wk, u8 flg, s16 x, s16 y );
static void VSD_VsBallAnmChg( VSD_WORK * wk );
static void VSD_VsFontOamMake( VSD_WORK * wk );
static void VSD_VsFontOamMove( VSD_WORK * wk, u32 id, s16 x, s16 y );
static void VSD_VsFontOamDelete( VSD_WORK * wk );
static void VSD_VsParticleInit( VSD_WORK * wk );
static int VSD_VsParticleMain( VSD_WORK * wk );
static void VSD_VsParticleDelete( VSD_WORK * wk );
static void VSD_VsEndObjMake( VSD_WORK * wk );
static void VSD_VsResultObjMake( VSD_WORK * wk );
static void VSD_VsResultMove( VSD_WORK * wk );

static void VSD_PokeCheckBgInit( VSD_WORK * wk );
static void VSD_PokeCheckBgExit( VSD_WORK * wk );
static void VSD_PokeCheckBgGraphicSet( VSD_WORK * wk );
static void VSD_PokeCheckObjMake( VSD_WORK * wk );
static void VSD_PokeParamGet( VSD_WORK * wk );
static void VSD_PokeCheckBgPut( VSD_WORK * wk );
static void VSD_PokeCheckBgCopy( VSD_WORK * wk );
static void VSD_PokeCheckBgMove( VSD_WORK * wk, u8 cnt );
static void VSD_PokeCheckBmpAdd( VSD_WORK * wk );
static void VSD_PokeCheckBmpExit( VSD_WORK * wk );
static void VSD_PokeCheckBmpPut( VSD_WORK * wk );
static void VSD_PokeCheckPokeIconMake( VSD_WORK * wk );
static void VSD_PokeCheckItemIconMake( VSD_WORK * wk );
static void VSD_PokeCheckStIconMake( VSD_WORK * wk );
static void VSD_PokeCheckBallMake( VSD_WORK * wk );
static void VSD_PokeCheckObjMove( VSD_WORK * wk, s16 mv );

static u32 sAllocTex( u32 size, BOOL is4x4comp );
static u32 sAllocTexPalette( u32 size, BOOL is4pltt );

static void VSD_FnoteMake( VS_DEMO_DATA * dat );


//============================================================================================
//	グローバル変数
//============================================================================================
// VS画面、勝敗画面のセルアクターパラメータ
static const u32 VS_ClactParam[][7] =
{	// chr_id, pal_id, cell_id, anm_id, bg_pri, obj_pri, pal_num
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },

	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },
	{ VS_CHR_ID_BALL, VS_PAL_ID_BALL, VS_CEL_ID_BALL, VS_ANM_ID_BALL, 2, 0, 0 },

	{ VS_CHR_ID_RESULT, VS_PAL_ID_BALL, VS_CEL_ID_RESULT, VS_ANM_ID_RESULT, 1, 0, 1 },
	{ VS_CHR_ID_RESULT, VS_PAL_ID_BALL, VS_CEL_ID_RESULT, VS_ANM_ID_RESULT, 1, 0, 1 },
};

// 処理テーブル：ポケモン確認画面
static const VSD_FUNC PokeCheckFuncTable[] = {
	VSD_SeqPokeCheckInit,
	VSD_SeqWait,			// ウェイト
	VSD_PokeCheckMove,
	VSD_SeqWait,			// ウェイト
	VSD_SeqEndSet,
};

// 処理テーブル：VS画面
static const VSD_FUNC VsStartFuncTable[] = {
	VSD_SeqVsStartInit,
	VSD_SeqWait,			// ウェイト
	VSD_SeqScrInMain,		// スクロールインメイン
	VSD_SeqShake,			// 揺らす
	VSD_SeqScrOut,			// スクロールアウト
};

// 処理テーブル：勝敗あり
static const VSD_FUNC VsEndWinFuncTable[] = {
	VSD_SeqVsEndInit,
	VSD_SeqWait,		// ウェイト
	VSD_SeqScrInMain,	// スクロールインメイン
	VSD_SeqShake,		// 揺らす
	VSD_SeqShakeWaitSet,
	VSD_SeqWait,
	VSD_SeqPushCheck,
	VSD_SeqPush,
	VSD_SeqPuchWaitSet,
	VSD_SeqResultOpen,
	VSD_SeqWait,
	VSD_SeqResultPut,
	VSD_SeqWait,
	VSD_SeqPlatePalChg,
	VSD_SeqWait,
	VSD_SeqEndSet,
};

// 処理テーブル：引き分け
static const VSD_FUNC VsEndDrawFuncTable[] = {
	VSD_SeqVsEndInit,
	VSD_SeqWait,		// ウェイト
	VSD_SeqScrInMain,	// スクロールインメイン
	VSD_SeqShake,		// 揺らす
	VSD_SeqPuchWaitSet,
	VSD_SeqResultOpen,
	VSD_SeqWait,
	VSD_SeqDrawPut,
	VSD_SeqWait,
	VSD_SeqEndSet,
};

// 勝敗画面：プレート押し出しテーブル
static const u8 VSD_PushMoveTbl[][2] =
{
	// BG, OBJ
	{ 8, 8 }, { 0, 8 }, { 0, 8 }, { 4, 12 }, { 0, 12 }, { 0, 12 },
};

// 確認画面：BMPウィンドウ定義
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
};

// 確認画面：プレートBG表示位置
static const u8 PokeCheckBgPos[][2] =
{	// LTX, LTY
	{ 0, 0 }, { 0, 6 }, { 0, 12 }, { 16, 1 }, { 16, 7 }, { 16, 13 }
};

// 確認画面：OBJ表示座標テーブル
static const u8 PokeCheckObjPosTable[][10] =
{	// ポケモン、アイテム、カスタムボール、状態異常、ボール
	{  30,  16,  38,  24,  46,  24,  36,  44,  16,  14 },	// １匹目
	{  30,  64,  38,  72,  46,  72,  36,  92,  16,  62 },	// ２匹目
	{  30, 112,  38, 120,  46, 120,  36, 140,  16, 110 },	// ３匹目
	{ 158,  24, 166,  32, 174,  32, 164,  52, 144,  22 },	// ４匹目
	{ 158,  72, 166,  80, 174,  80, 164, 100, 144,  70 },	// ５匹目
	{ 158, 120, 166, 128, 174, 128, 164, 148, 144, 118 }	// ６匹目
};

// 確認画面のセルアクターパラメータ
static const u32 PokeCheck_ClactParam[][7] =
{	// chr_id, pal_id, cell_id, anm_id, bg_pri, obj_pri, pal_num
	{ VS_CHR_ID_POKE1, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },

	{ VS_CHR_ID_POKE2, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },

	{ VS_CHR_ID_POKE3, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },

	{ VS_CHR_ID_POKE4, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },

	{ VS_CHR_ID_POKE5, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },

	{ VS_CHR_ID_POKE6, VS_PAL_ID_POKE, VS_CEL_ID_POKE, VS_ANM_ID_POKE, 1, 1, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ITEM, VS_PAL_ID_ITEM, VS_CEL_ID_ITEM, VS_ANM_ID_ITEM, 1, 0, 0 },
	{ VS_CHR_ID_ST, VS_PAL_ID_ST, VS_CEL_ID_ST, VS_ANM_ID_ST, 1, 0, 0 },
	{ VS_CHR_ID_PLBALL, VS_PAL_ID_PLBALL, VS_CEL_ID_PLBALL, VS_ANM_ID_PLBALL, 1, 2, 0 },
};


//--------------------------------------------------------------------------------------------
/**
 * タスク追加
 *
 * @param	dat		バッグデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void VSDemo_TaskAdd( VS_DEMO_DATA * dat )
{
	VSD_WORK * wk;

	wk = TCB_GetWork( PMDS_taskAdd(VSDemo_Main,sizeof(VSD_WORK),100,dat->heap) );

	memset( wk, 0, sizeof(VSD_WORK) );
	wk->dat = dat;
	wk->seq = SEQ_VSD_INIT;
}

//--------------------------------------------------------------------------------------------
/**
 * メインタスク
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSDemo_Main( TCB_PTR tcb, void * work )
{
	VSD_WORK * wk = work;

	switch( wk->seq ){
	case SEQ_VSD_INIT:		// 初期化
		wk->seq = VSD_SeqInit( wk );
		break;

	case SEQ_VSD_MAIN:
		while(1){
			u8	ret = wk->func[wk->func_seq]( wk );
			if( ret != VSD_FUNC_LOOP ){
				wk->func_seq++;
			}
			if( ret != VSD_FUNC_REPEAT ){
				break;
			}
		}
		break;

	case SEQ_VSD_END:		// 終了
		if( VSD_SeqEnd( tcb, wk ) == TRUE ){
			return;
		}
	}

	if( wk->func_seq != 0 ){	// 初期化中以外
		VSD_ObjAnm( wk );
		CATS_Draw( wk->crp );
	}
	if( wk->dat->mode != VSD_MODE_MULTI ){
		G3_SwapBuffers( GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VramSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//--------------------------------------------------------------------------------------------
/**
 * 初期化シーケンス
 *
 * @param	wk		ワーク
 *
 * @return	移行するシーケンス
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqInit( VSD_WORK * wk )
{
	G2_BlendNone();

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();				// HBlank停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	G2_BlendNone();
	G2S_BlendNone();

	VSD_VramSet();

	wk->bgl = GF_BGL_BglIniAlloc( wk->dat->heap );
	wk->pfd = PaletteFadeInit( wk->dat->heap );
	PaletteFadeWorkAllocSet( wk->pfd, FADE_MAIN_BG, FADE_PAL_ONE_SIZE*3, wk->dat->heap );

	wk->cnt  = 0;
	wk->wait = INIT_WAIT;

	wk->func_seq = 0;

	switch( wk->dat->mode ){
	case VSD_MODE_MULTI:
		wk->func = PokeCheckFuncTable;
		break;
	case VSD_MODE_IN:
		wk->func = VsStartFuncTable;
		break;
	case VSD_MODE_END:
		if( wk->dat->result == VSD_RESULT_DRAW ){
			wk->func = VsEndDrawFuncTable;
		}else{
			wk->func = VsEndWinFuncTable;
		}
		VSD_FnoteMake( wk->dat );
		break;
	}

	return SEQ_VSD_MAIN;
}


//--------------------------------------------------------------------------------------------
/**
 * メイン処理：確認画面の初期化
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqPokeCheckInit( VSD_WORK * wk )
{
	switch( wk->cnt ){
	case 0:
		VSD_PokeCheckBgInit( wk );
		VSD_PokeCheckBgGraphicSet( wk );
		break;
	case 1:
		VSD_PokeParamGet( wk );
		VSD_PokeCheckObjMake( wk );
		break;
	case 2:
		wk->cnt = 0;
		wk->wait = POKECHECK_INIT_WAIT;
		VSD_PokeCheckBgPut( wk );
		VSD_PokeCheckBmpAdd( wk );
		VSD_PokeCheckBmpPut( wk );
		VSD_PokeCheckBgCopy( wk );
		WirelessIconEasy();
		APP_WipeStart( APP_WIPE_IN, wk->dat->heap );
		sys_VBlankFuncChange( VSD_VsVBlank, wk );	// VBlankセット
		return VSD_FUNC_NEXT;
	}
	wk->cnt++;
	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：VS画面の初期化
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqVsStartInit( VSD_WORK * wk )
{
	switch( wk->cnt ){
	case 0:
		VSD_3DBgInit( wk );
		VSD_VsBgGraphicSet( wk );
		VSD_VsAlphaSet();
		break;
	case 1:
		VSD_VsObjGlobalPosSet( wk );
		VSD_VsObjMake( wk );
		WirelessIconEasy();
		VSD_VsParticleInit( wk );
		break;
	case 2:
		APP_WipeStart( APP_WIPE_IN, wk->dat->heap );
		sys_VBlankFuncChange( VSD_VsVBlank, wk );	// VBlankセット
		wk->cnt = 0;
		wk->shake_x = START_SHAKE_X;
		wk->shake_y = START_SHAKE_Y;
		wk->scr_spd = SCROLL_SPEED;
		return VSD_FUNC_NEXT;
	}
	wk->cnt++;
	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面の初期化
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqVsEndInit( VSD_WORK * wk )
{
	switch( wk->cnt ){
	case 0:
		VSD_3DBgInit( wk );
		VSD_VsBgGraphicSet( wk );
		VSD_VsAlphaSet();
		break;
	case 1:
		VSD_VsObjGlobalPosSet( wk );
		VSD_VsEndObjMake( wk );
		WirelessIconEasy();
		break;
	case 2:
		APP_WipeStart( APP_WIPE_IN, wk->dat->heap );
		sys_VBlankFuncChange( VSD_VsVBlank, wk );	// VBlankセット
		wk->cnt = 0;
		wk->shake_x = END_SHAKE_X;
		wk->shake_y = END_SHAKE_Y;
		wk->scr_spd = END_SCROLL_SPEED;
		return VSD_FUNC_NEXT;
	}

	wk->cnt++;
	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：ウェイト
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqWait( VSD_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == FALSE ){ return VSD_FUNC_LOOP; }

	if( wk->wait == wk->cnt ){
		wk->cnt = 0;
		return VSD_FUNC_NEXT;
	}
	wk->cnt++;
	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：VS画面・確認画面のスクロールイン処理
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqScrInMain( VSD_WORK * wk )
{
	if( GF_BGL_ScrollGetX( wk->bgl, GF_BGL_FRAME3_M ) <= SCROLL_END ){
		wk->cnt = 0;
		wk->old_sx = 0;
		wk->old_sy = 0;

		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, SCROLL_END );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, -SCROLL_END );

		VSD_VsBallObjMove( wk, 0, 0, 0 );
		VSD_VsBallObjMove( wk, 1, 0, 0 );
		VSD_VsBallObjMove( wk, 2, 0, 0 );
		VSD_VsBallObjMove( wk, 3, 0, 0 );

		VSD_VsFontOamMove( wk, 0, 0, 0 );
		VSD_VsFontOamMove( wk, 1, 0, 0 );
		VSD_VsFontOamMove( wk, 2, 0, 0 );
		VSD_VsFontOamMove( wk, 3, 0, 0 );

		return VSD_FUNC_NEXT;
	}

	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_DEC, wk->scr_spd );
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_INC, wk->scr_spd );

	wk->cnt++;

	VSD_VsBallObjMove( wk, 0, wk->scr_spd * wk->cnt - SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 1, wk->scr_spd * wk->cnt - SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 2, SCROLL_INIT - wk->scr_spd * wk->cnt, 0 );
	VSD_VsBallObjMove( wk, 3, SCROLL_INIT - wk->scr_spd * wk->cnt, 0 );

	VSD_VsFontOamMove( wk, 0, wk->scr_spd * wk->cnt - SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 1, wk->scr_spd * wk->cnt - SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 2, SCROLL_INIT - wk->scr_spd * wk->cnt, 0 );
	VSD_VsFontOamMove( wk, 3, SCROLL_INIT - wk->scr_spd * wk->cnt, 0 );

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：VS画面・確認画面の揺らす処理
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqShake( VSD_WORK * wk )
{
	s16	x, y;

	if( VSD_VsParticleMain( wk ) == FALSE && wk->cnt > SHAKE_CNT ){
		wk->cnt = 0;
		return VSD_FUNC_NEXT;
	}

	if( wk->cnt == 0 ){
		if( wk->dat->mode == VSD_MODE_IN ){
			Snd_SePlay( VSD_SE_VS_PLATE_BREAK );
		}else{
			Snd_SePlay( VSD_SE_RESULT_PLATE_BREAK );
		}
	}

	if( wk->cnt == SHAKE_CNT ){
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, SCROLL_END );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, -SCROLL_END );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 0 );

		VSD_VsBallObjMove( wk, 0, 0, 0 );
		VSD_VsBallObjMove( wk, 1, 0, 0 );
		VSD_VsBallObjMove( wk, 2, 0, 0 );
		VSD_VsBallObjMove( wk, 3, 0, 0 );

		VSD_VsFontOamMove( wk, 0, 0, 0 );
		VSD_VsFontOamMove( wk, 1, 0, 0 );
		VSD_VsFontOamMove( wk, 2, 0, 0 );
		VSD_VsFontOamMove( wk, 3, 0, 0 );

	}else if( wk->cnt < SHAKE_CNT ){

		x = ( gf_rand() % wk->shake_x ) - ( wk->shake_x / 2 );
		y = ( gf_rand() % wk->shake_y ) - ( wk->shake_y / 2 );

		if( ( x < 0 && wk->old_sx < 0 ) || ( x >0 && wk->old_sx > 0 ) ){
			x *= -1;
		}
		if( ( y < 0 && wk->old_sy < 0 ) || ( y >0 && wk->old_sy > 0 ) ){
			y *= -1;
		}

		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, SCROLL_END+x );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, -SCROLL_END+x );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, y );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, y );

		VSD_VsBallObjMove( wk, 0, x, y );
		VSD_VsBallObjMove( wk, 1, x, y );
		VSD_VsBallObjMove( wk, 2, x, y );
		VSD_VsBallObjMove( wk, 3, x, y );

		VSD_VsFontOamMove( wk, 0, x, y );
		VSD_VsFontOamMove( wk, 1, x, y );
		VSD_VsFontOamMove( wk, 2, x, y );
		VSD_VsFontOamMove( wk, 3, x, y );

		wk->old_sx = x;
		wk->old_sy = y;
	}

	wk->cnt++;

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：VS画面のスクロールアウト処理
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqScrOut( VSD_WORK * wk )
{
	if( wk->cnt == 8 ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->dat->heap );
	}

	if( wk->cnt >= 8 && WIPE_SYS_EndCheck() == TRUE ){
		wk->seq = SEQ_VSD_END;
		return VSD_FUNC_NEXT;
	}

	if( wk->cnt == 0 ){
		Snd_SePlay( VSD_SE_VS_PLATE_OUT );
	}

	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_INC, SCROLL_SPEED );
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, SCROLL_SPEED );

	wk->cnt++;

	VSD_VsBallObjMove( wk, 0, -SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsBallObjMove( wk, 1, -SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsBallObjMove( wk, 2, SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsBallObjMove( wk, 3, SCROLL_SPEED * wk->cnt, 0 );

	VSD_VsFontOamMove( wk, 0, -SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsFontOamMove( wk, 1, -SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsFontOamMove( wk, 2, SCROLL_SPEED * wk->cnt, 0 );
	VSD_VsFontOamMove( wk, 3, SCROLL_SPEED * wk->cnt, 0 );

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面の揺らした後のウェイト設定
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqShakeWaitSet( VSD_WORK * wk )
{
	wk->wait = SHAKE_WAIT;
	return VSD_FUNC_REPEAT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のプレート押し出し方向設定
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqPushCheck( VSD_WORK * wk )
{
	if( VSD_GetStandID() == TRUE ){
		if( wk->dat->result == VSD_RESULT_WIN ){
			wk->push_mv = VSD_TYPE_LEFT;
		}else{
			wk->push_mv = VSD_TYPE_RIGHT;
		}
	}else{
		if( wk->dat->result == VSD_RESULT_WIN ){
			wk->push_mv = VSD_TYPE_RIGHT;
		}else{
			wk->push_mv = VSD_TYPE_LEFT;
		}
	}
	return VSD_FUNC_REPEAT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のプレート押し出し処理（総合）
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqPush( VSD_WORK * wk )
{
	if( wk->push_mv == VSD_TYPE_LEFT ){
		return VSD_SeqLeftPush( wk );
	}
	return VSD_SeqRightPush( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のプレート押し出し処理（左が押す）
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqLeftPush( VSD_WORK * wk )
{
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, VSD_PushMoveTbl[wk->cnt][0] );
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_DEC, VSD_PushMoveTbl[wk->cnt][0] );
	VSD_VsBallObjMove( wk, 0, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 1, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 2, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 3, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 0, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 1, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 2, VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 3, VSD_PushMoveTbl[wk->cnt][1], 0 );

	if( wk->cnt == 0 ){
		Snd_SePlay( VSD_SE_RESULT_PLATE_MOVE );
	}

	if( wk->cnt == 5 ){
		wk->cnt = 0;
		return VSD_FUNC_NEXT;
	}else{
		wk->cnt++;
	}

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のプレート押し出し処理（右が押す）
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqRightPush( VSD_WORK * wk )
{
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_INC, VSD_PushMoveTbl[wk->cnt][0] );
	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_INC, VSD_PushMoveTbl[wk->cnt][0] );
	VSD_VsBallObjMove( wk, 0, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 1, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 2, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsBallObjMove( wk, 3, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 0, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 1, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 2, -VSD_PushMoveTbl[wk->cnt][1], 0 );
	VSD_VsFontOamMove( wk, 3, -VSD_PushMoveTbl[wk->cnt][1], 0 );

	if( wk->cnt == 0 ){
		Snd_SePlay( VSD_SE_RESULT_PLATE_MOVE );
	}

	if( wk->cnt == 5 ){
		wk->cnt = 0;
		return VSD_FUNC_NEXT;
	}else{
		wk->cnt++;
	}

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のプレート押し出し後のウェイト設定
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqPuchWaitSet( VSD_WORK * wk )
{
	wk->wait = PUSH_WAIT;
	return VSD_FUNC_REPEAT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面の勝敗ウィンドウオープン
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqResultOpen( VSD_WORK * wk )
{
	if( wk->cnt == 0 ){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

		GX_SetVisibleWnd( GX_WNDMASK_W0 );
		G2_SetWnd0InsidePlane(
			GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG1|
			GX_WND_PLANEMASK_BG2|GX_WND_PLANEMASK_BG3|GX_WND_PLANEMASK_OBJ, TRUE );
		G2_SetWndOutsidePlane(
			GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_BG2|
			GX_WND_PLANEMASK_BG3|GX_WND_PLANEMASK_OBJ, FALSE );
	}

	if( wk->cnt == RESULT_OPEN_CNT ){
		wk->cnt = 0;
		wk->wait = RESULT_WAIT;
		GX_SetVisibleWnd( GX_WNDMASK_NONE );
		return VSD_FUNC_NEXT;
	}else{
		G2_SetWnd0Position( 0, 95-wk->cnt, 255, 96+wk->cnt );
		wk->cnt++;
	}

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面の勝敗表示
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqResultPut( VSD_WORK * wk )
{
	Snd_SePlay( VSD_SE_RESULT_PUT );

	CATS_ObjectEnableCap( wk->cap[VS_CLA_RESULT1], 1 );
	CATS_ObjectEnableCap( wk->cap[VS_CLA_RESULT2], 1 );
	CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], 0 );
	wk->wait = RESULT_WAIT;
	return VSD_FUNC_NEXT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面の引き分け表示
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqDrawPut( VSD_WORK * wk )
{
	Snd_SePlay( VSD_SE_RESULT_PUT );

	CATS_ObjectEnableCap( wk->cap[VS_CLA_RESULT1], 1 );
	wk->wait = RESULT_END_WAIT;
	return VSD_FUNC_NEXT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：勝敗画面のパレット変更
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqPlatePalChg( VSD_WORK * wk )
{
	if( VSD_GetStandID() == TRUE ){
		if( wk->dat->result == VSD_RESULT_WIN ){
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, RESULT_WIN_CHG_PAL, 0, 0, 4, 0 );
		}else{
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, RESULT_LOSE_CHG_PAL, 0, 0, 4, 0 );
		}
	}else{
		if( wk->dat->result == VSD_RESULT_WIN ){
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, RESULT_LOSE_CHG_PAL, 0, 0, 4, 0 );
		}else{
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, RESULT_WIN_CHG_PAL, 0, 0, 4, 0 );
		}
	}
	Snd_SePlay( VSD_SE_RESULT_FADE );
	wk->wait = RESULT_END_WAIT;
	return VSD_FUNC_NEXT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：確認画面の初期移動処理
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_PokeCheckMove( VSD_WORK * wk )
{
	if( wk->cnt == 0 ){
		Snd_SePlay( VSD_SE_MULTI_POKE_IN );
	}

	if( wk->cnt == 16 ){
		wk->cnt  = 0;
		wk->wait = POKECHECK_END_WAIT;
		return VSD_FUNC_NEXT;
	}
	wk->cnt++;

	VSD_PokeCheckObjMove( wk, MULTI_SCROLL_INIT-wk->cnt );
	VSD_PokeCheckBgMove( wk, wk->cnt );

	return VSD_FUNC_LOOP;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：終了セット
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqEndSet( VSD_WORK * wk )
{
	APP_WipeStart( APP_WIPE_OUT, wk->dat->heap );
	wk->seq = SEQ_VSD_END;
	return VSD_FUNC_NEXT;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン処理：終了処理
 *
 * @param	wk		ワーク
 *
 * @return	処理コマンド
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_SeqEnd( TCB_PTR tcb, VSD_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == FALSE ){ return FALSE; }

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット

	if( wk->dat->mode != VSD_MODE_MULTI ){
		VSD_3DBgExit( wk );
		VSD_VsParticleDelete( wk );
		VSD_VsFontOamDelete( wk );
	}else{
		VSD_PokeCheckBgExit( wk );
		VSD_PokeCheckBmpExit( wk );
	}

	VSD_ObjFree( wk );
	DellVramTransferManager();

	PaletteFadeWorkAllocFree( wk->pfd, FADE_MAIN_BG );
	PaletteFadeFree( wk->pfd );

	wk->dat->end_flg = 1;
	PMDS_taskDel( tcb );

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 立ち位置取得
 *
 * @param	none
 *
 * @retval	"TRUE = 左"
 * @retval	"FALSE = 右"
 */
//--------------------------------------------------------------------------------------------
static BOOL VSD_GetStandID(void)
{
	switch( CommGetStandNo(CommGetCurrentID()) ){
	case 0:
	case 2:
		return TRUE;
	case 1:
	case 3:
		return FALSE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * リソースマネージャー初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_ClactResManInit( VSD_WORK * wk, TCATS_RESOURCE_NUM_LIST * crnl, int max )
{
	initVramTransferManagerHeap( 64, wk->dat->heap );

	wk->csp = CATS_AllocMemory( wk->dat->heap );
	wk->crp = CATS_ResourceCreate( wk->csp );
	{
		TCATS_OAM_INIT	coi = {
			0, 128,
			0, 32,
			0, 128,
			0, 32,
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			0,
			1024*64,
			1024*16,
			GX_OBJVRAMMODE_CHAR_1D_32K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		ccmm.num = max;
		CATS_SystemInit( wk->csp, &coi, &ccmm, 16 );
	}
	CATS_ClactSetInit( wk->csp, wk->crp, max );
	CATS_ResourceManagerInit( wk->csp, wk->crp, crnl );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加（個別）
 *
 * @param	wk		ワーク
 * @param	id		追加するセルアクターのID
 * @param	pri		BGとのプライオリティ
 *
 * @return	セルアクターデータ
 */
//--------------------------------------------------------------------------------------------
static CATS_ACT_PTR VSD_ClactAdd( VSD_WORK * wk, const u32 * id )
{
	TCATS_OBJECT_ADD_PARAM_S	prm;

	prm.x = 0;
	prm.y = 0;
	prm.z = 0;

	prm.anm = 0;
	prm.pri = id[5];
	prm.pal = id[6];
	prm.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;

	prm.id[0] = id[0];
	prm.id[1] = id[1];
	prm.id[2] = id[2];
	prm.id[3] = id[3];
	
	prm.bg_pri = id[4];
	prm.vram_trans = 0;

	return CATS_ObjectAdd_S( wk->csp, wk->crp, &prm );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター解放
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_ObjFree( VSD_WORK * wk )
{
	u32	i;

	for( i=0; i<wk->cap_max; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	CATS_ResourceDestructor_S( wk->csp, wk->crp );
	CATS_FreeMemory( wk->csp );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクターアニメ
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_ObjAnm( VSD_WORK * wk )
{
	u16	i;

	for( i=0; i<wk->cap_max; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}


//============================================================================================
//	VS画面/勝敗画面
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	work	ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsVBlank( void * work )
{
	VSD_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );
	PaletteFadeTrans( wk->pfd );

	// セルアクター
	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//--------------------------------------------------------------------------------------------
/**
 * BG初期化
 *
 * @param	wk	ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_3DBgInit( VSD_WORK * wk )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME3_M );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, SCROLL_INIT );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME2_M );
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, -SCROLL_INIT );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME1_M );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}


}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	wk	ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_3DBgExit( VSD_WORK * wk )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M );

	sys_FreeMemoryEz( wk->bgl );
}

//--------------------------------------------------------------------------------------------
/**
 * BGグラフィックセット
 *
 * @param	wk	ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsBgGraphicSet( VSD_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_VS_DEMO_GRA, NARC_vs_demo_gra_t_buttle_ncgr,
		wk->bgl, GF_BGL_FRAME1_M, 0, 0, 0, wk->dat->heap );
	ArcUtil_ScrnSet(
		ARC_VS_DEMO_GRA, NARC_vs_demo_gra_t_buttle03_nscr,
		wk->bgl, GF_BGL_FRAME1_M, 0, 0, 0, wk->dat->heap );
	ArcUtil_ScrnSet(
		ARC_VS_DEMO_GRA, NARC_vs_demo_gra_t_buttle01_nscr,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, wk->dat->heap );
	ArcUtil_ScrnSet(
		ARC_VS_DEMO_GRA, NARC_vs_demo_gra_t_buttle02_nscr,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, wk->dat->heap );

	ArcUtil_PalSet(
		ARC_VS_DEMO_GRA, NARC_vs_demo_gra_t_buttle_nclr, PALTYPE_MAIN_BG, 0, 0, wk->dat->heap );
	PaletteWorkSet_VramCopy( wk->pfd, FADE_MAIN_BG, 0, 0x20*3 );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME1_M, 0x18c6 );
}

//--------------------------------------------------------------------------------------------
/**
 * 半透明設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsAlphaSet(void)
{
	G2_SetBlendAlpha(
		GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1,
		GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ, 23, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * VS画面：OBJ追加
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsObjMake( VSD_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		VS_CHR_ID_MAX, VS_PAL_ID_MAX, VS_CEL_ID_MAX, VS_ANM_ID_MAX, 0, 0
	};
	u32	i;

	VSD_ClactResManInit( wk, &crnl, VS_CLA_MAX+8+1 );

	VSD_VsBallObjMake( wk );

	for( i=0; i<VS_CLA_MAX; i++ ){
		wk->cap[i] = VSD_ClactAdd( wk, &VS_ClactParam[i][0] );
	}
	VSD_VsBallObjMove( wk, 0, -SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 1, -SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 2, SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 3, SCROLL_INIT, 0 );
	VSD_VsBallAnmChg( wk );

	wk->cap_max = VS_CLA_MAX;

	VSD_VsFontOamMake( wk );
	VSD_VsFontOamMove( wk, 0, -SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 1, -SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 2, SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 3, SCROLL_INIT, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ボールOBJリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsBallObjMake( VSD_WORK * wk )
{
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BATT_OBJ,
		BATTLE_STOCK_M_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_BALL );
/*
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_BATT_OBJ, BATTLE_WOBJ_NCLR,
		0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_BALL );
*/
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_VS_DEMO_GRA,
		NARC_vs_demo_gra_t_buttle_font_nclr, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_BALL );
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BATT_OBJ, BATTLE_STOCK_M_NCER_BIN, 1, VS_CEL_ID_BALL );
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BATT_OBJ, BATTLE_STOCK_M_NANR_BIN, 1, VS_ANM_ID_BALL );
}

//--------------------------------------------------------------------------------------------
/**
 * ボールOBJ移動
 *
 * @param	wk		ワーク
 * @param	flg		0=自分側前半, 1=自分側後半, 2=敵側前半, 3=敵側後半
 * @param	px		X移動値
 * @param	py		Y移動値
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsBallObjMove( VSD_WORK * wk, u8 flg, s16 px, s16 py )
{
	u32	i;
	u8	start[] = { VS_CLA_BALL01, VS_CLA_BALL04, VS_CLA_BALL11, VS_CLA_BALL14 };

	for( i=0; i<3; i++ ){
		CATS_ObjectPosSetCap(
			wk->cap[ start[flg]+i ],
			wk->ball_gx[flg] + i*VS_CLA_BALL_SX + px, wk->ball_gy[flg] + py );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ボールアニメ切り替え
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsPartyBallAnmChg( VSD_WORK * wk, POKEPARTY * party, u16 max, u16 cla_id )
{
	POKEMON_PARAM * pp;
	u8	i;
	u8	prm, pp_cnt, add_cnt;

	pp_cnt  = (u8)PokeParty_GetPokeCount( party );
	add_cnt = 0;

	for( i=0; i<max; i++ ){
		CATS_ObjectAnimeSeqSetCap( wk->cap[i+cla_id], STOCK_ANMSEQ_NONE );
		if( pp_cnt > i ){
			pp = PokeParty_GetMemberPointer( party, i );

			if( PokeParaGet( pp, ID_PARA_monsno, NULL ) == 0 ||
				PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){
				continue;
			}

			prm = BadStatusIconAnmGet( pp );

			if( prm == ST_ICON_HINSI ){
				CATS_ObjectAnimeSeqSetCap( wk->cap[add_cnt+cla_id], STOCK_ANMSEQ_DEAD );
			}else if( prm != ST_ICON_NONE ){
				CATS_ObjectAnimeSeqSetCap( wk->cap[add_cnt+cla_id], STOCK_ANMSEQ_NG );
			}else{
				CATS_ObjectAnimeSeqSetCap( wk->cap[add_cnt+cla_id], STOCK_ANMSEQ_ALIVE );
			}

			add_cnt++;
		}
	}
}

static void VSD_VsBallAnmChg( VSD_WORK * wk )
{
	if( wk->dat->type == VSD_TYPE_NORMAL ){
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_LEFT1], 6, VS_CLA_BALL01 );
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_RIGHT1], 6, VS_CLA_BALL11 );
	}else{
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_LEFT1], 3, VS_CLA_BALL01 );
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_LEFT2], 3, VS_CLA_BALL04 );
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_RIGHT1], 3, VS_CLA_BALL11 );
		VSD_VsPartyBallAnmChg( wk, wk->dat->pp[VSD_PARTY_RIGHT2], 3, VS_CLA_BALL14 );
	}
}



//--------------------------------------------------------------------------------------------
/**
 * フォントOAM作成（個別）
 *
 * @param	wk		ワーク
 * @param	id		作成ID
 * @param	str		文字列
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsFontOamMakeMain( VSD_WORK * wk, u32 id, STRBUF * str )
{
	GF_BGL_BMPWIN * win;
	FONTOAM_INIT	init;

	win = &wk->win[0];

	GF_BGL_BmpWinObjAdd( wk->bgl, win, VSD_BMP_PNAME_SX, VSD_BMP_PNAME_SY, 0, 0 );

	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(3,4,0), NULL );

	init.fontoam_sys = wk->fsp;
	init.bmp         = win;
	init.clact_set   = CATS_GetClactSetPtr( wk->crp );
	init.pltt        = CATS_PlttProxy( wk->crp, VS_PAL_ID_BALL );
	init.parent      = NULL;
	init.char_ofs    = (VSD_BMP_PNAME1_CGX-VSD_BMP_PNAME_SIZ*id)*0x20;
	init.x           = 0;
	init.y           = 0;
	init.bg_pri      = 2;
	init.soft_pri    = 0;
	init.draw_area   = NNS_G2D_VRAM_TYPE_2DMAIN;
	init.heap        = wk->dat->heap;
	
	wk->fop[id] = FONTOAM_Init( &init );
	FONTOAM_SetPaletteNo( wk->fop[id], 0 );
	
	GF_BGL_BmpWinDel( win );	// 解放処理
}

//--------------------------------------------------------------------------------------------
/**
 * フォントOAM作成
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsFontOamMake( VSD_WORK * wk )
{
	wk->fsp = FONTOAM_SysInit( 8, wk->dat->heap );

	VSD_VsFontOamMakeMain( wk, 0, wk->dat->name[VSD_PARTY_LEFT1] );
	VSD_VsFontOamMakeMain( wk, 2, wk->dat->name[VSD_PARTY_RIGHT1] );

	if( wk->dat->type == VSD_TYPE_MULTI ){
		VSD_VsFontOamMakeMain( wk, 1, wk->dat->name[VSD_PARTY_LEFT2] );
		VSD_VsFontOamMakeMain( wk, 3, wk->dat->name[VSD_PARTY_RIGHT2] );
	}else{
		VSD_VsFontOamMakeMain( wk, 1, wk->dat->name[VSD_PARTY_LEFT1] );		// ダミー
		VSD_VsFontOamMakeMain( wk, 3, wk->dat->name[VSD_PARTY_RIGHT1] );	// ダミー
		FONTOAM_SetDrawFlag( wk->fop[1], FALSE );
		FONTOAM_SetDrawFlag( wk->fop[3], FALSE );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * フォントOAM移動
 *
 * @param	wk		ワーク
 * @param	id		0=自分側前半, 1=自分側後半, 2=敵側前半, 3=敵側後半
 * @param	px		X移動値
 * @param	py		Y移動値
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsFontOamMove( VSD_WORK * wk, u32 id, s16 x, s16 y )
{
	FONTOAM_SetMat( wk->fop[id], wk->name_gx[id]+x, wk->name_gy[id]+y );
}

//--------------------------------------------------------------------------------------------
/**
 * フォントOAM削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsFontOamDelete( VSD_WORK * wk )
{
	u32	i;

	if( wk->dat->mode == VSD_MODE_MULTI ){ return; }

	for( i=0; i<4; i++ ){
		FONTOAM_Delete( wk->fop[i] );
	}
	FONTOAM_SysDelete( wk->fsp );
}

//--------------------------------------------------------------------------------------------
/**
 * OBJを初期位置へ移動
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsObjGlobalPosSet( VSD_WORK * wk )
{
	if( wk->dat->type == VSD_TYPE_MULTI ){
		wk->ball_gx[0] = VS_CLA_BALL00M_PX;
		wk->ball_gy[0] = VS_CLA_BALL00M_PY;
		wk->ball_gx[1] = VS_CLA_BALL03M_PX;
		wk->ball_gy[1] = VS_CLA_BALL03M_PY;
		wk->ball_gx[2] = VS_CLA_BALL10M_PX;
		wk->ball_gy[2] = VS_CLA_BALL10M_PY;
		wk->ball_gx[3] = VS_CLA_BALL13M_PX;
		wk->ball_gy[3] = VS_CLA_BALL13M_PY;

		wk->name_gx[0] = VS_FOAM_NAME00M_PX;
		wk->name_gy[0] = VS_FOAM_NAME00M_PY;
		wk->name_gx[1] = VS_FOAM_NAME03M_PX;
		wk->name_gy[1] = VS_FOAM_NAME03M_PY;
		wk->name_gx[2] = VS_FOAM_NAME10M_PX;
		wk->name_gy[2] = VS_FOAM_NAME10M_PY;
		wk->name_gx[3] = VS_FOAM_NAME13M_PX;
		wk->name_gy[3] = VS_FOAM_NAME13M_PY;
	}else{
		wk->ball_gx[0] = VS_CLA_BALL00_PX;
		wk->ball_gy[0] = VS_CLA_BALL00_PY;
		wk->ball_gx[1] = VS_CLA_BALL03_PX;
		wk->ball_gy[1] = VS_CLA_BALL03_PY;
		wk->ball_gx[2] = VS_CLA_BALL10_PX;
		wk->ball_gy[2] = VS_CLA_BALL10_PY;
		wk->ball_gx[3] = VS_CLA_BALL13_PX;
		wk->ball_gy[3] = VS_CLA_BALL13_PY;

		wk->name_gx[0] = VS_FOAM_NAME00_PX;
		wk->name_gy[0] = VS_FOAM_NAME00_PY;
		wk->name_gx[2] = VS_FOAM_NAME10_PX;
		wk->name_gy[2] = VS_FOAM_NAME10_PY;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 勝敗画面：OBJ追加
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsEndObjMake( VSD_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		VS_CHR_ID_MAX, VS_PAL_ID_MAX, VS_CEL_ID_MAX, VS_ANM_ID_MAX, 0, 0
	};
	u32	i;

	VSD_ClactResManInit( wk, &crnl, VS_CLA_END_MAX+8+1 );

	VSD_VsBallObjMake( wk );
	VSD_VsResultObjMake( wk );

	for( i=0; i<VS_CLA_END_MAX; i++ ){
		wk->cap[i] = VSD_ClactAdd( wk, &VS_ClactParam[i][0] );
	}

	VSD_VsBallObjMove( wk, 0, -SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 1, -SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 2, SCROLL_INIT, 0 );
	VSD_VsBallObjMove( wk, 3, SCROLL_INIT, 0 );
	VSD_VsBallAnmChg( wk );

	VSD_VsResultMove( wk );

	VSD_VsFontOamMake( wk );
	VSD_VsFontOamMove( wk, 0, -SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 1, -SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 2, SCROLL_INIT, 0 );
	VSD_VsFontOamMove( wk, 3, SCROLL_INIT, 0 );

	wk->cap_max = VS_CLA_END_MAX;

}

//--------------------------------------------------------------------------------------------
/**
 * 勝敗OBJリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsResultObjMake( VSD_WORK * wk )
{
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_VS_DEMO_GRA,
		NARC_vs_demo_gra_t_buttle_font_ncgr, 0, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_RESULT );
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_VS_DEMO_GRA,
		NARC_vs_demo_gra_t_battle_font_ncer, 0, VS_CEL_ID_RESULT );
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_VS_DEMO_GRA,
		NARC_vs_demo_gra_t_battle_font_nanr, 0, VS_ANM_ID_RESULT );
}

//--------------------------------------------------------------------------------------------
/**
 * 勝敗OBJ表示位置セット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsResultMove( VSD_WORK * wk )
{
	CATS_ObjectEnableCap( wk->cap[VS_CLA_RESULT1], 0 );
	CATS_ObjectEnableCap( wk->cap[VS_CLA_RESULT2], 0 );

	if( wk->dat->result == VSD_RESULT_DRAW ){
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_DRAW_PX, RESULT_OBJ_PY );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], VSD_RESULT_DRAW-1 );
		return;
	}

	if( VSD_GetStandID() == TRUE ){
		if( wk->dat->result == VSD_RESULT_WIN ){
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX1, RESULT_OBJ_PY );
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX2, RESULT_OBJ_PY );
		}else{
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX2, RESULT_OBJ_PY );
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX1, RESULT_OBJ_PY );
		}
	}else{
		if( wk->dat->result == VSD_RESULT_WIN ){
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX2, RESULT_OBJ_PY );
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX1, RESULT_OBJ_PY );
		}else{
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX1, RESULT_OBJ_PY );
			CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX2, RESULT_OBJ_PY );
		}
	}
	CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], VSD_RESULT_WIN-1 );
	CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT2], VSD_RESULT_LOSE-1 );


/*
	switch( wk->dat->result ){
	case VSD_RESULT_WIN:
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX1, RESULT_OBJ_PY );
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX2, RESULT_OBJ_PY );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], VSD_RESULT_WIN-1 );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT2], VSD_RESULT_LOSE-1 );
		break;
	case VSD_RESULT_LOSE:
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_OBJ_PX2, RESULT_OBJ_PY );
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT2], RESULT_OBJ_PX1, RESULT_OBJ_PY );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], VSD_RESULT_WIN-1 );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT2], VSD_RESULT_LOSE-1 );
		break;
	default:
		CATS_ObjectPosSetCap( wk->cap[VS_CLA_RESULT1], RESULT_DRAW_PX, RESULT_OBJ_PY );
		CATS_ObjectAnimeSeqSetCap( wk->cap[VS_CLA_RESULT1], VSD_RESULT_DRAW-1 );
	}
*/
}


//============================================================================================
//	パーティクル
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * パーティクル初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsParticleInit( VSD_WORK * wk )
{
	GF_CAMERA_PTR	camera;
	void * res;

	wk->g3dm = GF_G3DMAN_Init(
					wk->dat->heap,
					GF_G3DMAN_LNK, GF_G3DTEX_512K, GF_G3DMAN_LNK, GF_G3DPLT_32K, NULL );

	G3X_AlphaBlend( TRUE );

	// パーティクルシステム初期化
	Particle_SystemWorkInit();

	// パーティクルシステム作成
	wk->ptm = sys_AllocMemory( wk->dat->heap, PARTICLE_LIB_HEAP_SIZE );
	wk->ptc = Particle_SystemCreate(
				sAllocTex, sAllocTexPalette, wk->ptm, PARTICLE_LIB_HEAP_SIZE, TRUE, wk->dat->heap );
	camera  = Particle_GetCameraPtr( wk->ptc );
	GFC_SetCameraClip( BP_NEAR, BP_FAR, camera );

	// リソース読み込み＆登録
	res = Particle_ArcResourceLoad(
			ARC_PARTICLE_DATA, NARC_particledata_vs_battle_spa, wk->dat->heap );
	Particle_ResourceSet( wk->ptc, res, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE );

	// パーティクル生成
	Particle_CreateEmitterCallback( wk->ptc, VS_BATTLE_T_BUTTLE01, NULL, NULL );
	Particle_CreateEmitterCallback( wk->ptc, VS_BATTLE_T_BUTTLE01A, NULL, NULL );
	Particle_CreateEmitterCallback( wk->ptc, VS_BATTLE_T_BUTTLE01B, NULL, NULL );
	Particle_CreateEmitterCallback( wk->ptc, VS_BATTLE_T_BUTTLE02, NULL, NULL );
	Particle_CreateEmitterCallback( wk->ptc, VS_BATTLE_T_BUTTLE03, NULL, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * パーティクル描画
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static int VSD_VsParticleMain( VSD_WORK * wk )
{
	const MtxFx43 * camera;
	int	draw_num;

	if( wk->dat->mode != VSD_MODE_IN ){ return FALSE; }

	GF_G3X_Reset();

	if( Particle_GetEmitterNum( wk->ptc ) == 0 ){ return FALSE; }

	Particle_DrawAll();		// パーティクル描画
	Particle_CalcAll();		// パーティクル計算

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * パーティクル削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_VsParticleDelete( VSD_WORK * wk )
{
	if( wk->dat->mode != VSD_MODE_IN ){ return; }

	Particle_SystemExit( wk->ptc );
	sys_FreeMemoryEz( wk->ptm );

	GF_G3D_Exit( wk->g3dm );
}

//--------------------------------------------------------------------------------------------
/**
 * テクスチャVRAMアドレスを返すためのコールバック関数
 *
 * @param   size		テクスチャサイズ
 * @param   is4x4comp	4x4圧縮テクスチャであるかどうかのフラグ(TRUE=圧縮テクスチャ)
 *
 * @return  読み込みを開始するVRAMのアドレス
 */
//--------------------------------------------------------------------------------------------
static u32 sAllocTex( u32 size, BOOL is4x4comp )
{
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	Particle_LnkTexKeySet(key);		//リンクドリストを使用しているのでキー情報をセット
	GF_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}

//--------------------------------------------------------------------------------------------
/**
 * テクスチャパレットVRAMアドレスを返すためのコールバック関数
 *
 * @param	size		テクスチャサイズ
 * @param	is4pltt		4色パレットであるかどうかのフラグ
 *
 * @retval	読み込みを開始するVRAMのアドレス
 *
 * direct形式のテクスチャの場合、SPL_LoadTexPlttByCallbackFunctionは
 * コールバック関数を呼び出しません。
 */
//--------------------------------------------------------------------------------------------
static u32 sAllocTexPalette( u32 size, BOOL is4pltt )
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, NNS_GFD_ALLOC_FROM_LOW);
	Particle_PlttLnkTexKeySet(key);	//リンクドリストを使用しているのでキー情報をセット
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "パーティクルでパレットの確保が出来ません！\n");
	}
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}


//============================================================================================
//	ポケモン確認画面
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BG初期化
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgInit( VSD_WORK * wk )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME1_M );
	}

	{	// PLATE (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, GF_BGL_FRAME2_M );
	}

	{	// BG (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BG削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgExit( VSD_WORK * wk )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3|GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M );

	sys_FreeMemoryEz( wk->bgl );
}

//--------------------------------------------------------------------------------------------
/**
 * BGグラフィックセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgGraphicSet( VSD_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_PLIST_GRA, NARC_plist_gra_p_list_NCGR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, wk->dat->heap );
	ArcUtil_ScrnSet(
		ARC_PLIST_GRA, NARC_plist_gra_p_list_NSCR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, wk->dat->heap );

	{
		NNSG2dPaletteData * pal;
		void * buf;
		u16 * cpy;
		
		buf = ArchiveDataLoadMalloc( ARC_PLIST_GRA, NARC_plist_gra_p_list_NCLR, wk->dat->heap );
		NNS_G2dGetUnpackedPaletteData( buf, &pal );
		GF_BGL_PaletteSet( GF_BGL_FRAME3_M, (void *)pal->pRawData, pal->szByte, 0 );
		cpy = (u16 *)pal->pRawData;
		memcpy( wk->pal, &cpy[PAL_PANEL_0*16], 32*3 );
		sys_FreeMemoryEz( buf );
	}

	PoleList_PokePlateScreenGet(
		wk->dat->heap, wk->plate_top, wk->plate_normal, wk->plate_none );
}

//--------------------------------------------------------------------------------------------
/**
 * BGプレートセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgPut( VSD_WORK * wk )
{
	u16 * plate;
	u32	i;

	for( i=0; i<6; i++ ){
		if( i == 0 || i == 3 ){
			plate = wk->plate_top;
		}else if( wk->poke[i].mons == 0 ){
			plate = wk->plate_none;
		}else{
			plate = wk->plate_normal;
		}
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME2_M, PokeCheckBgPos[i][0], PokeCheckBgPos[i][1],
			PL_PANEL_SX, PL_PANEL_SY, (const void *)plate, 0, 0, PL_PANEL_SX, PL_PANEL_SY );

		if( wk->poke[i].mons != 0 ){
			GF_BGL_ScrPalChange(
				wk->bgl, GF_BGL_FRAME2_M, PokeCheckBgPos[i][0],
				PokeCheckBgPos[i][1], PL_PANEL_SX, PL_PANEL_SY, PAL_PANEL_0+i );

			if( ( i < 3 && wk->dat->type == VSD_TYPE_RIGHT ) ||
				( i >= 3 && wk->dat->type == VSD_TYPE_LEFT ) ){
				GF_BGL_PaletteSet(
					GF_BGL_FRAME2_M, (void *)&wk->pal[16*1], 16*2, (PAL_PANEL_0+i)*16*2 );
			}else{
				GF_BGL_PaletteSet(
					GF_BGL_FRAME2_M, (void *)&wk->pal[0], 16*2, (PAL_PANEL_0+i)*16*2 );
			}
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}

//--------------------------------------------------------------------------------------------
/**
 * インしてくるBGプレートをコピー（メイン）
 *
 * @param	wk		ワーク
 * @param	cpy		コピー先
 * @param	frm		コピー元のBGフレーム
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgCopyMain( VSD_WORK * wk, u16 * cpy, u8 frm )
{
	u16 * buf;
	u16	px, i;

	buf = GF_BGL_ScreenAdrsGet( wk->bgl, frm );
	if( wk->dat->type == VSD_TYPE_LEFT ){
		px = 16;
	}else{
		px = 0;
	}
	for( i=0; i<24; i++ ){
		memcpy( &cpy[i*16], &buf[i*32+px], PL_PANEL_SX*2 );
		memset( &buf[i*32+px], 0, PL_PANEL_SX*2 );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * インしてくるBGプレートをコピー
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgCopy( VSD_WORK * wk )
{
	VSD_PokeCheckBgCopyMain( wk, &wk->plate_bg[0][0], GF_BGL_FRAME1_M );
	VSD_PokeCheckBgCopyMain( wk, &wk->plate_bg[1][0], GF_BGL_FRAME2_M );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}

//--------------------------------------------------------------------------------------------
/**
 * BGプレート移動
 *
 * @param	wk		ワーク
 * @param	cnt		移動カウント
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBgMove( VSD_WORK * wk, u8 cnt )
{
	if( wk->dat->type == VSD_TYPE_LEFT ){
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME1_M, 16+16-cnt, 0, cnt, 24,
			(const void *)&wk->plate_bg[0][0], 0, 0, 16, 24 );
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME2_M, 16+16-cnt, 0, cnt, 24,
			(const void *)&wk->plate_bg[1][0], 0, 0, 16, 24 );
	}else{
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME1_M, 0, 0, cnt, 24,
			(const void *)&wk->plate_bg[0][0], 16-cnt, 0, 16, 24 );
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME2_M, 0, 0, cnt, 24,
			(const void *)&wk->plate_bg[1][0], 16-cnt, 0, 16, 24 );
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンパラメータ取得
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void VSD_PokeParamGet( VSD_WORK * wk )
{
	POKEMON_PARAM * pp;
	u16	i;
	u16	pp_cnt;

	pp_cnt = (u16)PokeParty_GetPokeCount( wk->dat->pp[0] );

	memset( wk->poke, 0, sizeof(VSD_POKE)*6 );

	for( i=0; i<6; i++ ){
		if( pp_cnt <= i ){ break; }

		pp = PokeParty_GetMemberPointer( wk->dat->pp[0], i );

		wk->poke[i].chr_arc = PokeIconCgxArcIndexGetByPP( pp );

		wk->poke[i].mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
		if( wk->poke[i].mons == 0 ){ continue; }

		wk->poke[i].egg  = (u16)PokeParaGet( pp, ID_PARA_tamago_flag, NULL );
		wk->poke[i].hp   = (u16)PokeParaGet( pp, ID_PARA_hp, NULL );
		wk->poke[i].mhp  = (u16)PokeParaGet( pp, ID_PARA_hpmax, NULL );
		wk->poke[i].lv   = (u16)PokeParaGet( pp, ID_PARA_level, NULL );
		wk->poke[i].item = (u16)PokeParaGet( pp, ID_PARA_item, NULL );
		if( PokeParaGet( pp, ID_PARA_nidoran_nickname, NULL ) == TRUE ){
			wk->poke[i].sex_put = 0;
		}else{
			wk->poke[i].sex_put = 1;
		}
		wk->poke[i].sex = PokeSexGet( pp );
		wk->poke[i].st  = (u8)BadStatusIconAnmGet( pp );
	}
}
*/

static void VSD_PokePartyParamGet( VSD_WORK * wk, POKEPARTY * party, u8 start )
{
	POKEMON_PARAM * pp;
	u16	i;
	u16	pp_cnt;

	pp_cnt = (u16)PokeParty_GetPokeCount( party );

//	memset( wk->poke, 0, sizeof(VSD_POKE)*6 );

	for( i=0; i<3; i++ ){
		if( pp_cnt <= i ){
			wk->poke[i+start].chr_arc = PokeIconCgxArcIndexGetByMonsNumber( 0, 0, 0 );
			continue;
		}

		pp = PokeParty_GetMemberPointer( party, i );

		wk->poke[i+start].chr_arc = PokeIconCgxArcIndexGetByPP( pp );

		wk->poke[i+start].mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
		if( wk->poke[i+start].mons == 0 ){ continue; }

		wk->poke[i+start].egg  = (u16)PokeParaGet( pp, ID_PARA_tamago_flag, NULL );
		wk->poke[i+start].hp   = (u16)PokeParaGet( pp, ID_PARA_hp, NULL );
		wk->poke[i+start].mhp  = (u16)PokeParaGet( pp, ID_PARA_hpmax, NULL );
		wk->poke[i+start].lv   = (u16)PokeParaGet( pp, ID_PARA_level, NULL );
		wk->poke[i+start].item = (u16)PokeParaGet( pp, ID_PARA_item, NULL );
		wk->poke[i+start].cb   = (u8)PokeParaGet( pp, ID_PARA_cb_id, NULL );
		wk->poke[i+start].form = (u8)PokeParaGet( pp, ID_PARA_form_no, NULL );
		if( PokeParaGet( pp, ID_PARA_nidoran_nickname, NULL ) == TRUE ){
			wk->poke[i+start].sex_put = 0;
		}else{
			wk->poke[i+start].sex_put = 1;
		}
		wk->poke[i+start].sex = PokeSexGet( pp );
		wk->poke[i+start].st  = (u8)BadStatusIconAnmGet( pp );
	}
}

static void VSD_PokeParamGet( VSD_WORK * wk )
{
	memset( wk->poke, 0, sizeof(VSD_POKE)*6 );
	VSD_PokePartyParamGet( wk, wk->dat->pp[VSD_PARTY_LEFT1], 0 );
	VSD_PokePartyParamGet( wk, wk->dat->pp[VSD_PARTY_LEFT2], 3 );
}


//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンアニメ取得
 *
 * @param	wk		ワーク
 * @param	pos		位置
 *
 * @return	アニメ番号
 */
//--------------------------------------------------------------------------------------------
static u8 VSD_PokeIconAnmGet( VSD_WORK * wk, u32 pos )
{
	if( wk->poke[pos].hp == 0 ){
		return POKEICON_ANM_DEATH;
	}

	if( wk->poke[pos].st != ST_ICON_NONE && wk->poke[pos].st != ST_ICON_POKERUS ){
		return POKEICON_ANM_STCHG;
	}

	switch( GetHPGaugeDottoColor(wk->poke[pos].hp,wk->poke[pos].mhp,HPGAUGE_DOTTO_MAX) ){
	case HP_DOTTO_MAX:
		return POKEICON_ANM_HPMAX;
	case HP_DOTTO_GREEN:	// 緑
		return POKEICON_ANM_HPGREEN;
	case HP_DOTTO_YELLOW:	// 黄
		return POKEICON_ANM_HPYERROW;
	case HP_DOTTO_RED:		// 赤
		return POKEICON_ANM_HPRED;
	}

	return POKEICON_ANM_DEATH;
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加
 *
 * @param	wk		ワーク
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeClactAdd( VSD_WORK * wk, u32 pos )
{
	u32	i;

	for( i=0; i<5; i++ ){
		wk->cap[pos*5+i] = VSD_ClactAdd( wk, &PokeCheck_ClactParam[pos*5+i][0] );
		CATS_ObjectPosSetCap(
			wk->cap[pos*5+i], PokeCheckObjPosTable[pos][i*2], PokeCheckObjPosTable[pos][i*2+1] );
	}
	if( wk->poke[pos].mons == 0 ){
		for( i=0; i<5; i++ ){
			CATS_ObjectEnableCap( wk->cap[pos*5+i], 0 );
		}
	}else{
		// ポケアイコン
		CATS_ObjectPaletteSetCap(
			wk->cap[pos*5+0],
			PokeIconPalNumGet(wk->poke[pos].mons,wk->poke[pos].form,wk->poke[pos].egg) );
		CATS_ObjectAnimeSeqSetCap(
			wk->cap[pos*5+0], VSD_PokeIconAnmGet( wk, pos ) );

		// アイテムアイコン
		if( wk->poke[pos].item == 0 ){
			CATS_ObjectEnableCap( wk->cap[pos*5+1], 0 );
		}else if( ItemMailCheck( wk->poke[pos].item ) == TRUE ){
			CATS_ObjectAnimeSeqSetCap( wk->cap[pos*5+1], 1 );
		}else{
			CATS_ObjectAnimeSeqSetCap( wk->cap[pos*5+1], 0 );
		}
		// カスタムボール
		if( wk->poke[pos].cb == 0 ){
			CATS_ObjectEnableCap( wk->cap[pos*5+2], 0 );
		}else{
			CATS_ObjectAnimeSeqSetCap( wk->cap[pos*5+2], 2 );
		}
		// 状態異常アイコン
		if( wk->poke[pos].st == ST_ICON_NONE ){
			CATS_ObjectEnableCap( wk->cap[pos*5+3], 0 );
		}else{
			CATS_ObjectAnimeSeqSetCap( wk->cap[pos*5+3], wk->poke[i].st );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckObjMake( VSD_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		VS_CHR_ID_MV_MAX, VS_PAL_ID_MV_MAX, VS_CEL_ID_MV_MAX, VS_ANM_ID_MV_MAX, 0, 0
	};
	u32	i;

	VSD_ClactResManInit( wk, &crnl, VS_CLA_PLMAX+1 );

	VSD_PokeCheckPokeIconMake( wk );
	VSD_PokeCheckItemIconMake( wk );
	VSD_PokeCheckStIconMake( wk );
	VSD_PokeCheckBallMake( wk );

	for( i=0; i<6; i++ ){
		VSD_PokeClactAdd( wk, i );
	}

	VSD_PokeCheckObjMove( wk, MULTI_SCROLL_INIT );

	wk->cap_max = VS_CLA_PLMAX;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンアイコンのリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckPokeIconMake( VSD_WORK * wk )
{
	u32	i;

	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_POKEICON,
		PokeIconPalArcIndexGet(), 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_POKE );

	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_POKEICON, PokeIconAnmCellArcIndexGet(), 0, VS_CEL_ID_POKE );

	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_POKEICON, PokeIconAnmCellAnmArcIndexGet(), 0, VS_ANM_ID_POKE );

	for( i=0; i<6; i++ ){
		CATS_LoadResourceCharArc(
			wk->csp, wk->crp, ARC_POKEICON,
			wk->poke[i].chr_arc, 0, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_POKE1+i );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムアイコンのリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckItemIconMake( VSD_WORK * wk )
{
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_PLIST_GRA,
		NARC_plist_gra_item_icon_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_ITEM );

	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_PLIST_GRA,
		NARC_plist_gra_item_icon_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_ITEM );

	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_PLIST_GRA, NARC_plist_gra_item_icon_NCER, 0, VS_CEL_ID_ITEM );

	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_PLIST_GRA, NARC_plist_gra_item_icon_NANR, 0, VS_ANM_ID_ITEM );
}

//--------------------------------------------------------------------------------------------
/**
 * 状態異常アイコンのリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckStIconMake( VSD_WORK * wk )
{
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA,
		NARC_pst_gra_p_st_ijou_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_ST );

	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA,
		NARC_pst_gra_p_st_ijou_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_ST );

	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA, NARC_pst_gra_p_st_ijou_NCER, 0, VS_CEL_ID_ST );

	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_PSTATUS_GRA, NARC_pst_gra_p_st_ijou_NANR, 0, VS_ANM_ID_ST );
}

//--------------------------------------------------------------------------------------------
/**
 * ボールのリソース設定
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBallMake( VSD_WORK * wk )
{
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_PLIST_GRA,
		NARC_plist_gra_list_ball_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, VS_CHR_ID_PLBALL );

	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_PLIST_GRA,
		NARC_plist_gra_list_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, VS_PAL_ID_PLBALL );

	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_PLIST_GRA, NARC_plist_gra_list_ball_NCER, 0, VS_CEL_ID_PLBALL );

	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_PLIST_GRA, NARC_plist_gra_list_ball_NANR, 0, VS_ANM_ID_PLBALL );
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの移動
 *
 * @param	wk		ワーク
 * @param	mv		移動カウント
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckObjMove( VSD_WORK * wk, s16 mv )
{
	s32	i, j, start;

	if( wk->dat->type == VSD_TYPE_LEFT ){
		start = 3;
		mv *= 8;
	}else{
		start = 0;
		mv *= -8;
	}

	for( i=0; i<3; i++ ){
		for( j=0; j<5; j++ ){
			CATS_ObjectPosSetCap(
				wk->cap[(start+i)*5+j],
				PokeCheckObjPosTable[start+i][j*2]+mv,
				PokeCheckObjPosTable[start+i][j*2+1] );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMPセット
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBmpAdd( VSD_WORK * wk )
{
	u32	i;

	for( i=0; i<VSD_BMP_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &PokePanelBmpData[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP削除
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBmpExit( VSD_WORK * wk )
{
	u32	i;

	for( i=0; i<VSD_BMP_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ニックネーム表示
 *
 * @param	wk		ワーク
 * @param	mman	メッセージマネージャ
 * @param	nfont	8x8フォント
 * @param	wset	ワードセット
 * @param	buf		文字列展開バッファ
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckPutName(
				VSD_WORK * wk, MSGDATA_MANAGER * mman,
				NUMFONT * nfnt, WORDSET * wset, STRBUF * buf, u32 pos )
{
	POKEMON_PARAM * pp;
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[pos*4+WIN_NAME1];

	// 名前
	if( pos < 3 ){
		pp = PokeParty_GetMemberPointer( wk->dat->pp[VSD_PARTY_LEFT1], pos );
	}else{
		pp = PokeParty_GetMemberPointer( wk->dat->pp[VSD_PARTY_LEFT2], pos-3 );
	}
	str = MSGMAN_AllocString( mman, mes_pokelist_01_09+pos );
	WORDSET_RegisterPokeNickName( wset, 0, PPPPointerGet(pp) );
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf,
		PRM_NICKNAME_PX, PRM_NICKNAME_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	// 性別
	if( wk->poke[pos].sex_put == 0 ){
		if( wk->poke[pos].sex == PARA_MALE ){
			MSGMAN_GetString( mman, mes_pokelist_01_28, buf );
			GF_STR_PrintColor(
				win, FONT_SYSTEM, buf,
				PRM_SEX_PX, PRM_SEX_PY, MSG_NO_PUT, PCOL_N_BLUE, NULL );
		}else if( wk->poke[pos].sex == PARA_FEMALE ){
			MSGMAN_GetString( mman, mes_pokelist_01_29, buf );
			GF_STR_PrintColor(
				win, FONT_SYSTEM, buf,
				PRM_SEX_PX, PRM_SEX_PY, MSG_NO_PUT, PCOL_N_RED, NULL );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * レベル表示
 *
 * @param	wk		ワーク
 * @param	mman	メッセージマネージャ
 * @param	nfont	8x8フォント
 * @param	wset	ワードセット
 * @param	buf		文字列展開バッファ
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckPutLv(
				VSD_WORK * wk, MSGDATA_MANAGER * mman,
				NUMFONT * nfnt, WORDSET * wset, STRBUF * buf, u32 pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[pos*4+WIN_LV1];

	// LV
	NUMFONT_WriteMark( nfnt, NUMFONT_MARK_LV, win, STR_LV_PX, STR_LV_PY );
	str = MSGMAN_AllocString( mman, mes_pokelist_01_03+pos );
	WORDSET_RegisterNumber(
		wset, 0, wk->poke[pos].lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf, NUMFONT_MARK_WIDTH, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * HP表示
 *
 * @param	wk		ワーク
 * @param	mman	メッセージマネージャ
 * @param	nfont	8x8フォント
 * @param	wset	ワードセット
 * @param	buf		文字列展開バッファ
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckPutHP(
				VSD_WORK * wk, MSGDATA_MANAGER * mman,
				NUMFONT * nfnt, WORDSET * wset, STRBUF * buf, u32 pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[pos*4+WIN_HP1];

	// HP
	str = MSGMAN_AllocString( mman, mes_pokelist_01_21+pos );
	WORDSET_RegisterNumber(
		wset, 0, wk->poke[pos].hp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, buf, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf, STR_SLASH_PX-siz, STR_SLASH_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	// スラッシュ
	MSGMAN_GetString( mman, mes_pokelist_01_27, buf );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf, STR_SLASH_PX, STR_SLASH_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, buf, 0 );
	// MHP
	str = MSGMAN_AllocString( mman, mes_pokelist_01_15+pos );
	WORDSET_RegisterNumber(
		wset, 0, wk->poke[pos].mhp, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, buf, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, buf, STR_SLASH_PX+siz, STR_SLASH_PY, MSG_NO_PUT, PCOL_N_WHITE, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * HPゲージ表示
 *
 * @param	wk		ワーク
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckPutGage( VSD_WORK * wk, u32 pos )
{
	GF_BGL_BMPWIN * win;
	u32	siz;

	win = &wk->win[pos*4+WIN_HPBAR1];

	// HPゲージ
	siz = GetHPGaugeDottoColor( wk->poke[pos].hp, wk->poke[pos].mhp, HPGAUGE_DOTTO_MAX );
	OS_Printf( "HP COLLOR : %d\n", siz );
	switch( siz ){
	case HP_DOTTO_NULL:
		break;
	case HP_DOTTO_MAX:		// 緑
	case HP_DOTTO_GREEN:
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PALPOS_GREEN],
			2*2, (win->palnum*16+HPGAUGE_COL1)*2 );
		break;
	case HP_DOTTO_YELLOW:	// 黄
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PALPOS_YELLOW],
			2*2, (win->palnum*16+HPGAUGE_COL1)*2 );
		break;
	case HP_DOTTO_RED:		// 赤
		GF_BGL_PaletteSet(
			GF_BGL_FRAME1_M, &wk->pal[PALPOS_RED],
			2*2, (win->palnum*16+HPGAUGE_COL1)*2 );
		break;
	}

	siz = GetNumDotto( wk->poke[pos].hp, wk->poke[pos].mhp, HPGAUGE_DOTTO_MAX );
	GF_BGL_BmpWinFill( win, HPGAUGE_COL2, 0, 2, siz, 1 );
	GF_BGL_BmpWinFill( win, HPGAUGE_COL1, 0, 3, siz, 2 );
	GF_BGL_BmpWinFill( win, HPGAUGE_COL2, 0, 5, siz, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP表示メイン
 *
 * @param	wk		ワーク
 * @param	mman	メッセージマネージャ
 * @param	nfont	8x8フォント
 * @param	wset	ワードセット
 * @param	buf		文字列展開バッファ
 * @param	pos		位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBmpPutMain(
				VSD_WORK * wk, MSGDATA_MANAGER * mman,
				NUMFONT * nfnt, WORDSET * wset, STRBUF * buf, u32 pos )
{
	POKEMON_PARAM * pp;
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[pos*4];

	GF_BGL_BmpWinDataFill( &win[WIN_NAME1], 0 );
	GF_BGL_BmpWinDataFill( &win[WIN_LV1], 0 );
	GF_BGL_BmpWinDataFill( &win[WIN_HP1], 0 );
	GF_BGL_BmpWinDataFill( &win[WIN_HPBAR1], 0 );

	VSD_PokeCheckPutName( wk, mman, nfnt, wset, buf, pos );
	VSD_PokeCheckPutLv( wk, mman, nfnt, wset, buf, pos );
	VSD_PokeCheckPutHP( wk, mman, nfnt, wset, buf, pos );
	VSD_PokeCheckPutGage( wk, pos );

	GF_BGL_BmpWinOnVReq( &win[WIN_NAME1] );
	GF_BGL_BmpWinOnVReq( &win[WIN_LV1] );
	GF_BGL_BmpWinOnVReq( &win[WIN_HP1] );
	GF_BGL_BmpWinOnVReq( &win[WIN_HPBAR1] );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP表示
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VSD_PokeCheckBmpPut( VSD_WORK * wk )
{
	MSGDATA_MANAGER * mman;		// メッセージデータマネージャ
	NUMFONT * nfnt;				// 8x8フォント
	WORDSET * wset;				// 単語セット
	STRBUF * buf;
	u32	i;

	mman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_pokelist_dat, wk->dat->heap );
	nfnt = NUMFONT_Create( 15, 14, 0, wk->dat->heap );
	wset = WORDSET_Create( wk->dat->heap );
	buf  = STRBUF_Create( TMP_MSG_SIZ, wk->dat->heap );

	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		VSD_PokeCheckBmpPutMain( wk, mman, nfnt, wset, buf, i );
	}

	STRBUF_Delete( buf );
	MSGMAN_Delete( mman );
	NUMFONT_Delete( nfnt );
	WORDSET_Delete( wset );
}









// 冒険ノートデータ作成
static void VSD_FnoteMake( VS_DEMO_DATA * dat )
{
	void * buf;
	STRCODE * name1;
	STRCODE * name2;
	u8	sex1;
	u8	sex2;
	u8	result;
	u8	sio_id;

	if( dat->bp == NULL ){ return; }

	sio_id = CommGetCurrentID();	// 自分の通信ID
	result = dat->result - 1;		// 冒険ノートの勝敗に変換

	OS_Printf( "VSD_RESULT (1) : %d\n", dat->result );
	OS_Printf( "VSD_RESULT (2) : %d\n", result );

	// ユニオン
	if( ZoneData_IsUnionRoom( dat->bp->zone_id ) == TRUE ){
		sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[sio_id^1].tr_type );
		name1 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
		STRBUF_GetStringCode( dat->name[CommGetStandNo(sio_id^1)], name1, BUFLEN_PERSON_NAME );
		buf = FNOTE_SioUnionBattleDataMake( name1, sex1, result, dat->heap );
		sys_FreeMemoryEz( name1 );
	// 通信対戦
	}else{
		switch( CommStateGetServiceNo() ){
		case COMM_MODE_BATTLE_SINGLE:	// 1vs1 バトル
			sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[sio_id^1].tr_type );
			name1 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
			STRBUF_GetStringCode( dat->name[CommGetStandNo(sio_id^1)], name1, BUFLEN_PERSON_NAME );
			buf = FNOTE_SioSingleBtlDataMake( name1, sex1, result, dat->heap );
			sys_FreeMemoryEz( name1 );
			break;

		case COMM_MODE_BATTLE_DOUBLE:	// 1vs1 ダブルバトル
			sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[sio_id^1].tr_type );
			name1 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
			STRBUF_GetStringCode( dat->name[CommGetStandNo(sio_id^1)], name1, BUFLEN_PERSON_NAME );
			buf = FNOTE_SioDoubleBtlDataMake( name1, sex1, result, dat->heap );
			sys_FreeMemoryEz( name1 );
			break;

		case COMM_MODE_BATTLE_MIX_1ON1:	// 1vs1 ミックスバトル
			sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[sio_id^1].tr_type );
			name1 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
			STRBUF_GetStringCode( dat->name[CommGetStandNo(sio_id^1)], name1, BUFLEN_PERSON_NAME );
			buf = FNOTE_SioMixBtl1DataMake( name1, sex1, result, dat->heap );
			sys_FreeMemoryEz( name1 );
			break;

		case COMM_MODE_BATTLE_MULTI:	// 2vs2 マルチバトル
			name1 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
			name2 = sys_AllocMemory( dat->heap, sizeof(STRCODE)*BUFLEN_PERSON_NAME );
//			if( sio_id == 0 || sio_id == 2 ){
			if( VSD_GetStandID() == TRUE ){
				sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[1].tr_type );
				sex2  = TT_TrainerTypeSexGet( dat->bp->trainer_data[3].tr_type );
				STRBUF_GetStringCode( dat->name[1], name1, BUFLEN_PERSON_NAME );
				STRBUF_GetStringCode( dat->name[3], name2, BUFLEN_PERSON_NAME );
			}else{
				sex1  = TT_TrainerTypeSexGet( dat->bp->trainer_data[0].tr_type );
				sex2  = TT_TrainerTypeSexGet( dat->bp->trainer_data[2].tr_type );
				STRBUF_GetStringCode( dat->name[0], name1, BUFLEN_PERSON_NAME );
				STRBUF_GetStringCode( dat->name[2], name2, BUFLEN_PERSON_NAME );
			}
			buf = FNOTE_SioMultiBtlDataMake( name1, name2, sex1, sex2, result, dat->heap );
			sys_FreeMemoryEz( name1 );
			sys_FreeMemoryEz( name2 );
			break;

		default:
			return;
		}
	}

	FNOTE_DataSave( dat->bp->fnote_data, buf, FNOTE_TYPE_SIO );
}




















#ifdef PM_DEBUG
//============================================================================================
//============================================================================================
//============================================================================================
//	デバッグ処理
//============================================================================================
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_nakahiro.h"


static void D_VSDemoVramSet(void);

PROC_RESULT D_VSDemoProc_Init00( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init01( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init10( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init11( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init20( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init21( PROC * proc, int * seq );
PROC_RESULT D_VSDemoProc_Init22( PROC * proc, int * seq );
PROC_RESULT D_VsDemoProc_Main( PROC * proc, int * seq );
PROC_RESULT D_VsDemoProc_End( PROC * proc, int * seq );



static POKEMON_PARAM * vspp[12];
static STRBUF * vsstr[4];

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT D_VsDemoProc_Init( PROC * proc, int * seq, u8 mode, u8 type, u8 result )
{
	VS_DEMO_DATA * dat;
	u32	i;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BAG, 0x80000 );

	dat = PROC_AllocWork( proc, sizeof(VS_DEMO_DATA), HEAPID_BAG );
	memset( dat, 0, sizeof(VS_DEMO_DATA) );

	dat->heap = HEAPID_BAG;
	dat->mode = mode;
	dat->type = type;
	dat->result = result;

	dat->bp = NULL;

	// ポケモン作成
	dat->pp[0] = PokeParty_AllocPartyWork( HEAPID_BAG );
	dat->pp[1] = PokeParty_AllocPartyWork( HEAPID_BAG );
	dat->pp[2] = PokeParty_AllocPartyWork( HEAPID_BAG );
	dat->pp[3] = PokeParty_AllocPartyWork( HEAPID_BAG );
	for( i=0; i<12; i++ ){
		vspp[i] = PokemonParam_AllocWork( HEAPID_BAG );
	}

	for( i=0; i<11; i++ ){
		if( i == 5 || i == 11 ){
			PokeParaSet( vspp[i], 0, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
		}else{
			u16	item = 1;
			u8	cb = (u8)i+1;
			PokeParaSet( vspp[i], i+1, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
			PokeParaPut( vspp[i], ID_PARA_item, &item );
			PokeParaPut( vspp[i], ID_PARA_cb_id, &cb );
		}
		PokeParty_Add( dat->pp[i/3], vspp[i] );
	}
/*
	PokeParaSet( vspp[0], 1, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
	PokeParty_Add( dat->pp[0], vspp[0] );
	PokeParaSet( vspp[1], 3, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
	PokeParty_Add( dat->pp[2], vspp[1] );
	PokeParaSet( vspp[2], 1, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
	PokeParty_Add( dat->pp[1], vspp[2] );
	PokeParaSet( vspp[3], 3, 50, POW_RND, RND_SET, 0, ID_SET, 0 );
	PokeParty_Add( dat->pp[3], vspp[3] );
*/
	// 名前作成
	{
		MSGDATA_MANAGER * man;

		man = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_nakahiro_dat, HEAPID_BAG );
		vsstr[0] = MSGMAN_AllocString( man, msg_vsd_name00 );
		vsstr[1] = MSGMAN_AllocString( man, msg_vsd_name01 );
		vsstr[2] = MSGMAN_AllocString( man, msg_vsd_name02 );
		vsstr[3] = MSGMAN_AllocString( man, msg_vsd_name03 );

		dat->name[VSD_PARTY_LEFT1]  = vsstr[0];
		dat->name[VSD_PARTY_LEFT2]  = vsstr[1];
		dat->name[VSD_PARTY_RIGHT1] = vsstr[2];
		dat->name[VSD_PARTY_RIGHT2] = vsstr[3];

		MSGMAN_Delete( man );
	}

	VSDemo_TaskAdd( dat );

//	D_VSDemoVramSet();

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット

	Snd_DataSetByScene( SND_SCENE_BATTLE, SEQ_BA_TRAIN, 1 );	// バトル曲再生

	return PROC_RES_FINISH;
}

PROC_RESULT D_VSDemoProc_Init00( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_MULTI, VSD_TYPE_LEFT, 0 );
}
PROC_RESULT D_VSDemoProc_Init01( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_MULTI, VSD_TYPE_RIGHT, 0 );
}
PROC_RESULT D_VSDemoProc_Init10( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_IN, VSD_TYPE_NORMAL, 0 );
}
PROC_RESULT D_VSDemoProc_Init11( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_IN, VSD_TYPE_MULTI, 0 );
}
PROC_RESULT D_VSDemoProc_Init20( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_END, VSD_TYPE_NORMAL, VSD_RESULT_WIN );
}
PROC_RESULT D_VSDemoProc_Init21( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_END, VSD_TYPE_MULTI, VSD_RESULT_LOSE );
}
PROC_RESULT D_VSDemoProc_Init22( PROC * proc, int * seq )
{
	return D_VsDemoProc_Init( proc, seq, VSD_MODE_END, VSD_TYPE_NORMAL, VSD_RESULT_DRAW );
}



//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT D_VsDemoProc_Main( PROC * proc, int * seq )
{
	VS_DEMO_DATA * dat  = PROC_GetWork( proc );

	if( dat->end_flg == 1 ){
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT D_VsDemoProc_End( PROC * proc, int * seq )
{
	VS_DEMO_DATA * dat = PROC_GetWork( proc );
	u32	i;

	sys_FreeMemoryEz( dat->pp[0] );
	sys_FreeMemoryEz( dat->pp[1] );
	sys_FreeMemoryEz( dat->pp[2] );
	sys_FreeMemoryEz( dat->pp[3] );
	for( i=0; i<12; i++ ){
		sys_FreeMemoryEz( vspp[i] );
	}

	for( i=0; i<4; i++ ){
		if( vsstr[i] != NULL ){ STRBUF_Delete( vsstr[i] ); }
	}

	PROC_FreeWork( proc );				// ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_BAG );

	return PROC_RES_FINISH;
}


#endif
