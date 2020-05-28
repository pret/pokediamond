//============================================================================================
/**
 * @file	field_gimmick_def.h
 * @brief	マップ固有の仕掛けのIDを定義するファイル
 * @author	saito
 * @date	2006.02.09
 *
 */
//============================================================================================
#ifndef __FIELD_GIMMICK_DEF_H__
#define __FIELD_GIMMICK_DEF_H__

typedef enum{
	FLD_GIMMICK_NONE,			//0:なし
	FLD_GIMMICK_WATER_GYM,		//1:水ジム
	FLD_GIMMICK_GHOST_GYM,		//2:ゴーストジム
	FLD_GIMMICK_STEEL_GYM,		//3:鋼ジム
	FLD_GIMMICK_COMBAT_GYM,		//4:格闘ジム
	FLD_GIMMICK_ELEC_GYM,		//5:電気ジム
	FLD_GIMMICK_SAFARI_TRAIN,	//6:サファリ電車
	FLD_GIMMICK_FLD_LIFT,		//7:フィールドリフト
}FLD_GYMMICK_ID;

#define FLD_GIMMICK_MAX	(8)		//ギミック無しを含めた数

#endif	//__FIELD_GIMMICK_DEF_H__

