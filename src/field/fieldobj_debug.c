//==============================================================================
/**
 *
 * @file	fieldobj_debug.c
 * @brief	フィールドOBJ　デバッグ
 * @author	kagaya
 * @data	2005.07.11
 *
 */
//==============================================================================
//----
#ifdef PM_DEBUG
//----
#include "common.h"
#include "fieldobj.h"

#include "..\fielddata\maptable\zone_id.h"

//==============================================================================
//	エイリアステスト
//==============================================================================
#ifdef DEBUG_ALIES

const FIELD_OBJ_H DATA_DebugFldOBJHeaderR202A[2] =
{
	{
		128,		///<識別ID
		BOY1,		///<表示するOBJコード
		MV_DMY,	///<動作コード
		0,			///<イベントタイプ
		ZONE_ID_C01,///<イベントフラグ
		SCRID_ALIES,///<イベントID
		DIR_DOWN,	///<指定方向
		0,	///<指定パラメタ 0
		0,	///<指定パラメタ 1
		0,	///<指定パラメタ 2
		1,	///<X方向移動制限
		1,///<Z方向移動制限
		171,///<グリッドX
		798,///<グリッドZ
		0,	///<Y値
	},
	{
		129,		///<識別ID
		BOARD_A,	///<表示するOBJコード
		MV_DMY,	///<動作コード
		0,			///<イベントタイプ
		ZONE_ID_C01,///<イベントフラグ
		SCRID_ALIES,///<イベントID
		DIR_DOWN,	///<指定方向
		0,	///<指定パラメタ 0
		0,	///<指定パラメタ 1
		0,	///<指定パラメタ 2
		1,	///<X方向移動制限
		1,///<Z方向移動制限
		170,///<グリッドX
		798,///<グリッドZ
		0,	///<Y値
	},
};

const FIELD_OBJ_H DATA_DebugFldOBJHeaderC01[2] =
{
	{
		128,		///<識別ID
		BOY1,		///<表示するOBJコード
		MV_DMY,	///<動作コード
		0,			///<イベントタイプ
		0,///<イベントフラグ
		0,///<イベントID
		DIR_DOWN,	///<指定方向
		0,	///<指定パラメタ 0
		0,	///<指定パラメタ 1
		0,	///<指定パラメタ 2
		1,	///<X方向移動制限
		1,///<Z方向移動制限
		171,///<グリッドX
		798,///<グリッドZ
		0,	///<Y値
	},
	{
		129,		///<識別ID
		BOARD_A,		///<表示するOBJコード
		MV_DMY,	///<動作コード
		0,			///<イベントタイプ
		0,///<イベントフラグ
		0,///<イベントID
		DIR_DOWN,	///<指定方向
		0,	///<指定パラメタ 0
		0,	///<指定パラメタ 1
		0,	///<指定パラメタ 2
		1,	///<X方向移動制限
		1,///<Z方向移動制限
		170,///<グリッドX
		798,///<グリッドZ
		0,	///<Y値
	},
};

//--------------------------------------------------------------
/**
 * エイリアステスト　古いゾーンOBJ削除時のテスト
 * @param
 * @retval
 */
//--------------------------------------------------------------
FIELD_OBJ_H * DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeader(
		int new_zone_id, int *head_max, const FIELD_OBJ_H *head )
{
	int max;
	FIELD_OBJ_H *debughead;
	
	max = *head_max;
	
	if( new_zone_id == ZONE_ID_C01 ){
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderC01[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderC01[1];
		max += 2;
		OS_Printf( "フィールドOBJ ゾーン更新削除処理にてエイリアステスト　C01\n" );
	}else if( new_zone_id == ZONE_ID_R202 ){
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderR202A[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderR202A[1];
		max += 2;
		OS_Printf( "フィールドOBJ ゾーン更新削除処理にてエイリアステスト　R202\n" );
	}else{
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
	}
	
	*head_max = max;
	return( debughead );
}

void DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeaderDelete( FIELD_OBJ_H *head )
{
	sys_FreeMemory( HEAPID_FIELD, head );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ AddBin()エイリアス用
 * @param
 * @retval
 */
//--------------------------------------------------------------
FIELD_OBJ_H * DEBUG_FieldOBJ_AddBinHeaderAlies(
		int zone_id, int *head_max, const FIELD_OBJ_H *head )
{
	int max = *head_max;
	FIELD_OBJ_H *debughead;
	
	if( zone_id == ZONE_ID_C01 ){
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderC01[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderC01[1];
		max += 2;
		OS_Printf( "フィールドOBJ 一括追加処理にてエイリアステスト　C01\n" );
	}else if( zone_id == ZONE_ID_R202 ){
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderR202A[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderR202A[1];
		max += 2;
		OS_Printf( "フィールドOBJ 一括追加処理にてエイリアステスト　C01\n" );
	}else{
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*max );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
	}

	*head_max = max;
	return( debughead );
}

void DEBUG_FieldOBJ_AddBinHeaderAliesDelete( FIELD_OBJ_H *head )
{
	sys_FreeMemory( HEAPID_WORLD, head );
}
#endif	//DEBUG_ALIES

//----
#endif	//PM_DEBUG
//----
