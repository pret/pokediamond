/**
 *	@file	porucase_bmp.c
 *	@brief	�|���g�P�[�XBMP�E�B���h�E����
 *	@author Miyuki Iwasawa
 *	@date	06.03.15
 */

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/buflen.h"
#include "system/window.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/window.h"
#include "system/poruto_name.h"
#include "system/pmfprint.h"
#include "application/app_tool.h"
#include "application/poru_tool.h"
#include "savedata/poruto_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"
#include "porusys.h"
#include "poru_act.h"
#include "porucase_bmp.h"

#define LV_OFS_X	(8)
#define PORULIST_MAX	(6)

static void PoruListCB_ForLine(BMPLIST_WORK* work,u32 param,u8 y);
static void PoruListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode );
static void MenuListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode );

static const BMPLIST_HEADER PoruListHeader = {
	NULL,					//�\�������f�[�^�|�C���^
	PoruListCB_ForMove,PoruListCB_ForLine,	//�R�[���o�b�N(�J�[�\���ړ�����/��s����)
	NULL,					//GF_BGL_BMPWIN�\���̃f�[�^�ւ̃|�C���^
	0,PORULIST_MAX,					//���X�g���ڐ�,�\���ő區�ڐ�
	0,8,0,					//�\��X���W(���x��/����/�J�[�\��)
	0,						//�\���x���W
	FBMP_COL_BLACK,FBMP_COL_NULL,FBMP_COL_BLK_SDW,		//�����F,�w�i�F,�e�F
	0,0,				//�����ԊuX,Y
//	BMPLIST_NO_SKIP,	//�y�[�W�X�L�b�v�^�C�v
	BMPLIST_LRKEY_SKIP,	//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,		//�����w��
	1,					//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
	NULL,				//���[�N�|�C���^
};
static const BMPLIST_HEADER MenuListHeader = {
	NULL,					//�\�������f�[�^�|�C���^
	MenuListCB_ForMove,NULL,	//�R�[���o�b�N(�J�[�\���ړ�����/��s����)
	NULL,					//GF_BGL_BMPWIN�\���̃f�[�^�ւ̃|�C���^
	0,3,					//���X�g���ڐ�,�\���ő區�ڐ�
	0,8,0,					//�\��X���W(���x��/����/�J�[�\��)
	0,						//�\���x���W
	FBMP_COL_BLACK,FBMP_COL_WHITE,FBMP_COL_BLK_SDW,		//�����F,�w�i�F,�e�F
	0,0,				//�����ԊuX,Y
	BMPLIST_NO_SKIP,	//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,		//�����w��
	0,					//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
	NULL,				//���[�N�|�C���^
};

/**
 *	@brief	�|���g���X�g���[�N�N���A
 */
static void porulist_linkClear(PORU_LIST* pl)
{
	pl->view = 0;
	pl->next = pl->prev = 0xFF;
}

/**
 * @brief	�|���g���b�Z�[�W�`��
 */
static void poru_msgWrite(PORU_CASE_WORK* wk,STRBUF* msg,u8 spd,u8 win_f)
{
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE);

	//�E�B���h�E�`��
	if(win_f){
		BmpTalkWinWrite( &wk->win[WIN_MSG], WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL);
	}
	GF_BGL_BmpWinFill( &(wk->win[WIN_MSG]),WINCLR_COL(FBMP_COL_WHITE),
		0, 0,BMPL_MSG_SX*8,BMPL_MSG_SY*8);

	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_SKIP_OFF );
	
	//���b�Z�[�W�`��
	wk->msgIdx = GF_STR_PrintColor(
		&wk->win[WIN_MSG], FONT_TALK, msg,
		0, 0, spd, col, NULL );
}

/**
 *	@brief	�|���g���X�g�̃��[�h�ʗv�f��
 */
static u16 PoruList_GetListNum(PORUTO_PARAM* pp,PORU_CASE_WORK* wk)
{
	u16 i,count = 0;
	u8 mode,flag;
	PORU_LIST* pl;

	wk->startID = wk->endID = 0xFF;

	if(wk->viewMode == 5){
		mode = 0x1F;
	}else{
		mode = 1;
		for(i = 0;i < wk->viewMode;i++){
			mode <<= 1;
		}
	}
	
	for(i = 0;i < pp->porunum;i++){
		pl = &pp->list[i];
		porulist_linkClear(pl);
		if((!pl->valid) || pl->del){
			continue;
		}
		flag = (pl->flags & 0x1F);
		if((flag & mode) == 0){
			continue;
		}
		pl->view = 1;	//view�t���OOn

		//���X�g���q��
		if(wk->startID == 0xFF){
//			wk->startID = wk->endID = pl->myid;
			wk->startID = pl->myid;
		}else{
			pp->list[wk->endID].next = pl->myid;
		}
		pl->prev = wk->endID; 
		wk->endID = pl->myid;
		++count;
	}
	//�z���X�g�����
//	pp->list[wk->endID].next = wk->startID;
//	pp->list[wk->startID].prev = wk->endID;
	
	//�u��߂�v���ڕ��͕K���m��
	count += 1;
	
	return count;
}

/**
 *	@brief	�|���g���X�g���j���[�쐬
 */
void PoruList_CreatePMenu(PORU_CASE_WORK* wk)
{
	u8 i = 0,next = 0;
	PORU_LIST* pl;
	
	wk->viewNum =  PoruList_GetListNum(wk->param,wk);
	
	//BMP���X�g�̈�쐬
	wk->plist = BMP_MENULIST_Create(wk->viewNum,wk->heapID);

//	for(i = wk->startID;i != 0xFF;i = next){
	for(i = wk->endID;i != 0xFF;i = next){
		pl = &(wk->param->list[i]);
		next = pl->prev;//pl->next;
		
		WORDSET_RegisterWord(wk->msgDat.wset,0,
				PorutoName_GetNameAdrByMan(wk->nameMan,pl->flavor),
				PM_MALE,FALSE,PM_LANG);
		WORDSET_RegisterNumber(wk->msgDat.wset,1,pl->level,2,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.listbuf);
		BMP_MENULIST_AddString(wk->plist,wk->msgDat.tmp,pl->myid);

	//	BMP_MENULIST_AddString(wk->plist,
	//		PorutoName_GetNameAdrByMan(wk->nameMan,pl->flavor),pl->myid);
	}

	//�u��߂�v�����X�g�ɒǉ�
	BMP_MENULIST_AddString(wk->plist,wk->msgDat.endbuf,0xFF);

	//BMP���X�g��������
	MI_CpuCopy8(&PoruListHeader,&wk->plist_h,sizeof(BMPLIST_HEADER));

	wk->curPos = wk->param->curPos;		//�O��̈ʒu�𕜋A
	wk->listPos = wk->param->listPos;

	//���X�g�����ЂƂ����Ă���΃J�[�\���ʒu���}�C�i�X�␳
	if(wk->param->ret_mode){
		if(wk->listPos == 0){
			if(wk->curPos != 0 && wk->curPos >= (wk->viewNum-1)){
				--wk->curPos;
			}
		}else{
			if(wk->listPos+PORULIST_MAX >= wk->viewNum){
				--wk->listPos;
			}
		}
		wk->param->ret_mode = 0;
	}
	wk->plist_h.win = &(wk->win[WIN_PLIST]);
	wk->plist_h.list = wk->plist;
	wk->plist_h.work = (void*)wk;
	wk->plist_h.count = wk->viewNum;

	//���X�g�ǉ�
	wk->plist_cb_f = 0;
	wk->plist_wk = BmpListSet(&wk->plist_h,wk->listPos,wk->curPos,wk->heapID);
	wk->plist_cb_f = 1;
	//LV�\���E�B���h�EOn
//	GF_BGL_BmpWinOn(&wk->win[WIN_PLISTLV]);
}

/**
 *	@brief	�|���g���X�g�@���j���[���X�g�폜
 */
void PoruList_DeletePMenu(PORU_CASE_WORK* wk,BOOL trans)
{
	//�E�B���h�E�̈揉����
	GF_BGL_BmpWinFill( &(wk->win[WIN_PLIST]),WINCLR_COL(FBMP_COL_NULL),
			0, 0,BMPL_PLIST_SX*8,BMPL_PLIST_SY*8);
//	GF_BGL_BmpWinFill( &(wk->win[WIN_PLISTLV]),WINCLR_COL(FBMP_COL_NULL),
//			0, 0,BMPL_PLISTLV_SX*8,BMPL_PLISTLV_SY*8);

	if(trans){
		GF_BGL_BmpWinOff(&wk->win[WIN_PLIST]);
//		GF_BGL_BmpWinOff(&wk->win[WIN_PLISTLV]);
	}

	//���X�g���
	BmpListExit(wk->plist_wk,&(wk->listPos),&(wk->curPos));
	BMP_MENULIST_Delete(wk->plist);

	//�J�[�\���ʒu�ۑ�
	wk->param->listPos = wk->listPos;
	wk->param->curPos = wk->curPos;

	wk->plist_wk = NULL;
	wk->plist = NULL;
}

/**
 *	@brief	�|���g�{�^���v�b�V��������
 */
void PoruBtn_StateSet(PORU_CASE_WORK* wk,u8 idx,u8 state)
{
	switch(state){
	case BACT_ST_NULL:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN);
		CLACT_SetAnmFlag(wk->pActBtn[idx],FALSE);
		GF_BGL_BmpWinShift(
				&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_D,
				2, WINCLR_COL(FBMP_COL_NULL) );
		break;
	case BACT_ST_01:
		CLACT_AnmReStart( wk->pActBtn[idx]);
		CLACT_SetAnmFlag(wk->pActBtn[idx],TRUE);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			4, WINCLR_COL(FBMP_COL_NULL) );
		
		wk->tp_f = BACT_ST_01;
		break;
	case BACT_ST_02:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_01);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_D,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_NULL;
		break;
	case BACT_ST_03:
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_02);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_01;
		break;
	case BACT_ST_INI_PUSH:
		//�P�[�X���������ɉ�������Ԃɂ���R�}���h
		CLACT_AnmChg(wk->pActBtn[idx],idx*BACT_PTN+BACT_ST_01);
		CLACT_SetAnmFlag(wk->pActBtn[idx],TRUE);
		GF_BGL_BmpWinShift(
			&wk->win[WIN_SW01+idx], GF_BGL_BMPWIN_SHIFT_U,
			2, WINCLR_COL(FBMP_COL_NULL) );

		wk->tp_f = BACT_ST_NULL;
		break;
	}
	GF_BGL_BmpWinOn(&wk->win[WIN_SW01+idx]);
}

/**
 *	@brief	�|���g���X�g�\�[�g
 */
void PoruList_SortMenu(PORU_CASE_WORK* wk,u8 mode)
{
	int siz;
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

	//SE
	Snd_SePlay(PORUC_SE_BTN);
	
	//�{�^���t�H���g&�A�j������
	if(wk->tp_f != BACT_ST_INI){
		//���݂̃��[�h�`�F�b�N
		if(mode == wk->viewMode){
			PoruBtn_StateSet(wk,mode,BACT_ST_03);
			return;
		}
		PoruBtn_StateSet(wk,wk->viewMode,BACT_ST_NULL);
	}
	PoruBtn_StateSet(wk,mode,BACT_ST_01);
	wk->viewMode = mode;
	PoruList_DeletePMenu(wk,FALSE);

	//�J�[�\���ʒu���Z�b�g
	wk->listPos = wk->curPos = 0;
	wk->param->listPos = wk->param->curPos = 0;
	PoruList_CreatePMenu(wk);

	//����ʐ����؂�ւ�
	GF_BGL_BmpWinFill( &(wk->win[WIN_EXPS]),WINCLR_COL(FBMP_COL_NULL),
		0, 0,BMPL_EXPS_SX*8,BMPL_EXPS_SY*8);
	if(wk->viewMode == PVIEW_ALL){
		GF_BGL_BmpWinOn(&wk->win[WIN_EXPS]);
		return;
	}
	siz =	(BMPL_EXPS_SX*8)-
			FontProc_GetPrintStrWidth(FONT_SYSTEM,wk->msgDat.exbuf[wk->viewMode],0);

	GF_STR_PrintColor(
		&wk->win[WIN_EXPS], FONT_SYSTEM,
		wk->msgDat.exbuf[wk->viewMode],
		siz/2, 2, MSG_ALLPUT, col, NULL );
}

/**
 *	@brief	���}�[�N�A�N�^�[�Z�b�g
 */
static void flaverActSet(PORU_CASE_WORK* wk,PORU_LIST* pl)
{
	u8 i = 0,flag = 0x01;

	if(pl == NULL){
		for(i = 0;i < 5;i++){
			CLACT_SetDrawFlag(wk->pActFmk[i], 0);
		}
		return;
	}
	for(i = 0;i < 5;i++){
		if(pl->flags&flag){
			CLACT_SetDrawFlag(wk->pActFmk[i], 1);
		}else{
			CLACT_SetDrawFlag(wk->pActFmk[i], 0);
		}
		flag <<= 1;
	}
}

/**
 *	@brief	�|���g���X�g�@���j���[�R�[���o�b�O(���\������)
 *	
 *	@param	work	BMP���X�g�Őݒ肵�����[�N
 *	@param	index	BMP���X�g���g�p���Ă���E�B���h�E�C���f�b�N�X
 *	@param	param	BMP���X�g�̃p�����[�^
 *	@param	y		Y���W
 *
 *	@return	none
 */
//--------------------------------------------------------------------------------------------
static void PoruListCB_ForLine(BMPLIST_WORK* work,u32 param,u8 y)
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)BmpListParamGet(work,BMPLIST_ID_WORK);
	GF_PRINTCOLOR col;
	
	col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

#if 0
	if(wk->plist_cb_f){	//���������ȊO�Ȃ珈������
		//�f�[�^�V�t�g
		if(sys.repeat & PAD_KEY_UP){
			GF_BGL_BmpWinShift(
				&wk->win[WIN_PLISTLV], GF_BGL_BMPWIN_SHIFT_D,
				16, WINCLR_COL(FBMP_COL_NULL) );
		}else if(sys.repeat & PAD_KEY_DOWN){
			GF_BGL_BmpWinShift(
				&wk->win[WIN_PLISTLV], GF_BGL_BMPWIN_SHIFT_U,
				16, WINCLR_COL(FBMP_COL_NULL) );
		}
	}

	//LV�\��	
	if(param == 0xFF){
		GF_BGL_BmpWinFill( &(wk->win[WIN_PLISTLV]),WINCLR_COL(FBMP_COL_NULL),
			0, y,BMPL_PLISTLV_SX*8,16);
	}else{
		GF_STR_PrintColor(
			&wk->win[WIN_PLISTLV], FONT_SYSTEM, wk->param->list[param].lvbuf,
			LV_OFS_X, y, MSG_NO_PUT, col, NULL );
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	�|���g���X�g�@���j���[�R�[���o�b�O(�J�[�\���ړ�����)
 *
 * @param	work	BMP���X�g�Őݒ肵�����[�N
 * @param	param	BMP���X�g�̃p�����[�^
 * @param	mode	�������� = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PoruListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	PORU_CASE_WORK* wk = (PORU_CASE_WORK*)BmpListParamGet(work,BMPLIST_ID_WORK);
	GF_PRINTCOLOR col;
	u16 scr,cur;
	u8 taste = 0;

	col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);

	if(!mode){
		Snd_SePlay(PORUC_SE_SEL);
	}
	//�J�[�\���ړ�
	BmpListPosGet( work, &scr, &cur );
	CATS_ObjectPosSet(wk->pAct[NACT_CURSOR],NACT_CUR_PX,cur*NACT_CUR_SY+NACT_CUR_PY);
	
	//���}�[�N�`��R���g���[��
	if(scr == 0){
		CLACT_SetDrawFlag(wk->pAct[NACT_UP],FALSE);
	}else{
		CLACT_SetDrawFlag(wk->pAct[NACT_UP],TRUE);
	}
	if(scr < (wk->viewNum-PORULIST_MAX)){
		CLACT_SetDrawFlag(wk->pAct[NACT_DOWN],TRUE);
	}else{
		CLACT_SetDrawFlag(wk->pAct[NACT_DOWN],FALSE);
	}

	//�Ȃ߂炩���E�B���h�E��U�N���A
	GF_BGL_BmpWinFill( &(wk->win[WIN_TASTE]),WINCLR_COL(FBMP_COL_NULL),
		0, 0,BMPL_TASTE_SX*8,BMPL_TASTE_SY*8);

	if(param == 0xFF){
		flaverActSet(wk,NULL);
		GF_BGL_BmpWinOn(&wk->win[WIN_TASTE]);
		CATS_ObjectEnableCap(wk->pOam->act,FALSE);
		return;
	}
	//�}�[�N�`��
	flaverActSet(wk,&wk->param->list[param]);
	
	//�Ȃ߂炩���\��
	STRBUF_Clear(wk->msgDat.tmp);

	taste = wk->param->list[param].taste;
	if(taste > 99){
		taste = 99;
	}
	WORDSET_RegisterNumber(wk->msgDat.wset,0,taste,2,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.tbuf);		
	
	GF_STR_PrintColor(
		&wk->win[WIN_TASTE], FONT_SYSTEM, wk->msgDat.tmp,
		8, 0, MSG_ALLPUT, col, NULL );
	
	//�|���g�摜�X�V
	PoruOam_ChangeFlavor(wk->poruMan,wk->pOam,wk->param->list[param].flavor);
	CATS_ObjectEnableCap(wk->pOam->act,TRUE);
}

/**
 *	@brief	���j���[���X�g�쐬
 */
void MenuList_Create(PORU_CASE_WORK* wk)
{
	u8 i = 0;
	
	//BMP���X�g�̈�쐬
	wk->mlist = BMP_MENULIST_Create(MLIST_MAX,wk->heapID);

	for(i = 0;i < MLIST_MAX;i++){
		BMP_MENULIST_AddArchiveString(wk->mlist,
			wk->msgMan,mes_p_select_02_01+i,i);
	}

	//BMP���X�g��������
	MI_CpuCopy8(&MenuListHeader,&wk->mlist_h,sizeof(BMPLIST_HEADER));

	wk->mlist_h.win = &(wk->win[WIN_MENU]);
	wk->mlist_h.list = wk->mlist;
	wk->mlist_h.work = (void*)wk;
	wk->mlist_h.count = MLIST_MAX;

	//�E�B���h�E�t���[���`��
	BmpMenuWinWrite( &wk->win[WIN_MENU], WINDOW_TRANS_OFF, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );

	//���X�g�ǉ�
	wk->mlist_wk = BmpListSet(&wk->mlist_h,0,0,wk->heapID);
}

/**
 *	@brief	���j���[���X�g�폜
 */
void MenuList_Delete(PORU_CASE_WORK* wk)
{
	u16 cur,list;
	
	//�E�B���h�E�N���A
	BmpMenuWinClear(&(wk->win[WIN_MENU]),WINDOW_TRANS_ON);	
	GF_BGL_BmpWinOff(&wk->win[WIN_MENU]);

	//���X�g���
	BmpListExit(wk->mlist_wk,&list,&cur);
	BMP_MENULIST_Delete(wk->mlist);

	wk->mlist_wk = NULL;
	wk->mlist = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	���j���[���X�g�@���j���[�R�[���o�b�O(�J�[�\���ړ�����)
 *
 * @param	work	BMP���X�g�Őݒ肵�����[�N
 * @param	param	BMP���X�g�̃p�����[�^
 * @param	mode	�������� = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MenuListCB_ForMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	if(!mode){
		Snd_SePlay(PORUC_SE_SEL);
	}
}

/**
 *	@brief	YesNo�E�B���h�E�`��O���b�Z�[�W�\��
 */
void YesNoList_StartMsgSet(PORU_CASE_WORK* wk)
{
	//�|���g���̂Ă܂������b�Z�[�W�`��
	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterWord( wk->msgDat.wset,0,
			PorutoName_GetNameAdrByMan(wk->nameMan,wk->param->list[wk->selectID].flavor),
			PM_NEUTRAL,TRUE,PM_LANG);
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.qbuf);		

	poru_msgWrite(wk,wk->msgDat.tmp,wk->msgDat.msg_spd,TRUE);
}

/**
 *	@brief	�|���g���̂Ă܂����b�Z�[�W�Z�b�g
 */
void YesNoList_DelMsgSet(PORU_CASE_WORK* wk)
{
	//�|���g���̂Ă܂������b�Z�[�W�`��
	STRBUF_Clear(wk->msgDat.tmp);
	WORDSET_RegisterWord( wk->msgDat.wset,0,
			PorutoName_GetNameAdrByMan(wk->nameMan,wk->param->list[wk->selectID].flavor),
			PM_NEUTRAL,TRUE,PM_LANG);
	WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.dbuf);		

	poru_msgWrite(wk,wk->msgDat.tmp,wk->msgDat.msg_spd,FALSE);
}

/**
 *	@brief	YesNo�E�B���h�E������
 */
void YesNoList_Create(PORU_CASE_WORK* wk)
{
	// �͂��E������
	static const BMPWIN_DAT YesNoBmpWin = {
		BMPL_MYN_FRM,BMPL_MYN_PX,BMPL_MYN_PY,BMPL_MYN_SX,BMPL_MYN_SY,
		BMPL_MYN_PAL,BMPL_MYN_CGX
	};

	wk->ynmenu_wk = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, wk->heapID);
}

/**
 *	@brief	������ʕ`�惁�b�Z�[�W�Z�b�g
 */
void PoruCase_DrawInitialMsg(PORU_CASE_WORK* wk)
{
	int siz,i;
	GF_PRINTCOLOR col = GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL);
	GF_PRINTCOLOR scol = GF_PRINTCOLOR_MAKE(2,3,1);
//	GF_PRINTCOLOR scol = GF_PRINTCOLOR_MAKE(2,3,15);
	
	//�^�C�g���`��
	GF_STR_PrintColor(
		&wk->win[WIN_EXPM], FONT_SYSTEM, wk->msgDat.sbuf,
		4, 0, MSG_ALLPUT, col, NULL );

	//�{�^�����b�Z�[�W�`��
	for(i = 0;i < PVIEW_MAX;i++){
		static const u8 ypos[] = {2,2,4,6,2,6};
		siz = (BMPL_SW01_SX*8)-
			  FontProc_GetPrintStrWidth(FONT_BUTTON,wk->msgDat.swbuf[i],0);
		GF_STR_PrintColor(
			&wk->win[WIN_SW01+i], FONT_BUTTON, wk->msgDat.swbuf[i],
			siz/2, ypos[i], MSG_ALLPUT, scol,NULL );
	}
}

