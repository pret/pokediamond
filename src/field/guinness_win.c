//==============================================================================================
/**
 * @file	guinness_win.c
 * @brief	�M�l�X�E�B���h�E
 * @author	Satoshi Nohara
 * @date	2006.03.01
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
#include "system\wordset.h"				//WORDSET_ExpandStr
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "guinness_win.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat

#include "system/window.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_ev_win.h"			//msg_ev_win_016


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================


//==============================================================================================
//
//	�v���g�^�C�v�錾
//
//==============================================================================================
void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset );

static BOOL GMEVENT_GuinnessWin( GMEVENT_CONTROL* event );

static void GuinnessWin_Init( FIELDSYS_WORK* fsys, GUINNESS_WIN_WORK* wk, u8 cancel, WORDSET* wordset );
static void GuinnessWin_Start( GUINNESS_WIN_WORK* wk, u8 x, u8 y, u8 cursor );

static void BmpList_list_make( GUINNESS_WIN_WORK* wk, u32 msg_id, u32 param  );
static void BmpList_h_default_set(GUINNESS_WIN_WORK* wk);
static void	BmpList_CallBack( BMPLIST_WORK* lw, u32 param, u8 y );

static void ListMake_01( GUINNESS_WIN_WORK* wk );
static void talk_msg_print( GUINNESS_WIN_WORK* wk, u16 msg_id, u32 wait );

//�e�V�[�P���X����
static void NextSeqSet( GUINNESS_WIN_WORK* wk, u8 next_seq );
static void seq_list_sub( GUINNESS_WIN_WORK* wk );
static void seq_ranking_sub( GUINNESS_WIN_WORK* wk );
static void seq_yesno_sub( GUINNESS_WIN_WORK* wk );
static void seq_del_sub( GUINNESS_WIN_WORK* wk );
static void seq_end_sub( GUINNESS_WIN_WORK* wk );


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define GUINNESS_WIN_FONT		(FONT_SYSTEM)	//�t�H���g�w��
//#define GUINNESS_WIN_FONT	(FONT_TALK)			//�t�H���g�w��

#define GUINNESS_WIN_MSG_BUF_SIZE	(32*2)		//���b�Z�[�W�o�b�t�@�T�C�Y

//BMP���j���[
#define GUINNESS_WIN_MENU_MAX	(12)			//���j���[���ڂ̍ő吔

//BMP���X�g
#define GUINNESS_WIN_LIST_MAX	(16)			//���X�g���ڂ̍ő吔

//BMP���X�g�w�b�_�[��`
#define EV_LIST_LINE			(6)				//�\���ő區�ڐ�
#define EV_LIST_RABEL_X			(1)				//���x���\���w���W
#define EV_LIST_DATA_X			(12)			//���ڕ\���w���W
#define EV_LIST_LINE_Y			(8)				//�\���x���W

//�V�[�P���X��`
enum{
	SEQ_LIST,
	SEQ_RANKING,
	SEQ_YESNO,
	SEQ_DEL,
	SEQ_END,
};


//==============================================================================================
//
//	�����C���f�b�N�X�u��������`
//
//==============================================================================================
#define MSG_INDEX_SINGLE_BTL		(msg_ev_win_007)	//�u�V���O���o�g���v
#define MSG_INDEX_DOUBLE_BTL		(msg_ev_win_008)	//�u�_�u���o�g���v
#define MSG_INDEX_MULTI_BTL			(msg_ev_win_010)	//�u�}���`�o�g���v
#define MSG_INDEX_MULTI_COMM_BTL	(msg_ev_win_010)	//�u�}���`�o�g��������v
#define MSG_INDEX_WIFI_BTL			(msg_ev_win_010)	//�uWi-Fi�o�g���v
#define MSG_INDEX_AVERAGE_WIN		(msg_ev_win_021)	//�u�ւ������񂵂傤�����v
//...
//...
#define MSG_INDEX_FISHING			(msg_ev_win_051)	//�u�肠���������v

#define MSG_INDEX_WIN				(msg_ev_win_003)	//�u���傤�v
#define MSG_INDEX_CLOSE				(msg_ev_win_012)	//�u�Ƃ���v
#define MSG_INDEX_START				(msg_ev_win_011)	//�u�ǂ̂�񂵂傤���낭���݂܂����H�v
#define MSG_INDEX_DEL				(msg_ev_win_041)	//�u�����Ă������ł����H�v


//==============================================================================================
//
//	CGX
//
//==============================================================================================
#define GUINNESS_WIN_SX				(20)			//�E�B���h�E�T�C�Y
#define GUINNESS_WIN_SY				(14)			//�E�B���h�E�T�C�Y

//fld_bmp.h�Q��
enum{
	GUINNESS_LIST_CGX_NUM =		(1),				//1
	GUINNESS_WIN_CGX_NUM =		(MENU_WIN_CGX_NUM),	//473

	GUINNESS_YESNO_CGX_NUM =	(GUINNESS_WIN_CGX_NUM - (FLD_YESNO_WIN_SX * FLD_YESNO_WIN_SY))
	//GUINNESS_YESNO_CGX_NUM =	(FLD_YESNO_WIN_CGX),//277
	//GUINNESS_YESNO_CGX_NUM =	(GUINNESS_LIST_CGX_NUM + GUINNESS_WIN_SX * GUINNESS_WIN_SY),//281
	//GUINNESS_YESNO_CGX_NUM =	(512),
};

#if 0
OS_Printf("CGX_NUM = %d\n",(FLD_YESNO_WIN_CGX) );										//277
OS_Printf("CGX_NUM = %d\n",(GUINNESS_LIST_CGX_NUM+GUINNESS_WIN_SX*GUINNESS_WIN_SY));	//281
OS_Printf("CGX_NUM = %d\n",(FLD_MSG_WIN_CGX) );											//301
OS_Printf("CGX_NUM = %d\n",(MENU_WIN_CGX_NUM) );										//473
#endif


//==============================================================================================
//
//	�\����
//
//==============================================================================================
struct _GUINNESS_WIN_WORK{
	FIELDSYS_WORK * fsys;						//FIELDSYS_WORK�̃|�C���^

 	GF_BGL_BMPWIN bmpwin;						//BMP�E�B���h�E�f�[�^
 	GF_BGL_BMPWIN talk_bmpwin;					//��bBMP�E�B���h�E�f�[�^
	
	STRBUF* msg_buf[GUINNESS_WIN_MENU_MAX];		//���b�Z�[�W�f�[�^�̃|�C���^
	MSGDATA_MANAGER* msgman;					//���b�Z�[�W�}�l�[�W���[
	WORDSET* wordset;							//�P��Z�b�g

	u8 seq;										//�V�[�P���X�i���o�[
	u8 cancel;									//�L�����Z��
	u8 list_no;									//���j���[���ڂ̉��Ԗڂ�
	u8 del_mode;								//�폜���[�h�t���O

	u16 work1;									//���[�N1
	u16 work2;									//���[�N2
 
	BMPMENU_WORK* mw;							//�u�͂��E�������v�E�B���h�E

	//BMP���X�g
	BMPLIST_HEADER ListH;						//BMP���X�g�w�b�_�[
	BMPLIST_WORK* lw;							//BMP���X�g�f�[�^
	u16 list_bak;								//���X�g�ʒu�o�b�N�A�b�v
	u16 cursor_bak;								//�J�[�\���ʒu�o�b�N�A�b�v
	BMPLIST_DATA list_Data[GUINNESS_WIN_LIST_MAX];	//���X�g�f�[�^
};

//�u�͂��E�������v�E�B���h�E�f�[�^
static const BMPWIN_DAT YesNoBmpDat = {
	FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
	FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, GUINNESS_YESNO_CGX_NUM
};


//==============================================================================================
//
//	�O����Ăяo�����֐�	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�M�l�X�E�B���h�E�Ăяo��
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	wordset		WORDSET�^�̃|�C���^
 * @param	talk_bmpwin	GF_BGL_BMPWIN�^�̃|�C���^(��bBMPWIN��n��)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset )
{
	GUINNESS_WIN_WORK* wk;
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);

	//�J�n��
	Snd_SePlay( SE_GUINNESS_WIN_START );

	wk = sys_AllocMemory( HEAPID_FIELD, sizeof(GUINNESS_WIN_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "�M�l�X�E�B���h�E�������m�ێ��s�I" );
		return;	//�������Ȃ�
	}
	memset( wk, 0, sizeof(GUINNESS_WIN_WORK) );

	//���[�N������	
	GuinnessWin_Init( fsys, wk, cancel, wordset );

	//��b�r�b�g�}�b�v�E�B���h�E�f�[�^�ǉ�
	FldTalkBmpAdd( wk->fsys->bgl, &wk->talk_bmpwin ,FLD_MBGFRM_FONT);
	FieldTalkWinPut( &wk->talk_bmpwin, SaveData_GetConfig(wk->fsys->savedata) );
	talk_msg_print( wk, MSG_INDEX_START, MSG_ALLPUT );

	//���X�g�쐬
	ListMake_01( wk );

	//BmpList_list_make( wk, MSG_INDEX_WIN, 0 );

	GuinnessWin_Start( wk, x, y, cursor );

	FieldEvent_Call( event, GMEVENT_GuinnessWin, wk );
	return;
}


//==============================================================================================
//
//
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�C�x���g�E�B���h�E�@���[�N������
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GuinnessWin_Init( FIELDSYS_WORK* fsys, GUINNESS_WIN_WORK* wk, u8 cancel, WORDSET* wordset )
{
	int i;

	//���b�Z�[�W�f�[�^�}�l�[�W���[�쐬
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_ev_win_dat, HEAPID_FIELD );

	//�P��Z�b�g���W���[���쐬
	wk->wordset = WORDSET_Create( HEAPID_FIELD );
	//wk->wordset	= wordset;		//�X�N���v�g�������p��

	wk->fsys		= fsys;
	wk->cancel		= cancel;
	wk->list_no		= 0;

	for( i=0; i < GUINNESS_WIN_LIST_MAX ;i++ ){
		wk->list_Data[i].str	= NULL;
		wk->list_Data[i].param	= 0;
	}

	//MSGMAN_Create�̌�ɏ���
	for( i=0; i < GUINNESS_WIN_MENU_MAX ;i++ ){
		wk->msg_buf[i] = STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g�@�J�n
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GuinnessWin_Start( GUINNESS_WIN_WORK* wk, u8 x, u8 y, u8 cursor )
{
	//�\���ő區�ڐ��`�F�b�N
	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, x, y, 
									GUINNESS_WIN_SX, GUINNESS_WIN_SY, 
									FLD_SYSFONT_PAL, GUINNESS_LIST_CGX_NUM );


	//���ƂőΉ�
	//�x�T�C�Y�͕\�����ڐ������Ȃ��Ƃ��́A�ςɂȂ�I

	//���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g(409-511�g�p)
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//���j���[�E�B���h�E��`��
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL);

	//���X�g�w�b�_�[�����ݒ�
	BmpList_h_default_set(wk);

	wk->lw = BmpListSet( (const BMPLIST_HEADER*)&wk->ListH, 0, cursor, HEAPID_FIELD );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g	���X�g�쐬
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 * @param	msg_id		���b�Z�[�WID
 * @param	param		BMPLIST�p�����[�^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_list_make( GUINNESS_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < GUINNESS_WIN_LIST_MAX, "���X�g���ڐ��I�[�o�[�I" );

	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
	//*st = (const void *)&wk->msg_buf[wk->list_no][0];

	if( param == GUINNESS_WIN_LIST_LABEL ){
		wk->list_Data[ wk->list_no ].param = BMPLIST_RABEL;
		//*pa = BMPLIST_RABEL;
	}else{
		wk->list_Data[ wk->list_no ].param = param;
		//*pa = param;
	}

	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMP���X�g	�w�b�_�[�����ݒ�
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_h_default_set(GUINNESS_WIN_WORK* wk)
{
	wk->ListH.list		= wk->list_Data;
	wk->ListH.call_back = NULL;
	wk->ListH.icon		= BmpList_CallBack;
	wk->ListH.win		= &wk->bmpwin;

	wk->ListH.count		= wk->list_no;
	wk->ListH.line		= EV_LIST_LINE;

	wk->ListH.rabel_x	= EV_LIST_RABEL_X;
	wk->ListH.data_x	= EV_LIST_DATA_X;
	wk->ListH.cursor_x	= 0;
	wk->ListH.line_y	= EV_LIST_LINE_Y;

	wk->ListH.f_col		= FBMP_COL_BLACK;
	wk->ListH.b_col		= FBMP_COL_WHITE;		
	wk->ListH.s_col		= FBMP_COL_BLK_SDW;

	wk->ListH.msg_spc	= 0;
	wk->ListH.line_spc	= 16;
	wk->ListH.page_skip	= BMPLIST_LRKEY_SKIP;
	wk->ListH.font		= GUINNESS_WIN_FONT;
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

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�C�x���g���C��
 *
 * @param	event		GMEVENT_CONTROL�^�̃|�C���^
 *
 * @retval	"FALSE=�p���ATRUE=�I��"
 */
//--------------------------------------------------------------
static BOOL GMEVENT_GuinnessWin( GMEVENT_CONTROL* event )
{
	u32	ret;
	GUINNESS_WIN_WORK* wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){

	//���X�g����(���ڂ�I��)
	case SEQ_LIST:
		seq_list_sub( wk );
		break;

	//�����L���O����
	case SEQ_RANKING:
		seq_ranking_sub( wk );
		break;

	//�u�͂��E�������v�I��
	case SEQ_YESNO:
		seq_yesno_sub( wk );
		break;

	//�폜����
	case SEQ_DEL:
		seq_del_sub( wk );
		break;

	//�I������
	case SEQ_END:
		seq_end_sub( wk );
		sys_FreeMemoryEz( wk );
		return TRUE;			//�I���I
	};

	return FALSE;
};


//==============================================================================================
//
//	�e�V�[�P���X����
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	�Z�b�g
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void NextSeqSet( GUINNESS_WIN_WORK* wk, u8 next_seq )
{
	wk->seq = next_seq;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	���X�g
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_list_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret = BmpListMain( wk->lw );

	switch( ret ){

	case BMPLIST_NULL:
		break;

	case BMPLIST_CANCEL:
		NextSeqSet( wk, SEQ_END );
		break;

	default:
		wk->work1 = ret;						//�I�������l�����[�N�ɑ��
		NextSeqSet( wk, SEQ_RANKING );
		break;;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	�����L���O
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_ranking_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret;

	if( sys.trg & PAD_BUTTON_SELECT ){
		wk->del_mode = 1;					//�폜���[�hON
		return;
	}

	ret = BmpListMain( wk->lw );

	switch( ret ){

	case BMPLIST_NULL:
		break;

	case BMPLIST_CANCEL:
		if( wk->del_mode == 1 ){;
			wk->del_mode = 0;				//�폜���[�hOFF
		}

		NextSeqSet( wk, SEQ_LIST );
		break;

	default:
		//�폜���[�hON��������
		if( wk->del_mode == 1 ){;
			wk->work1 = ret;				//�I�������l�����[�N�ɑ��

			wk->mw = BmpYesNoSelectInit( wk->fsys->bgl, &YesNoBmpDat, 
											GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );

			talk_msg_print( wk, MSG_INDEX_DEL, MSG_ALLPUT );

			NextSeqSet( wk, SEQ_YESNO );
		}
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	�u�͂��E�������v
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_yesno_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret  = BmpYesNoSelectMain( wk->mw, HEAPID_FIELD );

	if( ret == 0 ){								//�͂�
		NextSeqSet( wk, SEQ_DEL );
	}else if( ret == BMPMENU_CANCEL ){			//�������A�L�����Z��
		NextSeqSet( wk, SEQ_RANKING );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	�폜
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_del_sub( GUINNESS_WIN_WORK* wk )
{
	//�I�����Ă���f�[�^���폜
	//

	//�f�[�^���\�[�g������
	//
		
	//�ĕ`��
	//
		
	NextSeqSet( wk, SEQ_RANKING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X	�I��
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_end_sub( GUINNESS_WIN_WORK* wk )
{
	int i;

	Snd_SePlay( SE_DECIDE );	//���ӁI

	//��b�E�B���h�E�I��
	BmpTalkWinClear( &wk->talk_bmpwin, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->talk_bmpwin );

	//���X�g�I��
	BmpListExit( wk->lw, NULL, NULL );
	BmpMenuWinClear( wk->ListH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->bmpwin );

	for( i=0; i < GUINNESS_WIN_MENU_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	WORDSET_Delete( wk->wordset );
	MSGMAN_Delete( wk->msgman );

	return;
}


//==============================================================================================
//
//
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	��b�E�B���h�E�Ƀ��b�Z�[�W���ꊇ�\��
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃A�h���X
 * @param	msg_id		���b�Z�[�WID
 * @param	wait		���b�Z�[�W�E�F�C�g
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_print( GUINNESS_WIN_WORK* wk, u16 msg_id, u32 wait )
{
	STRBUF* tmp_buf = STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );

	//���b�Z�[�W�N���A
	GF_BGL_BmpWinDataFill( &wk->talk_bmpwin, (FBMP_COL_WHITE) );

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	//�o�^���ꂽ�P����g���ĕ�����W�J����
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( &wk->talk_bmpwin, FONT_TALK, tmp_buf2, 0, 0, wait, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	�\�����邩�`�F�b�N���ă��X�g�쐬01
 *
 * @param	wk			GUINNESS_WIN_WORK�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ListMake_01( GUINNESS_WIN_WORK* wk )
{
	//�V���O���o�g���A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_SINGLE_BTL, 0 );
	}

	//�_�u���o�g���A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_DOUBLE_BTL, 1 );
	}

	//�}���`�o�g���A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_MULTI_BTL, 2 );
	}

	//�ʐM�}���`�o�g���A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_MULTI_COMM_BTL, 3 );
	}

	//Wi-Fi�o�g���A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_WIFI_BTL, 4 );
	}

	//�o�g���^���[���ϘA�����A����
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_AVERAGE_WIN, 5 );
	}

	BmpList_list_make( wk, MSG_INDEX_CLOSE, 6 );			//�u�Ƃ���v
	return;
}


