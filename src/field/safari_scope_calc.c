//===========================================================================
/**
 * @file	safari_scope_calc.c
 * @brief	�T�t�@���]����
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#include "common.h"
#include "fieldsys.h"
#include "encount_dat.h"
#include "eventdata.h"
#include "ev_mapchange.h"
#include "zonedata.h"
#include "system/arc_tool.h"
#include "system/timezone.h"
#include "system/zukanwork.h"
#include "safari_scope_common.h"
#include "safari_scope_calc.h"
#include "enc_tbl_change_def.h"
#include "encount_set.h"
#include "savedata/encount.h"

#include "fielddata/mapmatrix/map_matrix_id.h"
#include "arc/encdata_ex.naix"

#include "safari_enc.h"
#include "agb_slot_enc.h"

#define SPOT_LIST_MAX	(36)

typedef struct SCOPE_WIEWSPOT_tag
{
	u16 X;
	u16 Z;
}SCOPE_VIEWSPOT;

typedef struct SCOPE_DATA_tag
{
	SCOPE_VIEWSPOT Spot[SCOPE_DISP_CNT+1];
	LOCATION_WORK Next;
	FIELDSYS_WORK * fsys;
	int ReturnZoneID;
}SCOPE_DATA;

//--------------------------------------------------------------------------------------------
/**
 * �]�����ɏo���|�P�����̌���
 *
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 *
 * @return	int		�����X�^�[�i���o�[
 */
//--------------------------------------------------------------------------------------------
int SSC_GetSafScpMons(FIELDSYS_WORK * fsys)
{
	u8 i;
	BOOL book_get;
	int monsno[ENC_MONS_NUM_NORMAL];
	ENCOUNT_DATA *data;
	//fsys����G���J�E���g�f�[�^���擾
	data = (ENCOUNT_DATA*)EventData_GetEncountData(fsys);

	for(i=0;i<ENC_MONS_NUM_NORMAL;i++){
		monsno[i] = data->NormalEnc[i].MonsterNo;
	}

	book_get = ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(GameSystem_GetSaveData(fsys)));

	//�T�t�@������g�Z�b�g
	SafariEnc_SetSafariEnc(	EncDataSave_GetRandSeed(
								EncDataSave_GetSaveDataPtr(fsys->savedata), ENC_RND_SEED_SAFARI),
							book_get,
							fsys->location->zone_id,
							&monsno[SP_ENC_1], &monsno[SP_ENC_2]);
	//����e�[�u�������ւ�
	EncSet_SetTimeZoneEnc(data, &monsno[TIME_ENC_1], &monsno[TIME_ENC_2]);	
	
	//�`�f�a�X���b�g�e�[�u�������ւ�
	AgbSlotEnc_SetAgbSlotEnc(data, book_get, &monsno[AGB_ENC_1], &monsno[AGB_ENC_2]);
	
	//�����_����1�C�I�o
	return monsno[gf_p_rand(ENC_MONS_NUM_NORMAL)];
}

//--------------------------------------------------------------------------------------------
/**
 * �]���������_���X�g�쐬
 *
 * @param	inHeapID	�q�[�v�h�c
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	ptr			�f�[�^�|�C���^
 */
//--------------------------------------------------------------------------------------------
SSC_SD_PTR SSC_CreateScopePointList(const int inHeapID, FIELDSYS_WORK * fsys)
{
	u8 i;
	SSC_SD_PTR ptr;
	ptr = sys_AllocMemoryLo(inHeapID, sizeof(SCOPE_DATA));
	ptr->fsys = fsys;
	//�f�[�^�����[�h
	{
		u8 no;
		SCOPE_VIEWSPOT *spot;
		spot = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, NARC_encdata_ex_safari_scope_bin, HEAPID_FIELD);
//		spot = sys_LoadFile(HEAPID_FIELD,"data/safari_scope.bin" );
		//�����_����5�ӏ��擾
		for(i=0;i<SCOPE_DISP_CNT;i++){
			no = gf_p_rand(SPOT_LIST_MAX);
			ptr->Spot[i].X = spot[no].X;
			ptr->Spot[i].Z = spot[no].Z;
//			OS_Printf("xz=%d,%d\n",spot[no].X,spot[no].Z);
		}
		//6�ڂ͖]�����̏ꏊ�i�߂��Ă���ʒu�j
		{
			ptr->Spot[SCOPE_DISP_CNT].X = Player_NowGPosXGet( fsys->player );
			ptr->Spot[SCOPE_DISP_CNT].Z = Player_NowGPosZGet( fsys->player );
			ptr->ReturnZoneID = fsys->location->zone_id;
		}
		//�f�[�^���
		sys_FreeMemoryEz(spot);
	}
	
	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * �]���������_���X�g�j��
 *
 * @param	fsys	�]�����f�[�^�|�C���^
 * 
 * @return	none	
 */
//--------------------------------------------------------------------------------------------
void SSC_RereaseScopePointList(SSC_SD_PTR ptr)
{
	sys_FreeMemoryEz(ptr);
}

//--------------------------------------------------------------------------------------------
/**
 * ���P�[�V�����Z�b�g
 *
 * @param	inNo	�]������������
 * @param	ptr		�]�����f�[�^�|�C���^
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSC_SetNextLocation(const u8 inNo, SSC_SD_PTR ptr)
{
	int zone_id;
	int block_x,block_z;

	if (inNo == 0){
		int matrix_id;
		matrix_id = MATRIX_ID_DUN0602;	///�T�t�@��
		block_x = ptr->Spot[inNo].X/32;
		block_z = ptr->Spot[inNo].Z/32;
		zone_id = GetZoneIDFromMatID(matrix_id, block_x, block_z );
	}else if (inNo == SCOPE_DISP_CNT){
		zone_id = ptr->ReturnZoneID;
	}else{
		block_x = ptr->Spot[inNo].X/32;
		block_z = ptr->Spot[inNo].Z/32;
		zone_id = World_GetZoneIDFromMatrixXZ(ptr->fsys->World, block_x, block_z);
	}
	SetLocation(&ptr->Next, zone_id, DOOR_ID_JUMP_CODE, ptr->Spot[inNo].X, ptr->Spot[inNo].Z, DIR_UP);
}

//--------------------------------------------------------------------------------------------
/**
 * �W�����v
 *
 * @param		event	�C�x���g�|�C���^
 * @param		ptr		�]�����f�[�^�|�C���^
 * @return		none
 */
//--------------------------------------------------------------------------------------------
void SSC_JumpMap(GMEVENT_CONTROL * event, SSC_SD_PTR ptr)
{
	EventCmd_MapChangeByLocation(event, &ptr->Next);
}

//--------------------------------------------------------------------------------------------
/**
 * ���̃��[�ƃV�����f�[�^�̃|�C���^��Ԃ�
 *
 * @param		ptr					�]�����f�[�^�|�C���^
 * @return		LOCATION_WORK *		���P�[�V�����f�[�^�|�C���^
 */
//--------------------------------------------------------------------------------------------
LOCATION_WORK *SSC_GetNextLocaton(SSC_SD_PTR ptr)
{
	return &ptr->Next;
}



