//============================================================================================
/**
 * @file	seedbed.c
 * @author	tamada
 * @date	2005.02.01
 * @brief	���̂ݏ�ԃf�[�^����
 */
//============================================================================================

#include "common.h"

#include "seedbed_local.h"
#include "savedata/seedbed.h"

#include "gflib/system.h"
#include "itemtool/nuts.h"

#ifdef	DEBUG_ONLY_FOR_tamada
#define	DEBUG_SEED_INFO
#endif

#ifdef	DEBUG_SEED_INFO
#define	PUT_SEED_INFO(s,i)	PrintSeedInfo((s),(i))
#else
#define	PUT_SEED_INFO(s,i)	/* Do Nothing */
#endif

//============================================================================================
//				��`
//============================================================================================
enum {
		///�������J��Ԃ��ő吔
		SEED_ROUND_MAX		=	10,

		///�����Ȃ�����Ԃł̐������ԌW��
		FRUIT_TIME_RATE		=	4,

		///	�y��HP�ő�l
		GROUND_HP_MAX	= 100,

		///	���̂�HP�̍ő�l
		SEED_HP_BASE = 5,
		SEED_HP_MID	= 3,
};

static void InitSeed(SEEDBED * s);
static int get_grow_time(const SEED_TABLE * prm, int type, int compost);
//============================================================================================
//
//
//		�Z�[�u�f�[�^�C���^�[�t�F�C�X
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���̂ݏ�ԃf�[�^�T�C�Y�̎擾
 * @return	int		���̂ݏ�ԃf�[�^�̃T�C�Y
 */
//----------------------------------------------------------
int SEEDBED_GetWorkSize(void)
{
	return sizeof(SEEDBED) * SEEDBED_MAX;
}

//----------------------------------------------------------
/**
 * @brief	���̂ݏ�ԃf�[�^�p�������m��
 * @param	heapID		�m�ۂ���q�[�v�̎w��
 * @return	SEEDBED		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 */
//----------------------------------------------------------
SEEDBED * SEEDBED_AllocWork(u32 heapID)
{
	SEEDBED * sbed;
	sbed = sys_AllocMemory(heapID, sizeof(SEEDBED) * SEEDBED_MAX);
	return sbed;
}

//----------------------------------------------------------
/**
 * @brief	���̂ݏ�ԃf�[�^�S�̂̏�����
 * @param	SEEDBED		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 */
//----------------------------------------------------------
void SEEDBED_Init(SEEDBED * sbed)
{
	int i;
	MI_CpuClear8(sbed, sizeof(SEEDBED) * SEEDBED_MAX);

	for (i = 0; i < SEEDBED_MAX; i++) {
		sbed[i].stat = SEEDSTAT_NOTHING;
		sbed[i].type = 0;
	}
}

//----------------------------------------------------------
/**
 * @brief	���݂̂̏�����ԃZ�b�g
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	heapID
 * @param	init_data
 * @param	max
 */
//----------------------------------------------------------
void SEEDBED_SetDefaultData(SEEDBED * sbed, int heapID, const u16 * init_data, int max)
{
	int i;
	SEED_TABLE * prm = SEEDBED_CreateParamTable(heapID);

	for (i = 0; i < SEEDBED_MAX || i < max; i++) {
		InitSeed(&sbed[i]);
			sbed[i].type = init_data[i * 2] - NUTS_START_ITEMNUM + 1;
			sbed[i].stat = SEEDSTAT_FRUIT;
			sbed[i].grow_time = get_grow_time(prm, sbed[i].type, sbed[i].compost) * FRUIT_TIME_RATE;
			sbed[i].nuts_count = init_data[i * 2 + 1];
			sbed[i].ground_hp = GROUND_HP_MAX;
			sbed[i].seed_hp = SEED_HP_MID;
	}
	sys_FreeMemoryEz(prm);
}

//----------------------------------------------------------
/**
 * @brief	���̂ݐ�����������p�e�[�u���̐���
 * @param	heapID
 */
//----------------------------------------------------------
SEED_TABLE * SEEDBED_CreateParamTable(int heapID)
{
	int i;
	SEED_TABLE * tbl;
	NUTSDATA * data;
	ARCHANDLE * hdl;
	hdl = Nuts_DataHandleGet(heapID);
	tbl = sys_AllocMemory(heapID, sizeof(SEED_TABLE) * ITEM_NUTS_MAX);
	for (i = 0; i < ITEM_NUTS_MAX; i++) {
		data = Nuts_DataLoadHandle(hdl, i, heapID);
		tbl[i].grow_speed = Nuts_ParamGet(data, NUTS_PRM_SPEED);
		tbl[i].root_power = Nuts_ParamGet(data, NUTS_PRM_ABSORPTION);
		tbl[i].nuts_rate = Nuts_ParamGet(data, NUTS_PRM_MAGNIFICATION);
		sys_FreeMemoryEz(data);
	}
	Nuts_DataHandleClose(hdl);
	return tbl;
}



//============================================================================================
//
//		�����c�[���֐�
//
//============================================================================================
#ifdef	DEBUG_SEED_INFO
//----------------------------------------------------------
/**
 * @brief	�f�o�b�O���̕\��
 * @param	bed
 * @param	i
 */
//----------------------------------------------------------
static void PrintSeedInfo(const SEEDBED * bed, int i)
{
	const SEEDBED * s = bed + i;
	if (s->stat == SEEDSTAT_NOTHING) {
		return;
	}
	OS_Printf("SEED (ID:%03d) FLAG:%d STAT:%d TYPE:%02d\n",
			i, s->growth_flag, s->stat, s->type);
	OS_Printf("     COMPOST:%d GROUND:%03d NUTS:%d\n",
			s->compost, s->ground_hp, s->nuts_count);
	OS_Printf("     HP:%02d ROUND:%d gtime:%d dtime:%d\n",
			s->seed_hp, s->seed_count,s->grow_time, s->dry_time);
}
#endif

//----------------------------------------------------------
/**
 * @brief	���̂݃f�[�^������
 * @param	s	���̂ݏ�ԃf�[�^�ւ̃|�C���^
 */
//----------------------------------------------------------
static void InitSeed(SEEDBED * s)
{
	s->type = 0;
	s->stat = SEEDSTAT_NOTHING;
	s->grow_time = 0;
	s->dry_time = 0;
	s->seed_count = 0;
	s->nuts_count = 0;
	s->ground_hp = 0;
	s->seed_hp = 0;
	s->compost = SEEDCOMPOST_NOTHING;
	s->growth_flag = FALSE;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int count_nuts(SEEDBED * s, const SEED_TABLE * prm)
{
	//�؂̎�HP�@�~�@���̔{��
	return	prm[s->type -1].nuts_rate * s->seed_hp;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_grow_time(const SEED_TABLE * prm, int type, int compost)
{
	int time;
	time = prm[type - 1].grow_speed * 60;
	if (compost == SEEDCOMPOST_SUKUSUKU) {
		time = (time * 3) / 4;		// base * 0.75
	} else if (compost == SEEDCOMPOST_YURURI) {
		time = time + (time / 2);	// base * 1.5
	}
	return time;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_root_power(const SEED_TABLE * prm, int type, int compost)
{
	int power = prm[type - 1].root_power;
	if (compost == SEEDCOMPOST_YURURI) {
		return power / 2;
	} else if (compost == SEEDCOMPOST_SUKUSUKU) {
		return power + power / 2;
	} else {
		return power;
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_nuts_time_rate(const SEEDBED * s)
{
	//�~�i�[���R���V���g���Ă���Ƃ��A���������Ă��鎞�Ԃ�1.5�{�ɂȂ�
	if (s->compost == SEEDCOMPOST_MINAARU) {
		return FRUIT_TIME_RATE + 2;
	} else {
		return FRUIT_TIME_RATE;
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_round_max(const SEEDBED * s)
{
	//�˂΂肱�₵���g���Ă���Ƃ��A�������T�񑝂���
	if (s->compost == SEEDCOMPOST_NEBARI) {
		return SEED_ROUND_MAX + 5;
	} else {
		return SEED_ROUND_MAX;
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_life_time(SEEDBED * s)
{
	//�������J��Ԃ��ď�����܂ł̒���
	//�ŏ��̓y�̒�+�i��+�s+��+��) * SEED_ROUND_MAX;
	//LIFE_TIME_LEN		=	1+(1+1+1+FRUIT_TIME_RATE) * SEED_ROUND_MAX,
	return 1 + (1+1+1+get_nuts_time_rate(s)) * get_round_max(s);
}



//============================================================================================
//
//
//		���̂ݏ�ԃA�N�Z�X�p�O�����J�֐�
//
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	���݂̂̏�Ԏ擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @return	SEEDSTAT	���݂̂̏�ԁiseedbed.h�̒�`���Q�Ɓj
 */
//----------------------------------------------------------
SEEDSTAT SEEDBED_GetSeedStatus(const SEEDBED * sbed, int id)
{
	return sbed[id].stat;
}
//----------------------------------------------------------
/**
 * @brief	���݂̂̎�ނ��擾
 * @param	sbed		���̂ݏ�ԃf�[�^�ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @return	int			���݂̂̎�ށi�O�`ITEM_NUTS_MAX)
 */
//----------------------------------------------------------
int SEEDBED_GetSeedType(const SEEDBED * sbed, int id)
{
	return sbed[id].type;
}
//----------------------------------------------------------
/**
 * @brief	�����̏�Ԃ��擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @return	SEEDGROUND	������ԁiseedbed.h�̒�`���Q�Ɓj
 */
//----------------------------------------------------------
SEEDGROUND SEEDBED_GetGroundStatus(const SEEDBED * sbed, int id)
{
	int gr_hp;
	gr_hp = sbed[id].ground_hp;

	if (gr_hp == 0) {
		return SEEDGROUND_DRY;
	} else if (gr_hp <= 50) {
		return SEEDGROUND_WET;
	} else {
		return SEEDGROUND_FULL;
	}
}
//----------------------------------------------------------
/**
 * @brief	���݂̂�HP���擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @return	int			���݂̂�HP�i�O�`�P�O�j
 */
//----------------------------------------------------------
int SEEDBED_GetSeedHP(const SEEDBED * sbed, int id)
{
	return	sbed[id].seed_hp;
}


//----------------------------------------------------------
/**
 * @brief	���݂̂�A����
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @param	prm			���݂̂̎�ޖ��p�����[�^�e�[�u��
 * @param	type		���݂̂̎��
 */
//----------------------------------------------------------
void SEEDBED_SetNuts(SEEDBED * sbed, int id, const SEED_TABLE * prm, int type)
{
	//InitSeed(&sbed[id]);
	sbed[id].type = type;
	sbed[id].stat = SEEDSTAT_UNDERGROUND;
	sbed[id].grow_time = get_grow_time(prm, type, sbed[id].compost);
	sbed[id].dry_time = 0;
	sbed[id].seed_count = 0;
	sbed[id].nuts_count = 0;
	sbed[id].ground_hp = GROUND_HP_MAX;
	sbed[id].seed_hp = SEED_HP_BASE;
	//sbed[id].compost = co;
	sbed[id].growth_flag = TRUE;
	PUT_SEED_INFO(sbed,id);
}


//----------------------------------------------------------
/**
 * @brief	����������
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 */
//----------------------------------------------------------
void SEEDBED_SetSeedWater(SEEDBED * sbed, int id)
{
	sbed[id].ground_hp = GROUND_HP_MAX;
	PUT_SEED_INFO(sbed, id);
}

//----------------------------------------------------------
/**
 * @brief	�����t���O�̎擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @return	BOOL		TRUE�̂Ƃ��A��������
 */
//----------------------------------------------------------
BOOL SEEDBED_GetGrowthFlag(const SEEDBED * sbed, int id)
{
	return sbed[id].growth_flag;
}

//----------------------------------------------------------
/**
 * @brief	�����t���O�̃Z�b�g
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @param	flag		TRUE�̂Ƃ��A��������
 */
//----------------------------------------------------------
void SEEDBED_SetGrowthFlag(SEEDBED * sbed, int id, BOOL flag)
{
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_Printf("SEED:%d %s\n",id, (flag?"ON":"OFF"));
#endif
	sbed[id].growth_flag = flag;
}

//----------------------------------------------------------
/**
 * @brief	�R���V�̎�ނ��擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @param	compost		�R���V�̎w��
 */
//----------------------------------------------------------
SEEDCOMPOST SEEDBED_GetCompost(const SEEDBED * sbed, int id)
{
	return sbed[id].compost;
}

//----------------------------------------------------------
/**
 * @brief	�R���V���Z�b�g����
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 * @param	compost		�R���V�̎w��
 */
//----------------------------------------------------------
void SEEDBED_SetCompost(SEEDBED * sbed, int id, SEEDCOMPOST compost)
{
	sbed[id].compost = compost;
	PUT_SEED_INFO(sbed,id);
}
//----------------------------------------------------------
/**
 * @brief	���݂̂̐����擾
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 */
//----------------------------------------------------------
int SEEDBED_GetSeedCount(const SEEDBED * sbed, int id)
{
	PUT_SEED_INFO(sbed, id);
	return sbed[id].nuts_count;
}

//----------------------------------------------------------
/**
 * @brief	���݂̂����n
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	id			���݂̂��w�肷��ID
 */
//----------------------------------------------------------
int SEEDBED_GetHarvest(SEEDBED * sbed, int id)
{
	int harvest;
	harvest = sbed[id].nuts_count;
	InitSeed(&sbed[id]);
	PUT_SEED_INFO(sbed,id);
	return harvest;
}

//-------------------------------------------------------------------------
/**
 * @brief	���݂̂���Ă�
 * @param	sbed		���̂ݏ�ԃf�[�^�ւ̃|�C���^
 * @param	prm		���݂̂̎�ޖ��p�����[�^�e�[�u��
 */
//-------------------------------------------------------------------------
static void SeedGrowth(SEEDBED *s, const SEED_TABLE * prm)
{
	switch (s->stat) {

	case SEEDSTAT_NOTHING:		// �A���Ă��Ȃ�
		GF_ASSERT(0);
		break;

	case SEEDSTAT_UNDERGROUND:	// �A��������
	case SEEDSTAT_HUTABA:		// �o�t�A���蒼��
	case SEEDSTAT_MIKI:			// ���A������
		s->stat ++;
		break;

	case SEEDSTAT_FLOWER:		// ��
		s->nuts_count = count_nuts(s, prm);
		if (s->nuts_count < 2) {
			//�Œ�2�͎����Ȃ�
			s->nuts_count = 2;
		}
		s->stat ++;
		break;

	case SEEDSTAT_FRUIT:		// �����Ȃ������
		s->nuts_count = 0;
		s->stat = SEEDSTAT_HUTABA;
		//s->ground_hp = GROUND_HP_MAX;
		s->seed_hp = SEED_HP_BASE;
		s->seed_count ++;
		if (s->seed_count == get_round_max(s)) {
			InitSeed(s);
		}
		break;
	}
}

//----------------------------------------------------------
/**
 * @brief	���̋z������
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	prm			���݂̂̎�ޖ��p�����[�^�e�[�u��
 * @param	minute		�i�񂾎��ԁi���P�ʁj
 */
//----------------------------------------------------------
static void AbsorbWater(SEEDBED * s, const SEED_TABLE * prm, int count)
{
	int dec_count;
	int root_pow;
	int rest_count;
	if (s->stat == SEEDSTAT_FRUIT) {
		//�����Ȃ��Ă����Ԃł͂g�o�͕ω����Ȃ�
		return;
	}
	root_pow = get_root_power(prm, s->type, s->compost);
	count += s->dry_time;
	dec_count = count / 60;		//1���ԁ��P�|�C���g
	s->dry_time = count % 60;	//���܂�͏W�v���Ă���
	if (dec_count == 0) {
		return;
	}
	if (s->ground_hp >= root_pow * dec_count) {
		s->ground_hp -= root_pow * dec_count;
		return;
	}

	if (s->ground_hp > 0) {
		//�y��HP�����炷�̂ɉ����ԕK�v���i�؂�グ�j�Ōv�Z
		rest_count = (s->ground_hp + (root_pow - 1)) / root_pow;
		dec_count -= rest_count;
		s->ground_hp = 0;
	}

	//���ɗ]�n���Ȃ��Ȃ����̂Ń|�C���g�������̂�HP�����炷
	if (s->seed_hp > dec_count) {
		s->seed_hp -= dec_count;
	} else {
		s->seed_hp = 0;
	}
}

//----------------------------------------------------------
/**
 * @brief	���݂̂𐬒�������
 * @param	sbed		���̂ݏ�ԃf�[�^�S�̂ւ̃|�C���^
 * @param	prm		���݂̂̎�ޖ��p�����[�^�e�[�u��
 * @param	minute		�i�񂾎��ԁi���P�ʁj
 */
//----------------------------------------------------------
void SEEDBED_Growth(SEEDBED * sbed, const SEED_TABLE * prm, int minute)
{
	int i;
	s32 count;
	SEEDBED * s;

	for (i = 0; i < SEEDBED_MAX; i++) {
		s = &sbed[i];
		if ( s->type == 0
				|| s->stat == SEEDSTAT_NOTHING
				|| s->growth_flag == FALSE) {
			//��ގw�肪�Ȃ��A�؂̎����A�����Ă��Ȃ��A�������Ȃ��ꍇ�͎���
			continue;
		}
		if (minute >= get_grow_time(prm, s->type, s->compost) * get_life_time(s)) {
			//�����ȏ�̎��Ԃ��o�߂����ꍇ�͏���������
			InitSeed(s);
			continue;
		}

		//�����J�E���g����
		count = minute;

		while (s->stat != SEEDSTAT_NOTHING && count != 0) {
			if (s->grow_time > count) {
				//���z���J�E���g����
				AbsorbWater(s, prm, count);
				s->grow_time -= count;
				count = 0;
				break;
			}else{
				//���z���J�E���g����
				AbsorbWater(s, prm, s->grow_time);
				//��������
				SeedGrowth(s, prm);
				//���̒i�K�܂ł̃J�E���g���Z�b�g
				count -= s->grow_time;
				s->grow_time = get_grow_time(prm, s->type, s->compost);
				if (s->stat == SEEDSTAT_FRUIT) {
					s->grow_time *= get_nuts_time_rate(s);
				}
				PUT_SEED_INFO(sbed,i);
			}
		}

	}
}


