
//============================================================================
/**
 *
 *@file		sub_012.s
 *@brief	戦闘シーケンス
 *			AbirityCount系追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_012:
	//かたやぶりチェックのために上に移動
	ABICNT_CALC		AbirityCountNoCalc,AbirityCountNoAct,Umakukimaran
//直接追加の場合、WAZAOUTシーケンスでメッセージを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoAttackMsg
	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:
//直接追加の場合、WAZAOUTシーケンスで技エフェクトを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG,NoStatusEffect
	STATUS_EFFECT_WORK	SIDE_TSUIKA,BUF_PARA_TEMP_WORK
	SERVER_WAIT
	//エフェクトの連続チェックのフラグがない場合は、フラグ立てはなし
	IF				IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_CHECK,NoStatusEffect
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_ABICNT_EFF_FLAG
NoStatusEffect:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
//上がりきっているor下がりきっているor特性で変化なし等
AbirityCountNoCalc:
//直接追加の場合、WAZAOUTシーケンスでメッセージを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,AbirityCountNoCalcNext
	ATTACK_MESSAGE
	SERVER_WAIT
AbirityCountNoCalcNext:
	//アサートメッセージ非表示フラグが立っていたら、非表示
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_DIRECT_MSG,AbirityCountNoAct
	WAIT			MSG_WAIT
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
//間接追加で、特にメッセージ表示の必要なし
AbirityCountNoAct:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
