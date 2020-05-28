//============================================================================================
/**
 * @file	ug_treasureshopdata.c
 * @brief	宝屋の交換対応データ
 * @author	k.ohno
 * @date	2006.3.9
 */
//============================================================================================
#include "ug_trshopdata.h"

typedef struct UG_TREASURESHOPDATA_tag
{
    u8 shopData[3];
}TREASURE_SHOP_INFO;

#include "../../fielddata/underground/treasure_info.dat"

//------------------------------------------------------------------
/**
 * @brief	SHOPでの宝交換種類取得
 * @param	treasureType		罠種類
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneType(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでの宝交換最小レート取得
 * @param	treasureType		罠種類
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneCaratMin(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでの宝交換最大レート取得
 * @param	treasureType		罠種類
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneCaratMax(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[2];
}
