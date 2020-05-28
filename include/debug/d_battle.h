
//==============================================================================================
/**
 * @file	d_battle.h
 * @brief	戦闘用デバッグツール
 * @author	sogabe
 * @date	2006.04.14
 */
//==============================================================================================

#ifndef	__D_BATTLE_H__
#define	__D_BATTLE_H__

extern	void	DebugBattleInit(BATTLE_WORK *bw);
extern	BOOL	DebugBattleMain(BATTLE_WORK *bw);
extern	BOOL	DebugBattlePokemonReshuffle(BATTLE_WORK *bw,int client_no,int *pos);

extern	void	DebugSoftSpritePosPut(BATTLE_WORK *bw);

#endif	__D_BATTLE_H__
