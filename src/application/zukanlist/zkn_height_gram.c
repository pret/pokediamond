//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *	@file		zkn_height_gram.c
 *	@brief		�|�P���������@�d���A�N�Z�X
 *	@author		tomoya takahashi 
 *	@data		2006.02.02
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "src/application/zukanlist/zkn_data/zukan_data.naix"

#define __ZKN_HEIGHT_GRAM_H_GLOBAL
#include "include/application/zukanlist/zkn_height_gram.h"

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
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�����d�����
//=====================================
typedef struct _ZKN_HEIGHT_GRAM{
	int* p_height;
	int* p_gram;

	// �`��֌W
	short* p_height_y;
	short* p_height_y_poke;
	short* p_height_scale;
	short* p_height_scale_poke;
} ZKN_HEIGHT_GRAM;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static int* LoadHeight( int heap );
static int* LoadGram( int heap );
static void LoadHeightY_man( short** p_hero, short** p_poke, int heap );
static void LoadHeightY_girl( short** p_hero, short** p_poke, int heap );
static void LoadHeightScale_man( short** p_hero, short** p_poke, int heap );
static void LoadHeightScale_girl( short** p_hero, short** p_poke, int heap );

//----------------------------------------------------------------------------
/**
 *	@brief	�����d�����i�[�G���A�쐬
 *
 *	@param	heap	�g�p�q�[�v
 *
 *	@return	�G���A
 */
//-----------------------------------------------------------------------------
ZKN_HEIGHT_GRAM_PTR ZKN_HEIGHTGRAM_Alloc( int heap )
{
	ZKN_HEIGHT_GRAM_PTR p_heightgram;

	p_heightgram = sys_AllocMemory( heap, sizeof(ZKN_HEIGHT_GRAM) );
	memset( p_heightgram, 0, sizeof(ZKN_HEIGHT_GRAM) );

	return p_heightgram;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����d�����i�[�G���A�j��
 *
 *	@param	p_heightgram	�j��data
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Free( ZKN_HEIGHT_GRAM_PTR p_heightgram )
{
	GF_ASSERT( p_heightgram );

	sys_FreeMemoryEz( p_heightgram );
	p_heightgram = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����d�����ǂݍ���
 *
 *	@param	p_heightgram	�i�[�G���A
 *	@param	type			�f�[�^�^�C�v
 *	@param	heap			�q�[�v
 *
 *	@return	none
 *
 * type
 *		ZKN_HEIGHT_GRAM_TYPE_MAN,	// ��l���j
 *		ZKN_HEIGHT_GRAM_TYPE_GIRL,	// ��l����
 *	
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Load( ZKN_HEIGHT_GRAM_PTR p_heightgram, int type, int heap )
{
	GF_ASSERT( p_heightgram );

	// �ǂݍ��ݍς݂ł���B
	GF_ASSERT(p_heightgram->p_height == NULL);
	GF_ASSERT(p_heightgram->p_gram == NULL);

	p_heightgram->p_height = LoadHeight( heap );
	p_heightgram->p_gram = LoadGram( heap );

	// �\���p�����[�^
	if( type == ZKN_HEIGHT_GRAM_TYPE_MAN ){
		LoadHeightY_man( &p_heightgram->p_height_y, &p_heightgram->p_height_y_poke, heap );
		LoadHeightScale_man( &p_heightgram->p_height_scale, &p_heightgram->p_height_scale_poke, heap );
	}else{
		LoadHeightY_girl( &p_heightgram->p_height_y, &p_heightgram->p_height_y_poke, heap );
		LoadHeightScale_girl( &p_heightgram->p_height_scale, &p_heightgram->p_height_scale_poke, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����d�����j��
 *
 *	@param	p_heightgram	�j��data
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_HEIGHTGRAM_Release( ZKN_HEIGHT_GRAM_PTR p_heightgram )
{
	GF_ASSERT( p_heightgram->p_height );
	GF_ASSERT( p_heightgram->p_gram );
	
	sys_FreeMemoryEz( p_heightgram->p_height );
	sys_FreeMemoryEz( p_heightgram->p_gram );

	sys_FreeMemoryEz( p_heightgram->p_height_y );
	sys_FreeMemoryEz( p_heightgram->p_height_y_poke );
	sys_FreeMemoryEz( p_heightgram->p_height_scale );
	sys_FreeMemoryEz( p_heightgram->p_height_scale_poke );
	
	p_heightgram->p_height	= NULL;
	p_heightgram->p_gram	= NULL;
	p_heightgram->p_height_y = NULL;
	p_heightgram->p_height_y_poke = NULL;
	p_heightgram->p_height_scale = NULL;
	p_heightgram->p_height_scale_poke = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�������擾
 *
 *	@param	cp_heightgram		�����d�����
 *	@param	mons_no				�����X�^�[�i���o�[
 *
 *	@return	������10�{�����l
 */
//-----------------------------------------------------------------------------
int ZKN_HEIGHTGRAM_GetHeight( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height );
	return cp_heightgram->p_height[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�d�����擾
 *
 *	@param	cp_heightgram		�����d�����
 *	@param	mons_no				�����X�^�[�i���o�[
 *
 *	@return	�d����10�{�����l
 */
//-----------------------------------------------------------------------------
int ZKN_HEIGHTGRAM_GetGram( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_gram );
	return cp_heightgram->p_gram[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ׁ@��l���̕\���I�t�Z�b�g�ʒu
 *
 *	@param	cp_heightgram		�f�[�^���[�N
 *	@param	mons_no				�|�P�����i���o�[
 *
 *	@return	�I�t�Z�b�g�l
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightY_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_y );
	return cp_heightgram->p_height_y[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ׁ@�|�P�����̕\���I�t�Z�b�g�ʒu
 *
 *	@param	cp_heightgram	�f�[�^���[�N
 *	@param	mons_no			�����X�^�[�i���o�[ 
 *
 *	@return	�I�t�Z�b�g�l
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightY_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_y_poke );
	return cp_heightgram->p_height_y_poke[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ׁ@��l���g�k�l
 *
 *	@param	cp_heightgram	�f�[�^���[�N
 *	@param	mons_no			�����X�^�[�i���o�[
 *	
 *	@return	�g�k�l
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightScale_hero( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_scale );
	return cp_heightgram->p_height_scale[ mons_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ׁ@�|�P�����g�k�l
 *
 *	@param	cp_heightgram	�f�[�^���[�N
 *	@param	mons_no			�����X�^�[�i���o�[
 *	
 *	@return	�g�k�l
 */
//-----------------------------------------------------------------------------
short ZKN_HEIGHTGRAM_GetHeightScale_poke( CONST_ZKN_HEIGHT_GRAM_PTR cp_heightgram, int mons_no )
{
	GF_ASSERT( cp_heightgram );
	GF_ASSERT( cp_heightgram->p_height_scale_poke );
	return cp_heightgram->p_height_scale_poke[ mons_no ];
}







//----------------------------------------------------------------------------
/**
 *	@brief	�����f�[�^�ǂݍ���
 *
 *	@param	heap	�q�[�v
 *
 *	@return	�ǂݍ��݃f�[�^
 */
//-----------------------------------------------------------------------------
static int* LoadHeight( int heap )
{
	void* buff;

	buff = ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_dat, FALSE, heap, ALLOC_TOP );
	

	return (int*)buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�d���f�[�^�ǂݍ���
 *
 *	@param	heap	�q�[�v
 *
 *	@return	�ǂݍ��݃f�[�^
 */
//-----------------------------------------------------------------------------
static int* LoadGram( int heap )
{
	void* buff;

	buff = ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_gram_dat, FALSE, heap, ALLOC_TOP );

	return (int*)buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����\����Y���W�z��
 *
 *	@param	p_hero		��l��
 *	@param	p_poke		�|�P����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightY_man( short** p_hero, short** p_poke, int heap )
{

	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_man_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_man_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����\����Y���W�z��
 *
 *	@param	p_hero		��l��
 *	@param	p_poke		�|�P����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightY_girl( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_girl_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_y_girl_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����\�����g�k�l�z��
 *
 *	@param	p_hero		��l��
 *	@param	p_poke		�|�P����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightScale_man( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_man_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_man_poke_dat, FALSE, heap, ALLOC_TOP );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����\�����g�k�l�z��
 *
 *	@param	p_hero		��l��
 *	@param	p_poke		�|�P����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void LoadHeightScale_girl( short** p_hero, short** p_poke, int heap )
{
	*p_hero = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_girl_dat, FALSE, heap, ALLOC_TOP );
	*p_poke = (short*)ArcUtil_Load( ARC_ZUKAN_DATA, NARC_zukan_data_zkn_height_scale_girl_poke_dat, FALSE, heap, ALLOC_TOP );
}	

