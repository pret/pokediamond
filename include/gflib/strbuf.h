//=============================================================================================
/**
 * @file	strbuf.h
 * @brief	�ėp������o�b�t�@�^�I�u�W�F�N�g
 * @author	taya
 * @date	2005.11.02
 */
//=============================================================================================
#ifndef __STRBUF_H__
#define __STRBUF_H__

#include "number_str.h"



typedef struct _STRBUF	STRBUF;


//------------------------------------------------------------------
/**
 * ������o�b�t�@�I�u�W�F�N�g�쐬
 *
 * @param   size		�i�[�ł��镶�����iEOM���܂ށj
 * @param   heapID		�쐬��q�[�vID
 *
 * @retval  STRBUF*		�I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
extern STRBUF* STRBUF_Create( u32 size, u32 heapID );


//------------------------------------------------------------------
/**
 * ������o�b�t�@�I�u�W�F�N�g�폜
 *
 * @param   strbuf		�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
extern void STRBUF_Delete( STRBUF* strbuf );


//------------------------------------------------------------------
/**
 * ���e���N���A���ċ󕶎���ɂ���
 * �iCreate ����̓N���A����Ă���̂ŌĂԕK�v�͖����j
 *
 * @param   strbuf		�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
extern void STRBUF_Clear( STRBUF* strbuf );


//------------------------------------------------------------------
/**
 * �o�b�t�@�Ԃ̕�����R�s�[
 *
 * @param   dst		�R�s�[��o�b�t�@�I�u�W�F�N�g
 * @param   src		�R�s�[���o�b�t�@�I�u�W�F�N�g
 *
 */
//------------------------------------------------------------------
extern void STRBUF_Copy( STRBUF* dst, const STRBUF* src );

//------------------------------------------------------------------
/**
 * �������e�̃o�b�t�@�𕡐�����
 *
 * @param   strbuf		�������̃o�b�t�@�I�u�W�F�N�g
 *
 * @retval  STRBUF*		�������ꂽ�o�b�t�@�I�u�W�F�N�g
 */
//------------------------------------------------------------------
extern STRBUF* STRBUF_CreateBufferCopy( const STRBUF* origin, u32 heapID );

//------------------------------------------------------------------
/**
 * ���l�𕶎��񉻂��ăo�b�t�@�ɃZ�b�g����
 *
 * @param   dst			�I�u�W�F�N�g�ւ̃|�C���^
 * @param   number		���l
 * @param   keta		�ő包��
 * @param   dispType	�\���^�C�v
 * @param   codeType	�����R�[�h�^�C�v
 *
 */
//------------------------------------------------------------------
extern void STRBUF_SetNumber( STRBUF* dst, int number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType );

//------------------------------------------------------------------
/**
 * ���������𐔎��ɕϊ�����  18�����Ή�  ���̊֐��͕����R�[�h�ɍ��E�����
 *
 * @param   src			�ϊ������������������Ă���o�b�t�@
 * @param   pNumber     �ϊ����I���������
 * @return  ���������ꍇTRUE
 *
 */
//------------------------------------------------------------------

extern u64 STRBUF_GetNumber( const STRBUF* src, BOOL* pbFlag  );

//------------------------------------------------------------------
/**
 * ��������r����
 *
 * @param   str1		������P
 * @param   str2		������Q
 *
 * @retval  int			"0 = ��v"
 * @retval  int			"1 = �s��v"
 */
//------------------------------------------------------------------
extern int STRBUF_Compare( const STRBUF* str1, const STRBUF* str2 );

//------------------------------------------------------------------
/**
 * �i�[����Ă��镶������Ԃ�
 *
 * @param   strbuf		������o�b�t�@�I�u�W�F�N�g
 *
 * @retval  u32		������
 */
//------------------------------------------------------------------
extern u32 STRBUF_GetLen( const STRBUF* strbuf );

//------------------------------------------------------------------
/**
 * �i�[����Ă��镶���񂪉��s���邩�𒲂ׂ�
 *
 * @param   strbuf		������o�b�t�@�I�u�W�F�N�g
 *
 * @retval  u32		������̍s��
 */
//------------------------------------------------------------------
extern u32 STRBUF_GetLines( const STRBUF* strbuf );

//------------------------------------------------------------------
/**
 * ������́A�w��s�݂̂�ʃo�b�t�@�փR�s�[����
 *
 * @param   dst		�R�s�[��o�b�t�@
 * @param   src		�R�s�[���o�b�t�@
 * @param   line	�s�ԍ��i0 origin�j
 *
 */
//------------------------------------------------------------------
extern void STRBUF_CopyLine( STRBUF* dst, const STRBUF* src, u32 line );



//==========================================================================================
// �f�o�b�O�p
//==========================================================================================
#ifdef PM_DEBUG
extern BOOL STRBUF_CheckValid(const void* ptr);
//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ��i�P�U�i�j�f�o�b�O��p
 *
 * @param   dst			[out] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   number		���l
 * @param   keta		�ő包��
 * @param   dispType	�\���^�C�v
 * @param   codeType	�����R�[�h�^�C�v
 *
 * @return	none
 *
 * @li	type = NUMBER_DISPTYPE_LEFT		���l
 * @li	type = NUMBER_DISPTYPE_SPACE	�E�l�A����Ȃ������͋�
 * @li	type = NUMBER_DISPTYPE_ZERO		�E�l�A����Ȃ������͐����̃[��
 */
//--------------------------------------------------------------------------------------------
extern void STRBUF_SetHexNumber(STRBUF* dst, int num, u32 keta,
								NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType );
#endif



#endif
