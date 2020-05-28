//******************************************************************************
/**
 * 
 * @file	fldeff_shadow.c
 * @brief	フィールドOBJ影
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "..\..\include\system\timezone.h"
#include "..\..\include\system\pm_rtc.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_SHADOW_WRITE_OFF	//定義で影描画OFF
#define DEBUG_SHADOW_TIME

//#define SHADOW_DRAW_Z_OFFSET (FX32_ONE*(3))
//#define SHADOW_DRAW_Z_OFFSET (FX32_ONE*(5))			///<影描画オフセットZ軸
#define SHADOW_DRAW_Z_OFFSET (FX32_ONE*(3))				

#define SHADOW_SCALE_SPEED (0x0010)
#define SHADOW_ALPHA_SPEED (0x0200)

/*
#define	TIMEZONE_MORNING	(0)
#define	TIMEZONE_NOON		(1)
#define	TIMEZONE_EVENING	(2)
#define TIMEZONE_NIGHT		(3)
#define TIMEZONE_MIDNIGHT	(4)
*/

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_SHADOW型
//--------------------------------------------------------------
typedef struct _TAG_FE_SHADOW * FE_SHADOW_PTR;

//--------------------------------------------------------------
///	FE_SHADOW構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_SHADOW
{
	int time_seq_no;
	int time_zone;
	int next_time_zone;
	int frame;
	fx32 alpha;
	VecFx32 scale;
	
	FE_SYS *fes;
	TCB_PTR tcb_time_proc;
	NNSG3dRenderObj render;
	NNSG3dRenderObj render_red;
	NNSG3dRenderObj render_blue;
	NNSG3dResMdl *model;
	NNSG3dResMdl *model_red;
	NNSG3dResMdl *model_blue;
	NNSG3dResFileHeader *res_file;
	NNSG3dResFileHeader *res_file_red;
	NNSG3dResFileHeader *res_file_blue;
}FE_SHADOW;

#define FE_SHADOW_SIZE (sizeof(FE_SHADOW)) ///<FE_SHADOWサイズ

//--------------------------------------------------------------
///	SHADOW_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;								///<FE_SYS *
	FE_SHADOW_PTR shadow;						///<FE_SHADOW_PTR
	FIELD_OBJ_PTR fldobj;						///<影の対象FIELD_OBJ_PTR
}SHADOW_ADD_H;

#define SHADOW_ADD_H_SIZE (sizeof(SHADOW_ADD_H)) ///<SHADOW_ADD_Hサイズ

//--------------------------------------------------------------
///	SHADOW_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int obj_code;								///<影対象OBJコード
	int obj_id;									///<影対象OBJID
	int zone_id;								///<影対象ゾーンID
	int vanish_sw;								///<非表示SW
	int type;									///<SHADOW_BLACK等
	SHADOW_ADD_H head;							///<追加時のSHADOW_ADD_H
}SHADOW_WORK;

#define SHADOW_WORK_SIZE (sizeof(SHADOW_WORK))	///<SHADOW_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Shadow_TimeProcAdd( FE_SHADOW_PTR sd );
static void Shadow_TimeProcDelete( FE_SHADOW_PTR sd );
static void Shadow_TimeScaleGet( FE_SHADOW_PTR sd, VecFx32 *scale );
static int Shadow_TimeAlpha031( int alpha );
static void Shadow_TimeAlphaScaleSet( FE_SHADOW_PTR sd, int zone );
static void Shadow_ValueAdd( fx32 *val0, fx32 val1, fx32 add );
static void Shadow_TimeProc( TCB_PTR tcb, void *wk );

static void Shadow_GraphicInit( FE_SHADOW_PTR sd );
static void Shadow_GraphicDelete( FE_SHADOW_PTR sd );
static void Shadow_GraphicAlphaSet( FE_SHADOW_PTR sd, int alpha );

static const EOA_H_NPP DATA_EoaH_Shadow;
static const EOA_H_NPP DATA_EoaH_ShadowType;

const VecFx32 DATA_ShadowTimeScaleTbl[];
const fx32 DATA_ShadowTimeAlphaTbl[];

//==============================================================================
//	影　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * 影初期化
 * @param	fes		FE_SYS *
 * @retval	void*	エフェクト使用ワーク
 */
//--------------------------------------------------------------
void * FE_Shadow_Init( FE_SYS *fes )
{
	FE_SHADOW_PTR sd;
	
	sd = FE_AllocClearMemory( fes, FE_SHADOW_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Shadow_GraphicInit( sd );
	Shadow_TimeProcAdd( sd );
	
	return( sd );
}

//--------------------------------------------------------------
/**
 * 影削除
 * @param	work	エフェクト使用ワーク
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Shadow_Delete( void *work )
{
	FE_SHADOW_PTR sd = work;
	Shadow_TimeProcDelete( sd );
	Shadow_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	影　時間帯による拡縮、濃度処理
//==============================================================================
//--------------------------------------------------------------
/**
 * 影時間帯処理を追加
 * @param	sd		FE_SHADOW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_TimeProcAdd( FE_SHADOW_PTR sd )
{
	FIELDSYS_WORK *fsys = FE_FieldSysWorkGet( sd->fes );
	int pri = FieldOBJSys_TCBStandardPriorityGet( fsys->fldobjsys ) - 1; //FieldOBJよりも早く
	TCB_PTR tcb = TCB_Add( Shadow_TimeProc, sd, pri );
	sd->tcb_time_proc = tcb;
}

//--------------------------------------------------------------
/**
 * 影時間帯処理を削除
 * @param	sd		FE_SHADOW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_TimeProcDelete( FE_SHADOW_PTR sd )
{
	TCB_Delete( sd->tcb_time_proc );
}

//--------------------------------------------------------------
/**
 * 影時間帯から拡縮率を取得
 * @param	sd		FE_SHADOW_PTR
 * @param	scale	拡縮率格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_TimeScaleGet( FE_SHADOW_PTR sd, VecFx32 *scale )
{
	*scale = sd->scale;
}

//--------------------------------------------------------------
/**
 * 影時間帯別の濃度を0-31で取得
 * @param	alpha	fx32単位の濃度
 * @retval	int		0-31
 */
//--------------------------------------------------------------
static int Shadow_TimeAlpha031( int alpha )
{
	return( (alpha/FX32_ONE) );
}

//--------------------------------------------------------------
/**
 * 影時間帯別の濃度、拡縮率セット
 * @param	sd		FE_SHADOW_PTR
 * @param	zone TIMEZONE_MORNING等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_TimeAlphaScaleSet( FE_SHADOW_PTR sd, int zone )
{
	sd->alpha = DATA_ShadowTimeAlphaTbl[sd->time_zone];
	sd->scale = DATA_ShadowTimeScaleTbl[sd->time_zone];
}

//--------------------------------------------------------------
/**
 * 対象の増減
 * @param	val0	対象
 * @param	val1	目標
 * @param	add		増減値
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_ValueAdd( fx32 *val0, fx32 val1, fx32 add )
{
	if( (*val0) < val1 ){
		(*val0) += add;
		if( (*val0) > val1 ){ (*val0) = val1; }
	}else if( (*val0) > val1 ){
		(*val0) -= add;
		if( (*val0) < val1 ){ (*val0) = val1; }
	}
}

//--------------------------------------------------------------
/**
 * 影時間帯処理
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_TimeProc( TCB_PTR tcb, void *wk )
{
	int now_zone;
	FE_SHADOW_PTR sd = wk;
	
	now_zone = GF_RTC_GetTimeZone();
	
	switch( sd->time_seq_no ){
	case 0:													//初期化
		sd->time_zone = now_zone;
		Shadow_TimeAlphaScaleSet( sd, sd->time_zone );
		Shadow_GraphicAlphaSet( sd, Shadow_TimeAlpha031(sd->alpha) );
		sd->time_seq_no++;
		break;
	case 1:
		if( sd->time_zone == now_zone ){
			break;
		}
		
		sd->time_seq_no++;
	case 2:
		{
			fx32 next_alpha = DATA_ShadowTimeAlphaTbl[now_zone];
			VecFx32 next_scale = DATA_ShadowTimeScaleTbl[now_zone];
			
			Shadow_ValueAdd( &sd->scale.x, next_scale.x, SHADOW_SCALE_SPEED );
			Shadow_ValueAdd( &sd->scale.y, next_scale.y, SHADOW_SCALE_SPEED );
			Shadow_ValueAdd( &sd->scale.z, next_scale.z, SHADOW_SCALE_SPEED );
			Shadow_ValueAdd( &sd->alpha, next_alpha, SHADOW_ALPHA_SPEED );
			Shadow_GraphicAlphaSet( sd, Shadow_TimeAlpha031(sd->alpha) );
			
			if( next_scale.x == sd->scale.x &&
				next_scale.y == sd->scale.y &&
				next_scale.z == sd->scale.z &&
				next_alpha == sd->alpha ){
				sd->time_zone = now_zone;
				sd->time_seq_no = 1;
			}
		}
		
		break;
	}
}

//==============================================================================
//	影	パーツ
//==============================================================================

//==============================================================================
//	影　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * 影 グラフィック初期化
 * @param	sd	FE_SHADOW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_GraphicInit( FE_SHADOW_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_kage_nsbmd, ALLOC_FR,
			&sd->render, &sd->model, &sd->res_file );
	FE_simple3DModelInit( sd->fes, NARC_fldeff_red_mark_nsbmd, ALLOC_FR,
			&sd->render_red, &sd->model_red, &sd->res_file_red );
	FE_simple3DModelInit( sd->fes, NARC_fldeff_blue_mark_nsbmd, ALLOC_FR,
			&sd->render_blue, &sd->model_blue, &sd->res_file_blue );
}

//--------------------------------------------------------------
/**
 * 影 グラフィック削除
 * @param	sd	FE_SHADOW_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_GraphicDelete( FE_SHADOW_PTR sd )
{
	FE_FreeMemory( sd->res_file );
	FE_FreeMemory( sd->res_file_red );
	FE_FreeMemory( sd->res_file_blue );
}

//--------------------------------------------------------------
/**
 * 影に濃度をセット
 * @param	sd		FE_SHADOW_PTR
 * @param	alpha	半透明濃度0-31
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Shadow_GraphicAlphaSet( FE_SHADOW_PTR sd, int alpha )
{
	NNS_G3dMdlUseMdlAlpha( sd->model );
	NNS_G3dMdlSetMdlAlphaAll( sd->model, alpha );
}

//==============================================================================
//	影　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ用影追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJShadow_Add( FIELD_OBJ_PTR fldobj )
{
	int param,pri;
	SHADOW_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fes = fes;
	head.shadow = FE_EffectWorkGet( fes, FE_FLD_SHADOW );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	
	param = SHADOW_BLACK;
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_EoaAddNpp( fes, &DATA_EoaH_Shadow, &mtx, param, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA 影　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaShadow_Init( EOA_PTR eoa, void *wk )
{
	SHADOW_WORK *work;
	const SHADOW_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->type = EOA_AddParamGet( eoa );
	work->obj_code = FieldOBJ_OBJCodeGet( work->head.fldobj );
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	
	if( FieldOBJ_StatusBitCheck_Alies(work->head.fldobj) == TRUE ){
		work->zone_id = FieldOBJ_ZoneIDGetAlies( work->head.fldobj );
	}else{
		work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 影　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaShadow_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 影　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaShadow_Move( EOA_PTR eoa, void *wk )
{
	SHADOW_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );										//同一ではない
		return;
	}
	
	if( FieldOBJ_FieldOBJSysStatusBitCheck(fldobj,FLDOBJSYS_STA_BIT_SHADOW_JOIN_NOT) ){
		FE_EoaDelete( eoa );
		return;
	}
	
	work->vanish_sw = FALSE;
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,
		FLDOBJ_STA_BIT_VANISH|FLDOBJ_STA_BIT_SHADOW_VANISH) == TRUE ){
		work->vanish_sw = TRUE;									//非表示
		return;
	}
	
	{
		VecFx32 vec;
		
		FieldOBJ_VecPosGet( fldobj, &vec );
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 影　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaShadow_Draw( EOA_PTR eoa, void *wk )
{
	SHADOW_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec,scale;
		MtxFx33 rot = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		Shadow_TimeScaleGet( work->head.shadow, &scale );
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += -(FX32_ONE * 1) / 2;
		vec.y += -(FX32_ONE * 4);
		vec.z += (FX32_ONE * 1);
		
		simple_3DModelDraw( &work->head.shadow->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	影EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Shadow =
{
	SHADOW_WORK_SIZE,
	EoaShadow_Init,
	EoaShadow_Delete,
	EoaShadow_Move,
	EoaShadow_Draw,
};

//==============================================================================
//	赤影、黒影
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJに影を付ける
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	type	SHADOW_BLACK等
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJShadowSet( FIELD_OBJ_PTR fldobj, int type )
{
	int pri;
	SHADOW_ADD_H head;
	FE_SYS * fes;
	VecFx32 mtx;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fes = fes;
	head.shadow = FE_EffectWorkGet( fes, FE_FLD_SHADOW );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	return( FE_EoaAddNpp(fes,&DATA_EoaH_ShadowType,&mtx,type,&head,pri) );
}

//--------------------------------------------------------------
/**
 * EOA 赤影黒影　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaShadowType_Move( EOA_PTR eoa, void *wk )
{
	SHADOW_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );										//同一ではない
		return;
	}
	
	work->vanish_sw = FALSE;
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,
		FLDOBJ_STA_BIT_VANISH|FLDOBJ_STA_BIT_SHADOW_VANISH) == TRUE ){
		work->vanish_sw = TRUE;									//非表示
		return;
	}
	
	{
		VecFx32 vec;
		FieldOBJ_VecPosGet( fldobj, &vec );
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA 影　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaShadowType_Draw( EOA_PTR eoa, void *wk )
{
	SHADOW_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += -(FX32_ONE * 1) / 2;
		vec.y += -(FX32_ONE * 4);
		vec.z += (FX32_ONE * 1);
		
		switch( work->type ){
		case SHADOW_BLACK:
			simple_3DModelDraw( &work->head.shadow->render, &vec, &rot, &scale );
			break;
		case SHADOW_RED:
			simple_3DModelDraw( &work->head.shadow->render_red, &vec, &rot, &scale );
			break;
		case SHADOW_BLUE:
			simple_3DModelDraw( &work->head.shadow->render_blue, &vec, &rot, &scale );
			break;
		}
	}
}

//--------------------------------------------------------------
///	影タイプEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_ShadowType =
{
	SHADOW_WORK_SIZE,
	EoaShadow_Init,
	EoaShadow_Delete,
	EoaShadowType_Move,
	EoaShadowType_Draw,
};

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	時間帯別拡大率
//--------------------------------------------------------------
static const VecFx32 DATA_ShadowTimeScaleTbl[] =
{
	{ FX32_ONE, FX32_ONE, FX32_ONE },	//TIMEZONE_MORNING
	{ FX32_ONE+(FX32_ONE/4), FX32_ONE, FX32_ONE+(FX32_ONE/4)},	//TIMEZONE_NOON
	{ FX32_ONE+(FX32_ONE/4), FX32_ONE, FX32_ONE },	//TIMEZONE_EVENING
	{ FX32_ONE+(FX32_ONE/8), FX32_ONE, FX32_ONE },	//TIMEZONE_NIGHT
	{ FX32_ONE-(FX32_ONE/8), FX32_ONE, FX32_ONE-(FX32_ONE/8) },	//TIMEZONE_MIDNIGHT
};

//--------------------------------------------------------------
///	時間帯別半透明濃度
//--------------------------------------------------------------
static const fx32 DATA_ShadowTimeAlphaTbl[] =
{
	FX32_ONE*14, //TIMEZONE_MORNING
	FX32_ONE*18,	//TIMEZONE_NOON
	FX32_ONE*18,	//TIMEZONE_EVENING
	FX32_ONE*8,	//TIMEZONE_NIGHT
	FX32_ONE*4,	//TIMEZONE_MIDNIGHT
};

