/**
 *	@file	nmix_bag.c
 *	@brief	ナッツミキサー　木の実袋参照 
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#ifndef __H_NMIX_BAG_H__
#define __H_NMIX_BAG_H__

#undef GLOBAL
#ifdef	__H_NMIX_BAG_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

/**
 *	@brief	メインコマンド　木の実選択フロー
 */
GLOBAL int NMixMainSeq_Bag(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセスコール
 */
GLOBAL int NMixMainSeq_GameCall(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了待ち
 */
GLOBAL int NMixMainSeq_GameWait(NUTMIXER_WORK* mp,int *seq);

/**
 *	@brief	メインコマンド　ゲームメインプロセス終了処理
 */
GLOBAL int NMixMainSeq_GameEnd(NUTMIXER_WORK* mp,int *seq);




#undef	GLOBAL
#endif	//__H_NMIX_BAG_H__
