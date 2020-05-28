//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		comm_command_nutmixer_func.h
 *	@brief		通信コールバック関数
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 * 通信コールバック関数テーブルは、通信オーバーレイに配置しますが、
 * コールバック関数は、ミキサーのオーバレイ領域に配置すればよいので、
 * こうします。
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __COMM_COMMAND_NUTMIXER_FUNC_H__
#define __COMM_COMMAND_NUTMIXER_FUNC_H__

#include "nmix_game.h"

#undef GLOBAL
#ifdef	__COMM_COMMAND_NUTMIXER_FUNC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



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

// 通信初期化関数
extern void CommCommandNutMixerInitialize( NMIX_GAMEWORK* pWork, MYSTATUS* p_mystate );
extern void CommCommandNutMixerDest( NMIX_GAMEWORK* pWork );

	
// 共通サイズ取得関数
extern int CommNutMixerGetZeroSize( void );
extern int CommNutMixerGetOneSize( void );

//-----------------------------------------------------------------------------
/**
 *
 *		ゲーム用コマンドコールバック関数
 *
 */
//-----------------------------------------------------------------------------
// 同期用
extern void CommNutMixerGameSysStart( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameEnd( int netID, int size, void* pBuff, void* pWork );

// データ受信用
extern void CommNutMixerGameBeforeDataKo( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameBeforeData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameResultData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerPorutoData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameNextDataKo( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameNextData( int netID, int size, void* pBuff, void* pWork );

// サイズ取得関数
extern int CommNutMixerGetGameBeforeKoSize( void );
extern int CommNutMixerGetGameBeforeSize( void );
extern int CommNutMixerGetGameSize( void );
extern int CommNutMixerGetGameResultSize( void );



//-----------------------------------------------------------------------------
/**
 *
 *		通信システム関数
 *
 */
//-----------------------------------------------------------------------------



#undef	GLOBAL
#endif		// __COMM_COMMAND_NUTMIXER_FUNC_H__

