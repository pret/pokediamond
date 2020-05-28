//============================================================================================
/**
 * @file	pokeicon.h
 * @bfief	�|�P�����A�C�R���֘A����
 * @author	Hiroyuki Nakamura
 * @date	05.09.16
 */
//============================================================================================
#ifndef POKEICON_H
#define POKEICON_H

#include "poketool\poke_tool.h"

#undef GLOBAL
#ifdef POKEICON_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
// �f�I�L�V�X�p��`
enum {
	PICON_DEOKISISU_N = 0,		// �m�[�}���t�H����
	PICON_DEOKISISU_A,			// �A�^�b�N�t�H����
	PICON_DEOKISISU_D,			// �f�B�t�F���X�t�H����
	PICON_DEOKISISU_S			// �X�s�[�h�t�H����
};

// �A���m�[���p��`
enum {
	PICON_ANNOON_A = 0,			// A
	PICON_ANNOON_B,				// B
	PICON_ANNOON_C,				// C
	PICON_ANNOON_D,				// D
	PICON_ANNOON_E,				// E
	PICON_ANNOON_F,				// F
	PICON_ANNOON_G,				// G
	PICON_ANNOON_H,				// H
	PICON_ANNOON_I,				// I
	PICON_ANNOON_J,				// J
	PICON_ANNOON_K,				// K
	PICON_ANNOON_L,				// L
	PICON_ANNOON_M,				// M
	PICON_ANNOON_N,				// N
	PICON_ANNOON_O,				// O
	PICON_ANNOON_P,				// P
	PICON_ANNOON_Q,				// Q
	PICON_ANNOON_R,				// R
	PICON_ANNOON_S,				// S
	PICON_ANNOON_T,				// T
	PICON_ANNOON_U,				// U
	PICON_ANNOON_V,				// V
	PICON_ANNOON_W,				// W
	PICON_ANNOON_X,				// X
	PICON_ANNOON_Y,				// Y
	PICON_ANNOON_Z,				// Z
	PICON_ANNOON_EXQ,			// !
	PICON_ANNOON_QUE,			// ?
};

// �A�j���E�F�C�g�擾�p�����[�^
enum {
	POKEICON_HP_MAX = 0,
	POKEICON_HP_GREEN,
	POKEICON_HP_YERROW,
	POKEICON_HP_RED,
	POKEICON_HP_NULL
};

// �A�j�����
enum {
	POKEICON_ANM_DEATH = 0,		// �m��
	POKEICON_ANM_HPMAX,			// HP MAX
	POKEICON_ANM_HPGREEN,		// HP ��
	POKEICON_ANM_HPYERROW,		// HP ��
	POKEICON_ANM_HPRED,			// HP ��
	POKEICON_ANM_STCHG,			// ��Ԉُ�
};

#define	POKEICON_PAL_MAX	( 3 )	// �A�C�R���Ŏg�p����p���b�g��

#define POKEICON_SIZE_X		(32)	// �A�C�R���̉��T�C�Y
#define POKEICON_SIZE_Y		(32)	// �A�C�R���̏c�T�C�Y

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾 ( POKEMON_PASO_PARAM �� )
 *
 * @param	ppp			POKEMON_PASO_PARAM
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 *
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconCgxArcIndexGet( const POKEMON_PASO_PARAM* ppp );

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾 ( POKEMON_PARAM �� )
 *
 * @param	pp			POKEMON_PARAM
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 *
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconCgxArcIndexGetByPP( POKEMON_PARAM * pp );

//--------------------------------------------------------------------------------------------
/**
 * �L�����̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	mons		�|�P�����ԍ�
 * @param	egg			�^�}�S�t���O
 * @param	pat			�g���p�^�[��
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 *
 *	pat�̓f�I�L�V�X��A���m�[���Ɏg�p
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconCgxArcIndexGetByMonsNumber( u32 mons, u32 egg, u32 pat );

//--------------------------------------------------------------------------------------------
/**
 * �L�����̊g���p�^�[���i���o�[���擾�i�擾�����i���o�[��PokeIconCgxArcIndexGetByMonsNo�̈����Ƃ��Ďg����j
 *
 * @param   ppp		
 *
 * @retval  u16		�g���p�^�[���i���o�[
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 PokeIconCgxPatternGet( const POKEMON_PASO_PARAM* ppp );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�ԍ��擾
 *
 * @param	mons		�|�P�����ԍ�
 * @param	form		�t�H�����ԍ�
 * @param	egg			�^�}�S�t���O
 *
 * @return	�p���b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL const u8 PokeIconPalNumGet( u32 mons, u32 form, u32 egg );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�ԍ��擾�iPOKEMON_PASO_PARAM�Łj
 *
 * @param	ppp		POKEMON_PASO_PARAM
 *
 * @return	�p���b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL const u8 PokeIconPalNumGetByPPP( const POKEMON_PASO_PARAM * ppp );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�ԍ��擾�iPOKEMON_PARAM�Łj
 *
 * @param	pp		POKEMON_PARAM
 *
 * @return	�p���b�g�ԍ�
 */
//--------------------------------------------------------------------------------------------
GLOBAL const u8 PokeIconPalNumGetByPP( POKEMON_PARAM * pp );

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconPalArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconCellArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾�i�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconAnmCellArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���̃A�[�J�C�u�C���f�b�N�X�擾�i64k,�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIcon64kCellArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconCellAnmArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾�i�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIconAnmCellAnmArcIndexGet(void);

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�j���̃A�[�J�C�u�C���f�b�N�X�擾�i64k,�A�j������j
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 PokeIcon64kCellAnmArcIndexGet(void);


#undef GLOBAL
#endif	// POKEICON_H
