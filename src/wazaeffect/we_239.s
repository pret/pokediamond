//==============================================================================
/**
 * @file	we_239.s
 * @brief	ÇΩÇ¬Ç‹Ç´			239
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TATUMAKI
	
// =============================================================================
//
//
//	Å°ÇΩÇ¬Ç‹Ç´			239
//
//
// =============================================================================
WEST_TATUMAKI:
	
	LOAD_PARTICLE_DROP	0,W_239_SPA
	CAMERA_CHG		0,WE_CAMERA_TYPE_PERSPECTIV
	ADD_PARTICLE 	0,W_239_239_TORNADO_ROLL1, EMTFUNC_DF_SIDE
	ADD_PARTICLE 	0,W_239_239_TORNADO_ROLL2, EMTFUNC_DF_SIDE

	WAIT			10
	SE_R			SEQ_SE_DP_060
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 15,  WE_TOOL_E1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 15,  WE_TOOL_E2 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
