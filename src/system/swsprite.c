//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		swsprite.c
 *	@brief		�\�t�g�E�F�A�X�v���C�g�\���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "string.h"

#define __SESPRITE_H_GLOBAL
#include "include/system/swsprite.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	PLTT_16_SIZE	(32)		// 16�F�p���b�g�T�C�Y

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�L�����N�^�f�[�^
//
//=====================================
typedef struct SWSP_CHAR_tag{
	NNSGfdTexKey		vramKey;	// �g�pVram�̈�
	NNSG2dImageProxy	imgProxy;	// image�v���N�V
} SWSP_CHAR;

//-------------------------------------
//	
//	�p���b�g�f�[�^
//	
//=====================================
typedef struct SWSP_PLTT_tag{
	NNSGfdPlttKey			vramKey;	// �g�pVram�̈�
	NNSG2dImagePaletteProxy	imgProxy;	// image�v���N�V
} SWSP_PLTT;

//-------------------------------------
//	
//	�\�t�g�E�F�A�X�v���C�g�\���f�[�^
//	���P�ɂ܂Ƃ߂��I�u�W�F�N�g�f�[�^
//	
//=====================================
typedef struct SWSP_OBJ_tag{
	NNSG2dSVec2		matrix;					// �\���ʒu
	NNSG2dSVec2		center;					// ���S���W
    NNSG2dSVec2		size;					// �T�C�Y
	fx32			scale_x;				// ���g��l
	fx32			scale_y;				// ���g��l
	int				priority;				// �\���D�揇��
	int				rotZ;					// ��]�pZ
	BOOL			use;					// �g�p����
	BOOL			draw;					// �\�����邩
	NNSG2dImageAttr* tex_attr;				// �e�N�X�`���A�g���r���[�g
	u32				tex_addr;				// �e�N�X�`���A�h���X
	u32				pltt_addr;				// �p���b�g�A�h���X
	u32				pltt_offs;				// 16�F��
	BOOL			flipH;					// H�t���b�v
	BOOL			flipV;					// V�t���b�v
	GXRgb			diffcolor;				// �f�B�t���[�Y�J���[
	u8				alpha;					// �A���t�@
} SWSP_OBJ;

//-------------------------------------
//	
//	imageClip�p
//	�\�t�g�E�F�A�X�v���C�g�`��V�X�e��
//	�f�[�^�i�[�\����
//=====================================
typedef struct SWSP_SYS_tag{
	SWSP_OBJ*	obj_tbl;		// �I�u�W�F�e�[�u��
	int				obj_num;		// �I�u�W�F�e�[�u����
	SWSP_CHAR*	char_tbl;		// �L�����N�^�e�[�u��
	int				char_num;		// �L�����N�^�e�[�u����
	SWSP_PLTT*	pltt_tbl;		// �p���b�g�e�[�u��
	int				pltt_num;		// �p���b�g�e�[�u����

}SWSP_SYS;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void cleanSys( SWSP_SYS* data );
static void cleanObj( SWSP_OBJ* data );
static void cleanChar( SWSP_CHAR* data );
static void cleanPltt( SWSP_PLTT* data );

static void darwObj( SWSP_OBJ* data );

static SWSP_OBJ* makeObjData( int num, int heap );
static SWSP_CHAR* makeCharData( int num, int heap );
static SWSP_PLTT* makePlttData( int num, int heap );

static SWSP_OBJ* getCleanObj( SWSP_SYS* sys );
static SWSP_CHAR* getCleanChar( SWSP_SYS* sys );
static SWSP_PLTT* getCleanPltt( SWSP_SYS* sys );

static NNSGfdTexKey getCharVramKey( NNSG2dCharacterData* pChar );
static NNSGfdPlttKey getPlttVramKey( int pltt_num );
static void transCharData( NNSG2dCharacterData* pChar, NNSGfdTexKey vramKey, NNSG2dImageProxy* proxy );
static void transPlttData( NNSG2dPaletteData* pPltt, NNSGfdPlttKey vramKey, NNSG2dImagePaletteProxy* proxy );

// �X�v���C�g�f�[�^�ݒ�A�擾�֐�
static void setSpriteData( SWSP_OBJ_PTR obj, const SWSP_ADDDATA* add );

//-----------------------------------------------------------------------------
/**
*		�O���[�o���֐�����
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	imageClip�`��p�\�t�g�E�F�A�V�X�e��������
 *
 *	@param	data		�V�X�e���������f�[�^
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	SWSPRITE_PTR	�\�t�g�E�F�A�V�X�e���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_SYS_PTR SWSP_SysInit( const SWSP_SYSDATA* data )
{
	SWSP_SYS_PTR sys;
	int i;	// ���[�v�p

	sys = sys_AllocMemory( data->heap, sizeof(SWSP_SYS) );
	GF_ASSERT( sys );

	// �I�u�W�F�N�g�f�[�^�쐬
	sys->obj_tbl = makeObjData( data->obj_num, data->heap );
	sys->obj_num = data->obj_num;
	
	// �L�����N�^�f�[�^�쐬
	sys->char_tbl = makeCharData( data->char_num, data->heap );
	sys->char_num = data->char_num;
	
	// �p���b�g�f�[�^�쐬
	sys->pltt_tbl = makePlttData( data->pltt_num, data->heap );
	sys->pltt_num = data->pltt_num;

	return sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�V�X�e���j��
 *
 *	@param	data	�\�t�g�E�F�A�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SysDelete( SWSP_SYS_PTR data )
{
	GF_ASSERT(data);
	GF_ASSERT(data->obj_tbl);
	GF_ASSERT(data->char_tbl);
	GF_ASSERT(data->pltt_tbl);

	// �S�f�[�^�j��
	sys_FreeMemoryEz( data->obj_tbl );
	sys_FreeMemoryEz( data->char_tbl );
	sys_FreeMemoryEz( data->pltt_tbl );
	sys_FreeMemoryEz( data );
	data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�\������
 *
 *	@param		data �V�X�e�����̕\���I�u�W�F�N�g��\������
 *
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SysDraw( SWSP_SYS_PTR data )
{
	int i;		// ���[�v�p
	

	G3_PushMtx();
	
	
	for( i=0;i<data->obj_num;i++ ){
		if(data->obj_tbl[ i ].draw){
			darwObj( data->obj_tbl + i );
		}
	}

	G3_PopMtx(1);
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̍\���̃T�C�Y��Ԃ�
 *
 *	@param	none
 *
 *	@return	int	�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetCharDataSize( void )
{
	return sizeof( SWSP_CHAR );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�\���̂̃T�C�Y��Ԃ�
 *
 *	@param	none
 *
 *	@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetPlttDataSize( void )
{
	return sizeof( SWSP_PLTT );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�f�[�^�\���̂̃T�C�Y���擾����
 *
 *	@param	none
 *
 *	@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetSpriteDataSize( void )
{
	return sizeof( SWSP_OBJ );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_CHAR_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_CHAR_PTR SWSP_GetCharDataNo( SWSP_CHAR_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_PLTT_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_PLTT_PTR SWSP_GetPlttDataNo( SWSP_PLTT_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_OBJ_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_OBJ_PTR SWSP_GetSpriteDataNo( SWSP_OBJ_PTR obj, int no )
{
	return obj + no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�L�����N�^�f�[�^��ǂݍ���
 *
 *	@param	data	�ǂݍ��ރL�����N�^�f�[�^ 
 *
 *	@return	SWSP_CHAR_PTR	�ǂݍ��񂾃L�����N�^�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_CHAR_PTR SWSP_CharLoad( const SWSP_CHARDATA* data )
{
	SWSP_CHAR_PTR char_tbl;		// �f�[�^�i�[��

	// ��̃L�����N�^�f�[�^�e�[�u���擾
	char_tbl = getCleanChar( data->s_sys );
	GF_ASSERT( char_tbl );

	// 2Dmap���`�F�b�N
	GF_ASSERT( data->res_file->mapingType == GX_OBJVRAMMODE_CHAR_2D );
	
	// �L�����N�^�T�C�Y��vramKey���擾
	char_tbl->vramKey = getCharVramKey( data->res_file );	
	GF_ASSERT( char_tbl->vramKey );
	
	// vramkey�̃A�h���X�Ƀf�[�^�]��
	transCharData( data->res_file, char_tbl->vramKey, &char_tbl->imgProxy );

	return char_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�j��
 *
 *	@param	data	�L�����N�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_CharDelete( SWSP_CHAR_PTR data )
{
	// VramKey�̉��
	NNS_GfdFreeTexVram( data->vramKey );

	// �e�[�u��clean�A�b�v
	cleanChar( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�S�j��
 *
 *	@param	data		�L�����N�^�f�[�^��S���j������V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_CharDeleteAll( SWSP_SYS_PTR data )
{
	int i;		// ���[�v�p

	for(i=0;i<data->char_num;i++){
		if( data->char_tbl[ i ].vramKey ){
			SWSP_CharDelete( data->char_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�p���b�g�f�[�^��ǂݍ���
 *
 *	@param	data	�ǂݍ��ރp���b�g�f�[�^ 
 *
 *	@return	SWSP_PLTT_PTR	�ǂݍ��񂾃p���b�g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_PLTT_PTR SWSP_PlttLoad( const SWSP_PLTTDATA* data )
{
	SWSP_PLTT_PTR pltt_tbl;		// �p���b�g�f�[�^�i�[��

	// ��̃p���b�g�e�[�u���擾
	pltt_tbl = getCleanPltt( data->s_sys );
	GF_ASSERT( pltt_tbl );

	// VramKey�擾
	pltt_tbl->vramKey = getPlttVramKey( data->load_num );
	GF_ASSERT(pltt_tbl->vramKey);

	// �p���b�g�f�[�^�]��
	transPlttData( data->res_file, pltt_tbl->vramKey, &pltt_tbl->imgProxy );

	return pltt_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�p���b�g�f�[�^�j��
 *
 *	@param	data	�j������p���b�g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_PlttDelete( SWSP_PLTT_PTR data )
{
	// VramKey�̉��
	NNS_GfdFreePlttVram( data->vramKey );

	// �e�[�u��clean�A�b�v
	cleanPltt( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�S�j��
 *
 *	@param	data		�p���b�g�f�[�^��S�j������\�t�g�E�F�A�X�v���C�g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_PlttDeleteAll( SWSP_SYS_PTR data )
{
	int i;		// ���[�v�p

	for(i=0;i<data->pltt_num;i++){
		if( data->pltt_tbl[ i ].vramKey ){
			SWSP_PlttDelete( data->pltt_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���o�^
 *
 *	@param	add		�o�^�f�[�^
 *
 *	@return	SWSP_OBJ_PTR	�\�t�g�E�F�A�X�v���C�g�I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
SWSP_OBJ_PTR SWSP_Add( const SWSP_ADDDATA* add )
{
	SWSP_OBJ_PTR obj_tbl;	// �f�[�^�i�[��

	// �󂢂Ă���e�[�u�����擾
	obj_tbl = getCleanObj( add->s_sys );
	GF_ASSERT( obj_tbl );

	// �f�[�^�ݒ�
	// �ݒ肷��
	setSpriteData( obj_tbl, add );

	// �g�p���ɂ���
	obj_tbl->use	= TRUE;
	obj_tbl->draw	= TRUE;

	return obj_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���f�[�^�j��
 *
 *	@param	sp_obj �j������\�t�g�E�F�A�X�v���C�g�I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_Delete( SWSP_OBJ_PTR sp_obj )
{

	cleanObj( sp_obj );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���f�[�^�S�j��
 *
 *	@param	sys		�\���f�[�^�I�u�W�F��S�j������\�t�g�E�F�A�X�v���C�g�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_DeleteAll( SWSP_SYS_PTR sys )
{
	int i;		// ���[�v�p

	for(i=0;i<sys->obj_num;i++){
		if( sys->obj_tbl[ i ].use ){
			SWSP_Delete( sys->obj_tbl + i );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\��/��\���ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F�N�g
 *	@param	draw	�\��/�\��		(TRUE / FALSE)
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteDraw( SWSP_OBJ_PTR obj, BOOL draw )
{
	GF_ASSERT( obj );
	obj->draw = draw;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\��/��\�����擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F�N�g
 *
 *	@retval	TRUE	�\��
 *	@retval	FALSE	��\��
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SWSP_GetSpriteDraw( SWSP_OBJ_PTR obj )
{
	GF_ASSERT( obj );
	return obj->draw;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���W�ݒ�
 *
 *	@param	obj		�I�u�W�F	
 *	@param	x		���W��
 *	@param	y		���W��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePos( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->matrix.x = x;
	obj->matrix.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���W���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2 ���W(�����o s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpritePos( SWSP_OBJ_PTR obj )
{
	return obj->matrix;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���S���W�ݒ�
 *
 *	@param	obj		�I�u�W�F	
 *	@param	x		���W��
 *	@param	y		���W��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteCenterPos( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->center.x = x;
	obj->center.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���S���W���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2 ���W(�����o s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteCenterPos( SWSP_OBJ_PTR obj )
{
	return obj->center;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g��k���l��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		���g�k�l
 *	@param	y		���g�k�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteScale( SWSP_OBJ_PTR obj, fx32 x, fx32 y )
{
	obj->scale_x = x;
	obj->scale_y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g��k���l���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�����W�擾��
 *	@param	y		�����W�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_GetSpriteScale( SWSP_OBJ_PTR obj, fx32* x, fx32* y )
{
	*x = obj->scale_x;
	*y = obj->scale_y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�T�C�Y��
 *	@param	y		�T�C�Y��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteSize( SWSP_OBJ_PTR obj, int x, int y )
{
	obj->size.x = x;
	obj->size.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2	�X�v���C�g�T�C�Y�i�����o s16 x s16 y�j
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteSize( SWSP_OBJ_PTR obj )
{
	return obj->size;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�\���D�揇�ʂ�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	priority	�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePriority( SWSP_OBJ_PTR obj, int priority )
{
	obj->priority = priority;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\���D�揇�ʂ�ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	int		�\���D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
int SWSP_GetSpritePriority( SWSP_OBJ_PTR obj )
{
	return obj->priority;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃��l��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	alpha	���l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteAlpha( SWSP_OBJ_PTR obj, u8 alpha )
{
	obj->alpha = alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃��l���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
u8 SWSP_GetSpriteAlpha( SWSP_OBJ_PTR obj )
{
	return obj->alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̐F��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	color		�f�B�t���[�Y�J���[
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteDiffColor( SWSP_OBJ_PTR obj, GXRgb color )
{
	obj->diffcolor = color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̃f�B�t���[�Y�F���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *
 *	@retval	�J���[
 */
//-----------------------------------------------------------------------------
GXRgb SWSP_GetSpriteDiffColor( SWSP_OBJ_PTR obj )
{
	return obj->diffcolor;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃e�N�X�`���A�g���r���[�g��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	tex_attr	�e�N�X�`���A�g���r���[�g�|�C���^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteTexAttr( SWSP_OBJ_PTR obj, NNSG2dImageAttr* tex_attr )
{
	obj->tex_attr = tex_attr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃e�N�X�`���A�g���r���[�g���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dImageAttr*	�e�N�X�`���A�g���r���[�g
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageAttr* SWSP_GetSpriteTexAttr( SWSP_OBJ_PTR obj )
{
	return obj->tex_attr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���A�h���X�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	tex_addr	�e�N�X�`���A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteTexAddr( SWSP_OBJ_PTR obj, u32 tex_addr )
{
	obj->tex_addr = tex_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���A�h���X���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�e�N�X�`���A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpriteTexAddr( SWSP_OBJ_PTR obj )
{
	return obj->tex_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃p���b�g�A�h���X�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	pltt_addr	�p���b�g�A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePlttAddr( SWSP_OBJ_PTR obj, u32 pltt_addr )
{
	obj->pltt_addr = pltt_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃p���b�g�A�h���X�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�p���b�g�A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpritePlttAddr( SWSP_OBJ_PTR obj )
{
	return obj->pltt_addr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	pltt_offs	�p���b�g�I�t�Z�b�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpritePlttOffs( SWSP_OBJ_PTR obj, u32 pltt_offs )
{
	obj->pltt_offs = pltt_offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�I�t�Z�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
u32 SWSP_GetSpritePlttOffs( SWSP_OBJ_PTR obj )
{
	return obj->pltt_offs;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�t���b�v�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	flip_flg	�t���b�v�t���O
 *	@param	flip		�t���b�v�����邩	TRUE�@������@FALSE�@�����Ȃ�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg, BOOL flip )
{
	if(flip_flg == SWSP_FLIPH){
		obj->flipH = flip;
	}else{
		obj->flipV = flip;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̃t���b�v���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	flip_flg	HV�t���b�v�t���O
 *
 *	@return	BOOL	TRUE	�t���b�v����	FALSE
 *
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL SWSP_GetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg )
{
	if(flip_flg == SWSP_FLIPH){
		return obj->flipH;
	}
	
	return obj->flipV;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�pz��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	rota		�ݒ肷��p�x
 *
 *	@return
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRotZ( SWSP_OBJ_PTR obj, u16 rota )
{
	obj->rotZ = rota;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p�xZ���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *
 *	@return	u16		��]�p�x
 *
 *
 */
//-----------------------------------------------------------------------------
u16 SWSP_GetSpriteRotZ( SWSP_OBJ_PTR obj )
{
	return obj->rotZ;
}


#if 0

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�gcolor��ݒ�i�|���S��color�j
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	color	�|���S��color
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteColor( SWSP_OBJ_PTR obj, GXRgb color )
{
	obj->sprite.basicParams.color = color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�gcolor�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	GXRgb	color�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb SWSP_GetSpriteColor( SWSP_OBJ_PTR obj )
{
	return obj->sprite.basicParams.color;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g��UV�l��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	LR_flg		����@�E���t���O
 *	@param	u			U�l	�i���j
 *	@param	v			V�l	�i�c�j
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg, fx32 u, f32 v )
{
	if( LR_flg == SWSP_UVUL ){
		obj->sprite.uvUL.x = u;
		obj->sprite.uvUL.y = v;
	}else{
		obj->sprite.uvLR.x = u;
		obj->sprite.uvLR.y = v;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g��UV�l���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	LR_flg		����A�E���t���O
 *
 *	@return	NNSG2dFVec2 UV�l	�i�����o x=u  y=v�j
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dFVec2 SWSP_GetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg  )
{
	if( LR_flg == SWSP_UVUL ){
		return obj->sprite.uvUL;
	}
	
	return obj->sprite.uvLR;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�̒��S��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRotO( SWSP_OBJ_PTR obj, s16 x, s16 y )
{
	obj->sprite.rotO.x = x;
	obj->sprite.rotO.y = y;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̉�]���S���W�̎擾
 *
 *	@param	SWSP_OBJ_PTR obj	�X�v���C�g�I�u�W�F�N�g
 *
 *	@return	NNSG2dSVec2		��]���S���W	
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dSVec2 SWSP_GetSpriteRotO( SWSP_OBJ_PTR obj )
{
	return obj->sprite.rotO;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p��ݒ�
 *
 *	@param	obj
 *	@param	XYZ_flg
 *	@param	rota 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void SWSP_SetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg, u16 rota )
{
	switch(XYZ_flg){
	case SWSP_ROT_X:
		obj->sprite.rotX = rota;
		break;
	case SWSP_ROT_Y:
		obj->sprite.rotY = rota;
		break;
	case SWSP_ROT_Z:
		obj->sprite.basicParams.simpleParams.rotZ = rota;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p�x���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	XYZ_flg		�擾�����]�p�x�̃t���O
 *
 *	@return	u16		��]�p�x
 *
 *
 */
//-----------------------------------------------------------------------------
u16 SWSP_GetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg )
{
	switch(XYZ_flg){
	case SWSP_ROT_X:
		return obj->sprite.rotX;
		
	case SWSP_ROT_Y:
		return obj->sprite.rotY;
		
	case SWSP_ROT_Z:
		return obj->sprite.basicParams.simpleParams.rotZ;
	}

	return 0;
}
#endif

//-----------------------------------------------------------------------------
/**
*			�v���C�x�[�g�֐��S		private
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�V�X�e���f�[�^	�N���A
 *
 *	@param	data	�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanSys( SWSP_SYS* data )
{
	memset( data, 0, sizeof(SWSP_SYS) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F�N�g�f�[�^	�N���A
 *
 *	@param	data	�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanObj( SWSP_OBJ* data )
{
	memset( data, 0, sizeof(SWSP_OBJ) );
	data->alpha	= 31;
	data->diffcolor = GX_RGB( 31, 31, 31 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^	�N���A
 *
 *	@param	data �f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanChar( SWSP_CHAR* data )
{
	data->vramKey	= 0;
	NNS_G2dInitImageProxy( &data->imgProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^	�N���A
 *
 *	@param	data	�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void cleanPltt( SWSP_PLTT* data )
{
	data->vramKey	= 0;
	NNS_G2dInitImagePaletteProxy( &data->imgProxy );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	SWSP_OBJ�e�[�u���̍쐬
 *
 *	@param	num		�e�[�u����
 *	
 *	@return	SWSP_OBJ*	�e�[�u���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ* makeObjData( int num, int heap )
{
	SWSP_OBJ* data;
	int i;	// ���[�v�p
	
	// �I�u�W�F�N�g�f�[�^�쐬
	data = sys_AllocMemory( heap, sizeof(SWSP_OBJ) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanObj( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�e�[�u�����쐬
 *
 *	@param	num		�쐬��
 *	@param	heap	�g�p�q�[�v
 *
 *	@return	SWSP_CHAR*	�쐬�����e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR* makeCharData( int num, int heap )
{
	SWSP_CHAR* data;
	int i;	// ���[�v�p
	
	// �I�u�W�F�N�g�f�[�^�쐬
	data = sys_AllocMemory( heap, sizeof(SWSP_CHAR) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanChar( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�e�[�u�����쐬
 *
 *	@param	num		�쐬��
 *	@param	heap	�g�p�q�[�v
 *
 *	@return	SWSP_PLTT*	�쐬�����e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT* makePlttData( int num, int heap )
{
	SWSP_PLTT* data;
	int i;	// ���[�v�p
	
	// �I�u�W�F�N�g�f�[�^�쐬
	data = sys_AllocMemory( heap, sizeof(SWSP_PLTT) * num );
	GF_ASSERT( data );

	for(i=0;i<num;i++){
		cleanPltt( data + i );
	}

	return data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��̃I�u�W�F�f�[�^�擾
 *
 *	@param	sys		�擾��X�v���C�g�V�X�e���f�[�^
 *
 *	@return	SWSP_OBJ*	��̃I�u�W�F�N�g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ* getCleanObj( SWSP_SYS* sys )
{
	int i;		// ���[�v�p

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->obj_tbl[ i ].use == FALSE ){
			return ( sys->obj_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��̃L�����N�^�f�[�^�擾
 *
 *	@param	sys		�\�t�g�E�F�A�X�v���C�g�V�X�e���f�[�^
 *
 *	@return	SWSP_CHAR*	��̃L�����N�^�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_CHAR* getCleanChar( SWSP_SYS* sys )
{
	int i;		// ���[�v�p

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->char_tbl[ i ].vramKey == 0 ){
			return ( sys->char_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��̃p���b�g�f�[�^�擾
 *
 *	@param	sys		�\�t�g�E�F�A�X�v���C�g�V�X�e���f�[�^
 *
 *	@return	SWSP_PLTT*	��̃p���b�g
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_PLTT* getCleanPltt( SWSP_SYS* sys )
{
	int i;		// ���[�v�p

	for(i=0;i<sys->obj_num;i++ ){
		if( sys->pltt_tbl[ i ].vramKey == 0 ){
			return ( sys->pltt_tbl + i );
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^��]�����镪��VramKey���擾
 *
 *	@param	pChar	VramKey���擾����L�����N�^
 *
 *	@return	NNSGfdTexKey	�e�N�X�`���pVramKey
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSGfdTexKey getCharVramKey( NNSG2dCharacterData* pChar )
{
	return NNS_GfdAllocTexVram( pChar->szByte, FALSE, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�{������VramKey���擾
 *
 *	@param	pltt_num	�p���b�g�{���i�P�U�F�Ōv�Z�j
 *
 *	@return	NNSGfdPlttKey	�p���b�gVramKey
 *
 *
 */
//-----------------------------------------------------------------------------
static NNSGfdPlttKey getPlttVramKey( int pltt_num )
{ 
	return NNS_GfdAllocPlttVram( pltt_num * PLTT_16_SIZE, FALSE, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�]��
 *
 *	@param	pChar		�]������L�����N�^�f�[�^
 *	@param	vramKey		�]���恕�]���T�C�Y
 *	@param	proxy		�v���N�V
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void transCharData( NNSG2dCharacterData* pChar, NNSGfdTexKey vramKey, NNSG2dImageProxy* proxy )
{
	// �L�����N�^�f�[�^�]��
	NNS_G2dLoadImage2DMapping( 
			pChar,							// �]���L�����N�^�f�[�^
			NNS_GfdGetTexKeyAddr(vramKey),	// �]����
			NNS_G2D_VRAM_TYPE_3DMAIN,		// �]���^�C�v
			proxy );						// �]���f�[�^�i�[��
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�]��
 *
 *	@param	pPltt		�]���p���b�g�f�[�^
 *	@param	vramKey		�]���恕�]���T�C�Y
 *	@param	proxy		�v���N�V
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void transPlttData( NNSG2dPaletteData* pPltt, NNSGfdPlttKey vramKey, NNSG2dImagePaletteProxy* proxy )
{
	int tmp_size;		// ���T�C�Y�ۑ�
	
	// �p���b�g�]���f�[�^�T�C�Y��ύX
	tmp_size = pPltt->szByte;
	pPltt->szByte = NNS_GfdGetPlttKeySize( vramKey );
	
	// �p���b�g�f�[�^�]��
	NNS_G2dLoadPalette( 
			pPltt,
			NNS_GfdGetPlttKeyAddr( vramKey ),
			NNS_G2D_VRAM_TYPE_3DMAIN,
			proxy
			);

	// �p���b�g�T�C�Y��߂�
	pPltt->szByte = tmp_size;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�P�I�u�W�F�̕\��
 *
 *	@param	data	�I�u�W�F�f�[�^
 *	@param	z_offs	Z�I�t�Z�b�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void darwObj( SWSP_OBJ* data )
{
	NNSG2dSVec2 uv0, uv1;
	
	G3_PushMtx();

	G3_MaterialColorDiffAmb(data->diffcolor,        // diffuse
							GX_RGB(31, 31, 31),        // ambient
							TRUE                       // use diffuse as vtx color if TRUE
							);

	G3_MaterialColorSpecEmi(GX_RGB(16, 16, 16),        // specular
							GX_RGB(0, 0, 0),           // emission
							FALSE                      // use shininess table if TRUE
							);
	
	
	// �e�N�X�`���ݒ�
	G3_TexImageParam( 
			data->tex_attr->fmt,		// �e�N�X�`���t�H�[�}�b�g
            GX_TEXGEN_TEXCOORD,         // �e�N�X�`���R�[�h
            data->tex_attr->sizeS,      // �e�N�X�`���T�C�Y
            data->tex_attr->sizeT,      // �e�N�X�`���T�C�Y
            GX_TEXREPEAT_NONE,          // ���s�[�g�����邩
            GX_TEXFLIP_NONE,            // �t���b�v�����邩
            data->tex_attr->plttUse,    // color�p���b�g�O�𔲂��F�ɂ��邩
            data->tex_addr              // �e�N�X�`���A�h���X
            );

	// �p���b�g�t�H�[�}�b�g�Ȃ��...
	G3_TexPlttBase( (u32)(data->pltt_addr + (32 * data->pltt_offs)), data->tex_attr->fmt );                                
	
	// �|���S���A�g���r���[�g�ݒ�
	G3_PolygonAttr(GX_LIGHTMASK_NONE,           // disable lights
                   GX_POLYGONMODE_MODULATE,     // modulation mode
                   GX_CULL_NONE,                // cull back
                   0,							// polygon ID(0 - 63)
                   data->alpha,                 // alpha(0 - 31)
                   0                // OR of GXPolygonAttrMisc's value
                   );	
	
	// �t���b�v
	if(data->flipH){
		uv0.x = data->size.x;
		uv1.x = 0;
	}else{
		uv1.x = data->size.x;
		uv0.x = 0;
	}
	
	if(data->flipV){
		uv0.y = data->size.y;
		uv1.y = 0;
	}else{
		uv1.y = data->size.y;
		uv0.y = 0;
	}
	
	// ���S���W�ŉ�]�g��
	G3_Translate( 
			(data->matrix.x + data->center.x) * FX32_ONE,
			(data->matrix.y + data->center.y) * FX32_ONE,
			data->priority * FX32_ONE );
	// Z����]
    G3_RotZ( FX_SinIdx( data->rotZ ), FX_CosIdx( data->rotZ ) );
	// �g�k�l
	G3_Scale( data->scale_x, data->scale_y, FX32_ONE );

	// ���W�ݒ�i����j	�C���[�W�N���b�v�ȂǂŎg�p���Ă��邽�ߍ����ύX���邱�Ƃ͂ł��Ȃ�
	G3_Translate( 
			-data->center.x * FX32_ONE,
			-data->center.y * FX32_ONE,
			0 );

	
	// �`��
	NNS_G2dDrawSpriteFast( 
			0, 0, 0,
			data->size.x, data->size.y,
			uv0.x, uv0.y,
			uv1.x, uv1.y );

	G3_PopMtx(1);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�f�[�^��ݒ肷��
 *
 *	@param	obj			�I�u�W�F�N�g�f�[�^
 *	@param	add			�o�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setSpriteData( SWSP_OBJ* obj, const SWSP_ADDDATA* add )
{
	int i;
	int size_x, size_y;
	fx32 l_u, l_v;	// ����UV
	fx32 r_u, r_v;	// �E��UV
	
	// UV�l�ݒ�
	size_x = 8;
	for(i=0;i<add->p_char->imgProxy.attr.sizeS;i++){
		size_x *= 2;
	}//*/
	size_y = 8;
	for(i=0;i<add->p_char->imgProxy.attr.sizeT;i++){
		size_y *= 2;
	}//*/
	
	l_u = 0;
	l_v = 0;
	r_u = size_x << FX32_SHIFT;
	r_v = size_y << FX32_SHIFT;

	// ���W�ݒ�
	SWSP_SetSpritePos( obj, add->m_x, add->m_y );

	// ���S���W
	SWSP_SetSpriteCenterPos( obj, size_x / 2, size_y / 2 );

	// �g�k�l
	obj->scale_x = FX32_ONE;
	obj->scale_y = FX32_ONE;

	// �T�C�Y�ݒ�
	SWSP_SetSpriteSize( obj, size_x, size_y );

	//�@�D�揇�ʐݒ�
	SWSP_SetSpritePriority( obj, add->pri );

	// ���l�ݒ�
	SWSP_SetSpriteAlpha( obj, add->alpha );

	// �e�N�X�`���A�g���r���[�g�ݒ�
	SWSP_SetSpriteTexAttr( obj, &add->p_char->imgProxy.attr );

	// �e�N�X�`���A�h���X�ݒ�
	SWSP_SetSpriteTexAddr( obj, NNS_G2dGetImageLocation( &add->p_char->imgProxy, NNS_G2D_VRAM_TYPE_3DMAIN ) );

	// �p���b�g�A�h���X�ݒ�
	SWSP_SetSpritePlttAddr( obj, NNS_G2dGetImagePaletteLocation( &add->p_pltt->imgProxy, NNS_G2D_VRAM_TYPE_3DMAIN ) );

	// �p���b�g�I�t�Z�b�g�ݒ�
	SWSP_SetSpritePlttOffs( obj, add->pltt_offs );
	

	// �t���b�v�ݒ�
	SWSP_SetSpriteFlip( obj, SWSP_FLIPH, FALSE );
	SWSP_SetSpriteFlip( obj, SWSP_FLIPV, FALSE );

	SWSP_SetSpriteRotZ( obj, add->rota );
}

