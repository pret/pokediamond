
//============================================================================
/**
 *
 *@file		sub_090.s
 *@brief	戦闘シーケンス
 *			みがわりヒットシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_090:
	//ブリンクエフェクトするかしないかチェック
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK,NoBlinkEffect
	WAZAKOUKA_SE	SIDE_WORK
	POKEMON_BLINK	SIDE_WORK
	SERVER_WAIT
NoBlinkEffect:
	MESSAGE			MigawariHitMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	IF_PSP			IF_FLAG_BIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_MIGAWARI,SUB_090_END
MigawariEnd:
	STATUS_EFFECT	SIDE_WORK,STATUS_ACTION_DOLL_OFF
	SERVER_WAIT
	CHR_POP			SIDE_WORK
	SERVER_WAIT
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_MIGAWARI_IN
	SERVER_WAIT
	MESSAGE			MigawariEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_090_END:
	SEQ_END
