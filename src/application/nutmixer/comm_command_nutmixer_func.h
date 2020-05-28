//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		comm_command_nutmixer_func.h
 *	@brief		�ʐM�R�[���o�b�N�֐�
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 * �ʐM�R�[���o�b�N�֐��e�[�u���́A�ʐM�I�[�o�[���C�ɔz�u���܂����A
 * �R�[���o�b�N�֐��́A�~�L�T�[�̃I�[�o���C�̈�ɔz�u����΂悢�̂ŁA
 * �������܂��B
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __COMM_COMMAND_NUTMIXER_FUNC_H__
#define __COMM_COMMAND_NUTMIXER_FUNC_H__

#include "nmix_game.h"

#undef GLOBAL
#ifdef	__COMM_COMMAND_NUTMIXER_FUNC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

// �ʐM�������֐�
extern void CommCommandNutMixerInitialize( NMIX_GAMEWORK* pWork, MYSTATUS* p_mystate );
extern void CommCommandNutMixerDest( NMIX_GAMEWORK* pWork );

	
// ���ʃT�C�Y�擾�֐�
extern int CommNutMixerGetZeroSize( void );
extern int CommNutMixerGetOneSize( void );

//-----------------------------------------------------------------------------
/**
 *
 *		�Q�[���p�R�}���h�R�[���o�b�N�֐�
 *
 */
//-----------------------------------------------------------------------------
// �����p
extern void CommNutMixerGameSysStart( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameEnd( int netID, int size, void* pBuff, void* pWork );

// �f�[�^��M�p
extern void CommNutMixerGameBeforeDataKo( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameBeforeData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameResultData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerPorutoData( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameNextDataKo( int netID, int size, void* pBuff, void* pWork );
extern void CommNutMixerGameNextData( int netID, int size, void* pBuff, void* pWork );

// �T�C�Y�擾�֐�
extern int CommNutMixerGetGameBeforeKoSize( void );
extern int CommNutMixerGetGameBeforeSize( void );
extern int CommNutMixerGetGameSize( void );
extern int CommNutMixerGetGameResultSize( void );



//-----------------------------------------------------------------------------
/**
 *
 *		�ʐM�V�X�e���֐�
 *
 */
//-----------------------------------------------------------------------------



#undef	GLOBAL
#endif		// __COMM_COMMAND_NUTMIXER_FUNC_H__

