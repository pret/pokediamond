/**
 *	@file	porudemo.h
 *	@brief	�|���g�f���w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.03.28
 */

#ifndef __H_PORUDEMO_H__
#define __H_PORUDEMO_H__

#include "poketool/poke_tool.h"
#include "savedata/poruto_util.h"

//======================================================
//�f�[�^�p���\���̒�`
//======================================================
typedef struct _PORUDEMO_PARAM{
	POKEMON_PARAM*	pp;	///<�|�P����
	PORUTO_DATA*	poruto;	///<�|���g�f�[�^
	u16	flavor;		///<�|���g�̎��
	u8	msg_spd;	///<���b�Z�[�W�X�s�[�h
	u8	win_type;	///<�E�B���h�E�^�C�v
}PORUDEMO_PARAM;

//======================================================
//�I�[�o�[���C�v���Z�X��`
//======================================================
extern PROC_RESULT PoruDemo_Init(PROC* proc,int *seq);
extern PROC_RESULT PoruDemo_Main(PROC* proc,int *seq);
extern PROC_RESULT PoruDemo_End(PROC* proc,int *seq);

#endif	//__H_PORUDEMO_H__
