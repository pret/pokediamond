/**
 *	@file	nmix_bag.c
 *	@brief	ナッツミキサー　木の実袋参照 
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#ifndef __H_NMIX_BAG_H__
#define __H_NMIX_BAG_H__

/**
 *	@brief	メインコマンド　木の実選択フロー
 */
extern int NMixMainSeq_Bag(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセスコール
 */
extern int NMixMainSeq_GameCall(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了待ち
 */
extern int NMixMainSeq_GameWait(NUTMIXER_WORK* mp,int *seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了処理
 */
extern int NMixMainSeq_GameEnd(NUTMIXER_WORK* mp,int *seq);



#endif	//__H_NMIX_BAG_H__
