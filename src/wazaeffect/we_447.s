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
WEST_447:
	LOAD_PARTICLE_DROP	0,W_447_SPA
	
	ADD_PARTICLE 	0,W_447_447_MUSUBI_LINE1,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_447_447_MUSUBI_LINE2,		EMTFUNC_DEFENCE_POS
//	ADD_PARTICLE 	0,W_447_447_MUSUBI_LEAF1,		EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_300
	WAIT			5	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
