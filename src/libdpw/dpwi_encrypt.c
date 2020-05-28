/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpwi_encrypt.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DPW internal encryption module
	
	@author	Yuki Hayashi(hayashi_yuki@nintendo.co.jp)
	
	@version
		@li
*/

#include <dwc.h>

#include <nonport.h>
#include "include/libdpw/dpwi_encrypt.h"

#ifdef _NITRO
#include "include/libdpw/dpwi_define.h"
#endif


/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/
#define SIZE_CHECKSUM	4
#define SIZE_PID		4

/*-----------------------------------------------------------------------*
					�O���[�o���ϐ���`
 *-----------------------------------------------------------------------*/

static int s_local_seed;


/*-----------------------------------------------------------------------*
					�֐��v���g�^�C�v�錾
 *-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*
					�����������[�`��
 *-----------------------------------------------------------------------*/
static void my_randinit(unsigned long seed) {
	s_local_seed = (int)(seed | (seed << 16));
}

static unsigned char my_rand(void) {

	s_local_seed = (int)((MYRAND_A * s_local_seed + MYRAND_C) % MYRAND_M);

	return (unsigned char)((s_local_seed >> 16) & 0xff);
}



/*-----------------------------------------------------------------------*
					�O�����J�֐�
 *-----------------------------------------------------------------------*/

/*!
	�f�[�^���Í������ăo�b�t�@�ɏ����o���܂��B
	
	�Ǝ��̃X�g���[���Í������Ńf�[�^���Í������܂��Boutbuf�ɂ͍Œ�ł�
	ROUNDUP((len+4)/3)*4+1�̃T�C�Y���K�v�ł��B
	
	@param[in] src			�Í�������\�[�X
	@param[in] len			src�̃T�C�Y
	@param[in,out] outbuf	�Í������ꂽ�f�[�^���������ރo�b�t�@
	@param[in] outlen		outbuf�̃T�C�Y
*/
DpwiEncResult DpwiEncrypt(u32 pid, const u8* src, int len, u8* outbuf, int outlen){

	unsigned char* tmpbuf;
	u32 sum = 0;
	int i;

	// outbuf�̃T�C�Y�𒲂ׂ�
	if( outlen < (int)DpwiB64Size((u32)(len + SIZE_CHECKSUM + SIZE_PID)) + 1 )
		return DPWI_COMMON_ENC_ERROR_NOBUFFER;

	// ���[�N�o�b�t�@���m��
	tmpbuf = (unsigned char*)DWC_Alloc( (DWCAllocType)DPWI_ALLOC, (unsigned long)(len + SIZE_CHECKSUM + SIZE_PID) );
	if( tmpbuf == NULL )
		return DPWI_COMMON_ENC_ERROR_NOMEMORY;

	// �`�F�b�N�T�����v�Z
	sum += (u8)((pid >> 24) & 0xff);
	sum += (u8)((pid >> 16) & 0xff);
	sum += (u8)((pid >>  8) & 0xff);
	sum += (u8)((pid      ) & 0xff);

	for( i=0; i<len; i++ )
		sum += src[i];

	// �`�F�b�N�T���𗐐��̎�Ƃ���B
	my_randinit( sum );

	// �擪�S�o�C�g����Í������ꂽPID���i�[����
	tmpbuf[4] = (u8)(((pid      ) & 0xff) ^ my_rand());
	tmpbuf[5] = (u8)(((pid >>  8) & 0xff) ^ my_rand());
	tmpbuf[6] = (u8)(((pid >> 16) & 0xff) ^ my_rand());
	tmpbuf[7] = (u8)(((pid >> 24) & 0xff) ^ my_rand());

	// �X�R�A�E�h�c�𗐐��Ń}�X�N�������Ă����B
	for( i=0; i<len; i++ )
		tmpbuf[ SIZE_CHECKSUM+SIZE_PID + i ] = (u8)(src[i] ^ my_rand());

	// �`�F�b�N�T���Ƀ}�X�N��������
	sum ^= CHECKSUM_MASK;


	// �擪�S�o�C�g�Ƀ}�X�N���������`�F�b�N�T�����i�[����
	tmpbuf[0] = (u8)((sum >> 24) & 0xff);
	tmpbuf[1] = (u8)((sum >> 16) & 0xff);
	tmpbuf[2] = (u8)((sum >>  8) & 0xff);
	tmpbuf[3] = (u8)((sum      ) & 0xff);

	// base64 �ŃG���R�[�h����
	B64Encode(	(const char*)tmpbuf,
				(char*)outbuf,
				(int)(len + SIZE_CHECKSUM + SIZE_PID),
				2 /* url safe */ );

	// NULL�I�[����
	((char*)outbuf)[DpwiB64Size((u32)(len + SIZE_CHECKSUM + SIZE_PID))] = '\0';

	// ���[�N�o�b�t�@���J��
	DWC_Free( (DWCAllocType)DPWI_ALLOC, tmpbuf, (u32)0 );

	return DPWI_COMMON_ENC_SUCCESS;
}


/*!
	BASE64�G���R�[�h��̃T�C�Y�����߂܂�
	
	@param[in] len			�G���R�[�h����f�[�^�T�C�Y

	@return	�G���R�[�h��̃T�C�Y
*/
u32 DpwiB64Size( u32 len ){

	u32 i;

	i = (len) % 3 != 0 ? (u32)1 : (u32)0;

	return (((u32)(len / 3)) + i) * 4;
}
