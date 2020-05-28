
//============================================================================
/**
 *
 *@file		sub_036.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			がまん中シーケンス
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_036:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_GAMAN,SeqGamaning

//がまんがとかれた
SeqGamanOff:
	MESSAGE			GamanOverMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//技エフェクトを変えるためにカウントを１に
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	//ためフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	//ため発動フラグをセット
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TAME_AFTER
	//ダメージワークが０の時は、がまん失敗
	IF				IF_FLAG_EQ,BUF_PARA_DAMAGE,0,SeqGamanFaild
	SEQ_END

SeqGamanFaild:
	GOSUB			SUB_SEQ_UMAKUKIMARAN
	//技の起動に失敗フラグを立てる
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END

//がまん中
SeqGamaning:
	MESSAGE			GamanMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
SeqGamanRet:
	SEQ_END

