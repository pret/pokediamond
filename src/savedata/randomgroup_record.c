//============================================================================================
/**
 * @file	randomgroup_record.c
 * @brief	セーブデータ：ランダムグループのレコード処理関連
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.11
 */
//============================================================================================

#include "common.h"
#include "system/gamedata.h"

#include "savedata/randomgroup.h"
#include "randomgroup_local.h"

#include "system/pm_str.h"


static void RandomGroup_Delete(RANDOM_GROUP * rg, int id);
static void RandomGroup_Push(RANDOM_GROUP * rg, const RANDOM_SEED * rs);

//============================================================================================
//============================================================================================
#ifndef	PM_DEBUG

#define	DEBUG_RANDOM_PRINT(rg)	/* */

#else

#define	DEBUG_RANDOM_PRINT(rg)	DebugPrint(rg)
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static void DebugDump(void * address, int size, int base)
{
	int ofs;
	for (ofs = 0; ofs < size; ofs += base) {
		switch (base) {
		case 1:
			OS_TPrintf("%02x ",*((u8*)address + ofs));
			break;
		case 2:
			OS_TPrintf("%04x ",*((u16*)address + ofs));
			break;
		case 4:
			OS_TPrintf("%08x ",*((u32*)address + ofs));
			break;
		default:
			GF_ASSERT(0);
		}
	}
	OS_TPrintf("\n");
	
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static void DebugPrint(RANDOM_GROUP * rg)
{
	int i;
	OS_TPrintf("RANDOMGROUP:\n");
	for (i = 0; i < RANDOMGROUP_MAX; i++) {
		if (RandomGroup_IsNullData(&rg->group[i])) {
			OS_TPrintf("NG:");
		} else {
			OS_TPrintf("OK:");
		}
		DebugDump(&rg->group[i], sizeof(RANDOM_SEED), 2);
	}
	OS_TPrintf("\n");
}
#endif

//============================================================================================
//
//
//		混ぜるデータ生成関連
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	まぜるデータのサイズを返す
 * @param	rg
 * @return	u32
 */
//--------------------------------------------------------------------------------------------
u32 RandomGroup_GetDefaultDataSize(RANDOM_GROUP * rg)
{
	return sizeof(RANDOM_SEED);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	まぜるデータの先頭アドレスを返す
 * @param	rg
 * @return	void *	まぜるデータへのポインタ（実態は「現在使用しているランダムのタネデータ）
 */
//--------------------------------------------------------------------------------------------
void * RandomGroup_GetDefaultData(RANDOM_GROUP * rg)
{
	return &rg->group[RANDOMGROUP_MYUSE];
}


//============================================================================================
//
//		内部操作関数
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	ランダムのタネ：データ追加処理
 * @param	rg
 * @param	rs
 *
 * データを追加する。データは先頭から追加され、あふれた分は押し出し式に消えていく。
 */
//--------------------------------------------------------------------------------------------
static void RandomGroup_Push(RANDOM_GROUP * rg, const RANDOM_SEED * rs)
{
	int i;
	for (i = RANDOMGROUP_DATA3; i > RANDOMGROUP_DATA0; i --) {
		//[n] = [n-1] ... (n > 0)
		rg->group[i] = rg->group[i - 1];
	}
	// [0] = new data
	rg->group[RANDOMGROUP_DATA0] = *rs;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ランダムのタネ：削除処理
 * @param	rg
 * @param	id
 *
 * 削除した場所は詰められる。
 */
//--------------------------------------------------------------------------------------------
static void RandomGroup_Delete(RANDOM_GROUP * rg, int id)
{
	int i;
	RANDOM_SEED * rs;

	GF_ASSERT(RANDOMGROUP_DATA0 <= id && id <= RANDOMGROUP_DATA3);
	//指定箇所以下を順次繰り上げ
	for (i = id + 1; i <= RANDOMGROUP_DATA3; i++) {
		rg->group[i - 1] = rg->group[i];
	}

	//末端のDATA3を削除
	rs = &rg->group[RANDOMGROUP_DATA3];
	rs->group_name[0] = EOM_;
	rs->name[0] = EOM_;
}


//============================================================================================
//
//
//			混ぜるメイン処理
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief
 * @param	my_id
 * @param	rg
 * @param	darray
 *
 * ・「使用しているデータ」を持ち寄る。
 * ・
 */
//--------------------------------------------------------------------------------------------
void RandomGroup_RecordMix(int member, int my_id, RANDOM_GROUP * rg, const void ** darray)
{
	int i, j;
	RANDOM_SEED * rs;
	//DEBUG_RANDOM_PRINT(rg);
	for (i = 0; i < member; i++) {
		rs = (RANDOM_SEED *)darray[i];
		if (i == my_id) {
			//自分から送信されたデータの場合、パスする
			continue;
		}
		if (rs == NULL) {
			//無効データだった場合はパスする
			continue;
		}
		if (RandomGroup_IsNullData(rs) == TRUE) {
			//無効データの場合、パスする
			continue;
		}
		if (RandomGroup_Compare(rs, &rg->group[RANDOMGROUP_MINE])){
			//自分のグループと同じ場合、パスする
			continue;
		}
		for (j = 0; j < 4; j++) {
			if (RandomGroup_Compare(rs, &rg->group[RANDOMGROUP_DATA0 + j])) {
				//同じものがすでにある場合、削除→セット
				RandomGroup_Delete(rg, RANDOMGROUP_DATA0 + j);
			}
		}
		RandomGroup_Push(rg, rs);
	}
	//DEBUG_RANDOM_PRINT(rg);
}


#ifdef	PM_DEBUG
//============================================================================================
//============================================================================================
#include "system/pm_str.h"
static const STRCODE DmyGroupName1[] = { GU_,RU_,bou_,PU_,n1_,EOM_ };
static const STRCODE DmyGroupName2[] = { GU_,RU_,bou_,PU_,n2_,EOM_ };
static const STRCODE DmyGroupName3[] = { GU_,RU_,bou_,PU_,n3_,EOM_ };
static const STRCODE DmyGroupName4[] = { GU_,RU_,bou_,PU_,n4_,EOM_ };
static const STRCODE DmyGroupName5[] = { GU_,RU_,bou_,PU_,n5_,EOM_ };
static const STRCODE * const DmyGroupName[] = {
	DmyGroupName1,
	DmyGroupName2,
	DmyGroupName3,
	DmyGroupName4,
	DmyGroupName5,
};

static const STRCODE DmyLeaderName1[] = { RI_,bou_,DA_,bou_,n1_,EOM_ };
static const STRCODE DmyLeaderName2[] = { RI_,bou_,DA_,bou_,n2_,EOM_ };
static const STRCODE DmyLeaderName3[] = { RI_,bou_,DA_,bou_,n3_,EOM_ };
static const STRCODE DmyLeaderName4[] = { RI_,bou_,DA_,bou_,n4_,EOM_ };
static const STRCODE DmyLeaderName5[] = { RI_,bou_,DA_,bou_,n5_,EOM_ };
static const STRCODE * const DmyLeaderName[] = {
	DmyLeaderName1,
	DmyLeaderName2,
	DmyLeaderName3,
	DmyLeaderName4,
	DmyLeaderName5,
};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static void MakeRandomSeed(RANDOM_SEED * rs, int i)
{
	PM_strcpy(rs->group_name, DmyGroupName[i]);
	PM_strcpy(rs->name, DmyLeaderName[i]);
	rs->seed = i;
	rs->random = i;
}

//--------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------
void RandomGroup_Debug_RecordMix(SAVEDATA * sv)
{
	int i;
	const void ** array;
	RANDOM_GROUP * rg;
	RANDOM_SEED * rsp;
	rg = SaveData_GetRandomGroup(sv);
	array = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(u32) * 5);
	rsp = sys_AllocMemory(HEAPID_BASE_DEBUG, sizeof(RANDOM_SEED) * 5);
	for (i = 0; i < 5; i++) {
		MakeRandomSeed(&rsp[i], i);
		array[i] = rsp + i;
	}
	RandomGroup_RecordMix(5, 0, rg, array);
	sys_FreeMemoryEz(array);
	sys_FreeMemoryEz(rsp);
}
#endif

//--------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------

