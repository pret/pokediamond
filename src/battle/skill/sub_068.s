
//============================================================================
/**
 *
 *@file		sub_068.s
 *@brief	�퓬�V�[�P���X
 *			��ǂ肬�̂��˒ǉ����ʃV�[�P���X

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_068:
	//�݂������o����Ă��鎞�́A���s����
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//�����^�C�v�ɂ́A���ʂ��Ȃ�
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_type1,KUSA_TYPE,Koukanai
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_type2,KUSA_TYPE,Koukanai
	ATTACK_MESSAGE
	SERVER_WAIT
	//���łɏh���Ă��鎞�́A��p���b�Z�[�W���o��
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_YADORARE,NoHit
	//�������ŊO��Ă��鎞�́A��p���b�Z�[�W���o��
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,NoHit
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	//��ǂ肬�t���O���Z�b�g
	PSP_VALUE_WORK	VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,BUF_PARA_ATTACK_CLIENT
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_YADORARE
	MESSAGE			YadorigiMineMsg,TAG_NICK,SIDE_DEFENCE
	BRANCH			SUB_068_END
NoHit:
	//�Z�̔����Ɏ��s�����t���O���Z�b�g
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	WAIT			MSG_WAIT
	MESSAGE			KawashitaMineMsg,TAG_NICK,SIDE_DEFENCE
SUB_068_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
Koukanai:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_KOUKANAI
	SEQ_END
