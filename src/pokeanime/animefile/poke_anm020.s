//==============================================================================
/**
 * @file	poke_anm020.s
 * @brief	スパーク
 * @author	
 * @date	
 *
 */
//==============================================================================

	.text
	
	.include	"past.h"
	.include	"past_def.h"
	
	.global		PAST_ANIME020
	
// =============================================================================
//
//
//	スパーク
//
//
// =============================================================================
PAST_ANIME020:
	SET_WAIT		3
	SET_PALETTE_FADE	16,16,0,0x3ff
	SET_REQUEST

	SET_PALETTE_FADE	0,0,0,0x3ff
	SET_REQUEST

	SET_WAIT		6
	SET_PALETTE_FADE	16,16,0,0x3ff
	SET_REQUEST

	SET_WAIT		1
	SET_PALETTE_FADE	0,0,0,0x3ff
	SET_REQUEST

	
	START_LOOP		4
		SET_PALETTE_FADE	16,16,0,0x3ff
		SET_REQUEST
		
		SET_PALETTE_FADE	0,0,0,0x3ff
		SET_REQUEST
		SET_WAIT		1
	END_LOOP
	
	END_ANM
