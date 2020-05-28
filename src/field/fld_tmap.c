/**
 *	@file	fld_tmap.c
 *	@brief	�^�E���}�b�v�p�@�t�B�[���h�풓�֐��Q
 *	@author	Miyuki Iwasawa
 *	@date	06.04.05
 */

#include "common.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "field_subproc.h"
#include "field/field.h"
#include "field/townmap_footmark.h"
#include "field/situation_local.h"
#include "field/script.h"
#include "field/syswork.h"
#include "fieldmap.h"
#include "zonedata.h"
#include "system/mystatus.h"
#include "application/townmap.h"

///�Z�[�u�t���O���p���f�[�^�\����
typedef struct {
	u8	fk01;	///<�t���O��ʃt���O
	u8	fidx01;	///<�t���O�Q�ƃC���f�b�N�X
	u8	fk02;	///<�t���O��ʃt���O
	u8	fidx02;	///<�t���O�Q�ƃC���f�b�N�X
}TMAP_FLAGS_DATA;

///�^�E���}�b�v�@�����t���O�`�F�b�N
static const u8 arrive_id[TMAP_ARRIVEDATA_MAX] = {
 FLAG_ARRIVE_T01,
 FLAG_ARRIVE_T02,
 FLAG_ARRIVE_T03,
 FLAG_ARRIVE_T04,
 FLAG_ARRIVE_T05,
 FLAG_ARRIVE_T06,
 FLAG_ARRIVE_T07,
 FLAG_ARRIVE_C01,
 FLAG_ARRIVE_C02,
 FLAG_ARRIVE_C03,
 FLAG_ARRIVE_C04,
 FLAG_ARRIVE_C05,
 FLAG_ARRIVE_C06,
 FLAG_ARRIVE_C07,
 FLAG_ARRIVE_C08,
 FLAG_ARRIVE_C09,
 FLAG_ARRIVE_C11,
 FLAG_ARRIVE_R221R0101,
 FLAG_ARRIVE_C10,
 FLAG_ARRIVE_CHAMPLEAGUE,
};

static void tmap_FlagGet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,const char* path);

/**
 *	@brief	�t�B�[���h �^�E���}�b�v���W���[���f�[�^�Z�b�g
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:�f�[�^���i�[����\���̌^�ւ̃|�C���^
 *	@param	mode	u8:�Ăяo�����[�h(enum TMAP_MODE)
 */
void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode)
{
    MYSTATUS* pMyStatus;
	int i = 0,pos = 0,ret = 0;
	int x,z,zoneID;
	TOWN_MAP_FOOTMARK * fmark;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);

	memset(tp,0,sizeof(TOWNMAP_PARAM));

	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	zoneID = World_GetZoneIDFromMatrixXZ(fsys->World,x/BLOCK_GRID_W,z/BLOCK_GRID_W);
	if(ZoneData_IsSinouField(zoneID)){
		tp->player_x = x;
		tp->player_z = z;
	}else{
		tp->player_x = escape->grid_x;
		tp->player_z = escape->grid_z;
	}
//	tp->zone_id = GetNowZoneID(fsys);

	//���@�̐���
    pMyStatus = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
	tp->player_sex = MyStatus_GetMySex(pMyStatus); 

	//���@�̈ړ����O�擾
	fmark= Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
	
	pos = (fmark->NowPoint-2+FOOTMARK_NUM)%FOOTMARK_NUM;
	for(i = 0;i < TMAP_FVIEW_MAX;i++){
		tp->foot[i].x = fmark->Param[pos].BlockX;
		tp->foot[i].z = fmark->Param[pos].BlockZ;
		tp->foot[i].valid = fmark->Param[pos].Valied;
		if(fmark->Param[pos].Dir > 3){
			tp->foot[i].dir = DIR_RIGHT+1;
		}else{
			tp->foot[i].dir = fmark->Param[pos].Dir;
		}
		pos = (pos-1+FOOTMARK_NUM)%FOOTMARK_NUM;

		if(tp->foot[i].valid){
			ret++;
		}
	}

	//�B���}�b�v�o���t���O�擾
	for(i = 0;i < 4;i++){
		if(SysWork_HideMapWorkCheck( ev, i)){
			tp->view_f |= (0x01 << i);
		}
	}
	//�����t���O�擾
	for(i = 0;i < TMAP_ARRIVEDATA_MAX;i++){
		tp->arrive[i] = SysFlag_ArriveGet( ev,arrive_id[i]);
	}

	//�e��t���O�擾
	tmap_FlagGet(fsys,tp,"data/tmap_flags.dat");
	
	tp->mode = mode;
}

/**
 *	@brief	�t���O�擾
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:�f�[�^���i�[����\���̌^�ւ̃|�C���^
 *	@param	mode	u8:�Ăяo�����[�h(enum TMAP_MODE)
 */
static void tmap_FlagGet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,const char* path)
{
	FSFile fp;
	int ret,i;
	int dat_num;
	TMAP_FLAGS_DATA *src;
	TMAP_FLAGS* wp;
	EVENTWORK* event = SaveData_GetEventWork(fsys->savedata);

	FS_InitFile(&fp);
	if(!FS_OpenFile(&fp,path)){
		OS_Printf("FS_OpenFile(\"%s\") ... ERROR!\n",path);
		GF_ASSERT(0);
		return;
	}
	//�f�[�^���擾
	ret = FS_ReadFile(&fp,&dat_num,4);
	GF_ASSERT(ret >= 0 && "ERROR:tmap flags data num can't read");
	
	//�e���|�����������m��
	src = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(TMAP_FLAGS_DATA));
	MI_CpuClear8(src,sizeof(TMAP_FLAGS_DATA));

	tp->flag_num = dat_num;	//����ۑ�

	for(i = 0;i < dat_num;i++){
		wp = &(tp->flags[i]);
		ret = FS_ReadFile(&fp,src,sizeof(TMAP_FLAGS_DATA));

		//�t���O�擾
		switch(src->fk01){
		case 1:	//�����t���O
			wp->ex01 = SysFlag_ArriveGet(event,src->fidx01);
			wp->ex01_f = 1;
			break;
		case 2:	//�X�N���v�g�t���O
			wp->ex01 = CheckEventFlag(fsys,src->fidx01);
			wp->ex01_f = 1;
			break;
		}
		switch(src->fk02){
		case 1:	//�����t���O
			wp->ex02 = SysFlag_ArriveGet(event,src->fidx02);
			wp->ex02_f = 1;
			break;
		case 2:	//�X�N���v�g�t���O
			wp->ex02 = CheckEventFlag(fsys,src->fidx02);
			wp->ex02_f = 1;
			break;
		}
	}
	(void)FS_CloseFile(&fp);
	sys_FreeMemoryEz(src);	//�e���|�������
	return;
}

