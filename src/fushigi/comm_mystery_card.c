//============================================================================================
/**
 * @file	comm_fushigi_card.c
 * @bfief	�ӂ����ȁ@��������� �J�[�h�̊m�F���
 * @author	Satoshi Mitsuhara
 * @date	06.05.19
 *
 * $Id: comm_mystery_card.c,v 1.54 2006/08/07 11:48:10 mitsuhara Exp $
 */
//============================================================================================

// [Main]
// BG0	���b�Z�[�W�E�B���h�E
// BG1	�J�[�h�w�i
// BG2	��O�̃��j���[
// BG3	��Ԍ��̊i�q�͗l

// [Sub]
// �i�q�͗l�̂�


#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/wipe.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "system/laster.h"

#include "savedata/fushigi_data.h"
#include "savedata/config.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "poketool/pokeicon.h"

#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"
#include "comm_mystery_func.h"
#include "mysterylib.h"
#include "mystery.naix"

#include "msgdata/msg.naix"
#include "msgdata/msg_mystery.h"
//#include "nitrocrypto/crypto.h"

void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );

#define MYSTERYCARD_WIN_MAX	20

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *p, int heapid);


//============================================================================================
//	�萔��`
//============================================================================================
#define MYSTERYCARD_HEADSIZE	0x20000

#define TWAKU_PALETTE_NUMBER	10
#define LATTICEBG_PALNO		11
#define OSUSOWAKE_PALNO		12
#define WAKU_PALETTE_NUMBER1	13
#define WAKU_PALETTE_NUMBER2	14
#define	FONT_PALNO_NORMAL	15	/* �m�[�}���p���b�g */
#define	MYSTERYCARD_BLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 0))
#define	MYSTERYCARD_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))
#define	MYSTERYCARD_OWHITE	(GF_PRINTCOLOR_MAKE(14, 15, 0))

#define MYSTERYCARD_RED		(GF_PRINTCOLOR_MAKE( 3,  4, 0))
#define MYSTERYCARD_BLUE	(GF_PRINTCOLOR_MAKE( 5,  6, 0))

#define LATTICEBG_CHARBASE	(0)


#define MYSTERYCARD_FRAMECHR1	1
#define MYSTERYCARD_FRAMECHR2	(MYSTERYCARD_FRAMECHR1 + MENU_WIN_CGX_SIZ)
#define MYSTERYCARD_TFRAMECHR	(MYSTERYCARD_FRAMECHR2 + MENU_WIN_CGX_SIZ)
#define MYSTERYCARD_CHBASE	(MYSTERYCARD_TFRAMECHR + TALK_WIN_CGX_SIZ)

/* �O���t�B�b�N�X�̕\�� */
#define MYSTERYCARD_FRONT	0
#define MYSTERYCARD_BACK	1
#define MYSTERYCARD_MENU	2
#define MYSTERYCARD_SEND	3
#define WHITE			1
#define BLACK			2

/* ���j���[�E�B���h�E�̃f�[�^������ꏊ */
#define MYSTERYCARD_INDEX_MENU	7
#define MYSTERYCARD_MENU_BASE	640

/* �G���g������\�����Ă���E�B���h�E�̃C���f�b�N�X */
#define MYSTERYCARD_ENTRY_COUNT	15
/* �G���g���[��\�����Ă���E�B���h�E�̃C���f�b�N�X */
#define MYSTERYCARD_ENTRY_LIST	16
/* �Ō�̃��b�Z�[�W�E�B���h�E */
#define MYSTERYCARD_INDEX_LASTWIN	17


/* �������킯�ł���ő�l�� */
#define MYSTERYCARD_OSUSOWAKE_MAX	4
/* �������킯���郁���o�[���̕\���� */
#define MYSTERYCARD_OSUSOWAKE_HEIGHT	24

/* �\������|�P�����̃A�C�R���� */



// �|�P�����A�C�R�����n�܂�VRAM��ł̃I�t�Z�b�g
#define POKEICON_VRAM_OFFSET ( 0x64 )
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)
// �|�P�����A�C�R���̃p���b�g��]������I�t�Z�b�g
#define POKEICON_PAL_OFFSET				(  3 )

//** CharManager PlttManager�p **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)


// �J�[�h���߂��铮��p
typedef struct {
  u16 sbuff[2][HW_LCD_HEIGHT*4];
  LASTER_SYS_PTR laster_ptr;
  TCB_PTR tcb_ptr;
  fx32 speed, accel;
  BOOL do_run;
  BOOL mode;		// true: close   false: open
} CARDTURN;


typedef struct {
  int heapid;

  MYSTERYGIFT_WORK gwk;
  
  GF_BGL_INI *bgl;
  WORDSET *word;	       			// �P�ꃂ�W���[�����䃏�[�N�ւ̃|�C���^
  MSGDATA_MANAGER *msgman;	    		// MSG�f�[�^�}�l�[�W���ւ̃|�C���^

  GF_BGL_BMPWIN	win[MYSTERYCARD_WIN_MAX];	// ���b�Z�[�W��\������E�B���h�E
  int chbase[MYSTERYCARD_WIN_MAX];

  int nowbase;
  void *tbl;

  FUSHIGI_DATA *fdata;				// �ӂ����f�[�^��ǂ񂾏ꏊ
  SAVEDATA *sv;
  CONFIG *cfg;
  int win_type;
  LOAD_RESULT load_result;
  GIFT_CARD *card[GIFT_CARD_MAX];		// �J�[�h�f�[�^�ւ̃|�C���^

  int disp_card;				// �\���ΏۂɂȂ��Ă���J�[�h�ԍ�
  int disp_side;				// �\�����Ă����

  BMPLIST_WORK *lw;				// ���j���[
  BMP_MENULIST_DATA *bmd;

  GF_BGL_BMPWIN	msgwin;				// ���b�Z�[�W��\������E�B���h�E
  GF_BGL_BMPWIN	menuwin;			// ���j���[��\������E�B���h�E
  int menu_index;

  int entry;					// �������킯�Ɍq���Ă����l�̐�
  u32 tranerid[MYSTERYCARD_OSUSOWAKE_MAX];	// �O��q�����Ă����g���[�i�[�h�c

  MYSTATUS *my[MYSTERYCARD_OSUSOWAKE_MAX+1];	// �O��q�����Ă����g���[�i�[�h�c
  int worder[MYSTERYCARD_OSUSOWAKE_MAX+1];

  int prev_connect;				// ���������܂Ōq���Ă����l��
  int sync_wait;
  void (*wait_end_func)(void *p);
  int write_index;
  
  int next_seq;

  // �Z���A�N�^�[�֘A
  CLACT_SET_PTR	clactSet;				// �Z���A�N�^�[�Z�b�g 
  CLACT_U_EASYRENDER_DATA renddata;			// �ȈՃ����_�[�f�[�^
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// ���\�[�X�}�l�[�W��
  CLACT_U_RES_OBJ_PTR resObjTbl[CLACT_U_RES_MAX];	// ���\�[�X�I�u�W�F�e�[�u��
  CLACT_HEADER clActHeaderMain;
  // �{�^���A�C�R���̔w�i
  CLACT_WORK_PTR ibase[2];

  // �|�P�����A�C�R���̕\��
  CLACT_WORK_PTR pokeicon[3];

  //  CRYPTORC4Context rc4context;
  //  GIFT_BEACON_CRC gbc;				// �r�[�R���f�[�^
  GIFT_DATA comm_data;					// �Í������ꂽ�f�[�^

  CARDTURN cturn;					// �J�[�h�߂���p
  void (*func_hook)(void *);				// �O���t�@���N�V�������s�p

  int select_icon;
  void *time_icon;

  
} MYSTERYCARD_WORK;


enum {
  MYSTERYCARD_READ_SAVEDATA = 0,	/* �Z�[�u�f�[�^�̓ǂݍ��� */
  MYSTERYCARD_SEQ_INIT,			/* ������ */
  MYSTERYCARD_SEQ_CREATE_SCREEN,	/* ������ʍ쐬 */
  
  MYSTERYCARD_SEQ_MAIN,			/* ���C�����[�v */

  MYSTERYCARD_SEQ_CREATE_MENU,		/* ���j���[�̍쐬 */
  MYSTERYCARD_SEQ_MENU,			/* ���j���[�̃��C�����[�v */
  MYSTERYCARD_SEQ_MENU_TO_VIEWMODE,	/* �J�[�h�̐����������郂�[�h�ֈڍs */
  MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2,
  MYSTERYCARD_SEQ_MENU_VIEWMODE,	/* �J�[�h�̐����������郂�[�h */
  MYSTERYCARD_SEQ_MENU_VIEWMODE2,
  MYSTERYCARD_SEQ_MENU_VIEWMODE3,
  MYSTERYCARD_SEQ_END_MENU,		/* ���j���[���I�����ă��C�����[�v�� */
  MYSTERYCARD_SEQ_REMOVE_MENU,		/* �J�[�h���������j���[�̃��C�����[�v */

  MYSTERYCARD_SEQ_SENDFIGT_YESNO,	/* �����킯���܂����H�@�͂��^������ */
  MYSTERYCARD_SEQ_COMM_YESNO,		/* �c�r���C�����X�ʐM���J�n���܂����H�@�͂��^������ */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT,	/* �������킯��ʂ֍s������ */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2,	/* �������킯��ʂ֍s������ ���̂Q */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3,	/* �������킯��ʂ֍s������ ���̂R */
  MYSTERYCARD_SEQ_ENTRY_SENDGIFT,	/* �������킯��� */

  MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1,	/* �������킯��ʏI�� ���̂P */
  MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2,	/* �������킯��ʏI�� ���̂Q */

  MYSTERYCARD_SEQ_SEND_WAITSYNC,	/* �^�C�~���O���Ƃ��ăf�[�^���M */
  MYSTERYCARD_SEQ_WAIT_ENDCOMM,		/* �ʐM���C�u�������I������܂ő҂� */
  MYSTERYCARD_SEQ_SEND_SAVEDATA,	/* �������킯��̃f�[�^�Z�[�u */
  MYSTERYCARD_SEQ_LAST_SAVE_WAIT,	/* �q�@�Ɠ���������܂ő҂��Ă���Ō�̃Z�[�u���� */

  MYSTERYCARD_SEQ_SEND_FINISH,		/* �I��(�d��OFF) */
  
  MYSTERYCARD_SEQ_TO_RETURN,		/* �O�̃��j���[�֖߂邽�߂̓���� */
  MYSTERYCARD_SEQ_WAIT_FADE,		/* �t�F�[�h���I������܂ő҂� */

  MYSTERYCARD_SEQ_RETURN,		/* �O�̃��j���[��ʂ֖߂� */
  MYSTERYCARD_SEQ_LOOP,			/* �G���[���̖������[�v */

  MYSTERYCARD_SEQ_MAX
};


typedef struct {
  int id;
  u32 param;
} LISTDATA;



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static int MysteryCardGoRemove(PROC *proc);
static int MysteryCardGoSendGift(PROC *proc);
static int MysteryCardRetMainMenu(PROC *proc);
static int MysteryCardRemove(PROC *proc);
static void MysteryCardRemoveMainMenu(MYSTERYCARD_WORK *wk);
static BOOL _nop(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTitleWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardStatusWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardDateWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTextWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTransWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu1Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu2Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu3Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardDrawEntry(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static int MysteryCardDispConnectChildStatus(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win);
static void MysteryCardDispConnectChildCount(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, int num);
static void CommMysteryCardExit(MYSTERYCARD_WORK *wk, int *seq, int next);
static int MysteryCardCreateWindow(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN	*win, int index, int base);
static void CreateCardGraphics(MYSTERYCARD_WORK *wk, int side);
static int MysteryCardNextCard(MYSTERYCARD_WORK *wk, int card, int add);
static void MysteryCardCreateMsgWindow(MYSTERYCARD_WORK *wk, int font, int side);

static int CommMysteryCard_CreateBeacon(MYSTERYCARD_WORK *wk);
//static void CommMysteryCard_CreateSendData(MYSTERYCARD_WORK *wk);

static void MysteryCard_DisplayPokemonIcon(MYSTERYCARD_WORK *wk);
static void RemoveCellActor(MYSTERYCARD_WORK *wk);
static int MysteryCardGetConnectCount(MYSTERYCARD_WORK *wk);

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
typedef struct {
  int side;
  int sx, sy;
  int width, height;
  int font;
  int color;
  int background;
  
  u32 msgid;
  BOOL (*func)(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);

  int ox, oy;
  
} MYSTERYCARD_MSGWIN_TABLE;

MYSTERYCARD_MSGWIN_TABLE MsgWin_Table[] = {
  /*  ------------------------------ �\�� ---------------------------- */
  /* �ӂ����ȃJ�[�h */
  /*  0 */ { MYSTERYCARD_FRONT, 2,  2, 12,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_001,	_nop },
  /* ��������ЂÂ� */
  /*  1 */ { MYSTERYCARD_FRONT, 6, 17, 11,  2, FONT_TALK, MYSTERYCARD_WHITE, -1,	mystery_card_005,	_nop },
  /* �|�P�����Z���^�[�ɂ���\n�͂������񂩂�@�����Ƃ��Ă��������@�Ȃ� */
  /*  2 */ { MYSTERYCARD_FRONT, 2,  9, 28,  4, FONT_TALK, MYSTERYCARD_BLACK, -1,	NULL,		MysteryCardStatusWin },
  /* �J�[�h���̕\�� */
  /*  3 */ { MYSTERYCARD_FRONT, 2,  6, 28,  2, FONT_TALK, MYSTERYCARD_WHITE, -1,	NULL,		MysteryCardTitleWin },
  /* ���t */
  /*  4 */ { MYSTERYCARD_FRONT,18, 17, 11,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_014,		MysteryCardDateWin },

  /*  ------------------------------ ���� ---------------------------- */
  /* �J�[�h�̐��� */
  /*  5 */ { MYSTERYCARD_BACK , 2,  3, 28, 10, FONT_TALK, MYSTERYCARD_BLACK, -1,	NULL,		MysteryCardTextWin },
  /* ���΂��񐔂ƃ��b�Z�[�W�\�� */
  /*  6 */ { MYSTERYCARD_BACK , 2, 14, 28,  4, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_006,	MysteryCardTransWin },

  /*  ------------------------------ ���j���[ ---------------------------- */
  /*  7 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 15,	mystery_card_001,	_nop },
  /*  8 */ { MYSTERYCARD_MENU ,18,  9, 12,  8, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu1Win },
  /*  9 */ { MYSTERYCARD_MENU ,24, 13,  6,  4, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu2Win },
  /* 10 */ { MYSTERYCARD_MENU ,24, 13,  6,  4, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu3Win },

  /*  ------------------------------ �������킯 ---------------------------- */
  /* �Ƃ������͂�����@���������イ */
  /* 11 */ { MYSTERYCARD_SEND,  1,  1, 25,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_001, _nop, 7, 0},
  /* ���񂴂��̃G���g���[ */
  /* 12 */ { MYSTERYCARD_SEND, 23,  7,  9,  4, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_004, _nop, 2, 0 },
  /* ���΂� */
  /* 13 */ { MYSTERYCARD_SEND,  6, 20,  6,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_006, _nop, 8, 1},
  /* ��߂� */
  /* 14 */ { MYSTERYCARD_SEND, 21, 20,  6,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_007, _nop, 0, 1 },
  /* ���񂴂��̃G���g���[(���^�S) */
  /* 15 */ { MYSTERYCARD_SEND, 25, 12,  4,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_osusowake_005, MysteryCardDrawEntry },
  /* ���ۂɃG���g�����Ă�l��\������E�B���h�E */
  /* 16 */ { MYSTERYCARD_SEND,  2,  5, 19, 11, FONT_SYSTEM, MYSTERYCARD_BLACK, -1,	NULL,		     _nop },

  /* �������킯�����d���������Ă��������E�B���h�E */
  /* 17 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 14,	mystery_osusowake_008, _nop },
  /* 18 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 14,	mystery_osusowake_009, _nop },
};

/* ���j���[�p�f�[�^ */
LISTDATA MysteryCard_Menu1Data[] = {
  { mystery_card_007, (u32)MYSTERYCARD_SEQ_MENU_TO_VIEWMODE },	// ���߂����@���
  { mystery_card_008, (u32)MysteryCardGoSendGift },		// �������킯
  { mystery_card_009, (u32)MysteryCardGoRemove },		// ���Ă�
  { mystery_card_010, (u32)MYSTERYCARD_SEQ_END_MENU },		// ��߂�
};
/* �J�[�h�������I�� */
LISTDATA MysteryCard_Menu2Data[] = {
  { mystery_drop_004, (u32)MysteryCardRemove },			// �͂�
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// ������
};
/* �������킯�I�� */
LISTDATA MysteryCard_Menu3Data[] = {
  { mystery_drop_004, (u32)MYSTERYCARD_SEQ_COMM_YESNO },	// �͂�
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// ������
};
/* �c�r���C�����X�ʐM������H�I�� */
LISTDATA MysteryCard_Menu4Data[] = {
  { mystery_drop_004, (u32)MYSTERYCARD_SEQ_MENU_TO_SENDGIFT },	// �͂�
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// ������
};

/* �ėp���j���[�\����(���g�����������čė��p) */
static BMPLIST_HEADER MenuListHeader = {
  NULL,
  MysteryLib_MenuKeyMove,	 	/* �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐� */
  NULL,				     	/* ���\�����Ƃ̃R�[���o�b�N�֐� */
  NULL,					/* BMP�E�B���h�E�f�[�^ */
  0,/* ��Ŗ��߂� */			/* ���X�g���ڐ� */
  4,					/* �\���ő區�ڐ� */
  0,					/* ���x���\���w���W */
  12,					/* ���ڕ\���w���W */
  0,					/* �J�[�\���\���w���W */
  0,					/* �\���x���W */
  FBMP_COL_BLACK,			/*�����F */
  FBMP_COL_WHITE,			/*�w�i�F */
  FBMP_COL_BLK_SDW,			/*�����e�F */
  0,					/* �����Ԋu�w */
  16,					/* �����Ԋu�x */
  BMPLIST_LRKEY_SKIP,			/* �y�[�W�X�L�b�v�^�C�v */
  FONT_SYSTEM, 				/* �����w��(�{���� u8 �����ǁA����Ȃɍ��Ȃ��Ǝv���̂�) */
  0			  		/* �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF) */
};



//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(MYSTERYCARD_WORK *wk)
{
  RemoveCellActor(wk);
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_panel_00_lz_ccgr,
		       NARC_mystery_fusigi_panel_nclr,
		       NARC_mystery_fusigi_panel_00_lz_ccer,
		       NARC_mystery_fusigi_panel_00_lz_canr,
		       GF_BGL_MAIN_DISP);
}


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�̍폜
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RemoveCellActor(MYSTERYCARD_WORK *wk)
{
  if(wk->ibase[0])	CLACT_Delete(wk->ibase[0]);
  if(wk->ibase[1])	CLACT_Delete(wk->ibase[1]);
  wk->ibase[0] = wk->ibase[1] = NULL;
  if(wk->pokeicon[0])	CLACT_Delete(wk->pokeicon[0]);
  if(wk->pokeicon[1])	CLACT_Delete(wk->pokeicon[1]);
  if(wk->pokeicon[2])	CLACT_Delete(wk->pokeicon[2]);
  wk->pokeicon[0] = wk->pokeicon[1] = wk->pokeicon[2] = NULL;
  MysteryLib_RemoveClact();
}

//------------------------------------------------------------------
/**
 * @brief	�I���^��߂�y��I�u�W�F�N�g�̓o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetBaseIcon(MYSTERYCARD_WORK *wk)
{
  wk->select_icon = 0;
  wk->ibase[0] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->ibase[0],  72, 168, 1);
  CLACT_BGPriorityChg(wk->ibase[0], 2);
  wk->ibase[1] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->ibase[1], 184, 168, 0);
  CLACT_BGPriorityChg(wk->ibase[1], 2);
}


//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�����݂���΃N���A����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CMC_BmpMenuWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpMenuWinClear(win, trans_sw);
}
static void CMC_BmpTalkWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpTalkWinClear(win, trans_sw);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[��o�^����ėp�֐�
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateWindowMenuData(MYSTERYCARD_WORK *wk, LISTDATA *ld, int num, GF_BGL_BMPWIN *win)
{
  int i;
  BMPLIST_HEADER list_h;

  if(wk->bmd)	BMP_MENULIST_Delete(wk->bmd);
  if(wk->lw) 	BmpListExit(wk->lw, NULL, NULL);
  /* ���j���[�̕������o�^ */
  wk->bmd = BMP_MENULIST_Create(num,HEAPID_MYSTERYCARD);
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  for(i = 0; i < num; i++)
    BMP_MENULIST_AddArchiveString(wk->bmd, wk->msgman, ld[i].id, ld[i].param);
  MSGMAN_Delete(wk->msgman);
  /* desc�쐬 �� �ύX �� �o�^ */
  list_h = MenuListHeader;
  list_h.list = wk->bmd;
  list_h.count = num;
  list_h.win = win;
  wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_MYSTERYCARD);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�w��̃E�B���h�E�ɕ������\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void DrawStringWindow(GF_BGL_BMPWIN *win, int msgid)
{
  STRBUF *msg;
  MSGDATA_MANAGER *msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  WORDSET *word = WORDSET_Create(HEAPID_MYSTERYCARD);

  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_TALK, FONT_HEADER_B_COLOR));
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_MYSTERYCARD);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, MYSTERYCARD_BLACK, NULL);
  GF_BGL_BmpWinOn(win);

  STRBUF_Delete(msg);
  MSGMAN_Delete(msgman);
  WORDSET_Delete(word);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�������킯��ʂ̍쐬
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardCreateOsusowake(GF_BGL_INI *ini)
{
  // �������킯��ʐ�p�̃t�H���g�p���b�g��]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_font_00_nclr, PALTYPE_MAIN_BG, 16*2*FONT_PALNO_NORMAL, 16*2, HEAPID_MYSTERYCARD);

  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_nclr, PALTYPE_MAIN_BG, 16*2*OSUSOWAKE_PALNO, 16*2, HEAPID_MYSTERYCARD);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_M, 0, 6*16*0x20, 1, HEAPID_MYSTERYCARD);
  // ���C����ʃX�N���[���P
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_00_lz_cscr, ini,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_MYSTERYCARD);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_M, 0, 0, 32, 24, OSUSOWAKE_PALNO);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_M);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�������킯���鏈���ֈڍs
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardGoSendGift(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);

  DrawStringWindow(&wk->msgwin, mystery_card_011);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+3, wk->menu_index);
  return MYSTERYCARD_SEQ_SENDFIGT_YESNO;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�J�[�h�����Ă鏈���Ɉڍs
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardGoRemove(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);

  if(FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == TRUE)
    /* ��������́@���@�����Ƃ��Ă܂���\n���́@�J�[�h���@���Ă܂����H */
    DrawStringWindow(&wk->msgwin, mystery_drop_002);
  else
    /* ���́@�J�[�h���@���Ă܂����H */
    DrawStringWindow(&wk->msgwin, mystery_drop_001);

  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+2, wk->menu_index);
  return MYSTERYCARD_SEQ_REMOVE_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�J�[�h���̂Ă鏈��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardRemove(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  /* �J�[�h���̂ĂĂ܂��c�̏��� */
  MysteryCardRemoveMainMenu(wk);
  DrawStringWindow(&wk->msgwin, mystery_drop_003);
  /* �^�C���A�C�R���\���X�^�[�g */
  wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYCARD_TFRAMECHR);

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�̂Ă�J�[�h %d\n", wk->disp_card);
#endif
  /* �J�[�h�̖������� */
  FUSHIGIDATA_RemoveCardData(wk->fdata, wk->disp_card);
  SaveData_Save(wk->sv);

  /* �^�C���A�C�R�������� */
  TimeWaitIconDel(wk->time_icon);
  
  /* �J�[�h���c���Ă���΃��C��������
     �c���Ă��Ȃ���΁u�ӂ����ȁ@��������́v�̃��j���[�܂Ŗ߂� */
  if(FUSHIGIDATA_IsExistsCardAll(wk->fdata) == FALSE)
    return MYSTERYCARD_SEQ_TO_RETURN;
  
  /* �J�[�h���c���Ă���̂ŁA���̃J�[�h��T���ĕ\�� */
  wk->disp_card = MysteryCardNextCard(wk, wk->disp_card,  1);

  OS_TPrintf("���ɕ\������J�[�h %d\n", wk->disp_card);

  DrawStringWindow(&wk->msgwin, mystery_card_001);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);

  MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);

  return MYSTERYCARD_SEQ_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���C�����j���[�ɖ߂�
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardRetMainMenu(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);
  DrawStringWindow(&wk->msgwin, mystery_card_001);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);
  return MYSTERYCARD_SEQ_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardRemoveMainMenu(MYSTERYCARD_WORK *wk)
{
  BMP_MENULIST_Delete(wk->bmd); wk->bmd = NULL;
  BmpListExit(wk->lw, NULL, NULL); wk->lw = NULL;
  CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
  GF_BGL_BmpWinOff(&wk->menuwin); GF_BGL_BmpWinDel(&wk->menuwin);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�������Ȃ�
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL _nop(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col){ return TRUE; }

//--------------------------------------------------------------------------------------------
/**
 * @brief	�J�[�h�̃^�C�g���\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTitleWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF *msg;

  msg = STRBUF_Create( GIFT_DATA_CARD_TITLE_MAX+1, wk->heapid );
  STRBUF_SetStringCodeOrderLength(msg, wk->card[wk->disp_card]->beacon.event_name, GIFT_DATA_CARD_TITLE_MAX);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�J�[�h�̏�Ԃ�\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardStatusWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF * msg;
  GIFT_CARD *card = wk->card[wk->disp_card];
  int msgid;


  //  card->gift_type = MYSTERYGIFT_TYPE_NONE;
  
  //  if(card->gift_type == MYSTERYGIFT_TYPE_NONE){
  if(card->beacon.delivery_flag == FALSE){
    /* �J�[�h���݂̂Ŕz�B���̃f�[�^���Ȃ��ꍇ */
    msgid = mystery_card_004;
  } else {
    if(wk->fdata == NULL || FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == TRUE)
      /* �z�B����񂪂����āA�܂����[�U�[���󂯎���ĂȂ��ꍇ */
      msgid = mystery_card_002;
    else
      /* �z�B������󂯎���Ă����ꍇ�̃��b�Z�[�W */
      msgid = mystery_card_003;
  }

  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, msgid, wk->heapid);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���t��\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardDateWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  RTCDate date;

  RTC_ConvertDayToDate(&date, wk->card[wk->disp_card]->recv_date);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("pokemon_icon = %d, %d, %d\n",
	    wk->card[wk->disp_card]->pokemon_icon[0],
	    wk->card[wk->disp_card]->pokemon_icon[1],
	    wk->card[wk->disp_card]->pokemon_icon[2]);
  OS_Printf("���܂łɔz�z������ = %d\n", wk->card[wk->disp_card]->re_dealed_count);
  OS_Printf("%04d/%02d/%02d [ %d ]\n", date.year, date.month, date.day, wk->card[wk->disp_card]->recv_date);
#endif  

  // ��������Z�b�g�������Č�̓��b�Z�[�W�ɔC����
  WORDSET_RegisterNumber(wk->word, 0, date.year+2000, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(wk->word, 1, date.month,     2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(wk->word, 2, date.day,       2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�J�[�h�̐�������\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTextWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF * msg;

  msg = STRBUF_Create( GIFT_DATA_CARD_TEXT_MAX+1, HEAPID_MYSTERYCARD );
  STRBUF_SetStringCodeOrderLength(msg, wk->card[wk->disp_card]->event_text, GIFT_DATA_CARD_TEXT_MAX);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�z�z�ł���񐔂�\������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTransWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
#if 0	// �����񐔕\���e�X�g
  wk->card[wk->disp_card]->re_deal_count = 255;
#endif

  if(wk->card[wk->disp_card]->re_deal_count == 255){
    // �����񐔂̔z�z
    STRBUF * msg;
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, mystery_card_016, HEAPID_MYSTERYCARD);
    GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
    STRBUF_Delete(msg);
    return FALSE;
  } else if(wk->card[wk->disp_card]->re_deal_count){
    // �w��񐔂̔z�z
    WORDSET_RegisterNumber(wk->word, 0,
			   wk->card[wk->disp_card]->re_deal_count,
			   3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    return TRUE;
  } else {
    // �Ĕz�z�ł��Ȃ��̂ŕ\�����Ȃ�
    return FALSE;
  }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[�P���쐬
 *		���C�����j���[
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu1Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  LISTDATA ld[4];
  MYSTERYCARD_MSGWIN_TABLE *tbl;
  int index = 0;

  // �������킯���o���Ȃ��ꍇ�́u�������킯�v���j���[��\�����Ȃ�
  ld[index++] = MysteryCard_Menu1Data[0];
  if(wk->card[wk->disp_card]->re_deal_count)
    ld[index++] = MysteryCard_Menu1Data[1];
  // �z�B�l����󂯎���Ă��Ȃ��ꍇ�́u���Ă�v���j���[��\�����Ȃ�
  if(FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == FALSE)
    ld[index++] = MysteryCard_Menu1Data[2];
  ld[index++] = MysteryCard_Menu1Data[3];
  // �E�B���h�E�̃T�C�Y�ɂ��킹�ă��j���[����蒼��
  tbl = wk->tbl;
  GF_BGL_BmpWinOff(win);  GF_BGL_BmpWinDel(win);
  GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME2_M,
		   tbl->sx, tbl->sy + (4 - index) * 2, tbl->width, tbl->height - (4 - index) * 2,
		   FONT_PALNO_NORMAL, wk->nowbase);
  // ���j���[�o�^
  CreateWindowMenuData(wk, ld, index, win);

  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[�Q���쐬
 *		�J�[�h�����Ă܂����H�@�͂��^������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu2Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  CreateWindowMenuData(wk, MysteryCard_Menu2Data, 2, win);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[�R���쐬
 *		�������킯�����܂����H�@�͂��^������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu3Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  CreateWindowMenuData(wk, MysteryCard_Menu3Data, 2, win);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[�S���쐬
 *		�c�r���C�����X�������\n�������@���܂��@�͂��^������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu4Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  DrawStringWindow(&wk->msgwin, mystery_01_003);
  CreateWindowMenuData(wk, MysteryCard_Menu4Data, 2, win);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���݂̃G���g����\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardDrawEntry(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  WORDSET_RegisterNumber(wk->word, 0, 0/*wk->entry*/, 1, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�t�F�[�h����
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void RequestFade(MYSTERYCARD_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_MYSTERYCARD);
  if(seq)
    *seq = MYSTERYCARD_SEQ_WAIT_FADE;
  wk->next_seq = next_seq;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�K�v�ȃX�N���[���̍쐬
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardCreateMsgWindow(MYSTERYCARD_WORK *wk, int font, int side)
{
  int i, chbase;
  STRBUF * msg;
  GF_PRINTCOLOR col;
  MYSTERYCARD_MSGWIN_TABLE *tbl = MsgWin_Table;
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, wk->heapid);
  wk->word = WORDSET_Create(wk->heapid);

  wk->disp_side = side;

  CreateCardGraphics(wk, side);

  /* �܂��͕ʃT�C�h�̃E�B���h�E�𖕏� */
  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(tbl[i].side != side && tbl[i].side != MYSTERYCARD_MENU){
      if(wk->win[i].ini){
	GF_BGL_BmpWinOff(&wk->win[i]);
	GF_BGL_BmpWinDel(&wk->win[i]);
      }
    }
  }
  chbase = MYSTERYCARD_CHBASE;
  /* �V���ɃE�B���h�E����蒼�� */
  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(tbl[i].side == side){
      if(wk->win[i].ini == NULL){
	// �E�B���h�E������āc
	wk->chbase[i] = chbase;
	GF_BGL_BmpWinAdd(wk->bgl, &wk->win[i], GF_BGL_FRAME0_M,
			 tbl[i].sx, tbl[i].sy, tbl[i].width, tbl[i].height,
			 FONT_PALNO_NORMAL, chbase);
      }
      // �E�B���h�E���N���A���āc
      GF_BGL_BmpWinDataFill(&wk->win[i], FontHeaderGet(tbl[i].font, tbl[i].background));
      col = tbl[i].color;
      // �O���t�@���N�V�������Ăяo���āc
      if(tbl[i].func(wk, &wk->win[i], col) == TRUE){
	// ���b�Z�[�W������Ε\������
	if(tbl[i].msgid){
	  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, tbl[i].msgid, wk->heapid);
	  GF_STR_PrintColor(&wk->win[i], tbl[i].font, msg, tbl[i].ox, tbl[i].oy, MSG_NO_PUT, col, NULL);
	  STRBUF_Delete(msg);
	}
      }
      /* �Ō�ɃE�B���h�E�\�� */
      GF_BGL_BmpWinOn(&wk->win[i]);
      chbase += tbl[i].width * tbl[i].height;
    }
  }
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);

  /* �|�P�����̃A�C�R����\�� */
  if(side == MYSTERYCARD_FRONT)
    MysteryCard_DisplayPokemonIcon(wk);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�V�������j���[�E�B���h�E���J��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardCreateWindow(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN	*win, int index, int base)
{
  STRBUF * msg;
  GF_PRINTCOLOR col;
  MYSTERYCARD_MSGWIN_TABLE *tbl = MsgWin_Table + index;
#if 0
  OS_Printf("%d, %d, %d, %d, %d, %d\n", tbl->sx, tbl->sy, tbl->width, tbl->height, index,base);
#endif
  if(win->ini == NULL){
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME2_M,
		     tbl->sx, tbl->sy, tbl->width, tbl->height,
		     FONT_PALNO_NORMAL, base);
  }
  GF_BGL_BmpWinDataFill(win, tbl->background);
  if(tbl->msgid){
    wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
    wk->word = WORDSET_Create(HEAPID_MYSTERYCARD);
  }
  // �O���t�@���N�V�������Ăяo��
  wk->nowbase = base;
  wk->tbl = tbl;
  tbl->func(wk, win, MYSTERYCARD_BLACK);
  // ���b�Z�[�W������Ε\�����āc
  if(tbl->msgid){
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, tbl->msgid, HEAPID_MYSTERYCARD);
    GF_STR_PrintColor(win, tbl->font, msg, 0, 0, MSG_NO_PUT, tbl->color, NULL);
    STRBUF_Delete(msg);
    MSGMAN_Delete(wk->msgman);
    WORDSET_Delete(wk->word);
  }
  if(win == &wk->msgwin){	// ���߂�Ȃ����R�[�h
    BmpTalkWinWrite(win, WINDOW_TRANS_ON, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER);
  } else {
    BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  }

  return base + tbl->width * tbl->height;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���̃J�[�h����������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardNextCard(MYSTERYCARD_WORK *wk, int card, int add)
{
  int orgcard = card;

  while(1){
    card += add;
    if(card == GIFT_CARD_MAX)	card = 0;
    if(card == -1)		card = GIFT_CARD_MAX - 1;
    if(orgcard == card)
      break;
    if(FUSHIGIDATA_IsExistsCard(wk->fdata, card))
      break;
  }
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("���̃J�[�h�X���b�g�� %d �Ԃł�\n", card);
#endif
  return card;
}

static void CMC_ArcUtil_ScrnSet(MYSTERYCARD_WORK *wk, u32 dataIdx, u32 frm, u32 transSize)
{
  // ArcUtil_ScrnSet���Ɣ񐂒����Ԓ���VRAM�]������Ă��܂��̂ŁA�C��
  NNSG2dScreenData* scrnData;
  void *arcData = ArcUtil_Load(ARC_MYSTERY_GRA, dataIdx, 1, wk->heapid, ALLOC_BOTTOM);
  NNS_G2dGetUnpackedScreenData( arcData, &scrnData );
  GF_BGL_ScreenBufSet(wk->bgl, frm, scrnData->rawData, transSize);
  sys_FreeMemoryEz( arcData );
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃X�N���[����]��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateCardGraphics(MYSTERYCARD_WORK *wk, int side)
{
  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card_nclr, PALTYPE_MAIN_BG, 0, 16*16, wk->heapid);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card_lz_cngr, wk->bgl, GF_BGL_FRAME1_M, 0, 24*16*0x20, 1, wk->heapid);

  switch(side){
  case MYSTERYCARD_FRONT:
    // ���C�����BG1�X�N���[���]��
    ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card01_lz_cscr, wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
    break;
  case MYSTERYCARD_BACK:
    // ���C�����BG1�X�N���[���]��
    ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card02_lz_cscr, wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
    break;
  }

  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*LATTICEBG_PALNO, 16*2, wk->heapid);
  // ���C�����BG2�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME3_M, LATTICEBG_CHARBASE * 1/*0x20*/, 1*16*0x20, 1, wk->heapid);
  // ���C����ʃX�N���[���P
  CMC_ArcUtil_ScrnSet(wk, NARC_mystery_fusigi_bg_00_lz_cscr, GF_BGL_FRAME3_M, 32*24*2);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME3_M, 0, 0, 32, 24, LATTICEBG_PALNO);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME3_M);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[�I�������s
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void DoMenuMain(PROC *proc, int *seq, int (*cfunc)(PROC *))
{
  u32 ret;
  int ret_seq;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  static int (*func)(PROC *);
  
  ret = BmpListMain(wk->lw);
  switch(ret){
  case BMPLIST_NULL:	/* �����I������Ă��Ȃ� */
    break;
  case BMPLIST_CANCEL:	/* �L�����Z�����ꂽ */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    if(cfunc){
      ret_seq = cfunc(proc);
      if(ret_seq != -1)
	*seq = ret_seq;
    }
    break;
  default:		/* ���������肳�ꂽ */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    if(ret){
      if(ret < MYSTERYCARD_SEQ_MAX){
	*seq = ret;
      } else {
	func = (static int (*)(PROC *))ret;
	ret_seq = func(proc);
	if(ret_seq != -1)
	  *seq = ret_seq;
      }
    }
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	�|�P�����̃A�C�R����\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_DisplayPokemonIcon(MYSTERYCARD_WORK *wk)
{
  int px, no, pokeno;
  u8 *buf;
  NNSG2dCharacterData *chara;

  if(wk->pokeicon[0] == NULL && wk->pokeicon[1] == NULL && wk->pokeicon[2] == NULL){
  
    if(MysteryLib_isInitClact() == TRUE)
      RemoveCellActor(wk);
    MysteryLib_InitCPManager();
    MysteryLib_InitClactSystem();
    MysteryLib_InitClact(ARC_MYSTERY_GRA,
			 NARC_mystery_gba_box_oam_lz_cngr,
			 NARC_mystery_gba_box_oam_nclr,
			 NARC_mystery_gba_box_oam_lz_ccer,
			 NARC_mystery_gba_box_oam_lz_canr,
			 GF_BGL_MAIN_DISP);
    // �|�P�����A�C�R���p�p���b�g����C�ɓǂݍ����VRAM�]������
    ArcUtil_PalSet(ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20,
		   0, wk->heapid);
  }

  pokeno = 1;
  px = 178;
  for(no = 0; no < MYSTERYGIFT_POKEICON; no++, px += 25){
    pokeno = wk->card[wk->disp_card]->pokemon_icon[no];
    if(pokeno == 0){
      if(wk->pokeicon[no])
	CLACT_SetDrawFlag(wk->pokeicon[no], 0);
      continue;
    }

    wk->pokeicon[no] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->pokeicon[no], px, 16, 10+no);
    
    buf = ArcUtil_CharDataGet(ARC_POKEICON, 
			      PokeIconCgxArcIndexGetByMonsNumber(pokeno, 0, 0), 0, &chara, wk->heapid);
    DC_FlushRange(chara->pRawData, POKEICON_TRANS_SIZE);

    // �L�����N�^�[�]��
    GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20, POKEICON_TRANS_SIZE);
    // �p���b�g�ݒ�
    CLACT_PaletteNoChg(wk->pokeicon[no],  PokeIconPalNumGet(pokeno, 0, 0)+POKEICON_PAL_OFFSET );
    sys_FreeMemoryEz(buf);
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�ӂ����ȃJ�[�h�F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryCardProc_Init(PROC * proc, int * seq)
{
  MYSTERYCARD_WORK *wk;

  /* ���[�N�G���A��TITLE_STARTMENU�̏�ɍ쐬����(�����̏��Ԃ͖��Ȃ��͂�) */
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_MYSTERYCARD, MYSTERYCARD_HEADSIZE);
  wk = PROC_AllocWork(proc, sizeof(MYSTERYCARD_WORK), HEAPID_MYSTERYCARD);
  /* �������s�ǂ��|���̂Ń��[�N�̓[���N���A */
  memset(wk, 0, sizeof(MYSTERYCARD_WORK));
  
  /* �e��ϐ��̏����� */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_MYSTERYCARD);
  wk->heapid = HEAPID_MYSTERYCARD;

  /* ��ʂ̏����ݒ� */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* �ϐ������� */
  wk->disp_card = GIFT_CARD_MAX - 1;
  wk->write_index = 1;
  // ���C�u����������
  MysteryLib_Init(HEAPID_MYSTERYCARD);

  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  return PROC_RES_FINISH;
}


#define CARDHEIGHT		168
#define SPEED			0.025
//------------------------------------------------------------------
/**
 * @brief	�J�[�h��]����VBLANK����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_VBlankTcb(TCB_PTR tcb, void* p_work)
{
  CARDTURN *ct = (CARDTURN *)p_work;
  LASTER_DmaStop();
  LASTER_DmaSet(LASTER_GetReadBuff(ct->laster_ptr), (void *)REG_BG0HOFS_ADDR, sizeof(u32)*2, LASTER_DMA_TYPE32);
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h��]������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_InitTurn(MYSTERYCARD_WORK *wk, BOOL mode, fx32 default_speed, fx32 accel_speed)
{
  CARDTURN *ct = &wk->cturn;

  ct->mode = mode;
  ct->speed = default_speed;
  ct->accel = accel_speed;

  if(ct->laster_ptr == NULL)
    ct->laster_ptr = LASTER_Init(HEAPID_MYSTERYCARD, ct->sbuff[0], ct->sbuff[1]);
  if(ct->tcb_ptr == NULL)
    ct->tcb_ptr = VIntrTCB_Add(MysteryCard_VBlankTcb, ct, 1024);
  ct->do_run = TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�J�[�h��]�����̍ŏI��n��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_FinishTurn(MYSTERYCARD_WORK *wk)
{
  CARDTURN *ct = &wk->cturn;
  if(ct->laster_ptr)
    LASTER_Delete(ct->laster_ptr);
  if(ct->tcb_ptr)
    TCB_Delete(ct->tcb_ptr);
  ct->laster_ptr = NULL;
  ct->tcb_ptr = NULL;
  LASTER_DmaStop();
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h��]����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define CHANGE(y, v)		(0 - (y) + (v))
static BOOL MysteryCard_TurnMainProc(MYSTERYCARD_WORK *wk)
{
  int i, reg;
  u16 *buf;
  CARDTURN *ct = &wk->cturn;
  fx32 line = (CARDHEIGHT/2) * FX32_ONE;

  // �O��ł��łɏ����͏I�����Ă���
  if(ct->do_run == FALSE)	return TRUE;

  // ��ɏI��������s���āA�Ō�̂P�t���[�����쐬����
  if(ct->mode == TRUE){
    // ����ۂ̏I������
    ct->speed += ct->accel;
    ct->accel += ct->accel;
    if(ct->speed / FX32_ONE > 1000){
      ct->do_run = FALSE;
      line = CARDHEIGHT;
      ct->speed = 0;
      ct->accel = 0;
    }
  } else {
    // �J���ۂ̏I������
    ct->speed -= ct->accel;
    ct->accel /= 2;
    if(ct->accel < FX32_ONE/4/*4*/){
      ct->do_run = FALSE;
      ct->speed = 1*FX32_ONE;
      ct->accel = 0;
    }
  }
  // �e���C���̃X�N���[���l�v�Z
  buf = LASTER_GetWriteBuff(ct->laster_ptr);
  for(i = CARDHEIGHT/2; i < CARDHEIGHT; i++){
    reg = line / FX32_ONE;
    if(reg < 0)			reg = 0;
    if(reg > CARDHEIGHT)	reg = CARDHEIGHT;

    buf[i * 4 + 1] =		buf[i * 4 + 3] =		CHANGE(i, reg);
    buf[(CARDHEIGHT - i) * 4 + 1] =	buf[(CARDHEIGHT - i) * 4 + 3] =	CHANGE(CARDHEIGHT - i, CARDHEIGHT - reg);
    
    line += ct->speed;
  }
  DC_FlushRange(buf, sizeof(u16) * HW_LCD_HEIGHT*4);
  // �������I������o�b�t�@�֐؂�ւ�
  LASTER_VBlank(ct->laster_ptr);

  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�V�[�P���X
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SaveSequence(void *p)
{
  int ret;
  MYSTERYCARD_WORK *wk = (MYSTERYCARD_WORK *)p;
  ret = MysteryLib_SaveDSCard();
  if(ret == SAVE_RESULT_OK || ret == SAVE_RESULT_NG){
    Snd_SePlay(SEQ_SE_DP_SAVE);
    //    OS_TPrintf("�����Z�[�u���I�����܂���\n");
    wk->func_hook = NULL;
  }
}

//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�V�[�P���X�J�n
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_StartSaveSeq(MYSTERYCARD_WORK *wk)
{
  /* �z�z�����񐔂��J�E���g�A�b�v(����A�g���̂��ȁc�H) */
  if(wk->card[wk->disp_card]->re_dealed_count != 255)
    wk->card[wk->disp_card]->re_dealed_count++;
  /* �z�z�񐔂��|�P����(������255�Ȃ�Ζ������z�z) */
  if(wk->card[wk->disp_card]->re_deal_count != 255)
    wk->card[wk->disp_card]->re_deal_count--;
  // �Z�[�u�V�[�P���X��o�^
  MysteryLib_InitSaveDSCard(wk->sv);
  wk->func_hook = SaveSequence;
#if 0
  /* �f�[�^�Z�[�u */
  SaveData_Save(wk->sv);
#endif
}


//------------------------------------------------------------------
/**
 * @brief	�J�[�\���ړ�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SelectCursor(MYSTERYCARD_WORK *wk, int connect, int *seq)
{
  int mark;
  int select = wk->select_icon;

  // ���E�ړ�
  if(sys.trg & PAD_KEY_RIGHT && wk->select_icon != 1)
    wk->select_icon = 1;
  if(sys.trg & PAD_KEY_LEFT && wk->select_icon != 0)
    wk->select_icon = 0;
  // �J�[�\�����f
  if(select != wk->select_icon){
    CLACT_AnmChg(wk->ibase[0], wk->select_icon == 0 ? 1 : 0);
    CLACT_AnmChg(wk->ibase[1], wk->select_icon == 0 ? 0 : 1);
  }

  // �����̑I��
  mark = 0;
  if(sys.trg & PAD_BUTTON_CANCEL)
    mark = 2;
  else if((sys.trg & PAD_BUTTON_DECIDE) && connect && wk->select_icon == 0)
    mark = 1;
  else if((sys.trg & PAD_BUTTON_DECIDE) && wk->select_icon == 1)
    mark = 2;
  else if((sys.trg & PAD_BUTTON_DECIDE) && connect == 0)
    mark = 3;

  // �������s
  if(mark == 1){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // �f�[�^�̑��M�J�n
    CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
    wk->sync_wait = 1;
    *seq = MYSTERYCARD_SEQ_SEND_WAITSYNC;
    MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_LASTWIN, MYSTERYCARD_MENU_BASE);
    wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYCARD_TFRAMECHR);
  }
  if(mark == 2){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // �ʐM���I��������
    // ���ʐM���I�������玟�̃V�[�P���X�ֈڍs
    CommMysteryCardExit(wk,  seq, MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1);
  }
  if(mark == 3){
    Snd_SePlay(SEQ_SE_DP_SELECT);
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�ӂ����ȃJ�[�h�F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryCardProc_Main(PROC * proc, int * seq)
{
  int new_card, v1, v2, connect_ds;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  switch(*seq){
  case MYSTERYCARD_READ_SAVEDATA:
    wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
    wk->fdata = SaveData_GetFushigiData(wk->sv);
    wk->cfg = SaveData_GetConfig(wk->sv);
    wk->win_type = CONFIG_GetWindowType(wk->cfg);

    wk->card[0] = FUSHIGIDATA_GetCardData(wk->fdata, 0);
    wk->card[1] = FUSHIGIDATA_GetCardData(wk->fdata, 1);
    wk->card[2] = FUSHIGIDATA_GetCardData(wk->fdata, 2);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("0:%08X  1:%08X  2:%08X\n", wk->card[0], wk->card[1], wk->card[2]);
#endif
    wk->disp_card = MysteryCardNextCard(wk, wk->disp_card, 1);
    *seq = MYSTERYCARD_SEQ_INIT;
    break;
    
  case MYSTERYCARD_SEQ_INIT:
    CommMysteryFunc_VramBankSet();
    CommMysteryFunc_BgInit(wk->bgl);
    *seq = MYSTERYCARD_SEQ_CREATE_SCREEN;
    break;

  case MYSTERYCARD_SEQ_CREATE_SCREEN:
    /* ��ʍ쐬 */
    MSG_PrintInit();
    /* �X�N���[���]�� */
    CreateCardGraphics(wk, MYSTERYCARD_FRONT);
    /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
    SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYCARD);
    /*�E�B���h�E�g�L�����A�p���b�g���Z�b�g */
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_FRAMECHR1, WAKU_PALETTE_NUMBER1, 0, HEAPID_MYSTERYCARD);
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2, 1, HEAPID_MYSTERYCARD);
    TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER, wk->win_type, HEAPID_MYSTERYCARD);

    MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    /* �t�F�[�h�C�� */
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_MAIN, seq);

    break;

  case MYSTERYCARD_SEQ_MAIN:
    new_card = wk->disp_card;
    /* �J�[�h����ւ� */
    if(sys.trg & PAD_KEY_UP){
      new_card = MysteryCardNextCard(wk, wk->disp_card, -1);
    } else if(sys.trg & PAD_KEY_DOWN){
      new_card = MysteryCardNextCard(wk, wk->disp_card,  1);
    }
    /* �߂�{�^���`�F�b�N */
    else if(sys.trg & PAD_BUTTON_CANCEL){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_RETURN, seq);
    }
    /* �`�{�^���Ń��j���[���J�� */
    else if(sys.trg & PAD_BUTTON_DECIDE){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      *seq = MYSTERYCARD_SEQ_CREATE_MENU;
    }

    /* �ύX����������J�[�h�\�� */
    if(wk->disp_card != new_card){
      Snd_SePlay(SEQ_SE_DP_CARD2);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("�J�[�h�ύX����! %d -> %d\n", wk->disp_card, new_card);
#endif
      wk->disp_card = new_card;
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    }

    break;


  // �����̊Ԃ̓��j���[�̐��� ----------------------------

    
  case MYSTERYCARD_SEQ_CREATE_MENU:
    /* ���j���[���J�� */
    wk->menu_index = MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_MENU, MYSTERYCARD_MENU_BASE);
    MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);
    *seq = MYSTERYCARD_SEQ_MENU;
    break;

  case MYSTERYCARD_SEQ_MENU:
    /* ���j���[��� */
    DoMenuMain(proc, seq, NULL);
    if(sys.trg & PAD_BUTTON_CANCEL){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      *seq = MYSTERYCARD_SEQ_END_MENU;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_TO_VIEWMODE:
    /* �J�[�h�̐����������郂�[�h�ֈڍs */
    Snd_SePlay(SEQ_SE_DP_CARD2);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
    CMC_BmpTalkWinClear(&wk->msgwin,  WINDOW_TRANS_ON);
    CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
    // �J�[�h�����
    MysteryCard_InitTurn(wk, TRUE,     1*FX32_ONE, SPEED*FX32_ONE);
    *seq = MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2;
    break;
    
  case MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2:
    if(MysteryCard_TurnMainProc(wk)){
      // ���ʂ�`��
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_BACK);
      // �J�[�h���J��
      MysteryCard_InitTurn(wk, FALSE, 1800*FX32_ONE,   900*FX32_ONE);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_VIEWMODE:
    MysteryCard_TurnMainProc(wk);
    /* �J�[�h�̐����������郂�[�h */
    if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
      Snd_SePlay(SEQ_SE_DP_CARD2);
      //      Snd_SePlay(SEQ_SE_DP_SELECT);
      // �J�[�h�����
      MysteryCard_InitTurn(wk, TRUE,     1*FX32_ONE, SPEED*FX32_ONE);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE2;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_VIEWMODE2:
    if(MysteryCard_TurnMainProc(wk)){
      // �\�ʂ�`��
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
      // �J�[�h���J��
      MysteryCard_InitTurn(wk, FALSE, 1800*FX32_ONE,   900*FX32_ONE);
      GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE3;
    }
    break;
  case MYSTERYCARD_SEQ_MENU_VIEWMODE3:
    if(MysteryCard_TurnMainProc(wk)){
      // ���j���[��`��
      BmpTalkWinWrite(&wk->msgwin,  WINDOW_TRANS_ON, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER);
      BmpMenuWinWrite(&wk->menuwin, WINDOW_TRANS_ON, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2);
      GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
      MysteryCard_FinishTurn(wk);
      *seq = MYSTERYCARD_SEQ_MENU;
    }
    break;

  case MYSTERYCARD_SEQ_END_MENU:
    /* ���j���[������ */
    MysteryCardRemoveMainMenu(wk);
    /* ���b�Z�[�W�E�B���h�E������ */
    CMC_BmpTalkWinClear(&wk->msgwin, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);
    *seq = MYSTERYCARD_SEQ_MAIN;
    break;

  case MYSTERYCARD_SEQ_REMOVE_MENU:
    /* �J�[�h�������I�����j���[ */
    DoMenuMain(proc, seq, MysteryCardRetMainMenu);
    break;


  case MYSTERYCARD_SEQ_SENDFIGT_YESNO:
    /* �������킯�����܂����H �͂��^������ */
    /* �J�[�h�������I�����j���[ */
    DoMenuMain(proc, seq, MysteryCardRetMainMenu);
    break;

  case MYSTERYCARD_SEQ_COMM_YESNO:
    /* �u�c�r���C�����X��������@�������@���܂��v */
    MysteryCardMenu4Win(wk, &wk->menuwin, MYSTERYCARD_BLACK);
    *seq = MYSTERYCARD_SEQ_SENDFIGT_YESNO;
    break;


    
  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT:
    /* �������킯��ʂւ������߂̃t�F�[�h�A�E�g */
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2, seq);
    break;

  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2:
    /* �������킯��ʂ֍s������ */
    /* ���j���[������ */
    MysteryCardRemoveMainMenu(wk);
    /* ���b�Z�[�W�E�B���h�E������ */
    CMC_BmpTalkWinClear(&wk->msgwin, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);
    MysteryCardCreateMsgWindow(wk, FONT_SYSTEM, MYSTERYCARD_SEND);
    /* �������킯��ʂ̍쐬 */
    MysteryCardCreateOsusowake(wk->bgl);
    /* �I�u�W�F�N�g����̏����� */
    InitCellActor(wk);
    SetBaseIcon(wk);
    *seq = MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3;
    break;

  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3:
    // �e�Ƃ��ĒʐM�J�n
    CommMysteryCard_CreateBeacon(wk);
    WirelessIconEasy();		// �ʐM�A�C�R���\��
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_ENTRY_SENDGIFT, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT:
    /* �������킯�̃G���g������� */
    connect_ds = 0;
    if(CommIsConnect(COMM_PARENT_ID)){
      CommMPSetBeaconTempData(&wk->gwk.gift_data.beacon);
      // �Ȃ����Ă���q�@��\��
      connect_ds = MysteryCardDispConnectChildStatus(wk, &wk->win[MYSTERYCARD_ENTRY_LIST]);
      if(connect_ds == 0 && wk->prev_connect){
	// �N�����Ȃ��Ȃ��āA��قǂ܂Ōq�����Ă�����E�B���h�E���N���A
	GF_BGL_BmpWinDataFill(&wk->win[MYSTERYCARD_ENTRY_LIST], 0);
	GF_BGL_BmpWinOn(&wk->win[MYSTERYCARD_ENTRY_LIST]);
	wk->prev_connect = 0;
      }
      MysteryCardDispConnectChildCount(wk, &wk->win[MYSTERYCARD_ENTRY_COUNT], connect_ds);
      wk->prev_connect = connect_ds;
    }
    /* �J�[�\���ړ��őI�� */
    SelectCursor(wk, connect_ds, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1:
    // �t�F�[�h�A�E�g�J�n
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2:

    RemoveCellActor(wk);
    CMC_BmpTalkWinClear(&wk->msgwin,  WINDOW_TRANS_ON);
    CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
    
    // ��ʂ����������ăt�F�[�h�C��
    MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
    SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYCARD);
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_CREATE_MENU, seq);
    break;

    
  case MYSTERYCARD_SEQ_WAIT_ENDCOMM:
    if(CommStateIsInitialize() == FALSE)
      *seq = wk->next_seq;
    break;
    
  case MYSTERYCARD_SEQ_SEND_WAITSYNC:
    if(--wk->sync_wait == 0){
      /* �������킯�� */
      MysteryLib_CreateCryptoData(&wk->gwk.gift_data, &wk->comm_data, wk->heapid);
      CommMysterySendGiftDataParent((const void *)&wk->comm_data, sizeof(GIFT_DATA));
      /* �񓯊��Z�[�u�J�n */
      MysteryCard_StartSaveSeq(wk);
      *seq = MYSTERYCARD_SEQ_SEND_SAVEDATA;
    }
    break;
    
  case MYSTERYCARD_SEQ_SEND_SAVEDATA:
    // �Ō�̂P�Z�N�^�ȊO���Z�[�u�ł�����q�@�Ɠ��������
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST){
      CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE2);
      *seq = MYSTERYCARD_SEQ_LAST_SAVE_WAIT;
    }
    break;

  case MYSTERYCARD_SEQ_LAST_SAVE_WAIT:
    // �q�����Ă���q�@�S�Ă���̕Ԏ���҂�
    if(MysteryCardGetConnectCount(wk) == 0 || CommIsTimingSync(MYSTERYGIFT_SYNC_CODE2) == TRUE){
      MysteryLib_DoLastSave();
      /* �����܂����b�Z�[�W���o���ďI�� */
      MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_LASTWIN+1, MYSTERYCARD_MENU_BASE);
      TimeWaitIconDel(wk->time_icon);
      CommMysteryCardExit(wk, seq, MYSTERYCARD_SEQ_SEND_FINISH);
    }
    break;
    
  case MYSTERYCARD_SEQ_SEND_FINISH:
    // �������킯�I���A�{�^�����܂��ă��j���[��ʂ�
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))
      *seq = MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1;
    break;


    
    // �����̊Ԃ̓��j���[�̐��� ----------------------------

  case MYSTERYCARD_SEQ_TO_RETURN:
    // �����𔲂��đO�̃��j���[�ɋA�鎞�̓����
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_RETURN, seq);
    break;

  case MYSTERYCARD_SEQ_WAIT_FADE:
    /* �t�F�[�h�I���܂ő҂� */
    if(WIPE_SYS_EndCheck()){
      *seq = wk->next_seq;
    }
    break;

    case MYSTERYCARD_SEQ_RETURN:	/* �O�̃��j���[��ʂ֖߂� */
      RemoveCellActor(wk);
      MysteryCard_FinishTurn(wk);
      return PROC_RES_FINISH;
      break;
    
    case MYSTERYCARD_SEQ_LOOP:
      /* �G���[���̖������[�v */
      break;
  }

  // �A�C�R����\�����邽�߂ɕK�v�ȋ쓮����
  if(wk->clactSet!=NULL)
    CLACT_Draw( wk->clactSet );

  MysteryLib_DoClact();

  // �펞�ł͂Ȃ�����ǎ��s�����֐��͂����Ŏ��s
  if(wk->func_hook)
    wk->func_hook(wk);
  
  return PROC_RES_CONTINUE;
}


// ------------------------------ �������� ----------------------------
// �ʐM�֘A�̃v���O�������㔼�ɂ܂Ƃ߂܂�

//--------------------------------------------------------------------------------------------
/**
 * @brief	�r�[�R���f�[�^���쐬���Đe�Ƃ��ĒʐM���J�n
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommMysteryCard_CreateBeacon(MYSTERYCARD_WORK *wk)
{
  /* �Z�[�u�f�[�^����r�[�R�������쐬 */
  GIFT_CARD *gd = wk->card[wk->disp_card];
  memcpy(&wk->gwk.gift_data.data, gd, sizeof(GIFT_DATA));
  memcpy(&wk->gwk.gift_data.beacon, &gd->beacon, sizeof(GIFT_BEACON));
  // ���z�z����鑤�́A����ɑ��z�z���鎖�͂ł��܂���(�d�l)
  wk->gwk.gift_data.data.card.re_deal_count = 0;
  wk->gwk.gift_data.beacon.re_deal_flag = FALSE;
  // ���z�z�ł���u��v��ǉ�
  wk->gwk.gift_data.beacon.groundchild_flag = TRUE;

  CommMysteryStateEnterGiftParent(&wk->gwk, wk->sv, COMM_MODE_MYSTERY);
  
  return NULL;
}


// �S�̔z��̒������ԏ����ȗv�f��Ԃ�
// �����[�N��j��I�Ɉ����܂���
static int getmin(int *p)
{
  int *v = p;
  int val = *p;
  int index = 0;
  if(p[1] < val)	val = p[1], index = 1, v = &p[1];
  if(p[2] < val)	val = p[2], index = 2, v = &p[2];
  if(p[3] < val)	val = p[3], index = 3, v = &p[3];
  *v = 32767*32767;
  return index + 1;
}


//------------------------------------------------------------------
/**
 * @brief	�q�����Ă���l����Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryCardGetConnectCount(MYSTERYCARD_WORK *wk)
{
  int i, max;
  MYSTATUS *my;

  max = 0;
  for(i = 1; i < MYSTERYCARD_OSUSOWAKE_MAX + 1; i++){
    if(CommInfoGetMyStatus(i))
      max++;
  }
  return max;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�q�����Ă���q�@����\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardDispConnectChildStatus(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win)
{
  int i, max, y, redraw;
  u32 id;
  MYSTATUS *my;
  STRBUF *msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  int copy[MYSTERYCARD_OSUSOWAKE_MAX];
  int order[MYSTERYCARD_OSUSOWAKE_MAX];

  // �O��ƌq�����Ă���l���Ⴄ�����ׂ�
  max = 0;
  redraw = 0;
  for(i = 1; i < MYSTERYCARD_OSUSOWAKE_MAX + 1; i++){
    my = CommInfoGetMyStatus(i);
    if(my == NULL){
      if(wk->my[i])	redraw++;
      wk->my[i] = NULL;
      wk->worder[i] = 32767*32767;
    } else if(wk->my[i] != my){
      redraw++;
      max++;
      wk->my[i] = my;
      wk->worder[i] = wk->write_index++;
    } else {
      max++;
    }
  }

  // �ĕ\���̕K�v���Ȃ���΂��̐�̏��������Ȃ�
  if(redraw == 0)
    return max;

  // �\�����Ԃ��m�肷��
  copy[0] = wk->worder[1], copy[1] = wk->worder[2], copy[2] = wk->worder[3], copy[3] = wk->worder[4];
  order[0] = getmin(copy);
  order[1] = getmin(copy);
  order[2] = getmin(copy);
  order[3] = getmin(copy);

  // �ĕ`�悪�K�v�Ȃ�Ε`���Ȃ���
  word = WORDSET_Create(HEAPID_MYSTERYCARD);
  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  y = 0;
  // �E�B���h�E�������āc
  GF_BGL_BmpWinDataFill(win, 0);
  for(i = 0; i < max; i++){
    my = CommInfoGetMyStatus(order[i]);
    if(my){
      // �g���[�i�[����\��
      WORDSET_RegisterPlayerName(word, 0, my);
      msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_osusowake_002, HEAPID_MYSTERYCARD);
      if(MyStatus_GetMySex(my) == PM_MALE)
	GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, y, MSG_NO_PUT, MYSTERYCARD_BLUE, NULL);
      else
	GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, y, MSG_NO_PUT, MYSTERYCARD_RED, NULL);

      STRBUF_Delete(msg);
      // �h�c��\��
      WORDSET_RegisterNumber(word, 0,
			     MyStatus_GetID(my) & 0xFFFF,
			     5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
      msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_osusowake_003, HEAPID_MYSTERYCARD);
      GF_STR_PrintColor(win, FONT_SYSTEM, msg, 80, y, MSG_NO_PUT, MYSTERYCARD_OWHITE, NULL);
      STRBUF_Delete(msg);
      y += MYSTERYCARD_OSUSOWAKE_HEIGHT;
    }
  }
  if(max)	GF_BGL_BmpWinOn(win);
  MSGMAN_Delete(msgman);
  WORDSET_Delete(word);
  return max;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�q�����Ă���l����\��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardDispConnectChildCount(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, int num)
{
  STRBUF * msg;

  wk->entry = num;
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  wk->word = WORDSET_Create(HEAPID_MYSTERYCARD);

  GF_BGL_BmpWinDataFill(win, 0);
  WORDSET_RegisterNumber(wk->word, 0, wk->entry, 1, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, mystery_osusowake_005, HEAPID_MYSTERYCARD);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, MYSTERYCARD_BLACK, NULL);
  GF_BGL_BmpWinOn(win);
  
  STRBUF_Delete(msg);
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�ʐM���I��������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CommMysteryCardExit(MYSTERYCARD_WORK *wk, int *seq, int next)
{
  CommMysteryExitGift();
  WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
  wk->next_seq = next;
  *seq = MYSTERYCARD_SEQ_WAIT_ENDCOMM;
}

// ------------------------------ �����܂� ----------------------------

#define CHECK_OVERLAY
#ifdef CHECK_OVERLAY
FS_EXTERN_OVERLAY(startmenu);
#endif


extern const PROC_DATA MysteryGiftProcData;
static PROC_RESULT MysteryCardProc_End(PROC * proc, int * seq)
{
  int i;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(wk->win[i].ini){
      GF_BGL_BmpWinOff(&wk->win[i]);
      GF_BGL_BmpWinDel(&wk->win[i]);
    }
  }
  if(wk->msgwin.ini) { GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);  }
  if(wk->menuwin.ini){ GF_BGL_BmpWinOff(&wk->menuwin); GF_BGL_BmpWinDel(&wk->menuwin); }

  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_M);
  sys_FreeMemoryEz(wk->bgl);
#ifdef CHECK_OVERLAY
  Main_SetNextProc( FS_OVERLAY_ID(startmenu), &MysteryGiftProcData);
#else
  Main_SetNextProc( NO_OVERLAY_ID, &MysteryGiftProcData);
#endif

  sys_DeleteHeap(HEAPID_COMMICON);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_MYSTERYCARD);
  
  return PROC_RES_FINISH;
}

const PROC_DATA MysteryCardProcData = {
  MysteryCardProc_Init,
  MysteryCardProc_Main,
  MysteryCardProc_End,
  NO_OVERLAY_ID,
};
  


//------------------------------------------------------------------
/**
 * @brief	�J�[�h���󂯎������ɕ\������֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *p, int heapid)
{
  MYSTERYCARD_WORK *wk;

  CommMysteryFunc_BgInit(bgl);

  // �J�[�h�\���ɕK�v�ȃ��[�N�G���A�̐ݒ�
  wk = sys_AllocMemoryLo(heapid, sizeof(MYSTERYCARD_WORK));
  memset(wk, 0, sizeof(MYSTERYCARD_WORK));
  wk->bgl = bgl;
  wk->heapid = heapid;

  /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, wk->heapid);
  
  wk->card[0] = (GIFT_CARD *)p;
  wk->disp_card = 0;

  MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
  sys_FreeMemoryEz(wk);
}


/*  */
