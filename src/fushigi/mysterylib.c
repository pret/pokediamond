//============================================================================================
/**
 * @file	mysterylib.c	
 * @bfief	�ӂ����ȁ@��������̂Ŏg���郉�C�u�������ǂ�
 * @author	Satoshi Mitsuhara
 * @date	06.06.12
 *
 * $Id: mysterylib.c,v 1.41 2006/08/10 09:56:15 mitsuhara Exp $
 */
//============================================================================================
#include "common.h"
#include "system/main.h"
#include "system/procsys.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "system/msgdata_util.h"
#include "system/window.h"
#include "system/render_oam.h"

#include "system/gra_tool.h"
#include "system/snd_tool.h"

#include "poketool/monsno.h"
#include "itemtool/item.h"
#include "itemtool/itemsym.h"

#include "gflib/bg_system.h"
#include "gflib/char_manager.h"

#include "savedata/fushigi_data.h"

#include "mysterylib.h"
#include "mystery.naix"
#include "../application/tradelist/tradelist.naix"

#include "nitrocrypto/crypto.h"
#include "communication/communication.h"
#include "communication/comm_mp.h"


#define STACK_SIZE		1024

typedef struct {
  BOOL init_flag;

  int heapid;
  int next_seq;
  int fade_type;

  int save_seq;
  SAVEDATA *sv;
  void *time_icon;
  int icon_base;
  
  BOOL init_clact_flag[4];
  // ���o�p�Z���A�N�^�[
  MYSTERY_CLACT clact;
  CLACT_WORK_PTR giftact;
  int giftact_wait;
  fx32 sub_add;
  
  u8 PokeGra[0x20*10*10];
  SOFT_SPRITE_ARC PokeGraSsa;

  void (*vfunc)(void *);
  
} MYSTERYLIB_WORK;


#define	MYSTERYLIB_BLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 15))
#define	MYSTERYLIB_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))
#define	MYSTERYLIB_BLUE		(GF_PRINTCOLOR_MAKE(7, 8, 15))
#define MYSTERYLIB_CLRCODE	15

#define MYSTERYLIB_NOMSG	-1

#define SUBSURFACEX		(  0*FX32_ONE)
#define SUBSURFACEY		(256*FX32_ONE)


static MYSTERYLIB_WORK MysteryLibWork;

#define GetMysteryLibWorkPtr()	&MysteryLibWork

static void MysteryLib_VBlankFunc(void *work);

//------------------------------------------------------------------
/**
 * @brief	�ӂ����ȁ@��������̃��C�u����������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_Init(int heapid)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  //  if(wk->init_flag == TRUE)	return;

  memset(wk, 0, sizeof(MYSTERYLIB_WORK));
  wk->init_flag = TRUE;
  wk->heapid = heapid;
}


//------------------------------------------------------------------
/**
 * @brief	PROC���������܂Ƃ߂��֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void *MysteryLib_InitProc(PROC *proc, int heapid, int size, int heapsize)
{
  void *wk;

  sys_CreateHeap(HEAPID_BASE_APP, heapid, heapsize);
  sys_PrintHeapFreeSize(heapid);
  wk = PROC_AllocWork(proc, size, heapid);
  // �������s�ǂ��|���̂Ń��[�N�̓[���N���A
  memset(wk, 0, size);
  /* ��ʂ̏����ݒ� */
  WIPE_SetBrightness(WIPE_DISP_MAIN, WIPE_FADE_BLACK);
  WIPE_SetBrightness(WIPE_DISP_SUB,  WIPE_FADE_BLACK);
  return wk;
}


//------------------------------------------------------------------
/**
 * @brief	�a�f�������֐�(�P�t���[���̂�)
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_BgInitFrame(GF_BGL_INI *ini, int frame, u8 size, u32 scrbase, u32 scrchar)
{
  GF_BGL_BGCNT_HEADER MBg_Data = {
    0, 0, 0x800, 0,
    GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
    GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000,
    GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
  };
  MBg_Data.screenSize = size;
  switch(size){
  case GF_BGL_SCRSIZ_256x256: MBg_Data.scrbufferSiz = 0x0800; break;
  case GF_BGL_SCRSIZ_256x512: MBg_Data.scrbufferSiz = 0x1000; break;
  case GF_BGL_SCRSIZ_512x256: MBg_Data.scrbufferSiz = 0x1000; break;
  case GF_BGL_SCRSIZ_512x512: MBg_Data.scrbufferSiz = 0x2000; break;
  }
  MBg_Data.screenBase = scrbase / 0x0800;
  MBg_Data.charBase = scrchar / 0x4000;
  GF_BGL_BGControlSet(ini, frame, &MBg_Data, GF_BGL_MODE_TEXT );
  GF_BGL_ScrClear(ini, frame);
}


//------------------------------------------------------------------
/**
 * @brief	�t�F�[�h�̃^�C�v�ύX
 * @param	0: BLACK  1: WHITE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_ChangeFadeType(int type)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  wk->fade_type = type;
}

//------------------------------------------------------------------
/**
 * @brief	�t�F�[�h�֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_RequestFade(int type, int next_seq, int *seq, int next)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  if(wk->fade_type == 0)
    WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC, wk->heapid);
  else
    WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_WHITE,WIPE_DEF_DIV,WIPE_DEF_SYNC, wk->heapid);
  if(seq)
    *seq = next;
  wk->next_seq = next_seq;
}


//------------------------------------------------------------------
/**
 * @brief	�t�F�[�h�I���֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_FadeEndCheck(int *seq)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  if(WIPE_SYS_EndCheck()){
    *seq = wk->next_seq;
  }
}


//------------------------------------------------------------------
/**
 * @brief	MYSTERY_WIN�\���̂̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_WinInit1(MYSTERY_WIN *mw, GF_BGL_BMPWIN *win, int palno, int arc, int fchr, int fcol)
{
  // ��x�ݒ肵���炠�܂�ύX�̂Ȃ����̂��ŏ��ɐݒ�
  memset(mw, 0, sizeof(MYSTERY_WIN));
  mw->drawflag = TRUE;
  mw->redrawflag = TRUE;
  mw->msgid = MYSTERYLIB_NOMSG;
  mw->win = win;
  mw->palno = palno;
  mw->arcno = arc;
  mw->fchr = fchr;
  mw->fcol = fcol;
  mw->screen = GF_BGL_FRAME0_M;
  mw->font = FONT_SYSTEM;
  mw->color = MYSTERYLIB_BLACK;
  mw->clrcolor = MYSTERYLIB_CLRCODE;
  mw->winmode = MYSTERYLIB_WINTYPE_NORMAL;
  mw->dx = mw->dy = 0;
  mw->word = NULL;
  mw->msgspd = MSG_NO_PUT;
}
void MysteryLib_WinInit2(MYSTERY_WIN *mw, int w, int h,/* int msgid,*/ int base)
{
  // �E�B���h�E�𐶐����邽�тɕύX�����肻���Ȃ���
  mw->width = w;
  mw->height = h;
  mw->base = base;
}
void MysteryLib_WinInit3(MYSTERY_WIN *mw, int type, int font)
{
  mw->winmode = type;
  mw->font = font;
}
void MysteryLib_WinSetColor(MYSTERY_WIN *mw, int color)
{
  if(color != MYSTERYLIB_COLOR_NULL){
    switch(color){
    case MYSTERYLIB_COLOR_WHITE: mw->color = MYSTERYLIB_WHITE; break;
    case MYSTERYLIB_COLOR_BLACK: mw->color = MYSTERYLIB_BLACK; break;
    case MYSTERYLIB_COLOR_BLUE:  mw->color = MYSTERYLIB_BLUE;  break;
    }
  }
}
void MysteryLib_WinSetPos(MYSTERY_WIN *mw, int dx, int dy)
{
  mw->dx = dx;
  mw->dy = dy;
}
  
//------------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�E�B���h�E��o�^
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryLib_RedrawWin(MYSTERY_WIN *mw, int msgid)
{
  int midx;
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;

  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  // �E�B���h�E���N���A
  if(msgid != MYSTERYLIB_NOMSG && mw->msgid != msgid){
    mw->msgid = msgid;
    if(mw->redrawflag == TRUE)
      GF_BGL_BmpWinDataFill(mw->win, mw->clrcolor);
    if(mw->msgid != MYSTERYLIB_NOMSG){
      // �A�[�J�C�u����W�J���ĕ\��
      msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, mw->arcno, wk->heapid);
      if(mw->word == NULL)	word = WORDSET_Create(wk->heapid);
      else			word = mw->word;
      msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mw->msgid, wk->heapid);
      if(mw->rightflag == FALSE){
	midx = GF_STR_PrintColor(mw->win, mw->font, msg, mw->dx, mw->dy, mw->msgspd, mw->color, NULL);
      } else {
	// �E�񂹂��ĕ\��
	int width, wsize;
	width = FontProc_GetPrintStrWidth(mw->font, msg, FontHeaderGet(mw->font, FONT_HEADER_SPACE_X));
	wsize = GF_BGL_BmpWinGet_SizeX(mw->win) * 8 - width;
	midx = GF_STR_PrintColor(mw->win, mw->font, msg, wsize, mw->dy, mw->msgspd, mw->color, NULL);
	mw->rightflag = FALSE;
      }
      STRBUF_Delete(msg);
      if(mw->word == NULL)	WORDSET_Delete(word);
      MSGMAN_Delete(msgman);
    }
  }
  mw->msgspd = MSG_NO_PUT;
  return midx;
}
int MysteryLib_CreateWin(GF_BGL_INI *bgl, MYSTERY_WIN *mw, int sx, int sy, int msgid)
{
  int midx;
  if(mw->win->ini == NULL){
    GF_BGL_BmpWinAdd(bgl, mw->win, mw->screen, sx, sy, mw->width, mw->height, mw->palno, mw->base);
    midx = MysteryLib_RedrawWin(mw, msgid);
  } else {
    // �\�����W��ύX����
    if(sx != -1)	GF_BGL_BmpWinSet_PosX(mw->win, sx);
    if(sy != -1)	GF_BGL_BmpWinSet_PosY(mw->win, sy);
    midx = MysteryLib_RedrawWin(mw, msgid);
  }
  // �]���t���O��TRUE�Ȃ�΂u�q�`�l�֓]������
  if(mw->drawflag == TRUE){
    if(mw->winmode == MYSTERYLIB_WINTYPE_NORMAL)
      BmpMenuWinWrite(mw->win, WINDOW_TRANS_ON, mw->fchr, mw->fcol);
    else
      BmpTalkWinWrite(mw->win, WINDOW_TRANS_ON, mw->fchr, mw->fcol);
  }
  return midx;
}

//------------------------------------------------------------------
/**
 * @brief	�E�B���h�E�������L�����N�^������Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
int MysteryLib_GetWindowChr(MYSTERY_WIN *mw)
{
  return mw->width * mw->height;
}

//------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	�L�����N�^�A�p���b�g�}�l�[�W���[������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_InitCPManager(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  CHAR_MANAGER_MAKE cm = {
    MYSTERYLIB_CHAR_CONT_NUM,
    MYSTERYLIB_CHAR_VRAMTRANS_MAIN_SIZE,
    MYSTERYLIB_CHAR_VRAMTRANS_SUB_SIZE,
    NULL,
  };

  // �L�����N�^�}�l�[�W���[������
  cm.heap = wk->heapid;
  InitCharManager(&cm);

  // �p���b�g�}�l�[�W���[������
  InitPlttManager(MYSTERYLIB_PLTT_CONT_NUM, wk->heapid);
      
  // �ǂݍ��݊J�n�ʒu��������
  CharLoadStartAll();
  PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�V�X�e��������������Ă邩�Ԃ�
 * @param	NONE
 * @return	TRUE: �������ς݁@FALSE:���������ĂȂ�
 */
//------------------------------------------------------------------
BOOL MysteryLib_isInitClact(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  return !!wk->clact.clactSet;
}

//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�V�X�e���̏�����
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_InitClactSystem(void)
{
  int i;
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  // OAM�}�l�[�W���[�̏�����
  NNS_G2dInitOamManagerModule();
  // ���LOAM�}�l�[�W���쐬
  // �����_���pOAM�}�l�[�W���쐬
  // �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
  REND_OAMInit(0, 126,		// ���C�����OAM�Ǘ��̈�
	       0, 32,		// ���C����ʃA�t�B���Ǘ��̈�
	       0, 126,		// �T�u���OAM�Ǘ��̈�
	       0, 32,		// �T�u��ʃA�t�B���Ǘ��̈�
	       wk->heapid);
	
  // �Z���A�N�^�[������
  wk->clact.clactSet = CLACT_U_SetEasyInit( 70, &wk->clact.renddata, wk->heapid);
  CLACT_U_SetSubSurfaceMatrix(&wk->clact.renddata, 0, (256*FX32_ONE));

  wk->sub_add = SUB_SURFACE_Y;
  
  //���\�[�X�}�l�[�W���[������
  for(i = 0; i < CLACT_U_RES_MAX; i++){		//���\�[�X�}�l�[�W���[�쐬
    wk->clact.resMan[i] = CLACT_U_ResManagerInit(3, i, wk->heapid);
  }
}



//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[������
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_InitClact(int arcfile, int arcchar, int arcpal, int arccell, int arcanim, int screen)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  int hwscreen = screen == GF_BGL_MAIN_DISP ? NNS_G2D_VRAM_TYPE_2DMAIN : NNS_G2D_VRAM_TYPE_2DSUB;
  int comp;

  //  OS_TPrintf("%d, %d, %d, %d, %d, %d\n", arcfile, arcchar, arcpal, arccell, arcanim, screen);

  comp = 1;
  // ���߂�Ȃ����AITEMICON�����͓��ʈ���
  if(arcfile == ARC_ITEMICON)	comp = 0;
  
  //chara�ǂݍ���
  if(arcchar != -1){
    wk->clact.resObjTbl[screen][CLACT_U_CHAR_RES] =
      CLACT_U_ResManagerResAddArcChar(wk->clact.resMan[CLACT_U_CHAR_RES],
				      arcfile, arcchar, comp, screen, hwscreen, wk->heapid);
  }
  //pal�ǂݍ���
  if(arcpal != -1){
    wk->clact.resObjTbl[screen][CLACT_U_PLTT_RES] =
      CLACT_U_ResManagerResAddArcPltt(wk->clact.resMan[CLACT_U_PLTT_RES],
				      arcfile, arcpal, 0, screen, hwscreen, 3, wk->heapid);
  }
  //cell�ǂݍ���
  if(arccell != -1){
    wk->clact.resObjTbl[screen][CLACT_U_CELL_RES] =
      CLACT_U_ResManagerResAddArcKindCell(wk->clact.resMan[CLACT_U_CELL_RES],
					  arcfile, arccell, comp, screen, CLACT_U_CELL_RES,wk->heapid);
  }
  //�����֐���anim�ǂݍ���
  if(arcanim != -1){
    wk->clact.resObjTbl[screen][CLACT_U_CELLANM_RES] =
      CLACT_U_ResManagerResAddArcKindCell(wk->clact.resMan[CLACT_U_CELLANM_RES],
					  arcfile, arcanim, comp, screen, CLACT_U_CELLANM_RES,wk->heapid);
  }

  // Chara�]��
  CLACT_U_CharManagerSet(wk->clact.resObjTbl[screen][CLACT_U_CHAR_RES]);
  // �p���b�g�]��
  CLACT_U_PlttManagerSet(wk->clact.resObjTbl[screen][CLACT_U_PLTT_RES]);

  // �Z���A�N�^�[�w�b�_�쐬
  CLACT_U_MakeHeader(&wk->clact.clActHeader[screen], screen, screen, screen, screen,
		     CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
		     0, 0,
		     wk->clact.resMan[CLACT_U_CHAR_RES],
		     wk->clact.resMan[CLACT_U_PLTT_RES],
		     wk->clact.resMan[CLACT_U_CELL_RES],
		     wk->clact.resMan[CLACT_U_CELLANM_RES],
		     NULL,NULL);
  //�܂������]�����Ă��Ȃ�����
  if(screen == GF_BGL_MAIN_DISP)
    GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//���C�����OBJ�ʂn�m
  else
    GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON );	//�T�u���OBJ�ʂn�m

  sys_VBlankFuncChange(MysteryLib_VBlankFunc, NULL);
}


//------------------------------------------------------------------
/**
 * @brief	�T�u��ʂ̃T�[�t�F�C�X�ύX
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_SetSubSurfaceMatrix(fx32 x, fx32 y)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  CLACT_U_SetSubSurfaceMatrix(&wk->clact.renddata, x, y);
  wk->sub_add = y;
}


//------------------------------------------------------------------
/**
 * @brief	���t���[���Ăяo���ė~�����֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_DoClact(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

#if 1
  if(wk->giftact){
    VecFx32 *vec;
    if(wk->giftact_wait == 0){
      if(CLACT_GetDrawFlag(wk->giftact) == FALSE){
	CLACT_SetDrawFlag(wk->giftact, 1);
      }
      vec = (VecFx32 *)CLACT_GetMatrix(wk->giftact);
      if(vec->y < 384*FX32_ONE){
	vec->y += FX32_ONE * 3;
      }
    } else {
      wk->giftact_wait--;
    }
  }
#endif

  if(wk->clact.clactSet != NULL)
    CLACT_Draw(wk->clact.clactSet);
}


//------------------------------------------------------------------
/**
 * @brief	CLACT_ADD�̐��`���쐬
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
CLACT_WORK_PTR MysteryLib_MakeCLACT(int screen, CLACT_WORK_PTR anim, int sx, int sy, int anum)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  if(anim == NULL){
    CLACT_ADD add;
    add.ClActSet	= wk->clact.clactSet;
    add.ClActHeader	= &wk->clact.clActHeader[screen];
    add.mat.z		= 0;
    add.sca.x		= FX32_ONE;
    add.sca.y		= FX32_ONE;
    add.sca.z		= FX32_ONE;
    add.rot		= 0;
    add.mat.x		= FX32_ONE * sx;
    add.mat.y		= FX32_ONE * sy;
    add.pri		= 10;
    add.DrawArea	= screen == GF_BGL_MAIN_DISP ? NNS_G2D_VRAM_TYPE_2DMAIN : NNS_G2D_VRAM_TYPE_2DSUB;
    add.heap		= wk->heapid;
    if(add.DrawArea == NNS_G2D_VRAM_TYPE_2DSUB)
      add.mat.y += wk->sub_add;
    anim = CLACT_Add(&add);
  }

  //  OS_TPrintf("MakeCLACT: %d, %08X, %d, %d, %d\n", screen, anim, sx, sy, anum);

  CLACT_SetAnmFlag(anim, 1);
  CLACT_BGPriorityChg(anim, 0);
  CLACT_AnmChg(anim, anum);
  CLACT_SetDrawFlag(anim, 1);

  return anim;
}


//------------------------------------------------------------------
/**
 * @brief	�Z���A�N�^�[�̍폜
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_RemoveClact(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  MYSTERY_CLACT *act = &wk->clact;
  int i;

  // ���ꂾ�����ʂ�act�Ȃ̂ł����ŏ���
  if(wk->giftact){
    CLACT_Delete(wk->giftact);
    wk->giftact = NULL;
  }
  
  // �L�����]���}�l�[�W���[�j��
  if(act->resObjTbl[GF_BGL_MAIN_DISP][CLACT_U_CHAR_RES])
    CLACT_U_CharManagerDelete(act->resObjTbl[GF_BGL_MAIN_DISP][CLACT_U_CHAR_RES]);
  if(act->resObjTbl[GF_BGL_SUB_DISP ][CLACT_U_CHAR_RES])
    CLACT_U_CharManagerDelete(act->resObjTbl[GF_BGL_SUB_DISP ][CLACT_U_CHAR_RES]);
  // �p���b�g�]���}�l�[�W���[�j��
  if(act->resObjTbl[GF_BGL_MAIN_DISP][CLACT_U_PLTT_RES])
    CLACT_U_PlttManagerDelete(act->resObjTbl[GF_BGL_MAIN_DISP][CLACT_U_PLTT_RES]);
  if(act->resObjTbl[GF_BGL_SUB_DISP ][CLACT_U_PLTT_RES])
    CLACT_U_PlttManagerDelete(act->resObjTbl[GF_BGL_SUB_DISP ][CLACT_U_PLTT_RES]);

  // �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
  for(i = 0; i < CLACT_U_RES_MAX; i++){
    CLACT_U_ResManagerDelete(act->resMan[i]);
    act->resMan[i] = NULL;
  }

  // �Z���A�N�^�[�Z�b�g�j��
  CLACT_DestSet(act->clactSet);
  act->clactSet = NULL;
  //OAM�����_���[�j��
  REND_OAM_Delete();
  // ���\�[�X���
  DeleteCharManager();
  DeletePlttManager();

  sys_VBlankFuncChange( NULL, NULL );
}

//------------------------------------------------------------------
/**
 * @brief	�Q�[���J�Z�b�g�ɑΉ������r�b�g��Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u32 MysteryLib_GetCasetteCode(int cas)
{
  return (u32)1 << (cas - VERSION_DIAMOND);
}

//------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	VBLank Function
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryLib_VBlankFunc(void *work)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  if(wk->vfunc){
    wk->vfunc(wk);
    wk->vfunc = NULL;
  }
  // �Z���A�N�^�[Vram�]���}�l�[�W���[���s
  DoVramTransferManager();
  // �����_�����LOAM�}�l�[�W��Vram�]��
  REND_OAMTrans();	
  //  GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );

#if 0
  // �K�v�������Thread���������N����
  if(OS_IsThreadTerminated(&wk->thread) == FALSE)
    OS_WakeupThreadDirect(&wk->thread);
#endif
}


//------------------------------------------------------------------
/**
 * @brief	��������̂ɑΉ������p���b�g�ԍ���Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryLib_GetGiftPalno(int gift)
{
  int i;
  struct {
    u8 type, palno;
  } GiftPalno[] = {
    { MYSTERYGIFT_TYPE_NONE,		0 },
    { MYSTERYGIFT_TYPE_POKEMON,		1 },	// �|�P����
    { MYSTERYGIFT_TYPE_POKEEGG,		1 },	// �^�}�S
    { MYSTERYGIFT_TYPE_ITEM,		2 },	// �ǂ���
    { MYSTERYGIFT_TYPE_RULE,		3 },	// ���[��
    { MYSTERYGIFT_TYPE_GOODS,		2 },	// �O�b�Y
    { MYSTERYGIFT_TYPE_ACCESSORY,	2 },	// �A�N�Z�T��
    { MYSTERYGIFT_TYPE_RANGEREGG,	0 },	// �i�}�t�B�[�̃^�}�S
    { MYSTERYGIFT_TYPE_MEMBERSCARD,	5 },	// �����o�[�Y�J�[�h
    { MYSTERYGIFT_TYPE_LETTER,		5 },	// �I�[�L�h�̂Ă���
    { MYSTERYGIFT_TYPE_WHISTLE, 	5 },	// �Ă񂩂��̂ӂ�
    { MYSTERYGIFT_TYPE_POKETCH, 	4 },	// �|�P�b�`
    { -1 },
  };
  
  for(i = 0; GiftPalno[i].type != -1; i++)
    if(GiftPalno[i].type == gift)
      return GiftPalno[i].palno;
  return 0;
}


//------------------------------------------------------------------
/**
 * @brief	�w��̃|�P�����O���t�B�b�N�X�����[�h
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define POKEGRA_VRAM_OFFSET  ( 0 )
#define POKEGRA_VRAM_SIZE     ( 0x20*10*10 )
static void MysteryLib_LoadPokeGra(POKEMON_PARAM *pp, int mons_no, int form_no, u8 *char_work, SOFT_SPRITE_ARC *ssa)
{
  int sex, col;
  u32 rnd;
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�t�H�����ԍ��� %d �ł�\n", form_no);
#endif
  
  // �|�P�����̉摜��ǂݍ��ށi�������\�t�g�E�F�A�X�v���C�g�p�̃e�N�X�`����ԁj
  sex = PokeSexGet(pp);
  col = PokeRareGet(pp);
  PokeGraArcDataGet(ssa, mons_no, sex, PARA_FRONT, col, form_no, 0);

  // �e�N�X�`����OAM�p�ɕϊ�����(�p�b�`�[���̂Ԃ����l��)
  rnd = PokeParaGet( pp, ID_PARA_personal_rnd, NULL );
  Ex_ChangesInto_OAM_from_PokeTex(ssa->arc_no, ssa->index_chr, wk->heapid, 0, 0, 10, 10,
				  char_work, rnd, 0, PARA_FRONT, mons_no);

  // OAM�pVRAM�ɓ]��
  DC_FlushRange(char_work, 0x20*10*10);
  GXS_LoadOBJ(char_work, POKEGRA_VRAM_OFFSET + 1*POKEGRA_VRAM_SIZE, POKEGRA_VRAM_SIZE);

  // �p���b�g�]��
  ArcUtil_PalSet(ssa->arc_no, ssa->index_pal, PALTYPE_SUB_OBJ, 0x20*(2+1), 32, wk->heapid);
}


//------------------------------------------------------------------
/**
 * @brief	�v���[���g�{�b�N�X
 */
//------------------------------------------------------------------
static void MysteryLib_SetGraPresent(MYSTERYLIB_WORK *wk, int type, GIFT_DELIVERY *deli)
{
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fushigi_box_lz_cngr,
		       NARC_mystery_fushigi_box_nclr,
		       NARC_mystery_fushigi_box_lz_ccer,
		       NARC_mystery_fushigi_box_lz_canr,
		       GF_BGL_SUB_DISP);
  MysteryLib_SetSubSurfaceMatrix(SUBSURFACEX, SUBSURFACEY);
  wk->giftact = MysteryLib_MakeCLACT(GF_BGL_SUB_DISP, wk->giftact, HW_LCD_WIDTH/2, 0, 0);
}

//------------------------------------------------------------------
/**
 * @brief	�|�P����
 */
//------------------------------------------------------------------
static void MysteryLib_SetGraPoke(MYSTERYLIB_WORK *wk, int type, GIFT_DELIVERY *deli)
{
  POKEMON_PARAM *pp;

  MysteryLib_InitClact(ARC_TRADELIST_GRA,
		       NARC_TradeList_obj_s_lz_ncgr,
		       NARC_TradeList_DsTradeList_nclr,
		       NARC_TradeList_obj_s_lz_ncer,
		       NARC_TradeList_obj_s_lz_nanr,
		       GF_BGL_SUB_DISP);
  MysteryLib_SetSubSurfaceMatrix(SUBSURFACEX, SUBSURFACEY);
  wk->giftact = MysteryLib_MakeCLACT(GF_BGL_SUB_DISP, wk->giftact, HW_LCD_WIDTH/2, 0, 1);
  pp = (POKEMON_PARAM *)&deli->data.pokemon.data;
  switch(type){
  case MYSTERYGIFT_TYPE_POKEMON:	// �|�P����
    MysteryLib_LoadPokeGra(pp, PokeParaGet(pp,ID_PARA_monsno,0), PokeParaGet(pp,ID_PARA_form_no,0), wk->PokeGra, &wk->PokeGraSsa);
    break;
  case MYSTERYGIFT_TYPE_POKEEGG:	// �^�}�S
    MysteryLib_LoadPokeGra(pp, MONSNO_TAMAGO, 0, wk->PokeGra, &wk->PokeGraSsa);
    break;
  case MYSTERYGIFT_TYPE_RANGEREGG:	// �i�}�t�B�[�̃^�}�Sbattle/*.c
    MysteryLib_LoadPokeGra(pp, MONSNO_TAMAGO, 1, wk->PokeGra, &wk->PokeGraSsa);
    break;
  }
}

//------------------------------------------------------------------
/**
 * @brief	�A�C�e��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryLib_SetGraItem(MYSTERYLIB_WORK *wk, int type, GIFT_DELIVERY *deli)
{
  int item;

  switch(type){
  case MYSTERYGIFT_TYPE_ITEM:		// �ǂ���
    item = deli->data.item.itemNo;
    break;
  case MYSTERYGIFT_TYPE_MEMBERSCARD:	// �����o�[�Y�J�[�h
    item = ITEM_MENBAAZUKAADO;
    break;
  case MYSTERYGIFT_TYPE_LETTER:		// �I�[�L�h�̂Ă���
    item = ITEM_OOKIDONOTEGAMI;
    break;
  case MYSTERYGIFT_TYPE_WHISTLE:	// �Ă񂩂��̂ӂ�
    item = ITEM_TENKAINOHUE;
    break;
  }
  MysteryLib_InitClact(ARC_ITEMICON,
		       GetItemIndex(item,ITEM_GET_ICON_CGX),
		       GetItemIndex(item,ITEM_GET_ICON_PAL),
		       ItemIconCellGet(),
		       ItemIconCAnmGet(),
		       GF_BGL_SUB_DISP);
  MysteryLib_SetSubSurfaceMatrix(SUBSURFACEX, SUBSURFACEY);
  wk->giftact = MysteryLib_MakeCLACT(GF_BGL_SUB_DISP, wk->giftact, HW_LCD_WIDTH/2, 0, 0);
}


//------------------------------------------------------------------
/**
 * @brief	�T�u��ʂ�BG�p���b�g��]��
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryLib_InitGiftPal(void *p)
{
  MYSTERYLIB_WORK *wk = (MYSTERYLIB_WORK *)p;

  // �T�u��ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fushigi_back_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2*6, wk->heapid);
}

//------------------------------------------------------------------
/**
 * @brief	����ʂɃv���[���g�󂯎�艉�o��\��
 *
 * SUB_BG0	�i�q�͗l(�㏑������邩�猩���Ȃ��Ȃ��Ă�)
 * SUB_BG1	�w�i�a�f
 * SUB_BG2,3	���g�p
 * SUB_OAM	�v���[���g�\��
 * ���T�u��ʂ̂a�f�p���b�g���W�`�P�R�܂Ŏg�p
*/
//------------------------------------------------------------------
void MysteryLib_InitGift(GF_BGL_INI *ini, GIFT_DELIVERY *deli)
{
  int palno, type;
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  type = deli->gift_type;

#if 0
  //  type = MYSTERYGIFT_TYPE_POKEMON;
  type = MYSTERYGIFT_TYPE_ITEM;
  //  deli->data.pokemon.monsno = 151;
  //  deli->data.item.itemNo = ITEM_KODAWARIMEGANE;
#endif  

  palno = MysteryLib_GetGiftPalno(type);

#if 0
  // �T�u��ʂa�f�p���b�g�]��
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fushigi_back_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2*6, wk->heapid);
#endif
  // �T�u���BG1�L�����]��
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fushigi_back_lz_cngr, ini,
		    GF_BGL_FRAME1_S, 0, 10*16*0x20, 1, wk->heapid);
  // �T�u��ʃX�N���[���P
#if 0
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fushigi_back_lz_cscr, ini, GF_BGL_FRAME1_S, 0, 32*24*2, 1, wk->heapid);
#else
 {
   // ArcUtil_ScrnSet���Ɣ񐂒����Ԓ���VRAM�]������Ă��܂��̂ŁA�C��
   NNSG2dScreenData* scrnData;
   void *arcData = ArcUtil_Load(ARC_MYSTERY_GRA, NARC_mystery_fushigi_back_lz_cscr, 1, wk->heapid, ALLOC_BOTTOM);
   NNS_G2dGetUnpackedScreenData( arcData, &scrnData );
   GF_BGL_ScreenBufSet(ini, GF_BGL_FRAME1_S, scrnData->rawData, 32*24*2 );
   sys_FreeMemoryEz( arcData );
 }
#endif
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_S, 0, 0, 32, 24, 8 + palno);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_S);
  wk->vfunc = MysteryLib_InitGiftPal;

  
  // �ォ��~���Ă���A�N�^�[�̐ݒ�
  switch(type){
  case MYSTERYGIFT_TYPE_RULE:		// ���[��
  case MYSTERYGIFT_TYPE_GOODS:		// �O�b�Y
  case MYSTERYGIFT_TYPE_ACCESSORY:	// �A�N�Z�T��
  case MYSTERYGIFT_TYPE_POKETCH:	// �|�P�b�`
    MysteryLib_SetGraPresent(wk, type, deli);
    break;
  case MYSTERYGIFT_TYPE_RANGEREGG:	// �i�}�t�B�[�̃^�}�S
    wk->giftact_wait = 120;
  case MYSTERYGIFT_TYPE_POKEMON:	// �|�P����
  case MYSTERYGIFT_TYPE_POKEEGG:	// �^�}�S
    MysteryLib_SetGraPoke(wk, type, deli);
    break;
  case MYSTERYGIFT_TYPE_ITEM:		// �ǂ���
  case MYSTERYGIFT_TYPE_MEMBERSCARD:	// �����o�[�Y�J�[�h
  case MYSTERYGIFT_TYPE_LETTER:		// �I�[�L�h�̂Ă���
  case MYSTERYGIFT_TYPE_WHISTLE:	// �Ă񂩂��̂ӂ�
    MysteryLib_SetGraItem(wk, type, deli);
    break;
  }
  // �ŏ��͔�\��
  CLACT_SetDrawFlag(wk->giftact, 0);
}


//------------------------------------------------------------------
/**
 * @brief	�w��̃o�b�t�@���Í���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define SECRET_KEY	0xD679
void MysteryLib_CreateCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid)
{
  MATHCRC16Table *CrcTbl;
  CRYPTORC4Context *rc4context;
  u16 key[4];
  u16 crc, mask;
  int i;

#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    u8 *p;
#if 0
    p = (u8 *)&gift_data->data;
    for(i = 0; i < 256; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
#else
    p = (u8 *)&gift_data->beacon;
    for(i = 0; i < 128; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
#endif
    OS_TPrintf("\n");
  }
#endif

  // �r�[�R����񂩂�CRC�l�𐶐�
  CrcTbl = sys_AllocMemory(heapid, sizeof(MATHCRC16Table));
  MATH_CRC16InitTable(CrcTbl);
  crc = MATH_CalcCRC16(CrcTbl, &gift_data->beacon, sizeof(GIFT_BEACON));
  sys_FreeMemoryEz(CrcTbl);
  
  OS_GetMacAddress((u8*)key);
  key[3] = key[1];
  key[1] = crc;
  mask = SECRET_KEY;
  for(i = 0; i < 4; i++){
    key[i] = key[i] ^ mask;
    mask = key[i];
  }	

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("KEY: %04X %04X %04X %04X\n", key[0], key[1], key[2], key[3]);
#endif

  // MAC�A�h���X���L�[�Ƃ��ĈÍ���
  rc4context = sys_AllocMemory(heapid, sizeof(CRYPTORC4Context));
  CRYPTO_RC4Init(rc4context, key, 8 );
  CRYPTO_RC4Encrypt(rc4context, &gift_data->data, sizeof(GIFT_DATA), data);
  sys_FreeMemoryEz(rc4context);
#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    u8 *p;
    p = (u8 *)data;
    for(i = 0; i < 256; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
    OS_TPrintf("\n");
  }
#endif
}


//------------------------------------------------------------------
/**
 * @brief	�Í������ꂽ�o�b�t�@��Decode
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_DecodeCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid)
{
  MATHCRC16Table *CrcTbl;
  CRYPTORC4Context *rc4context;
  const WMBssDesc *bssDesc;
  u16 key[4];
  u16 crc, mask;
  int i;

#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    u8 *p;

    // ����������O�̃o�C�i���f�[�^��DTCM�ɕۑ�(�����������ꒃ�c)
    memcpy((void *)0x027E0100, gift_data, sizeof(GIFT_COMM_PACK));
    OS_TPrintf("�������O�̃f�[�^: %08X - %08X\n", 0x027E0100, 0x027E0100 + sizeof(GIFT_COMM_PACK));

    p = (u8 *)&gift_data->beacon;
    for(i = 0; i < 128; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
    OS_TPrintf("\n\n\n");


    
    p = (u8 *)&gift_data->data;
    for(i = 0; i < 256; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
    OS_TPrintf("\n");
  }
#endif
  // �r�[�R����񂩂�CRC�l�𐶐�
  CrcTbl = sys_AllocMemory(heapid, sizeof(MATHCRC16Table));
  MATH_CRC16InitTable(CrcTbl);
  crc = MATH_CalcCRC16(CrcTbl, &gift_data->beacon, sizeof(GIFT_BEACON));
  sys_FreeMemoryEz(CrcTbl);
  
  // �e��MAC�A�h���X�𓾂�
  bssDesc = CommMPGetWMBssDesc(0);
  memcpy(key, bssDesc->bssid, WM_SIZE_BSSID);
  key[3] = key[1];
  key[1] = crc;
  mask = SECRET_KEY;
  for(i = 0; i < 4; i++){
    key[i] = key[i] ^ mask;
    mask = key[i];
  }	

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("KEY: %04X %04X %04X %04X\n", key[0], key[1], key[2], key[3]);
#endif

  // MAC�A�h���X���L�[�Ƃ��ĕ�����
  rc4context = sys_AllocMemory(heapid, sizeof(CRYPTORC4Context));
  CRYPTO_RC4Init(rc4context, key, 8 );
  CRYPTO_RC4Encrypt(rc4context, &gift_data->data, sizeof(GIFT_DATA), data);
  sys_FreeMemoryEz(rc4context);

#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    u8 *p;
    p = (u8 *)data;
    for(i = 0; i < 256; i++){
      if((i & 15) == 0)	OS_TPrintf("\n");
      OS_TPrintf("%02X ", p[i]);
    }
    OS_TPrintf("\n");
  }
#endif
}


//------------------------------------------------------------------
/**
 * @brief	���j���[�Ń��C���ړ����������ۂɌĂ΂��R�[���o�b�N
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_MenuKeyMove(BMPLIST_WORK * wk, u32 param, u8 mode)
{
  switch(mode){
  case 0:		// �ʏ퓮��
    Snd_SePlay(SEQ_SE_DP_SELECT);
    break;
  case 1:		// ���j���[�N����
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	AGB�J�[�g���b�W�������o���荞�ݐݒ�
 * @param	NONE
 * @return	NONE
 * �� IrqTable��j��I�ɑ��삵�܂��c
*/
//------------------------------------------------------------------
static void CartridgeIrqFunc(void)
{
  u32 val;
  if(PAD_DetectFold() == FALSE){
    // �ӂ����܂��Ă��Ȃ���Ώ������~������
    // �ӂ������Ă�ۂ̏�����main.c��sleep���A�㏈���ɔC����
    // ������RTC�̓d�r�������ꍇ�ɂ̓J�[�g���b�W���h�����Ă��Ă����荞�݂�����̂ŁA
    // �������o������"�����I��"������Ă����ꍇ�̂ݏ������~������
    if(CTRDG_IsAgbCartridge() == FALSE)
      CTRDG_TerminateForPulledOut();
  }
}
void MysteryLib_SetAgbCartridgeIntr(BOOL flag)
{
  if(flag == TRUE){
    OS_DisableIrq();
    OS_SetIrqFunction(OS_IE_CARTRIDGE, CartridgeIrqFunc);
    OS_EnableIrqMask(OS_IE_CARTRIDGE);
    OS_EnableIrq();
  } else {
    OS_DisableIrqMask(OS_IE_CARTRIDGE);
  }
}
static void CartridgeIrqFunc2(void){}
void MysteryLib_SetAgbCartridgeIntr2(void)
{
  OS_DisableIrq();
  OS_SetIrqFunction(OS_IE_CARTRIDGE, CartridgeIrqFunc2);
  OS_EnableIrqMask(OS_IE_CARTRIDGE);
  OS_EnableIrq();
}


//------------------------------------------------------------------
/**
 * @brief	�c�r�Z�[�u�V�[�P���X
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryLib_InitSaveDSCard(SAVEDATA *sv)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  wk->sv = sv;
  wk->save_seq = MYSTERYLIB_SEQ_SAVE_INIT;
}

int MysteryLib_SaveDSCard(void)
{
  SAVE_RESULT result;
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();

  switch(wk->save_seq){
  case MYSTERYLIB_SEQ_SAVE_INIT:
    sys_SoftResetNG(SOFTRESET_TYPE_SAVELOAD);
    // DS���̃Z�[�u�A�����ݒ�
    SaveData_DivSave_Init(wk->sv, SVBLK_ID_MAX);
    wk->save_seq++;
    break;

  case MYSTERYLIB_SEQ_SAVE_MAIN:
    // �Z�[�u���C��
    //    OS_TPrintf("�����Z�[�u��...\n");
    result = SaveData_DivSave_Main(wk->sv);
    if(result == SAVE_RESULT_NG){
      wk->save_seq = MYSTERYLIB_SEQ_SAVE_NG;
    } else if(result == SAVE_RESULT_OK){
      wk->save_seq = MYSTERYLIB_SEQ_SAVE_OK;
    } else if(result == SAVE_RESULT_LAST){
      wk->save_seq = MYSTERYLIB_SEQ_SAVE_LAST;
    }
    if(result == SAVE_RESULT_OK || result == SAVE_RESULT_NG)
      sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
    return result;
    break;

  case MYSTERYLIB_SEQ_SAVE_LAST:
    // �Ō�̃Z�[�u�҂�
    // ���ɂ���MysteryLib_DoLastSave�����s����ƍŌ�̃Z�[�u������
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("LAST-SAVE\n");
#endif
    break;
  case MYSTERYLIB_SEQ_SAVE_OK:
    break;
  case MYSTERYLIB_SEQ_SAVE_NG:
    break;
  }
  return SAVE_RESULT_CONTINUE;
}

void MysteryLib_DoLastSave(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  if(wk->save_seq == MYSTERYLIB_SEQ_SAVE_LAST)
    wk->save_seq = MYSTERYLIB_SEQ_SAVE_MAIN;
}

void MysteryLib_CancelSaveDSCard(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  SaveData_DivSave_Cancel(wk->sv);
  sys_SoftResetOK(SOFTRESET_TYPE_SAVELOAD);
}

int MysteryLib_GetSaveStatus(void)
{
  MYSTERYLIB_WORK *wk = GetMysteryLibWorkPtr();
  return wk->save_seq;
}

/*  */
