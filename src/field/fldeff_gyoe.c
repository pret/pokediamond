//******************************************************************************
/**
 * 
 * @file	fldeff_gyoe.c
 * @brief	フィールドOBJぎょえー
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_gyoe.h"

#include "..\system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
#define GYOE_FLDOBJ_Y_OFFSET ((FX32_ONE*32))				///<フィールドOBJからのYオフセット
#define GYOE_FLDOBJ_Z_OFFSET ((FX32_ONE*1))					///<フィールドOBJからのZオフセット
#define GYOE_FLDOBJ_Y_MOVE_START ((FX32_ONE*6))				///<ギョエー初速

#define GYOE_END_FRAME (30)									///<ギョエー終了フレーム	

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_GYOE型
//--------------------------------------------------------------
typedef struct _TAG_FE_GYOE * FE_GYOE_PTR;

//--------------------------------------------------------------
///	FE_GYOE構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_GYOE
{
	int add_count_gyoe;
	int add_count_saisen;
	int draw_init_gyoe;
	int draw_init_saisen;
	FE_SYS *fes;
}FE_GYOE;

#define FE_GYOE_SIZE (sizeof(FE_GYOE)) ///<FE_GYOEサイズ

//--------------------------------------------------------------
///	GYOE_ADD_H構造体
//--------------------------------------------------------------
typedef struct
{
	GYOE_TYPE type;								///<GYOE_TYPE
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_GYOE_PTR gyoe;							///<FE_GYOE_PTR
	FIELD_OBJ_PTR fldobj;						///<ぎょえーの対象FIELD_OBJ_PTR
}GYOE_ADD_H;

#define GYOE_ADD_H_SIZE (sizeof(GYOE_ADD_H)) ///<GYOE_ADD_Hサイズ

//--------------------------------------------------------------
///	GYOE_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<動作番号
	int frame;									///<フレーム
	int obj_id;									///<ぎょえー対象OBJID
	int zone_id;								///<ぎょえー対象ゾーンID
	int vanish_sw;								///<非表示SW
	int end_sw;									///<終了SW
	VecFx32 offset;								///<オフセット
	VecFx32 move;								///<移動量
	GYOE_ADD_H head;							///<追加時のGYOE_ADD_H
	BLACT_WORK_PTR act;							///<ビルボードアクター
}GYOE_WORK;

#define GYOE_WORK_SIZE (sizeof(GYOE_WORK))	///<GYOE_WORKサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void Gyoe_AddCountUp( FE_GYOE_PTR gyoe );
static void Gyoe_AddCountDown( FE_GYOE_PTR gyoe );
static void Saisen_AddCountUp( FE_GYOE_PTR gyoe );
static void Saisen_AddCountDown( FE_GYOE_PTR gyoe );
static void GyoeType_AddCountUp( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static void GyoeType_AddCountDown( FE_GYOE_PTR gyoe, GYOE_TYPE type );

static void Gyoe_GraphicInit( FE_GYOE_PTR gyoe );
static void Saisen_GraphicInit( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicDelete( FE_GYOE_PTR gyoe );
static void Saisen_GraphicDelete( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicCheckInit( FE_GYOE_PTR gyoe );
static void Saisen_GraphicCheckInit( FE_GYOE_PTR gyoe );
static void Gyoe_GraphicCheckDelete( FE_GYOE_PTR gyoe );
static void Saisen_GraphicCheckDelete( FE_GYOE_PTR gyoe );
static void GyoeType_GraphicInit( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static void GyoeType_GraphicDelete( FE_GYOE_PTR gyoe, GYOE_TYPE type );
static BLACT_WORK_PTR GyoeType_BlActAdd( FE_SYS *fes, GYOE_TYPE type, VecFx32 *vec );

static const EOA_H_NPP DATA_EoaH_Gyoe;
static const EOA_H_NPP DATA_EoaH_FldOBJGyoe;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_Gyoe[];

//==============================================================================
//	ぎょえー　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * ぎょえー初期化
 * @param	fes		FE_SYS_PTR
 * @retval	FE_GYOE_PTR	FE_GYOE_PTR
 */
//--------------------------------------------------------------
void * FE_Gyoe_Init( FE_SYS *fes )
{
	FE_GYOE_PTR gyoe;
	
	gyoe = FE_AllocClearMemory( fes, FE_GYOE_SIZE, ALLOC_FR, 0 );
	gyoe->fes = fes;
	
	return( gyoe );
}

//--------------------------------------------------------------
/**
 * ぎょえー削除
 * @param	gyoe		FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Gyoe_Delete( void *work )
{
	FE_GYOE_PTR gyoe = work;
	Gyoe_GraphicDelete( gyoe );
	FE_FreeMemory( gyoe );
}

//==============================================================================
//	ぎょえー	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * ギョエー数カウント
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_AddCountUp( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_gyoe++;
}

//--------------------------------------------------------------
/**
 * ギョエー数デクリメント
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_AddCountDown( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_gyoe--;
	
	GF_ASSERT( gyoe->add_count_gyoe >= 0 &&
		"Gyoe_AddCountDown()　ギョエーの追加と削除の回数が合わない" );
}

//--------------------------------------------------------------
/**
 * 再戦ぎょえー数カウント
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_AddCountUp( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_saisen++;
}

//--------------------------------------------------------------
/**
 * 再戦ぎょえー数デクリメント
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_AddCountDown( FE_GYOE_PTR gyoe )
{
	gyoe->add_count_saisen--;
	
	GF_ASSERT( gyoe->add_count_saisen >= 0 &&
		"Gyoe_AddCountDown()　再戦ギョエーの追加と削除の回数が合わない" );
}

//--------------------------------------------------------------
/**
 * ギョエータイプ　カウント 
 * @param	gyoe	FE_GYOE_TYPE
 * @param	type	GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_AddCountUp( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_AddCountUp( gyoe );
	}else{
		Saisen_AddCountUp( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ギョエータイプ　デクリメント
 * @param	gyoe	FE_GYOE_TYPE
 * @param	type	GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_AddCountDown( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_AddCountDown( gyoe );
	}else{
		Saisen_AddCountDown( gyoe );
	}
}

//==============================================================================
//	ぎょえー　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * ぎょえー グラフィック初期化
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_gyoe == FALSE ){
		gyoe->draw_init_gyoe = TRUE;
		FE_BlActResAdd_MdlArc( gyoe->fes, FE_RESID_MDL_GYOE, NARC_fldeff_sisen_ef_nsbmd );
		FE_BlActResAdd_AnmArc( gyoe->fes, FE_RESID_ANM_GYOE, NARC_fldeff_kusaeff_itpcv_dat );
		FE_BlActResAdd_TexArc( gyoe->fes,
			FE_RESID_TEX_GYOE, NARC_fldeff_sisen_ef_nsbtx, TEXRESM_TEX_CUT_TRUE );
		
		FE_BlActHeaderManageAddResmID( gyoe->fes, FE_BLACT_H_ID_GYOE,
			FE_RESID_MDL_GYOE, FE_RESID_ANM_GYOE,
			FE_RESID_TEX_GYOE, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Gyoe );
	}
}

//--------------------------------------------------------------
/**
 * 再戦ギョエー グラフィック初期化
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_saisen == FALSE ){
		gyoe->draw_init_saisen = TRUE;
		FE_BlActResAdd_MdlArc( gyoe->fes,
			FE_RESID_MDL_GYOE_SAISEN, NARC_fldeff_saisen_ef_nsbmd );
		FE_BlActResAdd_AnmArc( gyoe->fes,
			FE_RESID_ANM_GYOE_SAISEN, NARC_fldeff_kusaeff_itpcv_dat );
		FE_BlActResAdd_TexArc( gyoe->fes,
			FE_RESID_TEX_GYOE_SAISEN, NARC_fldeff_saisen_ef_nsbtx, TEXRESM_TEX_CUT_TRUE );
		
		FE_BlActHeaderManageAddResmID( gyoe->fes, FE_BLACT_H_ID_GYOE_SAISEN,
			FE_RESID_MDL_GYOE_SAISEN, FE_RESID_ANM_GYOE_SAISEN,
			FE_RESID_TEX_GYOE_SAISEN, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ぎょえー グラフィック削除
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_gyoe == TRUE ){
		gyoe->draw_init_gyoe = FALSE;
		
		FE_BlActResDelete_Mdl( gyoe->fes, FE_RESID_MDL_GYOE );
		FE_BlActResDelete_Anm( gyoe->fes, FE_RESID_ANM_GYOE );
		FE_BlActResDelete_Tex( gyoe->fes, FE_RESID_TEX_GYOE );
		FE_BlActHeaderManageFree( gyoe->fes, FE_BLACT_H_ID_GYOE );
	}
}

//--------------------------------------------------------------
/**
 * 再戦ギョエー グラフィック削除
 * @param	gyoe	FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->draw_init_saisen == TRUE ){
		gyoe->draw_init_saisen = FALSE;
		
		FE_BlActResDelete_Mdl( gyoe->fes, FE_RESID_MDL_GYOE_SAISEN );
		FE_BlActResDelete_Anm( gyoe->fes, FE_RESID_ANM_GYOE_SAISEN );
		FE_BlActResDelete_Tex( gyoe->fes, FE_RESID_TEX_GYOE_SAISEN );
		FE_BlActHeaderManageFree( gyoe->fes, FE_BLACT_H_ID_GYOE_SAISEN );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック初期化
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicCheckInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_gyoe == 0 ){
		Gyoe_GraphicInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック初期化　再戦ギョエー
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicCheckInit( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_saisen == 0 ){
		Saisen_GraphicInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック削除
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Gyoe_GraphicCheckDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_gyoe == 0 ){
		Gyoe_GraphicDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * 判定つきグラフィック削除　再戦ギョエー
 * @param	gyoe FE_GYOE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Saisen_GraphicCheckDelete( FE_GYOE_PTR gyoe )
{
	if( gyoe->add_count_saisen == 0 ){
		Saisen_GraphicDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * グラフィック初期化　種類
 * @param	FE_GYOE_PTR gyoe
 * @param	type GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_GraphicInit( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_GraphicCheckInit( gyoe );
	}else{
		Saisen_GraphicCheckInit( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * グラフィック削除　種類
 * @param	FE_GYOE_PTR gyoe
 * @param	type GYOE_TYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
static void GyoeType_GraphicDelete( FE_GYOE_PTR gyoe, GYOE_TYPE type )
{
	if( type == GYOE_GYOE ){
		Gyoe_GraphicCheckDelete( gyoe );
	}else{
		Saisen_GraphicCheckDelete( gyoe );
	}
}

//--------------------------------------------------------------
/**
 * ギョエー　ビルボード追加
 * @param	fes			FE_SYS_PTR
 * @param	type		GYOE_TYPE
 * @param	vec			座標
 * @retval	BLACT_WORK_PTR	BLACT_WORK_PTR
 */
//--------------------------------------------------------------
static BLACT_WORK_PTR GyoeType_BlActAdd( FE_SYS *fes, GYOE_TYPE type, VecFx32 *vec )
{
	int id[2] = { FE_BLACT_H_ID_GYOE, FE_BLACT_H_ID_GYOE_SAISEN };
	BLACT_WORK_PTR act = FE_BlActAddID( fes, id[type], vec );
	return( act );
}

//==============================================================================
//	ぎょえー　EOA　フィールドOBJ用
//==============================================================================
//--------------------------------------------------------------
/**
 * ぎょえー追加
 * @param	fes			FE_SYS *
 * @param	mtx			表示位置
 * @param	se_play		TRUE=SE再生
 * @retval	EOA_PTR		追加EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Gyoe_Add( FE_SYS *fes, const VecFx32 *mtx, int se_play )
{
	int pri;
	GYOE_ADD_H head;
	EOA_PTR eoa;
	
	head.type = GYOE_GYOE;
	head.fes = fes;
	head.gyoe = FE_EffectWorkGet( fes, FE_FLD_GYOE );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Gyoe, mtx, se_play, &head, 0xff );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * ぎょえー終了チェック
 * @param	eoa		ギョエーEOA
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
int FE_Gyoe_EndCheck( EOA_PTR eoa )
{
	GYOE_WORK *work;
	
	work = EOA_LocalWorkGet( eoa );
	return( work->end_sw );
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaGyoe_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	const GYOE_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->move.y = GYOE_FLDOBJ_Y_MOVE_START;
	
	GyoeType_GraphicInit( work->head.gyoe, work->head.type );			//グラフィック初期化
	
	EOA_MatrixGet( eoa, &vec );
	work->act = GyoeType_BlActAdd( work->head.fes, work->head.type, &vec );
	GyoeType_AddCountUp( work->head.gyoe, work->head.type );			//カウントアップ
	
	if( EOA_AddParamGet(eoa) == TRUE ){
		Snd_SePlay( SE_MARK_GYOE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work = wk;
	
	EOA_MatrixGet( eoa, &vec );
	
	switch( work->seq_no ){
	case 0:
		work->offset.y += work->move.y;
		
		if( work->offset.y ){
			work->move.y -= FX32_ONE * 2;
		}else{
			work->move.y = 0;
			work->seq_no++;
		}
		
		break;
	case 1:		
		work->frame++;
		
		if( work->frame >= GYOE_END_FRAME ){
			work->seq_no++;
			work->frame = 0;
			work->end_sw = TRUE;
		}
		
		break;
	case 2:
		break;
	}
	
	EOA_MatrixSet( eoa, &vec );
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Delete( EOA_PTR eoa, void *wk )
{
	GYOE_WORK *work;
	
	work = wk;
	
	BLACT_Delete( work->act );									//アクター削除
	GyoeType_AddCountDown( work->head.gyoe, work->head.type );	//カウントダウン
	GyoeType_GraphicDelete( work->head.gyoe, work->head.type );	//グラフィック削除
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoe_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	
	vec.x += work->offset.x;
	vec.y += work->offset.y;
	vec.z += work->offset.z;
	
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	ぎょえー　EOA　フィールドOBJ用
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ用ぎょえー追加
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	se_play		TRUE=SE再生
 * @retval	EOA_PTR		追加EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJGyoe_Add( FIELD_OBJ_PTR fldobj, GYOE_TYPE type, int se_play )
{
	int pri;
	GYOE_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.type = type;
	head.fes = fes;
	head.gyoe = FE_EffectWorkGet( fes, FE_FLD_GYOE );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBStandardPriorityGet( fldobj ) + 1;	//フィールドOBJよりも処理を後に
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_FldOBJGyoe, &mtx, se_play, &head, pri );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　初期化　フィールドOBJ用
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=正常終了。FALSE=異常終了
 */
//--------------------------------------------------------------
static int EoaGyoeFldOBJ_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GYOE_WORK *work;
	const GYOE_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->move.y = GYOE_FLDOBJ_Y_MOVE_START;
		
	GyoeType_GraphicInit( work->head.gyoe, work->head.type );	//グラフィック初期化
	
	EOA_MatrixGet( eoa, &vec );
	work->act = GyoeType_BlActAdd( work->head.fes, work->head.type, &vec );
	
	GyoeType_AddCountUp( work->head.gyoe, work->head.type );	//カウントアップ
	
	if( EOA_AddParamGet(eoa) == TRUE ){
		Snd_SePlay( SE_MARK_GYOE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ぎょえー　動作　フィールドOBJ用
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGyoeFldOBJ_Move( EOA_PTR eoa, void *wk )
{
	GYOE_WORK *work;
	FIELD_OBJ_PTR fldobj;
	VecFx32 vec;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	GF_ASSERT( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) != FALSE &&
		"ギョエー動作中に対象のフィールドOBJが削除されました" );
	
	FieldOBJ_DrawVecPosTotalGet( fldobj, &vec );
	vec.y += GYOE_FLDOBJ_Y_OFFSET;
	vec.z += GYOE_FLDOBJ_Z_OFFSET;
	
	switch( work->seq_no ){
	case 0:
		work->offset.y += work->move.y;
		
		if( work->offset.y ){
			work->move.y -= FX32_ONE * 2;
		}else{
			work->move.y = 0;
			work->seq_no++;
		}
		
		break;
	case 1:		
		work->frame++;
		
		if( work->frame >= GYOE_END_FRAME ){
			work->seq_no++;
			work->frame = 0;
			work->end_sw = TRUE;
		}
		
		break;
	case 2:
		break;
	}
	
	EOA_MatrixSet( eoa, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	ぎょえーEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Gyoe =
{
	GYOE_WORK_SIZE,
	EoaGyoe_Init,
	EoaGyoe_Delete,
	EoaGyoe_Move,
	EoaGyoe_Draw,
};

//--------------------------------------------------------------
///	ぎょえーEOA_H　フィールドOBJ用
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_FldOBJGyoe =
{
	GYOE_WORK_SIZE,
	EoaGyoeFldOBJ_Init,
	EoaGyoe_Delete,
	EoaGyoeFldOBJ_Move,
	EoaGyoe_Draw,
};

//--------------------------------------------------------------
///	ギョエーアニメ
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_Gyoe[] =
{
	{ 0, 1, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
