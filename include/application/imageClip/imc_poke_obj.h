//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_poke_obj.h
 *	@brief		�C���[�W�N���b�v�|�P���� �f�[�^
 *	@author		tomoya takahashi
 *	@data		2005.09.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_POKE_OBJ_H__
#define __IMC_POKE_OBJ_H__

#include "system.h"
#include "system/gamedata.h"
#include "touchpanel.h"
#include "system/softsprite.h"
#include "poketool/poke_tool.h"
#include "include/application/imageClip/imc_drawsys.h"

#undef GLOBAL
#ifdef	__IMC_POKE_OBJ_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_POKE_INIT_X			(192)
#define IMC_POKE_INIT_Y			(56)
#define	IMC_POKE_DEFAULT_PRI	(0)

#define	IMC_POKE_ANM_NUM		(2)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�H������ł悢�T�C�Y�e�[�u��
//	
//=====================================
typedef struct {
	u16	x_no;
	u16	y_no;
} IMC_POKE_INS_DAT;

//-------------------------------------
//	
//	�C���[�W�N���b�v�|�P�����\����
//	
//=====================================
typedef struct {
	SOFT_SPRITE*		sprite;		// �X�v���C�g�f�[�^

	TP_HIT_TBL hit_tbl;	// �����蔻��f�[�^
	
	u8	ins_x;			// �p���b�g�ɐH������ł悢�T�C�YX
	u8	ins_y;			// �p���b�g�ɐH������ł悢�T�C�YY
	
	// �|�P�����f�[�^
	POKEMON_PARAM* poke_para;
} IMC_POKE;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����̃L�����N�^�f�[�^��`��V�X�e���ɓo�^
 *
 *	@param	poke_para		�|�P�����p�����[�^�\����
 *	@param	drawData		�`��V�X�e���f�[�^
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_CharSet( IMC_DRAW_DATA* drawData, SOFT_SPRITE_ARC* arc_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�@�|�P�����f�[�^�쐬
 *
 *	@param	poke			�C���[�W�N���b�v�@�|�P�����f�[�^
 *	@param	sprite_man		�\�t�g�E�F�A�X�v���C�g�}�l�[�W��
 *	@param	poke_para		�|�P�����p�����[�^�\����
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^
 *	@param	heap			�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_Init( IMC_POKE* poke,  SOFT_SPRITE_MANAGER* sprite_man, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�@�|�P�����f�[�^�j��
 *
 *	@param	poke			�C���[�W�N���b�v�@�|�P�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_Delete( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʂ�ݒ�
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	priority	�D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_DrawPrioritySet( IMC_POKE* poke, int priority );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʂ��擾
 *
 *	@param	poke		�|�P�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_POKE_DrawPriorityGet( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W��ݒ�
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_MatrixSet( IMC_POKE* poke, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������W���擾
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_MatrixGet( IMC_POKE* poke, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����T�C�Y���擾
 *
 *	@param	poke		�|�P�����f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_SizeGet( IMC_POKE* poke, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����ƃ^�b�`�p�l���̓����蔻��
 *
 *	@param	poke	�|�P�����f�[�^
 *
 *	@retval	TRUE	������
 *	@retval	FALSE	������Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHit( IMC_POKE* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����Ǝw����W�̓����蔻��
 *
 *	@param	poke	�|�P�����f�[�^
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@retval	TRUE	������
 *	@retval	FALSE	������Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitSelf( IMC_POKE* poke, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	offs_x		���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y		���ォ��̃I�t�Z�b�g�����W
 *	@param	char_data	�L�����N�^�f�[�^	
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitEx( IMC_POKE* poke, int* offs_x, int* offs_y, NNSG2dCharacterData* char_data );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l���Ƃ̓����蔻����ׂ����s��	���W�w��
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	x			���ォ��̃I�t�Z�b�g�����W
 *	@param	y			���ォ��̃I�t�Z�b�g�����W
 *	@param	char_data	�L�����N�^�f�[�^	
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����	�i�I�t�Z�b�g���W�s��j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_POKE_TPHitExSelf( IMC_POKE* poke, int x, int y, NNSG2dCharacterData* char_data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����̐H������ł悢�T�C�Y���擾
 *
 *	@param	poke		�I�u�W�F�N�g�f�[�^
 *	@param	ins_x		�H������ł悢�T�C�Y�擾�̈�
 *	@param	ins_y		�H������ł悢�T�C�Y�擾�̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_POKE_InSizeGet( IMC_POKE* poke, int* ins_x, int* ins_y );

#undef	GLOBAL
#endif		// __IMC_POKE_OBJ_H__
