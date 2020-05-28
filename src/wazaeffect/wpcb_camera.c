//==============================================================================
/**
 * @file	wpcb_camera.c
 * @brief	コールバックカメラ設定
 * @author	goto
 * @date	2006.03.02(木)
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


// -----------------------------------------
//
//	サポート関数
//
// -----------------------------------------
static void COT_ExDataGet(ECB_OPERATOR_DATA* odp, int data[]);

// -----------------------------------------
//
//	カメラ操作関数
//
// -----------------------------------------
static BOOL COT_None(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_SpinCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_UserCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_MoveCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_MoveCamera145(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_MoveCamera169(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_MoveCamera126(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_ATCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL COT_DFCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);


//--------------------------------------------------------------
/**
 *
 * @brief	カメラ設定関数テーブル
 *
 */
//--------------------------------------------------------------
static BOOL (* const CameraOperatorTool[])(EMIT_PTR emit, ECB_OPERATOR_DATA* odp) = {
	COT_None,
	COT_SpinCamera,
	COT_UserCamera,
	COT_MoveCamera,
	COT_MoveCamera145,
	COT_MoveCamera169,
	COT_MoveCamera126,
	COT_ATCamera,
	COT_DFCamera,
};


// =============================================================================
//
//
//	■ private
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	拡張データ取得
 *
 * @param	odp	
 * @param	data[]	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void COT_ExDataGet(ECB_OPERATOR_DATA* odp, int data[])
{
	WeSysExDataGet(odp->wsp, data, OPERATOR_CAMERA_EX_DATA_NUM);
}


//--------------------------------------------------------------
/**
 * @brief	カメラ操作
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL COT_None(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle = { 0, 0, 0 };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
//	SetCameraAngleRot(&angle, camera_ptr);
	GFC_SetCameraAngleRev(&angle, camera_ptr);
	
#ifdef WPCB_FREE_EMITTER_MOVE

	DebugWazaEffect_LoopEmitter(odp->ptc, emit, odp->wsp);
	
#endif

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	スピンカメラ設定
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
#define COT_SPIN_CAMERA_X	(0x1000*2)
#define COT_SPIN_CAMERA_Y	(0x1000*2)
#define COT_SPIN_CAMERA_Z	(0)
static BOOL COT_SpinCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle = { COT_SPIN_CAMERA_X, COT_SPIN_CAMERA_Y, COT_SPIN_CAMERA_Z };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	Particle_CameraTypeSet(odp->ptc, GF_CAMERA_ORTHO);			///< 正射影
	GFC_SetCameraAngleRev(&angle, camera_ptr);					///< カメラアングルを変更
//	SetCameraAngleRot(&angle, camera_ptr);

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	ユーザーカメラ設定
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL COT_UserCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int data[ OPERATOR_CAMERA_EX_DATA_NUM ];
	CAMERA_ANGLE	angle = { 0,0,0,0 };
	GF_CAMERA_PTR	camera_ptr;
	
	COT_ExDataGet(odp, data);
	
	angle.x = data[1];
	angle.y = data[2];
	angle.z = data[3];
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	GFC_SetCameraAngleRev(&angle, camera_ptr);

#ifdef WPCB_FREE_EMITTER_MOVE

	DebugWazaEffect_LoopEmitter(odp->ptc, emit, odp->wsp);
	
#endif
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	移動カメラ設定
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
#define COT_MOVE_CAMERA_X	(0x1000*3)
#define COT_MOVE_CAMERA_Y	(0x1000*2)
#define COT_MOVE_CAMERA_Z	(0x1000)
static BOOL COT_MoveCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle = { -COT_MOVE_CAMERA_X, COT_MOVE_CAMERA_Y, COT_MOVE_CAMERA_Z };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	Particle_CameraTypeSet(odp->ptc, GF_CAMERA_ORTHO);			///< 正射影
	GFC_SetCameraAngleRev(&angle, camera_ptr);					///< カメラアングルを変更
	
	return TRUE;
}

#define COT_MOVE_CAMERA2_X	(49664)
#define COT_MOVE_CAMERA2_Y	(5952)
#define COT_MOVE_CAMERA2_Z	(4096)
static BOOL COT_MoveCamera145(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle  = { COT_MOVE_CAMERA2_X, COT_MOVE_CAMERA2_Y, COT_MOVE_CAMERA2_Z };
	CAMERA_ANGLE  angle2 = { 9248, 3744, 0 };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);		
	Particle_CameraTypeSet(odp->ptc, GF_CAMERA_ORTHO);			///< 正射影
	
	if (WES_ContestFlag_Get(odp->wsp) == TRUE){
		GFC_SetCameraAngleRev(&angle, camera_ptr);					///< カメラアングルを変更
	}
	else {
		GFC_SetCameraAngleRev(&angle2, camera_ptr);					///< カメラアングルを変更
	}
	
	return TRUE;
}

static BOOL COT_MoveCamera169(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle = { COT_MOVE_CAMERA2_X, COT_MOVE_CAMERA2_Y, COT_MOVE_CAMERA2_Z };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	Particle_CameraTypeSet(odp->ptc, GF_CAMERA_ORTHO);			///< 正射影
	GFC_SetCameraAngleRev(&angle, camera_ptr);					///< カメラアングルを変更
	
	return TRUE;
}

static BOOL COT_MoveCamera126(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	GF_CAMERA_PTR camera_ptr;
	CAMERA_ANGLE  angle = { 0, 0, -6000 };
	
	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	Particle_CameraTypeSet(odp->ptc, GF_CAMERA_ORTHO);			///< 正射影
	GFC_SetCameraAngleRev(&angle, camera_ptr);					///< カメラアングルを変更
	
	return TRUE;	
}

static BOOL COT_ATCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	VecFx32 vec;

	GF_CAMERA_PTR	camera_ptr;

	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	WET_PokeParticleLookAtPosGet(odp->wsp, odp->s_client, &vec);

	GFC_SetLookTarget(&vec, camera_ptr);

	return TRUE;
}


static BOOL COT_DFCamera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	VecFx32 vec;

	GF_CAMERA_PTR	camera_ptr;

	camera_ptr = Particle_GetCameraPtr(odp->ptc);
	
	WET_PokeParticleLookAtPosGet(odp->wsp, odp->e_client, &vec);

	GFC_SetLookTarget(&vec, camera_ptr);

	return TRUE;
}


// =============================================================================
//
//
//	■ public
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	カメラ設定実行関数
 *
 * @param	no	
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CameraOperator_Executed(int no, EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	BOOL res;

	res = CameraOperatorTool[ no ](emit, odp);
	
	if (res == FALSE){
		OS_Printf("camera operator == false\n");
	}	
}

