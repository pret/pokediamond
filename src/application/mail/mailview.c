/**
 *	@file	mailview.c
 *	@brief	メール画面描画ルーチン
 *	@author	MiyukiIwasawa
 *	@date	06.02.08
 */

#include "common.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/brightness.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/palanm.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/font_arc.h"
#include "system/winframe.naix"
#include "poketool/pokeicon.h"
#include "poketool/monsno.h"
#include "msgdata/msg.naix"
#include "communication/communication.h"

#include "savedata/mail.h"
#include "savedata/config.h"
#include "application/mail/mail_param.h"
#include "application/mail/mailview.h"
#include "application/mail/mailview.dat"
#include "application/mail/mail_gra.naix"
#include "msgdata/msg_mailview.h"
#include "mail_snd_def.h"

#define MAILD_CHAR_S	(NARC_mail_gra_mail_000_ncgr)
#define MAILD_SCRN_S	(NARC_mail_gra_mail_000_nscr)
#define MAILD_PLTT_S	(NARC_mail_gra_mail_000_nclr)
#define MAILD_SCRN_FIL	(NARC_mail_gra_mail_scr_nscr)

#define WINCLR_COL(col)	(((col)<<4)|(col))

enum{
 MAILVIEW_BLACKSET,
 MAILVIEW_RESINIT,
 MAILVIEW_FADEIN,
 MAILVIEW_MAIN,
 MAILVIEW_FADEOUT,
 MAILVIEW_RESRELEASE,
};

enum{
 KEYIN_VIEW,
 KEYIN_CREATE,
 KEYIN_NOMSG,
 KEYIN_CANCEL
}KEYIN;

enum{
 WIN_M01,
 WIN_M02,
 WIN_M03,
 WIN_YN01,
 WIN_YN02,
 WIN_TALK,
 WIN_MAX,
};
enum{
 VIEW_SIDE_DECIDE,
 VIEW_SIDE_CANCEL,
};

#define VIEW_LINE_END	(3)
#define VIEW_LINE_MAX	(4)
#define VIEW_BUFLEN_MSG	(19*2*2)
#define VIEW_TALK_FCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE))
#define VIEW_NRM_FCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL))

///メール描画メインワーク
typedef struct _MAIL_VIEW_DATA{
	int	heapID;
	int	seq;		///<メインシーケンスNo
	u16	sub_seq;	///<サブシーケンスNo
	u16	win_type;	///<ウィンドウタイプ
	u8	mode;	///<動作タイプ
	u8	inMode;	///<動作タイプ
	u8	cntNo;
	u8	msgIdx;

	u8	msg_spd;
	u8	line;	///<選択ライン
	u8	side;	///<サイド選択
	u8	canm_f;	///<アニメフックフラグ
	u8	colEvy;
	u8	colDir;
	u8	nowCol;
	u8	oldCol;

	GF_BGL_INI *bgl;	///<BGLデータ

	MAIL_TMP_DATA	*dat;
	MSGDATA_MANAGER*	pMsgMan;
	STRBUF	*pMsg[MAILDAT_MSGMAX];
	PALETTE_FADE_PTR	palAnm;

	///グラフィックリソース
	void*	pScrBuf01;
	void*	pScrBuf02;
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr02;
	GF_BGL_BMPWIN	win[WIN_MAX];
	BMPMENU_WORK*	ynmenu_wk;
	
	CATS_SYS_PTR	pActSys;	///<セルアクターシステム
	CATS_RES_PTR	pActRes;	///<セルアクターリソース
	CATS_ACT_PTR	pAct[MAILDAT_ICONMAX];		///<アクター
}MAIL_VIEW_DAT;

///サブプロセス定義用関数型
typedef int (*MailKeyIn)(MAIL_VIEW_DAT* wk);

//=================================================
//プロトタイプ
//=================================================
static int MailViewMain(MAIL_VIEW_DAT* wk);

static int MailView_KeyInView(MAIL_VIEW_DAT* wk);
static int MailView_KeyInCreate(MAIL_VIEW_DAT* wk);
static int MailView_KeyInCancel(MAIL_VIEW_DAT* wk);

static void MailView_PltAnime(TCB_PTR tcb,void* work);
static int MailViewResInit(MAIL_VIEW_DAT* wk);
static int MailViewResRelease(MAIL_VIEW_DAT* wk);

static void MailVBlank(void * work);
static void MailView_VBankSet(void);
static void MailView_BGLInit(MAIL_VIEW_DAT* wk);
static void MailView_BGLRelease(MAIL_VIEW_DAT* wk);
static void MailView_2DGraInit(MAIL_VIEW_DAT* wk);
static void MailView_2DGraRelease(MAIL_VIEW_DAT* wk);
static void MailView_BmpWinInit(MAIL_VIEW_DAT* wk);
static void MailView_BmpWinRelease(MAIL_VIEW_DAT* wk);
static void MailView_MsgWrite(MAIL_VIEW_DAT* wk);

static void MailView_PokeIconInit(MAIL_VIEW_DAT* wk);
static void MailView_PokeIconRelease(MAIL_VIEW_DAT* wk);

//====================================================================
//プロセス定義
//====================================================================
PROC_RESULT MailViewProc_Init( PROC *proc,int *seq);
PROC_RESULT MailViewProc_Main( PROC *proc,int *seq);
PROC_RESULT MailViewProc_End( PROC *proc,int *seq);

/**
 *	@brief	メール描画呼び出し　初期化
 */
PROC_RESULT MailViewProc_Init(PROC* proc,int* seq)
{
	MAIL_TMP_DATA* tp;
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)PROC_GetWork(proc);

	//ワークエリア取得
	HeapStatePush();

	//ヒープ作成
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_MAILVIEW,0x20000);
	wk = PROC_AllocWork(proc,sizeof(MAIL_VIEW_DAT),HEAPID_MAILVIEW);
	memset(wk,0,sizeof(MAIL_VIEW_DAT));

	//ヒープID保存
	wk->heapID = HEAPID_MAILVIEW;

	//パラメータ引継ぎ
	wk->dat = (MAIL_TMP_DATA*)PROC_GetParentWork(proc);
	wk->inMode = wk->mode = wk->dat->val;	//描画タイプ
	wk->line = wk->dat->cntNo;
	wk->side = wk->dat->flags;
	wk->oldCol = wk->nowCol = wk->line;
	wk->dat->val = VIEW_END_CANCEL;

	wk->msg_spd = CONFIG_GetMsgPrintSpeed(wk->dat->configSave);
	wk->win_type = CONFIG_GetWindowType(wk->dat->configSave);
	return PROC_RES_FINISH;
};


/**
 *	@brief	メール描画呼び出し　メイン
 */
PROC_RESULT MailViewProc_Main(PROC* proc,int* seq)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)PROC_GetWork(proc);

	if(MailViewMain(wk)){
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	メール描画呼び出し	終了　
 */
PROC_RESULT MailViewProc_End(PROC* proc,int* seq)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)PROC_GetWork(proc);
	int heap;
	
	//終了パラメータ格納
	heap = wk->heapID;
	
	//ワークエリア解放
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(heap);

	sys_DeleteHeap(heap);

	return PROC_RES_FINISH;
}


//====================================================================
//ローカル関数定義
//====================================================================
//
/**
 *	@brief	会話文が全文空かどうかチェック
 *
 *	@retval	TRUE	全文空
 *	@retval FALSE	入力有り
 */
static BOOL MailView_IsWordNull(MAIL_VIEW_DAT* wk)
{
	int i = 0;

	for(i = 0;i < MAILDAT_MSGMAX;i++){
		if(PMSDAT_IsEnabled(&wk->dat->msg[i])){
			return FALSE;
		}
	}
	return TRUE;
}

/**
 *	@brief	メール描画　キー取得(Viewモード)
 */
static int MailView_KeyInView(MAIL_VIEW_DAT* wk)
{
	if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
		Snd_SePlay(SND_MAIL_FINISH);
		return 1;
	}
	return 0;
}
/**
 *	@brief	メール描画　キー取得(Createモード)
 */
static int MailView_KeyInCreate(MAIL_VIEW_DAT* wk)
{
	u8 se_play = 0;
	
	if(sys.trg & (PAD_BUTTON_DECIDE)){
		if(wk->line == VIEW_END_DECIDE){
			if(wk->side == VIEW_SIDE_DECIDE){
				//会話文が空かどうかチェック
				if(MailView_IsWordNull(wk)){
					Snd_SePlay(SND_MAIL_CANCEL);
					wk->mode = KEYIN_NOMSG;
					return FALSE;
				}else{
					wk->dat->val = VIEW_END_DECIDE;
					Snd_SePlay(SND_MAIL_FINISH);
				}
			}else{
				Snd_SePlay(SND_MAIL_CANCEL);
				wk->mode = KEYIN_CANCEL;
				return FALSE;
			}
			wk->dat->cntNo = wk->dat->flags = 0;
		}else{
			wk->dat->val = wk->dat->cntNo = wk->line;
			wk->dat->flags = wk->side;
			Snd_SePlay(SND_MAIL_DECIDE);
		}
		return TRUE;
	}else if(sys.trg & (PAD_BUTTON_CANCEL)){
		Snd_SePlay(SND_MAIL_CANCEL);
		wk->mode = KEYIN_CANCEL;
		return FALSE;
	}

	//選択項目変更
	if(sys.trg & (PAD_BUTTON_START)){
		//一発で「決定」へ
		wk->line = VIEW_END_DECIDE;
		wk->side = VIEW_SIDE_DECIDE;
//		wk->nowCol = wk->line+wk->side;
		se_play = 1;
	}else if(sys.trg & (PAD_KEY_DOWN)){
		wk->line = (wk->line + 1)%VIEW_LINE_MAX;
//		wk->nowCol = wk->line;
		se_play = 1;
	}else if(sys.trg & (PAD_KEY_UP)){
		wk->line = (wk->line+VIEW_LINE_MAX-1)%VIEW_LINE_MAX;
//		wk->nowCol = wk->line;
		se_play = 1;
	}else if(sys.trg & (PAD_KEY_RIGHT | PAD_KEY_LEFT)){
		if(wk->line == VIEW_LINE_END){
			wk->side ^= 1;
//			wk->nowCol = wk->line+wk->side;
			se_play = 1;
		}
	}else{
		return FALSE;
	}

	if(!se_play){
		return FALSE;
	}
	//選択ライン描画変更
	Snd_SePlay(SND_MAIL_SELECT);

	if(wk->line == VIEW_LINE_END){
		wk->nowCol = wk->line+wk->side;
	}else{
		wk->nowCol = wk->line;
	}
	return FALSE;
}

/**
 *	@brief	メール描画キー取得　メッセージ待ちモード
 */
static int MailView_KeyInMsg(MAIL_VIEW_DAT* wk)
{
	STRBUF* str = NULL;
	
	switch(wk->sub_seq){
	case 0:
		//空はダメメッセージ描画開始
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL	);
		
		GF_BGL_BmpWinDataFill(&(wk->win[WIN_TALK]),WINCLR_COL(FBMP_COL_WHITE));

		str = STRBUF_Create(VIEW_BUFLEN_MSG,wk->heapID);
		MSGMAN_GetString(wk->pMsgMan,msg_mail_nozero,str);
		GF_STR_PrintColor(
			&wk->win[WIN_TALK],FONT_TALK,str,
			0,0,MSG_ALLPUT,VIEW_TALK_FCOL,NULL);
		STRBUF_Delete(str);
		break;
	case 1:
		//キー待ち
		if(!(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))){
			return FALSE;
		}
		BmpTalkWinClear( &wk->win[WIN_TALK],WINDOW_TRANS_OFF);
		GF_BGL_BmpWinOff(&(wk->win[WIN_TALK]));

		wk->sub_seq = 0;
		wk->mode = wk->inMode;	//モードを元に戻す 
		return FALSE;
	}
	wk->sub_seq++;
	return FALSE;
}

/**
 *	@brief	YNウィンドウ初期化
 */
static void yesNoInit(MAIL_VIEW_DAT* wk)
{
	static const BMPWIN_DAT YesNoBmpWin = {
		BMPL_YESNO_FRM,BMPL_YESNO_PX,BMPL_YESNO_PY,BMPL_YESNO_SX,BMPL_YESNO_SY,
		BMPL_YESNO_PAL,BMPL_YESNO_CGX
	};

	wk->ynmenu_wk = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, wk->heapID);
}
/**
 *	@brief	YNウィンドウ選択待ち
 */
static int yesNoWait(MAIL_VIEW_DAT* wk)
{
	switch( BmpYesNoSelectMain( wk->ynmenu_wk, wk->heapID) ){
	case 0:	//はい
//		Snd_SePlay(PORUC_SE_DECIDE);
		return TRUE;
	case BMPMENU_CANCEL: //いいえ
//		Snd_SePlay(PORUC_SE_DECIDE);
		return FALSE;
	}
	return -1;
}

static int MailView_KeyInCancel(MAIL_VIEW_DAT* wk)
{
	int ret;
	STRBUF* str = NULL;
	
	switch(wk->sub_seq){
	case 0:
		wk->canm_f = 1;
		//やめますかメッセージ描画開始
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL	);
		GF_BGL_BmpWinDataFill(&(wk->win[WIN_TALK]),WINCLR_COL(FBMP_COL_WHITE));

		str = STRBUF_Create(VIEW_BUFLEN_MSG,wk->heapID);
		MSGMAN_GetString(wk->pMsgMan,msg_mail_cmsg,str);
		wk->msgIdx = GF_STR_PrintColor(
			&wk->win[WIN_TALK],FONT_TALK,str,
			0,0,wk->msg_spd,VIEW_TALK_FCOL,NULL);
		STRBUF_Delete(str);

		//カラーアニメを一旦もとの色に戻す
		SoftFadePfd(wk->palAnm,FADE_MAIN_BG,PALANM_STARTPAL+wk->oldCol,1,0,0x7FFF);
		wk->oldCol = wk->nowCol;
		wk->colDir = 0;
		wk->colEvy = 0;
		break;
	case 1:
		//描画終了待ち
		if( GF_MSG_PrintEndCheck( wk->msgIdx )){
			return FALSE;
		}
		//YNウィンドウ初期化
		yesNoInit(wk);
		break;
	case 2:
		//選択待ち
		ret = yesNoWait(wk);
		if(ret < 0){
			return FALSE;
		}
		BmpTalkWinClear( &wk->win[WIN_TALK],WINDOW_TRANS_OFF);
		GF_BGL_BmpWinOff(&(wk->win[WIN_TALK]));
		wk->sub_seq = 0;

		if(ret){
			//モジュール終了
			wk->dat->val = VIEW_END_CANCEL;
			return TRUE;
		}else{
			wk->mode = wk->inMode;	//モードを元に戻す 
			wk->canm_f = 0;
			return FALSE;
		}
	}
	wk->sub_seq++;
	return FALSE;
}
/**
 *	@brief	メール描画メイン
 */
static int MailViewMain(MAIL_VIEW_DAT* wk)
{
	switch(wk->seq){
	case MAILVIEW_BLACKSET:
		//Blank関数リセット
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		
//		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
//		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		WIPE_ResetWndMask(WIPE_DISP_MAIN);
		WIPE_ResetWndMask(WIPE_DISP_SUB);
		break;
	case MAILVIEW_RESINIT:
		if(!MailViewResInit(wk)){
			return FALSE;
		}
		sys_VBlankFuncChange(MailVBlank, wk);

//		if(wk->inMode == 0){
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
//		}
	
		//ブレンド設定
		WIPE_ResetBrightness(WIPE_DISP_MAIN);
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,GX_BLEND_PLANEMASK_BG3,ALPHA_SECOND,ALPHA_FIRST);

		PaletteFadeReq( wk->palAnm, PF_BIT_MAIN_ALL, 0xFFFF,-1,16,0,0x0000);
		break;
	case MAILVIEW_FADEIN:
		if(wk->pActRes != NULL){
			CATS_Draw(wk->pActRes);
		}
		if( PaletteFadeCheck(wk->palAnm)){
			return FALSE;
		}
		break;
	case MAILVIEW_MAIN:
		{
			static const MailKeyIn keyin[] = {
				MailView_KeyInView,
				MailView_KeyInCreate,
				MailView_KeyInMsg,
				MailView_KeyInCancel,
			};
	
			if(wk->pActRes != NULL){
				CATS_Draw(wk->pActRes);
			}
			if(!keyin[wk->mode](wk)){
				return FALSE;
			}
			PaletteFadeReq( wk->palAnm, PF_BIT_MAIN_ALL, 0xFFFF,-1,0,16,0x0000);
		}
		break;
	case MAILVIEW_FADEOUT:
		if( PaletteFadeCheck(wk->palAnm)){
			if(wk->pActRes != NULL){
				CATS_Draw(wk->pActRes);
			}
			return FALSE;
		}
		WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
		WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);
		sys_VBlankFuncChange(NULL, NULL);
		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);	
		break;
	case MAILVIEW_RESRELEASE:
		if(MailViewResRelease(wk)){
			return TRUE;
		}
		return FALSE;
	}
	wk->seq++;
	return FALSE;
}

/**
 *	@brief	メール画面VBlank
 */
static void MailVBlank(void * work)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)work;

	//パレット転送
	if( wk->palAnm != NULL ){
		PaletteFadeTrans( wk->palAnm );
	}

	//アクター転送
	if(wk->pActSys != NULL){
		CATS_RenderOamTrans();
	}

	NNS_GfdDoVramTransfer();	//VRam転送マネージャ実行
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

/**
 *	@brief	メール描画パレットアニメ
 */
static void MailView_PltAnime(TCB_PTR tcb,void* work)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)work;

	//パレットアニメが削除されたらタスクも削除
	if(wk->palAnm == NULL){
		TCB_Delete(tcb);
		return;
	}
	//アニメフックフラグが立っている時は一時停止
	if(wk->canm_f){
		return;
	}

	if(wk->oldCol != wk->nowCol){
		//元の色に戻す
		SoftFadePfd(wk->palAnm,FADE_MAIN_BG,PALANM_STARTPAL+wk->oldCol,1,0,0x7FFF);
		wk->oldCol = wk->nowCol;
		wk->colDir = 0;
		wk->colEvy = 0;
	}
	SoftFadePfd(wk->palAnm,FADE_MAIN_BG,PALANM_STARTPAL+wk->nowCol,1,wk->colEvy,0x7FFF);
	if(wk->colDir){
		if(wk->colEvy-- == 1){
			wk->colDir ^= 1;
		}
	}else{
		if(wk->colEvy++ == 12){
			wk->colDir ^= 1;
		}
	}
}

/**
 *	@brief	メール描画リソース初期化
 */
static int MailViewResInit(MAIL_VIEW_DAT* wk)
{
	switch(wk->sub_seq){
	case 0:
		MailView_BGLInit(wk);
		break;
	case 1:
		MailView_2DGraInit(wk);
		break;
	case 2:
		MailView_BmpWinInit(wk);
		MailView_MsgWrite(wk);
#if 0
		if(wk->mode == MAIL_MODE_CREATE){
			wk->sub_seq = 0;
			return TRUE;	//作成モードはアイコン描画ナシ
		}
#endif
		break;
	case 3:
		MailView_PokeIconInit(wk);
		wk->sub_seq = 0;
		return TRUE;
	}
	wk->sub_seq++;
	return FALSE;
}

/**
 *	@brief	メール描画リソース解放
 */
static int MailViewResRelease(MAIL_VIEW_DAT* wk)
{
//	if(wk->mode == MAIL_MODE_VIEW){
		MailView_PokeIconRelease(wk);
//	}
	if(wk->pMsg != NULL){
		MSGMAN_Delete(wk->pMsgMan);
	}
	MailView_BmpWinRelease(wk);
	MailView_2DGraRelease(wk);
	MailView_BGLRelease(wk);
	return TRUE;
}

/**
 *	@brief	メール描画Vramバンク初期化
 */
static void MailView_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	メール描画　BGL初期化
 */
static void MailView_BGLInit(MAIL_VIEW_DAT* wk)
{
	int i,frame;
	
	//VramBankセット
	MailView_VBankSet();

	//BGL初期化
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};
		GF_BGL_InitBG(&BGsys_data);
	}
	
	{
	GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
		{	//MAIN BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x10000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
		{	//MAIN BG1
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			1,0,0,FALSE},
		{	//MAIN BG2
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			2,0,0,FALSE},
		{	//MAIN BG3
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			3,0,0,FALSE},
		{	//SUB BG0
			0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
			0,0,0,FALSE},
	};
	GF_BGL_BGControlSet(wk->bgl,GF_BGL_FRAME0_M,&(TextBgCntDat[0]),GF_BGL_MODE_TEXT);
	GF_BGL_BGControlSet(wk->bgl,GF_BGL_FRAME1_M,&(TextBgCntDat[1]),GF_BGL_MODE_TEXT);
	GF_BGL_BGControlSet(wk->bgl,GF_BGL_FRAME2_M,&(TextBgCntDat[2]),GF_BGL_MODE_TEXT);
	GF_BGL_BGControlSet(wk->bgl,GF_BGL_FRAME3_M,&(TextBgCntDat[3]),GF_BGL_MODE_TEXT);
	GF_BGL_BGControlSet(wk->bgl,GF_BGL_FRAME0_S,&(TextBgCntDat[4]),GF_BGL_MODE_TEXT);
	}
	GF_BGL_ScrClear(wk->bgl,GF_BGL_FRAME0_M);
	GF_BGL_ScrClear(wk->bgl,GF_BGL_FRAME1_M);
	GF_BGL_ScrClear(wk->bgl,GF_BGL_FRAME2_M);
	GF_BGL_ScrClear(wk->bgl,GF_BGL_FRAME3_M);
	GF_BGL_ScrClear(wk->bgl,GF_BGL_FRAME0_S);
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME1_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME2_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME3_M,32,0,wk->heapID);
	GF_BGL_ClearCharSet(GF_BGL_FRAME0_S,32,0,wk->heapID);
}

/**
 *	@brief	メール描画　BGL解放
 */
static void MailView_BGLRelease(MAIL_VIEW_DAT* wk)
{
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME0_S);	
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME3_M);	
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME2_M);	
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME1_M);	
	GF_BGL_BGControlExit( wk->bgl, GF_BGL_FRAME0_M);

	sys_FreeMemoryEz(wk->bgl);
}

/**
 *	@brief	メール描画　BGリソース初期化
 */
static void MailView_2DGraInit(MAIL_VIEW_DAT* wk)
{
	void* tmp;
	u32	size;
	void* pSrc;
	NNSG2dCharacterData* pChar;
	NNSG2dPaletteData*	pPal;
	ARCHANDLE* handle;
	int	charID,scrnID,plttID;

	//デザインNoからグラフィックリソースID取得
	charID = MAILD_CHAR_S+wk->dat->design;
	scrnID = MAILD_SCRN_S+wk->dat->design;
	plttID = MAILD_PLTT_S+wk->dat->design;

	//アーカイブのハンドルを取得
	handle = ArchiveDataHandleOpen(ARC_MAIL_GRA,wk->heapID);

	//ウィンドウ用キャラクタ転送
	MenuWinGraphicSet(wk->bgl, BMPL_WIN_FRM,
		BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, MENU_TYPE_SYSTEM, wk->heapID);

	TalkWinGraphicSet(wk->bgl,BMPL_WIN_FRM,
		BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL, wk->win_type, wk->heapID);

	//キャラクタ転送
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,charID);
	pSrc = sys_AllocMemoryLo(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,charID,(void*)pSrc);
	
	NNS_G2dGetUnpackedCharacterData(pSrc,&pChar); 
	GF_BGL_LoadCharacter(wk->bgl,GF_BGL_FRAME1_M,
			pChar->pRawData,pChar->szByte,0);
	GF_BGL_LoadCharacter(wk->bgl,GF_BGL_FRAME0_S,
			pChar->pRawData,pChar->szByte,0);
	sys_FreeMemoryEz(pSrc);

	//パレット転送
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,plttID);
	pSrc = sys_AllocMemoryLo(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,plttID,(void*)pSrc);

	NNS_G2dGetUnpackedPaletteData(pSrc,&pPal);
//	GF_BGL_PaletteSet(GF_BGL_FRAME0_M,pPal->pRawData,pPal->szByte,0);
	GF_BGL_PaletteSet(GF_BGL_FRAME0_S,pPal->pRawData,pPal->szByte,0);
	
	//パレットアニメコントローラー確保
	wk->palAnm = PaletteFadeInit(wk->heapID);
	//リクエストデータをmallocしてセット
	PaletteFadeWorkAllocSet( wk->palAnm, FADE_MAIN_BG, FADE_PAL_ONE_SIZE*MAILVIEW_PALMAX,wk->heapID);
	PaletteFadeWorkAllocSet( wk->palAnm, FADE_MAIN_OBJ, FADE_PAL_ONE_SIZE*3,wk->heapID);
	PaletteWorkSet(wk->palAnm,pPal->pRawData,FADE_MAIN_BG,0,FADE_PAL_ONE_SIZE*3);

	if(wk->mode == MAIL_MODE_CREATE){
		//ウィンドウフォントパレットを入れ替え
		PaletteWorkSet(wk->palAnm,&(((u16*)pPal->pRawData)[16*3]),FADE_MAIN_BG,16,FADE_PAL_ONE_SIZE);
	}
	PaletteWorkSet_Arc(wk->palAnm,ARC_POKEICON,0,wk->heapID, 
		FADE_MAIN_OBJ,FADE_PAL_ONE_SIZE*3,0);

	//フォント＆ウィンドウ用パレットセット
	PaletteWorkSet_Arc(wk->palAnm,ARC_FONT,NARC_font_system_ncrl,wk->heapID, 
		FADE_MAIN_BG,FADE_PAL_ONE_SIZE,16*MENU_FONT_PAL);
	PaletteWorkSet_Arc(wk->palAnm,ARC_FONT,NARC_font_talk_ncrl,wk->heapID, 
		FADE_MAIN_BG,FADE_PAL_ONE_SIZE,16*TALK_FONT_PAL);
	PaletteWorkSet_Arc(wk->palAnm,ARC_WINFRAME,NARC_winframe_system_nclr,wk->heapID, 
		FADE_MAIN_BG,FADE_PAL_ONE_SIZE,16*BMPL_MENU_WIN_PAL);
	PaletteWorkSet_Arc(wk->palAnm,ARC_WINFRAME,NARC_winframe_talk_win00_nclr + wk->win_type,wk->heapID, 
		FADE_MAIN_BG,FADE_PAL_ONE_SIZE,16*BMPL_TALK_WIN_PAL);

#if 0
	if(wk->mode == MAIL_MODE_CREATE){
		PaletteWorkSet_Arc(wk->palAnm,ARC_FONT,NARC_font_system_ncrl,wk->heapID, 
			FADE_MAIN_BG,FADE_PAL_ONE_SIZE,16*FONT_PAL);
	}
#endif
	//初期パレットを塗りつぶす
	SoftFadePfd(wk->palAnm,FADE_MAIN_BG,0,16*MAILVIEW_PALMAX,16,0x0000);
	SoftFadePfd(wk->palAnm,FADE_MAIN_OBJ,0,16*3,16,0x0000);
	PaletteTrans_AutoSet(wk->palAnm,TRUE);
	PaletteFadeTrans( wk->palAnm );

	sys_FreeMemoryEz(pSrc);

	//スクリーン取得
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,scrnID);
	wk->pScrBuf01 = sys_AllocMemory(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,scrnID,(void*)wk->pScrBuf01);
	NNS_G2dGetUnpackedScreenData(wk->pScrBuf01,&(wk->pScr01)); 
	
	//スクリーン取得
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,MAILD_SCRN_FIL);
	wk->pScrBuf02 = sys_AllocMemory(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,MAILD_SCRN_FIL,(void*)wk->pScrBuf02);
	NNS_G2dGetUnpackedScreenData(wk->pScrBuf02,&(wk->pScr02)); 

	//ハンドル解放
	ArchiveDataHandleClose( handle );

	//初期スクリーン転送
	GF_BGL_ScrFill(wk->bgl,GF_BGL_FRAME0_S,0x2001,0,0,32,32,GF_BGL_SCRWRT_PALIN );
	
	GF_BGL_ScrWriteExpand(wk->bgl,GF_BGL_FRAME3_M,
			0,0,32,24,
			wk->pScr01->rawData,
			0,0,
			wk->pScr01->screenWidth/8,wk->pScr01->screenHeight/8);
	
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME3_M);
	GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME0_S);

	if(wk->mode == MAIL_MODE_CREATE){
		GF_BGL_ScrWriteExpand(wk->bgl,GF_BGL_FRAME2_M,
				0,0,32,24,
				wk->pScr02->rawData,
				0,0,
				wk->pScr02->screenWidth/8,wk->pScr02->screenHeight/8);
		GF_BGL_LoadScreenV_Req(wk->bgl,GF_BGL_FRAME2_M);
	
		//パレットアニメ設定	
		wk->colEvy = 0;
		wk->colDir = 0;
		TCB_Add(MailView_PltAnime,wk,0);
	}
}

/**
 *	@brief	メール描画　BGリソース解放
 */
static void MailView_2DGraRelease(MAIL_VIEW_DAT* wk)
{
	sys_FreeMemoryEz(wk->pScrBuf02);
	sys_FreeMemoryEz(wk->pScrBuf01);

	// パレットフェード開放
	PaletteFadeWorkAllocFree( wk->palAnm, FADE_MAIN_OBJ );
	PaletteFadeWorkAllocFree( wk->palAnm, FADE_MAIN_BG );

	//パレットフェードシステム開放
	PaletteFadeFree( wk->palAnm );
	wk->palAnm = NULL;
	
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
}

/**
 *	@brief	メール描画　BMPWin初期化
 */
static void MailView_BmpWinInit(MAIL_VIEW_DAT* wk)
{
	int	i = 0;
	
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_M01], BMPL_MSG_FRM,
		BMPL_MSG_PX, BMPL_M01_PY, BMPL_MSG_SX, BMPL_MSG_SY, BMPL_MSG_PAL, BMPL_M01_CGX );
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_M02], BMPL_MSG_FRM,
		BMPL_MSG_PX, BMPL_M02_PY, BMPL_MSG_SX, BMPL_MSG_SY, BMPL_MSG_PAL, BMPL_M02_CGX );
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_M03], BMPL_MSG_FRM,
		BMPL_MSG_PX, BMPL_M03_PY, BMPL_MSG_SX, BMPL_MSG_SY, BMPL_MSG_PAL, BMPL_M03_CGX );
	
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_YN01], BMPL_MSG_FRM,
		BMPL_YN01_PX, BMPL_YN_PY, BMPL_YN_SX, BMPL_YN_SY, BMPL_YN_PAL, BMPL_YN01_CGX );
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_YN02], BMPL_MSG_FRM,
		BMPL_YN02_PX, BMPL_YN_PY, BMPL_YN_SX, BMPL_YN_SY, BMPL_YN_PAL, BMPL_YN02_CGX );
	
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_TALK], BMPL_TALK_FRM,
		BMPL_TALK_PX, BMPL_TALK_PY, BMPL_TALK_SX, BMPL_TALK_SY, BMPL_TALK_PAL, BMPL_TALK_CGX );

	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinDataFill(&(wk->win[i]),0);
		if(i < WIN_TALK){
			GF_BGL_BmpWinOn(&wk->win[i]);
		}
	}
}

/**
 *	@brief	メール描画	BmpWin解放
 */
static void MailView_BmpWinRelease(MAIL_VIEW_DAT* wk)
{
	int	i = 0;

	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinOff(&wk->win[i]);
		GF_BGL_BmpWinDel(&wk->win[i]);
	}
}

/**
 *	@brief	メール描画　簡易文描画
 */
static void MailView_MsgWrite(MAIL_VIEW_DAT* wk)
{
	int i = 0;
	STRBUF* str;
	
	//メッセージ描画
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		if(!PMSDAT_IsEnabled(&wk->dat->msg[i])){
			continue;
		}
		str = PMSDAT_ToString(&wk->dat->msg[i],wk->heapID);
		GF_STR_PrintColor(
			&wk->win[WIN_M01+i],FONT_TALK,str,
			0,0,MSG_ALLPUT,VIEW_NRM_FCOL,NULL);
		STRBUF_Delete(str);

		GF_BGL_BmpWinOn(&wk->win[WIN_M01+i]);
	}
	if(wk->mode == MAIL_MODE_CREATE){	//メール作成
		STRBUF	*buf;
		int size;
		
		wk->pMsgMan = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
					NARC_msg_mailview_dat,wk->heapID);

		buf = STRBUF_Create(BUFLEN_PERSON_NAME*2,wk->heapID);
		for(i = 0;i < 2;i++){
			STRBUF_Clear(buf);
			MSGMAN_GetString(wk->pMsgMan,msg_mail_decide+i,buf);
	
			size = (BMPL_YN_SX*8)-FontProc_GetPrintStrWidth( FONT_TALK,buf, 0 );
			size /= 2;
			GF_STR_PrintColor(	&wk->win[WIN_YN01+i],FONT_TALK,
								buf,size,2,
								MSG_ALLPUT,VIEW_NRM_FCOL,	NULL );

			GF_BGL_BmpWinOn(&wk->win[WIN_YN01+i]);
		}
		STRBUF_Delete(buf);
	}else{	//メール描画
		//ライター名表示
		GF_STR_PrintColor(	&wk->win[WIN_YN01],FONT_TALK,
							wk->dat->name,0,2,
							MSG_ALLPUT,VIEW_NRM_FCOL,	NULL );

		GF_BGL_BmpWinOn(&wk->win[WIN_YN01]);
	}
}

/**
 *	@brief	メール描画　ポケモンアイコン追加
 */
static void MailView_PokeIconInit(MAIL_VIEW_DAT* wk)
{
	int i = 0,ct = 0;
	TCATS_OBJECT_ADD_PARAM_S	prm;

	//通信中なら通信アイコン復帰
	// 受信強度アイコンを通信接続中なら表示するし、
	// ユニオンのように通信回路は動作しているが接続はしていない状態なら出さない
	// Change by Mori 2006/07/19
	WirelessIconEasyUnion();
	
	if(wk->mode == MAIL_MODE_CREATE){
		return;	//作成モード中はアイコン描画はなし
	}
	initVramTransferManagerHeap(32,wk->heapID);

	//セルアクターシステム初期化
	wk->pActSys = CATS_AllocMemory(wk->heapID);
	wk->pActRes = CATS_ResourceCreate(wk->pActSys);

	{
		TCATS_OAM_INIT	coi = {
			0,7,		///< メイン	OAM管理領域・開始/終了
			1,1,		///< メイン	アフィン管理領域・開始/終了
			0,1,		///< サブ	OAM管理領域・開始/終了
			1,1,		///< サブ	アフィン管理領域・開始/終了
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			MAILDAT_ICONMAX,	//ID制御数
			1024,	//メイン画面サイズ(byte単位)
			0,		//サブ画面サイズ(byte単位)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//メインOBJモード指定
			GX_OBJVRAMMODE_CHAR_1D_32K,	//サブOBJモード指定
		};
		const TCATS_RESOURCE_NUM_LIST resNum = {
			MAILDAT_ICONMAX,	///< キャラの数
			1,					///< パレットの数
			1,					///< セルの数
			1,					///< セルアニメの数
			0,					///< マルチセルの数
			0,					///< マルチセルアニメの数
		};	

		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->pActSys, wk->pActRes,MAILDAT_ICONMAX );
		CATS_ResourceManagerInit(wk->pActSys,wk->pActRes,&resNum);
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
	}

	//リソース追加
	CATS_LoadResourcePlttArc(
		wk->pActSys,wk->pActRes,ARC_POKEICON,
		PokeIconPalArcIndexGet(),0,3,NNS_G2D_VRAM_TYPE_2DMAIN,0);

	CATS_LoadResourceCellArc(
		wk->pActSys,wk->pActRes,ARC_POKEICON,
			PokeIconCellArcIndexGet(),0,0);

	CATS_LoadResourceCellAnmArc(
		wk->pActSys,wk->pActRes,ARC_POKEICON,
		PokeIconCellAnmArcIndexGet(),0,0);

	for(i = 0;i < MAILDAT_ICONMAX;i++){
		if(wk->dat->icon[i].dat == MAIL_ICON_NULL){
			break;
		}
		CATS_LoadResourceCharArcModeAdjust(
			wk->pActSys, wk->pActRes,ARC_POKEICON,
			wk->dat->icon[i].cgxID,0,NNS_G2D_VRAM_TYPE_2DMAIN,i);
	
		MI_CpuClear8(&prm,sizeof(TCATS_OBJECT_ADD_PARAM_S));

		prm.x = ICONVIEW_PX-(ICONVIEW_WIDTH*i);	///< [ X ] 座標
		prm.y = ICONVIEW_PY;				///< [ Y ] 座標
		prm.z = 0;				///< [ Z ] 座標

		prm.anm = 0;									///< アニメ番号
		prm.bg_pri = MAILVIEW_ICON_PRI;					///< 優先順位
		prm.pal = wk->dat->icon[i].palID;				///< パレット番号
		prm.vram_trans = 0;	///< 描画エリア
		prm.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;	///< 描画エリア

		prm.id[0] = i;	//char
		prm.id[1] = 0;	//Pal
		prm.id[2] = 0;	//Cell
		prm.id[3] = 0;	//Cell Anime
		prm.id[4] = CLACT_U_HEADER_DATA_NONE;	//Multi Cell
		prm.id[5] = CLACT_U_HEADER_DATA_NONE;	//Muiti Cell Anime

		wk->pAct[i] = CATS_ObjectAdd_S(wk->pActSys,wk->pActRes,&prm);
	}

}

/**
 *	@brief	メール描画　ポケモンアイコン解放
 */
static void MailView_PokeIconRelease(MAIL_VIEW_DAT* wk)
{
	int i = 0;

	if(wk->mode == MAIL_MODE_VIEW){
		for(i = 0;i < MAILDAT_ICONMAX;i++){
			if(wk->pAct[i] != NULL){
				CATS_ActorPointerDelete_S(wk->pAct[i]);
			}
		}
		CATS_ResourceDestructor_S(wk->pActSys,wk->pActRes);
		CATS_FreeMemory(wk->pActSys);
		DellVramTransferManager();	
	}
}

