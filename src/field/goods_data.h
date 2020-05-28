//============================================================================================
/**
 * @file	goods_data.h
 * @brief	グッズサイズ、当たり判定情報の取得
 * @author	saito
 * @date	2006.02.27
 */
//============================================================================================
#ifndef __GOODS_DATA_H__
#define __GOODS_DATA_H__

#include "common.h"

extern const u8 GOODS_GetGoodsSizeX(const int inGoodsIndex);
extern const u8 GOODS_GetGoodsSizeZ(const int inGoodsIndex);
extern const u8 *GOODS_GetGoodsHitData(const int inGoodsIndex);
extern const u8 GOODS_GetGoodsChangeStoneType(const int inGoodsIndex);
extern const u8 GOODS_GetGoodsChangeStoneCaratMin(const int inGoodsIndex);
extern const u8 GOODS_GetGoodsChangeStoneCaratMax(const int inGoodsIndex);
extern const int GOODS_GetGoodsMoney(const int inGoodsIndex);
extern const int GOODS_GetMessageNo(const int inGoodsIndex);
extern const int GOODS_GetZenkokuMode(const int inGoodsIndex);
extern const int GOODS_GetLear(const int inGoodsIndex);

#endif	//__GOODS_DATA_H__
