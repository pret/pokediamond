//==============================================================================
/**
 * @file	we_201.s
 * @brief	���Ȃ��炵			201
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUNAARASI
	
// =============================================================================
//
//
//	�����Ȃ��炵			201
//
//
// =============================================================================
WEST_SUNAARASI:
	
	LOAD_PARTICLE_DROP	0,W_201_SPA
	ADD_PARTICLE 	0,W_201_201_SUNAARASI_KONA, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_201_201_SUNAARASI_MIST, EMTFUNC_DUMMY

	SE_C			SEQ_SE_DP_W201

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
