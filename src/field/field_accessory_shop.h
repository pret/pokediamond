//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_accessory_shop.h
 *	@brief		アクセサリー交換所
 *	@author		tomoya takahashi
 *	@data		2006.06.06
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_ACCESSORY_SHOP_H__
#define __FIELD_ACCESSORY_SHOP_H__

#include "include/savedata/savedata_def.h"
#include "include/gflib/bg_system.h"


#undef GLOBAL
#ifdef	__FIELD_ACCESSORY_SHOP_H_GLOBAL
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
//-------------------------------------
//	accessory交換所
//=====================================
typedef struct _FIELD_ACCE_SHOP FIELD_ACCE_SHOP;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

GLOBAL FIELD_ACCE_SHOP* FIELD_AcceShop_Alloc( u32 heapID, SAVEDATA* p_save, GF_BGL_INI* p_bgl );
GLOBAL void FIELD_AcceShop_Free( FIELD_ACCE_SHOP* p_acce_shop );
GLOBAL BOOL FIELD_AcceShop_Main( FIELD_ACCE_SHOP* p_acce_shop );


#undef	GLOBAL
#endif		// __FIELD_ACCESSORY_SHOP_H__

