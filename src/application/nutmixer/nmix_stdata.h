/**
 *	@file	nmix_stdata.h
 *	@biref	�i�b�c�~�L�T�[�@�풓�f�[�^�\���̒�`
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#ifndef __H_NMIX_STDATA_H__
#define __H_NMIX_STDATA_H__

#include "system/wordset.h"
#include "system/msgdata.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_porutogame1.h"

// �X�s�[�h���ӃR�����g
enum{
	NMIX_STMSG_SPEED_KOGERU00,
	NMIX_STMSG_SPEED_HAYAI00,
	NMIX_STMSG_SPEED_KOGERU01,
	NMIX_STMSG_SPEED_HAYAI01,
	NMIX_STMSG_SPEED_KOGERU02,
	NMIX_STMSG_SPEED_NUM
};

// ���ʔ��\�R�����g
enum{
	NMIX_STMSG_RESULT_COOK_TIME_TI,
	NMIX_STMSG_RESULT_COOK_TIME,
	NMIX_STMSG_RESULT_KOBOSI_NUM_TI,
	NMIX_STMSG_RESULT_KOBOSI_NUM,
	NMIX_STMSG_RESULT_KOGASI_NUM_TI,
	NMIX_STMSG_RESULT_KOGASI_NUM,
	NMIX_STMSG_RESULT_PORUTO_TI,
	NMIX_STMSG_RESULT_PORUTO,
	NMIX_STMSG_RESULT_TEAMWORK_TI,
	NMIX_STMSG_RESULT_TEAMWORK,
	NMIX_STMSG_RESULT_NUM
};


///�풓���b�Z�[�W�f�[�^
typedef struct _NMIXER_MSG{
	MSGDATA_MANAGER *man;	///<�}�l�[�W��
	WORDSET* wset;		///<���[�N
	STRBUF	*tmp;		///<�ėp

	STRBUF	*wait;		///<���̂܂܂��܂���������
	STRBUF	*nuts_in;	///<�؂̎������
	STRBUF	*tr_name;	///<�g���[�i�[��
	
	STRBUF	*casein;	///<�P�[�X�ɂ��܂�
	STRBUF	*replay;	///<���������c�c
	STRBUF	*exit;		///<���~
	STRBUF	*bag_erabu;	///<�o�b�O���炦����
	STRBUF	*poruto_ippai;	///<�|���g�������ς�
	STRBUF	*nuts_none;	///<�؂̎�������܂���
	
	STRBUF	*end;		///<�����
	STRBUF	*result;	///<���ʔ��\ �^�C�g��
	
	STRBUF	*spd[NMIX_STMSG_SPEED_NUM];	///<�X�s�[�h
	STRBUF	*res[NMIX_STMSG_RESULT_NUM];	///<���ʕ\��
}NMIXER_MSG;

#define WORDSET_NMIXER_BUFLEN	(64)

#endif	//__H_NMIX_STDATA_H__
