/**
 *	@file	fld_nmixer.c
 *	@brief	�t�B�[���h�p�@�i�b�c�~�L�T�[�w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_FLD_NUTMIXER_H__
#define __H_FLD_NUTMIXER_H__


#include "application/nutmixer.h"

///�v���C���[�h��`
#define NUTMIXER_CALL_LOCAL	(0)	///<��l�v���C���[�h
#define NUTMIXER_CALL_COMM	(1)	///<�ʐM�v���C���[�h

/**
 *	@brief	�i�b�c�~�L�T�[�Ăяo�����[�N�f�[�^�쐬
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	��l�v���C���[�h
 *					NUTMIXER_CALL_COMM:1	�ʐM���[�h
 */
extern NUTMIXER_PARAM* NutMixer_CreateCallWork(int mode,SAVEDATA* savedata,int heapID);

/**
 *	@brief	�i�b�c�~�L�T�[�Ăяo��
 *
 *	@param	mode	NUTMIXER_CALL_LOCAL:0	��l�v���C���[�h
 *					NUTMIXER_CALL_COMM:1	�ʐM���[�h
 */
extern NUTMIXER_PARAM* FieldNutMixer_InitCall(FIELDSYS_WORK* fsys,int mode,int heapID);


#endif	//__H_FLD_NUTMIXER_H__
