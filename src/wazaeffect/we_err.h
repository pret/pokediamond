//==============================================================================
/**
 * @file	we_err.h
 * @brief	技エフェクト関連のデバッグ関係のヘッダ
 * @author	matsuda
 * @date	2005.07.29(金)
 */
//==============================================================================
#ifndef __WE_ERR_H__
#define __WE_ERR_H__

#ifdef PM_DEBUG

#include "wazaeffect/we_mana.h"


//--------------------------------------------------------------
/**
 * @brief   技エフェクト関連のデバッグ用構造体
 */
//--------------------------------------------------------------
typedef struct{
	u16 debug_flag;		///<どのデバッグ機能が有効になっているかのフラグ
	
	VecFx32 emit_pos;	///<エミッタの生成位置

	VecFx32 eye;		///<カメラの位置ベクトル
	VecFx32 up;			///<カメラの上方向のベクトル
	VecFx32 at;			///<カメラの焦点
	
	//各デバッグ処理汎用ワーク
	//複数デバッグ機能を有効にしている場合、使用ワークが被らないように注意
	s32 wait;
	s32 work;
}WE_DEBUG_WORK;

///debug_flagの定義
enum{
	WE_DEBUG_BIT_EMITPOS = 1 << 0,		///<エミッタ生成位置を動かす
	WE_DEBUG_BIT_CAMERA = 1 << 1,		///<カメラを自由に動かす(パーティクル)
};


//==============================================================================
//	グローバル変数
//==============================================================================
extern WE_DEBUG_WORK WeDebugWork;


//==============================================================================
//	外部関数宣言
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

