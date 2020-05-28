//============================================================================================
/**
 * @file	goods_data.c
 * @brief	�O�b�Y�T�C�Y�A�����蔻����̎擾
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
 * @brief	�O�b�Y�����擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	u8					�O�b�Y�̉���
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsSizeX(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].SizeX;
}

//------------------------------------------------------------------
/**
 * @brief	�O�b�Y�c���擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	u8					�O�b�Y�̏c��
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsSizeZ(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].SizeZ;
}

//------------------------------------------------------------------
/**
 * @brief	�O�b�Y������f�[�^�擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	u8*					�O�b�Y�̓�����f�[�^�̔z��擪�A�h���X
 */
//------------------------------------------------------------------
const u8 *GOODS_GetGoodsHitData(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].HitData;
}

//------------------------------------------------------------------
/**
 * @brief	SHOP�ł̃O�b�Y������ގ擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	StoneType_e
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneType(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[0];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł̃O�b�Y�����ŏ����[�g�擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneCaratMin(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[1];
}
//------------------------------------------------------------------
/**
 * @brief	SHOP�ł̃O�b�Y�����ő僌�[�g�擾
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	carat 1-99
 */
//------------------------------------------------------------------
const u8 GOODS_GetGoodsChangeStoneCaratMax(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].shopData[2];
}
//------------------------------------------------------------------
/**
 * @brief	�n��SHOP�ł̔���ꍇ�̉��i
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	money
 */
//------------------------------------------------------------------
const int GOODS_GetGoodsMoney(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].money;
}

//------------------------------------------------------------------
/**
 * @brief	�b���������Ƃ���gmmMsgNo
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	rank
 */
//------------------------------------------------------------------
const int GOODS_GetMessageNo(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].messageNo;
}

//------------------------------------------------------------------
/**
 * @brief	�S�����[�h�ɂȂ�܂Ŕ����Ă͂����Ȃ��O�b�Y���ǂ���
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	TRUE�͔���Ȃ�
 */
//------------------------------------------------------------------
const int GOODS_GetZenkokuMode(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].zenkokuFlg;
}

//------------------------------------------------------------------
/**
 * @brief	���A�Ȃ̂Ō������Ă͂����Ȃ��O�b�Y���ǂ���
 * @param	inGoodsIndex		�O�b�Y�i���o�[
 * @return	TRUE�͌����ł��Ȃ�
 */
//------------------------------------------------------------------
const int GOODS_GetLear(const int inGoodsIndex)
{
	return GoodsSizeInfo[inGoodsIndex].learFlg;
}

