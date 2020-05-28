//============================================================================================
/**
 * @file	seedsys.c
 * @brief	フィールドでのきのみ成長処理など
 * @author	tamada GAME FREAK inc.
 * @date	2006.02.09
 */
//============================================================================================

//============================================================================================
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "savedata/seedbed.h"
#include "itemtool/myitem.h"
#include "itemtool/nuts.h"

#include "seedsys.h"
#include "fieldobj.h"

#include "field_event.h"

#include "itemtool/nuts.h"

#include "fieldmap_work.h"

#include "tv_topic.h"

static void CreateDummyOBJ(FIELDSYS_WORK *fsys, SEEDSYS_WORK * ssys);
static void DeleteDummyOBJ(SEEDSYS_WORK * ssys);
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
#define COMPOST_START_ITEMNUM	(ITEM_SUKUSUKUKOYASI)

//----------------------------------------------------------
//----------------------------------------------------------
struct SEEDSYS_WORK {
	int heapID;
	SEED_TABLE * param;
	NNSG3dRenderObj render;
	NNSG3dResMdl * model_p;
	NNSG3dResFileHeader * resfile;
};

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	きのみID→アイテムナンバーに変換
 */
//----------------------------------------------------------
static u16 nuts2item(int type)
{
	if (type == 0) {
		return 0;
	}
	return type + NUTS_START_ITEMNUM - 1;
}
//----------------------------------------------------------
/**
 * @brief	アイテムナンバー→きのみIDへの変換
 */
//----------------------------------------------------------
static u16 item2nuts(int itemno)
{
	if (itemno == 0) {
		return 0;
	}
	return itemno - NUTS_START_ITEMNUM + 1;
}
//----------------------------------------------------------
/**
 * @brief	コヤシ指定→アイテムナンバーへの変換
 */
//----------------------------------------------------------
static u16 compost2item(SEEDCOMPOST compost)
{
	if (compost == 0) {
		return 0;
	}
	return compost + COMPOST_START_ITEMNUM - 1;
}
//----------------------------------------------------------
/**
 * @brief	アイテムナンバー→コヤシ指定への変換
 */
//----------------------------------------------------------
static SEEDCOMPOST item2compost(int itemno)
{
	if (itemno == 0) {
		return 0;
	}
	return itemno - COMPOST_START_ITEMNUM + 1;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	きのみ成長制御システムの生成
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	heapID		確保するヒープのID
 */
//----------------------------------------------------------
SEEDSYS_WORK * SeedSys_Init(FIELDSYS_WORK * fsys, int heapID)
{
	SEEDSYS_WORK * sys;
	sys = sys_AllocMemory(heapID, sizeof(SEEDSYS_WORK));
	MI_CpuClear8(sys, sizeof(SEEDSYS_WORK));
	sys->heapID = heapID;
	sys->param = SEEDBED_CreateParamTable(heapID);
	CreateDummyOBJ(fsys,sys);
	return sys;
}

//----------------------------------------------------------
/**
 * @brief	きのみ成長制御システムの解放
 * @param	seedsys		SEEDSYS_WORKへのポインタ
 */
//----------------------------------------------------------
void SeedSys_Finish(SEEDSYS_WORK * seedsys)
{
	DeleteDummyOBJ(seedsys);
	sys_FreeMemoryEz(seedsys->param);
	sys_FreeMemoryEz(seedsys);
}

//----------------------------------------------------------
/**
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	diff_minute	すすんだ時間（分単位）
 */
//----------------------------------------------------------
void SeedSys_Growth(FIELDSYS_WORK * fsys, int diff_minute)
{
	SEEDBED * sbed;
	SEED_TABLE * param;
	if (fsys->fldmap == NULL) {
		param = SEEDBED_CreateParamTable(HEAPID_WORLD);
		sbed = SaveData_GetSeedBed(fsys->savedata);
		SEEDBED_Growth(sbed, param, diff_minute);
		sys_FreeMemoryEz(param);
	} else {
		param = fsys->fldmap->seedsys->param;
		sbed = SaveData_GetSeedBed(fsys->savedata);
		SEEDBED_Growth(sbed, param, diff_minute);
	}
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
static void CreateDummyOBJ(FIELDSYS_WORK *fsys, SEEDSYS_WORK * ssys)
{
	FE_SYS *fes = fsys->fes;
	u32 size = FE_ArcDataSizeGet( fes, NARC_fldeff_kage_nsbmd );
	ssys->resfile = sys_AllocMemory( ssys->heapID, size );
	FE_ArcDataLoad( fes, NARC_fldeff_kage_nsbmd, ssys->resfile );
	simple_3DModelSetResFileAlready( &ssys->render, &ssys->model_p, &ssys->resfile );
}

static void DeleteDummyOBJ(SEEDSYS_WORK * ssys)
{
	FE_FreeMemory(ssys->resfile);
}

#if 0	//old
static void CreateDummyOBJ(SEEDSYS_WORK * ssys)
{
	NNS_G3dRenderObjInit( &ssys->render, ssys->model_p );
	simple_3DModelSet( ssys->heapID, "data/kage.nsbmd",
                       &ssys->render, &ssys->model_p, &ssys->resfile );
}

static void DeleteDummyOBJ(SEEDSYS_WORK * ssys)
{
	sys_FreeMemoryEz(ssys->resfile);
}
#endif

//----------------------------------------------------------
//----------------------------------------------------------
static BOOL CheckInScreen(FIELDSYS_WORK * fsys, const VecFx32 * pos)
{
	const VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
	MtxFx33 rot;
	MTX_Identity33(&rot);
	if (BB_CullingCheck3DModel(fsys->fldmap->seedsys->model_p, pos, &rot, &scale) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	視界チェック
 * @param	fsys		FIELDSYS_WORKへのポインタ
 *
 * 視界に入ったら成長フラグをONにする
 */
//----------------------------------------------------------
void SeedSys_CheckInScreen(FIELDSYS_WORK * fsys)
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	while (FieldOBJSys_FieldOBJSearch(fsys->fldobjsys, &fldobj, &no, FLDOBJ_STA_BIT_USE) == TRUE) {
		if (FieldOBJ_OBJCodeSeedCheck(FieldOBJ_OBJCodeGet(fldobj)) == TRUE) {
			if (CheckInScreen(fsys, FieldOBJ_VecPosPtrGet(fldobj))) {
				int id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
				SEEDBED_SetGrowthFlag(sbed, id, TRUE);
			}

		}
	}
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	きのみが植えられるかどうかのチェック
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @retval	TRUE		きのみが植えられる
 * @retval	FALSE		きのみは植えられない
 */
//----------------------------------------------------------
BOOL SeedSys_EnableSetKinomi(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	if (fldobj == NULL) {
		return FALSE;
	}
	if (FieldOBJ_OBJCodeGet(fldobj) != SEED) {
		return FALSE;
	}
	if (SeedSys_GetSeedStatus(fsys,fldobj) != SEEDSTAT_NOTHING) {
		return FALSE;
	}
	return TRUE;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	木の実を収穫する
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	BOOL		きのみを取れたかどうか
 */
//----------------------------------------------------------
BOOL SeedSys_TakeNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	int id, num, type;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	type = SEEDBED_GetSeedType(sbed, id);
	num = SEEDBED_GetSeedCount(sbed, id);
	//テレビトピック生成
	TVTOPIC_Entry_TakeNuts(fsys, nuts2item(type), SEEDBED_GetSeedHP(sbed,id), num);
	SEEDBED_GetHarvest(sbed, id);
	FieldOBJ_SeedHarvestFlagSet(fldobj);
	return MyItem_AddItem(SaveData_GetMyItem(fsys->savedata), nuts2item(type), num, HEAPID_FIELD);
}

//============================================================================================
//============================================================================================
//-------------------------------------------------------------------------
/**
 * @brief	肥料をまく
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @param	item_compost	肥料の種類（アイテムナンバー）
 */
//-------------------------------------------------------------------------
void SeedSys_SetCompost(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_compost)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetCompost(sbed, id, item2compost(item_compost));
}

//-------------------------------------------------------------------------
/**
 * @brief	木の実を植える
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @param	item_nuts	きのみの種類（アイテムナンバー）
 */
//-------------------------------------------------------------------------
void SeedSys_SetNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_nuts)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetNuts(sbed, id, fsys->fldmap->seedsys->param, item2nuts(item_nuts));
}

//-------------------------------------------------------------------------
/**
 * @brief	水をまく
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 */
//-------------------------------------------------------------------------
void SeedSys_SetWater(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetSeedWater(sbed, id);
}

//-------------------------------------------------------------------------
/**
 * @brief	木の実の状態を取得する
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	SEEDSTAT	木の実の状態
 */
//-------------------------------------------------------------------------
SEEDSTAT SeedSys_GetSeedStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedStatus(sbed, id);
}

//-------------------------------------------------------------------------
/**
 * @brief	木の実の種類を取得する
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	u16			木の実の種類（アイテムナンバー）
 */
//-------------------------------------------------------------------------
int SeedSys_GetSeedType(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedType(sbed, id);
}
//-------------------------------------------------------------------------
/**
 * @brief	木の実の種類を取得する
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	int			木の実の種類（０～ITEM_NUTS_MAX)
 */
//-------------------------------------------------------------------------
u16 SeedSys_GetSeedTypeItem(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return nuts2item(SEEDBED_GetSeedType(sbed, id));
}

//-------------------------------------------------------------------------
/**
 * @brief	肥料の種類を取得する
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	u16			肥料の種類（アイテムナンバー）
 */
//-------------------------------------------------------------------------
u16 SeedSys_GetCompost(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return compost2item(SEEDBED_GetCompost(sbed, id));
}

//-------------------------------------------------------------------------
/**
 * @brief	水の状態を取得
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	u16
 */
//-------------------------------------------------------------------------
SEEDGROUND SeedSys_GetGroundStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetGroundStatus(sbed, id);

}

//-------------------------------------------------------------------------
/**
 * @brief	木の実の生った数を取得
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	int			生った木の実の数
 */
//-------------------------------------------------------------------------
int SeedSys_GetSeedCount(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedCount(sbed, id);

}

//============================================================================================
//============================================================================================
//
//-------------------------------------------------------------------------
/**
 * @brief	きのみに使えるどうぐのチェック
 * @param	fsys		FIELDSYS_WORKへのポインタ
 * @param	fldobj		木の実に関連付けられているFIELDOBJへのポインタ
 * @return	u32			使用可能なアイテムの情報（SEEDITEMCHK～参照）
 */
//-------------------------------------------------------------------------
u32 SeedSys_ItemUseCheck(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	u32 chk_value = 0;
	if (fldobj == NULL || FieldOBJ_OBJCodeGet(fldobj) != SEED){
		return SEEDITEMCHK_NOUSE;
	}
	switch (SeedSys_GetSeedStatus(fsys, fldobj)) {
	case SEEDSTAT_NOTHING:
		//植えられていない場合、きのみを使える
		chk_value |= SEEDITEMCHK_USE_SEED;
		if (SeedSys_GetCompost(fsys, fldobj) == 0) {
		//さらにこやしが埋められていない場合、こやしを使える
			chk_value |= SEEDITEMCHK_USE_COMPOST;
		}
		break;
	default:
		//通常、きのみが植えられているところではじょうろを使うことができる
		chk_value |= SEEDITEMCHK_USE_ZYOURO;
		break;
	}
	return chk_value;
}


//============================================================================================
//
//
//	みずやり動作イベント
//
//
//============================================================================================
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
typedef struct {
	int seq;
	int dir;
	int time_count;
	TCB_PTR tcb;
}EV_SEEDWATER_WORK;

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
enum {
	SW_SEQ_INIT = 0,
	SW_SEQ_SET,
	SW_SEQ_WAIT,
	SW_SEQ_ANIME_WAIT,
	SW_SEQ_END,
};

static const FIELD_OBJ_ACMD_LIST LeftMove[] = {
	{AC_WALK_L_16F, 1},
	{ACMD_END, 0},
};

static const FIELD_OBJ_ACMD_LIST RightMove[] = {
	{AC_WALK_R_16F, 1},
	{ACMD_END, 0},
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static BOOL HitCheck(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw, int dir)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	if (dir == DIR_LEFT) {
		gx --;
	} else if (dir == DIR_RIGHT) {
		gx ++;
	} else if (dir == DIR_UP) {
		gz --;
	} else if (dir == DIR_DOWN) {
		gz ++;
	} else {
		GF_ASSERT_MSG(0, "進行方向がおかしい！\n");
	}
	if (GetHitAttr(fsys, gx, gz)) {
		return TRUE;
	}
	return (FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz) != NULL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static FIELD_OBJ_PTR GetSlantFldObj(FIELDSYS_WORK * fsys, int move_dir)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	gz -= 1;
	if (move_dir == DIR_LEFT) {
		gx -= 1;
	} else if (move_dir == DIR_RIGHT) {
		gx += 1;
	}
	return FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static FIELD_OBJ_PTR GetFrontFldObj(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	if (esw->dir == DIR_UP) {
		gz -= 1;
	} else if (esw->dir == DIR_DOWN) {
		gz += 1;
	} else {
		GF_ASSERT_MSG(0, "自機の向きがおかしい！\n");
	}
	return FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static BOOL IsSeedObj(FIELD_OBJ_PTR fldobj)
{
	return (FieldOBJ_OBJCodeGet(fldobj) == SEED);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static void SetWater(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw)
{
	FIELD_OBJ_PTR fldobj;
	fldobj = GetFrontFldObj(fsys, esw);
	if (fldobj != NULL) {
		SeedSys_SetWater(fsys, fldobj);
	}
}

//-------------------------------------------------------------------------
/**
 */
//-------------------------------------------------------------------------
static void SetAnime(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw, const FIELD_OBJ_ACMD_LIST * anm)
{
	FIELD_OBJ_PTR pobj = Player_FieldOBJGet(fsys->player);
	esw->tcb = FieldOBJ_AcmdListSet(pobj, anm);
}

//-------------------------------------------------------------------------
/**
 */
//-------------------------------------------------------------------------
static BOOL GMEVENT_SeedWater(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SEEDWATER_WORK * esw = FieldEvent_GetSpecialWork(event);


	switch (esw->seq) {

	case SW_SEQ_INIT:
		Player_RequestSet(fsys->player, HERO_REQBIT_WATER);
		Player_Request(fsys->player);
		FieldOBJ_MovePauseClear(Player_FieldOBJGet(fsys->player));
		esw->seq = SW_SEQ_SET;
		break;

	case SW_SEQ_SET:
		SetWater(fsys, esw);
		esw->time_count = 0;
		esw->seq = SW_SEQ_WAIT;
		/* FALL THROUGH */

	case SW_SEQ_WAIT:
		if (sys.cont & PAD_KEY_LEFT) {
			FIELD_OBJ_PTR fldobj = GetSlantFldObj(fsys, DIR_LEFT);
			if (fldobj == NULL || !IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_END;
				break;
			}
			else if (!HitCheck(fsys, esw, DIR_LEFT)) {
				SetAnime(fsys, esw, LeftMove);
				esw->seq = SW_SEQ_ANIME_WAIT;
				break;
			}
		} else if (sys.cont & PAD_KEY_RIGHT) {
			FIELD_OBJ_PTR fldobj = GetSlantFldObj(fsys, DIR_RIGHT);
			if (fldobj == NULL || !IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_END;
				break;
			}
			else if (!HitCheck(fsys, esw, DIR_RIGHT)) {
				SetAnime(fsys, esw, RightMove);
				esw->seq = SW_SEQ_ANIME_WAIT;
				break;
			}
		} else if ((sys.cont & PAD_KEY_UP) && esw->dir == DIR_DOWN) {
			Player_DirSet(fsys->player, DIR_UP);
			esw->seq = SW_SEQ_END;
			break;
		} else if ((sys.cont & PAD_KEY_DOWN) && esw->dir == DIR_UP) {
			//Player_DirSet(fsys->player, DIR_DOWN);
			esw->seq = SW_SEQ_END;
			break;
		}
		esw->time_count ++;
		if (esw->time_count > 30 * 3) {
			Player_DirSet(fsys->player, esw->dir);
			esw->seq = SW_SEQ_END;
		}
		break;

	case SW_SEQ_ANIME_WAIT:
		if (FieldOBJ_AcmdListEndCheck(esw->tcb)) {
			FIELD_OBJ_PTR fldobj;
			FieldOBJ_AcmdListEnd(esw->tcb);
			fldobj = GetFrontFldObj(fsys, esw);
			if (fldobj != NULL && IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_SET;
			} else {
				Player_DirSet(fsys->player, esw->dir);
				esw->seq = SW_SEQ_END;
			}
		}
		break;

	case SW_SEQ_END:
		//自機の見た目を通常に戻す
		Player_DirSet(fsys->player, esw->dir);
		FieldOBJ_MovePause(Player_FieldOBJGet(fsys->player));
//		Player_RequestSet(fsys->player, HERO_REQBIT_NORMAL);
//		Player_Request(fsys->player);
		sys_FreeMemoryEz(esw);
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------------------
/**
 * @brief	水やりイベント呼び出し
 */
//-------------------------------------------------------------------------
void EventCall_SeedWater(FIELDSYS_WORK * fsys)
{
	EV_SEEDWATER_WORK * esw;
	esw = sys_AllocMemory(HEAPID_EVENT, sizeof(EV_SEEDWATER_WORK));
	esw->seq = 0;
	esw->tcb = NULL;
	esw->dir = Player_DirGet(fsys->player);
	FieldEvent_Call(fsys->event, GMEVENT_SeedWater, esw);
}

//-------------------------------------------------------------------------
/**
 * @brief	水やりイベント終了（自機フォームを通常に戻す）
 */
//-------------------------------------------------------------------------
void SeedSys_ResetPlayerForm(FIELDSYS_WORK * fsys)
{
	int form = Player_FormGet( fsys->player );
	u32 req_bit = Player_FormRequestGet( form );
	Player_RequestSet( fsys->player, req_bit );
	//Player_RequestSet(fsys->player, HERO_REQBIT_NORMAL);
	Player_Request(fsys->player);
}



