//==============================================================================================
/**
 * @file	opneing_sys.h
 * @brief	�I�[�v�j���O �V�X�e���@
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#ifndef _OPENING_SYS_H_
#define _OPENING_SYS_H_

#include "common.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/procsys.h"
#include "system/wordset.h"
#include "savedata/config.h"
#include "opening_obj.h"


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================
extern const PROC_DATA OpeningProcData;				//�v���Z�X��`�f�[�^

extern PROC_RESULT OpeningProc_Init( PROC * proc, int * seq );
extern PROC_RESULT OpeningProc_Main( PROC * proc, int * seq );
extern PROC_RESULT OpeningProc_End( PROC * proc, int * seq );

//==============================================================================================
//
//	��`
//
//==============================================================================================
//�r�b�g�}�b�vID
enum{
	BMPWIN_MENU_1 = 0,
	BMPWIN_GUIDE,
	BMPWIN_MENU_2,
	BMPWIN_OOKIDO,
	BMPWIN_YESNO,
	BMPWIN_IDSEL,
	OPENING_BMPWIN_MAX,								//BMP�E�B���h�E�̐�
};

#define OPENING_MENU_MAX		(4)					//���j���[�̐�

#define OP_FRM_FONT				(GF_BGL_FRAME1_M)

//�p���b�g��`
#define OP_TALKWIN_PAL			(10)				//��b�E�B���h�E�g�p�p���b�g�i���o�[
#define OP_MENU_PAL				(11)				//���j���[�E�B���h�E�g�p�p���b�g�i���o�[
#define OP_MSGFONT_PAL			(12)				//MSG�t�H���g�g�p�p���b�g�i���o�[
#define OP_FONT_PAL				(13)				//SYSTEM�t�H���g�g�p�p���b�g�i���o�[

//OBJ�i���o�[
#define OP_OBJ_HAKASE			(0)
#define OP_OBJ_RIVAL			(1)
#define OP_OBJ_KAGE				(2)

#define OP_VANISH_ON			(0)					//��\��
#define OP_VANISH_OFF			(1)					//�\��


//==============================================================================================
//
//	�\���̐錾
//
//==============================================================================================
typedef struct OPENING_WORK_tag
{
	GF_BGL_INI* bgl;								//BGL�f�[�^
	GF_BGL_BMPWIN bmpwin[OPENING_BMPWIN_MAX];		//BMP�E�B���h�E�f�[�^

	MSGDATA_MANAGER* msgman;						//���b�Z�[�W�}�l�[�W���[
	WORDSET* wordset;								//�P��Z�b�g
	STRBUF* msg_buf;								//���b�Z�[�W�o�b�t�@�|�C���^
	STRBUF* tmp_buf;								//�e���|�����o�b�t�@�|�C���^
	STRBUF* menu_buf[OPENING_MENU_MAX];				//���j���[�o�b�t�@�|�C���^

	STRCODE str[PERSON_NAME_SIZE + EOM_SIZE];
	PROC* proc;

	CONFIG* config;									//�R���t�B�O�|�C���^
	SAVEDATA* sv;									//�Z�[�u�f�[�^�|�C���^

	u16 count;
	u8 sub_seq;
	u8 msg_index;									//���b�Z�[�Windex

	u8 sex;											//����
	u8 cancel;										//��蒼���t���O
	u8 dmy3;
	u8 dmy4;

	//BMP���j���[(bmp_menu.h)
	BMPMENU_HEADER MenuH;							//BMP���j���[�w�b�_�[
	BMPMENU_WORK * mw;								//BMP���j���[���[�N
	BMPMENU_DATA Data[OPENING_MENU_MAX];			//BMP���j���[�f�[�^
	u32 ret_work;									//�I�������p�����[�^

	fx32 ScaleX;
	fx32 ScaleY;

	OPENING_OBJ_WORK ObjWork;

	PALETTE_FADE_PTR pfd;							//�p���b�g�t�F�[�h

	TCB_PTR	tcb;									//���O���͊Ď�TCB
}OPENING_WORK;


#endif //_OPENING_SYS_H_


