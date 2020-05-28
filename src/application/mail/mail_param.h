/**
 *	@file	mail_param.h
 *	@brief	���[���V�X�e���@�Ăяo�����̈��p���f�[�^�\���̌^��`
 *	@author	Miyuki Iwasawa
 *	@date	06.02.08
 */

#ifndef _H_MAIL_PARAM_H_
#define _H_MAIL_PARAM_H_

#include "savedata/mail_util.h"

typedef struct _MAIL_PARAM{
	u16	mode;		///<���[�����W���[���Ăяo���^�C�v
	u16	id;			///<�Ăяo��ID
	
	int	ret_val;	///<�߂�l

	int	blockID;
	u16 dataID;
	u8	poke_pos;
	u8	designNo;
	
	SAVEDATA*	savedata;	///<�Z�[�u�f�[�^�̎Q�ƃ|�C���^
	MAIL_DATA*	pDat;	///MAIL_DATA�̍\�z���[�N�Q�ƃ|�C���^
	MAIL_BLOCK* pBlock;
}MAIL_PARAM;

///���[�����W���[���Ăяo�����[�h
enum{
 MAIL_MODE_VIEW,
 MAIL_MODE_CREATE,
 MAIL_MODE_MAX,
};

#endif	//_H_MAIL_PARAM_H_



