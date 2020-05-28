/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_manager.h

  �r�o�k�}�l�[�W��

  $Id: spl_manager.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_manager.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.9  2005/08/30 09:15:30  okane_shinji
  SPL_SetDrawOrder��ǉ�

  Revision 1.8  2005/06/27 07:46:14  okane_shinji
  ʣ���ޥ͡�������갷���Ȥ��Ǥ�׻������������꤬ͭ���ˤʤ�褦�˽���

  Revision 1.7  2005/01/20 04:20:48  okane_shinji
  �p�[�e�B�N�����ƃG�~�b�^�����擾����֐��ǉ�

  Revision 1.6  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.5  2004/08/17 05:40:39  okane_shinji
  �p�[�e�B�N���̃|���S��������misc�t���O��ύX�ł���悤�ɕύX�B

  Revision 1.4  2004/07/05 07:33:02  okane_shinji
  �|���S��ID���蓖�Ă��ςɁB�֐�����ύX�B

  Revision 1.3  2004/06/23 07:21:21  okane_shinji
  �J���[�A�j���A���[�v�Đ��A�|���S���A�f�B���N�V���i���r���{�[�h�̉���

  Revision 1.2  2004/05/24 09:44:09  konoh
  ���������m�ۂ̕��@�����[�U�R�[���o�b�N�ōs���悤�ɕύX

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_MANAGER_H__
#define __SPL_MANAGER_H__

#include "spl_emitter.h"
#include "spl_particle.h"
#include "spl_resource.h"
#include "spl_texture.h"

/* �\���̂Ȃ� -------------------------------------------------------------- */

// �������m�ۃR�[���o�b�N
typedef void* (*SPLAlloc)(u32);

// �}�l�[�W���\����
typedef struct SPLManager
{
    // �q�[�v�֌W
    SPLAlloc alloc;

    // ���X�g�֌W
    SPLEmitterList act_emtr_list;
    SPLEmitterList ina_emtr_list;
    SPLParticleList ina_ptcl_list;

    // ���\�[�X�֌W
    SPLResource* res_ary;
    SPLTexture*  tex_ary;
    u16 res_num;
    u16 tex_num;

    u16 max_emtr_num;
    u16 max_ptcl_num;
    
    //u16 min_polygonID ;
    //u16 max_polygonID ;

    struct
    {
        u32 min:6;
        u32 max:6;
        u32 current:6;
        u32 fix:6;
        u32 drawOrder:1;
        u32 reserved:7;
    } polygonID ;

    s32 misc_flag ;

    // �`��E�v�Z�ɕK�v�ȃ}�l�[�W���̃J�����g�����i�[���邽�߂̍\����
    struct
    {
        // ���ݏ������̃G�~�b�^
        SPLEmitter* p_emtr ;

        // ���ݓK�p����Ă���J����
        const MtxFx43*    p_cmr  ;
    } current_state ;


    u16 uCurrentCycle ;
    u16 reserved ;

} SPLManager;

/* ------------------------------------------------------------------------- */

#define SPL_MANAGER_DRAWORDER_INREVERSE 0
#define SPL_MANAGER_DRAWORDER_INTURN    1

/* ------------------------------------------------------
 * �`�揇��ݒ�
 *------------------------------------------------------*/
static inline void SPL_SetDrawOrder( SPLManager* p_mgr, int flag )
{
    p_mgr->polygonID.drawOrder = flag ;
}

/* ------------------------------------------------------
 * �|���S��������misc�t���O��ݒ�
 *------------------------------------------------------*/
static inline void SPL_SetPolygonAttrMiscFlag( SPLManager* p_mgr, int flag )
{
    p_mgr->misc_flag = flag ;
}

/* ------------------------------------------------------
 * ���ݗL���ȃG�~�b�^�̐����擾
 *------------------------------------------------------*/
static inline s32 SPL_GetEmitterNum( SPLManager* p_mgr )
{
    return p_mgr->act_emtr_list.node_num ;
}

/* ------------------------------------------------------
 * ���ݗL���ȃp�[�e�B�N���̐����擾
 *------------------------------------------------------*/
static inline s32 SPL_GetWholeParticleNum( SPLManager* p_mgr )
{
    return p_mgr->max_ptcl_num - p_mgr->ina_ptcl_list.node_num ;
}



#endif
