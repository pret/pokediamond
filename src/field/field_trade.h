//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade.h
 *	@brief		ゲーム内交換
 *	@author		tomoya takahashi
 *	@data		2006.05.15
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_TRADE_H__
#define __FIELD_TRADE_H__

//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_
#include "include/demo/demo_trade.h"
#endif // __ASM_NO_DEF_

#undef GLOBAL
#ifdef	__FIELD_TRADE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	交換データナンバー
//=====================================
#define	FLD_TRADE_KEESHI	(0)
#define	FLD_TRADE_PERAPPU	(1)
#define	FLD_TRADE_GHOST		(2)
#define	FLD_TRADE_KOIKING	(3)
#define	FLD_TRADE_NUM		(4)

//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
typedef struct _FLD_TRADE_WORK FLD_TRADE_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *
 *		説明
 *			FLD_TRADE_WORK*  をアロックしてきたらもう
 *			下の関数でデータを取得できます。
 *	GLOBAL u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work );
 * 	GLOBAL u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work );
 *	GLOBAL u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work );
 *
 *			交換するポケモンが決まったら
 *			EventCmd_FldTradeをコールしてください。(field_trade_cmd.h)
 *			
 *			交換が終了したら
 *			FLD_TRADE_WORK*を破棄してください
 *
 */
//-----------------------------------------------------------------------------

GLOBAL FLD_TRADE_WORK* FLD_TradeAlloc( u32 heapID, u32 trade_no );
GLOBAL void FLD_TradeDelete( FLD_TRADE_WORK* p_work ); 

// 交換データ取得関係
GLOBAL u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work );	// 交換されるポケモンナンバー
GLOBAL u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work );	// 交換に必要なポケモンナンバー
GLOBAL u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work );	// 親の性別


// 交換の実行
GLOBAL void FLD_Trade( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos );
// デモデータ作成
GLOBAL void FLD_TradeDemoDataMake( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos, DEMO_TRADE_PARAM* p_demo, POKEMON_PARAM* sendPoke, POKEMON_PARAM* recvPoke );

#endif	__ASM_NO_DEF_

#undef	GLOBAL
#endif		// __FIELD_TRADE_H__

