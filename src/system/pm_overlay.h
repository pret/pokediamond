//==============================================================================
/**
 * @file	pm_overlay.h
 * @brief	オーバーレイ制御のヘッダ
 * @author	matsuda
 * @date	2005.06.20(月)
 */
//==============================================================================
#ifndef __PM_OVERLAY_H__
#define __PM_OVERLAY_H__


//==============================================================================
//	定数定義
//==============================================================================

/*------------------------------------
同期関数と非同期関数の動作の違いは非同期関数は別スレッドで読み込みを行うという点です。
この挙動の違いから、割り込み禁止状態や、使用するスタックが異なるといった差があります。
---------------------------------------*/

///オーバーレイ実行時のロードタイプ
enum{
	OVERLAY_LOAD_SYNCHRONIZE = 0,	///<全てを同期的に実行
	OVERLAY_LOAD_SYNCHRONIZE_2,		///<部分的に手作業で実行 (同期的)
	OVERLAY_LOAD_NOT_SYNCHRONIZE,	///<全てを手作業で実行 (非同期的)
};

///オーバーレイの展開メモリエリア
enum{
	OVERLAY_AREA_MAIN = 0,			///<メインメモリ
	OVERLAY_AREA_ITCM,				///<命令TCM
	OVERLAY_AREA_DTCM,				///<データTCM
};


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void Overlay_SystemWorkInit(void);
extern void Overlay_Init(void);
extern void Overlay_UnloadID(const FSOverlayID id);
extern void Overlay_UnloadMain(void);
extern void Overlay_UnloadItcm(void);
extern void Overlay_UnloadDtcm(void);
extern void Overlay_UnloadSameArea(const FSOverlayID id);
extern void Overlay_UnloadAll(void);
extern int Overlay_MemoryAreaGet(const FSOverlayID id);
extern BOOL Overlay_Load(const FSOverlayID id, int load_type);
extern BOOL Overlay_Call(const FSOverlayID id, int load_type, void(*func)(void *), void * work);



#endif	//__PM_OVERLAY_H__


