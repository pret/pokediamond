//============================================================================================
/**
 * @file	bmp_menu.c
 * @brief	BMP���j���[����
 * @author	Hiroyuki Nakamura
 * @date	2004.11.10
 *
 *	�E���j���[���X�N���[������Ȃ�BMPLIST���g�p���邱��
 *	�E�c�A���̃��j���[�ɑΉ�
 */
//============================================================================================
#define	BMP_MENU_H_GLOBAL

#include "common.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/palanm.h"
#include "system/window.h"
#include "system/bmp_cursor.h"
#include "system/snd_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"

#define	BMP_MENU_H_GLOBAL
#include "system/bmp_menu.h"


//============================================================================================
//	�V���{����`
//============================================================================================
enum {
	MV_UP = 0,
	MV_DOWN,
	MV_LEFT,
	MV_RIGHT
};

struct _BMPMENU_WORK {
	BMPMENU_HEADER	hed;
	BMPCURSOR * cursor;
	u32	cancel;
	u8	index;
	u8	cur_pos;
	u8	len;
	u8	px;
	u8	py;
	u8	sx;
	u8	sy;

	u8	mv;

	u8	mode;		// �������擾���[�h
};



//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BmpMenuWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx );
static void BmpTalkWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx );
static BOOL BmpMenuCursorMove( BMPMENU_WORK * mw, u8 mv, u16 se );
static u8 BmpMenuCursorMoveCheck( BMPMENU_WORK * mw, u8 mv );
static u8 BmpMenuStrLen( BMPMENU_WORK * buf );
static void BmpMenuStrPut( BMPMENU_WORK * mw );
static void BmpMenuCursorPut( BMPMENU_WORK * mw );
static void CursorWritePosGet( BMPMENU_WORK * mw, u8 * x, u8 * y, u8 pos );

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BMP���j���[�o�^�i�X�N���[���]�����Ȃ��j
 *
 * @param	dat			�w�b�_�f�[�^
 * @param	px			���ڕ\��X���W
 * @param	py			���ڕ\��Y���W
 * @param	pos			�����J�[�\���ʒu
 * @aram	mode		�������擾���[�h
 * @param	cancel		�L�����Z���{�^��
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
 */
//--------------------------------------------------------------------------------------------
BMPMENU_WORK * BmpMenuAdd_NoTrans(
					const BMPMENU_HEADER * dat, u8 px, u8 py, u8 pos, u8 mode, u32 cancel )
{
	BMPMENU_WORK * mw = (BMPMENU_WORK *)sys_AllocMemory( mode, sizeof(BMPMENU_WORK) );

	mw->hed		= *dat;
	mw->cursor  = BMPCURSOR_Create( mode );
	mw->cancel  = cancel;
	mw->cur_pos	= pos;
	mw->len		= BmpMenuStrLen( mw );
	mw->mode    = mode;

	mw->px = px;
	mw->py = py;
	mw->sx = FontHeaderGet( dat->font, FONT_HEADER_SIZE_X )
				+ FontHeaderGet( dat->font, FONT_HEADER_SPACE_X );
	mw->sy = FontHeaderGet( dat->font, FONT_HEADER_SIZE_Y )
				+ FontHeaderGet( dat->font, FONT_HEADER_SPACE_Y );

	BmpMenuStrPut( mw );
	BmpMenuCursorPut( mw );

	return mw;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���j���[�o�^�i�L�����Z���{�^���w��j
 *
 * @param	dat			�w�b�_�f�[�^
 * @param	px			���ڕ\��X���W
 * @param	py			���ڕ\��Y���W
 * @param	pos			�����J�[�\���ʒu
 * @aram	mode		�������擾���[�h
 * @param	cancel		�L�����Z���{�^��
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
 */
//--------------------------------------------------------------------------------------------
BMPMENU_WORK * BmpMenuAddEx(
					const BMPMENU_HEADER * dat, u8 px, u8 py, u8 pos, u8 mode, u32 cancel )
{
	BMPMENU_WORK * mw = BmpMenuAdd_NoTrans( dat, px, py, pos, mode, cancel );

	GF_BGL_BmpWinOn( mw->hed.win );

	return mw;
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���j���[�o�^�i�ȈՔŁj
 *
 * @param	dat			�w�b�_�f�[�^
 * @param	pos			�����J�[�\���ʒu
 * @aram	mode		�������擾���[�h
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
 * @li	B�{�^���L�����Z��
 */
//--------------------------------------------------------------------------------------------
BMPMENU_WORK * BmpMenuAdd( const BMPMENU_HEADER * dat, u8 pos, u8 mode )
{
	return BmpMenuAddEx(
				dat, FontHeaderGet( dat->font, FONT_HEADER_SIZE_X ), 0,
				pos, mode, PAD_BUTTON_CANCEL );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���j���[�j��
 *
 * @param	mw		BMP���j���[���[�N
 * @param	backup	�J�[�\���ʒu�ۑ��ꏊ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpMenuExit( BMPMENU_WORK * mw, u8 * backup )
{
	if( backup != NULL ){
		*backup = mw->cur_pos;
	}
	BMPCURSOR_Delete( mw->cursor );
	sys_FreeMemory( mw->mode, mw );
}


//--------------------------------------------------------------------------------------------
/**
 * ���j���[����֐�
 *
 * @param	mw		BMP���j���[���[�N
 *
 * @return	���쌋��
 */
//--------------------------------------------------------------------------------------------
u32 BmpMenuMain( BMPMENU_WORK * mw )
{
	mw->mv = BMPMENU_MOVE_NONE;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		Snd_SePlay( SE_DECIDE );
		return mw->hed.menu[ mw->cur_pos ].param;
	}
	if( sys.trg & mw->cancel ){
		Snd_SePlay( SE_CANCEL );
		return BMPMENU_CANCEL;
	}
	if( sys.trg & PAD_KEY_UP ){
		if( BmpMenuCursorMove( mw, MV_UP, SEQ_SE_DP_SELECT ) == TRUE ){
			mw->mv = BMPMENU_MOVE_UP;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_DOWN ){
		if( BmpMenuCursorMove( mw, MV_DOWN, SEQ_SE_DP_SELECT ) == TRUE ){
			mw->mv = BMPMENU_MOVE_DOWN;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_LEFT ){
		if( BmpMenuCursorMove( mw, MV_LEFT, SEQ_SE_DP_SELECT ) == TRUE ){
			mw->mv = BMPMENU_MOVE_LEFT;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		if( BmpMenuCursorMove( mw, MV_RIGHT, SEQ_SE_DP_SELECT ) == TRUE ){
			mw->mv = BMPMENU_MOVE_RIGHT;
		}
		return BMPMENU_NULL;
	}

	return BMPMENU_NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[����֐��i�\���L�[��SE���w��ł���j
 *
 * @param	mw		BMP���j���[���[�N
 * @param	key_se	�\���L�[��SE
 *
 * @return	���쌋��
 */
//--------------------------------------------------------------------------------------------
u32 BmpMenuMain_SE( BMPMENU_WORK * mw, u16 key_se )
{
	mw->mv = BMPMENU_MOVE_NONE;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		Snd_SePlay( SE_DECIDE );
		return mw->hed.menu[ mw->cur_pos ].param;
	}
	if( sys.trg & mw->cancel ){
		Snd_SePlay( SE_CANCEL );
		return BMPMENU_CANCEL;
	}
	if( sys.trg & PAD_KEY_UP ){
		if( BmpMenuCursorMove( mw, MV_UP, key_se ) == TRUE ){
			mw->mv = BMPMENU_MOVE_UP;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_DOWN ){
		if( BmpMenuCursorMove( mw, MV_DOWN, key_se ) == TRUE ){
			mw->mv = BMPMENU_MOVE_DOWN;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_LEFT ){
		if( BmpMenuCursorMove( mw, MV_LEFT, key_se ) == TRUE ){
			mw->mv = BMPMENU_MOVE_LEFT;
		}
		return BMPMENU_NULL;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		if( BmpMenuCursorMove( mw, MV_RIGHT, key_se ) == TRUE ){
			mw->mv = BMPMENU_MOVE_RIGHT;
		}
		return BMPMENU_NULL;
	}

	return BMPMENU_NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�O���R���g���[��
 *
 * @param	mw		BMP���j���[���[�N
 * @param	prm		�R���g���[���p�����[�^
 *
 * @return	���쌋��
 */
//--------------------------------------------------------------------------------------------
u32 BmpMenuMainOutControl( BMPMENU_WORK * mw, u8 prm )
{
	switch( prm ){
	case BMPMENU_CNTROL_DECIDE:		// ����
		Snd_SePlay( SE_DECIDE );
		return mw->hed.menu[ mw->cur_pos ].param;

	case BMPMENU_CNTROL_CANCEL:		// �L�����Z��
		Snd_SePlay( SE_CANCEL );
		return BMPMENU_CANCEL;

	case BMPMENU_CNTROL_UP:			// ��
		BmpMenuCursorMove( mw, MV_UP, SEQ_SE_DP_SELECT );
		return BMPMENU_NULL;

	case BMPMENU_CNTROL_DOWN:		// ��
		BmpMenuCursorMove( mw, MV_DOWN, SEQ_SE_DP_SELECT );
		return BMPMENU_NULL;

	case BMPMENU_CNTROL_LEFT:		// ��
		BmpMenuCursorMove( mw, MV_LEFT, SEQ_SE_DP_SELECT );
		return BMPMENU_NULL;

	case BMPMENU_CNTROL_RIGHT:		// �E
		BmpMenuCursorMove( mw, MV_RIGHT, SEQ_SE_DP_SELECT );
		return BMPMENU_NULL;
	}

	return BMPMENU_NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���ʒu�擾
 *
 * @param	mw		BMP���j���[���[�N
 *
 * @return	�J�[�\���ʒu
 */
//--------------------------------------------------------------------------------------------
u8 BmpMenuCursorPosGet( BMPMENU_WORK * mw )
{
	return mw->cur_pos;
}

//--------------------------------------------------------------------------------------------
/**
 * �ړ������擾
 *
 * @param	mw		BMP���j���[���[�N
 *
 * @return	�ړ������擾
 */
//--------------------------------------------------------------------------------------------
u8 BmpMenuMoveSiteGet( BMPMENU_WORK * mw )
{
	return mw->mv;
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���ړ�
 *
 * @param	mw		BMP���j���[���[�N
 * @param	mv		�ړ�����
 * @param	se		SE
 *
 * @retval	"TRUE = �ړ�����"
 * @retval	"FALSE = �ړ����ĂȂ�"
 */
//--------------------------------------------------------------------------------------------
static BOOL BmpMenuCursorMove( BMPMENU_WORK * mw, u8 mv, u16 se )
{
	u8	old = mw->cur_pos;

	if( BmpMenuCursorMoveCheck( mw, mv ) == FALSE ){
		return FALSE;
	}

	{
		u8	px, py;
		u8	col;
		
		col = FontHeaderGet( mw->hed.font, FONT_HEADER_B_COLOR );
		CursorWritePosGet( mw, &px, &py, old );
		GF_BGL_BmpWinFill( mw->hed.win, col, px, py, 8, mw->sy );
	}
	BmpMenuCursorPut( mw );
	Snd_SePlay( se );

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���ړ��`�F�b�N
 *
 * @param	mw		BMP���j���[���[�N
 * @param	mv		�ړ�����
 *
 * @retval	"TRUE = �ړ�����"
 * @retval	"FALSE = �ړ����ĂȂ�"
 */
//--------------------------------------------------------------------------------------------
static u8 BmpMenuCursorMoveCheck( BMPMENU_WORK * mw, u8 mv )
{
	s8	new_pos;

	if( mv == MV_UP ){
		if( mw->hed.y_max <= 1 ){ return FALSE; }
		if( ( mw->cur_pos % mw->hed.y_max ) == 0 ){
			if( mw->hed.loop_f == 0 ){ return FALSE; }
//			mw->cur_pos += ( mw->hed.y_max - 1 );
			new_pos = mw->cur_pos + ( mw->hed.y_max - 1 );
		}else{
//			mw->cur_pos -= 1;
//			return TRUE;
			new_pos = mw->cur_pos - 1;
		}
	}else if( mv == MV_DOWN ){
		if( mw->hed.y_max <= 1 ){ return FALSE; }
		if( ( mw->cur_pos % mw->hed.y_max ) == ( mw->hed.y_max - 1 ) ){
			if( mw->hed.loop_f == 0 ){ return FALSE; }
//			mw->cur_pos -= ( mw->hed.y_max - 1 );
			new_pos = mw->cur_pos - ( mw->hed.y_max - 1 );
		}else{
//			mw->cur_pos += 1;
//			return TRUE;
			new_pos = mw->cur_pos + 1;
		}
	}else if( mv == MV_LEFT ){
		if( mw->hed.x_max <= 1 ){ return FALSE; }
		if( mw->cur_pos < mw->hed.y_max ){
			if( mw->hed.loop_f == 0 ){ return FALSE; }
//			mw->cur_pos += ( mw->hed.y_max * ( mw->hed.x_max - 1 ) );
			new_pos = mw->cur_pos + ( mw->hed.y_max * ( mw->hed.x_max - 1 ) );
		}else{
//			mw->cur_pos -= mw->hed.y_max;
//			return TRUE;
			new_pos = mw->cur_pos - mw->hed.y_max;
		}
	}else{
		if( mw->hed.x_max <= 1 ){ return FALSE; }
		if( mw->cur_pos >= ( mw->hed.y_max * ( mw->hed.x_max - 1 ) ) ){
			if( mw->hed.loop_f == 0 ){ return FALSE; }
//			mw->cur_pos %= mw->hed.y_max;
			new_pos = mw->cur_pos % mw->hed.y_max;
		}else{
//			mw->cur_pos += mw->hed.y_max;
//			return TRUE;
			new_pos = mw->cur_pos + mw->hed.y_max;
		}
	}

	if( mw->hed.menu[ new_pos ].param == BMPMENU_DUMMY ){
		return FALSE;
	}
	mw->cur_pos = new_pos;
	return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * �Œ����ڂ̕��������擾
 *
 * @param	buf		BMP���j���[���[�N
 *
 * @return	�Œ����ڂ̕�����
 */
//--------------------------------------------------------------------------------------------
static u8 BmpMenuStrLen( BMPMENU_WORK * buf )
{
	u8	len = 0;
	u8	i, j;


	for( i=0; i<buf->hed.x_max*buf->hed.y_max; i++ ){
		j = FontProc_GetPrintStrWidth( buf->hed.font, buf->hed.menu[i].str, 0 );
		if( len < j ){ len = j; }
	}

	return len;
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[���ڕ\��
 *
 * @param	mw		BMP���j���[���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpMenuStrPut( BMPMENU_WORK * mw )
{
	const void* str;
	u8	px, py, plus;
	u8	i, j;

	GF_BGL_BmpWinDataFill( mw->hed.win, FontHeaderGet( mw->hed.font, FONT_HEADER_B_COLOR ) );

	px = mw->px;
//	plus = px * ( mw->len + 2 );
	plus = mw->len + mw->sx * 2;
	for( i=0; i<mw->hed.x_max; i++ ){
		for( j=0; j<mw->hed.y_max; j++ ){
			str = mw->hed.menu[i*mw->hed.y_max+j].str;
			py  = ( mw->sy + mw->hed.line_spc ) * j + mw->py;
			GF_STR_PrintSimple( mw->hed.win, mw->hed.font, str, px, py, MSG_NO_PUT, NULL );
		}
		px += plus;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���\��
 *
 * @param	mw		BMP���j���[���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpMenuCursorPut( BMPMENU_WORK * mw )
{
	u8	px, py;

	if( mw->hed.c_disp_f == 1 ){ return; }

	CursorWritePosGet( mw, &px, &py, mw->cur_pos );
	BMPCURSOR_Print( mw->cursor, mw->hed.win, px, py );
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���\���ʒu�擾
 *
 * @param	buf		BMP���j���[�f�[�^
 * @param	x		�\��X���W�擾�ꏊ
 * @param	y		�\��Y���W�擾�ꏊ
 * @param	pos		�J�[�\���ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CursorWritePosGet( BMPMENU_WORK * mw, u8 * x, u8 * y, u8 pos )
{
//	*x = ( pos / mw->hed.y_max ) * ( mw->len + 2 ) * mw->sx;
	*x = ( pos / mw->hed.y_max ) * ( mw->len + mw->sx * 2 );
	*y = ( pos % mw->hed.y_max ) * ( mw->sy + mw->hed.line_spc ) + mw->py;
}


//============================================================================================
//	�͂��E����������
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������E�B���h�E�Z�b�g�i�J�[�\���ʒu�w��j
 *
 * @param	ini		BGL�f�[�^
 * @param	data	�E�B���h�E�f�[�^
 * @param	cgx		�E�B���h�E�L�����ʒu
 * @param	pal		�E�B���h�E�p���b�g�ԍ�
 * @param	pos		�����J�[�\���ʒu
 * @param	heap	�q�[�vID
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP�E�B���h�E��BMP���j���[���[�N��Alloc�Ŏ擾���Ă���
 */
//--------------------------------------------------------------------------------------------
BMPMENU_WORK * BmpYesNoSelectInitEx(
				GF_BGL_INI * ini, const BMPWIN_DAT * data, u16 cgx, u8 pal, u8 pos, u32 heap )
{
	BMPMENU_HEADER hed;
	MSGDATA_MANAGER * man;
	BMP_MENULIST_DATA * ld;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, heap );
	ld  = BMP_MENULIST_Create( 2, heap );
	BMP_MENULIST_AddArchiveString( ld, man, msg_ev_win_046, 0 );
	BMP_MENULIST_AddArchiveString( ld, man, msg_ev_win_047, BMPMENU_CANCEL );
	MSGMAN_Delete( man );

	hed.menu     = ld;
	hed.win      = GF_BGL_BmpWinAllocGet( heap, 1 );
	hed.font     = FONT_SYSTEM;
	hed.x_max    = 1;
	hed.y_max    = 2;
	hed.line_spc = 0;
	hed.c_disp_f = 0;
	hed.line_spc = 0;

	GF_BGL_BmpWinAddEx( ini, hed.win, data );
	BmpMenuWinWrite( hed.win, WINDOW_TRANS_OFF, cgx, pal );
	return BmpMenuAddEx( &hed, 8, 0, pos, heap, PAD_BUTTON_CANCEL );
}

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������E�B���h�E�Z�b�g
 *
 * @param	ini		BGL�f�[�^
 * @param	data	�E�B���h�E�f�[�^
 * @param	cgx		�E�B���h�E�L�����ʒu
 * @param	pal		�E�B���h�E�p���b�g�ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP�E�B���h�E��BMP���j���[���[�N��Alloc�Ŏ擾���Ă���
 */
//--------------------------------------------------------------------------------------------
BMPMENU_WORK * BmpYesNoSelectInit(
					GF_BGL_INI * ini, const BMPWIN_DAT * data, u16 cgx, u8 pal, u32 heap )
{
/*
	BMPMENU_HEADER hed;
	MSGDATA_MANAGER * man;
	BMP_MENULIST_DATA * ld;

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, heap );
	ld  = BMP_MENULIST_Create( 2, heap );
	BMP_MENULIST_AddArchiveString( ld, man, msg_ev_win_046, 0 );
	BMP_MENULIST_AddArchiveString( ld, man, msg_ev_win_047, BMPMENU_CANCEL );
	MSGMAN_Delete( man );

	hed.menu     = ld;
	hed.win      = GF_BGL_BmpWinAllocGet( heap, 1 );
	hed.font     = FONT_SYSTEM;
	hed.x_max    = 1;
	hed.y_max    = 2;
	hed.line_spc = 0;
	hed.c_disp_f = 0;
	hed.line_spc = 0;

	GF_BGL_BmpWinAddEx( ini, hed.win, data );
	BmpMenuWinWrite( hed.win, WINDOW_TRANS_OFF, cgx, pal );
	return BmpMenuAddEx( &hed, 8, 0, 0, heap, PAD_BUTTON_CANCEL );
*/
	return BmpYesNoSelectInitEx( ini, data, cgx, pal, 0, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������I���E�B���h�E�̐���
 *
 * @param	ini		BGL�f�[�^
 * @param	heap	�q�[�vID
 *
 * @retval	"BMPMENU_NULL	�I������Ă��Ȃ�"
 * @retval	"0				�͂���I��"
 * @retval	"BMPMENU_CANCEL	������or�L�����Z��"
 */
//--------------------------------------------------------------------------------------------
u32 BmpYesNoSelectMain( BMPMENU_WORK * mw, u32 heap )
{
	u32	ret = BmpMenuMain( mw );

	if( ret != BMPMENU_NULL ){
		BmpYesNoWinDel( mw, heap );
	}
	return	ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������I���E�B���h�E�O���R���g���[��
 *
 * @param	ini		BGL�f�[�^
 * @param	prm		�R���g���[���p�����[�^
 * @param	heap	�q�[�vID
 *
 * @retval	"BMPMENU_NULL	�I������Ă��Ȃ�"
 * @retval	"0				�͂���I��"
 * @retval	"BMPMENU_CANCEL	������or�L�����Z��"
 */
//--------------------------------------------------------------------------------------------
u32 BmpYesNoSelectMainOutControl( BMPMENU_WORK * mw, u8 prm, u32 heap )
{
	u32	ret = BmpMenuMainOutControl( mw, prm );

	if( ret != BMPMENU_NULL ){
		BmpYesNoWinDel( mw, heap );
	}
	return	ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �͂��E�������E�B���h�E�폜
 *
 * @param	ini		BGL�f�[�^
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpYesNoWinDel( BMPMENU_WORK * mw, u32 heap )
{
	BmpMenuWinClear( mw->hed.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( mw->hed.win );
	sys_FreeMemory( heap, mw->hed.win );
	BMP_MENULIST_Delete( (BMP_MENULIST_DATA *)mw->hed.menu );
	BmpMenuExit( mw, NULL );
}


//------------------------------------------------------------------
/**
 * �E�B���h�E�ɃJ�[�\���摜��`��
 *
 * @param   win		�E�B���h�E
 * @param   x		�`��w���W�i�h�b�g�j
 * @param   y		�`��x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
void BmpWin_DrawCursorImage(GF_BGL_BMPWIN* win, u32 x, u32 y)
{
	static const u8 CursorBitmapImage[] = {
		0xff,0xff,0xff,0x00,
		0xff,0xff,0xff,0x00,
		0x21,0xff,0xff,0x00,
		0x11,0xf2,0xff,0x00,
		0x11,0x21,0xff,0x00,
		0x11,0x11,0xf2,0x00,
		0x11,0x11,0x21,0x00,
		0x11,0x11,0x22,0x00,

		0x11,0x21,0xf2,0x00,
		0x11,0x22,0xff,0x00,
		0x21,0xf2,0xff,0x00,
		0x22,0xff,0xff,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
	};

	GF_BGL_BmpWinPrint( win, (void*)CursorBitmapImage, 0, 0, 8, 16, x, y, 8, 16 );

}

