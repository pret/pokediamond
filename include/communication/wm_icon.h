//=============================================================================
/**
 * @file	comm_sharing_system.h
 * @brief	データ共有を行う場合の通信システム
 * @author	Katsumi Ohno
 * @date    2005.07.08
 */
//=============================================================================

#ifndef _WM_ICON_H_
#define _WM_ICON_H_


#include "gflib/tcb.h" //TCB_PTRのため

// 通信アイコンパレットデータが転送される位置
#define WM_ICON_PALETTE_NO	( 14 )

// 通信アイコンキャラデータを転送するVRAMの位置
// 通信アイコンキャラデータはﾒｲﾝOBJVRAMの一番最後に
// １６キャラ転送されます。

//OBJ16Kモードの時
#define WM_ICON_CHAR_OFFSET16  ( (512-16)*32 )	
//OBJ32Kモードの時
#define WM_ICON_CHAR_OFFSET32  ( (1024-16)*32 )	
//OBJ64Kモードの時
#define WM_ICON_CHAR_OFFSET64 ( (2048-16)*32 )	
//OBJ128Kモードの時
#define WM_ICON_CHAR_OFFSET128 ( (4096-16)*32 )	
//OBJ80Kモードの時
#define WM_ICON_CHAR_OFFSET80 ( (2560-16)*32 )	

// -----------------------------------------------
// 管理用構造体定義
// -----------------------------------------------

typedef struct{
	u16 pat;
	u16 wait;
}VOamAnm;

typedef struct _VINTR_WIRELESS_ICON		VINTR_WIRELESS_ICON;




extern VINTR_WIRELESS_ICON *AddWirelessIconOAM(u32 objVRAM, u32 HeapId, int x, int y, BOOL bWifi, const VOamAnm *tbl[]);
extern void WirelessIconEnd(VINTR_WIRELESS_ICON *vwi);
extern void WirelessIconAnimeChange(VINTR_WIRELESS_ICON *vwi, int anime);
extern void WirelessIconHoldLCD( VINTR_WIRELESS_ICON *vwi, BOOL bTop, u32 heapID );
extern void WirelessIconDefaultLCD( VINTR_WIRELESS_ICON* vwi );

extern void WirelessIconEasyUnion(void);
extern void WirelessIconEasy(void);
extern void WirelessIconEasyXY(int x,int y, BOOL bWifi);
extern void WirelessIconEasyEnd(void);
extern void WirelessIconEasy_SetLevel(int level);
extern void WirelessIconEasy_HoldLCD( BOOL bTop, u32 heapID );
extern void WirelessIconEasy_DefaultLCD( void );

#endif //_WM_ICON_H_
