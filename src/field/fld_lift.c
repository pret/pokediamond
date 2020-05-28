//=============================================================================
/**
 * @file	fld_lift.c
 * @bfief	���t�g����(�W������)
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/snd_tool.h"
#include "include/savedata/gimmickwork.h"
#include "../fielddata/build_model/build_model_id.h"
#include "fielddata/maptable/zone_id.h"

#include "field_gimmick_def.h"

#include "fld_lift.h"

#define FLD_LIFT_DATA_HRIGHT_ID	(0)		//�g�������C���f�b�N�X

#define NORM_LIFT_DIF	(FX32_ONE)		//�����ϓ��l
#define REAGE_LIFT_DIF	(FX32_ONE*2)		//�����ϓ��l
#define LIFT_BOTTOM	(0)
#define LIFT_TOP	(1)

#define MINE_LIFT_START_Z_D24R0103	(26)
#define MINE_LIFT_START_Z_D24R0105	(32*1+16)
#define MINE_LIFT_START_Z_D24R0106	(15)
#define MINE_LIFT_START_Z_C10R0102	(15)
#define MINE_LIFT_START_Z_C10R0104	(15)
#define MINE_LIFT_START_Z_C10R0106	(15)
#define MINE_LIFT_START_Z_C10R0108	(15)
#define MINE_LIFT_START_Z_C10R0110	(23)
#define MINE_LIFT_START_Z_C10R0111	(18)

#define MINE_R0103_EX_HEIGHT_X	(10)
#define MINE_R0103_EX_HEIGHT_Z	(23)

#define MINE_R0105_EX_HEIGHT_X	(18)
#define MINE_R0105_EX_HEIGHT_Z	(32*1+12)

#define MINE_R0106_EX_HEIGHT_X	(8)
#define MINE_R0106_EX_HEIGHT_Z	(11)

#define REAGE_EX_HEIGHT_X	(3)
#define REAGE_EX_HEIGHT_Z	(11)

#define CHAMP_EX_HEIGHT_X	(3)
#define CHAMP_EX_HEIGHT_Z	(19)

#define CHAMP_ROOM_EX_HEIGHT_X	(7)
#define CHAMP_ROOM_EX_HEIGHT_Z	(8)

#define LIFT_W	(3)
#define LIFT_H	(2)

#define MINE_LIFT_LV1		(FX32_ONE*16*1)		//�z�R���t���A
#define MINE_LIFT_LV2		(FX32_ONE*16*9)		//�z�R��t���A
#define REAGE01_LIFT_LV1	(0)					//�l�V��1���t���A
#define REAGE01_LIFT_LV2	(FX32_ONE*16*10)	//�l�V��1��t���A
#define REAGE02_LIFT_LV1	(0)					//�l�V��2���t���A
#define REAGE02_LIFT_LV2	(FX32_ONE*16*5)		//�l�V��2��t���A
#define REAGE03_LIFT_LV1	(0)					//�l�V��3���t���A
#define REAGE03_LIFT_LV2	(FX32_ONE*16*5)		//�l�V��3��t���A
#define REAGE04_LIFT_LV1	(0)					//�l�V��4���t���A
#define REAGE04_LIFT_LV2	(FX32_ONE*16*5)		//�l�V��4��t���A
#define CHAMP_LIFT_LV1		(0)					//�`�����s�I���ʘH���t���A
#define CHAMP_LIFT_LV2		(FX32_ONE*16*5)		//�`�����s�I���ʘH��t���A
#define CHAMP_ROOM_LIFT_LV1	(0)					//�`�����s�I���������t���A
#define CHAMP_ROOM_LIFT_LV2	(FX32_ONE*16*15)	//�`�����s�I��������t���A

#define EX_LIFT_POS_X	( FX32_ONE*(16*19+8) )
#define EX_LIFT_POS_Y	( FX32_ONE*16 )
#define EX_LIFT_POS_Z	( FX32_ONE*(16*(32+12)+8) )


typedef enum {
	LIFT_MINE01 = 0,
	LIFT_MINE02,
	LIFT_MINE03,
	LIFT_REAGE01,
	LIFT_REAGE02,
	LIFT_REAGE03,
	LIFT_REAGE04,
	LIFT_CHAMP,
	LIFT_CHAMP_ROOM,
	LIFT_MAX,
}LIFT_LOCATION;

typedef enum {
	TYPE_NORMAL,
	TYPE_REAGE,
};

typedef struct LIFT_DATA_tag
{
	fx32	BottomTop[2];
	int		X;
	int		Z;
	BOOL	Stop;	//��ɂ���������A�������Ȃ��Ȃ邩�ǂ����@TRUE�F�������Ȃ�
	BOOL	ExpObj;	//�g���n�a�i���ǂ����@TRUE:�g���n�a�i
}LIFT_DATA;

typedef struct LIFT_WORK_tag
{
	u16		Lift;		//���t�g�̈ʒu�i�ォ�����j
	u16		Location;
	BOOL	LiftValid;	//���t�g�������邩�H	TRUE:��������
	int		Type;		//�r�d	TYPE_NORMAL:�ʏ탊�t�g�@TYPE_REAGE:���[�O���t�g 
	//Type�̓Z�[�u����K�v�͂Ȃ����ǁA�C�x���g�Ɉ����p�����߂����Ɋm�ۂ���
}LIFT_WORK;

typedef struct {
	int seq;	///<�V�[�P���X�ێ����[�N
	fx32 DstHeight;	//�ړI����
	BOOL Exp;	//�g���n�a�i���ǂ����@TRUE:�g���n�a�i
	int Type;	//	LIFT_WORK��Type�������p��
}EVENT_FLIFT_WORK;


static BOOL GMEVENT_MoveUpLift(GMEVENT_CONTROL * event);
static BOOL GMEVENT_MoveDownLift(GMEVENT_CONTROL * event);
static void FldLiftSePlay(const int inType);
static void FldLiftSeStop(const int inType);


static const LIFT_DATA LiftData[LIFT_MAX] = 
{
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0103_EX_HEIGHT_X, MINE_R0103_EX_HEIGHT_Z, FALSE, FALSE },
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0105_EX_HEIGHT_X, MINE_R0105_EX_HEIGHT_Z, FALSE, TRUE },
	{ {MINE_LIFT_LV1, MINE_LIFT_LV2}, MINE_R0106_EX_HEIGHT_X, MINE_R0106_EX_HEIGHT_Z, FALSE, FALSE },
	{ {REAGE01_LIFT_LV1, REAGE01_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE02_LIFT_LV1, REAGE02_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE03_LIFT_LV1, REAGE03_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {REAGE04_LIFT_LV1, REAGE04_LIFT_LV2}, REAGE_EX_HEIGHT_X, REAGE_EX_HEIGHT_Z, TRUE, FALSE },
	{ {CHAMP_LIFT_LV1, CHAMP_LIFT_LV2}, CHAMP_EX_HEIGHT_X, CHAMP_EX_HEIGHT_Z, TRUE, FALSE },
	{ {CHAMP_ROOM_LIFT_LV1, CHAMP_ROOM_LIFT_LV2}, CHAMP_ROOM_EX_HEIGHT_X, CHAMP_ROOM_EX_HEIGHT_Z, TRUE, FALSE },
};

//---------------------------------------------------------------------------
/**
 * @brief	���t�g:�Z�b�g�A�b�v
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLIFT_Setup(FIELDSYS_WORK *fsys)
{
	BOOL rc;
	M3DO_PTR ptr;
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	const LIFT_DATA *lift_data;
	fx32 height;

	//�����ŃM�~�b�N���[�N�̒��g������
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	lift_data = &LiftData[ lift_work->Location ];
	height = lift_data->BottomTop[lift_work->Lift];

	if(lift_data->ExpObj){
		//���t�g�̍쐬
		VecFx32 vec = {EX_LIFT_POS_X, 0,EX_LIFT_POS_Z};
		vec.y = height;
		M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
							fsys->MapResource,
							BMID_LIFT_BASE01,
							&vec, NULL,
							fsys->field_3d_anime );//<���t�g
		ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
	}else{
		//���t�g�T��
		const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
		rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
		GF_ASSERT(rc);
	}
	
	//���f����y���W�ύX
	{
		VecFx32 vec;
		vec = M3DO_GetGlobalVec(ptr);
		vec.y = height;
		M3DO_SetGlobalVec(ptr, &vec);
	}
	//
	//�����f�[�^�쐬
	EXH_SetUpExHeightData(	FLD_LIFT_DATA_HRIGHT_ID,
							lift_data->X, lift_data->Z, LIFT_W, LIFT_H,
							height,
							fsys->ExHeightList );
	
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLIFT_Init(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_FLD_LIFT);

	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	lift_work->LiftValid = TRUE;
	lift_work->Type = TYPE_NORMAL;

	//�����Ă����ꏊ��Z���W�ŁA���t�g�̈ʒu������i���邱�Ƃɂ���j
	//���n�`�Ɉˑ���������Ȃ̂ŁA�n�`���ς�����ꍇ�͒��ӂ��K�v
	switch(fsys->location->zone_id){
	case ZONE_ID_D24R0103:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0103){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE01;
		break;
	case ZONE_ID_D24R0105:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0105){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE02;
		break;
	case ZONE_ID_D24R0106:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_D24R0106){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
		}
		lift_work->Location = LIFT_MINE03;
		break;
	case ZONE_ID_C10R0102:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0102){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_REAGE01;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0104:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0104){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_REAGE02;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0106:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0106){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_REAGE03;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0108:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0108){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_REAGE04;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0110:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0110){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_CHAMP;
		lift_work->Type = TYPE_REAGE;
		break;
	case ZONE_ID_C10R0111:
		if (fsys->location->grid_z == MINE_LIFT_START_Z_C10R0111){
			lift_work->Lift = LIFT_BOTTOM;
		}else{
			lift_work->Lift = LIFT_TOP;
			lift_work->LiftValid = FALSE;	//���t�g������
		}
		lift_work->Location = LIFT_CHAMP_ROOM;
		lift_work->Type = TYPE_REAGE;
		break;
	default:
		GF_ASSERT(0);
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g�̗L�����`�F�b�N
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	u8		0:���t�g����	1:���t�g�L��
 */
//---------------------------------------------------------------------------
u8 FLIFT_CheckValid(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	if (lift_work->LiftValid){
		return 1;
	}else{
		return 0;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g:�ړ�
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	u8		0�F�C�x���g�R�[�����Ȃ�	1�F�C�x���g�R�[������
 */
//---------------------------------------------------------------------------
void FLIFT_MoveLift(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	LIFT_WORK *lift_work;
	EVENT_FLIFT_WORK * eflw;

	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	lift_work = (LIFT_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_FLD_LIFT);

	//����ʍs���t�g�����`�F�b�N(���t�g����ɂ���ꍇ�͔������Ȃ��Ȃ�)
	if ( (LiftData[lift_work->Location].Stop)&&(lift_work->Lift == LIFT_TOP) ){
		return;
	}
	
	//�C�x���g�R�[��
	eflw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_FLIFT_WORK));
	eflw->seq = 0;

	{
		eflw->Exp = LiftData[ lift_work->Location ].ExpObj;
		eflw->Type = lift_work->Type;
		if (lift_work->Lift == LIFT_BOTTOM){		//��ɍs��
			eflw->DstHeight = LiftData[lift_work->Location].BottomTop[LIFT_TOP];
			FieldEvent_Call(fsys->event, GMEVENT_MoveUpLift, eflw);
			lift_work->Lift = LIFT_TOP;
		}else{											//���ɍs��
			eflw->DstHeight = LiftData[lift_work->Location].BottomTop[LIFT_BOTTOM];
			FieldEvent_Call(fsys->event, GMEVENT_MoveDownLift, eflw);
			lift_work->Lift = LIFT_BOTTOM;
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g���グ��
 * 
 * @param	event	�C�x���g�|�C���^
 * 
 * @return	BOOL TRUE:�C�x���g�I��	FALSE:�C�x���g�p��
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveUpLift(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_FLIFT_WORK * eflw = FieldEvent_GetSpecialWork(event);

	switch (eflw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//���@�̍��������擾���I�t

		//���t�g���Đ�
		FldLiftSePlay(eflw->Type);
		(eflw->seq) ++;
		break;
	case 1:	//���t�g���㏸
		{
			if (eflw->Exp){
				//���t�gOBJ���擾
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			}else{
				const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
				BOOL rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
				GF_ASSERT(rc);
			}
			//y���W�ύX
			{
				fx32 dif;
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				if (eflw->Type == TYPE_NORMAL){
					dif = NORM_LIFT_DIF;
				}else{
					dif = REAGE_LIFT_DIF;
				}
				vec.y += dif;

				if (vec.y >= eflw->DstHeight){	//�Z�b�g�I��
					vec.y = eflw->DstHeight;
					//���t�g����~
					FldLiftSeStop(eflw->Type);
					(eflw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//���@�����ύX
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//�����Z�b�g
		EXH_SetExHeight( FLD_LIFT_DATA_HRIGHT_ID, eflw->DstHeight, fsys->ExHeightList );
		//���@�̍��������擾���I��
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );
		//���t�g�ړ��I����
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(eflw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(eflw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g��������
 * 
 * @param	event	�C�x���g�|�C���^
 * 
 * @return	BOOL TRUE:�C�x���g�I��	FALSE:�C�x���g�p��
 */
//---------------------------------------------------------------------------
static BOOL GMEVENT_MoveDownLift(GMEVENT_CONTROL * event)
{
	M3DO_PTR ptr;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_FLIFT_WORK * eflw = FieldEvent_GetSpecialWork(event);

	switch (eflw->seq) {
	case 0:
		Player_HeightGet_ON_OFF( fsys->player, FALSE );//���@�̍��������擾���I�t

		//���t�g���Đ�
		FldLiftSePlay(eflw->Type);
		(eflw->seq)	++;
		break;
	case 1:	//���t�g�����~
		{
			if (eflw->Exp){
				//���t�gOBJ���擾
				ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_LIFT_BASE01);
			}else{
				const int list[2] = {BMID_LIFT_BASE01,BMID_LEAGE_LIFT};
				BOOL rc = MPTL_CheckPluralMap3DObj( fsys, list, 2, &ptr, NULL);
				GF_ASSERT(rc);
			}
			//y���W�ύX
			{
				VecFx32 vec;
				vec = M3DO_GetGlobalVec(ptr);
				vec.y -= NORM_LIFT_DIF;
				
				if (vec.y <= eflw->DstHeight){	//�Z�b�g�I��
					vec.y = eflw->DstHeight;
					//���t�g����~
					FldLiftSeStop(eflw->Type);
					(eflw->seq) ++;
				}
				Player_VecPosYSet( fsys->player, vec.y );	//���@�����ύX
				M3DO_SetGlobalVec(ptr, &vec);
			}
		}
		break;
	case 2:	//�����Z�b�g
		EXH_SetExHeight( FLD_LIFT_DATA_HRIGHT_ID, eflw->DstHeight, fsys->ExHeightList );
		//���@�̍��������擾���I��
		Player_HeightGetSet_ON_OFF( fsys->player, TRUE );
		//���t�g�ړ��I����
		Snd_SePlay( SE_YOSUGA_GYM_LIFT );
		(eflw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(eflw);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	���t�g��
 * 
 * @param	inType		���t�g�^�C�v
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void FldLiftSePlay(const int inType)
{
	if (inType == TYPE_NORMAL){
		Snd_SePlay( SEQ_SE_DP_ELEBETA );
	}else{
		Snd_SePlay( SE_C10_LIFT );
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	���t����~
 * 
 * @param	inType		���t�g�^�C�v 
 *
 * @return	none
 */
//---------------------------------------------------------------------------
static void FldLiftSeStop(const int inType)
{
	if (inType == TYPE_NORMAL){
		Snd_SeStopBySeqNo( SEQ_SE_DP_ELEBETA, 0 );
	}else{
		Snd_SeStopBySeqNo( SE_C10_LIFT, 0 );
	}
}



