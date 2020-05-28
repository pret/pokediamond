//=============================================================================================
/**
 * @file	fontdata_man.c
 * @brief	�t�H���g�f�[�^�}�l�[�W��
 * @author	taya
 * @date	2005.09.14
 *
 * @li	ntrfont.exe �ō쐬�����t�H���g�f�[�^���Ǘ�����}�l�[�W��
 */
//=============================================================================================
#ifndef __FONTDATA_MAN_H__
#define __FONTDATA_MAN_H__


#include "fontdata_loadtype.h"

typedef struct _GF_FONTDATA_MAN  GF_FONTDATA_MAN;


//==============================================================================================
/**
 * �t�H���g�f�[�^�}�l�[�W���쐬
 *
 * @param   arcID			�t�H���g�f�[�^���i�[����Ă���A�[�J�C�uID
 * @param   datID			�t�H���g�f�[�^���i�[����Ă���A�[�J�C�u���t�@�C��ID
 * @param   loadType		�t�H���g�f�[�^�̓ǂݏo������
 * @param   fixedFontFlag	TRUE�Ȃ瓙���t�H���g�Ƃ��Ĉ���
 * @param   heapID			�}�l�[�W���쐬��q�[�vID
 *
 * @retval  GF_FONTDATA_MAN*	�t�H���g�f�[�^�}�l�[�W���|�C���^
 *
 * @li  loadType �� FONTDATA_LOADTYPE_ON_MEMORY �̏ꍇ�A�}�l�[�W���Ɠ����q�[�v�̈�Ƀt�H���g�f�[�^��ǂݍ���
 */
//==============================================================================================
extern GF_FONTDATA_MAN* FontDataMan_Create( u32 arcID, u32 datID, FONTDATA_LOADTYPE loadType, BOOL fixedFontFlag, u32 heapID );


//==============================================================================================
/**
 * �t�H���g�f�[�^�}�l�[�W���폜
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W���̃|�C���^
 *
 */
//==============================================================================================
extern void FontDataMan_Delete( GF_FONTDATA_MAN* wk );


//==============================================================================================
/**
 * �t�H���g�r�b�g�f�[�^�̓ǂݍ��݃^�C�v��ύX����
 *
 * @param   wk			�t�H���g�f�[�^�}�l�[�W���|�C���^
 * @param   loadType	�ύX��̓ǂݍ��݃^�C�v
 *
 */
//==============================================================================================
extern void FontDataMan_ChangeLoadType( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID );


//------------------------------------------------------------------
/*
 *	�����r�b�g�}�b�v�f�[�^�擾
 *
 * @param	wk			�t�H���g�f�[�^�}�l�[�W��
 * @param	fcode		�����R�[�h
 * @param	dst			�r�b�g�}�b�v�擾���[�N
 *
 */
//------------------------------------------------------------------
extern void FontDataMan_GetBitmap( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );


//------------------------------------------------------------------
/**
 * ��������r�b�g�}�b�v���������̒����i�h�b�g�j���v�Z���ĕԂ�
 *
 * @param   wk		�t�H���g�f�[�^�}�l�[�W��
 * @param   str		������
 * @param   margin	���ԁi�h�b�g�j
 *
 * @retval  u32		����
 */
//------------------------------------------------------------------
extern u32 FontDataMan_GetStrWidth( const GF_FONTDATA_MAN* wk, const STRCODE* str, u32 margin );

#endif
