//============================================================================
/**
 *
 *@file		be_041.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			041　敵の「ぼうぎょ」や、自分の「こうげき」に関係なく４０の固定ダメージを与える
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_041:
	//レギュレーションでリトルカップの場合は、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_REGULATION_FLAG,REGULATION_FLAG_LITTLE_CUP,Umakukimaran
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//ダメージを40に
	VALUE			VAL_SET,BUF_PARA_DAMAGE,-40
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
