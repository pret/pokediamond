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

	.global		WEST_399
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_399:
	
	LOAD_PARTICLE_DROP	0,W_399_SPA
	WAIT			1

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1

	SE_FLOW_LR			SEQ_SE_DP_W399

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1	
	FUNC_CALL			WEST_SP_POKE_OAM_VIEW,	5, WEDEF_POKE_CAP_ID_0, 30, WT_BF_3DFRAME, 0, WEDEF_DROP_M1
	FUNC_CALL			WEST_SP_POKE_OAM_VIEW,	5, WEDEF_POKE_CAP_ID_1, 30, WT_BF_3DFRAME, 0, WEDEF_DROP_M2
	
	WAIT			1
	
	ADD_PARTICLE 	0,W_399_399_BALL_BURN1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_399_399_RING_BURN,	EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 1	

	WAIT			25
	POKE_OAM_ENABLE	WEDEF_POKE_CAP_ID_0, 0,
	POKE_OAM_ENABLE	WEDEF_POKE_CAP_ID_1, 0,
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 0	
	
	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_RES_FREE
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

