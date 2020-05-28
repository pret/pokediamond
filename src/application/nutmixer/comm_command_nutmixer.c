/**
 *	@file	comm_command_nutmixer.c
 *	@brief	�؂̎��~�L�T�[�@�ʐM�R�}���h�e�[�u��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 *	@data	06.05.23	tomoya �ύX
 */

#include "common.h"
#include "communication/communication.h"
#include "comm_command_nutmixer_func.h"
#include "comm_command_nutmixer.h"

#include "include/savedata/poruto_util.h"


// �Ή�����R�[���o�b�N�֐�
static const CommPacketTbl _CommNutMixerPacketTbl[] = {
	//-------------------------------------
	//�@�Q�[���p
	//=====================================
	// �����p	
	{ CommNutMixerGameSysStart, CommNutMixerGetZeroSize, NULL },			///< �~�L�T�[�J�n			�e�[���q
	{ CommNutMixerGameEnd, CommNutMixerGetZeroSize, NULL },			///< �Q�[���I��				�e�[���q
	// �f�[�^��M�p
	{ CommNutMixerGameBeforeDataKo, CommNutMixerGetGameBeforeKoSize, NULL },		///< �v���C���[��		�e�[���q
	{ CommNutMixerGameBeforeData, CommNutMixerGetGameBeforeSize, NULL },		///< �v���C���[��		�q�[���e
	{ CommNutMixerGameData, CommNutMixerGetGameSize, NULL },		///< �Q�[���f�[�^		�e���[���q
	{ CommNutMixerGameResultData, CommNutMixerGetGameResultSize, NULL },	///< ���ʃf�[�^			�e�[���q
	{ CommNutMixerPorutoData, PorutoData_GetWorkSize, NULL },	///< �|���g�f�[�^			�e�[���q
	{ CommNutMixerGameNextDataKo, CommNutMixerGetOneSize, NULL },	///< 	�Q�[���I���f�[�^	�e�[���q
	{ CommNutMixerGameNextData, CommNutMixerGetOneSize, NULL },		///< �Q�[���I���f�[�^		�q�[���e

};

//----------------------------------------------------------------------------
/**
 *	@brief		�R�}���h�e�[�u�����擾
 */
//-----------------------------------------------------------------------------
const CommPacketTbl* NutMixer_CommCommandTclGet( void )
{
	return _CommNutMixerPacketTbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�R�}���h�e�[�u���v�f�����擾
 */
//-----------------------------------------------------------------------------
int NutMixer_CommCommandTblNumGet( void )
{
    return sizeof(_CommNutMixerPacketTbl)/sizeof(CommPacketTbl);
}
