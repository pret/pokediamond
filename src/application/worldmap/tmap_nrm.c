/**
 *	@file	tmap_nrm.c
 *	@brief	�^�E���}�b�v�@�m�[�}�����[�h����
 *	@date	05.11.02
 *	@author	Miyuki Iwasawa
 */
#include "common.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "field/syswork.h"
#include "system/procsys.h"
#include "system/bmp_list.h"
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
#include "system/wipe.h"
#include "gflib/touchpanel.h"
#include "application/townmap.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_townmap.h"
#include "msgdata/msg_place_name.h"
#include "tmap.h"
#include "tmap_act.h"
#include "tmap_snd_def.h"
#include "tmap_nrm.dat"
#include "fielddata/maptable/zone_id.h"

//���̂�place_name_core.c
extern void PNC_GetPlaceNameFromZoneID(	const int inZoneID,
										const u32 inHeapID,
										STRBUF *outName);

///���Օ\���\����
#define DIR_NOT			(-1)	///<�������Ȃ��ꍇ
#define DIR_UP			(0)		///<�����
#define DIR_DOWN		(1)		///<������
#define DIR_LEFT		(2)		///<������
#define DIR_RIGHT		(3)		///<�E����
#define DIR_ROT_UP		(0)
#define DIR_ROT_LEFT	(1)
#define DIR_ROT_DOWN	(2)
#define DIR_ROT_RIGHT	(3)

typedef struct _TMAP_FVIEW{
	int	x;
	int	z;
	u16	dir;	//����
	u8	idx;
	u8	valid;
	
	CLACT_WORK_PTR	pAct;	///<�A�N�^�[���[�N
}TMAP_FVIEW;
typedef struct _TMAP_FOOTVIEW{
	int	num;	//�L���f�[�^��
	TCB_PTR	tcb;	///�A�j���^�X�N
	u16	anmct;	///<�A�j���J�E���^
	u8	now;
	u8	old;
	TMAP_FVIEW	foot[TMAP_FVIEW_MAX];
}TMAP_FOOTVIEW;

typedef struct _TMAP_MODE_NORMAL{
	int	seq;		///<�V�[�N����
	int	sub_seq;	///<�V�[�N����
	int	sub_ct;	///<�V�[�N����
	int	main_ct;	///<�V�[�N����
	u8	forcus;	///<�㉺��ʂǂ���ɐ��䂪���邩�H
	u8	key_f;	///<�L�[�t���O
	u8	view_f;	///<�r���[�X�V�t���O
	u8	cmove_f;	///<�J�[�\�����ړ������ǂ����H
	u8	tp_f;	///<�^�b�`�p�l���R���g���[���t���O
	u8	guide_f:4;	///<�K�C�h�X�V�t���O	
	u8	board_f:4;	///<�{�[�h�^�C�v���ʃt���O	
	u16	repeat_f;	///<���s�[�g
	int cposX;		///<���݂̃J�[�\���ʒu(�u���b�N)
	int cposZ;		///<���݂̃J�[�\���ʒu(�u���b�N)
	int	czoneID;	///<���݂̃]�[��ID
	int	ozoneID;	///<�Â��]�[��ID
	
	GF_BGL_BMPWIN	win[WIN_MAX];	///<BMP�E�B���h�E�f�[�^
	GF_BGL_BMPWIN*	pBoardWin;	///<�{�[�h�p�E�B���h�E

	TMAP_SCROLLPRM	scrBGM0;	///<�X�N���[���p�����[�^
	TMAP_SCROLLPRM	scrBGS0;	///<�X�N���[���p�����[�^

	TMAP_VIEW_DAT*	pTView;	///<�^�E��View�f�[�^
	TMAP_GDAT*		pBlock;	///<�u���b�N�f�[�^

	TMAP_FOOTVIEW	fView;	///<���Օ`��

	CLACT_WORK_PTR	pCAW_btn;	///<�A�N�^�[���[�N
	CLACT_WORK_PTR	pCAW_cur;	///<�A�N�^�[���[�N
	CLACT_WORK_PTR	pCAW_hero;	///<�A�N�^�[���[�N

	TCB_PTR			tcb;	//�^�X�N�|�C���^
}TMAP_MODE_NORMAL;

///�v���g�^�C�v
int	TMapNormal_Init(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Build(TMAP_MAIN_DAT* pMain);
int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Main(TMAP_MAIN_DAT* pMain);
int	TMapNormal_Draw(TMAP_MAIN_DAT* pMain);
int TMapNormal_Release(TMAP_MAIN_DAT *pMain);
int TMapNormal_VBlank(TMAP_MAIN_DAT *pMain);
int TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain);
int TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain);
int TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain);
int TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain);


static void TMap_BoardMsgSet(TMAP_MAIN_DAT* pMain,TMAP_GDAT* pBlock,int zoneID);
static void TMap_BoardGraphicOff(TMAP_MAIN_DAT* pMain);
static void TMap_GuideTagSet(TMAP_MAIN_DAT* pMain,GF_BGL_BMPWIN* win);
static void TMapN_BmpWinSet(TMAP_MAIN_DAT* pMain);
static void TMapN_BmpWinExit(TMAP_MAIN_DAT* pMain);
static void TMapN_SubButtonSet(TMAP_MAIN_DAT* pMain,u8 frm,u8 mode);
static void TMapN_2DGrapDefSet(TMAP_MAIN_DAT* pMain);
static void TMapN_2DGrapClear(TMAP_MAIN_DAT* pMain);
static void TMapN_CellActSet(TMAP_MAIN_DAT* pMain);
static void TMapN_FootViewInit(TMAP_MAIN_DAT* pMain);
static void TMapN_FootViewTask(TCB_PTR tcb,void* work);
static void TMapN_FootViewRelease(TMAP_MAIN_DAT* pMain);

static void TMapN_CheckKeyCursor(TMAP_MAIN_DAT* pMain,int key);
static void TMapN_ZoneNameGet(TMAP_MAIN_DAT *pMain,int zoneID,int x,int z);
static void TMapN_ZoneNameWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,int zoneID,int x,int z);
static void TMapN_BlockExpWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,TMAP_GDAT* pBlock);
static void TMapN_BlockChange(TMAP_MAIN_DAT* pMain);
static void TMapN_BlockReset(TMAP_MAIN_DAT* pMain);
static void TMapN_CursorDrawUp(TMAP_MAIN_DAT* pMain);
static void TMapN_SubScrollSet(TMAP_MAIN_DAT* pMain,int x,int y);


static void TMapNS_AddSVForcusTask(TMAP_MAIN_DAT* pMain,int mode);
static void TMapNS_SVForcusInTask(TCB_PTR tcb,void* work);
static void TMapNS_SVForcusOutTask(TCB_PTR tcb,void* work);

static int TMapJ_CheckJumpPos(TMAP_MAIN_DAT* pMain);

/**
 *	@brief	�m�[�}�����[�h������
 */
int	TMapNormal_Init(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk;

	pMain->pSwork = sys_AllocMemory(pMain->heapID,sizeof(TMAP_MODE_NORMAL));
	wk = (TMAP_MODE_NORMAL*)pMain->pSwork;
	memset(wk,0,sizeof(TMAP_MODE_NORMAL));

	return TMAP_SEQ_FINISH;	
}

/**
 *	@brief	�m�[�}�����[�h���
 */
int TMapNormal_Release(TMAP_MAIN_DAT *pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//�r���[�N���A
	TMapN_2DGrapClear(pMain);
	if(pMain->mode != TMAP_MBG){
		TMapN_FootViewRelease(pMain);
	}
	TownViewDataRelease(wk->pTView);
	TMapN_BmpWinExit(pMain);
	sys_FreeMemoryEz(wk);
	return TMAP_SEQ_FINISH;	
}

/**
 *	@brief	�m�[�}�����[�h�f�[�^�\�z
 */
int	TMapNormal_Build(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	switch(wk->seq){
	case 0:
		//���C������̃f�[�^���p��
		wk->cposX = pMain->cposX;
		wk->cposZ = pMain->cposZ;
		wk->czoneID = -1;	//�_�~�[�l
		//�T�u��ʃJ�[�\���ʒu�`��
		wk->scrBGS0.scrX = (wk->cposX*TMAP_SBLOCK_UNIT+8)	- 128+16;
		wk->scrBGS0.scrY = (wk->cposZ*TMAP_SBLOCK_UNIT)	- 96;

		TMapN_SubScrollSet(pMain,wk->scrBGS0.scrX,wk->scrBGS0.scrY);

		//Bmp�E�B���h�E������
		TMapN_BmpWinSet(pMain);
		
		//���Ճ}�[�N
		if(pMain->mode != TMAP_MBG){
			TMapN_FootViewInit(pMain);
		}
		break;
	case 1:
		//2DGrapSet
		TMapN_2DGrapDefSet(pMain);

		//�Z���A�N�^�[�ǉ�
		TMapN_CellActSet(pMain);
		
		//�^�E��View�쐬
		wk->pTView = TownViewDataCreate(pMain->pCActSys,pMain->pCActRes,
				pMain->param->arrive,TOWN_VIEW_MAX,pMain->heapID);
	
		TMapN_BlockReset(pMain);
		TMapN_BlockChange(pMain);
		wk->seq = 0;
		return TMAP_SEQ_FINISH;
	}
	wk->seq++;
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�m�[�}�����[�h�@�t�F�[�h�C��
 */
int TMapNormal_FadeInSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_FMAS,
			WIPE_TYPE_HOLEIN,
			WIPE_TYPE_TUNNELIN_TOP,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MOPEN);

	WIPE_ResetBrightness(WIPE_DISP_MAIN);
	WIPE_ResetBrightness(WIPE_DISP_SUB);
	//�u�����h�ݒ�
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,GX_BLEND_PLANEMASK_BG3,28,4);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	�m�[�}�����[�h�@�t�F�[�h�A�E�g
 */
int TMapNormal_FadeOutSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_FSAM,
			WIPE_TYPE_HOLEOUT,
			WIPE_TYPE_TUNNELOUT_TOP,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MCLOSE);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	BG���[�h�@�t�F�[�h�C��
 */
int TMapBG_FadeInSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_M,
			WIPE_TYPE_HOLEIN,
			WIPE_TYPE_HOLEIN,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MOPEN);

	WIPE_ResetBrightness(WIPE_DISP_MAIN);
//	WIPE_ResetBrightness(WIPE_DISP_SUB);
	//�u�����h�ݒ�
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,GX_BLEND_PLANEMASK_BG3,28,4);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	BG���[�h�@�t�F�[�h�A�E�g
 */
int TMapBG_FadeOutSet(TMAP_MAIN_DAT* pMain)
{
	pMain->wipe_f = 0;
	WIPE_SYS_Start(WIPE_PATTERN_M,
			WIPE_TYPE_HOLEOUT,
			WIPE_TYPE_HOLEOUT,0x0000,6,1,pMain->heapID
			);
	Snd_SePlay(SND_TMAP_MCLOSE);
//	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,GX_BLEND_PLANEMASK_NONE,31,0);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�m�[�}�����[�h�L�[�擾
 */
int	TMapNormal_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(	wk->tp_f <= 1 &&
		sys.trg & PAD_BUTTON_CANCEL){
		Snd_SePlay(SND_TMAP_CANCEL);
		return TMAP_SEQ_FINISH;	
	}
	if(wk->tp_f > 1){
		//�T�u��ʐ؂�ւ����̓L�[���m���Ȃ�
		return TMAP_SEQ_CONTINUE;
	}
	TMapN_CheckKeyCursor(pMain,sys.cont);

	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�W�����v���[�h�L�[�擾	�L�[�E�F�C�g���[�h
 */
int	TMapJump_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(wk->tp_f <= 1){	//�^�b�`�p�l���^�X�N�������Ă���Ƃ��͏I�����Ȃ�
		if(sys.trg & PAD_BUTTON_DECIDE){
			if(TMapJ_CheckJumpPos(pMain)){
				Snd_SePlay(SND_TMAP_DECIDE);
				return TMAP_SEQ_FINISH;
			}
			return TMAP_SEQ_CONTINUE;
		}else if(sys.trg & PAD_BUTTON_CANCEL){
			Snd_SePlay(SND_TMAP_CANCEL);
			return TMAP_SEQ_FINISH;
		}
	}
	if(wk->tp_f > 1){
		//�T�u��ʐ؂�ւ����̓L�[���m���Ȃ�
		return TMAP_SEQ_CONTINUE;
	}

	TMapN_CheckKeyCursor(pMain,sys.cont);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	BG���[�h�L�[�擾
 */
int	TMapBG_KeyIn(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(	sys.trg & (PAD_BUTTON_CANCEL)){
		Snd_SePlay(SND_TMAP_CANCEL);
		return TMAP_SEQ_FINISH;	
	}

	TMapN_CheckKeyCursor(pMain,sys.cont);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�m�[�}�����[�h�@���C���R���g���[��
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
int TMapNormal_Main(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(wk->view_f & VIEW_UP){
		//�u���b�N�X�V
		if(wk->guide_f >= 2){
			TMapN_BlockChange(pMain);
			wk->view_f = VIEW_CLEAR;
			wk->repeat_f = 0;
			wk->guide_f = 0;
		}
	}else if(wk->forcus == TMAPN_FORCUS_SUB && wk->repeat_f == 1){
		TMap_BoardMsgSet(pMain,NULL,wk->czoneID);		
	}

	TMapN_CursorDrawUp(pMain);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�m�[�}�����[�h�@Draw�V�[�P���X
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
int TMapNormal_Draw(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FVIEW *wp;
	int i;

	//���Օ`��
	for(i = 0;i < wk->fView.num;i++){
		wp = &(wk->fView.foot[i]);
	}

	TownViewDataDraw(wk->pTView,pMain->mode);
	return TMAP_SEQ_CONTINUE;
}

/**
 *	@brief	�Ŕt���[�� VBlank�]��
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
int TMapNormal_VBlank(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	GF_BGL_BMPWIN* win;
	TMAP_GDAT* pBlock = pMain->vb_block;
	int	zoneID = pMain->vb_zoneID;

	u32	siz;
	GF_PRINTCOLOR col;
	STRCODE name[BUFLEN_PLACE_NAME];

	if(!pMain->vb_trans){
		return TMAP_SEQ_CONTINUE;
	}
	//�t���OOff
	pMain->vb_trans = 0;

	//����
	if(pBlock == NULL){
		//�u���b�N�f�[�^����
		TMapN_BlockExpWrite(pMain,&(wk->win[WIN_BLOCK]),NULL);
		TMap_BoardGraphicOff(pMain);
		return TMAP_SEQ_CONTINUE;
	}
	TMapN_BlockExpWrite(pMain,&(wk->win[WIN_BLOCK]),pBlock);
	
	//�{�[�h���b�Z�[�W�`��
	STRBUF_Clear(pMain->placeName);
	TMapN_ZoneNameGet(pMain,zoneID,wk->cposX,wk->cposZ);
	
	BoardWinGraphicSet(	pMain->bgl,
			BMPL_BOARD_FRM,BMPW_BOARD_CGX,BMPL_BOARD_PAL,
			pBlock->kType, pBlock->kIdx,pMain->heapID);

	if(pBlock->kType == BOARD_TYPE_TOWN || pBlock->kType == BOARD_TYPE_ROAD){
		win = &wk->win[WIN_BOARD0];
	}else{
		win = &wk->win[WIN_BOARD1];
	}
	//���ꂩ��`���E�B���h�E�������Ă���
	wk->pBoardWin = win;
	wk->board_f = pBlock->kType;
	
	BmpBoardWinWrite(win, WINDOW_TRANS_OFF,
			BMPW_BOARD_CGX,BMPL_BOARD_PAL,/*BOARD_TYPE_TOWN*/pBlock->kType);
	
	GF_BGL_BmpWinDataFill(win,FBMP_COL_WHITE);
	GF_STR_PrintSimple(	win,
					FONT_TALK,
					pMain->placeName,
					0,0,
					MSG_NO_PUT,
					NULL );

	GF_BGL_BmpWinOn(win);
	GF_BGL_BmpWinOn(&wk->win[WIN_BLOCK]);
	return TMAP_SEQ_CONTINUE;
}
/**
 *	@brief	�^�b�`�p�l���`�F�b�N
 */
static int TMapNS_TPCheck(TMAP_MAIN_DAT* pMain,int mode)
{
	int ret;
	u16 pat;
	static const RECT_HIT_TBL TMapN_TpRect[] = {
		{0,191,0,255},
		{TMSCR_DSWMB_DPY*8,TMSCR_DSWMB_DEY*8,TMSCR_DSWMB_DPX*8,TMSCR_DSWMB_DEX*8},
		{RECT_HIT_END,0,0,0}
	};
	
	ret = GF_TP_RectHitTrg(&(TMapN_TpRect[1-mode]));
	if(ret == RECT_HIT_NONE || mode == TMAPN_FORCUS_SUB){
		return ret;
	}
	pat = 0x0012;	//0000 0011 1111 1111	�����p���b�gbit(on�ɂȂ��Ă���FNo�͔��������Ȃ�)
	if(GF_BGL_DotCheck(pMain->bgl,GF_BGL_FRAME1_S,sys.tp_x,sys.tp_y,&pat) == FALSE){
		return ret;
	}
	return RECT_HIT_NONE;
}

/**
 *	@brief	�^�b�`�p�l���`�F�b�N
 */
static BOOL TMapNS_TPCheckCall(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(pMain->param->mode == TMAP_MBG){
		return FALSE;	//BG���[�h�̓^�b�`�p�l���`�F�b�N����
	}
	if(GF_TP_GetCont()){
		if(wk->tp_f == 0 && TMapNS_TPCheck(pMain,wk->forcus) != RECT_HIT_NONE){
			TMapNS_AddSVForcusTask(pMain,wk->forcus);
			wk->tp_f = 3;
			return TRUE;
		}
	}else if(wk->tp_f == 3 || wk->tp_f == 1){
		wk->tp_f--;
	}
	return FALSE;
}

/**
 *	@brief	�J�[�\���ړ��L�[�`�F�b�N
 */
static void TMapN_CheckKeyCursor(TMAP_MAIN_DAT* pMain,int key)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	if(wk->key_f){
		if(!(key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_RIGHT|PAD_KEY_LEFT))){
			if(wk->guide_f == 1){	//�������ςȂ��`�F�b�N
				++wk->guide_f;
			}
		}
		return;	//�J�[�\���ړ���
	}

	//�^�b�`�p�l���`�F�b�N
	if(TMapNS_TPCheckCall(pMain)){
		return;
	}

	if(!(key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_RIGHT|PAD_KEY_LEFT))){
		if(wk->guide_f == 1){
			++wk->guide_f;
		}
		return;
	}
	if(key & PAD_KEY_UP){
		if(wk->cposZ >= CMOVE_MINZ){
			wk->cposZ -= 1;
			wk->key_f |= KEYS_CMOVE_MZ;
		}
	}
	if(key & PAD_KEY_DOWN){
		if(wk->cposZ <= CMOVE_MAXZ){
			wk->cposZ += 1;
			wk->key_f |= KEYS_CMOVE_PZ;
		}
	}
	if(key & PAD_KEY_RIGHT){
		if(wk->cposX <= CMOVE_MAXX){
			wk->cposX += 1;
			wk->key_f |= KEYS_CMOVE_PX;
		}
	}
	if(key & PAD_KEY_LEFT){
		if(wk->cposX >= CMOVE_MINX){
			wk->cposX -= 1;
			wk->key_f |= KEYS_CMOVE_MX;
		}
	}
	wk->cmove_f = CMOVE_COUNT;
	wk->key_f |= KEYS_FREEZE;	//�L�[�t�b�N

	if(wk->view_f != 0){
		wk->repeat_f++;
	}else{
		wk->repeat_f = 0;
	}
	wk->view_f = 0;
	wk->guide_f = 1;
	return;
}

/**
 *	@brief	�J�[�\���ړ��u���b�N�؂�ւ�
 */
static void TMapN_BlockChange(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	//�n���\����������
	TMapN_ZoneNameWrite(
		pMain,&(wk->win[WIN_M01]),wk->czoneID,wk->cposX,wk->cposZ);
	
	//����ԃ|�W�V�����`�F�b�N
	TownViewDataSelectPos(wk->pTView,wk->czoneID,wk->cposX,wk->cposZ);
	
	if(wk->forcus == TMAPN_FORCUS_SUB){
		//�u���b�N������������
		TMap_BoardMsgSet(pMain,wk->pBlock,wk->czoneID);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	}
}

/**
 *	@brief	�J�[�\���ړ��u���b�N�؂�ւ�
 */
static void TMapN_BlockReset(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	//���݂̃]�[�����擾
	wk->ozoneID = wk->czoneID;
	wk->czoneID = GetFieldMatrixZoneID((FMZ_CONST_PTR)pMain->pZone,wk->cposX,wk->cposZ);

	//���݂̃u���b�N�f�[�^���擾
	wk->pBlock = TMapBlockDataGet(pMain->pBDat,wk->cposX,wk->cposZ,pMain->mapView);
}

typedef struct _SP_ZONE_NAME{
	u16	x;
	u16	z;
	int	zoneID;
}SP_ZONE_NAME;

/**
 *	@brief	�t�B�[���h�}�g���N�X�]�[��ID��x,z���W����A�\������n������������߂�
 */
static void TMapN_ZoneNameGet(TMAP_MAIN_DAT *pMain,int zoneID,int x,int z)
{
	int i;
	
	static const SP_ZONE_NAME spZone[] = {
		{11,19,ZONE_ID_D05R0101},
		{11,20,ZONE_ID_D05R0101},
		{11,21,ZONE_ID_D05R0101},
		{11,22,ZONE_ID_D05R0101},
		{12,12,ZONE_ID_D05R0101},
		{12,13,ZONE_ID_D05R0101},
		{12,14,ZONE_ID_D05R0101},
		{12,15,ZONE_ID_D05R0101},
		{12,16,ZONE_ID_D05R0101},
		{12,17,ZONE_ID_D05R0101},
		{12,18,ZONE_ID_D05R0101},
		{12,19,ZONE_ID_D05R0101},
		{20,12,ZONE_ID_D31},
	};
	if(zoneID != 0)	{
		//�t�B�[���h�}�g���N�X�]�[��ID����擾
		PNC_GetPlaceNameFromZoneID(zoneID,pMain->heapID,pMain->placeName);
		return;
	}
	//�t�B�[���h�}�g���N�X��ɂȂ��]�[���������W����擾����
	for(i = 0;i < NELEMS(spZone);i++){
		if(spZone[i].x !=  x || spZone[i].z != z){
			continue;
		}
		//�Y���ꏊ��������
		PNC_GetPlaceNameFromZoneID(spZone[i].zoneID,pMain->heapID,pMain->placeName);
		return;	
	}
	//���O�̂Ȃ��ꏊ�p�̕������\��
	PNC_GetPlaceNameFromZoneID(0,pMain->heapID,pMain->placeName);
	return;
}

/**
 *	@brief	�]�[�����̕\���֐�
 *
 */
static void TMapN_ZoneNameWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,int zoneID,int x,int z)
{
	u32	siz;
	GF_PRINTCOLOR col;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	STRBUF_Clear(pMain->placeName);
	
	GF_BGL_BmpWinDataFill(win,0);
	col = GF_PRINTCOLOR_MAKE(1,2,0);
//	if(zoneID > 0 && wk->pBlock != NULL){
	if(wk->pBlock != NULL){
//		GetPlaceNameFromZoneID(zoneID,pMain->heapID,pMain->placeName);
		TMapN_ZoneNameGet(pMain,zoneID,x,z);

		if(pMain->mode == TMAP_MJUMP){
			siz = BMPL_M01_NSX;
		}else{
			siz = (BMPL_M01_SX*8)-FontProc_GetPrintStrWidth(FONT_SYSTEM,pMain->placeName,0);
			siz/=2;
		}
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							pMain->placeName,
							siz,BMPL_M01_WINY,
							MSG_NO_PUT,
							col,
							NULL );
	}

	//�ǂ��֔�т܂����H
	if(pMain->mode == TMAP_MJUMP){
		STRBUF* buf_q = MSGMAN_AllocString(pMain->pMsgTMap,mes_townmap_01_01);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							buf_q,
							0,BMPL_M01_WINY,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(buf_q);
	}

	GF_BGL_BmpWinOn(win);
}

/**
 *	@brief	�u���b�N�����̕\���֐�
 *
 */
static void TMapN_BlockExpWrite(TMAP_MAIN_DAT *pMain,GF_BGL_BMPWIN* win,TMAP_GDAT* pBlock)
{
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *ex1;
	STRBUF *ex2;
	
	if(pBlock == NULL){
		//�E�B���h�E�N���A
#if	S2410_060815_FIX
		/*�}�X�^�[��o�Ofix �����e�L�X�g�`�����s�����*/
		GF_BGL_BmpWinDataFill(win,0);
		GF_BGL_BmpWinOn(win);
#endif
		GF_BGL_BmpWinOff(win);
		return;
	}
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_BGL_BmpWinDataFill(win,0);

	if(	(pBlock->gmes01 != 0xFFFF) &&
		(pMain->param->flags[pBlock->id].ex01_f == 0 ||
		 pMain->param->flags[pBlock->id].ex01)){
		ex1 = MSGMAN_AllocString(pMain->pMsgTMap,pBlock->gmes01);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							ex1,
							pBlock->gmes01_ox,pBlock->gmes01_oy,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(ex1);
	}
	if(	(pBlock->gmes02 != 0xFFFF) &&
		(pMain->param->flags[pBlock->id].ex02_f == 0 ||
		 pMain->param->flags[pBlock->id].ex02)){
		ex2 = MSGMAN_AllocString(pMain->pMsgTMap,pBlock->gmes02);
		GF_STR_PrintColor(	win,
							FONT_SYSTEM,
							ex2,
							pBlock->gmes02_ox,pBlock->gmes02_oy,
							MSG_NO_PUT,
							col,
							NULL );
		STRBUF_Delete(ex2);
	}
}
/**
 *	@brief	�J�[�\���̕`��ꏊ�X�V
 */
static void TMapN_CursorDrawUp(TMAP_MAIN_DAT* pMain)
{
	int	dif = SUBSCR_MOVE_UNIT;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	if(!wk->cmove_f){
		return;
	}
	if(wk->cmove_f-- == CMOVE_COUNT){
		//�J�[�\���ړ�
		CATS_ObjectPosSet(wk->pCAW_cur,
				wk->cposX*CMOVE_UNIT+CMOVE_OFSX,
				wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);
		CLACT_AnmFrameChg(wk->pCAW_cur,FX32_ONE);	//�A�j���p�^�[�����Z�b�g

		//�u���b�N�f�[�^���Z�b�g
		TMapN_BlockReset(pMain);

		//���ʃ]�[�����\�������C�g
		TMapN_ZoneNameWrite(
			pMain,&(wk->win[WIN_M01]),
			GetFieldMatrixZoneID((FMZ_CONST_PTR)pMain->pZone,wk->cposX,wk->cposZ),wk->cposX,wk->cposZ);
		dif += 1;
	}
	
	if(wk->key_f & KEYS_CMOVE_MZ){
		wk->scrBGS0.scrY -= dif;
	}
	if(wk->key_f & KEYS_CMOVE_PZ){
		wk->scrBGS0.scrY += dif;
	}
	if(wk->key_f & KEYS_CMOVE_PX){
		wk->scrBGS0.scrX += dif;
	}
	if(wk->key_f & KEYS_CMOVE_MX){
		wk->scrBGS0.scrX -= dif;
	}
	TMapN_SubScrollSet(pMain,wk->scrBGS0.scrX,wk->scrBGS0.scrY);

	if(wk->cmove_f > 0){
		return;
	}
	wk->view_f = VIEW_UP;	//view�X�V
	wk->key_f = 0;	//�L�[�t�b�N����

	if(wk->ozoneID != wk->czoneID){
		TownViewDataSelectPos(wk->pTView,-1,0,0);
	}
}

/**
 *	@brief	�Ŕt���[�����b�Z�[�W�\��
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static void TMap_BoardMsgSet(TMAP_MAIN_DAT* pMain,TMAP_GDAT* pBlock,int zoneID)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *name;

	//�p�����[�^�ۑ�(���ۂ̍X�V��VBlank���ɍs��)
	pMain->vb_zoneID = zoneID;
	pMain->vb_block = pBlock;
	pMain->vb_trans = 1;
	return;
}

/**
 *	@brief	�Ŕt���[���\��Off
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static void TMap_BoardGraphicOff(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	GF_BGL_BMPWIN	*win;
	
	win = wk->pBoardWin;
	wk->pBoardWin = NULL;
	if(win == NULL){
		return;
	}

	GF_BGL_BmpWinDataFill(win,FBMP_COL_NULL);
	GF_BGL_BmpWinOff(win);
	
	BmpBoardWinClear(win,wk->board_f,WINDOW_TRANS_ON);
	GF_BGL_LoadScreenV_Req(pMain->bgl,BMPL_BOARD_FRM);
}


/**
 *	@brief	�K�C�h�^�O�\��
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static void TMap_GuideTagSet(TMAP_MAIN_DAT* pMain,GF_BGL_BMPWIN* win)
{
	u32	siz;
	GF_PRINTCOLOR col;
	STRBUF *buf;

	//BG�`��
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME1_S,
			TMSCR_DSWMG_DPX,TMSCR_DSWMG_DPY,TMSCR_DSWMG_DSX,TMSCR_DSWMG_DSY,
			pMain->pScr02_dswm->rawData,
			TMSCR_DSWMG_SPX,TMSCR_DSWMG_SPY,
			pMain->pScr02_dswm->screenWidth/8,pMain->pScr02_dswm->screenHeight/8);

	//���b�Z�[�W�`��
	buf = MSGMAN_AllocString(pMain->pMsgTMap,mes_townmap_02_01);

	siz = BMPL_GUIDE_NSX-FontProc_GetPrintStrWidth( FONT_SYSTEM,buf, 0 );
	siz/=2;
	
	col = GF_PRINTCOLOR_MAKE(1,2,0);
	GF_BGL_BmpWinDataFill(win,FBMP_COL_NULL);
	GF_STR_PrintColor(	win,
						FONT_SYSTEM,
						buf,
						siz,0,
						MSG_NO_PUT,
						col,
						NULL );
	GF_BGL_BmpWinOn(win);

	STRBUF_Delete(buf);
}

/**
 *	@brief	BmpWindow������
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static void TMapN_BmpWinSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_M01], BMPL_M01_FRM,
		BMPL_M01_PX, BMPL_M01_PY, BMPL_M01_SX, BMPL_M01_SY, BMPL_M01_PAL, BMPL_M01_CGX );
	
	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BOARD0], BMPL_BOARD_FRM,
		BMPL_BOARD0_PX, BMPL_BOARD0_PY, BMPL_BOARD0_SX, BMPL_BOARD0_SY, BMPL_BOARD_PAL, BMPL_BOARD0_CGX );
	
	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BOARD1], BMPL_BOARD_FRM,
		BMPL_BOARD1_PX, BMPL_BOARD1_PY, BMPL_BOARD1_SX, BMPL_BOARD1_SY, BMPL_BOARD_PAL, BMPL_BOARD1_CGX );

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_BLOCK], BMPL_BLOCK_FRM,
		BMPL_BLOCK_PX, BMPL_BLOCK_PY, BMPL_BLOCK_SX, BMPL_BLOCK_SY, BMPL_BLOCK_PAL, BMPL_BLOCK_CGX );

	GF_BGL_BmpWinAdd(
		pMain->bgl, &wk->win[WIN_GUIDE], BMPL_GUIDE_FRM,
		BMPL_GUIDE_PX, BMPL_GUIDE_PY, BMPL_GUIDE_SX, BMPL_GUIDE_SY, BMPL_GUIDE_PAL, BMPL_GUIDE_CGX );

	//�E�B���h�E�N���A
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_M01]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BOARD0]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BOARD1]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_BLOCK]),0);
	GF_BGL_BmpWinDataFill(&(wk->win[WIN_GUIDE]),0);
	GF_BGL_BmpWinOn(&wk->win[WIN_M01]);

	GF_BGL_BmpWinOff(&wk->win[WIN_BOARD0]);
	GF_BGL_BmpWinOff(&wk->win[WIN_BOARD1]);
	GF_BGL_BmpWinOff(&wk->win[WIN_BLOCK]);
	GF_BGL_BmpWinOff(&wk->win[WIN_GUIDE]);

}

/**
 *	@brief	BmpWindow���
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static void TMapN_BmpWinExit(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	u16	i;
	for(i = 0;i < WIN_MAX;i++){
		GF_BGL_BmpWinDel(&wk->win[i]);
	}
}

/**
 *	@brief	�{�^���X�N���[���`��
 *
 *	@param	pMain	TMAP_MAIN_DAT*
 *	@param	frm		�A�j���t���[��No
 *	@param	mode	�o�b�N���������ނ��ǂ����̃t���O(�������ނƂ���On)
 */
static void TMapN_SubButtonSet(TMAP_MAIN_DAT* pMain,u8 frm,u8 mode)
{
	if(mode){
		GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME1_S,
			0,0,32,24,
			pMain->pScr02_sw->rawData,
			0,0,
			pMain->pScr02_sw->screenWidth/8,pMain->pScr02_sw->screenHeight/8);
	}
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME1_S,
		TMSCR_DSWMB_DPX,TMSCR_DSWMB_DPY,TMSCR_DSWMB_DSX,TMSCR_DSWMB_DSY,
		pMain->pScr02_dswm->rawData,
		frm*TMSCR_DSWMB_DSX+TMSCR_DSWMB_SPX,TMSCR_DSWMB_SPY,
		pMain->pScr02_dswm->screenWidth/8,pMain->pScr02_dswm->screenHeight/8);
}

/**
 *	@brief	�z�z�}�b�v�`��@�T�u���[�`��
 *	
 */
	typedef struct _HMAP{
		u8	dpx,dpy;
		u8	px,py;
		u8	sx,sy;
	}HMAP;
	
static void TMap_HaifuMapSet(TMAP_MAIN_DAT* pMain,int mode)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	static const HMAP hmap[] = {
		{HMAP01_MB_DPX,HMAP01_MB_DPY,HMAP01_MB_PX,HMAP01_MB_PY,HMAP01_MB_SX,HMAP01_MB_SY},
		{HMAP01_ML_DPX,HMAP01_ML_DPY,HMAP01_ML_PX,HMAP01_ML_PY,HMAP01_ML_SX,HMAP01_ML_SY},
		{HMAP01_SB_DPX,HMAP01_SB_DPY,HMAP01_SB_PX,HMAP01_SB_PY,HMAP01_SB_SX,HMAP01_SB_SY},
		{HMAP01_SL_DPX,HMAP01_SL_DPY,HMAP01_SL_PX,HMAP01_SL_PY,HMAP01_SL_SX,HMAP01_SL_SY},
		
		{HMAP02_MB_DPX,HMAP02_MB_DPY,HMAP02_MB_PX,HMAP02_MB_PY,HMAP02_MB_SX,HMAP02_MB_SY},
		{HMAP02_ML_DPX,HMAP02_ML_DPY,HMAP02_ML_PX,HMAP02_ML_PY,HMAP02_ML_SX,HMAP02_ML_SY},
		{HMAP02_SB_DPX,HMAP02_SB_DPY,HMAP02_SB_PX,HMAP02_SB_PY,HMAP02_SB_SX,HMAP02_SB_SY},
		{HMAP02_SL_DPX,HMAP02_SL_DPY,HMAP02_SL_PX,HMAP02_SL_PY,HMAP02_SL_SX,HMAP02_SL_SY},
		
		{0,0,0,0,0,0},
		{HMAP03_ML_DPX,HMAP03_ML_DPY,HMAP03_ML_PX,HMAP03_ML_PY,HMAP03_ML_SX,HMAP03_ML_SY},
		{0,0,0,0,0,0},
		{HMAP03_SL_DPX,HMAP03_SL_DPY,HMAP03_SL_PX,HMAP03_SL_PY,HMAP03_SL_SX,HMAP03_SL_SY},
		
		{HMAP04_MB_DPX,HMAP04_MB_DPY,HMAP04_MB_PX,HMAP04_MB_PY,HMAP04_MB_SX,HMAP04_MB_SY},
		{HMAP04_ML_DPX,HMAP04_ML_DPY,HMAP04_ML_PX,HMAP04_ML_PY,HMAP04_ML_SX,HMAP04_ML_SY},
		{HMAP04_SB_DPX,HMAP04_SB_DPY,HMAP04_SB_PX,HMAP04_SB_PY,HMAP04_SB_SX,HMAP04_SB_SY},
		{HMAP04_SL_DPX,HMAP04_SL_DPY,HMAP04_SL_PX,HMAP04_SL_PY,HMAP04_SL_SX,HMAP04_SL_SY},
	};
	HMAP* mback,*mload,*sback,*sload;

	mback = (HMAP*)&(hmap[mode*4+0]);
	mload = (HMAP*)&(hmap[mode*4+1]);
	sback = (HMAP*)&(hmap[mode*4+2]);
	sload = (HMAP*)&(hmap[mode*4+3]);

	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME2_M,
			mload->px,mload->py,mload->sx,mload->sy,
			pMain->pScr01_dis->rawData,
			mload->dpx,mload->dpy,SCWS_GET(pMain->pScr01_dis),SCHS_GET(pMain->pScr01_dis));	

	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME2_S,
			sload->px,sload->py,sload->sx,sload->sy,pMain->pScr02_dis->rawData,
			sload->dpx,sload->dpy,SCWS_GET(pMain->pScr02_dis),SCHS_GET(pMain->pScr02_dis));
	
	if(mode == HIDEMAP_ID_L04){
		return;
	}
	//�w�i�}�b�v
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
			mback->px,mback->py,mback->sx,mback->sy,
			pMain->pScr01_dis->rawData,
			mback->dpx,mback->dpy,SCWS_GET(pMain->pScr01_dis),SCHS_GET(pMain->pScr01_dis));	

	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME3_S,
			sback->px,sback->py,sback->sx,sback->sy,pMain->pScr02_dis->rawData,
			sback->dpx,sback->dpy,SCWS_GET(pMain->pScr02_dis),SCHS_GET(pMain->pScr02_dis));
}

/**
 *	@brief �m�[�}�����[�h�@BG�f�[�^�Z�b�g
 */
static void TMapN_2DGrapDefSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	int sp = 0;
	
	//���[�h
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME2_M,
			0,0,32,24,
			pMain->pScr01->rawData,
			0,0,SCWS_GET(pMain->pScr01),SCHS_GET(pMain->pScr01));	

	//�w�i�}�b�v
	GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
			0,0,32,24,
			pMain->pScr01_back->rawData,
			0,0,SCWS_GET(pMain->pScr01_back),SCHS_GET(pMain->pScr01_back));	
	
	if(pMain->mode != TMAP_MJUMP){
		sp = ZONEN_BG_SY;
		GF_BGL_ScrWriteExpand(pMain->bgl,GF_BGL_FRAME3_M,
				ZONEN_BG_PX,ZONEN_BG_PY,ZONEN_BG_SX,ZONEN_BG_SY,
				pMain->pScr01_back->rawData,
				0,ZONEN_BG_PY,SCWS_GET(pMain->pScr01_back),SCHS_GET(pMain->pScr01_back));	
	}
	
	//�T�u
	TMapN_SubButtonSet(pMain,0,1);
	
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME2_S,0,0,64,64,pMain->pScr02_dr->rawData,
			0,0,pMain->pScr02_dr->screenWidth/8,pMain->pScr02_dr->screenHeight/8);
	GF_BGL_ScrWriteFree(pMain->bgl,GF_BGL_FRAME3_S,0,0,64,64,pMain->pScr02_dm->rawData,
			0,0,pMain->pScr02_dm->screenWidth/8,pMain->pScr02_dm->screenHeight/8);

	//�z�z�}�b�v�̕`��
//	pMain->mapView = 0x0F;
	if(pMain->mapView & 0x0001){	//�z�z�}�b�v1 D15
		TMap_HaifuMapSet(pMain,0);
	}
	if(pMain->mapView & 0x0002){	//�z�z�}�b�v2 D30
		TMap_HaifuMapSet(pMain,1);
	}
	if(pMain->mapView & 0x0004){	//�z�z�}�b�v3 L4
		TMap_HaifuMapSet(pMain,2);
	}
	if(pMain->mapView & 0x0008){	//�z�z�}�b�v4 D18
		TMap_HaifuMapSet(pMain,3);
	}
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_S);
}

static void TMapN_2DGrapClear(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//�X�N���[�����Z�b�g
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,0);
	GF_BGL_ScrollSet(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,0);
	
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME2_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME3_M,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME2_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME3_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_M);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_M);
	
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME2_S);
	GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME3_S);
}

/**
 *	@brief �m�[�}�����[�h�@�A�N�^�[�Z�b�g
 */
static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
{
	{	// �{�^���G�t�F�N�g
		0,	//ID
		0, 0, 0,	//x,y,z
		0, TMAP_SPRI_BTN, 0, NNS_G2D_VRAM_TYPE_2DSUB,	//anmNO,pri,pal,d_area
		0, 0, 0, 0	//prm1,prm2,prm3,prm4
	},
	{	// ���C���J�[�\�� 
		1,
		0, 0, 0,
		0, TMAP_SPRI_CUR, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{	// ���C�����@ 
		2,
		0, 0, 0,
		0, TMAP_SPRI_HERO, 1, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
};

static void TMapN_CellActSet(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	//�T�u��ʗp�{�^��
	wk->pCAW_btn =	CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[0] );

	CLACT_SetDrawFlag(wk->pCAW_btn, 0 );
	CLACT_SetAnmFrame(wk->pCAW_btn,FX32_ONE);
	CATS_ObjectPosSet(wk->pCAW_btn,128,108);

	//���C���J�[�\��
	wk->pCAW_cur =	CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[1] );

	CLACT_SetDrawFlag(wk->pCAW_cur, 1 );
	CLACT_SetAnmFrame(wk->pCAW_cur,FX32_CONST(2));
	CLACT_SetAnmFlag(wk->pCAW_cur,1);
	CATS_ObjectPosSet(wk->pCAW_cur,
			wk->cposX*CMOVE_UNIT+CMOVE_OFSX,wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);

	//���C�����@
	wk->pCAW_hero = CATS_ObjectAdd( pMain->pCActSys,
			pMain->pCActRes,
			&ActAddParam[2]);

	CLACT_SetDrawFlag(wk->pCAW_hero,1);
	CLACT_AnmFrameSet(wk->pCAW_hero,pMain->param->player_sex);
	CATS_ObjectPosSet(wk->pCAW_hero,
			wk->cposX*CMOVE_UNIT+CMOVE_OFSX,wk->cposZ*CMOVE_UNIT+CMOVE_OFSZ);
}

/**
 *	@brief	�m�[�}�����[�h�T�u��ʃX�N���[���l�Z�b�g	
 */
static void TMapN_SubScrollSet(TMAP_MAIN_DAT* pMain,int x,int y)
{
	if(x < TMAPN_BGS0X_MIN){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MIN);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MIN);
	}else if(x > TMAPN_BGS0X_MAX){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MAX);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,TMAPN_BGS0X_MAX);
	}else{
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_X_SET,x);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_X_SET,x);
	}
	
	if(y < TMAPN_BGS0Y_MIN){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MIN);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MIN);
	}else if(y > TMAPN_BGS0Y_MAX){
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MAX);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,TMAPN_BGS0Y_MAX);
	}else{
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME2_S,GF_BGL_SCROLL_Y_SET,y);
		GF_BGL_ScrollReq(pMain->bgl,GF_BGL_FRAME3_S,GF_BGL_SCROLL_Y_SET,y);
	}
}

/**
 *	@brief �m�[�}�����[�h�@���Ճf�[�^������
 */
static int TMapNS_IsFootMarkHit(TMAP_FOOTVIEW* pv,int x,int z)
{
	int i = 0;
	
	for(i = 0;i < pv->num;i++){
		if(pv->foot[i].x == x && pv->foot[i].z == z){
			return i;
		}
	}
	return -1;
}

/**
 *	@brief	�m�[�}�����[�h�@���Ճ}�[�N���\�[�X�쐬
 */
static void TMapN_FootViewInit(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FOOT	*wp;
	TMAP_FVIEW	*dest;
	int i = 0,ret,idx;

	//��,��,�E,��
	static const u16 dirTable[4] = {DIR_ROT_UP,DIR_ROT_DOWN,DIR_ROT_RIGHT,DIR_ROT_LEFT};
	static const TCATS_OBJECT_ADD_PARAM	ActAddParam =
	{
		TMAP_ACTID_FOOT,	//ID
		0, 0, 0,	//x,y,z
		0, TMAP_SPRI_FOOT, TMAP_APAL_FOOT, NNS_G2D_VRAM_TYPE_2DMAIN,	//anmNO,pri,pal,d_area
		0, 0, 0, 0	//prm1,prm2,prm3,prm4
	};

	//�f�[�^���
	MI_CpuClear8(&(wk->fView),sizeof(TMAP_FOOTVIEW));
	for(i = 0;i < TMAP_FVIEW_MAX;i++){
		wp = &(pMain->param->foot[i]);
		if(wp->valid == 0){
			break;
		}
		if(wp->x == pMain->gx && wp->z == pMain->gz){
			continue;	//���݂̎��@�ʒu�̓X���[
		}
		ret = TMapNS_IsFootMarkHit(&(wk->fView),wp->x,wp->z);
		if(ret < 0){
			dest = &(wk->fView.foot[wk->fView.num++]);
		}else{
			dest = &(wk->fView.foot[ret]);
		}
		dest->x = wp->x;
		dest->z = wp->z;
		if(wp->dir > DIR_RIGHT){
			dest->dir = 0;
			idx = 5;
		}else{
			dest->dir = dirTable[wp->dir];
			idx = 0;
		}
		dest->idx = i;//(TMAP_FVIEW_MAX-1)-i;
		dest->valid = 1;

		dest->pAct = CATS_ObjectAdd(pMain->pCActSys,
				pMain->pCActRes,&(ActAddParam));

		CATS_ObjectPosSet(dest->pAct,
				dest->x*TMAP_MDOT_UNIT+TMAP_MDOT_OFSX,
				dest->z*TMAP_MDOT_UNIT+TMAP_MDOT_OFSZ);
//		CLACT_AnmFrameChg(dest->pAct,FX32_CONST(idx+dest->idx));
//		CLACT_SetRotationAffine(dest->pAct,16384*dest->dir,CLACT_AFFINE_NORMAL);
		CLACT_DrawPriorityChg(dest->pAct,2);
		CLACT_SetDrawFlag(dest->pAct,FALSE);
	}
	if(wk->fView.num == 0){
		return;
	}
	//�A�j���^�X�N�o�^
	wk->fView.now = wk->fView.num-1;
	wk->fView.tcb = TCB_Add(TMapN_FootViewTask,&wk->fView,1);
}

static void TMapN_FootViewTask(TCB_PTR tcb,void* work)
{
	TMAP_FOOTVIEW* wk = (TMAP_FOOTVIEW*)work;

	if(wk->anmct++ % 26 > 0){
		return;
	}

	//�Â��ʒu�������ĐV�����ʒu���o��
	CLACT_SetDrawFlag(wk->foot[wk->old].pAct,FALSE);
	CLACT_SetDrawFlag(wk->foot[wk->now].pAct,TRUE);

	wk->old = wk->now;
	wk->now = (wk->now+(wk->num-1))%wk->num;

	if(wk->anmct > 26*10){
		wk->anmct = 1;
	}
}

/**
 *	@brief	�m�[�}�����[�h�@���Ճ}�[�N���\�[�X���
 */
static void TMapN_FootViewRelease(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_FVIEW	*dest;
	int i = 0,ret;

	if(wk->fView.tcb != NULL){
		TCB_Delete(wk->fView.tcb);
	}
	for(i = 0;i < wk->fView.num;i++){
		dest = &(wk->fView.foot[i]);
		CATS_ObjectDel(dest->pAct);
	}
}

/**
 *	@brief	�T�u��ʃt�H�[�J�X�^�X�N�o�^
 */
static void TMapNS_AddSVForcusTask(TMAP_MAIN_DAT* pMain,int mode)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;

	wk->sub_seq = 0;
	wk->sub_ct = 0;
	if(mode == 0){
		wk->tcb = TCB_Add(TMapNS_SVForcusInTask,pMain,0);
	}else{
		wk->tcb = TCB_Add(TMapNS_SVForcusOutTask,pMain,0);
	}
}

/**
 *	@brief	�T�u��ʃt�H�[�J�XIn�^�X�N
 */
static void TMapNS_SVForcusInTask(TCB_PTR tcb,void* work)
{
	TMAP_MAIN_DAT* pMain = (TMAP_MAIN_DAT*)work;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	static const u8 btnAnmTbl[] = {1,2,1,0};

	switch(wk->sub_seq){
	case 0:
		CLACT_SetDrawFlag(wk->pCAW_btn, 1 );
		CLACT_SetAnmFlag(wk->pCAW_btn,1);	//�I�[�g�A�j���Z�b�g
		CLACT_AnmFrameSet(wk->pCAW_btn,1);	//�A�j���X�^�[�g�t���[���Z�b�g

		Snd_SePlay(SND_TMAP_SOPEN);
		wk->sub_seq++;
		break;
	case 1:
		//�{�^���A�j��
		if(wk->sub_ct % 2){
			TMapN_SubButtonSet(pMain,btnAnmTbl[wk->sub_ct/2],0);
			GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
		}
		if(wk->sub_ct++ > 7){
			wk->sub_seq++;
		}
		break;
	case 2:
		CLACT_SetDrawFlag(wk->pCAW_btn, 0);
		CLACT_SetAnmFlag(wk->pCAW_btn,0);	//�I�[�g�A�j�����~�߂�
		//�t�F�[�h�A�E�g����
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTEROUT_DOWN,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 3:
		//�t�F�[�h�҂�
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		//��ʏ�������
		wk->forcus = TMAPN_FORCUS_SUB;
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME1_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		
		TMap_GuideTagSet(pMain,&(wk->win[WIN_GUIDE]));
		TMapN_BlockReset(pMain);
		TMapN_BlockChange(pMain);

		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTERIN_UP,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 4:
		if(!WIPE_SYS_EndCheck()){
			return; 
		}
		wk->sub_ct = 0;
		wk->sub_seq = 0;
		wk->tp_f -= 2;
		TCB_Delete(tcb);
		wk->tcb = NULL;
		break;
	}
}

/**
 *	@brief	�T�u��ʃt�H�[�J�X�A�E�g�^�X�N
 */
static void TMapNS_SVForcusOutTask(TCB_PTR tcb,void* work)
{
	TMAP_MAIN_DAT* pMain = (TMAP_MAIN_DAT*)work;
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	
	switch(wk->sub_seq){
	case 0:
		//�t�F�[�h�A�E�g����
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTEROUT_DOWN,0x0000,8,1,pMain->heapID
				);
		Snd_SePlay(SND_TMAP_SCLOSE);
		wk->sub_seq++;
		break;
	case 1:
		//�t�F�[�h�҂�
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		GF_BGL_ScrFill(pMain->bgl,GF_BGL_FRAME0_S,0x0000,0,0,32,32,GF_BGL_SCRWRT_PALIN);
		TMapN_SubButtonSet(pMain,0,1);
	
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME0_S);
		GF_BGL_LoadScreenV_Req(pMain->bgl,GF_BGL_FRAME1_S);
	
		pMain->wipe_f = 0;
		WIPE_SYS_Start(WIPE_PATTERN_S,
				WIPE_TYPE_SPLITIN_HCENTER,
				WIPE_TYPE_SHUTTERIN_UP,0x0000,8,1,pMain->heapID
				);
		wk->sub_seq++;
		break;
	case 2:
		if(!WIPE_SYS_EndCheck()){
			return;
		}
		wk->forcus = TMAPN_FORCUS_MAIN;
		wk->sub_seq = 0;
		wk->sub_ct = 0;
		wk->tp_f -= 2;
		TCB_Delete(tcb);
		wk->tcb = NULL;
		return;
	}
	return;
}

/**
 *	@brief	�W�����v���[�h�AA����`�F�b�N
 *	@param	pMain TMAP_MAIN_DAT�ւ̃|�C���^
 */
static int TMapJ_CheckJumpPos(TMAP_MAIN_DAT* pMain)
{
	TMAP_MODE_NORMAL* wk = pMain->pSwork;
	TMAP_VIEW_OBJ *pd = NULL;
	u8	jump_f = 1;

	if(wk->pBlock == NULL){
		return 0;	//����ԂŔ�ׂȂ��ꏊ
	}
	pd = TownViewDataSearchPos(wk->pTView,wk->czoneID,wk->cposX,wk->cposZ);

#ifdef PM_DEBUG
	if(pd == NULL || pd->flag == 0){
		if(pMain->param->debug_f == 0){
			return 0;	//�܂���ׂȂ�
		}
	}
#else	//ifdef PM_DEBUG
	if(pd == NULL || pd->flag == 0){
		return 0;	//�܂���ׂȂ�
	}
#endif	//ifdef PM_DEBUG
	
	pMain->param->retval = 1;
	pMain->param->ret_x = wk->cposX;
	pMain->param->ret_z = wk->cposZ;
	pMain->param->ret_zone = wk->czoneID;
	return 1;
}
