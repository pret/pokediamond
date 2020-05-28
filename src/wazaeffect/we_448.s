//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_448:
	
	LOAD_PARTICLE_DROP	0,W_448_SPA
	
	ADD_PARTICLE 	0,W_448_448_OSYABERI_RING,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_448_448_OSYABERI_ONPU,		EMTFUNC_ATTACK_POS
	
	//SE_L		SEQ_SE_DP_187
	VOICE_PLAY		PV_NORMAL, WAZA_SE_PAN_AT, PV_VOL_MAX

	LOOP_LABEL		2
		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
		FUNC_CALL		WEST_SP_WE_T05, 3, 16, -16, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		16
		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		8
	LOOP
	
	VOICE_WAIT_STOP 0

	WAIT_FLAG
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
