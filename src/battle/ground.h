//==============================================================================
/**
 * @file	ground.h
 * @brief	戦闘画面：地面(ポケモンが上に乗るお盆)のヘッダ
 * @author	matsuda
 * @date	2005.10.06(木)
 */
//==============================================================================
#ifndef __GROUND_H__
#define __GROUND_H__


//==============================================================================
//	定数定義
//==============================================================================
///自機側地面のX座標
#define GROUND_MINE_X		(64)
///自機側地面のY座標
#define GROUND_MINE_Y		(128 + 8)
///敵側地面のX座標
#define GROUND_ENEMY_X		(24*8)
///敵側地面のY座標
#define GROUND_ENEMY_Y		(8*11)


///地面(ポケモンが乗るお盆)のグラフィックタイプ
enum{
	GROUND_TYPE_NORMAL_MINE,		///<ノーマル地形味方側
	GROUND_TYPE_NORMAL_ENEMY,	///<ノーマル地形敵側
};


//==============================================================================
//	構造体定義
//==============================================================================
///地面(ポケモンが乗るお盆)ワーク
typedef struct{
	CATS_ACT_PTR cap;		///<ヘッダー付きアクターポインタ
	BATTLE_WORK	*bw;		///<戦闘システムワーク構造体
	u8 mine_enemy;			///<GROUND_TYPE_NORMAL_???
	u8 ground_id;			///<GROUND_ID_???
	s16 x;
	s16 y;
}GROUND_WORK;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void Ground_ResourceLoad(GROUND_WORK *ground);
extern void Ground_ActorSet(GROUND_WORK *ground);
extern void Ground_ActorDel(GROUND_WORK *ground);
extern void Ground_ResourceFree(GROUND_WORK *ground);
extern void Ground_ActorResourceSet(GROUND_WORK *ground, BATTLE_WORK *bw, 
	u16 mine_enemy, int ground_id);
extern void Ground_ActorResourceDel(GROUND_WORK *ground);
extern void Ground_EnableSet(GROUND_WORK *ground, int enable);



#endif	//__GROUND_H__

