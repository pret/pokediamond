//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade.h
 *	@brief		�Q�[��������
 *	@author		tomoya takahashi
 *	@data		2006.05.15
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_TRADE_H__
#define __FIELD_TRADE_H__

//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_
#include "include/demo/demo_trade.h"
#endif // __ASM_NO_DEF_

#undef GLOBAL
#ifdef	__FIELD_TRADE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�����f�[�^�i���o�[
//=====================================
#define	FLD_TRADE_KEESHI	(0)
#define	FLD_TRADE_PERAPPU	(1)
#define	FLD_TRADE_GHOST		(2)
#define	FLD_TRADE_KOIKING	(3)
#define	FLD_TRADE_NUM		(4)

//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
typedef struct _FLD_TRADE_WORK FLD_TRADE_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *
 *		����
 *			FLD_TRADE_WORK*  ���A���b�N���Ă��������
 *			���̊֐��Ńf�[�^���擾�ł��܂��B
 *	GLOBAL u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work );
 * 	GLOBAL u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work );
 *	GLOBAL u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work );
 *
 *			��������|�P���������܂�����
 *			EventCmd_FldTrade���R�[�����Ă��������B(field_trade_cmd.h)
 *			
 *			�������I��������
 *			FLD_TRADE_WORK*��j�����Ă�������
 *
 */
//-----------------------------------------------------------------------------

GLOBAL FLD_TRADE_WORK* FLD_TradeAlloc( u32 heapID, u32 trade_no );
GLOBAL void FLD_TradeDelete( FLD_TRADE_WORK* p_work ); 

// �����f�[�^�擾�֌W
GLOBAL u32 FLD_TradeMonsno( const FLD_TRADE_WORK* cp_work );	// ���������|�P�����i���o�[
GLOBAL u32 FLD_TradeChangeMonsno( const FLD_TRADE_WORK* cp_work );	// �����ɕK�v�ȃ|�P�����i���o�[
GLOBAL u32 FLD_TradeOyaSex( const FLD_TRADE_WORK* cp_work );	// �e�̐���


// �����̎��s
GLOBAL void FLD_Trade( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos );
// �f���f�[�^�쐬
GLOBAL void FLD_TradeDemoDataMake( FIELDSYS_WORK * p_fsys, FLD_TRADE_WORK* p_work, int party_pos, DEMO_TRADE_PARAM* p_demo, POKEMON_PARAM* sendPoke, POKEMON_PARAM* recvPoke );

#endif	__ASM_NO_DEF_

#undef	GLOBAL
#endif		// __FIELD_TRADE_H__

