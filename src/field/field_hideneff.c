//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hideneff.c
 *	@file		field_hideneff.h
 *	@brief		フィールド秘伝技エフェクト
 *	@data		2006.06.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "field_3dobj.h"
#include "hiden_effect.naix"

#include "src/fielddata/eventdata/zone_d01r0102evc.h"

#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/snd_tool.h"

#include "system/arc_util.h"

#define __FIELD_HIDENEFF_H_GLOBAL
#include "field_hideneff.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------

#define FHE_TASK_PRI	( 1024 )	// 動さタスク優先順位

//----------------------------------------------------------------------------
/**
 *	@brief	OBJIDのオブジェクトの向いている方向に設定
 */
//-----------------------------------------------------------------------------
static void FHE_objDirGridMatSet( FIELD_OBJ_SYS_PTR fldobjsys, u32 objID, FLD_3DOBJ* p_obj )
{
	int dir;	// 方向
	int grid_x, grid_z;
	VecFx32 pos;
	FIELD_OBJ_PTR p_fldobj;

	p_fldobj = FieldOBJSys_OBJIDSearch( fldobjsys, objID );

	// 取り合えず自機の位置に出す
	FieldOBJ_VecPosGet( p_fldobj, &pos );
	grid_x = FieldOBJ_NowPosGX_Get( p_fldobj );
	grid_z = FieldOBJ_NowPosGZ_Get( p_fldobj );
	dir = FieldOBJ_DirDispGet( p_fldobj );
	switch( dir ){
	case DIR_UP:
		grid_z--;
		break;
	case DIR_DOWN:
		grid_z++;
		break;
	case DIR_LEFT:
		grid_x --;
		break;
	case DIR_RIGHT:
		grid_x ++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, pos.y, GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	自機の向いているほうの位置を設定
 *
 *	@param	jiki	自機ポインタ
 *	@param	p_obj	描画オブジェクト
 */
//-----------------------------------------------------------------------------
static void FHE_playerDirGridMatSet( const PLAYER_STATE_PTR jiki, FLD_3DOBJ* p_obj )
{
	int dir;	// 方向
	int grid_x, grid_z;
	VecFx32 pos;

	// 取り合えず自機の位置に出す
	Player_VecPosGet( jiki, &pos );
	grid_x = Player_NowGPosXGet( jiki );
	grid_z = Player_NowGPosZGet( jiki );
	dir = Player_DirGet( jiki );
	switch( dir ){
	case DIR_UP:
		grid_z--;
		break;
	case DIR_DOWN:
		grid_z++;
		break;
	case DIR_LEFT:
		grid_x --;
		break;
	case DIR_RIGHT:
		grid_x ++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, pos.y, GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );

}


//----------------------------------------------------------------------------
/**
 *	@brief	自機の１つ前の座標を設定する
 *
 *	@param	jiki	自機
 *	@param	p_obj	オブジェクト
 */
//-----------------------------------------------------------------------------
static void FHE_playerVecMatSet( const PLAYER_STATE_PTR jiki, FLD_3DOBJ* p_obj )
{
/*	int grid_x, grid_z, grid_y;

	grid_y = FieldOBJ_OldPosGY_Get(Player_FieldOBJGet(jiki));
	grid_x = Player_OldGPosXGet( jiki );
	grid_z = Player_OldGPosZGet( jiki );
	FLD_3DObjSetMatrix( p_obj, GRID_SIZE_FX32(grid_x)+GRID_HALF_FX32, 
			GRID_SIZE_FX32(grid_y)+GRID_HALF_FX32, 
			GRID_SIZE_FX32(grid_z)+GRID_HALF_FX32 );//*/

	VecFx32 pos;

	// 取り合えず自機の位置に出す
	Player_VecPosGet( jiki, &pos );
	FLD_3DObjSetMatrix( p_obj, pos.x, pos.y, pos.z );
}


//-------------------------------------
// コモン共通ワーク
//=====================================
#define FHE_COMMON_ANM_NUM	( 4 )
typedef struct {
	FLD_3DOBJ		obj;
	FLD_3DOBJ_MDL	mdl;
	FLD_3DOBJ_ANM	anm[FHE_COMMON_ANM_NUM];
	u32				anm_num;
} FHE_COMMON_OBJ;

//----------------------------------------------------------------------------
/**
 *	@brief	共通オブジェ初期化
 *
 *	@param	p_obj		オブジェクト
 *	@param	mdl_idx		モデルIDX
 *	@param	anm_idx		アニメIDX	+ アニメ数までのアニメを読み込む
 *	@param	anm_num		アニメ数
 *	@param	p_allocator	アロケータ
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObjInit( FHE_COMMON_OBJ* p_obj, u32 mdl_idx, u32 anm_idx, int anm_num, NNSFndAllocator* p_allocator )
{
	int i;

	memset( p_obj, 0, sizeof(FHE_COMMON_OBJ) );

	// モデル読み込み
	FLD_3DObjMdlLoad( &p_obj->mdl, ARC_HIDEN_EFFECT, mdl_idx, HEAPID_FIELD );
	FLD_3DObjInit( &p_obj->obj, &p_obj->mdl );

	p_obj->anm_num = anm_num;

	// アニメ読み込み
	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmLoad( &p_obj->anm[i], &p_obj->mdl, ARC_HIDEN_EFFECT, anm_idx + i, HEAPID_FIELD, p_allocator );
		FLD_3DObjAddAnm( &p_obj->obj, &p_obj->anm[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	共通オブジェクトの破棄
 *	
 *	@param	p_obj		共通オブジェクト
 *	@param	p_allocator	アロケータ
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObjDelete( FHE_COMMON_OBJ* p_obj, NNSFndAllocator* p_allocator )
{
	int i;

	// モデル破棄
	FLD_3DObjMdlDelete( &p_obj->mdl );

	// アニメ破棄
	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmDelete( &p_obj->anm[i], p_allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ノーループアニメ
 *
 *	@param	p_obj	オブジェ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL Fhe_CommonObj_NoLoopAnime( FHE_COMMON_OBJ* p_obj )
{
	int i;
	BOOL check;

	check = TRUE;
	for( i=0; i<p_obj->anm_num; i++ ){
		check &= FLD_3DObjAnmNoLoop( &p_obj->anm[i], FX32_ONE );
	}
	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループアニメ
 *
 *	@param	p_obj	オブジェ
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObj_LoopAnime( FHE_COMMON_OBJ* p_obj )
{
	int i;

	for( i=0; i<p_obj->anm_num; i++ ){
		FLD_3DObjAnmLoop( &p_obj->anm[i], FX32_ONE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	共通オブジェ描画処理
 *
 *	@param	p_obj	共通オブジェクト
 */
//-----------------------------------------------------------------------------
static void Fhe_CommonObj_Draw( FHE_COMMON_OBJ* p_obj )
{
	FLD_3DObjDraw( &p_obj->obj );
}



//-----------------------------------------------------------------------------
/**
 *					いあいぎり
*/
//-----------------------------------------------------------------------------
// シーケンス
enum{
	FHE_IAIGIRI_SEQ_MOVE,
	FHE_IAIGIRI_SEQ_END,
};

// いあいぎりアニメ数
enum{
	FHE_IAIGRI_ANM_ICA,
	FHE_IAIGRI_ANM_IMA,
	FHE_IAIGRI_ANM_ITA,
	FHE_IAIGRI_ANM_NUM,
};
//-------------------------------------
//	いあいぎり
//=====================================
typedef struct {
	FHE_COMMON_OBJ obj;

	// アロケータ
	NNSFndAllocator allocator;

	u32 seq;	// シーケンス
} FLD_HIDENEFF_IAIGIRI;


//-----------------------------------------------------------------------------
/**
 *					いわくだき	
*/
//-----------------------------------------------------------------------------

// シーケンス
enum{
	FHE_IWAKUDAKI_SEQ_MOVE,
	FHE_IWAKUDAKI_SEQ_END,
};


// いわくだきアニメ数
enum{
	FHE_IWAKUDAKI_ANM_IMA,
	FHE_IWAKUDAKI_ANM_ICA,
	FHE_IWAKUDAKI_ANM_ITP,
	FHE_IWAKUDAKI_ANM_ITA,
	FHE_IWAKUDAKI_ANM_NUM,
};
//-------------------------------------
//	いわくだき
//=====================================
typedef struct {
	FHE_COMMON_OBJ obj;

	// アロケータ
	NNSFndAllocator allocator;

	u32 seq;	// シーケンス
} FLD_HIDENEFF_IWAKUDAKI;


//-----------------------------------------------------------------------------
/**
 *					たきのぼり	
*/
//-----------------------------------------------------------------------------
// 滝登りシーケンス
enum{
	FHE_TAKINOBORI_SEQ_START,
	FHE_TAKINOBORI_SEQ_LOOP,
};

// たきのぼりモデル数
enum{
	FHE_TAKINOBORI_OBJ_START,
	FHE_TAKINOBORI_OBJ_LOOP,
	FHE_TAKINOBORI_OBJ_NUM,
};

// たきのぼりアニメ数
enum{
	FHE_TAKINOBORI_ANM_ICA,
	FHE_TAKINOBORI_ANM_ITP,
	FHE_TAKINOBORI_ANM_NUM,
};
//-------------------------------------
//	たきのぼり
//=====================================
typedef struct _FLD_HIDENEFF_TAKINOBORI{
	FHE_COMMON_OBJ obj[FHE_TAKINOBORI_OBJ_NUM];

	// アロケータ
	NNSFndAllocator allocator;
	
	u32 seq;	// シーケンス
} FLD_HIDENEFF_TAKINOBORI;



//-----------------------------------------------------------------------------
/**
 *					ロッククライム	
*/
//-----------------------------------------------------------------------------

// シーケンス
enum{
	FHE_ROCKCLIMB_SEQ_MOVE,
};

#define FHE_ROCKCLIMB_OBJ_NUM	( 16 )	// 表示オブジェ数

// ロッククライムアニメ数
enum{
	FHE_ROCKCLIMB_ANM_IMA,
	FHE_ROCKCLIMB_ANM_ICA,
	FHE_ROCKCLIMB_ANM_ITP,
	FHE_ROCKCLIMB_ANM_ITA,
	FHE_ROCKCLIMB_ANM_NUM,
};

//-------------------------------------
//	ロッククライムエフェクトおぶじぇ
//=====================================
typedef struct {
	FLD_3DOBJ		obj;
	FLD_3DOBJ_ANM	anm[FHE_ROCKCLIMB_ANM_NUM];
	u32 status;
}FLD_HIDENEFF_ROCKCLIMB_OBJ;
//-------------------------------------
//	ロッククライム
//=====================================
typedef struct {
	FLD_3DOBJ_MDL	mdl;
	FLD_HIDENEFF_ROCKCLIMB_OBJ obj[ FHE_ROCKCLIMB_OBJ_NUM ];
	void* p_anmbuff[FHE_ROCKCLIMB_ANM_NUM];

	FIELDSYS_WORK* p_fsys;
	int wait;
	fx32 ofs_y;
	fx32 ofs_z;
	VecFx32 pos;

	// アロケータ
	NNSFndAllocator allocator;

	u32 seq;	// シーケンス
} FLD_HIDENEFF_ROCKCLIMB;
#define FHE_ROCKCLIMB_WAIT	( 4 )
#define FHE_ROCKCLIMB_EFF_OFS_Y	(GRID_FX32 * 2)
#define FHE_ROCKCLIMB_EFF_OFS_Z	(GRID_FX32)




//-----------------------------------------------------------------------------
/**
 *					いあいぎり	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IAIGIRI) );

	// アロケータ作成
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	// 共通オブジェクト初期化処理
	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iaigiri_nsbmd,
			NARC_hiden_effect_iaigiri_nsbca, FHE_IAIGRI_ANM_NUM, &p_fhe_w->allocator );

	// 座標設定
	FHE_playerDirGridMatSet( p_fsys->player, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IAIGIRI );

	// シーケンス
	p_fhe_w->seq = FHE_IAIGIRI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;

	Fhe_CommonObjDelete( &p_fhe_w->obj, &p_fhe_w->allocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	int i;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_IAIGIRI_SEQ_MOVE:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj.obj, FALSE );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_IAIGIRI_SEQ_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iaigiri_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = p_work;
	Fhe_CommonObj_Draw( &p_fhe_w->obj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	いあいぎり　エフェクト開始
 *
 *	@param	fsys	フィールドデータ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iaigiri_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IaigiriData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IAIGIRI),
		FHE_Iaigiri_Init,
		FHE_Iaigiri_Delete,
		FHE_Iaigiri_Main,
		FHE_Iaigiri_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IaigiriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	いあいぎり　エフェクト破棄
 *
 *	@param	p_demo	デモワーク
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Iaigiri_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	いあいぎり　終了チェック
 *
 *	@param	p_demo	デモワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_HIDENEFF_Iaigiri_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLD_HIDENEFF_IAIGIRI* p_fhe_w = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_fhe_w->seq == FHE_IAIGIRI_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *					いわくだき	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IWAKUDAKI) );

	// アロケータ作成
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iwakudaki_nsbmd,
			NARC_hiden_effect_iwakudaki_nsbca, FHE_IWAKUDAKI_ANM_NUM, &p_fhe_w->allocator );

	// 座標設定
	FHE_playerDirGridMatSet( p_fsys->player, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IWAKUDAKI );

	// シーケンス
	p_fhe_w->seq = FHE_IWAKUDAKI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化処理
 *	クロガネ炭坑用
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Kurogane_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_IWAKUDAKI) );

	// アロケータ作成
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	Fhe_CommonObjInit( &p_fhe_w->obj, NARC_hiden_effect_iwakudaki_nsbmd,
			NARC_hiden_effect_iwakudaki_nsbca, FHE_IWAKUDAKI_ANM_NUM, &p_fhe_w->allocator );

	// 座標設定
	FHE_objDirGridMatSet( p_fsys->fldobjsys, D01R0102_LEADER, &p_fhe_w->obj.obj );

	Snd_SePlay( SE_IWAKUDAKI );

	// シーケンス
	p_fhe_w->seq = FHE_IWAKUDAKI_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;

	Fhe_CommonObjDelete( &p_fhe_w->obj, &p_fhe_w->allocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	int i;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_IWAKUDAKI_SEQ_MOVE:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj.obj, FALSE );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_IWAKUDAKI_SEQ_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FHE_Iwakudaki_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = p_work;
	Fhe_CommonObj_Draw( &p_fhe_w->obj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	いわくだき　エフェクト開始
 *
 *	@param	fsys	フィールドデータ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IwakudakiData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IWAKUDAKI),
		FHE_Iwakudaki_Init,
		FHE_Iwakudaki_Delete,
		FHE_Iwakudaki_Main,
		FHE_Iwakudaki_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IwakudakiData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	いわくだき　エフェクト開始	クロガネ炭坑用
 *
 *	@param	fsys	フィールドデータ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_KuroganeL_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_IwakudakiData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_IWAKUDAKI),
		FHE_Iwakudaki_Kurogane_Init,
		FHE_Iwakudaki_Delete,
		FHE_Iwakudaki_Main,
		FHE_Iwakudaki_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_IwakudakiData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	いわくだき　エフェクト破棄
 *
 *	@param	p_demo	デモワーク
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Iwakudaki_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	いわくだき　終了チェック
 *
 *	@param	p_demo	デモワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_HIDENEFF_Iwakudaki_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLD_HIDENEFF_IWAKUDAKI* p_fhe_w = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_fhe_w->seq == FHE_IWAKUDAKI_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *					たきのぼり	
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化処理
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;
	const u8 mdl_idx[ FHE_TAKINOBORI_OBJ_NUM ] = {
		NARC_hiden_effect_ride_start_nsbmd,
		NARC_hiden_effect_ride_loop_nsbmd,
	};
	const u8 anm_idx[ FHE_TAKINOBORI_OBJ_NUM ] = {
		NARC_hiden_effect_ride_start_nsbca,
		NARC_hiden_effect_ride_loop_nsbca,
	};

	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_TAKINOBORI) );

	// アロケータ作成
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObjInit( &p_fhe_w->obj[i], mdl_idx[i], anm_idx[i], FHE_TAKINOBORI_ANM_NUM, &p_fhe_w->allocator );

		// 座標設定
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[i].obj );
	}

	// ループアニメは非表示
	FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_LOOP ].obj, FALSE );

	Snd_SePlay( SE_TAKINOBORI );

	// シーケンス
	p_fhe_w->seq = FHE_TAKINOBORI_SEQ_START;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄処理
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;

	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObjDelete( &p_fhe_w->obj[i], &p_fhe_w->allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ処理
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	BOOL check;

	switch( p_fhe_w->seq ){
	case FHE_TAKINOBORI_SEQ_START:
		check = Fhe_CommonObj_NoLoopAnime( &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_START] );
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_START].obj );
		if( check == TRUE ){
			FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_LOOP ].obj, TRUE );
			FLD_3DObjSetDraw( &p_fhe_w->obj[ FHE_TAKINOBORI_OBJ_START ].obj, FALSE );

			FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP].obj );
			p_fhe_w->seq ++;
		}
		break;
		
	case FHE_TAKINOBORI_SEQ_LOOP:
		Fhe_CommonObj_LoopAnime( &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP] );
		FHE_playerVecMatSet( p_fsys->player, &p_fhe_w->obj[FHE_TAKINOBORI_OBJ_LOOP].obj );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FHE_Takinobori_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_TAKINOBORI* p_fhe_w = p_work;
	int i;
	
	for( i=0; i<FHE_TAKINOBORI_OBJ_NUM; i++ ){
		Fhe_CommonObj_Draw( &p_fhe_w->obj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	たきのぼり　エフェクト開始
 *
 *	@param	fsys	フィールドデータ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_Takinobori_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_TakinoboriData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_TAKINOBORI),
		FHE_Takinobori_Init,
		FHE_Takinobori_Delete,
		FHE_Takinobori_Main,
		FHE_Takinobori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_TakinoboriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	たきのぼり　エフェクト破棄
 *
 *	@param	p_demo	デモワーク
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_Takinobori_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}






//-----------------------------------------------------------------------------
/**
 *					ロックCLIMB
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	lockCLIMBオブジェクト動さ開始
 *
 *	@param	p_obj	オブジェ
 *	@param	jiki	ターゲット　自機オブジェクト
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjStart( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, const PLAYER_STATE_PTR jiki, fx32 ofs_y, fx32 ofs_z )
{
	VecFx32 pos;
	int i;

	GF_ASSERT( p_obj->status == 0 );
	
	// 取り合えず自機の１つ前位置に出す
	Player_VecPosGet( jiki, &pos );
	FLD_3DObjSetMatrix( &p_obj->obj, pos.x, pos.y + ofs_y, pos.z + ofs_z );
	p_obj->status = 1;

	// アニメオブジェの初期化
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmSet( &p_obj->anm[i], 0 );	
	}

	// 描画ON
	FLD_3DObjSetDraw( &p_obj->obj, TRUE );

	Snd_SePlay( SE_ROCKCLIMB );
}

//----------------------------------------------------------------------------
/**	
 *	@brief	ロッククライムエフェクトオブジェクトメイン
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjMain( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj )
{
	int i;
	BOOL result;
	
	if( p_obj->status == 0 ){
		return ;
	}
	
	result = TRUE;
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		result &= FLD_3DObjAnmNoLoop( &p_obj->anm[i], FX32_ONE );
	}
	
	if( result == TRUE ){
		p_obj->status = 0;
		// 描画OFF
		FLD_3DObjSetDraw( &p_obj->obj, FALSE );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	ロッククライムオブジェクト　初期化
 *
 *	@param	p_obj		オブジェクトワーク
 *	@param	p_mdl		モデル
 *	@param	p_allocator	アロケータ
 *	@param	pp_anmbuff	アニメバッファ
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjInit( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl, NNSFndAllocator* p_allocator, void** pp_anmbuff )
{
	int i;

	memset( p_obj, 0, sizeof( FLD_HIDENEFF_ROCKCLIMB_OBJ ) );
	
	FLD_3DObjInit( &p_obj->obj, p_mdl );
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmLoad_Data( &p_obj->anm[i], p_mdl, pp_anmbuff[i],
				p_allocator );
		FLD_3DObjAddAnm( &p_obj->obj, &p_obj->anm[i] );
	}

	FLD_3DObjSetDraw( &p_obj->obj, FALSE );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ロッククライムオブジェ破棄
 *
 *	@param	p_obj	オブジェクト
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_ObjDelete( FLD_HIDENEFF_ROCKCLIMB_OBJ* p_obj, NNSFndAllocator* p_allocator )
{
	int i;

	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		FLD_3DObjAnmDelete( &p_obj->anm[i], p_allocator );
	}
	memset( p_obj, 0, sizeof( FLD_HIDENEFF_ROCKCLIMB_OBJ ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	進んでいるほうこうから出すエフェクトの位置を設定
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_MoveOfsSet( FLD_HIDENEFF_ROCKCLIMB* p_fhe_w )
{
	VecFx32 pos;
#if 1
	Player_VecPosGet( p_fhe_w->p_fsys->player, &pos );
	// 進み先が、下手前
	if( ((pos.x - p_fhe_w->pos.x) == 0) &&
		(pos.y < p_fhe_w->pos.y) && 
		(pos.z > p_fhe_w->pos.z) ){

		p_fhe_w->ofs_y = 0;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z*2;
	}else{
		p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
	}
	p_fhe_w->pos = pos;
#endif

	
#if 0
	Player_VecPosGet( p_fhe_w->p_fsys->player, &pos );
	// 進み先が左右
	if( (pos.x - p_fhe_w->pos.x) != 0 ){
		p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
		p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;

	// 進み先が、上
	}else if( pos.y > p_fhe_w->pos.y ){

		// 手前
		if( pos.z > p_fhe_w->pos.z ){
			p_fhe_w->ofs_y = -FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = -FHE_ROCKCLIMB_EFF_OFS_Z;

		// 奥
		}else{
			p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
		}

	// 進み先が、下
	}else{

		// 手前
		if( pos.z > p_fhe_w->pos.z ){
			p_fhe_w->ofs_y = 0;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z*2;

		// 奥
		}else{
			p_fhe_w->ofs_y = FHE_ROCKCLIMB_EFF_OFS_Y;
			p_fhe_w->ofs_z = FHE_ROCKCLIMB_EFF_OFS_Z;
		}
		
	}
	p_fhe_w->pos = pos;
#endif
}



//----------------------------------------------------------------------------
/**
 *	@brief	新しいロッククライムオブジェ動さ開始
 *
 *	@param	p_fhe 
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_Set( FLD_HIDENEFF_ROCKCLIMB* p_fhe )
{
	int i;

	// 進んでいるほうこうから出すエフェクトの位置を設定
	FHE_RockClime_MoveOfsSet( p_fhe );
	
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		if( p_fhe->obj[i].status == 0 ){
			Fhe_RockClime_ObjStart( &p_fhe->obj[i], p_fhe->p_fsys->player, p_fhe->ofs_y, p_fhe->ofs_z );
			return ;
		}
	}
	// オブジェクトがたりない
	GF_ASSERT(0);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ロッククライム　オブジェメイン
 *
 *	@param	p_fhe	lockCLIMBオブジェクト
 */
//-----------------------------------------------------------------------------
static void Fhe_RockClime_Main( FLD_HIDENEFF_ROCKCLIMB* p_fhe )
{
	int i;
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjMain( &p_fhe->obj[i] );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	ワーク初期化処理
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	memset( p_fhe_w, 0, sizeof(FLD_HIDENEFF_ROCKCLIMB) );

	// アロケータ作成
	sys_InitAllocator( &p_fhe_w->allocator, HEAPID_FIELD, 32 );

	// モデル読み込み
	FLD_3DObjMdlLoad( &p_fhe_w->mdl, ARC_HIDEN_EFFECT, NARC_hiden_effect_iwakudaki_nsbmd, HEAPID_FIELD );

	// アニメ読み込み
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		p_fhe_w->p_anmbuff[i] = ArcUtil_Load( ARC_HIDEN_EFFECT, NARC_hiden_effect_iwakudaki_nsbca + i, FALSE, HEAPID_FIELD, ALLOC_TOP );
	}
	
	// ロッククライムオブジェクト生成
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjInit( &p_fhe_w->obj[i], &p_fhe_w->mdl, &p_fhe_w->allocator, p_fhe_w->p_anmbuff );
	}

	p_fhe_w->p_fsys = p_fsys;
	Player_VecPosGet( p_fhe_w->p_fsys->player, &p_fhe_w->pos );

	// シーケンス
	p_fhe_w->seq = FHE_ROCKCLIMB_SEQ_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄処理
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		Fhe_RockClime_ObjDelete( &p_fhe_w->obj[i], &p_fhe_w->allocator );
	}
	FLD_3DObjMdlDelete( &p_fhe_w->mdl );

	// アニメ破棄
	for( i=0; i<FHE_ROCKCLIMB_ANM_NUM; i++ ){
		sys_FreeMemoryEz( p_fhe_w->p_anmbuff[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ処理
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;

	switch( p_fhe_w->seq ){
	case FHE_ROCKCLIMB_SEQ_MOVE:

		p_fhe_w->wait --;
		if( p_fhe_w->wait < 0 ){
			p_fhe_w->wait = FHE_ROCKCLIMB_WAIT;
			Fhe_RockClime_Set( p_fhe_w );
		}
		
		// エフェクト動さメイン
		Fhe_RockClime_Main( p_fhe_w );
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FHE_RockClime_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLD_HIDENEFF_ROCKCLIMB* p_fhe_w = p_work;
	int i;
	
	for( i=0; i<FHE_ROCKCLIMB_OBJ_NUM; i++ ){
		FLD_3DObjDraw( &p_fhe_w->obj[i].obj );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ロッククライム開始
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLD_HIDENEFF_RockClime_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FHE_RockClimeData = {
		FHE_TASK_PRI,
		sizeof(FLD_HIDENEFF_ROCKCLIMB),
		FHE_RockClime_Init,
		FHE_RockClime_Delete,
		FHE_RockClime_Main,
		FHE_RockClime_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FHE_RockClimeData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ロッククライム終了
 */
//-----------------------------------------------------------------------------
void FLD_HIDENEFF_RockClime_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}
