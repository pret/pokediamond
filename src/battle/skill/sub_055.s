
//============================================================================
/**
 *
 *@file		sub_055.s
 *@brief	戦闘シーケンス
 *			ねむるシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_055:
	ATTACK_MESSAGE
	SERVER_WAIT
	//特性ふみんを持っているときは、失敗する
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_HUMIN,TokuseiNoSleep
	//特性やるきを持っているときは、失敗する
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_YARUKI,TokuseiNoSleep
	//すでに眠っている場合は、失敗する
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI,AlreadySleep
	//特性ぼうおんを持っているときは、さわぐチェックをしない
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_BOUON,NoSawaguCheck
	//さわがれている場合は、失敗する
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SAWAGU,SawaguNoSleep
NoSawaguCheck:
	//HPMAXを取得
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_hpmax,BUF_PARA_HP_CALC_WORK
	//HPまんたんなら失敗
	IF_PSP_WORK		IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_hp,BUF_PARA_HP_CALC_WORK,HP_Mantan
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//状態異常の時は、状態異常を治す
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF,StatusRecoverMessage
	MESSAGE			NemuruMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_NEXT
StatusRecoverMessage:
	STATUS_SET		SIDE_ATTACK,STATUS_NORMAL
	//ねむり以外のフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF
	MESSAGE			NemuruRecoverMineMsg,TAG_NICK,SIDE_ATTACK
SUB_055_NEXT:
	SERVER_WAIT
	WAIT			MSG_WAIT
	//2ターンねむる（現在のターンを含めて３をセット）
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition,3
	STATUS_SET		SIDE_ATTACK,STATUS_NEMURI
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP計算サブルーチンへ
	GOSUB			SUB_SEQ_HP_CALC
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_NEMURI_OFF,StatusRecoverMessage
	MESSAGE			JikosaiseiMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_RET

TokuseiNoSleep:
	WAIT			MSG_WAIT
	MESSAGE			TokuseiSleepNGMineMsg,TAG_NICK_TOKU,SIDE_ATTACK,SIDE_ATTACK
	BRANCH			SUB_055_END
AlreadySleep:
	WAIT			MSG_WAIT
	MESSAGE			AlreadySleepMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
SawaguNoSleep:
//自分が騒いでいる時は、専用メッセージで
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_SAWAGU,SawaguMine
	WAIT			MSG_WAIT
	MESSAGE			NoisySleepNGMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
SawaguMine:
	WAIT			MSG_WAIT
	MESSAGE			SleepNGMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			SUB_055_END
HP_Mantan:
	WAIT			MSG_WAIT
	MESSAGE			MantanMineMsg,TAG_NICK,SIDE_ATTACK
SUB_055_END:
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
SUB_055_RET:
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

