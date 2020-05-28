//==============================================================================
/**
 * @file	we_err.h
 * @brief	�Z�G�t�F�N�g�֘A�̃f�o�b�O�֌W�̃w�b�_
 * @author	matsuda
 * @date	2005.07.29(��)
 */
//==============================================================================
#ifndef __WE_ERR_H__
#define __WE_ERR_H__

#ifdef PM_DEBUG

#include "wazaeffect/we_mana.h"


//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g�֘A�̃f�o�b�O�p�\����
 */
//--------------------------------------------------------------
typedef struct{
	u16 debug_flag;		///<�ǂ̃f�o�b�O�@�\���L���ɂȂ��Ă��邩�̃t���O
	
	VecFx32 emit_pos;	///<�G�~�b�^�̐����ʒu

	VecFx32 eye;		///<�J�����̈ʒu�x�N�g��
	VecFx32 up;			///<�J�����̏�����̃x�N�g��
	VecFx32 at;			///<�J�����̏œ_
	
	//�e�f�o�b�O�����ėp���[�N
	//�����f�o�b�O�@�\��L���ɂ��Ă���ꍇ�A�g�p���[�N�����Ȃ��悤�ɒ���
	s32 wait;
	s32 work;
}WE_DEBUG_WORK;

///debug_flag�̒�`
enum{
	WE_DEBUG_BIT_EMITPOS = 1 << 0,		///<�G�~�b�^�����ʒu�𓮂���
	WE_DEBUG_BIT_CAMERA = 1 << 1,		///<�J���������R�ɓ�����(�p�[�e�B�N��)
};


//==============================================================================
//	�O���[�o���ϐ�
//==============================================================================
extern WE_DEBUG_WORK WeDebugWork;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void DebugParticle_EmitMove(PTC_PTR ptc, EMIT_PTR emit, const VecFx32 *vec);
extern void DebugParticle_EmitMove2(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys);
extern void DebugParticle_CameraMove(PTC_PTR ptc);
extern void DebugParticle_CameraMove2(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys);
extern void DebugParticle_Axis(PTC_PTR ptc, EMIT_PTR emit);
extern void DebugParticle_AxisLoop(PTC_PTR ptc, int index, int cb_no, WE_SYS_PTR we_sys);

extern void DebugWazaEffect_LoopEmitter(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys);

#endif	//PM_DEBUG
#endif	//__WE_ERR_H__

