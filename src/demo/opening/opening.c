//==============================================================================================
/**
 * @file	opneing.c
 * @brief	�I�[�v�j���O
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "system/main.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/brightness.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/savedata.h"
#include "system/pmfprint.h"

#include "field/game_init.h"
#include "msgdata\msg.naix"							//NARC_msg_??_dat
#include "msgdata\msg_opening.h"					//msg_??

#include "opening.naix"
#include "opening_sys.h"
#include "opening_obj.h"
#include "opening_bmp.h"

#include "application/namein.h"						//NameInProcData

#include "gflib/strbuf_family.h"

#include "field/union_beacon_tool.h"				//UnionView_GetTrainerType


//==============================================================================================
//
//	�f�o�b�N
//
//==============================================================================================


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================


//==============================================================================================
//
//	��`
//
//==============================================================================================
//�V�[�P���X��`
enum {
	SEQ_WELCOME_PM_WORLD,				//�I�[�L�h���m�u�悤�����I�v
	SEQ_KEY_GUIDE,						//�������
	SEQ_GAME_GUIDE,						//�Q�[������
	SEQ_SEX_CHOICE,						//���ʑI��
	SEQ_NAME_INPUT,						//���O����
	SEQ_RIVAL_NAME,						//���C�o�����O����
	SEQ_ID_CHOICE,						//ID�I��
	SEQ_TO_ADVENTURE,					//�`����
	SEQ_EXIT,
};

#define OPENING_FADE_SYNC		(8)		//�t�F�[�hsync��

#define OPENING_MSG_BUF_SIZE	(800)//(1024)	//���b�Z�[�W�T�C�Y
#define OPENING_MENU_BUF_SIZE	(64)	//���j���[�T�C�Y

//���b�Z�[�W�\���ʒu
enum{
	OP_OOKIDO_X		= 0, 
	OP_OOKIDO_Y		= 0,
	OP_KEY_GUIDE_X	= 60, 
	OP_KEY_GUIDE_Y	= 8,
	OP_GAME_GUIDE_X = 8, 
	OP_GAME_GUIDE_Y = 48,
};

//�I�[�L�hOBJ�X�N���[��
#define OP_OOKIDO_SCR_SPD		(2)		//�X�N���[���X�s�[�h
#define OP_OOKIDO_SCR_END		(140 * FX32_ONE)
//#define OP_OOKIDO_SCR_END_2		(90 * FX32_ONE)
#define OP_OOKIDO_SCR_END_2		(86 * FX32_ONE)	//opening_obj.c�̃f�[�^�ƍ��킹��

//��l��BG�X�N���[��
#define OP_HERO_SCR_START		(-140)//(-120)	//�X�N���[���I��
#define OP_HERO_SCR_SPD			(4)		//�X�N���[���C���X�s�[�h
#define OP_HERO_SCR_SPD2		(2)		//�X�N���[�����S�X�s�[�h
#define OP_HERO_SCR_END			(-70)	//�X�N���[���I��

#define AFF_SCALE_END			(0x700)	//(0x200)	//�k���l

//���O���̓��[�h
enum{
	OP_NAMEIN_MODE_HERO = 0,
	OP_NAMEIN_MODE_RIVAL,
};

//�p���b�g�{��
#define OP_DEMO_PAL				(4)		

//�J�[�\���𓮂����܂ł̃E�F�C�g
#define OP_YESNO_WAIT			(3)


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================

static void SetVramBank(void);
static void SetBgHeader( GF_BGL_INI * ini );
static void SetBgGraphic_Sub2( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub4( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub5( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub6( OPENING_WORK * wk, u32 frm, int no );
static void SetBgGraphic_Sub7( OPENING_WORK * wk, u32 frm );
static void SetBgGraphic_Sub8( OPENING_WORK * wk, u32 frm );
static void SetBgGraphic_Sub9( OPENING_WORK * wk, u32 frm );
static void BgExit( GF_BGL_INI * ini );

static void SetPalette_Sub2(void);
static void SetPalette_Sub4(void);
static void SetPalette_Sub5(void);
static void SetPalette_Sub6(void);
static void SetPalette_Sub7(void);

static void VBlankFunc( void * work );
static int KeyCheck( int trg );
static void NextSeq( OPENING_WORK* wk, int* seq, int next );

static void OpeningAff( OPENING_WORK *wk );
static void OpeningAffReset(void);

//�V�[�P���X
static BOOL Seq_WelcomePMWorld( OPENING_WORK* wk );
static BOOL Seq_KeyGuide( OPENING_WORK* wk );
static BOOL Seq_GameGuide( OPENING_WORK* wk );
static BOOL Seq_SexChoice( OPENING_WORK* wk );
static BOOL Seq_NameIn( OPENING_WORK* wk );
static BOOL Seq_RivalNameIn( OPENING_WORK* wk );
static BOOL Seq_IdChoice( OPENING_WORK* wk );
static BOOL Seq_ToAdventure( OPENING_WORK* wk );

//���O����
static void OpeningNameInCall( OPENING_WORK* wk, u32 mode );
static void OpeningNameInMainTCB( TCB_PTR tcb, void* work );
static void OpeningRecover( OPENING_WORK* wk, u32 mode );

//���ʏ������A�I��
static void opening_init_sub();
static void opening_init_sub2( OPENING_WORK* wk );
static void opening_end_sub( OPENING_WORK* wk );

static void opening_talk_win_put( OPENING_WORK* wk );
static void opening_hero_fade_in( OPENING_WORK* wk );
static void opening_hero_fade_out( OPENING_WORK* wk );


//==============================================================================================
//
//	�֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F������
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	"������"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_Init( PROC * proc, int * seq )
{
	int i;
	OPENING_WORK * wk;

	//PLAYER_BGM�Ń^�C�g���A�I�[�v�j���O��炷�悤�ɂ���
	Snd_DataSetByScene( SND_SCENE_OPENING, SEQ_OPENING, 1 );	//�I�[�v�j���O�ȍĐ�

	opening_init_sub();

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OPENING, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(OPENING_WORK), HEAPID_OPENING );
	memset( wk, 0, sizeof(OPENING_WORK) );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OPENING );

	opening_init_sub2(wk);

	//�j����l��BG�͏����Ă���
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

	(*seq) = SEQ_WELCOME_PM_WORLD;

	wk->proc	= proc;
	wk->sv		= ((MAINWORK *)PROC_GetParentWork(wk->proc))->savedata;
	wk->config	= SaveData_GetConfig( wk->sv );	//�R���t�B�O�|�C���^���擾

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F���C��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	"������"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_Main( PROC * proc, int * seq )
{
	OPENING_WORK * wk  = PROC_GetWork( proc );

	//���O���͊Ď�
	if( wk->tcb != NULL ){
		return PROC_RES_CONTINUE;
	}

	switch( *seq ){

	//�I�[�L�h���m�u�悤�����I�v
	case SEQ_WELCOME_PM_WORLD:
		if( Seq_WelcomePMWorld(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//�N���A
		}
		break;

	//�������
	case SEQ_KEY_GUIDE:
		if( Seq_KeyGuide(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_WELCOME_PM_WORLD );
		}
		break;

	//�Q�[������
	case SEQ_GAME_GUIDE:				
		if( Seq_GameGuide(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_WELCOME_PM_WORLD );
		}
		break;

	//���ʑI��
	case SEQ_SEX_CHOICE:		
		if( Seq_SexChoice(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_NAME_INPUT );
		}
		break;

	//���O����
	case SEQ_NAME_INPUT:			
		if( Seq_NameIn(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//�N���A
		}
		break;

	//���C�o�����O����
	case SEQ_RIVAL_NAME:			
		if( Seq_RivalNameIn(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//�N���A
		}
		break;

	//ID�I��
	case SEQ_ID_CHOICE:			
		if( Seq_IdChoice(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_TO_ADVENTURE );
		}
		break;

	//�`����
	case SEQ_TO_ADVENTURE:		
		if( Seq_ToAdventure(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_EXIT );
		}
		break;

	case SEQ_EXIT:
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){
		//if( WIPE_SYS_EndCheck() == TRUE ){
			return PROC_RES_FINISH;
		//}
		break;
	}

	CLACT_Draw( wk->ObjWork.ClactSet );			//�Z���A�N�^�[�풓�֐�

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F�I��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	"������"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_End( PROC * proc, int * seq )
{
	int i;
	OPENING_WORK * wk = PROC_GetWork( proc );

	opening_end_sub( wk );

	PROC_FreeWork( proc );					//���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		//VBlank�Z�b�g
	sys_DeleteHeap( HEAPID_OPENING );

	Main_SetNextProc(NO_OVERLAY_ID, &FirstGameProcData);
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	VRAM�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetVramBank(void)
{
	GF_BGL_DISPVRAM tbl = {
		//GX_VRAM_BG_64_E,				//���C��2D�G���W����BG
		GX_VRAM_BG_128_A,				//���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			//���C��2D�G���W����BG�g���p���b�g

		GX_VRAM_SUB_BG_128_C,			//�T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		//�T�u2D�G���W����BG�g���p���b�g

		GX_VRAM_OBJ_128_B,				//���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		//���C��2D�G���W����OBJ�g���p���b�g

		GX_VRAM_SUB_OBJ_16_I,			//�T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	//�T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_NONE,				//�e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			//�e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------
/**
 * @brief	BG�ݒ�
 *
 * @param	init	BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgHeader( GF_BGL_INI * ini )
{
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_1, GX_BGMODE_1, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	//�I�[�L�h
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	//BG(�t�H���g)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, OP_FRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, OP_FRM_FONT );
	}

	{	//���ʔw�i
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	{	//�j����l��(256�F�A�g��k��)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x400, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
	}

	{	//����ʔw�i
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_S );
	}
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F�j����l��
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub2( OPENING_WORK * wk, u32 frm  )
{
	u8 sex;

	//256�F�A�g��k��
	SetPalette_Sub2();

//	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_character_NCGR, 
//						wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_OPENING );

	sex=(wk->sex == PM_MALE) ? NARC_opening_op_character01_NSCR : NARC_opening_op_character02_NSCR;
	ArcUtil_ScrnSet( ARC_OPENING_GRA, sex, wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F���ʔw�i
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub4( OPENING_WORK * wk, u32 frm  )
{
	SetPalette_Sub4();

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_demo_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_demo01_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F����ʔw�i
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub5( OPENING_WORK * wk, u32 frm  )
{
	SetPalette_Sub5();

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_demo_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_demo02_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F���ʑ������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub6( OPENING_WORK * wk, u32 frm, int no )
{
	int scrn;

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	switch( no ){
	case 0:
	case 3:
		scrn = NARC_opening_op_tutorial0_NSCR;
		break;
	case 1:
		scrn = NARC_opening_op_tutorial1_NSCR;
		break;
	case 2:
		scrn = NARC_opening_op_tutorial2_NSCR;
		break;
	};

	ArcUtil_ScrnSet( ARC_OPENING_GRA, scrn,	wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F����ʑ������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub7( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial3_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F���ʃQ�[������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub8( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial4_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�f�[�^�Z�b�g�F����ʃQ�[������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub9( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial5_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{
	//���C����ʂ̊e�ʂ̕\���R���g���[��(�\��OFF)
	GF_Disp_GX_VisibleControl(	GX_PLANEMASK_BG0 | 
								GX_PLANEMASK_BG1 | 
								GX_PLANEMASK_BG2 |
								GX_PLANEMASK_BG3 | 
								GX_PLANEMASK_OBJ, 
								VISIBLE_OFF );

	//�T�u��ʂ̊e�ʂ̕\���R���g���[��(�\��OFF)
	GF_Disp_GXS_VisibleControl(	GX_PLANEMASK_BG0 | 
								GX_PLANEMASK_BG1 | 
								GX_PLANEMASK_OBJ, 
								VISIBLE_OFF );

	//GF_BGL_BGControlSet�Ŏ擾�������������J��
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );
	GF_BGL_BGControlExit( ini, OP_FRM_FONT );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );

	sys_FreeMemoryEz( ini );
}

//--------------------------------------------------------------
/**
 * @brief	�j����l���p���b�g�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub2(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}

	{
		u16 * adr;
		adr = dat->pRawData;

		DC_FlushRange( dat->pRawData, (16*2)*4 );
		//�]������p���b�g�A�h���X�A�Z�b�g����p���b�gRAM�I�t�Z�b�g�A�]���T�C�Y
		GX_LoadBGPltt( dat->pRawData, 0, (16*2)*4 );			//���C��
		sys_FreeMemoryEz(buf);
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���ʔw�i�p���b�g�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub4(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	//�o�[�W�����Ńp���b�g�ύX
	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GX_LoadBGPltt( dat->pRawData, 0, (16*2) );		//���C��
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	����ʔw�i�p���b�g�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub5(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GXS_LoadBGPltt( dat->pRawData, 0, (16*2) );		//�T�u
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���ʑ�������p���b�g�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub6(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_tutorial_NCLR, &dat,HEAPID_OPENING);
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GX_LoadBGPltt( dat->pRawData, 0, (16*2*2) );		//���C��
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	����ʑ�������p���b�g�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub7(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_tutorial_NCLR, &dat,HEAPID_OPENING);
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GXS_LoadBGPltt( dat->pRawData, 0, (16*2*2) );		//�T�u
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	VBlank�֐�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void VBlankFunc( void * work )
{
	OPENING_WORK* wk = work;

	//�p���b�g�]��
	if( wk->pfd != NULL ){
		PaletteFadeTrans( wk->pfd );
	}

	//�Z���A�N�^�[
	//Vram�]���}�l�[�W���[���s
	DoVramTransferManager();

	//�����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//--------------------------------------------------------------
/**
 * @brief	�L�[�`�F�b�N
 *
 * @param	�L�[
 *
 * @return	none
 */
//--------------------------------------------------------------
static int KeyCheck( int trg )
{
	return (sys.trg & trg);
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�ύX
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void NextSeq( OPENING_WORK* wk, int* seq, int next )
{
	wk->count	= 0;
	wk->sub_seq = 0;
	*seq		= next;
	return;
}

static const fx32 aff_speed[] =
{
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
};

//--------------------------------------------------------------
/**
 * @brief	�k��
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningAff( OPENING_WORK *wk )
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;

	//���̑傫��
	//wk->ScaleX = 1 << FX32_SHIFT;
	//wk->ScaleY = 1 << FX32_SHIFT;
	
	//�g��
	//wk->ScaleX += 2 << (FX32_SHIFT - 6);
	//wk->ScaleY += 2 << (FX32_SHIFT - 6);
	
	//�k��
#if 1
	//�X���[�Y�ɏk��
	wk->ScaleX -= 1 << (FX32_SHIFT - 6);
	wk->ScaleY -= 1 << (FX32_SHIFT - 6);
	//wk->ScaleX -= 2 << (FX32_SHIFT - 6);	//�����Ȃ�
	//wk->ScaleY -= 2 << (FX32_SHIFT - 6);
	//wk->ScaleX -= 1 << (FX32_SHIFT - 2);	//�����Ȃ�
	//wk->ScaleY -= 1 << (FX32_SHIFT - 2);
	//wk->ScaleX -= 1 << (FX32_SHIFT - 8);	//�x���Ȃ�
	//wk->ScaleY -= 1 << (FX32_SHIFT - 8);
#else
	//�i�K�I�ɏk��
	//wk->ScaleX -= aff_speed[wk->count];
	//wk->ScaleY -= aff_speed[wk->count];
	wk->ScaleX -= aff_speed[wk->count/10];
	wk->ScaleY -= aff_speed[wk->count/10];
#endif

	rScale_x = FX_Inv(wk->ScaleX);
	rScale_y = FX_Inv(wk->ScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;

    SVC_WaitVBlankIntr();			//Waiting the end of VBlank interrup
	//G2S_SetBG3Affine( &mtx,		//a matrix for rotation and scaling
	G2_SetBG3Affine( &mtx,			//a matrix for rotation and scaling
						128, 96,	//the center of rotation
						0, 0);		//the reference point before rotation and scaling applied

	//OS_Printf( "scalex = %d\n", wk->ScaleX );
	//OS_Printf( "scaley = %d\n", wk->ScaleY );
	return ;
}

//--------------------------------------------------------------
/**
 * @brief	�g��k�����Z�b�g
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningAffReset(void)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv((1 << FX32_SHIFT));
	rScale_y = FX_Inv((1 << FX32_SHIFT));

    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;

    SVC_WaitVBlankIntr();			//Waiting the end of VBlank interrup
	G2_SetBG3Affine( &mtx,			//a matrix for rotation and scaling
						128, 96,	//the center of rotation
						0, 0 );		//the reference point before rotation and scaling applied
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F�I�[�L�h���m�u�悤�����I�v
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_WelcomePMWorld( OPENING_WORK* wk )
{
	u16 msg_id;
	u32 ret;
	VecFx32 vec;

	switch( wk->sub_seq ){

	//�I�[�L�h�f�[�^�Z�b�g
	case 0:
		//�������W�ɖ߂�
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//�I�[�L�h
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//���C�o��
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//�e

		//���ʔw�i
		SetBgGraphic_Sub4( wk, GF_BGL_FRAME2_M );
	
		//����ʔw�i
		SetBgGraphic_Sub5( wk, GF_BGL_FRAME2_S );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e

		wk->sub_seq++;
		break;

	//�u���b�N�C��
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );
					//WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC*3, HEAPID_OPENING );

		wk->count = 15;
		wk->sub_seq++;
		break;
		
	//�t�F�[�h�I���҂�
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){

			wk->count--;
			if( wk->count == 0 ){

				//��b�E�B���h�E�\��
				opening_talk_win_put( wk );

				//��b�E�B���h�E�ɃI�[�L�h���b�Z�[�W���Z�b�g
				//�u�悭���Ă��ꂽ�ˁI�v
				msg_id = (wk->cancel == 0) ? msg_opening_01 : msg_opening_20;
				//msg_id = (wk->cancel == 0) ? msg_opening_07 : msg_opening_07;
				wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
				GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
				wk->cancel = 0;
				wk->sub_seq++;
			}
		}
		break;

	//�I�[�L�h�̐���
	case 3:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}
		wk->sub_seq++;
		break;

	case 4:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_HAKASE, OP_OOKIDO_SCR_SPD );	//�I�[�L�h
		OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, OP_OOKIDO_SCR_SPD );			//�e
		//OS_Printf( "vec.x = %d\n", vec.x );

		//�X�N���[���I���`�F�b�N
		if( vec.x >= OP_OOKIDO_SCR_END ){
			//OS_Printf( "�I��vec.x = %d\n", vec.x );
			wk->sub_seq++;
		}
		break;

	case 5:
		//���j���[�E�B���h�E
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_MENU_1] );
		
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_MENU_1], 3 );
		OpeningSetMenuData( wk, 0, SEQ_SEX_CHOICE, msg_opening_09 );
		OpeningSetMenuData( wk, 1, SEQ_KEY_GUIDE, msg_opening_07 );
		OpeningSetMenuData( wk, 2, SEQ_GAME_GUIDE, msg_opening_08 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;

		wk->sub_seq++;
		break;

	//�I��҂�
	case 6:
		//�E�F�C�g
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_SEX_CHOICE;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//�u���b�N�A�E�g
	case 7:
		//�u�������傤�ԁv��I�񂾎�
		if( wk->ret_work == SEQ_SEX_CHOICE ){
			return TRUE;
		}

		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 8:
		if( WIPE_SYS_EndCheck() == TRUE ){
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F�������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_KeyGuide( OPENING_WORK* wk )
{
	switch( wk->sub_seq ){

	//��������f�[�^�Z�b�g
	case 0:
		//��b�E�B���h�E������
		BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

		SetPalette_Sub6();
		SetPalette_Sub7();

		SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 0 );
		SetBgGraphic_Sub7( wk, GF_BGL_FRAME2_S );

		//�u���낢��ȁv
		OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_01, 
							OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT,
							FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );
		wk->sub_seq++;
		break;

	//�u���b�N�C��
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//����������1
	case 3:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 1 );

			//�u���傤�����䂤�Ɂv
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_02, 
							OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
							FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//����������2
	case 4:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 2 );

			//�u���j���[���v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_03, 
								OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//����������3
	case 5:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 3 );

			//�u�����̂��߂�́v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_04, 
								OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//����������4
	case 6:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//�u���b�N�A�E�g
	case 7:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 8:
		if( WIPE_SYS_EndCheck() == TRUE ){
			GF_BGL_BmpWinOff( &wk->bmpwin[BMPWIN_GUIDE] );
			wk->cancel = 1;
			return TRUE;
		}
		break;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F�Q�[������
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_GameGuide( OPENING_WORK* wk )
{
	switch( wk->sub_seq ){

	//�Q�[�������f�[�^�Z�b�g
	case 0:
		//��b�E�B���h�E������
		BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

		SetPalette_Sub6();
		SetPalette_Sub7();

		SetBgGraphic_Sub8( wk, GF_BGL_FRAME2_M );
		SetBgGraphic_Sub9( wk, GF_BGL_FRAME2_S );

		//�u���ꂩ��͂��܂�v
		OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_01, 
							OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
							FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

		wk->sub_seq++;
		break;

	//�u���b�N�C��
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//�Q�[���������1
	case 3:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//�u�܂���݂��v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_02, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//�Q�[���������2
	case 4:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//�u�����Ă��܂��Ă���v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_03, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//�Q�[���������3
	case 5:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//�u�Ƃ��ɂ��傤�Ԃ��v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_04, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//�Q�[���������4
	case 6:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//�u�ڂ�������v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_05, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//�Q�[���������5
	case 7:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//�u���ꂪ�v
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_06, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//�Q�[���������6
	case 8:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//�u���b�N�A�E�g
	case 9:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 10:
		if( WIPE_SYS_EndCheck() == TRUE ){
			GF_BGL_BmpWinOff( &wk->bmpwin[BMPWIN_GUIDE] );
			wk->cancel = 1;
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F���ʑI��
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_SexChoice( OPENING_WORK* wk )
{
	u16 col;
	u16 msg_id;
	VecFx32 vec;

	switch( wk->sub_seq ){

	//���ʑI���f�[�^�Z�b�g
	case 0:
		wk->sex = PM_MALE;

		//�j����l��(256�F�A�g��k��)
		SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );

		//��b�E�B���h�E�\��
		//opening_talk_win_put( wk );
		//GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		//��l���X�N���[���C���J�n�ʒu�Z�b�g
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_START );

		wk->sub_seq++;
		break;

	case 1:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_HAKASE, -(OP_OOKIDO_SCR_SPD) );//�I�[�L�h
		OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, -(OP_OOKIDO_SCR_SPD) );		//�e

		//�X�N���[���I���`�F�b�N
		if( vec.x <= OP_OOKIDO_SCR_END_2 ){
			//�������W�ɖ߂�
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//�I�[�L�h
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//�e
			wk->sub_seq++;
		}
		break;

	//�t�F�[�h�I���҂�
	case 2:
		msg_id = (wk->cancel == 0) ? msg_opening_02 : msg_opening_18;
		//msg_id = (wk->cancel == 0) ? msg_opening_07 : msg_opening_07;
		wk->cancel = 0;

		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	//�I�[�L�h�̐���
	case 3:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
		PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );

		wk->count = 10;
		wk->sub_seq++;
		break;

	//�I�[�L�h�p���b�g�A�E�g�҂�
	case 4:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

			wk->count--;
			if( wk->count == 0 ){
				//�j����l��BG�\��
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
				wk->sub_seq++;
			}
		}
		break;

	//��l���X�N���[���C��
	case 5:
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_INC, OP_HERO_SCR_SPD );

		//�X�N���[���l�w�擾
		if( GF_BGL_ScrollGetX(wk->bgl, GF_BGL_FRAME3_M) < OP_HERO_SCR_END ){
			break;
		}

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_END );

		//���j���[�E�B���h�E
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_MENU_2] );
		
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_MENU_2], 2 );
		OpeningSetMenuData( wk, 0, PM_MALE, msg_opening_10 );
		OpeningSetMenuData( wk, 1, PM_FEMALE, msg_opening_11 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;

		wk->sub_seq++;
		break;

	//���ʑI������
	case 6:
		//�E�F�C�g
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );

		switch( wk->ret_work ){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
			//�j����l��(256�F�A�g��k��)
			if( sys.trg == PAD_KEY_UP ){
				wk->sex = PM_MALE;
			}else if( sys.trg == PAD_KEY_DOWN ){
				wk->sex = PM_FEMALE;
			}
			SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
			break;
		default:
			wk->sex = wk->ret_work;
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//�E�֏�����
	case 7:
		//��l���X�N���[���A�E�g
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_DEC, OP_HERO_SCR_SPD );

		//�X�N���[���l�w�擾
		if( GF_BGL_ScrollGetX(wk->bgl, GF_BGL_FRAME3_M) > OP_HERO_SCR_START ){
			break;
		}

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_START );

		//�j����l��BG��\��
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

		wk->count = 10;
		wk->sub_seq++;
		break;

	//��
	case 8:
		wk->count--;
		if( wk->count == 0 ){

			//�I�[�L�h�t�F�[�h�C��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	//�I�[�L�h�\��
	case 9:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			//��b�E�B���h�E�\��
			opening_talk_win_put( wk );

			wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_03, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
			wk->sub_seq++;
		}
		break;

	//���b�Z�[�W�\��
	case 10:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//�u���b�N�A�E�g
	case 11:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//�t�F�[�h�I���҂�
	case 12:
		if( WIPE_SYS_EndCheck() == TRUE ){
			//��b�E�B���h�E������
			BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F���O����
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_NameIn( OPENING_WORK* wk )
{
	u16 msg_id,col;

	switch( wk->sub_seq ){

	case 0:
		wk->sub_seq++;
		break;

	case 1:
		wk->sub_seq++;
		break;

	//���O���͌Ăяo��
	case 2:
		wk->tcb = NULL;
		OpeningNameInCall( wk, OP_NAMEIN_MODE_HERO );
		wk->sub_seq++;
		break;

	//���O���͏I���҂�
	case 3:
		//���O���͊Ď�
		if( wk->tcb != NULL ){
			break;
		}

		//��b�E�B���h�E�\��
		opening_talk_win_put( wk );

		//�u�����񂾂ˁH�v
		msg_id = (wk->sex == PM_MALE) ? msg_opening_16 : msg_opening_17;
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
		wk->sub_seq++;
		break;

	//���ʑI������
	case 4:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		//���j���[�E�B���h�E
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_YESNO] );
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_YESNO], 2 );
		OpeningSetMenuData( wk, 0, SEQ_RIVAL_NAME, msg_opening_14 );
		OpeningSetMenuData( wk, 1, SEQ_SEX_CHOICE, msg_opening_15 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;
		wk->sub_seq++;
		break;

	case 5:
		//�E�F�C�g
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_SEX_CHOICE;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//��l��BG�t�F�[�h�A�E�g
	case 6:
		opening_hero_fade_out( wk );
		wk->sub_seq++;
		break;

	case 7:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );		//�j����l��BG��\��
			GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );

			wk->count = 15;
			wk->sub_seq++;
		}
		break;

	case 8:
		wk->count--;
		if( wk->count == 0 ){
			//�I�[�L�h�t�F�[�h�C��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e
			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	case 9:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			if( wk->ret_work == SEQ_SEX_CHOICE ){
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e
				wk->cancel = 1;
			}else{

				MyStatus_SetMyName( SaveData_GetMyStatus(wk->sv), wk->str );//��l���̖��O�Z�b�g
				MyStatus_SetMySex( SaveData_GetMyStatus(wk->sv), wk->sex );	//��l���̐��ʃZ�b�g

				//�u�����Ȃ܂����ȁv
				msg_id = msg_opening_04;
				wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

				GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
			}

			wk->sub_seq++;
		}
		break;

	case 10:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F���C�o�����O����
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_RivalNameIn( OPENING_WORK* wk )
{
	VecFx32 vec;
	u16 msg_id,col;

	switch( wk->sub_seq ){

	case 0:
		//��b�E�B���h�E�\��
		opening_talk_win_put( wk );

		//�u����́@�Ȃ܂����@�������Ă���Ȃ����H�v
		msg_id = (wk->cancel ==0) ? msg_opening_21 : msg_opening_22;

		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	case 1:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		wk->count = 15;
		wk->sub_seq++;
		break;

	case 2:
		wk->count--;
		if( wk->count == 0 ){
			//�I�[�L�h�t�F�[�h�A�E�g
			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
			wk->sub_seq++;
		}
		break;

#if 0
	//�I�[�L�h�t�F�[�h�A�E�g��ɁA���C�o��������X���C�h�C��
	case 3:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

			OpeningClactPosSet( &wk->ObjWork, OP_OBJ_RIVAL, 200, 30 );			//���W�ύX

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	case 4:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_RIVAL, -(OP_OOKIDO_SCR_SPD) );	//���C�o��
		//OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, -(OP_OOKIDO_SCR_SPD) );		//�e

		//�X�N���[���I���`�F�b�N
		if( vec.x <= OP_OOKIDO_SCR_END_2 ){
			//�������W�ɖ߂�
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//���C�o��
			//OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );	//�e
			wk->sub_seq++;
		}
		break;
#else
	//�I�[�L�h�t�F�[�h�A�E�g��ɁA���C�o���^�񒆂���t�F�[�h�C��
	case 3:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );

			wk->count = 45;
			wk->sub_seq++;
		}
		break;

	case 4:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
			wk->count--;
			if( wk->count == 0 ){
				wk->sub_seq++;
			}
		}
		break;
#endif

	case 5:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );
		wk->sub_seq++;
		break;

	//�t�F�[�h�A�E�g�I���҂�
	case 6:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//���O���͌Ăяo��
	case 7:
		wk->tcb = NULL;
		OpeningNameInCall( wk, OP_NAMEIN_MODE_RIVAL );
		wk->sub_seq++;
		break;

	//���O���͏I���҂�
	case 8:
		//���O���͊Ď�
		if( wk->tcb != NULL ){
			break;
		}

		//��b�E�B���h�E�\��
		opening_talk_win_put( wk );

		//�u���Ɓ@�����̂��@����Ł@�����Ă��邩�ȁH�v
		msg_id = msg_opening_23;
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
		wk->sub_seq++;
		break;

	//�u�͂��E�������v�I������
	case 9:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		//���j���[�E�B���h�E
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_YESNO] );

		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_YESNO], 2 );
		OpeningSetMenuData( wk, 0, SEQ_ID_CHOICE, msg_opening_14 );
		OpeningSetMenuData( wk, 1, SEQ_RIVAL_NAME, msg_opening_15 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;
		wk->sub_seq++;
		break;

	case 10:
		//�E�F�C�g
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_RIVAL_NAME;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	case 11:
		//���C�o���t�F�[�h�A�E�g
		col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
		PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
		wk->sub_seq++;
		break;

	case 12:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			//�I�[�L�h�t�F�[�h�C��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );

			wk->sub_seq++;
		}
		break;

	case 13:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			if( wk->ret_work == SEQ_RIVAL_NAME ){
				wk->cancel = 1;
			}else{

				{
					/*******************/
					//MyStatus_SetMyName( my, wk->str );	//���C�o���̖��O�Z�b�g
					/*******************/
				}

			}

			return TRUE;
		}
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�FID�I��
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_IdChoice( OPENING_WORK* wk )
{
	u16 msg_id;

	switch( wk->sub_seq ){

	//�f�[�^�Z�b�g�Ȃ�
	case 0:
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//�I�[�L�h
		//OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//���C�o��
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//�e

#if 0
		//��b�E�B���h�E�\��
		opening_talk_win_put( wk );
		
		msg_id = (wk->cancel == 0) ? msg_opening_04 : msg_opening_05;
		wk->cancel = 0;

		//WORDSET_RegisterPlayerName( wk->wordset, 0, 
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
		//wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_07, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
#endif

		wk->sub_seq++;
		break;

	//�u���b�N�C��
	case 1:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		{
			//---------------------------------------------------------------
			//ID���V���b�t�����đI�ԏ������Ȃ��̂ŉ������AID���Z�b�g���Ă���
			//---------------------------------------------------------------
			
			//�I�����ʂ��猈�肵���g���[�i�[�^�C�v�̔ԍ����̂��̂��Z�o����
			int view = UnionView_GetTrainerType( 0x1234, wk->sex, 0 );

			//MYSTATUS�Ɏ����́u�����ځv���i�[����
			MyStatus_SetTrainerView( SaveData_GetMyStatus(wk->sv), view );
		}

		wk->sub_seq++;
		break;

	case 2:
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->count = 0;
			wk->sub_seq++;
		}
		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�F�`����
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	"TRUE = ���ցAFALSE = �p��"
 */
//--------------------------------------------------------------
static BOOL Seq_ToAdventure( OPENING_WORK* wk )
{
	u16 col;

	switch( wk->sub_seq ){

	//�f�[�^�Z�b�g�Ȃ�
	case 0:
		//��b�E�B���h�E�\��
		opening_talk_win_put( wk );
		
		WORDSET_RegisterPlayerName( wk->wordset, 0, SaveData_GetMyStatus(wk->sv) );//��l�����Z�b�g
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_06, 
		//wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_07, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	//�I�[�L�h��b�I���҂�
	case 1:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			//��b�E�B���h�E������
			BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

			OpeningOffBmpWin( wk->bmpwin );		//BMP�E�B���h�E�I�t

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
			//ChangeBrightnessRequest(OPENING_FADE_SYNC, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 
			//					PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);
			wk->sub_seq++;
		}
		break;

	//�I�[�L�h�t�F�[�h�A�E�g
	case 2:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

			wk->count = 15;
			wk->sub_seq++;
		}
		break;

	case 3:
		wk->count--;
		if( wk->count == 0 ){

			//�j����l��(256�F�A�g��k��)
			SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
			//�j����l��BG��\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

			wk->sub_seq++;
		}
		break;

	case 4:
		wk->count++;
		if( wk->count >= 10 ){
			wk->count = 0;
			wk->sub_seq++;
		}
		break;

	case 5:
#if 1
		OpeningAff( wk );
#else
		wk->count++;
		if( (wk->count % 10) == 0 ){
			OpeningAff( wk );
		}
#endif
		if( wk->ScaleX < AFF_SCALE_END ){ 
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	���O���͉�ʌĂяo��TCB
 *
 * @param	tcb			TCB�V�X�e�����[�N
 * @param	work		���[�N�G���A�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
typedef struct{
	int seq_no;
	u32 mode;
	OPENING_WORK* op_work;
	NAMEIN_PARAM* NameInParam;
	CONFIG*       config;
	PROC* proc;
}OPENING_NAMEIN_WORK;

static void OpeningNameInCall( OPENING_WORK* wk, u32 mode )
{
	OPENING_NAMEIN_WORK* name_wk;

	name_wk = sys_AllocMemory( HEAPID_OPENING, sizeof(OPENING_NAMEIN_WORK) );
	if( name_wk == NULL ){
		GF_ASSERT( (0) && "�������m�ێ��s�I" );
		return;
	}
	memset( name_wk, 0, sizeof(OPENING_NAMEIN_WORK) );
	name_wk->op_work = wk; 
	name_wk->mode	 = mode; 
	name_wk->config  = wk->config;

	wk->tcb	= TCB_Add( OpeningNameInMainTCB, name_wk, 0 );
	return;
}

static void OpeningNameInMainTCB(TCB_PTR tcb,void *work)
{
	OPENING_NAMEIN_WORK* wk = (OPENING_NAMEIN_WORK *)work;

	switch( wk->seq_no ){

	//�t�F�[�h�A�E�g
	case 0:
		wk->seq_no++;
		break;

	//�t�F�[�h�I���҂�
	case 1:
		//�폜����
		opening_end_sub( wk->op_work );

		//���O���͗p�������[�N�쐬
		if( wk->mode == OP_NAMEIN_MODE_HERO ){
			wk->NameInParam = NameIn_ParamAllocMake( HEAPID_OPENING, NAMEIN_MYNAME, 
														0, NAMEIN_PERSON_LENGTH, NULL );
			wk->NameInParam->info = wk->op_work->sex;	//�j��
		}else{
			wk->NameInParam = NameIn_ParamAllocMake( HEAPID_OPENING, NAMEIN_RIVALNAME,
														0, NAMEIN_PERSON_LENGTH, NULL );
			wk->NameInParam->info = PM_MALE;			//�j
		}

		wk->proc = PROC_Create( &NameInProcData, wk->NameInParam, HEAPID_OPENING );

		wk->seq_no++;
		break;

	//���O���͉�ʏI���҂�
	case 2:
		if( ProcMain(wk->proc) == TRUE ){

			STRBUF_GetStringCode( wk->NameInParam->strbuf, wk->op_work->str, 
										(PERSON_NAME_SIZE + EOM_SIZE) );

			//���A����
			PROC_Delete( wk->proc );

			//��ʍč\�z
			OpeningRecover( wk->op_work, wk->mode );

			//wordset���m�ۂ��Ă���Ă�
			if( wk->mode == OP_NAMEIN_MODE_HERO ){
				WORDSET_RegisterWord( wk->op_work->wordset, 0, wk->NameInParam->strbuf, 
										wk->op_work->sex, TRUE, PM_LANG );
			}else{
				WORDSET_RegisterWord( wk->op_work->wordset, 1, wk->NameInParam->strbuf, 
										PM_MALE, TRUE, PM_LANG );
			}

			NameIn_ParamDelete( wk->NameInParam );				//���O���̓��[�N�����
		
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
						WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

			wk->seq_no++;
		}
		break;

	//�t�F�[�h�C���I���҂�
	case 3:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->op_work->tcb = NULL;
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	��ʍč\�z
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningRecover( OPENING_WORK* wk, u32 mode )
{
	int i;

	opening_init_sub();
	
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OPENING );

	opening_init_sub2( wk );

	//�j����l��BG�\��
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

	OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//�I�[�L�h
	OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//���C�o��
	OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//�e

	//�������W�ɖ߂�
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//�I�[�L�h
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//���C�o��
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//�e

	//���ʔw�i
	SetBgGraphic_Sub4( wk, GF_BGL_FRAME2_M );
	
	//����ʔw�i
	SetBgGraphic_Sub5( wk, GF_BGL_FRAME2_S );

	//���[�h�ɂ�蕪��
	if( mode == OP_NAMEIN_MODE_HERO ){
		//�j����l��(256�F�A�g��k��)
		SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
	}else{
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//���C�o��

		//�j����l��BG�͏����Ă���
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���ʏ�����1
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_init_sub()
{
	WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
  
	sys_VBlankFuncChange( NULL, NULL );			//VBlank�Z�b�g
	sys_HBlankIntrSet( NULL,NULL );				//HBlank�Z�b�g
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );
	//sys_KeyRepeatSpeedSet( 4, 8 );
	return;	
}

//--------------------------------------------------------------
/**
 * @brief	���ʏ�����2
 *
 * @param	wk		OPENING_WORK�^�̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_init_sub2( OPENING_WORK* wk )
{
	int i;

	SetVramBank();

	SetBgHeader( wk->bgl );

	OpeningInitCellActor( &wk->ObjWork );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_HAKASE, OP_OBJ_HAKASE, 0 );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_RIVAL, OP_OBJ_RIVAL, 0 );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_KAGE, OP_OBJ_HAKASE, 1 );	

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
								NARC_msg_opening_dat, HEAPID_OPENING );

	wk->wordset = WORDSET_Create( HEAPID_OPENING );
	wk->msg_buf = STRBUF_Create( OPENING_MSG_BUF_SIZE, HEAPID_OPENING );
	wk->tmp_buf = STRBUF_Create( OPENING_MSG_BUF_SIZE, HEAPID_OPENING );

	//������o�b�t�@�쐬
	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		wk->menu_buf[i] = STRBUF_Create( OPENING_MENU_BUF_SIZE, HEAPID_OPENING );
	}

	//�t�H���g�p���b�g
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, OP_FONT_PAL * 32, HEAPID_OPENING );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, OP_MSGFONT_PAL * 32, HEAPID_OPENING );

	//�r�b�g�}�b�v�ǉ�
	OpeningAddBmpWin( wk->bgl, wk->bmpwin );

	//�p���b�g�t�F�[�h�V�X�e�����[�N�쐬
	wk->pfd = PaletteFadeInit( HEAPID_OPENING );

	//���N�G�X�g�f�[�^��malloc���ăZ�b�g
	PaletteFadeWorkAllocSet( wk->pfd, FADE_MAIN_OBJ, FADE_PAL_ALL_SIZE, HEAPID_OPENING );
	PaletteFadeWorkAllocSet( wk->pfd, FADE_MAIN_BG, FADE_PAL_ONE_SIZE*OP_DEMO_PAL, HEAPID_OPENING );

	//�I�[�L�h
	PaletteWorkSet_Arc(
			wk->pfd, ARC_OPENING_GRA, NARC_opening_op_hakase_NCLR,
			HEAPID_OPENING, FADE_MAIN_OBJ, 16*2*16, 0 );

	//���C�o��
	PaletteWorkSet_Arc(
			wk->pfd, ARC_OPENING_GRA, NARC_opening_op_rival_NCLR,
			HEAPID_OPENING, FADE_MAIN_OBJ, 16*1*16, 16*2 );

	//��l��BG
	if( PM_VERSION == VERSION_DIAMOND ){
		PaletteWorkSet_Arc(
				wk->pfd, ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR,
				HEAPID_OPENING, FADE_MAIN_BG, (16*2)*OP_DEMO_PAL, 0 );
	}else{
		PaletteWorkSet_Arc(
				wk->pfd, ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR,
				HEAPID_OPENING, FADE_MAIN_BG, (16*2)*OP_DEMO_PAL, 0 );
	}

	//sys_VBlankFuncChange( VBlankFunc, NULL );	//VBlank�Z�b�g
	sys_VBlankFuncChange( VBlankFunc, (void*)wk );	//VBlank�Z�b�g

	//������
	wk->ScaleX = 1 << FX32_SHIFT;
	wk->ScaleY = 1 << FX32_SHIFT;
	wk->cancel = 0;

	MsgPrintSkipFlagSet( MSG_SKIP_ON );	//�X�L�b�v�L��

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���ʏI��
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_end_sub( OPENING_WORK* wk )
{
	int i;

	// �p���b�g�t�F�[�h�J��
	PaletteFadeWorkAllocFree( wk->pfd, FADE_MAIN_OBJ );
	PaletteFadeWorkAllocFree( wk->pfd, FADE_MAIN_BG );

	//�p���b�g�t�F�[�h�V�X�e���J��
	PaletteFadeFree( wk->pfd );
	wk->pfd = NULL;

	OpeningAffReset();						//�g��k�����Z�b�g
	OpeningRereaseCellObject(&wk->ObjWork);	//2D�I�u�W�F�N�g�֘A�̈�J��
	MSGMAN_Delete( wk->msgman );			//���b�Z�[�W�}�l�[�W���J��
	WORDSET_Delete( wk->wordset );
	STRBUF_Delete( wk->msg_buf );			//���b�Z�[�W�o�b�t�@�J��
	STRBUF_Delete( wk->tmp_buf );			//���b�Z�[�W�o�b�t�@�J��

	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		STRBUF_Delete( wk->menu_buf[i] );	//���j���[�o�b�t�@�J��
	}

	OpeningExitBmpWin( wk->bmpwin );		//BMP�E�B���h�E�J��
	BgExit( wk->bgl );						//BGL�폜
	return;
}

//--------------------------------------------------------------
/**
 * @brief	��b�E�B���h�E�\��
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_talk_win_put( OPENING_WORK* wk )
{
	OpeningTalkWinPut( &wk->bmpwin[BMPWIN_OOKIDO], CONFIG_GetWindowType(wk->config) );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[BMPWIN_OOKIDO], FBMP_COL_WHITE );	//�h��Ԃ�
	return;
}

//--------------------------------------------------------------
/**
 * @brief	��l��BG�̃t�F�[�h�C��
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_hero_fade_in( OPENING_WORK* wk )
{
	u16 col;
	col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;

	PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, 0, 16, 0, col );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	��l��BG�̃t�F�[�h�A�E�g
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_hero_fade_out( OPENING_WORK* wk )
{
	u16 col;
	col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;

	//PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, 0, 0, 16, col );
	PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, -2, 0, 16, col );
	return;
}

#if 0
		//�E�B���h�E�ɃJ�[�\���摜��`��
		//BmpWin_DrawCursorImage(GF_BGL_BMPWIN* win, u32 x, u32 y);
#endif


