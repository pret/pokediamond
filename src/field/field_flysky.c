//******************************************************************************
/**
 * 
 * @file	field_flysky.c
 * @brief	�t�B�[���h�@������Ƃ�
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
//	�t�B�[���h�@��`�Z�@������Ƃ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ��`�Z������ԃJ�b�g�C�����}�b�v�J�ڃC�x���g�Ăяo���p�̃��[�N�Z�b�g
 * @param	heap_id		���[�N���m�ۂ���HEAP ID
 * @param	fsys		FIELDSYS_WORK *
 * @param	param		�\������POKEMON_PARAM *
 * @param	zone_id		�J�ڂ���]�[��ID
 * @param	map_gx		�J�ڐ�o���ʒu�O���b�hX���W
 * @param	map_gz		�J�ڐ�o���ʒu�O���b�hZ���W
 * @retval	void*		�m�ۂ������[�N*
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
 * ����ԃJ�b�g�C�����}�b�v�J��
 * @param	event	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�I��
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

