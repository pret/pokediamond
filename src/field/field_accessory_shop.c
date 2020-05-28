//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_accessory_shop.c
 *	@brief		�A�N�Z�T���[������
 *	@author		tomoya takahashi
 *	@data		2006.06.06
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "talk_msg.h"
#include "include/savedata/config.h"
#include "include/savedata/imageclip_data.h"
#include "include/itemtool/myitem.h"
#include "include/itemtool/nuts.h"

#include "include/system/wordset.h"
#include "include/system/msgdata.h"

#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_t03r0101.h"

#include "include/system/window.h"
#include "include/system/bmp_menu.h"
#include "include/system/fontproc.h"

#include "include/system/arc_util.h"

#include "fieldmap.h"

#include "include/system/bmp_list.h"
#include "include/application/imageClip/imc_drawdata_define.h"

#include "system/snd_play.h"
#include "system/snd_tool.h"

// ���X�g�㉺�A�C�R���p
#include "shop_gra.naix"


//////// accessory�V���b�v�f�[�^
#include "acce_shop.dat"


#define __FIELD_ACCESSORY_SHOP_H_GLOBAL
#include "field_accessory_shop.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Z���A�N�^�[
//=====================================
#define ACCE_SHOP_CLACT_WORK_NUM	( 2 )



//-------------------------------------
//	�풓�L�����N�^�@�p���b�g�ʒu
//=====================================
#define ACCE_SHOP_TALK_CHAROFS		( 1 )
#define ACCE_SHOP_TALK_PLTT			( 10 )
#define ACCE_SHOP_SYSTEM_CHAROFS	( 1+TALK_WIN_CGX_SIZ )
#define ACCE_SHOP_SYSTEM_PLTT		( 11 )
#define ACCE_SHOP_TALKFONT_PLTT			( 12 )
#define ACCE_SHOP_SYSTEMFONT_PLTT		( 13 )

#define ACCE_SHOP_FONTBMP_TALK_COLOR		( GF_PRINTCOLOR_MAKE(1,2,15) )
#define ACCE_SHOP_FONTBMP_SYS_COLOR			( GF_PRINTCOLOR_MAKE(1,2,15) )


//-------------------------------------
//	���C�����b�Z�[�W�\���̒萔
//=====================================
#define ACCE_SHOP_MAIN_MSGWIN_X		( 2 )
#define ACCE_SHOP_MAIN_MSGWIN_Y		( 19 )
#define ACCE_SHOP_MAIN_MSGWIN_SX	( 27 )
#define ACCE_SHOP_MAIN_MSGWIN_SY	( 4 )
#define ACCE_SHOP_MAIN_MSGWIN_CHAR	( ACCE_SHOP_SYSTEM_CHAROFS+MENU_WIN_CGX_SIZ )
#define ACCE_SHOP_MAIN_MSGWIN_PLTT	( ACCE_SHOP_TALKFONT_PLTT )

//-------------------------------------
//	�f�[�^��ʍ\���̒萔
//=====================================
#define ACCE_SHOP_DATA_WINWIN_X		( 1 )
#define ACCE_SHOP_DATA_WINWIN_Y		( 11 )
#define ACCE_SHOP_DATA_WINWIN_SX	( 14 )
#define ACCE_SHOP_DATA_WINWIN_SY	( 6 )
#define ACCE_SHOP_DATA_WINWIN_CHAR	( ACCE_SHOP_MAIN_MSGWIN_CHAR + (ACCE_SHOP_MAIN_MSGWIN_SX*ACCE_SHOP_MAIN_MSGWIN_SY) )
#define ACCE_SHOP_DATA_WINWIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )
enum{
	ACCE_SHOP_DATA_WIN_NUTS_NAME,
	ACCE_SHOP_DATA_WIN_NUTS_NEED,
	ACCE_SHOP_DATA_WIN_NUTS_HAVE,
	ACCE_SHOP_DATA_WIN_NUM,
};
#define ACCE_SHOP_DATA_WINWIN_DRAW_YOFS	( 16 )


//-------------------------------------
//	accessory���X�g�\���̒萔
//=====================================
#define ACCE_SHOP_LIST_WINWIN_X		( 17 )
#define ACCE_SHOP_LIST_WINWIN_Y		( 1 )
#define ACCE_SHOP_LIST_WINWIN_SX	( 14 )
#define ACCE_SHOP_LIST_WINWIN_SY	( 16 )
#define ACCE_SHOP_LIST_WINWIN_CHAR	( ACCE_SHOP_DATA_WINWIN_CHAR + (ACCE_SHOP_DATA_WINWIN_SX*ACCE_SHOP_DATA_WINWIN_SY) )
#define ACCE_SHOP_LIST_WINWIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )

#define ACCE_SHOP_LIST_WIN_DRAWLINE		( 7 )	// �\�����C��
#define ACCE_SHOP_LIST_WIN_DATA_X		( 16 )	// ���ڕ\���ʒu
#define ACCE_SHOP_LIST_WIN_CURSOR_X		( 0 )	// �J�[�\���\���ʒu
#define ACCE_SHOP_LIST_WIN_DRAW_Y		( 8 )	// �\���J�nY���W
#define ACCE_SHOP_LIST_WIN_FONT_COL_F	( 1 )	// �����F
#define ACCE_SHOP_LIST_WIN_FONT_COL_B	( 15 )	// �w�i�F
#define ACCE_SHOP_LIST_WIN_FONT_COL_S	( 2 )	// �e�F
#define ACCE_SHOP_LIST_WIN_MSG_SPC		( 0 )	// �����Ԋu
#define ACCE_SHOP_LIST_WIN_LINE_SPC		( 0 )	// ���C���Ԋu
#define ACCE_SHOP_LIST_WIN_PAGE_SKIP	( FALSE )	// �X�L�b�v
#define ACCE_SHOP_LIST_WIN_FONT			( FONT_SYSTEM )	// �����^�C�v
#define ACCE_SHOP_LIST_WIN_DISP			( 0 )

#define ACCE_SHOP_LIST_WIN_CLACT_RESNUM	( 4 )	// �L�����@�p���b�g�@�Z���@�Z���A�j��
#define ACCE_SHOP_LIST_WIN_CLACT_RESMAN_WORKNUM	( 1 )	// ���\�[�X�}�l�[�W�����[�N
#define ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID	( 5000 )
#define ACCE_SHOP_LIST_WIN_CLACT_OBJNUM	( 2 )

#define ACCE_SHOP_LIST_WIN_CLACT_X		( 192 )
#define ACCE_SHOP_LIST_WIN_CLACT_Y_0	( 8 )
#define ACCE_SHOP_LIST_WIN_CLACT_Y_1	( 136 )


//-------------------------------------
//	YESNO�E�B���h�E
//=====================================
#define ACCE_SHOP_YESNO_WIN_X	( 24 )		// ���ʒu
#define ACCE_SHOP_YESNO_WIN_Y	( 13 )		// ���ʒu
#define ACCE_SHOP_YESNO_WIN_SX	( 7 )		// ���T�C�Y
#define ACCE_SHOP_YESNO_WIN_SY	( 4 )		// y�T�C�Y
#define ACCE_SHOP_YESNO_WIN_CHAR	( ACCE_SHOP_LIST_WINWIN_CHAR + (ACCE_SHOP_LIST_WINWIN_SX*ACCE_SHOP_LIST_WINWIN_SY) )
#define ACCE_SHOP_YESNO_WIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )




//-------------------------------------
//	�S�̃V�[�P���X
//=====================================
enum{
	ACCE_SHOP_SEQ_STARTMSG,			// ����ɂ��́I
	ACCE_SHOP_SEQ_FULLHAVE_CHECK,	// �S�ẴA�N�Z�T���[�������Ă��邩�`�F�b�N
	ACCE_SHOP_SEQ_LIST_START,		// ���X�g��ʂ̊J�n
	ACCE_SHOP_SEQ_LIST_RESTART,		// ���X�g��ʂ̍ĊJ�n
	ACCE_SHOP_SEQ_LIST_MAIN,		// ���X�g�������C��

	ACCE_SHOP_SEQ_YESNO_START,		// �n�C�C�C�G
	ACCE_SHOP_SEQ_YESNO_MAIN,		// �n�C�C�C�G

	ACCE_SHOP_SEQ_GET_ACCE,			// �A�N�Z�T����������
	ACCE_SHOP_SEQ_GET_ACCE_FULL,	// �A�N�Z�T���S�����܂���
	ACCE_SHOP_SEQ_GET_ACCE_FULL2,	// �A�N�Z�T���S�����܂���

	ACCE_SHOP_SEQ_MSG_WAIT,	// ���b�Z�[�W�҂�
	ACCE_SHOP_SEQ_KEY_WAIT,	// �L�[�҂�
	ACCE_SHOP_SEQ_END,		// �I���
};



//-------------------------------------
//	����`
//=====================================
#define ACCE_SHOP_SND_KEY_ON	( SEQ_SE_DP_SELECT )		// �L�[�҂��ŉ����ꂽ�Ƃ��̉�
#define ACCE_SHOP_SND_LIST_MOVE	( SEQ_SE_DP_SELECT )		// ���X�g������
#define ACCE_SHOP_SND_LIST_SELECT	( SEQ_SE_DP_SELECT )	// ���X�g����
#define ACCE_SHOP_SND_LIST_CANCEL	( SEQ_SE_DP_SELECT )	// CANCEL


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------




//-------------------------------------
//	���C�����b�Z�[�W�\����
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	u32 msg_speed;
	u32 msg_idx;
	STRBUF* p_str;	// �\�����̕�����o�b�t�@
} ACCE_SHOP_MAIN_MSG;

//-------------------------------------
//	�����f�[�^�E�B���h�E
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	WORDSET* p_wordset;
	STRBUF* p_drawstr;
	STRBUF* p_wordstr[ACCE_SHOP_DATA_WIN_NUM];
} ACCE_SHOP_DATA_WIN;

#define ACCE_SHOP_DATA_LIST_NUM	( ACCE_SHOP_DATA_NUM + 1 )
//-------------------------------------
//	���X�g�E�B���h�E
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	BMPLIST_WORK* p_bmplist;
	BMPLIST_DATA list[ ACCE_SHOP_DATA_LIST_NUM ];
	STRBUF* p_list_str[ ACCE_SHOP_DATA_LIST_NUM ];
	s32 data_num;
	WORDSET* p_wordset;
	STRBUF* p_drawstr;
	u16 now_pos;
	u16 now_pos_param;
	void* p_work;		// ���X�g���������Ƃ��ɌĂԃR�[���o�b�N���[�N
	void (*callback)( void* p_work, u32 listnum );	// �R�[���o�b�N�֐�


	// �Z���A�N�^�[
	CLACT_U_RES_MANAGER_PTR	resMan[ACCE_SHOP_LIST_WIN_CLACT_RESNUM];	// ���\�[�X�}�l�[�W��
	CLACT_U_RES_OBJ_PTR		resObj[ACCE_SHOP_LIST_WIN_CLACT_RESNUM];	// ���ꂼ��̃��\�[�X�I�u�W�F��
	CLACT_WORK_PTR clact[ ACCE_SHOP_LIST_WIN_CLACT_OBJNUM ];
} ACCE_SHOP_LIST_WIN;
typedef void (*pAcceListMoveFunc)( void* p_work, u32 listnum );

//-------------------------------------
//	YES NO �E�B���h�E�I�u�W�F
//=====================================
typedef struct {
	u32 init;
	BMPMENU_WORK* p_yesno;	// YESNO���j���[
	u32 heapID;				// �q�[�v
} ACCE_SHOP_YESNO_MENU;


//-------------------------------------
//	���X�g���쎞
//	�f�[�^�E�B���h�E�ύX	�������[�N
//=====================================
typedef struct {
	u32 heapID;
	GF_BGL_INI* p_bgl;
	ACCE_SHOP_DATA_WIN* p_data_wnd;	// �f�[�^���b�Z�[�W�E�B���h�E
	const ACCE_SHOP_DATA* cp_data;	// �f�[�^
	MYITEM* p_myitem;		// �A�C�e��
} ACCE_SHOP_DATA_WIN_CHG;



//-------------------------------------
//	accessory������
//=====================================
typedef struct _FIELD_ACCE_SHOP{
	u32 seq;
	u32 seq_sub;
	SAVEDATA* p_savedata;
	IMC_ITEM_SAVEDATA* p_item;
	MYITEM* p_myitem;
	GF_BGL_INI* p_bgl;
	u32 heapID;
	CLACT_SET_PTR			clactSet;	// �Z���A�N�^�[�Z�b�g
	CLACT_U_EASYRENDER_DATA	renddata;	// �ȈՃ����_�[�f�[�^

	// ���b�Z�[�W�}�l�[�W��
	MSGDATA_MANAGER* p_msgman;

	// �R���t�B�O�f�[�^
	u32 win_type;
	u32 msg_speed;
	
	// �e�`��Ǘ��I�u�W�F
	ACCE_SHOP_MAIN_MSG main_msgwnd;	// ���C�����b�Z�[�W�E�B���h�E
	ACCE_SHOP_DATA_WIN data_msgwnd;	// �f�[�^���b�Z�[�W�E�B���h�E
	ACCE_SHOP_LIST_WIN list_wnd;	// ���X�g�E�B���h�E
	ACCE_SHOP_YESNO_MENU yes_no;	// �͂��@�������@���j���[
	
	// �\���ύX�I�u�W�F
	ACCE_SHOP_DATA_WIN_CHG data_msgwnd_chg;	// �f�[�^�E�B���h�E�ύX
} ;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void AcceShop_BGL_Init( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_BGL_Delete( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_CLACT_Init( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_CLACT_Delete( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_ConfigGet( FIELD_ACCE_SHOP* p_acce_shop );


static void AcceShop_MainMsgInit( ACCE_SHOP_MAIN_MSG* p_win, GF_BGL_INI* p_bgl, u32 heapID, u32 msg_speed );
static void AcceShop_MainMsgDelete( ACCE_SHOP_MAIN_MSG* p_win );
static void AcceShop_MainMsgSet( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str, u32 heapID );
static void AcceShop_MainMsgSet_noWait( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str );
static BOOL AcceShop_MainMsgWait( ACCE_SHOP_MAIN_MSG* p_win );

static void AcceShop_MainMsgChangeStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx );
static void AcceShop_MainMsgChangeEndStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx );


static void AcceShop_DataMsgInit( ACCE_SHOP_DATA_WIN* p_win, GF_BGL_INI* p_bgl, MSGDATA_MANAGER* p_msgman, u32 heapID );
static void AcceShop_DataMsgDelete( ACCE_SHOP_DATA_WIN* p_win );
static void AcceShop_DataMsgSet( ACCE_SHOP_DATA_WIN* p_win, u32 nut, u32 nut_need_num, u32 nut_get_num );

static void AcceShop_ListWinInit( ACCE_SHOP_LIST_WIN* p_win, GF_BGL_INI* p_bgl, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_num, MSGDATA_MANAGER* p_msgman, void* p_work, pAcceListMoveFunc callback, CLACT_SET_PTR clact_set );
static void AcceShop_ListWinDelete( ACCE_SHOP_LIST_WIN* p_win );
static u32 AcceShop_ListWinMain( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinReTrans( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinDrawClean( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinClactResLoad( CLACT_HEADER* p_head, ACCE_SHOP_LIST_WIN* p_win, u32 heapID );
static void AcceShop_ListWinClactResDelete( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinClactDrawSet( ACCE_SHOP_LIST_WIN* p_win );


static void AcceShop_YesNoWinInit( ACCE_SHOP_YESNO_MENU* p_win, GF_BGL_INI* p_bgl, u32 heapID );
static void AcceShop_YesNoWinDelete( ACCE_SHOP_YESNO_MENU* p_win );
static u32 AcceShop_YesNoWinMain( ACCE_SHOP_YESNO_MENU* p_win );


// ���X�g�̃R�[���o�b�N�ŁA�f�[�^�E�B���h�E��ύX����
static void AcceShop_DataWinChgDataInit( ACCE_SHOP_DATA_WIN_CHG* p_obj, ACCE_SHOP_DATA_WIN* data_win, const ACCE_SHOP_DATA* cp_data, MYITEM* p_save, u32 heapID, GF_BGL_INI* p_bgl );
static void AcceShop_DataWinChgCallBack( void* p_work, u32 listnum );

static BOOL AcceShop_FullAcceCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_num );
static BOOL AcceShop_NutsOkCheck( MYITEM* p_save, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID );
static BOOL AcceShop_AcceHaveOkCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_idx );

// �A�C�e����������
static void AcceShop_AcceChange( IMC_ITEM_SAVEDATA* p_acceitem, MYITEM* p_myitem, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID );




//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���V���b�v�쐬
 *
 *	@param	heapID		�q�[�vID
 *	@param	p_save		�Z�[�u�f�[�^
 *	@param	p_bgl		BGL
 *
 *	@return	���[�N
 */
//-----------------------------------------------------------------------------
FIELD_ACCE_SHOP* FIELD_AcceShop_Alloc( u32 heapID, SAVEDATA* p_save, GF_BGL_INI* p_bgl )
{
	FIELD_ACCE_SHOP* p_acce_shop = sys_AllocMemory( heapID, sizeof(FIELD_ACCE_SHOP) );
	memset( p_acce_shop, 0, sizeof(FIELD_ACCE_SHOP) );

	p_acce_shop->heapID = heapID;
	p_acce_shop->p_bgl = p_bgl;
	p_acce_shop->p_savedata = p_save;

	// �C���[�W�N���b�v�A�N�Z�T���f�[�^
	p_acce_shop->p_item = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData( p_acce_shop->p_savedata ) );

	// myitem
	p_acce_shop->p_myitem = SaveData_GetMyItem( p_save );

	// ���b�Z�[�W�}�l�[�W���쐬
	p_acce_shop->p_msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_t03r0101_dat, p_acce_shop->heapID );

	// �R���t�B�O������
	AcceShop_ConfigGet( p_acce_shop );

	// BGL������
	AcceShop_BGL_Init( p_acce_shop );

	// �Z���A�N�^�[
	AcceShop_CLACT_Init( p_acce_shop );

	return p_acce_shop;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���V���b�v�j��
 *
 *	@param	p_acce_shop		���[�N
 */
//-----------------------------------------------------------------------------
void FIELD_AcceShop_Free( FIELD_ACCE_SHOP* p_acce_shop )
{
	// ���b�Z�[�W�}�l�[�W���j��
	MSGMAN_Delete( p_acce_shop->p_msgman );
	
	// BGL�j��
	AcceShop_BGL_Delete( p_acce_shop );

	// �Z���A�N�^-
	AcceShop_CLACT_Delete( p_acce_shop );

	memset( p_acce_shop, 0, sizeof(FIELD_ACCE_SHOP) );
	sys_FreeMemoryEz( p_acce_shop );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���V���b�v�@���C��
 *
 *	@param	p_acce_shop		���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL FIELD_AcceShop_Main( FIELD_ACCE_SHOP* p_acce_shop )
{
	STRBUF* p_str;
	BOOL result;
	
	switch( p_acce_shop->seq ){
	case ACCE_SHOP_SEQ_STARTMSG:			// ����ɂ��́I
		AcceShop_MainMsgInit( &p_acce_shop->main_msgwnd, 
				p_acce_shop->p_bgl, p_acce_shop->heapID, p_acce_shop->msg_speed );

		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_01 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_FULLHAVE_CHECK;
		break;

	case ACCE_SHOP_SEQ_FULLHAVE_CHECK:	// �S�ẴA�N�Z�T���[�������Ă��邩�`�F�b�N
		// �A�N�Z�T���t���Ɏ����Ă��邩�`�F�b�N
		if( AcceShop_FullAcceCheck( p_acce_shop->p_item, AcceShopData, ACCE_SHOP_DATA_NUM ) ){

			// �t���Ɏ����Ă���
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_02 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �I����
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
		}else{
			// �t���Ɏ����Ă��Ȃ�
			p_acce_shop->seq = ACCE_SHOP_SEQ_LIST_START;
		}
		break;
		
	case ACCE_SHOP_SEQ_LIST_START:		// ���X�g��ʂ̊J�n
		AcceShop_DataMsgInit( &p_acce_shop->data_msgwnd, 
				p_acce_shop->p_bgl, p_acce_shop->p_msgman, 
				p_acce_shop->heapID );
		AcceShop_DataWinChgDataInit( &p_acce_shop->data_msgwnd_chg,
				&p_acce_shop->data_msgwnd,
				AcceShopData, p_acce_shop->p_myitem, 
				p_acce_shop->heapID, p_acce_shop->p_bgl );
		AcceShop_ListWinInit( &p_acce_shop->list_wnd, 
				p_acce_shop->p_bgl, p_acce_shop->heapID,
				AcceShopData, ACCE_SHOP_DATA_NUM, p_acce_shop->p_msgman,
				&p_acce_shop->data_msgwnd_chg, AcceShop_DataWinChgCallBack, p_acce_shop->clactSet );
		// ����������
	case ACCE_SHOP_SEQ_LIST_RESTART:		// ���X�g��ʂ̍ĊJ�n
		AcceShop_ListWinReTrans( &p_acce_shop->list_wnd );

		// �ǂ̃A�N�Z�T�����ق����H
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_03 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_MSG_WAIT;
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_MAIN;
		break;
		
	case ACCE_SHOP_SEQ_LIST_MAIN:		// ���X�g�������C��
		result = AcceShop_ListWinMain( &p_acce_shop->list_wnd );
		
		if( (result != BMPLIST_NULL) && (result != BMPLIST_CANCEL) ){

			// ���X�g�\���̈�̃X�N���[����������
			GF_BGL_ScrFill( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
				0, 0, 0, 32, 18, GF_BGL_SCRWRT_PALIN );

			// OAMOFF
			AcceShop_ListWinDrawClean( &p_acce_shop->list_wnd );

			// ���C���E�B���h�E�ύX
			AcceShop_MainMsgChangeStrSet( &p_acce_shop->main_msgwnd, p_acce_shop->p_msgman, p_acce_shop->heapID, AcceShopData, p_acce_shop->list_wnd.now_pos );	

			p_acce_shop->seq = ACCE_SHOP_SEQ_MSG_WAIT;
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_YESNO_START;

			Snd_SePlay( ACCE_SHOP_SND_LIST_SELECT );
			
		}else if( result == BMPLIST_CANCEL ){
			// �܂��ǂ���
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_08 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �I����
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
			
			Snd_SePlay( ACCE_SHOP_SND_LIST_CANCEL );
		}
		break;
		
	case ACCE_SHOP_SEQ_YESNO_START:		// �n�C�C�C�G
		// �͂��A�������@�E�B���h�E�\��
		AcceShop_YesNoWinInit( &p_acce_shop->yes_no, p_acce_shop->p_bgl, p_acce_shop->heapID );

		p_acce_shop->seq = ACCE_SHOP_SEQ_YESNO_MAIN;
		break;
		
	case ACCE_SHOP_SEQ_YESNO_MAIN:		// �n�C�C�C�G
		result = AcceShop_YesNoWinMain( &p_acce_shop->yes_no );
		if( result == 0 ){
			// �n�C�I��
			// �؂̎�����Ă邩�`�F�b�N
			if( AcceShop_NutsOkCheck( p_acce_shop->p_myitem, AcceShopData, p_acce_shop->list_wnd.now_pos, p_acce_shop->heapID ) == FALSE ){
				
				// �؂̎�������Ȃ���I
				p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_06 );
				AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
				STRBUF_Delete( p_str );
				p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// ���C���ւ�
				p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
				AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
				break;
			}

			// ����ȏ�A�N�Z�T�������o���邩�`�F�b�N
			if( AcceShop_AcceHaveOkCheck( p_acce_shop->p_item, AcceShopData, p_acce_shop->list_wnd.now_pos ) == FALSE ){

				// ����ȏ���ĂȂ�
				p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_07 );
				AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
				STRBUF_Delete( p_str );

				AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
				p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// ���C����
				p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
				break;
			}

			// �ǂ������肪�Ƃ�
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_05 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );

			AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );

			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �A�N�Z�T��������
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE;

		}else if( result == BMPMENU_CANCEL ){
			// �C�C�G�I��
			AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
			p_acce_shop->seq = ACCE_SHOP_SEQ_LIST_RESTART;
		}
		break;
		
	case ACCE_SHOP_SEQ_GET_ACCE:			// �A�N�Z�T����������
		// �A�N�Z�T���ƃA�C�e���ݒ�
		AcceShop_AcceChange( p_acce_shop->p_item, p_acce_shop->p_myitem, AcceShopData, p_acce_shop->list_wnd.now_pos, p_acce_shop->heapID );

		// �������b�Z�[�W�\��
		AcceShop_MainMsgChangeEndStrSet( &p_acce_shop->main_msgwnd, p_acce_shop->p_msgman, p_acce_shop->heapID, AcceShopData, p_acce_shop->list_wnd.now_pos );

		// �S���W�܂�����
		if( AcceShop_FullAcceCheck( p_acce_shop->p_item, AcceShopData, ACCE_SHOP_DATA_NUM ) ){
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �S���W�܂���������
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE_FULL;
		}else{
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// ������x
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
		}
		break;

	case ACCE_SHOP_SEQ_GET_ACCE_FULL:	// �A�N�Z�T���S�����܂���
		// �S���W�߂Ă���Ă��肪�Ƃ�
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_10 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �S���W�܂���������
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE_FULL2;
		break;

	case ACCE_SHOP_SEQ_GET_ACCE_FULL2:	// �A�N�Z�T���S�����܂���
		// �S���W�߂Ă���Ă��肪�Ƃ�
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_02 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// �I����
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
		break;


	case ACCE_SHOP_SEQ_MSG_WAIT:	// ���b�Z�[�W�҂�
		if( AcceShop_MainMsgWait( &p_acce_shop->main_msgwnd ) ){
			p_acce_shop->seq = p_acce_shop->seq_sub;
		}
		break;
		
	case ACCE_SHOP_SEQ_KEY_WAIT:// �L�[�҂�
		if( AcceShop_MainMsgWait( &p_acce_shop->main_msgwnd ) ){
			if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)  ){
				p_acce_shop->seq = p_acce_shop->seq_sub;
			}
		}
		break;
		
	case ACCE_SHOP_SEQ_END:		// �I���
		// �I������
		AcceShop_MainMsgDelete( &p_acce_shop->main_msgwnd );	
		AcceShop_DataMsgDelete( &p_acce_shop->data_msgwnd );	
		AcceShop_ListWinDelete( &p_acce_shop->list_wnd );	
		AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );	
		return TRUE;

	default:
		break;
	}

	CLACT_Draw( p_acce_shop->clactSet );
	
	return FALSE;
}





//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	�R���t�B�O�f�[�^�擾
 *
 *	@param	p_acce_shop		���[�N
 */
//-----------------------------------------------------------------------------
static void AcceShop_ConfigGet( FIELD_ACCE_SHOP* p_acce_shop )
{
	CONFIG * cfg = SaveData_GetConfig( p_acce_shop->p_savedata );
	p_acce_shop->win_type = CONFIG_GetWindowType( cfg );
	p_acce_shop->msg_speed = CONFIG_GetMsgPrintSpeed( cfg );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGL�������@���b�Z�[�W�p�ʂ́@BG�R���g�p
 *
 *	@param	p_acce_shop 
 */
//-----------------------------------------------------------------------------
static void AcceShop_BGL_Init( FIELD_ACCE_SHOP* p_acce_shop )
{
	// �g�[�N�E�B���h�E
	// �V�X�e���E�B���h�E
	// ������
	TalkWinGraphicSet( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
			ACCE_SHOP_TALK_CHAROFS,
			ACCE_SHOP_TALK_PLTT,
			p_acce_shop->win_type, 
			p_acce_shop->heapID );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 
			ACCE_SHOP_TALKFONT_PLTT * 32, 
			p_acce_shop->heapID );
	MenuWinGraphicSet( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
			ACCE_SHOP_SYSTEM_CHAROFS,
			ACCE_SHOP_SYSTEM_PLTT,
			p_acce_shop->win_type, 
			p_acce_shop->heapID );
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 
			ACCE_SHOP_SYSTEMFONT_PLTT * 32, 
			p_acce_shop->heapID );
	
	// �X�N���[���N���[��	
	GF_BGL_ScrClear( p_acce_shop->p_bgl, FLD_MBGFRM_FONT );
}

static void AcceShop_BGL_Delete( FIELD_ACCE_SHOP* p_acce_shop )
{
	// �X�N���[���N���[��	
	GF_BGL_ScrClear( p_acce_shop->p_bgl, FLD_MBGFRM_FONT );

	// �t�B�[���h�풓�L�����N�^���A
	FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�ݒ�
 *
 *	@param	p_acce_shop 
 */
//-----------------------------------------------------------------------------
static void AcceShop_CLACT_Init( FIELD_ACCE_SHOP* p_acce_shop )
{
	p_acce_shop->clactSet = CLACT_U_SetEasyInit( ACCE_SHOP_CLACT_WORK_NUM , &p_acce_shop->renddata, p_acce_shop->heapID );
}
static void AcceShop_CLACT_Delete( FIELD_ACCE_SHOP* p_acce_shop )
{
	CLACT_DestSet( p_acce_shop->clactSet );
}



//----------------------------------------------------------------------------
/**
 *	@brief	���C�����b�Z�[�W�E�B���h�E�@�I�u�W�F�@������
 *
 *	@param	p_win		�E�B���h�E�I�u�W�F
 *	@param	p_bgl		BGL
 *	@param	heapID		�q�[�vID
 *	@param	msg_speed	���b�Z�[�W�X�s�[�h
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgInit( ACCE_SHOP_MAIN_MSG* p_win, GF_BGL_INI* p_bgl, u32 heapID, u32 msg_speed )
{
	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->msg_speed = msg_speed;
	
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// �r�b�g�}�b�v�E�B���h�E�m��
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_MAIN_MSGWIN_X, ACCE_SHOP_MAIN_MSGWIN_Y,
			ACCE_SHOP_MAIN_MSGWIN_SX, ACCE_SHOP_MAIN_MSGWIN_SY,
			ACCE_SHOP_MAIN_MSGWIN_PLTT, ACCE_SHOP_MAIN_MSGWIN_CHAR );

	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	// �g�`��
	BmpTalkWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_TALK_CHAROFS, ACCE_SHOP_TALK_PLTT );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�����b�Z�[�W�I�u�W�F�@�j��
 *
 *	@param	p_win	�E�B���h�E�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgDelete( ACCE_SHOP_MAIN_MSG* p_win )
{
	if( p_win->init == 0 ){
		return ;
	}
	
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C�����b�Z�[�W�ݒ�
 *
 *	@param	p_win		�E�B���h�E�I�u�W�F
 *	@param	p_str		������
 *	@param	heapID
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgSet( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str, u32 heapID )
{
	GF_ASSERT( p_win->p_str == NULL );
	
	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	p_win->p_str = STRBUF_CreateBufferCopy( p_str, heapID );
	
	p_win->msg_idx = GF_STR_PrintColor( p_win->p_bmp, FONT_TALK, p_win->p_str, 0, 0, p_win->msg_speed, ACCE_SHOP_FONTBMP_TALK_COLOR, NULL );

	GF_BGL_BmpWinOn( p_win->p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�Z�[�W�E�G�C�g�Ȃ�
 *
 *	@param	p_win	�E�B���h�E
 *	@param	p_str	������
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgSet_noWait( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str )
{
	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );
	p_win->msg_idx = GF_STR_PrintColor( p_win->p_bmp, FONT_TALK, p_str, 0, 0, MSG_NO_PUT, ACCE_SHOP_FONTBMP_TALK_COLOR, NULL );

	GF_BGL_BmpWinOn( p_win->p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���b�Z�[�W�I���҂�
 *	
 *	@param	p_win	�E�B���h�E�I�u�W�F
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_MainMsgWait( ACCE_SHOP_MAIN_MSG* p_win )
{
	if( GF_MSG_PrintEndCheck( p_win->msg_idx ) == 0 ){

		// �ێ����Ă���������o�b�t�@�j��
		if( p_win->p_str != NULL ){
			STRBUF_Delete( p_win->p_str );
			p_win->p_str = NULL;
		}
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C����ʂɁ@�`�Ɓ`���������܂����H�@�e�L�X�g���o��
 *
 *	@param	p_win		�E�B���h�E�I�u�W�F
 *	@param	p_msgman	���b�Z�[�W�}�l�[�W��
 *	@param	heapID		�q�[�v
 *	@param	cp_data		�V���b�v�f�[�^
 *	@param	data_idx	�\���f�[�^�C���f�b�N�X
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgChangeStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	STRBUF* p_str;
	STRBUF* p_drawstr;
	WORDSET* p_wordset;
	
	// �ȈՉ�b�쐬
	p_wordset = WORDSET_Create( heapID );

	// �W�J�敶����쐬
	p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_01_04 );
	
	WORDSET_RegisterItemName( p_wordset, 0, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_wordset, 1, cp_data[ data_idx ].need_num,
			3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterAccessoryName( p_wordset, 2, cp_data[ data_idx ].acce_no );
	WORDSET_ExpandStr( p_wordset, p_drawstr, p_str );

	// �e�L�X�g�ݒ�
	AcceShop_MainMsgSet( p_win, p_drawstr, heapID );
	
	WORDSET_Delete( p_wordset );
	STRBUF_Delete( p_drawstr );
	STRBUF_Delete( p_str );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����I��	������\��
 *
 *	@param	p_win		���C���E�B���h�E�I�u�W�F
 *	@param	p_msgman	���b�Z�[�W�}�l�[�W��
 *	@param	heapID		�q�[�vID
 *	@param	cp_data		�f�[�^
 *	@param	data_idx	�f�[�^�C���f�b�N�X
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgChangeEndStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	STRBUF* p_str;
	STRBUF* p_drawstr;
	WORDSET* p_wordset;
	
	// �ȈՉ�b�쐬
	p_wordset = WORDSET_Create( heapID );

	// �W�J�敶����쐬
	p_drawstr = STRBUF_Create( 200, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_01_09 );
	
	WORDSET_RegisterItemName( p_wordset, 0, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_wordset, 1, cp_data[ data_idx ].need_num,
			3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterAccessoryName( p_wordset, 2, cp_data[ data_idx ].acce_no );
	WORDSET_ExpandStr( p_wordset, p_drawstr, p_str );

	// �e�L�X�g�ݒ�
	AcceShop_MainMsgSet( p_win, p_drawstr, heapID );
	
	WORDSET_Delete( p_wordset );
	STRBUF_Delete( p_drawstr );
	STRBUF_Delete( p_str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�[�^��ʏ�����
 *
 *	@param	p_win		�E�B���h�E�I�u�W�F
 *	@param	p_bgl		BGL
 *	@param	heapID		�q�[�v
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgInit( ACCE_SHOP_DATA_WIN* p_win, GF_BGL_INI* p_bgl, MSGDATA_MANAGER* p_msgman, u32 heapID )
{
	int i;

	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// �r�b�g�}�b�v�E�B���h�E�m��
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_DATA_WINWIN_X, ACCE_SHOP_DATA_WINWIN_Y,
			ACCE_SHOP_DATA_WINWIN_SX, ACCE_SHOP_DATA_WINWIN_SY,
			ACCE_SHOP_DATA_WINWIN_PLTT, ACCE_SHOP_DATA_WINWIN_CHAR );


	// �ȈՉ�b�쐬
	p_win->p_wordset = WORDSET_Create( heapID );
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		p_win->p_wordstr[i] = MSGMAN_AllocString( p_msgman, mes_accessory_03_01+i );
	}

	// �W�J�敶����쐬
	p_win->p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );


	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�[�^��ʔj��
 *	
 *	@param	p_win	�E�B���h�E�I�u�W�F
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgDelete( ACCE_SHOP_DATA_WIN* p_win )
{
	int i;

	if( p_win->init == 0 ){
		return ;
	}
	
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		// ������j��
		STRBUF_Delete( p_win->p_wordstr[i] );
	}
	STRBUF_Delete( p_win->p_drawstr );


	WORDSET_Delete( p_win->p_wordset );	
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�[�^�E�B���h�E�ݒ�
 *
 *	@param	p_win		�E�B���h�E
 *	@param	nut			�؂̎�	�i����i���o�[�j
 *	@param	nut_need_num�؂̎������ɕK�v�Ȑ�
 *	@param	nut_get_num	�؂̎��ێ���
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgSet( ACCE_SHOP_DATA_WIN* p_win, u32 nut, u32 nut_need_num, u32 nut_get_num )
{
	int i;

	// ���[�h�Z�b�g
	WORDSET_RegisterItemName( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_NAME, nut + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_NEED,
			nut_need_num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_HAVE,
			nut_get_num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );

	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	// ������W�J
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		WORDSET_ExpandStr( p_win->p_wordset, p_win->p_drawstr, p_win->p_wordstr[ i ] );

		GF_STR_PrintColor( p_win->p_bmp, FONT_SYSTEM, p_win->p_drawstr,
				0, 
				ACCE_SHOP_DATA_WINWIN_DRAW_YOFS * i,
				MSG_NO_PUT, ACCE_SHOP_FONTBMP_SYS_COLOR, NULL );
	}

	// �g�̕`��
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�E�B���h�E������
 *
 *	@param	p_win		���[�N
 *	@param	p_bgl		BGL
 *	@param	heapID		�q�[�v
 *	@param	cp_data		�f�[�^�e�[�u��
 *	@param	data_num	�f�[�^��
 *	@param	p_msgman	���b�Z�[�W�}�l�[�W��
 *	@param	clact_set	�Z���A�N�^�[�Z�b�g
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinInit( ACCE_SHOP_LIST_WIN* p_win, GF_BGL_INI* p_bgl, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_num, MSGDATA_MANAGER* p_msgman, void* p_work, pAcceListMoveFunc callback, CLACT_SET_PTR clact_set )
{
	int i;
	STRBUF* p_str;
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;

	static const u8 CLACT_Add_Y[ ACCE_SHOP_LIST_WIN_CLACT_OBJNUM ] = {
		ACCE_SHOP_LIST_WIN_CLACT_Y_0,
		ACCE_SHOP_LIST_WIN_CLACT_Y_1
	};
	static BMPLIST_HEADER BmpListHeader = {
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		ACCE_SHOP_LIST_WIN_DRAWLINE,
		0,
		ACCE_SHOP_LIST_WIN_DATA_X,
		ACCE_SHOP_LIST_WIN_CURSOR_X,
		ACCE_SHOP_LIST_WIN_DRAW_Y,
		ACCE_SHOP_LIST_WIN_FONT_COL_F,
		ACCE_SHOP_LIST_WIN_FONT_COL_B,
		ACCE_SHOP_LIST_WIN_FONT_COL_S,
		ACCE_SHOP_LIST_WIN_MSG_SPC,
		ACCE_SHOP_LIST_WIN_LINE_SPC,
		ACCE_SHOP_LIST_WIN_PAGE_SKIP,
		ACCE_SHOP_LIST_WIN_FONT,
		ACCE_SHOP_LIST_WIN_DISP,
		NULL
	};

	if( p_win->init == 1 ){
		return ;
	}

	
	p_win->init = 1;

	p_win->data_num = data_num + 1;
	
	p_win->p_work = p_work;
	p_win->callback = callback;
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// �r�b�g�}�b�v�E�B���h�E�m��
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_LIST_WINWIN_X, ACCE_SHOP_LIST_WINWIN_Y,
			ACCE_SHOP_LIST_WINWIN_SX, ACCE_SHOP_LIST_WINWIN_SY,
			ACCE_SHOP_LIST_WINWIN_PLTT, ACCE_SHOP_LIST_WINWIN_CHAR );

	// �ȈՉ�b�쐬
	p_win->p_wordset = WORDSET_Create( heapID );

	// �W�J�敶����쐬
	p_win->p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_03_01 );
	
	// ���X�g�f�[�^�쐬
	for( i=0; i<data_num; i++ ){
		WORDSET_RegisterAccessoryName( p_win->p_wordset, 0, cp_data[ i ].acce_no );
		WORDSET_ExpandStr( p_win->p_wordset, p_win->p_drawstr, p_str );
		p_win->p_list_str[ i ] = STRBUF_CreateBufferCopy( p_win->p_drawstr, heapID );
		p_win->list[ i ].str = p_win->p_list_str[ i ];
		p_win->list[ i ].param = i;
	}
	
	// �I���
	p_win->p_list_str[ data_num ] = MSGMAN_AllocString( p_msgman, mes_accessory_04_01 );
	p_win->list[ data_num ].str = p_win->p_list_str[ data_num ];
	p_win->list[ data_num ].param = data_num;
	
	WORDSET_Delete( p_win->p_wordset );
	STRBUF_Delete( p_win->p_drawstr );
	STRBUF_Delete( p_str );

	// �r�b�g�}�b�v���X�g�ɐݒ�
	BmpListHeader.win = p_win->p_bmp;
	BmpListHeader.count = p_win->data_num;
	BmpListHeader.list = p_win->list;
	p_win->p_bmplist = BmpListSet( &BmpListHeader, 0, 0, heapID );

	// �g�̕`��
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );

	// ���\�[�X�}�l�[�W���쐬
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_RESNUM; i++ ){
		p_win->resMan[ i ] = CLACT_U_ResManagerInit( ACCE_SHOP_LIST_WIN_CLACT_RESMAN_WORKNUM,
				i, heapID );
	}

	// ���\�[�X�ǂݍ���
	AcceShop_ListWinClactResLoad( &head, p_win, heapID );

	// �A�N�^�[�̓o�^
	add.ClActSet = clact_set;
	add.ClActHeader = &head;
	add.pri		= 0;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap	= heapID;
	add.mat.x	= ACCE_SHOP_LIST_WIN_CLACT_X * FX32_ONE;
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_OBJNUM; i++ ){
		add.mat.y	= CLACT_Add_Y[ i ] * FX32_ONE;
		p_win->clact[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_win->clact[ i ], i );
		CLACT_SetAnmFlag( p_win->clact[ i ], TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�E�B���h�E�j��
 *
 *	@param	p_win	���[�N
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinDelete( ACCE_SHOP_LIST_WIN* p_win )
{
	int i;

	if( p_win->init == 0 ){
		return ;
	}

	// �A�N�^�[�j��
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_OBJNUM; i++ ){

		CLACT_Delete( p_win->clact[ i ] );
	}

	// �A�N�^�[���\�[�X�j��
	AcceShop_ListWinClactResDelete( p_win );

	// ���X�g�Ȃ������j��
	for( i=0; i<p_win->data_num; i++ ){
		STRBUF_Delete( p_win->p_list_str[ i ] );
	}

	// �r�b�g�}�b�v���X�g�j��
	BmpListExit( p_win->p_bmplist, NULL, NULL );
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�E�B���h�E�@���C��
 *
 *	@param	p_win	�E�B���h�E
 *
 *	@retval	"param = �I���p�����[�^"
 *	@retval	"BMPLIST_NULL = �I��"
 *	@retval	"BMPLIST_CANCEL	= �L�����Z��(�a�{�^��)"
 */
//-----------------------------------------------------------------------------
static u32 AcceShop_ListWinMain( ACCE_SHOP_LIST_WIN* p_win )
{
	u32 result;
	u16 now_pos;
	
	result = BmpListMain( p_win->p_bmplist );

	// �I����B�{�^���ȊO�Ȃ猻�݃|�W�V�����ݒ�
	if( result == BMPLIST_NULL ){
		BmpListDirectPosGet( p_win->p_bmplist, &now_pos );
		if( p_win->now_pos != now_pos ){
			p_win->now_pos = now_pos;
			p_win->callback( p_win->p_work, p_win->now_pos );

			Snd_SePlay( ACCE_SHOP_SND_LIST_MOVE );

			AcceShop_ListWinClactDrawSet( p_win );

		}
	}else if( result != BMPLIST_CANCEL ){

		// �ŏI���ڂ�I���������߂�@�Ȃ̂�CANCEL��Ԃ�
		if( p_win->now_pos == (p_win->data_num - 1) ){
			result = BMPLIST_CANCEL;
		}
	}
	
	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ē]��
 *
 *	@param	p_win	���[�N
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinReTrans( ACCE_SHOP_LIST_WIN* p_win )
{
//	BmpListRewrite( p_win->p_bmplist );
	p_win->callback( p_win->p_work, p_win->now_pos );

	// �g�̕`��
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );

	// OAM�`��ݒ�	
	AcceShop_ListWinClactDrawSet( p_win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�E�`��OFF
 *
 *	@param	p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinDrawClean( ACCE_SHOP_LIST_WIN* p_win )
{
	CLACT_SetDrawFlag( p_win->clact[ 0 ], FALSE );
	CLACT_SetDrawFlag( p_win->clact[ 1 ], FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[���\�[�X�ǂݍ���
 *	
 *	@param	p_head	�w�b�_�[
 *	@param	p_win	
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactResLoad( CLACT_HEADER* p_head, ACCE_SHOP_LIST_WIN* p_win, u32 heapID )
{
	// ���\�[�X�ǂݍ���
	p_win->resObj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_win->resMan[ CLACT_U_CHAR_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NCGR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, heapID );	

	p_win->resObj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_win->resMan[ CLACT_U_PLTT_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_obj_NCLR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 1,  heapID );	

	p_win->resObj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell( 
			p_win->resMan[ CLACT_U_CELL_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NCER, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			CLACT_U_CELL_RES, heapID );	

	p_win->resObj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell( 
			p_win->resMan[ CLACT_U_CELLANM_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NANR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			CLACT_U_CELLANM_RES, heapID );


	CLACT_U_CharManagerSetAreaCont( p_win->resObj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerSetCleanArea( p_win->resObj[ CLACT_U_PLTT_RES ] );

	// �w�b�_�[�쐬
	CLACT_U_MakeHeader(
			p_head,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			CLACT_U_HEADER_DATA_NONE,
			CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_win->resMan[ 0 ],
			p_win->resMan[ 1 ],
			p_win->resMan[ 2 ],
			p_win->resMan[ 3 ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[���\�[�X�j��
 *
 *	@param	p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactResDelete( ACCE_SHOP_LIST_WIN* p_win )
{
	int i;
	CLACT_U_CharManagerDelete( p_win->resObj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_win->resObj[ CLACT_U_PLTT_RES ] );

	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_RESNUM; i++ ){
		CLACT_U_ResManagerDelete( p_win->resMan[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
*	@brief	�`��ݒ�
 *
 *	@param	* p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactDrawSet( ACCE_SHOP_LIST_WIN* p_win )
{
	u16 list_pos;
	
	// ���X�g�ʒu�擾
	BmpListPosGet( p_win->p_bmplist, &list_pos, NULL );
	
	if( (list_pos <= 0) ){
		CLACT_SetDrawFlag( p_win->clact[ 0 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_win->clact[ 0 ], TRUE );
	}
	if( list_pos >= (p_win->data_num - 7) ){
		CLACT_SetDrawFlag( p_win->clact[ 1 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_win->clact[ 1 ], TRUE );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	�f�[�^�E�B���h�E�ύX�@�I�u�W�F
 *
 *	@param	p_obj			�I�u�W�F
 *	@param	data_win		�f�[�^�E�B���h�E
 *	@param	cp_data			�A�N�Z�T���[�f�[�^
 *	@param	p_save			�Z�[�u�f�[�^
 *	@param	heapID			�q�[�v
 *	@param	p_bgl			BGL
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataWinChgDataInit( ACCE_SHOP_DATA_WIN_CHG* p_obj, ACCE_SHOP_DATA_WIN* data_win, const ACCE_SHOP_DATA* cp_data, MYITEM* p_save, u32 heapID, GF_BGL_INI* p_bgl )
{
	p_obj->p_bgl = p_bgl;
	p_obj->p_data_wnd = data_win;
	p_obj->cp_data = cp_data;
	p_obj->p_myitem = p_save;
	p_obj->heapID	= heapID;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�ɌĂ�ł��炤�@�f�[�^�E�B���h�E�X�V�R�[���o�b�N
 *
 *	@param	p_work
 *	@param	listnum 
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataWinChgCallBack( void* p_work, u32 listnum )
{
	ACCE_SHOP_DATA_WIN_CHG* p_obj = p_work;
	u32 have_item;
	
	// �V���b�v�f�[�^���ڐ��ȉ��Ȃ�@�f�[�^�X�V
	if( listnum < ACCE_SHOP_DATA_NUM ){
		
		have_item = MyItem_GetItemNum( p_obj->p_myitem, p_obj->cp_data[ listnum ].item_no + NUTS_START_ITEMNUM, p_obj->heapID );
		AcceShop_DataMsgSet( p_obj->p_data_wnd, 
				p_obj->cp_data[ listnum ].item_no, 
				p_obj->cp_data[ listnum ].need_num, 
				have_item );
	}else{
		// �X�N���[��������		
		GF_BGL_ScrFill( p_obj->p_bgl, FLD_MBGFRM_FONT,
				0,
				ACCE_SHOP_DATA_WINWIN_X-1, ACCE_SHOP_DATA_WINWIN_Y-1,
				ACCE_SHOP_DATA_WINWIN_SX+2, ACCE_SHOP_DATA_WINWIN_SY+2, 
				GF_BGL_SCRWRT_PALIN );
		GF_BGL_LoadScreenReq( p_obj->p_bgl, FLD_MBGFRM_FONT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E������
 *
 *	@param	p_win	�E�B���h�E���[�N
 *	@param	p_bgl	BGL
 *	@param	heapID	�q�[�v
 */
//-----------------------------------------------------------------------------
static void AcceShop_YesNoWinInit( ACCE_SHOP_YESNO_MENU* p_win, GF_BGL_INI* p_bgl, u32 heapID )
{
	static const BMPWIN_DAT BmpWinDat = {
		FLD_MBGFRM_FONT,
		ACCE_SHOP_YESNO_WIN_X,
		ACCE_SHOP_YESNO_WIN_Y,
		ACCE_SHOP_YESNO_WIN_SX,
		ACCE_SHOP_YESNO_WIN_SY,
		ACCE_SHOP_YESNO_WIN_PLTT,
		ACCE_SHOP_YESNO_WIN_CHAR
	};

	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->p_yesno = BmpYesNoSelectInit( p_bgl, &BmpWinDat, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT, heapID );
	p_win->heapID = heapID;

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E�j��
 *
 *	@param	p_win	�E�B���h�E���[�N
 */
//-----------------------------------------------------------------------------
static void AcceShop_YesNoWinDelete( ACCE_SHOP_YESNO_MENU* p_win )
{
	if( p_win->init == 0 ){
		return ;
	}
	
	// ����ɔj�������̂ŃR�����g�A�E�g
//	BmpYesNoWinDel( p_win->p_yesno, p_win->heapID );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNO�E�B���h�E���C��
 *
 *	@param	p_win	���[�N
 *
 * @retval	"BMPMENU_NULL	�I������Ă��Ȃ�"
 * @retval	"0				�͂���I��"
 * @retval	"BMPMENU_CANCEL	������or�L�����Z��"
 */
//-----------------------------------------------------------------------------
static u32 AcceShop_YesNoWinMain( ACCE_SHOP_YESNO_MENU* p_win )
{
	u32 result;
	result = BmpYesNoSelectMain( p_win->p_yesno, p_win->heapID );
	return result;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�V���b�v�̃A�N�Z�T�����t���Ɏ����Ă��邩�`�F�b�N
 *
 *	@param	cp_item		�Z�[�u�f�[�^
 *	@param	cp_data		�V���b�v�f�[�^
 *	@param	data_num	�f�[�^��
 *
 *	@retval	TRUE	�t���Ɏ����Ă���
 *	@retval	FALSE	�t���ɂ����ėǂ��Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_FullAcceCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_num )
{
	int i;

	// �S�f�[�^�A�N�Z�T����ǉ��ł��邩�`�F�b�N����
	for( i=0; i<data_num; i++ ){
		if( ImcSaveData_CheckAcceAdd( cp_item, cp_data[i].acce_no, 1 ) == TRUE ){
			return FALSE;
		}
	}
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�؂̎�����Ă��邩�`�F�b�N
 *
 *	@param	p_save		�Z�[�u
 *	@param	cp_data		�f�[�^
 *	@param	data_idx	�C���f�b�N�X
 *
 *	@retval	TRUE	����Ă���
 *	@retval	FALSE	����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_NutsOkCheck( MYITEM* p_save, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID )
{
	u32 item_num;
	
	item_num = MyItem_GetItemNum( p_save, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM, heapID );

	if( item_num >= cp_data[ data_idx ].need_num ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T�������Ă邩�`�F�b�N
 *
 *	@param	cp_item		���[�N	
 *	@param	cp_data		�f�[�^
 *	@param	data_idx	�C���f�b�N�X
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_AcceHaveOkCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	return ImcSaveData_CheckAcceAdd( cp_item, cp_data[ data_idx ].acce_no, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���ύX�@����
 *
 *	@param	p_acceitem		�A�N�Z�T���Z�[�u�f�[�^
 *	@param	p_myitem		�����A�C�e��
 *	@param	cp_data			�V���b�v�f�[�^
 *	@param	data_idx		�f�[�^�C���f�b�N�X
 */
//-----------------------------------------------------------------------------
static void AcceShop_AcceChange( IMC_ITEM_SAVEDATA* p_acceitem, MYITEM* p_myitem, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID )
{
	u32 acce_no = cp_data[ data_idx ].acce_no;
	u32 item_no = cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM;
	u32 need_num = cp_data[ data_idx ].need_num;
	BOOL result;

	ImcSaveData_AddAcceFlag( p_acceitem, acce_no, 1 );
	result = MyItem_SubItem( p_myitem, item_no, need_num, heapID );
	GF_ASSERT( result == TRUE );
}
