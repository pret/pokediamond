//==============================================================================================
/**
 * @file	backup_error.c
 * @brief	�o�b�N�A�b�v�F���s�\���
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

#include "msgdata/msg_backup_error.h"

#include "application/backup.h"

extern void sleepFunc(void);
//================================================================
//
//
//		
//
//
//================================================================
//�a�f�R���g���[���萔
#define BUERR_TEXT_FRAME	(GF_BGL_FRAME0_M)

#define BUERR_NULL_PALETTE	( 0x6c21 )		//�a�f�o�b�N�O���E���h�p���b�g

#define	BUERR_TEXT_PALNUM	(1)
#define BUERR_NWIN_CGXNUM	(512 - MENU_WIN_CGX_SIZ)
#define BUERR_NWIN_PALNUM	(2)

#define BUERR_STRBUF_SIZE	(0x180)	//���b�Z�[�W�o�b�t�@�T�C�Y
// ���b�Z�[�W�E�B���h�E
#define	BUERR_WIN_PX		(3)
#define	BUERR_WIN_PY		(3)
#define	BUERR_WIN_SX		(26)
#define	BUERR_WIN_SY		(18)
#define	BUERR_WIN_PAL		(BUERR_TEXT_PALNUM)
#define	BUERR_WIN_CGX		(BUERR_NWIN_CGXNUM-(BUERR_WIN_SX*BUERR_WIN_SY))

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
	BUERR_TEXT_FRAME,			//�E�C���h�E�g�p�t���[��
	BUERR_WIN_PX,BUERR_WIN_PY,	//�E�C���h�E�̈�̍���XY���W
	BUERR_WIN_SX,BUERR_WIN_SY,	//�E�C���h�E�̈��XY�T�C�Y
	BUERR_WIN_PAL,				//�E�C���h�E�̈�̃p���b�g�i���o�[ 
	BUERR_WIN_CGX,				//�E�C���h�E�L�����̈�̊J�n�L�����N�^�i���o�[
};

//=================================================================================================
//
// �ꊇ�R�[��
//
//=================================================================================================
void BackupErrorWarningCall( int heapID )
{
	//int	heapID = HEAPID_BACKUPCONT;
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;
	MSGDATA_MANAGER*	msgman;
	STRBUF*				msgstr;
	int msgID = error01;

	//sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x20000 );

	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

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
	GF_BGL_BGControlSet( bgl, BUERR_TEXT_FRAME, &hd0, GF_BGL_MODE_TEXT );// ���C���a�f�V�X�e���ݒ�
	GF_BGL_ScrClear( bgl, BUERR_TEXT_FRAME );	
	//���b�Z�[�W�E�C���h�E�L�������p���b�g�ǂݍ���
	MenuWinGraphicSet( bgl, BUERR_TEXT_FRAME, BUERR_NWIN_CGXNUM, BUERR_NWIN_PALNUM, 0, heapID );
	//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, BUERR_TEXT_PALNUM * (2*16), heapID );

	GF_BGL_ClearCharSet( BUERR_TEXT_FRAME, 32, 0, heapID );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, BUERR_NULL_PALETTE );	//�w�i�F������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, BUERR_NULL_PALETTE );	//�w�i�F������
	//���b�Z�[�W�f�[�^�ǂݍ���
	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_backup_error_dat, heapID );
	msgstr = STRBUF_Create( BUERR_STRBUF_SIZE, heapID);
	MSG_PrintInit();//���b�Z�[�W�\���V�X�e��������
		
	GF_BGL_BmpWinAddEx( bgl, &msgwin,&windata );//�r�b�g�}�b�v�쐬
	GF_BGL_BmpWinFill( &msgwin, FBMP_COL_WHITE, 0, 0, BUERR_WIN_SX*8, BUERR_WIN_SY*8 );
	BmpMenuWinWrite( &msgwin, WINDOW_TRANS_ON, BUERR_NWIN_CGXNUM, BUERR_NWIN_PALNUM );
	
	MSGMAN_GetString( msgman, msgID, msgstr );	//������̎擾
	GF_STR_PrintSimple(	&msgwin, FONT_SYSTEM, msgstr, 0, 0, 0, NULL );//������̕\��
	STRBUF_Delete( msgstr );

	GF_Disp_DispOn();
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );
	SetBrightness( BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );

	while( 1 ){
		sleepFunc();
#if 0
		int	keyData = PAD_Read();

		if( keyData & PAD_BUTTON_A ){
			break;
		}
#endif
		OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// �u�u�����N�҂�
	}

	GF_BGL_BmpWinDel(&msgwin);
	MSGMAN_Delete( msgman );//���b�Z�[�W�f�[�^�j��

	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_OFF );
	GF_BGL_BGControlExit( bgl, BUERR_TEXT_FRAME );
	sys_FreeMemoryEz( bgl );

	//sys_DeleteHeap( heapID );

	//OS_ResetSystem(0);
	PM_ForceToPowerOff();
}


