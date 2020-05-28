//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_res.h
 *@brief	�Z���A�N�^�[���[�e�B���e�B�V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 * ���̃V�X�e���́ACLACT���ȒP�Ɏg�p�ł���悤���\�[�X���Ǘ�����
 * �V�X�e�����܂Ƃ߂����ł��B
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __CLACT_UTIL_RES_H__
#define __CLACT_UTIL_RES_H__

#include "nnsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_RES_H_GLOBAL
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
//	���\�[�X�^�C�v��
//	
//=====================================
enum{
	CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
	CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
	CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
	CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
	CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
	CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
	CLACT_U_RES_MAX			// �ő�
};

//-------------------------------------
//	�o�C�i���f�[�^����R�[�h
//=====================================
// "e"�o�C�i���f�[�^�̏I���R�[�h
#define CLACT_U_RES_HEADER_MAKE_END_CODE	(0xfffffffe)

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	���\�[�X�}�l�[�W���[�Ǘ��\����
//	
//=====================================
typedef struct _CLACT_U_RES_MANAGER* CLACT_U_RES_MANAGER_PTR;
typedef const struct _CLACT_U_RES_MANAGER* CONST_CLACT_U_RES_MANAGER_PTR;

//-------------------------------------
//	
//	���\�[�X�}�l�[�W���[�I�u�W�F�N�g�\����
//	
//=====================================
typedef struct _CLACT_U_RES_OBJ* CLACT_U_RES_OBJ_PTR;
typedef const struct _CLACT_U_RES_OBJ* CONST_CLACT_U_RES_OBJ_PTR;

//-------------------------------------
//	
//	���\�[�X�}�l�[�W���I�u�W�F�e�[�u��
//	�\����
//
//	�w�b�_�[�����C�ɕ�����
//	���\�[�X��ǂݍ��ގ��̈����Ɏg�p
//
//	�ǂݍ��񂾃��\�[�X�̃I�u�W�F��ۑ�����
//	
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
	int		tbl_num;			// �e�[�u���v�f��
	int		tbl_now;			// ���݊i�[��
} CLACT_U_RES_OBJ_TBL;


//-------------------------------------
//	
//	���\�[�X�}�l�[�W���[�w�b�_�[�\����
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER* CLACT_U_RES_HEADER_PTR;
typedef const struct _CLACT_U_RES_HEADER* CONST_CLACT_U_RES_HEADER_PTR;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�Ǘ��}�l�[�W���[������
 *
 *@param	tbl_num			�f�[�^�o�^��
 *@param	res_type		���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	CLACT_RES_MANAGER_PTR	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_MANAGER_PTR CLACT_U_ResManagerInit(int tbl_num, int res_type, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�̔j��
 *
 *@param	resm	���\�[�X�}�l�[�W���[
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerDelete(CLACT_U_RES_MANAGER_PTR resm);



//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddChar(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	pltt_num		�p���b�g�ǂݍ��ݖ{��
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddPltt(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int pltt_num, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	path			�t�@�C���p�X
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p�q�[�v
 * 
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddKindCell(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int type,  int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	pltt_num		�p���b�g�ǂݍ��ݖ{��
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int type, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̃��\�[�X�ύX
 *
 *@param	resm			�L�����N�^�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p�q�[�v
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcChar(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�p���b�g�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcPltt(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�ύX���郊�\�[�X�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcFile			�A�[�J�C�u�t�@�C��ID
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcKindCell(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int type, int heap);

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̓o�^
 *
 *@param	resm			�L�����N�^�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type);

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�p���b�g�f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	vram			�u�������^�C�v
 *@param	pltt_num		�p���b�g�ǂݍ��ݖ{��
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type);

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̓o�^
 *
 *@param	resm			�p���b�g�p�ɍ쐬�������\�[�X�}�l�[�W���[
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	id				�Ǘ��h�c		�i�d�����Ȃ��悤�Ƀ��[�U�[���ݒ�j
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p�q�[�v
 *
 *@return	CLACT_U_RES_OBJ_PTR	���\�[�X�I�u�W�F�|�C���^
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int type, int heap);

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�A�[�J�C�u���ꂽ�L�����N�^�f�[�^�̃��\�[�X�ύX
 *
 *@param	resm			�L�����N�^�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p�q�[�v
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap);


//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�p���b�g�f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�p���b�g�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap);

//----------------------------------------------------------------------------
/**
 * ���A�[�J�C�u�n���h������
 *
 *@brief	�Z���A�Z���A�j���A�}���`�Z���A�}���`�Z���A�j���f�[�^�̃��\�[�X��ύX
 *
 *@param	resm			�ύX���郊�\�[�X�p���\�[�X�}�l�[�W���|�C���^
 *@param	resObj			�ύX���郊�\�[�X�I�u�W�F
 *@param	arcHandle		�A�[�J�C�u�t�@�C���n���h��
 *@param	detaIdx			�f�[�^�C���f�b�N�X
 *@param	compFlag		���k����Ă��邩	(TRUE ���k  �@�@FALSE �񈳏k)
 *@param	type			���\�[�X�^�C�v
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int type, int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ��ށi�P���j
 *
 *@param	resm	���\�[�X�}�l�[�W���[
 *@param	head	�ǂݍ��񂾃w�b�_�[
 *@param	no		�w�b�_�[�̉��Ԗڂ�ǂݍ��ނ�
 *@param	heap	�g�p����q�[�v
 *
 *@return	�ǂݍ��񂾃f�[�^
 *
 * �w�b�_����
 *	�w�b�_�t�@�C���́A"�t�@�C���^�C�v��"��"�f�[�^��"�ɕ�����܂��B
 *	"�t�@�C���^�C�v���̎��̍s����f�[�^���Ƃ��ăf�[�^���L�����܂��B"
 *	�܂��I�����ɂ�,'e'�����������Ȃ�������"�I���R�[�h"�ƂȂ�܂��B
 *	"e,e,e,e"	<-��������
 *	
 *	
 *	"��"�t�@�C���^�C�v��
 *	"���\�[�X�^�C�v , �A�[�J�C�u�f�[�^�t���O(0:��A�[�J�C�u	1:�A�[�J�C�u)"
 *	
 *	"��"�f�[�^��
 *	�f�[�^���̓��\�[�X�^�C�v���ω����܂��B
 *	�E���\�[�X�^�C�v��0=	"�L�����N�^"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v(1=MAIN 2=SUB 3=����)"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v"
 *	"e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O(0=�񈳏k 1=���k),�Ǘ�ID,Vram�^�C�v"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID,Vram�^�C�v"
 *	"e,e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��1=	"�p���b�g"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"e,e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"e,e,e,e,e,e"
 *	
 *	�E���\�[�X�^�C�v��2=	"�Z��"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��3=	"�Z���A�j��"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��4=	"�}���`�Z��"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��5=	"�}���`�Z���A�j��"
 *	�E�A�[�J�C�u�t���O��0=	"��A�[�J�C�u"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *	�E�A�[�J�C�u�t���O��1=	"�A�[�J�C�u"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"�A�[�J�C�u�t�@�C��idx,�A�[�J�C�u�f�[�^idx,���k�t���O,�Ǘ�ID"
 *	"e,e,e,e"
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int no, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ���(����)
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *@param	head		�w�b�_�[
 *@param	p_ro_tbl	�������m�ۍς݃��\�[�X�I�u�W�F�e�[�u��
 *@param	heap		�g�p����q�[�v
 *
 *@return	int			�o�^��
 *
 * CLACT_U_RES_OBJ_TBL*�̐���
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
	�쐬���Ă���n���Ă��������B
	�ǂݍ��񂾂�\�[�X�̃I�u�W�F�N�g�|�C���^	CLACT_U_RES_OBJ_PTR	��ۑ����܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerResAddsHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, CLACT_U_RES_OBJ_TBL* p_ro_tbl, int heap );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�f�[�^���w�b�_�[����ǂݍ���(�ǂݍ��ސ����w��)
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *@param	head		�w�b�_�[
 *@param	start		�ǂݍ��݊J�n�e�[�u���i���o�[
 *@param	num			�ǂݍ��ݐ�
 *@param	p_ro_tbl	�������m�ۍς݃��\�[�X�I�u�W�F�e�[�u��
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 * �w�b�_����start����num����ǂݍ��݂܂�
 * 
 * 
 * CLACT_U_RES_OBJ_TBL*�̐���
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// �|�C���^���i�[����e�[�u���̃|�C���^
		int		tbl_num;			// �e�[�u���v�f��
		int		tbl_now;			// ���݊i�[��
	} CLACT_U_RES_OBJ_TBL;
	��̍\���̂����̊֐��ō쐬�ł��܂��B
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
	�쐬���Ă���n���Ă��������B
	�ǂݍ��񂾂�\�[�X�̃I�u�W�F�N�g�|�C���^	CLACT_U_RES_OBJ_PTR	��ۑ����܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResAddsHdEx(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int start, int num, CLACT_U_RES_OBJ_TBL* p_ro_tbl,int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�i�[�p�e�[�u�����쐬
 *			���̃e�[�u�����g�p���A���\�[�X�f�[�^�̕����ǂݍ��݂ɂ��Ή�����
 *
 *@param	inResObjNum		���ɓo�^����f�[�^��
 *@param	heap			�������m�ۃq�[�v
 *
 *@return	CLACT_U_RES_OBJ_TBL*	�쐬�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�i�[�p�e�[�u���j��
 *
 *
 *@param	data		�j�����郊�\�[�X�I�u�W�F�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResObjTblDelete(CLACT_U_RES_OBJ_TBL* data);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�c��o�^�\���擾
 *
 *@param	resm		���\�[�X�}�l�[�W���[�|�C���^
 *
 *@return	int		�c��o�^�\��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerRest(CLACT_U_RES_MANAGER_PTR resm);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃f�[�^�����邩�`�F�b�N
 *
 *@param	resm	���\�[�X�}�l�[�W��
 *@param	id		�`�F�b�N����ID
 *
 *@retval	TRUE	ID�̃f�[�^������
 *@retval	FALSE	ID�̃f�[�^������
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_ResManagerCheckID(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���\�[�X�I�u�W�F���̓ǂݍ���ł����f�[�^�̂ݔj��
 *			ID�⃊�\�[�X�^�C�v�Ȃǂ̏��͕ێ������܂�
 *
 *	@param	res_obj		���\�[�X�I�u�W�F
 *
 *	@return	none
 *
 * ���̊֐����ĂԂ�Vram�ւ̃��\�[�X�̓]���Ȃǂ��s���Ȃ��Ȃ�܂��B
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResOnlyDelete( CLACT_U_RES_OBJ_PTR res_obj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�S�f�[�^�j��
 *
 *@param	resm		�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *@param	res_obj		���\�[�X�I�u�W�F
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResDelete(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR res_obj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�S�j��
 *
 *@param	resm		�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���[�|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResDeleteAll(CLACT_U_RES_MANAGER_PTR resm);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ID�̃��\�[�X���擾
 *
 *@param	id		�擾���郊�\�[�X�I�u�W�F�|�C���^�ɐݒ肳��Ă���Ǘ��h�c
 *	
 *@return	CLACT_U_RES_OBJ_PTR		���\�[�X�I�u�W�F�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F����h�c���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		�Ǘ��h�c
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjID(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɂh�c��ݒ�
 *
 *@param	resm	�ύX����I�u�W�F�̓o�^����Ă��郊�\�[�X�}�l�[�W��
 *@param	resObj	���\�[�X�I�u�W�F
 *@param	id		�ݒ肷��ID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjID(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int id);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�̃��\�[�X���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	void*	���\�[�X�|�C���^
 *
 * ���̃|�C���^�̒��g�������A���p�b�N���Ă��邽�߁A�A���p�b�N�֎~�ł��B
 * �A���p�b�N�ς݃t�@�C�����擾����֐���p�ӂ��Ă��邽�߁A
 * ��������g�p���Ă��������B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void* CLACT_U_ResManagerGetResObjRes(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�L�����N�^���\�[�X�I�u�W�F
 *
 *@return	�L�����N�^���\�[�X�f�[�^
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCharacterData* CLACT_U_ResManagerGetResObjResChar(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�p���b�g���\�[�X�I�u�W�F
 *
 *@return	�p���b�g���\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dPaletteData* CLACT_U_ResManagerGetResObjResPltt(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�Z�����\�[�X�I�u�W�F
 *
 *@return	�Z�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCellDataBank* CLACT_U_ResManagerGetResObjResCell(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�j���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�Z���A�j�����\�[�X�I�u�W�F
 *
 *@return	�Z���A�j�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCellAnimBankData* CLACT_U_ResManagerGetResObjResCellAnm(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�}���`�Z�����\�[�X�I�u�W�F
 *
 *@return	�}���`�Z�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dMultiCellDataBank* CLACT_U_ResManagerGetResObjResMultiCell(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	�}���`�Z���A�j���f�[�^���擾	���\�[�X�f�[�^���A���p�b�N���Ă���擾
 *
 *@param	resObj	�}���`�Z���A�j�����\�[�X�I�u�W�F
 *
 *@return	�}���`�Z���A�j�����\�[�X�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dMultiCellAnimBankData* CLACT_U_ResManagerGetResObjResMultiCellAnim(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă��郊�\�[�X�̃^�C�v���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		���\�[�X�^�C�v
 *
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjResType(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���Vram�^�C�v���擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		Vram�^�C�v�i�L�����N�^�B�p���b�g���̂݁j
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjVramType(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���p���b�g�ǂݍ��ݐ����擾
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *	
 *@return	int		�p���b�g�ǂݍ��ݖ{���i�p���b�g���̂݁j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjPlttNum(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F��Vram�^�C�v��ݒ�
 *
 *@param	resobj	���\�[�X�I�u�W�F
 *@param	vram	vram�^�C�v	���C��:1	�T�u:2	����:3
 *	
 *@return	none
 *
 * Vram�^�C�v
	main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
	sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	�����ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjVramType(CLACT_U_RES_OBJ_PTR resObj, int vram);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�I�u�W�F�ɐݒ肳��Ă���p���b�g�ǂݍ��ݐ���ݒ�
 *
 *@param	resObj	���\�[�X�I�u�W�F
 *@param	pltt	�p���b�g�ǂݍ��ݖ{��
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjPlttNum(CLACT_U_RES_OBJ_PTR resObj, int pltt);


//-----------------------------------------------------------------------------
//
//
//			�w�b�_�[�V�X�e��
//
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�w�b�_�[�T�C�Y���擾
 *
 *@param	none
 *
 *@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetHeaderSize(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�w�b�_�[��z��Ŋm�ۂ����Ƃ��̊e�v�f���̃f�[�^��
 *			�擾����֐�
 *
 *@param	head	�w�b�_�[�f�[�^�i�z��j
 *@param	no		�v�f��
 *
 *@return	CLACT_U_RES_HEADER_PTR
 *
 * no���z��̗v�f�����傫�����A�s���ȃ|�C���^��Ԃ��Ă��܂��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_HEADER_PTR CLACT_U_ResManagerGetHeaderNoData(CLACT_U_RES_HEADER_PTR head, int no);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���w�b�_�[�ǂݍ���
 *
 *@param	path		�w�b�_�[�t�@�C���p�X
 *@param	head		�w�b�_�[�i�[��
 *@param	type		���\�[�X�^�C�v
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 * �w�b�_����
 *	�w�b�_�t�@�C���́A"�t�@�C���^�C�v��"��"�f�[�^��"�ɕ�����܂��B
 *	"�t�@�C���^�C�v���̎��̍s����f�[�^���Ƃ��ăf�[�^���L�����܂��B"
 *	�܂��I�����ɂ�,'e'��4�Ȃ�������"�I���R�[�h"�ƂȂ�܂��B
 *	"e,e,e,e"
 *	
 *	"��"�t�@�C���^�C�v��
 *	"���\�[�X�^�C�v , �A�[�J�C�u�f�[�^�t���O(0:��A�[�J�C�u	1:�A�[�J�C�u)"
 *	
 *	"��"�f�[�^��
 *	�f�[�^���̓��\�[�X�^�C�v���ω����܂��B
 *	�E���\�[�X�^�C�v��0=	"�L�����N�^"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v(1=MAIN 2=SUB 3=����)"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��1=	"�p���b�g"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"�t�@�C���p�X,�Ǘ�ID,Vram�^�C�v,�p���b�g�ǂݍ��ݐ�"
 *	"e,e,e,e"
 *	
 *	�E���\�[�X�^�C�v��2=	"�Z��"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��3=	"�Z���A�j��"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��4=	"�}���`�Z��"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 *
 *	�E���\�[�X�^�C�v��5=	"�}���`�Z���A�j��"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"�t�@�C���p�X,�Ǘ�ID"
 *	"e,e,e,e"
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderLoad(const char* path, CLACT_U_RES_HEADER_PTR head,int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	�Z���A�N�^�[���[�e�B���e�B���\�[�X�}�l�[�W���o�C�i���w�b�_�[�ǂݍ���
 *
 *@param	cp_bindata		�o�C�i���f�[�^
 *@param	head			�w�b�_�[�i�[��
 *@param	heap			�g�p����q�[�v
 *
 *@return	none
 *
 * Binary�f�[�^����		�S�f�[�^4byte��؂�
 *	���\�[�X�^�C�v				(0�`5)
 *	�A�[�J�C�u�t�@�C��idx		(arc_tool.dat�ɒ�`����Ă��镨)
 *	�f�[�^idx					(naix�ɒ�`����Ă��镨)
 *	���k�t���O					(���k1	�񈳏k0)
 *	�Ǘ�ID						
 *	����Vram�^�C�v				(1=MAIN 2=SUB 3=����)
 *	  ���p���b�g�ǂݍ��ݖ{��	(1�`16)
 *
 * ���L�����N�^���\�[�X�̎�		(���̑��̎��̓_�~�[�f�[�^ = ���ł�OK)
 * ���p���b�g���\�[�X�̎�		(���̑��̎��̓_�~�[�f�[�^ = ���ł�OK)
 *
 * ��j
 *		���\�[�X�^�C�v	
 *		0x00000001		
 *		�A�[�J�C�uidx	�f�[�^idx		���k�t���O
 *		0x00000000		0x00000000		0x00000000
 *		�Ǘ�ID			vram�^�C�v		�p���b�g�ǂݍ��ݖ{��
 *		0x00000000		0x00000002		0x00000001
 *		�A�[�J�C�uidx	�f�[�^idx		���k�t���O
 *		0x00000000		0x00000001		0x00000000
 *		�Ǘ�ID			vram�^�C�v		�p���b�g�ǂݍ��ݖ{��
 *		0x00000001		0x00000002		0x00000001
 *		<�I���R�[�h>
 *		�A�[�J�C�uidx	�f�[�^idx		���k�t���O
 *		0xfffffffe		0xfffffffe		0xfffffffe		
 *		�Ǘ�ID			vram�^�C�v		�p���b�g�ǂݍ��ݖ{��
 *		0xfffffffe		0xfffffffe		0xfffffffe		
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderLoadBinary(const void* cp_bindata, CLACT_U_RES_HEADER_PTR head,int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���w�b�_�[�j��
 *
 *@param	head		�w�b�_�[�|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderFree(CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^���擾
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int		�ǂݍ��܂�Ă���f�[�^��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataNum(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^�̃��\�[�X�^�C�v���擾
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int		���\�[�X�^�C�v
 *
 * ���\�[�X�^�C�v
	enum{
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
		CLACT_U_MULTI_RES,		// �}���`�Z�����\�[�X���Ǘ�
		CLACT_U_MULTIANM_RES,	// �}���`�Z���A�j�����\�[�X���Ǘ�
		CLACT_U_RES_MAX			// �ő�
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataResType(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���\�[�X�}�l�[�W���[�w�b�_�[�ɓǂݍ��܂�Ă���f�[�^�̓A�[�J�C�u����Ă��邩
 *
 *@param	head		���\�[�X�w�b�_
 *
 *@return	int			0�F����ĂȂ�	1�F����Ă�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataArc(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^��ύX���� �֐��S
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *	@param	param		�ݒ肷��l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderDataIDSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderArcFileSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderDataIdxSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderCompFlagSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderVramTypeSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderPlttNumSet( CLACT_U_RES_HEADER_PTR head, int no, int param );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w�b�_�ɓo�^����Ă���f�[�^���擾����	�֐��S
 *
 *	@param	head		���\�[�X�w�b�_�[
 *	@param	no			���\�[�X�w�b�_�[���ɓo�^����Ă���f�[�^�i���o�[
 *
 *	@return	�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderDataIDGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderArcFileGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderDataIdxGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderCompFlagGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderVramTypeGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderPlttNumGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );

#undef	GLOBAL
#endif		// __CLACT_UTIL_RES_H__

