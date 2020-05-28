//============================================================================================
/**
 * @file	fnote_main.c
 * @brief	�`���m�[�g�@�\�����C������
 * @author	Hiroyuki Nakamura
 * @date	2006.03.06
 */
//============================================================================================
#include "common.h"
#include "savedata/fnote_mem.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_fantasy_note.h"
#include "application/app_tool.h"
#include "communication/wm_icon.h"

#define	F_NOTE_H_GLOBAL
#define	FNOTE_MAIN_H_GLOBAL
#include "application/f_note.h"
#include "fnote_main.h"
#include "fnote_bmp.h"
#include "f_note_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN = 0,			// �����t�F�[�h�҂�
	SEQ_MAIN,			// ���C���R���g���[��
	SEQ_PAGE_NOW,		// ���݂̃y�[�W��
	SEQ_PAGE_PAST,		// �ߋ��̃y�[�W��
	SEQ_OUT,			// �I���t�F�[�h�҂�
};

#define	TMP_MSG_BUFSIZ	( 128 )		// �e���|�������b�Z�[�W�o�b�t�@�T�C�Y



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void FNOTE_VBlankTask( TCB_PTR tcb, void * work );
static void FNOTE_VBlank( void * work );
static void FNOTE_VramBankSet(void);
static void FNOTE_BgSet( GF_BGL_INI * ini );
static void FNOTE_BgExit( GF_BGL_INI * ini );
static void FNOTE_BgGraphicSet( FNOTE_WORK * wk );
static void FNOTE_MsgBufCreate( FNOTE_WORK * wk );
static void FNOTE_MsgBufRelease( FNOTE_WORK * wk );

static int FNOTE_SeqIn( FNOTE_WORK * wk );
static int FNOTE_SeqMain( FNOTE_WORK * wk );
static int FNOTE_SeqPageNow( FNOTE_WORK * wk );
static int FNOTE_SeqPagePast( FNOTE_WORK * wk );
static int FNOTE_SeqOut( FNOTE_WORK * wk );

static u8 FNOTE_PageChangeCheck( FNOTE_WORK * wk, s8 mv );
static void FNOTE_ScrnFrameSet( FNOTE_WORK * wk );
static void FNOTE_ScrnPalChg( FNOTE_WORK * wk, u8 frm, u8 pal );
static void FNOTE_BmpScrnCopy( FNOTE_WORK * wk );
static u8 FNOTE_ScrnWriteNow( FNOTE_WORK * wk );
static u8 FNOTE_ScrnWritePast( FNOTE_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================

// �X�N���[�����������e�[�u��
static const u8 ScrnChgTbl[9][32] =
{
	{ 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f },
	{ 0x00,0x01,0x02,0x03,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0xff,0xff,0xff,0xff },
	{ 0x00,0x01,0x02,0x03,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0x00,0x01,0x02,0x03,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x1c,0x1d,0x1e,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0x00,0x01,0x02,0x03,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0x00,0x01,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0x1c,0x1d,0x1e,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff }

/*
	{ 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1c,0x1d,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x1c,0x1d,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x01,0x02,0x03,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x1c,0x1d,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x1c,0x1d,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x1e,0x1f },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11 },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x01,0x02,0x03 },
	{ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff }
*/
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
PROC_RESULT FantasyNoteProc_Init( PROC * proc, int * seq )
{
	FNOTE_WORK * wk;
	SAVEDATA * sv;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();				// HBlank���荞�ݒ�~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	G2_BlendNone();
	G2S_BlendNone();

	sys_KeyRepeatSpeedSet( 4, 8 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_FANTASYNOTE, 0x20000 );

	sv = PROC_GetParentWork( proc );
	wk = PROC_AllocWork( proc, sizeof(FNOTE_WORK), HEAPID_FANTASYNOTE );
	memset( wk, 0, sizeof(FNOTE_WORK) );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_FANTASYNOTE );

	wk->sv   = sv;
	wk->dat  = SaveData_GetFNote( sv );
	wk->myst = SaveData_GetMyStatus( sv );

	APP_WipeStart( APP_WIPE_IN, HEAPID_FANTASYNOTE );

	FontProc_LoadBitData( FONT_SYSTEM, HEAPID_FANTASYNOTE );

//	InitTPSystem();					// �^�b�`�p�l���V�X�e��������
//	InitTPNoBuff(4);

	FNOTE_VramBankSet();			// VRAM���蓖��
	FNOTE_BgSet( wk->bgl );			// BG������
	FNOTE_BgGraphicSet( wk );		// BG�O���t�B�b�N�Z�b�g

	FNOTE_MsgBufCreate( wk );		// ���b�Z�[�W�֘A�쐬

	FantasyNote_BmpAdd( wk );		// BMP�ݒ�

//	Debug_FNOTE_BmpPut( wk, 0 );
//	Debug_FNOTE_BmpPut( wk, 1 );
	FantasyNote_BmpPut( wk, 0 );

	FNOTE_BmpScrnCopy( wk );	// BMP�X�N���[���R�s�[

//	InitPageSet( wk );					// �����y�[�W�쐬

	sys_VBlankFuncChange( FNOTE_VBlank, wk );	// VBlank�Z�b�g

	GF_Disp_DispOn();

	WirelessIconEasy();
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON

	Snd_DataSetByScene( SND_SCENE_SUB_FNOTE, 0, 0 );// �T�E���h�f�[�^���[�h(�`���m�[�g)(BGM���p��)

	return PROC_RES_FINISH;
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
PROC_RESULT FantasyNoteProc_Main( PROC * proc, int * seq )
{
	FNOTE_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:			// �����t�F�[�h�҂�
		*seq = FNOTE_SeqIn( wk );
		break;
	
	case SEQ_MAIN:			// ���C���R���g���[��
		*seq = FNOTE_SeqMain( wk );
		break;

	case SEQ_PAGE_NOW:		// ���݂̃y�[�W��
		*seq = FNOTE_SeqPageNow( wk );
		break;

	case SEQ_PAGE_PAST:		// �ߋ��̃y�[�W��
		*seq = FNOTE_SeqPagePast( wk );
		break;

	case SEQ_OUT:			// �I���t�F�[�h�҂�
		if( FNOTE_SeqOut( wk ) == TRUE ){
			return PROC_RES_FINISH;
		}
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
PROC_RESULT FantasyNoteProc_End( PROC * proc, int * seq )
{
	FNOTE_WORK * wk  = PROC_GetWork( proc );

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g

	FantasyNote_BmpFree( wk );		// BMP�E�B���h�E�J��
	FNOTE_BgExit( wk->bgl );		// BGL�폜
	FNOTE_MsgBufRelease( wk );

	FontProc_UnloadBitData( FONT_SYSTEM );

//	TCB_Delete( wk->vtask );

	PROC_FreeWork( proc );				// ���[�N�J��

	sys_DeleteHeap( HEAPID_FANTASYNOTE );

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
static void FNOTE_VBlankTask( TCB_PTR tcb, void * work )
{
	FNOTE_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

static void FNOTE_VBlank( void * work )
{
	FNOTE_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );
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
static void FNOTE_VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_256_AB,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
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
static void FNOTE_BgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// ����
	{	// FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}
	{	// FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x20000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}
	{	// CHAR
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
	{	// CHAR
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_FANTASYNOTE );
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_FANTASYNOTE );
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
static void FNOTE_BgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControlInit();

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_FANTASYNOTE, ini );
}

//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_BgGraphicSet( FNOTE_WORK * wk )
{
	u16 * scrn_buf;

	if( MyStatus_GetMySex( wk->myst ) == 0 ){
		ArcUtil_BgCharSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_boy_NCGR,
			wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_FANTASYNOTE );
		ArcUtil_ScrnSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_boy_NSCR,
			wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_FANTASYNOTE );
		ArcUtil_PalSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_boy_NCLR,
			PALTYPE_MAIN_BG, 0, 0, HEAPID_FANTASYNOTE );
	}else{
		ArcUtil_BgCharSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_girl_NCGR,
			wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_FANTASYNOTE );
		ArcUtil_ScrnSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_girl_NSCR,
			wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_FANTASYNOTE );
		ArcUtil_PalSet(
			ARC_FNOTE_GRA, NARC_f_note_gra_note_girl_NCLR,
			PALTYPE_MAIN_BG, 0, 0, HEAPID_FANTASYNOTE );
	}

	scrn_buf = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME2_M );
	MI_CpuCopy16( scrn_buf, wk->chr_scrn, 0x800 );
	GF_BGL_ScreenBufSet( wk->bgl, GF_BGL_FRAME3_M, wk->chr_scrn, 0x800 );

	// �V�X�e���t�H���g�p���b�g�Z�b�g
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 15 * 32, HEAPID_FANTASYNOTE );

	// ����ʂ̃J���[�O������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_MsgBufCreate( FNOTE_WORK * wk )
{
	wk->mman = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fantasy_note_dat, HEAPID_FANTASYNOTE );
	wk->wset = WORDSET_Create( HEAPID_FANTASYNOTE );
	wk->msg_buf = STRBUF_Create( TMP_MSG_BUFSIZ, HEAPID_FANTASYNOTE );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FNOTE_MsgBufRelease( FNOTE_WORK * wk )
{
	MSGMAN_Delete( wk->mman );
	WORDSET_Delete( wk->wset );
	STRBUF_Delete( wk->msg_buf );
}




static int FNOTE_SeqIn( FNOTE_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		return SEQ_MAIN;
	}
	return SEQ_IN;
}

static int FNOTE_SeqMain( FNOTE_WORK * wk )
{
	// ���݂�
	if( sys.trg & PAD_KEY_LEFT ){
		if( FNOTE_PageChangeCheck( wk, -1 ) == TRUE ){
			return SEQ_PAGE_NOW;
		}
		return SEQ_MAIN;
	}

	// �ߋ���
	if( sys.trg & (PAD_BUTTON_A|PAD_KEY_RIGHT) ){
		if( FNOTE_PageChangeCheck( wk, 1 ) == TRUE ){
			return SEQ_PAGE_PAST;
		}
		return SEQ_MAIN;
	}

	// ���݂� or �I��
	if( sys.trg & PAD_BUTTON_B ){
		if( wk->page != 0 ){
			if( FNOTE_PageChangeCheck( wk, -1 ) == TRUE ){
				return SEQ_PAGE_NOW;
			}
		}else{
			APP_WipeStart( APP_WIPE_OUT, HEAPID_FANTASYNOTE );
			return SEQ_OUT;
		}
	}

	// �I��
	if( sys.trg & PAD_BUTTON_START ){
		APP_WipeStart( APP_WIPE_OUT, HEAPID_FANTASYNOTE );
		return SEQ_OUT;
	}
	return SEQ_MAIN;
}

static int FNOTE_SeqPageNow( FNOTE_WORK * wk )
{
	switch( wk->page_chg_seq ){
	case 0:
		FNOTE_ScrnFrameSet( wk );
		FNOTE_ScrnPalChg( wk, wk->new_chr_frm, wk->page-1 );
//		Debug_FNOTE_BmpPut( wk, wk->page_write_flg^1 );	// ��ʏ�������
		wk->page--;
		FantasyNote_BmpPut( wk, wk->page_write_flg^1 );	// ��ʏ�������
		wk->page_chg_seq = 1;
		Snd_SePlay( SEQ_SE_DP_MEKURU3 );
		break;

	case 1:
		if( FNOTE_ScrnWriteNow( wk ) == TRUE ){
			wk->page_chg_cnt = 0;
			wk->page_chg_seq = 0;
			wk->page_write_flg ^= 1;
//			wk->page--;

			GF_BGL_ScrWrite( wk->bgl, wk->now_bmp_frm, wk->bmp_scrn, 0, 0, 32, 32 );
			GF_BGL_ScrWrite( wk->bgl, wk->now_chr_frm, wk->chr_scrn, 0, 0, 32, 32 );
			GF_BGL_LoadScreenV_Req( wk->bgl, wk->now_bmp_frm );
			GF_BGL_LoadScreenV_Req( wk->bgl, wk->now_chr_frm );

			return SEQ_MAIN;
		}
	}

	return SEQ_PAGE_NOW;
}

static int FNOTE_SeqPagePast( FNOTE_WORK * wk )
{
	switch( wk->page_chg_seq ){
	case 0:
		FNOTE_ScrnFrameSet( wk );
//		Debug_FNOTE_BmpPut( wk, wk->page_write_flg^1 );	// ��ʏ�������
		wk->page++;
		FantasyNote_BmpPut( wk, wk->page_write_flg^1 );	// ��ʏ�������
		wk->page_chg_seq = 1;
		Snd_SePlay( SEQ_SE_DP_MEKURU3 );
		break;

	case 1:
		if( FNOTE_ScrnWritePast( wk ) == TRUE ){
			wk->page_chg_cnt = 0;
			wk->page_chg_seq = 0;
			wk->page_write_flg ^= 1;
//			wk->page++;
			return SEQ_MAIN;
		}
	}

	return SEQ_PAGE_PAST;
}



static int FNOTE_SeqOut( FNOTE_WORK * wk )
{
	return WIPE_SYS_EndCheck();
}





static void FNOTE_ScrnFrameSet( FNOTE_WORK * wk )
{
	if( wk->page_write_flg == 0 ){
		wk->now_bmp_frm = GF_BGL_FRAME0_M;
		wk->now_chr_frm = GF_BGL_FRAME2_M;
		wk->new_bmp_frm = GF_BGL_FRAME1_M;
		wk->new_chr_frm = GF_BGL_FRAME3_M;
	}else{
		wk->now_bmp_frm = GF_BGL_FRAME1_M;
		wk->now_chr_frm = GF_BGL_FRAME3_M;
		wk->new_bmp_frm = GF_BGL_FRAME0_M;
		wk->new_chr_frm = GF_BGL_FRAME2_M;
	}
}

static u8 FNOTE_PageCheck( FNOTE_WORK * wk, u8 page )
{
	FNOTE_WK_START	mem;

	FNOTE_DataGet( wk->dat, &mem, FNOTE_TYPE_START, page );
	if( mem.year == 0 && mem.month == 0 && mem.day == 0 ){
		return FALSE;
	}
	return TRUE;
}

static u8 FNOTE_PageChangeCheck( FNOTE_WORK * wk, s8 mv )
{
	if( mv == 1 ){
		if( wk->page != 9 ){
			if( FNOTE_PageCheck( wk, wk->page+1 ) == TRUE ){
				return TRUE;
			}
		}
	}else{
		if( wk->page != 0 ){
			if( FNOTE_PageCheck( wk, wk->page-1 ) == TRUE ){
				return TRUE;
			}
		}
	}
	return FALSE;
}

static void FNOTE_ScrnPalChg( FNOTE_WORK * wk, u8 frm, u8 pal )
{
	GF_BGL_ScrPalChange( wk->bgl, frm, 0, 0, 32, 32, pal );
	GF_BGL_LoadScreenV_Req( wk->bgl, frm );
}

static void FNOTE_BmpScrnCopy( FNOTE_WORK * wk )
{
	u16 * scrn_buf;

	scrn_buf = GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME0_M );
	MI_CpuCopy16( scrn_buf, wk->bmp_scrn, 0x800 );
}


static void FNOTE_ScrnWriteMain( FNOTE_WORK * wk, u16 * scrn, u16 frm, u16 cnt )
{
	u16	* scrn_buf;
	u16	i, j;

	scrn_buf = GF_BGL_ScreenAdrsGet( wk->bgl, frm );

	for( j=0; j<32; j++ ){
		if( ScrnChgTbl[cnt][j] == 0xff ){
			GF_BGL_ScrFill( wk->bgl, frm, 0, j, 0, 1, 32, 0 );
			continue;
		}
		for( i=0; i<32; i++ ){
			scrn_buf[i*32+j] = scrn[ i*32 + ScrnChgTbl[cnt][j] ];
		}
	}

	GF_BGL_LoadScreenV_Req( wk->bgl, frm );
}


static u8 FNOTE_ScrnWriteNow( FNOTE_WORK * wk )
{
	FNOTE_ScrnWriteMain( wk, wk->bmp_scrn, wk->now_bmp_frm, wk->page_chg_cnt );
	FNOTE_ScrnWriteMain( wk, wk->chr_scrn, wk->now_chr_frm, wk->page_chg_cnt );
	FNOTE_ScrnPalChg( wk, wk->now_chr_frm, wk->page+1 );

	wk->page_chg_cnt++;
	if( wk->page_chg_cnt == 9 ){
		GF_BGL_PrioritySet( wk->new_bmp_frm, 0 );
		GF_BGL_PrioritySet( wk->new_chr_frm, 1 );
		GF_BGL_PrioritySet( wk->now_bmp_frm, 2 );
		GF_BGL_PrioritySet( wk->now_chr_frm, 3 );
		return TRUE;
	}

	return FALSE;
}

static u8 FNOTE_ScrnWritePast( FNOTE_WORK * wk )
{
	FNOTE_ScrnWriteMain( wk, wk->bmp_scrn, wk->new_bmp_frm, 8-wk->page_chg_cnt );
	FNOTE_ScrnWriteMain( wk, wk->chr_scrn, wk->new_chr_frm, 8-wk->page_chg_cnt );
	FNOTE_ScrnPalChg( wk, wk->new_chr_frm, wk->page );

	if( wk->page_chg_cnt == 1 ){
		GF_BGL_PrioritySet( wk->new_bmp_frm, 0 );
		GF_BGL_PrioritySet( wk->new_chr_frm, 1 );
		GF_BGL_PrioritySet( wk->now_bmp_frm, 2 );
		GF_BGL_PrioritySet( wk->now_chr_frm, 3 );
	}

	wk->page_chg_cnt++;
	if( wk->page_chg_cnt == 9 ){
		return TRUE;
	}

	return FALSE;
}
