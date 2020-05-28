//============================================================================================
/**
 * @file	field_camera.c
 * @bfief	フィールドカメラ
 * @author	GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "camera.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "worldmap.h"
#include "fieldsys.h"

#include "field_camera.h"

#define FIELD_CAMERA_DELAY	(6)
#define FIELD_CAMERA_TRACE_BUFF	(FIELD_CAMERA_DELAY+1)

typedef	struct	{
	fx32			Distance;
	CAMERA_ANGLE	Angle;
	u8				View;
	u16				PerspWay;
	fx32			Near;
	fx32			Far;
}FLD_CAMERA_PARAM;

static const FLD_CAMERA_PARAM FieldCameraData[] = {
	{							//	0	通常
		0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	1	水ジム
		0x29aec1,
		{
			-0x309e,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	2	最初の湖
		0x20374c,
		{
			-0x26de,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x770,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	3	鋼ジム
		0x29aec1,
		{
			-0x29fe,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
	{							//	4	屋内（正射影）
		0x61b89b,
		{
			-0x239e,0,0
		},
		GF_CAMERA_ORTHO,
		0x0281,
		FX32_ONE * 150,
		FX32_ONE * 1735
	},

	{							//	5	テンガンザン山頂
		0x13c805,
		{
			-0x29fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0c01,
		FX32_ONE * 10,
		FX32_ONE * 1008
	},

	{							//	6	テンガンザン外回り1
		0x3628df,
		{
			-0x33fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0481,
		FX32_ONE * 115,
		FX32_ONE * 1221
	},

	{							//	7	テンガンザン外回り2
		0x29aec1,
		{
			-0x29fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 153,
		FX32_ONE * 1031
	},

	{							//	8	火山奥
		0x296ec1,
		{
			-0x321d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0701,
		FX32_ONE * 150,
		FX32_ONE * 1034
	},

	{							//	9	岩ジム
		0x1659ac,
		{
			-0x1cdd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0ab0,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	10	格闘ジム
		0x4b25b1,
		{
			-0x2b3d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0341,
		FX32_ONE * 150,
		FX32_ONE * 1746
	},

	{							//	11	ナギサシティ/223番水道/チャンピオンリーグ
		0x2a3d55,
		{
			-0x291d,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x05c1,
		FX32_ONE * 230,
		FX32_ONE * 1127
	},

	{							//	12	洞窟
		0x23e93f,
		{
			-0x2cfd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x06c1,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	13	鉱山
		0x20374c,
		{
			-0x21fd,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x0770,
		FX32_ONE * 150,
		FX32_ONE * 900
	},

	{							//	14	はじまりのま
		0xa9765,
		{
			-0x37bc,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x1501,
		FX32_ONE * 10,
		FX32_ONE * 1008
	},

	{							//	15	エイチ湖専用カメラ
		0x28dedf,
		{
			-0x26de,0,0
		},
		GF_CAMERA_PERSPECTIV,
		0x5f0,
		FX32_ONE * 150,
		FX32_ONE * 900
	},
};



//==============================================================================
/**
 * フィールド上で行うカメラ設定
 *
 * @param   Hero			主にエリア切り替え時に対応したカメラが設定される
 * @param	repw			フィールドシステムポインタ
 * @param   AreaCamera		主にエリア切り替え時に対応したカメラが設定される
 * @param	inDelayFlg		ｙ軸遅延を行うかどうかのフラグ
 *
 * @retval  none		
 */
//==============================================================================
void FieldCameraInit(	const VecFx32 *inTarget,
						FIELDSYS_WORK * repw,
						const int AreaCamera,
						const BOOL inDelayFlg)
{

	//カメラセット
	const VecFx32 *target = inTarget;
	const FLD_CAMERA_PARAM * camera_param = &FieldCameraData[AreaCamera];

	GF_ASSERT(AreaCamera < NELEMS(FieldCameraData));

	repw->camera_ptr = GFC_AllocCamera(HEAPID_FIELD);//フィールドカメラメモリ確保
	
	//カメラセット
	GFC_InitCameraTDA( target,
				camera_param->Distance,	// 距離
				&camera_param->Angle,	//
				camera_param->PerspWay,	// 投射影の角度
				camera_param->View,
				TRUE,
				repw->camera_ptr
				);
	//カメラの有効化
	GFC_AttachCamera(repw->camera_ptr);
	//ニア・ファー設定
	GFC_SetCameraClip(camera_param->Near, camera_param->Far,repw->camera_ptr);
	
	if (inDelayFlg){
		//カメラトレースデータセットアップ
		GFC_AllocTraceData(	FIELD_CAMERA_TRACE_BUFF, FIELD_CAMERA_DELAY,
							CAM_TRACE_MASK_Y, HEAPID_FIELD, repw->camera_ptr);
	}
}

//==============================================================================
/**
 * フィールド上カメラの解放
 *
 * @param   repw		フィールドシステムポインタ
 *
 * @retval  none		
 */
//==============================================================================
void FieldCameraEnd(FIELDSYS_WORK * repw)
{
	GFC_PurgeCamera();						//カメラの切り離し（無効化）
		
	GFC_FreeTraceData(repw->camera_ptr);	//カメラトレースデータ解放
	GFC_FreeCamera(repw->camera_ptr);		//フィールドカメラメモリ解放
}
