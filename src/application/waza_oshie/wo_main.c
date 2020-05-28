//============================================================================================
/**
 * @file	wo_main.c
 * @brief	�Z����/�v���o�������@���C��
 * @author	Hiroyuki Nakamura
 * @date	06.05.09
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/pmfprint.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "savedata/config.h"
#include "battle/battle_common.h"
#include "battle/wazatype_icon.h"
#include "poketool/waza_tool.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_waza_oboe.h"
#include "application/app_tool.h"
#include "application/p_status.h"

#include "application/waza_oshie.h"
#include "wo_bmp_def.h"
#include "wo_snd_def.h"
#include "waza_oshie_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	WIN_STR_BATTLE = 0,		// �u���������킴�v
	WIN_STR_CONTEST,		// �u�R���e�X�g�킴�v
	WIN_STR_CLASS,			// �u�Ԃ�邢�v
	WIN_STR_ATTACK,			// �u����傭�v
	WIN_STR_HIT,			// �u�߂����イ�v
	WIN_STR_PP,				// �uPP�v
	WIN_STR_APP,			// �u�A�s�[���|�C���g�v
	WIN_PRM_ATTACK,			// �З͒l
	WIN_PRM_HIT,			// �����l
	WIN_PRM_PP,				// PP�l
	WIN_BTL_INFO,			// �퓬����
	WIN_CON_INFO,			// �R���e�X�g����
	WIN_MSG,				// ���b�Z�[�W�E�B���h�E
	WIN_LIST,				// �Z���X�g
	WIN_YESNO,				// �͂�/������

	WIN_MAX
};

enum {
	WO_CLA_ARROW_L = 0,		// �y�[�W�J�[�\����
	WO_CLA_ARROW_R,			// �y�[�W�J�[�\���E
	WO_CLA_ARROW_U,			// ���X�g�J�[�\����
	WO_CLA_ARROW_D,			// ���X�g�J�[�\����
	WO_CLA_CURSOR,			// �I���J�[�\��
	WO_CLA_KIND,			// ���ރA�C�R��
	WO_CLA_TYPE1,			// �^�C�v�A�C�R���P
	WO_CLA_TYPE2,			// �^�C�v�A�C�R���Q
	WO_CLA_TYPE3,			// �^�C�v�A�C�R���R
	WO_CLA_TYPE4,			// �^�C�v�A�C�R���S
	WO_CLA_TYPE5,			// �^�C�v�A�C�R���T
	WO_CLA_TYPE6,			// �^�C�v�A�C�R���U
	WO_CLA_TYPE7,			// �^�C�v�A�C�R���V

	WO_CLA_MAX
};

typedef struct {
	WAZAOSHIE_DATA * dat;			// �O���ݒ�f�[�^

	GF_BGL_INI * bgl;				// BGL�f�[�^

	GF_BGL_BMPWIN	win[WIN_MAX];	// BMP�E�B���h�E�f�[�^

	MSGDATA_MANAGER * mman;		// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;				// �P��Z�b�g
//	NUMFONT * nfnt;				// 8x8�t�H���g
	STRBUF * mbuf;				// �ėp������W�J�̈�

	BMPLIST_WORK * lw;			// BMP���X�g���[�N
	BMP_MENULIST_DATA * ld;		// BMP���X�g�f�[�^

	BMPMENU_WORK * mw;			// BMP���j���[���[�N

	// �Z���A�N�^�[
	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap[WO_CLA_MAX];


	PSTATUS_DATA	psd;
	PROC * subProc;

	int	next_seq;				// ���̃V�[�P���X

	u8	sel_max;

	u8	midx;					// ���b�Z�[�W�C���f�b�N�X
	u8	ynidx;					// �͂��E������ID

}WO_WORK;


typedef int (*WO_SEQ_FUNC)(WO_WORK*);

// �͂��E����������
typedef struct {
	WO_SEQ_FUNC	yes;	// �͂�
	WO_SEQ_FUNC	no;		// ������
}YESNO_FUNC;

// �y�[�W
enum {
	WO_PAGE_BATTLE = 0,	// �퓬
	WO_PAGE_CONTEST		// �R���e�X�g
};

// ���C���V�[�P���X
enum {
	SEQ_FADE_WAIT = 0,	// �t�F�[�h�I���҂�
	SEQ_SELECT,			// �Z�Z���N�g
	SEQ_MSG_WAIT,		// ���b�Z�[�W�I���҂�
	SEQ_YESNO_PUT,		// �͂��E�������Z�b�g
	SEQ_YESNO_WAIT,		// �͂��E�������I��҂�
	SEQ_WAZA_SET,		// �Z�o��
	SEQ_WAZADEL_SET,	// �Y��ċZ�o��
	SEQ_DEL_CHECK,		// �Y�ꂳ����Z���`�F�b�N
	SEQ_FADEOUT_SET,	// �t�F�[�h�A�E�g�Z�b�g
	SEQ_END,			// �I��

	SEQ_PST_INIT,		// �X�e�[�^�X��ʂ�
	SEQ_PST_CALL,		// �X�e�[�^�X��ʌĂяo��
	SEQ_PST_WAIT,		// �X�e�[�^�X��ʏI���҂�
};

// ���b�Z�[�W�e�[�u��ID
enum {
	MSG_SEL_WAZA = 0,		// @0�Ɂ@�ǂ̂킴���@���ڂ�������H
	MSG_SET_CHECK,			// @1�@��  ���ڂ������܂����H
	MSG_END_CHECK,			// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
	MSG_SET_WAZA,			// @0�́@�����炵���@@1���@���ڂ����I��
	MSG_CHG_CHECK,			// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
	MSG_DEL_WAZA,			// �P�@�Q�́c�c�@�|�J���I���@@0�́@@1�� �����������@�`
	MSG_CHG_WAZA,			// @0�́@�����炵�� @1���@���ڂ����I��
	MSG_DEL_CHECK,			// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H
	MSG_CANCEL,				// @0�́@@1���@���ڂ����Ɂ@��������I��
	MSG_SUB_ITEM,			// @2�́@���ꂢ�Ɂ@�n�[�g�̃E���R���@�P�܂��@�������I��
	MSG_DEL_ENTER,			// @0���@�킷�ꂳ���ā@��낵���ł��ˁH"
};

// �͂��E�����������e�[�u��ID
enum {
	YESNO_SET_CHECK = 0,	// @1�@��  ���ڂ������܂����H
	YESNO_END_CHECK,		// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
	YESNO_CHG_CHECK,		// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
	YESNO_DEL_CHECK,		// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H
	YESNO_DEL_ENTER,		// @0���@�킷�ꂳ���ā@��낵���ł��ˁH"
};

// �����W�J���[�h
enum {
	STR_MODE_LEFT = 0,	// ���l��
	STR_MODE_RIGHT,		// �E�l��
	STR_MODE_CENTER,	// ����
};

#define	TMP_MSGBUF_SIZ	( 256 )		// �ėp������W�J�̈�T�C�Y

#define	WOFCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	WOFCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
//#define	WOFCOL_N_BLUE	( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��
//#define	WOFCOL_N_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��
#define	WOFCOL_W_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 15 ) )		// �t�H���g�J���[�F��

#define	HEART_PUT_PX	( 34 )		// �n�[�g��������X���W
#define	HEART_PUT_PY	( 5 )		// �n�[�g��������Y���W
#define	HEART_MAX		( 6 )		// �n�[�g��

#define	HEART_POINT_CHR	( 0x0e )	// �n�[�g�L�����ԍ��i�|�C���g����j
#define	HEART_NONE_CHR	( 0x12 )	// �n�[�g�L�����ԍ��i�|�C���g�Ȃ��j


#define	CLACT_ID_COMMON		( 47272 )	// ���̉�ʂŎg�p����Z���A�N�^�[��ID

// �L�������\�[�XID
enum {
	WO_CHR_ID_ARROW_LR = CLACT_ID_COMMON,	// �y�[�W�J�[�\��
	WO_CHR_ID_ARROW_UD,						// ���X�g�J�[�\��
	WO_CHR_ID_CURSOR,						// �I���J�[�\��
	WO_CHR_ID_KIND,							// ���ރA�C�R��
	WO_CHR_ID_TYPE1,						// �^�C�v�A�C�R���P
	WO_CHR_ID_TYPE2,						// �^�C�v�A�C�R���Q
	WO_CHR_ID_TYPE3,						// �^�C�v�A�C�R���R
	WO_CHR_ID_TYPE4,						// �^�C�v�A�C�R���S
	WO_CHR_ID_TYPE5,						// �^�C�v�A�C�R���T
	WO_CHR_ID_TYPE6,						// �^�C�v�A�C�R���U
	WO_CHR_ID_TYPE7,						// �^�C�v�A�C�R���V
	WO_CHR_ID_MAX = WO_CHR_ID_TYPE7 - WO_CHR_ID_ARROW_LR + 1	// �ő�
};

// �p���b�g���\�[�XID
enum {
	WO_PAL_ID_OBJ = CLACT_ID_COMMON,	// ���낢��
	WO_PAL_ID_TYPE,						// �^�C�v�E���ރA�C�R��
	WO_PAL_ID_MAX = WO_PAL_ID_TYPE - WO_PAL_ID_OBJ + 1	// �ő�
};

// �Z�����\�[�XID
enum {
	WO_CEL_ID_ARROW_LR = CLACT_ID_COMMON,	// �y�[�W�J�[�\��
	WO_CEL_ID_ARROW_UD,						// ���X�g�J�[�\��
	WO_CEL_ID_CURSOR,						// �I���J�[�\��
	WO_CEL_ID_TYPE,							// �^�C�v�A�C�R��
	WO_CEL_ID_MAX = WO_CEL_ID_TYPE - WO_CEL_ID_ARROW_LR + 1		// �ő�
};

// �Z���A�j�����\�[�XID
enum {
	WO_ANM_ID_ARROW_LR = CLACT_ID_COMMON,	// �y�[�W�J�[�\��
	WO_ANM_ID_ARROW_UD,						// ���X�g�J�[�\��
	WO_ANM_ID_CURSOR,						// �I���J�[�\��
	WO_ANM_ID_TYPE,							// �^�C�v�A�C�R��
	WO_ANM_ID_MAX = WO_ANM_ID_TYPE - WO_ANM_ID_ARROW_LR + 1		// �ő�
};


// �y�[�W�J�[�\����
#define	PAGE_CUR_L_PX	( 146 )
#define	PAGE_CUR_L_PY	( 8 )
// �y�[�W�J�[�\���E
#define	PAGE_CUR_R_PX	( 246 )
#define	PAGE_CUR_R_PY	( 8 )
// ���X�g�J�[�\����
#define	LIST_CUR_U_PX	( 196 )
#define	LIST_CUR_U_PY	( 20 )
// ���X�g�J�[�\����
#define	LIST_CUR_D_PX	( 196 )
#define	LIST_CUR_D_PY	( 140 )
// �I���J�[�\��
#define	SEL_CURSOR_PX	( 196 )
#define	SEL_CURSOR_PY	( 32 )
#define	SEL_CURSOR_SY	( 16 )
// ���ރA�C�R��
#define	KIND_ICON_PX	( 116 )
#define	KIND_ICON_PY	( 8 )
// �^�C�v�A�C�R���P
#define	TYPE_ICON1_PX	( 152 )
#define	TYPE_ICON1_PY	( 32 )
// �^�C�v�A�C�R���Q
#define	TYPE_ICON2_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON2_PY	( TYPE_ICON1_PY+16 )
// �^�C�v�A�C�R���R
#define	TYPE_ICON3_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON3_PY	( TYPE_ICON2_PY+16 )
// �^�C�v�A�C�R���S
#define	TYPE_ICON4_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON4_PY	( TYPE_ICON3_PY+16 )
// �^�C�v�A�C�R���T
#define	TYPE_ICON5_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON5_PY	( TYPE_ICON4_PY+16 )
// �^�C�v�A�C�R���U
#define	TYPE_ICON6_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON6_PY	( TYPE_ICON5_PY+16 )
// �^�C�v�A�C�R���V
#define	TYPE_ICON7_PX	( TYPE_ICON1_PX )
#define	TYPE_ICON7_PY	( TYPE_ICON6_PY+16 )


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void WO_DispInit( WO_WORK * wk );
static void WO_DispExit( WO_WORK * wk );

static void WO_VBlank( void * work );
static void WO_VramBankSet(void);
static void WO_BgSet( GF_BGL_INI * ini );
static void WO_BgExit( GF_BGL_INI * ini );
static void WO_BgGraphicSet( WO_WORK * wk );
static void WO_BmpWinSet( WO_WORK * wk );
static void WO_BmpWinExit( WO_WORK * wk );
static void WO_MsgCreate( WO_WORK * wk );
static void WO_MsgRelease( WO_WORK * wk );

static int WO_SeqFadeWait( WO_WORK * wk );
static int WO_SeqSelect( WO_WORK * wk );
static int WO_SeqFadeOutSet( WO_WORK * wk );
static int WO_SeqMsgWait( WO_WORK * wk );
static int WO_SeqYesNoPut( WO_WORK * wk );
static int WO_SeqYesNoWait( WO_WORK * wk );
static int WO_SeqWazaSet( WO_WORK * wk );
static int WO_SeqWazaDelSet( WO_WORK * wk );
static int WO_SeqDelCheck( WO_WORK * wk );
static int WO_SeqPstInit( WO_WORK * wk );
static int WO_SeqPstCall( WO_WORK * wk );
static int WO_SeqPstWait( WO_WORK * wk );

static void StrPut( WO_WORK * wk, u32 widx, u32 fnt, u32 col, u32 mode );
static void WO_PageChange( WO_WORK * wk );
static void WO_DefStrWrite( WO_WORK * wk );
static void WO_WazaListMake( WO_WORK * wk );
static void WO_WazaListExit( WO_WORK * wk );
static void CB_WazaListMove( BMPLIST_WORK * work, u32 param, u8 mode );
static void CB_WazaListWrite( BMPLIST_WORK * work, u32 param, u8 y );

static void BattleWazaParamPut( WO_WORK * wk, u32 prm );
static void ContestWazaParamPut( WO_WORK * wk, u32 prm );
static void WO_HeartPut( WO_WORK * wk, u16 waza );

static void WO_MsgMake( WO_WORK * wk, u32 id );
static void WO_TalkMsgSet( WO_WORK * wk, u32 id );
static BOOL WO_TalkMsgCallBack( MSG_PRINT_HEADER * mph, u16 value );
static u16 WO_SelWazaGet( WO_WORK * wk );
static u16 WO_DelWazaGet( WO_WORK * wk );
static u8 WO_WazaSetCheck( WO_WORK * wk );

static int WO_SetCheck_Yes( WO_WORK * wk );
static int WO_SetCheck_No( WO_WORK * wk );
static int WO_EndCheck_Yes( WO_WORK * wk );
static int WO_EndCheck_No( WO_WORK * wk );
static int WO_ChgCheck_Yes( WO_WORK * wk );
static int WO_ChgCheck_No( WO_WORK * wk );
static int WO_DelCheck_Yes( WO_WORK * wk );
static int WO_DelCheck_No( WO_WORK * wk );
static int WO_DelEnter_Yes( WO_WORK * wk );
static int WO_DelEnter_No( WO_WORK * wk );

static void WO_ObjInit( WO_WORK * wk );
static void WO_ObjFree( WO_WORK * wk );
static void WO_ObjAnm( WO_WORK * wk );
static void WO_TypeIconInit( WO_WORK * wk );
static void WO_TypeIconScroll( WO_WORK * wk, u16 old_scr, u16 new_scr );
static void WO_KindIconChange( WO_WORK * wk, u16 waza );
static void WO_SelCursorChange( WO_WORK * wk, u8 pos, u8 pal );
static void WO_PageCursorPut( WO_WORK * wk, u8 flg );
static void WO_ScrollCursorPut( WO_WORK * wk );
static void WO_ScrollCursorOff( WO_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// BMP�E�B���h�E�f�[�^
static const BMPWIN_DAT BmpWinData[] =
{
	{	// �u���������킴�v
		GF_BGL_FRAME1_M, WIN_STR_BATTLE_PX, WIN_STR_BATTLE_PY,
		WIN_STR_BATTLE_SX, WIN_STR_BATTLE_SY, WIN_STR_BATTLE_PAL, WIN_STR_BATTLE_CGX
	},
	{	// �u�R���e�X�g�킴�v
		GF_BGL_FRAME1_M, WIN_STR_CONTEST_PX, WIN_STR_CONTEST_PY,
		WIN_STR_CONTEST_SX, WIN_STR_CONTEST_SY, WIN_STR_CONTEST_PAL, WIN_STR_CONTEST_CGX
	},
	{	// �u�Ԃ�邢�v
		GF_BGL_FRAME1_M, WIN_STR_CLASS_PX, WIN_STR_CLASS_PY,
		WIN_STR_CLASS_SX, WIN_STR_CLASS_SY, WIN_STR_CLASS_PAL, WIN_STR_CLASS_CGX
	},
	{	// �u����傭�v
		GF_BGL_FRAME1_M, WIN_STR_ATTACK_PX, WIN_STR_ATTACK_PY,
		WIN_STR_ATTACK_SX, WIN_STR_ATTACK_SY, WIN_STR_ATTACK_PAL, WIN_STR_ATTACK_CGX
	},
	{	// �u�߂����イ�v
		GF_BGL_FRAME1_M, WIN_STR_HIT_PX, WIN_STR_HIT_PY,
		WIN_STR_HIT_SX, WIN_STR_HIT_SY, WIN_STR_HIT_PAL, WIN_STR_HIT_CGX
	},
	{	// �uPP�v
		GF_BGL_FRAME1_M, WIN_STR_PP_PX, WIN_STR_PP_PY,
		WIN_STR_PP_SX, WIN_STR_PP_SY, WIN_STR_PP_PAL, WIN_STR_PP_CGX
	},
	{	// �u�A�s�[���|�C���g�v
		GF_BGL_FRAME1_M, WIN_STR_APP_PX, WIN_STR_APP_PY,
		WIN_STR_APP_SX, WIN_STR_APP_SY, WIN_STR_APP_PAL, WIN_STR_APP_CGX
	},
	{	// �З͒l
		GF_BGL_FRAME1_M, WIN_PRM_ATTACK_PX, WIN_PRM_ATTACK_PY,
		WIN_PRM_ATTACK_SX, WIN_PRM_ATTACK_SY, WIN_PRM_ATTACK_PAL, WIN_PRM_ATTACK_CGX
	},
	{	// �����l
		GF_BGL_FRAME1_M, WIN_PRM_HIT_PX, WIN_PRM_HIT_PY,
		WIN_PRM_HIT_SX, WIN_PRM_HIT_SY, WIN_PRM_HIT_PAL, WIN_PRM_HIT_CGX
	},
	{	// PP�l
		GF_BGL_FRAME1_M, WIN_PRM_PP_PX, WIN_PRM_PP_PY,
		WIN_PRM_PP_SX, WIN_PRM_PP_SY, WIN_PRM_PP_PAL, WIN_PRM_PP_CGX
	},
	{	// �퓬����
		GF_BGL_FRAME1_M, WIN_BTL_INFO_PX, WIN_BTL_INFO_PY,
		WIN_BTL_INFO_SX, WIN_BTL_INFO_SY, WIN_BTL_INFO_PAL, WIN_BTL_INFO_CGX
	},
	{	// �R���e�X�g����
		GF_BGL_FRAME1_M, WIN_CON_INFO_PX, WIN_CON_INFO_PY,
		WIN_CON_INFO_SX, WIN_CON_INFO_SY, WIN_CON_INFO_PAL, WIN_CON_INFO_CGX
	},
	{	// ���b�Z�[�W�E�B���h�E
		GF_BGL_FRAME0_M, WIN_MSG_PX, WIN_MSG_PY,
		WIN_MSG_SX, WIN_MSG_SY, WIN_MSG_PAL, WIN_MSG_CGX,
	},
	{	// �Z���X�g
		GF_BGL_FRAME1_M, WIN_LIST_PX, WIN_LIST_PY,
		WIN_LIST_SX, WIN_LIST_SY, WIN_LIST_PAL, WIN_LIST_CGX
	},
	{	// �͂�/������
		GF_BGL_FRAME0_M, WIN_YESNO_PX, WIN_YESNO_PY,
		WIN_YESNO_SX, WIN_YESNO_SY, WIN_YESNO_PAL, WIN_YESNO_CGX
	}
};

// �Z���X�g�f�[�^�iBMP���X�g�j
static const BMPLIST_HEADER BagItemList = {
	NULL, CB_WazaListMove, CB_WazaListWrite, NULL,
	0, 7, 0,
	0, 0,			// ����X, �J�[�\��X
	0,				// �\��Y
	FBMP_COL_BLACK, FBMP_COL_NULL, FBMP_COL_BLK_SDW,
	0, 16,						// �����Ԋu�x
	BMPLIST_NO_SKIP, FONT_SYSTEM, 1,
	NULL,
};

// ���b�Z�[�W�e�[�u��
static const u32 MsgDataTbl[2][11] =
{
	{	// �Z����
		msg_waza_oboe_01,	// @0�Ɂ@�ǂ̂킴���@���ڂ�������H
		msg_waza_oboe_02,	// @1�@��  ���ڂ������܂����H
		msg_waza_oboe_03,	// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
		msg_waza_oboe_04,	// @0�́@�����炵���@@1���@���ڂ����I��"
		msg_waza_oboe_05,	// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
		msg_waza_oboe_06,	// �P�@�Q�́c�c�@�|�J���I���@@0�́@@1�� �����������@�`
		msg_waza_oboe_07,	// @0�́@�����炵�� @1���@���ڂ����I��
		msg_waza_oboe_08,	// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H"
		msg_waza_oboe_09,	// @0�́@@1���@���ڂ����Ɂ@��������I��
		msg_waza_oboe_10,	// @2�́@���ꂢ�Ɂ@�n�[�g�̃E���R���@�P�܂��@�������I��
		msg_waza_oboe_11,	// @0���@�킷�ꂳ���ā@��낵���ł��ˁH"
	},
	{	// �Z�v���o��
		msg_waza_omoi_01,	// @0�� �ǂ̂킴���@��������������H
		msg_waza_omoi_02,	// @1�@�� �����������܂����H
		msg_waza_omoi_03,	// @0�Ɂ@�킴�� ��������������̂��@������߂܂����H
		msg_waza_omoi_04,	// @0�́@�킷��Ă����@@1���@�������������I��
		msg_waza_omoi_05,	// @0�́@@1���@���������������c�c���@�������@�`
		msg_waza_omoi_06,	// �P�@�Q�́c�c�@�|�J���I���@@0�́@@1�� �����������@�`
		msg_waza_omoi_07,	// @0�́@�킷��Ă����@@1���@�������������I��
		msg_waza_omoi_08,	// ����ł́c�c�@@1���@�����������̂��@������߂܂����H
		msg_waza_omoi_09,	// @0�́@@1���@�������������Ɂ@��������I��
		msg_waza_omoi_10,	// @2�́@���ꂢ�� �n�[�g�̃E���R���@�P�܂��@�������I��
		msg_waza_omoi_11,	// @0���@�킷�ꂳ���ā@��낵���ł��ˁH"
	}
};

// �͂��E�����������e�[�u��
static const YESNO_FUNC YesNoFunc[] =
{
	{ WO_SetCheck_Yes, WO_SetCheck_No },	// @1�@��  ���ڂ������܂����H
	{ WO_EndCheck_Yes, WO_EndCheck_No },	// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
	{ WO_ChgCheck_Yes, WO_ChgCheck_No },	// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
	{ WO_DelCheck_Yes, WO_DelCheck_No },	// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H
	{ WO_DelEnter_Yes, WO_DelEnter_No },	// @0���@�킷�ꂳ���ā@��낵���ł��ˁH"
};

// �Z���A�N�^�[�f�[�^
static const TCATS_OBJECT_ADD_PARAM_S ClactParamTbl[] =
{
	{	// �y�[�W�J�[�\����
		PAGE_CUR_L_PX, PAGE_CUR_L_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_ARROW_LR, WO_PAL_ID_OBJ, WO_CEL_ID_ARROW_LR, WO_ANM_ID_ARROW_LR, 0, 0 },
		2, 0
	},
	{	// �y�[�W�J�[�\���E
		PAGE_CUR_R_PX, PAGE_CUR_R_PY, 0,
		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_ARROW_LR, WO_PAL_ID_OBJ, WO_CEL_ID_ARROW_LR, WO_ANM_ID_ARROW_LR, 0, 0 },
		2, 0
	},
	{	// ���X�g�J�[�\����
		LIST_CUR_U_PX, LIST_CUR_U_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_ARROW_UD, WO_PAL_ID_OBJ, WO_CEL_ID_ARROW_UD, WO_ANM_ID_ARROW_UD, 0, 0 },
		2, 0
	},
	{	// ���X�g�J�[�\����
		LIST_CUR_D_PX, LIST_CUR_D_PY, 0,
		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_ARROW_UD, WO_PAL_ID_OBJ, WO_CEL_ID_ARROW_UD, WO_ANM_ID_ARROW_UD, 0, 0 },
		2, 0
	},
	{	// �I���J�[�\��
		SEL_CURSOR_PX, SEL_CURSOR_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_CURSOR, WO_PAL_ID_OBJ, WO_CEL_ID_CURSOR, WO_ANM_ID_CURSOR, 0, 0 },
		2, 0
	},
	{	// ���ރA�C�R��
		KIND_ICON_PX, KIND_ICON_PY, 0,
		0, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_KIND, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���P
		TYPE_ICON1_PX, TYPE_ICON1_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE1, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���Q
		TYPE_ICON2_PX, TYPE_ICON2_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE2, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���R
		TYPE_ICON3_PX, TYPE_ICON3_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE3, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���S
		TYPE_ICON4_PX, TYPE_ICON4_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE4, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���T
		TYPE_ICON5_PX, TYPE_ICON5_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE5, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���U
		TYPE_ICON6_PX, TYPE_ICON6_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE6, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	},
	{	// �^�C�v�A�C�R���V
		TYPE_ICON7_PX, TYPE_ICON7_PY, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ WO_CHR_ID_TYPE7, WO_PAL_ID_OBJ, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE, 0, 0 },
		2, 0
	}
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
PROC_RESULT WazaOshieProc_Init( PROC * proc, int * seq )
{
	WO_WORK * wk;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WAZAOSHIE, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(WO_WORK), HEAPID_WAZAOSHIE );
	memset( wk, 0, sizeof(WO_WORK) );
	wk->dat = PROC_GetParentWork( proc );

	WO_DispInit( wk );

/*
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();				// HBlank��~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WAZAOSHIE );

	APP_WipeStart( APP_WIPE_IN, HEAPID_WAZAOSHIE );

	WO_VramBankSet();				// VRAM�ݒ�
	WO_BgSet( wk->bgl );			// BG�ݒ�
	WO_BgGraphicSet( wk );			// BG�O���t�B�b�N�Z�b�g

	WO_ObjInit( wk );

	WO_MsgCreate( wk );
	WO_BmpWinSet( wk );
	WO_PageChange( wk );

	WO_WazaListMake( wk );
*/


/*
	if( wk->dat->ret == WAZAOSHIE_RET_CHANGE ){
		WO_SelCursorChange( wk, wk->dat->pos, 1 );
		wk->next_seq = SEQ_DEL_CHECK;
	}else{
		WO_SelCursorChange( wk, wk->dat->pos, 0 );
		WO_MsgMake( wk, MSG_SEL_WAZA );
		StrPut( wk, WIN_MSG, FONT_TALK, WOFCOL_W_BLACK, STR_MODE_LEFT );
		wk->next_seq = SEQ_SELECT;
	}
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_MSG] );
*/
	WO_SelCursorChange( wk, wk->dat->pos, 0 );
	WO_MsgMake( wk, MSG_SEL_WAZA );
	StrPut( wk, WIN_MSG, FONT_TALK, WOFCOL_W_BLACK, STR_MODE_LEFT );
	wk->next_seq = SEQ_SELECT;
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_MSG] );

	WO_ScrollCursorPut( wk );

	sys_VBlankFuncChange( WO_VBlank, wk );	// VBlank�Z�b�g

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
PROC_RESULT WazaOshieProc_Main( PROC * proc, int * seq )
{
	WO_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_FADE_WAIT:		// �t�F�[�h�I���҂�
		*seq = WO_SeqFadeWait( wk );
		break;

	case SEQ_SELECT:		// �Z�Z���N�g
		*seq = WO_SeqSelect( wk );
		break;

	case SEQ_MSG_WAIT:		// ���b�Z�[�W�I���҂�
		*seq = WO_SeqMsgWait( wk );
		break;

	case SEQ_YESNO_PUT:		// �͂��E�������Z�b�g
		*seq = WO_SeqYesNoPut( wk );
		break;

	case SEQ_YESNO_WAIT:	// �͂��E�������I��҂�
		*seq = WO_SeqYesNoWait( wk );
		break;

	case SEQ_WAZA_SET:		// �Z�o��
		*seq = WO_SeqWazaSet( wk );
		break;

	case SEQ_WAZADEL_SET:	// �Y��ċZ�o��
		*seq = WO_SeqWazaDelSet( wk );
		break;

	case SEQ_DEL_CHECK:		// �Y�ꂳ����Z���`�F�b�N
		*seq = WO_SeqDelCheck( wk );
		break;

	case SEQ_FADEOUT_SET:	// �t�F�[�h�A�E�g�Z�b�g
		*seq = WO_SeqFadeOutSet( wk );
		break;

	case SEQ_END:			// �I��
		return PROC_RES_FINISH;

	case SEQ_PST_INIT:		// �X�e�[�^�X��ʂ�
		*seq = WO_SeqPstInit( wk );
		break;

	case SEQ_PST_CALL:		// �X�e�[�^�X��ʌĂяo��
		*seq = WO_SeqPstCall( wk );
		return PROC_RES_CONTINUE;

	case SEQ_PST_WAIT:		// �X�e�[�^�X��ʏI���҂�
		*seq = WO_SeqPstWait( wk );
		return PROC_RES_CONTINUE;
	}

	WO_ObjAnm( wk );
	CATS_Draw( wk->crp );

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
PROC_RESULT WazaOshieProc_End( PROC * proc, int * seq )
{
	WO_WORK * wk  = PROC_GetWork( proc );

/*
	WO_WazaListExit( wk );
	WO_BmpWinExit( wk );
	WO_BgExit( wk->bgl );		// BGL�폜

	WO_MsgRelease( wk );

	WO_ObjFree( wk );
	DellVramTransferManager();
*/

	WO_DispExit( wk );

	PROC_FreeWork( proc );					// ���[�N�J��

	sys_DeleteHeap( HEAPID_WAZAOSHIE );

	return PROC_RES_FINISH;
}


static void WO_DispInit( WO_WORK * wk )
{
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();				// HBlank��~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_WAZAOSHIE );

	APP_WipeStart( APP_WIPE_IN, HEAPID_WAZAOSHIE );

	WO_VramBankSet();				// VRAM�ݒ�
	WO_BgSet( wk->bgl );			// BG�ݒ�
	WO_BgGraphicSet( wk );			// BG�O���t�B�b�N�Z�b�g

	WO_ObjInit( wk );

	WO_MsgCreate( wk );
	WO_BmpWinSet( wk );
	WO_WazaListMake( wk );
	WO_PageChange( wk );

	sys_VBlankFuncChange( WO_VBlank, wk );	// VBlank�Z�b�g
}

static void WO_DispExit( WO_WORK * wk )
{
	WO_WazaListExit( wk );
	WO_BmpWinExit( wk );
	WO_BgExit( wk->bgl );		// BGL�폜

	WO_MsgRelease( wk );

	WO_ObjFree( wk );
	DellVramTransferManager();

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g
}


//--------------------------------------------------------------------------------------------
/**
 * VBlank�֐�
 *
 * @param	work	���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_VBlank( void * work )
{
	WO_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );

	// �Z���A�N�^�[
	DoVramTransferManager();	// Vram�]���}�l�[�W���[���s
	CATS_RenderOamTrans();
	
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
static void WO_VramBankSet(void)
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
static void WO_BgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	// WINDOW (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	// PARAM FONT (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	{	// PLATE (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_WAZAOSHIE );
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
static void WO_BgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 |
		GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_WAZAOSHIE, ini );
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
static void WO_BgGraphicSet( WO_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_WAZAOSHIE_GRA, NARC_waza_oshie_gra_waza_oboe_bg_NCGR,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_WAZAOSHIE );

	ArcUtil_ScrnSet(
		ARC_WAZAOSHIE_GRA, NARC_waza_oshie_gra_waza_oboe_NSCR,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_WAZAOSHIE );

	ArcUtil_PalSet(
		ARC_WAZAOSHIE_GRA, NARC_waza_oshie_gra_waza_oboe_NCLR,
		PALTYPE_MAIN_BG, 0, 0, HEAPID_WAZAOSHIE );

//	SystemFontPaletteLoad( PALTYPE_MAIN_BG, SYS_FONT_PAL * 32, HEAPID_BAG );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, WO_PAL_TALK_FONT * 32, HEAPID_WAZAOSHIE );

	// ���j���[�E�B���h�E�Z�b�g
	MenuWinGraphicSet(
		wk->bgl, GF_BGL_FRAME0_M, WO_MENU_WIN_CGX, WO_PAL_MENU_WIN, 0, HEAPID_WAZAOSHIE );
	// ��b�E�B���h�E�Z�b�g
	TalkWinGraphicSet(
		wk->bgl, GF_BGL_FRAME0_M, WO_TALK_WIN_CGX,
		WO_PAL_TALK_WIN, CONFIG_GetWindowType(wk->dat->cfg), HEAPID_WAZAOSHIE );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_BmpWinSet( WO_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &BmpWinData[i] );
		GF_BGL_BmpWinDataFill( &wk->win[i], 0 );
	}

	WO_DefStrWrite( wk );

	GF_BGL_BmpWinDataFill( &wk->win[WIN_MSG], 15 );
	BmpTalkWinWrite( &wk->win[WIN_MSG], WINDOW_TRANS_ON, WO_TALK_WIN_CGX, WO_PAL_TALK_WIN );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_BmpWinExit( WO_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->win[i] );
	}
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
static void WO_MsgCreate( WO_WORK * wk )
{
	wk->mman = MSGMAN_Create(
					MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_waza_oboe_dat, HEAPID_WAZAOSHIE );
	wk->wset = WORDSET_Create( HEAPID_WAZAOSHIE );

	wk->mbuf = STRBUF_Create( TMP_MSGBUF_SIZ, HEAPID_WAZAOSHIE );
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
static void WO_MsgRelease( WO_WORK * wk )
{
	MSGMAN_Delete( wk->mman );
	WORDSET_Delete( wk->wset );
	STRBUF_Delete( wk->mbuf );
}







static int WO_SeqFadeWait( WO_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		return wk->next_seq;
	}
	return SEQ_FADE_WAIT;
}

static int WO_SeqSelect( WO_WORK * wk )
{
	u32	ret;
	u16	scr, pos;

	if( sys.trg & (PAD_KEY_LEFT|PAD_KEY_RIGHT) ){
		Snd_SePlay( WO_SE_PAGE_MOVE );
		wk->dat->page ^= 1;
		WO_PageChange( wk );
		return SEQ_SELECT;
	}

	BmpListPosGet( wk->lw, &scr, &pos );
	ret = BmpListMain( wk->lw );
	BmpListPosGet( wk->lw, &wk->dat->scr, &wk->dat->pos );

	WO_TypeIconScroll( wk, scr, wk->dat->scr );

	if( wk->dat->pos != pos ){
		WO_SelCursorChange( wk, wk->dat->pos, 0 );
	}

	WO_ScrollCursorPut( wk );

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		Snd_SePlay( WO_SE_CANCEL );
		WO_SelCursorChange( wk, wk->dat->pos, 1 );
		WO_ScrollCursorOff( wk );
		WO_TalkMsgSet( wk, MSG_END_CHECK );
		wk->ynidx = YESNO_END_CHECK;
		wk->next_seq = SEQ_YESNO_PUT;
		return SEQ_MSG_WAIT;
	default:
		Snd_SePlay( WO_SE_DECIDE );
		WO_SelCursorChange( wk, wk->dat->pos, 1 );
		WO_ScrollCursorOff( wk );
		if( WO_WazaSetCheck( wk ) < 4 ){
			WO_TalkMsgSet( wk, MSG_SET_CHECK );
			wk->ynidx = YESNO_SET_CHECK;
			wk->next_seq = SEQ_YESNO_PUT;
		}else{
			WO_TalkMsgSet( wk, MSG_CHG_CHECK );
			wk->ynidx = YESNO_CHG_CHECK;
			wk->next_seq = SEQ_YESNO_PUT;
		}
		return SEQ_MSG_WAIT;
	}

	return SEQ_SELECT;
}

static int WO_SeqMsgWait( WO_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->midx ) == 0 ){
		return wk->next_seq;
	}
	return SEQ_MSG_WAIT;
}

static int WO_SeqYesNoPut( WO_WORK * wk )
{
	wk->mw = BmpYesNoSelectInit(
				wk->bgl, &BmpWinData[WIN_YESNO],
				WO_MENU_WIN_CGX, WO_PAL_MENU_WIN, HEAPID_WAZAOSHIE );
	return SEQ_YESNO_WAIT;
}

static int WO_SeqYesNoWait( WO_WORK * wk )
{
	switch( BmpYesNoSelectMain( wk->mw, HEAPID_WAZAOSHIE ) ){
	case 0:					// �͂�
		return YesNoFunc[wk->ynidx].yes( wk );

	case BMPMENU_CANCEL:	// ������ or �L�����Z��
		return YesNoFunc[wk->ynidx].no( wk );
	}

	return SEQ_YESNO_WAIT;
}

static int WO_SeqWazaSet( WO_WORK * wk )
{
	u32	buf;

	buf = WO_SelWazaGet( wk );
	PokeParaPut( wk->dat->pp, ID_PARA_waza1+wk->dat->del_pos, &buf );
	buf = 0;
	PokeParaPut( wk->dat->pp, ID_PARA_pp_count1+wk->dat->del_pos, &buf );
	buf = WT_PPMaxGet( WO_SelWazaGet(wk), 0 );
	PokeParaPut( wk->dat->pp, ID_PARA_pp1+wk->dat->del_pos, &buf );

	// sub item
/*
	{
		MyItem_SubItem( wk->dat->myitem, wk->dat->item, 1, HEAPID_POKELIST );
	}
*/

//	WO_TalkMsgSet( wk, MSG_SUB_ITEM );
//	wk->next_seq = SEQ_FADEOUT_SET;
	wk->dat->ret = WAZAOSHIE_RET_SET;
//	return SEQ_MSG_WAIT;
	return SEQ_FADEOUT_SET;
}

static int WO_SeqWazaDelSet( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_CHG_WAZA );
	wk->next_seq = SEQ_WAZA_SET;
	return SEQ_MSG_WAIT;
}

static int WO_SeqDelCheck( WO_WORK * wk )
{
	if( wk->dat->del_pos < 4 ){
		WO_TalkMsgSet( wk, MSG_DEL_ENTER );
		wk->ynidx = YESNO_DEL_ENTER;
	}else{
		WO_TalkMsgSet( wk, MSG_DEL_CHECK );
		wk->ynidx = YESNO_DEL_CHECK;
	}
	wk->next_seq = SEQ_YESNO_PUT;

	return SEQ_MSG_WAIT;
}

static int WO_SeqFadeOutSet( WO_WORK * wk )
{
	APP_WipeStart( APP_WIPE_OUT, HEAPID_WAZAOSHIE );
	wk->next_seq = SEQ_END;
	return SEQ_FADE_WAIT;
}





static void WO_PageChange( WO_WORK * wk )
{
	u16	waza;

	waza = WO_SelWazaGet( wk );

	if( wk->dat->page == WO_PAGE_BATTLE ){
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 0 );

		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_CONTEST] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_APP] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_CON_INFO] );

		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_BATTLE] );
/*
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_CLASS] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_ATTACK] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_HIT] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_PP] );
*/
		if( waza != WAZAOSHIE_TBL_MAX ){
			BattleWazaParamPut( wk, waza );
		}else{
			BattleWazaParamPut( wk, BMPLIST_CANCEL );
		}

//		CATS_ObjectEnableCap( wk->cap[WO_CLA_KIND], 1 );

	}else{
		GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, 256 );

		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_BATTLE] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_CLASS] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_ATTACK] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_HIT] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_PP] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_BTL_INFO] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_PRM_ATTACK] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_PRM_HIT] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_PRM_PP] );

		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_CONTEST] );
//		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_APP] );

		if( waza != WAZAOSHIE_TBL_MAX ){
			ContestWazaParamPut( wk, waza );
		}else{
			ContestWazaParamPut( wk, BMPLIST_CANCEL );
		}

		CATS_ObjectEnableCap( wk->cap[WO_CLA_KIND], 0 );
	}

	WO_TypeIconInit( wk );
}



static void StrPut( WO_WORK * wk, u32 widx, u32 fnt, u32 col, u32 mode )
{
	u8	siz;
	u8	wsx;
	u8	px;

	switch( mode ){
	case STR_MODE_LEFT:		// ���l��
		px = 0;
		break;
	case STR_MODE_RIGHT:	// �E�l��
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->mbuf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( &wk->win[widx] ) * 8;
		px  = wsx - siz;
		break;
	case STR_MODE_CENTER:	// ����
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->mbuf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( &wk->win[widx] ) * 8;
		px  = (wsx-siz)/2;
		break;
	}
	GF_STR_PrintColor( &wk->win[widx], fnt, wk->mbuf, px, 0, MSG_NO_PUT, col, NULL );
}

static void NumPrmSet( WO_WORK * wk, u32 msg_id, u32 num, u8 keta, u8 type )
{
	STRBUF * str;

	str = MSGMAN_AllocString( wk->mman, msg_id );
	WORDSET_RegisterNumber( wk->wset, 0, num, keta, type, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->mbuf, str );
	STRBUF_Delete( str );
}


//--------------------------------------------------------------------------------------------
/**
 * �Œ蕶����`��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_DefStrWrite( WO_WORK * wk )
{
	u32	siz;

	// �u���������킴�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_05, wk->mbuf );
	StrPut( wk, WIN_STR_BATTLE, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_CENTER );

	// �u�R���e�X�g�킴�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_07, wk->mbuf );
	StrPut( wk, WIN_STR_CONTEST, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_CENTER );

	// �u�Ԃ�邢�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_01, wk->mbuf );
	StrPut( wk, WIN_STR_CLASS, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_LEFT );

	// �u����傭�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_02, wk->mbuf );
	StrPut( wk, WIN_STR_ATTACK, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_LEFT );

	// �u�߂����イ�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_03, wk->mbuf );
	StrPut( wk, WIN_STR_HIT, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_LEFT );

	// �uPP�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_04, wk->mbuf );
	StrPut( wk, WIN_STR_PP, FONT_SYSTEM, WOFCOL_N_BLACK, STR_MODE_LEFT );

	// �u�A�s�[���|�C���g�v
	MSGMAN_GetString( wk->mman, msg_waza_oboe_01_06, wk->mbuf );
	StrPut( wk, WIN_STR_APP, FONT_SYSTEM, WOFCOL_N_WHITE, STR_MODE_CENTER );
}




static u32 WO_WazaTableNumGet( WO_WORK * wk )
{
	u32	i;

	for( i=0; i<256; i++ ){
		if( wk->dat->waza_tbl[i] == WAZAOSHIE_TBL_MAX ){
			break;
		}
	}
	return i;
}


static void WO_WazaListMake( WO_WORK * wk )
{
	MSGDATA_MANAGER * mman;
	BMPLIST_HEADER	lh;
	u32	i;

	wk->sel_max = (u8)WO_WazaTableNumGet( wk ) + 1;

	wk->ld = BMP_MENULIST_Create( wk->sel_max, HEAPID_WAZAOSHIE );

	mman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wazaname_dat, HEAPID_WAZAOSHIE );

	for( i=0; i<wk->sel_max; i++ ){
		if( wk->dat->waza_tbl[i] != WAZAOSHIE_TBL_MAX ){
			BMP_MENULIST_AddArchiveString(
				wk->ld, mman, wk->dat->waza_tbl[i], wk->dat->waza_tbl[i] );
		}else{
			BMP_MENULIST_AddArchiveString(
				wk->ld, wk->mman, msg_waza_oboe_01_11, BMPLIST_CANCEL );
			break;
		}
	}

	MSGMAN_Delete( mman );

	lh = BagItemList;
	lh.list  = wk->ld;
	lh.win   = &wk->win[WIN_LIST];
	lh.count = wk->sel_max;
	lh.work  = (void *)wk;
	wk->lw = BmpListSet( &lh, wk->dat->scr, wk->dat->pos, HEAPID_WAZAOSHIE );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_LIST] );
}

static void WO_WazaListExit( WO_WORK * wk )
{
	BmpListExit( wk->lw, &wk->dat->scr, &wk->dat->pos );
	BMP_MENULIST_Delete( wk->ld );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����X�g�R�[���o�b�N�֐��i�J�[�\���ړ����Ɓj
 *
 * @param	work	BMP���X�g�Őݒ肵�����[�N
 * @param	param	BMP���X�g�̃p�����[�^
 * @param	mode	�������� = 1
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CB_WazaListMove( BMPLIST_WORK * work, u32 param, u8 mode )
{
	WO_WORK * wk = (WO_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );

	if( mode != 1 ){
		Snd_SePlay( WO_SE_LIST_MOVE );
	}

	if( wk->dat->page == WO_PAGE_BATTLE ){
		BattleWazaParamPut( wk, param );
	}else{
		ContestWazaParamPut( wk, param );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����X�g�R�[���o�b�N�֐��i���\�����Ɓj
 *
 * @param	work	BMP���X�g�Őݒ肵�����[�N
 * @param	index	BMP���X�g���g�p���Ă���E�B���h�E�C���f�b�N�X
 * @param	param	BMP���X�g�̃p�����[�^
 * @param	y		Y���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CB_WazaListWrite( BMPLIST_WORK * work, u32 param, u8 y )
{
/*
	BAG_WORK * wk = (BAG_WORK *)BmpListParamGet( work, BMPLIST_ID_WORK );

	if( wk->irekae_flg == 1 && wk->irekae_param == param ){
		BmpListTmpColorChange( work, FBMP_COL_BLUE, FBMP_COL_NULL, FBMP_COL_BLU_SDW );
	}else{
		BmpListTmpColorChange( work, FBMP_COL_BLACK, FBMP_COL_NULL, FBMP_COL_BLK_SDW );
	}

	if( param != BMPLIST_RABEL && param != BMPLIST_CANCEL ){
		POCKET_DATA * pocket = &wk->dat->p_data[wk->dat->p_now];

		if( wk->irekae_flg == 1 && wk->irekae_param == param ){
			Bag_ItemListNumPut( wk, pocket->item[param].no, y, BAGCOL_N_BLUE );
		}else{
			Bag_ItemListNumPut( wk, pocket->item[param].no, y, BAGCOL_N_BLACK );
		}
	}
*/
}



static void BattleWazaParamPut( WO_WORK * wk, u32 prm )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_BTL_INFO], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_PRM_ATTACK], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_PRM_HIT], 0 );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_PRM_PP], 0 );

	CATS_ObjectEnableCap( wk->cap[WO_CLA_KIND], 0 );

	if( prm != BMPLIST_CANCEL ){
		MSGDATA_MANAGER * mman;
		u32	tmp;

		// �З�
		tmp = WT_WazaDataParaGet( prm, ID_WTD_damage );
		if( tmp <= 1 ){
			MSGMAN_GetString( wk->mman, msg_waza_oboe_01_12, wk->mbuf );
		}else{
			NumPrmSet( wk, msg_waza_oboe_01_08, tmp, 3, NUM_MODE_LEFT );
		}
		StrPut( wk, WIN_PRM_ATTACK, FONT_SYSTEM, WOFCOL_N_BLACK, STR_MODE_RIGHT );

		// ����
		tmp = WT_WazaDataParaGet( prm, ID_WTD_hitprobability );
		if( tmp == 0 ){
			MSGMAN_GetString( wk->mman, msg_waza_oboe_01_12, wk->mbuf );
		}else{
			NumPrmSet( wk, msg_waza_oboe_01_09, tmp, 3, NUM_MODE_LEFT );
		}
		StrPut( wk, WIN_PRM_HIT, FONT_SYSTEM, WOFCOL_N_BLACK, STR_MODE_RIGHT );

		// PP/MPP
		tmp = WT_PPMaxGet( prm, 0 );
		NumPrmSet( wk, msg_waza_oboe_01_10, tmp, 2, NUM_MODE_LEFT );
		StrPut( wk, WIN_PRM_PP, FONT_SYSTEM, WOFCOL_N_BLACK, STR_MODE_RIGHT );

		// ����
		mman = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazainfo_dat, HEAPID_WAZAOSHIE );
		MSGMAN_GetString( mman, prm, wk->mbuf );
		StrPut( wk, WIN_BTL_INFO, FONT_SYSTEM, WOFCOL_N_BLACK, STR_MODE_LEFT );
		MSGMAN_Delete( mman );

		WO_KindIconChange( wk, prm );
		CATS_ObjectEnableCap( wk->cap[WO_CLA_KIND], 1 );

		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_CLASS] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_ATTACK] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_HIT] );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_PP] );
	}else{
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_CLASS] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_ATTACK] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_HIT] );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_PP] );
	}

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_BTL_INFO] );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_PRM_ATTACK] );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_PRM_HIT] );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_PRM_PP] );
}

static void ContestWazaParamPut( WO_WORK * wk, u32 prm )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_CON_INFO], 0 );

	if( prm != BMPLIST_CANCEL ){
		MSGDATA_MANAGER * mman;
		u32	ap_no;
		u32	msg_id;

		ap_no  = WT_WazaDataParaGet( prm, ID_WTD_ap_no );
		msg_id = ConTool_GetListAPSetumeiMsgID( ap_no );

		mman = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_wazaexplain_dat, HEAPID_WAZAOSHIE );

		MSGMAN_GetString( mman, msg_id, wk->mbuf );
		GF_STR_PrintColor(
			&wk->win[WIN_CON_INFO], FONT_SYSTEM,
			wk->mbuf, 0, 0, MSG_NO_PUT, WOFCOL_N_BLACK, NULL );

		MSGMAN_Delete( mman );

		WO_HeartPut( wk, (u16)prm );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_STR_APP] );
	}else{
		WO_HeartPut( wk, WAZAOSHIE_TBL_MAX );
		GF_BGL_BmpWinOffVReq( &wk->win[WIN_STR_APP] );
	}

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_CON_INFO] );
}


static void WO_HeartPutMain( WO_WORK * wk, u16 chr, u8 num )
{
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr,
		HEART_PUT_PX+num*2, HEART_PUT_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+1,
		HEART_PUT_PX+num*2+1, HEART_PUT_PY, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+32,
		HEART_PUT_PX+num*2, HEART_PUT_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, chr+33,
		HEART_PUT_PX+num*2+1, HEART_PUT_PY+1, 1, 1, GF_BGL_SCRWRT_PALNL );
}

static void WO_HeartInit( WO_WORK * wk )
{
	u16	i;

	for( i=0; i<HEART_MAX; i++ ){
		WO_HeartPutMain( wk, HEART_NONE_CHR, i );
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}

static void WO_HeartPut( WO_WORK * wk, u16 waza )
{
	u32	ap_no;
	u16	i;
	s8	point;

	WO_HeartInit( wk );

	if( waza != WAZAOSHIE_TBL_MAX ){
		ap_no = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
		point = ConTool_GetAPWaza_App( ap_no ) / APP_APPEAL_ICON_ONE_POINT;
		for( i=0; i<point; i++ ){
			WO_HeartPutMain( wk, HEART_POINT_CHR, i );
		}
	}
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
}








static void WO_MsgMake( WO_WORK * wk, u32 id )
{
	STRBUF * str;

	switch( id ){
	case MSG_SEL_WAZA:	// @0�Ɂ@�ǂ̂킴���@���ڂ�������H
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		break;
	case MSG_SET_CHECK:	// @1�@��  ���ڂ������܂����H
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_END_CHECK:	// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		break;
	case MSG_SET_WAZA:	// @0�́@�����炵���@@1���@���ڂ����I��"
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_CHG_CHECK:	// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_DEL_WAZA:	// �P�@�Q�́c�c�@�|�J���I���@@0�́@@1�� �����������@�`
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		WORDSET_RegisterWazaName( wk->wset, 1, WO_DelWazaGet( wk ) );
		break;
	case MSG_CHG_WAZA:	// @0�́@�����炵�� @1���@���ڂ����I��
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_DEL_CHECK:	// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_CANCEL:	// @0�́@@1���@���ڂ����Ɂ@��������I��
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(wk->dat->pp) );
		WORDSET_RegisterWazaName( wk->wset, 1, WO_SelWazaGet( wk ) );
		break;
	case MSG_SUB_ITEM:	// @2�́@���ꂢ�Ɂ@�n�[�g�̃E���R���@�P�܂��@�������I��
		WORDSET_RegisterPlayerName( wk->wset, 2, wk->dat->myst );
		break;
	case MSG_DEL_ENTER:	// @0���@�킷�ꂳ���ā@��낵���ł��ˁH
		WORDSET_RegisterWazaName( wk->wset, 0, WO_DelWazaGet( wk ) );
		break;
	}

	str = MSGMAN_AllocString( wk->mman, MsgDataTbl[wk->dat->mode][id] );
	WORDSET_ExpandStr( wk->wset, wk->mbuf, str );
	STRBUF_Delete( str );
}

static u16 WO_SelWazaGet( WO_WORK * wk )
{
	return wk->dat->waza_tbl[ wk->dat->scr + wk->dat->pos ];
}

static u16 WO_DelWazaGet( WO_WORK * wk )
{
	return (u16)PokeParaGet( wk->dat->pp, ID_PARA_waza1+wk->dat->del_pos, NULL );
}


static void WO_TalkMsgSet( WO_WORK * wk, u32 id )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_MSG], 15 );

	WO_MsgMake( wk, id );
	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );
	wk->midx = GF_STR_PrintSimple(
				&wk->win[WIN_MSG], FONT_TALK, wk->mbuf,
				0, 0, CONFIG_GetMsgPrintSpeed(wk->dat->cfg), WO_TalkMsgCallBack );
}

//--------------------------------------------------------------------------------------------
/**
 * ��b�i���j���b�Z�[�W�R�[���o�b�N
 *
 * @param	mph		���b�Z�[�W�`��f�[�^
 * @param	value	�R�[���o�b�N�i���o
 *
 * @retval	"TRUE = �҂�"
 * @retval	"FALSE = ���̏�����"
 */
//--------------------------------------------------------------------------------------------
static BOOL WO_TalkMsgCallBack( MSG_PRINT_HEADER * mph, u16 value )
{
	switch( value ){
	case 1:		// SE�I���҂�
		return Snd_SePlayCheckAll();

	case 2:		// ME�I���҂�
		return Snd_MePlayCheckBgmPlay();
/*
	case 2:
		Snd_MePlay( SEQ_FANFA5 );
		break;
*/
	case 3:		// "�|�J��"
		Snd_SePlay( SEQ_SE_DP_KON );
		break;

	case 4:		// "���ڂ���"
		Snd_MePlay( SEQ_FANFA1 );
		break;

	case 5:		// "�|�J��"��SE�I���҂�
		return Snd_SePlayCheck( SEQ_SE_DP_KON );
	}

	return FALSE;
}


static u8 WO_WazaSetCheck( WO_WORK * wk )
{
	u8	i;

	for( i=0; i<4; i++ ){
		if( PokeParaGet( wk->dat->pp, ID_PARA_waza1+i, NULL ) == 0 ){
			break;
		}
	}
	return i;
}



	

// @1�@��  ���ڂ������܂����H
static int WO_SetCheck_Yes( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_SET_WAZA );
	wk->dat->del_pos = WO_WazaSetCheck( wk );
	wk->next_seq = SEQ_WAZA_SET;
	return SEQ_MSG_WAIT;
}
static int WO_SetCheck_No( WO_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_MSG], 15 );
	WO_MsgMake( wk, MSG_SEL_WAZA );
	StrPut( wk, WIN_MSG, FONT_TALK, WOFCOL_W_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_MSG] );
	WO_SelCursorChange( wk, wk->dat->pos, 0 );
	WO_PageCursorPut( wk, 1 );
	return SEQ_SELECT;
}

// @0�Ɂ@�킴��  ���ڂ�������̂��@������߂܂����H
static int WO_EndCheck_Yes( WO_WORK * wk )
{
//	WO_TalkMsgSet( wk, MSG_CANCEL );
//	wk->next_seq = SEQ_FADEOUT_SET;
	wk->dat->ret = WAZAOSHIE_RET_CANCEL;
	return SEQ_FADEOUT_SET;
}
static int WO_EndCheck_No( WO_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_MSG], 15 );
	WO_MsgMake( wk, MSG_SEL_WAZA );
	StrPut( wk, WIN_MSG, FONT_TALK, WOFCOL_W_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_MSG] );
	WO_SelCursorChange( wk, wk->dat->pos, 0 );
	WO_PageCursorPut( wk, 1 );
	return SEQ_SELECT;
}

// @0�́@�����炵���@@1���@���ڂ������c�c���@�������@�`
static int WO_ChgCheck_Yes( WO_WORK * wk )
{
//	wk->dat->ret = WAZAOSHIE_RET_CHANGE;
//	return SEQ_FADEOUT_SET;
	wk->next_seq = SEQ_PST_INIT;
	return SEQ_FADE_WAIT;
}
static int WO_ChgCheck_No( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_DEL_CHECK );
	wk->ynidx = YESNO_DEL_CHECK;
	wk->next_seq = SEQ_YESNO_PUT;
	return SEQ_MSG_WAIT;
}

// ����ł́c�c�@@1���@���ڂ���̂��@������߂܂����H
static int WO_DelCheck_Yes( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_CANCEL );
	wk->next_seq = SEQ_FADEOUT_SET;
	wk->dat->ret = WAZAOSHIE_RET_CANCEL;
	return SEQ_MSG_WAIT;
}
static int WO_DelCheck_No( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_CHG_CHECK );
	wk->ynidx = YESNO_CHG_CHECK;
	wk->next_seq = SEQ_YESNO_PUT;
	return SEQ_MSG_WAIT;
}

// @0���@�킷�ꂳ���ā@��낵���ł��ˁH
static int WO_DelEnter_Yes( WO_WORK * wk )
{
	WO_TalkMsgSet( wk, MSG_DEL_WAZA );
	wk->next_seq = SEQ_WAZADEL_SET;
	return SEQ_MSG_WAIT;
}
static int WO_DelEnter_No( WO_WORK * wk )
{
//	wk->dat->ret = WAZAOSHIE_RET_CHANGE;
//	return SEQ_FADEOUT_SET;
	wk->next_seq = SEQ_PST_INIT;
	return SEQ_FADE_WAIT;
}












//--------------------------------------------------------------------------------------------
/**
 * ���\�[�X�}�l�[�W���[������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_ClactResManInit( WO_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		WO_CHR_ID_MAX, WO_PAL_ID_MAX, WO_CEL_ID_MAX, WO_ANM_ID_MAX, 0, 0
	};

	initVramTransferManagerHeap( 64, HEAPID_WAZAOSHIE );

	wk->csp = CATS_AllocMemory( HEAPID_WAZAOSHIE );
	wk->crp = CATS_ResourceCreate( wk->csp );
	{
		TCATS_OAM_INIT	coi = {
			0, 128,
			0, 32,
			0, 128,
			0, 32,
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			WO_CLA_MAX,
			1024*128,
			1024*16,
			GX_OBJVRAMMODE_CHAR_1D_32K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit( wk->csp, &coi, &ccmm, 32 );
	}
	CATS_ClactSetInit( wk->csp, wk->crp, WO_CLA_MAX );
	CATS_ResourceManagerInit( wk->csp, wk->crp, &crnl );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}


//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_ObjFree( WO_WORK * wk )
{
	u32	i;

	for( i=0; i<WO_CLA_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	CATS_ResourceDestructor_S( wk->csp, wk->crp );
	CATS_FreeMemory( wk->csp );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�A�j��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_ObjAnm( WO_WORK * wk )
{
	u16	i;

	for( i=0; i<WO_CLA_MAX; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃��\�[�X�ݒ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_ResourceLoad( WO_WORK * wk )
{
	u32	i;

	// �L����
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_page_cur_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, WO_CHR_ID_ARROW_LR );
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_scroll_cur_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, WO_CHR_ID_ARROW_UD );
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_list_cur_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, WO_CHR_ID_CURSOR );
	for( i=WO_CHR_ID_TYPE1; i<=WO_CHR_ID_TYPE7; i++ ){
		WazaTypeIcon_CharResourceLoad( wk->csp, wk->crp, NNS_G2D_VRAM_TYPE_2DMAIN, 0, i );
	}
	WazaKindIcon_CharResourceLoad(wk->csp,wk->crp,NNS_G2D_VRAM_TYPE_2DMAIN,0,WO_CHR_ID_KIND);

	// �p���b�g
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_waza_oboe_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, WO_PAL_ID_OBJ );
	WazaTypeIcon_PlttResourceLoad( wk->csp, wk->crp, NNS_G2D_VRAM_TYPE_2DMAIN, WO_PAL_ID_TYPE );

	// �Z��
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_page_cur_NCER, 0, WO_CEL_ID_ARROW_LR );
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_scroll_cur_NCER, 0, WO_CEL_ID_ARROW_UD );
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_list_cur_NCER, 0, WO_CEL_ID_CURSOR );

	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_page_cur_NANR, 0, WO_ANM_ID_ARROW_LR );
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_scroll_cur_NANR, 0, WO_ANM_ID_ARROW_UD );
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_WAZAOSHIE_GRA,
		NARC_waza_oshie_gra_list_cur_NANR, 0, WO_ANM_ID_CURSOR );

	WazaTypeIcon_CellAnmResourceLoad( wk->csp, wk->crp, WO_CEL_ID_TYPE, WO_ANM_ID_TYPE );
}


//--------------------------------------------------------------------------------------------
/**
 * �^�C�v�A�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	waza	�Z�ԍ�
 * @param	num		�A�C�R���ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_TypeIconChange( WO_WORK * wk, u16 waza, u16 num )
{
	u32	type;
	
	if( wk->dat->page == WO_PAGE_BATTLE ){
		type = WT_WazaDataParaGet( waza, ID_WTD_wazatype );
	}else{
		type = WT_WazaDataParaGet( waza, ID_WTD_contype ) + ICONTYPE_STYLE;
	}

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaTypeIcon_ArcIDGet(),
		WazaTypeIcon_CgrIDGet(type), WAZATYPEICON_COMP_CHAR, WO_CHR_ID_TYPE1+num );

	CATS_ObjectPaletteSetCap( wk->cap[WO_CLA_TYPE1+num], WazaTypeIcon_PlttOffsetGet(type)+2 );
}

static void WO_TypeIconInit( WO_WORK * wk )
{
	u32	i;

	for( i=0; i<7; i++ ){
		CATS_ObjectPosSetCap(
			wk->cap[WO_CLA_TYPE1+i], TYPE_ICON1_PX, TYPE_ICON1_PY+SEL_CURSOR_SY*i );
		if( wk->dat->scr + i >= wk->sel_max-1 ){
			CATS_ObjectEnableCap( wk->cap[WO_CLA_TYPE1+i], 0 );
		}else{
			CATS_ObjectEnableCap( wk->cap[WO_CLA_TYPE1+i], 1 );
			WO_TypeIconChange( wk, wk->dat->waza_tbl[wk->dat->scr+i], i );
		}
	}
}

static void WO_TypeIconScroll( WO_WORK * wk, u16 old_scr, u16 new_scr )
{
	u32	i;
	s16	x, y;

	if( old_scr < new_scr ){
		for( i=0; i<7; i++ ){
			CATS_ObjectPosGetCap( wk->cap[WO_CLA_TYPE1+i], &x, &y );
			if( y == TYPE_ICON1_PY ){
				y = TYPE_ICON7_PY;
				if( wk->dat->waza_tbl[new_scr+6] != WAZAOSHIE_TBL_MAX ){
					WO_TypeIconChange( wk, wk->dat->waza_tbl[new_scr+6], i );
				}
			}else{
				y -= SEL_CURSOR_SY;
			}
			CATS_ObjectPosSetCap( wk->cap[WO_CLA_TYPE1+i], x, y );
		}
	}else if( old_scr > new_scr ){
		for( i=0; i<7; i++ ){
			CATS_ObjectPosGetCap( wk->cap[WO_CLA_TYPE1+i], &x, &y );
			if( y == TYPE_ICON7_PY ){
				y = TYPE_ICON1_PY;
				if( wk->dat->waza_tbl[new_scr] != WAZAOSHIE_TBL_MAX ){
					WO_TypeIconChange( wk, wk->dat->waza_tbl[new_scr], i );
				}
			}else{
				y += SEL_CURSOR_SY;
			}
			CATS_ObjectPosSetCap( wk->cap[WO_CLA_TYPE1+i], x, y );
		}
	}else{
		return;
	}

	for( i=0; i<7; i++ ){
		CATS_ObjectPosGetCap( wk->cap[WO_CLA_TYPE1+i], &x, &y );
		y = ( y - TYPE_ICON1_PY ) / SEL_CURSOR_SY;
		if( new_scr + y >= wk->sel_max-1 ){
			CATS_ObjectEnableCap( wk->cap[WO_CLA_TYPE1+i], 0 );
		}else{
			CATS_ObjectEnableCap( wk->cap[WO_CLA_TYPE1+i], 1 );
		}
	}
}



//--------------------------------------------------------------------------------------------
/**
 * ���ރA�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	waza	�Z�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void WO_KindIconChange( WO_WORK * wk, u16 waza )
{
	u32	kind = WT_WazaDataParaGet( waza, ID_WTD_kind );

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaKindIcon_ArcIDGet(),
		WazaKindIcon_CgrIDGet(kind), WAZAKINDICON_COMP_CHAR, WO_CHR_ID_KIND );

	CATS_ObjectPaletteSetCap( wk->cap[WO_CLA_KIND], WazaKindIcon_PlttOffsetGet(kind)+2 );
}


static void WO_ObjInit( WO_WORK * wk )
{
	u32	i;

	WO_ClactResManInit( wk );
	WO_ResourceLoad( wk );

	for( i=0; i<WO_CLA_MAX; i++ ){
		wk->cap[i] = CATS_ObjectAdd_S( wk->csp, wk->crp, &ClactParamTbl[i] );
	}
}


static void WO_SelCursorChange( WO_WORK * wk, u8 pos, u8 pal )
{
	CATS_ObjectPosSetCap(
		wk->cap[WO_CLA_CURSOR], SEL_CURSOR_PX, SEL_CURSOR_PY+SEL_CURSOR_SY*pos );
	CATS_ObjectPaletteSetCap( wk->cap[WO_CLA_CURSOR], pal );
}


static void WO_PageCursorPut( WO_WORK * wk, u8 flg )
{
	CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_L], flg );
	CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_R], flg );
}


static void WO_ScrollCursorPut( WO_WORK * wk )
{
	if( wk->dat->scr != 0 ){
		CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_U], 1 );
	}else{
		CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_U], 0 );
	}
	if( wk->dat->scr + 7 < wk->sel_max ){
		CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_D], 1 );
	}else{
		CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_D], 0 );
	}
}


static void WO_ScrollCursorOff( WO_WORK * wk )
{
	CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_U], 0 );
	CATS_ObjectEnableCap( wk->cap[WO_CLA_ARROW_D], 0 );
}







static int WO_SeqPstInit( WO_WORK * wk )
{
	APP_WipeStart( APP_WIPE_OUT, HEAPID_WAZAOSHIE );
	wk->next_seq = SEQ_PST_CALL;
	return SEQ_FADE_WAIT;
}

static int WO_SeqPstCall( WO_WORK * wk )
{
	u8 page[] = {
		PST_PAGE_B_SKILL,		// �u���������킴�v
		PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
		PST_PAGE_MAX
	};

	WO_DispExit( wk );

	wk->psd.ppd  = wk->dat->pp;
	wk->psd.cfg  = wk->dat->cfg;
	wk->psd.ppt  = PST_PP_TYPE_POKEPARAM;
	wk->psd.pos  = 0;
	wk->psd.max  = 1;
	wk->psd.waza = WO_SelWazaGet( wk );
	wk->psd.mode = PST_MODE_WAZAADD;
	wk->psd.ev_contest = 1;
	wk->psd.perap = NULL;
	PokeStatus_PageSet( &wk->psd, page );

	wk->subProc = PROC_Create( &PokeStatusProcData, &wk->psd, HEAPID_WAZAOSHIE );
	return SEQ_PST_WAIT;
}

static int WO_SeqPstWait( WO_WORK * wk )
{
	if( ProcMain( wk->subProc ) ){
        PROC_Delete( wk->subProc );
		WO_DispInit( wk );
		WO_SelCursorChange( wk, wk->dat->pos, 1 );
		WO_PageCursorPut( wk, 0 );
		WO_ScrollCursorOff( wk );
		wk->dat->del_pos = wk->psd.ret_sel;
		wk->next_seq = SEQ_DEL_CHECK;
		return SEQ_FADE_WAIT;
	}

	return SEQ_PST_WAIT;
}

