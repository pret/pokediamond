//============================================================================
/**
 *
 *@file		be_258.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			258�@�G�̉�𗦂��P�i�K������{
 *				 ���葤�̂Ђ���̂��ׁA���t���N�^�[�A����҂̂܂���A���낢����A�܂��т��A�ǂ��т��̌��ʂ��Ȃ����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_258:
	VALUE					VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KIRIHARAI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END

