//=============================================================================
/**
 * @file	bmp_list.c	
 * @brief	�r�b�g�}�b�v�a�f��ł̃��X�g�\���V�X�e��
 * @author	GAME FREAK inc.
 * @date	tetsu
 */
//=============================================================================
#include <nitro.h>
#include <nnsys.h>
#include "common.h"
#include "fntsys.h"
#include "system/fontproc.h"
#include "system/bmp_cursor.h"

#define __BMP_LIST_H_GLOBAL__
#include "system/bmp_list.h"


/********************************************************************/
/*                                                                  */
/*				�g�p��`											*/
/*                                                                  */
/********************************************************************/
enum {
	LIST_UP = 0,
	LIST_DOWN
};


typedef struct {
	u8	f_col:4;		// �\�������F
	u8	b_col:4;		// �\���w�i�F
	u8	s_col:4;		// �\�������e�F
	u8	msg_spc:6;		// �����Ԋu�w
	u8	dummy:6;		// ���g�p
	u8	font:7;			// �����w��
	u8	sw:1;			// �ꎞ�ύX�X�C�b�`
}BMPLIST_TMP;

///���X�g���[�N�\����
struct _BMPLIST_WORK {

	BMPLIST_HEADER	hed;	//�\�������f�[�^�w�b�_

	BMPLIST_TMP		tmp;	// �ꎞ�ύX�f�[�^

	BMPCURSOR * cursor;		// BMP�J�[�\���f�[�^

	u16	lp;			//���X�g�ʒu
	u16	cp;			//�J�[�\���ʒu
	u8	seq;		//�����V�[�P���X
	u8	scrwork;	//�X�N���[�����[�N
	u8	cur_actID;	//
	u8	work;		//�ړ������i�g���ĂȂ��悤�Ȃ̂Łj

	u8	mode;		// �������擾���[�h
};


/********************************************************************/
/*                                                                  */
/*				���[�J���֐��錾									*/
/*                                                                  */
/********************************************************************/
static void LocalMsgPrint( BMPLIST_WORK * lw, void * msg, u8 x, u8 y );
static void ListScreenPut( BMPLIST_WORK * lw, u16 print_p, u16 line, u16 len );
static void ListCursorPut( BMPLIST_WORK * lw );
static void ListCursorCls( BMPLIST_WORK * lw, u16 p );
static u8 ListCursorMoveUpDown( BMPLIST_WORK * lw, u8 mode );
static void ListScrollMoveUpDown( BMPLIST_WORK * lw, u8 len, u8 mode );
static u8 ListMoveUpDownCheck( BMPLIST_WORK * lw, u8 print_f, u8 req_line, u8 mode );
static void CallBackSet( BMPLIST_WORK * lw, u8 mode );



//--------------------------------------------------------------------------------------------
/**
 * �ݒ�֐�
 *
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	mode		�������擾���[�h
 *
 * @return	BMP���X�g���[�N
 *
 * @li	BMP���X�g���[�N��sys_AllocMemory�Ŋm��
 */
//--------------------------------------------------------------------------------------------
BMPLIST_WORK * BmpListSet(
					const BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p, u8 mode )
{
	BMPLIST_WORK * lw = (BMPLIST_WORK *)sys_AllocMemory( mode, sizeof(BMPLIST_WORK) );

	// ��{�ݒ�
	lw->hed       = *bmplist;
	lw->cursor    = BMPCURSOR_Create( mode );
	lw->lp        = list_p;
	lw->cp        = cursor_p;
	lw->seq       = 0;
	lw->scrwork   = 0;
	lw->cur_actID = 0xff;
	lw->work      = 0;
	lw->mode      = mode;

	// �e���|����������
	lw->tmp.f_col   = lw->hed.f_col;	// �\�������F
	lw->tmp.b_col   = lw->hed.b_col;	// �\���w�i�F
	lw->tmp.s_col   = lw->hed.s_col;	// �\�������e�F
	lw->tmp.msg_spc = lw->hed.msg_spc;	// �����Ԋu�w
	lw->tmp.font    = lw->hed.font;		// �����w��
	lw->tmp.sw      = 0;				// �ꎞ�ύX�X�C�b�`

	// ���ڐ����\���w�胉�C������菭�Ȃ��ꍇ�́A�\���w�胉�C���������ڐ��ɂ��킹��
	if( lw->hed.count < lw->hed.line ){
		lw->hed.line = lw->hed.count;
	}

	// BMP�J�[�\���F�ύX
	BMPCURSOR_ChangeColor(
		lw->cursor, GF_PRINTCOLOR_MAKE(lw->hed.f_col,lw->hed.s_col,lw->hed.b_col) );

	// ���X�g�L�����f�[�^������
	GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );
	ListScreenPut( lw, lw->lp, 0, lw->hed.line );		// �S�̃��X�g�`��
	ListCursorPut( lw );								// �J�[�\���`��

	CallBackSet( lw, 1 );

	GF_BGL_BmpWinOn( bmplist->win );

	return lw;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���֐�
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @retval	"param = �I���p�����[�^"
 * @retval	"BMPLIST_NULL = �I��"
 * @retval	"BMPLIST_CANCEL	= �L�����Z��(�a�{�^��)"
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMain( BMPLIST_WORK * lw )
{
	u16	skip_u, skip_d;

	lw->work = BMPLIST_MOVE_NONE;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		return lw->hed.list[lw->lp + lw->cp].param;
	}
	if( sys.trg & PAD_BUTTON_CANCEL ){
		return BMPLIST_CANCEL;
	}
	if( sys.repeat & PAD_KEY_UP ){
		if( ListMoveUpDownCheck( lw, 1, 1, LIST_UP ) == 0 ){
			lw->work = BMPLIST_MOVE_UP;
		}
		return BMPLIST_NULL;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		if( ListMoveUpDownCheck( lw, 1, 1, LIST_DOWN ) == 0 ){
			lw->work = BMPLIST_MOVE_DOWN;
		}
		return BMPLIST_NULL;
	}
	//�X�L�b�v�t���O����
	switch( lw->hed.page_skip ){
	default:
	case BMPLIST_NO_SKIP:
		skip_u = 0;
		skip_d = 0;
		break;
	case BMPLIST_LRKEY_SKIP:
		skip_u = ( sys.repeat & PAD_KEY_LEFT );
		skip_d = ( sys.repeat & PAD_KEY_RIGHT );
		break;
	case BMPLIST_LRBTN_SKIP:
		skip_u = ( sys.repeat & PAD_BUTTON_L );
		skip_d = ( sys.repeat & PAD_BUTTON_R );
		break;
	}
	if( skip_u ){
		if( ListMoveUpDownCheck( lw, 1, (u8)lw->hed.line, LIST_UP ) == 0 ){
			lw->work = BMPLIST_MOVE_UP_SKIP;
		}
		return BMPLIST_NULL;
	}
	if( skip_d ){
		if( ListMoveUpDownCheck( lw, 1, (u8)lw->hed.line, LIST_DOWN ) == 0 ){
			lw->work = BMPLIST_MOVE_DOWN_SKIP;
		}
		return BMPLIST_NULL;
	}

	return BMPLIST_NULL;
}


//--------------------------------------------------------------------------------------------
/**
 * �I���֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 *
 * @li	lw��sys_FreeMemory�ŊJ��
 * @li	�o�b�N�A�b�v���[�N�́ANULL�w��ŕۑ����Ȃ�
 */
//--------------------------------------------------------------------------------------------
void BmpListExit( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak )
{
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}
/*
	if( lw->cur_actID != 0xff ){
		CursorListActorDel( lw->cur_actID, lw->lh.c_disp_f - 2 );
	}
*/
	BMPCURSOR_Delete( lw->cursor );
	sys_FreeMemory( lw->mode, lw );
}

//--------------------------------------------------------------------------------------------
/**
 * ���X�g�ĕ`��
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListRewrite( BMPLIST_WORK * lw )
{
	// ���X�g�L�����f�[�^������
	GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );

	ListScreenPut( lw, lw->lp, 0, lw->hed.line );	// �S�̃��X�g�`��
	ListCursorPut( lw );							// �J�[�\���`��
	GF_BGL_BmpWinOn( lw->hed.win );
}


//--------------------------------------------------------------------------------------------
/**
 * �����F�ύX�֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	f_col		�����F
 * @param	b_col		�w�i�F
 * @param	s_col		�e�F
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListColorControl( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col )
{
	lw->hed.f_col = f_col;	//�����F�i���o�[
	lw->hed.b_col = b_col;	//�w�i�F�i���o�[
	lw->hed.s_col = s_col;	//�e�F�@�i���o�[
}

//--------------------------------------------------------------------------------------------
/**
 * �\���ʒu�ύX�֐�
 *
 * @param	lw			BMP���X�g���[�N
 * @param	x			�\���w���W(�L�����P��)
 * @param	y			�\���x���W(�L�����P��)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListMoveControl( BMPLIST_WORK * lw, u8 x, u8 y )
{
	GF_BGL_BmpWinSet_PosX( lw->hed.win, x );
	GF_BGL_BmpWinSet_PosY( lw->hed.win, y );
}


//--------------------------------------------------------------------------------------------
/**
 * �O���R���g���[���֐�(�`��E�R�[���o�b�N�w��)
 *
 * @param	lw			BMP���X�g���[�N
 * @param	lh			�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	print		�`��t���O
 * @param	direct		�w�����(�L�[��`)
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	BMPLIST_NULL	
 *
 * ���X�g�֐������삵�Ă��Ȃ��Ƃ��A�O������̎w��ɂ��
 * �J�[�\���ʒu�̕ϓ����`�F�b�N���A�w��o�b�N�A�b�v���[�N�ɕۑ�
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMainOutControlEx(
		BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
		u16 list_p, u16 cursor_p, u16 print, u16 direct, u16 * list_bak, u16 * cursor_bak )
{
    if( bmplist ){
		lw->hed = *bmplist;
	}
	lw->lp		= list_p;
	lw->cp		= cursor_p;
	lw->seq		= 0;
	lw->scrwork	= 0;

	if( direct == PAD_KEY_UP ){
		ListMoveUpDownCheck( lw, print, 1, LIST_UP );
	}else if( direct == PAD_KEY_DOWN ){
		ListMoveUpDownCheck( lw, print, 1, LIST_DOWN );
	}
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}

	return BMPLIST_NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �O���R���g���[���֐�(�J�[�\���ړ�����)
 *
 * @param	lw			BMP���X�g���[�N
 * @param	bmplist		�\�����X�g�w�b�_�|�C���^
 * @param	list_p		���X�g�����ʒu
 * @param	cursor_p	�J�[�\�������ʒu
 * @param	direct		�w�����(�L�[��`)
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	BMPLIST_NULL	
 *
 * ���X�g�֐������삵�Ă��Ȃ��Ƃ��A�O������̎w��ɂ��
 * �J�[�\���ʒu�̕ϓ����`�F�b�N���A�w��o�b�N�A�b�v���[�N�ɕۑ�
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMainOutControl(
		BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
		u16 list_p, u16 cursor_p, u16 direct, u16 * list_bak, u16 * cursor_bak )
{
	return BmpListMainOutControlEx(lw,bmplist,list_p,cursor_p,0,direct,list_bak,cursor_bak);
/*
    if(bmplist){
        lw->hed		= *bmplist;
    }
	lw->lp		= list_p;
	lw->cp		= cursor_p;
	lw->seq		= 0;
	lw->scrwork	= 0;

	if( direct == PAD_KEY_UP ){
		ListMoveUpDownCheck( lw, 0, 1, LIST_UP );
	}else if( direct == PAD_KEY_DOWN ){
		ListMoveUpDownCheck( lw, 0, 1, LIST_DOWN );
	}
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}

	return BMPLIST_NULL;
*/
}

//--------------------------------------------------------------------------------------------
/**
 * �����F�ꎞ�ύX
 *
 * @param	lw		BMP���X�g���[�N
 * @param	f_col	�����F
 * @param	b_col	�w�i�F
 * @param	s_col	�e�F
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListTmpColorChange( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col )
{
	lw->tmp.f_col = f_col;		// �����F�i���o�[
	lw->tmp.b_col = b_col;		// �w�i�F�i���o�[
	lw->tmp.s_col = s_col;		// �e�F�@�i���o�[
	lw->tmp.sw = 1;	
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̑S�̈ʒu���擾
 *
 * @param	lw			BMP���X�g���[�N
 * @param	pos_bak		�S�̃��X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListDirectPosGet( BMPLIST_WORK * lw, u16 * pos_bak )
{
	*pos_bak = (u16)(lw->lp + lw->cp);
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃��X�g�ʒu�A�J�[�\���ʒu���擾
 *
 * @param	lw			BMP���X�g���[�N
 * @param	list_bak	���X�g�ʒu�o�b�N�A�b�v���[�N�|�C���^
 * @param	cursor_bak	�J�[�\���ʒu�o�b�N�A�b�v���[�N�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListPosGet( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak )
{
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃J�[�\��Y���W���擾
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	�J�[�\��Y���W
 */
//--------------------------------------------------------------------------------------------
u16 BmpListCursorYGet( BMPLIST_WORK * lw )
{
	u8	yblk = FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;
	return  (u16)((lw->cp * yblk) + lw->hed.line_y);
}

//--------------------------------------------------------------------------------------------
/**
 * BMP���X�g�̃J�[�\���ړ������擾
 *
 * @param	lw		BMP���X�g���[�N
 *
 * @return	�J�[�\���ړ������擾
 */
//--------------------------------------------------------------------------------------------
u8 BmpListMoveSiteGet( BMPLIST_WORK * lw )
{
	return lw->work;
}

//--------------------------------------------------------------------------------------------
/**
 * �w��ʒu�̃p�����[�^�擾
 *
 * @param	lw		BMP���X�g���[�N
 * @param	pos		�ʒu
 *
 * @return	�p�����[�^
 */
//--------------------------------------------------------------------------------------------
u32 BmpListPosParamGet( BMPLIST_WORK * lw, u16 pos )
{
	return lw->hed.list[ pos ].param;
}

//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�擾�֐�
 *
 * @param	lw		BMP���X�g���[�N
 * @param	mode	�p�����[�^�擾�h�c
 *
 * @retval	"0xffffffff = �G���["
 * @retval	"0xffffffff != �p�����[�^"
 */
//--------------------------------------------------------------------------------------------
u32	BmpListParamGet( BMPLIST_WORK * lw, u8 mode )
{
	u32	ret;

	switch( mode ){
	case BMPLIST_ID_CALLBACK:	// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
		ret = (u32)lw->hed.call_back;
		break;
	case BMPLIST_ID_ICONFUNC:	// ���\�����Ƃ̃R�[���o�b�N�֐�
		ret = (u32)lw->hed.icon;
		break;
	case BMPLIST_ID_COUNT:		// ���X�g���ڐ�
		ret = (u32)lw->hed.count;
		break;
	case BMPLIST_ID_LINE:		// �\���ő區�ڐ�
		ret = (u32)lw->hed.line;
		break;
	case BMPLIST_ID_RABEL_X:	// ���x���\���w���W
		ret = (u32)lw->hed.rabel_x;
		break;
	case BMPLIST_ID_DATA_X:		// ���ڕ\���w���W
		ret = (u32)lw->hed.data_x;
		break;
	case BMPLIST_ID_CURSOR_X:	// �J�[�\���\���w���W
		ret = (u32)lw->hed.cursor_x;
		break;
	case BMPLIST_ID_LINE_Y:		// �\���x���W
		ret = (u32)lw->hed.line_y;
		break;
	case BMPLIST_ID_LINE_YBLK:		//�P�s���V�t�g�ʎ擾(�t�H���g�̑傫���{�x�Ԋu)
		ret = (u32)FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;
		break;
	case BMPLIST_ID_F_COL:		// �\�������F
		ret = (u32)lw->hed.f_col;
		break;
	case BMPLIST_ID_B_COL:		// �\���w�i�F
		ret = (u32)lw->hed.b_col;
		break;
	case BMPLIST_ID_S_COL:		// �\�������e�F
		ret = (u32)lw->hed.s_col;
		break;
	case BMPLIST_ID_MSG_SPC:	// �����Ԋu�w
		ret = (u32)lw->hed.msg_spc;
		break;
	case BMPLIST_ID_LINE_SPC:	// �����Ԋu�x
		ret = (u32)lw->hed.line_spc;
		break;
	case BMPLIST_ID_PAGE_SKIP:	// �y�[�W�X�L�b�v�^�C�v
		ret = (u32)lw->hed.page_skip;
		break;
	case BMPLIST_ID_FONT:		// �����w��
		ret = (u32)lw->hed.font;
		break;
	case BMPLIST_ID_C_DISP_F:	// �a�f�J�[�\��(allow)�\���t���O
		ret = (u32)lw->hed.c_disp_f;
		break;
	case BMPLIST_ID_WIN:		// �E�B���h�E�f�[�^
		ret = (u32)lw->hed.win;
		break;
	case BMPLIST_ID_WORK:		// ���[�N
		ret = (u32)lw->hed.work;
		break;

	default:
		ret = 0xffffffff;
	}
	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�ύX�֐�
 *
 * @param	lw		BMP���X�g���[�N
 * @param	mode	�p�����[�^�擾�h�c
 * @param	param	�ύX�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListParamSet( BMPLIST_WORK * lw, u8 mode, u32 param )
{
	switch( mode ){
	case BMPLIST_ID_CALLBACK:	// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
		lw->hed.call_back = (void *)param;
		break;
	case BMPLIST_ID_ICONFUNC:	// ���\�����Ƃ̃R�[���o�b�N�֐�
		lw->hed.icon = (void *)param;
		break;
	case BMPLIST_ID_COUNT:		// ���X�g���ڐ�
		lw->hed.count = (u16)param;
		break;
	case BMPLIST_ID_LINE:		// �\���ő區�ڐ�
		lw->hed.line = (u16)param;
		break;
	case BMPLIST_ID_RABEL_X:	// ���x���\���w���W
		lw->hed.rabel_x = (u8)param;
		break;
	case BMPLIST_ID_DATA_X:		// ���ڕ\���w���W
		lw->hed.data_x = (u8)param;
		break;
	case BMPLIST_ID_CURSOR_X:	// �J�[�\���\���w���W
		lw->hed.cursor_x = (u8)param;
		break;
	case BMPLIST_ID_LINE_Y:		// �\���x���W
		lw->hed.line_y = (u8)param;
		break;
	case BMPLIST_ID_F_COL:		// �\�������F
		lw->hed.f_col = (u8)param;
		break;
	case BMPLIST_ID_B_COL:		// �\���w�i�F
		lw->hed.b_col = (u8)param;
		break;
	case BMPLIST_ID_S_COL:		// �\�������e�F
		lw->hed.s_col = (u8)param;
		break;
	case BMPLIST_ID_MSG_SPC:	// �����Ԋu�w
		lw->hed.msg_spc = (u8)param;
		break;
	case BMPLIST_ID_LINE_SPC:	// �����Ԋu�x
		lw->hed.line_spc = (u8)param;
		break;
	case BMPLIST_ID_PAGE_SKIP:	// �y�[�W�X�L�b�v�^�C�v
		lw->hed.page_skip = (u8)param;
		break;
	case BMPLIST_ID_FONT:		// �����w��
		lw->hed.font = (u8)param;
		break;
	case BMPLIST_ID_C_DISP_F:	// �a�f�J�[�\��(allow)�\���t���O
		lw->hed.c_disp_f = (u8)param;
		break;
	case BMPLIST_ID_WIN:		// �E�B���h�E�f�[�^
		lw->hed.win = (GF_BGL_BMPWIN *)param;
		break;
	case BMPLIST_ID_WORK:		// ���[�N
		lw->hed.work = (void *)param;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP_MENULIST_DATA���ēx�ݒ肷��
 *
 * @param	BMP_MENULIST_DATA			BMPMENU���X�g�|�C���^
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListSetMenuListData(BMPLIST_WORK * lw, BMP_MENULIST_DATA* pList)
{
    lw->hed.list = pList;
}




/********************************************************************/
/*                                                                  */
/*                                                                  */
/*					���������֐�									*/
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include "gflib/strbuf.h"

//------------------------------------------------------------------
//		���b�Z�[�W�\��
//------------------------------------------------------------------
static void LocalMsgPrint( BMPLIST_WORK * lw, void * msg, u8 x, u8 y )
{
    if(msg==NULL){
        return;
    }
    
	if( lw->tmp.sw )					// �ꎞ�ύX�X�C�b�`
	{
		GF_STR_PrintExpand( lw->hed.win, lw->tmp.font, msg, x, y, MSG_NO_PUT, 
				GF_PRINTCOLOR_MAKE(lw->tmp.f_col, lw->tmp.s_col, lw->tmp.b_col),
				lw->tmp.msg_spc, 0, NULL );
	}
	else
	{
		GF_STR_PrintExpand( lw->hed.win, lw->hed.font, msg, x, y, MSG_NO_PUT, 
				GF_PRINTCOLOR_MAKE(lw->hed.f_col, lw->hed.s_col, lw->hed.b_col),
				lw->hed.msg_spc, 0, NULL );
	}
}


//------------------------------------------------------------------
//		���X�g�\��
//------------------------------------------------------------------
static void ListScreenPut( BMPLIST_WORK * lw, u16 print_p, u16 line, u16 len )
{
	int	i;
	u8	x,y,yblk;

	yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;

	for( i=0; i<len ;i++ ){
		if( lw->hed.list[print_p].param != BMPLIST_RABEL ){
			x = lw->hed.data_x;		// �`��w�I�t�Z�b�g
		}else{
			x = lw->hed.rabel_x;	// �`��w�I�t�Z�b�g
		}
		y = (u8)(((i + line) * yblk) + lw->hed.line_y);//�`��x�I�t�Z�b�g
		if( lw->hed.icon != NULL ){
			lw->hed.icon( lw, lw->hed.list[print_p].param,y );
		}
		LocalMsgPrint( lw, (void*)lw->hed.list[print_p].str, x, y );
		print_p++;
	}
}


//------------------------------------------------------------------
//		�J�[�\���\��
//static u8 ListCursorActorSet(BMPLIST_WORK* lw,int mode);
//------------------------------------------------------------------
static void ListCursorPut( BMPLIST_WORK * lw )
{
	u8	x,y,yblk;

	yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;
	x = lw->hed.cursor_x;	//�`��w�I�t�Z�b�g
	y = (u8)((lw->cp * yblk) + lw->hed.line_y);//�`��x�I�t�Z�b�g

	switch(lw->hed.c_disp_f){
	case 0:
		BMPCURSOR_Print( lw->cursor, lw->hed.win, x, y );
		break;
	case 1:
		break;
	case 2:
/*
		if(lw->cur_actID == 0xff){
			//������(�V�K�ݒ�)
			lw->cur_actID = ListCursorActorSet(lw,0);
		}
		CursorListActorPosSet(	lw->cur_actID,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_X) * 8 - 1,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_Y) * 8 + y - 1,
								0);
*/
		break;
	case 3:
/*
		if(lw->cur_actID == 0xff){
			//������(�V�K�ݒ�)
			lw->cur_actID = ListCursorActorSet(lw,1);
		}
		CursorListActorPosSet(	lw->cur_actID,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_X) * 8 + x,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_Y) * 8 + y,
								1);
*/
		break;
	}
}

/*
static u8 ListCursorActorSet(BMPLIST_WORK* lw,int mode)
{
	ACT_CURSORLIST_HEADER header;

	header.x		= 0;		//�\���ʒu�w
	header.y		= 160;		//�\���ʒu�x
	header.xsize	= BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_SIZ_X) * 8 + 2;	//�\���T�C�Y�w
	header.ysize	= FontHeaderGet(lw->lh.font,FONT_HEADER_SIZE_Y) + 2;		//�\���T�C�Y�x
	header.cellID	= 0x4000;		//�J�[�\���Z���h�c
	header.palID	= ACT_OAMPAL;	//�J�[�\���p���b�g�h�c
	header.palnum	= 15;			//�J�[�\���p���b�g�w��̏ꍇ�Ɏg�p

	return CursorListActorSet(&header,mode);

	return 0;
}
*/

//------------------------------------------------------------------
//		�J�[�\������
//------------------------------------------------------------------
static void ListCursorCls( BMPLIST_WORK * lw, u16 p )
{
	u8	yblk;

	switch(lw->hed.c_disp_f){
	case 0:
		yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;

		GF_BGL_BmpWinFill(
				lw->hed.win,						//�\���E�C���h�EINDEX
				(u8)lw->hed.b_col,					//�w�i�F�f�[�^
				lw->hed.cursor_x,					//�w���W
				(u16)(p * yblk + lw->hed.line_y),	//�x���W
				8, 16 );
		break;
	case 1:
	case 2:
	case 3:
		break;
	}
}

//------------------------------------------------------------------
//		�J�[�\���ړ�
//------------------------------------------------------------------
static u8 ListCursorMoveUpDown( BMPLIST_WORK * lw, u8 mode )
{
	u16	list_p,cursor_p,check_p;

	cursor_p	= lw->cp;
	list_p		= lw->lp;

	if(mode == LIST_UP){

		//�X�N���[������n�_(���X�g�̔������߂�����)
		if(lw->hed.line == 1){
			check_p = 0;
		}else{
			check_p = (u16)(lw->hed.line - ((lw->hed.line / 2) + (lw->hed.line % 2)) - 1);
/*
			if( ( lw->hed.line & 1 ) != 0 ){
				check_p = (u16)((lw->hed.line / 2));
			}else{
				check_p = (u16)(lw->hed.line - ((lw->hed.line / 2) + (lw->hed.line % 2)) - 1);
			}
*/
		}

		if(list_p == 0){	//���X�g�ŏ��̕���
			while(cursor_p > 0){
				cursor_p--;
				if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
					lw->cp = cursor_p;
					return 1;
				}
			}
			return 0;
		}
		while(cursor_p > check_p){
			cursor_p--;
			if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
				lw->cp = cursor_p;
				return 1;
			}
		}
		list_p--;
		lw->cp = check_p;
		lw->lp = list_p;

	}else{

		//�X�N���[������n�_(���X�g�̔������߂�����)
		if(lw->hed.line == 1){
			check_p = 0;
		}else{
			check_p = (u16)((lw->hed.line / 2) + (lw->hed.line % 2));
/*
			if( ( lw->hed.line & 1 ) != 0 ){
				check_p = (u16)((lw->hed.line / 2));
			}else{
				check_p = (u16)((lw->hed.line / 2) + (lw->hed.line % 2));
			}
*/
		}

		if(list_p == (lw->hed.count - lw->hed.line)){//���X�g�Ō�̕���
			while(cursor_p < (lw->hed.line - 1)){
				cursor_p++;
				if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
					lw->cp = cursor_p;
					return 1;
				}
			}
			return 0;
		}
		while(cursor_p < check_p){
			cursor_p++;
			if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
				lw->cp = cursor_p;
				return 1;
			}
		}
		list_p++;
		lw->cp = check_p;
		lw->lp = list_p;

	}

	return 2;
}

//------------------------------------------------------------------
//		��ʃX�N���[���ړ�
//------------------------------------------------------------------
static void ListScrollMoveUpDown( BMPLIST_WORK * lw, u8 len, u8 mode )
{
	u8	yblk;
	u16	ypos;

	if( len >= lw->hed.line ){
		GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );
		ListScreenPut( lw, lw->lp, 0, lw->hed.line );	//���C���`��
		return;
	}
	//�P�s���V�t�g�ʎ擾(�t�H���g�̑傫���{�x�Ԋu)
	yblk = FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;

	if( mode == LIST_UP ){
		//�f�[�^�V�t�g
		GF_BGL_BmpWinShift(
			lw->hed.win, GF_BGL_BMPWIN_SHIFT_D,
			(u8)(len * yblk), (u8)((lw->hed.b_col<<4)|lw->hed.b_col) );

		ListScreenPut( lw, lw->lp, 0, len );	//�ǉ����C���`��

		ypos = (u16)( lw->hed.line * yblk + lw->hed.line_y );

		//����������
		GF_BGL_BmpWinFill(
			lw->hed.win,					//�\���E�C���h�EINDEX
			(u8)lw->hed.b_col,				//�w�i�F�f�[�^
			0, ypos,
			(u16)(GF_BGL_BmpWinGet_SizeX( lw->hed.win ) * 8),
			(u16)(GF_BGL_BmpWinGet_SizeY( lw->hed.win ) * 8 - ypos) );

	}else{
		//�f�[�^�V�t�g
		GF_BGL_BmpWinShift(
				lw->hed.win, GF_BGL_BMPWIN_SHIFT_U,
				(u8)(len * yblk), (u8)((lw->hed.b_col<<4)|lw->hed.b_col) );
		//�ǉ����C���`��
		ListScreenPut(
			lw, (u16)(lw->lp + (lw->hed.line-len)), (u16)(lw->hed.line - len), (u16)len );
		//�㕔������
		GF_BGL_BmpWinFill(
			lw->hed.win,
			(u8)lw->hed.b_col,				//�w�i�F�f�[�^
			0, 0,
			(u16)(GF_BGL_BmpWinGet_SizeX( lw->hed.win ) * 8),
			(u16)lw->hed.line_y );
	}
}



//------------------------------------------------------------------
//		���X�g�ړ�����
//------------------------------------------------------------------
static u8 ListMoveUpDownCheck( BMPLIST_WORK * lw, u8 print_f, u8 req_line, u8 mode )
{
	u16	cursor_bak;	//�����J�[�\���ʒu
	u8	write_flg,write_req;	//�]���t���O
	u8	reqcount,linecount;		//�����J�E���g

	cursor_bak	= lw->cp;	//�J�[�\���ʒu�ۑ�
	linecount = 0;
	write_req = 0;

	for(reqcount=0;reqcount<req_line;reqcount++){
		do{
			write_flg = ListCursorMoveUpDown( lw, mode );	//�ړ�����
			write_req |= write_flg;
			if(write_flg != 2){
				break;
			}
			linecount++;
		//�J�[�\���ʒu�����x���ɂ�����Ȃ��Ȃ�܂ňړ�
		}while(lw->hed.list[lw->lp + lw->cp].param == BMPLIST_RABEL);
	}

	if(print_f){	//�\���X�C�b�`
		//�L�����f�[�^�쐬
		switch(write_req){
		//�ړ��s��
		default:
		case 0:
			return 1;
			break;
		//�J�[�\���݈̂ړ�
		case 1:
			ListCursorCls( lw, cursor_bak );
			ListCursorPut( lw );
			CallBackSet( lw, 0 );
			GF_BGL_BmpWinOn( lw->hed.win );
			break;
		//�\�����X�g�ړ� or ���X�g�{�J�[�\���ړ�
		case 2:
		case 3:
			ListCursorCls( lw, cursor_bak );
			ListScrollMoveUpDown( lw, linecount, mode );
			ListCursorPut( lw );
			CallBackSet( lw, 0 );
			GF_BGL_BmpWinOn( lw->hed.win );
			break;
		}
	}

	return 0;
}



//------------------------------------------------------------------
//		�R�[���o�b�N�֐��Ăяo��(�������� mode = 1,�ʏ퓮�쎞 mode = 0)
//------------------------------------------------------------------
static void CallBackSet( BMPLIST_WORK * lw, u8 mode )
{
	if( lw->hed.call_back != NULL){
		lw->hed.call_back( lw, lw->hed.list[lw->lp + lw->cp].param, mode );
	}
}



