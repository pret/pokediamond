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

	.global		WEST_366
	
// =============================================================================
//
//
//	���͂���
//
//
// =============================================================================
WEST_366:

	LOAD_PARTICLE_DROP	0,W_366_SPA
	
	SE_FLOW_LR	SEQ_SE_DP_KAZE
	SIDE_JP		0, WEST_366_SIDE_MINE, WEST_366_SIDE_ENEMY
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

WEST_366_SIDE_MINE:
	
	ADD_PARTICLE 	0,W_366_366_OIKAZE_LINE, EMTFUNC_ATTACK_POS	
	ADD_PARTICLE 	0,W_366_366_OIKAZE_WIND, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

WEST_366_SIDE_ENEMY:
	
	ADD_PARTICLE 	0,W_366_366_OIKAZE_LINE2, EMTFUNC_ATTACK_POS	
	ADD_PARTICLE 	0,W_366_366_OIKAZE_WIND2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_NONE, OPERATOR_POS_NONE, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

