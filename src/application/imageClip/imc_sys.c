//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_sys.c
 *	@brief		�C���[�W�N���b�v���C���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include <string.h>
#include "touchpanel_system.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"
#include "include/contest/contest.h"
#include "src/contest/comm_command_contest.h"
#include "include/communication/comm_tool.h"

#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_left_box.h"
#include "include/application/imageClip/imc_hand.h"
#include "include/application/imageClip/imc_acce_hand.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_button.h"
#include "include/system/wipe.h"
#include "include/application/imageClip/imc_subwin.h"
#include "include/application/imageClip/imc_rbox_player.h"
#include "include/application/imageClip/imc_snd_def.h"
#include "include/application/imageClip/imc_item_buff.h"

#include "include/system/pmfprint.h"

#include "include/communication/wm_icon.h"

#include "imc_calc.h"


#define __IMC_SYS_H_GLOBAL
#include "include/application/imageClip/imc_sys.h"


#ifdef PM_DEBUG

#define IMC_DEBUG

#endif


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���C���v���b�N
//	�V�[�P���X�ݒ�
//	
//=====================================
enum{
	IMC_SYS_SEQ_START_TIMING_WAIT,
	IMC_SYS_SEQ_FADE_IN,
	IMC_SYS_SEQ_FADE_IN_WAIT,
	IMC_SYS_SEQ_REFERENCE_ON,
	IMC_SYS_SEQ_REFARENCE_WAIT,
	IMC_SYS_SEQ_KET_WAIT,
	IMC_SYS_SEQ_MAIN,			// �C���[�W�N���b�v�쐬���C��
	IMC_SYS_SEQ_END_CHECK_WAIT,
	IMC_SYS_SEQ_END_CHECK,		// �I���`�F�b�N
	IMC_SYS_SEQ_SAVE_CHECK,		// �Z�[�u�`�F�b�N
	IMC_SYS_SEQ_MAIN_WAIT,
	IMC_SYS_SEQ_FADE_OUT,
	IMC_SYS_SEQ_FADE_OUT_WAIT,
};

//-------------------------------------
//	
//	���C���v���b�N
//	�V�[�P���X�ݒ�
//	�R���e�X�g
//	
//=====================================
enum{
	IMC_SYS_CON_SEQ_CON_SND_FADE,
	IMC_SYS_CON_SEQ_CON_SND_FADE_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_THEME_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_THEME_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_DOUKI,
	IMC_SYS_CON_SEQ_START_TIMING_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_END,
	IMC_SYS_CON_SEQ_FADE_IN,
	IMC_SYS_CON_SEQ_FADE_IN_WAIT,
	IMC_SYS_CON_SEQ_MAIN,			// �C���[�W�N���b�v�쐬���C��
	IMC_SYS_CON_SEQ_EX_END_WAIT,	// �����I���҂�
	IMC_SYS_CON_SEQ_END_CHECK_WAIT,
	IMC_SYS_CON_SEQ_END_CHECK,		// �I���`�F�b�N
	IMC_SYS_CON_SEQ_SAVE_CHECK,		// �Z�[�u�`�F�b�N
	IMC_SYS_CON_SEQ_MAIN_WAIT,
	IMC_SYS_CON_SEQ_FADE_OUT,
	IMC_SYS_CON_SEQ_FADE_OUT_WAIT,
};

//-------------------------------------
//	
//	���s���
//	
//=====================================
enum{
	IMC_SYS_ACCE,		// �A�N�Z�T���ύX
	IMC_SYS_BG,			// BG�ύX
	IMC_SYS_SND,		// �T�E���h�ύX
	IMC_SYS_END_CHECK_REQ,// �I���`�F�b�N���N�G�X�g
	IMC_SYS_END_CHECK,	// �I���`�F�b�N
	IMC_SYS_SAVE_CHECK_REQ,	// �Z�[�u�`�F�b�N
	IMC_SYS_SAVE,		// �Z�[�u�`�F�b�N
	IMC_SYS_SAVE_CAN,	// �Z�[�uCANCEL
	IMC_SYS_END_REQ,	// �I�����N�G�X�g
	IMC_SYS_END_CANCEL_REQ,	// �I���L�����Z�����N�G�X�g
	IMC_SYS_END,		// �I��
};

//-------------------------------------
//	
//	�I���m�F��ʂւ̃t�F�[�h
//	
//=====================================
enum
{
	IMC_SEENFADEIN_ACCE_FADEOUT,
	IMC_SEENFADEIN_ACCE_FADEWAIT,
	IMC_SEENFADEIN_BRIGHTNESS_OUT,
	IMC_SEENFADEIN_BRIGHTNESS_WAIT,
	IMC_SEENFADEIN_BUTTON_OLDOUT,
//	IMC_SEENFADEIN_BUTTON_CHG,
	IMC_SEENFADEIN_MOVE_BG,
	IMC_SEENFADEIN_MOVE_BGINIT,
//	IMC_SEENFADEIN_BUTTON_NEWIN,
	IMC_SEENFADEIN_BRIGHTNESS_IN,
	IMC_SEENFADEIN_BRIGHTNESS_INWAIT,
	IMC_SEENFADEIN_END
};
enum
{
	IMC_SEENFADEOUT_BRIGHTNESS_OUT,
	IMC_SEENFADEOUT_BRIGHTNESS_OUTWAIT,
//	IMC_SEENFADEOUT_BUTTON_OLDOUT,
//	IMC_SEENFADEOUT_BUTTON_CHG,
	IMC_SEENFADEOUT_MOVE_BG_SET,
	IMC_SEENFADEOUT_MOVE_BG,
	IMC_SEENFADEOUT_BUTTON_NEWIN,
	IMC_SEENFADEOUT_BRIGHTNESS_IN,
	IMC_SEENFADEOUT_BRIGHTNESS_WAIT,
	IMC_SEENFADEOUT_ACCE_FADEIN,
	IMC_SEENFADEOUT_ACCE_FADEWAIT,
	IMC_SEENFADEOUT_END
};

//-------------------------------------
//	�A�N�Z�T�����Ȃ����ă|�P�����Ƃ������Ă��邩
//	�`�F�b�N����V�X�e���̃I�u�W�F�N�g��
//=====================================
#define IMC_POKEON_ACCE_CHECK_OBJNUM	( IMC_RBOX_OBJ_CONTEST_MAX )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�C���[�W�N���b�v�f�[�^�\����
//	
//=====================================
typedef struct {
	// �`��֌W
	IMC_DRAW_DATA drawSys;

	// �A�C�e���o�b�t�@
	IMC_ITEM_BUFF item_buff;

	// �I�u�W�F�N�g���X�g�f�[�^
	IMC_OBJLIST_TBL	objListTbl;

	// �A�N�Z�T���f�[�^
	IMC_ACCESSORIE_OBJ_TBL* acce;

	// ����ʃf�[�^
	IMC_LEFT_BOX lbox;
	
	// �E��ʃf�[�^
	IMC_RIGHT_BOX rbox;
	IMC_RBOX_PLAYER rbox_player;		// �E�{�b�N�X�v���C���[
	
	// �n���h�f�[�^
	IMC_HAND hand;

	// �t���[��BG
	IMC_BG	frame_bg;
	
	// �{�^���f�[�^
	IMC_BUTTON_DATA bttn;				// �쐬��
		
	// �T�u�E�B���h�E
	IMC_SUBWIN	subwin;

	int state;		// ���̎��s���

	int effect;		// �G�t�F�N�g�����p

	// �n�C�C�C�G�@�E�B���h�E
	TOUCH_SW_SYS* p_tsw;
	GF_BGL_BMPWIN* p_tsw_bmp;	// �I���m�F�E�B���h�E

	// �Z�[�u�t���O
	BOOL save_flag;

	// �A�N�Z�T���ő吔
	int acce_max;

	//�@�R���e�X�g�p
	int rank;			// �����N
	int mode;			// ���[�h
	int type;			// ����
	int theme;			// �ā[��
	CON_IMC_LOCAL* p_comm_data;	// �ʐM�f�[�^	

	const CONFIG* cp_config;	// �R���t�B�O�f�[�^
	u32 msg_idx;
	STRBUF* p_glb_str;		// �O���[�o��������o�b�t�@
	WORDSET* p_wordset;		// ���[�h�Z�b�g
	
} IMC_SYS_WORK;

//-------------------------------------
//	
//	�t�F�[�h�����p���[�N
//	
//=====================================
typedef struct {
	IMC_SYS_WORK* sys_w;	// �V�X�e�����[�N
	BOOL*	end;			// �I�����m�t���O
	int		work;			// ���[�N�t���O
	int		seq;			// �V�[�P���X
} IMC_SYS_FADE_WORK;


//-------------------------------------
//	�A�N�Z�T�����Ȃ����ă|�P�����Ƃ������Ă��邩
//	�`�F�b�N����P�I�u�W�F�N�g�f�[�^
//=====================================
typedef struct {
	IMC_OBJLIST* obj;
	u32 pokemon_data;	// �|�P�����ɂ������Ă��Ȃ�:0  �|�P�����ɂ������Ă���:����ȊO
} IMC_POKE_ON_ACCEOBJ;

//-------------------------------------
//	�A�N�Z�T�����Ȃ����ă|�P�����Ƃ������Ă��邩
//	�`�F�b�N����V�X�e��
//=====================================
typedef struct {
	IMC_POKE_ON_ACCEOBJ	obj[ IMC_RBOX_OBJ_CONTEST_MAX ];
	int set_num;
} IMC_POKE_ON_ACCESYS;
//-------------------------------------
//	�A�N�Z�T�����Ȃ����ă|�P�����Ƃ������Ă��邩
//	�`�F�b�N�萔
//=====================================
enum{
	IMC_POKEON_ACCE_NONE,		// �Ȃ����Ă��Ȃ�
	IMC_POKEON_ACCE_ON,			// �Ȃ����Ă���
	IMC_POKEON_ACCE_SEARCHEND	// �Ȃ����Ă��違SEARCH�ς�
};



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void imageClipVBlankFunc( void* work );

static void initDrawSys( IMC_SYS_WORK* imc_w );
static void mainDrawSys( IMC_SYS_WORK* imc_w );
static void deleteDrawSys( IMC_SYS_WORK* imc_w );

static void initRightBox( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max );
static void initRightBox_Contest( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max );
static void deleteRightBox( IMC_SYS_WORK* imc_w );

static void initLeftBox( IMC_SYS_WORK* imc_w );
static void deleteLeftBox( IMC_SYS_WORK* imc_w );
static void setLeftBoxBg( IMC_SYS_WORK* imc_w );

static void setFrameBG( IMC_SYS_WORK* imc_w, int no );
static void delFrameBG( IMC_SYS_WORK* imc_w );

static void initBttn( IMC_SYS_WORK* imc_w );
static void initBttn_Contest( IMC_SYS_WORK* imc_w );
static void deleteBttn( IMC_SYS_WORK* imc_w );
static void mainBttn( IMC_SYS_WORK* imc_w );
static void resetBttn( IMC_SYS_WORK* imc_w );

static void endBttn( IMC_BUTTON* bttn, void* work );
static void retBttn( IMC_BUTTON* bttn, void* work );
static void retbBttn( IMC_BUTTON* bttn, void* work );
static void	acceBttn( IMC_BUTTON* bttn, void* work );
static void	bgBttn( IMC_BUTTON* bttn, void* work );

static void endCkEndBttn( IMC_BUTTON* bttn, void* work );
static void endCkCancelBttn( IMC_BUTTON* bttn, void* work );

static void initSubWin( IMC_SYS_WORK* imc_w, const CONFIG* cp_config );
static void initSubWin_Contest( IMC_SYS_WORK* imc_w, int acce_num, int thema, CON_IMC_LOCAL* p_comm_data, const CONFIG* cp_config );
static void deleteSubWin( IMC_SYS_WORK* imc_w );

static void endSeenFadeIn( IMC_SYS_WORK* imc_w, BOOL* end );
static void endSeenFadeInTask( TCB_PTR tcb, void* work );
static void endSeenFadeOut( IMC_SYS_WORK* imc_w, BOOL* end );
static void endSeenFadeOutTask( TCB_PTR tcb, void* work );
static BOOL endSeenFadeMoveBg( IMC_SYS_FADE_WORK* fade_w, int move_x, int move_y, int move_count_num );

static void dataSave( IMC_TELEVISION_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, const MYSTATUS* cp_tr );
static void dataSave_Contest( IMC_CONTEST_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, int rank, const MYSTATUS* cp_tr );

static void initConTextSys( IMC_SYS_WORK* imc_w );
static void deleteConTextSys( IMC_SYS_WORK* imc_w );

static void initTouchSWSys( IMC_SYS_WORK* imc_w );
static void deleteTouchSWSys( IMC_SYS_WORK* imc_w );
static u32 mainTouchSWSys( IMC_SYS_WORK* imc_w );
static void initTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w );
static u32 mainTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w );

static void initTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void setTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void deleteTouchSWBmpWin( IMC_SYS_WORK* imc_w );

static void initContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static u32 setContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void setContestWordSet( IMC_SYS_WORK* imc_w, int buff_id, int no );
static void endContestTextBmpWin( IMC_SYS_WORK* imc_w );
static void deleteContestTextBmpWin( IMC_SYS_WORK* imc_w );

static void initMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx, u8 cx, u8 cy, u8 csx, u8 csy );
static void setMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static u32 setMsgBmpWin_okuri( IMC_SYS_WORK* imc_w, u32 str_idx );
static void endMsgBmpWin_okuri( IMC_SYS_WORK* imc_w );
static void deleteMsgBmpWin( IMC_SYS_WORK* imc_w );

static void setAcceNumSubWin( IMC_SYS_WORK* imc_w );

static int getRightAcceMax_contest( int rank );

static void initPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys );
static void setPokeOnAcceCheckObj( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* obj, u32 init_data );
static void mainPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys );
static IMC_OBJLIST* getPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, u32 no );
static BOOL getPokeOnAcceCheckObjOnPoke( IMC_POKE_ON_ACCESYS* p_sys, u32 no );
static BOOL checkPokeOnAcceCalc( IMC_POKE_ON_ACCEOBJ* p_obj, IMC_POKE_ON_ACCEOBJ* p_check_obj );

static void setPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* dummy, u32 init_data );

static void Imc_OyaExEndCheck( IMC_SYS_WORK* imc_w );

//-----------------------------------------------------------------------------
/**
 *					�ʏ�
 * [JAMP_NORMAL]
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N����
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcInit( PROC* proc, int* seq )
{
	IMC_SYS_WORK*	imc_w;			// �C���[�W�N���b�v���[�N
	u32				check;			// �����p
	IMC_PROC_WORK*  p_imc_pr_w;		// �O������󂯎��f�[�^


	// �q�[�v�쐬
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// �C���[�W�N���b�v���[�N�쐬
	imc_w = PROC_AllocWork( proc, sizeof( IMC_SYS_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( imc_w, 0, sizeof( IMC_SYS_WORK ) );

	// V�u�����NH�u�����N�֐��ݒ�
	sys_VBlankFuncChange( imageClipVBlankFunc, imc_w );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~


	// �O������̃f�[�^���擾
	p_imc_pr_w = PROC_GetParentWork( proc );

	// �O������̃f�[�^�ݒ�
	imc_w->cp_config = p_imc_pr_w->cp_config;

	// �^�b�`�p�l���I�[�g�T���v�����O�J�n
	InitTPSystem();
	check = InitTPNoBuff( 4 );
//	GF_ASSERT( check == TP_OK );
	if( check != TP_OK ){
		OS_Printf( "check != TP_OK\n" );
	}
//	while( InitTPNoBuff( 4 ) != TP_OK ){};

	// �A�C�e���o�b�t�@�쐬
	IMC_ITEM_BUFF_Make( p_imc_pr_w->cp_imc_item, &imc_w->item_buff );

	// �\���ݒ�
	initDrawSys( imc_w );

	// �I�u�W�F�N�g���X�g�e�[�u���쐬
	IMC_OBJLIST_TblInit( &imc_w->objListTbl, IMC_OBJLIST_MAX, HEAPID_IMAGECLIP_DATA );
	
	// �A�N�Z�T���i�[�f�[�^�쐬
	imc_w->acce = IMC_ACCE_ObjTblInit( IMC_SYS_ACCESSORIE_MAX, HEAPID_IMAGECLIP_DATA );

	// �E�{�b�N�X�f�[�^�쐬
	initRightBox( imc_w, p_imc_pr_w->p_poke_para, IMC_RBOX_ACCE_TELEVISION_MAX );
	
	// ���{�b�N�X�f�[�^�쐬
	initLeftBox( imc_w );

	// �t���[��BG��\��
	setFrameBG( imc_w, IMC_BG_FRAME_00 );
	
	// �{�^���f�[�^�쐬
	initBttn( imc_w );

	// �T�u�E�B���h�E������
	initSubWin( imc_w, p_imc_pr_w->cp_config );

	// �n���h�f�[�^������
	IMC_ACCE_HAND_Init( &imc_w->hand, &imc_w->rbox, &imc_w->lbox, &imc_w->drawSys, &imc_w->subwin, TRUE );

	// �͂��@�������@�E�B���h�E�������m��
	imc_w->p_tsw = TOUCH_SW_AllocWork( HEAPID_IMAGECLIP_DATA );
	imc_w->p_tsw_bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DATA, 1 );

	// ��Ԑݒ�
	// ���	����
	imc_w->state = IMC_SYS_ACCE;

	// �T�E���h�f�[�^���[�h(�C���[�W�N���b�v)(BGM���p��)
	Snd_DataSetByScene( SND_SCENE_SUB_IMAGE, 0, 0 );
	
	return PROC_RES_FINISH;
}

#ifdef IMC_DEBUG
extern void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData );
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N���C��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcMain( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	PROC_RESULT	ret = PROC_RES_CONTINUE;
	IMC_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// �f�[�^�Z�[�u

	switch( (*seq) ){
	case IMC_SYS_SEQ_START_TIMING_WAIT:
	case IMC_SYS_SEQ_FADE_IN:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq)  = IMC_SYS_SEQ_FADE_IN_WAIT;
		break;
		
	case IMC_SYS_SEQ_FADE_IN_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;

	case IMC_SYS_SEQ_REFERENCE_ON:
		if( p_pr_w->reference == TRUE ){

			MsgPrintTouchPanelFlagSet(MSG_TP_ON);

			imc_w->msg_idx = IMC_SUBWIN_SetBmpWinWait( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_manual_01 );
			(*seq) ++;
		}else{
			(*seq) = IMC_SYS_SEQ_MAIN;
		}
		break;
		
	case IMC_SYS_SEQ_REFARENCE_WAIT:
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			IMC_SUBWIN_EndBmpWinWait( &imc_w->subwin );
			(*seq) ++;
		}
		break;

	case IMC_SYS_SEQ_KET_WAIT:
		if( (sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) | (sys.tp_trg) ){
			IMC_SUBWIN_SetBmpWin( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_manual_02 );

			MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
			(*seq) ++;
		}
		break;

	//-------------------------------------
	//	
	//	���C������
	//	
	//=====================================
	case IMC_SYS_SEQ_MAIN:

		if(imc_w->state == IMC_SYS_END_CHECK_REQ){
			// �t�F�[�h�J�n
			endSeenFadeIn( imc_w, &imc_w->effect );
			// �t�F�[�h�A�E�g
			(*seq) = IMC_SYS_SEQ_END_CHECK_WAIT;
		}

		// �n���h����
		IMC_HAND_Main( &imc_w->hand );

		// �E�{�b�N�X�̃A�N�Z�T������ݒ�
		setAcceNumSubWin( imc_w );

#ifdef IMC_DEBUG
		IMC_POKE_DEBUG_ChangePoke( &imc_w->rbox.boxDraw.poke, HEAPID_IMAGECLIP_DRAW, &imc_w->drawSys );
#endif

		// �T�u�E�B���h�E���C��
		IMC_SUBWIN_Main( &imc_w->subwin );
		
		// �{�^������
		mainBttn( imc_w );
		break;

	case IMC_SYS_SEQ_END_CHECK_WAIT:	// �I���`�F�b�N�t�F�[�h�҂�
		if( imc_w->effect ){
			imc_w->effect = FALSE;
			(*seq) = IMC_SYS_SEQ_END_CHECK;
			imc_w->state = IMC_SYS_END_CHECK;

			// �E�{�b�N�X�v���C���[�쐬
			IMC_RBOX_PLAYER_Init( &imc_w->rbox_player, &imc_w->rbox, HEAPID_IMAGECLIP_DRAW );
		}
		break;

	case IMC_SYS_SEQ_END_CHECK:			// �I���`�F�b�N����
		
		// �L�����Z���`�F�b�N
		if( imc_w->state == IMC_SYS_END_CANCEL_REQ ){
			// �t�F�[�h�J�n
			endSeenFadeOut( imc_w, &imc_w->effect );
			(*seq) = IMC_SYS_SEQ_MAIN_WAIT;
			break;
		}

		// �I���`�F�b�N
		if( imc_w->state == IMC_SYS_END_REQ ){
			(*seq) = IMC_SYS_SEQ_SAVE_CHECK;
			imc_w->state = IMC_SYS_SAVE_CHECK_REQ;
			
			initTouchSaveCheckSWSys( imc_w );	// �Z�[�u�`�F�b�N�{�^���쐬
			break;
		}
		
		// �{�^������
		imc_w->state = mainTouchSWSys( imc_w );

		// �E�{�b�N�X�v���C���[
		IMC_RBOX_PLAYER_Main( &imc_w->rbox_player );
		break;

	case IMC_SYS_SEQ_SAVE_CHECK:	// �Z�[�u�`�F�b�N
		if( imc_w->state == IMC_SYS_SAVE ){
			imc_w->save_flag = TRUE;
			(*seq) = IMC_SYS_SEQ_FADE_OUT;
			break;
		}
		if( imc_w->state == IMC_SYS_SAVE_CAN ){
			imc_w->save_flag = FALSE;
			(*seq) = IMC_SYS_SEQ_FADE_OUT;
			break;
		}

		// �{�^������
		imc_w->state = mainTouchSaveCheckSWSys( imc_w );

		// �E�{�b�N�X�v���C���[
		IMC_RBOX_PLAYER_Main( &imc_w->rbox_player );
		break;

	case IMC_SYS_SEQ_MAIN_WAIT:			// ���C����ʃt�F�[�h�҂�
		if( imc_w->effect ){
			imc_w->effect = FALSE;
			(*seq) = IMC_SYS_SEQ_MAIN;
			imc_w->state = IMC_SYS_ACCE;		// �A�N�Z�T���ύX�ł͂��߂�

			// �E�{�b�N�X�v���C���[�I��
			IMC_RBOX_PLAYER_Delete( &imc_w->rbox_player );
		}
		break;
		
	case IMC_SYS_SEQ_FADE_OUT:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;

	case IMC_SYS_SEQ_FADE_OUT_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) = 0;
			imc_w->state = IMC_SYS_END;
			ret = PROC_RES_FINISH;

			// �E�{�b�N�X�v���C���[�I��
			IMC_RBOX_PLAYER_Delete( &imc_w->rbox_player );
		}
		break;
	}

	///////////////////////////////////////////////
	//
	//	�����͋��ʏ���
	//
	//////////////////////////////////////////////
	// �`�揈��
	mainDrawSys( imc_w );
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N�I��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcEnd( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	u32	check;	// �����p
	IMC_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// �f�[�^�Z�[�u

	// �f�[�^���Z�[�u
	if( imc_w->save_flag == TRUE ){
		// ���R�[�h�f�[�^�@�X�R�A�����Z����
		RECORD_Score_Add( p_pr_w->p_record, SCORE_ID_MAKE_CLIP );
		
		dataSave( p_pr_w->p_imc_one_data, &imc_w->rbox, p_pr_w->cp_tr );	
	}

	// �Z�[�u�L���ݒ�
	if( p_pr_w->p_save_flg != NULL ){
		if( imc_w->save_flag == TRUE ){
			*p_pr_w->p_save_flg = TRUE;
		}else{
			*p_pr_w->p_save_flg = FALSE;
		}
	}

	// �n�C�C�C�G�E�B���h�E�������j��
	TOUCH_SW_FreeWork( imc_w->p_tsw );	
	GF_BGL_BmpWinFree( imc_w->p_tsw_bmp, 1 );
	
	// �T�u�E�B���h�E�j��
	deleteSubWin( imc_w );
	
	// �n���h���j��
	IMC_ACCE_HAND_Delete( &imc_w->hand );

	// �{�^���j��
	deleteBttn( imc_w );
	
	// �t���[��BG��j��
	delFrameBG( imc_w );
	
	// �E�{�b�N�X�j��
	deleteRightBox( imc_w );
	
	// ���{�b�N�X�j��
	deleteLeftBox( imc_w );
	
	// �A�N�Z�T���i�[�f�[�^�j��
	IMC_ACCE_ObjTblDelete( imc_w->acce );
	imc_w->acce = NULL;
	
	// �I�u�W�F�N�g���X�g�e�[�u���j��
	IMC_OBJLIST_TblDelete( &imc_w->objListTbl );
	
	deleteDrawSys( imc_w );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// �^�b�`�p�l���T���v�����O�I��
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// ���[�N�j��
	PROC_FreeWork( proc );

	// �q�[�v�j��
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );
	
	return PROC_RES_FINISH;
}





//-----------------------------------------------------------------------------
/**
 *					�R���e�X�g�p
 * [JAMP_CONTEST]
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N����
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestInit( PROC* proc, int* seq )
{
	IMC_SYS_WORK*	imc_w;			// �C���[�W�N���b�v���[�N
	u32				check;			// �����p
	IMC_CONTEST_PROC_WORK*  p_imc_pr_w;		// �O������󂯎��f�[�^


	// �q�[�v�쐬
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// �C���[�W�N���b�v���[�N�쐬
	imc_w = PROC_AllocWork( proc, sizeof( IMC_SYS_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( imc_w, 0, sizeof( IMC_SYS_WORK ) );

	// V�u�����NH�u�����N�֐��ݒ�
	sys_VBlankFuncChange( imageClipVBlankFunc, imc_w );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~


	// �O������̃f�[�^���擾
	p_imc_pr_w = PROC_GetParentWork( proc );

	// �R���e�X�g���擾
	imc_w->rank = p_imc_pr_w->rank;
	imc_w->mode = p_imc_pr_w->mode;
	imc_w->type = p_imc_pr_w->type;
	imc_w->theme = p_imc_pr_w->theme;
	imc_w->p_comm_data = p_imc_pr_w->p_comm_data;

	OS_Printf( "�R���e�X�g�e�[�}�@%d �����N %d \n", p_imc_pr_w->theme, p_imc_pr_w->rank );

	// �^�b�`�p�l���I�[�g�T���v�����O�J�n
	InitTPSystem();
	check = InitTPNoBuff( 4 );
//	GF_ASSERT( check == TP_OK );
	if( check != TP_OK ){
		OS_Printf( "check != TP_OK\n" );
	}
//	while( InitTPNoBuff( 4 ) != TP_OK ){};


	// �A�C�e���o�b�t�@�쐬
	IMC_ITEM_BUFF_Make( p_imc_pr_w->cp_imc_item, &imc_w->item_buff );

	
	// �\���ݒ�
	initDrawSys( imc_w );

	// �ŏ��A�N�^�[�Z�b�g��\��
	CLACT_DrawFlagSet( imc_w->drawSys.clactSet, 0 );

	// COMM_ICON�ݒ�
	WirelessIconEasy();	

	// �L�����N�^�}�l�[�W���ɃL�����N�^�̈��\��
	CLACT_U_WmIcon_SetReserveAreaCharManager( NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K );
	CLACT_U_WmIcon_SetReserveAreaPlttManager( NNS_G2D_VRAM_TYPE_2DMAIN );

	// �I�u�W�F�N�g���X�g�e�[�u���쐬
	IMC_OBJLIST_TblInit( &imc_w->objListTbl, IMC_OBJLIST_MAX, HEAPID_IMAGECLIP_DATA );
	
	// �A�N�Z�T���i�[�f�[�^�쐬
	imc_w->acce = IMC_ACCE_ObjTblInit( IMC_SYS_ACCESSORIE_MAX, HEAPID_IMAGECLIP_DATA );

	// �O������̃f�[�^�ݒ�
	imc_w->cp_config = p_imc_pr_w->cp_config;


	// �E�{�b�N�X�f�[�^�쐬
	if( imc_w->p_comm_data->sio_flag == 0 ){
		imc_w->acce_max = getRightAcceMax_contest( p_imc_pr_w->rank );	
	}else{
		imc_w->acce_max = CON_IMAGE_ACCE_MAX_SIO;
	}
	initRightBox_Contest( imc_w, p_imc_pr_w->p_poke_para, imc_w->acce_max );
		
	
	// ���{�b�N�X�f�[�^�쐬
	initLeftBox( imc_w );

	// �t���[��BG��\��
	setFrameBG( imc_w, IMC_BG_FRAME_00 );
	
	// �{�^���f�[�^�쐬
	initBttn_Contest( imc_w );

	// �T�u�E�B���h�E������
	initSubWin_Contest( imc_w, imc_w->acce_max, p_imc_pr_w->theme, p_imc_pr_w->p_comm_data, p_imc_pr_w->cp_config );

	// �n���h�f�[�^������
	IMC_ACCE_HAND_Init( &imc_w->hand, &imc_w->rbox, &imc_w->lbox, &imc_w->drawSys, &imc_w->subwin, FALSE );

	// �͂��@�������@�E�B���h�E�������m��
	imc_w->p_tsw = TOUCH_SW_AllocWork( HEAPID_IMAGECLIP_DATA );
	imc_w->p_tsw_bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DATA, 1 );

	// ��Ԑݒ�
	// ���	����
	imc_w->state = IMC_SYS_ACCE;

	// ���b�Z�[�W�ݒ�
	ConTool_MsgPrintFlagSet( imc_w->p_comm_data->sio_flag );
	
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N���C��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestMain( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	PROC_RESULT	ret = PROC_RES_CONTINUE;
	int count;

	switch( (*seq) ){
	case IMC_SYS_CON_SEQ_CON_SND_FADE:
		Snd_BgmFadeOut( BGM_VOL_CLIP, BGM_FADE_CLIP_TIME );
		(*seq) ++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_SND_FADE_WAIT:
		if( Snd_FadeCheck() == 0 ){
			(*seq) ++;
		}
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_ON:
		initConTextSys( imc_w );

		// �e�����N�̃A�N�Z�T���������[�h�Z�b�g�ɐݒ�
		setContestWordSet( imc_w, 0, imc_w->acce_max );
		
		if( imc_w->mode != CONMODE_VISUAL_PRACTICE ){
			// �{�ԃe�L�X�g
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_du_b_01 );
		}else{
			// ���K�e�L�X�g
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_prac_01 );
		}
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_WAIT:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;


	case IMC_SYS_CON_SEQ_CON_TEXT_THEME_ON:
		// THEME���\
		imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_theme_01 + imc_w->theme );
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_THEME_WAIT:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;

	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_ON:
		// �Ō�̊J�n�I�I�Ƃ������t
		if( imc_w->mode != CONMODE_VISUAL_PRACTICE ){
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_after_theme_02 );
		}else{
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_after_theme_01 );
		}
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_WAIT:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;


	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_DOUKI:
		// �����R�}���h��]��
		if( imc_w->p_comm_data->sio_flag ){
			CommTimingSyncStart( CONSIO_TIMING_CALL_IN_IMCPROC );
		}
		(*seq)++;
		break;

	case IMC_SYS_CON_SEQ_START_TIMING_WAIT:	// �����҂�
		// �ʐM���Ă���Ƃ���
		// �����҂�
		if( imc_w->p_comm_data->sio_flag ){
			if( CommIsTimingSync( CONSIO_TIMING_CALL_IN_IMCPROC ) ){
				(*seq)++;
			}
		}else{
			(*seq)++;
		}
		break;

		
	case IMC_SYS_CON_SEQ_CON_TEXT_END:
		deleteConTextSys( imc_w );
		// ����炷
		Snd_SePlay( IMC_SE_CON_START );
		(*seq)++;
		break;
	
	
	case IMC_SYS_CON_SEQ_FADE_IN:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_HOLEIN,
				WIPE_TYPE_TUNNELIN,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );

//		WirelessIconEasyXY( 0, 176, FALSE );	
		(*seq) ++;
		break;
		
	case IMC_SYS_CON_SEQ_FADE_IN_WAIT:
		if( WIPE_SYS_EndCheck() ){

			// �T�E���h�f�[�^���[�h(�R���e�X�g�C���[�W�N���b�v)(BGM�؂�ւ�)
			//Snd_DataSetByScene( SND_SCENE_SUB_IMAGE, 0, 0 );
			Snd_DataSetByScene( SND_SCENE_CON_IMAGE, SEQ_CO_DRESS, 0 );

			(*seq) ++;
		}
		break;

	//-------------------------------------
	//	
	//	���C������
	//	
	//=====================================
	case IMC_SYS_CON_SEQ_MAIN:

		// �I���{�^���������ꂽ�Ƃ��̏���
		if(imc_w->state == IMC_SYS_END_CHECK_REQ){
			// �e�ɏI�����R�[��
			CommContestSendImcForceEnd( imc_w->p_comm_data, TRUE );

			// �ʐM���Ă���Ƃ��͏�ɑ҂��Ă̕������o��
			if( imc_w->p_comm_data->sio_flag ){
				IMC_SUBWIN_SetBmpWin( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, msg_con_caution_01 );
			}
			
			(*seq)  = IMC_SYS_CON_SEQ_EX_END_WAIT;
			break;
		}

#ifdef IMC_DEBUG
		{
			static BOOL COUNTER_END_FLG = TRUE;
			if( sys.trg & PAD_BUTTON_L ){
				COUNTER_END_FLG ^= 1;
			}
			
			// �J�E���^�[���O�ɂȂ�����I���
			count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
			if(0 == count){
				(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
				// ����炷
				Snd_SePlay( IMC_SE_CON_FINISH );
			}

			// �n���h����
			IMC_HAND_Main( &imc_w->hand );

			// �E�{�b�N�X�̃A�N�Z�T������ݒ�
			setAcceNumSubWin( imc_w );

			// FALSE�Ȃ�I���Ȃ�
			if( COUNTER_END_FLG == TRUE ){
				// �T�u�E�B���h�E���C��
				IMC_SUBWIN_Main( &imc_w->subwin );
			}
			
			// �{�^������
			mainBttn( imc_w );

		}
#else
		// �J�E���^�[���O�ɂȂ�����I���
		count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
		if(0 == count){
			(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
			// ����炷
			Snd_SePlay( IMC_SE_CON_FINISH );
		}

		// �n���h����
		IMC_HAND_Main( &imc_w->hand );

		// �E�{�b�N�X�̃A�N�Z�T������ݒ�
		setAcceNumSubWin( imc_w );

		// �T�u�E�B���h�E���C��
		IMC_SUBWIN_Main( &imc_w->subwin );
		
		// �{�^������
		mainBttn( imc_w );
#endif
		break;

	case IMC_SYS_CON_SEQ_EX_END_WAIT:	// �I���������Ă̋����I���҂�
		// �J�E���^�[���O�ɂȂ�����I���
		count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
		if(0 == count){
			(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
			// ����炷
			Snd_SePlay( IMC_SE_CON_FINISH );
		}

		// �E�{�b�N�X�̃A�N�Z�T������ݒ�
		setAcceNumSubWin( imc_w );

		// �T�u�E�B���h�E���C��
		IMC_SUBWIN_Main( &imc_w->subwin );

		// �����I���`�F�b�N
		Imc_OyaExEndCheck( imc_w );
		
		break;

	case IMC_SYS_CON_SEQ_END_CHECK_WAIT:
		// �T�u�E�B���h�E���C��
		IMC_SUBWIN_Main( &imc_w->subwin );
		// �����ƃJ�E���^�[�̴̪�Ă��I�������I��
		if( IMC_SUBWIN_GetCounterEffectEnd( &imc_w->subwin ) ){
			(*seq) = IMC_SYS_CON_SEQ_FADE_OUT;
		}
		break;
		
	case IMC_SYS_CON_SEQ_FADE_OUT:

		// �����I���̂�҂�
		if( Snd_SePlayCheck( IMC_SE_CON_FINISH ) == TRUE ){
			break;
		}
		
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_DOOROUT,
				WIPE_TYPE_DOOROUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );

		Snd_SePlay( IMC_SE_CON_DOOR_CLOSE );
		(*seq) ++;
		break;

	case IMC_SYS_CON_SEQ_FADE_OUT_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) = 0;
			imc_w->state = IMC_SYS_END;
			ret = PROC_RES_FINISH;

			// �E�B���h�E�̏�����
			GX_SetVisibleWnd( GX_WNDMASK_NONE );
			
			// �E�{�b�N�X�̃f�[�^���I�����W�܂œ������Ă���
			IMC_RBOX_ListMove( &imc_w->rbox, -(IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT), (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT) );
		}
		break;
	}

	///////////////////////////////////////////////
	//
	//	�����͋��ʏ���
	//
	//////////////////////////////////////////////
	// �`�揈��
	mainDrawSys( imc_w );
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N�I��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestEnd( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	u32	check;	// �����p
	IMC_CONTEST_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// �f�[�^�Z�[�u

	OS_Printf( "�R���e�X�g�e�[�}�@%d �����N %d \n", imc_w->theme, imc_w->rank );

	// �f�[�^���Z�[�u
	dataSave_Contest( p_pr_w->p_imc_one_data, &imc_w->rbox, imc_w->rank, p_pr_w->cp_tr );	

	// �n�C�C�C�G�E�B���h�E�������j��
	TOUCH_SW_FreeWork( imc_w->p_tsw );	
	GF_BGL_BmpWinFree( imc_w->p_tsw_bmp, 1 );
	
	// �T�u�E�B���h�E�j��
	deleteSubWin( imc_w );
	
	// �n���h���j��
	IMC_ACCE_HAND_Delete( &imc_w->hand );

	// �{�^���j��
	deleteBttn( imc_w );
	
	// �t���[��BG��j��
	delFrameBG( imc_w );
	
	// �E�{�b�N�X�j��
	deleteRightBox( imc_w );
	
	// ���{�b�N�X�j��
	deleteLeftBox( imc_w );
	
	// �A�N�Z�T���i�[�f�[�^�j��
	IMC_ACCE_ObjTblDelete( imc_w->acce );
	imc_w->acce = NULL;
	
	// �I�u�W�F�N�g���X�g�e�[�u���j��
	IMC_OBJLIST_TblDelete( &imc_w->objListTbl );
	
	deleteDrawSys( imc_w );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// �^�b�`�p�l���T���v�����O�I��
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// ���[�N�j��
	PROC_FreeWork( proc );

	// �q�[�v�j��
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );

	// ���b�Z�[�W�ݒ�
	ConTool_MsgPrintFlagReset();

	WirelessIconEasyEnd();

	
	return PROC_RES_FINISH;
}




//-----------------------------------------------------------------------------
/**
*		�v���C�x�[�g�֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e��������
 *
 *	@param	imc_w	�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initDrawSys( IMC_SYS_WORK* imc_w )
{
	IMC_DRAW_LOADRES_DATA loadData;	// �摜�f�[�^�ǂݍ��݃f�[�^

	// ��ʃf�[�^�ݒ�
	IMC_DRAW_SetUp();

	// �`��V�X�e���쐬
	IMC_DRAW_InitSys( &imc_w->drawSys );
	
	// �`��f�[�^�쐬
	IMC_DRAW_MakeLoadSWSP_samp( &imc_w->drawSys, &loadData );

	// �`��f�[�^Vram�]��
	IMC_DRAW_LoadResource( &imc_w->drawSys, &loadData );

	// �`��f�[�^�j��
	IMC_DRAW_DestLoadSWSP( &loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e�����C��
 *
 *	@param	imc_w	�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainDrawSys( IMC_SYS_WORK* imc_w )
{
	IMC_DRAW_DrawSys( &imc_w->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���j��
 *
 *	@param	imc_w	�V�X�e�����[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteDrawSys( IMC_SYS_WORK* imc_w )
{
	// �`��f�[�^�j��
	IMC_DRAW_DeleteResource( &imc_w->drawSys );

	// �`��V�X�e���j��
	IMC_DRAW_DeleteSys( &imc_w->drawSys );

	// �`��ʐݒ�j��
	IMC_DRAW_PutBack();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�f�[�^�쐬
 *
 *	@param	imc_w	�C���[�W�N���b�v�V�X�e���f�[�^
 *	@param	pp		�|�P�����p�����[�^
 *	@param	acce_max	�A�N�Z�T���o�^���ő吔
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBox( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max )
{
	IMC_RIGHT_BOX_INIT	rbox_init;	// �E�{�b�N�X�������f�[�^

	// �E�{�b�N�X�f�[�^�쐬
	// �`��f�[�^
	rbox_init.SWSP_drawSys		= imc_w->drawSys.SWSP_drawSys;
	rbox_init.SWSP_charData		= imc_w->drawSys.SWSP_charData;
	rbox_init.SWSP_plttData		= imc_w->drawSys.SWSP_plttData;
	rbox_init.accePlttOfsTbl	= imc_w->drawSys.accePlttOfsTbl;
	rbox_init.SSM_drawSys		= imc_w->drawSys.SSM_drawSys;
	rbox_init.BG_Ini			= imc_w->drawSys.BG_Ini;
	rbox_init.acce_count_max	= acce_max;

	rbox_init.acce		= imc_w->acce;			// �A�N�Z�T���f�[�^
	rbox_init.objListTbl= &imc_w->objListTbl;	// �I�u�W�F�N�g���X�g�e�[�u��
	IMC_RBOX_InitSys( &imc_w->rbox, &rbox_init );
	
	// �|�P������o�^
	{
		SOFT_SPRITE_ARC	arc;
		IMC_RBOX_AddPoke( &imc_w->rbox, pp, &arc, HEAPID_IMAGECLIP_DRAW );

		// �|�P�����L�����N�^�f�[�^�o�^
		IMC_POKE_CharSet( &imc_w->drawSys, &arc );
	}
/*
	// �E�{�b�N�X�ɔz�u����f�[�^���쐬
	{
		int i;
		for(i=0;i<IMC_ACCE_MAX; i++){
			int x,y;
			x = IMC_RBOX_AREA_X;
			y = IMC_RBOX_AREA_Y;
			
			IMC_RBOX_AddAccessorie( &imc_w->rbox, i, 
					x + (gf_mtRand() % (IMC_RBOX_AREA_WIDTH / 2)),
					y + (gf_mtRand() % (IMC_RBOX_AREA_HEIGHT / 2)) );
		}
	}//*/
	IMC_RBOX_SetObjPriority( &imc_w->rbox );

	// BG��\��
	IMC_RBOX_BGSet( &imc_w->rbox, IMC_BG_RIGHT_00, HEAPID_IMAGECLIP_DRAW );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�@�E�{�b�N�X������
 *
 *	@param	imc_w
 *	@param	pp
 *	@param	acce_max 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void initRightBox_Contest( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max )
{
	int size_x, size_y;
	int in_size_x, in_size_y;
	
	initRightBox( imc_w, pp, acce_max );

	// �|�P�����T�C�Y�擾
	IMC_POKE_SizeGet( &imc_w->rbox.boxDraw.poke, &size_x, &size_y );
	IMC_POKE_InSizeGet( &imc_w->rbox.boxDraw.poke, &in_size_x, &in_size_y );

	// �R���e�X�g�p���W�ݒ�
	IMC_POKE_MatrixSet( &imc_w->rbox.boxDraw.poke, IMC_POKE_INIT_X, (IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT) - ((size_y/2) - in_size_y) + IMC_POKE_MAT_CONTEST_Y_OFS );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�f�[�^�j��
 *
 *	@param	imc_w	�C���[�W�N���b�v�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteRightBox( IMC_SYS_WORK* imc_w )
{
	// BG���N���[��
	IMC_RBOX_BGClean( &imc_w->rbox );
	
	// �E�{�b�N�X�z�u�f�[�^�j��
	IMC_RBOX_DeleteAccessorieAll( &imc_w->rbox );
	
	// �E�{�b�N�X�f�[�^�j��
	IMC_RBOX_DeleteSys( &imc_w->rbox );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�f�[�^�쐬
 *
 *	@param	imc_w	�C���[�W�N���b�v�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initLeftBox( IMC_SYS_WORK* imc_w )
{
	IMC_LEFT_BOX_INIT	lbox_init;	// �E�{�b�N�X�������f�[�^

	// ���{�b�N�X�f�[�^�쐬
	// �`��f�[�^
	lbox_init.SWSP_drawSys		= imc_w->drawSys.SWSP_drawSys;
	lbox_init.SWSP_charData		= imc_w->drawSys.SWSP_charData;
	lbox_init.SWSP_plttData		= imc_w->drawSys.SWSP_plttData;
	lbox_init.accePlttOfsTbl	= imc_w->drawSys.accePlttOfsTbl;
	lbox_init.BG_Ini			= imc_w->drawSys.BG_Ini;
	lbox_init.p_item_buff		= &imc_w->item_buff;
	lbox_init.acce			= imc_w->acce;			// �A�N�Z�T���f�[�^
	lbox_init.objListTbl	= &imc_w->objListTbl;	// �I�u�W�F�N�g���X�g�e�[�u��
	lbox_init.accelist_num	= IMC_LBOX_ACCE_NEAD_LIST_NUM;	// ���X�g��
	lbox_init.bglist_num	= IMC_LBOX_BG_NEAD_LIST_NUM;	// ���X�g��
	lbox_init.sndlist_num	= IMC_LBOX_SND_NEAD_LIST_NUM;	// ���X�g��
	IMC_LBOX_InitSys( &imc_w->lbox, &lbox_init );

	// �J�����g�擪�_�~�[�f�[�^�쐬
	IMC_LBOX_SetCurrentAccessorie( 
			&imc_w->lbox, 
			IMC_OBJLIST_ACCE,
			0 );


	// ���{�b�N�X�ɔz�u����f�[�^���쐬
	{
		int i, j;
		int add_num;

		for(i=0;i<IMC_ACCE_MAX; i++){
			add_num = IMC_ITEM_BUFF_AcceGetNum( &imc_w->item_buff, i );
			for( j=0; j<add_num; j++ ){
				// ���{�b�N�X�A�N�Z�T���z�u
				IMC_LBOX_AddAccessorie( &imc_w->lbox, IMC_OBJLIST_ACCE, i );
			}
		}
		// BG�T���l�C�����쐬
		for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

			add_num = IMC_ITEM_BUFF_TurnBgNoGet( &imc_w->item_buff, i );
			if( add_num < IMC_BG_RIGHT_MAX ){
				// ���{�b�N�X�A�N�Z�T���z�u
				IMC_LBOX_AddAccessorie( &imc_w->lbox, IMC_OBJLIST_BG, add_num );
			}
		}

		// �\���D�揇�ʐݒ�
		IMC_LBOX_SetAccessoriePriority( &imc_w->lbox );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�f�[�^�쐬
 *
 *	@param	imc_w	�C���[�W�N���b�v�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteLeftBox( IMC_SYS_WORK* imc_w )
{
	// BG���N���[��
	IMC_LBOX_BGClean( &imc_w->lbox );
	
	// �E�{�b�N�X�z�u�f�[�^�j��
	IMC_LBOX_DeleteAccessorieAll( &imc_w->lbox );
	
	// �E�{�b�N�X�f�[�^�j��
	IMC_LBOX_DeleteSys( &imc_w->lbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���{�b�N�XBG�̃Z�b�g�A�b�v
 *
 *	@param	imc_w	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setLeftBoxBg( IMC_SYS_WORK* imc_w )
{
	// �\���D�揇�ʐݒ�
	G2_SetBG0Priority( 1 );
	G2_SetBG1Priority( 0 );//*/
	G2_SetBG2Priority( 2 );
	G2_SetBG3Priority( 3 );

	// �X�N���[�����W��ݒ�
	// �Ȃ�������ł��܂������@���ł��H�H
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, -16 );
	
	// �w�i�i���o
	IMC_LBOX_BGSet( &imc_w->lbox, 0 );
	IMC_LBOX_BGChange( &imc_w->lbox, 0, IMC_LBOX_FADE_Y, 0, NULL );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	V�u�����N�֐�
 *
 *	@param	void* work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imageClipVBlankFunc( void* work )
{
	IMC_SYS_WORK* sys = work;

	// �`��֌WV�u�����N�֐�
	IMC_DRAW_VBlank( &sys->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���[��BG��\��
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *	@param	no		BGno
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setFrameBG( IMC_SYS_WORK* imc_w, int no )
{
	IMC_BG_ADD add;
	
	// �o�^�f�[�^�ݒ�
	add.bg_ini		= imc_w->drawSys.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_FRAME_CG_ARC_GET(no);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_FRAME_SC_ARC_GET(no);
	add.x			= 0;
	add.y			= 0;
	add.frame		= GF_BGL_FRAME1_M;
	add.pltt_num	= 1;
	add.pltt_offs	= 2;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	IMC_BG_MakaObj( &imc_w->frame_bg, &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���[��BG��\��
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delFrameBG( IMC_SYS_WORK* imc_w )
{
	IMC_BG_DeleteObj( &imc_w->frame_bg );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���f�[�^�쐬
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Init( &imc_w->bttn, &imc_w->drawSys );

	// ���p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RET, retBttn, imc_w, IMC_BTTN_PUSH_F );

	// ���p���b�g�ύX�߂�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RETB, retbBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// �A�N�Z�T���p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_ACE, acceBttn, imc_w, IMC_BTTN_PUSH_F );
	// �A�N�Z�T���p���b�g�ύX�{�^�����I����Ԃɂ���
	
	
	// BG�p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_BG, bgBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// �I���{�^���֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_END, endBttn, imc_w, IMC_BTTN_PUSH_F );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���f�[�^�쐬		�R���e�X�g�p
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBttn_Contest( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Init( &imc_w->bttn, &imc_w->drawSys );

	// ���p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RET, retBttn, imc_w, IMC_BTTN_PUSH_F );

	// ���p���b�g�ύX�߂�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RETB, retbBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// �A�N�Z�T���p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_ACE, acceBttn, imc_w, IMC_BTTN_PUSH_F );
	// �A�N�Z�T���p���b�g�ύX�{�^�����I����Ԃɂ���
	
	
	// BG�p���b�g�ύX�֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_BG, bgBttn, imc_w, IMC_BTTN_PUSH_F );

	// �I���{�^���֐���ݒ�
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_END, endBttn, imc_w, IMC_BTTN_PUSH_F );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���f�[�^�j��
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Delete( &imc_w->bttn, &imc_w->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^�����C���֐�
 *
 *	@param	imc_w	�C���[�W�N���b�v���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Main( &imc_w->bttn );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j���󋵂̃��Z�b�g
 *
 *	@param	imc_w 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void resetBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Reset( &imc_w->bttn );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v���I��������֐�
 *
 *	@param	bttn	�{�^���\����
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// �I�����ėǂ���ԉ��`�F�b�N
	if( IMC_LBOX_ENDCheck( &imc_w->lbox ) == FALSE ){
		return ;
	}
	
	// ��Ԑݒ�
	// ���	�I�����N�G�X�g
	imc_w->state = IMC_SYS_END_CHECK_REQ;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���p���b�g��ύX
 *
 *	@param	bttn	�{�^���\����
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void retBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int mode;
/*	int list_num;
	int list_max;

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, mode );
	list_max	= IMC_LBOX_GetDummyTblNum( &imc_w->lbox, mode );
	
	list_num = (list_num + 1) % list_max;

	// ���p���b�g�̒��g��ύX
	IMC_LBOX_ChangeCurrentAccessorie( 
			&imc_w->lbox, mode, list_num );//*/
	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	IMC_LBOX_AddCurrentAccessorie(
			&imc_w->lbox, mode, IMC_LBOX_ADD_ONE );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���p���b�g��߂�
 *
 *	@param	bttn	�{�^���\����
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void retbBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int mode;
/*	int list_num;
	int list_max;

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, mode );
	list_max	= IMC_LBOX_GetDummyTblNum( &imc_w->lbox, mode );
	
	list_num--;
	if( list_num < 0 ){
		list_num += list_max;
	}

	// ���p���b�g�̒��g��ύX
	IMC_LBOX_ChangeCurrentAccessorie( 
			&imc_w->lbox, mode, list_num );
//*/

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	IMC_LBOX_AddCurrentAccessorie(
			&imc_w->lbox, mode, IMC_LBOX_SUB_ONE );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���p���b�g�ɕύX
 *
 *	@param	bttn	�{�^���\����
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	acceBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int list_num;
	int mode;

	if( imc_w->state != IMC_SYS_ACCE ){
		list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, IMC_OBJLIST_ACCE );
		

		// ���p���b�g�̒��g��ύX
		IMC_LBOX_SetCurrentAccessorie( 
				&imc_w->lbox, IMC_OBJLIST_ACCE, list_num );

		// ��Ԑݒ�
		imc_w->state = IMC_SYS_ACCE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�p���b�g�ɕύX
 *
 *	@param	bttn	�{�^���\����
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	bgBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int list_num;
	int mode;

	if( imc_w->state != IMC_SYS_BG ){

		list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, IMC_OBJLIST_BG );
		
		// ���p���b�g�̒��g��ύX
		IMC_LBOX_SetCurrentAccessorie( 
				&imc_w->lbox, IMC_OBJLIST_BG, list_num );

		// ��Ԑݒ�
		imc_w->state = IMC_SYS_BG;

	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u�E�B���h�E������
 *
 *	@param	imc_w		�T�u�E�B���h�E
 *	@param	cp_config	�R���t�B�O�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSubWin( IMC_SYS_WORK* imc_w, const CONFIG* cp_config )
{
	IMC_SUBWIN_INIT	init;

	memset( &init, 0, sizeof(IMC_SUBWIN_INIT) );
	init.bg_ini		= imc_w->drawSys.BG_Ini;
	init.clactSet	= imc_w->drawSys.clactSet;
	init.p_resMan	= imc_w->drawSys.resMan;
	init.acce_max	= IMC_RBOX_ACCE_TELEVISION_MAX;	
	init.cp_config	= cp_config;

	
	IMC_SUBWIN_Init( &imc_w->subwin, &init, IMC_SUBWIN_DEFAULT_INIT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�T�u�E�B���h�E������
 *
 *	@param	imc_w		���[�N
 *	@param	acce_num	�A�N�Z�T���ő吔
 *	@param	thema		�e�[�}
 *	@param	p_comm_data	�ʐM�f�[�^
 *	@param	cp_config	�R���t�B�O�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initSubWin_Contest( IMC_SYS_WORK* imc_w, int acce_num, int thema, CON_IMC_LOCAL* p_comm_data, const CONFIG* cp_config )
{
	IMC_SUBWIN_INIT	init;
	BOOL oya;
	
	init.bg_ini		= imc_w->drawSys.BG_Ini;
	init.clactSet	= imc_w->drawSys.clactSet;
	init.p_resMan	= imc_w->drawSys.resMan;
	init.acce_max	= acce_num;	
	init.rank_msgid = NARC_msg_imageclip_dat;
	init.rank_strid = imgclip_theme_01 + thema;
	init.count_max	= IMC_COUNT_MAX;
	init.p_comm_data = p_comm_data;
	init.cp_config	= cp_config;

	IMC_SUBWIN_Init( &imc_w->subwin, &init, IMC_SUBWIN_CONTEST_INIT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u�E�B���h�E�j��
 *
 *	@param	imc_w	�T�u�E�B���h�E
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSubWin( IMC_SYS_WORK* imc_w )
{
	IMC_SUBWIN_Delete( &imc_w->subwin );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I����ʂփt�F�[�h�C���J�n
 *
 *	@param	imc_w	�V�X�e�����[�N	
 *	@param	end		�I�����m�t���O
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeIn( IMC_SYS_WORK* imc_w, BOOL* end )
{
	TCB_PTR tcb;
	IMC_SYS_FADE_WORK* fade_w;

	// �^�X�N�o�^
	tcb = PMDS_taskAdd( endSeenFadeInTask, sizeof( IMC_SYS_FADE_WORK ), 10, HEAPID_IMAGECLIP_DATA );

	// ���[�N�Ƀf�[�^�ݒ�
	fade_w = TCB_GetWork( tcb );
	fade_w->sys_w	= imc_w;
	fade_w->end		= end;
	fade_w->work	= 0;
	fade_w->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I����ʃt�F�[�h�^�X�N
 *
 *	@param	tcb		�^�X�N�I�u�W�F
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeInTask( TCB_PTR tcb, void* work )
{
	IMC_SYS_FADE_WORK* fade_w = work;
	BOOL	check;
	
	switch( fade_w->seq ){
	case IMC_SEENFADEIN_ACCE_FADEOUT:
		check = IMC_LBOX_ChangeCurrentAccessorie( 
				&fade_w->sys_w->lbox,
				IMC_LBOX_FADELIST_MODE,
				0);
		GF_ASSERT( check );	// ��������

		
		fade_w->seq++;
		break;
		
	case IMC_SEENFADEIN_ACCE_FADEWAIT:
		check = IMC_LBOX_ENDCheck( &fade_w->sys_w->lbox );
		if( check ){

			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_BRIGHTNESS_OUT:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_BLACK,
				BRIGHTNESS_NORMAL,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;


	case IMC_SEENFADEIN_BRIGHTNESS_WAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_BUTTON_OLDOUT:
		IMC_IMCBTTN_Move( &fade_w->sys_w->bttn, 0, IMC_SEENFADE_BTTNMOVE_ADD_Y );
		fade_w->work ++;
		if( fade_w->work >= IMC_SEENFADE_BTTNMOVE_COUNT ){
			fade_w->work = 0;
			fade_w->seq ++;
		}
		break;

	
	case IMC_SEENFADEIN_MOVE_BG:
		if( endSeenFadeMoveBg( fade_w, -IMC_SEENFADE_MOVE_ADD_X, IMC_SEENFADE_MOVE_ADD_Y, IMC_SEENFADE_MOVE_COUNT ) ){
			fade_w->work = 0;
			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_MOVE_BGINIT:
		// BG 1�ʂ�BG�ύX
		setFrameBG( fade_w->sys_w, IMC_BG_FRAME_01 );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, 0 );

		// �n�C�C�C�G�E�B���h�E�Z�b�g�A�b�v
		initTouchSWSys( fade_w->sys_w );
		fade_w->seq++;
		break;

		
	
	case IMC_SEENFADEIN_BRIGHTNESS_IN:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_NORMAL,
				BRIGHTNESS_BLACK,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;


	case IMC_SEENFADEIN_BRIGHTNESS_INWAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;
		
	case IMC_SEENFADEIN_END:
		*fade_w->end = TRUE;
		PMDS_taskDel( tcb );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�쐬��ʃt�F�[�h�J�n
 *
 *	@param	imc_w	�V�X�e�����[�N
 *	@param	end		�I�����m�t���O
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeOut( IMC_SYS_WORK* imc_w, BOOL* end )
{
	TCB_PTR tcb;
	IMC_SYS_FADE_WORK* fade_w;

	// �^�X�N�o�^
	tcb = PMDS_taskAdd( endSeenFadeOutTask, sizeof( IMC_SYS_FADE_WORK ), 10, HEAPID_IMAGECLIP_DATA );

	// ���[�N�Ƀf�[�^�ݒ�
	fade_w = TCB_GetWork( tcb );
	fade_w->sys_w	= imc_w;
	fade_w->end		= end;
	fade_w->work	= 0;
	fade_w->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�쐬��ʃt�F�[�h�^�X�N
 *
 *	@param	tcb		�^�X�N�I�u�W�F
 *	@param	work	���[�N
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeOutTask( TCB_PTR tcb, void* work )
{
	IMC_SYS_FADE_WORK* fade_w = work;
	BOOL	check;
	
	switch( fade_w->seq ){

	case IMC_SEENFADEOUT_BRIGHTNESS_OUT:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_BLACK,
				BRIGHTNESS_NORMAL,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;
			
	case IMC_SEENFADEOUT_BRIGHTNESS_OUTWAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;


	case IMC_SEENFADEOUT_MOVE_BG_SET:
		// �n�C�C�C�G�E�B���h�E�j��
		deleteTouchSWSys( fade_w->sys_w );
		// ���{�b�N�X�E�B���h�E�ݒ�
		setLeftBoxBg( fade_w->sys_w );
		// �{�^���̃A�j�����Z�b�g
		resetBttn( fade_w->sys_w );
		
		setFrameBG( fade_w->sys_w, IMC_BG_FRAME_00 );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, -IMC_SEENFADE_BG_MOVE_Y );
		fade_w->seq++;
		break;


	case IMC_SEENFADEOUT_MOVE_BG:
		if( endSeenFadeMoveBg( fade_w, IMC_SEENFADE_MOVE_ADD_X, -IMC_SEENFADE_MOVE_ADD_Y, IMC_SEENFADE_MOVE_COUNT ) ){
			fade_w->work = 0;
			fade_w->seq++;
		}
		break;


	case IMC_SEENFADEOUT_BUTTON_NEWIN:
		IMC_IMCBTTN_Move( &fade_w->sys_w->bttn, 0, -IMC_SEENFADE_BTTNMOVE_ADD_Y );
		fade_w->work ++;
		if( fade_w->work >= IMC_SEENFADE_BTTNMOVE_COUNT ){
			fade_w->work = 0;
			fade_w->seq ++;
		}
		break;

	case IMC_SEENFADEOUT_BRIGHTNESS_IN:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_NORMAL,
				BRIGHTNESS_BLACK,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;

	case IMC_SEENFADEOUT_BRIGHTNESS_WAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;
		
	case IMC_SEENFADEOUT_ACCE_FADEIN:
		check = IMC_LBOX_ChangeCurrentAccessorie( 
				&fade_w->sys_w->lbox,
				IMC_OBJLIST_ACCE,
				0);
		GF_ASSERT( check );	// ��������

		fade_w->seq++;
		break;
		
	case IMC_SEENFADEOUT_ACCE_FADEWAIT:
		check = IMC_LBOX_ENDCheck( &fade_w->sys_w->lbox );
		if( check ){

			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEOUT_END:
		*fade_w->end = TRUE;
		PMDS_taskDel( tcb );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N�V�[�P���X�@�I���{�^��
 *
 *	@param	bttn		�{�^���\����
 *	@param	work		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endCkEndBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// ��Ԑݒ�
	// ���	�I�����N�G�X�g
	imc_w->state = IMC_SYS_END_REQ;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N�V�[�P���X�@CANCEL�{�^��
 *
 *	@param	bttn		�{�^���\����
 *	@param	work		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endCkCancelBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// ��Ԑݒ�
	// ���	�I�����N�G�X�g
	imc_w->state = IMC_SYS_END_CANCEL_REQ;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�[�^�Z�[�u
 *
 *	@param	save_data	�Z�[�u�f�[�^
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void dataSave( IMC_TELEVISION_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, const MYSTATUS* cp_tr )
{
	IMC_OBJLIST* p_work;
	int count;
	STRBUF* p_str;
	int sex;

	ImcSaveData_ClaenTelevisionData( save_data );		// �ҏW���郏�[�N��������
	
	// �|�P�����f�[�^�ۑ�
	ImcSaveData_SetTelevisionPokeData( save_data, 
			rbox->boxDraw.poke.poke_para,
			&rbox->boxDraw.poke );

	// �g���[�i�[�f�[�^�ݒ�
	if( cp_tr ){
		p_str = MyStatus_CreateNameString( cp_tr, HEAPID_IMAGECLIP_DATA );
		sex = MyStatus_GetMySex( cp_tr );
		ImcSaveData_SetTelevisionTrData( save_data, p_str, sex );
		STRBUF_Delete( p_str );
	}

	// �A�N�Z�T���f�[�^�ۑ�
	count = 0;
	p_work = rbox->boxData.dummy_poke.next;
	while( p_work != &rbox->boxData.dummy_poke ){
		// �A�N�Z�T���f�[�^�Ȃ�ۑ�����	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			ImcSaveData_SetTelevisionAcceData( save_data, p_work->obj_data, count );
			count ++;
		}
		p_work = p_work->next;
	}
	p_work = rbox->boxData.dummy.next;
	while( p_work != &rbox->boxData.dummy ){
		// �A�N�Z�T���f�[�^�Ȃ�ۑ�����	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			ImcSaveData_SetTelevisionAcceData( save_data, p_work->obj_data, count );
			count ++;
		}
		p_work = p_work->next;
	}

	// BGID
	ImcSaveData_SetTelevisionBgId( save_data, rbox->boxDraw.bg_no );	

	// �Z�[�u����
	ImcSaveData_SetComplateFlagTelevisionData( save_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�p�Z�[�u�f�[�^�ۑ�
 *
 *	@param	save_data	�R���e�X�g�Z�[�u�f�[�^�ۑ���
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void dataSave_Contest( IMC_CONTEST_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, int rank, const MYSTATUS* cp_tr )
{
	int count;
	int i;
	IMC_POKE_ON_ACCESYS* p_sys;
	IMC_OBJLIST* p_obj;
	STRBUF* p_str;
	int sex;

	// �V�X�e��
	p_sys = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof(IMC_POKE_ON_ACCESYS) );
	initPokeOnAcceCheckSys( p_sys );
	
	// �|�P�����f�[�^�ۑ�
	ImcSaveData_SetContestPokeData( save_data, 
			rbox->boxDraw.poke.poke_para,
			&rbox->boxDraw.poke );


	// �g���[�i�[�f�[�^�ݒ�
	if( cp_tr ){
		p_str = MyStatus_CreateNameString( cp_tr, HEAPID_IMAGECLIP_DATA );
		sex = MyStatus_GetMySex( cp_tr );
		ImcSaveData_SetContestTrData( save_data, p_str, sex );
		STRBUF_Delete( p_str );
	}

	// �܂��S�A�N�Z�T���f�[�^�����[�N�ɐݒ肷��
	setPokeOnAcceCheckObjList( p_sys, &rbox->boxData.dummy_poke, IMC_POKEON_ACCE_ON );
	setPokeOnAcceCheckObjList( p_sys, &rbox->boxData.dummy, IMC_POKEON_ACCE_NONE );

	// �|�P�����ɂ��Ă���A�N�Z�T���`�F�b�N
	mainPokeOnAcceCheckSys( p_sys );

	// �A�N�Z�T���f�[�^�ۑ�
	count = 0;
	for( i=0; i<IMC_POKEON_ACCE_CHECK_OBJNUM; i++ ){

		if( getPokeOnAcceCheckObjOnPoke( p_sys, i ) == TRUE ){
			p_obj = getPokeOnAcceCheckObjList( p_sys, i );
			ImcSaveData_SetContestAcceData( save_data, p_obj->obj_data, count );
			count ++;
		}
	}

	// BGID
	ImcSaveData_SetContestBgId( save_data, rbox->boxDraw.bg_no );	
	// �����N�̕ۑ�
	ImcSaveData_SetContestRank( save_data, rank );

	// �Z�[�u����
	ImcSaveData_SetComplateFlagContestData( save_data );


	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[���t�F�[�h�@BG�ƃ|�P�����A�N�Z�T�������ړ��֐�
 *
 *	@param	fade_w				�t�F�[�h���[�N
 *	@param	move_x				X�ύX�l			(�|�P�����I�u�W�F�N�g�ɂ��킹��)
 *	@param	move_y				Y�ύX�l			(�|�P�����I�u�W�F�N�g�ɂ��킹��)
 *	@param	move_count_num		�����ő�l
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	���s
 */
//-----------------------------------------------------------------------------
static BOOL endSeenFadeMoveBg( IMC_SYS_FADE_WORK* fade_w, int move_x, int move_y, int move_count_num )
{
	// 3D�̃I�u�W�F�N�g�͕`��^�C�~���O�̉e���ŁA���f��1�V���N�x���Ȃ��Ă��܂��̂ŁA�P���ɕύX����
	if( fade_w->work < IMC_SEENFADE_MOVE_COUNT ){
		IMC_RBOX_ListMove( &fade_w->sys_w->rbox, move_x, move_y );
	}

	// �QD�I�u�W�F�N�g�͂P��x���^�C�~���O�ŕύX����
	if( fade_w->work >= 1 ){
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, move_x );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_X_DEC, move_x );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_DEC, move_y );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_DEC, move_y );
	}
	
	fade_w->work++;
	if( fade_w->work > move_count_num ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�@�����J�n
 *
 *	@param	imc_w	���[�N
 */
//-----------------------------------------------------------------------------
static void initConTextSys( IMC_SYS_WORK* imc_w )
{
	// �X�N���[���N���[��
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
	
	// �r�b�g�}�b�v�E�B���h�E�`��
	initContestTextBmpWin( imc_w, 0 );

	// �\���D�揇�ʐݒ�
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );

	//FRAME3�����\��������
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	// WIPE�j��
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�@�����I��
 *
 *	@param	imc_w	���[�N
 */
//-----------------------------------------------------------------------------
static void deleteConTextSys( IMC_SYS_WORK* imc_w )
{
	// �r�b�g�}�b�v�j��
	deleteContestTextBmpWin( imc_w );

	// �X�N���[����������
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );

	// ���{�b�N�X�O���t�B�b�N�Đݒ�
	setLeftBoxBg( imc_w );

	// WIPE�ݒ�
	WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );

	// �ŏ��A�N�^�[�Z�b�g�\��
	CLACT_DrawFlagSet( imc_w->drawSys.clactSet, 1 );

	//�S�ĕ\��������
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʁ@�G���E�B���h�E�@������
 *
 *	@param	imc_w	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initTouchSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_PARAM touch_prm;

	// �X�N���[���N���[��
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
	
	// YES NO �E�B���h�E�{�^���̕\��
	touch_prm.p_bgl		= imc_w->drawSys.BG_Ini;
	touch_prm.bg_frame	= GF_BGL_FRAME3_M;
	touch_prm.char_offs	= IMC_ENDCHECK_YESNO_CHAR_OFFS;
	touch_prm.pltt_offs = IMC_ENDCHECK_YESNO_PLTT_OFFS;
	touch_prm.x			= IMC_ENDCHECK_YESNO_X;
	touch_prm.y			= IMC_ENDCHECK_YESNO_Y;
	TOUCH_SW_Init( imc_w->p_tsw, &touch_prm );

	// �r�b�g�}�b�v�E�B���h�E�`��
	initTouchSWBmpWin( imc_w, imgclip_ok );

	// �\���D�揇�ʐݒ�
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʁ@�G���E�B���h�E�@�j��
 *
 *	@param	imc_w	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void deleteTouchSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_Reset( imc_w->p_tsw );

	// �r�b�g�}�b�v�j��
	deleteTouchSWBmpWin( imc_w );

	// �X�N���[����������
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʁ@�G���E�B���h�E�@���C������
 *
 *	@param	imc_w	���[�N
 *
 *	@retval	IMC_SYS_END_CHECK			// �����Ȃ�
 *	@retval	IMC_SYS_END_REQ				// �͂�
 *	@retval	IMC_SYS_END_CANCEL_REQ		// ������
 */
//-----------------------------------------------------------------------------
static u32 mainTouchSWSys( IMC_SYS_WORK* imc_w )
{
	u32 ret;
	ret = TOUCH_SW_Main( imc_w->p_tsw );

	switch( ret ){
	case TOUCH_SW_RET_NORMAL:	// �����Ȃ�
		ret = IMC_SYS_END_CHECK;
		break;
		
	case TOUCH_SW_RET_YES:	// �͂�
		ret = IMC_SYS_END_REQ;
		break;
		
	case TOUCH_SW_RET_NO:		// ������
		ret = IMC_SYS_END_CANCEL_REQ;
		break;
	}
	
	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�̏�����
 *
 *	@param	imc_w 
 *	@param	str_idx		������ID
 *	@param	cx			���L�����N�^�ʒu
 *	@param	cy			���L�����N�^�ʒu
 *	@param	csx			���L�����N�^�T�C�Y
 *	@param	csy			���L�����N�^�T�C�Y
 */
//-----------------------------------------------------------------------------
static void initMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx, u8 cx, u8 cy, u8 csx, u8 csy )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	WINTYPE wnd_no = CONFIG_GetWindowType( imc_w->cp_config );
	
	
	// �����t�H���g�J���[�p���b�g�]��
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, IMC_ENDCHECK_WND_PAL*32, HEAPID_IMAGECLIP_DRAW );
	
	// �r�b�g�}�b�v�E�B���h�E�쐬
	GF_BGL_BmpWinAdd( imc_w->drawSys.BG_Ini,
			imc_w->p_tsw_bmp, GF_BGL_FRAME3_M,
			cx, cy,
			csx, csy,
			IMC_ENDCHECK_WND_PAL, IMC_ENDCHECK_WND_CHROFS );
	// �N���[��
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// �g�`��
	TalkWinGraphicSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, IMC_ENDCHECK_WNDWAKU_CHROFS, IMC_ENDCHECK_WNDWAKU_PAL, wnd_no, HEAPID_IMAGECLIP_DRAW );
	BmpTalkWinWrite( imc_w->p_tsw_bmp, WINDOW_TRANS_ON, IMC_ENDCHECK_WNDWAKU_CHROFS, IMC_ENDCHECK_WNDWAKU_PAL );

	// �����`��
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	str = MSGMAN_AllocString( msg_data, str_idx );
	GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, str, 0, 0, 0, IMC_ENDCHECK_WND_PRICOLOR, NULL );
	// �������j��
	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	// �]��
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�ɕ������`��
 *
 *	@param	imc_w		���[�N
 *	@param	str_idx		������ID
 */
//-----------------------------------------------------------------------------
static void setMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	STRBUF* p_exstr;
	
	// �N���[��
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// �����`��
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	p_exstr = MSGMAN_AllocString( msg_data, str_idx );
	str = STRBUF_Create( 256, HEAPID_IMAGECLIP_DATA );

	WORDSET_ExpandStr( imc_w->p_wordset, str, p_exstr );
	
	GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, str, 0, 0, 0, IMC_ENDCHECK_WND_PRICOLOR, NULL );

	// �������j��
	STRBUF_Delete( str );
	STRBUF_Delete( p_exstr );
	MSGMAN_Delete( msg_data );

	// �]��
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�Z�[�W����`��
 *
 *	@param	imc_w		���[�N
 *	@param	str_idx		������ID
 *
 *	@return	���b�Z�[�WIDX
 */
//-----------------------------------------------------------------------------
static u32 setMsgBmpWin_okuri( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	u32 msg_index;
	MSGDATA_MANAGER* msg_data;
	u32 speed;
	STRBUF* p_exstr;

	GF_ASSERT( imc_w->p_glb_str == NULL );
	
	// �N���[��
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// �����`��
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	p_exstr = MSGMAN_AllocString( msg_data, str_idx );
	imc_w->p_glb_str = STRBUF_Create( 256, HEAPID_IMAGECLIP_DATA );

	WORDSET_ExpandStr( imc_w->p_wordset, imc_w->p_glb_str, p_exstr );
	
	if( imc_w->p_comm_data->sio_flag == 0 ){
		speed = CONFIG_GetMsgPrintSpeed( imc_w->cp_config );
	}else{
		speed = CONTEST_SIO_MSG_SPEED;
	}
	
	msg_index = GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, imc_w->p_glb_str, 0, 0, speed, IMC_ENDCHECK_WND_PRICOLOR, NULL );

	STRBUF_Delete( p_exstr );
	// �������j��
	MSGMAN_Delete( msg_data );

	// �]��
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����悤���[�N�j��
 *
 *	@param	imc_w 
 */
//-----------------------------------------------------------------------------
static void endMsgBmpWin_okuri( IMC_SYS_WORK* imc_w )
{
	STRBUF_Delete( imc_w->p_glb_str );
	imc_w->p_glb_str = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�̔j��
 *
 *	@param	imc_w	���[�N
 */
//-----------------------------------------------------------------------------
static void deleteMsgBmpWin( IMC_SYS_WORK* imc_w )
{
	// �]��
	GF_BGL_BmpWinOff( imc_w->p_tsw_bmp );
	GF_BGL_BmpWinDel( imc_w->p_tsw_bmp );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�I���`�F�b�N�r�b�g�}�b�v�E�B���h�E�쐬
 *
 *	@param	imc_w 
 *	@param	str_idx		������ID
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void initTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	initMsgBmpWin( imc_w, str_idx, 
			IMC_ENDCHECK_WND_X, IMC_ENDCHECK_WND_Y,
			IMC_ENDCHECK_WND_SIZX, IMC_ENDCHECK_WND_SIZY );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���`�F�b�N�r�b�g�}�b�v�E�B���h�E������ݒ�
 *
 *	@param	imc_w 
 *	@param	str_idx		������ID
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void setTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	setMsgBmpWin( imc_w, str_idx );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�������p�r�b�g�}�b�v�E�B���h�E�j��
 *
 *	@param	imc_w	
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void deleteTouchSWBmpWin( IMC_SYS_WORK* imc_w )
{
	deleteMsgBmpWin( imc_w );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�e�L�X�g	����BMP�쐬
 *
 *	@param	imc_w	���[�N
 *	@param	str_idx ���b�Z�[�W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	initMsgBmpWin( imc_w, str_idx, 
			IMC_CONTESTTEXT_WND_X, IMC_CONTESTTEXT_WND_Y,
			IMC_CONTESTTEXT_WND_SIZX, IMC_CONTESTTEXT_WND_SIZY );

	// ���[�h�Z�b�g�쐬
	imc_w->p_wordset = WORDSET_Create( HEAPID_IMAGECLIP_DATA );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�e�L�X�g�@
 *
 *	@param	imc_w		���[�N
 *	@param	str_idx		������ID
 *
 *	@return	���b�Z�[�WIDX
 */
//-----------------------------------------------------------------------------
static u32 setContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	return setMsgBmpWin_okuri( imc_w, str_idx );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�h�Z�b�g�ɐݒ�
 *
 *	@param	imc_w	���[�N
 *	@param	buff_id	�o�b�t�@ID
 *	@param	no		����
 */
//-----------------------------------------------------------------------------
static void setContestWordSet( IMC_SYS_WORK* imc_w, int buff_id, int no )
{
	WORDSET_RegisterNumber( imc_w->p_wordset, buff_id, no, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	������j��
 */
//-----------------------------------------------------------------------------
static void endContestTextBmpWin( IMC_SYS_WORK* imc_w )
{
	endMsgBmpWin_okuri( imc_w );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�e�L�X�gBMP�j��
 *
 *	@param	imc_w	���[�N
 */
//-----------------------------------------------------------------------------
static void deleteContestTextBmpWin( IMC_SYS_WORK* imc_w )
{
	deleteMsgBmpWin( imc_w );

	// ���[�h�Z�b�g�j��
	WORDSET_Delete( imc_w->p_wordset );
	imc_w->p_wordset = NULL;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�E�{�b�N�X�̃A�N�Z�T���o�^����ݒ�
 *
 *	@param	imc_w	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setAcceNumSubWin( IMC_SYS_WORK* imc_w )
{
	int acce_num;

	acce_num = IMC_RBOX_GetNowHaveAcceNum( &imc_w->rbox );
	
	// �E�{�b�N�X�̔z�u�A�N�Z�T���f�[�^��ݒ�
	IMC_SUBWIN_SetAcceIcon( &imc_w->subwin, acce_num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�̃����N�ɂ��A�A�N�Z�T���ő吔���擾
 *
 *	@param	rank	�����N��
 *
 *	@return	�A�N�Z�T����
 */
//-----------------------------------------------------------------------------
static int getRightAcceMax_contest( int rank )
{
	int acce_max;
	
	switch( rank ){
	case CONRANK_NORMAL:
		acce_max = CON_IMAGE_ACCE_MAX_NORMAL;
		break;

	case CONRANK_SUPER:
		acce_max = CON_IMAGE_ACCE_MAX_SUPER;
		break;

	case CONRANK_HYPER:
		acce_max = CON_IMAGE_ACCE_MAX_HYPER;
		break;

	case CONRANK_MASTER:
		acce_max = CON_IMAGE_ACCE_MAX_MASTER;
		break;

	default:
		// �����N�s��
		GF_ASSERT(0);
		break;
	}

	return acce_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u���邩�����p�C�G�X�m�[�{�^��������
 *
 *	@param	imc_w	���[�N
 *
 *	@return	none
 *
 *	�I���`�F�b�N�̃n�C�C�C�G�������p���܂�
 */
//-----------------------------------------------------------------------------
static void initTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_PARAM touch_prm;

	// YES NO �E�B���h�E�{�^���̕\��
	touch_prm.p_bgl		= imc_w->drawSys.BG_Ini;
	touch_prm.bg_frame	= GF_BGL_FRAME3_M;
	touch_prm.char_offs	= IMC_ENDCHECK_YESNO_CHAR_OFFS;
	touch_prm.pltt_offs = IMC_ENDCHECK_YESNO_PLTT_OFFS;
	touch_prm.x			= IMC_ENDCHECK_YESNO_X;
	touch_prm.y			= IMC_ENDCHECK_YESNO_Y;
	TOUCH_SW_Reset( imc_w->p_tsw );
	TOUCH_SW_Init( imc_w->p_tsw, &touch_prm );

	// �r�b�g�}�b�v�E�B���h�E�`��
	setTouchSWBmpWin( imc_w, imgclip_ng );

	// �\���D�揇�ʐݒ�
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^�`�F�b�N YESNO ���C������
 *
 *	@param	imc_w	���[�N
 *
 *	@retval	
 */
//-----------------------------------------------------------------------------
static u32 mainTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w )
{
	u32 ret;
	ret = TOUCH_SW_Main( imc_w->p_tsw );

	switch( ret ){
	case TOUCH_SW_RET_NORMAL:	// �����Ȃ�
		ret = IMC_SYS_SAVE_CHECK_REQ;
		break;
		
	case TOUCH_SW_RET_YES:	// �͂�
		ret = IMC_SYS_SAVE;
		break;
		
	case TOUCH_SW_RET_NO:		// ������
		ret = IMC_SYS_SAVE_CAN;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ɃA�N�Z�T���`���łȂ����Ă��邩�`�F�b�N����V�X�e���@������	�i���[�N���O�N���A�j
 *
 *	@param	p_sys	�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys )
{
	memset( p_sys, 0, sizeof(IMC_POKE_ON_ACCESYS) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ɃA�N�Z�T���`���łȂ����Ă��邩�`�F�b�N����V�X�e���@�I�u�W�F�N�g���X�g�ݒ�
 *
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	obj			�I�u�W�F�N�g
 *	@param	init_data	�|�P�����ɂ������Ă��邩�̏����l
 *
 *	@return	none
 *
 *	init_data	
 *		�ŏ�����|�P�����ɂ������Ă���Ƃ킩���Ă�����̂ɂ�1��n���Ă���
 *		IMC_POKEON_ACCE_NONE	�|�P�����ɂ������Ă��Ȃ�
 *		IMC_POKEON_ACCE_ON		�|�P�����ɂ������Ă���
 */
//-----------------------------------------------------------------------------
static void setPokeOnAcceCheckObj( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* obj, u32 init_data )
{
	//�@NULL�͂���
	GF_ASSERT( obj );
	p_sys->obj[ p_sys->set_num ].obj			= obj;
	p_sys->obj[ p_sys->set_num ].pokemon_data	= init_data;
	p_sys->set_num++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ɃA�N�Z�T���`���łȂ����Ă��邩�`�F�b�N����V�X�e���@�`�F�b�N�֐�
 *
 *	@param	p_sys	�V�X�e�����[�N
 *
 *	@return	none
 *
 *	���̊֐����s������@getPokeOnAcceCheckObjOnPoke��
 *	������������ƃA�N�Z�T���`���łȂ����Ă��邩���킩��
 */
//-----------------------------------------------------------------------------
static void mainPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys )
{
	int i, j;
	BOOL result;

	// �|�P�����ɂ������Ă���A�N�Z�T������
	// ���肵�Ă����A�͈͓��̃A�N�Z�T������������A
	// �����̒l������A�S�����肵���玩���ɂQ������
	// ����[IMC_POKEON_ACCE_ON]�̃A�N�Z�T�������x�́A
	// �͂�Ă�����
	// ������J��Ԃ�
	i=0;
	while( i<p_sys->set_num ){

		if( p_sys->obj[ i ].pokemon_data == IMC_POKEON_ACCE_ON ){

			// �����蔻��Ȃ��Ȃ�`�F�b�N�Ώۂ̃A�N�Z�T�����|�P�����ƂȂ����Ă���
			for( j=0; j<p_sys->set_num; j++ ){

				if( p_sys->obj[ j ].pokemon_data == IMC_POKEON_ACCE_NONE ){
					result = checkPokeOnAcceCalc( 
							&p_sys->obj[ i ], &p_sys->obj[ j ] );
					if( result == TRUE ){
						p_sys->obj[ j ].pokemon_data = IMC_POKEON_ACCE_ON;
					}
				}
			}
			// SEARCH����
			p_sys->obj[ i ].pokemon_data = IMC_POKEON_ACCE_SEARCHEND;
			// ������x�擪����`�F�b�N
			i = 0;
		}else{
			i++;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�i���o�[�̃I�u�W�F�N�g���X�g���擾����
 *
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	no			�z��C���f�b�N�X
 *
 *	@return	�I�u�W�F�N�g���X�g
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, u32 no )
{
	GF_ASSERT(no < IMC_POKEON_ACCE_CHECK_OBJNUM);

	return p_sys->obj[ no ].obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ɃA�N�Z�T���`���łȂ����Ă��邩�`�F�b�N����V�X�e���@���̃A�N�Z�T�����Ȃ����Ă��邩��Ԃ�
 *
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	no			�z��C���f�b�N�X
 *	
 *	@retval	TRUE	�Ȃ����Ă���
 *	@retval	FALSE	�Ȃ����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL getPokeOnAcceCheckObjOnPoke( IMC_POKE_ON_ACCESYS* p_sys, u32 no )
{
	GF_ASSERT(no < IMC_POKEON_ACCE_CHECK_OBJNUM);
	
	if( p_sys->obj[ no ].pokemon_data ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����蔻��
 *
 *	@param	p_obj		�������ƂȂ����Ă��邩�`�F�b�N���Ă���I�u�W�F�N�g
 *	@param	p_check_obj	�`�F�b�N�����I�u�W�F�N�g
 *
 *	@retval	TRUE	�������Ă���
 *	@retval	FLASE	�������Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
enum{
	IMC_POKEON_ACCE_TOP,
	IMC_POKEON_ACCE_BOTTOM,
	IMC_POKEON_ACCE_LEFT,
	IMC_POKEON_ACCE_RIGHT,
	IMC_POKEON_ACCE_YHALF,
	IMC_POKEON_ACCE_XHALF,
	IMC_POKEON_ACCE_POS_NUM
};
static BOOL checkPokeOnAcceCalc( IMC_POKE_ON_ACCEOBJ* p_obj, IMC_POKE_ON_ACCEOBJ* p_check_obj )
{
	int pos[IMC_POKEON_ACCE_POS_NUM];
	BOOL result;
	int i;
	int x, y;
	
	// 16�_�`�F�b�N����
	// �㉺���E�@�^��
	// �^��
	IMC_OBJLIST_GetObjCenterMat( p_obj->obj, &pos[IMC_POKEON_ACCE_XHALF], &pos[IMC_POKEON_ACCE_YHALF] );
	IMC_OBJLIST_GetObjRectSubInSize( p_obj->obj,
			&pos[IMC_POKEON_ACCE_TOP], &pos[IMC_POKEON_ACCE_BOTTOM], 
			&pos[IMC_POKEON_ACCE_LEFT], &pos[IMC_POKEON_ACCE_RIGHT] );

	for( i=0; i<16; i++ ){
		IMC_CALC_HitPoint16Get( pos[IMC_POKEON_ACCE_TOP], pos[IMC_POKEON_ACCE_BOTTOM],
				pos[IMC_POKEON_ACCE_LEFT], pos[IMC_POKEON_ACCE_RIGHT], i,
				&x, &y );	
/*		switch( i ){
		case 0:	// ����
			x = pos[IMC_POKEON_ACCE_LEFT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 1:	// �E��
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 2:	// ����
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 3:	// �E��
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 4:	// ���^��
			x = pos[IMC_POKEON_ACCE_LEFT];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		case 5:	// �E�^��
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		case 6:	// �^�񒆏�
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 7:	// �^�񒆉�
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_BOTTOM];
			break;
		case 8:	// �^��
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		default:
			GF_ASSERT(0);
			break;
		}//*/

		result = IMC_OBJLIST_ACCEPOKE_Hit( p_check_obj->obj, x, y );
		if( result == TRUE ){	// ���������甲����
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g���X�g���̃A�N�Z�T����S���@�`�F�b�N�p�e�[�u���ɓ����
 *
 *	@param	p_sys		���[�N
 *	@param	dummy		�_�~�[�f�[�^
 *	@param	init_data	�������f�[�^
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* dummy, u32 init_data )
{
	IMC_OBJLIST* p_work;

	p_work = dummy->next;	// �|�P�����̏�̃A�N�Z�T��
	while( p_work != dummy ){
		// �A�N�Z�T���f�[�^�Ȃ�ۑ�����	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			setPokeOnAcceCheckObj( p_sys, p_work, init_data );
		}
		p_work = p_work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����I���`�F�b�N
 *
 *	@param	imc_w 
 */
//-----------------------------------------------------------------------------
static void Imc_OyaExEndCheck( IMC_SYS_WORK* imc_w )
{
	int i;
	int count = 0;
	
	// �����ʐM���Ă��Ȃ��Ƃ��͖�������0�ɂ���
	if( imc_w->p_comm_data->sio_flag == 0 ){
		IMC_SUBWIN_SetCounterNowNum( &imc_w->subwin, 0 );
		return ;
	}

	// �����e�Ȃ�F����I���t���O�𒲂ׂ�
	if( imc_w->p_comm_data->server_no == imc_w->p_comm_data->my_net_id ){
		for( i=0; i<BREEDER_MAX; i++ ){
			if( imc_w->p_comm_data->recieve_force_end[i] == TRUE ){
				count ++;
			}
		}
		
		// �S������I���������̂ŃJ�E���g�l���O�ɂ���
		if( imc_w->p_comm_data->player_num  <= count ){
			IMC_SUBWIN_SetCounterNowNum( &imc_w->subwin, 0 );
		}
	}

}



//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�����蔻��|�C���g�擾�֐�
 *
 *	@param	top			�g�b�v
 *	@param	bottom		�{�g��
 *	@param	left		���t�g
 *	@param	right		���C�g
 *	@param	no			�����蔻��|�C���g�i���o�[(�O�`�P�T)
 *	@param	p_x			X���W�i�[��
 *	@param	p_y			Y���W�i�[��
 */
//-----------------------------------------------------------------------------
void IMC_CALC_HitPoint16Get( u32 top, u32 bottom, u32 left, u32 right, u32 no, int* p_x, int* p_y )
{
	u32 halfx_0, halfx_1;
	u32 halfy_0, halfy_1;
	
	halfx_0 = left + ((right - left) / 3);
	halfx_1 = left + ((right - left) / 3)*2;

	halfy_0 = top + ((bottom - top) / 3);
	halfy_1 = top + ((bottom - top) / 3)*2;
	
	switch( no ){
	case 0:	// ����
		*p_x = left;
		*p_y = top;
		break;

	case 1:	// ���@���ԂO
		*p_x = left;
		*p_y = halfy_0;
		break;

	case 2:	// ���@���ԂP
		*p_x = left;
		*p_y = halfy_1;
		break;

	case 3:	// ����
		*p_x = left;
		*p_y = bottom;
		break;

	case 4:	// ���ԂO�@��
		*p_x = halfx_0;
		*p_y = top;
		break;

	case 5:	// ���ԂO�@���ԂO
		*p_x = halfx_0;
		*p_y = halfy_0;
		break;

	case 6:	// ���ԂO�@���ԂP
		*p_x = halfx_0;
		*p_y = halfy_1;
		break;

	case 7:	// ���ԂO�@��
		*p_x = halfx_0;
		*p_y = bottom;
		break;

	case 8:	// ���ԂP�@��
		*p_x = halfx_1;
		*p_y = top;
		break;

	case 9:	// ���ԂP�@���ԂO
		*p_x = halfx_1;
		*p_y = halfy_0;
		break;

	case 10:	// ���ԂP�@���ԂP
		*p_x = halfx_1;
		*p_y = halfy_1;
		break;

	case 11:	// ���ԂP�@��
		*p_x = halfx_1;
		*p_y = bottom;
		break;

	case 12:	// �E�@��
		*p_x = right;
		*p_y = top;
		break;

	case 13:	// �E�@���ԂO
		*p_x = right;
		*p_y = halfy_0;
		break;

	case 14:	// �E�@���ԂP
		*p_x = right;
		*p_y = halfy_1;
		break;

	case 15:	// �E�@��
		*p_x = right;
		*p_y = bottom;
		break;
	}
}

