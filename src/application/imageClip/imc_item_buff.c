//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_item_buff.c
 *	@brief		アイテム数保持バッファ
 *	@author		tomoya takahashi
 *	@data		2006.03.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "assert.h"

#define __IMC_ITEM_BUFF_H_GLOBAL
#include "include/application/imageClip/imc_item_buff.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータからアイテム保持データ作成
 *
 *	@param	cp_imc_item		アイテムセーブデータ
 *	@param	p_buff			データ格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_ITEM_BUFF_Make( const IMC_ITEM_SAVEDATA* cp_imc_item, IMC_ITEM_BUFF* p_buff )
{
	int i;
	u32 idx;
	
	// アクセサリ保持データ取得
	for( i=0; i<IMC_ACCE_MAX; i++ ){
		p_buff->Acce[ i ] = ImcSaveData_GetAcceFlag( cp_imc_item, i );
	}

	// バッグ保持データ取得
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		p_buff->Bg[ i ] = IMC_BG_RIGHT_MAX;
	}
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		idx = ImcSaveData_GetBGFlag( cp_imc_item, i );
		
		if( idx != IMC_BG_RIGHT_MAX ){	
			p_buff->Bg[ idx ] = i;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数をへらす
 *
 *	@param	p_buff	バッファデータ
 *	@param	acce_no	アクセサリナンバー
 *	@param	num		減らす値
 *
 *	@retval	TRUE	０以上になった
 *	@retval	FALSE	０以下になった
 */
//-----------------------------------------------------------------------------
BOOL IMC_ITEM_BUFF_AcceDec( IMC_ITEM_BUFF* p_buff, u32 acce_no, int num )
{
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	if( p_buff->Acce[ acce_no ] == IMC_ACCE_MAX ){
		return FALSE;
	}

	if( (p_buff->Acce[ acce_no ] - num) >= 0 ){
		p_buff->Acce[ acce_no ] -= num;
		return TRUE;
	}

	p_buff->Acce[ acce_no ] = 0;
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ取得数　を返す
 *
 *	@param	p_buff		バッファ
 *	@param	acce_no		アクセサリナンバー
 *
 *	@return	アクセサリ取得数
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_AcceGetNum( const IMC_ITEM_BUFF* p_buff, u32 acce_no )
{
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	return p_buff->Acce[ acce_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	順番から対応するBGNoを取得する
 *
 *	@param	p_buff	バッファ
 *	@param	turn	順番
 *
 *	@return	BGナンバー
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_TurnBgNoGet( const IMC_ITEM_BUFF* p_buff, u32 turn )
{
	return p_buff->Bg[ turn ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGNOから取得した順番を求める
 *
 *	@param	p_buff		バッファ
 *	@param	bgno		BGNo
 *
 *	@return	見つけた順番		IMC_BG_RIGHT_MAX のときみつけていない
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_BgNoTurnGet( const IMC_ITEM_BUFF* p_buff, u32 bgno )
{
	int i;

	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		if( p_buff->Bg[ i ] == bgno ){
			return i;
		}
	}

	return i;
}

