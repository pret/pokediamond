//============================================================================
/**
 *
 *@file		be_144.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			144�@�G�̓���U���̃_���[�W��{�ɂ��ĕԂ��i�u���΂₳�v�Ɋ֌W�Ȃ��K����U�ɂȂ�j
 *			
 *
 *@author	HisashiSogabe
 *@data		2006.01.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_144:
	//�^�C�v�␳�v�Z�𖳎�����
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TYPE_FLAT
	MIRROR_CORT
	SEQ_END
