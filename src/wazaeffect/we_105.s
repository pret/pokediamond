//==============================================================================
/**
 * @file	we_105.s
 * @brief	Ç∂Ç±Ç≥Ç¢ÇπÇ¢			105
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZIKOSAISEI
	
// =============================================================================
//
//
//	Å°Ç∂Ç±Ç≥Ç¢ÇπÇ¢			105
//
//
// =============================================================================
WEST_ZIKOSAISEI:
	
	LOAD_PARTICLE_DROP	0,W_105_SPA
	ADD_PARTICLE 	0,W_105_105_JIKO_BALL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_105_105_JIKO_KIRA, EMTFUNC_ATTACK_POS
	
	SE_L			SEQ_SE_DP_W025
	WAIT			10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_YELLOW, 10,0

	SE_WAITPLAY_L	SEQ_SE_DP_W071B,31

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
