//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_accessorie.c
 *	@brief		�A�N�Z�T���Ǘ��V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "include/application/imageClip/imc_drawsys.h"

#include "include/application/imageClip/imc_drawdata_define.h"
#define	__IMC_ACCESSORIE_H_GLOBAL
#include "include/application/imageClip/imc_accessorie.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// �e�O���t�B�b�N�T�C�Y�̉�ʊO�ɂ߂荞��ł悢�T�C�Y
#define IMC_ACCE_HIT_16_SIZE_X	(0)
#define IMC_ACCE_HIT_16_SIZE_Y	(0)
#define IMC_ACCE_HIT_32_SIZE_X	(10)
#define IMC_ACCE_HIT_32_SIZE_Y	(10)
#define IMC_ACCE_HIT_64_SIZE_X	(20)
#define IMC_ACCE_HIT_64_SIZE_Y	(20)

#define IMC_ACCE_SIZE_16	(16)
#define IMC_ACCE_SIZE_32	(32)
#define IMC_ACCE_SIZE_64	(64)


// �����蔻���`�̔��T�C�Y
#define IMC_ACCE_HIT_AREA_HALF	(4)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static IMC_ACCESSORIE_OBJ* cleanObjDataGet( IMC_ACCESSORIE_OBJ_TBL* objTbl );
static SWSP_OBJ_PTR SWSP_add( IMC_ACCE_ADD* data );

static void setHitTbl( IMC_ACCESSORIE_OBJ* obj, TP_HIT_TBL* tp_hit );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����쐬
 *
 *	@param	obj_num		�A�N�Z�T����
 *	@param	heap		�q�[�v��
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	�I�u�W�F�N�g�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_ACCESSORIE_OBJ_TBL* IMC_ACCE_ObjTblInit( int obj_num, int heap )
{
	IMC_ACCESSORIE_OBJ_TBL* objTbl;
	
	// �������m��
	objTbl = sys_AllocMemory( heap, sizeof(IMC_ACCESSORIE_OBJ_TBL) );

	// �A�N�Z�T���e�[�u���쐬
	objTbl->obj_tbl = sys_AllocMemory( heap, sizeof(IMC_ACCESSORIE_OBJ)*obj_num );
	memset( objTbl->obj_tbl, 0, sizeof(IMC_ACCESSORIE_OBJ)*obj_num );
	objTbl->obj_num = obj_num;

	return objTbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����쐬
 *
 *	@param	obj_num		�A�N�Z�T����
 *	@param	heap		�q�[�v��
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	�I�u�W�F�N�g�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjTblDelete( IMC_ACCESSORIE_OBJ_TBL* obj_tbl )
{
	sys_FreeMemoryEz( obj_tbl->obj_tbl );
	sys_FreeMemoryEz( obj_tbl );

	obj_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���쐬
 *
 *	@param	data	�I�u�W�F�N�g�o�^�f�[�^
 *
 *	@return	IMC_ACCESSORIE_OBJ*	�A�N�Z�T���I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAdd( IMC_ACCE_ADD* data )
{
	IMC_ACCESSORIE_OBJ* obj_data;
	
	// �󂢂Ă���e�[�u���擾
	obj_data = cleanObjDataGet( data->objTbl );
	GF_ASSERT( obj_data );
	
	// �A�N�Z�T���f�[�^�ݒ�
	obj_data->accessorie_no = data->accessorie_no;
	
	// �`��f�[�^�쐬
	obj_data->drawObj = SWSP_add( data );

	return obj_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�f�[�^�j��
 *
 *	@param	obj		�j������I�u�W�F�N�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjDelete( IMC_ACCESSORIE_OBJ* obj )
{
	// �`��f�[�^�̔j��
	SWSP_Delete( obj->drawObj );

	// �f�[�^clean
	memset( obj, 0, sizeof( IMC_ACCESSORIE_OBJ ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�N�g�e�[�u�����̃A�N�Z�T���j��
 *
 *	@param	obj_tbl		�I�u�W�F�N�g�e�[�u��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjDeleteAll( IMC_ACCESSORIE_OBJ_TBL* obj_tbl )
{
	int i;

	for(i=0; i<obj_tbl->obj_num; i++){
		if( obj_tbl->obj_tbl[ i ].drawObj != NULL ){
			IMC_ACCE_ObjDelete( obj_tbl->obj_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����s��
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_ACCE_ObjTpHit( IMC_ACCESSORIE_OBJ* obj )
{
	TP_HIT_TBL	tp_hit;
	
	// �����蔻��f�[�^�쐬
	setHitTbl( obj, &tp_hit );	
	
	return GF_TP_SingleHitCont( &tp_hit );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��
 *
 *	@param	obj			�I�u�W�F�N�g�f�[�^
 *	@param	offs_x		���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y		���ォ��̃I�t�Z�b�g�����W
 *	@param	drawData	�L�����N�^�f�[�^
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_ACCE_ObjTpHitEx( IMC_ACCESSORIE_OBJ* obj, int* offs_x, int* offs_y, NNSG2dCharacterData* drawData )
{
	BOOL check;		// �`�F�b�N�p
	int x, y;		// ���݂̍�����W
	int i, j;		// ���[�v�p

	// �܂������蔻��𕁒ʂɍs��
	check = IMC_ACCE_ObjTpHit( obj );
	if( check == FALSE ){
		return FALSE;
	}

	// ���W�擾
	IMC_ACCE_ObjGetMat( obj, &x, &y );

	// �I�t�Z�b�g�l���擾
	*offs_x = sys.tp_x - x;
	*offs_y = sys.tp_y - y;

	// ���̈ʒu�̃L�����N�^�f�[�^���`�F�b�N
	// �����F�łȂ������`�F�b�N
/*	// �J���[�i���o�[���O�o�Ȃ����TRUE��Ԃ�
	check = IMC_DRAW_CharCheck( drawData, *offs_x, *offs_y, 0 );
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}
//*/
	for( i = (*offs_y - IMC_ACCE_HIT_AREA_HALF); i < (*offs_y + IMC_ACCE_HIT_AREA_HALF); i++ ){
	
		if( i >= 0 ){
			
			for( j = (*offs_x - IMC_ACCE_HIT_AREA_HALF); j < (*offs_x + IMC_ACCE_HIT_AREA_HALF); j++ ){
				
				if( j >= 0 ){
					// �J���[�i���o�[���O�o�Ȃ����TRUE��Ԃ�
					check = IMC_DRAW_CharCheck( drawData, j, i, 0 );
					if(check == IMC_DRAW_CHAR_CHECK_FALSE){
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����s��
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *	@param	x		���肘���W
 *	@param	y		���肙���W
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_ACCE_ObjTpHitSelf( IMC_ACCESSORIE_OBJ* obj, int x, int y )
{
	TP_HIT_TBL	tp_hit;
	
	// �����蔻��f�[�^�쐬
	setHitTbl( obj, &tp_hit );	

	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W��ݒ�	�i�����ɃX�v���C�g���ړ��j
 *
 *	@param	obj	�A�N�Z�T���I�u�W�F
 *	@param	x	x���W
 *	@param	y	y���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjSetMat( IMC_ACCESSORIE_OBJ* obj, s16 x, s16 y )
{
	// �X�v���C�g�ɐݒ�
	SWSP_SetSpritePos( obj->drawObj, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W���擾
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g
 *	@param	x		�����W�擾��
 *	@param	y		�����W�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjGetMat( IMC_ACCESSORIE_OBJ* obj, int* x, int* y )
{
	NNSG2dSVec2 mat;
	mat = SWSP_GetSpritePos( obj->drawObj );
	*x = mat.x;	
	*y = mat.y;	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y���擾
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g
 *	@param	x		���T�C�Y�擾��
 *	@param	y		���T�C�Y�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjGetSize( IMC_ACCESSORIE_OBJ* obj, int* x, int* y )
{
	NNSG2dSVec2 size;
	size = SWSP_GetSpriteSize( obj->drawObj );
	*x = size.x;	
	*y = size.y;	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�̃A�N�Z�T���̕`��ON�@OFF�@�ݒ�
 *
 *	@param	obj		�A�N�Z�T���I�u�W�F�N�g�f�[�^
 *	@param	flag	ON�@OFF�@�t���O
 *			
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjListDrawSet( IMC_ACCESSORIE_OBJ* obj, BOOL flag )
{
	SWSP_SetSpriteDraw( obj->drawObj, flag );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�̕\���D�揇�ʂ�ݒ�
 *
 *	@param	obj			�A�N�Z�T���I�u�W�F
 *	@param	priority	�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjDrawPrioritySet( IMC_ACCESSORIE_OBJ* obj, int priority )
{
	SWSP_SetSpritePriority( obj->drawObj, priority );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�̕\���D�揇�ʂ��擾
 *
 *	@param	obj			�A�N�Z�T���I�u�W�F
 *
 *	@return	priority
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_ACCE_ObjDrawPriorityGet( IMC_ACCESSORIE_OBJ* obj )
{
	return SWSP_GetSpritePriority( obj->drawObj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�H������ŗǂ��T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F�N�g�f�[�^
 *	@param	ins_x	�H������ŗǂ��T�C�YX
 *	@param	ins_y	�H������ŗǂ��T�C�YY
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjInSizeGet( IMC_ACCESSORIE_OBJ* obj, int* ins_x, int* ins_y )
{
	int size_x, size_y;		// �T�C�Y�擾�p

	// �A�N�Z�T���I�u�W�F�N�g�̂Ƃ�
	IMC_ACCE_ObjGetSize( obj, &size_x, &size_y );
	
	// �O���t�B�b�N�T�C�Y����擾
	switch(size_x){
	case IMC_ACCE_SIZE_16:
		*ins_x = IMC_ACCE_HIT_16_SIZE_X;
		break;
	case IMC_ACCE_SIZE_32:
		*ins_x = IMC_ACCE_HIT_32_SIZE_X;
		break;
	case IMC_ACCE_SIZE_64:
		*ins_x = IMC_ACCE_HIT_64_SIZE_X;
		break;
	}

	switch(size_y){
	case IMC_ACCE_SIZE_16:
		*ins_y = IMC_ACCE_HIT_16_SIZE_Y;
		break;
	case IMC_ACCE_SIZE_32:
		*ins_y = IMC_ACCE_HIT_32_SIZE_Y;
		break;
	case IMC_ACCE_SIZE_64:
		*ins_y = IMC_ACCE_HIT_64_SIZE_Y;
		break;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g�k�l��ݒ肷��
 *
 *	@param	obj			�A�N�Z�T���I�u�W�F
 *	@param	scale_x		���g�k�l
 *	@param	scale_y		���g�k�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_ACCE_ObjScaleSet( IMC_ACCESSORIE_OBJ* obj, int scale_x, int scale_y )
{
	GF_ASSERT( obj );
	
	SWSP_SetSpriteScale( obj->drawObj, scale_x, scale_y );
}


//-----------------------------------------------------------------------------
/**
*		�v���C�x�[�g�֐��S
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��̃e�[�u�����擾
 *
 *	@param	objTbl	�I�u�W�F�N�g�e�[�u��
 *
 *	@return	IMC_ACCESSORIE_OBJ*	��̃e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_ACCESSORIE_OBJ* cleanObjDataGet( IMC_ACCESSORIE_OBJ_TBL* objTbl )
{
	int i;		// ���[�v�p

	for(i=0; i<objTbl->obj_num; i++){
		if( objTbl->obj_tbl[ i ].drawObj == NULL ){
			return objTbl->obj_tbl + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�̓o�^
 *
 *	@param	data	�o�^�f�[�^	
 *
 *	@return	SWSP_OBJ_PTR	�쐬�����X�v���C�g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ_PTR SWSP_add( IMC_ACCE_ADD* data )
{
	SWSP_ADDDATA add;


	add.s_sys = data->SWSPsys;
	add.p_char = data->SWSPchar;
	add.p_pltt = data->SWSPpltt;
	add.m_x		= data->m_x;
	add.m_y		= data->m_y;
	add.rota	= 0;
	add.alpha	= 31;
	add.pri		= 0;
	add.pltt_offs = data->pltt_offs;

	return SWSP_Add( &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�̓����蔻��f�[�^�쐬
 *
 *	@param	obj		���I�u�W�F�N�g
 *	@param	tp_hit	�^�b�`�p�l�������蔻��f�[�^
 *
 *	@return
 *
 *	���O�ɃX�v���C�g�쐬���s���Ă���K�v������܂��B
 *
 */
//-----------------------------------------------------------------------------
static void setHitTbl( IMC_ACCESSORIE_OBJ* obj, TP_HIT_TBL* tp_hit )
{
	NNSG2dSVec2	pos	= SWSP_GetSpritePos( obj->drawObj );
	NNSG2dSVec2 size = SWSP_GetSpriteSize( obj->drawObj );
	
	// �X�v���C�g�T�C�Y���瓖���蔻��G���A�쐬
	tp_hit->rect.top		= pos.y;
	tp_hit->rect.bottom		= pos.y + size.y;
	tp_hit->rect.left		= pos.x;
	tp_hit->rect.right		= pos.x + size.x;
}
