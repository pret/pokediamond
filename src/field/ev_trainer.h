//******************************************************************************
/**
 *
 * @file	ev_trainer.h
 * @brief	トレーナー視線イベント
 * @author	kagaya
 * @data	05.10.03
 *
 */
//******************************************************************************
#ifndef EV_TRAINER_H_FILE
#define EV_TRAINER_H_FILE

//==============================================================================
//	incldue
//==============================================================================
#include "field_common.h"

//==============================================================================
//	define
//==============================================================================
#define EYE_CHECK_NOHIT (-1)					///<視線範囲チェック戻り値　ヒットなし

//==============================================================================
//	外部宣言
//==============================================================================
extern int EvTrainerEyeCheck( FIELDSYS_WORK *fsys, BOOL vs2 );

extern int EvTrainer_EyeLangeCheck(
	CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int *hit_dir );

extern int EvTrainerFldOBJTrainerIDGet( FIELD_OBJ_PTR fldobj );

extern TCB_PTR EvTrainerEyeMoveSet( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe, int tr_type, int pos );
extern int EvTrainerEyeMoveEndCheck( TCB_PTR tcb );
extern void EvTrainerEyeMoveEnd( TCB_PTR tcb );

//==============================================================================
//	デバッグ
//==============================================================================
#ifdef PM_DEBUG
//#define DEBUG_EV_LABEL							//定義で仮イベントラベル生成有効
#endif

#ifdef DEBUG_EV_LABEL
extern void DebugEvLabelInit( FIELDSYS_WORK *fsys, int max );
extern void DebugEvLabelFree( FIELDSYS_WORK *fsys );
extern void DebugEvLabelClear( FIELDSYS_WORK *fsys );
extern int DebugEvLabelTrainerFightCheck( int obj_id );
extern void DebugEvLabelTrainerFightEnd( int obj_id );
#endif

#endif //EV_TRAINER_H_FILE
