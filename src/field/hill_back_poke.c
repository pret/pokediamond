//============================================================================================
/**
 * @file	hill_back_poke.c
 * @brief	裏山エンカウントポケモン関連処理
 * @author	Nozomu Saito
 * @date	2006.05.25
 */
//============================================================================================
#include "common.h"
#include "savedata/encount.h"
#include "arc/encdata_ex.naix"
#include "encount_define.h"

#include "system/arc_tool.h"

#include "hill_back_poke.h"

//------------------------------------------------------------------
/**
 * @brief	裏山ポケモンのセット(押し出し式でセット)
 * @param	sv		セーブデータポインタ	
 * @return	none
 */
//------------------------------------------------------------------
void HillBack_SetEncPokemon(SAVEDATA* sv)
{
	u16 idx;
	u16 idx1,idx2;
	int monsno[2];
	int *tbl;

	//裏山エンカウントテーブル取得
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
	//特殊枠ポケモンインデックス取得（2体）
	EncDataSave_GetHillBackPokeIdx(sv, &idx1, &idx2);
	//インデックスとテーブルからポケモン取得
	if (idx1 != HILL_BACK_POKE_NONE){
		monsno[0] = tbl[idx1];
	}else{
		monsno[0] = 0;
	}
	if (idx2 != HILL_BACK_POKE_NONE){
		monsno[1] = tbl[idx2];
	}else{
		monsno[1] = 0;
	}

	while(1){
		//ポケモンランダム選出
		idx = gf_p_rand(HILL_BACK_ENC_MONS_MAX);
				
		//選出したポケモンは特殊枠に登録済みか？
		if ( (monsno[0]!=tbl[idx])&&
			 (monsno[1]!=tbl[idx]) ){
			//登録済みでなければ、押し出し式で登録
			EncDataSave_SetHillBackPokeIdx(sv, idx);
			break;
		}
	}
	sys_FreeMemoryEz(tbl);
}

//------------------------------------------------------------------
/**
 * @brief	会話に出てくるポケモンのモンスターナンバーを返す
 * @param	sv		セーブデータポインタ
 * @return	int		モンスターナンバー
 */
//------------------------------------------------------------------
int HillBack_GetMonsNo(SAVEDATA* sv)
{
	int monsno;
	int *tbl;
	u16 idx1,idx2;
	EncDataSave_GetHillBackPokeIdx(sv, &idx1, &idx2);

	GF_ASSERT(idx1!=HILL_BACK_POKE_NONE);

	//裏山エンカウントテーブル取得
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
	monsno = tbl[idx1];

	sys_FreeMemoryEz(tbl);

	return monsno;
}
