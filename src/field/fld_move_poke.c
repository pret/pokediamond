//============================================================================================
/**
 * @file	fld_move_poke.c
 * @bfief	�t�B�[���h�ړ��|�P�����֘A����
 * @author	Nozomu Saito
 * @date	06.05.13
 */
//============================================================================================
#include "savedata/encount.h"
#include "common.h"
#include "fieldsys.h"
#include "move_pokemon_def.h"
#include "move_pokemon.h"

#include "debug_saito.h"

#include "fld_move_poke.h"

static void MovePokeLocation(ENC_SV_PTR inEncData);
static void JumpMovePokeAffterBattle(ENC_SV_PTR inEncData, const int inZoneID);
static MPD_PTR GetMovePokeDataByMondNo(ENC_SV_PTR inEncData, const int inMonsNo);

//-----------------------------------------------------------------------------
/**
 * �퓬��̏���
 *
 * @param	
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FLD_MP_SetAfferBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam)
{
	u16 hp;
	u8 cond;
	int monsno;
	
	ENC_SV_PTR data;
	MPD_PTR mpd;
	POKEPARTY *poke_party;
	POKEMON_PARAM *poke_param;
	
	//�ړ��|�P�����Ɛ퓬���������`�F�b�N
	poke_party = inBattleParam->poke_party[POKEPARTY_ENEMY];
	poke_param = PokeParty_GetMemberPointer(poke_party, 0);

	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	monsno = PokeParaGet(poke_param, ID_PARA_monsno, NULL);
	mpd = GetMovePokeDataByMondNo(data, monsno);
	
	if(mpd != NULL){			//�ړ��|�P�����ƃG���J�E���g
		hp = (u16)(PokeParaGet(poke_param,ID_PARA_hp, NULL));
		cond = (u8)(PokeParaGet(poke_param,ID_PARA_condition, NULL));
		//�����Ăg�o��0�������͕ߊl�������H
		if ( ((inBattleParam->win_lose_flag==FIGHT_WIN)&&(hp == 0)) ||
			 (inBattleParam->win_lose_flag==FIGHT_POKE_GET) ) {
			//�G���J�E���g�����ړ��|�P�����f�[�^���N���A
			EncDataSave_ClearMovePokeData(&mpd);
		}else{
			//�p�����[�^�̔��f
			EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_HP, hp);
			EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_COND, cond);
		}
		//3�C�̈ړ��|�P�����̃W�����v
		JumpMovePokeAffterBattle(data, fsys->location->zone_id);

	}else{			//�ʏ�|�P�����ƃG���J�E���g
		//30���̊m���ŁA3�C�̈ړ��|�P�����̃W�����v
		if ( gf_p_rand(100)<30 ){
			JumpMovePokeAffterBattle(data, fsys->location->zone_id);
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * �퓬��̈ړ��|�P�����W�����v
 *
 * @param	
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void JumpMovePokeAffterBattle(ENC_SV_PTR inEncData, const int inZoneID)
{
	int zone;
	u8 i;
	for(i=0;i<MOVE_POKE_MAX;i++){
		//�ړ����ŁA���A��l���Ɠ����]�[���ɂ��邩�H
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			zone = MP_GetMovePokeZone(EncDataSave_GetMovePokeZoneIdx(inEncData, i));
			if (inZoneID == zone){
				//�W�����v
				MP_JumpMovePokemon(inEncData, i);
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * �����X�^�[�i���o�[����ړ��|�P�����f�[�^���擾
 *
 * @param	inMonsNo	�����X�^�[�i���o�[
 *
 * @return	MPD_PTR		�ړ��|�P�����f�[�^�|�C���^ �Ȃ��ꍇ��NULL��Ԃ�
 *
*/ 
//-----------------------------------------------------------------------------
static MPD_PTR GetMovePokeDataByMondNo(ENC_SV_PTR inEncData, const int inMonsNo)
{
	u8 i;
	MPD_PTR mpd;
	for(i=0;i<MOVE_POKE_MAX;i++){
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			mpd = EncDataSave_GetMovePokeDataPtr(inEncData, i);
			if (inMonsNo == EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO)){
				return mpd;
			}
		}
	}
	return NULL;
}
