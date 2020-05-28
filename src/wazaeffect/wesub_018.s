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
//	Å°ìVåÛ ñ∂
//
//
// =============================================================================
WEST_WeatherMist:

	LOAD_PARTICLE_DROP	0, SPA_WEATHER_EFF

	SE_REPEAT_C		SEQ_SE_DP_W109,4,3

	ADD_PARTICLE 	0, WEATHER_EFF_TURN_MIST1, EMTFUNC_DUMMY
	ADD_PARTICLE 	0, WEATHER_EFF_TURN_MIST2, EMTFUNC_DUMMY
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
