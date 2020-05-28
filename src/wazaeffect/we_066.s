//==============================================================================
/**
 * @file	we_066.s
 * @brief	Ç∂Ç≤Ç≠ÇÆÇÈÇ‹			66
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZIGOKUGURUMA
	
// =============================================================================
//
//
//	Å°Ç∂Ç≤Ç≠ÇÆÇÈÇ‹			66
//
//
// =============================================================================
#define WE066_ROTA_NUM	(7)
#define WE066_SYNC		(10)
WEST_ZIGOKUGURUMA:
	LOAD_PARTICLE_DROP	0,W_066_SPA
	LOAD_PARTICLE_DROP	1,W_004_SPA
	
	FUNC_CALL		WEST_SP_WE_066, 3, WE066_ROTA_NUM, WE066_SYNC, WE_TOOL_M1, 0, 0, 0, 0, 0
	FUNC_CALL		WEST_SP_WE_066, 3, WE066_ROTA_NUM, WE066_SYNC, WE_TOOL_E1, 0, 0, 0, 0, 0
	
	ADD_PARTICLE	0,W_066_066_KEMURI_ROLL01,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE	0,W_066_066_KEMURI_ROLL02,	 EMTFUNC_DEFENCE_POS

	SE_WAITPLAY_L		SEQ_SE_DP_W104,1
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,10

	SE_WAITPLAY_L		SEQ_SE_DP_W104,10
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,20

	SE_WAITPLAY_L		SEQ_SE_DP_W104,20
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,30

	SE_WAITPLAY_L		SEQ_SE_DP_W104,30
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,40

	SE_WAITPLAY_L		SEQ_SE_DP_W104,40
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,50

	SE_WAITPLAY_L		SEQ_SE_DP_W104,50
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,60

	SE_WAITPLAY_L		SEQ_SE_DP_W104,60
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,70

	SE_WAITPLAY_L		SEQ_SE_DP_W104,70
	SE_WAITPLAY_R		SEQ_SE_DP_W025B,80

	LOOP_LABEL	5
		WAIT 8
		ADD_PARTICLE	1,W_004_PUNCH_HIT01,	 EMTFUNC_DEFENCE_POS
	LOOP

	WAIT_PARTICLE

	EXIT_PARTICLE	0,
	EXIT_PARTICLE	1,

	WAIT_FLAG		///<TCBë“Çø
	
	SEQEND
