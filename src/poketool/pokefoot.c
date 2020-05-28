//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		pokefoot.c
 *	@brief		�|�P�������ՃO���t�B�b�N�f�[�^�擾�֐�
 *	@author		tomoya takahashi
 *	@data		2006.01.31
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "include/system/arc_util.h"
#include "include/system/arc_tool.dat"
#include "include/poketool/monsno.h"

#define	__POKEFOOT_H_GLOBAL
#include "include/poketool/pokefoot.h"

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
#define POKEFOOT_ARC_PLTT		( 0 )		// �p���b�g�C���f�b�N�X
#define POKEFOOT_ARC_CELL		( 2 )		// �Z���C���f�b�N�X
#define POKEFOOT_ARC_CELLANM	( 1 )		// �Z���A�j���C���f�b�N�X
#define POKEFOOT_ARC_CHAR_DMMY	( 3 )		// poke_foot_000
#define POKEFOOT_ARC_CHAR_START	( 4	)		// �L�����N�^�J�n�C���f�b�N�X

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
//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[���瑫�ՃL�����N�^�f�[�^�擾
 *
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	heap		�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^
 */
//-----------------------------------------------------------------------------
void* PokeFootCharPtrGet( int mons_no, int heap, ALLOC_TYPE alloc_type )
{	
	void* p_buff;
	
	GF_ASSERT( mons_no <= MONSNO_END );

	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CHAR_DMMY + mons_no, TRUE, heap, alloc_type );

	// �擾���s
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���Ճp���b�g�f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^
 */
//-----------------------------------------------------------------------------
void* PokeFootPlttPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_PLTT, FALSE, heap, alloc_type );

	// �擾���s
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՃZ���f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^
 */
//-----------------------------------------------------------------------------
void* PokeFootCellPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CELL, TRUE, heap, alloc_type );

	// �擾���s
	GF_ASSERT( p_buff );

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՃZ���A�j���f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^
 */
//-----------------------------------------------------------------------------
void* PokeFootCellAnmPtrGet( int heap, ALLOC_TYPE alloc_type )
{
	void* p_buff;
	
	p_buff = ArcUtil_Load( ARC_POKEFOOT_GRA, POKEFOOT_ARC_CELLANM, TRUE, heap, alloc_type );

	// �擾���s
	GF_ASSERT( p_buff );

	return p_buff;
}



// �A�[�J�C�u�t�@�C��IDX�@�f�[�^IDX
//----------------------------------------------------------------------------
/**
 *	@brief	�A�[�J�C�u�t�@�C��IDX�擾
 *
 *	@param	none	
 *
 *	@return	�A�[�J�C�u�t�@�C��IDX
 */
//-----------------------------------------------------------------------------
int PokeFootArcFileGet( void )
{
	return ARC_POKEFOOT_GRA;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^IDX�擾
 *
 *	@param	mons_no		�����X�^�[�i���o�[
 *
 *	@return	�L�����N�^�f�[�^IDX
 */
//-----------------------------------------------------------------------------
int PokeFootCharDataIdxGet( int mons_no )
{
	return POKEFOOT_ARC_CHAR_DMMY + mons_no;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^IDX�擾
 *
 *	@param	none
 *
 *	@return	�p���b�g�f�[�^IDX
 */
//-----------------------------------------------------------------------------
int PokeFootPlttDataIdxGet( void )
{
	return POKEFOOT_ARC_PLTT;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�Z���f�[�^IDX�擾
 *
 *	@param	none
 *
 *	@return	�Z���f�[�^IDX
 */
//-----------------------------------------------------------------------------
int PokeFootCellDataIdxGet( void )
{
	return POKEFOOT_ARC_CELL;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�j���f�[�^IDX�擾
 *
 *	@param	none
 *
 *	@return	�Z���A�j���f�[�^IDX
 */
//-----------------------------------------------------------------------------
int PokeFootCellAnmDataIdxGet( void )
{
	return POKEFOOT_ARC_CELLANM;
}

