//==============================================================================================
/**
 * @file	com_error_warning_reset.c
 * @brief	�ʐM�G���[��ʁi�\�t�g���Z�b�g�j
 * @author	
 * @date	
 */
//==============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_util.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "system/wordset.h"
#include "system/pmfprint.h"
#include "system/main.h"
#include "system/brightness.h"

#include "msgdata/msg_communication.h"

void ComErrorWarningResetCall( int heapID, int type, int code );
//================================================================
//
//
//		
//
//
//================================================================
//�a�f�R���g���[���萔
#define COMERRRST_TEXT_FRAME	(GF_BGL_FRAME0_M)

#define COMERRRST_NULL_PALETTE	( 0x6c21 )		//�a�f�o�b�N�O���E���h�p���b�g

#define	COMERRRST_TEXT_PALNUM	(1)
#define COMERRRST_NWIN_CGXNUM	(512 - MENU_WIN_CGX_SIZ)
#define COMERRRST_NWIN_PALNUM	(2)

#define COMERRRST_STRBUF_SIZE	(0x180)	//���b�Z�[�W�o�b�t�@�T�C�Y
// ���b�Z�[�W�E�B���h�E
#define	COMERRRST_WIN_PX		(3)
#define	COMERRRST_WIN_PY		(3)
#define	COMERRRST_WIN_SX		(26)
#define	COMERRRST_WIN_SY		(18)
#define	COMERRRST_WIN_PAL		(COMERRRST_TEXT_PALNUM)
#define	COMERRRST_WIN_CGX		(COMERRRST_NWIN_CGXNUM-(COMERRRST_WIN_SX*COMERRRST_WIN_SY))

//================================================================
//================================================================
static const GF_BGL_DISPVRAM vramSetTable = {
	GX_VRAM_BG_256_AB,				// ���C��2D�G���W����BG
	GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
	GX_VRAM_SUB_BG_NONE,			// �T�u2D�G���W����BG
	GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
	GX_VRAM_OBJ_NONE,				// ���C��2D�G���W����OBJ
	GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
	GX_VRAM_SUB_OBJ_NONE,			// �T�u2D�G���W����OBJ
	GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
	GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
	GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
};

static const GF_BGL_SYS_HEADER BGsys_data = {
	GX_DISPMODE_GRAPHICS,
	GX_BGMODE_0, GX_BGMODE_0,
	GX_BG0_AS_2D
};
static const GF_BGL_BGCNT_HEADER hd0 = {
	0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
	GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x18000, GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
};
static const BMPWIN_DAT windata = {
	COMERRRST_TEXT_FRAME,			//�E�C���h�E�g�p�t���[��
	COMERRRST_WIN_PX,COMERRRST_WIN_PY,	//�E�C���h�E�̈�̍���XY���W
	COMERRRST_WIN_SX,COMERRRST_WIN_SY,	//�E�C���h�E�̈��XY�T�C�Y
	COMERRRST_WIN_PAL,				//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	COMERRRST_WIN_CGX,				//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

//=================================================================================================
// ��pVIntr
//=================================================================================================
static void LocalVBlankIntr(void)
{
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);

	MI_WaitDma(GX_DEFAULT_DMAID);
}

//=================================================================================================
//
// �ꊇ�R�[��
//
//=================================================================================================
void ComErrorWarningResetCall( int heapID, int type, int code )
{
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;
	MSGDATA_MANAGER*	msgman;
	STRBUF*				msgstr;
	STRBUF*				msgtmp;
	WORDSET*			wordset;
	int					msgID;

	switch( type ){
      case 0:
      default:
		msgID = Msg_CommError;
        break;
      case 1:
		msgID = Msg_CommFatalError;
        break;
      case 2:
        msgID = Msg_CommErrorMystery;
        break;
      case 3:
        msgID = Msg_CommErrorGTSbusy;
        break;
      case 4:
		msgID = Msg_CommFatalError02;
        break;
    }
    
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

    (void)OS_DisableIrqMask(OS_IE_V_BLANK);
	OS_SetIrqFunction(OS_IE_V_BLANK, LocalVBlankIntr);
    (void)OS_EnableIrqMask(OS_IE_V_BLANK);

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );
	sys_KeyRepeatSpeedSet( 4, 8 );
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
	G2_BlendNone();
	G2S_BlendNone();
	GX_SetVisibleWnd( GX_WNDMASK_NONE ); 
	GXS_SetVisibleWnd( GX_WNDMASK_NONE ); 

	GF_Disp_SetBank( &vramSetTable );		//�u�q�`�l�ݒ�
	bgl = GF_BGL_BglIniAlloc( heapID );		//�a�f���C�u�����p�������m��
	GF_BGL_InitBG( &BGsys_data );			// �a�f�V�X�e���ݒ�
	GF_BGL_BGControlSet( bgl, COMERRRST_TEXT_FRAME, &hd0, GF_BGL_MODE_TEXT );
	GF_BGL_ScrClear( bgl, COMERRRST_TEXT_FRAME );	
	//���b�Z�[�W�E�C���h�E�L�������p���b�g�ǂݍ���
	MenuWinGraphicSet(	bgl, COMERRRST_TEXT_FRAME, 
						COMERRRST_NWIN_CGXNUM, COMERRRST_NWIN_PALNUM, 0, heapID );
	//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, COMERRRST_TEXT_PALNUM * (2*16), heapID );

	GF_BGL_ClearCharSet( COMERRRST_TEXT_FRAME, 32, 0, heapID );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, COMERRRST_NULL_PALETTE );	//�w�i�F������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, COMERRRST_NULL_PALETTE );	//�w�i�F������
	//���b�Z�[�W�f�[�^�ǂݍ���
	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_communication_dat, heapID );
	msgstr = STRBUF_Create( COMERRRST_STRBUF_SIZE, heapID);
	msgtmp = STRBUF_Create( COMERRRST_STRBUF_SIZE, heapID);
	MSG_PrintInit();//���b�Z�[�W�\���V�X�e��������
	wordset = WORDSET_Create( heapID );
		
	GF_BGL_BmpWinAddEx( bgl, &msgwin,&windata );//�r�b�g�}�b�v�쐬
	GF_BGL_BmpWinFill( &msgwin, FBMP_COL_WHITE, 0, 0, COMERRRST_WIN_SX*8, COMERRRST_WIN_SY*8 );
	BmpMenuWinWrite( &msgwin, WINDOW_TRANS_ON, COMERRRST_NWIN_CGXNUM, COMERRRST_NWIN_PALNUM );
	
	WORDSET_RegisterNumber( wordset, 0, code, 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_HANKAKU );
	MSGMAN_GetString( msgman, msgID, msgtmp );	//������̎擾
	WORDSET_ExpandStr( wordset, msgstr, msgtmp );

	GF_STR_PrintSimple(	&msgwin, FONT_SYSTEM, msgstr, 0, 0, 0, NULL );//������̕\��
	STRBUF_Delete( msgstr );

	GF_Disp_DispOn();
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );
	SetBrightness( BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );

	GF_BGL_BmpWinDel( &msgwin );
	MSGMAN_Delete( msgman );
	WORDSET_Delete( wordset );
	sys_FreeMemoryEz( bgl );
}




