/**
 *	@file	nmix_2d.h
 *	@brief	�i�b�c�~�L�T�[ 2D���\�[�X�Ǘ�
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 */

#ifndef __H_NMIX_2D_H__
#define __H_NMIX_2D_H__

#include "application/app_tool.h"

typedef struct _NMIX_2DRES{
	GF_BGL_INI *bgl;	///<BGL�f�[�^

	void*	pScrBuf01;
	NNSG2dScreenData*	pScr01;
	GF_BGL_BMPWIN	win;
	
}NMIX_2DRES;

#endif	//__H_NMIX_2D_H__
