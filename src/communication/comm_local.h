//=============================================================================
/**
 * @file	comm_local.h
 * @brief	�ʐM�N���X�݂̂ŎQ�Ƃ������\���̂ƃ��\�b�h��������Ă���.h
 * @author	Katsumi Ohno
 * @date    2005.07.12
 */
//=============================================================================
#ifndef _COMM_LOCAL_
#define _COMM_LOCAL_

#include "communication/comm_ring_buff.h"

//==============================================================================
// ��`
//==============================================================================
#define _COMM_RECV_BACKUP_NUM   (2)  ///< �ʐM��1/60�Ȃ̂� 60/30����M�f�[�^��~����K�v������

#define _DEFAULT_TIMEOUT_FRAME (30*5) ///< �ʐM�����̃^�C���A�E�g���Ԃ̃f�t�H���g

#define _SCAN_ALL_CHANNEL  (0)  ///< �X�L��������`�����l���������_���ōs���ꍇ�O�ɐݒ肷��

// �ʐM�T�[�r�X�̍ő�q�@�䐔
extern u16 CommLocalGetServiceMaxEntry(u16 serviceNo);
// �ʐM�T�[�r�X�̍ŏ��q�@�䐔
extern u16 CommLocalGetServiceMinEntry(u16 serviceNo);

// �f�o�b�O�p�R�}���h�v�����g
#define _COMMAND_TEST  (0)

#endif //_COMM_SHARING_LOCAL_

