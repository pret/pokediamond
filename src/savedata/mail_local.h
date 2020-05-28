/**
 *  @file	mail_local.h
 *	@brief	���[���Z�[�u�f�[�^���䃂�W���[���݂̂�include���ėǂ�
 *	@author	Miyuki Iwasawa
 *	@date	06.03.02
 */

#ifndef __H_MAIL_LOCAL_H__
#define __H_MAIL_LOCAL_H__

#include "savedata/mail.h"

///���[���f�[�^�Z�[�u�f�[�^�u���b�N��`�\����
typedef struct _MAIL_BLOCK{
//	MAIL_DATA	temoti[MAIL_STOCK_TEMOTI];	
	MAIL_DATA	paso[MAIL_STOCK_PASOCOM];
//	MAIL_DATA	extrade[MAIL_STOCK_EXTRADE];
//	MAIL_DATA	sodateya[MAIL_STOCK_SODATEYA];
}_MAIL_BLOCK;

#endif	//__H_MAIL_LOCAL_H__

