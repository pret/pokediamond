//==============================================================================================
/**
 * @file	ev_win.c
 * @brief	�C�x���g�E�B���h�E(BMP���j���[�ABMP���X�g)
 * @author	Satoshi Nohara
 * @date	2005.07.29
 */
//==============================================================================================
#include "common.h"
#include "gflib/msg_print.h"			//STRCODE
#include "system/msgdata.h"				//MSGMAN_TYPE_DIRECT
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/pm_str.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/wordset.h"				//WORDSET_ExpandStr
#include "system/wipe.h"				//WIPE_SYS_EndCheck
#include "system/window.h"
#include "savedata/coin.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "mapdefine.h"					//ZONE_ID_C01FS0101
#include "ev_win.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_ev_win.h"			//msg_ev_win_016
#include "msgdata/msg_shop.h"


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
static void EvWin_Init( FIELDSYS_WORK* fsys, EV_WIN_WORK* wk, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );

//BMP���j���[
EV_WIN_WORK * CmdEvBmpMenu_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );
void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  );
void CmdEvBmpMenu_Start( EV_WIN_WORK* wk );

//BMP���j���[�c��
void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max );
static void BmpMenuHV_h_default_set( EV_WIN_WORK* wk, u8 x_max, u8 y_max );

static void BmpMenu_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 param  );
static u32 BmpMenu_length_get( EV_WIN_WORK* wk );
static void BmpMenu_h_default_set(EV_WIN_WORK* wk);
static void EvBmpMenu_MainTCB( TCB_PTR tcb, void* wk );


//BMP���X�g
EV_WIN_WORK * CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman );
void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );
void CmdEvBmpList_Start( EV_WIN_WORK* wk );

static void BmpList_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  );
static u32 BmpList_length_get( EV_WIN_WORK* wk );
static void BmpList_h_default_set(EV_WIN_WORK* wk);
static void	BmpList_CallBack( BMPLIST_WORK* lw, u32 param, u8 y );
static void EvBmpList_MainTCB( TCB_PTR tcb, void* wk );
static void EvBmpList_Del( EV_WIN_WORK* wk );
static void talk_msg_print( EV_WIN_WORK* wk, u16 talk_msg_id, u32 wait );
static void talk_msg_update( EV_WIN_WORK* wk );


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define EV_WIN_FONT		(FONT_SYSTEM)			//�t�H���g�w��
//#define EV_WIN_FONT	(FONT_TALK)				//�t�H���g�w��

//#define EVWIN_MSG_BUF_SIZE	(32*2)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define EVWIN_MSG_BUF_SIZE		(40*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

//BMP���j���[
#define EV_WIN_MENU_MAX			(28)			//���j���[���ڂ̍ő吔

//BMP���X�g
#define EV_WIN_LIST_MAX			(28)			//���X�g���ڂ̍ő吔

#define	EV_WIN_MSG_MAX			(28)			//MSG�o�b�t�@�̍ő吔

//BMP���X�g�w�b�_�[��`
#define EV_LIST_LINE			(8)				//�\���ő區�ڐ�
#define EV_LIST_RABEL_X			(1)				//���x���\���w���W
#define EV_LIST_DATA_X			(12)			//���ڕ\���w���W
#define EV_LIST_CURSOR_X		(2)				//�J�[�\���\���w���W
#define EV_LIST_LINE_Y			(1)				//�\���x���W

//�J�[�\����
#define EV_WIN_CURSOR_WIDTH		(12)			//�J�[�\����

#define EV_WIN_DEFAULT_WAIT		(3)				//�L�[���삪�����ɓ���Ȃ��悤�Ɋ�{�E�F�C�g


// �����������E�B���h�E��`
#define	EVWIN_GOLD_SX		( 10 )								// �������E�B���h�EX�T�C�Y
#define	EVWIN_GOLD_SY		( 4 )								// �������E�B���h�EY�T�C�Y
#define	EVWIN_GOLD_FRM		( SHOP_FRM_WINDOW )					// �������E�B���h�EBG�t���[��
#define	EVWIN_GOLD_PAL		( FLD_SYSFONT_PAL )					// �������E�B���h�E�p���b�g
#define	EVWIN_GOLD_CGX		( 1 )								// �������E�B���h�E�L�����g�p�ʒu
#define	EVWIN_GOLD_CGX_SIZ	( EVWIN_GOLD_SX * EVWIN_GOLD_SY )	// �������E�B���h�E�L�����T�C�Y

#define	GOLD_BUFLEN			( 16 )					// ������������ ( (6��+�~+EOM)*2 )
#define	EVWIN_GOLD_SX_DOT	( EVWIN_GOLD_SX * 8 )	// �������E�B���h�EX�T�C�Y�i�h�b�g�j
#define	EVWIN_GOLD_VAL_PY	( 16 )					// �������\��Y���W

// �R�C���E�B���h�E��`
#define	EVWIN_COIN_SX		( 10 )									// �R�C���E�B���h�EX�T�C�Y
#define	EVWIN_COIN_SY		( 2 )									// �R�C���E�B���h�EY�T�C�Y
#define	EVWIN_COIN_FRM		( SHOP_FRM_WINDOW )						// �R�C���E�B���h�EBG�t���[��
#define	EVWIN_COIN_PAL		( FLD_SYSFONT_PAL )						// �R�C���E�B���h�E�p���b�g
#define	EVWIN_COIN_CGX		( EVWIN_GOLD_CGX+EVWIN_GOLD_CGX_SIZ )	// �R�C���E�B���h�E�L�����g�p�ʒu
#define	EVWIN_COIN_CGX_SIZ	( EVWIN_COIN_SX * EVWIN_COIN_SY )		// �R�C���E�B���h�E�L�����T�C�Y

#define	COIN_BUFLEN			( 16 )					// �R�C�������� ( (4��+�~+EOM)*2 )
#define	EVWIN_COIN_SX_DOT	( EVWIN_COIN_SX * 8 )	// �R�C���E�B���h�EX�T�C�Y�i�h�b�g�j

#define BP_BUFLEN			((4+2+1)*2)	//�o�g���|�C���g������((4��+BP+EOM)*2)

// ����������g���ĉ������I�I
#define	EVWIN_FREE_CGX		( EVWIN_COIN_CGX+EVWIN_COIN_CGX_SIZ )	// �t���[�̃L�����ʒu



//==============================================================================================
//
//	�\����
//
//==============================================================================================
struct _EV_WIN_WORK{
	FIELDSYS_WORK * fsys;						//FIELDSYS_WORK�̃|�C���^
	TCB_PTR	tcb;

 	GF_BGL_BMPWIN bmpwin;						//BMP�E�B���h�E�f�[�^
 	GF_BGL_BMPWIN* talk_bmpwin;					//BMP��b�E�B���h�E�f�[�^
	
	STRBUF* msg_buf[EV_WIN_MSG_MAX];			//���b�Z�[�W�f�[�^�̃|�C���^
	MSGDATA_MANAGER* msgman;					//���b�Z�[�W�}�l�[�W���[
	WORDSET* wordset;							//�P��Z�b�g

	u8  wait;									//�E�F�C�g
	u8  menu_id;								//BMP���j���[ID
	u8  cursor_pos;								//�J�[�\���ʒu
	u8  cancel:1;								//�L�����Z��
	u8  msgman_del_flag:1;						//���b�Z�[�W�}�l�[�W���[�폜�t���O
	u8  dmy:6;									//

	u8  x;										//�E�B���h�E�ʒuX
	u8  y;										//�E�B���h�E�ʒuY
	u8  dmyy;									//���j���[�i���o�[
	u8  list_no;								//���j���[���ڂ̉��Ԗڂ�

	u16* pMsg;									//���b�Z�[�W�f�[�^
	u16* work;									//���ʎ擾���[�N
 
	//BMP���j���[(bmp_menu.h)
	BMPMENU_HEADER MenuH;						//BMP���j���[�w�b�_�[
	BMPMENU_WORK * mw;							//BMP���j���[���[�N
	BMPMENU_DATA Data[EV_WIN_MENU_MAX];			//BMP���j���[�f�[�^

	//BMP���X�g
	BMPLIST_HEADER ListH;						//BMP���X�g�w�b�_�[
	BMPLIST_WORK* lw;							//BMP���X�g�f�[�^
	u16 list_bak;								//���X�g�ʒu�o�b�N�A�b�v
	u16 cursor_bak;								//�J�[�\���ʒu�o�b�N�A�b�v
	BMPLIST_DATA list_Data[EV_WIN_LIST_MAX];	//���X�g�f�[�^
	u16 talk_msg_id[EV_WIN_LIST_MAX];			//���X�g�f�[�^�ɑ΂ɂȂ��b���b�Z�[�WID

	u16 pos_bak;
};


//==============================================================================================
//
//	�֐�
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�C�x���g�E�B���h�E�@���[�N������
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvWin_Init( FIELDSYS_WORK* fsys, EV_WIN_WORK* wk, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	int i;

	if( msgman == NULL ){
		//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
		wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD);
		wk->msgman_del_flag = 1;
	}else{
		wk->msgman = msgman;	//���p��
		wk->msgman_del_flag = 0;
	}

	//wk->wordset = WORDSET_Create( HEAPID_FIELD );
	wk->wordset		= wordset;		//�X�N���v�g�������p��

	wk->fsys		= fsys;
	wk->work		= work;
	wk->cancel		= cancel;
	wk->cursor_pos	= cursor;
	wk->x			= x;
	wk->y			= y;
	wk->list_no		= 0;
	wk->talk_bmpwin	= talk_bmpwin;
	wk->wait		= EV_WIN_DEFAULT_WAIT;
	wk->pos_bak		= cursor;

	for( i=0; i < EV_WIN_MENU_MAX ;i++ ){
		wk->Data[i].str			= NULL;
		wk->Data[i].param		= 0;
	}

	for( i=0; i < EV_WIN_LIST_MAX ;i++ ){
		wk->list_Data[i].str	= NULL;
		wk->list_Data[i].param	= 0;
		wk->talk_msg_id[i] = EV_WIN_TALK_MSG_NONE;
	}

	//MSGMAN_Create�̌�ɏ���
	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		wk->msg_buf[i] = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	}

	//�I�������l���擾���郏�[�N��������
	*wk->work = EV_WIN_NOTHING;

	return;
}


//==============================================================================================
//
//	BMP���j���[�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@������
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	"EV_WIN_WORK�^�̃A�h���X�ANULL�͎��s"
 */
//--------------------------------------------------------------
EV_WIN_WORK * CmdEvBmpMenu_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	EV_WIN_WORK* wk;
	int i;

	wk = sys_AllocMemory( HEAPID_FIELD, sizeof(EV_WIN_WORK) );
	if( wk == NULL ){
		OS_Printf( "ev_win.c Alloc ERROR!" );
		return NULL;
	}
	memset( wk, 0, sizeof(EV_WIN_WORK) );

	//���[�N������	
	EvWin_Init( fsys, wk, x, y, cursor, cancel, work, wordset, talk_bmpwin, msgman );

	return wk;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPMENU�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenu_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	BmpMenu_list_make( wk, msg_id, param  );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPMENU�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenu_Start( EV_WIN_WORK* wk )
{
	u32 len;

	//(�ő啶�����{�J�[�\��) * �t�H���g�T�C�Y
	//len = (BmpMenu_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpMenu_length_get(wk);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, wk->list_no*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );

	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);


	//���j���[�w�b�_�[�����ݒ�
	BmpMenu_h_default_set(wk);
	wk->mw = BmpMenuAdd( &wk->MenuH, wk->cursor_pos, HEAPID_FIELD );

	//TCB�ǉ�
	wk->tcb	= TCB_Add( EvBmpMenu_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[	���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPMENU�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenu_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < EV_WIN_MENU_MAX, "���j���[���ڐ��I�[�o�[�I" );

#if 1
	{
		//�W�J����
		
		STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );	//�R�s�[�p�o�b�t�@

		MSGMAN_GetString( wk->msgman, msg_id, tmp_buf2 );
		WORDSET_ExpandStr( wk->wordset, wk->msg_buf[wk->list_no], tmp_buf2 );	//�W�J
		wk->Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];

		STRBUF_Delete( tmp_buf2 );
	}
#else
	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
#endif

	wk->Data[ wk->list_no ].param = param;
	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[	���ڂ̒�����ő啶�������擾
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static u32 BmpMenu_length_get( EV_WIN_WORK* wk )
{
	int i;
	u32 ret,tmp_ret;

	ret		= 0;
	tmp_ret = 0;

	for( i=0; i < wk->list_no ;i++ ){
		if( wk->Data[i].str == NULL ){
			break;
		}

		//ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, wk->msg_buf[i], 0 );
		ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, (STRBUF*)wk->Data[i].str, 0 );

		if( tmp_ret < ret ){
			tmp_ret = ret;
		}
	}

	return tmp_ret + EV_WIN_CURSOR_WIDTH;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j��	�w�b�_�[�����ݒ�
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenu_h_default_set(EV_WIN_WORK* wk)
{
	wk->MenuH.menu		= wk->Data;

	wk->MenuH.win		= &wk->bmpwin;

	wk->MenuH.font		= EV_WIN_FONT;
	wk->MenuH.x_max		= 1;
	wk->MenuH.y_max		= wk->list_no;
	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;

	//���j���[���ڂ�4��ވȏゾ�������̓J�[�\���̃��[�v�L��ɂ���
	if( wk->list_no >= 4 ){
		wk->MenuH.loop_f	= 1;			//�L
	}else{
		wk->MenuH.loop_f	= 0;			//��
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@���C��
 *
 * @param	tcb			TCB_PTR
 * @param	wk			���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvBmpMenu_MainTCB( TCB_PTR tcb, void* wk )
{
	u32 ret;
	EV_WIN_WORK *swk;
	swk = (EV_WIN_WORK *)wk;

	//�E�F�C�g
	if( swk->wait != 0 ){
		swk->wait--;
		return;
	}

	//���C�v���͏������Ȃ�
	if( WIPE_SYS_EndCheck() == FALSE ){
		return;
	}

	ret = BmpMenuMain( swk->mw );
	switch( ret ){
	case BMPMENU_NULL:
		break;
	case BMPMENU_CANCEL:
		if( swk->cancel == TRUE ){			//TRUE = B�L�����Z���L��
			*swk->work = EV_WIN_B_CANCEL;	//�I�������l�����[�N�ɑ��
			EvBmpMenu_Del(wk);
		}
		break;
	default:
		*swk->work = ret;					//�I�������l�����[�N�ɑ��
		EvBmpMenu_Del(wk);
		break;
	};

	return;
};

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�@�I��
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 *
 * SEQ_SE_DP_SELECT��炵�Ă���I
 */
//--------------------------------------------------------------
void EvBmpMenu_Del( EV_WIN_WORK* wk )
{
	int i;

	Snd_SePlay(SEQ_SE_DP_SELECT);	//���ӁI

	BmpMenuExit( wk->mw, NULL );
	BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( wk->MenuH.win );

	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	if( wk->msgman_del_flag == 1 ){
		//WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
	}

	TCB_Delete( wk->tcb );
	sys_FreeMemoryEz( wk );
	return;
}


//==============================================================================================
//
//	BMP���X�g�֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@������
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	"EV_WIN_WORK�^�̃A�h���X�ANULL�͎��s"
 */
//--------------------------------------------------------------
EV_WIN_WORK * CmdEvBmpList_Init( FIELDSYS_WORK* fsys, u8 x, u8 y, u8 cursor, u8 cancel, u16* work, WORDSET* wordset, GF_BGL_BMPWIN* talk_bmpwin, MSGDATA_MANAGER* msgman )
{
	return CmdEvBmpMenu_Init( fsys, x, y, cursor, cancel, work, wordset, talk_bmpwin, msgman  );
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	talk_msg_id	��b���b�Z�[�WID
 * @param	param		BMPLIST�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpList_MakeList( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  )
{
	BmpList_list_make( wk, msg_id, talk_msg_id, param  );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpList_Start( EV_WIN_WORK* wk )
{
	u32 len;

	//(�ő啶�����{�J�[�\��) * �t�H���g�T�C�Y
	//len = (BmpList_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpList_length_get(wk);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	//�\���ő區�ڐ��`�F�b�N
	if( wk->list_no > EV_LIST_LINE ){
		GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, EV_LIST_LINE*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );
	}else{
		GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
									len, wk->list_no*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );
	}

	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//���X�g�w�b�_�[�����ݒ�
	BmpList_h_default_set(wk);

	wk->lw = BmpListSet( (const BMPLIST_HEADER*)&wk->ListH, 0, wk->cursor_pos, HEAPID_FIELD );

	//��b�E�B���h�E�X�V
	talk_msg_update( wk );

	//TCB�ǉ�
	wk->tcb	= TCB_Add( EvBmpList_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g	���X�g�쐬
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	talk_msg_id	��b���b�Z�[�WID
 * @param	param		BMPLIST�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_list_make( EV_WIN_WORK* wk, u32 msg_id, u32 talk_msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < EV_WIN_LIST_MAX, "���X�g���ڐ��I�[�o�[�I" );

#if 1
	{
		//�W�J����
		
		STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );	//�R�s�[�p�o�b�t�@

		MSGMAN_GetString( wk->msgman, msg_id, tmp_buf2 );
		WORDSET_ExpandStr( wk->wordset, wk->msg_buf[wk->list_no], tmp_buf2 );	//�W�J
		wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];

		STRBUF_Delete( tmp_buf2 );
	}
#else

	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
	//*st = (const void *)&wk->msg_buf[wk->list_no][0];
#endif
	if( param == EV_WIN_LIST_LABEL ){
		wk->list_Data[ wk->list_no ].param = BMPLIST_RABEL;
		//*pa = BMPLIST_RABEL;
	}else{
		wk->list_Data[ wk->list_no ].param = param;
		//*pa = param;
	}

	wk->talk_msg_id[ wk->list_no ] = talk_msg_id;
	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g	���ڂ̒�����ő啶�������擾
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static u32 BmpList_length_get( EV_WIN_WORK* wk )
{
	int i;
	u32 ret,tmp_ret;

	ret		= 0;
	tmp_ret = 0;

	for( i=0; i < wk->list_no ;i++ ){
		if( wk->list_Data[i].str == NULL ){
			break;
		}

		//ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, wk->msg_buf[i], 0 );
		ret = FontProc_GetPrintStrWidth( EV_WIN_FONT, (STRBUF*)wk->list_Data[i].str, 0 );
		
		if( tmp_ret < ret ){
			tmp_ret = ret;
		}
	}

	return tmp_ret + EV_WIN_CURSOR_WIDTH;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g	�w�b�_�[�����ݒ�
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_h_default_set(EV_WIN_WORK* wk)
{
	wk->ListH.list		= wk->list_Data;
	wk->ListH.call_back = NULL;
	wk->ListH.icon		= BmpList_CallBack;
	wk->ListH.win		= &wk->bmpwin;

	wk->ListH.count		= wk->list_no;
	wk->ListH.line		= EV_LIST_LINE;

	wk->ListH.rabel_x	= EV_LIST_RABEL_X;
	wk->ListH.data_x	= EV_LIST_DATA_X;
	wk->ListH.cursor_x	= EV_LIST_CURSOR_X;
	wk->ListH.line_y	= EV_LIST_LINE_Y;

	wk->ListH.f_col		= FBMP_COL_BLACK;
	wk->ListH.b_col		= FBMP_COL_WHITE;		
	wk->ListH.s_col		= FBMP_COL_BLK_SDW;

	wk->ListH.msg_spc	= 0;
	wk->ListH.line_spc	= 16;
	wk->ListH.page_skip	= BMPLIST_LRKEY_SKIP;
	wk->ListH.font		= EV_WIN_FONT;
	wk->ListH.c_disp_f	= 0;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���X�g�V�X�e������̃R�[���o�b�N����s�\������
 *
 * @param	lw			BMPLIST_WORK�^�̃|�C���^
 * @param	param		�I�������^�[���p�����[�^
 * @param	y			
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void	BmpList_CallBack(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if( param == BMPLIST_RABEL ){
		BmpListTmpColorChange( lw, FBMP_COL_RED, FBMP_COL_WHITE, FBMP_COL_RED_SDW );
	}else{
		BmpListTmpColorChange( lw, FBMP_COL_BLACK, FBMP_COL_WHITE, FBMP_COL_BLK_SDW );
	}
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@���X�g���C��
 *
 * @param	tcb			TCB_PTR
 * @param	wk			���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvBmpList_MainTCB( TCB_PTR tcb, void* wk )
{
	u16 tmp_pos_bak;
	u32	ret;
	EV_WIN_WORK* swk;
	swk = (EV_WIN_WORK*)wk;

	//�E�F�C�g
	if( swk->wait != 0 ){
		swk->wait--;
		return;
	}

	//���C�v���͏������Ȃ�
	if( WIPE_SYS_EndCheck() == FALSE ){
		return;
	}

	ret = BmpListMain( swk->lw );

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = swk->pos_bak;		//�ޔ�
	BmpListDirectPosGet( swk->lw, &swk->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != swk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	//��b�E�B���h�E�̃��b�Z�[�W�X�V
	if( (sys.repeat & PAD_KEY_UP) || (sys.repeat & PAD_KEY_DOWN) ||
		(sys.repeat & PAD_KEY_LEFT) || (sys.repeat & PAD_KEY_RIGHT) ){
		talk_msg_update( swk );
	}

	switch( ret ){
	case BMPLIST_NULL:
		break;
	case BMPLIST_CANCEL:
		if( swk->cancel == TRUE ){			//TRUE = B�L�����Z���L��
			Snd_SePlay( SEQ_SE_DP_SELECT );
			*swk->work = EV_WIN_B_CANCEL;	//�I�������l�����[�N�ɑ��
			EvBmpList_Del(wk);
		}
		break;
	default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
		*swk->work = ret;					//�I�������l�����[�N�ɑ��
		EvBmpList_Del(wk);
		break;
	};

	return;
};

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@���X�g�I��
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 *
 * SEQ_SE_DP_SELECT��炵�Ă���I
 */
//--------------------------------------------------------------
static void EvBmpList_Del( EV_WIN_WORK* wk )
{
	int i;

	Snd_SePlay(SEQ_SE_DP_SELECT);	//���ӁI

	BmpListExit( wk->lw, NULL, NULL );
	BmpMenuWinClear( wk->ListH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->bmpwin );

	for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	if( wk->msgman_del_flag == 1 ){
		//WORDSET_Delete( wk->wordset );
		MSGMAN_Delete( wk->msgman );
	}

	TCB_Delete( wk->tcb );
	sys_FreeMemoryEz( wk );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	��b�E�B���h�E�Ƀ��b�Z�[�W���ꊇ�\��
 *
 * @param	wk			EV_WIN_WORK�^�̃A�h���X
 * @param	talk_msg_id	��b���b�Z�[�WID
 * @param	wait		���b�Z�[�W�E�F�C�g
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_print( EV_WIN_WORK* wk, u16 talk_msg_id, u32 wait )
{
	STRBUF* tmp_buf = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );

	//���b�Z�[�W�N���A
	GF_BGL_BmpWinDataFill( wk->talk_bmpwin, (FBMP_COL_WHITE) );

	MSGMAN_GetString( wk->msgman, talk_msg_id, tmp_buf );

	//�o�^���ꂽ�P����g���ĕ�����W�J����
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( wk->talk_bmpwin, FONT_TALK, tmp_buf2, 0, 0, wait, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	��b�E�B���h�E�Ƀ��b�Z�[�W���ꊇ�\��
 *
 * @param	wk			EV_WIN_WORK�^�̃A�h���X
 * @param	talk_msg_id	��b���b�Z�[�WID
 * @param	wait		���b�Z�[�W�E�F�C�g
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_update( EV_WIN_WORK* wk )
{
	BmpListDirectPosGet( wk->lw, &wk->cursor_bak );		//�J�[�\�����W�擾
	if( wk->talk_msg_id[wk->cursor_bak] != EV_WIN_TALK_MSG_NONE ){
		talk_msg_print( wk, wk->talk_msg_id[wk->cursor_bak], MSG_ALLPUT );
	}
	return;
}


//==============================================================================================
//
//	�G���x�[�^�t���A�֘A
//
//==============================================================================================
#define FLOOR_WIN_SIZE_X			(8)		//�t���A�E�B���h�E�̂w�T�C�Y
#define FLOOR_WIN_SIZE_Y			(4)		//�t���A�E�B���h�E�̂x�T�C�Y
#define FLOOR_TITLE_X				(0)		//�u���񂴂��́@�t���A�v�̕\���ʒu
#define FLOOR_TITLE_Y				(0)
#define FLOOR_TITLE_X2				(8*4)	//�u�������v�̕\���ʒu
#define FLOOR_TITLE_Y2				(16)
#define EV_WIN_SIZE_X				(16)	//�����ɕ\�������I���E�B���h�E�̂w�T�C�Y
#define EV_WIN_SIZE_Y				(10)	//�����ɕ\�������I���E�B���h�E�̂x�T�C�Y

static void ElevatorFloorMainTCB( TCB_PTR tcb, void* wk );
void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset);
static void ev_win_msg_print( EV_WIN_WORK* wk, u16 msg_id, u8 x, u8 y );


//--------------------------------------------------------------
/**
 * @brief	�t���A�E�B���h�E�\��
 *
 * @param	fsys		FIELDSYS_WORK�^�̃|�C���^
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	work		���ʂ������郏�[�N�̃|�C���^
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void ElevatorFloorWrite(FIELDSYS_WORK* fsys, u8 x, u8 y, u16* work, WORDSET* wordset)
{
	u32 len;
	EV_WIN_WORK* wk;

	//BMP���j���[������(ev_win.gmm�Œ�)
	wk = CmdEvBmpMenu_Init( fsys, x, y, 0, 0, work, wordset, NULL, NULL );

	//(�ő啶����) * �t�H���g�T�C�Y
	len = (FLOOR_WIN_SIZE_X) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	//�����ɕ\������C�x���g�E�B���h�E�̃I�t�Z�b�g������I
	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
						len, FLOOR_WIN_SIZE_Y, FLD_SYSFONT_PAL, EVWIN_FREE_CGX + (EV_WIN_SIZE_X*EV_WIN_SIZE_Y) );

	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet(wk->fsys->bgl,FLD_MBGFRM_FONT,MENU_WIN_CGX_NUM,MENU_WIN_PAL,0,HEAPID_FIELD);

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//�w��͈͂�h��Ԃ�
	GF_BGL_BmpWinFill( &wk->bmpwin, FBMP_COL_WHITE, 0, 0, (len*8), (FLOOR_WIN_SIZE_Y*8) );
	
	ev_win_msg_print( wk, msg_ev_win_016, FLOOR_TITLE_X, FLOOR_TITLE_Y );	//�u���񂴂��́@�t���A�v
	ev_win_msg_print( wk, msg_ev_win_017, FLOOR_TITLE_X2, FLOOR_TITLE_Y2 );	//�u�������v

	wk->MenuH.win = &wk->bmpwin;
	GF_BGL_BmpWinOn( &wk->bmpwin );
	
	//TCB�ǉ�
	wk->tcb	= TCB_Add( ElevatorFloorMainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�\��
 *
 * @param	wk			EV_WIN_WORK�^�̃A�h���X
 * @param	msg_id		���b�Z�[�WID
 * @param	x			�\���w���W
 * @param	y			�\���x���W
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ev_win_msg_print( EV_WIN_WORK* wk, u16 msg_id, u8 x, u8 y )
{
	STRBUF* tmp_buf = STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );
	GF_STR_PrintSimple( &wk->bmpwin, EV_WIN_FONT, tmp_buf2, x, y, MSG_NO_PUT, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�t���A�E�B���h�E�\�� ���C��
 *
 * @param	tcb			TCB_PTR
 * @param	wk			���[�N�̃A�h���X
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ElevatorFloorMainTCB( TCB_PTR tcb, void* wk )
{
	int i;
	EV_WIN_WORK *swk;
	swk = (EV_WIN_WORK *)wk;

	//�ʏ�AWK_ELEVATOR_FLOOR�̒l��"FLOOR_NOTHING"�ɂȂ�܂ŊĎ����Ă��鏈��
	if( *swk->work == FLOOR_NOTHING ){
		BmpMenuWinClear( swk->MenuH.win, WINDOW_TRANS_ON );
		GF_BGL_BmpWinDel( swk->MenuH.win );

		for( i=0; i < EV_WIN_MSG_MAX ;i++ ){
			STRBUF_Delete( swk->msg_buf[i] );
		}

		if( swk->msgman_del_flag == 1 ){
			//WORDSET_Delete( swk->wordset );
			MSGMAN_Delete( swk->msgman );
		}

		TCB_Delete( swk->tcb );
		sys_FreeMemoryEz( swk );
	}

	return;
};

//--------------------------------------------------------------
/**
 * ����ڑ��悩��A���݂̃t���A�i���o�[���擾
 *
 * @param   zone_id		�]�[��ID
 *
 * @retval  "�t���A�i���o�["
 *
 * �G���x�[�^�}�b�v����������Ή����Ă����I
 */
//--------------------------------------------------------------
u16 ElevatorNowFloorGet( int zone_id )
{
	u16 floor;

	switch( zone_id ){

	//-------------------------------
	case ZONE_ID_C05R0101:
		floor = FLOOR_C05R0103_1F;
		break;

	case ZONE_ID_C05R0102:
		floor = FLOOR_C05R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_C08R0801:
		floor = FLOOR_C08R0802_2F;
		break;

	case ZONE_ID_C08:
		floor = FLOOR_C08R0802_1F;
		break;

	//-------------------------------
	case ZONE_ID_C05R0801:
		floor = FLOOR_C05R0103_1F;
		break;

	case ZONE_ID_C05R0802:
		floor = FLOOR_C05R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_T07R0101:
		floor = FLOOR_T07R0103_1F;
		break;

	case ZONE_ID_T07R0102:
		floor = FLOOR_T07R0103_2F;
		break;

	//-------------------------------
	case ZONE_ID_C07R0201:
		floor = FLOOR_C07R0206_1F;
		break;

	case ZONE_ID_C07R0202:
		floor = FLOOR_C07R0206_2F;
		break;

	case ZONE_ID_C07R0203:
		floor = FLOOR_C07R0206_3F;
		break;

	case ZONE_ID_C07R0204:
		floor = FLOOR_C07R0206_4F;
		break;

	case ZONE_ID_C07R0205:
		floor = FLOOR_C07R0206_5F;
		break;

	//-------------------------------
	case ZONE_ID_C01R0201:
		floor = FLOOR_C01R0208_1F;
		break;

	case ZONE_ID_C01R0202:
		floor = FLOOR_C01R0208_2F;
		break;

	case ZONE_ID_C01R0203:
		floor = FLOOR_C01R0208_3F;
		break;

	case ZONE_ID_C01R0204:
		floor = FLOOR_C01R0208_4F;
		break;

	//�ǉ�����
	//case

	default:
		floor = FLOOR_C05R0103_1F;
	};

	return floor;
}


//==============================================================================================
//
//	BMP���j���[�c���֘A
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�c���@�J�n
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	x_max		���������ڍő吔(�K��1�ȏ�)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void CmdEvBmpMenuHV_Start( EV_WIN_WORK* wk, u8 x_max )
{
	u32 len;
	u8 y_max;

	//(�ő啶�����{�J�[�\��) * �t�H���g�T�C�Y
	//len = (BmpMenu_length_get(wk)+1) * FontHeaderGet(EV_WIN_FONT, FONT_HEADER_SIZE_X);
	len = BmpMenu_length_get(wk);
	//OS_Printf( "len = %d\n", len );

	if( (len % 8) == 0 ){
		len = (len / 8);
	}else{
		len = (len / 8)+1;
	}

	y_max = (wk->list_no / x_max);			//Y�T�C�Y
	if( (wk->list_no % x_max) != 0 ){		//�]�肪��������␳
		y_max++;
	}

	//OS_Printf( "len = %d\n", len );
	//OS_Printf( "x_max = %d\n", x_max );
	//OS_Printf( "len*x_max = %d\n", (len*x_max) );

	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, wk->x, wk->y, 
								(len * x_max), y_max*2, FLD_SYSFONT_PAL, EVWIN_FREE_CGX );

	//���ӁI
	//�ő啶�����ŁA�������̕�����`�悵�Ă���̂ŁA
	//�u���߂��������@�������@�@�@�@�v�݂����Ȃ�
	//
	//�u���߂��������@�������@�@�@�@�v
	//�u�͂��@�@�@�@�@�@�@�@�@�@�@�@�@�v�͏o���Ȃ��̂ŁA
	//�_�~�[�̋󔒕���������K�v������I
	
	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL);

	//���j���[�w�b�_�[�����ݒ�
	BmpMenuHV_h_default_set( wk, x_max, y_max );
	wk->mw = BmpMenuAdd( &wk->MenuH, wk->cursor_pos, HEAPID_FIELD );

	//TCB�ǉ�
	wk->tcb	= TCB_Add( EvBmpMenu_MainTCB, wk, 0 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���j���[�c��	�w�b�_�[�����ݒ�
 *
 * @param	wk			EV_WIN_WORK�^�̃|�C���^
 * @param	x_max		���������ڍő吔(�K��1�ȏ�)
 * @param	y_max		�c�������ڍő吔(�K��1�ȏ�)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpMenuHV_h_default_set( EV_WIN_WORK* wk, u8 x_max, u8 y_max )
{
	wk->MenuH.menu		= wk->Data;

	wk->MenuH.win		= &wk->bmpwin;

	wk->MenuH.font		= EV_WIN_FONT;
	wk->MenuH.x_max		= x_max;
	wk->MenuH.y_max		= y_max;

	wk->MenuH.line_spc	= 0;
	wk->MenuH.c_disp_f	= 0;

#if 0
	//���j���[���ڂ�4��ވȏゾ�������̓J�[�\���̃��[�v�L��ɂ���
	if( wk->list_no >= 4 ){
		wk->MenuH.loop_f	= 1;			//�L
	}else{
		wk->MenuH.loop_f	= 0;			//��
	}
#endif

	return;
}




//==============================================================================================
//
//	�������E�B���h�E
//	�����R�C���E�B���h�E
//
//==============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * �������E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_GoldWinDel�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_GoldWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_GOLD_SX, EVWIN_GOLD_SY, EVWIN_GOLD_PAL, EVWIN_GOLD_CGX );

	// ���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// ���j���[�E�B���h�E��`��
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// �w��͈͂�h��Ԃ�
	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	{	// �u�����������v
		MSGDATA_MANAGER * man;
		STRBUF * str;

		man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_shop_dat, HEAPID_FIELD );
		str = MSGMAN_AllocString( man, mes_shop_05_01 );
		GF_STR_PrintSimple( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, NULL );
		MSGMAN_Delete( man );
		STRBUF_Delete( str );
	}
	EvWin_GoldWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * �������E�B���h�E�폜
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_GoldWinDel( GF_BGL_BMPWIN * win )
{
	BmpMenuWinClear( win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinFree( win, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * �������`��
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_GoldWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u32	gold;
	u32	px;

	GF_BGL_BmpWinFill(
		win, FBMP_COL_WHITE, 0, EVWIN_GOLD_VAL_PY,
		EVWIN_GOLD_SX*8, EVWIN_GOLD_SY*8-EVWIN_GOLD_VAL_PY );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_shop_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( GOLD_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, mes_shop_05_02 );
	gold = MyStatus_GetGold( SaveData_GetMyStatus(fsys->savedata) );

	WORDSET_RegisterNumber( wset, 0, gold, 6, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_GOLD_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, EVWIN_GOLD_VAL_PY, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}


//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_CoinWinDel�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_CoinWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_COIN_SX, EVWIN_COIN_SY, EVWIN_COIN_PAL, EVWIN_COIN_CGX );

	// ���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// ���j���[�E�B���h�E��`��
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// �w��͈͂�h��Ԃ�
//	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	EvWin_CoinWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�폜
 *
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_CoinWinDel( GF_BGL_BMPWIN * win )
{
	BmpMenuWinClear( win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinFree( win, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���`��
 *
 * @param	fsys
 * @param	wk
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void EvWin_CoinWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u32	coin;
	u32	px;

	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( COIN_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, msg_ev_win_168 );
	coin = COIN_GetValue( SaveData_GetMyCoin(fsys->savedata) );

	WORDSET_RegisterNumber( wset, 0, coin, 5, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_COIN_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�E�B���h�E�\��
 *
 * @param	fsys
 * @param	wk
 * @param	x		�\��X���W
 * @param	y		�\��Y���W
 *
 * @return	�m�ۂ���BMP�E�B���h�E
 *
 *	EvWin_CoinWinDel(���L�Ŏg����)�ō폜���邱�ƁI
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * EvWin_BtlPointWinPut( FIELDSYS_WORK * fsys, u8 x, u8 y )
{
	GF_BGL_BMPWIN * win = GF_BGL_BmpWinAllocGet( HEAPID_FIELD, 1 );

	GF_BGL_BmpWinAdd(
		fsys->bgl, win, FLD_MBGFRM_FONT, x, y,
		EVWIN_COIN_SX, EVWIN_COIN_SY, EVWIN_COIN_PAL, EVWIN_COIN_CGX );

	// ���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
	MenuWinGraphicSet( fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );
	// ���j���[�E�B���h�E��`��
	BmpMenuWinWrite( win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	// �w��͈͂�h��Ԃ�
//	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	EvWin_BtlPointWrite( fsys, win );

	return win;
}

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�`��
 *
 * @param	fsys
 * @param	wk
 */
//--------------------------------------------------------------------------------------------
void EvWin_BtlPointWrite( FIELDSYS_WORK * fsys, GF_BGL_BMPWIN * win )
{
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * exp;
	STRBUF * str;
	u16	bp;
	u32	px;

	GF_BGL_BmpWinDataFill( win, FBMP_COL_WHITE );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_ev_win_dat, HEAPID_FIELD );
	wset = WORDSET_Create( HEAPID_FIELD );
	exp  = STRBUF_Create( COIN_BUFLEN, HEAPID_FIELD );
	str  = MSGMAN_AllocString( man, msg_bpgift_00 );
	bp	 = TowerScoreData_SetBattlePoint(
				SaveData_GetTowerScoreData(fsys->savedata),0,BTWR_DATA_get);

	WORDSET_RegisterNumber( wset, 0, bp, 5, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wset, exp, str );
	px = EVWIN_COIN_SX_DOT - FontProc_GetPrintStrWidth( FONT_SYSTEM, exp, 0 );
	GF_STR_PrintSimple( win, FONT_SYSTEM, exp, px, 0, MSG_NO_PUT, NULL );

	STRBUF_Delete( str );
	STRBUF_Delete( exp );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( win );
}
