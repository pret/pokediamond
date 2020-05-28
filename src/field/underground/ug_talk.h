//=============================================================================
/**
 * @file	ug_talk.h
 * @brief	�n����b���Ǘ�����N���X
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

// �b���������̃V�[�P���X��ύX���閽�߂�����
extern void CommUnderTalkRecvAskSeq(int netID, int size, void* pData, void* pWork);
// �b�������̃V�[�P���X��ύX���閽�߂�����
extern void CommUnderTalkRecvTalkSeq(int netID, int size, void* pData, void* pWork);
// �b���������̃V�[�P���X��ύX���閽�߂�����
extern void CommUnderTalkRecvAskSeqCall(int netID, int size, void* pData, void* pWork);
// �b�������̃V�[�P���X��ύX���閽�߂�����
extern void CommUnderTalkRecvTalkSeqCall(int netID, int size, void* pData, void* pWork);
// �V�[�P���X��ύX���閽�߂̃T�C�Y
extern int CommUnderTalkGetSeqCommandSize(void);


//   �A�C�e���������閽�߂�����
extern void CommUnderTalkRecvSendItem(int netID, int size, void* pData, void* pWork);
//   �A�C�e���������閽�߂�����
extern void CommUnderTalkRecvSendItemCall(int netID, int size, void* pData, void* pWork);
// �A�C�e���������閽�߂̃T�C�Y
extern int CommUnderTalkGetSendItemSize(void);

//
extern void UgTalkRecvSecretQ(int netID, int size, void* pData, void* pWork);
// 
extern void UgTalkRecvSecretQCall(int netID, int size, void* pData, void* pWork);
//
extern int UgTalkGetSecretQSize(void);

// ���Z�b�g
extern void TalkAskForceReset(void);


#endif // _UG_TALK_H_

