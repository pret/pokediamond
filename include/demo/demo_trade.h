//============================================================================================
/**
 * @file	demo_trade.h
 * @brief	�|�P���������f��
 * @author	taya
 * @date	2006.04.07
 */
//============================================================================================
#ifndef __DEMO_TRADE_H__
#define __DEMO_TRADE_H__

#include "system\procsys.h"
#include "poketool\poke_tool.h"
#include "savedata\mystatus.h"
#include "savedata\config.h"

//----------------------------------------------
/**
 * �w�i�^�C�v
 */
//----------------------------------------------
typedef enum {
	DEMO_TRADE_BGTYPE_MORNING,		///< ���`���̐���
	DEMO_TRADE_BGTYPE_EVENING,		///< �[�����̃I�����W��
	DEMO_TRADE_BGTYPE_NIGHT,		///< ��̈Â���
	DEMO_TRADE_BGTYPE_WIFI,			///< WI-FI��p�`���[�u�w�i
}DEMO_TRADE_BGTYPE;

//----------------------------------------------
/**
 * �Đ��V�[�P���X�w��
 */
//----------------------------------------------
typedef enum {
	DEMO_TRADE_SEQ_FULL = 1,			///< �S��
	DEMO_TRADE_SEQ_SEND_ONLY = 2,		///< ���镔������
	DEMO_TRADE_SEQ_RECV_ONLY = 4,		///< �󂯎�镔������
}DEMO_TRADE_SEQFLAG;



//-------------------------------------------------
/**
 *	PROC�p�p�����[�^
 */
//-------------------------------------------------
typedef struct {
	const POKEMON_PASO_PARAM*   sendPoke;	///< �����炩�瑗�����|�P����
	const POKEMON_PASO_PARAM*   recvPoke;	///< �����炩�瑗���Ă����|�P����
	const MYSTATUS*             partner;	///< ��������̃p�����[�^

	DEMO_TRADE_BGTYPE           bgType;		///< �f���w�i�^�C�v
	DEMO_TRADE_SEQFLAG          seqFlag;	///< �Đ��V�[�P���X

	const CONFIG*      config;		///< ���[�U�ݒ�R���t�B�O�f�[�^

}DEMO_TRADE_PARAM;


//-------------------------------------------------
/**
 *	PROC�֐�
 */
//-------------------------------------------------
extern PROC_RESULT TradeDemoProc_Init( PROC * proc, int * seq );
extern PROC_RESULT TradeDemoProc_Quit( PROC * proc, int * seq );
extern PROC_RESULT TradeDemoProc_Main( PROC * proc, int * seq );


//-------------------------------------------------
/**
 *	�I�[�o�[���C�錾
 */
//-------------------------------------------------
FS_EXTERN_OVERLAY(demo_trade);

#endif
