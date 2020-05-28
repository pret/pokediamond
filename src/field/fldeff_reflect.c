//******************************************************************************
/**
 * 
 * @file	fldeff_reflect.c
 * @brief	�t�B�[���hOBJ�f�肱��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "player.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define REF_SCALE_X_UP (FX32_ONE+(FX32_ONE/8))
#define REF_SCALE_X_DOWN (FX32_ONE-(FX32_ONE/8))
#define REF_SCALE_X_SPEED (FX32_ONE/64)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_GRASS_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_REFLECT * FE_REFLECT_PTR;

//--------------------------------------------------------------
///	FE_REFLECT�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_REFLECT
{
	FE_SYS *fes;
}FE_REFLECT;

#define FE_REFLECT_SIZE (sizeof(FE_REFLECT))	///<FE_REFLECT�T�C�Y

//--------------------------------------------------------------
///	REF_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_REFLECT_PTR fe_ref;
	FIELD_OBJ_PTR fldobj;
}REF_ADD_H;

#define REF_ADD_H_SIZE (sizeof(REF_ADD_H))		///<REF_ADD_H�T�C�Y

//--------------------------------------------------------------
///	REF_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int obj_id;
	int zone_id;
	int obj_code;
	int act_init_flag;
	REFTYPE type;
	REF_ADD_H head;
	BLACT_WORK_PTR act;
	VecFx32 scale;
	fx32 scale_val_x;
}REF_WORK;

#define REF_WORK_SIZE (sizeof(REF_WORK))		///<REF_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Reflect_GraphicInit( FE_REFLECT_PTR ref );
static void Reflect_GraphicDelete( FE_REFLECT_PTR ref );

static const EOA_H_NPP DATA_EoaH_Reflect;

static void EoaReflectVecGet( REF_WORK *work, FIELD_OBJ_PTR fldobj, VecFx32 *vec );
static void EoaReflectAddAct( EOA_PTR eoa, REF_WORK *work );

//==============================================================================
//	�f�肱��	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �f�肱�ݏ�����
 * @param	fes		FE_SYS *
 * @retval	void*	�G�t�F�N�g�g�p���[�N
 */
//--------------------------------------------------------------
void * FE_Reflect_Init( FE_SYS *fes )
{
	FE_REFLECT_PTR ref;
	
	ref = FE_AllocClearMemory( fes, FE_REFLECT_SIZE, ALLOC_FR, 0 );
	ref->fes = fes;
	Reflect_GraphicInit( ref );
	return( ref );
}

//--------------------------------------------------------------
/**
 * �f�肱�ݍ폜
 * @param	void	�G�t�F�N�g�g�p���[�N
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Reflect_Delete( void *work )
{
	FE_REFLECT_PTR ref = work;
	Reflect_GraphicDelete( ref );
	FE_FreeMemory( ref );
}

//==============================================================================
//	�f�肱�݁@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�O���t�B�b�N������
 * @param	ref		FE_REFLECT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Reflect_GraphicInit( FE_REFLECT_PTR ref )
{
	FE_BlActResAdd_MdlArc( ref->fes, FE_RESID_MDL_REFLECT, NARC_fldeff_mirror_nsbmd );
}

//--------------------------------------------------------------
/**
 * �f�肱�݁@�O���t�B�b�N�폜
 * @param	ref		FE_REFLECT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Reflect_GraphicDelete( FE_REFLECT_PTR ref )
{
	FE_BlActResDelete_Mdl( ref->fes, FE_RESID_MDL_REFLECT );
}

//==============================================================================
//	�f�肱�݁@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �f�肱�ݒǉ�
 * @param	fldobj	�Ώ�FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJReflect_Add( FIELD_OBJ_PTR fldobj, REFTYPE type )
{
	int pri;
	VecFx32 mtx;
	REF_ADD_H head;
	EOA_PTR eoa;
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.fe_ref = FE_EffectWorkGet( head.fes, FE_FLD_REFLECT );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( head.fes, &DATA_EoaH_Reflect, &mtx, type, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I�� FALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaReflect_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	REF_WORK *work;
	const REF_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	work->type = EOA_AddParamGet( eoa );
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->obj_code = FieldOBJ_OBJCodeGet( work->head.fldobj );
	
	if( FieldOBJ_OBJCodeSeedCheck(work->obj_code) == TRUE ){
		work->obj_code = FieldOBJ_OBJCodeSeedGet( work->head.fldobj );
	}
	
	work->scale.x = FX32_ONE;
	work->scale.y = FX32_ONE;
	work->scale.z = FX32_ONE;
	work->scale_val_x = REF_SCALE_X_SPEED;
	
	EoaReflectVecGet( work, work->head.fldobj, &mtx );
	EOA_MatrixSet( eoa, &mtx );
	EoaReflectAddAct( eoa, work );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflect_Delete( EOA_PTR eoa, void *wk )
{
	REF_WORK *work;
	
	work = wk;
	
	if( work->act_init_flag == TRUE ){
		BLACT_Delete( work->act );
	}
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflect_Move( EOA_PTR eoa, void *wk )
{
	int code;
	REF_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	code = FieldOBJ_OBJCodeGet( fldobj );
	
	if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
		code = FieldOBJ_OBJCodeSeedGet( work->head.fldobj );
	}
	
	if( work->obj_code != code ||
		FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ||
		FieldOBJ_StatusBitCheck_Reflect(fldobj) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	work->scale.x += work->scale_val_x;
		
	if( work->scale.x >= REF_SCALE_X_UP ){
		work->scale.x = REF_SCALE_X_UP;
		work->scale_val_x = -work->scale_val_x;
	}else if( work->scale.x <= REF_SCALE_X_DOWN ){
		work->scale.x = REF_SCALE_X_DOWN;
		work->scale_val_x = -work->scale_val_x;
	}
	
	{
		VecFx32 vec;
		EoaReflectVecGet( work, fldobj, &vec );
		EOA_MatrixSet( eoa, &vec );
	}
	
	{
		if( work->act_init_flag == FALSE ){
			EoaReflectAddAct( eoa, work );
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflect_Draw( EOA_PTR eoa, void *wk )
{
	REF_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	{
		int code = FieldOBJ_OBJCodeGet( fldobj );
	
		if( FieldOBJ_OBJCodeSeedCheck(code) == TRUE ){
			code = FieldOBJ_OBJCodeSeedGet( work->head.fldobj );
		}
	
		if( work->obj_code != code ||
			FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ||
			FieldOBJ_StatusBitCheck_Reflect(fldobj) == FALSE ){
			FE_EoaDelete( eoa );
			return;
		}
	}
	
	if( work->act_init_flag == FALSE ){
		return;
	}
	
	if( FieldOBJ_StatusBitCheck_Vanish(fldobj) == TRUE ){
		BLACT_ObjDrawFlagSet( work->act, FALSE );
	}else{
		BLACT_ObjDrawFlagSet( work->act, TRUE );
	}
	
	{
		VecFx32 vec;
		EOA_MatrixGet( eoa, &vec );
		BLACT_MatrixSet( work->act, &vec );
	}
	
	BLACT_ScaleSet( work->act, &work->scale );
	
	{
		BLACT_WORK_PTR act = FieldOBJ_DrawBlAct00_BlActPtrGet( work->head.fldobj );
		BLACT_AnmOffsChg( work->act, BLACT_AnmOffsGet(act) );
		BLACT_AnmFrameSet( work->act, BLACT_AnmFrameGet(act) );
	}
}

//--------------------------------------------------------------
///	�f�肱��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Reflect =
{
	REF_WORK_SIZE,
	EoaReflect_Init,
	EoaReflect_Delete,
	EoaReflect_Move,
	EoaReflect_Draw,
};

//--------------------------------------------------------------
/**
 * �f�肱�ݍ��W�Z�b�g
 * @param	fldobj	�Ώۂ�FIELD_OBJ_PTR	
 * @param	vec		���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectVecGet( REF_WORK *work, FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	int ret;
	fx32 x,z;
	fx32 offs[REFTYPE_MAX] = { NUM_FX32(12), NUM_FX32(16) };
	
#if 0	//�I�t�Z�b�g���l�����Ȃ�
	FieldOBJ_VecPosGet( fldobj, vec );
	
	ret = FieldOBJTool_GetHeight( work->head.fsys, vec );
	
	vec->z += NUM_FX32( -7 );
#else
	FieldOBJ_VecDrawOffsGet( fldobj, vec );
	x = vec->x;
	z = -vec->z;
	
	FieldOBJ_VecPosGet( fldobj, vec );
	ret = FieldOBJTool_GetHeight( work->head.fsys, vec );
	
	vec->x += x;
	vec->z += z + NUM_FX32( -7 );
#endif
	
	if( ret == FALSE ){
		vec->y = 0;
	}else{
		vec->y -= offs[work->type];
	}
}

//--------------------------------------------------------------
/**
 * �f�肱�ݑΏۂ̃w�b�_���擾���A�N�^�[�Z�b�g
 * @param	work	REF_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectAddAct( EOA_PTR eoa, REF_WORK *work )
{
	int ret;
	void *mdl;
	VecFx32 mtx;
	BLACT_HEADER act_head;
	
	{
		CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( work->head.fldobj );
	
		if( FieldOBJ_BlActHeaderGetOBJCode(fos,work->obj_code,&act_head) == FALSE ){
			return;
		}
		
		if( FieldOBJ_BlActAddPracFlagCheck(work->head.fldobj) == TRUE ){
			return;
		}
	}
	
	mdl = FE_BlActResGet_Mdl( work->head.fes, FE_RESID_MDL_REFLECT );
	act_head.ImdRes = mdl;
	
	EOA_MatrixGet( eoa, &mtx );
	work->act = FE_BlActAdd( work->head.fes, &act_head, &mtx );
	work->act_init_flag = TRUE;
}

//==============================================================================
//	�r���{�[�h����f�荞��	
//==============================================================================
//--------------------------------------------------------------
///	REFSOLE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_REFLECT_PTR fe_ref;
	BLACT_HEADER act_head;
	CONST_BLACT_WORK_PTR oya_act;
}REFSOLE_ADD_H;

//--------------------------------------------------------------
///	REFSOLE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	REFTYPE type;
	REFSOLE_ADD_H head;
	BLACT_WORK_PTR act;
	VecFx32 scale;
	fx32 scale_val_x;
	VecFx32 mtx;
}REFSOLE_WORK;

static const EOA_H_NPP DATA_EoaH_ReflectSole;

//--------------------------------------------------------------
/**
 * �f�肱�ݑΏۂ̃w�b�_���擾���A�N�^�[�Z�b�g
 * @param	work	REF_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectSoleAddAct( EOA_PTR eoa, REFSOLE_WORK *work )
{
	int ret;
	void *mdl;
	VecFx32 mtx;
	BLACT_HEADER act_head = work->head.act_head;
	
	mdl = FE_BlActResGet_Mdl( work->head.fes, FE_RESID_MDL_REFLECT );
	act_head.ImdRes = mdl;
	
	EOA_MatrixGet( eoa, &mtx );
	work->act = FE_BlActAdd( work->head.fes, &act_head, &mtx );
	
	{
		CONST_BLACT_WORK_PTR act = work->head.oya_act;
		BLACT_AnmOffsChg( work->act, BLACT_AnmOffsGet(act) );
		BLACT_AnmFrameSetOffs( work->act, BLACT_AnmFrameGetOffs(act) );
		BLACT_AnmFrameSet( work->act, BLACT_AnmFrameGet(act) );
		BLACT_AnmFrameChg( work->act, 0 );
		BLACT_VramAnmTransUserReq( work->act );
	}
}

//--------------------------------------------------------------
/**
 * �f�肱�ݍ��W�Z�b�g
 * @param	work	REFSOLE_WORK
 * @param	vec		���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectSoleVecGet( REFSOLE_WORK *work, VecFx32 *vec )
{
	int ret;
	VecFx32 mtx;
	fx32 x;
	fx32 offs[REFTYPE_MAX] = { NUM_FX32(12), NUM_FX32(16) };
	
	*vec = work->mtx;
	ret = FieldOBJTool_GetHeight( work->head.fsys, vec );
	vec->z += NUM_FX32( -7 );
	
	if( ret == FALSE ){
		vec->y = 0;
	}else{
		vec->y -= offs[work->type];
	}
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݃Z�b�g
 * @param	fes		FE_SYS *
 * @param	head	�f�荞��BLACT_HEADER
 * @param	act		�f�荞�ݑΏ�BLACT_WORK_PTR
 * @param	type	REFTYPE
 * @param	mtx		�f�荞�ݍ��W
 * @retval	EOA_PTR	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_EoaReflectSole_Add( FE_SYS *fes,
	const BLACT_HEADER *act_head, CONST_BLACT_WORK_PTR act, const VecFx32 *mtx,
	REFTYPE type, int pri )
{
	EOA_PTR eoa;
	REFSOLE_ADD_H head;
	
	head.fsys = FE_FieldSysWorkGet( fes );
	head.fes = fes;
	head.fe_ref = FE_EffectWorkGet( fes, FE_FLD_REFLECT );
	head.act_head = *act_head;
	head.oya_act = act;
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_ReflectSole, mtx, type, &head, pri );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I�� FALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaReflectSole_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	REFSOLE_WORK *work;
	const REFSOLE_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	work->type = EOA_AddParamGet( eoa );
	
	work->scale.x = FX32_ONE;
	work->scale.y = FX32_ONE;
	work->scale.z = FX32_ONE;
	work->scale_val_x = REF_SCALE_X_SPEED;
	
	EOA_MatrixGet( eoa, &work->mtx );
	
	EoaReflectSoleVecGet( work, &mtx );
	EOA_MatrixSet( eoa, &mtx );
	EoaReflectSoleAddAct( eoa, work );
	
	EOA_MoveProcCall( eoa );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectSole_Delete( EOA_PTR eoa, void *wk )
{
	REFSOLE_WORK *work;
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectSole_Move( EOA_PTR eoa, void *wk )
{
	REFSOLE_WORK *work = wk;
	
	work->scale.x += work->scale_val_x;
		
	if( work->scale.x >= REF_SCALE_X_UP ){
		work->scale.x = REF_SCALE_X_UP;
		work->scale_val_x = -work->scale_val_x;
	}else if( work->scale.x <= REF_SCALE_X_DOWN ){
		work->scale.x = REF_SCALE_X_DOWN;
		work->scale_val_x = -work->scale_val_x;
	}
	
	{
		VecFx32 vec;
		EoaReflectSoleVecGet( work, &vec );
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA �f�肱�݁@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaReflectSole_Draw( EOA_PTR eoa, void *wk )
{
	REFSOLE_WORK *work = wk;
	
	{
		VecFx32 vec;
		EOA_MatrixGet( eoa, &vec );
		BLACT_MatrixSet( work->act, &vec );
	}
	
	BLACT_ScaleSet( work->act, &work->scale );
}

//--------------------------------------------------------------
///	�f�肱��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_ReflectSole =
{
	REF_WORK_SIZE,
	EoaReflectSole_Init,
	EoaReflectSole_Delete,
	EoaReflectSole_Move,
	EoaReflectSole_Draw,
};

