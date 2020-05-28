//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_item_buff.c
 *	@brief		�A�C�e�����ێ��o�b�t�@
 *	@author		tomoya takahashi
 *	@data		2006.03.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "assert.h"

#define __IMC_ITEM_BUFF_H_GLOBAL
#include "include/application/imageClip/imc_item_buff.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------
/**
 *	@brief	�Z�[�u�f�[�^����A�C�e���ێ��f�[�^�쐬
 *
 *	@param	cp_imc_item		�A�C�e���Z�[�u�f�[�^
 *	@param	p_buff			�f�[�^�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_ITEM_BUFF_Make( const IMC_ITEM_SAVEDATA* cp_imc_item, IMC_ITEM_BUFF* p_buff )
{
	int i;
	u32 idx;
	
	// �A�N�Z�T���ێ��f�[�^�擾
	for( i=0; i<IMC_ACCE_MAX; i++ ){
		p_buff->Acce[ i ] = ImcSaveData_GetAcceFlag( cp_imc_item, i );
	}

	// �o�b�O�ێ��f�[�^�擾
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		p_buff->Bg[ i ] = IMC_BG_RIGHT_MAX;
	}
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		idx = ImcSaveData_GetBGFlag( cp_imc_item, i );
		
		if( idx != IMC_BG_RIGHT_MAX ){	
			p_buff->Bg[ idx ] = i;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ێ������ւ炷
 *
 *	@param	p_buff	�o�b�t�@�f�[�^
 *	@param	acce_no	�A�N�Z�T���i���o�[
 *	@param	num		���炷�l
 *
 *	@retval	TRUE	�O�ȏ�ɂȂ���
 *	@retval	FALSE	�O�ȉ��ɂȂ���
 */
//-----------------------------------------------------------------------------
BOOL IMC_ITEM_BUFF_AcceDec( IMC_ITEM_BUFF* p_buff, u32 acce_no, int num )
{
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	if( p_buff->Acce[ acce_no ] == IMC_ACCE_MAX ){
		return FALSE;
	}

	if( (p_buff->Acce[ acce_no ] - num) >= 0 ){
		p_buff->Acce[ acce_no ] -= num;
		return TRUE;
	}

	p_buff->Acce[ acce_no ] = 0;
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���擾���@��Ԃ�
 *
 *	@param	p_buff		�o�b�t�@
 *	@param	acce_no		�A�N�Z�T���i���o�[
 *
 *	@return	�A�N�Z�T���擾��
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_AcceGetNum( const IMC_ITEM_BUFF* p_buff, u32 acce_no )
{
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	return p_buff->Acce[ acce_no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	���Ԃ���Ή�����BGNo���擾����
 *
 *	@param	p_buff	�o�b�t�@
 *	@param	turn	����
 *
 *	@return	BG�i���o�[
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_TurnBgNoGet( const IMC_ITEM_BUFF* p_buff, u32 turn )
{
	return p_buff->Bg[ turn ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGNO����擾�������Ԃ����߂�
 *
 *	@param	p_buff		�o�b�t�@
 *	@param	bgno		BGNo
 *
 *	@return	����������		IMC_BG_RIGHT_MAX �̂Ƃ��݂��Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 IMC_ITEM_BUFF_BgNoTurnGet( const IMC_ITEM_BUFF* p_buff, u32 bgno )
{
	int i;

	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		if( p_buff->Bg[ i ] == bgno ){
			return i;
		}
	}

	return i;
}

