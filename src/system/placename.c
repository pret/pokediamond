//============================================================================================
/**
 * @file	placename.c
 * @brief	地名データ取り扱い
 * @author	taya
 * @date	2006.05.20
 */
//============================================================================================
#include "common.h"


#include "system\placename.h"


//--------------------------------------------------------------
/**
 *	捕獲場所タイプごとの開始値
 */
//--------------------------------------------------------------
enum {
	MAP_START_NUMBER = 0,
	GAME_EVENT_START_NUMBER = 2000,
	EXT_EVENT_START_NUMBER = 3000,
};

static const u16  TypeStartNumber[] = {
	MAP_START_NUMBER,
	GAME_EVENT_START_NUMBER,
	EXT_EVENT_START_NUMBER,
};

//------------------------------------------------------------------
/**
 * 捕獲場所ナンバーから捕獲場所タイプを取得
 *
 * @param   number		捕獲場所ナンバー（ポケモンパラメータとしてセットされている値）
 *
 * @retval  PLACENAME_TYPE		捕獲場所タイプ
 */
//------------------------------------------------------------------
PLACENAME_TYPE  PlaceName_GetType( u32 number )
{
	int i;

	for(i=0; i<(PLACENAME_TYPE_MAX-1); i++)
	{
		if( number < TypeStartNumber[i+1] )
		{
			return i;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * 捕獲場所ナンバーから、各捕獲場所タイプごとのインデックス値を返す
 * ※戻り値はgmmから文字列取得する際のインデックスとして使える
 *
 * @param   number		捕獲場所ナンバー（ポケモンパラメータとしてセットされている値）
 *
 * @retval  int		捕獲場所タイプごとのインデックス
 */
//------------------------------------------------------------------
int PlaceName_GetIndex( u32 number )
{
	int type = PlaceName_GetType( number );
	return number - TypeStartNumber[type];
}


//------------------------------------------------------------------
/**
 * 捕獲場所タイプ＆インデックスから、ポケモンパラメータとしてセットするための値を作成
 *
 * @param   type		捕獲場所タイプ
 * @param   index		タイプごとのインデックス
 *
 * @retval  int			ポケモンパラメータとしてセットするための値
 */
//------------------------------------------------------------------
int PlaceName_IndexToParamNumber( PLACENAME_TYPE type, int index )
{
	GF_ASSERT(type<PLACENAME_TYPE_MAX);
	return TypeStartNumber[type] + index;
}

