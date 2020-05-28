//==============================================================================================
/**
 * @file	intro.c
 * @brief	�Q�[���J�n�����f��
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
#include "system/savedata.h"
#include "system/palanm.h"
#include "system/msg_ds_icon.h"
#include "system/wordset.h"
#include "system/touch_subwindow.h"
#include "system/gra_tool.h"
#include "system/brightness.h"
#include "poketool/monsno.h"
#include "field/game_init.h"
#include "savedata/misc.h"
#include "savedata/config.h"
#include "system/main.h"
#include "system/gamestart.h"
#include "system/pmfprint.h"

#include "msgdata/msg_intro.h"

#include "application/namein.h"
#include "intro.naix"

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
	INTRO_SEQ_MAIN,
	INTRO_SEQ_EXIT,

	INTRO_SEQ_SUBPROC_CALL,
	INTRO_SEQ_SUBPROC_WAIT,
	INTRO_SEQ_SUBPROC_END,
};

//----------------------------------
//�^�錾
//----------------------------------
///	�^�C�g���S�̐���p���[�N�\����
typedef struct INTRO_DEMO_WORK_tag
{
	int					heapID; 
	SAVEDATA*			sv;			//�Z�[�u�f�[�^�|�C���^
	CONFIG*				config;		//�R���t�B�O�|�C���^

	int					subseq;
	int					subnextseq;
	PROC*				subproc;

	//�a�f�V�X�e���֘A
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;

	//�a�l�o���X�g�V�X�e���֘A
	int					listseq;
	GF_BGL_BMPWIN		listwin;
	BMPLIST_WORK*		list;
	BMP_MENULIST_DATA*	listdata;
	int					listres;

	//���b�Z�[�W�}�l�[�W���֘A
	MSGDATA_MANAGER*	msgman;
	int					msgseq;
	int					guideseq;
	int					msgID;
	STRBUF*				msgstr;
	void*				msgicon;
	WORDSET*			wordset;

	//�͂��E�������^�b�`�p�l���֘A
	TOUCH_SW_SYS*		tpSWsys;

	//���O���̓T�u�o�q�n�b�֘A
	TCB_PTR				namein_task; 
	NAMEIN_PARAM*		myname;
	NAMEIN_PARAM*		rivalname;

	//�������t�F�[�h�֐�
	int					alphafadeseq;
	int					alphaev1;
	int					alphaev2;

	//�����������ʕ���p
	u32					mysex;

	//�V�[���ݒ胂�[�h�p
	u8					maindisp_mode;
	u8					ppl1disp_mode;
	u8					ppl2disp_mode;
	u8					subdisp_mode;

	//��l���a�f�A�j���p
	u8					bganime_count_male;
	u8					bganime_count_wait_male;
	u8					bganime_count_female;
	u8					bganime_count_wait_female;

	//�E�G�C�g�J�E���^�[
	int					wait;
	//�ėp���[�N
	int					work[8];
}INTRO_DEMO_WORK;

//----------------------------------
//�萔�錾
//----------------------------------
//���b�Z�[�W�֐�����w���`
enum {
	A_BUTTON_WAIT = 0,
	A_BUTTON_NOWAIT,
};

//���b�Z�[�W�֐��V�[�P���X�i���o�[��`
enum{
	MSGSET = 0,
	MSGDRAW,
	MSGWAIT,
};

//���b�Z�[�W�֐�����w���`
enum {
	B_BUTTON_ENABLE = 0,
	B_BUTTON_DISABLE,
};

//���X�g�֐��V�[�P���X�i���o�[��`
enum {
	LISTSET = 0,
	LISTSELECT,
};

//���X�g�^�C�v
typedef enum {
	LISTTYPE_YESNO = 0,
	LISTTYPE_MENU,
	LISTTYPE_NAME,
}INTRO_LISTTYPE;

//�K�C�h�֐��V�[�P���X�i���o�[��`
enum{
	GUIDESET = 0,
	GUIDEDISPON,
	GUIDEFADEIN,
	GUIDEWAIT,
	GUIDEFADEOUT,
	GUIDEEND,
};

//�K�C�h�^�C�v
typedef enum {
	GUIDETYPE_OPERA = 0,
	GUIDETYPE_GUIDE,
}INTRO_GUIDETYPE;

//�w�i���[�h�ݒ�(MainDisp)
enum {
	BGTYPE_MAIN_NULL = 0,
	BGTYPE_MAIN_TUTORIAL1,
	BGTYPE_MAIN_TUTORIAL2,
	BGTYPE_MAIN_TUTORIAL3,
	BGTYPE_MAIN_GUIDE,
	BGTYPE_MAIN_END,
};

//�l�����[�h�ݒ�(MainDisp)
enum {
	BGTYPE_MPPL_NULL = 0,
	BGTYPE_MPPL_DOCTOR,
	BGTYPE_MPPL_HERO_0,
	BGTYPE_MPPL_HERO_1,
	BGTYPE_MPPL_HERO_2,
	BGTYPE_MPPL_HERO_3,
	BGTYPE_MPPL_HEROINE_0,
	BGTYPE_MPPL_HEROINE_1,
	BGTYPE_MPPL_HEROINE_2,
	BGTYPE_MPPL_HEROINE_3,
	BGTYPE_MPPL_RIVAL,
	BGTYPE_MPPL_POKEMON,
	BGTYPE_MPPL_END,
};

//�w�i���[�h�ݒ�(SubDisp)
enum {
	BGTYPE_SUB_NULL = 0,
	BGTYPE_SUB_TUTORIALBALL,
	BGTYPE_SUB_GUIDEBALL,
	BGTYPE_SUB_YESNO,
	BGTYPE_SUB_TOUCHBALL,
	BGTYPE_SUB_END,
};

//�������t�F�[�h�֐��V�[�P���X�i���o�[��`
enum {
	ALPHAFADEINIT = 0,
	ALPHAFADEIN,
	ALPHAFADEOUT,
	ALPHAFADEEND,
};

//�������t�F�[�h���[�h��`
enum {
	ALPHA_FADEIN = 0,
	ALPHA_FADEOUT,
};

//�X�N���[�����[�h��`
enum {
	SCROLL_CENTER = 0,
	SCROLL_RIGHT,
	SCROLL_LEFT,
};

//----------------------------------
//�O���֐���`
//----------------------------------
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

//----------------------------------
//�֐��錾
//----------------------------------
PROC_RESULT Intro_Init( PROC * proc, int * seq );
PROC_RESULT Intro_Main( PROC * proc, int * seq );
PROC_RESULT Intro_Exit( PROC * proc, int * seq );

static void Intro_VBlank( void* work );

static void Intro_VramBankSet( INTRO_DEMO_WORK* wk );
static void Intro_VramBankRelease( INTRO_DEMO_WORK* wk );
static void Intro_MsgDataSet( INTRO_DEMO_WORK* wk );
static void Intro_MsgDataRelease( INTRO_DEMO_WORK* wk );
static void Intro_InterFaceSet( INTRO_DEMO_WORK* wk );
static void Intro_InterFaceRelease( INTRO_DEMO_WORK* wk );

static void Intro_GraphicLoad( INTRO_DEMO_WORK* wk );
static void Intro_GraphicLoadSceneM( INTRO_DEMO_WORK* wk );
static void Intro_GraphicLoadScenePPL( INTRO_DEMO_WORK* wk );
static void Intro_GraphicLoadSceneS( INTRO_DEMO_WORK* wk );
static void Intro_GraphicLoadSceneBTN( INTRO_DEMO_WORK* wk );

static BOOL Intro_Seq_introduction( INTRO_DEMO_WORK * wk );
//----------------------------------
//�}�N���錾
//----------------------------------
#define KEYTRG( pattern )	( ( sys.trg & ( pattern ) ) == ( pattern ) )
#define KEYCNT( pattern )	( ( sys.cont & ( pattern ) ) == ( pattern ) )

#define FADE( pattern, col, heapID ) {						\
	WIPE_SYS_Start(	WIPE_PATTERN_WMS,pattern,pattern,col,	\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}
#define FADE_MAINONLY( pattern, col, heapID ) {				\
	WIPE_SYS_Start(	WIPE_PATTERN_M,pattern,pattern,col,		\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}
#define FADE_SUBONLY( pattern, col, heapID ) {				\
	WIPE_SYS_Start(	WIPE_PATTERN_S,pattern,pattern,col,		\
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
#define INTRO_TEXT_M_FRAME	(GF_BGL_FRAME0_M)
#define INTRO_PPL1_M_FRAME	(GF_BGL_FRAME1_M)
#define INTRO_PPL2_M_FRAME	(GF_BGL_FRAME2_M)
#define INTRO_BACK_M_FRAME	(GF_BGL_FRAME3_M)

#define INTRO_TEXT_S_FRAME	(GF_BGL_FRAME0_S)
#define INTRO_PPL1_S_FRAME	(GF_BGL_FRAME1_S)
#define INTRO_PBTN_S_FRAME	(GF_BGL_FRAME2_S)
#define INTRO_BACK_S_FRAME	(GF_BGL_FRAME3_S)

//���̑�
#define INTRO_MONSNO ( MONSNO_GONBE )

#define MSGSPD		( CONFIG_GetMsgPrintSpeed( wk->config ))
//=================================================================================================
//
// �o�q�n�b��`�e�[�u��
//
//=================================================================================================
const PROC_DATA IntroProcData = {
	Intro_Init,
	Intro_Main,
	Intro_Exit,
	NO_OVERLAY_ID
};

extern PROC_RESULT IntroTV_Init( PROC * proc, int * seq );
extern PROC_RESULT IntroTV_Main( PROC * proc, int * seq );
extern PROC_RESULT IntroTV_Exit( PROC * proc, int * seq );

static const PROC_DATA IntroTVProcData = {
	IntroTV_Init,
	IntroTV_Main,
	IntroTV_Exit,
	NO_OVERLAY_ID
};

//================================================================
//----------------------------------
//�o�q�n�b������
//----------------------------------
PROC_RESULT Intro_Init(PROC * proc, int * seq)
{
	INTRO_DEMO_WORK * wk;
	int	heapID = HEAPID_INTRO;

	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x40000 );

	wk = PROC_AllocWork( proc, sizeof( INTRO_DEMO_WORK ), heapID );
	memset( wk, 0, sizeof( INTRO_DEMO_WORK ) );

	wk->heapID	= heapID;
	wk->sv		= ((MAINWORK *)PROC_GetParentWork( proc ))->savedata;
	wk->config	= SaveData_GetConfig( wk->sv );	

	wk->subseq	= 0;
	wk->subnextseq = 0;
	wk->subproc	= NULL;
	wk->myname = NameIn_ParamAllocMake( heapID, NAMEIN_MYNAME, 0, NAMEIN_PERSON_LENGTH, wk->config );
	wk->rivalname = NameIn_ParamAllocMake( heapID, NAMEIN_RIVALNAME, 0, NAMEIN_PERSON_LENGTH, wk->config);
	wk->maindisp_mode	= BGTYPE_MAIN_NULL;
	wk->ppl1disp_mode	= BGTYPE_MPPL_NULL;
	wk->ppl2disp_mode	= BGTYPE_MPPL_NULL;
	wk->subdisp_mode	= BGTYPE_SUB_NULL;
	wk->wait			= 0;

	return	PROC_RES_FINISH;
}

//----------------------------------
//�o�q�n�b���C��
//----------------------------------
PROC_RESULT Intro_Main(PROC * proc, int* seq)
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

		Intro_VramBankSet( wk );
		Intro_MsgDataSet( wk );
		Intro_InterFaceSet( wk );

		sys_VBlankFuncChange(Intro_VBlank,(void*)wk);
		GF_Disp_DispOn();

		*seq = INTRO_SEQ_MAIN;
		break;

	// ���C�����[�v
	case INTRO_SEQ_MAIN:
		if( Intro_Seq_introduction( wk ) == TRUE ){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			*seq = INTRO_SEQ_EXIT;
		}
		if( wk->subproc != NULL ){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			*seq = INTRO_SEQ_SUBPROC_CALL;
		}
		break;

	// �I��
	case INTRO_SEQ_EXIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			Intro_MsgDataRelease( wk );
			Intro_VramBankRelease( wk );
			Intro_InterFaceRelease( wk );
			sys_VBlankFuncChange( NULL, NULL );

			result = PROC_RES_FINISH;
		}
		break;

	// �T�u�o�q�n�b�Ăяo��
	case INTRO_SEQ_SUBPROC_CALL:
		if(WIPE_SYS_EndCheck() == TRUE){
			Intro_MsgDataRelease( wk );
			Intro_VramBankRelease( wk );
			Intro_InterFaceRelease( wk );
			sys_VBlankFuncChange( NULL, NULL );

			*seq = INTRO_SEQ_SUBPROC_WAIT;
		}
		break;

	// �T�u�o�q�n�b�I���҂�
	case INTRO_SEQ_SUBPROC_WAIT:
		if( ProcMain( wk->subproc ) == TRUE ){
			PROC_Delete( wk->subproc );
			wk->subproc = NULL;

			*seq = INTRO_SEQ_SUBPROC_END;
		}
		break;

	// �T�u�o�q�n�b��蕜�A
	case INTRO_SEQ_SUBPROC_END:

		*seq = INTRO_SEQ_INIT;
		break;
	}
	return result;
}

//----------------------------------
//�o�q�n�b�I��
//----------------------------------
PROC_RESULT Intro_Exit(PROC * proc, int * seq)
{
	INTRO_DEMO_WORK * wk = PROC_GetWork( proc );
	int heapID = wk->heapID;

	//�p�����[�^�ݒ�	��l���̖��O������
	MyStatus_SetMyNameFromString( SaveData_GetMyStatus(wk->sv), wk->myname->strbuf );
	MyStatus_SetMySex( SaveData_GetMyStatus(wk->sv), wk->myname->info );
	{
		MISC* misc = SaveData_GetMisc( wk->sv );

		MISC_SetRivalName( misc, wk->rivalname->strbuf );
	}

	NameIn_ParamDelete( wk->myname );
	NameIn_ParamDelete( wk->rivalname );

	PROC_FreeWork( proc );
	sys_DeleteHeap( heapID );

	Main_SetNextProc( OVERLAY_ID_GAMESTART, &AfterOpeningProcData );
	return	PROC_RES_FINISH;
}


//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
static void Intro_VBlank(void* work)
{
	INTRO_DEMO_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}


//----------------------------------
//���[�J���֐��i�^�b�`�p�l���֘A�j
//----------------------------------
#define BALLSW_CENTER_X	(128)
#define BALLSW_CENTER_Y	(100)
//�{�[�����o�p( return : TRUE or FALSE )
static BOOL TouchPanel_BallEffect( void )
{
	BOOL result = FALSE;
	u16 x,y;

	if(sys.tp_trg){
		if(( sys.tp_x < 256 )&&( sys.tp_y < 192 )){
			if( sys.tp_x < BALLSW_CENTER_X ){
				x = BALLSW_CENTER_X - sys.tp_x;
			} else {
				x = sys.tp_x - BALLSW_CENTER_X;
			}
			if( sys.tp_y < BALLSW_CENTER_Y ){
				y = BALLSW_CENTER_Y - sys.tp_y;
			} else {
				y = sys.tp_y - BALLSW_CENTER_Y;
			}
			if( ( x*x + y*y ) <= 16*16 ){
				result = TRUE;
			}
		}
	}
	return result;
}


//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
#define INTRO_NULL_PALETTE	( 0x0000 )		//�a�f�o�b�N�O���E���h�p���b�g
#define PALSIZE				( 2*16 )

// �p���b�g�ݒ�(���C�����)
#define INTRO_BACKPLT_M_NUM		( 0 )			//�ʏ�w�i�i�ȉ��R�{���f�[�^�Z�b�g�j
#define INTRO_TUTPLT_M_NUM		( 1 )			//�`���[�g���A���w�i
#define INTRO_GUIDEPLT_M_NUM	( 2 )			//�ڂ�����K�C�h�w�i
#define INTRO_MWINPLT_M_NUM		( 3 )			//�V�X�e�����j���[�E�C���h�E
#define INTRO_TWINPLT_M_NUM		( 4 )			//��b�E�C���h�E
#define	INTRO_SYSFNTPLT_M_NUM	( 5 )			//�V�X�e���r�b�g�}�b�v
#define	INTRO_TKFNTPLT_M_NUM	( 6 )			//��b�r�b�g�}�b�v
#define	INTRO_PPL1PLT_M_NUM		( 7 )			//�l���a�f�P
#define	INTRO_PPL2PLT_M_NUM		( 8 )			//�l���a�f�Q
#define	INTRO_PPLNULLPLT_M_NUM	( 9 )			//�l���G�t�F�N�g

// �p���b�g�ݒ�(�T�u���)
#define INTRO_BACKPLT_S_NUM		( 0 )			//�ʏ�w�i�i�ȉ��T�{���f�[�^�Z�b�g�j
#define INTRO_BALLPLT_S_NUM		( 1 )			//�{�[���w�i
#define INTRO_GUIDEPLT_S_NUM	( 2 )			//�ڂ�����K�C�h�w�i
#define INTRO_TUTPLT_S_NUM		( 3 )			//�`���[�g���A���w�i
#define INTRO_TUTYNPLT_S_NUM	( 4 )			//�`���[�g���A���u�͂��E�������v�w�i
#define	INTRO_BTNYNPLT_S_NUM	( 5 )			//�{�^���u�͂��E�������v�i�ȉ��Q�{���f�[�^�Z�b�g�j
#define	INTRO_BTNYNPLT2_S_NUM	( 6 )			//�{�^���u�͂��E�������v
#define	INTRO_BTNBALLPLT_S_NUM	( 7 )			//�{�^���{�[���i�ȉ��R�{���f�[�^�Z�b�g�j
#define	INTRO_BTNBALLPLT1_S_NUM	( 8 )			//�{�^���{�[��
#define	INTRO_BTNBALLPLT2_S_NUM	( 9 )			//�{�^���{�[��
#define	INTRO_PPL1PLT_S_NUM		( 10 )			//�l���a�f�P
#define	INTRO_PPL2PLT_S_NUM		( 11 )			//�l���a�f�Q
#define	INTRO_PPLNULLPLT_S_NUM	( 10 )			//�l���G�t�F�N�g

// ��b�E�B���h�E�L�����iwindow.h�Q�Ɓj
#define INTRO_TWINCHR_SIZ	( TALK_WIN_CGX_SIZ )
#define INTRO_TWINCHR_NUM	( 0x400-INTRO_TWINCHR_SIZ )

// ���j���[�E�B���h�E�L�����iwindow.h�Q�Ɓj
#define INTRO_MWINCHR_SIZ	( MENU_WIN_CGX_SIZ )
#define INTRO_MWINCHR_NUM	( INTRO_TWINCHR_NUM - INTRO_MWINCHR_SIZ )

// �V�X�e���Ŏg�p����Ă���L�����N�^�[�J�n�ʒu
#define INTRO_TEXTSYSCHAR_END	( INTRO_MWINCHR_NUM )

#define BGCONTSET( frame, scr, cgx ){									\
	header.screenBase	= scr;											\
	header.charBase		= cgx;											\
	GF_BGL_BGControlSet( wk->bgl, frame, &header, GF_BGL_MODE_TEXT );	\
	GF_BGL_ScrClear( wk->bgl, frame );									\
}

static void Intro_VramBankSet( INTRO_DEMO_WORK* wk )
{
	{ //�u�q�`�l�ݒ�
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
			GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
			GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
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
		GF_BGL_BGCNT_HEADER header = {	0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										0, 0, GX_BG_EXTPLTT_01, 1, 0, 0, FALSE };
		// �e�L�X�g�a�f�ݒ�(BG0)
		BGCONTSET( INTRO_TEXT_M_FRAME, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x18000 )
		// �l���P�a�f�ݒ�(BG1)
		BGCONTSET( INTRO_PPL1_M_FRAME, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x14000 )
		// �l���Q�a�f�ݒ�(BG2)
		BGCONTSET( INTRO_PPL2_M_FRAME, GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x10000 )
		// �w�i�a�f�ݒ�(BG3)
		BGCONTSET( INTRO_BACK_M_FRAME, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x0c000 )

		//���b�Z�[�W�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
		TalkWinGraphicSet(	wk->bgl, INTRO_TEXT_M_FRAME, INTRO_TWINCHR_NUM, INTRO_TWINPLT_M_NUM,
							0, wk->heapID);
		//���j���[�E�C���h�E�L�������p���b�g�ǂݍ��݁i�E�C���h�E�O���j
		MenuWinGraphicSet(	wk->bgl,INTRO_TEXT_M_FRAME, INTRO_MWINCHR_NUM,INTRO_MWINPLT_M_NUM,
							0,wk->heapID);
		//�t�H���g�p���b�g�ǂݍ��݁i�V�X�e���j
		SystemFontPaletteLoad( PALTYPE_MAIN_BG, INTRO_SYSFNTPLT_M_NUM*PALSIZE, wk->heapID );
		//�t�H���g�p���b�g�ǂݍ��݁i��b�j
		TalkFontPaletteLoad( PALTYPE_MAIN_BG, INTRO_TKFNTPLT_M_NUM*PALSIZE, wk->heapID );
	}
	{ // �T�u�a�f�V�X�e���ݒ�
		GF_BGL_BGCNT_HEADER header = {	0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										0, 0, GX_BG_EXTPLTT_01, 0, 0, 0, FALSE };
		// �e�L�X�g�a�f�ݒ�(BG0)
		BGCONTSET( INTRO_TEXT_S_FRAME, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x18000 )
		// �͂��E�������a�f�ݒ�(BG1)
		BGCONTSET( INTRO_PPL1_S_FRAME, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x14000 )
		// �{�[���a�f�ݒ�(BG2)
		BGCONTSET( INTRO_PBTN_S_FRAME, GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x10000 )
		// �w�i�a�f�ݒ�(BG3)
		BGCONTSET( INTRO_BACK_S_FRAME, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x0c000 )
	}
	FRAME_ALLOFF
	Intro_GraphicLoad( wk );
	wk->alphafadeseq = ALPHAFADEINIT;
}

static void Intro_VramBankRelease( INTRO_DEMO_WORK* wk )
{
	FRAME_ALLOFF

	GF_BGL_BGControlExit( wk->bgl, INTRO_TEXT_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_PPL1_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_PPL2_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_BACK_M_FRAME );

	GF_BGL_BGControlExit( wk->bgl, INTRO_TEXT_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_PPL1_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_PBTN_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, INTRO_BACK_S_FRAME );

	sys_FreeMemoryEz( wk->bgl );
}


//----------------------------------
//���b�Z�[�W�ݒ�
//----------------------------------
static void Intro_MsgDataSet( INTRO_DEMO_WORK* wk )
{
	//���b�Z�[�W�f�[�^�ǂݍ���
	wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_intro_dat,wk->heapID );
	//���b�Z�[�W�\���V�X�e��������
	MSG_PrintInit();
	wk->msgicon = MSG_DsIconFlashAdd( NULL, MSG_DSI_MAINDISP, INTRO_TKFNTPLT_M_NUM, wk->heapID );
	wk->wordset = WORDSET_Create( wk->heapID );

	wk->msgseq		= MSGSET;
	wk->guideseq	= GUIDESET;
	wk->listseq		= LISTSET;
}

static void Intro_MsgDataRelease( INTRO_DEMO_WORK* wk )
{
	WORDSET_Delete( wk->wordset );
//	MSG_DsIconFlashReq( wk->msgicon, MSG_DSI_REQ_FREE );
	MSG_DsIconFlashDelete( wk->msgicon );
	//���b�Z�[�W�f�[�^�j��
	MSGMAN_Delete(wk->msgman);
}


//----------------------------------
//�C���^�[�t�F�[�X�ݒ�
//----------------------------------
static void Intro_InterFaceSet( INTRO_DEMO_WORK* wk )
{
	//�͂��E�������^�b�`�p�l���V�X�e���ǂݍ���
	wk->tpSWsys = TOUCH_SW_AllocWork( wk->heapID );
}

static void Intro_InterFaceRelease( INTRO_DEMO_WORK* wk )
{
	//�͂��E�������^�b�`�p�l���V�X�e���j��
	TOUCH_SW_FreeWork( wk->tpSWsys );
}

//----------------------------------
//�������t�F�[�h�C���A�E�g�i�a�f�O�C�P�C�Q�ɑ΂��āB�a�f�R�ʁi�w�i�j��Ώۂɂ���j
//----------------------------------
#define ALPHASET( plane, side ){														\
	if( side == 0 ){																	\
		G2_SetBlendAlpha(	plane,														\
			GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3,		\
			wk->alphaev1, wk->alphaev2 );												\
	} else {																			\
		G2S_SetBlendAlpha(	plane,														\
			GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3,		\
			wk->alphaev1, wk->alphaev2 );												\
	}																					\
}

static BOOL Intro_AlphaFade( INTRO_DEMO_WORK * wk,int frame, int type )
{
	BOOL result = FALSE;
	GXBlendPlaneMask plane1;
	int dispside;

	switch( frame ){
	default:
	case GF_BGL_FRAME0_M:
		plane1 = GX_BLEND_PLANEMASK_BG0;
		dispside = 0;
		break;
	case GF_BGL_FRAME1_M:
		plane1 = GX_BLEND_PLANEMASK_BG1;
		dispside = 0;
		break;
	case GF_BGL_FRAME2_M:
		plane1 = GX_BLEND_PLANEMASK_BG2;
		dispside = 0;
		break;
	case GF_BGL_FRAME0_S:
		plane1 = GX_BLEND_PLANEMASK_BG0;
		dispside = 1;
		break;
	case GF_BGL_FRAME1_S:
		plane1 = GX_BLEND_PLANEMASK_BG1;
		dispside = 1;
		break;
	case GF_BGL_FRAME2_S:
		plane1 = GX_BLEND_PLANEMASK_BG2;
		dispside = 1;
		break;
	}
	switch( wk->alphafadeseq ){
	case ALPHAFADEINIT:
		if( type == ALPHA_FADEIN ){
			wk->alphaev1 = 0;
			wk->alphaev2 = 16;
			wk->alphafadeseq = ALPHAFADEIN;
			ALPHASET( plane1, dispside )
			FRAME_ON( frame )
		} else {
			wk->alphaev1 = 16;
			wk->alphaev2 = 0;
			wk->alphafadeseq = ALPHAFADEOUT;
		}
		break;
	case ALPHAFADEIN:
		if( wk->alphaev2 ){
			wk->alphaev1++;
			wk->alphaev2--;
			ALPHASET( plane1, dispside )
		} else {
			wk->alphafadeseq = ALPHAFADEEND;
		}
		break;

	case ALPHAFADEOUT:
		if( wk->alphaev1 ){
			wk->alphaev1--;
			wk->alphaev2++;
			ALPHASET( plane1, dispside )
		} else {
			wk->alphafadeseq = ALPHAFADEEND;
			FRAME_OFF( frame )
		}
		break;

	case ALPHAFADEEND:
		G2_BlendNone();
		G2S_BlendNone();
		wk->alphafadeseq = ALPHAFADEINIT;
		result = TRUE;
		break;
	}
	return result;
}

//----------------------------------
//�ȈՃE�F�C�g
//----------------------------------
static BOOL Intro_Wait( INTRO_DEMO_WORK * wk, int wait )
{
	if( wk->wait < wait ){
		wk->wait++;
		return FALSE;
	} else {
		wk->wait = 0;
		return TRUE;
	}
}

//----------------------------------
//�a�f�X�N���[���p���b�g�ύX
//----------------------------------
static void Intro_BGscrPalChange( INTRO_DEMO_WORK * wk, int frame, int pal )
{
	GF_BGL_ScrPalChange( wk->bgl, frame, 0, 0, 32, 24, pal );
	GF_BGL_LoadScreenReq( wk->bgl, frame );
}

//----------------------------------
//�a�l�o�E�C���h�E�ݒ�
//----------------------------------
#define INTRO_STRBUF_SIZE		(0x400)	//���b�Z�[�W�o�b�t�@�T�C�Y

#define DOTSIZE					(8)

// ���b�Z�[�W�E�B���h�E�ifldbmp.h�Q�ƁA�b�f�w�ȊO�t�B�[���h�Ɠ����F�R�����g�͐��l�j
#define	INTRO_MSG_WIN_PX		(2)
#define	INTRO_MSG_WIN_PY		(19)
#define	INTRO_MSG_WIN_SX		(27)
#define	INTRO_MSG_WIN_SY		(4)
#define	INTRO_MSG_WIN_PAL		(INTRO_TKFNTPLT_M_NUM)
#define	INTRO_MSG_WIN_CGX		(INTRO_TEXTSYSCHAR_END-(INTRO_MSG_WIN_SX*INTRO_MSG_WIN_SY))

// �͂�/�������E�B���h�E�ifldbmp.h�Q�ƁA�b�f�w�ȊO�t�B�[���h�Ɠ����F�R�����g�͐��l�j
#define	INTRO_YESNO_WIN_PX		(2)
#define	INTRO_YESNO_WIN_PY		(3)
#define	INTRO_YESNO_WIN_SX		(6)
#define	INTRO_YESNO_WIN_SY		(4)
#define	INTRO_YESNO_WIN_PAL		(INTRO_SYSFNTPLT_M_NUM)
#define	INTRO_YESNO_WIN_CGX		(INTRO_MSG_WIN_CGX-(INTRO_YESNO_WIN_SX*INTRO_YESNO_WIN_SY))

// ���C�����j���[�E�B���h�E
#define	INTRO_MENU_WIN_PX		(1)
#define	INTRO_MENU_WIN_PY		(3)
#define	INTRO_MENU_WIN_SX		(16)
#define	INTRO_MENU_WIN_SY		(6)
#define	INTRO_MENU_WIN_PAL		(INTRO_SYSFNTPLT_M_NUM)
#define	INTRO_MENU_WIN_CGX		(INTRO_MSG_WIN_CGX-(INTRO_MENU_WIN_SX*INTRO_MENU_WIN_SY))

// ���O���X�g�E�B���h�E
#define	INTRO_NAME_WIN_PX		(2)
#define	INTRO_NAME_WIN_PY		(3)
#define	INTRO_NAME_WIN_SX		(14)
#define	INTRO_NAME_WIN_SY		(10)
#define	INTRO_NAME_WIN_PAL		(INTRO_SYSFNTPLT_M_NUM)
#define	INTRO_NAME_WIN_CGX		(INTRO_MSG_WIN_CGX-(INTRO_NAME_WIN_SX*INTRO_NAME_WIN_SY))

// �I�y���[�V�����E�B���h�E
#define	INTRO_OPERA_WIN_PX		(8)
#define	INTRO_OPERA_WIN_PY		(0)
#define	INTRO_OPERA_WIN_SX		(24)
#define	INTRO_OPERA_WIN_SY		(24)
#define	INTRO_OPERA_WIN_PAL		(INTRO_SYSFNTPLT_M_NUM)
#define	INTRO_OPERA_WIN_CGX		(INTRO_MSG_WIN_CGX-(INTRO_OPERA_WIN_SX*INTRO_OPERA_WIN_SY))

// �K�C�h�E�B���h�E
#define	INTRO_GUIDE_WIN_PX		(4)
#define	INTRO_GUIDE_WIN_PY		(0)
#define	INTRO_GUIDE_WIN_SX		(24)
#define	INTRO_GUIDE_WIN_SY		(24)
#define	INTRO_GUIDE_WIN_PAL		(INTRO_SYSFNTPLT_M_NUM)
#define	INTRO_GUIDE_WIN_CGX		(INTRO_MSG_WIN_CGX-(INTRO_GUIDE_WIN_SX*INTRO_GUIDE_WIN_SY))

//�r�b�g�}�b�v���X�g�\����
typedef struct INTRO_BMPLIST_tag
{
	u32 msgID;
	u32 retID;
}INTRO_BMPLIST_TBL;

static const BMPWIN_DAT msg_windata = {
	INTRO_TEXT_M_FRAME,INTRO_MSG_WIN_PX,INTRO_MSG_WIN_PY,
	INTRO_MSG_WIN_SX,INTRO_MSG_WIN_SY,INTRO_MSG_WIN_PAL,INTRO_MSG_WIN_CGX
};
static const BMPWIN_DAT yesno_windata = {
	INTRO_TEXT_M_FRAME,INTRO_YESNO_WIN_PX,INTRO_YESNO_WIN_PY,
	INTRO_YESNO_WIN_SX,INTRO_YESNO_WIN_SY,INTRO_YESNO_WIN_PAL,INTRO_YESNO_WIN_CGX 
};
static const BMPWIN_DAT menu_windata = {
	INTRO_TEXT_M_FRAME,INTRO_MENU_WIN_PX,INTRO_MENU_WIN_PY,
	INTRO_MENU_WIN_SX,INTRO_MENU_WIN_SY,INTRO_MENU_WIN_PAL,INTRO_MENU_WIN_CGX 
};
static const BMPWIN_DAT name_windata = {
	INTRO_TEXT_M_FRAME,INTRO_NAME_WIN_PX,INTRO_NAME_WIN_PY,
	INTRO_NAME_WIN_SX,INTRO_NAME_WIN_SY,INTRO_NAME_WIN_PAL,INTRO_NAME_WIN_CGX 
};
static const BMPWIN_DAT opera_windata = {
	INTRO_TEXT_M_FRAME,INTRO_OPERA_WIN_PX,INTRO_OPERA_WIN_PY,
	INTRO_OPERA_WIN_SX,INTRO_OPERA_WIN_SY,INTRO_OPERA_WIN_PAL,INTRO_OPERA_WIN_CGX 
};
static const BMPWIN_DAT guide_windata = {
	INTRO_TEXT_M_FRAME,INTRO_GUIDE_WIN_PX,INTRO_GUIDE_WIN_PY,
	INTRO_GUIDE_WIN_SX,INTRO_GUIDE_WIN_SY,INTRO_GUIDE_WIN_PAL,INTRO_GUIDE_WIN_CGX 
};

static const BMPLIST_HEADER listheader_default = {
	NULL,NULL,NULL,NULL,0,0,0,12,0,0,FBMP_COL_BLACK,FBMP_COL_WHITE,FBMP_COL_BLK_SDW,
	0,16,BMPLIST_NO_SKIP,FONT_SYSTEM,0
};						

static const INTRO_BMPLIST_TBL yesno_list[] = { 
	{msg_opening_24,1},{msg_opening_25,2}
};
static const INTRO_BMPLIST_TBL menu_list[] = { 
	{msg_opening_21,1},{msg_opening_22,2},{msg_opening_23,3}
};
static const INTRO_BMPLIST_TBL name_list_d[] = { 
	{msg_opening_26,1},{msg_opening_27,2},{msg_opening_28,3},{msg_opening_29,4},{msg_opening_30,5}
};
static const INTRO_BMPLIST_TBL name_list_p[] = { 
	{msg_opening_26,1},{msg_opening_31,2},{msg_opening_32,3},{msg_opening_33,4},{msg_opening_34,5}
};

//----------------------------------
//���b�Z�[�W�\��
//----------------------------------
static BOOL Intro_MsgPrint( INTRO_DEMO_WORK * wk,u32 msgID, int button_mode )
{
	BOOL result = FALSE;

	switch(wk->msgseq){
	case MSGSET:
		//�r�b�g�}�b�v�쐬
		GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&msg_windata );
		//�����N���A
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
						INTRO_MSG_WIN_SX*DOTSIZE,INTRO_MSG_WIN_SY*DOTSIZE);
		//���b�Z�[�W�E�C���h�E�����\��
		BmpTalkWinWrite(&wk->msgwin,WINDOW_TRANS_ON,INTRO_TWINCHR_NUM,INTRO_TWINPLT_M_NUM);

		MsgPrintSkipFlagSet( MSG_SKIP_ON );		// ���b�Z�[�W�X�L�b�v�L��
		MsgPrintAutoFlagSet( MSG_AUTO_OFF );	// ���b�Z�[�W�I�[�g���薳��

		//������̎擾
		{
			STRBUF*	msg_tmp = STRBUF_Create( INTRO_STRBUF_SIZE, wk->heapID );
			//������o�b�t�@�̍쐬
			wk->msgstr = STRBUF_Create(INTRO_STRBUF_SIZE, wk->heapID);	

			MSGMAN_GetString( wk->msgman, msgID, msg_tmp );
			WORDSET_RegisterWord( wk->wordset, 0, wk->myname->strbuf, wk->mysex, TRUE, PM_LANG );
			WORDSET_RegisterWord( wk->wordset, 1, wk->rivalname->strbuf, PM_MALE, TRUE, PM_LANG );
			WORDSET_ExpandStr( wk->wordset, wk->msgstr, msg_tmp );
			STRBUF_Delete( msg_tmp );
		}
		//������̕\��
		wk->msgID = GF_STR_PrintSimple(&wk->msgwin,FONT_TALK,wk->msgstr,0,0,MSGSPD,NULL);

		wk->msgseq = MSGDRAW;
		break;

	case MSGDRAW:
		//������`��҂�
		if(!(GF_MSG_PrintEndCheck(wk->msgID))){
			STRBUF_Delete(wk->msgstr);
			wk->msgseq = MSGWAIT;
		}
		break;

	case MSGWAIT:
		//�I���҂�
		if( ( button_mode != A_BUTTON_WAIT )||( KEYTRG( PAD_BUTTON_A )) ){
			GF_BGL_BmpWinDel(&wk->msgwin);
			wk->msgseq = MSGSET;
			result = TRUE;
		}
	}
	return result;
}

//----------------------------------
//���X�g�\���p�R�[���o�b�N
//----------------------------------
static void Intro_BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	if( mode == 0 ){//���������͖炳�Ȃ�
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

//----------------------------------
//���X�g�\��:BmpList�ݒ�Q��
//----------------------------------
static BOOL Intro_BmpList( INTRO_DEMO_WORK * wk, INTRO_LISTTYPE type, int button_mode )
{
	BOOL result = FALSE;
	BMPLIST_HEADER				listheader_tmp;
	const BMPWIN_DAT*			windata;
	const INTRO_BMPLIST_TBL*	list;
	int	i,count;

	switch( wk->listseq ){
	case LISTSET:
		switch( type ){
		default:
		case LISTTYPE_YESNO:
			windata	= &yesno_windata;
			list	= yesno_list;
			count	= NELEMS(yesno_list);
			break;
		case LISTTYPE_MENU:
			windata	= &menu_windata;
			list	= menu_list;
			count	= NELEMS(menu_list);
			break;
		case LISTTYPE_NAME:
			windata	= &name_windata;
			if( CasetteVersion == VERSION_DIAMOND ){
				list  = name_list_d;
				count = NELEMS(name_list_d);
			} else {
				list  = name_list_p;
				count = NELEMS(name_list_p);
			}
			break;
		}
		//���j���[�r�b�g�}�b�v�ǉ�
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->listwin, windata );
		//���j���[���X�g�p������o�b�t�@�쐬
		wk->listdata = BMP_MENULIST_Create( count, wk->heapID );
		//���j���[���X�g�p������o�b�t�@�擾
		for( i=0; i<count; i++ ){
			BMP_MENULIST_AddArchiveString(wk->listdata,wk->msgman,list[i].msgID,list[i].retID);
		}
		//���j���[�r�b�g�}�b�v���X�g�w�b�_�쐬
		listheader_tmp = listheader_default;
		listheader_tmp.list	= wk->listdata;
		listheader_tmp.count = count;
		listheader_tmp.line = count;
		listheader_tmp.call_back = Intro_BmpListMoveSeCall;
		listheader_tmp.win  = &wk->listwin;
		//���j���[�r�b�g�}�b�v���X�g�쐬
		wk->list = BmpListSet(&listheader_tmp,0,0,wk->heapID);
	
		//�E�C���h�E�i�O�g�j�`��
		BmpMenuWinWrite(listheader_tmp.win,WINDOW_TRANS_OFF,INTRO_MWINCHR_NUM,INTRO_MWINPLT_M_NUM);
		//�u�q�`�l�]��
		GF_BGL_BmpWinOn( &wk->listwin );

		wk->listseq = LISTSELECT;
		break;

	case LISTSELECT:
		wk->listres = BmpListMain(wk->list);
		if(wk->listres == BMPLIST_NULL){
				break;
		}
		if((wk->listres == BMPLIST_CANCEL)&&(button_mode == B_BUTTON_DISABLE)){
				break;
		}
		//�I�����X�g�폜����
		BmpMenuWinClear( &wk->listwin, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( &wk->listwin );
		BmpListExit( wk->list, NULL, NULL );
		BMP_MENULIST_Delete( wk->listdata );
		Snd_SePlay( SEQ_SE_DP_SELECT );

		wk->listseq = LISTSET;
		result = TRUE;
		break;
	}
	return result;
}

//----------------------------------
//�K�C�h�\��
//----------------------------------
static BOOL Intro_GuidePrint
			( INTRO_DEMO_WORK * wk,u32 msgID, INTRO_GUIDETYPE type, int pos_y, int siz_y )
{
	BOOL result = FALSE;
	BMPWIN_DAT	windata;

	switch(wk->guideseq){
	case GUIDESET:
		FRAME_OFF( INTRO_TEXT_M_FRAME )
		//������o�b�t�@�̍쐬
		wk->msgstr = STRBUF_Create(INTRO_STRBUF_SIZE, wk->heapID);	
		//������̎擾
		MSGMAN_GetString(wk->msgman,msgID,wk->msgstr);

		//�r�b�g�}�b�v�쐬�������N���A
		if( type == GUIDETYPE_GUIDE ){
			//�ڂ�����K�C�h�p
			windata = guide_windata;
			windata.pos_y = pos_y;
			windata.siz_y = siz_y;
			GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&windata );
			GF_BGL_BmpWinFill(&wk->msgwin,0,0,0,
						INTRO_GUIDE_WIN_SX*DOTSIZE,INTRO_GUIDE_WIN_SY*DOTSIZE);
			//������̕\��
			GF_STR_PrintColor(&wk->msgwin,FONT_SYSTEM,wk->msgstr,0,0,0,
							GF_PRINTCOLOR_MAKE(1, 2, 0),NULL);
		} else {
			//��������p
			windata = opera_windata;
			windata.pos_y = pos_y;
			windata.siz_y = siz_y;
			GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&windata );
			GF_BGL_BmpWinFill(&wk->msgwin,0,0,0,
						INTRO_OPERA_WIN_SX*DOTSIZE,INTRO_OPERA_WIN_SY*DOTSIZE);
			//������̕\��
			GF_STR_PrintColor(&wk->msgwin,FONT_SYSTEM,wk->msgstr,0,0,0,
							GF_PRINTCOLOR_MAKE(15, 2, 0),NULL);
		}
		STRBUF_Delete(wk->msgstr);
		wk->guideseq = GUIDEDISPON;
		break;

	case GUIDEDISPON:
		//�u�q�`�l�]��
		GF_BGL_BmpWinOn( &wk->msgwin );
		wk->guideseq = GUIDEFADEIN;
		break;

	case GUIDEFADEIN:
		if( Intro_AlphaFade( wk, INTRO_TEXT_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			wk->guideseq = GUIDEWAIT;
		}
		break;

	case GUIDEWAIT:
		//�I���҂�
		if( (KEYTRG( PAD_BUTTON_A ))||(KEYTRG( PAD_BUTTON_B )) ){
			Snd_SePlay( SEQ_SE_DP_SELECT );
			wk->guideseq = GUIDEFADEOUT;
		}
		break;

	case GUIDEFADEOUT:
		if( Intro_AlphaFade( wk, INTRO_TEXT_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			wk->guideseq = GUIDEEND;
		}
		break;

	case GUIDEEND:
		GF_BGL_BmpWinDel(&wk->msgwin);
		GF_BGL_ScrClear( wk->bgl, INTRO_TEXT_M_FRAME );
		wk->guideseq = GUIDESET;
		result = TRUE;
		break;
	}
	return result;
}


//----------------------------------
//�O���t�B�b�N�ǂݍ���
//���w�i�̓X�N���[���A
//	�l���̓L�����N�^�[�f�[�^�{�p���b�g�A
//	�{�^���̓X�N���[���{�L�����N�^�[�f�[�^�ɂ���ĕω�
//----------------------------------
static void Intro_GraphicLoad( INTRO_DEMO_WORK* wk )
{

	//���C����ʔw�i�L�����N�^�[
	ArcUtil_BgCharSet(	ARC_INTRO, NARC_intro_back_m_NCGR,
						wk->bgl, INTRO_BACK_M_FRAME, 0, 0, 0, wk->heapID );
	//NULL�L�����ݒ�
	GF_BGL_ClearCharSet( INTRO_TEXT_M_FRAME, 32, 0, wk->heapID );

	//�T�u��ʔw�i�L�����N�^�[
	ArcUtil_BgCharSet(	ARC_INTRO, NARC_intro_back_s_NCGR,
						wk->bgl, INTRO_BACK_S_FRAME, 0, 0, 0, wk->heapID );
	{//�p���b�g�i�o�[�W�����ɂ���ĕω��j
		int palIDm,palIDs;

		if( CasetteVersion == VERSION_DIAMOND ){
			palIDm = NARC_intro_back_m_d_NCLR;
			palIDs = NARC_intro_back_s_d_NCLR;
		} else {
			palIDm = NARC_intro_back_m_p_NCLR;
			palIDs = NARC_intro_back_s_p_NCLR;
		}
		ArcUtil_PalSet( ARC_INTRO, palIDm, PALTYPE_MAIN_BG, INTRO_BACKPLT_M_NUM * PALSIZE, 
						PALSIZE * 3, wk->heapID );
		ArcUtil_PalSet( ARC_INTRO, palIDs, PALTYPE_SUB_BG, INTRO_BACKPLT_M_NUM * PALSIZE, 
						PALSIZE * 5, wk->heapID );
	}
	Intro_GraphicLoadSceneM( wk );
	Intro_GraphicLoadScenePPL( wk );
	Intro_GraphicLoadSceneS( wk );

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, INTRO_NULL_PALETTE );	//�w�i�F������
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, INTRO_NULL_PALETTE );	//�w�i�F������
}


//----------------------------------
//�O���t�B�b�N�V�[���؂�ւ��ǂݍ��݁i���C���w�i�j
//----------------------------------
static void Intro_GraphicLoadSceneM( INTRO_DEMO_WORK* wk )
{
	int	dataIDTbl[] = { NARC_intro_back_m_null_NSCR,
						NARC_intro_back_m_t1_NSCR,
						NARC_intro_back_m_t2_NSCR,
						NARC_intro_back_m_t3_NSCR,
						NARC_intro_back_m_g_NSCR };

	if( wk->maindisp_mode >= BGTYPE_MAIN_END ){
			return;
	}
	ArcUtil_ScrnSet(	ARC_INTRO, dataIDTbl[ wk->maindisp_mode ],
						wk->bgl, INTRO_BACK_M_FRAME, 0, 0, 0, wk->heapID );
}


//----------------------------------
//�O���t�B�b�N�V�[���؂�ւ��ǂݍ��݁i���C���l���j
//----------------------------------
static void Intro_GraphicLoadScenePPL( INTRO_DEMO_WORK* wk )
{
	int	dataIDTbl[][2] = {	{ 0, 0 },	//�ǂݍ��݂Ȃ�
							{ NARC_intro_doctor_NCGR,		NARC_intro_doctor_NCLR },
							{ NARC_intro_hero_0_NCGR,		NARC_intro_hero_NCLR },
							{ NARC_intro_hero_1_NCGR,		NARC_intro_hero_NCLR },
							{ NARC_intro_hero_2_NCGR,		NARC_intro_hero_NCLR },
							{ NARC_intro_hero_3_NCGR,		NARC_intro_hero_NCLR },
							{ NARC_intro_heroine_0_NCGR,	NARC_intro_heroine_NCLR },
							{ NARC_intro_heroine_1_NCGR,	NARC_intro_heroine_NCLR },
							{ NARC_intro_heroine_2_NCGR,	NARC_intro_heroine_NCLR },
							{ NARC_intro_heroine_3_NCGR,	NARC_intro_heroine_NCLR },
							{ NARC_intro_rival_NCGR,		NARC_intro_rival_NCLR } };

	if(( wk->ppl1disp_mode != BGTYPE_MPPL_NULL )&&( wk->ppl1disp_mode < BGTYPE_MPPL_END )){
		ArcUtil_BgCharSet(	ARC_INTRO, dataIDTbl[ wk->ppl1disp_mode ][0],
							wk->bgl, INTRO_PPL1_M_FRAME, 0, 0, 0, wk->heapID );
		ArcUtil_PalSet( ARC_INTRO, dataIDTbl[ wk->ppl1disp_mode ][1],
						PALTYPE_MAIN_BG, INTRO_PPL1PLT_M_NUM * PALSIZE, PALSIZE, wk->heapID );
		ArcUtil_ScrnSet(	ARC_INTRO, NARC_intro_back_m_ppl_NSCR,
							wk->bgl, INTRO_PPL1_M_FRAME, 0, 0, 0, wk->heapID );
		Intro_BGscrPalChange( wk, INTRO_PPL1_M_FRAME, INTRO_PPL1PLT_M_NUM );
	}
	if(( wk->ppl2disp_mode != BGTYPE_MPPL_NULL )&&( wk->ppl2disp_mode < BGTYPE_MPPL_END )){
		ArcUtil_BgCharSet(	ARC_INTRO, dataIDTbl[ wk->ppl2disp_mode ][0],
							wk->bgl, INTRO_PPL2_M_FRAME, 0, 0, 0, wk->heapID );
		ArcUtil_PalSet( ARC_INTRO, dataIDTbl[ wk->ppl2disp_mode ][1],
						PALTYPE_MAIN_BG, INTRO_PPL2PLT_M_NUM * PALSIZE, PALSIZE, wk->heapID );
		ArcUtil_ScrnSet(	ARC_INTRO, NARC_intro_back_m_ppl_NSCR,
							wk->bgl, INTRO_PPL2_M_FRAME, 0, 0, 0, wk->heapID );
		Intro_BGscrPalChange( wk, INTRO_PPL2_M_FRAME, INTRO_PPL2PLT_M_NUM );
	}
}

//----------------------------------
//�O���t�B�b�N�V�[���؂�ւ��ǂݍ��݁i�T�u�w�i�j
//----------------------------------
static void Intro_GraphicLoadSceneS( INTRO_DEMO_WORK* wk )
{
	int	dataIDTbl[] = { NARC_intro_back_s_null_NSCR,
						NARC_intro_back_s_guide_NSCR,
						NARC_intro_back_s_guide_NSCR,
						NARC_intro_back_s_yn_NSCR,
						NARC_intro_back_s_ball_NSCR };

	if( wk->subdisp_mode >= BGTYPE_SUB_END ){
			return;
	}
	ArcUtil_ScrnSet(	ARC_INTRO, dataIDTbl[ wk->subdisp_mode ],
						wk->bgl, INTRO_BACK_S_FRAME, 0, 0, 0, wk->heapID );

	if( wk->subdisp_mode == BGTYPE_SUB_TUTORIALBALL ){
		Intro_BGscrPalChange( wk, INTRO_BACK_S_FRAME, INTRO_TUTPLT_S_NUM );
	} else if( wk->subdisp_mode == BGTYPE_SUB_GUIDEBALL ){
		Intro_BGscrPalChange( wk, INTRO_BACK_S_FRAME, INTRO_GUIDEPLT_S_NUM );
	}
}

//----------------------------------
//�O���t�B�b�N�ǂݍ��݁i�|�P�����j
//----------------------------------
#define MONSDATASIZE	( 10*10 )
static const u8 monscr_tbl[] = {
	 0, 1, 2, 3, 4, 5, 6, 7,64,65,
	 8, 9,10,11,12,13,14,15,66,67,
	16,17,18,19,20,21,22,23,68,69,
	24,25,26,27,28,29,30,31,70,71,
	32,33,34,35,36,37,38,39,72,73,
	40,41,42,43,44,45,46,47,74,75,
	48,49,50,51,52,53,54,55,76,77,
	56,57,58,59,60,61,62,63,78,79,
	80,81,82,83,88,89,90,91,96,97,
	84,85,86,87,92,93,94,95,98,99,
};

static const u16 monpal_null_tbl[] = {
	0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,
	0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,0x6a3c,
//	0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,
//	0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,0x54d9,
};

static void Intro_GraphicLoadScenePOKE( INTRO_DEMO_WORK* wk )
{
	SOFT_SPRITE_ARC ssa;
	void*	monsscr;
	void*	monscgx;
	void*	monspal;
	void*	monspal_null;

	int frame_m = INTRO_PPL2_M_FRAME;
	int frame_s = INTRO_PPL1_S_FRAME;
	int pal_m = INTRO_PPL2PLT_M_NUM;
	int pal_s = INTRO_PPL1PLT_S_NUM;
	int pal_m_null = INTRO_PPLNULLPLT_M_NUM;
	int pal_s_null = INTRO_PPLNULLPLT_S_NUM;

	//�A�[�J�C�u�t�@�C�����擾
	PokeGraArcDataGet( &ssa, INTRO_MONSNO, PARA_MALE, PARA_FRONT, PARA_NORMAL, 0, 0 );

	monsscr = sys_AllocMemory( wk->heapID, MONSDATASIZE*2 );
	{
		int	i;
		for( i=0; i<MONSDATASIZE; i++ ) ((u16*)monsscr)[i] = monscr_tbl[i]+1;
	}
	monscgx = ChangesInto_BattlePokeData_Alloc( ssa.arc_no, ssa.index_chr, wk->heapID );
	monspal = ChangesInto_BattlePokePalData_Alloc( ssa.arc_no, ssa.index_pal, wk->heapID );
	monspal_null = (void*)monpal_null_tbl;

	GF_BGL_ScrFill( wk->bgl, frame_m, 0, 0, 0, 32, 24, pal_m_null); 
	GF_BGL_ScrWrite( wk->bgl, frame_m, monsscr, 11, 11, 10, 10 ); 
	Intro_BGscrPalChange( wk, frame_m, pal_m_null );
	GF_BGL_ClearCharSet( frame_m, 32, 0, wk->heapID );
	GF_BGL_LoadCharacter( wk->bgl, frame_m, monscgx, MONSDATASIZE*0x20, 1 );
	GF_BGL_PaletteSet( frame_m, monspal, PALSIZE, PALSIZE*pal_m );
	GF_BGL_PaletteSet( frame_m, monspal_null, PALSIZE, PALSIZE*pal_m_null );

	GF_BGL_ScrFill( wk->bgl, frame_s, 0, 0, 0, 32, 24, pal_s_null); 
	GF_BGL_ScrWrite( wk->bgl, frame_s, monsscr, 11, 7, 10, 10 ); 
	Intro_BGscrPalChange( wk, frame_s, pal_s_null );
	GF_BGL_ClearCharSet( frame_s, 32, 0, wk->heapID );
	GF_BGL_LoadCharacter( wk->bgl, frame_s, monscgx, MONSDATASIZE*0x20, 1 );
	GF_BGL_PaletteSet( frame_s, monspal, PALSIZE, PALSIZE*pal_s );
	GF_BGL_PaletteSet( frame_s, monspal_null, PALSIZE, PALSIZE*pal_s_null );

	sys_FreeMemoryEz( monspal );
	sys_FreeMemoryEz( monscgx );
	sys_FreeMemoryEz( monsscr );
}


//----------------------------------
//�O���t�B�b�N�ǂݍ��݁i�T�u�{�^���j
//----------------------------------
static void Intro_GraphicLoadSceneBTN( INTRO_DEMO_WORK* wk )
{
	//�T�u�{�^���X�N���[��
	ArcUtil_ScrnSet(	ARC_INTRO, NARC_intro_button_s_ball_NSCR,
						wk->bgl, INTRO_PBTN_S_FRAME, 0, 0, 0, wk->heapID );
	Intro_BGscrPalChange( wk, INTRO_PBTN_S_FRAME, INTRO_BTNBALLPLT2_S_NUM );
	ArcUtil_PalSet(		ARC_INTRO, NARC_intro_button_s_NCLR, PALTYPE_SUB_BG, 
						INTRO_BTNBALLPLT_S_NUM * PALSIZE, PALSIZE * 3, wk->heapID );

	//NULL�L�����ݒ�
	GF_BGL_ClearCharSet( INTRO_PBTN_S_FRAME, 32, 0, wk->heapID );
	//�{�^���̓ǂݍ���
	ArcUtil_BgCharSet(	ARC_INTRO, NARC_intro_ball_button_0_NCGR,
						wk->bgl, INTRO_PBTN_S_FRAME, 0x20, 0, 0, wk->heapID );
}

//----------------------------------
//�X�N���[���i���C���l���j
//----------------------------------
static BOOL Intro_PPLScroll( INTRO_DEMO_WORK * wk,int frame, int type )
{
	BOOL result = FALSE;
	GXBlendPlaneMask plane1;

	if( type == SCROLL_CENTER ){
		{
			int scrx = GF_BGL_ScrollGetX( wk->bgl, frame );

			if( scrx != 0 ){
				if( scrx > 0 ){
					GF_BGL_ScrollSet( wk->bgl, frame, GF_BGL_SCROLL_X_DEC, 4 );
				} else {
					GF_BGL_ScrollSet( wk->bgl, frame, GF_BGL_SCROLL_X_INC, 4 );
				}
			} else {
				result = TRUE;
			}
		}
	}else if ( type == SCROLL_RIGHT ){
		if( GF_BGL_ScrollGetX( wk->bgl, frame ) != -8*6 ){
			GF_BGL_ScrollSet( wk->bgl, frame, GF_BGL_SCROLL_X_DEC, 4 );
		} else {
			result = TRUE;
		}
	}else if ( type == SCROLL_LEFT ){
		if( GF_BGL_ScrollGetX( wk->bgl, frame ) != 0 ){
			GF_BGL_ScrollSet( wk->bgl, frame, GF_BGL_SCROLL_X_INC, 4 );
		} else {
			result = TRUE;
		}
	}
	return result;
}


//----------------------------------
//�A�j���[�V�����i��l���j
//----------------------------------
static void Intro_MineAnimeInit( INTRO_DEMO_WORK * wk )
{
	wk->bganime_count_male			= 0;
	wk->bganime_count_wait_male		= 0;
	wk->bganime_count_female		= 0;
	wk->bganime_count_wait_female	= 0;
}

static void Intro_MineAnime( INTRO_DEMO_WORK * wk )
{
	if( wk->mysex == PM_MALE ){
		if( wk->bganime_count_wait_male ){
			wk->bganime_count_wait_male--;
		} else {
			wk->bganime_count_male++;
			wk->bganime_count_male &= 3;	//�S���
			wk->bganime_count_wait_male = 4;
		}
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 6, 10 );
		{
			int	dataIDTbl_Male[] = {	NARC_intro_hero_0_NCGR, NARC_intro_hero_1_NCGR,	
										NARC_intro_hero_2_NCGR,	NARC_intro_hero_3_NCGR };
			ArcUtil_BgCharSet(	ARC_INTRO, dataIDTbl_Male[ wk->bganime_count_male ],
								wk->bgl, INTRO_PPL1_M_FRAME, 0, 0, 0, wk->heapID );
		}
	} else {
		if( wk->bganime_count_wait_female ){
			wk->bganime_count_wait_female--;
		} else {
			wk->bganime_count_female++;
			wk->bganime_count_female &= 3;	//�S���
			wk->bganime_count_wait_female = 4;
		}
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, 6, 10 );
		{
			int	dataIDTbl_Female[] = {	NARC_intro_heroine_0_NCGR, NARC_intro_heroine_1_NCGR,	
										NARC_intro_heroine_2_NCGR,	NARC_intro_heroine_3_NCGR };

			ArcUtil_BgCharSet(	ARC_INTRO, dataIDTbl_Female[ wk->bganime_count_female ],
								wk->bgl, INTRO_PPL2_M_FRAME, 0, 0, 0, wk->heapID );
		}
	}
}

static void Intro_MineAnimeEnd( INTRO_DEMO_WORK * wk )
{
	G2_BlendNone();
}


//----------------------------------
//�k���A�j���[�V�����i��l���j
//----------------------------------
static void Intro_MineAnimeMinInit( INTRO_DEMO_WORK * wk )
{
	wk->work[0]	= 0;
	wk->work[1]	= 0;
}

static BOOL Intro_MineMinAnime( INTRO_DEMO_WORK * wk )
{
	BOOL result = FALSE;
	int dataID;

	if( wk->work[1] ){
		wk->work[1]--;
	} else {
		wk->work[0]++;
		wk->work[1] = 8;
	}
	if( wk->mysex == PM_MALE ){
		{
			int	dataIDTbl_Male[] = {	NARC_intro_hero_0_NCGR,		NARC_intro_hero_m1_NCGR,	
										NARC_intro_hero_m2_NCGR,	NARC_intro_hero_m3_NCGR,
										NARC_intro_hero_m4_NCGR,	0xff };
			dataID = dataIDTbl_Male[ wk->work[0] ];
		}
	} else {
		{
			int	dataIDTbl_Female[] = {	NARC_intro_heroine_0_NCGR,	NARC_intro_heroine_m1_NCGR,	
										NARC_intro_heroine_m2_NCGR,	NARC_intro_heroine_m3_NCGR,
										NARC_intro_heroine_m4_NCGR,	0xff };
	
			dataID = dataIDTbl_Female[ wk->work[0] ];
		}
	}
	if( dataID == 0xff ){
		result = TRUE;
	} else {
		ArcUtil_BgCharSet(	ARC_INTRO, dataID, wk->bgl, INTRO_PPL1_M_FRAME, 0, 0, 0, wk->heapID );
	}
	return result;
}


//----------------------------------
//�|�P�����o�ꉉ�o
//----------------------------------
#define POKE_FSTPOSY	(-8*13)
#define POKE_TOPPOSY	(8*14)
#define GRABITY_VAL		(9)
#define FIRSTSPEED		(8)

static BOOL Intro_PokeScroll( INTRO_DEMO_WORK * wk, int* seq )
{
	BOOL result = FALSE;

	switch( *seq ){
	case 0:
		GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_X_SET, 0 );
		GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_Y_SET, POKE_FSTPOSY );
		GF_BGL_PrioritySet( INTRO_PPL2_M_FRAME, 0 );
		FRAME_ON( INTRO_PPL1_S_FRAME )

		wk->work[5] = 0;
		wk->work[6] = FIRSTSPEED;
		wk->work[7] = 0;
		*seq = 1;
		break;

	case 1:
		{
			int scrx = GF_BGL_ScrollGetX( wk->bgl, INTRO_PPL2_M_FRAME );
			int scry = GF_BGL_ScrollGetY( wk->bgl, INTRO_PPL1_S_FRAME );

			int plus = wk->work[6] * GRABITY_VAL * wk->work[7];
			int minus = GRABITY_VAL * wk->work[7] * wk->work[7] / 2;
			int y = plus - minus;

			if( scry < 8*11 ){
				wk->work[7]++;
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_X_INC, 2 );
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL1_S_FRAME, GF_BGL_SCROLL_X_INC, 2 );
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL1_S_FRAME, GF_BGL_SCROLL_Y_SET, y );
			} else {
				FRAME_OFF( INTRO_PPL1_S_FRAME )
				wk->work[7] = 30;
				*seq = 2;
			}
		}
		break;

	case 2:
		if( wk->work[7] ){
			wk->work[7]--;
		} else {
			FRAME_ON( INTRO_PPL2_M_FRAME )
			wk->work[5] = 0;
#if 0
			wk->work[6] = FIRSTSPEED;
#else
			wk->work[6] = 9;
#endif
			wk->work[7] = 0;
			*seq = 3;
		}
		break;

	case 3:
		{
			int scrx = GF_BGL_ScrollGetX( wk->bgl, INTRO_PPL2_M_FRAME );
			int scry = GF_BGL_ScrollGetY( wk->bgl, INTRO_PPL2_M_FRAME );

			int plus = wk->work[6] * GRABITY_VAL * wk->work[7];
			int minus = GRABITY_VAL * wk->work[7] * wk->work[7] / 2;
			int y = POKE_FSTPOSY + plus - minus;

			if(( wk->work[5] > 0 ) && ( y <= 0 )){
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_Y_SET, 0 );
				wk->work[5] = 0;
				wk->work[6] = 1;
				wk->work[7] = 0;
				*seq = 4;
			} else {
				wk->work[7]++;
				wk->work[5] = y;
#if 0
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_X_INC, 2 );
#else
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_X_INC, 1 );
				y = y >> 1;
#endif
				if( y > 8*18 ){
					y = 8*18;
				}
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_Y_SET, y );
			}
		}
		break;

	case 4:
		{
			int scrx = GF_BGL_ScrollGetX( wk->bgl, INTRO_PPL2_M_FRAME );
			int scry = GF_BGL_ScrollGetY( wk->bgl, INTRO_PPL2_M_FRAME );

			int plus = wk->work[6] * GRABITY_VAL * wk->work[7];
			int minus = GRABITY_VAL * wk->work[7] * wk->work[7] / 2;
			int y = plus - minus;

			if(( wk->work[5] > 0 ) && ( y <= 0 )){
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_Y_SET, 0 );
				*seq = 5;
			} else {
				wk->work[7]++;
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_X_INC, 2 );
				GF_BGL_ScrollSet( wk->bgl, INTRO_PPL2_M_FRAME, GF_BGL_SCROLL_Y_SET, y );
				wk->work[5] = y;
			}
		}
		break;

	case 5:
		Snd_PMVoicePlay( INTRO_MONSNO );
	
		Intro_BGscrPalChange( wk, INTRO_PPL2_M_FRAME, INTRO_PPL2PLT_M_NUM );
		result = TRUE;
		break;
	}
	return result;
}

static void Intro_PokeScrollEnd( INTRO_DEMO_WORK * wk )
{
	GF_BGL_PrioritySet( INTRO_PPL2_M_FRAME, 1 );
}





//----------------------------------
//
//
//
//
//�V�[�P���X
//
//
//
//
//----------------------------------
#define SUBSEQ_RESET			{ wk->subseq = 0; }
#define SUBSEQ_SET( seq )		{ wk->subseq = seq; }
#define SUBNEXTSEQ_SET( seq, seqnext )	{	\
	wk->subnextseq = seqnext;				\
	wk->subseq = seq;						\
}
#define SUBNEXTSEQ_LOAD			{ wk->subseq = wk->subnextseq; }

#define INTRO_TEXT_FRAME_CLEAR	{ GF_BGL_ScrClear( wk->bgl, INTRO_TEXT_M_FRAME ); }
#define INTRO_BACK_M_SET( type ){		\
	wk->maindisp_mode = type;			\
	Intro_GraphicLoadSceneM( wk );		\
}
#define INTRO_PPL_SET( type1, type2 ){	\
	wk->ppl1disp_mode = type1;			\
	wk->ppl2disp_mode = type2;			\
	Intro_GraphicLoadScenePPL( wk );	\
}
#define INTRO_BACK_S_SET( type ){		\
	wk->subdisp_mode = type;			\
	Intro_GraphicLoadSceneS( wk );		\
}
#define FRAME_SCROLL_SET( frame, val )	\
	{ GF_BGL_ScrollSet( wk->bgl, frame, GF_BGL_SCROLL_X_SET, val ); }

#define INTRO_FLUSH_SET( sync, to, from  )	{											\
	ChangeBrightnessRequest( sync, to, from,											\
		( GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 ),	\
		MASK_MAIN_DISPLAY );															\
	ChangeBrightnessRequest( sync, to, from,											\
		( GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 ),	\
		MASK_SUB_DISPLAY );																\
}

#define INTRO_FLUSH_WAIT	( (IsFinishedBrightnessChg( MASK_MAIN_DISPLAY ) == TRUE )	\
							  &&(IsFinishedBrightnessChg( MASK_SUB_DISPLAY ) == TRUE ) )
		
enum{
	SEQ_0_0_00 = 0, SEQ_0_0_01,
	SEQ_1_1_00, 
	SEQ_1_2_00, SEQ_1_2_01, 
	SEQ_1_3_00, 
	SEQ_1_4_00, SEQ_1_4_01, SEQ_1_4_02, SEQ_1_4_03,
	SEQ_2_1_00, SEQ_2_1_01, SEQ_2_1_02,
	SEQ_2_2_00, SEQ_2_2_01, 
	SEQ_2_3_00, SEQ_2_3_01, 
	SEQ_2_4_00, SEQ_2_4_01, SEQ_2_4_02, 
	SEQ_2_5_00, SEQ_2_5_01, SEQ_2_5_02, SEQ_2_5_03, SEQ_2_5_04, SEQ_2_5_05, SEQ_2_5_06, 
	SEQ_2_6_00,
	SEQ_3_1_00, SEQ_3_1_01, SEQ_3_1_02,
	SEQ_4_1_00, SEQ_4_1_01, SEQ_4_1_02, SEQ_4_1_03, SEQ_4_1_04, 
				SEQ_4_1_05, SEQ_4_1_06, SEQ_4_1_07, SEQ_4_1_08, SEQ_4_1_09,
	SEQ_5_1_00, SEQ_5_1_01, 
	SEQ_5_2_00, SEQ_5_2_01, SEQ_5_2_02, SEQ_5_2_03, SEQ_5_2_04, SEQ_5_2_05, 
	SEQ_5_3_00, 
	SEQ_5_4_00, SEQ_5_4_01, SEQ_5_4_02, SEQ_5_4_03, 
	SEQ_5_5_00, SEQ_5_5_01, 
	SEQ_5_6_00, SEQ_5_6_01, 
	SEQ_5_7_00,	SEQ_5_7_01, SEQ_5_7_02, SEQ_5_7_03, SEQ_5_7_04,
	SEQ_6_1_00, SEQ_6_1_01, SEQ_6_1_02, SEQ_6_1_03, SEQ_6_1_04, 
	SEQ_6_2_00, SEQ_6_2_01, 
	SEQ_6_3_00, SEQ_6_3_01,
	SEQ_6_4_00, SEQ_6_4_01, SEQ_6_4_02,
	SEQ_7_1_00, 
	SEQ_7_2_00,	SEQ_7_2_01,	SEQ_7_2_02,
	SEQ_7_3_00, SEQ_7_3_01, SEQ_7_3_02,
	SEQ_8_1_00, SEQ_8_1_01, SEQ_8_1_02, SEQ_8_1_03, 
	SEQ_8_2_00, SEQ_8_2_01, SEQ_8_2_02, SEQ_8_2_03, SEQ_8_2_04, SEQ_8_2_05,
	SEQ_8_3_00,	SEQ_8_3_01,	SEQ_8_3_02,
	SEQ_8_4_00, SEQ_8_4_01, SEQ_8_4_02,
	SEQ_9_1_00, SEQ_9_1_01, SEQ_9_1_02, SEQ_9_1_03, SEQ_9_1_04, SEQ_9_1_05, 
	SEQ_9_2_00, SEQ_9_2_01, SEQ_9_2_02, SEQ_9_2_03,
	SEQ_10_1_00, 
	SEQ_11_1_00,
};

//----------------------------------
//����
//----------------------------------
static BOOL Intro_Seq_introduction( INTRO_DEMO_WORK * wk )
{
	BOOL result = FALSE;

	switch(wk->subseq){

//----------------------------------
	case SEQ_0_0_00:
		//PLAYER_BGM�Ń^�C�g���A�I�[�v�j���O��炷�悤�ɂ���
		Snd_DataSetByScene( SND_SCENE_OPENING, SEQ_OPENING, 1 );	//�I�[�v�j���O�ȍĐ�
		Snd_BgmStop( SEQ_OPENING, 0 );

		FRAME_ON( INTRO_TEXT_M_FRAME )
		FRAME_ON( INTRO_BACK_S_FRAME )
		//WIPE_ResetBrightness( WIPE_DISP_MAIN );
		//WIPE_ResetBrightness( WIPE_DISP_SUB );

		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_0_0_01 )
		break;

	case SEQ_0_0_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			if( Intro_Wait( wk, 40 ) == TRUE ){
				SUBSEQ_SET( SEQ_1_1_00 )
			}
		}
		break;

//----------------------------------
	case SEQ_1_1_00:
		if( Intro_MsgPrint( wk, msg_opening_01, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_1_2_00 )
			INTRO_TEXT_FRAME_CLEAR
		}
		break;

//----------------------------------
	case SEQ_1_2_00:
		Snd_BgmPlay( SEQ_OPENING );

		INTRO_PPL_SET( BGTYPE_MPPL_DOCTOR, BGTYPE_MPPL_NULL )
		FRAME_ON( INTRO_BACK_M_FRAME )
		FRAME_ON( INTRO_PPL1_M_FRAME )
		WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK,
						16, 4, wk->heapID );
		SUBSEQ_SET( SEQ_1_2_01 )
		break;

	case SEQ_1_2_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_1_3_00 )
		}
		break;

//----------------------------------
	case SEQ_1_3_00:
		if( Intro_MsgPrint( wk, msg_opening_02, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_1_4_00 )
		}
		break;

//----------------------------------
	case SEQ_1_4_00:
		if( Intro_PPLScroll( wk, INTRO_PPL1_M_FRAME, SCROLL_RIGHT ) == TRUE ){
			SUBSEQ_SET( SEQ_1_4_01 )
		}
		break;

	case SEQ_1_4_01:
		if( Intro_BmpList( wk, LISTTYPE_MENU, B_BUTTON_DISABLE ) == TRUE ){
			switch( wk->listres ){
			case 1:	//������@
				SUBNEXTSEQ_SET( SEQ_1_4_02, SEQ_2_1_00 )
				break;
			case 2:	//�ڂ�����K�C�h
				SUBNEXTSEQ_SET( SEQ_1_4_02, SEQ_4_1_00 )
				INTRO_TEXT_FRAME_CLEAR
				break;
			case 3:	//�I��
				SUBSEQ_SET( SEQ_5_1_00 )
				break;
			}
		}
		break;

	case SEQ_1_4_02:
		FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_1_4_03 )
		break;

	case SEQ_1_4_03:
		if(WIPE_SYS_EndCheck() == TRUE){
			INTRO_TEXT_FRAME_CLEAR
			FRAME_OFF( INTRO_PPL1_M_FRAME )
			SUBNEXTSEQ_LOAD
		}
		break;

//----------------------------------
	case SEQ_2_1_00:
		INTRO_BACK_M_SET( BGTYPE_MAIN_TUTORIAL1 )
		INTRO_BACK_S_SET( BGTYPE_SUB_TUTORIALBALL )
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_2_1_01 )
		break;

	case SEQ_2_1_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_2_1_02 )
		}
		break;

	case SEQ_2_1_02:
		if( Intro_GuidePrint( wk, msg_operation_01, GUIDETYPE_OPERA, 3, 18 ) == TRUE ){
			SUBSEQ_SET( SEQ_2_2_00 )
		}
		break;

//----------------------------------
	case SEQ_2_2_00:
		INTRO_BACK_M_SET( BGTYPE_MAIN_TUTORIAL2 )
		SUBSEQ_SET( SEQ_2_2_01 )
		break;

	case SEQ_2_2_01:
		if( Intro_GuidePrint( wk, msg_operation_02, GUIDETYPE_OPERA, 7, 10 ) == TRUE ){
			SUBSEQ_SET( SEQ_2_3_00 )
		}
		break;

//----------------------------------
	case SEQ_2_3_00:
		INTRO_BACK_M_SET( BGTYPE_MAIN_TUTORIAL3 )
		SUBSEQ_SET( SEQ_2_3_01 )
		break;

	case SEQ_2_3_01:
		if( Intro_GuidePrint( wk, msg_operation_03, GUIDETYPE_OPERA, 4, 12 ) == TRUE ){
			SUBSEQ_SET( SEQ_2_4_00 )
		}
		break;

//----------------------------------
	case SEQ_2_4_00:
		if( Intro_MsgPrint( wk, msg_opening_35, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_2_4_01 )
		}
		break;

	case SEQ_2_4_01:
		if( Intro_GuidePrint( wk, msg_operation_04, GUIDETYPE_OPERA, 4, 10 ) == TRUE ){
			SUBSEQ_SET( SEQ_2_4_02 )
			INTRO_TEXT_FRAME_CLEAR
		}
		break;

	case SEQ_2_4_02:
		FRAME_ON( INTRO_TEXT_M_FRAME )
		SUBSEQ_SET( SEQ_2_5_00 )
		break;

//----------------------------------
	case SEQ_2_5_00:
		if( Intro_MsgPrint( wk, msg_opening_03, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_2_5_01 )
		}
		break;

	case SEQ_2_5_01:
		{
			TOUCH_SW_PARAM tp_param = { NULL, INTRO_PBTN_S_FRAME, 1, 12,12, 8 };

			tp_param.p_bgl = wk->bgl;
			TOUCH_SW_Init( wk->tpSWsys, &tp_param );
			FRAME_ON( INTRO_PBTN_S_FRAME )
		}
		INTRO_BACK_S_SET( BGTYPE_SUB_YESNO )
		SUBSEQ_SET( SEQ_2_5_02 )
		break;

	case SEQ_2_5_02:
		if( sys.trg ){
			SUBSEQ_SET( SEQ_2_6_00 )
			break;
		}
		{
			int result = TOUCH_SW_MainMC( wk->tpSWsys );

			if( ( result == TOUCH_SW_RET_YES_TOUCH )||( result == TOUCH_SW_RET_NO_TOUCH ) ){
				SUBSEQ_SET( SEQ_2_5_03 )
			}
		}
		break;

	case SEQ_2_5_03:
		switch( TOUCH_SW_MainMC( wk->tpSWsys ) ){
		case TOUCH_SW_RET_YES:	//�͂�
			SUBSEQ_SET( SEQ_2_5_04 )
			break;
		case TOUCH_SW_RET_NO:	//������
			SUBSEQ_SET( SEQ_2_5_06 )
			break;
		}
		break;

	case SEQ_2_5_04:
		if( Intro_AlphaFade( wk, INTRO_PBTN_S_FRAME, ALPHA_FADEOUT ) == TRUE ){
			TOUCH_SW_Reset( wk->tpSWsys );
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			SUBSEQ_SET( SEQ_2_5_05 )
		}
		break;

	case SEQ_2_5_05:
		if(WIPE_SYS_EndCheck() == TRUE){
			INTRO_TEXT_FRAME_CLEAR
			SUBSEQ_SET( SEQ_3_1_00 )
		}
		break;

	case SEQ_2_5_06:
		if( Intro_AlphaFade( wk, INTRO_PBTN_S_FRAME, ALPHA_FADEOUT ) == TRUE ){
			INTRO_TEXT_FRAME_CLEAR
			TOUCH_SW_Reset( wk->tpSWsys );
			INTRO_BACK_M_SET( BGTYPE_MAIN_TUTORIAL1 )
			INTRO_BACK_S_SET( BGTYPE_SUB_TUTORIALBALL )
			SUBSEQ_SET( SEQ_2_1_02 )
		}
		break;

//----------------------------------
	case SEQ_2_6_00:
		if( Intro_MsgPrint( wk, msg_opening_04, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_2_5_02 )
		}
		break;

//----------------------------------
	case SEQ_3_1_00:
		INTRO_BACK_M_SET( BGTYPE_MAIN_NULL )
		INTRO_BACK_S_SET( BGTYPE_SUB_NULL )
		FRAME_ON( INTRO_PPL1_M_FRAME )
		FRAME_SCROLL_SET( INTRO_PPL1_M_FRAME, 0 )
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_3_1_01 )
		break;

	case SEQ_3_1_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_3_1_02 )
		}
		break;

	case SEQ_3_1_02:
		if( Intro_MsgPrint( wk, msg_opening_05, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_1_4_00 )
		}
		break;

//----------------------------------
	case SEQ_4_1_00:
		INTRO_BACK_M_SET( BGTYPE_MAIN_GUIDE )
		INTRO_BACK_S_SET( BGTYPE_SUB_GUIDEBALL )
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_4_1_01 )
		break;

	case SEQ_4_1_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_4_1_02 )
		}
		break;

	case SEQ_4_1_02:
		if( Intro_GuidePrint( wk, msg_guide_01, GUIDETYPE_GUIDE, 9, 6 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_03 )
		}
		break;

	case SEQ_4_1_03:
		if( Intro_GuidePrint( wk, msg_guide_02, GUIDETYPE_GUIDE, 8, 8 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_04 )
		}
		break;

	case SEQ_4_1_04:
		if( Intro_GuidePrint( wk, msg_guide_03, GUIDETYPE_GUIDE, 9, 6 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_05 )
		}
		break;

	case SEQ_4_1_05:
		if( Intro_GuidePrint( wk, msg_guide_04, GUIDETYPE_GUIDE, 5, 14 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_06 )
		}
		break;

	case SEQ_4_1_06:
		if( Intro_GuidePrint( wk, msg_guide_05, GUIDETYPE_GUIDE, 10, 4 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_07 )
		}
		break;

	case SEQ_4_1_07:
		if( Intro_GuidePrint( wk, msg_guide_06, GUIDETYPE_GUIDE, 6, 12 ) == TRUE ){
			SUBSEQ_SET( SEQ_4_1_08 )
		}
		break;

	case SEQ_4_1_08:
		FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_4_1_09 )
		break;

	case SEQ_4_1_09:
		if(WIPE_SYS_EndCheck() == TRUE){
			INTRO_TEXT_FRAME_CLEAR
			FRAME_ON( INTRO_TEXT_M_FRAME )
			SUBSEQ_SET( SEQ_3_1_00 )
		}
		break;

//----------------------------------
	case SEQ_5_1_00:
		if( Intro_PPLScroll( wk, INTRO_PPL1_M_FRAME, SCROLL_LEFT ) == TRUE ){
			SUBSEQ_SET( SEQ_5_1_01 )
		}
		break;

	case SEQ_5_1_01:
		if( Intro_MsgPrint( wk, msg_opening_06, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_5_2_00 )
		}
		break;

//----------------------------------
	case SEQ_5_2_00:
		FADE_SUBONLY( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_5_2_01 )
		break;

	case SEQ_5_2_01:
		if(WIPE_SYS_EndCheck() == TRUE){
			Intro_GraphicLoadSceneBTN( wk );
			INTRO_BACK_S_SET( BGTYPE_SUB_TOUCHBALL )
			FRAME_ON( INTRO_PBTN_S_FRAME )
			FADE_SUBONLY( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
			SUBSEQ_SET( SEQ_5_2_02 )
		}
		break;

	case SEQ_5_2_02:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_5_2_03 )
		}
		break;

	case SEQ_5_2_03:
		if( Intro_MsgPrint( wk, msg_opening_07, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_5_2_04 )
		}
		break;

	case SEQ_5_2_04:
		if( TouchPanel_BallEffect() == TRUE ){
			wk->work[0] = 0;	//�{�[���X�C�b�`�A�j���i���o�[
			wk->work[1] = 0;	//�{�[���X�C�b�`�A�j���J�E���^
			INTRO_TEXT_FRAME_CLEAR
			SUBSEQ_SET( SEQ_5_2_05 ) //�^�b�`�p�l���Ń{�[���̃{�^����������
		} else if( sys.trg ){
			SUBSEQ_SET( SEQ_5_3_00 ) //����ȊO�̃L�[
		}
		break;

	case SEQ_5_2_05:
		if( wk->work[1] ){
			wk->work[1]--;
		} else {
			{
				int	ballAnimeTbl[] = {	NARC_intro_ball_button_1_NCGR,
										NARC_intro_ball_button_2_NCGR,
										0xffff };

				if( ballAnimeTbl[ wk->work[0] ] == 0xffff){
					Snd_SePlay( SEQ_SE_DP_BOWA2 );

					SUBSEQ_SET( SEQ_5_4_00 )
				} else {
					//�{�^���̓ǂݍ���
					ArcUtil_BgCharSet(	ARC_INTRO, ballAnimeTbl[ wk->work[0] ],
										wk->bgl, INTRO_PBTN_S_FRAME, 0x20, 0, 0, wk->heapID );
					wk->work[0]++;
					wk->work[1] = 4;	//�{�[���X�C�b�`�A�j���J�E���^
				}
			}
		}
		break;

//----------------------------------
	case SEQ_5_3_00:
		if( Intro_MsgPrint( wk, msg_opening_08, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_5_2_04 )
		}
		break;

//----------------------------------
	case SEQ_5_4_00:
		INTRO_FLUSH_SET( 1, BRIGHTNESS_WHITE, BRIGHTNESS_NORMAL )
		SUBSEQ_SET( SEQ_5_4_01 )
		break;

	case SEQ_5_4_01:
		if( INTRO_FLUSH_WAIT ){
			INTRO_FLUSH_SET( 1, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE )
			SUBSEQ_SET( SEQ_5_4_02 )
		}
		break;

	case SEQ_5_4_02:
		if( INTRO_FLUSH_WAIT ){
			INTRO_FLUSH_SET( 4, BRIGHTNESS_WHITE, BRIGHTNESS_NORMAL )
			SUBSEQ_SET( SEQ_5_4_03 )
		}
		break;

	case SEQ_5_4_03:
		if( INTRO_FLUSH_WAIT ){
			SUBSEQ_SET( SEQ_5_5_00 )
		}
		break;

//----------------------------------
	case SEQ_5_5_00:
		Intro_GraphicLoadScenePOKE( wk );
		FRAME_OFF( INTRO_PBTN_S_FRAME )
		wk->work[0] = 0;
		Intro_PokeScroll( wk, &wk->work[0] );
		INTRO_BACK_S_SET( BGTYPE_SUB_NULL )
		INTRO_FLUSH_SET( 16, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE )
		SUBSEQ_SET( SEQ_5_5_01 )
		break;

	case SEQ_5_5_01:
		Intro_PokeScroll( wk, &wk->work[0] );
		if( INTRO_FLUSH_WAIT ){
			SUBSEQ_SET( SEQ_5_6_00 )
		}
		break;

//----------------------------------
	case SEQ_5_6_00:
		if( Intro_PokeScroll( wk, &wk->work[0] ) == TRUE ){
			SUBSEQ_SET( SEQ_5_6_01 )
		}
		break;

	case SEQ_5_6_01:
		if( Intro_Wait( wk, 40 ) == TRUE ){
			SUBSEQ_SET( SEQ_5_7_00 )
		}
		break;

//----------------------------------
	case SEQ_5_7_00:
		if( Intro_MsgPrint( wk, msg_opening_09, A_BUTTON_NOWAIT ) == TRUE ){
			INTRO_TEXT_FRAME_CLEAR
			SUBSEQ_SET( SEQ_5_7_01 )
		}
		break;

	case SEQ_5_7_01:
		if( Intro_AlphaFade( wk, INTRO_PPL2_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			Intro_PokeScrollEnd( wk );
			SUBSEQ_SET( SEQ_5_7_02 )
		}
		break;

	case SEQ_5_7_02:
		if( Intro_Wait( wk, 30 ) == TRUE ){
			SUBSEQ_SET( SEQ_5_7_03 )
		}
		break;

	case SEQ_5_7_03:
		if( Intro_MsgPrint( wk, msg_opening_36, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_5_7_04 )
		}
		break;

	case SEQ_5_7_04:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			SUBSEQ_SET( SEQ_6_1_00 )
		}
		break;

//----------------------------------
	case SEQ_6_1_00:
		Intro_MineAnimeInit( wk );
		INTRO_PPL_SET( BGTYPE_MPPL_HERO_0, BGTYPE_MPPL_HEROINE_0 )
		FRAME_SCROLL_SET( INTRO_PPL1_M_FRAME, -8*6 )
		FRAME_SCROLL_SET( INTRO_PPL2_M_FRAME, 8*6 )
		SUBSEQ_SET( SEQ_6_1_01 )
		break;

	case SEQ_6_1_01:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			SUBSEQ_SET( SEQ_6_1_02 )
		}
		break;

	case SEQ_6_1_02:
		if( Intro_AlphaFade( wk, INTRO_PPL2_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			SUBSEQ_SET( SEQ_6_1_03 )
		}
		break;

	case SEQ_6_1_03:
		if( Intro_MsgPrint( wk, msg_opening_10, A_BUTTON_NOWAIT ) == TRUE ){
			wk->mysex = PM_MALE;	//������
			SUBSEQ_SET( SEQ_6_1_04 )
		}
		break;

	case SEQ_6_1_04:
		if( KEYTRG( PAD_BUTTON_A ) ){
			wk->alphaev1 = 6;
			wk->alphaev2 = 10;
			wk->alphafadeseq = ALPHAFADEOUT;	//������肾���ǂ܂�������
			if( wk->mysex == PM_MALE ){
				SUBSEQ_SET( SEQ_6_2_00 )
			} else {
				SUBSEQ_SET( SEQ_6_3_00 )
			}
			break;
		}
		if( KEYTRG( PAD_KEY_LEFT ) || KEYTRG( PAD_KEY_RIGHT ) ){
			if( wk->mysex == PM_MALE ){
				wk->mysex = PM_FEMALE;
			} else {
				wk->mysex = PM_MALE;
			}
			Snd_SePlay( SEQ_SE_DP_SELECT );
		}
		Intro_MineAnime( wk );
		break;

//----------------------------------
	case SEQ_6_2_00:
		if( Intro_AlphaFade( wk, INTRO_PPL2_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			SUBSEQ_SET( SEQ_6_2_01 )
		}
		break;

	case SEQ_6_2_01:
		if( Intro_PPLScroll( wk, INTRO_PPL1_M_FRAME, SCROLL_CENTER ) == TRUE ){
			Intro_MineAnimeEnd( wk );
			SUBSEQ_SET( SEQ_6_4_00 )
		}
		break;

//----------------------------------
	case SEQ_6_3_00:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			SUBSEQ_SET( SEQ_6_3_01 )
		}
		break;

	case SEQ_6_3_01:
		if( Intro_PPLScroll( wk, INTRO_PPL2_M_FRAME, SCROLL_CENTER ) == TRUE ){
			Intro_MineAnimeEnd( wk );
			SUBSEQ_SET( SEQ_6_4_00 )
		}
		break;

//----------------------------------
	case SEQ_6_4_00:	//6-2,6-3����̔h��
		{
			u32 msgID;

			if( wk->mysex == PM_MALE ){
				msgID = msg_opening_11;
			} else {
				msgID = msg_opening_12;
			}
			if( Intro_MsgPrint( wk, msgID, A_BUTTON_NOWAIT ) == TRUE ){
				SUBSEQ_SET( SEQ_6_4_01 )
			}
		}
		break;

	case SEQ_6_4_01:
		if( Intro_BmpList( wk, LISTTYPE_YESNO, B_BUTTON_ENABLE ) == TRUE ){
			switch( wk->listres ){
			case 1:	//�͂�
				SUBSEQ_SET( SEQ_7_1_00 )
				break;
			case 2:	//������
			case BMPLIST_CANCEL:
				INTRO_TEXT_FRAME_CLEAR
				SUBSEQ_SET( SEQ_6_4_02 )
				break;
			}
		}
		break;

	case SEQ_6_4_02:
		{
			int frame;

			if( wk->mysex == PM_MALE ){
				frame = INTRO_PPL1_M_FRAME;
			} else {
				frame = INTRO_PPL2_M_FRAME;
			}
			if( Intro_AlphaFade( wk, frame, ALPHA_FADEOUT ) == TRUE ){
				SUBSEQ_SET( SEQ_6_1_00 )
			}
		}
		break;

//----------------------------------
	case SEQ_7_1_00:
		if( Intro_MsgPrint( wk, msg_opening_13, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_7_2_00 )
		}
		break;

//----------------------------------
	case SEQ_7_2_00:
		wk->myname->info = wk->mysex;
		wk->subproc = PROC_Create( &NameInProcData, wk->myname, wk->heapID );
		SUBSEQ_SET( SEQ_7_2_01 )
		break;

	case SEQ_7_2_01:
		FRAME_ON( INTRO_TEXT_M_FRAME )
		FRAME_ON( INTRO_BACK_M_FRAME )
		FRAME_ON( INTRO_BACK_S_FRAME )
		if( wk->mysex == PM_MALE ){
			FRAME_ON( INTRO_PPL1_M_FRAME )
			FRAME_SCROLL_SET( INTRO_PPL1_M_FRAME, 0 )
		} else {
			FRAME_ON( INTRO_PPL2_M_FRAME )
			FRAME_SCROLL_SET( INTRO_PPL2_M_FRAME, 0 )
		}
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_7_2_02 )
		break;

	case SEQ_7_2_02:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_7_3_00 )
		}
		break;

//----------------------------------
	case SEQ_7_3_00:
		{
			u32 msgID;
			int	mysex;

			if( wk->mysex == PM_MALE ){
				msgID = msg_opening_14;
			} else {
				msgID = msg_opening_15;
			}
			if( Intro_MsgPrint( wk, msgID, A_BUTTON_NOWAIT ) == TRUE ){
				SUBSEQ_SET( SEQ_7_3_01 )
			}
		}
		break;

	case SEQ_7_3_01:
		if( Intro_BmpList( wk, LISTTYPE_YESNO, B_BUTTON_ENABLE ) == TRUE ){
			INTRO_TEXT_FRAME_CLEAR
			switch( wk->listres ){
			case 1:	//�͂�
				SUBNEXTSEQ_SET( SEQ_7_3_02, SEQ_8_1_00 )
				break;
			case 2:	//������
			case BMPLIST_CANCEL:
				STRBUF_Clear( wk->myname->strbuf );
				SUBNEXTSEQ_SET( SEQ_7_3_02, SEQ_6_1_00 )
				break;
			}
		}
		break;

	case SEQ_7_3_02:
		{
			int frame;

			if( wk->mysex == PM_MALE ){
				frame = INTRO_PPL1_M_FRAME;
			} else {
				frame = INTRO_PPL2_M_FRAME;
			}
			if( Intro_AlphaFade( wk, frame, ALPHA_FADEOUT ) == TRUE ){
				SUBNEXTSEQ_LOAD
			}
		}
		break;

//----------------------------------
	case SEQ_8_1_00:
		INTRO_PPL_SET( BGTYPE_MPPL_DOCTOR, BGTYPE_MPPL_NULL )
		SUBSEQ_SET( SEQ_8_1_01 )
		break;

	case SEQ_8_1_01:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			SUBSEQ_SET( SEQ_8_1_02 )
		}
		break;

	case SEQ_8_1_02:
		if( Intro_MsgPrint( wk, msg_opening_16, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_1_03 )
		}
		break;

	case SEQ_8_1_03:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_2_00 )
		}
		break;

//----------------------------------
	case SEQ_8_2_00:
		INTRO_PPL_SET( BGTYPE_MPPL_RIVAL, BGTYPE_MPPL_NULL )
		SUBSEQ_SET( SEQ_8_2_01 )
		break;

	case SEQ_8_2_01:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			SUBSEQ_SET( SEQ_8_2_02 )
		}
		break;

	case SEQ_8_2_02:
		if( Intro_MsgPrint( wk, msg_opening_17, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_2_03 )
		}
		break;

	case SEQ_8_2_03:
		if( Intro_PPLScroll( wk, INTRO_PPL1_M_FRAME, SCROLL_RIGHT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_2_04 )
		}
		break;

	case SEQ_8_2_04:
		if( Intro_BmpList( wk, LISTTYPE_NAME, B_BUTTON_DISABLE ) == TRUE ){
			switch( wk->listres ){
			case 1:	//���Ԃ�ł��߂�
				SUBSEQ_SET( SEQ_8_3_00 )
				break;
			case 2:	//�f�t�H���g�P
			case 3:	//�f�t�H���g�Q
			case 4:	//�f�t�H���g�R
			case 5:	//�f�t�H���g�S
				{
					u32 msgID;

					if( CasetteVersion == VERSION_DIAMOND ){
						msgID = name_list_d[ wk->listres - 1 ].msgID;
					} else {
						msgID = name_list_p[ wk->listres - 1 ].msgID;
					}
					//������̎擾
					{
						STRBUF* str = MSGMAN_AllocString( wk->msgman, msgID );
						STRBUF_Copy( wk->rivalname->strbuf, str );
						STRBUF_Delete( str );
					}
				}
				SUBSEQ_SET( SEQ_8_2_05 )
				break;
			}
		}
		break;

	case SEQ_8_2_05:
		if( Intro_PPLScroll( wk, INTRO_PPL1_M_FRAME, SCROLL_LEFT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_4_00 )
		}
		break;

//----------------------------------
	case SEQ_8_3_00:
		wk->subproc = PROC_Create( &NameInProcData, wk->rivalname, wk->heapID );
		SUBSEQ_SET( SEQ_8_3_01 )
		break;

	case SEQ_8_3_01:
		FRAME_ON( INTRO_TEXT_M_FRAME )
		FRAME_ON( INTRO_BACK_M_FRAME )
		FRAME_ON( INTRO_BACK_S_FRAME )
		FRAME_ON( INTRO_PPL1_M_FRAME )
		FRAME_SCROLL_SET( INTRO_PPL1_M_FRAME, 0 )
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		SUBSEQ_SET( SEQ_8_3_02 )
		break;

	case SEQ_8_3_02:
		if(WIPE_SYS_EndCheck() == TRUE){
			SUBSEQ_SET( SEQ_8_4_00 )
		}
		break;

//----------------------------------
	case SEQ_8_4_00:
		if( Intro_MsgPrint( wk, msg_opening_18, A_BUTTON_NOWAIT ) == TRUE ){
			SUBSEQ_SET( SEQ_8_4_01 )
		}
		break;

	case SEQ_8_4_01:
		if( Intro_BmpList( wk, LISTTYPE_YESNO, B_BUTTON_ENABLE ) == TRUE ){
			switch( wk->listres ){
			case 1:	//�͂�
				INTRO_TEXT_FRAME_CLEAR
				SUBSEQ_SET( SEQ_8_4_02 )
				break;
			case 2:	//������
			case BMPLIST_CANCEL:
				STRBUF_Clear( wk->rivalname->strbuf );
				SUBSEQ_SET( SEQ_8_2_02 )
				break;
			}
		}
		break;

	case SEQ_8_4_02:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			SUBSEQ_SET( SEQ_9_1_00 )
		}
		break;

//----------------------------------
	case SEQ_9_1_00:
		INTRO_PPL_SET( BGTYPE_MPPL_DOCTOR, BGTYPE_MPPL_NULL )
		SUBSEQ_SET( SEQ_9_1_01 )
		break;

	case SEQ_9_1_01:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			SUBSEQ_SET( SEQ_9_1_02 )
		}
		break;

	case SEQ_9_1_02:
		if( Intro_Wait( wk, 30 ) == TRUE ){
			SUBSEQ_SET( SEQ_9_1_03 )
		}
		break;

	case SEQ_9_1_03:
		if( Intro_MsgPrint( wk, msg_opening_19, A_BUTTON_NOWAIT ) == TRUE ){
			Snd_BgmFadeOut( 0, 50 );
			SUBSEQ_SET( SEQ_9_1_04 )
		}
		break;

	case SEQ_9_1_04:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEOUT ) == TRUE ){
			INTRO_TEXT_FRAME_CLEAR
			SUBSEQ_SET( SEQ_9_1_05 )
		}
		break;

	case SEQ_9_1_05:
		if( Intro_Wait( wk, 30 ) == TRUE ){
			SUBSEQ_SET( SEQ_9_2_00 )
		}
		break;

//----------------------------------
	case SEQ_9_2_00:
		if( wk->mysex == PM_MALE ){
			INTRO_PPL_SET( BGTYPE_MPPL_HERO_0, BGTYPE_MPPL_NULL )
		} else {
			INTRO_PPL_SET( BGTYPE_MPPL_HEROINE_0, BGTYPE_MPPL_NULL )
		}
		SUBSEQ_SET( SEQ_9_2_01 )
		break;

	case SEQ_9_2_01:
		if( Intro_AlphaFade( wk, INTRO_PPL1_M_FRAME, ALPHA_FADEIN ) == TRUE ){
			Intro_MineAnimeMinInit( wk );
			SUBSEQ_SET( SEQ_9_2_02 )
		}
		break;

	case SEQ_9_2_02:
		if( Intro_Wait( wk, 30 ) == TRUE ){
			SUBSEQ_SET( SEQ_9_2_03 )
		}
		break;

	case SEQ_9_2_03:
		if( Intro_MineMinAnime( wk ) == TRUE ){
			SUBSEQ_SET( SEQ_10_1_00 )
		}
		break;

//----------------------------------
	case SEQ_10_1_00:
		wk->subproc = PROC_Create( &IntroTVProcData, NULL, wk->heapID );
		SUBSEQ_SET( SEQ_11_1_00 )
		break;

//----------------------------------
	case SEQ_11_1_00:
		result = TRUE;	
		break;
//----------------------------------
	}
	return result;	
}



