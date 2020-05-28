//============================================================================================
/**
 * @file	move_pokemon.c
 * @bfief	�ړ��|�P�����֘A����
 * @author	Nozomu Saito
 * @date	06.05.11
 */
//============================================================================================
#define	BRANCH_MAX		(5)

#define MOVE_POKE_AI_LV			(50)
#define MOVE_POKE_MUUBASU_LV	(50)
#define MOVE_POKE_DAAKU_LV		(40)

#include "common.h"
#include "fielddata/maptable/zone_id.h"
#include "savedata/encount.h"
#include "savedata/mystatus.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"

#include "move_pokemon_def.h"
#include "move_pokemon.h"

#ifdef PM_DEBUG
#include "field_common.h"
#endif

#include "debug_saito.h"

static void JumpMovePokeLocation(	ENC_SV_PTR data, const u8 inTargetPoke,
									const int inPlayerOldZone);
static void MovePokeLocation(ENC_SV_PTR data, const u8 inTargetPoke, const int inPlayerOldZone);
static void UpdateData(	ENC_SV_PTR data,
						const u8 inTargetPoke,
						const u8  inZoneIdx, const int inZone);
typedef struct MP_LOC_DATA_tag
{
	u16 BranchNum;
	u16 ZoneIdx[BRANCH_MAX];
}MP_LOC_DATA;

static const MP_LOC_DATA MovePokeLocationTbl[LOCATION_MAX] =
{
	{2,{1,23,0xffff,0xffff,0xffff}},
	{5,{0,2,3,22,23}},
	{4,{1,3,8,22,0xffff}},
	{4,{1,2,4,22,0xffff}},
	{2,{3,5,0xffff,0xffff,0xffff}},
	{4,{4,6,27,28,0xffff}},
	{3,{5,7,9,0xffff,0xffff}},
	{3,{6,8,13,0xffff,0xffff}},
	{3,{2,7,9,0xffff,0xffff}},
	{3,{8,10,15,0xffff,0xffff}},
	{3,{9,11,15,0xffff,0xffff}},
	{3,{10,12,19,0xffff,0xffff}},
	{2,{11,14,0xffff,0xffff,0xffff}},
	{4,{6,7,14,20,0xffff}},
	{3,{12,13,20,0xffff}},
	{3,{9,10,16,0xffff,0xffff}},
	{2,{15,17,0xffff,0xffff,0xffff}},
	{3,{16,18,26,0xffff,0xffff}},
	{3,{17,19,26,0xffff,0xffff}},
	{2,{11,18,0xffff,0xffff,0xffff}},
	{3,{13,14,21,0xffff,0xffff}},
	{1,{20,0xffff,0xffff,0xffff,0xffff}},
	{3,{1,2,3,0xffff,0xffff}},
	{3,{0,1,24,0xffff,0xffff}},
	{2,{23,25,0xffff,0xffff,0xffff}},
	{1,{24,0xffff,0xffff,0xffff,0xffff}},
	{2,{17,18,0xffff,0xffff,0xffff}},
	{1,{5,0xffff,0xffff,0xffff,0xffff}},
	{1,{5,0xffff,0xffff,0xffff,0xffff}},
};

static const int ZoneTbl[LOCATION_MAX] = {
	ZONE_ID_R201,		//0
	ZONE_ID_R202,		//1
	ZONE_ID_R203,		//2
	ZONE_ID_R204A,		//3
	ZONE_ID_R204B,		//4
	ZONE_ID_R205A,		//5
	ZONE_ID_R205B,		//6
	ZONE_ID_R206,		//7
	ZONE_ID_R207,		//8
	ZONE_ID_R208,		//9
	ZONE_ID_R209,		//10
	ZONE_ID_R210A,		//11
	ZONE_ID_R210B,		//12
	ZONE_ID_R211A,		//13
	ZONE_ID_R211B,		//14
	ZONE_ID_R212A,		//15
	ZONE_ID_R212B,		//16
	ZONE_ID_R213,		//17
	ZONE_ID_R214,		//18
	ZONE_ID_R215,		//19
	ZONE_ID_R216,		//20
	ZONE_ID_R217,		//21
	ZONE_ID_R218,		//22
	ZONE_ID_R219,		//23
	ZONE_ID_W220,		//24
	ZONE_ID_R221,		//25
	ZONE_ID_R222,		//26
	ZONE_ID_D02,		//27
	ZONE_ID_D04,		//28
};

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P�����W�����v
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
void MP_JumpMovePokemon(ENC_SV_PTR inEncData, const u8 inTarget)
{
	int player_old_zone;
	player_old_zone = EncDataSave_GetPlayerOldZone(inEncData);
	JumpMovePokeLocation(inEncData, inTarget, player_old_zone);
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P�����S���W�����v
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
void MP_JumpMovePokemonAll(ENC_SV_PTR inEncData)
{
	u8 i;
	for(i=0;i<MOVE_POKE_MAX;i++){
		//�ړ������H
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			//�W�����v
			MP_JumpMovePokemon(inEncData, i);
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * �ړ��|�P�����̗אڈړ�
 *
 * @param	
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void MP_MovePokemonNeighboring(ENC_SV_PTR inEncData)
{
	
	u8 i;
	for(i=0;i<MOVE_POKE_MAX;i++){
		//�ړ������H
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			//16����1�̊m���ŃW�����v
			if (gf_p_rand(16) == 0){
				OS_Printf_saitou("%d:�W�����v���܂�\n",i);
				//�W�����v
				MP_JumpMovePokemon(inEncData, i);
				
			}else{
				OS_Printf_saitou("%d:�אڈړ����܂�\n",i);
				//�אڈړ�
				{
					int player_old_zone;
					player_old_zone = EncDataSave_GetPlayerOldZone(inEncData);
					MovePokeLocation(inEncData, i, player_old_zone);
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P�����]�[���擾
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
int MP_GetMovePokeZone(const u8 inIndex)
{
	GF_ASSERT(inIndex<LOCATION_MAX);
	return ZoneTbl[inIndex];
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P���������邩���`�F�b�N
 *
 * @param	sv		�Z�[�u�f�[�^�|�C���^
 *
 * @return BOOL		TRUE:����	FALSE:���Ȃ�
 */
//--------------------------------------------------------------------------------------------
BOOL MP_CheckMovePoke(ENC_SV_PTR inEncData)
{
	u8 i;
	for(i=0;i<MOVE_POKE_MAX;i++){
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ��l���]�[�������̍X�V
 *
 * @param	inEncData		�G���J�E���g�֘A�Z�[�u�f�[�^�|�C���^
 * @param	inZone			�X�V�]�[��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MP_UpdatePlayerZoneHist(ENC_SV_PTR inEncData, const int inZone)
{
	if (MP_CheckMovePoke(inEncData)){
		//�����X�V
		EncDataSave_UpdatePlayerZoneHist( inEncData, inZone );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �w��ړ��|�P������o�^
 *
 * @param	
 * @param	
 * 
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MP_AddMovePoke(SAVEDATA *sv, const u8 inTargetPoke)
{
	POKEMON_PARAM *poke_param;
	MPD_PTR	 mpd;
	ENC_SV_PTR data;
	int player_old_zone;
	MYSTATUS * my_st;

	int monsno;
	u8 lv;
	
	data = EncDataSave_GetSaveDataPtr(sv);
	mpd = EncDataSave_GetMovePokeDataPtr(data, inTargetPoke);
	
	switch(inTargetPoke){
	case MOVE_POKE_AI:
		monsno = MONSNO_AI;
		lv = MOVE_POKE_AI_LV;
		break;
	case MOVE_POKE_MUUBASU:
		monsno = MONSNO_MUUBASU;
		lv = MOVE_POKE_MUUBASU_LV;
		break;
	case MOVE_POKE_DAAKU:
		monsno = MONSNO_DAAKU;
		lv = MOVE_POKE_DAAKU_LV;
		break;
	default:
		GF_ASSERT(0);
		return ;
	}

	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_MONSNO, monsno);
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_LV, lv);
	
	my_st =  SaveData_GetMyStatus(sv);

	poke_param = PokemonParam_AllocWork(HEAPID_FIELD);
	PokeParaInit(poke_param);
#ifdef MOVE_POKE_RARE
	PokeParaSet(poke_param, monsno, lv, POW_RND, RND_SET, 0, ID_SET, 0);
#else
	PokeParaSet(poke_param, monsno, lv, POW_RND, RND_NO_SET, 0, ID_SET, MyStatus_GetID_Low(my_st));
#endif

	//��Ԉُ�
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_COND, 0);
	//�G���J�E���g�t���O
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_ENC, 1);
	//�p���[����
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_POW_RND,
											PokeParaGet( poke_param, ID_PARA_power_rnd, NULL ));
	//������
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_PER_RND,
											PokeParaGet( poke_param, ID_PARA_personal_rnd, NULL ));
	//�g�o
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_HP,
											PokeParaGet( poke_param, ID_PARA_hpmax, NULL ));

	sys_FreeMemoryEz(poke_param);

	//����ړ��|�P�����o���ꏊ����
	player_old_zone = EncDataSave_GetPlayerOldZone(data);
	JumpMovePokeLocation(data, inTargetPoke, player_old_zone);
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P�����o���ꏊ���I
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void JumpMovePokeLocation(ENC_SV_PTR data, const u8 inTargetPoke, const int inPlayerOldZone)
{
	u8 zone_idx;
	int move_poke_now_zone;
	int zone;
	//��l�����O�X�񂢂��]�[����
	//������������ꏊ�͑ΏۊO�Ƃ���
	move_poke_now_zone = ZoneTbl[EncDataSave_GetMovePokeZoneIdx(data,inTargetPoke)];
	while(1){
		zone_idx = gf_p_rand(LOCATION_MAX);
		zone = ZoneTbl[zone_idx];
		if ((zone != inPlayerOldZone)&&(zone != move_poke_now_zone)){
			UpdateData(	data, inTargetPoke, zone_idx, zone);
			OS_Printf_saitou("%d�փW�����v player_old_zone:%d\n",zone,inPlayerOldZone);
			break;
		}
	}	
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ��|�P�����אڈړ�
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void MovePokeLocation(ENC_SV_PTR data, const u8 inTargetPoke, const int inPlayerOldZone)
{
	const MP_LOC_DATA *loc_data;
	u8 zone_idx;
	int zone;
	loc_data = &(MovePokeLocationTbl[EncDataSave_GetMovePokeZoneIdx(data,inTargetPoke)]);
	
	if (loc_data->BranchNum == 1){	//�ψڐ悪1�����Ȃ��ꍇ
		zone_idx = loc_data->ZoneIdx[0];
		zone = ZoneTbl[zone_idx];
		if (zone == inPlayerOldZone){	//��l���̑O�X��̃]�[����������A�W�����v
			OS_Printf_saitou("��l���̋����W�������̂ŃW�����v�ɕύX\n");
			JumpMovePokeLocation(data, inTargetPoke, inPlayerOldZone);
		}else{
			OS_Printf_saitou("%d:%d�ɗאڈړ�\n",inTargetPoke,zone);
			UpdateData(	data, inTargetPoke, zone_idx, zone);
		}
	}else{							//�ψڐ悪��������ꍇ
		u8 idx;
		while(1){
			//�אڏꏊ�������_���Ō���
			idx = gf_p_rand(loc_data->BranchNum);
			zone_idx = loc_data->ZoneIdx[idx];
			zone = ZoneTbl[zone_idx];
			//��l���̑O�X�񂢂��]�[���ȊO��I�o���Ĉړ�
			if (zone != inPlayerOldZone){
				OS_Printf_saitou("%d:%d�ɗאڈړ�\n",inTargetPoke,zone);
				UpdateData(	data, inTargetPoke, zone_idx, zone);
				break;
			}
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�X�V
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void UpdateData(	ENC_SV_PTR data,
						const u8 inTargetPoke,
						const u8  inZoneIdx, const int inZone)
{
	MPD_PTR mpd;
	mpd = EncDataSave_GetMovePokeDataPtr(data, inTargetPoke);
	//�X�V
	EncDataSave_SetMovePokeZoneIdx(data,inTargetPoke,inZoneIdx);
	//�ړ��|�P�����f�[�^������������
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_ZONE_ID, inZone);
}

#ifdef PM_DEBUG
//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�X�V
 *
 * @param	
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
void MP_DebugUpdateData(	ENC_SV_PTR data,
						const u8 inTargetPoke,
						const u8  inZoneIdx)
{
	MPD_PTR mpd;
	mpd = EncDataSave_GetMovePokeDataPtr(data, inTargetPoke);
	//�X�V
	EncDataSave_SetMovePokeZoneIdx(data,inTargetPoke,inZoneIdx);
	//�ړ��|�P�����f�[�^������������
	EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_ZONE_ID, ZoneTbl[inZoneIdx]);
}
#endif
