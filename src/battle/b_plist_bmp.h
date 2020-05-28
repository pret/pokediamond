//============================================================================================
/**
 * @file	b_plist_bmp.h
 * @brief	�퓬�p�|�P�������X�g���BMP�֘A
 * @author	Hiroyuki Nakamura
 * @date	05.02.01
 */
//============================================================================================
#ifndef B_PLIST_BMP_H
#define B_PLIST_BMP_H
#undef GLOBAL
#ifdef B_PLIST_BMP_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_BmpInit( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W���Ƃ�BMP�E�B���h�E�ǉ�
 *
 * @param	wk		���[�N
 * @param	page	�y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_BmpAdd( BPLIST_WORK * wk, u32 page );

//--------------------------------------------------------------------------------------------
/**
 * �ǉ�BMP�E�B���h�E�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_BmpFree( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�S�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_BmpFreeAll( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * BMP��������
 *
 * @param	wk		���[�N
 * @param	page	�y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_BmpWrite( BPLIST_WORK * wk, u32 page );

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_TalkMsgSet( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�\���J�n
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_TalkMsgStart( BPLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * HP�\�� & HP�Q�[�W�\��
 *
 * @param	wk		���[�N
 * @param	pos		�|�P�����ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BattlePokeList_P1_HPPut( BPLIST_WORK * wk, u8 pos );

GLOBAL void BattlePokeList_P1_LvPut( BPLIST_WORK * wk, u8 pos );

GLOBAL void BattlePokeList_PPRcv( BPLIST_WORK * wk, u16 widx, u16 pos );

GLOBAL void BPL_HidenMsgPut( BPLIST_WORK * wk );

GLOBAL void BattlePokeList_ItemUseMsgSet( BPLIST_WORK * wk );

GLOBAL void BattlePokeList_ItemUseSkillErrMsgSet( BPLIST_WORK * wk );


#undef GLOBAL
#endif	// B_PLIST_BMP_H
