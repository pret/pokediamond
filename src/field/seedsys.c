//============================================================================================
/**
 * @file	seedsys.c
 * @brief	�t�B�[���h�ł̂��̂ݐ��������Ȃ�
 * @author	tamada GAME FREAK inc.
 * @date	2006.02.09
 */
//============================================================================================

//============================================================================================
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "savedata/seedbed.h"
#include "itemtool/myitem.h"
#include "itemtool/nuts.h"

#include "seedsys.h"
#include "fieldobj.h"

#include "field_event.h"

#include "itemtool/nuts.h"

#include "fieldmap_work.h"

#include "tv_topic.h"

static void CreateDummyOBJ(FIELDSYS_WORK *fsys, SEEDSYS_WORK * ssys);
static void DeleteDummyOBJ(SEEDSYS_WORK * ssys);
//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
#define COMPOST_START_ITEMNUM	(ITEM_SUKUSUKUKOYASI)

//----------------------------------------------------------
//----------------------------------------------------------
struct SEEDSYS_WORK {
	int heapID;
	SEED_TABLE * param;
	NNSG3dRenderObj render;
	NNSG3dResMdl * model_p;
	NNSG3dResFileHeader * resfile;
};

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���̂�ID���A�C�e���i���o�[�ɕϊ�
 */
//----------------------------------------------------------
static u16 nuts2item(int type)
{
	if (type == 0) {
		return 0;
	}
	return type + NUTS_START_ITEMNUM - 1;
}
//----------------------------------------------------------
/**
 * @brief	�A�C�e���i���o�[�����̂�ID�ւ̕ϊ�
 */
//----------------------------------------------------------
static u16 item2nuts(int itemno)
{
	if (itemno == 0) {
		return 0;
	}
	return itemno - NUTS_START_ITEMNUM + 1;
}
//----------------------------------------------------------
/**
 * @brief	�R���V�w�聨�A�C�e���i���o�[�ւ̕ϊ�
 */
//----------------------------------------------------------
static u16 compost2item(SEEDCOMPOST compost)
{
	if (compost == 0) {
		return 0;
	}
	return compost + COMPOST_START_ITEMNUM - 1;
}
//----------------------------------------------------------
/**
 * @brief	�A�C�e���i���o�[���R���V�w��ւ̕ϊ�
 */
//----------------------------------------------------------
static SEEDCOMPOST item2compost(int itemno)
{
	if (itemno == 0) {
		return 0;
	}
	return itemno - COMPOST_START_ITEMNUM + 1;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���̂ݐ�������V�X�e���̐���
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	heapID		�m�ۂ���q�[�v��ID
 */
//----------------------------------------------------------
SEEDSYS_WORK * SeedSys_Init(FIELDSYS_WORK * fsys, int heapID)
{
	SEEDSYS_WORK * sys;
	sys = sys_AllocMemory(heapID, sizeof(SEEDSYS_WORK));
	MI_CpuClear8(sys, sizeof(SEEDSYS_WORK));
	sys->heapID = heapID;
	sys->param = SEEDBED_CreateParamTable(heapID);
	CreateDummyOBJ(fsys,sys);
	return sys;
}

//----------------------------------------------------------
/**
 * @brief	���̂ݐ�������V�X�e���̉��
 * @param	seedsys		SEEDSYS_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
void SeedSys_Finish(SEEDSYS_WORK * seedsys)
{
	DeleteDummyOBJ(seedsys);
	sys_FreeMemoryEz(seedsys->param);
	sys_FreeMemoryEz(seedsys);
}

//----------------------------------------------------------
/**
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	diff_minute	�����񂾎��ԁi���P�ʁj
 */
//----------------------------------------------------------
void SeedSys_Growth(FIELDSYS_WORK * fsys, int diff_minute)
{
	SEEDBED * sbed;
	SEED_TABLE * param;
	if (fsys->fldmap == NULL) {
		param = SEEDBED_CreateParamTable(HEAPID_WORLD);
		sbed = SaveData_GetSeedBed(fsys->savedata);
		SEEDBED_Growth(sbed, param, diff_minute);
		sys_FreeMemoryEz(param);
	} else {
		param = fsys->fldmap->seedsys->param;
		sbed = SaveData_GetSeedBed(fsys->savedata);
		SEEDBED_Growth(sbed, param, diff_minute);
	}
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
static void CreateDummyOBJ(FIELDSYS_WORK *fsys, SEEDSYS_WORK * ssys)
{
	FE_SYS *fes = fsys->fes;
	u32 size = FE_ArcDataSizeGet( fes, NARC_fldeff_kage_nsbmd );
	ssys->resfile = sys_AllocMemory( ssys->heapID, size );
	FE_ArcDataLoad( fes, NARC_fldeff_kage_nsbmd, ssys->resfile );
	simple_3DModelSetResFileAlready( &ssys->render, &ssys->model_p, &ssys->resfile );
}

static void DeleteDummyOBJ(SEEDSYS_WORK * ssys)
{
	FE_FreeMemory(ssys->resfile);
}

#if 0	//old
static void CreateDummyOBJ(SEEDSYS_WORK * ssys)
{
	NNS_G3dRenderObjInit( &ssys->render, ssys->model_p );
	simple_3DModelSet( ssys->heapID, "data/kage.nsbmd",
                       &ssys->render, &ssys->model_p, &ssys->resfile );
}

static void DeleteDummyOBJ(SEEDSYS_WORK * ssys)
{
	sys_FreeMemoryEz(ssys->resfile);
}
#endif

//----------------------------------------------------------
//----------------------------------------------------------
static BOOL CheckInScreen(FIELDSYS_WORK * fsys, const VecFx32 * pos)
{
	const VecFx32 scale = {FX32_ONE, FX32_ONE, FX32_ONE};
	MtxFx33 rot;
	MTX_Identity33(&rot);
	if (BB_CullingCheck3DModel(fsys->fldmap->seedsys->model_p, pos, &rot, &scale) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	���E�`�F�b�N
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 *
 * ���E�ɓ������琬���t���O��ON�ɂ���
 */
//----------------------------------------------------------
void SeedSys_CheckInScreen(FIELDSYS_WORK * fsys)
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	while (FieldOBJSys_FieldOBJSearch(fsys->fldobjsys, &fldobj, &no, FLDOBJ_STA_BIT_USE) == TRUE) {
		if (FieldOBJ_OBJCodeSeedCheck(FieldOBJ_OBJCodeGet(fldobj)) == TRUE) {
			if (CheckInScreen(fsys, FieldOBJ_VecPosPtrGet(fldobj))) {
				int id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
				SEEDBED_SetGrowthFlag(sbed, id, TRUE);
			}

		}
	}
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���݂̂��A�����邩�ǂ����̃`�F�b�N
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @retval	TRUE		���݂̂��A������
 * @retval	FALSE		���݂̂͐A�����Ȃ�
 */
//----------------------------------------------------------
BOOL SeedSys_EnableSetKinomi(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	if (fldobj == NULL) {
		return FALSE;
	}
	if (FieldOBJ_OBJCodeGet(fldobj) != SEED) {
		return FALSE;
	}
	if (SeedSys_GetSeedStatus(fsys,fldobj) != SEEDSTAT_NOTHING) {
		return FALSE;
	}
	return TRUE;
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�؂̎������n����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	BOOL		���݂̂���ꂽ���ǂ���
 */
//----------------------------------------------------------
BOOL SeedSys_TakeNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	int id, num, type;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	type = SEEDBED_GetSeedType(sbed, id);
	num = SEEDBED_GetSeedCount(sbed, id);
	//�e���r�g�s�b�N����
	TVTOPIC_Entry_TakeNuts(fsys, nuts2item(type), SEEDBED_GetSeedHP(sbed,id), num);
	SEEDBED_GetHarvest(sbed, id);
	FieldOBJ_SeedHarvestFlagSet(fldobj);
	return MyItem_AddItem(SaveData_GetMyItem(fsys->savedata), nuts2item(type), num, HEAPID_FIELD);
}

//============================================================================================
//============================================================================================
//-------------------------------------------------------------------------
/**
 * @brief	�엿���܂�
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @param	item_compost	�엿�̎�ށi�A�C�e���i���o�[�j
 */
//-------------------------------------------------------------------------
void SeedSys_SetCompost(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_compost)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetCompost(sbed, id, item2compost(item_compost));
}

//-------------------------------------------------------------------------
/**
 * @brief	�؂̎���A����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @param	item_nuts	���݂̂̎�ށi�A�C�e���i���o�[�j
 */
//-------------------------------------------------------------------------
void SeedSys_SetNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_nuts)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetNuts(sbed, id, fsys->fldmap->seedsys->param, item2nuts(item_nuts));
}

//-------------------------------------------------------------------------
/**
 * @brief	�����܂�
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 */
//-------------------------------------------------------------------------
void SeedSys_SetWater(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	SEEDBED_SetSeedWater(sbed, id);
}

//-------------------------------------------------------------------------
/**
 * @brief	�؂̎��̏�Ԃ��擾����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	SEEDSTAT	�؂̎��̏��
 */
//-------------------------------------------------------------------------
SEEDSTAT SeedSys_GetSeedStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedStatus(sbed, id);
}

//-------------------------------------------------------------------------
/**
 * @brief	�؂̎��̎�ނ��擾����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	u16			�؂̎��̎�ށi�A�C�e���i���o�[�j
 */
//-------------------------------------------------------------------------
int SeedSys_GetSeedType(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedType(sbed, id);
}
//-------------------------------------------------------------------------
/**
 * @brief	�؂̎��̎�ނ��擾����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	int			�؂̎��̎�ށi�O�`ITEM_NUTS_MAX)
 */
//-------------------------------------------------------------------------
u16 SeedSys_GetSeedTypeItem(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return nuts2item(SEEDBED_GetSeedType(sbed, id));
}

//-------------------------------------------------------------------------
/**
 * @brief	�엿�̎�ނ��擾����
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	u16			�엿�̎�ށi�A�C�e���i���o�[�j
 */
//-------------------------------------------------------------------------
u16 SeedSys_GetCompost(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return compost2item(SEEDBED_GetCompost(sbed, id));
}

//-------------------------------------------------------------------------
/**
 * @brief	���̏�Ԃ��擾
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	u16
 */
//-------------------------------------------------------------------------
SEEDGROUND SeedSys_GetGroundStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetGroundStatus(sbed, id);

}

//-------------------------------------------------------------------------
/**
 * @brief	�؂̎��̐����������擾
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	int			�������؂̎��̐�
 */
//-------------------------------------------------------------------------
int SeedSys_GetSeedCount(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	int id;
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	id = FieldOBJ_ParamGet(fldobj, FLDOBJ_PARAM_0);
	return SEEDBED_GetSeedCount(sbed, id);

}

//============================================================================================
//============================================================================================
//
//-------------------------------------------------------------------------
/**
 * @brief	���݂̂Ɏg����ǂ����̃`�F�b�N
 * @param	fsys		FIELDSYS_WORK�ւ̃|�C���^
 * @param	fldobj		�؂̎��Ɋ֘A�t�����Ă���FIELDOBJ�ւ̃|�C���^
 * @return	u32			�g�p�\�ȃA�C�e���̏��iSEEDITEMCHK�`�Q�Ɓj
 */
//-------------------------------------------------------------------------
u32 SeedSys_ItemUseCheck(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj)
{
	u32 chk_value = 0;
	if (fldobj == NULL || FieldOBJ_OBJCodeGet(fldobj) != SEED){
		return SEEDITEMCHK_NOUSE;
	}
	switch (SeedSys_GetSeedStatus(fsys, fldobj)) {
	case SEEDSTAT_NOTHING:
		//�A�����Ă��Ȃ��ꍇ�A���݂̂��g����
		chk_value |= SEEDITEMCHK_USE_SEED;
		if (SeedSys_GetCompost(fsys, fldobj) == 0) {
		//����ɂ��₵�����߂��Ă��Ȃ��ꍇ�A���₵���g����
			chk_value |= SEEDITEMCHK_USE_COMPOST;
		}
		break;
	default:
		//�ʏ�A���݂̂��A�����Ă���Ƃ���ł͂��傤����g�����Ƃ��ł���
		chk_value |= SEEDITEMCHK_USE_ZYOURO;
		break;
	}
	return chk_value;
}


//============================================================================================
//
//
//	�݂���蓮��C�x���g
//
//
//============================================================================================
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
typedef struct {
	int seq;
	int dir;
	int time_count;
	TCB_PTR tcb;
}EV_SEEDWATER_WORK;

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
enum {
	SW_SEQ_INIT = 0,
	SW_SEQ_SET,
	SW_SEQ_WAIT,
	SW_SEQ_ANIME_WAIT,
	SW_SEQ_END,
};

static const FIELD_OBJ_ACMD_LIST LeftMove[] = {
	{AC_WALK_L_16F, 1},
	{ACMD_END, 0},
};

static const FIELD_OBJ_ACMD_LIST RightMove[] = {
	{AC_WALK_R_16F, 1},
	{ACMD_END, 0},
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static BOOL HitCheck(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw, int dir)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	if (dir == DIR_LEFT) {
		gx --;
	} else if (dir == DIR_RIGHT) {
		gx ++;
	} else if (dir == DIR_UP) {
		gz --;
	} else if (dir == DIR_DOWN) {
		gz ++;
	} else {
		GF_ASSERT_MSG(0, "�i�s���������������I\n");
	}
	if (GetHitAttr(fsys, gx, gz)) {
		return TRUE;
	}
	return (FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz) != NULL);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static FIELD_OBJ_PTR GetSlantFldObj(FIELDSYS_WORK * fsys, int move_dir)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	gz -= 1;
	if (move_dir == DIR_LEFT) {
		gx -= 1;
	} else if (move_dir == DIR_RIGHT) {
		gx += 1;
	}
	return FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static FIELD_OBJ_PTR GetFrontFldObj(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw)
{
	int gx, gz;
	gx = Player_NowGPosXGet(fsys->player);
	gz = Player_NowGPosZGet(fsys->player);
	if (esw->dir == DIR_UP) {
		gz -= 1;
	} else if (esw->dir == DIR_DOWN) {
		gz += 1;
	} else {
		GF_ASSERT_MSG(0, "���@�̌��������������I\n");
	}
	return FieldOBJ_SearchGPos(fsys->fldobjsys, gx, gz);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static BOOL IsSeedObj(FIELD_OBJ_PTR fldobj)
{
	return (FieldOBJ_OBJCodeGet(fldobj) == SEED);
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static void SetWater(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw)
{
	FIELD_OBJ_PTR fldobj;
	fldobj = GetFrontFldObj(fsys, esw);
	if (fldobj != NULL) {
		SeedSys_SetWater(fsys, fldobj);
	}
}

//-------------------------------------------------------------------------
/**
 */
//-------------------------------------------------------------------------
static void SetAnime(FIELDSYS_WORK * fsys, EV_SEEDWATER_WORK * esw, const FIELD_OBJ_ACMD_LIST * anm)
{
	FIELD_OBJ_PTR pobj = Player_FieldOBJGet(fsys->player);
	esw->tcb = FieldOBJ_AcmdListSet(pobj, anm);
}

//-------------------------------------------------------------------------
/**
 */
//-------------------------------------------------------------------------
static BOOL GMEVENT_SeedWater(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SEEDWATER_WORK * esw = FieldEvent_GetSpecialWork(event);


	switch (esw->seq) {

	case SW_SEQ_INIT:
		Player_RequestSet(fsys->player, HERO_REQBIT_WATER);
		Player_Request(fsys->player);
		FieldOBJ_MovePauseClear(Player_FieldOBJGet(fsys->player));
		esw->seq = SW_SEQ_SET;
		break;

	case SW_SEQ_SET:
		SetWater(fsys, esw);
		esw->time_count = 0;
		esw->seq = SW_SEQ_WAIT;
		/* FALL THROUGH */

	case SW_SEQ_WAIT:
		if (sys.cont & PAD_KEY_LEFT) {
			FIELD_OBJ_PTR fldobj = GetSlantFldObj(fsys, DIR_LEFT);
			if (fldobj == NULL || !IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_END;
				break;
			}
			else if (!HitCheck(fsys, esw, DIR_LEFT)) {
				SetAnime(fsys, esw, LeftMove);
				esw->seq = SW_SEQ_ANIME_WAIT;
				break;
			}
		} else if (sys.cont & PAD_KEY_RIGHT) {
			FIELD_OBJ_PTR fldobj = GetSlantFldObj(fsys, DIR_RIGHT);
			if (fldobj == NULL || !IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_END;
				break;
			}
			else if (!HitCheck(fsys, esw, DIR_RIGHT)) {
				SetAnime(fsys, esw, RightMove);
				esw->seq = SW_SEQ_ANIME_WAIT;
				break;
			}
		} else if ((sys.cont & PAD_KEY_UP) && esw->dir == DIR_DOWN) {
			Player_DirSet(fsys->player, DIR_UP);
			esw->seq = SW_SEQ_END;
			break;
		} else if ((sys.cont & PAD_KEY_DOWN) && esw->dir == DIR_UP) {
			//Player_DirSet(fsys->player, DIR_DOWN);
			esw->seq = SW_SEQ_END;
			break;
		}
		esw->time_count ++;
		if (esw->time_count > 30 * 3) {
			Player_DirSet(fsys->player, esw->dir);
			esw->seq = SW_SEQ_END;
		}
		break;

	case SW_SEQ_ANIME_WAIT:
		if (FieldOBJ_AcmdListEndCheck(esw->tcb)) {
			FIELD_OBJ_PTR fldobj;
			FieldOBJ_AcmdListEnd(esw->tcb);
			fldobj = GetFrontFldObj(fsys, esw);
			if (fldobj != NULL && IsSeedObj(fldobj)) {
				esw->seq = SW_SEQ_SET;
			} else {
				Player_DirSet(fsys->player, esw->dir);
				esw->seq = SW_SEQ_END;
			}
		}
		break;

	case SW_SEQ_END:
		//���@�̌����ڂ�ʏ�ɖ߂�
		Player_DirSet(fsys->player, esw->dir);
		FieldOBJ_MovePause(Player_FieldOBJGet(fsys->player));
//		Player_RequestSet(fsys->player, HERO_REQBIT_NORMAL);
//		Player_Request(fsys->player);
		sys_FreeMemoryEz(esw);
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------------------
/**
 * @brief	�����C�x���g�Ăяo��
 */
//-------------------------------------------------------------------------
void EventCall_SeedWater(FIELDSYS_WORK * fsys)
{
	EV_SEEDWATER_WORK * esw;
	esw = sys_AllocMemory(HEAPID_EVENT, sizeof(EV_SEEDWATER_WORK));
	esw->seq = 0;
	esw->tcb = NULL;
	esw->dir = Player_DirGet(fsys->player);
	FieldEvent_Call(fsys->event, GMEVENT_SeedWater, esw);
}

//-------------------------------------------------------------------------
/**
 * @brief	�����C�x���g�I���i���@�t�H�[����ʏ�ɖ߂��j
 */
//-------------------------------------------------------------------------
void SeedSys_ResetPlayerForm(FIELDSYS_WORK * fsys)
{
	int form = Player_FormGet( fsys->player );
	u32 req_bit = Player_FormRequestGet( form );
	Player_RequestSet( fsys->player, req_bit );
	//Player_RequestSet(fsys->player, HERO_REQBIT_NORMAL);
	Player_Request(fsys->player);
}



