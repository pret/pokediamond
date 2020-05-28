//==============================================================================
/**
 * @file	wpcb_struct.h
 * @brief	基本構造体 wpcb_xxx.c しか、includeしてはいけない
 * @author	goto
 * @date	2006.02.12(日)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef __WPCB_STRUCT_H__
#define __WPCB_STRUCT_H__

#include "we_sys.h"

// -----------------------------------------
//
//	□ モード列挙
//
// -----------------------------------------
enum ECB_OPERATOR_MODE {
	
	ECB_MODE_PRI	= 0,	///< 優先度
	ECB_MODE_TARGET,		///< 対象
	ECB_MODE_POS,			///< 座標
	ECB_MODE_AXIS,			///< 軸方向
	ECB_MODE_FIELD,			///< フィールド
	ECB_MODE_CAMERA,		///< カメラ
	
	ECB_MODE_MAX,
	ECB_MODE_NUM = ECB_MODE_MAX,

};


//------------------------------------------
/**
 *
 * @brief	operator構造体
 *
 */
//------------------------------------------
typedef struct {
	
	WE_SYS_PTR	wsp;				///< we_sys
	PTC_PTR		ptc;				///< ptc
	s8	reverce_flag;				///< 反転フラグ
	int mode[ ECB_MODE_NUM ];		///< mode
	int s_client;					///< 開始クライアント
	int e_client;					///< 終了クライアント
	
	VecFx32		pos;				///< 実際の座標
	
} ECB_OPERATOR_DATA;

#endif

