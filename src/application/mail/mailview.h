/**
 *	@file	mailview.h
 *	@brief	���[���`�惋�[�`���@���[�J���w�b�_
 *	@author	MiyukiIwasawa
 *	@date	06.02.08
 */

#ifndef _H_MAIL_VIEW_H_
#define _H_MAIL_VIEW_H_

typedef enum{
	MAILMODE_CREATE,	///<�쐬����
	MAILMODE_VIEW_D,	///<�f�U�C�����݂�
	MAILMODE_VIEW,		///<�쐬�ς݂̃��[�����݂�
}MAILMODE_ENUM;

enum{
 VIEW_END_LINE0,
 VIEW_END_LINE1,
 VIEW_END_LINE2,
 VIEW_END_DECIDE,
 VIEW_END_CANCEL = 0xFFFF,
};

///���[���f�[�^�e���|����
typedef struct _MAIL_TMP_DATA{
	u16	val;
	u8	cntNo;
	u8	flags;
	CONFIG*	configSave;	///<�R���t�B�O�Z�[�u�f�[�^
	
	u32	writerID;
	u8	sex;
	u8	lang;
	u8	ver;
	u8	design;
	STRBUF	*name;
	MAIL_ICON	icon[MAILDAT_ICONMAX];
	PMS_DATA	msg[MAILDAT_MSGMAX];
}MAIL_TMP_DATA;

extern PROC_RESULT MailViewProc_Init( PROC *proc,int *seq);
extern PROC_RESULT MailViewProc_Main( PROC *proc,int *seq);
extern PROC_RESULT MailViewProc_End( PROC *proc,int *seq);

#endif	//_H_MAIL_VIEW_H_


