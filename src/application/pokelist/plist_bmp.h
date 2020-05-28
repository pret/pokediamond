//============================================================================================
/**
 * @file	plist_bmp.h
 * @brief	�|�P�������X�g���BMP�֘A
 * @author	Hiroyuki Nakamura
 * @date	05.09.29
 */
//============================================================================================
#ifndef	PLIST_BMP_H
#define	PLIST_BMP_H
#undef	GLOBAL
#ifdef	PLIST_BMP_H_GLOBAL
#define	GLOBAL /*	*/
#else
#define	GLOBAL extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	PL_MSG_COMP_EXPAND	( 0xffffffff )


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

GLOBAL void PokeListBmpAdd( PLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�j��
 *
 * @param	wk		�|�P�������X�g���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListBmpWinExit( PLIST_WORK * wk );


GLOBAL void PokeListNameMake( PLIST_WORK * wk, POKEMON_PARAM * pp, u32 pos );

GLOBAL void PokeListNamePut( PLIST_WORK * wk, u8 num );

GLOBAL void PokeListHPPut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeListHPClear( PLIST_WORK * wk, u8 num );
GLOBAL void PokeListHPBerPut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeListLvPut( PLIST_WORK * wk, u8 num );

GLOBAL void PokeListParamPut( PLIST_WORK * wk, u8 num );

GLOBAL void PokeListParamBmpCgxOn( PLIST_WORK * wk, u8 num );
GLOBAL void PokeListParamBmpWinOff( PLIST_WORK * wk, u8 num );

GLOBAL void PokeList_PanelShinkaCommPut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeList_PanelWazaOboeCommPut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeList_PanelContestCommPut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeList_PanelBattleInNamePut( PLIST_WORK * wk, u8 num );
GLOBAL void PokeList_PanelBattleInCommPut( PLIST_WORK * wk, u8 num );

GLOBAL void PokeListMenuStrMake( PLIST_WORK * wk );
GLOBAL void PokeListMenuDataMake( PLIST_WORK * wk, const u8 * prm, u8 siz );

GLOBAL void PokeListMenuMsgMake( PLIST_WORK * wk );

GLOBAL void PokeList_WazaMenuStrGet( PLIST_WORK * wk, u16 waza, u8 pos );


//--------------------------------------------------------------------------------------------
/**
 * �u�����Ă��v�u���ǂ�v�\��
 *
 * @param	wk		�|�P�������X�g���[�N
 * @param	flg		�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListSelectMsgPut( PLIST_WORK * wk, u8 flg );

//--------------------------------------------------------------------------------------------
/**
 * �P�s���b�Z�[�W�\��
 *
 * @param	wk		�|�P�������X�g���[�N
 ` @param	id		���b�Z�[�WID
 * @param	flg		�E�B���h�E�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListSmallMsgPut( PLIST_WORK * wk, u32 id, u8 flg );

//--------------------------------------------------------------------------------------------
/**
 * �Q�s���b�Z�[�W�\��
 *
 * @param	wk		�|�P�������X�g���[�N
 * @param	id		���b�Z�[�WID
 * @param	flg		�E�B���h�E�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListMiddleMsgPut( PLIST_WORK * wk, u32 id, u8 flg );

//--------------------------------------------------------------------------------------------
/**
 * ��b�i���j���b�Z�[�W�\��
 *
 * @param	wk		�|�P�������X�g���[�N
 * @param	id		���b�Z�[�WID
 * @param	flg		�E�B���h�E�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListLargeMsgPut( PLIST_WORK * wk, u32 id, u8 flg );

//--------------------------------------------------------------------------------------------
/**
 * ��b�i���j���b�Z�[�W�X�^�[�g
 *
 * @param	wk		�|�P�������X�g���[�N
 * @param	id		���b�Z�[�WID
 * @param	flg		�E�B���h�E�\���t���O
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeList_TalkMsgStart( PLIST_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������\��
 *
 * @param	wk		�|�P�������X�g���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeList_YesNoSelectInit( PLIST_WORK * wk );





GLOBAL void PokeList_LvWinPut( PLIST_WORK * wk );
GLOBAL void PokeList_LvUpParamPut( PLIST_WORK * wk );
GLOBAL void PokeList_LvUpWinExit( PLIST_WORK * wk );



#undef GLOBAL
#endif
