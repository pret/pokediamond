//===========================================================================
/**
 * @file	ev_pokemon.c
 * @brief	�C�x���g�\�[�X�F�|�P�����֘A
 * @author	tamada GAME FREAK Inc.
 * @date	2005.12.18
 */
//===========================================================================
#include "common.h"

#include "fieldsys.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_tool.h"
#include "poketool/poke_memo.h"
#include "savedata/zukanwork.h"
#include "savedata/get_poke.h"

#include "ev_pokemon.h"
#include "battle/battle_common.h"		//CONDITION_�`
#include "sodateya.h"

#include "itemtool/itemsym.h"
//===========================================================================
//===========================================================================
#if 0
typedef void(* ITL_FUNC)(POKEMON_PARAM * poke, void *);
//------------------------------------------------------------------
/**
 * @brief	�莝���S���ւ̑�����ꊇ�ōs��
 * @param	party		�莝���|�P�����ւ̃|�C���^
 * @param	func		����֐��ւ̃|�C���^
 * @param	work		���[�N�ւ̃|�C���^
 *
 * �^�}�S�ł��Ȃ��A�C�₵�Ă����Ȃ��|�P�����ɑ΂�����֐����Ăяo���B
 * ���x�x�O���B���Ԃ񃁃����������悭�Ȃ�͂��B
 */
//------------------------------------------------------------------
void EvPoke_Itelator(POKEPARTY * party, ITL_FUNC func, void * work)
{
	int i, max;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(poke, ID_PARA_tamago_flag, NULL) != 0) {
			continue;
		}
		if (PokeParaGet(poke, ID_PARA_hp, NULL) == 0) {
			continue;
		}
		func(pp, work);
	}
}
#endif
//------------------------------------------------------------------
/**
 * @brief	�|�P�������퓬�\���ǂ����̃`�F�b�N
 * @param	pp		�Ώۃ|�P�����ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A�퓬�\
 *
 * �m���ł��^�}�S�ł��Ȃ����TRUE��Ԃ�
 */
//------------------------------------------------------------------
BOOL EvPoke_EnableBattle(POKEMON_PARAM * pp)
{
	if (PokeParaGet(pp, ID_PARA_hp, NULL) == 0) {
		return FALSE;
	}
	if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)) {
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief
 * @param	heapID
 * @param	sv
 * @param	monsno
 * @param	level
 * @param	itemno
 * @param	place_id
 * @param	ground_id
 * @retval	TRUE
 * @retval	FALSE
 */
//------------------------------------------------------------------
BOOL EvPoke_Add(int heapID, SAVEDATA * sv, u16 monsno, u8 level,
		u16 itemno, int place_id, int ground_id)
{
	BOOL result;
	POKEMON_PARAM *poke_param;
	u32 buf;
	POKEPARTY * party;
	MYSTATUS * my;

	my = SaveData_GetMyStatus(sv);
	party = SaveData_GetTemotiPokemon(sv);
	poke_param = PokemonParam_AllocWork(heapID);
	PokeParaInit(poke_param);
	PokeParaSet(poke_param, monsno, level, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
	PokeParaGetInfoSet(poke_param, my, ITEM_MONSUTAABOORU, place_id, ground_id, heapID);
	buf = itemno;
	PokeParaPut(poke_param, ID_PARA_item, &buf);
	result = PokeParty_Add(party, poke_param);
	if (result) {
		SaveData_GetPokeRegister( sv, poke_param );
	}
	sys_FreeMemoryEz(poke_param);

	return result;
}

//------------------------------------------------------------------
/**
 * @brief	�莝���Ƀ^�}�S��������
 * @param	heapID
 * @param	sv
 * @param	monsno
 * @param	eventflg
 * @param	type      ���܂ꂽ�ꏊ�^�C�v  placename.h�Q��
 * @param	index     ���܂ꂽ�ꏊindex
 * @retval	TRUE
 * @retval	FALSE
 * 
 */
//------------------------------------------------------------------
BOOL EvPoke_AddTamago(int heapID, SAVEDATA * sv, u16 monsno, u8 eventflg, PLACENAME_TYPE type, int index)
{
    int number;
    BOOL result;
	MYSTATUS *my = SaveData_GetMyStatus( sv );
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	POKEMON_PARAM* poke_param = PokemonParam_AllocWork(HEAPID_EVENT);
	PokeParaInit(poke_param);
    number = PlaceName_IndexToParamNumber( type, index);
	PokemonTamagoSet_forEvent(poke_param, monsno, eventflg, my, TRMEMO_FUSHIGI_PLACESET, number);
	result = PokeParty_Add(temoti, poke_param);
	sys_FreeMemoryEz(poke_param);
	return result;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�����ɂ킴���Z�b�g����
 * @param	party		POKEPARTY�\���̂ւ̃|�C���^
 * @param	poke_pos	�|�P�����̈ʒu�i�O�`�U�j
 * @param	waza_pos	�킴���Z�b�g����ꏊ�i�O�`�R�j
 * @param	waza_no		�킴�̎��
 */
//------------------------------------------------------------------
void EvPoke_ChangeWaza(POKEPARTY * party, int poke_pos, int waza_pos, u16 waza_no)
{
	PokeWazaSetPos(PokeParty_GetMemberPointer(party, poke_pos), waza_no, waza_pos);
}

//------------------------------------------------------------------
/**
 * @brief	�莝���|�P�����̂킴�`�F�b�N
 * @param	party		POKEPARTY�\���̂ւ̃|�C���^
 * @param	waza_no		�킴�̎��
 * @retval	0-5			�����Ă���|�P�����̈ʒu
 * @retval	0xff		�����Ă���|�P���������Ȃ�
 *
 * �莝���|�P�����Ɏw�肵���킴�������Ă�����̂����邩�ǂ�����Ԃ��B
 */
//------------------------------------------------------------------
int EvPoke_CheckWaza(POKEPARTY * party, u16 waza_no)
{
	int i, max;
	POKEMON_PARAM * poke;

	max = PokeParty_GetPokeCount(party);

	for (i = 0; i<max; i++){
		poke = PokeParty_GetMemberPointer(party, i);

		//���܂��`�F�b�N
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
			continue;
		}
		//���U���X�g����`�F�b�N
		if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza_no)
			){
			return i;		//�����Ă���|�P�����̃��X�g��̕��т�Ԃ�
			break;
		}
	}
	return 0xff;
}

//------------------------------------------------------------------
/**
 * @brief	�킦��|�P�����̐��𐔂���
 * @param	party	POKEPARTY�ւ̃|�C���^
 * @return	int		�킦��|�P�����̐�
 */
//------------------------------------------------------------------
int EvPoke_CountLivingPokemon(const POKEPARTY * party)
{
	int i, max, count;
	POKEMON_PARAM * pp;
	
	max = PokeParty_GetPokeCount(party);
	count = 0;
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			count ++;
		}
#if 0
		if (PokeParaGet(pp, ID_PARA_hp, NULL) == 0) {
			continue;
		}
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)) {
			continue;
		}
		count ++;
#endif
	}
	return count;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�e�B�̒��̐킦��|�P������Ԃ�(�擪���璲�ׂāA�n�߂Ɉ��������������Ԃ�)
 * @param	party	POKEPARTY�ւ̃|�C���^
 * @return	pp		�|�P�����p�����|�C���^
 */
//------------------------------------------------------------------
POKEMON_PARAM *EvPoke_GetLivingPokemonTop(const POKEPARTY * party)
{
	int i, max;
	POKEMON_PARAM * pp;
	
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			return pp;
		}
	}
	GF_ASSERT(0);
	return NULL;
}

//--------------------------------------------------------------
/**
 * @brief	�擪�̃|�P�����ւ̃|�C���^�擾
 * @param	party	POKEPARTY�ւ̃|�C���^
 * @return	�^�}�S���̂������擪�̃|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------
POKEMON_PARAM * EvPoke_GetPokemonTop(const POKEPARTY * party)
{
	u16 i,max;
	POKEMON_PARAM * pp;

	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == 0) {
			return pp;
		}
	}
	return NULL;
}


//------------------------------------------------------------------
/**
 * @brief	2vs2�ΐ킪�\���ǂ����`�F�b�N
 * @param	party	POKEPARTY�ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��A2vs2�ΐ�ł���
 */
//------------------------------------------------------------------
BOOL EvPoke_Enable2vs2Battle(const POKEPARTY * party)
{
	if (EvPoke_CountLivingPokemon(party) >= 2) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�莝���|�P�����S���ɃV���I�E�`�����s�I�����{�����Z�b�g
 * @param	party	POKEPARTY�ւ̃|�C���^
 *
 * �a������̍ۂɌĂяo�����
 */
//------------------------------------------------------------------
void EvPoke_SetChampionRibbon(POKEPARTY * party)
{
	int i,max;
	u8 flag = 1;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == 0) {
			PokeParaPut(pp, ID_PARA_sinou_champ_ribbon, &flag);
		}
	}
}

//===========================================================================
//===========================================================================

//------------------------------------------------------------------
/**
 * @brief	�Ń_���[�W�`�F�b�N
 * @param	party		�莝���|�P�����ւ̃|�C���^
 * @param	placeID		�n��ID
 * @retval	FLD_POISON_DEAD			�|�P�������C�₵��
 * @retval	FLD_POISON_DAMAGE		�|�P�������_���[�W���󂯂�
 * @retval	FLD_POISON_NODAMAGE		�|�P�����̓_���[�W���󂯂Ȃ�����
 */
//------------------------------------------------------------------
FLD_POISON_STAT EvPoke_PoisonDamage(POKEPARTY * party, u16 placeID)
{
	int poison_count = 0;
	int dead_count = 0;
	int i, max;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			if (PokeParaGet(pp, ID_PARA_condition, NULL) & (CONDITION_DOKUDOKU|CONDITION_DOKU)) {
				u32 hp = PokeParaGet(pp, ID_PARA_hp, NULL);
				if (hp > 1) {
					hp --;
				}
				PokeParaPut(pp, ID_PARA_hp, &hp);
				if (hp == 1) {
					dead_count ++;
					FriendCalc( pp, FRIEND_DOKU_HINSHI, placeID);	// �Ȃ��ǌv�Z
				}
				poison_count ++;
			}
		}
	}

	if (dead_count) {
		return FLD_POISON_DEAD;
	} else if (poison_count) {
		return FLD_POISON_DAMAGE;
	} else {
		return FLD_POISON_NODAMAGE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	�łɂ��C��F��
 * @param	pp			�|�P�����ւ̃|�C���^
 * @retval	TRUE		�łŋC�₵��
 * @retval	FALSE		�C�₵�Ă��Ȃ�
 *
 * �ŏ�Ԃł���HP���O�̃|�P�������ǂ��C��Ƃ݂Ȃ��B
 * ���̍ۂɃR���f�B�V�������N���A����B
 */
//------------------------------------------------------------------
BOOL EvPoke_ApprovePoisonDead(POKEMON_PARAM * pp)
{
	if ((PokeParaGet(pp, ID_PARA_condition, NULL) & (CONDITION_DOKUDOKU|CONDITION_DOKU))
			&& PokeParaGet(pp, ID_PARA_hp, NULL) == 1){
		u32 cond = 0;
		PokeParaPut(pp, ID_PARA_condition, &cond);
		return TRUE;
	}
	return FALSE;
}





