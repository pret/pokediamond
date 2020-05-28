//==============================================================================
/**
 * @file	we_336.s
 * @brief	�Ƃ��ڂ�			336
 * @author	goto
 * @date	2005.07.13(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOOBOE
	
// =============================================================================
//
//
//	���Ƃ��ڂ�			336
//
//
// =============================================================================
WEST_TOOBOE:
	
	LOAD_PARTICLE_DROP	0,W_336_SPA

	VOICE_PLAY		PV_W_TOOBOE, WAZA_SE_PAN_AT, PV_VOL_MAX					
	
	FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, 150, 100, (20 << 16) | 1, (6 << 16) | 6
	
	ADD_PARTICLE 	0,W_336_336_VOICE_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			5
	
	ADD_PARTICLE 	0,W_336_336_CIRCLE_BURN, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	VOICE_WAIT_STOP 0
	WAIT			2			///< ����TCB�폜�҂�

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
