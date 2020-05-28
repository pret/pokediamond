//============================================================================================
/**
 * @file	comm_mystery_figt.c
 * @bfief	�ӂ����ȁ@���������
 * @author	Satoshi Mitsuhara
 * @date	06.05.08
 *
 * $Id: comm_mystery_gift.c,v 1.97 2006/08/12 06:29:26 mitsuhara Exp $
 */
//============================================================================================
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/snd_tool.h"
#include "system/pm_rtc.h"

#include "demo/title.h"
#include "mystery.naix"
#include "msgdata/msg.naix"
#include "msgdata/msg_mystery.h"
#include "msgdata/msg_wifi_system.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "../communication/wh.h"

#include "savedata/fushigi_data.h"
#include "savedata/system_data.h"
#include "savedata/config.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"

#include "comm_mystery_func.h"
#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"
#include "agbdownload.h"
#include "beacondownload.h"

#include "mysterylib.h"

// �e�̃e�X�g����
//#define PARENT_TEST


extern void STRBUF_GetStringCode( const STRBUF* strbuf, STRCODE* ary, u32 arysize );
extern void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *, int heapid);

// ���Q�l�t�@�C��
//  src/field/comm_command_field.h       �ʐM�R�}���h�̃R�}���h���x��
//  src/field/comm_command_field.c       �ʐM�R�}���h�̃R�[���o�b�N�֐��e�[�u��
//  src/field/comm_field_state.c         �ʐM�Ɋ֘A���闬��̐���  
//  src/field/comm_direct_counter.c      �|�P�����Z���^�[�QF�̃J�E���^�[�ŕK�v�ȃ��j���[�Ƃ��̗���

//============================================================================================
//	�萔��`
//============================================================================================

enum {
  MYSTERYGIFT_SEQ_INIT = 0,		/* ��ʊ֌W�̏����� */
  MYSTERYGIFT_SEQ_CREATE_SCREEN,	/* ��ʍ쐬 */
  MYSTERYGIFT_SEQ_WAIT_FADE,		/* �t�F�[�h��҂��� */
  MYSTERYGIFT_SEQ_MAIN,			/* MAIN PROC */
  
  MYSTERYGIFT_SEQ_RECV,			/* �u��������̂��@�����Ƃ�v */
  MYSTERYGIFT_SEQ_DIRECT_YESNO,		/* �_�C���N�g�ő���u�͂��^�������v */

  MYSTERYGIFT_SEQ_RECV_BEACON,		/* �r�[�R�������󂯎�� */

  /* DS�e�@����̃_�E�����[�h�V�[�P���X */
  MYSTERYGIFT_SEQ_START_CHILD,		/* �q�@�Ƃ��ĒʐM�J�n */
  MYSTERYGIFT_SEQ_RECV_YESNO_CHILD,	/* �q�@�F�������f�[�^���󂯎�邩�H */
  MYSTERYGIFT_SEQ_REQEST_CHILD,		/* �q�@�F�e�ɑ΂��Đڑ��v�����o�����^�e�҂� */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1,	/* �q�@�F�e�@����f�[�^����M�����܂ő҂� */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2,	/* �q�@�F��M���ꂽ�f�[�^�̈Í��������� */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3,	/* �q�@�F�����Z�[�u�I���҂� */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30,
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31,
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4,
  MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL,	/* �q�@�F�\�����݂����ۂ��ꂽ�ꍇ */
  MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT,/* �q�@�F�L�����Z���������� */
  MYSTERYGIFT_SEQ_SEND_RECV_CANCEL,	/* �q�@�F�L�����Z������ */

  /* AGB�J�Z�b�g����̃_�E�����[�h�V�[�P���X */
  MYSTERYGIFT_SEQ_AGB_START_CHILD,	/* �q�@�Ƃ��ĒʐM�J�n */
  MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD,	/* �q�@�F�������f�[�^���󂯎�邩�H */
  MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD,	/* �q�@�F�󂯎��邩�`�F�b�N */
  MYSTERYGIFT_SEQ_AGB_REQEST_CHILD,	/* �q�@�F�e�ɑ΂��Đڑ��v�����o�����^�e�҂� */
  MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD,	/* �q�@�F�e�@����f�[�^����M�����܂ő҂� */
  MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2,	/* �q�@�F�����Z�[�u�I���҂� */
  MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD,/* �q�@�F�f�[�^���󂯎�����|��e�@�ɑ��M */
  MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD2,
  
  /* WiFi����̎擾�V�[�P���X */
  MYSTERYGIFT_WIFI_DOWNLOAD_MAIN,	/* WiFi�ʐM */
  
  /* �r�[�R���擾�V�[�P���X */
  MYSTERYGIFT_BEACON_SEQ_INIT,		/* �r�[�R���擾������ */
  MYSTERYGIFT_BEACON_SEQ_WAIT,		/* �r�[�R���擾�@�������Ȃ� */
  MYSTERYGIFT_BEACON_SEQ_TIMER,		/* �r�[�R���擾�� */

  MYSTERYGIFT_BEACON_DOWNLOAD_YESNO,	/* �r�[�R���_�E�����[�h�� */
  MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE,	/* event_name�������Ă���̂�҂� */
  MYSTERYGIFT_BEACON_DOWNLOAD,		/* �r�[�R���_�E�����[�h�� */
  MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE,	/* �Z�[�u�I����҂��Ď��̏����� */
  MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL,	/* �L�����Z������ */
  
  /* �r�[�R���_�E�����[�h�V�[�P���X */
  BEACON_STATE_INIT1,			// �������(�ʐM���C�u��������)
  BEACON_STATE_INIT2,			// �������
  BEACON_STATE_START,			// �J�n����
  BEACON_STATE_SCANNING,		// �X�L������
  BEACON_STATE_DOWNLOAD,		// �e�@�������āA�_�E�����[�h��
  BEACON_STATE_COMPLETE,		// �_�E�����[�h����
  BEACON_STATE_CANCELING,		// �L�����Z��������
  BEACON_STATE_FINISH,			// �_�E�����[�h�I��
  BEACON_STATE_SUCCESS,			// �_�E�����[�h����
  BEACON_STATE_CRCERROR,		// �_�E�����[�h�b�q�b�G���[	
  BEACON_STATE_CANCEL,			// �L�����Z���I��
  BEACON_STATE_ERROR,				// �G���[

  MYSTERYGIFT_ERROR_FULL,		// �z�B���܂��̓J�[�h����t�Ŏ󂯎��Ȃ�
  MYSTERYGIFT_SEQ_DISP_MSG,
  MYSTERYGIFT_SEQ_RETURN_TOPMENU,
  MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK,	// ���z�z�`�F�b�N
  
  MYSTERYGIFT_SEQ_RETURN,		/* �^�C�g���̃��j���[�ɖ߂� */
  MYSTERYGIFT_SEQ_GO_LOOKCARD,		/* �J�[�h������֔�� */

  MYSTERYGIFT_SEQ_LOOP,			/* �������[�v */
  MYSTERYGIFT_SEQ_DISP_CARD,		/* �J�[�h����\������ */
  MYSTERYGIFT_SEQ_FADEOUT_RESET,	/* �t�F�[�h�A�E�g�����Z�b�g */
  
#ifdef PARENT_TEST
  /* �ȉ��A�f�o�b�O�p */
  MYSTERYGIFT_SEQ_START_PARENT,		/* �e�@�F�ʐM�J�n */
  MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING,	/* �e�@�F�q�@�Ƃ̓�����҂� */
  MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT,	/* �e�@�F�q�@�Ƃ̃^�C�~���O���킹 */
  MYSTERYGIFT_SEQ_SENDDATA_PARENT,	/* �e�@�F�f�[�^���M�J�n */
#endif	// PARENT_TEST

  MYSTERYGIFT_SEQ_MAX
};



typedef struct {
  int id;
  u32 param;
} LISTDATA;


#define MYSTERYGIFT_FRAMECHR1	1
#define MYSTERYGIFT_FRAMECHR2	(MYSTERYGIFT_FRAMECHR1 + TALK_WIN_CGX_SIZ)
#define MYSTERYGIFT_WINDOWCHR	(MYSTERYGIFT_FRAMECHR2 + MENU_WIN_CGX_SIZ)
#define MYSTERYGIFT_TOPMENUCHR	(MYSTERYGIFT_WINDOWCHR + 26 * 6)
#define MYSTERYGIFT_COMMTYPECHR	(MYSTERYGIFT_TOPMENUCHR + 16 * 6)
#define MYSTERYGIFT_COMMDIRCHR	(MYSTERYGIFT_COMMTYPECHR + 17 * 8)
#define MYSTERYGIFT_UPWINCHR	(MYSTERYGIFT_COMMDIRCHR + 6 * 4)

#define	FONT_PALNO_NORMAL	0	/* �m�[�}���p���b�g */
#define	FONT_PALNO_SELECT	1	/* �I�����p���b�g */
#define WAKU_PALETTE_NUMBER1	2
#define WAKU_PALETTE_NUMBER2	3
#define	MYSTERYGIFT_BLACK	(GF_PRINTCOLOR_MAKE(1, 2, 15))
#define	MYSTERYGIFT_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static int CommParentStart(PROC *proc);
static int CommChildStart(PROC *proc);
static int CommChildRecvStart(PROC *proc);
static int CommWiFiChildStart(PROC *proc);
static int CommBeaconChildStart(PROC *proc);

static int CommDirectMenuNo(PROC *proc);
static int CommDirectCommMenuNo(PROC *proc);
static int CommDirectMenuYesNo(PROC *proc);
static int CommWiFiMenuYesNo(PROC *proc);
static int CommBeaconMenuYesNo(PROC *proc);
static int CommChildRecvBeaconStart(PROC *proc);
static int CommChildRecvBeaconCancel(PROC *proc);

static int CommTypeMenuRetire(PROC *proc);

static int TopMainMenuRecvGift(PROC *proc);
static int TopMainMenuLookCard(PROC *proc);
static int TopMainMenuRetire(PROC *proc);
static void CreateWindowMenuData(PROC *proc, LISTDATA *ld, int num, GF_BGL_BMPWIN *win, u32 msg);
static void CreateMenuWindow(PROC *proc, int base, u32 msg);

static void DisplaySequence(PROC *proc, GF_BGL_BMPWIN *win, u32 msgid);

static void MysteryGift_BeaconCancel(void);
static void MysteryGiftBeaconProc_Main(MYSTERYGIFT_WORK *wk);
static void MysteryGift_BeaconMainLoop(MYSTERYGIFT_WORK *wk);
static int MysteryGif_DisplayMessage(PROC *proc, GF_BGL_BMPWIN *win, int msgid, int seq);


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
static PROC *MysteryProc;

/* �g�b�v���C�����j���[�p�f�[�^ */
LISTDATA TopMainMenu_MenuData1[] = {
  { mystery_menu_001, (u32)TopMainMenuRecvGift },
  { mystery_menu_002, (u32)TopMainMenuLookCard },
  { mystery_menu_003, (u32)TopMainMenuRetire },
};

/* �ʐM�����I�����j���[�p�f�[�^ */
LISTDATA CommTypeMenu_MenuData[] = {
  { mystery_menu_004, (u32)CommDirectMenuYesNo },
  { mystery_menu_009, (u32)CommBeaconMenuYesNo },
  { mystery_menu_005, (u32)CommWiFiMenuYesNo },
  { mystery_menu_006, (u32)CommTypeMenuRetire },
};

/* �ʐM�����Łu�_�C���N�g�v��I���������̊m�F���j���[ */
LISTDATA CommDirectYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildStart },
#ifndef PARENT_TEST
  { mystery_menu_008, (u32)CommDirectMenuNo },
#else
  // �f�o�b�O�p�ł͐e�@�Ƃ��ċN������
  { mystery_menu_008, (u32)CommParentStart },
#endif
};

/* �_�C���N�g�ʐM���ɐڑ����܂����u�͂��^�������v���j���[ */
LISTDATA CommDirectCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvStart },
  { mystery_menu_008, (u32)CommDirectCommMenuNo },
};



/* �ʐM�����ŁuWiFi������v��I���������̊m�F���j���[ */
LISTDATA CommWiFiYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommWiFiChildStart },
  { mystery_menu_008, (u32)CommDirectMenuNo },
};
/* WiFi�ʐM�ɐڑ����܂����u�͂��^�������v���j���[ */
LISTDATA CommWiFiCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvStart },
  { mystery_menu_008, (u32)NULL },
};



/* �ʐM�����Łu�u���[�h�L���X�g�v��I���������̊m�F���j���[ */
LISTDATA CommBeaconYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommBeaconChildStart },
  { mystery_menu_008, (u32)CommDirectMenuNo },
};
/* �u���[�h�L���X�g�ʐM���Ɍ������f�[�^����M���邩�u�͂��^�������v���j���[ */
LISTDATA CommBeaconCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvBeaconStart },
  { mystery_menu_008, (u32)CommChildRecvBeaconCancel },
};





/* �ėp���j���[�\����(���g�����������čė��p) */
static BMPLIST_HEADER MenuListHeader = {
  NULL,
  MysteryLib_MenuKeyMove,	 	/* �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐� */
  NULL,				     	/* ���\�����Ƃ̃R�[���o�b�N�֐� */
  NULL,					/* BMP�E�B���h�E�f�[�^ */
  0,/* ��Ŗ��߂� */			/* ���X�g���ڐ� */
  3,					/* �\���ő區�ڐ� */
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



#define debug_printf	OS_TPrintf
static int s_state;
static int progress_time;
static void *buffer;


#ifdef PARENT_TEST
//--------------------------------------------------------------------------------------------
/**
 * @brief	�ʐM�f�[�^�̂ł��������֐�
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
#include "gflib/fntsys.h"
#include "msgdata/msg_debug_mitsuhara.h"
static GIFT_COMM_PACK decchi_giftdata;
static GIFT_COMM_PACK *DecchiCreateGiftData(MYSTERYGIFT_WORK *wk)
{
  int i;
  
  GIFT_COMM_PACK *gd = &decchi_giftdata;
  // �ǂ��q�͐^��������_���ł��I
  static STRCODE title[] = { hu_, si_, gi_, na_, o_, ku_, ri_, mo_, no_, TE_, SU_, TO_, de_, su_, CR_,
			     D__, S__, spc_, BA_, bou_, ZI_, YYO_, N_, EOM_, 0 };
  static STRCODE etext[] = { hu_, na_, tu_, ki_, ba_, ni_, spc_, hu_, ru_, bi_, ta_, ka_, i_, zu_, wo_, CR_,
			     mo_, ttu_, te_, i_, ku_, to_, CR_,
			     sa_, i_, ha_, te_, no_, ko_, to_, u_, ni_, spc_, i_, ke_, ru_, zo_, gyoe_, CR_,
			     ya_, se_, i_, no_, MI_, YYU_, U_, ni_, spc_, a_, i_, ni_, i_, ko_, u_, gyoe_,  EOM_, 0 };
  static u8 pokedata[] = {
    0xA6, 0x8A, 0x4E, 0x79, 0x00, 0x00, 0x6F, 0xFD, 0x0F, 0x80, 0xCC, 0x00, 0xE1, 0x4C, 0xEA, 0x2D,
    0x94, 0x1D, 0x47, 0x82, 0xF0, 0xAE, 0x93, 0xCE, 0x7F, 0x0A, 0xE7, 0xA3, 0x67, 0xD3, 0x98, 0x2F,
    0x2B, 0x8A, 0xD9, 0x46, 0xF9, 0xE9, 0xE5, 0x53, 0xC6, 0x18, 0x72, 0xB7, 0x2C, 0x7D, 0x3B, 0x86,
    0x9D, 0x85, 0x49, 0xC1, 0xB6, 0x97, 0xBA, 0x86, 0x2E, 0xA8, 0x19, 0x01, 0x20, 0x07, 0x9D, 0x0B,
    0xFA, 0xFF, 0x89, 0x74, 0xED, 0x8C, 0x68, 0x00, 0xF7, 0x54, 0xB9, 0x92, 0xB3, 0xCF, 0xC4, 0xB8,
    0xA6, 0x84, 0x0A, 0xF3, 0x8C, 0xE3, 0x56, 0x3A, 0x03, 0xB0, 0x08, 0x03, 0x75, 0x49, 0x80, 0x19,
    0x00, 0x85, 0xEE, 0xBF, 0x3F, 0x99, 0x84, 0x21, 0xFD, 0x34, 0x71, 0x40, 0x7D, 0x11, 0x75, 0x07,
    0xA3, 0xCB, 0xAA, 0xDB, 0x1E, 0x60, 0x03, 0xEB, 0x7C, 0xE1, 0x8D, 0x23, 0x60, 0xEE, 0xAD, 0x2E,
    0xA9, 0xEC, 0xBE, 0x26, 0xA1, 0xE5, 0x78, 0x4C, 0x13, 0xF7, 0x29, 0x73, 0xBA, 0x77, 0x92, 0xCB,
    0x58, 0x20, 0x2A, 0x89, 0x06, 0xBB, 0x19, 0x60, 0xA5, 0xDF, 0xE4, 0xD5, 0x6D, 0xFE, 0xDF, 0x0B,
    0xA2, 0x0B, 0x3B, 0xC7, 0xC2, 0xBF, 0xC7, 0x17, 0xC6, 0x5F, 0xB7, 0x4B, 0xD0, 0x38, 0x52, 0x35,
    0xD1, 0xB4, 0x8D, 0x81, 0x60, 0x83, 0x4E, 0x07, 0x82, 0x66, 0x68, 0x1A, 0x8C, 0xF8, 0x38, 0xD8,
    0x70, 0xAF, 0xA3, 0x65, 0x4B, 0xC8, 0x64, 0x6C, 0x0F, 0x6B, 0xE4, 0x85, 0xA0, 0x68, 0xE1, 0x6B,
    0xBA, 0x26, 0x8C, 0x66, 0x7D, 0x34, 0xCA, 0x89, 0x7C, 0xC8, 0x14, 0xDA, 0x71, 0xF8, 0x8C, 0xB3,
    0x44, 0x9F, 0x9E, 0xF1, 0x90, 0x20, 0x51, 0x90, 0xBF, 0xA8, 0x42, 0x5A,
  };
  
  // ��������Ƃ��Ă��邽�߂ɏ�����
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  wk->word = WORDSET_Create(HEAPID_MYSTERYGIFT);

  MI_CpuClear8(gd, sizeof(GIFT_COMM_PACK));
  // �|�P�����f�[�^���R�s�[(PokemonParam)
  for(i = 0; i < sizeof(pokedata); i++)
    gd->data.deli.data.pokemon.data[i] = pokedata[i];

  // ����ȊO�̃f�[�^�Z�b�g
  memcpy(gd->beacon.event_name, title, GIFT_DATA_CARD_TITLE_MAX*2);
  
  gd->beacon.version = (1 << VERSION_DIAMOND) | (1 << VERSION_PEARL) | (1 << VERSION_DP_NEXT);// �Ώۃo�[�W����
  gd->beacon.only_one_flag = 0;			// �P�x�����z�M�t���O
  gd->beacon.access_point = 0;			// �A�N�Z�X�|�C���g(���g�p)
  gd->beacon.have_card = 1;			// �J�[�h�����܂�ł��邩
  gd->beacon.delivery_flag = 1;			// �z�B������󂯎����̂��܂�ł��邩

  // �J�[�h���̂ł�������
  gd->data.card.re_deal_count = 128; 		// �Ĕz�z�̉�(0�`254�A255�͖�����)
  gd->data.card.pokemon_icon[0] = 1;		// �|�P�����A�C�R���R��
  gd->data.card.pokemon_icon[1] = 151;		// �|�P�����A�C�R���R��
  gd->data.card.pokemon_icon[2] = 250;		// �|�P�����A�C�R���R��

  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKEMON;	// �|�P����
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKEEGG;	// �^�}�S
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_ITEM;	// �ǂ���
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_RULE;	// ���[��
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_GOODS;	// �O�b�Y
  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;	// �A�N�Z�T��
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_RANGEREGG;	// �}�i�t�B�[�̃^�}�S
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_MEMBERSCARD;	// �����o�[�Y�J�[�h
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_LETTER;	// �I�[�L�h�̂Ă���
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_WHISTLE;	// �Ă񂩂��̂ӂ�
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKETCH;	// �|�P�b�`
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_CLEAR;	// �ӂ����̈�̋����N���A


  gd->beacon.event_id = gd->data.deli.gift_type + 100;	// �C�x���g�h�c

  // ���܂�������������^�}�S�ݒ�
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_POKEEGG){
    u8 tamago = 1;
    POKEMON_PARAM *pp = (POKEMON_PARAM *)gd->data.deli.data.pokemon.data;
    PokeParaPut(pp, ID_PARA_tamago_flag, &tamago);
  }

  // �A�C�e������
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_ITEM){
    gd->data.deli.data.item.itemNo = 80;
  }

  // ���M�����[�V����
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_RULE){
    REGULATION _dummycup = {
      {EOM_}, // gmm����Ƃ��Ă���
      80,//���x���̍��v�W�O�܂�
      3,//�R�C
      30,//�|�P�����̃��x���R�O�܂�
      -20,//�g�������Q�D�O������
      -20,// �̏d�����Q�O��������
      0,// �i���|�P�����Q���ł��Ȃ�
      0,// ���ʂȃ|�P�����Q���ł��Ȃ�
      0,// �����|�P�����Q���ł��Ȃ�
      0,// ��������������Ȃ�
      0,// �Œ�_���[�W�Z���K�����s
    };
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_mitsuhara_dat, HEAPID_MYSTERYGIFT);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_regulation_dummy );
    //    gd.gift_type = MYSTERYGIFT_TYPE_RULE;
    Regulation_SetCupName(&_dummycup,pStr);
    MI_CpuCopy8(&_dummycup, &gd->data.deli.data, sizeof(REGULATION));
    MSGMAN_Delete(msgman);
    STRBUF_Delete(pStr);
  }

  // �O�b�Y
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_GOODS){
    gd->data.deli.data.goods.goodsNo = 33;
  }

  // �A�N�Z�T��
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_ACCESSORY){
    gd->data.deli.data.accessory.accType = MYSTERYGIFT_ACCTYPE_SEAL;
    gd->data.deli.data.accessory.accNo = 79;//�����V�[��
  }

  // �|�P�b�`
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_POKETCH){
    gd->data.deli.data.poketch.id = 1; //POKETCH_APPID_STOPWATCH
  }

  // �ӂ����̈�̋����N���A
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_CLEAR){
    gd->beacon.version  = 0xFFFFFFFF;
    gd->beacon.event_id = 0xFFFF;
  }


  
  // �o���オ�����r�[�R���f�[�^��{�̂ɂ��R�s�[���Ă���(�Ĕz�z�p)
  memcpy(&gd->data.card.beacon, &gd->beacon, sizeof(GIFT_BEACON));

  // �C�x���g���̃R�s�[
  memcpy(gd->data.card.event_text, etext, GIFT_DATA_CARD_TEXT_MAX*2);
  // ��n��
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);

#ifdef DEBUG_ONLY_FOR_mituhara
  // �f�o�b�K�Ńo�C�i�����o�͂�����AGB-ROM����邽�߂̃A�h���X�\��
  OS_TPrintf("�ł��������f�[�^�F0x%08X - 0x%08X\n", &decchi_giftdata, (u32)&decchi_giftdata + sizeof(GIFT_COMM_PACK));
  OS_TPrintf("                  %dbytes\n", sizeof(GIFT_COMM_PACK));
#endif
  
  return gd;
}
#endif	// PARENT_TEST

//------------------------------------------------------------------
/**
 * @brief	�^�C���A�C�R����ON/OFF
 * @param	flag: TRUE �\���@FALSE ��\��
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetTimeWaitIcon(MYSTERYGIFT_WORK *wk, int flag)
{
  if(flag == TRUE){
    if(wk->time_icon == NULL){
      wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYGIFT_FRAMECHR1);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("--- �^�C���A�C�R��: ON\n");
#endif
    }
  } else {
    if(wk->time_icon){
      TimeWaitIconDel(wk->time_icon);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("--- �^�C���A�C�R��: OFF\n");
#endif
    }
    wk->time_icon = NULL;
  }
}
void SetTimeWaitIconEx(MYSTERYGIFT_WORK *wk, int flag)
{
  SetTimeWaitIcon(wk, flag);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	���̃��j���[��ʂ̍ŏI��n��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void TopMainMenuFinish(PROC *proc)
{
  int i;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  MysteryLib_RemoveClact();

  
  if(wk->bmd)		BMP_MENULIST_Delete(wk->bmd);
  if(wk->lw)		BmpListExit(wk->lw, NULL, NULL);
  GF_BGL_BmpWinOff(&wk->msgwin); GF_BGL_BmpWinDel(&wk->msgwin);
  if(GF_BGL_BmpWinAddCheck(&wk->upwin)){
    GF_BGL_BmpWinOff(&wk->upwin); GF_BGL_BmpWinDel(&wk->upwin);
  }
  for(i = 0; i < MYSTERYGIFT_WIN_MAX; i++){
    if(wk->selwin[i].ini){
      GF_BGL_BmpWinOff(&wk->selwin[i]);
      GF_BGL_BmpWinDel(&wk->selwin[i]);
    }
  }
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_S);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_S);
  sys_FreeMemoryEz(wk->bgl);
}

// *******************************************************************************************


//** CharManager PlttManager�p **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)


static void VBlankFunc( void * work )
{
  // �Z���A�N�^�[Vram�]���}�l�[�W���[���s
  DoVramTransferManager();
  // �����_�����LOAM�}�l�[�W��Vram�]��
  REND_OAMTrans();	
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(MYSTERYGIFT_WORK *wk)
{
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_cur_00_lz_ccgr,
		       NARC_mystery_fusigi_cur_nclr,
		       NARC_mystery_fusigi_cur_00_lz_ccer,
		       NARC_mystery_fusigi_cur_00_lz_canr,
		       GF_BGL_MAIN_DISP);
}


//------------------------------------------------------------------
/**
 * @brief	�I���^��߂�y��I�u�W�F�N�g�̓o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetBaseIcon(MYSTERYGIFT_WORK *wk, int anum)
{
  if(anum != -1){
    wk->arrow = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->arrow, HW_LCD_WIDTH/2, 100, anum);
  } else {
    CLACT_SetDrawFlag(wk->arrow, 0);
  }
}



// *******************************************************************************************


#ifdef PARENT_TEST
//--------------------------------------------------------------------------------------------
/**
 * @brief	�e�@�Ƃ��ĒʐM�J�n
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommParentStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  SAVEDATA *sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;

  // ����f�[�^�̂ł�������
  GIFT_COMM_PACK *gd = DecchiCreateGiftData(wk);
  // MYSTERYGIFT_WORK�փf�[�^���Z�b�g
  memcpy(&wk->gift_data, gd, sizeof(GIFT_COMM_PACK));
  
  CommMysteryStateEnterGiftParent(wk, sv, COMM_MODE_MYSTERY);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_Printf("�e�Ƃ��ĒʐM�J�n\n");
#endif
  return MYSTERYGIFT_SEQ_START_PARENT;
}
#endif	// PARENT_TEST


// *******************************************************************************************


//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�����݂���΃N���A����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CMG_BmpMenuWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpMenuWinClear(win, trans_sw);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�q�@�Ƃ��ĒʐM�J�n
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE){
    /* �u��������́@���@�������Ă��܂�\n���΂炭�@���܂��@���������c�c�v */
    DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  }
  /* �u�͂��^�������v�̃��j���[�E�B���h�E�͂���������� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("�q�Ƃ��ĒʐM�J�n\n");
#endif
  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE){
    CommMysteryStateEnterGiftChild(wk, COMM_MODE_MYSTERY);
    // �^�C���A�E�g���Ԃ�ݒ�
    wk->timeout = MYSTERYGIFT_TIMEOUT;
    // �ʐM�A�C�R���\��
    WirelessIconEasy();
    // �^�C���A�C�R���\��
    SetTimeWaitIcon(wk, TRUE);
    return MYSTERYGIFT_SEQ_START_CHILD;
  } else {
    OS_TPrintf("AGB�J�[�g���b�W����̓]�� \n");
    return MYSTERYGIFT_SEQ_AGB_START_CHILD;
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	��������̂���M����Ɗm�肵�����̓���(�q�@)
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildRecvStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  // �_�C���N�g�ʐM�̏ꍇ�͂����Ńo�[�W�����Ⴂ���`�F�b�N
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION)
    return MYSTERYGIFT_ERROR_FULL;
  
  // �z���g�Ɏ󂯎��邩�`�F�b�N���s��
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT ||	/* �z�B������t */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD ||	/* �J�[�h����t */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		/* ��x�����󂯎��Ȃ� */
    return MYSTERYGIFT_ERROR_FULL;

  // ���z�z�̏ꍇ�̓z���g�Ɏ󂯎��́H�`�F�b�N���s��
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_GROUNDCHILD){
    /* mituhara; */
    return MYSTERYGIFT_ERROR_FULL;
  }

  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommMysteryStateConnectGiftChild(wk->connectIndex);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("�e�ɑ΂��Đڑ��v�����o���܂���\n");
#endif  
  }
  // �u���������݂��@���܂���\n���΂炭�@���܂����������c�v
  DisplaySequence(proc, &wk->msgwin, mystery_01_007);
  /* �u�͂��^�������v�̃��j���[�E�B���h�E�͂���������� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);

  // �󂯎��I�u�W�F�N�g�̕\��(Wi-Fi�̏ꍇ�͏u�ԓI�ɂ����\������Ȃ��̂ŁA���������\�����Ȃ�)
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    SetBaseIcon(wk, 0);
    SetTimeWaitIcon(wk, TRUE);
  }

  // �󂯎����@�������ɕς�邽�߁A�V�[�P���X����
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
    return MYSTERYGIFT_SEQ_REQEST_CHILD;
  } else {
    return MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD;
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^���Z�[�u�\���̂ɃZ�b�g
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static GIFT_DELIVERY *CommSetSaveData(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GIFT_DATA *gdata = &wk->gift_data.data;
  GIFT_BEACON *beacon = &wk->gift_data.beacon;
  GIFT_COMM_PACK *gcp;

  switch(wk->comm_type){
  case MYSTERYCOMM_TYPE_DIRECT:
    memcpy(gdata, CommGetMysteryGiftRecvBuff(0, NULL, 0), sizeof(GIFT_DATA));
    /* ��M�����f�[�^�̈Í���decode */
    MysteryLib_DecodeCryptoData(&wk->gift_data, &wk->gift_data.data, HEAPID_MYSTERYGIFT);
    break;
  case MYSTERYCOMM_TYPE_BEACON:
    gcp = (GIFT_COMM_PACK *)wk->recvbuf;
    memcpy(gdata, &gcp->data, sizeof(GIFT_DATA));
#if 0
    memcpy(beacon, &gcp->data.card.beacon, sizeof(GIFT_BEACON));
#else
    memcpy(beacon, &gcp->beacon, sizeof(GIFT_BEACON));
#endif
    break;
  }
  return &gdata->deli;
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
  MYSTERYGIFT_WORK *wk = (MYSTERYGIFT_WORK *)p;
  if(wk->save_cancel == TRUE){
    // �Z�[�u���L�����Z�����ꂽ
    wk->func_hook = NULL;
  }
  ret = MysteryLib_SaveDSCard();
  if(ret == SAVE_RESULT_OK || ret == SAVE_RESULT_NG){
    Snd_SePlay(SEQ_SE_DP_SAVE);
    //    OS_TPrintf("�����Z�[�u���I�����܂���\n");
    wk->func_hook = NULL;
  }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�͂����f�[�^���Z�[�u�̈�֓o�^����
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CommChildSaveRecvData(PROC *proc)
{
  int type, ret;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GIFT_BEACON *beacon = &wk->gift_data.beacon;
  GIFT_DATA *gdata = &wk->gift_data.data;
  SAVEDATA *sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  FUSHIGI_DATA *fdata;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�J�[�h���:\t%d\n", beacon->have_card);
  OS_TPrintf("�|�P�����A�C�R��:\t%3d : %3d : %3d\n",
	     gdata->card.pokemon_icon[0], gdata->card.pokemon_icon[1], gdata->card.pokemon_icon[2]);
#endif
  
  if(beacon->have_card == 0){
    type = MYSTERYGIFT_DELIVERY;
  } else {
    RTCDate date;
    type = MYSTERYGIFT_CARD;
    /* �Ĕz�z�����񐔂����Z�b�g */
    gdata->card.re_dealed_count = 0;	//gdata->card.re_deal_count;
    /* �������Ĕz�z�\�t���O���Q�Ă�����񐔂����Z�b�g */
    if(beacon->re_deal_flag == FALSE)
      gdata->card.re_deal_count = 0;
    /* �Z�[�u������t������ */
    GF_RTC_GetDate(&date);
    gdata->card.recv_date = RTC_ConvertDateToDay(&date);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("%4d�N%2d��%2d�� -> %08X\n", date.year, date.month, date.day, gdata->card.recv_date);
#endif
  }

  // �ӂ����f�[�^�̃|�C���^�𓾂�
  fdata = SaveData_GetFushigiData(sv);
  // �C�x���g�ԍ��t���O�𗧂Ă�
  FUSHIGIDATA_SetEventRecvFlag(fdata, beacon->event_id);
  // �Z�[�u�G���A�Ƀf�[�^���Z�b�g
  if(type == MYSTERYGIFT_DELIVERY){
    ret = FUSHIGIDATA_SetDeliData(fdata, (const void *)gdata, 0);
  } else {
    ret = FUSHIGIDATA_SetCardData(fdata, (const void *)gdata);
  }
  // �Z�[�u�V�[�P���X��o�^
  MysteryLib_InitSaveDSCard(sv);
  wk->save_cancel = FALSE;
  wk->func_hook = SaveSequence;
}




//--------------------------------------------------------------------------------------------
// ���_�C���N�g�ʐM�Łu�͂��^�������v��I������E�B���h�E

//--------------------------------------------------------------------------------------------
/**
 * @brief	�_�C���N�g�ʐM���Ɍ��������e�Ɛڑ����邩�u�͂��^�������v
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateDirectCommYesNoMenu(PROC *proc, int flag)
{
  int msg;
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(flag == 0)	msg = mystery_01_005;
  else		msg = -1;
  
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommDirectCommYesNoMenu_MenuData, NELEMS(CommDirectCommYesNoMenu_MenuData), win, msg);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}



//--------------------------------------------------------------------------------------------
// ���ʐM���@�Ń_�C���N�g�ʐM��I�������ۂ̊m�F�E�B���h�E

//--------------------------------------------------------------------------------------------
/**
 * @brief	�_�C���N�g�ʐM���܂����H�Łu�������v��I��
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommDirectMenuNo(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    SetTimeWaitIcon(wk, FALSE);	// �^�C���A�C�R������
  }

  WirelessIconEasyEnd();
  return TopMainMenuRecvGift(proc);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�_�C���N�g�ʐM���܂����H�u�͂��^�������v
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int CommDirectMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE)
    wk->comm_type = MYSTERYCOMM_TYPE_DIRECT;
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* ���j���[������������ */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommDirectYesNoMenu_MenuData, NELEMS(CommDirectYesNoMenu_MenuData), win, mystery_01_003);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	WiFi�_�E�����[�h�ʐM���܂����H�u�͂��^�������v
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int CommWiFiMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->comm_type = MYSTERYCOMM_TYPE_WIFI;
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* ���j���[������������ */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommWiFiYesNoMenu_MenuData, NELEMS(CommWiFiYesNoMenu_MenuData), win, mystery_wifi_001);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}





//--------------------------------------------------------------------------------------------
/**
 * @brief	�u���[�h�L���X�g�ʐM���܂����H�u�͂��^�������v
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int CommBeaconMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->comm_type = MYSTERYCOMM_TYPE_BEACON;
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* ���j���[������������ */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommBeaconYesNoMenu_MenuData, NELEMS(CommBeaconYesNoMenu_MenuData), win, mystery_broadcast_001);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�u���[�h�L���X�g�ʐM���Ɍ������f�[�^����M���邩�u�͂��^�������v���j���[
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateBeaconCommYesNoMenu(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommBeaconCommYesNoMenu_MenuData, NELEMS(CommBeaconCommYesNoMenu_MenuData), win, mystery_01_005);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�݂������f�[�^�����サ�񂵂܂����Łu�������v
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommDirectCommMenuNo(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
  WirelessIconEasyEnd();
  /* �_�C���N�g�ʐM�̏ꍇ�͒ʐM��H��؂� */
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommMysteryExitGift();
  }
  return TopMainMenuRecvGift(proc);
}


//------------------------------------------------------------------
/**
 * @brief	�u���[�h�L���X�g�ʐM�J�n
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommBeaconChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  /* �u��������́@���@�������Ă��܂�
     �@���΂炭�@���܂��@���������c�c�v */
  DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  /* �u�͂��^�������v�̃��j���[�E�B���h�E�͂���������� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  // �^�C���A�C�R���\��
  SetTimeWaitIcon(wk, TRUE);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�r�[�R�������擾����\n");
#endif
  s_state = BEACON_STATE_INIT1;
  return MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	��������̂��r�[�R�������M����Ɗm�肵�����̓���
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildRecvBeaconStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  OS_TPrintf("�G���[�ԍ��� %d\n", wk->gift_error);

  
  // �z���g�Ɏ󂯎��邩�`�F�b�N���s��
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT ||	/* �z�B������t */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD ||	/* �J�[�h����t */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		/* ��x�����󂯎��Ȃ� */
    return MYSTERYGIFT_ERROR_FULL;

  /* �u�͂��^�������v�̃��j���[�E�B���h�E�͂���������� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);

  // �󂯎��I�u�W�F�N�g�̕\��
  SetBaseIcon(wk, 1);

  /* ��������́@���@���サ�񂿂イ�@�ł�\n�ł񂰂���@����Ȃ��Ł@���������c�c */
  DisplaySequence(proc, &wk->msgwin, mystery_01_008);
  return MYSTERYGIFT_BEACON_DOWNLOAD;
}


//------------------------------------------------------------------
/**
 * @brief	��������̂��󂯎��Ȃ��Ɗm�肵���Ƃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommChildRecvBeaconCancel(PROC *proc)
{
  if(s_state == BEACON_STATE_SCANNING || s_state == BEACON_STATE_DOWNLOAD || s_state == BEACON_STATE_ERROR){
    if(bsdown_end()){
      s_state = BEACON_STATE_CANCELING;	
    }
  }
  return MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL;
}




//--------------------------------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	WiFi������ʐM�J�n
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommWiFiChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  /* �u��������́@���@�������Ă��܂�
     �@���΂炭�@���܂��@���������c�c�v */
  DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  SetTimeWaitIcon(wk, TRUE);
  /* �u�͂��^�������v�̃��j���[�E�B���h�E�͂���������� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  // �^�C���A�C�R���\��
  SetTimeWaitIcon(wk, TRUE);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("WiFi�ʐM���J�n���܂�\n");
#endif

  wk->wifi_dl_seq = WIFI_MYSTERYGIFT_BASE;
  wk->wifi_check_func = NULL;
  return MYSTERYGIFT_WIFI_DOWNLOAD_MAIN;
}






//--------------------------------------------------------------------------------------------
// ���ʐM���@�I�����j���[�̏���

//--------------------------------------------------------------------------------------------
/**
 * @brief	�ʐM�����I�����j���[�Łu���ǂ�v��I��
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int CommTypeMenuRetire(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* ���C�����j���[��\�� */
  CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
  return MYSTERYGIFT_SEQ_MAIN;
}



//--------------------------------------------------------------------------------------------
// ���g�b�v���C�����j���[�̏���

//--------------------------------------------------------------------------------------------
/**
 * @brief	��ԍŏ��̑I����ʂŁu��������̂��@�����Ƃ�v��I��
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuRecvGift(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  SYSTEMDATA *sysdata;
  //  LISTDATA ld[4];
  //  int width, max = 0;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(wk->sv);

  /* �r�[�R���擾�������~ */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER){
    wk->beacon_wait = 1;
    MysteryGiftBeaconProc_Main(wk);
  }
  
  /* ���̃��j���[�E�B���h�E��\�������Ȃ� */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_MAIN], WINDOW_TRANS_ON);
  /* ���j���[������������ */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE];
#if 0
  // ��Ԃɂ���ă��j���[�̍��ڂƑ傫����ω�������^�C�v(�ς��Ȃ��Ȃ����c)
  width = 16;
  // �ŏ��̃��j���[�͕K�{
  ld[max++] = CommTypeMenu_MenuData[0];
  // �ӂ����Ȃ�������̂��J������t���I�[�v���ƂȂ�܂���
  ld[max++] = CommTypeMenu_MenuData[1];
  ld[max++] = CommTypeMenu_MenuData[2];

  // �Ō���K�{
  ld[max++] = CommTypeMenu_MenuData[3];
#endif
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 15, 9, 16, 8,
		     FONT_PALNO_NORMAL, MYSTERYGIFT_COMMTYPECHR);
  CreateWindowMenuData(proc, CommTypeMenu_MenuData, 4, win, mystery_01_002);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_RECV;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	��ԍŏ��̑I����ʂŁu�J�[�h���@�݂�v��I��
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuLookCard(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  /* �r�[�R���擾�������~ */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER){
    wk->beacon_wait = 1;
    MysteryGiftBeaconProc_Main(wk);
  }
  /* MYSTERYGIFT_SEQ_WAIT_FADE �� MYSTERYGIFT_SEQ_WAIT_RETURN */
  MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_GO_LOOKCARD, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
  return -1;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	��ԍŏ��̑I����ʂŁu��߂�v��I��
 * @param	NONE
 * @return	���̃V�[�P���X�ԍ�
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuRetire(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  /* �r�[�R���擾���ł���ΏI�������� */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER)
    wk->beacon_wait = 1;

  /* MYSTERYGIFT_SEQ_WAIT_FADE �� MYSTERYGIFT_SEQ_WAIT_RETURN */
  MysteryLib_ChangeFadeType(1);
  MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_RETURN, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
  return -1;
}


//--------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------
/**
 * @brief	BG������
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInitSub(GF_BGL_INI *ini, int frame, u32 scrbase, u32 scrchar)
{
  GF_BGL_BGCNT_HEADER MBg_Data = {
    0, 0, 0x800, 0,
    GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
    GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
    GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
  };
  MBg_Data.screenBase = scrbase / 0x0800;
  MBg_Data.charBase = scrchar / 0x4000;
  GF_BGL_BGControlSet(ini, frame, &MBg_Data, GF_BGL_MODE_TEXT );
  GF_BGL_ScrClear(ini, frame);
}
static void BgInit( GF_BGL_INI * ini )
{
  /* BG SYSTEM */
  GF_BGL_SYS_HEADER BGsys_data = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };
  GF_BGL_InitBG( &BGsys_data );
  BgInitSub(ini, GF_BGL_FRAME0_M, 0xF000, 0x0000); /* MAIN DISP BG0 */
  BgInitSub(ini, GF_BGL_FRAME1_M, 0xF800, 0x8000); /* MAIN DISP BG1 */
  BgInitSub(ini, GF_BGL_FRAME0_S, 0x3800, 0x0000); /* SUB DISP BG0 */
  BgInitSub(ini, GF_BGL_FRAME1_S, 0x7800, 0x4000); /* SUB DISP BG1 */
}


//------------------------------------------------------------------
/**
 * @brief	�w�i�O���t�B�b�N�X�̓o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateBgScreenSub(GF_BGL_INI * ini)
{
  // �T�u��ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2, HEAPID_MYSTERYGIFT);
  // �T�u���BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_S, 0, 10*16*0x20, 1, HEAPID_MYSTERYGIFT);
  // �T�u��ʃX�N���[���P
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, ini,
		  GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_MYSTERYGIFT);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_S, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_S);
}

static void CreateBgScreen(GF_BGL_INI * ini)
{
  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*8, 16*2, HEAPID_MYSTERYGIFT);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_M, 0, 10*16*0x20, 1, HEAPID_MYSTERYGIFT);
  // ���C����ʃX�N���[���P
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, ini,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_MYSTERYGIFT);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_M, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_M);

  // ������ʂ̊i�q�͗l
  CreateBgScreenSub(ini);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[��o�^����ėp�֐�
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateWindowMenuData(PROC *proc, LISTDATA *ld, int num, GF_BGL_BMPWIN *win, u32 msg)
{
  int i;
  BMPLIST_HEADER list_h;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->bmd)	BMP_MENULIST_Delete(wk->bmd);
  /* ���j���[�̕������o�^ */
  wk->bmd = BMP_MENULIST_Create(num,HEAPID_MYSTERYGIFT);
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  for(i = 0; i < num; i++)
    BMP_MENULIST_AddArchiveString(wk->bmd, wk->msgman, ld[i].id, ld[i].param);
  MSGMAN_Delete(wk->msgman);
  /* desc�쐬 �� �ύX �� �o�^ */
  list_h = MenuListHeader;
  list_h.list = wk->bmd;
  list_h.count = list_h.line = num;
  list_h.win = win;
  if(wk->lw) 	BmpListExit(wk->lw, NULL, NULL);
  wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_MYSTERYGIFT);
  /* ���b�Z�[�W�E�B���h�E�Ƀ��b�Z�[�W�\�� */
  if(msg != -1)
    DisplaySequence(proc, &wk->msgwin, msg);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	���j���[��\������
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateMenuWindow(PROC *proc, int base, u32 msg)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GF_BGL_BMPWIN *win;
  LISTDATA ld[4];
  int i, index = 0;
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(wk->sv);
  win = &wk->selwin[MYSTERYGIFT_WIN_MAIN];
  // �K�v�ȃ��j���[�݂̂��R�s�[
  ld[index++] = TopMainMenu_MenuData1[0];
  if(FUSHIGIDATA_IsExistsCardAll(fdata))
    ld[index++] = TopMainMenu_MenuData1[1];
  ld[index++] = TopMainMenu_MenuData1[2];
  // �E�B���h�E�o�^
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 8,  7, 16, index*2, FONT_PALNO_NORMAL, base);
  // ���j���[�쐬
  CreateWindowMenuData(proc, ld, index, win, msg);
  // �E�B���h�E�\��
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�փ��b�Z�[�W�̕\��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	msgid	���b�Z�[�W��ID
 */
//--------------------------------------------------------------------------------------------
static void DisplaySequence(PROC *proc, GF_BGL_BMPWIN *win, u32 msgid)
{
  STRBUF * msg;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  wk->word = WORDSET_Create(HEAPID_MYSTERYGIFT);

  /*�E�B���h�E�g����h��Ԃ�(�����F) */
  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_TALK, FONT_HEADER_B_COLOR));
  if(wk->msg)
    msg = wk->msg;
  else
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, msgid, HEAPID_MYSTERYGIFT);

  wk->m_id = GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, wk->msg_wait, MYSTERYGIFT_BLACK, NULL);
  if(wk->msg == NULL)
    STRBUF_Delete(msg);
  /*�E�B���h�E�g�`��(��b�p�E�B���h�E���g�p) */
  BmpTalkWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR1, WAKU_PALETTE_NUMBER1);
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);
  wk->msg_wait = MSG_NO_PUT;
}
static void DisplaySequenceDirect(PROC *proc, GF_BGL_BMPWIN *win, STRCODE *msgcode)
{
  STRBUF *msg;

  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  msg = STRBUF_Create( GIFT_DATA_CARD_TITLE_MAX+1, HEAPID_MYSTERYGIFT );
  STRBUF_SetStringCodeOrderLength(msg, msgcode, GIFT_DATA_CARD_TITLE_MAX);
  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
  GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, 0, MSG_NO_PUT, MYSTERYGIFT_BLACK, NULL);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  STRBUF_Delete(msg);
}
static BOOL DisplaySequenceEndCheck(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  if(GF_MSG_PrintEndCheck(wk->m_id) == 0)
      return TRUE;
  return FALSE;
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
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
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
      func = (static int (*)(PROC *))ret;
      ret_seq = func(proc);
      if(ret_seq != -1)
	*seq = ret_seq;
    }
    break;
  }
}


//--------------------------------------------------------------------------------------------
// �ȉ��A�g�ݍ��킹���Ȃ������֐��������\��


//------------------------------------------------------------------
/**
 * @brief	�O���t�B�b�N�X�f�[�^������
 */
//------------------------------------------------------------------
static BOOL MysteryGift_InitGraphicsData(PROC *proc, MYSTERYGIFT_WORK *wk)
{
  int type;

  MSG_PrintInit();
  /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYGIFT);
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_SELECT * 32, HEAPID_MYSTERYGIFT);
  /*�E�B���h�E�g�L�����A�p���b�g���Z�b�g */
  type = CONFIG_GetWindowType(wk->cfg);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYGIFT_FRAMECHR1, WAKU_PALETTE_NUMBER1, type, HEAPID_MYSTERYGIFT);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2, 1, HEAPID_MYSTERYGIFT);
  /* �����߂�Ȃ����R�[�h(�p���b�g�O�J���[�O�̐F���ł�������) */
  *((u16 *)HW_BG_PLTT) = RGB(12, 12, 31);
  /* �����b�Z�[�W��\������E�B���h�E */
  if(!GF_BGL_BmpWinAddCheck(&wk->msgwin))
    GF_BGL_BmpWinAdd(wk->bgl, &wk->msgwin, GF_BGL_FRAME0_M, 2, 19, 27, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_WINDOWCHR);
  DisplaySequence(proc, &wk->msgwin, mystery_01_001); /* �u�ӂ����ȁ@��������́@�ց@�悤�����I�v */
  /* ���j���[��\������E�B���h�E �u�ӂ����ȁ@��������́@�ց@�悤�����I�v */
  CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
  CreateBgScreen(wk->bgl);
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	WiFi�_�E�����[�h���C������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
extern int WifiMysteryGift_Main(PROC *proc, int *seq);
static void WiFi_MysteryGitft_Main(PROC *proc, int *seq)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  switch(WifiMysteryGift_Main(proc, &wk->wifi_dl_seq)){
  case ND_RESULT_EXECUTE:		// ���s��
    break;
  case ND_RESULT_COMPLETE:		// ����_�E�����[�h�I��
    memcpy(&wk->gift_data, wk->filebuffer, sizeof(GIFT_COMM_PACK));
    SetTimeWaitIcon(wk, FALSE);
    wk->from_seq = MYSTERYGIFT_WIFI_DOWNLOAD_MAIN;
    *seq = MYSTERYGIFT_SEQ_AGB_START_CHILD;
    /* �V�[�P���X�ύX */
    break;
  case ND_RESULT_NOT_FOUND_FILES:	// �t�@�C����������Ȃ�����
  case ND_RESULT_DOWNLOAD_CANCEL:	// ���[�U�[����L�����Z�����ꂽ
    SetTimeWaitIcon(wk, FALSE);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    break;
  case ND_RESULT_DOWNLOAD_ERROR:	// �Ȃ�炩�̃G���[���N����
    GF_BGL_BmpWinOff(&wk->wifiwin);
    GF_BGL_BmpWinDel(&wk->wifiwin);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME0_M);
    /* ���C�����j���[��\�� */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
    *seq = MYSTERYGIFT_SEQ_MAIN;
    break;
  }
}

//------------------------------------------------------------------
/**
 * @brief	Wi-Fi�ŒʐM�֕��A�s�\�ȃG���[���N�����ꍇ�̏���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void WifiMysteryGift_ErrorDisp(MYSTERYGIFT_WORK *wk)
{
  WORDSET *word;
  MYSTERY_WIN mw;
  int msg;

  if(wk->wifi_errmsg != -1)	msg = dwc_error_0001 + wk->wifi_errmsg;
  else				msg = dwc_error_0012;

  // OBJ��ʂ͔�\��
  GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
  // �X�N���[�����N���A���āc
  GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME0_M);
  // �G���[�ԍ���word�փZ�b�g����
  word = WORDSET_Create(HEAPID_MYSTERYGIFT);
  WORDSET_RegisterNumber(word, 0, wk->wifi_errcode, 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  // �E�B���h�E������ĕ\��
  MysteryLib_WinInit1(&mw, &wk->wifiwin, FONT_PALNO_SELECT, NARC_msg_wifi_system_dat, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  MysteryLib_WinInit2(&mw, 24, 16, 100);
  MysteryLib_WinInit3(&mw, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  mw.word = word;
  MysteryLib_CreateWin(wk->bgl, &mw, 4, 4, msg);
  WORDSET_Delete(word);
}


//------------------------------------------------------------------
/**
 * @brief	�z�B���܂��̓J�[�h����t�ł�������̂��󂯎��Ȃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryGift_FullError(PROC *proc)
{
  int msg;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT)		msg = mystery_err_001;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD)	msg = mystery_err_005;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		msg = mystery_err_002;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION)	msg = mystery_err_007;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_GROUNDCHILD){
    msg = mystery_01_010;
    return MysteryGif_DisplayMessage(proc, &wk->msgwin, msg, MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK);
  }
  
  return MysteryGif_DisplayMessage(proc, &wk->msgwin, msg, MYSTERYGIFT_SEQ_RETURN_TOPMENU);
}


//------------------------------------------------------------------
/**
 * @brief	�s�X�V�t�����b�Z�[�W�̕\������
 * @param	NONE
 * @return	NONE
 * ���\�� wk->msg_next_seq �ɏI����̃V�[�P���X�����Ă�����
*/
//------------------------------------------------------------------
static int MysteryGif_DisplayMessage(PROC *proc, GF_BGL_BMPWIN *win, int msgid, int next_seq)
{
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(win && msgid){
    // �\�����I������܂�msg�o�b�t�@��ۏႹ�˂΂Ȃ�Ȃ�
    msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
    word = WORDSET_Create(HEAPID_MYSTERYGIFT);
    wk->msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_MYSTERYGIFT);
    wk->msg_wait = 1;
    // �\��
    DisplaySequence(proc, win, msgid);
    wk->msg_next_seq = next_seq;
    // �g��Ȃ��Ȃ����o�b�t�@�͊J��
    WORDSET_Delete(word);
    MSGMAN_Delete(msgman);

  } else {
    if(GF_MSG_PrintEndCheck(wk->m_id) == 0){
      // �\�����I�������J��
      STRBUF_Delete(wk->msg);
      wk->msg = NULL;
      wk->msg_wait = 0;
      return wk->msg_next_seq;
    }
  }
  return MYSTERYGIFT_SEQ_DISP_MSG;
}


//------------------------------------------------------------------
/**
 * @brief	�G���[���N�����ۂɒʐM��؂鏈��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CommDisconnect(MYSTERYGIFT_WORK *wk)
{
  switch(wk->comm_type){
  case MYSTERYCOMM_TYPE_NULL:
    break;
  case MYSTERYCOMM_TYPE_DIRECT:		// �_�C���N�g�ʐM
    CommMysteryExitGift();
    WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
    break;
  case MYSTERYCOMM_TYPE_AGBCARTRIDGE:	// �`�f�a�̃J�[�g���b�W����_�E�����[�h
    break;
  case MYSTERYCOMM_TYPE_BEACON:		// �r�[�R������_�E�����[�h
    break;
  case MYSTERYCOMM_TYPE_WIFI:		// Wi-Fi����̃_�E�����[�h
    break;
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryGiftProc_Init(PROC * proc, int * seq)
{
  MYSTERYGIFT_WORK *wk;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("sizeof(GIFT_BEACON)     = %3d\n", sizeof(GIFT_BEACON));
  //  OS_TPrintf("sizeof(GIFT_BEACON_CRC) = %3d\n", sizeof(GIFT_BEACON_CRC));
  OS_TPrintf("sizeof(POKEMON_PARAM)   = %3d\n", PokemonParam_GetWorkSize());
  OS_TPrintf("sizeof(GIFT_PRESENT)    = %3d\n", sizeof(GIFT_PRESENT));
#endif
  
  MysteryGiftSetProcp(proc);
  /* ���[�N�G���A��TITLE_STARTMENU�̏�ɍ쐬����(�����̏��Ԃ͖��Ȃ��͂�) */
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_MYSTERYGIFT, 0x30000);
  wk = PROC_AllocWork(proc, sizeof(MYSTERYGIFT_WORK), HEAPID_MYSTERYGIFT);
  /* �������s�ǂ��|���̂Ń��[�N�̓[���N���A */
  memset(wk, 0, sizeof(MYSTERYGIFT_WORK));
  
  /* �e��ϐ��̏����� */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_MYSTERYGIFT);
  GF_Disp_GX_VisibleControlInit();
  GF_Disp_GXS_VisibleControlInit();
  CommMysteryFunc_VramBankSet();
  BgInit(wk->bgl);

  /* ��ʂ̏����ݒ� */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* �T�E���h�f�[�^���[�h */
  Snd_DataSetByScene( SND_SCENE_HUSIGI, SEQ_PRESENT, 1 );

  /* AGB����̃_�E�����[�h���ǂ����̃t���O��ݒ� */
  if(GetAgbCartridgeDataSize()){
    wk->comm_type = MYSTERYCOMM_TYPE_AGBCARTRIDGE;
    sys_InitAgbCasetteVer(CasetteVersion);
    MysteryLib_SetAgbCartridgeIntr(TRUE);	/* AGB�J�[�g���b�W�̔������oON */
  }
  /* �r�[�R���擾�V�[�P���X������ */
  wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_WAIT;
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->cfg = SaveData_GetConfig(wk->sv);

  wk->msg_wait = MSG_NO_PUT;

#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    POKEMON_PARAM *pp = PokeParty_GetMemberPointer(SaveData_GetTemotiPokemon(wk->sv), 0);
    u32 adrs = (u32)pp + PokemonParam_GetWorkSize();
    OS_TPrintf("POKEMON_PARAM: %08X - %08X\n", pp, adrs);
  }
#endif
  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  
  return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryGiftProc_Main(PROC * proc, int * seq)
{
  u32 ret, value;
  GIFT_DELIVERY *deli;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  CTRDG_IsExisting();

  //  OS_TPrintf("seq = %d\n", *seq);
  
  // �r�[�R���擾�V�[�P���X
  if(wk->beacon_seq != MYSTERYGIFT_BEACON_SEQ_WAIT)
    MysteryGiftBeaconProc_Main(wk);
  
  switch(*seq){
  case MYSTERYGIFT_SEQ_INIT:
    /* ���C�u���������� */
    MysteryLib_Init(HEAPID_MYSTERYGIFT);
    wk->seq = seq;
    *seq = MYSTERYGIFT_SEQ_CREATE_SCREEN;
    break;

  case   MYSTERYGIFT_SEQ_CREATE_SCREEN:
    /* ��ʍ쐬 */
    MysteryGift_InitGraphicsData(proc, wk);
    InitCellActor(wk);
    /* �t�F�[�h�C�� */
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, MYSTERYGIFT_SEQ_MAIN, seq, MYSTERYGIFT_SEQ_WAIT_FADE);
#if 0
    // �r�[�R���͏E��Ȃ��Ă��ǂ��Ȃ�܂���
    wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_INIT;
#endif
    break;

  case MYSTERYGIFT_SEQ_WAIT_FADE:
    // �t�F�[�h���I������܂ő҂��Ď��̃V�[�P���X��
    MysteryLib_FadeEndCheck(seq);
    break;

  case MYSTERYGIFT_SEQ_MAIN:
    /* �g�b�v���j���[�̃��C�����[�v */
    DoMenuMain(proc, seq, TopMainMenuRetire);
    break;

  case MYSTERYGIFT_SEQ_RECV:
    /* �ʐM���������肷��E�B���h�E�̃��C�����[�v */
    DoMenuMain(proc, seq, CommTypeMenuRetire);
    break;

  case MYSTERYGIFT_SEQ_DIRECT_YESNO:
    /* �_�C���N�g�ő���u�͂��^�������v�̃��C�����[�v */
    DoMenuMain(proc, seq, CommDirectMenuNo);
    break;



//--------------------------------------------------------------------------------------------

    // WiFi�_�E�����[�h�̏���

  case MYSTERYGIFT_WIFI_DOWNLOAD_MAIN:
    WiFi_MysteryGitft_Main(proc, seq);
    break;


//--------------------------------------------------------------------------------------------

    // �r�[�R���_�E�����[�h�̏���

  case MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE:
    // event_name�������Ă���̂�҂�
    MysteryGift_BeaconMainLoop(wk);
    // �r�[�R�������E������ȉ��̏����֐i�ށB�_�E�����[�h�������̂͑����čs����
    // �Í����ɔ����A�S�Ẵf�[�^���_�E�����[�h���Ă��珈������悤�ɕύX
    if(s_state == BEACON_STATE_SUCCESS){
      // �^�C���A�C�R������
      SetTimeWaitIcon(wk, FALSE);
      // �r�[�R������{���̃��[�N�G���A�ɃR�s�[�ۑ�
      CommSetSaveData(proc);

      // �󂯎�����r�[�R�����̃G���[�𒲂ׂĂ���
      wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
      // �󂯎�苖�̂q�n�l�o�[�W�����ƈقȂ��Ă�����󂯎��Ȃ�
      if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION){
	SetTimeWaitIcon(wk, FALSE);	// 	�^�C���A�C�R��������
	*seq = MYSTERYGIFT_ERROR_FULL;
      } else {

	if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	  GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);

	// �����Ŏ�M�����^�C�g����\��
	DisplaySequenceDirect(proc, &wk->upwin, bsdown_c_fileheader());
	DisplaySequence(proc, &wk->msgwin, mystery_01_005);
	/* �u�͂��^�������v���j���[�̍쐬 */
	CreateBeaconCommYesNoMenu(proc);
	*seq = MYSTERYGIFT_BEACON_DOWNLOAD_YESNO;
      }
    }
    // �L�����Z������
    if(s_state == BEACON_STATE_CANCEL || s_state == BEACON_STATE_CRCERROR){
      MysteryGift_BeaconCancel();
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD_YESNO:
    // �u��������̂��@���サ�񂵂܂����v�u�͂��^�������v
    DoMenuMain(proc, seq, CommChildRecvBeaconCancel);
    MysteryGift_BeaconMainLoop(wk);
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD:
    // �_�E�����[�h�͂��łɏI����Ă���
    // �����ŉ���ʂ̍X�V(�󂯎��A�j���[�V�����ǉ�)
    //    SetBaseIcon(wk, -1);
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    SetTimeWaitIcon(wk, TRUE);
    /* �����ŃZ�[�u���Ă݂悤 */
    CommChildSaveRecvData(proc);
    *seq = MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE;
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE:
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST)
      MysteryLib_DoLastSave();
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_OK){
      SetTimeWaitIcon(wk, FALSE);
      SetBaseIcon(wk, -1);
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      /* ��������̂��@�����Ƃ�܂����I\n�t�����h���B�@�V���b�v�@��\n�͂�������@����@�����Ƃ��ĂˁI */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_LOOP);

    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      SetBaseIcon(wk, -1);
      /* �Z�[�u�G���[�̎��̏��� */
      wk->gift_data.beacon.have_card = 0;	// �J�[�h��ʂ͕\�����Ȃ�
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

    
  case MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL:
    // �L�����Z���������I������܂ő҂��܂�
    MysteryGift_BeaconMainLoop(wk);
    if(s_state == BEACON_STATE_CANCEL || s_state == BEACON_STATE_SUCCESS || s_state == BEACON_STATE_CRCERROR){
      if(s_state == BEACON_STATE_CANCEL)
	MysteryGift_BeaconCancel();
      // �L�����Z�������I��
      *seq = CommDirectCommMenuNo(proc);
    }
    break;


//--------------------------------------------------------------------------------------------


#ifdef PARENT_TEST
    // �����܂ł��e�X�g�p�̐e�@�ł��B
    // �ʐM���X�^�[�g������Ƃ��͂`�{�^���������Ă�������
    // �a�{�^���������Ή���q�����Ă��邩�m�邱�Ƃ��ł��܂�
  case MYSTERYGIFT_SEQ_START_PARENT:
    // �e�@�Ƃ��ĒʐM�J�n
    if(CommIsConnect(COMM_PARENT_ID)){
      CommMPSetBeaconTempData(&wk->gift_data.beacon);
      if(sys.trg & PAD_BUTTON_CANCEL){
	Snd_SePlay(SEQ_SE_DP_SELECT);
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_Printf("�q�����Ă���q�̐�: %d\n", CommMysteryGetCommChild());
#endif
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	Snd_SePlay(SEQ_SE_DP_SELECT);
	//	wk->sync_wait = 1;
	CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
	*seq = MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING;
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_Printf("���M�J�n\n");
#endif
      }
    }
    break;

  case MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING:
    if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE) == TRUE){
      *seq = MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT;
    }
    break;
    
  case MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT:
    //    if(--wk->sync_wait == 0){
      /* �����Ńf�[�^�̑��M���J�n(wk->gift_data�Ƀf�[�^���󂯂�) */
      MysteryLib_CreateCryptoData(&wk->gift_data, &wk->comm_data, HEAPID_MYSTERYGIFT);
      CommMysterySendGiftDataParent((const void *)&wk->comm_data, sizeof(GIFT_DATA));
      *seq = MYSTERYGIFT_SEQ_SENDDATA_PARENT;
      //    }
    break;

  case MYSTERYGIFT_SEQ_SENDDATA_PARENT:
    if(CommMysteryGiftGetRecvCheck() == TRUE){
      CommMysteryExitGift();
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_Printf("�ʐM������ɏI�����܂����I\n");
#endif
      *seq = MYSTERYGIFT_SEQ_LOOP;
    }
    
    break;

#endif	// PARENT_TEST



//--------------------------------------------------------------------------------------------


    


  case MYSTERYGIFT_SEQ_START_CHILD:
    //    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - WM_GetLinkLevel());
    /* �q�@�Ƃ��ĒʐM�J�n */
    if((wk->connectIndex = CommMysteryCheckParentBeacon(wk)) != -1){
      SetTimeWaitIcon(wk, FALSE);	// �^�C���A�C�R������
      // �r�[�R���̃G���[�`�F�b�N�̂ݍs��
      // �q�@�̏ꍇ�́A�󂯎��o�[�W����������Ă�����G���[��\������悤�ɂ���
      wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
      // �r�[�R�����ɖ��ߍ��܂�Ă���^�C�g����\������
      if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);
      DisplaySequenceDirect(proc, &wk->upwin, wk->gift_data.beacon.event_name);
      DisplaySequence(proc, &wk->msgwin, mystery_01_005);
      /* �u�͂��^�������v���j���[�̍쐬 */
      CreateDirectCommYesNoMenu(proc, 0);
      *seq = MYSTERYGIFT_SEQ_RECV_YESNO_CHILD;
    }
    /* �L�����Z������ */
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0)){
      SetTimeWaitIcon(wk, FALSE);	// �^�C���A�C�R������
      CommMysteryExitGift();
      WirelessIconEasyEnd();		// �ʐM�A�C�R���폜
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_YESNO_CHILD:
    /* �u���́@��������́@���@���サ��@���܂����H�v�́u�͂��^�������v�I�� */
#if 0
    DoMenuMain(proc, seq, CommDirectMenuNo);
#else
    DoMenuMain(proc, seq, CommDirectCommMenuNo);
#endif
    break;

  case MYSTERYGIFT_SEQ_REQEST_CHILD:
    /* �e�@����̑��M�҂� */
    value = CommGetCurrentID();
    if(value != COMM_PARENT_ID && CommIsConnect(value)){
      if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE) == TRUE){
	SetTimeWaitIcon(wk, FALSE);
	CommStateSetErrorCheck(TRUE,TRUE);
	/* ��������́@���@���サ�񂿂イ�@�ł�
	   �ł񂰂���@����Ȃ��Ł@���������c�c */
	DisplaySequence(proc, &wk->msgwin, mystery_01_008);
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("�e�@���瑗�M���J�n����܂����I\n");
#endif
	SetBaseIcon(wk, 1);
	SetTimeWaitIcon(wk, TRUE);
	wk->timeout = 60*10;
	*seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1;
      }
    } else if(value != COMM_PARENT_ID && CommIsConnect(value) == 0){
      /* �e�Ƃ̒ʐM���Ƃ܂��Ă��܂�����u���������݋��ہv�Ƃ݂Ȃ� */
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      SetBaseIcon(wk, -1);
      SetTimeWaitIcon(wk, FALSE);
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL;
      break;
    }
    /* �L�����Z������ */
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0)){
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      SetBaseIcon(wk, -1);
      SetTimeWaitIcon(wk, FALSE);
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1:
    /* �e�@����f�[�^���M���I������܂ő҂� */
    if(CommMysteryCheckRecvData()){
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2;
    }
    /* �L�����Z������ */
    value = CommGetCurrentID();
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0) || (value != COMM_PARENT_ID && CommIsConnect(value) == 0)){
      SetTimeWaitIcon(wk, FALSE);
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }

    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2:
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("�󂯎��m�F���ł��܂����I\n");
#endif
    // �����ŉ���ʂ̍X�V(�󂯎��A�j���[�V�����ǉ�)
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    CommStateSetErrorCheck(FALSE,FALSE);
    /* �����ŃZ�[�u���Ă݂悤 */
    CommChildSaveRecvData(proc);
    *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3;
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3:
    // �������e�@�Ƃ̒ʐM���؂ꂽ��Z�[�u���s
    value = CommGetCurrentID();
    if(value != COMM_PARENT_ID && CommIsConnect(value) == 0){
      CommMysteryExitGift();
      // �ʐM�ؒf
      wk->save_cancel = TRUE;
      MysteryLib_CancelSaveDSCard();
      SetTimeWaitIcon(wk, FALSE);
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      SetBaseIcon(wk, -1);
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31;
      break;
    }
    // �Z�[�u�����҂�
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST){
      // �e�@�Ɠ��������
      CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE2);
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30;
      wk->sync_wait = 120;	// �^�C���A�E�g�p�J�E���^

    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      /* �Z�[�u�G���[�̎��̏��� */
      MysteryLib_CancelSaveDSCard();
      wk->gift_data.beacon.have_card = 0;	// �J�[�h��ʂ͕\�����Ȃ�
      SetTimeWaitIcon(wk, FALSE);
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30:
    // �e�@����Ԏ����߂��Ă�����Z�[�u����
    if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE2) == TRUE){
      // �Ō�̃Z�[�u���s��
      MysteryLib_DoLastSave();
      wk->sync_wait = 10;
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4;
    } else if(--wk->sync_wait == 0){
      /* �Z�[�u�G���[�̎��̏��� */
      MysteryLib_CancelSaveDSCard();
      wk->gift_data.beacon.have_card = 0;	// �J�[�h��ʂ͕\�����Ȃ�
      SetTimeWaitIcon(wk, FALSE);
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;
    
  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31:
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("�Z�[�u���s\n");
#endif
      //      DisplaySequence(proc, &wk->msgwin, mystery_err_008);
      // ��̃E�B���h�E������
      CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
      wk->gift_data.beacon.have_card = 0;
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_008, MYSTERYGIFT_SEQ_LOOP);
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4:
    if(--wk->sync_wait == 0){ // || CommMysteryGiftGetRecvCheck() == TRUE){
      // �ʐM�ؒf
      SetTimeWaitIcon(wk, FALSE);
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      SetBaseIcon(wk, -1);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_Printf("���S�I��\n");
#endif
      /* ��������̂��@�����Ƃ�܂����I\n�t�����h���B�@�V���b�v�@��\n�͂�������@����@�����Ƃ��ĂˁI */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL:
    /* �\�����݂����ۂ��ꂽ�ꍇ�̏��� */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // �u���������݁@���@����Ё@����܂����v
    DisplaySequence(proc, &wk->msgwin, mystery_err_004);
    // ��̃E�B���h�E������
    CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL;
    break;
    
    break;
  case MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT:
    // 	�^�C���A�C�R��������
    SetTimeWaitIcon(wk, FALSE);
    /* �L�����Z�������̏��� */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // �u��������́@��\n�݂���܂���@�ł����v
    DisplaySequence(proc, &wk->msgwin, mystery_err_003);
    // ��̃E�B���h�E������
    CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL;
    break;
  case MYSTERYGIFT_SEQ_SEND_RECV_CANCEL:

    OS_TPrintf("�L�����Z������\n");

    /* ���[�U�[�ɂ��L�����Z�� */
    if(sys.trg){
      /* ���C�����j���[��\�� */
      Snd_SePlay(SEQ_SE_DP_SELECT);
      CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
      *seq = MYSTERYGIFT_SEQ_MAIN;
    }
    break;

    

//--------------------------------------------------------------------------------------------
//	�`�f�a�J�[�g���b�W����̃f�[�^�]��

  case MYSTERYGIFT_SEQ_AGB_START_CHILD:
    /* �r�[�R�������������փR�s�[���ă��j���[��\�� */
    if(wk->from_seq != MYSTERYGIFT_WIFI_DOWNLOAD_MAIN)
      ReadAgbCartridgeData(&wk->gift_data, sizeof(GIFT_COMM_PACK));

#if 0
    // ���������e�X�g
    wk->gift_data.beacon.version  = 0xFFFFFFFF;
    wk->gift_data.beacon.event_id = 0xFFFF;
#endif

    // ��ɃX���b�g�n�̃G���[�`�F�b�N
    wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
    
    // �󂯎�苖�̂q�n�l�o�[�W�����ƈقȂ��Ă�����󂯎��Ȃ�
    if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION){
      SetTimeWaitIcon(wk, FALSE);	// 	�^�C���A�C�R��������
      *seq = MYSTERYGIFT_ERROR_FULL;
    } else {
      if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);
      DisplaySequenceDirect(proc, &wk->upwin, wk->gift_data.beacon.event_name);
      DisplaySequence(proc, &wk->msgwin, mystery_01_005);
      /* �u�͂��^�������v���j���[�̍쐬 */
      CreateDirectCommYesNoMenu(proc, 0);
      *seq = MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD;
    }
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD:
    /* �u���́@��������́@���@���サ��@���܂����H�v�́u�͂��^�������v�I�� */
    DoMenuMain(proc, seq, CommDirectCommMenuNo);
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD:
    /* ��M�ł��邩�ǂ����̃`�F�b�N */
    *seq = MYSTERYGIFT_SEQ_AGB_REQEST_CHILD;
    break;
    
  case MYSTERYGIFT_SEQ_AGB_REQEST_CHILD:
    // �����ŉ���ʂ̍X�V(�󂯎��A�j���[�V�����ǉ�)
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    /* ��������́@���@���サ�񂿂イ�@�ł�
       �ł񂰂���@����Ȃ��Ł@���������c�c */
    DisplaySequence(proc, &wk->msgwin, mystery_01_008);
    SetBaseIcon(wk, 1);
    SetTimeWaitIcon(wk, TRUE);
    wk->sync_wait = 60;
    *seq = MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD;
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD:
    /* �e�@����f�[�^���M���I������܂ő҂� */
    if(--wk->sync_wait == 0){
      /* �����ŃZ�[�u���Ă݂悤 */
      CommChildSaveRecvData(proc);
      *seq = MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2;
    }
    break;
  case MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2:
    // �Z�[�u�����҂�
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST)
      MysteryLib_DoLastSave();
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_OK){
      wk->sync_wait = 1;
      SetTimeWaitIcon(wk, FALSE);
      SetBaseIcon(wk, -1);
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      /* ��������̂��@�����Ƃ�܂����I\n�t�����h���B�@�V���b�v�@��\n�͂�������@����@�����Ƃ��ĂˁI */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD);
    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      /* �Z�[�u�G���[�̎��̏��� */
      SetBaseIcon(wk, -1);
      wk->gift_data.beacon.have_card = 0;	// �J�[�h��ʂ͕\�����Ȃ�
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD:
    if(--wk->sync_wait == 0){
      wk->sync_wait = 256*256;
      *seq = MYSTERYGIFT_SEQ_LOOP;
    }      
    break;


//--------------------------------------------------------------------------------------------

  case MYSTERYGIFT_ERROR_FULL:
    // �ʐM��؂鏈��(���������z�z�`�F�b�N�̏ꍇ�͐؂�Ȃ�)
    if(wk->gift_error != COMMMYSTERYFUNC_ERROR_GROUNDCHILD)
      CommDisconnect(wk);

    // �z�B���܂��̓J�[�h����t�Ŏ󂯎��Ȃ�
    *seq = MysteryGift_FullError(proc);
    // �͂��^�������̃��j���[������
    CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
    break;

  case MYSTERYGIFT_SEQ_DISP_MSG:
    // ���b�Z�[�W���\�����I���܂Ń��[�v
    *seq = MysteryGif_DisplayMessage(proc, NULL, NULL, *seq);
    break;

  case MYSTERYGIFT_SEQ_RETURN_TOPMENU:
    if(sys.trg){
      /* ��̃��j���[�E�B���h�E������ */
      CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
      *seq = CommTypeMenuRetire(proc);
    }
    break;

  case MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK:
    OS_TPrintf("���z�z�`�F�b�N\n");
    /* �u�͂��^�������v���j���[�̍쐬 */
    CreateDirectCommYesNoMenu(proc, 1);
    *seq = MYSTERYGIFT_SEQ_RECV_YESNO_CHILD;
    wk->gift_error = COMMMYSTERYFUNC_ERROR_NONE;
    break;

    
//--------------------------------------------------------------------------------------------
    
  case MYSTERYGIFT_SEQ_RETURN:
    /* �^�C�g���̃��j���[�ɖ߂� */
    TopMainMenuFinish(proc);
    wk->to_seq = 0;
    return PROC_RES_FINISH;
    break;

  case MYSTERYGIFT_SEQ_GO_LOOKCARD:
    /* �J�[�h��ʂ֍s�� */
    TopMainMenuFinish(proc);
    wk->to_seq = 1;
    return PROC_RES_FINISH;
    break;
    

  case MYSTERYGIFT_SEQ_LOOP:
    /* �d�����n�e�e�ɂ���^�J�[�h��񂪂���Ε\������ */
    if(sys.trg){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      if(wk->gift_data.beacon.have_card == 1){
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_DISP_CARD, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
      } else {
	MysteryLib_ChangeFadeType(1);
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_FADEOUT_RESET, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
      }	
    }
    break;

  case MYSTERYGIFT_SEQ_DISP_CARD:
    // ����ʂ͊i�q�͗l�𕜊�
    CreateBgScreenSub(wk->bgl);
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
    // ���ʂ̓J�[�h���̕\��
    MysteryCard_DisplayCardOnly(wk->bgl, &wk->gift_data.data.card, HEAPID_MYSTERYGIFT);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, MYSTERYGIFT_SEQ_LOOP, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
    wk->gift_data.beacon.have_card = 0;
    break;

  case MYSTERYGIFT_SEQ_FADEOUT_RESET:
    OS_ResetSystem(0);
    break;
  }

  // �펞�ł͂Ȃ�����ǎ��s�����֐��͂����Ŏ��s
  if(wk->func_hook)
    wk->func_hook(wk);

  
  // �A�C�R����\�����邽�߂ɕK�v�ȋ쓮����
  MysteryLib_DoClact();

  return PROC_RES_CONTINUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^�̃|�C���^��Ԃ�
 * @param	NONE
 * @return	SAVEDATA	�Z�[�u�f�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
PROC *MyseryGiftGetProcp(void)
{
  return MysteryProc;
}
void MysteryGiftSetProcp(PROC *proc)
{
  MysteryProc = proc;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�^�C�g���v���Z�X�F�I��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
extern const PROC_DATA MysteryCardProcData;
#define CHECK_OVERLAY
static PROC_RESULT MysteryGiftProc_End(PROC * proc, int * seq)
{
  FS_EXTERN_OVERLAY( title );
#ifdef CHECK_OVERLAY
  FS_EXTERN_OVERLAY( startmenu );
#endif
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  if(wk->to_seq == 0){
    Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
  } else if(wk->to_seq == 1){
#ifdef CHECK_OVERLAY
    Main_SetNextProc( FS_OVERLAY_ID(startmenu), &MysteryCardProcData);
#else
    Main_SetNextProc( NO_OVERLAY_ID, &MysteryCardProcData);
#endif
  }
  sys_DeleteHeap(HEAPID_COMMICON);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_MYSTERYGIFT);
  if(wk->comm_type == MYSTERYCOMM_TYPE_AGBCARTRIDGE)
    sys_InitAgbCasetteVer(0);
  MysteryLib_SetAgbCartridgeIntr(FALSE);	/* AGB�J�[�g���b�W�̔������oOFF */

  return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	�r�[�R���擾�V�[�P���X
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define BEACON_GATHER_TIME	(2*60)			// �r�[�R�������W�߂鎞��
static void MysteryGiftBeaconProc_Main(MYSTERYGIFT_WORK *wk)
{
  int flag;

  switch(wk->beacon_seq){
  case MYSTERYGIFT_BEACON_SEQ_WAIT:	// �������Ȃ�
    break;

  case MYSTERYGIFT_BEACON_SEQ_INIT:
    // * �p�[�e�B�[�Q�[�������̒ʐM�����J�n�i�q�@��Ԃ̂݁j
    CommStateEnterPartyGameScanChild(wk->sv);
    wk->beacon_wait = BEACON_GATHER_TIME;
    wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_TIMER;
    break;

  case MYSTERYGIFT_BEACON_SEQ_TIMER:
    // �r�[�R�����W��
    flag = CommStateGetPartyGameBit();

#if 0//def DEBUG_ONLY_FOR_mituhara
    // �f�o�b�O��
    if(sys.trg & PAD_BUTTON_L)	flag |= PARTYGAME_MYSTERY_BCON;
#endif

    if(flag & PARTYGAME_MYSTERY_BCON)	wk->found_beacon = TRUE;

    if(--wk->beacon_wait == 0){
      // �p�[�e�B�[�Q�[���T�[�`�̏I������
      CommStateExitPartyGameScan();
      wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_WAIT;
    }
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	�r�[�R���_�E�����[�h
 *		���C�V���g���l��main.c�������ɈڐA
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
// bsdown����Ԃ��Ă���R�[���o�b�N����������B
static void MysteryGift_BSCallBack( int code )
{
  switch( code ){
  case BSDOWNCALLBACK_STARTSCAN:	// �X�L�����J�n��
    s_state = BEACON_STATE_SCANNING;
    break;
  case BSDOWNCALLBACK_START:		// �e�@���݂����Ƃ�
    s_state = BEACON_STATE_DOWNLOAD;
    break;
  case BSDOWNCALLBACK_SUCCESS:		// �f�[�^�����S�Ɏ󂯎�����Ƃ�
    s_state = BEACON_STATE_COMPLETE;
    break;
  case BSDOWNCALLBACK_FINISH:		// �����̏I������
    if( s_state == BEACON_STATE_COMPLETE ){
      s_state = BEACON_STATE_FINISH;
    }	else {
      s_state = BEACON_STATE_CANCEL;				
    }
    break;
  case BSDOWNCALLBACK_ERROR:		// �G���[������
    s_state = BEACON_STATE_ERROR;
    break;
  }
}


static void MysteryGift_BeaconCancel(void)
{
  OS_TPrintf("�C�N�j���[�����J��\n");
  CommVRAMDFinalize();
  sys_FreeMemoryEz(buffer);
  WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
  buffer = NULL;
}

static void MysteryGift_BeaconMainLoop(MYSTERYGIFT_WORK *wk)
{
  if( s_state == BEACON_STATE_FINISH ){
    MysteryGift_BeaconCancel();

    // �_�E�����[�h�����҂��B�b�q�b�����������`�F�b�N
    // �R�[���o�b�N�łȂ��A�����Ń`�F�b�N����̂́A���荞�݂Ƀ��[�`���ɏd�����������ꂽ���Ȃ�����
    if( bsdown_c_checkcrc() ) {
      s_state = BEACON_STATE_SUCCESS;
    } else {
      s_state = BEACON_STATE_CRCERROR;
    }
  }

  if(s_state == BEACON_STATE_INIT1 || s_state == BEACON_STATE_INIT2 || s_state == BEACON_STATE_START ||
     s_state == BEACON_STATE_SCANNING || s_state == BEACON_STATE_DOWNLOAD || s_state == BEACON_STATE_CANCELING)
    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - WM_GetLinkLevel());
  
  //  OS_TPrintf("s_state = %d\n", s_state - BEACON_STATE_INIT1);
  
  switch( s_state ){
  case BEACON_STATE_INIT1:				// �������(�ʐM���C�u����������)
    CommVRAMDInitialize();
    s_state = BEACON_STATE_INIT2;
    break;			
  case BEACON_STATE_INIT2:				// �������
    if(CommIsVRAMDInitialize() == TRUE){
      progress_time = 0;
      buffer = sys_AllocMemory(HEAPID_MYSTERYGIFT, bsdown_c_worksize());
      bsdown_c_init( &(wk->recvbuf[0]), MysteryGift_BSCallBack, buffer );
      s_state = BEACON_STATE_START;
      WirelessIconEasy();	// �ʐM�A�C�R���\��(�A���e�i�����Ȃ�T-T)
      debug_printf("PRESS A TO START\n");
    }
    break;
  case BEACON_STATE_START:				// �������
    debug_printf("INITIALIZING...\n");
    break;
  case BEACON_STATE_SCANNING:			// �X�L������
    debug_printf("SEARCHING......\n");
    //    debug_printf("PRESS START TO RESTART\n");
    break;
  case BEACON_STATE_DOWNLOAD:			// �e�@�������āA�_�E�����[�h��
    debug_printf("packets %d / %d\t", bsdown_c_received(), bsdown_c_total());
    progress_time++;
    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );
    break;				
  case BEACON_STATE_COMPLETE:			// �_�E�����[�h����
    debug_printf("Finishing( size = %d byte )\n", bsdown_c_size());
    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );				
    break;
  case BEACON_STATE_CANCELING:		// �L�����Z��������
    debug_printf("CANCELING......\n");    //    s_state = BEACON_STATE_FINISH;	// ���s���ďI��������
    break;
  case BEACON_STATE_SUCCESS:			// �_�E�����[�h�I��
    //    debug_printf("Complete( size = %d byte )\n", bsdown_c_size());
    //    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );				
    //    debug_printf("PRESS START TO RESTART\n");				
    break;
  case BEACON_STATE_CANCEL:			// �L�����Z���I��
    //    debug_printf("PRESS START TO RESTART\n");
    return;
    break;			
  case BEACON_STATE_ERROR:				// �G���[	
    debug_printf("error......\n");
    break;
  case BEACON_STATE_CRCERROR:
    debug_printf("crc error.\n");
    //    debug_printf("PRESS START TO RESTART\n");
    break;
  }
		
  if(sys.trg & PAD_BUTTON_CANCEL){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // ���Z�b�g����
    switch( s_state ){
    case BEACON_STATE_SCANNING:			// �X�L������
    case BEACON_STATE_DOWNLOAD:			// �e�@�������āA�_�E�����[�h��
    case BEACON_STATE_ERROR:				// �G���[

      OS_TPrintf("�L�����Z���˗�\n");
      if( bsdown_end() ){
	s_state = BEACON_STATE_CANCELING;	
      }					
      break;
				
    case BEACON_STATE_SUCCESS:			// �_�E�����[�h�I��
    case BEACON_STATE_CANCEL:			// �L�����Z���I��
    case BEACON_STATE_CRCERROR:		// �b�q�b�G���[
      return;
    default:
      break;
    }				
  }
}


//------------------------------------------------------------------
///	�v���Z�X�f�[�^
//------------------------------------------------------------------
const PROC_DATA MysteryGiftProcData = {
  MysteryGiftProc_Init,
  MysteryGiftProc_Main,
  MysteryGiftProc_End,
  NO_OVERLAY_ID,
};
  
/*  */
