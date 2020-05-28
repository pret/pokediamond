
//============================================================================
/**
 *
 *@file		sub_027.s
 *@brief	戦闘シーケンス
 *			こおりの追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_027:
	//特性マグマのよろいを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_MAGUMANOYOROI,TokuseiNoKoori
	//天候無効系の特性は、天候チェックを無視
	NOOTENKI_CHECK				SUB_027_NEXT
	//天候がはれの時は、こおらない
	IF							IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,Umakukimaran
SUB_027_NEXT:
	//間接追加の場合、りんぷんチェックをする
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,NoRinpun
	//特性りんぷんを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RINPUN,Umakukimaran
NoRinpun:
//直接追加の場合、WAZAOUTシーケンスでメッセージを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoAttackMsg
	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:

//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran

//すでにこおっている場合は、失敗する
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_KOORI,AlreadyKoori

//こおりタイプには効果がない
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type1,KOORI_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_TSUIKA,ID_PSP_type2,KOORI_TYPE,Koukanai

//すでに状態異常になっている場合は、失敗する
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//わざがはずれているときは、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//しんぴのまもりで守られている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoKoori

//直接追加の場合、WAZAOUTシーケンスで技エフェクトを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
NoWazaEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_KOORI
	SERVER_WAIT
	//こおりフラグを立てる
	PSP_VALUE		VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_KOORI
	//ため系フラグを落とす
	KEEP_OFF		SIDE_TSUIKA
	MESSAGE			KooriMineMsg,TAG_NICK,SIDE_TSUIKA
	SERVER_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_KOORI
	WAIT			MSG_WAIT
	SEQ_END

//うまくきまらないとき
Umakukimaran:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_027_RET

//すでにこおっているとき
AlreadyKoori:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	//現状メッセージがない
//	MESSAGE			AlreadyKooriMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_027_END

//こうかがないとき
Koukanai:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	MESSAGE			KoukanaiMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_027_END

//特性でこおりを防ぐ
TokuseiNoKoori:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//現状メッセージがない
//	MESSAGE			MagumanoyoroiMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_027_END


//しんぴのまもりで防がれたとき
ShinpiNoKoori:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_027_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_027_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_027_RET:
	SEQ_END

