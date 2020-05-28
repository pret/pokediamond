//============================================================================================
/**
 * @file	goods_data.c
 * @brief	グッズサイズ、当たり判定情報の取得
 * @author	saito
 * @date	2006.02.27
 */
//============================================================================================
#include "goods_data.h"

#include "msgdata/msg_uwstatus.h"

typedef struct GOOD_SIZZE_INFO_tag
{
	u8 SizeX;
	u8 SizeZ;
	u8 HitData[9];
    u8 shopData[3];
    int money;
    int messageNo;
    u8 zenkokuFlg;
    u8 learFlg;
}GOODS_SIZE_INFO;

#include "../fielddata/base_goods/goods_size_info.dat"

//------------------------------------------------------------------
/**
 * @brief	グッズ横幅取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	u8					グッズの横幅
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsSizeX(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].SizeX;
}

//------------------------------------------------------------------
/**
 * @brief	グッズ縦幅取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	u8					グッズの縦幅
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsSizeZ(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].SizeZ;
}

//------------------------------------------------------------------
/**
 * @brief	グッズ当たりデータ取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	u8*					グッズの当たりデータの配列先頭アドレス
 */
//------------------------------------------------------------------
const u8 *GOODS_GetGoodsHitData(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].HitData;
}

//------------------------------------------------------------------
/**
 * @brief	SHOPでのグッズ交換種類取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneType(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでのグッズ交換最小レート取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneCaratMin(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOPでのグッズ交換最大レート取得
 * @param	inGoodsIndex		グッズナンバー
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneCaratMax(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[2];
}
//------------------------------------------------------------------
/**
 * @brief	地上SHOPでの売る場合の価格
 * @param	inGoodsIndex		グッズナンバー
 * @return	money
 */
//------------------------------------------------------------------
const int GOODS_GetGoodsMoney(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].money;
}

//------------------------------------------------------------------
/**
 * @brief	話しかけたときのgmmMsgNo
 * @param	inGoodsIndex		グッズナンバー
 * @return	rank
 */
//------------------------------------------------------------------
const int GOODS_GetMessageNo(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].messageNo;
}

//------------------------------------------------------------------
/**
 * @brief	全国モードになるまで売ってはいけないグッズかどうか
 * @param	inGoodsIndex		グッズナンバー
 * @return	TRUEは売れない
 */
//------------------------------------------------------------------
const int GOODS_GetZenkokuMode(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].zenkokuFlg;
}

//------------------------------------------------------------------
/**
 * @brief	レアなので交換してはいけないグッズかどうか
 * @param	inGoodsIndex		グッズナンバー
 * @return	TRUEは交換できない
 */
//------------------------------------------------------------------
const int GOODS_GetLear(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].learFlg;
}

