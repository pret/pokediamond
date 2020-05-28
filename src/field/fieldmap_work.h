//============================================================================================
/**
 * @file	fieldmap_work.h
 * @date	2006.02.04
 * @author	tamada
 * @brief	フィールドマップ限定のワーク定義
 *
 * FIELDMAP_WORKは、フィールドマップの中にしか生存期間のないワークです。
 * オーバーレイで追い出される要素（フィールドの３D表示、エフェクトその他）は
 * この領域にぶらさがることになります。
 *
 */
//============================================================================================
#ifndef	__FIELDMAP_WORK_H__
#define	__FIELDMAP_WORK_H__

#include "field/poketch.h"
#include "place_name.h"
#include "weather_sys_def.h"
#include "field_anime_def.h"
#include "seedsys.h"
#include "fieldmap_func_def.h"
#include "field_hblank.h"
#include "poison_effect.h"

//------------------------------------------------------------------
/**
 * @brief	フィールドマップ専用ワーク定義
 */
//------------------------------------------------------------------
struct FIELDMAP_WORK {
	BOOL main_mode_flag;
	FLDMAPFUNC_SYS * fmapfunc_sys;
	PNC_PTR place_name_cont;
	WEATHER_MANAGER_PTR weather_data;
	FIELD_ANIME_PTR field_trans_anime;
	POKETCH_WORK * poketch;
	SEEDSYS_WORK * seedsys;
	FIELD_HBLANK_SYS * hblanksys;
	POISON_EFFECT_WORK * poisoneffect;

	void *Work;			//汎用ワークポインタ　現在は、ジムワークとして使います
};


#endif	/* __FIELDMAP_WORK_H__ */
