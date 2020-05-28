//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hideneff.c
 *	@file		field_hideneff.h
 *	@brief		�t�B�[���h��`�Z�G�t�F�N�g
 *	@data		2006.06.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "field_3dobj.h"
#include "hiden_effect.naix"

#include "src/fielddata/eventdata/zone_d01r0102evc.h"

#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/snd_tool.h"

#include "system/arc_util.h"

#define __FIELD_HIDENEFF_H_GLOBAL
#include "field_hideneff.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------

#define FHE_TASK_PRI	( 1024 )	// �����^�X�N�D�揇��

//----------------------------------------------------------------------------
/**
 *	@brief	OBJID�̃I�u�W�F�N�g�̌����Ă�������ɐݒ�
 */
//-----------------------------------------------------------------------------
static void FHE_objDirGridMatSet( FIELD_OBJ_SYS_PTR fldobjsys, u32 objID, FLD_3DOBJ* p_obj )
{
	int dir;	// ����
	int grid_x, grid_z;
	VecFx32 pos;
	FIELD_OBJ_PTR p_fldobj;

	p_fldobj = FieldOBJSys_OBJIDSearch( fldobjsys, objID );

	// ��荇�������@�̈ʒu�ɏo��
	FieldOBJ_VecPosGet( p_fldobj, &pos );
	grid_x = FieldOBJ_NowPosGX_Get( p_fldobj );
	grid_z = FieldOBJ_NowPosGZ_Get( p_fldobj );
	dir = FieldOBJ_DirDispGet( p_fldobj );
	switch( dir ){
	case DIR_UP:
		grid_z--;
		break;
	case DIR_DOWN:
		grid_z++;
		break;
	case DIR_LEFT:
		grid_x --;
		break;
	case DIR_RIGHT:
		grid_x ++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, pos.y, GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���@�̌����Ă���ق��̈ʒu��ݒ�
 *
 *	@param	jiki	���@�|�C���^
 *	@param	p_obj	�`��I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void FHE_playerDirGridMatSet( const PLAYER_STATE_PTR jiki, FLD_3DOBJ* p_obj )
{
	int dir;	// ����
	int grid_x, grid_z;
	VecFx32 pos;

	// ��荇�������@�̈ʒu�ɏo��
	Player_VecPosGet( jiki, &pos );
	grid_x = Player_NowGPosXGet( jiki );
	grid_z = Player_NowGPosZGet( jiki );
	dir = Player_DirGet( jiki );
	switch( dir ){
	case DIR_UP:
		grid_z--;
		break;
	case DIR_DOWN:
		grid_z++;
		break;
	case DIR_LEFT:
		grid_x --;
		break;
	case DIR_RIGHT:
		grid_x ++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, pos.y, GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );

}


//----------------------------------------------------------------------------
/**
 *	@brief	���@�̂P�O�̍��W��ݒ肷��
 *
 *	@param	jiki	���@
 *	@param	p_obj	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void FHE_playerVecMatSet( const PLAYER_STATE_PTR jiki, FLD_3DOBJ* p_obj )
{
/*	int grid_x, grid_z, grid_y;

	grid_y = FieldOBJ_OldPosGY_Get(Player_FieldOBJGet(jiki));
	grid_x = Player_OldGPosXGet( jiki );
	grid_z = Player_OldGPosZGet( jiki );
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, 
			GRID_SIZE_FX32(grid_y)+GRID_HALF_FX32, 
			GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );//*/

	VecFx32 pos;

	// ��荇�������@�̈ʒu�ɏo��
	Player_VecPosGet( jiki, &pos );
	FLD_3DObjSetMatrix( p_obj, pos.x, pos.y, pos.z );
}


//-------------------------------------
// �R�������ʃ��[�N
//=====================================
#define FHE_COMMON_ANM_NUM	( 4 )
typedef struct {
	FLD_3DOBJ		obj;
	FLD_3DOBJ_MDL	mdl;
	FLD_3DOBJ_ANM	anm[FHE_COMMON_ANM_NUM];
	u32				anm_num;
} FHE_COMMON_OBJ;

//----------------------------------------------------------------------------
/**
 *	@brief	���ʃI�u�W�F������
 *
 *	@param	p_obj		�I�u�W�F�N�g
 *	@param	mdl_idx		���f��IDX
 *	@param	anm_idx		�A�j��IDX	+ �A�j�����܂ł̃A�j����ǂݍ���
 *	@param	anm_num		�A�j����
 *	@param	p_allocator	�A���P�[�^
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObjInit( FHE_COMMON_OBJ* p_obj, u32 mdl_idx, u32 anm_idx, int anm_num, NNSFndAllocator* p_allocator )
{
	int i;

	memset( p_obj, 0, sizeof(FHE_COMMON_OBJ) );

	// ���f���ǂݍ���
	FLD_3DObjMdlLoad( &p_obj->mdl, ARC_HIDEN_EFFECT, mdl_idx, HEAPID_FIELD );
	FLD_3DObjInit( &p_obj->obj, &p_obj->mdl );

	p_obj->anm_num = anm_num;

	// �A�j���ǂݍ���
	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmLoad( &p_obj->anm[i], &p_obj->mdl, ARC_HIDEN_EFFECT, anm_idx + i, HEAPID_FIELD, p_allocator );
		FLD_3DObjAddAnm( &p_obj->obj, &p_obj->anm[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ʃI�u�W�F�N�g�̔j��
 *	
 *	@param	p_obj		���ʃI�u�W�F�N�g
 *	@param	p_allocator	�A���P�[�^
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObjDelete( FHE_COMMON_OBJ* p_obj, NNSFndAllocator* p_allocator )
{
	int i;

	// ���f���j��
	FLD_3DObjMdlDelete( &p_obj->mdl );

	// �A�j���j��
	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmDelete( &p_obj->anm[i], p_allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�m�[���[�v�A�j��
 *
 *	@param	p_obj	�I�u�W�F
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL Fhe_CommonObj_NoLoopAnime( FHE_COMMON_OBJ* p_obj )
{
	int i;
	BOOL check;

	check = TRUE;
	for( i=0; i<p_obj->anm_num; i++ ){
		check &= FLD_3DObjAnmNoLoop( &p_obj->anm[i], FX32_ONE );
	}
	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�v�A�j��
 *
 *	@param	p_obj	�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObj_LoopAnime( FHE_COMMON_OBJ* p_obj )
{
	int i;

	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmLoop( &p_obj->anm[i], FX32_ONE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ʃI�u�W�F�`�揈��
 *
 *	@param	p_obj	���ʃI�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObj_Draw( FHE_COMMON_OBJ* p_obj )
{
	FLD_3DObjDraw( &p_obj->obj );
}



//-----------------------------------------------------------------------------
/**
 *					����������
*/
//-----------------------------------------------------------------------------
// �V�[�P���X
enum{
	FHE_IAIGIRI_SEQ_MOVE,
	FHE_IAIGIRI_SEQ_END,
};

// ����������A�j����
enum{
	FHE_IAIGRI_ANM_ICA,
	FHE_IAIGRI_ANM_IMA,
	FHE_IAIGRI_ANM_ITA,
	FHE_IAIGRI_ANM_NUM,
};
//-------------------------------------
//	����������
//=====================================
typedef struct {
	FHE_COMMON_OBJ obj;

	// �A���P�[�^
	NNSFndAllocator allocator;

	u32 seq;	// �V�[�P���X
} FLD_HIDENEFF_IAIGIRI;


//-----------------------------------------------------------------------------
/**
 *					���킭����	
*/
//-----------------------------------------------------------------------------

// �V�[�P���X
enum{
	FHE_IWAKUDAKI_SEQ_MOVE,
	FHE_IWAKUDAKI_SEQ_END,
};


// ���킭�����A�j����
enum{
	FHE_IWAKUDAKI_ANM_IMA,
	FHE_IWAKUDAKI_ANM_ICA,
	FHE_IWAKUDAKI_ANM_ITP,
	FHE_IWAKUDAKI_ANM_ITA,
	FHE_IWAKUDAKI_ANM_NUM,
};
//-------------------------------------
//	���킭����
//=====================================
typedef struct {
	FHE_COMMON_OBJ obj;

	// �A���P�[�^
	NNSFndAllocator allocator;

	u32 seq;	// �V�[�P���X
} FLD_HIDENEFF_IWAKUDAKI;


//-----------------------------------------------------------------------------
/**
 *					�����̂ڂ�	
*/
//-----------------------------------------------------------------------------
// ��o��V�[�P���X
enum{
	FHE_TAKINOBORI_SEQ_START,
	FHE_TAKINOBORI_SEQ_LOOP,
};

// �����̂ڂ胂�f����
enum{
	FHE_TAKINOBORI_OBJ_START,
	FHE_TAKINOBORI_OBJ_LOOP,
	FHE_TAKINOBORI_OBJ_NUM,
};

// �����̂ڂ�A�j����
enum{
	FHE_TAKINOBORI_ANM_ICA,
	FHE_TAKINOBORI_ANM_ITP,
	FHE_TAKINOBORI_ANM_NUM,
};
//-------------------------------------
//	�����̂ڂ�
//=====================================
typedef struct _FLD_HIDENEFF_TAKINOBORI{
	FHE_COMMON_OBJ obj[FHE_TAKINOBORI_OBJ_NUM];

	// �A���P�[�^
	NNSFndAllocator allocator;
	
	u32 seq;	// �V�[�P���X
} FLD_HIDENEFF_TAKINOBORI;



//-----------------------------------------------------------------------------
/**
 *					���b�N�N���C��	
*/
//-----------------------------------------------------------------------------

// �V�[�P���X
enum{
	FHE_ROCKCLIMB_SEQ_MOVE,
};

#define FHE_ROCKCLIMB_OBJ_NUM	( 16 )	// �\���I�u�W�F��

// ���b�N�N���C���A�j����
enum{
	FHE_ROCKCLIMB_ANM_IMA,
	FHE_ROCKCLIMB_ANM_ICA,
	FHE_ROCKCLIMB_ANM_ITP,
	FHE_ROCKCLIMB_ANM_ITA,
	FHE_ROCKCLIMB_ANM_NUM,
};

//-------------------------------------
//	���b�N�N���C���G�t�F�N�g���Ԃ���
//=====================================
typedef struct {
	FLD_3DOBJ		obj;
	FLD_3DOBJ_ANM	anm[FHE_ROCKCLIMB_ANM_NUM];
	u32 status;
}FLD_HIDENEFF_ROCKCLIMB_OBJ;
//-------------------------------------
//	���b�N�N���C��
//=====================================
typedef struct {
	FLD_3DOBJ_MDL	mdl;
	FLD_HIDENEFF_ROCKCLIMB_OBJ obj[ FHE_ROCKCLIMB_OBJ_NUM ];
	void* p_anmbuff[FHE_ROCKCLIMB_ANM_NUM];

	FIELDSYS_WORK* p_fsys;
	int wait;
	fx32 ofs_y;
	fx32 ofs_z;
	VecFx32 pos;

	// �A���P�[�^
	NNSFndAllocator allocator;

	u32 seq;	// �V�[�P���X
} FLD_HIDENEFF_ROCKCLIMB;
#define FHE_ROCKCLIMB_WAIT	( 4 )
#define FHE_ROCKCLIMB_EFF_OFS_Y	(GRID_FX32 * 2)
#define FHE_ROCKCLIMB_EFF_OFS_Z	(GRID_FX32)




//-----------------------------------------------------------------------------
/**
 *					����������	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���[�N����������
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IAIGIRI) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	// ���ʃI�u�W�F�N�g����������
	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iaigiri_nsbmd,
			NARC_hiden_effect_iaigiri_nsbca, FHE_IAIGRI_ANM_NUM, &p_fhe_w->allocator );

	// ���W�ݒ�
	FHE_playerDirGridMatSet( p_fsys->player, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IAIGIRI );

	// �V�[�P���X
	p_fhe_w->seq = FHE_IAIGIRI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j������
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;

	Fhe_CommonObjDelete( &p_fhe_w->obj, &p_fhe_w->allocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	int i;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_IAIGIRI_SEQ_MOVE:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj.obj, FALSE );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_IAIGIRI_SEQ_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	Fhe_CommonObj_Draw( &p_fhe_w->obj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����������@�G�t�F�N�g�J�n
 *
 *	@param	fsys	�t�B�[���h�f�[�^
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iaigiri_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IaigiriData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IAIGIRI),
		FHE_Iaigiri_Init,
		FHE_Iaigiri_Delete,
		FHE_Iaigiri_Main,
		FHE_Iaigiri_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IaigiriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����������@�G�t�F�N�g�j��
 *
 *	@param	p_demo	�f�����[�N
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Iaigiri_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����������@�I���`�F�b�N
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_HIDENEFF_Iaigiri_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_fhe_w->seq == FHE_IAIGIRI_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *					���킭����	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���[�N����������
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IWAKUDAKI) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iwakudaki_nsbmd,
			NARC_hiden_effect_iwakudaki_nsbca, FHE_IWAKUDAKI_ANM_NUM, &p_fhe_w->allocator );

	// ���W�ݒ�
	FHE_playerDirGridMatSet( p_fsys->player, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IWAKUDAKI );

	// �V�[�P���X
	p_fhe_w->seq = FHE_IWAKUDAKI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N����������
 *	�N���K�l�Y�B�p
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Kurogane_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IWAKUDAKI) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iwakudaki_nsbmd,
			NARC_hiden_effect_iwakudaki_nsbca, FHE_IWAKUDAKI_ANM_NUM, &p_fhe_w->allocator );

	// ���W�ݒ�
	FHE_objDirGridMatSet( p_fsys->fldobjsys, D01R0102_LEADER, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IWAKUDAKI );

	// �V�[�P���X
	p_fhe_w->seq = FHE_IWAKUDAKI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j������
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;

	Fhe_CommonObjDelete( &p_fhe_w->obj, &p_fhe_w->allocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_IWAKUDAKI_SEQ_MOVE:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj.obj, FALSE );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_IWAKUDAKI_SEQ_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	Fhe_CommonObj_Draw( &p_fhe_w->obj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���킭�����@�G�t�F�N�g�J�n
 *
 *	@param	fsys	�t�B�[���h�f�[�^
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IwakudakiData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IWAKUDAKI),
		FHE_Iwakudaki_Init,
		FHE_Iwakudaki_Delete,
		FHE_Iwakudaki_Main,
		FHE_Iwakudaki_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IwakudakiData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���킭�����@�G�t�F�N�g�J�n	�N���K�l�Y�B�p
 *
 *	@param	fsys	�t�B�[���h�f�[�^
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_KuroganeL_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IwakudakiData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IWAKUDAKI),
		FHE_Iwakudaki_Kurogane_Init,
		FHE_Iwakudaki_Delete,
		FHE_Iwakudaki_Main,
		FHE_Iwakudaki_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IwakudakiData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���킭�����@�G�t�F�N�g�j��
 *
 *	@param	p_demo	�f�����[�N
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Iwakudaki_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���킭�����@�I���`�F�b�N
 *
 *	@param	p_demo	�f�����[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FLD_HIDENEFF_Iwakudaki_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_fhe_w->seq == FHE_IWAKUDAKI_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *					�����̂ڂ�	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���[�N����������
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;
	const u8 mdl_idx[ FHE_TAKINOBORI_OBJ_NUM ] = {
		NARC_hiden_effect_ride_start_nsbmd,
		NARC_hiden_effect_ride_loop_nsbmd,
	};
	const u8 anm_idx[ FHE_TAKINOBORI_OBJ_NUM ] = {
		NARC_hiden_effect_ride_start_nsbca,
		NARC_hiden_effect_ride_loop_nsbca,
	};

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_TAKINOBORI) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObjInit( &p_fhe_w->obj[i], mdl_idx[i], anm_idx[i], FHE_TAKINOBORI_ANM_NUM, &p_fhe_w->allocator );

		// ���W�ݒ�
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[i].obj );
	}

	// ���[�v�A�j���͔�\��
	FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_LOOP ].obj, FALSE );

	Snd_SePlay( SE_TAKINOBORI );

	// �V�[�P���X
	p_fhe_w->seq = FHE_TAKINOBORI_SEQ_START;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j������
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;

	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObjDelete( &p_fhe_w->obj[i], &p_fhe_w->allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_TAKINOBORI_SEQ_START:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_START] );
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_START].obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_LOOP ].obj, TRUE );
			FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_START ].obj, FALSE );

			FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP].obj );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_TAKINOBORI_SEQ_LOOP:
		Fhe_CommonObj_LoopAnime( &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP] );
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP].obj );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;
	
	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObj_Draw( &p_fhe_w->obj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����̂ڂ�@�G�t�F�N�g�J�n
 *
 *	@param	fsys	�t�B�[���h�f�[�^
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Takinobori_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_TakinoboriData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_TAKINOBORI),
		FHE_Takinobori_Init,
		FHE_Takinobori_Delete,
		FHE_Takinobori_Main,
		FHE_Takinobori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_TakinoboriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����̂ڂ�@�G�t�F�N�g�j��
 *
 *	@param	p_demo	�f�����[�N
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Takinobori_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}






//-----------------------------------------------------------------------------
/**
 *					���b�NCLIMB
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	lockCLIMB�I�u�W�F�N�g�����J�n
 *
 *	@param	p_obj	�I�u�W�F
 *	@param	jiki	�^�[�Q�b�g�@���@�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjStart( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, const PLAYER_STATE_PTR jiki, fx32 ofs_y, fx32 ofs_z )
{
	VecFx32 pos;
	int i;

	GF_ASSERT( p_obj->status == 0 );
	
	// ��荇�������@�̂P�O�ʒu�ɏo��
	Player_VecPosGet( jiki, &pos );
	FLD_3DObjSetMatrix( &p_obj->obj, pos.x, pos.y + ofs_y, pos.z + ofs_z );
	p_obj->status = 1;

	// �A�j���I�u�W�F�̏�����
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmSet( &p_obj->anm[i], 0 );	
	}

	// �`��ON
	FLD_3DObjSetDraw( &p_obj->obj, TRUE );

	Snd_SePlay( SE_ROCKCLIMB );
}

//----------------------------------------------------------------------------
/**	
 *	@brief	���b�N�N���C���G�t�F�N�g�I�u�W�F�N�g���C��
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjMain( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj )
{
	int i;
	BOOL result;
	
	if( p_obj->status == 0 ){
		return ;
	}
	
	result = TRUE;
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		result &= FLD_3DObjAnmNoLoop( &p_obj->anm[i], FX32_ONE );
	}
	
	if( result == TRUE ){
		p_obj->status = 0;
		// �`��OFF
		FLD_3DObjSetDraw( &p_obj->obj, FALSE );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	���b�N�N���C���I�u�W�F�N�g�@������
 *
 *	@param	p_obj		�I�u�W�F�N�g���[�N
 *	@param	p_mdl		���f��
 *	@param	p_allocator	�A���P�[�^
 *	@param	pp_anmbuff	�A�j���o�b�t�@
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjInit( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl, NNSFndAllocator* p_allocator, void** pp_anmbuff )
{
	int i;

	memset( p_obj, 0, sizeof( FLD_HIDENEFF_ROCKCLIMB_OBJ ) );
	
	FLD_3DObjInit( &p_obj->obj, p_mdl );
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmLoad_Data( &p_obj->anm[i], p_mdl, pp_anmbuff[i],
				p_allocator );
		FLD_3DObjAddAnm( &p_obj->obj, &p_obj->anm[i] );
	}

	FLD_3DObjSetDraw( &p_obj->obj, FALSE );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�N�N���C���I�u�W�F�j��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjDelete( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, NNSFndAllocator* p_allocator )
{
	int i;

	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmDelete( &p_obj->anm[i], p_allocator );
	}
	memset( p_obj, 0, sizeof( FLD_HIDENEFF_ROCKCLIMB_OBJ ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�i��ł���ق���������o���G�t�F�N�g�̈ʒu��ݒ�
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_MoveOfsSet( FLD_HIDENEFF_ROCKCLIMB* p_fhe_w )
{
	VecFx32 pos;
#if 1
	Player_VecPosGet( p_fhe_w->p_fsys->player, &pos );
	// �i�ݐ悪�A����O
	if( ((pos.x - p_fhe_w->pos.x) == 0) &&
		(pos.y < p_fhe_w->pos.y) && 
		(pos.z > p_fhe_w->pos.z) ){

		p_fhe_w->ofs_y = 0;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z*2;
	}else{
		p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
	}
	p_fhe_w->pos = pos;
#endif

	
#if 0
	Player_VecPosGet( p_fhe_w->p_fsys->player, &pos );
	// �i�ݐ悪���E
	if( (pos.x - p_fhe_w->pos.x) != 0 ){
		p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;

	// �i�ݐ悪�A��
	}else if( pos.y > p_fhe_w->pos.y ){

		// ��O
		if( pos.z > p_fhe_w->pos.z ){
			p_fhe_w->ofs_y = -FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = -FHE_ROCKCLIMB_EFF_OFS_Z;

		// ��
		}else{
			p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
		}

	// �i�ݐ悪�A��
	}else{

		// ��O
		if( pos.z > p_fhe_w->pos.z ){
			p_fhe_w->ofs_y = 0;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z*2;

		// ��
		}else{
			p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
		}
		
	}
	p_fhe_w->pos = pos;
#endif
}



//----------------------------------------------------------------------------
/**
 *	@brief	�V�������b�N�N���C���I�u�W�F�����J�n
 *
 *	@param	p_fhe 
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_Set( FLD_HIDENEFF_ROCKCLIMB* p_fhe )
{
	int i;

	// �i��ł���ق���������o���G�t�F�N�g�̈ʒu��ݒ�
	FHE_RockClime_MoveOfsSet( p_fhe );
	
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		if( p_fhe->obj[i].status == 0 ){
			Fhe_RockClime_ObjStart( &p_fhe->obj[i], p_fhe->p_fsys->player, p_fhe->ofs_y, p_fhe->ofs_z );
			return ;
		}
	}
	// �I�u�W�F�N�g������Ȃ�
	GF_ASSERT(0);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�N�N���C���@�I�u�W�F���C��
 *
 *	@param	p_fhe	lockCLIMB�I�u�W�F�N�g
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_Main( FLD_HIDENEFF_ROCKCLIMB* p_fhe )
{
	int i;
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjMain( &p_fhe->obj[i] );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	���[�N����������
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_ROCKCLIMB) );

	// �A���P�[�^�쐬
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	// ���f���ǂݍ���
	FLD_3DObjMdlLoad( &p_fhe_w->mdl, ARC_HIDEN_EFFECT, NARC_hiden_effect_iwakudaki_nsbmd, HEAPID_FIELD );

	// �A�j���ǂݍ���
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		p_fhe_w->p_anmbuff[i] = ArcUtil_Load( ARC_HIDEN_EFFECT, NARC_hiden_effect_iwakudaki_nsbca + i, FALSE, HEAPID_FIELD, ALLOC_TOP );
	}
	
	// ���b�N�N���C���I�u�W�F�N�g����
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjInit( &p_fhe_w->obj[i], &p_fhe_w->mdl, &p_fhe_w->allocator, p_fhe_w->p_anmbuff );
	}

	p_fhe_w->p_fsys = p_fsys;
	Player_VecPosGet( p_fhe_w->p_fsys->player, &p_fhe_w->pos );

	// �V�[�P���X
	p_fhe_w->seq = FHE_ROCKCLIMB_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�j������
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjDelete( &p_fhe_w->obj[i], &p_fhe_w->allocator );
	}
	FLD_3DObjMdlDelete( &p_fhe_w->mdl );

	// �A�j���j��
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		sys_FreeMemoryEz( p_fhe_w->p_anmbuff[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��������
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;

	switch( p_fhe_w->seq ){
	case FHE_ROCKCLIMB_SEQ_MOVE:

		p_fhe_w->wait --;
		if( p_fhe_w->wait < 0 ){
			p_fhe_w->wait = FHE_ROCKCLIMB_WAIT;
			Fhe_RockClime_Set( p_fhe_w );
		}
		
		// �G�t�F�N�g�������C��
		Fhe_RockClime_Main( p_fhe_w );
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		FLD_3DObjDraw( &p_fhe_w->obj[i].obj );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	���b�N�N���C���J�n
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_RockClime_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_RockClimeData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_ROCKCLIMB),
		FHE_RockClime_Init,
		FHE_RockClime_Delete,
		FHE_RockClime_Main,
		FHE_RockClime_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_RockClimeData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�N�N���C���I��
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_RockClime_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}
