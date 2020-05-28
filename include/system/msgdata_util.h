//============================================================================================
/**
 * @file	msgdata_util.h
 * @brief	���b�Z�[�W�f�[�^�֘A�֗��֐�
 * @author	taya
 * @date	2005.12.05
 */
//============================================================================================
#ifndef __MSGDATA_UTIL_H__
#define __MSGDATA_UTIL_H__

#include "gflib/strbuf.h"
#include "system/msgdata.h"
#include "system/wordset.h"


//------------------------------------------------------------------
/**
 * ���b�Z�[�W�f�[�^���^�O�W�J����������o�b�t�@���쐬���ĕԂ��B
 * ���O�Ɍʂ̃^�O�ݒ菈�����s���Ă����K�v������B
 * �쐬���ꂽ������̉�������͊e���ōs���B
 *
 * @param   wordSet		�^�O���ݒ肳�ꂽ�P��Z�b�g���W���[��
 * @param   msgMan		�W�J�O��������Ǘ����Ă��郁�b�Z�[�W�}�l�[�W��
 * @param   strID		�W�J�O�������ID
 * @param   heapID		������o�b�t�@�쐬��̃q�[�vID
 *
 * @retval  STRBUF*		�쐬���ꂽ������o�b�t�@
 */
//------------------------------------------------------------------
extern STRBUF* MSGDAT_UTIL_AllocExpandString( WORDSET* wordSet, MSGDATA_MANAGER* msgMan, u32 strID, u32 heapID );


//------------------------------------------------------------------
/**
 * ���U����������A�V�K�ɍ쐬����������o�b�t�@�ɃR�s�[���ĕԂ�
 * �i������o�b�t�@�̍폜�͊e���ōs���j
 *
 * @param   wazaID		���U�h�c
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  STRBUF*		������o�b�t�@�i���s�Ȃ�NULL)
 */
//------------------------------------------------------------------
extern STRBUF* MSGDAT_UTIL_GetWazaName( u32 wazaID, u32 heapID );


//------------------------------------------------------------------
/**
 * �|�P��������������A�V�K�ɍ쐬����������o�b�t�@�ɃR�s�[���ĕԂ�
 * �i������o�b�t�@�̍폜�͊e���ōs���j
 *
 * @param   monsno		�|�P�����i���o�[
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  STRBUF*		������o�b�t�@�i���s�Ȃ�NULL)
 */
//------------------------------------------------------------------
extern STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID );



#endif
