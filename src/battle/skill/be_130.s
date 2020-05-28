//============================================================================
/**
 *
 *@file		be_130.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			130　固定ダメージ２０
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_130:
	//レギュレーションでリトルカップの場合は、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_REGULATION_FLAG,REGULATION_FLAG_LITTLE_CUP,Umakukimaran
	//タイプ補正計算を無視する
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//ダメージを20に
	VALUE			VAL_SET,BUF_PARA_DAMAGE,-20
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
