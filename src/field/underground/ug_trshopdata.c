//============================================================================================
/**
 * @file	ug_treasureshopdata.c
 * @brief	�󉮂̌����Ή��f�[�^
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
 * @brief	SHOP�ł̕������ގ擾
 * @param	treasureType		㩎��
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneType(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł̕�����ŏ����[�g�擾
 * @param	treasureType		㩎��
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneCaratMin(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł̕�����ő僌�[�g�擾
 * @param	treasureType		㩎��
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrShopGetChangeStoneCaratMax(const int treasureType)
{
	return TreasureShopInfo[treasureType].shopData[2];
}
