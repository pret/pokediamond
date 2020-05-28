
//============================================================================
/**
 *
 *@file		sub_255.s
 *@brief	戦闘シーケンス
 *			いうことを聞かずなまけるシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_255:
	WAIT		MSG_WAIT/2
	RANDOM_GET	3,0
	IF			IF_FLAG_EQ,BUF_PARA_CALC_WORK,1,IukotowokikanaiMessage
	IF			IF_FLAG_EQ,BUF_PARA_CALC_WORK,2,SoppowomuitaMessage
	IF			IF_FLAG_EQ,BUF_PARA_CALC_WORK,3,SiranpuriMessage
NamaketeiruMessage:
	MESSAGE		NamaketeiruMsg,TAG_NICK,SIDE_ATTACK
	BRANCH		SUB_255_NEXT
IukotowokikanaiMessage:
	MESSAGE		IukotowokikanaiMsg,TAG_NICK,SIDE_ATTACK
	BRANCH		SUB_255_NEXT
SoppowomuitaMessage:
	MESSAGE		SoppowomuitaMsg,TAG_NICK,SIDE_ATTACK
	BRANCH		SUB_255_NEXT
SiranpuriMessage:
	MESSAGE		SiranpuriMsg,TAG_NICK,SIDE_ATTACK
	BRANCH		SUB_255_NEXT
SUB_255_NEXT:
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
