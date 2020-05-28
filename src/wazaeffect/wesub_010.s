//==============================================================================
/**
 * @file	wesub_010.s
 * @brief	あいてむ
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_PokeItemUse
	
// =============================================================================
//
//
//	■アイテム
//
//
// =============================================================================
#define Y_TOP		(140)
#define FWAIT		(1)
#define IWAIT		(5)
#define OWAIT		(5)
#define TWAIT		(IWAIT + OWAIT)
WEST_PokeItemUse:

	LOAD_PARTICLE_DROP	0, SPA_ITEM_EFF
	
	ADD_PARTICLE 	0, ITEM_EFF_ITEM_POKE, EMTFUNC_ATTACK_POS

	WAIT			5
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	
	LOOP_LABEL		2

		SE_L		SEQ_SE_DP_W207

		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, Y_TOP, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT

	LOOP

	SE_L			SEQ_SE_DP_BT_001
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
