//==============================================================================================
/**
 * @file	syoujyou.c
 * @brief	�\����i�}�ӃR���v���[�g�j
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
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/main.h"

#include "demo\syoujyou.h"
#include "msgdata/msg_award.h"
#include "syoujyou.naix"

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
	SYOUJYOU_SEQ_INIT = 0,
	SYOUJYOU_SEQ_DISPON,
	SYOUJYOU_SEQ_WAIT,
	SYOUJYOU_SEQ_SCROLL,
	SYOUJYOU_SEQ_MAIN,
	SYOUJYOU_SEQ_EXIT,
};

//----------------------------------
//�^�錾
//----------------------------------
///	����p���[�N�\����
typedef struct SYOUJYOU_WORK_tag
{
	int					heapID; 
	int					type; 
	SAVEDATA*			savedata;
	MYSTATUS*			my;

	//�a�f�V�X�e���֘A
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin_m;
	GF_BGL_BMPWIN		msgwin_s;
	MSGDATA_MANAGER*	msgman;
	WORDSET*			wordset;

	//�X�N���[��
	s16					scroll;
	int					wait;
}SYOUJYOU_WORK;

//----------------------------------
//�O���֐���`
//----------------------------------
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

//----------------------------------
//�֐��錾
//----------------------------------
PROC_RESULT Syoujyou_Init( PROC * proc, int * seq );
PROC_RESULT Syoujyou_Main( PROC * proc, int * seq );
PROC_RESULT Syoujyou_Exit( PROC * proc, int * seq );

static void Syoujyou_VBlank( void* work );

static void Syoujyou_VramBankSet( SYOUJYOU_WORK* wk );
static void Syoujyou_VramBankRelease( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgDataSet( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgDataRelease( SYOUJYOU_WORK* wk );

static void Syoujyou_ScrollInit( SYOUJYOU_WORK* wk );
static void Syoujyou_ScrollSet( SYOUJYOU_WORK* wk );
static void Syoujyou_GraphicLoad( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgPrint( SYOUJYOU_WORK* wk );

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
#define SYOUJYOU_TEXT_M_FRAME	(GF_BGL_FRAME0_M)
#define SYOUJYOU_SYOU_M_FRAME	(GF_BGL_FRAME1_M)
#define SYOUJYOU_BACK_M_FRAME	(GF_BGL_FRAME3_M)

#define SYOUJYOU_TEXT_S_FRAME	(GF_BGL_FRAME0_S)
#define SYOUJYOU_SYOU_S_FRAME	(GF_BGL_FRAME1_S)
#define SYOUJYOU_BACK_S_FRAME	(GF_BGL_FRAME3_S)

//=================================================================================================
//
// �o�q�n�b��`�e�[�u��
//
//=================================================================================================
const PROC_DATA SyoujyouProcData = {
	Syoujyou_Init,
	Syoujyou_Main,
	Syoujyou_Exit,
	NO_OVERLAY_ID
};

//================================================================
//----------------------------------
//�o�q�n�b������
//----------------------------------
PROC_RESULT Syoujyou_Init( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk;
	int	heapID = HEAPID_SYOUJYOU;

	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof( SYOUJYOU_WORK ), heapID );
	memset( wk, 0, sizeof( SYOUJYOU_WORK ) );

	wk->heapID = heapID;
	{
		SYOUJYOU_INI* ini = (SYOUJYOU_INI*)PROC_GetParentWork( proc );

		wk->savedata	= ini->savedata;
		wk->type		= ini->type;
		wk->my			= SaveData_GetMyStatus(wk->savedata);
	}

	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);
	sys_KeyRepeatSpeedSet(4,8);

	Syoujyou_VramBankSet( wk );
	Syoujyou_MsgDataSet( wk );
	sys_VBlankFuncChange( Syoujyou_VBlank, (void*)wk );

	GF_Disp_DispOn();

	return	PROC_RES_FINISH;
}

//----------------------------------
//�o�q�n�b���C��
//----------------------------------
PROC_RESULT Syoujyou_Main( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk = PROC_GetWork( proc );
	PROC_RESULT result = PROC_RES_CONTINUE;

	switch( *seq ){
	// ��ʏ�����
	case SYOUJYOU_SEQ_INIT:

		Syoujyou_ScrollInit( wk );
		Syoujyou_GraphicLoad( wk );
		Syoujyou_MsgPrint( wk );

		FRAME_ON( SYOUJYOU_TEXT_M_FRAME );
		FRAME_ON( SYOUJYOU_SYOU_M_FRAME );
		FRAME_ON( SYOUJYOU_BACK_M_FRAME );
		FRAME_ON( SYOUJYOU_TEXT_S_FRAME );
		FRAME_ON( SYOUJYOU_SYOU_S_FRAME );
		FRAME_ON( SYOUJYOU_BACK_S_FRAME );
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		*seq = SYOUJYOU_SEQ_DISPON;
		break;

	// �f�B�X�v���C���f
	case SYOUJYOU_SEQ_DISPON:
		if(WIPE_SYS_EndCheck() == TRUE){
			wk->wait = 0;
			*seq = SYOUJYOU_SEQ_WAIT;
		}
		break;
	
	// �J�n�E�F�C�g
	case SYOUJYOU_SEQ_WAIT:
		if( wk->wait < 60 ){
			wk->wait++;
		} else {
			*seq = SYOUJYOU_SEQ_SCROLL;
		}
		break;
	
	// �J�n�E�F�C�g
	case SYOUJYOU_SEQ_SCROLL:
		if( ( wk->scroll > -8*24 )){
			wk->scroll -= 4;
			Syoujyou_ScrollSet( wk );
		} else {
			wk->scroll = -8*24;
			Syoujyou_ScrollSet( wk );
			*seq = SYOUJYOU_SEQ_MAIN;
		}
		break;
	
	// ���C�����[�v
	case SYOUJYOU_SEQ_MAIN:
		if( (KEYTRG( PAD_BUTTON_A ))||(KEYTRG( PAD_BUTTON_B ))||( sys.tp_trg ) ){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			*seq = SYOUJYOU_SEQ_EXIT;
		}
#if 0
		if( KEYCNT( PAD_KEY_UP ) && ( wk->scroll < 0 )){
			wk->scroll += 4;
			Syoujyou_ScrollSet( wk );
		}
		if( KEYCNT( PAD_KEY_DOWN ) && ( wk->scroll > -8*24 )){
			wk->scroll -= 4;
			Syoujyou_ScrollSet( wk );
		}
#endif
		break;

	// �I��
	case SYOUJYOU_SEQ_EXIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			result = PROC_RES_FINISH;
		}
		break;
	}
	return result;
}

//----------------------------------
//�o�q�n�b�I��
//----------------------------------
PROC_RESULT Syoujyou_Exit( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk = PROC_GetWork( proc );
	int heapID = wk->heapID;

	Syoujyou_MsgDataRelease( wk );
	Syoujyou_VramBankRelease( wk );
	sys_VBlankFuncChange( NULL, NULL );

	PROC_FreeWork( proc );
	sys_DeleteHeap( heapID );

	return	PROC_RES_FINISH;
}


//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
static void Syoujyou_VBlank( void* work )
{
	SYOUJYOU_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}


//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
#define PALSIZE			( 2*16 )

// �p���b�g�ݒ�(���C���T�u��ʋ���)
#define SYOUJYOU_BACKPLT_NUM	( 0 )			//�w�i
#define SYOUJYOU_SYOUPLT_NUM	( 1 )			//�܏�
#define SYOUJYOU_TEXTPLT_NUM	( 2 )			//���b�Z�[�W

#define BGCONTSET( frame, scr, cgx, scrsiz, bufsiz ){					\
	header.screenBase		= scr;										\
	header.charBase			= cgx;										\
	header.scrbufferSiz		= bufsiz;									\
	header.screenSize		= scrsiz;									\
	GF_BGL_BGControlSet( wk->bgl, frame, &header, GF_BGL_MODE_TEXT );	\
	GF_BGL_ScrClear( wk->bgl, frame );									\
}

static void Syoujyou_VramBankSet( SYOUJYOU_WORK* wk )
{
	{ //�u�q�`�l�ݒ�
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG(���C���Ƌ���)
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
	{ // �a�f�V�X�e���ݒ�
		GF_BGL_BGCNT_HEADER header = {	0, 0, 0, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										0, 0, GX_BG_EXTPLTT_01, 0, 0, 0, FALSE };
		// ���C���a�f�V�X�e���ݒ�
		// �e�L�X�g�a�f�ݒ�(BG0)
		BGCONTSET(	SYOUJYOU_TEXT_M_FRAME, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000, 
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// �܏�a�f�ݒ�(BG1)
		BGCONTSET(	SYOUJYOU_SYOU_M_FRAME, GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// �w�i�a�f�ݒ�(BG3)
		BGCONTSET(	SYOUJYOU_BACK_M_FRAME, GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x04000,
					GF_BGL_SCRSIZ_256x256, 0x0800 )

		// �T�u�a�f�V�X�e���ݒ�
		// �e�L�X�g�a�f�ݒ�(BG0)
		BGCONTSET(	SYOUJYOU_TEXT_S_FRAME, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// �܏�a�f�ݒ�(BG1)
		BGCONTSET(	SYOUJYOU_SYOU_S_FRAME, GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// �w�i�a�f�ݒ�(BG3)
		BGCONTSET(	SYOUJYOU_BACK_S_FRAME, GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x04000,
					GF_BGL_SCRSIZ_256x256, 0x800 )
	}
	FRAME_ALLOFF
}

static void Syoujyou_VramBankRelease( SYOUJYOU_WORK* wk )
{
	FRAME_ALLOFF

	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_TEXT_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_SYOU_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_BACK_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_TEXT_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_SYOU_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_BACK_S_FRAME );

	sys_FreeMemoryEz( wk->bgl );
}


//----------------------------------
//���b�Z�[�W�ݒ�
//----------------------------------
#define	SYOUJYOU_TEXT_WIN_PX		(0)
#define	SYOUJYOU_TEXT_WIN_PY		(0)
#define	SYOUJYOU_TEXT_WIN_SX		(32)
#define	SYOUJYOU_TEXT_WIN_SY		(24)
#define	SYOUJYOU_TEXT_WIN_PAL		( SYOUJYOU_TEXTPLT_NUM )
#define	SYOUJYOU_TEXT_WIN_CGX		(1)

#define DOTSIZE						(8)

static void Syoujyou_MsgDataSet( SYOUJYOU_WORK* wk )
{
	BMPWIN_DAT text_windata = { 0,SYOUJYOU_TEXT_WIN_PX,SYOUJYOU_TEXT_WIN_PY,
		SYOUJYOU_TEXT_WIN_SX,SYOUJYOU_TEXT_WIN_SY,SYOUJYOU_TEXT_WIN_PAL,SYOUJYOU_TEXT_WIN_CGX };

	MSG_PrintInit();											//���b�Z�[�W�\���V�X�e��������
	wk->msgman = MSGMAN_Create									//���b�Z�[�W�f�[�^�ǂݍ���
		( MSGMAN_TYPE_DIRECT, ARC_MSG,NARC_msg_award_dat, wk->heapID );
	wk->wordset = WORDSET_Create( wk->heapID );					//���[�h�Z�b�g�쐬

	text_windata.frm_num = SYOUJYOU_TEXT_M_FRAME;
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->msgwin_m, &text_windata );	//�r�b�g�}�b�v�쐬
	GF_BGL_BmpWinFill(&wk->msgwin_m,FBMP_COL_NULL,0,0,			//�r�b�g�}�b�v�����N���A
			SYOUJYOU_TEXT_WIN_SX * DOTSIZE, SYOUJYOU_TEXT_WIN_SY * DOTSIZE );
	text_windata.frm_num = SYOUJYOU_TEXT_S_FRAME;
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->msgwin_s, &text_windata );	//�r�b�g�}�b�v�쐬
	GF_BGL_BmpWinFill(&wk->msgwin_s,FBMP_COL_NULL,0,0,			//�r�b�g�}�b�v�����N���A
			SYOUJYOU_TEXT_WIN_SX * DOTSIZE, SYOUJYOU_TEXT_WIN_SY * DOTSIZE );
}

static void Syoujyou_MsgDataRelease( SYOUJYOU_WORK* wk )
{
	GF_BGL_BmpWinDel( &wk->msgwin_s );	//�r�b�g�}�b�v�j��
	GF_BGL_BmpWinDel( &wk->msgwin_m );	//�r�b�g�}�b�v�j��

	WORDSET_Delete( wk->wordset );		//���[�h�Z�b�g�j��
	MSGMAN_Delete(wk->msgman);			//���b�Z�[�W�f�[�^�j��
}


//----------------------------------
//�X�N���[���ݒ�
//----------------------------------
#define SUBBG_OFFS ( 8*24 )
static void Syoujyou_ScrollInit( SYOUJYOU_WORK* wk )
{
	wk->scroll = 0;
	Syoujyou_ScrollSet( wk );
}

static void Syoujyou_ScrollSet( SYOUJYOU_WORK* wk )
{
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_SYOU_M_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_SYOU_S_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll+SUBBG_OFFS );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_TEXT_M_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_TEXT_S_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll+SUBBG_OFFS );
}


//----------------------------------
//�O���t�B�b�N�ǂݍ���
//----------------------------------
static void Syoujyou_GraphicLoad( SYOUJYOU_WORK* wk )
{
	int back_scrID, back_cgxID, back_palID;
	int syou_scrID, syou_cgxID, syou_palID;

	if( wk->type == SYOUJYOU_TYPE_SINOU ){
	//�V���I�E
		back_scrID = NARC_syoujyou_syoujyou_s_bg_NSCR;
		back_cgxID = NARC_syoujyou_syoujyou_s_bg_NCGR; 
		back_palID = NARC_syoujyou_syoujyou_s_bg_NCLR;
		syou_scrID = NARC_syoujyou_dp_syoujyou_s_NSCR;
		syou_cgxID = NARC_syoujyou_dp_syoujyou_s_NCGR;
		syou_palID = NARC_syoujyou_dp_syoujyou_s_NCLR;
	} else {
		//�S��
		back_scrID = NARC_syoujyou_syoujyou_z_bg_NSCR;
		back_cgxID = NARC_syoujyou_syoujyou_z_bg_NCGR; 
		back_palID = NARC_syoujyou_syoujyou_z_bg_NCLR;
		syou_scrID = NARC_syoujyou_dp_syoujyou_z_NSCR;
		syou_cgxID = NARC_syoujyou_dp_syoujyou_z_NCGR;
		syou_palID = NARC_syoujyou_dp_syoujyou_z_NCLR;
	}
	//�w�i
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, back_scrID, wk->bgl, 
						SYOUJYOU_BACK_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, back_cgxID, wk->bgl, 
						SYOUJYOU_BACK_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, back_palID, PALTYPE_MAIN_BG, 
						SYOUJYOU_BACKPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, back_scrID, wk->bgl, 
						SYOUJYOU_BACK_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, back_cgxID, wk->bgl, 
						SYOUJYOU_BACK_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, back_palID, PALTYPE_SUB_BG, 
						SYOUJYOU_BACKPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	//�܏�
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, syou_scrID, wk->bgl, 
						SYOUJYOU_SYOU_M_FRAME, 0, 0, 0, wk->heapID );
	GF_BGL_ScrPalChange( wk->bgl, SYOUJYOU_SYOU_M_FRAME, 0, 0, 32, 24, SYOUJYOU_SYOUPLT_NUM );
	GF_BGL_LoadScreenReq( wk->bgl, SYOUJYOU_SYOU_M_FRAME );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, syou_cgxID, wk->bgl, 
						SYOUJYOU_SYOU_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, syou_palID, PALTYPE_MAIN_BG, 
						SYOUJYOU_SYOUPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, syou_scrID, wk->bgl, 
						SYOUJYOU_SYOU_S_FRAME, 0, 0, 0, wk->heapID );
	GF_BGL_ScrPalChange( wk->bgl, SYOUJYOU_SYOU_S_FRAME, 0, 0, 32, 24, SYOUJYOU_SYOUPLT_NUM );
	GF_BGL_LoadScreenReq( wk->bgl, SYOUJYOU_SYOU_S_FRAME );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, syou_cgxID, wk->bgl, 
						SYOUJYOU_SYOU_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, syou_palID, PALTYPE_SUB_BG, 
						SYOUJYOU_SYOUPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	//�e�L�X�g�iNULL�L�����ݒ�j
	GF_BGL_ClearCharSet( SYOUJYOU_TEXT_M_FRAME, 32, 0, wk->heapID );
	GF_BGL_ClearCharSet( SYOUJYOU_TEXT_S_FRAME, 32, 0, wk->heapID );
	//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, SYOUJYOU_TEXTPLT_NUM * PALSIZE, wk->heapID );
	SystemFontPaletteLoad( PALTYPE_SUB_BG, SYOUJYOU_TEXTPLT_NUM * PALSIZE, wk->heapID );
}


//----------------------------------
//���b�Z�[�W�\��
//----------------------------------
#define SYOUJYOU_STRBUF_SIZE		(0x200)	//���b�Z�[�W�o�b�t�@�T�C�Y

static void Syoujyou_MsgPrint( SYOUJYOU_WORK* wk )
{
	STRBUF* msg_str = STRBUF_Create( SYOUJYOU_STRBUF_SIZE, wk->heapID );
	{//���O�̕\��
		STRBUF* msg_tmp = STRBUF_Create( SYOUJYOU_STRBUF_SIZE, wk->heapID );

		MSGMAN_GetString( wk->msgman, msg_l02r0301_award_01, msg_tmp );
		WORDSET_RegisterPlayerName( wk->wordset, 0, wk->my );
		WORDSET_ExpandStr( wk->wordset, msg_str, msg_tmp );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 48, 32, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 48, 32, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		STRBUF_Delete( msg_tmp );
	}
	{//�{���̕\��
		int		msgID;
	
		if( wk->type == SYOUJYOU_TYPE_SINOU ){
			msgID = msg_l02r0301_award_02;
		} else {
			msgID = msg_l02r0301_award_03;
		}
		MSGMAN_GetString( wk->msgman, msgID, msg_str );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 64, 64, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 64, 64, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
	}
	{
		MSGMAN_GetString( wk->msgman, msg_l02r0301_award_04, msg_str );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 138, 144, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 138, 144, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
	}
	STRBUF_Delete( msg_str );
}



