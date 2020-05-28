//============================================================================================
/**
 * @file	mysterylib.h
 * @bfief	ふしぎな　おくりもので使えるライブラリもどき
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


// メッセージウィンドウ制御系
typedef struct {
  int winmode;
  int drawflag;
  int redrawflag;
  int rightflag;		// 右寄せ
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


// セルアクター制御系
typedef struct {
  CLACT_SET_PTR	clactSet;				// セルアクターセット 
  CLACT_U_EASYRENDER_DATA renddata;			// 簡易レンダーデータ
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// リソースマネージャ
  CLACT_U_RES_OBJ_PTR resObjTbl[2][CLACT_U_RES_MAX];	// リソースオブジェテーブル
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
///	ふしぎな　おくりものライブラリ初期化
//------------------------------------------------------------------
extern void MysteryLib_Init(int heap);

//------------------------------------------------------------------
///	PROC初期化をまとめた関数
//------------------------------------------------------------------
extern void *MysteryLib_InitProc(PROC *proc, int heapid, int size, int heapsize);

//------------------------------------------------------------------
///	ＢＧ初期化関数(１フレームのみ)
//------------------------------------------------------------------
extern void MysteryLib_BgInitFrame(GF_BGL_INI *ini, int frame, u8 size, u32 scrbase, u32 scrchar);

//------------------------------------------------------------------
///	フェードのタイプ変更
//------------------------------------------------------------------
extern void MysteryLib_ChangeFadeType(int type);

//------------------------------------------------------------------
///	フェード関数
//------------------------------------------------------------------
extern void MysteryLib_RequestFade(int type, int next_seq, int *seq, int next);

//------------------------------------------------------------------
///	フェード終了関数
//------------------------------------------------------------------
extern void MysteryLib_FadeEndCheck(int *seq);

//------------------------------------------------------------------
///	MYSTERY_WIN構造体の初期化
//------------------------------------------------------------------
extern void MysteryLib_WinInit1(MYSTERY_WIN *mw, GF_BGL_BMPWIN *win, int palno, int arc, int fchr, int fcol);
extern void MysteryLib_WinInit2(MYSTERY_WIN *mw, int w, int h, /*int msgid,*/ int base);
extern void MysteryLib_WinInit3(MYSTERY_WIN *mw, int type, int font);
extern void MysteryLib_WinSetColor(MYSTERY_WIN *mw, int color);
extern void MysteryLib_WinSetPos(MYSTERY_WIN *mw, int dx, int dy);

//------------------------------------------------------------------
///	メッセージウィンドウを登録
//------------------------------------------------------------------
extern int MysteryLib_CreateWin(GF_BGL_INI *bgl, MYSTERY_WIN *mw, int sx, int sy, int msg);

//------------------------------------------------------------------
///	ウィンドウが消費するキャラクタ総数を返す
//------------------------------------------------------------------
extern int MysteryLib_GetWindowChr(MYSTERY_WIN *mw);

//------------------------------------------------------------------
///	キャラクタ、パレットマネージャー初期化
//------------------------------------------------------------------
extern void MysteryLib_InitCPManager(void);

//------------------------------------------------------------------
///	セルアクターシステムが初期化されてるか返す
//------------------------------------------------------------------
extern BOOL MysteryLib_isInitClact(void);

//------------------------------------------------------------------
///	セルアクターシステムの初期化
//------------------------------------------------------------------
extern void MysteryLib_InitClactSystem(void);

//------------------------------------------------------------------
///	セルアクター初期化
//------------------------------------------------------------------
extern void MysteryLib_InitClact(int arcfile, int arcchar, int arcpal, int arccell, int arcanim, int screen);

//------------------------------------------------------------------
///	サブ画面のサーフェイス変更
//------------------------------------------------------------------
extern void MysteryLib_SetSubSurfaceMatrix(fx32 x, fx32 y);

//------------------------------------------------------------------
///	毎フレーム呼び出して欲しい関数
//------------------------------------------------------------------
extern void MysteryLib_DoClact(void);

//------------------------------------------------------------------
///	CLACT_ADDの雛形を作成
//------------------------------------------------------------------
extern CLACT_WORK_PTR MysteryLib_MakeCLACT(int screen, CLACT_WORK_PTR anim, int sx, int sy, int anum);

//------------------------------------------------------------------
///	セルアクターの削除
//------------------------------------------------------------------
extern void MysteryLib_RemoveClact(void);

//------------------------------------------------------------------
///	ゲームカセットに対応したビットを返す
//------------------------------------------------------------------
extern u32 MysteryLib_GetCasetteCode(int cas);

//------------------------------------------------------------------
///	下画面にプレゼント受け取り演出を表示
//------------------------------------------------------------------
extern void MysteryLib_InitGift(GF_BGL_INI *ini, GIFT_DELIVERY *deli);

//------------------------------------------------------------------
///	指定のバッファを暗号化
//------------------------------------------------------------------
extern void MysteryLib_CreateCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid);

//------------------------------------------------------------------
///	暗号化されたバッファをDecode
//------------------------------------------------------------------
extern void MysteryLib_DecodeCryptoData(GIFT_COMM_PACK *gift_data, GIFT_DATA *data, int heapid);

//------------------------------------------------------------------
///	メニューでライン移動があった際に呼ばれるコールバック
//------------------------------------------------------------------
extern void MysteryLib_MenuKeyMove(BMPLIST_WORK * wk, u32 param, u8 mode);

//------------------------------------------------------------------
///	ＡＧＢカセットの抜きチェック
//------------------------------------------------------------------
extern void MysteryLib_CheckAgbCartridge(void);

//------------------------------------------------------------------
/// 	AGBカートリッジ抜き検出割り込み設定
//------------------------------------------------------------------
extern void MysteryLib_SetAgbCartridgeIntr(BOOL flag);
extern void MysteryLib_SetAgbCartridgeIntr2(void);

//------------------------------------------------------------------
///	ＤＳセーブシーケンス
//------------------------------------------------------------------
extern void MysteryLib_InitSaveDSCard(SAVEDATA *sv);
extern int MysteryLib_SaveDSCard(void);
extern void MysteryLib_DoLastSave(void);
extern void MysteryLib_CancelSaveDSCard(void);
extern int MysteryLib_GetSaveStatus(void);


#endif	// __MYSTERYLIB_H__
/*  */
