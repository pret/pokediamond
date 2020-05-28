//==============================================================================
/**
 * @file	wpcb.h
 * @brief	関数などを書く
 * @author	goto
 * @date	2006.02.12(日)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
#ifndef __WPCB_H__
#define __WPCB_H__

#ifdef PM_DEBUG

/* ---
	wpcb_xxx.x で扱うデバッグ用コマンドのON/OFFを操作する
--- */

	
#if 0	///< 自由にパーティクル要素を操作する
	#define WPCB_FREE_EMITTER_MOVE
#endif

#endif

// -----------------------------------------
//
// wpcb_operator.c
//
// -----------------------------------------
extern void ECB_Operator(EMIT_PTR emit);
extern s8	ECB_Operator_ReverceFlag(ECB_OPERATOR_DATA* odp);


// -----------------------------------------
//
// wpcb_field.c
//
// -----------------------------------------
extern void FieldOperator_Executed(int no, EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
extern int	FieldOperator_BitGet(int no);
extern int	FieldOperator_BitDataMax(void);

// -----------------------------------------
//
// wpcb_camera.c
//
// -----------------------------------------
extern void CameraOperator_Executed(int no, EMIT_PTR emit, ECB_OPERATOR_DATA* odp);


// -----------------------------------------
//
// wpcb_debug.c
//
// -----------------------------------------
extern void Debug_OperatorStatusPrint(ECB_OPERATOR_DATA* odp);

#endif

