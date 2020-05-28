//******************************************************************************
/**
 * 
 * @file	field_effect_data.c
 * @brief	フィールドエフェクト用データ定義
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"

//==============================================================================
//	フィールドエフェクト　関数登録
//==============================================================================
//--------------------------------------------------------------
///	フィールドエフェクト　初期化、削除関数登録　並びは不順
//--------------------------------------------------------------
const FE_SUBPROC_DATA DATA_FE_SubProcDataTbl[FE_PROC_MAX+1] =
{
	{FE_FLD_SHADOW,FE_Shadow_Init,FE_Shadow_Delete},
	{FE_FLD_REFLECT,FE_Reflect_Init,FE_Reflect_Delete},
	{FE_UG_TRAP,FE_Trap_Init,FE_Trap_Delete},
	{FE_UG_TRAP_HOLE,FE_Hole_Init,FE_Hole_Delete},
	{FE_UG_TRAP_DIR,FE_DirTrap_Init,FE_DirTrap_Delete},
	{FE_UG_TRAP_FLAG,FE_Flag_Init,FE_Flag_Delete},
	{FE_UG_TRAP_EXCLAMATION,FE_Exclamation_Init,FE_Exclamation_Delete},
	{FE_UG_TRAP_OK,FE_Ok_Init,FE_Ok_Delete},
	{FE_UG_TRAP_SMOG,FE_Trapsmog_Init,FE_Trapsmog_Delete},
	{FE_UG_TRAP_GFLASH,FE_GFlash_Init,FE_GFlash_Delete},
	{FE_UG_DRILL,FE_Drill_Init,FE_Drill_Delete},
	{FE_FLD_FOOTMARK,FE_FootMark_Init,FE_FootMark_Delete},
	{FE_FLD_BOARD,FE_Board_Init,FE_Board_Delete},
	{FE_FLD_SEEDGROUND,FE_SeedGround_Init,FE_SeedGround_Delete},
	{FE_FLD_SNOWBALL,FE_SnowBall_Init,FE_SnowBall_Delete},
	{FE_FLD_BOOK,FE_Book_Init,FE_Book_Delete},
	{FE_FLD_ARROW,FE_Arrow_Init,FE_Arrow_Delete},
	{FE_FLD_NAMIPOKE,FE_NamiPoke_Init,FE_NamiPoke_Delete},
	{FE_FLD_ROCKRIDE,FE_RockRide_Init,FE_RockRide_Delete},
	{FE_FLD_RIPPLE,FE_Ripple_Init,FE_Ripple_Delete},
	{FE_FLD_NRIPPLE,FE_NRipple_Init,FE_NRipple_Delete},
	{FE_FLD_GRASS,FE_Grass_Init,FE_Grass_Delete},
	{FE_FLD_GYOE,FE_Gyoe_Init,FE_Gyoe_Delete},
	{FE_FLD_SPLASH,FE_Splash_Init,FE_Splash_Delete},
	{FE_UG_REDFRAME,FE_RedFrame_Init,FE_RedFrame_Delete},
	{FE_FLD_KEMURI,FE_Kemuri_Init,FE_Kemuri_Delete},
	{FE_FLD_LGRASS,FE_LGrass_Init,FE_LGrass_Delete},
	{FE_FLD_NGRASS,FE_NGrass_Init,FE_NGrass_Delete},
	{FE_FLD_HIDE,FE_Hide_Init,FE_Hide_Delete},
	{FE_FLD_HKEMURI,FE_HKemuri_Init,FE_HKemuri_Delete},
	{FE_FLD_SEED_EFF,FE_SeedEff_Init,FE_SeedEff_Delete},
	{FE_FLD_DOOR2,FE_Door2_Init,FE_Door2_Delete},
	
	{FE_PROC_MAX,NULL,NULL},	///< 終端
};

//--------------------------------------------------------------
///	フィールドエフェクト　全エフェクト登録用データテーブル（地上用）
//--------------------------------------------------------------
const u32 DATA_FE_GroundProcRegistTbl[FE_PROC_MAX+1] =
{
	FE_FLD_SHADOW,
	FE_FLD_FOOTMARK,
	FE_FLD_BOARD,
	FE_FLD_SEEDGROUND,
	FE_FLD_BOOK,
	FE_FLD_ARROW,
	FE_FLD_NAMIPOKE,
	FE_FLD_ROCKRIDE,
	FE_FLD_HIDE,
	FE_FLD_DOOR2,
	
	FE_FLD_SNOWBALL,
	FE_FLD_RIPPLE,
	FE_FLD_NRIPPLE,
	
	FE_FLD_GRASS,
	FE_FLD_GYOE,
	FE_FLD_SPLASH,
	FE_UG_REDFRAME,
	FE_FLD_KEMURI,
	FE_FLD_LGRASS,
	FE_FLD_NGRASS,
	FE_FLD_HKEMURI,
	FE_FLD_REFLECT,
	FE_FLD_SEED_EFF,
	
	FE_PROC_MAX, //終端
};

//--------------------------------------------------------------
///	フィールドエフェクト　地下エフェクト登録用データテーブル
//--------------------------------------------------------------
const u32 DATA_FE_UnderProcRegistTbl[FE_PROC_MAX+1] =
{
	FE_UG_TRAP,
	FE_UG_TRAP_HOLE,
	FE_UG_TRAP_DIR,
	FE_UG_TRAP_FLAG,
	FE_UG_TRAP_EXCLAMATION,
	FE_UG_TRAP_OK,
	FE_FLD_ARROW,
	
	FE_UG_TRAP_SMOG,
	FE_UG_TRAP_GFLASH,
	FE_UG_DRILL,
	
	FE_FLD_GYOE,
	
	FE_PROC_MAX, //終端
};
