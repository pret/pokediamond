//==============================================================================
/**
 * @file	we_013.s
 * @brief	Ç©Ç‹Ç¢ÇΩÇø			13
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAMAITATI
	
// =============================================================================
//
//
//	Å°Ç©Ç‹Ç¢ÇΩÇø			13
//
//
// =============================================================================
WEST_KAMAITATI:

	TURN_CHK	TURN_1, TURN_2

	SEQEND

TURN_1:

	LOAD_PARTICLE_DROP	0, W_013_SPA
//	CAMERA_CHG		0, WE_CAMERA_TYPE_PERSPECTIV	
	ADD_PARTICLE 	0, W_013_013_TORNADO,	EMTFUNC_ATTACK_POS
//	ADD_PARTICLE 	0, W_013_SLASH03,		EMTFUNC_ATTACK_POS
	
	WAIT			10
	SE_L			SEQ_SE_DP_060
	WAIT			10

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

TURN_2:
	
	LOAD_PARTICLE_DROP	0,W_013_SPA
	ADD_PARTICLE 	0,W_013_013_HIT_SLASH, EMTFUNC_DF_SIDE

	SE_WAITPLAY_R	SEQ_SE_DP_146,5
	
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E2 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

