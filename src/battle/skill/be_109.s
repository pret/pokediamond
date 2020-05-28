//============================================================================
/**
 *
 *@file		be_109.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			109�@�ʏ�́u���΂₳�v���P�i�K������u���������v�u�ڂ�����v���P�i�K�オ��̂����A
 *				 �S�[�X�g�^�C�v�̃|�P���������̋Z���g�p����ƁA�g�o�����炷�����ɁA�U�����̃|�P�����̂g�o���P�^�Q���炵�܂��B
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_109:
	//�|�P�����̃^�C�v���S�[�X�g�^�C�v�Ȃ�A�S�[�X�g�^�C�v�̂̂낢���N��
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_type1,GHOST_TYPE,GhostNoroi
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_type2,GHOST_TYPE,GhostNoroi
NormalNoroi:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NORMAL_NOROI|ADD_STATUS_ATTACK
	SEQ_END

GhostNoroi:
	//�Z�ɂ���ă^�C�v���S�[�X�g�ɕς���Ă���ꍇ������̂ŁADefenceClient�̃`�F�b�N������
	IF_WORK			IF_FLAG_NE,BUF_PARA_ATTACK_CLIENT,BUF_PARA_DEFENCE_CLIENT,GhostNoroiStart
	DIR_CLIENT_GET	SIDE_ATTACK
GhostNoroiStart:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GHOST_NOROI|ADD_STATUS_WAZAKOUKA
	//�S�[�X�g�̋Z�G�t�F�N�g���Z�b�g
	VALUE			VAL_SET,BUF_PARA_WAZA_EFF_CNT,1
	SEQ_END
