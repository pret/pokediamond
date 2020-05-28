//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nutmix_comm_pack.h
 *	@brief		通信PACKAGEシステム
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NUTMIX_COMM_PACK_H__
#define __NUTMIX_COMM_PACK_H__

#include "communication/communication.h"

#undef GLOBAL
#ifdef	__NUTMIX_COMM_PACK_H_GLOBAL
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
//	通信パックフラグ
//=====================================
#define NUTMIX_COMM_PACK_ONE	( 0 )	// 一人用
#define NUTMIX_COMM_PACK_COMM	( 1 )	// 通信

//-------------------------------------
//	ダミーコールバックワーク数
//=====================================
#define NUTMIX_COMM_PACK_DUMMY_WORK_NUM	( 8 )

//-------------------------------------
//	ダミーコールバック　システムTCB　
//	VWAITタスク優先順位
//=====================================
//出来るだけ、VWAITの一番最後にしたい
#define NUTMIX_COMM_PACK_DUMMY_TCB_PRI	( 5000 )

//-------------------------------------
//	ダミーコールバックのときの
//	接続ID（ダミー）
//=====================================
#define NUTMIX_COMM_PACK_DUMMY_NETID	( COMM_PARENT_ID )




//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
// パックシステムワーク
typedef struct _NUTMIX_COMMPACK_WORK NUTMIX_COMMPACK_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL NUTMIX_COMMPACK_WORK* NMIX_CommPack_CommandInitialize( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int comm_flg, int heapID );
GLOBAL BOOL NMIX_CommPack_CommSendData( int command, const void* data, int size, NUTMIX_COMMPACK_WORK* p_sys );
GLOBAL void NMIX_CommPack_CommDelete( NUTMIX_COMMPACK_WORK* p_sys );

GLOBAL int NMIX_CommPack_CommGetCurrentID( NUTMIX_COMMPACK_WORK* p_sys );
GLOBAL BOOL NMIX_CommPack_CommIsConnect( NUTMIX_COMMPACK_WORK* p_sys, u16 netID );


#undef	GLOBAL
#endif		// __NUTMIX_COMM_PACK_H__

