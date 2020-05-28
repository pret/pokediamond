
// ����


#ifndef _UG_DIG_FOSSIL_H_
#define _UG_DIG_FOSSIL_H_

#include "../fieldsys.h"

/// ���Ώ�����
extern void CommFossilInitialize(void* pWork, FIELDSYS_WORK* pFSys);
/// ���[�N�T�C�Y�擾
extern int CommFossilGetWorkSize(void);
/// �ꎞ�I�ȃ��Z�b�g
extern void CommFossilReset(void);
/// �ꎞ�I�ȕ��A
extern void CommFossilReboot(void);
/// �I������
extern void CommFossilFinalize(void);
/// �ڂ̑O�̉��΂�����
extern BOOL CommFossilCheck(int netID, Grid* pTouch);
/// ���Δ������N���C�A���g�ɕ\���{�@�邩�ǂ����₢���킹��
extern void CommFossilRecvFind(int netID, int size, void* pData, void* pWork);
/// ���@�J�n�v��
extern void CommFossilRecvDigStartReq(int netID, int size, void* pData, void* pWork);
/// ���@�J�n
extern void CommFossilRecvDigStart(int netID, int size, void* pData, void* pWork);
/// ���@�I���v��
extern void CommFossilRecvDigEndReq(int netID, int size, void* pData, void* pWork);
/// ���@�I��
extern void CommFossilRecvDigEnd(int netID, int size, void* pData, void* pWork);
/// ���@�ʒu��e�@�ɑ���
extern void CommFossilRecvDigPos(int netID, int size, void* pData, void* pWork);
/// ���Δ��@���̈ʒu�𑗂�R�}���h�̃T�C�Y
extern int CommFossilGetDigPosSize(void);
/// ���Δ��@���̈ʒu���q�@�ɍĕ��z
extern void CommFossilRecvDigPosReturn(int netID, int size, void* pData, void* pWork);
/// ���Δ��@���̈ʒu��e�@���瑗��ꍇ�̃R�}���h�̃T�C�Y
extern int CommFossilGetDigPosReturnSize(void);
/// ���΃T�[�`�^�b�`�p�l������
extern void CommFossilTouch(int netID, Grid* pTouch);
/// ���΂����邩�ǂ������ׂ�
extern BOOL UGFossileCheck(int x,int z);
/// �p�\�R�����΃��[�_�[�J�n
extern void UgFossilPcRadarStart(void);
/// �p�\�R�����΃��[�_�[�I��
extern void UgFossilPcRadarEnd(void);
/// �p�\�R�����΃��[�_�[�̊J�n������
extern void UgFossilRecvPcRadar(int netID, int size, void* pData, void* pWork);
/// �p�\�R�����΃��[�_�[�ԐM
extern void UgFossilRecvPcRadarPos(int netID, int size, void* pData, void* pWork);
/// �p�\�R�����΃��[�_�[�ԐM�T�C�Y
extern int UgFossilGetPcRadarSize(void);

/// ���t���[���s���K�v�����鏈��
extern void UgFossilProcess(void);
/// ���[�_�[�p���΂̈ʒuX���W�𓾂�
extern int UgFossilGetRadarPointX(int index);
/// ���[�_�[�p���΂̈ʒuZ���W�𓾂�
extern int UgFossilGetRadarPointZ(int index);

/// ���[�_�[�p���΂̈ʒuX���W�𓾂�
extern int UgFossilGetIntervalRadarPointX(int index);
/// ���[�_�[�p���΂̈ʒuZ���W�𓾂�
extern int UgFossilGetIntervalRadarPointZ(int index);

/// ���΂�����̎��ӂɔz�u
extern void UgFossilOneSetup(int xbase,int zbase, MATHRandContext16* pRand);

/// ���΂Ɋւ���LOG��Ԃ�
extern BOOL UgDigFossilGetActionMessage(STRBUF* pStrBuf);

extern BOOL UgDigFossilIsDig(int netID);
/// ���E�v���[���[�̃p�����[�^�[����
extern void UgDigFossilResetPlayer(int netID);
/// �������@�菉�����f�[�^��M
//extern void CommFossilRecvInit(int netID, int size, void* pData, void* pWork);
/// �������@�菉�����f�[�^���M
//extern void UgDigFossilPlayerInit(void);

// �����΂��@���Ă��邩�ǂ��� �N���C�A���g���
extern BOOL UgDigFossilIsNow(void);
// �����΂��@���Ă��邩�ǂ��� �T�[�o�[��ԂƂ��ĕۑ�
extern void UgDigFossilSetNow(int netID, int bDig);


#endif //__UG_MANAGER_H__
