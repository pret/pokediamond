//******************************************************************************
/**
 *
 * @file	fieldobj_move.c
 * @brief	�t�B�[���hOBJ ����n
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
//#define DEBUG_FLDOBJ_MOVE_SUB_TEST	//�T�u����e�X�g
#ifdef DEBUG_FLDOBJ_MOVE_SUB_TEST
#define DEBUG_MOVE_SUB_TYPE (EV_TYPE_TRAINER_SPIN_MOVE_L)
#define DEBUG_MOVE_SUB_PARAM (2)
#endif

//--------------------------------------------------------------
///	�X�e�[�^�X�r�b�g
//--------------------------------------------------------------
///�ړ�������֎~����X�e�[�^�X�r�b�g
#define STA_BIT_MOVE_ERROR (FLDOBJ_STA_BIT_HEIGHT_GET_ERROR|FLDOBJ_STA_BIT_ATTR_GET_ERROR)

//--------------------------------------------------------------
///	�A�g���r���[�g�I�t�Z�b�g
//--------------------------------------------------------------
#define ATTROFFS_Y_NUMA 			(NUM_FX32(-12))				///<��Y�I�t�Z�b�g
#define ATTROFFS_Y_NUMA_DEEP		(NUM_FX32(-14))				///<�[����Y�I�t�Z�b�g
#define ATTROFFS_Y_YUKI		 		(NUM_FX32(-12))				///<��Y�I�t�Z�b�g
#define ATTROFFS_Y_YUKI_DEEP		(NUM_FX32(-14))				///<�[����Y�I�t�Z�b�g
#define ATTROFFS_Y_YUKI_DEEP_MOST	(NUM_FX32(-16))				///<�X�ɐ[����Y�I�t�Z�b�g

//==============================================================================
//	�v���g�^�C�v
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
//	�t�B�[���hOBJ ����
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ ���쏉����
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
 * �t�B�[���hOBJ����
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

//�g���[�i�[�y�A����A�e���ړ����ł��q���A�g���r���[�g�n�ňړ��s�̏ꍇ
//���W�̂��ꂪ�������鎖������B
//�g���[�i�[�y�A����̎q�͐e��M�p���A�A�g���r���[�g�n�ŃG���[�������Ă�
//�e���ړ����ł���Έړ�������悤�ɂ���
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
 * ����\���ǂ����`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=�\,FALSE=�s��
 */
//--------------------------------------------------------------
static int FldOBJ_MoveStartCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
		return( TRUE );
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,STA_BIT_MOVE_ERROR) == 0 ){
		return( TRUE );
	}else if( FieldOBJ_MoveCodeGet(fldobj) == MV_TR_PAIR ){		//�e�̍s���ɏ]��
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ړ��J�n���ɍs�������擾
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
 * �ړ��J�n���ɍs���A�g���r���[�g�擾
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
 * �ړ��J�n�Ŕ����@1st
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
 * �ړ��J�n�Ŕ����@2nd
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
 * ����I���Ŕ���
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
//	�}�b�v�A�g���r���[�g
//==============================================================================
//--------------------------------------------------------------
/**
 * ����J�n�Ŕ�������A�g���r���[�g���� 1st
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
 * ����J�n�Ŕ�������A�g���r���[�g���� 2nd
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
		
		FldOBJ_MapAttrSEProc_1( fldobj, now, old, state );				//�`��֌W�Ȃ�?
	}
}

//--------------------------------------------------------------
/**
 * ����J�n�Ŕ�������A�g���r���[�g���� 2nd Jump
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
		FldOBJ_MapAttrSEProc_1( fldobj, now, old, state );				//�`��֌W�Ȃ�?
	}
}

//--------------------------------------------------------------
/**
 * ����I���Ŕ�������A�g���r���[�g�����@end
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
		
		//�I���@�A�g���r���[�g����
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
 * ����I���Ŕ�������A�g���r���[�g�����@end jump
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
		
		//�I���@�A�g���r���[�g����
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
//	�A�g���r���[�g�ύ���
//==============================================================================
//--------------------------------------------------------------
/**
 * �A�g���r���[�g�ύ����@����J�n�A����I��
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����J�n 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
 * ���@���� 1,2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@����
//==============================================================================
//--------------------------------------------------------------
/**
 * ���Ձ@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@����
//==============================================================================
//--------------------------------------------------------------
/**
 * ���򖗁@����J�n�I�� 012
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
 * ���򖗁@�W�����v����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJ_MapAttrSplashProc_Jump1(
		FIELD_OBJ_PTR fldobj, MATR now, MATR old, const OBJCODE_STATE *state )
{
	FieldOBJ_StatusBitSet_ShoalEffectSet( fldobj, FALSE );
}

//==============================================================================
///	�A�g���r���[�g�@�e
//==============================================================================
//--------------------------------------------------------------
/**
 * �e�@����J�n 0
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
 * �e�@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
 * �e�@����I�� 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@�y��
//==============================================================================
//--------------------------------------------------------------
/**
 * �y���@����I�� 2 
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@������
//==============================================================================
//--------------------------------------------------------------
/**
 * �������@����J�n 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
 * �������@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@����
//==============================================================================
//--------------------------------------------------------------
/**
 * �����@����J�n 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
 * �����@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@�����܂�
//==============================================================================
//--------------------------------------------------------------
/**
 * �����܂�@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
 * �����܂�@����I�� 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
 * ���@����I�� 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@�f�肱��
//==============================================================================
//--------------------------------------------------------------
/**
 * �f�肱�݁@����J�n 01
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
				
				if( MATR_IsPoolCheck(attr) == TRUE ){	//������
					FE_FldOBJReflect_Add( fldobj, REFTYPE_POOL );
				}else{									//�r
					FE_FldOBJReflect_Add( fldobj, REFTYPE_POND );
				}
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * �f�肱�݁@����I�� 2
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�@��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����J�n 0
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	now			���݂̃A�g���r���[�g
 * @param	old			�ߋ��̃A�g���r���[�g
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
//	�A�g���r���[�g�֘ASE
//==============================================================================
//--------------------------------------------------------------
/**
 * SE�@����J�n 1
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	now		���݂̃A�g���r���[�g
 * @param	old		�ߋ��̃A�g���r���[�g
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
//	���W�`�F�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �w����W��Q���`�F�b�N
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @param	x		�`�F�b�N����X���W	�O���b�h
 * @param	z		�`�F�b�N����Z���W	�O���b�h
 * @retval	u32		�q�b�g�r�b�g�BFLDOBJ_MOVE_HIT_BIT_LIM��
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
 * �t�B�[���hOBJ�ړ��`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		���ݎ����W
 * @param	x		�ړ���X���W	�O���b�h
 * @param	y		�ړ���Y���W
 * @param	z		�ړ���Z���W	�O���b�h
 * @param	dir		�ړ����� DIR_UP��
 * @retval	u32		�q�b�g�r�b�g�BFLDOBJ_MOVE_HIT_BIT_LIM��
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
 * �t�B�[���hOBJ�ړ��`�F�b�N�@���݈ʒu���画��
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�ړ���X���W	�O���b�h
 * @param	y		�ړ���X���W
 * @param	z		�ړ���X���W	�O���b�h
 * @param	dir		�ړ����� DIR_UP��
 * @retval	u32		�q�b�g�r�b�g�BFLDOBJ_MOVE_HIT_BIT_LIM��
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
 * �t�B�[���hOBJ�ړ��`�F�b�N�@���݈ʒu+������
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	dir		�ړ���������BDIR_UP��
 * @retval	u32		�q�b�g�r�b�g�BFLDOBJ_MOVE_HIT_BIT_LIM��
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
 * �t�B�[���hOBJ���m�̏Փ˃`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�ړ���X���W	�O���b�h
 * @param	y		�ړ���X���W	�O���b�h
 * @param	z		�ړ���X���W	�O���b�h
 * @retval	int		TRUE=�Փ˃A��
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
 * �t�B�[���hOBJ�ړ������`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�ړ���X���W	�O���b�h
 * @param	y		�ړ���Y���W	�O���b�h
 * @param	z		�ړ���Z���W	�O���b�h
 * @retval	int		TRUE=�����z��
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
 * �t�B�[���hOBJ�A�g���r���[�g�q�b�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR 
 * @param	x		�ړ���X���W	�O���b�h
 * @param	z		�ړ���Z���W	�O���b�h
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=�ړ��s�A�g���r���[�g
 */
//--------------------------------------------------------------
int FieldOBJ_MoveHitCheckAttr( CONST_FIELD_OBJ_PTR fldobj, int x, int z, int dir )
{
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	MATR now_attr = FieldOBJ_NowMapAttrGet( fldobj );
	MATR next_attr = GetAttributeLSB( fsys, x, z );
	
	GF_ASSERT( dir != DIR_NOT && "FieldOBJ_MoveHitCheckAttr()dir = DIR_NOT �����ُ�" );
	GF_ASSERT( dir < DIR_4_MAX && "FieldOBJ_MoveHitCheckAttr()dir�l�ُ�" );
	
	if( DATA_HitCheckAttr_Now[dir](now_attr) == TRUE ||
		DATA_HitCheckAttr_Next[dir](next_attr) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	���݈ʒu�A�g���r���[�g���画�肷��ړ�����A�g���r���[�g�`�F�b�N�֐�
//--------------------------------------------------------------
static BOOL (* const DATA_HitCheckAttr_Now[DIR_4_MAX])( MATR attr ) =
{
	MATR_IsBadMoveUpCheck,
	MATR_IsBadMoveDownCheck,
	MATR_IsBadMoveLeftCheck,
	MATR_IsBadMoveRightCheck,
};

//--------------------------------------------------------------
///	�����ʒu�A�g���r���[�g���画�肷��ړ�����A�g���r���[�g�`�F�b�N�֐�
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
 * �����l���������A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l���������A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l��������A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l�������󂢐�A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l���������A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l��������{���c�A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
 * �����l��������{�����A�g���r���[�g�`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=���A�g���r���[�g
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
//	�O���b�h���W�ړ��n
//==============================================================================
//--------------------------------------------------------------
///	4�����ʍ��W�����@X
//--------------------------------------------------------------
static const int DATA_GPosX_Dir4AddTbl[] =
{ 0, 0, -1, 1 };

//--------------------------------------------------------------
///	4�����ʍ��W�����@Y
//--------------------------------------------------------------
static const int DATA_GPosY_Dir4AddTbl[] =
{ 0, 0, 0, 0 };

//--------------------------------------------------------------
///	4�����ʍ��W�����@Z
//--------------------------------------------------------------
static const int DATA_GPosZ_Dir4AddTbl[] =
{ -1, 1, 0, 0 };

//--------------------------------------------------------------
/**
 * ��������X���������l���擾
 * @param	dir		�����BDIR_UP��
 * @retval	int		�O���b�h�P�ʂł̑����l
 */
//--------------------------------------------------------------
int FieldOBJ_DirAddValueGX( int dir )
{
	return( DATA_GPosX_Dir4AddTbl[dir] );
}

//--------------------------------------------------------------
/**
 * ��������Z���������l���擾
 * @param	dir		�����BDIR_UP��
 * @retval	int		�O���b�h�P�ʂł̑����l
 */
//--------------------------------------------------------------
int FieldOBJ_DirAddValueGZ( int dir )
{
	return( DATA_GPosZ_Dir4AddTbl[dir] );
}

//--------------------------------------------------------------
/**
 * �����Ō��ݍ��W���X�V
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			�ړ�����
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
 * ���ݍ��W�ŉߋ����W���X�V
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
 * ���݂̃O���b�h���W����w�������̃A�g���r���[�g���擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		DIR_UP��
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
//	3D���W�n
//==============================================================================
//--------------------------------------------------------------
/**
 * �w��l�����Z����
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	val			�ړ���
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
 * �w��l���w������ɉ��Z����
 * @param	fldobj		FIELD_OBJ_PTR 
 * @param	dir			�ړ�4�����BDIR_UP��
 * @param	val			�ړ���(��
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
 * ���ݍ��W���獂���擾�������W�ɔ��f
 * FLDOBJ_STA_BIT_HEIGHT_GET_ERROR�̃Z�b�g�������čs��
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int		TRUE=��������ꂽ�BFALSE=���Ȃ��BFLDOBJ_STA_BIT_HEIGHT_GET_ERROR�Ŏ擾�\
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
 * ���ݍ��W�ŃA�g���r���[�g���f
 * FLDOBJ_STA_BIT_ATTR_GET_ERROR�̃Z�b�g�������čs��
 * @retval	int		TRUE=�擾�����BFALSE=���s�B
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
		OS_Printf( "�A�g���r���[�g�擾�@ATTR=0x%x, X=0x%x, Z=0x%x, OBJCODE =0x%x�@",attr, gx, gz, FieldOBJ_OBJCodeGet(fldobj) );
		
		if( MATR_IsNotAttr(attr) == TRUE ){
			OS_Printf( "�A�g���r���[�g�擾�c�ُ�\n" );
		}else{
			OS_Printf( "�A�g���r���[�g�擾�c����\n" );
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
 * �w��l���w������ɉ��Z����
 * @param	dir			�ړ�4�����BDIR_UP��
 * @param	vec			������Ώ�
 * @param	val			�ړ���(��
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
 * �w�肳�ꂽ�O���b�h���W�̒��S�ʒu�������W�Ŏ擾
 * @param	gx	�O���b�hX���W	
 * @param	gz	�O���b�hZ���W
 * @param	vec	���W�i�[��
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
 * �w�肳�ꂽ�����W���O���b�h�P�ʂɒ���
 * @param	gx	�O���b�hX���W�i�[��
 * @param	gy	�O���b�hY���W�i�[��
 * @param	gz	�O���b�hZ���W�i�[��
 * @param	vec	�ϊ�������W
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
//	���̑��p�[�c
//==============================================================================
//--------------------------------------------------------------
//	�������]�e�[�u��
//--------------------------------------------------------------
static const int DATA_DirFlipTbl[] =
{ DIR_DOWN, DIR_UP, DIR_RIGHT, DIR_LEFT };

//--------------------------------------------------------------
/**
 * �^����ꂽ�����𔽓]����
 * @param	dir		DIR_UP��
 * @retval	int		dir�̔��]����
 */
//--------------------------------------------------------------
int FieldOBJTool_DirFlip( int dir )
{
	return( DATA_DirFlipTbl[dir] );
}

//--------------------------------------------------------------
/**
 * �����ԕ������擾
 * @param	ax	�Ώ�A X���W
 * @param	az	�Ώ�A Z���W
 * @param	bx	�Ώ�B X���W
 * @param	bz	�Ώ�B Z���W
 * @retval	int	�Ώ�A����Ώ�B�ւ̕��� DIR_UP��
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
 * �����擾
 * @param	fsys	FIELDSYS_WORK *
 * @param	vec		�����擾����X,Y,Z�i�[�|�C���^�BY�͍����擾�ōX�V
 * @retval	int		TRUE=����擾�@FALSE=�����ݒ薳��
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
 * �����擾
 * @param	fsys	FIELDSYS_WORK *
 * @param	vec		�����擾����X,Y,Z�i�[�|�C���^�BY�͍����擾�ōX�V
 * @param	eflag	TRUE=�g����������
 * @retval	int		TRUE=����擾�@FALSE=�����ݒ薳��
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
