#ifndef _CAMERA_H_
#define _CAMERA_H_

//カメラトレースマスク定義
#define CAM_TRACE_MASK_X	(1)
#define CAM_TRACE_MASK_Y	(2)
#define CAM_TRACE_MASK_Z	(4)
#define CAM_TRACE_MASK_ALL	(CAM_TRACE_MASK_X|CAM_TRACE_MASK_Y|CAM_TRACE_MASK_Z)

extern GXBufferMode	SwapBuffMode;
//---------------------------------------------------------
//			定数定義
//---------------------------------------------------------
//---------------------------
//	射影フラグ定数
enum
{
	GF_CAMERA_PERSPECTIV,		// 透視射影
	GF_CAMERA_ORTHO,			// 正射影
};

/*---------------------------------------------------------------------------*
	カメラアングル構造体
 *---------------------------------------------------------------------------*/
typedef struct
{
	u16 x;
	u16 y;
	u16 z;
	u16 Dummy;
} CAMERA_ANGLE;

/*---------------------------------------------------------------------------*
	カメラアングル構造体
 *---------------------------------------------------------------------------*/
//カメラパラメータ構造体
typedef	struct	{
//	VecFx32			*Position;
	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	u8				dummy;
}GF_CAMERA_PARAM;

typedef struct GF_CAMERA_tag * GF_CAMERA_PTR;
typedef struct GF_CAMERA_tag const * GF_CAMERA_CONST_PTR;

extern void GFC_AllocTraceData(	const int inHistNum, const int inDelay,
								const int inTraceMask, const int inHeapID,
								GF_CAMERA_PTR ioCamera);

extern void GFC_FreeTraceData(GF_CAMERA_PTR camera_ptr);

//カメラ作成
extern GF_CAMERA_PTR GFC_AllocCamera(const int inHeapID);

//カメラ解放
extern void GFC_FreeCamera(GF_CAMERA_PTR camera_ptr);

//カメラコピー
extern void GFC_CopyCamera(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera);
//カメラトレースデータのポインタコピー
extern void GFC_CopyCameraTracePtr(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera);
//カメラ反映関数（描画時に呼ぶ）
extern void GFC_CameraLookAt();
//カメラの上方向を設定
extern void GFC_SetCamUp(const VecFx32 *inCamUp,GF_CAMERA_PTR camera_ptr);
//カメラ初期化
extern void GFC_InitCameraTDA( const VecFx32* inTarget,
						const fx32 inDistance,
						const CAMERA_ANGLE *inAngle,
						const u16 inPerspWay,
						const u8 inView,
						const BOOL inBindFlg,
						GF_CAMERA_PTR camera_ptr
					);
//カメラ初期化
extern void GFC_InitCameraCDA( const VecFx32* inCamPos,
						const fx32 inDistance,
						const CAMERA_ANGLE *inAngle,
						const u16 inPerspWay,
						const u8 inView,
						GF_CAMERA_PTR camera_ptr
					);

//カメラ初期化
extern void GFC_InitCameraTC( const VecFx32* inTarget,
							const VecFx32* inCamPos,
							const u16 inPerspWay,
							const u8 inView,
							const BOOL inbindFlg,
							GF_CAMERA_PTR camera_ptr
						);

//カメラのアタッチ(カメラの有効化)
void GFC_AttachCamera(GF_CAMERA_PTR camera_ptr);
//カメラがバインドする対象物をセット
void GFC_BindCameraTarget(const VecFx32 *inTarget, GF_CAMERA_PTR camera_ptr);
//カメラがバインドしている対象物を切り離す
extern void GFC_PurgeCameraTarget(GF_CAMERA_PTR camera_ptr);
//現在のカメラからスワップバッファモードを取得
extern GXBufferMode GetBufferMode(void);
//カメラにNULLをセット
extern void GFC_PurgeCamera(void);
//射影セット
extern void GFC_SetCameraView(const u8 inView,GF_CAMERA_PTR camera_ptr);
//視野角のセット
extern void GFC_SetCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr);
//視野角の加算
extern void GFC_AddCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr);
//カメラと注視点を同時に平行移動
extern void GFC_ShiftCamera(const VecFx32 *inMoveVec,GF_CAMERA_PTR camera_ptr);
//カメラアングルセット	自転
extern void GFC_SetCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//カメラアングルセット　公転
extern void GFC_SetCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//カメラアングル加算　自転
extern void GFC_AddCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//カメラアングル加算　公転
extern void GFC_AddCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr);
//カメラ距離セット
extern void GFC_SetCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr);
//注視点再設定
extern void GFC_ReSetCameraTarget(const VecFx32 *inTargetVec,GF_CAMERA_PTR camera_ptr);
//カメラ距離加算
extern void GFC_AddCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr);
//カメラクリップ座標セット
extern void GFC_SetCameraClip(const fx32 near,const fx32 far,GF_CAMERA_PTR camera_ptr);
//射影取得
extern u8 GFC_GetCameraView(GF_CAMERA_CONST_PTR camera_ptr);
//視野角の取得
extern u16 GFC_GetCameraPerspWay(GF_CAMERA_CONST_PTR camera_ptr);
//距離の取得
extern fx32 GFC_GetCameraDistance(GF_CAMERA_CONST_PTR camera_ptr);
//アングルの取得
extern CAMERA_ANGLE GFC_GetCameraAngle(GF_CAMERA_CONST_PTR camera_ptr);
//注視点の取得
extern VecFx32 GFC_GetLookTarget(GF_CAMERA_CONST_PTR camera_ptr);
//カメラ位置の取得
extern VecFx32 GFC_GetCameraPos(GF_CAMERA_CONST_PTR camera_ptr);
//ファー取得
extern fx32 GFC_GetCameraFar(GF_CAMERA_CONST_PTR camera_ptr);
//ニア取得
extern fx32 GFC_GetCameraNear(GF_CAMERA_CONST_PTR camera_ptr);
//注視点の設定
extern void GFC_SetLookTarget(const VecFx32* t_pos, GF_CAMERA_PTR camera_ptr);
//カメラ位置の設定
extern void GFC_SetCameraPos(const VecFx32* c_pos, GF_CAMERA_PTR camera_ptr);

#endif //_CAMERA_H_
