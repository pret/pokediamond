//============================================================================================
/**
 * @file	msgdata.h
 * @brief	�e�탁�b�Z�[�W�f�[�^��舵��
 * @author	taya
 * @date	2005.09.26
 */
//============================================================================================
#ifndef __MSGDATA_H__
#define __MSGDATA_H__

#include "gflib\strbuf.h"
#include "system\arc_tool.h"




/*==========================================================================================*/
/*
 *	�����b�Z�[�W�f�[�^�̍\��
 *
 *    �����̃��b�Z�[�W�f�[�^�t�@�C�����܂Ƃ߂�ꂽ�y�A�[�J�C�u�z����ԑ傫�ȒP�ʂł��B
 *    ����� nnsarc �ō쐬�����ʏ�̃A�[�J�C�u�t�@�C���ł��B
 *    ���b�Z�[�W�f�[�^�͕K���A�[�J�C�u���Ďg���܂��B
 *
 *
 *    �y�A�[�J�C�u�z�̒��ɂ͂������́y���b�Z�[�W�f�[�^�z���܂Ƃ߂��Ă��܂��B
 *    ����� MessageEditor �̃f�[�^���R���o�[�g�������̂ŁA�f�e�Ǝ��d�l�ł��B
 *
 *
 *    ����Ɂy���b�Z�[�W�f�[�^�z�̒��ɂ͂������́y������z�����݂��܂��B
 *    �܂�A�v���P�[�V��������K�v�ȁy������z���擾���邽�߂ɂ́A
 *    �A�[�J�C�u�h�c�C���b�Z�[�W�f�[�^�h�c�A������h�c�̂R�̃L�[���K�v�Ƃ������ƂɂȂ�܂��B
 *
 *
 *	�����b�Z�[�W�f�[�^�̎�舵�����@
 *
 *    ���b�Z�[�W�f�[�^�̎�舵���C���^�[�t�F�C�X�͂Q��ނ���܂��B
 *
 *    �`�D�y���b�Z�[�W�f�[�^�z�S�̂�RAM��Ƀ��[�h���Ă����A��������K�v�ɉ�����
 *        �y������z�����[�J���̃o�b�t�@�ɃR�s�[���Ďg���B
 *          �s�v�ɂȂ�����y���b�Z�[�W�f�[�^�z��j������B
 *
 *    �a�D�y������z���K�v�ɂȂ邽�тɁA���́y������z������RAM��Ƀ��[�h����B
 *         ���[�J���o�b�t�@�ɃR�s�[�����瑦���Ƀ��[�h�̈�͔j������B
 *
 *    �`�������ƁA��R�́y������z����Ȃ�y���b�Z�[�W�f�[�^�z����舵���ꍇ�ɁA
 *    ����������10�o�C�g���x�́y������z���~���������Ȃ̂ɁA����o�C�g�́y���b�Z�[�W�f�[�^�z��
 *    ���[�h���邱�ƂɂȂ�\��������܂��B
 *
 *   �i�Ⴆ�ΑS�|�P���������P�́y���b�Z�[�W�f�[�^�z�ɂȂ��Ă���ꍇ�A�P�����Q�o�C�g�Ȃ̂�
 *     �傴���ς�500�̕��Ƃ���� 500 * 5 * 2 �� 5000 �o�C�g�B���[�J���C�Y���Ƀ|�P��������
 *     �{�ɐL�т��10000�o�C�g�ł��j
 *
 *    �ꍇ�ɂ���ẮA����ق��ґ�Ƀ��������g���Ȃ��P�[�X�Ƃ����̂����邩������܂���B
 *    ���̏ꍇ�͂a�������g���Ă��������B
 *
 *    ������������͕�����擾�̂��тɃt�@�C�����[�h�A�������m�ہ�������s���̂ŁA
 *    �����́y������z���擾����ꍇ�ɂ͎��s���x���]���ɂȂ�܂��B
 *
 *
 *	�����b�Z�[�W�f�[�^�}�l�[�W���ɂ���
 *
 *    ��L�`�E�a�̃C���^�[�t�F�C�X�����z�����A�A�v�����x���ł̏C�����ȒP�ɂ��邽�߂�
 *    �}�l�[�W����p�ӂ��܂����B���̃}�l�[�W������ă��b�Z�[�W�f�[�^����舵�����ƂŁA
 *    �`��������a�����ɕς������i���邢�͂��̋t�j�Ƃ����ꍇ�ɁA�A�v���P�[�V�����v��
 *    �O�������̂��قڕύX�����Ɏ����ł��܂��B�ڍׂ̓}�l�[�W���֐��̐������������������B
 *
 *
/*==========================================================================================*/




//----------------------------------------------------
/**
 *  �}�l�[�W���^�C�v��`
 */
//----------------------------------------------------
typedef enum {
	MSGMAN_TYPE_NORMAL,		///< �`�����BRAM��ɕK�v�ȃf�[�^��ێ���������̂ō���������������H���B
	MSGMAN_TYPE_DIRECT,		///< �a�����B������擾���ƂɕK�v�Œ�������������m�ہ�����B�ȃ����������x���B
}MSGMAN_TYPE;

//----------------------------------------------------
/**
 *  �}�l�[�W�����[�N�\���̂̌^�錾
 */
//----------------------------------------------------
typedef struct _MSGDATA_MANAGER	MSGDATA_MANAGER;

//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W���쐬
 *
 * ��������ς������ꍇ�A���̊֐��� type ������ς��邾���ŗǂ��B
 *
 *
 * @param   type		�}�l�[�W���^�C�v�w��
 * @param   arcID		���b�Z�[�W�f�[�^�̊܂܂��A�[�J�C�u�h�c
 * @param   datID		���b�Z�[�W�f�[�^�{�̂̃A�[�J�C�u���h�c
 * @param   heapID		�������m�ۗp�q�[�v�h�c
 *
 * @retval  MSGDATA_MANAGER*		�쐬�����}�l�[�W�����[�N�|�C���^
 */
//------------------------------------------------------------------
extern MSGDATA_MANAGER*  MSGMAN_Create( MSGMAN_TYPE type, u32 arcID, u32 datID, u32 heapID );


//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W���̔j��
 *
 * @param   man		�}�l�[�W�����[�N�|�C���^
 *
 */
//------------------------------------------------------------------
extern void MSGMAN_Delete( MSGDATA_MANAGER* man );



//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������擾
 * �i�w��o�b�t�@�ɃR�s�[�j
 *
 * @param   man		�}�l�[�W�����[�N�|�C���^
 * @param   strID	������h�c
 * @param   dst		������R�s�[��o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void MSGMAN_GetString( const MSGDATA_MANAGER* man, u32 strID, STRBUF* dst );


//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^�}�l�[�W�����g���ĕ�������擾
 *�i������STRBUF���쐬���ĕԂ��B�쐬���ꂽSTRBUF�̔j���͊e���ōs���j
 *
 * @param   man			�}�l�[�W�����[�N�|�C���^
 * @param   strID		������ID
 *
 * @retval  STRBUF*		�R�s�[��o�b�t�@�|�C���^
 */
//------------------------------------------------------------------
extern	STRBUF* MSGMAN_AllocString( const MSGDATA_MANAGER* man, u32 strID );


//------------------------------------------------------------------
/**
 * �i�[����Ă��郁�b�Z�[�W����Ԃ�
 *
 * @param   man		�}�l�[�W�����[�N�|�C���^
 *
 * @retval  u32		���b�Z�[�W��
 */
//------------------------------------------------------------------
extern u32 MSGMAN_GetMessageCount( const MSGDATA_MANAGER* man );






//------------------------------------------------------
/**
 *  ���b�Z�[�W�f�[�^�w�b�_
 */
//------------------------------------------------------
typedef struct _MSGDATA_HEADER	MSGDATA_HEADER;


extern MSGDATA_HEADER* MSGDAT_Load( u32 arcID, u32 datID, u32 heapID );
extern void MSGDAT_Unload( MSGDATA_HEADER* msgdat );
extern void MSGDAT_GetStr( const MSGDATA_HEADER* msgdat, u32 strID, STRBUF* dst );
extern STRBUF* MSGDAT_GetStrAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID );
extern void MSGDAT_GetStrDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRBUF* dst );
extern STRBUF* MSGDAT_GetStrDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID );
extern u32 MSGDAT_GetMessageCount( const MSGDATA_HEADER* msgdat );
extern u32 MSGDAT_GetMessageCountDirect( u32 arcID, u32 datID );
extern STRBUF* MSGDAT_GetStrDirectAllocByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID );
extern void MSGDAT_GetStrDirectByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID, STRBUF* dst );


//====================================================================================
// ��������͋��ŁB����������̂Ŏg��Ȃ��ł�
//====================================================================================
extern void MSGMAN_GetStr( const MSGDATA_MANAGER* man, u32 strID, STRCODE* dst );
extern STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID );
extern void MSGDAT_Get( const MSGDATA_HEADER* msgdat, u32 strID, STRCODE* dst );
extern STRCODE* MSGDAT_GetAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID );
extern void MSGDAT_GetDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRCODE* dst );
extern STRCODE* MSGDAT_GetDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID );
extern STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID );
extern void MSGDAT_MonsNameGet( u32 monsno, u32 heapID, STRCODE* dst );


#endif
