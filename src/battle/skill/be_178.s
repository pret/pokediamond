//============================================================================
/**
 *
 *@file		be_178.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			178�@����̓������R�s�[����
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_178:
	//�����}���`�^�C�v�������Ă���|�P�����͎��s
	TOKUSEI_CHECK	TOKUSEI_HAVE,SIDE_ATTACK,TOKUSYU_MARUTITAIPU,Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NARIKIRI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
