//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_rbox_player.c
 *	@brief		右ボックスプレイヤー
 *	@author		tomoya takahashi
 *	@data		2005.10.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "include/application/imageClip/imc_drawdata_define.h"


#define __IMC_RBOX_PLAYER_H_GLOBAL
#include "include/application/imageClip/imc_rbox_player.h"


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

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスプレイヤー初期化
 *
 *	@param	rbox_player	右ボックスプレイヤー
 *	@param	rbox		右ボックス構造体
 *	@param	heap		使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Init( IMC_RBOX_PLAYER* rbox_player, const IMC_RIGHT_BOX* rbox, int heap )
{
	IMC_BG_ANM_INIT init;
	
	rbox_player->rbox = rbox;

	init.bg			= &rbox->boxDraw.bg;
	init.scrn_arc	= IMC_BG_RIGHT_SC_ANM_ARC_GET( rbox->boxDraw.bg_no );
	init.timing		= IMC_RBOX_PLAYER_BG_ANM_TIMING;
	init.heap		= heap;
	IMC_BG_AnmInit( &rbox_player->bg_anm, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスプレイヤーメイン
 *	
 *	@param	rbox_player		右ボックスプレイヤー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Main( IMC_RBOX_PLAYER* rbox_player )
{
	// BGアニメ
	IMC_BG_Anm( &rbox_player->bg_anm, IMC_RBOX_PLAYER_BG_ANM_FRAME );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスプレイヤー破棄
 *
 *	@param	rbox_player		右ボックスプレイヤー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Delete( IMC_RBOX_PLAYER* rbox_player )
{
	IMC_BG_AnmDelete( &rbox_player->bg_anm );
	memset( rbox_player, 0, sizeof(IMC_RBOX_PLAYER) );
}

