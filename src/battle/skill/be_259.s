//============================================================================
/**
 *
 *@file		be_259.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			259　攻撃する順番を素早さが遅い順にする。同じ技プライオリティ間のみで入れ替えをする。
 *				 特性あとだしに対しては技無効。ツメ系の道具発動します。
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_259:
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TRICKROOM,TrickRoomReverse
TrickRoomNormal:
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,TRICKROOM_COUNT<<FIELD_TRICKROOM_SHIFT
	MESSAGE_PARAM	TrickRoomMineMsg,TAG_NICK,SIDE_ATTACK
	BRANCH			BE_259_NEXT
TrickRoomReverse:
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TRICKROOM
	MESSAGE_PARAM	TrickRoomReverseMineMsg,TAG_NICK,SIDE_ATTACK
BE_259_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	TRICKROOM
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
