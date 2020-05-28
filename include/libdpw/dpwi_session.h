/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_session.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	session manager
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#ifndef _DPWI_COMMON_SESSION_H_
#define _DPWI_COMMON_SESSION_H_

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/

//!< �Z�b�V�����X�e�[�^�X
typedef enum{
	DPWI_COMMON_SESSION_STATE_CANCELED,			//!< �L�����Z��
	DPWI_COMMON_SESSION_STATE_ERROR,			//!< �G���[����<
	DPWI_COMMON_SESSION_STATE_INITIAL,			//!< �������
	DPWI_COMMON_SESSION_STATE_REQUEST,			//!< ���N�G�X�g���s
	DPWI_COMMON_SESSION_STATE_GETTING_TOKEN,	//!< �g�[�N���擾��
	DPWI_COMMON_SESSION_STATE_GOT_TOKEN,		//!< �g�[�N���擾����
	DPWI_COMMON_SESSION_STATE_SENDING_DATA,		//!< �f�[�^���M��
	DPWI_COMMON_SESSION_STATE_COMPLETED			//!< ����
}DpwiSessionState;

//!< �֐��Ԃ�l
typedef enum{

	DPWI_COMMON_SESSION_SUCCESS,				//!< ����I��
	DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED,	//!< ��������
	DPWI_COMMON_SESSION_ERROR_NOMEMORY			//!< �������[�s��

}DpwiSessionResult;

typedef enum{

	DPWI_COMMON_SESSION_ERROR_IN_ERROR,				//!<  0: �G���[������ 
	DPWI_COMMON_SESSION_ERROR_INVALID_POST,			//!<  1: �����ȑ��M 
	DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY,	//!<  2: �������s�� 
	DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME,	//!<  3: �����ȃt�@�C���� 
	DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE,	//!<  4: �����ȃo�b�t�@�T�C�Y 
	DPWI_COMMON_SESSION_ERROR_INVALID_URL,			//!<  5: ������URL
	DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR,	//!<  6: ���̑��̃G���[

	DPWI_COMMON_SESSION_ERROR_SUCCESS,				//!<  7: �t�@�C���擾���� 
	DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY,		//!<  8: ���������蓖�Ď��s 
	DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW,		//!<  9: �������ꂽ�o�b�t�@�����������邽�߁A�t�@�C���̎擾���s 
	DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED,		//!< 10: URL��̓G���[ 
	DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED,	//!< 11: �z�X�g���������s 
	DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED,		//!< 12: �\�P�b�g�̍쐬�A�������A�ǂݏo���A�������ݎ��s 
	DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED,		//!< 13: HTTP�T�[�o�ւ̐ڑ����s 
	DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE,			//!< 14: HTTP�T�[�o����̃��X�|���X�̉�̓G���[ 
	DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED,		//!< 15: HTTP�T�[�o�̃��N�G�X�g���� 
	DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED,			//!< 16: �t�@�C���擾������ 
	DPWI_COMMON_SESSION_ERROR_FORBIDDEN,			//!< 17: HTTP�T�[�o�̃t�@�C�����M���� 
	DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND,		//!< 18: HTTP�T�[�o��̃t�@�C���������s 
	DPWI_COMMON_SESSION_ERROR_SERVER_ERROR,			//!< 19: HTTP�T�[�o�����G���[ 
	DPWI_COMMON_SESSION_ERROR_FILE_WRITE_FAILED,	//!< 20: ���[�J���t�@�C���ւ̏������݃G���[ 
	DPWI_COMMON_SESSION_ERROR_FILE_READ_FAILED,		//!< 21: ���[�J���t�@�C������̓ǂݏo���G���[ 
	DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE,		//!< 22: �_�E�����[�h�̒��f 
	DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG,			//!< 23: �t�@�C�����傫�����邽�߃_�E�����[�h�s�\ 
	DPWI_COMMON_SESSION_ERROR_ENCRYPTION_ERROR,		//!< 24: �Í����G���[ 
	DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR,			//!< 25: ���������蓖�Ď��s 

	DPWI_COMMON_SESSION_ERROR_CHECKSUM,				//!< 26: COMMON�w: �`�F�b�N�T���̕s��v
	DPWI_COMMON_SESSION_ERROR_PID,					//!< 27: COMMON�w: PID�̕s��v
	DPWI_COMMON_SESSION_ERROR_DATA_LENGTH, 			//!< 28: COMMON�w: �f�[�^�̒������s��
	DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND,		//!< 29: COMMON�w: �g�[�N�����Ȃ�
	DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED,		//!< 30: COMMON�w: �g�[�N���̗L�������؂�
	DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH,		//!< 31: COMMON�w: �n�b�V��������Ȃ�
	DPWI_COMMON_SESSION_ERROR_BUFFER_OVER			//!< 32: COMMON�w: ��M�o�b�t�@���I�[�o�[����

}DpwiHttpError;

/*-----------------------------------------------------------------------*
					�֐��v���g�^�C�v�錾
 *-----------------------------------------------------------------------*/

void DpwiSessionInitialize( void );
void DpwiSessionShutdown( void );
void DpwiSessionCancel( void );
DpwiSessionState DpwiSessionThink( void );
DpwiSessionResult DpwiSessionRequest(	const u8* url,
										int pid,
										const void* data,
										int len,
										u8* resbuf,
										int buflen );
DpwiHttpError DpwiGetLastError( void );
int DpwiGetResponseSize( void );


#ifdef __cplusplus
}
#endif

#endif
