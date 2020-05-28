//==============================================================================
/**
 * @file	wpcd_debug.c
 * @brief	デバッグ
 * @author	goto
 * @date	2006.03.03(金)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================


#include "common.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"
#include "wp_callback.h"
#include "we_tool.h"
#include "we_err.h"
#include "we_def.h"

#include "wpcb_common.h"


//--------------------------------------------------------------
/**
 * @brief	デバッグ情報表示
 *
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void Debug_OperatorStatusPrint(ECB_OPERATOR_DATA* odp)
{
	OS_Printf("\n----- operator 利用中 -----\n");
	OS_Printf("開始クライアント　%d\n", odp->s_client);
	OS_Printf("終了クライアント　%d\n", odp->e_client);
	OS_Printf("反転フラグ　　　　%d\n", odp->reverce_flag);
	OS_Printf("\n----- operator mode -----\n");
	OS_Printf("ターゲット　　　　%d\n", odp->mode[0]);
	OS_Printf("座標操作　　　　　%d\n", odp->mode[1]);
	OS_Printf("方向操作　　　　　%d\n", odp->mode[2]);
	OS_Printf("フィールド操作　　%d\n", odp->mode[3]);
	OS_Printf("カメラ操作　　　　%d\n", odp->mode[4]);
	
	///< 詳細
	if (odp->mode[ ECB_MODE_FIELD ] == OPERATOR_FLD_NONE){ return; }
	
	OS_Printf("フィールド操作　詳細%d\n");
	{
		int i;
		int num;
		int bit;
		
		char str_debug_msg[][255] = {
			"OPERATOR_FLD_NONE",
			"OPERATOR_FLD_GRAVITY_MAG",
			"OPERATOR_FLD_RANDOM_MAG",
			"OPERATOR_FLD_RANDOM_INTVL",
			"OPERATOR_FLD_MAGNET_POS",
			"OPERATOR_FLD_MAGNET_MAG",
			"OPERATOR_FLD_SPIN_RAD",
			"OPERATOR_FLD_SPIN_AXIS",
			"OPERATOR_FLD_SIMPLE_CLS_Y",
			"OPERATOR_FLD_SIMPLE_CLS_CB",
			"OPERATOR_FLD_SIMPLE_CLS_EVT",
			"OPERATOR_FLD_SIMPLE_CLS_GLB",
			"OPERATOR_FLD_CONVERGENCE_POS",
			"OPERATOR_FLD_CONVERGENCE_RATIO",
			"OPERATOR_FLD_END",
		};
		
		num = FieldOperator_BitDataMax();
		
		for (i = 0; i < num; i++){
			
			bit = FieldOperator_BitGet(i);

			if (IsBitCheck(odp->mode[ ECB_MODE_FIELD ], bit) == FALSE){ continue; }
			
			OS_Printf("%s\n", str_debug_msg[i]);
		}
	}
}


