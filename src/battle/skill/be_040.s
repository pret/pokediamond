//============================================================================
/**
 *
 *@file		be_040.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			040�@�G�|�P�����̂g�o�𔼕��ɂ���
 *
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_040:
	//�^�C�v�␳�v�Z�𖳎�����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	//HP�̔������_���[�W��
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hp,BUF_PARA_DAMAGE
	VALUE			VAL_MUL,BUF_PARA_DAMAGE,-1
	DAMAGE_DIV		BUF_PARA_DAMAGE,2
	SEQ_END
