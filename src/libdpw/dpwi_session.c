/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_session.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DPW internal session module
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#include <dwc.h>
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_encrypt.h"

#ifdef _NITRO
#include "include/libdpw/dpwi_define.h"
#endif

#ifndef _NITRO
	#include "include/libdpw/dpwi_sha1.h"
#endif

/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/

#define HASH_LENGTH		40								// �n�b�V���̒���
#define TOKEN_LENGTH	32								// �g�[�N���̒���
#define KEY_LENGTH		20								// �閧���̒���
#define KEYTOKEN_LENGTH		(TOKEN_LENGTH + KEY_LENGTH + 1)	// �閧���{�g�[�N��

#define SECRET_KEY		"sAdeqWo3voLeC5r16DYv"			// �閧��

#define COMMON_ERROR_MSG_LENGTH		22

#define COMMON_ERROR_CHECKSUM			"error: check sum      "
#define COMMON_ERROR_PID				"error: pid            "
#define COMMON_ERROR_DATA_LENGTH 		"error: data length    "
#define COMMON_ERROR_TOKEN_NOT_FOUND 	"error: token not found"
#define COMMON_ERROR_TOKEN_EXPIRED		"error: token expired  "
#define COMMON_ERROR_INCORRECT_HASH		"error: incorrect hash "

/*-----------------------------------------------------------------------*
					�O���[�o���ϐ���`
 *-----------------------------------------------------------------------*/


/**
 * 
 * �Z�b�V��������ێ�����\���̕ϐ�
 * 
 * [  base url ]?pid=[-----]&hash=[-----]&data=[-----------------------]
 * |                              |            |
 * |<- *request                   |<- *hash    |<- *data
 * 
 */

struct{

	DpwiSessionState	state;

	int		reqid;		//!< ���N�G�X�g���ʎq
	int		lasterr;	//!< ���X�g�G���[
	int		reslen;		//!< ���X�|���X�̃f�[�^�T�C�Y

	int		pid;		//!< PID

	void*	srcbuf;		//!< ���M�f�[�^�o�b�t�@�̃|�C���^
	int		srcbuflen;	//!< ���M�f�[�^�o�b�t�@�̃T�C�Y
	void*	resbuf;		//!< ���X�|���X�f�[�^�i�[�o�b�t�@�̃|�C���^
	int		resbuflen;	//!< ���X�|���X�f�[�^�i�[�o�b�t�@�̃T�C�Y

	char*	request;	//!< ���N�G�X�g������
	char*	hash;		//!< ���N�G�X�g�����񒆂̃n�b�V���ʒu
	char*	data;		//!< ���N�G�X�g�����񒆂̃f�[�^�ʒu
	int		datasize;	//!< data�̃T�C�Y

}g_session = { DPWI_COMMON_SESSION_STATE_ERROR, 0, 0, 0 };


static void setlasterror( int err ){

	switch( err ){
	// �G���[������
	case DWC_GHTTP_IN_ERROR:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_IN_ERROR;
		break;
	// �����ȑ��M
	case DWC_GHTTP_INVALID_POST:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_POST;
		break;
	// �������s��
	case DWC_GHTTP_INSUFFICIENT_MEMORY:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY;
		break;
	// �����ȃt�@�C����
	case DWC_GHTTP_INVALID_FILE_NAME:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME;
		break;
	// �����ȃo�b�t�@�T�C�Y
	case DWC_GHTTP_INVALID_BUFFER_SIZE:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE;
		break;
	// ������URL
	case DWC_GHTTP_INVALID_URL:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INVALID_URL;
		break;
	// ���̑��̃G���[
	case DWC_GHTTP_UNSPECIFIED_ERROR:
		g_session.lasterr = DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR;
		break;
	// ����
	default:
		g_session.lasterr = 0;
	}

}

// �����R�[���o�b�N�֐�
static void Completed(	const char* buf,
						int len,
						DWCGHTTPResult result,
						void* param )
{
#pragma unused(param)
	
	// GHTTP�̏������s���Ă��Ȃ����Ƃ������t���O�𗧂Ă�
	g_session.reqid = -1;
	
	// �X�e�[�g���G���[��������I��
	//
	if( g_session.state == DPWI_COMMON_SESSION_STATE_ERROR ){

		return;

	}

	
	// HTTP�ʐM�̌��ʂ�����
	//
	// HTTP GET 200 �̃��X�|���X�̂ݏ���
	// ����ȊO 404��500�ł̓G���[�𔭐����ďI������
	// 
	if ( result == DWC_GHTTP_SUCCESS ){

		switch( g_session.state ){

		// �g�[�N���擾
		//-------------------
		case DPWI_COMMON_SESSION_STATE_GETTING_TOKEN:

			// �g�[�N���̃T�C�Y�����������ǂ���
			//
			// ��������΃n�b�V�������߁A�f�[�^���Í������Ď��̒ʐM���s������
			// ������B
			// 
			if(len == TOKEN_LENGTH){

				//
				// �������[���݂݂������ߖ񂷂�݌v�Ȃ̂ł킩��ɂ����E�E�E
				//
				int i;										// ���[�v�J�E���^
				u8* hashtmp = (u8*)(g_session.hash + 20);	// �n�b�V���ꎞ�̈�
				char data[KEYTOKEN_LENGTH];					// �閧���{�g�[�N��
				DpwiEncResult res;							// �Í�������
				const char hextbl[] = "0123456789abcdef";	// hex�ϊ��e�[�u��

				// �閧�����i�[
				strcpy( data, SECRET_KEY );

				// �g�[�N����A��
				strncat( data, buf, (u32)len );
				
				// �n�b�V���v�Z
				MATH_CalcSHA1((u8*)hashtmp, (const u8*)data, strlen(data));

				// �p�����[�^�[���ǉ�
				// 
				// ���̎��_�ł�request�ɂ�"*?pid=****"�܂ŏ�����Ă���
				// 
				strcat( g_session.request, "&hash=" );

				// hex�ϊ�
				//
				// �������ݐ��g_session.request����"hash="�̌�40bytes
				// 
				for(i=0; i<20; i++){
					g_session.hash[i*2]   = hextbl[hashtmp[i] >> 4];
					g_session.hash[i*2+1] = hextbl[hashtmp[i] & 0x0f];
				}
				g_session.hash[HASH_LENGTH] = '\0';

				// URL�ɂȂ�
				strcat( g_session.request, "&data=" );


				// ���M�f�[�^�̈Í���
				// 
				// �Í������ꂽ�f�[�^��g_session.request�ɒ��������
				//
				res = DpwiEncrypt(	(u32)g_session.pid,
									(u8 *)g_session.srcbuf,
									g_session.srcbuflen,
									(u8 *)g_session.data,
									g_session.datasize );

				switch(res){

				// ����
				case DPWI_COMMON_ENC_SUCCESS:
					break;

				// �������[�s���G���[
				case DPWI_COMMON_ENC_ERROR_NOMEMORY:
				case DPWI_COMMON_ENC_ERROR_NOBUFFER:

					// �G���[
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

					return;
				}

				// ���̃X�e�[�g��
				//
				// -> �g�[�N���擾�����X�e�[�g
				// 
				g_session.state = DPWI_COMMON_SESSION_STATE_GOT_TOKEN;

			}else{

				// �G���[
				g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

			}

			break;


		// �f�[�^���M����
		//-------------------
		case DPWI_COMMON_SESSION_STATE_SENDING_DATA:

			// ���X�|���X���擾
			//
			
			// �G���[���ǂ����`�F�b�N
			if( len == COMMON_ERROR_MSG_LENGTH ){

				if( strncmp(buf, COMMON_ERROR_CHECKSUM, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_CHECKSUM;
					break;
				} else if (strncmp(buf, COMMON_ERROR_PID, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_PID;
					break;
				} else if (strncmp(buf, COMMON_ERROR_DATA_LENGTH, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_DATA_LENGTH;
					break;
				} else if (strncmp(buf, COMMON_ERROR_TOKEN_NOT_FOUND, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND;
					break;
				} else if (strncmp(buf, COMMON_ERROR_TOKEN_EXPIRED, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED;
					break;
				} else if (strncmp(buf, COMMON_ERROR_INCORRECT_HASH, COMMON_ERROR_MSG_LENGTH) == 0 ){
					g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
					g_session.lasterr = DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH;
					break;
				}
			}

			// ���X�|���X�o�b�t�@�Ɏ��܂邩���`�F�b�N
			// 
			if( len <= g_session.resbuflen ){

				// �R�s�[
				memcpy(g_session.resbuf, buf, (u32)len);

				// �I���X�e�[�g��
				g_session.state = DPWI_COMMON_SESSION_STATE_COMPLETED;

			}else{

				// ���X�|���X���i�[����o�b�t�@�T�C�Y������Ȃ�
				//
				// �ꉞ�������߂邾����������
				// �S���������߂Ȃ������G���[�͕Ԃ�
				//

				// �o�b�t�@�T�C�Y�������R�s�[
				memcpy(g_session.resbuf, buf, (u32)g_session.resbuflen );

				// �G���[�X�e�[�g��
				g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
				g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BUFFER_OVER;
			}

			// ���X�|���X�̃T�C�Y��ێ�
			g_session.reslen = len;

			break;

		}

	}else{

		// HTTP�G���[
		//
		g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		// �G���[�R�[�h�𔻕�
		switch ( result ){
		// ���������蓖�Ď��s
		case DWC_GHTTP_OUT_OF_MEMORY:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY;
			break;
		// �������ꂽ�o�b�t�@�����������邽�߁A�t�@�C���̎擾���s 
		case DWC_GHTTP_BUFFER_OVERFLOW:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW;
			break;
		// URL��̓G���[
		case DWC_GHTTP_PARSE_URL_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED;
			break;
		// �z�X�g���������s
		case DWC_GHTTP_HOST_LOOKUP_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED;
			break;
		// �\�P�b�g�̍쐬�A�������A�ǂݏo���A�������ݎ��s 
		case DWC_GHTTP_SOCKET_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED;
			break;
		// HTTP�T�[�o�ւ̐ڑ����s 
		case DWC_GHTTP_CONNECT_FAILED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED;
			break;
		// HTTP�T�[�o����̃��X�|���X�̉�̓G���[ 
		case DWC_GHTTP_BAD_RESPONSE:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE;
			break;
		// HTTP�T�[�o�̃��N�G�X�g���� 
		case DWC_GHTTP_REQUEST_REJECTED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED;
			break;
		// �t�@�C���擾������ 
		case DWC_GHTTP_UNAUTHORIZED:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED;
			break;
		// HTTP�T�[�o�̃t�@�C�����M���� 
		case DWC_GHTTP_FORBIDDEN:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FORBIDDEN;
			break;
		// HTTP�T�[�o��̃t�@�C���������s 
		case DWC_GHTTP_FILE_NOT_FOUND:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND;
			break;
		// HTTP�T�[�o�����G���[
		case DWC_GHTTP_SERVER_ERROR:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_SERVER_ERROR;
			break;
		// �_�E�����[�h�̒��f
		case DWC_GHTTP_FILE_INCOMPLETE:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE;
			break;
		// �t�@�C�����傫�����邽�߃_�E�����[�h�s�\ 
		case DWC_GHTTP_FILE_TOO_BIG:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG;
			break;
		// �������[�G���[
		case DWC_GHTTP_MEMORY_ERROR:
			g_session.lasterr = DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR;
			break;
		}
		
	}

}


/*!
	�Z�b�V���������������܂�
	
	
*/
void DpwiSessionInitialize( void ){

	// �X�e�[�^�X�t���O���Z�b�g
	g_session.state = DPWI_COMMON_SESSION_STATE_INITIAL;
	g_session.reqid = -1;

	// ������
	if ( !DWC_InitGHTTP(NULL) ){

		// GHTTP�̏������Ɏ��s
		g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

	}

	return;

}


/*!
	���N�G�X�g�𔭍s���܂�
	
	�Z�b�V�������m�����āA�f�[�^�𑗐M���A���X�|���X����M���܂��B
	
	@param[in]		url		�X�N���v�g��URL
	@param[in]		pid		GameSpy Profile ID
	@param[in]		data	���M����f�[�^
	@param[in]		len		data�̃T�C�Y
	@param[in]		resbuf	���X�|���X���󂯎�邽�߂̃o�b�t�@
	@param[in]		buflen	resbuf�̃T�C�Y

	@retval	DPWI_COMMON_SESSION_SUCCESS					����
	@retval	DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED	��������
	@retval	DPWI_COMMON_SESSION_ERROR_NOMEMORY			�������[�s��

*/
DpwiSessionResult DpwiSessionRequest(	const u8* url,
										int pid,
										const void* data,
										int len,
										u8* resbuf,
										int ressize ){


	// �������`�F�b�N
	if( g_session.state != DPWI_COMMON_SESSION_STATE_INITIAL )
		return DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED;

	// �e��ϐ���ێ�
	g_session.pid		= pid;
	g_session.srcbuf	= (void*)data;
	g_session.srcbuflen	= len;
	g_session.resbuf	= resbuf;
	g_session.resbuflen	= ressize;

	// ���N�G�X�g������p�������[���m��
	// ( baseurllen + param[pid] + param[hash] + base64data + few more )
	g_session.request = (char*)DWC_Alloc( (DWCAllocType)DPWI_ALLOC,
									strlen((const char*)url)
									+ 68 + DpwiB64Size(8 + (u32)len) + 1);
	if( g_session.request == NULL )
		return DPWI_COMMON_SESSION_ERROR_NOMEMORY;

	// �x�[�X�t�q�k��PID�����N�G�X�g�Ɋi�[
	sprintf( g_session.request, "%s?pid=%d", url, pid );

	// �p�����[�^�[�̃I�t�Z�b�g��ێ�
	//
	// �������[�ߖ�̂��߂ɓ���o�b�t�@�̃|�C���^��ێ�����
	// 
	g_session.hash	= g_session.request + strlen(g_session.request)
						+ strlen("&hash=");
	g_session.data	= g_session.hash + HASH_LENGTH + strlen("&data=");
	g_session.datasize = (int)(DpwiB64Size(8 + (u32)len) + 1);


	// �J�n
	g_session.state = DPWI_COMMON_SESSION_STATE_REQUEST;

	return DPWI_COMMON_SESSION_SUCCESS;
}


/*!
	�񓯊�������i�߂܂�

	@return	�Z�b�V�����̃X�e�[�^�X
*/
DpwiSessionState DpwiSessionThink( void ){

	BOOL result;

	switch( g_session.state ){

	// �L�����Z�����ꂽ
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_CANCELED:
		break;

	// �G���[
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_ERROR:
		break;

	// ��������
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_INITIAL:
		break;

	// ���N�G�X�g��������
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_REQUEST:

		// �g�[�N���擾���N�G�X�g���M
		g_session.reqid = DWC_GetGHTTPData(	g_session.request,
											Completed,
											&g_session );

		setlasterror( g_session.reqid );

		if( g_session.reqid >= 0 )
			g_session.state = DPWI_COMMON_SESSION_STATE_GETTING_TOKEN;
		else
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		break;
	
	// �g�[�N���擾��
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_GETTING_TOKEN:

		result = DWC_ProcessGHTTP();

		if( !result ){
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
			break;
		}

		break;

	// �g�[�N���擾����
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_GOT_TOKEN:

		// �f�[�^���M���N�G�X�g���M
		g_session.reqid = DWC_GetGHTTPData(	g_session.request,
											Completed,
											&g_session );

		setlasterror( g_session.reqid );

		if( g_session.reqid >= 0 )
			g_session.state = DPWI_COMMON_SESSION_STATE_SENDING_DATA;
		else
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

		break;

	// �f�[�^���M��
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_SENDING_DATA:

		result = DWC_ProcessGHTTP();

		if( !result ){
			g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;
			break;
		}

		break;

	// ��������
	//-----------------------
	case DPWI_COMMON_SESSION_STATE_COMPLETED:
		break;
	}

	return g_session.state;
}


/*!
	�Z�b�V�����𒆒f���܂�
	
	�Z�b�V�����𒆒f���܂�
	
*/
void DpwiSessionCancel( void ){

	if( g_session.reqid >= 0 )
		DWC_CancelGHTTPRequest( g_session.reqid );

	g_session.state = DPWI_COMMON_SESSION_STATE_CANCELED;

	return;

}

/*!
	�Z�b�V�������I�����܂�
	
	�Z�b�V�������I�����ă������[��������܂�
	
*/
void DpwiSessionShutdown( void ){

	// �������[�J��
	if( g_session.request != NULL){
	
		DWC_Free( (DWCAllocType)DPWI_ALLOC, g_session.request, (u32)0 );
		g_session.request = NULL;

	}

	// GHTTP�J��
	DWC_ShutdownGHTTP();

	// �X�e�[�^�X�𖳌��ɂ���
	g_session.state = DPWI_COMMON_SESSION_STATE_ERROR;

	return;

}


/*!
	�Ō�̃G���[���擾���܂�
	
	
*/
DpwiHttpError DpwiGetLastError( void ){

	return (DpwiHttpError)g_session.lasterr;

}

/*!
	���X�|���X�̃f�[�^�T�C�Y��Ԃ��܂�
	
	
*/
int DpwiGetResponseSize( void ){

	return g_session.reslen;

}

