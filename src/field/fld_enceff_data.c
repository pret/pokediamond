//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fld_encount_data.c
 *	@brief		�t�B�[���h�G���J�E���g�f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.06.08
 *	
 *	�o�g���p�����[�^����
 *	�G���J�E���g�G�t�F�N�g�@BGM�������Ă����郋�[�`��
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "fieldsys.h"

#include "encount_effect.h"
#include "ev_pokemon.h"
#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/monsno.h"

#include "battle/trtype_def.h"

#include "system/snd_tool.h"
#include "field/fld_bgm.h"

#define __FIELD_ENCEFF_DATA_H_GLOBAL
#include "fld_enceff_data.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	����G���J�E���g�^�C�v�萔
//
//	�ʏ�G���J�E���g
//		�t�B�[���h�A�g���[�i�[�ȊO��
//		�Ǝ��̃G�t�F�N�g�����g�p����G�t�F�N�g
//=====================================
enum{
	// GYM
	FLD_ENCEFF_SP_GYM_KUROGANE,			// �N���K�l�W��
	FLD_ENCEFF_SP_GYM_HAKUTAI,			// �n�N�^�C�W��
	FLD_ENCEFF_SP_GYM_NOMOSE,			// �m���Z�W��
	FLD_ENCEFF_SP_GYM_TOBARI,			// �g�o���W��
	FLD_ENCEFF_SP_GYM_YOSUGA,			// ���X�K�g�W��
	FLD_ENCEFF_SP_GYM_KISSAKI,			// �L�b�T�L�W��
	FLD_ENCEFF_SP_GYM_MIO,				// �~�I�W��
	FLD_ENCEFF_SP_GYM_NAGISA,			// �i�M�T�W��
	// �l�V��
	FLD_ENCEFF_SP_BIGFOUR_00,
	FLD_ENCEFF_SP_BIGFOUR_01,
	FLD_ENCEFF_SP_BIGFOUR_02,
	FLD_ENCEFF_SP_BIGFOUR_03,
	// �`�����s�I��
	FLD_ENCEFF_SP_CHANPION,
	// ���C�o��
	FLD_ENCEFF_SP_RIVAL,
	// ����|�P����
	FLD_ENCEFF_SP_LEGEND_POKE00,	// �V�F�C�~
	FLD_ENCEFF_SP_PACKAGE_POKE00,	// �C�A�A�G�A
	FLD_ENCEFF_SP_REIHAI_POKE00,	// ���C�@�n�C
	FLD_ENCEFF_SP_AI_POKE00,		// �A�C
	FLD_ENCEFF_SP_ARUSEUSU,			// �A���Z�E�X
	FLD_ENCEFF_SP_LEGEND_POKE01,	// ڼ޷޶޽�A�q�[�h�����A�L�}�C�����A�_�[���炢
	FLD_ENCEFF_SP_LEGEND_POKE02,	// �N���Z���A
	
	// ��͒c
	FLD_ENCEFF_SP_GINGA_NORMAL,		// �ʏ탁���o�[
	FLD_ENCEFF_SP_GINGA_SPECIAL,	// �����N���X
	FLD_ENCEFF_SP_GINGA_BOSU,	// �{�X
	// ���̑�����o�g��
	FLD_ENCEFF_SP_BATTLE_TOWER,		// �o�g���^���[
	FLD_ENCEFF_SP_BATTLE_COMMU,		// �ʐM�o�g��
	FLD_ENCEFF_SP_BATTLE_DOUBLE,		// �_�u���o�g���g���[�i�[
	FLD_ENCEFF_SP_BATTLE_DOUBLE_YASEI,	// �_�u���o�g���₹��
	FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN,	// �^���[�^�C�N�[��

	// �m�[�}��	
	FLD_ENCEFF_SP_NORMAL_TRAINER,	// �g���[�i�[
	FLD_ENCEFF_SP_NORMAL_FIELD,		// �쐶

	FLD_ENCEFF_SP_MAX,	// ����G���J�E���g��
};



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	����G���J�E���g�f�[�^���[�N
//=====================================
typedef struct {
	u16 effect_no;
	u16 bgm_no;
} FLD_ENCEFF_SP_DATA;


//-----------------------------------------------------------------------------
/**
 *		����G���J�E���g�G�t�F�N�g�e�[�u��
 *			�y����G���J�E���g�^�C�v�萔�z�̂Ȃ�т�
 *			���킹��K�v������܂��B
*/
//-----------------------------------------------------------------------------
// �G���J�E���g�G�t�F�N�g���o�g���p�����[�^����SEARCH����
#define ENCOUNT_EFFECT_SEARCH	( 0xffff )


static const FLD_ENCEFF_SP_DATA FLD_EncEffSpData[ FLD_ENCEFF_SP_MAX ] = {
	// GYM
	{ ENCOUNT_SPTR_KUROGANE_GYM,	SEQ_BA_GYM },	// �N���K�l�W��
	{ ENCOUNT_SPTR_HAKUTAI_GYM,		SEQ_BA_GYM },	// �n�N�^�C�W��
	{ ENCOUNT_SPTR_NOMOSE_GYM,		SEQ_BA_GYM },	// �m���Z�W��
	{ ENCOUNT_SPTR_TOBARI_GYM,		SEQ_BA_GYM },	// �g�o���W��
	{ ENCOUNT_SPTR_YOSUGA_GYM,		SEQ_BA_GYM },	// ���X�K�g�W��
	{ ENCOUNT_SPTR_KISSAKI_GYM,		SEQ_BA_GYM },	// �L�b�T�L�W��
	{ ENCOUNT_SPTR_MIO_GYM,			SEQ_BA_GYM },	// �~�I�W��
	{ ENCOUNT_SPTR_NAGISA_GYM,		SEQ_BA_GYM },	// �i�M�T�W��
	// �l�V��
	{ ENCOUNT_SPTR_SITEN_00,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_01,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_02,	SEQ_BA_TENNO },
	{ ENCOUNT_SPTR_SITEN_03,	SEQ_BA_TENNO },
	// �`�����s�I��
	{ ENCOUNT_SPTR_CHANPION,	SEQ_BA_CHANP },
	// ���C�o��
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_RIVAL },
	// ����|�P����
	{ ENCOUNT_LEGEND_NORMAL,	SEQ_BA_POKE },	// �V�F�C�~
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_DPOKE2 },	// �C�A�A�G�A
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_DPOKE1 },	// ���C�@�n�C�@
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_DPOKE1 },	// �A�C
	{ ENCOUNT_LEGEND_PACKAGE,	SEQ_BA_SECRET1 },	// �A���Z�E�X
	{ ENCOUNT_LEGEND_NORMAL,	SEQ_BA_SECRET2 },	// ���W�M�K�X�A�q�[�h�����A�L�}�C����
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_POKE },	// �N���Z���A

	// ��͒c
	{ ENCOUNT_GINGA_NORMAL,		SEQ_BA_GINGA },	// �ʏ탁���o�[
	{ ENCOUNT_GINGA_SPECIAL,	SEQ_BA_GINGA3},	// �����N���X
	{ ENCOUNT_GINGA_SPECIAL,	SEQ_BA_AKAGI },	// �{�X
	// ���̑�����o�g��
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_TRAIN },	// �o�g���^���[
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_TRAIN },	// �ʐM�o�g��
	{ ENCOUNT_SPECIAL_DOUBLE,	SEQ_BA_TRAIN },	// �_�u���o�g��
	{ ENCOUNT_SPECIAL_DOUBLE,	SEQ_BA_POKE },	// �_�u���o�g���₹��
	{ ENCOUNT_SPECIAL_TOWER,	SEQ_BA_CHANP },	// �o�g���^���[�^�C�N�[��
	// �m�[�}��
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_TRAIN },	// �g���[�i�[
	{ ENCOUNT_EFFECT_SEARCH,	SEQ_BA_POKE },	// �쐶

//	{ �G�t�F�N�g,BGM },	
};


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetTrainer( u32 tr_type );
static u32 FLD_EncEffSpDataTypeGetPokemon( POKEPARTY* p_poke_party );

static u32 FLD_EncEffSpDataTypeGet( const BATTLE_PARAM* p_bp );
static u32 FLD_EncEffSpDataEffectNoGet( u32 type, const BATTLE_PARAM* p_bp );
static u32 FLD_EncEffSpDataBgmNoGet( u32 type, const BATTLE_PARAM* p_bp );




//----------------------------------------------------------------------------
/**
 *	@brief	����G���J�E���g�^�C�v�@�擾
 *	
 *	@param	BATTLE_PARAM* p_bp 
 *	@retval	����G���J�E���g�e�[�u��
 *	@retval	FLD_ENCEFF_SP_MAX	����e�[�u���ɂȂ�
 *
 *	* �D�揇��
 *		����g���[�i�[
 *		����|�P�����́@�o�g���^���[�@�ʐM�@�_�u���ł�
 *		�o�Ă��Ȃ��ƍl���č쐬
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGet( const BATTLE_PARAM* p_bp )
{
	u32 fight_type = p_bp->fight_type;
	u32 trainer_sp;
	u32 mons_sp;
	

	// �g���[�i�[��`�F�b�N
	if( (fight_type & FIGHT_TYPE_TRAINER) ){

		// �g���[�i�[�`�F�b�N
		trainer_sp = FLD_EncEffSpDataTypeGetTrainer( p_bp->trainer_data[ CLIENT_NO_ENEMY ].tr_type );

		// �o�g���^���[�́A����g���[�i�[ID�Ȃ̂�
		// ��ɔ��f����
		if( fight_type & FIGHT_TYPE_TOWER ){

			// �^���[�^�C�N�[�����ŗD��
			if( trainer_sp == FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN ){
				return trainer_sp;
			}

			// �_�u���o�g���`�F�b�N
			if( fight_type & FIGHT_TYPE_2vs2 ){
				return FLD_ENCEFF_SP_BATTLE_DOUBLE;
			}
			return FLD_ENCEFF_SP_BATTLE_TOWER;
		}

		// ��͒c��D�悷��
		if( (trainer_sp == FLD_ENCEFF_SP_GINGA_NORMAL) || 
			(trainer_sp == FLD_ENCEFF_SP_GINGA_SPECIAL) ||
			(trainer_sp == FLD_ENCEFF_SP_GINGA_BOSU) ){
			return trainer_sp;
		}

		// �_�u���o�g���`�F�b�N
		if( fight_type & FIGHT_TYPE_2vs2 ){
			return FLD_ENCEFF_SP_BATTLE_DOUBLE;
		}

		// �ʐM�o�g���`�F�b�N
		if( fight_type & FIGHT_TYPE_SIO ){
			return FLD_ENCEFF_SP_BATTLE_COMMU;
		}

		return trainer_sp;
	}

	// ����|�P�����`�F�b�N
	mons_sp = FLD_EncEffSpDataTypeGetPokemon( p_bp->poke_party[ CLIENT_NO_ENEMY ] );

	// �t�B�[���h�ȉ��̓���|�P�����Ȃ�Ԃ�
	if( mons_sp < FLD_ENCEFF_SP_NORMAL_FIELD ){
		return mons_sp;
	}

	// �_�u���o�g���`�F�b�N
	if( fight_type & FIGHT_TYPE_2vs2 ){
		return FLD_ENCEFF_SP_BATTLE_DOUBLE_YASEI;
	}

	// �쐶
	return mons_sp;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�G���J�E���g�G�t�F�N�g�i���o�[�̎擾
 *	@param	type	�y����G���J�E���g�^�C�v�萔�z
 *	@param	p_bp	�o�g���p�����[�^
 *	@return	�G���J�E���g�G�t�F�N�g�i���o�[
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataEffectNoGet( u32 type, const BATTLE_PARAM* p_bp )
{
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	
	if( FLD_EncEffSpData[ type ].effect_no == ENCOUNT_EFFECT_SEARCH ){
		// ���x�����Ȃǂ����Č��߂�
		return ENCEFF_GetEffectNo( p_bp );
	}else{

		return FLD_EncEffSpData[ type ].effect_no;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGM�i���o�[�̎擾
 *	@param	type	�y����G���J�E���g�^�C�v�萔�z
 *	@param	p_bp	�o�g���p�����[�^
 *	@return	BGM�i���o�[
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataBgmNoGet( u32 type, const BATTLE_PARAM* p_bp )
{
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	return FLD_EncEffSpData[ type ].bgm_no;
}

//----------------------------------------------------------------------------
/**
 *	[type �̎擾�͓����ōs��]
 *	@brief	�G���J�E���g�G�t�F�N�g�i���o�[�̎擾
 *	@param	p_bp	�o�g���p�����[�^
 *	@return	�G���J�E���g�G�t�F�N�g�i���o�[
 */
//-----------------------------------------------------------------------------
u32 FLD_EncEffSpDataEffectNoPackGet( const BATTLE_PARAM* p_bp )
{
	u32 type;
	type = FLD_EncEffSpDataTypeGet( p_bp );
	return FLD_EncEffSpDataEffectNoGet( type, p_bp );
}

//----------------------------------------------------------------------------
/**
 *	[type �̎擾�͓����ōs��]
 *	@brief	BGM�i���o�[�̎擾
 *	@param	p_bp	�o�g���p�����[�^
 *	@return	BGM�i���o�[
 */
//-----------------------------------------------------------------------------
u32 FLD_EncEffSpDataBgmNoPackGet( const BATTLE_PARAM* p_bp )
{
	u32 type;
	type = FLD_EncEffSpDataTypeGet( p_bp );
	return FLD_EncEffSpDataBgmNoGet( type, p_bp );
}



//-----------------------------------------------------------------------------
/**
 *			�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�G���J�E���g�G�t�F�N�g�f�[�^�擾
 *
 *	@param	p_data		�f�[�^�i�[��
 *	@param	type		�y����G���J�E���g�^�C�v�萔�z
 */
//-----------------------------------------------------------------------------
static void FLD_EncEffSpDataGet( FLD_ENCEFF_SP_DATA* p_data, u32 type )
{
	// �^�C�v���s��
	GF_ASSERT( type < FLD_ENCEFF_SP_MAX );
	*p_data = FLD_EncEffSpData[ type ];
}


//----------------------------------------------------------------------------
/**
 *	@brief	����g���[�i�[����G���J�E���g�^�C�v�I�o
 *
 *	@param	tr_type	�g���[�i�[TYPE
 *
 *	@retval	����G���J�E���g�e�[�u��
 *	@retval	FLD_ENCEFF_SP_MAX	����e�[�u���ɂȂ�
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetTrainer( u32 tr_type )
{
	u32 retval = FLD_ENCEFF_SP_NORMAL_TRAINER;
	
	
	// tr_type��������ƘA�Ԃŕ���ł��Ȃ��̂�
	// �S��case�łƂ�K�v������
	switch( tr_type ){
	// GYM
	case TRTYPE_LEADER1:		// �N���K�l�W��
		retval = FLD_ENCEFF_SP_GYM_KUROGANE;
		break;
	case TRTYPE_LEADER2:		// �n�N�^�C�W��
		retval = FLD_ENCEFF_SP_GYM_HAKUTAI;
		break;
	case TRTYPE_LEADER3:		// �m���Z�W��
		retval = FLD_ENCEFF_SP_GYM_NOMOSE;
		break;
	case TRTYPE_LEADER4:		// �g�o���W��
		retval = FLD_ENCEFF_SP_GYM_TOBARI;
		break;
	case TRTYPE_LEADER5:		// ���X�K�g�W��
		retval = FLD_ENCEFF_SP_GYM_YOSUGA;
		break;
	case TRTYPE_LEADER6:		// �L�b�T�L�W��
		retval = FLD_ENCEFF_SP_GYM_KISSAKI;
		break;
	case TRTYPE_LEADER7:		// �~�I�W��
		retval = FLD_ENCEFF_SP_GYM_MIO;
		break;
	case TRTYPE_LEADER8:		// �i�M�T�W��
		retval = FLD_ENCEFF_SP_GYM_NAGISA;
		break;
		
	// �l�V��
	case TRTYPE_BIGFOUR1:
		retval = FLD_ENCEFF_SP_BIGFOUR_00;
		break;
	case TRTYPE_BIGFOUR2:
		retval = FLD_ENCEFF_SP_BIGFOUR_01;
		break;
	case TRTYPE_BIGFOUR3:
		retval = FLD_ENCEFF_SP_BIGFOUR_02;
		break;
	case TRTYPE_BIGFOUR4:
		retval = FLD_ENCEFF_SP_BIGFOUR_03;
		break;
		
	// �`�����s�I��
	case TRTYPE_CHAMPION:
		retval = FLD_ENCEFF_SP_CHANPION;
		break;

	// ���C�o��
	case TRTYPE_RIVAL:
		retval = FLD_ENCEFF_SP_RIVAL;
		break;
		
	// ��͒c
	case TRTYPE_GINGALBOSS:
		retval = FLD_ENCEFF_SP_GINGA_BOSU;
		break;
		
	case TRTYPE_GINGALEADER1:
	case TRTYPE_GINGALEADER2:
	case TRTYPE_GINGALEADER3:
		retval = FLD_ENCEFF_SP_GINGA_SPECIAL;
		break;
	case TRTYPE_GINGAM:
	case TRTYPE_GINGAW:
		retval = FLD_ENCEFF_SP_GINGA_NORMAL;
		break;

	// �o�g���^���[
	case TRTYPE_KUROTUGU:
		retval = FLD_ENCEFF_SP_BATTLE_TOWER_TAIKUUN;
		break;

	default:
		break;
	}

	return retval;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����|�P�����@�`�F�b�N
 *
 *	@param	p_poke_party	�|�P�����p�[�e�B
 *
 *	@retval	����G���J�E���g�e�[�u��
 *	@retval	FLD_ENCEFF_SP_MAX	����e�[�u���ɂȂ�
 */
//-----------------------------------------------------------------------------
static u32 FLD_EncEffSpDataTypeGetPokemon( POKEPARTY* p_poke_party )
{
	POKEMON_PARAM* p_enemy_poke;
	u32 monsno;
	u32 retval = FLD_ENCEFF_SP_NORMAL_FIELD;

	// �|�P�����p�����[�^�擾
	p_enemy_poke = EvPoke_GetLivingPokemonTop( p_poke_party );
	monsno = PokeParaGet( p_enemy_poke, ID_PARA_monsno, NULL );

	switch( monsno ){
	case MONSNO_EURISU:	// �V�F�C�~�A
		retval = FLD_ENCEFF_SP_LEGEND_POKE00;
		break;

	case MONSNO_MUUBASU:	// �N���Z���A
		retval = FLD_ENCEFF_SP_LEGEND_POKE02;
		break;

		
	case MONSNO_REZIKINGU:	// ���W�M�K�X�@�q�[�h�����@�L�}�C�����@�_�[�N���C
	case MONSNO_KIMAIRAN:
	case MONSNO_HIIDORAN:
	case MONSNO_DAAKU:
	case MONSNO_PURAZUMA:
		retval = FLD_ENCEFF_SP_LEGEND_POKE01;
		break;
		
	case MONSNO_AI:	// �A�C
		retval = FLD_ENCEFF_SP_AI_POKE00;
		break;

	case MONSNO_REI:	// ���C�@�n�C
	case MONSNO_HAI:
		retval = FLD_ENCEFF_SP_REIHAI_POKE00;
		break;
		
	case MONSNO_IA:	// �C�A�A�G�A�A�A�E�X
	case MONSNO_EA:
		retval = FLD_ENCEFF_SP_PACKAGE_POKE00;
		break;

	case MONSNO_AUSU:	// �A���Z�E�X
		retval = FLD_ENCEFF_SP_ARUSEUSU;
		break;

	default:
		break;
	}
	return retval;
}
