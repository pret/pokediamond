/**
 *	@file	b_tower_wifi.h
 *	@brief	バトルタワーwifi/通信マルチ関連ソース
 *	@author	Miyuki Iwasawa
 *	@date	06.05.23
 */

#ifndef __H_B_TOWER_WIFI_H__
#define __H_B_TOWER_WIFI_H__

#undef GLOBAL
#ifdef __B_TOWER_WIFI_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

/**
 *	@brief	通信用にアップデートするプレイヤーデータをセーブデータから作成する
 *
 *	@param	mode	0:シングル用(トレーナーロード用)
 *					1:wifi用(タワーwifi用)
 */
GLOBAL void BtlTowerData_MakeUpdatePlayerData(SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode,DPW_BT_PLAYER* dat);

#endif	//__H_B_TOWER_WIFI_H__
