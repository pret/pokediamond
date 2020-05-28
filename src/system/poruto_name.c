/**
 *	@file	poruto_name.c
 *	@brief	�|���g�̎�ޖ����擾����
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#include "common.h"
#include "gflib/strbuf.h"
#include "system/buflen.h"
#include "system/pm_str.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_porutoname.h"

#include "system/poruto_name.h"

/**
 *	@brief	�|���g���擾�}�l�[�W���쐬
 *
 *	�����p���I�������K�� PorutoName_ReleaseManager()���Ăяo����
 *	�@�̈���J�����Ă�������
 */
PORUTO_NAME_MAN* PorutoName_CreateManager(int heapID)
{
	PORUTO_NAME_MAN *man;
	int i;
	
	man = sys_AllocMemory(heapID,sizeof(PORUTO_NAME_MAN));
	MI_CpuClear8(man,sizeof(PORUTO_NAME_MAN));

	man->pMsgMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);

	//�|���g�����擾���Ă���
	for(i = 0;i < PORUTO_FLAVOR_MAX;i++){
		man->name[i] = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
		MSGMAN_GetString(man->pMsgMan,i,man->name[i]);
	}
	return man;
}

/**
 *	@brief	�|���g���擾�}�l�[�W�����
 */
void PorutoName_ReleaseManager(PORUTO_NAME_MAN* man)
{
	int i;

	for(i = (PORUTO_FLAVOR_MAX-1);i >= 0;i--){
		STRBUF_Delete(man->name[i]);
	}
	MSGMAN_Delete(man->pMsgMan);

	sys_FreeMemoryEz(man);
}

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W���w���)
 *
 *	���\��PORUTO_NAME_STRLEN (20)+EOM_�T�C�Y���̃o�b�t�@���m�ۂ���
 *	  STRBUF�f�[�^�ւ̃|�C���^��n���K�v������
 *	�@�����w��ɂ�BUFLEN_PORUTO_NAME���g�p���Ă��ǂ�
 */
void PorutoName_GetNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,STRBUF* buf)
{
	STRBUF_Clear(buf);
	MSGMAN_GetString(man->pMsgMan,id,buf);
}

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W����STRBUF*���擾)
 *
 *	���}�l�[�W�����[�N���Ɋm�ۂ���Ă���STRBUF�̈�ւ̃|�C���^��Ԃ�
 *	�@�Q�Ƃ͉����ҏW�͕s�I
 */
const STRBUF* PorutoName_GetNameAdrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id)
{
	return (const STRBUF*)man->name[id];
}

/**
 *	@brief	�|���g�t���o�[ID���疼�O��������擾(�}�l�[�W���w��/�������擾��)
 *
 *	��STRBUF�Ƀ��������m�ۂ��ĕԂ��̂ŁA����͎����ł�邱�ƁI
 */
STRBUF* PorutoName_AllocNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,int heapID)
{
	return STRBUF_CreateBufferCopy(man->name[id],heapID);
}

/**
 *	@brief�@�|���g�t���o�[ID���疼�O��������擾(�g���̂�)
 *	
 *	���\��PORUTO_NAME_STRLEN (20)+EOM_�T�C�Y���̃o�b�t�@���m�ۂ���
 *	  STRBUF�f�[�^�ւ̃|�C���^��n���K�v������
 */
void PorutoName_GetNameStrInst(PORUTO_FLAVORID id,STRBUF* buf,int heapID)
{
	MSGDATA_MANAGER *man;

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	
	STRBUF_Clear(buf);
	MSGMAN_GetString(man,id,buf);

	MSGMAN_Delete(man);
}

/**
 *	@brief�@�|���g�t���o�[ID���疼�O��������擾(�g���̂�/�������擾��)
 *	
 *	��STRBUF�Ƀ��������擾���ĕԂ��̂ŁA����͎����ōs�����ƁI
 */
STRBUF* PorutoName_AllocNameStrInst(PORUTO_FLAVORID id,int heapID)
{
	MSGDATA_MANAGER *man;
	STRBUF* buf;
	
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	
	buf = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
	MSGMAN_GetString(man,id,buf);

	STRBUF_Delete(buf);
	MSGMAN_Delete(man);

	return buf;
}

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
void PorutoName_WriteByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,
	GF_BGL_BMPWIN *win,u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back )
{
	GF_STR_PrintColor(	win,font,man->name[id],
						ofsx,ofsy,
						wait,col,call_back);
}

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
void PorutoName_WriteInst(PORUTO_FLAVORID id,int heapID,GF_BGL_BMPWIN *win,
		u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back )
{
	STRBUF *buf;
	MSGDATA_MANAGER *man;

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	

	buf = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
	MSGMAN_GetString(man,id,buf);
	
	GF_STR_PrintColor(	win,font,buf,
						ofsx,ofsy,
						wait,col,call_back);

	STRBUF_Delete(buf);
	MSGMAN_Delete(man);
}
