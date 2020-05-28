//==============================================================================
/**
 * @file	con_result.c
 * @brief	�R���e�X�g���ʔ��\���
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "system/pmfprint.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"
#include "system/gra_tool.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "system/brightness.h"
#include "system/snd_tool.h"

#include "communication/communication.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_con_tally.h"

#include "con_result.h"
#include "con_tool.h"
#include "res_tool.h"
#include "res_order.h"
#include "res_tcb_pri.h"

#include "system/window.h"
#include "system/wipe.h"
#include "communication/wm_icon.h"

#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);



//==============================================================================
//	�萔��`
//==============================================================================
///���݂̓�����
enum{
	DPW_PROC_MODE_INIT,		///<��������
	DPW_PROC_MODE_MAIN,		///<���C��
	DPW_PROC_MODE_ETC,		///<����ȊO
};

///Vram�]���}�l�[�W���[�^�X�N��
#define CONRES_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

//--------------------------------------------------------------
//	CL_ACT�p�̒萔��`
//--------------------------------------------------------------
///���C��	OAM�Ǘ��̈�E�J�n
#define CONRES_OAM_START_MAIN			(BATTLE_OAM_START_MAIN)
///���C��	OAM�Ǘ��̈�E�I��
#define CONRES_OAM_END_MAIN				(BATTLE_OAM_END_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�J�n
#define CONRES_OAM_AFFINE_START_MAIN		(BATTLE_OAM_AFFINE_START_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�I��
#define CONRES_OAM_AFFINE_END_MAIN		(BATTLE_OAM_AFFINE_END_MAIN)
///�T�u	OAM�Ǘ��̈�E�J�n
#define CONRES_OAM_START_SUB				(BATTLE_OAM_START_SUB)
///�T�u	OAM�Ǘ��̈�E�I��
#define CONRES_OAM_END_SUB				(BATTLE_OAM_END_SUB)
///�T�u �A�t�B���Ǘ��̈�E�J�n
#define CONRES_OAM_AFFINE_START_SUB		(BATTLE_OAM_AFFINE_START_SUB)
///�T�u	�A�t�B���Ǘ��̈�E�I��
#define CONRES_OAM_AFFINE_END_SUB		(BATTLE_OAM_AFFINE_END_SUB)

///�L�����}�l�[�W���F�L�����N�^ID�Ǘ���(���ʁ{�����)
#define CONRES_CHAR_MAX					(BATTLE_CHAR_MAX)
///�L�����}�l�[�W���F���C����ʃT�C�Y(byte�P��)
#define CONRES_CHAR_VRAMSIZE_MAIN		(BATTLE_CHAR_VRAMSIZE_MAIN)
///�L�����}�l�[�W���F�T�u��ʃT�C�Y(byte�P��)
#define CONRES_CHAR_VRAMSIZE_SUB			(BATTLE_CHAR_VRAMSIZE_SUB)

///���C����ʁ{�T�u��ʂŎg�p����A�N�^�[����
#define CONRES_ACTOR_MAX					(BATTLE_ACTOR_MAX)

///OBJ�Ŏg�p����p���b�g�{��(���ʁ{�����)
#define CONRES_OAM_PLTT_MAX				(BATTLE_OAM_PLTT_MAX)

///�]�����[�h 3D = 0 main = 1 sub = 2 main/sub = 3
#define CONRES_OAM_VRAM_TRANS			(BATTLE_OAM_VRAM_TRANS)

///OAM���\�[�X�F�L�����o�^�ő吔(���C����� + �T�u���)
#define CONRES_OAMRESOURCE_CHAR_MAX		(BATTLE_OAMRESOURCE_CHAR_MAX)
///OAM���\�[�X�F�p���b�g�o�^�ő吔(���C����� + �T�u���)
#define CONRES_OAMRESOURCE_PLTT_MAX		(BATTLE_OAMRESOURCE_PLTT_MAX)
///OAM���\�[�X�F�Z���o�^�ő吔
#define CONRES_OAMRESOURCE_CELL_MAX		(BATTLE_OAMRESOURCE_CELL_MAX)
///OAM���\�[�X�F�Z���A�j���o�^�ő吔
#define CONRES_OAMRESOURCE_CELLANM_MAX	(BATTLE_OAMRESOURCE_CELLANM_MAX)
///OAM���\�[�X�F�}���`�Z���o�^�ő吔
#define CONRES_OAMRESOURCE_MCELL_MAX		(BATTLE_OAMRESOURCE_MCELL_MAX)
///OAM���\�[�X�F�}���`�Z���A�j���o�^�ő吔
#define CONRES_OAMRESOURCE_MCELLANM_MAX	(BATTLE_OAMRESOURCE_MCELLANM_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�T�u���BG�̃X�N���[���N���A�R�[�h
#define SUB_BG_CLEAR_CODE		(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�ǂ񂿂傤�̃p���b�g�ԍ�
#define DONTYOU_PALNO			(0xc)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///���ʔ��\���J�n���鎞�̑҂�����
#define RESULT_ANNOUNCEMENT_WAIT			(60)
///�r�W���A������̌��ʔ��\��������̑҂�����
#define RESULT_ANNOUNCEMENT_WAIT_VISUAL		(60)
///�r�W���A������̌��ʔ��\��������̑҂�����
#define RESULT_ANNOUNCEMENT_WAIT_DANCE		(90)
///�r�W���A������̌��ʔ��\��������̑҂�����
#define RESULT_ANNOUNCEMENT_WAIT_ACTIN		(15)

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void ConresVBlank(void *work);
static void ConresHBlank(void *work);
static void ConresUpdate(TCB_PTR tcb, void *work);
static void ConresSys_VramBankSet(GF_BGL_INI *bgl);
static void ConresSys_DefaultBmpWinAdd(CONRES_PROC_WORK *rpw);
static void ConresSystemWorkInit(CONRES_PROC_WORK *rpw);
static void ConresDefaultOBJSet(CONRES_PROC_WORK *rpw);
static void ConresDefaultOBJDel(CONRES_PROC_WORK *rpw);
static void ConresDefaultOBJSet_Sub(CONRES_PROC_WORK *rpw);
static void ConresDefaultOBJDel_Sub(CONRES_PROC_WORK *rpw);
static void ConresDefaultBGSet(CONRES_PROC_WORK *rpw);
static void ConresDefaultBGDel(CONRES_PROC_WORK *rpw);
static void ConresDefaultBGSet_Sub(CONRES_PROC_WORK *rpw);
static void ConresDefaultBGDel_Sub(CONRES_PROC_WORK *rpw);
static int ConresSeq_Init(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_FastTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_DonchouUp(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_ResultChange(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_RankingAnnounce(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_ResultTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_DonchouDown(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_EndTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_End(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static void ConresParticleInit(void);
static int ConresSeq_ChangeFirstTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_ResultVisual(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_ResultDance(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static int ConresSeq_ResultActin(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local);
static void VBlankTCB_IntrTask(TCB_PTR tcb, void *work);


//==============================================================================
//	�f�[�^
//==============================================================================

//==============================================================================
//	�V�[�P���X�e�[�u��
//==============================================================================
///ConresMainSeqTbl�̖߂�l�Ƃ��Ďg�p
enum{
	CRRET_CONTINUE,		///<����ێ�
	CRRET_NEXT,			///<���̃V�[�P���X��
	CRRET_SELECT_SEQ,	///<select_seq���[�N�ɓ����Ă���V�[�P���X�֐i��
	CRRET_END,			///<�I��
};

///���ʔ��\���僁�C���֐��̃V�[�P���X�e�[�u��
static int (* const ConresMainSeqTbl[])(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local) = {
	ConresSeq_Init,
	ConresSeq_FastTalk,
//	ConresSeq_DonchouUp,
//	ConresSeq_DonchouDown,
	ConresSeq_ResultChange,
	ConresSeq_ChangeFirstTalk,
	ConresSeq_ResultVisual,
	ConresSeq_ResultDance,
	ConresSeq_ResultActin,
	ConresSeq_RankingAnnounce,
	ConresSeq_ResultTalk,
	ConresSeq_EndTalk,
	ConresSeq_End,
};
///ConresMainSeqTbl�̃V�[�P���X�ԍ�	��ConresMainSeqTbl�ƕ��т𓯂��ɂ��Ă������ƁI�I
enum{
	CRSEQ_INIT,
	CRSEQ_FAST_TALK,
//	CRSEQ_DONCHOU_UP,
//	CRSEQ_DONCHOU_DOWN,
	CRSEQ_RESULT_CHANGE,
	CRSEQ_RESULT_FIRST_TALK,
	CRSEQ_RESULT_VISUAL,
	CRSEQ_RESULT_DANCE,
	CRSEQ_RESULT_ACTIN,
	CRSEQ_RANKING_ANNOUNCE,
	CRSEQ_RESULT_TALK,
	CRSEQ_END_TALK,
	CRSEQ_END,
};

//==============================================================================
//	CLACT�p�f�[�^
//==============================================================================
static	const TCATS_OAM_INIT ConresTcats = {
	CONRES_OAM_START_MAIN, CONRES_OAM_END_MAIN,
	CONRES_OAM_AFFINE_START_MAIN, CONRES_OAM_AFFINE_END_MAIN,
	CONRES_OAM_START_SUB, CONRES_OAM_END_SUB,
	CONRES_OAM_AFFINE_START_SUB, CONRES_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE ConresCcmm = {
	CONRES_CHAR_MAX,
	CONRES_CHAR_VRAMSIZE_MAIN,
	CONRES_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

static const TCATS_RESOURCE_NUM_LIST ConresResourceList = {
	CONRES_OAMRESOURCE_CHAR_MAX,
	CONRES_OAMRESOURCE_PLTT_MAX,
	CONRES_OAMRESOURCE_CELL_MAX,
	CONRES_OAMRESOURCE_CELLANM_MAX,
	CONRES_OAMRESOURCE_MCELL_MAX,
	CONRES_OAMRESOURCE_MCELLANM_MAX,
};

//==============================================================================
//	
//==============================================================================
///�J�����̃t���b�V���G�t�F�N�g�̃E�F�C�g�e�[�u��
ALIGN4 static const u16 CameraFlashEffectTbl[] = {
	20, 35, 8, 30,21,25,30,15,
};



//--------------------------------------------------------------
/**
 * @brief   �v���Z�X�֐��F������
 *
 * @param   proc		�v���Z�X�f�[�^
 * @param   seq			�V�[�P���X
 *
 * @retval  ������
 */
//--------------------------------------------------------------
PROC_RESULT ConresProc_Init( PROC * proc, int * seq )
{
	CONRES_PROC_WORK *rpw;

	sys_VBlankFuncChange(NULL, NULL);	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);
	GX_SetVisibleWnd(GX_WNDMASK_NONE);
	GXS_SetVisibleWnd(GX_WNDMASK_NONE);
	G2_BlendNone();
	G2S_BlendNone();

	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_CONRES, CONRES_ALLOC_SIZE);

	rpw = PROC_AllocWork(proc, sizeof(CONRES_PROC_WORK), HEAPID_CONRES );
	MI_CpuClear8(rpw, sizeof(CONRES_PROC_WORK));

//	simple_3DBGInit(HEAPID_CONRES);
	rpw->g3Dman = ADV_Contest_3D_Init(HEAPID_CONRES);
	
	rpw->consys = PROC_GetParentWork(proc);
	rpw->consys->class_proc = rpw;
	rpw->consys->class_flag = CON_CLASS_RESULT;
	rpw->sys.c_game = &rpw->consys->c_game;
	ConresSystemWorkInit(rpw);
	rpw->disp_mode = RESDISP_MODE_ANNOUNCE;
	
	//�p���b�g�t�F�[�h�V�X�e���쐬
	rpw->sys.pfd = PaletteFadeInit(HEAPID_CONRES);
	PaletteTrans_AutoSet(rpw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(rpw->sys.pfd, FADE_MAIN_BG, 0x200, HEAPID_CONRES);
	PaletteFadeWorkAllocSet(rpw->sys.pfd, FADE_SUB_BG, 0x200, HEAPID_CONRES);
	PaletteFadeWorkAllocSet(rpw->sys.pfd, FADE_MAIN_OBJ, CONTEST_MAIN_OBJPAL_SIZE, HEAPID_CONRES);
	PaletteFadeWorkAllocSet(rpw->sys.pfd, FADE_SUB_OBJ, 0x200, HEAPID_CONRES);
	
	rpw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_CONRES);

	initVramTransferManagerHeap(CONRES_VRAM_TRANSFER_TASK_NUM, HEAPID_CONRES);

	sys_KeyRepeatSpeedSet( 4, 8 );

//	rpw->dip = DINPUT_SystemInit(&rpw->sys);

	//VRAM���蓖�Đݒ�
	ConresSys_VramBankSet(rpw->sys.bgl);

	// �^�b�`�p�l���V�X�e��������
	InitTPSystem();
	InitTPNoBuff(4);

	// �{�^���p�t�H���g��ǂݍ���
	FontProc_LoadFont(FONT_BUTTON, HEAPID_CONRES);

	// ������ۑ�
//	SetConresWorkParameter(rpw, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

	//�A�N�^�[�V�X�e���쐬
	rpw->sys.csp=CATS_AllocMemory(HEAPID_CONRES);
	CATS_SystemInit(rpw->sys.csp,&ConresTcats,&ConresCcmm,CONRES_OAM_PLTT_MAX);
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	rpw->sys.crp=CATS_ResourceCreate(rpw->sys.csp);
	CATS_ClactSetInit(rpw->sys.csp, rpw->sys.crp, CONRES_ACTOR_MAX);
	CATS_ResourceManagerInit(rpw->sys.csp,rpw->sys.crp,&ConresResourceList);

	rpw->sys.soft_sprite = SoftSpriteInit(HEAPID_CONRES);
	ConresParticleInit();	//�p�[�e�B�N��������

	//���b�Z�[�W�}�l�[�W���쐬
	rpw->sys.conres_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_con_tally_dat, 
		HEAPID_CONRES);
	rpw->sys.wordset = WORDSET_Create(HEAPID_CONRES);
	rpw->sys.msg_buf = STRBUF_Create(CONRES_MESSAGE_BUF_SIZE, HEAPID_CONRES);	//������o�b�t�@�쐬
	
	//�t�H���gOAM�V�X�e���쐬
	rpw->sys.fontoam_sys = FONTOAM_SysInit(CONRES_FONTOAM_MAX_MAIN, HEAPID_CONRES);

	//�풓BG�Z�b�g
	ConresDefaultBGSet(rpw);
	ConresDefaultBGSet_Sub(rpw);

	//BMP�E�B���h�E�ǉ�
	ConresSys_DefaultBmpWinAdd(rpw);

	//�풓OBJ�Z�b�g
	ConresDefaultOBJSet(rpw);
	ConresDefaultOBJSet_Sub(rpw);

//	DINPUT_CreateBG(rpw->dip, DINPUT_TYPE_WALL, TRUE, NULL);
	
	//�|�P����(�\�t�g�E�F�A�X�v���C�g)����
	RT_SoftSpriteAddAll(rpw);

	WirelessIconEasy();	//�ʐM�A�C�R��
	
	// �P�x�ύX�Z�b�g
//	ChangeBrightnessRequest(
//		8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	WIPE_SYS_Start(WIPE_PATTERN_FMAS, WIPE_TYPE_SCREWIN, WIPE_TYPE_SCREWIN, WIPE_FADE_BLACK, 
		WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CONRES);

	rpw->update_tcb = TCB_Add(ConresUpdate, rpw, TCBPRI_CONRES_UPDATE);
	rpw->proc_mode = DPW_PROC_MODE_MAIN;

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	//�T�E���h�f�[�^���[�h(�R���e�X�g)
	Snd_DataSetByScene( SND_SCENE_CONTEST, SEQ_CON_TEST, 1 );
	//if(Snd_NowBgmNoGet() != SEQ_CON_TEST){
	//	Snd_Stop();
	//	Snd_BgmPlay(SEQ_CON_TEST);
	//}

	ConTool_MsgPrintFlagSet(rpw->consys->sio_flag);
	
	sys_VBlankFuncChange(ConresVBlank, rpw);
	//��Wipe��H�u�����N���g�p����̂ŁAWipe���I��������Z�b�g����悤�ɕύX
//	sys_HBlankIntrSet(ConresHBlank, rpw);
	rpw->vintr_tcb = VIntrTCB_Add(VBlankTCB_IntrTask, rpw, 10);
	
	Snd_SePlay(RSE_AUDIENCE);
	
#if 0	//�f�o�b�O�p�ɓ��_�Z�b�g
	{
		int i;
		for(i = 0; i < 4; i++){
			rpw->consys->c_game.score[i].bp = contest_rand(rpw->consys) % 100;
			rpw->consys->c_game.score[i].clip = contest_rand(rpw->consys) % 100;
			rpw->consys->c_game.score[i].dance = contest_rand(rpw->consys) % 100;
			rpw->consys->c_game.score[i].actin = contest_rand(rpw->consys) % 100;
		}
			rpw->consys->c_game.score[0].bp = 100;
			rpw->consys->c_game.score[0].clip = 100;
			rpw->consys->c_game.score[0].dance = 100;
			rpw->consys->c_game.score[0].actin = 100;
	}
#endif

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief   �v���Z�X�֐��F���C��
 *
 * @param   proc		�v���Z�X�f�[�^
 * @param   seq			�V�[�P���X
 *
 * @retval  ������
 */
//--------------------------------------------------------------
PROC_RESULT ConresProc_Main( PROC * proc, int * seq )
{
	CONRES_PROC_WORK * rpw  = PROC_GetWork( proc );
	int ret;
	enum{
		SEQ_IN,
		SEQ_MAIN,
		SEQ_OUT,
	};
	
	contest_rand(rpw->consys);
	
	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if(WIPE_SYS_EndCheck() == TRUE){
			sys_HBlankIntrSet(ConresHBlank, rpw);
			rpw->flash_eff = ADV_FlashEffectTaskSet(HEAPID_CONRES, rpw->sys.pfd, 
				CameraFlashEffectTbl, NELEMS(CameraFlashEffectTbl), ADV_FLASH_EFF_LOOP_ETERNITY,
				TCBPRI_CONRES_FLASH_EFF);
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		if(ConTool_ServerMineCheck(rpw->consys) == TRUE){
			ret = ConresMainSeqTbl[rpw->tbl_seq_no](rpw, &rpw->local);
			if(ret == CRRET_NEXT || ret == CRRET_SELECT_SEQ){
				if(ret == CRRET_NEXT){
					rpw->tbl_seq_no++;
				}
				else{
					rpw->tbl_seq_no = rpw->local.select_seq;
				}
				MI_CpuClear8(&rpw->local, sizeof(CONRES_LOCAL_WORK));
			}
			else if(ret == CRRET_END){
				*seq = SEQ_OUT;
				MI_CpuClear8(&rpw->local, sizeof(CONRES_LOCAL_WORK));
			//	WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
			//		WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CONRES);
				break;
			}
		}
		CO_TransmitCheckExe(&rpw->cow);
		CO_RecieveCheckExe(&rpw->cow, rpw);

		if(rpw->main_end == TRUE){
			*seq = SEQ_OUT;
			MI_CpuClear8(&rpw->local, sizeof(CONRES_LOCAL_WORK));
		//	WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
		//		WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CONRES);
		}
		break;

	case SEQ_OUT:
//		if(IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY)){
		if(WIPE_SYS_EndCheck() == TRUE){
			return PROC_RES_FINISH;
		}
		break;
	}

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �v���Z�X�֐��F�I��
 *
 * @param   proc		�v���Z�X�f�[�^
 * @param   seq			�V�[�P���X
 *
 * @retval  ������
 */
//--------------------------------------------------------------
PROC_RESULT ConresProc_End( PROC * proc, int * seq )
{
	CONRES_PROC_WORK * rpw = PROC_GetWork( proc );
	int i;

	Particle_SystemExitAll();
	
	//�풓OBJ�폜
	ConresDefaultOBJDel(rpw);
	ConresDefaultOBJDel_Sub(rpw);
	//�풓BG�폜
	ConresDefaultBGDel(rpw);
	ConresDefaultBGDel_Sub(rpw);

	//BMP�J��
	for(i = 0; i < CONRES_BMPWIN_MAX; i++){
		GF_BGL_BmpWinDel(&rpw->sys.win[i]);
	}

	//���C�����BG�폜
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(rpw->sys.bgl, CONRES_FRAME_WIN );
	GF_BGL_BGControlExit(rpw->sys.bgl, CONRES_FRAME_EFF );
	GF_BGL_BGControlExit(rpw->sys.bgl, CONRES_FRAME_BACKGROUND );
	//�T�u���BG�폜
	GF_BGL_VisibleSet(CONRES_FRAME_SUB_AUDIENCE, VISIBLE_OFF);
	GF_BGL_BGControlExit(rpw->sys.bgl, CONRES_FRAME_SUB_AUDIENCE);

	//�A�N�^�[�V�X�e���폜
	CATS_ResourceDestructor_S(rpw->sys.csp,rpw->sys.crp);
	CATS_FreeMemory(rpw->sys.csp);

	//Vram�]���}�l�[�W���[�폜
	DellVramTransferManager();

	//�\�t�g�E�F�A�X�v���C�g�폜
	RT_SoftSpriteDelAll(&rpw->sys);
	SoftSpriteEnd(rpw->sys.soft_sprite);

	//�t�H���gOAM�V�X�e���폜
	FONTOAM_SysDelete(rpw->sys.fontoam_sys);
	
	//�t�H���g�폜
	FontProc_UnloadFont(FONT_BUTTON);

	//�p���b�g�t�F�[�h�V�X�e���폜
	PaletteFadeWorkAllocFree(rpw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(rpw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(rpw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(rpw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(rpw->sys.pfd);

	//���b�Z�[�W�}�l�[�W���̍폜
	STRBUF_Delete(rpw->sys.msg_buf);
	WORDSET_Delete(rpw->sys.wordset);
	MSGMAN_Delete(rpw->sys.conres_msg);

	//BGL�J��
	sys_FreeMemoryEz(rpw->sys.bgl);

	TCB_Delete(rpw->update_tcb);
	TCB_Delete(rpw->vintr_tcb);
	
	//simple_3DBGExit();
	ADV_Contest_3D_Exit(rpw->g3Dman);

	StopTP();		//�^�b�`�p�l���̏I��

	PROC_FreeWork(proc);				// ���[�N�J��
	
	GX_SetVisibleWnd(GX_WNDMASK_NONE);
	GXS_SetVisibleWnd(GX_WNDMASK_NONE);
	
	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	sys_DeleteHeap(HEAPID_CONRES);

	ConTool_MsgPrintFlagReset();
	
	MI_CpuFill16((void*)HW_BG_PLTT, 0x7fff, 0x200);
	MI_CpuFill16((void*)HW_OBJ_PLTT, 0x7fff, 0x200);
	MI_CpuFill16((void*)HW_DB_BG_PLTT, 0x7fff, 0x200);
	MI_CpuFill16((void*)HW_DB_OBJ_PLTT, 0x7fff, 0x200);

	WirelessIconEasyEnd();

	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	Overlay_UnloadID(FS_OVERLAY_ID(ol_imageclip));
	
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK�֐�
 *
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ConresVBlank(void *work)
{
	CONRES_PROC_WORK *rpw = work;

	{//�E�B���h�E���W
		G2_SetWnd0Position(rpw->wnd0_x1, rpw->wnd0_y1, rpw->wnd0_x2, rpw->wnd0_y2);
		G2_SetWnd1Position(rpw->wnd1_x1, rpw->wnd1_y1, rpw->wnd1_x2, rpw->wnd1_y2);
	}
	
	SoftSpriteTextureTrans(rpw->sys.soft_sprite);

	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	PaletteFadeTrans(rpw->sys.pfd);
	
	GF_BGL_VBlankFunc(rpw->sys.bgl);
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief	HBLANK�֐�
 *
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ConresHBlank(void *work)
{
	CONRES_PROC_WORK *rpw = work;
	s32 v_count;
	
	if(rpw->disp_mode == RESDISP_MODE_RESULT){
		v_count = GX_GetVCount();
//		if(v_count == (RES_BMPWIN_TALK_POS_Y - 1) * 8){
		if(v_count >= (RES_BMPWIN_TALK_POS_Y - 1) * 8 && 
				v_count <= (RES_BMPWIN_TALK_POS_Y - 0) * 8){
			GF_BGL_PrioritySet(CONRES_FRAME_WIN, 0);
		}
		else if(v_count < (RES_BMPWIN_TALK_POS_Y - 1) * 8){
			//VBlankTCB_IntrTask�Ńv���C�I���e�B�͖߂��Ă���̂Œʏ�Ȃ炱���ł��K�v�͂Ȃ����A
			//�ʐM�̓d�g�󋵂Ŕ������鏈�����ׂɂ���ẮA�ǂ���V�u�����N���߂��Ă�����s�����
			//�قǂ̏����������������Ă��܂悤�Ȃ̂ŁA�ی��Ƃ��Ă����ł��v���C�I���e�B��
			//�߂����������Ă��� 2006.08.10(��)
			GF_BGL_PrioritySet(CONRES_FRAME_WIN, CONRES_BGPRI_WIN);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   VBlank�^�X�N�֐�(1/60�ŉ��܂�)
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VBlankTCB_IntrTask(TCB_PTR tcb, void *work)
{
	CONRES_PROC_WORK *rpw = work;
	
	if(rpw->disp_mode == RESDISP_MODE_RESULT){
		//H�u�����N�ŏグ�Ă����v���C�I���e�B��߂�
		GF_BGL_PrioritySet(CONRES_FRAME_WIN, CONRES_BGPRI_WIN);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����[�v�̍Ō�ɍs���V�X�e���֘A�̍X�V����
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		rpw
 */
//--------------------------------------------------------------
static void ConresUpdate(TCB_PTR tcb, void *work)
{
	CONRES_PROC_WORK *rpw = work;
	
	if(rpw->proc_mode == DPW_PROC_MODE_MAIN){
		SoftSpriteMain(rpw->sys.soft_sprite);
		BattleParticle_Main();
		CATS_Draw(rpw->sys.crp);
		CATS_UpdateTransfer();
		G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

	CommErrorCheck(HEAPID_CONRES, rpw->sys.bgl);
}

//--------------------------------------------------------------
/**
 * @brief   Vram�o���N�ݒ���s��
 *
 * @param   bgl		BGL�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresSys_VramBankSet(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();

	//VRAM�ݒ�
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
			GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAM�N���A
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//���C����ʃt���[���ݒ�
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M	�E�B���h�E
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
//				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
				CONRES_BGPRI_WIN, 0, 0, FALSE
			},
			///<FRAME2_M	�G�t�F�N�g
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
//				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				CONRES_BGPRI_EFF, 0, 0, FALSE
			},
			///<FRAME3_M	�w�i
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				CONRES_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, CONRES_FRAME_WIN, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, CONRES_FRAME_WIN );
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_WIN, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_WIN, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, CONRES_FRAME_EFF, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, CONRES_FRAME_EFF );
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, CONRES_FRAME_BACKGROUND, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, CONRES_FRAME_BACKGROUND );
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_BACKGROUND, GF_BGL_SCROLL_Y_SET, 0);

		G2_SetBG0Priority(CONRES_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//�T�u��ʃt���[���ݒ�
	{
		GF_BGL_BGCNT_HEADER SubBgCntDat[] = {
			///<FRAME0_S	�ϋq
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				CONRES_BGPRI_SUB_AUDIENCE, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, CONRES_FRAME_SUB_AUDIENCE, &SubBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, CONRES_FRAME_SUB_AUDIENCE );
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, CONRES_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_Y_SET, 0);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ����BMP�E�B���h�E��ݒ肷��
 *
 * @param   rpw		���ʔ��\�Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresSys_DefaultBmpWinAdd(CONRES_PROC_WORK *rpw)
{
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_TALK], CONRES_FRAME_WIN, 
		RES_BMPWIN_TALK_POS_X,RES_BMPWIN_TALK_POS_Y,
		RES_BMPWIN_TALK_SIZE_X,RES_BMPWIN_TALK_SIZE_Y, 
		RES_BMPWIN_TALK_COLOR, RES_BMPWIN_TALK_CGX_OFFSET);

	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_NICK_0], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_NICK, RES_BMPWIN_POS_Y_NICK + RES_BMPWIN_POS_Y_SPACE_NICK * 0, 
		RES_BMPWIN_NICK_SIZE_X, RES_BMPWIN_NICK_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_NICK_CGX_OFFSET_0);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_NICK_1], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_NICK, RES_BMPWIN_POS_Y_NICK + RES_BMPWIN_POS_Y_SPACE_NICK * 1, 
		RES_BMPWIN_NICK_SIZE_X, RES_BMPWIN_NICK_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_NICK_CGX_OFFSET_1);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_NICK_2], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_NICK, RES_BMPWIN_POS_Y_NICK + RES_BMPWIN_POS_Y_SPACE_NICK * 2, 
		RES_BMPWIN_NICK_SIZE_X, RES_BMPWIN_NICK_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_NICK_CGX_OFFSET_2);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_NICK_3], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_NICK, RES_BMPWIN_POS_Y_NICK + RES_BMPWIN_POS_Y_SPACE_NICK * 3, 
		RES_BMPWIN_NICK_SIZE_X, RES_BMPWIN_NICK_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_NICK_CGX_OFFSET_3);

	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_OYA_0], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_OYA, RES_BMPWIN_POS_Y_OYA + RES_BMPWIN_POS_Y_SPACE_OYA * 0, 
		RES_BMPWIN_OYA_SIZE_X, RES_BMPWIN_OYA_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_OYA_CGX_OFFSET_0);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_OYA_1], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_OYA, RES_BMPWIN_POS_Y_OYA + RES_BMPWIN_POS_Y_SPACE_OYA * 1, 
		RES_BMPWIN_OYA_SIZE_X, RES_BMPWIN_OYA_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_OYA_CGX_OFFSET_1);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_OYA_2], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_OYA, RES_BMPWIN_POS_Y_OYA + RES_BMPWIN_POS_Y_SPACE_OYA * 2, 
		RES_BMPWIN_OYA_SIZE_X, RES_BMPWIN_OYA_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_OYA_CGX_OFFSET_2);
	GF_BGL_BmpWinAdd(rpw->sys.bgl, &rpw->sys.win[CONRES_BMPWIN_OYA_3], CONRES_FRAME_WIN, 
		RES_BMPWIN_POS_X_OYA, RES_BMPWIN_POS_Y_OYA + RES_BMPWIN_POS_Y_SPACE_OYA * 3, 
		RES_BMPWIN_OYA_SIZE_X, RES_BMPWIN_OYA_SIZE_Y, 
		RES_BMPWIN_NAME_COLOR, RES_BMPWIN_OYA_CGX_OFFSET_3);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\����p�p�[�e�B�N��������
 */
//--------------------------------------------------------------
static void ConresParticleInit(void)
{
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	//�|�P�����Ŏg�p���镪���m��
	tex_key = NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key = NNS_GfdAllocPlttVram(0x20 * CLIENT_MAX, 0, 0);
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	tex_addrs = NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(pltt_key);
	OS_TPrintf("�|�P�����p�Ɋm�ۂ����e�N�X�`��Vram�̐擪�A�h���X��%d\n", tex_addrs);
	OS_TPrintf("�|�P�����p�Ɋm�ۂ����p���b�gVram�̐擪�A�h���X��%d\n", pltt_addrs);

	//�p�[�e�B�N���V�X�e�����[�N������
	Particle_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\����Ǘ����[�N�̏����p�����[�^���Z�b�g����
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresSystemWorkInit(CONRES_PROC_WORK *rpw)
{
	int i;
	
	GF_ASSERT(rpw->consys != NULL);
	
	for(i = 0; i < BREEDER_MAX; i++){
		rpw->r_game.breeder_sort[i] = BREEDER_MAX - 1 - i;	//�G���g���[��
	}
	
	ConresOrder_WorkInit(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\����Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultOBJSet(CONRES_PROC_WORK *rpw)
{
	RT_Announce_OBJSet(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\����Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultOBJDel(CONRES_PROC_WORK *rpw)
{
	RT_Result_OBJDel(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F���ʔ��\����Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultOBJSet_Sub(CONRES_PROC_WORK *rpw)
{
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F���ʔ��\����Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultOBJDel_Sub(CONRES_PROC_WORK *rpw)
{
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F���ʔ��\����Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultBGSet(CONRES_PROC_WORK *rpw)
{
	RT_Announce_BGSet(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F���ʔ��\����Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultBGDel(CONRES_PROC_WORK *rpw)
{
	RT_Result_BGDel(rpw);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F���ʔ��\����Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultBGSet_Sub(CONRES_PROC_WORK *rpw)
{
	//�L�����N�^
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_SUB_BG_NCGR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_CONRES);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL__SUB_BG_NSCR_BIN, rpw->sys.bgl, 
		CONRES_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_CONRES);

	//�p���b�g
	PaletteWorkSet_Arc(rpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_SUB_BG_NCLR, 
		HEAPID_CONRES, FADE_SUB_BG, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F���ʔ��\����Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   rpw		���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConresDefaultBGDel_Sub(CONRES_PROC_WORK *rpw)
{
}




//==============================================================================
//
//	�V�[�P���X
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F����������
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_Init(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	int i;
	
	switch(local->seq){
	case 0:
		RT_CalcPoint(rpw);
		
		{
			int victory_breeder;
			for(victory_breeder = 0; victory_breeder < BREEDER_MAX; victory_breeder++){
				if(rpw->consys->c_game.score[victory_breeder].final_ranking == 0){
					break;
				}
			}
			GF_ASSERT(victory_breeder != BREEDER_MAX);
			
			rpw->advance.victory_breeder = victory_breeder;
		}

		for(i = 0; i < BREEDER_MAX; i++){
			rpw->advance.ranking[i] = rpw->r_game.ranking[i];
		}
		
		for(i = 0; i < BREEDER_MAX; i++){
			rpw->r_game.score[i] = rpw->consys->c_game.score[i];
		}
		
		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_GAMEPARAM_UPDATE, &rpw->r_game) == TRUE){
			local->seq++;
		}
		break;
	case 2:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�ŏ��̃��b�Z�[�W�\��
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_FastTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = 0;
		rpw->advance.a_talk_bmpwin_not_close = 0;
		rpw->advance.a_talk_tagpara.mine_brd = rpw->r_game.breeder_sort[0];
		rpw->advance.a_talk_id = A_TALK_HOST_01;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�ǂ񂿂傤���グ��
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_DonchouUp(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_DONCHOU_UP, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			return CRRET_NEXT;
		}
		break;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F���ʔ��\��ʂɐ؂�ւ�
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ResultChange(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_RESULT_CHANGE, &rpw->r_game) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F���ʔ��\��ʂɐ؂�ւ���̍ŏ��̉�b
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ChangeFirstTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = TRUE;
		rpw->advance.a_talk_bmpwin_not_close = TRUE;
		rpw->advance.a_talk_id = A_TALK_HOST_06;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		local->work++;
		if(local->work > RESULT_ANNOUNCEMENT_WAIT){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�r�W���A������
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ResultVisual(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		switch(rpw->consys->c_game.mode){
		case CONMODE_GRAND:
		case CONMODE_ACTIVE:
		case CONMODE_CHARM:
		case CONMODE_VISUAL_PRACTICE:
		case CONMODE_VISUAL_TUTORIAL:
			break;
		default:
			return CRRET_NEXT;
		}

		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = TRUE;
		rpw->advance.a_talk_bmpwin_not_close = TRUE;
		rpw->advance.a_talk_id = A_TALK_HOST_02;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		rpw->advance.meter_type = CONGAME_VISUAL;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_METER_UPDATE, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 3:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 4:
		local->work++;
		if(local->work > RESULT_ANNOUNCEMENT_WAIT_VISUAL){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�_���X����
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ResultDance(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		switch(rpw->consys->c_game.mode){
		case CONMODE_GRAND:
		case CONMODE_ACTIVE:
		case CONMODE_DANCE_PRACTICE:
		case CONMODE_DANCE_TUTORIAL:
			break;
		default:
			return CRRET_NEXT;
		}
		
		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = TRUE;
		rpw->advance.a_talk_bmpwin_not_close = TRUE;
		rpw->advance.a_talk_tagpara.mine_brd = rpw->r_game.breeder_sort[0];
		rpw->advance.a_talk_tagpara.num = ConTool_EntryNoGet(rpw->r_game.breeder_sort[0]) + 1;
		rpw->advance.a_talk_id = A_TALK_HOST_03;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		rpw->advance.meter_type = CONGAME_DANCE;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_METER_UPDATE, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 3:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 4:
		local->work++;
		if(local->work > RESULT_ANNOUNCEMENT_WAIT_DANCE){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F���Z�͌���
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ResultActin(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		switch(rpw->consys->c_game.mode){
		case CONMODE_GRAND:
		case CONMODE_CHARM:
		case CONMODE_ACTIN_PRACTICE:
		case CONMODE_ACTIN_TUTORIAL:
			break;
		default:
			return CRRET_NEXT;
		}

		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = TRUE;
		rpw->advance.a_talk_bmpwin_not_close = TRUE;
		rpw->advance.a_talk_tagpara.mine_brd = rpw->r_game.breeder_sort[0];
		rpw->advance.a_talk_tagpara.num = ConTool_EntryNoGet(rpw->r_game.breeder_sort[0]) + 1;
		rpw->advance.a_talk_id = A_TALK_HOST_04;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		rpw->advance.meter_type = CONGAME_ACTIN;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_METER_UPDATE, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 3:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 4:
		local->work++;
		if(local->work > RESULT_ANNOUNCEMENT_WAIT_ACTIN){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F���ʔ��\
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_RankingAnnounce(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_RANKING_ANNOUNCE, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
		
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F���ʃ��b�Z�[�W�\��
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_ResultTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = TRUE;
		rpw->advance.a_talk_bmpwin_not_close = TRUE;
		rpw->advance.a_talk_tagpara.mine_brd = rpw->advance.victory_breeder;
		rpw->advance.a_talk_tagpara.num = ConTool_EntryNoGet(rpw->advance.victory_breeder) + 1;
		rpw->advance.a_talk_id = A_TALK_HOST_05;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	
	case 2:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_VICTORY_APPEAR, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 3:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
		
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�ǂ񂿂傤��������
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_DonchouDown(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_DONCHOU_DOWN, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			return CRRET_NEXT;
		}
		break;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�Ō�̃��b�Z�[�W�\��
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_EndTalk(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		rpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		rpw->advance.a_talk_bmpwin_not_open = 0;
		rpw->advance.a_talk_bmpwin_not_close = 0;
		rpw->advance.a_talk_tagpara.mine_brd = rpw->r_game.breeder_sort[0];
		rpw->advance.a_talk_id = A_TALK_CONRES_NULL;
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_TALK, &rpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return CRRET_NEXT;
	}
	return CRRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʔ��\�V�[�P���X�F�I������
 *
 * @param   rpw			���ʔ��\����Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ConresSeq_End(CONRES_PROC_WORK *rpw, CONRES_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_RESULT_FADEOUT, NULL) == TRUE){
			local->seq++;
		}
		break;
	case 1:
		//if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case 2:
		if(CO_OrderSet(&rpw->cow, rpw, RORDER_NO_CONRES_EXIT, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&rpw->cow) == 0){
		if(CO_AnswerCountCheck(&rpw->cow, rpw->consys->c_game.player_num, 
				rpw->consys->c_game.my_breeder_no, rpw->consys->c_game.server_no) == TRUE){
			return CRRET_END;
		}
		break;
	}
	return CRRET_CONTINUE;
}

