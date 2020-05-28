//============================================================================================
/**
 * @file	mysterylib.h
 * @bfief	�ӂ����ȁ@��������̂Ŏg���郉�C�u�������ǂ�
 * @author	Satoshi Mitsuhara
 * @date	06.06.12
 *
 * $Id: mysterylib.h,v 1.19 2006/08/10 09:45:23 mitsuhara Exp $
 */
//============================================================================================
#ifndef __MYSTERYLIB_H__
#define __MYSTERYLIB_H__

#include "system/fontproc.h"
#include "system/clact_util.h"
#include "system/bmp_list.h"
#include "savedata/fushigi_data.h"

#ifdef DEBUG_ONLY_FOR_mituhara
#define MIT_PRINTF(...)		(void) ((OS_TPrintf(__VA_ARGS__)))
#else
#define MIT_PRINTF(...)		NULL
#endif


// ���b�Z�[�W�E�B���h�E����n
typedef struct {
  int winmode;
  int drawflag;
  int redrawflag;
  int rightflag;		// �E��
  GF_BGL_BMPWIN *win;
  WORDSET *word;
  int width, height;
  int dx, dy;
  int base;
  int screen;
  int palno;
  int arcno;
  int fchr, fcol;
  FONT_TYPE font;
  GF_PRINTCOLOR color;
  u8 clrcolor;
  int msgid;
  int msgspd;
} MYSTERY_WIN;


// �Z���A�N�^�[����n
typedef struct {
  CLACT_SET_PTR	clactSet;				// �Z���A�N�^�[�Z�b�g 
  CLACT_U_EASYRENDER_DATA renddata;			// �ȈՃ����_�[�f�[�^
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// ���\�[�X�}�l�[�W��
  CLACT_U_RES_OBJ_PTR resObjTbl[2][CLACT_U_RES_MAX];	// ���\�[�X�I�u�W�F�e�[�u��
  CLACT_HEADER clActHeader[2];

  int arcfile;
  int arcchar;
  int arcpal;
  int arccell;
  int arcanim;
  int screen;
} MYSTERY_CLACT;

enum {
  MYSTERYLIB_SEQ_SAVE_INIT = 0,
  MYSTERYLIB_SEQ_SAVE_MAIN,
  MYSTERYLIB_SEQ_SAVE_OK,
  MYSTERYLIB_SEQ_SAVE_NG,
  MYSTERYLIB_SEQ_SAVE_LAST,
  MYSTERYLIB_SEQ_SAVE_MAX
};

#define MYSTERYLIB_WINTYPE_NORMAL	0
#define MYSTERYLIB_WINTYPE_TALK		1

#define MYSTERYLIB_COLOR_NULL		0
#define MYSTERYLIB_COLOR_WHITE		1
#define MYSTERYLIB_COLOR_BLACK		2
#define MYSTERYLIB_COLOR_BLUE		3


#define MYSTERYLIB_CHAR_CONT_NUM		20
#define MYSTERYLIB_CHAR_VRAMTRANS_MAIN_SIZE	2048
#define MYSTERYLIB_CHAR_VRAMTRANS_SUB_SIZE	2048
#define MYSTERYLIB_PLTT_CONT_NUM		20


//------------------------------------------------------------------
///	�ӂ����ȁ@��������̃��C�u����������
//------------------------------------------------------------------
extern void MysteryLib_Init(int heap);

//------------------------------------------------------------------
///	PROC���������܂Ƃ߂��֐�
//------------------------------------------------------------------
extern void *MysteryLib_InitProc(PROC *proc, int heapid, int size, int heapsize);

//------------------------------------------------------------------
///	�a�f�������֐�(�P�t���[���̂�)
//------------------------------------------------------------------
extern void MysteryLib_BgInitFrame(GF_BGL_INI *ini, int frame, u8 size, u32 scrbase, u32 scrchar);

//------------------------------------------------------------------
///	�t�F�[�h�̃^�C�v�ύX
//------------------------------------------------------------------
extern void MysteryLib_ChangeFadeType(int type);

//------------------------------------------------------------------
///	�t�F�[�h�֐�
//------------------------------------------------------------------
extern void MysteryLib_RequestFade(int type, int next_seq, int *seq, int next);

//------------------------------------------------------------------
///	�t�F�[�h�I���֐�
//------------------------------------------------------------------
extern void MysteryLib_FadeEndCheck(int *seq);

//------------------------------------------------------------------
///	MYSTERY_WIN�\���̂̏�����
//------------------------------------------------------------------
extern void MysteryLib_WinInit1(MYSTERY_WIN *mw, GF_BGL_BMPWIN *win, int palno, int arc, int fchr, int fcol);
extern void MysteryLib_WinInit2(MYSTERY_WIN *mw, int w, int h, /*int msgid,*/ int base);
extern void MysteryLib_WinInit3(MYSTERY_WIN *mw, int type, int font);
extern void MysteryLib_WinSetColor(MYSTERY_WIN *mw, int color);
extern void MysteryLib_WinSetPos(MYSTERY_WIN *mw, int dx, int dy);

//------------------------------------------------------------------
///	���b�Z�[�W�E�B���h�E��o�^
//------------------------------------------------------------------
extern int MysteryLib_CreateWin(GF_BGL_INI *bgl, MYSTERY_WIN *mw, int sx, int sy, int msg);

//------------------------------------------------------------------
///	�E�B���h�E�������L�����N�^������Ԃ�
//------------------------------------------------------------------
extern int MysteryLib_GetWindowChr(MYSTERY_WIN *mw);

//------------------------------------------------------------------
///	�L�����N�^�A�p���b�g�}�l�[�W���[������
//------------------------------------------------------------------
extern void MysteryLib_InitCPManager(void);

//------------------------------------------------------------------
///	�Z���A�N�^�[�V�X�e��������������Ă邩�Ԃ�
//------------------------------------------------------------------
extern BOOL MysteryLib_isInitClact(void);

//------------------------------------------------------------------
///	�Z���A�N�^�[�V�X�e���̏�����
//------------------------------------------------------------------
extern void MysteryLib_InitClactSystem(void);

//------------------------------------------------------------------
///	�Z���A�N�^�[������
//------------------------------------------------------------------
extern void MysteryLib_InitClact(int arcfile, int arcchar, int arcpal, int arccell, int arcanim, int screen);

//------------------------------------------------------------------
///	�T�u��ʂ̃T�[�t�F�C�X�ύX
//------------------------------------------------------------------
extern void MysteryLib_SetSubSurfaceMatrix(fx32 x, fx32 y);

//------------------------------------------------------------------
///	���t���[���Ăяo���ė~�����֐�
//------------------------------------------------------------------
extern void MysteryLib_DoClact(void);

//------------------------------------------------------------------
///	CLACT_ADD�̐��`���쐬
//------------------------------------------------------------------
extern CLACT_WORK_PTR MysteryLib_MakeCLACT(int screen, CLACT_WORK_PTR anim, int sx, int sy, int anum);

//------------------------------------------------------------------
///	�Z���A�N�^�[�̍폜
//------------------------------------------------------------------
extern void MysteryLib_RemoveClact(void);

//------------------------------------------------------------------
///	�Q�[���J�Z�b�g�ɑΉ������r�b�g��Ԃ�
//------------------------------------------------------------------
extern u32 MysteryLib_GetCasetteCode(int cas);

//------------------------------------------------------------------
///	����ʂɃv���[���g�󂯎�艉�o��\��
//------------------------------------------------------------------
extern void MysteryLib_InitGift(GF_BGL_INI *ini, GIFT_DELIVERY *deli);

//------------------------------------------------------------------
///	�w��̃o�b�t�@���Í���
//------------------------------------------------------------------
extern void MysteryLib_CreateCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid);

//------------------------------------------------------------------
///	�Í������ꂽ�o�b�t�@��Decode
//------------------------------------------------------------------
extern void MysteryLib_DecodeCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid);

//------------------------------------------------------------------
///	���j���[�Ń��C���ړ����������ۂɌĂ΂��R�[���o�b�N
//------------------------------------------------------------------
extern void MysteryLib_MenuKeyMove(BMPLIST_WORK * wk, u32 param, u8 mode);

//------------------------------------------------------------------
///	�`�f�a�J�Z�b�g�̔����`�F�b�N
//------------------------------------------------------------------
extern void MysteryLib_CheckAgbCartridge(void);

//------------------------------------------------------------------
/// 	AGB�J�[�g���b�W�������o���荞�ݐݒ�
//------------------------------------------------------------------
extern void MysteryLib_SetAgbCartridgeIntr(BOOL flag);
extern void MysteryLib_SetAgbCartridgeIntr2(void);

//------------------------------------------------------------------
///	�c�r�Z�[�u�V�[�P���X
//------------------------------------------------------------------
extern void MysteryLib_InitSaveDSCard(SAVEDATA *sv);
extern int MysteryLib_SaveDSCard(void);
extern void MysteryLib_DoLastSave(void);
extern void MysteryLib_CancelSaveDSCard(void);
extern int MysteryLib_GetSaveStatus(void);


#endif	// __MYSTERYLIB_H__
/*  */
