//============================================================================================
/**
 * @brief	coin.c
 * @brief	コイン操作
 * @date	2006.03.09
 * @author	tamada
 */
//============================================================================================

#include "savedata/coin.h"
#include "coin_local.h"
#include "gflib/assert.h"

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	コインデータの初期化処理
 * @param	coin		コインデータへのポインタ
 */
//---------------------------------------------------------------------------
void COIN_Init(COIN * coin)
{
	coin->value = 0;
}
//---------------------------------------------------------------------------
/**
 * @brief	コインの数をセットする
 * @param	coin		コインデータへのポインタ
 * @param	setvalue	セットする値
 */
//---------------------------------------------------------------------------
void COIN_Set(COIN * coin, u32 setvalue)
{
	GF_ASSERT(setvalue <= COIN_MAX);
	coin->value = setvalue;
}

//---------------------------------------------------------------------------
/**
 * @brief	コインの数を取得する
 * @param	coin		コインデータへのポインタ
 * @retval	int			コインの数
 */
//---------------------------------------------------------------------------
u32 COIN_GetValue(const COIN * coin)
{
	return coin->value;
}

//---------------------------------------------------------------------------
/**
 * @brief	コインを増やす
 * @param	coin		コインデータへのポインタ
 * @param	addvalue	増やす値
 * @retval	TRUE		成功した
 * @retval	FALSE		失敗した
 */
//---------------------------------------------------------------------------
BOOL COIN_Add(COIN * coin, u32 addvalue)
{
//	GF_ASSERT(addvalue > COIN_MAX);
	if (coin->value >= COIN_MAX) {
		return FALSE;
	}
	coin->value += addvalue;
	if (coin->value > COIN_MAX) {
		coin->value = COIN_MAX;
	}
	return TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	コインを増やせるかどうかをチェック
 * @param	coin		コインデータへのポインタ
 * @param	addvalue	増やす値
 * @retval	TRUE		コインを増やすのに成功した
 * @retval	FALSE		コインを増やすのに失敗した（最大値を超えた）
 */
//---------------------------------------------------------------------------
BOOL COIN_AddCheck(const COIN * coin, u32 addvalue)
{
	if (addvalue + (u32)coin->value <= COIN_MAX) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	コインを減らす
 * @param	coin		コインデータへのポインタ
 * @param	subvalue	減らす値
 * @retval	TRUE		成功した
 * @retval	FALSE		失敗した
 */
//---------------------------------------------------------------------------
BOOL COIN_Sub(COIN * coin, u32 subvalue)
{
//	GF_ASSERT(subvalue > COIN_MAX);
	if (coin->value < subvalue) {
		return FALSE;
	}
	coin->value -= subvalue;
	return TRUE;
}

