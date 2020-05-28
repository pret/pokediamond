//============================================================================================
/**
 * @file	townmap_footmark.c
 * @brief	タウンマップ上で表示される主人公の移動状況記録
 * @author	saitou GAME FREAK inc.
 *
 * 2005.12.19	色々修正
 */
//============================================================================================
#include "common.h"

#include "townmap_footmark.h"
#include "player.h"

//-----------------------------------------------------------------------------
/**
*	タウンマップ足跡初期化
*
* @param	
* @param	
* @param	
*/
//-----------------------------------------------------------------------------
void TMFootMark_Init(TOWN_MAP_FOOTMARK *outFootMark)
{
	u8 i;
	for (i=0;i<FOOTMARK_NUM;i++){
		outFootMark->Param[i].BlockX = 0;
		outFootMark->Param[i].BlockZ = 0;
		outFootMark->Param[i].Dir = 0;
		outFootMark->Param[i].Valied = 0;
	}
	outFootMark->NowPoint = 0;
	outFootMark->NowBlockX = 0;
	outFootMark->NowBlockZ = 0;
}

//-----------------------------------------------------------------------------
/**
*	タウンマップ足跡セット
*
* @param	
* @param	
* @param	
*/
//-----------------------------------------------------------------------------
void TMFootMark_SetNoDir(TOWN_MAP_FOOTMARK *ioFootMark, int x, int z)
{
	u8 block_x,block_z;
	block_x = x / 32;
	block_z = z / 32;
	if ( (block_x != ioFootMark->NowBlockX) || (block_z != ioFootMark->NowBlockZ)){
		ioFootMark->Param[ioFootMark->NowPoint].BlockX = block_x;
		ioFootMark->Param[ioFootMark->NowPoint].BlockZ = block_z;
		ioFootMark->Param[ioFootMark->NowPoint].Dir = DIR_NOT;
		ioFootMark->Param[ioFootMark->NowPoint].Valied = 1;
		ioFootMark->NowPoint = (ioFootMark->NowPoint+1)%FOOTMARK_NUM;
	}
}
#if 0
void TMFootMark_SetNoDir(const PLAYER_STATE_PTR inPlayer, TOWN_MAP_FOOTMARK *ioFootMark)
{
	u8 block_x,block_z;
	block_x = Player_NowGPosXGet( inPlayer ) / 32;
	block_z = Player_NowGPosZGet( inPlayer ) / 32;
	if ( (block_x != ioFootMark->NowBlockX) || (block_z != ioFootMark->NowBlockZ)){
		ioFootMark->Param[ioFootMark->NowPoint].BlockX = Player_NowGPosXGet( inPlayer ) / 32;
		ioFootMark->Param[ioFootMark->NowPoint].BlockZ = Player_NowGPosZGet( inPlayer ) / 32;
		ioFootMark->Param[ioFootMark->NowPoint].Dir = DIR_NOT;
		ioFootMark->Param[ioFootMark->NowPoint].Valied = 1;
		ioFootMark->NowPoint = (ioFootMark->NowPoint+1)%FOOTMARK_NUM;
	}
}
#endif

//-----------------------------------------------------------------------------
/**
*	タウンマップ足跡更新
*
* @param	
* @param	
* @param	
*/
//-----------------------------------------------------------------------------
void TMFootMark_Update(TOWN_MAP_FOOTMARK *ioFootMark, int x, int z, int dir)
{
	u8 block_x,block_z;
	block_x = x;// / 32;
	block_z = z;// / 32;
	if ( (block_x != ioFootMark->NowBlockX) || (block_z != ioFootMark->NowBlockZ)){
		ioFootMark->Param[ioFootMark->NowPoint].BlockX = block_x;
		ioFootMark->Param[ioFootMark->NowPoint].BlockZ = block_z;
		ioFootMark->Param[ioFootMark->NowPoint].Dir = dir;
		ioFootMark->Param[ioFootMark->NowPoint].Valied = 1;

		ioFootMark->NowBlockX = block_x;
		ioFootMark->NowBlockZ = block_z;
		ioFootMark->NowPoint = (ioFootMark->NowPoint+1)%FOOTMARK_NUM;
	}
}

#if 0
void TMFootMark_UpdateByPlayer(	const PLAYER_STATE_PTR inPlayer, TOWN_MAP_FOOTMARK *ioFootMark)
{
	u8 block_x,block_z;
	block_x = Player_NowGPosXGet( inPlayer ) / 32;
	block_z = Player_NowGPosZGet( inPlayer ) / 32;
	if ( (block_x != ioFootMark->NowBlockX) || (block_z != ioFootMark->NowBlockZ)){
		ioFootMark->Param[ioFootMark->NowPoint].BlockX = block_x;
		ioFootMark->Param[ioFootMark->NowPoint].BlockZ = block_z;
		ioFootMark->Param[ioFootMark->NowPoint].Dir = Player_DirGet( inPlayer );
		ioFootMark->Param[ioFootMark->NowPoint].Valied = 1;

		ioFootMark->NowBlockX = block_x;
		ioFootMark->NowBlockZ = block_z;
		ioFootMark->NowPoint = (ioFootMark->NowPoint+1)%FOOTMARK_NUM;
	}
}
#endif

#ifdef	PM_DEBUG
//-----------------------------------------------------------------------------
/**
 * @brief	デバッグ用初期化関数
 * @param	footmark
 */
//-----------------------------------------------------------------------------
void TMFootMark_Init_Debug(TOWN_MAP_FOOTMARK * footmark)
{
	static const struct {u8 x; u8 z; u8 dir; } fm_dmy[] = {
		{ 3, 27, DIR_NOT },
		{ 3, 26, DIR_UP },
		{ 4, 26, DIR_RIGHT },
		{ 5, 26, DIR_RIGHT },
		{ 5, 25, DIR_UP },
		{ 5, 24, DIR_UP },
	};
	int i;
	TMFootMark_Init(footmark);
	for (i = 0; i < NELEMS(fm_dmy); i++) {
		TMFootMark_Update(footmark, fm_dmy[i].x, fm_dmy[i].z, fm_dmy[i].dir);
	}
}

#endif	//PM_DEBUG
