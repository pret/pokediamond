//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	none
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
	.text
	
	.include	"west.h"

	.global		WEST_JOY

///< ‚¿‚å‚¢‚¿‚å‚¢
WEST_JOY:
	
	LOOP_LABEL		2
		SE_R		SEQ_SE_DP_001
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  -8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
	LOOP
	
	SEQEND

