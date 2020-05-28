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
  RC4FastDecrypt 関数を RC4FastEncrypt 関数の別名として追加

  Revision 1.4  2006/03/07 04:42:45  seiki_masashi
  RC4Decrypt 関数を RC4Encrypt 関数の別名として追加

  Revision 1.3  2006/03/07 01:25:25  okubata_ryoma
  CRYPTO_RC4Crypto を CRYPTO_RC4Enｃｒｙｐｔ に変更

  Revision 1.2  2006/02/24 01:21:27  okubata_ryoma
  NitroCrypto の新設　Crypt から Crypto へ

  Revision 1.1  2005/12/27 12:43:56  seiki_masashi
  RC4 関数の追加


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

  Description:  RC4 アルゴリズムで暗号化/復号を行うための初期化を行う

  Arguments:    context - RC4 の鍵情報などを収めるコンテキスト構造体
                key - 鍵データ
                key_len - 鍵長

  Returns:      なし
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4Init(
    CRYPTORC4Context* context,
    const void* key,
    u32 key_len
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Encrypt

  Description:  RC4 アルゴリズムで暗号化/復号を行う

  Arguments:    context - RC4 の鍵情報などを収めたコンテキスト構造体
                in      - 入力データ
                length  - データ長
                out     - 出力データ

  Returns:      なし
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4Encrypt(
    CRYPTORC4Context* context,
    const void* in,
    u32 length,
    void* out
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4Decrypt

  Description:  RC4 アルゴリズムで暗号化/復号を行う

  Arguments:    context - RC4 の鍵情報などを収めたコンテキスト構造体
                in      - 入力データ
                length  - データ長
                out     - 出力データ

  Returns:      なし
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

  Description:  RC4 アルゴリズムで暗号化/復号を行う

  Arguments:    key - 鍵データ
                key_len - 鍵データ長
                data - 変換するデータ（上書きされる）
                data_len - データ長

  Returns:      なし
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

// CRYPTORC4Context に比べ、使用メモリが約4倍
typedef struct CRYPTORC4FastContext
{
    u32 i, j;
    u32 s[256];
} CRYPTORC4FastContext;

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastInit

  Description:  RC4 アルゴリズムで暗号化/復号を行うための初期化を行う

  Arguments:    context - RC4 の鍵情報などを収めるコンテキスト構造体
                key - 鍵データ
                key_len - 鍵長

  Returns:      なし
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4FastInit(
    CRYPTORC4FastContext* context,
    const void* key,
    u32 key_len
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastEncrypt

  Description:  RC4Fast アルゴリズムで暗号化/復号を行う
                CRYPTO_RC4Encrypt に比べ、使用メモリが約4倍で速度は約1.5倍

  Arguments:    context - RC4 の鍵情報などを収めたコンテキスト構造体
                in      - 入力データ
                length  - データ長
                out     - 出力データ

  Returns:      なし
 *---------------------------------------------------------------------------*/
void CRYPTO_RC4FastEncrypt(
    CRYPTORC4FastContext* context,
    const void* in,
    u32 length,
    void* out
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_RC4FastDecrypt

  Description:  RC4Fast アルゴリズムで暗号化/復号を行う
                CRYPTO_RC4Decrypt に比べ、使用メモリが約4倍で速度は約1.5倍

  Arguments:    context - RC4 の鍵情報などを収めたコンテキスト構造体
                in      - 入力データ
                length  - データ長
                out     - 出力データ

  Returns:      なし
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

  Description:  RC4Fast アルゴリズムで暗号化/復号を行う
                CRYPTO_RC4 に比べ、使用メモリが約4倍で速度は約1.5倍

  Arguments:    key - 鍵データ
                key_len - 鍵データ長
                data - 変換するデータ（上書きされる）
                data_len - データ長

  Returns:      なし
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
