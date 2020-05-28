/*---------------------------------------------------------------------------*
  Project:  NitroCrypto - include
  File:     crypto/sign.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: sign.h,v $
  Revision 1.1  2006/07/05 13:07:09  mitsuhara
  *** empty log message ***

  Revision 1.2  2006/02/24 01:21:27  okubata_ryoma
  NitroCrypto の新設　Crypt から Crypto へ

  Revision 1.1  2005/12/19 22:08:53  seiki_masashi
  NitroWiFi の CRYPT ライブラリを新設し、電子署名検証機能を追加

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CRYPTO_SIGN_H_
#define NITRO_CRYPTO_SIGN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_VerifySignatureWithHash

  Description:  ハッシュ値から電子署名を検証する

  Arguments:    hash_ptr - ハッシュ値へのポインタ
                sign_ptr - 電子署名へのポインタ
                mod_ptr - 公開鍵へのポインタ
  Returns:      認証できたら TRUE
                認証できなかったら FALSE
 *---------------------------------------------------------------------------*/
int CRYPTO_VerifySignatureWithHash(
    const void* hash_ptr,
    const void* sign_ptr,
    const void* mod_ptr
);

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_VerifySignature

  Description:  データから電子署名を検証する

  Arguments:    data_ptr - データへのポインタ
                data_len - データのサイズ
                sign_ptr - 電子署名へのポインタ
                mod_ptr - 公開鍵へのポインタ

  Returns:      認証できたら TRUE
                認証できなかったら FALSE
 *---------------------------------------------------------------------------*/
int CRYPTO_VerifySignature(
    const void* data_ptr,
    int   data_len,
    const void* sign_ptr,
    const void* mod_ptr
);


#ifdef __cplusplus
}
#endif

#endif //_NITRO_CRYPTO_SIGN_H_
