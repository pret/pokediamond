//============================================================================
/**
 *
 *@file		be_164.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			164�@�T�^�[���̊ԁA�V�C��������Ԃɂ���B������Ԓ��͕X�^�C�v�ȊO�̓^�[���`�F�b�N�ɂP�^�P�U�_���[�W
 *
 *@author	HisashiSogabe
 *@data		2006.01.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_164:
	IF				IF_FLAG_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_ARARE,Umakukimaran
	MESSAGE_PARAM	ArareMsg,TAG_NONE
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_ARARE
	VALUE			VAL_SET,BUF_PARA_WEATHER_COUNT,ARARE_COUNT
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_TENKOU|ADD_STATUS_WAZAKOUKA
	//�������ʂł����̃^�[�����𑝂₷���ʂ́A�^�[�����𑝂₷
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_ARAREUP,BE_164_END
	SOUBI_ATK_GET	SIDE_ATTACK,BUF_PARA_CALC_WORK
	VALUE_WORK		VAL_ADD,BUF_PARA_WEATHER_COUNT,BUF_PARA_CALC_WORK
BE_164_END:
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
