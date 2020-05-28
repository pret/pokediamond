//******************************************************************************
/**
 *
 * @file	field_zoom.c
 * @brief	フィールドのカメラワーク、簡易ズーム
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#include "common.h"
#include "field_zoom.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
/// ZOOM_WORK	
//--------------------------------------------------------------
typedef struct
{
	u32 heap_id;
	int seq_no;
	int end_flag;
	ZOOMTYPE zoom_type;
	fx32 org_distance;
	fx32 target_dist;
	fx32 target_dist_end;
	u32 target_frame;
	fx32 now_dist;
	u32 now_frame;
	fx32 dist_speed;
	FIELDSYS_WORK *fsys;
	GF_CAMERA_PTR camera;
}ZOOM_WORK;

#define ZOOM_WORK_SIZE (sizeof(ZOOM_WORK))

//==============================================================================
//	static
//==============================================================================
static void Zoom_TCB( TCB_PTR tcb, void *wk );
static void (* const ZoomTypeTbl[ZOOMTYPE_MAX+1])( ZOOM_WORK *work );

static void zp_SetDistance( ZOOM_WORK *work );
static void zp_TargetSppedInit( ZOOM_WORK *work );
static void zp_TargetBackInit( ZOOM_WORK *work );
static int zp_TargetSppedUp( ZOOM_WORK *work );

//==============================================================================
//	ズーム処理
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールド　カメラズーム処理追加
 * @param	fsys	FIELDSYS_WORK *
 * @param	heap_id	ヒープID
 * @retval	TCB_PTR カメラズーム動作TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR FieldZoom_Init( FIELDSYS_WORK *fsys, u32 heap_id )
{
	TCB_PTR tcb;
	ZOOM_WORK *work = sys_AllocMemoryLo( heap_id, ZOOM_WORK_SIZE );
	memset( work, 0, ZOOM_WORK_SIZE );
	
	work->heap_id = heap_id;
	work->zoom_type = ZOOMTYPE_NON;
	work->fsys = fsys;
	work->camera = fsys->camera_ptr;
	work->org_distance = GFC_GetCameraDistance( work->camera );
	work->now_dist = work->org_distance;
	
	tcb = TCB_Add( Zoom_TCB, work, 0xffff );
	return( tcb );
}

//--------------------------------------------------------------
/**
 * カメラズーム処理終了チェック
 * @param	tcb		TCB_PTR
 * @retval	BOOL	TRUE=終了
 */
//--------------------------------------------------------------
BOOL FieldZoom_EndCheck( TCB_PTR tcb )
{
	ZOOM_WORK *work = TCB_GetWork( tcb );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * カメラズーム処理削除
 * @param	tcb		TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldZoom_Delete( TCB_PTR tcb )
{
	ZOOM_WORK *work = TCB_GetWork( tcb );
	sys_FreeMemoryEz( work );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * カメラズーム処理タイプ変更
 * @param	tcb				TCB_PTR
 * @param	type			ZOOMTYPE
 * @param	target_dist		目標距離 -でズームイン +でズームアウト
 * @param	target_frame	目標フレーム　何フレームでtarget_distに到達するか
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldZoom_TypeChange(
	TCB_PTR tcb, ZOOMTYPE type, fx32 target_dist, u32 target_frame )
{
	ZOOM_WORK *work = TCB_GetWork( tcb );
	work->seq_no = 0;
	work->end_flag = FALSE;
	work->zoom_type = type;
	work->target_dist = target_dist;
	work->target_frame = target_frame;
	work->now_frame = 0;
}

//==============================================================================
//	ズーム動作
//==============================================================================
//--------------------------------------------------------------
/**
 * ズーム動作　tcb
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Zoom_TCB( TCB_PTR tcb, void *wk )
{
	ZOOM_WORK *work = wk;
	ZoomTypeTbl[work->zoom_type]( work );
}

//==============================================================================
//	ズーム動作	ZOOMTYPE_NON
//==============================================================================
//--------------------------------------------------------------
/**
 * カメラ動作　無し
 * @param	work	ZOOM_WORK *
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static void ZoomType_Non( ZOOM_WORK *work )
{
	work->end_flag = TRUE;
}

//==============================================================================
//	ズーム動作	ZOOMTYPE_ZOOM
//==============================================================================
//--------------------------------------------------------------
/**
 * カメラ動作　ZOOMTYPE_ZOOM
 * @param	work	ZOOM_WORK *
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static void ZoomType_Zoom( ZOOM_WORK *work )
{
	switch( work->seq_no ){
	case 0:
		zp_TargetSppedInit( work );
		work->seq_no++;
	case 1:
		if( zp_TargetSppedUp(work) == TRUE ){
			work->seq_no++;
			work->end_flag = TRUE;
		}
		
		zp_SetDistance( work );
	}
}

//==============================================================================
//	ズーム動作	ZOOMTYPE_BACK
//==============================================================================
//--------------------------------------------------------------
/**
 * カメラ動作　ZOOMTYPE_BACK
 * @param	work	ZOOM_WORK *
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static void ZoomType_Back( ZOOM_WORK *work )
{
	switch( work->seq_no ){
	case 0:
		zp_TargetBackInit( work );
		work->seq_no++;
	case 1:
		if( zp_TargetSppedUp(work) == TRUE ){
			work->seq_no++;
			work->end_flag = TRUE;
		}
		
		zp_SetDistance( work );
	}
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * カメラ距離セット
 * @param	work	ZOOM_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void zp_SetDistance( ZOOM_WORK *work )
{
	GFC_SetCameraDistance( work->now_dist, work->camera );
}

//--------------------------------------------------------------
/**
 * カメラ距離　目標距離、目標フレームを元に速度初期化
 * @param	work	ZOOM_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void zp_TargetSppedInit( ZOOM_WORK *work )
{
	fx32 fxframe = work->target_frame;
	work->dist_speed = work->target_dist / fxframe;
	work->target_dist_end = work->now_dist + work->target_dist;
}

//--------------------------------------------------------------
/**
 * カメラ距離　元の位置へ目標フレームを元に速度初期化
 * @param	work	ZOOM_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void zp_TargetBackInit( ZOOM_WORK *work )
{
	fx32 fxframe = work->target_frame;
	fx32 dist = work->org_distance - work->now_dist;
	work->dist_speed = dist / fxframe;
	work->target_dist_end = work->org_distance;
}

//--------------------------------------------------------------
/**
 * カメラ距離　速度を加える
 * @param	work	ZOOM_WORK
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
static int zp_TargetSppedUp( ZOOM_WORK *work )
{
	work->now_dist += work->dist_speed;
	work->now_frame++;
	
	if( work->now_frame >= work->target_frame ){
		work->now_frame = work->target_frame;
		work->now_dist = work->target_dist_end;
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	ズーム動作テーブル	並びはZOOMTYPE一致
//--------------------------------------------------------------
static void (* const ZoomTypeTbl[ZOOMTYPE_MAX+1])( ZOOM_WORK *work ) =
{
	ZoomType_Non,		//ZOOMTYPE_NON
	ZoomType_Zoom,		//ZOOMTYPE_ZOOM
	ZoomType_Back,		//ZOOMTYPE_BACK
};

