//============================================================================================
/**
 * @file	regulation.h
 * @brief	�o�g�����M�����[�V�����f�[�^�A�N�Z�X�p�w�b�_
 * @author	k.ohno
 * @date	2006.5.24
 */
//============================================================================================
#ifndef __REGULATION_DATA_H__
#define __REGULATION_DATA_H__

#include "regulation.h"

// * @brief	���M�����[�V�����f�[�^�ւ̃|�C���^�擾
extern const REGULATION* Data_GetRegulation(SAVEDATA* pSave, int regNo);
// * @brief	���M�����[�V�����f�[�^�̖��O�擾
extern void Data_GetRegulationName(SAVEDATA* pSave, int regNo, STRBUF* pStrBuff, int HeapID);


#endif //__REGULATION_DATA_H__
