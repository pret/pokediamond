//============================================================================================
/**
 * @file	namein.c
 * @bfief	���O���͉�ʏ���
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================
#define USE_PARAM_STR		// NAMEIN_PARAM�� u16 str[20]���K�v�ȊԗL���ɂ���

//#define DEBUG_OAM_POSPRINT	// �L���ɂ���ƃ^�b�`�p�l���̓�����̈���m�F�ł���


#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/window.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_namein.h"
#include "msgdata/msg_fightmsg_dp.h"
#include "system/wipe.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/msg_ds_icon.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/boxdata.h"
#include "application/namein.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "namein_snd_def.h"

// �L���ɂ����LCD���㉺�t�ɂ��ă^�b�`�p�l���œ��͂ł���悤�ɂȂ�
#define NAMEIN_MAINUSE_TOUCHPANEL

#define POKEICON_VRAM_OFFSET (22*32+31)
#define POKEICON_PAL_OFFSET	 ( 6 )

// CLACT�Œ�`���Ă���Z�����傫�����ăT�u��ʂɉe�����łĂ��܂��̂ŗ����Ă݂�
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)


// ���͂����������\������ۂ̊Ԋu
#define INPUT_WORD_SPACE (12)		

// �����p�l���̕����̊Ԋu
#define WORDPANEL_WORD_SPACE (16)		

// ������ރp�l�����n�m�ɂȂ�܂Ń^�b�`���L���ɂȂ�Ȃ��悤�ɂ��邽�߂̃E�F�C�g
#define TOUCH_START_WAIT	 ( 5 )

#include "namein.naix"			// �O���t�B�b�N�A�[�J�C�u��`
#include "../../field/poketch/poketch_arc.h"

#ifdef DEBUG_OAM_POSPRINT

static CLACT_WORK_PTR	testclact[4];
static int              testclact_no = 0;

#endif

//============================================================================================
//	�萔��`
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_WAIT,
	SEQ_MAIN,
	SEQ_OUT,
};


typedef struct {
	int x;			// ���݈ʒu
	int y;			//
	int oldx;		// 1STEP�O�̈ʒu
	int oldy;		//
	int lastxarrow;	// �Ō�̈ړ�����

	int on;			// �\��ON�EOFF
	int decide;		// ����A�j�����H
}NAMEIN_CURSOR;

#define INPUT_SCREEN_MAX	( 5)	
#define INPUT_WORD_W		(13)
#define INPUT_WORD_H		( 6)
#define INPUT_WORD_WH		(INPUT_WORD_W*INPUT_WORD_H)
#define INPUT_WORD_MAX		(32)	//�����͖���

// CellActor�ɏ��������郊�\�[�X�}�l�[�W���̎�ނ̐��i���}���`�Z���E�}���`�Z���A�j���͎g�p���Ȃ��j
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )
#define NAMELINE_OAM_NUM		( 12 )

// �J�[�\����CLACT_WORK�i���o�[
#define CLACT_CURSOR_NUM		(  8 )

// �����p�l���̓]����
#define WORDPANEL_TRANS_SIZE	( 32*14*2 )

// �����p�l���̈ʒu��`
#define WORDPANEL_POS_REGX		(  -11 )
#define WORDPANEL_POS_REGY		(  -80 )
#define HIDDENPANEL_POS_REGX	(  238 )
#define DOWNPANEL_POS_REGY		( -196 )

#define WORDPANEL_IN_SPEED		( 24 )
#define WORDPANEL_OUT_SPEED		( 10 )

// ���͍ςݕ����̉���OBJ
#define NAMELINE_POS_X			( 10*8   )
#define NAMELINE_POS_Y			(  4*8+5 )

// �p�\�R���E���@�E�|�P�����A�C�R��OBJ�ʒu
#define NAMEIN_MYICON_X			( 24 )
#define NAMEIN_MYICON_Y			( 16-8 )

// �|�P�����̐��ʃA�C�R���̈ʒu
#define NAMEIN_SEXICON_Y		( NAMELINE_POS_Y - 12)

// ���O���͏��ʒu��`�i���Ȃ��̂Ȃ܂��́H�j
#define NAME_INFO_POSX			(  7 )
#define NAME_INFO_POSY			(  2 )
#define NAME_INFO_POSW			( 22 )
#define NAME_INFO_POSH			(  2 )
#define NAMEINFO_WIN_SIZE		( NAME_INFO_POSW*NAME_INFO_POSH )


// ���O���͌��ʕ\���ʒu��`
#define NAME_RESULT_POSX		( 10   )
#define NAME_RESULT_POSY		(  3   )
#define NAME_RESULT_POSW		( 9*2  )
#define NAME_RESULT_POSH		(  2   )
#define NAME_RESULT_WIN_SIZE	( NAME_RESULT_POSW*NAME_RESULT_POSH )

// �u�O���[�v�v������\���p��`
#define GROUP_TEXT_POSX			(  10+9 )
#define GROUP_TEXT_POSY			(  NAME_RESULT_POSY )
#define GROUP_TEXT_POSW			(  7  )
#define GROUP_TEXT_POSH			(  2  )
#define GROUP_TEXT_WIN_SIZE		( GROUP_TEXT_POSW*GROUP_TEXT_POSH )


#define FLD_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E�p���b�g
#define FLD_MESFONT_PAL      ( 12 )         //  ���b�Z�[�W�t�H���g�p���b�g


// ��b�E�C���h�E�ʒu��`(�t�B�[���h����̃R�s�[)
#define	TALK_MSG_WIN_PX		(  2 )
#define	TALK_MSG_WIN_PY		( 19 )
#define	TALK_MSG_WIN_SX		( 27 )
#define	TALK_MSG_WIN_SY		(  4 )
#define	TALK_MSG_WIN_PAL	( FLD_MESFONT_PAL )

// BG2�̃O���t�B�b�N�f�[�^�T�C�Y�Ɖ�b�E�C���h�E�L�����f�[�^�̊J�n�ʒu
#define NAMEIN_BG2GRAPHIC_NUM	  ( 32*8 )
#define NAMEIN_BG2GRAPHIC_SIZE	  ( NAMEIN_BG2GRAPHIC_NUM*0x20 )
#define NAMEIN_TALKWIN_CGX_OFFSET ( NAMEIN_BG2GRAPHIC_NUM )



// �����p�l���̑J�ڗp
enum{
	NAMEIN_MODE_REQ  = 0, 
	NAMEIN_MODE_SET,
	NAMEIN_MODE_ANIM,
	NAMEIN_MODE_ANIM_WAIT,
	NAMEIN_MODE,
	NAMEIN_MODE_BOXMSG,
	NAMEIN_MODE_BOXMSG_END,
	NAMEIN_MODE_BOXMSG_END_WAIT,
};

// �@�\�{�^����`
enum{
	NAMEIN_MODE_HIRA = 0,
	NAMEIN_MODE_KANA,
	NAMEIN_MODE_ALPHA,
	NAMEIN_MODE_KIGOU,
	NAMEIN_MODE_NUMCODE,
};

// �㉺��ʎw���`
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// �v�͂O��
#define SUB_LCD		( GF_BGL_SUB_DISP )		// �P�Ȃ�ł����B

// �^�b�`�p�l�������`����Ƃ��Ɏg��
#define PANEL_X		( 28 )
#define PANEL_Y		( 88 )
#define PANEL_H		( 19 )


// BMPWIN�w��
enum{
	BMP_WORDPANEL_BG0=0,
	BMP_WORDPANEL_BG1,
	BMP_TITLE_MES,
	BMP_RESULT_NAME,
	BMP_SUB_BUTTON1,
	BMP_SUB_BUTTON2,
	BMP_SUB_BUTTON3,
	BMP_SUB_STRING,
	BMP_GROUP_STRING,
	BMP_TALK_WIN,
	BMP_NAMEIN_MAX,
};

// �@�\�{�^���p��`
#define FUNCBUTTON_NUM	( 7 ) 		// �@�\�{�^���̐�

// �e�f�[�^��`

#include "namein.dat"

//============================================================================================
//	�\���̒�`
//============================================================================================

struct NAMEIN_WORK{

	int    inputmode;										// ���̓��[�h�i0:��l��,1:�|�P����,2:�{�b�N�X
	int    inputinfo;										// ���͏��i�j���A�|�P����NO�Ȃ�
	int    inputform;										// ���߂����i�|�P�����`��j
	int    inputmax;										// ���͕����ő吔
	int    inputsex;										// �|�P�����̎��͐��ʂ�\������
	int    endmode;											// 1�̎��̓|�P������BOX�ɓ]������|�̃��b�Z�[�W���ł�
	CONFIG *config;

	NAMEIN_CURSOR 	Cursor;									// �J�[�\�����@X�EY�E�ߋ�X�E�\��ON
	u16				CursorPal;
	u16 			wordmap[INPUT_WORD_H][INPUT_WORD_W];	// �����Ճ}�b�v
	u16 			nowmap;									// ���݂̕����}�b�v
	u16 			inputword[INPUT_WORD_MAX];				// ���͂���������
	u16 			paramstr[INPUT_WORD_MAX];				// ����������(�Ăяo�����Ɋi�[����Ă���������i��r�Ɏg�p�j�j
	u16				nowinput;								// ���݂̃J�[�\���ʒu
	u16				subtouchword[3];						// �R�̉��{�^���ɔz�u����Ă��镶���R�[�h
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;								// ���C�v�����I�����o�t���O

	WORDSET			*WordSet;								// ���b�Z�[�W�W�J�p���[�N�}�l�[�W���[
	MSGDATA_MANAGER *MsgManager;							// ���O���̓��b�Z�[�W�f�[�^�}�l�[�W���[
	MSGDATA_MANAGER *MsgDefaultName;						// �����̖��O��⃁�b�Z�[�W�f�[�^
	MSGDATA_MANAGER *FightMsgManager;						// �|�P�����ߊl�̎��̃��b�Z�[�W�f�[�^��퓬����Q��
	STRBUF			*TitleStr;								// ���O���̓^�C�g��
	STRBUF			*ChangeWordStr;							// �u������ ������v
	STRBUF			*BoxMessage;							// �u�|�P�����́����ɓ]�����ꂽ�v
	STRBUF			*GroupString;							// �u�O���[�v�v������

	CLACT_SET_PTR 			clactSet;								// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;								// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// ���\�[�X�I�u�W�F�e�[�u��
	CLACT_HEADER			clActHeader_m;							// �Z���A�N�^�[�w�b�_�[
	CLACT_HEADER			clActHeader_s;							// �Z���A�N�^�[�w�b�_�[
	CLACT_WORK_PTR			clActWork[NAMEIN_OAM_NUM];				// �Z���A�N�^�[���[�N�|�C���^�z��
	CLACT_WORK_PTR			NameLineActWork[NAMELINE_OAM_NUM];		// ���͌��ʕ\��������̉��A���_�[���C��
	CLACT_WORK_PTR			NameIconActWork[2];						// ���͉�ʐ����A�C�R���i���@�E�p�\�R���^���ʁ��E���j
	TCB_PTR					FuncButtonTask[FUNCBUTTON_NUM];

	GF_BGL_BMPWIN 			NameInWin[BMP_NAMEIN_MAX];				// ���O���͗pBMP�E�C���h�E
	int						msg_index;


	int						seq;									// ���݂̕������͏�ԁi����OK/�A�j�����j�Ȃ�
	int						mode;									// ���ݍőO�ʂ̕����p�l��

	int						front;									// ��O�ɗ��Ă���BG��
	VecFx32					panelpos[2];							// �ړ�����2��BG�ʗp���W���[�N(�Œ菭���ł͎g���Ă��Ȃ��j

	int						word;									

	int						old_subbutton;							// �O��̉���ʃ{�^�����
	int						subbutton_mode;
	int						subbutton_work;

	int						funcbutton[FUNCBUTTON_NUM];				// �{�^��������ԃt���O

	void*					BgCharaBuf;
	NNSG2dCharacterData*	BgCharaDat;

	void*					PokeIconBuf;							// �|�P�����A�C�R���f�[�^
	NNSG2dCharacterData*	PokeIconCharaDat;						

	void*					PokeIconPalBuf;
	NNSG2dPaletteData*		PokeIconPalDat;
	
	u8						ObjTransWork[32*4*2];					//

	void					*dsicon_task;							//

	BOOL					TP_decide;

	int						wait;
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static PROC_RESULT NameInProc_Init( PROC * proc, int * seq );
static PROC_RESULT NameInProc_Main( PROC * proc, int * seq );
static PROC_RESULT NameInProc_End( PROC * proc, int * seq );

static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini, GF_BGL_BMPWIN *win );
static void BgGraphicSet( NAMEIN_WORK * wk );
static void PanelFunc(GF_BGL_INI *bgl, GF_BGL_BMPWIN *win, int *seq, int mode, int *front, VecFx32 panelpos[], CLACT_WORK_PTR *clActWork, void *dakuten_Character);
static void InitWork(NAMEIN_WORK *wk, PROC * proc);
static void FrontBackBG_RegSet(GF_BGL_INI *bgl, int front, VecFx32 panelpos[]);
static void SetPanelFirstPos(VecFx32 panelpos[], int front);
static void InitCellActor(NAMEIN_WORK *wk);
static void SetCellActor(NAMEIN_WORK *wk);
static void char_pltt_manager_init(void);
static void BmpMessageSet(NAMEIN_WORK *wk, PROC* proc);
static void DebugOBJPOSGet(NAMEIN_WORK *wk);
static void ControlCursor(NAMEIN_WORK *wk);
static void CursorColTrans(u16 *CursorCol);
static void TouchFunc(NAMEIN_WORK *wk);
static void NameinWordPanelPrint(GF_BGL_BMPWIN *win, const u16 *str, int x,int y, int space, int sw, GF_PRINTCOLOR color, u8 *datkuten_Character);
static void ChangeSubPanelButtonWord(GF_BGL_BMPWIN *win, const u16 *tbl, u8 *TransWork, STRBUF *ChangeWordStr);
static void MakeWordMap(u16 map[][INPUT_WORD_W], const int no);
static void SubPanelButton_CharaChange(GF_BGL_BMPWIN *win, STRCODE *str,int pos,  u16 *words, u8 *TransWork, STRBUF *ChangeWordStr);
static int  DecideMainButton(NAMEIN_WORK *wk,u16 code, int pad);
static int  ConvertWord(int start, int num, int flag, int target, u16*str, int pos);
static int  RotateConvertWord(int start, int num, u16 *str, int pos);
static void InputResultUnderLineMove(CLACT_WORK_PTR *lineact,int pos, int max);
static void SetNameInWorkParameter(NAMEIN_WORK *wk, NAMEIN_PARAM *param);
static void WordPanelSetUp(GF_BGL_BMPWIN *win,u16 bgchara, int frame, GF_PRINTCOLOR color, u8 *dakuten_Character);
static void CursorAppearUpDate(NAMEIN_WORK *wk, int arrow);
static void FuncButtonAnimation(int funcbutton[], CLACT_WORK_PTR *ButtonAct, int frame);
static void FuncButtonTaskFunc( TCB_PTR tcb, void *work );
static void QuakeFrameTaskFunc( TCB_PTR tcb, void *work );
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, NNSG2dPaletteData* pal, int pokeno, int form );
static void Namein_LCDOnOff( int flag);
static void SetBoxMessage( NAMEIN_WORK *wk, PROC * proc );
static void NameinIconAdd(NAMEIN_WORK *wk, CLACT_ADD *add );
static void InputCancelFunc( NAMEIN_WORK *wk, NAMEIN_PARAM *param );
static void PrintTalkInfoStr( GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title );
static void CursorAnimationControl( NAMEIN_WORK *wk );
static int  NameInputMainMode( NAMEIN_WORK *wk, int seq );
static int SpaceCheck( STRCODE *str );


static void *GF_STR_PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg,u8 fnt_index, GF_PRINTCOLOR col);

#ifdef DEBUG_OAM_POSPRINT

static testclact_set( void );

#endif
//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �v���Z�X��`�f�[�^
const PROC_DATA NameInProcData = {
	NameInProc_Init,
	NameInProc_Main,
	NameInProc_End,
	NO_OVERLAY_ID,
};


static NAMEIN_WORK *debug_namein;
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
static PROC_RESULT NameInProc_Init( PROC * proc, int * seq )
{
	NAMEIN_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
		sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_NAMEIN, 0x20000+0x8000 );

		wk = PROC_AllocWork( proc, sizeof(NAMEIN_WORK), HEAPID_NAMEIN );
		memset( wk, 0, sizeof(NAMEIN_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_NAMEIN );
		
		// ������}�l�[�W���[����
		wk->WordSet          = WORDSET_Create( HEAPID_NAMEIN );
		wk->MsgManager       = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_namein_dat, HEAPID_NAMEIN );
		wk->MsgDefaultName   = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_opening_name_dat, HEAPID_NAMEIN );
		wk->FightMsgManager  = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_fightmsg_dp_dat, HEAPID_NAMEIN );

		sys_KeyRepeatSpeedSet( 4, 8 );

		VramBankSet();
		
		// BGL���W�X�^�ݒ�
		BgInit( wk->bgl );					

		// �P�x�ύX�Z�b�g

//		ChangeBrightnessRequest(
//			8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );

		
		// ������ۑ�
		SetNameInWorkParameter(wk, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

		//BG�O���t�B�b�N�Z�b�g
		BgGraphicSet( wk );

//		InitTPSystem();						// �^�b�`�p�l���V�X�e��������
//		InitTPNoBuff(4);
  
		// �{�^���p�t�H���g��ǂݍ���
		FontProc_LoadFont( FONT_BUTTON, HEAPID_NAMEIN );
  	
 
		// VBlank�֐��Z�b�g
		sys_VBlankFuncChange( VBlankFunc, NULL );	
  
		// ���[�N������
		InitWork(wk,proc);

		// �V�X�e���t�H���g�풓
		FontProc_LoadBitData(FONT_SYSTEM,HEAPID_NAMEIN);

		// OBJ�L�����A�p���b�g�}�l�[�W���[������
		char_pltt_manager_init();

		// CellActor�V�X�e��������
		InitCellActor(wk);
		
		// CellActro�\���o�^
		SetCellActor(wk);

		// BMPWIN�o�^�E�`��
		BmpMessageSet(wk,proc);


		// ���{�^��OBJ�t�H���g�]��
		SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
									wk->inputword,
									wk->nowinput,
									wk->subtouchword,
									wk->ObjTransWork,
									wk->ChangeWordStr);

		// �T�E���h�f�[�^���[�h(���O����)(BGM���p��)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
		Namein_LCDOnOff( VISIBLE_ON );

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
		{
			//��ʔ��]	add by tetsu
			sys.disp3DSW = DISP_3D_TO_SUB;
			GF_Disp_DispSelect();
		}
#endif
		(*seq)++;
		break;
	case 1:
		wk = PROC_GetWork( proc );
		if(wk->inputmode==NAMEIN_POKEMON){
			// �|�P�����A�C�R���f�[�^��VRAM�ɓ]��
			TransPokeIconCharaPal(wk->PokeIconCharaDat, wk->PokeIconPalDat, wk->inputinfo, wk->inputform );
		}
		debug_namein = wk;

		wk->dsicon_task = MSG_DsIconFlashAdd( NULL, MSG_DSI_SUBDISP, TALK_MSG_WIN_PAL, HEAPID_NAMEIN );
		
		(*seq) = 0;
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * �|�P�����A�C�R����]������i�|�P�����̖��O�̎������j
 *
 * @param   chara	�L�����N�^�[�t�@�C���A�h���X
 * @param   pal		�p���b�g�t�@�C���A�h���X
 * @param   pokeno	�|�P�����̊J��NO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, NNSG2dPaletteData* pal, int pokeno, int form )
{
	u8 *pokepal;

	// �L�����N�^�[�]��
	GX_LoadOBJ(chara->pRawData, POKEICON_VRAM_OFFSET*0x20, 0x20*4*4);

	// �p���b�g�]��
	pokepal = (u8*)pal->pRawData;
	GX_LoadOBJPltt((void*)(pokepal + PokeIconPalNumGet(pokeno, form, 0)*0x20), 
					POKEICON_PAL_OFFSET*0x20, 0x20);


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

static PROC_RESULT NameInProc_Main( PROC * proc, int * seq )
{
	NAMEIN_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if( WIPE_SYS_EndCheck() ){
			*seq     = SEQ_WAIT;
			wk->wait = 0;
		}
		break;

	case SEQ_WAIT:
		wk->wait++;
		// �J�[�\���A�j���[�V��������
		CursorAnimationControl( wk );
		// �@�\�{�^���̃A�j������
		FuncButtonAnimation(wk->funcbutton, wk->clActWork, wk->mode);
		if(wk->wait > TOUCH_START_WAIT){
			*seq     = SEQ_MAIN;
			wk->wait = 0;
		}
		break;

	case SEQ_MAIN:
		// �J�[�\���ړ�

		switch(wk->seq){
		case NAMEIN_MODE:

			// �ʏ���͐���
			if(!wk->Cursor.decide){
				// ���̓A�j�����͓������Ȃ�
				*seq = NameInputMainMode(wk, *seq);
			}

			// �J�[�\���A�j���[�V��������
			CursorAnimationControl( wk );

			break;
		case NAMEIN_MODE_BOXMSG:

			// �|�P�����̓{�b�N�X�Ɋi�[���ꂽ�惁�b�Z�[�W
			SetBoxMessage( wk, proc );
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_TALK_WIN], 0x0f0f );
			BmpTalkWinWrite( &wk->NameInWin[BMP_TALK_WIN], WINDOW_TRANS_ON, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL );
			wk->msg_index = GF_STR_PrintSimple( &wk->NameInWin[BMP_TALK_WIN], FONT_TALK, wk->BoxMessage, 0, 0, 1, NULL );
			GF_BGL_BmpWinOn( &wk->NameInWin[BMP_TALK_WIN] );

			wk->seq = NAMEIN_MODE_BOXMSG_END;
			break;
		case NAMEIN_MODE_BOXMSG_END:
			// �{�b�N�X�s�����b�Z�[�W�\���҂�
			if(GF_MSG_PrintEndCheck( wk->msg_index )==0){
				Snd_SePlay( NAMEIN_SE_END );
				wk->funcbutton[6]++;
				wk->wait = 0 ;
				wk->seq = NAMEIN_MODE_BOXMSG_END_WAIT;
			}
			break;
		case NAMEIN_MODE_BOXMSG_END_WAIT:
			// �{�b�N�X���b�Z�[�W�\���҂�
			wk->wait++;
			if(wk->wait>30){
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
				*seq = SEQ_OUT;
			}
			break;
		}

		// ���N�G�X�g���ɕ����p�l�������ւ���
		PanelFunc(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG0], &wk->seq, wk->mode, &wk->front, wk->panelpos, wk->clActWork, wk->BgCharaDat->pRawData);

		// �@�\�{�^���̃A�j������
		FuncButtonAnimation(wk->funcbutton, wk->clActWork, wk->mode);

		CursorColTrans(&wk->CursorPal);

		break;

	case SEQ_OUT:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	CLACT_Draw( wk->clactSet );									// �Z���A�N�^�[�풓�֐�

	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * @brief   ���O���͒ʏ펞���C������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int NameInputMainMode( NAMEIN_WORK *wk, int seq )
{
			ControlCursor(wk);		//		DebugOBJPOSGet(wk);
			//TouchFunc(wk);
			if( sys.trg & PAD_BUTTON_SELECT){
				// �t�����h�R�[�h���͂̎��̓p�l���؂�ւ��͂ł��Ȃ�
				if(wk->inputmode!=NAMEIN_FRIENDCODE){
					// �p�l���؂�ւ�
					wk->seq = NAMEIN_MODE_REQ;
					wk->mode++;
					if(wk->mode>NAMEIN_MODE_KIGOU){
						wk->mode=NAMEIN_MODE_HIRA;
					}
					wk->funcbutton[wk->mode]++;
					MakeWordMap(wk->wordmap, wk->mode);		// �������̓}�b�v�����ւ�
					Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
				}
				wk->funcbutton[wk->mode]++;
				MakeWordMap(wk->wordmap, wk->mode);		// �������̓}�b�v�����ւ�
				Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
			}else if( sys.trg & PAD_BUTTON_A){
				// ��������
				seq = DecideMainButton(wk,wk->wordmap[wk->Cursor.y][wk->Cursor.x], 1);

				// ���͌�J�[�\����\������
				wk->Cursor.on = 1;
			}else if( wk->TP_decide == TRUE ){
				seq = DecideMainButton(wk,wk->wordmap[wk->Cursor.y][wk->Cursor.x], 0);

				// ���͌�J�[�\�����n�e�e����
				wk->Cursor.on = 0;
#else
			}else if( sys.trg & PAD_BUTTON_A){
#endif
			}else if( sys.trg & PAD_BUTTON_B ){
				// ��������
				seq = DecideMainButton(wk,NAMEIN_MODORU,1);

			}
			else if( sys.trg & PAD_BUTTON_R){
				seq = DecideMainButton( wk, NAMEIN_KOMOJI, 1 );
			}

	return seq;
}

#define DEFAULT_NAME_MAX		18

// �_�C���E�p�[���ŕς��
#if (PM_VERSION==VERSION_DIAMOND)

#define MALE_NAME_START			( msg_opening_name_01 )
#define FEMALE_NAME_START		( msg_opening_name_19 )
#define RIVAL_NAME_NO			( msg_opening_rival_dia_01 )

#else

#define MALE_NAME_START			( msg_opening_name_45 )
#define FEMALE_NAME_START		( msg_opening_name_63 )
#define RIVAL_NAME_NO			( msg_opening_rival_pearl_01 )

#endif

//------------------------------------------------------------------
/**
 * @brief   ���͖����ŏI�����鎞�ɃL�����Z�������ɂ��邩
 *			�f�t�H���g�l�[�������邩
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InputCancelFunc( NAMEIN_WORK *wk, NAMEIN_PARAM *param )
{
	// �����̖��O���͂̎��̓L�����Z���͖���
	if(wk->inputmode==NAMEIN_MYNAME){
		STRBUF *DefaultName;
		if(wk->inputinfo==PM_MALE){
			DefaultName = MSGMAN_AllocString( wk->MsgDefaultName, MALE_NAME_START+gf_rand()%DEFAULT_NAME_MAX );
		}else if(wk->inputinfo==PM_FEMALE){
			DefaultName = MSGMAN_AllocString( wk->MsgDefaultName, FEMALE_NAME_START+gf_rand()%DEFAULT_NAME_MAX );
		}
		STRBUF_Copy(param->strbuf, DefaultName);
		STRBUF_Delete(DefaultName);
#ifdef USE_PARAM_STR
		STRBUF_GetStringCode( param->strbuf, param->str, 10 );
#endif

	// ���C�o�����̎��̓L�����Z���ł͂Ȃ��f�t�H���g�l�[��������
	}else if(wk->inputmode==NAMEIN_RIVALNAME){
		STRBUF *rivalName;
		rivalName = MSGMAN_AllocString( wk->MsgDefaultName, RIVAL_NAME_NO );
		STRBUF_Copy(param->strbuf, rivalName);
		STRBUF_Delete(rivalName);
#ifdef USE_PARAM_STR
		STRBUF_GetStringCode( param->strbuf, param->str, 10 );
#endif

	}else{
		OS_Printf("���͂̓L�����Z��\n");
		
		// �L�����Z��
		param->cancel = 1;
	}

}

//------------------------------------------------------------------
/**
 * @brief   ���͕����񂪑S�ăX�y�[�X�Ȃ�L�����Z�������ɂ���`�F�b�N
 *
 * @param   str		
 *
 * @retval  int		�S�ăX�y�[�X��������1,�������0
 */
//------------------------------------------------------------------
static int SpaceCheck( STRCODE *str )
{
	int flag=1;
	int i;
	for(i=0;;i++){
		if(str[i]==EOM_){
			break;
		}
		if(str[i]!=spc_){
			flag = 0;
		}
	}
	
	return flag;
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
static PROC_RESULT NameInProc_End( PROC * proc, int * seq )
{
	NAMEIN_WORK  *wk    = PROC_GetWork( proc );
	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);
	int i;

	// ���͕�����̍Ō��EOM�����Ă���
	wk->inputword[wk->nowinput] = EOM_;

	// �|�P�������O���͂̎��̃L�����Z������̂��߂̏���
	if(wk->inputmode==NAMEIN_POKEMON){
		// wk->paramstr�Ƀf�t�H���g�|�P������������邩�H
		STRCODE comparestr[MONS_NAME_SIZE+EOM_SIZE];
		POKEMON_PARAM *pp;

		OS_Printf("paramstr %02x, %02x, %02x, %02x, %02x, %02x,\n",
			wk->paramstr[0],wk->paramstr[1],wk->paramstr[2],wk->paramstr[3],wk->paramstr[4],wk->paramstr[5]
		);

		pp = PokemonParam_AllocWork(HEAPID_NAMEIN);
		PokeParaSet(pp,wk->inputinfo,5,10,10,10,10,10);
//		PokeParaGet(pp,ID_PARA_nickname, comparestr);
		sys_FreeMemoryEz(pp);

	}

	// �L�����Z������Ȃ����H
	if(wk->nowinput==0 || (PM_strcmp( wk->inputword, wk->paramstr)==0) || SpaceCheck(wk->inputword)){

		InputCancelFunc( wk, param );

	}else{
		// ���͕�������������[�N�ɔ��f
		PM_strcpy(wk->paramstr,wk->inputword);
#ifdef USE_PARAM_STR
		PM_strcpy(param->str,wk->inputword);
#endif

		STRBUF_SetStringCode(param->strbuf,wk->inputword);
	}
	
	STRBUF_Delete(wk->GroupString);

	// �@�\�{�^���ʒu����^�X�N���
	for(i=0;i<FUNCBUTTON_NUM;i++){
		PMDS_taskDel(wk->FuncButtonTask[i]);
	}
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

	// BMPWIN�p�L�����f�[�^���
	sys_FreeMemory( HEAPID_NAMEIN, wk->BgCharaBuf );

	// �|�P�����A�C�R�����
	if(wk->inputmode==NAMEIN_POKEMON){
		sys_FreeMemory( HEAPID_NAMEIN,wk->PokeIconBuf );
		sys_FreeMemory( HEAPID_NAMEIN,wk->PokeIconPalBuf );	
	}

	//��b�E�C���h�E�p�o�b�t�@���
	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_S);

	DeleteCharManager();
	DeletePlttManager();

	// BMP�E�B���h�E�J��
	BgExit(wk->bgl,wk->NameInWin);
	// BGL�폜

	// �풓�V�X�e���t�H���g���
	FontProc_UnloadBitData(FONT_SYSTEM);


	GX_SetVisibleWnd( GX_WNDMASK_NONE );	//�n�[�h�E�F�A�E�C���h�E����

	// �{�^���p�t�H���g���
	FontProc_UnloadFont( FONT_BUTTON );

//	StopTP();							// �^�b�`�p�l���I��

	//�|�P�����]��������o�b�t�@���m�ۂ��Ă���������
	if(wk->BoxMessage){
		STRBUF_Delete(wk->BoxMessage);
	}

	// �u�`�̂Ȃ܂��́H�v���
	STRBUF_Delete(wk->TitleStr);
	//�u��������������v���
	STRBUF_Delete(wk->ChangeWordStr);

	// ���b�Z�[�W�}�l�[�W���[�E���[�h�Z�b�g�}�l�[�W���[���
	MSGMAN_Delete( wk->FightMsgManager );
	MSGMAN_Delete( wk->MsgDefaultName );
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	PROC_FreeWork( proc );				// ���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_NAMEIN );

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
	{
		//��ʔ��]	add by tetsu
		sys.disp3DSW = DISP_3D_TO_MAIN;
		GF_Disp_DispSelect();
	}
#endif
	return PROC_RES_FINISH;
}

//==============================================================================
/**
 * ���O���͂ɓn���p�����[�^���m�ۂ���i���O���͂̌��ʂ�����̂ŁA�Ăяo������HEAPID���K�v�j
 *
 * @param   HeapId		�Ăяo������HEAPID
 * @param   mode		���O���̓��[�h(NAMEIN_MYNAME,NAMEIN_BOX,NAMEIN_POKEMON)
 * @param   info		NAMEIN_MYNAME�̎���0=�j1=��, NAMEIN_POKEMON�̎��͊J��NO
 * @param   wordmax		���͕����ő吔�̎w��
 *
 * @retval  NAMEIN_PARAM *		�m�ۂ��ꂽ���O���̓p�����[�^�̃|�C���^
 */
//==============================================================================
NAMEIN_PARAM *NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax, CONFIG *config)
{
	NAMEIN_PARAM *param;
	
	
	param = (NAMEIN_PARAM*)sys_AllocMemory(HeapId, sizeof(NAMEIN_PARAM));

	param->mode    = mode;		// ���̓��[�h�i�����̖��O�A�|�P�����A�{�b�N�X�j
	param->info    = info;		// �i�j�E���A�|�P�����̊J��NO)
	param->wordmax = wordmax;	// ���͕����ő吔
	param->cancel  = 0;			// �L�����Z���t���O
#ifdef USE_PARAM_STR
	param->str[0]  = EOM_;
#endif

	// ������ő咷�{EOM�ŕ�����o�b�t�@���쐬
	param->strbuf = STRBUF_Create( wordmax+1, HeapId );


	// �|�P�����ߊl�̎��Ƀ{�b�N�X�]���������������ɂ͎g�p����郁���o
	param->get_msg_id  = 0;		// �|�P�����ߊl���b�Z�[�WID
	param->boxdata     = NULL;	// �|�P�����{�b�N�X�f�[�^�ւ̃|�C���^
	param->sex		   = 0;
	param->config      = config;
	param->form		   = 0;

	return param;
}

//==============================================================================
/**
 * ���O���̓p�����[�^�̉���i���O���͌�Ƀ��[�U�[�����O�擾�����������Ă��炤�j
 *
 * @param   param		
 *
 * @retval  none		
 */
//==============================================================================
void NameIn_ParamDelete(NAMEIN_PARAM *param)
{
	GF_ASSERT((param->strbuf)!=NULL);
	GF_ASSERT((param)!=NULL);
	
	STRBUF_Delete(param->strbuf);
	sys_FreeMemoryEz(param);
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
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//==============================================================================
/**
 * �O�����疼�O���͏������p�����[�^�[�����炤
 *
 * @param   wk			���O���̓��[�N�̃|�C���^
 * @param   mode		���̓��[�h�inamein.h��enum�Q��
 * @param   info		���͏��i�j���E�|�P�����m�n�Ȃ�
 * @param   wordmax		���͕����ő吔
 *
 * @retval  none		
 */
//==============================================================================
static void SetNameInWorkParameter(NAMEIN_WORK *wk, NAMEIN_PARAM *param)
{
	wk->inputmode = param->mode;
	wk->inputinfo = param->info;
	wk->inputform = param->form;
	wk->inputmax  = param->wordmax;
	wk->inputsex  = param->sex;
	wk->config    = param->config;
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

	// ���ʕ�����0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// ���ʕ�����1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// �w�i
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	// ��b�E�C���h�EBG
//	{	
//		GF_BGL_BGCNT_HEADER TextBgCntDat = {
//			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
//			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
//			0, 0, 0, FALSE
//		};
//		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
//	}




	// BUTTON (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// BG (CHAR)
//	{	
//		GF_BGL_BGCNT_HEADER TextBgCntDat = {
//			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
//			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
//			1, 0, 0, FALSE
//		};
//		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
//	}

	Namein_LCDOnOff( VISIBLE_OFF );

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_NAMEIN );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_NAMEIN );

	// ���ʂ̃n�[�h�E�F�A�E�C���h�E0���n�m��
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_OBJ,1);
	G2_SetWndOutsidePlane(   GX_WND_PLANEMASK_BG0 
	                       | GX_WND_PLANEMASK_BG1 
	                       | GX_WND_PLANEMASK_BG2 
	                       | GX_WND_PLANEMASK_BG3 
	                       | GX_WND_PLANEMASK_OBJ,1);
	G2_SetWnd0Position(0, 0, 255, 64);


}


//------------------------------------------------------------------
/**
 * $brief   ���O���͉�ʂ̕\���n�m�E�n�e�e
 *
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Namein_LCDOnOff( int flag)
{
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG0, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG2, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG3, 0);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_OBJ, flag);


    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_BG0,flag);
    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_BG1,0);
    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_OBJ,0);
	
}

//------------------------------------------------------------------
/**
 * ���O���̓��[�N������
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(NAMEIN_WORK *wk, PROC * proc)
{
	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);
	wk->seq = NAMEIN_MODE;

	SetPanelFirstPos(wk->panelpos, 0);

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+wk->front,       GF_BGL_SCROLL_X_SET, wk->panelpos[wk->front].x );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+wk->front,       GF_BGL_SCROLL_Y_SET, wk->panelpos[wk->front].y );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+((wk->front)^1), GF_BGL_SCROLL_X_SET, wk->panelpos[((wk->front)^1)].x );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+((wk->front)^1), GF_BGL_SCROLL_Y_SET, wk->panelpos[((wk->front)^1)].y );

#ifdef PM_DEBUG
	{
		int i;
		for(i=0;i<9;i++){
			wk->framenum[i][0] = main_button_info[i][0];
			wk->framenum[i][1] = main_button_info[i][1];
		}
	}
#endif

	wk->paramstr[0] = EOM_;
	// �p�����[�^�[�Ŗ���Ă���STRBUF�̓W�J
	if(param->strbuf){
		STRBUF_GetStringCode(param->strbuf, wk->paramstr, INPUT_WORD_MAX);
	}

	MI_CpuFill16( wk->inputword, spc_,  INPUT_WORD_MAX*2 );


	// �u�`�̂Ȃ܂��́H�v������W�J
	if(wk->inputmode==NAMEIN_POKEMON){
		POKEMON_PARAM *pp;

		pp = PokemonParam_AllocWork(HEAPID_NAMEIN);
		PokeParaSet(pp,wk->inputinfo,5,10,10,10,10,10);
		WORDSET_RegisterPokeMonsName( wk->WordSet, 0, PPPPointerGet(pp) );
		sys_FreeMemoryEz(pp);
	}

	// �I�����Ƀ��b�Z�[�W�\�����s�����i�|�P�����ߊl���j
	if(param->get_msg_id!=0){
		wk->endmode       = 1;
		OS_Printf("BOXDATA Addr = %08x\n",param->boxdata);
	}

	// �u�`�̂Ȃ܂��́H�v������擾(�|�P�����̖��O�������œW�J�����)
	wk->TitleStr      = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, 
														NameinTitleStrTable[wk->inputmode], HEAPID_NAMEIN );
	
	// ��������������
	wk->ChangeWordStr = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, 
														NAMEIN_MSG_CHANGEWORD, HEAPID_NAMEIN );


	// �u�O���[�v�v
	wk->GroupString   = MSGMAN_AllocString( wk->MsgManager, NAMEIN_MSG_TITLEINFO7 );

	// NAMEIN_PARAM.str�Ƀf�t�H���g����������Ă���΃J�[�\���̈ʒu��0�ł͂Ȃ��Ȃ�
	wk->nowinput       = PM_strlen( wk->paramstr ); 
	wk->Cursor.x       = 0;	// �����ʒu���u���v�̈ʒu��
	wk->Cursor.y       = 1;	
	wk->Cursor.oldx    = -1;
	wk->Cursor.oldy    = -1;
	wk->Cursor.on      = 0;	
	wk->Cursor.decide  = 0;	
	wk->old_subbutton  = RECT_HIT_NONE;							// �O��̉���ʃ{�^�����
	wk->subbutton_mode = 0;
	wk->subbutton_work = 0;
	wk->inputword[wk->inputmax] = EOM_;


	// �@�\�{�^��������ԃ��[�N������
	{
		int i;
		for(i=0;i<FUNCBUTTON_NUM;i++){
			wk->funcbutton[i]	= 0;
		}

		// �������̓{�^���̏����ݒ�
		switch(wk->inputmode){
		case NAMEIN_POKEMON:
			wk->funcbutton[NAMEIN_MODE_KANA]    = 1;
			break;
		case NAMEIN_FRIENDCODE:
			wk->funcbutton[NAMEIN_MODE_KIGOU] = 1;
			break;
		default:
			wk->funcbutton[NAMEIN_MODE_HIRA]    = 1;
			break;
		}
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   �|�P�����ߊl�Ń{�b�N�X�ɍs�����b�Z�[�W���o�����߂̏���
 *
 * @param   wk		
 * @param   proc		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetBoxMessage( NAMEIN_WORK *wk, PROC * proc )
{
	STRBUF *name=NULL;

	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);


	// �퓬���烁�b�Z�[�WID�����Ă���Ȃ��
	if(param->get_msg_id!=0){
		int setbox,newbox;

		name = STRBUF_Create(200,HEAPID_NAMEIN);

		// �����̓{�b�N�X�u�H�H�H�v�ɓ]������܂���
		wk->BoxMessage = NULL;

		setbox = BOXDAT_GetCureentTrayNumber(param->boxdata);
		newbox = BOXDAT_GetEmptyTrayNumber(param->boxdata);
		
		// �]����{�b�N�X���ݒ�
		WORDSET_RegisterBoxTrayName( wk->WordSet, 1, param->boxdata, setbox );


		// ���ݓ]����ƁA���ۂ̓]���悪�Ⴄ�ꍇ�͐V�����]���於���擾����
		if(setbox!=newbox){
			WORDSET_RegisterBoxTrayName( wk->WordSet, 2, param->boxdata, newbox );
			param->get_msg_id+=2;
		}else{
			WORDSET_RegisterBoxTrayName( wk->WordSet, 2, param->boxdata, setbox );
		}

		// ���͕�����𖼑O�o�b�t�@�ɔ��f
		if(wk->nowinput==0 || SpaceCheck(wk->inputword)){
			// ���O����͂��Ă��Ȃ��̂ŁA�f�t�H���g�l�[��������
			POKEMON_PARAM	*poke = PokemonParam_AllocWork(HEAPID_NAMEIN);
			PokeParaSet( poke, wk->inputinfo,1,0,0,0,0,0);
			WORDSET_RegisterPokeMonsName( wk->WordSet,  0, PPPPointerGet(poke) );
			sys_FreeMemoryEz(poke);
		}else{
			// ���O����͂��Ă�����
			wk->inputword[wk->nowinput] = EOM_;
			STRBUF_SetStringCode( name, wk->inputword );
			WORDSET_RegisterWord( wk->WordSet, 0, name, 0, 0, 0 );
		}
		wk->BoxMessage    = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->FightMsgManager, param->get_msg_id, HEAPID_NAMEIN );
		wk->endmode       = 1;

		STRBUF_Delete(name);

	}
	
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
static void BgExit( GF_BGL_INI * ini, GF_BGL_BMPWIN *win )
{
	int i;
//	GF_Disp_GX_VisibleControl(
//		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
//		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
//	GF_Disp_GXS_VisibleControl(
//		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	for(i=0;i<BMP_NAMEIN_MAX;i++){
		GF_BGL_BmpWinDel( &win[i] );
	}

//	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
//	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_NAMEIN, ini );
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
static void BgGraphicSet( NAMEIN_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// �㉺��ʂa�f�p���b�g�]��
	ArcUtil_PalSet(    ARC_NAMEIN_GRA,  NARC_namein_name_bg_NCLR, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_NAMEIN);
//	ArcUtil_PalSet(    ARC_NAMEIN_GRA,  NARC_namein_name_bg_NCLR, PALTYPE_SUB_BG,  0, 16*3*2,  HEAPID_NAMEIN);
	ArcUtil_PalSet(    ARC_POKETCH_IMG, NARC_poketch_before_nclr, PALTYPE_SUB_BG, 0, 16*2,  HEAPID_NAMEIN);
	
	// �o�b�N�h���b�v�p���b�g���O�N���A
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

	// ����BG2�L�����]��
	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NCGR, bgl, GF_BGL_FRAME2_M, 0, NAMEIN_BG2GRAPHIC_SIZE, 1, HEAPID_NAMEIN);

	// ����BG2�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NSCR, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_NAMEIN);


	// ����BG1�L�����]��
	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NCGR, bgl, GF_BGL_FRAME1_M, 0, 32*8*0x20, 1, HEAPID_NAMEIN);
	// ����BG1�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR, bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
	// ����BG0�X�N���[���]��
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_screen2_lz_NSCR, bgl, GF_BGL_FRAME0_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
	
	// ��b�E�C���h�E�L�����f�[�^�]��
//	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME3_M, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL, 0, HEAPID_NAMEIN );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, TALK_MSG_WIN_PAL*32, HEAPID_NAMEIN );

	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME0_S, NAMEIN_TALKWIN_CGX_OFFSET, 
						FLD_MESFRAME_PAL, CONFIG_GetWindowType(wk->config), HEAPID_NAMEIN );
	TalkFontPaletteLoad( PALTYPE_SUB_BG, TALK_MSG_WIN_PAL*32, HEAPID_NAMEIN );

	// �����BG0�L�����]��
	// �����BG0�X�N���[���]��
//	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NCGR, bgl, GF_BGL_FRAME0_S, 0, 32*2*0x20, 1, HEAPID_NAMEIN);
//	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);

//	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr, bgl, GF_BGL_FRAME0_S, 0, 0, 1, HEAPID_NAMEIN);
//	ArcUtil_ScrnSet(   ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr, bgl, GF_BGL_FRAME0_S, 0, 0, 1, HEAPID_NAMEIN);


	// BMPWIN�]���p�L�����p��(BgCharaBuf�͖��O���͏I�����ɉ������K�v����j
	wk->BgCharaBuf = ArcUtil_CharDataGet( ARC_NAMEIN_GRA, NARC_namein_name_bg_prog_lz_NCGR, 1, &wk->BgCharaDat, HEAPID_NAMEIN );

}


//** CharManager PlttManager�p **//
#define NAMEIN_CHAR_CONT_NUM				(20)
#define NAMEIN_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define NAMEIN_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define NAMEIN_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	�L�����N�^�}�l�[�W���[
//	�p���b�g�}�l�[�W���[�̏�����
//
//=====================================
void char_pltt_manager_init(void)
{
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			NAMEIN_CHAR_CONT_NUM,
			NAMEIN_CHAR_VRAMTRANS_MAIN_SIZE,
			NAMEIN_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_NAMEIN
		};
		InitCharManager(&cm);
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(NAMEIN_PLTT_CONT_NUM, HEAPID_NAMEIN);

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
static void InitCellActor(NAMEIN_WORK *wk)
{
	int i;
	
	
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			0, 128,		// ���C�����OAM�Ǘ��̈�
			0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
			0, 128,		// �T�u���OAM�Ǘ��̈�
			0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
			HEAPID_NAMEIN);
	
	
	
	// �Z���A�N�^�[������
	wk->clactSet = CLACT_U_SetEasyInit( 40+4, &wk->renddata, HEAPID_NAMEIN );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//���\�[�X�}�l�[�W���[�쐬
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_NAMEIN);
	}


	//---------���ʗp-------------------

	//chara�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NCGR, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_NAMEIN);

	//pal�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_NCLR, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAPID_NAMEIN);

	//cell�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NCER, 1, 0, CLACT_U_CELL_RES,HEAPID_NAMEIN);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NANR, 1, 0, CLACT_U_CELLANM_RES,HEAPID_NAMEIN);

	// �|�P�����̖��O���͂̏ꍇ�̓A�C�R���f�[�^��ǂݍ���
	if(wk->inputmode==NAMEIN_POKEMON){
		wk->PokeIconBuf    = ArcUtil_CharDataGet( ARC_POKEICON, 
								PokeIconCgxArcIndexGetByMonsNumber( wk->inputinfo, 0, wk->inputform ), 
								0, 
								&wk->PokeIconCharaDat, HEAPID_NAMEIN );
		DC_FlushRange(wk->PokeIconCharaDat,0x20*4*4);

		wk->PokeIconPalBuf = ArcUtil_PalDataGet( ARC_POKEICON, PokeIconPalArcIndexGet(), &wk->PokeIconPalDat, HEAPID_NAMEIN );
		DC_FlushRange(wk->PokeIconPalDat,0x20*4);	
	}
//	ArcUtil_PalDataGet( u32 fileIdx, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );

	//---------����ʗp-------------------



	//chara�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NCGR, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_NAMEIN);

	//pal�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_NAMEIN);

	//cell�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NCER, 1, 1, CLACT_U_CELL_RES,HEAPID_NAMEIN);

	//�����֐���anim�ǂݍ���
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NANR, 1, 1, CLACT_U_CELLANM_RES,HEAPID_NAMEIN);

	// ���\�[�X�}�l�[�W���[����]��

	// Chara�]��
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// �p���b�g�]��
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

typedef struct{
	CLACT_WORK_PTR parent;
	CLACT_WORK_PTR child;
	int dx;
	int id;
}FUNC_BUTTON_TASK_WORK;


//------------------------------------------------------------------
/**
 * �@�\�{�^�����p�l���t���[���Ɠ�������悤�ɂ��鏈��
 *
 * @param   tcb		
 * @param   work	
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void FuncButtonTaskFunc( TCB_PTR tcb, void *work )
{
	const VecFx32 *pVex;
	VecFx32 cVex;
	FUNC_BUTTON_TASK_WORK *wk = (FUNC_BUTTON_TASK_WORK*)work;

	pVex   = CLACT_GetMatrix(wk->parent);
	cVex.x = pVex->x + wk->dx;
	cVex.y = FX32_ONE*main_button_info[wk->id][1];
	cVex.z = 0;
	CLACT_SetMatrix(wk->child, &cVex);
}



//------------------------------------------------------------------
/**
 * �Z���A�N�^�[�o�^
 *
 * @param   wk			NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(NAMEIN_WORK *wk)
{
	int i;
	// �Z���A�N�^�[�w�b�_�쐬
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 1,
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

		add.mat.x		= FX32_CONST(32) ;
		add.mat.y		= FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���iMAIN����ASUB�����j
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_NAMEIN;

		//�Z���A�N�^�[�\���J�n

		// ���ʗp
		for(i=0;i<9;i++){
			add.mat.x = FX32_ONE*main_button_info[i][0];
			add.mat.y = FX32_ONE*main_button_info[i][1];
			wk->clActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[i],1);
			CLACT_AnmChg( wk->clActWork[i], main_button_info[i][2] );
			CLACT_DrawPriorityChg(wk->clActWork[i], main_button_info[i][3]);	// ���ꂼ��̃A�N�^�[�̃v���C�I���e�B�ݒ�
			
		}
		CLACT_SetDrawFlag( wk->clActWork[4], 0);
		CLACT_SetDrawFlag( wk->clActWork[8], 0);
		
		// �@�\�{�^�����p�l���o�[�ɓ������ē���������o�^
		for(i=0;i<7;i++){
			FUNC_BUTTON_TASK_WORK *twk;
			wk->FuncButtonTask[i] = PMDS_taskAdd(FuncButtonTaskFunc, 16, 5, HEAPID_NAMEIN);
			twk         = TCB_GetWork(wk->FuncButtonTask[i]);
			twk->parent = wk->clActWork[FUNCBUTTON_FRAME_ACTNO];
			twk->child  = wk->clActWork[i];
			twk->dx     = FX32_ONE*main_button_info[i][0];
			twk->id     = i;
		}

		//���O���͌��ʃA���_�[���C��
		for(i=0;i<wk->inputmax;i++){
			add.mat.x = FX32_ONE*(NAMELINE_POS_X+i*12);
			add.mat.y = FX32_ONE*NAMELINE_POS_Y;
			wk->NameLineActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->NameLineActWork[i],1);
			CLACT_AnmChg( wk->NameLineActWork[i], 43 );
		}
		// �P�����ڂ̃A���_�[���C�����㉺�ɓ�����
		InputResultUnderLineMove(wk->NameLineActWork, wk->nowinput, wk->inputmax);

		// ���O���̓A�C�R���\���o�^�i���[�h�ɂ���Đ؂�ւ���j
		NameinIconAdd( wk, &add );
		
#ifdef DEBUG_OAM_POSPRINT
		// �|�C���g�m�F�p
		for(i=0;i<4;i++){
			testclact[i] = CLACT_Add(&add);
			CLACT_AnmChg( testclact[i], 56+i );
		}

#endif


#ifndef NAMEIN_MAINUSE_TOUCHPANEL
		// ����ʗp
		for(i=0;i<2;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE*sub_button_info[i][0];
			add.mat.y = FX32_ONE*(sub_button_info[i][1]) + NAMEIN_SUB_ACTOR_DISTANCE;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->clActWork[10+i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[10+i],1);
			CLACT_AnmChg( wk->clActWork[10+i], sub_button_info[i][2] );
		}
#endif		
	}	
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ�ʂn�m
	
}

static void NameinIconAdd(NAMEIN_WORK *wk, CLACT_ADD *add )
{
		// ���͐����p�A�C�R���i���@�A���ʁA�p�\�R���A�|�P�����Ȃǁj
		add->mat.x = FX32_ONE*NAMEIN_MYICON_X;
		add->mat.y = FX32_ONE*NAMEIN_MYICON_Y;
		wk->NameIconActWork[0] = CLACT_Add(add);
		CLACT_SetAnmFlag(wk->NameIconActWork[0],1);
		switch(wk->inputmode){
		// ��l��
		case NAMEIN_MYNAME:
			if(wk->inputinfo==PM_MALE){
				CLACT_AnmChg( wk->NameIconActWork[0], 48 );	//�j������
			}else{
				CLACT_AnmChg( wk->NameIconActWork[0], 49 );	//�j������
			}
			break;
		// ���C�o��
		case NAMEIN_RIVALNAME:
			CLACT_AnmChg( wk->NameIconActWork[0], 51 );	
			break;
		// �Δ�
		case NAMEIN_STONE:
			CLACT_AnmChg( wk->NameIconActWork[0], 55 );	
			break;
		// �����_���O���[�v
		case NAMEIN_RANDOMGROUP:
			CLACT_AnmChg( wk->NameIconActWork[0], 54 );	
			break;
		// �Ƃ������R�[�h
		case NAMEIN_FRIENDCODE:
		case NAMEIN_FRIENDNAME:
			CLACT_AnmChg( wk->NameIconActWork[0], 53 );	
			break;
		// �p�\�R��
		case NAMEIN_BOX:
//			wk->NameIconActWork[0] = CLACT_Add(add);
			CLACT_AnmChg( wk->NameIconActWork[0], 47 );
			break;
		// �|�P�����A�C�R��
		case NAMEIN_POKEMON:
			CLACT_AnmChg( wk->NameIconActWork[0], 50 );
			// ���ʃA�C�R��(���ʖ����łȂ���΁j
			if(wk->inputsex!=PARA_UNK){
				add->mat.x = FX32_ONE*(NAMELINE_POS_X + wk->inputmax * 13);
				add->mat.y = FX32_ONE*NAMEIN_SEXICON_Y;
				wk->NameIconActWork[1] = CLACT_Add(add);
				if(wk->inputsex==PARA_MALE){
					CLACT_AnmChg( wk->NameIconActWork[1], 45 );	// ��
				}else{
					CLACT_AnmChg( wk->NameIconActWork[1], 46 );	// ��
				}
			}
			break;
		}

}


typedef struct{
	CLACT_WORK_PTR	frame;
	int				seq;
	int				dx;
	int				dy;
}QUAKE_FRAME_TASK_WORK;

static void QuakeFrameTaskFunc( TCB_PTR tcb, void *work )
{
	QUAKE_FRAME_TASK_WORK *wk = (QUAKE_FRAME_TASK_WORK *)work;
	VecFx32 tmp;
	tmp.y = wk->dy;
	tmp.z = 0;


	switch(wk->seq){
	case 0:
		tmp.x = wk->dx + 4*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		
		break;
	case 2:
		tmp.x = wk->dx - 3*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		break;
	case 4:
		tmp.x = wk->dx + 2*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		break;
	case 6:
		tmp.x = wk->dx;
		CLACT_SetMatrix(wk->frame, &tmp);
		PMDS_taskDel(tcb);
		break;
	}
	wk->seq++;
}

//------------------------------------------------------------------
/**
 * �����p�l�������N�G�X�g�����������ւ���
 *
 * @param   seq			�J�ڏ��
 * @param   mode		�������̓��[�h�i���ȁE�J�i�E�`�a�b�E�L���j
 * @param   front		�O�ɗ��Ă���a�f�ʂ�ۑ����Ă��郏�[�N
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PanelFunc(GF_BGL_INI *bgl,GF_BGL_BMPWIN *win, int *seq, int mode, int *frontBG, VecFx32 panelpos[], CLACT_WORK_PTR *clActWork,void *dakuten)
{
	int front = *frontBG;
	int back  = front^1;
	int i;
	switch(*seq){

	case NAMEIN_MODE_REQ:
		{
			u16 bgcol = wordpanel_bg_col[mode]|(wordpanel_bg_col[mode]<<4);
			// �V��������Ă��镶���p�l���ʂ�]��
			ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+mode, bgl, GF_BGL_FRAME0_M+front, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
			SetPanelFirstPos(panelpos, front);

			WordPanelSetUp(&win[front],bgcol, mode, GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[mode]*/),dakuten);

			(*seq)++;
		}
		break;
    	
	case NAMEIN_MODE_SET:
		// �Q����BG�ʂ̏������W���Z�b�g
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, HIDDENPANEL_POS_REGX );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_Y_SET, WORDPANEL_POS_REGY   );
		(*seq)++;
		break;
    	
	case NAMEIN_MODE_ANIM:
		// BG�ʂ��ړ�������B
		// ��ʒu�܂ł�����X�g�b�v�i�V�p�l���������̓t���[�����h���j
		
		
		panelpos[front].x-=WORDPANEL_IN_SPEED;
		if(panelpos[front].x < WORDPANEL_POS_REGX+10){		// �t���[����h�炷
			QUAKE_FRAME_TASK_WORK *qtfw;
			TCB_PTR qt;
			
			qt          = PMDS_taskAdd(QuakeFrameTaskFunc, 16, 0, HEAPID_NAMEIN);
			qtfw        = TCB_GetWork(qt);
			qtfw->frame = clActWork[7];
			qtfw->seq   = 0;
			qtfw->dx    = CLACT_GetMatrix(clActWork[7])->x;
			qtfw->dy    = CLACT_GetMatrix(clActWork[7])->y;

			panelpos[front].x=WORDPANEL_POS_REGX;
			(*seq)++;
		}
		// ��ʒu�܂ŗ�����X�g�b�v
		panelpos[back].y-=WORDPANEL_OUT_SPEED;
		if(panelpos[back].y < DOWNPANEL_POS_REGY){
			panelpos[back].y=DOWNPANEL_POS_REGY;
		}


		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, panelpos[front].x );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+back,  GF_BGL_SCROLL_Y_SET, panelpos[back].y );

		break;
    	
    case NAMEIN_MODE_ANIM_WAIT:
		// ��ʒu�܂ŗ�����X�g�b�v
		panelpos[back].y-=WORDPANEL_OUT_SPEED;
		if(panelpos[back].y < DOWNPANEL_POS_REGY){
			panelpos[back].y=DOWNPANEL_POS_REGY;
		}


		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, panelpos[front].x );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+back,  GF_BGL_SCROLL_Y_SET, panelpos[back].y );
		// ������BG�ʂ��ړ��I��������V�[�P���X�I��
		if(panelpos[front].x==WORDPANEL_POS_REGX && panelpos[back].y==DOWNPANEL_POS_REGY){
			(*seq)++;
			(*frontBG) ^=1;			//�a�f�ʂ̏㉺�����ւ���
			FrontBackBG_RegSet(bgl, *frontBG, panelpos);
			Snd_SePlay( SEQ_SE_DP_NAMEIN_01 );
		}
    	break;
	case NAMEIN_MODE:
		break;
    	

	}
}


//------------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�ɕ`����s��
 *
 * @param   bmp		
 * @param   inputmode		
 * @param   Title		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PrintTalkInfoStr( GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title )
{

	BmpTalkWinWrite( bmp, WINDOW_TRANS_ON, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL );

	/* wk->msg_index = */ GF_STR_PrintSimple( bmp, FONT_TALK, Title, 0, 0, MSG_ALLPUT, NULL );
	
	GF_BGL_BmpWinOn( bmp );
}
//------------------------------------------------------------------
/**
 * �u�`�̂Ȃ܂��́H�v�������`�悷��
 *
 * @param   bmp			������`��pBMPWIN�\����
 * @param   inputmode	���̓��[�h�iMYNAME,POKEMON,BOX)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PrintTitleInfoStr(GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title)
{
	int x = 16;

	int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, Title, 0 );

	// ����������͂O����`�悷�邪�A�Z��������͏����E�ɓ�����
	if(length>130){
		x = 0;
	}

	GF_BGL_BmpWinDataFill( bmp, 0x0101 );

	GF_STR_PrintColor(	bmp, FONT_SYSTEM, Title, x, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);

	GF_BGL_BmpWinOn( bmp );

}

//------------------------------------------------------------------
/**
 * BMPWIN�����i�����p�l���Ƀt�H���g�`��j
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpMessageSet(NAMEIN_WORK *wk, PROC* proc)
{
	// BG0�ʗp�i�����p�l��1�p�jBMP�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG0], GF_BGL_FRAME0_M,
						WORDPANEL_WIN_POSX, WORDPANEL_WIN_POSY, WORDPANEL_WIN_W, WORDPANEL_WIN_H, 1,  WORDPANEL0_WIN_OFFSET);

	// BG1�ʗp�i�����p�l��2�p�jBMP�E�C���h�E�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG1], GF_BGL_FRAME1_M,
						WORDPANEL_WIN_POSX, WORDPANEL_WIN_POSY, WORDPANEL_WIN_W, WORDPANEL_WIN_H, 1,  WORDPANEL1_WIN_OFFSET);

	//�ŏ��Ɍ����Ă���ʂȂ̂ŕ����p�l���`��Ɠ]�����s��
	// �����p�l���������E�o�^
	if(wk->inputmode==NAMEIN_POKEMON){
		ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+1, wk->bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
		wk->mode = NAMEIN_MODE_KANA;
		MakeWordMap(wk->wordmap,1);			// �J�^�J�i�����}�b�v�W�J
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0707, 1, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[1]*/),wk->BgCharaDat->pRawData);
	}else if(wk->inputmode==NAMEIN_FRIENDCODE){
		ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+3, wk->bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
		wk->mode = NAMEIN_MODE_NUMCODE;
		MakeWordMap(wk->wordmap,4);			// �����̂ݕ����}�b�v�W�J
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0a0a, 4, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[3]*/),wk->BgCharaDat->pRawData);
	}else{
		wk->mode = NAMEIN_MODE_HIRA;
		MakeWordMap(wk->wordmap,0);			// �Ђ炪�ȕ����}�b�v�W�J
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0404, 0, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[0]*/),wk->BgCharaDat->pRawData);
	}




	// ��ʏ㕔���b�Z�[�W�pBMPWIN�m��
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_TITLE_MES], GF_BGL_FRAME2_M,
						NAME_INFO_POSX, NAME_INFO_POSY, NAME_INFO_POSW, NAME_INFO_POSH, 0,  NAMEINFO_WIN_OFFSET);



	{
		int w =  ( (wk->inputmax*12) /8 )+1;	// 12dot�����ŕK�v�ȃL�������̎Z�o

		// ���O�\���pBMPWIN�m��
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_RESULT_NAME], GF_BGL_FRAME2_M,
							NAME_RESULT_POSX, NAME_RESULT_POSY, w, NAME_RESULT_POSH, 0,  NAMERESULT_WIN_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );


		// �u�O���[�v�v������
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_GROUP_STRING], GF_BGL_FRAME2_M,
						NAME_RESULT_POSX+w-1, GROUP_TEXT_POSY, GROUP_TEXT_POSW, GROUP_TEXT_POSH, 0,  GROUP_TEXT_WIN_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_GROUP_STRING], 0x0101 );
	}

	if(wk->inputmode==NAMEIN_RANDOMGROUP){
		PrintTitleInfoStr(&wk->NameInWin[BMP_GROUP_STRING], wk->inputmode, wk->GroupString );
		GF_BGL_BmpWinOn( &wk->NameInWin[BMP_GROUP_STRING] );
	}


	// BOX�a���p�ɉ�b�E�C���h�E�̈���m�ۂ���
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_TALK_WIN], GF_BGL_FRAME0_S,
						TALK_MSG_WIN_PX, TALK_MSG_WIN_PY, TALK_MSG_WIN_SX, TALK_MSG_WIN_SY, TALK_MSG_WIN_PAL, BOX_MESAGGE_WIN_OFFSET);
	GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_TALK_WIN], 0x0f0f );
	

	// �u�`�̂Ȃ܂��́H�v�������\��
	PrintTalkInfoStr(&wk->NameInWin[BMP_TALK_WIN], wk->inputmode, wk->TitleStr);


	// NAMEIN_PARAM�Ƀf�t�H���g�����񂪓����Ă����甽�f������
	{
		NAMEIN_PARAM* param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);

		if(wk->paramstr[0]!= EOM_)
		{
			PM_strcpy(wk->inputword,wk->paramstr);
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);		
		}
	}
	
	// ����ʃ{�^���pBMP�m��
	{
		int i;
		// �u�́@�΁@�ρv�Ȃ�
		for(i=0;i<3;i++){
			// �ǂ���OBJVRAM�ɓ]������̂ŁABG�ʂ͂ǂ��ł�����
			GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_SUB_BUTTON1+i], GF_BGL_FRAME2_M,	0, 0, 2, 2, 0,  SUB_BUTTON_WORD_OFFSET);
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_SUB_BUTTON1+i], 0 );
		}

		// �u��������������v
		// �ǂ���OBJVRAM�ɓ]������̂ŁABG�ʂ͂ǂ��ł�����
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_SUB_STRING], GF_BGL_FRAME2_M,	0, 0, 16, 2, 0,  SUB_BUTTON_STRING_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_SUB_STRING], 0 );


	}
}	

//------------------------------------------------------------------
/**
 * Bg0�ʂ�BG1�ʂ̃v���C�I���e�B���R���R���ς��̂Ŋ֐���
 *
 * @param   front	�ǂ���̖ʂ���ɗ��邩(0 or 1)
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void FrontBackBG_RegSet(GF_BGL_INI *bgl, int front, VecFx32 panelpos[])
{
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M+front, 1 );
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M+front^1, 2 );

}

//------------------------------------------------------------------
/**
 * �����p�l���̏������W�ۑ�
 *
 * @param   panelpos[]		�����p�l���̈ʒu
 * @param   front				BG0�ʂ�BG1�ʂ̂ǂ��炪�ォ(0����BG0����)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetPanelFirstPos(VecFx32 panelpos[], int front)
{
	panelpos[front].x   = HIDDENPANEL_POS_REGX;
    panelpos[front].y   = WORDPANEL_POS_REGY;
    panelpos[front^1].x = WORDPANEL_POS_REGX;
    panelpos[front^1].y = WORDPANEL_POS_REGY;
	
}

#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * �f�o�b�O�\���p��OBJ��BG�𓮂���
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugOBJPOSGet(NAMEIN_WORK *wk)
{
		if( sys.cont & PAD_KEY_UP){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}
		if( sys.cont & PAD_KEY_DOWN){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_LEFT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_RIGHT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}

}

#endif



#define MOVE_UP 	1
#define MOVE_DOWN 	2
#define MOVE_LEFT 	3
#define MOVE_RIGHT 	4

static const arrowtbl[][2]={{0,0},{0,-1},{0,1},{-1,0},{1,0}};

static int AroundWork(int w, int min, int max)
{
	if(w>=max){
		w = min;
	}
	if(w<min){
		w = max-1;
	}
	return w;
}

//------------------------------------------------------------------
/**
 * �J�[�\���ړ���
 *
 * @param   wk		NAMEIN_WORK*
 * @param   arrow	�ړ������t���O
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void CursorMove(NAMEIN_WORK *wk, int arrow)
{
	int x,y;
	u16 old;
	
	if(arrow==0){
		return;
	}
	
	// �c���SKIP�̗񂾂ƁA�������[�v�ɓ���̂ŗv�C���i�ƂȂ�̗����������Ȃǁj
	old  = wk->wordmap[wk->Cursor.y][wk->Cursor.x];
	x    = AroundWork((wk->Cursor.x + arrowtbl[arrow][0]), 0, INPUT_WORD_W);
	y    = AroundWork((wk->Cursor.y + arrowtbl[arrow][1]), 0, INPUT_WORD_H);

	// X�����̈ړ��i�@�\�{�^���E�X�L�b�v�񏈗����݁j
	while(wk->wordmap[y][x]==SKIP_ || (wk->wordmap[y][x]==old && wk->wordmap[y][x]>NAMEIN_BUTTON)){
//		OS_Printf(" %d, %d, \n",wk->wordmap[y][x], old, );

		if(wk->Cursor.oldy==0 && wk->wordmap[y][x]==SKIP_ && arrowtbl[arrow][1]!=0){	// �{�^���̏�ɂ��āA���̍s��SKIP��
			x += wk->Cursor.lastxarrow;													// �������ꍇ�̏����i�Ō�̉��ړ���
			x = AroundWork(x, 0, INPUT_WORD_W);											// �Ƃ��Ă����Ă��̕����ɂ��炷�j
		}else{
			x += arrowtbl[arrow][0];													// �ړ��悪SKIP_�������ꍇ��
			x = AroundWork(x, 0, INPUT_WORD_W);											// SKIP_����Ȃ��Ȃ�܂ňړ����J��Ԃ�
			y += arrowtbl[arrow][1];
			y = AroundWork(y, 0, INPUT_WORD_H);
		}
	}
	
	// �ŏI�ړ�����i�[
	wk->Cursor.x = x;	
	wk->Cursor.y = y;
}

//------------------------------------------------------------------
/**
 * �J�[�\���ړ�����
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none	
 */
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
static BOOL TouchPanelCheck( NAMEIN_WORK *wk );
#endif
//------------------------------------------------------------------
static void ControlCursor(NAMEIN_WORK *wk)
{
	int move  = 0;
	int arrow = 0;

	// �L�[���͂ɑ΂��Ĉړ�����S�����̂����̈������
	if( sys.repeat & PAD_KEY_UP){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_UP;
		move++;
	}
	if( sys.repeat & PAD_KEY_DOWN){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_DOWN;
		move++;
	}
	if( sys.repeat & PAD_KEY_LEFT){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_LEFT;
		move++;
	}
	if( sys.repeat & PAD_KEY_RIGHT){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_RIGHT;
		move++;
	}
	
	// �I���{�^���ʒu��
	if( sys.trg & PAD_BUTTON_START){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		wk->Cursor.x = 12;
		wk->Cursor.y = 0;
		move++;
	}
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
	{
		if( ( wk->TP_decide = TouchPanelCheck( wk ) ) == TRUE ){
			arrow = 0;
			move++;
		}
	}
#endif
	// �ړ�������������ύX
	if(move){
		CursorMove(wk,arrow);				// �J�[�\���̈ړ�������肷��
		CursorAppearUpDate(wk,arrow);	// �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
	}

}


//------------------------------------------------------------------
/**
 * �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
 * �����̏�ł���΁A�����`�̃J�[�\���A�{�^���̏�ł���Β����`�̃J�[�\��
 * �����̍X�V���s���邱�ƂŁA�T�u��ʂ̒��̃t�H���g�̍X�V���s����
 *
 * @param   wk			NAMEIN_WORK*
 * @param   arrow		�ړ�����
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(NAMEIN_WORK *wk, int arrow)
{
	// �J�[�\���������̗�ɂ��邩�H
	if(wk->Cursor.y!=0){
		VecFx32 tmpVex;

		// �����̗�ɂ���
		if(wk->Cursor.oldy==0 && wk->Cursor.oldy != wk->Cursor.y){		// ���O�Ƀt�@���N�V�����{�^���̏�ɂ�����
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START );	// �ʏ�J�[�\���ɃA�N�^�[�ύX
		}
		tmpVex.x = FX32_ONE*(MAIN_CURSOR_POSX+wk->Cursor.x*16);
		tmpVex.y = FX32_ONE*(MAIN_CURSOR_POSY+(wk->Cursor.y-1)*PANEL_H);
		CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);
	}else{
		VecFx32 tmpVex;

		// �{�^���̗�ɂ���
		int func_type = wk->wordmap[wk->Cursor.y][wk->Cursor.x]-NAMEIN_HIRA;
		tmpVex.x = FX32_ONE*func_button_pos_tbl[func_type];
		tmpVex.y = FX32_ONE*FUNC_BUTTON_POS_Y;
		CLACT_AnmChg( wk->clActWork[8], func_button_appear[func_type] );// �{�^���ɑΉ������J�[�\���ɕύX
		CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);

		
	}
	wk->CursorPal = 180;							// �ړ�������J�[�\���̃p���b�g�͐Ԃ���Ԃɖ߂�
	CLACT_AnmFrameSet( wk->clActWork[8], 0 );		// �ړ�������J�[�\���̃A�j���͍ŏ��̃t���[���ɖ߂�


	wk->Cursor.oldx       = wk->Cursor.x;
	wk->Cursor.oldy       = wk->Cursor.y;
	if(arrowtbl[arrow][0]!=0){
		wk->Cursor.lastxarrow = arrowtbl[arrow][0];
	}

}

//------------------------------------------------------------------
/**
 * �A�j���[�V�����ɂ��킹�ĉ���ʂ̃{�^��BG�̃X�N���[��������������
 *
 * @param   mode		
 * @param   work		
 * @param   bgl		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubButtonBGFunc(int *mode, int *work, GF_BGL_INI *bgl)
{

	switch(*work){
	case 1:	case 5:
	// �����BG0�X�N���[���]��
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s2_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	case 3:	
	// �����BG0�X�N���[���]��
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s3_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	case 7:	
	// �����BG0�X�N���[���]��
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	}


	// �u�����v���u�����v�̍ۂɂ�work���グ��������
	if(mode!=0){		// 
		if(*work > 9 ){	// 6�ȏ�ɂ͂Ȃ�Ȃ��悤��
			*work = 0;
			*mode  = 0;
		}
		*work += *mode;
	}
//	OS_Printf("mode = %d, work = %d\n",mode, *work);
}

//------------------------------------------------------------------
/**
 * �^�b�`�p�l���ŉ������{�^�����ւ���
 *
 * @param   wk		NAMEIN_WORK�̃|�C���^
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchFunc(NAMEIN_WORK *wk)
{
#ifndef NAMEIN_MAINUSE_TOUCHPANEL
	int button=-1,i;

	// ���͏���
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if(button != RECT_HIT_NONE && wk->subtouchword[button] != spc_){
//		DecideMainButton(wk,wk->subtouchword[button]);
		DecideMainButton(wk,NAMEIN_KOMOJI,1);				// �ϊ��{�^��ON
		CLACT_AnmChg( wk->clActWork[10], sub_button_info[0][2] );	// ����ʂ̕�����BG�ɍ��킹�ď㉺�ɓ�����
		CLACT_AnmChg( wk->clActWork[11], sub_button_info[1][2]+1 );	// ����ʂ̕�����BG�ɍ��킹�ď㉺�ɓ�����
		wk->subbutton_mode=1;
	}

	// �����ڂ̏���
//	button=GF_TP_RectHitCont( sub_button_hittbl );

	SubButtonBGFunc(&wk->subbutton_mode, &wk->subbutton_work, wk->bgl);
#endif
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


	GX_LoadOBJPltt((u16*)&tmp, (16+13)*2, 2);
}



//------------------------------------------------------------------
/**
 * �����p�l���ɋϓ��ȊԊu�ɕ�����z�u����
 * �v���|�[�V���i���t�H���g�Ȃ̂ŉ������m�F���Ȃ���ꕶ�����z�u����
 *
 * �u�h�v�u�K�v�u[s]�v�ɑΉ�(CODE��DAKUTEN_,HANDAKUTEN_,SPACE_�j
 * ������12�h�b�g���z�u����鎖�ɂ���B
 *
 * @param   win		bmp
 * @param   str		������
 * @param   x		�J�nX�i����j
 * @param   y		�J�nY�i����j
 * @param   sw		MSG_ALLPUT��MSG_NO_PUT
 * @param   color	5bitx3�̃J���[�w��
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NameinWordPanelPrint(GF_BGL_BMPWIN *win, const u16 *str, int x,int y, int space, int sw, GF_PRINTCOLOR color, u8 *dakuten_Character)
{
	int i=0,w,dx;
	u16 word[2];
	STRBUF *strbuf_word;
	
	strbuf_word = STRBUF_Create( 2, HEAPID_NAMEIN );
	// �ꕶ�������o��
	while(str[i]!=EOM_){
		// ���ꕶ���������ꍇ�̏���
		if(str[i]==DAKU_ || str[i]==HANDAKU_ || str[i]==SPACE_){
			u16 tmp = str[i] - NAMEIN_CODE;


			//12x12�̓��ꕶ����`��
			GF_BGL_BmpWinPrint(	win, (void*)&dakuten_Character[tmp*8*8*4/2],
				0, 0, 12, 12,
				x+i*space, y+2, 12, 12 );

		}else{
		// �ʏ핶������

			if(str[i]==SKIP_){		//�X�L�b�v�L���͕`�悵�Ȃ�
				i++;
				continue;
			}
			word[0] = str[i];
			word[1] = EOM_;

			//�t�H���g�̉������擾���A12�h�b�g���z�u����Ƃ��̍����Z�o���ĕ`��
			w=FontProc_GetStrWidth( FONT_SYSTEM, word, 0 );
			dx = x+i*space+((space-w)/2);
			STRBUF_SetStringCode( strbuf_word, word );
			GF_STR_PrintColor(	win, FONT_SYSTEM, strbuf_word, dx, y, sw, color,NULL);

		}
		i++;
	}	
	STRBUF_Delete( strbuf_word );
}


static const u8 StringCharacterOffsetTable[]={
	96,104,80,88
};


static void *GF_STR_PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, u8 fnt_index,const   GF_PRINTCOLOR col)
{

	GF_STR_PrintColor(	win, fnt_index, msg, 0, 0, MSG_NO_PUT, col,NULL);

	return win->chrbuf;
}

//------------------------------------------------------------------
/**
 * ����ʂ̃{�^���ɏ�����Ă��镶���L�����N�^�[��]��
 *
 * @param   win		������W�J����BMPWIN�\���̂̃|�C���^
 * @param   tbl		�u�͂΂ρv�Ȃǂ̕ϊ�����������������e�[�u���̃|�C���^�B��������NULL
 * @param   code	�ϊ����̖��������͂����ɓ����Btbl������Ƃ���0
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChangeSubPanelButtonWord(GF_BGL_BMPWIN *win, const u16 *tbl, u8 *TransWork, STRBUF *ChangeWordStr)
{
	u16  word[SUB_BUTTON_STRING_MAX+1],i,n;
	void *objcharaadr;
	STRBUF *strbuf_word;

	GF_BGL_BmpWinDataFill( &win[3], 0 );
	
	// �u��������������v�`��
	objcharaadr=GF_STR_PrintCGXOnly(&win[3], ChangeWordStr, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xd,0x0e,0xf));

	// BMP�����ŕ`�悵���o�b�t�@��OBJ�ɓ]�����Ĕ��f������
	DC_FlushRange(objcharaadr,0x20*4*16);	
	for(i=0;i<4;i++){						
		FONTOAM_BmpCutOamSize( &win[3], 4, 2, 4*i, 0,  (char*)TransWork);
		DC_FlushRange(TransWork,0x20*4*2);	
		GXS_LoadOBJ(TransWork, StringCharacterOffsetTable[i]*0x20, 0x20*4*2);
	}


	// STRBUF�쐬
	strbuf_word = STRBUF_Create(SUB_BUTTON_STRING_MAX+1, HEAPID_NAMEIN);
	
	// BMPWIN�ŕ����L�����N�^���쐬������AOBJVRAM�ɓ]�����鏈�����R��J��Ԃ�
	for(i=0;i<3;i++){
		word[0] = tbl[i];
		word[1] = EOM_;
		GF_BGL_BmpWinDataFill( &win[i], 0 );

		// STRBUF�ɕϊ��ABMP�����ŃL�����N�^�[�`��
		STRBUF_SetStringCode( strbuf_word, word );
		objcharaadr=GF_STR_PrintCGXOnly(&win[i], strbuf_word, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xd,0x0e,0xf));

		// BMP�����ŕ`�悵���o�b�t�@��OBJ�ɓ]�����Ĕ��f������
		DC_FlushRange(objcharaadr,0x20*4);	
		GXS_LoadOBJ(objcharaadr, obj_word_offset[i]*0x20, 0x20*4);

	}

	STRBUF_Delete(strbuf_word);
}

//------------------------------------------------------------------
/**
 * �J�[�\�����ړ��������ɁA����ʃ{�^���̒��̕���������������
 *
 * @param   win		GF_BGL_BMPWIN*
 * @param   code	�����R�[�h
 * @param   words	NAMEIN_WORK.subtouchword
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubPanelButton_CharaChange(GF_BGL_BMPWIN *win, STRCODE *str,int pos, u16 *words, u8 *TransWork, STRBUF *ChangeWordStr)
{
	int i,r;
	const u16 *tbl = NULL;
	STRCODE code;

	if(pos==0){
		code = SPACE_;
	}else{
		code = str[pos-1];
	}

	// ���ꕶ���E�{�^���̃R�[�h�͑S�ċ󔒕����Ƃ��ĕ\��
	switch(code){
	case DAKU_			:	case HANDAKU_		:	case SPACE_			:	case SKIP_			:
	case NAMEIN_HIRA	:	case NAMEIN_KANA	:	case NAMEIN_ALPHA	:	case NAMEIN_KIGOU	:
	case NAMEIN_KOMOJI	:	case NAMEIN_MODORU	:	case NAMEIN_OWARI	:
		code = spc_;
	break;
	}
	
	for(i=0;i<3;i++){		// ��U������
		words[i] = spc_;
	}
	words[0] = code;		// ���R�[�h���

	if(code!=spc_){	
		// �ϊ��e�[�u�����������đ����E�������E����������������T��
		for(i=0;i<sizeof(convert_tbl)/(3*2);i++){
			// �ϊ��O�̕���
			if(convert_tbl[i][0]==code){
				for(r=0;r<3;r++){
					words[r] =  convert_tbl[i][r];	// ����������e�[�u�����R�s�[
				}
				break;
			}
			// �ϊ���̏������i�����������ړ��͂ł���悤�ɂȂ����̂Łj
			if(convert_tbl[i][2]==code){
				for(r=0;r<3;r++){
					words[r] =  convert_tbl[i][r];	// ����������e�[�u�����R�s�[
				}
				break;
			}
		}
	}

	// WINBMP��ŏ����AOBJVRAM�ɓ]��
	ChangeSubPanelButtonWord(win, words, TransWork, ChangeWordStr);
}



//------------------------------------------------------------------
/**
 * ���ݓ��͕����p�l���}�b�v���쐬����
 *
 * @param   map[][INPUT_WORD_W]		�������ޕ����}�b�v���[�N
 * @param   no						�����p�l���ԍ�(0-3)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MakeWordMap(u16 map[][INPUT_WORD_W], const int no)
{
	int i,j;
	
	//��ʍŏ�i�̃{�^���z�u�ݒ�
	for(i=0;i<INPUT_WORD_W;i++){
		map[0][i] = str_func_b[no][i];
	}
	
	for(j=0;j<INPUT_WORD_H-1;j++){
		for(i=0;i<INPUT_WORD_W;i++){
			map[1+j][i] = str_nametbl[no][j][i];
		}
	}
}

//------------------------------------------------------------------
/**
 * �������͌���
 *
 * @param   wk		NAMEIN_WORK*
 * @param   code	�����R�[�h(�{�^���E���ꕶ�����܂�)
 *
 * @retval  int		�ʏ��SEQ_MAIN�B�I������SEQ_OUT
 */
//------------------------------------------------------------------
static int DecideMainButton(NAMEIN_WORK *wk,u16 code, int pad)
{
	// ���ꕶ���E�{�^���̃R�[�h�͑S�ċ󔒕����Ƃ��ĕ\��
	if(code==SPACE_ || code == SKIP_){
		code = spc_;
	}

	// �t�����h�R�[�h���͂̎��̐���
	if(wk->inputmode==NAMEIN_FRIENDCODE){
		if(code==NAMEIN_HIRA || code==NAMEIN_KANA || code==NAMEIN_ALPHA || code==NAMEIN_KIGOU ){
			code = spc_;
		}
	}

	switch(code){
	// ���� 
	case DAKU_			:	
		if(ConvertWord(DAKU_WORD_START,DAKU_WORD_NUM,1,DAKU_,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;
	// ������
	case HANDAKU_		:	
		if(ConvertWord(HANDAKU_WORD_START,HANDAKU_WORD_NUM,2,HANDAKU_,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;
	// ������
	case NAMEIN_KOMOJI	:
		if(RotateConvertWord(BIGSMALL_WORD_START,HANDAKU_WORD_NUM,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			wk->funcbutton[4]++;
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;

	// �����p�l���؂�ւ��{�^��
	case NAMEIN_HIRA	:	case NAMEIN_KANA	:	case NAMEIN_ALPHA	:	case NAMEIN_KIGOU	:
		// �p�l���؂�ւ�
		if(wk->mode!=code-NAMEIN_HIRA){
			wk->seq  = NAMEIN_MODE_REQ;
			wk->mode = code-NAMEIN_HIRA;
			MakeWordMap(wk->wordmap, wk->mode);		// �������̓}�b�v�����ւ�
			wk->funcbutton[code-NAMEIN_HIRA]++;
			Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
			CLACT_SetDrawFlag( wk->clActWork[8], pad);
		}
		break;

	// 1�����߂�
	case NAMEIN_MODORU	:
		if(wk->nowinput!=0){
			wk->inputword[wk->nowinput-1] = EOM_;
			wk->nowinput--;
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			if(wk->nowinput==0){
				// 0�������ƕ����v�����g���������Ȃ��̂�
				GF_BGL_BmpWinOn( &wk->NameInWin[BMP_RESULT_NAME] );
			}else{
				NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
										INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			}
			SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
										wk->inputword,
										wk->nowinput,
										wk->subtouchword,
										wk->ObjTransWork,
										wk->ChangeWordStr);
			InputResultUnderLineMove(wk->NameLineActWork,wk->nowinput, wk->inputmax);
			wk->funcbutton[5]++;
			Snd_SePlay(NAMEIN_SE_BS);
			CLACT_SetDrawFlag( wk->clActWork[8], pad);
		}
		break;
	// ���O���͏I��
	case NAMEIN_OWARI	:		
		// �i�r�Q�[�V�����A�C�R���A�j���I��
//		MSG_DsIconFlashReq( wk->dsicon_task, MSG_DSI_REQ_FREE );

		// �������̕�������������̂ň��S
		MSG_DsIconFlashDelete( wk->dsicon_task );
		CLACT_SetDrawFlag( wk->clActWork[8], pad);

		// ���͏I��
		if(wk->endmode==0){
			Snd_SePlay( NAMEIN_SE_END );
			wk->funcbutton[6]++;
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
			return SEQ_OUT;
		}else{
			wk->seq = NAMEIN_MODE_BOXMSG;
		}
	break;

	// �ʏ�̕�������
	default:
		if(wk->mode==NAMEIN_MODE_NUMCODE && code==spc_){
			return SEQ_MAIN;
		}

		if(wk->nowinput!=wk->inputmax){				//Max�܂ōs���ĂȂ����������
			wk->inputword[wk->nowinput] = code;
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint( &wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			wk->nowinput++;
			InputResultUnderLineMove(wk->NameLineActWork,wk->nowinput, wk->inputmax);
			Snd_SePlay(NAMEIN_SE_DECIDE);

				// �������ɂ��ĐԂ��ۂ̃A�j���ɐ؂�ւ���
				CLACT_SetDrawFlag( wk->clActWork[8], 1);
				CLACT_ObjModeSet( wk->clActWork[8], GX_OAM_MODE_XLU );
				G2_SetBlendAlpha( 0,GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2,8,8 );
				CLACT_AnmChg( wk->clActWork[8], 60);
				wk->Cursor.decide = 1;
			
			SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
										wk->inputword,
										wk->nowinput,
										wk->subtouchword,
										wk->ObjTransWork,
										wk->ChangeWordStr);

		}
	}	
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * �������E���_�E�����_������ł���e�[�u���ɏ�������ւ���������Ԃ�
 * �u���v�Ȃ�u�������v�A�u�́v�Ȃ�u�΁��ρ��́v
 * @param   tbl		
 * @param   pos		
 *
 * @retval  u16		
 */
//------------------------------------------------------------------
static u16 GetConvertWord(const u16 *tbl, int pos)
{

	do{
		pos = AroundWork(++pos,0,3);
//		OS_Printf("pos = %d, code = %d",pos,tbl[pos]);
	}while(tbl[pos]==spc_);
	
//	OS_Printf("last --- pos = %d, code = %d",pos,tbl[pos]);
	return tbl[pos];
}

//------------------------------------------------------------------
/**
 * �u��������������v�{�^������
 *
 * @param   start	convert_tbl�������J�n����ʒu
 * @param   num		convert_tbl�������I������ʒu
 * @param   str		������o�b�t�@
 * @param   pos		���݂̃J�[�\��
 *
 * @retval  int		0�Ȃ玸�s	1�Ȃ琬���istr�͏���������Ă���)
 */
//------------------------------------------------------------------
static int RotateConvertWord(int start, int num, u16 *str, int pos)
{
	int i,r;
	u16 code,w;
	if(pos==0){
		return 0;
	}

	code = str[pos-1];

	for(i=start;i<num;i++){
		for(r=0;r<3;r++){
			if(convert_tbl[i][r]==code && code!=spc_){
				str[pos-1] = GetConvertWord(convert_tbl[i],r);
				return 1;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * ���͍ςݕ����ϊ�����
 *
 * @param   start	convert_tbl�̌����J�n�ʒu
 * @param   num		convert_tbl�̌����I���ʒu
 * @param   target	convert_tbl�̂O�����ڂƔ�r����̂͂P�Ԗڂ��Q�Ԗڂ��i1or2)
 * @param   flag	DAKU_,HANDAKU_,NAMEIN_KOMOJI�̂ǂꂩ
 * @param   str		���͍ςݕ�����
 * @param   pos		���ݓ��͑҂��̏ꏊ
 *
 * @retval  int		0=�ϊ�����	1=�ϊ�����
 */
//------------------------------------------------------------------
static int ConvertWord(int start, int num, int target, int flag, u16 *str, int pos)
{
	int i;
	u16 code;

	// 1���������͂��Ă��Ȃ��ꍇ�͕ϊ��͔������Ȃ�
	if(pos==0 || str[pos-1]==spc_){
		return 0;
	}	

	// ���̕�����ϊ�����
	code=str[pos-1];
	for(i=start;i<num;i++){
		if(convert_tbl[i][0]==code){
			str[pos-1]=convert_tbl[i][target];
			return 1;
		}
	}

	// �ϊ��ς݂̕��������ɖ߂�
	for(i=start;i<num;i++){
		if(convert_tbl[i][target]==code){
			str[pos-1]=convert_tbl[i][0];
			return 1;
		}
	}

	//���ꏈ���u�΁��ρv�u�Á����v�Ȃ�

	switch(flag){
	case DAKU_:
		for(i=0;i<NELEMS(extra_daku_tbl);i++){
			if(extra_daku_tbl[i][0]==code){
				str[pos-1] = extra_daku_tbl[i][1];
				return 1;
			}
		}
		break;
	case HANDAKU_:
		for(i=0;i<NELEMS(extra_handaku_tbl);i++){
			if(extra_handaku_tbl[i][0]==code){
				str[pos-1] = extra_handaku_tbl[i][1];
				return 1;
			}
		}
		break;
	case NAMEIN_KOMOJI:
		if(code==du_){
			str[pos-1] = ttu_;
			return 1;
		}
		if(code==DU_){
			str[pos-1] = TTU_;
			return 1;
		}
		break;
	}	

	// �ϊ������ł͂Ȃ�����
	return 0;
}


//------------------------------------------------------------------
/**
 * ���͍ςݕ�����̉��̃A���_�[���C���𓮂����w����s��
 *
 * @param   lineact		�A���_�[���C���̃Z���A�N�^�[�̃|�C���^
 * @param   pos			�ʒu
 * @param   max			�����ő吔
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InputResultUnderLineMove(CLACT_WORK_PTR *lineact,int pos, int max)
{
	int i;
	for(i=0;i<max;i++){
		CLACT_AnmChg( lineact[i], 43 );		// �S�ăA���_�[���C���������Ȃ���ԂɃN���A
	}
	if(pos!=max){
		CLACT_AnmChg( lineact[pos], 44 );	// �w��̕������㉺�ɓ�����
	}
}


#define PLATE_CHARA_OFFSET1	( 12 )
#define PLATE_CHARA_OFFSET2	( 16 )
#define PLATE_H_CHARASIZE	(  8 )	// �����p�l������BMP�������ݕ����L�����c��

static const u8 plate_num[]={2,2,3,2,2};
static const u8 plate_table[][3]={
	{8*8,17*8,0,},
	{8*8,17*8,0,},
	{5*8,12*8,18*8,},
	{8*8,17*8,0,},
	{8*8,17*8,0,},

};
static const u8 plate_chara_no[][5]={
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
};

static const u8 plate_chara_pos[5]={
	0,1,2,3,3
};

static const u8 plate_wall_col[]={3,6,0xc,9,9};

//------------------------------------------------------------------
/**
 * �����p�l���̕����z�u�E�g�`��Ȃǂ��s��
 *
 * @param   win			GF_BGL_WINBMP*
 * @param   bgchara		�����p�l���̔w�i�L����
 * @param   frame		�O�`�R�̕����p�l���ԍ�
 * @param   color		GF_PRINTCOLOR
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WordPanelSetUp(GF_BGL_BMPWIN *win,u16 bgchara, int frame, GF_PRINTCOLOR color, u8* dakuten_Character )
{
	int i,r,h;

	// ���ꂼ��̕����p�l���̔w�i�F�ŃN���A
	GF_BGL_BmpWinDataFill( win, bgchara );

	// �����p�l�����̎d�؂��`��
//	for(r=0;r<plate_num[frame];r++){
//		for(i=0;i<PLATE_H_CHARASIZE;i++){
//			GF_BGL_BmpWinPrint(	win, (void*)&dakuten_Character[(plate_chara_no[frame][r]+plate_chara_pos[frame])*8*8/2],
//				0, 0, 8, 8,
//				plate_table[frame][r], 8*i, 8, 8 );
//		}
//	}

	// �����p�l���Ɏs���͗l��`��
	for(i=0;i<6;i++){
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 0,  16,   PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 19*2, 16, PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 19*4, 16, PANEL_H );		
	}
	for(i=0;i<7;i++){
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 32*i, 19,   16, PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 32*i, 19*3, 16, PANEL_H );		
	}

	// �`��
	for(i=0;i<5;i++){
		NameinWordPanelPrint(win,str_nametbl[frame][i],0,i*PANEL_H+4,
								WORDPANEL_WORD_SPACE, MSG_NO_PUT,color,dakuten_Character);
	}
	// �]��
	GF_BGL_BmpWinOn( win );

}

//------------------------------------------------------------------
/**
 * �@�\�{�^���i���ȁE�J�i�EABC�E�������^�������^���ǂ邨���j�̃A�j������
 *
 * @param   funcbutton[]	�{�^��������ԃt���O��
 * @param   ButtonAct		CLACT_WORK_PTR
 * @param   frame			���݂̕����p�l���ԍ�
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FuncButtonAnimation(int funcbutton[], CLACT_WORK_PTR *ButtonAct, int frame)
{
	int i,r;
	// ���� �J�i ABC ������ �{�^��
	for(i=0;i<4;i++){
		if(funcbutton[i]){
			for(r=0;r<4;r++){
				CLACT_AnmChg( ButtonAct[r], main_button_info[r][2] );
			}
			CLACT_AnmChg( ButtonAct[i], main_button_info[i][2]-3 );
			break;
		}
	}

	// ���������{�^���i���� �J�i ABC�ɂ���ăZ���A�j�����Ⴄ�j
//	if(funcbutton[4]){
//		CLACT_AnmChg( ButtonAct[4], main_button_info[4][2] + frame);	// �u�L���v�̏��������{�^���͑��݂��Ȃ�
//	}

	// ���ǂ� �����{�^��
	for(i=5;i<7;i++){
		if(funcbutton[i]){
			CLACT_AnmChg( ButtonAct[i], main_button_info[i][2]+1);
		}
	}
	
	// �A�j�������f���ꂽ��N���A
	for(i=0;i<7;i++){
		funcbutton[i] = 0;
	}

}


//------------------------------------------------------------------
/**
 * @brief   �J�[�\���A�j���[�V��������
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAnimationControl( NAMEIN_WORK *wk )
{
	// �J�[�\�����A�j���I����ԂɂȂ��Ă���ꍇ�͒ʏ�J�[�\���ɕω�������
	if(!CLACT_AnmActiveCheck( wk->clActWork[8] )){
		if(wk->nowinput==wk->inputmax){			// �������̓}�b�N�X�܂ł�����u�I���v�{�^����
			wk->Cursor.x = 12;
			wk->Cursor.y = 0;
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START);
			OS_Printf("����������\n");
		}else{
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START);
		}

		// �\���n�m�Ȃ�J�[�\���`���߂��E�\���n�e�e�Ȃ�J�[�\�����B��
		if(wk->Cursor.on==0){
			CLACT_SetDrawFlag( wk->clActWork[8], 0);
		}else{
			CursorAppearUpDate(wk,0);		// �ړ��̌��ʃJ�[�\���̌`�󂪂ǂ̂悤�ɕς�邩�����肷��
		}
		wk->Cursor.decide = 0;

		// �������n�a�i������
		CLACT_ObjModeSet( wk->clActWork[8], GX_OAM_MODE_NORMAL );
	}

}

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
//------------------------------------------------------------------
/**
 * �^�b�`�p�l�����菈��
 *
 * @param   wk
 * @return  
 */
//------------------------------------------------------------------
//�f�[�^�ݒ�\���́i���o�C�i���f�[�^�j
typedef struct NM_TP_DATA_tag
{
	u8 x;
	u8 y;
	u16 type:2;
	u8	cx:5;
	u8	cy:5;
}NM_TP_DATA;

enum {
	CTYPE_S1 = 0,		// �����Ȃ��E�Ђ炪�ȁE�`�a�b�E������
	CTYPE_S2 = 1,		// ���ǂ�E�����
	CTYPE_WD = 2,		// ����
};


static const NM_TP_DATA TouchPanelDataTable[] = {
	{ MAIN_BUTTON1_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 0,0},
	{ MAIN_BUTTON2_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 1,0},	
	{ MAIN_BUTTON3_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 3,0},
	{ MAIN_BUTTON4_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 4,0},	
	{ MAIN_BUTTON6_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S2, 8,0},
	{ MAIN_BUTTON7_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S2,11,0},

	{PANEL_X+  0, PANEL_Y+ 0,CTYPE_WD, 0,1},{PANEL_X+ 16, PANEL_Y+ 0,CTYPE_WD, 1,1},{PANEL_X+ 32, PANEL_Y+ 0,CTYPE_WD, 2,1},
	{PANEL_X+ 48, PANEL_Y+ 0,CTYPE_WD, 3,1},{PANEL_X+ 64, PANEL_Y+ 0,CTYPE_WD, 4,1},
	{PANEL_X+ 80, PANEL_Y+ 0,CTYPE_WD, 5,1},{PANEL_X+ 96, PANEL_Y+ 0,CTYPE_WD, 6,1},{PANEL_X+112, PANEL_Y+ 0,CTYPE_WD, 7,1},
	{PANEL_X+128, PANEL_Y+ 0,CTYPE_WD, 8,1},{PANEL_X+144, PANEL_Y+ 0,CTYPE_WD, 9,1},
	{PANEL_X+160, PANEL_Y+ 0,CTYPE_WD,10,1},{PANEL_X+176, PANEL_Y+ 0,CTYPE_WD,11,1},{PANEL_X+192, PANEL_Y+ 0,CTYPE_WD,12,1},

	{PANEL_X+  0, PANEL_Y+PANEL_H,CTYPE_WD, 0,2},{PANEL_X+ 16, PANEL_Y+PANEL_H,CTYPE_WD, 1,2},{PANEL_X+ 32, PANEL_Y+PANEL_H,CTYPE_WD, 2,2},
	{PANEL_X+ 48, PANEL_Y+PANEL_H,CTYPE_WD, 3,2},{PANEL_X+ 64, PANEL_Y+PANEL_H,CTYPE_WD, 4,2},
	{PANEL_X+ 80, PANEL_Y+PANEL_H,CTYPE_WD, 5,2},{PANEL_X+ 96, PANEL_Y+PANEL_H,CTYPE_WD, 6,2},{PANEL_X+112, PANEL_Y+PANEL_H,CTYPE_WD, 7,2},
	{PANEL_X+128, PANEL_Y+PANEL_H,CTYPE_WD, 8,2},{PANEL_X+144, PANEL_Y+PANEL_H,CTYPE_WD, 9,2},
	{PANEL_X+160, PANEL_Y+PANEL_H,CTYPE_WD,10,2},{PANEL_X+176, PANEL_Y+PANEL_H,CTYPE_WD,11,2},{PANEL_X+192, PANEL_Y+PANEL_H,CTYPE_WD,12,2},

	{PANEL_X+  0, PANEL_Y+PANEL_H*2,CTYPE_WD, 0,3},{PANEL_X+ 16, PANEL_Y+PANEL_H*2,CTYPE_WD, 1,3},{PANEL_X+ 32, PANEL_Y+PANEL_H*2,CTYPE_WD, 2,3},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*2,CTYPE_WD, 3,3},{PANEL_X+ 64, PANEL_Y+PANEL_H*2,CTYPE_WD, 4,3},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*2,CTYPE_WD, 5,3},{PANEL_X+ 96, PANEL_Y+PANEL_H*2,CTYPE_WD, 6,3},{PANEL_X+112, PANEL_Y+PANEL_H*2,CTYPE_WD, 7,3},
	{PANEL_X+128, PANEL_Y+PANEL_H*2,CTYPE_WD, 8,3},{PANEL_X+144, PANEL_Y+PANEL_H*2,CTYPE_WD, 9,3},
	{PANEL_X+160, PANEL_Y+PANEL_H*2,CTYPE_WD,10,3},{PANEL_X+176, PANEL_Y+PANEL_H*2,CTYPE_WD,11,3},{PANEL_X+192, PANEL_Y+PANEL_H*2,CTYPE_WD,12,3},

	{PANEL_X+  0, PANEL_Y+PANEL_H*3,CTYPE_WD, 0,4},{PANEL_X+ 16, PANEL_Y+PANEL_H*3,CTYPE_WD, 1,4},{PANEL_X+ 32, PANEL_Y+PANEL_H*3,CTYPE_WD, 2,4},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*3,CTYPE_WD, 3,4},{PANEL_X+ 64, PANEL_Y+PANEL_H*3,CTYPE_WD, 4,4},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*3,CTYPE_WD, 5,4},{PANEL_X+ 96, PANEL_Y+PANEL_H*3,CTYPE_WD, 6,4},{PANEL_X+112, PANEL_Y+PANEL_H*3,CTYPE_WD, 7,4},
	{PANEL_X+128, PANEL_Y+PANEL_H*3,CTYPE_WD, 8,4},{PANEL_X+144, PANEL_Y+PANEL_H*3,CTYPE_WD, 9,4},
	{PANEL_X+160, PANEL_Y+PANEL_H*3,CTYPE_WD,10,4},{PANEL_X+176, PANEL_Y+PANEL_H*3,CTYPE_WD,11,4},{PANEL_X+192, PANEL_Y+PANEL_H*3,CTYPE_WD,12,4},

	{PANEL_X+  0, PANEL_Y+PANEL_H*4,CTYPE_WD, 0,5},{PANEL_X+ 16, PANEL_Y+PANEL_H*4,CTYPE_WD, 1,5},{PANEL_X+ 32, PANEL_Y+PANEL_H*4,CTYPE_WD, 2,5},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*4,CTYPE_WD, 3,5},{PANEL_X+ 64, PANEL_Y+PANEL_H*4,CTYPE_WD, 4,5},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*4,CTYPE_WD, 5,5},{PANEL_X+ 96, PANEL_Y+PANEL_H*4,CTYPE_WD, 6,5},{PANEL_X+112, PANEL_Y+PANEL_H*4,CTYPE_WD, 7,5},
	{PANEL_X+128, PANEL_Y+PANEL_H*4,CTYPE_WD, 8,5},{PANEL_X+144, PANEL_Y+PANEL_H*4,CTYPE_WD, 9,5},
	{PANEL_X+160, PANEL_Y+PANEL_H*4,CTYPE_WD,10,5},{PANEL_X+176, PANEL_Y+PANEL_H*4,CTYPE_WD,11,5},{PANEL_X+192, PANEL_Y+PANEL_H*4,CTYPE_WD,12,5},
};

#define TP_DATATBL_MAX ( NELEMS( TouchPanelDataTable ) )

//------------------------------------------------------------------
/**
 * @brief   �����ՂɑΉ������^�b�`���胋�[�`��
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL TouchPanelCheck( NAMEIN_WORK *wk )
{
	int	i,start=0;
	u8	x,y,start_x,start_y,size_x,size_y;

	// �t�����h�R�[�h���͂̎��͕����Ր؂�ւ��{�^���𖳌��ɂ���
	if(wk->inputmode==NAMEIN_FRIENDCODE){
		start = 4;
	}

	if( sys.tp_trg ){

		//���荞�݂Œl���ς��Ȃ��悤��
		x = sys.tp_x;
		y = sys.tp_y;

		for(i=start;i<TP_DATATBL_MAX;i++){
			start_x = TouchPanelDataTable[i].x;
			start_y = TouchPanelDataTable[i].y;

			// �{�^�������擾
			switch( TouchPanelDataTable[i].type ){

			case CTYPE_S1:
				size_x = 24-1;
				size_y = 22;
				break;
			case CTYPE_S2:
				size_x = 32;
				size_y = 22;
				break;
			case CTYPE_WD:
				size_x = 16;
				size_y = PANEL_H;
				break;
			}
			
			// �����蔻��
			if((x >= start_x)&&(y >= start_y)&&(x <= (start_x+size_x))&&(y <= (start_y+size_y))){
				wk->Cursor.x = TouchPanelDataTable[i].cx;
				wk->Cursor.y = TouchPanelDataTable[i].cy;
				return TRUE;
			}
		}
	}
	return FALSE;
}

#ifdef DEBUG_OAM_POSPRINT
//------------------------------------------------------------------
/**
 * @brief   ���W�m�F�p�n�`�l�̕\��
 *
 * @param   none		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static testclact_set( void )
{
	VecFx32 tmpVex;
	int start_x,start_y,size_x,size_y;

	switch( TouchPanelDataTable[testclact_no].type ){

	case CTYPE_S1:
		size_x = 24-1;
		size_y = 22;
		break;
	case CTYPE_S2:
		size_x = 32;
		size_y = 22;
		break;
	case CTYPE_WD:
		size_x = 16;
		size_y = PANEL_H;
		break;
	}


	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x);
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y);
	CLACT_SetMatrix(testclact[0], &tmpVex);

	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x+size_x);
	tmpVex.y = FX32_ONE*TouchPanelDataTable[testclact_no].y;
	CLACT_SetMatrix(testclact[1], &tmpVex);

	tmpVex.x = FX32_ONE*TouchPanelDataTable[testclact_no].x;
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y+size_y);
	CLACT_SetMatrix(testclact[2], &tmpVex);

	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x+size_x);
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y+size_y);
	CLACT_SetMatrix(testclact[3], &tmpVex);


}
#endif



#endif

