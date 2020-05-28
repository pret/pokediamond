//==============================================================================
/**
 * @file	we_001.s
 * @brief	�͂���
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	���͂���
//
//
// =============================================================================
WEST_Hataku:

	LOAD_PARTICLE_DROP		0,W_459_SPA

	ADD_PARTICLE		0, W_459_459_DUST01,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_459_459_DUST02,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_459_459_DUST_BURN,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_459_459_BALL_BIG,		EMTFUNC_ATTACK_POS	
	ADD_PARTICLE		0, W_459_459_LINE_BURN,		EMTFUNC_ATTACK_POS
	
	SE_L				SEQ_SE_DP_W459

	///< ���΂炭������w�i���炭
	WAIT			20
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	
	WAIT			30
	SE_L				SEQ_SE_DP_W060C
	WAIT			20

	///< ���̐F�ɖ߂���
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
		
	///< ��C�ɔ���
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 0, 15, WE_PAL_WHITE,
	WAIT_FLAG

	SE_R			SEQ_SE_DP_W053

	///< �ڂ���[�[�[�[�[��
	ADD_PARTICLE		0, W_459_459_BOMB_LINE01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_459_459_BOMB_LINE02,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_B_X, 0, SHAKE_B_WAIT, SHAKE_B_NUM*4,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	WAIT_PARTICLE
	EXIT_PARTICLE		0,
	
	WAIT			20
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, -2, 15, 0, WE_PAL_WHITE,
	WAIT_FLAG
	SE_STOP			SEQ_SE_DP_W053
	
	SEQEND

