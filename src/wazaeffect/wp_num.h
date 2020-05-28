//==============================================================================
/**
 * @file	wp_num.h
 * @brief	技エフェクトパーティクルデータテーブルのデータ番号定義
 * @author	matsuda
 * @date	2005.07.22(金)
 */
//==============================================================================
#ifndef __WP_NUM_H__
#define __WP_NUM_H__


//==============================================================================
//	エミッタ生成時のコールバック関数のポインタテーブルの定義　※EmitterCallbackFuncの並びに合わせる
//==============================================================================
#define EMTFUNC_START			(0)

#define EMTFUNC_DUMMY					(0 + EMTFUNC_START)
#define EMTFUNC_CAMERA_REVERSE_ATTACK	(1 + EMTFUNC_DUMMY)
#define EMTFUNC_CAMERA_REVERSE_DEFENCE	(1 + EMTFUNC_CAMERA_REVERSE_ATTACK)
#define EMTFUNC_ATTACK_POS				(1 + EMTFUNC_CAMERA_REVERSE_DEFENCE)
#define EMTFUNC_DEFENCE_POS				(1 + EMTFUNC_ATTACK_POS)
#define EMTFUNC_AXIS_ATTACK				(1 + EMTFUNC_DEFENCE_POS)
#define EMTFUNC_AXIS_DEFENCE			(1 + EMTFUNC_AXIS_ATTACK)

#define EMTFUNC_AXIS_DEFAULT_CNV		(1 + EMTFUNC_AXIS_DEFENCE)
#define EMTFUNC_AXIS_CENTER_CNV			(1 + EMTFUNC_AXIS_DEFAULT_CNV)
#define EMTFUNC_AXIS_TP_CNV				(1 + EMTFUNC_AXIS_CENTER_CNV)
#define EMTFUNC_AXIS_PP_CNV				(1 + EMTFUNC_AXIS_TP_CNV)
#define EMTFUNC_AXIS_SET_CNV			(1 + EMTFUNC_AXIS_PP_CNV)

#define EMTFUNC_AXIS_DEFAULT_MAG		(1 + EMTFUNC_AXIS_SET_CNV)
#define EMTFUNC_AXIS_CENTER_MAG			(1 + EMTFUNC_AXIS_DEFAULT_MAG)
#define EMTFUNC_AXIS_TP_MAG				(1 + EMTFUNC_AXIS_CENTER_MAG)
#define EMTFUNC_AXIS_PP_MAG				(1 + EMTFUNC_AXIS_TP_MAG)
#define EMTFUNC_AXIS_SET_MAG			(1 + EMTFUNC_AXIS_PP_MAG)

#define EMTFUNC_FIELD_OPERATOR			(1 + EMTFUNC_AXIS_SET_MAG)			///< operator関数
#define EMTFUNC_SEP_POS					(1 + EMTFUNC_FIELD_OPERATOR)		///< Sep用 の 座標
#define EMTFUNC_AT_SIDE					(1 + EMTFUNC_SEP_POS)				///< 2対選択用
#define EMTFUNC_DF_SIDE					(1 + EMTFUNC_AT_SIDE)				///< 2対選択用
#define EMTFUNC_ATTACK_POS_CR			(1 + EMTFUNC_DF_SIDE)				///< カメラ反転してるとき

#define EMTFUNC_DEBUG_START				(1 + EMTFUNC_DF_SIDE)
#define EMTFUNC_DEBUG					(EMTFUNC_DEBUG_START)

#endif	//__WP_NUM_H__


