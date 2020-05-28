//=============================================================================
/**
 * @file	comm_field_state.h
 * @brief	�ʐM��Ԃ��Ǘ�����T�[�r�X  �ʐM�̏�ʂɂ���
 *          �X���b�h�̂ЂƂƂ��ē����A�����̒ʐM��Ԃ⑼�̋@���
 *          �J�n��I�����Ǘ�����
 *          �t�B�[���h��Œ��ڊǗ��������̂�communication����field�Ɉړ� 2005.09.28
 * @author	Katsumi Ohno
 * @date    2005.08.08
 */
//=============================================================================

#ifndef __COMM_FIELD_STATE_H__
#define __COMM_FIELD_STATE_H__

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "savedata/undergrounddata.h"  //SECRETBASEDATA

#define COMM_HEAPSIZE_BATTLE_CHILD    (0x9000)  // �o�g���q�@�̈�
#define COMM_HEAPSIZE_BATTLE_PARENT   (0x9000)  // �o�g���e�@�̈�
#define COMM_HEAPSIZE_UNDERGROUND     (0xB000)  // �n���̈�


//==============================================================================
// extern�錾
//==============================================================================


// �n���ɓ���ꍇ�̏��� �X�e�[�g���n���p�ɕύX�����
extern void CommFieldStateEnterUnderGround(FIELDSYS_WORK* pFSys);

extern void CommFieldStateArrivalUnderGround(void);

// �n�����ł�ꍇ�̏��� �X�e�[�g�������Ȃ��ɕύX�����
extern void CommFieldStateExitUnderGround(void);
// �n����JUMP����ꍇ�̏��� �X�e�[�g��Hold��ԂɂȂ�
extern BOOL CommStateJumpUnderGround(void);
// �n����ʐM�ؒf����JUMP����ꍇ�̏��� �X�e�[�g��Hold��ԂɂȂ�
extern void CommStateExitAndJumpUnderGround(void);
// �n����ʐM�ؒf���邪�A�T�[�r�X�͎c�����܂�
extern void CommFieldStateStalthUnderGround(void);
// �n���ʐM���ĊJ
extern void CommFieldStateUnderGroundReConnect(void);

// �n����JUMP���I������ꍇ�̏��� �X�e�[�g��Active��ԂɂȂ�
extern BOOL CommStateJumpEndUnderGround(void);

// �o�g�����ɐe�ɂȂ�ꍇ�̏����J�n
extern void CommFieldStateEnterBattleParent(FIELDSYS_WORK* pFSys,int serviceNo, int regulationNo);
// �o�g�����Ɏq�ɂȂ�ꍇ�̏����J�n
extern void CommFieldStateEnterBattleChild(FIELDSYS_WORK* pFSys,int serviceNo, int regulationNo);
// �o�g�����ɐe�����߂��ۂ̎q�@�̏���
extern void CommFieldStateConnectBattleChild(int connectIndex);
// �o�g�����Ɏq�@���ċN�����鎞�̏���
extern void CommFieldStateRebootBattleChild(void);
// �o�g�����Ɉړ��ł��镔���ɓ��鎞�̏���
extern void CommFieldStateEnterBattleRoom(FIELDSYS_WORK* pFSys);
// �ړ��ʒu�ɗ������Ƃ̎�M
extern void CommDirectRecvStartPos(int netID, int size, void* pData, void* pWork);
// �ړ��ʒu�ɂ��邩�ǂ���
extern BOOL CommDirectIsMoveState(void);
// �f�[�^�R�s�[���I��������ǂ���
extern BOOL CommFieldStateIsCopyEnd(void);

// �g���[�i�[�J�[�h�{��
extern void CommDCRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork );
// �g���[�i�[�J�[�h�{��
extern u8* CommDCGetTrainerCardRecvBuff( int netID, void* pWork, int size);

// �I�������葱��
extern void CommFieldStateExitBattle(void);
// �I�������葱�� �^�C�~���O������
extern void CommFieldStateExitBattleTiming(void);

// �ړ��\�X�e�[�g�Ȃ̂��ǂ����Ԃ�
extern BOOL CommIsUnderGroundMoveState(void);

#ifdef PM_DEBUG
//
extern void CommFieldStateConnectBattleChild_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo, int connectIndex);
//
extern void CommFieldStateEnterBattleParent_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo);

#endif

extern SECRETBASEDATA* CommUgSetupSecretBaseData(SAVEDATA * sv);
extern BOOL CommFieldStateIsUnder(void);
extern void CommStateFieldUnderOptionReset(void);
extern void CommStateFieldUnderOptionReboot(void);

#endif //__COMM_FIELD_STATE_H__

