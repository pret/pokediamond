/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_particle.h

  �p�[�e�B�N���P�ʂ̏����֌W

  $Id: spl_particle.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_particle.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.12  2005/09/01 00:57:23  okane_shinji
  (none)

  Revision 1.11  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.10.2.2  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.10.2.1  2005/02/07 01:18:22  okane_shinji
  �v�Z�T�C�N���w�肪�\�ȃo�[�W����

  Revision 1.10  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.9  2004/09/01 01:32:22  okane_shinji
  SPL_GetParticleAge�@SPL_GetParticleLife�ǉ�

  Revision 1.8  2004/08/04 05:55:42  okane_shinji
  �\���̂̃p�f�B���O�𐮂��܂����B

  Revision 1.7  2004/07/15 02:47:37  okane_shinji
  �G�~�b�^�̕�����ύX�ł���悤�ɕύX

  Revision 1.6  2004/07/13 05:12:23  okane_shinji
  �p�[�e�B�N���̊�{�X�P�[����fx32�Ŏ��悤�ɕύX

  Revision 1.5  2004/06/23 07:21:21  okane_shinji
  �J���[�A�j���A���[�v�Đ��A�|���S���A�f�B���N�V���i���r���{�[�h�̉���

  Revision 1.4  2004/06/15 05:18:19  konoh
  �����C�t���[�g�̌v�Z���@������Z���瑝����Z�֕ύX

  Revision 1.3  2004/06/15 01:40:14  okane_shinji
  �p�[�e�B�N���E�G�~�b�^�̏�Ԏ擾�֐���ǉ�

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.1  2004/04/14 05:09:27  konoh
  ���e�N�X�`�����p�[�e�B�N�����Ɏw�肷��悤��

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_PARTICLE_H__
#define __SPL_PARTICLE_H__

/* �\���� ------------------------------------------------------------------ */

// �p�[�e�B�N���\����
// ���т��������񂮂��Ⴎ����ł��邪�A�L���b�V�����l������
// ���s����I�ɂ��̔z�u�ɂ������ԑ��������i�ق�܂����ȁB�B�j
typedef struct SPLParticle
{
    struct SPLParticle* p_next; // for SPLNode
    struct SPLParticle* p_prev; // for SPLNode

    VecFx32 ptcl_pos;
    VecFx32 vel;

    u16 rtt;
    s16 rtt_vel;

    u16 life;
    u16 age;

    u16 life_rate_diff_loop   ;
    u16 life_rate_diff_noloop ;

    struct
    {
        u16 tex_no:8;
        u16 life_rate_offset:8;
    } etc;

    struct
    {
        u16 base_alp:5;
        u16 anm_alp:5;
        u16 current_polygonID:6 ;
    } alp;

    fx32 base_scl ;
    fx16 anm_scl;

    GXRgb clr; // �x�[�X�ƃA�j���ɕ�����K�v�����邩�H (:KHTODO:)

    VecFx32 emtr_pos;

} SPLParticle;

// �p�[�e�B�N�����X�g
typedef struct SPLParticleList
{
    SPLParticle* p_begin; // for SPLList
    int node_num;         // for SPLList
    SPLParticle* p_end;   // for SPLList
} SPLParticleList;

// �֐�---------------------------------------------------------------------

// ���̃p�[�e�B�N����Ԃ�
static inline SPLParticle* SPL_GetNextParticle( const SPLParticle* ptcl )
{
    return ptcl->p_next ;
}

// �O�̃p�[�e�B�N����Ԃ�
static inline SPLParticle* SPL_GetPrevParticle( const SPLParticle* ptcl )
{
    return ptcl->p_prev ;
}

// �p�[�e�B�N���̈ʒu��Ԃ��i�G�~�b�^�̈ʒu���܂߂���Έʒu�j�B
static inline void SPL_GetParticlePos( const SPLParticle* ptcl, VecFx32 *pos )
{
    pos->x = ptcl->ptcl_pos.x + ptcl->emtr_pos.x ;
    pos->y = ptcl->ptcl_pos.y + ptcl->emtr_pos.y ;
    pos->z = ptcl->ptcl_pos.z + ptcl->emtr_pos.z ;
}

// �p�[�e�B�N���̎������I��������B
static inline void SPL_TerminateParticleLife( SPLParticle* ptcl )
{
    ptcl->age = ptcl->life ;
}

// �p�[�e�B�N���̔N����擾
static inline u16 SPL_GetParticleAge( const SPLParticle* ptcl )
{
    return ptcl->age ;
}

// �p�[�e�B�N���̎������擾
static inline u16 SPL_GetParticleLife( const SPLParticle* ptcl )
{
    return ptcl->life ;
}





/* ------------------------------------------------------------------------- */

#endif
