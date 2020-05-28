//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_item_buff.h
 *	@brief		�A�C�e�����ێ��o�b�t�@
 *	@author		tomoya takahashi
 *	@data		2006.03.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ITEM_BUFF_H__
#define __IMC_ITEM_BUFF_H__

#include "include/savedata/imageclip_data.h"

#undef GLOBAL
#ifdef	__IMC_ITEM_BUFF_H_GLOBAL
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
//-------------------------------------
//	�A�C�e���ێ��o�b�t�@
//=====================================
typedef struct {
	u32 Acce[ IMC_ACCE_MAX ];	// �A�N�Z�T���i���o�[index�ێ���
	u32 Bg[ IMC_BG_RIGHT_MAX ];	// BG��������indexBG�i���o�[
} IMC_ITEM_BUFF;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void IMC_ITEM_BUFF_Make( const IMC_ITEM_SAVEDATA* cp_imc_item, IMC_ITEM_BUFF* p_buff );

GLOBAL BOOL IMC_ITEM_BUFF_AcceDec( IMC_ITEM_BUFF* p_buff, u32 acce_no, int num );
GLOBAL u32 IMC_ITEM_BUFF_AcceGetNum( const IMC_ITEM_BUFF* p_buff, u32 acce_no );

u32 IMC_ITEM_BUFF_TurnBgNoGet( const IMC_ITEM_BUFF* p_buff, u32 turn );
u32 IMC_ITEM_BUFF_BgNoTurnGet( const IMC_ITEM_BUFF* p_buff, u32 bgno );

#undef	GLOBAL
#endif		// __IMC_ITEM_BUFF_H__

