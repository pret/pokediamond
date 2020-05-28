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

	.global		WEST_401
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_401:
	
	LOAD_PARTICLE_DROP	0,W_401_SPA
	WAIT			1
	
	SE_L			SEQ_SE_DP_W057

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1
	
	LOOP_LABEL		1
		FUNC_CALL		WEST_SP_WE_T10, 4,  2, 0,  +8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		2
		FUNC_CALL		WEST_SP_WE_T10, 4,  2, 0,  -8, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT		2	
	LOOP

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_1	
	FUNC_CALL			WEST_SP_POKE_OAM_VIEW,	5, WEDEF_POKE_CAP_ID_0, 30, WT_BF_3DFRAME, 0, WEDEF_DROP_M1
	FUNC_CALL			WEST_SP_POKE_OAM_VIEW,	5, WEDEF_POKE_CAP_ID_1, 30, WT_BF_3DFRAME, 0, WEDEF_DROP_M2
	
	ADD_PARTICLE 	0,W_401_401_RING_BIG,		EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_401_401_BALL_BURN,		EMTFUNC_ATTACK_POS

	WAIT			25
	POKE_OAM_ENABLE	WEDEF_POKE_CAP_ID_0, 0,
	POKE_OAM_ENABLE	WEDEF_POKE_CAP_ID_1, 0,
	SE_R			SEQ_SE_DP_W291
	
	ADD_PARTICLE 	0,W_401_401_KEMURI_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_RES_FREE
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

