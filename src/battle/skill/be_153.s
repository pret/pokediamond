//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			153�@�G���J�E���g�퓬���͋����I�ɐ퓬���I��������
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_153:
	//�쐶��̂݋N��
	IF			IF_FLAG_BIT,BUF_PARA_FIGHT_TYPE,FIGHT_TYPE_TRAINER,Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_TELEPORT|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
