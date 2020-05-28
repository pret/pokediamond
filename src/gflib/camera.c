/*---------------------------------------------------------------------------*
  Project:  PokemonDS
  File:     camera.c

  基本カメラシステム

 *---------------------------------------------------------------------------*/

#include <nitro.h>
#include <nnsys.h>
# include "system.h"
#include "camera.h"
#include "calc3d.h"
#include "assert.h"

GXBufferMode	SwapBuffMode = GX_BUFFERMODE_W;		// スワップバッファモード

/*---------------------------------------------------------------------------*
	LookAt構造体
 *---------------------------------------------------------------------------*/
typedef struct
{
	VecFx32		camPos;					// カメラの位置(＝視点)
	VecFx32		target;					// カメラの焦点(＝注視点)
	VecFx32		camUp;					// カメラの上方向

} GF_CAMERA_LOOKAT;

/*---------------------------------------------------------------------------*
	Vw3Persp構造体
 *---------------------------------------------------------------------------*/
typedef struct
{
	fx32		fovySin;			// 視野角/2の正弦をとった値
    fx32		fovyCos;			// 視野角/2の余弦をとった値
    fx32		aspect;				// アスペクト比
    fx32		nearClip;			// 視点からnearクリップ面までの距離
    fx32		farClip;			// 視点からfarクリップ面までの距離

} GF_CAMERA_PERSP;

/*---------------------------------------------------------------------------*
	カメラトレース構造体
 *---------------------------------------------------------------------------*/
typedef struct GF_CAMERA_TRACE_tag
{
	int HistNum;
	int CamPoint;
	int TargetPoint;
	int Delay;			//遅延時間
	BOOL UpdateFlg;		//更新開始フラグ
	BOOL ValidX;		//X遅延を有効にするかのフラグ
	BOOL ValidY;		//Y遅延を有効にするかのフラグ
	BOOL ValidZ;		//Z遅延を有効にするかのフラグ
	VecFx32 *HistPos;
}GF_CAMERA_TRACE;

/*---------------------------------------------------------------------------*
	カメラ構造体
 *---------------------------------------------------------------------------*/
typedef struct GF_CAMERA_tag
{
	GF_CAMERA_PERSP		persp;
	GF_CAMERA_LOOKAT	lookat;

	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	VecFx32 BindTargetOld;
	const VecFx32 *BindTarget;
	BOOL XBind;
	BOOL YBind;
	BOOL ZBind;
	GF_CAMERA_TRACE *Trace;
} GF_CAMERA;

/*---------------------------------------------------------------------------*
	static変数
 *---------------------------------------------------------------------------*/
static GF_CAMERA_PTR 	GF_Camera = NULL;        // カメラ構造体ポインタ

//---------------------------------------------------------------------------
/**
 * @brief	カメラ位置を注視点、距離、アングルから算出する
 * 
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetCamPosByTarget_Dist_Ang(GF_CAMERA_PTR camera_ptr)
{
	u16 angle_x;
	//仰角⇒地面からの傾きに変換
	angle_x = -camera_ptr->Angle.x;
	/*== カメラ座標を求める ==*/
	camera_ptr->lookat.camPos.x = FX_Mul( FX_Mul( FX_SinIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.camPos.z = FX_Mul( FX_Mul( FX_CosIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.camPos.y = FX_Mul( FX_SinIdx( angle_x ), camera_ptr->Distance );

	/*== 視点からの距離にする ==*/
	VEC_Add(&camera_ptr->lookat.camPos,&camera_ptr->lookat.target,&camera_ptr->lookat.camPos);
	//camera_ptr->lookat.camPos.x += camera_ptr->lookat.target.x;
	//camera_ptr->lookat.camPos.y += camera_ptr->lookat.target.y;
	//camera_ptr->lookat.camPos.z += camera_ptr->lookat.target.z;
	
}

//---------------------------------------------------------------------------
/**
 * @brief	注視点をカメラ位置、距離、アングルから算出する
 * 
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetTargetByCamPos_Dist_Ang(GF_CAMERA_PTR camera_ptr)
{
	u16 angle_x;
	//仰角⇒地面からの傾きに変換
	angle_x = -camera_ptr->Angle.x;
	camera_ptr->lookat.target.x = -FX_Mul( FX_Mul( FX_SinIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.target.z = -FX_Mul( FX_Mul( FX_CosIdx( camera_ptr->Angle.y ), camera_ptr->Distance ), FX_CosIdx( camera_ptr->Angle.x ) );
	camera_ptr->lookat.target.y = -FX_Mul( FX_SinIdx( angle_x ), camera_ptr->Distance );
	VEC_Add(&camera_ptr->lookat.target,&camera_ptr->lookat.camPos,&camera_ptr->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ初期化共通処理
 * 
 * @param	inPerspway	パース
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void InitCameraCommon(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr){
	//視野角セット
	camera_ptr->PerspWay = inPerspWay;
	camera_ptr->persp.fovySin  = FX_SinIdx( inPerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( inPerspWay );
	//アスペクト比セット
	camera_ptr->persp.aspect   = FX32_ONE * 4 / 3;
	//ニア・ファークリップをセット
	camera_ptr->persp.nearClip = FX32_ONE * 150;
	camera_ptr->persp.farClip  = FX32_ONE * 900;

	//カメラの上方向を設定
	camera_ptr->lookat.camUp.x =  0;
	camera_ptr->lookat.camUp.y =  FX32_ONE;
	camera_ptr->lookat.camUp.z =  0;

	//カメラが捕らえる対象物の座標へのポインタを初期化
	camera_ptr->BindTarget = NULL;
	
	camera_ptr->XBind = FALSE;
	camera_ptr->YBind = FALSE;
	camera_ptr->ZBind = FALSE;

	camera_ptr->Trace = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	バインド調整
 * 
 * @param	inCamera	カメラポインタ
 * @param	outVec		バインド差分
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void FixBindValid(GF_CAMERA_CONST_PTR inCamera, VecFx32 *outVec)
{
	if (inCamera->XBind == FALSE){
		outVec->x = 0;
	}
	if (inCamera->YBind == FALSE){
		outVec->y = 0;
	}
	if (inCamera->ZBind == FALSE){
		outVec->z = 0;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	トレースデータの更新
 * 
 * @param	camera_ptr	カメラポインタ
 * @param	inVec		バッファに格納する座標
 * @param	outVec		適用座標
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void UpdateTraceData(GF_CAMERA_CONST_PTR camera_ptr, const VecFx32 *inVec, VecFx32 *outVec)
{
	int *cam;
	int *target;
	if (camera_ptr->Trace==NULL){
		(*outVec) = (*inVec);
	}else{
		cam = &camera_ptr->Trace->CamPoint;
		target = &camera_ptr->Trace->TargetPoint;
		if (!camera_ptr->Trace->UpdateFlg){
			(*outVec) = (*inVec);
			if (*cam==camera_ptr->Trace->Delay){
				camera_ptr->Trace->UpdateFlg = TRUE;
			}
		}else{
			//履歴データから座標取得
			(*outVec) = camera_ptr->Trace->HistPos[(*cam)];
		}
		//参照位置更新
		(*cam) = ((*cam)+1)%camera_ptr->Trace->HistNum;
		//履歴に積む
		camera_ptr->Trace->HistPos[(*target)] = (*inVec);
		//書き換え位置更新
		(*target) = ((*target)+1)%camera_ptr->Trace->HistNum;
		
		//トレースデータの無効座標軸は、そのまま現在座標を採用
		if (!camera_ptr->Trace->ValidX){	//ｘ無効判定
			outVec->x = inVec->x;
		}
		if (!camera_ptr->Trace->ValidY){	//ｙ無効判定
			outVec->y = inVec->y;
		}
		if (!camera_ptr->Trace->ValidZ){	//ｚ無効判定
			outVec->z = inVec->z;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	トレース構造体のアロケーション　カメラが対象物にバインド済みであること
 * 
 * @param	inHistNum		バッファサイズ
 * @param	inDelay			遅延度合い
 * @param	inTraceMask		トレースマスク	camera.hに定義
 * @param	inHeapID		ヒープID
 * @param	ioCamera		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AllocTraceData(const int inHistNum, const int inDelay,
						const int inTraceMask, const int inHeapID,
						GF_CAMERA_PTR ioCamera)
{
	int i;
	GF_CAMERA_TRACE *trace;
	//バインドされていなければ、処理しない
	if (ioCamera->BindTarget == NULL){
		return;
	}
	//配列サイズの整合性チェック
	GF_ASSERT((inDelay+1<=inHistNum)&&"配列数が足りません");
	
	trace = sys_AllocMemory(inHeapID,sizeof(GF_CAMERA_TRACE));
	trace->HistPos = sys_AllocMemory(inHeapID,sizeof(VecFx32)*inHistNum);
	
	//トレース配列クリア
	for(i=0;i<inHistNum;i++){
		trace->HistPos[i].x = 0;
		trace->HistPos[i].y = 0;
		trace->HistPos[i].z = 0;
	}
	
	trace->HistNum = inHistNum;
	//０番目にカメラ参照位置をセット
	trace->CamPoint = 0;
	//対象物参照位置セット
	trace->TargetPoint = 0+inDelay;
	
	trace->Delay = inDelay;
	trace->UpdateFlg = FALSE;
	
	trace->ValidX = FALSE;
	trace->ValidY = FALSE;
	trace->ValidZ = FALSE;
	if (inTraceMask & CAM_TRACE_MASK_X){
		trace->ValidX = TRUE;
	}
	if (inTraceMask & CAM_TRACE_MASK_Y){
		trace->ValidY = TRUE;
	}
	if (inTraceMask & CAM_TRACE_MASK_Z){
		trace->ValidZ = TRUE;
	}
	
	ioCamera->Trace = trace;
}

//---------------------------------------------------------------------------
/**
 * @brief	トレースデータの解放
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_FreeTraceData(GF_CAMERA_PTR camera_ptr)
{
	if (camera_ptr->Trace!=NULL){
		sys_FreeMemoryEz(camera_ptr->Trace->HistPos);
		sys_FreeMemoryEz(camera_ptr->Trace);
		camera_ptr->Trace = NULL;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ作成
 * 
 * @param	inHeapID		ヒープID
 * 
 * @return	GF_CAMERA_PTR	カメラポインタ
 */
//---------------------------------------------------------------------------
GF_CAMERA_PTR GFC_AllocCamera(const int inHeapID)
{
	GF_CAMERA_PTR camera_ptr;
	camera_ptr = sys_AllocMemory(inHeapID,sizeof(GF_CAMERA));
	return camera_ptr;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ解放
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_FreeCamera(GF_CAMERA_PTR camera_ptr)
{
	//カメラ本体の解放
	sys_FreeMemoryEz( camera_ptr );
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラコピー
 * 
 * @param	inCamera		コピー元カメラポインタ
 * @param	outCamera		コピー先カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CopyCamera(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera)
{
	*outCamera = (*inCamera);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラトレースデータのポインタコピー
 * 
 * @param	inCamera		コピー元カメラポインタ
 * @param	outCamera		コピー先カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CopyCameraTracePtr(GF_CAMERA_CONST_PTR inCamera, GF_CAMERA_PTR outCamera)
{
	outCamera->Trace = inCamera->Trace;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラのアタッチ(カメラの有効化)
 * 
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AttachCamera(GF_CAMERA_PTR camera_ptr)
{
	GF_Camera = camera_ptr;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラにNULLをセット（アタッチ解除）
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_PurgeCamera(void)
{
	GF_Camera = NULL;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ反映関数（描画時に呼ぶ）
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_CameraLookAt(void)
{
	if (GF_Camera == NULL){
		return;
	}
	
	//カメラが何かをバインドしているなら優先的にその座標を捕らえる
	if (GF_Camera->BindTarget != NULL){
		//移動差分を計算
		VecFx32 vec;
		VecFx32 dst_vec;
		VEC_Subtract(GF_Camera->BindTarget,&GF_Camera->BindTargetOld,&vec);

		FixBindValid(GF_Camera,&vec);
		UpdateTraceData(GF_Camera, &vec, &dst_vec);
		
		GFC_ShiftCamera(&dst_vec,GF_Camera);
		GF_Camera->BindTargetOld = *GF_Camera->BindTarget;
	}
	NNS_G3dGlbLookAt(&GF_Camera->lookat.camPos, &GF_Camera->lookat.camUp, &GF_Camera->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラの上方向を設定
 * 
 * @param	inCamUp		カメラ上方向定義ベクトル
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCamUp(const VecFx32 *inCamUp,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.camUp = *inCamUp;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラがバインドする対象物をセット
 * 
 * @param	inTarget	バインド対象座標
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_BindCameraTarget(const VecFx32 *inTarget, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->BindTarget = inTarget;
	camera_ptr->BindTargetOld = *inTarget;
	camera_ptr->XBind = TRUE;
	camera_ptr->YBind = TRUE;
	camera_ptr->ZBind = TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラがバインドしている対象物を切り離す
 * 
 * @param	camera_ptr	カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_PurgeCameraTarget(GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->BindTarget = NULL;
	camera_ptr->XBind = FALSE;
	camera_ptr->YBind = FALSE;
	camera_ptr->ZBind = FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	現在のカメラからスワップバッファモードを取得
 * 
 * @param	none
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
GXBufferMode GetBufferMode(void)
{
	if (GF_Camera!=NULL){
		if (GF_Camera->View == GF_CAMERA_PERSPECTIV){
			return GX_BUFFERMODE_W;
		}else{
			return GX_BUFFERMODE_Z;
		}
	}else{
		OS_Printf("ERROR:バッファモード取得失敗");
		return GX_BUFFERMODE_W;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラのクリップパラメータをセットする
 * 
 * @param	near			ニアクリップ値
 * @param	far				ファークリップ値
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraClip(const fx32 near,const fx32 far,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->persp.nearClip = near;
	camera_ptr->persp.farClip = far;
	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ構造体を初期化(注視点、距離、アングルを使って初期化)
 * 
 * @param	inTarget		対象注視点
 * @param	inDistance		注視点までの距離
 * @param	inAngle			アングル
 * @param	inPerspWay		パース
 * @param	inView			射影モード
 * @param	inBindFlg		注視点とのバインド有無
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraTDA
( const VecFx32* inTarget,
  const fx32 inDistance,
  const CAMERA_ANGLE *inAngle,
  const u16 inPerspWay,
  const u8 inView,
  const BOOL inBindFlg,
  GF_CAMERA_PTR camera_ptr
)
{
	// カメラの設定
	InitCameraCommon(inPerspWay,camera_ptr);
	
	//注視点をセット
	camera_ptr->lookat.target = *inTarget;
	
	//注視点からのカメラ位置の距離を設定
	camera_ptr->Distance = inDistance;

	//アングルセット
	camera_ptr->Angle = *inAngle;

	// カメラの座標をセット
	SetCamPosByTarget_Dist_Ang(camera_ptr);

	//射影セット
	GFC_SetCameraView(inView,camera_ptr);

	if (inBindFlg){
		//カメラの捕らえる対象物をバインド
		camera_ptr->BindTarget = inTarget;
		camera_ptr->BindTargetOld = *inTarget;
		camera_ptr->XBind = TRUE;
		camera_ptr->YBind = TRUE;
		camera_ptr->ZBind = TRUE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ構造体を初期化(カメラ位置、距離、アングルを使って初期化)
 * 
 * @param	inCamPos		カメラ位置
 * @param	inDistance		注視点までの距離
 * @param	inAngle			アングル
 * @param	inPerspWay		パース
 * @param	inView			射影モード
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraCDA
( const VecFx32* inCamPos,
  const fx32 inDistance,
  const CAMERA_ANGLE *inAngle,
  const u16 inPerspWay,
  const u8 inView,
  GF_CAMERA_PTR camera_ptr
)
{
	// カメラの設定
	InitCameraCommon(inPerspWay,camera_ptr);

	//カメラの座標をセット
	camera_ptr->lookat.camPos = *inCamPos;
	
	//カメラ位置から注視点までの距離を設定
	camera_ptr->Distance = inDistance;

	//アングルセット
	camera_ptr->Angle = *inAngle;

	// 注視点の座標をセット
	SetTargetByCamPos_Dist_Ang(camera_ptr);

	//射影セット
	GFC_SetCameraView(inView,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ構造体を初期化(注視点、カメラ位置を使って初期化　Z軸回転未対応)
 * 
 * @param	inTarget		対象注視点
 * @param	inCamPos		カメラ位置
 * @param	inPerspWay		パース
 * @param	inView			射影モード
 * @param	inBindFlg		注視点とのバインド有無
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_InitCameraTC
( const VecFx32* inTarget,
  const VecFx32* inCamPos,
  const u16 inPerspWay,
  const u8 inView,
  const BOOL inBindFlg,
  GF_CAMERA_PTR camera_ptr
)
{
	VecFx32 dst;
	// カメラの設定
	InitCameraCommon(inPerspWay,camera_ptr);
	
	//注視点をセット
	camera_ptr->lookat.target = *inTarget;

	//カメラの座標をセット
	camera_ptr->lookat.camPos = *inCamPos;
	
	//注視点からのカメラ位置の距離を設定
	VEC_Subtract(inCamPos, inTarget , &dst);
	camera_ptr->Distance = VEC_Mag(&dst); 

	//アングルセット
	{
		VecFx32 x_vec = {0,0,0};
		VecFx32 y_vec = {0,0,0};
		VecFx32 vec = {0,0,0};
		VecFx32 base_vec;
		base_vec.x = 0;
		base_vec.y = 0;
		base_vec.z = FX32_ONE;
		vec = dst;
		vec.y = 0;
		camera_ptr->Angle.y = GetRad(&base_vec, &vec );
		
		base_vec.x = FX32_ONE;
		base_vec.y = 0;
		base_vec.z = 0;
		vec.x = dst.z;
		vec.z = dst.y;
		vec.y = 0;
		camera_ptr->Angle.x = GetRad(&base_vec, &vec );

		camera_ptr->Angle.z = 0;

		OS_Printf("ANGGLE_%x,%x,%x\n",camera_ptr->Angle.x,camera_ptr->Angle.y,camera_ptr->Angle.z);
	}
	
	//射影セット
	GFC_SetCameraView(inView,camera_ptr);

	if (inBindFlg){
		//カメラの捕らえる対象物をバインド
		camera_ptr->BindTarget = inTarget;
		camera_ptr->BindTargetOld = *inTarget;
		camera_ptr->XBind = TRUE;
		camera_ptr->YBind = TRUE;
		camera_ptr->ZBind = TRUE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	射影セット
 * 
 * @param	inView			射影モード
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraView(const u8 inView,GF_CAMERA_PTR camera_ptr)
{
	// 射影チェック
	if( inView == GF_CAMERA_PERSPECTIV )
	{
		// 透視射影
		NNS_G3dGlbPerspective
			(camera_ptr->persp.fovySin, camera_ptr->persp.fovyCos,
			 camera_ptr->persp.aspect, camera_ptr->persp.nearClip,
			 camera_ptr->persp.farClip);
		camera_ptr->View = GF_CAMERA_PERSPECTIV;
		SwapBuffMode = GX_BUFFERMODE_Z;//GX_BUFFERMODE_W;
	}
	else	//(inVew == SIMPLE_ORTHO)
	{
		fx32	height, width;			// 高さと幅

		//-------- 正射影 --------
		// 透視射影の設定から正射影をセット
		// 高さを求める
		height = FX_Mul(FX_Div(camera_ptr->persp.fovySin, camera_ptr->persp.fovyCos), camera_ptr->Distance);
		// 幅を求める
		width  = FX_Mul(height, camera_ptr->persp.aspect );

		NNS_G3dGlbOrtho(
			height,
			-height,
			-width,
			width,
			camera_ptr->persp.nearClip,
			camera_ptr->persp.farClip
		);
		camera_ptr->View = GF_CAMERA_ORTHO;
		SwapBuffMode = GX_BUFFERMODE_Z;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	視野角のセット
 * 
 * @param	inPerspWay		パース
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->PerspWay = inPerspWay;

	/*== 射影の角度をセット ==*/
	camera_ptr->persp.fovySin  = FX_SinIdx( camera_ptr->PerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( camera_ptr->PerspWay );

	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	視野角の加算
 * 
 * @param	inPerspWay		加算パース
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraPerspWay(const u16 inPerspWay,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->PerspWay += inPerspWay;

	/*== 射影の角度をセット ==*/
	camera_ptr->persp.fovySin  = FX_SinIdx( camera_ptr->PerspWay );
	camera_ptr->persp.fovyCos  = FX_CosIdx( camera_ptr->PerspWay );

	GFC_SetCameraView(camera_ptr->View,camera_ptr);
}
#if 0
//カメラ位置のセット
void SetCameraPos(const VecFx32* inCamPos)
{
	camera_ptr->lookat.camPos = *inCamPos;
}

//注視点のセット
void SetCameraTarget(const VecFx32* inTarget)
{
	camera_ptr->lookat.target = *inTarget;
}

//注視点を移動
void MoveTarget(const VecFx32 *inMoveVec)
{
	VEC_Add(&camera_ptr->lookat.target,&inMoveVec,&Gf_Camera.lookat.target);
}

//カメラ位置を移動
void MoveCameraPos(const VecFx32 *inMoveVec)
{
	VEC_Add(&camera_ptr->lookat.camPos,&inMoveVec,&camera_ptr->lookat.camPos);
}
#endif

//---------------------------------------------------------------------------
/**
 * @brief	カメラと注視点を同時に平行移動
 * 
 * @param	inMoveVec		移動値
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_ShiftCamera(const VecFx32 *inMoveVec,GF_CAMERA_PTR camera_ptr)
{
	//カメラ動作設定
	VEC_Add(&camera_ptr->lookat.camPos,inMoveVec,&camera_ptr->lookat.camPos);
	VEC_Add(&camera_ptr->lookat.target,inMoveVec,&camera_ptr->lookat.target);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラアングルセット	自転
 * 
 * @param	inAngle			アングル
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle = *inAngle;
	SetTargetByCamPos_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラアングルセット	公転
 * 
 * @param	inAngle			アングル
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle = *inAngle;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラアングル加算	自転
 * 
 * @param	inAngle			加算アングル
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraAngleRot(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle.x += inAngle->x;
	camera_ptr->Angle.y += inAngle->y;
	camera_ptr->Angle.z += inAngle->z;
	SetTargetByCamPos_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラアングル加算	公転
 * 
 * @param	inAngle			加算アングル
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraAngleRev(const CAMERA_ANGLE *inAngle,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Angle.x += inAngle->x;
	camera_ptr->Angle.y += inAngle->y;
	camera_ptr->Angle.z += inAngle->z;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ距離セット
 * 
 * @param	inDist			距離
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_SetCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Distance = inDist;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	注視点の再設定(カメラの位置も動く)
 * 
 * @param	inTargetVec			注視点
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_ReSetCameraTarget(const VecFx32 *inTargetVec,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.target = (*inTargetVec);
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ距離加算
 * 
 * @param	inDist			加算距離ル
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GFC_AddCameraDistance(const fx32 inDist,GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->Distance += inDist;
	SetCamPosByTarget_Dist_Ang(camera_ptr);
}

//////////////////////////////////
//取得関数(まだ全部作ってません)//
//////////////////////////////////

//---------------------------------------------------------------------------
/**
 * @brief	射影取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	u8				射影モード
 */
//---------------------------------------------------------------------------
u8 GFC_GetCameraView(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->View;
}

//---------------------------------------------------------------------------
/**
 * @brief	視野角の取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	u16				パース
 */
//---------------------------------------------------------------------------
u16 GFC_GetCameraPerspWay(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->PerspWay;
}

//---------------------------------------------------------------------------
/**
 * @brief	距離の取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	fx32			距離
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraDistance(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->Distance;
}

//---------------------------------------------------------------------------
/**
 * @brief	アングル取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	CAMERA_ANGLE	アングル
 */
//---------------------------------------------------------------------------
CAMERA_ANGLE GFC_GetCameraAngle(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->Angle;
}

//---------------------------------------------------------------------------
/**
 * @brief	注視点の取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	VecFx32			注視点
 */
//---------------------------------------------------------------------------
VecFx32 GFC_GetLookTarget(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->lookat.target;
}

//---------------------------------------------------------------------------
/**
 * @brief	カメラ位置の取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	VecFx32			カメラ位置
 */
//---------------------------------------------------------------------------
VecFx32 GFC_GetCameraPos(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->lookat.camPos;
}

//---------------------------------------------------------------------------
/**
 * @brief	ファー取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	VecFx32			ファー
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraFar(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->persp.farClip;
}

//---------------------------------------------------------------------------
/**
 * @brief	ニア取得
 * 
 * @param	camera_ptr		カメラポインタ
 * 
 * @return	VecFx32			ニア
 */
//---------------------------------------------------------------------------
fx32 GFC_GetCameraNear(GF_CAMERA_CONST_PTR camera_ptr)
{
	return camera_ptr->persp.nearClip;
}

//注視点の設定
void GFC_SetLookTarget(const VecFx32* t_pos, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.target = *t_pos;
}

//カメラ位置の設定
void GFC_SetCameraPos(const VecFx32* c_pos, GF_CAMERA_PTR camera_ptr)
{
	camera_ptr->lookat.camPos = *c_pos;
}
