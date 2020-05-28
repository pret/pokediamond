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
WEST_443:
	LOAD_PARTICLE_DROP	0,W_443_SPA
	
	ADD_PARTICLE 	0,W_443_443_BOMB_STONE1,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_443_443_BOMB_STONE2,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_443_443_BOMB_HIT,			EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_290
	WAIT			20
	SE_R			SEQ_SE_DP_W443B
	WAIT			2
	SE_R			SEQ_SE_DP_W443B
	WAIT			3
	SE_R			SEQ_SE_DP_W443B
	WAIT			2
	SE_R			SEQ_SE_DP_W443B
	WAIT			3
	SE_R			SEQ_SE_DP_W443B
	WAIT			5
	SE_R			SEQ_SE_DP_W443B
	WAIT			2
	SE_R			SEQ_SE_DP_W443B
	WAIT			3
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*4,  WE_TOOL_E1 | WE_TOOL_SSP,
		
	SE_WAITPLAY_R	SEQ_SE_DP_161,5
	SE_WAITPLAY_R	SEQ_SE_DP_161,15

	WAIT_PARTICLE
	EXIT_PARTICLE	0,


	SEQEND
