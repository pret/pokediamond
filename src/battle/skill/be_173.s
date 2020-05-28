//============================================================================
/**
 *
 *@file		be_173.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			173　フィールドによって出る技が違う　海＝なみのり　草むら＝はっぱカッター　洞窟＝いわなだれ
 *				「しぜんのちからは　なみのりに　なった！」
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_173:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	SHIZENNOCHIKARA
	MESSAGE			ShizennochikaraMsg,TAG_WAZA_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL
