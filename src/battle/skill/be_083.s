//============================================================================
/**
 *
 *@file		be_083.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			083　全ての技の中からランダムで１つ技を出す
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_083:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//ランダムで出せる技を選択して技のシーケンスへジャンプ
	YUBIWOHURU
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL
