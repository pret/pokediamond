//============================================================================================
/**
 * @file	quick_sand.c
 * @brief	流砂監視、アニメ呼び出し関連ファイル
 * @author	Nozomu Saito
 * @date	2006.03.16
 */
//============================================================================================
#include "quick_sand.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "fieldmap_func.h"
#include "field_3d_anime_ev.h"

typedef struct QUICK_SAND_POS_INFO_tag
{
	int GridX;
	int GridZ;
}QUICK_SAND_POS_INFO;

//==============================================================================
/**
 * 流砂タスククリエイト関数　ワーク初期化
 * 
 * @param	*fwk		フィールドマップファンクションポインタ
 * @param	*fsys		フィールドシステムポインタ
 * @param	*work		ワーク
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Create(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	//自機座標監視用ワークを初期化
	QUICK_SAND_POS_INFO *info = (QUICK_SAND_POS_INFO*)work;
	info->GridX = 0;
	info->GridZ = 0;
}

//==============================================================================
/**
 * 流砂タスクデリート関数　何もしません
 * 
 * @param	*fwk		フィールドマップファンクションポインタ
 * @param	*fsys		フィールドシステムポインタ
 * @param	*work		ワーク
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Delete(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	;
}

//==============================================================================
/**
 * 流砂タスクアップデート関数　流砂チェックを行います
 * 
 * @param	*fwk		フィールドマップファンクションポインタ
 * @param	*fsys		フィールドシステムポインタ
 * @param	*work		ワーク
 *
 * @retval  none
 */
//==============================================================================
static void QuickSand_Update(FLDMAPFUNC_WORK * fwk, FIELDSYS_WORK * fsys, void * work)
{
	u8 attr;
	int x,z;
	u8 anime_no;
	QUICK_SAND_POS_INFO *info = (QUICK_SAND_POS_INFO*)work;
	
	//自機の位置取得
	x = Player_NowGPosXGet(fsys->player);
	z = Player_NowGPosZGet(fsys->player);

	//座標比較
	if ((info->GridX == x)&&(info->GridZ == z)){
		return;
	}

	info->GridX = x;
	info->GridZ = z;
	
	//アトリビュート取得
	attr = GetAttributeLSB(fsys, x, z);
	
	if (MATR_IsShiftingSandLower(attr)){
		anime_no = 0;	//流砂下
	}else if (MATR_IsShiftingSandUpper(attr)){
		anime_no = 1;	//流砂上
	}else{
		return;
	}
	Fld3DAnm_StartQuickSandAnime(x, z, anime_no, fsys);
}

static const FLDMAPFUNC_DATA QuickSandData = {
	FLDMAP_PRI_QUICK_SAND,
	sizeof(QUICK_SAND_POS_INFO),
	QuickSand_Create,
	QuickSand_Delete,
	QuickSand_Update,
	NULL
};

//==============================================================================
/**
 * 流砂タスク作成関数
 * 
 * @param	*fsys		フィールドシステムポインタ
 *
 * @retval  none
 */
//==============================================================================
void QuickSand_CheckTask(FIELDSYS_WORK * fsys)
{
	FLDMAPFUNC_Create(fsys->fldmap->fmapfunc_sys, &QuickSandData);
}
