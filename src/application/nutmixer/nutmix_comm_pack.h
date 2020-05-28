//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nutmix_comm_pack.h
 *	@brief		�ʐMPACKAGE�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NUTMIX_COMM_PACK_H__
#define __NUTMIX_COMM_PACK_H__

#include "communication/communication.h"

#undef GLOBAL
#ifdef	__NUTMIX_COMM_PACK_H_GLOBAL
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
//	�ʐM�p�b�N�t���O
//=====================================
#define NUTMIX_COMM_PACK_ONE	( 0 )	// ��l�p
#define NUTMIX_COMM_PACK_COMM	( 1 )	// �ʐM

//-------------------------------------
//	�_�~�[�R�[���o�b�N���[�N��
//=====================================
#define NUTMIX_COMM_PACK_DUMMY_WORK_NUM	( 8 )

//-------------------------------------
//	�_�~�[�R�[���o�b�N�@�V�X�e��TCB�@
//	VWAIT�^�X�N�D�揇��
//=====================================
//�o���邾���AVWAIT�̈�ԍŌ�ɂ�����
#define NUTMIX_COMM_PACK_DUMMY_TCB_PRI	( 5000 )

//-------------------------------------
//	�_�~�[�R�[���o�b�N�̂Ƃ���
//	�ڑ�ID�i�_�~�[�j
//=====================================
#define NUTMIX_COMM_PACK_DUMMY_NETID	( COMM_PARENT_ID )




//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
// �p�b�N�V�X�e�����[�N
typedef struct _NUTMIX_COMMPACK_WORK NUTMIX_COMMPACK_WORK;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL NUTMIX_COMMPACK_WORK* NMIX_CommPack_CommandInitialize( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int comm_flg, int heapID );
GLOBAL BOOL NMIX_CommPack_CommSendData( int command, const void* data, int size, NUTMIX_COMMPACK_WORK* p_sys );
GLOBAL void NMIX_CommPack_CommDelete( NUTMIX_COMMPACK_WORK* p_sys );

GLOBAL int NMIX_CommPack_CommGetCurrentID( NUTMIX_COMMPACK_WORK* p_sys );
GLOBAL BOOL NMIX_CommPack_CommIsConnect( NUTMIX_COMMPACK_WORK* p_sys, u16 netID );


#undef	GLOBAL
#endif		// __NUTMIX_COMM_PACK_H__

