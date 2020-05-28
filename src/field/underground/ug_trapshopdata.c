//============================================================================================
/**
 * @file	ug_trapshopdata.c
 * @brief	㩉��̌����Ή��f�[�^
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
 * @brief	SHOP�ł�㩌�����ގ擾
 * @param	trapType		㩎��
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneType(const int trapType)
{
	return TrapShopInfo[trapType].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł�㩌����ŏ����[�g�擾
 * @param	trapType		㩎��
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneCaratMin(const int trapType)
{
	return TrapShopInfo[trapType].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł�㩌����ő僌�[�g�擾
 * @param	trapType		㩎��
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 TrapShopGetChangeStoneCaratMax(const int trapType)
{
	return TrapShopInfo[trapType].shopData[2];
}
