//============================================================================================
/**
 * @file	ug_trapshopdata.c
 * @brief	罠屋の交換対応データ
 * @author	k.ohno
 * @date	2006.3.9
 */
//============================================================================================
#include "ug_trapshopdata.h"

typedef struct UG_TRAPSHOPDATA_tag
{
    u8 shopData[3];
}TRAP_SHOP_INFO;

#include "../../fielddata/underground/trap_info.dat"

//------------------------------------------------------------------
/**
 * @brief	SHOPでの罠交換種類取得
 * @param	trapType		罠種類
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneType(const int trapType)
{
	return TrapShopInfo[trapType].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでの罠交換最小レート取得
 * @param	trapType		罠種類
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneCaratMin(const int trapType)
{
	return TrapShopInfo[trapType].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでの罠交換最大レート取得
 * @param	trapType		罠種類
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneCaratMax(const int trapType)
{
	return TrapShopInfo[trapType].shopData[2];
}
