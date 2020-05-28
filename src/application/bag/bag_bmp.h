//============================================================================================
/**
 * @file	bag_bmp.h
 * @brief	�o�b�O���BMP����
 * @author	Hiroyuki Nakamura
 * @date	05.11.28
 */
//============================================================================================
#ifndef BAG_BMP_H
#define BAG_BMP_H
#undef GLOBAL
#ifdef BAG_BMP_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	SYS_FONT_PAL	( 3 )
#define	WINDOW_PAL		( 14 )
#define	ICON_PAL		( 13 )
#define	TALKWIN_PAL		( 12 )
#define	TALK_FONT_PAL	( 11 )

#define	BUTTON_CGX_START	( 30 )
#define	BUTTON_CGX_WIDE		( 30 )
#define	BUTTON_CGX_XNEXT	( 15 )
#define	BUTTON_CGX_YNEXT	( 30 * 5 )
#define	BUTTON_CGX_SIZE		( 5 )
#define	BUTTON_PAL_NUM		( 2 )

// �A�C�e�����X�g
#define	BMP_LIST_PX		( 14 )
#define	BMP_LIST_PY		( 0 )
#define	BMP_LIST_SX		( 17 )
#define	BMP_LIST_SY		( 18 )
#define	BMP_LIST_PAL	( SYS_FONT_PAL )
#define	BMP_LIST_CGX	( 1 )
#define	BMP_LIST_FRM	( GF_BGL_FRAME2_M )
// ����
//306
#define	BMP_INFO_PX		( 0 )
#define	BMP_INFO_PY		( 18 )
#define	BMP_INFO_SX		( 32 )
#define	BMP_INFO_SY		( 6 )
#define	BMP_INFO_PAL	( SYS_FONT_PAL )
#define	BMP_INFO_CGX	( BMP_LIST_CGX + BMP_LIST_SX * BMP_LIST_SY )
#define	BMP_INFO_FRM	( GF_BGL_FRAME0_M )
// �|�P�b�g��
//168
#define	BMP_POCKET_PX	( 0 )
#define	BMP_POCKET_PY	( 13 )
#define	BMP_POCKET_SX	( 12 * 3 )
#define	BMP_POCKET_SY	( 3 )
#define	BMP_POCKET_PAL	( SYS_FONT_PAL )
#define	BMP_POCKET_CGX	( BMP_INFO_CGX + BMP_INFO_SX * BMP_INFO_SY )
#define	BMP_POCKET_FRM	( GF_BGL_FRAME2_M )
// ���j���[���
#define	BMP_MENU_INFO_PX	( 6 )
#define	BMP_MENU_INFO_PY	( 19 )
#define	BMP_MENU_INFO_SX	( 14 )
#define	BMP_MENU_INFO_SY	( 4 )
#define	BMP_MENU_INFO_PAL	( TALK_FONT_PAL )
#define	BMP_MENU_INFO_CGX	( BMP_POCKET_CGX + BMP_POCKET_SX * BMP_POCKET_SY )
#define	BMP_MENU_INFO_FRM	( GF_BGL_FRAME0_M )
// ���j���[���Q�i�؂̎��|�P�b�g�p�j
#define	BMP_MENU_INFO2_PX	( 6 )
#define	BMP_MENU_INFO2_PY	( 19 )
#define	BMP_MENU_INFO2_SX	( 13 )
#define	BMP_MENU_INFO2_SY	( 4 )
#define	BMP_MENU_INFO2_PAL	( TALK_FONT_PAL )
#define	BMP_MENU_INFO2_CGX	( BMP_MENU_INFO_CGX )
#define	BMP_MENU_INFO2_FRM	( GF_BGL_FRAME0_M )
// �|�P�b�g�A�C�R��
//68
#define	BMP_P_ICON_PX	( 0 )
#define	BMP_P_ICON_PY	( 11 )
#define	BMP_P_ICON_SX	( 12 )
#define	BMP_P_ICON_SY	( 2 )
#define	BMP_P_ICON_PAL	( ICON_PAL )
#define	BMP_P_ICON_CGX	( BMP_MENU_INFO_CGX + BMP_MENU_INFO_SX * BMP_MENU_INFO_SY )
#define	BMP_P_ICON_FRM	( GF_BGL_FRAME0_M )
// ��b�E�B���h�E
#define	BMP_TALK_PX		( 2 )
#define	BMP_TALK_PY		( 19 )
#define	BMP_TALK_SX		( 27 )
#define	BMP_TALK_SY		( 4 )
#define	BMP_TALK_PAL	( TALK_FONT_PAL )
#define	BMP_TALK_CGX	( BMP_P_ICON_CGX + BMP_P_ICON_SX * BMP_P_ICON_SY )
#define	BMP_TALK_FRM	( GF_BGL_FRAME0_M )

#define	ADD_CGX_NUM		( BMP_TALK_CGX + BMP_TALK_SX * BMP_TALK_SY )

// �͂��E������
#define	BMP_YESNO_PX	( 23 )
#define	BMP_YESNO_PY	( 13 )
#define	BMP_YESNO_SX	( 7 )
#define	BMP_YESNO_SY	( 4 )
#define	BMP_YESNO_PAL	( SYS_FONT_PAL )
#define	BMP_YESNO_CGX	( ADD_CGX_NUM )
#define	BMP_YESNO_FRM	( GF_BGL_FRAME0_M )
// �T���ڃ��j���[�i�ő�j
#define	BMP_MENU1_PX	( 23 )
#define	BMP_MENU1_PY	( 23 )
#define	BMP_MENU1_SX	( 8 )
#define	BMP_MENU1_SY	( 10 )
#define	BMP_MENU1_PAL	( SYS_FONT_PAL )
#define	BMP_MENU1_CGX	( BMP_YESNO_CGX + BMP_YESNO_SX * BMP_YESNO_SY )
#define	BMP_MENU1_FRM	( GF_BGL_FRAME0_M )
// �̂Ă���I��
#define	BMP_DEL_PX		( 24 )
#define	BMP_DEL_PY		( 19 )
#define	BMP_DEL_SX		( 7 )
#define	BMP_DEL_SY		( 4 )
#define	BMP_DEL_PAL		( SYS_FONT_PAL )
#define	BMP_DEL_CGX		( BMP_MENU1_CGX + BMP_MENU1_SX * BMP_MENU1_SY )
#define	BMP_DEL_FRM		( GF_BGL_FRAME0_M )
// ���I���i����j
#define	BMP_SALE_NUM_PX		( 19 )
#define	BMP_SALE_NUM_PY		( 13 )
#define	BMP_SALE_NUM_SX		( 12 )
#define	BMP_SALE_NUM_SY		( 4 )
#define	BMP_SALE_NUM_PAL	( SYS_FONT_PAL )
#define	BMP_SALE_NUM_CGX	( BMP_MENU1_CGX )
#define	BMP_SALE_NUM_FRM	( GF_BGL_FRAME0_M )
// ����������
#define	BMP_GOLD_PX		( 1 )
#define	BMP_GOLD_PY		( 1 )
#define	BMP_GOLD_SX		( 10 )
#define	BMP_GOLD_SY		( 4 )
#define	BMP_GOLD_PAL	( SYS_FONT_PAL )
#define	BMP_GOLD_CGX	( BMP_SALE_NUM_CGX + BMP_SALE_NUM_SX * BMP_SALE_NUM_SY )
#define	BMP_GOLD_FRM	( GF_BGL_FRAME0_M )
// �|���g�̐�
#define	BMP_PORUTO_PX	( 1 )
#define	BMP_PORUTO_PY	( 12 )
#define	BMP_PORUTO_SX	( 11 )
#define	BMP_PORUTO_SY	( 4 )
#define	BMP_PORUTO_PAL	( SYS_FONT_PAL )
#define	BMP_PORUTO_CGX	( BMP_MENU1_CGX + BMP_MENU1_SX * BMP_MENU1_SY )
#define	BMP_PORUTO_FRM	( GF_BGL_FRAME0_M )

#define	MENU_WIN_CGX_NUM	( 1024 - MENU_WIN_CGX_SIZ )
#define	MENU_WIN_PAL		( WINDOW_PAL )
#define	TALK_WIN_CGX_NUM	( MENU_WIN_CGX_NUM - TALK_WIN_CGX_SIZ )

#define	BAGCOL_GREY_F	( 8 )
#define	BAGCOL_GREY_S	( 9 )

#define	BAGCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	BAGCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
#define	BAGCOL_N_GREY	( GF_PRINTCOLOR_MAKE( 8, 9, 0 ) )		// �t�H���g�J���[�F�D
//#define	BAGCOL_N_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��




//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�ݒ�
 *
 * @param	index	�C���f�b�N�X�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BagBmpWinSet( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�j��
 *
 * @param	index	�C���f�b�N�X�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BagBmpWinExit( GF_BGL_BMPWIN * win );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g���擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketNameMake( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�����
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketNameRelease( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�����X�N���[���ɔ��f
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 *
 *	�ʏ��BMP�����ł͂Ȃ����߁A�w��G���A�݂̂��X�N���[���ɔ��f������
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketNameScreenPut( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketNamePut( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�A�C�R���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	pos		�\���ʒu
 * @param	flg		�I���t���O	( 1 = �I������Ă��� )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketIconPut( BAG_WORK * wk, u8 pos, u8 flg );

//--------------------------------------------------------------------------------------------
/**
 * �S�|�P�b�g�A�C�R���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_PocketIconPutAll( BAG_WORK * wk );



//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�������\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_ItemInfoPut( BAG_WORK * wk, u16 item );

//--------------------------------------------------------------------------------------------
/**
 * ���\��������擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_NumStrGet( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ���\����������
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_NumStrRelease( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����X�g���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_ItemListNumPut( BAG_WORK * wk, u16 num, u16 y, u32 col );

GLOBAL void BagBmp_WazaMachineNoPut( BAG_WORK * wk, MINEITEM * item, u32 py );

GLOBAL void BagBmp_NutsNoPut( BAG_WORK * wk, MINEITEM * item, u32 py );

GLOBAL void BagBmp_WazaPageToziruPut( BAG_WORK * wk, u32 py );

GLOBAL void BagBmp_WazaMashineInfoPut( BAG_WORK * wk, u16 item );

GLOBAL void BagBmp_CnvButtonIconPut( BAG_WORK * wk, u32 py );


//--------------------------------------------------------------------------------------------
/**
 * ���j���[���ڎ擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_MenuStrGet( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[���ډ��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_MenuStrRelease( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�쐬
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	tbl		���j���[�e�[�u��
 * @param	max		���j���[��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_ItemMenuSet( BAG_WORK * wk, u8 * tbl, u8 max );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�j���i�ʏ�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_ItemMenuExit( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�j���i�u���Ă�v�̏ꍇ�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
//GLOBAL void Bag_ItemMenuExitSub( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * ����ւ����b�Z�[�W�\���i�ǂ��ɂ���܂����H�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_ItemChgInfoMsgSet( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �̂Ă���I���E�B���h�E�쐬
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_DelNumSelWinSet( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �̂Ă�֘A�E�B���h�E�j��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_DelNumSelWinExit( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �̂Ă���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_SubNumPut( BAG_WORK * wk );

//--------------------------------------------------------------------------------------------
/**
 * �u���ĂĂ������ł����H�v�\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
GLOBAL void Bag_SubTalkWinSet( BAG_WORK * wk );



GLOBAL u8 Bag_TalkMsgPrint( BAG_WORK * wk );

GLOBAL void Bag_YesNoSelInit( BAG_WORK * wk );

GLOBAL void Bag_SaleNumWinPut( BAG_WORK * wk, u8 flg );

GLOBAL void Bag_GoldWinPut( BAG_WORK * wk, u8 flg );


GLOBAL void BagBmp_PorutoWinPut( BAG_WORK * wk );


#undef GLOBAL
#endif	/* BAG_BMP_H */
