//============================================================================================
/**
 * @file	pokepark_sys.c
 * @brief	ポケパーク制御
 * @date	2006.06.08
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "savedata/pokepark_data.h"

#include "pokepark_sys.h"

#include "field_battle.h"
#include "map_tool.h"

#include "gflib/calctool.h"
#include "system/pm_rtc.h"

#include "system/arc_tool.h"
#include "../arc/ppark.naix"

#include "savedata/record.h"

#ifdef	PM_DEBUG
//#define	POKEPARK_DEBUG
#endif

//============================================================================================
//============================================================================================
//-------------------------------------------------------------
//-------------------------------------------------------------
typedef enum {
	PPENCTYPE_NOTHING = 0,

	PPENCTYPE_ZONE1,
	PPENCTYPE_ZONE2,
	PPENCTYPE_ZONE3,
	PPENCTYPE_ZONE4,

	PPENCTYPE_ZONE1_WATER,
	PPENCTYPE_ZONE2_WATER,
	PPENCTYPE_ZONE3_WATER,
	PPENCTYPE_ZONE4_WATER,
}PPENCTYPE;

//-------------------------------------------------------------
//-------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 enc_type;		///<PPENCTYPE
	u8 enc_rate;		///<エンカウント率
	u16 score;			///<捕まえたときのポイント
	u8 type1;			///<
	u8 type2;			///<
}POKE_ENC_DATA;

//-------------------------------------------------------------
//-------------------------------------------------------------
struct POKEPARK_CONTROL{
	POKE_ENC_DATA EncData[POKEPARK_MONS_MAX];
	u8 get_work[POKEPARK_MONS_MAX];
	int step_count;
	int enc_ofs;
	s64 start_time;
	int time_score;
};

enum {
	BINOFS_GROUND_ENC = 0,
	BINOFS_WATER_ENC,
	BINOFS_SCORE,
	BINOFS_ENC_RATE,
	BINOFS_TYPE1,
	BINOFS_TYPE2,
};

static POKEPARK_CONTROL PokeParkControl;


//============================================================================================
//============================================================================================

static void SetUpEncData(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl);
static void ReflectBattleResult(FIELDSYS_WORK * fsys, BATTLE_PARAM * bp, POKEPARK_CONTROL * ctrl);
static BOOL GetPokeParkEncount(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl, int x, int z);
static BATTLE_PARAM * SetBattleParam(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl);

static CountCaptured(POKEPARK_CONTROL * ctrl);
static void InitPokeParkStep(POKEPARK_CONTROL * ctrl);
static BOOL CheckPokeParkStep(POKEPARK_CONTROL * ctrl);

static u32 GetTypeScore(POKEPARK_CONTROL * ctrl);
static u32 GetCaptureScore(POKEPARK_CONTROL * ctrl);
static u32 GetTimeScore(POKEPARK_CONTROL * ctrl);
//============================================================================================
//
//			外部公開関数
//
//============================================================================================
//-------------------------------------------------------------
/**
 * @brief	ポケパーク：ゲーム開始！
 */
//-------------------------------------------------------------
void PokeParkSys_Init(FIELDSYS_WORK * fsys)
{
	int i;
	POKEPARK_CONTROL * ctrl = &PokeParkControl;

	MI_CpuClearFast(ctrl, sizeof(POKEPARK_CONTROL));
	SetUpEncData(fsys, ctrl);
	InitPokeParkStep(ctrl);
	ctrl->start_time = GF_RTC_GetDateTimeBySecond();
}

//-------------------------------------------------------------
/**
 * @brief	ポケパーク：ゲーム終了！
 */
//-------------------------------------------------------------
void PokeParkSys_Finish(FIELDSYS_WORK * fsys)
{
	POKEPARK_CONTROL * ctrl = &PokeParkControl;
	RECORD * rec = SaveData_GetRecord(fsys->savedata);
	s64 finish_time = GF_RTC_GetDateTimeBySecond();
	s64 used_time = GF_RTC_GetPassTime(ctrl->start_time, finish_time);
	if (used_time < 1000) {
		ctrl->time_score = ((1000 - used_time) * 2);
	} else {
		ctrl->time_score = 0;
	}
#if 0
		OS_TPrintf("POKEPARK:START  %d\n",ctrl->start_time);
		OS_TPrintf("POKEPARK:FINISH %d\n",finish_time);
		OS_TPrintf("POKEPARK:DIFFER %d\n", finish_time - ctrl->start_time);
		OS_TPrintf("POKEPARK:SCORE %d\n", ctrl->time_score);
#endif
	RECORD_Score_Add(rec, SCORE_ID_CLEAR_POKEPARK);
	
}

//-------------------------------------------------------------
/**
 * @brief	エンカウント判定
 */
//-------------------------------------------------------------
BOOL PokeParkSys_CheckEncount(FIELDSYS_WORK * fsys, int x, int z)
{
	if (CheckPokeParkStep(&PokeParkControl) == TRUE) {
		return GetPokeParkEncount(fsys, &PokeParkControl, x, z);
	} else {
		return FALSE;
	}
}

//-------------------------------------------------------------
/**
 * @brief	戦闘開始設定
 */
//-------------------------------------------------------------
BATTLE_PARAM * PokeParkSys_SetBattleParam(FIELDSYS_WORK * fsys)
{
	return SetBattleParam(fsys, &PokeParkControl);
}

//-------------------------------------------------------------
/**
 * @brief	戦闘結果を反映する
 */
//-------------------------------------------------------------
void PokeParkSys_ReflectBattleResult(FIELDSYS_WORK * fsys, BATTLE_PARAM * bp)
{
	ReflectBattleResult(fsys, bp, &PokeParkControl);
}

//-------------------------------------------------------------
/**
 * @brief	現在のボールの数を取得する
 */
//-------------------------------------------------------------
int PokeParkSys_GetBallCount(FIELDSYS_WORK * fsys)
{
	return POKEPARK_MONS_MAX - CountCaptured(&PokeParkControl);
}

//-------------------------------------------------------------
/**
 * @brief	ポケモンごとに固有の得点を取得
 */
//-------------------------------------------------------------
int PokeParkSys_GetCaptureScore(FIELDSYS_WORK * fsys)
{
	return GetCaptureScore(&PokeParkControl);
}
//-------------------------------------------------------------
/**
 * @brief	時間による得点を取得
 */
//-------------------------------------------------------------
int PokeParkSys_GetTimeScore(FIELDSYS_WORK * fsys)
{
	return GetTimeScore(&PokeParkControl);
}

//-------------------------------------------------------------
/**
 * @brief	ポケモンのタイプによる得点を取得
 */
//-------------------------------------------------------------
int PokeParkSys_GetTypeScore(FIELDSYS_WORK * fsys)
{
	return GetTypeScore(&PokeParkControl);
}

//============================================================================================
//============================================================================================
#ifdef	POKEPARK_DEBUG
//-------------------------------------------------------------
//-------------------------------------------------------------
static void DebugPutEncData(const POKE_ENC_DATA * enc)
{
	OS_TPrintf("POKEPARK:No.%03d POS%02d RATE%02d SCORE %02d\n",
			enc->monsno, enc->enc_type, enc->enc_rate, enc->score);
}
#endif
//-------------------------------------------------------------
//-------------------------------------------------------------
static void ReadPokeParkData(u32 monsno, u8 * data)
{
	int ofs;
	GF_ASSERT(0 < monsno && monsno <= MONSNO_END);
	ofs = (monsno - 1) * 6;
	ArchiveDataLoadOfs(data, ARC_PPARK_DATA, NARC_ppark_pokepark_bin, ofs, sizeof(u8) * 6);
}
//-------------------------------------------------------------
//-------------------------------------------------------------
static void SetUpEncData(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl)
{
	int i;
	u8 bindata[8];
	u16 monsno;
	POKEMON_PARAM * pp;
	POKEPARK_DATA * ppd;

	ppd = SaveData_GetPokeParkData(fsys->savedata);
	pp = PokemonParam_AllocWork(HEAPID_FIELD);
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		ctrl->get_work[i] = 0;
		POKEPARKDATA_CopyPokemonParam(ppd, i, pp);
		monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
		ctrl->EncData[i].monsno = monsno;
		ReadPokeParkData(monsno, bindata);
		if (bindata[BINOFS_GROUND_ENC] != 0) {
			ctrl->EncData[i].enc_type =  bindata[BINOFS_GROUND_ENC];
		} else {
			ctrl->EncData[i].enc_type = PPENCTYPE_ZONE1_WATER - 1 + bindata[BINOFS_WATER_ENC];
		}
		ctrl->EncData[i].enc_rate = bindata[BINOFS_ENC_RATE];
		ctrl->EncData[i].score = bindata[BINOFS_SCORE];
		ctrl->EncData[i].type1 = PokeParaGet(pp, ID_PARA_type1, NULL);
		ctrl->EncData[i].type2 = PokeParaGet(pp, ID_PARA_type2, NULL);
#ifdef	POKEPARK_DEBUG
		DebugPutEncData(&ctrl->EncData[i]);
#endif
	}
	sys_FreeMemoryEz(pp);

}

//-------------------------------------------------------------
/**
 * @brief	捕まえた数を数える
 */
//-------------------------------------------------------------
static CountCaptured(POKEPARK_CONTROL * ctrl)
{
	int i;
	int capture_count = 0;
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		if (ctrl->get_work[i] != 0) {
			capture_count++;
		}
	}
	return capture_count;
}

//============================================================================================
//
//		エンカウントチェック＆戦闘設定
//
//============================================================================================
//-------------------------------------------------------------
//-------------------------------------------------------------
static void InitPokeParkStep(POKEPARK_CONTROL * ctrl)
{
	ctrl->step_count = gf_p_rand(10) + 5;
#ifdef	POKEPARK_DEBUG
	OS_TPrintf("POKEPARK:STEP:%d\n",ctrl->step_count);
#endif
}

//-------------------------------------------------------------
//-------------------------------------------------------------
static BOOL CheckPokeParkStep(POKEPARK_CONTROL * ctrl)
{
	ctrl->step_count --;
	if (ctrl->step_count == 0) {
		InitPokeParkStep(ctrl);
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
static PPENCTYPE GetPokeParkEncType(FIELDSYS_WORK * fsys, int x, int z)
{
	u16 mattr = GetAttributeLSB(fsys, x, z);
	int ofs;
	ofs = (x < 32)? 0 : 1;
	ofs += (z < 32)? 0 : 2;
	if (MATR_IsGrass(mattr)) {
		return PPENCTYPE_ZONE1 + ofs;
	} else if (MATR_IsWater(mattr)) {
		return PPENCTYPE_ZONE1_WATER + ofs;
	}
	return PPENCTYPE_NOTHING;
}

//-------------------------------------------------------------
/**
 * @brief	エンカウントチェック
 */
//-------------------------------------------------------------
static BOOL GetPokeParkEncount(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl, int x, int z)
{
	int i;
	int rand, rate = 0;
	PPENCTYPE enc_type = GetPokeParkEncType(fsys, x, z);

	if (enc_type == PPENCTYPE_NOTHING) {
		return FALSE;
	}
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		if (ctrl->get_work[i] == 0 && ctrl->EncData[i].enc_type == enc_type) {
			rate += ctrl->EncData[i].enc_rate;
		}
	}
	if (rate == 0) {
		return FALSE;
	}
	rand = gf_p_rand(rate + 20);
#ifdef	POKEPARK_DEBUG
	OS_TPrintf("POKEPARK:%02d/%02d\n",rand, rate + 20);
#endif
	if (rand < 20) {
		return FALSE;
	}
	rand -= 20;
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		if (ctrl->get_work[i] == 0 && ctrl->EncData[i].enc_type == enc_type) {
			if (rand <ctrl->EncData[i].enc_rate) {
				ctrl->enc_ofs = i;
				return TRUE;
			} else {
				rand -= ctrl->EncData[i].enc_rate;
			}
		}
	}
	GF_ASSERT(0);	//ここにくることはありえないはず
	return FALSE;
}

//-------------------------------------------------------------
/**
 * @brief	戦闘結果を反映する
 */
//-------------------------------------------------------------
static void ReflectBattleResult(FIELDSYS_WORK * fsys, BATTLE_PARAM * bp, POKEPARK_CONTROL * ctrl)
{
	switch (bp->win_lose_flag) {
	case FIGHT_POKE_GET:
		ctrl->get_work[ctrl->enc_ofs] = CountCaptured(ctrl) + 1;
#ifdef	POKEPARK_DEBUG
		OS_TPrintf("POKEPARK:Caputured %d\n", ctrl->enc_ofs);
#endif
		break;
	case FIGHT_ESCAPE:
#ifdef	POKEPARK_DEBUG
		OS_TPrintf("POKEPARK:Escaped\n");
#endif
		break;
	default:
		GF_ASSERT(0);
	}

#ifdef	POKEPARK_DEBUG
	{
		int i;
		for (i = 0; i < POKEPARK_MONS_MAX; i++) {
			OS_TPrintf("[%d]%d ",i, ctrl->get_work[i]);
		}
		OS_PutString("\n");
	}
#endif
}

//-------------------------------------------------------------
/**
 * @brief	戦闘開始設定
 */
//-------------------------------------------------------------
static BATTLE_PARAM * SetBattleParam(FIELDSYS_WORK * fsys, POKEPARK_CONTROL * ctrl)
{
	BATTLE_PARAM * bp;
	POKEMON_PARAM * pp = PokemonParam_AllocWork(HEAPID_EVENT);
	POKEPARK_DATA * ppd = SaveData_GetPokeParkData(fsys->savedata);

	int ball = PokeParkSys_GetBallCount(fsys);
	bp = BattleParam_CreateForPokePark(HEAPID_WORLD, ball);
	BattleParam_SetParamByGameData(bp, fsys);
	POKEPARKDATA_CopyPokemonParam(ppd, ctrl->enc_ofs, pp);
	BattleParam_AddPokemon(bp, pp, POKEPARTY_ENEMY);
#ifdef	POKEPARK_DEBUG
	OS_TPrintf("POKEPARK:Encount %d\n",PokeParaGet(pp, ID_PARA_monsno, NULL));
#endif
	sys_FreeMemoryEz(pp);
	return bp;
}

//============================================================================================
//
//		スコア判定
//
//============================================================================================
enum {
	POINT_EACH_TYPE = 50,			///<タイプ毎の得点
	POINT_DIFFERENT_TYPE = 200,		///<前と違うタイプのときの得点
};
//-------------------------------------------------------------
//-------------------------------------------------------------
static u32 GetCaptureScore(POKEPARK_CONTROL * ctrl)
{
	int i;
	u32 score = 0;
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		score += ctrl->EncData[i].score;
	}
	return score;
}

//-------------------------------------------------------------
/**
 * @brief	ポケモンのタイプによる得点計算
 */
//-------------------------------------------------------------
static u32 GetTypeScore(POKEPARK_CONTROL * ctrl)
{
	int i, j;
	int type1, type2, new_type1, new_type2;
	u32 type_bit = 0;
	u32 score = 0;

	for (i = 1; i < POKEPARK_MONS_MAX + 1; i++) {
		for (j = 0; j < POKEPARK_MONS_MAX; j ++) {
			if (ctrl->get_work[j] == i) {
				new_type1 = ctrl->EncData[j].type1;
				new_type2 = ctrl->EncData[j].type2;
				if (i != 1	/* 一匹目は対象にならない */
						&& type1 != new_type1
						&& type1 != new_type2
						&& type2 != new_type1
						&& type2 != new_type2) {
					score += POINT_DIFFERENT_TYPE;
				}
				type1 = new_type1;
				type2 = new_type2;
				type_bit |= (1 << type1);
				type_bit |= (1 << type2);
				break;
			}
		}
	}

	for (;type_bit != 0; type_bit >>= 1) {
		if (type_bit & 1) {
			score += POINT_EACH_TYPE;
		}
	}
	return score;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
static u32 GetTimeScore(POKEPARK_CONTROL * ctrl)
{
	return ctrl->time_score;
}

