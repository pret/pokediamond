//============================================================================
/**
 *
 *@file		be_233.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			233�@�����Ă��铹���Ώۂɓ�������B�����Ă��铹��Ȃ��ꍇ���s�B
 *				 �����铹��ɂ��З͂���ʕω�����B�ʓr���ʃe�[�u���p�ӁB�ʃV�[�g�y����ǉ��Z�z�̎Q�ƁB
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_233:
	//�����}���`�^�C�v�́A���܂����܂��
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran
	NAGETSUKERU		Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_NAGETSUKERU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			NagetsukeruMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
//	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_item,0
	KILL_ITEM		SIDE_ATTACK
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END

