
//============================================================================
/**
 *
 *@file		sub_275.s
 *@brief	戦闘シーケンス
 *			ポケモン捕獲シーケンス（サファリボール）
 *@author	HisashiSogabe
 *@data		2005.07.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_275:
	IF					IF_FLAG_BIT,BUF_PARA_FIGHT_TYPE,FIGHT_TYPE_POKE_PARK,ParkBallThrow
	MESSAGE				ItemUseMsg,TAG_TRNAME_ITEM,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	TRAINER_THROW		SIDE_MINE,TT_TYPE_SAFARI_BALL
	BRANCH				SUB_275_NEXT
ParkBallThrow:
	MESSAGE_NO_DIR		ParkballThrowMsg,TAG_NICK,SIDE_ENEMY
	SERVER_WAIT
	TRAINER_THROW		SIDE_MINE,TT_TYPE_PARK_BALL
SUB_275_NEXT:
	POKEMON_GET_INIT	GET_SAFARI
	POKEMON_GET
	//サファリボールの個数をチェックする
	IF					IF_FLAG_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_POKE_GET,SUB_275_END
	IF					IF_FLAG_NE,BUF_PARA_SAFARI_BALL_COUNT,0,SUB_275_END
	SE_PLAY				SIDE_ATTACK,BSE_SAFARI_END				
	MESSAGE				SafariZoneEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT				MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	VALUE				VAL_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_ESCAPE
SUB_275_END:
	SEQ_END
