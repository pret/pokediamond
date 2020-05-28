//==============================================================================
/**
 * @file	field_effect.h
 * @brief	フィールドエフェクト
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_EFFECT_H_FILE
#define FIELD_EFFECT_H_FILE

//==============================================================================
/*
	フィールドエフェクト関連　簡易説明
	
	＜ソースファイル＞
	field_effect.h フィールドエフェクトヘッダー
	field_effect.c フィールドエフェクト処理
	field_effect_data.c　エフェクト登録ソースファイル
	
	※以下、field_effect.hにinlcude済み
	field_effect_code.h フィールドエフェクト用シンボル定義
	field_effect_subproc.h　エフェクト参照ヘッダー　一覧
	
	＜フィールドエフェクト用　アーカイブデータインデックスIDファイル＞
	src\data\mmodel\fldeff.naix
	※field_effect.hにinlcude済み
	
	＜新規エフェクトの追加方法＞
	１：FE_SUBPROC_INIT型のエフェクト初期化関数、FE_SUBPROC_DELETE型のエフェクト削除関数作成
	２：新規エフェクト関数参照ヘッダーをfield_effect_subproc.hにinlcude
	３：field_effect_code.h　に新規エフェクトIDを追加
	４：field_effect_data.c　に新規エフェクトIDとそれに関連した初期化、削除関数定義
	５：FE_EffectRegist()等で呼び出し、動作確認
	６：field_effect_subproc.h field_effect_code.h field_effect_data.cをcommit
	
	＜フィールドエフェクト専用アーカイブデータの更新方法＞
	１：src\data\mmodel\fldeff_listへアーカイブ対象ファイルを定義
	２：上記ディレクトリでmake実行。アーカイブが作成される
	３：動作確認
	４：アーカイブ対象ファイルとfldeff_listをcommitする
	※mmodelディレクトリにてmakeする事で生成されるコンバートデータファイルのcommitは禁止
	※アーカイブファイル(*.narc,*.naix)のcommitも禁止。アーカイブファイル生成は個々の環境で行う
	
	＜エフェクト追加、削除関連関数＞
	FE_EffectRegist()
	FE_EffectRegistMore()
	FE_EffectDelete()
	
	＜エフェクト使用ワーク取得関数＞
	FE_EffectWorkGet()
	
	＜フィールドエフェクト専用ヒープ領域関連関数＞
	FE_AllocMemory()
	FE_AllocClearMemory()
	FE_FreeMemory()
	
	＜フィールドエフェクト専用アーカイブデータ関連関数＞
	FE_ArcDataLoad()
	FE_ArcDataLoadAlloc()
	FE_ArcDataSizeGet()
*/
//==============================================================================

#include "localres.h"					//LRES
#include "eoa.h"						//EOA

#include "field_common.h"				//FIELD COMMON
#include "fieldobj.h"					//FIELD_OBJ

#include "field_effect_code.h"			//エフェクトシンボル定義
#include "..\data\mmodel\fldeff.naix"	//ARC_FLDEFF

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	ビルボード　常駐　転送
//--------------------------------------------------------------
enum
{
	FE_BLACT_TEX_VRAM = 0,									///<テクスチャVRAM常駐
	FE_BLACT_TEX_TRANS,										///<テクスチャ転送
};

//==============================================================================
//	typedef struct 
//==============================================================================
//--------------------------------------------------------------
///	FE_SYS構造体名定義　フィールドエフェクト情報を纏める
//--------------------------------------------------------------
typedef struct _TAG_FE_SYS FE_SYS;

//--------------------------------------------------------------
///	エフェクト初期化関数型定義。
/// 引数：FE_SYS * 戻り値：関数で使用するワーク *
//--------------------------------------------------------------
typedef void * (*FE_SUBPROC_INIT)( FE_SYS * );

//--------------------------------------------------------------
///	エフェクト削除関数型定義。
/// 引数：void * = FE_SUBPROC_INITの戻り値
//--------------------------------------------------------------
typedef void (*FE_SUBPROC_DELETE)( void * );

//--------------------------------------------------------------
///	FE_SUBPROC_DATA構造体 エフェクト関数ID登録データ
//--------------------------------------------------------------
typedef struct
{
	u32 id;								///<proc_init,proc_delを呼び出す為の識別ID
	FE_SUBPROC_INIT proc_init;			///<idを指定した際に呼ばれるエフェクト初期化関数
	FE_SUBPROC_DELETE proc_del;			///<idを指定した際に呼ばれるエフェクト削除関数
}FE_SUBPROC_DATA;

#define FE_SUBPROC_DATA_SIZE (sizeof(FE_SUBPROC_DATA))

//==============================================================================
//	外部参照
//==============================================================================
extern FE_SYS * FE_Init( FIELDSYS_WORK *fsys, u32 reg_max, u32 heap_id, u32 worksize );
extern void FE_ParamInit_EOA( FE_SYS *fes, u32 eoa_max );
extern void FE_ParamInit_BlAct( FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size );
extern void FE_EffectRegist( FE_SYS *fes, u32 id );
extern void FE_EffectRegistMore( FE_SYS *fes, const u32 *id_tbl );
extern int FE_EffectRegistCheck( FE_SYS *fes, u32 id );
extern void FE_EffectDelete( FE_SYS *fes, u32 id );
extern void FE_Draw( FE_SYS *fes );
extern void FE_Delete( FE_SYS *fes );

extern void * FE_AllocMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type );
extern void * FE_AllocClearMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type, u32 clear );
extern void FE_FreeMemory( void *alloc );
extern void * FE_EffectWorkGet( FE_SYS *fes, u32 id );
extern FIELDSYS_WORK * FE_FieldSysWorkGet( const FE_SYS *fes );
extern FE_SYS * FE_FieldOBJ_FE_SYS_Get( CONST_FIELD_OBJ_PTR fldobj );

extern u32 FE_ArcDataSizeGet( FE_SYS *fes, u32 datid );
extern void FE_ArcDataLoad( FE_SYS *fes, u32 datid, void *buf );
extern void * FE_ArcDataLoadAlloc( FE_SYS *fes, u32 datid, ALLOCTYPE type );

extern EOA_PTR FE_EoaAddNpp( const FE_SYS *fes, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri );
extern void FE_EoaDelete( EOA_PTR eoa );

extern BLACT_WORK_PTR FE_BlActAdd( FE_SYS *fes, 
		const BLACT_HEADER *head, const VecFx32 *vec );
extern BLACT_WORK_PTR FE_BlActAddID( FE_SYS *fes, u32 id, const VecFx32 *vec );
extern BLACT_HEADER * FE_BlActHeaderManageAdd( FE_SYS *fes, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl );
extern BLACT_HEADER * FE_BlActHeaderManageAddResmID(
		FE_SYS *fes, u32 id, u32 mdl_id, u32 anm_id, u32 tex_id, int tex_flag,
		const BLACT_ANIME_TBL *anm_tbl );
extern BLACT_HEADER * FE_BlActHeaderManageGet( FE_SYS *fes, u32 id );
extern void FE_BlActHeaderManageFree( FE_SYS *fes, u32 id );

extern void FE_BlActResAdd_Mdl( FE_SYS *fes, u32 id, const void *data, u32 size );
extern void FE_BlActResAdd_MdlArc( FE_SYS *fes, u32 id, u32 datid );
extern void * FE_BlActResGet_Mdl( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Mdl( FE_SYS *fes, u32 id );
extern void FE_BlActResAdd_Anm( FE_SYS *fes, u32 id, const void *data, u32 size );
extern void FE_BlActResAdd_AnmArc( FE_SYS *fes, u32 id, u32 datid );
extern void * FE_BlActResGet_Anm( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Anm( FE_SYS *fes, u32 id );
extern void FE_BlActResAdd_Tex( FE_SYS *fes, u32 id, void *data, u32 texcut );
extern void FE_BlActResAdd_TexArc( FE_SYS *fes, u32 id, u32 datid, u32 texcut );
extern void * FE_BlActResGet_Tex( FE_SYS *fes, u32 id );
extern void FE_BlActResDelete_Tex( FE_SYS *fes, u32 id );

extern void FE_simple3DModelInitOnly( FE_SYS *fes,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile );
extern void FE_simple3DModelInit( FE_SYS *fes, u32 dataid, ALLOCTYPE type,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile );
extern void FE_3DObjMdlLoad( FE_SYS *fes, FLD_3DOBJ_MDL *p_mdl, u32 dataid, ALLOCTYPE type );
extern void FE_3DObjAnmLoad(
		FE_SYS *fes,
		FLD_3DOBJ_ANM *p_anm,
		const FLD_3DOBJ_MDL *cp_mdl,
		NNSFndAllocator* pallocator,
		u32 dataid, ALLOCTYPE type );
extern void FE_InitAllocator( FE_SYS *fes, NNSFndAllocator *pAllocator );

//==============================================================================
//	field_effect_data.c
//==============================================================================
extern const FE_SUBPROC_DATA DATA_FE_SubProcDataTbl[FE_PROC_MAX+1];
extern const u32 DATA_FE_GroundProcRegistTbl[FE_PROC_MAX+1];
extern const u32 DATA_FE_UnderProcRegistTbl[FE_PROC_MAX+1];

//==============================================================================
//	field_effect.hを利用した関数のinclude
//==============================================================================
#include "field_effect_subproc.h"

#endif //FIELD_EFFECT_H_FILE
