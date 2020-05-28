/**
 *	@file	mailview.c
 *	@brief	���[����ʕ`�惋�[�`��
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

///���[���`�惁�C�����[�N
typedef struct _MAIL_VIEW_DATA{
	int	heapID;
	int	seq;		///<���C���V�[�P���XNo
	u16	sub_seq;	///<�T�u�V�[�P���XNo
	u16	win_type;	///<�E�B���h�E�^�C�v
	u8	mode;	///<����^�C�v
	u8	inMode;	///<����^�C�v
	u8	cntNo;
	u8	msgIdx;

	u8	msg_spd;
	u8	line;	///<�I�����C��
	u8	side;	///<�T�C�h�I��
	u8	canm_f;	///<�A�j���t�b�N�t���O
	u8	colEvy;
	u8	colDir;
	u8	nowCol;
	u8	oldCol;

	GF_BGL_INI *bgl;	///<BGL�f�[�^

	MAIL_TMP_DATA	*dat;
	MSGDATA_MANAGER*	pMsgMan;
	STRBUF	*pMsg[MAILDAT_MSGMAX];
	PALETTE_FADE_PTR	palAnm;

	///�O���t�B�b�N���\�[�X
	void*	pScrBuf01;
	void*	pScrBuf02;
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr02;
	GF_BGL_BMPWIN	win[WIN_MAX];
	BMPMENU_WORK*	ynmenu_wk;
	
	CATS_SYS_PTR	pActSys;	///<�Z���A�N�^�[�V�X�e��
	CATS_RES_PTR	pActRes;	///<�Z���A�N�^�[���\�[�X
	CATS_ACT_PTR	pAct[MAILDAT_ICONMAX];		///<�A�N�^�[
}MAIL_VIEW_DAT;

///�T�u�v���Z�X��`�p�֐��^
typedef int (*MailKeyIn)(MAIL_VIEW_DAT* wk);

//=================================================
//�v���g�^�C�v
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
//�v���Z�X��`
//====================================================================
PROC_RESULT MailViewProc_Init( PROC *proc,int *seq);
PROC_RESULT MailViewProc_Main( PROC *proc,int *seq);
PROC_RESULT MailViewProc_End( PROC *proc,int *seq);

/**
 *	@brief	���[���`��Ăяo���@������
 */
PROC_RESULT MailViewProc_Init(PROC* proc,int* seq)
{
	MAIL_TMP_DATA* tp;
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)PROC_GetWork(proc);

	//���[�N�G���A�擾
	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_MAILVIEW,0x20000);
	wk = PROC_AllocWork(proc,sizeof(MAIL_VIEW_DAT),HEAPID_MAILVIEW);
	memset(wk,0,sizeof(MAIL_VIEW_DAT));

	//�q�[�vID�ۑ�
	wk->heapID = HEAPID_MAILVIEW;

	//�p�����[�^���p��
	wk->dat = (MAIL_TMP_DATA*)PROC_GetParentWork(proc);
	wk->inMode = wk->mode = wk->dat->val;	//�`��^�C�v
	wk->line = wk->dat->cntNo;
	wk->side = wk->dat->flags;
	wk->oldCol = wk->nowCol = wk->line;
	wk->dat->val = VIEW_END_CANCEL;

	wk->msg_spd = CONFIG_GetMsgPrintSpeed(wk->dat->configSave);
	wk->win_type = CONFIG_GetWindowType(wk->dat->configSave);
	return PROC_RES_FINISH;
};


/**
 *	@brief	���[���`��Ăяo���@���C��
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
 *	@brief	���[���`��Ăяo��	�I���@
 */
PROC_RESULT MailViewProc_End(PROC* proc,int* seq)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)PROC_GetWork(proc);
	int heap;
	
	//�I���p�����[�^�i�[
	heap = wk->heapID;
	
	//���[�N�G���A���
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(heap);

	sys_DeleteHeap(heap);

	return PROC_RES_FINISH;
}


//====================================================================
//���[�J���֐���`
//====================================================================
//
/**
 *	@brief	��b�����S���󂩂ǂ����`�F�b�N
 *
 *	@retval	TRUE	�S����
 *	@retval FALSE	���͗L��
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
 *	@brief	���[���`��@�L�[�擾(View���[�h)
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
 *	@brief	���[���`��@�L�[�擾(Create���[�h)
 */
static int MailView_KeyInCreate(MAIL_VIEW_DAT* wk)
{
	u8 se_play = 0;
	
	if(sys.trg & (PAD_BUTTON_DECIDE)){
		if(wk->line == VIEW_END_DECIDE){
			if(wk->side == VIEW_SIDE_DECIDE){
				//��b�����󂩂ǂ����`�F�b�N
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

	//�I�����ڕύX
	if(sys.trg & (PAD_BUTTON_START)){
		//�ꔭ�Łu����v��
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
	//�I�����C���`��ύX
	Snd_SePlay(SND_MAIL_SELECT);

	if(wk->line == VIEW_LINE_END){
		wk->nowCol = wk->line+wk->side;
	}else{
		wk->nowCol = wk->line;
	}
	return FALSE;
}

/**
 *	@brief	���[���`��L�[�擾�@���b�Z�[�W�҂����[�h
 */
static int MailView_KeyInMsg(MAIL_VIEW_DAT* wk)
{
	STRBUF* str = NULL;
	
	switch(wk->sub_seq){
	case 0:
		//��̓_�����b�Z�[�W�`��J�n
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
		//�L�[�҂�
		if(!(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))){
			return FALSE;
		}
		BmpTalkWinClear( &wk->win[WIN_TALK],WINDOW_TRANS_OFF);
		GF_BGL_BmpWinOff(&(wk->win[WIN_TALK]));

		wk->sub_seq = 0;
		wk->mode = wk->inMode;	//���[�h�����ɖ߂� 
		return FALSE;
	}
	wk->sub_seq++;
	return FALSE;
}

/**
 *	@brief	YN�E�B���h�E������
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
 *	@brief	YN�E�B���h�E�I��҂�
 */
static int yesNoWait(MAIL_VIEW_DAT* wk)
{
	switch( BmpYesNoSelectMain( wk->ynmenu_wk, wk->heapID) ){
	case 0:	//�͂�
//		Snd_SePlay(PORUC_SE_DECIDE);
		return TRUE;
	case BMPMENU_CANCEL: //������
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
		//��߂܂������b�Z�[�W�`��J�n
		BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL	);
		GF_BGL_BmpWinDataFill(&(wk->win[WIN_TALK]),WINCLR_COL(FBMP_COL_WHITE));

		str = STRBUF_Create(VIEW_BUFLEN_MSG,wk->heapID);
		MSGMAN_GetString(wk->pMsgMan,msg_mail_cmsg,str);
		wk->msgIdx = GF_STR_PrintColor(
			&wk->win[WIN_TALK],FONT_TALK,str,
			0,0,wk->msg_spd,VIEW_TALK_FCOL,NULL);
		STRBUF_Delete(str);

		//�J���[�A�j������U���Ƃ̐F�ɖ߂�
		SoftFadePfd(wk->palAnm,FADE_MAIN_BG,PALANM_STARTPAL+wk->oldCol,1,0,0x7FFF);
		wk->oldCol = wk->nowCol;
		wk->colDir = 0;
		wk->colEvy = 0;
		break;
	case 1:
		//�`��I���҂�
		if( GF_MSG_PrintEndCheck( wk->msgIdx )){
			return FALSE;
		}
		//YN�E�B���h�E������
		yesNoInit(wk);
		break;
	case 2:
		//�I��҂�
		ret = yesNoWait(wk);
		if(ret < 0){
			return FALSE;
		}
		BmpTalkWinClear( &wk->win[WIN_TALK],WINDOW_TRANS_OFF);
		GF_BGL_BmpWinOff(&(wk->win[WIN_TALK]));
		wk->sub_seq = 0;

		if(ret){
			//���W���[���I��
			wk->dat->val = VIEW_END_CANCEL;
			return TRUE;
		}else{
			wk->mode = wk->inMode;	//���[�h�����ɖ߂� 
			wk->canm_f = 0;
			return FALSE;
		}
	}
	wk->sub_seq++;
	return FALSE;
}
/**
 *	@brief	���[���`�惁�C��
 */
static int MailViewMain(MAIL_VIEW_DAT* wk)
{
	switch(wk->seq){
	case MAILVIEW_BLACKSET:
		//Blank�֐����Z�b�g
		sys_VBlankFuncChange(NULL, NULL);
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

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
	
		//�u�����h�ݒ�
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
 *	@brief	���[�����VBlank
 */
static void MailVBlank(void * work)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)work;

	//�p���b�g�]��
	if( wk->palAnm != NULL ){
		PaletteFadeTrans( wk->palAnm );
	}

	//�A�N�^�[�]��
	if(wk->pActSys != NULL){
		CATS_RenderOamTrans();
	}

	NNS_GfdDoVramTransfer();	//VRam�]���}�l�[�W�����s
	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

/**
 *	@brief	���[���`��p���b�g�A�j��
 */
static void MailView_PltAnime(TCB_PTR tcb,void* work)
{
	MAIL_VIEW_DAT* wk = (MAIL_VIEW_DAT*)work;

	//�p���b�g�A�j�����폜���ꂽ��^�X�N���폜
	if(wk->palAnm == NULL){
		TCB_Delete(tcb);
		return;
	}
	//�A�j���t�b�N�t���O�������Ă��鎞�͈ꎞ��~
	if(wk->canm_f){
		return;
	}

	if(wk->oldCol != wk->nowCol){
		//���̐F�ɖ߂�
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
 *	@brief	���[���`�惊�\�[�X������
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
			return TRUE;	//�쐬���[�h�̓A�C�R���`��i�V
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
 *	@brief	���[���`�惊�\�[�X���
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
 *	@brief	���[���`��Vram�o���N������
 */
static void MailView_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	���[���`��@BGL������
 */
static void MailView_BGLInit(MAIL_VIEW_DAT* wk)
{
	int i,frame;
	
	//VramBank�Z�b�g
	MailView_VBankSet();

	//BGL������
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
 *	@brief	���[���`��@BGL���
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
 *	@brief	���[���`��@BG���\�[�X������
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

	//�f�U�C��No����O���t�B�b�N���\�[�XID�擾
	charID = MAILD_CHAR_S+wk->dat->design;
	scrnID = MAILD_SCRN_S+wk->dat->design;
	plttID = MAILD_PLTT_S+wk->dat->design;

	//�A�[�J�C�u�̃n���h�����擾
	handle = ArchiveDataHandleOpen(ARC_MAIL_GRA,wk->heapID);

	//�E�B���h�E�p�L�����N�^�]��
	MenuWinGraphicSet(wk->bgl, BMPL_WIN_FRM,
		BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, MENU_TYPE_SYSTEM, wk->heapID);

	TalkWinGraphicSet(wk->bgl,BMPL_WIN_FRM,
		BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL, wk->win_type, wk->heapID);

	//�L�����N�^�]��
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,charID);
	pSrc = sys_AllocMemoryLo(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,charID,(void*)pSrc);
	
	NNS_G2dGetUnpackedCharacterData(pSrc,&pChar); 
	GF_BGL_LoadCharacter(wk->bgl,GF_BGL_FRAME1_M,
			pChar->pRawData,pChar->szByte,0);
	GF_BGL_LoadCharacter(wk->bgl,GF_BGL_FRAME0_S,
			pChar->pRawData,pChar->szByte,0);
	sys_FreeMemoryEz(pSrc);

	//�p���b�g�]��
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,plttID);
	pSrc = sys_AllocMemoryLo(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,plttID,(void*)pSrc);

	NNS_G2dGetUnpackedPaletteData(pSrc,&pPal);
//	GF_BGL_PaletteSet(GF_BGL_FRAME0_M,pPal->pRawData,pPal->szByte,0);
	GF_BGL_PaletteSet(GF_BGL_FRAME0_S,pPal->pRawData,pPal->szByte,0);
	
	//�p���b�g�A�j���R���g���[���[�m��
	wk->palAnm = PaletteFadeInit(wk->heapID);
	//���N�G�X�g�f�[�^��malloc���ăZ�b�g
	PaletteFadeWorkAllocSet( wk->palAnm, FADE_MAIN_BG, FADE_PAL_ONE_SIZE*MAILVIEW_PALMAX,wk->heapID);
	PaletteFadeWorkAllocSet( wk->palAnm, FADE_MAIN_OBJ, FADE_PAL_ONE_SIZE*3,wk->heapID);
	PaletteWorkSet(wk->palAnm,pPal->pRawData,FADE_MAIN_BG,0,FADE_PAL_ONE_SIZE*3);

	if(wk->mode == MAIL_MODE_CREATE){
		//�E�B���h�E�t�H���g�p���b�g�����ւ�
		PaletteWorkSet(wk->palAnm,&(((u16*)pPal->pRawData)[16*3]),FADE_MAIN_BG,16,FADE_PAL_ONE_SIZE);
	}
	PaletteWorkSet_Arc(wk->palAnm,ARC_POKEICON,0,wk->heapID, 
		FADE_MAIN_OBJ,FADE_PAL_ONE_SIZE*3,0);

	//�t�H���g���E�B���h�E�p�p���b�g�Z�b�g
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
	//�����p���b�g��h��Ԃ�
	SoftFadePfd(wk->palAnm,FADE_MAIN_BG,0,16*MAILVIEW_PALMAX,16,0x0000);
	SoftFadePfd(wk->palAnm,FADE_MAIN_OBJ,0,16*3,16,0x0000);
	PaletteTrans_AutoSet(wk->palAnm,TRUE);
	PaletteFadeTrans( wk->palAnm );

	sys_FreeMemoryEz(pSrc);

	//�X�N���[���擾
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,scrnID);
	wk->pScrBuf01 = sys_AllocMemory(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,scrnID,(void*)wk->pScrBuf01);
	NNS_G2dGetUnpackedScreenData(wk->pScrBuf01,&(wk->pScr01)); 
	
	//�X�N���[���擾
	size = ArchiveDataSizeGet(ARC_MAIL_GRA,MAILD_SCRN_FIL);
	wk->pScrBuf02 = sys_AllocMemory(wk->heapID,size);
	ArchiveDataLoadByHandle(handle,MAILD_SCRN_FIL,(void*)wk->pScrBuf02);
	NNS_G2dGetUnpackedScreenData(wk->pScrBuf02,&(wk->pScr02)); 

	//�n���h�����
	ArchiveDataHandleClose( handle );

	//�����X�N���[���]��
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
	
		//�p���b�g�A�j���ݒ�	
		wk->colEvy = 0;
		wk->colDir = 0;
		TCB_Add(MailView_PltAnime,wk,0);
	}
}

/**
 *	@brief	���[���`��@BG���\�[�X���
 */
static void MailView_2DGraRelease(MAIL_VIEW_DAT* wk)
{
	sys_FreeMemoryEz(wk->pScrBuf02);
	sys_FreeMemoryEz(wk->pScrBuf01);

	// �p���b�g�t�F�[�h�J��
	PaletteFadeWorkAllocFree( wk->palAnm, FADE_MAIN_OBJ );
	PaletteFadeWorkAllocFree( wk->palAnm, FADE_MAIN_BG );

	//�p���b�g�t�F�[�h�V�X�e���J��
	PaletteFadeFree( wk->palAnm );
	wk->palAnm = NULL;
	
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
}

/**
 *	@brief	���[���`��@BMPWin������
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
 *	@brief	���[���`��	BmpWin���
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
 *	@brief	���[���`��@�ȈՕ��`��
 */
static void MailView_MsgWrite(MAIL_VIEW_DAT* wk)
{
	int i = 0;
	STRBUF* str;
	
	//���b�Z�[�W�`��
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
	if(wk->mode == MAIL_MODE_CREATE){	//���[���쐬
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
	}else{	//���[���`��
		//���C�^�[���\��
		GF_STR_PrintColor(	&wk->win[WIN_YN01],FONT_TALK,
							wk->dat->name,0,2,
							MSG_ALLPUT,VIEW_NRM_FCOL,	NULL );

		GF_BGL_BmpWinOn(&wk->win[WIN_YN01]);
	}
}

/**
 *	@brief	���[���`��@�|�P�����A�C�R���ǉ�
 */
static void MailView_PokeIconInit(MAIL_VIEW_DAT* wk)
{
	int i = 0,ct = 0;
	TCATS_OBJECT_ADD_PARAM_S	prm;

	//�ʐM���Ȃ�ʐM�A�C�R�����A
	// ��M���x�A�C�R����ʐM�ڑ����Ȃ�\�����邵�A
	// ���j�I���̂悤�ɒʐM��H�͓��삵�Ă��邪�ڑ��͂��Ă��Ȃ���ԂȂ�o���Ȃ�
	// Change by Mori 2006/07/19
	WirelessIconEasyUnion();
	
	if(wk->mode == MAIL_MODE_CREATE){
		return;	//�쐬���[�h���̓A�C�R���`��͂Ȃ�
	}
	initVramTransferManagerHeap(32,wk->heapID);

	//�Z���A�N�^�[�V�X�e��������
	wk->pActSys = CATS_AllocMemory(wk->heapID);
	wk->pActRes = CATS_ResourceCreate(wk->pActSys);

	{
		TCATS_OAM_INIT	coi = {
			0,7,		///< ���C��	OAM�Ǘ��̈�E�J�n/�I��
			1,1,		///< ���C��	�A�t�B���Ǘ��̈�E�J�n/�I��
			0,1,		///< �T�u	OAM�Ǘ��̈�E�J�n/�I��
			1,1,		///< �T�u	�A�t�B���Ǘ��̈�E�J�n/�I��
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			MAILDAT_ICONMAX,	//ID���䐔
			1024,	//���C����ʃT�C�Y(byte�P��)
			0,		//�T�u��ʃT�C�Y(byte�P��)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//���C��OBJ���[�h�w��
			GX_OBJVRAMMODE_CHAR_1D_32K,	//�T�uOBJ���[�h�w��
		};
		const TCATS_RESOURCE_NUM_LIST resNum = {
			MAILDAT_ICONMAX,	///< �L�����̐�
			1,					///< �p���b�g�̐�
			1,					///< �Z���̐�
			1,					///< �Z���A�j���̐�
			0,					///< �}���`�Z���̐�
			0,					///< �}���`�Z���A�j���̐�
		};	

		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->pActSys, wk->pActRes,MAILDAT_ICONMAX );
		CATS_ResourceManagerInit(wk->pActSys,wk->pActRes,&resNum);
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
	}

	//���\�[�X�ǉ�
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

		prm.x = ICONVIEW_PX-(ICONVIEW_WIDTH*i);	///< [ X ] ���W
		prm.y = ICONVIEW_PY;				///< [ Y ] ���W
		prm.z = 0;				///< [ Z ] ���W

		prm.anm = 0;									///< �A�j���ԍ�
		prm.bg_pri = MAILVIEW_ICON_PRI;					///< �D�揇��
		prm.pal = wk->dat->icon[i].palID;				///< �p���b�g�ԍ�
		prm.vram_trans = 0;	///< �`��G���A
		prm.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;	///< �`��G���A

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
 *	@brief	���[���`��@�|�P�����A�C�R�����
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

