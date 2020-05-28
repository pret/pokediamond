//============================================================================================
/**
 * @file	mapdata_warp.c
 * @brief	ワープ用データ関連ソース
 * @date	2005.12.19
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"
#include "field_common.h"
#include "mapdata_warp.h"

#include "mapdefine.h"
#include "fieldobj_code.h"		//DIR_UP DIR_DOWN
#include "ev_mapchange.h"		//DOOR_ID_JUMP_CODE

#include "sysflag.h"			//SysFlag_ArriveSet

//自動生成されるはずのシンボル定義
#include "../fielddata/warpdata/warpdata.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct {
	u16 room_id, room_gx, room_gz;
	u16 fld_id, fld_gx, fld_gz;
	u8 IsTeleportPos;
	u8 AutoSetArriveFlag;
	u16 arrive_id;
}WARPDATA;

//自動生成されるはずのデータ定義
#include "../fielddata/warpdata/warpdata.c"


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ワープIDの正規化
 * @param	warp_id		ワープID
 * @return	int			正規化したワープID
 *
 * 不正な値は変換する。1オリジンを0オリジンに変換する。
 */
//------------------------------------------------------------------
static int RegulateWarpID(int warp_id)
{
	if(warp_id <= 0 || warp_id > NELEMS(WarpData)) {
		GF_ASSERT_MSG(0, "不正なワープID（%d）です。\n", warp_id);
		warp_id = 1;		//製品版では不正な値でも動作するように補正する
	}
	warp_id --;		//1 origin --> 0 origin
	return warp_id;
}

//------------------------------------------------------------------
/**
 * @brief	ワープIDの初期値を取得する
 */
//------------------------------------------------------------------
int WARPDATA_GetInitializeID(void)
{
	return 1;
}

//------------------------------------------------------------------
/**
 * @brief	ワープ場所の取得
 * @param	warp_id		ワープID
 * @param	loc			場所を受け取るLOCATION_WORKへのポインタ
 */
//------------------------------------------------------------------
void WARPDATA_GetWarpLocation(int warp_id, LOCATION_WORK * loc)
{
	warp_id = RegulateWarpID(warp_id);

	loc->zone_id = WarpData[warp_id].fld_id;
	loc->door_id = DOOR_ID_JUMP_CODE;
	loc->grid_x = WarpData[warp_id].fld_gx;
	loc->grid_z = WarpData[warp_id].fld_gz;
	loc->dir = DIR_DOWN;
}

//------------------------------------------------------------------
/**
 * @brief	復活場所の取得
 * @param	warp_id		ワープID
 * @param	loc			場所を受け取るLOCATION_WORKへのポインタ
 */
//------------------------------------------------------------------
void WARPDATA_GetRevivalLocation(int warp_id, LOCATION_WORK * loc)
{
	warp_id = RegulateWarpID(warp_id);

	loc->zone_id = WarpData[warp_id].room_id;
	loc->door_id = DOOR_ID_JUMP_CODE;
	loc->grid_x = WarpData[warp_id].room_gx;
	loc->grid_z = WarpData[warp_id].room_gz;
	loc->dir = DIR_UP;
}

//------------------------------------------------------------------
/**
 * @brief	ワープIDの取得
 * @param	zone_id		検索する屋内のゾーンID
 * @retval	int			ワープID（１オリジン）
 * @retval	0			見つからなかった
 */
//------------------------------------------------------------------
int WARPDATA_SearchByRoomID(int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].room_id == zone_id
				&& WarpData[i].IsTeleportPos) {
			return i + 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * @brief	ワープIDの取得
 * @param	zone_id		検索するフィールドのゾーンID
 * @retval	int			ワープID（１オリジン）
 * @retval	0			見つからなかった
 */
//------------------------------------------------------------------
int WARPDATA_SearchByFieldID(int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id
				&& WarpData[i].IsTeleportPos) {
			return i + 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * @brief	ワープIDの取得（「そらをとぶ」用）
 * @param	zone_id		検索するフィールドのゾーンID
 * @param	gx			検索するX位置（グリッド単位）
 * @param	gz			検索するY位置（グリッド単位）
 * @retval	int			ワープID（１オリジン）
 * @retval	0			見つからなかった
 *
 * 同一ゾーン内に二箇所「そらをとぶ」の飛び先があるので、
 * タウンマップが返すブロック単位の選択位置を元にそれを判別
 * できるようにしている。
 */
//------------------------------------------------------------------
int WARPDATA_SearchForFly(int zone_id, int gx, int gz)
{
	int i;
	int blk_x = gx / 32;
	int blk_z = gz / 32;
	int id = 0;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id) {
			id = i + 1;
			if (blk_x == WarpData[i].fld_gx / 32 && blk_z == WarpData[i].fld_gz / 32) {
				return id;
			}
		}
	}
	return id;
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	到着フラグのセット
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	zone_id		セットする場所のゾーンID
 */
//------------------------------------------------------------------
void ARRIVEDATA_SetArriveFlag( FIELDSYS_WORK * fsys, int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id && WarpData[i].AutoSetArriveFlag) {
			SysFlag_ArriveSet(SaveData_GetEventWork(fsys->savedata), WarpData[i].arrive_id);
			return;
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	到着フラグを参照する
 * @param	fsys		フィールド制御ワークへのポインタ
 * @param	warp_id		対象となるマップのワープID
 * @retval	BOOL		TRUEのとき、来たことがある
 */
//------------------------------------------------------------------
BOOL ARRIVEDATA_GetArriveFlag(FIELDSYS_WORK * fsys, int warp_id)
{
	int reg_id = RegulateWarpID(warp_id);
	return SysFlag_ArriveGet(SaveData_GetEventWork(fsys->savedata), WarpData[reg_id].arrive_id);
}

