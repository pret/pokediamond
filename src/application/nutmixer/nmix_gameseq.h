/**
 *	@file	nmix_gameseq.h
 *	@brief	�i�b�c�~�L�T�[�@�Q�[���V�[�P���X�R�}���h��`
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 */

#ifndef __H_NMIX_GAMESEQ_H__
#define __H_NMIX_GAMESEQ_H__

// �Q�[���������V�[�P���X
enum{
	NMIX_GAME_MIANSEQ_INIT,				// �Q�[����{�`��V�X�e���̏�����
	NMIX_GAME_MAINSEQ_SYSSTART,			// �Q�[�������̊J�n	�e�[���q�J�n����
	NMIX_GAME_MAINSEQ_SYSSTART_WAIT,	// �Q�[���V�X�e���J�n�����҂�
	NMIX_GAME_MAINSEQ_BEFORE,			// �Q�[���J�n�O����
	NMIX_GAME_MAINSEQ_BEFORE_WAIT,		// �Q�[���J�n�O�����I���E�G�C�g
	NMIX_GAME_MAINSEQ_RES_LOAD,			// ���\�[�X�ǂݍ���
	NMIX_GAME_MAINSEQ_GAMESTART,		// �Q�[���J�n
	NMIX_GAME_MAINSEQ_GAMEMAIN,			// �Q�[�����C��
	NMIX_GAME_MAINSEQ_GAMEEND,			// �Q�[���j������
	NMIX_GAME_MAINSEQ_RESULT_WAIT,		// �Q�[�����U���g���҂�
	NMIX_GAME_MAINSEQ_RESULT,			// �Q�[�����U���g����
	NMIX_GAME_MAINSEQ_SYSEND_WAIT,		// �Q�[���I���҂�
	NMIX_GAME_MIANSEQ_RES_RELEASE,		// ���\�[�X�j��
	NMIX_GAME_MAINSEQ_SYSEND,			// �I������
};

#endif	//__H_NMIX_GAMESEQ_H___
