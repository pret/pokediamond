
//============================================================================
/**
 *
 *@file		sub_292.s
 *@brief	戦闘シーケンス
 *			2ターン技を1ターンでだす装備アイテム効果シーケンス（ロケットずつき専用）
 *@author	HisashiSogabe
 *@data		2006.08.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_292:
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//技エフェクトオフ時のために消える系のチェックをして姿を消す
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_KIE,NoVanish
	VANISH_ON_OFF	SIDE_ATTACK,SW_VANISH_ON
NoVanish:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//防御を１段階上げるをセット
	VALUE_WORK		VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	VALUE			VAL_SET,BUF_PARA_TSUIKA_PARA,ADD_COND2_DEFUP
	VALUE			VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT
	GOSUB			SUB_SEQ_ABICNT_CALC
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			Item1turnMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	KILL_ITEM		SIDE_ATTACK
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END
