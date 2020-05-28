//==============================================================================
/**
 * @file	ball_effect_tool.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.05.01(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"

#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"

#include "include/poketool/pokeicon.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"


#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"

#include "ball_effect_tool.h"
#include "include/application/cb_sys.h"

//--------------------------------------------------------------
/**
 * @brief	2点間の距離
 *
 * @param	x1	
 * @param	y1	
 * @param	x2	
 * @param	y2	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int  BET_PtoP(s16 x1, s16 y1, s16 x2, s16 y2)
{
	int range;
	
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	
	range = FX_Sqrt( ((py*py)+(px*px)) * FX32_ONE ) / FX32_ONE;
	
	return range;
}


//--------------------------------------------------------------
/**
 * @brief	シールの位置
 *
 * @param	seal	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BET_Seal_RangeGet(CB_SEAL* seal)
{
	int range;
	s16 x, y;
	
	x = CB_SaveData_SealPXGet(seal);
	y = CB_SaveData_SealPYGet(seal);
	
	range = BET_PtoP(x, y, SEAL_DEF_POS_X, SEAL_DEF_POS_Y);
	
	return range;
}

//--------------------------------------------------------------
/**
 * @brief	シールの位置から待ち時間取得
 *
 * @param	seal	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BET_Seal_RangeWaitGet(CB_SEAL* seal)
{
	int type;
	int wait;
	int range;
	int seal_id;
	int tbl_id;
	const u8 wait_tbl[] = {
		0,8,14,20,20,16,16,
	};
	
	seal_id = CB_SaveData_SealIDGet(seal);
	
	type = Seal_TypeGet(seal_id);
	
	if (type == 0){
		range = BET_Seal_RangeGet(seal);
		OS_Printf("range = %2d\n", range);
		if (range >= (CB_RELEASE_RANGE - 4)){
			tbl_id = 3;
		}
		else {
			tbl_id = (((range + 1) / CB_RELEASE_RANGE_LINE));// % CB_WAIT_TABLE;
			if (tbl_id >= CB_WAIT_TABLE){
				tbl_id = 3;
			}
		}
		wait = wait_tbl[ tbl_id ];
		OS_Printf("tbl id = %2d, w = %2d\n",tbl_id, wait);
	}
	else {
		wait = wait_tbl[ 1 ];
	}	
	
	return wait;
}

