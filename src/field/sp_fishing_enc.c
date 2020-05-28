//=============================================================================
/**
 * @file	sp_fishing_enc.c
 * @bfief	����ނ�G���J�E���g�֘A
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
 * @brief	����ނ�̃|�C���g�`�F�b�N
 *
 * @param   inRandSeed	�����̎�
 * @param	inX			�ނ�|�C���g�w���W
 * @param	inZ			�ނ�|�C���gZ���W
 * @param	inMapW		�}�b�v�}�g���b�N�X��
 *
 * @retval  BOOL		TRUE�̂Ƃ��A����ނ�|�C���g
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

	//�T���Œʏ�G���J�E���g
	if (gf_p_rand(2) == 0){
		return FALSE;
	}
	//�����_���̎�擾
	rand_seed = RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) );
	//�ނ�|�C���g�擾
	Player_DirFrontGridPosGet( fsys->player, &x, &z );
	//�}�b�v�}�g���b�N�X�����擾
	map_w = GetWorldMapMatrixW(fsys->World);
	
	hit = FALSE;
	//�����_���̎���S����
	val[0] = (rand_seed >> 24) & 0xff;
	val[1] = (rand_seed >> 16) & 0xff;
	val[2] = (rand_seed >> 8) & 0xff;
	val[3] = rand_seed & 0xff;
	
	//����ނ�A�[�J�C�u�f�[�^���
	data = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX,
			NARC_encdata_ex_fishing_point_bin, HEAPID_FIELD);
	//�u���b�N�����擾
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
	GF_ASSERT((sep<256)&&"�敪�����I�[�o�[�@���̕��@�ł͌v�Z�ł��܂���");
	
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

	//�ނ莅�����炵�����W�����[���h�O���b�h�C���f�b�N�X�ɕϊ�
	fp_wld_idx = (map_w*BLOCK_GRID_W*z)+x;
	//4�̃|�C���g�Ɣ�r
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
 * @brief	����ނ�|�P�����̃��x�����擾
 *
 * @param   outMaxLv	�ő僌�x��
 * @param	outMinLv	�ŏ����x��		
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
 * @brief	����ނ�|�P�����̃����X�^�[�i���o�[��Ԃ�
 *
 * @param   outMonsNo	�����X�^�[�i���o�[�i�[�ꏊ
 *
 * @retval	none
 */
//------------------------------------------------------------------
void SpFishing_GetMonsNo(int *outMonsNo)
{
	int *data;
	//����ނ�A�[�J�C�u�f�[�^���
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

	//�����_���̎�擾
	rand_seed = RandomGroup_GetDefaultRandom( SaveData_GetRandomGroup(fsys->savedata) );
	*outRand = rand_seed;
	//�}�b�v�}�g���b�N�X�����擾
	map_w = GetWorldMapMatrixW(fsys->World);
	
	//�����_���̎���S����
	val[0] = (rand_seed >> 24) & 0xff;
	val[1] = (rand_seed >> 16) & 0xff;
	val[2] = (rand_seed >> 8) & 0xff;
	val[3] = rand_seed & 0xff;
	
	//����ނ�A�[�J�C�u�f�[�^���
	data = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX,
			NARC_encdata_ex_fishing_point_bin, HEAPID_FIELD);
	//�u���b�N�����擾
	block_num = ((int*)data)[0];
	
	total = 0;
	for(i=0;i<block_num;i++){
		total +=  ((int*)data)[1+i];
	}
	ary = &((u16*)data)[2+block_num*2];
	
	sep = total/FISH_POINT_MAX;
	GF_ASSERT((sep<256)&&"�敪�����I�[�o�[�@���̕��@�ł͌v�Z�ł��܂���");
	
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
