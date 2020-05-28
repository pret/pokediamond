
//============================================================================
/**
 *
 *@file		sub_257.s
 *@brief	戦闘シーケンス
 *			いうことを聞かずにひるねをはじめるシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_257:
	WAIT		MSG_WAIT/2
	MESSAGE		HiruneMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//追加対象にAttackClientを設定
	VALUE_WORK	VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_ATTACK_CLIENT
	//技効果による追加効果フラグを設定
	VALUE		VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA
	//ねむり追加シーケンスをコール
	GOSUB		SUB_SEQ_NEMURI
	SEQ_END
