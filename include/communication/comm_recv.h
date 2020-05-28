//=============================================================================
/**
 * @file	comm_recv.h
 * @brief	�S���̃f�[�^���܂Ƃ߂Č����������ꍇ�����ɋL�q���܂�
 * @author	Katsumi Ohno
 * @date    2005.07.12
 */
//=============================================================================


#ifndef _COMM_RECV_H_
#define _COMM_RECV_H_

//==============================================================================
// extern�錾
//==============================================================================

/// ���r�[�𔲂��閽�߂��������ǂ���
extern BOOL CommRecvIsExitRobby(void);
/// �I���L�����Z������M
extern BOOL CommRecvIsExitCancel(void);
/// �I������M
extern BOOL CommRecvIsExit(void);
/// �S���̏I������M
extern BOOL CommRecvIsExitAll(void);
/// �S�����Q�X�g���[���ɍs�����Ƃ���������
extern BOOL CommRecvIsPleaseGuestRoomAll(void);
/// �I���R�}���h����M�����烂�[�h�ɉ����ď������s�������ؒf����
extern void CommAutoExitCommandFunc(void);
/// �����I���R�}���h��M
extern void CommRecvAutoExit(int netID, int size, void* pData, void* pWork);



#endif //_COMM_RECV_H_
