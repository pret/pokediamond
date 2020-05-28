//=============================================================================
/**
 * @file	ug_bag.h
 * @brief	�n��������Ǘ�����N���X
 * @author	Katsumi Ohno
 * @date    2005.12.21
 */
//=============================================================================

#ifndef _UG_BAG_H_
#define _UG_BAG_H_

#include "../fieldsys.h"  //FIELDSYS_WORK
#include "savedata/undergrounddata.h"  //UNDERGROUNDDATA

typedef void (*pBagEndFunc)(int selectNo);

extern void CommUnderBagInitialize(UNDERGROUNDDATA* pUGData);
extern void CommUnderBagFinalize(void);
extern void CommUnderBagInit(pBagEndFunc func, FIELDSYS_WORK* pFSys);
extern void CommUnderBagDeleteTrap(int type);
extern void CommUnderBagDeleteStone(int type);

// �o�b�O�ɂ��܂�����
extern BOOL CommUnderBagAddStone(int no, int carat);
// ����������o�b�O�ɓ����
extern BOOL CommUnderBagAddTreasure(int no);
// 㩂����΂�ɒǉ�
extern BOOL CommUnderBagAddTrap(int no);
// ���󂩃^�}���𕪗ނ��ăo�b�O�ɓ����
extern BOOL CommUnderBagAddFossil(int no);
// GOODS�����΂�ɓ����
extern BOOL CommUnderBagAddGoods(int no);
//GOOS���j���[���J��
extern void* UgBagGoodsMenuStart(pBagEndFunc func, FIELDSYS_WORK* pFSys);
// GOODS���o�b�O�������
extern void UgBagDeleteGoods(int type);

// �������E�C���h�E
extern void CommUnderBagFlagStart(pBagEndFunc func, FIELDSYS_WORK* pFSys);



/// ���X�̑I��
extern int UgShopSelectMenuFuncAndCheck(void* pWork);
/// ���X�̑I���J�n
extern void* UgShopSelectMenuInit( BOOL bTrapShop, FIELDSYS_WORK* pFSys );
/// �n���̂��X�̃��j���[���J��
extern void* UgShopMenuInit(BOOL bTrapShop, FIELDSYS_WORK* pFSys);
extern void* UgShopMenuInit2(BOOL bTrapShop, FIELDSYS_WORK* pFSys,int no);
/// �n���̂��X�̃��j���[���J��
///extern void* UgShopMenuInit_New(BOOL bTrapShop, BOOL bBuy, FIELDSYS_WORK* pFSys);
/// �n���̂��X�̃��j���[�̏�Ԃ𓾂�
extern int UgShopMenuFuncAndCheck(void* pWork);

#include "ug_def.h"


/// ���X�̉�b�J�n
extern int UgShopTalkStart(int messageNo);
/// ���X�̉�b�I��
extern void UgShopTalkEnd(void);
/// �A�C�e���̖��O�����X�̉�b�ɓo�^
extern void UgShopTalkRegisterItemName(int index,int type);
/// 㩂̖��O�����X�̉�b�ɓo�^
extern void UgShopTalkRegisterTrapName(int index,int type);
/// �O�b�Y�̖��O�����X�̉�b�ɓo�^
extern void UgShopTalkRegisterGoodsName(int index,int type);

/// �����I�ɏ���
extern void UgGoodsMenuForceDelete(void* work,u32 ret);
/// �����I�ɏ��� �����Ⴄ�����g�͓���
extern void UgGoodsMenuForceDelete2(TCB_PTR pTCB, void* work);


#endif // _UG_BAG_H_

