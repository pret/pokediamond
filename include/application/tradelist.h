//============================================================================================
/**
 * @file	tradelist.h
 * @bfief	�|�P�����������X�g���
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================
#ifndef _TRADELIST_H_
#define _TRADELIST_H_


//============================================================================================
//	�萔��`
//============================================================================================
#include "savedata/friendlist.h"
#include "savedata/wifihistory.h"
#include "savedata/config.h"
#include "savedata/zukanwork.h"
#include "savedata/fnote_mem.h"
#include "savedata/record.h"


#define TRADELIST_END_FINISH  ( 0 )				// ��������߂ďI������
#define TRADELIST_END_DEMO    ( 1 )				// �����𐬗������ăf���ɂ���

// �������X�g�ɍs���Ƃ��ɓn���p�����[�^�\����
typedef struct {
	FIELDSYS_WORK *fsys;
	MYSTATUS      *mystatus;
	POKEPARTY     *myparty;
	FRIEND_LIST   *friendlist;
	SAVEDATA      *savedata;
	WIFI_HISTORY  *wifihistory;
	CONFIG		  *config;			// �R���t�B�O�\����
	FNOTE_DATA	  *fnote;			// �`���m�[�g�|�C���^
	RECORD		  *record;			// ���R�[�h�|�C���^
	ZUKAN_WORK    *zukanwork;		// �}�Ӄf�[�^
	int			  result;			// �������X�g����̕Ԃ�l 
									// TRADELIST_END_FINISH = ��������߂�
									// TRADELIST_END_DEMO   = �����f����
	int			  exchangepos;		// ���������|�P�����̈ʒu

	int			  zukanmode;		// �}�Ӄ��[�h�i�V���I�E�E�S��)
	int			  times;

	// �f����ʗp�p�����[�^�i�|�C���^�󂯓n���ł͂Ȃ��A���̗p�̈���m�ۂ��Ă���̂ŃR�s�[����j
	MYSTATUS*			result_partner;
	POKEMON_PARAM*		result_sendPoke;
	POKEMON_PARAM*		result_recvPoke;

}TRADELIST_PARAM;



typedef struct TRADELIST_WORK TRADELIST_WORK;	// �|�P����������ʃ��[�N�\���́i�|�C���^�Q�Ƃ����ł���j


extern PROC_RESULT TradeListProc_Init( PROC * proc, int * seq );
extern PROC_RESULT TradeListProc_Main( PROC * proc, int * seq );
extern PROC_RESULT TradeListProc_End( PROC * proc, int * seq );



#endif //_TRADELIST_DEF_H_
