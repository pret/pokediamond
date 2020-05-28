//============================================================================================
/**
 * @file	ug_local.h
 * @brief	地下共通項目のローカル宣言
 * @author	k.ohno
 * @date	2006.3.9
 */
//============================================================================================
#ifndef __UG_LOCAL_H__
#define __UG_LOCAL_H__

#include "ug_list.h"

//==============================================================================
//	型宣言
//==============================================================================
typedef int (*pGetNumFunc)(void* work);   // 要素の個数を返す関数
typedef int (*pGetTypeFunc)(int index, void* work);   // 要素の中身を順に取り出す関数を返す
typedef int (*pGetCaratFunc)(int index, void* work);   // 要素の中身パラメータを順に取り出す関数を返す
typedef	void (*pBmpCallBack)(BMPLIST_WORK * wk,u32 param,u8 mode);	//カーソル移動ごとのコールバック関数

#define _SHOP_BUY_LIST_MAX (5)

#define _FIELD_START_MENU_MAX ( 7 )
#define	_FIELD_MENU_MAX		( 6 )					// 項目最大数
#define	_FLDMENU_CLACT_MAX	( _FIELD_START_MENU_MAX + 1 )	// セルアクター最大数（項目＋カーソル）

#define _MENURETURN_EXIT   BMPLIST_CANCEL //(0xf0)   // とじるを表示した場合の戻り値

#define _MENU_UG_PRI  (10000)   // メニューのタスクpriorty

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ


typedef struct{
  void* menuCallBack;
  TCB_PTR pTCB;
  FLD_COMACT_WORK* fca;
  FIELDSYS_WORK* pFSys;
  GF_BGL_BMPWIN  win;		// BMPウィンドウワーク
  GF_BGL_BMPWIN  winSub;		// BMPウィンドウワーク
  GF_BGL_BMPWIN  winSub2;		// BMPウィンドウワーク
  BMPLIST_DATA*  menulist;
  BMPLIST_DATA*  subMenulist;
  BMPLIST_WORK*  lw;		// BMPメニューワーク
  UG_BMPLIST_WORK* pUGlw;
  BMPLIST_WORK*  subLw;		// BMPメニューワーク
  BMPMENU_WORK* mw;
  BMP_MENULIST_DATA * ld;	// BMPリストデータ
  BMPMENU_WORK*  pYesNoWork;
  pBmpCallBack pLineCallBack;  // 1LINEコールバック
  pBmpCallBack pIconCallBack;  // ICONコールバック
  STRBUF* pStrBuf1;
  STRBUF* pStrBuf2;
  WORDSET* pWordSet;
  FIELD_CLACT	fcat;		// セルアクター設定データ
  CATS_ACT_PTR	cap[_FLDMENU_CLACT_MAX];
  u32	clact_max;			// セルアクター登録数
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
  u16	pos;				// メニュー位置
  u32	ret;				// メニュー戻り
  u16 connectIndex;  // つなぐ親機のINDEX
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

/// MENUカーソル位置を表示数を見て補正
extern void UgBagCursorLineLimit(_START_WORK* pStart, int line,int count);
extern void _udCurDisp(_START_WORK* pPc, int line,  int maxLine , int windowNum);

enum _LOCAL_UG_MENU_RET {
  _RESULT_NONE,
  _RESULT_OK,
  _RESULT_NG,
  _RESULT_DELFLAG_OPEN,
  _RESULT_FOSSIL,
};


// キーを記憶しておく仕組み

#define _KEY_RESERVE_BUFF  (20)

enum{
  _KEY_NAME_NONE,
  _KEY_NAME_PC,
  _KEY_NAME_BAG,
  _KEY_NAME_SHOP_GOODS,      //ugdef.h UG_SHOP_TRAPとおなじ
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
  _KEY_MENU_SHOP_MAIN,   // うるかう
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
