//============================================================================
/**
 *
 *@file		be_180.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			180　自分の控えポケモンの技をランダムで出す
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_180:
	//ランダムで出せる技を選択して技のシーケンスへジャンプ
	NEKONOTE		Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
