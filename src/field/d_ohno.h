//=============================================================================
/**
 * @file	d_ohno.h
 * @bfief	���p�f�o�b�O���[�`��
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __D_OHNO_H__
#define __D_OHNO_H__
#ifdef PM_DEBUG


// �f�o�b�O�p�ɌĂяo���ŏ��̊֐��B���j���[���J������
extern void DebugCommMenuInit(void* pFSys);

// �`�����l���\��������E�C���h�E���o�����ǂ���
extern BOOL DebugOhnoGetCommDebugDisp(void);
extern void DebugOhnoCommDebugDisp(void* pDummy);

// �n���ڑ����f�o�b�O�̈חׂƂȂ���Ȃ��悤�ɂ���
extern void DebugOhnoCommDebugUnderNo(int no);
// �傫���f�[�^�̃e�X�g
extern void CommDebugRecvHugeData(int netID, int size, void* pData, void* pWork);

//�e�@�����A�q�@�����̐ڑ�
extern void DebugOhnoCommDebugUnderParentOnly(int no);
extern void DebugOhnoCommDebugUnderChildOnly(int no);


#endif//PM_DEBUG
#endif //__D_OHNO_H__
