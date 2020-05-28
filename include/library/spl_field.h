/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_field.h

  �t�B�[���h�i�^���n�ւ̉e�����y�ڂ����́j����

  �������̂�SPLField�̔z�񂩉������s���t�B�[���h�̎�ޖ���
  ���������߂Ă����̂ł͌������������ȂƂ������ƂŁA
  �֐��|�C���^�ƃL���X�g�ŏ������s���`�ɁA�A�A

  $Id: spl_field.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_field.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.7  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.6.2.1  2005/03/04 05:55:36  okane_shinji
  (none)

  Revision 1.6  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.5  2004/07/02 06:24:03  okane_shinji
  (none)

  Revision 1.4  2004/07/02 06:21:37  okane_shinji
  �����W���ǉ�

  Revision 1.3  2004/07/02 01:11:24  okane_shinji
  �֐��E�ϐ����O�ύX

  Revision 1.2  2004/07/02 00:07:45  okane_shinji
  �V���v���R���W�����t�B�[���h�ƈʒu���Z�}�O�l�b�g�t�B�[���h��ǉ�

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_FIELD_H__
#define __SPL_FIELD_H__

#include "spl_particle.h"

struct SPLEmitter ;

/* �\���� ------------------------------------------------------------------ */

// �t�B�[���h�����\����
typedef struct SPLField
{
    void (*p_exec)(const void*, SPLParticle*, VecFx32*, struct SPLEmitter* p_emtr );
    const void* p_obj;
} SPLField;

// �d�̓t�B�[���h
typedef struct SPLGravity
{
    VecFx16 mag;
    u16 reserved0;
} SPLGravity;

// �����_���t�B�[���h
typedef struct SPLRandom
{
    VecFx16 mag;
    u16 intvl;
} SPLRandom;

// �}�O�l�b�g�t�B�[���h
typedef struct SPLMagnet
{
    VecFx32 pos;
    fx16    mag;
    u16     reserved0;
} SPLMagnet;

// �X�s���t�B�[���h
typedef struct SPLSpin
{
    u16 radian;
    u16 axis_type;
} SPLSpin;

// �V���v���R���W�����t�B�[���h
typedef struct SPLSimpleCollisionField
{
    fx32 y ; // �C�x���g���N����y���ʂ̒l
    fx16 coeff_bounce ;
    
    struct
    {
        u16 eventtype:2 ;
        u16 global:1 ;
        u16 reserved:13 ;
    } etc ;
} SPLSimpleCollisionField ;

// �ʒu�ɉ��Z�t�B�[���h�i�}�O�l�b�g�̈���j
typedef struct SPLConvergence
{
    VecFx32 pos  ; // �z���񂹂���ꏊ
    fx16    ratio; // �z���񂹂��鋭��
    u16     reserved0;
} SPLConvergence ;



/* ------------------------------------------------------------------------- */


/* ��`�Ȃ� ---------------------------------------------------------------- */

#define SPL_FLD_TYPE_NUM  6 // �t�B�[���h�̎�� TODO:6��

#define SPL_FLD_SPIN_AXIS_TYPE_X   0
#define SPL_FLD_SPIN_AXIS_TYPE_Y   1
#define SPL_FLD_SPIN_AXIS_TYPE_Z   2


// �V���v���R���W�����t�B�[���h�̃C�x���g�^�C�v
#define SPL_FLD_SCF_EVENTTYPE_CESSER     0
#define SPL_FLD_SCF_EVENTTYPE_REFLECTION 1



/* ------------------------------------------------------------------------- */


/* �e��t�B�[���h���� ------------------------------------------------------ */

extern void spl_calc_gravity(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_random(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_magnet(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_spin(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_scfield(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
extern void spl_calc_convergence(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );


/* ------------------------------------------------------------------------- */

#endif
