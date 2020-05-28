//============================================================================================
/**
 * @file	bmp_menu_list.h
 * @brief	bmp_menu �� bmp_list �Ŏg�p����\���̂̒�`
 * @author	taya
 * @date	2005.12.02
 *
 * bmp_menu �� bmp_list �őS�������^�E�����p�r�̍\���̂�ʌɒ�`���Ă���̂ł܂Ƃ߂Ă����B
 *
 * �������Ă����΁A���̍\���̂𓮓I�ɐ�������֐��ȂǁA���ʂ̂��̂��Ăяo����B
 *
 * ����ɁA���̕����z��iSTRCODE = u16�j���g�p���Ă���ӏ���STRBUF�^�ɒu�����������A
 * �����̒�`�݂̂�����������Ηǂ��B
 *
 */
//============================================================================================

#ifndef __BMP_MENU_LIST_H__
#define __BMP_MENU_LIST_H__

#include "gflib/strbuf.h"
#include "system/msgdata.h"

//------------------------------------------------------------------------------------
/**
 *	���j���[�\���p�̕�����ƁA���ꂪ�I�����ꂽ���̃p�����[�^�l���`���邽�߂̍\���́B
 */
//------------------------------------------------------------------------------------
struct _BMP_MENULIST_DATA {
	const void * str;
	u32	param;
};


// �ǂ����������^�Ƃ��Ē�`���Ă������ƂŁA�ȉ��̋��ʊ֐��Q���Ăяo����
typedef	struct _BMP_MENULIST_DATA		BMP_MENULIST_DATA, BMPLIST_DATA, BMPMENU_DATA;



//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@���쐬
 *
 * @param   maxElems		���X�g�ɓo�^���镶����̍ő吔
 * @param   heapID			���X�g�쐬��q�[�vID
 *
 * @retval  BMP_MENULIST_DATA*		�쐬���ꂽ���X�g�o�b�t�@
 */
//------------------------------------------------------------------
extern BMP_MENULIST_DATA*  BMP_MENULIST_Create( u32 maxElems, u32 heapID );


//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@��j������
 * ��BMP_MENULIST_Create�ō쐬�������̈ȊO��n���Ă̓_���B
 *
 * @param   list		���X�g�o�b�t�@
 */
//------------------------------------------------------------------
extern void BMP_MENULIST_Delete( BMP_MENULIST_DATA* list );


//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@�ɕ����񁕃p�����[�^���Z�b�g����i�}�l�[�W������ăA�[�J�C�u�f�[�^����ǂݍ��݁j
 *
 * @param   list		[in] ���X�g�o�b�t�@
 * @param   man			[in] ���b�Z�[�W�f�[�^�}�l�[�W��
 * @param   strID		������ID
 * @param   param		������p�����[�^
 */
//------------------------------------------------------------------
extern void BMP_MENULIST_AddArchiveString( BMP_MENULIST_DATA* list, const MSGDATA_MANAGER* man, u32 strID, u32 param );


//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@�ɕ����񁕃p�����[�^���Z�b�g����i������𒼐ڎw�肷��j
 *
 * @param   list		[in] ���X�g�o�b�t�@
 * @param   str			[in] ������
 * @param   param		������p�����[�^
 *
 */
//------------------------------------------------------------------
extern void BMP_MENULIST_AddString( BMP_MENULIST_DATA* list, const STRBUF* str, u32 param );

//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@�ɑ��̃��X�g�̃f�[�^��Link����
 * @param   list		[inout] ���X�g�o�b�t�@
 * @param   insList		[in] ���X�g�|�C���^
 *
 */
//------------------------------------------------------------------
extern void BMP_MENULIST_AddLinkList( BMP_MENULIST_DATA* list, const BMP_MENULIST_DATA* insList );

//------------------------------------------------------------------
/**
 * ���X�g�o�b�t�@��STRBUF��j������
 * ��BMP_MENULIST_Create�ō쐬�������̈ȊO��n���Ă̓_���B
 *
 * @param   list		���X�g�o�b�t�@
 *
 */
//------------------------------------------------------------------
extern void BMP_MENULIST_STRBUFDelete( BMP_MENULIST_DATA* list_top );

#endif
