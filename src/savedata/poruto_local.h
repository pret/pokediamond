/**
 *	@file	poruto_local.h
 *	@brief	�|���g�Z�[�u�f�[�^�u���b�N �\���̒�`
 *	@author	Miyuki Iwasawa
 *	@date	06.3.10
 */

#ifndef __H_PORUTO_LOCAL_H__
#define __H_PORUTO_LOCAL_H__

#include "savedata/poruto.h"

///�|���g�Z�[�u�f�[�^�u���b�N��`
typedef struct _PORUTO_BLOCK{
 PORUTO_DATA	poruto[PORUTO_STOCK_MAX];
}_PORUTO_BLOCK;

#endif //__H_PORUTO_LOCAL_H__

