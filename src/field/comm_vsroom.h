//=============================================================================
/**
 * @file	comm_direct_counter.h
 * @bfief	�ʐM�_�C���N�g�R�[�i�[�̃J�E���^�[
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __COMM_VSROOM_H__
#define __COMM_VSROOM_H__

#include "poketool\pokeparty.h"

typedef void (StartLineCallBack)(BOOL bStart, const POKEPARTY* party);

/// ��ʒu�ɂ������̃C�x���g
extern void EventCmd_StartLine(FIELDSYS_WORK* pFSys,StartLineCallBack* pCallBack);
/// �g���[�i�[�Ƃ̉�b
extern void EventCmd_VSRoomTrainer(FIELDSYS_WORK* pFSys);



// �~�b�N�X�o�g���p�f�[�^�ʐM�֐��Q
extern void CommMixBattleRecv(int netID, int size, void* pBuff, void* pWork);
extern int  CommMixBattleGetDataSize( void );
extern u8* CommMixBattleGetBuffer( int netID, void* pWork, int size );
extern void CommMixBattleTradeRecv( int netID, int size, void* pBuff, void* pWork );

#endif  // __COMM_VSROOM_H__
