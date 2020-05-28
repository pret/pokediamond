/**
 *	@file	poruto_name.c
 *	@brief	�|���g�̎�ޖ����擾����c�[���Q
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#ifndef __H_PORUTO_NAME_H__
#define __H_PORUTO_NAME_H__

#include "gflib/msg_print.h"
#include "gflib/bg_system.h"
#include "system/msgdata.h"
#include "savedata/poruto_def.h"

///�|���g���擾�}�l�[�W���[�^
typedef struct _PORUTO_NAME_MAN{
	MSGDATA_MANAGER* pMsgMan;
	STRBUF	*name[PORUTO_FLAVOR_MAX];	
}PORUTO_NAME_MAN;

/**
 *	@brief	�|���g���擾�}�l�[�W���쐬
 *
 *	�����p���I�������K�� PorutoName_ReleaseManager()���Ăяo����
 *	�@�̈���J�����Ă�������
 */
extern PORUTO_NAME_MAN* PorutoName_CreateManager(int heapID);

/**
 *	@brief	�|���g���擾�}�l�[�W�����
 */
extern void PorutoName_ReleaseManager(PORUTO_NAME_MAN* man);

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W���w���)
 *
 *	��PORUTO_NAME_STRLEN (10)+EOM_�T�C�Y���̃o�b�t�@���m�ۂ���K�v�L��
 *	�@BUFLEN_PORUTO_NAME���g�p���Ă��ǂ�
 */
extern void PorutoName_GetNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,STRBUF* buf);

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W����STRBUF*���擾)
 *
 *	���}�l�[�W�����[�N���Ɋm�ۂ���Ă���STRBUF�̈�ւ̃|�C���^��Ԃ�
 *	�@�Q�Ƃ͉����ҏW�͕s�I
 */
extern const STRBUF* PorutoName_GetNameAdrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id);

/**
 *	@brief�@�|���g�t���o�[ID���疼�O��������擾(�g���̂�)
 */
extern void PorutoName_GetNameStrInst(PORUTO_FLAVORID id,STRBUF* buf,int heapID);

/**
 *
 *	@brief�@�|���g�t���o�[ID���疼�O��������擾(�g���̂�/�������擾��)
 *	
 *	��STRBUF�Ƀ��������擾���ĕԂ��̂ŁA����͎����ōs�����ƁI
 */
extern STRBUF* PorutoName_AllocNameStrInst(PORUTO_FLAVORID id,int heapID);

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W���w��/�������擾��)
 *
 *	��STRBUF�Ƀ��������m�ۂ��ĕԂ��̂ŁA����͎����ł�邱�ƁI
 */
extern STRBUF* PorutoName_AllocNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,int heapID);

/**
 *	@brief	�|���g�t���o�[ID���w�肵�Ė��O�������`��(�}�l�[�W���w���)
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	fnt_index	�g�p�����w�b�_INDEX(msg_print.h �Q��)
 * @param	x			�E�C���h�E���\���J�nX�I�t�Z�b�g
 * @param	y			�E�C���h�E���\���J�nY�I�t�Z�b�g
 * @param	wait		�����`��E�F�C�g
 * @param	call_back	�����`�悲�Ƃ̃R�[���o�b�N�֐�
 *
 * @return	���b�Z�[�W�C���f�b�N�X
 *
 * call_back �ݒ�Ɋւ��āA���̊֐�����̈����� 
 *   MSG_PRINT_HEADER �\����(msg_print.h ���Q��)�|�C���^
 * �ƂȂ�
 *
 * wait �ݒ��
 *   MSG_NOTRANS	�f�B�X�v���C�]���Ȃ�
 *�@ MSG_ALL		�f�B�X�v���C�ꊇ�]��
 *   1 �`			�P�������Ƃ̓]���E�F�C�g�l
 * �Ŏw��(msg_print.h ��`)
 */
extern void PorutoName_WriteByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,
	GF_BGL_BMPWIN *win,u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back );

/**
 *	@brief	�|���g�t���o�[ID���w�肵�Ė��O�������`��(�g���̂�)
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	fnt_index	�g�p�����w�b�_INDEX(msg_print.h �Q��)
 * @param	x			�E�C���h�E���\���J�nX�I�t�Z�b�g
 * @param	y			�E�C���h�E���\���J�nY�I�t�Z�b�g
 * @param	wait		�����`��E�F�C�g
 * @param	call_back	�����`�悲�Ƃ̃R�[���o�b�N�֐�
 *
 * @return	���b�Z�[�W�C���f�b�N�X
 *
 * call_back �ݒ�Ɋւ��āA���̊֐�����̈����� 
 *   MSG_PRINT_HEADER �\����(msg_print.h ���Q��)�|�C���^
 * �ƂȂ�
 *
 * wait �ݒ��
 *   MSG_NOTRANS	�f�B�X�v���C�]���Ȃ�
 *�@ MSG_ALL		�f�B�X�v���C�ꊇ�]��
 *   1 �`			�P�������Ƃ̓]���E�F�C�g�l
 * �Ŏw��(msg_print.h ��`)
 */
extern void PorutoName_WriteInst(PORUTO_FLAVORID id,int heapID,GF_BGL_BMPWIN *win,
		u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back );






#endif	//__H_PORUTO_NAME_H__
