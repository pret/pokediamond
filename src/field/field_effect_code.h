//==============================================================================
/**
 * @file	field_effect_code.h
 * @brief	フィールドエフェクト用シンボル定義
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_EFFECT_CODE_H_FILE
#define FIELD_EFFECT_CODE_H_FILE

//==============================================================================
//	エフェクト
//==============================================================================
//--------------------------------------------------------------
///	エフェクトID
//--------------------------------------------------------------
enum
{
	FE_FLD_SHADOW = 0,								///<フィールドOBJ　影
	FE_FLD_REFLECT,									///<フィールドOBJ　映り込み
	FE_UG_TRAP,										///<地下　罠
	FE_UG_TRAP_HOLE,								///<地下　罠　穴
	FE_UG_TRAP_DIR,									///<地下　罠　方向
	FE_UG_TRAP_FLAG,								///<地下　罠　旗
	FE_UG_TRAP_EXCLAMATION,							///<地下　罠　!マーク
	FE_UG_TRAP_OK,									///<地下　罠　OKマーク
	FE_UG_TRAP_SMOG,								///<地下　罠　煙
	FE_UG_TRAP_GFLASH,								///<地下　罠　たまマーク
	FE_UG_DRILL,									///<地下　ドリル演出
	FE_FLD_FOOTMARK,								///<フィールドOBJ　足跡
	FE_FLD_BOARD,									///<フィールドOBJ　看板
	FE_FLD_SEEDGROUND,								///<フィールドOBJ　木の実土
	FE_FLD_SNOWBALL,								///<フィールドOBJ　雪球
	FE_FLD_BOOK,									///<フィールドOBJ　本
	FE_FLD_ARROW,									///<フィールドOBJ　矢印
	FE_FLD_NAMIPOKE,								///<フィールドOBJ　波乗りポケモン
	FE_FLD_ROCKRIDE,								///<フィールドOBJ　壁のぼりポケモン
	FE_FLD_RIPPLE,									///<フィールドOBJ　水波紋
	FE_FLD_NRIPPLE,									///<フィールドOBJ　沼波紋
	FE_FLD_GRASS,									///<フィールドOBJ　草削除
	FE_FLD_GYOE,									///<フィールドOBJ　ギョエー
	FE_FLD_SPLASH,									///<フィールドOBJ　水しぶき
	FE_UG_REDFRAME,									///<地下　枠
	FE_FLD_KEMURI,									///<フィールドOBJ　土煙
	FE_FLD_LGRASS,									///<フィールドOBJ　長い草
	FE_FLD_NGRASS,									///<フィールドOBJ　沼草
	FE_FLD_HIDE,									///<フィールドOBJ　隠れ蓑
	FE_FLD_HKEMURI,									///<フィールドOBJ　隠れ蓑煙
	FE_FLD_SEED_EFF,								///<フィールドOBJ　木の実エフェクト
	FE_FLD_DOOR2,									///<フィールドOBJ　ドア２
	
	FE_PROC_MAX,									///<最大
};

//==============================================================================
//	ビルボード
//==============================================================================
//--------------------------------------------------------------
///	ビルボードヘッダーID
//--------------------------------------------------------------
enum
{
	FE_BLACT_H_ID_GRASS = 0,								///<草
	FE_BLACT_H_ID_GYOE,										///<ギョエー
	FE_BLACT_H_ID_REFLECT,									///<映りこみ
	FE_BLACT_H_ID_SPLASH,									///<水飛沫
	FE_BLACT_H_ID_REDFRAME,									///<赤枠
	FE_BLACT_H_ID_GRASS_ENCOUNT_SMALL,						///<エンカウント草揺れ小
	FE_BLACT_H_ID_GRASS_ENCOUNT_BIG,						///<エンカウント草揺れ大
	FE_BLACT_H_ID_GRASS_ENCOUNT_KIRAKIRA,					///<エンカウント草揺れきらきら
	FE_BLACT_H_ID_KEMURI,									///<土煙
	FE_BLACT_H_ID_LGRASS,									///<長い草
	FE_BLACT_H_ID_NGRASS,									///<沼草
	FE_BLACT_H_ID_HKEMURI,									///<隠れ蓑土煙
	FE_BLACT_H_ID_GYOE_SAISEN,								///<再戦ギョエー
	FE_BLACT_H_ID_SEED_EFF,									///<木の実エフェクト
	
	FE_BLACT_H_ID_NOT,										///<無効ID
};

//--------------------------------------------------------------
///	ビルボードリソース　モデルID
//--------------------------------------------------------------
enum
{
	FE_RESID_MDL_GRASS = 0,									///<草
	FE_RESID_MDL_GYOE,										///<ギョエー
	FE_RESID_MDL_REFLECT,									///<映りこみ
	FE_RESID_MDL_SPLASH,									///<水飛沫
	FE_RESID_MDL_REDFRAME,									///<赤枠
	FE_RESID_MDL_GRASS_ENCOUNT,								///<草エンカウント
	FE_RESID_MDL_KEMURI,									///<土煙
	FE_RESID_MDL_LGRASS,									///<長い草
	FE_RESID_MDL_NGRASS,									///<沼草
	FE_RESID_MDL_HKEMURI,									///<隠れ蓑土煙
	FE_RESID_MDL_GYOE_SAISEN,								///<再戦ギョエー
	FE_RESID_MDL_SEED_EFF,									///<木の実エフェクト
};

//--------------------------------------------------------------
///	ビルボードリソース　アニメID
//--------------------------------------------------------------
enum
{
	FE_RESID_ANM_GRASS = 0,									///<草
	FE_RESID_ANM_GYOE,										///<ギョエー
	FE_RESID_ANM_SPLASH,									///<水飛沫
	FE_RESID_ANM_GRASS_ENCOUNT_SMALL,						///<エンカウント草揺れ小
	FE_RESID_ANM_GRASS_ENCOUNT_BIG,							///<エンカウント草揺れ大
	FE_RESID_ANM_GRASS_ENCOUNT_KIRAKIRA,					///<エンカウント草揺れきらきら
	FE_RESID_ANM_KEMURI,									///<土煙
	FE_RESID_ANM_LGRASS,									///<長い草
	FE_RESID_ANM_NGRASS,									///<沼草
	FE_RESID_ANM_HKEMURI,									///<隠れ蓑土煙
	FE_RESID_ANM_GYOE_SAISEN,								///<再戦ギョエー
	FE_RESID_ANM_SEED_EFF,									///<木の実エフェクト
};

//--------------------------------------------------------------
///	ビルボードリソース　テクスチャID
//--------------------------------------------------------------
enum
{
	FE_RESID_TEX_GRASS = 0,									///<草
	FE_RESID_TEX_GYOE,										///<ギョエー
	FE_RESID_TEX_SPLASH,									///<水飛沫
	FE_RESID_TEX_REDFRAME,									///<赤枠
	FE_RESID_TEX_GRASS_ENCOUNT_SMALL,						///<エンカウント草揺れ小
	FE_RESID_TEX_GRASS_ENCOUNT_BIG,							///<エンカウント草揺れ大
	FE_RESID_TEX_GRASS_ENCOUNT_KIRAKIRA,					///<エンカウント草揺れきらきら
	FE_RESID_TEX_KEMURI,									///<土煙
	FE_RESID_TEX_LGRASS,									///<長い草
	FE_RESID_TEX_NGRASS,									///<沼草
	FE_RESID_TEX_HKEMURI,									///<隠れ蓑土煙
	FE_RESID_TEX_GYOE_SAISEN,								///<再戦ギョエー
	FE_RESID_TEX_SEED_EFF,									///<木の実エフェクト
	
	FE_RESID_TEX_MAX,										///<最大
};

#endif //FIELD_EFFECT_CODE_H_FILE
