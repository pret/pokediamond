//==============================================================================
/**
 * @file	d_matsu.c
 * @brief	���c�f�o�b�O�p�t�@�C��
 * @author	matsuda
 * @date	2005.06.20(��)
 */
//==============================================================================

#ifdef PM_DEBUG	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include "common.h"
#include "system/pm_overlay.h"
#include "system/test_overlay.h"

#include "system/bmp_list.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "system/fontproc.h"
#include "contest/contest.h"

#include "script.h"
#include "..\fielddata\script\connect_def.h"

#include "system/particle.h"
#include "particledata/particledata.h"
#include "particledata/particledata.naix"

#include "system/fontproc.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_matsu.h"

#include "field/sysflag.h"




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
 * @brief   ���c�f�o�b�O�p�\����
 */
//--------------------------------------------------------------
typedef struct{
	FIELDSYS_WORK *fsys;
	BMPLIST_WORK *lw;
	BMP_MENULIST_DATA *listmenu;
	GF_BGL_BMPWIN bmpwin;
	s16 wait;
	u8 main_seq;
}DMATSU_WORK;

//--------------------------------------------------------------
/**
 * @brief   ���c�f�o�b�O�p�\����(�O���[�o���ϐ�)
 */
//--------------------------------------------------------------
typedef struct{
	u8 dance_rotation_off;		///<1:�_���X�̃��[�e�[�V�����Ȃ�
}DMATSU_GLOBAL_WORK;

//==============================================================================
//	�O���[�o���ϐ��錾
//==============================================================================
///1:���[�e�[�V�����Ȃ��B�@0:���[�e�[�V��������@2:�_���X�񐔐����Ȃ�
u8 DmatsuWork_DanceRotationOff = 0;

//==============================================================================
//	�^�錾
//==============================================================================
typedef void (*pDMFunc)(DMATSU_WORK *);

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void DM_MenuMain(TCB_PTR tcb, void *work);
static void DM_MenuExit(DMATSU_WORK *dm);
static void DM_ActingStart(DMATSU_WORK *dm);
static void DM_VisualStart(DMATSU_WORK *dm);
static void DM_ClipVisualStart(DMATSU_WORK *dm);
static void DM_DanceStart(DMATSU_WORK *dm);
static void DM_DanceNoneLimitStart(DMATSU_WORK *dm);
static void DM_DanceRotatinOn(DMATSU_WORK *dm);
static void DM_DanceRotationOff(DMATSU_WORK *dm);
static void DM_ContestSioStart(DMATSU_WORK *dm);
static void DM_ResultStart(DMATSU_WORK *dm);
static void TestOverlaySet(DMATSU_WORK *dm);
static void TestSet(DMATSU_WORK *dm);
static void FieldParticleTest(DMATSU_WORK *dm);
static void DM_SysFlagON_Style(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Style(DMATSU_WORK *dm);
static void DM_SysFlagON_Beautiful(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Beautiful(DMATSU_WORK *dm);
static void DM_SysFlagON_Cute(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Cute(DMATSU_WORK *dm);
static void DM_SysFlagON_Clever(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Clever(DMATSU_WORK *dm);
static void DM_SysFlagON_Strong(DMATSU_WORK *dm);
static void DM_SysFlagOFF_Strong(DMATSU_WORK *dm);
void DebugMatsudaInit(FIELDSYS_WORK *fsys);

//==============================================================================
//	�f�o�b�O���j���[���X�g�p�f�[�^��
//==============================================================================
///�f�o�b�O���j���[�̍���
static const struct {
	u32  str_id;
	u32  param;
}DebugMenuParamList[] = {
	{ DMMSG_ACTIN, (u32)DM_ActingStart },
	{ DMMSG_VISUAL, (u32)DM_VisualStart},
	{ DMMSG_CLIP_VISUAL, (u32)DM_ClipVisualStart},
	{ DMMSG_DANCE, (u32)DM_DanceStart},
	{ DMMSG_DANCE_NONE_LIMIT, (u32)DM_DanceNoneLimitStart},
	{ DMMSG_ROTE_ON, (u32)DM_DanceRotatinOn},
	{ DMMSG_ROTE_OFF, (u32)DM_DanceRotationOff},
	{ DMMSG_TUUSHIN, (u32)DM_ContestSioStart},
	{ DMMSG_RESULT, (u32)DM_ResultStart},
	{ DMMSG_PARTICLE, (u32)FieldParticleTest },
	{ DMMSG_OVERLAY, (u32)TestOverlaySet },
	{ DMMSG_SYSFLAG_ON_STYLE, (u32)DM_SysFlagON_Style },
	{ DMMSG_SYSFLAG_OFF_STYLE, (u32)DM_SysFlagOFF_Style },
	{ DMMSG_SYSFLAG_ON_BEAUTIFUL, (u32)DM_SysFlagON_Beautiful },
	{ DMMSG_SYSFLAG_OFF_BEAUTIFUL, (u32)DM_SysFlagOFF_Beautiful },
	{ DMMSG_SYSFLAG_ON_CUTE, (u32)DM_SysFlagON_Cute },
	{ DMMSG_SYSFLAG_OFF_CUTE, (u32)DM_SysFlagOFF_Cute },
	{ DMMSG_SYSFLAG_ON_CLEVER, (u32)DM_SysFlagON_Clever },
	{ DMMSG_SYSFLAG_OFF_CLEVER, (u32)DM_SysFlagOFF_Clever },
	{ DMMSG_SYSFLAG_ON_STRONG, (u32)DM_SysFlagON_Strong },
	{ DMMSG_SYSFLAG_OFF_STRONG, (u32)DM_SysFlagOFF_Strong },
};


#define LIST_MENU_MAX		(NELEMS(DebugMenuParamList))

///�f�o�b�O���j���[�̃��X�g
static const BMPLIST_HEADER DebugMenuListHeader = {
	NULL,			// �\�������f�[�^�|�C���^
	NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
	NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
	NULL,
	LIST_MENU_MAX,	// ���X�g���ڐ�
	11,//LIST_MENU_MAX,						// �\���ő區�ڐ�
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




//--------------------------------------------------------------
/**
 * @brief   �I�[�o�[���C�e�X�g
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void TestOverlayStart(TCB_PTR tcb, void *work)
{
	DMATSU_WORK *dm = work;
	
	if(dm->wait == 0){
		dm->wait++;
		/* address of function is specified in main.lsf */
		OS_Printf("func_1() : addr = 0x%08X.\n", test_overlay_func_1);
		OS_Printf("func_2() : addr = 0x%08X.\n", test_overlay_func_2);
		OS_Printf("func_3() : addr = 0x%08X.\n", test_overlay_itcm);
		return;
	}
	
	//OS_PrintServer();

	//�e�\���L�[�ɂ���ăI�[�o�[���C�ǂݏo��
	if(sys.trg & PAD_KEY_RIGHT){
		//�܂�������Ԃ��g�p���Ă���I�[�o�[���C��S�ăA�����[�h
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_first));
		//�������g���I�[�o�[���C���s
		Overlay_Load(FS_OVERLAY_ID(test_first), OVERLAY_LOAD_NOT_SYNCHRONIZE);
	}
	else if(sys.trg & PAD_KEY_DOWN){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_second));
		Overlay_Load(FS_OVERLAY_ID(test_second), OVERLAY_LOAD_SYNCHRONIZE_2);
		Overlay_Load(FS_OVERLAY_ID(test_second_abc), OVERLAY_LOAD_SYNCHRONIZE_2);
	}
	else if(sys.trg & PAD_KEY_LEFT){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_itcm));
		Overlay_Load(FS_OVERLAY_ID(test_itcm), OVERLAY_LOAD_SYNCHRONIZE);
	}
	else if(sys.trg & PAD_KEY_UP){
		Overlay_UnloadSameArea(FS_OVERLAY_ID(test_second_abc));
		Overlay_Load(FS_OVERLAY_ID(test_second_abc), OVERLAY_LOAD_SYNCHRONIZE_2);
	}

	//�e�{�^���ɂ���ăI�[�o�[���C����Ă���t�@�C�����̊֐��Ăяo��
	if (sys.trg & PAD_BUTTON_A){
		test_overlay_func_1();
	}
	else if (sys.trg & PAD_BUTTON_B){
		test_overlay_func_2();
	}
	else if(sys.trg & PAD_BUTTON_Y){
		test_overlay_itcm();
	}
	else if(sys.trg & PAD_BUTTON_X){
		test_overlay_func_3();
	}
	
	if(sys.trg & PAD_BUTTON_START){
		sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
		TCB_Delete(tcb);
		FieldSystemProc_SeqHoldEnd();
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief   ���c�f�o�b�O�����A�Ăяo����
 */
//--------------------------------------------------------------
void DebugMatsudaInit(FIELDSYS_WORK *fsys)
{
	DMATSU_WORK *dm;
	BMPLIST_HEADER list_h;
	
	dm = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(DMATSU_WORK));
	memset(dm, 0, sizeof(DMATSU_WORK));
	
	//BMP�E�B���h�E����
	GF_BGL_BmpWinAdd(fsys->bgl, &dm->bmpwin, 
		FLD_MBGFRM_FONT, 1, 1, 19, 22, 13, 1);
	dm->fsys = fsys;
	
	dm->listmenu = BMP_MENULIST_Create(LIST_MENU_MAX, HEAPID_BASE_DEBUG);

	//�����񃊃X�g�쐬
	{
		MSGDATA_MANAGER *man;
		STRBUF * str_buf;
		int i;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
			NARC_msg_debug_matsu_dat, HEAPID_BASE_DEBUG);
		
		for(i = 0; i < LIST_MENU_MAX; i++){
			BMP_MENULIST_AddArchiveString(dm->listmenu, man, DebugMenuParamList[i].str_id, 
				DebugMenuParamList[i].param);
		}
		
		MSGMAN_Delete(man);
	}
	
	list_h = DebugMenuListHeader;
	list_h.win = &dm->bmpwin;
    list_h.list = dm->listmenu;
	dm->lw = BmpListSet(&list_h, 0, 0, HEAPID_BASE_DEBUG);
	
	GF_BGL_BmpWinOn(&dm->bmpwin);
	
	TCB_Add(DM_MenuMain, dm, 10);
}

//--------------------------------------------------------------
/**
 * @brief   ���c�p�f�o�b�O���j���[���X�g�I��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�f�o�b�O�p���c���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DM_MenuMain(TCB_PTR tcb, void *work)
{
	DMATSU_WORK *dm = work;
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
			DM_MenuExit(dm);
			TCB_Delete(tcb);
			sys_FreeMemoryEz(dm);
			FieldSystemProc_SeqHoldEnd();
			return;
		default:
			{
				pDMFunc func = (pDMFunc)ret;

				DM_MenuExit(dm);
				TCB_Delete(tcb);
				func(dm);
				return;
			}
			break;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���c�p�f�o�b�O���j���[���X�g�����
 * @param   dm		�f�o�b�O�p���c���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DM_MenuExit(DMATSU_WORK *dm)
{
	BMP_MENULIST_Delete(dm->listmenu);
	BmpListExit(dm->lw, NULL, NULL);

	GF_BGL_BmpWinOff(&dm->bmpwin);
	GF_BGL_BmpWinDel(&dm->bmpwin);
}

static void TestOverlaySet(DMATSU_WORK *dm)
{
	TCB_Add(TestOverlayStart, dm, 20);
}

extern void BattleSystemProc(void);
static void TestSet(DMATSU_WORK *dm)
{
#if 0
	sys.mainSys_sequence = 5;//SEQ_EXIT;
	sys.pReturnProc = BattleSystemProc;
	//FieldSysWork.general_seqno = 0;
#else
//	if(sys.trg & START_BUTTON){
		sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
//		TCB_Delete(tcb);
		FieldSystemProc_SeqHoldEnd();
		return;
//	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F���Z�͕���J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ActingStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_ACTIN);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�r�W���A������J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_VisualStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_VISUAL);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�C���[�W�N���b�v���r�W���A������J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ClipVisualStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_CLIP_VISUAL);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�_���X����J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 0;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�_���X����J�n(�S�Ă̎l�������Ń_���X)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceNoneLimitStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 2;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�_���X����J�n(���[�e�[�V��������)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceRotatinOn(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�_���X����J�n(���[�e�[�V�����Ȃ�)
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_DanceRotationOff(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 1;
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_DANCE);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F�_���X����J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ContestSioStart(DMATSU_WORK *dm)
{
	DmatsuWork_DanceRotationOff = 0;
	EventSet_Script(dm->fsys, SCRID_CONNECT_CONTEST, NULL );
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F���ʔ��\�J�n
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void DM_ResultStart(DMATSU_WORK *dm)
{
	DebugContest_FieldConnectStart(dm->fsys, DEBUG_CON_RESULT);
}

//--------------------------------------------------------------
/**
 * @brief   
 * @param   dm		
 */
//--------------------------------------------------------------
static void DM_SysFlagON_Style(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STYLE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Style(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STYLE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Beautiful(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_BEAUTIFUL);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Beautiful(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_BEAUTIFUL);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Cute(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CUTE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Cute(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CUTE);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Clever(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CLEVER);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Clever(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_CLEVER);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagON_Strong(DMATSU_WORK *dm)
{
	SysFlag_ConMasterSet(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STRONG);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

static void DM_SysFlagOFF_Strong(DMATSU_WORK *dm)
{
	SysFlag_ConMasterReset(SaveData_GetEventWork(dm->fsys->savedata), CONTYPE_STRONG);
	sys_FreeMemoryEz(dm);
	FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���e�X�g
 *
 * @param   dm		
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void FieldParticleTest(DMATSU_WORK *dm);
static void TestTCB_Particle(TCB_PTR tcb, void *work);
static int TestParticle_Main(void);
static u32 sAllocTex(u32 size, BOOL is4x4comp);
static u32 sAllocTexPalette(u32 size, BOOL is4pltt);

typedef struct{
	PTC_PTR ptc;
	u8 seq;
	
}TEST_PARTICLE_WORK;

///�퓬�p�[�e�B�N���̃J�����j�A�ݒ�
#define BP_NEAR			(FX32_ONE)
///�퓬�p�[�e�B�N���̃J�����t�@�[�ݒ�
#define BP_FAR			(FX32_ONE * 900)

static void FieldParticleTest(DMATSU_WORK *dm)
{
	sys_FreeMemory(HEAPID_BASE_DEBUG, dm);
	FieldSystemProc_SeqHoldEnd();
	
	{
		TEST_PARTICLE_WORK *tpw;
		
		tpw = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(TEST_PARTICLE_WORK));
		MI_CpuClear8(tpw, sizeof(TEST_PARTICLE_WORK));
		TCB_Add(TestTCB_Particle, tpw, 20);
	}
}

static void TestTCB_Particle(TCB_PTR tcb, void *work)
{
	TEST_PARTICLE_WORK *tpw = work;
	int heap_id = HEAPID_BASE_DEBUG;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	void *resource;
	
	switch(tpw->seq){
	case 0:		//������
		Particle_SystemWorkInit();	//�p�[�e�B�N���V�X�e��������
		tpw->seq++;
		break;
	case 1:		//�p�[�e�B�N���V�X�e���쐬
		heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE);
		tpw->ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, 
			PARTICLE_LIB_HEAP_SIZE, TRUE, heap_id);
		camera_ptr = Particle_GetCameraPtr(tpw->ptc);
		GFC_SetCameraClip(BP_NEAR, BP_FAR, camera_ptr);

		tpw->seq++;
		break;
	case 2:		//���\�[�X�ǂݍ��݁��o�^
		resource = Particle_ArcResourceLoad(
			ARC_PARTICLE_DATA, NARC_particledata_w_001_spa, heap_id);
		Particle_ResourceSet(tpw->ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
		
		tpw->seq++;
		break;
	case 3:		//�p�[�e�B�N������
		Particle_CreateEmitterCallback(tpw->ptc, 0, NULL, NULL);
		break;
	case 4:		//�p�[�e�B�N�����s
		if(TestParticle_Main() == FALSE){
			tpw->seq++;
		}
		break;
	case 5:		//�p�[�e�B�N���V�X�e���j��
		heap = Particle_HeapPtrGet(tpw->ptc);
		Particle_SystemExit(tpw->ptc);
		sys_FreeMemoryEz(heap);
		
		tpw->seq++;
		break;
	default:
		sys_FreeMemoryEz(tpw);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N���V�X�e���E���C���֐�(�v�Z�E�`�揈���Ȃǂ����s)
 *
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static int TestParticle_Main(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;
	
	GF_G3X_Reset();


	if(Particle_GetActionNum() == 0){
		return FALSE;
	}
	

	draw_num = Particle_DrawAll();	//�p�[�e�B�N���`��

	if(draw_num > 0){
		//�p�[�e�B�N���̕`�悪�I�������̂ŁA�Ăу\�t�g�E�F�A�X�v���C�g�p�J�����ɐݒ�
		GF_G3X_Reset();
	}

	Particle_CalcAll();	//�p�[�e�B�N���v�Z

	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �e�N�X�`��VRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
 *
 * @param   size		�e�N�X�`���T�C�Y
 * @param   is4x4comp	4x4���k�e�N�X�`���ł��邩�ǂ����̃t���O(TRUE=���k�e�N�X�`��)
 *
 * @retval  �ǂݍ��݂��J�n����VRAM�̃A�h���X
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	GF_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	Particle_LnkTexKeySet(key);		//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}

//--------------------------------------------------------------
/**
 * @brief	�e�N�X�`���p���b�gVRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
 *
 * @param	size		�e�N�X�`���T�C�Y
 * @param	is4pltt		4�F�p���b�g�ł��邩�ǂ����̃t���O
 *
 * @retval	�ǂݍ��݂��J�n����VRAM�̃A�h���X
 *
 * direct�`���̃e�N�X�`���̏ꍇ�ASPL_LoadTexPlttByCallbackFunction��
 * �R�[���o�b�N�֐����Ăяo���܂���B
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, NNS_GFD_ALLOC_FROM_LOW);
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "�p�[�e�B�N���Ńp���b�g�̊m�ۂ��o���܂���I\n");
	}
	Particle_PlttLnkTexKeySet(key);	//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_TPrintf("vram=%d\n", address);
	return address;
}

#endif	// PM_DEBUG +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


