//============================================================================
/**
 *
 *@file		be_241.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			241　相手が出そうとしている攻撃技を１．５倍の威力で出す。さきに攻撃できれば成功。できない場合失敗。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_241:
	//出せる技を選択して技のシーケンスへジャンプ
	SAKIDORI		Umakukimaran
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
