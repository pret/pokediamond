//============================================================================================
/**
 * @file	hill_back_poke.c
 * @brief	���R�G���J�E���g�|�P�����֘A����
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
 * @brief	���R�|�P�����̃Z�b�g(�����o�����ŃZ�b�g)
 * @param	sv		�Z�[�u�f�[�^�|�C���^	
 * @return	none
 */
//------------------------------------------------------------------
void HillBack_SetEncPokemon(SAVEDATA* sv)
{
	u16 idx;
	u16 idx1,idx2;
	int monsno[2];
	int *tbl;

	//���R�G���J�E���g�e�[�u���擾
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
	//����g�|�P�����C���f�b�N�X�擾�i2�́j
	EncDataSave_GetHillBackPokeIdx(sv, &idx1, &idx2);
	//�C���f�b�N�X�ƃe�[�u������|�P�����擾
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
		//�|�P���������_���I�o
		idx = gf_p_rand(HILL_BACK_ENC_MONS_MAX);
				
		//�I�o�����|�P�����͓���g�ɓo�^�ς݂��H
		if ( (monsno[0]!=tbl[idx])&&
			 (monsno[1]!=tbl[idx]) ){
			//�o�^�ς݂łȂ���΁A�����o�����œo�^
			EncDataSave_SetHillBackPokeIdx(sv, idx);
			break;
		}
	}
	sys_FreeMemoryEz(tbl);
}

//------------------------------------------------------------------
/**
 * @brief	��b�ɏo�Ă���|�P�����̃����X�^�[�i���o�[��Ԃ�
 * @param	sv		�Z�[�u�f�[�^�|�C���^
 * @return	int		�����X�^�[�i���o�[
 */
//------------------------------------------------------------------
int HillBack_GetMonsNo(SAVEDATA* sv)
{
	int monsno;
	int *tbl;
	u16 idx1,idx2;
	EncDataSave_GetHillBackPokeIdx(sv, &idx1, &idx2);

	GF_ASSERT(idx1!=HILL_BACK_POKE_NONE);

	//���R�G���J�E���g�e�[�u���擾
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_mnt_af_bin, HEAPID_FIELD);
	monsno = tbl[idx1];

	sys_FreeMemoryEz(tbl);

	return monsno;
}
