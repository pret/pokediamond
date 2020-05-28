//==============================================================================
/**
 * @file	we_106.s
 * @brief	Ç©ÇΩÇ≠Ç»ÇÈ			106
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KATAKUNARU
	
// =============================================================================
//
//
//	Å°Ç©ÇΩÇ≠Ç»ÇÈ			106
//
//
// =============================================================================
WEST_KATAKUNARU:

	LOAD_PARTICLE_DROP	0,W_106_SPA
	
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_1,
	
	ADD_PARTICLE 	0,W_106_106_KATAKU_KIRA, EMTFUNC_ATTACK_POS
	
	SE_REPEAT_L		SEQ_SE_DP_W231,12,2

	FUNC_CALL	ST_EFF_METAL, 2, STEFF_GRA_METAL, 0

	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	POKEOAM_RES_FREE
	
	SEQEND
