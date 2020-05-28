/**
 *	@file	nutmixer_def.h
 *	@brief	�i�b�c�~�L�T�[�@�萔��`
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_NUTMIXER_DEF_H__
#define __H_NUTMIXER_DEF_H__

///�v���C���[�h��`
#define NUTMIXER_PLAY_LOCAL	(0)
#define NUTMIXER_PLAY_COMM	(1)

///�����o�[����`
#define NUTMIXER_MEMBER_MAX	(4)

///�ʐM�����҂��@�A���o�[
typedef enum{
	SYNCHROID_NONE,				///<�ʐM�����i�V
	SYNCHROID_BAG_END,			///<�o�b�N�I���҂�
	SYNCHROID_GAME_START,		///<�Q�[���J�n
	SYNCHROID_GAME_END,			///<�Q�[���I��
};

#ifdef PM_DEBUG
///< AUTO�~�L�T�[����
//#define DEBUG_NUTMIXER_AUTO	
#endif


#endif	//__H_NUTMIXER_DEF_H__
