//******************************************************************************
/**
 * 
 * @file	fldeff_gyoe.c
 * @brief	�t�B�[���hOBJ���傦�[
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_gyoe.h"

#include "..\system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
#define GYOE_FLDOBJ_Y_OFFSET ((FX32_ONE*32))				///<�t�B�[���hOBJ�����Y�I�t�Z�b�g
#define GYOE_FLDOBJ_Z_OFFSET ((FX32_ONE*1))					///<�t�B�[���hOBJ�����Z�I�t�Z�b�g
#define GYOE_FLDOBJ_Y_MOVE_START ((FX32_ONE*6))				///<�M���G�[����

#define GYOE_END_FRAME (30)									///<�M���G�[�I���t���[��	

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_GYOE�^
//--------------------------------------------------------------
typedef struct _TAG_FE_GYOE * FE_GYOE_PTR;

//--------------------------------------------------------------
///	FE_GYOE�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_GYOE
{
	int add_count_gyoe;
	int add_count_saisen;
	int draw_init_gyoe;
	int draw_init_saisen;
	FE_SYS *fes;
}FE_GYOE;

#define FE_GYOE_SIZE (sizeof(FE_GYOE)) ///<FE_GYOE�T�C�Y

//--------------------------------------------------------------
///	GYOE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	GYOE_TYPE type;								///<GYOE_TYPE
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_GYOE_PTR gyoe;							///<FE_GYOE_PTR
	FIELD_OBJ_PTR fldobj;						///<���傦�[�̑Ώ�FIELD_OBJ_PTR
}GYOE_ADD_H;

#define GYOE_ADD_H_SIZE (sizeof(GYOE_ADD_H)) ///<GYOE_ADD_H�T�C�Y

//--------------------------------------------------------------
///	GYOE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<����ԍ�
	int frame;									///<�t���[��
	int obj_id;									///<���傦�[�Ώ�OBJID
	int zone_id;								///<���傦�[�Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW
	int end_sw;									///<�I��SW
	VecFx32 offset;								///<�I�t�Z�b�g
	VecFx32 move;								///<�ړ���
	GYOE_ADD_H head;							///<�ǉ�����GYOE_ADD_H
	BLACT_WORK_PTR act;							///<�r���{�[�h�A�N�^�[
}GYOE_WORK;

#define GYOE_WORK_SIZE (sizeof(GYOE_WORK))	///<GYOE_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Gyoe_AddCountUp( FE_GYOE_PTR gyoe );
static void Gyoe_AddCountDown( FE_GYOE_PTR gyoe );
static void Saisen_AddCountUp( FE_GYOE_PTR gyoe );
static void Saisen_AddCountDown( FE_GYOE_PTR gyoe );
static void GyoeType_AddCountUp( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static void GyoeType_AddCountDown( FE_GYOE_PTR gyoe, GYOE_TYPE type );

static void Gyoe_GraphicInit( FE_GYOE_PTR gyoe );
static void Saisen_GraphicInit( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicDelete( FE_GYOE_PTR gyoe );
static void Saisen_GraphicDelete( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicCheckInit( FE_GYOE_PTR gyoe );
static void Saisen_GraphicCheckInit( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicCheckDelete( FE_GYOE_PTR gyoe );
static void Saisen_GraphicCheckDelete( FE_GYOE_PTR gyoe );
static void GyoeType_GraphicInit( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static void GyoeType_GraphicDelete( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static BLACT_WORK_PTR GyoeType_BlActAdd( FE_SYS *fes, GYOE_TYPE type, VecFx32 *vec );

static const EOA_H_NPP DATA_EoaH_Gyoe;
static const EOA_H_NPP DATA_EoaH_FldOBJGyoe;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_Gyoe[];

//==============================================================================
//	���傦�[�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���傦�[������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_GYOE_PTR	FE_GYOE_PTR
 */
//--------------------------------------------------------------
void * FE_Gyoe_Init( FE_SYS *fes )
{
	FE_GYOE_PTR gyoe;
	
	gyoe = FE_AllocClearMemory( fes, FE_GYOE_SIZE, ALLOC_FR, 0 );
	gyoe->fes = fes;
	
	return( gyoe );
}

//--------------------------------------------------------------
/**
 * ���傦�[�폜
 * @param	gyoe		FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Gyoe_Delete( void *work )
{
	FE_GYOE_PTR gyoe = work;
	Gyoe_GraphicDelete( gyoe );
	FE_FreeMemory( gyoe );
}

//==============================================================================
//	���傦�[	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �M���G�[���J�E���g
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_AddCountUp( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_gyoe++;
}

//--------------------------------------------------------------
/**
 * �M���G�[���f�N�������g
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_AddCountDown( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_gyoe--;
	
	GF_ASSERT( gyoe->add_count_gyoe >= 0 &&
		"Gyoe_AddCountDown()�@�M���G�[�̒ǉ��ƍ폜�̉񐔂�����Ȃ�" );
}

//--------------------------------------------------------------
/**
 * �Đ킬�傦�[���J�E���g
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_AddCountUp( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_saisen++;
}

//--------------------------------------------------------------
/**
 * �Đ킬�傦�[���f�N�������g
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_AddCountDown( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_saisen--;
	
	GF_ASSERT( gyoe->add_count_saisen >= 0 &&
		"Gyoe_AddCountDown()�@�Đ�M���G�[�̒ǉ��ƍ폜�̉񐔂�����Ȃ�" );
}

//--------------------------------------------------------------
/**
 * �M���G�[�^�C�v�@�J�E���g 
 * @param	gyoe	FE_GYOE_TYPE
 * @param	type	GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_AddCountUp( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_AddCountUp( gyoe );
	}else{
		Saisen_AddCountUp( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * �M���G�[�^�C�v�@�f�N�������g
 * @param	gyoe	FE_GYOE_TYPE
 * @param	type	GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_AddCountDown( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_AddCountDown( gyoe );
	}else{
		Saisen_AddCountDown( gyoe );
	}
}

//==============================================================================
//	���傦�[�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���傦�[ �O���t�B�b�N������
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_gyoe == FALSE ){
		gyoe->draw_init_gyoe = TRUE;
		FE_BlActResAdd_MdlArc( gyoe->fes, FE_RESID_MDL_GYOE, NARC_fldeff_sisen_ef_nsbmd );
		FE_BlActResAdd_AnmArc( gyoe->fes, FE_RESID_ANM_GYOE, NARC_fldeff_kusaeff_itpcv_dat );
		FE_BlActResAdd_TexArc( gyoe->fes,
			FE_RESID_TEX_GYOE, NARC_fldeff_sisen_ef_nsbtx, TEXRESM_TEX_CUT_TRUE );
		
		FE_BlActHeaderManageAddResmID( gyoe->fes, FE_BLACT_H_ID_GYOE,
			FE_RESID_MDL_GYOE, FE_RESID_ANM_GYOE,
			FE_RESID_TEX_GYOE, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Gyoe );
	}
}

//--------------------------------------------------------------
/**
 * �Đ�M���G�[ �O���t�B�b�N������
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_saisen == FALSE ){
		gyoe->draw_init_saisen = TRUE;
		FE_BlActResAdd_MdlArc( gyoe->fes,
			FE_RESID_MDL_GYOE_SAISEN, NARC_fldeff_saisen_ef_nsbmd );
		FE_BlActResAdd_AnmArc( gyoe->fes,
			FE_RESID_ANM_GYOE_SAISEN, NARC_fldeff_kusaeff_itpcv_dat );
		FE_BlActResAdd_TexArc( gyoe->fes,
			FE_RESID_TEX_GYOE_SAISEN, NARC_fldeff_saisen_ef_nsbtx, TEXRESM_TEX_CUT_TRUE );
		
		FE_BlActHeaderManageAddResmID( gyoe->fes, FE_BLACT_H_ID_GYOE_SAISEN,
			FE_RESID_MDL_GYOE_SAISEN, FE_RESID_ANM_GYOE_SAISEN,
			FE_RESID_TEX_GYOE_SAISEN, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ���傦�[ �O���t�B�b�N�폜
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_gyoe == TRUE ){
		gyoe->draw_init_gyoe = FALSE;
		
		FE_BlActResDelete_Mdl( gyoe->fes, FE_RESID_MDL_GYOE );
		FE_BlActResDelete_Anm( gyoe->fes, FE_RESID_ANM_GYOE );
		FE_BlActResDelete_Tex( gyoe->fes, FE_RESID_TEX_GYOE );
		FE_BlActHeaderManageFree( gyoe->fes, FE_BLACT_H_ID_GYOE );
	}
}

//--------------------------------------------------------------
/**
 * �Đ�M���G�[ �O���t�B�b�N�폜
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_saisen == TRUE ){
		gyoe->draw_init_saisen = FALSE;
		
		FE_BlActResDelete_Mdl( gyoe->fes, FE_RESID_MDL_GYOE_SAISEN );
		FE_BlActResDelete_Anm( gyoe->fes, FE_RESID_ANM_GYOE_SAISEN );
		FE_BlActResDelete_Tex( gyoe->fes, FE_RESID_TEX_GYOE_SAISEN );
		FE_BlActHeaderManageFree( gyoe->fes, FE_BLACT_H_ID_GYOE_SAISEN );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N������
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicCheckInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_gyoe == 0 ){
		Gyoe_GraphicInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N�������@�Đ�M���G�[
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicCheckInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_saisen == 0 ){
		Saisen_GraphicInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N�폜
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicCheckDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_gyoe == 0 ){
		Gyoe_GraphicDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N�폜�@�Đ�M���G�[
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicCheckDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_saisen == 0 ){
		Saisen_GraphicDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * �O���t�B�b�N�������@���
 * @param	FE_GYOE_PTR gyoe
 * @param	type GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_GraphicInit( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_GraphicCheckInit( gyoe );
	}else{
		Saisen_GraphicCheckInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * �O���t�B�b�N�폜�@���
 * @param	FE_GYOE_PTR gyoe
 * @param	type GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_GraphicDelete( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_GraphicCheckDelete( gyoe );
	}else{
		Saisen_GraphicCheckDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * �M���G�[�@�r���{�[�h�ǉ�
 * @param	fes			FE_SYS_PTR
 * @param	type		GYOE_TYPE
 * @param	vec			���W
 * @retval	BLACT_WORK_PTR	BLACT_WORK_PTR
 */
//--------------------------------------------------------------
static BLACT_WORK_PTR GyoeType_BlActAdd( FE_SYS *fes, GYOE_TYPE type, VecFx32 *vec )
{
	int id[2] = { FE_BLACT_H_ID_GYOE, FE_BLACT_H_ID_GYOE_SAISEN };
	BLACT_WORK_PTR act = FE_BlActAddID( fes, id[type], vec );
	return( act );
}

//==============================================================================
//	���傦�[�@EOA�@�t�B�[���hOBJ�p
//==============================================================================
//--------------------------------------------------------------
/**
 * ���傦�[�ǉ�
 * @param	fes			FE_SYS *
 * @param	mtx			�\���ʒu
 * @param	se_play		TRUE=SE�Đ�
 * @retval	EOA_PTR		�ǉ�EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Gyoe_Add( FE_SYS *fes, const VecFx32 *mtx, int se_play )
{
	int pri;
	GYOE_ADD_H head;
	EOA_PTR eoa;
	
	head.type = GYOE_GYOE;
	head.fes = fes;
	head.gyoe = FE_EffectWorkGet( fes, FE_FLD_GYOE );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Gyoe, mtx, se_play, &head, 0xff );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * ���傦�[�I���`�F�b�N
 * @param	eoa		�M���G�[EOA
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
int FE_Gyoe_EndCheck( EOA_PTR eoa )
{
	GYOE_WORK *work;
	
	work = EOA_LocalWorkGet( eoa );
	return( work->end_sw );
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaGyoe_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	const GYOE_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->move.y = GYOE_FLDOBJ_Y_MOVE_START;
	
	GyoeType_GraphicInit( work->head.gyoe, work->head.type );			//�O���t�B�b�N������
	
	EOA_MatrixGet( eoa, &vec );
	work->act = GyoeType_BlActAdd( work->head.fes, work->head.type, &vec );
	GyoeType_AddCountUp( work->head.gyoe, work->head.type );			//�J�E���g�A�b�v
	
	if( EOA_AddParamGet(eoa) == TRUE ){
		Snd_SePlay( SE_MARK_GYOE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work = wk;
	
	EOA_MatrixGet( eoa, &vec );
	
	switch( work->seq_no ){
	case 0:
		work->offset.y += work->move.y;
		
		if( work->offset.y ){
			work->move.y -= FX32_ONE * 2;
		}else{
			work->move.y = 0;
			work->seq_no++;
		}
		
		break;
	case 1:		
		work->frame++;
		
		if( work->frame >= GYOE_END_FRAME ){
			work->seq_no++;
			work->frame = 0;
			work->end_sw = TRUE;
		}
		
		break;
	case 2:
		break;
	}
	
	EOA_MatrixSet( eoa, &vec );
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Delete( EOA_PTR eoa, void *wk )
{
	GYOE_WORK *work;
	
	work = wk;
	
	BLACT_Delete( work->act );									//�A�N�^�[�폜
	GyoeType_AddCountDown( work->head.gyoe, work->head.type );	//�J�E���g�_�E��
	GyoeType_GraphicDelete( work->head.gyoe, work->head.type );	//�O���t�B�b�N�폜
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	
	vec.x += work->offset.x;
	vec.y += work->offset.y;
	vec.z += work->offset.z;
	
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	���傦�[�@EOA�@�t�B�[���hOBJ�p
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p���傦�[�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	se_play		TRUE=SE�Đ�
 * @retval	EOA_PTR		�ǉ�EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJGyoe_Add( FIELD_OBJ_PTR fldobj, GYOE_TYPE type, int se_play )
{
	int pri;
	GYOE_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.type = type;
	head.fes = fes;
	head.gyoe = FE_EffectWorkGet( fes, FE_FLD_GYOE );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBStandardPriorityGet( fldobj ) + 1;	//�t�B�[���hOBJ�������������
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_FldOBJGyoe, &mtx, se_play, &head, pri );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@�������@�t�B�[���hOBJ�p
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaGyoeFldOBJ_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	const GYOE_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->move.y = GYOE_FLDOBJ_Y_MOVE_START;
		
	GyoeType_GraphicInit( work->head.gyoe, work->head.type );	//�O���t�B�b�N������
	
	EOA_MatrixGet( eoa, &vec );
	work->act = GyoeType_BlActAdd( work->head.fes, work->head.type, &vec );
	
	GyoeType_AddCountUp( work->head.gyoe, work->head.type );	//�J�E���g�A�b�v
	
	if( EOA_AddParamGet(eoa) == TRUE ){
		Snd_SePlay( SE_MARK_GYOE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���傦�[�@����@�t�B�[���hOBJ�p
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoeFldOBJ_Move( EOA_PTR eoa, void *wk )
{
	GYOE_WORK *work;
	FIELD_OBJ_PTR fldobj;
	VecFx32 vec;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	GF_ASSERT( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) != FALSE &&
		"�M���G�[���쒆�ɑΏۂ̃t�B�[���hOBJ���폜����܂���" );
	
	FieldOBJ_DrawVecPosTotalGet( fldobj, &vec );
	vec.y += GYOE_FLDOBJ_Y_OFFSET;
	vec.z += GYOE_FLDOBJ_Z_OFFSET;
	
	switch( work->seq_no ){
	case 0:
		work->offset.y += work->move.y;
		
		if( work->offset.y ){
			work->move.y -= FX32_ONE * 2;
		}else{
			work->move.y = 0;
			work->seq_no++;
		}
		
		break;
	case 1:		
		work->frame++;
		
		if( work->frame >= GYOE_END_FRAME ){
			work->seq_no++;
			work->frame = 0;
			work->end_sw = TRUE;
		}
		
		break;
	case 2:
		break;
	}
	
	EOA_MatrixSet( eoa, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	���傦�[EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Gyoe =
{
	GYOE_WORK_SIZE,
	EoaGyoe_Init,
	EoaGyoe_Delete,
	EoaGyoe_Move,
	EoaGyoe_Draw,
};

//--------------------------------------------------------------
///	���傦�[EOA_H�@�t�B�[���hOBJ�p
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_FldOBJGyoe =
{
	GYOE_WORK_SIZE,
	EoaGyoeFldOBJ_Init,
	EoaGyoe_Delete,
	EoaGyoeFldOBJ_Move,
	EoaGyoe_Draw,
};

//--------------------------------------------------------------
///	�M���G�[�A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_Gyoe[] =
{
	{ 0, 1, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
