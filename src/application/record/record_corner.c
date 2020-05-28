//============================================================================================
/**
 * @file	record_corner.c
 * @bfief	���R�[�h�R�[�i�[��ʏ���
 * @author	Akito Mori
 * @date	06.03.26
 */
//============================================================================================
#define DEBUGPLAY_ONE	( 0 )



#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_record.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "system/bmp_menu.h"
#include "application/record_corner.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/comm_save.h"
#include "communication/wm_icon.h"
#include "field/fld_bmp.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "field/union_beacon_tool.h"
#include "field/fieldobj_code.h"

#include "record_corner_local.h"

#include "comm_command_record.h"


#include "msgdata/msg_ev_win.h"

// SE�p��`
#define RECORD_MOVE_SE		(SEQ_SE_DP_SELECT)
#define RECORD_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define RECORD_BS_SE		(SEQ_SE_DP_SELECT)

#define FIELDOBJ_PAL_START	( 7 )

#define RECORD_1SEC_WAIT	( 45 )

#include "record.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../wifi_worldtrade/worldtrade.naix"
#include "../../field/poketch/poketch_arc.h"

#include "communication/wh.h"

//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_LEAVE,
	SEQ_OUT,
};

enum{
	LIMIT_MODE_NONE,	///<�����Ȃ�
	LIMIT_MODE_TRUE,	///<����������
	LIMIT_MODE_ONLY,	///<����������(��l�̂�)
};



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( RECORD_WORK *wk );
static void FreeWork( RECORD_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( RECORD_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(RECORD_WORK *wk);
static void SetCellActor(RECORD_WORK *wk);
static void BmpWinInit(RECORD_WORK *wk, PROC* proc);
static void BmpWinDelete( RECORD_WORK *wk );
static void CursorAppearUpDate(RECORD_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void EndSequenceCommonFunc( RECORD_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static BOOL NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, RECORD_WORK *wk );
static int  ConnectCheck( RECORD_WORK *wk );
static BOOL  MyStatusCheck( RECORD_WORK *wk );
static void RecordMessagePrint( RECORD_WORK *wk, int msgno, int all_put );
static int  EndMessageWait( int msg_index );
static void EndMessageWindowOff( RECORD_WORK *wk );
static int  OnlyParentCheck( void );
static int  MyStatusGetNum( void );
static void RecordDataSendRecv( RECORD_WORK *wk );
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait);
static void SequenceChange_MesWait( RECORD_WORK *wk, int next );
static void TrainerObjFunc( RECORD_WORK *wk );
static void LoadFieldObjData( RECORD_WORK *wk );
static void FreeFieldObjData( RECORD_WORK *wk );
static void TransFieldObjData( NNSG2dCharacterData *CharaData[2], NNSG2dPaletteData *PalData[2], int id, int view, int sex );
static void TransPal( TCB_PTR tcb, void *work );
static int GetTalkSpeed( RECORD_WORK *wk );
static void ChangeConnectMax( RECORD_WORK *wk, int plus );
static int  RecordCorner_BeaconControl( RECORD_WORK *wk, int plus );
static void PadControl( RECORD_WORK *wk );


// FuncTable����V�[�P���X�J�ڂŌĂ΂��֐�
static int Record_MainInit( RECORD_WORK *wk, int seq );
static int Record_MainNormal( RECORD_WORK *wk, int seq );
static int Record_StartRecordCommand( RECORD_WORK *wk, int seq );
static int Record_RecordSendData( RECORD_WORK *wk, int seq );
static int Record_RecordMixData( RECORD_WORK *wk, int seq );
static int Record_StartSelectWait( RECORD_WORK *wk, int seq );
static int Record_StartSelect( RECORD_WORK *wk, int seq );
static int Record_EndSelectPutString( RECORD_WORK *wk, int seq );
static int Record_EndSelectWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerOK( RECORD_WORK *wk, int seq );
static int Record_EndSelectAnswerNG( RECORD_WORK *wk, int seq );
static int Record_EndChild( RECORD_WORK *wk, int seq );
static int Record_EndChildWait( RECORD_WORK *wk, int seq );
static int Record_EndSelectParent( RECORD_WORK *wk, int seq );
static int Record_EndSelectParentWait( RECORD_WORK *wk, int seq );
static int Record_ForceEnd( RECORD_WORK *wk, int seq );
static int Record_ForceEndWait( RECORD_WORK *wk, int seq );
static int Record_ForceEndSynchronize( RECORD_WORK *wk, int seq );
static int Record_EndParentOnly( RECORD_WORK *wk, int seq );
static int Record_EndParentOnlyWait( RECORD_WORK *wk, int seq );
static int Record_MessageWaitSeq( RECORD_WORK *wk, int seq );
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq );
static int Record_LogoutChildClose( RECORD_WORK *wk, int seq );
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq );
static int Record_NewMember( RECORD_WORK *wk, int seq );
static int Record_NewMemberEnd( RECORD_WORK *wk, int seq );
static int Record_CommSaveStart( RECORD_WORK *wk, int seq );
static int Record_CommSave( RECORD_WORK *wk, int seq ) ;
static int Record_EndMessageWait( RECORD_WORK *wk, int seq );
static int Record_FroceEndMesWait( RECORD_WORK *wk, int seq );



// ���R�[�h�R�[�i�[���C���V�[�P���X�p�֐��z���`
static int (*FuncTable[])(RECORD_WORK *wk, int seq)={
	Record_MainInit,				// 	RECORD_MODE_INIT  = 0, 
	Record_NewMember, 		        // 	RECORD_MODE_NEWMEMBER,
	Record_NewMemberEnd,            // 	RECORD_MODE_NEWMEMBER_END,
	Record_MainNormal,              // 	RECORD_MODE,
	Record_EndSelectPutString,      // 	RECORD_MODE_END_SELECT,
	Record_EndSelectWait,			// 	RECORD_MODE_END_SELECT_WAIT,
	Record_EndSelectAnswerWait,		//	RECORD_MODE_END_SELECT_ANSWER_WAIT
	Record_EndSelectAnswerOK,		//	RECORD_MODE_END_SELECT_ANSWER_OK
	Record_EndSelectAnswerNG,		//	RECORD_MODE_END_SELECT_ANSWER_NG
	Record_EndChild,				//  RECORD_MODE_END_CHILD,
	Record_EndChildWait,			//  RECORD_MODE_END_CHILD_WAIT,
	Record_EndSelectParent,			// 	RECORD_MODE_END_SELECT_PARENT,
	Record_EndSelectParentWait,		//  RECORD_MODE_END_SELECT_PARENT_WAIT,
	Record_ForceEnd,				//	RECORD_MODE_FORCE_END,
	Record_FroceEndMesWait,			//  RECORD_MODE_FORCE_END_MES_WAIT,
	Record_ForceEndWait,			//  RECORD_MODE_FORCE_END_WAIT,
	Record_ForceEndSynchronize,		//  RECORD_MODE_FORCE_END_SYNCHRONIZE,
	Record_EndParentOnly,			// 	RECORD_MODE_END_PARENT_ONLY,
	Record_EndParentOnlyWait,		// 	RECORD_MODE_END_PARENT_ONLY_WAIT,
	Record_LogoutChildMes,			// 	RECORD_MODE_LOGOUT_CHILD,
	Record_LogoutChildMesWait,		//  RECORD_MODE_LOGOUT_CHILD_WAIT,
	Record_LogoutChildClose,		//  RECORD_MODE_LOGOUT_CHILD_CLOSE,
	Record_StartSelect,				// 	RECORD_MODE_START_SELECT,
	Record_StartSelectWait,         // 	RECORD_MODE_START_SELECT_WAIT
	Record_StartRecordCommand,		//  RECORD_MODE_START_RECORD_COMMAND
	Record_RecordSendData,			//	RECORD_MODE_RECORD_SEND_DATA ���������R�[�h�f�[�^��M�`�F�b�N

	// ������ւ�ɍ����鏈������������
	// �Z�[�u����V�[�P���X���������肵�悤

	Record_RecordMixData,			//	RECORD_MODE_RECORD_MIX_DATA	�܂���V�[�P���X
	
	Record_CommSaveStart,			//  RECORD_MODE_COMM_SAVE_START
	Record_CommSave,				//  RECORD_MODE_COMM_SAVE
	Record_EndMessageWait,			//  RECORD_MODE_END_MES_WAIT
	

	Record_MessageWaitSeq,			//  RECORD_MODE_MESSAGE_WAIT,
};



//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

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
PROC_RESULT RecordCornerProc_Init( PROC * proc, int * seq )
{
	RECORD_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		// ���R�[�h�R�[�i�[�p�q�[�v�쐬
		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_RECORD, 0x41000 );

		wk = PROC_AllocWork( proc, sizeof(RECORD_WORK), HEAPID_RECORD );
		memset( wk, 0, sizeof(RECORD_WORK) );
		wk->bgl   = GF_BGL_BglIniAlloc( HEAPID_RECORD );
		wk->param = (RECORD_INPUT_PARAM*)PROC_GetParentWork( proc );
		wk->savedata = wk->param->sv;
		
		// ������}�l�[�W���[����
		wk->WordSet    = WORDSET_Create( HEAPID_RECORD );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_record_dat, HEAPID_RECORD );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM �o���N�ݒ�
		VramBankSet();
		
		// BGL���W�X�^�ݒ�
		BgInit( wk->bgl );					

		WIPE_ResetBrightness( WIPE_DISP_MAIN );
		WIPE_ResetBrightness( WIPE_DISP_SUB );

		// ���C�v�t�F�[�h�J�n
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD );
		

		//BG�O���t�B�b�N�Z�b�g
		BgGraphicSet( wk );

//		InitTPSystem();						// �^�b�`�p�l���V�X�e��������
//		InitTPNoBuff(2);
  
		// VBlank�֐��Z�b�g
		sys_VBlankFuncChange( VBlankFunc, wk );	
  

		// ���[�N������
		InitWork( wk );

		// OBJ�L�����A�p���b�g�}�l�[�W���[������
		char_pltt_manager_init();

		// CellActor�V�X�e��������
		InitCellActor(wk);
		
		// CellActro�\���o�^
		SetCellActor(wk);

		// BMPWIN�o�^�E�`��
		BmpWinInit(wk,proc);

		// �T�E���h�f�[�^���[�h(���O����)(BGM���p��)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		// ��ʏo�͂��㉺����ւ���
//		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

		// �ʐM�R�}���h���������X�g�p�ɕύX
		CommCommandRecordInitialize( wk );

		// ���R�[�h�R�[�i�[���[�h�ɕύX
		CommStateUnionRecordCornerChange();

        // 3��܂Őڑ��\�ɏ�������
        CommStateSetLimitNum(3);

		// �e��������u���R�[�h�ʐM��W���v�Ƀr�[�R����������
		if(CommGetCurrentID()==0){
			Union_BeaconChange( UNION_PARENT_MODE_RECORD_FREE );
		}


		WirelessIconEasy();

		MakeSendData(wk->savedata, &wk->send_data);

		wk->trans_tcb = VIntrTCB_Add( TransPal, wk, 5 );


		(*seq)++;
		break;
	case 1:
		wk = PROC_GetWork( proc );
		(*seq) = SEQ_IN;
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}

static int debug_pal_no = 0;
static int debug_obj_no = 0;


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

PROC_RESULT RecordCornerProc_Main( PROC * proc, int * seq )
{
	RECORD_WORK * wk  = PROC_GetWork( proc );

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		wk->ridatu_bit &= WH_GetBitmap();
	}
	
	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ���C�v�����҂�
			*seq = SEQ_MAIN;

			// �������q�@�Őڑ��䐔���Q��ȏゾ�����ꍇ�͂����G���`����Ă���
			if(CommGetCurrentID()!=0){
				if(MyStatusGetNum()>2){
					// �q�@�������N�G�X�g
					CommSendData(CR_RECORD_CHILD_JOIN, NULL, 0);
				}
			}

		}
		break;

	case SEQ_MAIN:
		// �J�[�\���ړ�

		// �V�[�P���X���̓���
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}
		if(wk->record_execute == FALSE){	//���R�[�h�������̎��͍X�V���Ȃ�
			NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(1, 3, 0), wk );
		}
		TrainerObjFunc(wk);

		// �ω������l���ɉ����ăr�[�R����ς���
		if(CommGetCurrentID()==0){
			int temp = RecordCorner_BeaconControl( wk, 1 );
			if(*seq==SEQ_MAIN){
				// �I���V�[�P���X�Ȃǂɗ���Ă��Ȃ���ΕύX����
				*seq = temp;
			}
		}

		break;
	case SEQ_LEAVE:
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}
		break;
	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	CLACT_Draw( wk->clactSet );									// �Z���A�N�^�[�풓�֐�

	return PROC_RES_CONTINUE;
}

#define DEFAULT_NAME_MAX		18

// �_�C���E�p�[���ŕς��񂾂낤
#define MALE_NAME_START			0
#define FEMALE_NAME_START		18

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
PROC_RESULT RecordCornerProc_End( PROC * proc, int * seq )
{
	RECORD_WORK  *wk    = PROC_GetWork( proc );
	int i;

	// �p���b�g�]���^�X�N�I��
	TCB_Delete( wk->trans_tcb );

	// �Z���A�N�^�[���\�[�X���

	// �L�����]���}�l�[�W���[�j��
//	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
//	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
//	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES]);
		
	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(wk->clactSet);

	//OAM�����_���[�j��
	REND_OAM_Delete();

	// ���\�[�X���
	DeleteCharManager();
	DeletePlttManager();

	// BMP�E�B���h�E�J��
	BmpWinDelete( wk );

	// BGL�폜
	BgExit( wk->bgl );

	// �ʐM�I��
//	CommStateExitUnion();
    CommStateSetLimitNum(2);
	CommStateUnionBconCollectionRestart();
	UnionRoomView_ObjInit( wk->param->union_view );

	// �^�b�`�p�l���V�X�e���I��
//	StopTP();							


	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ���[�N���
	FreeWork( wk );


	PROC_FreeWork( proc );				// PROC���[�N�J��

	// ����ւ���Ă����㉺��ʏo�͂����ɖ߂�
	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	// �r�[�R����������
	Union_BeaconChange( UNION_PARENT_MODE_FREE );

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_RECORD );

	return PROC_RES_FINISH;
}

static const u8 palanimetable[][2]={
	{ 8,2,},
	{ 8,3,},
	{ 8,4,},
	{24,0,},
	{ 0,0xff,},
};



//------------------------------------------------------------------
/**
 * @brief   �p���b�g�]���^�X�N
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPal( TCB_PTR tcb, void *work )
{
	RECORD_WORK     *wk  = (RECORD_WORK *)work;
	VTRANS_PAL_WORK *pal = &wk->palwork;
	
	// �p���b�g�A�j��
	if(pal->sw){
		if(pal->wait>palanimetable[pal->seq][0]){
			u16 *src;
			pal->wait=0;
			pal->seq++;
			if(palanimetable[pal->seq][1]==0xff){
				pal->seq = 0;
			}
			src = (u16*)pal->palbuf->pRawData;
			GX_LoadOBJPltt(&src[16*palanimetable[pal->seq][1]], 0, 32);
//			OS_Printf("�p���b�g�]�� seq = %d \n",pal->seq);
		}else{
			wk->palwork.wait++;
		}
		
		CursorColTrans(&wk->CursorPal);
	}


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
	// �Z���A�N�^�[
	// Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
	
	GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
	
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

		GX_VRAM_OBJ_128_B,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ���C����ʕ�����0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );


	}

	// ���C�����1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_S );
	}

	// ���C����ʔw�i
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_S );
	}


	// �T�u��ʃe�L�X�g��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	// �T�u��ʔw�i��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_RECORD );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_RECORD );

}


#define TALK_MESSAGE_BUF_NUM	( 90*2 )
#define TITLE_MESSAGE_BUF_NUM	( 20*2 )

//------------------------------------------------------------------
/**
 * ���G�������[�N������
 *
 * @param   wk		RECORD_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( RECORD_WORK *wk )
{
	int i;

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_RECORD );
		wk->TrainerStatus[i][0] = NULL;
		wk->TrainerStatus[i][1] = NULL;
		wk->TrainerReq[i]       = RECORD_EXIST_NO;

	}
	// ������o�b�t�@�쐬
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_RECORD );
	wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_RECORD );

	wk->seq = RECORD_MODE_INIT;
	
	// ���R�[�h��������ڂ��イ���I������擾
	MSGMAN_GetString(  wk->MsgManager, msg_union_record_title_01, wk->TitleString );

	// �t�B�[���hOBJ�摜�ǂݍ���
	LoadFieldObjData( wk );

	wk->ObjPaletteTable = UnionView_PalleteTableAlloc( HEAPID_RECORD );


	// �p���b�g�A�j���p���[�N������
	wk->palwork.sw       = 0;
	wk->palwork.wait     = 0;
	wk->palwork.seq      = 0;
	wk->palwork.paldata  = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_record_s_obj_nclr, &wk->palwork.palbuf, HEAPID_RECORD );
	wk->connectBackup    = 0;
	wk->YesNoMenuWork    = NULL;
	wk->shareNum		 = 2;
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
static void FreeWork( RECORD_WORK *wk )
{
	int i;

	// �t�B�[���hOBJ�摜���
	FreeFieldObjData( wk );

	// �@�B�̃p���b�g�A�j���p�f�[�^���
	sys_FreeMemoryEz(wk->palwork.paldata);

	// ���j�I��OBJ�̃p���b�g�f�[�^���
	sys_FreeMemoryEz(wk->ObjPaletteTable);

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TitleString ); 
	STRBUF_Delete( wk->TalkString ); 

}

//--------------------------------------------------------------------------------------------
/**
 * BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemoryEz( ini );
}


//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		�|�P�������X�g��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( RECORD_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet( ARC_RECORD_GRA,  NARC_record_record_s_nclr, PALTYPE_MAIN_BG, 0, 16*16*2, HEAPID_RECORD );
	ArcUtil_PalSet( ARC_POKETCH_IMG, NARC_poketch_before_nclr,  PALTYPE_SUB_BG,  0, 16*2,   HEAPID_RECORD );
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_RECORD );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_RECORD );




	// ���C�����BG2�L�����]��
//	ArcUtil_BgCharSet( ARC_RECORD_GRA, NARC_record_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_S, 0, 32*8*0x20, 1, HEAPID_RECORD);

	// ���C�����BG2�X�N���[���]��
//	ArcUtil_ScrnSet(   ARC_RECORD_GRA, NARC_record_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 32*24*2, 1, HEAPID_RECORD);



	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr, bgl, GF_BGL_FRAME2_S, 0, 0, 1, HEAPID_RECORD);
	ArcUtil_ScrnSet(   ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr, bgl, GF_BGL_FRAME2_S, 0, 0, 1, HEAPID_RECORD);

	// �T�u���BG1�L�����]��
	ArcUtil_BgCharSet( ARC_RECORD_GRA, NARC_record_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_M, 0, 32*8*0x20, 1, HEAPID_RECORD);

	// �T�u���BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_RECORD_GRA, NARC_record_subbg_lz_nscr, bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_RECORD);

	// �T�u��ʉ�b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_RECORD );

	MenuWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1+TALK_WIN_CGX_SIZ, FLD_MENUFRAME_PAL, 0, HEAPID_RECORD );

}


//** CharManager PlttManager�p **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)

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
			RECORD_CHAR_CONT_NUM,
			RECORD_CHAR_VRAMTRANS_MAIN_SIZE,
			RECORD_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_RECORD
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(RECORD_PLTT_CONT_NUM, HEAPID_RECORD);

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
static void InitCellActor(RECORD_WORK *wk)
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
			HEAPID_RECORD);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( 30, &wk->renddata, HEAPID_RECORD );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(3, i, HEAPID_RECORD);
	}


	//---------���ʗp-------------------
#if 0
	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_RECORD_GRA, NARC_record_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_RECORD);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_RECORD_GRA, NARC_record_record_m_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_RECORD);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_RECORD_GRA, NARC_record_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_RECORD);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_RECORD_GRA, NARC_record_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_RECORD);
#endif

	//---------���ʐl��OBJ�ǂݍ���-------------------

	//chara�ǂݍ���
	wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_RECORD_GRA, NARC_record_obj_s_lz_ncgr, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_RECORD);

	//pal�ǂݍ���
	wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_RECORD_GRA, NARC_record_record_s_obj_nclr, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 15, HEAPID_RECORD);

	//cell�ǂݍ���
	wk->resObjTbl[CHARA_RES][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_RECORD_GRA, NARC_record_obj_s_lz_ncer, 1, 2, CLACT_U_CELL_RES,HEAPID_RECORD);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[CHARA_RES][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_RECORD_GRA, NARC_record_obj_s_lz_nanr, 1, 2, CLACT_U_CELLANM_RES,HEAPID_RECORD);


	//---------����ʗp-------------------



	//chara�ǂݍ���
//	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
//							ARC_RECORD_GRA, NARC_record_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_RECORD);

	//pal�ǂݍ���
//	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
//							ARC_RECORD_GRA, NARC_record_record_m_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_RECORD);

	//cell�ǂݍ���
//	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
//							ARC_RECORD_GRA, NARC_record_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_RECORD);

	//�����֐���anim�ǂݍ���
//	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
//							ARC_RECORD_GRA, NARC_record_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_RECORD);

	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
//	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
//	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
//	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
//	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[CHARA_RES][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

#define TRAINER_NAME_WIN_X		(  2 )
#define TRAINER1_NAME_WIN_Y		(  6 )
#define TRAINER2_NAME_WIN_Y		(  7 )

static const u16 obj_pos_tbl[][2]={
	{ 204,  84   },
	{ 204,  61-8 },
	{ 233,  80-8 },
	{ 223, 111-8 },
	{ 184, 111-8 },
	{ 174,  80-8 },
};

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			RECORD_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(RECORD_WORK *wk)
{
	int i;
#if 0
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);
#endif

	CLACT_U_MakeHeader(&wk->clActHeader_friend, 2, 2, 2, 2, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 1,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);


	{
		//�o�^���i�[
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_friend;

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_RECORD;

		//�Z���A�N�^�[�\���J�n

		// �^�񒆂̋@�B�����͕\��
		add.mat.x = FX32_ONE *   obj_pos_tbl[0][0];
		add.mat.y = FX32_ONE *   obj_pos_tbl[0][1];
		wk->MainActWork[0] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->MainActWork[0],1);
//		CLACT_AnmChg( wk->MainActWork[0], 0 );
		CLACT_SetDrawFlag( wk->MainActWork[0], 1 );

		// ���C����ʗp(�l���̓o�^�j
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   obj_pos_tbl[i+1][0];
			add.mat.y = FX32_ONE *   obj_pos_tbl[i+1][1];
			wk->MainActWork[i+1] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->MainActWork[i+1],1);
			CLACT_AnmChg( wk->MainActWork[i+1], 27+(i-1)*2 );
			CLACT_SetDrawFlag( wk->MainActWork[i+1], 0 );
		}


		//�Z���A�N�^�[�\���J�n
		// �T�u��ʗp(���̓o�^�j
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
//			wk->SubActWork[i] = CLACT_Add(&add);
//			CLACT_SetAnmFlag(wk->SubActWork[i],1);
//			CLACT_AnmChg( wk->SubActWork[i], i );
//			CLACT_DrawPriorityChg(wk->SubActWork[i], 1);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
//			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
			
		}
		
	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m
	
}

// ���������{�[�hBMP�i����ʁj
#define OEKAKI_BOARD_POSX	 ( 1 )
#define OEKAKI_BOARD_POSY	 ( 2 )
#define OEKAKI_BOARD_W	 ( 30 )
#define OEKAKI_BOARD_H	 ( 15 )


// ���O�\��BMP�i���ʁj
#define RECORD_NAME_BMP_W	 ( 16 )
#define RECORD_NAME_BMP_H	 ( 11 )
#define RECORD_NAME_BMP_SIZE (RECORD_NAME_BMP_W * RECORD_NAME_BMP_H)


// �u��߂�v������BMP�i����ʁj
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 20 )
#define OEKAKI_END_BMP_W	( 6  )
#define OEKAKI_END_BMP_H	( 2  )


// ��b�E�C���h�E�\���ʒu��`
#define RECORD_TALK_X		(  2 )
#define RECORD_TALK_Y		(  19 )

#define RECORD_TITLE_X		(   3  )
#define RECORD_TITLE_Y		(   1  )
#define RECORD_TITLE_W		(  26  )
#define RECORD_TITLE_H		(   2  )


#define RECORD_MSG_WIN_OFFSET 		(1 + TALK_WIN_CGX_SIZ     + MENU_WIN_CGX_SIZ)
#define RECORD_TITLE_WIN_OFFSET		( RECORD_MSG_WIN_OFFSET   + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define RECORD_NAME_WIN_OFFSET		( RECORD_TITLE_WIN_OFFSET + RECORD_TITLE_W*RECORD_TITLE_H )
#define RECORD_YESNO_WIN_OFFSET		( RECORD_NAME_WIN_OFFSET  + RECORD_NAME_BMP_SIZE )

//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit(RECORD_WORK *wk, PROC* proc)
{
	// ---------- ���C����� ------------------

	// BG1��BMP�i��߂�j�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_S,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 13,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );

	// ----------- �T�u��ʖ��O�\��BMP�m�� ------------------
	// BG0��BMP�i��b�E�C���h�E�j�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		RECORD_TALK_X, RECORD_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  RECORD_MSG_WIN_OFFSET );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG0��BMP�i�^�C�g���E�C���h�E�j�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME0_M,
		RECORD_TITLE_X, RECORD_TITLE_Y, RECORD_TITLE_W, RECORD_TITLE_H, 15,  RECORD_TITLE_WIN_OFFSET );
	CenteringPrint(&wk->TitleWin, wk->TitleString, MSG_ALLPUT);

	// ���O�\���E�C���h�E
	{
		int i;
			GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[0], GF_BGL_FRAME0_M,	
				TRAINER_NAME_WIN_X, TRAINER1_NAME_WIN_Y, RECORD_NAME_BMP_W, RECORD_NAME_BMP_H, 15,  RECORD_NAME_WIN_OFFSET);

			GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[0], 0 );

		//�ŏ��Ɍ����Ă���ʂȂ̂ŕ����p�l���`��Ɠ]�����s��
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(1, 3, 0), wk );


	}

	OS_Printf("YESNO win offset = %d\n",RECORD_YESNO_WIN_OFFSET);

/*
3713 2D4A 5694 089D 5EBF 7DC0 76EF 0000
0000 0000 0000 7FFF 62FF 6F7B 7F52 7FFF

*/



}	

//------------------------------------------------------------------
/**
 * $brief   �Z���^�����O���ăv�����g
 *
 * @param   win		GF_BGL_BMPWIN
 * @param   strbuf	
 *
 * @retval  none
 */
//------------------------------------------------------------------
static void CenteringPrint(GF_BGL_BMPWIN *win, STRBUF *strbuf, int wait)
{
	int length = FontProc_GetPrintStrWidth( FONT_TALK, strbuf, 0 );
	int x      = (RECORD_TITLE_W*8-length)/2;
	
	GF_BGL_BmpWinDataFill( win, 0x0000 );

	GF_STR_PrintColor(	win, FONT_TALK, strbuf, x, 1, wait,	GF_PRINTCOLOR_MAKE(1, 4, 0),NULL);

}


// �͂��E������BMP�i����ʁj
#define YESNO_WIN_FRAME_CHAR	( 1 + TALK_WIN_CGX_SIZ )
#define YESNO_CHARA_OFFSET		( 1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY )
#define YESNO_WINDOW_X			( 22 )
#define YESNO_WINDOW_Y1			(  7 )
#define YESNO_WINDOW_Y2			( 13 )
#define YESNO_CHARA_W			(  8 )
#define YESNO_CHARA_H			(  4 )


//------------------------------------------------------------------
/**
 * $brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( RECORD_WORK *wk )
{
	int i;
	
//	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[0] );
//	}
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->MsgWin );


}





//------------------------------------------------------------------
/**
 * �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
 * �����̏�ł���΁A�����`�̃J�[�\���A�{�^���̏�ł���Β����`�̃J�[�\��
 * �����̍X�V���s���邱�ƂŁA�T�u��ʂ̒��̃t�H���g�̍X�V���s����
 *
 * @param   wk			RECORD_WORK*
 * @param   arrow		�ړ�����
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(RECORD_WORK *wk, int arrow)
{
	VecFx32 tmpVex;

//	tmpVex.x = FX32_ONE*(MAIN_CURSOR_POSX+wk->Cursor.x*12);
//	tmpVex.y = FX32_ONE*(MAIN_CURSOR_POSY+(wk->Cursor.y-1)*16);
//	CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);


}




//------------------------------------------------------------------
/**
 * $brief   �J�[�\���ʒu��ύX����
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}





//------------------------------------------------------------------
/**
 * $brief   �J�n���̃��b�Z�[�W
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Record_MainInit( RECORD_WORK *wk, int seq )
{
	
    CommStateSetErrorCheck(FALSE,TRUE); // �q�@�̏o���肪�m�肷��܂ł̓G���[�������Ȃ�
	// �e�̎���A�{�^���ŊJ�n���b�Z�[�W�B�q�@�͊J�n�҂����b�Z�[�W
	if(CommGetCurrentID()==0){
		RecordMessagePrint(wk, msg_union_record_01_01, 0 );
	}else{
		RecordMessagePrint(wk, msg_union_record_01_07, 0 );
	}
	SequenceChange_MesWait(wk, RECORD_MODE);

//	wk->seq = RECORD_MODE;

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ���R�[�h�R�[�i�[�ʏ폈��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_MainNormal( RECORD_WORK *wk, int seq )
{
	// �S�̑���֎~�łȂ���΃L�[����
	PadControl( wk );

	//TrainerObjFunc(wk);

	
	if(CommGetCurrentID()==0){				// �e�@�̎�
		if(OnlyParentCheck()!=1){			// ��l����Ȃ����H
			RecordDataSendRecv( wk );
		}
	}else{
			RecordDataSendRecv( wk );
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * @brief   �L�[���͊Ǘ�
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static void PadControl( RECORD_WORK *wk )
{
	// ���R�[�h�������J�n���܂����H�i�e�̂݁j
	if(sys.trg&PAD_BUTTON_A){
		if(CommGetCurrentID()==0){
			if(MyStatusGetNum()==wk->shareNum && wk->ridatu_bit == 0){
				u8 flag = RECORD_BAN_ON;
				RecordMessagePrint( wk, msg_union_record_01_02, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_START_SELECT);

				// ���E�֎~�ʒB
				CommSendData( CR_RECORD_BAN, &flag, 1 );
				
				// �ڑ��l������ON
				ChangeConnectMax( wk, 0 );
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}

	}else if(sys.trg&PAD_BUTTON_B){
		// ��߂܂����H
		if(CommGetCurrentID()){
			// �q�@�͐e�@����֎~�����Ă���ꍇ�͏I���ł��Ȃ�
			if(wk->banFlag==0){
				RecordMessagePrint( wk, msg_union_record_01_03, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_END_SELECT);
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}else{
//			if( MyStatusGetNum()==wk->shareNum ){
			if( CommGetConnectNum()==wk->shareNum && wk->ridatu_bit == 0){
				u8 flag = RECORD_BAN_ON;
				// �e�@�͏I�����j���[��
				RecordMessagePrint( wk, msg_union_record_01_03, 0 );
				SequenceChange_MesWait(wk,RECORD_MODE_END_SELECT);
				// ���E�֎~�ʒB
				CommSendData( CR_RECORD_BAN, &flag, 1 );

				// �ڑ��l������ON
				ChangeConnectMax( wk, 0 );
			}
			else{
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
		}
	}
	else{
		if(wk->beacon_flag == RECORD_BAN_NONE){
			if(CommGetCurrentID() == 0 && CommGetConnectNum()==wk->shareNum){
				u8 flag = RECORD_BAN_NONE;
				// ���E�֎~�����ʒB
				CommSendData( CR_RECORD_BAN, &flag, 1 );
			}
		}
	}

}

//------------------------------------------------------------------
/**
 * $brief   �I���I�������̋��ʏ����֐�(���ŕ`�擙�j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndSequenceCommonFunc( RECORD_WORK *wk )
{
	
}


//------------------------------------------------------------------
/**
 * $brief   �V�����q�@�������̂Őe�@���摜�𑗐M���͂��߂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Record_NewMember( RECORD_WORK *wk, int seq )
{
	// ���������񂪂͂����Ă��܂���
//	RecordMessagePrint(wk, msg_oekaki_01);
//	wk->seq = RECORD_MODE_NEWMEMBER_WAIT;
	SequenceChange_MesWait(wk, RECORD_MODE_NEWMEMBER_END );

	// �摜�]����ԂɂȂ�����P�x�_�E��
//	G2_SetBlendBrightness(  GX_BLEND_PLANEMASK_BG1|
//							GX_BLEND_PLANEMASK_BG2|
//							GX_BLEND_PLANEMASK_BG3|
//							GX_BLEND_PLANEMASK_OBJ
//								,  -6);

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   ���b�Z�[�W�I����҂��Ď��̃V�[�P���X�ɍs���֐�
 *
 * @param   wk		
 * @param   next		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SequenceChange_MesWait( RECORD_WORK *wk, int next )
{
	wk->seq     = RECORD_MODE_MESSAGE_WAIT;
	wk->nextseq = next;
}

//------------------------------------------------------------------
/**
 * $brief   �V�����q�@�p�̉摜��M�҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int Record_MessageWaitSeq( RECORD_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = wk->nextseq;
	}
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   �q�@������M�I��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_NewMemberEnd( RECORD_WORK *wk, int seq )
{
	// �P�x�_�E������
//	G2_BlendNone();

	if(CommGetCurrentID()==0){
		int flag = RECORD_BAN_NONE;
		// ���E�֎~�����ʒB
		CommSendData( CR_RECORD_BAN, &flag, 1 );
	}

	wk->seq = RECORD_MODE;
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}


// �͂��E������
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( 13 )
#define	BMP_YESNO_CGX	( RECORD_YESNO_WIN_OFFSET )


// �͂��E������
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME0_M, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, BMP_YESNO_CGX
};

//------------------------------------------------------------------
/**
 * $brief   ���R�[�h�R�[�i�[�u��߂�v��I��������
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectPutString( RECORD_WORK *wk, int seq )
{
	// �͂��E�������\��
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_END_SELECT_WAIT;
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �u��߂܂����H�v�͂��E�������I��҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectWait( RECORD_WORK *wk, int seq )
{
	int result;
	u32 ret;
	
	// �q�@�͐e�@���瑀��֎~�����Ă���ꍇ�͑���ł��Ȃ�
	if(CommGetCurrentID()){
		if(wk->banFlag){
			if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
			EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
			return seq;
		}
	}
	else{	//�e�̏ꍇ
		if(wk->ridatu_bit != 0){			//���E���悤�Ƃ��Ă���q������Ȃ狖���Ȃ�
			if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
				Snd_SePlay(SEQ_SE_DP_CUSTOM06);
			}
			EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
			return seq;
		}
	}

//	if(wk->shareNum != MyStatusGetNum()){	//��v���Ă��Ȃ��Ȃ�u��߂�v�����Ȃ�
	if(MyStatusGetNum() != CommGetConnectNum()){
		//��v���Ă��Ȃ��Ȃ�u��߂�v�����Ȃ�(�q���ʂ邱���͐e�����X�V����Ȃ�shareNum�͌��Ȃ�)
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}

	// ���j���[����
	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			if(CommGetCurrentID()==0){
				int flag = RECORD_BAN_NONE;
				// ���E�֎~�����ʒB
				CommSendData( CR_RECORD_BAN, &flag, 1 );

				// �ڑ��l������OFF
				ChangeConnectMax( wk, 1 );
			}
			
			SequenceChange_MesWait( wk, RECORD_MODE_INIT );
		}else{
			if(CommGetCurrentID()==0){		
				SequenceChange_MesWait( wk, RECORD_MODE_END_SELECT_PARENT );
				RecordMessagePrint( wk, msg_union_record_01_13, 0 );		// ���[�_�[����߂�Ɓc
			}else{
				COMM_RECORD_END_CHILD_WORK crec;
				
				MI_CpuClear8(&crec, sizeof(COMM_RECORD_END_CHILD_WORK));
				crec.request = CREC_REQ_RIDATU_CHECK;
				crec.ridatu_id = CommGetCurrentID();
				
				wk->status_end = TRUE;
				wk->ridatu_wait = 0;
				//wk->seq = RECORD_MODE_END_CHILD;
				wk->seq = RECORD_MODE_END_SELECT_ANSWER_WAIT;
				CommSendData( CR_RECORD_END_CHILD, &crec, sizeof(COMM_RECORD_END_CHILD_WORK) );
			}
		}
		wk->YesNoMenuWork = NULL;
	}


	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �u��߂܂����H�v���u�͂��v�A�Őe���痣�E���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectAnswerWait( RECORD_WORK *wk, int seq )
{
	wk->ridatu_wait = 0;
	
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   �u��߂܂����H�v���u�͂��v�A�Őe���痣�E���҂���OK!
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectAnswerOK( RECORD_WORK *wk, int seq )
{
	if((wk->oya_share_num != CommGetConnectNum())
			|| (wk->oya_share_num != MyStatusGetNum())){
		OS_TPrintf("share_nuM = %d, Comm = %d, My = %d, Bit = %d\n", wk->oya_share_num, CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		wk->ridatu_wait = 0;
		wk->seq = RECORD_MODE_END_SELECT_ANSWER_NG;
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}
	
	wk->ridatu_wait++;
	OS_TPrintf("ridatu_wait = %d\n", wk->ridatu_wait);
	if(wk->ridatu_wait > 30){
		COMM_RECORD_END_CHILD_WORK crec;
		
		MI_CpuClear8(&crec, sizeof(COMM_RECORD_END_CHILD_WORK));
		crec.request = CREC_REQ_RIDATU_EXE;
		crec.ridatu_id = CommGetCurrentID();

		CommSendData( CR_RECORD_END_CHILD, &crec, sizeof(COMM_RECORD_END_CHILD_WORK) );

		wk->ridatu_wait = 0;
		wk->seq = RECORD_MODE_END_CHILD;
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   �u��߂܂����H�v���u�͂��v�A�Őe���痣�E���҂���NG!
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectAnswerNG( RECORD_WORK *wk, int seq )
{
	wk->status_end = FALSE;
	SequenceChange_MesWait( wk, RECORD_MODE_INIT );
	
	OS_TPrintf("==========���E�����L�����Z���I===========\n");

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}


//------------------------------------------------------------------
/**
 * $brief   ���̃����o�[�Ń��R�[�h���J�n���܂����H
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartSelect( RECORD_WORK *wk, int seq )
{
	// �͂��E�������\��
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_START_SELECT_WAIT;
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �u�J�n���܂����H�v�͂��E�������I��҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartSelectWait( RECORD_WORK *wk, int seq )
{
	int result;
	u32 ret;

	if(MyStatusGetNum() != wk->shareNum 		//��v���Ă��Ȃ��Ȃ狖���Ȃ�
			|| wk->ridatu_bit != 0){			//���E���悤�Ƃ��Ă���q������Ȃ狖���Ȃ�
		if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
			Snd_SePlay(SEQ_SE_DP_CUSTOM06);
		}
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}
		
	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			int flag = RECORD_BAN_NONE;
			// ���E�֎~�����ʒB
			CommSendData( CR_RECORD_BAN, &flag, 1 );

			// �r�[�R����ԕύX
			
			ChangeConnectMax( wk, 1 );
			SequenceChange_MesWait( wk, RECORD_MODE_INIT );


		}else{
			// ��΂����ɂ���̂͐e������
			if(CommGetCurrentID()==0){		
//				SequenceChange_MesWait( wk, RECORD_MODE_STAET_RECORD_COMMAND );
//				RecordMessagePrint( wk, msg_union_record_01_11, 1 );		// �܂��Ă��܂�
                // �ڑ��֎~�ɏ�������
				wk->seq = RECORD_MODE_START_RECORD_COMMAND;
				wk->start_num = MyStatusGetNum();
			}else{
				GF_ASSERT(0);
			}
		}
		wk->YesNoMenuWork = NULL;
	}


	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}


//------------------------------------------------------------------
/**
 * $brief   �e�@��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_StartRecordCommand( RECORD_WORK *wk, int seq )
{
	if(wk->record_send == 0){
		if(CommSendData( CR_RECORD_START, NULL, 0 ) == TRUE){
			wk->record_send = TRUE;
		}
	}
	
//	SequenceChange_MesWait( wk, RECORD_MODE_RECORD_SEND_DATA );
//	RecordMessagePrint( wk, msg_union_record_01_11, 1 );		// �܂��Ă��܂�

	return seq;

}

//==============================================================================
/**
 * $brief   �^�C�g�����b�Z�[�W��ς���u�������񂿂イ�I�v
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void RecordCornerTitleChange( RECORD_WORK *wk )
{
	// ���R�[�h��������ڂ��イ���I������擾
	MSGMAN_GetString(  wk->MsgManager, msg_union_record_title_02, wk->TitleString );

	CenteringPrint(&wk->TitleWin, wk->TitleString, MSG_ALLPUT);
	
	// �@�B���A�j��������
	CLACT_AnmChg( wk->MainActWork[0], 37 );

	// VBLANK�p���b�g�A�j���J�n
	wk->palwork.sw = 1;
}

//------------------------------------------------------------------
/**
 * $brief   �f�[�^���M�E��M�҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_RecordSendData( RECORD_WORK *wk, int seq )
{
	int i,result;

	result = 0;
//	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
//		result += CommIsSpritDataRecv(i);
//	}

	if( CommGetCurrentID() == 0 && CommGetConnectNum() != wk->start_num){
		//�J�n�������̐l���ƌ��݂̐l�����ς���Ă���Ȃ�ʐM�G���[�ɂ���
//		OS_TPrintf("�l�����ς���Ă���̂ŋ����I�ɒʐM�G���[�ɂ��܂��@�J�n����%d, ���݁�%d\n", wk->start_num, CommGetConnectNum());
//		CommStateSetError();
	}
	
	// ��M���I�������l���Ɛڑ��l���������ɂȂ�����I��
	if( CommGetConnectNum()==wk->recv_count ){

		// �f�[�^�����鏈����
		wk->seq = RECORD_MODE_RECORD_MIX_DATA;

		for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
			OS_TPrintf("��M�f�[�^ id=%d, seed=%d, xor=%08x\n",i,wk->recv_data[i].seed, wk->recv_data[i]._xor);
		}
	}

	return seq;
}
//------------------------------------------------------------------
/**
 * @brief	�܂��鏈��
 *
 * @param	wk
 * @param	seq
 *
 * @return	int
 */
//------------------------------------------------------------------
static int Record_RecordMixData( RECORD_WORK *wk, int seq )
{
	// �f�[�^�������鏈��
	MixReceiveData(wk->savedata, wk->recv_data);

	wk->seq = RECORD_MODE_COMM_SAVE_START;

	return seq;
}




//------------------------------------------------------------------
/**
 * @brief   ���R�[�h�����I���Z�[�u
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_CommSaveStart( RECORD_WORK *wk, int seq )
{
	void *FnoteWork;

	// �\�t�g���Z�b�g�s�\�ɂ���
	sys.DontSoftReset = 1;

	// �`���m�[�g����
	FnoteWork = FNOTE_SioRecordDataMake( HEAPID_RECORD );
	FNOTE_DataSave( wk->param->fnote, FnoteWork, FNOTE_TYPE_SIO );

	// �X�R�A�����Z
	RECORD_Score_Add( wk->param->record, SCORE_ID_COMM_RECORD_CORNER );

	// �ʐM�����Z�[�u����������
	CommSyncronizeSaveInit( &wk->saveseq_work );
	wk->seq = RECORD_MODE_COMM_SAVE;
	OS_Printf("�����Z�[�u�J�n\n");
	return seq;
}


//==============================================================================
/**
 * @brief   ���R�[�h�����ʐM�����Z�[�u�I���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  stati int		
 */
//==============================================================================
static int Record_CommSave( RECORD_WORK *wk, int seq ) 
{
	if( CommGetCurrentID() == 0 && CommGetConnectNum() != wk->start_num){
		//�J�n�������̐l���ƌ��݂̐l�����ς���Ă���Ȃ�ʐM�G���[�ɂ���
//		OS_TPrintf("�l�����ς���Ă���̂ŋ����I�ɒʐM�G���[�ɂ��܂��@�J�n����%d, ���݁�%d\n", wk->start_num, CommGetConnectNum());
//		CommStateSetError();
	}

	// �ʐM�����Z�[�u�I���҂�
	if(CommSyncronizeSave(wk->param->sv, SVBLK_ID_MAX, &wk->saveseq_work)){

		// SE�I��
		Snd_SeStopBySeqNo( SEQ_SE_DP_F209, 8 );


		// �u���R�[�h�������I�����܂����I�v
		RecordMessagePrint( wk, msg_union_record_01_12, 0 );
		SequenceChange_MesWait( wk, RECORD_MODE_END_MES_WAIT );

		// �@�B�̃A�j�����ɖ߂�
		CLACT_AnmChg( wk->MainActWork[0], 0 );

		// VBLANK�p���b�g�A�j���I��
		wk->palwork.sw = 0;

		wk->wait = 0;
		OS_Printf("�����Z�[�u�I��\n");

		// �\�t�g���Z�b�g�\�ɂ���
		sys.DontSoftReset = 0;

		wk->record_execute = FALSE;
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * @brief   ����I��(���b�Z�[�W�\������P�b�܂��ďI���j
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndMessageWait( RECORD_WORK *wk, int seq )
{
	if(wk->wait++ > 60){
		// �I���p�ʐM����
//		CommTimingSyncStart(RECORD_SYNCHRONIZE_END);
		wk->seq = RECORD_MODE_FORCE_END_WAIT;
	}
	return seq;
}


// RECORD_MODE_END_CHILD
//------------------------------------------------------------------
/**
 * $brief   �q�@�I�����b�Z�[�W�J�n
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Record_EndChild( RECORD_WORK *wk, int seq )
{
	u8 temp;
	
	// ���R�[�h�R�[�i�[���ʂ��܂���
	RecordMessagePrint( wk, msg_union_record_01_04, 0 );	

	// �I���ʒB
	temp = 0;
//	CommSendData( CR_RECORD_END_CHILD, &temp, 1 );

	SequenceChange_MesWait( wk, RECORD_MODE_END_CHILD_WAIT );

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}
				

// RECORD_MODE_END_CHILD_WAIT
//------------------------------------------------------------------
/**
 * $brief   �q�@�I�����b�Z�[�W�\���I���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Record_EndChildWait( RECORD_WORK *wk, int seq )
{			
	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT ){
		// ���C�v�t�F�[�h�J�n
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD );
		seq = SEQ_OUT;						//�I���V�[�P���X��
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}


//------------------------------------------------------------------
/**
 * $brief   �e�@���I������Ƃ��͂�����x�u���[�_�[����߂�Ɓc�v�Ǝ��₷��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectParent( RECORD_WORK *wk, int seq )
{

	// �͂��E�������\��
	wk->YesNoMenuWork = BmpYesNoSelectInit(	wk->bgl, &YesNoBmpWin, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL, HEAPID_RECORD );

	wk->seq = RECORD_MODE_END_SELECT_PARENT_WAIT;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   �e�@�̂Q��ڂ́u�͂��E�������v
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndSelectParentWait( RECORD_WORK *wk, int seq )
{
	int ret;

	if(wk->shareNum != MyStatusGetNum()			//��v���Ă��Ȃ��Ȃ�u��߂�v�����Ȃ�
			|| wk->ridatu_bit != 0){			//���E���悤�Ƃ��Ă���q������Ȃ狖���Ȃ�
		if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL | PAD_KEY_UP | PAD_KEY_DOWN)){
			Snd_SePlay(SEQ_SE_DP_CUSTOM06);
		}
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}

	ret = BmpYesNoSelectMain( wk->YesNoMenuWork, HEAPID_RECORD );

	if(ret!=BMPMENU_NULL){
		if(ret==BMPMENU_CANCEL){
			int flag = RECORD_BAN_NONE;
			
			wk->seq = RECORD_MODE_INIT;

			// ���E�֎~�����ʒB
			CommSendData( CR_RECORD_BAN, &flag, 1 );

			// �ڑ��l������OFF
			ChangeConnectMax( wk, 1 );

		}else{
			wk->seq = RECORD_MODE_FORCE_END;
			CommSendData( CR_RECORD_END, NULL, 0 );						//�I���ʒm
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// �e�@�i�����j�̖��O��WORDSET
		}
		wk->YesNoMenuWork = NULL;
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   �e�@���I���ƌ������̂ŏI���
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_ForceEnd( RECORD_WORK *wk, int seq )
{
	if(CommGetCurrentID()==0){
		// ����ł́@���R�[�h�ʐM�����イ���@���܂�
		RecordMessagePrint( wk, msg_union_record_01_04, 0 );
	}else{
		// ��������邭�Ȃ��������o�[������̂ł������񂵂܂�
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// �e�@�i�����j�̖��O��WORDSET
		RecordMessagePrint( wk, msg_union_record_01_15, 0 );
	}
	SequenceChange_MesWait(wk,RECORD_MODE_FORCE_END_MES_WAIT);
	wk->wait = 0;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}


//------------------------------------------------------------------
/**
 * @brief   �����I�����b�Z�[�W�P�b�҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_FroceEndMesWait( RECORD_WORK *wk, int seq )
{
	wk->wait++;
	if(wk->wait > RECORD_1SEC_WAIT){
		wk->seq = RECORD_MODE_FORCE_END_WAIT;
	}
	
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �e�@���I���ƌ������̂ŏI���
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_ForceEndWait( RECORD_WORK *wk, int seq )
{
	// �ʐM�����҂�
	CommTimingSyncStart(RECORD_SYNCHRONIZE_END);
	wk->seq = RECORD_MODE_FORCE_END_SYNCHRONIZE;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �S���̒ʐM������҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_ForceEndSynchronize( RECORD_WORK *wk, int seq )
{
	if(CommIsTimingSync(RECORD_SYNCHRONIZE_END)){
	    CommStateSetErrorCheck(FALSE, FALSE); // �I�������ɓ������̂Őؒf�͂�������

		OS_Printf("�I������������\n");
		// ���C�v�t�F�[�h�J�n
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_RECORD);

		seq = SEQ_OUT;						//�I���V�[�P���X��
	}
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}


//------------------------------------------------------------------
/**
 * $brief   �e��l�ɂȂ����̂ŏI��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndParentOnly( RECORD_WORK *wk, int seq )
{
	RecordMessagePrint( wk, msg_union_record_01_08, 0 );	// ���[�_�[���������̂ŉ��U���܂��B
	wk->seq = RECORD_MODE_END_PARENT_ONLY_WAIT;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   ��l�ɂȂ������͂�\�����ďI���V�[�P���X��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_EndParentOnlyWait( RECORD_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = RECORD_MODE_END_CHILD_WAIT;
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}


//------------------------------------------------------------------
/**
 * $brief   ���������񂪂�����܂���
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq )
{
	// ���������񂪂�����܂���
	if( wk->MsgIndex != 0xff && EndMessageWait( wk->MsgIndex ) == 0){
		//�\�����̃��b�Z�[�W������ꍇ�͋�����~
		GF_STR_PrintForceStop(wk->MsgIndex);
	}
	RecordMessagePrint(wk, msg_union_record_01_14, 1 );
	wk->seq = RECORD_MODE_LOGOUT_CHILD_WAIT;

	// �ڑ��\�l������U���݂̐ڑ��l���ɗ��Ƃ�
	if(CommGetCurrentID()==0){
		ChangeConnectMax( wk, 0 );
	}


	OS_TPrintf("�l���`�F�b�N��logout child %d\n", CommGetConnectNum());
	wk->err_num = CommGetConnectNum();
	
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �q�@�����������͏I���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq )
{
	// �ڑ��l�����P���邩�`�F�b�N
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	wk->seq  = RECORD_MODE_LOGOUT_CHILD_CLOSE;
	wk->wait = 0;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �\���I���E�F�C�g
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Record_LogoutChildClose( RECORD_WORK *wk, int seq )
{			

	// �ڑ��l�����P����܂ł͑҂�
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}
	
	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT && wk->err_num == 0){
		wk->seq = RECORD_MODE_INIT;//RECORD_MODE;				//�I���V�[�P���X��

		// ���E�҂����Ȃ��Ȃ����̂ŁA�{�P��Ԃň�l�͓����悤�ɂ���
		if(CommGetCurrentID()==0){
			ChangeConnectMax( wk, 1 );
		}
	}

	EndSequenceCommonFunc( wk );			//�I���I�����̋��ʏ���
	return seq;
	
}

#if 0
//------------------------------------------------------------------
/**
 * $brief   ���������񂪂�����܂���
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_LogoutChildMes( RECORD_WORK *wk, int seq )
{
	// ���������񂪂�����܂���
	wk->seq = RECORD_MODE_LOGOUT_CHILD_WAIT;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   �q�@�����������͏I���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Record_LogoutChildMesWait( RECORD_WORK *wk, int seq )
{
		wk->seq  = RECORD_MODE_LOGOUT_CHILD_CLOSE;
		wk->wait = 0;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   �\���I���E�F�C�g
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Record_LogoutChildClose( RECORD_WORK *wk, int seq )
{			

	if( ++wk->wait > RECORD_CORNER_MESSAGE_END_WAIT ){
		wk->seq = RECORD_MODE;				//�I���V�[�P���X��
	}

	EndSequenceCommonFunc( wk );			//�I���I�����̋��ʏ���
	return seq;
	
}

#endif


//==============================================================================
/**
 * $brief   �ǂ�ȏ�Ԃł����Ă������I�Ƀ��C���V�[�P���X�`�F���W
 *
 * @param   wk		
 * @param   seq		
 * @param   id		
 *
 * @retval  none		
 */
//==============================================================================
void RecordCorner_MainSeqForceChange( RECORD_WORK *wk, int seq, u8 id  )
{
	switch(seq){
	case RECORD_MODE_NEWMEMBER_END:
		EndMessageWindowOff( wk );
		break;
	case RECORD_MODE_FORCE_END:
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		break;
	case RECORD_MODE_RECORD_SEND_DATA:
		if(EndMessageWait(wk->MsgIndex) == 0){
			//�\�����̃��b�Z�[�W������ꍇ�͋�����~
			GF_STR_PrintForceStop(wk->MsgIndex);
		}
		RecordMessagePrint( wk, msg_union_record_01_11, 0 );		// �u�܂��Ă��܂��v�\��
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		break;
	case RECORD_MODE_LOGOUT_CHILD:
		if(wk->status_end == TRUE){
			return;	//�������g�����E������
		}
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		if(id==CommGetCurrentID()){
			// ���������E����q�@�������ꍇ�́u�q�@�����Ȃ��Ȃ���v�Ƃ͌���Ȃ�
			return;
		}
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		if(CommGetCurrentID() == 0){
			wk->ridatu_bit &= 0xffff ^ id;
		}
		break;
	case RECORD_MODE_END_SELECT_ANSWER_OK:
		break;
	case RECORD_MODE_END_SELECT_ANSWER_NG:
		break;
	default:
		GF_ASSERT( "�w��ȊO�̃V�[�P���X�`�F���W������" );
		return;
	}
	wk->seq = seq;

}

//==============================================================================
/**
 * $brief   �������������Ă��烁�C�����[�v���V�[�P���X�`�F���W(�ʏ��Ԃł��邱�Ɓj
 *
 * @param   wk		
 * @param   seq		���̃��C���V�[�P���X�Ƀ`�F���W������
 *
 * @retval  none		
 */
//==============================================================================
void RecordCorner_MainSeqCheckChange( RECORD_WORK *wk, int seq, u8 id  )
{
	// �ʏ��ԂȂ�
	if(wk->seq == RECORD_MODE){
		OS_Printf("�q�@%d�̖��O��o�^\n",id);
		switch(seq){
		case RECORD_MODE_NEWMEMBER:	
			// �w��̎q�@�̖��O��WORDSET�ɓo�^�i���E�E������)
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			ChangeConnectMax( wk, 1 );
			wk->seq      = seq;
			wk->shareNum = CommGetConnectNum();
			wk->ridatu_bit = 0;
			if(CommGetCurrentID()==0){
				int flag = RECORD_BAN_ON;//NONE;
				// ���E�֎~�����ʒB
				CommSendData( CR_RECORD_BAN, &flag, 1 );
				
			}
			break;
			// ������ 
		case RECORD_MODE_LOGOUT_CHILD:
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			if(id==CommGetCurrentID()){
				// ���������E����q�@�������ꍇ�́u�q�@�����Ȃ��Ȃ���v�Ƃ͌���Ȃ�
				return;
			}
			if(CommGetCurrentID() == 0){
				wk->ridatu_bit &= 0xffff ^ id;
			}
			wk->seq = seq;
			break;
		default:
			GF_ASSERT( 0&&"�w��ȊO�̃V�[�P���X�`�F���W������" );
			return;
		}


	}
	else if(seq == RECORD_MODE_NEWMEMBER){
		wk->ridatu_bit = 0;
		wk->shareNum = CommGetConnectNum();
	}

}



//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------













//------------------------------------------------------------------
/**
 * �@�B�̃p���b�g�ύX�i�_�Łj
 *
 * @param   CursorCol	sin�ɓn���p�����[�^�i360�܂Łj
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorColTrans(u16 *CursorCol)
{
	fx32  sin;
	GXRgb tmp;
	int   r,g,b;

	*CursorCol+=10;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, ( 5    )*2, 2);
	GX_LoadOBJPltt((u16*)&tmp, ( 5+16 )*2, 2);
}

//------------------------------------------------------------------
/**
 * $brief   ���݉��l�ڑ����Ă��邩�H
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int OnlyParentCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return result;
}

#define NAME_PRINT_HABA	( 18 )
#define ID_STRING_NUM	(2+1+5+1)
//------------------------------------------------------------------
/**
 * $brief   �I�����C���󋵂��m�F���ď��ʂɖ��O��ID��\������
 *
 * @param   win		
 * @param   frame		
 * @param   color		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static BOOL NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, RECORD_WORK *wk )
{
	int i,id = CommGetCurrentID();
	STRBUF *id_str = NULL;


	// ���O�擾�̏󋵂ɕω��������ꍇ�͏��������Ȃ�
	if(!MyStatusCheck(wk)){
		return FALSE;
	}


	// ���ꂼ��̕����p�l���̔w�i�F�ŃN���A
	GF_BGL_BmpWinDataFill(&win[0],0x0000);

	// �`��
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][0]!=NULL){
			// �g���[�i�[ID�̎擾
			u16 tid = MyStatus_GetID_Low( wk->TrainerStatus[i][0] );

			// �����̖��O�擾
			MyStatus_CopyNameString( wk->TrainerStatus[i][0], wk->TrainerName[i] );

			// �g���[�i�[ID�𖄂ߍ��񂾕�����uID 12345�v���擾
			WORDSET_RegisterNumber( wk->WordSet, 0, tid, 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_HANKAKU );
			id_str = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, msg_union_record_name_02, HEAPID_RECORD );
			
			if(id==i){	// �����̖��O�̎��͐ԐF�Ŗ��O��ID��`��
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, wk->TrainerName[i], 5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(2,3,0),NULL);
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, id_str, 5+13*5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(2,3,0),NULL);
			}else{
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, wk->TrainerName[i], 5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, color,NULL);
				GF_STR_PrintColor(	&win[0], FONT_SYSTEM, id_str, 5+13*5, 1+i*NAME_PRINT_HABA, MSG_NO_PUT, color,NULL);
			}
			// ID����������
			STRBUF_Delete(id_str);
		}
	}
	GF_BGL_BmpWinOn( &win[0] );

	return TRUE;
}




#define PLATE_CHARA_OFFSET1	( 12 )
#define PLATE_CHARA_OFFSET2	( 16 )

static const u8 plate_num[4]={2,2,3,2};
static const u8 plate_table[4][3]={
	{8*8,17*8,0,},
	{8*8,17*8,0,},
	{5*8,12*8,18*8,},
	{8*8,17*8,0,},

};
static const u8 plate_chara_no[][5]={
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
};

//------------------------------------------------------------------
/**
 * $brief   �ڑ����m�F���ꂽ�ꍇ�͖��O���擾����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int ConnectCheck( RECORD_WORK *wk )
{
	int i,result=0;
	MYSTATUS *status;
	STRCODE  *namecode;

	// �ڑ��`�F�b�N
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->ConnectCheck[i][0] = wk->ConnectCheck[i][1];

		wk->ConnectCheck[i][0] = CommIsConnect(i);

	}

	// �ڑ��������疼�O�𔽉f������
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->ConnectCheck[i][0]){				// �ڑ����Ă��邩�H
			// �ڑ����Ă���

			status = CommInfoGetMyStatus(i);
			if(status!=NULL){					// MYSTATUS�͎擾�ł��Ă��邩�H
				namecode = (STRCODE*)MyStatus_GetMyName(status);
				STRBUF_SetStringCode( wk->TrainerName[i], namecode );
			}

		}
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   �^�b�`�p�l�����̑���M���s��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RecordDataSendRecv( RECORD_WORK *wk )
{
	
}


//------------------------------------------------------------------
/**
 * $brief   ���݂̃I�����C�������擾
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyStatusGetNum( void )
{
	int i,result;
	for(result=0,i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(CommInfoGetMyStatus(i)!=NULL){
			result++;
		}
	}
	return result;
}

//--------------------------------------------------------------
/**
 * @brief   ���݂̃I�����C�������擾(�O���[�o���֐���)
 *
 * @param   none		
 *
 * @retval  �ڑ��l��
 */
//--------------------------------------------------------------
int RecordCorner_MyStatusGetNum(void)
{
	return MyStatusGetNum();
}


//	RECORD_EXIST_NO=0,
//	RECORD_EXIST_APPEAR_REQ,
//	RECORD_EXIST_APPEAR,
//	RECORD_EXIST_BYE_REQ,


//------------------------------------------------------------------
/**
 * $brief   MYSTATUS�̎擾�󋵂ɕω������������H
 *
 * @param   wk		
 *
 * @retval  int		��������1,  �����ꍇ��0
 */
//------------------------------------------------------------------
static BOOL MyStatusCheck( RECORD_WORK *wk )
{
	int i,result=FALSE;
	// �ڑ��������疼�O�𔽉f������
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		wk->TrainerStatus[i][1] = wk->TrainerStatus[i][0];
		wk->TrainerStatus[i][0] = CommInfoGetMyStatus(i);
	}

	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][1] != wk->TrainerStatus[i][0]){

			// �ω�����
			result = TRUE;

			// �o��E����Ȃ烊�N�G�X�g�̔��s
			if(wk->TrainerStatus[i][0]==NULL){
				wk->TrainerReq[i] = RECORD_EXIST_BYE_REQ;
			}else{
				wk->TrainerReq[i] = RECORD_EXIST_APPEAR_REQ;
			}
		}
		
	}

	return result;
}


//------------------------------------------------------------------
/**
 * $brief   ��b�E�C���h�E�\��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void RecordMessagePrint( RECORD_WORK *wk, int msgno, int all_put )
{
	// ������擾
	STRBUF *tempbuf;
	
	tempbuf = STRBUF_Create(TALK_MESSAGE_BUF_NUM,HEAPID_RECORD);
	MSGMAN_GetString(  wk->MsgManager, msgno, tempbuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	STRBUF_Delete(tempbuf);

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, 1, FLD_MESFRAME_PAL );

	// ������`��J�n
	if(all_put == 0){
		wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, GetTalkSpeed(wk), NULL);
	}
	else{
		//�ꊇ�\���̏ꍇ��MsgIndex��0xff�ɂȂ�̂Œ��ӁI
		GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, MSG_ALLPUT, NULL);
		wk->MsgIndex = 0xff;
	}

}

//------------------------------------------------------------------
/**
 * $brief   ��b�\���E�C���h�E�I���҂�
 *
 * @param   msg_index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int EndMessageWait( int msg_index )
{
	if(msg_index == 0xff){
		return 1;
	}
	
	if(GF_MSG_PrintEndCheck( msg_index )==0){
		
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessageWindowOff( RECORD_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}


//------------------------------------------------------------------
/**
 * @brief   �g���[�i�[OBJ�̕\������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TrainerObjFunc( RECORD_WORK *wk )
{
	int i,seflag=0;
	
	for(i=0;i<RECORD_CORNER_MEMBER_MAX;i++){
		switch(wk->TrainerReq[i]){
		case RECORD_EXIST_NO:
			break;
		case RECORD_EXIST_APPEAR_REQ:
			{
				int view,sex;
				GF_ASSERT(wk->TrainerStatus[i][0]!=NULL);
				
				sex = MyStatus_GetMySex( wk->TrainerStatus[i][0] );
				view  = MyStatus_GetTrainerView( wk->TrainerStatus[i][0] );
				if(CommGetCurrentID()==i){
					// ��l��OBJ�p�̃A�j��
					CLACT_AnmChg( wk->MainActWork[i+1], 38+sex*2 );
				}else{
					// �t�B�[���hOBJ�p�̃A�j��
					TransFieldObjData( wk->FieldObjCharaData, wk->FieldObjPalData,  i, view, sex );
					CLACT_AnmChg( wk->MainActWork[i+1], 27+i*2 );
				}

			}
			CLACT_SetDrawFlag(wk->MainActWork[i+1], 1);
			wk->TrainerReq[i] = RECORD_EXIST_APPEAR;
			seflag = 1;
			break;
		case RECORD_EXIST_APPEAR:
			break;
		case RECORD_EXIST_BYE_REQ:
//			CLACT_SetDrawFlag(wk->MainActWork[i+1], 0);
			if(CommGetCurrentID()==i){
				int sex = MyStatus_GetMySex( wk->TrainerStatus[i][0] );
				CLACT_AnmChg( wk->MainActWork[i+1], 38+sex*2+1 );
			}else{
				CLACT_AnmChg( wk->MainActWork[i+1], 27+i*2+1 );
			}
			wk->TrainerReq[i] = RECORD_EXIST_NO;
			break;
		}
	}
	
	// �o��SE���K�v�ȏꍇ�͖炷
	if(seflag){
		Snd_SePlay( SE_GTC_APPEAR );
	}
}


//------------------------------------------------------------------
/**
 * @brief   �t�B�[���hOBJ�摜�ǂݍ��݁i���j�I���Ǝ��@�j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadFieldObjData( RECORD_WORK *wk )
{
	// �p���b�g�ǂݍ���
	wk->FieldObjPalBuf[0] = ArcUtil_PalDataGet( ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_nclr, &(wk->FieldObjPalData[0]), HEAPID_RECORD );
	wk->FieldObjPalBuf[1] = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &(wk->FieldObjPalData[1]), HEAPID_RECORD );

	// �摜�ǂݍ���
	wk->FieldObjCharaBuf[0] = ArcUtil_CharDataGet( ARC_WORLDTRADE_GRA, NARC_worldtrade_hero_lz_ncgr, 1, &(wk->FieldObjCharaData[0]), HEAPID_RECORD );
	wk->FieldObjCharaBuf[1] = ArcUtil_CharDataGet( ARC_RECORD_GRA, NARC_record_union_chara_lz_ncgr,  1, &(wk->FieldObjCharaData[1]), HEAPID_RECORD );

}

#define OBJ_TRANS_SIZE	( 3 * 4*4 )
static const u16 obj_offset[]={
	( 13                    )*0x20,
	( 13 + OBJ_TRANS_SIZE*1 )*0x20,
	( 13 + OBJ_TRANS_SIZE*2 )*0x20,
	( 13 + OBJ_TRANS_SIZE*3 )*0x20,
	( 13 + OBJ_TRANS_SIZE*4 )*0x20,
};


static int _obj_no = 0;
static int _pal_no = 0;

//------------------------------------------------------------------
/**
 * @brief   �n���ꂽ���j�I�������ڃR�[�h����t�B�[���hOBJ�̃L������]������
 *
 * @param   id		
 * @param   view		
 * @param   sex		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransFieldObjData( NNSG2dCharacterData *CharaData[2], NNSG2dPaletteData *PalData[2], int id, int view, int sex )
{
	int pos;
	u8 *chara, *pal;
	
	// ���j�I���L������]��

	pos   = UnionView_GetCharaNo( sex, view );

	chara = (u8*)CharaData[1]->pRawData;
	pal   = (u8*)PalData[1]->pRawData;

	GX_LoadOBJ( &chara[OBJ_TRANS_SIZE*pos*0x20], obj_offset[id], OBJ_TRANS_SIZE*0x20 );
	GX_LoadOBJPltt( &pal[pos*32], (id+FIELDOBJ_PAL_START)*32, 32 );

	OS_Printf("ID=%d �̃��j�I�������ڂ� %d �A�C�R���ԍ��� %d\n", id, view, pos);

	
	
}

//------------------------------------------------------------------
/**
 * @brief   �t�B�[���hOBJ�摜���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeFieldObjData( RECORD_WORK *wk )
{

	sys_FreeMemoryEz( wk->FieldObjPalBuf[0]  );
	sys_FreeMemoryEz( wk->FieldObjPalBuf[1]  );
                      
	sys_FreeMemoryEz( wk->FieldObjCharaBuf[0] );
	sys_FreeMemoryEz( wk->FieldObjCharaBuf[1] );
}

//------------------------------------------------------------------
/**
 * @brief   ��b�X�s�[�h���擾
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetTalkSpeed( RECORD_WORK *wk )
{
	return 1;
//	return CONFIG_GetMsgPrintSpeed(wk->param->config);
}

//------------------------------------------------------------------
/**
 * @brief   �ڑ��l�������̎��ڑ��l���{�P�ɂȂ�悤�ɍĐݒ肷��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChangeConnectMax( RECORD_WORK *wk, int plus )
{
	if(CommGetCurrentID()==0){
		if(plus == -1){
			CommStateSetLimitNum(1);
			OS_Printf("�ڑ��l���������I��1�l�ɕύX\n");
		}
		else{
			int num = CommGetConnectNum()+plus;
			if(num>5){
				num = 5;
			}
			CommStateSetLimitNum(num);
			OS_Printf("�ڑ��l���� %d�l�ɕύX\n",num);
		}
		
		if(plus == -1){
			wk->limit_mode = LIMIT_MODE_ONLY;
		}
		else if(plus == 0){
			wk->limit_mode = LIMIT_MODE_TRUE;
		}
		else{
			wk->limit_mode = LIMIT_MODE_NONE;
		}
	}

}


//------------------------------------------------------------------
/**
 * @brief   ��W�l���ƃr�[�R������ݒ肷��
 *
 * @param   wk		
 * @param   plus	1�Ȃ��W���������A0�Ȃ���ߐ؂肽���Ƃ�
 *
 * @retval  none
 */
//------------------------------------------------------------------
static int RecordCorner_BeaconControl( RECORD_WORK *wk, int plus )
{
	int num;
	// �r�[�R��������������
	num = MyStatusGetNum();

	if(num>wk->shareNum){
		u8 flag = RECORD_BAN_ON;
		// ���E�֎~�����ʒB
		CommSendData( CR_RECORD_BAN, &flag, 1 );
		wk->beacon_flag = RECORD_BAN_ON;
	}
	else{
		wk->beacon_flag = RECORD_BAN_NONE;
	}

	// �ڑ��l���ƃ��R�[�h�����\�l������v����܂ł͑���֎~
	if(num==wk->connectBackup){
		return SEQ_MAIN;
	}

	OS_TPrintf("�l�����ς����\n");

	// �������Ȃ��A�����ߐ؂�ł��Ȃ��Ȃ��W���s
	switch(num){
	case 1:
		// �ЂƂ�ɂȂ����̂ŏI��
		OS_TPrintf("ONLY!! Comm = %d, My = %d, Bit = %d\n", CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		if(CommGetConnectNum() > 1 || WH_GetBitmap() > 1){
			return SEQ_MAIN;	//���S�Ɉ�l�ɂ͂Ȃ��Ă��Ȃ��̂ł܂��������Ȃ�
		}
		wk->seq = RECORD_MODE_END_PARENT_ONLY;
		ChangeConnectMax( wk, -1 );
		if(wk->YesNoMenuWork!=NULL){
			BmpYesNoWinDel( wk->YesNoMenuWork, HEAPID_RECORD );
			wk->YesNoMenuWork = NULL;
		}
		return SEQ_LEAVE;
		break;
	case 2:	case 3:case 4:
		// �܂�������
		Union_BeaconChange( UNION_PARENT_MODE_RECORD_FREE );

		// �ڑ��l�����������ꍇ�͐ڑ��ő�l�������炷
		if(num<wk->connectBackup){
			switch(wk->limit_mode){
			case LIMIT_MODE_NONE:
				ChangeConnectMax( wk, plus );
				break;
			case LIMIT_MODE_TRUE:
				ChangeConnectMax(wk, 0);
				break;
			}
			wk->shareNum = CommGetConnectNum();
		}
		break;
	case 5:
		// �����ς��ł�
		Union_BeaconChange( UNION_PARENT_MODE_RECORDNOW );
		ChangeConnectMax( wk, plus );
		break;
	}

	
	// �ڑ��l����ۑ�
	wk->connectBackup = MyStatusGetNum();

	return SEQ_MAIN;
}