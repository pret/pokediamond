
//============================================================================
/**
 *
 *@file		sub_018.s
 *@brief	戦闘シーケンス
 *			ねむりシーケンス
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_018:
	//技効果での追加の時は専用のチェックをする
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,NormalCheck
	//特性ふみんを持っているときは、失敗する（かたやぶりチェックのために最上位）
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiNoSleep
	//特性やるきを持っているときは、失敗する（かたやぶりチェックのために最上位）
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiNoSleep
	//天候無効系の特性は、天候チェックを無視
	NOOTENKI_CHECK	WazaKoukaCheckNext
	//天候がはれじゃないときは、特性リーフガードチェックをしない
	IF				IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,WazaKoukaCheckNext
	//特性リーフガードを持っているときは、失敗する（かたやぶりチェックのために最上位）
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoSleep
WazaKoukaCheckNext:
//すでに眠っている場合は、失敗する
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep
//特性ぼうおんを持っているときは、さわぐチェックをしない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,WazaKoukaNoSawaguCheck
//さわがれている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
WazaKoukaNoSawaguCheck:
//すでに状態異常になっている場合は、失敗する
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran
	BRANCH			NoWazaEffect
NormalCheck:
	//特性ふみんを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_HUMIN,TokuseiNoSleep
	//特性やるきを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_YARUKI,TokuseiNoSleep
	//天候無効系の特性は、天候チェックを無視
	NOOTENKI_CHECK				SUB_018_NEXT
	//天候がはれじゃないときは、特性リーフガードチェックをしない
	IF							IF_FLAG_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE_ALL,SUB_018_NEXT
	//特性リーフガードを持っているときは、失敗する（かたやぶりチェックのために最上位）
	KATAYABURI_TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_RIIHUGAADO,TokuseiNoSleep
SUB_018_NEXT:
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

//特性追加の場合、みがわりチェックなし
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoMigawari
//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_TSUIKA,Umakukimaran

NoMigawari:
//すでに眠っている場合は、失敗する
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep

//特性ぼうおんを持っているときは、さわぐチェックをしない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_TSUIKA,TOKUSYU_BOUON,NoSawaguCheck
//さわがれている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
NoSawaguCheck:
//すでに状態異常になっている場合は、失敗する
	IF_PSP			IF_FLAG_NE,SIDE_TSUIKA,ID_PSP_condition,0,Umakukimaran

//特性追加の場合、以下のチェックは必要なし
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,NoWazaEffect

//わざがはずれているときは、うまくきまらんにする
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran

//しんぴのまもりで守られている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_SIDE_CONDITION_TSUIKA,SIDE_CONDITION_SHINPI,ShinpiNoSleep
//直接追加の場合、WAZAOUTシーケンスで技エフェクトを出さないので、ここで出す
	IF				IF_FLAG_NE,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT

NoWazaEffect:
	STATUS_EFFECT	SIDE_TSUIKA,STATUS_NEMURI
	SERVER_WAIT
	//２～５ターンの乱数を取得
	RANDOM_GET		3,3
	PSP_VALUE_WORK	VAL_BIT,SIDE_TSUIKA,ID_PSP_condition,BUF_PARA_CALC_WORK
//特性追加の場合、専用メッセージへ
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiSleepMsg
NormalMsg:
	MESSAGE			SleepBeginMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			MsgAfter

TokuseiSleepMsg:
	MESSAGE			TokuseiSleepBeginM2MMsg,TAG_NICK_TOKU_NICK,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_TSUIKA
MsgAfter:
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_SET		SIDE_TSUIKA,STATUS_NEMURI
	SERVER_WAIT
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_waza_kouka,WAZAKOUKA_KIE,KieOff
	//ため系フラグを落とす
	KEEP_OFF		SIDE_TSUIKA
	BRANCH			NextCheck
KieOff:
	//ため系フラグを落とす
	KEEP_OFF		SIDE_TSUIKA
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_TSUIKA_CLIENT
	GOSUB			SUB_SEQ_VANISH_OFF
NextCheck:
	SEQ_END

//特性で防いだとき
TokuseiNoSleep:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
//特性追加の場合、専用メッセージへ
//	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,TokuseiNoSleep2
//特性追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
//技効果での追加の時はAttackMessageを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,TokuseiNoAttackMessage
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
TokuseiNoAttackMessage:
	MESSAGE			TokuseiSleepNGMineMsg,TAG_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA
	BRANCH			SUB_018_END
TokuseiNoSleep2:
	MESSAGE			TokuseiNoTokuseiM2MMsg,TAG_NICK_TOKU_NICK_TOKU,SIDE_TSUIKA,SIDE_TSUIKA,SIDE_WORK,SIDE_CLIENT_WORK
	BRANCH			SUB_018_END

//うまくきまらないとき
Umakukimaran:
//間接追加、特性追加、技効果での追加の場合は、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_WAZA_KOUKA,SUB_018_RET
	WAIT			MSG_WAIT
	WAZA_PARAM_GET	ID_WTD_attackrange
	//複数選択技は、あたらなかったメッセージにする
	IF				IF_FLAG_EQ,BUF_PARA_CALC_WORK,RANGE_DOUBLE,Ataranakatta
	IF				IF_FLAG_EQ,BUF_PARA_CALC_WORK,RANGE_TRIPLE,Ataranakatta
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	BRANCH			SUB_018_RET
Ataranakatta:
	GOSUB			SUB_SEQ_ATARANAKATTA
	BRANCH			SUB_018_RET

//すでに眠っているとき
AlreadySleep:
//間接追加、特性追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_TOKUSEI,SUB_018_RET
	WAIT			MSG_WAIT
	MESSAGE			AlreadySleepMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END

//さわぐで眠れないとき
SawaguNoSleep:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
//自分が騒いでいる時は、専用メッセージで
	IF_PSP			IF_FLAG_BIT,SIDE_TSUIKA,ID_PSP_condition2,CONDITION2_SAWAGU,SawaguMine
	WAIT			MSG_WAIT
	MESSAGE			NoisySleepNGMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END
SawaguMine:
	WAIT			MSG_WAIT
	MESSAGE			SleepNGMineMsg,TAG_NICK,SIDE_TSUIKA
	BRANCH			SUB_018_END

//しんぴのまもりで眠れないとき
ShinpiNoSleep:
//間接追加の場合、メッセージを出さない
	IF				IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_INDIRECT,SUB_018_RET
	WAIT			MSG_WAIT
	MESSAGE			ShinpiGuardMineMsg,TAG_NICK,SIDE_TSUIKA
SUB_018_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
//	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_018_RET:
	SEQ_END

