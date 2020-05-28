
//============================================================================================
/**
 * @file	tr_ai.h
 * @bfief	トレーナーAIプログラム
 * @author	HisashiSogabe
 * @date	06.04.26
 */
//============================================================================================

#ifndef __TR_AI_H_
#define __TR_AI_H_

#define	WAZA_AI_CALC_CONTINUE	(0xff)		//AI計算の途中

extern	void	WazaAIInit(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit);
extern	void	WazaAIInit2(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 point_bit);
extern	u8		WazaAIMain(BATTLE_WORK *bw,u8 client_no);
extern	void	WazaNoStockClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);
extern	void	TokusyuNoSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u8 speabino);
extern	void	TokusyuNoClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);
extern	void	SoubiItemSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no,u16 item_no);
extern	void	SoubiItemClear(BATTLE_WORK *bw,SERVER_PARAM *sp,u8 client_no);

extern	int		ClientAICommandSelectAI(BATTLE_WORK *bw,int client_no);
extern	int		ClientAIPokeSelectAI(BATTLE_WORK *bw,int client_no);
extern	int		ClientAIReshuffleSelMonsNoGet(BATTLE_WORK *bw,int client_no);

#endif __TR_AI_H_
