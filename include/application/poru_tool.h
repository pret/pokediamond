/**
 *	@file	poru_tool.h
 *	@brief	�|���g�c�[��
 *	@author	Miyuki Iwasawa
 *	@date	06.03.14
 */

#ifndef __H_PORU_TOOL_H__
#define __H_PORU_TOOL_H__

#include "savedata/savedata_def.h"
#include "savedata/poruto_util.h"
#include "savedata/mystatus.h"
#include "system/gamedata.h"
#include "itemtool/myitem.h"
#include "poketool/pokeparty.h"
#include "application/p_status.h"
#include "application/pokelist.h"

typedef enum{
 PORU_FAVOLITE_SUKI,	///<�D��
 PORU_FAVOLITE_KIRAI,	///<�L���C
 PORU_FAVOLITE_NRM,		///<����
}PORU_FAVOLITE;

///�|���g�f�[�^���X�g�\��
typedef struct _PORU_LIST{
	u8	id;			///�f�[�^ID
	u8	level;		///<�|���g�̃��x��
	u8	flavor;		///<�|���g�̎��
	u8	taste;		///<�Ȃ߂炩��

	union{
		struct{
		u8	spicy:1;	///<�����Ă��閡
		u8	astr:1;
		u8	sweet:1;
		u8	bitter:1;
		u8	sour:1;
		u8	view:1;	///<�`��t���O
		u8	del:1;		///<�폜�t���O
		u8	valid:1;	///<�L��/�����t���O
		};
		u8 flags;
	};
	u8	myid;
	u8	prev;
	u8	next;

//	STRBUF	*lvbuf;
}PORU_LIST;

///�|���g�Ăяo�����[�N
typedef struct _PORUTO_PARAM{
	u8		porunum;	///<�Ăяo�����̃|���g�̐�
	u8		selID;
	u8		ret_mode;	///<���^�[���l
	u8		ret_view;	///<���^�[��view���[�h
	u16		listPos;	///<�������X�g�|�W�V����
	u16		curPos;		///<�����J�[�\���|�W�V����
	
	PORUTO_BLOCK* poruSave;	///<�|���g�Z�[�u�f�[�^
	MYSTATUS	*mySave;	///<�X�e�[�^�X
	POKEPARTY	*ppSave;	///<�|�P�p�[�e�B
	MYITEM		*itemSave;	///<�A�C�e��
	CONFIG		*configSave;	///<�R���t�B�O

	PORU_LIST	list[PORUTO_STOCK_MAX];	///<����f�[�^��
}PORUTO_PARAM;

///�I�[�o�[���C�v���Z�X�O���Q�Ɛ錾
extern const PROC_DATA PorutoSysProcData;

/**
 *	@brief	�|���g�V�X�e���Ăяo�����[�N�f�[�^�쐬
 *
 *	���K�� PorutoSys_ReleaseCallWork()�֐��ŉ�����邱�ƁI
 */
extern PORUTO_PARAM* PorutoSys_CreateCallWork(SAVEDATA* savedata,int heapID);

/**
 *	@brief	�|���g�P�[�X�Ăяo�����[�N���������
 */
extern void PorutoSys_ReleaseCallWork(PORUTO_PARAM* pp);

/**
 *	@brief	�|���g�f�[�^�Ɛ��i���炻�̃|���g���D�����������Ԃ�
 */
extern PORU_FAVOLITE PoruSys_IsFavolite(PORUTO_DATA *dat,u8 seikaku);

/**
 *	@brief	�|���g�p�����[�^���|�P�����p�����[�^��Push����
 */
extern void PoruSys_PoruPara2Poke(PORUTO_DATA* dat,POKEMON_PARAM* poke);

/**
 *	@brief	���i����ǂ̖����D�����������Ԃ�
 *
 *	@param	�|�P�����̐��iNo
 *	@param	mode	PORU_FAVOLITE_SUKI:�D���Ȗ��^�C�v��Ԃ�
 *					PORU_FAVOLITE_KIRAI:�L���C�Ȗ��^�C�v��Ԃ�
 *
 *	@retval	PORUTO_FTYPE_SPICY	�h��
 *	@retval	PORUTO_FTYPE_ASTR	���Ԃ�
 *	@retval	PORUTO_FTYPE_SWEET	���܂�
 *	@retval	PORUTO_FTYPE_BITTER	�ꂢ
 *	@retval	PORUTO_FTYPE_SOUR	�����ς�
 *	@retval	PORUTO_FTYPE_MIX	�D���������Ȃ�
 */
extern u8	PoruSys_GetFavolite(u8 seikaku,PORU_FAVOLITE mode);



#endif	//__H_PORU_TOOL_H__

