/*---------------------------------------------------------------------------*
  Project:  NitroCrypto - include
  File:     crypto/rc4.h

  Copyright 2005,2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: rc4.h,v $
  Revision 1.1  2006/07/05 13:07:09  mitsuhara
  *** empty log message ***

  Revision 1.5  2006/03/08 04:19:58  seiki_masashi
  RC4FastDecrypt �֐��� RC4FastEncrypt �֐��̕ʖ��Ƃ��Ēǉ�

  Revision 1.4  2006/03/07 04:42:45  seiki_masashi
  RC4Decrypt �֐��� RC4Encrypt �֐��̕ʖ��Ƃ��Ēǉ�

  Revision 1.3  2006/03/07 01:25:25  okubata_ryoma
  CRYPTO_RC4Crypto �� CRYPTO_RC4En���������� �ɕύX

  Revision 1.2  2006/02/24 01:21:27  okubata_ryoma
  NitroCrypto �̐V�݁@Crypt ���� Crypto ��

  Revision 1.1  2005/12/27 12:43:56  seiki_masashi
  RC4 �֐��̒ǉ�


  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CRYPTO_RC4_H_
#define NITRO_CRYPTO_RC4_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CRYPTORC4Context
{
    u8 i, j;
    u8 padd[2];
    u8 s[256];
} CRYPTORC4Context;

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Init

  Description:  RC4 �A���S���Y���ňÍ���/�������s�����߂̏��������s��

  Arguments:    context - RC4 �̌����Ȃǂ����߂�R���e�L�X�g�\����
                key - ���f�[�^
                key_len - ����

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4Init(
    CRYPTORC4Context* context,
    const void* key,
    u32 key_len
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Encrypt

  Description:  RC4 �A���S���Y���ňÍ���/�������s��

  Arguments:    context - RC4 �̌����Ȃǂ����߂��R���e�L�X�g�\����
                in      - ���̓f�[�^
                length  - �f�[�^��
                out     - �o�̓f�[�^

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4Encrypt(
    CRYPTORC4Context* context,
    const void* in,
    u32 length,
    void* out
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Decrypt

  Description:  RC4 �A���S���Y���ňÍ���/�������s��

  Arguments:    context - RC4 �̌����Ȃǂ����߂��R���e�L�X�g�\����
                in      - ���̓f�[�^
                length  - �f�[�^��
                out     - �o�̓f�[�^

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
static inline void CRYPTO_RC4Decrypt(
    CRYPTORC4Context* context,
    const void* in,
    u32 length,
    void* out
)
{
    CRYPTO_RC4Encrypt(context, in, length, out);
}

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4

  Description:  RC4 �A���S���Y���ňÍ���/�������s��

  Arguments:    key - ���f�[�^
                key_len - ���f�[�^��
                data - �ϊ�����f�[�^�i�㏑�������j
                data_len - �f�[�^��

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
static inline void CRYPTO_RC4(
    const void* key,
    u32 key_len,
    void* data,
    u32 data_len
)
{
    CRYPTORC4Context context;
    CRYPTO_RC4Init(&context, key, key_len);
    CRYPTO_RC4Encrypt(&context, data, data_len, data);
}


///////////////////////////////////////////////////////////////////////////////
// RC4 Fast
///////////////////////////////////////////////////////////////////////////////

// CRYPTORC4Context �ɔ�ׁA�g�p����������4�{
typedef struct CRYPTORC4FastContext
{
    u32 i, j;
    u32 s[256];
} CRYPTORC4FastContext;

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastInit

  Description:  RC4 �A���S���Y���ňÍ���/�������s�����߂̏��������s��

  Arguments:    context - RC4 �̌����Ȃǂ����߂�R���e�L�X�g�\����
                key - ���f�[�^
                key_len - ����

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4FastInit(
    CRYPTORC4FastContext* context,
    const void* key,
    u32 key_len
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastEncrypt

  Description:  RC4Fast �A���S���Y���ňÍ���/�������s��
                CRYPTO_RC4Encrypt �ɔ�ׁA�g�p����������4�{�ő��x�͖�1.5�{

  Arguments:    context - RC4 �̌����Ȃǂ����߂��R���e�L�X�g�\����
                in      - ���̓f�[�^
                length  - �f�[�^��
                out     - �o�̓f�[�^

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4FastEncrypt(
    CRYPTORC4FastContext* context,
    const void* in,
    u32 length,
    void* out
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastDecrypt

  Description:  RC4Fast �A���S���Y���ňÍ���/�������s��
                CRYPTO_RC4Decrypt �ɔ�ׁA�g�p����������4�{�ő��x�͖�1.5�{

  Arguments:    context - RC4 �̌����Ȃǂ����߂��R���e�L�X�g�\����
                in      - ���̓f�[�^
                length  - �f�[�^��
                out     - �o�̓f�[�^

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
static inline void CRYPTO_RC4FastDecrypt(
    CRYPTORC4FastContext* context,
    const void* in,
    u32 length,
    void* out
)
{
    CRYPTO_RC4FastEncrypt(context, in, length, out);
}

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Fast

  Description:  RC4Fast �A���S���Y���ňÍ���/�������s��
                CRYPTO_RC4 �ɔ�ׁA�g�p����������4�{�ő��x�͖�1.5�{

  Arguments:    key - ���f�[�^
                key_len - ���f�[�^��
                data - �ϊ�����f�[�^�i�㏑�������j
                data_len - �f�[�^��

  Returns:      �Ȃ�
 *---------------------------------------------------------------------------*/
static inline void CRYPTO_RC4Fast(
    const void* key,
    u32 key_len,
    void* data,
    u32 data_len
)
{
    CRYPTORC4FastContext context;
    CRYPTO_RC4FastInit(&context, key, key_len);
    CRYPTO_RC4FastEncrypt(&context, data, data_len, data);
}

#ifdef __cplusplus
}
#endif

#endif //_NITRO_CRYPTO_RC4_H_
