//============================================================================
/**
 *
 *@file		be_173.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			173�@�t�B�[���h�ɂ���ďo��Z���Ⴄ�@�C���Ȃ݂̂�@���ނ灁�͂��σJ�b�^�[�@���A������Ȃ���
 *				�u������̂�����́@�Ȃ݂̂�Ɂ@�Ȃ����I�v
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_173:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	SHIZENNOCHIKARA
	MESSAGE			ShizennochikaraMsg,TAG_WAZA_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	JUMP_WAZA_WORK	JWW_FLAG_NORMAL
