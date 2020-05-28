/**
 *	@file	fld_mailbox.c
 *	@brief	�t�B�[���h���[���{�b�N�X����
 *	@author	Miyuki Iwasawa
 *	@date	06.03.03
 */

#include "common.h"
#include "fld_bmp.h"
#include "fntsys.h"
#include "talk_msg.h"
#include "fieldmap.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/brightness.h"
#include "system/wipe.h"
#include "system/buflen.h"
#include "system/pm_str.h"
#include "system/arc_util.h"
#include "system/pmfprint.h"
#include "system/snd_tool.h"
#include "gflib/strbuf.h"
#include "gflib/strbuf_family.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "field/fieldsys.h"
#include "field/field.h"
#include "field/field_event.h"
#include "field/fld_comact.h"
#include "field/script_def.h"
#include "field/field_3d_anime_ev.h"
#include "field/paso_anm.h"

#include "savedata/mail_util.h"
#include "application/mailtool.h"
#include "msgdata/msg_mailbox.h"
#include "msgdata/msg.naix"

typedef struct _MAIL_LIST{
	u8	id;
	u8	valid;
	u8	prev;
	u8	next;
	u8	sex;
	u8	design;
	u16	itemno;
	STRBUF	*name;
}MAIL_LIST;

typedef struct{
	u32	str_id;
	u32	param;
}MENU_PARAM;

typedef enum{
 MIDX_SELECT,	//�ǂ����܂����H
 MIDX_DSEL,		//���e�������܂��������ł����H
 MIDX_POKE,		//�|�P�����ɂ������܂����H
 MIDX_TOBAG,	//�o�b�O�ɂ��ǂ��܂����H
 MIDX_BAGFULL,	//�o�b�O�������ς�
 MIDX_POKECANCEL,	//��������̂���߂܂���
 MIDX_MAX,
}MBOX_MSGIDX;

typedef struct _MAILBOX_MSG{
	WORDSET* wset;	//���[�N
	STRBUF*	tmp;	//�ėp

	STRBUF* ebuf;	//��߂�
	STRBUF* tbuf;	//�^�C�g��
	STRBUF*	mbuf[MIDX_MAX];
}MAILBOX_MSG;

typedef struct _MAIL_BOX_MAIN{
	int	heapID;
	int* end_flag;
	TCB_PTR		tcb;
	TCB_FUNC	next_tcb;
	
	u16	seq;
	u16	sub_seq;
	u16 win_type;
	u8	msg_spd;
	u8	selPos;
	
	u8	selectID;
	u8	listEnd;
	u8	listStart;
	u8	listSize;
	MAIL_LIST	mailList[MAIL_STOCK_PASOCOM];

	MSGDATA_MANAGER* pMsg;
	MAILBOX_MSG		msgDat;

	u8		msgIdx;
	u8		msgwin_f;
	u8		delMode;	
	u8		listMode:4;	
	u8		listdel_f:2;	
	u8		additem_f:2;	

	u16		List;
	u16		Cursor;
	BMPLIST_HEADER	bmplist_h;
	BMPLIST_WORK*	blistWk; 
	BMPLIST_DATA*	menulist; 
	BMPMENU_WORK*	ynmenu_wk;
	
	FIELDSYS_WORK*	fsys;
	GF_BGL_INI* bgl;
	GF_BGL_BMPWIN	bmpwin;
	GF_BGL_BMPWIN	msgwin;
	GF_BGL_BMPWIN	titlewin;
	FLD_COMACT_WORK*	fca;

	MAIL_PARAM	*param;
	MAIL_BLOCK* pBlock;
	MYITEM*		itemSave;
	
	PLIST_DATA*	plist;
#ifdef PM_DEBUG
	u16	deb_flag;	///<�f�o�b�O�R���p�C�����̂ݗL���ȃt���O
	u16 deb_design;	///<�f�o�b�O���̂ݗL���ȃf�U�C���t���O
#endif	//PM_DEBUG
}MAIL_BOX_MAIN;


//===============================================
//�萔��`
//===============================================
#define FADEOUT		WIPE_TYPE_FADEOUT
#define FADEIN		WIPE_TYPE_FADEIN
#define LIST_MAIL	(0)
#define LIST_SELECT	(1)

#define TALK_FCOL	(GF_PRINTCOLOR_MAKE(FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE))
#define BMPL_MENU_WIN_CGX	(MENU_WIN_CGX_NUM)
#define BMPL_TALK_WIN_CGX	(TALK_WIN_CGX_NUM)
#define BMPL_MENU_WIN_PAL	(FLD_MENUFRAME_PAL)
#define BMPL_TALK_WIN_PAL	(FLD_MESFRAME_PAL)

//��b�E�B���h�E
#define BMPL_TALK_PX	(FLD_MSG_WIN_PX)
#define BMPL_TALK_PY	(FLD_MSG_WIN_PY)
#define BMPL_TALK_SX	(FLD_MSG_WIN_SX)
#define BMPL_TALK_SY	(FLD_MSG_WIN_SY)
#define BMPL_TALK_PAL	(FLD_MSG_WIN_PAL)
#define BMPL_TALK_CGX	(BMPL_MENU_WIN_CGX-BMPL_TALK_SX*BMPL_TALK_SY)

//YN�E�B���h�E
#define BMPL_YESNO_PX	(FLD_YESNO_WIN_PX)
#define BMPL_YESNO_PY	(FLD_YESNO_WIN_PY)
#define BMPL_YESNO_SX	(FLD_YESNO_WIN_SX)
#define BMPL_YESNO_SY	(FLD_YESNO_WIN_SY)
#define BMPL_YESNO_PAL	(FLD_YESNO_WIN_PAL)
#define BMPL_YESNO_CGX	(BMPL_TALK_CGX-BMPL_YESNO_SX*BMPL_YESNO_SY)

//���O�̃E�B���h�E
#define MAILBOX_CGX_START	(BMPL_YESNO_CGX)
#define MAILBOX_FRAME	(FLD_MBGFRM_FONT)
#define MAILBOX_FPAL	(FLD_SYSFONT_PAL)

//���[�����X�g�E�B���h�E
#define MLIST_WIN_SX	(12)
#define MLIST_WIN_SY	(16)
#define MLIST_WIN_PX	(31-MLIST_WIN_SX)
#define MLIST_WIN_PY	(1)
#define MLIST_WIN_CGXNUM	(MLIST_WIN_SX*MLIST_WIN_SY)
#define MLIST_WIN_CGX	(MAILBOX_CGX_START-MLIST_WIN_CGXNUM)

//�A�N�V�����I���E�B���h�E
#define MENU_WIN_SX	(14)
#define MENU_WIN_SY	(8)
#define MENU_WIN_PX	(1)
#define MENU_WIN_PY	(1)
#define MENU_WIN_CGXNUM	(MENU_WIN_SX*((MENU_WIN_SY+1)*2))
#define MENU_WIN_CGX	(MAILBOX_CGX_START-MLIST_WIN_CGXNUM)

//�^�C�g���E�B���h�E
#define TITLE_WIN_PX	(1)
#define TITLE_WIN_PY	(1)
#define TITLE_WIN_SX	(9)
#define TITLE_WIN_SY	(2)
#define TITLE_WIN_CGXNUM	(TITLE_WIN_SX*TITLE_WIN_SY)
#define TITLE_WIN_CGX	(MLIST_WIN_CGX-TITLE_WIN_CGXNUM)

//------------------------------------------------------------------
///	���ڃ��X�g�f�[�^
//------------------------------------------------------------------
static const BMPLIST_HEADER MailListHeader = {
	NULL,			//�\�������f�[�^�|�C���^
	NULL,				//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,		//�P�s���Ƃ̃R�[���o�b�N�֐�
	NULL,				//GF_BGL_BMPWIN�\���̃f�[�^�ւ̃|�C���^
	0,			//���X�g���ڐ�
	7,					//�\���ő區�ڐ�
	2,					//���x���\���w���W
	10,					//���ڕ\���w���W
	1,					//�J�[�\���\���w���W
	0,					//�\���x���W
	FBMP_COL_BLACK,		//�����F
	FBMP_COL_WHITE,		//�w�i�F
	FBMP_COL_BLK_SDW,	//�����e�F
	0,					//�����Ԋu�w
	1,					//�����Ԋu�x
	BMPLIST_LRKEY_SKIP,	//�y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,		//�����w��
	0,					//�a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
	NULL,				//���[�N�|�C���^
};

#define MAILMENU_EXIT	(0xFFFF)
#define MAILMENU_BUFLEN	(10)
#define MAILMSG_BUFLEN	(20*2)

typedef enum{
 BOX_MENU_VIEW,
 BOX_MENU_DEL,
 BOX_MENU_TRANS,
 BOX_MENU_EXIT,
}BOX_MENU;

static const MENU_PARAM normalMenu[] = {
 {msg_view,BOX_MENU_VIEW},
 {msg_del,BOX_MENU_DEL},
 {msg_trans,BOX_MENU_TRANS},
 {msg_exit,BOX_MENU_EXIT},
};

//===============================================
///�v���g�^�C�v
//===============================================
void EventCmd_MailBoxCall( GMEVENT_CONTROL *event);
void MailBox_Call(void* fsys,int* end_flag);
static void MailBox_Exit(MAIL_BOX_MAIN* wk);

///
static void MailBox_ExitCall(TCB_PTR tcb,void* work);
static void MailBox_MailListInit(TCB_PTR tcb,void* work);
static void MailBox_MailListKeyIn(TCB_PTR tcb,void* work);
static void MailBox_SelectListInit(TCB_PTR tcb,void* work);
static void MailBox_SelectListKeyIn(TCB_PTR tcb,void* work);
static void MailBox_MailListExit(TCB_PTR tcb,void* work);
static void MailBox_SelectListExit(TCB_PTR tcb,void* work);
static void MailBox_MailCall(TCB_PTR tcb,void* work);
static void MailBox_MailDelSelect(TCB_PTR tcb,void* work);
static void MailBox_MailDelExe(TCB_PTR tcb,void* work);
static void MailBox_PokeListCall(TCB_PTR tcb,void* work);
static void MailBox_MailPokeCancel(TCB_PTR tcb,void* work);
static void MailBox_DelMail2PokeCall(TCB_PTR tcb,void* work);

//*********************************************************************
//���[�J���T�u
static void mbox_NextTcb(MAIL_BOX_MAIN* wk,TCB_FUNC first,TCB_FUNC second);
static void mbox_MAIL_LIST_Clear(MAIL_LIST* dat,u8 id);
static void mbox_MAIL_LIST_ArrayInit(MAIL_LIST* dat,u8 num,int heapID);
static void mbox_MAIL_LIST_ArrayEnd(MAIL_LIST* dat,u8 num);
static void mbox_MailListInit(MAIL_BOX_MAIN* wk);
static void mbox_CB_MailListLine(BMPLIST_WORK* lw,u32 param,u8 y);
static void mbox_CB_MailListMove(BMPLIST_WORK * work, u32 param, u8 mode);
static void mbox_SelectListInit(MAIL_BOX_MAIN* wk,u8 list,u8 cur);
static void mbox_CB_SelectListMove(BMPLIST_WORK * work, u32 param, u8 mode);
static void mbox_MailListEnd(MAIL_BOX_MAIN* wk);
static void mbox_SelectListEnd(MAIL_BOX_MAIN* wk);

static void mbox_GetSaveData(MAIL_BOX_MAIN* wk,SAVEDATA* savedata,int heapID);
static void mbox_MailChainOut(MAIL_BOX_MAIN* wk,u8 id);
static BOOL mbox_MailReturnBag(MAIL_BOX_MAIN* wk);
static void mbox_Mail2Poke(MAIL_BOX_MAIN* wk,u8 pokeno,BOOL addItem);

static void mbox_MsgResInit(MAIL_BOX_MAIN* wk);
static void mbox_MsgResRelease(MAIL_BOX_MAIN* wk);
static void mbox_ComResInit(MAIL_BOX_MAIN* wk);
static void mbox_ComResRelease(MAIL_BOX_MAIN* wk);

static void mbox_PrintTalkMsg(MAIL_BOX_MAIN* wk,MBOX_MSGIDX idx,u8 spd,u8 del_f,int win_f);
static void mbox_TalkMsgClear(MAIL_BOX_MAIN* wk);
static BOOL mbox_TalkMsgWait(MAIL_BOX_MAIN* wk);
static void mbox_YesNoInit(MAIL_BOX_MAIN* wk);
static int mbox_YesNoWait(MAIL_BOX_MAIN* wk);

static int mbox_FadeCall(MAIL_BOX_MAIN* wk,int type);
static int mbox_FieldSetCall(MAIL_BOX_MAIN* wk);
static int mbox_ListFree(MAIL_BOX_MAIN* wk,u8 mode);

static int mbox_PokeListCall(MAIL_BOX_MAIN* wk,int mode);
static int mbox_MailCall(MAIL_BOX_MAIN* wk);

//===============================================
///�O���[�o��
//===============================================
/**
 *	@brief	���[���{�b�N�X�Ăяo����������
 */
void MailBox_Call(void* fsys,int* end_flag)
{
	MAIL_BOX_MAIN* wk = NULL;
	SAVEDATA* sv;

	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_MAILBOX,0x5000);
	
	//���[�N�G���A�擾
	HeapStatePush();

	wk = sys_AllocMemory(HEAPID_MAILBOX,sizeof(MAIL_BOX_MAIN));
	MI_CpuClear8(wk,sizeof(MAIL_BOX_MAIN));

	wk->end_flag = end_flag;

#ifdef PM_DEBUG
	//�f�o�b�O�t���O����ɗ��p
	wk->deb_flag = *end_flag;
	*end_flag = 0;
#endif	//PM_DEBUG

	sv = GameSystem_GetSaveData(fsys);
	wk->fsys = (FIELDSYS_WORK*)fsys;
	wk->heapID = HEAPID_MAILBOX;
	wk->listEnd = 0;
	wk->listStart = 0xFF;
	wk->msg_spd = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(sv));
	wk->win_type = CONFIG_GetWindowType(SaveData_GetConfig(sv));

	//MAIL_LIST�\���̔z��̏�����
	mbox_MAIL_LIST_ArrayInit(wk->mailList,MAIL_STOCK_PASOCOM,wk->heapID);
	//�Z�[�u�f�[�^�擾
	mbox_GetSaveData(wk,sv,wk->heapID);

	//���b�Z�[�W���\�[�X�쐬
	mbox_MsgResInit(wk);
	
	//�������X�g�쐬
	wk->tcb = TCB_Add(MailBox_MailListInit,wk,0);

#ifdef PM_DEBUG
	if(wk->deb_flag){
		FieldSystemProc_SeqHold();
	}
#endif	//PM_DEBUG
}
/**
 *	@brief	���[���{�b�N�X�I������
 */
void MailBox_Exit(MAIL_BOX_MAIN* wk)
{
	TCB_Delete(wk->tcb);
	*(wk->end_flag) = 1;	//�I���t���OON

	//���b�Z�[�W���\�[�X�j��
	mbox_MsgResRelease(wk);

#ifdef PM_DEBUG
	if(wk->deb_flag){
		FieldSystemProc_SeqHoldEnd();
	}
#endif	//PM_DEBUG
	
	//MAIL_LIST�\���̔z�񃊃\�[�X�̉��
	mbox_MAIL_LIST_ArrayEnd(wk->mailList,MAIL_STOCK_PASOCOM);
	sys_FreeMemoryEz(wk);

	HeapStatePop();
	HeapStateCheck(wk->heapID);	
	sys_DeleteHeap(wk->heapID);
}

//==================================================
//���C�����X�g�֘A�^�X�N
//==================================================
/**
 *	@brief	���[���{�b�N�X�I���R�[��
 */
static void MailBox_ExitCall(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	MailBox_Exit(wk);
}

/**
 *	@brief	���[���{�b�N�X���C�����X�g������
 */
static void MailBox_MailListInit(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	//�R�������\�[�X������
	mbox_ComResInit(wk);
	mbox_MailListInit(wk);
	TCB_ChangeFunc(tcb,MailBox_MailListKeyIn);
}

/**
 *	@brief	���[���{�b�N�X���C�����X�g�R���g���[��
 */
static void MailBox_MailListKeyIn(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;
	s32	ret_code;

	ret_code = BmpListMain(wk->blistWk);

	if(wk->fca != NULL){
		//�A�N�^�[�A�j��
		FActCom_Main(wk->fca);
	}
	if(sys.trg & PAD_BUTTON_CANCEL){
		mbox_NextTcb(wk,MailBox_MailListExit,MailBox_ExitCall);
		Snd_SePlay(SEQ_SE_DP_SELECT);
		return;
	}
	if(sys.trg & PAD_BUTTON_DECIDE){
		Snd_SePlay(SEQ_SE_DP_SELECT);
		switch(ret_code){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
		case MAILMENU_EXIT:
			mbox_NextTcb(wk,MailBox_MailListExit,MailBox_ExitCall);
			break;
		default:
			wk->selectID = ret_code;
			mbox_NextTcb(wk,MailBox_MailListExit,MailBox_SelectListInit);
			break;
		}
	}
	return;	
}


/**
 *	@brief	���[���{�b�N�X�Z���N�g���X�g������
 */
static void MailBox_SelectListInit(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:	
		//�R�������\�[�X������
		mbox_ComResInit(wk);
		mbox_SelectListInit(wk,0,0);

		//���[�����ǂ����܂������b�Z�[�W�`��
		mbox_PrintTalkMsg(wk,MIDX_SELECT,wk->msg_spd,FALSE,TRUE);
		++wk->seq;
		break;
	case 1:
		if(!mbox_TalkMsgWait(wk)){
			break;
		}
		TCB_ChangeFunc(tcb,MailBox_SelectListKeyIn);
		wk->seq = 0;
		break;
	}
	return;
}

/**
 *	@brief	���[���{�b�N�X�Z���N�g���X�g�L�[�擾
 */
static void MailBox_SelectListKeyIn(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;
	s32	ret_code;

	ret_code = BmpListMain(wk->blistWk);

	if(sys.trg & PAD_BUTTON_CANCEL){
		mbox_NextTcb(wk,MailBox_SelectListExit,MailBox_MailListInit);
		Snd_SePlay(SEQ_SE_DP_SELECT);
		return;
	}
#ifdef PM_DEBUG
	if(wk->deb_flag){
		if(sys.trg & PAD_KEY_RIGHT){
			wk->deb_design = (wk->deb_design+1)%4;
		}else if(sys.trg & PAD_KEY_LEFT){
			wk->deb_design = (wk->deb_design+3)%4;
		}	
	}
#endif
	if(sys.trg & PAD_BUTTON_DECIDE){
		Snd_SePlay(SEQ_SE_DP_SELECT);
		switch(ret_code){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
		case BOX_MENU_EXIT:
			mbox_NextTcb(wk,MailBox_SelectListExit,MailBox_MailListInit);
			break;
		case BOX_MENU_DEL:	//���[��������
			mbox_NextTcb(wk,MailBox_MailDelSelect,NULL);
			break;
		case BOX_MENU_TRANS:	//�|�P�����Ɏ�������
			mbox_NextTcb(wk,MailBox_PokeListCall,MailBox_MailPokeCancel);
			break;
		case BOX_MENU_VIEW:
		default:
			TCB_ChangeFunc(tcb,MailBox_MailCall);
			break;
		}
	}
	return;	
	
}

/**
 *	@brief	���[���{�b�N�X�@���[�����X�g���
 */
static void MailBox_MailListExit(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;
	
	mbox_MailListEnd(wk);
	mbox_ComResRelease(wk);
	TCB_ChangeFunc(tcb,wk->next_tcb);
}

/**
 *	@brief	���[���{�b�N�X �Z���N�g���X�g���
 */
static void MailBox_SelectListExit(TCB_PTR tcb,void* work)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;
	
	mbox_SelectListEnd(wk);
	mbox_ComResRelease(wk);
	TCB_ChangeFunc(tcb,wk->next_tcb);
}

/**
 *	@brief	���[���R�}���h�Ăяo���^�X�N
 */
static void MailBox_MailCall(TCB_PTR tcb,void* work)
{
	int ret;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
		if(!mbox_FadeCall(wk,FADEOUT)){
			return;
		}
		mbox_ListFree(wk,LIST_SELECT);
		break;
	case 1:
		if(!mbox_MailCall(wk)){
			return;
		}
		break;
	case 2:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(!mbox_FieldSetCall(wk)){
			return;
		}
		break;
	case 3:
		if(!mbox_FadeCall(wk,FADEIN)){
			return;
		}
		//���X�g�Đ�
		mbox_ComResInit(wk);
		mbox_MailListInit(wk);
		wk->seq = 0;
		TCB_ChangeFunc(tcb,MailBox_MailListKeyIn);
		return;
	}
	wk->seq++;
	return;
}

/**
 *	@brief	���[���������I���T�u�^�X�N
 */
static void MailBox_MailDelSelect(TCB_PTR tcb,void* work)
{
	int ret;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
		//���[���������܂������b�Z�[�W��`��
		mbox_PrintTalkMsg(wk,MIDX_DSEL,wk->msg_spd,FALSE,TRUE);
		break;
	case 1:
		if(!mbox_TalkMsgWait(wk)){
			return;
		}
		//YN�E�B���h�E�\��
		mbox_YesNoInit(wk);
		break;
	case 2:
		//YN�I��҂�
		ret = mbox_YesNoWait(wk);
		if(ret < 0){
			return;	//�I��
		}
		if(ret){	//����
			//�|�P�����Ɏ������܂����H
			mbox_PrintTalkMsg(wk,MIDX_POKE,wk->msg_spd,FALSE,FALSE);
			wk->seq = 4;
		}else{	//�����Ȃ�
			wk->seq = 3;
		}
		return;
	case 3:	//���[�����X�g�ɖ߂�
		mbox_TalkMsgClear(wk);
		mbox_NextTcb(wk,MailBox_SelectListExit,MailBox_MailListInit);	
		wk->seq = 0;
		return;
	case 4:	//�|�P�����Ɏ������邩�ǂ����I������
		if(!mbox_TalkMsgWait(wk)){
			return;
		}
		//YN�E�B���h�E�\��
		mbox_YesNoInit(wk);
		break;
	case 5:
		//YN�I��҂�
		ret = mbox_YesNoWait(wk);
		if(ret < 0){
			return;	//�I��
		}
		if(ret){	//��������
			//�|�P�������X�g�^�X�N��
			mbox_NextTcb(wk,MailBox_DelMail2PokeCall,NULL);
		}else{
			//�o�b�O�Ƀ��[����߂��^�X�N��
			mbox_NextTcb(wk,MailBox_MailDelExe,MailBox_SelectListExit);
		}
		mbox_TalkMsgClear(wk);
		wk->seq = 0;
		return;
	}
	wk->seq++;
	return;
}

/**
 *	@brief	���[�������������^�X�N
 */
static void MailBox_MailDelExe(TCB_PTR tcb,void* work)
{
	int ret;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
	#if 1
		if(wk->next_tcb == NULL){
			//�I�����X�g���X�g�Đ�
			mbox_ComResInit(wk);
			mbox_SelectListInit(wk,0,1);
		}
#endif
		//���[�����o�b�O�ɖ߂��������s
		if(mbox_MailReturnBag(wk)){
			mbox_PrintTalkMsg(wk,MIDX_TOBAG,wk->msg_spd,FALSE,TRUE);
		}else{
			mbox_PrintTalkMsg(wk,MIDX_BAGFULL,wk->msg_spd,FALSE,TRUE);
		}
		break;
	case 1:
		if(!mbox_TalkMsgWait(wk)){
			return;
		}
		break;
	case 2:
		if(!(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))){
			return;
		}
		mbox_TalkMsgClear(wk);
		//���[�����X�g�ɖ߂�
		mbox_NextTcb(wk,MailBox_SelectListExit,MailBox_MailListInit);
		wk->seq = 0;
		return;
	}
	wk->seq++;
	return;
}

/**
 *	@brief	�|�P�������X�g�@�Ăяo���^�X�N
 */
static void MailBox_PokeListCall(TCB_PTR tcb,void* work)
{
	u8	pos;
	PLIST_DATA* pld;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
		if(!mbox_FadeCall(wk,FADEOUT)){
			return;
		}
		mbox_ListFree(wk,LIST_SELECT);
		break;	
	case 1:	//���X�g�Ăяo��
		if(!mbox_PokeListCall(wk,PL_MODE_MAILBOX)){
			return;
		}
		break;
	case 2:	//���X�g�I���҂�
		//�t�B�[���h�}�b�v�v���Z�X���A
		if(!mbox_FieldSetCall(wk)){
			return;
		}
		break;
	case 3:
		if(!mbox_FadeCall(wk,FADEIN)){
			return;
		}
		pos = wk->plist->ret_sel;
		sys_FreeMemoryEz(wk->plist);
		
		if(pos == PL_SEL_POS_EXIT){
			mbox_NextTcb(wk,wk->next_tcb,NULL);	
			wk->seq = 0;
			return;	
		}
		//�|�P�����Ɏ������鏈��
		mbox_Mail2Poke(wk,pos,FALSE);	
		mbox_NextTcb(wk,MailBox_MailListInit,NULL);	
		wk->seq = 0;
		return;
	}
	wk->seq++;
	return;
}

/**
 *	@brief	���[�����|�P�����Ɏ�������̂��L�����Z���������̃��b�Z�[�W����
 */
static void MailBox_MailPokeCancel(TCB_PTR tcb,void* work)
{
	int ret;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
		//�I�����X�g���X�g�Đ�
		mbox_ComResInit(wk);
		mbox_SelectListInit(wk,0,2);

		mbox_PrintTalkMsg(wk,MIDX_POKECANCEL,wk->msg_spd,FALSE,TRUE);
		break;
	case 1:
		if(!mbox_TalkMsgWait(wk)){
			return;
		}
		break;
	case 2:
		if(!(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))){
			return;
		}
		mbox_TalkMsgClear(wk);
		//���[�����X�g�ɖ߂�
		mbox_NextTcb(wk,MailBox_SelectListExit,MailBox_MailListInit);
		wk->seq = 0;
		return;
	}
	wk->seq++;
	return;
}

/**
 *	@brief	���������[�����|�P�����Ɏ�������@�Ăяo���^�X�N
 */
static void MailBox_DelMail2PokeCall(TCB_PTR tcb,void* work)
{
	int ret;
	u8	pos,ret_mode;
	PLIST_DATA* pld;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)work;

	switch(wk->seq){
	case 0:
		if(!mbox_FadeCall(wk,FADEOUT)){
			return;
		}
		mbox_ListFree(wk,LIST_SELECT);
		/*
		 * ���̎��_�ł̃A�C�e������0�łȂ���΁A���[�����|�P�����Ɏ��������Ƃ���
		 * �A�C�e�������P�����Ă���̂ŁA�ЂƂ��₷
		 */
		if(MyItem_GetItemNum(wk->itemSave,wk->mailList[wk->selectID].itemno,wk->heapID) > 0){
			wk->additem_f = 1;
		}else{
			wk->additem_f = 0;
		}
		break;
	case 1:
		//���[������������|�P������I��������
		if(!mbox_PokeListCall(wk,PL_MODE_ITEMSET)){
			return;
		}
		pos = wk->plist->ret_sel;
		ret_mode = wk->plist->ret_mode;
		sys_FreeMemoryEz(wk->plist);

		if(ret_mode != PL_RET_MAILSET || pos == PL_SEL_POS_EXIT){
			//���[������������̂��~�߂�
			wk->next_tcb = MailBox_MailDelExe;
			wk->seq = 4;
			return;
		}
		wk->selPos = pos;
		//���X�g�̃`�F�C������O���Ă���
//		mbox_MailChainOut(wk,wk->selectID);

		//�L���t���O��off���Ă���
		wk->mailList[wk->selectID].valid = 0;
		break;
	case 2:
		//���[���쐬
		ret = mbox_MailCall(wk);
		if(!ret){
			return;
		}
		if(ret == 1){
			//���[������������̂��~�߂�
			wk->next_tcb = MailBox_MailDelExe;
			wk->seq = 4;
			return;
		}
		wk->next_tcb = MailBox_MailListInit;
		break;
	case 3:
		//���[�����������܂�����ʂ�\��
		if(!mbox_PokeListCall(wk,PL_MODE_MAILSET)){
			return;
		}
		sys_FreeMemoryEz(wk->plist);
		//�|�P�����Ɏ������鏈��
		mbox_Mail2Poke(wk,wk->selPos,wk->additem_f);
		wk->additem_f = 0;	//�t���O�N���A
		break;
	case 4:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(!mbox_FieldSetCall(wk)){
			return;
		}
		break;
	case 5:
		if(!mbox_FadeCall(wk,FADEIN)){
			return;
		}
		//�o�b�O�Ƀ��[����߂��^�X�N��
		mbox_NextTcb(wk,wk->next_tcb,NULL);
		wk->seq = 0;
		return;
	}
	++wk->seq;
}
//=======================================================================
///�T�u
/**
 *	@brief	���[���{�b�N�X���C�����X�g�������^�X�N
 */
static void mbox_MailListInit(MAIL_BOX_MAIN* wk)
{
	u8	i = 0,size = 0;
	MAIL_LIST	*pl;

	static const BMPWIN_DAT bmp[2] = {
		{
			MAILBOX_FRAME,MLIST_WIN_PX, MLIST_WIN_PY,
			MLIST_WIN_SX, MLIST_WIN_SY, MAILBOX_FPAL, MLIST_WIN_CGX
		},{
			MAILBOX_FRAME,TITLE_WIN_PX, TITLE_WIN_PY,
			TITLE_WIN_SX, TITLE_WIN_SY, MAILBOX_FPAL, TITLE_WIN_CGX
		},
	};

	//�J�[�\���A�N�^�[������
	wk->fca = FComAct_Init(wk->heapID);
	FComAct_CursorPosSet(wk->fca,200,10,138);
	FComAct_SetDrawFlg(wk->fca,FCA_UCURSOR,TRUE);
	FComAct_SetDrawFlg(wk->fca,FCA_DCURSOR,TRUE);

	//�E�B���h�E�쐬
	GF_BGL_BmpWinAddEx(wk->bgl,&(wk->bmpwin),&bmp[0]);
	GF_BGL_BmpWinAddEx(wk->bgl,&(wk->titlewin),&bmp[1]);
	GF_BGL_BmpWinDataFill(&wk->bmpwin,WINCLR_COL(FBMP_COL_WHITE));
	GF_BGL_BmpWinDataFill(&wk->titlewin,WINCLR_COL(FBMP_COL_WHITE));

	
	//BMP���j���[���X�g�쐬(�T�C�Y+[��߂�]�����m��)
	wk->menulist = BMP_MENULIST_Create(wk->listSize+1,wk->heapID);
	
	for(i = 0;i < MAIL_STOCK_PASOCOM;i++){
		
		pl = &(wk->mailList[i]);
		//���C�^�[���擾
		if(!pl->valid){
#ifdef PM_DEBUG			
			if(wk->deb_flag != 2){
				continue;
			}
#else
			continue;
#endif	//PM_DEBUG
		}
		BMP_MENULIST_AddString(wk->menulist,pl->name,pl->id);
		size++;
	}
	//�u��߂�v��ǉ�
	BMP_MENULIST_AddString(wk->menulist,wk->msgDat.ebuf,MAILMENU_EXIT);
	size++;
	
	//BMP���X�g�ݒ�
	MI_CpuCopy8((void*)&MailListHeader,(void*)&(wk->bmplist_h),sizeof(BMPLIST_HEADER));
	wk->bmplist_h.win = &(wk->bmpwin);
	wk->bmplist_h.list = wk->menulist;
	wk->bmplist_h.work = (void*)wk;
	wk->bmplist_h.count = size;
	wk->bmplist_h.line_y = 6;
	wk->bmplist_h.call_back = mbox_CB_MailListMove;
	wk->bmplist_h.icon = mbox_CB_MailListLine;

	//���X�g�폜�t���Oon�Ȃ�J�[�\���ʒu����
	if(wk->listdel_f){
		if(wk->List == 0){
			if(wk->Cursor != 0 && wk->Cursor >= (size-1)){
				--wk->Cursor;
			}
		}else{
			if(wk->List+7 >= size){
				--wk->List;
			}
		}
		wk->listdel_f = 0;
	}
	wk->blistWk = BmpListSet(&(wk->bmplist_h),wk->List,wk->Cursor,wk->heapID);
	BmpMenuWinWrite( &wk->bmpwin, WINDOW_TRANS_ON, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );
	
	//�^�C�g���`��
	GF_STR_PrintColor(&wk->titlewin, FONT_SYSTEM,wk->msgDat.tbuf,
		2, 0, MSG_ALLPUT, TALK_FCOL, NULL );
	//	GF_BGL_BmpWinOn(&wk->titlewin);
	BmpMenuWinWrite( &wk->titlewin, WINDOW_TRANS_ON, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );

	
	GF_BGL_LoadScreenV_Req(wk->bgl,MAILBOX_FRAME);

	//���X�g���[�h�ۑ�
	wk->listMode = 0;
}

/**
 *	@brief	���[���{�b�N�X�@���[�����X�g���C���R�[���o�b�N
 */
static void mbox_CB_MailListLine(BMPLIST_WORK* work,u32 param,u8 y)
{
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)BmpListParamGet(work,BMPLIST_ID_WORK);

	if(param == MAILMENU_EXIT){
		BmpListTmpColorChange(work,FBMP_COL_BLACK,FBMP_COL_WHITE,FBMP_COL_BLK_SDW);
	}else{
		if(wk->mailList[param].sex){
			BmpListTmpColorChange(work,FBMP_COL_RED,FBMP_COL_WHITE,FBMP_COL_RED_SDW);
		}else{
//			BmpListTmpColorChange(work,FBMP_COL_GREEN,FBMP_COL_WHITE,FBMP_COL_GRN_SDW);
			BmpListTmpColorChange(work,FBMP_COL_BLUE,FBMP_COL_WHITE,FBMP_COL_BLU_SDW);
		}
	}
}

/**
 *	@brief	���[���{�b�N�X�@���[�����X�g�J�[�\���ړ��R�[���o�b�N
 */
static void mbox_CB_MailListMove(BMPLIST_WORK * work, u32 param, u8 mode)
{
	u16	scr,cur,ct;
	MAIL_BOX_MAIN* wk = (MAIL_BOX_MAIN*)BmpListParamGet(work,BMPLIST_ID_WORK);
	
	//�J�[�\���ړ�
	BmpListPosGet( work, &scr, &cur );
	ct = BmpListParamGet(work,BMPLIST_ID_COUNT);

	if(!mode){
		Snd_SePlay(SEQ_SE_DP_SELECT);
	}
	//���}�[�N�`��R���g���[��
	if(scr == 0){
		FComAct_SetDrawFlg(wk->fca,FCA_UCURSOR,FALSE);
	}else{
		FComAct_SetDrawFlg(wk->fca,FCA_UCURSOR,TRUE);
	}
	if(scr < (ct-7)){
		FComAct_SetDrawFlg(wk->fca,FCA_DCURSOR,TRUE);
	}else{
		FComAct_SetDrawFlg(wk->fca,FCA_DCURSOR,FALSE);
	}
}

/**
 *	@brief	���[���{�b�N�X�Z���N�g���X�g������
 */
static void mbox_SelectListInit(MAIL_BOX_MAIN* wk,u8 list,u8 cur)
{
	u8	i = 0,size = 0;

	static const BMPWIN_DAT bmp = { MAILBOX_FRAME,
		MENU_WIN_PX, MENU_WIN_PY,
		MENU_WIN_SX, MENU_WIN_SY, MAILBOX_FPAL, MENU_WIN_CGX
	};

	//BMP���j���[���X�g�쐬
	size = NELEMS(normalMenu);
	wk->menulist = BMP_MENULIST_Create(size,wk->heapID);
	GF_BGL_BmpWinAddEx(wk->bgl,&(wk->bmpwin),&bmp);
	GF_BGL_BmpWinDataFill(&wk->bmpwin,WINCLR_COL(FBMP_COL_WHITE));
	
	for(i = 0;i < size;i++){
		BMP_MENULIST_AddArchiveString(wk->menulist,
			wk->pMsg, normalMenu[i].str_id, normalMenu[i].param );
	}
	
	//BMP���X�g�ݒ�
	MI_CpuCopy8((void*)&MailListHeader,(void*)&(wk->bmplist_h),sizeof(BMPLIST_HEADER));
	wk->bmplist_h.win = &(wk->bmpwin);
	wk->bmplist_h.list = wk->menulist;
	wk->bmplist_h.work = (void*)wk;
	wk->bmplist_h.count = size;
	wk->bmplist_h.line = 4;
	wk->bmplist_h.page_skip = BMPLIST_NO_SKIP;
	wk->bmplist_h.call_back = mbox_CB_SelectListMove;
	wk->blistWk = BmpListSet(&(wk->bmplist_h),list,cur,wk->heapID);
	
	BmpMenuWinWrite( &wk->bmpwin, WINDOW_TRANS_ON, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL );	
	GF_BGL_LoadScreenV_Req(wk->bgl,MAILBOX_FRAME);	

	//���X�g���[�h�ۑ�
	wk->listMode = 1;
}

/**
 *	@brief	���[���{�b�N�X�@�Z���N�g���X�g�J�[�\���ړ��R�[���o�b�N
 */
static void mbox_CB_SelectListMove(BMPLIST_WORK * work, u32 param, u8 mode)
{
	if(!mode){
		Snd_SePlay(SEQ_SE_DP_SELECT);
	}
}

/**
 *	@brief	���[���{�b�N�X ���[�����X�g�̈���
 */
static void mbox_MailListEnd(MAIL_BOX_MAIN* wk)
{
	u16	list,cur;
	
	//BMP���X�g�̊J��
	BmpListExit(wk->blistWk,&list,&cur);	//���X�g�j��
	BMP_MENULIST_Delete(wk->menulist);	//���j���[������j��
	
	//BMPWIN�j��
	GF_BGL_BmpWinOff(&(wk->titlewin));	//WindowOFF
	BmpMenuWinClear( &(wk->titlewin),WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&(wk->titlewin));	//BMP Window Del
	
	GF_BGL_BmpWinOff(&(wk->bmpwin));	//WindowOFF	
	BmpMenuWinClear( &(wk->bmpwin),WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&(wk->bmpwin));	//BMP Window Del

	//�J�[�\���ʒu�ۑ�
	wk->List = list;
	wk->Cursor = cur;

	//�A�N�^�[�J�[�\���j��
	if(wk->fca != NULL){
		FComAct_Delete(wk->fca);
		wk->fca = NULL;
	}

	GF_BGL_LoadScreenV_Req(wk->bgl,MAILBOX_FRAME);	
}

/**
 *	@brief	���[���{�b�N�X �Z���N�g���X�g�̈���
 */
static void mbox_SelectListEnd(MAIL_BOX_MAIN* wk)
{
	u16	list,cur;
	
	//BMPWIN�j��
	GF_BGL_BmpWinOff(&(wk->bmpwin));	//WindowOFF
	
	//BMP���X�g�̊J��
	BmpMenuWinClear( &(wk->bmpwin),WINDOW_TRANS_ON);
	BmpListExit(wk->blistWk,&list,&cur);	//���X�g�j��
	BMP_MENULIST_Delete(wk->menulist);	//���j���[������j��
	GF_BGL_BmpWinDel(&(wk->bmpwin));	//BMP Window Del
	
	mbox_TalkMsgClear(wk);

	GF_BGL_LoadScreenV_Req(wk->bgl,MAILBOX_FRAME);
}

/**
 *	@brief	
 */
//===================================================
//���[�J��
//===================================================
/**
 *	@brief	TCB�t�@���N�V�����`�F���W
 */
static void mbox_NextTcb(MAIL_BOX_MAIN* wk,TCB_FUNC first,TCB_FUNC second)
{
	TCB_ChangeFunc(wk->tcb,first);
	wk->seq = 0;
	wk->next_tcb = second;
}

/**
 *	@brief	MAP_LIST�\���̂����Ԃɏ�����
 */
static void mbox_MAIL_LIST_Clear(MAIL_LIST* dat,u8 id)
{
	dat->id = id;
	dat->valid = 0;
	dat->prev = 0;
	dat->next = 0;
	if(dat->name != NULL){
		STRBUF_Clear(dat->name);
	}
}

/**
 *	@brief	MAP_LIST�\���̔z���������
 */
static void mbox_MAIL_LIST_ArrayInit(MAIL_LIST* dat,u8 num,int heapID)
{
	u8 i = 0;

	for(i = 0;i < num;i++){
		dat[i].name = STRBUF_Create(BUFLEN_PERSON_NAME,heapID);
		mbox_MAIL_LIST_Clear(dat,i);
	}
}

/**
 *	@brief	MAP_LIST�\���̔z����̃��\�[�X�����
 */
static void mbox_MAIL_LIST_ArrayEnd(MAIL_LIST* dat,u8 num)
{
	u8 i = 0;

	for(i = 0;i < num;i++){
		if(dat[i].name != NULL){
			STRBUF_Delete(dat[i].name);
		}
	}
}

/**
 *	brief	�Z�[�u�f�[�^���擾
 */
static void mbox_GetSaveData(MAIL_BOX_MAIN* wk,SAVEDATA* savedata,int heapID)
{
	u8 i = 0,prev = 0,start = 0xFF,end = 0;
	int id;
	MAIL_BLOCK* pBlock;
	MAIL_DATA* mail;
	
	MAIL_LIST	*pNow,*pLast;
	
	//���[���u���b�N�Z�[�u�f�[�^�|�C���^�擾
	pBlock = SaveData_GetMailBlock(savedata);
	wk->pBlock = pBlock;

	//�A�C�e���f�[�^�Z�[�u�|�C���^�擾
	wk->itemSave = SaveData_GetMyItem(savedata);

	//�f�[�^�擾�e���|�����쐬
	mail = MailData_CreateWork(heapID);
	
	for(i = 0;i < MAIL_STOCK_PASOCOM;i++){
		MAIL_GetMailData(pBlock,MAILBLOCK_PASOCOM,i,mail);

		pNow = &(wk->mailList[i]);
		pLast = &(wk->mailList[wk->listEnd]);
	
		mbox_MAIL_LIST_Clear(pNow,i);
		
		pNow->id = i;
		if(!MailData_IsEnable(mail)){
#ifdef PM_DEBUG			
			if(wk->deb_flag==2){
				wk->listSize++;
			}
#endif
			continue;
		}
		pNow->valid = 1;	//�L���t���OOn
		pNow->sex = MailData_GetWriterSex(mail);//���C�^�[���ʎ擾
		pNow->design = MailData_GetDesignNo(mail);
		pNow->itemno = MailItemNumGet(pNow->design);//�A�C�e��NO�擾
		STRBUF_SetStringCode(pNow->name,MailData_GetWriterName(mail));

		//�z���X�g�쐬
		pNow->prev = wk->listEnd;
		pLast->next = pNow->id;

		wk->listEnd = pNow->id;	//�Ō���X�V
		wk->listSize++;
		if(wk->listStart == 0xFF){
			wk->listStart = i;	//�X�^�[�gNO���擾
		}
	}

	//�z���X�g�����
	wk->mailList[wk->listEnd].next = wk->listStart;
	wk->mailList[wk->listStart].prev = wk->listEnd;
	
	//���[�����[�N�j��
	sys_FreeMemoryEz(mail);
}

/**
 *	@brief	�J�����g���[�������X�g�`�F�C������O������
 */
static void mbox_MailChainOut(MAIL_BOX_MAIN* wk,u8 id)
{
	MAIL_LIST* pNow;
	pNow = &(wk->mailList[id]);
	
	//���[���f�[�^�����X�g����폜
	wk->mailList[pNow->prev].next = pNow->next;
	wk->mailList[pNow->next].prev = pNow->prev;
	wk->mailList[id].valid = 0;
	//���X�g���ЂƂ������t���O�𗧂ĂĂ���
	wk->listdel_f = 1;
}

/**
 *	@brief	���[�����o�b�O�ɖ߂�����
 */
static BOOL mbox_MailReturnBag(MAIL_BOX_MAIN* wk)
{
	MAIL_LIST* pNow;
	BOOL ret;
	
	pNow = &(wk->mailList[wk->selectID]);
	
	ret = MyItem_AddCheck(wk->itemSave,pNow->itemno,1,wk->heapID);
	
	//���[���A�C�e�����o�b�O�ɒǉ�
	if(ret){
		MyItem_AddItem(wk->itemSave,pNow->itemno,1,wk->heapID);
	}
	//���[���Z�[�u�f�[�^���N���A
	MAIL_DelMailData(wk->pBlock,MAILBLOCK_PASOCOM,wk->selectID);

#if 0
	if(!pNow->valid){	//���X�g����폜�ς݂Ȃ炱���ŋA��
		return ret;
	}
#endif
	//���[���f�[�^�����X�g����폜
	mbox_MailChainOut(wk,wk->selectID);

	//���X�g�\���̂��N���A
	mbox_MAIL_LIST_Clear(pNow,wk->selectID);
	return ret;
}

/**
 *	@brief	���[�����|�P�����Ɏ������鏈��
 */
static void mbox_Mail2Poke(MAIL_BOX_MAIN* wk,u8 pokeno,BOOL addItem)
{
	MAIL_LIST* pNow;
	POKEPARTY *pp;
	POKEMON_PARAM* poke;
	
	pNow = &(wk->mailList[wk->selectID]);
	
	if(!pNow->valid){
		return;
	}
	//POKEPARA�擾
	pp = SaveData_GetTemotiPokemon(GameSystem_GetSaveData(wk->fsys));
	poke = PokeParty_GetMemberPointer(pp,pokeno);	
	
	//�|�P�����Ƀ��[�����ڂ�
	MailSys_MoveMailPaso2Poke(wk->pBlock,wk->selectID,poke,wk->heapID);

	if(addItem){
		//���[���������Ă��玝�������ꍇ�A�A�C�e���������Ă���̂łЂƂǉ�����
		if(MyItem_AddCheck(wk->itemSave,pNow->itemno,1,wk->heapID)){
			//���[���A�C�e�����o�b�O�ɒǉ�
			MyItem_AddItem(wk->itemSave,pNow->itemno,1,wk->heapID);
		}
	}
	//���[���f�[�^�����X�g����폜
	mbox_MailChainOut(wk,wk->selectID);
	mbox_MAIL_LIST_Clear(pNow,wk->selectID);
}

/**
 *	@brief	���[���{�b�N�X�@���b�Z�[�W���\�[�X������
 */
static void mbox_MsgResInit(MAIL_BOX_MAIN* wk)
{
	MSGDATA_MANAGER*	pMsg;
	int i;
	STRBUF	*buf;
		
	wk->pMsg = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,
					NARC_msg_mailbox_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx(1,MAILMSG_BUFLEN,wk->heapID);
	
	wk->msgDat.tmp = STRBUF_Create(MAILMSG_BUFLEN,wk->heapID);

	wk->msgDat.ebuf = MSGMAN_AllocString(wk->pMsg,msg_exit);
	wk->msgDat.tbuf = MSGMAN_AllocString(wk->pMsg,msg_title);

	for(i = 0;i < MIDX_MAX;i++){
		wk->msgDat.mbuf[i] = MSGMAN_AllocString(wk->pMsg,msg_select+i);
	}
}

/**
 *	@brief	���[���{�b�N�X�@���b�Z�[�W���\�[�X���
 */
static void mbox_MsgResRelease(MAIL_BOX_MAIN* wk)
{
	int i;

	for(i = 0;i < MIDX_MAX;i++){
		STRBUF_Delete(wk->msgDat.mbuf[i]);
	}
	STRBUF_Delete(wk->msgDat.tbuf);
	STRBUF_Delete(wk->msgDat.ebuf);
	STRBUF_Delete(wk->msgDat.tmp);

	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->pMsg);
}

/**
 *	@brief	���[���{�b�N�Xview �R�������\�[�X�̎擾
 */
static void mbox_ComResInit(MAIL_BOX_MAIN* wk)
{
	//BGL�擾
	wk->bgl = FieldBglIniGet(wk->fsys);

	//�R�����E�B���h�E�O���t�B�b�N�Z�b�g
	TalkWinGraphicSet(wk->bgl,MAILBOX_FRAME,
			BMPL_TALK_WIN_CGX,BMPL_TALK_WIN_PAL,wk->win_type,wk->heapID);
	MenuWinGraphicSet(wk->bgl,MAILBOX_FRAME,
			BMPL_MENU_WIN_CGX,BMPL_MENU_WIN_PAL,MENU_TYPE_SYSTEM,wk->heapID);

	SystemFontPaletteLoad(PALTYPE_MAIN_BG,FLD_SYSFONT_PAL*32,wk->heapID);
	TalkFontPaletteLoad(PALTYPE_MAIN_BG,FLD_MESFONT_PAL*32,wk->heapID);

	//�R�����E�B���h�EAdd
	GF_BGL_BmpWinAdd(
			wk->bgl, &wk->msgwin, MAILBOX_FRAME,
			BMPL_TALK_PX,BMPL_TALK_PY,BMPL_TALK_SX,BMPL_TALK_SY,
			BMPL_TALK_PAL,BMPL_TALK_CGX);
	GF_BGL_BmpWinDataFill(&wk->msgwin,FBMP_COL_NULL);
}

/**
 *	@brief	���[���{�b�N�Xview �R�������\�[�X�̉��
 */
static void mbox_ComResRelease(MAIL_BOX_MAIN* wk)
{
	GF_BGL_BmpWinOff(&wk->msgwin);
	GF_BGL_BmpWinDel(&wk->msgwin);
	MI_CpuClear8(&wk->msgwin,sizeof(GF_BGL_BMPWIN));
	wk->bgl = NULL;
}

/**
 *	@brief	���[���{�b�N�X�@��b���b�Z�[�W�`��
 */
static void mbox_PrintTalkMsg(MAIL_BOX_MAIN* wk,MBOX_MSGIDX idx,u8 spd,u8 del_f,int win_f)
{
	STRBUF* msg;

	if(win_f){
		BmpTalkWinWrite( &wk->msgwin, WINDOW_TRANS_OFF, BMPL_TALK_WIN_CGX, BMPL_TALK_WIN_PAL);		
	}
	GF_BGL_BmpWinFill( &wk->msgwin,WINCLR_COL(FBMP_COL_WHITE),
		0, 0,BMPL_TALK_SX*8,BMPL_TALK_SY*8);

	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_SKIP_OFF );

	if(idx == MIDX_SELECT){
		STRBUF_Clear(wk->msgDat.tmp);
		WORDSET_RegisterWord( wk->msgDat.wset,0,
				wk->mailList[wk->selectID].name,PM_NEUTRAL,TRUE,PM_LANG);
		WORDSET_ExpandStr(wk->msgDat.wset,wk->msgDat.tmp,wk->msgDat.mbuf[idx]);				

		msg = wk->msgDat.tmp;
	}else{
		msg = wk->msgDat.mbuf[idx];
	}
	//���b�Z�[�W�`��
	wk->msgIdx = GF_STR_PrintColor(
		&wk->msgwin, FONT_TALK, msg,
		0, 0, spd, TALK_FCOL, NULL );

	GF_BGL_BmpWinOn(&wk->msgwin);
	wk->msgwin_f = del_f;	//���b�Z�[�W�҂���ɃE�B���h�E���N���A���邩�ǂ����H
}

/**
 *	@brief	���[���{�b�N�X�@��b���b�Z�[�W�I���҂�
 */
static void mbox_TalkMsgClear(MAIL_BOX_MAIN* wk)
{
	BmpTalkWinClear( &wk->msgwin, WINDOW_TRANS_OFF);		
	GF_BGL_BmpWinOff(&wk->msgwin);
}

/**
 *	@brief	���[���{�b�N�X�@��b���b�Z�[�W�I���҂�
 */
static BOOL mbox_TalkMsgWait(MAIL_BOX_MAIN* wk)
{
	if( GF_MSG_PrintEndCheck( wk->msgIdx )){
		return FALSE;
	}
	if(wk->msgwin_f){
		mbox_TalkMsgClear(wk);
	}
	return TRUE;
}

/**
 *	@brief	���[���{�b�N�X�@YN�E�B���h�E������
 */
static void mbox_YesNoInit(MAIL_BOX_MAIN* wk)
{
	static const BMPWIN_DAT YesNoBmpWin = {
		MAILBOX_FRAME,BMPL_YESNO_PX,BMPL_YESNO_PY,BMPL_YESNO_SX,BMPL_YESNO_SY,
		BMPL_YESNO_PAL,BMPL_YESNO_CGX
	};

	wk->ynmenu_wk = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, BMPL_MENU_WIN_CGX, BMPL_MENU_WIN_PAL, wk->heapID);
}

/**
 *	@brief	���[���{�b�N�X�@YN�I��҂�
 */
static int mbox_YesNoWait(MAIL_BOX_MAIN* wk)
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

/**
 *	@brief	�t�F�[�h�Ăяo��
 */
static int mbox_FadeCall(MAIL_BOX_MAIN* wk,int type)
{
	switch(wk->sub_seq){
	case 0:
		WIPE_SYS_Start(WIPE_PATTERN_WMS,
				type,type,0x0000,COMM_BRIGHTNESS_SYNC,1,wk->heapID
				);
		wk->sub_seq++;
		break;
	case 1:
		if(!WIPE_SYS_EndCheck()){
			break;
		}
		wk->sub_seq = 0;
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	�t�B�[���h�v���Z�X���A�R�[��
 */
static int mbox_FieldSetCall(MAIL_BOX_MAIN* wk)
{
	switch(wk->sub_seq){
	case 0:
		//�t�B�[���h�}�b�v�v���Z�X���A
		FieldEvent_Cmd_SetMapProc(wk->fsys);
		wk->sub_seq++;
		break;		
	case 1:
		//�t�B�[���h�v���Z�X�J�n�I���҂�
		if(!FieldEvent_Cmd_WaitMapProcStart(wk->fsys)){
			break;
		}
		//�C�x���g�t�b�N
#ifdef PM_DEBUG
		if(wk->deb_flag){
			FieldSystemProc_SeqHold();
			wk->sub_seq = 0;
			return TRUE;
		}
#endif	//PM_DEBUG
		//�p�\�R���A�j�����A
		FLD_SCR_ANM_PASO_Setup(wk->fsys,SCR_PASO_ANM_NO);
		FLD_SCR_ANM_PASO_PasoOnAnm(wk->fsys,SCR_PASO_ANM_NO);
		wk->sub_seq++;
		break;
	case 2:
		//�p�\�R���A�j���҂�
		if(!F3DASub_WaitAnimation(wk->fsys->AnimeContMng,SCR_PASO_ANM_NO)){
			break;
		}
		wk->sub_seq = 0;
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	���X�g����
 */
static int mbox_ListFree(MAIL_BOX_MAIN* wk,u8 mode)
{
#ifdef PM_DEBUG
	if(wk->deb_flag == 0){
		//�p�\�R���A�j�����
		FLD_SCR_ANM_DOOR_FreeDoor(wk->fsys,SCR_PASO_ANM_NO);
	}
#else
	//�p�\�R���A�j�����
	FLD_SCR_ANM_DOOR_FreeDoor(wk->fsys,SCR_PASO_ANM_NO);
#endif
	if(mode == LIST_MAIL){
		//���[�����X�g���
		mbox_MailListEnd(wk);
	}else{
		//���X�g���\�[�X���
		mbox_SelectListEnd(wk);
	}
	mbox_ComResRelease(wk);
	return TRUE;
}

/**
 *	@brief	�|�P�������X�g�Ăяo��
 */
static int mbox_PokeListCall(MAIL_BOX_MAIN* wk,int mode)
{
	PLIST_DATA* pld;

	switch(wk->sub_seq){
	case 0:
		pld = sys_AllocMemory( wk->heapID, sizeof(PLIST_DATA) );
		MI_CpuClear8( pld,sizeof(PLIST_DATA) );
		pld->pp = SaveData_GetTemotiPokemon(GameSystem_GetSaveData(wk->fsys));
		pld->myitem = SaveData_GetMyItem(GameSystem_GetSaveData(wk->fsys));
		pld->cfg = SaveData_GetConfig(GameSystem_GetSaveData(wk->fsys));
		pld->mailblock = SaveData_GetMailBlock( wk->fsys->savedata );

		pld->type = PL_TYPE_SINGLE;
		pld->mode = mode;//PL_MODE_MAILBOX;
		pld->item = wk->mailList[wk->selectID].itemno;

		if(mode == PL_MODE_MAILSET){
			pld->ret_sel = wk->selPos;
		}
		GameSystem_StartSubProc( wk->fsys, &PokeListProcData, pld );
		wk->plist = pld;
		wk->sub_seq++;
		break;
	case 1:
		if(FieldEvent_Cmd_WaitSubProcEnd(wk->fsys)){
			break;
		}
		wk->sub_seq = 0;	
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	���[���Ăяo��
 */
static int mbox_MailCall(MAIL_BOX_MAIN* wk)
{
	int ret = 0;
	
	switch(wk->sub_seq){
	case 0:
		if(wk->mailList[wk->selectID].valid){
			//���[��������
			wk->param =  FieldMailView_InitCall(wk->fsys,
				MAILBLOCK_PASOCOM,wk->selectID,wk->heapID);
		}else{
#ifdef PM_DEBUG
			if(wk->deb_flag == 2){
				//�f�o�b�O���[���쐬
				wk->param =  FieldMailCreate_InitCall( wk->fsys,
					MAILBLOCK_PASOCOM,0,wk->deb_design,wk->heapID);
			}else{
				//���������[�����|�P�����Ɏ�������Ƃ��̃��[���쐬
				wk->param =  FieldMailCreate_InitCall( wk->fsys,
					MAILBLOCK_PASOCOM,wk->selPos,
					wk->mailList[wk->selectID].design,wk->heapID);
			}
#else
			//���������[�����|�P�����Ɏ�������Ƃ��̃��[���쐬
			wk->param =  FieldMailCreate_InitCall( wk->fsys,
				MAILBLOCK_PASOCOM,wk->selPos,
				wk->mailList[wk->selectID].design,wk->heapID);
#endif
		}
		wk->sub_seq++;
		break;
	case 1:
		//�v���Z�X�I���҂�
		if(FieldEvent_Cmd_WaitSubProcEnd(wk->fsys)){
			break;
		}
		if(MailSys_IsDataCreate(wk->param)){
			wk->mailList[wk->selectID].valid = 1;
			//�쐬�f�[�^���Z�[�u�f�[�^�ɔ��f
			MailSys_PushDataToSave(wk->param,MAILBLOCK_PASOCOM,wk->mailList[wk->selectID].id);
#ifdef PM_DEBUG
			if(wk->deb_flag==2){
				wk->mailList[wk->selectID].sex = MailData_GetWriterSex(wk->param->pDat);
				STRBUF_SetStringCode(wk->mailList[wk->selectID].name,MailData_GetWriterName(wk->param->pDat));
			}
#endif
			ret = 2;
		}else{
			ret = 1;
		}
		MailSys_ReleaseCallWork(wk->param);
		wk->sub_seq = 0;
		return ret;
	}
	return FALSE;
}

//========================================================
//	�X�N���v�g�R�}���h
//========================================================
typedef struct _MAILBOX_EVENT{
	int	ret_val;
	int	seq;
}MAILBOX_EVENT;

//--------------------------------------------------------------
/**
 * @brief	���[���{�b�N�X�C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL MyPCEvent_MailBox( GMEVENT_CONTROL *ev )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	MAILBOX_EVENT *wk = FieldEvent_GetSpecialWork( ev );

	switch (wk->seq) {
	case 0:
		//���[���{�b�N�X�^�X�N�o�^
		MailBox_Call(fsys,&(wk->ret_val));
		wk->seq++;
		break;
	case 1:
		if(!wk->ret_val){
			return FALSE;
		}
		sys_FreeMemoryEz(wk);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	���[���{�b�N�X�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		�ړ�����
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_MailBoxCall( GMEVENT_CONTROL *event)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	
	MAILBOX_EVENT *wk = sys_AllocMemoryLo( HEAPID_WORLD,sizeof(MAILBOX_EVENT));
	
	wk->ret_val = 0;
	wk->seq = 0;
	FieldEvent_Call( fsys->event, MyPCEvent_MailBox, wk);
}

