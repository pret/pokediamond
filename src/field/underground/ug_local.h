//============================================================================================
/**
 * @file	ug_local.h
 * @brief	�n�����ʍ��ڂ̃��[�J���錾
 * @author	k.ohno
 * @date	2006.3.9
 */
//============================================================================================
#ifndef __UG_LOCAL_H__
#define __UG_LOCAL_H__

#include "ug_list.h"

//==============================================================================
//	�^�錾
//==============================================================================
typedef int (*pGetNumFunc)(void* work);   // �v�f�̌���Ԃ��֐�
typedef int (*pGetTypeFunc)(int index, void* work);   // �v�f�̒��g�����Ɏ��o���֐���Ԃ�
typedef int (*pGetCaratFunc)(int index, void* work);   // �v�f�̒��g�p�����[�^�����Ɏ��o���֐���Ԃ�
typedef	void (*pBmpCallBack)(BMPLIST_WORK * wk,u32 param,u8 mode);	//�J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�

#define _SHOP_BUY_LIST_MAX (5)

#define _FIELD_START_MENU_MAX ( 7 )
#define	_FIELD_MENU_MAX		( 6 )					// ���ڍő吔
#define	_FLDMENU_CLACT_MAX	( _FIELD_START_MENU_MAX + 1 )	// �Z���A�N�^�[�ő吔�i���ځ{�J�[�\���j

#define _MENURETURN_EXIT   BMPLIST_CANCEL //(0xf0)   // �Ƃ����\�������ꍇ�̖߂�l

#define _MENU_UG_PRI  (10000)   // ���j���[�̃^�X�Npriorty

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y


typedef struct{
  void* menuCallBack;
  TCB_PTR pTCB;
  FLD_COMACT_WORK* fca;
  FIELDSYS_WORK* pFSys;
  GF_BGL_BMPWIN  win;		// BMP�E�B���h�E���[�N
  GF_BGL_BMPWIN  winSub;		// BMP�E�B���h�E���[�N
  GF_BGL_BMPWIN  winSub2;		// BMP�E�B���h�E���[�N
  BMPLIST_DATA*  menulist;
  BMPLIST_DATA*  subMenulist;
  BMPLIST_WORK*  lw;		// BMP���j���[���[�N
  UG_BMPLIST_WORK* pUGlw;
  BMPLIST_WORK*  subLw;		// BMP���j���[���[�N
  BMPMENU_WORK* mw;
  BMP_MENULIST_DATA * ld;	// BMP���X�g�f�[�^
  BMPMENU_WORK*  pYesNoWork;
  pBmpCallBack pLineCallBack;  // 1LINE�R�[���o�b�N
  pBmpCallBack pIconCallBack;  // ICON�R�[���o�b�N
  STRBUF* pStrBuf1;
  STRBUF* pStrBuf2;
  WORDSET* pWordSet;
  FIELD_CLACT	fcat;		// �Z���A�N�^�[�ݒ�f�[�^
  CATS_ACT_PTR	cap[_FLDMENU_CLACT_MAX];
  u32	clact_max;			// �Z���A�N�^�[�o�^��
  pBagEndFunc endfunc;
  pGetNumFunc getNumFunc;
  pGetTypeFunc getTypeFunc;
  pGetCaratFunc getCaratFunc;
  void* pWork;
  u8 item[_SHOP_BUY_LIST_MAX];
  u8 stone[_SHOP_BUY_LIST_MAX];
  u8 carat[_SHOP_BUY_LIST_MAX];
  BOOL fadeFlg;
  int personal;
  int msgIndex;
  int cursor;
  int line;
  u32 list_id;
  u16	pos;				// ���j���[�ʒu
  u32	ret;				// ���j���[�߂�
  u16 connectIndex;  // �Ȃ��e�@��INDEX
  u8 waitMode;
  u8 endState;
  u8 work;
  u8 seqNext;
  u8 seq;
  u8 bBuy;
  u8 ShopID;
  u16 pos_bak;
  u16 pos_bak2;
} _START_WORK;


typedef void (*NEXTJOB_CALLBACK)(_START_WORK* pStart);

extern void _startMenuEnd(_START_WORK* pStart);
extern int _underBagGetGoodsID(int index, void* work);
extern int _underPcGetGoodsID(int index, void* work);
extern int _underBagGetStoneID(int index, void* work);
extern int _underBagGetStoneCarat(int index, void* work);
extern int _underPcGetStoneType(int index, void* work);
extern int _underPcGetStoneCarat(int index, void* work);
extern int _underBagGetTreasureID(int index, void* work);
extern int _underPcGetTreasureType(int index, void* work);
extern int _underBagGetTrapID(int index,void* work);
extern int _underPcGetTrapType(int index, void* work);

extern void _trapMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode);
extern void _treasureMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode);
extern void _goodsMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode);
extern void _goodsMenuStart_Bag(_START_WORK* pStart);
extern void _goodsMenuStart_BagPc(_START_WORK* pStart);
extern void _stoneMenuStart_ShopBag(_START_WORK* pStart);
extern void _trapMenuStart_Bag(_START_WORK* pStart);
extern void _treasureMenuStart_Bag(_START_WORK* pStart);
extern void _goodsMenuStart_Shop(_START_WORK* pStart);
extern void _trapMenuStart_Shop(_START_WORK* pStart);
extern void _treasureMenuStart_Shop(_START_WORK* pStart);
extern void _goodsMenuStart_Pc(_START_WORK* pStart);
extern void _stoneMenuStart_Pc(_START_WORK* pStart);
extern void _trapMenuStart_Pc(_START_WORK* pStart);
extern void _treasureMenuStart_Pc(_START_WORK* pStart);

/// MENU�J�[�\���ʒu��\���������ĕ␳
extern void UgBagCursorLineLimit(_START_WORK* pStart, int line,int count);
extern void _udCurDisp(_START_WORK* pPc, int line,  int maxLine , int windowNum);

enum _LOCAL_UG_MENU_RET {
  _RESULT_NONE,
  _RESULT_OK,
  _RESULT_NG,
  _RESULT_DELFLAG_OPEN,
  _RESULT_FOSSIL,
};


// �L�[���L�����Ă����d�g��

#define _KEY_RESERVE_BUFF  (20)

enum{
  _KEY_NAME_NONE,
  _KEY_NAME_PC,
  _KEY_NAME_BAG,
  _KEY_NAME_SHOP_GOODS,      //ugdef.h UG_SHOP_TRAP�Ƃ��Ȃ�
  _KEY_NAME_SHOP_TRAP,
  _KEY_NAME_SHOP_TREASURE,
};

enum{
  _KEY_MENU_PC_SEND_STONE,
  _KEY_MENU_PC_SEND_TREASURE,
  _KEY_MENU_PC_SEND_GOODS,
  _KEY_MENU_PC_SEND_TRAP,
  _KEY_MENU_PC_RECV_STONE,
  _KEY_MENU_PC_RECV_TREASURE,
  _KEY_MENU_PC_RECV_GOODS,
  _KEY_MENU_PC_RECV_TRAP,
  _KEY_MENU_BAG_TRAP,
  _KEY_MENU_BAG_STONE,
  _KEY_MENU_BAG_GOODS,
  _KEY_MENU_BAG_TREASURE,
  _KEY_MENU_SHOP_STONE,
  _KEY_MENU_SHOP_GOODS,
  _KEY_MENU_SHOP_TRAP,
  _KEY_MENU_SHOP_TREASURE,
  _KEY_MENU_BUY_GOODS,
  _KEY_MENU_BUY_TRAP,
  _KEY_MENU_BUY_TREASURE,
  _KEY_MENU_SHOP_MAIN,   // ���邩��
  _KEY_MENU_PC_SEND,
  _KEY_MENU_PC_RECV,
  _KEY_MENU_PC_RADAR,
  _KEY_MENU_PC_MAIN,
};

typedef struct{
    u16 keyBaseName;
    u16 windowName;
    u16 oldCursor;
    u16 oldLine;
} _RECORD_MENU_KEY;




#endif //__UG_LOCAL_H__
