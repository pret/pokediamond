
//============================================================================
/**
 *
 *@file		sub_051.s
 *@brief	戦闘シーケンス
 *			あばれた後のこんらん追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_051:
	//技効果による追加効果フラグを設定
	VALUE		VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA
	//こんらん追加シーケンスをコール
	GOSUB		SUB_SEQ_KONRAN
	//こんらんしていなかったら、メッセージ表示しない
	IF_PSP		IF_FLAG_NBIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_KONRAN,SUB_051_END
	MESSAGE		AbareruEndMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT		MSG_WAIT
SUB_051_END:
	SEQ_END
