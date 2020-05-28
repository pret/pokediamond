//============================================================================
/**
 *
 *@file		be_009.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			009　敵が使った技と同じ技を出す
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_009:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//オウム返しワークをチェックして、返せるときはその技のシーケンスへジャンプ
	OUMU_CHECK
OumuSippai:
	MESSAGE			OumuNGMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//技の起動に失敗フラグを立てる
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
