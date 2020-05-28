/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_resource.h

  �i�e�N�X�`���ȊO�́j���\�[�X�֌W

  $Id: spl_resource.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_resource.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.31  2005/06/15 23:47:39  okane_shinji
  (none)

  Revision 1.30  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.29.2.1  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.29  2005/01/13 06:07:09  okane_shinji
  (none)

  Revision 1.28  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.27  2004/08/31 08:52:41  okane_shinji
  ���C��

  Revision 1.26  2004/08/31 07:38:38  okane_shinji
  �e�N�X�`���p�^�[���A�j���̃f�[�^�\���C��

  Revision 1.25  2004/08/17 08:30:00  okane_shinji
  ���\�[�X���̃e�N�X�`�����擾�֐��ǉ�

  Revision 1.24  2004/08/10 08:12:21  okane_shinji
  �\���̍\����ύX

  Revision 1.23  2004/08/10 06:06:18  okane_shinji
  �q�̕��o����ݒ�ł���悤�ɕύX�B

  Revision 1.22  2004/08/10 05:11:47  okane_shinji
  ��{�X�P�[���A�����x�̌^��fx16����fx32�ɕύX

  Revision 1.21  2004/08/04 05:55:42  okane_shinji
  �\���̂̃p�f�B���O�𐮂��܂����B

  Revision 1.20  2004/07/20 10:00:42  okane_shinji
  (none)

  Revision 1.19  2004/07/20 09:33:41  okane_shinji
  �C�ӎ������̉~�G�~�b�g�Ή�

  Revision 1.18  2004/07/16 01:41:17  okane_shinji
  �G�~�b�^�Ɋւ���p�����[�^���G�~�b�^���ƂɕύX�ł���悤�ɕύX

  Revision 1.17  2004/07/02 01:33:19  okane_shinji
  �}�N���C��

  Revision 1.16  2004/07/02 01:11:24  okane_shinji
  �֐��E�ϐ����O�ύX

  Revision 1.15  2004/07/02 00:07:45  okane_shinji
  �V���v���R���W�����t�B�[���h�ƈʒu���Z�}�O�l�b�g�t�B�[���h��ǉ�

  Revision 1.14  2004/06/28 02:40:55  okane_shinji
  �q�ւ̃X�P�[���p���A���s�[�g�񐔂̎w��AD�r���{�[�h�̈����L�΂����̉���

  Revision 1.13  2004/06/25 07:37:29  okane_shinji
  �~�{�����[���A���{�����[���ǉ��B�|���S���\������XYZ��]�̕s��C��

  Revision 1.12  2004/06/25 06:25:42  okane_shinji
  �|���S���\���Ɋւ���C���B�X�P�[���A�j���[�V�����̒ǉ�

  Revision 1.11  2004/06/24 05:37:48  okane_shinji
  �S�o�C�g�A���C�����g���[���ᔽ���C��

  Revision 1.10  2004/06/24 05:00:12  okane_shinji
  SPLResInOut�\���̂��C��

  Revision 1.9  2004/06/24 04:22:45  okane_shinji
  �A�j���[�V�����ɂ�peak��ݒ�ł���悤�ɕύX�B1���[�v������̃t���[������ς��邱�Ƃ��ł���悤�ɕύX

  Revision 1.8  2004/06/23 07:21:21  okane_shinji
  �J���[�A�j���A���[�v�Đ��A�|���S���A�f�B���N�V���i���r���{�[�h�̉���

  Revision 1.7  2004/05/26 06:13:51  konoh
  ���A�X�y�N�g��@�\�ǉ�

  Revision 1.6  2004/05/25 08:06:36  konoh
  ���~�n�����ʒu�Ɏ��w��ǉ�

  Revision 1.5  2004/05/25 06:30:29  konoh
  �������_���J���[�@�\�ǉ�

  Revision 1.4  2004/05/25 02:04:57  konoh
  �������_���e�N�X�`���@�\�ǉ�

  Revision 1.3  2004/05/24 07:35:44  konoh
  (none)

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.1  2004/04/15 07:23:37  konoh
  �����Ńt���O�ǉ�

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_RESOURCE_H__
#define __SPL_RESOURCE_H__

#include "spl_field.h"

/* �萔�Ȃ� ---------------------------------------------------------------- */

// �����ʒu�֌W
#define SPL_INIT_POS_TYPE_ZERO              0
#define SPL_INIT_POS_TYPE_SPHERE            1
#define SPL_INIT_POS_TYPE_CIRCLE            2
#define SPL_INIT_POS_TYPE_CIRCLE_RI         3
#define SPL_INIT_POS_TYPE_SPHERE_VOLUME     4
#define SPL_INIT_POS_TYPE_CIRCLE_VOLUME     5
#define SPL_INIT_POS_TYPE_CYLINDER          6
#define SPL_INIT_POS_TYPE_CYLINDER_RI       7
#define SPL_INIT_POS_TYPE_SEMISPHERE        8
#define SPL_INIT_POS_TYPE_SEMISPHERE_VOLUME 9


// �~�n�����ʒu�ɂ����鎲�w��
#define SPL_CIRCLE_AXIS_X   2
#define SPL_CIRCLE_AXIS_Y   1
#define SPL_CIRCLE_AXIS_Z   0
#define SPL_CIRCLE_AXIS_ARBITRARY 3

// �`��^�C�v
#define SPL_DRAW_BB    0 // �r���{�[�h
#define SPL_DRAW_DBB   1 // �f�B���N�V���i���r���{�[�h
#define SPL_DRAW_POL   2 // �|���S��
#define SPL_DRAW_DPL   3 // �f�B���N�V���i���|���S���i�i�s�������ނ��Łj
#define SPL_DRAW_DPC   4 // �f�B���N�V���i���|���S�\�i�������ނ��Łj


// �|���S���`��̍ۂ̊����
#define SPL_POLYGON_BASEPLANE_XY 0
#define SPL_POLYGON_BASEPLANE_XZ 1

// �|���S���`��̍ۂ̉�]��
#define SPL_POLYGON_ROTAXIS_Y    0
#define SPL_POLYGON_ROTAXIS_XYZ  1

// �X�P�[���A�j�����K�p��������
#define SPL_ANM_SCL_DIRECT_XY 0
#define SPL_ANM_SCL_DIRECT_X  1
#define SPL_ANM_SCL_DIRECT_Y  2

// �ő�e�N�X�`���p�^�[����
#define SPL_MAX_TEX_PTN_NUM  8

// �`���C���h��]�֌W
#define SPL_CHLD_RTT_NONE  0 // ��]���Ȃ�
#define SPL_CHLD_RTT_STILL 1 // ���񂾏u�Ԃ̐e�̊p�x���p��

// �W�r�b�g�łO�`�P��\�����Ă���̊֌W
#define SPL_FX8_SHIFT    8
#define SPL_FX8_MAX   0xff

// �g�p���Ă���t�B�[���h�����t���O����擾
#define SPL_CHLD_RTT_MOVE  2 // ���񂾏u�Ԃ̐e�̊p�x�Ɗp���x���p��
#define SPL_GET_FLD_NUM(x) ((x).use_fld_grvt +\
                                                        (x).use_fld_rndm +\
                                                        (x).use_fld_mgnt +\
                                                        (x).use_fld_spin +\
                                                        (x).use_fld_scfld +\
                                                        (x).use_fld_cngc)
// �|���S���̃I�t�Z�b�g�N�_
#define SPL_OFFSET_CENTER 0
#define SPL_OFFSET_TOP    1
#define SPL_OFFSET_BUTTOM 2
#define SPL_OFFSET_RIGHT  3
#define SPL_OFFSET_LEFT   4


/* ------------------------------------------------------------------------- */

/* �\���� ------------------------------------------------------------------ */

// �r�o�`���\�[�X�w�b�_
typedef struct SPLArcHdr
{
    u32 id;
    u32 ver;
    u16 res_num;
    u16 tex_num;
    u32 reserved0;
    u32 res_size;
    u32 tex_size;
    u32 tex_offset;
    u32 reserved1;
} SPLArcHdr;

///////////////////////////////////////////////////////////////////////////////

// �x�[�X�t���O
typedef union
{
    u32 all;
    struct
    {
        u32 init_pos_type:4;
        u32 draw_type:2;
        u32 circle_axis:2;

        u32 use_scl_anm:1;
        u32 use_clr_anm:1;
        u32 use_alp_anm:1;
        u32 use_tex_anm:1;
        u32 use_rtt_anm:1;
        u32 use_init_rtt_rndm:1;
        u32 self_dest:1;
        u32 follow_emtr:1;

        u32 use_chld:1;
        u32 pol_rot_axis:2;          // �|���S���\���̂Ƃ��̉�]��
        u32 pol_baseplane:1;         // �|���S���\���̂Ƃ��̊����
        u32 ptcl_random_loop_anm:1 ; // ���[�v�A�j���̂Ƃ��A�J�n�^�C�~���O�������_�}�C�Y����
        u32 draw_child_first:1 ;     // �e���q���ɏ����Ƃ���1
        u32 draw_parent:1;           // �e��`�悷�邩�ǂ���0�̂Ƃ��͕`�悷��
        u32 camera_offset:1;         // �I�t�Z�b�g���W���J�������W�n�Ōv�Z���邩�ǂ���

        u32 use_fld_grvt:1;
        u32 use_fld_rndm:1;
        u32 use_fld_mgnt:1;
        u32 use_fld_spin:1;
        u32 use_fld_scfld:1;
        u32 use_fld_cngc:1;
        
        u32 polygonID_fixed:1;
        u32 child_polygonID_fixed:1;
    };
} SPLResBaseFlag;

// �`���C���h�t���O
typedef union
{
    u16 all;
    struct
    {
        u16 affect_fld:1;
        u16 use_scl_anm:1;
        u16 use_alp_anm:1;
        u16 rtt_type:2;
        u16 follow_emtr:1;
        u16 use_chld_clr:1;
        u16 draw_type:2;
        u16 pol_rot_axis:2;  // �|���S���\���̂Ƃ��̉�]��
        u16 pol_baseplane:1; // �|���S���\���̂Ƃ��̊����
        u16 reserved0:4;
    };
} SPLResChldFlag;

// �C���E�A�E�g�^�C�~���O
typedef union
{
    u16 all;
    struct
    {
        u16 in:8;
        u16 out:8;
    };
} SPLResInOut;

typedef union
{
    u32 all ;
    struct
    {
        u32 in:8;
        u32 peak:8;
        u32 out:8;
        u32 reserved:8;
    } ;
} SPLResInPeakOut ;

///////////////////////////////////////////////////////////////////////////////

// �r�o�q�x�[�X
// ���}�[�N�̓G�~�b�^�ŃR�s�[����Ďg����B����ȊO�͒��Ɏg����
typedef struct SPLResBase
{
    SPLResBaseFlag flag;

    VecFx32 pos ;

    fx32 gen_num;
    fx32 radius; // ��
    fx32 length; // �������_�ł͉~���̒����ɂ����g�p����Ȃ�

    VecFx16 axis;

    GXRgb clr_n;

    fx32 init_vel_mag_pos; // ��
    fx32 init_vel_mag_axis;// ��
    fx32 base_scl;         // ��
    fx16 aspect;
    u16 start_offset ;// �G�~�b�^���J�n����܂ł̃^�C�~���O

    s16 rtt_min;
    s16 rtt_max;

    u16 init_rtt ;
    u16 reserved0 ;

    u16 emtr_life;
    u16 ptcl_life; // ��

    struct
    {
        u32 base_scl:8; 
        u32 ptcl_life:8; 
        u32 init_vel_mag:8;
        u32 reserved0:8;
    } rndm;

    struct
    {
        u32 gen_intvl:8; // ��
        u32 base_alp:8;
        u32 air_resist:8;
        u32 tex_no:8;
        
        u32 loop_frame:8;  // �P���[�v������̃t���[����
        u32 dbb_scale:16;  // D�r���{�[�h�̎��̈����L�΂������ifx16�����j
        u32 tex_repeat_num_s:2;
        u32 tex_repeat_num_t:2;
        u32 scl_anm_direct:3 ;
        u32 dpol_center:1;
        //u32 reserved:1;
        
        u32 reverse_tex_s:1 ; // �e�N�X�`���𔽓]���邩�ǂ����B�B
        u32 reverse_tex_t:1 ;
        u32 offset_pos:3;     // �I�t�Z�b�g�ꏊ(���㉺���E)
        u32 reserved1:27 ; 
    } etc;

    // �|���S���̃I�t�Z�b�g�ʒu
    fx16 offset_x ;
    fx16 offset_y ;

    struct
    {
        u32 flag:8 ;
        u32 reserved:24;
    } usr ; 

} SPLResBase;

// �r�o�q�X�P�[���A�j��
typedef struct SPLResSclAnm
{
    fx16 scl_s;
    fx16 scl_n;
    fx16 scl_e;
    SPLResInOut in_out;
    struct
    {
        u16 loop:1 ;
        u16 reserved:15;
    } etc ;
    u16 reserved0 ;
} SPLResSclAnm;

// �r�o�q�J���[�A�j��
typedef struct SPLResClrAnm
{
    GXRgb clr_s;
    GXRgb clr_e;
    SPLResInPeakOut in_peak_out;
    struct
    {
        u16 use_rndm:1;
        u16 loop:1;
        u16 interpolation:1;
        u16 reserved0:13;
    } etc;
    u16 reserved0;
} SPLResClrAnm;

// �r�o�q�A���t�@�A�j��
typedef struct SPLResAlpAnm
{
    union
    {
        u16 all;
        struct
        {
            u16 s:5;
            u16 n:5;
            u16 e:5;
            u16 reserved0:1;
        };
    } alp;

    struct
    {
        u16 flick:8;
        u16 loop:1;
        u16 reserved0:7;
    } etc;

    SPLResInOut in_out;
    u16 reserved0;
} SPLResAlpAnm;

// �r�o�q�e�N�X�`���p�^�[���A�j��
typedef struct SPLResTexAnm
{
    u8 tex_no[SPL_MAX_TEX_PTN_NUM] ;

    struct
    {
        u32 use_num:8;
        u32 diff:8;
        u32 use_rndm:1;
        u32 loop:1;
        u32 reserved0:14;
    } etc;
} SPLResTexAnm;

// �r�o�q�`���C���h
typedef struct SPLResChld
{
    SPLResChldFlag flag;

    fx16 init_vel_mag_rndm;
    fx16 scl_e;

    u16 life;

    struct
    {
        u16 vel_ratio:8;
        u16 scl_ratio:8;
    } ratio;

    GXRgb clr;

    struct
    {
        u32 gen_num:8;
        u32 gen_start:8;
        u32 gen_intvl:8;
        u32 tex_no:8;
        u32 tex_repeat_num_s:2;
        u32 tex_repeat_num_t:2;
        
        u32 reverse_tex_s:1 ;
        u32 reverse_tex_t:1 ;
        u32 dpol_center:1 ; // D�|���S���̂Ƃ����S���������ǂ����H
        u32 reserved0:25;
        //u32 reserved0:26;
    } etc;

} SPLResChld;

// ���\�[�X�\����
typedef struct SPLResource
{
    SPLResBase*   p_base;
    SPLResSclAnm* p_scl_anm;
    SPLResClrAnm* p_clr_anm;
    SPLResAlpAnm* p_alp_anm;
    SPLResTexAnm* p_tex_anm;
    SPLResChld*   p_chld;
    SPLField*     fld_ary;
    u16           fld_num;
    u16           reserved ;
} SPLResource;

/* ------------------------------------------------------------------------- */



/* ------------------------------------------------------
 * ���\�[�X�ɂ�����e�N�X�`���I�t�Z�b�g
 *------------------------------------------------------*/
static inline u32 SPL_GetTexOffsetOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->tex_offset ;
}

/* ------------------------------------------------------
 * ���\�[�X�ɂ�����e�N�X�`���T�C�Y
 *------------------------------------------------------*/
static inline u32 SPL_GetTexSizeOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->tex_size ;
}

/* ------------------------------------------------------
 * ���\�[�X�ɂ����郊�\�[�X�T�C�Y
 *------------------------------------------------------*/
static inline u32 SPL_GetResSizeOnResource( const void* p_spa )
{
    const SPLArcHdr* p_arc_hdr = (const SPLArcHdr*) p_spa;

    return p_arc_hdr->res_size ;
}




/* ------------------------------------------------------------------------- */










#endif
