//============================================================================================
/**
 * @file	regulation_local.h
 * @brief	�o�g�����M�����[�V�����w�b�_�[(���̃f�B���N�g���݂̂ł̂ݎQ�Ɖ�)
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================

#ifndef __REGULATION_LOCAL_H__
#define __REGULATION_LOCAL_H__

//============================================================================================

#include "savedata/regulation.h"


// �ő吔�̃��M�����[�V�����m��
struct _REGULATION_DATA {
  REGULATION regulation_buff[REGULATION_MAX_NUM];
};

//----------------------------------------------------------
/**
 * @brief	�e�f�[�^�̋����͈�
 */
//----------------------------------------------------------
#define _REG_NUM_MAX   (6)    // �Q���l���ő�
#define _REG_NUM_MIN   (1)    // �Q���l���ŏ�
#define _REG_LEVEL_MAX   (100)    // level�ő�
#define _REG_LEVEL_MIN   (1)    // level�ŏ�
#define _REG_TOTAL_LEVEL_MAX   (_REG_NUM_MAX*_REG_LEVEL_MAX)    // totallevel�ő�
#define _REG_TOTAL_LEVEL_MIN   (_REG_NUM_MIN*_REG_LEVEL_MIN)    // totallevel�ŏ�
#define _REG_WEIGHT_MAX   (99)    // weight�ő�
#define _REG_WEIGHT_MIN   (-99)    // weight�ŏ�


//============================================================================================

#endif //__REGULATION_LOCAL_H__

