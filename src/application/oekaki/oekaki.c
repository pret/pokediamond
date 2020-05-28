//============================================================================================
/**
 * @file	oekaki.c
 * @bfief	���G�����{�[�h��ʏ���
 * @author	Akito Mori
 * @date	05.10.05
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
#include "msgdata/msg_oekaki.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wh.h"
#include "field/fld_bmp.h"
#include "field/fieldobj.h"
#include "field/comm_union_beacon.h"
#include "field/comm_union_view_common.h"
#include "savedata/fnote_mem.h"
#include "savedata/config.h"

#include "application/oekaki.h"

#include "oekaki_local.h"

#include "comm_command_oekaki.h"


//#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"

// SE�p��`
#define OEKAKI_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define OEKAKI_BS_SE		(SEQ_SE_DP_CUSTOM06)


#include "oekaki.naix"			// �O���t�B�b�N�A�[�J�C�u��`

//============================================================================================
//	�萔��`
//============================================================================================

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( OEKAKI_WORK *wk );
static void FreeWork( OEKAKI_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( OEKAKI_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(OEKAKI_WORK *wk);
static void SetCellActor(OEKAKI_WORK *wk);
static void BmpWinInit(OEKAKI_WORK *wk, PROC* proc);
static void BmpWinDelete( OEKAKI_WORK *wk );
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void NormalTouchFunc(OEKAKI_WORK *wk);
static int Oekaki_MainNormal( OEKAKI_WORK *wk, int seq );
static void EndSequenceCommonFunc( OEKAKI_WORK *wk );
static int Oekaki_EndSelectPutString( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerOK( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectAnswerNG( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChild( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChildWait( OEKAKI_WORK *wk, int seq );
static int 	Oekaki_EndChildWait2( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectParent( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndSelectParentWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEnd( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEndWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_ForceEndSynchronize( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndParentOnly( OEKAKI_WORK *wk, int seq );
static int Oekaki_EndParentOnlyWait( OEKAKI_WORK *wk, int seq );
static void DrawPoint_to_Line( 	GF_BGL_BMPWIN *win, 	const u8 *brush, 	int px, int py, int *sx, int *sy, 	int count, int flag );
static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock );
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw );
static void MoveCommCursor( OEKAKI_WORK *wk );
static void DebugTouchDataTrans( OEKAKI_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, OEKAKI_WORK *wk );
static int ConnectCheck( OEKAKI_WORK *wk );
static void LineDataSendRecv( OEKAKI_WORK *wk );
static int MyStatusCheck( OEKAKI_WORK *wk );
static void EndMessagePrint( OEKAKI_WORK *wk, int msgno, int wait );
static int EndMessageWait( int msg_index );
static void EndMessageWindowOff( OEKAKI_WORK *wk );
static int OnlyParentCheck( void );
static int Oekaki_LogoutChildMes( OEKAKI_WORK *wk, int seq );
static int Oekaki_LogoutChildClose( OEKAKI_WORK *wk, int seq );
static int Oekaki_LogoutChildMesWait( OEKAKI_WORK *wk, int seq );
static int MyStatusGetNum( void );
static int Oekaki_NewMemberWait( OEKAKI_WORK *wk, int seq );
static int Oekaki_NewMember( OEKAKI_WORK *wk, int seq );
static int Oekaki_NewMemberEnd( OEKAKI_WORK *wk, int seq );
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no);
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag );
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy );
static void ChangeConnectMax( OEKAKI_WORK *wk, int plus );
static int ConnectNumControl( OEKAKI_WORK *wk );
static int Oekaki_ForceEndWaitNop( OEKAKI_WORK *wk, int seq );
static void SetNextSequence( OEKAKI_WORK *wk, int nextSequence );
static void OekakiSequenceControl( OEKAKI_WORK *wk, int proc_seq );

static BOOL OekakiInitYesNoWin(OEKAKI_WORK *wk, TOUCH_SW_PARAM *param);
static void OekakiResetYesNoWin(OEKAKI_WORK *wk);
static int FakeEndYesNoSelect( OEKAKI_WORK  *wk );
static void SetTouchpanelData( TOUCH_INFO *touchResult, TP_ONE_DATA *tpData, int brush_color, int brush );


typedef struct{
	int (*func)(OEKAKI_WORK *wk, int seq);
	int execOn_SeqLeave;
}OEKAKI_FUNC_TABLE;

static OEKAKI_FUNC_TABLE FuncTable[]={
	{NULL,						1,},	// OEKAKI_MODE_INIT  = 0, 
	{Oekaki_NewMember, 		    0,},    // OEKAKI_MODE_NEWMEMBER,
	{Oekaki_NewMemberWait,      0,},    // OEKAKI_MODE_NEWMEMBER_WAIT,
	{Oekaki_NewMemberEnd,       0,},    // OEKAKI_MODE_NEWMEMBER_END,
	{Oekaki_MainNormal,         0,},    // OEKAKI_MODE,
	{Oekaki_EndSelectPutString, 1,},    // OEKAKI_MODE_END_SELECT,
	{Oekaki_EndSelectWait,		1,},	// OEKAKI_MODE_END_SELECT_WAIT,
	{Oekaki_EndSelectAnswerWait,1,},	// OEKAKI_MODE_END_SELECT_ANSWER_WAIT
	{Oekaki_EndSelectAnswerOK,	1,},	// OEKAKI_MODE_END_SELECT_ANSWER_OK
	{Oekaki_EndSelectAnswerNG,	1,},	// OEKAKI_MODE_END_SELECT_ANSWER_NG
	{Oekaki_EndChild,			1,},	// OEKAKI_MODE_END_CHILD
	{Oekaki_EndChildWait,		1,},	// OEKAKI_MODE_END_CHILD_WAIT
	{Oekaki_EndChildWait2,		1,},	// OEKAKI_MODE_END_CHILD_WAIT2
	{Oekaki_EndSelectParent,	1,},	// OEKAKI_MODE_END_SELECT_PARENT
	{Oekaki_EndSelectParentWait,1,},	// OEKAKI_MODE_END_SELECT_PARENT_WAIT
	{Oekaki_ForceEnd,			1,},	// OEKAKI_MODE_FORCE_END
	{Oekaki_ForceEndWait,		1,},	// OEKAKI_MODE_FORCE_END_WAIT
	{Oekaki_ForceEndSynchronize,1,},	// OEKAKI_MODE_FORCE_END_SYNCHRONIZE
	{Oekaki_ForceEndWaitNop,	1,},	// OEKAKI_MODE_FORCE_END_WAIT_NOP
	{Oekaki_EndParentOnly,		1,},	// OEKAKI_MODE_END_PARENT_ONLY
	{Oekaki_EndParentOnlyWait,	1,},	// OEKAKI_MODE_END_PARENT_ONLY_WAIT
	{Oekaki_LogoutChildMes,		1,},	// OEKAKI_MODE_LOGOUT_CHILD
	{Oekaki_LogoutChildMesWait,	1,},	// OEKAKI_MODE_LOGOUT_CHILD_WAIT
	{Oekaki_LogoutChildClose,	1,},	// OEKAKI_MODE_LOGOUT_CHILD_CLOSE
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
PROC_RESULT OekakiProc_Init( PROC * proc, int * seq )
{
	OEKAKI_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OEKAKI, 0x40000 );

		wk = PROC_AllocWork( proc, sizeof(OEKAKI_WORK), HEAPID_OEKAKI );
		memset( wk, 0, sizeof(OEKAKI_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OEKAKI );
		
		// ������}�l�[�W���[����
		wk->WordSet    = WORDSET_Create( HEAPID_OEKAKI );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_oekaki_dat, HEAPID_OEKAKI );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM �o���N�ݒ�
		VramBankSet();
		
		// BGL���W�X�^�ݒ�
		BgInit( wk->bgl );					

		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

		// �P�x�ύX�Z�b�g
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEIN, WIPE_TYPE_HOLEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		
		// �p�����[�^�擾
		{
			OEKAKI_PARAM *param = (OEKAKI_PARAM*)PROC_GetParentWork( proc );
			wk->param = param;
		}

		//BG�O���t�B�b�N�Z�b�g
		BgGraphicSet( wk );

		// �^�b�`�p�l���V�X�e��������
		InitTPSystem();						
		InitTPNoBuff(2);
  
		// VBlank�֐��Z�b�g
		sys_VBlankFuncChange( VBlankFunc, wk->bgl );	
  
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
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

		// �ʐM�R�}���h���������X�g�p�ɕύX
		CommCommandOekakiBoardInitialize( wk );
        // ���G�������ɂ͐ڑ��ؒf�ŃG���[�������Ȃ�
        CommStateSetErrorCheck(FALSE,TRUE);
        
        // 3��܂Őڑ��\�ɏ�������(�J�n�������͂Q�l�ł����ɂ���̂ł��ƈ�l���������悤�ɂ��Ă����j
		if(CommGetCurrentID()==0){
	        CommStateSetLimitNum(3);
		}

		
		WirelessIconEasy();

		// �e��������u���������ʐM���v�Ƀr�[�R����������
		if(CommGetCurrentID()==0){
			Union_BeaconChange( UNION_PARENT_MODE_OEKAKI_FREE );
			CommMPSetDisconnectOtherError(TRUE);
		}
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

PROC_RESULT OekakiProc_Main( PROC * proc, int * seq )
{
	OEKAKI_WORK * wk  = PROC_GetWork( proc );

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		wk->ridatu_bit &= WH_GetBitmap();
	}
	
	// ���[�N�Ɍ��݂�proc�V�[�P���X��ۑ�
	wk->proc_seq = *seq;

	// �T�u�V�[�P���X�J�ڐ�����s��
	OekakiSequenceControl( wk, *seq );
	
	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ���C�v�����҂�
//			*seq = SEQ_MAIN;

			// �������q�@�Őڑ��䐔���Q��ȏゾ�����ꍇ�͂����G���`����Ă���
			if(CommGetCurrentID()!=0){
				if( (MyStatusGetNum()>=2) ){
					// �q�@�������N�G�X�g
					CommSendData(CO_OEKAKI_CHILD_JOIN, NULL, 0);
					OS_Printf("�������܂�\n");
					*seq = SEQ_MAIN;
				}
				break;
			}else{
				//�e�̓��C����
				*seq = SEQ_MAIN;
			}
		}
		break;

	case SEQ_MAIN:
		// �J�[�\���ړ�

		// �V�[�P���X���̓���
		if(FuncTable[wk->seq].func!=NULL){
			*seq = FuncTable[wk->seq].func( wk, *seq );
		}
		// �ڑ��l�����m�F���ď��ʂɖ��O��`��
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xd,0xf),wk);

		if(CommGetCurrentID()==0){				// �e��
			int temp = ConnectNumControl(wk);
			if(*seq == SEQ_MAIN){
				// ���ɏI���V�[�P���X�Ȃǂɓ����Ă���ꍇ�͏��������Ȃ�
				*seq = temp;
			}
		}
		CursorColTrans(&wk->CursorPal);

		break;
	case SEQ_LEAVE:
		if(FuncTable[wk->seq].func!=NULL && FuncTable[wk->seq].execOn_SeqLeave){
			*seq = FuncTable[wk->seq].func( wk, *seq );
		}
		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			OS_Printf("���C�v�I���m�F\n");
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
PROC_RESULT OekakiProc_End( PROC * proc, int * seq )
{
	OEKAKI_WORK  *wk    = PROC_GetWork( proc );
	OEKAKI_PARAM *param = (OEKAKI_PARAM*)PROC_GetParentWork( proc );
	int i;
	void *FnoteWork;

	switch(*seq){
	case 0:
		OS_Printf("�����������[�N��������˓�\n");
		// �`���m�[�g�p����
		FnoteWork = FNOTE_SioUnionPictureDataMake( HEAPID_OEKAKI );
		FNOTE_DataSave( param->fnote, FnoteWork, FNOTE_TYPE_SIO );

		// Vblank���Ԓ���BG�]���I��
		sys_VBlankFuncChange( NULL, NULL);

		// �Z���A�N�^�[���\�[�X���

		// �L�����]���}�l�[�W���[�j��
		CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
		CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

		// �p���b�g�]���}�l�[�W���[�j��
		CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
		CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
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

		// �^�b�`�p�l���V�X�e���I��
		StopTP();							


		// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
		MSGMAN_Delete( wk->MsgManager );
		WORDSET_Delete( wk->WordSet );

		(*seq)++;
		break;
	case 1:
		// �ʐM�I��
	//	CommStateExitUnion();
		CommStateSetLimitNum(1);
		CommStateUnionBconCollectionRestart();
		UnionRoomView_ObjInit( param->view );

		// ����ւ���Ă����㉺��ʏo�͂����ɖ߂�
		GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

		// �r�[�R����������
		Union_BeaconChange( UNION_PARENT_MODE_FREE );

		CommMPSetDisconnectOtherError(FALSE);
		(*seq)++;
		break;
	case 2:
		if (wk->ireagalJoin){
			OS_Printf("�e�@�����ɂȂ�܂őҋ@\n");	
			if (WH_GetBitmap() == 1){
				(*seq)++;
			}
		}else{
			(*seq)++;
		}
		break;
	case 3:
		CommStateSetLimitNum(2);
		// ���[�N���
		FreeWork( wk );

		sys_FreeMemoryEz( wk->param );

		PROC_FreeWork( proc );				// PROC���[�N�J��

		sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

		sys_DeleteHeap( HEAPID_OEKAKI );

		CommStateSetLimitNum(2);

		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
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
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// ���C����ʃ��N�K�L��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// ���C����ʔw�i
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

#if 0
	// �w�i (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
#endif

	// �T�u��ʃe�L�X�g��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// �T�u��ʔw�i��
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_OEKAKI );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_OEKAKI );

}


#define TALK_MESSAGE_BUF_NUM	( 40*2 )

//------------------------------------------------------------------
/**
 * ���G�������[�N������
 *
 * @param   wk		OEKAKI_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( OEKAKI_WORK *wk )
{
	int i;

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_OEKAKI );
		wk->AllTouchResult[i].size = 0;
		wk->OldTouch[i].size = 0;
		wk->TrainerStatus[i][0] = NULL;
		wk->TrainerStatus[i][1] = NULL;

	}
	// �u��߂�v������o�b�t�@�쐬
	wk->EndString  = STRBUF_Create( 10, HEAPID_OEKAKI );
	wk->TalkString = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_OEKAKI );

	// �u���V������
	wk->brush_color  = 0;
	wk->brush        = MIDDLE_BRUSH;
	wk->banFlag      = OEKAKI_BAN_OFF;
	wk->yesno_flag   = 0;
	wk->shareNum     = 2;
	wk->shareBit     = WH_GetBitmap();
	wk->firstChild   = 0;
	wk->ireagalJoin  = 0;
	wk->seq          = 0;
	wk->bookJoin  = 0;
	wk->joinBit  = 0;

	// �e�͒ʐM�ŊG���󂯎��K�v������
	if( CommGetCurrentID()==0 ){
		SetNextSequence( wk, OEKAKI_MODE );
	}else{
		// �G���󂯎��Ȃ��Ƃ����Ȃ�
		SetNextSequence( wk, OEKAKI_MODE );
	}
	
	// �u��߂�v�擾
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_08, wk->EndString );

	// ���G�����摜���k�f�[�^�̈�
	wk->lz_buf = sys_AllocMemory( HEAPID_OEKAKI, 30*16*32 );

	// ����ʃE�C���h�E�V�X�e��������
	wk->TouchSubWindowSys = TOUCH_SW_AllocWork( HEAPID_OEKAKI );

	// �ڑ��l���Ď��p���[�N������
	wk->connectBackup = 0;
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
static void FreeWork( OEKAKI_WORK *wk )
{
	int i;

	sys_FreeMemoryEz(  wk->lz_buf );
	TOUCH_SW_FreeWork( wk->TouchSubWindowSys );


	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->EndString  ); 

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

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
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
static void BgGraphicSet( OEKAKI_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, PALTYPE_MAIN_BG, 0, 16*2*2,  HEAPID_OEKAKI);
	ArcUtil_PalSet(    ARC_OEKAKI_GRA, NARC_oekaki_oekaki_s_nclr, PALTYPE_SUB_BG,  0, 16*2*2,  HEAPID_OEKAKI);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_OEKAKI );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_OEKAKI );




	// ���C�����BG2�L�����]��
	ArcUtil_BgCharSet( ARC_OEKAKI_GRA, NARC_oekaki_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// ���C�����BG2�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_OEKAKI_GRA, NARC_oekaki_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_OEKAKI);



	// �T�u���BG1�L�����]��
	ArcUtil_BgCharSet( ARC_OEKAKI_GRA, NARC_oekaki_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// �T�u���BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_OEKAKI_GRA, NARC_oekaki_subbg_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_OEKAKI);

	// �T�u��ʉ�b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->param->config), HEAPID_OEKAKI );

	MenuWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1+TALK_WIN_CGX_SIZ, FLD_MENUFRAME_PAL, 0, HEAPID_OEKAKI );

}


//** CharManager PlttManager�p **//
#define OEKAKI_CHAR_CONT_NUM				(20)
#define OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define OEKAKI_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define OEKAKI_PLTT_CONT_NUM				(20)

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
			OEKAKI_CHAR_CONT_NUM,
			OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE,
			OEKAKI_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_OEKAKI
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(OEKAKI_PLTT_CONT_NUM, HEAPID_OEKAKI);

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
static void InitCellActor(OEKAKI_WORK *wk)
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
			HEAPID_OEKAKI);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( 50+3, &wk->renddata, HEAPID_OEKAKI );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_OEKAKI);
	}


	//---------���ʗp-------------------

	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OEKAKI);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAPID_OEKAKI);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);


	//---------����ʗp-------------------



	//chara�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_OEKAKI);

	//pal�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_oekaki_m_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_OEKAKI);

	//cell�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_OEKAKI_GRA, NARC_oekaki_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);

	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

static const u16 pal_button_oam_table[][3]={
	{13     , 171, 5},		// ��
	{13+24*1, 171, 7},		// ��
	{13+24*2, 171, 9},		// ��
	{13+24*3, 171,11},		// ��
	{13+24*4, 171,13},		// ��
	{13+24*5, 171,15},		// ���F
	{13+24*6, 171,17},		// ��
	{13+24*7, 171,19},		// ���F
	{13+24*8+20, 171,21},	// �u��߂�v

	// �y����A�C�R��
	{20,	  9,   29, },
	{36,      9,   32, },	// �����l�Ō����ԂɂȂ��Ă���
	{52,      9,   33, },
};

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			OEKAKI_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(OEKAKI_WORK *wk)
{
	int i;
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

	{
		//�o�^���i�[
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_m;

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_OEKAKI;

		//�Z���A�N�^�[�\���J�n

		// ���C����ʗp(���̓o�^�j
		for(i=0;i<5;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  TRAINER_NAME_POS_X + i * 40);
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN );
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->MainActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->MainActWork[i],1);
			CLACT_AnmChg( wk->MainActWork[i], i );
			CLACT_SetDrawFlag( wk->MainActWork[i], 0 );

		}

		// ���C����ʃp���b�g�E�u��߂�v�{�^���̓o�^
		for(i=0;i<9+3;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  pal_button_oam_table[i][0]);
			add.mat.y = FX32_ONE * ( pal_button_oam_table[i][1] );
			wk->ButtonActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ButtonActWork[i],1);
			CLACT_AnmChg( wk->ButtonActWork[i], pal_button_oam_table[i][2] );
			if(i >= 8){
				CLACT_BGPriorityChg( wk->ButtonActWork[i], 2 );
			}
//			CLACT_SetDrawFlag( wk->ButtonActWork[i], 0 );
		}

		// ���F�p���b�g�͂ւ��܂��Ă���
		CLACT_AnmChg( wk->ButtonActWork[0], 6 );


		// �T�u��ʗp(���̓o�^�j
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
			wk->SubActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->SubActWork[i],1);
			CLACT_AnmChg( wk->SubActWork[i], i );
			CLACT_DrawPriorityChg(wk->SubActWork[i], 1);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
			
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
#define OEKAKI_NAME_BMP_W	 ( 10 )
#define OEKAKI_NAME_BMP_H	 (  2 )
#define OEKAKI_NAME_BMP_SIZE (OEKAKI_NAME_BMP_W * OEKAKI_NAME_BMP_H)


// �u��߂�v������BMP�i����ʁj
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 21 )
#define OEKAKI_END_BMP_W	( 6  )
#define OEKAKI_END_BMP_H	( 2  )


// ��b�E�C���h�E�\���ʒu��`
#define OEKAKI_TALK_X		(  2 )
#define OEKAKI_TALK_Y		(  1 )
//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit(OEKAKI_WORK *wk, PROC* proc)
{
	// ---------- ���C����� ------------------

	// BG0��BMP�i��b�E�C���h�E�j�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		OEKAKI_TALK_X, OEKAKI_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG1�ʗpBMP�i���G�����摜�j�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->OekakiBoard, GF_BGL_FRAME1_M,
		OEKAKI_BOARD_POSX, OEKAKI_BOARD_POSY, OEKAKI_BOARD_W, OEKAKI_BOARD_H, 0,  1 );
	GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );

	// BG1��BMP�i��߂�j�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_M,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 13,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );
//	GF_STR_PrintSimple( &wk->EndWin, FONT_TALK, wk->EndString, 0, 0, MSG_ALLPUT, NULL);
	GF_STR_PrintColor( &wk->EndWin, FONT_TALK, wk->EndString, 0, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x7,0x1,0x0),NULL);

	// ----------- �T�u��ʖ��O�\��BMP�m�� ------------------
	{
		int i;
		for(i=0;i<OEKAKI_MEMBER_MAX;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[i], GF_BGL_FRAME0_S,	
				TRAINER_NAME_POS_X/8+2, TRAINER_NAME_POS_Y/8+i*4-1, 10, 2, 13,  1+i*OEKAKI_NAME_BMP_SIZE);
			GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[i], 0 );
		}

		//�ŏ��Ɍ����Ă���ʂȂ̂ŕ����p�l���`��Ɠ]�����s��
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xd,0xf), wk );
	}

}	

// �͂��E�������p��`�i����ʁj
#define YESNO_CHARA_OFFSET	(1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY)
#define YESNO_CHARA_W		( 8 )
#define YESNO_CHARA_H		( 4 )





//------------------------------------------------------------------
/**
 * $brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( OEKAKI_WORK *wk )
{
	int i;
	
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->OekakiBoard );
	GF_BGL_BmpWinDel( &wk->MsgWin );


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
	mat.y = FX32_CONST( y - 8 );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


// ---------------------------------------------------------
// �ʏ펞�^�b�`���o�e�[�u��
// ---------------------------------------------------------

#define PAL_BUTTON_X	(  0  )
#define PAL_BUTTON_Y	( 150 )
#define PAL_BUTTON_W	( 3*8 )
#define PAL_BUTTON_H	( 5*8 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define PAL_BUTTON_RECT ( 3*8 -1 )
#define END_BUTTON_RECT ( 8*8 -1 )

#define PAL_BUTTON0_X	( PAL_BUTTON_X+PAL_BUTTON_W*0 )
#define PAL_BUTTON1_X	( PAL_BUTTON_X+PAL_BUTTON_W*1 )
#define PAL_BUTTON2_X	( PAL_BUTTON_X+PAL_BUTTON_W*2 )
#define PAL_BUTTON3_X	( PAL_BUTTON_X+PAL_BUTTON_W*3 )
#define PAL_BUTTON4_X	( PAL_BUTTON_X+PAL_BUTTON_W*4 )
#define PAL_BUTTON5_X	( PAL_BUTTON_X+PAL_BUTTON_W*5 )
#define PAL_BUTTON6_X	( PAL_BUTTON_X+PAL_BUTTON_W*6 )
#define PAL_BUTTON7_X	( PAL_BUTTON_X+PAL_BUTTON_W*7 )
#define END_BUTTON_X	( PAL_BUTTON_X+PAL_BUTTON_W*8 )

#define BRUSH_BUTTON0_X ( 14 ) // 16,5 23,12
#define BRUSH_BUTTON1_X ( 30 ) // 16,5 23,12
#define BRUSH_BUTTON2_X ( 46 ) // 16,5 23,12
#define BRUSH_BUTTON_Y  (  1 ) // 16,5 23,12
#define BRUSH_BUTTON_W  ( 12 ) // 16,5 23,12
#define BRUSH_BUTTON_H  ( 12 ) // 16,5 23,12


static const RECT_HIT_TBL sub_button_hittbl[]={

// �p���b�g
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON0_X,PAL_BUTTON0_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON1_X,PAL_BUTTON1_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON2_X,PAL_BUTTON2_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON3_X,PAL_BUTTON3_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON4_X,PAL_BUTTON4_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON5_X,PAL_BUTTON5_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON6_X,PAL_BUTTON6_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON7_X,PAL_BUTTON7_X+PAL_BUTTON_RECT},

// �I���{�^��
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,END_BUTTON_X,END_BUTTON_X+END_BUTTON_RECT},

// �y����{�^��
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON0_X,BRUSH_BUTTON0_X+BRUSH_BUTTON_W},
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON1_X,BRUSH_BUTTON1_X+BRUSH_BUTTON_W},
{BRUSH_BUTTON_Y,BRUSH_BUTTON_Y+BRUSH_BUTTON_H, BRUSH_BUTTON2_X,BRUSH_BUTTON2_X+BRUSH_BUTTON_W},

{RECT_HIT_END,0,0,0},		// �I���f�[�^
};


// ---------------------------------------------------------
// ���E�I���֎~���̍ۂ�YESNO�{�^�����o�e�[�u��
// ---------------------------------------------------------
#define OEKAKI_YESNO_BUTTON_X ( 25 )
#define OEKAKI_YESNO_BUTTON_Y ( 6  )

#define FAKE_YESNO_X	( OEKAKI_YESNO_BUTTON_X*8 )
#define FAKE_YESNO_Y	( OEKAKI_YESNO_BUTTON_Y*8 )
#define FAKE_YESNO_W	( 6*8 )
#define FAKE_YESNO_H	( 8*8 )

static const RECT_HIT_TBL fake_yesno_hittbl[]={
{FAKE_YESNO_Y, FAKE_YESNO_Y+FAKE_YESNO_H, FAKE_YESNO_X, FAKE_YESNO_X+FAKE_YESNO_W},
{RECT_HIT_END,0,0,0},
};

// ---------------------------------------------------------
// �`��̈挟�o�p�e�[�u��
// ---------------------------------------------------------
#define DRAW_AREA_X	(  8  )
#define DRAW_AREA_Y	( 16  )
#define DRAW_AREA_W	( OEKAKI_BOARD_W*8 )
#define DRAW_AREA_H	( OEKAKI_BOARD_H*8)

static const RECT_HIT_TBL sub_canvas_touchtbl[]={
	{DRAW_AREA_Y,DRAW_AREA_Y+DRAW_AREA_H,DRAW_AREA_X,DRAW_AREA_X+DRAW_AREA_W},
{RECT_HIT_END,0,0,0},		// �I���f�[�^
};




//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ŉ������{�^�����ւ���
 *
 * @param   wk		OEKAKI_WORK�̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NormalTouchFunc(OEKAKI_WORK *wk)
{
	int button=-1,touch;
	int decide = FALSE;
	
	// ���͏���

	// �J���[�؂�ւ�
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		switch(button){
		case 0:	case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			// �F�ύX
			if(wk->brush_color!=button){
				wk->brush_color = button;
				PalButtonAppearChange( wk->ButtonActWork, button);
				Snd_SePlay(OEKAKI_DECIDE_SE);
			}
			break;
		case 8:
			// �u��߂�v����������E�C���h�E�`��J�n
			if(wk->seq==OEKAKI_MODE){
				// �e�@�̏ꍇ�͐ڑ�����
				if(CommGetCurrentID()==0){
					//�R�l�N�g���ƕ\���l�����قȂ�ꍇ�́A��߂�{�^���𖳔����ɂ���
					if (wk->shareBit != WH_GetBitmap()){
						Snd_SePlay(OEKAKI_BS_SE);
						break;
					}
					CommStateSetLimitNum(CommGetConnectNum());
					wk->banFlag = OEKAKI_BAN_ON;
					// �u������������߂܂����H�v
					EndMessagePrint( wk, msg_oekaki_02, 1 );
					SetNextSequence( wk, OEKAKI_MODE_END_SELECT );
					EndButtonAppearChange( wk->ButtonActWork, TRUE );
					decide = TRUE;
					Snd_SePlay(OEKAKI_DECIDE_SE);
				}else{
					if(wk->AllTouchResult[0].banFlag == OEKAKI_BAN_ON ){
						// �e�@�ɋ֎~����Ă���Ƃ��͂r�d�̂�
						Snd_SePlay(OEKAKI_BS_SE);
					}else{
						// �u������������߂܂����H�v
						EndMessagePrint( wk, msg_oekaki_02, 1 );
						SetNextSequence( wk, OEKAKI_MODE_END_SELECT );
						EndButtonAppearChange( wk->ButtonActWork, TRUE );
						decide = TRUE;
						Snd_SePlay(OEKAKI_DECIDE_SE);
					}
				}

			}
			break;
		case 9:	case 10: case 11:
			// �y����ύX
			{
				int i;
				for(i=0;i<3;i++){
					if((button-9)==i){
						CLACT_AnmChg( wk->ButtonActWork[CELL_BRUSH_NO+i], 29+2*i+1 );		// ON
					}else{
						CLACT_AnmChg( wk->ButtonActWork[CELL_BRUSH_NO+i], 29+2*i );	// OFF
					}
				}
				if(wk->brush!=(SMALL_BRUSH + button-9)){
					wk->brush = SMALL_BRUSH + button-9;
					Snd_SePlay(SEQ_SE_DP_BUTTON3);
				}
			}
			break;
		}
	}

	// �J�[�\���ʒu�ύX
	touch = GF_TP_RectHitCont( sub_canvas_touchtbl );

	CLACT_SetDrawFlag( wk->MainActWork[CommGetCurrentID()], 0 );
	if(touch!=RECT_HIT_NONE){
		// �����̃J�[�\���̓^�b�`�p�l���̍��W�𔽉f������
		SetCursor_Pos( wk->MainActWork[CommGetCurrentID()], sys.tp_x, sys.tp_y );
		CLACT_SetDrawFlag( wk->MainActWork[CommGetCurrentID()], 1 );
	}

	// �T���v�����O�����擾���Ċi�[
	{
		TP_ONE_DATA	tpData;
		int i;
		if(MainTP( &tpData, TP_BUFFERING_JUST, 64 )==TP_OK){
			SetTouchpanelData( &wk->MyTouchResult, &tpData, wk->brush_color, wk->brush );

			if(decide == TRUE){
				wk->MyTouchResult.size = 0;
			}
		}
	}

	// �����ڂ̏���
//	button=GF_TP_RectHitCont( sub_button_hittbl );


}


//------------------------------------------------------------------
/**
 * $brief   �p���b�g�Ƃ�߂�{�^���̃Z���A�N�^�[����
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   button		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no )
{
	int i;
	
	for(i=0;i<8;i++){
		// �����ꂽ�{�^���͂ւ��ށB�ق��̃{�^���͖߂�
		if(i==no){
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2]+1 );
		}else{
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2] );
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   ��߂�{�^���̃I���E�I�t
 *
 * @param   act		�A�N�^�[�̃|�C���^
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag )
{
	if(flag==TRUE){
		CLACT_AnmChg( act[8], pal_button_oam_table[8][2]+1 );
	}else{
		CLACT_AnmChg( act[8], pal_button_oam_table[8][2] );
	}
}

//------------------------------------------------------------------
/**
 * $brief   ���G�����{�[�h�ʏ폈��
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_MainNormal( OEKAKI_WORK *wk, int seq )
{
	NormalTouchFunc(wk);			//  �^�b�`�p�l������


	
	if(CommGetCurrentID()==0){				// �e�@�̎�
		if(OnlyParentCheck()!=1){			// ��l����Ȃ����H
			LineDataSendRecv( wk );
		}
	}else{
			LineDataSendRecv( wk );
	}
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 1 );

	return seq;
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
static void EndSequenceCommonFunc( OEKAKI_WORK *wk )
{
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 0 );
	
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
static int Oekaki_NewMember( OEKAKI_WORK *wk, int seq )
{
	// ���������񂪂͂����Ă��܂���
	OS_Printf("newMember��%d\n",wk->newMemberId);
	if(CommGetCurrentID()==wk->newMemberId){
		EndMessagePrint(wk, msg_oekaki_14, 0);
	}else{
		EndMessagePrint(wk, msg_oekaki_01, 0);
	}
	SetNextSequence( wk, OEKAKI_MODE_NEWMEMBER_WAIT );

	Snd_SePlay(SEQ_SE_DP_BUTTON9);

	// �摜�]����ԂɂȂ�����P�x�_�E��
	G2_SetBlendBrightness(  GX_BLEND_PLANEMASK_BG1|
							GX_BLEND_PLANEMASK_BG2|
							GX_BLEND_PLANEMASK_BG3|
							GX_BLEND_PLANEMASK_OBJ
								,  -6);

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	
	return seq;

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
static int Oekaki_NewMemberWait( OEKAKI_WORK *wk, int seq )
{
//	if( EndMessageWait( wk->MsgIndex ) ){
//		// ��b�E�C���h�E�\���҂��͍s�����A�摜�f�[�^��M�̕����������͂��Ȃ̂ł��������V�[�P���X�����肩����͂�
//	}
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
static int Oekaki_NewMemberEnd( OEKAKI_WORK *wk, int seq )
{
	// �P�x�_�E������
	G2_BlendNone();

	ChangeConnectMax(wk, 1);

	SetNextSequence( wk, OEKAKI_MODE );
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	//�����ς�
	wk->bookJoin = 0;
	OS_Printf("��������\n");
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   ���G�����{�[�h�u��߂�v��I��������
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectPutString( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;
		BOOL rc;

		// YES NO �E�B���h�E�{�^���̕\��
		param.p_bgl		= wk->bgl;
		param.bg_frame	= GF_BGL_FRAME0_M;
		param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
		param.pltt_offs = 8;
		param.x			= OEKAKI_YESNO_BUTTON_X; /*25*/
		param.y			= OEKAKI_YESNO_BUTTON_Y; /* 6*/

		rc = OekakiInitYesNoWin(wk, &param);
		GF_ASSERT(rc);

		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_WAIT );
	}
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
static int Oekaki_EndSelectWait( OEKAKI_WORK *wk, int seq )
{
	int result;

	// �둗�M��h��
	wk->MyTouchResult.size = 0;

	if(wk->AllTouchResult[0].banFlag==OEKAKI_BAN_ON && CommGetCurrentID()!=0){
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

		if(FakeEndYesNoSelect(wk)){
			// �e�@�ɋ֎~����Ă���Ƃ��͂r�d�̂�
			Snd_SePlay(OEKAKI_BS_SE);
		}

		return seq;
	}

	if(CommGetCurrentID() == 0 && wk->ridatu_bit != 0){
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}
	
	if(MyStatusGetNum() != CommGetConnectNum()){
		//��v���Ă��Ȃ��Ȃ�u��߂�v�����Ȃ�(�q���ʂ邱���͐e�����X�V����Ȃ�shareNum�͌��Ȃ�)
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}

	result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//��߂܂����H
	case TOUCH_SW_RET_YES:						//�͂�
		if(CommGetCurrentID()==0){		
			SetNextSequence( wk, OEKAKI_MODE_END_SELECT_PARENT );
			EndMessagePrint( wk, msg_oekaki_05, 1 );		// ���[�_�[����߂�Ɓc
		}else{
			COMM_OEKAKI_END_CHILD_WORK coec;
			
			MI_CpuClear8(&coec, sizeof(COMM_OEKAKI_END_CHILD_WORK));
			coec.request = COEC_REQ_RIDATU_CHECK;
			coec.ridatu_id = CommGetCurrentID();
			
			wk->status_end = TRUE;
			wk->ridatu_wait = 0;

//			SetNextSequence( wk, OEKAKI_MODE_END_CHILD );
			SetNextSequence( wk, OEKAKI_MODE_END_SELECT_ANSWER_WAIT );
			CommSendData( CO_OEKAKI_END_CHILD, &coec, sizeof(COMM_OEKAKI_END_CHILD_WORK) );
			BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		}
		OekakiResetYesNoWin(wk);

		//���������ĕ`��
		GF_BGL_BmpWinOn( &wk->OekakiBoard );
	
		break;
	case TOUCH_SW_RET_NO:						//������
		SetNextSequence( wk, OEKAKI_MODE );
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		OekakiResetYesNoWin(wk);

		//���������ĕ`��
		GF_BGL_BmpWinOn( &wk->OekakiBoard );
		
		// �e�@�͐ڑ����ۂ�����
		if(CommGetCurrentID()==0){
//			CommStateSetEntryChildEnable(TRUE);
			CommStateSetLimitNum(CommGetConnectNum()+1);
			wk->banFlag = OEKAKI_BAN_OFF;
		}

		break;
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
static int Oekaki_EndSelectAnswerWait( OEKAKI_WORK *wk, int seq )
{
	// �둗�M��h��
	wk->MyTouchResult.size = 0;
	
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
static int Oekaki_EndSelectAnswerOK( OEKAKI_WORK *wk, int seq )
{
	// �둗�M��h��
	wk->MyTouchResult.size = 0;

	if((wk->oya_share_num != CommGetConnectNum())
			|| (wk->oya_share_num != MyStatusGetNum())){
		OS_TPrintf("share_nuM = %d, Comm = %d, My = %d, Bit = %d\n", wk->oya_share_num, CommGetConnectNum(), MyStatusGetNum(), WH_GetBitmap());
		wk->ridatu_wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_ANSWER_NG );
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}
	
	wk->ridatu_wait++;
	OS_TPrintf("ridatu_wait = %d\n", wk->ridatu_wait);
	if(wk->ridatu_wait > 30){
		COMM_OEKAKI_END_CHILD_WORK coec;
		
		MI_CpuClear8(&coec, sizeof(COMM_OEKAKI_END_CHILD_WORK));
		coec.request = COEC_REQ_RIDATU_EXE;
		coec.ridatu_id = CommGetCurrentID();

		CommSendData( CO_OEKAKI_END_CHILD, &coec, sizeof(COMM_OEKAKI_END_CHILD_WORK) );

		wk->ridatu_wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD );
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
static int Oekaki_EndSelectAnswerNG( OEKAKI_WORK *wk, int seq )
{
	// �둗�M��h��
	wk->MyTouchResult.size = 0;

	wk->status_end = FALSE;
	SetNextSequence( wk, OEKAKI_MODE );
	EndButtonAppearChange( wk->ButtonActWork, FALSE );
	
	OS_TPrintf("==========���E�����L�����Z���I===========\n");
	
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}

// OEKAKI_MODE_END_CHILD
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
static int 	Oekaki_EndChild( OEKAKI_WORK *wk, int seq )
{
	u8 temp;
	
	// ������������߂܂���
	EndMessagePrint( wk, msg_oekaki_07, 1 );	

	// �I���ʒB
//	CommSendData( CO_OEKAKI_END_CHILD, &temp, 1 );

	SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT );

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
}
				

// OEKAKI_MODE_END_CHILD_WAIT
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
static int 	Oekaki_EndChildWait( OEKAKI_WORK *wk, int seq )
{			

	if( EndMessageWait( wk->MsgIndex ) ){
		wk->wait = 0;
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT2 );
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}

//------------------------------------------------------------------
/**
 * $brief   ���b�Z�[�W�\���I���㏭���҂�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int 			
 */
//------------------------------------------------------------------
static int 	Oekaki_EndChildWait2( OEKAKI_WORK *wk, int seq )
{			

	if( ++wk->wait > OEKAKI_MESSAGE_END_WAIT ){
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		seq = SEQ_OUT;						//�I���V�[�P���X��
	}

	EndSequenceCommonFunc( wk );			//�I���I�����̋��ʏ���
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
static int Oekaki_EndSelectParent( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;
		BOOL rc;

		// YES NO �E�B���h�E�{�^���̕\��
		param.p_bgl		= wk->bgl;
		param.bg_frame	= GF_BGL_FRAME0_M;
		param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
		param.pltt_offs = 8;
		param.x			= 25;
		param.y			= 6;

		rc = OekakiInitYesNoWin(wk, &param);
		GF_ASSERT(rc);

		SetNextSequence( wk, OEKAKI_MODE_END_SELECT_PARENT_WAIT );

	}

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
static int Oekaki_EndSelectParentWait( OEKAKI_WORK *wk, int seq )
{
	int result = TOUCH_SW_Main( wk->TouchSubWindowSys );

	if(wk->shareNum != MyStatusGetNum()	//��v���Ă��Ȃ��Ȃ�u��߂�v�����Ȃ�
			|| wk->ridatu_bit != 0){	//���E���悤�Ƃ��Ă���q������Ȃ狖���Ȃ�
		EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
		return seq;
	}

	switch(result){				//��߂܂����H
	case TOUCH_SW_RET_YES:						//�͂�
		SetNextSequence( wk, OEKAKI_MODE_FORCE_END );
		CommSendData_ServerSide( CO_OEKAKI_END, NULL, 0 );	//�I���ʒm
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// �e�@�i�����j�̖��O��WORDSET
		seq = SEQ_LEAVE;
		OS_Printf("OEKAKI_MODE_FORCE_END�ɂ�������\n");
		OekakiResetYesNoWin(wk);
		break;
	case TOUCH_SW_RET_NO:						//������
		SetNextSequence( wk, OEKAKI_MODE );
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		OekakiResetYesNoWin(wk);

		// �e�@�͐ڑ����ۂ�����
		if(CommGetCurrentID()==0){
//			CommStateSetEntryChildEnable(TRUE);
			CommStateSetLimitNum(CommGetConnectNum()+1);
			wk->banFlag = OEKAKI_BAN_OFF;
		}
		break;
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
static int Oekaki_ForceEnd( OEKAKI_WORK *wk, int seq )
{
	WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(0) );	// �e�@�i�����j�̖��O��WORDSET
	
	EndMessagePrint( wk, msg_oekaki_04, 1 );				// ���[�_�[���������̂ŉ��U���܂��B
	SetNextSequence( wk, OEKAKI_MODE_FORCE_END_WAIT );

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
static int Oekaki_ForceEndWait( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_FORCE_END_SYNCHRONIZE );
		CommTimingSyncStart(OEKAKI_SYNCHRONIZE_END);
		OS_Printf("�����J�n\n");
		
	}

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
static int Oekaki_ForceEndSynchronize( OEKAKI_WORK *wk, int seq )
{
	if(CommIsTimingSync(OEKAKI_SYNCHRONIZE_END) || CommGetConnectNum() == 1){
		OS_Printf("�I������������  seq = %d\n", seq);
		OS_Printf("�R�l�N�g�l��%d\n",CommGetConnectNum());
//		wk->seq = OEKAKI_MODE_FORCE_END_WAIT_NOP;
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_HOLEOUT, WIPE_TYPE_HOLEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		seq = SEQ_OUT;						//�I���V�[�P���X��
	}
	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;
	
}

//------------------------------------------------------------------
/**
 * @brief   �������Ȃ�
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ForceEndWaitNop( OEKAKI_WORK *wk, int seq )
{
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
static int Oekaki_EndParentOnly( OEKAKI_WORK *wk, int seq )
{
	EndMessagePrint( wk, msg_oekaki_06, 1 );				// ���[�_�[���������̂ŉ��U���܂��B
	SetNextSequence( wk, OEKAKI_MODE_END_PARENT_ONLY_WAIT );

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
static int Oekaki_EndParentOnlyWait( OEKAKI_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_END_CHILD_WAIT2 );
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
static int Oekaki_LogoutChildMes( OEKAKI_WORK *wk, int seq )
{
	// ���������񂪂�����܂���
	if( wk->MsgIndex != 0xff && EndMessageWait( wk->MsgIndex ) == 0){
		//�\�����̃��b�Z�[�W������ꍇ�͋�����~
		GF_STR_PrintForceStop(wk->MsgIndex);
	}

	EndMessagePrint( wk, msg_oekaki_03, 1 );	
	SetNextSequence( wk, OEKAKI_MODE_LOGOUT_CHILD_WAIT );
	Snd_SePlay(SEQ_SE_DP_BUTTON9);

	// �ڑ��\�l������U���݂̐ڑ��l���ɗ��Ƃ�
	if(CommGetCurrentID()==0){
		ChangeConnectMax( wk, 0 );
	}
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
static int Oekaki_LogoutChildMesWait( OEKAKI_WORK *wk, int seq )
{
	// �ڑ��l�����P���邩�`�F�b�N
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	if( EndMessageWait( wk->MsgIndex ) ){
		SetNextSequence( wk, OEKAKI_MODE_LOGOUT_CHILD_CLOSE );
		wk->wait = 0;
	}

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
static int 	Oekaki_LogoutChildClose( OEKAKI_WORK *wk, int seq )
{			
	// �ڑ��l�����P����܂ł͑҂�
	if(wk->err_num != 0 && CommGetConnectNum() != wk->err_num){
		wk->err_num = 0;
	}

	if( ++wk->wait > OEKAKI_MESSAGE_END_WAIT && wk->err_num == 0 ){
		EndMessageWindowOff( wk );
		SetNextSequence( wk, OEKAKI_MODE );
		if(CommGetCurrentID() == 0){
			wk->banFlag = OEKAKI_BAN_OFF;
			ChangeConnectMax(wk, 1);
		}
	}

	EndSequenceCommonFunc( wk );			//�I���I�����̋��ʏ���
	return seq;
	
}




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
void OekakiBoard_MainSeqForceChange( OEKAKI_WORK *wk, int seq, u8 id  )
{
	switch(seq){
	case OEKAKI_MODE_NEWMEMBER:	
		if(wk->seq==OEKAKI_MODE_END_SELECT_WAIT || wk->seq==OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			OekakiResetYesNoWin(wk);
//			CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);
		}
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		// �w��̎q�@�̖��O��WORDSET�ɓo�^�i���E�E������)
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		wk->newMemberId = id;
		wk->ridatu_bit = 0;
		OS_Printf("�V�����l��ID %d\n",id);
		break;
	case OEKAKI_MODE_NEWMEMBER_END:
		EndMessageWindowOff( wk );
		break;
	case OEKAKI_MODE_LOGOUT_CHILD:
		if(wk->status_end == TRUE){
			return;	//�������g�����E������
		}
		WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
		if(id==CommGetCurrentID()){
			// ���������E����q�@�������ꍇ�́u�q�@�����Ȃ��Ȃ���v�Ƃ͌���Ȃ�
			return;
		}

		if(CommGetCurrentID() == 0){
			wk->ridatu_bit &= 0xffff ^ id;
		}
		if(wk->seq==OEKAKI_MODE_END_SELECT_WAIT || wk->seq==OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			OekakiResetYesNoWin(wk);
//			CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);

			//���������ĕ`��
			GF_BGL_BmpWinOn( &wk->OekakiBoard );
		}
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		break;
	case OEKAKI_MODE_FORCE_END:
		break;
	case OEKAKI_MODE_END_SELECT_ANSWER_OK:
		break;
	case OEKAKI_MODE_END_SELECT_ANSWER_NG:
		break;
	default:
		GF_ASSERT( "�w��ȊO�̃V�[�P���X�`�F���W������" );
		return;
	}
	SetNextSequence( wk, seq );

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
void OekakiBoard_MainSeqCheckChange( OEKAKI_WORK *wk, int seq, u8 id  )
{
	// �ʏ��ԂȂ�
	if(wk->seq == OEKAKI_MODE){
		OS_Printf("�q�@%d�̖��O��o�^\n",id);
		switch(seq){
		case OEKAKI_MODE_LOGOUT_CHILD:
			WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(id) );	
			if(id==CommGetCurrentID()){
				// ���������E����q�@�������ꍇ�́u�q�@�����Ȃ��Ȃ���v�Ƃ͌���Ȃ�
				return;
			}
			if(CommGetCurrentID() == 0){
				wk->ridatu_bit &= 0xffff ^ id;
			}
			SetNextSequence( wk, seq );
			break;
		
		default:
			GF_ASSERT( 0&&"�w��ȊO�̃V�[�P���X�`�F���W������" );
			return;
		}


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
//11520
//---------------------------------------------------------
// �u���V�p�^�[��
//---------------------------------------------------------

// �ǂ����Ă��p���b�g�f�[�^��3bit�ɏk�߂Ă��܂������̂ŁA�����F��8�ɂ���
// �F�w�莩�̂�0-7�ɓ��ĂĂ���B0�͓����F����BD�ʂ����ɂ��č���������悤�ɂ��Ă���

// BMP�f�[�^�͍Œቡ8dot���K�v�Ȃ̂ŁA4x4�̃h�b�g�f�[�^����肽������
// �Q�o�C�g���ƂɎQ�Ƃ���Ȃ��f�[�^�������Q�o�C�g�K�v
static const u8 oekaki_brush[3][8][24]={

{	/*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x11,  0x00,0x00,  0x00,0x11, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x22,  0x00,0x00,  0x00,0x22, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x33,  0x00,0x00,  0x00,0x33, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x44,  0x00,0x00,  0x00,0x44, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x55,  0x00,0x00,  0x00,0x55, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x66,  0x00,0x00,  0x00,0x66, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x77,  0x00,0x00,  0x00,0x77, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,  0x00,0x88,  0x00,0x00,  0x00,0x88, 0x00,0x00,  0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
},
{	/*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x00,0x00, 0x00,0x00, 0x00,0x11, 0x00,0x00,  0x10,0x11,  0x01,0x00,  0x10,0x11, 0x01,0x00,  0x00,0x11, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x22, 0x00,0x00,  0x20,0x22,  0x02,0x00,  0x20,0x22, 0x02,0x00,  0x00,0x22, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x33, 0x00,0x00,  0x30,0x33,  0x03,0x00,  0x30,0x33, 0x03,0x00,  0x00,0x33, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x44, 0x00,0x00,  0x40,0x44,  0x04,0x00,  0x40,0x44, 0x04,0x00,  0x00,0x44, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x55, 0x00,0x00,  0x50,0x55,  0x05,0x00,  0x50,0x55, 0x05,0x00,  0x00,0x55, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x66, 0x00,0x00,  0x60,0x66,  0x06,0x00,  0x60,0x66, 0x06,0x00,  0x00,0x66, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x77, 0x00,0x00,  0x70,0x77,  0x07,0x00,  0x70,0x77, 0x07,0x00,  0x00,0x77, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
	{0x00,0x00, 0x00,0x00, 0x00,0x88, 0x00,0x00,  0x80,0x88,  0x08,0x00,  0x80,0x88, 0x08,0x00,  0x00,0x88, 0x00,0x00, 0x00,0x00, 0x00,0x00,},
},                                                                     
{   /*  0  */              /*  1  */               /*  2  */              /*  3  */
	{0x10,0x11, 0x01,0x00, 0x11,0x11, 0x11,0x00,  0x11,0x11,  0x11,0x00,  0x11,0x11, 0x11,0x00,  0x11,0x11, 0x11,0x00, 0x10,0x11, 0x01,0x00,},
	{0x20,0x22, 0x02,0x00, 0x22,0x22, 0x22,0x00,  0x22,0x22,  0x22,0x00,  0x22,0x22, 0x22,0x00,  0x22,0x22, 0x22,0x00, 0x20,0x22, 0x02,0x00,},
	{0x30,0x33, 0x03,0x00, 0x33,0x33, 0x33,0x00,  0x33,0x33,  0x33,0x00,  0x33,0x33, 0x33,0x00,  0x33,0x33, 0x33,0x00, 0x30,0x33, 0x03,0x00,},
	{0x40,0x44, 0x04,0x00, 0x44,0x44, 0x44,0x00,  0x44,0x44,  0x44,0x00,  0x44,0x44, 0x44,0x00,  0x44,0x44, 0x44,0x00, 0x40,0x44, 0x04,0x00,},
	{0x50,0x55, 0x05,0x00, 0x55,0x55, 0x55,0x00,  0x55,0x55,  0x55,0x00,  0x55,0x55, 0x55,0x00,  0x55,0x55, 0x55,0x00, 0x50,0x55, 0x05,0x00,},
	{0x60,0x66, 0x06,0x00, 0x66,0x66, 0x66,0x00,  0x66,0x66,  0x66,0x00,  0x66,0x66, 0x66,0x00,  0x66,0x66, 0x66,0x00, 0x60,0x66, 0x06,0x00,},
	{0x70,0x77, 0x07,0x00, 0x77,0x77, 0x77,0x00,  0x77,0x77,  0x77,0x00,  0x77,0x77, 0x77,0x00,  0x77,0x77, 0x77,0x00, 0x70,0x77, 0x07,0x00,},
	{0x80,0x88, 0x08,0x00, 0x88,0x88, 0x88,0x00,  0x88,0x88,  0x88,0x00,  0x88,0x88, 0x88,0x00,  0x88,0x88, 0x88,0x00, 0x80,0x88, 0x08,0x00,},
},
};

/*


















*/



//==============================================================================
/**
 * @brief   �`��J�n�ʒu���}�C�i�X�����ɂ����Ă��`��ł���BmpWinPrint���b�p�[
 * @retval  none		
 */
//==============================================================================
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy )
{
	// X�`��J�n�|�C���g���}�C�i�X��
	if(win_x < 0){
		int diff;
		diff = win_x*-1;
		if(diff>win_dx){	// ���̃}�C�i�X���͓]�����𒴂��ĂȂ���
			diff = win_dx;	// �����Ă���]�����Ɠ����ɂ���
		}

		// �]���Q�ƊJ�n�|�C���g�ƁA�]����������
		win_x   = 0;
		src_x  += diff;
		src_dx -= diff;
		win_dx -= diff;
	}

	// Y�`��J�n�|�C���g���}�C�i�X��
	if(win_y < 0){
		int diff;
		diff = win_y*-1;
		if(diff>win_dy){	// ���̃}�C�i�X���͓]�����𒴂��ĂȂ���
			diff = win_dy;	// �����Ă���]�����Ɠ����ɂ���
		}

		// �]���Q�ƊJ�n�|�C���g�ƁA�]����������
		win_y   = 0;
		src_y  += diff;
		src_dy -= diff;
		win_dy -= diff;
	}

	GF_BGL_BmpWinPrint( win, src,	src_x, src_y, src_dx, src_dy, win_x, win_y, win_dx, win_dy );
}


#define POINT_W	( 6 )
#define POINT_H	( 6 )
//------------------------------------------------------------------
/**
 * $brief   ���C���`��
 *
 * @param   win		
 * @param   brush		
 * @param   px		
 * @param   py		
 * @param   sx		
 * @param   sy		
 * @param   count		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawPoint_to_Line( 
	GF_BGL_BMPWIN *win, 
	const u8 *brush, 
	int px, int py, int *sx, int *sy, 
	int count, int flag )
{
	int dx, dy, s, step;
	int x1 = *sx;
	int y1 = *sy;
	int x2 = px;
	int y2 = py;

	// ����͌��_�ۑ��̂�
	if(count==0 && flag == 0){
		*sx = px;		*sy = py;
		return;
	}
	

	dx = MATH_IAbs(x2 - x1);  dy = MATH_IAbs(y2 - y1);
	if (dx > dy) {
		if (x1 > x2) {
			step = (y1 > y2) ? 1 : -1;
			s = x1;  x1 = x2;  x2 = s;  y1 = y2;
		} else step = (y1 < y2) ? 1: -1;
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		s = dx >> 1;
		while (++x1 <= x2) {
			if ((s -= dy) < 0) {
				s += dx;  y1 += step;
			};
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		}
	} else {
		if (y1 > y2) {
			step = (x1 > x2) ? 1 : -1;
			s = y1;  y1 = y2;  y2 = s;  x1 = x2;
		} else step = (x1 < x2) ? 1 : -1;
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		s = dy >> 1;
		while (++y1 <= y2) {
			if ((s -= dx) < 0) {
				s += dy;  x1 += step;
			}
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, POINT_W, POINT_H, x1, y1, POINT_W, POINT_H );
		}
	}
	
	
	*sx = px;			*sy = py;

}

static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock )
{
	int i;
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		stock[i].size = all[i].size;
		if(all[i].size!=0){
			stock[i].x = all[i].x[all[i].size-1];
			stock[i].y = all[i].y[all[i].size-1];
		}
	}
}


static int debug_count;
//------------------------------------------------------------------
/**
 * $brief  �ʐM�Ŏ�M�����^�b�`�p�l���̌��ʃf�[�^�����ɕ`�悷��
 *
 * @param   win		
 * @param   all		
 * @param   draw	��������ōs����CGX�ύX��]�����邩�H(0:���Ȃ�	1:����j
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw )
{
	int px,py,i,r,flag=0, sx, sy;

//	OS_Printf("id0=%d,id1=%d,id2=%d,id3=%d,id4=%d\n",all[0].size,all[1].size,all[2].size,all[3].size,all[4].size);

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(all[i].size!=0){
			if(old[i].size){
				sx = old[i].x-9;
				sy = old[i].y-17;
			}
			for(r=0;r<all[i].size;r++){
				px = all[i].x[r] - 9;
				py = all[i].y[r] - 17;
				// BG1�ʗpBMP�i���G�����摜�j�E�C���h�E�m��
//				GF_BGL_BmpWinPrint( win, (void*)oekaki_brush[all[i].brush],	0, 0, 4, 4, px, py, 4, 4 );
				DrawPoint_to_Line(win, oekaki_brush[all[i].brush][all[i].color], px, py, &sx, &sy, r, old[i].size);
				flag = 1;
			}
			
		}
	}
	if(flag && draw){
		
//		OS_Printf("write board %d times\n",debug_count++);
		GF_BGL_BmpWinOn( win );
	}
	
	// ����̍ŏI���W�̃o�b�N�A�b�v�����   
    Stock_OldTouch(all, old);
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		all[i].size = 0;		// ��x�`�悵������W���͎̂Ă�
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   �ʐM�f�[�^����J�[�\���ʒu���ړ�������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MoveCommCursor( OEKAKI_WORK *wk )
{
	int i;
	TOUCH_INFO *all = wk->AllTouchResult;
	
	// ���W�f�[�^�������Ă��鎞�̓J�[�\�����W�𔽉f������
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(i!=CommGetCurrentID()){		// �����̃J�[�\���̓^�b�`�p�l�����璼�ڂƂ�
			if(all[i].size!=0 && CommInfoGetMyStatus(i)!=NULL){
				CLACT_SetDrawFlag( wk->MainActWork[i], 1 );
				SetCursor_Pos( wk->MainActWork[i], all[i].x[all[i].size-1],  all[i].y[all[i].size-1]);
			}else{
				CLACT_SetDrawFlag( wk->MainActWork[i], 0 );
			}
		}
	}
	
}
//------------------------------------------------------------------
/**
 * $brief   �f�o�b�O�p�Ɏ����Ŏ擾����������M�o�b�t�@�ɃR�s�[����
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void DebugTouchDataTrans( OEKAKI_WORK *wk )
{
	wk->AllTouchResult[0] = wk->MyTouchResult;
}


//------------------------------------------------------------------
/**
 * �J�[�\���̃p���b�g�ύX�i�_�Łj
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

	*CursorCol+=20;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, ( 12 )*2, 2);
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
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return result;
}


//------------------------------------------------------------------
/**
 * $brief   �I�����C���󋵂��m�F���ď��ʂɖ��O��\������
 *
 * @param   win		
 * @param   frame		
 * @param   color		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, OEKAKI_WORK *wk )
{
	int i,id = CommGetCurrentID();
	int num;

	// ���O�擾�̏󋵂ɕω��������ꍇ�͏��������Ȃ�
	if(!MyStatusCheck(wk)){
		return;
	}

	// ���O�C���󋵂ɉ����ď��ʂ̖���ON�EOFF����
	for(i=0;i<5;i++){
		if(wk->TrainerStatus[i][0]==NULL){
			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
		}else{
			CLACT_SetDrawFlag( wk->SubActWork[i], 1 );
		}
	}

	// ���ꂼ��̕����p�l���̔w�i�F�ŃN���A
	for(i=0;i<5;i++){
		GF_BGL_BmpWinFill( &win[i], 0, 0, 0, OEKAKI_NAME_BMP_W*8, OEKAKI_NAME_BMP_H*8 );
	}

	// �`��
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][0]!=NULL){
			MyStatus_CopyNameString( wk->TrainerStatus[i][0], wk->TrainerName[i] );
			if(id==i){
				GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(FBMP_COL_RED,FBMP_COL_RED_SDW,15),NULL);
			}else{
				GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, color,NULL);
			}
		}
		GF_BGL_BmpWinOn( &win[i] );
	}
	OS_Printf("���O�����������܂���\n");

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
static int ConnectCheck( OEKAKI_WORK *wk )
{
	int i,result=0;
	MYSTATUS *status;
	STRCODE  *namecode;

	// �ڑ��`�F�b�N
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->ConnectCheck[i][0] = wk->ConnectCheck[i][1];

		wk->ConnectCheck[i][0] = CommIsConnect(i);

	}

	// �ڑ��������疼�O�𔽉f������
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->ConnectCheck[i][0]){				// �ڑ����Ă��邩�H

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
static void LineDataSendRecv( OEKAKI_WORK *wk )
{
	if( CommGetCurrentID()==0 ){
		// �e�@�͎����̃^�b�`�p�l������ǉ����đ��M����
        if(CommIsEmptyQueue_ServerSize()){
			wk->MyTouchResult.banFlag    = wk->banFlag;
			wk->ParentTouchResult[0] = wk->MyTouchResult;
			CommSendData_ServerSide( CO_OEKAKI_LINEPOSSERVER, wk->ParentTouchResult, COMM_SEND_5TH_PACKET_MAX*OEKAKI_MEMBER_MAX );
		}
	}else{
        if(CommIsEmptyQueue()){
			// �q�@�͎����̃^�b�`�p�l������e�@�ɑ��M����
			CommSendData( CO_OEKAKI_LINEPOS, &wk->MyTouchResult, COMM_SEND_5TH_PACKET_MAX );
		}
	}
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
	for(result=0,i=0;i<OEKAKI_MEMBER_MAX;i++){
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
int OekakiBoard_MyStatusGetNum(void)
{
	return MyStatusGetNum();
}

//------------------------------------------------------------------
/**
 * $brief   MYSTATUS�̎擾�󋵂ɕω������������H
 *
 * @param   wk		
 *
 * @retval  int		��������1,  �����ꍇ��0
 */
//------------------------------------------------------------------
static int MyStatusCheck( OEKAKI_WORK *wk )
{
	int i,result=0;
	// �ڑ��������疼�O�𔽉f������
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerStatus[i][1] = wk->TrainerStatus[i][0];
		wk->TrainerStatus[i][0] = CommInfoGetMyStatus(i);
	}

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(wk->TrainerStatus[i][1] != wk->TrainerStatus[i][0]){
			result = 1;
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
static void EndMessagePrint( OEKAKI_WORK *wk, int msgno, int wait )
{
	// ������擾
	STRBUF *tempbuf;
	
	tempbuf = STRBUF_Create(TALK_MESSAGE_BUF_NUM,HEAPID_OEKAKI);
	MSGMAN_GetString(  wk->MsgManager, msgno, tempbuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	STRBUF_Delete(tempbuf);

	// ��b�E�C���h�E�g�`��
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, 1, FLD_MESFRAME_PAL );


	// ���b�Z�[�W�X�s�[�h���w��
	if(wait==0){
		wait = MSG_ALLPUT;
	}

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, wait, NULL);
	if(wait == MSG_ALLPUT){
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
static void EndMessageWindowOff( OEKAKI_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
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
static void ChangeConnectMax( OEKAKI_WORK *wk, int plus )
{
	if(CommGetCurrentID()==0){
		int num = CommGetConnectNum()+plus;
		if(num>5){
			num = 5;
		}
		CommStateSetLimitNum(num);
		OS_Printf("�ڑ��l���� %d�l�ɕύX\n",num);
	}

}

//------------------------------------------------------------------
/**
 * @brief  �ڑ��l�����Ď����Đ����ς��� 
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ConnectNumControl( OEKAKI_WORK *wk )
{
	int num;
	// �r�[�R��������������
	num = MyStatusGetNum();

	switch(num){
	case 1:
		if(wk->seq<=OEKAKI_MODE_END_SELECT_PARENT_WAIT){
			if (WH_GetBitmap() != 1){
				OS_Printf("��l�ł͂Ȃ��Ȃ�܂����B\n");
				OS_Printf("bit:%d\n",WH_GetBitmap());
				wk->ireagalJoin = 1;
			}
			OS_Printf("OEKAKI_MODE_END_PARENT_ONLY�ɂ�������\n");
//			wk->seq = OEKAKI_MODE_END_PARENT_ONLY;
			wk->next_seq = OEKAKI_MODE_END_PARENT_ONLY;	//�\��
			OS_Printf("�ڑ��������P�ɂ���");
   	    	CommStateSetLimitNum(1);
			// ��߂�I�𒆂������狭�����Z�b�g
			if(wk->yesno_flag){
				OekakiResetYesNoWin(wk);
				CLACT_AnmChg(wk->ButtonActWork[8], pal_button_oam_table[8][2]);
			}
			return SEQ_LEAVE;
		}
		break;
	case 2:case 3:case 4:
		// �܂�������
		Union_BeaconChange( UNION_PARENT_MODE_OEKAKI_FREE );

		// �ڑ��l�����������ꍇ�͐ڑ��ő�l�������炷
		if(num<wk->connectBackup){
			if(wk->banFlag==OEKAKI_BAN_ON){
				ChangeConnectMax( wk, 0 );
			}else{
				ChangeConnectMax( wk, 1 );
			}
		}
		break;
	case 5:
		// �����ς��ł�
		Union_BeaconChange( UNION_PARENT_MODE_OEKAKINOW );
		break;
	}

	// �摜���L�l�����������Ƃ��͍X�V
	if(num<wk->connectBackup){
		wk->shareNum = CommGetConnectNum();
		wk->shareBit = WH_GetBitmap();
		OS_TPrintf("�ڑ��l�����������̂�shareNum��%d�l�ɕύX\n", CommGetConnectNum());
		/*�������t���O�������Ă����ԂŁA�l����������*/
		if(wk->bookJoin){/*�����\��r�b�g�Ɣ�r���A���ꂪ�����Ă����ꍇ�́A�����҂��d����؂����Ƃ݂Ȃ�*/
			if (!(wk->shareBit&wk->joinBit)){
				//���~�b�g�����Đݒ�
				ChangeConnectMax( wk, 1 );
				//���E����
				wk->banFlag = OEKAKI_BAN_OFF;
				//�����\��L�����Z��
				wk->bookJoin = 0;
				wk->joinBit = 0;
				OS_Printf("�����L�����Z������܂���\n");
			}
		}
	}

	// �ڑ��l����ۑ�
	wk->connectBackup = MyStatusGetNum();

	// �ʐM�ڑ��l�����摜���L�l�����������Ȃ����ꍇ�͗��E�֎~�t���O�𗧂Ă�
	if(wk->shareNum < CommGetConnectNum()){
		OS_Printf("ban_flag_on:%d,%d\n",wk->shareNum, CommGetConnectNum());
		OS_Printf("�����\��\n");
		wk->banFlag = OEKAKI_BAN_ON;
		//���������҂���
		wk->bookJoin = 1;
		//�������悤�Ƃ��Ă���l�̃r�b�g���擾
		wk->joinBit = wk->shareBit^WH_GetBitmap();
		GF_ASSERT( (wk->joinBit == 2)||
					(wk->joinBit == 4)||
					(wk->joinBit == 8)||
					(wk->joinBit == 16) );
		
	}

	return SEQ_MAIN;
}


//------------------------------------------------------------------
/**
 * @brief   ���Ɉڍs���������V�[�P���X�ԍ�������
 *
 * @param   wk		
 * @param   nextSequence		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetNextSequence( OEKAKI_WORK *wk, int nextSequence )
{
	wk->next_seq = nextSequence;
}


//------------------------------------------------------------------
/**
 * @brief   wk->seq�̃R���g���[�����s��
 *
 * @param   wk		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void OekakiSequenceControl( OEKAKI_WORK *wk, int proc_seq )
{
	// �V�[�P���X���Ⴄ�Ȃ�
	if(wk->seq!=wk->next_seq){
		// �I���V�[�P���X����Ȃ����Ƃ��m�F����
		if(proc_seq!=SEQ_LEAVE){ 
			wk->seq = wk->next_seq;
		}else{
			// �ꕔ���s�����̃V�[�P���X����Ȃ����Ƃ��m�F����
			if(FuncTable[wk->next_seq].execOn_SeqLeave){
				OS_Printf("now_next:%d,%d\n",wk->seq,wk->next_seq);
				// �V�[�P���X��������
				wk->seq = wk->next_seq;
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���̂͂��E�������E�B���h�E�̍쐬�֐�
 *
 * @param   wk		
 *
 * @retval  BOOL		TRUE�F����	FALSE�F���s 			
 */
//------------------------------------------------------------------
static BOOL OekakiInitYesNoWin(OEKAKI_WORK *wk, TOUCH_SW_PARAM *param)
{
	if(!wk->yesno_flag){
		TOUCH_SW_Init( wk->TouchSubWindowSys, param );
		wk->yesno_flag = 1;
		return TRUE;
	}else{
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���̂͂��E�������E�B���h�E�̏����֐�
 *
 * @param   wk		
 *
 * @retval  void 			
 */
//------------------------------------------------------------------
static void OekakiResetYesNoWin(OEKAKI_WORK *wk)
{
	if(wk->yesno_flag){
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		wk->yesno_flag = 0;
	}
}


//------------------------------------------------------------------
/**
 * @brief   YESNO�{�^�����֎~���Ă���ԁA�R�̌��o���s��
 *
 * @param   wk		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int FakeEndYesNoSelect( OEKAKI_WORK  *wk )
{

	int button=GF_TP_RectHitTrg( fake_yesno_hittbl );
	if( button != RECT_HIT_NONE ){
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���f�[�^�̊i�[����
 *
 * @param   touchResult		
 * @param   tpData		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetTouchpanelData( TOUCH_INFO *touchResult, TP_ONE_DATA *tpData, int brush_color, int brush )
{
	int i,n;

	// �ŏ��ɃT���v�����O���ꂽ�_���i�[
	if(tpData->Size!=0){
		touchResult->x[0] = tpData->TPDataTbl[0].x;
		touchResult->y[0] = tpData->TPDataTbl[0].y;

		// �Ō�ɃT���v�����O���ꂽ�_���i�[
		n = tpData->Size-1;
		touchResult->x[1] = tpData->TPDataTbl[n].x;
		touchResult->y[1] = tpData->TPDataTbl[n].y;
	}

	// �ő�S��T���v�����O�����͂������A����ł����M�f�[�^�͂Q�Ɗi�[����
	if(tpData->Size>=2){
		touchResult->size  = 2;
	}else{
		touchResult->size  = tpData->Size;
	}
	
	// �F�E�傫���ݒ�
	touchResult->color = brush_color;
	touchResult->brush = brush;

}