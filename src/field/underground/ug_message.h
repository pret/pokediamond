//=============================================================================
/**
 * @file	comm_message.h
 * @brief	通信用 メッセージを簡単に扱うためのクラス
 * @author	k.ohno
 * @date    2006.02.05
 */
//=============================================================================

#ifndef __UG_MESSAGE_H__
#define __UG_MESSAGE_H__

#include "savedata/mystatus.h"
#include "gflib/msg_print.h"	// STRCODE 定義のため
#include "system/msgdata.h" //MSGDATA_MANAGER
#include "gflib/bg_system.h" //GF_BGL_INI
#include "gflib/strbuf.h" //STRBUF
#include "system/bmp_list.h" //BMPLISTHEADER

//--------------------------------------------------------------
//   typedef
//--------------------------------------------------------------

typedef struct _COMM_MESSAGE COMM_MESSAGE;

typedef void (*PTRCommMsgCallback)(int num);


#define COMM_MESFRAME_PAL     ( 10 )         //  メッセージウインドウ
#define COMM_MENUFRAME_PAL    ( 11 )         //  メニューウインドウ
#define COMM_MESFONT_PAL      ( 12 )         //  メッセージフォント
#define COMM_SYSFONT_PAL	  ( 13 )         //  システムフォント

// 会話ウィンドウ
#define	COMM_TALK_WIN_CGX_SIZE	( 18+12 )
#define	COMM_TALK_WIN_CGX_NUM	( 512 - COMM_TALK_WIN_CGX_SIZE)
#define	COMM_MSG_WIN_PX		( 2 )
#define	COMM_MSG_WIN_PY		( 19 )
#define	COMM_MSG_WIN_SX		( 27 )
#define	COMM_MSG_WIN_SY		( 4 )
#define	COMM_MSG_WIN_PAL		( COMM_MESFONT_PAL )
#define	COMM_MSG_WIN_CGX		( (COMM_TALK_WIN_CGX_NUM - 73) - ( COMM_MSG_WIN_SX * COMM_MSG_WIN_SY ) )



//--------------------------------------------------------------
// function
//--------------------------------------------------------------

extern COMM_MESSAGE* CommMsgInitialize(int msgManagerNo,int heapID, GF_BGL_INI* bgl,int speed, int msgSize);
extern void CommMsgSetBgl(COMM_MESSAGE* pComm,GF_BGL_INI* bgl);
extern void CommMsgFinalize(COMM_MESSAGE* pComm);
extern void CommMsgChangeMSGMAN(COMM_MESSAGE* pComm, int msgManagerNo, int type);
extern MSGDATA_MANAGER* CommMsgGetMsgManager(COMM_MESSAGE* pComm);

extern int CommMsgTalkWindowAllWrite(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack);
extern int CommMsgTalkWindowStart(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack);
extern int CommMsgTalkWindowStartSendNum(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack, int callbackNum);
//extern int CommMsgTalkWindowStartBuff(COMM_MESSAGE* pComm, STRBUF* pStrBuf, BOOL bTask,  PTRCommMsgCallback pEndCallBack);
extern void CommMsgTalkWindowEnd(COMM_MESSAGE* pComm);
extern void CommMsgTalkWindowMeWait(COMM_MESSAGE* pComm);

extern STRBUF* CommMsgGetExpandStrBuf(COMM_MESSAGE* pComm, int msgNo);

// レジスターに単語登録するための関数群
extern void CommMsgRegisterMyName(COMM_MESSAGE* pComm, MYSTATUS* pMy);
extern void CommMsgRegisterTargetName(COMM_MESSAGE* pComm, MYSTATUS* pTarget);
extern void CommMsgRegisterUGItemName(COMM_MESSAGE* pComm,int type);
extern void CommMsgRegisterUGTrapName(COMM_MESSAGE* pComm,int type);
extern void CommMsgRegisterSecretQuestionName(COMM_MESSAGE* pComm,int type);
extern void CommMsgRegisterSecretAnswerNameIndex(COMM_MESSAGE* pComm,int index,int type);
extern void CommMsgRegisterSecretAnswerName(COMM_MESSAGE* pComm,int type);
extern void CommMsgRegisterUGGoodsName(COMM_MESSAGE* pComm,int type);
extern void CommMsgRegisterNumber1Index(COMM_MESSAGE* pComm,int index,int num);
extern void CommMsgRegisterNumber2(COMM_MESSAGE* pComm,int num);
extern void CommMsgRegisterNumber2Index(COMM_MESSAGE* pComm,int index,int num);
extern void CommMsgRegisterNumber5(COMM_MESSAGE* pComm,int num);
extern void CommMsgRegisterNumber6(COMM_MESSAGE* pComm,int num);
extern void CommMsgRegisterUGItemNameIndex(COMM_MESSAGE* pComm,int index,int type);
extern void CommMsgRegisterUGTrapNameIndex(COMM_MESSAGE* pComm,int index,int type);
extern void CommMsgRegisterUGGoodsNameIndex(COMM_MESSAGE* pComm,int index,int type);
extern void CommMsgPrintStop(COMM_MESSAGE* pComm);

extern const BMPLIST_HEADER* CommMsgGetNormalBmpListHeader(void);
extern BOOL CommMsgIsOutputing(COMM_MESSAGE* pComm);
extern void CommMsgFunc(COMM_MESSAGE* pComm);



#endif //__UG_MESSAGE_H__
