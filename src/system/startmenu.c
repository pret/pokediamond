//============================================================================================
/**
 * @file	startmenu.c	
 * @bfief	�^�C�g�����j���[
 * @author	Satoshi Mitsuhara
 * @date	06.04.11
 *
 * $Id: startmenu.c,v 1.71 2006/08/10 08:57:27 mitsuhara Exp $
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/main.h"
#include "system/wipe.h"
#include "system/wordset.h"
#include "system/msgdata_util.h"
#include "system/arc_util.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/snd_play.h"
#include "system/render_oam.h"

#include "gflib/bg_system.h"
#include "gflib/rebooter.h"

#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/playtime.h"
#include "savedata/fushigi_data.h"
#include "savedata/system_data.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_startmenu.h"
#include "msgdata/msg_bconfind.h"

#include "communication/comm_state.h"

#include "../fushigi/agbpoke_access.h"
#include "../fushigi/mysterylib.h"
#include "../fushigi/agbdownload.h"
#include "../fushigi/mystery.naix"

#include "msgdata/msg_wifi_system.h"
#include "wifi/dwc_rap.h"

/*
 * ���K���\������郁�j���[
 *
 *	�Â�����͂��߂�
 *	�������傩��͂��߂�
 *	WiFi�����Ă�
 *
 * ���J�[�g���b�W���h�����Ă���ƕ\������郁�j���[
 *
 *	�Ȃ�Ƃ��Ƃ����Ă���(���r�[/�T�t�@�C�A/...)
 *
 * �������ɂ���ĕ\������郁�j���[
 *
 *	�|�P���������W���[�Ƃ�����
 *	Wii�Ƃ̂�����
 *
 * �����j���[����I��������ɐڑ��������
 *
 *	�_�C���N�g������
 *	WiFi������
 *	�r�[�R��������
 *
 */
/*
  �^�C�g�����j���[�̍ŏ��̎��_�ł��肢��������������܂��B
  WIFI�̏������֐��Ȃ̂ł����A���̊֐��̖߂�l��
  DWC_INIT_RESULT_DESTROY_OTHER_SETTING�@�̏ꍇ�ɁA
  ���b�Z�[�W���o���Ă������������̂ł��B
  ���Ȃ݂ɂ��̃G���[��DS�{�̂̒ʐM��񂪉�ꂽ�ꍇ�ɏo�܂��B

  #include "msgdata/msg_wifi_system.h"
  #include "wifi/dwc_rap.h"

  ret = mydwc_init(HEAPID_BASE_APP);
  if(ret == DWC_INIT_RESULT_DESTROY_OTHER_SETTING){
    message (  dwc_message_0001 );
  }

  PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL �Ŗ{���̃^�C�g���ֈړ�

  ��������������ɂȂ�܂��B
*/

//
// BG0 - ���j���[�\�����
// BG1 - �r�[�R�����E�����ۂɕ\������郁�j���[(�ꎞ�I�\���̂�)
// BG2 - �ʐM�A�C�R��(BG0�ƈꏏ�ɃX�N���[��)
//

#define WIICLIENT_FILE		"data/eoo.dat"

#define STARTMENU_FCHR1		1			// �ʏ�t���[��
#define STARTMENU_FCOL1		2
#define STARTMENU_FCHR2		(STARTMENU_FCHR1 + 9)	// �I�����t���[��
#define STARTMENU_FCOL2		3


#define STARTMENU_WCHR		(STARTMENU_FCHR2 + 9)
#define STARTMENU_WCOL_SELECT	0
#define STARTMENU_WCOL_NORMAL	1

#define STARTMENU_WICON_PAL	4

#define STARTMENU_NOSELECT	-1

#define STARTMENU_FIRSTGAME_SELECT	0x80

#define RGB(r, g, b)	(((b)&31)<<10|((g)&31)<<5|((r)&31))

enum {
  // ���C���V�[�P���X
  STARTMENU_SEQ_INIT,
  STARTMENU_SEQ_CHECK_SYSTEM,		// �e��V�X�e���`�F�b�N
  STARTMENU_SEQ_DISP_ERROR,
  STARTMENU_SEQ_HARDINIT,
  STARTMENU_SEQ_CREATE_SCREEN,		// �X�N���[���쐬(��{�`)
  STARTMENU_SEQ_MAIN,
  STARTMENU_SEQ_SELECT_FIRSTGAME,

  STARTMENU_SEQ_SELECT_MENU,		// ���j���[���I�����ꂽ��̏���

  STARTMENU_SEQ_FADE_WAIT,
  STARTMENU_SEQ_FINISH,			// ��������������

  // �r�[�R���擾�V�[�P���X
  STARTMENU_BEACON_SEQ_INIT,		// ������
  STARTMENU_BEACON_SEQ_INIT2,		// ������
  STARTMENU_BEACON_SEQ_WAIT,		// ���C���������ǂ��Ƃ����܂ő҂�
  STARTMENU_BEACON_SEQ_TIMER,		// ���ۂ̃r�[�R�����W����
  STARTMENU_BEACON_SEQ_CANCEL,		// �����L�����Z�����[�h

  // �r�[�R���擾���̃��b�Z�[�W�\��
  BEACON_MSGSEQ_NOP,			// �������Ȃ�
  BEACON_MSGSEQ_INIT,			// ������
  BEACON_MSGSEQ_INIT_DISP,		// �X�N���[��������
  BEACON_MSGSEQ_INIT_MAIN,		// �L�[���͑҂�
  BEACON_MSGSEQ_INIT_FINISH,		// �I��
  BEACON_MSGSEQ_FADE_WAIT,		// �t�F�[�h�҂�
  
  STARTMENU_SEQ_MAX
};


typedef struct _STARTMENU_DATA {
  int mark;
  int height;
  int msgid;
  // �\�����ɌĂяo�����t�@���N�V����
  BOOL (*func)(void */* STARTMENU_WORK */, int, MYSTERY_WIN *, int);
} STARTMENU_DATA;


static BOOL StartMenuAgbPokemon(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckMystery(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckRanger(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckWii(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuSetWifi(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuContinue(void *, int, MYSTERY_WIN *, int);

enum {
  SEL_CANCEL = 0,
  SEL_CONTINUE,
  SEL_FIRSTGAME,
  SEL_MYSTERY,
  SEL_RANGER,
  SEL_AGBPOKEMON,
  SEL_WII,
  SEL_WIFI,
  SEL_MAX
};

enum {
  STARTMENU_DWC_ERROR = 0,		// DS�{�̂̒ʐM��񂪉��Ă���
  STARTMENU_ERROR_MAX
};

typedef struct {
  int sx, sy, width, height;
  u32 arc, msgid;
  void (*func)(void */*STARTMENU_WORK* */);
} ERRORTABLE;

// �Q�Z�b�g�̃G���[�\�����b�Z�[�W
static ERRORTABLE ErrorMsgTable[] = {
  { 5, 5, 22, 14, NARC_msg_wifi_system_dat, dwc_message_0001, NULL/*DispErrorDwc*/ },
};


STARTMENU_DATA StartMenuWinTable[] = {
  // �Â����� �͂��߂�
  { SEL_CONTINUE,   10, mes_startmenu_01,	StartMenuContinue },
  // �������傩��@�͂��߂�
  { SEL_FIRSTGAME,   2, mes_startmenu_02,	NULL },
  // �ӂ����ȁ@���������
  { SEL_MYSTERY,     2, mes_startmenu_03,	StartMenuCheckMystery },
  // �|�P���������W���[�Ƃ́@������
  { SEL_RANGER,      2, mes_startmenu_04, 	StartMenuCheckRanger },
  // �~�~�~����@��Ă���
  { SEL_AGBPOKEMON,  2, NULL, 			StartMenuAgbPokemon },
  // Wii�Ɓ@������
  { SEL_WII,         2, mes_startmenu_11, 	StartMenuCheckWii },
  // Wi-Fi�����Ă�
  { SEL_WIFI,        2, mes_startmenu_12, 	StartMenuSetWifi },
};


static u32 StartMenuContinueTable[] = {
  mes_startmenu_01,			// �Â�����@�͂��߂�
  mes_startmenu_13,			// ���ザ�񂱂�
  mes_startmenu_14,			// �v���C������
  mes_startmenu_16,			// �����Ă���o�b�W
  mes_startmenu_15,			// �|�P����������
};

// �r�[�R�����E�����Ƃ��̃��b�Z�[�W�f�[�^
typedef struct {
  int sx, sy;
  int width, height;
  int msg;
} BEACON_MSG_TABLE;
BEACON_MSG_TABLE BeaconMsgTable[] = {
  { 4, 2, 24, 20, bcon_002 },		// �ӂ����Ȃ�������̂𔭌��B���j���[�őI��ł�
  { 4, 4, 24, 16, bcon_004 },		// �ӂ����Ȃ�������̂𔭌��B�ł��܂��_��
  { 4, 1, 24, 22, bcon_001 },		// �����W���[�𔭌��B���j���[�őI��ł�
  { 4, 3, 24, 18, bcon_003 },		// �����W���[�𔭌��B�ł��܂��_��
  // �����ꂾ�����j���[�I�������b�Z�[�W
  { 2, 1, 28, 22, bcon_006 },		// �������傩��͂��߂Ă��Z�[�u�ł����H
};



// ���j���[�̍ő吔
#define MENU_WIN_MAX	(sizeof(StartMenuWinTable) / sizeof(STARTMENU_DATA))

// �r�[�R�������W�߂鎞��
#define BEACON_GATHER_TIME	(2*60)

#define SetSeq(w, n)	(w = n)


typedef struct {
  GF_BGL_INI *bgl;
  SAVEDATA *sv;
  ZUKAN_WORK *zw;
  MYSTATUS *mst;
  PLAYTIME *ptime;
  FUSHIGI_DATA *fdata;				// �ӂ����f�[�^��ǂ񂾏ꏊ

  // ���C���V�[�P���X�֌W

  int jiffy;
  int next_seq;
  int chrbase;			       	// �E�B���h�E�̃L�����N�^�x�[�X

  int agbpokemon;     			// �h�����Ă���AGB�J�Z�b�g�̃^�C�v(CASTYPE_xxx)
  int agbpokemoncheck;
  int pokemonranger;			// �|�P���������W���[�𔭌�����
  int wii;				// Wii�̃r�[�R���𔭌�����
  int mystery;				// �ӂ����ȁ@��������̃r�[�R��

  int menu_flag;			// �e��r�[�R�����j���[��\���������H(PARTYGAME_xxx)
  int new_menu_flag;
  
  
  int beacon_status;
  int beacon_disp_status;
  int redrawflag;
  
  int zukangetflag;			// ������������Ă���Ȃ�TRUE
  int badgecount;			// �����Ă���o�b�`�̐�


  int cursor;				// ���݂̃J�[�\���ʒu

  int select;				// �I�����ꂽ����(-1�Ȃ�Ή����I�����Ă��Ȃ�)
  
  GF_BGL_BMPWIN mwin[MENU_WIN_MAX];
  int menuflag[MENU_WIN_MAX];		// �\������Ă�����TRUE(default = FALSE)
  int iconflag[MENU_WIN_MAX];		// ���C�����X�A�C�R�������鎞��TRUE

  fx32 scrolly;				// ���݂̃X�N���[���l
  fx32 target;				// �ړI���W

  // �r�[�R���擾�֌W
  int beacon_seq;
  int beacon_wait;
  int beacon_msg_seq;			// �r�[�R���擾���ɕ\�����郁�b�Z�[�W�V�[�P���X
  int beacon_msg_wait;
  int beacon_key_wait;
  int beacon_result;
  GF_BGL_BMPWIN beacon_win;
  
  int pass_start_menu;			// TRUE�Ȃ�΃X�^�[�g���j���[��\�������Ȃ�
  int req_popup;

  // �G���[���
  BOOL errorflag[STARTMENU_ERROR_MAX];
  GF_BGL_BMPWIN ewin;
  
  // �J�[�\���A�N�^�[
  CLACT_WORK_PTR clcursor[2];		// 0 = ���@1 = ��

  int anim_index;
} STARTMENU_WORK;






//============================================================================================
//	�O���֐���`
//============================================================================================
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern int CommPlayerNowFlagDataArraySize(void);
extern int MyStatus_GetWorkSize(void);
extern void CreateIndexData(int heapid);

//============================================================================================
//	�萔��`
//============================================================================================


//------------------------------------------------------------------
/**
 * @brief	�V�X�e���G���[�`�F�b�N
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int StartMenuCheckSystem(STARTMENU_WORK *wk)
{
  int max, ret;
  
  max = 0;
#if 0  //main�ŌĂт܂��̂ŁA�����͏����܂�
  // DS�{�̂̒ʐM��񂪉��Ă��Ȃ����`�F�b�N����
  ret = mydwc_init(HEAPID_BASE_APP);
#if 0	// �f�o�b�O�p�ł���
  ret = DWC_INIT_RESULT_DESTROY_OTHER_SETTING;
#endif
  if(ret == DWC_INIT_RESULT_DESTROY_OTHER_SETTING){
    wk->errorflag[STARTMENU_DWC_ERROR] = TRUE;
    max++;
  }
#endif
  return max;
}


//------------------------------------------------------------------
/**
 * @brief	�G���[����\������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuDisplayError(STARTMENU_WORK *wk)
{
  int i;
  ERRORTABLE *et;
  MYSTERY_WIN mw;

  // �G���[�\���E�B���h�E������������Ă��邩�ǂ����Ŕ��f���s��������
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == FALSE){
    for(i = 0; i < STARTMENU_ERROR_MAX; i++){
      if(wk->errorflag[i] == TRUE){
	wk->errorflag[i] = FALSE;
	et = &ErrorMsgTable[i];
	//�����ŃG���[�\�����s��
	MysteryLib_WinInit1(&mw, &wk->ewin, STARTMENU_WCOL_SELECT, et->arc, STARTMENU_FCHR1, STARTMENU_FCOL1);
	MysteryLib_WinInit2(&mw, et->width, et->height, /*et->msgid,*/ STARTMENU_WCHR);
	MysteryLib_CreateWin(wk->bgl, &mw, et->sx, et->sy, et->msgid);
	return TRUE;
      }
    }
  } else {
    // �G���[�E�B���h�E�̕\����
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      BmpMenuWinClear(&wk->ewin, WINDOW_TRANS_ON);
      GF_BGL_BmpWinDel(&wk->ewin);
    }
    return TRUE;
  }



  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�J�Z�b�g���h�����Ă��邩����������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridgeInit(STARTMENU_WORK *wk)
{
  int pmv;
  int flag = agbpoke_init(NULL);

  wk->agbpokemon = FALSE;
  
  // AGB�|�P�������h�����Ă��Ȃ���Ή������Ȃ�
  if(flag != AGBPOKE_ERROR_OK)
    return;

  // �V�X�e���փJ�Z�b�g�^�C�v��ʒm����
  pmv = 0;	// unknown
  switch(agbpoke_getPokemonType()){
  case CASTYPE_RUBY:	pmv = VERSION_RUBY;	break;
  case CASTYPE_SAPPHIRE:pmv = VERSION_SAPPHIRE; break;
  case CASTYPE_GREEN:	pmv = VERSION_GREEN;	break;
  case CASTYPE_RED:	pmv = VERSION_RED;	break;
  case CASTYPE_EMERALD:	pmv = VERSION_EMERALD;	break;
  }
  sys_InitAgbCasetteVer(pmv);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("AGB�J�Z�b�g�o�[�W����: %d\n", pmv);
#endif

#ifndef DEBUG_ONLY_FOR_mituhara
  // DP���̑S�������񃂁[�h��ON�ɂȂ��Ă��Ȃ���΃|�P�����J�Z�b�g�̃��j���[�͕\������Ȃ�
  if(ZukanWork_GetZenkokuZukanFlag(wk->zw) == FALSE)
    return;
#endif

  // DP�Ɠ�������łȂ���΃��j���[�͕\�����Ȃ�
  if(agbpoke_getPokemonLanguage() != CasetteLanguage)
    return;

  // �|�P�����̃^�C�v��ݒ肷��
  wk->agbpokemon = agbpoke_getPokemonType() + 1;

#if 0
  // RTC�t���̃J�[�g���b�W�ŁARTC�̓d�r���؂ꂽ���̂͏��OS_IE_CARTRIDGE���荞�݂�
  // �|�����Ă��܂����߁A�^�C�g����ʂł̓J�[�g���b�W������������Ȃ�
  // �������u�~�~�~����@��Ă���v��I���������ɒ�~����悤�ɂ���
  // 2006.08.10(���}�X�^�[�A�b�v����)

  /* AGB�J�[�g���b�W�̔������oON */
  MysteryLib_SetAgbCartridgeIntr(TRUE);
#else
  /* �X���[�v���̃J�[�g���b�W������L���ɂ��邽�߂̊֐��Ăяo�� */
  MysteryLib_SetAgbCartridgeIntr2();
#endif
}


//------------------------------------------------------------------
/**
 * @brief	�r�[�R���擾�v���Z�X
 * 		��thread�ɂȂ��Ă�킯�ł͂���܂���
 */
//------------------------------------------------------------------
static void StartMenuBeacon_Proc(STARTMENU_WORK *wk)
{
  int flag;

  switch(wk->beacon_seq){
  case STARTMENU_BEACON_SEQ_WAIT:
    // �O������V�[�P���X��ύX����Ȃ����蓮���Ȃ�
    break;

  case STARTMENU_BEACON_SEQ_INIT:
    wk->beacon_seq = STARTMENU_BEACON_SEQ_INIT2;
    break;
  case STARTMENU_BEACON_SEQ_INIT2:
    // * �p�[�e�B�[�Q�[�������̒ʐM�����J�n�i�q�@��Ԃ̂݁j
    CommStateEnterPartyGameScanChild(wk->sv);
    wk->beacon_wait = BEACON_GATHER_TIME;
    wk->beacon_seq = STARTMENU_BEACON_SEQ_TIMER;
    wk->beacon_status = 0;
    // ���łɁu�ӂ����ȁ@��������́v���j���[���\������Ă�����|�b�v�A�b�v�͂��Ȃ�
    if(FUSHIGIDATA_IsFushigiMenu(wk->fdata) == TRUE){
      wk->beacon_status |= PARTYGAME_MYSTERY_BCON;
      wk->beacon_disp_status |= PARTYGAME_MYSTERY_BCON;
    }
    
    break;

  case STARTMENU_BEACON_SEQ_TIMER:
    // ���łɃ|�b�v�A�b�v�\��
    if(wk->beacon_msg_wait)	break;
    // �r�[�R�����W��
    flag = CommStateGetPartyGameBit();

#ifdef DEBUG_ONLY_FOR_mituhara
    // �f�o�b�O��
#if 1
    if(sys.trg & PAD_BUTTON_L)	flag |= PARTYGAME_RANGER_BCON;
    if(sys.trg & PAD_BUTTON_R)	flag |= PARTYGAME_WII_BCON;
    if(sys.trg & PAD_BUTTON_Y)	flag |= PARTYGAME_MYSTERY_BCON;
#else
    flag |= PARTYGAME_RANGER_BCON;
    flag |= PARTYGAME_WII_BCON;
    flag |= PARTYGAME_MYSTERY_BCON;
#endif
#endif
    
    // �O��܂ŕ\�����Ă��Ȃ��r�b�g�̂ݗ��Ă�
    flag = ~wk->beacon_status & flag;
    // �����̃r�[�R�����E���Ă��āA���荞�݃��b�Z�[�W�\�����łȂ��āA���łɗ\��ς݂łȂ��āA�܂��\�����ĂȂ��ꍇ
    if(flag && wk->beacon_msg_seq == BEACON_MSGSEQ_NOP && wk->beacon_msg_wait == 0 && wk->beacon_status != flag){
      wk->redrawflag = TRUE;
      if(flag & PARTYGAME_MYSTERY_BCON)	wk->mystery = TRUE,		flag = PARTYGAME_MYSTERY_BCON;
      if(flag & PARTYGAME_RANGER_BCON)	wk->pokemonranger = TRUE,	flag = PARTYGAME_RANGER_BCON;
      if(flag & PARTYGAME_WII_BCON)	wk->wii = TRUE,			flag = PARTYGAME_WII_BCON;
      // �ӂ����r�[�R���ƃ����W���[�r�[�R���̏ꍇ�͊��荞�݃��b�Z�[�W�\��
      if(flag & (PARTYGAME_MYSTERY_BCON|PARTYGAME_RANGER_BCON))
	wk->req_popup = TRUE;
      // �����ł悤�₭�\���ς݃t���O�̍X�V
      wk->beacon_status |= flag;
    }
    if(--wk->beacon_wait == 0){
      // �p�[�e�B�[�Q�[���T�[�`�̏I������
      CommStateExitPartyGameScan();
      wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    }
    break;

  case STARTMENU_BEACON_SEQ_CANCEL:
    // �����I������(�Q�[�����J�n���ꂽ�Ƃ�)
    CommStateExitPartyGameScan();
    wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	�r�[�R�����擾�����ۂɕ\��������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL BeaconMessage_Proc(STARTMENU_WORK *wk)
{
  MYSTERY_WIN mw;
  BEACON_MSG_TABLE *tbl;
  int msg, status;

  switch(wk->beacon_msg_seq){
  case BEACON_MSGSEQ_NOP:
    if(wk->beacon_msg_wait == 0)	return FALSE;
    // �r�[�R�����E���Ă��琔�t���[����ɔ���
    if(--wk->beacon_msg_wait == 0)
      wk->beacon_msg_seq = BEACON_MSGSEQ_INIT;
    return TRUE;
    break;

  case BEACON_MSGSEQ_INIT:
    // ������
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME1_M, STARTMENU_FCHR1, STARTMENU_FCOL1, 0, HEAPID_STARTMENU);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME1_M);
    *((u16 *)HW_BG_PLTT + 33) = RGB(26, 26, 26);
    wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_DISP;
    break;

  case BEACON_MSGSEQ_INIT_DISP:
    // �X�N���[��������
    MysteryLib_WinInit1(&mw, &wk->beacon_win, STARTMENU_WCOL_SELECT, NARC_msg_bconfind_dat, STARTMENU_FCHR1, STARTMENU_FCOL1);

    // �P�x�\���������j���[�͕\�����Ȃ����߂ɕ\�������t���O���o���Ă���
    status = wk->beacon_status & ~wk->beacon_disp_status;

    if(status & PARTYGAME_MYSTERY_BCON){
      if(wk->menu_flag & PARTYGAME_MYSTERY_BCON)	tbl = &BeaconMsgTable[0];	// �ӂ����ǉ�
      else						tbl = &BeaconMsgTable[1];	// �ǉ��ł��Ȃ�����
    } else if(status & PARTYGAME_RANGER_BCON){
      if(wk->menu_flag & PARTYGAME_RANGER_BCON)		tbl = &BeaconMsgTable[2];	// �����W���[�ǉ�
      else						tbl = &BeaconMsgTable[3];	// �ǉ��ł��Ȃ�����
    } else if(status & STARTMENU_FIRSTGAME_SELECT){
      tbl = &BeaconMsgTable[4];	// �������傩��͂��߂������񂾎��̃��b�Z�[�W
      status = 0;	// ���x�ł��\�����������̂Ŋo�������Ȃ�
    }
    wk->beacon_disp_status |= status;

    MysteryLib_WinInit2(&mw, tbl->width, tbl->height, STARTMENU_WCHR);
    mw.screen = GF_BGL_FRAME1_M;
    MysteryLib_CreateWin(wk->bgl, &mw, tbl->sx, tbl->sy, tbl->msg);

    GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME1_M,
			GF_BGL_BmpWinGet_PosX(mw.win),  GF_BGL_BmpWinGet_PosY(mw.win),
			GF_BGL_BmpWinGet_SizeX(mw.win), GF_BGL_BmpWinGet_SizeY(mw.win),
			STARTMENU_WCOL_SELECT);
    
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON);
    wk->beacon_key_wait = 30;
    wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_MAIN;
    break;

  case BEACON_MSGSEQ_INIT_MAIN:
    // �L�[���͑҂�
    if(wk->beacon_key_wait){
      wk->beacon_key_wait--;
    } else {
      if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
	GF_BGL_BmpWinDel(&wk->beacon_win);
	wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_FINISH;
	wk->beacon_result = sys.trg;
	Snd_SePlay(SEQ_SE_DP_SELECT);
      }
    }
    break;

  case BEACON_MSGSEQ_INIT_FINISH:
    // �I��
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_ON);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
    wk->beacon_msg_seq = BEACON_MSGSEQ_NOP;
    break;
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	���t���[���s������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
// �������򂵂Ȃ�ABS
#define ABS(x)		(((x) ^ ((x)>>31)) - ((x)>>31))
#define SCROLL_MAX_SPEED	(12 * FX32_ONE)
static void StartMenuProc(STARTMENU_WORK *wk)
{
  fx32 speed;

  // �X�N���[������
  if(wk->scrolly != wk->target){
    speed = (wk->target - wk->scrolly) / 4;
    if(ABS(speed) > SCROLL_MAX_SPEED){
      if(speed > 0)	speed =  SCROLL_MAX_SPEED;
      else		speed = -SCROLL_MAX_SPEED;
    }
    wk->scrolly += speed;

    if(ABS(wk->target - wk->scrolly) < FX32_ONE/8)
      wk->scrolly = wk->target;

    GF_BGL_ScrollReq(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCROLL_Y_SET, wk->scrolly / FX32_ONE);
    GF_BGL_ScrollReq(wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, wk->scrolly / FX32_ONE);
  } 
}

//------------------------------------------------------------------
/**
 * @brief	�X�N���[��������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitStartMenuScreen(STARTMENU_WORK *wk)
{
  GF_BGL_DISPVRAM tbl = {
    GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
    GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
    GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
    GX_VRAM_SUB_BGEXTPLTT_NONE,			// �T�u2D�G���W����BG�g���p���b�g
    GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
    GX_VRAM_OBJEXTPLTT_NONE,			// ���C��2D�G���W����OBJ�g���p���b�g
    GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,		// �T�u2D�G���W����OBJ�g���p���b�g
    GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
    GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
  };
  GF_BGL_SYS_HEADER BGsys_data = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };

  GF_Disp_SetBank( &tbl );

  /* BG SYSTEM */
  GF_BGL_InitBG( &BGsys_data );
  /* ���j���[��\������BG */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCRSIZ_256x512, 0xF000, 0x0000); /* MAIN DISP BG0 */
  G2_SetBG0Priority(2);
  GF_BGL_ClearCharSet(GF_BGL_FRAME0_M, 32, 0, HEAPID_STARTMENU);
  /* �r�[�R���擾���ɕ\�����郁�b�Z�[�WBG */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_M, GF_BGL_SCRSIZ_256x256, 0xD800, 0x8000); /* MAIN DISP BG1 */
  G2_SetBG1Priority(1);
  GF_BGL_ClearCharSet(GF_BGL_FRAME1_M, 32, 0, HEAPID_STARTMENU);
  /* �ʐM�A�C�R����\������BG��� */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCRSIZ_256x512, 0xE000, 0x0000); /* MAIN DISP BG2 */
  G2_SetBG2Priority(0);
  GF_BGL_ClearCharSet(GF_BGL_FRAME2_M, 32, 0, HEAPID_STARTMENU);

  MSG_PrintInit();

  /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, STARTMENU_WCOL_NORMAL * 32, HEAPID_STARTMENU);
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, STARTMENU_WCOL_SELECT * 32, HEAPID_STARTMENU);
  *((u16 *)HW_BG_PLTT +  0) = RGB( 0,  0,  0);

  *((u16 *)HW_BG_PLTT + 31) = RGB(26, 26, 26);	// �E�B���h�E�̔w�i
  //�E�B���h�E�g�L�����A�p���b�g���Z�b�g
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, STARTMENU_FCHR1, STARTMENU_FCOL1, 0, HEAPID_STARTMENU);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, STARTMENU_FCHR2, STARTMENU_FCOL2, 1, HEAPID_STARTMENU);
  // �I�����ĂȂ��E�B���h�E�̔����C��
  *((u16 *)HW_BG_PLTT + 33) = RGB(26, 26, 26);

}


//------------------------------------------------------------------
/**
 * @brief	�X�N���[���J�[�\���̕\������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void StartMenuInitClact(STARTMENU_WORK *wk)
{
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_title_cursor_lz_cngr,
		       NARC_mystery_title_cursol_nclr,
		       NARC_mystery_title_cursor_lz_ccer,
		       NARC_mystery_title_cursor_lz_canr,
		       GF_BGL_MAIN_DISP);
  wk->clcursor[0] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->clcursor[0],  HW_LCD_WIDTH/2, 8, 0);
  CLACT_SetDrawFlag(wk->clcursor[0], 0);
  wk->clcursor[1] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->clcursor[1],  HW_LCD_WIDTH/2, HW_LCD_HEIGHT - 8, 1);
  CLACT_SetDrawFlag(wk->clcursor[1], 0);
}


//------------------------------------------------------------------
/**
 * @brief	�ʐM�A�C�R���̃O���t�B�b�N�X����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define WIRELESS_CHR_BASE		0x0380
static void WirelessIconInit(STARTMENU_WORK *wk)
{
  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_wicon_nclr, PALTYPE_MAIN_BG, STARTMENU_WICON_PAL*32, 32*1, HEAPID_STARTMENU);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_wicon_ncgr, wk->bgl,
		    GF_BGL_FRAME2_M, WIRELESS_CHR_BASE, 2*32*0x20, 0, HEAPID_STARTMENU);
}


//------------------------------------------------------------------
/**
 * @brief	�w����W�ɒʐM�A�C�R����\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define WIRELESS_ICON_BASE		((STARTMENU_WICON_PAL << 12) + WIRELESS_CHR_BASE + 0)
static void SetWirelessIcon(STARTMENU_WORK *wk, int sx, int sy, int flag)
{
  u16 *scrn = (u16 *)GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  int base = WIRELESS_ICON_BASE;

  if(flag == 2)	base = WIRELESS_ICON_BASE + 2;
  
  scrn[sy * 32 + sx + 0] = base + 0;
  scrn[sy * 32 + sx + 1] = base + 1;
  sy++;
  scrn[sy * 32 + sx + 0] = base + 8;
  scrn[sy * 32 + sx + 1] = base + 9;
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}
static void ClrWirelessIcon(STARTMENU_WORK *wk, int sx, int sy)
{
  u16 *scrn = (u16 *)GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  scrn[sy * 32 + sx + 0] = WIRELESS_ICON_BASE + 4;
  scrn[sy * 32 + sx + 1] = WIRELESS_ICON_BASE + 4;
  sy++;
  scrn[sy * 32 + sx + 0] = WIRELESS_ICON_BASE + 4;
  scrn[sy * 32 + sx + 1] = WIRELESS_ICON_BASE + 4;
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	�Â�����͂��߂�̓��e�\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define STARTMENU_MARGIN_L	32
#define	STARTMENU_BLUE		(GF_PRINTCOLOR_MAKE(7, 8, 15))
#define	STARTMENU_RED		(GF_PRINTCOLOR_MAKE(3, 4, 15))

static void StartMenuContinueSub1(GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, WORDSET *word, GF_PRINTCOLOR color, u32 msgid, int y)
{
  int width, wsize;
  STRBUF * msg;

  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_STARTMENU);
  width = FontProc_GetPrintStrWidth(FONT_SYSTEM, msg,	FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_X));
  wsize = GF_BGL_BmpWinGet_SizeX(win) * 8 - (width + STARTMENU_MARGIN_L);
  GF_STR_PrintColor(win, FONT_SYSTEM, msg, wsize, y, MSG_NO_PUT, color, NULL);
  STRBUF_Delete(msg);
}
static void StartMenuContinueSub2(WORDSET *word, int value)
{
  int keta, type;
  if (value >= 100) { 	keta = 3; 	type = NUMBER_DISPTYPE_LEFT;  }
  else if (value >= 10) {	keta = 3;	type = NUMBER_DISPTYPE_SPACE; }
  else {			keta = 3 - 1;	type = NUMBER_DISPTYPE_SPACE; }
  WORDSET_RegisterNumber(word, 0, value, keta, type, NUMBER_CODETYPE_DEFAULT);
}

static BOOL StartMenuContinue(void *p, int index, MYSTERY_WIN *mw, int y)
{
  int i, width, wsize;
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  GF_PRINTCOLOR color;

  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_startmenu_dat, HEAPID_STARTMENU);
  word = WORDSET_Create(HEAPID_STARTMENU);

  // ����(FEMALE)�Ȃ�ԁA����ȊO(MALE, NEUTRAL)�Ȃ�ΐ�
  if(MyStatus_GetMySex(wk->mst) == PM_FEMALE)	color = STARTMENU_RED;
  else						color = STARTMENU_BLUE;
  
  // ��������̂P�s��\��
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
  // �Q�s�ڈȍ~��\��
  for(i = 1; i < sizeof(StartMenuContinueTable) / sizeof(u32); i++){
    // ������������Ă��Ȃ�������A�����������ڂ�\�����Ȃ�
    if(i == 4 && wk->zukangetflag == FALSE) continue;
    // ����ȊO�͕��ʂɕ\�����ėǂ�
    msg = MSGDAT_UTIL_AllocExpandString(word, msgman, StartMenuContinueTable[i], HEAPID_STARTMENU);
    GF_STR_PrintColor(mw->win, FONT_SYSTEM, msg, STARTMENU_MARGIN_L, i*16, MSG_NO_PUT, color, NULL);
    STRBUF_Delete(msg);
  }
  
  // ��l���̏��\��
  WORDSET_RegisterPlayerName(word, 0, wk->mst);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_17, 16*1);
  // �v���C���Ԃ�\��
  StartMenuContinueSub2(word, PLAYTIME_GetHour(wk->ptime));
  WORDSET_RegisterNumber(word, 1, PLAYTIME_GetMinute(wk->ptime), 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_18, 16*2);
  // �����Ă���o�b�`
  WORDSET_RegisterNumber(word, 0, wk->badgecount, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_20, 16*3);
  // �|�P����������\��
  if(wk->zukangetflag){
    StartMenuContinueSub2(word, ZukanWork_GetZukanPokeSeeCount(wk->zw));
    StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_19, 16*4);
  }
  // �܂Ƃ߂ĕ\��
  BmpMenuWinWrite(mw->win, WINDOW_TRANS_ON, mw->fchr, mw->fcol);
  // �`������t���O��ON
  wk->menuflag[index] = StartMenuWinTable[index].mark;

  WORDSET_Delete(word);
  MSGMAN_Delete(msgman);

  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�`�f�a�|�P�����̗L���𒲂ׂă��j���[�\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuAgbPokemon(void *p, int index, MYSTERY_WIN *mw, int y)
{
  int msg;
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;

  // AGB�J�[�g���b�W�̑��݂͕ʂ̃^�C�~���O�ōs���Ă��܂�
  if(wk->agbpokemon == FALSE)	return FALSE;

  // �������I��
  switch(wk->agbpokemon - 1){
  case CASTYPE_RUBY:	msg = mes_startmenu_05; break;
  case CASTYPE_SAPPHIRE:msg = mes_startmenu_06; break;
  case CASTYPE_GREEN:	msg = mes_startmenu_07; break;
  case CASTYPE_RED:	msg = mes_startmenu_08; break;
  case CASTYPE_EMERALD:	msg = mes_startmenu_09; break;
  }    
  // ���j���[�\��
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, msg);
  ClrWirelessIcon(wk, 26, y);
  wk->menuflag[index] = StartMenuWinTable[index].mark;

  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�ӂ����ȁ@��������̂�\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuCheckMystery(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;

  // �ӂ����ȁ@��������̂������I��ON�ɂ���ꍇ�̏���
  if(wk->mystery == FALSE){
    // ���łɂӂ����ȁ@��������͕̂\���\�H
    if(FUSHIGIDATA_IsFushigiMenu(wk->fdata) == TRUE)
      wk->mystery = TRUE;
    // �Q�[�����̂������Ƃ΂��������Ă���H
    if(SYSTEMDATA_GetWifiMPOpenFlag(SaveData_GetSystemData(wk->sv)) == TRUE)
      wk->mystery = TRUE;
    // AGB�ł̔z�z�p�J�Z�b�g���h�����Ă�H
    if(GetAgbCartridgeDataSize()){
      wk->mystery = TRUE;
      MysteryLib_SetAgbCartridgeIntr(TRUE);	/* AGB�J�[�g���b�W�̔������oON */
    }
  }

  // �ӂ����ȁ@��������̂������I��OFF�ɂ���ꍇ�̏���
  if(wk->mystery == TRUE){
    // ������������Ă��Ȃ���΋����I��OFF����
    if(wk->zukangetflag == FALSE)
      wk->mystery = FALSE;
  }

  // ���ۂ̃`�F�b�N��StartMenuBeacon_Proc�ōs���Ă��܂�
  if(wk->mystery == TRUE){
    // ���j���[�\��
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
#if 0
    SetWirelessIcon(wk, 26, y, 1);
    wk->iconflag[index] = 1;
#else
    ClrWirelessIcon(wk, 26, y);
#endif
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    wk->menu_flag |= PARTYGAME_MYSTERY_BCON;
    FUSHIGIDATA_SetFushigiMenu(wk->fdata);
    return TRUE;
  }

  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P���������W���[�Ƃ̐ڑ���\��
 * @param	NONE
 * @return	NONE
*/
//------------------------------------------------------------------
static BOOL StartMenuCheckRanger(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // ���ۂ̃`�F�b�N��StartMenuBeacon_Proc�ōs���Ă��܂�

  if(wk->pokemonranger == TRUE && wk->zukangetflag == TRUE){
    // ���j���[�\��
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
    SetWirelessIcon(wk, 26, y, 1);
    wk->iconflag[index] = 1;
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    wk->menu_flag |= PARTYGAME_RANGER_BCON;
    return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	Wii�̃��j���[��\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuCheckWii(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // ���ۂ̃`�F�b�N��StartMenuBeacon_Proc�ōs���Ă��܂�

  if(wk->wii == TRUE){
    // ���j���[�\��
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
    wk->iconflag[index] = 1;
    SetWirelessIcon(wk, 26, y, 1);
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	Wi-Fi�ݒ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuSetWifi(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // ���j���[�\��
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
  wk->iconflag[index] = 2;
  SetWirelessIcon(wk, 26, y, 2);
  wk->menuflag[index] = StartMenuWinTable[index].mark;
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	���j���[�쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL CreateStartMenu(STARTMENU_WORK *wk)
{
  STARTMENU_DATA *smd;
  MYSTERY_WIN mw;
  int i, y, ret;

  ret = FALSE;
  y = 1;
  wk->chrbase = STARTMENU_WCHR;
  for(i = 0; i < MENU_WIN_MAX; i++){
    smd = &StartMenuWinTable[i];

    MysteryLib_WinInit1(&mw, &wk->mwin[i], STARTMENU_WCOL_NORMAL, NARC_msg_startmenu_dat, STARTMENU_FCHR1, STARTMENU_FCOL1);
    MysteryLib_WinInit2(&mw, 26, smd->height,/* NULL,*/ wk->chrbase);
    if(smd->func){
      // func�����ŕ\��
      if(wk->menuflag[i]){
	GF_BGL_BmpWinSet_PosX(mw.win, 3);
	GF_BGL_BmpWinSet_PosY(mw.win, y);
	BmpMenuWinWrite(mw.win, WINDOW_TRANS_ON, mw.fchr, mw.fcol);
	if(wk->iconflag[i])	SetWirelessIcon(wk, 26, y, wk->iconflag[i]);
	else			ClrWirelessIcon(wk, 26, y);
	y += smd->height + 2;
	ret = TRUE;
      } else if(smd->func(wk, i, &mw, y) == TRUE){
	y += smd->height + 2;
	ret = TRUE;
      }
    } else {
      // �ʏ�\��
      MysteryLib_CreateWin(wk->bgl, &mw, 3, y, smd->msgid);
      wk->menuflag[i] = smd->mark;
      y += smd->height + 2;
    }
    wk->chrbase += 26 * smd->height;
  }
  return ret;
}


//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�̘g(�t���[��)���ĕ\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RedrawWindowFrame(STARTMENU_WORK *wk, int select)
{
  int i;
  for(i = 0; i < sizeof(StartMenuWinTable) / sizeof(STARTMENU_DATA); i++){
    if(GF_BGL_BmpWinAddCheck(&wk->mwin[i]) == FALSE)	continue;

    if(i == select){
      BmpMenuWinWrite(&wk->mwin[i], WINDOW_TRANS_OFF, STARTMENU_FCHR2, STARTMENU_FCOL2);
      GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_M,
			  GF_BGL_BmpWinGet_PosX(&wk->mwin[i]),  GF_BGL_BmpWinGet_PosY(&wk->mwin[i]),
			  GF_BGL_BmpWinGet_SizeX(&wk->mwin[i]), GF_BGL_BmpWinGet_SizeY(&wk->mwin[i]),
			  STARTMENU_WCOL_SELECT);
    } else {
      BmpMenuWinWrite(&wk->mwin[i], WINDOW_TRANS_OFF, STARTMENU_FCHR1, STARTMENU_FCOL1);
      GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_M,
			  GF_BGL_BmpWinGet_PosX(&wk->mwin[i]),  GF_BGL_BmpWinGet_PosY(&wk->mwin[i]),
			  GF_BGL_BmpWinGet_SizeX(&wk->mwin[i]), GF_BGL_BmpWinGet_SizeY(&wk->mwin[i]),
			  STARTMENU_WCOL_NORMAL);
    }
  }
  // �X�N���[���̑S�̂��ē]��
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME0_M);
}


//------------------------------------------------------------------
/**
 * @brief	���̃J�[�\���ʒu����������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void NextCursorPosition(STARTMENU_WORK *wk, int offset)
{
  int now = wk->cursor;

  while(1){
    now += offset;
    // �I�[�o�[�t���[����
    if(now == -1)		now = 0;
    if(now == MENU_WIN_MAX)	now = MENU_WIN_MAX - 1;
    // ������ꏊ���Ȃ���Γ����Ȃ�
    if(now == wk->cursor)
      break;
    // ������ꏊ�����������猈��
    if(wk->menuflag[now]){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      break;
    }
  }

  wk->cursor = now;
}


//------------------------------------------------------------------
/**
 * @brief	�J�[�\������ʓ��ɓ���悤�ɃX�N���[���o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCursorScroll(STARTMENU_WORK *wk)
{
  int cursory, height, basey;

  // �h�b�g���Z�̃J�[�\���ʒu���Z�o
  cursory = (GF_BGL_BmpWinGet_PosY(&wk->mwin[wk->cursor] ) - 1) * 8;
  height = (GF_BGL_BmpWinGet_SizeY(&wk->mwin[wk->cursor] ) + 2) * 8;

  // ���݂̃X�N���[���l(�ړI���W)
  basey = wk->target / FX32_ONE;

  // ��ʂ̒��ɓ����Ă��邩��������

  // ��ʂ̏�ɂ͂ݏo�Ă�̂ŉ��ɃX�N���[���Z�b�g
  if(basey > cursory){
    wk->target = cursory * FX32_ONE;
  }
  // ��ʂ̉��ɂ͂ݏo�Ă���̂ŏ�ɃX�N���[���Z�b�g
  if(basey + HW_LCD_HEIGHT <= cursory){
    wk->target = ((cursory + height) - HW_LCD_HEIGHT) * FX32_ONE;
  }
}


//------------------------------------------------------------------
/**
 * @brief	�㉺�J�[�\���̕\���^��\������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCursorVisible(STARTMENU_WORK *wk)
{
  int i, du, dd;
  int cursory, height, basey;

  du = dd = FALSE;

  // ���݂̃X�N���[���l(�ړI���W)
  basey = wk->target / FX32_ONE;

  for(i = 0; i < MENU_WIN_MAX; i++){
    if(GF_BGL_BmpWinAddCheck(&wk->mwin[i]) == FALSE)
      continue;

    // �h�b�g���Z�̃J�[�\���ʒu���Z�o
    cursory = (GF_BGL_BmpWinGet_PosY(&wk->mwin[i] ) - 1) * 8;
    height = (GF_BGL_BmpWinGet_SizeY(&wk->mwin[i] ) + 2) * 8;

    // ��̂͂ݏo���`�F�b�N
    if(basey > cursory)
      du = TRUE;
    // ���̂͂ݏo���`�F�b�N
    if(basey + HW_LCD_HEIGHT <= cursory)
      dd = TRUE;
  }

  CLACT_SetDrawFlag(wk->clcursor[0], du);
  CLACT_SetDrawFlag(wk->clcursor[1], dd);

}


//------------------------------------------------------------------
/**
 * @brief	�����̏I�� �������J���Ȃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void StartMenuFinish(PROC *proc)
{
  int i;
  STARTMENU_WORK *wk = PROC_GetWork(proc);

  // �A�N�^�[�֘A�̊J��
  if(wk->clcursor[0] || wk->clcursor[1]){
    CLACT_Delete(wk->clcursor[0]);
    CLACT_Delete(wk->clcursor[1]);
    MysteryLib_RemoveClact();
  }
  
  // �E�B���h�E�J��
  for(i = 0; i < MENU_WIN_MAX; i++){
    if(wk->mwin[i].ini){
      GF_BGL_BmpWinOff(&wk->mwin[i]);
      GF_BGL_BmpWinDel(&wk->mwin[i]);
    }
  }
  // BGL�J��
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  sys_FreeMemoryEz(wk->bgl);
  sys_VBlankFuncChange(NULL, NULL);
}


//------------------------------------------------------------------
/**
 * @brief	�I���E�B���h�E�̃p���b�g�A�j��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u16 animtable[] = {
  RGB( 1, 28, 20),  RGB( 3, 28, 20),  RGB( 5, 28, 20),  RGB( 7, 28, 20),
  RGB( 9, 28, 20),  RGB(11, 28, 20),  RGB(13, 28, 20),  RGB(15, 28, 20),
  RGB(17, 28, 20),  RGB(19, 28, 20),  RGB(21, 28, 20),  RGB(23, 28, 20),
  RGB(25, 28, 20),  RGB(27, 28, 20),  RGB(29, 28, 20),  RGB(31, 28, 20),
  RGB(29, 28, 20),  RGB(27, 28, 20),  RGB(25, 28, 20),  RGB(23, 28, 20),
  RGB(21, 28, 20),  RGB(19, 28, 20),  RGB(17, 28, 20),  RGB(15, 28, 20),
  RGB(13, 28, 20),  RGB(11, 28, 20),  RGB( 9, 28, 20),  RGB( 7, 28, 20),
  RGB( 5, 28, 20),  RGB( 3, 28, 20),
  0,
};
static void SelectPalAnim(STARTMENU_WORK *wk)
{
  u16 *col = (u16 *)0x0500006C;
  if(animtable[wk->anim_index] == 0)
    wk->anim_index = 0;
  *col = animtable[wk->anim_index++];
}

static void VBlankFunc(void *work)
{
  // �Z���A�N�^�[Vram�]���}�l�[�W���[���s
  DoVramTransferManager();
  // �����_�����LOAM�}�l�[�W��Vram�]��
  REND_OAMTrans();	
  GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
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
static PROC_RESULT StartMenuProc_Init(PROC * proc, int * seq)
{
  STARTMENU_WORK *wk;

  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_STARTMENU, 0x40000);
  //  sys_PrintHeapFreeSize(HEAPID_STARTMENU);
  wk = PROC_AllocWork(proc, sizeof(STARTMENU_WORK), HEAPID_STARTMENU);
  // �������s�ǂ��|���̂Ń��[�N�̓[���N���A
  memset(wk, 0, sizeof(STARTMENU_WORK));

  /* �e��ϐ��̏����� */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_STARTMENU);

  /* ��ʂ̏����ݒ� */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* �ϐ������� */
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->fdata = SaveData_GetFushigiData(wk->sv);
  //  wk->cursor = 0;
  wk->scrolly = FX32_ONE * 0;
  wk->target  = FX32_ONE * 0;

  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->zw = SaveData_GetZukanWork(wk->sv);
  wk->ptime = SaveData_GetPlayTime(wk->sv);

  wk->zukangetflag = ZukanWork_GetZukanGetFlag(wk->zw);
  wk->badgecount = MyStatus_GetBadgeCount(wk->mst);
  wk->beacon_msg_seq = BEACON_MSGSEQ_NOP;
  
  // ���C�u����������
  MysteryLib_Init(HEAPID_STARTMENU);

  // �Z�[�u�f�[�^��������΃X�^�[�g���j���[���̂�\�������Ȃ�
  if(!SaveData_GetExistFlag(wk->sv)){
    wk->pass_start_menu = TRUE;
  }

  Snd_BgmChannelSetAndReverbSet( 0 );	// �g�p�\�`�����l������A���o�[�u�ݒ�(�N���A)
  Snd_SceneSet( SND_SCENE_DUMMY );		// ���̃V�[�����K���ǂݍ��܂��悤�ɂ��Ă����I

#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("sizeof(POKEMON_PARAM) = %d\n", PokemonParam_GetWorkSize());
  OS_TPrintf("sizeof(_SEND_FLAG) = %d\n", CommPlayerNowFlagDataArraySize());
  OS_TPrintf("sizeof(MYSTATUS) = %d\n", MyStatus_GetWorkSize());
#endif

#ifdef CREATE_INDEX
  CreateIndexData(HEAPID_STARTMENU);
#endif

  
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
static PROC_RESULT StartMenuProc_Main(PROC * proc, int * seq)
{
  int ret;
  STARTMENU_WORK *wk = PROC_GetWork(proc);
  wk->jiffy++;
  CTRDG_IsExisting();

  // �r�[�R����M���̃��b�Z�[�W�\���V�[�P���X
  if(BeaconMessage_Proc(wk) == TRUE){
    StartMenuBeacon_Proc(wk);
    StartMenuProc(wk);
    return PROC_RES_CONTINUE;
  }

  // �I������Ă���E�B���h�E���p���b�g�A�j���[�V����
  SelectPalAnim(wk);

  switch(*seq){
  case STARTMENU_SEQ_INIT:
    // �a�f�֌W�̕K�v�Œ���̏�����
    InitStartMenuScreen(wk);
    SetSeq(*seq, STARTMENU_SEQ_CHECK_SYSTEM);
    break;

  case STARTMENU_SEQ_CHECK_SYSTEM:
    // �e��V�X�e���̃`�F�b�N(��C�Ƀ`�F�b�N�A�����\��)
    if(StartMenuCheckSystem(wk) == 0){
      SetSeq(*seq, STARTMENU_SEQ_HARDINIT);
    } else {
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, STARTMENU_SEQ_DISP_ERROR, seq, STARTMENU_SEQ_FADE_WAIT);
      *((u16 *)HW_BG_PLTT +  0) = RGB(12, 12, 31);
    }
    break;

  case STARTMENU_SEQ_DISP_ERROR:
    // �G���[���������̂ŏڍׂ�\�����܂���
    if(StartMenuDisplayError(wk) == FALSE)
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_HARDINIT, seq, STARTMENU_SEQ_FADE_WAIT);
    break;
    
  case STARTMENU_SEQ_HARDINIT:
    wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    // �Z�[�u�f�[�^���Ȃ���΃Q�[���̍ŏ�����n�߂�
    if(wk->pass_start_menu == TRUE){
      wk->select = SEL_FIRSTGAME;
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
    } else {
      // AGB�J�[�g���b�W�̏����������Ď��̃V�[�P���X��
      AgbCartridgeInit(wk);
      SetSeq(*seq, STARTMENU_SEQ_CREATE_SCREEN);
    }
    break;

  case STARTMENU_SEQ_CREATE_SCREEN:
    // �J�[�\���I�u�W�F�N�g�̓ǂݍ���
    StartMenuInitClact(wk);
    // ���C�����X�A�C�R���̓ǂݍ���
    WirelessIconInit(wk);
    sys_VBlankFuncChange(VBlankFunc, wk->bgl);

    // �X�N���[���쐬(��{�`)
    CreateStartMenu(wk);
    RedrawWindowFrame(wk, wk->cursor);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, STARTMENU_SEQ_MAIN, seq, STARTMENU_SEQ_FADE_WAIT);
    *((u16 *)HW_BG_PLTT +  0) = RGB(12, 12, 31);
    // �r�[�R���̎��W���J�n����
    wk->beacon_seq = STARTMENU_BEACON_SEQ_INIT;
    break;

  case STARTMENU_SEQ_MAIN:
    // ����{�^�� / �L�����Z���{�^��
    if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
      if(sys.trg & PAD_BUTTON_DECIDE){
	Snd_SePlay(SEQ_SE_DP_SELECT);
	wk->select = wk->menuflag[wk->cursor];

	// AGB�J�Z�b�g����A��Ă����I�񂾍ۂ̒�~���菈��
	if(wk->select == SEL_AGBPOKEMON){
	  if(CTRDG_IsPulledOut() == TRUE)
	    CTRDG_TerminateForPulledOut();
	}
	
      } else {
	Snd_SePlay(SEQ_SE_DP_SELECT);
	wk->select = SEL_CANCEL;
	MysteryLib_ChangeFadeType(1);
      }
      if(wk->select == SEL_FIRSTGAME){
	// �������傩��͂��߂��I�������ꍇ�ɂ͌x����ʂ�\������
	wk->beacon_status |= STARTMENU_FIRSTGAME_SELECT;
	wk->beacon_msg_wait = 1;
	SetSeq(*seq, STARTMENU_SEQ_SELECT_FIRSTGAME);
      } else {
	if(wk->select == SEL_WII)
	  MysteryLib_ChangeFadeType(1);
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
      }

      // �r�[�R�����W���������狭���I��������
      if(wk->beacon_seq == STARTMENU_BEACON_SEQ_TIMER)
	wk->beacon_seq = STARTMENU_BEACON_SEQ_CANCEL;
      break;
    }
    
    // �ĕ`��̕K�v������΍ĕ`�悷��
    if(wk->redrawflag == TRUE){
      CreateStartMenu(wk);
      wk->redrawflag = FALSE;
      break;
    }

    // �J�[�\���ړ�
    if(sys.trg & PAD_KEY_UP)
      NextCursorPosition(wk, -1);
    if(sys.trg & PAD_KEY_DOWN)
      NextCursorPosition(wk,  1);
    // �X�N���[����������
    RedrawWindowFrame(wk, wk->cursor);
    // �X�N���[������
    SetCursorScroll(wk);
    // �㉺�J�[�\���̕\������
    SetCursorVisible(wk);

    // ���X�N�G�X�g���o�Ă���΃|�b�v�A�b�v���j���[�̓o�^
    if(*seq == STARTMENU_SEQ_MAIN && wk->req_popup == TRUE){
      wk->req_popup = FALSE;
      wk->beacon_msg_wait = 1;
    }
    
    break;

  case STARTMENU_SEQ_SELECT_FIRSTGAME:
    // �������傩��͂��߂��I�񂾎��͌x����\��
    if(wk->beacon_msg_seq == BEACON_MSGSEQ_NOP){
      if(wk->beacon_result & PAD_BUTTON_CANCEL){
	SetSeq(*seq, STARTMENU_SEQ_MAIN);
      } else {
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
      }
    }
    break;

    
  case STARTMENU_SEQ_SELECT_MENU:
    // �������Q���J��
    StartMenuFinish(proc);
    return PROC_RES_FINISH;
    break;

    
  case STARTMENU_SEQ_FADE_WAIT:
    // �t�F�[�h���I������܂ő҂��Ď��̃V�[�P���X��
    MysteryLib_FadeEndCheck(seq);
    break;

  case STARTMENU_SEQ_FINISH:
    return PROC_RES_FINISH;
    break;
  }

  StartMenuBeacon_Proc(wk);
  StartMenuProc(wk);
  MysteryLib_DoClact();
  
  return PROC_RES_CONTINUE;
}



//------------------------------------------------------------------
/**
 * @brief	�I�����ꂽ���j���[�ɂ���ď�������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#include "system/gamestart.h"
#include "demo/title.h"
FS_EXTERN_OVERLAY( title );
#define CHECK_OVERLAY
#ifdef CHECK_OVERLAY
FS_EXTERN_OVERLAY( startmenu );
#endif
extern const PROC_DATA MysteryGiftProcData;
extern const PROC_DATA AgbCartridgeProcData;
extern const PROC_DATA PokemonRangerProcData;
extern const PROC_DATA StartMenuWifiProcData;

static void StartMenuSetNextProc(STARTMENU_WORK *wk)
{
  switch(wk->select){
  case SEL_CONTINUE:	// �Â�����@�͂��߂�
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &ContinueGameStartProcData);
    break;
  case SEL_FIRSTGAME:	// �������傩��@�͂��߂�
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &NewGameStartProcData);
    break;
  case SEL_MYSTERY:	// �ӂ����ȁ@���������
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &MysteryGiftProcData);
#else
    Main_SetNextProc(NO_OVERLAY_ID, &MysteryGiftProcData);
#endif
    break;
  case SEL_AGBPOKEMON:	// �~�~�~����@��Ă���
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &AgbCartridgeProcData);
#else
    Main_SetNextProc(NO_OVERLAY_ID, &AgbCartridgeProcData);
#endif
    break;
  case SEL_RANGER:	// �|�P���������W���[�Ƃ́@������
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &PokemonRangerProcData);
#else
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &PokemonRangerProcData);
#endif
    break;
  case SEL_WII:		// Wii�Ɓ@������
    rebooter(WIICLIENT_FILE);
    break;  case SEL_WIFI:	// Wi-Fi�����Ă�
    Snd_Stop();
    Main_SetNextProc(NO_OVERLAY_ID, &StartMenuWifiProcData);
    break;
  case SEL_CANCEL:	// �L�����Z��
    Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
    break;
  }
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
static PROC_RESULT StartMenuProc_End(PROC * proc, int * seq)
{
  STARTMENU_WORK *wk = PROC_GetWork(proc);

  StartMenuSetNextProc(wk);

  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_STARTMENU);

  /* AGB�J�[�g���b�W�̔������oOFF */
  MysteryLib_SetAgbCartridgeIntr(FALSE);

  return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------
// ���̒�`��src/demo/title.c����Q�Ƃ���܂�
//--------------------------------------------------------------------------------------------
//FS_EXTERN_OVERLAY(startmenu);
const PROC_DATA StartMenuProcData = {
  StartMenuProc_Init,
  StartMenuProc_Main,
  StartMenuProc_End,
  NO_OVERLAY_ID,
};



/*  */
