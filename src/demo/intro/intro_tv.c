//==============================================================================================
/**
 * @file	intro_tv.c
 * @brief	�Q�[���J�n�����f���i�s�u��ʁj
 * @author	
 * @date	
 */
//==============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_util.h"
#include "savedata/savedata_def.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/palanm.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "system/wordset.h"
#include "system/brightness.h"
#include "system/pmfprint.h"

#include "msgdata/msg_telop.h"

#include "intro_tv.naix"

//================================================================
//================================================================
//
//
//		
//
//
//================================================================
//----------------------------------
//�萔�錾
//----------------------------------
// �o�q�n�b���C���V�[�P���X
enum {
	INTRO_SEQ_INIT = 0,
	INTRO_SEQ_BGMSTART,
	INTRO_SEQ_DISPWAIT,
	INTRO_SEQ_DISPON,
	INTRO_SEQ_MAIN,
	INTRO_SEQ_EXIT,
};

//----------------------------------
//�^�錾
//----------------------------------
///	�^�C�g���S�̐���p���[�N�\����
typedef struct INTRO_DEMO_WORK_tag
{
	int					heapID; 
	GF_BGL_INI*			bgl;
	MSGDATA_MANAGER*	msgman;
	int					telopseq;
	GF_BGL_BMPWIN		telopwin;
	int					scroll;
	int					wait;

}INTRO_DEMO_WORK;

//----------------------------------
//�萔�錾
//----------------------------------
//�e���b�v�֐��V�[�P���X�i���o�[��`
enum {
	TELOP_SET = 0,
	TELOP_WAIT,
	TELOP_KEY,
	TELOP_END,
};

//----------------------------------
//�O���֐���`
//----------------------------------
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

//----------------------------------
//�֐��錾
//----------------------------------
PROC_RESULT IntroTV_Init( PROC * proc, int * seq );
PROC_RESULT IntroTV_Main( PROC * proc, int * seq );
PROC_RESULT IntroTV_Exit( PROC * proc, int * seq );

static void IntroTV_VBlank( void* work );

static void IntroTV_VramBankSet( INTRO_DEMO_WORK* wk );
static void IntroTV_VramBankRelease( INTRO_DEMO_WORK* wk );
static void IntroTV_MsgDataSet( INTRO_DEMO_WORK* wk );
static void IntroTV_MsgDataRelease( INTRO_DEMO_WORK* wk );

static BOOL IntroTV_TelopPrint( INTRO_DEMO_WORK * wk, int msgID, int x, int y );
static void IntroTV_SousaScroll( INTRO_DEMO_WORK * wk );
//----------------------------------
//�}�N���錾
//----------------------------------
#define KEYTRG( pattern )	( ( sys.trg & ( pattern ) ) == ( pattern ) )
#define KEYCNT( pattern )	( ( sys.cont & ( pattern ) ) == ( pattern ) )

#define FADE( pattern, col, heapID ) {						\
	WIPE_SYS_Start(	WIPE_PATTERN_WMS,pattern,pattern,col,	\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}

#define FRAME_ON( frame )		{ GF_BGL_VisibleSet( frame, VISIBLE_ON ); }
#define FRAME_OFF( frame )		{ GF_BGL_VisibleSet( frame, VISIBLE_OFF ); }
#define FRAME_ALLOFF {				\
	FRAME_OFF( GF_BGL_FRAME0_M )	\
	FRAME_OFF( GF_BGL_FRAME1_M )	\
	FRAME_OFF( GF_BGL_FRAME2_M )	\
	FRAME_OFF( GF_BGL_FRAME3_M )	\
	FRAME_OFF( GF_BGL_FRAME0_S )	\
	FRAME_OFF( GF_BGL_FRAME1_S )	\
	FRAME_OFF( GF_BGL_FRAME2_S )	\
	FRAME_OFF( GF_BGL_FRAME3_S )	\
}

//�a�f�R���g���[���萔
#define INTRO_TV_TELOP_FRAME	(GF_BGL_FRAME2_M)
#define INTRO_TV_TVFRM_FRAME	(GF_BGL_FRAME0_M)
#define INTRO_TV_SOUSA_FRAME	(GF_BGL_FRAME1_M)
#define INTRO_TV_TENGN_FRAME	(GF_BGL_FRAME3_M)

//=================================================================================================
//
// �o�q�n�b��`�e�[�u��
//
//=================================================================================================
#if 0
const PROC_DATA IntroTVProcData = {
	IntroTV_Init,
	IntroTV_Main,
	IntroTV_Exit,
	NO_OVERLAY_ID
};
#endif

//================================================================
//----------------------------------
//�o�q�n�b������
//----------------------------------
PROC_RESULT IntroTV_Init(PROC * proc, int * seq)
{
	INTRO_DEMO_WORK * wk;
	int	heapID = HEAPID_INTRO_TV;

	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x40000 );

	wk = PROC_AllocWork( proc, sizeof( INTRO_DEMO_WORK ), heapID );
	memset( wk, 0, sizeof( INTRO_DEMO_WORK ) );

	wk->heapID	= heapID;
	wk->wait	= 0;

	return	PROC_RES_FINISH;
}

//----------------------------------
//�o�q�n�b���C��
//----------------------------------
PROC_RESULT IntroTV_Main(PROC * proc, int* seq)
{
	INTRO_DEMO_WORK * wk = PROC_GetWork( proc );
	PROC_RESULT result = PROC_RES_CONTINUE;

	switch( *seq ){
	// ��ʏ�����
	case INTRO_SEQ_INIT:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane(0);
		GXS_SetVisiblePlane(0);
		sys_KeyRepeatSpeedSet(4,8);

		IntroTV_VramBankSet( wk );
		IntroTV_MsgDataSet( wk );

		sys_VBlankFuncChange(IntroTV_VBlank,(void*)wk);
		GF_Disp_DispOn();

		// �I�[�v�j���O�Ȓ�~
		//Snd_BgmStop( SEQ_OPENING, 0 );

		wk->wait = 2*30;
		*seq = INTRO_SEQ_BGMSTART;
		break;

	// �����E�F�C�g
	case INTRO_SEQ_BGMSTART:
		if( wk->wait ){
			wk->wait--;
		} else {
			//  (�t�B�[���h)�s�u�ȍĐ�
			Snd_ZoneBgmSet( SEQ_TV_HOUSOU );	//�]�[���̋Ȃ��Z�b�g
			Snd_DataSetByScene( SND_SCENE_FIELD, SEQ_TV_HOUSOU, 1 );

			wk->wait = 3*30;
			*seq = INTRO_SEQ_DISPWAIT;
		}
		break;

	// �����E�F�C�g
	case INTRO_SEQ_DISPWAIT:
		if( wk->wait ){
			wk->wait--;
		} else {
			wk->wait = 0;
			FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
			*seq = INTRO_SEQ_DISPON;
		}
		break;

	// ����
	case INTRO_SEQ_DISPON:
		IntroTV_SousaScroll( wk );
		if(WIPE_SYS_EndCheck() == TRUE){
			*seq = INTRO_SEQ_MAIN;
		}
		break;

	// ���C�����[�v
	case INTRO_SEQ_MAIN:
		IntroTV_SousaScroll( wk );
		if( IntroTV_TelopPrint( wk, msg_telop_01, 5*8, 6*8 ) == TRUE ){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			*seq = INTRO_SEQ_EXIT;
		}
		break;

	// �I��
	case INTRO_SEQ_EXIT:
		IntroTV_SousaScroll( wk );
		if(WIPE_SYS_EndCheck() == TRUE){
			IntroTV_MsgDataRelease( wk );
			IntroTV_VramBankRelease( wk );
			sys_VBlankFuncChange( NULL, NULL );

			result = PROC_RES_FINISH;
		}
		break;
	}
	return result;
}

//----------------------------------
//�o�q�n�b�I��
//----------------------------------
PROC_RESULT IntroTV_Exit(PROC * proc, int * seq)
{
	INTRO_DEMO_WORK * wk = PROC_GetWork( proc );
	int heapID = wk->heapID;

	PROC_FreeWork( proc );
	sys_DeleteHeap( heapID );

	return	PROC_RES_FINISH;
}


//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
static void IntroTV_VBlank(void* work)
{
	INTRO_DEMO_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}


//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
#define INTRO_TV_NULL_PALETTE		( 0x0000 )		//�a�f�o�b�N�O���E���h�p���b�g
#define PALSIZE					( 2*16 )

#define	INTRO_TV_TELOP_PALNUM	(1)

static void IntroTV_VramBankSet( INTRO_DEMO_WORK* wk )
{
	{ //�u�q�`�l�ݒ�
		GF_BGL_DISPVRAM vramSetTable = {
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
		GF_Disp_SetBank( &vramSetTable );
	}

	{ //�a�f���C�u�����p�������m��
		wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	}
	{ // �a�f�V�X�e���ݒ�
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}
	{ // ���C���a�f�V�X�e���ݒ�
		int frame, cgxID, scrID;
		{// �e���b�v�a�f�ݒ�
			GF_BGL_BGCNT_HEADER hd0 = { 0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x18000, 
										GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
			frame = INTRO_TV_TELOP_FRAME;

			GF_BGL_BGControlSet( wk->bgl, frame, &hd0, GF_BGL_MODE_TEXT );
			GF_BGL_ClearCharSet( frame, 32, 0, wk->heapID );
			GF_BGL_ScrClear( wk->bgl, frame );	
		}
		{// �s�u�g�a�f�ݒ�
			GF_BGL_BGCNT_HEADER hd1 = { 0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x14000, 
										GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
			frame = INTRO_TV_TVFRM_FRAME;
			cgxID = NARC_intro_tv_tv02_NCGR;
			scrID = NARC_intro_tv_tv02_NSCR;

			GF_BGL_BGControlSet( wk->bgl, frame, &hd1, GF_BGL_MODE_TEXT );
			ArcUtil_BgCharSet( ARC_INTRO_TV, cgxID, wk->bgl, frame, 0, 0, 0, wk->heapID );
			ArcUtil_ScrnSet( ARC_INTRO_TV, scrID, wk->bgl, frame, 0, 0, 0, wk->heapID );
		}
		{// �������a�f�ݒ�
			GF_BGL_BGCNT_HEADER hd2 = { 0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x10000, 
										GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
			frame = INTRO_TV_SOUSA_FRAME;
			cgxID = NARC_intro_tv_tv03_NCGR;
			scrID = NARC_intro_tv_tv03_NSCR;

			GF_BGL_BGControlSet( wk->bgl, frame, &hd2, GF_BGL_MODE_TEXT );
			ArcUtil_BgCharSet( ARC_INTRO_TV, cgxID, wk->bgl, frame, 0, 0, 0, wk->heapID );
			ArcUtil_ScrnSet( ARC_INTRO_TV, scrID, wk->bgl, frame, 0, 0, 0, wk->heapID );
		}
		{// �s�u��ʂa�f�ݒ�
			GF_BGL_BGCNT_HEADER hd3 = { 0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
										GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x20000, 
										GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
			frame = INTRO_TV_TENGN_FRAME;
			cgxID = NARC_intro_tv_tv01_NCGR;
			scrID = NARC_intro_tv_tv01_NSCR;

			GF_BGL_BGControlSet( wk->bgl, frame, &hd3, GF_BGL_MODE_TEXT );
			ArcUtil_BgCharSet( ARC_INTRO_TV, cgxID, wk->bgl, frame, 0, 0, 0, wk->heapID );
			ArcUtil_ScrnSet( ARC_INTRO_TV, scrID, wk->bgl, frame, 0, 0, 0, wk->heapID );
		}
	}
	ArcUtil_PalSet( ARC_INTRO_TV, NARC_intro_tv_tv_NCLR, 
					PALTYPE_MAIN_BG, 0, 0, wk->heapID );

	//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, INTRO_TV_TELOP_PALNUM * PALSIZE, wk->heapID );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, INTRO_TV_NULL_PALETTE );	//�w�i�F������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, INTRO_TV_NULL_PALETTE );	//�w�i�F������

	G2_SetBlendAlpha(	GX_BLEND_PLANEMASK_BG1, 
						(GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 ),
						0x04, 0x0c );
}

static void IntroTV_VramBankRelease( INTRO_DEMO_WORK* wk )
{
	FRAME_ALLOFF
	G2_BlendNone();

	GF_BGL_BGControlExit( wk->bgl, INTRO_TV_TENGN_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_TV_SOUSA_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_TV_TVFRM_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_TV_TELOP_FRAME );

	sys_FreeMemoryEz( wk->bgl );
}


//----------------------------------
//���b�Z�[�W�ݒ�
//----------------------------------
static void IntroTV_MsgDataSet( INTRO_DEMO_WORK* wk )
{
	//���b�Z�[�W�f�[�^�ǂݍ���
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_telop_dat, wk->heapID );
	//���b�Z�[�W�\���V�X�e��������
	MSG_PrintInit();
	wk->telopseq = TELOP_SET;
}

static void IntroTV_MsgDataRelease( INTRO_DEMO_WORK* wk )
{
	//���b�Z�[�W�f�[�^�j��
	MSGMAN_Delete(wk->msgman);
}

//----------------------------------
//�e���b�v�\��
//----------------------------------
#define INTRO_TV_STRBUF_SIZE		(0x400)	//���b�Z�[�W�o�b�t�@�T�C�Y
#define DOTSIZE						( 8 )

#define	INTRO_TV_TELOP_WIN_PX		( 0 )
#define	INTRO_TV_TELOP_WIN_PY		( 0 )
#define	INTRO_TV_TELOP_WIN_SX		( 32 )
#define	INTRO_TV_TELOP_WIN_SY		( 24 )
#define	INTRO_TV_TELOP_WIN_PAL		( INTRO_TV_TELOP_PALNUM )
#define	INTRO_TV_TELOP_WIN_CGX		( 1 )

static const BMPWIN_DAT telop_windata = {
	INTRO_TV_TELOP_FRAME,INTRO_TV_TELOP_WIN_PX,INTRO_TV_TELOP_WIN_PY,
	INTRO_TV_TELOP_WIN_SX,INTRO_TV_TELOP_WIN_SY,INTRO_TV_TELOP_WIN_PAL,INTRO_TV_TELOP_WIN_CGX 
};

static BOOL IntroTV_TelopPrint( INTRO_DEMO_WORK * wk, int msgID, int x, int y )
{
	BOOL	result = FALSE;

	switch( wk->telopseq ){
	case TELOP_SET:
		FRAME_OFF( INTRO_TV_TELOP_FRAME );
		{
			STRBUF*	msgstr = STRBUF_Create( INTRO_TV_STRBUF_SIZE, wk->heapID);	

			MSGMAN_GetString( wk->msgman, msgID, msgstr );
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->telopwin, &telop_windata );
			GF_BGL_BmpWinFill( &wk->telopwin, 0, 0, 0,
						INTRO_TV_TELOP_WIN_SX * DOTSIZE, INTRO_TV_TELOP_WIN_SY * DOTSIZE );
			GF_STR_PrintColor( &wk->telopwin, FONT_SYSTEM, msgstr, x, y, 0,
								GF_PRINTCOLOR_MAKE(15, 2, 0), NULL );
			STRBUF_Delete( msgstr );
		}
		GF_BGL_BmpWinOn( &wk->telopwin );
		FRAME_ON( INTRO_TV_TELOP_FRAME );

		wk->wait = 90+150;
		wk->telopseq = TELOP_WAIT;
		break;

	case TELOP_WAIT:
		if( wk->wait ){
			wk->wait--;
		} else {
			wk->telopseq = TELOP_KEY;
		}
		break;

	case TELOP_KEY:
		if( (KEYTRG( PAD_BUTTON_A ) || KEYTRG( PAD_BUTTON_B )) ){
			wk->telopseq = TELOP_END;
		}
		break;

	case TELOP_END:
		GF_BGL_BmpWinDel( &wk->telopwin );
		GF_BGL_ScrClear( wk->bgl, INTRO_TV_TELOP_FRAME );
		wk->telopseq = TELOP_SET;
		result = TRUE;
		break;
	}
	return result;
}

//----------------------------------
//�������X�N���[��
//----------------------------------
static void IntroTV_SousaScroll( INTRO_DEMO_WORK * wk )
{
	wk->scroll += 0x04;
	GF_BGL_ScrollSet( wk->bgl, INTRO_TV_SOUSA_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll >> 4 );
}




