//==============================================================================
/**
 * @file	we_121.s
 * @brief	�^�}�S�΂�����			121
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TAMAGOBAKUDAN
	
// =============================================================================
//
//
//	���^�}�S�΂�����			121
//
//
// =============================================================================
WEST_TAMAGOBAKUDAN:
	
	LOAD_PARTICLE_DROP	0,W_121_SPA
	LOAD_PARTICLE_DROP	1,W_121_SPA
	
	SE_FLOW_LR		SEQ_SE_DP_W039
	ADD_PARTICLE_EMIT_SET 	0, 1, W_121_121_EGGBOM_BALL, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 0, 0, 0, 10, 64,
	
	WAIT			8
	SE_R			SEQ_SE_DP_W120
	WAIT			2
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	ADD_PARTICLE 	0,W_121_121_EGGBOM_BOMB,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_121_121_EGGBOM_BOMB2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_121_121_EGGBOM_HIT,		EMTFUNC_DEFENCE_POS

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	EXIT_PARTICLE	1,
	
	SEQEND
