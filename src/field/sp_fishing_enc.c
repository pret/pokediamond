//=============================================================================
/**
 * @file	sp_fishing_enc.c
 * @bfief	特殊釣りエンカウント関連
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "arc/encdata_ex.naix"

#include "savedata/savedata.h"
#include "savedata/randomgroup.h" 
#include "fieldsys.h"

#include "sp_fishing_enc.h"

#define FISH_POINT_MAX	(4)

#define SP_FISH_LV_MAX	(20)
#define SP_FISH_LV_MIN	(10)

//------------------------------------------------------------------
/**
 * @brief	特殊釣りのポイントチェック
 *
 * @param   inRandSeed	乱数の種
 * @param	inX			釣りポイントＸ座標
 * @param	inZ			釣りポイントZ座標
 * @param	inMapW		マップマトリックス幅
 *
 * @retval  BOOL		TRUEのとき、特殊釣りポイント
 */
//------------------------------------------------------------------
BOOL SpFishing_CheckPoint(FIELDSYS_WORK *fsys)
{
	u8 i;
	int total;
	int sep;
	u8 rest;
	u8 ofs;

	void *data;
	u16 *ary;
	int block_num;
	int val[FISH_POINT_MAX];
	int point[FISH_POINT_MAX];
	int world_idx[FISH_POINT_MAX];
	int fp_wld_idx;
	BOOL hit;

	u32 rand_seed;
	int map_w;
	int x,z;

	//５割で通常エンカウント
	if (gf_p_rand(2) == 0){
		return FALSE;
	}
	//ランダムの種取得
	rand_seed = RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) );
	//釣りポイント取得
	Player_DirFrontGridPosGet( fsys->player, &x, &z );
	//マップマトリックス横幅取得
	map_w = GetWorldMapMatrixW(fsys->World);
	
	hit = FALSE;
	//ランダムの種を４分割
	val[0] = (rand_seed >> 24) & 0xff;
	val[1] = (rand_seed >> 16) & 0xff;
	val[2] = (rand_seed >> 8) & 0xff;
	val[3] = rand_seed & 0xff;
	
	//特殊釣りアーカイブデータ解析
	data = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX,
			NARC_encdata_ex_fishing_point_bin, HEAPID_FIELD);
	//ブロック数を取得
	block_num = ((int*)data)[0];
OS_Printf("b_num = %d\n",block_num);
	
	total = 0;
	for(i=0;i<block_num;i++){
		total +=  ((int*)data)[1+i];
	}
OS_Printf("total = %d\n",total);

	ary = &((u16*)data)[2+block_num*2];
	
OS_Printf("d = %d\n",ary[0]);

	sep = total/FISH_POINT_MAX;
	GF_ASSERT((sep<256)&&"区分数をオーバー　この方法では計算できません");
	
	rest = total%FISH_POINT_MAX;
	ofs = 0;

	for (i=0;i<FISH_POINT_MAX;i++){
		point[i] = sep*i+(val[i]%sep)+ofs;
OS_Printf("point= %d\n",point[i]);
		world_idx[i] = ary[ point[i] ];
OS_Printf("world= %d\n",world_idx[i]);
		if (rest != 0){
			ofs++;
			rest--;
		}
	}

	//釣り糸をたらした座標をワールドグリッドインデックスに変換
	fp_wld_idx = (map_w*BLOCK_GRID_W*z)+x;
	//4つのポイントと比較
	for(i=0;i<FISH_POINT_MAX;i++){
		if (world_idx[i] == fp_wld_idx){
			hit = TRUE;
			break;
		}
	}

	sys_FreeMemoryEz(data);

	return hit;
}

//------------------------------------------------------------------
/**
 * @brief	特殊釣りポケモンのレベル幅取得
 *
 * @param   outMaxLv	最大レベル
 * @param	outMinLv	最小レベル		
 *
 * @retval  none
 */
//------------------------------------------------------------------
void SpFishing_GetMaxMinLv(u8 *outMaxLv, u8 *outMinLv)
{
	(*outMaxLv) = SP_FISH_LV_MAX;
	(*outMinLv) = SP_FISH_LV_MIN;
}

//------------------------------------------------------------------
/**
 * @brief	特殊釣りポケモンのモンスターナンバーを返す
 *
 * @param   outMonsNo	モンスターナンバー格納場所
 *
 * @retval	none
 */
//------------------------------------------------------------------
void SpFishing_GetMonsNo(int *outMonsNo)
{
	int *data;
	//特殊釣りアーカイブデータ解析
	data = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX,
			NARC_encdata_ex_fish_bin, HEAPID_FIELD);
	(*outMonsNo) = (*data);

	sys_FreeMemoryEz(data);
}

#ifdef PM_DEBUG

void  DEBUGSpFishing_GetPoint(FIELDSYS_WORK *fsys, int *outPos, u32 *outRand)
{
	u8 i;
	int total;
	int sep;
	u8 rest;
	u8 ofs;

	void *data;
	u16 *ary;
	int block_num;
	int val[FISH_POINT_MAX];
	int point[FISH_POINT_MAX];
	int world_idx[FISH_POINT_MAX];

	u32 rand_seed;
	int map_w;

	//ランダムの種取得
	rand_seed = RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) );
	*outRand = rand_seed;
	//マップマトリックス横幅取得
	map_w = GetWorldMapMatrixW(fsys->World);
	
	//ランダムの種を４分割
	val[0] = (rand_seed >> 24) & 0xff;
	val[1] = (rand_seed >> 16) & 0xff;
	val[2] = (rand_seed >> 8) & 0xff;
	val[3] = rand_seed & 0xff;
	
	//特殊釣りアーカイブデータ解析
	data = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX,
			NARC_encdata_ex_fishing_point_bin, HEAPID_FIELD);
	//ブロック数を取得
	block_num = ((int*)data)[0];
	
	total = 0;
	for(i=0;i<block_num;i++){
		total +=  ((int*)data)[1+i];
	}
	ary = &((u16*)data)[2+block_num*2];
	
	sep = total/FISH_POINT_MAX;
	GF_ASSERT((sep<256)&&"区分数をオーバー　この方法では計算できません");
	
	rest = total%FISH_POINT_MAX;
	ofs = 0;

	for (i=0;i<FISH_POINT_MAX;i++){
		point[i] = sep*i+(val[i]%sep)+ofs;
		world_idx[i] = ary[ point[i] ];

		outPos[(i*2)] = world_idx[i]%(map_w*BLOCK_GRID_W);//x
		outPos[(i*2)+1] = world_idx[i]/(map_w*BLOCK_GRID_W);//z
		
		if (rest != 0){
			ofs++;
			rest--;
		}
	}

	sys_FreeMemoryEz(data);
}


#endif
