//============================================================================================
/**
 * @file	sway_grass_hist_def.h
 * @brief	揺れ草エンカウント履歴
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================
#ifndef _SWAY_GRASS_HIST_DEF_H_
#define _SWAY_GRASS_HIST_DEF_H_

typedef struct SWAY_GRASS_REC_tag{
	u16 MonsNo;
	u16 Chain;
}SWAY_GRASS_REC;

typedef struct SWAY_GRASS_HIST_tag{
	SWAY_GRASS_REC SwayGrassRec[3];
}SWAY_GRASS_HIST;

#endif //_SWAY_GRASS_HIST_DEF_H_
