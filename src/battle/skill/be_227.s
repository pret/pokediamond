//============================================================================
/**
 *
 *@file		be_227.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			227　後攻のとき敵から最後に受けたダメージを1.5倍で返す。そのターン攻撃を受けていないと失敗。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_227:
	METALMIRROR		Umakukimaran
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
