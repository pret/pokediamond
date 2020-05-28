//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_right_box.h
 *	@brief		�E�{�b�N�X�f�[�^
 *	@author		tomoya takahashi
 *	@data		2005.09.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_RIGHT_BOX_H__
#define __IMC_RIGHT_BOX_H__

#include <nnsys.h>

#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_poke_obj.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_bg.h"
#include "touchpanel.h"

#undef GLOBAL
#ifdef	__IMC_RIGHT_BOX_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define	IMC_RBOX_ACCE_PRIORITY_START	(-1)		// �A�N�Z�T���̕\���D�揇�̔ԍ�
#define	IMC_RBOX_OBJ_MAX				(11)		// �E�{�b�N�X�̃I�u�W�F�N�g�o�^�ő吔
													// �A�N�Z�T��10 + �|�P����1

#define	IMC_RBOX_OBJ_CONTEST_MAX		(21)		// �E�{�b�N�X�̃I�u�W�F�N�g�o�^�ő吔

#define	IMC_RBOX_ACCE_TELEVISION_MAX	(10)		// �E�{�b�N�X�̃I�u�W�F�N�g�o�^�ő吔
													// �A�N�Z�T��10

#define	IMC_RBOX_ACCE_CONTEST_MAX		(20)		// �E�{�b�N�X�̃A�N�Z�T���ő吔


//-------------------------------------
//	
//	BG�p
//	
//=====================================
#define	IMC_RBOX_BG_PLTT_NUM	(1)		// �p���b�g��
#define IMC_RBOX_BG_PLTT_OFFS	(1)		// �p���b�g�ԍ�

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�E�{�b�N�X�\����	
//	�`�敔
//	
//=====================================
typedef struct {
	// �`��V�X�e���f�[�^
	// �A�N�Z�T���p
	SWSP_SYS_PTR	SWSP_drawSys;		// �X�v���C�g�`��V�X�e��
	SWSP_CHAR_PTR*	SWSP_charData;		// �L�����N�^�f�[�^�z��
	SWSP_PLTT_PTR*	SWSP_plttData;		// �p���b�g�f�[�^�z��
	u8* accePlttOfsTbl;

	// �|�P�����p
	SOFT_SPRITE_MANAGER* SSM_drawSys;		// �|�P�����`��p�X�v���C�g

	// BG�f�[�^
	GF_BGL_INI*		BG_Ini;
	
	// �A�N�Z�T���f�[�^
	IMC_ACCESSORIE_OBJ_TBL*	acce;

	
	// �E�w�i�f�[�^
	IMC_BG	bg;		// �EBG�f�[�^
	int bg_no;		// �EBG�i���o�[
	
	// �|�P�����f�[�^
	IMC_POKE	poke;
	
	// �����f�[�^
	
} IMC_RIGHT_BOXDRAW;

//-------------------------------------
//	
//	�E�{�b�N�X�\���̃f�[�^��
//	
//=====================================
typedef struct {
	// �I�u�W�F���X�g
	IMC_OBJLIST_TBL*		objListTbl;
	IMC_OBJLIST				dummy;		// �|�P�����̉�
	IMC_OBJLIST				dummy_poke;	// �|�P�����̏�
	int		obj_count;		// �A�N�Z�T���o�^��
	int		obj_count_max;	// �A�N�Z�T���o�^�ő吔

} IMC_RIGHT_BOXDATA;


//-------------------------------------
//	
//	�E�{�b�N�X�f�[�^
//	
//=====================================
typedef struct {

	IMC_RIGHT_BOXDATA	boxData;
	IMC_RIGHT_BOXDRAW	boxDraw;
} IMC_RIGHT_BOX;



//-------------------------------------
//	
//	�E�{�b�N�X�������\����	
//	
//=====================================
typedef struct {
	// �A�N�Z�T���p
	SWSP_SYS_PTR	SWSP_drawSys;		// �X�v���C�g�`��V�X�e��
	SWSP_CHAR_PTR*	SWSP_charData;		// �L�����N�^�f�[�^�z��
	SWSP_PLTT_PTR*	SWSP_plttData;		// �p���b�g�f�[�^�z��
	u8* accePlttOfsTbl;

	// �|�P�����p
	SOFT_SPRITE_MANAGER* SSM_drawSys;		// �|�P�����`��p�X�v���C�g

	// BG�f�[�^
	GF_BGL_INI*		BG_Ini;

	IMC_ACCESSORIE_OBJ_TBL* acce;		// �A�N�Z�T�����X�g�f�[�^
	IMC_OBJLIST_TBL*		objListTbl;	// �I�u�W�F���X�g�e�[�u��

	int acce_count_max;			// �A�N�Z�T���o�^�ő吔
} IMC_RIGHT_BOX_INIT;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�p�̈�쐬
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	init		�E�{�b�N�X�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_InitSys( IMC_RIGHT_BOX* rbox, IMC_RIGHT_BOX_INIT* init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�p�̈�j��
 *
 *	@param	rbox		�j������E�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteSys( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����f�[�^�v���C���[�p�쐬
 *
 *	@param	rbox			�E�{�b�N�X�f�[�^
 *	@param	poke_para		�쐬����|�P�����̃|�P�����p�����[�^
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^�i�[�̈�
 *	@param	x				x���W
 *	@param	y				y���W
 *	@param	pri				�\���D�揇��
 *	@param	heap			�q�[�vID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_AddPokePlayer( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int x, int y, int pri, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����f�[�^�쐬
 *
 *	@param	rbox			�E�{�b�N�X�f�[�^
 *	@param	poke_para		�쐬����|�P�����̃|�P�����p�����[�^
 *	@param	arc_data		�A�[�J�C�u�t�@�C���f�[�^�i�[�̈�
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_AddPoke( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����ړ��ǉ�
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	poke	�|�P�����I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_MoveAddPoke( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߃��X�g����폜
 *	
 *	@param	poke		�|�P�����I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_MoveDeletePoke( IMC_OBJLIST* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�����I�u�W�F�N�g�j��
 *
 *	@param	rbox	�E�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeletePoke( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	rbox				�E�{�b�N�X�p�f�[�^
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *	@param	x					X���W
 *	@param	y					Y���W
 *	@param	pri					�\���D�揇��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieEasy( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, int pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieMoveEasy( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );


//----------------------------------------------------------------------------
/**
 *	[�ׂ��������@�C���[�W�N���b�v�쐬�V�X�e���ł͂��������Ă�]
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	rbox				�E�{�b�N�X�p�f�[�^
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *	@param	x					X���W
 *	@param	y					Y���W
 *	@param	SWSP_UPchar			����p�L�����N�^�f�[�^
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorie( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *	[�ׂ��������@�C���[�W�N���b�v�쐬�V�X�e���ł͂��������Ă�]
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	rbox		�E�{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *	@param	SWSP_UPchar			����p�L�����N�^�f�[�^
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���s	�i�o�^�ő吔�ȏ�o�^���悤�Ƃ����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj, NNSG2dCharacterData** SWSP_UPchar );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�j��
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	acce_obj	�j������A�N�Z�T��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorie( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߂̃��X�g����̍폜
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	acce_obj	�ړ������邽�߂Ƀ��X�g����폜����A�N�Z�T���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���A�N�Z�T���S�Ă��͂�
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorieAll( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X���̃X�v���C�g�ŕ\������Ă���I�u�W�F�N�g�𓮂���
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�������l
 *	@param	y		�������l
 *	
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_ListMove( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̏�̃A�N�Z�T���𓮂���
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_PokeUpListMove( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�̒��S���W��ݒ�
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	old_x		�O�͉�������ɂ��Ă����̂�
 *	@param	old_y
 *	@param	x			���ꂩ��͉�������ɂ���̂�
 *	@param	y 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_ListMatSet( IMC_RIGHT_BOX* rbox, int old_x, int old_y, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�̃A�N�Z�T���\���v���C�I���e�B��ݒ�
 *
 *	@param	rbox		�E�{�b�N�X 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_SetObjPriority( IMC_RIGHT_BOX* rbox );
GLOBAL void IMC_RBOX_SetObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority );
GLOBAL void IMC_RBOX_AddObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�����E�{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_TPHit( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w����W���E�{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	rbox		�E�{�b�N�X�f�[�^
 *	@param	x			���肘���W
 *	@param	y			���肙���W
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_TPHitSelf( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����s��
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_RBOX_TPHitObj( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����ׂ����s��
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	offset_x	�I�t�Z�b�g�����W
 *	@param	offset_y	�I�t�Z�b�g�����W
 *	@param	SWSP_UPchar	����L�����N�^�f�[�^�e�[�u��
 *
 *	@return	none
 *
 * �L�����N�^�f�[�^���Q�Ƃ��Ĕ����F�ł͂Ȃ����`�F�b�N
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_RBOX_TPHitObjEx( IMC_RIGHT_BOX* rbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��\��
 *
 *	@param	rbox		�E�{�b�N�X
 *	@param	bg_num		�E�{�b�N�XBG�i���o�[
 *	@param	heap		�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_BGSet( IMC_RIGHT_BOX* rbox, int bg_num, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG���N���[������
 *
 *	@param	rbox		�E�{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_BGClean( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������W���擾
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_GetPokeMatrix( IMC_RIGHT_BOX* rbox, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *	@brief	�ێ����Ă���A�N�Z�T�����擾
 *
 *	@param	rbox	�E�{�b�N�X
 *
 *	@return	�A�N�Z�T����
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_RBOX_GetNowHaveAcceNum( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̏�ɏ���Ă���A�N�Z�T�����H������ł���T�C�Y���擾
 *
 *	@param	rbox		�E�{�b�N�X���[�N
 *	@param	enc_x		�H������ł�T�C�Y��
 *	@param	enc_y		�H������ł�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_GetPokeUpListEncSize( IMC_RIGHT_BOX* rbox, int* enc_x, int* enc_y );

//----------------------------------------------------------------------------
/**
 *	@brief	�E�{�b�N�X�@�F�ݒ�
 *
 *	@param	rbox	�E�{�b�N�X
 *	@param	color	�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_SetObjColor( IMC_RIGHT_BOX* rbox, GXRgb color );

#undef	GLOBAL
#endif		// __IMC_RIGHT_BOX_H__

