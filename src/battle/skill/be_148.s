//============================================================================
/**
 *
 *@file		be_148.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			148　２ターン後に敵を攻撃する
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_148:
	MIRAIYOCHI	Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	//命中率がはいっているので、必ず当たるようにフラグを立てる
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_NONE|SERVER_STATUS_FLAG_OTHER_HIT_CALC|SERVER_STATUS_FLAG_KIE_HIT
	SEQ_END

Umakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	SEQ_END
