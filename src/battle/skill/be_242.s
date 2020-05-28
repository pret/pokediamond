//============================================================================
/**
 *
 *@file		be_242.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			242　ひとつ前に出た技を出す。（ダブルバトルにも対応）
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_242:
	//出せる技を選択して技のシーケンスへジャンプ
	MANEKKO			Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
