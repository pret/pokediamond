//==============================================================================================
/**
 * @file	opneing_sys.h
 * @brief	オープニング システム　
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#ifndef _OPENING_SYS_H_
#define _OPENING_SYS_H_

#include "common.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/procsys.h"
#include "system/wordset.h"
#include "savedata/config.h"
#include "opening_obj.h"


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================
extern const PROC_DATA OpeningProcData;				//プロセス定義データ

extern PROC_RESULT OpeningProc_Init( PROC * proc, int * seq );
extern PROC_RESULT OpeningProc_Main( PROC * proc, int * seq );
extern PROC_RESULT OpeningProc_End( PROC * proc, int * seq );

//==============================================================================================
//
//	定義
//
//==============================================================================================
//ビットマップID
enum{
	BMPWIN_MENU_1 = 0,
	BMPWIN_GUIDE,
	BMPWIN_MENU_2,
	BMPWIN_OOKIDO,
	BMPWIN_YESNO,
	BMPWIN_IDSEL,
	OPENING_BMPWIN_MAX,								//BMPウィンドウの数
};

#define OPENING_MENU_MAX		(4)					//メニューの数

#define OP_FRM_FONT				(GF_BGL_FRAME1_M)

//パレット定義
#define OP_TALKWIN_PAL			(10)				//会話ウィンドウ使用パレットナンバー
#define OP_MENU_PAL				(11)				//メニューウィンドウ使用パレットナンバー
#define OP_MSGFONT_PAL			(12)				//MSGフォント使用パレットナンバー
#define OP_FONT_PAL				(13)				//SYSTEMフォント使用パレットナンバー

//OBJナンバー
#define OP_OBJ_HAKASE			(0)
#define OP_OBJ_RIVAL			(1)
#define OP_OBJ_KAGE				(2)

#define OP_VANISH_ON			(0)					//非表示
#define OP_VANISH_OFF			(1)					//表示


//==============================================================================================
//
//	構造体宣言
//
//==============================================================================================
typedef struct OPENING_WORK_tag
{
	GF_BGL_INI* bgl;								//BGLデータ
	GF_BGL_BMPWIN bmpwin[OPENING_BMPWIN_MAX];		//BMPウィンドウデータ

	MSGDATA_MANAGER* msgman;						//メッセージマネージャー
	WORDSET* wordset;								//単語セット
	STRBUF* msg_buf;								//メッセージバッファポインタ
	STRBUF* tmp_buf;								//テンポラリバッファポインタ
	STRBUF* menu_buf[OPENING_MENU_MAX];				//メニューバッファポインタ

	STRCODE str[PERSON_NAME_SIZE + EOM_SIZE];
	PROC* proc;

	CONFIG* config;									//コンフィグポインタ
	SAVEDATA* sv;									//セーブデータポインタ

	u16 count;
	u8 sub_seq;
	u8 msg_index;									//メッセージindex

	u8 sex;											//性別
	u8 cancel;										//やり直しフラグ
	u8 dmy3;
	u8 dmy4;

	//BMPメニュー(bmp_menu.h)
	BMPMENU_HEADER MenuH;							//BMPメニューヘッダー
	BMPMENU_WORK * mw;								//BMPメニューワーク
	BMPMENU_DATA Data[OPENING_MENU_MAX];			//BMPメニューデータ
	u32 ret_work;									//選択したパラメータ

	fx32 ScaleX;
	fx32 ScaleY;

	OPENING_OBJ_WORK ObjWork;

	PALETTE_FADE_PTR pfd;							//パレットフェード

	TCB_PTR	tcb;									//名前入力監視TCB
}OPENING_WORK;


#endif //_OPENING_SYS_H_


