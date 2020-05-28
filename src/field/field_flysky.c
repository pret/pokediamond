//******************************************************************************
/**
 * 
 * @file	field_flysky.c
 * @brief	フィールド　そらをとぶ
 * @author	kagaya
 * @data	05.07.13
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "field_event.h"
#include "field_cutin.h"
#include "ev_mapchange.h"
#include "mapdata_warp.h"

#include "field_flysky.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
//	SORATOBI_WORK
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	int seq_no;
	u16 zone_id;
	s16 map_gx;
	s16 map_gz;
	POKEMON_PARAM *poke_param;
	TCB_PTR tcb_cutin;
}SORATOBI_WORK;

#define SORATOBI_WORK_SIZE (sizeof(SORATOBI_WORK))

//==============================================================================
//	フィールド　秘伝技　そらをとぶ
//==============================================================================
//--------------------------------------------------------------
/**
 * 秘伝技そらを飛ぶカットイン→マップ遷移イベント呼び出し用のワークセット
 * @param	heap_id		ワークを確保するHEAP ID
 * @param	fsys		FIELDSYS_WORK *
 * @param	param		表示するPOKEMON_PARAM *
 * @param	zone_id		遷移するゾーンID
 * @param	map_gx		遷移先出現位置グリッドX座標
 * @param	map_gz		遷移先出現位置グリッドZ座標
 * @retval	void*		確保したワーク*
 */
//--------------------------------------------------------------
void * EventWorkSet_FlySkyMapChange( u32 heap_id,
		FIELDSYS_WORK *fsys, POKEMON_PARAM *param, u16 zone_id, s16 map_gx, s16 map_gz )
{
	SORATOBI_WORK *work = sys_AllocMemoryLo( heap_id, SORATOBI_WORK_SIZE );
	memset( work, 0, SORATOBI_WORK_SIZE );
	work->fsys = fsys;
	work->poke_param = param;
	work->zone_id = zone_id;
	work->map_gx = map_gx;
	work->map_gz = map_gz;
	return( work );
}

//--------------------------------------------------------------
/**
 * 空を飛ぶカットイン→マップ遷移
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=終了
 */
//--------------------------------------------------------------
BOOL GMEVENT_FlySkyMapChange( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	SORATOBI_WORK *work = FieldEvent_GetSpecialWork( event );
	
	switch( work->seq_no ){
	case 0:
		work->tcb_cutin = FieldCutIn_Init(
			work->fsys, CUTIN_TYPE_SKY,
			work->poke_param, Player_SexGet(work->fsys->player) );
		
		work->seq_no++;
		break;
	case 1:
		if( FieldCutIn_EndCheck(work->tcb_cutin) == FALSE ){
			break;
		}
		
		FieldCutIn_End( work->tcb_cutin );
		
		{
			u16 warp_id;
			LOCATION_WORK loc;
			//warp_id = WARPDATA_SearchByFieldID(work->zone_id);
			warp_id = WARPDATA_SearchForFly(work->zone_id, work->map_gx, work->map_gz);
			GF_ASSERT(warp_id != 0);
			WARPDATA_GetWarpLocation(warp_id, &loc);
			EventChange_MapChangeBySky( event,
					loc.zone_id, DOOR_ID_JUMP_CODE,
					loc.grid_x, loc.grid_z, DIR_DOWN );
			
		}
		
		sys_FreeMemoryEz( work );
	}
	
	return( FALSE );
}

