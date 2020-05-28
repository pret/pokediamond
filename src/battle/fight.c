
//============================================================================================
/**
 * @file	fight.c
 * @bfief	�퓬���C���v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================


#include "common.h"

#include "battle/battle_server.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/client.h"
#include "battle/client_tool.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/shinka.h"
#include "battle/trtype_def.h"
#include "fight_def.h"
#include "ground.h"
#include "itemtool/myitem.h"
#include "system/brightness.h"
#include "system/window.h"
#include "field/field.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/softsprite.h"
#include "system/pm_rtc.h"

#include "system/fontproc.h"
#include "system/font_arc.h"
#include "system/palanm.h"

#include "system/pmfprint.h"
#include "system/msgdata.h"
#include "system/msg_ds_icon.h"
#include "system/wipe.h"
#include "system/wordset.h"
#include "system/snd_tool.h"

#include "system/zukanwork.h"

#include "application/app_tool.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "battle/graphic/batt_bg_def.h"
#include "battle_input.h"
#include "system/numfont.h"
#include "battle/battle_tcb_pri.h"

#include "pokeanime/p_anm_sys.h"

#include "msgdata/msg.naix"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/comm_wifihistory.h"
#include "field/comm_union_beacon.h"
#include "comm_command_battle.h"
#include "battle_snd_def.h"

#include "gflib/mmap_get.h"

#include "savedata/perapvoice.h"
#include "savedata/wifihistory.h"

#include "msgdata/msg_fightmsg_dp.h"

#include "system/pm_overlay.h"
#include <nitro/sinit.h>
FS_EXTERN_OVERLAY(battle_bag_list);
FS_EXTERN_OVERLAY(vs_demo);
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_zukan);

//============================================================================================
/**
 * �萔�錾
 */
//============================================================================================

#define	HEAP_CHECK

//#define DEBUG_PRINT			//�V�[�P���X�\����ON

#define	BATTLE_BMP_WIN_MAX		(3)		///<�퓬�Ŏg�p����BMPWIN��MAX
#define	BATTLE_CELL_TRANS_MAX	(2)		///<�퓬�Ŏg�p����CellTrans��MAX

#define BATTLE_BG1_V_START_OFFSET	( -51 )	///<�퓬�J�n����BG1��VOFFSET�̒l 

enum {
	SEQ_INIT = 0,
	SEQ_SIO_INIT,
	SEQ_SIO_MAIN,
	SEQ_FIGHT_LIST_DEMO_INIT,
	SEQ_FIGHT_LIST_DEMO_MAIN,
	SEQ_FIGHT_MENU_DEMO_INIT,
	SEQ_FIGHT_MENU_DEMO_MAIN,
	SEQ_FIGHT_SYNCRO_WAIT,
	SEQ_FIGHT_INIT,
	SEQ_FIGHT_MAIN,
	SEQ_WIN_LOSE_INIT,
	SEQ_WIN_LOSE_MAIN,
	SEQ_WIN_LOSE_WAIT,
	SEQ_SHINKA_INIT,
	SEQ_SHINKA_MAIN,
	SEQ_EXIT
};

static	const	u32	BattleServerVersion=0x100;		//�퓬�T�[�o�o�[�W�����@1.00

//============================================================================================
/**
 * �v���g�^�C�v�錾
 */
//============================================================================================

BOOL BattleSystemProc(PROC *proc,int *seq);
void	FightScreenTransition(BATTLE_WORK *bw);
void	FightScreenEnd(BATTLE_WORK *bw);
void	FightScreenRecover(BATTLE_WORK *bw);
void	FightScreenPokemonGetEnd(BATTLE_WORK *bw);
void	FightScreenPokemonGet(BATTLE_WORK *bw);

static	void	FightInit(PROC *proc);
static	int		FightMain(PROC *proc);
static	void	FightEnd(PROC *proc);

static	BOOL	FightListDemoInit(PROC *proc);
static	BOOL	FightListDemoMain(PROC *proc);

static	BOOL	FightMenuDemoInit(PROC *proc);
static	BOOL	FightMenuDemoMain(PROC *proc);

static	BOOL	FightWinLoseDemoInit(PROC *proc);
static	BOOL	FightWinLoseDemoMain(PROC *proc);

static	void	FightSioInit(PROC *proc,BATTLE_PARAM *bp);
static	BOOL	FightSioMain(PROC *proc);
static	void	FightSioEnd(PROC *proc);

static	void	FightBGCreate(BATTLE_WORK *bw, GF_BGL_INI *bgl);
static	void	FightOBJCreate(BATTLE_WORK *bw);
static	void	FightBGEnd(GF_BGL_INI *bgl);
static	void	FightOBJEnd(BATTLE_WORK *bw);

static	void	FightSystemBoot(BATTLE_WORK *bw,BATTLE_PARAM *bp);

static	void	FightParticleInit(void);	//�p�[�e�B�N��������
static	void	FightVBlank(void *work);
static	void	FightSioVBlank(void *work);

static void FightUpdate(TCB_PTR tcb, void *work);

static void FightPinchSECheck(TCB_PTR tcb, void *work);

static GF_G3DMAN * Fight_3D_Init(void);
static void Fight_3D_Exit(GF_G3DMAN *g3Dman);
static void FightSimpleSetUp(void);
static void	FightMsgPrintModeSet(BATTLE_WORK *bw);
static void StartMsgWinMove( TCB_PTR tcb, void *work );

static	BOOL	BossTrTypeCheck(u16 tr_type);
static	void	FightSioServerBootCheck(BATTLE_WORK *bw,BATTLE_PARAM *bp);

//============================================================================================
/**
 * CL_ACT�p�f�[�^
 */
//============================================================================================

static	const TCATS_OAM_INIT BattleTcats = {
	BATTLE_OAM_START_MAIN, BATTLE_OAM_END_MAIN,
	BATTLE_OAM_AFFINE_START_MAIN, BATTLE_OAM_AFFINE_END_MAIN,
	BATTLE_OAM_START_SUB, BATTLE_OAM_END_SUB,
	BATTLE_OAM_AFFINE_START_SUB, BATTLE_OAM_AFFINE_END_SUB,
};

static	const TCATS_CHAR_MANAGER_MAKE BattleCcmm = {
	BATTLE_CHAR_MAX,
	BATTLE_CHAR_VRAMSIZE_MAIN,
	BATTLE_CHAR_VRAMSIZE_SUB,
	GX_OBJVRAMMODE_CHAR_1D_64K,
	GX_OBJVRAMMODE_CHAR_1D_32K
};

const TCATS_RESOURCE_NUM_LIST BattleResourceList = {
	BATTLE_OAMRESOURCE_CHAR_MAX,
	BATTLE_OAMRESOURCE_PLTT_MAX,
	BATTLE_OAMRESOURCE_CELL_MAX,
	BATTLE_OAMRESOURCE_CELLANM_MAX,
	BATTLE_OAMRESOURCE_MCELL_MAX,
	BATTLE_OAMRESOURCE_MCELLANM_MAX,
};

//============================================================================================
/**
 *
 *	�퓬PROC�֐�
 *
 * @param
 */
//============================================================================================
BOOL BattleSystemProc(PROC *proc,int * seq)
{
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);

	switch( *seq ){
	case SEQ_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_INIT\n");
#endif
		{
			sys_CreateHeap(HEAPID_BASE_APP,HEAPID_BATTLE,BATTLE_ALLOC_SIZE);
		}
		if(bp->fight_type&FIGHT_TYPE_SIO){
			*seq = SEQ_SIO_INIT;
		}
		else{
			*seq = SEQ_FIGHT_LIST_DEMO_INIT;
		}
		break;
	case SEQ_SIO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SIO_INIT\n");
#endif
		FightSioInit(proc,bp);
		// �n���V�o�^
        Comm_WifiHistoryCheck( bp->wifihistory );
		//�ʐM�ΐ�񐔂��J�E���g�A�b�v
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BATTLE);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BATTLE);
		}
		*seq = SEQ_SIO_MAIN;
		break;
	case SEQ_SIO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SIO_MAIN\n");
#endif
		if(FightSioMain(proc)==TRUE){
			FightSioEnd(proc);
			*seq = SEQ_FIGHT_LIST_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_LIST_DEMO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_LIST_DEMO_INIT\n");
#endif
		if(FightListDemoInit(proc)==TRUE){
			*seq = SEQ_FIGHT_LIST_DEMO_MAIN;
		}
		else{
			*seq = SEQ_FIGHT_MENU_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_LIST_DEMO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_LIST_DEMO_MAIN\n");
#endif
		if(FightListDemoMain(proc)==TRUE){
			*seq = SEQ_FIGHT_MENU_DEMO_INIT;
		}
		break;
	case SEQ_FIGHT_MENU_DEMO_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MENU_DEMO_INIT\n");
#endif
		if(FightMenuDemoInit(proc)==TRUE){
			*seq = SEQ_FIGHT_MENU_DEMO_MAIN;
		}
		else{
			*seq = SEQ_FIGHT_INIT;
		}
		break;
	case SEQ_FIGHT_MENU_DEMO_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MENU_DEMO_MAIN\n");
#endif
		if(FightMenuDemoMain(proc)==TRUE){
			Overlay_UnloadID(FS_OVERLAY_ID(vs_demo));
			*seq = SEQ_FIGHT_SYNCRO_WAIT;
			CommTimingSyncStart( COMM_BATTLE_START_WAIT_NUM );
		}
		break;
	case SEQ_FIGHT_SYNCRO_WAIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_SYNCRO_WAIT\n");
#endif
		if(CommIsTimingSync( COMM_BATTLE_START_WAIT_NUM )){
			*seq = SEQ_FIGHT_INIT;
		}
		break;
	case SEQ_FIGHT_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_INIT\n");
#endif
		Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);
		FightInit(proc);
		*seq = SEQ_FIGHT_MAIN;
		break;
	case SEQ_FIGHT_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_FIGHT_MAIN\n");
#endif
		if(FightMain(proc)==1){
			FightEnd(proc);
			*seq = SEQ_WIN_LOSE_INIT;
		}
		break;
	case SEQ_WIN_LOSE_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_INIT\n");
#endif
		if(FightWinLoseDemoInit(proc)==TRUE){
			*seq = SEQ_WIN_LOSE_MAIN;
		}
		else{
			sys_DeleteHeap(HEAPID_BATTLE);
			*seq = SEQ_SHINKA_INIT;
		}
		break;
	case SEQ_WIN_LOSE_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_MAIN\n");
#endif
		if(FightWinLoseDemoMain(proc)==TRUE){
			Overlay_UnloadID(FS_OVERLAY_ID(vs_demo));
			sys_DeleteHeap(HEAPID_BATTLE);
			CommTimingSyncStart( COMM_BATTLE_WIN_LOSE_WAIT_NUM );
			*seq = SEQ_WIN_LOSE_WAIT;
		}
		break;
	case SEQ_WIN_LOSE_WAIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_WIN_LOSE_WAIT\n");
#endif
		if(CommIsTimingSync( COMM_BATTLE_WIN_LOSE_WAIT_NUM )){
			*seq = SEQ_EXIT;
		}
		break;
	case SEQ_SHINKA_INIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SHINKA_INIT\n");
#endif
		{
			int				sel_mons_no;
			int				after_mons_no;
			int				shinka_cond;
			POKEMON_PARAM	*pp;

			after_mons_no=BattleWorkShinkaCheck(bp,&sel_mons_no,&shinka_cond);

			if(after_mons_no){
				sys_CreateHeap(HEAPID_BASE_APP,HEAPID_ITEMSHINKA,0x30000);
				pp=PokeParty_GetMemberPointer(bp->poke_party[CLIENT_NO_MINE],sel_mons_no);
				bp->work=ShinkaInit(bp->poke_party[CLIENT_NO_MINE],pp,after_mons_no,
									bp->config,bp->contest_see_flag,bp->zw,bp->my_item,bp->record,bp->poketch_data,
									shinka_cond,SHINKA_STATUS_FLAG_CANCEL_ON|SHINKA_STATUS_FLAG_BATTLE_MODE,HEAPID_ITEMSHINKA);
				*seq = SEQ_SHINKA_MAIN;
			}
			else{
				*seq = SEQ_EXIT;
			}
		}
		break;
	case SEQ_SHINKA_MAIN:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_SHINKA_MAIN\n");
#endif
		{
			SHINKA_WORK *sw=(SHINKA_WORK *)bp->work;
			if(ShinkaEndCheck(sw)==TRUE){
				ShinkaEnd(sw);
				sys_DeleteHeap(HEAPID_ITEMSHINKA);
				*seq = SEQ_SHINKA_INIT;
			}
		}
		break;
	case SEQ_EXIT:
#ifdef DEBUG_PRINT
		OS_Printf("SEQ_EXIT\n");
#endif
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
/**
 *
 *	�퓬��ʕʏ������ڏ����i�o�b�O�Ƃ����X�g�Ƃ��ɍs���Ƃ��ɍ폜����֘A���܂Ƃ߂Ă���j
 *
 * @param
 */
//============================================================================================
void	FightScreenTransition(BATTLE_WORK *bw)
{
//	sys_VBlankFuncChange(NULL,NULL);

	BINPUT_SystemFree(bw->bip);

	//�T�u���
	BINPUT_FrameExit(bw->bgl);

	//VRAM���������N�G�X�g
	bw->bl_vram_init_req=1;

//	FightBGEnd(bw->bgl);
//	FightOBJEnd(bw);
	
//	CATS_ResourceDestructor_S(bw->csp,bw->crp);
//	CATS_FreeMemory(bw->csp);

//	DellVramTransferManager();

	//���X�g�A�o�b�O��ʂł��{�^���t�H���g��ʂɃ��[�h����\��������̂�Unload
	FontProc_UnloadFont(FONT_BUTTON);
	BattleWorkProcModeSet(bw,BW_PROC_MODE_BAG_LIST);
	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	Overlay_Load(FS_OVERLAY_ID(battle_bag_list), OVERLAY_LOAD_NOT_SYNCHRONIZE);
}

//============================================================================================
/**
 *
 *	�퓬��ʍ폜�����i�o�b�O�Ƃ����X�g�Ƃ��ɍs���Ƃ��ɍ폜����֘A���番���j
 *
 * @param
 */
//============================================================================================
void	FightScreenEnd(BATTLE_WORK *bw)
{
	sys_VBlankFuncChange(NULL,NULL);

	BINPUT_SystemFree(bw->bip);

	GF_BGL_BmpWinDel(&bw->win[TALK_WIN_NO]);

	FightBGEnd(bw->bgl);
	FightOBJEnd(bw);
	
	CATS_ResourceDestructor_S(bw->csp,bw->crp);
	CATS_FreeMemory(bw->csp);

	DellVramTransferManager();

	//���X�g�A�o�b�O��ʂł��{�^���t�H���g��ʂɃ��[�h����\��������̂�Unload
	FontProc_UnloadFont(FONT_BUTTON);
}

//============================================================================================
/**
 *
 *	�퓬��ʕ��A����
 *
 * @param
 */
//============================================================================================
void	FightScreenRecover(BATTLE_WORK *bw)
{
	Overlay_UnloadID(FS_OVERLAY_ID(battle_bag_list));
	Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	BattleWorkProcModeSet(bw,BW_PROC_MODE_FIGHT);

//	MI_CpuFill16((void*)HW_BG_PLTT, 0x0000, HW_BG_PLTT_SIZE);
	MI_CpuFill16((void*)GF_MMAP_SubBgPlttAddr(), 0x0000, GF_MMAP_SubBgPlttSize());


	//�퓬���͉�ʃV�X�e�����[�N�m��
	bw->bip=BINPUT_SystemInit(bw,BattleWorkMySexGet(bw,CommGetCurrentID()));

	//���X�g�A�o�b�O��ʂ�Unload�����\��������̂Ńt�H���g���ă��[�h
	FontProc_LoadFont(FONT_BUTTON, HEAPID_BATTLE);

	//VRAM�ݒ菉�������N�G�X�g
	bw->vram_init_req=1;

//	initVramTransferManagerHeap(BATTLE_VRAM_TRANSFER_TASK_NUM,HEAPID_BATTLE);
//
//	GF_Disp_GX_VisibleControlInit();

	//VRAM�ݒ�
//	{
//		GF_BGL_DISPVRAM vramSetTable = {
//			GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
//			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
//			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
//			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
//			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
//			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
//			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
//			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
//			GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
//			GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
//		};
//		GF_Disp_SetBank( &vramSetTable );
//
//		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
//		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
//	}
	//�T�u��ʃt���[���ݒ�
	{
		BINPUT_DefaultFrameSet(bw->bgl);
	}
//	GF_Disp_DispOn();

//	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

//	FightBGCreate(bw, bw->bgl);
//	GF_BGL_BmpWinAdd(bw->bgl,bw->win,GF_BGL_FRAME1_M,0x02,0x13,27,4,0x0b,TALK_WIN_CGX_SIZ+1);
//	GF_BGL_BmpWinDataFill(bw->win,0xff);
//	BmpTalkWinWrite(bw->win,WINDOW_TRANS_ON,1,0x0a);

//	bw->csp=CATS_AllocMemory(HEAPID_BATTLE);
//	CATS_SystemInit(bw->csp,&BattleTcats,&BattleCcmm,BATTLE_OAM_PLTT_MAX);
//	bw->crp=CATS_ResourceCreate(bw->csp);
//	CATS_ClactSetInit(bw->csp, bw->crp, BATTLE_ACTOR_MAX);
//	CATS_ResourceManagerInit(bw->csp,bw->crp,&BattleResourceList);

	//�T�u���		�A�N�^�[�V�X�e��������Ă���Ă�ł�������
	BINPUT_DefaultDataSet(bw->bip);
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL, TRUE, NULL);
	BINPUT_StockBallActorResourceLoad(bw->bip);

//	FightOBJCreate(bw);

//	SoftSpriteRecover(bw->soft_sprite);
	//��b�E�C���h�E�̃J�[�\���L�������ē]��
	PokeFontTrgCursorCgxSet(TALK_WIN_CGX_START);

	FightMsgPrintModeSet(bw);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(bw->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
}

//============================================================================================
/**
 *
 *	�퓬��ʍ폜�����i�|�P�����Q�b�g���̐}�Ӊ�ʂɍs���Ƃ��ɍ폜����j
 *
 * @param
 */
//============================================================================================
void	FightScreenPokemonGetEnd(BATTLE_WORK *bw)
{
	GF_BGL_BmpWinDel(&bw->win[TALK_WIN_NO]);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit(bw->bgl, GF_BGL_FRAME3_M );

//	FightBGEnd(bw->bgl);
//	FightOBJEnd(bw);

	BattleWorkGaugeOff(bw);
}

//============================================================================================
/**
 *
 *	�|�P�����ߊl��ʐ���
 *
 * @param
 */
//============================================================================================
void	FightScreenPokemonGet(BATTLE_WORK *bw)
{
#if 0
	//VRAM�ݒ�
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
			GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
		};
		GF_Disp_SetBank( &vramSetTable );

		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}
#endif
#if 0
	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}
#endif

	// �u�����h�ݒ�
	{
		bw->bld_init_req=1;
	}

	//���C����ʃt���[���ݒ�
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
//				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_WINDOW, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_EFFECT, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bw->bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bw->bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}

	//�w�i�O���t�B�b�N�f�[�^���[�h
	{
		WINTYPE	win_type;

		win_type=BattleWorkConfigWinTypeGet(bw);

		TalkWinGraphicNullSet(bw->bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN+bw->bg_id,bw->bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bw->pfd, ARC_BATT_BG, BATT_BG00_D_NCLR+(bw->bg_id*3)+BattleWorkTimeZoneOffsetGet(bw), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0, 0);
		PaletteWorkSet_Arc(bw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);
		PaletteWorkSet_Arc(bw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, 0x0b*0x10);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bw->bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
	}

	//�E�C���h�E�}�X�N�ݒ�̏�����
	{
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE,NULL);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE,NULL);
	}

	GF_Disp_DispOn();

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	sys_VBlankFuncChange(FightVBlank,bw);

	//VRAM�ݒ菉�������N�G�X�g
	bw->vram_init_req=1;

	GF_BGL_BmpWinAdd(bw->bgl,bw->win,GF_BGL_FRAME1_M,0x02,0x13,27,4,0x0b,TALK_WIN_CGX_SIZ+1);
	GF_BGL_BmpWinDataFill(bw->win,0xff);
	BmpTalkWinWrite(&bw->win[TALK_WIN_NO],WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	FightMsgPrintModeSet(bw);
}

//============================================================================================
/**
 *	�G���J�E���g���̔w�i�F�̏����l
 *
 * @param
 */
//============================================================================================
static	const	int	EncountFirstColor[][3]={
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_BASIC			//����
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_SEA				//�C
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_CITY			//�X
	{GX_RGB(11,21,5),GX_RGB(11,21,5),GX_RGB(11,21,5)},		//BG_ID_FOREST			//�X��
	{0x7b51,GX_RGB(30,17,0),GX_RGB(0,16,23)},				//BG_ID_MOUNTAIN		//�R�x
	{GX_RGB(31,26,31),GX_RGB(31,26,22),GX_RGB(24,22,22)},	//BG_ID_SNOW_MOUNTAIN	//��R
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_A			//�����`
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_B			//�����a
	{0x7fff,0x7fff,0x7fff},									//BG_ID_ROOM_C			//�����b
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_A			//���A�`
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_B			//���A�a
	{GX_RGB(5,5,7),GX_RGB(5,5,7),GX_RGB(5,5,7)},			//BG_ID_CAVE_C			//���A�b
};

//============================================================================================
/**
 * @param
 */
//============================================================================================
static	void	FightInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	SOFT_SPRITE_ARC	ssa;
	int				i;
	RTCDate date;
	RTCTime time;
	u32 seed;

	MI_CpuFill16((void*)GF_MMAP_MainBgPlttAddr(), 0x0000, GF_MMAP_MainBgPlttSize());
	MI_CpuFill16((void*)GF_MMAP_SubBgPlttAddr(), 0x0000, GF_MMAP_SubBgPlttSize());

	//�����_���̎��ޔ�
	bw->seed_temp=gf_get_seed();

	//�����_���̎���擾
	GF_RTC_GetDateTime(&date, &time);
	seed = date.year + date.month * 0x100 * date.day * 0x10000
		+ time.hour * 0x10000 + (time.minute + time.second) * 0x1000000
		+ sys.vsync_counter;
	gf_srand(seed);

	//3D�`��n�̏�����
	//simple_3DBGInit(HEAPID_BATTLE);
	bw->g3Dman = Fight_3D_Init();

	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	FontProc_LoadFont(FONT_BUTTON, HEAPID_BATTLE);
	bw->numfont_hp = NUMFONT_Create(0xe, 1, 0xf, HEAPID_BATTLE);
#if 1	//���x����numfont_hp�Ɠ��������g�p����悤�ɂȂ��� 2005.11.10(��)	��check
	bw->numfont_lv = bw->numfont_hp;
#else
	bw->numfont_lv = NUMFONT_Create(0xe, 1, 0xf, HEAPID_BATTLE);
#endif
	
	bw->pfd = PaletteFadeInit(HEAPID_BATTLE);
	PaletteTrans_AutoSet(bw->pfd, TRUE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_MAIN_BG, 0x200, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_SUB_BG, 0x200, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_MAIN_OBJ, BATTLE_MAIN_OBJPAL_SIZE, HEAPID_BATTLE);
	PaletteFadeWorkAllocSet(bw->pfd, FADE_SUB_OBJ, 0x200, HEAPID_BATTLE);
	
	bw->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	bw->win=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,BATTLE_BMP_WIN_MAX);

	//�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@���m��
	for(i=0;i<CLIENT_MAX;i++){
		bw->exchr_param[i].exchr_buffer=sys_AllocMemory(HEAPID_BATTLE,EXCHR_BUFFER_SIZE);
	}

	initVramTransferManagerHeap(BATTLE_VRAM_TRANSFER_TASK_NUM,HEAPID_BATTLE);

	//�퓬���͉�ʃV�X�e�����[�N�m��
	bw->bip=BINPUT_SystemInit(bw,BattleWorkMySexGet(bw,CommGetCurrentID()));

	FightBGCreate(bw,bw->bgl);
	GF_BGL_BmpWinAdd(bw->bgl,&bw->win[TALK_WIN_NO],GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(&bw->win[TALK_WIN_NO],0xff);
	BmpTalkWinWrite(&bw->win[TALK_WIN_NO],WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	bw->csp=CATS_AllocMemory(HEAPID_BATTLE);
	CATS_SystemInit(bw->csp,&BattleTcats,&BattleCcmm,BATTLE_OAM_PLTT_MAX);
	//�ʐM�A�C�R���p�ɃL�������p���b�g����
	CLACT_U_WmIcon_SetReserveAreaCharManager(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
	CLACT_U_WmIcon_SetReserveAreaPlttManager(NNS_G2D_VRAM_TYPE_2DMAIN);
	bw->crp=CATS_ResourceCreate(bw->csp);
	CATS_ClactSetInit(bw->csp, bw->crp, BATTLE_ACTOR_MAX);
	CATS_ResourceManagerInit(bw->csp,bw->crp,&BattleResourceList);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(bw->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);

	BINPUT_DefaultDataSet(bw->bip);
	//�T�u���		�A�N�^�[�V�X�e��������Ă���Ă�ł�������
#if 0	//��l���w�i�͕\�����Ȃ��悤�ɂ���	2006.04.18(��) matsuda
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL_MISSING_PLAYER, TRUE, NULL);
	BINPUT_PlayerBG_SetX(bw->bip, 256);
	BINPUT_EffBGWallSet(bw->bip);
#else
	BINPUT_CreateBG(bw->bip, BINPUT_TYPE_WALL, TRUE, NULL);
#endif
	BINPUT_StockBallActorResourceLoad(bw->bip);

	bw->soft_sprite=SoftSpriteInit(HEAPID_BATTLE);
	SoftSpritePaletteTransParamSet(bw->soft_sprite,0,SOFT_SPRITE_COL_SIZE);	//�e�̕����]������悤�ɃT�C�Y��ύX

	BattleWorkGaugeInit(bw);	//HP�Q�[�W������

	FightParticleInit();	//�p�[�e�B�N��������
	bw->wsp=WES_Create(HEAPID_BATTLE);

	FightOBJCreate(bw);

	InitTPSystem();			// �^�b�`�p�l���V�X�e��������
	InitTPNoBuff(4);

	//���b�Z�[�W�}�l�[�W���쐬
	bw->fight_msg=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_fightmsg_dp_dat,HEAPID_BATTLE);
	bw->attack_msg=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_atkmsg_dat,HEAPID_BATTLE);
	//�P��o�b�t�@�쐬
	bw->wordset=WORDSET_Create(HEAPID_BATTLE);

	bw->msg_buf=STRBUF_Create(BATTLE_MESSAGE_BUF_SIZE,HEAPID_BATTLE);
	
	//�p���b�g�f�[�^��ޔ�
	MI_CpuCopy16(PaletteWorkDefaultWorkGet(bw->pfd,FADE_MAIN_BG),&bw->push_bg_palette[0],0x20*7);
	MI_CpuCopy16(PaletteWorkDefaultWorkGet(bw->pfd,FADE_MAIN_OBJ),&bw->push_obj_palette[0],0x20*7);

	{
		int	time;

		time=BattleWorkTimeZoneOffsetGet(bw);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0,112);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0x0c*16,0x0c*16+4*16);
		PaletteWork_Clear(bw->pfd,FADE_MAIN_OBJ,FADEBUF_ALL,EncountFirstColor[bw->bg_id][time],0,BATTLE_MAIN_OBJPAL_COLOR_NUM-1);
	}

	PaletteWork_Clear(bw->pfd,FADE_MAIN_BG,FADEBUF_TRANS,0x0000,0x0a*16,0x0a*16+2*16);
	PaletteWork_Clear(bw->pfd,FADE_SUB_BG,FADEBUF_TRANS,0xffff,0,255);
	PaletteWork_Clear(bw->pfd,FADE_SUB_OBJ,FADEBUF_TRANS,0xffff,0,255);

	//���b�Z�[�W�E�C���h�E�pDS�A�C�R���p���b�g�A�j��
	bw->msg_icon=MSG_DsIconFlashAdd(bw->pfd,MSG_DSI_MAINDISP,0x0b,HEAPID_BATTLE);
	MSG_DsIconFlashReq(bw->msg_icon,MSG_DSI_REQ_STOP);

	bw->update_tcb     = TCB_Add(FightUpdate, bw, TCBPRI_FIGHT_UPDATE);
	bw->pinch_tcb      = TCB_Add(FightPinchSECheck, bw, TCBPRI_PINCH_SE_CHECK);

	// �퓬�J�n���Ƀ��b�Z�[�W�E�C���h�E��������X�N���[��������^�X�N�̋N��
	bw->msgwinmove_tcb = VIntrTCB_Add( StartMsgWinMove, bw, TCBPRI_MSG_WIN_MOVE );
	bw->bg1_scroll     = BATTLE_BG1_V_START_OFFSET;							// �X�N���[�������l



	FightMsgPrintModeSet(bw);

	//�o�b�O��ʃJ�[�\���ʒu�̏�����
	MyItem_BattleBagCursorPosInit(BattleWorkBagCursorGet(bw));

	//�|�P�����v���O�����A�j���V�X�e�����[�N����
	bw->pasp=PokeAnm_AllocMemory(HEAPID_BATTLE,CLIENT_MAX,0);

	//�Z���]���}�l�[�W���̊m��
	bw->cell_trans=InitCellTransfer(BATTLE_CELL_TRANS_MAX,HEAPID_BATTLE);
}

//============================================================================================
/**
 * @param
 */
//============================================================================================

static	int		FightMain(PROC *proc)
{
	BATTLE_WORK	*bw=PROC_GetWork(proc);
	int	i;

	if(bw->server_flag){
		if(bw->fight_type&FIGHT_TYPE_SIO){
			ServerMain(bw,bw->server_param);
		}
		else{
			bw->fight_end_flag=ServerMain(bw,bw->server_param);
			ScioBattleRecvData(bw);
		}
	}
	for(i=0;i<bw->client_set_max;i++){
		ClientMain(bw,bw->client_param[i]);
	}

	return bw->fight_end_flag;
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
static	void	FightEnd(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	int	i;

	WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);
	WIPE_SetBrightness(WIPE_DISP_SUB, WIPE_FADE_BLACK);

	//�t�H�����`�F���W����|�P�����̃`�F�b�N
	BattleWorkFormChgCheck(bw);

	//TV�ԑg�R�[��
	//�Q�b�g���́A�߂܂����|�P������PP
	//����ȊO�́A�ΐ푊���PP
	if(bw->win_lose_flag!=FIGHT_POKE_GET){
		BattleWorkTVDataSet(bw,PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_ENEMY],0));
	}
	
	for(i=0;i<CLIENT_MAX;i++){
		PokeParty_Copy(bw->poke_party[i],bp->poke_party[i]);
		sys_FreeMemoryEz(bw->poke_party[i]);
		MyStatus_Copy(bw->my_status[i],bp->my_status[i]);
		sys_FreeMemoryEz(bw->my_status[i]);
	}

	//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���J��
	MSG_DsIconFlashDelete(bw->msg_icon);

	//�莝���A�C�e���R�s�[
	MyItem_Copy(bw->my_item,bp->my_item);
	sys_FreeMemoryEz(bw->my_item);

	//�}�Ӄ��[�N�R�s�[
	ZukanWork_Copy(bw->zw,bp->zw);
	sys_FreeMemoryEz(bw->zw);

	//�{�b�N�X�R�s�[
	bp->box=bw->box;

	//�o�b�O�J�[�\���R�s�[
	bp->bag_cursor=bw->bag_cursor;

	//�|�P�b�`�f�[�^�R�s�[
	bp->poketch_data=bw->poketch_data;

	///<�e���r�F�ߊl�ԑg�p�R�s�[
	bp->TVWatchBattleWork=bw->TVWatchBattleWork;

	//�T�t�@���{�[���̐��R�s�[
	bp->safari_ball=bw->safari_ball;

	//���s�t���O�R�s�[
	bp->win_lose_flag=bw->win_lose_flag&FIGHT_ESCAPE_SELECT_OFF;

	//�ߊl�����|�P������ClientNo���R�s�[
	bp->get_pokemon_client=bw->get_pokemon_client;

	//���x���A�b�v�|�P�������R�s�[
	bp->level_up_flag=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_level_up_pokemon,NULL);

	//�o�g���^���[���їp���[�N�R�s�[
	bp->btr.total_turn+=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_turn,NULL);
	bp->btr.total_hinshi+=(ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_hinshi,CLIENT_NO_MINE)+
						   ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_hinshi,CLIENT_NO_MINE2));
	bp->btr.total_damage+=(ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_damage,CLIENT_NO_MINE)+
						   ST_ServerParamDataGet(bw,bw->server_param,ID_SP_total_damage,CLIENT_NO_MINE2));

	//�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@���J��
	for(i=0;i<CLIENT_MAX;i++){
		sys_FreeMemoryEz(bw->exchr_param[i].exchr_buffer);
	}

	sys_FreeMemoryEz(bw->msg_buf);

	//�p���b�g�t�F�[�h�V�X�e���폜
	PaletteFadeWorkAllocFree(bw->pfd, FADE_MAIN_BG);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_SUB_BG);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_MAIN_OBJ);
	PaletteFadeWorkAllocFree(bw->pfd, FADE_SUB_OBJ);
	PaletteFadeFree(bw->pfd);

	//���b�Z�[�W�}�l�[�W���̍폜
	MSGMAN_Delete(bw->fight_msg);
	MSGMAN_Delete(bw->attack_msg);

	//�P��o�b�t�@�폜
	WORDSET_Delete(bw->wordset);

	//�|�P�����v���O�����A�j���폜
	PokeAnm_FreeMemory(bw->pasp);

	Particle_SystemExitAll();
	WES_Delete(bw->wsp);

	ServerEnd(bw->server_param);
	for(i=0;i<bw->client_set_max;i++){
		ClientEnd(bw,bw->client_param[i],bw->proc_mode);

	}

	SoftSpriteEnd(bw->soft_sprite);

	//���O���͂�������́AFightScreenEnd���ĂԕK�v�͂Ȃ�
	if(bw->proc_mode!=BW_PROC_MODE_NAMEIN_AFTER){
		FightScreenEnd(bw);		//�폜�֘A�܂Ƃ߂Ă���֐�
	}

	//����J�[�\�����[�h��OFF
	MsgPrintSkipFlagSet(MSG_SKIP_OFF);
	MsgPrintAutoFlagSet(MSG_AUTO_OFF);
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);

	GF_BGL_BmpWinFree(bw->win,BATTLE_BMP_WIN_MAX);

	sys_FreeMemoryEz(bw->bgl);
	sys_FreeMemoryEz(bw->bg_area);
	sys_FreeMemoryEz(bw->pal_area);

	NUMFONT_Delete(bw->numfont_hp);
#if 1	//���x����numfont_hp�Ɠ��������g�p����悤�ɂȂ��� 2005.11.10(��)	��check
	;
#else
	NUMFONT_Delete(bw->numfont_lv);
#endif
	FontProc_UnloadFont(FONT_BUTTON);

	TCB_Delete(bw->update_tcb);
	TCB_Delete(bw->pinch_tcb);

	StopTP();		//�^�b�`�p�l���̏I��

	//3D�`��n�̏�����
//	simple_3DBGExit();
	Fight_3D_Exit(bw->g3Dman);

	//�ޔ����������̎��߂�
	gf_srand(bw->seed_temp);

	//�s���`SE���Ȃ��Ă�����~�߂�
	if(BattleWorkPinchSEFlagGet(bw)){
		Snd_SeStopBySeqNo(BSE_PINCH,0);
	}

	//�Z���]���}�l�[�W���̊J��
	DeleteCellTransfer(bw->cell_trans);

	sys_FreeMemoryEz(bw);

	Overlay_UnloadID(FS_OVERLAY_ID(bc_common));
	if(!CommStateIsWifiConnect()){
		Overlay_UnloadID(FS_OVERLAY_ID(ol_zukan));
	}
}

//============================================================================================
/**
 *	�퓬�w�i��ʏ���������ʐ���
 */
//============================================================================================
static	void	FightBGCreate(BATTLE_WORK *bw, GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();
	WIPE_ResetBrightness(WIPE_DISP_MAIN);
	WIPE_ResetBrightness(WIPE_DISP_SUB);

	//VRAM�ݒ�
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
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

	// �u�����h�ݒ�
	{
		bw->bld_init_req=1;
	}

	//���C����ʃt���[���ݒ�
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
//				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_WINDOW, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_EFFECT, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				BATTLE_BGPRI_BACKGROUND, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//�T�u��ʃt���[���ݒ�
	{
		BINPUT_DefaultFrameSet(bgl);
	}

	//�w�i�O���t�B�b�N�f�[�^���[�h
	{
		WINTYPE	win_type;

		win_type=BattleWorkConfigWinTypeGet(bw);

		TalkWinGraphicNullSet(bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN+bw->bg_id,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bw->pfd, ARC_BATT_BG, BATT_BG00_D_NCLR+(bw->bg_id*3)+BattleWorkTimeZoneOffsetGet(bw), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0, 0);
		PaletteWorkSet_Arc(bw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);
		PaletteWorkSet_Arc(bw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, 0x0b*0x10);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
	}

	//�E�C���h�E�}�X�N�ݒ�̏�����
	{
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE,NULL);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE,NULL);
	}

	GF_Disp_DispOn();

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	sys_VBlankFuncChange(FightVBlank,bw);

}

//============================================================================================
/**
 *	�퓬OBJ��ʏ���������ʐ���
 */
//============================================================================================
static	void	FightOBJCreate(BATTLE_WORK *bw)
{
	int				ground_id;
	int				i;
	int				sel_mons_no;
	SERVER_PARAM	*sp;
	POKEMON_PARAM	*pp;
	
	ground_id = BattleWorkGroundIDGet(bw);
	
	Ground_ActorResourceSet(&bw->ground[GROUND_MINE],bw,GROUND_TYPE_NORMAL_MINE, ground_id);
	Ground_ActorResourceSet(&bw->ground[GROUND_ENEMY], bw, GROUND_TYPE_NORMAL_ENEMY, ground_id);

	//�{�[�����\�[�X�̐�ǂ�
	sp=BattleWorkServerParamGet(bw);
	for(i=0;i<bw->client_set_max;i++){
		sel_mons_no=ST_ServerParamDataGet(bw,sp,ID_SP_sel_mons_no,i);
		pp=BattleWorkPokemonParamGet(bw,i,sel_mons_no);
		ClientBMInit(bw,bw->client_param[i],PokeParaGet(pp,ID_PARA_get_ball,NULL),sel_mons_no);
	}

	//�ʐM�A�C�R���̋N��
	WirelessIconEasy();
}

//============================================================================================
/**
 *	�퓬�w�i��ʏI������
 */
//============================================================================================
static	void	FightBGEnd(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit(bgl, GF_BGL_FRAME3_M );
	//�T�u���
	BINPUT_FrameExit(bgl);
}

//============================================================================================
/**
 *	�퓬OBJ��ʏI������
 */
//============================================================================================
static	void	FightOBJEnd(BATTLE_WORK *bw)
{
	int	i;

//�폜
//	for(i=0;i<GROUND_MAX;i++){
//	  Ground_ActorResourceDel(&bw->ground[i]);
//	}
}

//============================================================================================
/**
 *	�퓬���[�`���Q�N���p�����[�^�e�[�u��
 */
//============================================================================================
//1vs1�f�[�^
static	const	u8 ClientTypeTable1vs1[]={
	{CLIENT_TYPE_AA},
	{CLIENT_TYPE_BB},
};

//�ʐM1vs1�f�[�^
static	const	u8 ClientTypeTableSIO1vs1[][2]={
	{
	{CLIENT_TYPE_AA},
	{CLIENT_TYPE_BB},
	},
	{
	{CLIENT_TYPE_BB},
	{CLIENT_TYPE_AA},
	},
};

//2vs2�f�[�^
static	const	u8 ClientTypeTable2vs2[]={
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_C},
	{CLIENT_TYPE_D},
};

//�ʐM2vs2�f�[�^
static	const	u8 ClientTypeTableSIO2vs2[][4]={
	{
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_C},
	{CLIENT_TYPE_D},
	},
	{
	{CLIENT_TYPE_B},
	{CLIENT_TYPE_A},
	{CLIENT_TYPE_D},
	{CLIENT_TYPE_C},
	}
};

//�ʐMMulti�f�[�^
static	const	u8 ClientTypeTableSIOMulti[][4]={
	//�����ʒu0
	{
	{CLIENT_TYPE_A},	//�����ʒu0
	{CLIENT_TYPE_D},	//�����ʒu1
	{CLIENT_TYPE_C},	//�����ʒu2
	{CLIENT_TYPE_B},	//�����ʒu3
	},
	//�����ʒu1
	{
	{CLIENT_TYPE_B},	//�����ʒu0
	{CLIENT_TYPE_C},	//�����ʒu1
	{CLIENT_TYPE_D},	//�����ʒu2
	{CLIENT_TYPE_A},	//�����ʒu3
	},
	//�����ʒu2
	{
	{CLIENT_TYPE_A},	//�����ʒu0
	{CLIENT_TYPE_D},	//�����ʒu1
	{CLIENT_TYPE_C},	//�����ʒu2
	{CLIENT_TYPE_B},	//�����ʒu3
	},
	//�����ʒu3
	{
	{CLIENT_TYPE_B},	//�����ʒu0
	{CLIENT_TYPE_C},	//�����ʒu1
	{CLIENT_TYPE_D},	//�����ʒu2
	{CLIENT_TYPE_A},	//�����ʒu3
	},
};

//============================================================================================
/**
 *	�퓬���[�`���Q�N��
 *
 * @param[in]	battle_work	�퓬���[�N�\����
 * @param[in]	bp			�퓬�p�����[�^�\����
 */
//============================================================================================
static	void	FightSystemBoot(BATTLE_WORK *bw,BATTLE_PARAM *bp)
{
	int	i,j;
	FIGHT_SYSTEM_BOOT_PARAM	fsbp;
	POKEMON_PARAM *pp;
	POKEMON_PARAM *pp2;

	bw->fight_type=bp->fight_type;

	for(i=0;i<CLIENT_MAX;i++){
		//�}�C�X�e�[�^�X�쐬
		bw->my_status[i]=MyStatus_AllocWork(HEAPID_BATTLE);
		MyStatus_Copy(bp->my_status[i],bw->my_status[i]);
		//�|�P���������f�[�^�쐬
		bw->poke_voice[i]=bp->poke_voice[i];
	}

	//�莝���A�C�e���쐬
	bw->my_item=MyItem_AllocWork(HEAPID_BATTLE);
	MyItem_Copy(bp->my_item,bw->my_item);

	//�}�Ӄ��[�N�쐬
	bw->zw=ZukanWork_AllocWork(HEAPID_BATTLE);
	ZukanWork_Copy(bp->zw,bw->zw);

	//�{�b�N�X�R�s�[
	bw->box=bp->box;

	//�R���t�B�O�R�s�[
	bw->config=bp->config;

	// �Ƃ������O���[�v�|�C���^�R�s�[
	bw->friendlist = bp->friendlist;

	//�o�b�O�J�[�\���R�s�[
	bw->bag_cursor=bp->bag_cursor;

	//�|�P�b�`�f�[�^�R�s�[
	bw->poketch_data=bp->poketch_data;

	//�ꏊ�i�����R�s�[
	bw->shinka_place_mode=bp->shinka_place_mode;

	///<�e���r�F�ߊl�ԑg�p�R�s�[
	bw->TVWatchBattleWork=bp->TVWatchBattleWork;

	//�T�t�@���{�[���̐��R�s�[
	bw->safari_ball=bp->safari_ball;

	//�n�`ID�n�R�s�[
	bw->ground_id=bp->ground_id;
	bw->bg_id=bp->bg_id;
	bw->place_id=bp->place_id;

	//���ԑуR�s�[
	bw->time_zone=bp->time_zone;

	//�퓬���ʃt���O�R�s�[
	bw->battle_status_flag=bp->battle_status_flag;

	//���M�����[�V�����t���O�R�s�[
	bw->regulation_flag=bp->regulation_flag;

	//�R���e�X�g���������ǂ����t���O�R�s�[
	bw->contest_see_flag=bp->contest_see_flag;

	//�~�Y�L�ɂ��������ǂ����t���O�R�s�[
	bw->mizuki_flag=bp->mizuki_flag;

	//�t�B�[���h�V����R�s�[
	bw->weather=bp->weather;

	//�J�E���g�A�b�v�p���[�N���R�s�[
	bw->record=bp->record;
	//���R�[�h��NULL���Ƃ܂����̂ŁA�A�T�[�g
	GF_ASSERT(bp->record!=NULL);

	//�g���[�i�[ID���Z�b�g
	for(i=0;i<CLIENT_MAX;i++){
		bw->trainer_id[i]=bp->trainer_id[i];
		bw->trainer_data[i]=bp->trainer_data[i];
	}

	bw->server_param=ServerInit(bw);

	for(i=0;i<CLIENT_MAX;i++){
		bw->poke_party[i]=PokeParty_AllocPartyWork(HEAPID_BATTLE);
	}

	//�ʐM�ΐ�
	if(bw->fight_type&FIGHT_TYPE_SIO){
		CommCommandBattleInitialize(bw);
		{
			u8	sio_id=CommGetCurrentID();
			int	cnt;

			//�T�[�o�N���`�F�b�N
			FightSioServerBootCheck(bw,bp);

			if(bw->fight_type&FIGHT_TYPE_TOWER){
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTable2vs2[i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				bw->client_set_max=i;
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					//client_param�����ׂĐ�������Ȃ��ƌĂׂȂ��̂ŁA�ʃ��[�v�̒��Ɉړ�
					CT_UISet(bw,bw->client_param[i]);
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
				ST_ServerListRowInit(bw,bw->server_param);
#if 0
				pp=PokemonParam_AllocWork(HEAPID_BATTLE);
				for(i=0;i<2;i++){
					for(j=0;j<POKEMON_TEMOTI_MAX;j++){
						PokeParty_Add(bw->poke_party[i],pp);
					}
				}
				sys_FreeMemoryEz(pp);
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTable2vs2[i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
					if(cnt>3){
						cnt=3;
					}
					//client_param�����ׂĐ�������Ȃ��ƌĂׂȂ��̂ŁA�ʃ��[�v�̒��Ɉړ�
					CT_UISet(bw,bw->client_param[i]);
					switch(i){
					case CLIENT_NO_MINE:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					case CLIENT_NO_ENEMY:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case CLIENT_NO_MINE2:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case CLIENT_NO_ENEMY2:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					default:
						GF_ASSERT("�s���ȗ����ʒu�ł�\n");
						break;
					}
				}
				bw->client_set_max=CLIENT_MAX;
#endif
			}
			else if(bw->fight_type&FIGHT_TYPE_MULTI){
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIOMulti[CommGetStandNo(sio_id)][CommGetStandNo(i)];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				bw->client_set_max=i;
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					//client_param�����ׂĐ�������Ȃ��ƌĂׂȂ��̂ŁA�ʃ��[�v�̒��Ɉړ�
					CT_UISet(bw,bw->client_param[i]);
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
				ST_ServerListRowInit(bw,bw->server_param);
#if 0
				pp=PokemonParam_AllocWork(HEAPID_BATTLE);
				for(i=0;i<2;i++){
					for(j=0;j<POKEMON_TEMOTI_MAX;j++){
						PokeParty_Add(bw->poke_party[i],pp);
					}
				}
				sys_FreeMemoryEz(pp);
				for(i=0;i<CLIENT_MAX;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIOMulti[CommGetStandNo(sio_id)][CommGetStandNo(i)];
					bw->client_param[i]=ClientInit(bw,&fsbp);
				}
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
					if(cnt>3){
						cnt=3;
					}
					//client_param�����ׂĐ�������Ȃ��ƌĂׂȂ��̂ŁA�ʃ��[�v�̒��Ɉړ�
					CT_UISet(bw,bw->client_param[i]);
					switch(CommGetStandNo(i)){
					case TRAINER_STAND_A:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					case TRAINER_STAND_B:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case TRAINER_STAND_C:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
						break;
					case TRAINER_STAND_D:
						for(j=0;j<cnt;j++){
							pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
							pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
							PokeCopyPPtoPP(pp,pp2);
						}
						ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
						break;
					default:
						GF_ASSERT("�s���ȗ����ʒu�ł�\n");
						break;
					}
				}
				bw->client_set_max=CLIENT_MAX;
#endif
			}
			//2vs2
			else if(bw->fight_type&FIGHT_TYPE_2vs2){
				for(i=0;i<4;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIO2vs2[sio_id][i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
					CT_UISet(bw,bw->client_param[i]);
				}
				bw->client_set_max=i;
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
				}
				for(i=0;i<bw->client_set_max;i++){
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i&1]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i&1],j);
						if(i>1){
							if((ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,i&1)!=j)&&
							   (PokeParaGet(pp,ID_PARA_monsno,NULL))&&
							   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
							   (PokeParaGet(pp,ID_PARA_hp,NULL))){
								break;
							}
						}
						else{
							if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
							   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
							   (PokeParaGet(pp,ID_PARA_hp,NULL))){
								break;
							}
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
			}
			//1vs1
			else{
				for(i=0;i<2;i++){
					fsbp.client_no=i;
					fsbp.client_type=ClientTypeTableSIO1vs1[sio_id][i];
					bw->client_param[i]=ClientInit(bw,&fsbp);
					CT_UISet(bw,bw->client_param[i]);
				}
				bw->client_set_max=i;
				//�莝���|�P�����Z�b�g
				for(i=0;i<CLIENT_MAX;i++){
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
					for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				}
			}
		}
		ST_ServerListRowInit(bw,bw->server_param);
	}
	//�^�b�O�o�g��
	else if(bw->fight_type&FIGHT_TYPE_TAG){
		{
			int	sel_mons_no;

			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			bw->client_set_max=i;
			//�莝���|�P�����Z�b�g
			for(i=0;i<CLIENT_MAX;i++){
				PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
			}
			for(i=0;i<bw->client_set_max;i++){
				for(j=0;j<BattleWorkPokeCountGet(bw,i);j++){
					pp=BattleWorkPokemonParamGet(bw,i,j);
					if(i==CLIENT_NO_MINE2){
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))&&
						   (sel_mons_no!=j)){
							break;
						}
					}
					else{
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
				}
				ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
				if(i==CLIENT_NO_MINE){
					sel_mons_no=j;
				}
			}
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
#if 0
		{
			int	cnt;
			pp=PokemonParam_AllocWork(HEAPID_BATTLE);
			for(i=0;i<2;i++){
				for(j=0;j<POKEMON_TEMOTI_MAX;j++){
					PokeParty_Add(bw->poke_party[i],pp);
				}
			}
			sys_FreeMemoryEz(pp);
			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			//�莝���|�P�����Z�b�g
			for(i=0;i<CLIENT_MAX;i++){
				cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
				switch(i){
				case 0:
					PokeParty_Copy(bp->poke_party[i],bw->poke_party[0]);
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
					break;
				case 1:
					if(cnt>3){
						cnt=3;
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
					break;
				case 2:
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,1);
					break;
				case 3:
					if(cnt>3){
						cnt=3;
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				}
			}
			bw->client_set_max=CLIENT_MAX;
			ST_ServerListRowInit(bw,bw->server_param);
			bw->server_flag=1;
		}
#endif
	}
	//AI�}���`
	else if(bw->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable2vs2[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//�莝���|�P�����Z�b�g
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
		}
		for(i=0;i<bw->client_set_max;i++){
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
				   (PokeParaGet(pp,ID_PARA_hp,NULL))){
					break;
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
#if 0
		{
			int	cnt;
			pp=PokemonParam_AllocWork(HEAPID_BATTLE);
			for(i=0;i<2;i++){
				for(j=0;j<POKEMON_TEMOTI_MAX;j++){
					PokeParty_Add(bw->poke_party[i],pp);
				}
			}
			sys_FreeMemoryEz(pp);
			for(i=0;i<CLIENT_MAX;i++){
				fsbp.client_no=i;
				fsbp.client_type=ClientTypeTable2vs2[i];
				bw->client_param[i]=ClientInit(bw,&fsbp);
				CT_UISet(bw,bw->client_param[i]);
			}
			//�莝���|�P�����Z�b�g
			for(i=0;i<CLIENT_MAX;i++){
				cnt=PokeParty_GetPokeCount(bp->poke_party[i]);
				if(cnt>3){
					cnt=3;
				}
				switch(i){
				case 0:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bw->poke_party[0],j);
						if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
						   (PokeParaGet(pp,ID_PARA_hp,NULL))){
							break;
						}
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
					break;
				case 1:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,0);
					break;
				case 2:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[0],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				case 3:
					for(j=0;j<cnt;j++){
						pp=PokeParty_GetMemberPointer(bp->poke_party[i],j);
						pp2=PokeParty_GetMemberPointer(bw->poke_party[1],j+3);
						PokeCopyPPtoPP(pp,pp2);
					}
					ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,3);
					break;
				}
			}
			bw->server_flag=1;
			bw->client_set_max=CLIENT_MAX;
		}
#endif
	}
	//2vs2�ŋN��
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		for(i=0;i<CLIENT_MAX;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable2vs2[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//�莝���|�P�����Z�b�g
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
		}
		for(i=0;i<bw->client_set_max;i++){
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i&1]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i&1],j);
				if(i>1){
					if((ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,i&1)!=j)&&
					   (PokeParaGet(pp,ID_PARA_monsno,NULL))&&
					   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
					   (PokeParaGet(pp,ID_PARA_hp,NULL))){
						break;
					}
				}
				else{
					if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
					   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
					   (PokeParaGet(pp,ID_PARA_hp,NULL))){
						break;
					}
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
	}
	//1vs1�ŋN��
	else{
		for(i=0;i<2;i++){
			fsbp.client_no=i;
			fsbp.client_type=ClientTypeTable1vs1[i];
			bw->client_param[i]=ClientInit(bw,&fsbp);
			CT_UISet(bw,bw->client_param[i]);
		}
		bw->client_set_max=i;
		//�莝���|�P�����Z�b�g
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Copy(bp->poke_party[i],bw->poke_party[i]);
			for(j=0;j<PokeParty_GetPokeCount(bw->poke_party[i]);j++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[i],j);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
				   (PokeParaGet(pp,ID_PARA_hp,NULL))){
					break;
				}
			}
			ST_ServerParamDataPut(bw,bw->server_param,ID_SP_sel_mons_no,i,j);
		}
		ST_ServerListRowInit(bw,bw->server_param);
		bw->server_flag=1;
	}

	//�|�P�p�[�N�̎��́A����̃g���[�i�[�f�[�^�̖��O�ɐe�̖��O�����Ă���
	if(bw->fight_type&FIGHT_TYPE_POKE_PARK){
		pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_ENEMY],0);
		PokeParaGet(pp,ID_PARA_oyaname,(u8 *)&bw->trainer_data[CLIENT_NO_ENEMY].name);
	}

	//�{�X��Q���̂Ȃ��x�v�Z
	if(bw->fight_type&FIGHT_TYPE_TRAINER){
		if((BossTrTypeCheck(bw->trainer_data[CLIENT_NO_ENEMY].tr_type)==TRUE)||
		   (BossTrTypeCheck(bw->trainer_data[CLIENT_NO_ENEMY2].tr_type)==TRUE)){
			for(i=0;i<PokeParty_GetPokeCount(bw->poke_party[CLIENT_NO_MINE]);i++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_MINE],i);
				FriendCalc(pp,FRIEND_BOSS_BATTLE,bw->place_id);
			}
			for(i=0;i<PokeParty_GetPokeCount(bw->poke_party[CLIENT_NO_MINE2]);i++){
				pp=PokeParty_GetMemberPointer(bw->poke_party[CLIENT_NO_MINE2],i);
				FriendCalc(pp,FRIEND_BOSS_BATTLE,bw->place_id);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �g���[�i�[�^�C�v���{�X�N���X���`�F�b�N
 */
//--------------------------------------------------------------
static	BOOL	BossTrTypeCheck(u16 tr_type)
{
	switch(tr_type){
	case TRTYPE_LEADER1:
	case TRTYPE_LEADER2:
	case TRTYPE_LEADER3:
	case TRTYPE_LEADER4:
	case TRTYPE_LEADER5:
	case TRTYPE_LEADER6:
	case TRTYPE_LEADER7:
	case TRTYPE_LEADER8:
	case TRTYPE_BIGFOUR1:
	case TRTYPE_BIGFOUR2:
	case TRTYPE_BIGFOUR3:
	case TRTYPE_BIGFOUR4:
	case TRTYPE_CHAMPION:
		return TRUE;
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p3DBG�������֐�
 */
//--------------------------------------------------------------
static GF_G3DMAN * Fight_3D_Init(void)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(HEAPID_BATTLE, GF_G3DMAN_LNK, GF_G3DTEX_256K, 
		GF_G3DMAN_LNK, GF_G3DPLT_32K, FightSimpleSetUp);
	return g3Dman;
}

static void FightSimpleSetUp(void)
{
	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend( TRUE );		// �A���t�@�u�����h�@�I��
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p3DBG�I������
 *
 * @param   g3Dman		
 */
//--------------------------------------------------------------
static void Fight_3D_Exit(GF_G3DMAN *g3Dman)
{
	GF_G3D_Exit(g3Dman);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N��������
 */
//--------------------------------------------------------------
static	void	FightParticleInit(void)
{
	//--------------------------------------------------------------
	//	������
	//--------------------------------------------------------------
#if 0
	// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// �}�l�[�W�����p���b�g��32KB���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);

	//�|�P�����Ŏg�p���镪���m��
	NNS_GfdAllocFrmTexVram(0x4000, 0, 0);
	NNS_GfdAllocFrmPlttVram(0x20 * 4, 0, NNS_GFD_ALLOC_FROM_LOW);
#else
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	//�|�P�����Ŏg�p���镪���m��
	tex_key = NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key = NNS_GfdAllocPlttVram(0x20 * (CLIENT_MAX+2), 0, 0);		//�e�̕����ǉ�
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	tex_addrs = NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(pltt_key);
	OS_TPrintf("�|�P�����p�Ɋm�ۂ����e�N�X�`��Vram�̐擪�A�h���X��%d\n", tex_addrs);
	OS_TPrintf("�|�P�����p�Ɋm�ۂ����p���b�gVram�̐擪�A�h���X��%d\n", pltt_addrs);
#endif
	//�p�[�e�B�N���V�X�e�����[�N������
	Particle_SystemWorkInit();
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK�֐�
 *
 * @param	work	VBLank�ɂ͈������K�v�Ȃ̂Œ�`���Ă��邪���ۂɂ�NULL�������Ă���̂ŁA�A�N�Z�X�͋֎~�I
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	FightVBlank(void *work)
{
	BATTLE_WORK *bw = work;

	//�����̕΂���Ȃ������߂ɁA�����_�����Ă�ł���
	gf_rand();

	if(bw->bld_init_req){
		bw->bld_init_req=0;
		G2_BlendNone();
		G2S_BlendNone();
	}
	if(bw->vram_init_req){
		bw->vram_init_req=0;
		{
			GF_BGL_DISPVRAM vramSetTable = {
				GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
				GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
				GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
				GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
				GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
				GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
				GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
				GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
				GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
				GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
			};
			GF_Disp_SetBank( &vramSetTable );
		}
	}
	if(bw->bl_vram_init_req){
		bw->bl_vram_init_req=0;
		{
			GF_BGL_DISPVRAM	tbl = {
				GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
				GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
				GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
				GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
				GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
				GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
				GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
				GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
				GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
				GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
			};
			GF_Disp_SetBank( &tbl );
		}
	}

	SoftSpriteTextureTrans(bw->soft_sprite);
	
	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	PaletteFadeTrans(bw->pfd);

	GF_BGL_VBlankFunc( bw->bgl );

	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK�֐�
 *
 * @param	work	VBLank�ɂ͈������K�v�Ȃ̂Œ�`���Ă��邪���ۂɂ�NULL�������Ă���̂ŁA�A�N�Z�X�͋֎~�I
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	FightSioVBlank(void *work)
{
	BATTLE_SIO_WORK *bsw = work;

	PaletteFadeTrans(bsw->pfd);

	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s

	GF_BGL_VBlankFunc( bsw->bgl );

	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief   ���C�����[�v�̍Ō�ɍs���V�X�e���֘A�̍X�V����
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		bw
 */
//--------------------------------------------------------------
static void FightUpdate(TCB_PTR tcb, void *work)
{
	BATTLE_WORK *bw = work;

	//�ʐM�G���[�Ď�
	CommErrorCheck(HEAPID_BATTLE,bw->bgl);
	
	if((bw->proc_mode==BW_PROC_MODE_FIGHT)||(bw->proc_mode==BW_PROC_MODE_BAG_LIST)){
//���߂��Ɍ��Ɉړ�
//		SoftSpriteMain(bw->soft_sprite);
		if(bw->proc_mode==BW_PROC_MODE_FIGHT){
			BattleParticle_Main();
		}
		SoftSpriteMain(bw->soft_sprite);
		CATS_Draw(bw->crp);
		CATS_UpdateTransfer();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}

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
 * @brief   �s���`SE�̃`�F�b�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		bw
 */
//--------------------------------------------------------------
#define	PINCH_SE_WAIT	(4)
#define	PINCH_SE_PAUSE	(2)
static void FightPinchSECheck(TCB_PTR tcb, void *work)
{
	BATTLE_WORK		*bw=work;
	CLIENT_PARAM	*cp;
	GAUGE_WORK		*gauge;
	int				client_no;
	int				client_set_max;
	int				flag;
	int				se_flag;
	int				wait;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	flag=0;
	se_flag=BattleWorkPinchSEFlagGet(bw);

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_NO_PINCH_SE){
		return;
	}

	if(se_flag&PINCH_SE_PAUSE){
		if(se_flag&1){
			Snd_SeStopBySeqNo(BSE_PINCH,0);
			BattleWorkPinchSEFlagSet(bw,PINCH_SE_PAUSE);
		}
		return;
	}
	
	for(client_no=0;client_no<client_set_max;client_no++){
		cp=BattleWorkClientParamGet(bw,client_no);
		if(CT_CPClientBootGet(cp)==CLIENT_BOOT_NORMAL){
			gauge=CT_CPGaugeWorkGet(cp);
			if(gauge!=NULL){	
				if(GetHPGaugeDottoColor(gauge->hp,gauge->hpmax,GAUGE_HP_DOTTOMAX)==HP_DOTTO_RED){
					flag|=No2Bit(client_no);
				}
			}
		}
	}
	if((flag)&&(BattleWorkPinchSEFlagGet(bw)==0)){
		Snd_SePlay(BSE_PINCH);
		BattleWorkPinchSEFlagSet(bw,1);
		BattleWorkPinchSEWaitSet(bw,PINCH_SE_WAIT);
	}
	else if((flag==0)&&(BattleWorkPinchSEFlagGet(bw))){
		Snd_SeStopBySeqNo(BSE_PINCH,0);
		BattleWorkPinchSEFlagSet(bw,0);
	}

	//�s���`SE�̓��[�v�ł͂Ȃ��̂ŁA�ăR�[��������
	if(BattleWorkPinchSEFlagGet(bw)){
		wait=BattleWorkPinchSEWaitGet(bw);
		if(Snd_SePlayCheck(BSE_PINCH)==FALSE){
			if(--wait==0){
				Snd_SePlay(BSE_PINCH);
				BattleWorkPinchSEWaitSet(bw,PINCH_SE_WAIT);
			}
			else{
				BattleWorkPinchSEWaitSet(bw,wait);
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief   �퓬�J�n���ɃE�C���h�E�ʂ������猻���悤�ɂ���
 * 			BG1OFFSET�̒l���O�ɂȂ�����I���i���E���܂��j
 *
 *
 * @param   tcb		
 * @param   work	BATTLE_WORK*
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void StartMsgWinMove( TCB_PTR tcb, void *work )
{
	BATTLE_WORK		*bw=work;

	bw->bg1_scroll += 3;
	
	GF_BGL_ScrollSet( bw->bgl, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, bw->bg1_scroll );

	if(bw->bg1_scroll==0){
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * @brief   
 *
 * ProcData�Ŏw�肵���ȊO�̃I�[�o�[���C�̃��[�h���s��
 *
 */
//--------------------------------------------------------------
static void NitroStaticInit(void)
{
	if(!CommStateIsWifiConnect()){
		Overlay_Load(FS_OVERLAY_ID(ol_zukan), OVERLAY_LOAD_NOT_SYNCHRONIZE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�ΐ펞�̑ΐ�O�莝���|�P�������X�g�\�����[�`��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		bw
 */
//--------------------------------------------------------------
static	void	FightSioInit(PROC *proc,BATTLE_PARAM *bp)
{
	BATTLE_SIO_WORK	*bsw=PROC_AllocWork(proc,sizeof(BATTLE_SIO_WORK), HEAPID_BATTLE);

	bsw->bp=bp;
	bsw->send_count=0;
	bsw->seq_no=0;
	bsw->time_out_count=0;

	bsw->pfd = PaletteFadeInit(HEAPID_BATTLE);
	PaletteTrans_AutoSet(bsw->pfd, TRUE);
	PaletteFadeWorkAllocSet(bsw->pfd, FADE_MAIN_BG, 0x200, HEAPID_BATTLE);
	PaletteWork_Clear(bsw->pfd,FADE_MAIN_BG,FADEBUF_ALL,0x0000,0,256);
	
	bsw->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	bsw->win=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,1);

	CommCommandBattleCPInitialize(bsw);

	GF_Disp_GX_VisibleControlInit();

	//VRAM�ݒ�
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
			GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
			GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
			GX_VRAM_TEX_01_BC,				// �e�N�X�`���C���[�W�X���b�g
			GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAM�N���A
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
		MI_CpuFill16((void*)HW_BG_PLTT, 0x0000, HW_BG_PLTT_SIZE);
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
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			BATTLE_BGPRI_WINDOW, 0, 0, FALSE
		};
		GF_BGL_BGControlSet(bsw->bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bsw->bgl, GF_BGL_FRAME1_M );
	}

	//�w�i�O���t�B�b�N�f�[�^���[�h
	{
		WINTYPE	win_type;

		win_type=CONFIG_GetWindowType(bp->config);

		TalkWinGraphicNullSet(bsw->bgl, GF_BGL_FRAME1_M,TALK_WIN_CGX_START,TALK_WIN_PAL_NO,win_type,HEAPID_BATTLE);
		PaletteWorkSet_Arc(bsw->pfd, ARC_FONT, NARC_font_talk_ncrl, HEAPID_BATTLE, FADE_MAIN_BG, 0x20, 0x0b*0x10);
		PaletteWorkSet_Arc(bsw->pfd, ARC_WINFRAME, TalkWinPalArcGet(win_type), HEAPID_BATTLE, 
			FADE_MAIN_BG, 0x20, TALK_WIN_PAL_NO*0x10);

		PaletteWork_Clear(bsw->pfd,FADE_MAIN_BG,FADEBUF_TRANS,0x0000,0,256);
	}

	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	GF_BGL_BmpWinAdd(bsw->bgl,bsw->win,GF_BGL_FRAME1_M,
					 TALK_WIN_X,TALK_WIN_Y,TALK_WIN_SIZE_X,TALK_WIN_SIZE_Y,TALK_MSG_PAL_NO,TALK_MSG_START);
	GF_BGL_BmpWinDataFill(bsw->win,0xff);
	BmpTalkWinWrite(bsw->win,WINDOW_TRANS_ON,TALK_WIN_CGX_START,TALK_WIN_PAL_NO);

	//���b�Z�[�W�\��
	{
		MSGDATA_MANAGER		*msg_m;
		STRBUF				*msg_buf;


		msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_fightmsg_dp_dat,HEAPID_BATTLE);
		msg_buf=STRBUF_Create(0x100,HEAPID_BATTLE);

		MSGMAN_GetString(msg_m,TaikiMsg,msg_buf);
		GF_STR_PrintSimple(bsw->win,FONT_TALK,msg_buf,0,0,NULL,NULL);

		//���b�Z�[�W�}�l�[�W���֘A�폜
		STRBUF_Delete(msg_buf);
		MSGMAN_Delete(msg_m);
	}

	sys_VBlankFuncChange(FightSioVBlank,bsw);

	PaletteFadeReq(bsw->pfd,PF_BIT_MAIN_ALL,0xffff,0,16,0,0x0000);

	bsw->time_icon=TimeWaitIconAdd(bsw->win,TALK_WIN_CGX_START);

	//�ʐM�A�C�R���̋N��
	WirelessIconEasy();
}

enum{
	FSM_SEQ_FADE_INIT=0,
	FSM_SEQ_FADE_WAIT,
	FSM_SEQ_SYNCHRONIZE,
	FSM_SEQ_SYNCHRONIZE_WAIT,
	FSM_SEQ_SEND_SV_DATA,
	FSM_SEQ_SEND_SV_DATA_WAIT,
	FSM_SEQ_SEND_MS_DATA_MAKE,
	FSM_SEQ_SEND_MS_DATA,
	FSM_SEQ_SEND_MS_DATA_WAIT,
	FSM_SEQ_SEND_TR_DATA_MAKE,
	FSM_SEQ_SEND_TR_DATA,
	FSM_SEQ_SEND_TR_DATA_WAIT,
	FSM_SEQ_SEND_POKE_DATA_MAKE,
	FSM_SEQ_SEND_POKE_DATA,
	FSM_SEQ_SEND_POKE_DATA_WAIT,
	FSM_SEQ_SEND_POKE_VOICE_MAKE,
	FSM_SEQ_SEND_POKE_VOICE,
	FSM_SEQ_SEND_POKE_VOICE_WAIT,

	FSM_SEQ_SEND_FRIEND_LIST_MAKE,
	FSM_SEQ_SEND_FRIEND_LIST,
	FSM_SEQ_SEND_FRIEND_LIST_WAIT,

	FSM_SEQ_SEND_TOWER_TR_DATA1_MAKE,
	FSM_SEQ_SEND_TOWER_TR_DATA1,
	FSM_SEQ_SEND_TOWER_TR_DATA1_WAIT,
	FSM_SEQ_SEND_TOWER_TR_DATA2_MAKE,
	FSM_SEQ_SEND_TOWER_TR_DATA2,
	FSM_SEQ_SEND_TOWER_TR_DATA2_WAIT,
	FSM_SEQ_SEND_TOWER_POKE_DATA1_MAKE,
	FSM_SEQ_SEND_TOWER_POKE_DATA1,
	FSM_SEQ_SEND_TOWER_POKE_DATA1_WAIT,
	FSM_SEQ_SEND_TOWER_POKE_DATA2_MAKE,
	FSM_SEQ_SEND_TOWER_POKE_DATA2,
	FSM_SEQ_SEND_TOWER_POKE_DATA2_WAIT,
	FSM_SEQ_SEND_DATA_END
};

static	BOOL	FightSioMain(PROC *proc)
{
	BATTLE_SIO_WORK	*bsw=PROC_GetWork(proc);
	BOOL			ret;

	//�ʐM�G���[�Ď�
	CommErrorCheck(HEAPID_BATTLE,bsw->bgl);

	ret=FALSE;

	switch(bsw->seq_no){
	case FSM_SEQ_FADE_INIT:
		WIPE_ResetBrightness(WIPE_DISP_MAIN);
		bsw->seq_no++;
		break;
	case FSM_SEQ_FADE_WAIT:
		if(PaletteFadeCheck(bsw->pfd)==0){	//�P�x�ύX�t�F�[�h�I���҂����ĐF�X�폜
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SYNCHRONIZE:
		CommTimingSyncStart( COMM_BATTLE_STRAT_SYNC_NUM );
		bsw->seq_no++;
		break;
	case FSM_SEQ_SYNCHRONIZE_WAIT:
		if(CommIsTimingSync( COMM_BATTLE_STRAT_SYNC_NUM )){
			CommTimingSyncStart( COMM_BATTLE_SV_SYNC_NUM );
			bsw->time_out_count=0;
			bsw->seq_no++;
		}
		else{
			bsw->time_out_count++;
			if(bsw->time_out_count>SERVER_QUE_TIME_OUT){
				OS_Printf("�퓬�J�n�O�^�C���A�E�g����\n");
				CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
			}
		}
		break;
	case FSM_SEQ_SEND_SV_DATA:
		if(CommCommandBattleSendServerVersionData(bsw,BattleServerVersion)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_MS_DATA_MAKE:
		if(CommCommandBattleSendMyStatusDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_MS_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_MS_DATA:
		if(CommCommandBattleSendMyStatusDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TR_DATA_MAKE:
		if(CommCommandBattleSendTrainerDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TR_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TR_DATA:
		if(CommCommandBattleSendTrainerDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_DATA_MAKE:
		if(CommCommandBattleSendPokeDataMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_POKE_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_DATA:
		if(CommCommandBattleSendPokeDataWait(bsw)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_VOICE_MAKE:
		if(CommCommandBattleSendPokeVoiceMake(bsw)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_POKEV_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_POKE_VOICE:
		if(CommCommandBattleSendPokeVoiceWait(bsw)==TRUE){
			OS_Printf("�y���b�v�{�C�X��M�҂�\n");
			bsw->seq_no++;
		}
		break;

	case FSM_SEQ_SEND_FRIEND_LIST_MAKE:
		if(CommCommandBattleSendFriendListMake(bsw)==TRUE){
			OS_Printf("�Ƃ������O���[�v�f�[�^�쐬�I��\n");
			CommTimingSyncStart( COMM_BATTLE_FLIST_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_FRIEND_LIST:
		if(CommCommandBattleSendFriendListWait(bsw)==TRUE){
			OS_Printf("�Ƃ������O���[�v�f�[�^��M\n");
			bsw->seq_no++;
		}
		break;


	case FSM_SEQ_SEND_TOWER_TR_DATA1_MAKE:
		if((bsw->bp->fight_type&FIGHT_TYPE_TOWER)==0){
			bsw->seq_no=FSM_SEQ_SEND_DATA_END;
			OS_Printf("�g���[�i�[�f�[�^�쐬\n");
		}
		else{
			//�q�@������͑��M���Ȃ�
			if(CommGetCurrentID()){
				CommTimingSyncStart( COMM_BATTLE_TTDATA1_SYNC_NUM );
				bsw->seq_no++;
			}
			else if(CommCommandBattleSendTowerTrDataMake(bsw,CLIENT_NO_ENEMY)==TRUE){
				CommTimingSyncStart( COMM_BATTLE_TTDATA1_SYNC_NUM );
				bsw->seq_no++;
			}
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA1:
		bsw->send_count=1;
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TTDATA1_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerTrDataWait(bsw,CLIENT_NO_ENEMY,COMM_BATTLE_TTDATA1_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA2_MAKE:
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TTDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerTrDataMake(bsw,CLIENT_NO_ENEMY2)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TTDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_TR_DATA2:
		bsw->send_count=1;
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TTDATA2_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerTrDataWait(bsw,CLIENT_NO_ENEMY2,COMM_BATTLE_TTDATA2_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA1_MAKE:
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TPDATA1_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerPokeDataMake(bsw,CLIENT_NO_ENEMY)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TPDATA1_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA1:
		bsw->send_count=1;
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TPDATA1_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerPokeDataWait(bsw,CLIENT_NO_ENEMY,COMM_BATTLE_TPDATA1_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA2_MAKE:
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			CommTimingSyncStart( COMM_BATTLE_TPDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		else if(CommCommandBattleSendTowerPokeDataMake(bsw,CLIENT_NO_ENEMY2)==TRUE){
			CommTimingSyncStart( COMM_BATTLE_TPDATA2_SYNC_NUM );
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_TOWER_POKE_DATA2:
		bsw->send_count=1;
		//�q�@������͑��M���Ȃ�
		if(CommGetCurrentID()){
			if(CommIsTimingSync(COMM_BATTLE_TPDATA2_SYNC_NUM)==TRUE){
				bsw->seq_no++;
			}
		}
		else if(CommCommandBattleSendTowerPokeDataWait(bsw,CLIENT_NO_ENEMY2,COMM_BATTLE_TPDATA2_SYNC_NUM)==TRUE){
			bsw->seq_no++;
		}
		break;
	case FSM_SEQ_SEND_SV_DATA_WAIT:
	case FSM_SEQ_SEND_MS_DATA_WAIT:
	case FSM_SEQ_SEND_TR_DATA_WAIT:
	case FSM_SEQ_SEND_POKE_DATA_WAIT:
	case FSM_SEQ_SEND_POKE_VOICE_WAIT:
	case FSM_SEQ_SEND_FRIEND_LIST_WAIT:
	case FSM_SEQ_SEND_TOWER_TR_DATA1_WAIT:
	case FSM_SEQ_SEND_TOWER_TR_DATA2_WAIT:
	case FSM_SEQ_SEND_TOWER_POKE_DATA1_WAIT:
	case FSM_SEQ_SEND_TOWER_POKE_DATA2_WAIT:
		if(bsw->send_count==CommGetConnectNum()){

			if(bsw->seq_no==FSM_SEQ_SEND_FRIEND_LIST_WAIT){
				int i;
				for(i=0;i<CLIENT_MAX;i++){
					sys_FreeMemoryEz(bsw->recv_flist[i]);
				}
			}

			bsw->send_count=0;
			bsw->time_out_count=0;
			bsw->seq_no++;
			if(bsw->seq_no==FSM_SEQ_SEND_DATA_END){
				PaletteFadeReq(bsw->pfd,PF_BIT_MAIN_ALL,0xffff,0,0,16,0x0000);
			}

		}
		else{
			bsw->time_out_count++;
			if(bsw->time_out_count>SERVER_QUE_TIME_OUT){
				OS_Printf("�퓬�J�n�O�^�C���A�E�g����\n");
				CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
			}
		}
		break;
	case FSM_SEQ_SEND_DATA_END:
		if(PaletteFadeCheck(bsw->pfd)==0){	//�P�x�ύX�t�F�[�h�I���҂����ĐF�X�폜
			ret=TRUE;
			TimeWaitIconDel(bsw->time_icon);
			CommSetWifiBothNet(FALSE); // �퓬�̒ʐM�𓯊�����񓯊��ɕς���
		}
		break;
	}

	return ret;
}

static	void	FightSioEnd(PROC *proc)
{
	BATTLE_SIO_WORK	*bsw=PROC_GetWork(proc);

	sys_VBlankFuncChange(NULL,NULL);

	WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);

	//�p���b�g�t�F�[�h�V�X�e���폜
	PaletteFadeWorkAllocFree(bsw->pfd, FADE_MAIN_BG);
	PaletteFadeFree(bsw->pfd);

	GF_BGL_BmpWinFree(bsw->win,1);

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_BGL_BGControlExit(bsw->bgl, GF_BGL_FRAME1_M );

	sys_FreeMemoryEz(bsw->bgl);

	sys_FreeMemoryEz(bsw);
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�ΐ�J�n�O�f���i�}���`���̃|�P�������X�g�\���j
 */
//--------------------------------------------------------------
static	BOOL	FightListDemoInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_AllocWork(proc,sizeof(BATTLE_WORK), HEAPID_BATTLE);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	u8	sio_id;

	sio_id=CommGetCurrentID();

	MI_CpuClearFast(bw,sizeof(BATTLE_WORK));

	FightSystemBoot(bw,bp);

	//�ʐM�ΐ�łȂ���΃f���͂Ȃ��A�o�g���^���[���Ȃ�
	if(((bw->fight_type&FIGHT_TYPE_SIO)==0)||
		(bw->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	//�f���v���O���������[�h
	Overlay_Load(FS_OVERLAY_ID(vs_demo), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	//�}���`�ł͂Ȃ����̓f���Ȃ�
	if((bw->fight_type&FIGHT_TYPE_MULTI)==0){
		return FALSE;
	}

	bw->vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	MI_CpuClearFast(bw->vdd,sizeof(VS_DEMO_DATA));

	//�}���`�ΐ�
	switch(CommGetStandNo(sio_id)){
	case 0:
	case 3:
		bw->vdd->pp[0]=bw->poke_party[sio_id];
		bw->vdd->pp[2]=bw->poke_party[BattleWorkPartnerClientNoGet(bw,sio_id)];
		break;
	case 1:
	case 2:
		bw->vdd->pp[0]=bw->poke_party[BattleWorkPartnerClientNoGet(bw,sio_id)];
		bw->vdd->pp[2]=bw->poke_party[sio_id];
		break;
	}
	bw->vdd->heap=HEAPID_BATTLE;
	bw->vdd->mode=VSD_MODE_MULTI;
	switch(CommGetStandNo(sio_id)){
	case 0:
	case 3:
		bw->vdd->type=VSD_TYPE_LEFT;
		break;
	case 1:
	case 2:
		bw->vdd->type=VSD_TYPE_RIGHT;
		break;
	}

	VSDemo_TaskAdd(bw->vdd);

	return TRUE;
}

static	BOOL	FightListDemoMain(PROC *proc)
{
	int	i;
	BATTLE_WORK		*bw=PROC_GetWork(proc);

	if(bw->vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(bw->vdd->name[i]!=NULL){
				sys_FreeMemoryEz(bw->vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(bw->vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�ΐ�J�n�O�f��
 */
//--------------------------------------------------------------
static	BOOL	FightMenuDemoInit(PROC *proc)
{
	BATTLE_WORK		*bw=PROC_GetWork(proc);
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	u8	sio_id;
	int	i;

	sio_id=CommGetCurrentID();

	//�ʐM�ΐ�łȂ���΃f���͂Ȃ��A�o�g���^���[���Ȃ�
	if(((bw->fight_type&FIGHT_TYPE_SIO)==0)||
		(bw->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	bw->vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	MI_CpuClearFast(bw->vdd,sizeof(VS_DEMO_DATA));

	//�}���`�ΐ�
	if(bw->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			bw->vdd->pp[CommGetStandNo(i)]=bw->poke_party[i];
			bw->vdd->name[CommGetStandNo(i)]=MyStatus_CreateNameString(bw->my_status[i],HEAPID_BATTLE);
			OS_TPrintf("sio_id:%d stand_no:%d pp:%08x\n",i,CommGetStandNo(i),bw->vdd->pp[CommGetStandNo(i)]);
		}
		bw->vdd->heap=HEAPID_BATTLE;
		bw->vdd->mode=VSD_MODE_IN;
		bw->vdd->type=VSD_TYPE_MULTI;
	}
	else{
		bw->vdd->pp[CommGetStandNo(sio_id)]=bw->poke_party[sio_id];
		bw->vdd->pp[CommGetStandNo(sio_id^1)]=bw->poke_party[sio_id^1];
		bw->vdd->name[CommGetStandNo(sio_id)]=MyStatus_CreateNameString(bw->my_status[sio_id],HEAPID_BATTLE);
		bw->vdd->name[CommGetStandNo(sio_id^1)]=MyStatus_CreateNameString(bw->my_status[sio_id^1],HEAPID_BATTLE);
		bw->vdd->heap=HEAPID_BATTLE;
		bw->vdd->mode=VSD_MODE_IN;
		bw->vdd->type=VSD_TYPE_NORMAL;
	}

	VSDemo_TaskAdd(bw->vdd);

	return TRUE;
}

static	BOOL	FightMenuDemoMain(PROC *proc)
{
	int	i;
	BATTLE_WORK		*bw=PROC_GetWork(proc);

	if(bw->vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(bw->vdd->name[i]!=NULL){
				sys_FreeMemoryEz(bw->vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(bw->vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�ΐ팋�ʃf��
 */
//--------------------------------------------------------------
static	BOOL	FightWinLoseDemoInit(PROC *proc)
{
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	VS_DEMO_DATA	*vdd;
	u8	sio_id;
	int	i;

	sio_id=CommGetCurrentID();

	//�ʐM�ΐ�łȂ���΃f���͂Ȃ��A�o�g���^���[���Ȃ�
	if(((bp->fight_type&FIGHT_TYPE_SIO)==0)||
		(bp->fight_type&FIGHT_TYPE_TOWER)){
		return FALSE;
	}

	//�f���v���O���������[�h
	Overlay_Load(FS_OVERLAY_ID(vs_demo), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	vdd=sys_AllocMemory(HEAPID_BATTLE,sizeof(VS_DEMO_DATA));
	bp->work=vdd;
	MI_CpuClearFast(vdd,sizeof(VS_DEMO_DATA));
	vdd->bp=bp;

	switch(bp->win_lose_flag){
	case FIGHT_WIN:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_WIN);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_WIN);
		}
		break;
	case FIGHT_LOSE:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_LOSE);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_LOSE);
		}
		break;
	case FIGHT_DRAW:
	case FIGHT_ESCAPE:
		if(!CommStateIsWifiConnect()){
			RECORD_Inc(bp->record,RECID_COMM_BTL_DRAW);
		}
		else{
			RECORD_Inc(bp->record,RECID_WIFI_BTL_DRAW);
		}
		break;
	}

	//�}���`�ΐ�
	if(bp->fight_type&FIGHT_TYPE_MULTI){
		for(i=0;i<CLIENT_MAX;i++){
			vdd->pp[CommGetStandNo(i)]=bp->poke_party[i];
			vdd->name[CommGetStandNo(i)]=MyStatus_CreateNameString(bp->my_status[i],HEAPID_BATTLE);
		}
		vdd->heap=HEAPID_BATTLE;
		vdd->mode=VSD_MODE_END;
		vdd->type=VSD_TYPE_MULTI;
		if(bp->win_lose_flag!=FIGHT_ESCAPE){
			vdd->result=bp->win_lose_flag;
		}
		else{
			vdd->result=VSD_RESULT_DRAW;
		}
	}
	else{
		vdd->pp[CommGetStandNo(sio_id)]=bp->poke_party[sio_id];
		vdd->pp[CommGetStandNo(sio_id^1)]=bp->poke_party[sio_id^1];
		vdd->name[CommGetStandNo(sio_id)]=MyStatus_CreateNameString(bp->my_status[sio_id],HEAPID_BATTLE);
		vdd->name[CommGetStandNo(sio_id^1)]=MyStatus_CreateNameString(bp->my_status[sio_id^1],HEAPID_BATTLE);
		vdd->heap=HEAPID_BATTLE;
		vdd->mode=VSD_MODE_END;
		vdd->type=VSD_TYPE_NORMAL;
		if(bp->win_lose_flag!=FIGHT_ESCAPE){
			vdd->result=bp->win_lose_flag;
		}
		else{
			vdd->result=VSD_RESULT_DRAW;
		}
	}

	VSDemo_TaskAdd(vdd);

	return TRUE;
}

static	BOOL	FightWinLoseDemoMain(PROC *proc)
{
	int	i;
	BATTLE_PARAM	*bp=PROC_GetParentWork(proc);
	VS_DEMO_DATA	*vdd=bp->work;

	if(vdd->end_flg){
		for(i=0;i<CLIENT_MAX;i++){
			if(vdd->name[i]!=NULL){
				sys_FreeMemoryEz(vdd->name[i]);
			}
		}
		sys_FreeMemoryEz(vdd);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬���̑���J�[�\�����[�h�̐ݒ�
 */
//--------------------------------------------------------------
static void	FightMsgPrintModeSet(BATTLE_WORK *bw)
{
	if(bw->fight_type&(FIGHT_TYPE_SIO|FIGHT_TYPE_GET_DEMO)){
		//�����L�[�����AUTO��
		MsgPrintAutoFlagSet(MSG_AUTO_ON);
	}
	else{
		MsgPrintAutoFlagSet(MSG_AUTO_SKIP_ON);
		MsgPrintSkipFlagSet(MSG_SKIP_ON);
		MsgPrintTouchPanelFlagSet(MSG_TP_ON);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�ΐ펞�̃T�[�o�N���`�F�b�N
 */
//--------------------------------------------------------------
static	void	FightSioServerBootCheck(BATTLE_WORK *bw,BATTLE_PARAM *bp)
{
	int	i,j,work;
	int	sio_id,max;
	int	id[CLIENT_MAX];
	int	version[CLIENT_MAX];

	for(i=0;i<CLIENT_MAX;i++){
		id[i]=i;
		version[i]=bp->server_version[i];
	}

	sio_id=CommGetCurrentID();
	max=CommGetConnectNum();

	for(i=0;i<max-1;i++){
		for(j=i+1;j<max;j++){
			if(version[i]<version[j]){
				work=id[i];
				id[i]=id[j];
				id[j]=work;
				work=version[i];
				version[i]=version[j];
				version[j]=work;
			}
		}
	}

	if(id[0]==sio_id){
		bw->server_flag=1;
	}
}

