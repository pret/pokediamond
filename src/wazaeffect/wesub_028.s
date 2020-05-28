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

	.global		WEST_EAT


#define ROTA_NUM_S ((360*0xffff) / 360)
#define ROTA_NUM_E ((365*0xffff) / 360)
#define ROTA_SYNC	(10)
WEST_EAT:

	LOOP_LABEL		2
		
		SE_R			SEQ_SE_DP_W036
		
		FUNC_CALL		WEST_SP_POKEROTA_00, 6, ROTA_NUM_S, ROTA_NUM_E, ROTA_SYNC, 2, 0, 32, 0,1
		WAIT_FLAG
		
	LOOP	
	
	SEQEND
