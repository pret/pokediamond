//============================================================================
/**
 *
 *@file		be_259.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			259�@�U�����鏇�Ԃ�f�������x�����ɂ���B�����Z�v���C�I���e�B�Ԃ݂̂œ���ւ�������B
 *				 �������Ƃ����ɑ΂��Ă͋Z�����B�c���n�̓�������܂��B
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
