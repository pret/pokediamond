//==============================================================================
/**
 * @file	ground.c
 * @brief	戦闘画面：地面(ポケモンが上に乗るお盆)
 * @author	matsuda
 * @date	2005.10.06(木)
 */
//==============================================================================
#include "common.h"
#include "graphic\batt_obj_def.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "ground.h"
#include "system/arc_tool.h"
#include "battle/battle_id.h"
#include "battle/attr_def.h"



//==============================================================================
//	定数定義
//==============================================================================
///地面のBGプライオリティ
#define GROUND_BGPRI		(3)
///自機側地面のソフトプライオリティ
#define GROUND_SOFTPRI_MINE		(1000)
///敵側地面のソフトプライオリティ
#define GROUND_SOFTPRI_ENEMY	(1000)


//==============================================================================
//	データ
//==============================================================================
///地面アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GroundObjParam[] = {
	{//GROUND_TYPE_NORMAL_MINE
		ENCOUNT_X_TYPE_AA, GROUND_MINE_Y, 0,		//x, y, z
		0, GROUND_SOFTPRI_MINE, 0,		//アニメ番号、優先順位、パレット番号
		NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
		{	//使用リソースIDテーブル
			CHARID_GROUND_MINE,	//キャラ
			PLTTID_GROUND,	//パレット
			CELLID_GROUND_MINE,	//セル
			CELLANMID_GROUND_MINE,	//セルアニメ
			CLACT_U_HEADER_DATA_NONE,		//マルチセル
			CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
		},
		GROUND_BGPRI,			//BGプライオリティ
		0,			//Vram転送フラグ
	},
	{//GROUND_TYPE_NORMAL_ENEMY
		ENCOUNT_X_TYPE_BB, GROUND_ENEMY_Y, 0,		//x, y, z
		0, GROUND_SOFTPRI_ENEMY, 0,		//アニメ番号、優先順位、パレット番号
		NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
		{	//使用リソースIDテーブル
			CHARID_GROUND_ENEMY,	//キャラ
			PLTTID_GROUND,	//パレット
			CELLID_GROUND_ENEMY,	//セル
			CELLANMID_GROUND_ENEMY,	//セルアニメ
			CLACT_U_HEADER_DATA_NONE,		//マルチセル
			CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
		},
		GROUND_BGPRI,			//BGプライオリティ
		0,			//Vram転送フラグ
	},
};

///地面キャラIDリソーステーブル：自分側
ALIGN4 static const u16 GroundResourceID_Mine[] = {
	GROUND02_M_NCGR_BIN,
	GROUND07_M_NCGR_BIN,
	GROUND00_M_NCGR_BIN,
	GROUND10_M_NCGR_BIN,
	GROUND04_M_NCGR_BIN,
	GROUND09_M_NCGR_BIN,
	GROUND05_M_NCGR_BIN,
	GROUND01_M_NCGR_BIN,
	GROUND03_M_NCGR_BIN,
	GROUND06_M_NCGR_BIN,
	GROUND08_M_NCGR_BIN,
};

///地面キャラIDリソーステーブル：敵側
ALIGN4 static const u16 GroundResourceID_Enemy[] = {
	GROUND02_E_NCGR_BIN,
	GROUND07_E_NCGR_BIN,
	GROUND00_E_NCGR_BIN,
	GROUND10_E_NCGR_BIN,
	GROUND04_E_NCGR_BIN,
	GROUND09_E_NCGR_BIN,
	GROUND05_E_NCGR_BIN,
	GROUND01_E_NCGR_BIN,
	GROUND03_E_NCGR_BIN,
	GROUND06_E_NCGR_BIN,
	GROUND08_E_NCGR_BIN,
};

///地面パレットIDリソーステーブル
ALIGN4 static const u16 GroundResourceID_Palette[][3] = {
	BATT_GROUND02_D_NCLR,	BATT_GROUND02_E_NCLR,	BATT_GROUND02_N_NCLR,
	BATT_GROUND07_D_NCLR,	BATT_GROUND07_E_NCLR,	BATT_GROUND07_N_NCLR,
	BATT_GROUND00_D_NCLR,	BATT_GROUND00_E_NCLR,	BATT_GROUND00_N_NCLR,
	BATT_GROUND10_D_NCLR,	BATT_GROUND10_E_NCLR,	BATT_GROUND10_N_NCLR,
	BATT_GROUND04_D_NCLR,	BATT_GROUND04_E_NCLR,	BATT_GROUND04_N_NCLR,
	BATT_GROUND09_D_NCLR,	BATT_GROUND09_E_NCLR,	BATT_GROUND09_N_NCLR,
	BATT_GROUND05_D_NCLR,	BATT_GROUND05_E_NCLR,	BATT_GROUND05_N_NCLR,
	BATT_GROUND01_D_NCLR,	BATT_GROUND01_E_NCLR,	BATT_GROUND01_N_NCLR,
	BATT_GROUND03_D_NCLR,	BATT_GROUND03_E_NCLR,	BATT_GROUND03_N_NCLR,
	BATT_GROUND06_D_NCLR,	BATT_GROUND06_E_NCLR,	BATT_GROUND06_N_NCLR,
	BATT_GROUND08_D_NCLR,	BATT_GROUND08_E_NCLR,	BATT_GROUND08_N_NCLR,
};


//--------------------------------------------------------------
/**
 * @brief   地面のリソース読み込み
 * @param   ground		地面ワークへのポインタ
 */
//--------------------------------------------------------------
void Ground_ResourceLoad(GROUND_WORK *ground)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_param;
	int char_resource_id, char_id, cell_resource_id, cell_id, anm_resource_id, anm_id;
	int time_zone_offset;
	
//	GF_ASSERT(ground->type < NELEMS(GroundObjParam));
	
	csp = BattleWorkCATS_SYS_PTRGet(ground->bw);
	crp = BattleWorkCATS_RES_PTRGet(ground->bw);
	time_zone_offset = BattleWorkTimeZoneOffsetGet(ground->bw);
	
	obj_param = &GroundObjParam[ground->mine_enemy];
	if(ground->mine_enemy == GROUND_TYPE_NORMAL_MINE){
		char_resource_id = GroundResourceID_Mine[ground->ground_id];
		char_id = CHARID_GROUND_MINE;
		cell_resource_id = GROUND00_M_NCER_BIN;
		cell_id = CELLID_GROUND_MINE;
		anm_resource_id = GROUND00_M_NANR_BIN;
		anm_id = CELLANMID_GROUND_MINE;
	}
	else{
		char_resource_id = GroundResourceID_Enemy[ground->ground_id];
		char_id = CHARID_GROUND_ENEMY;
		cell_resource_id = GROUND00_E_NCER_BIN;
		cell_id = CELLID_GROUND_ENEMY;
		anm_resource_id = GROUND00_E_NANR_BIN;
		anm_id = CELLANMID_GROUND_ENEMY;
	}
	
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, char_resource_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, char_id);
	CATS_LoadResourcePlttWorkArc(BattleWorkPfdGet(ground->bw), FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GroundResourceID_Palette[ground->ground_id][time_zone_offset], 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GROUND);
	//背景チェンジのために、BGパレットにも展開
	PaletteWorkSet_Arc(BattleWorkPfdGet(ground->bw),ARC_BATT_OBJ,
		GroundResourceID_Palette[ground->ground_id][time_zone_offset], HEAPID_BATTLE, 
		FADE_MAIN_BG, 0x20, 0x07*0x10);
	
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, cell_resource_id, 1, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, anm_resource_id, 1, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   地面アクターを生成する
 * @param   ground		地面ワークへのポインタ
 *
 * 先にリソースが読み込まれている必要があります。
 */
//--------------------------------------------------------------
void Ground_ActorSet(GROUND_WORK *ground)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_param;
	
	csp = BattleWorkCATS_SYS_PTRGet(ground->bw);
	crp = BattleWorkCATS_RES_PTRGet(ground->bw);

	obj_param = &GroundObjParam[ground->mine_enemy];

	ground->cap = CATS_ObjectAdd_S(csp, crp, obj_param);
	CATS_ObjectUpdate(ground->cap->act);
}

//--------------------------------------------------------------
/**
 * @brief   地面のアクターを削除する
 * @param   ground		地面ワークへのポインタ
 */
//--------------------------------------------------------------
void Ground_ActorDel(GROUND_WORK *ground)
{
	if(ground->cap == NULL){
		return;
	}
	CATS_ActorPointerDelete_S(ground->cap);
	ground->cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   地面のリソースを解放する
 * @param   ground		地面ワークへのポインタ
 */
//--------------------------------------------------------------
void Ground_ResourceFree(GROUND_WORK *ground)
{
	CATS_RES_PTR crp;
	int char_id, cell_id, anm_id;
	
	crp = BattleWorkCATS_RES_PTRGet(ground->bw);

	if(ground->mine_enemy == GROUND_TYPE_NORMAL_MINE){
		char_id = CHARID_GROUND_MINE;
		cell_id = CELLID_GROUND_MINE;
		anm_id = CELLANMID_GROUND_MINE;
	}
	else{
		char_id = CHARID_GROUND_ENEMY;
		cell_id = CELLID_GROUND_ENEMY;
		anm_id = CELLANMID_GROUND_ENEMY;
	}
	
	CATS_FreeResourceChar(crp, char_id);
	CATS_FreeResourcePltt(crp, PLTTID_GROUND);
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   地面のアクターの表示設定
 * @param   ground		地面ワークへのポインタ
 * @param   enable		CATS_ENABLE_TRUE(表示) or CATS_ENABLE_FALSE(非表示)
 */
//--------------------------------------------------------------
void Ground_EnableSet(GROUND_WORK *ground, int enable)
{
	if(ground->cap == NULL){
		return;
	}
	
	CATS_ObjectEnableCap(ground->cap, enable);
}


//==============================================================================
//
//	複数の関数をセットにしたもの
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   地面のリソースセットとアクター登録をセットにしたもの
 *
 * @param   ground		地面ワークへのポインタ
 * @param   bw			戦闘システムワークへのポインタ
 * @param   type		地面のグラフィックタイプ(GROUND_TYPE_???)
 * @param   ground_id	地面の種類(GROUND_ID_???)
 */
//--------------------------------------------------------------
void Ground_ActorResourceSet(GROUND_WORK *ground, BATTLE_WORK *bw, u16 mine_enemy, int ground_id)
{
	MI_CpuClearFast(ground, sizeof(GROUND_WORK));
	ground->bw = bw;
	ground->mine_enemy = mine_enemy;
	ground->ground_id = ground_id;
	if(ground_id >= GROUND_ID_ALL){
		GF_ASSERT(0 && "グラウンドIDが存在しません");
		ground->ground_id = 0;
	}
	Ground_ResourceLoad(ground);
	Ground_ActorSet(ground);
}

//--------------------------------------------------------------
/**
 * @brief   地面のアクター削除とリソース解放をセットにしたもの
 * @param   ground		地面ワークへのポインタ
 */
//--------------------------------------------------------------
void Ground_ActorResourceDel(GROUND_WORK *ground)
{
	Ground_ActorDel(ground);
	Ground_ResourceFree(ground);
	MI_CpuClearFast(ground, sizeof(GROUND_WORK));
}

