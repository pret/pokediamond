//============================================================================================
/**
 * @file	plist_obj.h
 * @brief	�|�P�������X�gOBJ����
 * @author	Hiroyuki Nakamura
 * @date	05.10.05
 */
//============================================================================================
#ifndef PLIST_OBJ_H
#define PLIST_OBJ_H
#undef GLOBAL
#ifdef PLIST_OBJ_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif



enum {
	PLA_CHAR_ID_BALL = 0,
	PLA_CHAR_ID_CURSOR,
	PLA_CHAR_ID_ENTER,
	PLA_CHAR_ID_STATUS,
	PLA_CHAR_ID_ICON1,
	PLA_CHAR_ID_ICON2,
	PLA_CHAR_ID_ICON3,
	PLA_CHAR_ID_ICON4,
	PLA_CHAR_ID_ICON5,
	PLA_CHAR_ID_ICON6,
	PLA_CHAR_ID_ITEM,
	PLA_CHAR_ID_BUTTON_EF,
};
/*
enum {
	PLA_PLTT_ID_OBJ = 0,
	PLA_PLTT_ID_STATUS,
	PLA_PLTT_ID_ICON,
	PLA_PLTT_ID_ITEM,
};
enum {
	PLA_CELL_ID_BALL = 0,
	PLA_CELL_ID_CURSOR,
	PLA_CELL_ID_ENTER,
	PLA_CELL_ID_STATUS,
	PLA_CELL_ID_ICON1,
	PLA_CELL_ID_ICON2,
	PLA_CELL_ID_ITEM,
};
enum {
	PLA_CANM_ID_BALL = 0,
	PLA_CANM_ID_CURSOR,
	PLA_CANM_ID_STATUS,
	PLA_CANM_ID_ENTER,
	PLA_CANM_ID_ICON1,
	PLA_CANM_ID_ICON2,
	PLA_CANM_ID_ITEM,
};
*/
enum {
	PL_ST_POKERUS = 0,	// �|�P���X
	PL_ST_MAHI,			// ���
	PL_ST_KOORI,		// �X
	PL_ST_NEMURI,		// ����
	PL_ST_DOKU,			// ��
	PL_ST_YAKEDO,		// �Ώ�
	PL_ST_HINSI,		// �m��

	PL_ST_NONE,			// ��Ԉُ�Ȃ�
};


//---------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[������
 *
 * @param	wk		�|�P�������X�g���[�N
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
GLOBAL void PokeListCellActorInit( PLIST_WORK * wk );

GLOBAL void PokeListCellActSet( PLIST_WORK * wk );
GLOBAL void PokeListIconAdd( PLIST_WORK * wk, u8 pos, u16 px, u16 py );
GLOBAL void PokeListBallActSet( PLIST_WORK * wk, u8 pos, u16 px, u16 py );

GLOBAL void PokeListCellActRerease( PLIST_WORK * wk );

GLOBAL void PokeList_StatusIconChg( PLIST_WORK * wk, u8 pos, u8 st );
GLOBAL void PokeList_ItemIconChg( PLIST_WORK * wk, u8 pos, u16 item );
GLOBAL void PokeList_MailIconChg( PLIST_WORK * wk, u8 pos );
GLOBAL void PokeList_ItemIconPosSet( PLIST_WORK * wk, u8 pos, s16 x, s16 y );

GLOBAL void PokeList_CustomIconPosSet( PLIST_WORK * wk, u8 pos );
GLOBAL void PokeList_CustomIconChg( PLIST_WORK * wk, u8 pos );

GLOBAL void PokeIconAnime( PLIST_WORK * wk );

GLOBAL void PokeList_SelCursorChgDirect( PLIST_WORK * wk, u8 pos, u8 pal );

GLOBAL void PokeListObj_SubButtonEffInit( PLIST_WORK * wk, s16 x, s16 y );
GLOBAL void PokeListObj_SubButtonEffMain( PLIST_WORK * wk );



#undef GLOBAL
#endif	// PLIST_OBJ_H
