//============================================================================================
/**
 * @file	regulation.c
 * @brief	�o�g�����M�����[�V�����f�[�^�A�N�Z�X�p�\�[�X
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/regulation.h"
#include "regulation_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"


//============================================================================================
//============================================================================================

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
int Regulation_GetWorkSize(void)
{
	return sizeof(REGULATION);
}

//----------------------------------------------------------
/**
 * @brief	���[�N�T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int RegulationData_GetWorkSize(void)
{
	return sizeof(REGULATION_DATA);
}

//----------------------------------------------------------
/**
 * @brief	�o�g�����M�����[�V�������[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	REGULATION*	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
REGULATION* Regulation_AllocWork(u32 heapID)
{
	REGULATION* reg;
	reg = sys_AllocMemory(heapID, sizeof(REGULATION));
	Regulation_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	REGULATION�̃R�s�[
 * @param	from	�R�s�[��REGULATION�ւ̃|�C���^
 * @param	to		�R�s�[��REGULATION�ւ̃|�C���^
 */
//----------------------------------------------------------
void Regulation_Copy(const REGULATION *pFrom, REGULATION* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(REGULATION));
}

//----------------------------------------------------------
/**
 * @brief	REGULATION�̔�r
 * @param	cmp1   ��r����REGULATION�ւ̃|�C���^
 * @param	cmp2   ��r�����REGULATION�ւ̃|�C���^
 * @return  ��v���Ă�����TRUE
 */
//----------------------------------------------------------
int Regulation_Cmp(const REGULATION* pCmp1,const REGULATION* pCmp2)
{
    int i,size = sizeof(REGULATION);
    const u8* pc1 = (const u8*)pCmp1;
    const u8* pc2 = (const u8*)pCmp2;

    for(i = 0; i < size; i++){
        if(*pc1 != *pc2){
            return FALSE;
        }
        pc1++;
        pc2++;
    }
    return TRUE;
}

//============================================================================================
//
//	REGULATION����̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�o�g�����M�����[�V�����f�[�^�̏�����
 * @param	pReg		REGULATION���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void Regulation_Init(REGULATION* pReg)
{
	memset(pReg, 0, sizeof(REGULATION));
}

//----------------------------------------------------------
/**
 * @brief	�o�g�����M�����[�V�����f�[�^�̏�����
 * @param	pReg		REGULATION���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void RegulationData_Init(REGULATION_DATA* pRegData)
{
	memset(pRegData, 0, sizeof(REGULATION_DATA));
}

//----------------------------------------------------------
/**
 * @brief	�J�b�v���Z�b�g
 * @param	pReg	REGULATION���[�N�|�C���^
 * @param	pCupBuf	�J�b�v�����������o�b�t�@
 */
//----------------------------------------------------------
void Regulation_SetCupName(REGULATION* pReg, const STRBUF *pCupBuf)
{
    STRBUF_GetStringCode(pCupBuf, pReg->cupName, (REGULATION_NAME_SIZE + EOM_SIZE));
}

//----------------------------------------------------------
/**
 * @brief	�J�b�v���擾
 * @param	pReg		    REGULATION���[�N�|�C���^
 * @param	pReturnCupName	�J�b�v��������STRBUF�|�C���^
 * @return	none
 */
//----------------------------------------------------------
void Regulation_GetCupName(const REGULATION* pReg,STRBUF* pReturnCupName)
{
    STRBUF_SetStringCodeOrderLength(pReturnCupName, pReg->cupName, (REGULATION_NAME_SIZE + EOM_SIZE));
}

//----------------------------------------------------------
/**
 * @brief	�J�b�v���O�擾�iSTRBUF�𐶐��j
 * @param	pReg	���[�N�ւ̃|�C���^
 * @param	heapID	STRBUF�𐶐�����q�[�v��ID
 * @return	STRBUF	���O���i�[����STRBUF�ւ̃|�C���^
 */
//----------------------------------------------------------
STRBUF* Regulation_CreateCupName(const REGULATION* pReg, int heapID)
{
	STRBUF* tmpBuf = STRBUF_Create((REGULATION_NAME_SIZE + EOM_SIZE)*GLOBAL_MSGLEN, heapID);
	STRBUF_SetStringCode( tmpBuf, pReg->cupName );
	return tmpBuf;
}

//----------------------------------------------------------
/**
 * @brief	�p�����[�^�[���擾����
 * @param	pReg	REGULATION���[�N�|�C���^
 * @param	type	REGULATION_PARAM_TYPE enum �̂ǂꂩ
 */
//----------------------------------------------------------
int Regulation_GetParam(const REGULATION* pReg, REGULATION_PARAM_TYPE type)
{
    int ret = 0;

    switch(type){
      case REGULATION_POKE_NUM:      //�|�P������
        ret = pReg->num;
        break;
      case REGULATION_LEVEL:         //�|�P�����̃��x��
        ret = pReg->level;
        break;
      case REGULATION_TOTAL_LEVEL:   //�|�P�����̃��x�����v
        ret = pReg->totalLevel;
        break;
      case REGULATION_EVOLUTION:     //�i���O����
        ret = pReg->evolution;
        break;
      case REGULATION_HEIGHT:        //�g��
        ret = pReg->height;
        break;
      case REGULATION_HEIGHT_LIMIT:  //�g������  -1,0,1
        if(pReg->height>0){
            ret = 1;   // �ȏ�
        }
        else if(pReg->height<0){
            ret = -1;  // �ȉ�
        }
        break;
      case REGULATION_WEIGHT:       //�̏d
        ret = pReg->weight;
        break;
      case REGULATION_WEIGHT_LIMIT:   //�̏d����  -1,0,1
        if(pReg->weight>0){
            ret = 1;   // �ȏ�
        }
        else if(pReg->weight<0){
            ret = -1;  // �ȉ�
        }
        break;
      case REGULATION_BOTH_ITEM:    //��������n�j���H
        ret = pReg->bBothItem;
        break;
      case REGULATION_BOTH_MONSTER: //�����|�P�����n�j���H
        ret = pReg->bBothMonster;
        break;
      case REGULATION_LEGEND:       // �`���n�L��
        ret = pReg->bLegend;
        break;
      case REGULATION_FIXDAMAGE:       // ���ꃋ�[���i�Œ�_���[�W�����j
        ret = pReg->bFixDamage;
        break;
    }
    return ret;
}

//----------------------------------------------------------
/**
 * @brief	�p�����[�^�[����������
 * @param	pReg	REGULATION���[�N�|�C���^
 * @param	type	REGULATION_PARAM_TYPE enum �̂ǂꂩ
 * @param	param	�������ޒl
 * @return  �������������񂾂�TRUE  �s���Ȓl�̏ꍇFALSE
 */
//----------------------------------------------------------
BOOL Regulation_SetParam(REGULATION* pReg, REGULATION_PARAM_TYPE type, int param)
{
    switch(type){
      case REGULATION_POKE_NUM:      //�|�P������
        GF_ASSERT_RETURN(param <= _REG_NUM_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_NUM_MIN,FALSE);
        pReg->num = param;
        break;
      case REGULATION_LEVEL:         //�|�P�����̃��x��
        GF_ASSERT_RETURN(param <= _REG_LEVEL_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_LEVEL_MIN,FALSE);
        pReg->level = param;
        break;
      case REGULATION_TOTAL_LEVEL:   //�|�P�����̃��x�����v
        GF_ASSERT_RETURN(param <= _REG_TOTAL_LEVEL_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_TOTAL_LEVEL_MIN,FALSE);
        pReg->totalLevel = param;
        break;
      case REGULATION_EVOLUTION:     //�i���O����
        pReg->evolution = param;
        break;
      case REGULATION_HEIGHT:        //�g��
        pReg->height = param;
        break;
      case REGULATION_HEIGHT_LIMIT:  //�g������  -1,0,1
        if((param == 1) && (pReg->height < 0)){
            pReg->height = -pReg->height;
        }
        else if((param == -1) && (pReg->height > 0)){
            pReg->height = -pReg->height;
        }
        else{
            pReg->height = 0;
        }
        break;
      case REGULATION_WEIGHT:       //�̏d
        GF_ASSERT_RETURN(param <= _REG_WEIGHT_MAX, FALSE);
        GF_ASSERT_RETURN(param >= _REG_WEIGHT_MIN, FALSE);
        pReg->weight;
        break;
      case REGULATION_WEIGHT_LIMIT:   //�̏d����  -1,0,1
        if((param == 1) && (pReg->weight < 0)){
            pReg->weight = -pReg->weight;
        }
        else if((param == -1) && (pReg->weight > 0)){
            pReg->weight = -pReg->weight;
        }
        else{
            pReg->weight = 0;
        }
        break;
      case REGULATION_BOTH_ITEM:    //��������n�j���H
        pReg->bBothItem = param;
        break;
      case REGULATION_BOTH_MONSTER: //�����|�P�����n�j���H
        pReg->bBothMonster = param;
        break;
      case REGULATION_LEGEND:       // �`���n�L��
        pReg->bLegend = param;
        break;
      case REGULATION_FIXDAMAGE:       // �Œ�_���[�W�Z���K�����s
        pReg->bFixDamage = param;
        break;
    }
    return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	���M�����[�V�����f�[�^�ւ̃|�C���^�擾
 * @param	pSave    	�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @param	���{�ڂ̃��M�����[�V�����f�[�^��
 * @return	REGULATION	���[�N�ւ̃|�C���^  �����f�[�^�̏ꍇNULL
 */
//----------------------------------------------------------
REGULATION* SaveData_GetRegulation(SAVEDATA* pSave, int regNo)
{
	REGULATION_DATA* pRegData = NULL;

    GF_ASSERT_RETURN(regNo < REGULATION_MAX_NUM,NULL);
    
	pRegData = SaveData_Get(pSave, GMDATA_ID_REGULATION);
    if(Regulation_GetParam(&pRegData->regulation_buff[regNo],REGULATION_POKE_NUM)!=0){
        return &pRegData->regulation_buff[regNo];
    }
    return NULL;
}

//----------------------------------------------------------
/**
 * @brief	���M�����[�V�����f�[�^�̕ۑ�
 * @param	pSave    	�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @param	const REGULATION  ���M�����[�V�����f�[�^
 * @return	none
 */
//----------------------------------------------------------
void SaveData_SetRegulation(SAVEDATA* pSave, const REGULATION* pReg)
{
	REGULATION_DATA* pRegData = NULL;

	pRegData = SaveData_Get(pSave, GMDATA_ID_REGULATION);
    Regulation_Copy(pReg, &pRegData->regulation_buff[0]);
}

