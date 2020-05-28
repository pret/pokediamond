//==============================================================================
/**
 * @file	we_153.s
 * @brief	ÇæÇ¢ÇŒÇ≠ÇÕÇ¬			153
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DAIBAKUHATU
	
// =============================================================================
//
//
//	Å°ÇæÇ¢ÇŒÇ≠ÇÕÇ¬			153
//
//
// =============================================================================
WEST_DAIBAKUHATU:

	LOAD_PARTICLE_DROP	0,W_153_SPA
	
	SE_L			SEQ_SE_DP_SHUSHU

	ADD_PARTICLE 	0,W_153_153_DAIBAKU_BALL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_153_153_DAIBAKU_CORE, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_153_153_DAIBAKU_LIGHT,EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_153_153_DAIBAKU_BOMB, EMTFUNC_ATTACK_POS
	
	WAIT			40
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 15, WE_PAL_WHITE,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 15,20
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M2, 0, 1, WE_PAL_WHITE, 15,20
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_WHITE, 15,20
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E2, 0, 1, WE_PAL_WHITE, 15,20

	WAIT			1
	SE_C			SEQ_SE_DP_186
	WAIT			14
	//SE_REPEAT_L	SEQ_SE_DP_W153,3,4
	SE_REPEAT_L		SEQ_SE_DP_W436,3,4
		
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_B_X, 0, SHAKE_B_WAIT, SHAKE_B_NUM,  WE_TOOL_STAGE | WE_TOOL_SSP

	WAIT			15

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 15, 0, WE_PAL_WHITE,
	
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 8, 8, 0, 8, 0
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
