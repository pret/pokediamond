//============================================================================================
/**
 * @file	mysign.c
 * @bfief	�}�C�T�C���쐬����
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================

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
#include "application/mysign.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "field/fld_bmp.h"
#include "system/fontoam.h"
#include "savedata/savedata.h"
#include "savedata/trainercard_data.h"
#include "savedata/record.h"
#include "savedata/config.h"


#include "mysign_local.h"



//#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"

// SE�p��`
#define OEKAKI_MOVE_SE		(SEQ_SE_DP_SELECT)
#define OEKAKI_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define OEKAKI_BS_SE		(SEQ_SE_DP_SELECT)
// Snd_SePlay( SEQ_SE_DP_KYU01 );

#define BUTTON_NUM			( 1 )

#include "mysign.naix"			// �O���t�B�b�N�A�[�J�C�u��`
//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_OUT,
};



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

/*** �֐��v���g�^�C�v ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( MYSIGN_WORK *wk );
static void FreeWork( MYSIGN_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( MYSIGN_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(MYSIGN_WORK *wk);
static void SetCellActor(MYSIGN_WORK *wk);
static void BmpWinInit(MYSIGN_WORK *wk, PROC* proc);
static void BmpTouchYesnoWin_Init( GF_BGL_INI *ini, GF_BGL_BMPWIN  **yeswin, GF_BGL_BMPWIN  **nowin, int heap  );
static void BmpTouchYesnoWin_End( GF_BGL_BMPWIN  *yeswin, GF_BGL_BMPWIN  *nowin );
static void BmpWinDelete( MYSIGN_WORK *wk );
static void ControlCursor(MYSIGN_WORK *wk);
static void CursorAppearUpDate(MYSIGN_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void NormalTouchFunc(MYSIGN_WORK *wk);
static int  EndTouchFunc( GF_BGL_BMPWIN *TalkWin, GF_BGL_BMPWIN *Yes, GF_BGL_BMPWIN *No );
static int Oekaki_MainNormal( MYSIGN_WORK *wk, int seq );
static void EndSequenceCommonFunc( MYSIGN_WORK *wk );
static int Oekaki_EndSelectPutString( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndSelectWait( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChild( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChildWait( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChildWait2( MYSIGN_WORK *wk, int seq );
static int Oekaki_ReWrite( MYSIGN_WORK *wk, int seq );
static int Oekaki_ReWriteWait( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndParentOnly( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndParentOnlyWait( MYSIGN_WORK *wk, int seq );
static void DrawPoint_to_Line( 	GF_BGL_BMPWIN *win, 	const u8 *brush, 	int px, int py, int *sx, int *sy, 	int count, int flag );
static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock );
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw );
static void MoveCommCursor( MYSIGN_WORK *wk );
static void DebugTouchDataTrans( MYSIGN_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, MYSIGN_WORK *wk );
static void LineDataSendRecv( MYSIGN_WORK *wk );
static void EndMessagePrint( MYSIGN_WORK *wk, int msgno );
static int EndMessageWait( int msg_index );
static void EndMessageWindowOff( MYSIGN_WORK *wk );
static int Oekaki_LogoutChildMes( MYSIGN_WORK *wk, int seq );
static int Oekaki_LogoutChildClose( MYSIGN_WORK *wk, int seq );
static int Oekaki_LogoutChildMesWait( MYSIGN_WORK *wk, int seq );
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no);
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag );
static int Oekaki_ReWriteSelect( MYSIGN_WORK *wk, int seq );
static void TouchYesNoStart( GF_BGL_INI *bgl, TOUCH_SW_SYS* touch_sub_window_sys );
static void Output_SignData( u8 *des, u8 *src );
static void *PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, int y, u8 fnt_index,const   GF_PRINTCOLOR col);
static void BrushCanvas( MYSIGN_WORK *wk);
static void PlayScruchSe( SCRUCH_INFO *scruchInfo );
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy );




static int (*FuncTable[])(MYSIGN_WORK *wk, int seq)={
	NULL,							// MYSIGN_MODE_INIT  = 0, 
	Oekaki_MainNormal,              // MYSIGN_MODE,
	Oekaki_EndSelectPutString,      // MYSIGN_MODE_END_SELECT,
	Oekaki_EndSelectWait,			// MYSIGN_MODE_END_SELECT_WAIT,
	Oekaki_ReWrite,					// MYSIGN_MODE_REWRITE_
	Oekaki_ReWriteWait,				// MYSIGN_MODE_REWRITE_WAIT
	Oekaki_ReWriteSelect,			// MYSIGN_MODE_REWRITE_SELECT
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
PROC_RESULT MySignProc_Init( PROC * proc, int * seq )
{
	MYSIGN_WORK * wk;

	switch(*seq){
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
		
		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OEKAKI, 0x40000 );

		wk = PROC_AllocWork( proc, sizeof(MYSIGN_WORK), HEAPID_OEKAKI );
		memset( wk, 0, sizeof(MYSIGN_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OEKAKI );
		
		// ������}�l�[�W���[����
		wk->WordSet    = WORDSET_Create( HEAPID_OEKAKI );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_oekaki_dat, HEAPID_OEKAKI );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM �o���N�ݒ�
		VramBankSet();
		
		// BGL���W�X�^�ݒ�
		BgInit( wk->bgl );					

///		WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060715 del
///		WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060715 del
		
		// �P�x�ύX�Z�b�g
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		

		// �p�����[�^�擾
		{
			SAVEDATA *sv = (SAVEDATA*)PROC_GetParentWork(proc);
			// �T�C�������o���o�b�t�@�|�C���^�擾
			wk->SignBuf = (u8*)TRCSave_GetSighnDataPtr(TRCSave_GetSaveDataPtr(sv));

			// ���R�[�h�f�[�^�|�C���^�擾
			wk->record  = (RECORD *)SaveData_GetRecord((SAVEDATA*)PROC_GetParentWork(proc));
			wk->config  = (CONFIG *)SaveData_GetConfig((SAVEDATA*)PROC_GetParentWork(proc));
		}

		//BG�O���t�B�b�N�Z�b�g
		BgGraphicSet( wk );

		InitTPSystem();						// �^�b�`�p�l���V�X�e��������
		InitTPNoBuff(1);
  
		// VBlank�֐��Z�b�g
		sys_VBlankFuncChange( VBlankFunc, wk->bgl );	
  
		// �{�^���p�t�H���g��ǂݍ���
		FontProc_LoadFont( FONT_BUTTON, HEAPID_OEKAKI );


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

		// �T�E���h�f�[�^���[�h(�T�C������)(BGM���p��)
		Snd_DataSetByScene( SND_SCENE_SUB_TRCARD, 0, 0 );
	
		// ��ʏo�͂��㉺����ւ���
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

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

PROC_RESULT MySignProc_Main( PROC * proc, int * seq )
{
	MYSIGN_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ���C�v�����҂�
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		// �J�[�\���ړ�

		// �V�[�P���X���̓���
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}

		CursorColTrans(&wk->CursorPal);

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
PROC_RESULT MySignProc_End( PROC * proc, int * seq )
{
	MYSIGN_WORK  *wk    = PROC_GetWork( proc );
	int i;

	// �T�C�����Z�[�u�f�[�^�ɏ����o��
	Output_SignData( wk->SignBuf, wk->OekakiBoard.chrbuf );

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

	// �{�^���p�t�H���g���
	FontProc_UnloadFont( FONT_BUTTON );

	// BGL�폜
	BgExit( wk->bgl );

	// �^�b�`�p�l���V�X�e���I��
	StopTP();							


	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ���[�N���
	FreeWork( wk );

	PROC_FreeWork( proc );				// PROC���[�N�J��

	// ����ւ���Ă����㉺��ʏo�͂����ɖ߂�
	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_OEKAKI );

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
#define END_MESSAGE_BUF_NUM		( 10*2 )
#define  TITLE_MESSAGE_BUF_NUM	( 20*2 )

//------------------------------------------------------------------
/**
 * ���G�������[�N������
 *
 * @param   wk		MYSIGN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( MYSIGN_WORK *wk )
{
	int i;

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_OEKAKI );
		wk->AllTouchResult[i].size = 0;
		wk->OldTouch[i].size = 0;

	}
	// �u��߂�v������o�b�t�@�쐬
	wk->EndString   = STRBUF_Create( END_MESSAGE_BUF_NUM,   HEAPID_OEKAKI );
	wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_OEKAKI );
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM,  HEAPID_OEKAKI );

	// �u���V������
	wk->brush_color  = 0;
	

	wk->seq = MYSIGN_MODE;
	
	// �u��߂�v�擾
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_13, wk->EndString );

	// �g���[�i�[�T�C����������
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_10, wk->TitleString );

	// ����ʃE�C���h�E�V�X�e��������
	wk->TouchSubWindowSys = TOUCH_SW_AllocWork( HEAPID_OEKAKI );

	MI_CpuClearFast( &wk->scruchInfo, sizeof(SCRUCH_INFO));
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
static void FreeWork( MYSIGN_WORK *wk )
{
	int i;

	TOUCH_SW_FreeWork( wk->TouchSubWindowSys );


	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->TitleString  ); 
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
static void BgGraphicSet( MYSIGN_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_MYSIGN_GRA, NARC_mysign_mysign_m_nclr, PALTYPE_MAIN_BG, 0, 16*2*3,  HEAPID_OEKAKI);
	ArcUtil_PalSet(    ARC_MYSIGN_GRA, NARC_mysign_mysign_s_nclr, PALTYPE_SUB_BG,  0, 16*2*2,  HEAPID_OEKAKI);
	
	// ��b�t�H���g�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_OEKAKI );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_OEKAKI );


	// �O�L�����ڂ��N���A����
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_OEKAKI );

	// ���C�����BG2�L�����]��
	ArcUtil_BgCharSet( ARC_MYSIGN_GRA, NARC_mysign_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// ���C�����BG2�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_MYSIGN_GRA, NARC_mysign_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_OEKAKI);



	// �T�u���BG1�L�����]��
	ArcUtil_BgCharSet( ARC_MYSIGN_GRA, NARC_mysign_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// �T�u���BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_MYSIGN_GRA, NARC_mysign_subbg_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_OEKAKI);

	// �T�u��ʉ�b�E�C���h�E�O���t�B�b�N�]��
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->config), HEAPID_OEKAKI );

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
static void InitCellActor(MYSIGN_WORK *wk)
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
	wk->clactSet = CLACT_U_SetEasyInit( 50, &wk->renddata, HEAPID_OEKAKI );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_OEKAKI);
	}


	//---------���ʗp-------------------

	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OEKAKI);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_MYSIGN_GRA, NARC_mysign_mysign_m_obj_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_OEKAKI);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);


	//---------����ʗp-------------------



	//chara�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_OEKAKI);

	//pal�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_MYSIGN_GRA, NARC_mysign_mysign_m_obj_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_OEKAKI);

	//cell�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);

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

static const u16 pal_button_oam_table[BUTTON_NUM][3]={
	{48+12*8*2-2*8, 171+4, 0},
//	{48       , 171+4, 5},
//	{48+12*8*1, 171+4, 7},
};

//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			MYSIGN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(MYSIGN_WORK *wk)
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
#if 0
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
#endif
		

		// ���C����ʃp���b�g�E�u��߂�v�{�^���̓o�^
		for(i=0;i<BUTTON_NUM;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  pal_button_oam_table[i][0]);
			add.mat.y = FX32_ONE * ( pal_button_oam_table[i][1] );
			wk->ButtonActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ButtonActWork[i],1);
			CLACT_AnmChg( wk->ButtonActWork[i], pal_button_oam_table[i][2] );
			CLACT_PaletteNoChg( wk->ButtonActWork[i], 0 );
			if(i==0){
				CLACT_BGPriorityChg( wk->ButtonActWork[i], 2 );
			}

//			CLACT_SetDrawFlag( wk->ButtonActWork[i], 0 );
		}

#if 0
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
#endif		
	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m
	
}


//------------------------------------------------------------------
/**
 * @brief   �n�`�l�p��BmpWin�̃������ɂ̂ݕ������`�悷��
 *
 * @param   win			BMPWIN
 * @param   msg			STRBUF
 * @param   y			BMP���̕`��J�n�x���W
 * @param   fnt_index	�t�H���I�w��
 * @param   col			�J���[�w��
 *
 * @retval  void *		�`�悵�ă������̃g�b�v
 */
//------------------------------------------------------------------
static void *PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, int y, u8 fnt_index,const   GF_PRINTCOLOR col)
{
	int x,length;

	length = FontProc_GetPrintStrWidth( FONT_BUTTON, msg, 0 );
	x      = ((win->sizx*8)-length)/2;

	GF_STR_PrintColor(	win, fnt_index, msg, x, y, MSG_NO_PUT, col,NULL);

	return win->chrbuf;
}


// ���������{�[�hBMP�i����ʁj
#define OEKAKI_BOARD_POSX	 ( 4 )
#define OEKAKI_BOARD_POSY	 ( 9 )


// ���O�\��BMP�i���ʁj
#define OEKAKI_NAME_BMP_W	 ( 10 )
#define OEKAKI_NAME_BMP_H	 (  2 )
#define OEKAKI_NAME_BMP_SIZE (OEKAKI_NAME_BMP_W * OEKAKI_NAME_BMP_H)

#define END_BMP_OFFSET		 (1+OEKAKI_BOARD_W*OEKAKI_BOARD_H)
#define TITLE_BMP_OFFSET     (END_BMP_OFFSET + OEKAKI_END_BMP_W*OEKAKI_END_BMP_H)

// �u��߂�v������BMP�i����ʁj
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 21 )
#define OEKAKI_END_BMP_W	( 8  )
#define OEKAKI_END_BMP_H	( 2  )

// �u�g���[�i�[�T�C�����������I�v
#define TITLE_BMP_X			(  2 )
#define TITLE_BMP_Y			(  2 )
#define TITLE_BMP_W			( 28 )
#define TITLE_BMP_H			(  2 )

// ��b�E�C���h�E�\���ʒu��`
#define OEKAKI_TALK_X		(  2 )
#define OEKAKI_TALK_Y		(  1 )

#define OBJ_VRAM_WORD_OFFSET		( 0 )
#define OBJ_VRAM_WORD_TRANS_SIZE	( 0x20*4*2 )
//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( MYSIGN_WORK *wk, PROC* proc )
{
	// ---------- ���C����� ------------------

	// BG0��BMP�i��b�E�C���h�E�j�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		OEKAKI_TALK_X, OEKAKI_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG1�ʗpBMP�i���G�����摜�j�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->OekakiBoard, GF_BGL_FRAME1_M,
		OEKAKI_BOARD_POSX, OEKAKI_BOARD_POSY, OEKAKI_BOARD_W, OEKAKI_BOARD_H, 1,  1 );
	GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );

	// BG1��BMP�i��߂�j�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_M,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 2,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );
//	GF_STR_PrintColor( &wk->EndWin, FONT_BUTTON, wk->EndString, 0, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x1,0x2,0x3),NULL);

	{
		void *objcharaadr;
		int  i;
		objcharaadr = PrintCGXOnly(&wk->EndWin, wk->EndString, 1, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xe,7,2));

		// BMP�����ŕ`�悵���o�b�t�@��OBJ�ɓ]�����Ĕ��f������
		DC_FlushRange(objcharaadr,0x20*8*2);	
		for(i=0;i<2;i++){						
			FONTOAM_BmpCutOamSize( &wk->EndWin, 4, 2, 4*i, 0,  (char*)wk->TransWork);
			DC_FlushRange(wk->TransWork,OBJ_VRAM_WORD_TRANS_SIZE);	
			GX_LoadOBJ(wk->TransWork, OBJ_VRAM_WORD_OFFSET+i*OBJ_VRAM_WORD_TRANS_SIZE, OBJ_VRAM_WORD_TRANS_SIZE);
		}
	}


	// BG1��BMP�i�g���[�i�[�T�C�����������I�j�E�C���h�E�m�ہE�`��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME1_M,
	TITLE_BMP_X, TITLE_BMP_Y, TITLE_BMP_W, TITLE_BMP_H, 13,  TITLE_BMP_OFFSET );

	{
		int length = FontProc_GetPrintStrWidth( FONT_TALK, wk->TitleString, 0 );
		int x      = (TITLE_BMP_W*8-length)/2;

		GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
		GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, x, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x1,0x2,0x0),NULL);
	}

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

// �͂��E������BMP�i����ʁj
#define YESNO_WIN_FRAME_CHAR	( 1 + TALK_WIN_CGX_SIZ )
#define YESNO_CHARA_OFFSET	(1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY)
#define YESNO_WINDOW_X		( 22   )
#define YESNO_WINDOW_Y1		(  7   )
#define YESNO_WINDOW_Y2		(  7+6 )
#define YESNO_CHARA_W		( 8 )
#define YESNO_CHARA_H		( 4 )

static const BMPWIN_DAT TouchYesNoBmpDat[2]={
	{
		GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y1,
		YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET
	},
	{
		GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y2,
		YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H
		
	}
};




//------------------------------------------------------------------
/**
 * $brief   ����ʁi�^�b�`�p�j�͂��E�������E�C���h�E�\��
 *
 * @param   ini		
 * @param   yeswin		
 * @param   nowin		
 * @param   heap		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpTouchYesnoWin_Init( GF_BGL_INI *ini, GF_BGL_BMPWIN  **yeswin, GF_BGL_BMPWIN  **nowin, int heap  )
{
	MSGDATA_MANAGER * man;
	STRBUF *yes,*no;
	int yespos, nopos;

	// �͂��E������������擾
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, heap );
	yes = MSGMAN_AllocString( man, msg_ev_win_046 );
	no  = MSGMAN_AllocString( man, msg_ev_win_047 );
	MSGMAN_Delete( man );

	// BMPWIN�m��(Alloc)
	*yeswin = GF_BGL_BmpWinAllocGet( heap, 1 );
	*nowin  = GF_BGL_BmpWinAllocGet( heap, 1 );
	
	GF_BGL_BmpWinAddEx( ini, *yeswin, &TouchYesNoBmpDat[0] );
	GF_BGL_BmpWinAddEx( ini, *nowin, &TouchYesNoBmpDat[1] );

	// Window�g�`��
	BmpMenuWinWrite( *yeswin, WINDOW_TRANS_OFF, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL );
	BmpMenuWinWrite( *nowin, WINDOW_TRANS_OFF, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL );

	// BMP�L�����h��Ԃ�
	GF_BGL_BmpWinDataFill( *yeswin, 0x0f0f );
	GF_BGL_BmpWinDataFill( *nowin,  0x0f0f );

	// �͂��E�������Z���^�����O�ʒu�擾
	yespos = FontProc_GetPrintStrWidth( FONT_TALK, yes, 0 );
    nopos  = FontProc_GetPrintStrWidth( FONT_TALK,  no, 0 );
	yespos = (YESNO_CHARA_W*8/2) - yespos/2;
	nopos =  (YESNO_CHARA_W*8/2) - nopos/2;
	
	// �͂��E�������`��
	
	GF_STR_PrintSimple( *yeswin, FONT_TALK,  yes,  yespos, 2*8-12/2, MSG_ALLPUT, NULL);
	GF_STR_PrintSimple( *nowin,  FONT_TALK,   no,  nopos,  2*8-12/2, MSG_ALLPUT, NULL);

	// �͂��E��������������
	STRBUF_Delete(yes);
	STRBUF_Delete(no);
}

//------------------------------------------------------------------
/**
 * $brief   ����ʁi�^�b�`�p�j�͂��E�������E�C���h�E�폜
 *
 * @param   yeswin		
 * @param   nowin		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpTouchYesnoWin_End( GF_BGL_BMPWIN  *yeswin, GF_BGL_BMPWIN  *nowin )
{
	// BMPWIN�\��OFF
	GF_BGL_BmpWinOff( yeswin );
	GF_BGL_BmpWinOff( nowin  );

	// Window�g����
	BmpMenuWinClear( yeswin, WINDOW_TRANS_ON );
	BmpMenuWinClear( nowin,  WINDOW_TRANS_ON );

	// BMPWIN���
	GF_BGL_BmpWinFree( yeswin,1 );
	GF_BGL_BmpWinFree( nowin,1 );
}

//------------------------------------------------------------------
/**
 * $brief   �m�ۂ���BMPWIN�����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( MYSIGN_WORK *wk )
{
	int i;
	
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->OekakiBoard );
	GF_BGL_BmpWinDel( &wk->MsgWin );


}



//------------------------------------------------------------------
/**
 * �J�[�\���ړ�����
 *
 * @param   wk		MYSIGN_WORK*
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void ControlCursor(MYSIGN_WORK *wk)
{
	int move  = 0;
	int arrow = 0;


	// �ړ�������������ύX
	if(move){
		CursorAppearUpDate(wk,arrow);		// �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
	}

}


//------------------------------------------------------------------
/**
 * �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
 * �����̏�ł���΁A�����`�̃J�[�\���A�{�^���̏�ł���Β����`�̃J�[�\��
 * �����̍X�V���s���邱�ƂŁA�T�u��ʂ̒��̃t�H���g�̍X�V���s����
 *
 * @param   wk			MYSIGN_WORK*
 * @param   arrow		�ړ�����
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(MYSIGN_WORK *wk, int arrow)
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

	mat.x = FX32_CONST( x + 8 );
	mat.y = FX32_CONST( y - 10 );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


#define PAL_BUTTON_X	(  0  )
#define PAL_BUTTON_Y	( 150 )
#define PAL_BUTTON_W	( 12*8 )
#define PAL_BUTTON_H	( 5*8 )
#define PAL_BUTTON_RECT ( 12*8 -1 )
#define END_BUTTON_RECT ( 8*8 -1 )

#define PAL_BUTTON0_X	( PAL_BUTTON_X+PAL_BUTTON_W*0 )
#define PAL_BUTTON1_X	( PAL_BUTTON_X+PAL_BUTTON_W*1 )
#define END_BUTTON_X	( PAL_BUTTON_X+PAL_BUTTON_W*2 )


static const RECT_HIT_TBL sub_button_hittbl[]={
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,END_BUTTON_X,END_BUTTON_X+END_BUTTON_RECT},
{RECT_HIT_END,0,0,0},		// �I���f�[�^
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON0_X,PAL_BUTTON0_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON1_X,PAL_BUTTON1_X+PAL_BUTTON_RECT},
};

#define DRAW_AREA_X	(  8*OEKAKI_BOARD_POSX  )
#define DRAW_AREA_Y	(  8*OEKAKI_BOARD_POSY  )
#define DRAW_AREA_W	( OEKAKI_BOARD_W*8 )
#define DRAW_AREA_H	( OEKAKI_BOARD_H*8)

static const RECT_HIT_TBL sub_canvas_touchtbl[]={
	{DRAW_AREA_Y,DRAW_AREA_Y+DRAW_AREA_H,DRAW_AREA_X,DRAW_AREA_X+DRAW_AREA_W},
{RECT_HIT_END,0,0,0},		// �I���f�[�^
};


// ����ʗp�͂��E�����������̃^�b�`����e�[�u��
static const RECT_HIT_TBL end_button_touchtbl[]={
	{ YESNO_WINDOW_Y1*8, (YESNO_WINDOW_Y1+YESNO_CHARA_H)*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{ YESNO_WINDOW_Y2*8, YESNO_WINDOW_Y2*8+YESNO_CHARA_H*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{RECT_HIT_END,0,0,0},		// �I���f�[�^
};



//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ŉ������{�^�����ւ���
 *
 * @param   wk		MYSIGN_WORK�̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NormalTouchFunc(MYSIGN_WORK *wk)
{
	int button=-1,touch;

	// ���͏���

	// �u���V�؂�ւ�
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		if(button==0){
			// �u��߂�v����������E�C���h�E�`��J�n
			if(wk->seq==MYSIGN_MODE){
				EndMessagePrint( wk, msg_oekaki_11 );
				wk->seq = MYSIGN_MODE_END_SELECT;
				EndButtonAppearChange( wk->ButtonActWork, TRUE );
				Snd_SePlay( SEQ_SE_DP_DECIDE );
			}
		}else{
			// �I���{�^������Ȃ��ꍇ�́A�F�ύX
			wk->brush_color = button;
			PalButtonAppearChange( wk->ButtonActWork, button);
		}
	}

	// �J�[�\���ʒu�ύX
	touch = GF_TP_RectHitCont( sub_canvas_touchtbl );

//	CLACT_SetDrawFlag( wk->MainActWork[0], 0 );
	if(touch!=RECT_HIT_NONE){
		// �����̃J�[�\���̓^�b�`�p�l���̍��W�𔽉f������
//		SetCursor_Pos( wk->MainActWork[0], sys.tp_x, sys.tp_y );
		BrushCanvas(wk);
	}

	// �T���v�����O�����擾���Ċi�[
	{
		TP_ONE_DATA	tpData;
		int i;
		if(MainTP( &tpData, TP_BUFFERING_JUST, 1 )==TP_OK){
			for(i=0;i<tpData.Size;i++){
				wk->MyTouchResult.x[i] = tpData.TPDataTbl[i].x;
				wk->MyTouchResult.y[i] = tpData.TPDataTbl[i].y;
			}
			wk->MyTouchResult.size  = tpData.Size;
			wk->MyTouchResult.brush = wk->brush_color;
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
	
	for(i=0;i<BUTTON_NUM;i++){
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
		CLACT_AnmChg( act[0], pal_button_oam_table[0][2]+1 );
	}else{
		CLACT_AnmChg( act[0], pal_button_oam_table[0][2] );
	}
}

//------------------------------------------------------------------
/**
 * $brief   ���������I���̂͂��E�������E�C���h�E�^�b�`����
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int  EndTouchFunc( GF_BGL_BMPWIN *TalkWin, GF_BGL_BMPWIN *Yes, GF_BGL_BMPWIN *No )
{
	int button;
	int result = 0;
	
	// �͂��E�������e�X�g
	button=GF_TP_RectHitTrg( end_button_touchtbl );
	if( button != RECT_HIT_NONE ){
			// �E�C���h�E�N���A
		BmpTalkWinClear( TalkWin, WINDOW_TRANS_ON );
		BmpTouchYesnoWin_End( Yes, No   );
		if(button==0){
			result = 1;
		}else{
			result = 2;
		}
	}
	
	return result;
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
static int Oekaki_MainNormal( MYSIGN_WORK *wk, int seq )
{
	NormalTouchFunc(wk);			//  �^�b�`�p�l������

	NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xc,0xf),wk);

	
	LineDataSendRecv( wk );

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
static void EndSequenceCommonFunc( MYSIGN_WORK *wk )
{
	ControlCursor(wk);		//	DebugOBJPOSGet(wk);
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 0 );
	
}

//------------------------------------------------------------------
/**
 * $brief   YESNO�E�C���h�E�V�X�e���X�^�[�g
 *
 * @param   bgl		
 * @param   touch_sub_window_sys		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void TouchYesNoStart( GF_BGL_INI *bgl, TOUCH_SW_SYS* touch_sub_window_sys )
{
	TOUCH_SW_PARAM param;

	// YES NO �E�B���h�E�{�^���̕\��
	param.p_bgl		= bgl;
	param.bg_frame	= GF_BGL_FRAME0_M;
	param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
	param.pltt_offs = 8;
	param.x			= 25;
	param.y			= 6;

	TOUCH_SW_Init( touch_sub_window_sys, &param );

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
static int Oekaki_EndSelectPutString( MYSIGN_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;

		// YES NO �E�B���h�E�{�^���̕\��
		TouchYesNoStart( wk->bgl, wk->TouchSubWindowSys );
	
		wk->seq = MYSIGN_MODE_END_SELECT_WAIT;
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
static int Oekaki_EndSelectWait( MYSIGN_WORK *wk, int seq )
{
	int result;
	result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//��߂܂����H
	case TOUCH_SW_RET_YES:						//�͂�
		// �X�R�A���Z
		RECORD_Score_Add( wk->record, SCORE_ID_WRITE_SIGN );
		
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		return SEQ_OUT;
		break;
	case TOUCH_SW_RET_NO:						//������
		wk->seq = MYSIGN_MODE_REWRITE;
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		break;
	}

	// �둗�M��h��
	wk->MyTouchResult.size = 0;

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���

	return seq;
}




//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ReWriteSelect( MYSIGN_WORK *wk, int seq )
{
	int result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//�����Ȃ����܂����H
	case TOUCH_SW_RET_YES:						//�͂�
		
		wk->seq = MYSIGN_MODE;
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );

		GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );
		GF_BGL_BmpWinOn( &wk->OekakiBoard );

		break;
	case TOUCH_SW_RET_NO:						//������
		wk->seq = MYSIGN_MODE;
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		break;
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * $brief   �u��߂Ȃ��v�ɂ������A�{�[�h�̃N���A�����邩�H
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ReWrite( MYSIGN_WORK *wk, int seq )
{
	EndMessagePrint( wk, msg_oekaki_12 );		// �����Ȃ����܂����H
	wk->seq = MYSIGN_MODE_REWRITE_WAIT;

	EndSequenceCommonFunc( wk );				//�I���I�����̋��ʏ���
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
static int Oekaki_ReWriteWait( MYSIGN_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = MYSIGN_MODE_REWRITE_SELECT;
		TouchYesNoStart( wk->bgl, wk->TouchSubWindowSys );
//		return SEQ_OUT;
	}

	EndSequenceCommonFunc( wk );		//�I���I�����̋��ʏ���
	return seq;

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
static const u8 oekaki_brush[2][8][16]={
	{/*  0  */              /*  1  */               /*  2  */              /*  3  */
//	{0x00,0x00, 0x00,0x00,  0x11,0x01,  0x00,0x00,  0x11,0x01, 0x00,0x00,  0x11,0x01,0x00,0x00,},
//	{0x00,0x00, 0x00,0x00,  0x00,0x00,  0x00,0x00,  0x00,0x00, 0x00,0x00,  0x00,0x00,0x00,0x00,},

	{0x00,0x00, 0x00,0x00,  0x10,0x01,  0x00,0x00,  0x10,0x01, 0x00,0x00,  0x00,0x00,0x00,0x00,},
	{0x00,0x00, 0x00,0x00,  0x00,0x00,  0x00,0x00,  0x00,0x00, 0x00,0x00,  0x00,0x00,0x00,0x00,},


	},                                                                     
	{                                                                      
	{0x00,0x00, 0x11,0x11,  0x10,0x01,  0x10,0x11,  0x10,0x01, 0x11,0x11,  0x00,0x00,},
	{0x00,0x00, 0x22,0x22,  0x20,0x02,  0x22,0x22,  0x20,0x02, 0x22,0x22,  0x00,0x00,},
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
	if(win_x < 0){
		int diff;
		diff = win_x*-1;
		if(diff>win_dx){
			diff = win_dx;
		}
		win_x   = 0;
		src_x  += diff;
		src_dx -= diff;
		win_dx -= diff;
	}

	if(win_y < 0){
		int diff;
		diff = win_y*-1;
		if(diff>win_dy){
			diff = win_dy;
		}
		win_y   = 0;
		src_y  += diff;
		src_dy -= diff;
		win_dy -= diff;
	}

	GF_BGL_BmpWinPrint( win, src,	src_x, src_y, src_dx, src_dy, win_x, win_y, win_dx, win_dy );
}


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

//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		s = dx >> 1;
		while (++x1 <= x2) {
			if ((s -= dy) < 0) {
				s += dx;  y1 += step;
			};
//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		}
	} else {
		if (y1 > y2) {
			step = (x1 > x2) ? 1 : -1;
			s = y1;  y1 = y2;  y2 = s;  x1 = x2;
		} else step = (x1 < x2) ? 1 : -1;
//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		s = dy >> 1;
		while (++y1 <= y2) {
			if ((s -= dx) < 0) {
				s += dy;  x1 += step;
			}
//			GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
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
				sx = old[i].x-OEKAKI_BOARD_POSX*8;
				sy = old[i].y-OEKAKI_BOARD_POSY*8;
			}
			for(r=0;r<all[i].size;r++){
				px = all[i].x[r] - OEKAKI_BOARD_POSX*8;
				py = all[i].y[r] - OEKAKI_BOARD_POSY*8;
				

				// BG1�ʗpBMP�i���G�����摜�j�E�C���h�E�m��
				DrawPoint_to_Line(win, oekaki_brush[0][all[i].brush], px, py, &sx, &sy, r, old[i].size);
//				DrawPoint_to_Line(win, oekaki_brush[0][all[i].brush], -1, -1, &sx, &sy, r, old[i].size);
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
static void MoveCommCursor( MYSIGN_WORK *wk )
{
	int i;
	// �`��p�y�����񃏁[�N�ɂ����ڔ��f������
	TOUCH_INFO *all = wk->AllTouchResult;


	// ���W�f�[�^�������Ă��鎞�̓J�[�\�����W�𔽉f������

//	SetCursor_Pos( wk->MainActWork[i], all[0].x[all[0].size-1],  all[0].y[all[0].size-1]);

	
	
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
static void DebugTouchDataTrans( MYSIGN_WORK *wk )
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
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, MYSIGN_WORK *wk )
{
	int i,id;

	return ;

	// ���ꂼ��̕����p�l���̔w�i�F�ŃN���A
	for(i=0;i<5;i++){
		GF_BGL_BmpWinFill( &win[i], 0, 0, 0, OEKAKI_NAME_BMP_W*8, OEKAKI_NAME_BMP_H*8 );
	}

	// �`��
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(FBMP_COL_RED,FBMP_COL_RED_SDW,15),NULL);
		GF_BGL_BmpWinOn( &win[i] );
	}

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
 * $brief   �^�b�`�p�l�����̑���M���s��
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LineDataSendRecv( MYSIGN_WORK *wk )
{

	wk->AllTouchResult[0] = wk->MyTouchResult;

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
static void EndMessagePrint( MYSIGN_WORK *wk, int msgno )
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

	// ������`��J�n
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, 
										CONFIG_GetMsgPrintSpeed(wk->config), NULL);


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
static void EndMessageWindowOff( MYSIGN_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}



//------------------------------------------------------------------
/**
 * $brief   �T�C���f�[�^���������ށi16�F�f�[�^��1bit�ɏk�߂ď�������)
 *
 * @param   des		
 * @param   src		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Output_SignData( u8 *des, u8 *src )
{
	int i,s,count=0;
	
	
	s=0;
	*des = 0;
	for(i=0;i<OEKAKI_GRAPHI_SIZE;i++){
		int w;

		// ���ʃf�[�^��1bit��
		w = src[i]&0x0f;
		if(w==1){
			*des |= (1<<s);
		}
		s++;

		// ��ʃf�[�^��1bit��
		w = src[i]>>4;
		if(w==1){
			*des |= (1<<s);
		}
		s++;

		// 8bit�ɂȂ����珑���o��
		if(s==8){
			count++;
			des++;
			*des=0;
			s=0;
		}
		
		if( count>= OEKAKI_GRAPHI_SIZE ){
			GF_ASSERT(0 && "���k�f�[�^���̈�𒴂���");
		}

	}
}


#define MIN_SCRUCH	(3)
#define MAX_SCRUCH	(40)

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W����
 *
 * @param	wk		��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BrushCanvas( MYSIGN_WORK *wk)
{
	BOOL scruch;
	int sub;
	scruch = FALSE;
	//�ێ����W�ƃ^�b�`���W�̍��������
	if( (sys.tp_x!=0xffff)&&(sys.tp_y!=0xffff) && (wk->BeforeX!=0xffff)&&(wk->BeforeY!=0xffff) ){	//�l�L�����H

		//�������K��l�ȏ�̏ꍇ�͖��������Ƃɂ���
		if ( wk->BeforeX > sys.tp_x ){		//�O��̂ق����l���傫�����H
			sub = wk->BeforeX - sys.tp_x;
			wk->scruchInfo.DirX = -1;
		}else{
			sub = sys.tp_x - wk->BeforeX;
			wk->scruchInfo.DirX = 1;
		}
		if ( (sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH) ){
			if ( wk->BeforeY > sys.tp_y ){	//�O��̂ق����l���傫�����H
				sub = wk->BeforeY - sys.tp_y;
				wk->scruchInfo.DirY = -1;
			}else{
				sub = sys.tp_y - wk->BeforeY;
				wk->scruchInfo.DirY = 1;
			}
			if (sub<=MAX_SCRUCH){
				scruch = TRUE;			//��������
				PlayScruchSe( &wk->scruchInfo );
//				Snd_SePlay( SEQ_SE_DP_KYU01 );
			}else{
//				ClearScruchSndNow(&wk->ScruchSnd);
			}
		}else if (sub<=MAX_SCRUCH){
			if ( wk->BeforeY > sys.tp_y ){		//�O��̂ق����l���傫�����H
				sub = wk->BeforeY - sys.tp_y;
				wk->scruchInfo.DirY = -1;
			}else{
				sub = sys.tp_y - wk->BeforeY;
				wk->scruchInfo.DirY = 1;
			}
			if ((sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH)){
				scruch = TRUE;		//��������
				PlayScruchSe( &wk->scruchInfo );
//				Snd_SePlay( SEQ_SE_DP_KYU01 );
			}else{
//				ClearScruchSndNow(&wk->ScruchSnd);
			}
		}

	}
		//�ێ����W�X�V
	wk->BeforeX = sys.tp_x;
	wk->BeforeY = sys.tp_y;
}


//------------------------------------------------------------------
/**
 * @brief   ������ς����̂ł���΁A���ʉ����u�L���b�v�Ɩ炷
 *
 * @param   scruchInfo		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PlayScruchSe( SCRUCH_INFO *scruchInfo )
{
	//���񔻒�
	if ((scruchInfo->OldDirX == 0)&&(scruchInfo->OldDirY == 0)){
		OS_Printf("����\n");//����
		if(!Snd_SePlayCheck( SEQ_SE_DP_KYU01 )){
			Snd_SePlay( SEQ_SE_DP_KYU01 );
		}
	}
	//�O��̕����ƍ���̕������r
	if ((scruchInfo->OldDirX*scruchInfo->DirX<0) ||
			(scruchInfo->OldDirY*scruchInfo->DirY<0)){
//		OS_Printf("�؂�ւ�\n");//�������ς�����̂ŉ���؂�ւ���
		if(!Snd_SePlayCheck( SEQ_SE_DP_KYU01 )){
			Snd_SePlay( SEQ_SE_DP_KYU01 );
		}
	}

	scruchInfo->OldDirX = scruchInfo->DirX;
	scruchInfo->OldDirY = scruchInfo->DirY;
	scruchInfo->DirX = 0;
	scruchInfo->DirY = 0;
}
