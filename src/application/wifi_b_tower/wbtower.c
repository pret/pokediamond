//============================================================================================
/**
 * @file	wbtower.c
 * @bfief	WIFI�o�g���^���[����
 * @author	Akito Mori
 * @date	06.05.15
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_bt.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/pms_data.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_wifi_lobby.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/gf_date.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"


#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "system/bmp_menu.h"
#include "application/wbtower.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wm_icon.h"
#include "field/fld_bmp.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "savedata/savedata.h"

#include "wifi/dwc_rap.h"

#include "wbtower_local.h"
#include "system/pm_overlay.h"



#include "msgdata/msg_ev_win.h"
#include "msgdata/msg_trname.h"

// SE�p��`
#define WORLD_MOVE_SE		(SEQ_SE_DP_SELECT)
#define RECORD_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define RECORD_BS_SE		(SEQ_SE_DP_SELECT)


#define MYDWC_HEAPSIZE		0x20000
#include "../wifi_worldtrade/worldtrade.naix"			// �O���t�B�b�N�A�[�J�C�u��`
//============================================================================================
//	�萔��`
//============================================================================================



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void InitWork( WBTOWER_WORK *wk, PROC *proc );
static void FreeWork( WBTOWER_WORK *wk );
static void char_pltt_manager_init(void);
static void InitCellActor(WBTOWER_WORK *wk);
static void SetCellActor(WBTOWER_WORK *wk);
static void CursorAppearUpDate(WBTOWER_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void RecordMessagePrint( WBTOWER_WORK *wk, int msgno, int wait );
static void FreeFunc(DWCAllocType name, void* ptr,  u32 size);
static void *AllocFunc( DWCAllocType name, u32   size, int align );
static void InitDpw( void *heapPtr, NNSFndHeapHandle heapHandle, DWCAllocEx alloc, DWCFreeEx free  );
static void InitCLACT( WBTOWER_WORK *wk );
static void FreeCLACT( WBTOWER_WORK *wk );


static NNSFndHeapHandle _wtHeapHandle;


//============================================================================================
//	�֐��e�[�u����`
//============================================================================================

// ���E�����T�u�v���Z�X�p�֐��z���`
static int (*SubProcessTable[][3])(WBTOWER_WORK *wk, int seq)={
	{ WBTower_EnterInit,   WBTower_EnterMain,    WBTower_EnterEnd   },
//	{ WBTower_Upload_Init,  WBTower_Upload_Main,   WBTower_Upload_End  },
};


WBTOWER_WORK *debug_wbtower;

//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

#if 0


typedef struct {
	Dpw_Bt_Leader leader[30];
}TEST_BT_LEADER;

TEST_BT_LEADER TestBtLeader;

static void TestLeaderDataMake( TEST_BT_LEADER *leader )
{
	MSGDATA_MANAGER *msgman;
	STRBUF *name;
	int i;

	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trname_dat, HEAPID_WIFI_BATTLETOWER );

	for(i=0;i<30;i++){
		name = MSGMAN_AllocString( msgman, TR_TANPAN_01+i );
		STRBUF_GetStringCode( name, leader->leader[i].playerName,  6 );
		STRBUF_Delete(name);

		leader->leader[i].versionCode = PM_VERSION;
		leader->leader[i].langCode    = PM_LANG;
		leader->leader[i].countryCode = 0;
		leader->leader[i].localCode   = 0;
		leader->leader[i].playerId[0] = i+32;
		leader->leader[i].playerId[1] = 78;
		leader->leader[i].playerId[2] = 0;
		leader->leader[i].playerId[3] = 0;

		PMSDAT_Init( (PMS_DATA*)leader->leader[i].leaderMessage, PMS_TYPE_BATTLE_WON );
		
		TestBtLeader.leader[i].gender      = 0;

	}
	MSGMAN_Delete( msgman );

	OS_Printf("testbtleader size=%d\n", sizeof(TEST_BT_LEADER));

}
#endif

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F������
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WBTowerProc_Init( PROC * proc, int * seq )
{
	WBTOWER_WORK * wk;
	
	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );


		// ���R�[�h�R�[�i�[�p�q�[�v�쐬
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WIFI_BATTLETOWER, 0x50000 );

		wk = PROC_AllocWork( proc, sizeof(WBTOWER_WORK), HEAPID_WIFI_BATTLETOWER );
		memset( wk, 0, sizeof(WBTOWER_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WIFI_BATTLETOWER );
		debug_wbtower = wk;
		
		// BG SYSTEM
		{	
			GF_BGL_SYS_HEADER BGsys_data = {
				GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
			};
			GF_BGL_InitBG( &BGsys_data );
		}
		
		
		// ������}�l�[�W���[����
		wk->WordSet    		 = WORDSET_CreateEx( 11, WORDSET_DEFAULT_BUFLEN, HEAPID_WIFI_BATTLETOWER );
		wk->MsgManager       = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_bt_dat, HEAPID_WIFI_BATTLETOWER );
		wk->LobbyMsgManager  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_lobby_dat, HEAPID_WIFI_BATTLETOWER );
		wk->SystemMsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_system_dat, HEAPID_WIFI_BATTLETOWER );

		sys_KeyRepeatSpeedSet( 4, 8 );

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

//	//	InitTPSystem();						// �^�b�`�p�l���V�X�e��������
//	//	InitTPNoBuff(2);


		// ���[�N������
		InitWork( wk, proc );

		InitCLACT( wk );

		// �T�E���h�f�[�^���[�h(���O����)(BGM���p��)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		// DWC���C�u�����iWifi�j�ɓn�����߂̃��[�N�̈���m��
		wk->heapPtr    = sys_AllocMemory(HEAPID_WIFI_BATTLETOWER, MYDWC_HEAPSIZE + 32);
		wk->heapHandle = NNS_FndCreateExpHeap( (void *)( ((u32)wk->heapPtr + 31) / 32 * 32 ), MYDWC_HEAPSIZE);

		*seq = 1;
		break;
		
	case 1:
		DwcOverlayStart();

		DpwCommonOverlayStart();

		// �C�N�j���[�����]��
		CommVRAMDInitialize();


		(*seq) = SEQ_INIT_DPW;
		
//		TestLeaderDataMake( &TestBtLeader );
		
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F���C��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------

PROC_RESULT WBTowerProc_Main( PROC * proc, int * seq )
{
	WBTOWER_WORK * wk  = PROC_GetWork( proc );
	int update;

	// ��M���x�A�C�R�����f
	DWC_UpdateConnection();

	// �풓�֐��Ăяo��
	Dpw_Bt_Main();

	// Wifi��M���x���f
	DWC_UpdateConnection();

	switch( *seq ){
	// �T�u����������
	case SEQ_INIT_DPW:
//		InitDpw(wk->heapPtr, wk->heapHandle, AllocFunc, FreeFunc );
		if(CommIsVRAMDInitialize()){
			_wtHeapHandle = wk->heapHandle;
	

			// wifi�������Ǘ��֐��Ăяo��
			DWC_SetMemFunc( AllocFunc, FreeFunc );

			*seq = SEQ_INIT;
		}
		break;
	case SEQ_INIT:
		*seq = (*SubProcessTable[wk->sub_process][0])(wk, *seq);
		break;

	// �T�u�����t�F�[�h�C���҂�
	case SEQ_FADEIN:
		if( WIPE_SYS_EndCheck() ){
			*seq = SEQ_MAIN;
		}
		break;

	// �T�u�������C��
	case SEQ_MAIN:
		*seq = (*SubProcessTable[wk->sub_process][1])(wk, *seq);

		break;

	// �T�u�����t�F�[�h�A�E�g�҂�
	case SEQ_FADEOUT:
		if( WIPE_SYS_EndCheck() ){
			// �T�u�������(SEQ_INIT�ɍs�����ASEQ_OUT�ɂ������͂��܂����j
			*seq = (*SubProcessTable[wk->sub_process][2])(wk, *seq);
		}
		break;

	// ���E�����I������
	case SEQ_OUT:
		return PROC_RES_FINISH;
		break;
	}
	if(wk->clactSet!=NULL){
		CLACT_Draw( wk->clactSet );									// �Z���A�N�^�[�풓�֐�
	}
	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F�I��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT WBTowerProc_End( PROC * proc, int * seq )
{
	WBTOWER_WORK  *wk    = PROC_GetWork( proc );
	int i;

	sys_FreeMemoryEz( wk->heapPtr );

	DpwCommonOverlayEnd();
	DwcOverlayEnd();

	// �Z���A�N�^�[���\�[�X���
	FreeCLACT( wk );


	// �^�b�`�p�l���V�X�e���I��
//	StopTP();							


	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	
	MSGMAN_Delete( wk->SystemMsgManager );
	MSGMAN_Delete( wk->LobbyMsgManager );
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ���[�N���
	FreeWork( wk );

	// �C�N�j���[�������
	CommVRAMDFinalize();


	// BG_SYSTEM���
	sys_FreeMemoryEz( wk->bgl );

	PROC_FreeWork( proc );				// PROC���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_WIFI_BATTLETOWER );

	OS_Printf("�o�g���^���[���� = %d\n",wk->param->result);

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank�֐�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	// �Z���A�N�^�[Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
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




//------------------------------------------------------------------
/**
 * ���E�������[�N������
 *
 * @param   wk		WBTOWER_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( WBTOWER_WORK *wk, PROC *proc )
{
	// �Ăяo�����̃p�����[�^���擾
	wk->param = (WBTOWER_PARAM*)PROC_GetParentWork( proc );

	wk->sub_process 	= WBTOWER_ENTER;
	WBTower_SubProcessChange( wk, WBTOWER_ENTER, 0 );

}

//------------------------------------------------------------------
/**
 * $brief   ���[�N���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( WBTOWER_WORK *wk )
{
	

}





//** CharManager PlttManager�p **//
#define WBTOWER_CHAR_CONT_NUM				(20)
#define WBTOWER_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define WBTOWER_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define WBTOWER_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
static void char_pltt_manager_init(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			WBTOWER_CHAR_CONT_NUM,
			WBTOWER_CHAR_VRAMTRANS_MAIN_SIZE,
			WBTOWER_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_WIFI_BATTLETOWER
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(WBTOWER_PLTT_CONT_NUM, HEAPID_WIFI_BATTLETOWER);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * ���[�_�[��ʗp�Z���A�N�^�[������
 *
 * @param   wk		���[�_�[�\���̂̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(WBTOWER_WORK *wk)
{
	int i;
	
	
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 126,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 126,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_WIFI_BATTLETOWER);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( 10, &wk->renddata, HEAPID_WIFI_BATTLETOWER );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, WBTOWER_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_WIFI_BATTLETOWER);
	}


	//---------���ʗp-------------------
	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_WIFI_BATTLETOWER);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_WIFI_BATTLETOWER);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_WIFI_BATTLETOWER);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
			ARC_WORLDTRADE_GRA, NARC_worldtrade_btower_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_WIFI_BATTLETOWER);


	//---------����ʗp-------------------

/*
	//chara�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_WIFI_BATTLETOWER);

	//pal�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 9, HEAPID_WIFI_BATTLETOWER);

	//cell�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_WIFI_BATTLETOWER);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_WORLDTRADE_GRA, NARC_worldtrade_worldtrade_obj_s_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_WIFI_BATTLETOWER);
	// ���\�[�X�}�l�[�W���[����]��
*/
	// Chara�]��
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
//	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
//	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

	

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  3 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

static const u16 arrowtable[][2]={
	{ 232-8, 112-1    },
	{ 232-8, 112+16+1 },
};



//==============================================================================
/**
 * $brief   �Z���A�N�^�[�w�b�_�쐬���[�`��
 *
 * @param   wk		
 * @param   add		
 * @param   param		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_MakeCLACT( CLACT_ADD *add, WBTOWER_WORK *wk, CLACT_HEADER *header, int param)
{
	add->ClActSet	  = wk->clactSet;
	add->ClActHeader  = header;

	add->mat.z		= 0;
	add->sca.x		= FX32_ONE;
	add->sca.y		= FX32_ONE;
	add->sca.z		= FX32_ONE;
	add->rot		= 0;
	add->pri		= 1;
	add->DrawArea	= param;
	add->heap		= HEAPID_WIFI_BATTLETOWER;

}

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			WBTOWER_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(WBTOWER_WORK *wk)
{
	int i;
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_main, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
	//�܂������]�����Ă��Ȃ�����

#if 0	
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_sub, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
#endif


	{
		//�o�^���i�[
		CLACT_ADD add;
		WBTower_MakeCLACT( &add, wk, &wk->clActHeader_main, NNS_G2D_VRAM_TYPE_2DMAIN );

		//�Z���A�N�^�[�\���J�n
		// ���Q��
		for(i=0;i<2;i++){
			add.mat.x = FX32_ONE *   arrowtable[i][0];
			add.mat.y = FX32_ONE *   arrowtable[i][1];
			wk->ArrowActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ArrowActWork[i],1);
			CLACT_AnmChg( wk->ArrowActWork[i], i );
			CLACT_SetDrawFlag( wk->ArrowActWork[i], 0 );
		}

	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m
	

	WirelessIconEasy();
}



// �͂��E������
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( 13 )

// �͂��E������(�E�C���h�E�p�j
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME0_M, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, 
	0, //��Ŏw�肷��
};


//==============================================================================
/**
 * $brief   �͂��E�������E�C���h�E�o�^
 *
 * @param   bgl		
 * @param   menuframe		
 * @param   y		
 * @param   yesno_bmp_cgx		
 *
 * @retval  BMPMENU_WORK *		
 */
//==============================================================================
BMPMENU_WORK *WBTower_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx )
{
	BMPWIN_DAT yesnowin;

	yesnowin        = YesNoBmpWin;
	yesnowin.pos_y  = y;
	yesnowin.chrnum = yesno_bmp_cgx;

	return BmpYesNoSelectInit( bgl, &yesnowin, WBTOWER_MENUFRAME_CHR, WBTOWER_MENUFRAME_PAL, HEAPID_WIFI_BATTLETOWER );
}



//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 * @param   to_seq		
 * @param   next_seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WBTower_SetNextSeq( WBTOWER_WORK *wk, int to_seq, int next_seq )
{
	wk->subprocess_seq      = to_seq;
	wk->subprocess_nextseq  = next_seq;
}

//------------------------------------------------------------------
/**
 * $brief   �T�u�v���Z�X�I�����̎��̍s�������͂���
 *
 * @param   wk		
 * @param   to_seq		
 * @param   next_seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void WBTower_SetNextProcess( WBTOWER_WORK *wk, int next_process )
{
	wk->sub_nextprocess = next_process;
}

//==============================================================================
/**
 * $brief   CLACT�̍��W�ύX
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_ActPos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


/*---------------------------------------------------------------------------*
  �������m�ۊ֐�
 *---------------------------------------------------------------------------*/
static void *AllocFunc( DWCAllocType name, u32   size, int align )
{
#pragma unused( name )
    void * ptr;
    OSIntrMode old;
    old = OS_DisableInterrupts();
    ptr = NNS_FndAllocFromExpHeapEx( _wtHeapHandle, size, align );
    OS_RestoreInterrupts( old );
    if(ptr == NULL){
	}
	
    return ptr;
}

/*---------------------------------------------------------------------------*
  �������J���֐�
 *---------------------------------------------------------------------------*/
static void FreeFunc(DWCAllocType name, void* ptr,  u32 size)
{
#pragma unused( name, size )
    OSIntrMode old;

    if ( !ptr ) return;
    old = OS_DisableInterrupts();
    NNS_FndFreeToExpHeap( _wtHeapHandle, ptr );
    OS_RestoreInterrupts( old );
}



//------------------------------------------------------------------
/**
 * $brief   NitroDpw_Tr������
 *
 * @param   heapPtr		
 * @param   headHandle		
 * @param   alloc		
 * @param   free		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitDpw( void *heapPtr, NNSFndHeapHandle heapHandle, DWCAllocEx alloc, DWCFreeEx free  )
{
	

	_wtHeapHandle = heapHandle;
	
	// �C�N�j���[�����]��
//	CommVRAMDInitialize();

	// wifi�������Ǘ��֐��Ăяo��
	DWC_SetMemFunc( alloc, free );


}






//==============================================================================
/**
 * $brief   WIFI�ڑ��󋵎擾
 *
 * @param   none		
 *
 * @retval  int		
 */
//==============================================================================
int WBTower_WifiLinkLevel( void )
{
    return WM_LINK_LEVEL_3 - DWC_GetLinkLevel();
}




//==============================================================================
/**
 * @brief   �T�u�v���Z�X���[�h�̐؂�ւ��w��
 *
 * @param   wk			
 * @param   subprccess	
 * @param   mode		
 *
 * @retval  none		
 */
//==============================================================================
void WBTower_SubProcessChange( WBTOWER_WORK *wk, int subprccess, int mode )
{
	wk->sub_nextprocess  = subprccess;
	wk->sub_process_mode = mode;
}
















//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCLACT( WBTOWER_WORK *wk )
{

	// VRAM �o���N�ݒ�
	VramBankSet();

	// OBJ�L�����A�p���b�g�}�l�[�W���[������
	char_pltt_manager_init();

	// CellActor�V�X�e��������
	InitCellActor(wk);
		
	// CellActro�\���o�^
	SetCellActor(wk);


	// VBlank�֐��Z�b�g
	sys_VBlankFuncChange( VBlankFunc, NULL );	
}

//------------------------------------------------------------------
/**
 * @brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeCLACT( WBTOWER_WORK *wk )
{
	int i;
	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->clactSet);
	wk->clactSet = NULL;

	//OAM�����_���[�j��
	REND_OAM_Delete();

	// ���\�[�X���
	DeleteCharManager();
	DeletePlttManager();

}




















