/***
 *	@file	porusys.h
 *	@brief	ポルトモジュール内ローカルヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.03.11
 */

#ifndef __H_PORU_SYS_H__
#define __H_PORU_SYS_H__

#include "application/poru_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/poruto_name.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "porucase.dat"
#include "poru_snd_def.h"

//プロトタイプ
typedef struct _PORU_CASE_WORK PORU_CASE_WORK;
#include "poru_act.h"
#include "poru_oam.h"

#define WORDSET_PORU_BUFLEN	(64)

typedef enum{
 PVIEW_SPICY,
 PVIEW_ASTR,
 PVIEW_SWEET,
 PVIEW_BITTER,
 PVIEW_SOUR,
 PVIEW_ALL,
 PVIEW_MAX,
}PCASE_VIEW;

typedef enum{
 PCASE_RET_CANCEL,
 PCASE_RET_DECIDE,
}PCASE_RET;

typedef enum{
 PCASE_MODE_PSEL,
 PCASE_MODE_MSEL,
 PCASE_MODE_MSELWAIT,
 PCASE_MODE_YNSET,
 PCASE_MODE_YNWAIT,
 PCASE_MODE_DEL,
 PCASE_MODE_EXIT,
};

typedef struct _PORUCASE_MSG{
	WORDSET* wset;		//ワーク
	STRBUF	*tmp;		//汎用
	STRBUF	*endbuf;	//やめる
	STRBUF	*listbuf;	//やめる
	STRBUF	*tbuf;		//滑らかさ
	STRBUF	*qbuf;		//捨てますか？
	STRBUF	*dbuf;		//捨てました
	STRBUF	*sbuf;		//サムネイル
	STRBUF	*swbuf[PVIEW_MAX];		//下画面スイッチ
	STRBUF	*exbuf[PVIEW_ALL];		//下画面説明文
	u8	msg_spd;	///<メッセージスピード
	u8	dmy[3];	///<padding
}PORUCASE_MSG;

typedef struct _PORU_CASE_WORK{
	int	heapID;
	int	seq;
	int	sub_seq;
	int	wipe_f;
	int ret_mode;
	u16	tp_f;
	u16	plist_cb_f;	///<ポルトリストコールバック処理有効
	u16	selMode;
	u8	selectID;
	u8	viewMode;

	u8	viewNum;
	u8	startID;
	u8	endID;

	u8	msgIdx;
	PORUTO_PARAM* param;	///<引継ぎパラメータ
	GF_BGL_INI *bgl;	///<BGLデータ

	///ポルト名取得マネージャ
	PORUTO_NAME_MAN	*nameMan;
	MSGDATA_MANAGER *msgMan;
	PORUCASE_MSG	msgDat;

	///ポルトリストコントローラ
	u16		listPos;
	u16		curPos;
	BMPLIST_HEADER	plist_h;
	BMPLIST_HEADER	mlist_h;
	BMPLIST_WORK* plist_wk; 
	BMPLIST_WORK* mlist_wk; 
	BMPLIST_DATA* plist; 
	BMPLIST_DATA* mlist; 
	BMPMENU_WORK* ynmenu_wk; 

	///グラフィックリソース
	void*	pScrBuf01;
	void*	pScrBuf02;
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr02;
	GF_BGL_BMPWIN	win[WIN_MAX];
	
	CATS_SYS_PTR	pActSys;	///<セルアクターシステム
	CATS_RES_PTR	pActRes;	///<セルアクターリソース
	CLACT_WORK_PTR	pAct[NORMAL_ACTMAX];		///<アクター
	CLACT_WORK_PTR	pActFmk[FMARK_ACTMAX];		///<アクター
	CLACT_WORK_PTR	pActBtn[BUTTON_ACTMAX];		///<アクター

	PORUOAM_MAN		*poruMan;	///<ポルトOAMマネージャ
	PORUTO_OAM		*pOam;		///<ポルト	
}PORU_CASE_WORK;

#define WINCLR_COL(col)	(((col)<<4)|(col))

///ポルトモジュール内外部参照
extern PROC_RESULT PoruCase_Init(PROC* proc,int* seq);
extern PROC_RESULT PoruCase_Main(PROC* proc,int* seq);
extern PROC_RESULT PoruCase_End(PROC* proc,int* seq);

#endif	//__H_PORU_SYS_H__

