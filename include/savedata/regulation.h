//============================================================================================
/**
 * @file	regulation.h
 * @brief	�o�g�����M�����[�V�����f�[�^�A�N�Z�X�p�w�b�_
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================
#ifndef __REGULATION_H__
#define __REGULATION_H__

#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "system/gamedata.h"        //EOM_SIZE�Q�Ƃ̂���
#include "gflib/msg_print.h"		//STRCODE�Q�Ƃ̂���
#include "gflib/strbuf.h"			//STRBUF�Q�Ƃ̂���

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�o�g�����M�����[�V�����f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _REGULATION_DATA REGULATION_DATA;


#define REGULATION_NAME_SIZE   (11)      // ���[�����̒��� 11����22�o�C�g +EOM2byte
#define REGULATION_MAX_NUM   (1)   // �P�{�ۑ��\

typedef enum  {
  REGULATION_NAME,          //���[����
  REGULATION_POKE_NUM,      //�|�P������
  REGULATION_LEVEL,         //�|�P�����̃��x��
  REGULATION_TOTAL_LEVEL,   //�|�P�����̃��x�����v
  REGULATION_EVOLUTION,     //�i���|�P�������ǂ���
  REGULATION_HEIGHT,        //�g��   0.2 - 9.9m 
  REGULATION_HEIGHT_LIMIT,  //�g������  -1,0,1
  REGULATION_WEIGHT,       //�̏d    1-99  kg
  REGULATION_WEIGHT_LIMIT,   //�̏d����  -1,0,1
  REGULATION_BOTH_ITEM,    //��������n�j���H
  REGULATION_BOTH_MONSTER, //�����|�P�����n�j���H
  REGULATION_LEGEND,       // �`���n�L��
  REGULATION_FIXDAMAGE,    // �Œ�_���[�W�Z���K�����s
} REGULATION_PARAM_TYPE;

//----------------------------------------------------------
/**
 * @brief	�o�g�����M�����[�V�����f�[�^�^��`  fushigi_data.h�Q�Ƃ̈׊O�����J��
 */
//----------------------------------------------------------
typedef struct {
	STRCODE cupName[REGULATION_NAME_SIZE + EOM_SIZE];
	u16 totalLevel;
	u8 num;
	u8 level;
    s8 height;
    s8 weight;
    u8 evolution:1;    //  
    u8 bLegend:1;
    u8 bBothMonster:1;
    u8 bBothItem:1;
    u8 bFixDamage:1;
}  REGULATION;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e����ʐM�Ŏg�p����֐�
//----------------------------------------------------------
extern int Regulation_GetWorkSize(void);
extern int RegulationData_GetWorkSize(void);
extern REGULATION * Regulation_AllocWork(u32 heapID);
extern void Regulation_Copy(const REGULATION * from, REGULATION * to);
extern int Regulation_Cmp(const REGULATION* pCmp1,const REGULATION* pCmp2);

//----------------------------------------------------------
//	REGULATION����̂��߂̊֐�
//----------------------------------------------------------
extern void Regulation_Init(REGULATION * my);
extern void RegulationData_Init(REGULATION_DATA * my);

//���O
extern void Regulation_SetCupName(REGULATION * pReg, const STRBUF* pCupName);
extern void Regulation_GetCupName(const REGULATION* pReg,STRBUF* pReturnCupName);
extern STRBUF* Regulation_CreateCupName(const REGULATION* pReg, int heapID);

extern int Regulation_GetParam(const REGULATION* pReg, REGULATION_PARAM_TYPE type);
extern BOOL Regulation_SetParam(REGULATION * pReg, REGULATION_PARAM_TYPE type, int param);

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern REGULATION* SaveData_GetRegulation(SAVEDATA* pSave,int regNo);
extern void SaveData_SetRegulation(SAVEDATA* pSave, const REGULATION* pReg);


#endif //__REGULATION_H__
