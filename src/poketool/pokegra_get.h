//============================================================================================
/**
 * @file	pokegra_get.h
 * @brief	�|�P�����O���t�B�b�N�擾����
 * @author	Hiroyuki Nakamura
 * @date	2005.05.09
 */
//============================================================================================
#ifndef POKEGRA_GET_H
#define POKEGRA_GET_H
#undef GLOBAL
#ifdef POKEGRA_GET_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
/*
   0000_0000_0000_0000_0000_0000_0000_0000
     || |||| |||| |||| �J���i���o�[
     || |||| |||| ||||
     || |||| ����R�[�h�i�A���m�[���Ȃǁj�i5bit�ŏ\���j
     || ||||
     || ||�t�@�C���^�C�v
     || ||
     || �O���t�B�b�N�^�C�v
     ||
	 |����
	 |
	 �J���[
*/

#define	POKEGRA_EXCODE_SHIFT	( 16 )	// �p�����[�^�V�t�g�F����R�[�h

#define	POKEGRA_CGX		( 0x00000000 )	// �t�@�C���^�C�v�F�L����
#define	POKEGRA_PAL		( 0x01000000 )	// �t�@�C���^�C�v�F�p���b�g
#define	POKEGRA_FRNT	( 0x00000000 )	// �O���t�B�b�N�^�C�v�F�O��
#define	POKEGRA_BACK	( 0x04000000 )	// �O���t�B�b�N�^�C�v�F�w��
#define	POKEGRA_ICON	( 0x08000000 )	// �O���t�B�b�N�^�C�v�F�A�C�R��
#define	POKEGRA_MALE	( 0x00000000 )	// ��
#define	POKEGRA_FEMALE	( 0x10000000 )	// ��
#define	POKEGRA_N_COL	( 0x00000000 )	// �ʏ�J���[
#define	POKEGRA_R_COL	( 0x20000000 )	// ���A�J���[

// ����R�[�h�F�A���m�[���p��`
#define POKEGRA_UNA		( 0x00000000 )	// A
#define POKEGRA_UNB		( 0x00010000 )	// B
#define POKEGRA_UNC		( 0x00020000 )	// C
#define POKEGRA_UND		( 0x00030000 )	// D
#define POKEGRA_UNE		( 0x00040000 )	// E
#define POKEGRA_UNF		( 0x00050000 )	// F
#define POKEGRA_UNG		( 0x00060000 )	// G
#define POKEGRA_UNH		( 0x00070000 )	// H
#define POKEGRA_UNI		( 0x00080000 )	// I
#define POKEGRA_UNJ		( 0x00090000 )	// J
#define POKEGRA_UNK		( 0x000a0000 )	// K
#define POKEGRA_UNL		( 0x000b0000 )	// L
#define POKEGRA_UNM		( 0x000c0000 )	// M
#define POKEGRA_UNN		( 0x000d0000 )	// N
#define POKEGRA_UNO		( 0x000e0000 )	// O
#define POKEGRA_UNP		( 0x000f0000 )	// P
#define POKEGRA_UNQ		( 0x00100000 )	// Q
#define POKEGRA_UNR		( 0x00110000 )	// R
#define POKEGRA_UNS		( 0x00120000 )	// S
#define POKEGRA_UNT		( 0x00130000 )	// T
#define POKEGRA_UNU		( 0x00140000 )	// U
#define POKEGRA_UNV		( 0x00150000 )	// V
#define POKEGRA_UNW		( 0x00160000 )	// W
#define POKEGRA_UNX		( 0x00170000 )	// X
#define POKEGRA_UNY		( 0x00180000 )	// Y
#define POKEGRA_UNZ		( 0x00190000 )	// Z
#define POKEGRA_EXC		( 0x001a0000 )	// !
#define POKEGRA_QUE		( 0x001b0000 )	// ?


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �p�X���쐬
 *
 * @param	path	�p�X���i�[�ꏊ
 * @param	param	�p�����[�^
 *
 * @return	none
 *
 * @li	�쐬�����p�X���̗�F"/data/pmdp_frnt_001_m.ncgr"�i�t�V�M�_�l���̑O�ʂ̃L�����j
 *
 *	��P�j�L�������̑O�ʃL����
 *	  PokeGraGetPath( path, MONSNO_KIMORI | POKEGRA_CGX | POKEGRA_FRNT | POKEGRA_MALE );
 *	��Q�j�L�������̃p���b�g
 *	  PokeGraGetPath( path, MONSNO_KIMORI | POKEGRA_PAL | POKEGRA_FRNT | POKEGRA_N_COL );
 *	��R�j�L�����̃A�C�R���L����
 *	  PokeGraGetPath( path, MONSNO_KIMORI | POKEGRA_CGX | POKEGRA_ICON );
 *	��S�j�L�����̃A�C�R���p���b�g
 *	  PokeGraGetPath( path, MONSNO_KIMORI | POKEGRA_PAL | POKEGRA_ICON );
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeGraGetPath( char * path, u32 param );

//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�擾
 *
 * @param	param	�p�����[�^
 * @param	mode	�������擾���[�h
 *
 * @return	�O���t�B�b�N�f�[�^
 *
 * @li	malloc���g�p����̂ŁA�J����Y�ꂸ�ɁI
 */
//--------------------------------------------------------------------------------------------
GLOBAL void * PokeGraGet( u32 param, u8 mode );


#undef GLOBAL
#endif	/* POKEGRA_GET_H */
