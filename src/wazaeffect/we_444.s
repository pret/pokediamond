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
WEST_444:
	LOAD_PARTICLE_DROP	0,W_444_SPA
	
	ADD_PARTICLE 	0,W_444_444_STONE_STONE1,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_444_444_STONE_STONE2,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_444_444_STONE_LINE,			EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_444_444_STONE_HIT,			EMTFUNC_DEFENCE_POS
	
	SE_REPEAT_R		SEQ_SE_DP_W088,2,4
	WAIT			25
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_W082
	SE_REPEAT_R		SEQ_SE_DP_W088,6,3
		
	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
