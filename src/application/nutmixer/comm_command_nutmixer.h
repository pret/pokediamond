/**
 *	@file	comm_command_nutmixer.h
 *	@brief	�i�b�c�~�L�T�[�@�ʐM�R�}���h�e�[�u��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 *	@data	06.05.23	tomoya �ύX
 */

#ifndef __H_COMM_COMMAND_NUTMIXER_H__
#define __H_COMM_COMMAND_NUTMIXER_H__

/// �i�b�c�~�L�T�[��p�ʐM�R�}���h�̒�`�B
enum CommCommandTradeList_e {

	//-------------------------------------
	//�@�Q�[���p
	//=====================================
	// �����p	
	CNM_MIXER_GAME_SYS_START = CS_COMMAND_MAX,	///< �~�L�T�[�Q�[���J�n		�e�[���q
	CNM_MIXER_GAME_END,							///< �Q�[���I��				�e�[���q
	
	// �f�[�^��M�p
	CNM_MIXER_GAME_BEFOREDATA_KO,	///< �Q�[���J�n�O�f�[�^	�e�[���q	�Q�[���J�n�����ɂ��Ȃ��Ă���
	CNM_MIXER_GAME_BEFOREDATA,		///< �Q�[���J�n�O�f�[�^	�q�[���e
	CNM_MIXER_GAMEDATA,				///< �Q�[���f�[�^		�e���[���q
	CNM_MIXER_GAME_RESULTDATA,		///< ���ʃf�[�^			�e�[���q	���ʕ\�������ɂ��Ȃ��Ă���
	CNM_MIXER_PORUTO_DATA,			///< �|���g�f�[�^�]���@�e�[���q
	CNM_MIXER_GAME_NEXT_KO,			///< �Q�[�����Â��邩�ǂ��� �e�[���q
	CNM_MIXER_GAME_NEXT,			///< �Q�[�����Â��邩�ǂ��� �q�[���e


	//-------------------------------------
	//	
	//=====================================
	
	//------------------------------------------------�����܂�
	CNM_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������
};

extern const CommPacketTbl* NutMixer_CommCommandTclGet( void );
extern int NutMixer_CommCommandTblNumGet( void );


#endif	//__H_COMM_COMMAND_NUTMIXER_H__
