//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		pokefoot.h
 *	@brief		�|�P�������ՃO���t�B�b�N�f�[�^�擾�֐�
 *	@author		tomoya takahashi
 *	@data		2006.01.31
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __POKEFOOT_H__
#define __POKEFOOT_H__

#undef GLOBAL
#ifdef	__POKEFOOT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

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
 *	@return	�t�@�C���f�[�^	�j���͊e��
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCharPtrGet( int mons_no, int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	���Ճp���b�g�f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^	�j���͊e��
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootPlttPtrGet( int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	���ՃZ���f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^	�j���͊e��
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCellPtrGet( int heap, ALLOC_TYPE alloc_type );
//----------------------------------------------------------------------------
/**
 *	@brief	���ՃZ���A�j���f�[�^�擾
 *
 *	@param	heap	�q�[�v
 *	@param	alloc_type	�A���b�N�^�C�v
 *
 *	@return	�t�@�C���f�[�^	�j���͊e��
 * [allocType]
 *		ALLOC_TOP		�q�[�v�擪����m��
 *		ALLOC_BOTTOM	�q�[�v�������m��
 */
//-----------------------------------------------------------------------------
GLOBAL void* PokeFootCellAnmPtrGet( int heap, ALLOC_TYPE alloc_type );

// �A�[�J�C�u�t�@�C��IDX�@�f�[�^IDX
// �L�����N�^�@�Z���@�Z���A�j���f�[�^�͈��k����Ă��܂�
GLOBAL int PokeFootArcFileGet( void );
GLOBAL int PokeFootCharDataIdxGet( int mons_no );
GLOBAL int PokeFootPlttDataIdxGet( void );
GLOBAL int PokeFootCellDataIdxGet( void );
GLOBAL int PokeFootCellAnmDataIdxGet( void );


#undef	GLOBAL
#endif		// __POKEFOOT_H__

