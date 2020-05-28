/**
 *	@file	mail_def.h
 *	@brief	���[���f�[�^�@�萔��`�t�@�C��
 *	@author	Miyuki Iwasawa
 *	@date	06.02.09
 */

#ifndef __H_MAIL_DEF_H__
#define __H_MAIL_DEF_H__

#if 0
#define MAIL_STOCK_TEMOTI	(6)		///<�莝���Žį����Ă����鐔
#define MAIL_STOCK_EXTRADE	(1)		///<���E����
#define MAIL_STOCK_SODATEYA	(2)		///<��ĉ����[��
#define MAIL_STOCK_MAX	(	MAIL_STOCK_TEMOTI+\
							MAIL_STOCK_PASOCOM+\
							MAIL_STOCK_EXTRADE+\
							MAIL_STOCK_SODATEYA)
#endif
#define MAIL_STOCK_PASOCOM	(20)	///<�߿�݂Žį����Ēu���鐔
#define MAIL_STOCK_MAX	(MAIL_STOCK_PASOCOM)

#define MAILDAT_MSGMAX	(3)	///<�ȈՕ��v�f��
#define MAILDAT_ICONMAX	(3)	///<�|�P�����A�C�R���v�f��

///�f�[�^�u���b�N�A�N�Z�XID��`
typedef enum{
 MAILBLOCK_PASOCOM,
 MAILBLOCK_MAX,
 MAILBLOCK_TEMOTI,	///<�u���b�N�O�f�[�^ID(�莝��)
// MAILBLOCK_EXTRADE,	///<�u���b�N�O�f�[�^ID(���E����)
// MAILBLOCK_SODATEYA,///<�u���b�N�O�f�[�^ID(��Ă⃁�[��)
 MAILBLOCK_NULL,	///<�u���b�N�O�f�[�^ID(����ID)
}MAILBLOCK_ID;

///�f�U�C��No��`
typedef enum{
 MAIL_DESIGN_START = 0,
 MAIL_DESIGN_00 = 0,
 MAIL_DESIGN_01,
 MAIL_DESIGN_02,
 MAIL_DESIGN_03,
 MAIL_DESIGN_04,
 MAIL_DESIGN_05,
 MAIL_DESIGN_06,
 MAIL_DESIGN_07,
 MAIL_DESIGN_08,
 MAIL_DESIGN_09,
 MAIL_DESIGN_10,
 MAIL_DESIGN_11,
 MAIL_DESIGN_END = 11,
 MAIL_DESIGN_MAX,
 MAIL_DESIGN_NULL = 0xFFFF,	///<����
}MAIL_DESIGN_NO;

#define MAILDATA_NULLID	(0xFFFFFFFF)
#define MAIL_ICON_NULL	(0xFFFF)
#define MAIL_ICON_CGXN	(0xFFF)
#define MAIL_ICON_PALNULL	(0xF)

///���[���|�P�����A�C�R���f�[�^�^
typedef union _MAIL_ICON{
	struct{
		u16	cgxID:12;	///<�|�P�����A�C�R���L�����N�^CgxID
		u16	palID:4;	///<�|�P�����A�C�R���p���b�gID
	};
	u16	dat;
}MAIL_ICON;

#define MAIL_ICONPRM_CGX	(0)
#define MAIL_ICONPRM_PAL	(1)
#define MAIL_ICONPRM_ALL	(2)

#endif	//__H_MAIL_DEF_H__


