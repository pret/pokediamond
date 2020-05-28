//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_vram.h
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[���g�p���L�����N�^�f�[�^�p���b�g�f�[�^��Vram�ɓ]������V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __CLACT_UTIL_VRAM_H__
#define __CLACT_UTIL_VRAM_H__

#include "include/system/clact_util_res.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_VRAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define CLACT_U_PLTT_NO_NONE	(NNS_G2D_VRAM_ADDR_NOT_INITIALIZED)

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

//////////////////////////////////////////////////////////////////////////////
// �L�����N�^�f�[�^�]���֐�
// �G���A�R���g���[���^�C�v
// vram�G���A���P�L�������ƂɊǗ�����z����쐬���āA
// �󂫗̈悩��g�p�ł���vram�G���A���������܂��B
//
// �������܂��B
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 * CLACT_U_ResManagerResAddChar�֐��Ȃǂ̖߂�l
 * �ǂݍ��񂾃��\�[�X�̃f�[�^�@�Ǘ�ID�Ȃǂ��i�[����Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_TBL�@���\�[�X�I�u�W�F�e�[�u��
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSetsAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * NitroSystem�̓]���֐����ŁA�L�����N�^�n�a�i�}�b�s���O���[�h���W�X�^��ύX���Ă��āA
 * �QD�}�b�s���O���[�h�ŃR���o�[�g�����t�@�C�����PD�}�b�s���O���[�h�œǂݍ��݂����Ȃǂ�
 * �������������Ă��o���Ȃ��悤�ɂȂ��Ă��邽�ߍ쐬���܂����B
 *
 * ���̊֐����g�p����ƁA���̃}�b�s���O���[�h���擾���A���̃}�b�s���O���[�h�œ]������悤��
 * �L�����N�^�f�[�^�̒��g������������Ƃ����������s���āA�]�����������Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetCharModeAdjustAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 * NitroSystem�̓]���֐����ŁA�L�����N�^�n�a�i�}�b�s���O���[�h���W�X�^��ύX���Ă��āA
 * �QD�}�b�s���O���[�h�ŃR���o�[�g�����t�@�C�����PD�}�b�s���O���[�h�œǂݍ��݂����Ȃǂ�
 * �������������Ă��o���Ȃ��悤�ɂȂ��Ă��邽�ߍ쐬���܂����B
 *
 * ���̊֐����g�p����ƁA���̃}�b�s���O���[�h���擾���A���̃}�b�s���O���[�h�œ]������悤��
 * �L�����N�^�f�[�^�̒��g������������Ƃ����������s���āA�]�����������Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSetsCharModeAdjustAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl );


//////////////////////////////////////////////////////////////////////////////
// �L�����N�^�f�[�^�]���֐�
// �I�t�Z�b�g�^�C�v
// �ォ�珇�ɋl�߂�Vram�ɓ]�����Ă����܂��B
// ����������Ȃǂ��Ă���������̈��F�����āA
// ���̗̈�ɍēx�Ⴄ�L�����N�^��]������Ȃǂ��ł��܂���B
//
// ��{�I�ɂ́A���CLACT_U_CharManagerSetAreaCont�n�֐����g�p���Ă�������
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 * CLACT_U_ResManagerResAddChar�֐��Ȃǂ̖߂�l
 * �ǂݍ��񂾃��\�[�X�̃f�[�^�@�Ǘ�ID�Ȃǂ��i�[����Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_TBL�@���\�[�X�I�u�W�F�e�[�u��
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * NitroSystem�̓]���֐����ŁA�L�����N�^�n�a�i�}�b�s���O���[�h���W�X�^��ύX���Ă��āA
 * �QD�}�b�s���O���[�h�ŃR���o�[�g�����t�@�C�����PD�}�b�s���O���[�h�œǂݍ��݂����Ȃǂ�
 * �������������Ă��o���Ȃ��悤�ɂȂ��Ă��邽�ߍ쐬���܂����B
 *
 * ���̊֐����g�p����ƁA���̃}�b�s���O���[�h���擾���A���̃}�b�s���O���[�h�œ]������悤��
 * �L�����N�^�f�[�^�̒��g������������Ƃ����������s���āA�]�����������Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetCharModeAdjust(  CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃L�����N�^�f�[�^��ݒ�i�����j
 *				�}�b�s���O���[�h�����̏�ԂɕύX���郂�[�h
 *
 *@param	resTbl		���\�[�X�I�u�W�F�z��̃|�C���^
 *
 *@return	none
 *
 * NitroSystem�̓]���֐����ŁA�L�����N�^�n�a�i�}�b�s���O���[�h���W�X�^��ύX���Ă��āA
 * �QD�}�b�s���O���[�h�ŃR���o�[�g�����t�@�C�����PD�}�b�s���O���[�h�œǂݍ��݂����Ȃǂ�
 * �������������Ă��o���Ȃ��悤�ɂȂ��Ă��邽�ߍ쐬���܂����B
 *
 * ���̊֐����g�p����ƁA���̃}�b�s���O���[�h���擾���A���̃}�b�s���O���[�h�œ]������悤��
 * �L�����N�^�f�[�^�̒��g������������Ƃ����������s���āA�]�����������Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSetsCharModeAdjust( const CLACT_U_RES_OBJ_TBL* resTbl );




//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^��ύX����
 *
 *	@param	nowTbl		���̃L�����N�^�f�[�^
 *	@param	newTbl		�ύX����L�����N�^�f�[�^
 *
 *	@return	none
 *
 * nowTbl�̂���Vram��newTbl�̃L�����N�^�f�[�^��]�����܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowTbl, CONST_CLACT_U_RES_OBJ_PTR newTbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̍ē]�����s��
 *
 *	@param	resObj	���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃L�����N�^�f�[�^��j��
 *
 *@param	resObj		���\�[�X�I�u�W�F�|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerDelete( CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�}�l�W���[���烊�\�[�X�I�u�W�F�e�[�u���ɑΉ�����f�[�^��j��
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u��
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl );
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���[�W�v���N�V���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@return	NNSG2dImageProxy*	�C���[�W�v���N�V
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* CLACT_U_CharManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�QD�}�b�s���O���[�h�̃L�����N�^��ǂݍ���
 *
 *	@param	resObj		���\�[�X�I�u�W�F
 *	@param	proxy		�]���f�[�^���i�[����v���N�V
 *	@param	base_addr	Vram�x�[�X�A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_2DmapCharLoad( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* proxy, int base_addr );

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram�]���p�̃C���[�W�v���N�V���擾
 *
 *@param	charObj	�L�����N�^���\�[�X�I�u�W�F
 *@param	cellObj	�Z�����\�[�X�I�u�W�F
 *
 *@return	NNSG2dImageProxy*	�C���[�W�v���N�V
 *
 *	����Vram�̈���m�ۂ��Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* CLACT_U_CharManagerGetVramTransferProxy( CONST_CLACT_U_RES_OBJ_PTR charObj, CONST_CLACT_U_RES_OBJ_PTR cellObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z��Vram�]���A�j����Vram�̈���J��
 *
 *@param	pImage		Vram�]���p�ɍ쐬���ꂽ�C���[�W�v���N�V
 *
 *@return	none
 *
 * ����Vram�̈���J�����Ă��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerDeleteVramTransferProxy( const NNSG2dImageProxy* pImage );

// �󂫗̈���������ē]�����܂�
// �������A��̓]���֐����g�p���Ă��̌�ɓ]�������
// �㏑������܂��B
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�Ƀ��\�[�X�I�u�W�F���̃p���b�g�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 * CLACT_U_ResManagerResAddPltt�֐��Ȃǂ̖߂�l
 * �ǂݍ��񂾃��\�[�X�̃f�[�^�@�Ǘ�ID�Ȃǂ��i�[����Ă��܂��B
 *
 * �󂢂Ă����Ԃ��r�b�g����ŊǗ����Ă��܂��B
 * ��{���������g�p���Ă��������B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_PlttManagerSetCleanArea( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃p���b�g�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���|�C���^
 *
 *@return	none
 *
 * �󂢂Ă����Ԃ��r�b�g����ŊǗ����Ă��܂��B
 * ��{���������g�p���Ă��������B
 * 
 * CLACT_U_RES_OBJ_TBL�@���\�[�X�I�u�W�F�e�[�u��
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerSetsCleanArea( const CLACT_U_RES_OBJ_TBL* resTbl );



//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�[�W���[�Ƀ��\�[�X�I�u�W�F���̃p���b�g�f�[�^��ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s
 *
 * CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F
 * CLACT_U_ResManagerResAddPltt�֐��Ȃǂ̖߂�l
 * �ǂݍ��񂾃��\�[�X�̃f�[�^�@�Ǘ�ID�Ȃǂ��i�[����Ă��܂��B
 *
 * �I�t�Z�b�g���炵�Ő擪����p���b�g��ǉ����Ă����܂��B
 * �������A�p���b�g�g�p�֎~�̈�Ȃǂ̊Ǘ����s��Ȃ����߁A�������܂���
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_PlttManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[�Ƀ��\�[�X�I�u�W�F�Ȃ��̃p���b�g�f�[�^��ݒ�i�����j
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���|�C���^
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_TBL�@���\�[�X�I�u�W�F�e�[�u��
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 * �I�t�Z�b�g���炵�Ő擪����p���b�g��ǉ����Ă����܂��B
 * �������A�p���b�g�g�p�֎~�̈�Ȃǂ̊Ǘ����s��Ȃ����߁A�������܂���
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�ύX
 *
 *	@param	nowObj		���̃p���b�g�f�[�^�̃��\�[�X�I�u�W�F
 *	@param	newObj		�ύX����p���b�g�̃��\�[�X�I�u�W�F
 *
 *	@return	none
 *
 * nowTbl�̂���Vram��newTbl�̃p���b�g�f�[�^��]�����܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowObj, CONST_CLACT_U_RES_OBJ_PTR newObj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�̍ē]�����s��
 *
 *	@param	resObj	���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃p���b�g�f�[�^��j��
 *
 *@param	resObj		���\�[�X�I�u�W�F�|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerDelete( CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�}�l�W���[���烊�\�[�X�I�u�W�F��ID�̃p���b�g�f�[�^��j��
 *
 *@param	resTbl		���\�[�X�I�u�W�F�e�[�u���̃|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl );
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�v���N�V���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F�p�����[�^
 *@param	pImage	�֘A������C���[�W�v���N�V	�g���p���b�g�ȊO�̂Ƃ���NULL
 *
 *@return	�p���b�g�v���N�V
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL const NNSG2dImagePaletteProxy* CLACT_U_PlttManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* pImage );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�o�^����Ă���p���b�g�����Ԃ̃p���b�g�ɓ]������Ă��邩��Ԃ�
 *
 *	@param	resObj		���\�[�X�I�u�W�F
 *	@param	vram		vram�^�C�v
 *
 *	@retval	CLACT_U_PLTT_NO_NONE�ȊO	�]�����ꂽ�p���b�g�ԍ�
 *	@retval	CLACT_U_PLTT_NO_NONE		�p���b�g�]������Ă��Ȃ�
 *
 * vram�^�C�v
 *	NNS_G2D_VRAM_TYPE_2DMAIN    �Q�c�O���t�B�b�N�X�G���W���`�p
 *  NNS_G2D_VRAM_TYPE_2DSUB     �Q�c�O���t�B�b�N�X�G���W���a�p
 *
 * resObj
 *	GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);
 *	�֐��Ŏ擾���Ă��������B
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_U_PlttManagerGetPlttNo( CONST_CLACT_U_RES_OBJ_PTR resObj, NNS_G2D_VRAM_TYPE type );


#undef	GLOBAL
#endif		// CLACT_UTIL_VRAM_H__

