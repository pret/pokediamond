//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_playsys.h
 *	@brief		�C���[�W�N���b�v�v���C���[�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.12.27
 *
 * �C���[�W�N���b�v�v���b�N���쐬���ĕ\������ȊO�̕��@��
 * �\������C���[�W�N���b�v�v���C���[
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_PLAYSYS_H__
#define __IMC_PLAYSYS_H__
#include "bg_system.h"
#include "poketool/poke_tool.h"
#include "savedata/imageclip_data.h"

#undef GLOBAL
#ifdef	__IMC_PLAYSYS_H_GLOBAL
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
//
//	�C���[�W�N���b�v�v���C���[�V�X�e��
//	
//=====================================
typedef struct _IMC_PLAYERSYS* IMC_PLAYERSYS_PTR;
typedef const struct _IMC_PLAYERSYS* CONST_IMC_PLAYERSYS_PTR;


//-------------------------------------
//	
//	�������f�[�^
//	
//=====================================
typedef struct {
	GF_BGL_INI* p_bg_ini;	// BG�V�X�e��	NOBG�̂Ƃ���NULL��OK
							// GF_BGL_FRAME2_M�̃R���g���[���Z�b�g������ōs���܂��B
	int x;				// �S�̂̒��S
	int y;				// �S�̂̒��S
	int heap_id;		// �g�p����q�[�vID
} IMC_PLAYERSYS_INIT;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[����
 *
 *	@param	cp_init		�������f�[�^
 *	@param	save_data	�Z�[�u�f�[�^
 *
 *	@return	�������ꂽ�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_ContestPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data );
GLOBAL IMC_PLAYERSYS_PTR IMC_ContestPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[���C��
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerMain( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[�I��
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerEnd( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank���Ԓ��ɌĂԊ֐�
 *
 *	@param	p_sys	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_PlayerVblank( IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	�`��@�t���O
 *			TRUE�@�`��@		FALSE	��`��
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag );
GLOBAL BOOL IMC_Player_GetDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���`��@�t���O
 *			TRUE�@�`��@		FALSE	��`��
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetAcceDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag );
GLOBAL BOOL IMC_Player_GetAcceDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	���W ��]�@�g�k
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y );
GLOBAL void IMC_Player_SetRota( IMC_PLAYERSYS_PTR p_sys, u16 rota );
GLOBAL void IMC_Player_SetScale( IMC_PLAYERSYS_PTR p_sys, fx32 x, fx32 y, fx32 z );
GLOBAL void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y );
GLOBAL void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y );

//-----------------------------------------------------------------------------
/**
 *	@brief	�S�̓I�ȕ`��F
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetColor( IMC_PLAYERSYS_PTR p_sys, GXRgb color );
GLOBAL GXRgb IMC_Player_GetColor( CONST_IMC_PLAYERSYS_PTR cp_sys );

//-----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����𒆐S�Ƃ������W�ƒ��S�I�t�Z�b�g�̐ݒ�
 *
 *	@param	p_sys	���[�N
 *	@param	x		�����W	�i�����͍���ł͂Ȃ��|�P�����̒��S���W�j
 *	@param	y		�����W	�i�����͍���ł͂Ȃ��|�P�����̒��S���W�j
 *
 *	@param	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPokeMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̑��Ս��W��ݒ肷��
 *
 *	@param	p_sys	���[�N
 *	@param	x		�����W	�i�����͍���ł͂Ȃ��|�P�����̑������W�j
 *	@param	y		�����W	�i�����͍���ł͂Ȃ��|�P�����̑������W�j
 *	@param	height	���̃|�P�����̍���
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPokeMatrix_Ground( IMC_PLAYERSYS_PTR p_sys, int x, int y, int height );


//-----------------------------------------------------------------------------
/**
 *	@brief	�D�揇�ʂ�ݒ�	�擪�̃A�N�Z�T���̗D�揇��
 *
 *	@param	p_sys	���[�N
 *	@param	pri		�|�P�����̗D�揇�ʁi�\�t�g�E�F�A�X�v���C�g�́j
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_Player_SetPriority( IMC_PLAYERSYS_PTR p_sys, int pri );
GLOBAL void IMC_Player_AddPriority( IMC_PLAYERSYS_PTR p_sys, int pri );



#ifdef PM_DEBUG
#include "include/system/procsys.h"

//-------------------------------------
//	�C���[�W�N���b�v�O���f�[�^
//=====================================
typedef struct {
	// �C���[�W�N���b�v�Z�[�u�̈�
	const IMC_TELEVISION_SAVEDATA* p_imc_one_data;
} IMC_PROC_PLAY_WORK;

// �`�F�b�N�p�v���b�N
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcInit( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcMain( PROC* proc, int* seq );
GLOBAL PROC_RESULT IMC_PlayTelevision_ProcEnd( PROC* proc, int* seq );
#endif

#undef	GLOBAL
#endif		// __IMC_PLAYSYS_H__

