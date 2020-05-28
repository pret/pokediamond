//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_rbox_player.c
 *	@brief		�E�{�b�N�X�v���C���[
 *	@author		tomoya takahashi
 *	@data		2005.10.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "include/application/imageClip/imc_drawdata_define.h"


#define __IMC_RBOX_PLAYER_H_GLOBAL
#include "include/application/imageClip/imc_rbox_player.h"


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
 *
 *	@brief	�E�{�b�N�X�v���C���[������
 *
 *	@param	rbox_player	�E�{�b�N�X�v���C���[
 *	@param	rbox		�E�{�b�N�X�\����
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Init( IMC_RBOX_PLAYER* rbox_player, const IMC_RIGHT_BOX* rbox, int heap )
{
	IMC_BG_ANM_INIT init;
	
	rbox_player->rbox = rbox;

	init.bg			= &rbox->boxDraw.bg;
	init.scrn_arc	= IMC_BG_RIGHT_SC_ANM_ARC_GET( rbox->boxDraw.bg_no );
	init.timing		= IMC_RBOX_PLAYER_BG_ANM_TIMING;
	init.heap		= heap;
	IMC_BG_AnmInit( &rbox_player->bg_anm, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�v���C���[���C��
 *	
 *	@param	rbox_player		�E�{�b�N�X�v���C���[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Main( IMC_RBOX_PLAYER* rbox_player )
{
	// BG�A�j��
	IMC_BG_Anm( &rbox_player->bg_anm, IMC_RBOX_PLAYER_BG_ANM_FRAME );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�v���C���[�j��
 *
 *	@param	rbox_player		�E�{�b�N�X�v���C���[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_PLAYER_Delete( IMC_RBOX_PLAYER* rbox_player )
{
	IMC_BG_AnmDelete( &rbox_player->bg_anm );
	memset( rbox_player, 0, sizeof(IMC_RBOX_PLAYER) );
}

