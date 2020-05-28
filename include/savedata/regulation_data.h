//============================================================================================
/**
 * @file	regulation.h
 * @brief	バトルレギュレーションデータアクセス用ヘッダ
 * @author	k.ohno
 * @date	2006.5.24
 */
//============================================================================================
#ifndef __REGULATION_DATA_H__
#define __REGULATION_DATA_H__

#include "regulation.h"

// * @brief	レギュレーションデータへのポインタ取得
extern const REGULATION* Data_GetRegulation(SAVEDATA* pSave, int regNo);
// * @brief	レギュレーションデータの名前取得
extern void Data_GetRegulationName(SAVEDATA* pSave, int regNo, STRBUF* pStrBuff, int HeapID);


#endif //__REGULATION_DATA_H__
