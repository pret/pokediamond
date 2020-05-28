//============================================================================================
/**
 * @file	pokemonranger.c	
 * @bfief	�|�P���������W���[�Ƃ̐ڑ����/���܂��]��
 * @author	Satoshi Mitsuhara
 * @date	06.04.27
 *
 * $Id: pokemonranger.c,v 1.21 2006/08/01 14:41:26 mitsuhara Exp $
 */
//============================================================================================

// BG0		���j���[�⃁�b�Z�[�W�\��
// BG1		�i�q�͗l�̔w�i

#include "common.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/render_oam.h"
#include "system/pm_rtc.h"
#include "system/snd_tool.h"
#include "system/window.h"
#include "system/msgdata_util.h"

#include "savedata/zukanwork.h"
#include "savedata/config.h"
#include "savedata/savedata.h"
#include "savedata/fushigi_data.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_startmenu.h"
#include "msgdata/msg_bconfind.h"
#include "msgdata/msg_mystery.h"
#include "strbuf_family.h"	//for STRBUF_SetStringCode ������

#include "demo/title.h"
#include "field/field.h"

#include "system/main.h"
#include "system/brightness.h"

#include "communication/communication.h"
#include "communication/comm_system.h"
#include "communication/comm_mp.h"
#include "communication/mpconnect.h"
#include "communication/mpdata.h"

#include "system/startmenu.h"
#include "poketool/monsno.h"

#include "mysterylib.h"
#include "mystery.naix"


#include "pokemonrangerdata.h"

//============================================================================================
/**
 * ���|�P���������W���[�Ƃ̐ڑ���ʗp���[�N��`��
 */
//============================================================================================

#define POKEMONRANGER_WCOL_NORMAL	0
#define POKEMONRANGER_FCOL		1
#define POKEMONRANGER_TWCOL		2

#define POKEMONRANGER_FCHR		1			// �ʏ�t���[��
#define POKEMONRANGER_TWCHR		(POKEMONRANGER_FCHR + MENU_WIN_CGX_SIZ)
#define POKEMONRANGER_WCHR		(POKEMONRANGER_TWCHR + TALK_WIN_CGX_SIZ)



typedef struct {
  int heapid;
  GF_BGL_INI * bgl;
  SAVEDATA *sv;
  ZUKAN_WORK *zw;
  MYSTATUS *mst;
  CONFIG *cfg;

  GF_BGL_BMPWIN	ewin;
  GF_BGL_BMPWIN	twin;		// TalkWin�p�̃r�b�g�}�b�v�Ǘ��\����
  GF_BGL_BMPWIN	swin;		// �X�e�[�^�X�\���p�r�b�g�}�b�v�Ǘ��\����

  MYSTERY_WIN talkwin;		// TalkWint�o�^�p
  MYSTERY_WIN titlewin;		// �^�C�g���\���E�B���h�E
  MYSTERY_WIN statwin;		// �X�e�[�^�X�\���p�E�B���h�E

  int chrbase;
  int commvramload;		// �C�N�j���[���������݂��鎞��TRUE

  
  int beacon_seq;		// �r�[�R���擾�V�[�P���X
  int beacon_ret;		// ��L�̃��^�[���l
  
  int beacon_check_time;	// �r�[�R�����`�F�b�N���鎞��
  int doproc;			// true = MpProc�쓮
  int seq;			// �쓮�V�[�P���X
  int mp_time_out;		// �^�C���A�E�g�܂ł̃J�E���g
  int connect_num;		// �R�l�N�V�����ԍ�
  int disable;			// true = �ʐM���f�v���t���O
  u8 mp_buf[12*1024];		// MP�ʐM�쓮�p���[�N�G���A(���ۂɂ͖�10KB�K�v)
  PROC *proc;			// proc

  //  MYSTERY_CLACT act;
  CLACT_WORK_PTR arrow;
  
  FUSHIGI_DATA *fdata;		// �Z�[�u�p�̂ӂ����f�[�^�����[�h�����ꏊ
  LOAD_RESULT result;		// ��L�f�[�^�̃��[�h��

  int warning_msg;		// �x����ʎ��̃��b�Z�[�WID

  GIFT_CARD gc;			// �J�[�h��\�����邽�߂ɕK�v

  void *time_icon;		// �^�C���A�C�R���p
  
} POKEMONRANGER_WORK;


// CheckPokemonRangerBeacon�֐����Ԃ��l
enum {
  POKEMONRANGER_RET_NONE,	// �����C�x���g�͖���
  POKEMONRANGER_RET_FOUNDRANGER,// �����W���[���������I
  POKEMONRANGER_RET_DISCONNECT,	// �ʐM���؂ꂽ
  POKEMONRANGER_RET_TIMEOUT,	// �^�C���A�E�g
  POKEMONRANGER_RET_SUCCESS,	// ���܂��ʐM����
  POKEMONRANGER_RET_CANCEL,	// ���[�U�[����̃L�����Z��
  POKEMONRANGER_RET_MAX
};

#define POKEMONRANGER_CHECK_BEACON_TIME		(60)


#if 0
char *vtable[] = {
  "POKEMONRANGER_COMM_INIT",
  "POKEMONRANGER_COMM_IDLE",
  "POKEMONRANGER_COMM_CHECK_PARENT_INIT",
  "POKEMONRANGER_COMM_CHECK_PARENT",
  "POKEMONRANGER_COMM_CONNECT_WAIT_PARENT",
  "POKEMONRANGER_COMM_CREATE_SCREEN",
  "POKEMONRANGER_COMM_WAIT_FADE_CREATE_SCREEN",
  "POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT",
  "POKEMONRANGER_COMM_SELECT_WAIT_PARENT",
  "POKEMONRANGER_COMM_FIND_PARENT",
  "POKEMONRANGER_COMM_SEND_USERDATA_WAIT",
  "POKEMONRANGER_COMM_RECV_PARENT_INIT",
  "POKEMONRANGER_COMM_RECV_PARENT",
  "POKEMONRANGER_COMM_RECV_SUCCESS",
  "POKEMONRANGER_COMM_SAVE_WAIT",
  "POKEMONRANGER_COMM_SAVE_DUMMY_WAIT",
  "POKEMONRANGER_COMM_SAVE_SYNC",
  "POKEMONRANGER_COMM_SAVE_SYNC_WAIT",
  "POKEMONRANGER_COMM_SAVE_SYNC_END",
  "POKEMONRANGER_COMM_RECV_END_WAIT",
  "POKEMONRANGER_COMM_RECV_END",
  "POKEMONRANGER_COMM_NOTFIND_PARENT",
  "POKEMONRANGER_COMM_DISCONNECT_PARENT",
  "POKEMONRANGER_COMM_TIMEOUT",
  "POKEMONRANGER_COMM_CANSEL",
  "POKEMONRANGER_COMM_STOP",
  "POKEMONRANGER_COMM_RETURN_TITLE",
  "POKEMONRANGER_COMM_LOOP",
  "POKEMONRANGER_COMM_RESET",
};
#endif


enum {
    POKEMONRANGER_COMM_INIT,			// ���[�h�J�n����̃t�F�[�h�҂�
    POKEMONRANGER_COMM_IDLE,			// �ʐM���C�u�����̏����҂�
    POKEMONRANGER_COMM_CHECK_PARENT_INIT,	// �����W���[�i�e�@�j��T�����߂̏�����
    POKEMONRANGER_COMM_CHECK_PARENT,		// �����W���[�i�e�@�j��T��
    POKEMONRANGER_COMM_CONNECT_WAIT_PARENT,	// �����W���[�i�e�@�j�̐ڑ��\��҂��ڑ���v��
    POKEMONRANGER_COMM_CREATE_SCREEN,		// �V�K�ǉ��@��ʂ����
    POKEMONRANGER_COMM_WAIT_FADE_CREATE_SCREEN,	// �V�K�ǉ��@�t�F�[�h���I������̂�҂�
    POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT,	// �����W���[�i�e�@�j�̐ڑ��҂�
    POKEMONRANGER_COMM_SELECT_WAIT_PARENT,	// �����W���[�i�e�@�j�ƃf�[�^�ʐM���邩�ǂ����̑I��
    POKEMONRANGER_COMM_FIND_PARENT,		// �����W���[�i�e�@�j�ɐڑ��� ���[�U�[�f�[�^���M��
    POKEMONRANGER_COMM_SEND_USERDATA_WAIT,	// �����W���[�i�e�@�j�ւ̃��[�U�[�f�[�^���M�I���҂�
    POKEMONRANGER_COMM_RECV_PARENT_INIT,	// �����W���[�i�e�@�j�����M���邽�߂̏�����
    POKEMONRANGER_COMM_RECV_PARENT,		// �����W���[�i�e�@�j�����M��
    POKEMONRANGER_COMM_RECV_SUCCESS,		// �����W���[�i�e�@�j����̎�M���� �^�}�S���Z�[�u�J�n
    POKEMONRANGER_COMM_SAVE_WAIT,		// �^�}�S���Z�[�u��
    POKEMONRANGER_COMM_SAVE_DUMMY_WAIT,		// �����W���[�i�e�@�j�ɓ����҂����O�̃_�~�[�҂�
    POKEMONRANGER_COMM_SAVE_SYNC,		// �^�}�S���Z�[�u�I�� �����W���[�i�e�@�j�ɓ����҂����N�G�X�g
    POKEMONRANGER_COMM_SAVE_SYNC_WAIT,		// �����W���[�i�e�@�j�ɓ����҂���    
    POKEMONRANGER_COMM_SAVE_SYNC_END,
    POKEMONRANGER_COMM_RECV_END_WAIT,
    POKEMONRANGER_COMM_RECV_END,		// �����W���[�i�e�@�j����̎�M�^�^�}�S���Z�[�u�I��
    POKEMONRANGER_COMM_NOTFIND_PARENT,		// �����W���[�i�e�@�j��������Ȃ������^�ڑ��ł��Ȃ�����
    POKEMONRANGER_COMM_DISCONNECT_PARENT,	// �����W���[�i�e�@�j�Ƃ̐ڑ�����
    POKEMONRANGER_COMM_TIMEOUT,			// �����W���[�Ƃ̒ʐM���^�C���A�E�g����
    POKEMONRANGER_COMM_CANSEL,			// �����W���[�Ƃ̒ʐM���L�����Z��
    POKEMONRANGER_COMM_STOP,			// �����W���[�Ƃ̑S�Ă̒ʐM�I��
    POKEMONRANGER_COMM_RETURN_TITLE,		// �ʐM���I�������ă^�C�g���֖߂�
    POKEMONRANGER_COMM_LOOP,			// �������Ȃ�
    POKEMONRANGER_COMM_RESET,			// ���Z�b�g����

    POKEMONRANGER_COMM_END

} POKEMONRANGER_COMM;


enum {
  // ���C���V�[�P���X
  POKEMONRANGER_SEQ_INIT,			// ��ԍŏ��̏����ݒ�
  POKEMONRANGER_SEQ_DISP_ERROR,			// �N���ɃG���[������Ε\�����ďI��
  POKEMONRANGER_SEQ_INIT_SCREEN,		// �ŏ��̉�ʂ�\��
  POKEMONRANGER_SEQ_FULL_WARNING,		// �x����ʕ\��

  POKEMONRANGER_SEQ_MAIN,
  POKEMONRANGER_SEQ_DISP_CARD_INIT,
  POKEMONRANGER_SEQ_DISP_CARD,


  // �r�[�R�������V�[�P���X
  POKEMONRANGER_SEQ_BEACON_INIT,		// �]���ɕK�v�ȃf�[�^�̏�����
  POKEMONRANGER_SEQ_BEACON_FIND,		// �r�[�R����T���Đڑ�
  POKEMONRANGER_SEQ_BEACON_WAIT,		// �������Ȃ�
  POKEMONRANGER_SEQ_BEACON_MAIN,		// �f�[�^�̎�M���̑�����


  POKEMONRANGER_SEQ_RESET,			// �\�t�g�E�F�A���Z�b�g
  POKEMONRANGER_SEQ_FINISH,			// �I�����ă^�C�g����ʂ֖߂�
  POKEMONRANGER_SEQ_FADE_WAIT,
  
  POKEMONRANGER_SEQ_END
} POKEMONRANGER_SEQ;


#define POKEMONDP_CONNECT_ID		21
#define POKEMONRANGER_CONNECT_CH	1


#define POKEMONRANGER_FRAMECHR1	1
#define POKEMONRANGER_FRAMECHR2	(POKEMONRANGER_FRAMECHR1+9)
#define POKEMONRANGER_WINDOWCHR	(POKEMONRANGER_FRAMECHR2+9)
#define WAKU_PALETTE_NUMBER1	2
#define WAKU_PALETTE_NUMBER2	3
#define	FONT_PAL_NO_N		( 0 )	// �m�[�}���p���b�g
#define	FONT_PAL_NO_S		( 1 )	// �I�����p���b�g
#define	POKEMONRANGER_BLACK	(GF_PRINTCOLOR_MAKE(1, 2, 15))
#define	POKEMONRANGER_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))

#define RGB(r, g, b)	(((b)&31)<<10|((g)&31)<<5|((r)&31))


static void StartMenu_RangerScreenInit(PROC * proc);
static void PokemonRangerInitSubScreen(POKEMONRANGER_WORK *wk);
static void DisplaySequence(PROC *proc, u32 msgid);
static void PokemonRanger_ScreenFinish(PROC *proc);

extern int CheckPokemonRangerBeacon(POKEMONRANGER_WORK *wk);
extern int DisablePokemonRangerBeacon(POKEMONRANGER_WORK *wk);

extern void StartMenu_BgInit(PROC * proc);

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *, int heapid);



// ���[�U�[��
static u16 ModeDptestName[PERSON_NAME_SIZE+EOM_SIZE] = { 0 };
// ���[�U�[�h�c
static u16 ModeDptestUserId[10] = { 0 };

// ��M�f�[�^�o�b�t�@
static u8 ModeDptestRecvData[42] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

// MP�ʐM�p�f�X�N���v�^
static MpInitDesc init_desc = {
  22, 1, OS_LANGUAGE_JAPANESE, POKEMONDP_CONNECT_ID, ModeDptestUserId, ModeDptestName,
};


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�쓮�p��VBlankFunc
 */
//------------------------------------------------------------------
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
 * @brief	�ʐM�ɕK�v�ȃf�[�^�̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitConnectData(POKEMONRANGER_WORK *wk)
{
  int i;
  u32 code;
  const STRCODE *datap;

  // ���[�U�[����RANGER-CODE�֕ϊ����Ċi�[
  datap = MyStatus_GetMyName( wk->mst );
  for(i = 0; i < PERSON_NAME_SIZE+EOM_SIZE; i++)
    ModeDptestName[i] = ConvDP2Ranger(datap[i]);

  // ���[�U�[ID�𕶎���֕ϊ����Ċi�[
  code = MyStatus_GetID_Low(wk->mst);
  ConvDPDec2RangerDec(&ModeDptestUserId[0], code);
  ModeDptestUserId[5] = ranger_EOM_;
}


//------------------------------------------------------------------
/**
 * @brief	�a�f������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitScreen(POKEMONRANGER_WORK *wk)
{
  int type;

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
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCRSIZ_256x256, 0xF000, 0x0000); /* MAIN DISP BG0 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_M, GF_BGL_SCRSIZ_256x256, 0xF800, 0x4000); /* MAIN DISP BG1 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_S, GF_BGL_SCRSIZ_256x256, 0x7800, 0x0000); /* SUB DISP BG0 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_S, GF_BGL_SCRSIZ_256x256, 0x7000, 0x4000); /* SUB DISP BG1 */
  MSG_PrintInit();

  /* ���b�Z�[�W�̃t�H���g�J���[��ݒ� */
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, POKEMONRANGER_WCOL_NORMAL * 32, wk->heapid);

  //�E�B���h�E�g�L�����A�p���b�g���Z�b�g
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, POKEMONRANGER_FCHR,  POKEMONRANGER_FCOL,     0, wk->heapid);
  type = CONFIG_GetWindowType(wk->cfg);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, POKEMONRANGER_TWCHR, POKEMONRANGER_TWCOL, type, wk->heapid);

  // �i�q�͗l��\������
  // ���C����ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*8, 16*2, wk->heapid);
  // ���C�����BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME1_M, 0, 10*16*0x20, 1, wk->heapid);
  // ���C����ʃX�N���[���P
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, wk->bgl,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME1_M, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME1_M);
  // �T�u��ʂ̊i�q�͗l��\��
  PokemonRangerInitSubScreen(wk);
}


//------------------------------------------------------------------
/**
 * @brief	�T�u��ʂ̊i�q�͗l��\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitSubScreen(POKEMONRANGER_WORK *wk)
{
  // �T�u��ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2, wk->heapid);
  // �T�u���BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME0_S, 0, 10*16*0x20, 1, wk->heapid);
  // �T�u��ʃX�N���[���O
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, wk->bgl,
		  GF_BGL_FRAME0_S, 0, 32*24*2, 1, wk->heapid);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_S, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME0_S);
}

//------------------------------------------------------------------
/**
 * @brief	������������ĂȂ����̃G���[�\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL PokemonRangerNoHaveZukan(POKEMONRANGER_WORK *wk)
{
  MYSTERY_WIN mw;

  // �G���[�\���E�B���h�E������������Ă��邩�ǂ����Ŕ��f���s��������
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == FALSE){
    MysteryLib_WinInit1(&mw, &wk->ewin, POKEMONRANGER_WCOL_NORMAL, NARC_msg_bconfind_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
    MysteryLib_WinInit2(&mw, 22, 16,wk->chrbase);
    MysteryLib_CreateWin(wk->bgl, &mw, 5, 4, bcon_003);
    return TRUE;
  } else {
    // �G���[�E�B���h�E�̕\����
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
      BmpMenuWinClear(&wk->ewin, WINDOW_TRANS_ON);
      GF_BGL_BmpWinDel(&wk->ewin);
      return FALSE;
    }
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	���܂��̎�M��ʂ��쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DisplayRangerStatus(POKEMONRANGER_WORK *wk);
static void PokemonRangerCreateScreen(POKEMONRANGER_WORK *wk)
{
  // �����̃��b�Z�[�W�\��(��b�E�B���h�E���J��)
  MysteryLib_WinInit1(&wk->talkwin, &wk->twin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_TWCHR, POKEMONRANGER_TWCOL);
  MysteryLib_WinInit2(&wk->talkwin, 27, 4, /*mystery_test_001,*/ wk->chrbase);
  MysteryLib_WinInit3(&wk->talkwin, MYSTERYLIB_WINTYPE_TALK, FONT_TALK);
  // �u�|�P���������W���[����́@���������݂�\n�������Ă��܂��v
  MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_005);
  wk->chrbase += MysteryLib_GetWindowChr(&wk->talkwin);

  // ��ʏ�̃^�C�g���\��
  MysteryLib_WinInit1(&wk->titlewin, &wk->ewin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
  MysteryLib_WinInit2(&wk->titlewin, 30, 4, /*mystery_01_012,*/ wk->chrbase);
  MysteryLib_WinInit3(&wk->titlewin, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  MysteryLib_CreateWin(wk->bgl, &wk->titlewin, 1, 1, mystery_01_012);
  wk->chrbase += MysteryLib_GetWindowChr(&wk->titlewin);

  // �A�N�^�[������
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_cur_00_lz_ccgr,
		       NARC_mystery_fusigi_cur_nclr,
		       NARC_mystery_fusigi_cur_00_lz_ccer,
		       NARC_mystery_fusigi_cur_00_lz_canr,
		       GF_BGL_MAIN_DISP);
  // ���A�C�R����o�^
  wk->arrow = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->arrow, HW_LCD_WIDTH/2, 76, 1);
  
  DisplayRangerStatus(wk);
}


//------------------------------------------------------------------
/**
 * @brief	�����W���[�ɑ���������������ɂ��\��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DisplayRangerStatus(POKEMONRANGER_WORK *wk)
{
  u32 high, low, width, wsize;
  u8 mac_addr[6];
  MpMACAddData mac_data;
  WORDSET *word;

  word = WORDSET_Create(wk->heapid);

  MysteryLib_WinInit1(&wk->statwin, &wk->swin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
  MysteryLib_WinInit2(&wk->statwin, 26, 4, wk->chrbase);
  MysteryLib_WinInit3(&wk->statwin, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  //  wk->chrbase += MysteryLib_GetWindowChr(&wk->statwin);
  wk->statwin.word = word;

  // ���O��ݒ�
  WORDSET_RegisterPlayerName(word, 0, wk->mst);
  // IDNo.��ݒ�
  WORDSET_RegisterNumber(word, 1, MyStatus_GetID_Low(wk->mst), 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, 3, 13, mystery_ranger_001);

  // �u���������݃i���o�[�v�\��
  wk->statwin.redrawflag = FALSE;
  MysteryLib_WinSetPos(&wk->statwin, 0, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SIZE_Y));
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, -1, -1, mystery_ranger_003);
  // ���������݃i���o�[���E�l�ŕ\��
  OS_GetMacAddress(mac_addr);
  mac_data = MpMACAddArrayToMACAddData(mac_addr);
  MpMACAddressToConnectCode(mac_data.u.data32, &high, &low);
  WORDSET_RegisterNumber(word, 0, high, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(word, 1, low,  4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  wk->statwin.rightflag = TRUE;
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, -1, -1, mystery_ranger_004);
  
  WORDSET_Delete(word);
}


//------------------------------------------------------------------
/**
 * @brief	���p���������������J��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerFinish(PROC *proc)
{
  int i;
  POKEMONRANGER_WORK *wk = PROC_GetWork(proc);

  // �Z���A�N�^�[���폜
  MysteryLib_RemoveClact();
  
  // �E�B���h�E�J��
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == TRUE){
    GF_BGL_BmpWinOff(&wk->ewin); GF_BGL_BmpWinDel(&wk->ewin);
    GF_BGL_BmpWinOff(&wk->twin); GF_BGL_BmpWinDel(&wk->twin);
    GF_BGL_BmpWinOff(&wk->swin); GF_BGL_BmpWinDel(&wk->swin);
  }
  // BGL�J��
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_S);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_S);
  sys_FreeMemoryEz(wk->bgl);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�V�[�P���X�쓮�ɕK�v�ȃ��[�N�G���A������
 * @param	wk	�ʐM�֌W���[�N�ւ̃|�C���^
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT PokemonRangerProc_Init(PROC * proc, int * seq)
{
  POKEMONRANGER_WORK *wk;

  wk = MysteryLib_InitProc(proc, HEAPID_POKEMONRANGER, sizeof(POKEMONRANGER_WORK), 0x20000);
  // �e��ϐ��̏�����
  wk->heapid = HEAPID_POKEMONRANGER;
  wk->bgl = GF_BGL_BglIniAlloc(wk->heapid);
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->zw = SaveData_GetZukanWork(wk->sv);
  wk->cfg = SaveData_GetConfig(wk->sv);
  // ���C�u����������
  MysteryLib_Init(wk->heapid);
  // �ӂ����f�[�^�̃|�C���^�𓾂�
  wk->fdata = SaveData_GetFushigiData(wk->sv);
  
  // �ϐ�������
  wk->beacon_seq = POKEMONRANGER_SEQ_BEACON_WAIT;
  wk->chrbase =POKEMONRANGER_WCHR;
  wk->beacon_check_time = 0;
  wk->seq = POKEMONRANGER_COMM_INIT;
  wk->doproc = FALSE;

  // �ʐM�A�C�R����\�����邽�߂̃q�[�v�m��
  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  
  /* �T�E���h�f�[�^���[�h */
  Snd_DataSetByScene( SND_SCENE_AGB, SEQ_PRESENT, 1 );

  return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�̃��C������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static PROC_RESULT PokemonRangerProc_Main(PROC * proc, int * seq)
{
  POKEMONRANGER_WORK *wk = PROC_GetWork(proc);
  
  switch(*seq){
  case POKEMONRANGER_SEQ_INIT:
    PokemonRangerInitScreen(wk);
    // ������������Ă��Ȃ���Όx����\�����ă^�C�g���֖߂�
    if(ZukanWork_GetZukanGetFlag(wk->zw) == FALSE)
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_DISP_ERROR,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    else
      *seq = POKEMONRANGER_SEQ_INIT_SCREEN;
    break;

  case POKEMONRANGER_SEQ_DISP_ERROR:
    // �N���ɃG���[������Ε\�����ďI��
    if(PokemonRangerNoHaveZukan(wk) == FALSE){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH, seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;
    
  case POKEMONRANGER_SEQ_INIT_SCREEN:
    // �ŏ��̉�ʂ�\��
    PokemonRangerCreateScreen(wk);

#if 0
    if(FUSHIGIDATA_CheckCardDataSpace(wk->fdata) == FALSE){
      // �J�[�h�̈悪�����ς��̏ꍇ�͌x����\�����ďI��
      wk->talkwin.msgspd = 1;
      wk->warning_msg = MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_err_005);
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_FULL_WARNING,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else
#endif
      if(FUSHIGIDATA_CheckDeliDataSpace(wk->fdata) == FALSE){
      // �z�B���������ς��̏ꍇ�͌x����\�����ďI��
      wk->talkwin.msgspd = 1;
      wk->warning_msg = MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_err_001);
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_FULL_WARNING,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else {
      // �r�[�R�������J�n
      wk->beacon_seq = POKEMONRANGER_SEQ_BEACON_INIT;
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_MAIN,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;

  case POKEMONRANGER_SEQ_FULL_WARNING:
    // �x����ʕ\��
    if(GF_MSG_PrintEndCheck(wk->warning_msg) == 0 && sys.trg & PAD_BUTTON_DECIDE){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;
    
  case POKEMONRANGER_SEQ_MAIN:
    // �����ŒʐM�̃��C���������s��
    wk->beacon_ret = CheckPokemonRangerBeacon(wk);
    // �I�����邩�A�L�����Z�������܂ő҂�
    if(wk->beacon_ret == POKEMONRANGER_RET_CANCEL){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else if(wk->beacon_ret == POKEMONRANGER_RET_SUCCESS){
#if 0
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_DISP_CARD_INIT, seq, POKEMONRANGER_SEQ_FADE_WAIT);
#else
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
#endif
    }
    break;

  case POKEMONRANGER_SEQ_DISP_CARD_INIT:
    // ����ʂ͊i�q�͗l�𕜊�
    PokemonRangerInitSubScreen(wk);
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
    // ���ʂ̓J�[�h���̕\��
    MysteryCard_DisplayCardOnly(wk->bgl, &wk->gc, HEAPID_POKEMONRANGER);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_DISP_CARD, seq, POKEMONRANGER_SEQ_FADE_WAIT);
    wk->gc.beacon.have_card = 0;
    break;

  case POKEMONRANGER_SEQ_DISP_CARD:
    if(sys.trg)
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_RESET,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    break;

  case POKEMONRANGER_SEQ_RESET:
    // �����΍����̎���ɂ��\�t�g�E�F�A���Z�b�g
    OS_ResetSystem(0); 
    break;

  case POKEMONRANGER_SEQ_FINISH:
    // ��n�����ă^�C�g���֖߂�
    PokemonRangerFinish(proc);
    return PROC_RES_FINISH;
    break;
    
  case POKEMONRANGER_SEQ_FADE_WAIT:
    // �t�F�[�h���I������܂ő҂��Ď��̃V�[�P���X��
    MysteryLib_FadeEndCheck(seq);
    break;
  }

  // �A�C�R����\�����邽�߂ɕK�v�ȋ쓮����
  MysteryLib_DoClact();

  return PROC_RES_CONTINUE;
}
//#include "demo/title.h"
FS_EXTERN_OVERLAY( title );
static PROC_RESULT PokemonRangerProc_End(PROC * proc, int * seq)
{
  sys_DeleteHeap(HEAPID_COMMICON);
  Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_POKEMONRANGER);

  OS_TPrintf("�I�����܂���\n");

  return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	�|�P���������W���[�̃Z�[�u�f�[�^���쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreatePokemonRangerSaveData(POKEMONRANGER_WORK *wk)
{
  RTCDate date;
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
#if 0
  GIFT_CARD *gc = sys_AllocMemory(wk->heapid, sizeof(GIFT_CARD));
#else
  GIFT_CARD *gc = &wk->gc;
#endif
  MI_CpuClear8(gc, sizeof(GIFT_CARD));

  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, wk->heapid);
  word = WORDSET_Create(wk->heapid);

  // �J�[�h�̃f�[�^���쐬����
  gc->gift_type = MYSTERYGIFT_TYPE_RANGEREGG;	// ��������̃^�C�v�́u�}�i�t�B�̂��܂��v
  
  // �J�[�h�^�C�g���̐ݒ�
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_ranger_011, wk->heapid);
  STRBUF_GetStringCode((const STRBUF *)msg, gc->beacon.event_name, GIFT_DATA_CARD_TITLE_MAX);
  STRBUF_Delete(msg);

  gc->beacon.version = (			// �Ώۃo�[�W����
			MysteryLib_GetCasetteCode(VERSION_DIAMOND) |
			MysteryLib_GetCasetteCode(VERSION_PEARL) |
			MysteryLib_GetCasetteCode(VERSION_DP_NEXT));
  gc->beacon.event_id = MYSTERYGIFT_MANAFIEGG;	// �}�i�t�B�̂��܂��͂P��
  gc->beacon.only_one_flag = 0;			// �P�x�����z�M�t���O(���x�ł��󂯎���)
  gc->beacon.access_point = 0;			// �A�N�Z�X�|�C���g(����)
  gc->beacon.have_card = 1;			// �J�[�h�����܂�ł���
  gc->beacon.delivery_flag = 1;			// �z�B������󂯎����̂��܂�ł���
  gc->beacon.groundchild_flag = 0;		// ���z�z�ł͂Ȃ�
  
  // �C�x���g�e�L�X�g�̕�����̐ݒ�
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_ranger_010, wk->heapid);
  STRBUF_GetStringCode((const STRBUF *)msg, gc->event_text, GIFT_DATA_CARD_TEXT_MAX);
  STRBUF_Delete(msg);

  gc->re_deal_count = 0;			// �Ĕz�z�̉�(�Ĕz�z�͏o���Ȃ�)
  gc->pokemon_icon[0] = MONSNO_MANAFI;		// �|�P�����A�C�R��(�}�i�t�B)
  gc->pokemon_icon[1] = 0;			// �|�P�����A�C�R��(�Ȃ�)
  gc->pokemon_icon[2] = 0;			// �|�P�����A�C�R��(�Ȃ�)
  gc->re_dealed_count = 0;			// �z�z������
  GF_RTC_GetDate(&date);
  gc->recv_date = RTC_ConvertDateToDay(&date);	// �Z�[�u������t������

  WORDSET_Delete(word);
  MSGMAN_Delete(msgman);
			
  // �Z�[�u�̈�ɓo�^(���O�ɋ󂫗̈���`�F�b�N���Ă�̂Ő�΂ɑ��v)
#if 0
  FUSHIGIDATA_SetCardData(wk->fdata, gc);
#else
  FUSHIGIDATA_SetDeliData(wk->fdata, &gc->gift_type, 0);
#endif
#if 1
  // �����ŉ���ʂ̍X�V(�󂯎��A�j���[�V�����ǉ�)
  GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
  MysteryLib_InitGift(wk->bgl, (GIFT_DELIVERY *)gc);
#endif
#if 0
  // ��n��
  sys_FreeMemoryEz(gc);
#endif
}


//------------------------------------------------------------------
/**
 * @brief	�^�C���A�E�g�ݒ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerSetTimeOut(POKEMONRANGER_WORK *wk, int time)
{
  wk->mp_time_out = time;
}


//------------------------------------------------------------------
/**
 * @brief	�^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int PokemonRangerCheckConnect(POKEMONRANGER_WORK *wk, int *seq, int flag, u32 key)
{
  // �^�C���A�E�g����
  if(--wk->mp_time_out == 0){
    MpRequestClose();
    *seq = POKEMONRANGER_COMM_TIMEOUT;
    return 0;
  }
  if(flag){
    // �ʐM�ؒf�`�F�b�N
    if(!MpIsConnect()){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      return 0;
    }
  }
  // �L�����Z���`�F�b�N
  if(key && sys.trg & key){
    MpRequestClose();
    *seq = POKEMONRANGER_COMM_RETURN_TITLE;
    return 1;
  }
  return 0;
}



//--------------------------------------------------------------------------------------------
/**
 * �|�P���������W���[�Ƃ̒ʐM�V�[�P���X
 * �����̏�����src/system/startmenu.c����Ăяo����܂�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int CheckPokemonRangerBeacon(POKEMONRANGER_WORK *wk)
{
  int num, v1;
  u16 *p1;
  int *seq = &wk->seq;

  // ���C�u�����̏��������I������܂ł�MpProc���Ăяo���Ȃ�
  if(wk->doproc == TRUE){
    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - MpGetConnectLinkLevel());
    // ���C�������쓮
    MpProc();
    // �g�p����|�[�g�ԍ��ݒ�
    MpSetChannel(POKEMONRANGER_CONNECT_CH);
  }

  //  MIT_PRINTF("seq = %d %s\n", *seq, vtable[*seq]);

  switch(*seq){
  case POKEMONRANGER_COMM_INIT:
    /// VRAMD�ɃC�N�j���[����������
    PokemonRangerInitConnectData(wk);
    CommVRAMDInitialize();
    wk->commvramload = TRUE;
    *seq = POKEMONRANGER_COMM_IDLE;
    break;

  case POKEMONRANGER_COMM_IDLE:
    /// VRAMD�փC�N�j���[����������̂�҂�
    if(CommIsVRAMDInitialize()){
      // �ʐM������
      MpInit(&init_desc, wk->mp_buf);
      // ����ȍ~��MpProc���Ăяo����OK
      wk->doproc = TRUE;
      // �ʐM�A�C�R���\��
      WirelessIconEasy();
      *seq = POKEMONRANGER_COMM_CHECK_PARENT_INIT;
    }
    break;

  case POKEMONRANGER_COMM_CHECK_PARENT_INIT:
    // �q�@�Ƃ��ĒʐM�J�n
    MpRequestScan();
    // �^�C���A�E�g��1600�t���[��
    PokemonRangerSetTimeOut(wk, 1600);
    wk->time_icon = TimeWaitIconAdd(&wk->twin, POKEMONRANGER_TWCHR);
    *seq = POKEMONRANGER_COMM_CHECK_PARENT;
    break;

  case POKEMONRANGER_COMM_CHECK_PARENT:
    // �e�@�i�����W���[�j�����҂�
    num = MpGetConnectListNum();
    if (num) {
      // �|�P���������W���[�𔭌������I
      wk->connect_num = num - 1;
      // �^�C���A�E�g�ݒ�
      PokemonRangerSetTimeOut(wk, 1800);
      *seq = POKEMONRANGER_COMM_CONNECT_WAIT_PARENT;
    }
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);

    break;

    // ����������ڑ�����
    
  case POKEMONRANGER_COMM_CONNECT_WAIT_PARENT:
    // �e�@�i�����W���[�j�̐ڑ��\�҂�
    if (MpGetConnectParentEnable(wk->connect_num)) {
      // �ڑ��v��
      MpConnectParent(wk->connect_num);
      *seq = POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT;
      wk->mp_time_out = 1800;
    }
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT:
    // �e�@�i�����W���[�j�̐ڑ��҂�

    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);

    // �ڑ��ł�����POKEMONRANGER_COMM_SELECT_WAIT_PARENT
    if (MpIsConnect()) {
      *seq = POKEMONRANGER_COMM_SELECT_WAIT_PARENT;
    }    
    break;

  case POKEMONRANGER_COMM_SELECT_WAIT_PARENT:
    // �����W���[�i�e�@�j�ƃf�[�^�ʐM���邩�ǂ����̑I��
    // �|�P���������W���[�֐ڑ�������
    MpSetSendRedy();
    *seq = POKEMONRANGER_COMM_FIND_PARENT;
    wk->mp_time_out = 1800;
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_FIND_PARENT:
    // �f�[�^���M�v���ʐM�I���H
    if (MpIsSendDataEnd()) {
      // ������̃��[�U�[�f�[�^���M
      MpSetSendUserData();
      *seq = POKEMONRANGER_COMM_SEND_USERDATA_WAIT;
      wk->mp_time_out = 3200;
      // �u�|�P���������W���[�́@���߂��\n�^�b�`�@���Ă�������
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_test_006);
      // ���A�C�R�����ꎞ�I�ɏ���
      CLACT_SetDrawFlag(wk->arrow, 0);
      TimeWaitIconDel(wk->time_icon);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      wk->time_icon = NULL;

      return POKEMONRANGER_RET_FOUNDRANGER;
    }    
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;


    // ����ȍ~�̓��C���V�[�P���X��
    
  case POKEMONRANGER_COMM_SEND_USERDATA_WAIT:
    // ���M�I���ō���̓����W���[����̃f�[�^���󂯎��
    if (MpIsSendDataEnd()) {
      // �u�|�P���������W���[��\n�Ă񂻂����@�܂��Ă��܂��v
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_006);
      // ���A�C�R����\��
      CLACT_SetDrawFlag(wk->arrow, 1);

      DisplayRangerStatus(wk);
      *seq = POKEMONRANGER_COMM_RECV_PARENT_INIT;
    }
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;
      
  case POKEMONRANGER_COMM_RECV_PARENT_INIT:
    // �e�@�i�����W���[�j����̃f�[�^��M�J�n
    MpSetRecvData(ModeDptestRecvData, 42, 1);
    *seq = POKEMONRANGER_COMM_RECV_PARENT;
    wk->mp_time_out = 3200;
    break;

  case POKEMONRANGER_COMM_RECV_PARENT:
    // �f�[�^�̎�M�I���܂ő҂�
    if (MpIsRecvDataEnd()) {
      *seq = POKEMONRANGER_COMM_RECV_SUCCESS;
      wk->mp_time_out = 60;
      // �u�^�}�S�́@���サ��Ɂ@���������@���܂����v
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_006);
    }
    // �^�C���A�E�g�A�ʐM�ؒf�A�L�����Z������
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_RECV_SUCCESS:
    if(--wk->mp_time_out == 0){
      // �Z�[�u�J�n
      // �u���|�[�g���@�����Ă��܂��@���΂炭�@���܂��@���������v
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_007);
      wk->time_icon = TimeWaitIconAdd(&wk->twin, POKEMONRANGER_TWCHR);

      // �Z�[�u�f�[�^���쐬
      CreatePokemonRangerSaveData(wk);
      // �Z�[�u�����J�n
      MysteryLib_InitSaveDSCard(wk->sv);

      *seq = POKEMONRANGER_COMM_SAVE_WAIT;
    }
    break;

  case POKEMONRANGER_COMM_SAVE_WAIT:
    // �Z�[�u�I���҂�
    if(MysteryLib_SaveDSCard() == SAVE_RESULT_LAST){
      *seq = POKEMONRANGER_COMM_SAVE_DUMMY_WAIT;
      wk->mp_time_out = 6 + (OS_GetTickLo() % 54);
    }
    break;

  case POKEMONRANGER_COMM_SAVE_DUMMY_WAIT:
    // �����W���[�i�e�@�j�ɓ����҂����O�̃_�~�[�҂�
    if (--wk->mp_time_out == 0) {
      *seq = POKEMONRANGER_COMM_SAVE_SYNC;
    }
    break;

  case POKEMONRANGER_COMM_SAVE_SYNC:
    // �����W���[�i�e�@�j�ɓ����p�f�[�^���M�J�n
    // �����̂��߂Ƀf�[�^���M
    MpSetRecvData(ModeDptestRecvData, 42, 2);
    *seq = POKEMONRANGER_COMM_SAVE_SYNC_WAIT;
    wk->mp_time_out = 1200;
    break;

  case POKEMONRANGER_COMM_SAVE_SYNC_WAIT:
    // �f�[�^���M�I���ōŌ�̃Z�[�u
    if(MpIsRecvDataAcknowledge()) {
      // �Ō�̂P�Z�N�^���Z�[�u����
#if 0
      MysteryLib_SaveDSCard();
#else
      MysteryLib_DoLastSave();
#endif
      
      *seq = POKEMONRANGER_COMM_SAVE_SYNC_END;
      wk->mp_time_out = 800;
      break;
    }
    // ��莞�Ԃ��o�߂��Ă��ʐM���o���Ȃ�����
    if(--wk->mp_time_out == 0){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_TIMEOUT;
      wk->mp_time_out = 120;
    }
    // �ڑ����؂ꂽ��
    if (!MpIsConnect()) {
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      wk->mp_time_out = 120;
    }
    break;
      
  case POKEMONRANGER_COMM_SAVE_SYNC_END:
    // �Z�[�u�̏I�����m�F���A�f�[�^���M�I����҂�
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      wk->mp_time_out = 120;
    } else if(MysteryLib_GetSaveStatus() != MYSTERYLIB_SEQ_SAVE_OK){
      MysteryLib_SaveDSCard();
    } else {
      if(MpIsRecvDataEnd() || (!MpIsConnect())){
	*seq = POKEMONRANGER_COMM_RECV_END_WAIT;
	wk->mp_time_out = 1 /*120*/;
	MpRequestClose();
	break;
      }
    }
    // ��莞�Ԃ��o�߂��Ă��ʐM���o���Ȃ�����
    if(--wk->mp_time_out == 0){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_TIMEOUT;
      wk->mp_time_out = 10;
    }
      
  case POKEMONRANGER_COMM_RECV_END_WAIT:
    // �����W���[�i�e�@�j�ɓ����҂���
    if (--wk->mp_time_out == 0) {
      *seq = POKEMONRANGER_COMM_RECV_END;
      // �u�Ă񂻂����@���イ��傤�@���܂���\n�`�{�^���Ł@�ł񂰂���@����܂��v
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_008);
      // ���A�C�R���̕\�����~�߂�
      CLACT_SetDrawFlag(wk->arrow, 0);
      TimeWaitIconDel(wk->time_icon);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      wk->time_icon = NULL;
    }
    break;
      
  case POKEMONRANGER_COMM_RECV_END:
    // �����W���[�i�e�@�j����̎�M�^�^�}�S���Z�[�u�I��
    if (MpIsEnd()) {
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
	wk->commvramload = FALSE;
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	*seq = POKEMONRANGER_COMM_LOOP;
	return POKEMONRANGER_RET_SUCCESS;
      }
    }
    break;

    
  case POKEMONRANGER_COMM_DISCONNECT_PARENT:
    // �^�C���A�E�g���ʐM�ؒf�������𓯂��ɂ��܂�
    *seq = POKEMONRANGER_COMM_TIMEOUT;
  case POKEMONRANGER_COMM_TIMEOUT:
    // �����W���[�Ƃ̒ʐM���^�C���A�E�g
    // �u�|�P���������W���[�Ƃ́@�����񂪁@������@����܂����v
    MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_009);
    // ���A�C�R���̕\�����~�߂�
    CLACT_SetDrawFlag(wk->arrow, 0);
    if(wk->time_icon)
      TimeWaitIconDel(wk->time_icon);
    wk->time_icon = NULL;
    *seq = POKEMONRANGER_COMM_RESET;
    break;

  case POKEMONRANGER_COMM_RESET:
    // �ʐM���I�������ă��Z�b�g����
    if (MpIsEnd()){
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
	wk->commvramload = FALSE;
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	OS_ResetSystem(0); 
      }
    }      
    break;

  case POKEMONRANGER_COMM_RETURN_TITLE:
    // �ʐM���I�������ă^�C�g���֖߂�
    if (MpIsEnd()){
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
	wk->commvramload = FALSE;
	if(wk->time_icon)
	  TimeWaitIconDel(wk->time_icon);
	return POKEMONRANGER_RET_CANCEL;
      }
    }      
    break;

    
  case POKEMONRANGER_COMM_LOOP:
    break;
    
  }
  return POKEMONRANGER_RET_NONE;
}

#if 0
//--------------------------------------------------------------------------------------------
/**
 * �|�P���������W���[�Ƃ̒ʐM�V�[�P���X���I��������
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int DisablePokemonRangerBeacon(POKEMONRANGER_WORK *wk)
{
  if(wk->disable == TRUE){
    MpRequestClose();
    wk->disable = FALSE;
  } else {
    if (MpIsEnd()) {
      /// VRAMD�̃C�N�j���[�������̂Ă�
      CommVRAMDFinalize();
      wk->doproc = FALSE;
      WirelessIconEasyEnd(); // �ʐM�A�C�R���폜
      return TRUE;
    }
  }
  return FALSE;
}
#endif

const PROC_DATA PokemonRangerProcData = {
  PokemonRangerProc_Init,
  PokemonRangerProc_Main,
  PokemonRangerProc_End,
  NO_OVERLAY_ID,
};



/*  */
