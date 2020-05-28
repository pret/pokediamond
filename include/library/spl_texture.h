/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_texture.h

  テクスチャ

  テクスチャリソースとしては圧縮テクスチャ用のデータを持つが
  ライブラリでは使用しない

  $Id: spl_texture.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_texture.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLライブラリが更新されたので更新

  Revision 1.3  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.2.6.1  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.2  2004/08/19 08:46:39  okane_shinji
  テクスチャをVRAMに読み込んだ後、リソースのテクスチャ部分を開放しても大丈夫なように修正

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_TEXTURE_H__
#define __SPL_TEXTURE_H__

/* 構造体 ------------------------------------------------------------------ */

// テクスチャパラメータ
typedef union
{
    u32 all;
    struct
    {
        u32 fmt:4;
        u32 s:4;
        u32 t:4;
        u32 rep:2;
        u32 flp:2;
        u32 plt0:1;
        
        u32 overlaped:1;
        u32 sharedTexNo:8;
        u32 reserved0:6;
    };
} SPLTexParam;

// テクスチャヘッダ
typedef struct SPLTexHdr
{
    u32 id;

    SPLTexParam param;

    u32 tex_size;
    u32 plt_ofst;
    u32 plt_size;
    u32 plt_idx_ofst;
    u32 plt_idx_size;
    u32 total_size;
} SPLTexHdr;

// テクスチャ構造体
typedef struct SPLTexture
{
    // VRAM確保後は使用されないこと前提
    const void* p_obj;

    u32 tex_addr;
    u32 plt_addr;

    SPLTexParam tex_param ;

    u16 wdt;
    u16 hgt;
} SPLTexture;

/* ------------------------------------------------------------------------- */

/* 定数など ---------------------------------------------------------------- */

// テクスチャＩＤ
#define SPL_TEX_ID    'SPT '

/* ------------------------------------------------------------------------- */

#endif
