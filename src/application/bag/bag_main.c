//============================================================================================
/**
 * @file	bag_main.c
 * @brief	バッグ画面処理
 * @author	Hiroyuki Nakamura
 * @date	06.04.17
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/gamedata.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/pm_str.h"
#include "system/pmfprint.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/brightness.h"
#include "system/buflen.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/mystatus.h"
#include "system/wipe.h"
#include "savedata/config.h"
#include "savedata/encount.h"
#include "savedata/vidro_type.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "itemtool/itemuse_def.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_bag.h"
#include "msgdata/msg_common_scr.h"
#include "field/itemuse.h"
#include "application/app_tool.h"
#include "communication/wm_icon.h"

#include "../../field/map_mode.h"

#define	BAG_MAIN_H_GLOBAL
#include "application/bag.h"
#include "bag_main.h"
#include "bag_obj.h"
#include "bag_bmp.h"
#include "bag_snd_def.h"
#include "bag_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_PAGE,
	SEQ_IREKAE,
	SEQ_MENU,
	SEQ_YESNO,
	SEQ_NUM,

	SEQ_ITEM_SUB_MAIN,		// メニュー「すてる」個数選択
	SEQ_ITEM_SUB_YN_INIT,	// メニュー「すてる」はい・いいえ初期化
	SEQ_ITEM_SUB_YN_SEL,	// メニュー「すてる」はい・いいえ
	SEQ_ITEM_SUB_CMP,		// メニュー「すてる」完了
	SEQ_ITEM_SUB_RET,		// メニュー「すてる」メッセージ終了待ち＆ボタン待ち -> メインへ

	SEQ_ITEM_ERR_WAIT,	// アイテム使用失敗

	SEQ_BAG_ITEMUSE,	// バッグ内アイテム使用

	SEQ_ITEMSET_MAIN,	// ポケモンリスト「もたせる」アイテム選択
	SEQ_ITEMSET_ERR,	// ポケモンリスト「もたせる」失敗

	SEQ_SALE_MAIN,		// 「売る」モードアイテム選択
	SEQ_SALE_NUM_INIT,	// 「売る」モード個数選択初期化
	SEQ_SALE_NUM_SEL,	// 「売る」モード個数選択
	SEQ_SALE_YN_INIT,	// 「売る」はい・いいえ初期化
	SEQ_SALE_YN_SEL,	// 「売る」はい・いいえ
	SEQ_SALE_CMP,		// 「売る」完了
	SEQ_SALE_RET,		// 「売る」メッセージ終了待ち＆ボタン待ち -> メインへ

	SEQ_KINOMISEL_MAIN,	// 木の実関連選択処理

	SEQ_OUT,
};

#define	WIPE_COUNT_M	( 192 )		// 上画面のウィンドウエフェクトカウンタの最大値
#define	WIPE_COUNT_S	( 384 )		// 下画面のウィンドウエフェクトカウンタの最大値
#define	WIPE_SPEED		( 16 )		// ウィンドウエフェクトスピード
#define	VCOUNT_MAX		( 262 )		// Vカウンタ最大値
// ウィンドウのマスク
#define	WIPE_MASK		(	GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | \
							GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | \
							GX_WND_PLANEMASK_OBJ )

// アイテムリスト選択
enum {
	LIST_SEL_NONE = 0,	// 選択中
	LIST_SEL_ITEM,		// アイテムを選択
	LIST_SEL_CHANGE,	// 入れ替え
	LIST_SEL_CANCEL		// キャンセル
};


// ボタンデータ
typedef struct {
	const u8 * write_tbl;			// ボタン位置（キャラ単位）
	const RECT_HIT_TBL * rect_tbl;	// タッチパネル判定テーブル
}SUB_BUTTON_POS;

// ボタンアニメ用TCBワーク
typedef struct {
	BAG_WORK * bag_wk;	// バッグ画面のワーク
	u8	seq;			// シーケンス
	u8	cnt;			// カウンタ
	u8	button;			// ボタン番号
}BUTTON_ANM_WORK;

// ボタンアニメ用ワーク
typedef struct {
	u8	seq;			// シーケンス
	u8	cnt;			// カウンタ
	u8	button;			// ボタン番号
}BUTTON_ANM_WK;

#define	BAG_TMPMSG_SIZ	( 256 )		// メッセージ展開場所の文字数


typedef int (*seqFunc)(BAG_WORK*);	// シーケンス関数ポインタ型


#define	ICONPUT_SCRN_PX		( 0 )
#define	ICONPUT_SCRN_PY		( 18 )
#define	ICONPUT_SCRN_SX		( 5 )
#define	ICONPUT_SCRN_SY		( 5 )


#define	LIST_PX_NORMAL		( 0 )		// アイテムリストの表示X座標（通常）
#define	LIST_PX_WAZAMACHINE	( 32 )		// アイテムリストの表示X座標（技マシン）

#define	SUB_ENTER_PX		( 13 )		// 下画面の決定ボタンのスクリーン書き換えX座標
#define	SUB_ENTER_PY		( 7 )		// 下画面の決定ボタンのスクリーン書き換えY座標
#define	SUB_ENTER_SX		( 6 )		// 下画面の決定ボタンのスクリーン書き換えXサイズ
#define	SUB_ENTER_SY		( 6 )		// 下画面の決定ボタンのスクリーン書き換えYサイズ
#define	SUB_ENTER_CGX		( 0x276)	// 下画面の決定ボタンのキャラ番号
#define	SUB_ENTER_PAL		( 3 )		// 下画面の決定ボタンのパレット

#define	SUB_ENTER_EFF_X		( 128 )		// 下画面の決定ボタンのエフェクト表示X座標
#define	SUB_ENTER_EFF_Y		( 80 )		// 下画面の決定ボタンのエフェクト表示Y座標

#define	SUB_WHEEL_CX	( 128 )		// 下画面のホイールの中心X座標
#define	SUB_WHEEL_CY	( 80 )		// 下画面のホイールの中心Y座標
#define	SUB_WHEEL_R		( 80 )		// 下画面のホイールの半径

#define	SUB_WHEEL_REG	( 2 )		// 下画面のホイールのグラフィック回転補正

#define	WHEEL_ROT_LIST	( 36 )		// 下画面ホイールで一周でリストが動くカウント
#define	WHEEL_ROT_MENU	( 18 )		// 下画面ホイールで一周でメニューが動くカウント


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BAG_SaveDataGet( BAG_WORK * wk );
static void BagVBlank(void * work);
static void BagVramBankSet(void);
static void BagBgSet( GF_BGL_INI * ini );
static void BagBgExit( GF_BGL_INI * ini );
static void BagBgGraphicSet( BAG_WORK * wk );
//static void BagWindowSet(void);
static u8 ItemListControl( BAG_WORK * wk );
static u8 PocketControl( BAG_WORK * wk );
static int MenuControl( BAG_WORK * wk );
//static void BagInWipeEff(void * work);
static void ItemListDataMake( BAG_WORK * wk );
static void ItemListParamReset( u16 * scr, u16 * pos, u8 buf_max );
static void ItemListParamResetAll( BAG_WORK * wk );
static void ItemListCurPosReset( u16 * scr, u16 * pos, u8 buf_max, u8 list_max );
static void ItemListCurPosResetAll( BAG_WORK * wk );
static void ItemListSet( BAG_WORK * wk, u16 scr, u16 pos );
static void CB_ItemListMove( BMPLIST_WORK * work, u32 param, u8 mode );
static void CB_ItemListWrite( BMPLIST_WORK * work, u32 param, u8 y );
static void ItemListExit( BAG_WORK * wk );
static void ItemInfoPrint( u16 id, s8 wait );
static void CellActorTest(void);
//static void WipeEffOff(void);
static void BagCellActorInit( BAG_WORK * wk );
static void PocketDataInit( BAG_WORK * wk );
static u8 PocketCursorObjPXGet( BAG_WORK * wk, u8 poke );
static void PocketIconXmake( BAG_WORK * wk );
static int SubPokeButtonCheck( BAG_WORK * wk );
static void PokeArrowMove( BAG_WORK * wk );
static void SubPokeButtonBgChg( BAG_WORK * wk, u8 num, u8 anm );
static u8 PocketButtonControl( BAG_WORK * wk );
static int SubPokeButtonEndCheck( BAG_WORK * wk );
static void ItemMenuExit( BAG_WORK * wk );
static u8 PocketCursorMove( BAG_WORK * wk );
static void SubPokeButtonBgChg( BAG_WORK * wk, u8 num, u8 anm );
static void SubPokeButtonBgInit( BAG_WORK * wk );
static u8 ItemChangeChack( BAG_WORK * wk );
static void ItemChangeInit( BAG_WORK * wk );
static u8 ItemChangeMain( BAG_WORK * wk );
static void ItemChangeComp( BAG_WORK * wk );
static void ItemChangeEnd( BAG_WORK * wk );
static void ItemChgCursorChg( BAG_WORK * wk );
static void ItemIconChange( BAG_WORK * wk, u16 item );
static void PocketChangeInitKey( BAG_WORK * wk );
static void PocketChangeInitTp( BAG_WORK * wk );
static void PocketChangeInit( BAG_WORK * wk );
static u8 PocketChange( BAG_WORK * wk );
static u8 PocketChangeReset( BAG_WORK * wk );
static u8 ButtonAnmTask( BAG_WORK * wk );
static u8 PocketCursorMove( BAG_WORK * wk );
static void MsgManCreate( BAG_WORK * wk );
static void PocketNameScreenPut( BAG_WORK * wk );
static void ItemMenuMake( BAG_WORK * wk );
static void ItemListStrAlloc( BAG_WORK * wk );
static void ItemListStrFree( BAG_WORK * wk );
static int Bag_MenuUse( BAG_WORK * wk );
static int MainSeqFunc( BAG_WORK * wk );
static int SaleMainSeq( BAG_WORK * wk );
static int SaleRetSeq( BAG_WORK * wk );
static int SaleNumInitSeq( BAG_WORK * wk );
static int SaleNumSelSeq( BAG_WORK * wk );
static int SaleYesNoInitSeq( BAG_WORK * wk );
static int SaleYesNoSelectSeq( BAG_WORK * wk );
static int SaleCmpSeq( BAG_WORK * wk );
static int ItemErrWaitSeq( BAG_WORK * wk );
static int Bag_MenuTag( BAG_WORK * wk );
static int Bag_MenuKettei( BAG_WORK * wk );
static int Bag_MenuSub( BAG_WORK * wk );
static int Bag_MenuSubMain( BAG_WORK * wk );
static int Bag_MenuSubYesNoInitSeq( BAG_WORK * wk );
static int Bag_MenuSubYesNoSelectSeq( BAG_WORK * wk );
static int Bag_MenuSubCmpSeq( BAG_WORK * wk );
static int Bag_MenuSubRetSeq( BAG_WORK * wk );
static int Bag_MenuSet( BAG_WORK * wk );
static int Bag_MenuCnvSet( BAG_WORK * wk );
static int Bag_MenuCnvDel( BAG_WORK * wk );

static int PokeItemSet_MainSeq( BAG_WORK * wk );
static int PokeItemSet_ErrorSeq( BAG_WORK * wk );
static int KinomiSel_MainSeq( BAG_WORK * wk );
static void BAG_CursorInit( BAG_WORK * wk );
static void BAG_CursorSave( BAG_WORK * wk );

static int BAG_ItemUse( BAG_WORK * wk );
static int Seq_BagItemUse( BAG_WORK * wk );
static int BAG_ItemUseWazaMachine( BAG_WORK * wk );
static BOOL BAG_ItemUseMsgNormal( BAG_WORK * wk, u16 item );
static STRBUF * BAG_SpraySet( BAG_WORK * wk, u16 item );
static void BAG_ItemSubListReset( BAG_WORK * wk );
static int BAG_ItemUseMsgNormalFunc( BAG_WORK * wk );

static void BAG_ItemSubListReset( BAG_WORK * wk );

static void BAG_IconPutScrnChg( BAG_WORK * wk, u8 flg );

static BOOL BAG_SubEnterButtonCheck( BAG_WORK * wk );
static void SubEnterButtonBgChg( BAG_WORK * wk, u8 anm );
static void SubEnterButtonAnm( BAG_WORK * wk );

static void BAG_WheelMoveKey( BAG_WORK * wk, s8 mv );
static BOOL BAG_WheelMenuMove( BAG_WORK * wk );
static BOOL BAG_WheelMove( BAG_WORK * wk, u16 mv_rot );
static s16 BAG_WheelRotGet( BAG_WORK * wk, u16 x, u16 y );
static BOOL BAG_WheelListMove( BAG_WORK * wk );
static BOOL BAG_WheelChgListMove( BAG_WORK * wk );
static BOOL BAG_WheelNumSel( BAG_WORK * wk, s16 * num, u16 max );
static BOOL BAG_WheelListWrite( BAG_WORK * wk, u16 mv );
static BOOL BAG_WheelChgListWrite( BAG_WORK * wk, u16 mv );
static BOOL BAG_WheelMenuWrite( BAG_WORK * wk, u8 prm );


//============================================================================================
//	グローバル変数
//============================================================================================
//static u32	WipeCount = 0;		// ウィンドウエフェクト用カウンタ ( HBLANK )

// プロセス定義データ
const PROC_DATA BagProcData = {
	BagProc_Init,
	BagProc_Main,
	BagProc_End,
	NO_OVERLAY_ID,
};

// アイテムリストデータ（BMPリスト）
static const BMPLIST_HEADER BagItemList = {
	NULL, CB_ItemListMove, CB_ItemListWrite, NULL,
	0, 9, 0,
	0, 0,			// 項目X, カーソルX
	0,				// 表示Y
	FBMP_COL_BLACK, FBMP_COL_NULL, FBMP_COL_BLK_SDW,
	0, 16,						// 文字間隔Ｙ
	BMPLIST_NO_SKIP, FONT_SYSTEM, 1,
	NULL,
};



// 8ボタンの位置テーブル
static const u8 PokeButtonPos8[] = {
	1, 4,	2, 10,	5, 15,	10, 18,	17, 18,	22, 15,	25, 10,	26, 4,
};

// 8ボタンのタッチパネル判定テーブル
static const RECT_HIT_TBL PokeButtonRect8[] =
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

// 4ボタンの位置テーブル
static const u8 PokeButtonPos4[] = {
	1, 4,	5, 15,	22, 15,	26, 4,
};

// 4ボタンのタッチパネル判定テーブル
static const RECT_HIT_TBL PokeButtonRect4[] =
{
	{ 4*8,	9*8-1,	1*8,  6*8-1 },
	{ 15*8,	20*8-1,	5*8,  10*8-1 },
	{ 15*8,	20*8-1, 22*8, 27*8-1 },
	{ 4*8,	9*8-1,	26*8, 31*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

// 1ボタンの位置テーブル
static const u8 PokeButtonPos1[] = {
	17, 18,
};

// 1ボタンのタッチパネル判定テーブル
static const RECT_HIT_TBL PokeButtonRect1[] =
{
	{ 18*8,	23*8-1,	17*8, 22*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

// 7ボタンの位置テーブル
static const u8 PokeButtonPos7[] = {
	2, 10,	5, 15,	10, 18,	17, 18,	22, 15,	25, 10,	26, 4,
};

// 7ボタンのタッチパネル判定テーブル
static const RECT_HIT_TBL PokeButtonRect7[] =
{
	{ 10*8,	15*8-1,	2*8,  7*8-1 },
	{ 15*8,	20*8-1,	5*8,  10*8-1 },
	{ 18*8,	23*8-1,	10*8, 15*8-1 },
	{ 18*8,	23*8-1,	17*8, 22*8-1 },
	{ 15*8,	20*8-1, 22*8, 27*8-1 },
	{ 10*8,	15*8-1, 25*8, 30*8-1 },
	{ 4*8,	9*8-1,	26*8, 31*8-1 },
	{ RECT_HIT_END, 0, 0, 0 }
};

// ボタンデータ
static const SUB_BUTTON_POS PokeButtonPos[] =
{
	{ NULL, NULL },							// 0
	{ PokeButtonPos1, PokeButtonRect1 },	// 1
	{ NULL, NULL },							// 2
	{ NULL, NULL },							// 3
	{ PokeButtonPos4, PokeButtonRect4 },	// 4
	{ NULL, NULL },							// 5
	{ NULL, NULL },							// 6
	{ PokeButtonPos7, PokeButtonRect7 },	// 7
	{ PokeButtonPos8, PokeButtonRect8 }		// 8
};



static const u8 PocketMax[] = {
	BAG_NORMAL_ITEM_MAX,	// 道具ポケット最大数
	BAG_DRUG_ITEM_MAX,		// 薬ポケット最大数
	BAG_BALL_ITEM_MAX,		// モンスターボールポケット最大数
	BAG_WAZA_ITEM_MAX,		// 技マシンポケット最大数
	BAG_NUTS_ITEM_MAX,		// 木の実ポケット最大数
	BAG_SEAL_ITEM_MAX,		// シールポケット最大数
	BAG_BATTLE_ITEM_MAX,	// 戦闘用アイテムポケット最大数
	BAG_EVENT_ITEM_MAX,		// 大切な物ポケット最大数
};


// メニューパラメータテーブル
static const u32 MenuParamTbl[] = {
	(u32)Bag_MenuUse,		// つかう
	(u32)Bag_MenuUse,		// おりる
	(u32)Bag_MenuUse,		// みる
	(u32)Bag_MenuUse,		// うめる
	(u32)Bag_MenuUse,		// ひらく
	(u32)Bag_MenuSub,		// すてる
	(u32)Bag_MenuCnvSet,	// とうろく
	(u32)Bag_MenuCnvDel,	// かいじょ
	(u32)Bag_MenuSet,		// もたせる
	(u32)Bag_MenuTag,		// タグをみる
	(u32)Bag_MenuKettei,	// けってい
	BMPMENU_CANCEL,			// やめる
};


static const u16 IconPutScrn_Normal[] = {
	0x1077,0x1078,0x1078,0x1079,0x1026,
	0x1010,0x1011,0x1011,0x1012,0x1013,
	0x1014,0x1001,0x1001,0x1001,0x1034,
	0x1014,0x1001,0x1001,0x1001,0x1034,
	0x1030,0x1031,0x1031,0x1032,0x1033
};
static const u16 IconPutScrn_WMachine[] = {
	0x1026,0x1002,0x1002,0x1002,0x1002,
	0x1026,0x1002,0x1002,0x1002,0x1002,
	0x1026,0x1002,0x1002,0x1002,0x1002,
	0x1026,0x1002,0x1002,0x1002,0x1002,
	0x1026,0x1002,0x1002,0x1002,0x1002
};

// 下画面の決定ボタンのタッチ座標テーブル
static const RECT_HIT_TBL EnterButtonRect[] =
{
	{ 56, 103, 104, 151 },
	{ RECT_HIT_END, 0, 0, 0 }
};

// ホイールのタッチ判定テーブル
static const TP_HIT_TBL WheelHitTbl[] =
{
	{ TP_USE_CIRCLE, SUB_WHEEL_CX, SUB_WHEEL_CY, 26 },
	{ TP_USE_CIRCLE, SUB_WHEEL_CX, SUB_WHEEL_CY, 64 },
	{ TP_HIT_END, 0, 0, 0 }
};

// ホイールを触り続けているかの判定テーブル
static const TP_HIT_TBL WheelContTbl[] =
{
	{ TP_USE_CIRCLE, SUB_WHEEL_CX, SUB_WHEEL_CY, 16 },
	{ TP_USE_CIRCLE, SUB_WHEEL_CX, SUB_WHEEL_CY, 80 },
	{ TP_HIT_END, 0, 0, 0 }
};


//============================================================================================
//	プロセス関数
//============================================================================================

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
PROC_RESULT BagProc_Init( PROC * proc, int * seq )
{
	BAG_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();				// HBlank停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	G2_BlendNone();
	G2S_BlendNone();

//	WipeCount = 0;			// ウィンドウエフェクトカウンタ初期化

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_BAG, 0x30000 );

	wk = PROC_AllocWork( proc, sizeof(BAG_WORK), HEAPID_BAG );
	memset( wk, 0, sizeof(BAG_WORK) );
	wk->dat = PROC_GetParentWork( proc );

	BAG_SaveDataGet( wk );

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_BAG );

	wk->sex  = MyStatus_GetMySex( wk->myst );

//	APP_WipeStart( APP_WIPE_IN, HEAPID_BAG );
	WIPE_SYS_Start(
		WIPE_PATTERN_FMAS, WIPE_TYPE_SHUTTERIN_DOWN, WIPE_TYPE_SHUTTERIN_DOWN,
		WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_BAG );

	sys_KeyRepeatSpeedSet( 3, 8 );

	BAG_CursorInit( wk );				// カーソル位置、ポケット初期設定

	MsgManCreate( wk );
	ItemListStrAlloc( wk );

	PocketDataInit( wk );				// ポケット設定
	PocketIconXmake( wk );				// アイコンの座標取得

	BagVramBankSet();					// VRAM設定
	BagBgSet( wk->bgl );				// BG設定
	BagBgGraphicSet( wk );				// BGグラフィックセット

	SubPokeButtonBgInit( wk );

	InitTPSystem();						// タッチパネルシステム初期化
	InitTPNoBuff(4);

//	BagCellActorInit( wk );				// セルアクター初期化

	BagBmpWinSet( wk );					// BMPウィンドウ設定

	MsgPrintTouchPanelFlagSet( MSG_TP_ON );

	Bag_PocketNameMake( wk );			// ポケット名取得
	Bag_PocketNameScreenPut( wk );		// ポケット名をスクリーンに反映
	Bag_PocketNamePut( wk );			// ポケット名表示
	Bag_PocketIconPutAll( wk );			// ポケットアイコン表示

	Bag_MenuStrGet( wk );				// メニュー項目取得
	Bag_NumStrGet( wk );				// 個数表示文字列取得

	ItemListDataMake( wk );				// アイテムリスト作成

	// アイテムリスト設定
/*
	ItemListCurPosReset(
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur,
		wk->dat->p_data[wk->dat->p_now].max, 9 );
*/

	ItemListParamReset(
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur,
		wk->dat->p_data[wk->dat->p_now].max );
	ItemListCurPosReset(
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur,
		wk->dat->p_data[wk->dat->p_now].max, 9 );

//	ItemListParamResetAll( wk );
//	ItemListCurPosResetAll( wk );

	BagCellActorInit( wk );				// セルアクター初期化

	ItemListSet(
		wk, wk->dat->p_data[wk->dat->p_now].scr, wk->dat->p_data[wk->dat->p_now].cur );

	if( wk->dat->mode == BAG_MODE_MIX || wk->dat->mode == BAG_MODE_MIX_SIO ){
		BagBmp_PorutoWinPut( wk );
	}

//	BagWindowSet();						// ウィンドウ設定

//	sys_HBlankIntrSet( BagInWipeEff, NULL );	// HBlankセット
	sys_VBlankFuncChange( BagVBlank, wk );		// VBlankセット

	Snd_DataSetByScene( SND_SCENE_SUB_BAG, 0, 0 );	// サウンドデータロード(バッグ)(BGM引継ぎ)

	WirelessIconEasyUnion();

	return PROC_RES_FINISH;
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
PROC_RESULT BagProc_Main( PROC * proc, int * seq )
{
	BAG_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() == TRUE ){
//		if( WIPE_SYS_EndCheck() == TRUE && WipeCount > WIPE_COUNT_S ){
//			WipeEffOff();
			if( wk->dat->mode == BAG_MODE_ITEMSALE ){
				*seq = SEQ_SALE_MAIN;
			}else if( wk->dat->mode == BAG_MODE_ITEMSET ){
				*seq = SEQ_ITEMSET_MAIN;
			}else if( wk->dat->mode == BAG_MODE_KINOMI ){
				*seq = SEQ_KINOMISEL_MAIN;
			}else{
				*seq = SEQ_MAIN;
			}
		}
		break;

	case SEQ_MAIN:
		*seq = MainSeqFunc( wk );
		break;

	case SEQ_PAGE:
		PokeArrowMove( wk );
		if( PocketChange( wk ) == TRUE ){
			if( wk->dat->mode == BAG_MODE_ITEMSALE ){
				*seq = SEQ_SALE_MAIN;
			}else if( wk->dat->mode == BAG_MODE_ITEMSET ){
				*seq = SEQ_ITEMSET_MAIN;
			}else if( wk->dat->mode == BAG_MODE_KINOMI ){
				*seq = SEQ_KINOMISEL_MAIN;
			}else{
				*seq = SEQ_MAIN;
			}
		}
		break;

	case SEQ_IREKAE:
		if( ItemChangeMain( wk ) == TRUE ){
//			SubEnterButtonBgChg( wk, 0 );
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MENU:
		*seq = MenuControl( wk );
		break;

	case SEQ_YESNO:
		break;
	case SEQ_NUM:
		break;

	case SEQ_ITEM_SUB_MAIN:		// メニュー「すてる」個数選択
		*seq = Bag_MenuSubMain( wk );
		break;
	case SEQ_ITEM_SUB_YN_INIT:	// メニュー「すてる」はい・いいえ初期化
		*seq = Bag_MenuSubYesNoInitSeq( wk );
		break;
	case SEQ_ITEM_SUB_YN_SEL:	// メニュー「すてる」はい・いいえ
		*seq = Bag_MenuSubYesNoSelectSeq( wk );
		break;
	case SEQ_ITEM_SUB_CMP:		// メニュー「すてる」完了
		*seq = Bag_MenuSubCmpSeq( wk );
		break;
	case SEQ_ITEM_SUB_RET:		// メニュー「すてる」メッセージ終了待ち＆ボタン待ち -> メインへ
		*seq = Bag_MenuSubRetSeq( wk );
		break;

	case SEQ_ITEM_ERR_WAIT:
		*seq = ItemErrWaitSeq( wk );
		break;

	case SEQ_BAG_ITEMUSE:	// バッグ内アイテム使用
		*seq = Seq_BagItemUse( wk );
		break;

	case SEQ_ITEMSET_MAIN:
		*seq = PokeItemSet_MainSeq( wk );
		break;
	case SEQ_ITEMSET_ERR:
		*seq = PokeItemSet_ErrorSeq( wk );
		break;

	case SEQ_SALE_MAIN:		// 「売る」モードアイテム選択
		*seq = SaleMainSeq( wk );
		break;
	case SEQ_SALE_NUM_INIT:	// 「売る」モード個数選択初期化
		*seq = SaleNumInitSeq( wk );
		break;
	case SEQ_SALE_NUM_SEL:	// 「売る」モード個数選択
		*seq = SaleNumSelSeq( wk );
		break;
	case SEQ_SALE_YN_INIT:	// 「売る」はい・いいえ初期化
		*seq = SaleYesNoInitSeq( wk );
		break;
	case SEQ_SALE_YN_SEL:	// 「売る」はい・いいえ
		*seq = SaleYesNoSelectSeq( wk );
		break;
	case SEQ_SALE_CMP:		// 「売る」完了
		*seq = SaleCmpSeq( wk );
		break;
	case SEQ_SALE_RET:		// 「売る」メッセージ終了待ち＆ボタン待ち -> メインへ
		*seq = SaleRetSeq( wk );
		break;

	case SEQ_KINOMISEL_MAIN:	// 木の実関連選択処理
		*seq = KinomiSel_MainSeq( wk );
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() == TRUE ){
			return PROC_RES_FINISH;
		}
		break;
	}

	SubEnterButtonAnm( wk );
	BagObj_SubButtonEffMain( wk );
	Bag_ObjAnmMain( wk );
	CATS_Draw( wk->crp );

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
PROC_RESULT BagProc_End( PROC * proc, int * seq )
{
	BAG_WORK * wk  = PROC_GetWork( proc );

//	CATS_ResourceDestructor( wk->csp, wk->crp );
//	CATS_FreeMemory( wk->csp );
	BAGOBJ_ClactFree( wk );

	ItemListExit( wk );				// アイテムリスト削除
	BAG_CursorSave( wk );
	BagBmpWinExit( wk->win );		// BMPウィンドウ開放
	BagBgExit( wk->bgl );			// BGL削除
	StopTP();						// タッチパネル終了
	DellVramTransferManager();

	Bag_MenuStrRelease( wk );
	Bag_PocketNameRelease( wk );
	Bag_NumStrRelease( wk );

	ItemListStrFree( wk );

	STRBUF_Delete( wk->expb );

	MSGMAN_Delete( wk->waza_man );
	MSGMAN_Delete( wk->item_man );
	MSGMAN_Delete( wk->msg_man );
	NUMFONT_Delete( wk->num_font );
	WORDSET_Delete( wk->wset );

	ArchiveDataHandleClose( wk->gra_h );

	PROC_FreeWork( proc );				// ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_BAG );

	return PROC_RES_FINISH;
}


//============================================================================================
//	セーブデータ操作
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * セーブデータから必要なデータを取り出す
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BAG_SaveDataGet( BAG_WORK * wk )
{
	wk->myitem = SaveData_GetMyItem( wk->dat->sv );
	wk->myst   = SaveData_GetMyStatus( wk->dat->sv );
	wk->cfg    = SaveData_GetConfig( wk->dat->sv );
}

//--------------------------------------------------------------------------------------------
/**
 * エンカウントセーブデータのポインタ取得
 *
 * @param	wk		ワーク
 *
 * @return	エンカウントセーブデータのポインタ
 */
//--------------------------------------------------------------------------------------------
static ENC_SV_PTR BAG_EncountSaveGet( BAG_WORK * wk )
{
	return EncDataSave_GetSaveDataPtr( wk->dat->sv );
}

//--------------------------------------------------------------------------------------------
/**
 * セーブデータにスプレーの効果を入れる
 *
 * @param	wk		ワーク
 * @param	prm		スプレーの効果
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BAG_SaveDataSpraySet( BAG_WORK * wk, u8 prm )
{
	u8 * swk;
	
	swk  = EncDataSave_GetSprayCnt( BAG_EncountSaveGet(wk) );
	*swk = prm;
}

//--------------------------------------------------------------------------------------------
/**
 * セーブデータにビードロの効果を入れる
 *
 * @param	wk		ワーク
 * @param	type	ビードロのタイプ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BAG_SaveDataVidroSet( BAG_WORK * wk, u8 type )
{
	EncDataSave_SetVidro( BAG_EncountSaveGet(wk), type );
}


//============================================================================================
//	設定
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BagVBlank( void * work )
{
	BAG_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );

	// セルアクター
	DoVramTransferManager();	// Vram転送マネージャー実行
	CATS_RenderOamTrans();
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
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
static void BagVramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );

//	GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_2D );	// 2D mapping mode
}

//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BagBgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_1, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// MENU & INFO (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	// FRAME (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// ITEM LIST (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	{	// LIST BACK (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// BUTTON (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	{	// BAG GRAPHIC (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	{	// WHEEL (CHAR)
		GF_BGL_BGCNT_HEADER AffBgCntDat = {
			0, 0, 0x400, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_S, &AffBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_RotateCenterSetReq( ini, GF_BGL_FRAME3_S, GF_BGL_CENTER_X_SET, 128 );
		GF_BGL_RotateCenterSetReq( ini, GF_BGL_FRAME3_S, GF_BGL_CENTER_Y_SET, 80 );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_BAG );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_BAG );
}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BagBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_BAG, ini );
}

//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BagBgGraphicSet( BAG_WORK * wk )
{
	wk->gra_h = ArchiveDataHandleOpen( ARC_BAG_GRA, HEAPID_BAG );

	ArcUtil_BgCharSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg_NCGR, wk->bgl, GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_BAG );
	ArcUtil_ScrnSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg1_NSCR, wk->bgl, GF_BGL_FRAME1_M, 0, 0, 0, HEAPID_BAG );
	ArcUtil_ScrnSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg0_NSCR, wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_BAG );
	ArcUtil_PalSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg_NCLR, PALTYPE_MAIN_BG, 0, 0, HEAPID_BAG );

	// アイコンパレット
	ArcUtil_PalSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_pocketlist_NCLR, PALTYPE_MAIN_BG, 16*13*2, 32, HEAPID_BAG );

	TalkFontPaletteLoad( PALTYPE_MAIN_BG, TALK_FONT_PAL * 32, HEAPID_BAG );

	// メニューウィンドウセット
	MenuWinGraphicSet( wk->bgl, GF_BGL_FRAME0_M, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_BAG );
	// 会話ウィンドウセット
	TalkWinGraphicSet(
		wk->bgl, GF_BGL_FRAME0_M, TALK_WIN_CGX_NUM,
		TALKWIN_PAL, CONFIG_GetWindowType(wk->cfg), HEAPID_BAG );

	ArcUtil_BgCharSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg_s_NCGR, wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_BAG );
	ArcUtil_PalSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg_s_NCLR, PALTYPE_SUB_BG, 0, 0, HEAPID_BAG );
	ArcUtil_ScrnSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_bg_s0_NSCR,
		wk->bgl, GF_BGL_FRAME1_S, 0, 0, 0, HEAPID_BAG );

	ArcUtil_BgCharSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_wheel_NCGR, wk->bgl, GF_BGL_FRAME3_S, 0, 0, 0, HEAPID_BAG );
	ArcUtil_ScrnSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_wheel_NSCR,
		wk->bgl, GF_BGL_FRAME3_S, 0, 0, 0, HEAPID_BAG );

	// ボタン
	ArcUtil_BgCharSet(
		ARC_BAG_GRA,NARC_bag_gra_bag_button2_NCGR,wk->bgl,GF_BGL_FRAME0_S,0,0,0,HEAPID_BAG );
	ArcUtil_PalSet(
		ARC_BAG_GRA, NARC_bag_gra_bag_button_NCLR, PALTYPE_SUB_BG, 16*2*2, 0x20*2, HEAPID_BAG );
}

//--------------------------------------------------------------------------------------------
/**
 * メッセージ関連作成
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MsgManCreate( BAG_WORK * wk )
{
	// メッセージマネージャ作成
	wk->msg_man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_bag_dat, HEAPID_BAG );
	// 8x8フォント作成
	wk->num_font = NUMFONT_Create( FBMP_COL_BLACK, FBMP_COL_BLK_SDW, FBMP_COL_NULL, HEAPID_BAG );

	wk->wset = WORDSET_Create( HEAPID_BAG );

	wk->item_man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_itemname_dat, HEAPID_BAG );
	wk->waza_man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wazaname_dat, HEAPID_BAG );

	// メッセージ展開用バッファ
	wk->expb = STRBUF_Create( BAG_TMPMSG_SIZ, HEAPID_BAG );
}

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウ設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void BagWindowSet(void)
{
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2_SetWnd0Position( 0, 255, 0, 192 );

	GXS_SetVisibleWnd( GX_WNDMASK_W0 );
	G2S_SetWnd0InsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2S_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
	G2S_SetWnd0Position( 0, 255, 0, 192 );
}
*/

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウエフェクト
 *
 * @param	none
 *
 * @return	none
 *
 * @li	HBlank中の処理
 */
//--------------------------------------------------------------------------------------------
/*
static void BagInWipeEff(void * work)
{
	s32	v_cnt = GX_GetVCount();

	if( WipeCount < WIPE_COUNT_M ){
		G2_SetWnd0Position( 0, WipeCount, 0, 192 );
		if( v_cnt < WipeCount ){
			G2_SetWndOutsidePlane( WIPE_MASK, 1 );
		}else{
			G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
		}
	}else if( WipeCount <= WIPE_COUNT_S ){
		u32	w_cnt = WipeCount - WIPE_COUNT_M;

		G2S_SetWnd0Position( 0, w_cnt, 0, 192 );
		if( v_cnt <= w_cnt ){
			G2S_SetWndOutsidePlane( WIPE_MASK, 1 );
		}else{
			G2S_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, 1 );
		}
	}

	if( v_cnt == VCOUNT_MAX && WipeCount <= WIPE_COUNT_S ){
		G2_SetWndOutsidePlane( WIPE_MASK, 1 );
		if( WipeCount > WIPE_COUNT_M ){
			G2S_SetWndOutsidePlane( WIPE_MASK, 1 );
		}
		WipeCount += WIPE_SPEED;
	}
}
*/

//--------------------------------------------------------------------------------------------
/**
 * ウィンドウエフェクト終了
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void WipeEffOff(void)
{
	WipeCount = 0;
	sys_HBlankIntrStop();				//HBlank割り込み停止
	GX_SetVisibleWnd( GX_WNDMASK_NONE );
	GXS_SetVisibleWnd( GX_WNDMASK_NONE );
}
*/




//--------------------------------------------------------------------------------------------
/**
 * ポケット数取得
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PocketDataInit( BAG_WORK * wk )
{
	u8	i;

	wk->p_max = 0;
	for( i=0; i<BAG_POKE_MAX; i++ ){
		if( wk->dat->p_data[i].item != 0 ){
			wk->p_max++;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 現在のポケットの指定位置のアイテムを取得
 *
 * @param	wk		バッグ画面のワーク
 * @param	pos		位置
 * @param	id		取得ID
 *
 * @return	指定位置のアイテム
 *
 * @li	id = POS_GET_ID : アイテム番号
 * @li	id = POS_GET_NUM : 所持数
 */
//--------------------------------------------------------------------------------------------
u16 Bag_PosItemGet( BAG_WORK * wk, u16 pos, u16 id )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	if( id == POS_GET_ID ){
		return pocket->item[pos].id;
	}
	return pocket->item[pos].no;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリストデータ作成
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BAG_GetItemName( MSGDATA_MANAGER * man, STRBUF * buf, u16 item, u32 heap_id )
{
	MSGMAN_GetString( man, item, buf );
}

static void BAG_GetItemWazaName( MSGDATA_MANAGER * man, STRBUF * buf, u16 item, u32 heap_id )
{
	MSGMAN_GetString( man, GetWazaNoItem(item), buf );
}


static void BAG_CursorInit( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	u16	i, pid;

	wk->dat->p_now = 0;

	pocket = wk->dat->p_data;

	if( wk->dat->bag_cursor == NULL ){
		for( i=0; i<BAG_POKE_MAX; i++ ){
			if( pocket[i].item == NULL ){ break; }
			pocket[i].cur = 1;
			pocket[i].scr = 0;
		}
		return;
	}

	for( i=0; i<BAG_POKE_MAX; i++ ){
		u8	pos, scr;
		if( pocket[i].item == NULL ){ break; }
		MyItem_FieldBagCursorGet( wk->dat->bag_cursor, pocket[i].type, &pos, &scr );
		if( pos == 0 ){ pos = 1; }
		pocket[i].cur = pos;
		pocket[i].scr = scr;
	}

	pid = MyItem_FieldBagPocketGet( wk->dat->bag_cursor );

	for( i=0; i<BAG_POKE_MAX; i++ ){
		if( pocket[i].item == NULL ){ break; }
		if( pocket[i].type == pid ){
			wk->dat->p_now = (u8)i;
		}
	}
}

static void BAG_CursorSave( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	u32	i;

	if( wk->dat->bag_cursor == NULL ){ return; }

	pocket = wk->dat->p_data;

	for( i=0; i<BAG_POKE_MAX; i++ ){
		if( pocket[i].item == NULL ){ break; }
		MyItem_FieldBagCursorSet(
			wk->dat->bag_cursor, pocket[i].type, (u8)pocket[i].cur, (u8)pocket[i].scr );
	}

	MyItem_FieldBagPocketSet( wk->dat->bag_cursor, pocket[wk->dat->p_now].type );
}



static void ItemListDataMake( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	u32	i;
	
	pocket = &wk->dat->p_data[wk->dat->p_now];

	wk->ld = BMP_MENULIST_Create( PocketMax[pocket->type]+3, HEAPID_BAG );

	BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_RABEL );
	if( pocket->type == BAG_POKE_WAZA ){
		for( i=0; i<PocketMax[pocket->type]; i++ ){
			if( pocket->item[i].id == 0 || pocket->item[i].no == 0 ){
				break;
			}
			BAG_GetItemWazaName( wk->waza_man, wk->itemname[i], pocket->item[i].id, HEAPID_BAG );
			BMP_MENULIST_AddString( wk->ld, wk->itemname[i], i );
		}
		BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_CANCEL );
		BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_RABEL );
		pocket->max = i+3;
	}else{
		for( i=0; i<PocketMax[pocket->type]; i++ ){
			if( pocket->item[i].id == 0 || pocket->item[i].no == 0 ){
				break;
			}
			BAG_GetItemName( wk->item_man, wk->itemname[i], pocket->item[i].id, HEAPID_BAG );
			BMP_MENULIST_AddString( wk->ld, wk->itemname[i], i );
		}
		if( wk->dat->mode != BAG_MODE_MIX_SIO ){
			if( pocket->type == BAG_POKE_NUTS ){
				BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_CANCEL );
			}else{
				BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_041, BMPLIST_CANCEL );
			}
			BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_RABEL );
			pocket->max = i+3;
		}else{
			BMP_MENULIST_AddArchiveString( wk->ld, wk->msg_man, msg_bag_033, BMPLIST_RABEL );
			pocket->max = i+2;
		}
	}
}

static void ItemListStrAlloc( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BAG_LARGE_POKE_MAX; i++ ){
		wk->itemname[i] = STRBUF_Create( BUFLEN_ITEM_NAME, HEAPID_BAG );
	}
}

static void ItemListStrFree( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BAG_LARGE_POKE_MAX; i++ ){
		STRBUF_Delete( wk->itemname[i] );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * スクロールカウンタ、カーソル位置の修正
 *
 * @param	scr			スクロールカウンタ
 * @param	pos			カーソル位置
 * @oaram	buf_max		bufに入っているデータの数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemListParamReset( u16 * scr, u16 * pos, u8 buf_max )
{
	u8	pos_max;

	buf_max -= 1;	// 最後のラベル分をマイナス

	if( buf_max > 8 ){
		pos_max = 8 - 1;
	}else{
		pos_max = buf_max-1;
	}

	if( *scr != 0 ){
		if( *scr + pos_max > buf_max-1 ){
			*scr = buf_max-1 - pos_max;
		}
	}

	if( *scr + *pos >= buf_max-1 ){
		*pos = buf_max-1 - *scr;
	}
}

static void ItemListParamResetAll( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<wk->p_max; i++ ){
		ItemListParamReset(
			&wk->dat->p_data[i].scr, &wk->dat->p_data[i].cur, wk->dat->p_data[i].max );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * BMPリストのカーソル位置の修正
 *
 * @param	scr			スクロールカウンタ
 * @param	pos			カーソル位置
 * @oaram	buf_max		bufに入っているデータの数
 * @param	list_max	BMPリストの表示最大数
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemListCurPosReset( u16 * scr, u16 * pos, u8 buf_max, u8 list_max )
{
	u8 pos_max;
	u8	i;

	buf_max -= 1;	// 最後のラベル分をマイナス

	if( buf_max > 8 ){
		pos_max = 8 - 1;
	}else{
		pos_max = buf_max-1;
	}

/*
	if( buf_max > list_max ){
		pos_max = list_max;
	}else{
		pos_max = buf_max;
	}

	if( ( list_max & 1 ) != 0 ){
		if( !( *pos >= ( list_max >> 1 ) ) ){ return; }
		for( i=0; i<*pos-(list_max>>1); i++ ){
			if( *scr+pos_max == buf_max ){ break; }
			*pos -= 1;
			*scr += 1;
		}
	}else{
		if( !( *pos >= ( list_max >> 1 ) + 1 ) ){ return; }

		for( i=0; i<=*pos-(list_max>>1); i++ ){
			if( *scr+pos_max == buf_max ){ break; }
			*pos -= 1;
			*scr += 1;
		}
	}
*/
	if( !( *pos >= ( list_max >> 1 ) + 2 ) ){ return; }

	for( i=0; i<=*pos-(list_max>>1)-2; i++ ){
		if( *scr+pos_max == buf_max-1 ){ break; }
		*pos -= 1;
		*scr += 1;
	}
}

static void ItemListCurPosResetAll( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<wk->p_max; i++ ){
		ItemListCurPosReset(
			&wk->dat->p_data[i].scr, &wk->dat->p_data[i].cur, wk->dat->p_data[i].max, 9 );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * アイテムリストセット
 *
 * @param	wk		バッグ画面のワーク
 * @param	scr		スクロール位置
 * @param	pos		カーソル位置
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemListSet( BAG_WORK * wk, u16 scr, u16 pos )
{
	BMPLIST_HEADER	list_h;

	list_h = BagItemList;
	list_h.list  = wk->ld;
	list_h.win   = &wk->win[WIN_LIST];
	list_h.count = wk->dat->p_data[wk->dat->p_now].max;
	list_h.work  = (void *)wk;
	if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_WAZA ||
		wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_NUTS ){
		list_h.data_x = LIST_PX_WAZAMACHINE;
	}else{
		list_h.data_x = LIST_PX_NORMAL;
	}
	wk->lw = BmpListSet( &list_h, scr, pos, HEAPID_BAG );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_LIST] );
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリストコールバック関数（カーソル移動ごと）
 *
 * @param	work	BMPリストで設定したワーク
 * @param	param	BMPリストのパラメータ
 * @param	mode	初期化時 = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CB_ItemListMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	BAG_WORK * wk = (BAG_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );

	if( mode != 1 ){
		switch( wk->se_type ){
		case 0:
			Snd_SePlay( BAG_SE_LIST_MOVE1 );
			break;
		case 1:
			Snd_SePlay( BAG_SE_LIST_MOVE2 );
			break;
		default:
			Snd_SePlay( BAG_SE_LIST_MOVE3 );
		}
		wk->se_type = ( wk->se_type + 1 ) % 3;

		if( wk->wheel_flg == 0 || CATS_ObjectAnimeActiveCheckCap(wk->cap[ACT_BAG]) == FALSE ){
			CATS_ObjectAnimeFrameSetCap( wk->cap[ACT_BAG], 0 );
			CATS_ObjectAnimeSeqSetCap(
				wk->cap[ACT_BAG], BAG_POKE_MAX+wk->dat->p_data[wk->dat->p_now].type );
		}
	}

	if( wk->irekae_flg == 1 ){ return; }
	
	GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], 0 );

	if( param != BMPLIST_CANCEL ){
		POCKET_DATA * pocket;

		pocket = &wk->dat->p_data[wk->dat->p_now];
		Bag_ItemInfoPut( wk, pocket->item[param].id );
		BagItemIconChange( wk, pocket->item[param].id );

	}else{
		Bag_ItemInfoPut( wk, 0xffff );
		BagItemIconChange( wk, ITEM_RETURN_ID );
	}

	if( wk->info_put == 0 ){
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリストコールバック関数（一列表示ごと）
 *
 * @param	work	BMPリストで設定したワーク
 * @param	index	BMPリストが使用しているウィンドウインデックス
 * @param	param	BMPリストのパラメータ
 * @param	y		Y座標
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CB_ItemListWrite( BMPLIST_WORK * work, u32 param, u8 y )
{
	BAG_WORK * wk = (BAG_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	if( wk->irekae_flg == 1 && wk->irekae_param == param ){
		BmpListTmpColorChange( work, BAGCOL_GREY_F, FBMP_COL_NULL, BAGCOL_GREY_S );
	}else{
		BmpListTmpColorChange( work, FBMP_COL_BLACK, FBMP_COL_NULL, FBMP_COL_BLK_SDW );
	}

	if( pocket->type == BAG_POKE_EVENT ){
		if( param != BMPLIST_RABEL && param != BMPLIST_CANCEL ){
			if( MyItem_CnvButtonItemGet( wk->myitem ) == pocket->item[param].id ){
				BagBmp_CnvButtonIconPut( wk, y );
			}
		}
	}else if( pocket->type == BAG_POKE_WAZA ){
		if( param == BMPLIST_CANCEL ){
			BagBmp_WazaPageToziruPut( wk, y );
		}else if( param != BMPLIST_RABEL ){
			BagBmp_WazaMachineNoPut( wk, &pocket->item[param], y );
		}
	}else if( pocket->type == BAG_POKE_NUTS ){
		if( param == BMPLIST_CANCEL ){
			BagBmp_WazaPageToziruPut( wk, y );
		}else if( param != BMPLIST_RABEL ){
			BagBmp_NutsNoPut( wk, &pocket->item[param], y );
		}
	}else{
		if( param != BMPLIST_RABEL && param != BMPLIST_CANCEL ){
			if( wk->irekae_flg == 1 && wk->irekae_param == param ){
				Bag_ItemListNumPut( wk, pocket->item[param].no, y, BAGCOL_N_GREY );
			}else{
				Bag_ItemListNumPut( wk, pocket->item[param].no, y, BAGCOL_N_BLACK );
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * アイテムリスト破棄
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemListExit( BAG_WORK * wk )
{
	BmpListExit(
		wk->lw, &wk->dat->p_data[wk->dat->p_now].scr, &wk->dat->p_data[wk->dat->p_now].cur );
	BMP_MENULIST_Delete( wk->ld );
	wk->lw = NULL;
}


//--------------------------------------------------------------------------------------------
/**
 * メインコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	シーケンス
 */
//--------------------------------------------------------------------------------------------
static int MainSeqFunc( BAG_WORK * wk )
{
	PokeArrowMove( wk );

	if( BAG_WheelListMove( wk ) == TRUE ){
		return SEQ_MAIN;
	}

	// ポケット選択（十字キー）
	if( PocketControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// ポケット選択（サブ画面ボタン）
	if( PocketButtonControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// アイテム選択
	{
		u8	ret = ItemListControl( wk );

		if( ret == LIST_SEL_ITEM ){			// 選択された
			BagObj_CursorPalChg( wk, 2 );
			GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], FBMP_COL_NULL );
			GF_BGL_BmpWinOff( &wk->win[WIN_INFO] );
			ItemMenuMake( wk );
			if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_WAZA ){
				BAG_IconPutScrnChg( wk, 1 );
			}
			return SEQ_MENU;
		}else if( ret == LIST_SEL_CHANGE ){	// 入れ替え
			ItemChangeInit( wk );
			return SEQ_IREKAE;
		}else if( ret == LIST_SEL_CANCEL ){	// キャンセル
			return SEQ_OUT;
		}
	}
	return SEQ_MAIN;
}


//--------------------------------------------------------------------------------------------
/**
 * アイテムリストコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"LIST_SEL_NONE = 何も選択されていない"
 * @retval	"LIST_SEL_ITEM = アイテムが選択された"
 * @retval	"LIST_SEL_CANCEL = キャンセル"
 */
//--------------------------------------------------------------------------------------------
static u8 ItemListControl( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	u32	ret;
	u16	scr, cur;

	pocket = &wk->dat->p_data[wk->dat->p_now];

	BmpListPosGet( wk->lw, &pocket->scr, &pocket->cur );

	if( sys.trg & PAD_BUTTON_SELECT ){
		if( ItemChangeChack( wk ) == TRUE ){
			Snd_SePlay( BAG_SE_ITEM_SELECT );
			return LIST_SEL_CHANGE;
		}
	}

	ret = BmpListMain( wk->lw );
	BmpListPosGet( wk->lw, &scr, &cur );

	if( pocket->cur != cur ){
		CATS_ObjectPosSetCap(
			wk->cap[ACT_LIST_SEL_CURSOR], CURSOR_ACT_PX, CURSOR_ACT_PY + (cur-1) * 16 );
	}
	pocket->scr = scr;
	pocket->cur = cur;

	// 下画面の決定ボタン
	if( ret == BMPLIST_NULL ){
		if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
			ret = BmpListPosParamGet( wk->lw, scr+cur );
			wk->enter_anm_flg = 1;
		}
	}

	switch( ret ){
	case BMPLIST_NULL:
		{
			u8	mv = BmpListMoveSiteGet( wk->lw );

			if( mv == BMPLIST_MOVE_UP ){
				BAG_WheelMoveKey( wk, WHEEL_ROT_LIST );
			}else if( mv == BMPLIST_MOVE_DOWN ){
				BAG_WheelMoveKey( wk, -WHEEL_ROT_LIST );
			}
		}
		break;
	case BMPLIST_CANCEL:
		if( wk->dat->mode == BAG_MODE_MIX_SIO ){
			return LIST_SEL_NONE;
		}
		Snd_SePlay( BAG_SE_ITEM_CANCEL );
		wk->dat->ret_item = 0;				// 選択アイテム
		wk->dat->ret_mode = BAG_RET_CANCEL;	// 終了モード
		APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
		return LIST_SEL_CANCEL;
	default:
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		wk->dat->ret_item = (u16)pocket->item[ret].id;	// 選択アイテム
		wk->sel_max   = (u16)pocket->item[ret].no;		// 所持数
		return LIST_SEL_ITEM;
	}

	return LIST_SEL_NONE;
}


//--------------------------------------------------------------------------------------------
/**
 * ポケットカーソル移動のためのデータを作成
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 *
 * @li	wk->p_icon_gx = 一番左のポケットアイコンのX座標
 * @li	wk->p_icon_sx = ポケットアイコン同士の間隔
 */
//--------------------------------------------------------------------------------------------
static void PocketIconXmake( BAG_WORK * wk )
{
	wk->p_icon_gx =
		P_ICON_DEF_PX + ( P_ICON_DEF_SX - ( P_ICON_SIZ_X * wk->p_max ) ) / ( wk->p_max + 1 );
	wk->p_icon_sx = P_ICON_SIZ_X + wk->p_icon_gx - P_ICON_DEF_PX;
}



//--------------------------------------------------------------------------------------------
/**
 * ポケットコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = キー入力あり"
 * @retval	"FALSE = キー入力なし"
 */
//--------------------------------------------------------------------------------------------
static u8 PocketControl( BAG_WORK * wk )
{
	if( sys.repeat & PAD_KEY_LEFT ){
		if( wk->p_max == 1 ){ return FALSE; }
		Snd_SePlay( BAG_SE_POCKET_MOVE );
		if( wk->dat->p_now != 0 ){
			wk->page_work.next = wk->dat->p_now - 1;
			wk->p_next = wk->dat->p_now - 1;
		}else{
			wk->page_work.next = wk->p_max - 1;
			wk->p_next = wk->p_max - 1;
		}
		BagPocketCursorMoveInit( wk );

		wk->page_work.move = 0;
		PocketChangeInitKey( wk );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		return TRUE;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		if( wk->p_max == 1 ){ return FALSE; }
		Snd_SePlay( BAG_SE_POCKET_MOVE );
		if( wk->dat->p_now+1 < wk->p_max ){
			wk->page_work.next = wk->dat->p_now + 1;
			wk->p_next = wk->dat->p_now + 1;
		}else{
			wk->page_work.next = 0;
			wk->p_next = 0;
		}
		BagPocketCursorMoveInit( wk );

		wk->page_work.move = 1;
		PocketChangeInitKey( wk );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケット切り替え共通初期処理
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PocketChangeInitKey( BAG_WORK * wk )
{
	PocketChangeInit( wk );
	wk->page_work.tp_seq  = 3;
	wk->page_work.tp_mode = 0;
}

static void PocketChangeInitTp( BAG_WORK * wk )
{
	if( wk->page_work.move != 2 ){
		PocketChangeInit( wk );
	}else{
		wk->page_work.cur_seq = 2;
	}
	wk->page_work.tp_seq  = 0;
	wk->page_work.tp_mode = 1;
}

static void PocketChangeInit( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk = &wk->page_work;

	pwk->cur_seq = 0;
	pwk->cur_cnt = 0;
	pwk->tp_cnt  = 0;
	pwk->tp_chg  = 0;
	pwk->tp_push = 0;

	ItemListExit( wk );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_LIST], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], 0 );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_LIST] );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
	CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CURSOR ], ACT_OFF );
	CATS_ObjectEnableCap( wk->cap[ ACT_ITEMICON ], ACT_OFF );

	Bag_PocketIconPut( wk, wk->dat->p_now, 0 );

	SubPokeButtonBgChg( wk, wk->dat->p_now, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ポケット切り替え処理
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 切り替え終了"
 * @retval	"FALSE = 切り替え中"
 */
//--------------------------------------------------------------------------------------------
static u8 PocketChange( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk;
	int	tp_ret;
	u8	cur_ret;
	u8	anm_ret;

	pwk = &wk->page_work;

	// タッチパネルに触っているか
	if( GF_TP_GetCont() == FALSE ){	// 触れていない
		pwk->tp_push = 1;
	}

	// タッチ位置の確認
	tp_ret = SubPokeButtonEndCheck( wk );
	if( tp_ret == RECT_HIT_NONE || tp_ret != pwk->next ){
		pwk->tp_chg = 1;
	}

	// 十字キーチェック
	if( PocketChangeReset( wk ) == FALSE ){
		// タッチパネルチェック
		if( pwk->tp_push == 1 && tp_ret != RECT_HIT_NONE ){

			wk->dat->p_now = pwk->next;

			if( pwk->next > (u8)tp_ret ){
				pwk->move    = 0;
				pwk->cur_seq = 0;
				SubPokeButtonBgChg( wk, pwk->next, 0 );
				Bag_PocketIconPut( wk, pwk->next, 0 );
			}else if( pwk->next < (u8)tp_ret ){
				pwk->move    = 1;
				pwk->cur_seq = 0;
				SubPokeButtonBgChg( wk, pwk->next, 0 );
				Bag_PocketIconPut( wk, pwk->next, 0 );
			}else{
				pwk->move= 2;
			}

			pwk->next = (u8)tp_ret;
			pwk->tp_chg  = 0;
			pwk->tp_push = 0;
			pwk->tp_seq  = 0;

			wk->p_next = (u8)tp_ret;
			BagPocketCursorMoveInit( wk );
		}
	}

	// エフェクト
	cur_ret = PocketCursorMove( wk );
	anm_ret = ButtonAnmTask( wk );

	BagPocketCursorMoveMain( wk );

	if( cur_ret == TRUE && anm_ret == TRUE && pwk->tp_chg == 1 &&
		BagPocketCursorMoveCheck( wk ) == TRUE ){

		if( pwk->tp_mode == 1 ){
			SubPokeButtonBgChg( wk, pwk->next, 1 );
			GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		}
		CATS_ObjectEnableCap( wk->cap[ ACT_ITEMICON ], ACT_ON );
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケット再切り替えチェック
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 再切り替え"
 * @retval	"FALSE = なにもしない"
 */
//--------------------------------------------------------------------------------------------
static u8 PocketChangeReset( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk = &wk->page_work;

	if( sys.trg & PAD_KEY_LEFT ){
		if( wk->p_max == 1 ){ return TRUE; }
		Snd_SePlay( BAG_SE_POCKET_MOVE );
		CATS_ObjectAnimeSeqSetCap( wk->cap[ACT_BAG], wk->dat->p_data[pwk->next].type );
		SubPokeButtonBgChg( wk, pwk->next, 0 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );

		wk->dat->p_now = pwk->next;

		if( pwk->next != 0 ){
			pwk->next = pwk->next - 1;
			wk->p_next = wk->p_next - 1;
		}else{
			pwk->next = wk->p_max - 1;
			wk->p_next = wk->p_max - 1;
		}

		pwk->cur_seq = 0;
		pwk->move    = 0;

		pwk->tp_push = 1;
		pwk->tp_chg  = 1;
		pwk->tp_mode = 0;

		if( pwk->tp_seq != 3 ){ pwk->tp_seq = 4; }


		BagPocketCursorMoveInit( wk );

		return TRUE;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		if( wk->p_max == 1 ){ return TRUE; }
		Snd_SePlay( BAG_SE_POCKET_MOVE );
		CATS_ObjectAnimeSeqSetCap( wk->cap[ACT_BAG], wk->dat->p_data[pwk->next].type );
		SubPokeButtonBgChg( wk, pwk->next, 0 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );

		wk->dat->p_now = pwk->next;

		if( pwk->next+1 < wk->p_max ){
			pwk->next = pwk->next + 1;
			wk->p_next = wk->p_next + 1;
		}else{
			pwk->next = 0;
			wk->p_next = 0;
		}

		pwk->cur_seq = 0;
		pwk->move    = 1;

		pwk->tp_push = 1;
		pwk->tp_chg  = 1;
		pwk->tp_mode = 0;

		if( pwk->tp_seq != 3 ){ pwk->tp_seq = 4; }

		BagPocketCursorMoveInit( wk );

		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケットカーソル移動
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 移動完了"
 * @retval	"FALSE = 移動中"
 */
//--------------------------------------------------------------------------------------------
static u8 PocketCursorMove( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk = &wk->page_work;

	switch( pwk->cur_seq ){
	case 0:		// 初期化
		pwk->cur_cnt = 0;
//		PocketMvTblMake( wk );
		pwk->cur_seq++;
		break;

	case 1:		// 移動
		if( pwk->cur_cnt < 8 ){
			pwk->cur_cnt++;
			Bag_PocketNamePut( wk );
		}else{
			if( wk->lw != NULL ){
				BmpListExit(
					wk->lw,
					&wk->dat->p_data[wk->dat->p_now].scr,
					&wk->dat->p_data[wk->dat->p_now].cur );
				BMP_MENULIST_Delete( wk->ld );
			}
			wk->dat->p_now = pwk->next;

			CATS_ObjectAnimeSeqSetCap( wk->cap[ACT_BAG], wk->dat->p_data[wk->dat->p_now].type );

			Bag_PocketIconPutAll( wk );		// ボタン連打でバグるので追加
			Bag_PocketIconPut( wk, wk->dat->p_now, 1 );

			ItemListDataMake( wk );
/*
			ItemListCurPosReset(
				&wk->dat->p_data[wk->dat->p_now].scr,
				&wk->dat->p_data[wk->dat->p_now].cur,
				wk->dat->p_data[wk->dat->p_now].max, 9 );
*/

			ItemListParamReset(
				&wk->dat->p_data[wk->dat->p_now].scr,
				&wk->dat->p_data[wk->dat->p_now].cur,
				wk->dat->p_data[wk->dat->p_now].max );
			ItemListCurPosReset(
				&wk->dat->p_data[wk->dat->p_now].scr,
				&wk->dat->p_data[wk->dat->p_now].cur,
				wk->dat->p_data[wk->dat->p_now].max, 9 );

			ItemListSet(
				wk, wk->dat->p_data[wk->dat->p_now].scr, wk->dat->p_data[wk->dat->p_now].cur );
			CATS_ObjectPosSetCap(
				wk->cap[ACT_LIST_SEL_CURSOR],
				CURSOR_ACT_PX, CURSOR_ACT_PY + (wk->dat->p_data[wk->dat->p_now].cur-1) * 16 );
			CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CURSOR ], ACT_ON );

			pwk->cur_seq++;
			return TRUE;
		}
		break;

	case 2:		// 終了
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ボタンコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 押された"
 * @retval	"FALSE = 押されていない"
 */
//--------------------------------------------------------------------------------------------
static u8 PocketButtonControl( BAG_WORK * wk )
{
	int	ret = SubPokeButtonCheck( wk );

	if( ret == RECT_HIT_NONE ){ return FALSE; }
	if( wk->p_max == 1 ){ return FALSE; }

	if( wk->dat->p_now == (u8)ret ){
		wk->page_work.move = 2;
	}else if( wk->dat->p_now > (u8)ret ){
		wk->page_work.move = 0;
	}else{
		wk->page_work.move = 1;
	}

	wk->page_work.next = (u8)ret;

	wk->p_next = (u8)ret;
	BagPocketCursorMoveInit( wk ); 

	PocketChangeInitTp( wk );

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * タッチパネルのボタン押し判定
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"RECT_HIT_NONE = 押されていない"
 * @retval	"RECT_HIT_NONE != 押したボタン番号"
 */
//--------------------------------------------------------------------------------------------
static int SubPokeButtonCheck( BAG_WORK * wk )
{
	int	ret = GF_TP_RectHitTrg( PokeButtonPos[ wk->p_max ].rect_tbl );
//	int	ret = GF_TP_HitTrg( PokeButtonPos[ wk->p_max ].rect_tbl );

	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}
	}

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * タッチパネルのボタン放し判定
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"RECT_HIT_NONE = 放した"
 * @retval	"RECT_HIT_NONE != 押されている"
 */
//--------------------------------------------------------------------------------------------
static int SubPokeButtonEndCheck( BAG_WORK * wk )
{
	int	ret = GF_TP_RectHitCont( PokeButtonPos[ wk->p_max ].rect_tbl );
//	int	ret = GF_TP_HitCont( PokeButtonPos[ wk->p_max ].rect_tbl );

	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return RECT_HIT_NONE;
		}
	}

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * ボタンアニメ
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u8 ButtonAnmTask( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk = &wk->page_work;

	switch( pwk->tp_seq ){
	case 0:
		pwk->tp_cnt  = 0;
		pwk->tp_mode = 1;
		pwk->tp_button = pwk->next;
		pwk->tp_seq++;
		break;
	case 1:
		if( pwk->tp_cnt != 3 ){ break; }

		Snd_SePlay( BAG_SE_SUB_BUTTON );
		// ボタンをへこませる
		SubPokeButtonBgChg( wk, pwk->tp_button, 2 );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		// エフェクトセルアクター用意
		BagObj_SubButtonEffInit(
			wk,
			PokeButtonPos[wk->p_max].write_tbl[pwk->tp_button*2] * 8 + 20,
			PokeButtonPos[wk->p_max].write_tbl[pwk->tp_button*2+1] * 8 + 20 );
		pwk->tp_seq++;
		break;
	case 2:
		if( pwk->tp_cnt != 7 ){ break; }
		pwk->tp_seq++;
		return TRUE;

	case 3:
		return TRUE;

	case 4:
		pwk->tp_seq = 3;
		return TRUE;
	}

	pwk->tp_cnt++;

	return FALSE;
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
static void SubPokeButtonBgChg( BAG_WORK * wk, u8 num, u8 anm )
{
	u16 * buf;
	const u8 * pos;
	u16	start;
	u8	type;
	u8	i, j;
	
	buf   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_S );
	pos   = &PokeButtonPos[wk->p_max].write_tbl[num*2];
	type  = wk->dat->p_data[num].type;
	start = (type/2)*BUTTON_CGX_YNEXT + (type&1)*BUTTON_CGX_XNEXT
				+ BUTTON_CGX_START + anm*BUTTON_CGX_SIZE;

	for( i=0; i<BUTTON_CGX_SIZE; i++ ){
		for( j=0; j<BUTTON_CGX_SIZE; j++ ){
			buf[ (i+pos[1])*32 + j+pos[0] ] = start+i*BUTTON_CGX_WIDE+j + (BUTTON_PAL_NUM<<12);
		}
	}
}


static void SubEnterButtonBgChg( BAG_WORK * wk, u8 anm )
{
	u16 * buf;
	const u8 * pos;
	u16	start;
	u8	type;
	u8	i, j;
	
	buf   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_S );
	start = SUB_ENTER_CGX + SUB_ENTER_SX * anm;
		
	for( i=0; i<SUB_ENTER_SY; i++ ){
		for( j=0; j<SUB_ENTER_SX; j++ ){
			buf[ (SUB_ENTER_PY+i)*32 + SUB_ENTER_PX+j ] =
				start+i*BUTTON_CGX_WIDE+j + (SUB_ENTER_PAL<<12);
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
}

static void SubEnterButtonAnm( BAG_WORK * wk )
{
	switch( wk->enter_anm_flg ){
	case 0:
		break;
	case 1:
		BagObj_SubButtonEffInit( wk, SUB_ENTER_EFF_X, SUB_ENTER_EFF_Y );
		Snd_SePlay( BAG_SE_SUB_BUTTON );
		SubEnterButtonBgChg( wk, 2 );
//		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
		wk->enter_anm_cnt = 0;
		wk->enter_anm_flg++;
		break;
	case 2:
		if( wk->enter_anm_cnt == 3 ){
			SubEnterButtonBgChg( wk, 1 );
//			GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
			wk->enter_anm_flg++;
			wk->enter_anm_cnt = 0;
		}else{
			wk->enter_anm_cnt++;
		}
		break;
	case 3:
		if( wk->enter_anm_cnt == 2 ){
			SubEnterButtonBgChg( wk, 0 );
//			GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
			wk->enter_anm_flg = 0;
			wk->enter_anm_cnt = 0;
		}else{
			wk->enter_anm_cnt++;
		}
	}
}

static void SubPokeButtonBgInit( BAG_WORK * wk )
{
	u8	i;

	SubEnterButtonBgChg( wk, 0 );

	if( wk->p_max != 1 ){
		for( i=0; i<wk->p_max; i++ ){
			SubPokeButtonBgChg( wk, i, 0 );
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME0_S );
}


//--------------------------------------------------------------------------------------------
/**
 * ポケット切り替え矢印動作
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeArrowMove( BAG_WORK * wk )
{
	if( wk->arrow_cnt == 0 ){
//		VecFx32 vec;
		s16	x, y;

		switch( wk->arrow_mv ){
		case 0:
		case 1:
/*
			vec = *(CLACT_GetMatrix( wk->act_work[ACT_POKE_ARROW_LEFT] ));
			vec.x -= FX32_ONE; 
			CLACT_SetMatrix( wk->act_work[ACT_POKE_ARROW_LEFT], &vec );
			vec = *(CLACT_GetMatrix( wk->act_work[ACT_POKE_ARROW_RIGHT] ));
			vec.x += FX32_ONE; 
			CLACT_SetMatrix( wk->act_work[ACT_POKE_ARROW_RIGHT], &vec );
*/
			CATS_ObjectPosGetCap( wk->cap[ACT_POKE_ARROW_LEFT], &x, &y );
			x -= 1;
			CATS_ObjectPosSetCap( wk->cap[ACT_POKE_ARROW_LEFT], x, y );
			CATS_ObjectPosGetCap( wk->cap[ACT_POKE_ARROW_RIGHT], &x, &y );
			x += 1;
			CATS_ObjectPosSetCap( wk->cap[ACT_POKE_ARROW_RIGHT], x, y );
			break;
		case 2:
		case 3:
			CATS_ObjectPosGetCap( wk->cap[ACT_POKE_ARROW_LEFT], &x, &y );
			x += 1;
			CATS_ObjectPosSetCap( wk->cap[ACT_POKE_ARROW_LEFT], x, y );
			CATS_ObjectPosGetCap( wk->cap[ACT_POKE_ARROW_RIGHT], &x, &y );
			x -= 1;
			CATS_ObjectPosSetCap( wk->cap[ACT_POKE_ARROW_RIGHT], x, y );
			break;
		}

		wk->arrow_mv = ( wk->arrow_mv + 1 ) & 3;
	}

	wk->arrow_cnt = ( wk->arrow_cnt + 1 ) & 3;
}



//--------------------------------------------------------------------------------------------
/**
 * サブ画面の決定ボタンチェック
 */
//--------------------------------------------------------------------------------------------

static BOOL BAG_SubEnterButtonCheck( BAG_WORK * wk )
{
	int	ret = GF_TP_RectHitTrg( EnterButtonRect );
//	int	ret = GF_TP_HitCont( EnterButtonRect );

	if( ret != RECT_HIT_NONE ){
		u16	pat = 0xfffe;

		if( GF_BGL_DotCheck( wk->bgl, GF_BGL_FRAME0_S, sys.tp_x, sys.tp_y, &pat ) == FALSE ){
			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//============================================================================================
//	入れ替え
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 入れ替え可能かをチェック
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 可能"
 * @retval	"FALSE = "不可"
 */
//--------------------------------------------------------------------------------------------
static u8 ItemChangeChack( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	if( BmpListPosParamGet( wk->lw, pocket->scr+pocket->cur ) == BMPLIST_CANCEL ){
		return FALSE;
	}

	if( wk->dat->mode != BAG_MODE_FIELD ){
		return FALSE;
	}

	if( pocket->type == BAG_POKE_NUTS || pocket->type == BAG_POKE_WAZA ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替え初期設定
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
static void ItemChangeInit( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	wk->irekae_flg   = 1;
	wk->irekae_pos   = pocket->scr + pocket->cur;
	wk->irekae_param = BmpListPosParamGet( wk->lw, wk->irekae_pos );

	Bag_ItemChgInfoMsgSet( wk );

	BmpListRewrite( wk->lw );

	ItemChgCursorChg( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替え先選択
 *
 * @param	wk		バッグ画面のワーク
 *
 * @retval	"TRUE = 終了"
 * @retval	"FALSE = 選択中"
 */	
//--------------------------------------------------------------------------------------------
static u8 ItemChangeMain( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	u32	ret;
	u16	scr, cur;

	if( BAG_WheelChgListMove( wk ) == TRUE ){
		return FALSE;
	}

	pocket = &wk->dat->p_data[wk->dat->p_now];

	BmpListPosGet( wk->lw, &pocket->scr, &pocket->cur );

	// 下画面の決定ボタン
	if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
//		ret = BmpMenuMainOutControl( wk->mw, BMPMENU_CNTROL_DECIDE );
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		ItemChangeComp( wk );
		wk->enter_anm_flg = 1;
		return TRUE;
	}

	if( sys.trg & PAD_BUTTON_SELECT ){
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		ItemChangeComp( wk );
		return TRUE;
	}

	ret = BmpListMain( wk->lw );
	BmpListPosGet( wk->lw, &scr, &cur );

	if( pocket->cur != cur ){
		CATS_ObjectPosSetCap(
			wk->cap[ACT_LIST_SEL_CHANGE], CURSOR_ACT_PX, CURSOR_ACT_PY+(cur-1)*16-8 );
	}
	pocket->scr = scr;
	pocket->cur = cur;

	switch( ret ){
	case BMPLIST_NULL:
		{
			u8	mv = BmpListMoveSiteGet( wk->lw );

			if( mv == BMPLIST_MOVE_UP ){
				BAG_WheelMoveKey( wk, WHEEL_ROT_LIST );
			}else if( mv == BMPLIST_MOVE_DOWN ){
				BAG_WheelMoveKey( wk, -WHEEL_ROT_LIST );
			}
		}
		break;
	case BMPLIST_CANCEL:
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		if( sys.trg & PAD_BUTTON_DECIDE ){
			ItemChangeComp( wk );
		}else{
			ItemChangeEnd( wk );
		}
		return TRUE;
	default:
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		ItemChangeComp( wk );
		return LIST_SEL_ITEM;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替え・決定
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
static void ItemChangeComp( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];
	u16	pos = pocket->scr + pocket->cur;

	if( !( wk->irekae_pos == pos || wk->irekae_pos == (pos-1) ) ){
		ItemPutIn( pocket->item, wk->irekae_pos-1, pos-1 );
		BMP_MENULIST_Delete( wk->ld );
		ItemListDataMake( wk );
	}

	ItemChangeEnd( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 入れ替え・キャンセル
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
static void ItemChangeEnd( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	BmpListExit( wk->lw, &pocket->scr, &pocket->cur );
	wk->lw = NULL;

	if( wk->irekae_pos < (pocket->scr+pocket->cur) ){
		pocket->cur -= 1;
	}

	wk->irekae_flg   = 0;
	wk->irekae_pos   = 0;
	wk->irekae_param = 0;

	ItemListSet( wk, pocket->scr, pocket->cur );
	ItemChgCursorChg( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * カーソル切り替え
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemChgCursorChg( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	if( wk->irekae_flg == 0 ){
		CATS_ObjectPosSetCap(
			wk->cap[ACT_LIST_SEL_CURSOR], CURSOR_ACT_PX, CURSOR_ACT_PY + (pocket->cur-1) * 16 );

		CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CURSOR ], ACT_ON );
		CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CHANGE ], ACT_OFF );
		if( wk->p_max != 1 ){
			CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_LEFT ], ACT_ON );
			CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_RIGHT ], ACT_ON );
		}
	}else{
		CATS_ObjectPosSetCap(
			wk->cap[ACT_LIST_SEL_CHANGE], CURSOR_ACT_PX, CURSOR_ACT_PY + (pocket->cur-1) * 16 - 8 );

		CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CURSOR ], ACT_OFF );
		CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CHANGE ], ACT_ON );
		if( wk->p_max != 1 ){
			CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_LEFT ], ACT_OFF );
			CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_RIGHT ], ACT_OFF );
		}
	}
}


//============================================================================================
//============================================================================================
//	メニュー
//============================================================================================
//============================================================================================

static void ItemMenuMake( BAG_WORK * wk )
{
	void * itemdata;
	u32	max;
	u8	pocket;
	u8	tbl[BAG_MENU_MAX];

	itemdata = GetItemArcData( wk->dat->ret_item, ITEM_GET_DATA, HEAPID_BAG );
	max      = 0;
	pocket   = wk->dat->p_data[ wk->dat->p_now ].type;

	// フィールド
	if( wk->dat->mode == BAG_MODE_FIELD ){
		// タグをみる
		if( pocket == BAG_POKE_NUTS ){
			tbl[max] = BAG_MENU_TAGUWOMIRU;
			max++;
		}
		// コロシアム・ユニオンルームでは「みる」のみ
		if( wk->dat->map_mode == MAP_MODE_COLOSSEUM || wk->dat->map_mode == MAP_MODE_UNION ){
			if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_SEAL ){
				tbl[max] = BAG_MENU_MIRU;
				max++;
			}
		}else{
			// つかう
			// おりる
			// みる
			// ひらく
			// うめる
			if( ItemBufParamGet( itemdata, ITEM_PRM_FIELD ) != 0 ){
				if( wk->dat->ret_item == ITEM_ZITENSYA && wk->dat->cycle_flg == 1 ){
					tbl[max] = BAG_MENU_ORIRU;
				}else if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_SEAL ){
					tbl[max] = BAG_MENU_MIRU;
				}else if( wk->dat->ret_item == ITEM_POFINKEESU ){
					tbl[max] = BAG_MENU_HIRAKU;
				}else if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_NUTS &&
						  ItemUse_KinomiTypeCheck( wk->dat->icwk ) == TRUE ){
					tbl[max] = BAG_MENU_UMERU;
				}else{
					tbl[max] = BAG_MENU_TSUKAU;
				}
				max++;
			}
		}
		// もたせる
		// すてる
		if( ItemBufParamGet( itemdata, ITEM_PRM_EVENT ) == 0 ){
			tbl[max] = BAG_MENU_MOTASERU;
			max++;
			if( pocket != BAG_POKE_WAZA ){
				tbl[max] = BAG_MENU_SUTERU;
				max++;
			}
		}
		// とうろく
		// かいじょ
		if( ItemBufParamGet( itemdata, ITEM_PRM_CNV ) != 0 ){
			if( MyItem_CnvButtonItemGet( wk->myitem ) == wk->dat->ret_item ){
				tbl[max] = BAG_MENU_KAIZYO;
			}else{
				tbl[max] = BAG_MENU_TOUROKU;
			}
			max++;
		}
	}else if( wk->dat->mode == BAG_MODE_MIX || wk->dat->mode == BAG_MODE_MIX_SIO ){
		// けってい
		tbl[max] = BAG_MENU_KETTEI;
		max++;
		// タグをみる
		tbl[max] = BAG_MENU_TAGUWOMIRU;
		max++;
	}
	// やめる
	tbl[max] = BAG_MENU_YAMERU;
	max++;

	Bag_ItemMenuSet( wk, tbl, max );

	sys_FreeMemoryEz( itemdata );
}


//--------------------------------------------------------------------------------------------
/**
 * メニューコントロール
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int MenuControl( BAG_WORK * wk )
{
	u32	ret;

	if( BAG_WheelMenuMove( wk ) == TRUE ){
		return SEQ_MENU;
	}

	ret = BmpMenuMain( wk->mw );

	// 下画面の決定ボタン
	if( ret == BMPLIST_NULL ){
		if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
			ret = BmpMenuMainOutControl( wk->mw, BMPMENU_CNTROL_DECIDE );
			wk->enter_anm_flg = 1;
		}
	}

	switch( ret ){
	case BMPMENU_NULL:
		{
			u8	mv = BmpMenuMoveSiteGet( wk->mw );

			if( mv == BMPMENU_MOVE_UP ){
				BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
			}else if( mv == BMPMENU_MOVE_DOWN ){
				BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
			}
		}
		break;

	case BMPMENU_CANCEL:
		BagObj_CursorPalChg( wk, 1 );
		Bag_ItemMenuExit( wk );
		if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_WAZA ){
			BAG_IconPutScrnChg( wk, 0 );
		}
//		SubEnterButtonBgChg( wk, 0 );
		return SEQ_MAIN;

	default:
		{
			pBagFunc	func = (pBagFunc)ret;
			return func( wk );
		}
	}

	return SEQ_MENU;
}



static void BAG_IconPutScrnChg( BAG_WORK * wk, u8 flg )
{
	if( flg == 0 ){
		GF_BGL_ScrWrite(
			wk->bgl, GF_BGL_FRAME1_M, IconPutScrn_Normal,
			ICONPUT_SCRN_PX, ICONPUT_SCRN_PY, ICONPUT_SCRN_SX, ICONPUT_SCRN_SY );
		CATS_ObjectEnableCap( wk->cap[ ACT_ITEMICON ], ACT_ON );
	}else{
		GF_BGL_ScrWrite(
			wk->bgl, GF_BGL_FRAME1_M, IconPutScrn_WMachine,
			ICONPUT_SCRN_PX, ICONPUT_SCRN_PY, ICONPUT_SCRN_SX, ICONPUT_SCRN_SY );
		CATS_ObjectEnableCap( wk->cap[ ACT_ITEMICON ], ACT_OFF );
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );
}




const u32 Bag_MenuParamGet( u32 menu_num )
{
	return MenuParamTbl[menu_num];
}

//============================================================================================
//	メニュー：つかう
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー：つかう
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuUse( BAG_WORK * wk )
{
	ITEMCHECK_FUNC	check;
	s32	id;

	Bag_ItemMenuExit( wk );

	id    = ItemParamGet( wk->dat->ret_item, ITEM_PRM_FIELD, HEAPID_BAG );
	check = (ITEMCHECK_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_CHECKFUNC, id );

	if( check != NULL ){
		u32	ret = check( wk->dat->icwk );
		if( ret != ITEMCHECK_TRUE ){
			BAG_ItemUseErrorMsgSet( wk->myst, wk->expb, wk->dat->ret_item, ret, HEAPID_BAG );
			GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
			BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
			wk->midx = Bag_TalkMsgPrint( wk );
			return SEQ_ITEM_ERR_WAIT;
		}
	}

	return BAG_ItemUse( wk );
}

static int ItemErrWaitSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		if( (sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B)) || sys.tp_trg ){
			BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
			GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
			BagObj_CursorPalChg( wk, 1 );
//			SubEnterButtonBgChg( wk, 0 );
			if( wk->dat->mode == BAG_MODE_KINOMI ){
				return SEQ_KINOMISEL_MAIN;
			}else{
				return SEQ_MAIN;
			}
		}
	}
	return SEQ_ITEM_ERR_WAIT;
}

// バッグ内アイテム使用
static int BAG_ItemUse( BAG_WORK * wk )
{
	POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

	wk->sub_seq  = 0;

	// 技マシン
	if( pocket->type == BAG_POKE_WAZA ){
		wk->use_func = (u32)BAG_ItemUseWazaMachine;
		return SEQ_BAG_ITEMUSE;
	}

	// コインケース、シール入れ、アクセサリー入れ、ポイントカード
	if( BAG_ItemUseMsgSet( wk->dat->sv, wk->expb, wk->dat->ret_item, HEAPID_BAG ) == TRUE ){
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
		wk->midx = Bag_TalkMsgPrint( wk );
		return SEQ_ITEM_ERR_WAIT;
	}

	// 白黒ビードロ、スプレー
	if( BAG_ItemUseMsgNormal( wk, wk->dat->ret_item ) == TRUE ){
		wk->use_func = (u32)BAG_ItemUseMsgNormalFunc;
		return SEQ_BAG_ITEMUSE;
	}

	APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
	wk->dat->ret_mode = BAG_RET_USE;	// 終了モード
	return SEQ_OUT;
}

static int Seq_BagItemUse( BAG_WORK * wk )
{
	seqFunc	func = (seqFunc)wk->use_func;
	return	func(wk);
}

// 技マシン使用
static int BAG_ItemUseWazaMachine( BAG_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:
		{
			u16	waza = GetWazaNoItem( wk->dat->ret_item );
			WORDSET_RegisterWazaName( wk->wset, 0, waza );
			if( HidenWazaCheck( waza ) == TRUE ){
				MSGMAN_GetString( wk->msg_man, msg_bag_064, wk->expb );
			}else{
				MSGMAN_GetString( wk->msg_man, msg_bag_063, wk->expb );
			}
		}
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
		wk->midx    = Bag_TalkMsgPrint( wk );
		wk->sub_seq = 1;
		break;

	case 1:
		if( GF_MSG_PrintEndCheck( wk->midx ) != 0 ){ break; }
		if( (sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B)) || sys.tp_trg ){
			STRBUF * str = MSGMAN_AllocString( wk->msg_man, msg_bag_065 );
			GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
			WORDSET_ExpandStr( wk->wset, wk->expb, str );
			STRBUF_Delete( str );
			wk->midx    = Bag_TalkMsgPrint( wk );
			wk->sub_seq = 2;
		}
		break;

	case 2:
		if( GF_MSG_PrintEndCheck( wk->midx ) != 0 ){ break; }
		Bag_YesNoSelInit( wk );
		wk->sub_seq = 3;
		break;

	case 3:
		{
			u32	ret;

			if( BAG_WheelMenuMove( wk ) == TRUE ){
				break;
			}

			if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
				ret = BmpYesNoSelectMainOutControl(wk->mw, BMPMENU_CNTROL_DECIDE, HEAPID_BAG );
				wk->enter_anm_flg = 1;
			}else{
				ret = BmpYesNoSelectMain( wk->mw, HEAPID_BAG );
			}

			switch( ret ){
			case 0:
				APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
				BAG_IconPutScrnChg( wk, 0 );
				wk->dat->ret_mode = BAG_RET_USE;	// 終了モード
				return SEQ_OUT;

			case BMPMENU_NULL:
				{
					u8	mv = BmpMenuMoveSiteGet( wk->mw );

					if( mv == BMPMENU_MOVE_UP ){
						BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
					}else if( mv == BMPMENU_MOVE_DOWN ){
						BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
					}
				}
				break;

			case BMPMENU_CANCEL:
				BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
				GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
				BagObj_CursorPalChg( wk, 1 );
				BAG_IconPutScrnChg( wk, 0 );
//				SubEnterButtonBgChg( wk, 0 );
				return SEQ_MAIN;
			}
		}
		break;
	}
	return SEQ_BAG_ITEMUSE;
}

// 白黒ビードロ、スプレー
static BOOL BAG_ItemUseMsgNormal( BAG_WORK * wk, u16 item )
{
	STRBUF * str;

	WORDSET_RegisterPlayerName( wk->wset, 0, wk->myst );
	WORDSET_RegisterItemName( wk->wset, 1, item );

	if( item == ITEM_KUROIBIIDORO ){
		str = MSGMAN_AllocString( wk->msg_man, msg_bag_069 );
		BAG_SaveDataVidroSet( wk, VIDRO_BLACK );
		wk->sel_num = 0;
	}else if( item == ITEM_SIROIBIIDORO ){
		str = MSGMAN_AllocString( wk->msg_man, msg_bag_068 );
		BAG_SaveDataVidroSet( wk, VIDRO_WHITE );
		wk->sel_num = 0;
	}else if( item == ITEM_GOORUDOSUPUREE || item == ITEM_SIRUBAASUPUREE || item == ITEM_MUSIYOKESUPUREE ){
		str = BAG_SpraySet( wk, item );
	}else{
		return FALSE;
	}

	WORDSET_ExpandStr( wk->wset, wk->expb, str );
	STRBUF_Delete( str );

	return TRUE;
}

static STRBUF * BAG_SpraySet( BAG_WORK * wk, u16 item )
{
	s32	prm;
	u8 * swk;

	// スプレー効果チェック
	if( EncDataSave_CanUseSpray( BAG_EncountSaveGet(wk) ) == FALSE ){
		wk->sel_num = 0;
		return MSGMAN_AllocString( wk->msg_man, msg_bag_067 );
	}

	prm = ItemParamGet( item, ITEM_PRM_ATTACK, HEAPID_BAG );
	BAG_SaveDataSpraySet( wk, (u8)prm );
	wk->sel_num = 1;
	Snd_SePlay( SEQ_SE_DP_CARD2 );
	return MSGMAN_AllocString( wk->msg_man, msg_bag_066 );
}

static void BAG_ItemSubListReset( BAG_WORK * wk )
{
	MyItem_SubItemDirect(
		wk->dat->p_data[wk->dat->p_now].item,
		wk->dat->p_data[ wk->dat->p_now ].max-3,
		wk->dat->ret_item, wk->sel_num, HEAPID_BAG );

	BmpListExit(
		wk->lw,
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur );
	BMP_MENULIST_Delete( wk->ld );
	ItemListDataMake( wk );

	ItemListParamReset(
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur,
		wk->dat->p_data[wk->dat->p_now].max );
	ItemListCurPosReset(
		&wk->dat->p_data[wk->dat->p_now].scr,
		&wk->dat->p_data[wk->dat->p_now].cur,
		wk->dat->p_data[wk->dat->p_now].max, 9 );

	ItemListSet(
		wk, wk->dat->p_data[wk->dat->p_now].scr, wk->dat->p_data[wk->dat->p_now].cur );
}

static int BAG_ItemUseMsgNormalFunc( BAG_WORK * wk )
{
	switch( wk->sub_seq ){
	case 0:		// メッセージ描画
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
		wk->midx = Bag_TalkMsgPrint( wk );
		wk->sub_seq = 1;
		break;

	case 1:		// メッセージ削除
		if( GF_MSG_PrintEndCheck( wk->midx ) != 0 ){ break; }
		if( (sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B)) || sys.tp_trg ){
			BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
			wk->sub_seq = 2;
		}
		break;

	case 2:		// 再描画
		if( wk->sel_num != 0 ){
			BAG_ItemSubListReset( wk );
		}
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
		BagObj_CursorPalChg( wk, 1 );
//		SubEnterButtonBgChg( wk, 0 );
		return SEQ_MAIN;
	}
	return SEQ_BAG_ITEMUSE;
}



//============================================================================================
//	メニュー：タグをみる
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー：タグをみる
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuTag( BAG_WORK * wk )
{
	Bag_ItemMenuExit( wk );

	APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
	wk->dat->ret_mode = BAG_RET_TAG;	// 終了モード
	return SEQ_OUT;
}


//============================================================================================
//	メニュー：けってい
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー：けってい
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuKettei( BAG_WORK * wk )
{
	Bag_ItemMenuExit( wk );

	APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
	wk->dat->ret_mode = BAG_RET_ENTER;	// 終了モード
	return SEQ_OUT;
}


//============================================================================================
//	メニュー：すてる
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 捨てる初期化
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSub( BAG_WORK * wk )
{
//	Bag_ItemMenuExitSub( wk );
	Bag_ItemMenuExit( wk );

	wk->sel_num = 1;

	if( MyItem_GetItemNumDirect(
			wk->dat->p_data[wk->dat->p_now].item,
			wk->dat->p_data[wk->dat->p_now].max-3, wk->dat->ret_item, HEAPID_BAG ) == 1 ){

		Bag_SubTalkWinSet( wk );
		return SEQ_ITEM_SUB_YN_INIT;
	}

	Bag_DelNumSelWinSet( wk );
	Bag_NumArrowSet( wk, 0 );
	return SEQ_ITEM_SUB_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * 捨てる個数選択
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSubMain( BAG_WORK * wk )
{
	if( BAG_WheelNumSel( wk, &wk->sel_num, wk->sel_max ) == TRUE ){
		Bag_SubNumPut( wk );
		return SEQ_ITEM_SUB_MAIN;
	}

	if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
		Bag_SubTalkWinSet( wk );
		Bag_NumArrowPut( wk, ACT_OFF );
		wk->enter_anm_flg = 1;
		return SEQ_ITEM_SUB_YN_INIT;
	}

	switch( NumSelectCheck( &wk->sel_num, wk->sel_max ) ){
	case APP_NUMSEL_NONE:
		break;
	case APP_NUMSEL_UP:
		BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
		Bag_SubNumPut( wk );
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return SEQ_ITEM_SUB_MAIN;

	case APP_NUMSEL_DOWN:
		BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
		Bag_SubNumPut( wk );
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return SEQ_ITEM_SUB_MAIN;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		Bag_SubTalkWinSet( wk );
		Bag_NumArrowPut( wk, ACT_OFF );
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		return SEQ_ITEM_SUB_YN_INIT;
	}

	if( sys.trg & PAD_BUTTON_CANCEL ){
		Bag_DelNumSelWinExit( wk );
		Bag_NumArrowPut( wk, ACT_OFF );
		BagObj_CursorPalChg( wk, 1 );
//		SubEnterButtonBgChg( wk, 0 );
		Snd_SePlay( BAG_SE_ITEM_CANCEL );
		return SEQ_MAIN;
	}

	return SEQ_ITEM_SUB_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * 「すてる」はい・いいえ初期化
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSubYesNoInitSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		Bag_YesNoSelInit( wk );
		return SEQ_ITEM_SUB_YN_SEL;
	}
	return SEQ_ITEM_SUB_YN_INIT;
}

//--------------------------------------------------------------------------------------------
/**
 * 「すてる」はい・いいえ
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSubYesNoSelectSeq( BAG_WORK * wk )
{
	u32	ret;

	if( BAG_WheelMenuMove( wk ) == TRUE ){
		return SEQ_ITEM_SUB_YN_SEL;
	}

	if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
		ret = BmpYesNoSelectMainOutControl(wk->mw, BMPMENU_CNTROL_DECIDE, HEAPID_BAG );
		wk->enter_anm_flg = 1;
	}else{
		ret = BmpYesNoSelectMain( wk->mw, HEAPID_BAG );
	}

	switch( ret ){
	case 0:
		{
			STRBUF * str = MSGMAN_AllocString( wk->msg_man, msg_bag_055 );
			WORDSET_RegisterItemName( wk->wset, 0, wk->dat->ret_item );
			WORDSET_RegisterNumber(
				wk->wset, 1, wk->sel_num, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			WORDSET_ExpandStr( wk->wset, wk->expb, str );
			STRBUF_Delete( str );
		}
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		wk->midx = Bag_TalkMsgPrint( wk );
		return SEQ_ITEM_SUB_CMP;

	case BMPMENU_NULL:
		{
			u8	mv = BmpMenuMoveSiteGet( wk->mw );

			if( mv == BMPMENU_MOVE_UP ){
				BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
			}else if( mv == BMPMENU_MOVE_DOWN ){
				BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
			}
		}
		break;

	case BMPMENU_CANCEL:
		BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
		BagObj_CursorPalChg( wk, 1 );
//		SubEnterButtonBgChg( wk, 0 );
		return SEQ_MAIN;
	}
	return SEQ_ITEM_SUB_YN_SEL;
}

//--------------------------------------------------------------------------------------------
/**
 * 「すてる」完了
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSubCmpSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) != 0 ){
		return SEQ_ITEM_SUB_CMP;
	}

	wk->info_put = 1;

	BAG_ItemSubListReset( wk );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_TALK] );

	return SEQ_ITEM_SUB_RET;
}

//--------------------------------------------------------------------------------------------
/**
 * 「すてる」メッセージ終了待ち＆ボタン待ち -> メインへ
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSubRetSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) || sys.tp_trg ){
			wk->info_put = 0;
			BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
			GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
			BagObj_CursorPalChg( wk, 1 );
//			SubEnterButtonBgChg( wk, 0 );
			return SEQ_MAIN;
		}
	}
	return SEQ_ITEM_SUB_RET;
}


//============================================================================================
//	メニュー：とうろく
//============================================================================================
static int Bag_MenuCnvSet( BAG_WORK * wk )
{
	MyItem_CnvButtonItemSet( wk->myitem, wk->dat->ret_item );

	BmpListRewrite( wk->lw );

	Bag_ItemMenuExit( wk );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
	BagObj_CursorPalChg( wk, 1 );
//	SubEnterButtonBgChg( wk, 0 );
	return SEQ_MAIN;
}


//============================================================================================
//	メニュー：解除
//============================================================================================
static int Bag_MenuCnvDel( BAG_WORK * wk )
{
	MyItem_CnvButtonItemSet( wk->myitem, 0 );

	BmpListRewrite( wk->lw );

	Bag_ItemMenuExit( wk );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
	BagObj_CursorPalChg( wk, 1 );
//	SubEnterButtonBgChg( wk, 0 );
	return SEQ_MAIN;
}


//============================================================================================
//	メニュー：もたせる
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー：もたせる
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	移行するメインシーケンス
 */
//--------------------------------------------------------------------------------------------
static int Bag_MenuSet( BAG_WORK * wk )
{
	Bag_ItemMenuExit( wk );

	APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
	BAG_IconPutScrnChg( wk, 0 );
	wk->dat->ret_mode = BAG_RET_ITEMSET;	// 終了モード
	return SEQ_OUT;
}



//============================================================================================
//	ポケモンリスト「もたせる」
//============================================================================================

static int PokeItemSet_MainSeq( BAG_WORK * wk )
{
	PokeArrowMove( wk );

	if( BAG_WheelListMove( wk ) == TRUE ){
		return SEQ_ITEMSET_MAIN;
	}

	// ポケット選択（十字キー）
	if( PocketControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// ポケット選択（サブ画面ボタン）
	if( PocketButtonControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// アイテム選択
	{
		u8	ret = ItemListControl( wk );

		if( ret == LIST_SEL_ITEM ){			// 選択された
			if( ItemParamGet( wk->dat->ret_item, ITEM_PRM_EVENT, HEAPID_BAG ) != 0 ){
				STRBUF * str;

				GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
				BmpTalkWinWrite(
					&wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
				WORDSET_RegisterItemName( wk->wset, 0, wk->dat->ret_item );
				str = MSGMAN_AllocString( wk->msg_man, msg_bag_046 );
				WORDSET_ExpandStr( wk->wset, wk->expb, str );
				STRBUF_Delete( str );
				wk->midx = Bag_TalkMsgPrint( wk );
				BagObj_CursorPalChg( wk, 2 );
				return SEQ_ITEMSET_ERR;
			}
			wk->dat->ret_mode = BAG_RET_POKEITEMSET;
			APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
			return SEQ_OUT;
		}else if( ret == LIST_SEL_CANCEL ){	// キャンセル
			wk->dat->ret_mode = BAG_RET_POKEITEMSET;
			return SEQ_OUT;
		}
	}
	return SEQ_ITEMSET_MAIN;
}

static int PokeItemSet_ErrorSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) || sys.tp_trg ){
			BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
			GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
			BagObj_CursorPalChg( wk, 1 );
//			SubEnterButtonBgChg( wk, 0 );
			return SEQ_ITEMSET_MAIN;
		}
	}
	return SEQ_ITEMSET_ERR;
}


//============================================================================================
//	売る
//============================================================================================
// 「売る」モードアイテム選択
static int SaleMainSeq( BAG_WORK * wk )
{
	PokeArrowMove( wk );

	if( BAG_WheelListMove( wk ) == TRUE ){
		return SEQ_SALE_MAIN;
	}

	// ポケット選択（十字キー）
	if( PocketControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// ポケット選択（サブ画面ボタン）
	if( PocketButtonControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// アイテム選択
	{
		u8	ret = ItemListControl( wk );

		if( ret == LIST_SEL_ITEM ){			// 選択された
			STRBUF * str;

			Bag_GoldWinPut( wk, 0 );

			GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
			BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
			WORDSET_RegisterItemName( wk->wset, 0, wk->dat->ret_item );
			BagObj_CursorPalChg( wk, 2 );
			wk->sel_price = ItemParamGet( wk->dat->ret_item, ITEM_PRM_PRICE, HEAPID_BAG );
			// 大切なもの
			if( ItemParamGet( wk->dat->ret_item, ITEM_PRM_EVENT, HEAPID_BAG ) != 0 || wk->sel_price == 0 ){
				str = MSGMAN_AllocString( wk->msg_man, mes_shop_093 );
				WORDSET_ExpandStr( wk->wset, wk->expb, str );
				STRBUF_Delete( str );
				wk->midx = Bag_TalkMsgPrint( wk );
				return SEQ_SALE_RET;
			}
			wk->sel_num = 1;
			wk->sel_price >>= 1;
			// １コしかない
			if( MyItem_GetItemNumDirect(
					wk->dat->p_data[wk->dat->p_now].item,
					wk->dat->p_data[wk->dat->p_now].max-3, wk->dat->ret_item, HEAPID_BAG ) == 1 ){
				str = MSGMAN_AllocString( wk->msg_man, mes_shop_095 );
				WORDSET_RegisterNumber(
					wk->wset, 0, wk->sel_num*wk->sel_price, 6,
					NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
				WORDSET_ExpandStr( wk->wset, wk->expb, str );
				STRBUF_Delete( str );
				wk->midx = Bag_TalkMsgPrint( wk );
				return SEQ_SALE_YN_INIT;
			}
			str = MSGMAN_AllocString( wk->msg_man, mes_shop_094 );
			WORDSET_ExpandStr( wk->wset, wk->expb, str );
			STRBUF_Delete( str );
			wk->midx = Bag_TalkMsgPrint( wk );
			return SEQ_SALE_NUM_INIT;
		}else if( ret == LIST_SEL_CANCEL ){	// キャンセル
			return SEQ_OUT;
		}
	}
	return SEQ_SALE_MAIN;
}

// 「売る」モード個数選択初期化
static int SaleNumInitSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
//		wk->sel_num   = 1;
//		wk->sel_price = ItemParamGet( wk->dat->ret_item, ITEM_PRM_PRICE, HEAPID_BAG ) >> 1;
		if( wk->sel_max > 99 ){ wk->sel_max = 99; }
		Bag_SaleNumWinPut( wk, 0 );
		Bag_NumArrowSet( wk, 1 );
		return SEQ_SALE_NUM_SEL;
	}
	return SEQ_SALE_NUM_INIT;
}

// 「売る」モード個数選択
static int SaleNumSelSeq( BAG_WORK * wk )
{
	if( BAG_WheelNumSel( wk, &wk->sel_num, wk->sel_max ) == TRUE ){
		Bag_SaleNumWinPut( wk, 1 );
		return SEQ_SALE_NUM_SEL;
	}

	if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
		STRBUF * str;
		Bag_NumArrowPut( wk, ACT_OFF );
		BmpMenuWinClear( &wk->win[WIN_SALE_NUM], WINDOW_TRANS_OFF );
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		str = MSGMAN_AllocString( wk->msg_man, mes_shop_095 );
		WORDSET_RegisterNumber(
			wk->wset, 0, wk->sel_num*wk->sel_price, 6,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->expb, str );
		STRBUF_Delete( str );
		wk->midx = Bag_TalkMsgPrint( wk );
		wk->enter_anm_flg = 1;
		return SEQ_SALE_YN_INIT;
	}

	switch( NumSelectCheck( &wk->sel_num, wk->sel_max ) ){
	case APP_NUMSEL_NONE:
		break;
	case APP_NUMSEL_UP:
		BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
		Bag_SaleNumWinPut( wk, 1 );
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return SEQ_SALE_NUM_SEL;

	case APP_NUMSEL_DOWN:
		BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
		Bag_SaleNumWinPut( wk, 1 );
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return SEQ_SALE_NUM_SEL;
	}

	if( sys.trg & PAD_BUTTON_DECIDE ){
		STRBUF * str;
		Bag_NumArrowPut( wk, ACT_OFF );
		BmpMenuWinClear( &wk->win[WIN_SALE_NUM], WINDOW_TRANS_OFF );
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		str = MSGMAN_AllocString( wk->msg_man, mes_shop_095 );
		WORDSET_RegisterNumber(
			wk->wset, 0, wk->sel_num*wk->sel_price, 6,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->expb, str );
		STRBUF_Delete( str );
		wk->midx = Bag_TalkMsgPrint( wk );
		Snd_SePlay( BAG_SE_ITEM_SELECT );
		return SEQ_SALE_YN_INIT;
	}
	if( sys.trg & PAD_BUTTON_CANCEL ){
		wk->sel_price = 0;
		Bag_NumArrowPut( wk, ACT_OFF );
		BmpMenuWinClear( &wk->win[WIN_GOLD], WINDOW_TRANS_OFF );
		BmpMenuWinClear( &wk->win[WIN_SALE_NUM], WINDOW_TRANS_OFF );
		BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
		BagObj_CursorPalChg( wk, 1 );
//		SubEnterButtonBgChg( wk, 0 );
		Snd_SePlay( BAG_SE_ITEM_CANCEL );
		return SEQ_SALE_MAIN;
	}
	return SEQ_SALE_NUM_SEL;
}

// 「売る」はい・いいえ初期化
static int SaleYesNoInitSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		Bag_YesNoSelInit( wk );
		return SEQ_SALE_YN_SEL;
	}
	return SEQ_SALE_YN_INIT;
}

// 「売る」はい・いいえ
static int SaleYesNoSelectSeq( BAG_WORK * wk )
{
	u32	ret;

	if( BAG_WheelMenuMove( wk ) == TRUE ){
		return SEQ_SALE_YN_SEL;
	}

	if( BAG_SubEnterButtonCheck( wk ) == TRUE ){
		ret = BmpYesNoSelectMainOutControl(wk->mw, BMPMENU_CNTROL_DECIDE, HEAPID_BAG );
		wk->enter_anm_flg = 1;
	}else{
		ret = BmpYesNoSelectMain( wk->mw, HEAPID_BAG );
	}

	switch( ret ){
	case 0:
		{
			STRBUF * str = MSGMAN_AllocString( wk->msg_man, mes_shop_096 );
			WORDSET_RegisterItemName( wk->wset, 0, wk->dat->ret_item );
			WORDSET_RegisterNumber(
				wk->wset, 1, wk->sel_num*wk->sel_price, 6,
				NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
			WORDSET_ExpandStr( wk->wset, wk->expb, str );
			STRBUF_Delete( str );
		}
		GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
		wk->midx = Bag_TalkMsgPrint( wk );
		return SEQ_SALE_CMP;

	case BMPMENU_NULL:
		{
			u8	mv = BmpMenuMoveSiteGet( wk->mw );

			if( mv == BMPMENU_MOVE_UP ){
				BAG_WheelMoveKey( wk, WHEEL_ROT_MENU );
			}else if( mv == BMPMENU_MOVE_DOWN ){
				BAG_WheelMoveKey( wk, -WHEEL_ROT_MENU );
			}
		}
		break;

	case BMPMENU_CANCEL:
		wk->sel_price = 0;
		BmpMenuWinClear( &wk->win[WIN_GOLD], WINDOW_TRANS_OFF );
		BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
		BagObj_CursorPalChg( wk, 1 );
//		SubEnterButtonBgChg( wk, 0 );
		return SEQ_SALE_MAIN;
	}
	return SEQ_SALE_YN_SEL;
}

// 「売る」完了
static int SaleCmpSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) != 0 ){
		return SEQ_SALE_CMP;
	}
//	wk->gold = Mystatus_AddGold( wk->dat->myst, wk->sel_num*wk->sel_price );
	Snd_SePlay( SEQ_SE_DP_REGI );
	Mystatus_AddGold( wk->myst, wk->sel_num*wk->sel_price );
	if( wk->sel_num == 1 ){
		if( wk->dat->fnote_sale_cnt != 0xff ){
			wk->dat->fnote_sale_cnt++;
		}
	}else{
		wk->dat->fnote_sale_cnt = 2;
	}
	Bag_GoldWinPut( wk, 1 );

	wk->info_put = 1;

	BAG_ItemSubListReset( wk );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_TALK] );

	return SEQ_SALE_RET;
}

// 「売る」メッセージ終了待ち＆ボタン待ち -> メインへ
static int SaleRetSeq( BAG_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) || sys.tp_trg ){
			wk->info_put  = 0;
			wk->sel_price = 0;
			BmpMenuWinClear( &wk->win[WIN_GOLD], WINDOW_TRANS_OFF );
			BmpTalkWinClear( &wk->win[WIN_TALK], WINDOW_TRANS_ON );
			GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
			BagObj_CursorPalChg( wk, 1 );
//			SubEnterButtonBgChg( wk, 0 );
			return SEQ_SALE_MAIN;
		}
	}
	return SEQ_SALE_RET;
}


//============================================================================================
//	木の実関連
//============================================================================================

static int KinomiSel_MainSeq( BAG_WORK * wk )
{
	PokeArrowMove( wk );

	if( BAG_WheelListMove( wk ) == TRUE ){
		return SEQ_KINOMISEL_MAIN;
	}

	// ポケット選択（十字キー）
	if( PocketControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// ポケット選択（サブ画面ボタン）
	if( PocketButtonControl( wk ) == TRUE ){
		return SEQ_PAGE;
	}

	// アイテム選択
	{
		u8	ret = ItemListControl( wk );

		if( ret == LIST_SEL_ITEM ){			// 選択された
			if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_NORMAL ){
				if( ItemParamGet(wk->dat->ret_item,ITEM_PRM_FIELD,HEAPID_BAG) != ITEMUSE_FLD_KOYASHI ){
					BAG_ItemUseErrorMsgSet(
						wk->myst, wk->expb, wk->dat->ret_item, ITEMCHECK_FALSE, HEAPID_BAG );
					GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );
					BmpTalkWinWrite(
						&wk->win[WIN_TALK], WINDOW_TRANS_ON, TALK_WIN_CGX_NUM, TALKWIN_PAL );
					wk->midx = Bag_TalkMsgPrint( wk );
					return SEQ_ITEM_ERR_WAIT;
				}
			}
			wk->dat->ret_mode = BAG_RET_USE;
			APP_WipeStart( APP_WIPE_OUT, HEAPID_BAG );
			return SEQ_OUT;
		}else if( ret == LIST_SEL_CANCEL ){	// キャンセル
			wk->dat->ret_mode = BAG_RET_CANCEL;
			return SEQ_OUT;
		}
	}
	return SEQ_KINOMISEL_MAIN;
}





//============================================================================================
//	ホイール関連
//============================================================================================
static void BAG_WheelMoveKey( BAG_WORK * wk, s8 mv )
{
	s16	rad = GF_BGL_RadianGet( wk->bgl, GF_BGL_FRAME3_S );

	rad += mv;
	if( rad >= 360 ){
		rad -= 360;
	}else if( rad < 0 ){
		rad += 360;
	}
	GF_BGL_RadianSetReq( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_RADION_SET, rad );
	wk->wheel_rot = rad;
}


// ホイールに触ったか
static BOOL BAG_WheelTouchCheck(void)
{
	int	ret = GF_TP_HitTrg( WheelHitTbl );

	if( ret == 1 ){
		return TRUE;
	}
	return FALSE;
}

// ホイールに触っているか
static BOOL BAG_WheelPushCheck(void)
{
	int	ret = GF_TP_HitCont( WheelContTbl );

	if( ret == 1 ){
		return TRUE;
	}
	return FALSE;
}

// 現在の中心からの角度を取得
/*
static u16 BAG_WheelTpPosAtan( u16 x, u16 y )
{
	return FX_Atan2Idx( (SUB_WHEEL_CY-y)*FX32_ONE, (SUB_WHEEL_CX-x)*FX32_ONE );
}
*/

static BOOL BAG_WheelMove( BAG_WORK * wk, u16 mv_rot )
{
	if( BAG_WheelTouchCheck() == TRUE ){
		wk->wheel_flg = 1;
		wk->wheel_mv  = 0;
		wk->wheel_pos = 0;
		wk->backup_tpx = sys.tp_x;
		wk->backup_tpy = sys.tp_y;
	}

	if( wk->wheel_flg == 1 ){
		if( BAG_WheelPushCheck() == TRUE ){
			s32	mv, rot;

			mv = CalcTool_CircleVectorDistance(
					SUB_WHEEL_CX - wk->backup_tpx, SUB_WHEEL_CY - wk->backup_tpy,
					SUB_WHEEL_CX - sys.tp_x, SUB_WHEEL_CY - sys.tp_y, SUB_WHEEL_R );

			rot = CalcTool_CircleVectroDistRotaGet( SUB_WHEEL_R, mv * SUB_WHEEL_REG );
			rot = ((rot<<8)/182)>>8;
			wk->wheel_rot += rot;
			if( wk->wheel_rot < 0 ){
				wk->wheel_rot += 360;
			}else if( wk->wheel_rot >= 360 ){
				wk->wheel_rot -= 360;
			}
			GF_BGL_RadianSetReq( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_RADION_SET, wk->wheel_rot );

			{
				s32	max;
				s32	mv_cnt;

				max = 2 * SUB_WHEEL_R * 3.14;	// 円周
				mv_cnt = max / mv_rot;

				if( mv > 0 ){
					if( wk->wheel_mv < 0 ){
						wk->wheel_mv = mv / mv_cnt;
						wk->wheel_pos = mv % mv_cnt;
					}else{
						wk->wheel_mv += ( (wk->wheel_pos+mv) / mv_cnt );
						wk->wheel_pos = (wk->wheel_pos+mv) % mv_cnt;
					}
				}else if( mv < 0 ){
					if( wk->wheel_mv > 0 ){
						wk->wheel_mv = mv / mv_cnt;
						wk->wheel_pos = mv % mv_cnt;
					}else{
						wk->wheel_mv += ( (wk->wheel_pos+mv) / mv_cnt );
						wk->wheel_pos = (wk->wheel_pos+mv) % mv_cnt;
					}
				}
			}
			wk->backup_tpx = sys.tp_x;
			wk->backup_tpy = sys.tp_y;
		}else{
			wk->wheel_flg = 0;
			wk->wheel_mv  = 0;
		}
		return TRUE;
	}

	return FALSE;

/*
	if( BAG_WheelTouchCheck() == TRUE ){
		wk->wheel_flg = 1;
		wk->wheel_mv  = 0;
		wk->wheel_pos = BAG_WheelTpPosAtan( sys.tp_x, sys.tp_y );
	}

	if( wk->wheel_flg == 1 ){
		if( BAG_WheelPushCheck() == TRUE ){
			s16	mv;
			s16	zettai;

			mv = BAG_WheelRotGet( wk, sys.tp_x, sys.tp_y );
			if( mv != wk->wheel_rot ){
				GF_BGL_RadianSetReq( wk->bgl, GF_BGL_FRAME3_S, GF_BGL_RADION_SET, mv );

				zettai = mv - wk->wheel_rot;
				if( zettai < 0 ){ zettai = -zettai; }

				if( zettai >= 180 ){
					zettai = 360 - zettai;
				}

				if( zettai >= mv_rot ){
					if( mv - wk->wheel_rot > 0 ){
						// 0から360に移動させたときの不具合補正
						if( mv - wk->wheel_rot > 180 ){
							// 逆回転させたときはカウンタをクリア
							if( wk->wheel_mv > 0 ){
								wk->wheel_mv = -(zettai/mv_rot);
							}else{
								wk->wheel_mv -= (zettai/mv_rot);
							}
						}else{
							// 逆回転させたときはカウンタをクリア
							if( wk->wheel_mv < 0 ){
								wk->wheel_mv = (zettai/mv_rot);
							}else{
								wk->wheel_mv += (zettai/mv_rot);
							}
						}
					}else if( mv - wk->wheel_rot < 0 ){
						// 360から0に移動させたときの不具合補正
						if( mv - wk->wheel_rot < -180 ){
							// 逆回転させたときはカウンタをクリア
							if( wk->wheel_mv < 0 ){
								wk->wheel_mv = (zettai/mv_rot);
							}else{
								wk->wheel_mv += (zettai/mv_rot);
							}
						}else{
							// 逆回転させたときはカウンタをクリア
							if( wk->wheel_mv > 0 ){
								wk->wheel_mv = -(zettai/mv_rot);
							}else{
								wk->wheel_mv -= (zettai/mv_rot);
							}
						}
					}
					wk->wheel_pos = BAG_WheelTpPosAtan( sys.tp_x, sys.tp_y );
					wk->wheel_rot = mv;
				}
			}
			wk->backup_tpx = sys.tp_x;
			wk->backup_tpy = sys.tp_y;
		}else{
			wk->wheel_flg = 0;
			wk->wheel_mv  = 0;
			if( sys.tp_cont ){
				wk->wheel_rot = BAG_WheelRotGet( wk, sys.tp_x, sys.tp_y );
			}else{
				wk->wheel_rot = BAG_WheelRotGet( wk, wk->backup_tpx, wk->backup_tpy );
			}
		}
		return TRUE;
	}

	return FALSE;
*/

}

/*
static s16 BAG_WheelRotGet( BAG_WORK * wk, u16 x, u16 y )
{
	s32	zettai;

	zettai = BAG_WheelTpPosAtan( x, y ) - wk->wheel_pos;

	// 絶対値を求める
	if( zettai < 0 ){
		zettai = (((zettai<<8)/182)>>8);
		zettai = 360+zettai;
	}else{
		zettai = (((zettai<<8)/182)>>8);
	}

	if( wk->wheel_rot+zettai >= 360 ){
		return ( (wk->wheel_rot+zettai) - 360 );
	}

	return (wk->wheel_rot+zettai);
}
*/


// アイテムリスト選択
static BOOL BAG_WheelListMove( BAG_WORK * wk )
{
	BOOL mv_ret = BAG_WheelMove( wk, WHEEL_ROT_LIST );

	if( wk->wheel_mv > 0 ){
		if( BAG_WheelListWrite( wk, PAD_KEY_UP ) == TRUE ){
			wk->wheel_mv--;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}else if( wk->wheel_mv < 0 ){
		if( BAG_WheelListWrite( wk, PAD_KEY_DOWN ) == TRUE ){
			wk->wheel_mv++;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}

	return mv_ret;
}

static BOOL BAG_WheelListWrite( BAG_WORK * wk, u16 mv )
{
	u16	scr, cur;

	scr = wk->dat->p_data[ wk->dat->p_now ].scr;
	cur = wk->dat->p_data[ wk->dat->p_now ].cur;

	BmpListMainOutControlEx( wk->lw, NULL, scr, cur, 1, mv, &scr, &cur );

	if( scr == wk->dat->p_data[ wk->dat->p_now ].scr &&
		cur == wk->dat->p_data[ wk->dat->p_now ].cur ){
		return FALSE;
	}

	CATS_ObjectPosSetCap(
		wk->cap[ACT_LIST_SEL_CURSOR], CURSOR_ACT_PX, CURSOR_ACT_PY + (cur-1) * 16 );

	wk->dat->p_data[ wk->dat->p_now ].scr = scr;
	wk->dat->p_data[ wk->dat->p_now ].cur = cur;

	return TRUE;
}

// 入れ替え時のアイテムリスト選択
static BOOL BAG_WheelChgListMove( BAG_WORK * wk )
{
	BOOL mv_ret = BAG_WheelMove( wk, WHEEL_ROT_LIST );

	if( wk->wheel_mv > 0 ){
		if( BAG_WheelChgListWrite( wk, PAD_KEY_UP ) == TRUE ){
			wk->wheel_mv--;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}else if( wk->wheel_mv < 0 ){
		if( BAG_WheelChgListWrite( wk, PAD_KEY_DOWN ) == TRUE ){
			wk->wheel_mv++;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}

	return mv_ret;
}

static BOOL BAG_WheelChgListWrite( BAG_WORK * wk, u16 mv )
{
	u16	scr, cur;

	scr = wk->dat->p_data[ wk->dat->p_now ].scr;
	cur = wk->dat->p_data[ wk->dat->p_now ].cur;

	BmpListMainOutControlEx( wk->lw, NULL, scr, cur, 1, mv, &scr, &cur );

	if( scr == wk->dat->p_data[ wk->dat->p_now ].scr &&
		cur == wk->dat->p_data[ wk->dat->p_now ].cur ){
		return FALSE;
	}

	CATS_ObjectPosSetCap(
		wk->cap[ACT_LIST_SEL_CHANGE], CURSOR_ACT_PX, CURSOR_ACT_PY+(cur-1)*16-8 );

	wk->dat->p_data[ wk->dat->p_now ].scr = scr;
	wk->dat->p_data[ wk->dat->p_now ].cur = cur;

	return TRUE;
}

// メニュー選択
static BOOL BAG_WheelMenuMove( BAG_WORK * wk )
{
	BOOL mv_ret = BAG_WheelMove( wk, WHEEL_ROT_MENU );

	if( wk->wheel_mv > 0 ){
		if( BAG_WheelMenuWrite( wk, BMPMENU_CNTROL_UP ) == TRUE ){
			wk->wheel_mv--;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}else if( wk->wheel_mv < 0 ){
		if( BAG_WheelMenuWrite( wk, BMPMENU_CNTROL_DOWN ) == TRUE ){
			wk->wheel_mv++;
		}else{
			wk->wheel_mv = 0;
		}
		return TRUE;
	}

	return mv_ret;
}

static BOOL BAG_WheelMenuWrite( BAG_WORK * wk, u8 prm )
{
	u8	cur = BmpMenuCursorPosGet( wk->mw );
	
	BmpMenuMainOutControl( wk->mw, prm );

	if( cur == BmpMenuCursorPosGet( wk->mw ) ){
		return FALSE;
	}

	return TRUE;
}

// 個数選択
static BOOL BAG_WheelNumSel( BAG_WORK * wk, s16 * num, u16 max )
{
	BOOL mv_ret;
	s16	tmp;

	mv_ret = BAG_WheelMove( wk, WHEEL_ROT_MENU );
	tmp = *num;

	if( wk->wheel_mv > 0 ){
		wk->wheel_mv--;
		*num += 1;
		if( *num > max ){ *num = 1; }
		if( *num == tmp ){ return FALSE; }
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return TRUE;
	}else if( wk->wheel_mv < 0 ){
		wk->wheel_mv++;
		*num -= 1;
		if( *num <= 0 ){ *num = max; }
		if( *num == tmp ){ return FALSE; }
		Snd_SePlay( SEQ_SE_DP_BAG_004 );
		return TRUE;
	}

	return mv_ret;
}

