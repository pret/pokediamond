//=============================================================================
/**
 * @file	comm_command_mystery.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *		�u�ӂ����Ȃ�������́v�p          
 *          	comm_command_mystery.h �� enum �Ɠ������тł���K�v������܂�
 * @author	Satoshi Mitsuhara
 * @date    2006.05.16
 * $Id: comm_command_mystery.c,v 1.1 2006/05/18 11:04:55 mitsuhara Exp $
*/
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_command_mystery.h"
#include "comm_mystery_state.h"


//==============================================================================
//  �e�[�u���ɏ����֐��̒�`
//==============================================================================

//==============================================================================
//  static��`
//==============================================================================

//==============================================================================
//	�e�[�u���錾
//  comm_shar.h �� enum �Ɠ����Ȃ�тɂ��Ă�������
//  CALLBACK���Ă΂ꂽ���Ȃ��ꍇ��NULL�������Ă�������
//  �R�}���h�̃T�C�Y��Ԃ��֐��������Ă��炦��ƒʐM���y���Ȃ�܂�
//  _getZero�̓T�C�Y�Ȃ���Ԃ��܂��B_getVariable�͉σf�[�^�g�p���Ɏg���܂�
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
  /* �ӂ����Ȃ�������́@�f�[�^���M */
  { CommMysteryGiftRecvPlace, CommMysteryGetRecvPlaceSize, CommGetMysteryGiftRecvBuff },
  /* ��M�������܂����̃t���O�@�f�[�^���M */
  { CommMysterySendRecvResult, _getZero, NULL },
};

//--------------------------------------------------------------
/**
 * @brief   �ӂ����Ȃł����Ɨp�̃R�}���h�̌n�ɏ��������܂�
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void CommCommandMysteryInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

/*  */
