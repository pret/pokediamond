//==============================================================================
/**
 * @file	wesub_006.s
 * @brief	Ç±ÇÒÇÁÇÒ
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusKonran
	
// =============================================================================
//
//
//	Å°âÒïú
//
//
// =============================================================================
WEST_StatusRECOVER:

	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_1,
	
	FUNC_CALL	ST_EFF_RECOVER, 2, STEFF_GRA_RECOVER, 0

	//SE_L			SEQ_SE_DP_W036
	SE_L			SEQ_SE_DP_W071B

	WAIT			5
	ADD_PARTICLE 	0, STATUS_EFF_TURN_HEAL, EMTFUNC_ATTACK_POS
	
	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2
	POKEOAM_RES_FREE
		
	//SE_L			SEQ_SE_DP_W234

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
