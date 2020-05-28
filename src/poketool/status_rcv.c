//============================================================================================
/**
 * @file	status_rcv.c
 * @brief	�A�C�e���g�p���̃|�P�����񕜏���
 * @author	Hiroyuki Nakamura
 * @date	05.12.01
 */
//============================================================================================
#include "common.h"
#include "battle/battle_common.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"
#include "itemtool/item.h"

#define	STATUS_RCV_H_GLOBAL
#include "poketool/status_rcv.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	TEMP_BUFLEN		( 8 )		// �v�Z�p���[�N��

#define RCV_25PER		( 253 )		// 25%��
#define RCV_HALF		( 254 )		// ����
#define RCV_ALL			( 255 )		// �S��

#define PP_RCV_ALL		( 127 )		// PP�S��

#define	PRMEXP_MAX		( 510 )		// �w�͒l�̍��v�̍ő�l
#define	ITEM_PRMEXP_MAX	( 100 )		// ����ŃA�b�v����w�͒l�̍ő�l

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static u8 PP_RcvCheck( POKEMON_PARAM * pp, u32 pos );
static u8 PP_Recover( POKEMON_PARAM * pp, u32 pos, u32 rcv );
static u8 PP_Up( POKEMON_PARAM * pp, u32 pos, u32 cnt );
static void HP_Recover( POKEMON_PARAM * pp, u32 hp, u32 max, u32 rcv );
static s32 PrmExp_Up( s32 exp, s32 other, s32 up );
static u8 Friend_Up( POKEMON_PARAM * pp, s32 now, s32 prm, u16 place, u32 heap );
static u8 Friend_UpCheck( POKEMON_PARAM * pp, ITEMDATA * dat );


//--------------------------------------------------------------------------------------------
/**
 * ����g�p�`�F�b�N���� ( POKEMON_PARAM )
 *
 * @param	pp			�񕜂���|�P�����̃f�[�^
 * @param	item		�g�p����A�C�e��
 * @param	pos			�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	heap_id		�q�[�vID
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
u8 StatusRecoverCheck( POKEMON_PARAM * pp, u16 item, u16 pos, u32 heap_id )
{
	ITEMDATA * dat;
	s32	tmp[TEMP_BUFLEN];

	dat = GetItemArcData( item, ITEM_GET_DATA, heap_id );

	// ���[�N�^�C�v���`�F�b�N
	if( ItemBufParamGet( dat, ITEM_PRM_W_TYPE ) != 1 ){
		sys_FreeMemoryEz( dat );
		return FALSE;
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_condition, NULL );

	// �����
	if( ItemBufParamGet( dat, ITEM_PRM_SLEEP_RCV ) != 0 ){
		if( ( tmp[0] & CONDITION_NEMURI ) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}
	// �ŉ�
	if( ItemBufParamGet( dat, ITEM_PRM_POISON_RCV ) != 0 ){
		if( ( tmp[0] & (CONDITION_DOKU|CONDITION_DOKUDOKU) ) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}
	// �Ώ���
	if( ItemBufParamGet( dat, ITEM_PRM_BURN_RCV ) != 0 ){
		if( ( tmp[0] & CONDITION_YAKEDO ) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}
	// �X��
	if( ItemBufParamGet( dat, ITEM_PRM_ICE_RCV ) != 0 ){
		if( ( tmp[0] & CONDITION_KOORI ) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}
	// ��჉�
	if( ItemBufParamGet( dat, ITEM_PRM_PARALYZE_RCV ) != 0 ){
		if( ( tmp[0] & CONDITION_MAHI ) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_hp, NULL );

	// �m���� or �S���m����
	if( ( ItemBufParamGet( dat, ITEM_PRM_DEATH_RCV ) != 0 ||
		  ItemBufParamGet( dat, ITEM_PRM_ALL_DEATH_RCV ) != 0 )
		 && ItemBufParamGet( dat, ITEM_PRM_LV_UP ) == 0 ){

		if( tmp[0] == 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	// HP��
	}else if( ItemBufParamGet( dat, ITEM_PRM_HP_RCV ) != 0 ){
		if( tmp[0] != 0 && tmp[0] < PokeParaGet( pp, ID_PARA_hpmax, NULL ) ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}

	// ���x���A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_LV_UP ) != 0 ){
		if( PokeParaGet( pp, ID_PARA_level, NULL ) < 100 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}

	// �i��
	if( ItemBufParamGet( dat, ITEM_PRM_EVOLUTION ) != 0 ){
		if( PokeShinkaCheck( NULL, pp, ITEM_SHINKA_CHECK, item ,NULL) != 0 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}

	// PP�A�b�v or PP�A�b�v�i�R�i�K�j
	if( ItemBufParamGet( dat, ITEM_PRM_PP_UP ) != 0 ||
		ItemBufParamGet( dat, ITEM_PRM_PP_3UP ) != 0 ){

		if( PokeParaGet( pp, ID_PARA_pp_count1+pos, NULL ) < 3 &&
			WT_PPMaxGet( PokeParaGet(pp,ID_PARA_waza1+pos,NULL), 0 ) >= 5 ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}

	// PP��
	if( ItemBufParamGet( dat, ITEM_PRM_PP_RCV ) != 0 ){
		if( PP_RcvCheck( pp, pos ) == TRUE ){
			sys_FreeMemoryEz( dat );
			return TRUE;
		}
	}
	// PP�񕜁i�S�Ă̋Z�j
	if( ItemBufParamGet( dat, ITEM_PRM_ALL_PP_RCV ) != 0 ){
		for( tmp[0]=0; tmp[0]<4; tmp[0]++ ){
			if( PP_RcvCheck( pp, tmp[0] ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_hp_exp, NULL );
	tmp[1] = PokeParaGet( pp, ID_PARA_pow_exp, NULL );
	tmp[2] = PokeParaGet( pp, ID_PARA_def_exp, NULL );
	tmp[3] = PokeParaGet( pp, ID_PARA_agi_exp, NULL );
	tmp[4] = PokeParaGet( pp, ID_PARA_spepow_exp, NULL );
	tmp[5] = PokeParaGet( pp, ID_PARA_spedef_exp, NULL );

	// HP�w�͒l�A�b�v
	if( PokeParaGet( pp, ID_PARA_monsno, NULL ) != MONSNO_NUKENIN ){
		if( ItemBufParamGet( dat, ITEM_PRM_HP_EXP ) != 0 ){
			tmp[6] = ItemBufParamGet( dat, ITEM_PRM_HP_EXP_POINT );
			OS_Printf( "HP EXP : now = %d, prm = %d\n", tmp[0], tmp[6] );
			if( tmp[6] > 0 ){
				if( tmp[0] < ITEM_PRMEXP_MAX &&
					(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
					sys_FreeMemoryEz( dat );
					return TRUE;
				}
			}else if( tmp[6] < 0 ){
				if( tmp[0] > 0 ){
					sys_FreeMemoryEz( dat );
					return TRUE;
				}
				if( Friend_UpCheck( pp, dat ) == TRUE ){
					sys_FreeMemoryEz( dat );
					return TRUE;
				}
			}
		}
	}
	// �U���w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_POWER_EXP ) != 0 ){
		tmp[6] = ItemBufParamGet( dat, ITEM_PRM_POWER_EXP_POINT );
		if( tmp[6] > 0 ){
			if( tmp[1] < ITEM_PRMEXP_MAX &&
				(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}else if( tmp[6] < 0 ){
			if( tmp[1] > 0 ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
			if( Friend_UpCheck( pp, dat ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}
	// �h��w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_DEFENCE_EXP ) != 0 ){
		tmp[6] = ItemBufParamGet( dat, ITEM_PRM_DEFENCE_EXP_POINT );
		if( tmp[6] > 0 ){
			if( tmp[2] < ITEM_PRMEXP_MAX &&
				(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}else if( tmp[6] < 0 ){
			if( tmp[2] > 0 ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
			if( Friend_UpCheck( pp, dat ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}
	// �f�����w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_AGILITY_EXP ) != 0 ){
		tmp[6] = ItemBufParamGet( dat, ITEM_PRM_AGILITY_EXP_POINT );
		if( tmp[6] > 0 ){
			if( tmp[3] < ITEM_PRMEXP_MAX &&
				(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}else if( tmp[6] < 0 ){
			if( tmp[3] > 0 ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
			if( Friend_UpCheck( pp, dat ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}
	// ���U�w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_SP_ATTACK_EXP ) != 0 ){
		tmp[6] = ItemBufParamGet( dat, ITEM_PRM_SP_ATTACK_EXP_POINT );
		if( tmp[6] > 0 ){
			if( tmp[4] < ITEM_PRMEXP_MAX &&
				(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}else if( tmp[6] < 0 ){
			if( tmp[4] > 0 ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
			if( Friend_UpCheck( pp, dat ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}
	// ���h�w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_SP_DEFENCE_EXP ) != 0 ){
		tmp[6] = ItemBufParamGet( dat, ITEM_PRM_SP_DEFENCE_EXP_POINT );
		if( tmp[6] > 0 ){
			if( tmp[5] < ITEM_PRMEXP_MAX &&
				(tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]) < PRMEXP_MAX ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}else if( tmp[6] < 0 ){
			if( tmp[5] > 0 ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
			if( Friend_UpCheck( pp, dat ) == TRUE ){
				sys_FreeMemoryEz( dat );
				return TRUE;
			}
		}
	}

	sys_FreeMemoryEz( dat );

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ����g�p�`�F�b�N���� ( POKEPARTY )
 *
 * @param	party		�񕜂���|�P�����̃f�[�^
 * @param	item		�g�p����A�C�e��
 * @param	pos1		�|�P�����f�[�^�̒��̈ʒu
 * @param	pos2		�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	heap_id		�q�[�vID
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
u8 PokeParty_StatusRecoverCheck( POKEPARTY * party, u16 item, u8 pos1, u8 pos2, u32 heap_id )
{
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer( party, pos1 );

	return StatusRecoverCheck( pp, item, pos2, heap_id );
}


//--------------------------------------------------------------------------------------------
/**
 * �񕜏��� ( POKEMON_PARAM )
 *
 * @param	pp			�񕜂���|�P�����̃f�[�^
 * @param	item		�g�p����A�C�e��
 * @param	pos			�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	place		�ꏊ
 * @param	heap_id		�q�[�vID
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
u8 StatusRecover( POKEMON_PARAM * pp, u16 item, u16 pos, u16 place, u32 heap_id )
{
	ITEMDATA * dat;
	s32	tmp[TEMP_BUFLEN];
	u8	use_flg;
	u8	dat_flg;

	dat = GetItemArcData( item, ITEM_GET_DATA, heap_id );

	// ���[�N�^�C�v���`�F�b�N
	if( ItemBufParamGet( dat, ITEM_PRM_W_TYPE ) != 1 ){
		sys_FreeMemoryEz( dat );
		return FALSE;
	}

	use_flg = FALSE;
	dat_flg = FALSE;

	tmp[0] = PokeParaGet( pp, ID_PARA_condition, NULL );
	tmp[1] = tmp[0];

	// �����
	if( ItemBufParamGet( dat, ITEM_PRM_SLEEP_RCV ) != 0 ){
		tmp[1] &= CONDITION_NEMURI_OFF;
		dat_flg = TRUE;
	}
	// �ŉ�
	if( ItemBufParamGet( dat, ITEM_PRM_POISON_RCV ) != 0 ){
		tmp[1] &= CONDITION_POISON_OFF;
		dat_flg = TRUE;
	}
	// �Ώ���
	if( ItemBufParamGet( dat, ITEM_PRM_BURN_RCV ) != 0 ){
		tmp[1] &= CONDITION_YAKEDO_OFF;
		dat_flg = TRUE;
	}
	// �X��
	if( ItemBufParamGet( dat, ITEM_PRM_ICE_RCV ) != 0 ){
		tmp[1] &= CONDITION_KOORI_OFF;
		dat_flg = TRUE;
	}
	// ��჉�
	if( ItemBufParamGet( dat, ITEM_PRM_PARALYZE_RCV ) != 0 ){
		tmp[1] &= CONDITION_MAHI_OFF;
		dat_flg = TRUE;
	}
	if( tmp[0] != tmp[1] ){
		PokeParaPut( pp, ID_PARA_condition, &tmp[1] );
		use_flg = TRUE;
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_hp, NULL );
	tmp[1] = PokeParaGet( pp, ID_PARA_hpmax, NULL );

/*
	// �m���� or �S���m����
	if( tmp[0] == 0 ){
		if( ItemBufParamGet( dat, ITEM_PRM_DEATH_RCV ) != 0 ||
			ItemBufParamGet( dat, ITEM_PRM_ALL_DEATH_RCV ) != 0 ){

			HP_Recover( pp, tmp[0], tmp[1], ItemBufParamGet(dat,ITEM_PRM_HP_RCV_POINT) );
			use_flg = TRUE;
		}
	// HP��
	}else if( tmp[0] < tmp[1] ){
		if( ItemBufParamGet( dat, ITEM_PRM_HP_RCV ) != 0 ){
			HP_Recover( pp, tmp[0], tmp[1], ItemBufParamGet(dat,ITEM_PRM_HP_RCV_POINT) );
			use_flg = TRUE;
		}
	}
*/
	// �m���� or �S���m����
	if( ( ItemBufParamGet(dat,ITEM_PRM_DEATH_RCV) != 0 ||
		  ItemBufParamGet(dat,ITEM_PRM_ALL_DEATH_RCV) != 0 )
		&& ItemBufParamGet( dat, ITEM_PRM_LV_UP ) != 0 ){
		if( tmp[0] == 0 ){
			HP_Recover( pp, tmp[0], tmp[1], ItemBufParamGet(dat,ITEM_PRM_HP_RCV_POINT) );
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	// HP��
	}else if( ItemBufParamGet( dat, ITEM_PRM_HP_RCV ) != 0 ){
		if( tmp[0] < tmp[1] ){
			HP_Recover( pp, tmp[0], tmp[1], ItemBufParamGet(dat,ITEM_PRM_HP_RCV_POINT) );
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	}

	tmp[2] = PokeParaGet( pp, ID_PARA_level, NULL );

	// ���x���A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_LV_UP ) != 0 ){
		if( tmp[2] < 100 ){
			PokeParaAdd( pp, ID_PARA_exp, PokeParaNextLevelExpGet(pp) );
			PokeParaCalc(pp);
			if( tmp[0] == 0 ){
				tmp[3] = PokeParaGet( pp, ID_PARA_hpmax, NULL );
				HP_Recover( pp, tmp[0], tmp[3], tmp[3]-tmp[1] );
			}
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	}

	// �i��
	if( ItemBufParamGet( dat, ITEM_PRM_EVOLUTION ) != 0 ){
		dat_flg = TRUE;
	}

	// PP�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_PP_UP ) != 0 ){
		if( PP_Up( pp, pos, 1 ) == TRUE ){
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	// PP�A�b�v�i�R�i�K�j
	}else if( ItemBufParamGet( dat, ITEM_PRM_PP_3UP ) != 0 ){
		if( PP_Up( pp, pos, 3 ) == TRUE ){
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	}

	// PP��
	if( ItemBufParamGet( dat, ITEM_PRM_PP_RCV ) != 0 ){
		if( PP_Recover( pp, pos, ItemBufParamGet(dat,ITEM_PRM_PP_RCV_POINT) ) == TRUE ){
			use_flg = TRUE;
		}
		dat_flg = TRUE;
	// PP�񕜁i�S�Ă̋Z�j
	}else if( ItemBufParamGet( dat, ITEM_PRM_ALL_PP_RCV ) != 0 ){
		for( tmp[0]=0; tmp[0]<4; tmp[0]++ ){
			if( PP_Recover( pp, tmp[0], ItemBufParamGet(dat,ITEM_PRM_PP_RCV_POINT) ) == TRUE ){
				use_flg = TRUE;
			}
		}
		dat_flg = TRUE;
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_hp_exp, NULL );
	tmp[1] = PokeParaGet( pp, ID_PARA_pow_exp, NULL );
	tmp[2] = PokeParaGet( pp, ID_PARA_def_exp, NULL );
	tmp[3] = PokeParaGet( pp, ID_PARA_agi_exp, NULL );
	tmp[4] = PokeParaGet( pp, ID_PARA_spepow_exp, NULL );
	tmp[5] = PokeParaGet( pp, ID_PARA_spedef_exp, NULL );

	// HP�w�͒l�A�b�v
	if( PokeParaGet( pp, ID_PARA_monsno, NULL ) != MONSNO_NUKENIN ){
		if( ItemBufParamGet( dat, ITEM_PRM_HP_EXP ) != 0 ){
			tmp[7] = ItemBufParamGet( dat,ITEM_PRM_HP_EXP_POINT );
			tmp[6] = PrmExp_Up( tmp[0], (tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]), tmp[7] );
			if( tmp[6] != -1 ){
				tmp[0] = tmp[6];
				PokeParaPut( pp, ID_PARA_hp_exp, &tmp[0] );
				PokeParaCalc( pp );
				use_flg = TRUE;
			}
			if( tmp[7] > 0 ){ dat_flg = TRUE; }
		}
	}
	// �U���w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_POWER_EXP ) != 0 ){
		tmp[7] = ItemBufParamGet( dat,ITEM_PRM_POWER_EXP_POINT );
		tmp[6] = PrmExp_Up( tmp[1], (tmp[0]+tmp[2]+tmp[3]+tmp[4]+tmp[5]), tmp[7] );
		if( tmp[6] != -1 ){
			tmp[1] = tmp[6];
			PokeParaPut( pp, ID_PARA_pow_exp, &tmp[1] );
			PokeParaCalc( pp );
			use_flg = TRUE;
		}
		if( tmp[7] > 0 ){ dat_flg = TRUE; }
	}
	// �h��w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_DEFENCE_EXP ) != 0 ){
		tmp[7] = ItemBufParamGet( dat,ITEM_PRM_DEFENCE_EXP_POINT );
		tmp[6] = PrmExp_Up( tmp[2], (tmp[0]+tmp[1]+tmp[3]+tmp[4]+tmp[5]), tmp[7] );
		if( tmp[6] != -1 ){
			tmp[2] = tmp[6];
			PokeParaPut( pp, ID_PARA_def_exp, &tmp[2] );
			PokeParaCalc( pp );
			use_flg = TRUE;
		}
		if( tmp[7] > 0 ){ dat_flg = TRUE; }
	}
	// �f�����w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_AGILITY_EXP ) != 0 ){
		tmp[7] = ItemBufParamGet( dat,ITEM_PRM_AGILITY_EXP_POINT );
		tmp[6] = PrmExp_Up( tmp[3], (tmp[0]+tmp[1]+tmp[2]+tmp[4]+tmp[5]), tmp[7] );
		if( tmp[6] != -1 ){
			tmp[3] = tmp[6];
			PokeParaPut( pp, ID_PARA_agi_exp, &tmp[3] );
			PokeParaCalc( pp );
			use_flg = TRUE;
		}
		if( tmp[7] > 0 ){ dat_flg = TRUE; }
	}
	// ���U�w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_SP_ATTACK_EXP ) != 0 ){
		tmp[7] = ItemBufParamGet( dat,ITEM_PRM_SP_ATTACK_EXP_POINT );
		tmp[6] = PrmExp_Up( tmp[4], (tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[5]), tmp[7] );
		if( tmp[6] != -1 ){
			tmp[4] = tmp[6];
			PokeParaPut( pp, ID_PARA_spepow_exp, &tmp[4] );
			PokeParaCalc( pp );
			use_flg = TRUE;
		}
		if( tmp[7] > 0 ){ dat_flg = TRUE; }
	}
	// ���h�w�͒l�A�b�v
	if( ItemBufParamGet( dat, ITEM_PRM_SP_DEFENCE_EXP ) != 0 ){
		tmp[7] = ItemBufParamGet( dat,ITEM_PRM_SP_DEFENCE_EXP_POINT );
		tmp[6] = PrmExp_Up( tmp[5], (tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]), tmp[7] );
		if( tmp[6] != -1 ){
			tmp[5] = tmp[6];
			PokeParaPut( pp, ID_PARA_spedef_exp, &tmp[5] );
			PokeParaCalc( pp );
			use_flg = TRUE;
		}
		if( tmp[7] > 0 ){ dat_flg = TRUE; }
	}

	if( use_flg == FALSE && dat_flg == TRUE ){
		sys_FreeMemoryEz( dat );
		return FALSE;
	}

	tmp[0] = PokeParaGet( pp, ID_PARA_friend, NULL );

	// �Ȃ��x�P
	if( tmp[0] < 100 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND1 ) != 0 ){
			if( Friend_Up( pp, tmp[0], ItemBufParamGet(dat,ITEM_PRM_FRIEND1_POINT), place, heap_id ) == FALSE ){
				sys_FreeMemoryEz( dat );
				return use_flg;
			}
		}
	// �Ȃ��x�Q
	}else if( tmp[0] >= 100 && tmp[0] < 200 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND2 ) != 0 ){
			if( Friend_Up( pp, tmp[0], ItemBufParamGet(dat,ITEM_PRM_FRIEND2_POINT), place, heap_id ) == FALSE ){
				sys_FreeMemoryEz( dat );
				return use_flg;
			}
		}
	// �Ȃ��x�R
	}else if( tmp[0] >= 200 && tmp[0] <= 255 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND3 ) != 0 ){
			if( Friend_Up( pp, tmp[0], ItemBufParamGet(dat,ITEM_PRM_FRIEND3_POINT), place, heap_id ) == FALSE ){
				sys_FreeMemoryEz( dat );
				return use_flg;
			}
		}
	}

	sys_FreeMemoryEz( dat );
	return use_flg;
}

//--------------------------------------------------------------------------------------------
/**
 * �񕜏��� ( POKEPARTY )
 *
 * @param	party		�񕜂���|�P�����̃f�[�^
 * @param	item		�g�p����A�C�e��
 * @param	pos1		�|�P�����f�[�^�̒��̈ʒu
 * @param	pos2		�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	place		�ꏊ
 * @param	heap_id		�q�[�vID
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
u8 PokeParty_StatusRecover( POKEPARTY * party, u16 item, u8 pos1, u8 pos2, u16 place, u32 heap_id )
{
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer( party, pos1 );

	return StatusRecover( pp, item, pos2, place, heap_id );
}


//--------------------------------------------------------------------------------------------
/**
 * PP�񕜃`�F�b�N
 *
 * @param	pp		�񕜂���|�P�����̃f�[�^
 * @param	pos		�񕜈ʒu�i�Z�ʒu�Ȃǁj
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
static u8 PP_RcvCheck( POKEMON_PARAM * pp, u32 pos )
{
	u16	waza;
	u8	npp;
	u8	ppc;

	waza = (u16)PokeParaGet( pp, ID_PARA_waza1+pos, NULL );
	if( waza == 0 ){
		return FALSE;
	}
	npp = (u8)PokeParaGet( pp, ID_PARA_pp1+pos, NULL );
	ppc = (u8)PokeParaGet( pp, ID_PARA_pp_count1+pos, NULL );

	if( npp < WT_PPMaxGet( waza, ppc ) ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * PP��
 *
 * @param	pp		�񕜂���|�P�����̃f�[�^
 * @param	pos		�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	rcv		�񕜒l
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
static u8 PP_Recover( POKEMON_PARAM * pp, u32 pos, u32 rcv )
{
	u16	waza;
	u8	npp;
	u8	mpp;

	waza = (u16)PokeParaGet( pp, ID_PARA_waza1+pos, NULL );
	if( waza == 0 ){
		return FALSE;
	}
	npp  = (u8)PokeParaGet( pp, ID_PARA_pp1+pos, NULL );
	mpp  = (u8)WT_PPMaxGet( waza, PokeParaGet(pp,ID_PARA_pp_count1+pos,NULL) );

	if( npp < mpp ){
		if( rcv == PP_RCV_ALL ){
			npp = mpp;
		}else{
			npp += rcv;
			if( npp > mpp ){
				npp = mpp;
			}
		}
		PokeParaPut( pp, ID_PARA_pp1+pos, &npp );
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * PP�A�b�v
 *
 * @param	pp		�񕜂���|�P�����̃f�[�^
 * @param	pos		�񕜈ʒu�i�Z�ʒu�Ȃǁj
 * @param	cnt		�A�b�v�l
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
static u8 PP_Up( POKEMON_PARAM * pp, u32 pos, u32 cnt )
{
	u16	waza;
	u8	npp;
	u8	ppc;
	u8	mpp;

	ppc = PokeParaGet( pp, ID_PARA_pp_count1+pos, NULL );
	if( ppc == 3 ){
		return FALSE;
	}

	waza = (u16)PokeParaGet( pp, ID_PARA_waza1+pos, NULL );

	if( WT_PPMaxGet( waza, 0 ) < 5 ){
		return FALSE;
	}

	npp  = (u8)PokeParaGet( pp, ID_PARA_pp1+pos, NULL );
	mpp  = (u8)WT_PPMaxGet( waza, ppc );

	if( ppc+cnt > 3 ){
		ppc = 3;
	}else{
		ppc = ppc + cnt;
	}
	npp = npp + WT_PPMaxGet( waza, ppc ) - mpp;

	PokeParaPut( pp, ID_PARA_pp_count1+pos, &ppc );
	PokeParaPut( pp, ID_PARA_pp1+pos, &npp );

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * HP��
 *
 * @param	pp		�񕜂���|�P�����̃f�[�^
 * @param	hp		���݂�HP
 * @param	max		�ő�HP
 * @param	rcv		�񕜒l
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
static void HP_Recover( POKEMON_PARAM * pp, u32 hp, u32 max, u32 rcv )
{
	if( max == 1 ){
		rcv = 1;
	}else if( rcv == RCV_ALL ){
		rcv = max;
	}else if( rcv == RCV_HALF ){
		rcv = max/2;
	}else if( rcv == RCV_25PER ){
		rcv = max/4;
	}

	if( hp+rcv > max ){
		hp = max;
	}else{
		hp += rcv;
	}

	PokeParaPut( pp, ID_PARA_hp, &hp );
}

//--------------------------------------------------------------------------------------------
/**
 * �w�͒lUp�v�Z
 *
 * @param	exp		���݂̓w�͒l
 * @param	other	���̑��̓w�͒l�̍��v
 * @param	up		�A�b�v����l
 *
 * @retval	"-1 = �A�b�v���Ȃ�"
 * @retval	"0 != �v�Z���ʁi�Z�b�g����w�͒l�j"
 */
//--------------------------------------------------------------------------------------------
static s32 PrmExp_Up( s32 exp, s32 other, s32 up )
{
	if( exp == 0 && up < 0 ){
		return -1;
	}
	if( exp >= ITEM_PRMEXP_MAX && up > 0 ){
		return -1;
	}
	if( (exp+other) >= PRMEXP_MAX && up > 0 ){
		return -1;
	}

	exp += up;
	if( exp > ITEM_PRMEXP_MAX ){
		exp = ITEM_PRMEXP_MAX;
	}else if( exp < 0 ){
		exp = 0;
	}
	if( (exp+other) > PRMEXP_MAX ){
		exp = PRMEXP_MAX - other;
	}
	return exp;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ȃ��x���オ�邩
 *
 * @param	pp		�|�P�����̃f�[�^
 * @param	prm		�ύX�l
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 *
 * @li	������ꍇ�͖���
 */
//--------------------------------------------------------------------------------------------
static u8 Friend_UpCheck( POKEMON_PARAM * pp, ITEMDATA * dat )
{
	s32	now;
	s32	prm;

	now = PokeParaGet( pp, ID_PARA_friend, NULL );
	if( now >= FRIEND_MAX ){ return FALSE; }

	// �Ȃ��x�P
	if( now < 100 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND1 ) != 0 ){
			if( ItemBufParamGet( dat,ITEM_PRM_FRIEND1_POINT ) > 0 ){
				return TRUE;
			}
		}
		return FALSE;
	// �Ȃ��x�Q
	}else if( now >= 100 && now < 200 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND2 ) != 0 ){
			if( ItemBufParamGet( dat,ITEM_PRM_FRIEND2_POINT ) > 0 ){
				return TRUE;
			}
		}
		return FALSE;
	// �Ȃ��x�R
	}else if( now >= 200 && now < 255 ){
		if( ItemBufParamGet( dat, ITEM_PRM_FRIEND3 ) != 0 ){
			if( ItemBufParamGet( dat,ITEM_PRM_FRIEND3_POINT ) > 0 ){
				return TRUE;
			}
		}
		return FALSE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ȃ��xUp
 *
 * @param	pp		�|�P�����̃f�[�^
 * @param	now		���݂̒l
 * @param	prm		�ύX�l
 * @param	place	�ꏊ
 *
 * @retval	"TRUE = �g�p�\"
 * @retval	"FALSE = �g�p�s��"
 */
//--------------------------------------------------------------------------------------------
static u8 Friend_Up( POKEMON_PARAM * pp, s32 now, s32 prm, u16 place, u32 heap )
{
	if( now == FRIEND_MAX && prm > 0 ){
		return FALSE;
	}
	if( now == 0 && prm < 0 ){
		return FALSE;
	}

	if( prm > 0 ){
		// ��������
		if( ItemParamGet(PokeParaGet(pp,ID_PARA_item,NULL),ITEM_PRM_EQUIP,heap)==SOUBI_NATUKIDOUP ){
			prm = prm * 150 / 100;
		}
		// �ߊl�{�[��
		if( PokeParaGet( pp, ID_PARA_get_ball, NULL ) == ITEM_GOOZYASUBOORU ){
			prm++;
		}
		// �ߊl�ꏊ
		if( PokeParaGet( pp, ID_PARA_get_place, NULL ) == place ){
			prm++;
		}
	}

	prm += now;
	if( prm > FRIEND_MAX ){
		prm = FRIEND_MAX;
	}
	if( prm < 0 ){
		prm = 0;
	}
	PokeParaPut( pp, ID_PARA_friend, &prm );
	return TRUE;
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------
void PokeParty_RecoverAll(POKEPARTY * party)
{
	int i, j, total;
	u32 buf;
	POKEMON_PARAM * pp;

	total = PokeParty_GetPokeCount(party);
	for (i = 0; i < total; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_poke_exist, NULL) == FALSE) {
			continue;
		}
		//HP�S��
		buf = PokeParaGet( pp, ID_PARA_hpmax, NULL );
		PokeParaPut(pp, ID_PARA_hp, &buf);
		//��Ԉُ��
		buf = 0;
		PokeParaPut(pp, ID_PARA_condition, &buf);
		//PP�S��
		for (j = 0; j < 4; j++) {
			if (PP_RcvCheck(pp,j) == TRUE) {
				PP_Recover(pp, j, PP_RCV_ALL);
			}
		}

	}
}


