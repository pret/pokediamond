//============================================================================================
/**
 * @file	map_jump_def.h
 * @brief	マップジャンプタイプ定義
 * @date	2006.02.08
 * @author	Nozomu Saito
 */
//============================================================================================
#ifndef __MAP_JUMP_DEF_H__
#define __MAP_JUMP_DEF_H__

#define MAP_JUMP_TYPE_MAX	(7)

typedef enum{
	M_JUMP_MATOUT,		//0:室内→外
	M_JUMP_DOOR,	//1:ドア（外）→室内
	M_JUMP_ESCA,	//2:エスカレーター
	M_JUMP_STAIRS,	//3:階段
	M_JUMP_DUNIN,	//4:ダンジョン外から入る
	M_JUMP_DUNOUT,	//5:ダンジョン外に出る
	M_JUMP_MATIN,	//6:外マット→屋内
}MAP_JUMP_TYPE;

#endif //__MAP_JUMP_DEF_H__
