/**
 *	@file	nmix_res.h
 *	@brief	�i�b�c�~�L�T�[�@���\�[�X�Ǘ�
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 *
 *
 *	�`��c�[���������ɒǉ�
 */

#ifndef __H_NMIX_RES_H__
#define __H_NMIX_RES_H__

#ifdef __NMIX_RES_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif



//-----------------------------------------------------------------------------
/**
 *		�萔��`
 */
//-----------------------------------------------------------------------------
//-------------------------------------
// OAM
//=====================================
#define NMIX_OAM_OAM_MAIN_S			(0)			// ���C����� OAM�g�p�̈�J�n
#define NMIX_OAM_OAM_MAIN_E			(128)		// ���C����� OAM�g�p�̈�I��
#define NMIX_OAM_AFF_MAIN_S			(0)			// ���C����� �A�t�B���g�p�̈�J�n
#define NMIX_OAM_AFF_MAIN_E			(32)		// ���C����� �A�t�B���g�p�̈�I��
#define NMIX_OAM_OAM_SUB_S			(0)			// �T�u��� OAM�g�p�̈�J�n
#define NMIX_OAM_OAM_SUB_E			(128)		// �T�u��� OAM�g�p�̈�I��
#define NMIX_OAM_AFF_SUB_S			(0)			// �T�u��� �A�t�B���g�p�̈�J�n
#define NMIX_OAM_AFF_SUB_E			(32)		// �T�u��� �A�t�B���g�p�̈�I��
#define NMIX_OAM_CHAR_ENTRY_NUM		(32)		// �L�����N�^�}�l�[�W���G���g���[��
#define NMIX_OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x20000)	// ���C����� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define NMIX_OAM_CHAR_VRAMTRANS_SUB_SIZE	(0x0)		// �T�u��� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define NMIX_OAM_PLTT_ENTRY_NUM		(32)		// �p���b�g�}�l�[�W���G���g���[��



//-------------------------------------
//	�Z���A�N�^�[
//=====================================
#define NMIX_GAME_CLACT_WORK_MAX		( 72 )	// ���[�N�ő�
#define NMIX_GAME_CLACT_RES_MAX			( 16 )	// ���ꂼ�ꃊ�\�[�X�ő�
#define NMIX_GAME_CLACT_RES_OBJ_TYPE	( 4 )	// char/pltt/cell/cellanm

//-------------------------------------
//	�\�t�g�E�F�A�X�v���C�g
//=====================================
#define NMIX_GAME_SWSP_WORK_MAX			( 48 )
#define NMIX_GAME_SWSP_CHAR_MAX			( 32 )
#define NMIX_GAME_SWSP_PLTT_MAX			( 32 )





//-----------------------------------------------------------------------------
/**
 *
 *		�v���g�^�C�v�錾
 *
 */
//-----------------------------------------------------------------------------


/**
 *	@brief	�R�}���h�@���\�[�X������
 */
GLOBAL void NMixGameCom_GameStartGraphicInit(NMIX_GAMEWORK* wk);
/**
 *	@brief	�R�}���h�@���\�[�X���
 */
GLOBAL void NMixGameCom_GameStartGraphicRelease(NMIX_GAMEWORK* wk);


/**
 *	@brief	�R�}���h�@���\�[�X������
 */
GLOBAL int NMixGameCom_ResInit(NMIX_GAMEWORK* wk,int* seq);
/**
 *	@brief	�R�}���h�@���\�[�X���
 */
GLOBAL int NMixGameCom_ResRelease(NMIX_GAMEWORK* wk,int *seq);


// �`�揈��
GLOBAL void NMixGame_Draw( NMIX_GAMEWORK* wk );
GLOBAL void NMixGame_GraVBlank( NMIX_GAMEWORK* wk );



#endif	//__H_NMIX_RES_H__
