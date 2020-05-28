//==============================================================================
/**
 * @file	wp_callback.h
 * @brief	�Z�G�t�F�N�g�G�~�b�^�������ɌĂяo�����ėp�R�[���o�b�N�֐��Ȃǂ̃w�b�_
 * @author	matsuda
 * @date	2005.08.03(��)
 */
//==============================================================================
#ifndef __WP_CALLBACK_H__
#define __WP_CALLBACK_H__

#define AXIS_EX_MODE_NONE	 		(0)		///< �����Ȃ�
#define AXIS_EX_MODE_DEFAULT_CNV	(1)		///< �f�t�H���g�̒l�ŏW��
#define AXIS_EX_MODE_CENTER_CNV		(2)		///< �����ɏW��
#define AXIS_EX_MODE_TP_CNV			(3)		///< �Ώۃ|�P�����ɏW��
#define AXIS_EX_MODE_PP_CNV			(4)		///< ��_�|�P�����ɏW��
#define AXIS_EX_MODE_SET_CNV		(5)		///< �w��ʒu�ŏW��

#define AXIS_EX_MODE_DEFAULT_MAG	(1)		///< �f�t�H���g�̒l�ŏW��
#define AXIS_EX_MODE_CENTER_MAG		(2)		///< �����ɏW��
#define AXIS_EX_MODE_TP_MAG			(3)		///< �Ώۃ|�P�����ɏW��
#define AXIS_EX_MODE_PP_MAG			(4)		///< ��_�|�P�����ɏW��
#define AXIS_EX_MODE_SET_MAG		(5)		///< �w��ʒu�ŏW��

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void EmitCall_CameraReverseAttack(EMIT_PTR emit);
extern void EmitCall_CameraReverseDefence(EMIT_PTR emit);
extern void EmitCall_DefencePos(EMIT_PTR emit);
extern void EmitCall_AttackPos(EMIT_PTR emit);
extern void EmitCall_AxisDefence(EMIT_PTR emit);
extern void EmitCall_AxisAttack(EMIT_PTR emit);
extern void EmitCall_SepPos(EMIT_PTR emit);
extern void EmitCall_DFsidePos(EMIT_PTR emit);
extern void EmitCall_ATsidePos(EMIT_PTR emit);
extern void EmitCall_ATPosCR(EMIT_PTR emit);

// ----- �W������n -----
extern void EmitCall_AxisAttack_DefaultCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_CenterCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_TargetPokemonCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PlayerPokemonCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PosSetCNV(EMIT_PTR emit);

// ----- �}�O�l�b�g����n -----
extern void EmitCall_AxisAttack_DefaultMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_CenterMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_TargetPokemonMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PlayerPokemonMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PosSetMAG(EMIT_PTR emit);


extern void EmitCall_InitSpeedSet(EMIT_PTR emit);

extern void EmitCall_Debug(EMIT_PTR emit);
extern void EmitCall_AttackPosSet(EMIT_PTR emit);

#endif	//__WP_CALLBACK_H__


