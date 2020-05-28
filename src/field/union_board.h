//===========================================================================
/**
 *
 *@file		union_board.h
 *@brief	ユニオンルーム掲示板（サブ画面）ヘッダファイル
 *@author	Akito Mori
 *@data		2006.02.04
 *
 */
//===========================================================================
#ifndef _UNION_BOARD_H_
#define _UNION_BOARD_H_


typedef struct UNION_BOARD_WORK	UNION_BOARD_WORK;


extern UNION_BOARD_WORK *UnionRoom_BoardInit( FIELDSYS_WORK *fsys );
extern void 			 UnionRoom_BoardEnd( UNION_BOARD_WORK *urw );
extern void UnionBoard_ChatDataDelete( UNION_CHAT_RINGBUF *ucr );
extern UNION_CHAT_RINGBUF *UnionBoard_ChatAllocInit( int heapID );

#endif