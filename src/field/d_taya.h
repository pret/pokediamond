//============================================================================================
/**
 * @file	d_taya.h
 * @bfief	田谷 デバッグメニュー
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _D_TAYA_H_
#define _D_TAYA_H_

#include "field_common.h"


typedef struct {
	u16  key;			///< 再生キーデータ（０で先頭に戻る）
	u16  frames;		///< 次のキー再生までのウェイトフレーム数
	u16  repeat;		///< 今のシーケンスを繰り返す数
}DEBUG_KEYPLAY_DATA;

#define DEBUG_KEYPLAY_END	(0x8000)	/// キーデータにこの値が来たら先頭に戻る

extern void DebugTayaMenuInit( void* fsys );


extern void DebugKeyPlay_Start( const DEBUG_KEYPLAY_DATA* tbl );
extern void DebugKeyPlay_Stop( void );
extern BOOL DebugKeyPlay_IsPlaying( void );


extern void DebugKeyPlay_Main( void );


#endif
