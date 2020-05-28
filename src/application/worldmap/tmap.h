/**
 *	@file	tmap.h
 *	@brief	�^�E���}�b�v���W���[�����ł������J����w�b�_
 *	@date	05.11.02
 *	@author	Miyuki Iwasawa
 */
#ifndef _TMAP_H_
#define _TMAP_H_

#include "townmap.dat"
#include "tmap_def.h"
#include "tmap_gra.naix"	//�A�[�J�C�u�t�@�C��
#include "tmap_sub.h"	//�T�u


//================================================================
///�f�[�^�^��`�G���A
//================================================================
typedef struct _TMAP_SCROLLPRM{
	int	scrX;
	int	scrY;
	int	difX;
	int	difY;
}TMAP_SCROLLPRM;

///�v���g�^�C�v
struct TMAP_MAIN_DAT;
///�T�u�v���Z�X��`�p�֐��^
//typedef int (*TMapSubProc)(TMAP_MAIN_DAT* pMain);

///���C�����[�N
typedef struct TMAP_MAIN_DAT{
	u8	mode;	///<���샂�[�h�擾
	u8	forcus;	///<�㉺��ʂǂ���ɐ��䂪���邩�H
	u16	mapView;	///<�z�z�}�b�v�`�搧��t���O
	int	heapID;	///<HeapID
	int	main_seq;	///<�V�[�P���X
	int	sub_seq;	///<�V�[�P���X
	int seq;
	int	wipe_f;		///<���C�v�t���O

	int	cposX;
	int cposZ;
	int	gx;
	int gz;
	
	GF_BGL_INI *bgl;	///<BGL�f�[�^
	TOWNMAP_PARAM* param;	///<�O�����p���p�����[�^IO
	FMZ_PTR	pZone;		///<�]�[���f�[�^�擾�|�C���^
	void*	pSwork;			///<�T�u���[�N�m�ۃ|�C���^
	int (*keyFunc)(struct TMAP_MAIN_DAT*);

	TMAP_VIEW_DAT*	pVDat;
	TMAP_GDAT_LIST* pBDat;
	TMAP_FOOT	foot[TMAP_FVIEW_MAX];
	
	///���b�Z�[�W���\�[�X
	MSGDATA_MANAGER*	pMsgMap;
	MSGDATA_MANAGER*	pMsgTMap;
	STRBUF				*placeName;
	
	///VBlank�]���p�ۑ��p�����[�^
	int	vb_trans;
	int	vb_zoneID;
	TMAP_GDAT*	vb_block;
	
	///�O���t�B�b�N���\�[�X
	void*	pScrBuf01;
	void*	pScrBuf01_back;
	void*	pScrBuf01_dis;
	void*	pScrBuf02_dm;
	void*	pScrBuf02_dr;
	void*	pScrBuf02_dswm;
	void*	pScrBuf02_sw;
	void*	pScrBuf02_dis;
	
	NNSG2dScreenData*	pScr01;
	NNSG2dScreenData*	pScr01_back;
	NNSG2dScreenData*	pScr01_dis;
	NNSG2dScreenData*	pScr02_dm;
	NNSG2dScreenData*	pScr02_dr;
	NNSG2dScreenData*	pScr02_dswm;
	NNSG2dScreenData*	pScr02_sw;
	NNSG2dScreenData*	pScr02_dis;

	CATS_SYS_PTR	pCActSys;	///<�Z���A�N�^�[�V�X�e��
	CATS_RES_PTR	pCActRes;	///<�Z���A�N�^�[���\�[�X
	CATS_ACT_PTR	pCAct;		///<�A�N�g
}TMAP_MAIN_DAT;

///�T�u�v���Z�X��`�p�֐��^
typedef int (*TMapSubProc)(TMAP_MAIN_DAT* pMain);

typedef struct _TMAP_SUB_PROC{
	TMapSubProc	init;
	TMapSubProc	build;
	TMapSubProc	fadein;
	TMapSubProc	fadeout;
	TMapSubProc	keyIO;
	TMapSubProc	main;
	TMapSubProc	draw;
	TMapSubProc	release;
	TMapSubProc	vBlank;
}TMAP_SUB_PROC;

///==============================================================
//�^�E���}�b�v���W���[�����O���[�o���֐�
///==============================================================

#endif	//_TMAP_H_
