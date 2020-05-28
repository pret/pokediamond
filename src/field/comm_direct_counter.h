//=============================================================================
/**
 * @file	comm_direct_counter.h
 * @bfief	�ʐM�_�C���N�g�R�[�i�[�̃J�E���^�[
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __COMM_DIRECT_COUNTER_H__
#define __COMM_DIRECT_COUNTER_H__

#include "comm_direct_counter_def.h"
#include "battle/battle_common.h"

//==============================================================================
// extern�錾
//==============================================================================
/// �ʐM�_�C���N�g�R�[�i�[�̃J�E���^�̃��j���[
extern void CommDirectCounterMenu(FIELDSYS_WORK* pFSys);


/// �e�@�I���E�C���h�E���J��
extern void CommSelectParentWindowOpen(FIELDSYS_WORK* pFSys,
                                       int connectMode,int type1,int type2);
/// �e�@�I���E�C���h�E����������
extern u32 CommSelectParentWindowCheck(void);

/// �q�@�ꗗ�E�C���h�E���J��
extern void CommChildWindowOpen(FIELDSYS_WORK* pFSys,
                                int connectMode,int type1,int type2);
/// �q�@�ꗗ�E�C���h�E���Ď�����
extern u32 CommChildWindowCheck(void);

extern void CommChildListWindowOpen(void);
extern void CommParentSelectParentWindowOpen(void);

/// �ʐM�_�C���N�g���[���ɓ��������̏���
extern void CommDirectEnterBattleRoom(FIELDSYS_WORK* pFSys);
/// �ʐM�_�C���N�g���[���̏������������I��������ǂ���
extern BOOL CommDirectIsRoomInitialize(void);
/// �ʐM�_�C���N�g�R�[�i�[�̏I���������J�n����
extern void CommDirectEnd(void);
// �o�g���p�����[�^�Z�b�g
extern BATTLE_PARAM* DirectCounter_BattleParamSet(FIELDSYS_WORK* fsys);




#ifdef PM_DEBUG
///   �f�o�b�O�p�_�C���N�g�R�[�i�[�e�@�ڑ�
extern void CommDirectParent_Debug(FIELDSYS_WORK* pFSys);
///   �f�o�b�O�p�_�C���N�g�R�[�i�[�q�@�ڑ�
extern void CommDirectChild_Debug(FIELDSYS_WORK* pFSys);
/// �f�o�b�O�p�_�C���N�g�R�[�i�[�ڑ�����
extern void CommDirectConnect_Debug(void);
/// �f�o�b�O�p�_�C���N�g�R�[�i�[�������p�����[�^�ݒ�
extern void CommDirectConnectSetParam_Debug(FIELDSYS_WORK* pFSys, int gameMode, int type1, int type2);
#endif

#endif  // __COMM_DIRECT_COUNTER_H__
