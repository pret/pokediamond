/**
 *@file		effect_warppoint.h
 *@brief	ワープポイント　地下移動からもらいました
 *@author	k.ohno
 *@data		2006.06.21
 *
 */
#ifndef __EFFECT_WARPPOINT_H__
#define __EFFECT_WARPPOINT_H__

#include "fieldsys.h"


//----------------------------------------------------------------------------
/**
 *@brief	地下マップフェードエフェクト
 *@param	fsys	フィールドシステムワーク
 *@param	no		上か下か
 *@param	end		終了チェックフラグ
 *@return	none
 */
//-----------------------------------------------------------------------------
extern void StartJumpPointEffect(FIELDSYS_WORK* fsys, BOOL bUp, BOOL* end);

#endif		// __EFFECT_WARPPOINT_H__

