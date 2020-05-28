/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_texture.h

  �e�N�X�`��

  �e�N�X�`�����\�[�X�Ƃ��Ă͈��k�e�N�X�`���p�̃f�[�^������
  ���C�u�����ł͎g�p���Ȃ�

  $Id: spl_texture.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_texture.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.3  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.2.6.1  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.2  2004/08/19 08:46:39  okane_shinji
  �e�N�X�`����VRAM�ɓǂݍ��񂾌�A���\�[�X�̃e�N�X�`���������J�����Ă����v�Ȃ悤�ɏC��

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_TEXTURE_H__
#define __SPL_TEXTURE_H__

/* �\���� ------------------------------------------------------------------ */

// �e�N�X�`���p�����[�^
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

// �e�N�X�`���w�b�_
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

// �e�N�X�`���\����
typedef struct SPLTexture
{
    // VRAM�m�ی�͎g�p����Ȃ����ƑO��
    const void* p_obj;

    u32 tex_addr;
    u32 plt_addr;

    SPLTexParam tex_param ;

    u16 wdt;
    u16 hgt;
} SPLTexture;

/* ------------------------------------------------------------------------- */

/* �萔�Ȃ� ---------------------------------------------------------------- */

// �e�N�X�`���h�c
#define SPL_TEX_ID    'SPT '

/* ------------------------------------------------------------------------- */

#endif
