//============================================================================
/**
 *
 *@file		be_232.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			232　ポケモン、トレーナー（受けたポケモンに対して）道具が使用出来なくなる。効果時間：５ターンの間
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_232:
	//みがわりがいる場合はうまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SHUTOUT|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
