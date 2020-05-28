/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_emitter.h

  �G�~�b�^�P�ʂ̏����֌W

  $Id: spl_emitter.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_emitter.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.36  2005/08/31 09:54:04  okane_shinji
  ���X�g�ɋ@�\�ǉ�

  Revision 1.35  2005/06/20 08:42:35  okane_shinji
  SPL_SetEmitterInitVelocityOffset���ɲ�

  Revision 1.34  2005/06/15 23:47:42  okane_shinji
  (none)

  Revision 1.33  2005/03/17 08:27:13  okane_shinji
  (none)

  Revision 1.32.2.5  2005/03/16 09:47:52  okane_shinji
  ver.1.20

  Revision 1.32.2.4  2005/03/04 05:55:36  okane_shinji
  (none)

  Revision 1.32.2.3  2005/02/09 00:12:21  okane_shinji
  �R�[���o�b�N�֐��̎d�l�ύX

  Revision 1.32.2.2  2005/02/07 01:25:49  okane_shinji
  �v�Z�T�C�N���w�肪�\�ȃo�[�W����

  Revision 1.32.2.1  2005/02/07 01:18:22  okane_shinji
  �v�Z�T�C�N���w�肪�\�ȃo�[�W����

  Revision 1.32  2005/01/13 06:07:09  okane_shinji
  (none)

  Revision 1.31  2004/12/28 00:44:28  okane_shinji
  �ʒu�ݒ�֐��̈ʒu�ݒ���I�t�Z�b�g�Ƃ̉��Z�ɕύX

  Revision 1.30  2004/12/21 02:01:33  okane_shinji
  (none)

  Revision 1.29  2004/12/10 07:27:24  okane_shinji
  ���[�U�t���O�擾�֐�SPL_Get_UserFlag��ǉ�

  Revision 1.28  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.27  2004/09/01 10:18:00  okane_shinji
  SPL_SetCalc SPL_SetDraw SPL_SetEmission �̐ݒ���@��ύX

  Revision 1.26  2004/08/10 05:11:47  okane_shinji
  ��{�X�P�[���A�����x�̌^��fx16����fx32�ɕύX

  Revision 1.25  2004/08/09 10:47:12  okane_shinji
  SPL_SetCurrentPolygonID�ǉ�

  Revision 1.24  2004/08/04 05:55:42  okane_shinji
  �\���̂̃p�f�B���O�𐮂��܂����B

  Revision 1.23  2004/07/20 09:33:41  okane_shinji
  �C�ӎ������̉~�G�~�b�g�Ή�

  Revision 1.22  2004/07/16 01:41:17  okane_shinji
  �G�~�b�^�Ɋւ���p�����[�^���G�~�b�^���ƂɕύX�ł���悤�ɕύX

  Revision 1.21  2004/07/15 02:47:37  okane_shinji
  �G�~�b�^�̕�����ύX�ł���悤�ɕύX

  Revision 1.20  2004/07/06 05:10:40  okane_shinji
  �A�N�Z�T�֐��̃o�O�C��

  Revision 1.19  2004/07/02 00:07:45  okane_shinji
  �V���v���R���W�����t�B�[���h�ƈʒu���Z�}�O�l�b�g�t�B�[���h��ǉ�

  Revision 1.18  2004/06/28 07:22:04  okane_shinji
  �s��C���B�֐����ύX

  Revision 1.17  2004/06/28 07:02:54  okane_shinji
  �֐����C��

  Revision 1.16  2004/06/28 04:45:07  okane_shinji
  �A�N�Z�X�֐��̃C�����C����

  Revision 1.15  2004/06/23 07:21:21  okane_shinji
  �J���[�A�j���A���[�v�Đ��A�|���S���A�f�B���N�V���i���r���{�[�h�̉���

  Revision 1.14  2004/06/15 01:41:06  okane_shinji
  �p�[�e�B�N���E�G�~�b�^�̏�Ԏ擾�֐���ǉ�

  Revision 1.13  2004/06/14 07:22:35  konoh
  ��SPL_SetEmtrVel�����C��

  Revision 1.12  2004/06/14 07:01:36  okane_shinji
  ��̃G�~�b�^�𕡐��̈ʒu�Ŏg�p�ł���悤�ɏC��

  Revision 1.11  2004/06/14 01:25:16  okane_shinji
  (none)

  Revision 1.10  2004/06/14 00:52:58  okane_shinji
  �G�~�b�^�ɃR�[���o�b�N��o�^�ł���悤�ɂ��܂����B

  Revision 1.9  2004/06/11 02:09:30  konoh
  (none)

  Revision 1.8  2004/06/11 02:07:09  konoh
  ���G�~�b�^����֐��Q�ǉ�

  Revision 1.7  2004/06/11 00:51:19  konoh
  ���G�~�b�^���x�@�\�ǉ�

  Revision 1.6  2004/06/09 00:45:31  konoh
  ���G�~�b�^���x���̌v�Z��~�E�`���~�����ǉ�

  Revision 1.5  2004/06/08 08:24:14  konoh
  (none)

  Revision 1.4  2004/06/07 00:19:36  konoh
  ����C��R�͈͕̔ύX

  Revision 1.3  2004/05/24 07:35:44  konoh
  (none)

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.2  2004/04/19 06:41:30  konoh
  �������X�g�b�v�t���O�̒ǉ�

  Revision 1.1.2.1  2004/04/15 07:24:00  konoh
  ���G�~�b�^�̏�ԃt���O�ǉ�

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_EMITTER_H__
#define __SPL_EMITTER_H__

#include "spl_particle.h"
#include "spl_resource.h"

/* �\���� ------------------------------------------------------------------ */

// �G�~�b�^�t���O
typedef struct SPLEmitterFlag
{
    union
    {
        u32 all;
        struct
        {
            u32 terminate:1;
            u32 stop_generate:1;
            u32 stop_calc:1;
            u32 stop_draw:1;
            u32 started: 1 ;
            u32 reserved0:27;
        };
    };
} SPLEmitterFlag;


// �G�~�b�^�\����
typedef struct SPLEmitter
{
    struct SPLEmitter* p_next; // for SPLNode
    struct SPLEmitter* p_prev; // for SPLNode

    SPLParticleList act_ptcl_list;
    SPLParticleList act_chld_list;

    // ���\�[�X
    SPLResource* p_res;

    // ���\�[�X��ˑ��p�����[�^
    SPLEmitterFlag flag;
    VecFx32 emtr_pos;
    VecFx32 emtr_vel;
    VecFx32 emtr_init_vel ;
    u16 age;
    fx16 gen_num_dec; // ���t���[���������̏�����

    // �Q�[�����ŕύX�ł���p�����[�^�B
    // ���\�[�X����R�s�[����
    VecFx16 axis ;
    u16 init_rtt ;  // ������]�p�x

    fx32 gen_num ; // ���o���[�g

    fx32 radius ;
    fx32 length ;
    fx32 init_vel_mag_pos ;
    fx32 init_vel_mag_axis ;
    fx32 base_scl ;
    u16  ptcl_life ;

    GXRgb clr; // �O���[�o���J���[

    // �V���v���R���W�����p�̃p�����[�^�B�B
    fx32 simple_collision_y ;

    // �e�N�X�`�����W
    fx16 tex_s ;
    fx16 tex_t ;
    fx16 chld_tex_s ;
    fx16 chld_tex_t ;

    struct
    {
        u32 gen_intvl:8;
        u32 base_alp:8;
        u32 calc_cycle:3 ;
        u32 reserved:13;
    } etc;

    // �������ɒ����ȓ�
    VecFx16 cross_to_axis_1 ;
    VecFx16 cross_to_axis_2 ;

    // �R�[���o�b�N�֐�
    void (*callbackfunc)(struct SPLEmitter*, unsigned int uFlag )  ;
    
    // ���[�U�����R�Ɏg�p�ł���f�[�^
    void* emtr_userdata ;
    
    // ���[�U�����R�Ɏg�p�ł��郏�[�N�̈�
    union
    {
        u32 uw_u32;
        u16 uw_u16[2] ;
        u8  uw_u8[4] ;
    } userwork ;


} SPLEmitter;

// �G�~�b�^���X�g
typedef struct SPLEmitterList
{
    SPLEmitter* p_begin; // for SPLList
    int node_num;        // for SPLList
    SPLEmitter* p_end;   // for SPLList
} SPLEmitterList;

/* ------------------------------------------------------------------------- */


/* ��`�� ------------------------------------------------------------------ */

#define SPL_EMTR_FOREVER  0 // ���������^�C�v
#define SPL_PTCL_GEN      0 // 
#define SPL_CHLD_GEN      0 //

#define SPL_PTCL_ANM_FUNC_NUM 4 // �e�p�[�e�B�N���A�j���ő吔
#define SPL_CHLD_ANM_FUNC_NUM 2 // �q�p�[�e�B�N���A�j���ő吔

// ��C��R�͂��̌W�����g���āi�P�`�R���S�j�͈̔͂̒l��
#define SPL_AIR_RESIST_OFST   (3 << 7) // ��C��R�v�Z
#define SPL_AIR_RESIST_SHIFT        9  // ��C��R�v�Z

#define SPL_EMITTER_CALLBACK_FRONT 0
#define SPL_EMITTER_CALLBACK_BACK  1

/* ------------------------------------------------------------------------- */

// �������m�ۃR�[���o�b�N
typedef void* (*SPLCallback)(SPLEmitter*);

/* �A�N�Z�X�p�֐� -------------------------------------------------------------------- */

/* ------------------------------------------------------
 * �G�~�b�^�̒�~
 *------------------------------------------------------*/
static inline void SPL_Terminate(  SPLEmitter* p_emtr )
{
    p_emtr->flag.terminate = 1 ;
}

/* ------------------------------------------------------
 * �v�Z�̒�~/�J�n
 *------------------------------------------------------*/
static inline void SPL_StopCalc( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_calc = 1 ;
}
static inline void SPL_RestartCalc( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_calc = 0 ;
}
static inline void SPL_SetCalc( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_calc = !flag ;
}

/* ------------------------------------------------------
 * �`��̒�~/�J�n
 *------------------------------------------------------*/
static inline void SPL_StopDraw( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_draw = 1 ;
}
static inline void SPL_RestartDraw( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_draw = 0 ;
}
static inline void SPL_SetDraw( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_draw = !flag ;
}

/* ------------------------------------------------------
 * �����̒�~/�J�n
 *------------------------------------------------------*/
static inline void SPL_StopEmission( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_generate = 1 ;
}
static inline void SPL_RestartEmission( SPLEmitter* p_emtr )
{
    p_emtr->flag.stop_generate = 0 ;
}
static inline void SPL_SetEmission( SPLEmitter* p_emtr, BOOL flag )
{
    p_emtr->flag.stop_generate = !flag ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̈ʒu�p�����[�^���Z�b�g����B�I�t�Z�b�g�l�͏�ɔ��f�����B
 *------------------------------------------------------*/
static inline void SPL_SetEmitterPosition( SPLEmitter* p_emtr, const VecFx32* p_pos )
{
    //p_emtr->emtr_pos = *( p_pos ) ;
    p_emtr->emtr_pos.x = p_pos->x + p_emtr->p_res->p_base->pos.x ;
    p_emtr->emtr_pos.y = p_pos->y + p_emtr->p_res->p_base->pos.y ;
    p_emtr->emtr_pos.z = p_pos->z + p_emtr->p_res->p_base->pos.z ;
}
static inline void SPL_SetEmitterPositionX(  SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_pos.x = x + p_emtr->p_res->p_base->pos.x ;
}
static inline void SPL_SetEmitterPositionY(  SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_pos.y = y + p_emtr->p_res->p_base->pos.y ;
}
static inline void SPL_SetEmitterPositionZ(  SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_pos.z = z + p_emtr->p_res->p_base->pos.z ;
}


/* ------------------------------------------------------
 * �G�~�b�^�̑��x�p�����[�^���Z�b�g����
 *------------------------------------------------------*/
static inline void SPL_SetEmitterVelocity( SPLEmitter* p_emtr, const VecFx32* p_vel )
{
    p_emtr->emtr_vel = *( p_vel ) ;
}
static inline void SPL_SetEmitterVelocityX( SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_vel.x = x ;
}
static inline void SPL_SetEmitterVelocityY( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_vel.y = y ;
}
static inline void SPL_SetEmitterVelocityZ( SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_vel.z = z ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̏������x�p�����[�^���Z�b�g����
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityOffset( SPLEmitter* p_emtr, const VecFx32* p_vel )
{
    p_emtr->emtr_init_vel = *( p_vel ) ;
}
static inline void SPL_SetEmitterInitVelocityOffsetX( SPLEmitter* p_emtr, fx32 x )
{
    p_emtr->emtr_init_vel.x = x ;
}
static inline void SPL_SetEmitterInitVelocityOffsetY( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->emtr_init_vel.y = y ;
}
static inline void SPL_SetEmitterInitVelocityOffsetZ( SPLEmitter* p_emtr, fx32 z )
{
    p_emtr->emtr_init_vel.z = z ;
}


/* ------------------------------------------------------
 * �R�[���o�b�N�֐����Z�b�g����
 *------------------------------------------------------*/
static inline void SPL_SetCallbackFunc( SPLEmitter* p_emtr, void (*callbackfunc_)(struct SPLEmitter*, unsigned int uFlag ) )
{
    p_emtr->callbackfunc=callbackfunc_ ;
}

/* ------------------------------------------------------
 * �G�~�b�^�ɑ�����p�[�e�B�N���̐����Q�Ƃ���
 *------------------------------------------------------*/
static inline s32 SPL_GetParticleNum( const SPLEmitter* p_emtr )
{
    return p_emtr->act_ptcl_list.node_num ;
}
static inline s32 SPL_GetChildParticleNum( const SPLEmitter* p_emtr )
{
    return p_emtr->act_chld_list.node_num ;
}
static inline s32 SPL_GetAllParticleNum( const SPLEmitter* p_emtr )
{
    return SPL_GetParticleNum(p_emtr)+SPL_GetChildParticleNum(p_emtr) ;
}

/* ------------------------------------------------------
 * ���[�U�f�[�^�̃Z�b�g  / �Q�b�g
 *------------------------------------------------------*/
static inline void SPL_SetUserData( SPLEmitter* p_emtr, void* p_data  )
{
    p_emtr->emtr_userdata = p_data ;
}
static inline void* SPL_GetUserData( const SPLEmitter* p_emtr )
{
    return p_emtr->emtr_userdata ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̌������Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterAxis( SPLEmitter* p_emtr, const VecFx16* axis )
{
    p_emtr->axis = *axis ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̑傫�����Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterRadius( SPLEmitter* p_emtr, fx32 radius )
{
    p_emtr->radius = radius ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̑S�����������Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityPos( SPLEmitter* p_emtr, fx16 init_vel_mag_pos )
{
    p_emtr->init_vel_mag_pos = init_vel_mag_pos ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̎������������Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitVelocityAxis( SPLEmitter* p_emtr, fx16 init_vel_mag_axis )
{
    p_emtr->init_vel_mag_axis = init_vel_mag_axis ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̊�{�X�P�[�����Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterBaseScale( SPLEmitter* p_emtr, fx16 base_scl )
{
    p_emtr->base_scl = base_scl ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̃p�[�e�B�N���������Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterParticleLife( SPLEmitter* p_emtr, u16 ptcl_life )
{
    p_emtr->ptcl_life = ptcl_life ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̐����Ԋu���Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterEmissionInterval( SPLEmitter* p_emtr, u16 gen_intvl )
{
    p_emtr->etc.gen_intvl = (u8)gen_intvl ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̊�{�����Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterBaseAlpha( SPLEmitter* p_emtr, u16 base_alp )
{
    p_emtr->etc.base_alp = (u8)base_alp ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̃O���[�o���F���Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterGlobalColor( SPLEmitter* p_emtr, GXRgb color )
{
    p_emtr->clr = color ;
}

/* ------------------------------------------------------
 * �G�~�b�^������o�����p�[�e�B�N���̏�����]�p�x
 *------------------------------------------------------*/
static inline void SPL_SetEmitterInitialRotationAngle( SPLEmitter* p_emtr, u16 init_rtt )
{
    p_emtr->init_rtt = init_rtt ;
}



/* ------------------------------------------------------
 * �G�~�b�^�̕��o���[�g���Z�b�g
 *------------------------------------------------------*/
static inline void SPL_SetEmitterGenerationRatio( SPLEmitter* p_emtr, fx32 gen_num )
{
    p_emtr->gen_num = gen_num ;
}

/* ------------------------------------------------------
 * ���[�U�����R�Ɏg�p�ł��郏�[�N�̈�� �Z�b�g  / �Q�b�g
 *------------------------------------------------------*/
static inline void SPL_SetUserWork( SPLEmitter* p_emtr, u32 user_work )
{
    p_emtr->userwork.uw_u32 = user_work ;
}
static inline u32 SPL_GetUserWork( const SPLEmitter* p_emtr )
{
    return p_emtr->userwork.uw_u32 ;
}

static inline void SPL_SetUserWorkU16( SPLEmitter* p_emtr, u16 index, u16 user_work )
{
    p_emtr->userwork.uw_u16[index] = user_work ;
}
static inline u16 SPL_GetUserWorkU16( SPLEmitter* p_emtr, u16 index )
{
    return p_emtr->userwork.uw_u16[index] ;
}

static inline void SPL_SetUserWorkU8( SPLEmitter* p_emtr, u16 index, u8 user_work )
{
    p_emtr->userwork.uw_u8[index] = user_work ;
}
static inline u8 SPL_GetUserWorkU8( SPLEmitter* p_emtr, u16 index )
{
    return p_emtr->userwork.uw_u8[index] ;
}

/* ------------------------------------------------------
 * �擪�̃p�[�e�B�N�����擾����
 *------------------------------------------------------*/
static inline SPLParticle* SPL_GetHeadParticle( const SPLEmitter* p_emtr )
{
    return p_emtr->act_ptcl_list.p_begin ;
}

static inline SPLParticle* SPL_GetChildHeadParticle( const SPLEmitter* p_emtr )
{
    return p_emtr->act_chld_list.p_begin ;
}

/* ------------------------------------------------------
 * �~���G�~�b�^�̔z�u�����W�w�肷�郆�[�e�B���e�B
 *------------------------------------------------------*/
void SPL_Util_SetCylinderEmiterDirection( SPLEmitter* p_emtr, const VecFx32* p1, const VecFx32* p2 ) ;


/* ------------------------------------------------------
 * ���[�U�t���O�̎擾
 *------------------------------------------------------*/
static inline u8 SPL_GetUserFlag( SPLEmitter* p_emtr )
{
    return (u8)p_emtr->p_res->p_base->usr.flag ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̌v�Z�T�C�N�����w�肷��
 *------------------------------------------------------*/
static inline void SPL_SetEmitterCalcCycle( SPLEmitter* p_emtr, u16 cycle )
{
    // cycle��0,1,2�̂ǂꂩ�ł���K�v������B
    p_emtr->etc.calc_cycle = cycle ;
}

/* ------------------------------------------------------
 * �G�~�b�^�̃V���v���R���W����������ύX����
 *------------------------------------------------------*/
static inline void SPL_SetEmitterSimpleCollisionHeight( SPLEmitter* p_emtr, fx32 y )
{
    p_emtr->simple_collision_y = y ;
}





/* ------------------------------------------------------------------------- */

#endif
