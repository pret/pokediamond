/**
 *	@file	mailview.h
 *	@brief	メール描画ルーチン　ローカルヘッダ
 *	@author	MiyukiIwasawa
 *	@date	06.02.08
 */

#ifndef _H_MAIL_VIEW_H_
#define _H_MAIL_VIEW_H_

typedef enum{
	MAILMODE_CREATE,	///<作成する
	MAILMODE_VIEW_D,	///<デザインをみる
	MAILMODE_VIEW,		///<作成済みのメールをみる
}MAILMODE_ENUM;

enum{
 VIEW_END_LINE0,
 VIEW_END_LINE1,
 VIEW_END_LINE2,
 VIEW_END_DECIDE,
 VIEW_END_CANCEL = 0xFFFF,
};

///メールデータテンポラリ
typedef struct _MAIL_TMP_DATA{
	u16	val;
	u8	cntNo;
	u8	flags;
	CONFIG*	configSave;	///<コンフィグセーブデータ
	
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


