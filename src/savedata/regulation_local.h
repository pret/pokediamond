//============================================================================================
/**
 * @file	regulation_local.h
 * @brief	バトルレギュレーションヘッダー(このディレクトリのみでのみ参照可)
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================

#ifndef __REGULATION_LOCAL_H__
#define __REGULATION_LOCAL_H__

//============================================================================================

#include "savedata/regulation.h"


// 最大数のレギュレーション確保
struct _REGULATION_DATA {
  REGULATION regulation_buff[REGULATION_MAX_NUM];
};

//----------------------------------------------------------
/**
 * @brief	各データの許す範囲
 */
//----------------------------------------------------------
#define _REG_NUM_MAX   (6)    // 参加人数最大
#define _REG_NUM_MIN   (1)    // 参加人数最小
#define _REG_LEVEL_MAX   (100)    // level最大
#define _REG_LEVEL_MIN   (1)    // level最小
#define _REG_TOTAL_LEVEL_MAX   (_REG_NUM_MAX*_REG_LEVEL_MAX)    // totallevel最大
#define _REG_TOTAL_LEVEL_MIN   (_REG_NUM_MIN*_REG_LEVEL_MIN)    // totallevel最小
#define _REG_WEIGHT_MAX   (99)    // weight最大
#define _REG_WEIGHT_MIN   (-99)    // weight最小


//============================================================================================

#endif //__REGULATION_LOCAL_H__

