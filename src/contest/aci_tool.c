//==============================================================================
/**
 * @file	aci_tool.c
 * @brief	actin_input.cで使用するツール(actin_input.cのシステムに依存しないもの限定)
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "con_tool.h"
#include "actin_id.h"
#include "aci_tool.h"



//==============================================================================
//	アクターヘッダ
//==============================================================================
///審判ハートアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S SubHeartJudgeObjParam = {
	SUB_HEART_JUDGE_POS_X, SUB_HEART_JUDGE_POS_Y, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_HEART_JUDGE, PALOFS_SUB_HEART_32,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_SUB_HEART_32,	//キャラ
		PLTTID_OBJ_COMMON_SUB,	//パレット
		CELLID_SUB_HEART_32,	//セル
		CELLANMID_SUB_HEART_32,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_HEART_JUDGE,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///AP値ハートアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S AppHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_APP_HEART, PALOFS_SUB_HEART_8,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_SUB_HEART_8,	//キャラ
		PLTTID_OBJ_COMMON_SUB,	//パレット
		CELLID_SUB_HEART_8,	//セル
		CELLANMID_SUB_HEART_8,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_APP_HEART,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///妨害値ハートアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ObstructHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTINSUB_SOFTPRI_APP_HEART, PALOFS_SUB_HEART_BLACK_8,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_SUB_HEART_8,	//キャラ
		PLTTID_OBJ_COMMON_SUB,	//パレット
		CELLID_SUB_HEART_8,	//セル
		CELLANMID_SUB_HEART_8,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_APP_HEART,			//BGプライオリティ
	0,			//Vram転送フラグ
};




//--------------------------------------------------------------
/**
 * @brief   審判ハートのリソース登録
 *
 * @param   csp			
 * @param   crp			
 * @param   judge_no	審判NO
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeResourceSet(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//リソースロード
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_SUB_HEART_32);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NCER_BIN, 1, 
		CELLID_SUB_HEART_32);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART32_NANR_BIN,
		1, CELLANMID_SUB_HEART_32);
}

//--------------------------------------------------------------
/**
 * @brief   審判ハートのアクター登録
 *
 * @param   csp			
 * @param   crp			
 * @param   judge_no	審判NO
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
CATS_ACT_PTR ACIT_SubHeartJudgeActorAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no)
{
	CATS_ACT_PTR sub_heart_judge_cap;
	
	//アクター生成
	sub_heart_judge_cap = CATS_ObjectAdd_S(csp, crp, &SubHeartJudgeObjParam);
	CATS_ObjectPosSetCap_SubSurface(sub_heart_judge_cap, 
		SUB_HEART_JUDGE_POS_X + SUB_HEART_JUDGE_POS_X_SPACE * judge_no, 
		SUB_HEART_JUDGE_POS_Y + SUB_HEART_JUDGE_POS_Y_SPACE * judge_no,
		ACTIN_SUB_ACTOR_DISTANCE);
	CATS_ObjectUpdate(sub_heart_judge_cap->act);
	return sub_heart_judge_cap;
}

//--------------------------------------------------------------
/**
 * @brief   審判ハートのリソースを削除する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_SUB_HEART_32);
	CATS_FreeResourceCell(crp, CELLID_SUB_HEART_32);
	CATS_FreeResourceCellAnm(crp, CELLANMID_SUB_HEART_32);
}

//--------------------------------------------------------------
/**
 * @brief   審判ハートのアクターを削除する(リソース＆アクター)
 *
 * @param   sub_heart_judge_cap		審判アクターへのポインタ
 */
//--------------------------------------------------------------
void ACIT_SubHeartJudgeActorDel(CATS_ACT_PTR sub_heart_judge_cap)
{
	CATS_ActorPointerDelete_S(sub_heart_judge_cap);
}

//--------------------------------------------------------------
/**
 * @brief   AP値ハートのリソースをロードする
 *
 * @param   csp			
 * @param   crp			
 */
//--------------------------------------------------------------
void ACIT_AppHeartResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//リソースロード
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_SUB_HEART_8);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NCER_BIN, 1, 
		CELLID_SUB_HEART_8);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, SUB_HEART8_NANR_BIN,
		1, CELLANMID_SUB_HEART_8);
}

//--------------------------------------------------------------
/**
 * @brief   AP値ハートアクターを生成する
 *
 * @param   csp		
 * @param   crp		
 * @param   x			座標X
 * @param   y			座標Y
 * @param   ap_point	AP値
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
CATS_ACT_PTR ACIT_AppHeartActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	int x, int y, int ap_point)
{
	CATS_ACT_PTR heart_cap;

	//アクター生成
	if(ap_point >= 0){
		heart_cap = CATS_ObjectAdd_S(csp, crp, &AppHeartObjParam);
	}
	else{
		heart_cap = CATS_ObjectAdd_S(csp, crp, &ObstructHeartObjParam);
	}
	CATS_ObjectPosSetCap_SubSurface(heart_cap, x, y, ACTIN_SUB_ACTOR_DISTANCE);
	CATS_ObjectUpdate(heart_cap->act);
	return heart_cap;
}

//--------------------------------------------------------------
/**
 * @brief   AP値ハートアクターを削除する
 * @param   heart_cap		AP値ハートへのポインタ
 */
//--------------------------------------------------------------
void ACIT_AppHeartActorDel(CATS_ACT_PTR heart_cap)
{
	CATS_ActorPointerDelete_S(heart_cap);
}

//--------------------------------------------------------------
/**
 * @brief   AP値ハートのリソースを解放する
 * @param   crp		
 */
//--------------------------------------------------------------
void ACIT_AppHeartResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_SUB_HEART_8);
	CATS_FreeResourceCell(crp, CELLID_SUB_HEART_8);
	CATS_FreeResourceCellAnm(crp, CELLANMID_SUB_HEART_8);
}
