//==============================================================================
/**
 * @file	field_effect.h
 * @brief	�t�B�[���h�G�t�F�N�g
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_EFFECT_H_FILE
#define FIELD_EFFECT_H_FILE

//==============================================================================
/*
	�t�B�[���h�G�t�F�N�g�֘A�@�ȈՐ���
	
	���\�[�X�t�@�C����
	field_effect.h �t�B�[���h�G�t�F�N�g�w�b�_�[
	field_effect.c �t�B�[���h�G�t�F�N�g����
	field_effect_data.c�@�G�t�F�N�g�o�^�\�[�X�t�@�C��
	
	���ȉ��Afield_effect.h��inlcude�ς�
	field_effect_code.h �t�B�[���h�G�t�F�N�g�p�V���{����`
	field_effect_subproc.h�@�G�t�F�N�g�Q�ƃw�b�_�[�@�ꗗ
	
	���t�B�[���h�G�t�F�N�g�p�@�A�[�J�C�u�f�[�^�C���f�b�N�XID�t�@�C����
	src\data\mmodel\fldeff.naix
	��field_effect.h��inlcude�ς�
	
	���V�K�G�t�F�N�g�̒ǉ����@��
	�P�FFE_SUBPROC_INIT�^�̃G�t�F�N�g�������֐��AFE_SUBPROC_DELETE�^�̃G�t�F�N�g�폜�֐��쐬
	�Q�F�V�K�G�t�F�N�g�֐��Q�ƃw�b�_�[��field_effect_subproc.h��inlcude
	�R�Ffield_effect_code.h�@�ɐV�K�G�t�F�N�gID��ǉ�
	�S�Ffield_effect_data.c�@�ɐV�K�G�t�F�N�gID�Ƃ���Ɋ֘A�����������A�폜�֐���`
	�T�FFE_EffectRegist()���ŌĂяo���A����m�F
	�U�Ffield_effect_subproc.h field_effect_code.h field_effect_data.c��commit
	
	���t�B�[���h�G�t�F�N�g��p�A�[�J�C�u�f�[�^�̍X�V���@��
	�P�Fsrc\data\mmodel\fldeff_list�փA�[�J�C�u�Ώۃt�@�C�����`
	�Q�F��L�f�B���N�g����make���s�B�A�[�J�C�u���쐬�����
	�R�F����m�F
	�S�F�A�[�J�C�u�Ώۃt�@�C����fldeff_list��commit����
	��mmodel�f�B���N�g���ɂ�make���鎖�Ő��������R���o�[�g�f�[�^�t�@�C����commit�͋֎~
	���A�[�J�C�u�t�@�C��(*.narc,*.naix)��commit���֎~�B�A�[�J�C�u�t�@�C�������͌X�̊��ōs��
	
	���G�t�F�N�g�ǉ��A�폜�֘A�֐���
	FE_EffectRegist()
	FE_EffectRegistMore()
	FE_EffectDelete()
	
	���G�t�F�N�g�g�p���[�N�擾�֐���
	FE_EffectWorkGet()
	
	���t�B�[���h�G�t�F�N�g��p�q�[�v�̈�֘A�֐���
	FE_AllocMemory()
	FE_AllocClearMemory()
	FE_FreeMemory()
	
	���t�B�[���h�G�t�F�N�g��p�A�[�J�C�u�f�[�^�֘A�֐���
	FE_ArcDataLoad()
	FE_ArcDataLoadAlloc()
	FE_ArcDataSizeGet()
*/
//==============================================================================

#include "localres.h"					//LRES
#include "eoa.h"						//EOA

#include "field_common.h"				//FIELD COMMON
#include "fieldobj.h"					//FIELD_OBJ

#include "field_effect_code.h"			//�G�t�F�N�g�V���{����`
#include "..\data\mmodel\fldeff.naix"	//ARC_FLDEFF

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�r���{�[�h�@�풓�@�]��
//--------------------------------------------------------------
enum
{
	FE_BLACT_TEX_VRAM = 0,									///<�e�N�X�`��VRAM�풓
	FE_BLACT_TEX_TRANS,										///<�e�N�X�`���]��
};

//==============================================================================
//	typedef struct 
//==============================================================================
//--------------------------------------------------------------
///	FE_SYS�\���̖���`�@�t�B�[���h�G�t�F�N�g����Z�߂�
//--------------------------------------------------------------
typedef struct _TAG_FE_SYS FE_SYS;

//--------------------------------------------------------------
///	�G�t�F�N�g�������֐��^��`�B
/// �����FFE_SYS * �߂�l�F�֐��Ŏg�p���郏�[�N *
//--------------------------------------------------------------
typedef void * (*FE_SUBPROC_INIT)( FE_SYS * );

//--------------------------------------------------------------
///	�G�t�F�N�g�폜�֐��^��`�B
/// �����Fvoid * = FE_SUBPROC_INIT�̖߂�l
//--------------------------------------------------------------
typedef void (*FE_SUBPROC_DELETE)( void * );

//--------------------------------------------------------------
///	FE_SUBPROC_DATA�\���� �G�t�F�N�g�֐�ID�o�^�f�[�^
//--------------------------------------------------------------
typedef struct
{
	u32 id;								///<proc_init,proc_del���Ăяo���ׂ̎���ID
	FE_SUBPROC_INIT proc_init;			///<id���w�肵���ۂɌĂ΂��G�t�F�N�g�������֐�
	FE_SUBPROC_DELETE proc_del;			///<id���w�肵���ۂɌĂ΂��G�t�F�N�g�폜�֐�
}FE_SUBPROC_DATA;

#define FE_SUBPROC_DATA_SIZE (sizeof(FE_SUBPROC_DATA))

//==============================================================================
//	�O���Q��
//==============================================================================
extern FE_SYS * FE_Init( FIELDSYS_WORK *fsys, u32 reg_max, u32 heap_id, u32 worksize );
extern void FE_ParamInit_EOA( FE_SYS *fes, u32 eoa_max );
extern void FE_ParamInit_BlAct( FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size );
extern void FE_EffectRegist( FE_SYS *fes, u32 id );
extern void FE_EffectRegistMore( FE_SYS *fes, const u32 *id_tbl );
extern int FE_EffectRegistCheck( FE_SYS *fes, u32 id );
extern void FE_EffectDelete( FE_SYS *fes, u32 id );
extern void FE_Draw( FE_SYS *fes );
extern void FE_Delete( FE_SYS *fes );

extern void * FE_AllocMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type );
extern void * FE_AllocClearMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type, u32 clear );
extern void FE_FreeMemory( void *alloc );
extern void * FE_EffectWorkGet( FE_SYS *fes, u32 id );
extern FIELDSYS_WORK * FE_FieldSysWorkGet( const FE_SYS *fes );
extern FE_SYS * FE_FieldOBJ_FE_SYS_Get( CONST_FIELD_OBJ_PTR fldobj );

extern u32 FE_ArcDataSizeGet( FE_SYS *fes, u32 datid );
extern void FE_ArcDataLoad( FE_SYS *fes, u32 datid, void *buf );
extern void * FE_ArcDataLoadAlloc( FE_SYS *fes, u32 datid, ALLOCTYPE type );

extern EOA_PTR FE_EoaAddNpp( const FE_SYS *fes, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri );
extern void FE_EoaDelete( EOA_PTR eoa );

extern BLACT_WORK_PTR FE_BlActAdd( FE_SYS *fes, 
		const BLACT_HEADER *head, const VecFx32 *vec );
extern BLACT_WORK_PTR FE_BlActAddID( FE_SYS *fes, u32 id, const VecFx32 *vec );
extern BLACT_HEADER * FE_BlActHeaderManageAdd( FE_SYS *fes, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl );
extern BLACT_HEADER * FE_BlActHeaderManageAddResmID(
		FE_SYS *fes, u32 id, u32 mdl_id, u32 anm_id, u32 tex_id, int tex_flag,
		const BLACT_ANIME_TBL *anm_tbl );
extern BLACT_HEADER * FE_BlActHeaderManageGet( FE_SYS *fes, u32 id );
extern void FE_BlActHeaderManageFree( FE_SYS *fes, u32 id );

extern void FE_BlActResAdd_Mdl( FE_SYS *fes, u32 id, const void *data, u32 size );
extern void FE_BlActResAdd_MdlArc( FE_SYS *fes, u32 id, u32 datid );
extern void * FE_BlActResGet_Mdl( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Mdl( FE_SYS *fes, u32 id );
extern void FE_BlActResAdd_Anm( FE_SYS *fes, u32 id, const void *data, u32 size );
extern void FE_BlActResAdd_AnmArc( FE_SYS *fes, u32 id, u32 datid );
extern void * FE_BlActResGet_Anm( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Anm( FE_SYS *fes, u32 id );
extern void FE_BlActResAdd_Tex( FE_SYS *fes, u32 id, void *data, u32 texcut );
extern void FE_BlActResAdd_TexArc( FE_SYS *fes, u32 id, u32 datid, u32 texcut );
extern void * FE_BlActResGet_Tex( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Tex( FE_SYS *fes, u32 id );

extern void FE_simple3DModelInitOnly( FE_SYS *fes,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile );
extern void FE_simple3DModelInit( FE_SYS *fes, u32 dataid, ALLOCTYPE type,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile );
extern void FE_3DObjMdlLoad( FE_SYS *fes, FLD_3DOBJ_MDL *p_mdl, u32 dataid, ALLOCTYPE type );
extern void FE_3DObjAnmLoad(
		FE_SYS *fes,
		FLD_3DOBJ_ANM *p_anm,
		const FLD_3DOBJ_MDL *cp_mdl,
		NNSFndAllocator* pallocator,
		u32 dataid, ALLOCTYPE type );
extern void FE_InitAllocator( FE_SYS *fes, NNSFndAllocator *pAllocator );

//==============================================================================
//	field_effect_data.c
//==============================================================================
extern const FE_SUBPROC_DATA DATA_FE_SubProcDataTbl[FE_PROC_MAX+1];
extern const u32 DATA_FE_GroundProcRegistTbl[FE_PROC_MAX+1];
extern const u32 DATA_FE_UnderProcRegistTbl[FE_PROC_MAX+1];

//==============================================================================
//	field_effect.h�𗘗p�����֐���include
//==============================================================================
#include "field_effect_subproc.h"

#endif //FIELD_EFFECT_H_FILE
