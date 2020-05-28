//============================================================================================
/**
 * @file	demo_trade_3d.c
 * @brief	ポケモン交換デモ（3Dオブジェクト描画）
 * @author	taya
 * @date	2006.04.13
 */
//============================================================================================
#include "demo_trade_common.h"
#include "demo_trade_3d.h"
#include "gflib\simple_3dgraphics.h"
#include "gflib\bounding_box.h"


//-------------------------------------------------
/**
 *	3Dオブジェクト
 */
//-------------------------------------------------
struct _DT3DOBJ{
	void*		modelLoadPtr;

	NNSG3dRenderObj		renderObj;
	NNSG3dResMdlSet*	modelSet;
	NNSG3dResMdl*		model;
	NNSG3dResTex*		texture;

	BOOL		drawFlag;
	VecFx32		pos;
	VecFx32		scale;
	VecFx16		rot;

	int			alpha;

};

//-------------------------------------------------
/**
 *	3Dオブジェクト管理ワーク
 */
//-------------------------------------------------
struct _DT3DMAN {

	GF_CAMERA_PTR	camera;
	VecFx32			cameraTarget;
	CAMERA_ANGLE	cameraAngle;

	DT3DOBJ*		obj;
	u32				objMax;
};

//==============================================================
// Prototype
//==============================================================
static void inline make_rot_matrix( MtxFx33* rotMtx, const VecFx16* rot );
static void rend_obj( DT3DOBJ* obj );
static void init_obj_work( DT3DOBJ* obj );
static void quit_obj_work( DT3DOBJ* obj );
static void setup_camera_work( DT3DMAN* wk, fx32 targetX, fx32 targetY, fx32 targetZ );
static void cleanup_camera_work( DT3DMAN* wk );



//------------------------------------------------------------------
/**
 * 
 *
 * @param   objMax		
 *
 * @retval  DT3DMAN*		
 */
//------------------------------------------------------------------
DT3DMAN* DT3DMAN_Create( u32 objMax, fx32 targetX, fx32 targetY, fx32 targetZ )
{
	DT3DMAN* man = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(DT3DMAN) );
	if( man )
	{
		u32 i;

		setup_camera_work( man, targetX, targetY, targetZ );

		man->obj = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(DT3DOBJ)*objMax );
		man->objMax = objMax;
		for(i=0; i<objMax; i++)
		{
			init_obj_work( &man->obj[i] );
		}
	}
	return man;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void DT3DMAN_Delete( DT3DMAN* wk )
{
	int i;

	for(i=0; i<wk->objMax; i++)
	{
		quit_obj_work( &(wk->obj[i]) );
	}
	sys_FreeMemoryEz( wk->obj );
	cleanup_camera_work( wk );

	sys_FreeMemoryEz( wk );
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void DT3DMAN_Draw( DT3DMAN* wk )
{
	NNS_G3dGePushMtx();
	{
		int i;

		// カメラ設定
		GFC_CameraLookAt();

		for(i=0; i<wk->objMax; i++)
		{
			if( wk->obj[i].drawFlag )
			{
				rend_obj( &(wk->obj[i]) );
			}
		}

	}
	NNS_G3dGePopMtx(1);

}
static void inline make_rot_matrix( MtxFx33* rotMtx, const VecFx16* rot )
{
	MtxFx33 tmpMtx;

	// 回転行列作成
	MTX_Identity33( rotMtx );
	MTX_RotX33( &tmpMtx, FX_SinIdx((u16)(rot->x)), FX_CosIdx((u16)(rot->x)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
	MTX_RotY33( &tmpMtx, FX_SinIdx((u16)(rot->y)), FX_CosIdx((u16)(rot->y)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
	MTX_RotZ33( &tmpMtx, FX_SinIdx((u16)(rot->z)), FX_CosIdx((u16)(rot->z)) );
	MTX_Concat33( &tmpMtx, rotMtx, rotMtx );
}


static void rend_obj( DT3DOBJ* obj )
{
	MtxFx33 rotMtx;

	make_rot_matrix( &rotMtx, &(obj->rot) );

	if( obj->alpha != DT3D_ALPHA_MAX )
	{
		NNS_G3dGlbPolygonAttr( 0, 0, 0, 0, obj->alpha, 0 );
	}

	simple_3DModelDraw( &obj->renderObj, &obj->pos, &rotMtx, &obj->scale );

}









//------------------------------------------------------------------
/**
 * オブジェクト領域初期化
 *
 * @param   obj		
 *
 */
//------------------------------------------------------------------
static void init_obj_work( DT3DOBJ* obj )
{
	obj->drawFlag = FALSE;
	obj->modelLoadPtr = NULL;

	obj->rot.x = obj->rot.y = obj->rot.z = 0;
	obj->scale.x = obj->scale.y = obj->scale.z = FX32_ONE;
	obj->pos.x = obj->pos.y = obj->pos.z = 0;

}
//------------------------------------------------------------------
/**
 * オブジェクト領域クリア
 *
 * @param   obj		
 *
 */
//------------------------------------------------------------------
static void quit_obj_work( DT3DOBJ* obj )
{
	if( obj->modelLoadPtr )
	{
		sys_FreeMemoryEz( obj->modelLoadPtr );
		obj->modelLoadPtr = NULL;
		obj->drawFlag = FALSE;
	}
}


//------------------------------------------------------------------
/**
 * オブジェクト追加
 *
 * @param   man		
 * @param   id		
 * @param   arcID		
 * @param   datID		
 * @param   xpos		
 * @param   ypos		
 * @param   zpos		
 *
 */
//------------------------------------------------------------------
DT3DOBJ* DT3D_AddObj( DT3DMAN* man, int id, u32 arcID, u32 datID, fx32 xpos, fx32 ypos, fx32 zpos, BOOL drawFlag )
{
	DT3DOBJ* obj = &man->obj[id];

	obj->modelLoadPtr = ArcUtil_Load( arcID, datID, FALSE, HEAPID_DEMO_TRADE_SUB, ALLOC_BOTTOM );
	DC_FlushRange( obj->modelLoadPtr, ArchiveDataSizeGet( arcID, datID ) );

	if( obj->modelLoadPtr )
	{
		obj->modelSet	= NNS_G3dGetMdlSet( obj->modelLoadPtr );
		obj->model		= NNS_G3dGetMdlByIdx( obj->modelSet, 0 );
		obj->texture	= NNS_G3dGetTex( obj->modelLoadPtr );

		LoadVRAMTexture( obj->texture );
		BindTexture( obj->modelLoadPtr, obj->texture );

		NNS_G3dRenderObjInit( &obj->renderObj, obj->model );

		obj->pos.x = xpos;
		obj->pos.y = ypos;
		obj->pos.z = zpos;

		obj->alpha = DT3D_ALPHA_MAX;

		obj->drawFlag = drawFlag;
	}

	return obj;
}

//------------------------------------------------------------------
/**
 * オブジェクト破棄
 *
 * @param   obj		
 *
 */
//------------------------------------------------------------------
void DT3D_DeleteObj( DT3DOBJ* obj )
{
	quit_obj_work( obj );
}


void DT3D_GetObjPos( const DT3DOBJ* obj, VecFx32* dst )
{
	*dst = obj->pos;
}

void DT3D_SetObjPos( DT3DOBJ* obj, const VecFx32* pos )
{
	obj->pos = *pos;
}

void DT3D_GetObjRot( const DT3DOBJ* obj, VecFx16* dst )
{
	*dst = obj->rot;
}

void DT3D_SetObjRot( DT3DOBJ* obj, const VecFx16* rot )
{
	obj->rot = *rot;
}

void DT3D_SetObjDrawFlag( DT3DOBJ* obj, BOOL flag )
{
	obj->drawFlag = flag;
}

void DT3D_SetObjAlpha( DT3DOBJ* obj, int alpha )
{
	obj->alpha = alpha;

	if( alpha != DT3D_ALPHA_MAX )
	{
		NNS_G3dMdlUseGlbAlpha( obj->model );
	}
	else
	{
		NNS_G3dMdlUseMdlAlpha( obj->model );
	}
}

void DT3D_SetObjScale( DT3DOBJ* obj, fx32 scale )
{
	obj->scale.x = scale;
	obj->scale.y = scale;
	obj->scale.z = scale;
}

BOOL DT3D_CheckObjVisible( DT3DOBJ* obj )
{
	MtxFx33  rotMtx;
	BOOL ret;

	make_rot_matrix(&rotMtx, &(obj->rot));

	NNS_G3dGePushMtx();
	// カメラ設定
	GFC_CameraLookAt();
	ret = BB_CullingCheck3DModel( obj->model, &obj->pos, &rotMtx, &obj->scale );
	NNS_G3dGePopMtx(1);

	return ret;
}

//======================================================================================

void DT3D_SetCameraPos( DT3DMAN* wk, const VecFx32* pos )
{
	GFC_SetCameraPos( pos, wk->camera );
}

void DT3D_GetCameraPos( DT3DMAN* wk, VecFx32* pos )
{
	*pos = GFC_GetCameraPos( wk->camera );
}

void DT3D_SetCameraAngleRev( DT3DMAN* wk, const CAMERA_ANGLE* angle )
{
	GFC_SetCameraAngleRev( angle, wk->camera );
}

void DT3D_GetCameraAngle( DT3DMAN* wk, CAMERA_ANGLE* angle )
{
	*angle = GFC_GetCameraAngle( wk->camera );
}
void DT3D_AddCameraAngleRot( DT3DMAN* wk, const CAMERA_ANGLE* angle )
{
	GFC_AddCameraAngleRot( angle, wk->camera );
}

void DT3D_SetCameraDistance( DT3DMAN* wk, fx32 distance )
{
	GFC_SetCameraDistance( distance, wk->camera );
}


void DT3D_SetCameraView( DT3DMAN* wk, u8 view )
{
	GFC_SetCameraView( view, wk->camera );
}

void DT3D_SetCameraParse( DT3DMAN* wk, u16 parse )
{
	GFC_SetCameraPerspWay( parse, wk->camera );
}

//======================================================================================


static void setup_camera_work( DT3DMAN* wk, fx32 targetX, fx32 targetY, fx32 targetZ )
{
	enum {
		CAMERA_PEARCE	= FX_GET_ROTA_NUM(22),
		CAMERA_DISTANCE	= (300 << FX32_SHIFT)
	};

	CAMERA_ANGLE angle;
	VecFx32 up;

	wk->camera = GFC_AllocCamera( HEAPID_DEMO_TRADE_SUB );

	wk->cameraTarget.x = targetX;
	wk->cameraTarget.y = targetY;
	wk->cameraTarget.z = targetZ;

	wk->cameraAngle.x = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.y = FX_GET_ROTA_NUM(0);
	wk->cameraAngle.z = FX_GET_ROTA_NUM(0);

	GFC_InitCameraTDA( 
			&(wk->cameraTarget),
			CAMERA_DISTANCE,
			&(wk->cameraAngle),
			CAMERA_PEARCE,
			GF_CAMERA_PERSPECTIV,
			TRUE,	
			wk->camera
	);


	up.x = 0;
	up.y = FX32_ONE;
	up.z = 0;
	GFC_SetCamUp( &up, wk->camera );

	GFC_AttachCamera( wk->camera );

	GFC_SetCameraClip( (0<<FX32_SHIFT), (1000<<FX32_SHIFT), wk->camera );
}

static void cleanup_camera_work( DT3DMAN* wk )
{
	GFC_FreeCamera( wk->camera );
}



