//==============================================================================
/**
 * @file	we_297.s
 * @brief	�t�F�U�[�_���X			297
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_FEZAADANSU
	
// =============================================================================
//
//
//	���t�F�U�[�_���X			297
//
//
// =============================================================================
WEST_FEZAADANSU:
	LOAD_PARTICLE_DROP	0,W_297_SPA
	
	SE_R			SEQ_SE_DP_W080

	ADD_PARTICLE 	0,W_297_297_HANE_TURN, EMTFUNC_DEFENCE_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

#if 0
	FUNC_CALL	WEST_SP_TEST_1, 0, 0
	FUNC_CALL	WEST_SP_TEST_2, 0, 0
	FUNC_CALL	WEST_SP_TEST_3, 0, 0
	FUNC_CALL	WEST_SP_TEST_4, 0, 0
	
	WAIT		60
#endif
	SEQEND

