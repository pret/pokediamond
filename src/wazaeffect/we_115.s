//==============================================================================
/**
 * @file	we_115.s
 * @brief	���t���N�^�[			115
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RIHUREKUTAA
	
// =============================================================================
//
//
//	�����t���N�^�[			115
//
//
// =============================================================================
WEST_RIHUREKUTAA:

	LOAD_PARTICLE_DROP	0,W_115_SPA
	ADD_PARTICLE 	0,W_115_115_REFRCT_MIRRROR, EMTFUNC_AT_SIDE
	ADD_PARTICLE 	0,W_115_115_REFRCT_KIRA02,  EMTFUNC_AT_SIDE
	SE_L			SEQ_SE_DP_W115

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
