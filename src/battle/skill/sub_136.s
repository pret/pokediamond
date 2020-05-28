
//============================================================================
/**
 *
 *@file		sub_136.s
 *@brief	戦闘シーケンス
 *			ねがいごとがかなったシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_136:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ヒールブロックを受けている時は回復動作なし
	IF_PSP			IF_FLAG_NE,SIDE_WORK,ID_PSP_wkw_healblock_count,0,Healblock
	//HPMAXを読み込み
	PSP_VALUE_WORK	VAL_GET,SIDE_WORK,ID_PSP_hpmax,BUF_PARA_CALC_WORK
	//HPがまんたんの時は、その旨のメッセージを表示
	IF_PSP_WORK		IF_FLAG_EQ,SIDE_WORK,ID_PSP_hp,BUF_PARA_CALC_WORK,HP_MANTAN
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_RECOVER
	SERVER_WAIT
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			JikosaiseiMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
SUB_136_END:
	SEQ_END

HP_MANTAN:
	WAIT			MSG_WAIT
	MESSAGE			MantanMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Healblock:
	VALUE			VAL_SET,BUF_PARA_WAZA_WORK,WAZANO_KAIHUKUHUUZI
	MESSAGE			HealblockRecoverNGMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
