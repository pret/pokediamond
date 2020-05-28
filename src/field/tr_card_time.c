//============================================================================================
/**
 * @file	tr_card_time.c
 * @bfief	�g���[�i�[�J�[�h���ԍX�V
 * @author	Nozomu Saito
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "system/mystatus.h"
#include "savedata/trainercard_data.h"
#include "ev_time.h"
#include "application/trainer_card.h"
#include "tr_card_time.h"

//�o�b�W���H�X�s�[�h
#define SUB_BADGE_CORRODE	(10)

//--------------------------------------------------------------------------------------------
/**
 * �o�b�W�𕅐H�����鏈���i�P�����ɌĂ΂��j
 *
 * @param	sv				�Z�[�u�f�[�^
 * @param	diff_days		��������
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCTIME_CorrodeBadge(SAVEDATA *sv, const s32 diff_days)
{
	u8 i;
	int count;
	TR_CARD_SV_PTR trc_ptr;
	TR_BADGE_DATA_PTR badge_ptr;
	MYSTATUS *my_st;

	if (diff_days <= 0){
		return ;
	}
	
	trc_ptr = TRCSave_GetSaveDataPtr(sv);
	badge_ptr = TRCSave_GetBadgeDataPtr(trc_ptr);
	my_st = SaveData_GetMyStatus(sv);
	for(i=0;i<8;i++){
		//�����ĂȂ���Ώ������΂�
		if (MyStatus_GetBadgeFlag(my_st, i) == FALSE){
			continue;
		}
		
		count = TRCSave_GetBadgeScruchCount(i, badge_ptr);
		if ((0<count)&&(count<COUNT_LV4)){
			count -= (SUB_BADGE_CORRODE*diff_days);
		}else{
			GF_ASSERT(count<COUNT_LV4&&"BadgeLevelOver");
			count = 0;
		}

		if (count<0){
			count = 0;
		}
		TRCSave_SetBadgeScruchCount(i, count, badge_ptr);
	}
}
