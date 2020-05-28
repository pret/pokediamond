//==============================================================================
/**
 * @file	ec_eff.h
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.01.17(火)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	__EC_EFF_H__
#define	__EC_EFF_H__

#include "effectdata/waza_particle_def.h"

// -----------------------------------------
//
//	エンカウントエフェクト 管理構造体
//
// -----------------------------------------
typedef struct _TEC_EFF_SYS * ECE_PTR;

typedef struct _TEC_EFF_MANAGER * ECEM_PTR;


// -----------------------------------------
//
//	外部指定引数用 構造体( 絶対増えるから )
//
// -----------------------------------------
/// マネージャー初期化用
typedef struct {
	
	int dmy;
	
} TECM_ADD_PARAM;

/// エンカウントエフェクト初期化用
typedef struct {

	int	eff_no;			///< エフェクト番号 EECE_EFF_NO 参照
	int	camera_type;	///< カメラのタイプ GF_CAMERA	参照
	
} TEC_ADD_PARAM;


/*
	camera_type
	GF_CAMERA_PERSPECTIV	// 透視射影
	GF_CAMERA_ORTHO			// 正射影
*/


// -----------------------------------------
//
//	エフェクトの番号定義
//
// -----------------------------------------
#define ECE_DEF_SPA_START	(P_EC_001_1_SPA)

enum EECE_EFF_NO {
	
	ECE_SPA_GRASS_001			= P_EC_001_1_SPA,			///< 芝生
	ECE_SPA_GRASS_002,
	ECE_SPA_WATER_001			= P_EC_002_1_SPA,			///< 水上
	ECE_SPA_WATER_002,
	ECE_SPA_GRAVEL_001			= P_EC_003_1_SPA,			///< 砂利
	ECE_SPA_GRAVEL_002,
	ECE_SPA_FLOOR_001			= P_EC_004_1_SPA,			///< 床
	ECE_SPA_FLOOR_002,
	ECE_SPA_ROCK_SURFACE_001	= P_EC_005_1_SPA,			///< 岩肌
	ECE_SPA_ROCK_SURFACE_002,
	ECE_SPA_SNOWFIELD_001		= P_EC_006_1_SPA,			///< 雪原
	ECE_SPA_SNOWFIELD_002,
	ECE_SPA_CAVE_001			= P_EC_007_1_SPA,			///< 洞窟
	ECE_SPA_CAVE_002,
	ECE_SPA_POOL_BALL_001		= P_EC_008_1_SPA,			///< みずたまり
	ECE_SPA_POOL_BALL_002,
	ECE_SPA_ON_THE_ICE_001		= P_EC_009_1_SPA,			///< 氷上
	ECE_SPA_ON_THE_ICE_002,
	ECE_SPA_SANDS_001			= P_EC_010_1_SPA,			///< 砂地
	ECE_SPA_SANDS_002,
	ECE_SPA_BOG_001				= P_EC_011_1_SPA,			///< 沼地
	ECE_SPA_BOG_002,	
};

// -----------------------------------------
//
//	外部参照関数
//
// -----------------------------------------
/// ECE_MANAGER
extern ECEM_PTR ECEM_Init(int heap_area, TECM_ADD_PARAM* ecmap);
extern ECE_PTR	ECEM_Load(ECEM_PTR ecmp, TEC_ADD_PARAM* ecap);
extern void		ECEM_ECE_Free(ECEM_PTR ecmp, ECE_PTR ecp);
extern void		ECEM_Free(ECEM_PTR ecmp);

extern void		ECEM_Skip(ECEM_PTR ecmp);

/// ECE
extern ECE_PTR	ECE_Init(int heap_area, TEC_ADD_PARAM* ecap);	///< 初期化
extern void		ECE_Call(ECE_PTR ecp);							///< 実行
extern BOOL		ECE_EndCheck(ECE_PTR ecp);						///< 終了チェック
extern void		ECE_Free(ECE_PTR ecp);							///< 解放処理

/*

	/// マネージャ利用の注意点
	
	ECEM_Init		初期化
	↓	
	ECEM_Load		エフェクトロード(使うものを使うだけロード)
	↓	
	ECE_Call		実行
	↓	
	ECE_EndCheck	終了待ち
	↓	
	ECEM_Free		マネージャも、ECEもすべて破棄
	
	※3個以上を動かす場合、ECEM_ECE_Freeで破棄して空きを作る

*/

#endif