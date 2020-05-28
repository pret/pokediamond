//===================================================================
/**
 * @file	agbpokemon.c	
 * @bfief	AGB�|�P�����J�Z�b�g��DP�Ԃ̃|�P�����f�[�^�ړ�
 * @author	Satoshi Mitsuhara
 * @date	06.05.30
 *
 * $Id: agbpokemon.c,v 1.63 2006/08/14 11:00:46 mitsuhara Exp $
 */
//===================================================================

// BG0	���b�Z�[�W�E�B���h�E
// BG1	�|�P�����X�e�[�^�X�\���E�B���h�E
// BG2	�w�i
// BG3	���g�p

#include "common.h"
#include "system/main.h"
#include "system/procsys.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/touch_subwindow.h"
#include "system/pmfprint.h"
#include "system/agb_str.h"

#include "gflib/touchpanel.h"
#include "itemtool/item.h"

#include "system/clact_tool.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/poke_tool.h"
#include "../poketool/poke_tool_def.h"		/* ##### */
#include "savedata/pokepark_data.h"
#include "savedata/savedata.h"
#include "savedata/config.h"

#include "battle/battle_server.h"
#include "battle/wazano_def.h"

#include "agbpoke_access.h"
#include "agbpoke_tool.h"
#include "agbpoke_util.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_pokemonpark.h"

#include "demo/title.h"

#include "comm_mystery_func.h"
#include "mystery.naix"
#include "mysterylib.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define SetSeq(x)		*seq = (x)

// �|�P�����A�C�R�����n�܂�VRAM��ł̃I�t�Z�b�g
#define POKEICON_VRAM_OFFSET ( 0x64 )
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)
// �|�P�����A�C�R���̃p���b�g��]������I�t�Z�b�g
#define POKEICON_PAL_OFFSET				(  8 )
//** CharManager PlttManager�p **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)
// �|�P�����̕\���ݒ�
#define POKEMON_WIDTH			40
#define POKEMON_HEIGHT			24
#define POKEMON_BASEX			28
#define POKEMON_BASEY			40


#define POKEMON_ICON_MAX			30
#define POKEMON_SCREEN_TOUCH_MAX		3
#define POKEMON_TOUCH_ICONMAX		(POKEMON_ICON_MAX+POKEMON_SCREEN_TOUCH_MAX+1)

#define POKEMON_SELECT_MAX			6
#define POKEMON_NOSELECT			-1

#define ICON_CANCEL			(POKEMON_ICON_MAX+0)
#define ICON_ARROWL			(POKEMON_ICON_MAX+1)
#define ICON_ARROWR			(POKEMON_ICON_MAX+2)
#define ICON_TERMINATE			(POKEMON_ICON_MAX+3)


typedef struct {
  GF_BGL_BMPWIN *win;
  int flag;
  int sx, sy;
  int width, height;
  int dx, dy;
  int base;
  int screen;
  FONT_TYPE font;
  GF_PRINTCOLOR color;
  GF_PRINTCOLOR clrcolor;
  int msgid;
  STRCODE *msgp;
  STRBUF *msg;
  WORDSET *word;
  int msgwait;

  int m_id;
} REGWIN;
#define MSG_FLAG_CENTER		0x01
#define MSG_FLAG_NOCLEAR	0x02
#define MSG_FLAG_NOREDRAW	0x04
#define MSG_FLAG_FRAME		0x08
#define MSG_FLAG_TALKWIN	0x10



typedef struct {
  CLACT_WORK_PTR clact;
  CLACT_WORK_PTR item;
  int monsno;
} POKEMON_ICON;

typedef struct {
  CLACT_WORK_PTR icon;
  int pokeno;
  int boxno;
} MARK_ICON;


typedef struct {
  int save_seq;
  int wait_frame;
  void *time_icon;

} SAVEWORK;


typedef struct {
  int vadrs;				// VRAM�A�h���X
  int palno;				// �p���b�g�ԍ�
  CLACT_WORK_PTR icon;			// CLACT
  u8 chbuf[POKEICON_TRANS_SIZE];	// �L�����N�^�o�b�t�@
} POKEBUF;



typedef struct {
  int cartridge_type;				// VERSION_xxxx (pm_version.h�Q��)
  int agberror;
  int msg_flag;
  int jiffy;
  
  SAVEDATA *sv;
  MYSTATUS *mst;
  CONFIG *cfg;
  int win_type;
  
  GF_BGL_INI *bgl;

  int next_seq;

  // �Z���A�N�^�[�֘A
  CLACT_SET_PTR	clactSet;				// �Z���A�N�^�[�Z�b�g 
  CLACT_U_EASYRENDER_DATA renddata;			// �ȈՃ����_�[�f�[�^
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// ���\�[�X�}�l�[�W��
  CLACT_U_RES_OBJ_PTR resObjTbl[CLACT_U_RES_MAX];	// ���\�[�X�I�u�W�F�e�[�u��
  CLACT_HEADER clActHeaderMain;
  // �|�P�����A�C�R�� 30�̕�
  POKEMON_ICON icon[POKEMON_ICON_MAX];
  RECT_HIT_TBL iconrect[POKEMON_TOUCH_ICONMAX];

  // �Ƃ���
  CLACT_WORK_PTR cancel[4];	// �S���
  // �E��
  CLACT_WORK_PTR arrowr[4];	// �S���
  // ����
  CLACT_WORK_PTR arrowl[4];	// �S���
  // ����}�[�N
  MARK_ICON mark[POKEMON_SELECT_MAX];	// �U��(�I���ł���|�P�����̐�)
  int selected;
  
  // �����ʂ̃|�P�����A�N�^�[
  CLACT_WORK_PTR check_poke[POKEMON_SELECT_MAX];
  REGWIN cwin;

  // ���b�Z�[�W�E�B���h�E�֘A
  GF_BGL_BMPWIN	TitleWin;
  GF_BGL_BMPWIN	BoxNameWin;
  GF_BGL_BMPWIN	CheckWin;
  
  // AGB�J�[�g���b�W�A�N�Z�X�֌W
  int cartridge_status;
  int load_status;
  u32 buffer[AGBPOKE_BUFFERSIZE/sizeof(u32)];
  POKEBOX_SAVE_DATA *boxdata;
  int CurrentBox;

  int wait_seq;

  // ����ʃE�C���h�E�V�X�e��
  TOUCH_SW_SYS *TouchSubWindowSys;

  SAVEWORK save_work;

  // �|�P�����A�C�R���̍����\���p
  POKEBUF pokebuf[POKEMON_ICON_MAX];
  void (*DrawFunc)(void);
  
} AGBCARTRIDGE_WORK;


POKEBUF *_PokeBufPtr;


enum {

  AGBCARTRIDGE_SEQ_INIT_CARTRIDGE,	/* AGB�J�[�g���b�W������ */
  AGBCARTRIDGE_SEQ_PREINIT_SCREEN,	/* �X�N���[�������� */
  
  AGBCARTRIDGE_SEQ_CHECK_USER,		/* �J�[�g���b�W�̃��[�U�[�m�F */
  AGBCARTRIDGE_SEQ_CHECK_USER_YESNO,

  AGBCARTRIDGE_SEQ_CHECK_FINAL,
  AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO,
  AGBCARTRIDGE_SEQ_DISP_MESSAGE,
  AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO,
  
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN,
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2,
  AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3,
  AGBCARTRIDGE_SEQ_ERROR_SCREEN,	/* �^�C�g���֖߂�G���[�\�� */

  AGBCARTRIDGE_SEQ_INIT_SCREEN,		/* �X�N���[�������� ���̂Q */
  AGBCARTRIDGE_SEQ_MAIN,		/* ���C������ */
  AGBCARTRIDGE_SEQ_SELECT_WARNING,	/* �I���ł��Ȃ��|�P������I�� */

  AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN,	/* �m�F��ʂ֍s���Ԃ̂�����Ƃ́u�ԁv */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN,	/* �m�F��ʍ쐬 */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1,	/* �u��Ă����܂��v�̃^�b�v�҂� */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH,	/* �u�z���g�ɂ����́H�v�̃^�b�v�҂� */
  AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN,	/* �m�F��ʏ��� */
  AGBCARTRIDGE_SEQ_RETURN_SELECT,	/* �I����ʂɖ߂邽�߂̏����� */

  AGBCARTRIDGE_SEQ_SAVE,		/* �Z�[�u���� */
  AGBCARTRIDGE_SEQ_SAVE_END,		/* �^�b�v�҂� */
  
  AGBCARTRIDGE_SEQ_WAIT_FADE,		/* �t�F�[�h��҂��Ď��̃V�[�P���X�� */
  AGBCARTRIDGE_SEQ_FINISH,		/* ���̉�ʂ̌�n���{�Ō� */
  AGBCARTRIDGE_SEQ_MAX
};


enum {
  SAVE_SEQ_INIT,			/* �Z�[�u���������� */

  SAVE_SEQ_WAIT_INIT_TIMING1,		/* �^�C�~���O���炵���ԏ��������̂P */
  SAVE_SEQ_WAIT_TIMING1,		/* �^�C�~���O���炵���Ԃ��̂P */
  
  SAVE_SEQ_DSSAVE_INIT,			/* DS���̃Z�[�u������ */
  SAVE_SEQ_DSSAVE_MAIN,			/* DS���̃Z�[�u���C�� */

  SAVE_SEQ_AGBSAVE_CHECK,		/* AGB���̃Z�[�u�e�X�g(�K�C�h���C���Ɋ�Â�����) */
  SAVE_SEQ_AGBSAVE_INIT,		/* AGB���̃Z�[�u������ */
  SAVE_SEQ_AGBSAVE_MAIN,		/* AGB���̃Z�[�u���C�� */
#if 0
  SAVE_SEQ_WAIT_INIT_TIMING2,		/* �^�C�~���O���炵���ԏ��������̂Q */
  SAVE_SEQ_WAIT_TIMING2,		/* �^�C�~���O���炵���Ԃ��̂Q */
#endif
  SAVE_SEQ_SAVE_LAST,			/* �Ō�̃Z�N�^���Z�[�u */
  SAVE_SEQ_SAVE_FINAL,			/* �Ō��҂� */

  /* ���֐��̖߂�l�Ƃ��Ďg�p�� */
  SAVE_STATUS_WRITING,			/* �������ݏ����� */
  SAVE_STATUS_WRITE_SUCCESS,		/* �������݂ɐ������� */
  SAVE_STATUS_WRITE_ERROR,		/* �������݂Ɏ��s���� */
  
  SAVE_SEQ_MAX
};


// �E�B���h�E�֘A
#define	FONT_PALNO_NORMAL	15	/* �m�[�}���p���b�g */

#define	AGBPOKEMON_BLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 0))
#define	AGBPOKEMON_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))
#define	AGBPOKEMON_WHITEBLACK	(GF_PRINTCOLOR_MAKE(15, 2, 15))
#define	AGBPOKEMON_BLACKBLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 15))

#define AGBPOKEMON_CHRBASE	0
#define AGBPOKEMON_TITLEBASE	0xA0
#define AGBPOKEMON_STATUSBASE	(14*2+AGBPOKEMON_TITLEBASE)

#define AGBPOKEMON_FRAMECHR	0x3F0
#define AGBPOKEMON_FRAMECOL	14
#define AGBPOKEMON_TFRAMECHR	(AGBPOKEMON_FRAMECHR - TALK_WIN_CGX_SIZ)
#define AGBPOKEMON_TFRAMECOL	13

#define AGBPOKEMON_YESWIN	(30*4+1)
#define AGBPOKEMON_NOWIN	(8*2+30*4+1)


// �A��čs���Ȃ��u�Ђł�킴�v�̃��X�g
static int WazaHidenTable[] = {
  WAZANO_IAIGIRI,			// ����������
  WAZANO_SORAWOTOBU,			// ������Ƃ�
  WAZANO_NAMINORI,			// �Ȃ݂̂�
  WAZANO_KAIRIKI,			// �����肫
  WAZANO_HURASSYU,			// �t���b�V��
  WAZANO_IWAKUDAKI,			// ���킭����
  WAZANO_TAKINOBORI,			// �����̂ڂ�
  WAZANO_DAIBINGU,			// �_�C�r���O
};

// ���[�U�[�m�F�p�̃��b�Z�[�W�e�[�u��
static int UsrCheckMsgTable[] = {
  NULL,		// unknown
  msg_pokepark_02,			// �o�[�W�����FAGB�T�t�@�C�A
  msg_pokepark_01,			// �o�[�W�����FAGB���r�[
  msg_pokepark_03,			// �o�[�W�����FAGB�G�������h
  msg_pokepark_04,			// �o�[�W�����FAGB�t�@�C�A�[���b�h
  msg_pokepark_05,			// �o�[�W�����FAGB���[�t�O���[��
};

// �Z�[�u���̃��b�Z�[�W
static int SaveMsgTable[] = {
  NULL,		// unknown
#if (PM_VERSION == VERSION_DIAMOND)
  msg_pokepark_22,			// "�T�t�@�C�A�@�Ɓ@�_�C�������h�@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_20,			// "���r�[�@�Ɓ@�_�C�������h�@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_24,			// "�G�������h�@�Ɓ@�_�C�������h�@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_26,			// "�t�@�C�A���b�h�@�Ɓ@�_�C�������h�@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_28,			// "���[�t�O���[���@�Ɓ@�_�C�������h�@��\n�|�P�������|�[�g���@�����Ă��܂�"
#elif (PM_VERSION == VERSION_PEARL)
  msg_pokepark_23,			// "�T�t�@�C�A�@�Ɓ@�p�[���@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_21,			// "���r�[�@�Ɓ@�p�[���@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_25,			// "�G�������h�@�Ɓ@�p�[���@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_27,			// "�t�@�C�A���b�h�@�Ɓ@�p�[���@��\n�|�P�������|�[�g���@�����Ă��܂�"
  msg_pokepark_29,			// "���[�t�O���[���@�Ɓ@�p�[���@��\n�|�P�������|�[�g���@�����Ă��܂�"
#endif
};

static u8 BgPalTable[] = {
  0,		// NULL
  2,		// �T�t�@�C��
  1,		// ���r�[
  3,		// �G�������h
  4,		// �t�@�C�A���b�h
  5,		// ���[�t�O���[��
};


static int ErrorMsgTable[] = {
  NULL,
  msg_pokepark_39,			// AGB�̃Z�[�u�f�[�^���ǂ߂Ȃ�������
  msg_pokepark_33,			// �Q�S�����񂽂��Ȃ��Ɓc
  msg_pokepark_34,			// �ق񂽂�������������Ƃ���������������
  msg_pokepark_34,			// �ق񂽂�������������Ƃ���������������
  msg_pokepark_07,			// �{�b�N�X�ɂU�������܂���
  msg_pokepark_09,			// ���łɂ��������Ă܂��c
  msg_pokepark_35,			// ���܂���Q�S�������Ă���܂���
};

#if (PM_VERSION == VERSION_DIAMOND)
#define CHECK_FINAL_MSG		msg_pokepark_36
#define SAVE_SUCCESS_MSG	msg_pokepark_31
#elif (PM_VERSION == VERSION_PEARL)
#define CHECK_FINAL_MSG		msg_pokepark_37
#define SAVE_SUCCESS_MSG	msg_pokepark_32
#endif


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void DrawBoxTitle(AGBCARTRIDGE_WORK *wk, int boxnumber);
static void CheckSelectPokemonIcon(AGBCARTRIDGE_WORK *wk);
static void InitUpMessageWindow(AGBCARTRIDGE_WORK *wk);
static void AgbCartridge_ReqYesNoIcon(AGBCARTRIDGE_WORK *wk);
static void AgbCartridgeDataUpdate(AGBCARTRIDGE_WORK *wk);
void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );

extern void STRBUF_SetStringCode( STRBUF* strbuf, const STRCODE* sz );

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================

extern void AGBPPPtoDSPPP(PokemonPasoParam *agb_ppp,POKEMON_PASO_PARAM *ds_ppp);


//------------------------------------------------------------------
/**
 * @brief	AGB�ł͂��肦�Ȃ��|�P�����̔���
 * @param	NONE
 * @return	TRUE: OK  FALSE: �s���|�P����
 */
//------------------------------------------------------------------
#define MONSNO_AGB_END	413
static BOOL CheckInJusticePokemon(int agb_monsno)
{
  if(agb_monsno <= 0 || agb_monsno >= MONSNO_AGB_END)
    return TRUE;
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	wk->cartridge_type �֒l��ݒ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_SetCartridgeType(AGBCARTRIDGE_WORK *wk)
{
  switch(agbpoke_getPokemonType()){
  case CASTYPE_RUBY:	wk->cartridge_type = VERSION_RUBY;	break;
  case CASTYPE_SAPPHIRE:wk->cartridge_type = VERSION_SAPPHIRE;	break;
  case CASTYPE_GREEN:	wk->cartridge_type = VERSION_GREEN;	break;
  case CASTYPE_RED:	wk->cartridge_type = VERSION_RED;	break;
  case CASTYPE_EMERALD:	wk->cartridge_type = VERSION_EMERALD;	break;
  default:		wk->cartridge_type = -1;		break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�V�[�P���X
 * @param	NONE
 * @return	NONE
 *
 * �ň��ȏ�Ԃł����Ă����B�͂��邯��ǌ����͂��Ȃ��悤�ɂ���
 * �����̏��ԂƂ��Ă͈ȉ��̒ʂ�
 * �P�A�c�r�̃��X�g�P�Z�N�^�ȊO��S�ăZ�[�u
 * �Q�A�`�f�a�̃��X�g�P�Z�N�^�ȊO��S�ăZ�[�u
 * �R�A�^�C�~���O���炵(�^�C�~���O���v���đ��B����Ȃ��悤�ɂ��邽��)
 * �S�A�c�r�Ƃ`�f�a�̃��X�g�Z�N�^����C�ɃZ�[�u
 * �T�A�I��
*/
//------------------------------------------------------------------
static int SaveSequence(AGBCARTRIDGE_WORK *wk)
{
  int ret;
  u8 backupbuf[16];
  SAVE_RESULT result;
  POKEPARK_DATA *ppark;
  SAVEWORK *sw = &wk->save_work;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("  save_seq = %d\n", sw->save_seq);
#endif
#if 0
  // �Z�[�u���s�e�X�g
  return SAVE_STATUS_WRITE_SUCCESS;
#endif
  
  switch(sw->save_seq){
  case SAVE_SEQ_INIT:
    // ����������
    AgbCartridgeDataUpdate(wk);
    ppark = SaveData_GetPokeParkData(wk->sv);
    // �Z�[�u�Ǘ��p�f�[�^���Z�b�g
    POKEPARKDATA_SetMasterData(ppark, agbpoke_GetTrainerID());
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_INIT_TIMING1:
    /* �^�C�~���O���炵���ԏ��������̂P */
    sw->wait_frame = 1 + OS_GetTick() % 120;
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_TIMING1:
    /* �^�C�~���O���炵���Ԃ��̂P */
    if(--sw->wait_frame == 0)
      sw->save_seq++;
    break;

  case SAVE_SEQ_DSSAVE_INIT:
    // DS���̃Z�[�u�A�����ݒ�
    SaveData_DivSave_Init(wk->sv, SVBLK_ID_MAX);
    sw->save_seq++;
    break;

  case SAVE_SEQ_DSSAVE_MAIN:
    // DS���̃Z�[�u���C��
    result = SaveData_DivSave_Main(wk->sv);
    if(result == SAVE_RESULT_NG)	return SAVE_STATUS_WRITE_ERROR;
    if(result == SAVE_RESULT_LAST)	sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_CHECK:
    // AGB���̃Z�[�u�e�X�g(�K�C�h���C���Ɋ�Â�����)
    CTRDG_ReadAgbFlash(0, 0, backupbuf, sizeof(backupbuf));
    sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_INIT:
    // AGB���̃Z�[�u������
    ret = agbpoke_saveEdit_Async();
    if(ret == FALSE){
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_ERROR;
    }
    sw->save_seq++;
    break;

  case SAVE_SEQ_AGBSAVE_MAIN:
    // AGB���̃Z�[�u���C��
    if(agbpoke_check_status() == AGBPOKE_ERROR_WRITING)
      // �����Ă���Œ���������P�t���[��������҂�
      break;
    if(agbpoke_check_status() == AGBPOKE_ERROR_LAST){
      // �Ō�̂P�Z�N�^�ȊO�͏������߂�
      sw->save_seq++;
    } else {
      // ����ɂǂ�ǂ񏑂��Ă���
      ret = agbpoke_saveEdit_check();
      if(ret == AGBPOKE_ERROR_WRITE){
	sys_SleepOK(SLEEPTYPE_SAVELOAD);
	return SAVE_STATUS_WRITE_ERROR;
      }
    }
    break;
#if 0
  case SAVE_SEQ_WAIT_INIT_TIMING2:
    // �^�C�~���O���炵���ԏ�����
    sw->wait_frame = 10 + (wk->jiffy % 60);
    sw->save_seq++;
    break;

  case SAVE_SEQ_WAIT_TIMING2:
    // �^�C�~���O���炵����
    if(--sw->wait_frame == 0)
      sw->save_seq++;
    break;
#endif
  case SAVE_SEQ_SAVE_LAST:
    // �Ō�̃Z�N�^���Z�[�u
    // �܂���DS�����Z�[�u
    do {
      result = SaveData_DivSave_Main(wk->sv);
      //      OS_TPrintf("----- DS : %d\n", result);
      if(result == SAVE_RESULT_NG)	return SAVE_STATUS_WRITE_ERROR;
    } while(result != SAVE_RESULT_OK);
    // ����AGB�����Z�[�u(�����ł�Async���Ă΂�Ă���̂ň�Umain�֏�����߂�)
    agbpoke_saveEdit_check();
    sys_SleepNG(SLEEPTYPE_SAVELOAD); // DS����SleepON�ɂ���Ă���̂ōēxOFF
    sw->save_seq++;
    break;

  case SAVE_SEQ_SAVE_FINAL:
    // AGB���̏I����҂�
    ret = agbpoke_saveEdit_check();
    if(ret == AGBPOKE_ERROR_WRITE){
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_ERROR;
    }
    if(ret == AGBPOKE_ERROR_OK){
      //      OS_TPrintf("�������Z�[�u�I���ł�������\n");
      sys_SleepOK(SLEEPTYPE_SAVELOAD);
      return SAVE_STATUS_WRITE_SUCCESS;
    }
    break;
  }

  return SAVE_STATUS_WRITING;
}


//------------------------------------------------------------------
/**
 * @brief	�c�r�J�[�h�ւ̃Z�[�u����
 * @param	wk
 * @return	NONE
 */
//------------------------------------------------------------------
static void SaveDsCard(AGBCARTRIDGE_WORK *wk)
{
  POKEPARK_DATA *ppark;
  SAVE_RESULT result;

  ppark = SaveData_GetPokeParkData(wk->sv);
  // �Z�[�u�Ǘ��p�f�[�^���Z�b�g
  POKEPARKDATA_SetMasterData(ppark, agbpoke_GetTrainerID());
  // ���ۂ̃Z�[�u����
  sys_SoftResetNG(SOFTRESET_TYPE_SAVELOAD);
  result = SaveData_Save(wk->sv);
  sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
  //  result = SaveData_SaveParts(wk->sv, SVBLK_ID_MAX);
}


//------------------------------------------------------------------
/**
 * @brief	�q�`�l��̂`�f�a�J�Z�b�g�f�[�^���X�V
 * @brief	�q�`�l��̂c�r�J�[�h�f�[�^���X�V
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridgeDataUpdate(AGBCARTRIDGE_WORK *wk)
{
  int i, boxno, index;
  u16 monsno;

  POKEMON_PASO_PARAM *ds_ppp_ptr;
  PokemonPasoParam *ppp;
  POKEMON_PARAM ds_ppp;
  POKEPARK_DATA *ppark;

  // DS���̃f�[�^���X�V
  
  ppark = SaveData_GetPokeParkData(wk->sv);
  ds_ppp_ptr = PPPPointerGet(&ds_ppp);
  // �I�������U�C���|�P�����p�[�N�̃��[�N�փZ�b�g
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    index = wk->mark[i].pokeno;
    boxno = wk->mark[i].boxno;
    ppp = &wk->boxdata->PPPBox[boxno][index];
    // AGB��PPP��DS��PPP�֕ϊ����Ȃ��珑������
    AGBPPPtoDSPPP(ppp, ds_ppp_ptr);
    POKEPARKDATA_SetData(ppark, ds_ppp_ptr, i);
  }


  // �`�f�a���̃f�[�^���X�V
  
  // �I�����ꂽ�|�P�������{�b�N�X�������
  monsno = 0;
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    index = wk->mark[i].pokeno;
    boxno = wk->mark[i].boxno;
    // ���蓾�Ȃ��������ǔO�̂��߂Ƀ`�F�b�N������
    if(index != POKEMON_NOSELECT && boxno != BOX_NUM){
      AgbPokePasoParaPut(&(wk->boxdata->PPPBox[boxno][index]),ID_AGB_monsno, (u8 *)&monsno);
    }
  }

#if 0
  // ��Ƀf�o�b�O�p�ɒǉ����Ă����܂�(poke_exist_flag��0�Ȃ��monsno��0�ɂ��Ă���)
  for(boxno = 0; boxno < BOX_NUM; boxno++){
    for(i = 0; i < POKEMON_ICON_MAX; i++){
      if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[boxno][i]),ID_AGB_poke_exist_flag, NULL) == 0)
	AgbPokePasoParaPut(&(wk->boxdata->PPPBox[boxno][i]),ID_AGB_monsno, (u8 *)&monsno);
    }
  }
#endif

#if 0//def DEBUG_ONLY_FOR_mituhara
  // �|�P�����������B����(���ӂ�)
  if(sys.cont & PAD_BUTTON_B){
    MATHRandContext16 context;
    u8 name[MONS_NAME_SIZE+1] = { JP_AGB_A__, JP_AGB_B__, JP_AGB_C__, JP_AGB_D__, JP_AGB_E__,
				  JP_AGB_F__, JP_AGB_G__, JP_AGB_H__, JP_AGB_I__, JP_AGB_J__ };
    u8 oyaname[PERSON_NAME_SIZE+1] = { JP_AGB_K__, JP_AGB_L__, JP_AGB_M__, JP_AGB_N__, JP_AGB_O__, JP_AGB_P__, JP_AGB_Q__ };
    
    PokemonPasoParam ppp = wk->boxdata->PPPBox[0][0];
    MATH_InitRand16(&context, 0xabab);

    for(boxno = 0; boxno < BOX_NUM; boxno++){
      for(i = 0; i < POKEMON_ICON_MAX; i++){
	monsno = MATH_Rand16(&context, 386);
	AgbPokePasoParaPut(&ppp, ID_AGB_monsno, (u8 *)&monsno);
#if 0	// �C�O�ŃJ�Z�b�g�e�X�g
	monsno = LANG_ENGLISH;
	AgbPokePasoParaPut(&ppp, ID_AGB_country_code, (u8 *)&monsno);
	AgbPokePasoParaPut(&ppp, ID_AGB_nickname, name);
	AgbPokePasoParaPut(&ppp, ID_AGB_oyaname, oyaname);
#endif
	wk->boxdata->PPPBox[boxno][i] = ppp;
      }
    }
  }
#endif
}


//------------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�Z���^�����O
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetMessageStartPos(REGWIN *rwin, STRBUF *str, int flag)
{
  int len, width;
  if(flag & MSG_FLAG_CENTER){
    len = FontProc_GetPrintStrWidth(FONT_TALK, (const STRBUF *)str, 0);
    width = rwin->width * 8;
    return (width - len) / 2;
  } else {
    return rwin->dx;
  }
}

//------------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�E�B���h�E�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateMsgWindow(AGBCARTRIDGE_WORK *wk, REGWIN *rwin, int flag)
{
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  int x, y, msgwait;

  if(rwin->msgwait == 0)	msgwait = MSG_NO_PUT;
  else				msgwait = rwin->msgwait;

  // �E�B���h�E���o�^����Ă��Ȃ���Γo�^
  if(rwin->win->ini == NULL){
    GF_BGL_BmpWinAdd(wk->bgl, rwin->win, rwin->screen,
		     rwin->sx, rwin->sy, rwin->width, rwin->height,
		     FONT_PALNO_NORMAL, rwin->base);
  }
  // �E�B���h�E��������
  if(!(flag & MSG_FLAG_NOCLEAR))
    GF_BGL_BmpWinDataFill(rwin->win, rwin->clrcolor);

  // ���b�Z�[�W������Ε\��
  if(rwin->msgid != -1){
    // �A�[�J�C�u����W�J���ĕ\��
    msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_pokemonpark_dat, HEAPID_AGBCARTRIDGE);
    if(rwin->word)	word = rwin->word;
    else		word = WORDSET_Create(HEAPID_AGBCARTRIDGE);
    msg = MSGDAT_UTIL_AllocExpandString(word, msgman, rwin->msgid, HEAPID_AGBCARTRIDGE);
    x = GetMessageStartPos(rwin, msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, msg, x, rwin->dy, msgwait, rwin->color, NULL);
    STRBUF_Delete(msg);
    if(rwin->word == NULL)
      WORDSET_Delete(word);
    MSGMAN_Delete(msgman);
    rwin->msgid = -1;
  }
  if(rwin->msgp){
    // ������𒼐ڕ\��
    msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
    STRBUF_SetStringCodeOrderLength(msg, rwin->msgp, 64);
    x = GetMessageStartPos(rwin, msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, msg, x, rwin->dy, msgwait, rwin->color, NULL);
    STRBUF_Delete(msg);
    rwin->msgp = NULL;
  }
  if(rwin->msg){
    // STRBUF�`��\��
    x = GetMessageStartPos(rwin, rwin->msg, flag);
    rwin->m_id = GF_STR_PrintColor(rwin->win, rwin->font, rwin->msg, x, rwin->dy, msgwait, rwin->color, NULL);
    rwin->msg = NULL;
  }
  // �t���O�ɂ���ĕ`��
  if(!(flag & MSG_FLAG_NOREDRAW))
    GF_BGL_BmpWinOn(rwin->win);
  // �g������ꍇ������܂�
  if(flag & MSG_FLAG_FRAME){
    if(flag & MSG_FLAG_TALKWIN){
      BmpTalkWinWrite(rwin->win, WINDOW_TRANS_ON, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL);
    } else {
      BmpMenuWinWrite(rwin->win, WINDOW_TRANS_ON, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL);
    }
  }
}

//------------------------------------------------------------------
/**
 * @brief	�L�����N�^�A�p���b�g�̃}�l�[�W���[�N��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CharPlttManagerInit(void)
{
  // �L�����N�^�}�l�[�W���[������
  {
    CHAR_MANAGER_MAKE cm = {
      RECORD_CHAR_CONT_NUM,
      RECORD_CHAR_VRAMTRANS_MAIN_SIZE,
      RECORD_CHAR_VRAMTRANS_SUB_SIZE,
      HEAPID_AGBCARTRIDGE,
    };
    InitCharManager(&cm);
  }
  // �p���b�g�}�l�[�W���[������
  InitPlttManager(RECORD_PLTT_CONT_NUM, HEAPID_AGBCARTRIDGE);
      
  // �ǂݍ��݊J�n�ʒu��������
  CharLoadStartAll();
  PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(AGBCARTRIDGE_WORK *wk)
{
  int i;
  // OAM�}�l�[�W���[�̏�����
  NNS_G2dInitOamManagerModule();
  // ���LOAM�}�l�[�W���쐬
  // �����_���pOAM�}�l�[�W���쐬
  // �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
  REND_OAMInit( 
	       0, 126,		// ���C�����OAM�Ǘ��̈�
	       0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
	       0, 126,		// �T�u���OAM�Ǘ��̈�
	       0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
	       HEAPID_AGBCARTRIDGE);
	
  // �Z���A�N�^�[������
  wk->clactSet = CLACT_U_SetEasyInit( 80, &wk->renddata, HEAPID_AGBCARTRIDGE);
  CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, (256*FX32_ONE)/*NAMEIN_SUB_ACTOR_DISTANCE*/ );

  //���\�[�X�}�l�[�W���[������
  for(i=0;i<CLACT_U_RES_MAX;i++){		//���\�[�X�}�l�[�W���[�쐬
    wk->resMan[i] = CLACT_U_ResManagerInit(3, i, HEAPID_AGBCARTRIDGE);
  }

  //---------���ʗp-------------------
  //chara�ǂݍ���
  wk->resObjTbl[CLACT_U_CHAR_RES] =
    CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
				    ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_cngr,
				    1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_AGBCARTRIDGE);
      
  //pal�ǂݍ���
  wk->resObjTbl[CLACT_U_PLTT_RES] =
    CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
				    ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_nclr,
				    0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 4, HEAPID_AGBCARTRIDGE);

  //cell�ǂݍ���
  wk->resObjTbl[CLACT_U_CELL_RES] =
    CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
					ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_ccer,
					1, 0, CLACT_U_CELL_RES,HEAPID_AGBCARTRIDGE);

  //�����֐���anim�ǂݍ���
  wk->resObjTbl[CLACT_U_CELLANM_RES] =
    CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
					ARC_MYSTERY_GRA, NARC_mystery_gba_box_oam_lz_canr,
					1, 0, CLACT_U_CELLANM_RES,HEAPID_AGBCARTRIDGE);
  // Chara�]��
  CLACT_U_CharManagerSet( wk->resObjTbl[CLACT_U_CHAR_RES] );
  // �p���b�g�]��
  CLACT_U_PlttManagerSet( wk->resObjTbl[CLACT_U_PLTT_RES] );
  // �|�P�����A�C�R���p�p���b�g����C�ɓǂݍ����VRAM�]������
  ArcUtil_PalSet( ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20,
		  0, HEAPID_AGBCARTRIDGE);
}


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�w�b�_�̍쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCellActor(AGBCARTRIDGE_WORK *wk)
{
  // �Z���A�N�^�[�w�b�_�쐬
  CLACT_U_MakeHeader(&wk->clActHeaderMain, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
		     0, 0,
		     wk->resMan[CLACT_U_CHAR_RES],
		     wk->resMan[CLACT_U_PLTT_RES],
		     wk->resMan[CLACT_U_CELL_RES],
		     wk->resMan[CLACT_U_CELLANM_RES],
		     NULL,NULL);
  //�܂������]�����Ă��Ȃ�����
  GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
}


//------------------------------------------------------------------
/**
 * @brief	CLACT_ADD�̐��`���쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbPokemon_MakeCLACT(CLACT_ADD *add, AGBCARTRIDGE_WORK *wk, CLACT_HEADER *header, int param)
{
  add->ClActSet		= wk->clactSet;
  add->ClActHeader	= &wk->clActHeaderMain;
  add->mat.z		= 0;
  add->sca.x		= FX32_ONE;
  add->sca.y		= FX32_ONE;
  add->sca.z		= FX32_ONE;
  add->rot		= 0;
  add->pri		= 20;
  add->DrawArea		= param;
  add->heap		= HEAPID_AGBCARTRIDGE;
}


//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃{�b�N�X����index�Ԗڂ̃|�P������Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetPokeBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGB�̍\���̐�p�֐���p�ӂ��Ă��܂�
  // DP�̍\���̂ƍ�����Ȃ��悤�A���Ȃ蒍�ӂ��Ă��������܂�
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_monsno, NULL);
}

//Add by soga�@��������
//�|�P�����A�C�R���\���ŕK�v�ȃp�����[�^��ǉ����܂���
//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃{�b�N�X����index�Ԗڂ̃^�}�S�t���O��Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetEggFlagBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGB�̍\���̐�p�֐���p�ӂ��Ă��܂�
  // DP�̍\���̂ƍ�����Ȃ��悤�A���Ȃ蒍�ӂ��Ă��������܂�
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_tamago_flag, NULL);
}

//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃{�b�N�X����index�Ԗڂ̌�������Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetPersonalRndBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGB�̍\���̐�p�֐���p�ӂ��Ă��܂�
  // DP�̍\���̂ƍ�����Ȃ��悤�A���Ȃ蒍�ӂ��Ă��������܂�
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_personal_rnd, NULL);
}

//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃{�b�N�X����index�Ԗڂ̃Q�b�g�o�[�W������Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int GetCassetteVersionBoxIndex(AGBCARTRIDGE_WORK *wk, int box, int index)
{
  // AGB�̍\���̐�p�֐���p�ӂ��Ă��܂�
  // DP�̍\���̂ƍ�����Ȃ��悤�A���Ȃ蒍�ӂ��Ă��������܂�
  return AgbPokePasoParaGet(&(wk->boxdata->PPPBox[box][index]), ID_AGB_get_cassette, NULL);
}
//Add by soga�@�����܂�

//------------------------------------------------------------------
/**
 * @brief	RECT_HIT_TBL��o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetRectHitTable(RECT_HIT_TBL *rect, int x, int y, int sizx, int sizy)
{
  rect->rect.top    = y - sizy / 2;
  rect->rect.left   = x - sizx / 2;
  rect->rect.bottom = y + sizy / 2;
  rect->rect.right  = x + sizx / 2;
}

//------------------------------------------------------------------
/// @brief	�q�[�v�T�C�Y���Œ�ɂ����ł�ArcUtrl_CahrDataGet
//------------------------------------------------------------------
static void *ArcUtil_CharDataGet2(u32 fileIdx, u32 dataIdx, NNSG2dCharacterData** charData, u32 heapID)
{
  void* arcData;

  arcData = sys_AllocMemoryLo(heapID, 4096);	/* �q�[�v�T�C�Y�Œ� */
  if(arcData != NULL){
    ArchiveDataLoad(arcData, fileIdx, dataIdx);
    if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE){
      // ���s������NULL
      sys_FreeMemoryEz( arcData );
      return NULL;
    }
  }
  return arcData;
}
static void ArcUtil_CharDataGet3(u32 dataIdx, NNSG2dCharacterData** charData, void *arcData, ARCHANDLE* handle)
{
  ArchiveDataLoadByHandle(handle, dataIdx, arcData);
  NNS_G2dGetUnpackedBGCharacterData( arcData, charData );
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�����̃t�H�����i���o�[���擾
 * @param	pokeno			�擾����|�P�����i���o�[
 * @param	personal_rnd	�擾���邽�߂ɕK�v�Ȍ�����
 * @param	get_cassette	�擾���邽�߂ɕK�v�ȃQ�b�g�J�Z�b�g�o�[�W����
 *
 * @return	�擾�����t�H�����i���o�[
 */
//------------------------------------------------------------------
static	u8	GetPokeFormNo(int pokeno,u32 personal_rnd,int get_cassette)
{
	u8	form_no;

	form_no=0;

#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_TPrintf("MONSNO_DEOKISISU: %d - %d\n", MONSNO_DEOKISISU, pokeno);
	OS_TPrintf("get_cassette\n", get_cassette);
#endif

	switch(pokeno){
	//�A���m�[���̃t�H�������擾
	case MONSNO_ANNOON:
		form_no=(((personal_rnd&0x03000000)>>18)|
				 ((personal_rnd&0x00030000)>>12)|
				 ((personal_rnd&0x00000300)>> 6)|
				  (personal_rnd&0x00000003))%28;
		break;
	case MONSNO_DEOKISISU:
		switch(get_cassette){
		default:
		case VERSION_RUBY:
		case VERSION_SAPPHIRE:
			//���r�[�E�T�t�@�C�A�E���m�̃o�[�W�����̓m�[�}��
			form_no=FORMNO_DEOKISISU_NORMAL;
			break;
		case VERSION_RED:
			//�t�@�C�A���b�h�̓A�^�b�N
			form_no=FORMNO_DEOKISISU_ATTACK;
			break;
		case VERSION_GREEN:
			//���[�t�O���[���̓f�B�t�F���X
			form_no=FORMNO_DEOKISISU_DEFENCE;
			break;
		case VERSION_EMERALD:
			//�G�������h�̓X�s�[�h
			form_no=FORMNO_DEOKISISU_SPEED;
			break;
		}
		break;
	}

	return form_no;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�����̃A�C�R�����u�q�`�l�֓o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( int pokeno, int tamago_flag, u32 personal_rnd, int get_cassette, int no, CLACT_WORK_PTR icon)
{
  u8 *buf;
  u8 form_no;
  NNSG2dCharacterData *chara;

  // AGB�|�P������DP�|�P�����֕ϊ�
  pokeno = ChangeAGBPoke2DPPoke(pokeno);

  // �|�P�����̃t�H�����i���o�[���擾(�����DS��monsno�Ŕ���)
  form_no = GetPokeFormNo(pokeno,personal_rnd,get_cassette);

  buf = ArcUtil_CharDataGet2( ARC_POKEICON, 
			      PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago_flag, form_no ), &chara, HEAPID_AGBCARTRIDGE);
  DC_FlushRange(chara->pRawData, POKEICON_TRANS_SIZE);

  // �L�����N�^�[�]��
  GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20, POKEICON_TRANS_SIZE);
  // �p���b�g�ݒ�
  CLACT_PaletteNoChg( icon,  PokeIconPalNumGet( pokeno, form_no, tamago_flag )+POKEICON_PAL_OFFSET );

  sys_FreeMemoryEz(buf);
}

static void TransPokeIconCharaPal2(int pokeno, int tamago_flag, int form_no,
				   int no, CLACT_WORK_PTR icon, void *buf, ARCHANDLE* handle)
{
  u32 dataidx;
  NNSG2dCharacterData *chara;
  POKEBUF *pbuf = _PokeBufPtr + no;

  if(icon){
#if 0
    // AGB�|�P������DP�|�P�����֕ϊ�
    pokeno = ChangeAGBPoke2DPPoke(pokeno);
#else

    if(CheckInJusticePokemon(pokeno) == FALSE)
      // AGB�|�P������DP�|�P�����֕ϊ�
      pokeno = ChangeAGBPoke2DPPoke(pokeno);
    else
      // �s���|�P����
      pokeno = 0;
#endif
    // �|�P�����̃f�[�^�C���f�b�N�X�ԍ����擾
    dataidx = PokeIconCgxArcIndexGetByMonsNumber( pokeno, tamago_flag, form_no );
    // �|�P�����L�����N�^���o�b�t�@�ɓ]��
    ArcUtil_CharDataGet3(dataidx, &chara, buf, handle);
    MI_CpuCopyFast(chara->pRawData, pbuf->chbuf, POKEICON_TRANS_SIZE);
    pbuf->vadrs = (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20;
    pbuf->icon = icon;
    pbuf->palno = PokeIconPalNumGet( pokeno, form_no, tamago_flag )+POKEICON_PAL_OFFSET;
  } else {
    pbuf->icon = NULL;
  }
}

static void TransPokeIconFinish(void)
{
  int i;
  POKEBUF *pbuf = _PokeBufPtr;
  for(i = 0; i < POKEMON_ICON_MAX; i++, pbuf++){
    if(pbuf->icon){
      // �L�����N�^�[�]��
      DC_FlushRange(pbuf->chbuf, POKEICON_TRANS_SIZE);
      GX_LoadOBJ(pbuf->chbuf, pbuf->vadrs, POKEICON_TRANS_SIZE);
      // �p���b�g�ݒ�
      CLACT_PaletteNoChg(pbuf->icon, pbuf->palno);
    }
  }
}


     
//------------------------------------------------------------------
/**
 * @brief	�w��{�b�N�X�̃|�P��������ʂɕ\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RedrawPokemonBox(AGBCARTRIDGE_WORK *wk)
{
  int i, monsno, tamago_flag, get_cassette, form_no;
  u32 personal_rnd;
  void *buf;
  ARCHANDLE* handle;

  handle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_AGBCARTRIDGE);
  buf = sys_AllocMemoryLo(HEAPID_AGBCARTRIDGE, 4096);

  // �|�P�����A�C�R���̕\��
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[wk->CurrentBox][i]), ID_AGB_poke_exist_flag, NULL)){
      monsno = GetPokeBoxIndex(wk, wk->CurrentBox, i);
      //add by soga�@��������
      tamago_flag = GetEggFlagBoxIndex(wk, wk->CurrentBox, i);
      personal_rnd = GetPersonalRndBoxIndex(wk, wk->CurrentBox, i);
#if 0
      get_cassette = GetCassetteVersionBoxIndex(wk, wk->CurrentBox, i);
#else
      get_cassette = sys.AgbCasetteVersion;
#endif
      //add by soga�@�����܂�

      // �|�P�����̃t�H�����i���o�[���擾(�����DS��monsno�Ŕ���)
      form_no = GetPokeFormNo(ChangeAGBPoke2DPPoke(monsno), personal_rnd, get_cassette);
      TransPokeIconCharaPal2(monsno, tamago_flag, form_no, i, wk->icon[i].clact, buf, handle);
      CLACT_SetDrawFlag( wk->icon[i].clact, 1 );
      // �A�C�e���A�C�R���̓o�^
      if(AgbPokePasoParaGet(&(wk->boxdata->PPPBox[wk->CurrentBox][i]), ID_AGB_item, NULL))
	CLACT_SetDrawFlag( wk->icon[i].item, 1 );
      else
	CLACT_SetDrawFlag( wk->icon[i].item, 0 );
    } else {
      TransPokeIconCharaPal2(monsno, tamago_flag, form_no, i, NULL, buf, handle);
      CLACT_SetDrawFlag( wk->icon[i].clact, 0 );
      CLACT_SetDrawFlag( wk->icon[i].item, 0 );
    }
  }
  sys_FreeMemoryEz(buf);
  ArchiveDataHandleClose( handle );

  
  // �|�P�����A�C�R���̓]���֐����`
  wk->DrawFunc = TransPokeIconFinish;
  
  // �{�b�N�X�̃^�C�g���\��
  DrawBoxTitle(wk, wk->CurrentBox);
  // �I���A�C�R���𔽉f
  CheckSelectPokemonIcon(wk);
}


//------------------------------------------------------------------
/**
 * @brief	��ʂɃ|�P�������R�O���ׂ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetPokemonIcon(AGBCARTRIDGE_WORK *wk)
{
  int index, x, y;
  CLACT_ADD add;

  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );

  index = 0;
  for(y = 0; y < 5; y++){
    for(x = 0; x < 6; x++){

      SetRectHitTable(&wk->iconrect[index],
		      x * POKEMON_WIDTH  + POKEMON_BASEX,
		      y * POKEMON_HEIGHT + POKEMON_BASEY,
		      28, 28);
      add.mat.x = FX32_ONE * (x * POKEMON_WIDTH  + POKEMON_BASEX);
      add.mat.y = FX32_ONE * (y * POKEMON_HEIGHT + POKEMON_BASEY);
      // �|�P�����̃A�C�R���o�^
      if(wk->icon[index].clact == NULL)
	wk->icon[index].clact = CLACT_Add(&add);
      CLACT_SetAnmFlag(wk->icon[index].clact, 1);
      CLACT_AnmChg( wk->icon[index].clact, 10+index );
      CLACT_BGPriorityChg( wk->icon[index].clact, 1 );
      CLACT_SetDrawFlag( wk->icon[index].clact, 1 );
      CLACT_DrawPriorityChg( wk->icon[index].clact, 100+index);
      // �A�C�e���̃A�C�R���o�^
      add.mat.x += FX32_ONE * 6;
      add.mat.y += FX32_ONE * 12;
      if(wk->icon[index].item == NULL)
	wk->icon[index].item = CLACT_Add(&add);
      CLACT_SetAnmFlag(wk->icon[index].item, 1);
      CLACT_AnmChg( wk->icon[index].item, 40);
      CLACT_BGPriorityChg( wk->icon[index].item, 1 );
      CLACT_SetDrawFlag( wk->icon[index].item, 0 );
      CLACT_DrawPriorityChg( wk->icon[index].item, 0+index);

      index++;
      if(index == POKEMON_ICON_MAX)	return;
    }
  }
}


//------------------------------------------------------------------
/**
 * @brief	�|�P�����ȊO�̃A�C�R����o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static CLACT_WORK_PTR SetOamIcon(AGBCARTRIDGE_WORK *wk, int x, int y, int anim, int flag)
{
  CLACT_ADD add;
  CLACT_WORK_PTR p;
  
  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );
  add.mat.x = FX32_ONE * x;
  add.mat.y = FX32_ONE * y;
  add.pri   = 10;
  p = CLACT_Add(&add);
  CLACT_SetAnmFlag(p, 1);
  CLACT_AnmChg(p, anim);
  CLACT_BGPriorityChg(p, 1);
  CLACT_SetDrawFlag(p, flag);
  return p;
}
static void SetMiscIcon(AGBCARTRIDGE_WORK *wk)
{
  int i;

  SetRectHitTable(&wk->iconrect[ICON_CANCEL], 228, 176, 50, 32);
  wk->cancel[0] = SetOamIcon(wk, 228, 176, 6, 1);	// ��߂�

  SetRectHitTable(&wk->iconrect[ICON_ARROWR], 176, 176, 32, 32);
  wk->arrowr[0] = SetOamIcon(wk, 176, 176, 3, 1);	// �E��

  SetRectHitTable(&wk->iconrect[ICON_ARROWL],  24, 176, 32, 32);
  wk->arrowl[0] = SetOamIcon(wk,  24, 176, 0, 1);	// ����

  wk->iconrect[ICON_TERMINATE].rect.top = RECT_HIT_END;

  // ����A�C�R���̓o�^
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    wk->mark[i].icon = SetOamIcon(wk, 36*i, 64, 9, 0);
    wk->mark[i].pokeno = POKEMON_NOSELECT;
    wk->mark[i].boxno = BOX_NUM;
  }
  wk->selected = 0;
}


//------------------------------------------------------------------
/**
 * @brief	�|�P�����̃^�}�S�`�F�b�N
 * @param	NONE
 * @return	TRUE: ���܂��ł����@FALSE: ���܂�����Ȃ�
 */
//------------------------------------------------------------------
static BOOL CheckPokemonEgg(AGBCARTRIDGE_WORK *wk, int num)
{
  int monsno;
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];

  if(AgbPokePasoParaGet(ppp, ID_AGB_monsno_egg, NULL) == MONSNO_AGB_TAMAGO)
    return TRUE;
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�Ђł�킴�������Ă��邩�`�F�b�N
 * @param	NONE
 * @return	TRUE: �����Ă��@FALSE: �����ĂȂ�
 */
//------------------------------------------------------------------
static BOOL CheckPokemonHidenWaza(AGBCARTRIDGE_WORK *wk, int num)
{
  int w, i, waza;

  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];

  for(w = 0; w < 4; w++){
    waza = AgbPokePasoParaGet(ppp, ID_AGB_waza1 + w, NULL);
    for(i = 0; i < sizeof(WazaHidenTable) / sizeof(int); i++){
      if(WazaHidenTable[i] == waza)
	return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�����Ă����Ȃ��A�C�e���������Ă��Ȃ����`�F�b�N
 * @param	NONE
 * @return	TRUE: �����Ă��@FALSE: �����ĂȂ�
 */
//------------------------------------------------------------------
#include "agbitemexist.h"
static BOOL CheckPokemonExistItem(AGBCARTRIDGE_WORK *wk, int num)
{
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];
  int item = AgbPokePasoParaGet(ppp, ID_AGB_item, NULL);
  int i;

  for(i = 0; AgbItemExistCheck[i]; i++){
    if(item == AgbItemExistCheck[i])
      return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�s���ȃ|�P�����`�F�b�N
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL CheckPokemonFusei(AGBCARTRIDGE_WORK *wk, int num)
{
  PokemonPasoParam *ppp = &wk->boxdata->PPPBox[wk->CurrentBox][num];
  int monsno = AgbPokePasoParaGet(ppp, ID_AGB_monsno, NULL);
  return CheckInJusticePokemon(monsno);
}


//------------------------------------------------------------------
/**
 * @brief	�w�肵���A�C�R���̉��Ɍ���A�C�R���𐧌�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define SELECT_POKEMON_FULL	0		// ���łɂ����ς�
#define SELECT_POKEMON_SELECT	1		// �I������
#define SELECT_POKEMON_CANCEL	2		// ��������
#define SELECT_POKEMON_NOMONS	3		// �������������ɂ��Ȃ�
#define SELECT_POKEMON_EGG	4		// ���͂��܂�������
#define SELECT_POKEMON_WAZA	5		// �Ђł�킴�������Ă���
#define SELECT_POKEMON_ITEM	6		// �����Ă����Ȃ��A�C�e���������Ă�
#define SELECT_POKEMON_FUSEI	7		// �s���ȃ|�P�����ԍ�������

static int SelectPokemon(AGBCARTRIDGE_WORK *wk, int num)
{
  int i, sel;

  // �󔒂̃`�F�b�N
  if(wk->icon[num].clact && CLACT_GetDrawFlag(wk->icon[num].clact) == FALSE)
    return SELECT_POKEMON_NOMONS;
  
  // ���łɑI���ς݂Ȃ̂��𒲂ׂ�
  for(sel = -1, i = 0; sel == -1 && i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].boxno == wk->CurrentBox &&
       wk->mark[i].pokeno == num)
      sel = i;
  }
#if 0	// the �����N
  return SELECT_POKEMON_ITEM;
#endif
  
  // ���܂��`�F�b�N
  if(CheckPokemonEgg(wk, num) == TRUE)
    return SELECT_POKEMON_EGG;

  // �Ђł�킴�������Ă��邩�`�F�b�N
  if(CheckPokemonHidenWaza(wk, num) == TRUE)
    return SELECT_POKEMON_WAZA;

  // �����Ă����Ȃ��A�C�e���������Ă��邩�`�F�b�N
  if(CheckPokemonExistItem(wk, num) == TRUE)
    return SELECT_POKEMON_ITEM;

  // �s���ȃ|�P�������`�F�b�N
  if(CheckPokemonFusei(wk, num) == TRUE)
    return SELECT_POKEMON_FUSEI;
  
  if(sel == -1){
    // �I������Ă��Ȃ������ꍇ
    const VecFx32 *vec;
    VecFx32 nvec;

    // ���łɂU�C���I������Ă����牽�����Ȃ�
    if(wk->selected == POKEMON_SELECT_MAX)
      return SELECT_POKEMON_FULL;

    for(i = 0; i < POKEMON_SELECT_MAX; i++)
      if(wk->mark[i].pokeno == POKEMON_NOSELECT){
	// ���̃|�P����������W���𓾂�(�|�C���^�𓾂邾��)
	vec = CLACT_GetMatrix(wk->icon[num].clact);
	// ���̏����A�C�R���փR�s�[����
	CLACT_SetMatrix(wk->mark[i].icon, vec);
	// ���̃R�s�[�������̃|�C���^�𓾂āc
	vec = CLACT_GetMatrix(wk->mark[i].icon);
	// ���W���|�P�����̍���ɃI�t�Z�b�g�ړ�
	nvec = *vec;
	nvec.x -= FX32_ONE * 8;
	nvec.y -= FX32_ONE * 4;
	CLACT_SetMatrix(wk->mark[i].icon, &nvec);
	// �A�C�R���̕\���t���O��ON
  	CLACT_SetDrawFlag(wk->mark[i].icon, 1);
	wk->mark[i].pokeno = num;
	wk->mark[i].boxno = wk->CurrentBox;
	wk->selected++;
	return SELECT_POKEMON_SELECT;
      }

  } else {
    // �I������Ă����ꍇ
    CLACT_SetDrawFlag(wk->mark[sel].icon, 0);
    wk->mark[sel].pokeno = POKEMON_NOSELECT;
    wk->selected--;
    return SELECT_POKEMON_CANCEL;
  }
  return SELECT_POKEMON_FULL;
}


//------------------------------------------------------------------
/**
 * @brief	�����{�b�N�X�Ȃ�΃A�C�R���\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CheckSelectPokemonIcon(AGBCARTRIDGE_WORK *wk)
{
  int i;
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].pokeno != POKEMON_NOSELECT && wk->mark[i].boxno == wk->CurrentBox){
      CLACT_SetDrawFlag(wk->mark[i].icon, 1);
    } else {
      CLACT_SetDrawFlag(wk->mark[i].icon, 0);
    }
  }
}



//------------------------------------------------------------------
/**
 * @brief	�{�b�N�X�^�C�g���̕\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DrawBoxTitle(AGBCARTRIDGE_WORK *wk, int boxnumber)
{
  REGWIN rwin;
  STRCODE title[BOXNAME_MAX+EOM_SIZE];

  memset(&rwin, 0, sizeof(REGWIN));
  rwin.win = &wk->TitleWin;
  rwin.sx = 6;
  rwin.sy = 21;
  rwin.width = 13;
  rwin.height = 2;
  rwin.msgid = -1;
  rwin.dx = 0;
  rwin.dy = 0;
  rwin.screen = GF_BGL_FRAME1_M;
  rwin.font = FONT_TALK;
  rwin.color = AGBPOKEMON_BLACK;
  rwin.base = AGBPOKEMON_TITLEBASE;
  AGBSTR_to_DSSTR(wk->boxdata->BoxName[boxnumber], title, BOXNAME_MAX+EOM_SIZE, agbpoke_getPokemonLanguage());
  rwin.msgp = title;
  CreateMsgWindow(wk, &rwin, MSG_FLAG_CENTER);
}


//------------------------------------------------------------------
/**
 * @brief	�|�P�����̃}�[�N����\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DrawStatusPokeMark(AGBCARTRIDGE_WORK *wk, PokemonPasoParam *ppp)
{
  u16 *scrn = GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  u8 mark;
  int i;

  if(ppp)	mark = AgbPokePasoParaGet(ppp, ID_AGB_mark, NULL);
  else		mark = 0;

  for(i = 0; i < 4; i++){
    if(mark & 1)	scrn[32*3 + 11 + i] = 0x0080 + i;
    else		scrn[32*3 + 11 + i] = 0x0060 + i;
    mark >>= 1;
  }
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	���E�B���h�E��\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define SetRWin(msg, x, y)	rwin.msgid = (msg), rwin.dx = (x), rwin.dy = (y);
static void DrawStatusWindow(AGBCARTRIDGE_WORK *wk, PokemonPasoParam *ppp)
{
  int monsno, level;
  int agb_item, dp_item;
  REGWIN rwin;
  MSGDATA_MANAGER* man;
  u8 agb_name[MONS_NAME_SIZE+AGB_EOM_SIZE];
  STRCODE ds_name[MONS_NAME_SIZE+AGB_EOM_SIZE];
  STRBUF *msg;

  memset(&rwin, 0, sizeof(REGWIN));
  rwin.win = &wk->BoxNameWin;
  rwin.sx = 0;
  rwin.sy = 0;
  rwin.width = 32;
  rwin.height = 4;
  rwin.screen = GF_BGL_FRAME1_M;
  rwin.font = FONT_TALK;
  rwin.base = AGBPOKEMON_STATUSBASE;
  rwin.color = AGBPOKEMON_WHITE;
  rwin.msgp = NULL;

  // �u�������́v
  SetRWin(msg_pokepark__status_02, 18*8, 0);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW);
  // �uLv.�v
  SetRWin(msg_pokepark__status_01, 10*8, 8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
  // �}�[�N
  DrawStatusPokeMark(wk, ppp);

  // PPP�̎w�肪�Ȃ���΂���ȍ~�͏������Ȃ�
  if(ppp == NULL){
    GF_BGL_BmpWinOn(rwin.win);
    return;
  }

  // �j�b�N�l�[��(������̃|�P�����������Ă���\��������)
  AgbPokePasoParaGet(ppp, ID_AGB_nickname, agb_name);
  AGBSTR_to_DSSTR(agb_name, ds_name, MONS_NAME_SIZE+AGB_EOM_SIZE, AgbPokePasoParaGet(ppp, ID_AGB_country_code, NULL));
  rwin.msgp = ds_name;
  SetRWin(-1, 1*8, 0);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);

  // �|�P������
  msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
  man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_AGBCARTRIDGE);
  // [[[�����Ń|�P�����̐��ʓ����`�F�b�N�ł���]]]
  monsno = ChangeAGBPoke2DPPoke(AgbPokePasoParaGet(ppp, ID_AGB_monsno, NULL));
  MSGMAN_GetString(man, monsno, msg);
  rwin.msg = msg;
  SetRWin(-1, 2*8, 2*8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
  MSGMAN_Delete(man);
  STRBUF_Delete(msg);

  // �����Ă���A�C�e����
  agb_item = AgbPokePasoParaGet(ppp, ID_AGB_item, NULL);
  if(agb_item){
    dp_item = ITEM_AgbItemCnv(agb_item);
    msg = STRBUF_Create(64, HEAPID_AGBCARTRIDGE);
    GetItemName(msg, dp_item, HEAPID_AGBCARTRIDGE);
    rwin.msg = msg;
    SetRWin(-1, 19*8, 2*8);
    CreateMsgWindow(wk, &rwin, MSG_FLAG_NOREDRAW|MSG_FLAG_NOCLEAR);
    STRBUF_Delete(msg);
  }
  
  // ���x��
  level = AgbPokePasoLevelCalc(ppp);
  msg = STRBUF_Create(10, HEAPID_AGBCARTRIDGE);
  STRBUF_SetNumber(msg, level,  3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  rwin.msg = msg;
  SetRWin(-1, 12*8+4, 1*8);
  CreateMsgWindow(wk, &rwin, MSG_FLAG_NOCLEAR);
  STRBUF_Delete(msg);

  // �|�P�����{�C�X��炷
  Snd_PMVoicePlay(monsno);
}

//------------------------------------------------------------------
/**
 * @brief	�t�F�[�h����
 *
 * @param	none
 * @return	none
 */
//------------------------------------------------------------------
static void RequestFade(AGBCARTRIDGE_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_AGBCARTRIDGE);
  if(seq)
    SetSeq(AGBCARTRIDGE_SEQ_WAIT_FADE);
  wk->next_seq = next_seq;
}
static void RequestFadeW(AGBCARTRIDGE_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_WHITE,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_AGBCARTRIDGE);
  if(seq)
    SetSeq(AGBCARTRIDGE_SEQ_WAIT_FADE);
  wk->next_seq = next_seq;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	BG������
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit(GF_BGL_INI * ini)
{
  {	/* BG SYSTEM */
    GF_BGL_SYS_HEADER BGsys_data = {
      GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
    };
    GF_BGL_InitBG( &BGsys_data );
  }

  {	/* MAIN DISP BG0 */
    GF_BGL_BGCNT_HEADER MBg0_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &MBg0_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
  }

  {	/* MAIN DISP BG1 */
    GF_BGL_BGCNT_HEADER MBg1_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &MBg1_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
  }

  {	/* MAIN DISP BG2 */
    GF_BGL_BGCNT_HEADER MBg2_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_23, 2, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &MBg2_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
  }

  {	/* MAIN DISP BG3 */
    GF_BGL_BGCNT_HEADER MBg3_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_23, 3, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &MBg3_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
  }
}


//------------------------------------------------------------------
/**
 * @brief	�X�N���[���쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateAgbCartridgeScreen(AGBCARTRIDGE_WORK *wk)
{
  GF_BGL_DISPVRAM tbl = {
    GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
    GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g

    GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
    GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g

    GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
    GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

    GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

    GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
    GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
  };
  GF_Disp_SetBank( &tbl );

  BgInit(wk->bgl);

  // �㉺��ʂ��Ђ�����Ԃ�
  sys.disp3DSW = DISP_3D_TO_SUB;
  GF_Disp_DispSelect();
  
  MSG_PrintInit();

  /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_AGBCARTRIDGE);

  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_bg_nclr, PALTYPE_MAIN_BG, 0, 32*6, HEAPID_AGBCARTRIDGE);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main_lz_cngr, wk->bgl,
		    GF_BGL_FRAME2_M, 0, 10*16*0x20, 1, HEAPID_AGBCARTRIDGE);

  // �{�^���p�t�H���g�̓ǂݍ���
  FontProc_LoadFont(FONT_BUTTON, HEAPID_AGBCARTRIDGE);
}
static void CreateAgbCartridgeScreen2(AGBCARTRIDGE_WORK *wk)
{
  // ���C����ʃX�N���[���P
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main1_lz_cscr, wk->bgl,
		  GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_AGBCARTRIDGE);
  // �h�����Ă���`�f�a�J�Z�b�g�ɂ���Ăa�f�̃p���b�g��ς���
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME2_M, 0, 0, 32, 24, BgPalTable[wk->cartridge_type]);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	��E�B���h�E�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitUpMessageWindow(AGBCARTRIDGE_WORK *wk)
{
  // �E�B���h�E�g�ƃp���b�g���u�q�`�l�փ��[�h
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, AGBPOKEMON_FRAMECOL * 32, HEAPID_AGBCARTRIDGE);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL, 0, HEAPID_AGBCARTRIDGE);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL, wk->win_type, HEAPID_AGBCARTRIDGE);

  memset(&wk->cwin, 0, sizeof(REGWIN));
  wk->cwin.win = &wk->CheckWin;
  wk->cwin.sx = 2;
  wk->cwin.sy = 1;
  wk->cwin.width = 27;
  wk->cwin.height = 4;
  wk->cwin.screen = GF_BGL_FRAME0_M;
  wk->cwin.font = FONT_TALK;
  wk->cwin.base = AGBPOKEMON_CHRBASE + 1;
  wk->cwin.color = AGBPOKEMON_BLACKBLACK;
  wk->cwin.clrcolor = AGBPOKEMON_WHITEBLACK;
  wk->cwin.msgp = NULL;
  wk->cwin.msg = NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�m�F��ʂ̃X�N���[�����쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateCheckScreen(AGBCARTRIDGE_WORK *wk)
{
  int i, monsno, tamago_flag, get_cassette;
  u32 personal_rnd;
  CLACT_ADD add;

  // ��ʒ��̃I�u�W�F�N�g�͖���(�������o�^�͎c���Ă���)
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    CLACT_SetDrawFlag( wk->icon[i].clact, 0 );
    CLACT_SetDrawFlag( wk->icon[i].item, 0 );
  }
  for(i = 0; i < POKEMON_SELECT_MAX; i++)
    CLACT_SetDrawFlag( wk->mark[i].icon, 0 );
  CLACT_SetDrawFlag(wk->cancel[0], 0);
  CLACT_SetDrawFlag(wk->arrowl[0], 0);
  CLACT_SetDrawFlag(wk->arrowr[0], 0);
  
  // �V���ɂU�̕��̃A�N�^�[��o�^
  AgbPokemon_MakeCLACT(&add, wk, &wk->clActHeaderMain, NNS_G2D_VRAM_TYPE_2DMAIN );
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    add.mat.x = FX32_ONE * (i * POKEMON_WIDTH  + POKEMON_BASEX);
    add.mat.y = FX32_ONE * 142;
    wk->check_poke[i] = CLACT_Add(&add);
    
    CLACT_SetAnmFlag(wk->check_poke[i], 1);
    CLACT_AnmChg( wk->check_poke[i], 10+i );
    CLACT_BGPriorityChg( wk->check_poke[i], 1 );
    CLACT_SetDrawFlag( wk->check_poke[i], 1 );
    monsno = GetPokeBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
	//add by soga�@��������
    tamago_flag = GetEggFlagBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
    personal_rnd = GetPersonalRndBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
#if 0
    get_cassette = GetCassetteVersionBoxIndex(wk, wk->mark[i].boxno, wk->mark[i].pokeno);
#else
    get_cassette = sys.AgbCasetteVersion;
#endif
	//add by soga�@�����܂�
    TransPokeIconCharaPal(monsno, tamago_flag, personal_rnd, get_cassette, i, wk->check_poke[i]);
  }
  
  // �X�N���[���f�[�^�]��(�L�����N�^�͓���̂��̂��g��)
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_gba_box_main2_lz_cscr, wk->bgl,
		  GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_AGBCARTRIDGE);
  // �h�����Ă���`�f�a�J�Z�b�g�ɂ���Ăa�f�̃p���b�g��ς���
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME2_M, 0, 0, 32, 24, BgPalTable[wk->cartridge_type]);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
  // �|�P�����X�e�[�^�X�\���a�f�͏����Ă��܂�
  GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );

  // �E�B���h�E�g�ƃp���b�g���u�q�`�l�փ��[�h
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, AGBPOKEMON_FRAMECOL * 32, HEAPID_AGBCARTRIDGE);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_FRAMECHR, AGBPOKEMON_FRAMECOL, 0, HEAPID_AGBCARTRIDGE);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, AGBPOKEMON_TFRAMECHR, AGBPOKEMON_TFRAMECOL, wk->win_type, HEAPID_AGBCARTRIDGE);
  
  // ���b�Z�[�W�E�B���h�E���쐬
  InitUpMessageWindow(wk);
  wk->cwin.msgid = msg_pokepark_12;	// ����񂾁@�U�Ђ��́@�|�P������\n��ā@�����܂�
  CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
}


//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DeleteWindow(GF_BGL_BMPWIN *win)
{
  if(win->ini){
    BmpTalkWinClear(win, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(win);
    GF_BGL_BmpWinDel(win);
  }
}


//------------------------------------------------------------------
/**
 * @brief	�I����ʂ𕜊�������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void ReviveSelectScreen(AGBCARTRIDGE_WORK *wk)
{
  int i;
  // �I����ʂɖ߂鏈��


  // �\�����Ă����A�N�^�[�𖕏�
  for(i = 0; i < POKEMON_SELECT_MAX; i++)
    CLACT_Delete(wk->check_poke[i]);
    
  // �|�P�����X�e�[�^�X�\���a�f�𕜊�
  GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

  /* ���b�Z�[�W�E�B���h�E������ */
  DeleteWindow(&wk->CheckWin);
  // ���̑��A�C�R���𕜊�������
  CLACT_SetDrawFlag(wk->cancel[0], 1);
  CLACT_SetDrawFlag(wk->arrowl[0], 1);
  CLACT_SetDrawFlag(wk->arrowr[0], 1);
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    wk->mark[i].pokeno = POKEMON_NOSELECT;
    wk->mark[i].boxno = BOX_NUM;
  }
  wk->selected = 0;
}


//------------------------------------------------------------------
/**
 * @brief	���ׂẴ��\�[�X���J�����ď������I��������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void FinishScreen(AGBCARTRIDGE_WORK *wk)
{
  int i;

  sys_VBlankFuncChange( NULL, NULL );

  // �|�P�����A�C�R��
  for(i = 0; i < POKEMON_ICON_MAX; i++){
    if(wk->icon[i].clact)
      CLACT_Delete(wk->icon[i].clact);
    if(wk->icon[i].item)
      CLACT_Delete(wk->icon[i].item);
  }
  // �I���}�[�N
  for(i = 0; i < POKEMON_SELECT_MAX; i++){
    if(wk->mark[i].icon)
      CLACT_Delete(wk->mark[i].icon);
  }
  // �₶�邵�Ƃ��u��߂�v�Ƃ�
  if(wk->cancel[0])	CLACT_Delete(wk->cancel[0]);
  if(wk->arrowl[0])	CLACT_Delete(wk->arrowl[0]);
  if(wk->arrowr[0])	CLACT_Delete(wk->arrowr[0]);
  // �E�B���h�E���폜
  DeleteWindow(&wk->TitleWin);
  DeleteWindow(&wk->BoxNameWin);
  DeleteWindow(&wk->CheckWin);
  
  //�t�H���g�폜
  FontProc_UnloadFont(FONT_BUTTON);

  // �L�����]���}�l�[�W���[�j��
  CLACT_U_CharManagerDelete(wk->resObjTbl[CLACT_U_CHAR_RES]);
  // �p���b�g�]���}�l�[�W���[�j��
  CLACT_U_PlttManagerDelete(wk->resObjTbl[CLACT_U_PLTT_RES]);
  // �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
  for(i=0;i<CLACT_U_RES_MAX;i++)
    CLACT_U_ResManagerDelete(wk->resMan[i]);

  // �Z���A�N�^�[�Z�b�g�j��
  CLACT_DestSet(wk->clactSet);
  wk->clactSet = NULL;
  //OAM�����_���[�j��
  REND_OAM_Delete();
  // ���\�[�X���
  DeleteCharManager();
  DeletePlttManager();
  // �^�b�`�V�X�e���̊J��
  TOUCH_SW_FreeWork(wk->TouchSubWindowSys);
  
  // �㉺��ʂ����ɖ߂��Ă���
  sys.disp3DSW = DISP_3D_TO_MAIN;
  GF_Disp_DispSelect();

  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_M);
}


//------------------------------------------------------------------
/**
 * @brief	�͂��^�������A�C�R����o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_ReqYesNoIcon(AGBCARTRIDGE_WORK *wk)
{
  // �͂��^�������I��
  TOUCH_SW_PARAM param;
  param.p_bgl		= wk->bgl;
  param.bg_frame	= GF_BGL_FRAME0_M;
  param.char_offs	= 512;
  param.pltt_offs 	= 8;
  param.x		= 25;
  param.y		= 7;
  TOUCH_SW_Init(wk->TouchSubWindowSys, &param );
}


//------------------------------------------------------------------
/**
 * @brief	�J�[�g���b�W�̃��[�U�[�m�F
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridge_CreateCheckUser(AGBCARTRIDGE_WORK *wk)
{
  REGWIN rwin;
  WORDSET *word;
  STRBUF *strbuf;
  STRCODE dsname[AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE];

  AGBSTR_to_DSSTR(agbpoke_GetTrainerName(), dsname, AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE, agbpoke_getPokemonLanguage());
  word = WORDSET_Create(HEAPID_AGBCARTRIDGE);
  strbuf = STRBUF_Create(AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE, HEAPID_AGBCARTRIDGE);
  STRBUF_SetStringCode(strbuf, dsname);
  WORDSET_RegisterWord(word, 1, strbuf, PM_MALE, TRUE, PM_LANG);

  // [�g���[�i�[��]�́@[�J�Z�b�g��] ����\n�|�P�������@��Ă��܂����H
  InitUpMessageWindow(wk);
  wk->cwin.msgid = UsrCheckMsgTable[wk->cartridge_type];
  wk->cwin.word = word;
  CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
  STRBUF_Delete(strbuf);
  WORDSET_Delete(word);
  AgbCartridge_ReqYesNoIcon(wk);
}

static void VBlankFunc( void * work )
{
  AGBCARTRIDGE_WORK *wk = (AGBCARTRIDGE_WORK *)work;

  if(wk->DrawFunc){
    wk->DrawFunc();
    wk->DrawFunc = NULL;
  }
  
  // �Z���A�N�^�[Vram�]���}�l�[�W���[���s
  DoVramTransferManager();
  // �����_�����LOAM�}�l�[�W��Vram�]��
  REND_OAMTrans();	
  GF_BGL_VBlankFunc(wk->bgl);
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//------------------------------------------------------------------
/**
 * @brief	�G���[�`�F�b�N�����܂���֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
enum {
  AGBPOKEMON_ERROR_NONE,		// �G���[�Ȃ�
  AGBPOKEMON_ERROR_LOAD_FAILD,		// �Z�[�u�f�[�^�̃��[�h�Ɏ��s����
  AGBPOKEMON_ERROR_FEW_24HOUR,		// �܂��Q�S���ԗ����Ă��Ȃ�
  AGBPOKEMON_ERROR_MACADDRESS,		// DS�{�̂�MacAddress���ς���Ă�
  AGBPOKEMON_ERROR_MOVE_TIME,		// DS�{�̂̎��v���������ꂽ
  AGBPOKEMON_ERROR_PCBOX_NOPOKE,	// �{�b�N�X�ɂU�C���݂��Ȃ�
  AGBPOKEMON_ERROR_POKEPARK_FULL,	// �|�P�p�[�N�ɑ��݂��Ă���
  AGBPOKEMON_ERROR_IMAKARA_24HOUR,	// ������Q�S���ԘA��Ă���Ȃ�
  AGBPOKEMON_ERROR_MAX
};

#define AGBPOKEMON_24HOUR		(60*60*24)	// 60�b�~60���~24����

static int AgbCartridge_CheckAgbError(AGBCARTRIDGE_WORK *wk)
{
  int time;
  u32 AgbTrainerID;
  POKEPARK_DATA *ppark;

#if 0
  return AGBPOKEMON_ERROR_MOVE_TIME;		// DS�{�̂̎��v���������ꂽ
#endif


#if 0//def DEBUG_ONLY_FOR_mituhara
  return AGBPOKEMON_ERROR_NONE;
#endif
  
  ppark = SaveData_GetPokeParkData(wk->sv);
  // �V�K�Z�[�u�Ȃ�΂������̃G���[�`�F�b�N�͂�����΂�
  if(POKEPARKDATA_isNewSave(ppark) == FALSE){

    // MAC�A�h���X�`�F�b�N
    if(POKEPARKDATA_CheckMacAddress(ppark) == FALSE)
      return AGBPOKEMON_ERROR_MACADDRESS;	// MAC�A�h���X�s��v

    // ���v�s���ύX�`�F�b�N
    if(POKEPARKDATA_CheckRTCOffset(ppark) == FALSE)
      return AGBPOKEMON_ERROR_MOVE_TIME;	// ���v���炵��

    // AGB�J�Z�b�g�̃g���[�i�[ID�𓾂�
    AgbTrainerID = agbpoke_GetTrainerID();
    time = POKEPARKDATA_CheckHistoryID(ppark, AgbTrainerID);
    // �܂��P�x���A��Ă��Ă��Ȃ���ΘA��Ă�����
    if(time == 0)	time = AGBPOKEMON_24HOUR * 2;
#ifdef DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("�O��A��Ă��Ă���̌o�ߎ���: %2d�� %2d�b\n", time / 60, time % 60);
    //    time = AGBPOKEMON_24HOUR * 2;
#endif
    if(time < AGBPOKEMON_24HOUR)
      return AGBPOKEMON_ERROR_FEW_24HOUR;	// �܂�24���Ԍo���ĂȂ�

  }
  // �{�b�N�X�̃|�P�������`�F�b�N
  {
    PokemonPasoParam *ppp;
    int i, box, max = 0;
    for(box = 0; box < BOX_NUM; box++){
      for(i = 0; i < POKEMON_ICON_MAX; i++){
	ppp = &wk->boxdata->PPPBox[box][i];
	if(AgbPokePasoParaGet(ppp, ID_AGB_poke_exist_flag, NULL))
	  max++;
      }
    }
#ifdef DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("PCBOX�ɂ���|�P�����̐�: %d\n", max);
#endif    
    if(max < POKEPARK_MONS_MAX)	// include/savedata/pokepark_data.h
      return AGBPOKEMON_ERROR_PCBOX_NOPOKE; // �{�b�N�X�ɂU�C���Ȃ�����
  }
  
  // �|�P�p�[�N�p�{�b�N�X���󂢂Ă��邩���ׂ�
  if(POKEPARKDATA_CountPokemon(ppark))
    return AGBPOKEMON_ERROR_POKEPARK_FULL;
  return AGBPOKEMON_ERROR_NONE;
}


//------------------------------------------------------------------
/**
 * @brief	���A�s�\�ȃG���[��\������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DisplayError(AGBCARTRIDGE_WORK *wk, int errno)
{
  if(wk->agberror){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = ErrorMsgTable[errno];
    wk->cwin.msgwait = 1;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->agberror = 0;
  } else {
    if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
      MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
      return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�I�����K�v�ȃG���[�\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DispYesNoError(AGBCARTRIDGE_WORK *wk, int errno)
{
  if(wk->agberror){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = ErrorMsgTable[errno];
    wk->cwin.msgwait = 1;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->agberror = 0;
  } else {
    if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
       AgbCartridge_ReqYesNoIcon(wk);
       MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
       return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�X�N���[�����K�v�ȃ��b�Z�[�W�̕\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL AgbCartridge_DisplayMessage(AGBCARTRIDGE_WORK *wk, int frame)
{
  if(wk->msg_flag != -1){
    InitUpMessageWindow(wk);
    MsgPrintTouchPanelFlagSet(MSG_TP_ON);
    wk->cwin.msgid = wk->msg_flag;
    wk->cwin.msgwait = frame;
    CreateMsgWindow(wk, &wk->cwin, MSG_FLAG_FRAME|MSG_FLAG_TALKWIN);
    wk->msg_flag = -1;
    Snd_SePlay(SEQ_SE_DP_SELECT);
  } else {
    if(frame){
      if(GF_MSG_PrintEndCheck(wk->cwin.m_id) == 0){
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
	return TRUE;
      }
    } else {
      if(sys.tp_trg || sys.trg){
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
	Snd_SePlay(SEQ_SE_DP_SELECT);
	return TRUE;
      }
    }
  }
  return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�Z�b�g��������Ă���F������
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_Init(PROC * proc, int * seq)
{
  AGBCARTRIDGE_WORK *wk;

  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_AGBCARTRIDGE, 0x28000);
  sys_PrintHeapFreeSize(HEAPID_AGBCARTRIDGE);
  wk = PROC_AllocWork(proc, sizeof(AGBCARTRIDGE_WORK), HEAPID_AGBCARTRIDGE);
  /* �������s�ǂ��|���̂Ń��[�N�̓[���N���A */
  memset(wk, 0, sizeof(AGBCARTRIDGE_WORK));

  /* �e��ϐ��̏����� */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_AGBCARTRIDGE);

  /* ����ʃE�C���h�E�V�X�e�������� */
  wk->TouchSubWindowSys = TOUCH_SW_AllocWork(HEAPID_AGBCARTRIDGE);

  /* ��ʂ̏����ݒ� */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* �ϐ������� */
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->cfg = SaveData_GetConfig(wk->sv);
  wk->win_type = CONFIG_GetWindowType(wk->cfg);

  /* �T�E���h�f�[�^���[�h */
  Snd_DataSetByScene( SND_SCENE_AGB, SEQ_PRESENT, 1 );

  /* �����Z�[�u�p��Tick������ */
  if(OS_IsTickAvailable() == FALSE)
    OS_InitTick();
  
  /* AGB�J�[�g���b�W�̔������oON */
  MysteryLib_SetAgbCartridgeIntr2();

  _PokeBufPtr = wk->pokebuf;
  
  return PROC_RES_FINISH;
}



//--------------------------------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�Z�b�g��������Ă���F���C��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_Main(PROC * proc, int * seq)
{
  int selno, seltype, ret;
  AGBCARTRIDGE_WORK *wk = PROC_GetWork(proc);

  // AGB�J�[�g���b�W���������ꍇ�͏�����~
  CTRDG_IsExisting();
  if(CTRDG_IsPulledOut() == TRUE)
    CTRDG_TerminateForPulledOut();
  
  wk->jiffy++;
  
  switch(*seq){

  case AGBCARTRIDGE_SEQ_INIT_CARTRIDGE:
    // �J�[�g���b�W�̏�����
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("�|�P�����J�Z�b�g�̃Z�[�u�f�[�^�̑傫�� = %d\n", AGBPOKE_BUFFERSIZE);
#endif
    agbpoke_preinit();
    wk->cartridge_status = agbpoke_init(wk->buffer);
    if(wk->cartridge_status == AGBPOKE_ERROR_OK){
      wk->load_status = agbpoke_LoadDATA();
      if(wk->load_status == AGBPOKE_ERROR_OK){
	wk->boxdata = agbpoke_getPCdata();
	wk->CurrentBox = wk->boxdata->CurrentBoxNo;
      } else {
	// �Ⴆ�΃{�b�N�X�ɂP�C�����Ȃ��Ƃ��A
	// �������������Ă��Ȃ��Ƃ�
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("AGB�J�Z�b�g�f�[�^�̃��[�h�Ɏ��s���܂���: %d\n", wk->load_status);
#endif
	wk->agberror = AGBPOKEMON_ERROR_LOAD_FAILD;
      }
    } else {
      // AGB�J�Z�b�g�������ꂽ�ꍇ�ɂ́A����������������~���邽�߁A
      // �����܂ŏ��������Ȃ��͂��ł��B
    }
    // �J�Z�b�g�̃^�C�v��ݒ�
    AgbCartridge_SetCartridgeType(wk);
    SetSeq(AGBCARTRIDGE_SEQ_PREINIT_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_PREINIT_SCREEN:
    // ��ʍ쐬
    CreateAgbCartridgeScreen(wk);

    CharPlttManagerInit();
    InitCellActor(wk);
    SetCellActor(wk);
    SetMiscIcon(wk);
    sys_VBlankFuncChange( VBlankFunc, wk );
    GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_OFF );	//���C�����OBJ��OFF

    if(wk->agberror == AGBPOKEMON_ERROR_LOAD_FAILD)
      RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_ERROR_SCREEN, seq);
    else
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_USER);
    break;

  case AGBCARTRIDGE_SEQ_CHECK_USER:
    // �J�[�g���b�W�̃��[�U�[�m�F
    AgbCartridge_CreateCheckUser(wk);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_CHECK_USER_YESNO, seq);
    break;

  case AGBCARTRIDGE_SEQ_CHECK_USER_YESNO:
    // �m�F��ʏ���
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// �͂�
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      wk->msg_flag = CHECK_FINAL_MSG;
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_FINAL);
      break;
    case TOUCH_SW_RET_NO:		// ������
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_CHECK_FINAL:
    // �ŏI�m�F
    // "��Ă����@�|�P�����́@�f�a�`�ɂ�\n���ǂ����Ƃ��@�ł��܂���
    // �|�P�������@�_�C�������h��\n��Ă��܂����H"
    if(AgbCartridge_DisplayMessage(wk, 1)){
      // �͂��^�������I���̓o�^
      AgbCartridge_ReqYesNoIcon(wk);
      SetSeq(AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO);
    }
    break;

  case AGBCARTRIDGE_SEQ_CHECK_FINAL_YESNO:
    // �m�F��ʏ���
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// �͂�
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      // �G���[�`�F�b�N���܂���̂���
      wk->agberror = AgbCartridge_CheckAgbError(wk);
      if(wk->agberror){
	if(wk->agberror == AGBPOKEMON_ERROR_MACADDRESS || wk->agberror == AGBPOKEMON_ERROR_MOVE_TIME)
	  SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN);
	else
	  SetSeq(AGBCARTRIDGE_SEQ_ERROR_SCREEN);
      } else {
	wk->msg_flag = msg_pokepark_08;
	SetSeq(AGBCARTRIDGE_SEQ_DISP_MESSAGE);
      //	RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_INIT_SCREEN, seq);
      }
      break;
    case TOUCH_SW_RET_NO:		// ������
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_DISP_MESSAGE:
    // "��Ă����@�|�P������\n�U�Ђ��@�����Ł@��������"
    if(AgbCartridge_DisplayMessage(wk, 1)){
      // �͂��^�������I���̓o�^
      //      AgbCartridge_ReqYesNoIcon(wk);
      SetSeq(AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO);
    }
    break;

  case AGBCARTRIDGE_SEQ_DISP_MESSAGE_YESNO:
    // �m�F�̃^�b�v�܂��̓L�[���͂�҂�
    if(sys.tp_trg || sys.trg)
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_INIT_SCREEN, seq);
    break;
    
  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN:
    // �I�����K�v�ȃG���[�\��[������] �� AGBCARTRIDGE_SEQ_ERROR_SCREEN
    // MAC�A�h���X�����Ԃ����炵���ꍇ�̃Z�[�u����
    if(AgbCartridge_DispYesNoError(wk, wk->agberror))
      SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2);
    break;

  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN2:
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// �͂�
      TOUCH_SW_Reset( wk->TouchSubWindowSys );

      wk->cwin.msgwait = 0;
      wk->cwin.msgid = msg_pokepark_42;	// �ւ񂱂����イ�@�ł�\n�ł񂰂���@����Ȃ��Ł@��������
      CreateMsgWindow(wk, &wk->cwin, 0);


      wk->save_work.time_icon = TimeWaitIconAdd(&wk->CheckWin, AGBPOKEMON_TFRAMECHR);
      SetSeq(AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3);
      break;
    case TOUCH_SW_RET_NO:		// ������
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      break;
    }
    break;

  case AGBCARTRIDGE_SEQ_ERROR_YESNO_SCREEN3:
    // �����ł̓Z�[�u���I���܂Ŗ߂��Ă��Ȃ�
    SaveDsCard(wk);
    TimeWaitIconDel(wk->save_work.time_icon);
    wk->agberror = AGBPOKEMON_ERROR_IMAKARA_24HOUR;
    SetSeq(AGBCARTRIDGE_SEQ_ERROR_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_ERROR_SCREEN:
    // �G���[�\�����^�C�g���֖߂�
    if(AgbCartridge_DisplayError(wk, wk->agberror))
      SetSeq(AGBCARTRIDGE_SEQ_SAVE_END);
    break;

    
  case AGBCARTRIDGE_SEQ_INIT_SCREEN:
    // ��ʍ쐬�@���̂Q
    DeleteWindow(&wk->CheckWin);
    CreateAgbCartridgeScreen2(wk);
    SetPokemonIcon(wk);
    RedrawPokemonBox(wk);

    // VBlank�֐��Z�b�g
    sys_VBlankFuncChange( VBlankFunc, wk );
    GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ��ON
    // �uLv�v�Ɓu�������́v�����\��������
    DrawStatusWindow(wk, NULL);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_MAIN, seq);

    sys_PrintHeapFreeSize(HEAPID_AGBCARTRIDGE);
    
    break;

  case AGBCARTRIDGE_SEQ_MAIN:
    // �I�����C��
    selno = GF_TP_RectHitTrg((const RECT_HIT_TBL *)wk->iconrect);
    if(selno != RECT_HIT_NONE){
      if(selno < POKEMON_ICON_MAX){
	seltype = SelectPokemon(wk, selno);
	if(seltype == SELECT_POKEMON_SELECT){
	  // �|�P������I�����܂���
	  DrawStatusWindow(wk, &(wk->boxdata->PPPBox[wk->CurrentBox][selno]));
	  // �I�������|�P������MAX�ɒB���Ă�����m�F��ʂ�
	  if(wk->selected == POKEMON_SELECT_MAX){
	    wk->wait_seq = 45;	// 45 * 2��90frame�̑҂�����
	    SetSeq(AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN);
	  }
	} else if(seltype == SELECT_POKEMON_CANCEL){
	  // �I�����������܂���
	  DrawStatusWindow(wk, NULL);		// ���E�B���h�E�́u���v������
	} else if(seltype == SELECT_POKEMON_EGG){
	  // �I�������|�P���������܂��ł���
	  wk->msg_flag = msg_pokepark_10;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_WAZA){
	  // �I�������|�P�������Ђł�킴�������Ă���
	  wk->msg_flag = msg_pokepark_11;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_ITEM){
	  // �I�������|�P�����������Ă����Ȃ��A�C�e���������Ă���
	  wk->msg_flag = msg_pokepark_40;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	} else if(seltype == SELECT_POKEMON_FUSEI){
	  // �s���Ȕԍ��̃|�P����������
	  wk->msg_flag = msg_pokepark_40;
	  SetSeq(AGBCARTRIDGE_SEQ_SELECT_WARNING);
	}
      } else {
	switch(selno){
	case ICON_ARROWL:
	  if(wk->CurrentBox == 0)
	    wk->CurrentBox = BOX_NUM - 1;
	  else
	    wk->CurrentBox--;
	  RedrawPokemonBox(wk);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	case ICON_ARROWR:
	  if(++wk->CurrentBox == BOX_NUM)
	    wk->CurrentBox = 0;
	  RedrawPokemonBox(wk);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	case ICON_CANCEL:
	  RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
	  Snd_SePlay(SEQ_SE_DP_SELECT);
	  break;
	}
      }
    }
    break;

  case AGBCARTRIDGE_SEQ_SELECT_WARNING:
    // �x���\��
    if(AgbCartridge_DisplayMessage(wk, 0)){
      DeleteWindow(&wk->CheckWin);
      SetSeq(AGBCARTRIDGE_SEQ_MAIN);
    }
    break;


  case AGBCARTRIDGE_SEQ_WAIT_CHECK_SCREEN:
    // �m�F��ʂ֍s���O�̈�u�̊Ԃ����
    if(--wk->wait_seq == 0){
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN, seq);
    }
    break;
    
  case AGBCARTRIDGE_SEQ_CREATE_CHECK_SCREEN:
    // �m�F��ʂ̍쐬
    CreateCheckScreen(wk);
    RequestFade(wk, WIPE_TYPE_FADEIN, AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1, seq);
    // �͂��^�������I��
    AgbCartridge_ReqYesNoIcon(wk);
    break;

  case AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH1:
    // �u����񂾂U�Ђ��́@�ۂ�������@��Ă����܂��v�m�F��ʏ���
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// �͂�
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      SetSeq(AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH);
      break;
    case TOUCH_SW_RET_NO:		// ������
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_RETURN_SELECT, seq);
      break;
    }
    break;
    
  case AGBCARTRIDGE_SEQ_CREATE_CHECK_TOUCH:
    // �m�F�^�b�v�҂�
    //    if(sys.tp_trg)
    {
      REGWIN rwin;
      // ���b�Z�[�W�E�B���h�E�̓��e��ύX����
      wk->cwin.msgid = msg_pokepark_13;	// ���r�[�@�Ɂ@���ǂ����Ƃ�\n�ł��܂��񂪁@��낵���@�ł����H
      CreateMsgWindow(wk, &wk->cwin, 0);
      // �͂��^�������I��
      AgbCartridge_ReqYesNoIcon(wk);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      SetSeq(AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN);
    }
    break;

  case AGBCARTRIDGE_SEQ_CREATE_CHECK_MAIN:
    // �m�F��ʏ���
    selno = TOUCH_SW_Main( wk->TouchSubWindowSys );
    switch(selno){
    case TOUCH_SW_RET_YES:		// �͂�
      // �~�~�@�Ɓ@������\n�|�P�������|�[�g���@�����Ă��܂�
      wk->cwin.msgid = SaveMsgTable[wk->cartridge_type];
      CreateMsgWindow(wk, &wk->cwin, 0);
      //      wk->wait_seq = 60;
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      wk->save_work.save_seq = SAVE_SEQ_INIT;
      wk->save_work.time_icon = TimeWaitIconAdd(&wk->CheckWin, AGBPOKEMON_TFRAMECHR);

      SetSeq(AGBCARTRIDGE_SEQ_SAVE);
      sys_SoftResetNG(SOFTRESET_TYPE_SAVELOAD);
      break;
    case TOUCH_SW_RET_NO:		// ������
      TOUCH_SW_Reset( wk->TouchSubWindowSys );
      RequestFade(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_RETURN_SELECT, seq);
      break;
    }
    break;
    
  case AGBCARTRIDGE_SEQ_RETURN_SELECT:
    // �I����ʂ𕜊�������
    ReviveSelectScreen(wk);
    SetSeq(AGBCARTRIDGE_SEQ_INIT_SCREEN);
    break;

  case AGBCARTRIDGE_SEQ_SAVE:
    // �񓯊��Z�[�u����
    ret = SaveSequence(wk);

    if(ret != SAVE_STATUS_WRITING){

      TimeWaitIconDel(wk->save_work.time_icon);

      Snd_SePlay(SEQ_SE_DP_SAVE);

#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("�Z�[�u����: %d\n", ret);
#endif
      if(ret == SAVE_STATUS_WRITE_SUCCESS)
	wk->cwin.msgid = SAVE_SUCCESS_MSG;	// �U�Ђ����@�Ԃ��@[����]�@��\n��Ă����@���Ƃ��@�ł��܂���
      else
	wk->cwin.msgid = msg_pokepark_38;	// �|�P�������|�[�g���@�����̂Ɂ@�����ς��@���܂���

      CreateMsgWindow(wk, &wk->cwin, 0);
      SetSeq(AGBCARTRIDGE_SEQ_SAVE_END);
      sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
    }
    break;

  case AGBCARTRIDGE_SEQ_SAVE_END:
    // �m�F�^�b�v�҂�
    if(sys.tp_trg){
      RequestFadeW(wk, WIPE_TYPE_FADEOUT, AGBCARTRIDGE_SEQ_FINISH, seq);
      Snd_SePlay(SEQ_SE_DP_SELECT);
    }
    break;
    
    
  case AGBCARTRIDGE_SEQ_WAIT_FADE:
    // �t�F�[�h���I������܂ő҂��Ď��̃V�[�P���X��
    if(WIPE_SYS_EndCheck()){
      *seq = wk->next_seq;
    }
    break;

  case AGBCARTRIDGE_SEQ_FINISH:
    FinishScreen(wk);
    return PROC_RES_FINISH;
    break;
  }

  // �A�C�R����\�����邽�߂ɕK�v�ȋ쓮����
  if(wk->clactSet!=NULL)
    CLACT_Draw( wk->clactSet );

  return PROC_RES_CONTINUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�Z�b�g��������Ă���F�I��
 * @param	proc	�v���Z�X�ւ̃|�C���^
 * @param	seq		�V�[�P���X�p���[�N�ւ̃|�C���^
 * @return	PROC_RES_CONTINUE	����p����
 * @return	PROC_RES_FINISH		����I��
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT AgbCartridgeProc_End(PROC * proc, int * seq)
{
  FS_EXTERN_OVERLAY( title );
  AGBCARTRIDGE_WORK *wk = PROC_GetWork(proc);

  sys_FreeMemoryEz(wk->bgl);
  Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_AGBCARTRIDGE);
  /* AGB�J�[�g���b�W�̔������oOFF */
  MysteryLib_SetAgbCartridgeIntr(FALSE);

  return PROC_RES_FINISH;
}

const PROC_DATA AgbCartridgeProcData = {
  AgbCartridgeProc_Init,
  AgbCartridgeProc_Main,
  AgbCartridgeProc_End,
  NO_OVERLAY_ID,
};

/*  */
