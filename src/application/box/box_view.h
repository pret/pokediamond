//============================================================================================
/**
 * @file	box_view.h
 * @brief	ボックス操作画面　描画部共有ヘッダ
 * @author	taya
 * @date	2005.09.13
 */
//============================================================================================
#ifndef __BOX_VIEW_H__
#define __BOX_VIEW_H__

#include "box_common.h"
#include "system\arc_tool.h"
#include "system\clact_util.h"
#include "system\numfont.h"
#include "system\softsprite.h"
#include  "system\msgdata.h"
#include  "system\wordset.h"

//------------------------------------------------------
/*
 * 60fps化の望みを捨てないために…
 */
//------------------------------------------------------
#define BOX_FPS_60

#ifdef BOX_FPS_60
#define  BOX_TIMER_RATIO	(2)
#else
#define  BOX_TIMER_RATIO	(1)
#endif

#define BOX_TIMER(t)		((t)*BOX_TIMER_RATIO)
#define BOX_EFF_SPEED(s)	((s)*(2/BOX_TIMER_RATIO))
#define BOX_ANM_SPEED		(FX32_ONE*(2/BOX_TIMER_RATIO))


//-----------------------------------------------------
/**
 *  ＢＧ割り振り
 */
//-----------------------------------------------------
enum {
	FRM_MAIN_POKEMON = GF_BGL_FRAME0_M,
	FRM_MAIN_MESSAGE = GF_BGL_FRAME1_M,
	FRM_MAIN_STATUS  = GF_BGL_FRAME2_M,
	FRM_MAIN_TRAY    = GF_BGL_FRAME3_M,

	FRM_SUB_BMPWIN   = GF_BGL_FRAME0_S,
	FRM_SUB_REEL     = GF_BGL_FRAME1_S,
	FRM_SUB_ICONLINE = GF_BGL_FRAME2_S,
	FRM_SUB_BACK     = GF_BGL_FRAME3_S,

	// つよさ比べモード時の割り振り
	FRM_SUB_COMPARE_BMPWIN = GF_BGL_FRAME0_S,
	FRM_SUB_COMPARE_PAGE1  = GF_BGL_FRAME1_S,
	FRM_SUB_COMPARE_PAGE2  = GF_BGL_FRAME2_S,
	FRM_SUB_COMPARE_PAGE3  = GF_BGL_FRAME3_S,
};
//-----------------------------------------------------
/**
 *  ＢＧパレット割り振り
 */
//-----------------------------------------------------
enum {
	PAL_MAIN_STATUS = 0,
	PAL_MAIN_STATUS2,
	PAL_MAIN_STATUS3,
	PAL_MAIN_STATUS4,
	PAL_MAIN_WINDOW,
	PAL_COMPAREMODE_ARROW_L,
	PAL_COMPAREMODE_ARROW_R,
	PAL_FIX_USE_MAX,


	PAL_MAIN_WINDOW_FRAME = PAL_FIX_USE_MAX,
	PAL_MAIN_MESSAGE_FRAME,

	PAL_MAIN_WALLPAPER_A,
	PAL_MAIN_WALLPAPER_B,
};

enum {
	PAL_SUB_BG1 = 0,
	PAL_SUB_BG2,
	PAL_SUB_BMPWIN,

	// つよさくらべモード
	PAL_SUB_COMPARE_LEFT = 0,
	PAL_SUB_COMPARE_RIGHT,
	PAL_SUB_COMPARE_CONDITION,
};

//-----------------------------------------------------
/**
 * ＯＢＪパレット割り振り
 */
//-----------------------------------------------------
enum {
	OBJPAL_CURSOR = 0,
	OBJPAL_MAINBUTTON,
	OBJPAL_ICON,			// ポケモンアイコンに４本
	OBJPAL_ICON2,
	OBJPAL_ICON3,
	OBJPAL_ICON4,
	OBJPAL_AREASELECT_ICON,	// 範囲選択アイコンにも４本
	OBJPAL_AREASELECT_ICON2,
	OBJPAL_AREASELECT_ICON3,
	OBJPAL_AREASELECT_ICON4,
	OBJPAL_TYPE,			// タイプアイコンに３本
	OBJPAL_TYPE2,
	OBJPAL_TYPE3,
	OBJPAL_TRAYICON_WP = 0x0d,
	OBJPAL_TRAYICON_POKE = 0x0e,
	OBJPAL_TRAYICON_BASE = 0x0f,

	//------------------------------

	OBJPAL_CURSOR_EXPERTMODE = OBJPAL_MAINBUTTON,	// 同居してる
	OBJPAL_TRAYICON_TOP = OBJPAL_TRAYICON_WP,

	// どうぐ整理モードで使うアイテムアイコン用パレット指定
	// ポケモンアイコンの範囲選択は行わないので、そこを丸々使わせてもらう
	OBJPAL_ITEMICON_INFOWIN = OBJPAL_AREASELECT_ICON,	// アイテム説明ウィンドウ用アイコン
	OBJPAL_ITEMICON1,	// つかんでるアイコン、出てくるアイコン、消えるアイコンで合計３個まで
	OBJPAL_ITEMICON2,
	OBJPAL_ITEMICON3,


	OBJPAL_COMPARE_POKEICON1 = 4,
	OBJPAL_COMPARE_POKEICON2,
	OBJPAL_COMPARE_POKEICON3,
	OBJPAL_COMPARE_POKEICON4,
	OBJPAL_COMPARE_CONDITION,

};

//-----------------------------------------------------
/**
 *  ＯＢＪキャラ位置割り振り（メインLCD側）
 */
//-----------------------------------------------------
enum {
	OBJCHAR_TRAYICON_SIZE = 4 * 4 * 2,	// 8bit なので
	OBJCHAR_POKEICON_SIZE = 4 * 4,

	OBJCHAR_CURSOR_POS = 0,
	OBJCHAR_CURSOR_SIZE = 88,

	OBJCHAR_TRAY_ICON_POS = OBJCHAR_CURSOR_POS + OBJCHAR_CURSOR_SIZE,			// 0+88 = 88
	OBJCHAR_TRAY_ICON_HALF_SIZE = 480,	// OBJCHAR_POKEICON_SIZE * 30（１ボックス分）
	OBJCHAR_TRAY_ICON_SIZE = 960,

	OBJCHAR_PARTY_ICON_POS = OBJCHAR_TRAY_ICON_POS + OBJCHAR_TRAY_ICON_SIZE,	// 88+960 = 1048,
	OBJCHAR_PARTY_ICON_SIZE = 192,

	OBJCHAR_MOVING_SINGLE_ICON_POS = OBJCHAR_PARTY_ICON_POS + OBJCHAR_PARTY_ICON_SIZE,	// 1048+192 = 1240,
	OBJCHAR_MOVING_SINGLE_ICON_SIZE = 16,

	OBJCHAR_MAIN_BUTTON_POS = OBJCHAR_MOVING_SINGLE_ICON_POS + OBJCHAR_MOVING_SINGLE_ICON_SIZE,	// 1240+16= 1256,
	OBJCHAR_MAIN_BUTTON_SIZE = 216,

	OBJCHAR_ARROW_POS = OBJCHAR_MAIN_BUTTON_POS + OBJCHAR_MAIN_BUTTON_SIZE,	// 1256+216 = 1472,
	OBJCHAR_ARROW_SIZE = 8,

	OBJCHAR_INFOBACK_POS = OBJCHAR_ARROW_POS + OBJCHAR_ARROW_SIZE,			// 1472+8 = 1480,
	OBJCHAR_INFOBACK_SIZE = 24,

	OBJCHAR_POKETYPE_POS = OBJCHAR_INFOBACK_POS + OBJCHAR_INFOBACK_SIZE,	// 1480+24 = 1504
	OBJCHAR_POKETYPE_HALF_SIZE = 8,
	OBJCHAR_POKETYPE_SIZE = 16,

	// ここまで常駐 -------------------------------------
	OBJCHAR_FIX_END = OBJCHAR_POKETYPE_POS + OBJCHAR_POKETYPE_SIZE,			// 1504+16 = 1520

	// 範囲選択ポケアイコン
	OBJCHAR_AREASELECT_ICON_POS = OBJCHAR_FIX_END,

	// アイテムアイコン
	OBJCHAR_ITEMICON_POS_TOP = OBJCHAR_FIX_END,
	OBJCHAR_ITEMICON_SIZE = 16,
	OBJCHAR_ITEMICON_INFO_POS = OBJCHAR_ITEMICON_POS_TOP,
	OBJCHAR_ITEMICON_1_POS    = OBJCHAR_ITEMICON_POS_TOP + OBJCHAR_ITEMICON_SIZE,
	OBJCHAR_ITEMICON_2_POS    = OBJCHAR_ITEMICON_POS_TOP + OBJCHAR_ITEMICON_SIZE*2,
	OBJCHAR_ITEMICON_3_POS    = OBJCHAR_ITEMICON_POS_TOP + OBJCHAR_ITEMICON_SIZE*3,

	OBJCHAR_ITEMICON_END = OBJCHAR_ITEMICON_3_POS+OBJCHAR_ITEMICON_SIZE,	// 1520+3*16= 1568

	// トレイアイコン
	OBJCHAR_TRAYICON_POS = OBJCHAR_ITEMICON_END,


};

//-----------------------------------------------------
/**
 *  ＯＢＪキャラ位置割り振り（サブLCD側）
 */
//-----------------------------------------------------
enum {
	OBJCHAR_SUB_BUTTON_POS = 0,
	OBJCHAR_SUB_BUTTON_SIZE = 192,

	// ここまで常駐 --------------------------------------
	OBJCHAR_SUB_FIX_END = OBJCHAR_SUB_BUTTON_POS + OBJCHAR_SUB_BUTTON_SIZE,

	OBHCHAR_SUB_MARKICON_POS = OBJCHAR_SUB_FIX_END,
	OBJCHAR_SUB_MARKICON_SIZE = 256,

	OBJCHAR_SUB_TRAYICON_POS = OBJCHAR_SUB_FIX_END,
};
//-----------------------------------------------------
/**
 *  画面レイアウト
 */
//-----------------------------------------------------
enum {
	SUBSURFACE_YOFS = (192*2),


	ICON_TRAY_XORG = 112,
	ICON_TRAY_YORG = 40,
	ICON_TRAY_XSPC = 24,
	ICON_TRAY_YSPC = 24,

	PARTYICON_YSPC = 40,

	PARTYICON_1ST_XPOS = 144,
	PARTYICON_1ST_YPOS = 28,

	PARTYICON_2ND_XPOS = 192,
	PARTYICON_2ND_YPOS = 36,

	PARTYICON_3RD_XPOS = PARTYICON_1ST_XPOS,
	PARTYICON_3RD_YPOS = PARTYICON_1ST_YPOS + PARTYICON_YSPC,

	PARTYICON_4TH_XPOS = PARTYICON_2ND_XPOS,
	PARTYICON_4TH_YPOS = PARTYICON_2ND_YPOS + PARTYICON_YSPC,

	PARTYICON_5TH_XPOS = PARTYICON_1ST_XPOS,
	PARTYICON_5TH_YPOS = PARTYICON_3RD_YPOS + PARTYICON_YSPC,

	PARTYICON_6TH_XPOS = PARTYICON_2ND_XPOS,
	PARTYICON_6TH_YPOS = PARTYICON_4TH_YPOS + PARTYICON_YSPC,

	PARTYTRAY_CLOSEBUTTON_XPOS = 192,
	PARTYTRAY_CLOSEBUTTON_YPOS = 184,


	CURSOR_ICON_YDIFF = -16,
	CURSOR_ICON_XDIFF = 0,
	CURSOR_CATCHICON_XDIFF = 0,
	CURSOR_CATCHICON_YDIFF = -4,

	CURSOR_TRAYTAB_XPOS = 168,
	CURSOR_TRAYTAB_YPOS = 8,

	MAINBUTTON_XPOS = 183,
	MAINBUTTON_YPOS = 176,

	CURSOR_PARTYBUTTON_XPOS = MAINBUTTON_XPOS - 24,
	CURSOR_PARTYBUTTON_YPOS = MAINBUTTON_YPOS - 16,
	CURSOR_CLOSEBUTTON_XPOS = MAINBUTTON_XPOS + 52,
	CURSOR_CLOSEBUTTON_YPOS = CURSOR_PARTYBUTTON_YPOS,

/*
	SUB_TRAYICON0_XPOS = 
	SUB_TRAYICON0_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON1_XPOS = 
	SUB_TRAYICON1_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON2_XPOS = 
	SUB_TRAYICON2_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON3_XPOS = 
	SUB_TRAYICON3_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON4_XPOS = 72,
	SUB_TRAYICON4_YPOS = SUBSURFACE_YOFS + 112,
	SUB_TRAYICON5_XPOS = 
	SUB_TRAYICON5_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON6_XPOS = 
	SUB_TRAYICON6_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON7_XPOS = 
	SUB_TRAYICON7_YPOS = SUBSURFACE_YOFS + 0,
	SUB_TRAYICON8_XPOS = 
	SUB_TRAYICON8_YPOS = SUBSURFACE_YOFS + 0,
*/

};

//-----------------------------------------------------
/**
 *  アクタープライオリティ
 */
//-----------------------------------------------------
enum {
	/* カーソルは指すアイコンに同期 */
	BGPRI_TRAY_ICON = 2,
	BGPRI_PARTY_ICON = 1,
	BGPRI_MOVING_ICON = 1,
	BGPRI_MAIN_BUTTON = 2,
	BGPRI_TYPE_ICON = 3,
	BGPRI_INFO_BACK = 3,

	BGPRI_SUB_ICON = 2,
	BGPRI_SUB_BUTTON = 3,

	BGPRI_ITEMICON_INFO = 0,
};

enum {
	ACTPRI_ITEMICON_INFO,
	ACTPRI_CURSOR,
	ACTPRI_CATCH_ICON,
	ACTPRI_ITEM_ICON,
	ACTPRI_PARTY_ICON_MIN,
	ACTPRI_PARTY_ICON_MAX = ACTPRI_PARTY_ICON_MIN + TEMOTI_POKEMAX,
	ACTPRI_TRAY_ICON_MIN,
	ACTPRI_TRAY_ICON_MAX = ACTPRI_TRAY_ICON_MIN + BOX_MAX_POS,
	ACTPRI_CURSOR_SHADOW,
	ACTPRI_ARROW,
	ACTPRI_MAIN_BUTTON,
	ACTPRI_TAB_ARROW,
	ACTPRI_TYPE_ICON,
	ACTPRI_INFO_BACK,


	ACTPRI_SUB_ICON,
	ACTPRI_SUB_BUTTON,
};


/*============================================================================*/
/*  アイコン描画関連                                                          */
/*============================================================================*/

#define BOXICON_CHAR_SIZE		(4*4)

// 本来8bitなのでキャラ数*0x40必要だが、アニメ無しなので半分で良い。+0x80はヘッダ分。
#define BOXICON_CHARBUF_SIZE	(BOXICON_CHAR_SIZE*0x20+0x80)	

enum {
	ICON_ANM_NORMAL,	///< 通常時
	ICON_ANM_RELEASE,	///< 逃がすとき
	ICON_ANM_COMEBACK,	///< 戻ってくるとき
};

enum{
	ITEMICON_ANM_CAUGHT,
	ITEMICON_ANM_APPEAR,
	ITEMICON_ANM_DISAPPEAR,
	ITEMICON_ANM_CATCH,
	ITEMICON_ANM_SET,
	ITEMICON_ANM_CAUGHT_RESTORE,
	ITEMICON_ANM_APPEARED,
};

typedef struct {
	CLACT_WORK_PTR		act;
	NNSG2dImageProxy	imgProxy;
	u32					imgArcIdx;
	u16					imgPalNo;
	u16					markingBit;
	u16					itemNo;
}BOX_ICON_WORK;


typedef struct {
	void*					anmBuf;
	NNSG2dAnimBankData*		anmBank;

	void*					cellBuf;
	u32						cellBankSize;
	NNSG2dCellDataBank*		cellBank;

	void*					item_cellBuf;
	void*					item_anmBuf;
	NNSG2dCellDataBank*		item_cellBank;
	NNSG2dAnimBankData*		item_anmBank;


	CLACT_SET_PTR				actSys;
	NNSG2dImagePaletteProxy		plttProxy;
	GF_BGL_INI*					bgl;
	const BOXAPP_VPARAM*		vpara;
	BOXAPP_VIEW_WORK*			vwk;

	ARCHANDLE*					arcHandle;

	u8   charbuf[BOXICON_CHARBUF_SIZE];

}BOX_ICON_SYS;



extern BOOL BoxAppView_IconSysInit( BOX_ICON_SYS* iconSys, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys );
extern void BoxAppView_IconSysQuit( BOX_ICON_SYS* iconSys );
extern void BoxAppView_IconAdd( BOX_ICON_SYS* wk, POKEMON_PASO_PARAM* ppp, s32 x, s32 y, u32 bgpri, u32 actpri, u32 charno, BOX_ICON_WORK* icon );
extern void BoxAppView_IconAddCharSet( BOX_ICON_SYS* wk, POKEMON_PASO_PARAM* ppp, u32 monsno, u32 arcIdx, u8* charBuf, s32 x, s32 y, u32 bgpri, u32 actpri, u32 charno, BOX_ICON_WORK* icon );
extern void BoxAppView_IconCharDataLoad( BOX_ICON_SYS* wk, void* buf, u32 datIdx, u32 size );
extern void BoxAppView_IconWorkInit( BOX_ICON_SYS* iconSys, BOX_ICON_WORK* wk, u32 num );
extern void BoxAppView_IconWorkQuit( BOX_ICON_SYS* iconSys, BOX_ICON_WORK* wk, u32 num );
extern void BoxAppView_IconWorkCopy( const BOX_ICON_WORK* src, BOX_ICON_WORK* dst, u32 num );
extern void BoxAppView_IconAnmStart( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon, u32 anm );
extern BOOL BoxAppView_IconAnmWait( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon );
extern void BoxAppView_IconLimitModeSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 limitBit );
extern void BoxAppView_IconMarkBitSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 markBit );
extern void BoxAppView_IconItemNumberSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 itemNo );
extern void BoxAppView_IconAreaSelectPalSet( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon, BOOL areaSelFlag );

extern void BoxAppView_Icon_ResetImageBank( BOX_ICON_SYS* sys, BOX_ICON_WORK* icon, u32 charpos );
extern const BOXAPP_WORK* BoxAppView_GetMainWork( BOXAPP_VIEW_WORK* vwk );

/*============================================================================*/
/*  アイテムアイコン関連                                                      */
/*============================================================================*/
typedef		struct _ITEMICON_VIEW_WORK		ITEMICON_VIEW_WORK;

extern BOOL BoxAppView_ItemIconInit( ITEMICON_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys );
extern void BoxAppView_ItemIconQuit( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartDisp( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartAppear( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitAppear( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartCatch( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitCatch( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_MoveCaughtIcon( ITEMICON_VIEW_WORK* wk, const VecFx32* mtx );
extern void BoxAppView_ItemIcon_ChangePriorityCaughtIcon( ITEMICON_VIEW_WORK* wk, u32 pri );
extern void BoxAppView_ItemIcon_StartSet( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitSet( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartDisappear( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitDisappear( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartSwap( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitSwap( ITEMICON_VIEW_WORK* wk );
extern void BoxAppView_ItemIcon_StartRestore( ITEMICON_VIEW_WORK* wk );
extern BOOL BoxAppView_ItemIcon_WaitRestore( ITEMICON_VIEW_WORK* wk );





/*============================================================================*/
/*  トレイ描画関連                                                            */
/*============================================================================*/

enum {
	TRAY_WALLPAPER_FADE_STEPS = BOX_TIMER(4),
};

//-----------------------------------------------------
/**
 *  トレイ描画処理ワーク
 */
//-----------------------------------------------------
typedef struct {
	u8  trayNum;		///< 表示中トレイナンバー
	u8  scrnPos;		///< 表示中トレイの描画開始スクリーンＸ位置（キャラ単位）
	u8  imgPos;			///< 表示中トレイの画像転送位置（キャラ・パレット・付随するOBJ等々）
	u8  scrollOutIcon;	///<

	u32 scrollWait;		///< スクロール処理タイマー

	s32 scrollPos;		///< 現在のスクロール値（計算用 = 固定小数）
	s32 scrollSetPos;	///< 現在のスクロール値（セット用 = 整数）
	s32 scrollValue;	///< スクロール時の加算値
	s32 scrollEndPos;	///< スクロール終了時の値

	fx32  scrollIconXpos[BOX_MAX_COLUMN];
	u32   scrollInTrayNumber;
	u32   scrollInIconVramPos;

	fx32  scrollInIconXpos[2][BOX_MAX_COLUMN];
	fx32  scrollOutIconXpos[2][BOX_MAX_COLUMN];
	u32   scrollIconVcnt;

	BOOL  scrollEndFlag;

	u16  icon_release_pos;	///< 逃がしアイコン位置
	u8   wpseq;			///< 壁紙変更動作シーケンス
	u8   wp_taskFlag;
	u8   mvseq;

	BOX_ICON_WORK	icon[2][BOX_MAX_POS];

	u8   iconCharBuf[BOX_MAX_POS][BOXICON_CHARBUF_SIZE];
	u16  iconArcIdx[BOX_MAX_POS];
	u16  iconMonsNo[BOX_MAX_POS];

	s16  readicon_column;
	s16  readicon_column_add;

	int  iconVisibleXmin;
	int  iconVisibleXmax;
	int  scrollXofs;

	u16  wallpaperFadePalette[TRAY_WALLPAPER_FADE_STEPS+1][16];

	BOX_ICON_SYS*				iconSys;
	GF_BGL_INI*					bgl;
	const BOXAPP_VPARAM*		vpara;
	BOXAPP_VIEW_WORK*			vwk;
}TRAY_VIEW_WORK;

//-----------------------------------------------------
/**
 *  トレイ描画関数群
 */
//-----------------------------------------------------
extern BOOL BoxAppView_TrayInit( TRAY_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys );
extern void BoxAppView_TrayQuit( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TraySetup( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayWrite( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int pos, BOOL iconWriteFlag );
extern void BoxAppView_TrayScrollSet( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int direction );
extern BOOL BoxAppView_TrayScrollWait( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayVBlank( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayMoveIconData( TRAY_VIEW_WORK* wk, u32 pos, s32 charpos, BOX_ICON_WORK* dst );
extern void BoxAppView_TrayPutIconData( TRAY_VIEW_WORK* wk, u32 pos, const BOX_ICON_WORK* icon );
extern BOX_ICON_WORK* BoxAppView_TrayGetIconData( TRAY_VIEW_WORK* wk, u32 pos );
extern void BoxAppView_TrayChangeWallPaperStart( TRAY_VIEW_WORK* wk );
extern BOOL BoxAppView_TrayChangeWallPaperWait( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayUpdateIcon( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayIconReleaseStart( TRAY_VIEW_WORK* wk, u32 pos );
extern BOOL BoxAppView_TrayIconReleaseWait( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayIconLimitModeSet( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayIconUpdateItem( TRAY_VIEW_WORK* wk, u32 pos, u32 itemNumber );
extern void BoxAppView_TrayIconMarkUpdate( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayIconAleaSelectUpdate( TRAY_VIEW_WORK* wk );
extern void BoxAppView_TrayIconAleaSelectQuit( TRAY_VIEW_WORK* wk );


/*============================================================================*/
/*  手持ちトレイ描画関連                                                      */
/*============================================================================*/
typedef struct {
	BOXAPP_VIEW_WORK*		vwk;
	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;
	const BOXAPP_VPARAM*	vpara;
	TRAY_VIEW_WORK*			trayWork;

	void*					scrnBuf;
	NNSG2dScreenData*		scrnData;

	void*					icon_move_work;
	fx32					icon_add_x;
	fx32					icon_add_y;

	u8						icon_closeup_poke_pos;
	u8						icon_closeup_poke_cnt;
	u8						icon_closeup_time;
	u8						tray_viewpos;
	BOOL					tray_taskflag;

	u32						scrnWriteXpos;
	int						iconXofs;

	BOX_ICON_SYS*			iconsys;
	BOX_ICON_WORK			icon[ TEMOTI_POKEMAX ];

	u8						mvseq;

}PARTY_VIEW_WORK;

extern BOOL BoxAppView_PartyInit( PARTY_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys );
extern void BoxAppView_PartyQuit( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyDisp( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyOpenStart( PARTY_VIEW_WORK* wk );
extern BOOL BoxAppView_PartyOpenWait( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyCloseStart( PARTY_VIEW_WORK* wk );
extern BOOL BoxAppView_PartyCloseWait( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyMoveIconData( PARTY_VIEW_WORK* wk, u32 pos, u32 charpos, BOX_ICON_WORK* dst );
extern void BoxAppView_PartyIconCloseupStart( PARTY_VIEW_WORK* wk );
extern BOOL BoxAppView_PartyIconCloseupWait( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyLastIconCloseupStart( PARTY_VIEW_WORK* wk );
extern BOOL BoxAppView_PartyLastIconCloseupWait( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyAddIconData( PARTY_VIEW_WORK* wk, u32 cursor_pos, const BOX_ICON_WORK* srcIcon );
extern void BoxAppView_PartySetIconData( PARTY_VIEW_WORK* wk, u32 cursor_pos, const BOX_ICON_WORK* srcIcon );
extern BOX_ICON_WORK* BoxAppView_PartyGetIconData( PARTY_VIEW_WORK* wk, u32 pos );
extern void BoxAppView_PartyPointIconAzuke( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyIconReleaseStart( PARTY_VIEW_WORK* wk, u32 pos );
extern BOOL BoxAppView_PartyIconReleaseWait( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyGetIconDispPos( PARTY_VIEW_WORK* wk, u32 pos, s32* x, s32* y );
extern void BoxAppView_PartyIconLimitModeSet( PARTY_VIEW_WORK* wk );
extern void BoxAppView_PartyIconUpdateItem( PARTY_VIEW_WORK* wk, u32 pos, u32 itemNumber );
extern void BoxAppView_PartyIconMarkUpdate( PARTY_VIEW_WORK* wk );


/*============================================================================*/
/*  カーソル描画関連                                                          */
/*============================================================================*/

/// カーソル描画処理ワーク
typedef struct {
	CLACT_SET_PTR		actsys;
	CLACT_WORK_PTR		act;
	CLACT_WORK_PTR		shadow_act;
	CLACT_WORK_PTR		arrow_act_L;
	CLACT_WORK_PTR		arrow_act_R;

	void*				cellBuf;
	void*				anmBuf;
	NNSG2dCellDataBank*	cellBank;
	NNSG2dAnimBankData*	anmBank;
	NNSG2dImageProxy	imgProxy;

	BOX_ICON_SYS*		iconSys;
	BOX_ICON_WORK		catch_icon[BOX_MAX_POS];

	struct {
		fx32   x;
		fx32   y;
	}iconOfs[BOX_MAX_POS];

	u32					catch_icon_count;

	TRAY_VIEW_WORK*		trayWork;
	PARTY_VIEW_WORK*	partyWork;
	ITEMICON_VIEW_WORK* itemIconWork;

	s32		xpos;
	s32		ypos;
	s32		next_xpos;
	s32		next_ypos;

	s32		move_x;
	s32		move_y;
	s32		add_x;
	s32		add_y;

	u8		move_seq;
	u8		area;
	u8		next_area;
	u8		move_timer;

	u8		move_taskflag;
	s8		tray_xpos;
	s8		tray_ypos;
	s8		party_pos;

	u8		catchicon_syncro_flag;
	u8		itemicon_syncro_flag;
	u8		shadow_syncro_flag;

	const BOXAPP_VPARAM*	vpara;
	BOXAPP_VIEW_WORK*		vwk;
}CURSOR_VIEW_WORK;


extern BOOL BoxAppView_CursorInit( CURSOR_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys );
extern void BoxAppView_CursorActSet( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorQuit( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorMoveStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorMoveWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorCatchWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorPutStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorPutWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorIconSwapStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorIconSwapWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorButtonPushActionStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorButtonPushActionWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorButtonReleaseActionStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorButtonReleaseActionWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorPriPartyMode( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorPriNormalMode( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchIconAzukeru( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchIconReleaseStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorCatchIconReleaseWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchIconLimitModeSet( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchIconUpdateItem( CURSOR_VIEW_WORK* wk, u32 itemNumber );
extern void BoxAppView_CursorIconMarkUpdate( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorExpertModeChange( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorAleaSelectStart( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorCatchAleaSelectStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorCatchAleaSelectWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorGetMatrix( CURSOR_VIEW_WORK* wk, VecFx32* mtx );
extern void BoxAppView_CursorItemCatchStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorItemCatchWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorItemSetStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorItemSetWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorItemSwapStart( CURSOR_VIEW_WORK* wk );
extern BOOL BoxAppView_CursorItemSwapWait( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorItemReleaseStart( CURSOR_VIEW_WORK* wk );
extern void BoxAppView_CursorItemReleaseEnd( CURSOR_VIEW_WORK* wk );
extern NNSG2dCellDataBank* BoxAppView_IconSys_GetCellBank( BOX_ICON_SYS* sys );
extern NNSG2dAnimBankData* BoxAppView_IconSys_GetAnimBank( BOX_ICON_SYS* sys );


/*============================================================================*/
/*  ボタン描画関連                                                            */
/*============================================================================*/
typedef struct {
	CLACT_SET_PTR		actsys;
	CLACT_WORK_PTR		act;

	void*				cellBuf;
	void*				anmBuf;
	NNSG2dCellDataBank*	cellBank;
	NNSG2dAnimBankData*	anmBank;
	NNSG2dImageProxy	imgProxy;


	CLACT_SET_PTR			actSys;
	const BOXAPP_VPARAM*	vpara;
	BOXAPP_VIEW_WORK*		vwk;

}BUTTON_VIEW_WORK;


extern BOOL BoxAppView_ButtonInit( BUTTON_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys );
extern void BoxAppView_ButtonActSet( BUTTON_VIEW_WORK* wk );
extern void BoxAppView_ButtonQuit( BUTTON_VIEW_WORK* wk );


typedef enum {
	BUTTON_STATE_INIT,
	BUTTON_STATE_PARTY_PUSH,
	BUTTON_STATE_CLOSE_PUSH,
}BOXAPPVIEW_BUTTON_STATE;
extern void BoxAppView_ButtonStateChange( BUTTON_VIEW_WORK* wk, BOXAPPVIEW_BUTTON_STATE state );


/*============================================================================*/
/*  ステータス描画関連                                                        */
/*============================================================================*/
typedef struct {
	BOOL					enableFlag;

	GF_BGL_BMPWIN*			bmpwin;
	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;
	const BOXAPP_VPARAM*	vpara;
	BOXAPP_VIEW_WORK*		vwk;

	NUMFONT*				numfontNo;
	NUMFONT*				numfontLv;

	SOFT_SPRITE_MANAGER*	spriteMan;
	SOFT_SPRITE*			sprite;

	void*					infobackCellBuf;
	NNSG2dCellDataBank*		infobackCellData;
	CLACT_WORK_PTR			infobackAct;

	void*					typeIconCellBuf;
	NNSG2dCellDataBank*		typeIconCellData;
	CLACT_WORK_PTR			typeIconAct[2];

	STRBUF*					strMale;
	STRBUF*					strFemale;

	TCB_PTR					task;

	u16		infoTimer;

}STATUS_VIEW_WORK;

extern BOOL BoxAppView_StatusInit( STATUS_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys, const MSGDATA_MANAGER* msgman );
extern void BoxAppView_StatusQuit( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusSetup( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusUpdate( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusUpdateStart( STATUS_VIEW_WORK* wk );
extern BOOL BoxAppView_StatusUpdateWait( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusMarkUpdate( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusVBlank( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusUpdateItemInfo( STATUS_VIEW_WORK* wk );
extern void BoxAppView_StatusUpdateClear( STATUS_VIEW_WORK* wk );
extern void BoxAppView_Status_StartSoftSpritePreparation( STATUS_VIEW_WORK* wk );
extern BOOL BoxAppView_Status_WaitSoftSpritePreparation( STATUS_VIEW_WORK* wk );

/*============================================================================*/
/*  メッセージ描画関連                                                        */
/*============================================================================*/

#define BOX_MSG_MAXLEN		(64)

typedef struct {

	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;
	const BOXAPP_VPARAM*	vpara;
	BOXAPP_VIEW_WORK*		vwk;
	MSGDATA_MANAGER*		msgman_boxmes;
	MSGDATA_MANAGER*		msgman_boxmenu;

	GF_BGL_BMPWIN*			bmpwin;
	u16						msgwin_disp_flag;
	u16						menuwin_disp_flag;
	int						wintype;

	void*					markCharBuf;
	NNSG2dCharacterData*	markCharData;

	const WORDSET*  wordset;
	STRBUF*		buf;
	STRBUF*		expand_buf;

}MSG_VIEW_WORK;

extern BOOL BoxAppView_MsgInit( MSG_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys,
	 MSGDATA_MANAGER* msgman_boxmes, const WORDSET* wordset, int winType );
extern void BoxAppView_MsgQuit( MSG_VIEW_WORK* wk );
extern void BoxAppView_MsgSetup( MSG_VIEW_WORK* wk );
extern void BoxAppView_MsgWrite( MSG_VIEW_WORK* wk, u32 msg_id );
extern void BoxAppView_MenuWrite( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu );
extern void BoxAppView_MsgClear( MSG_VIEW_WORK* wk );
extern void BoxAppView_MenuClear( MSG_VIEW_WORK* wk );
extern void BoxAppView_MenuCursorUpdate( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu );
extern void BoxAppView_MenuMarkUpdate( MSG_VIEW_WORK* wk, const BOXAPP_MENU* menu );

/*============================================================================*/
/*  特殊ウィンドウ描画関連                                                    */
/*============================================================================*/
enum {
	TRAYICON_CHAR_BYTESIZE = OBJCHAR_TRAYICON_SIZE * 0x20,

	TRAYICON_FADE_MAX = 8,
	TRAYICON_PAL_COLOR_NUM = 0x10*3,
	TRAYICON_PAL_SIZE = (TRAYICON_PAL_COLOR_NUM*sizeof(u16)),
};

typedef struct {
	BOXAPP_VIEW_WORK*		vwk;
	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;
	const BOXAPP_VPARAM*	vpara;
	GF_BGL_BMPWIN*			bmpwin;

	void*					iconCharBuf;
	NNSG2dCharacterData*	iconCharData;
	void*					iconCellBuf;
	NNSG2dCellDataBank*		iconCellData;
	void*					iconAnimBuf;
	NNSG2dAnimBankData*		iconAnimData;

	void*					jumpwinScrnBuf;
	NNSG2dScreenData*		jumpwinScrnData;
	void*					itemwinScrnBuf;
	NNSG2dScreenData*		itemwinScrnData;

	BMPPRT_HEADER			trayIconBmpHeader;
	NUMFONT*				numfont;
	CLACT_WORK_PTR			trayIconAct[ BOX_MAX_TRAY ];
	CLACT_WORK_PTR			itemIconAct;
	u32						pokeCount[ BOX_MAX_TRAY ];
	TCB_PTR					effectTask;
	s32						center_trayno;

	u16						trayIconPalBuf[ TRAYICON_FADE_MAX ][ TRAYICON_PAL_COLOR_NUM ];

	u8						trayIconCharBuf[ BOX_MAX_TRAY ][ TRAYICON_CHAR_BYTESIZE ];
	u8						trayIconCharCreateFlag[ BOX_MAX_TRAY ];

	MSGDATA_MANAGER*		mm_itemInfo;
	STRBUF*					tmpbuf;

}EXWIN_VIEW_WORK;

extern BOOL BoxAppView_ExWinInit( EXWIN_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys );
extern void BoxAppView_ExWinSetup( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWinQuit( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWin_JumpWinDispStart( EXWIN_VIEW_WORK* wk );
extern BOOL BoxAppView_ExWin_JumpWinDispWait( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWin_JumpWinUpdate( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWin_JumpWinDelStart( EXWIN_VIEW_WORK* wk );
extern BOOL BoxAppView_ExWin_JumpWinDelWait( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWin_ItemInfoWinDispStart( EXWIN_VIEW_WORK* wk );
extern BOOL BoxAppView_ExWin_ItemInfoWinDispWait( EXWIN_VIEW_WORK* wk );
extern void BoxAppView_ExWin_ItemInfoWinClearStart( EXWIN_VIEW_WORK* wk );
extern BOOL BoxAppView_ExWin_ItemInfoWinClearWait( EXWIN_VIEW_WORK* wk );


extern void BoxAppView_ExWin_TransTrayIconCharData( EXWIN_VIEW_WORK* wk, u32 trayno, u32 charpos, NNS_G2D_VRAM_TYPE vramType, NNSG2dImageProxy* proxy );
extern NNSG2dCellDataBank* BoxAppView_ExWin_GetTrayIconCellDataAdrs( EXWIN_VIEW_WORK* wk );

/*============================================================================*/
/*  リールコントロール関連                                                    */
/*============================================================================*/

typedef struct _REEL_VIEW_WORK	REEL_VIEW_WORK;

extern BOOL BoxAppView_Reel_Init( REEL_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys );
extern void BoxAppView_Reel_Quit( REEL_VIEW_WORK* wk );
extern void BoxAppView_Reel_Setup( REEL_VIEW_WORK* wk );
extern void BoxAppView_Reel_ChangeState( REEL_VIEW_WORK* wk );
extern BOOL BoxAppView_Reel_ChangeStateWait( REEL_VIEW_WORK* wk );
extern void BoxAppView_Reel_DispIcon( REEL_VIEW_WORK* wk );
extern BOOL BoxAppView_Reel_DispIconWait( REEL_VIEW_WORK* wk );
extern void BoxAppView_Reel_MoveIcon( REEL_VIEW_WORK* wk );
extern BOOL BoxAppView_Reel_MoveIconWait( REEL_VIEW_WORK* wk );
extern void BoxAppView_Reel_MarkIconUpdate( REEL_VIEW_WORK* wk );

/*============================================================================*/
/*  つよさくらべ関連                                                           */
/*============================================================================*/
typedef struct _COMPARE_VIEW_WORK	COMPARE_VIEW_WORK;

extern BOOL BoxAppView_CompareInit( COMPARE_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys, MSGDATA_MANAGER* msgman );
extern void BoxAppView_CompareQuit( COMPARE_VIEW_WORK* wk );
extern void BoxAppView_SetupCompare( COMPARE_VIEW_WORK* wk );
extern void BoxAppView_Compare_SwitchSide( COMPARE_VIEW_WORK* wk, BOOL buttonAnmFlag );
extern void BoxAppView_Compare_StartUpdate( COMPARE_VIEW_WORK* wk );
extern BOOL BoxAppView_Compare_WaitUpdate( COMPARE_VIEW_WORK* wk );
extern void BoxAppView_Compare_ChangePage( COMPARE_VIEW_WORK* wk );
extern BOOL BoxAppView_Compare_WaitChangePage( COMPARE_VIEW_WORK* wk );

/*============================================================================*/
/*  描画メイン                                                                */
/*============================================================================*/
extern TCB_PTR BoxAppView_VTaskAdd(TCB_FUNC func, void* wk_adrs, u32 pri );

extern NNSG2dImagePaletteProxy* BoxAppView_GetObjPlttProxy( BOXAPP_VIEW_WORK* vwk );

extern BOX_ICON_SYS* BoxAppView_GetIconSysWork( BOXAPP_VIEW_WORK* vwk );
extern TRAY_VIEW_WORK* BoxAppView_GetTrayViewWork( BOXAPP_VIEW_WORK* vwk );
extern PARTY_VIEW_WORK* BoxAppView_GetPartyViewWork( BOXAPP_VIEW_WORK* vwk );
extern EXWIN_VIEW_WORK* BoxAppView_GetExWinViewWork( BOXAPP_VIEW_WORK* vwk );
extern CURSOR_VIEW_WORK* BoxAppView_GetCursorWork( BOXAPP_VIEW_WORK* vwk );
extern ITEMICON_VIEW_WORK* BoxAppView_GetItemIconWork( BOXAPP_VIEW_WORK* vwk );
extern int BoxAppView_GetTrayScrollOfs( BOXAPP_VIEW_WORK* vwk );

extern void BoxAppView_SetActHeader( CLACT_HEADER* header, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* pltProxy,
					NNSG2dCellDataBank* cellBank, NNSG2dCellAnimBankData* anmBank, u32 bgPri );

extern CLACT_WORK_PTR BoxAppView_AddActor( CLACT_SET_PTR  actSys, CLACT_HEADER_PTR  actHeader, u32 x, u32 y, u32 actPri, int drawArea);
extern void BoxAppView_ChangeDrawPriority( CLACT_WORK_PTR act, u32 pri );

extern SOFT_SPRITE_MANAGER* BoxAppView_GetSpriteManager( BOXAPP_VIEW_WORK* vwk );
extern void BoxAppView_PalFade( const u16* src, u16* dst, u32 colNum, u16 colCode, u32 step );




typedef void (*pMemoryFreeTaskCallBack)(void*);
extern void BoxAppView_IrqMemoryFreeReq( void* memory, pMemoryFreeTaskCallBack callback, void* arg );


#endif
