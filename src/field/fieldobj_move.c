//******************************************************************************
/**
 *
 * @file	fieldobj_move.c
 * @brief	フィールドOBJ 動作系
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "map_tool.h"
#include "fieldobj.h"
#include "field_effect.h"

#include "..\system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_FLDOBJ_MOVE_SUB_TEST	//サブ動作テスト
#ifdef DEBUG_FLDOBJ_MOVE_SUB_TEST
#define DEBUG_MOVE_SUB_TYPE (EV_TYPE_TRAINER_SPIN_MOVE_L)
#define DEBUG_MOVE_SUB_PARAM (2)
#endif

//--------------------------------------------------------------
///	ステータスビット
//--------------------------------------------------------------
///移動動作を禁止するステータスビット
#define STA_BIT_MOVE_ERROR (FLDOBJ_STA_BIT_HEIGHT_GET_ERROR|FLDOBJ_STA_BIT_ATTR_GET_ERROR)

//--------------------------------------------------------------
///	アトリビュートオフセット
//--------------------------------------------------------------
#define ATTROFFS_Y_NUMA 			(NUM_FX32(-12))				///<沼Yオフセット
#define ATTROFFS_Y_NUMA_DEEP		(NUM_FX32(-14))				///<深い沼Yオフセット
#define ATTROFFS_Y_YUKI		 		(NUM_FX32(-12))				///<雪Yオフセット
#define ATTROFFS_Y_YUKI_DEEP		(NUM_FX32(-14))				///<深い雪Yオフセット
#define ATTROFFS_Y_YUKI_DEEP_MOST	(NUM_FX32(-16))				///<更に深い雪Yオフセット

//==============================================================================
//	プロトタイプ
//==============================================================================
static int FldOBJ_MoveStartCheck( CONST_FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveBeforeHeight( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveBeforeAttr( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveStartFirst( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveStartSecond( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MoveEnd( FIELD_OBJ_PTR fldobj );

static void FldOBJ_MapAttrProc_MoveStartFirst( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MapAttrProc_MoveStartSecond( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MapAttrProc_MoveStartJumpSecond( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MapAttrProc_MoveEnd( FIELD_OBJ_PTR fldobj );
static void FldOBJ_MapAttrProc_MoveEndJump( FIELD_OBJ_PTR fldobj );

static void FldOBJ_MapAttrHeight_02(
		FIELD_OBJ_PTR fldobj,MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrGrassProc_12(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrFootMarkProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrSplashProc_012(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrSplashProc_Jump1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrShadowProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrShadowProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrShadowProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrGroundSmokeProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrLGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrLGrassProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrNGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrNGrassProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrPoolProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrPoolProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrSwampProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrSwampProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrReflect_01(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );
static void FldOBJ_MapAttrReflect_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrBridgeProc_01(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static void FldOBJ_MapAttrSEProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state );

static BOOL (* const DATA_HitCheckAttr_Now[DIR_4_MAX])( MATR attr );
static BOOL (* const DATA_HitCheckAttr_Next[DIR_4_MAX])( MATR attr );

//==============================================================================
//	フィールドOBJ 動作
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ 動作初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveInit( FIELD_OBJ_PTR fldobj )
{
#ifdef DEBUG_FLDOBJ_MOVE_SUB_TEST
	{
		if( FieldOBJ_MoveCodeGet(fldobj) == MV_RT2 ){
			FieldOBJ_EventTypeSet( fldobj, DEBUG_MOVE_SUB_TYPE );
			FieldOBJ_ParamSet( fldobj, DEBUG_MOVE_SUB_PARAM, FLDOBJ_PARAM_1 );
		}
	}
#endif
	
	FieldOBJ_MoveInitProcCall( fldobj );
	FieldOBJ_MoveSubProcInit( fldobj );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ動作
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_Move( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_FieldOBJSysStatusBitCheck(fldobj,FLDOBJSYS_STA_BIT_MOVE_PROC_STOP) ){
		return;
	}
	
	FldOBJ_MoveBeforeHeight( fldobj );
	FldOBJ_MoveBeforeAttr( fldobj );
	FldOBJ_MoveStartFirst( fldobj );
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ACMD) ){
		FieldOBJ_AcmdAction( fldobj );
	}else if( FieldOBJ_MovePauseCheck(fldobj) == FALSE ){
		if( FldOBJ_MoveStartCheck(fldobj) == TRUE ){
			if( FieldOBJ_MoveSub(fldobj) == FALSE ){
				FieldOBJ_MoveProcCall( fldobj );
			}
		}
	}
	
	FldOBJ_MoveStartSecond( fldobj );
	FldOBJ_MoveEnd( fldobj );
}

//トレーナーペア動作、親が移動中でも子がアトリビュート系で移動不可の場合
//座標のずれが発生する事がある。
//トレーナーペア動作の子は親を信用し、アトリビュート系でエラーがあっても
//親が移動中であれば移動させるようにする
#if 0
void FieldOBJ_Move( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_FieldOBJSysStatusBitCheck(fldobj,FLDOBJSYS_STA_BIT_MOVE_PROC_STOP) ){
		return;
	}
	
	FldOBJ_MoveBeforeHeight( fldobj );
	FldOBJ_MoveBeforeAttr( fldobj );
	FldOBJ_MoveStartFirst( fldobj );
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ACMD) ){
		FieldOBJ_AcmdAction( fldobj );
	}else if( FieldOBJ_MovePauseCheck(fldobj) == FALSE ){
		if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ||
			FieldOBJ_StatusBit_Check(fldobj,STA_BIT_MOVE_ERROR) == 0 ){
			if( FieldOBJ_MoveSub(fldobj) == FALSE ){
				FieldOBJ_MoveProcCall( fldobj );
			}
		}
	}
	
	FldOBJ_MoveStartSecond( fldobj );
	FldOBJ_MoveEnd( fldobj );
}
#endif

//--------------------------------------------------------------
/**
 * 動作可能かどうかチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=可能,FALSE=不可
 */
//--------------------------------------------------------------
static int FldOBJ_MoveStartCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
		return( TRUE );
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,STA_BIT_MOVE_ERROR) == 0 ){
		return( TRUE );
	}else if( FieldOBJ_MoveCodeGet(fldobj) == MV_TR_PAIR ){		//親の行動に従う
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 移動開始時に行う高さ取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveBeforeHeight( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) ){
		FieldOBJ_VecPosNowHeightGetSet( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * 移動開始時に行うアトリビュート取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveBeforeAttr( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_ATTR_GET_ERROR) ){
		if( FieldOBJ_NowPosMapAttrSet(fldobj) == TRUE ){
			FieldOBJ_StatusBitON_MoveStart( fldobj );
		}
	}
}

//--------------------------------------------------------------
/**
 * 移動開始で発生　1st
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveStartFirst( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_MOVE_START) ){
		FldOBJ_MapAttrProc_MoveStartFirst( fldobj );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj,
		FLDOBJ_STA_BIT_MOVE_START | FLDOBJ_STA_BIT_JUMP_START );
}

//--------------------------------------------------------------
/**
 * 移動開始で発生　2nd
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveStartSecond( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_JUMP_START) ){
		FldOBJ_MapAttrProc_MoveStartJumpSecond( fldobj );
	}else if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_MOVE_START) ){
		FldOBJ_MapAttrProc_MoveStartSecond( fldobj );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj,
		FLDOBJ_STA_BIT_MOVE_START | FLDOBJ_STA_BIT_JUMP_START );
}

//--------------------------------------------------------------
/**
 * 動作終了で発生
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_JUMP_END) ){
		FldOBJ_MapAttrProc_MoveEndJump( fldobj );
	}else if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_MOVE_END) ){
		FldOBJ_MapAttrProc_MoveEnd( fldobj );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj,
		FLDOBJ_STA_BIT_MOVE_END | FLDOBJ_STA_BIT_JUMP_END );
}

//==============================================================================
//	マップアトリビュート
//==============================================================================
//--------------------------------------------------------------
/**
 * 動作開始で発生するアトリビュート処理 1st
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrProc_MoveStartFirst( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_NowPosMapAttrSet( fldobj );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		MATR now = FieldOBJ_NowMapAttrGet( fldobj );
		MATR old = FieldOBJ_OldMapAttrGet( fldobj );
		const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
		FldOBJ_MapAttrBridgeProc_01( fldobj, now, old, state );
		FldOBJ_MapAttrGrassProc_0( fldobj, now, old, state );
		FldOBJ_MapAttrSplashProc_012( fldobj, now, old, state );
		FldOBJ_MapAttrShadowProc_0( fldobj, now, old, state );
		FldOBJ_MapAttrHeight_02( fldobj, now, old, state );
		FldOBJ_MapAttrLGrassProc_0( fldobj, now, old, state );
		FldOBJ_MapAttrNGrassProc_0( fldobj, now, old, state );
		FldOBJ_MapAttrReflect_01( fldobj, now, old, state );
	}
}

//--------------------------------------------------------------
/**
 * 動作開始で発生するアトリビュート処理 2nd
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrProc_MoveStartSecond( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_NowPosMapAttrSet( fldobj );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		MATR now = FieldOBJ_NowMapAttrGet( fldobj );
		MATR old = FieldOBJ_OldMapAttrGet( fldobj );
		const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
		
		FldOBJ_MapAttrBridgeProc_01( fldobj, now, old, state );
		FldOBJ_MapAttrGrassProc_12( fldobj, now, old, state );
		FldOBJ_MapAttrFootMarkProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrSplashProc_012( fldobj, now, old, state );
		FldOBJ_MapAttrShadowProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrLGrassProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrNGrassProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrPoolProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrSwampProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrReflect_01( fldobj, now, old, state );
		
		FldOBJ_MapAttrSEProc_1( fldobj, now, old, state );				//描画関係ない?
	}
}

//--------------------------------------------------------------
/**
 * 動作開始で発生するアトリビュート処理 2nd Jump
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrProc_MoveStartJumpSecond( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_NowPosMapAttrSet( fldobj );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		MATR now = FieldOBJ_NowMapAttrGet( fldobj );
		MATR old = FieldOBJ_OldMapAttrGet( fldobj );
		const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
		
		FldOBJ_MapAttrBridgeProc_01( fldobj, now, old, state );
		FldOBJ_MapAttrShadowProc_1( fldobj, now, old, state );
		FldOBJ_MapAttrReflect_01( fldobj, now, old, state );
		FldOBJ_MapAttrSplashProc_Jump1( fldobj, now, old, state );
		FldOBJ_MapAttrSEProc_1( fldobj, now, old, state );				//描画関係ない?
	}
}

//--------------------------------------------------------------
/**
 * 動作終了で発生するアトリビュート処理　end
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrProc_MoveEnd( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_NowPosMapAttrSet( fldobj );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		MATR now = FieldOBJ_NowMapAttrGet( fldobj );
		MATR old = FieldOBJ_OldMapAttrGet( fldobj );
		const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
		
		//終了　アトリビュート処理
		FldOBJ_MapAttrHeight_02( fldobj, now, old, state );
		FldOBJ_MapAttrPoolProc_2( fldobj, now, old, state );
		FldOBJ_MapAttrSwampProc_2( fldobj, now, old, state );
		FldOBJ_MapAttrSplashProc_012( fldobj, now, old, state );
		FldOBJ_MapAttrReflect_2( fldobj, now, old, state );
		FldOBJ_MapAttrShadowProc_2( fldobj, now, old, state );
	}
}

//--------------------------------------------------------------
/**
 * 動作終了で発生するアトリビュート処理　end jump
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrProc_MoveEndJump( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_NowPosMapAttrSet( fldobj );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		MATR now = FieldOBJ_NowMapAttrGet( fldobj );
		MATR old = FieldOBJ_OldMapAttrGet( fldobj );
		const OBJCODE_STATE *state = FieldOBJ_OBJCodeDrawStateGet( fldobj );
		
		//終了　アトリビュート処理
		FldOBJ_MapAttrHeight_02( fldobj, now, old, state );
		FldOBJ_MapAttrPoolProc_2( fldobj, now, old, state );
		FldOBJ_MapAttrSwampProc_2( fldobj, now, old, state );
		FldOBJ_MapAttrSplashProc_012( fldobj, now, old, state );
		FldOBJ_MapAttrReflect_2( fldobj, now, old, state );
		FldOBJ_MapAttrShadowProc_2( fldobj, now, old, state );
		FldOBJ_MapAttrGrassProc_12( fldobj, now, old, state );
		FldOBJ_MapAttrGroundSmokeProc_2( fldobj, now, old, state );
	}
}

//==============================================================================
//	アトリビュート可変高さ
//==============================================================================
//--------------------------------------------------------------
/**
 * アトリビュート可変高さ　動作開始、動作終了
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrHeight_02(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( FieldOBJ_StatusBitCheck_AttrOffsOFF(fldobj) == FALSE ){
		if( MATR_IsSwampDeep(now) == TRUE || MATR_IsSwampGrassDeep(now) == TRUE ){
			VecFx32 vec = { 0, ATTROFFS_Y_NUMA_DEEP, 0 };
			FieldOBJ_VecAttrOffsSet( fldobj, &vec );
			return;
		}
		
		if( MATR_IsSwamp(now) == TRUE || MATR_IsSwampGrass(now) == TRUE ){
			VecFx32 vec = { 0, ATTROFFS_Y_NUMA, 0 };
			FieldOBJ_VecAttrOffsSet( fldobj, &vec );
			return;
		}
		
		if( MATR_IsSnowDeepMost(now) == TRUE ){
			VecFx32 vec = { 0, ATTROFFS_Y_YUKI_DEEP_MOST, 0 };
			FieldOBJ_VecAttrOffsSet( fldobj, &vec );
			return;
		}
		
		if( MATR_IsSnowDeep(now) == TRUE ){
			VecFx32 vec = { 0, ATTROFFS_Y_YUKI_DEEP, 0 };
			FieldOBJ_VecAttrOffsSet( fldobj, &vec );
			return;
		}
		
		
		if( MATR_IsShallowSnow(now) == TRUE ){
			VecFx32 vec = { 0, ATTROFFS_Y_YUKI, 0 };
			FieldOBJ_VecAttrOffsSet( fldobj, &vec );
			return;
		}
	}
	
	{
		VecFx32 vec = { 0, 0, 0 };
		FieldOBJ_VecAttrOffsSet( fldobj, &vec );
	}
}

//==============================================================================
//	アトリビュート　草
//==============================================================================
//--------------------------------------------------------------
/**
 * 草　動作開始 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsGrass(now) == TRUE ){
		FE_FldOBJGrass_Add( fldobj, FALSE );
	}
}

//--------------------------------------------------------------
/**
 * 草　動作 1,2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrGrassProc_12(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsGrass(now) == TRUE ){
		FE_FldOBJGrass_Add( fldobj, TRUE );
	}
}

//==============================================================================
//	アトリビュート　足跡
//==============================================================================
//--------------------------------------------------------------
/**
 * 足跡　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrFootMarkProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( state->type_footmark == FLDOBJ_FOOTMARK_NON ){
		return;
	}
	
	if( FieldOBJ_MapAttrKindCheck_Sand(fldobj,old) == TRUE ){
		if( state->type_footmark == FLDOBJ_FOOTMARK_NORMAL ){
			FE_FldOBJFootMarkNormal_Add( fldobj );
		}else if( state->type_footmark == FLDOBJ_FOOTMARK_CYCLE ){
			FE_FldOBJFootMarkCycle_Add( fldobj );
		}
		return;
	}
	
	if( MATR_IsSnowDeep(old) == TRUE || MATR_IsSnowDeepMost(old) == TRUE ||
		MATR_IsShallowSnow(old) ){
		FE_FldOBJFootMarkSnowDeep_Add( fldobj );
		return;
	}
	
	if( FieldOBJ_MapAttrKindCheck_MostShallowSnow(fldobj,old) == TRUE ){
		FE_FldOBJFootMarkSnow_Add( fldobj );
		return;
	}
}

//==============================================================================
//	アトリビュート　水飛沫
//==============================================================================
//--------------------------------------------------------------
/**
 * 水飛沫　動作開始終了 012
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSplashProc_012(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsShoal(now) == TRUE ){
		if( FieldOBJ_StatusBitCheck_ShoalEffectSet(fldobj) == FALSE ){
			FE_FldOBJSplash_Add( fldobj, TRUE );
			FieldOBJ_StatusBitSet_ShoalEffectSet( fldobj, TRUE );
		}
	}else{
		FieldOBJ_StatusBitSet_ShoalEffectSet( fldobj, FALSE );
	}
}

//--------------------------------------------------------------
/**
 * 水飛沫　ジャンプ動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSplashProc_Jump1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	FieldOBJ_StatusBitSet_ShoalEffectSet( fldobj, FALSE );
}

//==============================================================================
///	アトリビュート　影
//==============================================================================
//--------------------------------------------------------------
/**
 * 影　動作開始 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrShadowProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	FldOBJ_MapAttrShadowProc_1( fldobj, now, old, state );
}

//--------------------------------------------------------------
/**
 * 影　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrShadowProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	{
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
		
		if( FieldOBJSys_ShadowJoinCheck(fos) == FALSE ){
			return;
		}
	}
	
	if( state->type_shadow == FLDOBJ_SHADOW_NON ){
		return;
	}
	
	if( MATR_IsGrass(now) == TRUE ||
		MATR_IsLongGrass(now) == TRUE ||
		FieldOBJ_MapAttrKindCheck_Water(fldobj,now) == TRUE ||
		MATR_IsPoolCheck(now) == TRUE ||
		MATR_IsShoal(now) == TRUE ||
		FieldOBJ_MapAttrKindCheck_Snow(fldobj,now) == TRUE ||
		MATR_IsSwamp(now) == TRUE ||
		MATR_IsSwampGrass(now) == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}else{
		if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_SHADOW_SET) == 0 ){
			FE_FldOBJShadow_Add( fldobj );
			FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_SET );
		}
	}
}

//--------------------------------------------------------------
/**
 * 影　動作終了 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrShadowProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	{
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
		
		if( FieldOBJSys_ShadowJoinCheck(fos) == FALSE ){
			return;
		}
	}
	
	if( state->type_shadow == FLDOBJ_SHADOW_NON ){
		return;
	}
	
	if( MATR_IsGrass(now) == TRUE ||
		MATR_IsLongGrass(now) == TRUE ||
		FieldOBJ_MapAttrKindCheck_Water(fldobj,now) == TRUE ||
		MATR_IsPoolCheck(now) == TRUE ||
		MATR_IsShoal(now) == TRUE ||
		FieldOBJ_MapAttrKindCheck_Snow(fldobj,now) == TRUE ||
		MATR_IsSwamp(now) == TRUE ||
		MATR_IsSwampGrass(now) == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}
}

//==============================================================================
//	アトリビュート　土煙
//==============================================================================
//--------------------------------------------------------------
/**
 * 土煙　動作終了 2 
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrGroundSmokeProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( FieldOBJ_MapAttrKindCheck_Water(fldobj,now) == TRUE ||
		MATR_IsShoal(now) == TRUE ||
		MATR_IsIce(now) == TRUE ||
		MATR_IsSwamp(now) == TRUE ||
		MATR_IsSwampGrass(now) == TRUE ||
		FieldOBJ_MapAttrKindCheck_Snow(fldobj,now) == TRUE ){
		return;
	}
	
	FE_FldOBJKemuri_Add( fldobj );
}

//==============================================================================
//	アトリビュート　長い草
//==============================================================================
//--------------------------------------------------------------
/**
 * 長い草　動作開始 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrLGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsLongGrass(now) == TRUE ){
		FE_FldOBJLGrass_Add( fldobj, FALSE );
	}
}

//--------------------------------------------------------------
/**
 * 長い草　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrLGrassProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsLongGrass(now) == TRUE ){
		FE_FldOBJLGrass_Add( fldobj, TRUE );
	}
}

//==============================================================================
//	アトリビュート　沼草
//==============================================================================
//--------------------------------------------------------------
/**
 * 沼草　動作開始 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrNGrassProc_0(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsSwampGrass(now) == TRUE ){
		FE_FldOBJNGrass_Add( fldobj, FALSE );
	}
}

//--------------------------------------------------------------
/**
 * 沼草　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrNGrassProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsSwampGrass(now) == TRUE ){
		FE_FldOBJNGrass_Add( fldobj, TRUE );
	}
}

//==============================================================================
//	アトリビュート　水たまり
//==============================================================================
//--------------------------------------------------------------
/**
 * 水たまり　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrPoolProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsPoolCheck(old) == TRUE ){
		FE_FldOBJRippleSet( fldobj,
			FieldOBJ_OldPosGX_Get(fldobj),
			FieldOBJ_OldPosGY_Get(fldobj), 
			FieldOBJ_OldPosGZ_Get(fldobj) );
	}
}

//--------------------------------------------------------------
/**
 * 水たまり　動作終了 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrPoolProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsPoolCheck(now) == TRUE ){
		FE_FldOBJRippleSet( fldobj,
			FieldOBJ_NowPosGX_Get(fldobj),
			FieldOBJ_NowPosGY_Get(fldobj), 
			FieldOBJ_NowPosGZ_Get(fldobj) );
	}
}

//==============================================================================
//	アトリビュート　沼
//==============================================================================
//--------------------------------------------------------------
/**
 * 沼　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSwampProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsSwamp(old) == TRUE ){
		FE_FldOBJNRippleSet( fldobj,
			FieldOBJ_OldPosGX_Get(fldobj),
			FieldOBJ_OldPosGY_Get(fldobj), 
			FieldOBJ_OldPosGZ_Get(fldobj) );
	}
}

//--------------------------------------------------------------
/**
 * 沼　動作終了 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSwampProc_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsSwamp(now) == TRUE ){
		FE_FldOBJNRippleSet( fldobj,
			FieldOBJ_NowPosGX_Get(fldobj),
			FieldOBJ_NowPosGY_Get(fldobj), 
			FieldOBJ_NowPosGZ_Get(fldobj) );
	}
}

//==============================================================================
//	アトリビュート　映りこみ
//==============================================================================
//--------------------------------------------------------------
/**
 * 映りこみ　動作開始 01
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrReflect_01(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( state->type_reflect == FLDOBJ_REFLECT_NON ){
		return;
	}
	
	{
		MATR attr = FieldOBJ_NextDirAttrGet( fldobj, DIR_DOWN );
		
		if( FieldOBJ_StatusBitCheck_Reflect(fldobj) == FALSE ){
			if( MATR_IsReflect(attr) == TRUE || MATR_IsReflect(now) == TRUE ){
				FieldOBJ_StatusBitSet_Reflect( fldobj, TRUE );
				
				if( MATR_IsPoolCheck(attr) == TRUE ){	//水溜り
					FE_FldOBJReflect_Add( fldobj, REFTYPE_POOL );
				}else{									//池
					FE_FldOBJReflect_Add( fldobj, REFTYPE_POND );
				}
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * 映りこみ　動作終了 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrReflect_2(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( state->type_reflect == FLDOBJ_REFLECT_NON ||
		FieldOBJ_StatusBitCheck_Reflect(fldobj) == FALSE ){
		return;
	}
	
	{
		MATR attr = FieldOBJ_NextDirAttrGet( fldobj, DIR_DOWN );
		
		if( MATR_IsReflect(attr) == FALSE ){
			FieldOBJ_StatusBitSet_Reflect( fldobj, FALSE );
		}
	}
}

//==============================================================================
//	アトリビュート　橋
//==============================================================================
//--------------------------------------------------------------
/**
 * 橋　動作開始 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			現在のアトリビュート
 * @param	old			過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrBridgeProc_01(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	if( MATR_IsBridgeFlag(now) == TRUE ){
		FieldOBJ_StatusBitSet_Bridge( fldobj, TRUE );
	}else if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
		if( MATR_IsBridge(now) == FALSE ){
			FieldOBJ_StatusBitSet_Bridge( fldobj, FALSE );
		}
	}
}

//==============================================================================
//	アトリビュート関連SE
//==============================================================================
//--------------------------------------------------------------
/**
 * SE　動作開始 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		現在のアトリビュート
 * @param	old		過去のアトリビュート
 * @param	state		OBJCODE_STATE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSEProc_1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
#if 0
	if( MATR_IsSnow(now) ){
		Snd_SePlay( SEQ_SE_DP_YUKIASHI );
	}
#endif
}

//==============================================================================
//	座標チェック
//==============================================================================
//--------------------------------------------------------------
/**
 * 指定座標障害物チェック
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @param	x		チェックするX座標	グリッド
 * @param	z		チェックするZ座標	グリッド
 * @retval	u32		ヒットビット。FLDOBJ_MOVE_HIT_BIT_LIM等
 */
//--------------------------------------------------------------
u32 FieldOBJ_PosHitCheck( CONST_FIELD_OBJ_SYS_PTR fos, int x, int z )
{
	u32 ret;
	
	ret = FLDOBJ_MOVE_HIT_BIT_NON;
	
	if(	GetHitAttr(FieldOBJSys_FieldSysWorkGet(fos),x,z) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_ATTR;
	}
	
	if( FieldOBJ_SearchGPos(fos,x,z) != NULL ){
		ret |= FLDOBJ_MOVE_HIT_BIT_OBJ;
	}
	
	return( ret );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ移動チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		現在実座標
 * @param	x		移動先X座標	グリッド
 * @param	y		移動先Y座標
 * @param	z		移動先Z座標	グリッド
 * @param	dir		移動方向 DIR_UP等
 * @retval	u32		ヒットビット。FLDOBJ_MOVE_HIT_BIT_LIM等
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveHitCheck(
		CONST_FIELD_OBJ_PTR fldobj, const VecFx32 *vec, int x, int y, int z, int dir )
{
	u32 ret;
	
	ret = FLDOBJ_MOVE_HIT_BIT_NON;
	
	if( FieldOBJ_MoveHitCheckLimit(fldobj,x,y,z) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_LIM;
	}
	
	{
		s8 flag;
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		
		if( MPTL_CheckHitWall(fsys,vec,x,z,&flag) == TRUE ){
			ret |= FLDOBJ_MOVE_HIT_BIT_ATTR;
			
			if( flag != HIT_RES_EQUAL ){
				ret |= FLDOBJ_MOVE_HIT_BIT_HEIGHT;
			}
		}
	}
	
	if( FieldOBJ_MoveHitCheckAttr(fldobj,x,z,dir) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_ATTR;
	}
	
	if( FieldOBJ_MoveHitCheckFellow(fldobj,x,y,z) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_OBJ;
	}
	
	return( ret );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ移動チェック　現在位置から判定
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		移動先X座標	グリッド
 * @param	y		移動先X座標
 * @param	z		移動先X座標	グリッド
 * @param	dir		移動方向 DIR_UP等
 * @retval	u32		ヒットビット。FLDOBJ_MOVE_HIT_BIT_LIM等
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveHitCheckNow( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z, int dir )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	return( FieldOBJ_MoveHitCheck(fldobj,&vec,x,y,z,dir) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ移動チェック　現在位置+方向版
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	dir		移動する方向。DIR_UP等
 * @retval	u32		ヒットビット。FLDOBJ_MOVE_HIT_BIT_LIM等
 */
//--------------------------------------------------------------
u32 FieldOBJ_MoveHitCheckDir( CONST_FIELD_OBJ_PTR fldobj, int dir )
{
	int x,y,z;
	
	x = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
	y = FieldOBJ_NowPosGY_Get( fldobj );
	z = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
	
	return( FieldOBJ_MoveHitCheckNow(fldobj,x,y,z,dir) );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ同士の衝突チェック
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		移動先X座標	グリッド
 * @param	y		移動先X座標	グリッド
 * @param	z		移動先X座標	グリッド
 * @retval	int		TRUE=衝突アリ
 */
//--------------------------------------------------------------
int FieldOBJ_MoveHitCheckFellow( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z )
{
	int max,hx,hz;
	CONST_FIELD_OBJ_SYS_PTR sys;
	CONST_FIELD_OBJ_PTR fieldobj;
	
	sys = FieldOBJ_FieldOBJSysGet( fldobj );
	fieldobj = FieldOBJSys_FieldOBJWorkGet( sys );
	max = FieldOBJSys_OBJMaxGet( sys );
	
	do{
		if( fieldobj != fldobj ){
			if( FieldOBJ_StatusBit_Check(fieldobj,FLDOBJ_STA_BIT_USE) ){
				if( FieldOBJ_StatusBit_Check(fieldobj,FLDOBJ_STA_BIT_FELLOW_HIT_NON) == 0 ){
					hx = FieldOBJ_NowPosGX_Get( fieldobj );
					hz = FieldOBJ_NowPosGZ_Get( fieldobj );
			
					if( hx == x && hz == z ){
						int hy = FieldOBJ_NowPosGY_Get( fieldobj );
						int sy = hy - y;
						if( sy < 0 ){ sy = -sy; }
						if( sy < H_GRID_FELLOW_SIZE ){
							return( TRUE );
						}
					}
			
					hx = FieldOBJ_OldPosGX_Get( fieldobj );
					hz = FieldOBJ_OldPosGZ_Get( fieldobj );
			
					if( hx == x && hz == z ){
						int hy = FieldOBJ_NowPosGY_Get( fieldobj );
						int sy = hy - y;
						if( sy < 0 ){ sy = -sy; }
						if( sy < H_GRID_FELLOW_SIZE ){
							return( TRUE );
						}
					}
				}
			}
		}
		
		FieldOBJSys_FieldOBJWorkInc( &fieldobj );
		max--;
	}while( max );
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ移動制限チェック
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		移動先X座標	グリッド
 * @param	y		移動先Y座標	グリッド
 * @param	z		移動先Z座標	グリッド
 * @retval	int		TRUE=制限越え
 */
//--------------------------------------------------------------
int FieldOBJ_MoveHitCheckLimit( CONST_FIELD_OBJ_PTR fldobj, int x, int y, int z )
{
	int init,limit,min,max;
	
	init = FieldOBJ_InitPosGX_Get( fldobj );
	limit = FieldOBJ_MoveLimitXGet( fldobj );
	
	if( limit != MOVE_LIMIT_NOT ){
		min = init - limit;
		max = init + limit;
	
		if( min > x || max < x ){
			return( TRUE );
		}
	}
	
	init = FieldOBJ_InitPosGZ_Get( fldobj );
	limit = FieldOBJ_MoveLimitZGet( fldobj );
	
	if( limit != MOVE_LIMIT_NOT ){
		min = init - limit;
		max = init + limit;
	
		if( min > z || max < z ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJアトリビュートヒットチェック
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		移動先X座標	グリッド
 * @param	z		移動先Z座標	グリッド
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=移動不可アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MoveHitCheckAttr( CONST_FIELD_OBJ_PTR fldobj, int x, int z, int dir )
{
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	MATR now_attr = FieldOBJ_NowMapAttrGet( fldobj );
	MATR next_attr = GetAttributeLSB( fsys, x, z );
	
	GF_ASSERT( dir != DIR_NOT && "FieldOBJ_MoveHitCheckAttr()dir = DIR_NOT 方向異常" );
	GF_ASSERT( dir < DIR_4_MAX && "FieldOBJ_MoveHitCheckAttr()dir値異常" );
	
	if( DATA_HitCheckAttr_Now[dir](now_attr) == TRUE ||
		DATA_HitCheckAttr_Next[dir](next_attr) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	現在位置アトリビュートから判定する移動制御アトリビュートチェック関数
//--------------------------------------------------------------
static BOOL (* const DATA_HitCheckAttr_Now[DIR_4_MAX])( MATR attr ) =
{
	MATR_IsBadMoveUpCheck,
	MATR_IsBadMoveDownCheck,
	MATR_IsBadMoveLeftCheck,
	MATR_IsBadMoveRightCheck,
};

//--------------------------------------------------------------
///	未来位置アトリビュートから判定する移動制御アトリビュートチェック関数
//--------------------------------------------------------------
static BOOL (* const DATA_HitCheckAttr_Next[DIR_4_MAX])( MATR attr ) =
{
	MATR_IsBadMoveDownCheck,
	MATR_IsBadMoveUpCheck,
	MATR_IsBadMoveRightCheck,
	MATR_IsBadMoveLeftCheck,
};

//--------------------------------------------------------------
/**
 * 橋を考慮した水アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_Water( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( MATR_IsBridgeWater(attr) ){
		if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == FALSE ){
			return( TRUE );
		}
	}else if( MATR_IsWater(attr) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した砂アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_Sand( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( MATR_IsBridgeSand(attr) ){
		if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == FALSE ){
			return( TRUE );
		}
	}else if( MATR_IsSand(attr) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した雪アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_Snow( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( MATR_IsBridgeSnowShallow(attr) ){
		if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == FALSE ){
			return( TRUE );
		}
	}else if( MATR_IsSnow(attr) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した浅い雪アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_MostShallowSnow( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( MATR_IsBridgeSnowShallow(attr) ){
		if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == FALSE ){
			return( TRUE );
		}
	}else if( MATR_IsMostShallowSnow(attr) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した橋アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_Bridge( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
		if( MATR_IsBridge(attr) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した一本橋縦アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_BridgeV( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
		if( MATR_IsBridgeV(attr) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 橋を考慮した一本橋横アトリビュートチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	アトリビュート
 * @retval	int		TRUE=水アトリビュート
 */
//--------------------------------------------------------------
int FieldOBJ_MapAttrKindCheck_BridgeH( FIELD_OBJ_PTR fldobj, u32 attr )
{
	if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
		if( MATR_IsBridgeH(attr) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	グリッド座標移動系
//==============================================================================
//--------------------------------------------------------------
///	4方向別座標増減　X
//--------------------------------------------------------------
static const int DATA_GPosX_Dir4AddTbl[] =
{ 0, 0, -1, 1 };

//--------------------------------------------------------------
///	4方向別座標増減　Y
//--------------------------------------------------------------
static const int DATA_GPosY_Dir4AddTbl[] =
{ 0, 0, 0, 0 };

//--------------------------------------------------------------
///	4方向別座標増減　Z
//--------------------------------------------------------------
static const int DATA_GPosZ_Dir4AddTbl[] =
{ -1, 1, 0, 0 };

//--------------------------------------------------------------
/**
 * 方向からX方向増減値を取得
 * @param	dir		方向。DIR_UP等
 * @retval	int		グリッド単位での増減値
 */
//--------------------------------------------------------------
int FieldOBJ_DirAddValueGX( int dir )
{
	return( DATA_GPosX_Dir4AddTbl[dir] );
}

//--------------------------------------------------------------
/**
 * 方向からZ方向増減値を取得
 * @param	dir		方向。DIR_UP等
 * @retval	int		グリッド単位での増減値
 */
//--------------------------------------------------------------
int FieldOBJ_DirAddValueGZ( int dir )
{
	return( DATA_GPosZ_Dir4AddTbl[dir] );
}

//--------------------------------------------------------------
/**
 * 方向で現在座標を更新
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			移動方向
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_NowGPosDirAdd( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_OldPosGX_Set( fldobj, FieldOBJ_NowPosGX_Get(fldobj) );
	FieldOBJ_OldPosGY_Set( fldobj, FieldOBJ_NowPosGY_Get(fldobj) );
	FieldOBJ_OldPosGZ_Set( fldobj, FieldOBJ_NowPosGZ_Get(fldobj) );
	
	FieldOBJ_NowPosGX_Add( fldobj, FieldOBJ_DirAddValueGX(dir) );
	FieldOBJ_NowPosGY_Add( fldobj, 0 );
	FieldOBJ_NowPosGZ_Add( fldobj, FieldOBJ_DirAddValueGZ(dir) );
}

//--------------------------------------------------------------
/**
 * 現在座標で過去座標を更新
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_GPosUpdate( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_OldPosGX_Set( fldobj, FieldOBJ_NowPosGX_Get(fldobj) );
	FieldOBJ_OldPosGY_Set( fldobj, FieldOBJ_NowPosGY_Get(fldobj) );
	FieldOBJ_OldPosGZ_Set( fldobj, FieldOBJ_NowPosGZ_Get(fldobj) );
}

//--------------------------------------------------------------
/**
 * 現在のグリッド座標から指定方向先のアトリビュートを取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		DIR_UP等
 * @retval	u32		MATR
 */
//--------------------------------------------------------------
u32 FieldOBJ_NextDirAttrGet( FIELD_OBJ_PTR fldobj, int dir )
{
	int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
	int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	MATR attr = GetAttributeLSB( fsys, gx, gz );
	
	return( attr );
}

//==============================================================================
//	3D座標系
//==============================================================================
//--------------------------------------------------------------
/**
 * 指定値を加算する
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	val			移動量
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosAdd( FIELD_OBJ_PTR fldobj, const VecFx32 *val )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	
	vec.x += val->x;
	vec.y += val->y;
	vec.z += val->z;
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * 指定値を指定方向に加算する
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			移動4方向。DIR_UP等
 * @param	val			移動量(正
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_VecPosDirAdd( FIELD_OBJ_PTR fldobj, int dir, fx32 val )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	
	switch( dir ){
	case DIR_UP:		vec.z -= val;	break;
	case DIR_DOWN:		vec.z += val;	break;
	case DIR_LEFT:		vec.x -= val;	break;
	case DIR_RIGHT:		vec.x += val;	break;
	}
	
	FieldOBJ_VecPosSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * 現在座標から高さ取得し実座標に反映
 * FLDOBJ_STA_BIT_HEIGHT_GET_ERRORのセットも併せて行う
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int		TRUE=高さが取れた。FALSE=取れない。FLDOBJ_STA_BIT_HEIGHT_GET_ERRORで取得可能
 */
//--------------------------------------------------------------
int FieldOBJ_VecPosNowHeightGetSet( FIELD_OBJ_PTR fldobj )
{
	VecFx32 vec_pos,vec_pos_h;
	
	FieldOBJ_VecPosGet( fldobj, &vec_pos );
	vec_pos_h = vec_pos;
	
	if( FieldOBJ_HeightOFFCheck(fldobj) == TRUE ){
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_ERROR );
		return( FALSE );
	}
	
	{
		int eflag = FieldOBJ_StatusBitCheck_HeightExpand( fldobj );
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int ret = FieldOBJTool_GetHeightExpand( fsys, &vec_pos_h, eflag );
		
		if( ret == TRUE ){
			vec_pos.y = vec_pos_h.y;
			FieldOBJ_VecPosSet( fldobj, &vec_pos );
			FieldOBJ_OldPosGY_Set( fldobj, FieldOBJ_NowPosGY_Get(fldobj) );
			FieldOBJ_NowPosGY_Set( fldobj, SIZE_H_GRID_FX32(vec_pos.y) );
			FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_ERROR );
		}else{
			FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_HEIGHT_GET_ERROR );
		}
		
		return( ret );
	}
}

//--------------------------------------------------------------
/**
 * 現在座標でアトリビュート反映
 * FLDOBJ_STA_BIT_ATTR_GET_ERRORのセットも併せて行う
 * @retval	int		TRUE=取得成功。FALSE=失敗。
 */
//--------------------------------------------------------------
int FieldOBJ_NowPosMapAttrSet( FIELD_OBJ_PTR fldobj )
{
	int gx = FieldOBJ_OldPosGX_Get( fldobj );
	int gz = FieldOBJ_OldPosGZ_Get( fldobj );
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	MATR attr = GetAttributeLSB( fsys, gx, gz );
	FieldOBJ_OldMapAttrSet( fldobj, attr );
	
	gx = FieldOBJ_NowPosGX_Get( fldobj );
	gz = FieldOBJ_NowPosGZ_Get( fldobj );
	attr = GetAttributeLSB( fsys, gx, gz );
	FieldOBJ_NowMapAttrSet( fldobj, attr );
	
#if 0	
	{
		OS_Printf( "アトリビュート取得　ATTR=0x%x, X=0x%x, Z=0x%x, OBJCODE =0x%x　",attr, gx, gz, FieldOBJ_OBJCodeGet(fldobj) );
		
		if( MATR_IsNotAttr(attr) == TRUE ){
			OS_Printf( "アトリビュート取得…異常\n" );
		}else{
			OS_Printf( "アトリビュート取得…正常\n" );
		}
	}
#endif
	
	if( MATR_IsNotAttr(attr) == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_ATTR_GET_ERROR );
		return( FALSE );
	}
	
	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ATTR_GET_ERROR );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 指定値を指定方向に加算する
 * @param	dir			移動4方向。DIR_UP等
 * @param	vec			加える対象
 * @param	val			移動量(正
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJTool_VecPosDirAdd( int dir, VecFx32 *vec, fx32 val )
{
	switch( dir ){
	case DIR_UP:		vec->z -= val;	break;
	case DIR_DOWN:		vec->z += val;	break;
	case DIR_LEFT:		vec->x -= val;	break;
	case DIR_RIGHT:		vec->x += val;	break;
	}
}

//--------------------------------------------------------------
/**
 * 指定されたグリッド座標の中心位置を実座標で取得
 * @param	gx	グリッドX座標	
 * @param	gz	グリッドZ座標
 * @param	vec	座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJTool_GridCenterPosGet( int gx, int gz, VecFx32 *vec )
{
	vec->x = GRID_SIZE_FX32( gx ) + GRID_HALF_FX32;
	vec->z = GRID_SIZE_FX32( gz ) + GRID_HALF_FX32;
}

//--------------------------------------------------------------
/**
 * 指定された実座標をグリッド単位に直す
 * @param	gx	グリッドX座標格納先
 * @param	gy	グリッドY座標格納先
 * @param	gz	グリッドZ座標格納先
 * @param	vec	変換する座標
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJTool_VectorGridPosGet( int *gx, int *gy, int *gz, const VecFx32 *vec )
{
	*gx = SIZE_GRID_FX32( vec->x );
	*gy = SIZE_H_GRID_FX32( vec->y );
	*gz = SIZE_GRID_FX32( vec->z );
}

//==============================================================================
//	その他パーツ
//==============================================================================
//--------------------------------------------------------------
//	方向反転テーブル
//--------------------------------------------------------------
static const int DATA_DirFlipTbl[] =
{ DIR_DOWN, DIR_UP, DIR_RIGHT, DIR_LEFT };

//--------------------------------------------------------------
/**
 * 与えられた方向を反転する
 * @param	dir		DIR_UP等
 * @retval	int		dirの反転方向
 */
//--------------------------------------------------------------
int FieldOBJTool_DirFlip( int dir )
{
	return( DATA_DirFlipTbl[dir] );
}

//--------------------------------------------------------------
/**
 * 距離間方向を取得
 * @param	ax	対象A X座標
 * @param	az	対象A Z座標
 * @param	bx	対象B X座標
 * @param	bz	対象B Z座標
 * @retval	int	対象Aから対象Bへの方向 DIR_UP等
 */
//--------------------------------------------------------------
int FieldOBJTool_DirRange( int ax, int az, int bx, int bz )
{
	if( ax > bx ){ return( DIR_LEFT ); }
	if( ax < bx ){ return( DIR_RIGHT ); }
	if( az > bz ){ return( DIR_UP ); }
	
	return( DIR_DOWN );
}

//--------------------------------------------------------------
/**
 * 高さ取得
 * @param	fsys	FIELDSYS_WORK *
 * @param	vec		高さ取得するX,Y,Z格納ポインタ。Yは高さ取得で更新
 * @retval	int		TRUE=正常取得　FALSE=高さ設定無し
 */
//--------------------------------------------------------------
int FieldOBJTool_GetHeight( FIELDSYS_WORK *fsys, VecFx32 *vec )
{
	fx32 y;
	HEIGHT_TYPE flag;
	
	y = GetHeightPack( fsys, vec->y, vec->x, vec->z, &flag );
	
	if( flag == HEIGHT_FAIL ){
		return( FALSE );
	}
	
	vec->y = y;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 高さ取得
 * @param	fsys	FIELDSYS_WORK *
 * @param	vec		高さ取得するX,Y,Z格納ポインタ。Yは高さ取得で更新
 * @param	eflag	TRUE=拡張高さ反応
 * @retval	int		TRUE=正常取得　FALSE=高さ設定無し
 */
//--------------------------------------------------------------
int FieldOBJTool_GetHeightExpand( FIELDSYS_WORK *fsys, VecFx32 *vec, int eflag )
{
	fx32 y;
	HEIGHT_TYPE flag;
	
	y = GetHeightPack( fsys, vec->y, vec->x, vec->z, &flag );
	
	if( flag == HEIGHT_FAIL ){
		return( FALSE );
	}
	
	if( flag == HEIGHT_EXPAND && eflag == FALSE ){
		return( FALSE );
	}
	
	vec->y = y;
	return( TRUE );
}
