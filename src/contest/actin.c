//==============================================================================
/**
 * @file	actin.c
 * @brief	���Z�͕���
 * @author	matsuda
 * @date	2005.11.15(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "system/pmfprint.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"
#include "system/snd_tool.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "communication/communication.h"

#include "con_tool.h"
#include "actin_tool.h"
#include "actin_order.h"
#include "actin_id.h"
#include "actin_input.h"
#include "actin_calc.h"
#include "contest_order.h"
#include "aci_tool.h"
#include "contype_icon.h"
#include "poketool/waza_tool.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_cmsg_acting.h"
#include "msgdata/msg_cmsg_wazaexplain.h"
#include "msgdata/msg_cmsg_wazakouka.h"

#include "system/wipe.h"
#include "communication/wm_icon.h"

#include "battle/wazano_def.h"
#include "system/msgdata_util.h"

#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);


//==============================================================================
//	�萔��`
//==============================================================================
///���݂̓�����
enum{
	APW_PROC_MODE_INIT,		///<��������
	APW_PROC_MODE_MAIN,		///<���C��
	APW_PROC_MODE_ETC,		///<����ȊO
};

///Vram�]���}�l�[�W���[�^�X�N��
#define ACTIN_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

///���̂܂܂̍��W�w�肾�ƁA256x256�͈̔͂𒴂������ɂ̓E�B���h�E���쐬�o���Ȃ��B
///���̕����W�����炷����2���ڂ̃X�N���[�����Q�Ƃ���悤�ɂȂ�B
#define CONTEST_ADD_BMP_Y		(32)

//--------------------------------------------------------------
//	BMP�E�B���h�E
//--------------------------------------------------------------
///BMP�E�B���h�ECGX�G���A�J�n�ʒu(�I�t�Z�b�g)
#define BMPWIN_CGX_START			((0x8000 - 0x2000) / 32)

#define BMPWIN_TALK_COLOR			(0xd)
#define BMPWIN_TALK_CGX_OFFSET		(BMPWIN_CGX_START)
#define BMPWIN_TALK_CGX_SIZE		(20 * 4)	//(0x900 / 32)

#define BMPWIN_DEBUG_COLOR			(BMPWIN_TALK_COLOR)
#define BMPWIN_DEBUG_CGX_OFFSET		(BMPWIN_TALK_CGX_OFFSET + BMPWIN_TALK_CGX_SIZE)
#define BMPWIN_DEBUG_CGX_SIZE		(20 * 4)

//--------------------------------------------------------------
//	CL_ACT�p�̒萔��`
//--------------------------------------------------------------
///���C��	OAM�Ǘ��̈�E�J�n
#define ACTIN_OAM_START_MAIN			(BATTLE_OAM_START_MAIN)
///���C��	OAM�Ǘ��̈�E�I��
#define ACTIN_OAM_END_MAIN				(BATTLE_OAM_END_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�J�n
#define ACTIN_OAM_AFFINE_START_MAIN		(BATTLE_OAM_AFFINE_START_MAIN)
///���C��	�A�t�B���Ǘ��̈�E�I��
#define ACTIN_OAM_AFFINE_END_MAIN		(BATTLE_OAM_AFFINE_END_MAIN)
///�T�u	OAM�Ǘ��̈�E�J�n
#define ACTIN_OAM_START_SUB				(BATTLE_OAM_START_SUB)
///�T�u	OAM�Ǘ��̈�E�I��
#define ACTIN_OAM_END_SUB				(BATTLE_OAM_END_SUB)
///�T�u �A�t�B���Ǘ��̈�E�J�n
#define ACTIN_OAM_AFFINE_START_SUB		(BATTLE_OAM_AFFINE_START_SUB)
///�T�u	�A�t�B���Ǘ��̈�E�I��
#define ACTIN_OAM_AFFINE_END_SUB		(BATTLE_OAM_AFFINE_END_SUB)

///�L�����}�l�[�W���F�L�����N�^ID�Ǘ���(���ʁ{�����)
#define ACTIN_CHAR_MAX					(BATTLE_CHAR_MAX)
///�L�����}�l�[�W���F���C����ʃT�C�Y(byte�P��)
#define ACTIN_CHAR_VRAMSIZE_MAIN		(BATTLE_CHAR_VRAMSIZE_MAIN)
///�L�����}�l�[�W���F�T�u��ʃT�C�Y(byte�P��)
#define ACTIN_CHAR_VRAMSIZE_SUB			(BATTLE_CHAR_VRAMSIZE_SUB)

///���C����ʁ{�T�u��ʂŎg�p����A�N�^�[����
#define ACTIN_ACTOR_MAX					(BATTLE_ACTOR_MAX)

///OBJ�Ŏg�p����p���b�g�{��(���ʁ{�����)
#define ACTIN_OAM_PLTT_MAX				(BATTLE_OAM_PLTT_MAX)

///�]�����[�h 3D = 0 main = 1 sub = 2 main/sub = 3
#define ACTIN_OAM_VRAM_TRANS			(BATTLE_OAM_VRAM_TRANS)

///OAM���\�[�X�F�L�����o�^�ő吔(���C����� + �T�u���)
#define ACTIN_OAMRESOURCE_CHAR_MAX		(BATTLE_OAMRESOURCE_CHAR_MAX)
///OAM���\�[�X�F�p���b�g�o�^�ő吔(���C����� + �T�u���)
#define ACTIN_OAMRESOURCE_PLTT_MAX		(BATTLE_OAMRESOURCE_PLTT_MAX)
///OAM���\�[�X�F�Z���o�^�ő吔
#define ACTIN_OAMRESOURCE_CELL_MAX		(BATTLE_OAMRESOURCE_CELL_MAX)
///OAM���\�[�X�F�Z���A�j���o�^�ő吔
#define ACTIN_OAMRESOURCE_CELLANM_MAX	(BATTLE_OAMRESOURCE_CELLANM_MAX)
///OAM���\�[�X�F�}���`�Z���o�^�ő吔
#define ACTIN_OAMRESOURCE_MCELL_MAX		(BATTLE_OAMRESOURCE_MCELL_MAX)
///OAM���\�[�X�F�}���`�Z���A�j���o�^�ő吔
#define ACTIN_OAMRESOURCE_MCELLANM_MAX	(BATTLE_OAMRESOURCE_MCELLANM_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�T�u���BG�̃X�N���[���N���A�R�[�h
#define SUB_BG_CLEAR_CODE		(0)


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void ActinSys_VramBankSet(GF_BGL_INI *bgl);
static void ActinSys_DefaultBmpWinAdd(ACTIN_PROC_WORK *apw);
static void ActinParticleInit(void);
static void ActinUpdate(TCB_PTR tcb, void *work);
static void ActinVBlank(void *work);
static void ActinSystemWorkInit(ACTIN_PROC_WORK *apw);
static int ActinSeq_Init(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_Practice_FastTalk(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_FastTalk(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_UserSelect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_SelectBreeder(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_PokemonIn(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_WazaEffectBefore(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_WazaEffect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_AppealReview(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_PokemonOut(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_NextBreeder(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_AllReviewAfter(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_TurnStart(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_JudgeComment(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_TurnEnd(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static int ActinSeq_End(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
static void ActinDefaultOBJSet(ACTIN_PROC_WORK *apw);
static void ActinDefaultOBJDel(ACTIN_PROC_WORK *apw);
static void ActinDefaultOBJSet_Sub(ACTIN_PROC_WORK *apw);
static void ActinDefaultOBJDel_Sub(ACTIN_PROC_WORK *apw);
static void ActinDefaultBGSet(ACTIN_PROC_WORK *apw);
static void ActinDefaultBGDel(ACTIN_PROC_WORK *apw);
static void ActinDefaultBGSet_Sub(ACTIN_PROC_WORK *apw);
static void ActinDefaultBGDel_Sub(ACTIN_PROC_WORK *apw);
void ActinBG_BrdPanelSet(ACTIN_PROC_WORK *apw, int eff_bg_type, int disp_set);
#ifdef PM_DEBUG
static int ActinSeq_DebugWazaEffect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local);
#endif

//==============================================================================
//	�f�[�^
//==============================================================================

//==============================================================================
//	�V�[�P���X�e�[�u��
//==============================================================================
///ActinMainSeqTbl�̖߂�l�Ƃ��Ďg�p
enum{
	ASRET_CONTINUE,		///<����ێ�
	ASRET_NEXT,			///<���̃V�[�P���X��
	ASRET_SELECT_SEQ,	///<select_seq���[�N�ɓ����Ă���V�[�P���X�֐i��
	ASRET_END,			///<�I��
};

///���Z�͕��僁�C���֐��̃V�[�P���X�e�[�u��
static int (* const ActinMainSeqTbl[])(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local) = {
	ActinSeq_Init,
	ActinSeq_Practice_FastTalk,
	ActinSeq_FastTalk,
	ActinSeq_TurnStart,
	ActinSeq_UserSelect,
	ActinSeq_SelectBreeder,
	ActinSeq_PokemonIn,
	ActinSeq_WazaEffectBefore,
	ActinSeq_WazaEffect,
	ActinSeq_AppealReview,
	ActinSeq_PokemonOut,
	ActinSeq_NextBreeder,
	ActinSeq_AllReviewAfter,
	ActinSeq_JudgeComment,
	ActinSeq_TurnEnd,
	ActinSeq_End,
	
#ifdef PM_DEBUG
	ActinSeq_DebugWazaEffect,
#endif
};
///ActinMainSeqTbl�̃V�[�P���X�ԍ�	��ActinMainSeqTbl�ƕ��т𓯂��ɂ��Ă������ƁI�I
enum{
	ASEQ_INIT,
	ASEQ_PRACTICE_FAST_TALK,
	ASEQ_FAST_TALK,
	ASEQ_TURN_START,
	ASEQ_USER_SELECT,
	ASEQ_SELECT_BREEDER,
	ASEQ_POKEMON_IN,
	ASEQ_WAZAEFFECT_BEFORE,
	ASEQ_WAZAEFFECT,
	ASEQ_APPEAL_REVIEW,
	ASEQ_POKEMON_OUT,
	ASEQ_NEXT_BREEDER,
	ASEQ_ALL_REVIEW_AFTER,
	ASEQ_JUDGE_COMMENT,
	ASEQ_TURN_END,
	ASEQ_END,
	
#ifdef PM_DEBUG
	ASEQ_DEBUG_WAZAEFF,
#endif
};

//==============================================================================
//	CLACT�p�f�[�^
//==============================================================================
static	const TCATS_OAM_INIT ActinTcats = {
	ACTIN_OAM_START_MAIN, ACTIN_OAM_END_MAIN,
	ACTIN_OAM_AFFINE_START_MAIN, ACTIN_OAM_AFFINE_END_MAIN,
	ACTIN_OAM_START_SUB, ACTIN_OAM_END_SUB,
	ACTIN_OAM_AFFINE_START_SUB, ACTIN_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE ActinCcmm = {
	ACTIN_CHAR_MAX,
	ACTIN_CHAR_VRAMSIZE_MAIN,
	ACTIN_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

static const TCATS_RESOURCE_NUM_LIST ActinResourceList = {
	ACTIN_OAMRESOURCE_CHAR_MAX,
	ACTIN_OAMRESOURCE_PLTT_MAX,
	ACTIN_OAMRESOURCE_CELL_MAX,
	ACTIN_OAMRESOURCE_CELLANM_MAX,
	ACTIN_OAMRESOURCE_MCELL_MAX,
	ACTIN_OAMRESOURCE_MCELLANM_MAX,
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
PROC_RESULT ActinProc_Init( PROC * proc, int * seq )
{
	ACTIN_PROC_WORK *apw;

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
	
	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_ACTIN, ACTIN_ALLOC_SIZE);

	apw = PROC_AllocWork(proc, sizeof(ACTIN_PROC_WORK), HEAPID_ACTIN );
	MI_CpuClear8(apw, sizeof(ACTIN_PROC_WORK));

//	simple_3DBGInit(HEAPID_ACTIN);
	apw->g3Dman = ADV_Contest_3D_Init(HEAPID_ACTIN);

	apw->consys = PROC_GetParentWork(proc);
	apw->consys->class_proc = apw;
	apw->consys->class_flag = CON_CLASS_ACTIN;
	apw->sys.c_game = &apw->consys->c_game;
	ActinSystemWorkInit(apw);
	
	//�p���b�g�t�F�[�h�V�X�e���쐬
	apw->sys.pfd = PaletteFadeInit(HEAPID_ACTIN);
	PaletteTrans_AutoSet(apw->sys.pfd, TRUE);
	PaletteFadeWorkAllocSet(apw->sys.pfd, FADE_MAIN_BG, 0x200, HEAPID_ACTIN);
	PaletteFadeWorkAllocSet(apw->sys.pfd, FADE_SUB_BG, 0x200, HEAPID_ACTIN);
	PaletteFadeWorkAllocSet(apw->sys.pfd, FADE_MAIN_OBJ, CONTEST_MAIN_OBJPAL_SIZE, HEAPID_ACTIN);
	PaletteFadeWorkAllocSet(apw->sys.pfd, FADE_SUB_OBJ, 0x200, HEAPID_ACTIN);
	
	apw->sys.bgl = GF_BGL_BglIniAlloc(HEAPID_ACTIN);

	initVramTransferManagerHeap(ACTIN_VRAM_TRANSFER_TASK_NUM, HEAPID_ACTIN);

	sys_KeyRepeatSpeedSet( 4, 8 );

	apw->aip = AINPUT_SystemInit(apw->consys, &apw->sys, &apw->a_game);

	//VRAM���蓖�Đݒ�
	ActinSys_VramBankSet(apw->sys.bgl);

	// �^�b�`�p�l���V�X�e��������
	InitTPSystem();
	InitTPNoBuff(4);

	// �{�^���p�t�H���g��ǂݍ���
	FontProc_LoadFont(FONT_BUTTON, HEAPID_ACTIN);

	// ������ۑ�
//	SetActinWorkParameter(apw, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

	//�A�N�^�[�V�X�e���쐬
	apw->sys.csp=CATS_AllocMemory(HEAPID_ACTIN);
	CATS_SystemInit(apw->sys.csp,&ActinTcats,&ActinCcmm,ACTIN_OAM_PLTT_MAX);
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	apw->sys.crp=CATS_ResourceCreate(apw->sys.csp);
	CATS_ClactSetInit(apw->sys.csp, apw->sys.crp, ACTIN_ACTOR_MAX);
	CATS_ResourceManagerInit(apw->sys.csp,apw->sys.crp,&ActinResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(apw->sys.csp), 0, ACTIN_SUB_ACTOR_DISTANCE);

	apw->sys.soft_sprite = SoftSpriteInit(HEAPID_ACTIN);
	ActinParticleInit();	//�p�[�e�B�N��������
	apw->sys.wsp = WES_Create(HEAPID_ACTIN);	//�Z�G�t�F�N�g�V�X�e���쐬
	WES_ContestFlag_Set(apw->sys.wsp, TRUE);	//�R���e�X�g�t���O�Z�b�g

	//���b�Z�[�W�}�l�[�W���쐬
	apw->sys.actin_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_acting_dat, 
		HEAPID_ACTIN);
	apw->sys.breeder_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_breeder_dat, 
		HEAPID_ACTIN);
	apw->sys.explain_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
		NARC_msg_cmsg_wazaexplain_dat, HEAPID_ACTIN);
	apw->sys.wazakouka_msg = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
		NARC_msg_cmsg_wazakouka_dat, HEAPID_ACTIN);

	//�t�H���gOAM�V�X�e���쐬
	apw->sys.fontoam_sys = FONTOAM_SysInit(ACTIN_FONTOAM_MAX_MAIN, HEAPID_ACTIN);

	apw->sys.wordset = WORDSET_Create(HEAPID_ACTIN);	//�P��o�b�t�@�쐬
	apw->sys.msg_buf = STRBUF_Create(ACTIN_MESSAGE_BUF_SIZE, HEAPID_ACTIN);	//������o�b�t�@�쐬
	
	//�풓BG�Z�b�g
	ActinDefaultBGSet(apw);
	ActinDefaultBGSet_Sub(apw);

	//BMP�E�B���h�E�ǉ�
	ActinSys_DefaultBmpWinAdd(apw);
	//BreederParamBmpWriteAll(apw);
	BreederPanelColorChangeAll(apw);

	//�풓OBJ�Z�b�g
	ActinDefaultOBJSet(apw);
	ActinDefaultOBJSet_Sub(apw);

	{
		u16 wazano[WAZA_TEMOTI_MAX];
		int i;
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			wazano[i] =PokeParaGet(apw->consys->c_game.pp[apw->consys->c_game.my_breeder_no], 
				ID_PARA_waza1 + i, NULL);
		}
		AINPUT_WazaParaMemoryDecord(apw->aip, wazano);
	}
	AINPUT_CreateBG(apw->aip, AINPUT_TYPE_WALL, TRUE, NULL);
	
	//�|�P�����\�t�g�E�F�A�X�v���C�g����
	AT_SoftSpriteAddAll(&apw->sys);
	
	WirelessIconEasy();	//�ʐM�A�C�R��
	
	// �P�x�ύX�Z�b�g
//	ChangeBrightnessRequest(
//		8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	WIPE_SYS_Start(WIPE_PATTERN_FMAS, WIPE_TYPE_BLINDIN_H, WIPE_TYPE_BLINDIN_H, WIPE_FADE_BLACK, 
		WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_ACTIN);

	apw->update_tcb = TCB_Add(ActinUpdate, apw, TCBPRI_ACTIN_UPDATE);
	apw->proc_mode = APW_PROC_MODE_MAIN;

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	//�T�E���h�f�[�^���[�h(�R���e�X�g)
	Snd_DataSetByScene( SND_SCENE_CONTEST, SEQ_CON_TEST, 1 );
	//if(Snd_NowBgmNoGet() != SEQ_CON_TEST){
	//	Snd_Stop();
	//	Snd_BgmPlay(SEQ_CON_TEST);
	//}

	ConTool_MsgPrintFlagSet(apw->consys->sio_flag);
	
	sys_VBlankFuncChange(ActinVBlank, apw);
	
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
PROC_RESULT ActinProc_Main( PROC * proc, int * seq )
{
	ACTIN_PROC_WORK * apw  = PROC_GetWork( proc );
	int ret;
	enum{
		SEQ_IN,
		SEQ_MAIN,
		SEQ_OUT,
	};
	
	contest_rand(apw->consys);
	
	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if(WIPE_SYS_EndCheck() == TRUE){
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		if(ConTool_ServerMineCheck(apw->consys) == TRUE){
			ret = ActinMainSeqTbl[apw->tbl_seq_no](apw, &apw->local);
			if(ret == ASRET_NEXT || ret == ASRET_SELECT_SEQ){
				if(ret == ASRET_NEXT){
					apw->tbl_seq_no++;
				}
				else{
					apw->tbl_seq_no = apw->local.select_seq;
				}
				MI_CpuClear8(&apw->local, sizeof(ACTIN_LOCAL_WORK));
			}
			else if(ret == ASRET_END){
				*seq = SEQ_OUT;
				MI_CpuClear8(&apw->local, sizeof(ACTIN_LOCAL_WORK));
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_SCREWOUT, WIPE_TYPE_SCREWOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_ACTIN);
				break;
			}
		}
		
		CO_TransmitCheckExe(&apw->cow);
		CO_RecieveCheckExe(&apw->cow, apw);
		
		if(apw->main_end == TRUE){
			*seq = SEQ_OUT;
			MI_CpuClear8(&apw->local, sizeof(ACTIN_LOCAL_WORK));
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_SCREWOUT, WIPE_TYPE_SCREWOUT, 
				WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_ACTIN);
		}
		break;

	case SEQ_OUT:
		if(WIPE_SYS_EndCheck() == TRUE){
//		if(IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY)){
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
PROC_RESULT ActinProc_End( PROC * proc, int * seq )
{
	ACTIN_PROC_WORK * apw = PROC_GetWork( proc );
	int i;

	Particle_SystemExitAll();
	WES_Delete(apw->sys.wsp);

	//�풓OBJ�폜
	ActinDefaultOBJDel(apw);
	ActinDefaultOBJDel_Sub(apw);
	//�풓BG�폜
	ActinDefaultBGDel(apw);
	ActinDefaultBGDel_Sub(apw);

	//BMP�J��
	for(i = 0; i < ACTIN_BMPWIN_MAX; i++){
		GF_BGL_BmpWinDel(&apw->sys.win[i]);
	}

	//���C�����BG�폜
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(apw->sys.bgl, ACTIN_FRAME_WIN );
	GF_BGL_BGControlExit(apw->sys.bgl, ACTIN_FRAME_EFF );
	GF_BGL_BGControlExit(apw->sys.bgl, ACTIN_FRAME_AUDIENCE );
	//�T�u���BG�폜
	AINPUT_FrameExit(apw->sys.bgl);
	AINPUT_SystemFree(apw->aip);

	//�A�N�^�[�V�X�e���폜
	CATS_ResourceDestructor_S(apw->sys.csp,apw->sys.crp);
	CATS_FreeMemory(apw->sys.csp);

	//Vram�]���}�l�[�W���[�폜
	DellVramTransferManager();

	//�\�t�g�E�F�A�X�v���C�g�폜
	AT_SoftSpriteDelAll(&apw->sys);
	SoftSpriteEnd(apw->sys.soft_sprite);

	//�t�H���g�폜
	FontProc_UnloadFont(FONT_BUTTON);

	//�t�H���gOAM�V�X�e���폜
	FONTOAM_SysDelete(apw->sys.fontoam_sys);

	//�p���b�g�t�F�[�h�V�X�e���폜
	PaletteFadeWorkAllocFree(apw->sys.pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(apw->sys.pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(apw->sys.pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(apw->sys.pfd, FADE_SUB_OBJ);
	PaletteFadeFree(apw->sys.pfd);

	//���b�Z�[�W�}�l�[�W���̍폜
	STRBUF_Delete(apw->sys.msg_buf);
	WORDSET_Delete(apw->sys.wordset);
	MSGMAN_Delete(apw->sys.actin_msg);
	MSGMAN_Delete(apw->sys.breeder_msg);
	MSGMAN_Delete(apw->sys.explain_msg);
	MSGMAN_Delete(apw->sys.wazakouka_msg);

	//BGL�J��
	sys_FreeMemoryEz(apw->sys.bgl);

	TCB_Delete(apw->update_tcb);

	//simple_3DBGExit();
	ADV_Contest_3D_Exit(apw->g3Dman);

	StopTP();		//�^�b�`�p�l���̏I��

	PROC_FreeWork(proc);				// ���[�N�J��
	
	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	sys_DeleteHeap(HEAPID_ACTIN);

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
 * @param	work	���Z�͕���Ǘ����[�N�ւ̃|�C���^
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ActinVBlank(void *work)
{
	ACTIN_PROC_WORK *apw = work;
	
	SoftSpriteTextureTrans(apw->sys.soft_sprite);

	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	PaletteFadeTrans(apw->sys.pfd);
	
	GF_BGL_VBlankFunc(apw->sys.bgl);
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����[�v�̍Ō�ɍs���V�X�e���֘A�̍X�V����
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		apw
 */
//--------------------------------------------------------------
static void ActinUpdate(TCB_PTR tcb, void *work)
{
	ACTIN_PROC_WORK *apw = work;
	
	if(apw->proc_mode == APW_PROC_MODE_MAIN){
		SoftSpriteMain(apw->sys.soft_sprite);
		BattleParticle_Main();
		CATS_Draw(apw->sys.crp);
		CATS_UpdateTransfer();
		G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}
	
	CommErrorCheck(HEAPID_ACTIN, apw->sys.bgl);

#ifdef PM_DEBUG		//�|���S���̃��C���Y�I�[�o�[�`�F�b�N
	if(G3X_IsLineBufferUnderflow() != 0){
		OS_TPrintf("--------------���C���Y�I�[�o�[�����I�I----------\n");
		//GF_ASSERT(0 && "���C���Y�I�[�o�[���������܂���");
		G3X_ResetLineBufferUnderflow();
	}
	else if(G3X_GetRenderedLineCount() < 10){
		OS_TPrintf("========== ���C���Y�I�[�o�[�������������ł��c Count = %d\n", 
			G3X_GetRenderedLineCount());
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   Vram�o���N�ݒ���s��
 *
 * @param   bgl		BGL�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinSys_VramBankSet(GF_BGL_INI *bgl)
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
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				ACTIN_BGPRI_WINDOW, 0, 0, FALSE
			},
			///<FRAME2_M	�G�t�F�N�g
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				ACTIN_BGPRI_EFFECT, 0, 0, FALSE
			},
			///<FRAME3_M	�w�i
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				ACTIN_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, ACTIN_FRAME_WIN, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, ACTIN_FRAME_WIN );
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_WIN, GF_BGL_SCROLL_X_SET, FRAME_WIN_DEFAULT_X);
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_WIN, GF_BGL_SCROLL_Y_SET, FRAME_WIN_DEFAULT_Y);
		GF_BGL_BGControlSet(bgl, ACTIN_FRAME_EFF, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, ACTIN_FRAME_EFF );
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_BGControlSet(bgl, ACTIN_FRAME_AUDIENCE, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, ACTIN_FRAME_AUDIENCE );
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_AUDIENCE, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, ACTIN_FRAME_AUDIENCE, GF_BGL_SCROLL_Y_SET, 0);

		G2_SetBG0Priority(ACTIN_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//�T�u��ʃt���[���ݒ�
	{
		AINPUT_DefaultFrameSet(bgl);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ����BMP�E�B���h�E��ݒ肷��
 *
 * @param   apw		���Z�͊Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinSys_DefaultBmpWinAdd(ACTIN_PROC_WORK *apw)
{
	GF_BGL_BmpWinAdd(apw->sys.bgl, &apw->sys.win[ACTIN_BMPWIN_TALK], ACTIN_FRAME_WIN, 
		11, 0x13, 20, 4, BMPWIN_TALK_COLOR, BMPWIN_TALK_CGX_OFFSET);

#if 0
	GF_BGL_BmpWinAdd(apw->sys.bgl, &apw->sys.win[ACTIN_BMPWIN_BREEDER_0], ACTIN_FRAME_WIN, 
		23, 0+CONTEST_ADD_BMP_Y, 8, 4, BMPWIN_BREEDER0_COLOR, BMPWIN_BREEDER0_CGX_OFFSET);
	GF_BGL_BmpWinAdd(apw->sys.bgl, &apw->sys.win[ACTIN_BMPWIN_BREEDER_1], ACTIN_FRAME_WIN, 
		23, 6+CONTEST_ADD_BMP_Y, 8, 4, BMPWIN_BREEDER1_COLOR, BMPWIN_BREEDER1_CGX_OFFSET);
	GF_BGL_BmpWinAdd(apw->sys.bgl, &apw->sys.win[ACTIN_BMPWIN_BREEDER_2], ACTIN_FRAME_WIN, 
		23, 12+CONTEST_ADD_BMP_Y, 8, 4, BMPWIN_BREEDER2_COLOR, BMPWIN_BREEDER2_CGX_OFFSET);
	GF_BGL_BmpWinAdd(apw->sys.bgl, &apw->sys.win[ACTIN_BMPWIN_BREEDER_3], ACTIN_FRAME_WIN, 
		23, 18+CONTEST_ADD_BMP_Y, 8, 4, BMPWIN_BREEDER3_COLOR, BMPWIN_BREEDER3_CGX_OFFSET);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ���Z����p�p�[�e�B�N��������
 */
//--------------------------------------------------------------
static void ActinParticleInit(void)
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
 * @brief   ���Z�͕���Ǘ����[�N�̏����p�����[�^���Z�b�g����
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinSystemWorkInit(ACTIN_PROC_WORK *apw)
{
	int i;
	
	GF_ASSERT(apw->consys != NULL);
	
	for(i = 0; i < BREEDER_MAX; i++){
		apw->a_game.breeder_sort[i] = apw->consys->actin_sort[i];
	}

	ActinOrder_WorkInit(apw);
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultOBJSet(ACTIN_PROC_WORK *apw)
{
	//�풓OBJ�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(apw->sys.pfd, FADE_MAIN_OBJ, apw->sys.csp, apw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_OBJ_NCLR, 0, 
		ACTIN_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_OBJ_COMMON);
	//�t�H���gOAM�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(apw->sys.pfd, FADE_MAIN_OBJ, apw->sys.csp, apw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_FONTOBJ_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_FONTACT);
	
	AT_NextIconResourceLoad(apw->sys.csp, apw->sys.crp);
	
	AT_BreederPanelFontOamCreateAll(apw);
	AT_JudgeAddAll(&apw->sys, apw->consys);
	AT_SpecialHeartSet(&apw->sys, apw->consys->c_game.special_judge_no);
	
	AT_JudgeReactionIconResourceLoad(apw->sys.pfd, apw->sys.csp, apw->sys.crp);
	AT_JudgeReactionIconActorAdd(&apw->sys);

	AT_AppealPointResourceLoad(apw->sys.csp, apw->sys.crp);
	AT_VoltagePointResourceLoad(apw->sys.csp, apw->sys.crp);
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�͕���Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultOBJDel(ACTIN_PROC_WORK *apw)
{
	AT_SpecialHeartDel(&apw->sys);
	AT_JudgeDelAll(&apw->sys);
	AT_BreederPanelFontOamDeleteAll(apw);
	AT_NextIconActorDelAll(&apw->sys);
	
	AT_NextIconResourceFree(apw->sys.crp);
	CATS_FreeResourcePltt(apw->sys.crp, PLTTID_OBJ_COMMON);
	CATS_FreeResourcePltt(apw->sys.crp, PLTTID_FONTACT);
	
	AT_JudgeReactionIconActorDel(&apw->sys);
	AT_JudgeReactionIconResourceDel(apw->sys.crp);

	AT_AppealPointResourceFree(apw->sys.crp);
	AT_AppealPointActorDelAll(&apw->sys);
	AT_VoltagePointResourceFree(apw->sys.crp);
	AT_VoltagePointActorDelAll(&apw->sys);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F���Z�͕���Ŏg�p�����{�I�ȏ풓OBJ�̓o�^���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultOBJSet_Sub(ACTIN_PROC_WORK *apw)
{
	//�풓OBJ�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(apw->sys.pfd, FADE_SUB_OBJ, apw->sys.csp, apw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_SUB_OBJ_NCLR, 0, 
		ACTIN_SUB_COMMON_PAL_NUM, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_OBJ_COMMON_SUB);
	//�t�H���gOAM�p���b�g���[�h
	CATS_LoadResourcePlttWorkArc(apw->sys.pfd, FADE_SUB_OBJ, apw->sys.csp, apw->sys.crp, 
		ARC_CONTEST_OBJ, CONTEST_FONTOBJ_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_SUB_FONTACT);
	
	ACIT_AppHeartResourceLoad(apw->sys.csp, apw->sys.crp);
	ACIT_SubHeartJudgeResourceSet(apw->sys.csp, apw->sys.crp);
	
	ConTypeIcon_CellAnmResourceLoad(apw->sys.csp, apw->sys.crp, 
		CELLID_CONTYPE_ICON, CELLANMID_CONTYPE_ICON);
	{
		int i, con_type, wazano;
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			wazano = PokeParaGet(apw->consys->c_game.pp[apw->consys->c_game.my_breeder_no], 
				ID_PARA_waza1 + i, NULL);
			if(wazano != 0){
				con_type = WT_WazaDataParaGet(wazano, ID_WTD_contype);
			}
			else{
				con_type = 0;
			}
			ConTypeIcon_CharResourceLoad(apw->sys.csp, apw->sys.crp, NNS_G2D_VRAM_TYPE_2DSUB, 
				con_type, CHARID_CONTYPE_ICON_1 + i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���OBJ�F���Z�͕���Ŏg�p�����{�I�ȏ풓OBJ�̍폜���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultOBJDel_Sub(ACTIN_PROC_WORK *apw)
{
	CATS_FreeResourcePltt(apw->sys.crp, PLTTID_OBJ_COMMON_SUB);

	ACIT_AppHeartResourceFree(apw->sys.crp);
	ACIT_SubHeartJudgeResourceFree(apw->sys.crp);
	
	ConTypeIcon_CellAnmResourceFree(apw->sys.crp, CELLID_CONTYPE_ICON, CELLANMID_CONTYPE_ICON);
	{
		int i;
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			ConTypeIcon_CharResourceFree(apw->sys.crp, CHARID_CONTYPE_ICON_1 + i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�g�ʂɃu���[�_�[�p�l��BG��W�J����
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   eff_bg_type �Z�b�g����BG�̃^�C�v(EFF_BG_TYPE_???)
 * @param   disp_set	TRUE:DISPCNT�ŃG�t�F�N�g�ʂ�ON�ɂ���
 */
//--------------------------------------------------------------
void ActinBG_BrdPanelSet(ACTIN_PROC_WORK *apw, int eff_bg_type, int disp_set)
{
	if(eff_bg_type == EFF_BG_TYPE_BRDPANEL){
		//�L�����N�^�F�Ƃ肠�����E�B���h�E�L�����Ɠ������̂�W�J
		ArcUtil_BgCharSet(ARC_CONTEST_BG, PANEL_NCGR_BIN, apw->sys.bgl, 
			ACTIN_FRAME_BRDPANEL, 0, 0x4000, 1, HEAPID_ACTIN);
		//�X�N���[��
		ArcUtil_ScrnSet(ARC_CONTEST_BG, BRDPANEL_NSCR_BIN, apw->sys.bgl, 
			ACTIN_FRAME_BRDPANEL, 0, 0, 1, HEAPID_ACTIN);
		//BG�v���C�I���e�B
		GF_BGL_PrioritySet(ACTIN_FRAME_WIN, ACTIN_BGPRI_EFFECT);
		GF_BGL_PrioritySet(ACTIN_FRAME_BRDPANEL, ACTIN_BGPRI_WINDOW);
		
		BreederPanelColorChangeAll(apw);
	
		if(disp_set == TRUE){
			GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_ON);
		}
	}
	else{
		GF_BGL_ClearCharSet(ACTIN_FRAME_BRDPANEL, 0x4000, 0, HEAPID_ACTIN);
		GF_BGL_ScrClear(apw->sys.bgl, ACTIN_FRAME_BRDPANEL);
		//BG�v���C�I���e�B
		GF_BGL_PrioritySet(ACTIN_FRAME_WIN, ACTIN_BGPRI_WINDOW);
		GF_BGL_PrioritySet(ACTIN_FRAME_BRDPANEL, ACTIN_BGPRI_EFFECT);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F���Z�͕���Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultBGSet(ACTIN_PROC_WORK *apw)
{
	//�ϋq
	ArcUtil_BgCharSet(ARC_CONTEST_BG, CON_BG_NCGR_BIN, apw->sys.bgl, 
		ACTIN_FRAME_AUDIENCE, 0, 0, 1, HEAPID_ACTIN);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, CON_BG_NSCR_BIN, apw->sys.bgl, 
		ACTIN_FRAME_AUDIENCE, 0, 0, 1, HEAPID_ACTIN);
	
	//�E�B���h�E
	ArcUtil_BgCharSet(ARC_CONTEST_BG, PANEL_NCGR_BIN, apw->sys.bgl, 
		ACTIN_FRAME_WIN, 0, 0, 1, HEAPID_ACTIN);
	ArcUtil_ScrnSet(ARC_CONTEST_BG, PANEL_NSCR_BIN, apw->sys.bgl, 
		ACTIN_FRAME_WIN, 0, 0, 1, HEAPID_ACTIN);
	
	//�G�t�F�N�g
//	GF_BGL_ScrClear(apw->sys.bgl, ACTIN_FRAME_EFF);
	ActinBG_BrdPanelSet(apw, EFF_BG_TYPE_BRDPANEL, FALSE);
	
	//�p���b�g
	PaletteWorkSet_Arc(apw->sys.pfd, ARC_CONTEST_BG, CONTEST_BG_NCLR, 
		HEAPID_ACTIN, FADE_MAIN_BG, 0, 0);
	//�����p�̃u���[�_�[�p�l���̃J���[�f�[�^�������̃u���[�_�[�ԍ��ʒu�ֈڂ��ς���
	//���ʐM�ΐ킾�ƃu���[�_�[�ԍ���0�ȊO�̂��̂ɂ��Ȃ�̂�
	{
		u16 *my, *target, *defwk, *transwk;
		
		my = sys_AllocMemory(HEAPID_ACTIN, 0x20);
		target = sys_AllocMemory(HEAPID_ACTIN, 0x20);
		defwk = PaletteWorkDefaultWorkGet(apw->sys.pfd, FADE_MAIN_BG);
		transwk = PaletteWorkTransWorkGet(apw->sys.pfd, FADE_MAIN_BG);
		MI_CpuCopy16(&defwk[BreederPanelScreenPalNo[0] * 16], my, 0x20);
		MI_CpuCopy16(&defwk[BreederPanelScreenPalNo[apw->consys->c_game.my_breeder_no] * 16], 
			target, 0x20);
		MI_CpuCopy16(my, &defwk[BreederPanelScreenPalNo[apw->consys->c_game.my_breeder_no] * 16],
			0x20);
		MI_CpuCopy16(target, &defwk[BreederPanelScreenPalNo[0] * 16], 0x20);
		//�]���p���b�g�ɂ��R�s�[
		MI_CpuCopy16(my, &transwk[BreederPanelScreenPalNo[apw->consys->c_game.my_breeder_no] * 16],
			0x20);
		MI_CpuCopy16(target, &transwk[BreederPanelScreenPalNo[0] * 16], 0x20);
		sys_FreeMemoryEz(my);
		sys_FreeMemoryEz(target);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����BG�F���Z�͕���Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultBGDel(ACTIN_PROC_WORK *apw)
{
	return;
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F���Z�͕���Ŏg�p�����{BG�f�[�^�̃Z�b�g���s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultBGSet_Sub(ACTIN_PROC_WORK *apw)
{
	//�p���b�g
//	PaletteWorkSet_Arc(apw->sys.pfd, ARC_CONTEST_BG, CONTEST_SUB_NCLR, 
//		HEAPID_ACTIN, FADE_SUB_BG, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �T�u���BG�F���Z�͕���Ŏg�p�����{BG�f�[�^�̍폜�������s��
 * @param   apw		���Z�͕���Ǘ����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ActinDefaultBGDel_Sub(ACTIN_PROC_WORK *apw)
{
	return;
}




//==============================================================================
//
//	�V�[�P���X
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F����������
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_Init(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_OPENING_EFFECT, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F���K�A�ŏ��̃��b�Z�[�W�\��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_Practice_FastTalk(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	if(ConTool_PracticeModeCheck(apw->consys) == FALSE){
		return ASRET_NEXT;
	}
	
	switch(local->seq){
	case 0:
		apw->advance.nt.a_talk_id = A_TALK_NULL;	//A_TALK_PRAC_APREFACE;
		apw->advance.nt.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		apw->advance.nt.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_TALK, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�ŏ��̃��b�Z�[�W�\��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_FastTalk(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
//		if(apw->consys->c_game.mode == CONMODE_CHARM){
//			apw->advance.nt.a_talk_id = A_TALK_ACT_HOST_02;
//		}
//		else{
//			apw->advance.nt.a_talk_id = A_TALK_ACT_HOST_01;
//		}
		if(ConTool_PracticeModeCheck(apw->consys) == TRUE){
			apw->advance.nt.a_talk_id = A_TALK_PRACTICE_OPENING;
		}
		else{
			apw->advance.nt.a_talk_id = AT_A_TalkIDGet_Host01(apw->consys->c_game.type);
		}
		
		apw->advance.nt.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		apw->advance.nt.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_TALK, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
		//if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�^�[���J�n����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_TurnStart(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
//	int i;
	
	switch(local->seq){
	case 0:
	default:
//		for(i = 0; i < BREEDER_MAX; i++){
//			apw->advance.now_sort[i] = apw->a_game.breeder_sort[i];
//		}
		
	#ifdef PM_DEBUG
		if(apw->consys->sio_flag == FALSE){
			if(sys.cont & PAD_BUTTON_START){
				local->select_seq = ASEQ_DEBUG_WAZAEFF;
				return ASRET_SELECT_SEQ;
			}
		}
	#endif
		
		return ASRET_NEXT;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�Z�ƐR���̑I��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_UserSelect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_USER_SELECT, NULL) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case 2:
		//CPU��AI�v�Z
		{
			ACTIN_AI_ANSWER answer;
			int i;
			
			ActinAI_Main(apw, &answer);
			for(i = apw->consys->c_game.player_num; i < BREEDER_MAX; i++){
				apw->a_game.waza_no[i] = answer.wazano[i];
				apw->a_game.judge_no[i] = answer.judge_no[i];
			}
		}
		local->seq++;
		break;
	default:
		AWAZA_WazaParaTurnInit(apw, &apw->advance.wazapara);
		return ASRET_NEXT;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F��ɏo��u���[�_�[��I��(�e�u���[�_�[�����Z���n�߂�O�ɍs������)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_SelectBreeder(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	int now_breeder, i, check_breeder;
	
	now_breeder = apw->a_game.breeder_sort[apw->a_game.breeder_end_count];
	
	apw->advance.now_breeder = now_breeder;
	apw->advance.now_pos = apw->a_game.breeder_end_count;
//	apw->advance.waza_no = apw->a_game.waza_no[now_breeder];
	apw->advance.judge_no = apw->a_game.judge_no[now_breeder];
	
	apw->advance.judge_reaction_type = JUDGE_REACTION_ICON_NOMINATION;
	for(i = 0; i < apw->a_game.breeder_end_count; i++){
		check_breeder = apw->a_game.breeder_sort[i];
		if(apw->a_game.judge_no[check_breeder] == apw->a_game.judge_no[now_breeder]){
			apw->advance.judge_reaction_type = JUDGE_REACTION_ICON_WEAR;
		}
	}
	
	AT_MsgTagParaInitDataSet(apw, &apw->advance.nt.a_talk_tagpara, now_breeder);
	AT_MsgTagParaInitDataSet(apw, &apw->advance.nt.after_a_talk_tagpara, now_breeder);

#if 0
	//-- �Z���ʌv�Z --//
	apw->advance.waza_personal = apw->advance.wazapara.personal[now_breeder];
	//�Z���ʌv�Z���ʂ��q�@���ł��K�v�Ȃ��̂���
	for(i = 0; i < BREEDER_MAX; i++){
		apw->advance.next_sort[i] = apw->advance.wazapara.personal[i].next_sort;
		apw->advance.next_pos[i] = apw->advance.wazapara.personal[i].next_pos;
	}
#endif

#if 0
	{
		int ap_point, ap_point_calc, judge_suffer, voltage_addsub, voltage_calc, voltage_now;
		int voltage_add_ap;

		//��{AP�擾
		ap_point = ACALC_BaseAppealGet(apw->advance.waza_no);
		//�R�����`�F�b�N
		judge_suffer = ACALC_JudgeSufferCheck(&apw->a_game, apw->advance.now_breeder);
		//�{���e�[�W�`�F�b�N
		voltage_addsub = ACALC_VoltageUpDownCheck(apw->consys->c_game.type, apw->advance.waza_no,
			apw->advance.judge_no, apw->consys->c_game.special_judge_no);
		//�{���e�[�W���Z
		voltage_now = apw->a_game.voltage_total[apw->advance.judge_no];
		voltage_calc = ACALC_VoltageAdd(&apw->a_game, apw->advance.judge_no, voltage_addsub);
		voltage_add_ap = 0;
		if(voltage_calc == VOLTAGE_POINT_FULL){
			if(apw->advance.judge_no == apw->consys->c_game.special_judge_no){
				voltage_add_ap = VOLTAGE_FULL_ADD_AP_SPECIAL;
			}
			else{
				voltage_add_ap = VOLTAGE_FULL_ADD_AP;
			}
		}
		
		//���v�v�Z
		ap_point_calc = ap_point - (judge_suffer * APPEAL_ICON_ONE_POINT);
		if(ap_point_calc < 0){
			ap_point_calc = 0;
		}
		
		apw->advance.ap_point = ap_point;
		apw->advance.judge_suffer = judge_suffer;
		apw->advance.voltage_now = voltage_now;
		apw->advance.voltage_calc = voltage_calc;
		apw->advance.voltage_add_ap = voltage_add_ap;
		apw->advance.ap_point_calc = ap_point_calc;
		//���vAP�l�ɉ��Z
		apw->a_game.app_total[apw->advance.now_breeder] += ap_point_calc + voltage_add_ap;
	}
#endif

	return ASRET_NEXT;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�|�P�����o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_PokemonIn(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_POKEMON_IN, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�Z�G�t�F�N�g���o���O�̏���
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_WazaEffectBefore(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		apw->advance.nt.a_talk_id = A_TALK_NULL;
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_WAZAEFFECT_BEFORE, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			apw->advance.nt.a_talk_id = A_TALK_NULL;
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�Z�G�t�F�N�g���o��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_WazaEffect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		apw->advance.nt.a_talk_id = A_TALK_WAZA_APPEAL;
		if(apw->advance.judge_reaction_type == JUDGE_REACTION_ICON_WEAR){
			apw->advance.nt.after_a_talk_id = A_TALK_JUDGE_LOOK;
		}
		else{
			apw->advance.nt.after_a_talk_id = A_TALK_NULL;
		}
		
		AWAZA_FirstMsg(apw, &apw->advance.wazapara, apw->advance.now_breeder);
		
		local->seq++;
		//break;
	case 1:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_WAZAEFFECT, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			apw->advance.nt.a_talk_id = A_TALK_NULL;
			apw->advance.nt.after_a_talk_id = A_TALK_NULL;
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�o�����Z�̕]�����s��(���o)
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_AppealReview(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
#if 0
	switch(local->seq){
	case 0:		//���ʂ𑗐M
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_APPEAL_REVIEW, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
#else
	enum{
		AR_INIT,
		AR_WAZA_CALC,
		AR_WAZA_REQ,
		AR_WAZA_WAIT,
		AR_KOUKA_CALC,
		AR_KOUKA_REQ,
		AR_KOUKA_WAIT,
		AR_SP_KOUKA_CALC,
		AR_SP_KOUKA_REQ,
		AR_SP_KOUKA_WAIT,
		AR_VOLTAGE_CALC,
		AR_VOLTAGE_REQ,
		AR_VOLTAGE_WAIT,
	};
	
	switch(local->seq){
	case AR_INIT:
		AWAZA_WazaParaBreederInit(apw, &apw->advance.wazapara, apw->advance.now_breeder);
		local->seq++;
		break;
	
	case AR_WAZA_CALC:
		AWAZA_BaseAP(apw, &apw->advance.wazapara, apw->advance.now_breeder);
		local->seq++;
		//break;
	case AR_WAZA_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_APPEAL_FIRST, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case AR_WAZA_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case AR_KOUKA_CALC:
		AWAZA_Kouka(apw, &apw->advance.wazapara, apw->advance.now_breeder, apw->advance.now_pos);
		local->seq++;
		//break;
	case AR_KOUKA_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_APPEAL_KOUKA, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case AR_KOUKA_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case AR_SP_KOUKA_CALC:
		AWAZA_KoukaSpecial(apw, &apw->advance.wazapara, apw->advance.now_breeder, apw->advance.now_pos);
		local->seq++;
		//break;
	case AR_SP_KOUKA_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_APPEAL_SPECIAL_KOUKA, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case AR_SP_KOUKA_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case AR_VOLTAGE_CALC:
		AWAZA_Voltage(apw, &apw->advance.wazapara, apw->advance.now_breeder, &apw->advance.nt);
		local->seq++;
		//break;
	case AR_VOLTAGE_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_APPEAL_VOLTAGE, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case AR_VOLTAGE_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	
	default:
		AWAZA_WazaParaBreederGameUpdate(apw, &apw->advance.wazapara, apw->advance.now_breeder);
		return ASRET_NEXT;
	}
#endif
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�|�P�����ޏ�
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_PokemonOut(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	int now;
	
	switch(local->seq){
	case 0:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_POKEMON_OUT, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_NEXT;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F���̃u���[�_�[�֐i�ޑO�̌㏈��
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_NextBreeder(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
//	if(apw->advance.voltage_calc >= VOLTAGE_POINT_FULL){
//		apw->a_game.voltage_total[apw->advance.judge_no] = 0;
//	}

	apw->a_game.breeder_end_count++;
	if(apw->a_game.breeder_end_count >= BREEDER_MAX){
		return ASRET_NEXT;
	}
	else{
		local->select_seq = ASEQ_SELECT_BREEDER;
		return ASRET_SELECT_SEQ;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�S���̉��Z���I�������ɔ��������鉉�Z����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_AllReviewAfter(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	enum{
		ARF_INIT,

		ARF_AFTERREVIEW_INIT,
		ARF_AFTERREVIEW_CALC,
		ARF_AFTERREVIEW_REQ,
		ARF_AFTERREVIEW_WAIT,
		ARF_AFTERREVIEW_END,

		ARF_JUDGESUFFER_INIT,
		ARF_JUDGESUFFER_MAIN,
		ARF_JUDGESUFFER_CALC,
		ARF_JUDGESUFFER_REQ,
		ARF_JUDGESUFFER_WAIT,
		ARF_JUDGESUFFER_NEXT,
		ARF_JUDGESUFFER_END,

		ARF_JUDGEWAZA_INIT,
		ARF_JUDGEWAZA_CALC,
		ARF_JUDGEWAZA_REQ,
		ARF_JUDGEWAZA_WAIT,
		ARF_JUDGEWAZA_NEXT,
		ARF_JUDGEWAZA_END,

		ARF_ENDREVIEW_INIT_UPDATE,
		ARF_ENDREVIEW_INIT,
		ARF_ENDREVIEW_CALC,
		ARF_ENDREVIEW_REQ,
		ARF_ENDREVIEW_WAIT,
		ARF_ENDREVIEW_END,
	};
	BOOL ret;
	
	switch(local->seq){
	case ARF_INIT:
		local->seq++;
		break;
	
	case ARF_AFTERREVIEW_INIT:
		apw->advance.now_breeder = apw->a_game.breeder_sort[local->work];
		apw->advance.now_pos = local->work;
		local->seq++;
		//break;
	case ARF_AFTERREVIEW_CALC:
		ret = AWAZA_KoukaAfterTiming(apw, &apw->advance.wazapara, 
			apw->advance.now_breeder, apw->advance.now_pos);
		if(ret == TRUE){
			local->seq++;
		}
		else{
			local->seq = ARF_AFTERREVIEW_END;
		}
		break;
	case ARF_AFTERREVIEW_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_REVIEW_AFTER, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case ARF_AFTERREVIEW_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case ARF_AFTERREVIEW_END:
		local->work++;
		if(local->work >= BREEDER_MAX){
			local->work = 0;
			local->seq++;
		}
		else{
			local->seq = ARF_AFTERREVIEW_INIT;
		}
		break;

	case ARF_JUDGESUFFER_INIT:
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				AWAZA_JudgeSuffer(apw, &apw->advance.wazapara, i, &apw->advance.nt);
			}
		}
		local->seq++;
		break;
	case ARF_JUDGESUFFER_MAIN:
		{//�R���I��
			int judge_counter[JUDGE_MAX];
			int judge_sort[JUDGE_MAX];
			int suffer_breeder[JUDGE_MAX][BREEDER_MAX];
			int i, j, t, breeder_no;
			
			for(i = 0; i < JUDGE_MAX; i++){
				judge_counter[i] = 0;
				judge_sort[i] = i;
				for(j = 0; j < BREEDER_MAX; j++){
					suffer_breeder[i][j] = BREEDER_MAX;
				}
			}
			for(i = 0; i < BREEDER_MAX; i++){
				breeder_no = apw->a_game.breeder_sort[i];
				judge_counter[apw->a_game.judge_no[breeder_no]]++;
				for(j = 0; j < BREEDER_MAX; j++){
					if(suffer_breeder[apw->a_game.judge_no[breeder_no]][j] == BREEDER_MAX){
						suffer_breeder[apw->a_game.judge_no[breeder_no]][j] = breeder_no;
						break;
					}
				}
			}
			
			//��萔���������Ƀ\�[�g
			for(i = 0; i < JUDGE_MAX - 1; i++){
				for(j = JUDGE_MAX - 1; j > i; j--){
					if(judge_counter[j-1] < judge_counter[j]){
						//���l������ւ�
						t = judge_counter[j];
						judge_counter[j] = judge_counter[j-1];
						judge_counter[j-1] = t;
						//�R���ԍ����ꂩ��
						t = judge_sort[j];
						judge_sort[j] = judge_sort[j-1];
						judge_sort[j-1] = t;
					}
				}
			}
			apw->advance.jsr.judge_no = judge_sort[local->work];
			for(i = 0; i < BREEDER_MAX; i++){
				apw->advance.jsr.suffer_breeder[i] = suffer_breeder[judge_sort[local->work]][i];
			}
			switch(judge_counter[local->work]){
			case 1:
				apw->advance.nt.a_talk_id = A_TALK_NO_JUDGE_SUFFER;
				break;
			case 2:
				apw->advance.nt.a_talk_id = A_TALK_JUDGE_SUFFER0002;
				break;
			case 3:
				apw->advance.nt.a_talk_id = A_TALK_JUDGE_SUFFER0003;
				break;
			case 4:
				apw->advance.nt.a_talk_id = A_TALK_JUDGE_SUFFER0004;
				break;
			default:
				local->seq = ARF_JUDGESUFFER_END;
				return ASRET_CONTINUE;
			}
		}
//		apw->advance.now_breeder = apw->a_game.breeder_sort[local->work];
//		apw->advance.now_pos = local->work;
		//apw->advance.nt.a_talk_id = A_TALK_JUDGE_LOOK;
		apw->advance.nt.after_a_talk_id = A_TALK_NULL;
		AT_MsgTagParaInitDataSet(apw, &apw->advance.nt.a_talk_tagpara, apw->advance.now_breeder);
		AT_MsgTagParaInitDataSet(apw, &apw->advance.nt.after_a_talk_tagpara, 
			apw->advance.now_breeder);
		
		local->seq++;
		//break;
	case ARF_JUDGESUFFER_CALC:
	#if 0	//��check �R�����Z�͂Ƃ肠�������� 2006.03.31(��)
		ret = AWAZA_KoukaJudgeSufferTiming(apw, &apw->advance.wazapara, 
			apw->advance.now_breeder, apw->advance.now_pos);
		if(ret == FALSE){
			AWAZA_JudgeSuffer(apw, &apw->advance.wazapara, apw->advance.now_breeder, 
				&apw->advance.nt);
		}
	#else
//		AWAZA_JudgeSuffer(apw, &apw->advance.wazapara, apw->advance.now_breeder, 
//			&apw->advance.nt);
	#endif
		local->seq++;
		break;
	case ARF_JUDGESUFFER_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_JUDGE_SUFFER, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case ARF_JUDGESUFFER_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			apw->advance.nt.a_talk_id = A_TALK_NULL;
			apw->advance.nt.after_a_talk_id = A_TALK_NULL;
			local->seq++;
		}
		break;
	case ARF_JUDGESUFFER_NEXT:
		local->work++;
		if(local->work < JUDGE_MAX){
			local->seq = ARF_JUDGESUFFER_MAIN;
		}
		else{
			local->seq++;
		}
		break;
	case ARF_JUDGESUFFER_END:
		local->work = 0;
		local->seq++;
		break;

	case ARF_JUDGEWAZA_INIT:
		apw->advance.now_breeder = apw->a_game.breeder_sort[local->work];
		apw->advance.now_pos = local->work;
		local->seq++;
		//break;
	case ARF_JUDGEWAZA_CALC:
		ret = AWAZA_KoukaJudgeSufferTiming(apw, &apw->advance.wazapara, 
			apw->advance.now_breeder, apw->advance.now_pos);
		if(ret == FALSE){
			local->seq = ARF_JUDGEWAZA_NEXT;
		}
		else{
			local->seq++;
		}
		break;
	case ARF_JUDGEWAZA_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_JUDGE_WAZA, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case ARF_JUDGEWAZA_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			apw->advance.nt.a_talk_id = A_TALK_NULL;
			apw->advance.nt.after_a_talk_id = A_TALK_NULL;
			local->seq++;
		}
		break;
	case ARF_JUDGEWAZA_NEXT:
		local->work++;
		if(local->work < BREEDER_MAX){
			local->seq = ARF_JUDGEWAZA_INIT;
		}
		else{
			local->seq++;
		}
		break;
	case ARF_JUDGEWAZA_END:
		local->work = 0;
		local->seq++;
		break;

	case ARF_ENDREVIEW_INIT_UPDATE:
		AWAZA_TimingBeforeAppUpdate(&apw->advance.wazapara);
		local->seq++;
		//break;
	case ARF_ENDREVIEW_INIT:
		apw->advance.now_breeder = apw->a_game.breeder_sort[local->work];
		apw->advance.now_pos = local->work;
		local->seq++;
		//break;
	case ARF_ENDREVIEW_CALC:
		ret = AWAZA_KoukaEndTiming(apw, &apw->advance.wazapara, 
			apw->advance.now_breeder, apw->advance.now_pos);
		if(ret == TRUE){
			local->seq++;
		}
		else{
			local->seq = ARF_ENDREVIEW_END;
		}
		break;
	case ARF_ENDREVIEW_REQ:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_REVIEW_END, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case ARF_ENDREVIEW_WAIT:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	case ARF_ENDREVIEW_END:
		local->work++;
		if(local->work >= BREEDER_MAX){
			local->work = 0;
			local->seq++;
		}
		else{
			local->seq = ARF_ENDREVIEW_INIT;
		}
		break;

	default:
		return ASRET_NEXT;
	}
	
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F���Z�I����̐R���R�����g
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_JudgeComment(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		local->seq++;
		break;
	case 1:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_JUDGE_COMMENT, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 2:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	default:
		return ASRET_NEXT;
	}
	
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F���݂̃^�[���I������
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_TurnEnd(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	int i;
	
	switch(local->seq){
	case 0:		//�I�����̃G�t�F�N�g�����s
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_TURNEND_EFF, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 1:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case 2:
		{
			int sort_waza_check;
			
			sort_waza_check = 0;
			for(i = 0; i < BREEDER_MAX; i++){
				if(apw->advance.wazapara.personal[i].next_sort != AWK_SORT_NONE){
					sort_waza_check++;	//�S�����\�[�g�Z���g�p���Ă���ꍇ�̓��b�Z�[�W�Ȃ�
				}
			}
			
			if(apw->a_game.turn < ACTIN_END_TURN - 1 && sort_waza_check < BREEDER_MAX){
				apw->advance.nt.a_talk_id = A_TALK_EXPLAIN_01;
			}
			else{
				apw->advance.nt.a_talk_id = A_TALK_NULL;
			}
		}
		apw->advance.nt.a_talk_bmpwin_close_wait = CONTEST_MESSAGE_END_WAIT;
		apw->advance.nt.a_talk_bmpwin_not_close = 0;
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_TALK, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 3:
		//if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	
	case 4:		//�p�����[�^�X�V
		AWAZA_WazaParaTurnGameUpdate(apw, &apw->advance.wazapara);
		
		//�u���[�_�[�\�[�g
		ACALC_BreederSort(&apw->a_game);
		
		//�Z�����X�V
		for(i = 0; i < BREEDER_MAX; i++){
			apw->a_game.waza_history[i] = apw->a_game.waza_no[i];
		}
		
		apw->a_game.turn++;

		local->seq++;
		break;
	
	case 5:		//�X�V�����p�����[�^��S���ɑ��M
		//�Ƃ肠����a_game��S�đ��M�B��ŕK�v�Ȃ��̂����ɕς��邩�� 2005.12.22(��) ��check
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_TURN_PARAM_UPDATE, &apw->a_game) == TRUE){
			local->seq++;
		}
		break;
	case 6:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;
	
	default:
		//�ŏI�^�[���m�F
		if(apw->a_game.turn >= ACTIN_END_TURN){
			local->select_seq = ASEQ_END;
			return ASRET_SELECT_SEQ;
		}
		else{
			apw->a_game.breeder_end_count = 0;
			local->select_seq = ASEQ_TURN_START;
			return ASRET_SELECT_SEQ;
		}
		break;
	}
	return ASRET_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�I������
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_End(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	switch(local->seq){
	case 0:
		{
			int i;
			for(i = 0; i < BREEDER_MAX; i++){
				apw->consys->c_game.score[i].actin = apw->a_game.app_total[i];
			}
		}
		local->seq++;
		//break;

	case 1:
		apw->advance.nt.a_talk_id = A_TALK_EXPLAIN_02;
		apw->advance.nt.after_a_talk_id = A_TALK_NULL;
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_ENDING_EFFECT, &apw->advance) == TRUE){
			local->seq++;
		}
		break;
	case 2:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			local->seq++;
		}
		break;

	case 3:
		if(CO_OrderSet(&apw->cow, apw, AORDER_NO_ACTIN_EXIT, NULL) == TRUE){
			local->seq++;
		}
		break;
	default:
//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
		if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
				apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
			return ASRET_END;
		}
		break;
	}
	return ASRET_CONTINUE;
}


#ifdef PM_DEBUG //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   ���Z�̓V�[�P���X�F�Z�G�t�F�N�g�f�o�b�O
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   local		���[�J�����[�N�ւ̃|�C���^
 *
 * @retval  �p������t���O
 */
//--------------------------------------------------------------
static int ActinSeq_DebugWazaEffect(ACTIN_PROC_WORK *apw, ACTIN_LOCAL_WORK *local)
{
	ACTIN_DEBUG_WORK *debug;
	enum{
		DEBUG_SEQ_INIT,
		DEBUG_SEQ_WAZANAME_PUT,
		DEBUG_SEQ_KEY_WAIT,
		DEBUG_SEQ_WAZAEFF,
		
		DEBUG_SEQ_END,
	};
	
	debug = &apw->debug;
	switch(local->seq){
	case DEBUG_SEQ_INIT:
		GF_BGL_BmpWinAdd(apw->sys.bgl, &debug->win, ACTIN_FRAME_WIN, 
			11, 0x1, 20, 4, BMPWIN_DEBUG_COLOR, BMPWIN_DEBUG_CGX_OFFSET);
		
		debug->wazano = 1;

		local->seq++;
		break;
	case DEBUG_SEQ_WAZANAME_PUT:
		GF_BGL_BmpWinDataFill(&debug->win, 0xff);
		{
			STRBUF *wazaname_p, *num_p;
			
			wazaname_p = MSGDAT_UTIL_GetWazaName(debug->wazano, HEAPID_ACTIN);
			GF_STR_PrintSimple(&debug->win, FONT_SYSTEM, wazaname_p, 0, 0, MSG_ALLPUT, NULL);
			STRBUF_Delete(wazaname_p);
			
			num_p = STRBUF_Create(32, HEAPID_ACTIN);
			STRBUF_SetNumber(num_p, debug->wazano, 3, NUMBER_DISPTYPE_SPACE, 
				NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintSimple(&debug->win, FONT_SYSTEM, num_p, 0, 16, MSG_ALLPUT, NULL);
			STRBUF_Delete(num_p);
		}
		local->seq++;
		break;
	case DEBUG_SEQ_KEY_WAIT:
		if(sys.trg & PAD_BUTTON_B){
			local->seq = DEBUG_SEQ_END;
			break;
		}
		else if(sys.repeat & PAD_KEY_RIGHT){
			debug->wazano++;
			if(debug->wazano > WAZANO_MAX){
				debug->wazano = 1;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.repeat & PAD_KEY_LEFT){
			debug->wazano--;
			if(debug->wazano < 1){
				debug->wazano = WAZANO_MAX;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.repeat & PAD_BUTTON_R){
			debug->wazano += 10;
			if(debug->wazano > WAZANO_MAX){
				debug->wazano = 1;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.repeat & PAD_BUTTON_L){
			debug->wazano -= 10;
			if(debug->wazano < 1){
				debug->wazano = WAZANO_MAX;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.repeat & PAD_KEY_DOWN){
			debug->wazano += 100;
			if(debug->wazano > WAZANO_MAX){
				debug->wazano = 1;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.repeat & PAD_KEY_UP){
			debug->wazano -= 100;
			if(debug->wazano < 1){
				debug->wazano = WAZANO_MAX;
			}
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
		}
		else if(sys.trg & PAD_BUTTON_A){
			debug->sub_seq = 0;
			local->seq = DEBUG_SEQ_WAZAEFF;
			break;
		}
		break;
	case DEBUG_SEQ_WAZAEFF:
		switch(debug->sub_seq){
		case 0:
			GF_BGL_BmpWinOff(&debug->win);
			
			//SelectBreeder
			apw->advance.now_breeder = apw->consys->c_game.my_breeder_no;
			apw->advance.now_pos = 0;
			apw->advance.judge_no = 0;
			apw->advance.judge_reaction_type = JUDGE_REACTION_ICON_NOMINATION;
			apw->advance.wazapara.personal[apw->advance.now_breeder].wazano = debug->wazano;

			debug->sub_seq++;
			break;
		case 1:	//PokemonIn
			if(CO_OrderSet(&apw->cow, apw, AORDER_NO_POKEMON_IN, &apw->advance) == TRUE){
				debug->sub_seq++;
			}
			break;
		case 2:
	//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
			if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
					apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
				debug->sub_seq++;
			}
			break;
		case 3:	//WazaEffect
			apw->advance.nt.a_talk_id = A_TALK_NULL;
			apw->advance.nt.after_a_talk_id = A_TALK_NULL;
			if(CO_OrderSet(&apw->cow, apw, AORDER_NO_WAZAEFFECT, &apw->advance) == TRUE){
				debug->sub_seq++;
			}
			break;
		case 4:
			if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
					apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
				debug->sub_seq++;
			}
			break;
		case 5:	//PokemonOut
			if(CO_OrderSet(&apw->cow, apw, AORDER_NO_POKEMON_OUT, &apw->advance) == TRUE){
				debug->sub_seq++;
			}
			break;
		case 6:
	//		if(CO_RequestBitNumCheck(&apw->cow) == 0){
			if(CO_AnswerCountCheck(&apw->cow, apw->consys->c_game.player_num, 
					apw->consys->c_game.my_breeder_no, apw->consys->c_game.server_no) == TRUE){
				debug->sub_seq++;
			}
			break;
		default:
			debug->sub_seq = 0;
			local->seq = DEBUG_SEQ_WAZANAME_PUT;
			break;
		}
		break;
		
	case DEBUG_SEQ_END:
	default:
		GF_BGL_BmpWinOff(&debug->win);
		GF_BGL_BmpWinDel(&debug->win);

		local->select_seq = ASEQ_USER_SELECT;
		return ASRET_SELECT_SEQ;
	}
	return ASRET_CONTINUE;
}
#endif	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

