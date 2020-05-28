//============================================================================================
/**
 * @file	pms_input_view.h
 * @bfief	簡易会話入力画面（描画メイン－下請け参照ヘッダ）
 * @author	taya
 * @date	06.02.07
 */
//============================================================================================
#ifndef __PMS_INPUT_VIEW_H__
#define __PMS_INPUT_VIEW_H__

#include "gflib\tcb.h"
#include "system\fontproc.h"
#include "pmsi.naix"


#define  PMSI_FPS_60		// これが有効だと各種エフェクトを60fpsで動かす

#ifdef PMSI_FPS_60
#define  PMSI_FRAME_RATIO	(2)
#else
#define  PMSI_FRAME_RATIO	(1)
#endif

#define  PMSI_FRAMES(n)		((n)*PMSI_FRAME_RATIO)
#define  PMSI_ANM_SPEED		((FX32_ONE*2)/PMSI_FRAME_RATIO)

//============================================================================================
//============================================================================================


//------------------------------------------------
/**
 * フレーム割り振り
 */ 
//------------------------------------------------
enum {
	FRM_MAIN_EDITAREA =  GF_BGL_FRAME0_M,
	FRM_MAIN_CATEGORY =  GF_BGL_FRAME1_M,
	FRM_MAIN_WORDWIN  =  GF_BGL_FRAME2_M,
	FRM_MAIN_BUTTON   =  GF_BGL_FRAME3_M,

	FRM_SUB_BG = GF_BGL_FRAME0_S,

	FRM_MAIN_EDITAREA_BLENDMASK = GX_BLEND_PLANEMASK_BG0,
	FRM_MAIN_CATEGORY_BLENDMASK = GX_BLEND_PLANEMASK_BG1,
	FRM_MAIN_WORDWIN_BLENDMASK  = GX_BLEND_PLANEMASK_BG2,
	FRM_MAIN_BUTTON_BLENDMASK   = GX_BLEND_PLANEMASK_BG3,

	FRM_MAIN_EDITAREA_WNDMASK  = GX_WND_PLANEMASK_BG0,
	FRM_MAIN_CATEGORY_WNDMASK  = GX_WND_PLANEMASK_BG1,
	FRM_MAIN_WORDWIN_WNDMASK   = GX_WND_PLANEMASK_BG2,
	FRM_MAIN_BUTTON_WNDMASK    = GX_WND_PLANEMASK_BG3,

};
//------------------------------------------------
/**
 * パレット割り振り
 */ 
//------------------------------------------------
enum {
	PALNUM_MAIN_EDITAREA = 0x00,
	PALNUM_MAIN_CATEGORY = 0x0b,
	PALNUM_MAIN_WORDWIN  = 0x0c,
	PALNUM_MAIN_BUTTON   = 0x0d,
	PALNUM_MAIN_SYSWIN   = 0x0e,
	PALNUM_MAIN_TALKWIN  = 0x0f,

	PALNUM_TRANS_MAX = PALNUM_MAIN_BUTTON,
};

//------------------------------------------------
/**
 * 使用フォント
 */ 
//------------------------------------------------
enum {
	PMSI_FONT_EDITAREA_BASE = FONT_TALK,
	PMSI_FONT_EDITAREA_WORD = FONT_TALK,
	PMSI_FONT_BUTTON = FONT_SYSTEM,
	PMSI_FONT_CATEGORY = FONT_SYSTEM,
	PMSI_FONT_WORDWIN = FONT_SYSTEM,
	PMSI_FONT_MESSAGE = FONT_TALK,
	PMSI_FONT_YESNO = FONT_SYSTEM,
};


//------------------------------------------------
/**
 * LCD
 */ 
//------------------------------------------------
enum {
	PMSIV_LCD_MAIN = 0,
	PMSIV_LCD_SUB,
};

enum {
	BGPRI_MAIN_EDITAREA = 0,
	BGPRI_MAIN_CATEGORY,
	BGPRI_MAIN_WORDWIN,
	BGPRI_MAIN_BUTTON,

	BGPRI_SUB_BASE = 0,
};

enum {
	ACTPRI_EDITAREA_CURSOR,
	ACTPRI_EDITAREA_ARROW,
	ACTPRI_CATEGORY_CURSOR,
	ACTPRI_WORDWIN_CURSOR,
	ACTPRI_WORDWIN_ARROW,
	ACTPRI_BUTTON_CURSOR,
};

enum {
	ANM_EDITAREA_CURSOR_ACTIVE,
	ANM_EDITAREA_CURSOR_STOP,
	ANM_BUTTON_CURSOR_ACTIVE,
	ANM_BUTTON_CURSOR_STOP,
	ANM_CATEGORY_CURSOR_ACTIVE,
	ANM_CATEGORY_CURSOR_STOP,
	ANM_INITIAL_CURSOR_ACTIVE,
	ANM_INITIAL_CURSOR_STOP,
	ANM_WORDWIN_CURSOR_ACTIVE,
	ANM_WORDWIN_CURSOR_STOP,

	ANM_WORD_ARROW_DOWN,
	ANM_WORD_ARROW_UP,
	ANM_EDITAREA_ARROW_RIGHT,
	ANM_EDITAREA_ARROW_LEFT,

	ANM_EDITAREA_ALLCOVER_CURSOR_ACTIVE,
	ANM_EDITAREA_ALLCOVER_CURSOR_STOP,

	ANM_CATEGORY_BACK_CURSOR_ACTIVE,
	ANM_CATEGORY_BACK_CURSOR_STOP,

};


extern TCB_PTR  PMSIView_AddVTask( TCB_FUNC func, void* wk, int pri );
extern GF_BGL_INI*  PMSIView_GetBGL( PMS_INPUT_VIEW* vwk );
extern CLACT_SET_PTR  PMSIView_GetActSys( PMS_INPUT_VIEW* vwk );
extern NNSG2dImageProxy*  PMSIView_GetObjImageProxy( PMS_INPUT_VIEW* vwk, int lcd );
extern NNSG2dImagePaletteProxy*  PMSIView_GetObjPaletteProxy( PMS_INPUT_VIEW* vwk, int lcd );
extern void PMSIView_SetupDefaultActHeader( PMS_INPUT_VIEW* vwk, CLACT_HEADER* header, u32 lcd, u32 bgpri );
extern CLACT_WORK_PTR PMSIView_AddActor( PMS_INPUT_VIEW* vwk, CLACT_HEADER* header, u32 x, u32 y, u32 actpri, int drawArea );


//================================================================================
//  入力欄処理
//================================================================================
typedef struct _PMSIV_EDIT		PMSIV_EDIT;

extern PMSIV_EDIT*  PMSIV_EDIT_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk );
extern void PMSIV_EDIT_Delete( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_SetupGraphicDatas( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_UpdateEditArea( PMSIV_EDIT* wk );

extern void PMSIV_EDIT_StopCursor( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_ActiveCursor( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_MoveCursor( PMSIV_EDIT* wk, int pos );
extern void PMSIV_EDIT_VisibleCursor( PMSIV_EDIT* wk, BOOL flag );

extern void PMSIV_EDIT_SetSystemMessage( PMSIV_EDIT* wk, u32 msg_type );
extern void PMSIV_EDIT_DispYesNoWin( PMSIV_EDIT* wk, int cursor_pos );
extern void PMSIV_EDIT_MoveYesNoCursor( PMSIV_EDIT* wk, int pos );
extern void PMSIV_EDIT_EraseYesNoWin( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_StopArrow( PMSIV_EDIT* wk );
extern void PMSIV_EDIT_ActiveArrow( PMSIV_EDIT* wk );


extern u32 PMSIV_EDIT_GetWordPosMax( const PMSIV_EDIT* wk );

//================================================================================
//  コマンドボタン処理
//================================================================================
typedef struct _PMSIV_BUTTON	PMSIV_BUTTON;

extern PMSIV_BUTTON*  PMSIV_BUTTON_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk );
extern void PMSIV_BUTTON_Delete( PMSIV_BUTTON* wk );
extern void PMSIV_BUTTON_SetupGraphicDatas( PMSIV_BUTTON* wk );

extern void PMSIV_BUTTON_StopCursor( PMSIV_BUTTON* wk );
extern void PMSIV_BUTTON_ActiveCursor( PMSIV_BUTTON* wk );
extern void PMSIV_BUTTON_MoveCursor( PMSIV_BUTTON* wk, int pos );
extern void PMSIV_BUTTON_VisibleCursor( PMSIV_BUTTON* wk, BOOL flag );
extern BOOL PMSIV_BUTTON_GetCursorVisibleFlag( PMSIV_BUTTON* wk );
extern void PMSIV_BUTTON_Hide( PMSIV_BUTTON* wk );
extern void PMSIV_BUTTON_Appear( PMSIV_BUTTON* wk );

//================================================================================
//  カテゴリウィンドウ処理
//================================================================================
typedef struct _PMSIV_CATEGORY	PMSIV_CATEGORY;

extern PMSIV_CATEGORY*  PMSIV_CATEGORY_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk );
extern void PMSIV_CATEGORY_Delete( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_SetupGraphicDatas( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_StartEnableBG( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitEnableBG( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_StartDisableBG( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitDisableBG( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_VisibleCursor( PMSIV_CATEGORY* wk, BOOL flag );
extern void PMSIV_CATEGORY_MoveCursor( PMSIV_CATEGORY* wk, u32 pos );
extern void PMSIV_CATEGORY_StartFadeOut( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitFadeOut( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_StartFadeIn( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitFadeIn( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_SetDisableBG( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_ChangeModeBG( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_StartModeChange( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitModeChange( PMSIV_CATEGORY* wk );
extern void PMSIV_CATEGORY_StartBrightDown( PMSIV_CATEGORY* wk );
extern BOOL PMSIV_CATEGORY_WaitBrightDown( PMSIV_CATEGORY* wk );


//================================================================================
//  単語ウィンドウ処理
//================================================================================
typedef struct _PMSIV_WORDWIN	PMSIV_WORDWIN;

extern PMSIV_WORDWIN*  PMSIV_WORDWIN_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk );
extern void PMSIV_WORDWIN_Delete( PMSIV_WORDWIN* wk );
extern void PMSIV_WORDWIN_SetupGraphicDatas( PMSIV_WORDWIN* wk );
extern void PMSIV_WORDWIN_SetupWord( PMSIV_WORDWIN* wk );
extern void PMSIV_WORDWIN_StartFadeIn( PMSIV_WORDWIN* wk );
extern BOOL PMSIV_WORDWIN_WaitFadeIn( PMSIV_WORDWIN* wk );
extern void PMSIV_WORDWIN_VisibleCursor( PMSIV_WORDWIN* wk, BOOL flag );
extern void PMSIV_WORDWIN_MoveCursor( PMSIV_WORDWIN* wk, u32 pos );
extern void PMSIV_WORDWIN_StartScroll( PMSIV_WORDWIN* wk, int vector );
extern BOOL PMSIV_WORDWIN_WaitScroll( PMSIV_WORDWIN* wk );
extern void PMSIV_WORDWIN_StartFadeOut( PMSIV_WORDWIN* wk );
extern BOOL PMSIV_WORDWIN_WaitFadeOut( PMSIV_WORDWIN* wk );


//================================================================================
//  サブ画面処理
//================================================================================
typedef struct _PMSIV_SUB	PMSIV_SUB;

enum {
	SUB_BUTTON_UP,
	SUB_BUTTON_DOWN,
};
enum {
	SUB_BUTTON_STATE_RELEASE,
	SUB_BUTTON_STATE_HOLD,
};

extern PMSIV_SUB*  PMSIV_SUB_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk );
extern void PMSIV_SUB_Delete( PMSIV_SUB* wk );
extern void PMSIV_SUB_SetupGraphicDatas( PMSIV_SUB* wk );
extern void PMSIV_SUB_ChangeCategoryButton( PMSIV_SUB* wk );
extern BOOL PMSIV_SUB_WaitChangeCategoryButton( PMSIV_SUB* wk );
extern void PMSIV_SUB_VisibleArrowButton( PMSIV_SUB* wk, BOOL flag );
extern void PMSIV_SUB_ChangeArrowButton( PMSIV_SUB* wk, int pos, int state );

#endif
