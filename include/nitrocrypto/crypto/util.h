/*---------------------------------------------------------------------------*
  Project:  NitroCrypto - include
  File:     crypto/util.h

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: util.h,v $
  Revision 1.1  2006/07/05 13:07:09  mitsuhara
  *** empty log message ***

  Revision 1.3  2006/02/24 01:21:27  okubata_ryoma
  NitroCrypto の新設　Crypt から Crypto へ

  Revision 1.2  2005/12/21 14:44:05  seiki_masashi
  small fix

  Revision 1.1  2005/12/21 13:55:54  seiki_masashi
  CRYPT_SetAllocator 関数を追加

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

#ifndef NITRO_CRYPTO_UTIL_H_
#define NITRO_CRYPTO_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*
  Name:         CRYPTO_SetAllocator

  Description:  CRYPTO ライブラリで使用するメモリ管理関数を登録する

  Arguments:    alloc - メモリ確保関数へのポインタ
                free  - メモリ解放関数へのポインタ

  Returns:      なし
 *---------------------------------------------------------------------------*/
void CRYPTO_SetAllocator(
    void* (*alloc) (u32),
    void  (*free) (void*)
);

#ifdef __cplusplus
}
#endif

#endif //_NITRO_CRYPTO_UTIL_H_
