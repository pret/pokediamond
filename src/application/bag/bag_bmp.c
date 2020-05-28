//============================================================================================
/**
 * @file	bag_bmp.c
 * @brief	�o�b�O���BMP����
 * @author	Hiroyuki Nakamura
 * @date	05.11.28
 */
//============================================================================================
#include "common.h"
#include "system/gamedata.h"
#include "system/procsys.h"
#include "system/window.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/pmfprint.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/buflen.h"
#include "system/snd_tool.h"
#include "savedata/config.h"
#include "savedata/poruto_util.h"
#include "itemtool/item.h"
#include "battle/battle_common.h"
#include "poketool/waza_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_bag.h"
#include "msgdata/msg_itempocket.h"

#define	BAG_BMP_H_GLOBAL
#include "application/bag.h"
#include "bag_main.h"
#include "bag_bmp.h"
#include "bag_obj.h"
#include "bag_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
#define	POCKET_NAME_AREA_SX		( 96 )		// �|�P�b�g���\���G���AX�T�C�Y
#define	POCKET_NAME_AREA_GX		( 50 )		// �|�P�b�g���\���X���W
#define	POCKET_NAME_SCROLL_X	( 12 )		// �P�J�E���g�X�N���[������h�b�g��

#define	MENU_INFO_STRLEN	( BMP_MENU_INFO_SX*2*2 )	// ���j���[����������T�C�YWinSiz * 2�s * �C�O�Ή�

#define	NUMSEL_EX		( BMP_SALE_NUM_SX * 8 )

#define	NORMAL_INFO_PX	( 40 )		// �A�C�e�����\��X���W

#define	INFO_TYPE_PX	( 0 )		// �Z�}�V����� �u�^�C�v�v�\��X���W
#define	INFO_TYPE_PY	( 0 )		// �Z�}�V����� �u�^�C�v�v�\��Y���W
#define	INFO_PP_PX		( 0 )		// �Z�}�V����� �uPP�v�\��X���W
#define	INFO_PP_PY		( 16 )		// �Z�}�V����� �uPP�v�\��Y���W
#define	INFO_KIND_PX	( 96 )		// �Z�}�V����� �u�Ԃ�邢�v�\��X���W
#define	INFO_KIND_PY	( 0 )		// �Z�}�V����� �u�Ԃ�邢�v�\��Y���W
#define	INFO_POW_PX		( 96 )		// �Z�}�V����� �u����傭�v�\��X���W
#define	INFO_POW_PY		( 16 )		// �Z�}�V����� �u����傭�v�\��Y���W
#define	INFO_HIT_PX		( 96 )		// �Z�}�V����� �u�߂����イ�v�\��X���W
#define	INFO_HIT_PY		( 32 )		// �Z�}�V����� �u�߂����イ�v�\��YX���W
#define	INFO_PPNUM_PX	( 48 )		// �Z�}�V����� PP�l�\��X���W
#define	INFO_PPNUM_PY	( 16 )		// �Z�}�V����� PP�l�\��Y���W
#define	INFO_POWNUM_PX	( 96+64 )	// �Z�}�V����� �З͒l�\��X���W
#define	INFO_POWNUM_PY	( 16 )		// �Z�}�V����� �З͒l�\��Y���W
#define	INFO_HITNUM_PX	( 96+64 )	// �Z�}�V����� �����l�\��X���W
#define	INFO_HITNUM_PY	( 32 )		// �Z�}�V����� �����l�\��Y���W

#define	NX_POS_PX	( 100 )				// �u���v�\��X���W�i�ʏ�j
#define	WX_POS_PX	( NX_POS_PX+12 )	// �u���v�\��X���W�i�Z�}�V���j
#define	NUM_POS_EX	( 17*8-2 )			// ���\��X���W�I�[
#define	NUM_BUFLEN	( 10 )				// ("x???"+EOM_) x �C�O

#define	WM_NO_Y_PLUS	( 5 )		// �Z�}�V���́uNo�v�\��Y���W�I�t�Z�b�g

#define	LIST_FILL_SY	( 16 )		// �Z�}�V���|�P�b�g�́u�Ƃ���v��\�����邽�߂�Y�T�C�Y

#define	LIST_ICON_SX	( 64 )		// �u�Ђł�v�u�Ƃ��낭�v�A�C�R���̃L�����f�[�^�T�C�YX
#define	LIST_ICON_SY	( 16 )		// �u�Ђł�v�u�Ƃ��낭�v�A�C�R���̃L�����f�[�^�T�C�YY

#define	HIREN_ICON_PX	( 40 )		// �u�Ђł�v�A�C�R���̃L�����f�[�^�̊J�nX���W
#define	HIREN_ICON_PY	( 0 )		// �u�Ђł�v�A�C�R���̃L�����f�[�^�̊J�nY���W
#define	HIREN_ICON_SX	( 24 )		// �u�Ђł�v�A�C�R���̃L�����f�[�^��X�T�C�Y
#define	HIREN_ICON_SY	( 16 )		// �u�Ђł�v�A�C�R���̃L�����f�[�^��Y�T�C�Y

#define	CNV_ICON_PX			( 0 )	// �u�Ƃ��낭�v�A�C�R���̃L�����f�[�^�̊J�nX���W
#define	CNV_ICON_PY			( 0 )	// �u�Ƃ��낭�v�A�C�R���̃L�����f�[�^�̊J�nY���W
#define	CNV_ICON_SX			( 40 )	// �u�Ƃ��낭�v�A�C�R���̃L�����f�[�^��X�T�C�Y
#define	CNV_ICON_SY			( 16 )	// �u�Ƃ��낭�v�A�C�R���̃L�����f�[�^��Y�T�C�Y
#define	CNV_ICON_SCRPUT_X	( 96 )	// �u�Ƃ��낭�v�A�C�R���̕\��X���W

#define	GOLD_EX			( BMP_GOLD_SX * 8 )		// �������\���̏I�[X���W


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BAG_HidenIconPut( BAG_WORK * wk, u32 py );
static void BAG_WazaMashinePPPut( BAG_WORK * wk, u16 item );

static BOOL BAG_TalkMsgCallBack( MSG_PRINT_HEADER * mph, u16 value );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �͂��E������
static const BMPWIN_DAT YesNoBmpWin = {
	BMP_YESNO_FRM, BMP_YESNO_PX, BMP_YESNO_PY,
	BMP_YESNO_SX, BMP_YESNO_SY, BMP_YESNO_PAL, BMP_YESNO_CGX
};



//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�ݒ�
 *
 * @param	index	�C���f�b�N�X�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagBmpWinSet( BAG_WORK * wk )
{
	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_LIST], BMP_LIST_FRM,
		BMP_LIST_PX, BMP_LIST_PY, BMP_LIST_SX, BMP_LIST_SY, BMP_LIST_PAL, BMP_LIST_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_INFO], BMP_INFO_FRM,
		BMP_INFO_PX, BMP_INFO_PY, BMP_INFO_SX, BMP_INFO_SY, BMP_INFO_PAL, BMP_INFO_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_POCKET],
		BMP_POCKET_FRM, BMP_POCKET_PX, BMP_POCKET_PY,
		BMP_POCKET_SX, BMP_POCKET_SY, BMP_POCKET_PAL, BMP_POCKET_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_MENU_INFO],
		BMP_MENU_INFO_FRM, BMP_MENU_INFO_PX, BMP_MENU_INFO_PY,
		BMP_MENU_INFO_SX, BMP_MENU_INFO_SY, BMP_MENU_INFO_PAL, BMP_MENU_INFO_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_MENU_INFO2],
		BMP_MENU_INFO2_FRM, BMP_MENU_INFO2_PX, BMP_MENU_INFO2_PY,
		BMP_MENU_INFO2_SX, BMP_MENU_INFO2_SY, BMP_MENU_INFO2_PAL, BMP_MENU_INFO2_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_P_ICON],
		BMP_P_ICON_FRM, BMP_P_ICON_PX, BMP_P_ICON_PY,
		BMP_P_ICON_SX, BMP_P_ICON_SY, BMP_P_ICON_PAL, BMP_P_ICON_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_TALK],
		BMP_TALK_FRM, BMP_TALK_PX, BMP_TALK_PY,
		BMP_TALK_SX, BMP_TALK_SY, BMP_TALK_PAL, BMP_TALK_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_SALE_NUM],
		BMP_SALE_NUM_FRM, BMP_SALE_NUM_PX, BMP_SALE_NUM_PY,
		BMP_SALE_NUM_SX, BMP_SALE_NUM_SY, BMP_SALE_NUM_PAL, BMP_SALE_NUM_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_GOLD], BMP_GOLD_FRM,
		BMP_GOLD_PX, BMP_GOLD_PY, BMP_GOLD_SX, BMP_GOLD_SY, BMP_GOLD_PAL, BMP_GOLD_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_SUB], BMP_DEL_FRM,
		BMP_DEL_PX, BMP_DEL_PY, BMP_DEL_SX, BMP_DEL_SY, BMP_DEL_PAL, BMP_DEL_CGX );

	GF_BGL_BmpWinAdd(
		wk->bgl, &wk->win[WIN_PORUTO],
		BMP_PORUTO_FRM, BMP_PORUTO_PX, BMP_PORUTO_PY,
		BMP_PORUTO_SX, BMP_PORUTO_SY, BMP_PORUTO_PAL, BMP_PORUTO_CGX );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�E�B���h�E�j��
 *
 * @param	index	�C���f�b�N�X�i�[�ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagBmpWinExit( GF_BGL_BMPWIN * win )
{
	u16	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &win[i] );
	}
}


//============================================================================================
//	�|�P�b�g��
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g���擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_PocketNameMake( BAG_WORK * wk )
{
	MSGDATA_MANAGER * man;
	u16	i;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_itempocket_dat, HEAPID_BAG );

	for( i=0; i<BAG_POKE_MAX; i++ ){
		wk->pocket_name[i]  = MSGMAN_AllocString( man, i );
	}

	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�����
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_PocketNameRelease( BAG_WORK * wk )
{
	u16	i;

	for( i=0; i<BAG_POKE_MAX; i++ ){
		STRBUF_Delete( wk->pocket_name[i] );
	}
}

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
void Bag_PocketNameScreenPut( BAG_WORK * wk )
{
	u16	i;
	u16	ssx;

	ssx = BMP_POCKET_SX/3;

	for( i=0; i<ssx; i++ ){
		GF_BGL_ScrFill(
			wk->bgl, BMP_POCKET_FRM, BMP_POCKET_CGX+ssx+i,
			BMP_POCKET_PX+i, BMP_POCKET_PY, 1, 1, BMP_POCKET_PAL );
		GF_BGL_ScrFill(
			wk->bgl, BMP_POCKET_FRM, BMP_POCKET_CGX+BMP_POCKET_SX+ssx+i,
			BMP_POCKET_PX+i, BMP_POCKET_PY+1, 1, 1, BMP_POCKET_PAL );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g���\���E�R�A
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	str		�\�����镶����
 * @param	cx		������̕\�����SX���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PocketNamePutCore( BAG_WORK * wk, STRBUF * str, u16 cx )
{
	u32	siz;

	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );

	GF_STR_PrintColor(
		&wk->win[WIN_POCKET], FONT_SYSTEM, str, cx-siz/2, 2, MSG_NO_PUT, BAGCOL_N_BLACK, NULL );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_PocketNamePut( BAG_WORK * wk )
{
	PAGE_CHG_WORK * pwk;
	STRBUF * new_p;
	STRBUF * now_p;
	u16	px;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_POCKET], 0 );

	pwk = &wk->page_work;

	now_p = wk->pocket_name[ wk->dat->p_data[wk->dat->p_now].type ];
	new_p = wk->pocket_name[ wk->dat->p_data[pwk->next].type ];

	if( pwk->move == 0 ){
		px = POCKET_NAME_AREA_SX + POCKET_NAME_AREA_GX + POCKET_NAME_SCROLL_X * pwk->cur_cnt;
		PocketNamePutCore( wk, new_p, px - POCKET_NAME_AREA_SX );
	}else{
		px = POCKET_NAME_AREA_SX + POCKET_NAME_AREA_GX - POCKET_NAME_SCROLL_X * pwk->cur_cnt;
		PocketNamePutCore( wk, new_p, POCKET_NAME_AREA_SX + px );
	}
	PocketNamePutCore( wk, now_p, px );

	GF_BGL_BmpWinCgxOn( &wk->win[WIN_POCKET] );
}


//============================================================================================
//	�|�P�b�g�A�C�R��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�A�C�R���̃L�����f�[�^�擾
 *
 * @param	wk		�L�����擾�ꏊ
 *
 * @return	�L�����W�J�̈�
 */
//--------------------------------------------------------------------------------------------
static void * PocketIconCgxGet( BAG_WORK * wk, NNSG2dCharacterData ** chr )
{
	void * buf;

	buf = ArchiveDataLoadAllocByHandle( wk->gra_h, NARC_bag_gra_bag_pocketlist_NCGR, HEAPID_BAG );
	NNS_G2dGetUnpackedBGCharacterData( buf, chr );
	return buf;
}

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
void Bag_PocketIconPut( BAG_WORK * wk, u8 pos, u8 flg )
{
	NNSG2dCharacterData * chr;
	void * arc_buf;
	u8	spx;

	arc_buf = PocketIconCgxGet( wk, &chr );

	if( flg == 1 ){
		spx = wk->dat->p_data[pos].type * 32 + 16;
	}else{
		spx = wk->dat->p_data[pos].type * 32;
	}

	GF_BGL_BmpWinPrint(
		&wk->win[WIN_P_ICON], chr->pRawData, spx, 0, 32*8, 16,
		wk->p_icon_gx+wk->p_icon_sx*pos, 3, P_ICON_SIZ_X, P_ICON_SIZ_Y );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_P_ICON] );
	sys_FreeMemory( HEAPID_BAG, arc_buf );
}

//--------------------------------------------------------------------------------------------
/**
 * �S�|�P�b�g�A�C�R���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_PocketIconPutAll( BAG_WORK * wk )
{
	NNSG2dCharacterData * chr;
	void * arc_buf;
	u8	i;
	u8	spx;

	arc_buf = PocketIconCgxGet( wk, &chr );

	GF_BGL_BmpWinDataFill( &wk->win[WIN_P_ICON], 0 );

	for( i=0; i<wk->p_max; i++ ){
		if( i == wk->dat->p_now ){
			spx = wk->dat->p_data[i].type * 32 + 16;
		}else{
			spx = wk->dat->p_data[i].type * 32;
		}
		GF_BGL_BmpWinPrint(
			&wk->win[WIN_P_ICON], chr->pRawData, spx, 0, 32*8, 16,
			wk->p_icon_gx+wk->p_icon_sx*i, 3, P_ICON_SIZ_X, P_ICON_SIZ_Y );
	}

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_P_ICON] );
	sys_FreeMemory( HEAPID_BAG, arc_buf );
}




//--------------------------------------------------------------------------------------------
/**
 * �A�C�e������P��o�^
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemNameWordSet( BAG_WORK * wk, u32 pos, u32 buf_id )
{
	WORDSET_RegisterItemName( wk->wset, buf_id, Bag_PosItemGet(wk,pos,POS_GET_ID) );
}


//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�������\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_ItemInfoPut( BAG_WORK * wk, u16 item )
{
	STRBUF * buf;

	if( item != 0xffff ){
		buf = STRBUF_Create( BUFLEN_ITEM_INFO, HEAPID_BAG );
		ItemInfoGet( buf, item, HEAPID_BAG );
	}else{
		buf = MSGMAN_AllocString( wk->msg_man, mes_bag_103 );
	}

	GF_STR_PrintColor(
		&wk->win[WIN_INFO], FONT_SYSTEM, buf,
		NORMAL_INFO_PX, 0, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( buf );
}



void BagBmp_WazaMashineInfoPut( BAG_WORK * wk, u16 item )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u16	waza;
	u16	prm;

	win  = &wk->win[WIN_INFO];
	waza = GetWazaNoItem( item );

	// �^�C�v
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_107 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, INFO_TYPE_PX, INFO_TYPE_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// PP
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_095 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, INFO_PP_PX, INFO_PP_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// �Ԃ�邢
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_098 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, INFO_KIND_PX, INFO_KIND_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// ����傭
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_096 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, INFO_POW_PX, INFO_POW_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	// �߂����イ
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_097 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, INFO_HIT_PX, INFO_HIT_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	// PP�l
	prm = WT_PPMaxGet( waza, 0 );
	str = MSGMAN_AllocString( wk->msg_man, mes_bag_099 );
	WORDSET_RegisterNumber( wk->wset, 0, prm, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->expb, INFO_PPNUM_PX, INFO_PPNUM_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	// �З͒l
	prm = WT_WazaDataParaGet( waza, ID_WTD_damage );
	if( prm <= 1 ){
		str = MSGMAN_AllocString( wk->msg_man, msg_bag_025 );
	}else{
		str = MSGMAN_AllocString( wk->msg_man, mes_bag_100 );
	}
	WORDSET_RegisterNumber( wk->wset, 0, prm, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->expb, INFO_POWNUM_PX, INFO_POWNUM_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
	// �����l
	prm = WT_WazaDataParaGet(waza,ID_WTD_hitprobability);
	if( prm == 0 ){
		str = MSGMAN_AllocString( wk->msg_man, msg_bag_025 );
	}else{
		str = MSGMAN_AllocString( wk->msg_man, mes_bag_100 );
	}
	WORDSET_RegisterNumber( wk->wset, 0, prm, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, str );
	STRBUF_Delete( str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->expb, INFO_HITNUM_PX, INFO_HITNUM_PY, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );
}


//--------------------------------------------------------------------------------------------
/**
 * ���\��������擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_NumStrGet( BAG_WORK * wk )
{
	wk->num_str1 = MSGMAN_AllocString( wk->msg_man, msg_bag_093 );
	wk->num_str2 = MSGMAN_AllocString( wk->msg_man, msg_bag_038 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���\����������
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_NumStrRelease( BAG_WORK * wk )
{
	STRBUF_Delete( wk->num_str1 );
	STRBUF_Delete( wk->num_str2 );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����X�g���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_ItemListNumPut( BAG_WORK * wk, u16 num, u16 y, u32 col )
{
	STRBUF * expb;
	u32	siz;

	if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_WAZA ){
		GF_STR_PrintColor(
			&wk->win[WIN_LIST], FONT_SYSTEM,
			wk->num_str1, WX_POS_PX, y, MSG_NO_PUT, col, NULL );
	}else{
		GF_STR_PrintColor(
			&wk->win[WIN_LIST], FONT_SYSTEM,
			wk->num_str1, NX_POS_PX, y, MSG_NO_PUT, col, NULL );
	}

	expb = STRBUF_Create( NUM_BUFLEN, HEAPID_BAG );

	WORDSET_RegisterNumber( wk->wset, 0, num, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, expb, wk->num_str2 );

	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, expb, 0 );

	GF_STR_PrintColor(
		&wk->win[WIN_LIST], FONT_SYSTEM, expb, NUM_POS_EX-siz, y, MSG_NO_PUT, col, NULL );

	STRBUF_Delete( expb );
}


void BagBmp_WazaMachineNoPut( BAG_WORK * wk, MINEITEM * item, u32 py )
{
	u16	id = item->id;

	if( id < ITEM_HIDENMASIN01 ){
		id = id - ITEM_WAZAMASIN01 + 1;
		NUMFONT_WriteSet(
			wk->num_font, NUMFONT_MARK_NO, id, 2,
			NUMFONT_MODE_ZERO, &wk->win[WIN_LIST], 0, py + WM_NO_Y_PLUS );
		Bag_ItemListNumPut( wk, item->no, py, BAGCOL_N_BLACK );
	}else{
		id = id - ITEM_HIDENMASIN01 + 1;
		NUMFONT_WriteNumber(
			wk->num_font, id, 2, NUMFONT_MODE_SPACE,
			&wk->win[WIN_LIST], NUMFONT_MARK_WIDTH, py + WM_NO_Y_PLUS );
		BAG_HidenIconPut( wk, py );
	}
}

void BagBmp_NutsNoPut( BAG_WORK * wk, MINEITEM * item, u32 py )
{
	NUMFONT_WriteSet(
		wk->num_font, NUMFONT_MARK_NO, NutsNoGet(item->id)+1, 2,
		NUMFONT_MODE_ZERO, &wk->win[WIN_LIST], 0, py + WM_NO_Y_PLUS );
	Bag_ItemListNumPut( wk, item->no, py, BAGCOL_N_BLACK );
}

static void * ListIconCgxGet( BAG_WORK * wk, NNSG2dCharacterData ** chr )
{
	void * buf;

	buf = ArchiveDataLoadAllocByHandle( wk->gra_h, NARC_bag_gra_listicon_NCGR, HEAPID_BAG );
	NNS_G2dGetUnpackedBGCharacterData( buf, chr );
	return buf;
}

static void BAG_HidenIconPut( BAG_WORK * wk, u32 py )
{
	NNSG2dCharacterData * chr;
	void * arc_buf;
	u8	spx;

	arc_buf = ListIconCgxGet( wk, &chr );

	GF_BGL_BmpWinPrint(
		&wk->win[WIN_LIST], chr->pRawData, HIREN_ICON_PX, HIREN_ICON_PY,
		LIST_ICON_SX, LIST_ICON_SY, 0, py, HIREN_ICON_SX, HIREN_ICON_SY );

	sys_FreeMemory( HEAPID_BAG, arc_buf );
}



void BagBmp_WazaPageToziruPut( BAG_WORK * wk, u32 py )
{
	STRBUF * str = MSGMAN_AllocString( wk->msg_man, msg_bag_041 );

	GF_BGL_BmpWinFill( &wk->win[WIN_LIST], 0, 0, py, BMP_LIST_SX*8, LIST_FILL_SY );

	GF_STR_PrintColor(
		&wk->win[WIN_LIST], FONT_SYSTEM, str,
		0, py, MSG_NO_PUT, BAGCOL_N_BLACK, NULL );

	STRBUF_Delete( str );
}


void BagBmp_CnvButtonIconPut( BAG_WORK * wk, u32 py )
{
	NNSG2dCharacterData * chr;
	void * arc_buf;
	u8	spx;

	arc_buf = ListIconCgxGet( wk, &chr );

	GF_BGL_BmpWinPrint(
		&wk->win[WIN_LIST], chr->pRawData, CNV_ICON_PX, CNV_ICON_PY,
		LIST_ICON_SX, LIST_ICON_SY, CNV_ICON_SCRPUT_X, py, CNV_ICON_SX, CNV_ICON_SY );

	sys_FreeMemory( HEAPID_BAG, arc_buf );
}



//============================================================================================
//	���j���[
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���j���[���ڎ擾
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_MenuStrGet( BAG_WORK * wk )
{
	wk->menu_str[ BAG_MENU_TSUKAU ]     = MSGMAN_AllocString( wk->msg_man, msg_bag_001 );
	wk->menu_str[ BAG_MENU_ORIRU ]      = MSGMAN_AllocString( wk->msg_man, msg_bag_007 );
	wk->menu_str[ BAG_MENU_MIRU ]       = MSGMAN_AllocString( wk->msg_man, msg_bag_017 );
	wk->menu_str[ BAG_MENU_UMERU ]		= MSGMAN_AllocString( wk->msg_man, mes_bag_104 );
	wk->menu_str[ BAG_MENU_HIRAKU ]		= MSGMAN_AllocString( wk->msg_man, mes_bag_105 );
	wk->menu_str[ BAG_MENU_SUTERU ]     = MSGMAN_AllocString( wk->msg_man, msg_bag_002 );
	wk->menu_str[ BAG_MENU_TOUROKU ]    = MSGMAN_AllocString( wk->msg_man, msg_bag_003 );
	wk->menu_str[ BAG_MENU_KAIZYO ]     = MSGMAN_AllocString( wk->msg_man, msg_bag_019 );
	wk->menu_str[ BAG_MENU_MOTASERU ]   = MSGMAN_AllocString( wk->msg_man, msg_bag_004 );
	wk->menu_str[ BAG_MENU_TAGUWOMIRU ] = MSGMAN_AllocString( wk->msg_man, msg_bag_005 );
	wk->menu_str[ BAG_MENU_KETTEI ]		= MSGMAN_AllocString( wk->msg_man, msg_bag_006 );
	wk->menu_str[ BAG_MENU_YAMERU ]     = MSGMAN_AllocString( wk->msg_man, msg_bag_009 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[���ډ��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_MenuStrRelease( BAG_WORK * wk )
{
	u16	i;

	for( i=0; i<BAG_MENU_MAX; i++ ){
		STRBUF_Delete( wk->menu_str[i] );
	}
}

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
void Bag_ItemMenuSet( BAG_WORK * wk, u8 * tbl, u8 max )
{
	BMPMENU_HEADER hed;
	POCKET_DATA * pocket;
	STRBUF * msg;
	STRBUF * expb;
	u16	i;
	u16	info;

	if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_NUTS ){
		GF_BGL_BmpWinAdd(
			wk->bgl, &wk->add_win[ADD_WIN_MENU],
			BMP_MENU1_FRM, BMP_MENU1_PX, BMP_MENU1_PY-max*2,
			BMP_MENU1_SX, max*2, BMP_MENU1_PAL, BMP_MENU1_CGX );
		info = WIN_MENU_INFO2;
	}else{
		GF_BGL_BmpWinAdd(
			wk->bgl, &wk->add_win[ADD_WIN_MENU],
			BMP_MENU1_FRM, BMP_MENU1_PX+1, BMP_MENU1_PY-max*2,
			BMP_MENU1_SX-1, max*2, BMP_MENU1_PAL, BMP_MENU1_CGX );
		info = WIN_MENU_INFO;
	}

	wk->md = BMP_MENULIST_Create( max, HEAPID_BAG );

	// ���j���[�f�[�^�쐬
	for( i=0; i<max; i++ ){
		BMP_MENULIST_AddString( wk->md, wk->menu_str[tbl[i]], Bag_MenuParamGet( tbl[i] ) );
	}

	hed.menu  = wk->md;
	hed.win   = &wk->add_win[ADD_WIN_MENU];
	hed.font  = FONT_SYSTEM;
	hed.x_max = 1;
	hed.y_max = max;
	hed.line_spc = 0;
	hed.c_disp_f = 0;
	if( max >= 4 ){
		hed.loop_f = 1;
	}else{
		hed.loop_f = 0;
	}

	wk->mw = BmpMenuAdd_NoTrans( &hed, 8, 0, 0, HEAPID_BAG, PAD_BUTTON_CANCEL );

	if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_WAZA ){
		GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], FBMP_COL_NULL );
		BagBmp_WazaMashineInfoPut( wk, wk->dat->ret_item );
		GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
		BagObj_WazaIconPut( wk, wk->dat->ret_item, ACT_ON );
	}else{
		// ����
		BmpTalkWinWrite(
			&wk->win[info], WINDOW_TRANS_OFF, TALK_WIN_CGX_NUM, TALKWIN_PAL );

		GF_BGL_BmpWinDataFill( &wk->win[info], FBMP_COL_WHITE );

		msg    = MSGMAN_AllocString( wk->msg_man, msg_bag_042 );
		expb   = STRBUF_Create( MENU_INFO_STRLEN, HEAPID_BAG );
		pocket = &wk->dat->p_data[ wk->dat->p_now ];

		ItemNameWordSet( wk, pocket->scr+pocket->cur-1, 0 );
		WORDSET_ExpandStr( wk->wset, expb, msg );

		GF_STR_PrintSimple( &wk->win[info], FONT_TALK, expb, 0, 0, MSG_NO_PUT, NULL );

		STRBUF_Delete( expb );
		STRBUF_Delete( msg );

		GF_BGL_BmpWinOnVReq( &wk->win[info] );
	}

	BmpMenuWinWrite(
		&wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_MENU] );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�j���i�ʏ�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Bag_ItemMenuExit( BAG_WORK * wk )
{
	u32	info;

	if( wk->dat->p_data[wk->dat->p_now].type == BAG_POKE_NUTS ){
		info = WIN_MENU_INFO2;
	}else{
		info = WIN_MENU_INFO;
	}

	if( wk->dat->p_data[wk->dat->p_now].type != BAG_POKE_WAZA ){
		BmpTalkWinClear( &wk->win[info], WINDOW_TRANS_OFF );
		GF_BGL_BmpWinOffVReq( &wk->win[info] );
	}

	BmpMenuWinClear( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF );

	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_MENU] );

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	GF_BGL_BmpWinDel( &wk->add_win[ADD_WIN_MENU] );

	GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], FBMP_COL_NULL );
	Bag_ItemInfoPut( wk, wk->dat->ret_item );
	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );

	BagObj_WazaIconPut( wk, 0, ACT_OFF );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�j���i�u���Ă�v�̏ꍇ�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
void Bag_ItemMenuExitSub( BAG_WORK * wk )
{
	BmpMenuWinClear( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF );

	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_MENU] );

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	GF_BGL_BmpWinDel( &wk->add_win[ADD_WIN_MENU] );
}
*/

//--------------------------------------------------------------------------------------------
/**
 * ����ւ����b�Z�[�W�\���i�ǂ��ɂ���܂����H�j
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void Bag_ItemChgInfoMsgSet( BAG_WORK * wk )
{
	STRBUF * msg;
	STRBUF * expb;

	GF_BGL_BmpWinDataFill( &wk->win[WIN_INFO], FBMP_COL_NULL );

	msg  = MSGMAN_AllocString( wk->msg_man, msg_bag_045 );
	expb = STRBUF_Create( BUFLEN_ITEM_INFO, HEAPID_BAG );

	ItemNameWordSet( wk, wk->irekae_pos-1, 0 );
	WORDSET_ExpandStr( wk->wset, expb, msg );

	GF_STR_PrintColor(
		&wk->win[WIN_INFO], FONT_SYSTEM, expb,
		NORMAL_INFO_PX, 0, MSG_NO_PUT, BAGCOL_N_WHITE, NULL );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );

	STRBUF_Delete( expb );
	STRBUF_Delete( msg );
}


//--------------------------------------------------------------------------------------------
/**
 * �̂Ă�֘A�E�B���h�E�Z�b�g
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void Bag_DelNumSelWinSet( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	STRBUF * msg;
	STRBUF * expb;
	u16	i;

	BmpMenuWinWrite(
		&wk->win[WIN_SUB], WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	Bag_SubNumPut( wk );

	BmpTalkWinWrite(
		&wk->win[WIN_MENU_INFO], WINDOW_TRANS_OFF, TALK_WIN_CGX_NUM, TALKWIN_PAL );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_MENU_INFO], FBMP_COL_WHITE );

	msg    = MSGMAN_AllocString( wk->msg_man, msg_bag_054 );
	expb   = STRBUF_Create( MENU_INFO_STRLEN, HEAPID_BAG );
	pocket = &wk->dat->p_data[ wk->dat->p_now ];

	ItemNameWordSet( wk, pocket->scr+pocket->cur-1, 0 );
	WORDSET_ExpandStr( wk->wset, expb, msg );

	GF_STR_PrintSimple( &wk->win[WIN_MENU_INFO], FONT_TALK, expb, 0, 0, MSG_NO_PUT, NULL );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_MENU_INFO] );

	STRBUF_Delete( expb );
	STRBUF_Delete( msg );
}

//--------------------------------------------------------------------------------------------
/**
 * �̂Ă���\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void Bag_SubNumPut( BAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * strb;
	u32	siz;

	win = &wk->win[WIN_SUB];

	GF_BGL_BmpWinDataFill( win, 15 );

	strb = MSGMAN_AllocString( wk->msg_man, mes_bag_093 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->sel_num, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, strb );
	GF_STR_PrintSimple( win, FONT_SYSTEM, wk->expb, 16, 8, MSG_NO_PUT, NULL );
	GF_BGL_BmpWinOnVReq( win );
	STRBUF_Delete( strb );
}

//--------------------------------------------------------------------------------------------
/**
 * �̂Ă�֘A�E�B���h�E�j��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void Bag_DelNumSelWinExit( BAG_WORK * wk )
{
	BmpTalkWinClear( &wk->win[WIN_MENU_INFO], WINDOW_TRANS_OFF );
	BmpMenuWinClear( &wk->win[WIN_SUB], WINDOW_TRANS_OFF );

	GF_BGL_BmpWinOffVReq( &wk->win[WIN_MENU_INFO] );
	GF_BGL_BmpWinOffVReq( &wk->win[WIN_SUB] );

	GF_BGL_BmpWinOnVReq( &wk->win[WIN_INFO] );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���ĂĂ������ł����H�v�\��
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */	
//--------------------------------------------------------------------------------------------
void Bag_SubTalkWinSet( BAG_WORK * wk )
{
	POCKET_DATA * pocket;
	STRBUF * msg;
	u16	i;

	BmpTalkWinWrite( &wk->win[WIN_TALK], WINDOW_TRANS_OFF, TALK_WIN_CGX_NUM, TALKWIN_PAL );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_TALK], 15 );

	msg    = MSGMAN_AllocString( wk->msg_man, msg_bag_056 );
	pocket = &wk->dat->p_data[ wk->dat->p_now ];

	ItemNameWordSet( wk, pocket->scr+pocket->cur-1, 0 );
	WORDSET_RegisterNumber(
		wk->wset, 1, wk->sel_num, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( wk->wset, wk->expb, msg );
	STRBUF_Delete( msg );
	wk->midx = Bag_TalkMsgPrint( wk );
}






u8 Bag_TalkMsgPrint( BAG_WORK * wk )
{
	u8	idx;

	MsgPrintSkipFlagSet( MSG_SKIP_ON );
	MsgPrintAutoFlagSet( MSG_AUTO_OFF );
	idx = GF_STR_PrintSimple(
			&wk->win[WIN_TALK], FONT_TALK,wk->expb, 0, 0,
			CONFIG_GetMsgPrintSpeed( wk->cfg ), BAG_TalkMsgCallBack );

	return idx;
}

//--------------------------------------------------------------------------------------------
/**
 * ��b�i���j���b�Z�[�W�R�[���o�b�N
 *
 * @param	mph		���b�Z�[�W�`��f�[�^
 * @param	value	�R�[���o�b�N�i���o
 *
 * @retval	"TRUE = �҂�"
 * @retval	"FALSE = ���̏�����"
 */
//--------------------------------------------------------------------------------------------
static BOOL BAG_TalkMsgCallBack( MSG_PRINT_HEADER * mph, u16 value )
{
	switch( value ){
	case 1:		// SE�I���҂�
		return Snd_SePlayCheckAll();

	case 2:		// ME�I���҂�
		return Snd_MePlayCheckBgmPlay();

	case 3:		// "���ǂ�����"
		Snd_SePlay( SEQ_SE_DP_PC_LOGIN );
		break;

	case 4:		// "���ǂ�����"��SE�I���҂�
		return Snd_SePlayCheck( SEQ_SE_DP_PC_LOGIN );
	}

	return FALSE;
}

void Bag_YesNoSelInit( BAG_WORK * wk )
{
	wk->mw = BmpYesNoSelectInit(
				wk->bgl, &YesNoBmpWin, MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_BAG );
}

void Bag_SaleNumWinPut( BAG_WORK * wk, u8 flg )
{
	GF_BGL_BMPWIN * win;
	STRBUF * strb;
	u32	siz;

	win = &wk->win[WIN_SALE_NUM];

	if( flg == 0 ){
		BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	}

	GF_BGL_BmpWinDataFill( win, 15 );

	strb = MSGMAN_AllocString( wk->msg_man, mes_shop_099 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->sel_num, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, strb );
	GF_STR_PrintSimple( win, FONT_SYSTEM, wk->expb, 0, 8, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );

	strb = MSGMAN_AllocString( wk->msg_man, mes_shop_100 );
	WORDSET_RegisterNumber( 
		wk->wset, 0, wk->sel_price*wk->sel_num, 6,
		NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->expb, strb );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->expb, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, wk->expb, NUMSEL_EX-siz, 8, MSG_NO_PUT, NULL );
	GF_BGL_BmpWinOnVReq( win );
	STRBUF_Delete( strb );
}



void Bag_GoldWinPut( BAG_WORK * wk, u8 flg )
{
	GF_BGL_BMPWIN * win;
	STRBUF * strb;
	u32	siz;

	win = &wk->win[WIN_GOLD];

	if( flg == 0 ){
		GF_BGL_BmpWinDataFill( win, 15 );
		BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
		strb = MSGMAN_AllocString( wk->msg_man, mes_shop_097 );
		GF_STR_PrintSimple( win, FONT_SYSTEM, strb, 0, 0, MSG_NO_PUT, NULL );
		STRBUF_Delete( strb );
	}else{
		GF_BGL_BmpWinFill( win, 15, 0, 16, GOLD_EX, 16 );
	}

	strb = MSGMAN_AllocString( wk->msg_man, mes_shop_098 );
	WORDSET_RegisterNumber(
		wk->wset, 0, MyStatus_GetGold(wk->myst),
		6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( wk->wset, wk->expb, strb );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->expb, 0 );
	GF_STR_PrintSimple(
		win, FONT_SYSTEM, wk->expb, GOLD_EX-siz, 16, MSG_NO_PUT, NULL );
	GF_BGL_BmpWinOnVReq( win );
	STRBUF_Delete( strb );
}


//--------------------------------------------------------------------------------------------
/**
 * �u�|�t�B���̂����v�\��
 */
//--------------------------------------------------------------------------------------------
void BagBmp_PorutoWinPut( BAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[WIN_PORUTO];

	GF_BGL_BmpWinDataFill( win, 15 );
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	str = MSGMAN_AllocString( wk->msg_man, msg_bag_polto_01 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, NULL );
	STRBUF_Delete( str );

	str = MSGMAN_AllocString( wk->msg_man, msg_bag_polto_02 );
	WORDSET_RegisterNumber(
		wk->wset, 0, PORUTO_GetDataNum(SaveData_GetPorutoBlock(wk->dat->sv)),
		3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );

	WORDSET_ExpandStr( wk->wset, wk->expb, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->expb, 0 );
	GF_STR_PrintSimple(
		win, FONT_SYSTEM, wk->expb, BMP_PORUTO_SX*8-siz, 16, MSG_NO_PUT, NULL );

	GF_BGL_BmpWinOnVReq( win );
}
