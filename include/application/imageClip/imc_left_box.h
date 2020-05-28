//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_left_box.h
 *	@brief		���{�b�N�X�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_LEFT_BOX_H__
#define __IMC_LEFT_BOX_H__

#include <nnsys.h>

#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_bg.h"
#include "include/application/imageClip/imc_item_buff.h"
#include "touchpanel.h"


#undef GLOBAL
#ifdef	__IMC_LEFT_BOX_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	
//	���{�b�N�X�A�N�Z�T���\���D�揇�ʊJ�n
//	
//=====================================
#define IMC_LBOX_ACCE_PRIORITY_START	(-1)



//-------------------------------------
//	
//	BG�p
//	
//=====================================
#define	IMC_LBOX_BG_PLTT_NUM	(1)
#define IMC_LBOX_BG_PLTT_OFFS	(2)

//-------------------------------------
//	
//	���̓�����
//	
//=====================================
enum{
	IMC_LBOX_STATE_NORM,	// �ʏ�
	IMC_LBOX_STATE_FADE,	// �p���b�g�t�F�[�h��
};

//-------------------------------------
//	
//	�t�F�[�h����
//	
//=====================================
enum{
	IMC_LBOX_FADE_X = 1,
	IMC_LBOX_FADE_Y = 2
};

//-------------------------------------
//	
//	���X�g�����ZӰ��
//	
//=====================================
enum{
	IMC_LBOX_ADD_ONE,		// +1
	IMC_LBOX_SUB_ONE,		// -1
};

//-------------------------------------
//
//	���p���b�g�t�F�[�h�A�E�g�p
//	���X�g���[�h
//
//	�t�F�[�h�A�E�g�p���X�g��
//	�P�����Ȃ��ł�
//	
//	�t�F�[�h�������Ȃ����X�g��`�悳���邽��
//=====================================
#define IMC_LBOX_FADELIST_MODE		(IMC_OBJLIST_ACCE_MAX)
#define IMC_LBOX_FADELIST_LISTNUM	(1)
#define IMC_LBOX_LIST_NUM			(IMC_LBOX_FADELIST_MODE + 1)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���p���b�g���X�g
//	
//=====================================
typedef struct {
	IMC_OBJLIST*			dummyTbl;		// ���X�g�_�~�[�e�[�u��
	int						dummyNum;		// �_�~�[�e�[�u����
	int						dummyCurrent;	// ���̃J�����g�_�~�[�e�[�u��
} IMC_LEFT_LIST_DATA;

//-------------------------------------
//	
//	���{�b�N�X�\����	
//	�`�敔
//	
//=====================================
typedef struct {
	// �`��V�X�e���f�[�^
	SWSP_SYS_PTR	SWSP_drawSys;		// �X�v���C�g�`��V�X�e��
	SWSP_CHAR_PTR*	SWSP_charData;		// �L�����N�^�f�[�^�z��
	SWSP_PLTT_PTR*	SWSP_plttData;		// �p���b�g�f�[�^�z��
	u8* accePlttOfsTbl;						// �A�N�Z�T���p���b�g�I�t�Z�b�g
	
	// BG�f�[�^
	GF_BGL_INI*		BG_Ini;
	
	// �A�N�Z�T���f�[�^
	IMC_ACCESSORIE_OBJ_TBL*	acce;
	
	// �w�i�f�[�^���X�g
	IMC_BG	bg;
	IMC_ACCESSORIE_OBJ_TBL*	bg_acce;	// BG�T���l�C��
	
	// �����f�[�^���X�g
	
} IMC_LEFT_BOXDRAW;

//-------------------------------------
//	
//	���{�b�N�X�\���̃f�[�^��
//	
//=====================================
typedef struct {

	// ���̕ҏW���[�h
	// �A�N�Z�T��	BG	�T�E���h
	int		mode;

	// BG�T���l�C���\�����f�[�^
	IMC_ITEM_BUFF* p_item_buff;

	// �I�u�W�F�N�g���X�g
	IMC_OBJLIST_TBL* objListTbl;
	
	// �A�N�Z�T�����[�h���̃��X�g�f�[�^
	// �擪�_�~�[�f�[�^
	// �擪�_�~�[�f�[�^��
	// ���̃J�����g�_�~�[�f�[�^
	//
	IMC_LEFT_LIST_DATA	acce_list[ IMC_LBOX_LIST_NUM ];

	int	state;		// ���̓����� 
	int back_no;	// ���̔w�i�i���o�[
} IMC_LEFT_BOXDATA;


//-------------------------------------
//	
//	���{�b�N�X�f�[�^
//	
//=====================================
typedef struct {

	IMC_LEFT_BOXDATA	boxData;
	IMC_LEFT_BOXDRAW	boxDraw;
} IMC_LEFT_BOX;



//-------------------------------------
//	
//	���{�b�N�X�������\����	
//	
//=====================================
typedef struct {
	SWSP_SYS_PTR	SWSP_drawSys;		// �X�v���C�g�`��V�X�e��
	SWSP_CHAR_PTR*	SWSP_charData;		// �L�����N�^�f�[�^�z��
	SWSP_PLTT_PTR*	SWSP_plttData;		// �p���b�g�f�[�^�z��
	u8* accePlttOfsTbl;						// �A�N�Z�T���p���b�g�I�t�Z�b�g
	
	// BG�f�[�^
	GF_BGL_INI*		BG_Ini;

	IMC_ACCESSORIE_OBJ_TBL* acce;			// �A�N�Z�T�����X�g�f�[�^
	IMC_OBJLIST_TBL*		objListTbl;		// �I�u�W�F�N�g���X�g�e�[�u��
	int						accelist_num;	// �쐬����A�N�Z�T�����X�g��
	int						bglist_num;		// �쐬����BG�T���l�C�����X�g��
	int						sndlist_num;	// �쐬����T�E���h�T���l�C�����X�g��

	IMC_ITEM_BUFF* p_item_buff;		// BG�̕\�����f�[�^
} IMC_LEFT_BOX_INIT;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�p�̈�쐬
 *
 *	@param	lbox		���{�b�N�X�p�f�[�^
 *	@param	init		���{�b�N�X�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_InitSys( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�p�̈�j��
 *
 *	@param	lbox		�j�����鍶�{�b�N�X�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteSys( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���[�i���o�[���烊�X�g�i���o�[���擾
 *
 *	@param	mode			���[�h
 *	@param	accessorie_no	�A�N�Z�T���i���o�[
 *
 *	@return	int		�A�N�Z�T���[���X�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetListNo( int mode, int accessorie_no, IMC_ITEM_BUFF* p_item_buff );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���[�h�ƃA�N�Z�T���i���o�[����o�^����Ă����ׂ����W���擾
 *
 *	@param	mode			���[�h
 *	@param	accessorie_no	�A�N�Z�T���i���o�[
 *	@param	x				�����W�i�[��
 *	@param	y				�����W�i�[��
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_GetMat( int mode, int accessorie_no, int* x, int* y, int size_x, int size_y, IMC_ITEM_BUFF* p_item_buff );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̐V�K�ǉ�
 *
 *	@param	lbox				���{�b�N�X�p�f�[�^
 *	@param	mode				�A�N�Z�T�����[�h
 *	@param	accessorie_no		�ǉ�����A�N�Z�T���i���o�[
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,		// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_OBJLIST_ACCE_MAX		// ���[�h�ő吔
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AddAccessorie( IMC_LEFT_BOX* lbox, int mode, int accessorie_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���̈ړ��ǉ�
 *
 *	@param	lbox		���{�b�N�X�p�f�[�^
 *	@param	acce_obj	�A�N�Z�T���f�[�^
 *	@param	mode		�A�N�Z�T�����[�h
 *	@param	list_num	�o�^���郊�X�g
 *
 *	@return	none
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AddAccessorieMove( IMC_LEFT_BOX* lbox, int mode, int list_num, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���I�u�W�F�j��
 *
 *	@param	acce_obj	�j������A�N�Z�T��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorie( IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ړ������邽�߂̃��X�g����̍폜
 *
 *	@param	acce_obj	�ړ������邽�߂Ƀ��X�g����폜����A�N�Z�T���f�[�^
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorieMove( IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���A�N�Z�T���S�Ă��͂�
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorieAll( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����X�g�S�Ă̍��W�𓮂���
 *
 *	@param	lbox		���{�b�N�X
 *	@param	mode		���[�h
 *	@param	list_no		���X�g�i���o�[
 *	@param	x			�����������W
 *	@param	y			�����������W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AccessorieListMove( IMC_LEFT_BOX* lbox, int mode, int list_no, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���{�b�N�X�A�N�Z�T���̕\���D�揇��ݒ�
 *
 *	@param	lbox	���u���b�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_SetAccessoriePriority( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 * �������ŃG�t�F�N�g���s���܂��B
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g��ύX
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	list_num		�ݒ肷��J�����g�A�N�Z�T�����X�g
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_LBOX_FADELIST_MODE	// �t�F�[�h���p���X�g	list_num�͂O�Œ�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_ChangeCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num );

//----------------------------------------------------------------------------
/**
 * �������ŃG�t�F�N�g���s���܂��B
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g�̑����Z
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	add_mode		�������[�h
 *
 *	@retval	TRUE			����
 *	@retval	FALSE			���s
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_LBOX_FADELIST_MODE	// �t�F�[�h���p���X�g	list_num�͂O�Œ�

	add_mode
		IMC_LBOX_ADD_ONE,		// +1
		IMC_LBOX_SUB_ONE,		// -1
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_AddCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int add_mode );

//----------------------------------------------------------------------------
/**
 *
 * ���G�t�F�N�g�Ȃ�
 *
 *	@brief	�J�����g�A�N�Z�T�����X�g��ݒ�
 *
 *	@param	lbox			���{�b�N�X�f�[�^
 *	@param	mode			�A�N�Z�T�����[�h
 *	@param	list_num		�ݒ肷��J�����g�A�N�Z�T�����X�g
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_LBOX_FADELIST_MODE	// �t�F�[�h���p���X�g	list_num�͂O�Œ�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_SetCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�������{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	lbox		���{�b�N�X�f�[�^
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_TPHit( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w����W�����{�b�N�X�ɓ������Ă邩�`�F�b�N
 *
 *	@param	lbox		���{�b�N�X�f�[�^
 *	@param	x			���肘���W
 *	@param	y			���肙���W
 *
 *	@retval	TRUE		�q�b�g
 *	@retval	FALSE		��q�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_TPHitSelf( IMC_LEFT_BOX* lbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����s��
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	none
 *
 *	�J�����g�A�N�Z�T�����X�g���`�F�b�N���܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_LBOX_TPHitAccessorie( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T�����Ƃ̓����蔻����ׂ����s��
 *
 *	@param	lbox	���{�b�N�X
 *	@param	offset_x	�I�t�Z�b�g�����W
 *	@param	offset_y	�I�t�Z�b�g�����W
 *	@param	SWSP_UPchar	�L�����N�^���\�[�X�e�[�u��
 *
 *	@return	none
 *
 *	�J�����g�A�N�Z�T�����X�g���`�F�b�N���܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_LBOX_TPHitAccessorieEx( IMC_LEFT_BOX* lbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG��\��
 *
 *	@param	rbox		���{�b�N�X
 *	@param	bg_num		���{�b�N�XBG�i���o�[
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGSet( IMC_LEFT_BOX* lbox, int bg_num );

//----------------------------------------------------------------------------
/**
 * ���G�t�F�N�g�t��
 *
 *	@brief	���{�b�N�X�w�i��ύX
 *
 *	@param	lbox		���{�b�N�f�[�^
 *	@param	bg_num		�ύX���BG�i���o�[
 *	@param	fade_way	�t�F�[�h����
 *	@param	sync		���V���N�ōs����
 *	@param	end_flg		�I�����m�t���O
 *
 *	@return	none
 *
 * fade_way
	IMC_LBOX_FADE_X = 1,
	IMC_LBOX_FADE_Y = 2
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGChange( IMC_LEFT_BOX* lbox, int bg_num, int fade_way, int sync, BOOL* end_flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG���N���[������
 *
 *	@param	lbox		���{�b�N�X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGClean( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���݂̃��[�h
 *
 *	@param	lbox	���{�b�N�X
 *
 *	@return	�A�N�Z�T�����[�h
 *
 * mode
	IMC_OBJLIST_ACCE,		// �A�N�Z�T���^�C�v
	IMC_OBJLIST_BG,			// BG�T���l�C���^�C�v
	IMC_OBJLIST_SND,		// �T�E���h�T���l�C���^�C�v
	IMC_LBOX_FADELIST_MODE	// �t�F�[�h���p���X�g	list_num�͂O�Œ�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetMode( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���[�h���Ƃ̃J�����g�_�~�[�e�[�u���i���o�[���擾
 *
 *	@param	lbox	���{�b�N�X�f�[�^
 *	@param	mode	���ׂ������[�h
 *	
 *	@return	�J�����g�_�~�[�e�[�u���i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetCurrentNo( IMC_LEFT_BOX* lbox, int mode  );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�_�~�[�e�[�u�������擾
 *
 *	@param	lbox		���{�b�N�X�I�u�W�F
 *	@param	mode		�A�N�Z�T�����[�h
 *
 *	@return	�_�~�[�e�[�u����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetDummyTblNum( IMC_LEFT_BOX* lbox, int mode );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����{�b�N���󂵂Ă悢��ԂȂ̂����`�F�b�N
 *
 *	@param	lbox	���{�b�N�X�f�[�^
 *
 *	@retval	TRUE	OK
 *	@retval FALSE	NG		�t�F�[�h���ł�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_ENDCheck( IMC_LEFT_BOX* lbox );
	
#undef	GLOBAL
#endif		// __IMC_LEFT_BOX_H__
