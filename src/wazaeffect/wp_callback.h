//==============================================================================
/**
 * @file	wp_callback.h
 * @brief	技エフェクトエミッタ生成時に呼び出される汎用コールバック関数などのヘッダ
 * @author	matsuda
 * @date	2005.08.03(水)
 */
//==============================================================================
#ifndef __WP_CALLBACK_H__
#define __WP_CALLBACK_H__

#define AXIS_EX_MODE_NONE	 		(0)		///< 何もなし
#define AXIS_EX_MODE_DEFAULT_CNV	(1)		///< デフォルトの値で集束
#define AXIS_EX_MODE_CENTER_CNV		(2)		///< 中央に集束
#define AXIS_EX_MODE_TP_CNV			(3)		///< 対象ポケモンに集束
#define AXIS_EX_MODE_PP_CNV			(4)		///< 基点ポケモンに集束
#define AXIS_EX_MODE_SET_CNV		(5)		///< 指定位置で集束

#define AXIS_EX_MODE_DEFAULT_MAG	(1)		///< デフォルトの値で集束
#define AXIS_EX_MODE_CENTER_MAG		(2)		///< 中央に集束
#define AXIS_EX_MODE_TP_MAG			(3)		///< 対象ポケモンに集束
#define AXIS_EX_MODE_PP_MAG			(4)		///< 基点ポケモンに集束
#define AXIS_EX_MODE_SET_MAG		(5)		///< 指定位置で集束

//==============================================================================
//	外部関数宣言
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

// ----- 集束操作系 -----
extern void EmitCall_AxisAttack_DefaultCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_CenterCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_TargetPokemonCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PlayerPokemonCNV(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PosSetCNV(EMIT_PTR emit);

// ----- マグネット操作系 -----
extern void EmitCall_AxisAttack_DefaultMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_CenterMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_TargetPokemonMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PlayerPokemonMAG(EMIT_PTR emit);
extern void EmitCall_AxisAttack_PosSetMAG(EMIT_PTR emit);


extern void EmitCall_InitSpeedSet(EMIT_PTR emit);

extern void EmitCall_Debug(EMIT_PTR emit);
extern void EmitCall_AttackPosSet(EMIT_PTR emit);

#endif	//__WP_CALLBACK_H__


