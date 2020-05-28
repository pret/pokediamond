//============================================================================
/**
 *
 *@file		be_008.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			008　敵が「ねむり」状態の時だけ効果のある技（「ねむり」状態でないと技は失敗する）、
 *				 敵に与えたダメージの半分の数値だけＨＰが回復する
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_008:
	//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_DEFENCE,Sippai
	//相手が寝ていないときは、失敗する
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_NEMURI,Sippai

	//技効果を追加してシーケンスを発動
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_YUMEKUI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Sippai:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			SippaiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//WazaStatusMessageを無効にするためにこのフラグを立てる
	//VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI_RENZOKU_CHECK
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END


