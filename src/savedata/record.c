//============================================================================================
/**
 * @file	record.c
 * @brief	�Q�[�����J�E���g�����֘A
 * @author	tamada
 * @date	2006.03.28
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "savedata/savedata.h"

#include "savedata/record.h"


#include "gflib/assert.h"

//============================================================================================
//============================================================================================
struct RECORD{
	u32 large_rec[LARGE_REC_NUM];
	u16 small_rec[SMALL_REC_NUM];
};
#ifdef _NITRO
// �\���̂��z��̃T�C�Y�ƂȂ��Ă��邩�`�F�b�N
SDK_COMPILER_ASSERT(sizeof(RECORD) == 332);
#endif

//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���[�N�T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int RECORD_GetWorkSize(void)
{
	return sizeof(RECORD);
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h������
 * @param	rec		���R�[�h�f�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
void RECORD_Init(RECORD * rec)
{
	MI_CpuClear32(rec, sizeof(RECORD));
}

//----------------------------------------------------------
/**
 * @brief
 * @param	sv
 * @return	RECORD�ւ̃|�C���^
 */
//----------------------------------------------------------
RECORD * SaveData_GetRecord(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_RECORD);
}

//============================================================================================
//
//
//			�����֐�
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�l�̎擾
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���R�[�h���ڎw��ID
 * @return	u32		���݂̒l
 */
//----------------------------------------------------------
static u32 get_value(const RECORD * rec, int id)
{
	if (id < LARGE_REC_MAX) {
		return rec->large_rec[id];
	} else if (id < SMALL_REC_MAX) {
		return rec->small_rec[id - LARGE_REC_MAX];
	}
	GF_ASSERT_MSG(0, "record: id error\n");
	return 0;
}

//----------------------------------------------------------
/**
 * @brief	�l���Z�b�g����
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���R�[�h���ڎw��ID
 * @param	value	�Z�b�g����l
 * @return	u32		���݂̒l
 */
//----------------------------------------------------------
static u32 set_value(RECORD * rec, int id, u32 value)
{
	if (id < LARGE_REC_MAX) {
		rec->large_rec[id] = value;
	} else if (id < SMALL_REC_MAX) {
		rec->small_rec[id - LARGE_REC_MAX] = value;
	} else {
		GF_ASSERT_MSG(0, "record: id error\n");
	}
	return get_value(rec, id);
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h���ڂ��Ƃ̏�����擾����
 * @param	id		���R�[�h���ڎw��ID
 * @return	u32		����̒l
 */
//----------------------------------------------------------
static u32 get_limit(int id)
{
	static u8 limit[SMALL_REC_MAX] = {
		1,	//RECID_SCORE
		//4byte
		1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,	//1-16
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	//17-32
		1,1,1,1,1,1,1,1,0,0,0,	//33-43
		//2byte
		1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,	//44-59
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,	//60-75
		0,0,0,0,0,0,0,0,0,1,	//76-85
	};

	if (id < LARGE_REC_MAX) {
		if(limit[id]){
			return 999999999;
		}else{
			return 999999;
		}
	} else if (id < SMALL_REC_MAX) {
		if(limit[id]){
			return 0xffff;
		}else{
			return 9999;
		}
	}
	GF_ASSERT_MSG(0, "record: id error\n");
	return 0;
}

//----------------------------------------------------------
//----------------------------------------------------------
static int get_score_number(int score_id)
{
	static const u16 num[SCOREID_MAX] = { 
		1,		//SCORE_ID_GET_NUTS					�X�R�A�F���݂̂������
		1,		//SCORE_ID_HONEY_TREE				�X�R�A�F�؂ɖ���h����
		1,		//SCORE_ID_WRITE_MAIL				�X�R�A�F���[����������
		1,		//SCORE_ID_INTERVIEW				�X�R�A�F�e���r�C���^�r���[�ɓ�����
		1,		//SCORE_ID_WRITE_SIGN				�X�R�A�F�T�C��������
		1,		//SCORE_ID_PLAY_SLOT				�X�R�A�F�X���b�g�n�߂�
		2,		//SCORE_ID_CUSTOM_CAPSULE			�X�R�A�F�J�X�^���J�v�Z�������
		2,		//SCORE_ID_MAKE_CLIP				�X�R�A�F�N���b�v�����
		2,		//SCORE_ID_WILD_BATTLE_WIN			�X�R�A�F�쐶�G���J�E���g����
		2,		//SCORE_ID_POKE_GET_SINOU			�X�R�A�F�|�P�����Q�b�g�i�V���I�E������j
		3,		//SCORE_ID_POKE_GET_WORLD			�X�R�A�F�|�P�����Q�b�g�i�V���I�E������O�j
		3,		//SCORE_ID_TRAINER_BATTLE_WIN		�X�R�A�F�g���[�i�[�폟��
		3,		//SCORE_ID_MINIGAME_NUTS			�X�R�A�F�؂̎�����(1�l)
		7,		//SCORE_ID_CONTEST_GRANDPRIX		�X�R�A�F�R���e�X�g�D��
		7,		//SCORE_ID_BTOWER_7WIN				�X�R�A�F�o�g���^���[7�l��������
		7,		//SCORE_ID_EGG_HATCHING				�X�R�A�F�^�}�S���z����
		10,		//SCORE_ID_COMM_TRADE_POKE			�X�R�A�F�ʐM����(Wifi/�_�C���N�g)
		10,		//SCORE_ID_CLEAR_POKEPARK			�X�R�A�F�|�P�p�[�N�N���A
		11,		//SCORE_ID_COMM_MINIGAME_NUTS		�X�R�A�F�؂̎������i�ʐM�j
		11,		//SCORE_ID_COMM_CONTEST_GRANDPRIX	�X�R�A�F�R���e�X�g�D���i�ʐM�j
		11,		//SCORE_ID_COMM_RECORD_CORNER		�X�R�A�F���R�[�h�R�[�i�[
		11,		//SCORE_ID_COMM_BATTLE_COUNT		�X�R�A�F�ʐM�ΐ�(Wifi/�_�C���N�g/���j�I��)
		20,		//SCORE_ID_ZUKAN_ENTRY				�X�R�A�F������o�^
		30,		//SCORE_ID_GYM_LEADER_WIN			�X�R�A�F�W�����[�_�[�ɏ�����
		35,		//SCORE_ID_DENDOU					�X�R�A�F�a�����肵��
		40,		//SCORE_ID_WORLD_TRADE				�X�R�A�F���E�ʐM����������
		500,	//SCORE_ID_COMMENDATION_A			�X�R�A�F�\����A���������
		10000,	//SCORE_ID_COMMENDATION_B			�X�R�A�F�\����B���������

		30,		//SCORE_ID_NEW_FLAG_TAKE_OUT		�X�R�A�F�Y�z �V�����������A��
		30,		//SCORE_ID_FLAG_TAKE_OUT			�X�R�A�F�Y�z �������A��
		2,		//SCORE_ID_GET_FOSSIL				�X�R�A�F�Y�z ���Δ��@
		5,		//SCORE_ID_ITEM_DEPOSIT				�X�R�A�F�Y�z ����ɓ���a����
		1,		//SCORE_ID_HELLO					�X�R�A�F�Y�z ����������
		1,		//SCORE_ID_QUESTION					�X�R�A�F�Y�z ���₷��
		5,		//SCORE_ID_RESCUE					�X�R�A�F�Y�z 㩂��珕����
		3,		//SCORE_ID_MAKE_BASE				�X�R�A�F�Y�z ��n���
		1,		//SCORE_ID_MINE_IN					�X�R�A�F�Y�z �n���ɗ���
		1,		//SCORE_ID_WLAK_100					�X�R�A�F�Y�z 100�����邭
	};
	return num[score_id];
}

//============================================================================================
//
//
//				����֐�
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���R�[�h���Z�b�g����
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���ڂ��w�肷��ID
 * @param	value	�Z�b�g����l
 * @return	u32		���̍��ڂ̒l
 */
//----------------------------------------------------------
u32 RECORD_Set(RECORD * rec, int id, u32 value)
{
	u32	limit = get_limit(id);
	
	if (value < limit) {
		return set_value(rec, id, value);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	�傫����΃��R�[�h���X�V����
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���ڂ��w�肷��ID
 * @param	value	�Z�b�g����l
 * @return	u32		���̍��ڂ̒l
 */
//----------------------------------------------------------
u32 RECORD_SetIfLarge(RECORD * rec, int id, u32 value)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);

	if(value > limit){
		value = limit;	//����`�F�b�N
	}
	if (now < value) {
		return set_value(rec, id, value);
	} else {
		if(now > limit){
			return set_value(rec, id, limit);
		}
		return now;
	}
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h���C���N�������g����
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���ڂ��w�肷��ID
 * @param	value	�Z�b�g����l
 * @return	u32		���̍��ڂ̒l
 */
//----------------------------------------------------------
u32 RECORD_Inc(RECORD * rec, int id)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);
	if (now + 1 < limit) {
		return set_value(rec, id, now + 1);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h�ɒl��������
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���ڂ��w�肷��ID
 * @param	value	������l
 * @return	u32		���̍��ڂ̒l
 */
//----------------------------------------------------------
u32 RECORD_Add(RECORD * rec, int id, u32 add_value)
{
	u32	limit = get_limit(id);
	u32 now = get_value(rec, id);
	if (now + add_value < limit) {
		return set_value(rec, id, now + add_value);
	} else {
		return set_value(rec, id, limit);
	}
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h���擾����
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		���ڂ��w�肷��ID
 * @return	u32		���̍��ڂ̒l
 */
//----------------------------------------------------------
u32 RECORD_Get(const RECORD * rec, int id)
{
	u32	limit = get_limit(id);
	u32	value = get_value(rec, id);

	if(value > limit){
		return limit;
	}else{
		return value;
	}
}

//----------------------------------------------------------
/**
 * @brief	�X�R�A�̉��Z
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	id		�X�R�A�w���ID
 */
//----------------------------------------------------------
void RECORD_Score_Add(RECORD * rec, int id)
{
	u32 score;
	
	GF_ASSERT(id < SCOREID_MAX);
	
	//�J���X�g�`�F�b�N����
	score = RECORD_Get(rec, RECID_SCORE);
	if ( score+get_score_number(id) > SCORE_MAX ){
		RECORD_Set(rec, RECID_SCORE, SCORE_MAX);
	}else{
		RECORD_Add(rec, RECID_SCORE, get_score_number(id));
	}
}


//----------------------------------------------------------
/**
 * @brief	�X�R�A�̎擾
 * @param	rec		RECORD�ւ̃|�C���^
 * @return	u32		���݂̃X�R�A
 */
//----------------------------------------------------------
u32 RECORD_Score_Get(const RECORD * rec)
{
	return RECORD_Get(rec, RECID_SCORE);
}

//----------------------------------------------------------
/**
 * @brief	�}�ӃX�R�A�̉��Z
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @param	monsno	�|�P�����i���o�[
 */
//----------------------------------------------------------
void RECORD_Score_AddZukanScore(RECORD * rec, const ZUKAN_WORK * zw, u16 const inMonsno)
{
	if ( !ZukanWork_GetPokeGetFlag(zw, inMonsno) ){
		RECORD_Score_Add(rec, SCORE_ID_ZUKAN_ENTRY);
	}
}

#ifdef PM_DEBUG
//----------------------------------------------------------
/**
 * @brief	�X�R�A�̃Z�b�g
 * @param	rec		RECORD�ւ̃|�C���^
 * @param	inScore	�Z�b�g����X�R�A
 */
//----------------------------------------------------------
void RECORD_Score_DebugSet(RECORD * rec, const u32 inScore)
{
	u32 score;

	score = inScore;
	
	//�J���X�g�`�F�b�N����
	if ( score > SCORE_MAX ){
		score = SCORE_MAX;
	}

	RECORD_Set(rec, RECID_SCORE, score);
}

#endif	//PM_DEBUG


