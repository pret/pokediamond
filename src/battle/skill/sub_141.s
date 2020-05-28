
//============================================================================
/**
 *
 *@file		sub_141.s
 *@brief	戦闘シーケンス
 *			あくびシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_141:
	//特性ふみんを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiUmakukimaran
	//特性やるきを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiUmakukimaran
	//天候無効系の特性は、天候チェックを無視
	NOOTENKI_CHECK				SUB_141_NEXT
	//天候がはれじゃないときは、特性リーフガードチェックをしない
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_141_NEXT
	//特性リーフガードを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiUmakukimaran
SUB_141_NEXT:

	ATTACK_MESSAGE
	SERVER_WAIT
NoAttackMsg:
//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran
//特性ぼうおんを持っているときは、さわぐチェックをしない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,NoSawaguCheck
//さわがれている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,Umakukimaran
NoSawaguCheck:
//すでに状態異常になっている場合は、失敗する
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran
//しんぴのまもりで守られている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiUmakukimaran
//命中率で外れている場合は、うまくきまらん
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

	AKUBI			Umakukimaran

	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	MESSAGE			AkubiM2MMsg,TAG_NICK_NICK,SIDE_ATTACK,SIDE_TSUIKA
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

//特性で防いだとき
TokuseiUmakukimaran:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			TokuseiUmakukimaranMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_141_END

//うまくきまらないとき
Umakukimaran:
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_141_RET

//しんぴのまもりで防いだ時
ShinpiUmakukimaran:
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_141_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_141_RET:
	SEQ_END

