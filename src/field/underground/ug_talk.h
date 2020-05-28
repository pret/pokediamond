//=============================================================================
/**
 * @file	ug_talk.h
 * @brief	地下会話を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.12.19
 */
//=============================================================================

#ifndef _UG_TALK_H_
#define _UG_TALK_H_

#include "../fieldsys.h"  //FIELDSYS_WORK

typedef void (*pEndFunc)(int selectNo);

extern void CommUnderTalkInit(int targetID,pEndFunc func, FIELDSYS_WORK* pFSys);

extern void CommUnderTalkBind(int askID, int talkID, FIELDSYS_WORK* pFSys);

// 話しかけられのシーケンスを変更する命令が来た
extern void CommUnderTalkRecvAskSeq(int netID, int size, void* pData, void* pWork);
// 話しかけのシーケンスを変更する命令が来た
extern void CommUnderTalkRecvTalkSeq(int netID, int size, void* pData, void* pWork);
// 話しかけられのシーケンスを変更する命令が来た
extern void CommUnderTalkRecvAskSeqCall(int netID, int size, void* pData, void* pWork);
// 話しかけのシーケンスを変更する命令が来た
extern void CommUnderTalkRecvTalkSeqCall(int netID, int size, void* pData, void* pWork);
// シーケンスを変更する命令のサイズ
extern int CommUnderTalkGetSeqCommandSize(void);


//   アイテムをあげる命令が来た
extern void CommUnderTalkRecvSendItem(int netID, int size, void* pData, void* pWork);
//   アイテムをあげる命令が来た
extern void CommUnderTalkRecvSendItemCall(int netID, int size, void* pData, void* pWork);
// アイテムをあげる命令のサイズ
extern int CommUnderTalkGetSendItemSize(void);

//
extern void UgTalkRecvSecretQ(int netID, int size, void* pData, void* pWork);
// 
extern void UgTalkRecvSecretQCall(int netID, int size, void* pData, void* pWork);
//
extern int UgTalkGetSecretQSize(void);

// リセット
extern void TalkAskForceReset(void);


#endif // _UG_TALK_H_

