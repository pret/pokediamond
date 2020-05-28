//==============================================================================
/**
 * @file	we_045.s
 * @brief	Ç»Ç´Ç≤Ç¶			45
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NAKIGOE
	
// =============================================================================
//
//
//	Å°Ç»Ç´Ç≤Ç¶			45
//
//
// =============================================================================
WEST_NAKIGOE:

	LOAD_PARTICLE_DROP	0,W_045_SPA
	ADD_PARTICLE 	0,W_045_045_VOICE_BURN, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_045_045_RING_BIG,	EMTFUNC_ATTACK_POS
	
	VOICE_PLAY		PV_W_NAKIGOE1, WAZA_SE_PAN_AT, PV_VOL_DEFAULT
	VOICE_WAIT_STOP 0
	VOICE_PLAY		PV_W_NAKIGOE2, WAZA_SE_PAN_AT, PV_VOL_MAX
	
	WAIT			5

	VOICE_WAIT_STOP 0

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E2 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
