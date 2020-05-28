/**
 *	@file	nmix_game.c
 *	@brief	�i�b�c�~�L�T�[�@�Q�[�����C��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "savedata/record.h"

#include "nutmixer.naix"
#include "system/arc_util.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "comm_command_nutmixer.h"
#include "comm_command_nutmixer_func.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"
#include "nmix_game.h"
#include "nmix_gameseq.h"
#include "nmix_res.h"
#include "nmix_game_comm.h"
#include "nmix_game_demo.h"
#include "system/wipe.h"
#include "field/tvtopic_extern.h"

#include "include/communication/wm_icon.h"

#include "nmix_game_snd_def.h"

typedef enum{
 GAMEMAIN_SEQ_MAIN,
 GAMEMAIN_SEQ_SYNCSTART,
 GAMEMAIN_SEQ_SYNCWAIT,
};


//// �E�G�C�g
#define GAMEMAIN_GAMEEND_WAIT	( 30*1 )	// �Q�[���I�����̃E�G�C�g
#define GAMERESULT_SEEN1_WAIT	( 30*1 )	// ���ʔ��\�V�[���P�҂�
#define GAMERESULT_SEEN2_WAIT	( 30*1 )	// ���ʔ��\�V�[���Q�҂�
#define GAMERESULT_END_WAIT		( 30*20 )	// ���ʔ��\�I���҂�
#define GAMENEXT_END_WAIT		( 30*5 )	// ���ɐi�ޑ҂�
#define GAMESYS_END_WAIT		( 30*2 )	// ���S�I�����̑҂�

#define GAMESTART_NUTIN_WAIT	( 24 )	// �J�E���g�_�E���O�E�G�C�g

#define GAME_OKURI_KEY	( (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) 


/// ���ʔ��\���������x���̂��𕷂��Ƃ���
enum{
	GAMERESULT_SEQ_START = 0,			// ���ʕ\���J�n
	GAMERESULT_SEQ_WIPE_WAIT,			// ���C�v�҂�
	GAMERESULT_SEQ_SEEN1_ON,			// ����1�\��
	GAMERESULT_SEQ_SEEN2_ON,			// ����2�\��
	GAMERESULT_SEQ_SEEN2_ENDWAIT,		// ���ʕ\���I���҂�
	GAMERESULT_SEQ_PORUTO_SAVE,			// �|���g�Z�[�u
	GAMERESULT_SEQ_PORUTO_SAVEWAIT,		// �Z�[�u�҂�
	GAMERESULT_SEQ_NEXT_Q,				// �����邩����
	GAMERESULT_SEQ_NEXT_Q_WAIT,			// ����̓����҂�
	GAMERESULT_SEQ_NEXT_YES,			// ������
	GAMERESULT_SEQ_TEXTON_YAMERU,		// �n�C�����ǃ|���g�P�[�X����t��������؂̎��������Ă��Ȃ������Ƃ�
	GAMERESULT_SEQ_NEXT_NO,				// ��߂鏈��
};


///�v���g�^�C�v�錾
//===================================================
///�I�[�o�[���C�v���Z�X��`
PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq);
PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq);
PROC_RESULT NMixGameProc_End(PROC* proc,int *seq);

///�Q�[���R�}���h�v���g�^�C�v
//===================================================
static int NMixGameCom_SeqEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqSysInit( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqSysStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqDummyWait( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_SeqBefore( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameMain( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResult( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResLoad( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );
static int NMixGameCom_GameResRelease( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq );


///��ʍ\�z�֐��S
static void NMixGame_Tool_Data_DrawLink( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_SpriteDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_YazirusiDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_CommentDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_SoopEffectSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_Yazirusi_ReqDrawSet( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_KiraKira_ReqDrawSet( NMIX_GAMEWORK* wk );

/// ��
static void NMixGame_Tool_ChapuChapuSnd( NMIX_GAMEWORK* wk );


/// �ʐM���[�N�쐬
static void NMixGame_Tool_CommDataInit( NMIX_GAMEWORK* wk );
static void NMixGame_Tool_CommDataDelete( NMIX_GAMEWORK* wk );


/// �|���g�i�[����
static BOOL NMixGame_Tool_PorutoSet( NUTMIXER_WORK* mp, PORUTO_DATA* p_poruto, int num );

///�Q�[���V�[�P���X�z���`
//===================================================
typedef int (*NMixGameFunc)(NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq);

typedef struct _NMIX_GAMEMAIN_SEQ{
 NMixGameFunc	func;	///<�V�[�P���XFunc
 int			syncID;	///<�V���N��ID
}NMIX_GAMEMAIN_SEQ;

static const NMIX_GAMEMAIN_SEQ NMixGameMainTbl[] = {
	{ NMixGameCom_SeqSysInit,	SYNCHROID_BAG_END },// SYSINIT
	{ NMixGameCom_SeqSysStart,	SYNCHROID_NONE },	// SYSSTART
	{ NMixGameCom_SeqDummyWait, SYNCHROID_NONE },	// SYSSTART_WAIT
	{ NMixGameCom_SeqBefore,	SYNCHROID_NONE },	// BEFORE
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// BEFORE_WAIT
	{ NMixGameCom_GameResLoad,	SYNCHROID_GAME_START },	// RES_LOAD
	{ NMixGameCom_GameStart,	SYNCHROID_NONE },	// GAMESTART
	{ NMixGameCom_GameMain,		SYNCHROID_NONE },	// GAMEMAIN
	{ NMixGameCom_GameEnd,		SYNCHROID_NONE },	// GAMEEND
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// RESULT_WAIT
	{ NMixGameCom_GameResult,	SYNCHROID_NONE },	// RESULT
	{ NMixGameCom_SeqDummyWait,	SYNCHROID_NONE },	// SYSEND_WAIT
	{ NMixGameCom_GameResRelease,SYNCHROID_GAME_END },// RES_RELEASE
	{ NMixGameCom_SeqEnd,		SYNCHROID_NONE },
};

/**
 *	@brief VBlank���荞�݊֐�
 */
static void NMixGameVBlank(void* work)
{
	NUTMIXER_WORK	*mp = (NUTMIXER_WORK*)work;
	NMIX_GAMEWORK	*wk = (mp->app_wk);

	// �`��֌WV�u�����N�֐�
	NMixGame_GraVBlank( wk );

	DoVramTransferManager();
}


///�v���Z�X
//===================================================
/**
 *	@brief	�i�b�c�~�L�T�[�@�Q�[�����C��������
 */
PROC_RESULT NMixGameProc_Init(PROC* proc,int *seq)
{
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk;

	HeapStatePush();

	
	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_NMIXER_GM,0x20000);
	
	wk = PROC_AllocWork(proc,sizeof(NMIX_GAMEWORK),HEAPID_NMIXER_GM);
	memset(wk, 0, sizeof(NMIX_GAMEWORK));

	pp->app_wk = wk;


	wk->heapID = HEAPID_NMIXER_GM;


	// Vram�]���}�l�[�W��������
	initVramTransferManagerHeap( 16, wk->heapID );

	// �ʐM�J�n
	if( pp->comm_f == TRUE ){
		wk->commpack_flg = NUTMIX_COMM_PACK_COMM; 
	}else{
		wk->commpack_flg = NUTMIX_COMM_PACK_ONE;
	}
	CommCommandNutMixerInitialize( wk, pp->param->mySave );

	// �R���t�B�O���擾
	wk->wnd_type = CONFIG_GetWindowType( pp->param->configSave );
	wk->msg_speed = CONFIG_GetMsgPrintSpeed( pp->param->configSave );

	// OAM�\��
	wk->clact_draw = TRUE;

	// V�u�����N�֐��o�^
	sys_VBlankFuncChange( NMixGameVBlank, pp );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~
	
	// �T�E���h�f�[�^���[�h(����)
	Snd_DataSetByScene( SND_SCENE_NUTMIXER, SEQ_KINOMI1, 1 );

	return PROC_RES_FINISH;
}

/**
 *	@brief	�i�b�c�~�L�T�[�@�Q�[�����C��
 */
PROC_RESULT NMixGameProc_Main(PROC* proc,int *seq)
{
	int	now_seq,synchro;
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk = (NMIX_GAMEWORK*)PROC_GetWork(proc);

	const NMIX_GAMEMAIN_SEQ *sp;
	
	now_seq = wk->main_seq;
	sp = &(NMixGameMainTbl[now_seq]); 

	switch(*seq){
	case GAMEMAIN_SEQ_MAIN:
		if(sp->func == NULL){
			break;
		}
		//���C���Ăяo��
		synchro = sp->syncID;
		wk->main_seq = (sp->func)(pp,wk,&wk->sub_seq); 
		
		// ���N�G�X�g�V�[�P���X��ݒ�
		if( wk->main_seq_chg_req ){
			wk->main_seq = wk->main_seq_req;
			wk->main_seq_chg_req = FALSE;
		}
			
		if(now_seq == wk->main_seq){
			break;
		}
		//���Z�b�g
		wk->sub_seq = 0;	//���Z�b�g

		if(!pp->comm_f){
			break;	//���[�J���v���C
		}

		//�ʐM�v���C
		if(synchro == SYNCHROID_NONE){
			break;
		}
		//�ʐM�����ɓ���
		wk->synchroID = synchro;

		*seq = GAMEMAIN_SEQ_SYNCSTART;
		break;
	case GAMEMAIN_SEQ_SYNCSTART:
		CommTimingSyncStart(wk->synchroID);
		*seq = GAMEMAIN_SEQ_SYNCWAIT;
		break;
	case GAMEMAIN_SEQ_SYNCWAIT:
		if(!CommIsTimingSync(wk->synchroID)){
			break;
		}
		//�ʐM�����I��&���̃V�[�P���X��
		*seq = GAMEMAIN_SEQ_MAIN;
		wk->synchroID = 0;
		break;
	}

	// �`�揈��
	NMixGame_Draw( wk );

	// �ʐM�G���[����
	CommErrorCheck( wk->heapID, wk->bgl );
	
	if( wk->seqend_f ){
		return PROC_RES_FINISH;
	}else{
		return PROC_RES_CONTINUE;
	}
}

/**
 *	@brief	�i�b�c�~�L�T�[�@�Q�[�����C���I��
 */
PROC_RESULT NMixGameProc_End(PROC* proc,int* seq)
{
	int	heapID;
	NUTMIXER_WORK* pp = PROC_GetParentWork(proc);
	NMIX_GAMEWORK* wk = (NMIX_GAMEWORK*)PROC_GetWork(proc);

	heapID = wk->heapID;

	// �ʐM�j��
	CommCommandNutMixerDest( wk );

	// V�u�����N�֐��o�^
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// Vram�]���}�l�[�W���j��
	DellVramTransferManager();

	//���[�N���
	MI_CpuClear8(wk,sizeof(NMIX_GAMEWORK));
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(heapID);

	pp->app_wk = NULL;
	
	sys_DeleteHeap(heapID);
	return PROC_RES_FINISH;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�P���X�ݒ肨�肢
 *
 *	@param	p_work	�Q�[�����[�N
 *	@param	seq		�ݒ�V�[�P���X
 */
//-----------------------------------------------------------------------------
void NMIX_SetMainSeq( NMIX_GAMEWORK* p_work, int seq )
{
	p_work->main_seq_req = seq;
	p_work->main_seq_chg_req = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�����N�G�X�g
 *
 *	@param	p_work	���[�N
 */
//-----------------------------------------------------------------------------
void NMIX_SetEndReq( NMIX_GAMEWORK* p_work )
{
	p_work->seqend_f = TRUE;
}


//======================================================
//�Q�[���v���Z�X�@�R�}���h�Q
//======================================================
//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�������̏�����	
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqSysInit( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	switch( *seq ){
	case 0:
		// �ʐM���[�N������
		NMixGame_Tool_CommDataInit( wk );

		// �e���`�F�b�N
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			NMIX_DATA_OyaInit( &wk->oya_data );	
		}
		NMixGameDemo_SubWin_Init( &wk->sub_win,
				wk->comm_count, &wk->msgDat, &wk->game_comm_pack,
				wk->wnd_type, wk->heapID );
		NMixGameDemo_NabeGra_Init( &wk->nabe_gra );
		NMixGameDemo_MainWin_Init( &wk->main_win,
				wk->comm_count, &wk->msgDat, &wk->game_comm_pack,
				wk->wnd_type, wk->heapID );


		
		NMixGameDemo_CountDown_Init( &wk->countdown );
		NMixGameDemo_CountDown_Init( &wk->end_mark );
		NMixGameDemo_CountDown_Init( &wk->pen );
		NMixGameDemo_OtherMark_Init( &wk->other_mark, &wk->game_comm_pack, wk->comm_count, wk->comm_work );
		NMixGameDemo_SoopEffect_Init( &wk->soop_effect );
		NMixGameDemo_Yazirusi_Init( &wk->yazirusi );
		NMixGameDemo_HosiKiraKira_Init( &wk->hosi_kira, wk->comm_count );

		NMIX_DATA_KoInit( &wk->ko_data );

		NMixGameCom_GameStartGraphicInit( wk );

		// COMM_ICON�ݒ�
		WirelessIconEasy();	
		// ���C����ʁAOAM�\��
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

		// �ʐM���肪����Ƃ�
		if( wk->comm_count > 1 ){
			// ���̂܂܂��҂���������
			NMixGameDemo_SubWin_WinWaitMsgOn( &wk->sub_win );
		}

		// ��O���t�B�b�NON
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_NABE_UP, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_NABE_DOWN, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_0, TRUE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_1, TRUE );	

		(*seq) ++;
		break;

	case 1:
		
		//�u���b�N�C��
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_OUTCOLOR, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq)++;
		break;

	case 2:
		if( WIPE_SYS_EndCheck() ){
			return wk->main_seq + 1;
		}
		break;
	}

	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�������̊J�n	�e�[���q�J�n����
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqSysStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	// �e�̂Ƃ��A�q�ɊJ�n���߂�]��
	if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
		NMIX_CommPack_CommSendData( CNM_MIXER_GAME_SYS_START,
			NULL, 0, wk->comm_work );
	}
	return wk->main_seq + 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�E�G�C�g�@�e�Ƃ̓����҂��p
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqDummyWait( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���O����		�؂̎��f�[�^�̓]���Ȃ�
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_SeqBefore( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	switch( *seq ){
	case 0:
		// �������[�N�Ȃǂ̃������m�ۂ��s��
		NMixGameDemo_NutsIn_Init( &wk->nuts_in, wk->comm_count );
		(*seq) ++;
		break;
	case 1:
		wk->game_comm_pack.send_before_data.nut_type = mp->itemno;
		
		// �؂̎��f�[�^�]��
		NMIX_CommPack_CommSendData( CNM_MIXER_GAME_BEFOREDATA, 
				&wk->game_comm_pack.send_before_data, 
				CommNutMixerGetGameBeforeSize(), wk->comm_work );	
		(*seq) ++;
		return wk->main_seq + 1;
	}
	return wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���J�n������	�t�F�[�h�C���@�|���b�N�������J�E���g�_�E�����
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameStart( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	u32 main_ret;
	int net_id;
	BOOL check;
	
	switch( *seq ){
	case 0:
		// YESNO���[�N������	BGL���Ђ悤�Ȃ̂ł����Ŋm��
		NMixGameDemo_YesNoWnd_Init( &wk->yes_no, wk->heapID, wk->bgl );

		(*seq) ++;
		break;

	case 1:
		// �F�̃|���b�N�𓊓�
		NMixGameDemo_NutsIn_Start( &wk->nuts_in );
		(*seq)++;
		break;

	case 2:
		main_ret = NMixGameDemo_NutsIn_Main( &wk->nuts_in );
		if( main_ret == NMIX_DEMO_NUTS_RET_TRUE ){
			(*seq)++;
			NMixGameDemo_SubWin_WinNutsOff( &wk->sub_win );

			wk->wait = GAMESTART_NUTIN_WAIT;
		}else if( main_ret != NMIX_DEMO_NUTS_RET_FALSE ){

			// �`�����ꂽ�I�I
			net_id = wk->game_comm_pack.playno_netid[ main_ret - NMIX_DEMO_NUTS_RET_NUTS_00 ];
			// ���������ƃe�L�X�g���o��
			NMixGameDemo_SubWin_WinNutsOn( &wk->sub_win, wk->game_comm_pack.get_ko_before_data.before[ net_id ].nut_type );

		}
		break;

	case 3:	// �y���\��
		// �E�G�C�g�����
		if( wk->wait > 0 ){
			wk->wait--;
			break;
		}
		
		NMixGameDemo_CountDown_Start_Pen( &wk->pen );

		(*seq)++;
		break;
	
	case 4:	// �J�E���g�_�E���J�n

		// �y�����I���̂�҂�
		if( NMixGameDemo_CountDown_Main( &wk->pen ) == FALSE ){
			break;
		}
		
		// ��̊G��ύX
		NMixGameDemo_SubWin_PlayerNameOn( &wk->sub_win );

		// �J�E���g�_�E���J�n
		NMixGameDemo_CountDown_Start( &wk->countdown );

		(*seq)++;
		break;

	case 5:	// �J�E���g�_�E�����I������烁�C����
		check = NMixGameDemo_CountDown_Main( &wk->countdown );

		// �A�j���t���[�����ς�����特��炷
		{
			int anm_num = CLACT_AnmFrameGet( wk->countdown.clact );
			if( wk->last_count_down != (anm_num+1) / 3 ){
				// �Ō��1��́A�X�^�[�g���ɂȂ�
				if( anm_num < 10 ){
					// �J�n
					Snd_SePlay( NMIXGAME_SE_COUNT_DOWN );
				}else{

					// �J�n
					Snd_SePlay( NMIXGAME_SE_GAME_START );
				}
				wk->last_count_down = (anm_num+1) / 3;
			}
		}
		if( check ){

			NMixGameDemo_OtherMark_DrawFlag( &wk->other_mark, TRUE );

			// �΃A�j���J�n
			NMixGameDemo_NabeGra_FireAnmStart( &wk->nabe_gra );

			
			return wk->main_seq + 1;
		}
		break;
	}
	return  wk->main_seq;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����C������	���ۂ̃Q�[������
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameMain( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	BOOL result;
	
	//-------------------------------------
	//	�]���f�[�^�쐬��
	//=====================================
	// �q����
	NMIX_DATA_KoMain( &wk->ko_data );
	// �q�]���f�[�^�쐬
	NMIX_DATA_KoMake( &wk->game_comm_pack.send_game_data.one,
			&wk->ko_data );
	// �e����
	if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
		// �e�������C��
		result = NMIX_DATA_OyaMain( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );

		// �I����������
		if( result == TRUE ){
//			OS_Printf( "�I����]��\n" );
			result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_END, NULL, 0, wk->comm_work );
			GF_ASSERT( result );
			return wk->main_seq;
		}

		NMIX_DATA_OyaCookCountAdd( &wk->oya_data );
		
		NMIX_DATA_OyaCommDataMake( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );	// �ʐM�f�[�^�ݒ�
	}

	// �]��
	result = NMIX_CommPack_CommSendData( CNM_MIXER_GAMEDATA, &wk->game_comm_pack.send_game_data, CommNutMixerGetGameSize(), wk->comm_work );
	if( result == FALSE ){

#ifdef PM_DEBUG
		wk->comm_err_count ++;
#endif
	}

	//-------------------------------------
	//	�`��f�[�^�쐬��
	//=====================================
	NMixGame_Tool_Data_DrawLink( wk );

	// �X�[�v�G�t�F�N�g����
	NMixGameDemo_SoopEffect_Main( &wk->soop_effect, &wk->game_comm_pack );

	// ���G�t�F�N�g���C��
	NMixGameDemo_Yazirusi_Main( &wk->yazirusi );

	// �L���L���G�t�F�N�g���C��
	NMixGameDemo_HosiKiraKira_Main( &wk->hosi_kira );

	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���I������	�Q�[���I������	�h�����h�@������@�t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameEnd( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	PORUTO_DATA* p_poruto;
	BOOL result;

	// �Q�[���I���O�ɃG�t�F�N�g���o�Ă���\��������̂�
	// �����ŏI��点��
	// �X�[�v�G�t�F�N�g����
	NMixGameDemo_SoopEffect_Main( &wk->soop_effect, &wk->game_comm_pack );


	switch( *seq ){
	case 0:
		// �R�����g���o�Ă�����Ƃ߂�
		NMixGameDemo_StopComment( &wk->main_win );

		// ��󂪏o�Ă�����Ƃ߂�
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
		
		// �I���ƕ\��
		NMixGameDemo_CountDown_Start( &wk->end_mark );

		// ���ƂƂ߂�
		Snd_SeStopBySeqNo(NMIXGAME_SE_SOBORO_ROTA,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_SOBORO_KOGE,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_GAME_KIRAKIRA,0);
        Snd_SeStopBySeqNo(NMIXGAME_SE_GAME_ROTAWAY_ON,0);

		// �I��艹
		Snd_SePlay( NMIXGAME_SE_GAME_END );

		// �΂�����
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_0, FALSE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_1, FALSE );	
		NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_2, FALSE );	

		(*seq) ++;
		break;

	case 1:
		// �J�E���g�_�E���҂�
		if( NMixGameDemo_CountDown_Main( &wk->end_mark ) == FALSE ){
			break;
		}

		// ��ʃt�F�[�h�A�E�g
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case 2:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;
	
	case 3:
		// ���R�[�h�@�X�R�A����
		{
			RECORD* p_record = SaveData_GetRecord( mp->param->SaveData );
			if( wk->commpack_flg == NUTMIX_COMM_PACK_ONE ){
				RECORD_Score_Add( p_record, SCORE_ID_MINIGAME_NUTS );
			}else{
				RECORD_Score_Add( p_record, SCORE_ID_COMM_MINIGAME_NUTS );
			}
		}

		// �e�Ȃ�|���g�f�[�^�]�����s��
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			p_poruto = PorutoData_AllocWork( wk->heapID );
			NMIX_DATA_OyaCalcPorutoData( &wk->oya_data, p_poruto, &wk->game_comm_pack, wk->comm_count, wk->heapID );

			// �]��
			result = NMIX_CommPack_CommSendData( CNM_MIXER_PORUTO_DATA, p_poruto, PorutoData_GetWorkSize(), wk->comm_work );
			GF_ASSERT( result );

			sys_FreeMemoryEz( p_poruto );
		}
		(*seq) ++;
		break;

	case 4:
		// �e�Ȃ猋�ʓ]�����s��
		if( NMIX_CommPack_CommGetCurrentID( wk->comm_work ) == COMM_PARENT_ID ){
			
			// ���ʍ쐬
			NMIX_DATA_OyaCommDataMake_Result( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
			if( sys.cont & PAD_BUTTON_A ){
				NMIX_DATA_OyaCommDataMake_Result_MaxDebug( &wk->oya_data, &wk->game_comm_pack, wk->comm_count );
			}
#endif	// NMIX_DEBUG_DUMMY_RESULT_ON

			// �]��
			result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_RESULTDATA, &wk->game_comm_pack.send_oya_result_data, CommNutMixerGetGameResultSize(), wk->comm_work );
			GF_ASSERT( result );
		}
		return wk->main_seq + 1;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����ʕ\��	�t�F�[�h�C���[���\���[���t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResult( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	u32 yes_no;
	BOOL result;
	u8 send_data;

	switch( *seq ){
	case GAMERESULT_SEQ_START:
		NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN0 );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		wk->clact_draw = FALSE;	// OAM�\��OFF
//		CLACT_DrawFlagSet( wk->clact.cas, FALSE );	// OAM��\��

		// �|���g�\��ON
		NMixGameDemo_PorutoDraw_Init( &wk->poruto_draw, NMIX_DEMO_RESULT_PORUTO_DRAW_X, NMIX_DEMO_RESULT_PORUTO_DRAW_Y, wk->game_comm_pack.get_result_data.poruto_type, wk->heapID );
	
		// ��ʃt�F�[�h�C��
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case GAMERESULT_SEQ_WIPE_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq)++;
			wk->wait = GAMERESULT_SEEN1_WAIT;
		}
		break;

	case GAMERESULT_SEQ_SEEN1_ON:
		wk->wait --;
		if( wk->wait < 0 ){
			NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN1 );

			// ���ʕ\��
			Snd_SePlay( NMIXGAME_SE_GAME_RESULT_ON );
			(*seq)++;
			wk->wait = GAMERESULT_SEEN2_WAIT;
		}
		break;
		
	case GAMERESULT_SEQ_SEEN2_ON:
		wk->wait --;
		if( wk->wait < 0 ){
			NMixGameDemo_ResultOn( &wk->main_win, NMIX_DEMO_MINWIN_RESULT_SEEN2 );

			NMixGameDemo_PorutoDraw_Draw( &wk->poruto_draw );

			// ���ʕ\��
			Snd_SePlay( NMIXGAME_SE_GAME_RESULT_ON );
			(*seq)++;
			wk->wait = GAMERESULT_END_WAIT;
		}
		break;

	case GAMERESULT_SEQ_SEEN2_ENDWAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_trg = 1;	//�^�b�`�p�l���������ςȂ�
#endif	// DEBUG_NUTMIXER_AUTO
	
		// 10�b�����A�^�b�`���ꂽ��I���
		wk->wait --;
		if( (wk->wait < 0) || (sys.tp_trg) || (sys.trg & GAME_OKURI_KEY) ){
			(*seq)++;
			break;
		}
		NMixGameDemo_PorutoDraw_Draw( &wk->poruto_draw );
		break;

	case GAMERESULT_SEQ_PORUTO_SAVE:		// �Z�[�u�f�[�^�Ƀ|���b�N��ǉ�����
		// �|���g�j��
		NMixGameDemo_PorutoDraw_Delete( &wk->poruto_draw );

		// �e�L�X�g��\��
		NMixGameDemo_ResultOff( &wk->main_win );

#ifndef DEBUG_NUTMIXER_AUTO
		// �|���g�i�[
		NMixGame_Tool_PorutoSet( mp, wk->game_comm_pack.p_get_ko_poruto, wk->comm_count );
#endif
		NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO );
		wk->wait = GAMENEXT_END_WAIT;
		(*seq)++;
		break;

	case GAMERESULT_SEQ_PORUTO_SAVEWAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_trg = 1;	//�^�b�`�p�l���������ςȂ�
#endif	// DEBUG_NUTMIXER_AUTO
		wk->wait --;
		// �^�b�`�����玟��
		if( (sys.tp_trg) || (wk->wait < 0) || (sys.trg & GAME_OKURI_KEY) ){
			(*seq)++;
		}
		break;

	case GAMERESULT_SEQ_NEXT_Q:
		// �Ђ��Â��|���g���쐬���܂����H
		NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI );

		// YESNO�E�B���h�E
		NMixGameDemo_YesNoWnd_Start( &wk->yes_no );


#ifdef DEBUG_NUTMIXER_AUTO
		wk->wait = 2600;
#endif

		(*seq)++;
		break;

	case GAMERESULT_SEQ_NEXT_Q_WAIT:
#ifdef DEBUG_NUTMIXER_AUTO
		wk->wait --;

		if( sys.trg & PAD_BUTTON_A ){
			OS_Printf( "wait %d\n", wk->wait );
		}
		if( wk->wait < 0 ){
			sys.tp_trg = 1;	//�^�b�`�p�l���������ςȂ�
			sys.tp_cont = 1;//�^�b�`�p�l���������ςȂ�
			sys.tp_x = (24 * 8) + 2;
			sys.tp_y = (8 * 8) + 2;//*/
/*			// �q�@�ʐM���I��点��
			if( wk->game_comm_pack.my_netid != COMM_PARENT_ID ){
				CommSetError();
//				sys.DontSoftReset = 0xff;
			}
//*/
		}
#endif	// DEBUG_NUTMIXER_AUTO

		yes_no = NMixGameDemo_YesNoWnd_Main( &wk->yes_no );

		if( (yes_no == TOUCH_SW_RET_YES) ||
			(yes_no == TOUCH_SW_RET_NO) ){

			if( yes_no == TOUCH_SW_RET_YES ){

				// �܂��|���g���͂��邩�`�F�b�N
				//�|���g�P�[�X�������ς��łȂ����`�F�b�N
				if( PORUTO_GetDataNum( mp->param->poruSave ) >= PORUTO_STOCK_MAX ){
				
					NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI );
					(*seq) = GAMERESULT_SEQ_TEXTON_YAMERU;	// ��߂鏈����

					wk->wait = GAMENEXT_END_WAIT;
					break;
				}
				// �o�b�O�̒��ɖ؂̎������邩�`�F�b�N
				if( MyItem_CheckItemPocket( mp->param->itemSave ,BAG_POKE_NUTS) == FALSE ){
					NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE );
					(*seq) = GAMERESULT_SEQ_TEXTON_YAMERU;	// ��߂鏈����
					wk->wait = GAMENEXT_END_WAIT;
					break;
				}
				
				(*seq) = GAMERESULT_SEQ_NEXT_YES;

			}else{
				(*seq) = GAMERESULT_SEQ_NEXT_NO;
			}

			if( wk->comm_count > 1 ){
				// �ʐM�ҋ@��
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI );
			}
		}
		break;

	case GAMERESULT_SEQ_NEXT_YES:
		wk->game_next = TRUE;
		// �܂�������Ɛe�ɓ]��
		result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT, &wk->game_next, CommNutMixerGetOneSize(), wk->comm_work );
		GF_ASSERT( result );
		return  wk->main_seq + 1;

	case GAMERESULT_SEQ_TEXTON_YAMERU:	// �|���g����t�̂Ƃ�
		wk->wait --;
		// �^�b�`�����玟��
		if( (sys.tp_trg) || (wk->wait < 0) || (sys.trg & GAME_OKURI_KEY) ){

			if( wk->comm_count > 1 ){
				// �ʐM�ҋ@��
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI );
			}

			(*seq) = GAMERESULT_SEQ_NEXT_NO;
		}
		break;
		
	case GAMERESULT_SEQ_NEXT_NO:
		// ������߂�Ɛe�ɓ]��
		wk->game_next = FALSE;
		result = NMIX_CommPack_CommSendData( CNM_MIXER_GAME_NEXT, &wk->game_next, CommNutMixerGetOneSize(), wk->comm_work );
		GF_ASSERT( result );
		return  wk->main_seq + 1;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return  wk->main_seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����\�[�X�ǂݍ���
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResLoad( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{
	return NMixGameCom_ResInit( wk, seq );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[�����\�[�X�j��
 */
//-----------------------------------------------------------------------------
static int NMixGameCom_GameResRelease( NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq )
{

	switch( *seq ){
	case 0:
		if( wk->game_comm_pack.get_game_next == TRUE ){
			
			// �o�b�O����؂̎���I��ł�������
			NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_BAG );
			mp->game_next = TRUE;
		}else{
			mp->game_next = FALSE;
			// ������������Ȃ̂ɁA�e���痈�����߂��I���̂Ƃ�
			if( wk->game_next == TRUE ){
				// �s���������Ȃ����ЂƂ����܂�
				NMixGameDemo_TextOn( &wk->main_win, NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU );
			}else{

				// 1�l�p�̂Ƃ��̓E�G�C�g����Ȃ�
				// �����l���p�́A�t�F�[�h�A�E�g�̃^�C�~���O��
				// ���킹�邽�߃E�G�C�g�������
				if( wk->comm_count <= 1 ){
					(*seq) = 2;
					break;
				}
			}

			// �`���m�[�g
			{
				void* buff;
				if( wk->commpack_flg == NUTMIX_COMM_PACK_COMM ){
					buff = FNOTE_SioPorutoDataMake( wk->heapID );	
					FNOTE_DataSave( mp->param->fnote, buff, FNOTE_TYPE_SIO );
				}
			}
		
		}
		wk->wait = GAMESYS_END_WAIT;
		(*seq)++;
		break;
	
	case 1:
		wk->wait --;
		if( (wk->wait < 0) ){
			(*seq)++;
		}
		break;

	case 2:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, wk->heapID );
		(*seq) ++;
		break;

	case 3:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;


	case 4:
		NMixGameCom_ResRelease( wk, seq );
		NMixGameCom_GameStartGraphicRelease(  wk );
		return wk->main_seq + 1;
	};

	return  wk->main_seq;
}

/**
 *	@brief	�R�}���h �Q�[���v���Z�X�I���@
 */
static int NMixGameCom_SeqEnd(NUTMIXER_WORK* mp,NMIX_GAMEWORK* wk,int* seq)
{
	// �m�ۂ��Ă������[�N��j������
	NMixGameDemo_NutsIn_Delete( &wk->nuts_in );
	NMixGameDemo_SubWin_Delete( &wk->sub_win );
	NMixGameDemo_CountDown_Delete( &wk->countdown );
	NMixGameDemo_CountDown_Delete( &wk->end_mark );
	NMixGameDemo_CountDown_Delete( &wk->pen );
	NMixGameDemo_NabeGra_Delete( &wk->nabe_gra );
	NMixGameDemo_OtherMark_Delete( &wk->other_mark );
	NMixGameDemo_MainWin_Delete( &wk->main_win );
	NMixGameDemo_SoopEffect_Delete( &wk->soop_effect );
	NMixGameDemo_Yazirusi_Delete( &wk->yazirusi );
	NMixGameDemo_HosiKiraKira_Delete( &wk->hosi_kira );
	NMixGameDemo_YesNoWnd_Delete( &wk->yes_no );

	// �ʐM���[�N�j��
	NMixGame_Tool_CommDataDelete( wk );

	// �ʐM�G���[����\��
#ifdef PM_DEBUG
	OS_Printf( "�ʐM�G���[���@%d\n", wk->comm_err_count );
#endif
	
	NMIX_SetEndReq( wk );
	return wk->main_seq; 
}









//-----------------------------------------------------------------------------
/**
 * 
 *		�`��\�z�֐��֘A
 * 
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�Q�[���f�[�^��`��ɔ��f������
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_Data_DrawLink( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	fx32 scale;
	
	// �O���t�B�b�N��]
	NMixGameDemo_NabeGra_GraphicSetSoopRota( &wk->nabe_gra, p_oya->rota );

	// �`���v�`���v��
	NMixGame_Tool_ChapuChapuSnd( wk );

	// �O���t�B�b�N�g�嗦
	scale = NMIX_DATA_SoopSpeedGraScale( p_oya->rota_sp, p_oya->mix_type );
	NMixGameDemo_NabeGra_GraphicSetSoopScale( &wk->nabe_gra, scale );

	// �΃A�j��
	NMixGameDemo_NabeGra_FireAnm( &wk->nabe_gra, p_oya->mix_type );


	// �F�̈ʒu��ݒ�
	NMixGameDemo_OtherMark_Main( &wk->other_mark );

	// �X�v���C�g�`��ݒ�
	NMixGame_Tool_SpriteDrawSet( wk );

	// �����ύX
	NMixGame_Tool_Yazirusi_ReqDrawSet( wk );

	// �t��]�G�t�F�N�g
	NMixGame_Tool_YazirusiDrawSet( wk );

	// ������@���ڂ��@�e�L�X�g�`��
	NMixGame_Tool_CommentDrawSet( wk );

	// ������@���ڂ��@�G�t�F�N�g�ݒ�
	NMixGame_Tool_SoopEffectSet( wk );

	// �L���L���G�t�F�N�g
	NMixGame_Tool_KiraKira_ReqDrawSet( wk );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�v���C�g�`��@�ݒ�
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_SpriteDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u8 draw_flg[ NMIX_SOOPTYPE_SOOP_NUM ][7] = {
		{
			TRUE, TRUE, FALSE,
			TRUE, FALSE, FALSE,
			NMIX_DEMO_NABE_OBJ_SOOP_0,	// ���l��ݒ肷��X�[�v
		},
		{
			FALSE, TRUE, TRUE,
			FALSE, TRUE, FALSE,
			NMIX_DEMO_NABE_OBJ_SOOP_1,
		},
		{
			FALSE, FALSE, TRUE,
			FALSE, FALSE, TRUE,
			NMIX_DEMO_NABE_OBJ_NUM,	// =none
		},	
	};

	// �X�[�v�^�C�v�̃O���t�B�b�N�ݒ�
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_0, draw_flg[ p_oya->mix_type ][0] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_1, draw_flg[ p_oya->mix_type ][1] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_SOOP_2, draw_flg[ p_oya->mix_type ][2] );

	// �Ή���
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_0, draw_flg[ p_oya->mix_type ][3] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_1, draw_flg[ p_oya->mix_type ][4] );
	NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, NMIX_DEMO_NABE_OBJ_FIRE_2, draw_flg[ p_oya->mix_type ][5] );

	// ���l�ݒ�
	if( draw_flg[ p_oya->mix_type ][6] != NMIX_DEMO_NABE_OBJ_NUM ){
		if( p_oya->alpha_num > 0 ){
			NMixGameDemo_NabeGra_GraphicSetAlpha( &wk->nabe_gra, draw_flg[ p_oya->mix_type ][6], p_oya->alpha_num );
		}else{
			NMixGameDemo_NabeGra_GraphicSetDrawFlg( &wk->nabe_gra, draw_flg[ p_oya->mix_type ][6], FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t��]���\������
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_YazirusiDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;

	// ��]���N�G�X�g�����ƈ�v���Ă��邩�`�F�b�N
	// �����x�����o�Ă���Ƃ�������
	if( (p_oya->now_rota_req == p_oya->rota_way) ||
		(p_oya->rota_sp == 0) || ( wk->houkou_draw_flg != 0 ) ){	// ��]���x�O�̂Ƃ��͊֌W�Ȃ�
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
		NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
		// �\��OFF
		wk->gyaku_draw_flg = 0;
	}else{
		// �t�ł���I
		if( p_oya->now_rota_req == 0 ){
			if( wk->gyaku_draw_flg != NMIX_GAME_WAY_FLAG_RIGHT ){
				// �E�ɉ��`
				NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );
				wk->gyaku_draw_flg = NMIX_GAME_WAY_FLAG_RIGHT;
				// ������OFF
				NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );

				// �t��]
				Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			}
		}else{
			// ���ɉ��`
			if( wk->gyaku_draw_flg != NMIX_GAME_WAY_FLAG_LEFT ){
				// ���ɉ��`
				NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT_R );
				wk->gyaku_draw_flg = NMIX_GAME_WAY_FLAG_LEFT;
				// �E����OFF
				NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT_R );

				// �t��]
				Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			}
		}
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�R�����g�`�搧��
 *
 *	���̃G�t�F�N�g�́A
 *	�t��]�G�t�F�N�g�ݒ��ɌĂԕK�v������܂�
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommentDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u8 kobore_comm[ NMIX_SOOPTYPE_SOOP_NUM ] ={
		NMIX_STMSG_SPEED_HAYAI00, NMIX_STMSG_SPEED_HAYAI01, 0
	};
	static const u8 kogeru_comm[ NMIX_SOOPTYPE_SOOP_NUM ] ={
		NMIX_STMSG_SPEED_KOGERU00, NMIX_STMSG_SPEED_KOGERU01, NMIX_STMSG_SPEED_KOGERU02
	};
 	
	// �t��]���]�����x�������Ă���Ƃ��́A�\�����Ȃ�
	if( (wk->gyaku_draw_flg != 0) || 
		(wk->houkou_draw_flg != 0) ){
		NMixGameDemo_StopComment( &wk->main_win );
		wk->kobore_draw_flg = FALSE;
		wk->kogeru_draw_flg = FALSE;
	}else{

		// �X�s�[�h�`�F�b�N
		// ���ڂ�
		if( wk->kobore_draw_flg == FALSE ){

			if( p_oya->kobore_req ){
				NMixGameDemo_StopComment( &wk->main_win );
				NMixGameDemo_StartComment( &wk->main_win, kobore_comm[ p_oya->mix_type ] );
				wk->kobore_draw_flg = TRUE;
				wk->kogeru_draw_flg = FALSE;
			}
		}else{
			// �I�������t���O��������
			if( NMixGameDemo_EndCheckComment( &wk->main_win ) ){
				wk->kobore_draw_flg = FALSE;
			}
		}
		
		// ������
		if( wk->kogeru_draw_flg == FALSE ){

			if( p_oya->koge_req ){
				NMixGameDemo_StopComment( &wk->main_win );
				NMixGameDemo_StartComment( &wk->main_win, kogeru_comm[ p_oya->mix_type ] );
				wk->kogeru_draw_flg = TRUE;
				wk->kobore_draw_flg = FALSE;
			}
		}else{
			// �I�������t���O��������
			if( NMixGameDemo_EndCheckComment( &wk->main_win ) ){
				wk->kogeru_draw_flg = FALSE;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�[�v�G�t�F�N�g�ݒ�
 *
 *	@param	wk	���[�N
 *
 *	���������܂�
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_SoopEffectSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u32 SoopEffectKoboreSndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_KOBORE,
		NMIXGAME_SE_CREAM_KOBORE,
		NMIXGAME_SE_CREAM_KOBORE
	};
	static const u32 SoopEffectKogeSndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_KOGE,
		NMIXGAME_SE_CREAM_KOGE,
		NMIXGAME_SE_SOBORO_KOGE
	};

	
	if( p_oya->kobore_req ){
		NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DMEO_SOOP_EFF_TYPE_KOBORE );

		// ���ڂꉹ
		Snd_SePlay( SoopEffectKoboreSndTbl[ p_oya->mix_type ] );
	}
	
	if( p_oya->koge_req == NMIX_GAME_COMM_KOGE_KOGE_REQ ){
		
			NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DEMO_SOOP_EFF_TYPE_KOGE );
			
			// ������
			Snd_SePlay( SoopEffectKogeSndTbl[ p_oya->mix_type ] );
		
	}else if( p_oya->koge_req == NMIX_GAME_COMM_KOGE_KEMURI_REQ ){
		NMixGameDemo_SoopEffect_Add( &wk->soop_effect, p_oya->mix_type, NMIX_DMEO_SOOP_EFF_TYPE_KEMURI );
	}

	// �X�[�v�̃X�s�[�h�����傤�Ǘǂ��Ȃ����炱��������
	if( NMIX_DATA_SoopSpeedKoge( p_oya->rota_sp, p_oya->mix_type ) == FALSE ){
		NMixGameDemo_SoopEffect_DelReq( &wk->soop_effect );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̉�]�����@�`��
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_Yazirusi_ReqDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	BOOL result;

	// ���̉�]�����Ɛe���痈����]�������Ⴄ���`�F�b�N
	if( p_oya->rota_req_eff ){
		
		// ��]�����G�t�F�N�g�ݒ�
		if( p_oya->now_rota_req == 0 ){
			// �E��
			NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
			NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
			
			// �����w��
			Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			
			wk->houkou_draw_flg = NMIX_GAME_WAY_FLAG_RIGHT;
		}else{
			// ����
			NMixGameDemo_Yazirusi_Add( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
			NMixGameDemo_Yazirusi_Stop( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );

			// �����w��
			Snd_SePlay( NMIXGAME_SE_GAME_ROTAWAY_ON );
			wk->houkou_draw_flg = NMIX_GAME_WAY_FLAG_LEFT;
		}
	}

	// �\������������t���O��OFF
	if( wk->houkou_draw_flg == NMIX_GAME_WAY_FLAG_RIGHT ){
		
		result = NMixGameDemo_Yazirusi_EndCheck( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_RIGHT );
		if( result == TRUE ){
			wk->houkou_draw_flg = 0;
		}
	}else if( wk->houkou_draw_flg == NMIX_GAME_WAY_FLAG_LEFT ){

		result = NMixGameDemo_Yazirusi_EndCheck( &wk->yazirusi, NMIX_DEMO_YAZIRUSI_LEFT );
		if( result == TRUE ){
			wk->houkou_draw_flg = 0;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�L���L���G�t�F�N�g
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_KiraKira_ReqDrawSet( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	int x = wk->game_comm_pack.send_game_data.one.x;
	int y = wk->game_comm_pack.send_game_data.one.y;

	if( p_oya->kirakira_eff == 1 ){
		NMixGameDemo_HosiKiraKira_Add( &wk->hosi_kira, x, y );

		// �L���L����
		Snd_SePlay( NMIXGAME_SE_GAME_KIRAKIRA );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM���[�N����������
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommDataInit( NMIX_GAMEWORK* wk )
{
	int i;
	wk->game_comm_pack.p_get_ko_poruto = PorutoData_AllocWork( wk->heapID );
	wk->game_comm_pack.my_netid = NMIX_CommPack_CommGetCurrentID( wk->comm_work );


	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		wk->game_comm_pack.get_game_data[ i ].one.x = 128;
		wk->game_comm_pack.get_game_data[ i ].one.y = 96;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʐM���[�N�j������
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_CommDataDelete( NMIX_GAMEWORK* wk )
{
	GF_ASSERT( wk->game_comm_pack.p_get_ko_poruto );
	sys_FreeMemoryEz( wk->game_comm_pack.p_get_ko_poruto );
	wk->game_comm_pack.p_get_ko_poruto = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|���g�f�[�^���Z�[�u����
 *
 *	@param	wk			���[�N
 *	@param	p_poruto	�|���g�f�[�^
 *	@param	num			�i�[��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	�P�[�X����t
 */
//-----------------------------------------------------------------------------
static BOOL NMixGame_Tool_PorutoSet( NUTMIXER_WORK* mp, PORUTO_DATA* p_poruto, int num )
{
	int i;
	u16 ret;
	int poruto_type;
	BOOL return_val = TRUE;
	TV_WORK* p_tvw = SaveData_GetTvWork( mp->param->SaveData );
		
	for( i=0; i<num; i++ ){
		ret = PORUTO_AddData( mp->param->poruSave, p_poruto );
		if( ret == PORUTO_DATA_NULL ){
//			OS_Printf( "�|���g��t %d\n", i );
			return_val = FALSE;
			break;
		}
	}

	//�@�e���r���[�N�ɕۑ�
	poruto_type = PorutoData_GetParam( p_poruto, PORUTO_PARAID_FLAVOR );
	TVTOPIC_PorutoTemp_Set( p_tvw, poruto_type );
	
	return return_val;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`���v�`���v���@���o��
 *
 *	@param	wk	���[�N
 */
//-----------------------------------------------------------------------------
static void NMixGame_Tool_ChapuChapuSnd( NMIX_GAMEWORK* wk )
{
	NUTMIX_OYA* p_oya = &wk->game_comm_pack.get_game_data[ COMM_PARENT_ID ].oya;
	static const u32 SndTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		NMIXGAME_SE_SOOP_ROTA,
		NMIXGAME_SE_CREAM_ROTA,
		NMIXGAME_SE_SOBORO_ROTA,
	};

	if( ((p_oya->rota_way == 0) && (wk->last_rota > p_oya->rota)) ||
		((p_oya->rota_way == 1) && (wk->last_rota < p_oya->rota)) ){
		Snd_SePlay( SndTbl[ p_oya->mix_type ] );
	}
	
	wk->last_rota = p_oya->rota;
}

