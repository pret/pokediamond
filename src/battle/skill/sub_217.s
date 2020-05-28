
//============================================================================
/**
 *
 *@file		sub_217.s
 *@brief	戦闘シーケンス
 *			2ターン技を1ターンでだす装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_217:
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//技エフェクトオフ時のために消える系のチェックをして姿を消す
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE,NoVanish
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
NoVanish:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			Item1turnMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	KILL_ITEM		SIDE_ATTACK
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END
