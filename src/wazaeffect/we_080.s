//==============================================================================
/**
 * @file	we_080.s
 * @brief	ÇÕÇ»Ç—ÇÁÇÃÇ‹Ç¢			80
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HANABIRANOMAI
	
// =============================================================================
//
//
//	Å°ÇÕÇ»Ç—ÇÁÇÃÇ‹Ç¢			80
//
//
// =============================================================================
WEST_HANABIRANOMAI:
	
	LOAD_PARTICLE_DROP	0,W_080_SPA
	SE_L			SEQ_SE_DP_W080

	FUNC_CALL		WEST_SP_WE_KAITEN, 3, WE_TOOL_M1, 3, 10
	
	LOOP_LABEL		3
	
		ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN01, EMTFUNC_ATTACK_POS
		ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN02, EMTFUNC_ATTACK_POS
		ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN03, EMTFUNC_ATTACK_POS
		ADD_PARTICLE 	0,W_080_080_BALL_SPIN,		  EMTFUNC_ATTACK_POS
		WAIT			10
	
	LOOP
	
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN02,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0, W_080_080_HANABIRA_SPIN03,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_080_080_BALL_SPIN,			EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_W080C
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
