/**
 *	@file	poruto.c
 *	@brief	�|���g�Z�[�u�f�[�^ ����
 *	@author	Miyuki Iwasawa
 *	@date	06.2.28
 */

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/poruto.h"
#include "savedata/poruto_util.h"
#include "savedata/poruto_local.h"

/**
 *	@brief	�|���g�f�[�^�T�C�Y�擾
 */
int PorutoData_GetWorkSize(void)
{
	return sizeof(PORUTO_DATA);
}

/**
 *	@brief	���̃|���g�f�[�^���L�����ǂ����Ԃ�
 */
BOOL PorutoData_IsEnable(PORUTO_DATA* dat)
{
	if(dat->flavor == PORUTO_FLAVOR_NULL){
		return FALSE;
	}
	return TRUE;
}

/**
 *	@brief	�|���g�f�[�^�N���A
 */
void PorutoData_Clear(PORUTO_DATA* dat)
{
	dat->flavor = PORUTO_FLAVOR_NULL;
	dat->spicy = 0;
	dat->astringent = 0;
	dat->sweet = 0;
	dat->bitter = 0;
	dat->sour = 0;
	dat->taste = 0;
	dat->pad_dmy = 0;
}

/**
 *	@brief	�|���g�f�[�^���[�N�쐬
 */
PORUTO_DATA* PorutoData_AllocWork(int heapID)
{
	PORUTO_DATA* dat;

	dat = sys_AllocMemoryLo(heapID,sizeof(PORUTO_DATA));
	PorutoData_Clear(dat);
	return dat;
}

/**
 *	@brief	�|���g�f�[�^�R�s�[
 */
void PorutoData_Copy(PORUTO_DATA* src,PORUTO_DATA* dest)
{
	dest->flavor = src->flavor;
	dest->spicy = src->spicy;
	dest->astringent = src->astringent;
	dest->sweet = src->sweet;
	dest->bitter = src->bitter;
	dest->sour = src->sour;
	dest->taste = src->taste;
	dest->pad_dmy = src->pad_dmy;
}

/**
 *	@brief	�|���g�̃p�����[�^���擾
 *
 *	@param	dat
 *	@param	id	enum PORUTO_PARAID�^(poruto_def.h�Q��)
 *
 *	@return	u8:�擾�����p�����[�^
 */
u8 PorutoData_GetParam(PORUTO_DATA* dat,PORUTO_PARAID id)
{
	switch(id){
	case PORUTO_PARAID_FLAVOR:
		return dat->flavor;
	case PORUTO_PARAID_SPICY:
		return dat->spicy;
	case PORUTO_PARAID_ASTR:
		return dat->astringent;
	case PORUTO_PARAID_SWEET:
		return dat->sweet;
	case PORUTO_PARAID_BITTER:
		return dat->bitter;
	case PORUTO_PARAID_SOUR:
		return dat->sour;
	case PORUTO_PARAID_TASTE:
	default:
		return dat->taste;
	}
}
	
/**
 *	@brief	�|���g�̃p�����[�^���Z�b�g
 *
 *	@param	dat
 *	@param	value	�Z�b�g�������f�[�^
 *	@param	id	enum PORUTO_PARAID�^(poruto_def.h�Q��)
 *
 */
void PorutoData_SetParam(PORUTO_DATA* dat,u8 valid,PORUTO_PARAID id)
{
	if(id == PORUTO_PARAID_FLAVOR){
		if(valid < PORUTO_FLAVOR_MAX){
			dat->flavor = valid;
		}
		return;	
	}
	if(valid >= PORUTO_PARAM_MAX){
		return;
	}
	switch(id){
	case PORUTO_PARAID_SPICY:
		dat->spicy = valid;
		break;
	case PORUTO_PARAID_ASTR:
		dat->astringent = valid;
		break;
	case PORUTO_PARAID_SWEET:
		dat->sweet = valid;
		break;
	case PORUTO_PARAID_BITTER:
		dat->bitter = valid;
		break;
	case PORUTO_PARAID_SOUR:
		dat->sour = valid;
		break;
	case PORUTO_PARAID_TASTE:
		dat->taste = valid;
		break;
	default:
		break;
	}
	return;
}

//�s�����|���g�𐶐�
static void porudata_MakeNoGoodPoruto(PORUTO_DATA *dat,u8 taste)
{
	int ct;
	u8 id;

	ct = 0;
	do{
		id = gf_rand()%PORUTO_FTYPE_NUM;
		if(dat->param[id+1] != 0){
			continue;
		}
		dat->param[id+1] = 2;
		++ct;
	}while(ct < 3);
	dat->flavor = PORUTO_FLAVOR_NGOOD;
	dat->taste = taste;
}

/**
 *	@brief	���Ǝ|������|���g�̎�ނ����肵�A�p�����[�^���Z�b�g���ĕԂ�
 *
 *	@param	dat	PORUTO_DATA*:�p�����[�^���Z�b�g����|���g�f�[�^�^�\����
 *	@param	prm	u8[5]:5��ނ̖��l���i�[
 *	@param	taste	�|���l���i�[
 *	@param	mazui	�����I�ɕs�����|���g�ɂȂ邩�ǂ����H TRUE�Ȃ�܂����|���g
 *
 *	@return	PORUTO_FLAVORID	�쐬���ꂽ�|���g�̃t���o�[ID
 */
PORUTO_FLAVORID PorutoData_CalcParam(PORUTO_DATA* dat,u8 *prm,u8 taste,BOOL mazui)
{
	int i,fct = 0;
	u8	kind[5];	
	u8	maro_f = 0,fid = 0;

	fid = PORUTO_FLAVOR_NGOOD;

	if(mazui){
		//�܂����|���g
		porudata_MakeNoGoodPoruto(dat,taste);
		return fid;
	}
	
	//�����Ă��閡�l�̐������Z
	for(i = 0;i < 5;i++){
		if(prm[i]){
			if(prm[i] >=  50){
				maro_f = 1;	//�܂�₩�t���O
			}
			kind[fct++] = i;
		}
	}
	
	switch(fct){
	case 0:	//�܂����|���g
		porudata_MakeNoGoodPoruto(dat,taste);
		return fid;
	case 1:	//�������
		fid = kind[0]*5+kind[0];
		break;
	case 2:	//�������
		if(prm[kind[0]] >= prm[kind[1]]){
			fid = kind[0]*5+kind[1];
		}else{
			fid = kind[1]*5+kind[0];
		}
		break;
	case 3:	//�����Ă�
		fid = PORUTO_FLAVOR_HEAVY;
		break;
	case 4:	//���ǂ�
	case 5:
		fid = PORUTO_FLAVOR_THICK;
		break;
	}
	if(maro_f){	//���l��50���z�������̂���ł�����΂܂�₩
		fid = PORUTO_FLAVOR_MILD;
	}
	//�p�����[�^�i�[
	for(i = 0;i < 5;i++){
		dat->param[i+1] = prm[i];
	}
	//���l�Ǝ|���l���i�[
	dat->flavor = fid;
	dat->taste = taste;
	return fid;
}

/**
 *	@brief	�|���g�p�����[�^�擾(�z���)
 *
 *	���Ăяo�����Ńf�[�^�̎擾�ꏊ��p�ӂ���o�[�W����
 *	�@u8[PORUTO_PARAID_NUM] ���̃������G���A���K�v
 */
void PorutoData_GetParamArray(PORUTO_DATA* dat,u8* array)
{
	array[PORUTO_PARAID_FLAVOR] = dat->flavor;
	array[PORUTO_PARAID_SPICY] = dat->spicy;
	array[PORUTO_PARAID_ASTR] = dat->astringent;
	array[PORUTO_PARAID_SWEET] = dat->sweet;
	array[PORUTO_PARAID_BITTER] = dat->bitter;
	array[PORUTO_PARAID_SOUR] = dat->sour;
	array[PORUTO_PARAID_TASTE] = dat->taste;
}

/**
 *	@brief	�|���g�p�����[�^�擾(�z��,�������m�۔�)
 *
 *	���֐����ŕK�v�ȃo�b�t�@���擾���ĕԂ��o�[�W����
 *	�@�Ăяo�����Ŗ����I�ȃ�����������K�v
 */
u8* PorutoData_GetParamArrayMem(PORUTO_DATA* dat,int heapID)
{
	u8* array;

	array = sys_AllocMemory(heapID,PORUTO_PARAID_NUM);
	array[PORUTO_PARAID_FLAVOR] = dat->flavor;
	array[PORUTO_PARAID_SPICY] = dat->spicy;
	array[PORUTO_PARAID_ASTR] = dat->astringent;
	array[PORUTO_PARAID_SWEET] = dat->sweet;
	array[PORUTO_PARAID_BITTER] = dat->bitter;
	array[PORUTO_PARAID_SOUR] = dat->sour;
	array[PORUTO_PARAID_TASTE] = dat->taste;
	return array;
}

/**
 *	@brief	�|���g�̃��x�����擾
 */
u8 PorutoData_GetLevel(PORUTO_DATA* dat)
{
	u8	type = 0;
	u8	level = 0;

	type = dat->flavor / PORUTO_FTYPE_NUM;
	switch(type){
	case PORUTO_FTYPE_SPICY:
		level = dat->spicy;
		break;
	case PORUTO_FTYPE_ASTR:
		level = dat->astringent;
		break;
	case PORUTO_FTYPE_SWEET:
		level = dat->sweet;
		break;
	case PORUTO_FTYPE_BITTER:
		level = dat->bitter;
		break;
	case PORUTO_FTYPE_SOUR:
		level = dat->sour;
		break;
	case PORUTO_FTYPE_MIX:
	default:
		//�~�b�N�X�n�͈�ԍ����p�����[�^��T��
		level = dat->spicy;
		if(level < dat->astringent){
			level = dat->astringent;
		}
		if(level < dat->sweet){
			level = dat->sweet;
		}
		if(level < dat->bitter){
			level = dat->bitter;
		}
		if(level < dat->sour){
			level = dat->sour;
		}
		break;
	}
	if(level > PORUTO_PARAM_VMAX){
		return PORUTO_PARAM_VMAX;
	}
	return level;
}

//=================================================================
// �|���g�Z�[�u�f�[�^�u���b�N�A�N�Z�X�n
//=================================================================

/**
 *	@brief	�Z�[�u�f�[�^�u���b�N�ւ̃|�C���^���擾
 */
PORUTO_BLOCK* SaveData_GetPorutoBlock(SAVEDATA* sv)
{
	return SaveData_Get(sv,GMDATA_ID_PORUTODATA);
}

/**
 *	@brief	�|���g�Z�[�u�f�[�^�T�C�Y�擾
 */
int PORUTO_GetSaveWorkSize(void)
{
	return sizeof(PORUTO_DATA)*PORUTO_STOCK_MAX;
}

/**
 *	@brief	�|���g�f�[�^�z�񏉊���
 */
void PORUTO_Init(PORUTO_BLOCK* block)
{
	int i = 0;
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PorutoData_Clear(&block->poruto[i]);
	}
}

/**
 *	@brief	�|���g�Z�[�u�f�[�^�̋󂫗̈��T��
 *
 *	@retval	PORUTO_DATA_NULL	�󂫗̈悪�Ȃ�
 *	@retval "���̑�"			�󂫗̈��IndexNo
 */
u16 PORUTO_SearchNullData(PORUTO_BLOCK* block)
{
	u16 i;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(block->poruto[i].flavor == PORUTO_FLAVOR_NULL){
			return i;
		}
	}
	return PORUTO_DATA_NULL;
}

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^�󂫗̈�ɒǉ�����
 *
 *	@retval	PORUTO_DATA_NULL	�󂫗̈悪�Ȃ��Ēǉ��ł��Ȃ�����
 *	@retval "���̑�"			�ǉ������̈��index
 */
u16 PORUTO_AddData(PORUTO_BLOCK* block,PORUTO_DATA* dat) 
{
	u16	idx = PORUTO_SearchNullData(block);

	if(idx == PORUTO_DATA_NULL){
		return idx;
	}
	//�ǉ�
	PorutoData_Copy(dat,&block->poruto[idx]);
	return idx;
}

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����폜����(index�w��)
 *
 */
BOOL PORUTO_DelData(PORUTO_BLOCK* block,u16 idx) 
{
	if(idx >= PORUTO_STOCK_MAX){
		return FALSE;
	}
	//�폜
	PorutoData_Clear(&block->poruto[idx]);
	return TRUE;
}

/**
 *	@brief	�w�肵��index��̎��̗L���f�[�^��index��Ԃ�
 *
 */
static u16	poruto_GetNextValiableIndex(PORUTO_BLOCK* block,u16 now)
{
	u16	i;

	for(i = now;i < PORUTO_STOCK_MAX;i++){
		if(block->poruto[i].flavor != PORUTO_FLAVOR_NULL){
			//�L���f�[�^����
			return i;
		}
	}
	//�L���f�[�^�͌�����Ȃ�����
	return 0xFFFF;
}
/**
 *	@brief	�|���g�Z�[�u�f�[�^�𐮗�����
 *
 *	���f�[�^�z��̌��󂫂��l�߂�
 */
void PORUTO_DataAdjust(PORUTO_BLOCK* block)
{
	u16 i,j,tmp;
	u16	s,d,rest;

	//�c��̐�������
	rest = PORUTO_STOCK_MAX;

	for(i = 0;i < rest;i++){
		if(block->poruto[i].flavor != PORUTO_FLAVOR_NULL){
			continue;
		}
		s = i;
		tmp = poruto_GetNextValiableIndex(block,s);
		if(tmp == 0xFFFF){
			//����ȏ��ɗL���f�[�^�͂Ȃ�
			break;	//�I��
		}
		d = tmp;
		tmp = d-s;
		for(;d < rest;s++,d++){
			PorutoData_Copy(&block->poruto[d],&block->poruto[s]);
			PorutoData_Clear(&block->poruto[d]);
		}
		rest -= tmp;
	}
}

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����擾����(index�w��)
 *
 *	�������n���ꂽPORUTO_DATA�\���̌^�̈�ցA�Z�[�u�f�[�^���R�s�[���ĕԂ�
 */
void PORUTO_GetData(PORUTO_BLOCK* block,u16 idx,PORUTO_DATA* dest)
{
	if(idx >= PORUTO_STOCK_MAX){
		PorutoData_Clear(dest);
		return;
	}
	//�擾
	PorutoData_Copy(&block->poruto[idx],dest);
	return ;
}

/**
 *	@brief	�|���g�f�[�^���Z�[�u�f�[�^����擾����(index�w��/�������m�۔�)
 *
 *	��PORUTO_DATA�\���̌^�̈���m�ۂ��A�Z�[�u�f�[�^���R�s�[���ĕԂ�
 *	�@�Ăяo�����������I�ɉ�����邱�ƁI
 */
PORUTO_DATA* PORUTO_GetDataAlloc(PORUTO_BLOCK* block,u16 idx,int heapID)
{
	PORUTO_DATA* dest;
	
	dest = PorutoData_AllocWork(heapID);
	
	if(idx >= PORUTO_STOCK_MAX){
		PorutoData_Clear(dest);
		return NULL;
	}
	
	//�擾
	PorutoData_Copy(&block->poruto[idx],dest);
	return dest;
}

/**
 *	@brief	�Z�[�u�f�[�^�̈�ɂ���L���ȃ|���g�f�[�^����Ԃ�
 */
u16	PORUTO_GetDataNum(PORUTO_BLOCK* block)
{
	u16	num = 0,i;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(PorutoData_IsEnable(&block->poruto[i])){
			++num;
		}
	}
	return num;
}

#ifdef PM_DEBUG
/**
 *	@brief	�|���g�f�o�b�O�@�f�[�^�S������
 */
void PorutoDebug_AllDataDelete(PORUTO_BLOCK* block)
{
	u16	i = 0;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PorutoData_Clear(&block->poruto[i]);
	}
}

/**
 *	�K���ȃp�����[�^�������_����������
 */
#define PARA_DMYMAX	(99)
#define PARA_DMYNMAX	(48)
static void porudeb_CreateRndParam(PORUTO_DATA* dat,u8 level)
{
	u8	main,sub;
	u8	param[PORUTO_PARAID_NUM];

	MI_CpuClear8(param,PORUTO_PARAID_NUM);

	//���C���̖������߂�
	main = gf_rand()%PORUTO_FTYPE_MAX;

	//�~�b�N�X���閡�����߂�
	sub = gf_rand()%PORUTO_FTYPE_NUM;

	if(main == PORUTO_FTYPE_MIX){
		u8 i,j,ct;
		switch(sub){
		case 0:	//�܂���
			for(ct = 0;ct < 3;ct++){
				j = gf_rand()%PORUTO_FTYPE_NUM;
				for(i = 0;i < PORUTO_FTYPE_NUM;i++){
					if(param[j] == 0){
						break;
					}
					j = (j+1)%PORUTO_FTYPE_NUM;	
				}
				param[j] = 2;
			}
			dat->flavor = PORUTO_FLAVOR_NGOOD;
			break;
		case 1:	//�܂�₩
			i = gf_rand()%PORUTO_FTYPE_NUM;
			j = gf_rand()%PORUTO_FTYPE_NUM;
			param[i] = gf_rand()%(PARA_DMYMAX-PORUTO_MILD_VALUE)+PORUTO_MILD_VALUE;
			param[j] = gf_rand()%(PARA_DMYMAX-PORUTO_MILD_VALUE)+PORUTO_MILD_VALUE;
			dat->flavor = PORUTO_FLAVOR_MILD;
			break;
		default:
			for(ct = 0;ct < (sub+1);ct++){
				j = gf_rand()%PORUTO_FTYPE_NUM;
				for(i = 0;i < PORUTO_FTYPE_NUM;i++){
					if(param[j] == 0){
						break;
					}
					j = (j+1)%PORUTO_FTYPE_NUM;	
				}
				param[j] = gf_rand()%(PARA_DMYMAX-1)+1;
			}
			if(sub == 2){
				dat->flavor = PORUTO_FLAVOR_HEAVY;
			}else{
				dat->flavor = PORUTO_FLAVOR_THICK;
			}
			break;
		}
	}else{
		//���C��
		param[main] = gf_rand()%(PARA_DMYNMAX)+2;
		//�T�u
		if(sub != main){	//���C���ȉ��̒l��ݒ�
			param[sub] = gf_rand()%(param[main]-1)+1;
		}
		dat->flavor = main*PORUTO_FTYPE_NUM+sub;	//������
	}
	//�|��������
	if(level > 99){
		dat->taste = 99;//gf_rand()%PARA_DMYMAX;
	}else{
		dat->taste = level;
	}

	//���̃p�����[�^�������o��
	dat->spicy = param[0];
	dat->astringent = param[1];
	dat->sweet = param[2];
	dat->bitter = param[3];
	dat->sour = param[4];
}

/**
 *	@brief	�|���g�f�o�b�O�@�e�L�g�[�ȃ|���g���w�肵�����ǉ�
 */
u16 PorutoDebug_AddRndData(PORUTO_BLOCK* block,u16 num)
{
	u16	ret = 0,i;
	
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(PorutoData_IsEnable(&block->poruto[i])){
			continue;
		}
		//�����_���ȃp�����[�^������
		porudeb_CreateRndParam(&block->poruto[i],ret+1);
		if(++ret >= num){
			return ret;
		}
	}
	return ret;
}

#endif	//PM_DEBUG
