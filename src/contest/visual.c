//==============================================================================
/**
 * @file	visual.c
 * @brief	�r�W���A������
 * @author	matsuda
 * @date	2005.12.10(�y)
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

#include "con_tool.h"
#include "visual.h"
#include "visual_tool.h"
#include "visual_tcb_pri.h"
#include "visual_id.h"
#include "visual_order.h"
#include "adv_tool.h"

#include "system/window.h"
#include "system/wipe.h"
#include "savedata/config.h"
#include "communication/wm_icon.h"

#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);



//==============================================================================
//	�萔��`
//==============================================================================
///���݂̓�����
enum{
	VPW_PROC_MODE_INIT,		///<��������
	VPW_PROC_MODE_MAIN,		///<���C��
	VPW_PROC_MODE_ETC,		///<����ȊO
};

///Vram�]���}�l�[�W���[�^�X�N��
#define VISUAL_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
///BMP�E�B���h�ECGX�G���A�J�n�ʒu(�I�t�Z�b�g)
#define BMPWIN_CGX_START			(TALK_WIN_CGX_SIZ + VISUAL_TALKWIN_CGX_OFFSET)

#define BMPWIN_TALK_COLOR			(13)
#define BMPWIN_TALK_CGX_OFFSET		(BMPWIN_CGX_START)

//--------------------------------------------------------------
//	CL_ACT�p�̒萔��`
//--------------------------------------------------------------
///���C��	OAM�Ǘ��̈�E�J�n
#define VISUAL_OAM_START_MAIN			(BATTLE_OAM_START_MAIN)
///���C��	OAM�Ǘ��̈�E�I��
#define VISUAL_OAM_END_MAIN				(BATTLE_OAM_END_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�J�n
#define VISUAL_OAM_AFFINE_START_MAIN		(BATTLE_OAM_AFFINE_START_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�I��
#define VISUAL_OAM_AFFINE_END_MAIN		(BATTLE_OAM_AFFINE_END_MAIN)
///�T�u	OAM�Ǘ��̈�E�J�n
#define VISUAL_OAM_START_SUB				(BATTLE_OAM_START_SUB)
///�T�u	OAM�Ǘ��̈�E�I��
#define VISUAL_OAM_END_SUB				(BATTLE_OAM_END_SUB)
///�T�u �A�t�B���Ǘ��̈�E�J�n
#define VISUAL_OAM_AFFINE_START_SUB		(BATTLE_OAM_AFFINE_START_SUB)
///�T�u	�A�t�B���Ǘ��̈�E�I��
#define VISUAL_OAM_AFFINE_END_SUB		(BATTLE_OAM_AFFINE_END_SUB)

///�L�����}�l�[�W���F�L�����N�^ID�Ǘ���(���ʁ{�����)
#define VISUAL_CHAR_MAX					(BATTLE_CHAR_MAX)
///�L�����}�l�[�W���F���C����ʃT�C�Y(byte�P��)
#define VISUAL_CHAR_VRAMSIZE_MAIN		(BATTLE_CHAR_VRAMSIZE_MAIN)
///�L�����}�l�[�W���F�T�u��ʃT�C�Y(byte�P��)
#define VISUAL_CHAR_VRAMSIZE_SUB			(BATTLE_CHAR_VRAMSIZE_SUB)

///���C����ʁ{�T�u��ʂŎg�p����A�N�^�[����
#define VISUAL_ACTOR_MAX					(BATTLE_ACTOR_MAX)

///OBJ�Ŏg�p����p���b�g�{��(���ʁ{�����)
#define VISUAL_OAM_PLTT_MAX				(BATTLE_OAM_PLTT_MAX)

///�]�����[�h 3D = 0 main = 1 sub = 2 main/sub = 3
#define VISUAL_OAM_VRAM_TRANS			(BATTLE_OAM_VRAM_TRANS)

///OAM���\�[�X�F�L�����o�^�ő吔(���C����� + �T�u���)
#define VISUAL_OAMRESOURCE_CHAR_MAX		(BATTLE_OAMRESOURCE_CHAR_MAX)
///OAM���\�[�X�F�p���b�g�o�^�ő吔(���C����� + �T�u���)
#define VISUAL_OAMRESOURCE_PLTT_MAX		(BATTLE_OAMRESOURCE_PLTT_MAX)
///OAM���\�[�X�F�Z���o�^�ő吔
#define VISUAL_OAMRESOURCE_CELL_MAX		(BATTLE_OAMRESOURCE_CELL_MAX)
///OAM���\�[�X�F�Z���A�j���o�^�ő吔
#define VISUAL_OAMRESOURCE_CELLANM_MAX	(BATTLE_OAMRESOURCE_CELLANM_MAX)
///OAM���\�[�X�F�}���`�Z���o�^�ő吔
#define VISUAL_OAMRESOURCE_MCELL_MAX		(BATTLE_OAMRESOURCE_MCELL_MAX)
///OAM���\�[�X�F�}���`�Z���A�j���o�^�ő吔
#define VISUAL_OAMRESOURCE_MCELLANM_MAX	(BATTLE_OAMRESOURCE_MCELLANM_MAX)

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
///�ǂ񂿂傤�t�F�[�h�A�E�g�F�t�F�[�h���x
#define DFO_WAIT			(16)//(3)
///�ǂ񂿂傤�t�F�[�h�A�E�g�F�J�nEVY
#define DFO_START_EVY		(0)
///�ǂ񂿂傤�t�F�[�h�A�E�g�F�I��EVY
#define DFO_END_EVY			(-16)
///�ǂ񂿂傤�t�F�[�h�A�E�g�F�ύX��̐F
#define DFO_NEXT_RGB		(0x0000)

///�ǂ񂿂傤�t�F�[�h�C���F�t�F�[�h���x
#define DFI_WAIT			(2)
///�ǂ񂿂傤�t�F�[�h�C���F�J�nEVY
#define DFI_START_EVY		(DFO_END_EVY)
///�ǂ񂿂傤�t�F�[�h�C���F�I��EVY
#define DFI_END_EVY			(4)
///�ǂ񂿂傤�t�F�[�h�C���F�ύX��̐F
#define DFI_NEXT_RGB		(DFO_NEXT_RGB)

///�ǂ񂿂傤�t�F�[�h�C���Ō�F�t�F�[�h���x
#define DFE_WAIT			(1)
///�ǂ񂿂傤�t�F�[�h�C���Ō�F�J�nEVY
#define DFE_START_EVY		(DFI_END_EVY)
///�ǂ񂿂傤�t�F�[�h�C���Ō�F�I��EVY
#define DFE_END_EVY			(0)
///�ǂ񂿂傤�t�F�[�h�C���Ō�F�ύX��̐F
#define DFE_NEXT_RGB		(DFO_NEXT_RGB)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�r�W���A������J�n���̍ŏ��̃t�F�[�h�C���̃E�F�C�g
#define VISUAL_START_FADEIN_WAIT		(6)


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void VisualVBlank(void *work);
static void VisualUpdate(TCB_PTR tcb, void *work);
static void VisualSys_VramBankSet(GF_BGL_INI *bgl);
static void VisualSys_DefaultBmpWinAdd(VISUAL_PROC_WORK *vpw);
static void VisualSystemWorkInit(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJSet(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJDel(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJSet_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultOBJDel_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGSet(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGDel(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGSet_Sub(VISUAL_PROC_WORK *vpw);
static void VisualDefaultBGDel_Sub(VISUAL_PROC_WORK *vpw);
static int VisualSeq_Init(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_JudgeFastTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_EndTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_End(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static void VisualParticleInit(void);
static int VisualSeq_PokeSelect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_Appear(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_TrainerIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_IntroduceTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_AppearEffect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_TrainerOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_Advance(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_AudienceEvaluate(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_PokeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_NextPoke(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouDown(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouFadeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_FullFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);
static int VisualSeq_DonchouEffectUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local);


//==============================================================================
//	�f�[�^
//==============================================================================

//==============================================================================
//	�V�[�P���X�e�[�u��
//==============================================================================
///VisualMainSeqTbl�̖߂�l�Ƃ��Ďg�p
enum{
	VSRET_CONTINUE,		///<����ێ�
	VSRET_NEXT,			///<���̃V�[�P���X��
	VSRET_SELECT_SEQ,	///<select_seq���[�N�ɓ����Ă���V�[�P���X�֐i��
	VSRET_END,			///<�I��
};

///�r�W���A�����僁�C���֐��̃V�[�P���X�e�[�u��
static int (* const VisualMainSeqTbl[])(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local) = {
	VisualSeq_Init,
	VisualSeq_JudgeFastTalk,
	VisualSeq_PokeSelect,
	
	VisualSeq_DonchouFadeOut,
	
	VisualSeq_IntroduceTalk,

	VisualSeq_Appear,
//	VisualSeq_DonchouFadeIn,
	VisualSeq_DonchouEffectUp,
//	VisualSeq_FullFadeIn,
	
//	VisualSeq_DonchouUp,

//	VisualSeq_TrainerIn,
//	VisualSeq_AppearEffect,
//	VisualSeq_TrainerOut,
//	VisualSeq_Advance,
	VisualSeq_AudienceEvaluate,
//	VisualSeq_PokeOut,
//	VisualSeq_DonchouDown,
	VisualSeq_NextPoke,
	VisualSeq_EndTalk,
	VisualSeq_End,
};
///VisualMainSeqTbl�̃V�[�P���X�ԍ�	��VisualMainSeqTbl�ƕ��т𓯂��ɂ��Ă������ƁI�I
enum{
	VSEQ_INIT,
	VSEQ_JUDGE_FAST_TALK,
	VSEQ_POKE_SELECT,
	
	VSEQ_DONCHOU_FADEOUT,

	VSEQ_INTRODUCE_TALK,

	VSEQ_APPEAR,
//	VSEQ_DONCHOU_FADEIN,
	VSEQ_DONCHOU_EFFECT_UP,
//	VSEQ_FULL_FADEIN,
	
//	VSEQ_DONCHOU_UP,

//	VSEQ_TRAINER_IN,
//	VSEQ_APPEAR_EFFECT,
//	VSEQ_TRAINER_OUT,
//	VSEQ_ADVANCE,
	VSEQ_AUDIENCE_EVALUATE,
//	VSEQ_POKE_OUT,
//	VSEQ_DONCHOU_DOWN,
	VSEQ_NEXT_POKE,
	VSEQ_END_TALK,
	VSEQ_END,
};

//==============================================================================
//	CLACT�p�f�[�^
//==============================================================================
static	const TCATS_OAM_INIT VisualTcats = {
	VISUAL_OAM_START_MAIN, VISUAL_OAM_END_MAIN,
	VISUAL_OAM_AFFINE_START_MAIN, VISUAL_OAM_AFFINE_END_MAIN,
	VISUAL_OAM_START_SUB, VISUAL_OAM_END_SUB,
	VISUAL_OAM_AFFINE_START_SUB, VISUAL_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE VisualCcmm = {
	VISUAL_CHAR_MAX,
	VISUAL_CHAR_VRAMSIZE_MAIN,
	VISUAL_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

static const TCATS_RESOURCE_NUM_LIST VisualResourceList = {
	VISUAL_OAMRESOURCE_CHAR_MAX,
	VISUAL_OAMRESOURCE_PLTT_MAX,
	VISUAL_OAMRESOURCE_CELL_MAX,
	VISUAL_OAMRESOURCE_CELLANM_MAX,
	VISUAL_OAMRESOURCE_MCELL_MAX,
	VISUAL_OAMRESOURCE_MCELLANM_MAX,
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
PROC_RESULT VisualProc_Init( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK *vpw;

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

	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_VISUAL, VISUAL_ALLOC_SIZE);

	vpw = PROC_AllocWork(proc, sizeof(VISUAL_PROC_WORK), HEAPID_VISUAL );
	MI_CpuClear8(vpw, sizeof(VISUAL_PROC_WORK));

//	simple_3DBGInit(HEAPID_VISUAL);
	vpw->g3Dman = ADV_Contest_3D_Init(HEAPID_VISUAL);

	vpw->consys = PROC_GetParentWork(proc);
	vpw->consys->class_proc = vpw;
	vpw->consys->class_flag = CON_CLASS_VISUAL;
	vpw->sys.c_game = &vpw->consys->c_game;
	VisualSystemWorkInit(vpw);
	
	//�p���b�g�t�F�[�h�V�X�e���쐬
	vpw->sys.pfd = PaletteFadeInit(HEAPID_VISUAL);
	PaletteTrans_AutoSet(vpw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_MAIN_BG, 0x200, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_SUB_BG, 0x200, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_MAIN_OBJ, CONTEST_MAIN_OBJPAL_SIZE, HEAPID_VISUAL);
	PaletteFadeWorkAllocSet(vpw->sys.pfd, FADE_SUB_OBJ, 0x200, HEAPID_VISUAL);
	
	vpw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_VISUAL);

	initVramTransferManagerHeap(VISUAL_VRAM_TRANSFER_TASK_NUM, HEAPID_VISUAL);

	sys_KeyRepeatSpeedSet( 4, 8 );

//	vpw->aip = AINPUT_SystemInit(&vpw->sys);

	//VRAM���蓖�Đݒ�
	VisualSys_VramBankSet(vpw->sys.bgl);

	// �^�b�`�p�l���V�X�e��������
	InitTPSystem();
	InitTPNoBuff(4);

	// �{�^���p�t�H���g��ǂݍ���
	FontProc_LoadFont(FONT_BUTTON, HEAPID_VISUAL);

	// ������ۑ�
//	SetVisualWorkParameter(vpw, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

	//�A�N�^�[�V�X�e���쐬
	vpw->sys.csp=CATS_AllocMemory(HEAPID_VISUAL);
	CATS_SystemInit(vpw->sys.csp,&VisualTcats,&VisualCcmm,VISUAL_OAM_PLTT_MAX);
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	vpw->sys.crp=CATS_ResourceCreate(vpw->sys.csp);
	CATS_ClactSetInit(vpw->sys.csp, vpw->sys.crp, VISUAL_ACTOR_MAX);
	CATS_ResourceManagerInit(vpw->sys.csp,vpw->sys.crp,&VisualResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(vpw->sys.csp), 0, VISUAL_SUB_ACTOR_DISTANCE);

	vpw->sys.soft_sprite = SoftSpriteInit(HEAPID_VISUAL);
	VisualParticleInit();	//�p�[�e�B�N��������

	//���b�Z�[�W�}�l�[�W���쐬
	vpw->sys.visual_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_visual_dat, 
		HEAPID_VISUAL);
	vpw->sys.wordset = WORDSET_Create(HEAPID_VISUAL);
	vpw->sys.msg_buf = STRBUF_Create(VISUAL_MESSAGE_BUF_SIZE, HEAPID_VISUAL);
	
	//�풓BG�Z�b�g
	VisualDefaultBGSet(vpw);
	VisualDefaultBGSet_Sub(vpw);

	//BMP�E�B���h�E�ǉ�
	VisualSys_DefaultBmpWinAdd(vpw);

	//�풓OBJ�Z�b�g
	VisualDefaultOBJSet(vpw);
	VisualDefaultOBJSet_Sub(vpw);
	
	//�]���p���b�g��^�����ɂ���(�o�b�O�O���E���h�͏���)
	PaletteWork_Clear(vpw->sys.pfd, FADE_MAIN_BG, FADEBUF_TRANS, 0x7fff, 1, 16*16);
	PaletteWork_Clear(vpw->sys.pfd, FADE_SUB_BG, FADEBUF_TRANS, 0x7fff, 1, 16*16);
	PaletteWork_Clear(vpw->sys.pfd, FADE_MAIN_OBJ, FADEBUF_TRANS, 0x7fff, 0, 
		CONTEST_MAIN_OBJPAL_COLOR_NUM);
	PaletteWork_Clear(vpw->sys.pfd, FADE_SUB_OBJ, FADEBUF_TRANS, 0x7fff, 0, 16*16);
	
	//�|�P����(�\�t�g�E�F�A�X�v���C�g)����
	//VT_SoftSpriteAddAll(&vpw->sys);

	WirelessIconEasy();	//�ʐM�A�C�R��
	
	// �P�x�ύX�Z�b�g
//	ChangeBrightnessRequest(
//		8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	WIPE_SYS_Start(WIPE_PATTERN_FMAS, WIPE_TYPE_DOORIN, WIPE_TYPE_DOORIN, WIPE_FADE_BLACK, 
		WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);

	vpw->update_tcb = TCB_Add(VisualUpdate, vpw, TCBPRI_VISUAL_UPDATE);
	vpw->proc_mode = VPW_PROC_MODE_MAIN;

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	//�T�E���h�f�[�^���[�h(�R���e�X�g)
	Snd_SceneSet( SND_SCENE_DUMMY );		//�K�����[�h�����悤�ɃN���A����I
	Snd_DataSetByScene( SND_SCENE_CONTEST, SEQ_CON_TEST, 1 );
	//Snd_Stop();
	//Snd_BgmPlay(SEQ_CON_TEST);

	ConTool_MsgPrintFlagSet(vpw->consys->sio_flag);
	
	sys_VBlankFuncChange(VisualVBlank, vpw);
	
	Snd_SePlay(VSE_DOOR_OPEN);
	
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
PROC_RESULT VisualProc_Main( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK * vpw  = PROC_GetWork( proc );
	int ret;
	enum{
		SEQ_IN,
		SEQ_MAIN,
		SEQ_OUT,
	};
	
	contest_rand(vpw->consys);
	
	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if(WIPE_SYS_EndCheck() == TRUE){
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_MAIN_BG, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_SUB_BG, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_MAIN_OBJ, CONTEST_MAIN_OBJPAL_FADEBIT, 
				VISUAL_START_FADEIN_WAIT, EVY_MAX, 0, 0x7fff);
			PaletteFadeReq(vpw->sys.pfd, PF_BIT_SUB_OBJ, 0xffff, VISUAL_START_FADEIN_WAIT,
				EVY_MAX, 0, 0x7fff);
			
			Snd_SePlay(VSE_AUDIENCE);
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		if(ConTool_ServerMineCheck(vpw->consys) == TRUE){
			ret = VisualMainSeqTbl[vpw->tbl_seq_no](vpw, &vpw->local);
			if(ret == VSRET_NEXT || ret == VSRET_SELECT_SEQ){
				if(ret == VSRET_NEXT){
					vpw->tbl_seq_no++;
				}
				else{
					vpw->tbl_seq_no = vpw->local.select_seq;
				}
				MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
			}
			else if(ret == VSRET_END){
				*seq = SEQ_OUT;
				MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_HOLEOUT, WIPE_TYPE_TUNNELOUT_TOP,
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);
				break;
			}
		}
		
		CO_TransmitCheckExe(&vpw->cow);
		CO_RecieveCheckExe(&vpw->cow, vpw);

		if(vpw->main_end == TRUE){
			*seq = SEQ_OUT;
			MI_CpuClear8(&vpw->local, sizeof(VISUAL_LOCAL_WORK));
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_HOLEOUT, WIPE_TYPE_TUNNELOUT_TOP,
				WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_VISUAL);
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
PROC_RESULT VisualProc_End( PROC * proc, int * seq )
{
	VISUAL_PROC_WORK * vpw = PROC_GetWork( proc );
	int i;

	Particle_SystemExitAll();

	//�풓OBJ�폜
	VisualDefaultOBJDel(vpw);
	VisualDefaultOBJDel_Sub(vpw);
	//�풓BG�폜
	VisualDefaultBGDel(vpw);
	VisualDefaultBGDel_Sub(vpw);

	//BMP�J��
	for(i = 0; i < VISUAL_BMPWIN_MAX; i++){
		GF_BGL_BmpWinDel(&vpw->sys.win[i]);
	}

	//���C�����BG�폜
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_WIN );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_EFF );
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_BACKGROUND );
	//�T�u���BG�폜
	GF_BGL_VisibleSet(VISUAL_FRAME_SUB_AUDIENCE, VISIBLE_OFF);
	GF_BGL_BGControlExit(vpw->sys.bgl, VISUAL_FRAME_SUB_AUDIENCE);

	//�A�N�^�[�V�X�e���폜
	CATS_ResourceDestructor_S(vpw->sys.csp,vpw->sys.crp);
	CATS_FreeMemory(vpw->sys.csp);

	//Vram�]���}�l�[�W���[�폜
	DellVramTransferManager();

	//�C���[�W�N���b�v�폜
	for(i = 0; i < BREEDER_MAX; i++){
		if(vpw->imcwork[i].imc_ptr != NULL){
			IMC_PlayerEnd(vpw->imcwork[i].imc_ptr);
		}
	}

	//�\�t�g�E�F�A�X�v���C�g�폜
	VT_SoftSpriteDelAll(&vpw->sys);
	VT_TrainerDel(vpw);
	SoftSpriteEnd(vpw->sys.soft_sprite);

	//���b�Z�[�W�}�l�[�W���̍폜
//	MSGMAN_Delete(vpw->fight_msg);

	//�t�H���g�폜
	FontProc_UnloadFont(FONT_BUTTON);

	//�p���b�g�t�F�[�h�V�X�e���폜
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(vpw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(vpw->sys.pfd);

	//���b�Z�[�W�}�l�[�W���̍폜
	WORDSET_Delete(vpw->sys.wordset);
	STRBUF_Delete(vpw->sys.msg_buf);
	MSGMAN_Delete(vpw->sys.visual_msg);

	//BGL�J��
	sys_FreeMemoryEz(vpw->sys.bgl);

	TCB_Delete(vpw->update_tcb);

//	simple_3DBGExit();
	ADV_Contest_3D_Exit(vpw->g3Dman);

	StopTP();		//�^�b�`�p�l���̏I��

	PROC_FreeWork(proc);				// ���[�N�J��
	
	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	sys_DeleteHeap(HEAPID_VISUAL);

	ConTool_MsgPrintFlagReset();

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
static void VisualVBlank(void *work)
{
	VISUAL_PROC_WORK *vpw = work;

	{//�E�B���h�E���W
		G2_SetWnd0Position(vpw->wnd0_x1, vpw->wnd0_y1, vpw->wnd0_x2, vpw->wnd0_y2);
		G2_SetWnd1Position(vpw->wnd1_x1, vpw->wnd1_y1, vpw->wnd1_x2, vpw->wnd1_y2);
	}
	
	SoftSpriteTextureTrans(vpw->sys.soft_sprite);
	{
		int i;
		for(i = 0; i < BREEDER_MAX; i++){
			if(vpw->imcwork[i].imc_ptr != NULL){
				IMC_PlayerVblank(vpw->imcwork[i].imc_ptr);
			}
		}
	}

	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	PaletteFadeTrans(vpw->sys.pfd);

	GF_BGL_VBlankFunc(vpw->sys.bgl);
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����[�v�̍Ō�ɍs���V�X�e���֘A�̍X�V����
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		vpw
 */
//--------------------------------------------------------------
static void VisualUpdate(TCB_PTR tcb, void *work)
{
	VISUAL_PROC_WORK *vpw = work;
	
	if(vpw->proc_mode == VPW_PROC_MODE_MAIN){
		SoftSpriteMain(vpw->sys.soft_sprite);	//�g���[�i�[�p�Ɍv�Z�K�v
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				if(vpw->imcwork[i].imc_ptr != NULL){
					IMC_PlayerMain(vpw->imcwork[i].imc_ptr);
				}
			}
		}
		BattleParticle_Main();
		CATS_Draw(vpw->sys.crp);
		CATS_UpdateTransfer();
		G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

	CommErrorCheck(HEAPID_VISUAL, vpw->sys.bgl);
}

//--------------------------------------------------------------
/**
 * @brief   Vram�o���N�ݒ���s��
 *
 * @param   bgl		BGL�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualSys_VramBankSet(GF_BGL_INI *bgl)
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
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_WIN, 0, 0, FALSE
			},
			///<FRAME2_M	�G�t�F�N�g
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_EFF, 0, 0, FALSE
			},
			///<FRAME3_M	�w�i
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_SUB_AUDIENCE, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_WIN, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_WIN );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_WIN, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_WIN, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_EFF, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_EFF );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_BACKGROUND, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_BACKGROUND );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_BACKGROUND, GF_BGL_SCROLL_Y_SET, 0);

		G2_SetBG0Priority(VISUAL_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//�T�u��ʃt���[���ݒ�
	{
		GF_BGL_BGCNT_HEADER SubBgCntDat[] = {
			///<FRAME0_S	�ϋq
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				VISUAL_BGPRI_SUB_AUDIENCE, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, &SubBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, VISUAL_FRAME_SUB_AUDIENCE );
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, VISUAL_FRAME_SUB_AUDIENCE, GF_BGL_SCROLL_Y_SET, 0);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ����BMP�E�B���h�E��ݒ肷��
 *
 * @param   vpw		�r�W���A���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualSys_DefaultBmpWinAdd(VISUAL_PROC_WORK *vpw)
{
	GF_BGL_BmpWinAdd(vpw->sys.bgl, &vpw->sys.win[VISUAL_BMPWIN_TALK], VISUAL_FRAME_WIN, 
		0x02,0x13,27,4, BMPWIN_TALK_COLOR, BMPWIN_TALK_CGX_OFFSET);
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������p�p�[�e�B�N��������
 */
//--------------------------------------------------------------
static void VisualParticleInit(void)
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
 * @brief   �r�W���A������Ǘ����[�N�̏����p�����[�^���Z�b�g����
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualSystemWorkInit(VISUAL_PROC_WORK *vpw)
{
	int i;
	
	GF_ASSERT(vpw->consys != NULL);
	
	for(i = 0; i < BREEDER_MAX; i++){
		vpw->v_game.breeder_sort[i] = BREEDER_MAX - 1 - i;
	}

	VisualOrder_WorkInit(vpw);
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultOBJSet(VISUAL_PROC_WORK *vpw)
{
	//�풓OBJ�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(vpw->sys.pfd, FADE_MAIN_OBJ, vpw->sys.csp, vpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_VISUAL_OBJ_NCLR, 0, 
		VISUAL_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, V_PLTTID_OBJ_COMMON);
	
	VT_AudienceHeartResourceLoad(vpw->sys.csp, vpw->sys.crp);
	
	ADV_FlowerResourceLoad(vpw->sys.csp, vpw->sys.crp, vpw->sys.pfd,
		V_CHARID_FLOWER, -1, V_CELLID_FLOWER, V_CELLANMID_FLOWER);
	ADV_FlowerActorAddAll(&vpw->sys.flower, vpw->sys.csp, vpw->sys.crp, 
		V_CHARID_FLOWER, V_PLTTID_OBJ_COMMON, V_CELLID_FLOWER, V_CELLANMID_FLOWER, 
		PALOFS_FLOWER, V_FLOWER_SOFTPRI, V_FLOWER_BGPRI, TCBPRI_VISUAL_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A������Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultOBJDel(VISUAL_PROC_WORK *vpw)
{
	VT_AudienceHeartResourceFree(vpw->sys.crp);
	
	ADV_FlowerActorDelAll(&vpw->sys.flower);
	ADV_FlowerResourceFree(vpw->sys.crp, V_CHARID_FLOWER, -1, V_CELLID_FLOWER, V_CELLANMID_FLOWER);
	
	//�풓OBJ�p���b�g�������
	CATS_FreeResourcePltt(vpw->sys.crp, V_PLTTID_OBJ_COMMON);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F�r�W���A������Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultOBJSet_Sub(VISUAL_PROC_WORK *vpw)
{
	//�풓OBJ�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(vpw->sys.pfd, FADE_SUB_OBJ, vpw->sys.csp, vpw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_VISUAL_SUB_OBJ_NCLR, 0, 
		VISUAL_SUB_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DSUB, V_PLTTID_OBJ_COMMON_SUB);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F�r�W���A������Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultOBJDel_Sub(VISUAL_PROC_WORK *vpw)
{
	//�풓OBJ�p���b�g�������
	CATS_FreeResourcePltt(vpw->sys.crp, V_PLTTID_OBJ_COMMON_SUB);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F�r�W���A������Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultBGSet(VISUAL_PROC_WORK *vpw)
{
	WINTYPE win_type;
	
	//�L�����N�^
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_BG_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_BACKGROUND, 0, 0, 1, HEAPID_VISUAL);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_BG_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_BACKGROUND, 0, 0, 1, HEAPID_VISUAL);
	GF_BGL_ScrClear(vpw->sys.bgl, VISUAL_FRAME_WIN);

	//�p���b�g
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_BG_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0, 0);
	//�t�H���g�p�p���b�g
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CON_BG_FONT_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, BMPWIN_TALK_COLOR * 16);


	//��b�E�B���h�E
	win_type = CONFIG_GetWindowType(vpw->consys->config);
	TalkWinGraphicSet(vpw->sys.bgl, VISUAL_FRAME_WIN, VISUAL_TALKWIN_CGX_OFFSET, 
		VISUAL_TALKWIN_BACK_COLOR, win_type, HEAPID_VISUAL);
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, VISUAL_TALKWIN_PALNO * 16);

	//�ǂ񂿂傤
	ArcUtil_BgCharSet(ARC_CONTEST_BG, DONTYOU_ANIM_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_EFF, 0, 0, 1, HEAPID_VISUAL);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL_DONCHOU_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_EFF, 0, 0, 1, HEAPID_VISUAL);
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, DONTYOU_ANIM_NCLR, 
		HEAPID_VISUAL, FADE_MAIN_BG, 0x20, DONTYOU_PALNO * 16);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F�r�W���A������Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultBGDel(VISUAL_PROC_WORK *vpw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F�r�W���A������Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultBGSet_Sub(VISUAL_PROC_WORK *vpw)
{
	//�L�����N�^
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_VISUAL_SUB_BG_NCGR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_VISUAL);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_VISUAL__SUB_BG_NSCR_BIN, vpw->sys.bgl, 
		VISUAL_FRAME_SUB_AUDIENCE, 0, 0, 1, HEAPID_VISUAL);

	//�p���b�g
	PaletteWorkSet_Arc(vpw->sys.pfd, ARC_CONTEST_BG, CONTEST_VISUAL_SUB_BG_NCLR, 
		HEAPID_VISUAL, FADE_SUB_BG, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F�r�W���A������Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   vpw		�r�W���A������Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VisualDefaultBGDel_Sub(VISUAL_PROC_WORK *vpw)
{
}




//==============================================================================
//
//	�V�[�P���X
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F����������
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_Init(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(PaletteFadeCheck(vpw->sys.pfd) != 0){
			break;
		}
		
		//�N���b�v�̓��_�v�Z
		ADV_ClipScoreCalc(vpw->consys, HEAPID_VISUAL);
		//BP�̓��_�v�Z
		ADV_BPScoreCalc(vpw->consys);
		
		//VT_SoftSpriteAddAll(&vpw->sys);
//		if(CO_OrderSet(vpw, AORDER_NO_POKEMON_SPRITE_ADD_ALL, NULL) == TRUE){
			local->seq++;
//		}
		break;
	default:
//		if(CO_RequestBitNumCheck(vpw) == 0){
//		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
//		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�R���̍ŏ��̉�b��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_JudgeFastTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	
	switch(local->seq){
	case 0:
		if(ConTool_PracticeModeCheck(vpw->consys) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_PRACTICE_01;
		}
		else{
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_01;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�|�P�����I��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_PokeSelect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	
	switch(local->seq){
	case 0:
		vpw->advance.now_breeder = vpw->v_game.breeder_sort[vpw->v_game.breeder_end_count];
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_SAMPLE, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ǂ񂿂傤���t�F�[�h�A�E�g
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouFadeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFO_START_EVY;
		vpw->advance.fade_end_evy = DFO_END_EVY;
		vpw->advance.fade_wait = DFO_WAIT;
		vpw->advance.fade_next_rgb = DFO_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ǂ񂿂傤���t�F�[�h�C��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFI_START_EVY;
		vpw->advance.fade_end_evy = DFI_END_EVY;
		vpw->advance.fade_wait = DFI_WAIT;
		vpw->advance.fade_next_rgb = DFI_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F���S�ɖ��邭
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_FullFadeIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.fade_start_evy = DFE_START_EVY;
		vpw->advance.fade_end_evy = DFE_END_EVY;
		vpw->advance.fade_wait = DFE_WAIT;
		vpw->advance.fade_next_rgb = DFE_NEXT_RGB;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_FADE_INOUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ǂ񂿂傤���G�t�F�N�g�㏸
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouEffectUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_EFFECT_UP, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�|�P�����o��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_Appear(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_APPEAR, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ǂ񂿂傤�グ��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouUp(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_UP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�g���[�i�[�o��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_TrainerIn(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TRAINER_IN, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�Љ�b�Z�[�W
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_IntroduceTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		switch(vpw->v_game.breeder_end_count){
		case 0:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_02;
			break;
		case 1:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_03;
			break;
		case 2:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_04;
			break;
		default:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_05;
			break;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		vpw->advance.a_talk_tagpara.mine_brd = vpw->advance.now_breeder;
		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�|�P�����o��G�t�F�N�g
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_AppearEffect(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_APPEAR_EFFECT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�g���[�i�[�ޏ�
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_TrainerOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TRAINER_OUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�|�P�����O�i
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_Advance(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_ADVANCE, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ϋq�]��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_AudienceEvaluate(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	enum{
		SEQ_INIT,
	#if 1
		SEQ_ALL_HEART,
		SEQ_ALL_HEART_WAIT,
	#else
		SEQ_BP_TALK,
		SEQ_BP_TALK_WAIT,
		SEQ_BP_HEART,
		SEQ_BP_HEART_WAIT,
		SEQ_CLIP_TALK,
		SEQ_CLIP_TALK_WAIT,
		SEQ_CLIP_HEART,
		SEQ_CLIP_HEART_WAIT,
	#endif
		SEQ_END,
	};
	
	switch(local->seq){
	case SEQ_INIT:
		vpw->advance.evaluate_heart_num_bp = 
			ConTool_HeartNumGet_BP(vpw->consys, vpw->advance.now_breeder);
		vpw->advance.evaluate_heart_num_clip = 
			ConTool_HeartNumGet_Clip(vpw->consys, vpw->advance.now_breeder);
		local->seq++;
		//break;

#if 1
	case SEQ_ALL_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_ALL, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_ALL_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

#else
	case SEQ_BP_TALK:
//		vpw->advance.a_talk_id = VT_A_TalkIDGet_BPAppeal(vpw->consys->c_game.type);
		vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_BP_TALK_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			local->seq++;
		}
		break;
	case SEQ_BP_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_BP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_BP_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case SEQ_CLIP_TALK:
//		vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_13;
		vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_CLIP_TALK_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			local->seq++;
		}
		break;
	case SEQ_CLIP_HEART:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_AUDIENCE_EVALUATE_CLIP, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case SEQ_CLIP_HEART_WAIT:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
#endif

	default:
		return VSRET_NEXT;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�|�P�����ޏ�
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_PokeOut(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(vpw->v_game.breeder_end_count + 1 == BREEDER_MAX){
			local->select_seq = VSEQ_NEXT_POKE;
			return VSRET_SELECT_SEQ;
		}
		local->seq++;
		break;
	case 1:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_POKE_OUT, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�ǂ񂿂傤������
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_DonchouDown(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_DONCHOU_DOWN, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F���̃|�P�����֐i�ޑO�̌㏈��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_NextPoke(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->v_game.breeder_end_count++;
		local->seq++;
		break;
	default:
		if(vpw->v_game.breeder_end_count >= BREEDER_MAX){
			return VSRET_NEXT;
		}
		local->select_seq = VSEQ_POKE_SELECT;
		return VSRET_SELECT_SEQ;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�r�W���A��������I�����鎞�̃��b�Z�[�W�\��
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_EndTalk(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		vpw->advance.se_id = VSE_AUDIENCE;
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_VISUAL_FINISH, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
		
	case 2:
		switch(vpw->consys->c_game.mode){
		case CONMODE_GRAND:
			vpw->advance.a_talk_id = A_TALK_VISUAL_HOST_06;
			break;
		default:
			vpw->advance.a_talk_id = A_TALK_VISUAL_NULL;
			break;
		}
		vpw->advance.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		vpw->advance.a_talk_bmpwin_not_close = 0;
		local->seq++;
		//break;
	case 3:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_TALK, &vpw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_NEXT;
		}
		break;
	}
	return VSRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   �r�W���A���V�[�P���X�F�I������
 *
 * @param   vpw			�r�W���A������Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int VisualSeq_End(VISUAL_PROC_WORK *vpw, VISUAL_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&vpw->cow, vpw, VORDER_NO_VISUAL_EXIT, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&vpw->cow) == 0){
		if(CO_AnswerCountCheck(&vpw->cow, vpw->consys->c_game.player_num, 
				vpw->consys->c_game.my_breeder_no, vpw->consys->c_game.server_no) == TRUE){
			return VSRET_END;
		}
		break;
	}
	return VSRET_CONTINUE;
}

