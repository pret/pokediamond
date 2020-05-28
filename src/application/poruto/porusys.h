/***
 *	@file	porusys.h
 *	@brief	�|���g���W���[�������[�J���w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.03.11
 */

#ifndef __H_PORU_SYS_H__
#define __H_PORU_SYS_H__

#include "application/poru_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/poruto_name.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "porucase.dat"
#include "poru_snd_def.h"

//�v���g�^�C�v
typedef struct _PORU_CASE_WORK PORU_CASE_WORK;
#include "poru_act.h"
#include "poru_oam.h"

#define WORDSET_PORU_BUFLEN	(64)

typedef enum{
 PVIEW_SPICY,
 PVIEW_ASTR,
 PVIEW_SWEET,
 PVIEW_BITTER,
 PVIEW_SOUR,
 PVIEW_ALL,
 PVIEW_MAX,
}PCASE_VIEW;

typedef enum{
 PCASE_RET_CANCEL,
 PCASE_RET_DECIDE,
}PCASE_RET;

typedef enum{
 PCASE_MODE_PSEL,
 PCASE_MODE_MSEL,
 PCASE_MODE_MSELWAIT,
 PCASE_MODE_YNSET,
 PCASE_MODE_YNWAIT,
 PCASE_MODE_DEL,
 PCASE_MODE_EXIT,
};

typedef struct _PORUCASE_MSG{
	WORDSET* wset;		//���[�N
	STRBUF	*tmp;		//�ėp
	STRBUF	*endbuf;	//��߂�
	STRBUF	*listbuf;	//��߂�
	STRBUF	*tbuf;		//���炩��
	STRBUF	*qbuf;		//�̂Ă܂����H
	STRBUF	*dbuf;		//�̂Ă܂���
	STRBUF	*sbuf;		//�T���l�C��
	STRBUF	*swbuf[PVIEW_MAX];		//����ʃX�C�b�`
	STRBUF	*exbuf[PVIEW_ALL];		//����ʐ�����
	u8	msg_spd;	///<���b�Z�[�W�X�s�[�h
	u8	dmy[3];	///<padding
}PORUCASE_MSG;

typedef struct _PORU_CASE_WORK{
	int	heapID;
	int	seq;
	int	sub_seq;
	int	wipe_f;
	int ret_mode;
	u16	tp_f;
	u16	plist_cb_f;	///<�|���g���X�g�R�[���o�b�N�����L��
	u16	selMode;
	u8	selectID;
	u8	viewMode;

	u8	viewNum;
	u8	startID;
	u8	endID;

	u8	msgIdx;
	PORUTO_PARAM* param;	///<���p���p�����[�^
	GF_BGL_INI *bgl;	///<BGL�f�[�^

	///�|���g���擾�}�l�[�W��
	PORUTO_NAME_MAN	*nameMan;
	MSGDATA_MANAGER *msgMan;
	PORUCASE_MSG	msgDat;

	///�|���g���X�g�R���g���[��
	u16		listPos;
	u16		curPos;
	BMPLIST_HEADER	plist_h;
	BMPLIST_HEADER	mlist_h;
	BMPLIST_WORK* plist_wk; 
	BMPLIST_WORK* mlist_wk; 
	BMPLIST_DATA* plist; 
	BMPLIST_DATA* mlist; 
	BMPMENU_WORK* ynmenu_wk; 

	///�O���t�B�b�N���\�[�X
	void*	pScrBuf01;
	void*	pScrBuf02;
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr02;
	GF_BGL_BMPWIN	win[WIN_MAX];
	
	CATS_SYS_PTR	pActSys;	///<�Z���A�N�^�[�V�X�e��
	CATS_RES_PTR	pActRes;	///<�Z���A�N�^�[���\�[�X
	CLACT_WORK_PTR	pAct[NORMAL_ACTMAX];		///<�A�N�^�[
	CLACT_WORK_PTR	pActFmk[FMARK_ACTMAX];		///<�A�N�^�[
	CLACT_WORK_PTR	pActBtn[BUTTON_ACTMAX];		///<�A�N�^�[

	PORUOAM_MAN		*poruMan;	///<�|���gOAM�}�l�[�W��
	PORUTO_OAM		*pOam;		///<�|���g	
}PORU_CASE_WORK;

#define WINCLR_COL(col)	(((col)<<4)|(col))

///�|���g���W���[�����O���Q��
extern PROC_RESULT PoruCase_Init(PROC* proc,int* seq);
extern PROC_RESULT PoruCase_Main(PROC* proc,int* seq);
extern PROC_RESULT PoruCase_End(PROC* proc,int* seq);

#endif	//__H_PORU_SYS_H__

