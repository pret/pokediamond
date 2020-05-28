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
WEST_Hataku:

	LOAD_PARTICLE_DROP	0,W_454_SPA
	
	ADD_PARTICLE		0, W_454_454_KEMURI_BURN01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_454_454_KEMURI_BURN02, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_454_454_BEE_PARTY01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE		0, W_454_454_BEE_PARTY02,	EMTFUNC_DEFENCE_POS
	
	//SE_REPEAT_R		SEQ_SE_DP_W456,8,6
	SE_REPEAT_R			SEQ_SE_DP_W456,6,8

	WAIT				28
	SE_R				SEQ_SE_DP_W109
	WAIT				3

	//SE_REPEAT_R			SEQ_SE_DP_W025B,4,2
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,20
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,24

	FUNC_CALL			WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*8,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
