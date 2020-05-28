//============================================================================================
/**
 * @file	world_trade.h
 * @bfief	���E��������
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#ifndef _WORLD_TRADE_H_
#define _WORLD_TRADE_H_

#include "savedata/worldtrade_data.h"
#include "savedata/wifihistory.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"
#include "savedata/record.h"
#include "savedata/system_data.h"
#include "itemtool/myitem.h"


//============================================================================================
//	��`
//============================================================================================

// �v���Z�X��`�f�[�^
extern PROC_RESULT WorldTradeProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WorldTradeProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WorldTradeProc_End ( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��鐢�E�������[�N�\����
typedef struct WORLDTRADE_WORK WORLDTRADE_WORK;	


typedef struct{
	WORLDTRADE_DATA *worldtrade_data;	// ���E�����f�[�^
	SYSTEMDATA		*systemdata;		// �V�X�e���Z�[�u�f�[�^�iDPW���C�u�����p�Ƃ������R�[�h��ۑ��j
	POKEPARTY       *myparty;			// �莝���|�P����
	BOX_DATA        *mybox;				// �{�b�N�X�f�[�^
	ZUKAN_WORK      *zukanwork;			// �}�Ӄf�[�^
	WIFI_LIST		*wifilist;			// �Ƃ������蒠
	WIFI_HISTORY	*wifihistory;		// �n���V�f�[�^
	MYSTATUS		*mystatus;			// �g���[�i�[���
	SAVEDATA		*savedata;			// �Z�[�u�f�[�^�|�C���^
	CONFIG			*config;			// �R���t�B�O�\����
	RECORD			*record;			// ���R�[�h�R�[�i�[�|�C���^
	FNOTE_DATA		*fnote;				// �`���m�[�g�|�C���^
	MYITEM			*myitem;			// �A�C�e���|�P�b�g�|�C���^
	int				zukanmode;			// �}�Ӄ��[�h�i�V���I�E�E�S��)
	int				profileId;			// GameSpy�v���t�@�C��ID
	int				contestflag;		// �R���e�X�g�����Ă邩�t���O
	int				connect;			// ����f�r�h�c���擾�����i1:�擾���Ă��� 0:���������Ă�)

}WORLDTRADE_PARAM;

#endif