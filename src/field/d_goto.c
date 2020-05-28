//==============================================================================
/**
 * @file	d_goto.c
 * @brief	�㓡�p�f�o�b�O�p�t�@�C��
 * @author	goto
 * @date	2005.06.20(��)
 */
//==============================================================================
#ifdef PM_DEBUG

#include "common.h"
#include "system/pm_overlay.h"
#include "system/test_overlay.h"

#include "system/bmp_list.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "contest/contest.h"

#include "script.h"

#include "system/fontproc.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_goto.h"

extern void DebugGotoMenuInit(FIELDSYS_WORK* fsys);

extern void CustomBallEdit_Start(FIELDSYS_WORK *fsys);

//==============================================================================
//	�I�[�o�[���CID��extern�錾
//==============================================================================
/* overlay id in *.lcf */
FS_EXTERN_OVERLAY(test_first);
FS_EXTERN_OVERLAY(test_second);
FS_EXTERN_OVERLAY(test_itcm);
FS_EXTERN_OVERLAY(test_second_abc);


//==============================================================================
//	�\���̐錾
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �㓡�f�o�b�O�p�\����
 */
//--------------------------------------------------------------
typedef struct{
	FIELDSYS_WORK *fsys;
	BMPLIST_WORK *lw;
	BMP_MENULIST_DATA *listmenu;
	GF_BGL_BMPWIN bmpwin;
	s16 wait;
	u8 main_seq;
}DGOTO_WORK;


//==============================================================================
//	�^�錾
//==============================================================================
typedef void (*pDMFunc)(DGOTO_WORK *);


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void DG_MenuMain(TCB_PTR tcb, void *work);
static void DG_MenuExit(DGOTO_WORK *dm);
static void DG_CustomStart(DGOTO_WORK *dm);
static void DG_CustomStart2(DGOTO_WORK *dm);
static void DG_SealAdd(DGOTO_WORK *dm);
static void DG_EggDemoNormal(DGOTO_WORK *dm);
static void DG_EggDemoSpecial(DGOTO_WORK *dm);


//==============================================================================
//	�f�o�b�O���j���[���X�g�p�f�[�^��
//==============================================================================
///�f�o�b�O���j���[�̍���
static const struct {
	
	u32  str_id;
	u32  param;
	
} DebugMenuParamList[] = {
	
	{ dmg_01,		(u32)DG_CustomStart		},
	{ dmg_01_01,	(u32)DG_CustomStart2	},
	{ dmg_02,		(u32)DG_SealAdd			},
	{ dmg_03,		(u32)DG_EggDemoNormal	},
	{ dmg_04,		(u32)DG_EggDemoSpecial	},
	
};


#define LIST_MENU_MAX		(NELEMS(DebugMenuParamList))

///�f�o�b�O���j���[�̃��X�g
static const BMPLIST_HEADER DebugMenuListHeader = {
	NULL,			// �\�������f�[�^�|�C���^
	NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
	NULL,
	LIST_MENU_MAX,	// ���X�g���ڐ�
	LIST_MENU_MAX,						// �\���ő區�ڐ�
	0,						// ���x���\���w���W
	8,						// ���ڕ\���w���W
	0,						// �J�[�\���\���w���W
	0,						// �\���x���W
	FBMP_COL_WHITE,			// �����F
	FBMP_COL_BLACK,			// �w�i�F
	FBMP_COL_BLK_SDW,		// �����e�F
	0,						// �����Ԋu�w
	16,						// �����Ԋu�x
	BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
	FONT_SYSTEM,				// �����w��
	0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
};

#define DGOTO_HEAP	(HEAPID_BASE_DEBUG)

void DebugGotoMenuInit(FIELDSYS_WORK* fsys)
{
	DGOTO_WORK *dm;
	BMPLIST_HEADER list_h;
	
	dm = sys_AllocMemory(DGOTO_HEAP, sizeof(DGOTO_WORK));
	memset(dm, 0, sizeof(DGOTO_WORK));
	
	//BMP�E�B���h�E����
	GF_BGL_BmpWinAdd(fsys->bgl, &dm->bmpwin, 
		FLD_MBGFRM_FONT, 1, 1, 15, 24, 13, 1);
	dm->fsys = fsys;
	
	dm->listmenu = BMP_MENULIST_Create(LIST_MENU_MAX, DGOTO_HEAP);

	//�����񃊃X�g�쐬
	{
		MSGDATA_MANAGER *man;
		STRBUF * str_buf;
		int i;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
			NARC_msg_debug_goto_dat, DGOTO_HEAP);
		
		for(i = 0; i < LIST_MENU_MAX; i++){
			BMP_MENULIST_AddArchiveString(dm->listmenu, man, DebugMenuParamList[i].str_id, 
				DebugMenuParamList[i].param);
		}
		
		MSGMAN_Delete(man);
	}
	
	list_h = DebugMenuListHeader;
	list_h.win = &dm->bmpwin;
    list_h.list = dm->listmenu;
	dm->lw = BmpListSet(&list_h, 0, 0, DGOTO_HEAP);
	
	GF_BGL_BmpWinOn(&dm->bmpwin);
	
	TCB_Add(DG_MenuMain, dm, 10);
//	FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------
/**
 * @brief   �㓡�p�f�o�b�O���j���[���X�g�I��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�f�o�b�O�p�㓡���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DG_MenuMain(TCB_PTR tcb, void *work)
{
	DGOTO_WORK *dm = work;
	u32	ret;

	ret = BmpListMain(dm->lw);
	switch(dm->main_seq){
	case 0:
		dm->main_seq++;
		break;
	case 1:
		switch(ret){
		case BMPLIST_NULL:
			break;
		case BMPLIST_CANCEL:
			DG_MenuExit(dm);
			TCB_Delete(tcb);
			sys_FreeMemoryEz(dm);
			FieldSystemProc_SeqHoldEnd();
			return;
		default:
			{
				pDMFunc func = (pDMFunc)ret;

				DG_MenuExit(dm);
				TCB_Delete(tcb);
				func(dm);
				sys_FreeMemoryEz(dm);
				return;
			}
			break;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �㓡�p�f�o�b�O���j���[���X�g�����
 * @param   dm		�f�o�b�O�p�㓡���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DG_MenuExit(DGOTO_WORK *dm)
{
	BMP_MENULIST_Delete(dm->listmenu);
	BmpListExit(dm->lw, NULL, NULL);

	GF_BGL_BmpWinOff(&dm->bmpwin);
	GF_BGL_BmpWinDel(&dm->bmpwin);
}


#include "savedata/custom_ball.h"
#include "src/demo/egg/egg.h"
static void DG_CustomStart(DGOTO_WORK *dm)
{

	CustomBallEdit_Start(dm->fsys);
	
}

static void DG_CustomStart2(DGOTO_WORK *dm)
{
	Debug_CB_SaveData_Sample(CB_SaveData_AllDataGet(dm->fsys->savedata), 1);
	
	CustomBallEdit_Start(dm->fsys);
	
}

static void DG_SealAdd(DGOTO_WORK *dm)
{
	Debug_CB_SaveData_Sample(CB_SaveData_AllDataGet(dm->fsys->savedata), 0);
	
	CustomBallEdit_Start(dm->fsys);
}


static void DG_EggDemoNormal(DGOTO_WORK *dm)
{
	DebugEGG_DemoStart(dm->fsys);
}


static void DG_EggDemoSpecial(DGOTO_WORK *dm)
{
	DebugEGG_DemoStartMana(dm->fsys);
}

#endif