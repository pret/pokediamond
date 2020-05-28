//============================================================================================
/**
 * @file	board.c
 * @brief	�Ŕ���
 * @author	Hiroyuki Nakamura
 * @date	2005.10.25
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "talk_msg.h"

#include "system/window.h"

#define	BOARD_H_GLOBAL
#include "board.h"


//============================================================================================
//	�萔��`
//============================================================================================
/// �Ŕ��[�N
struct _BOARD_WORK {
	GF_BGL_BMPWIN	win;	// BMP�E�B���h�E
	u16	map;				// �}�b�vID�i�O���t�B�b�NID�j
	u8	type;				// �Ŕ^�C�v
	u8	req:7;				// ���N�G�X�g
	u8	flg:1;				// �쐬�t���O
};

#define	BOARD_INIT_SCROLL_Y	( -48 )		///< �쐬����̏���Y�X�N���[���l
#define	BOARD_SCROLL_VAL	( 16 )		///< 1sync �̃X�N���[���l
#define	BOARD_WIN_PX		( 0 )		///< �E�B���h�E�`��X���W
#define	BOARD_WIN_PY		( 18 )		///< �E�B���h�E�`��Y���W
#define	BOARD_WIN_SX		( 32 )		///< �E�B���h�EX�T�C�Y
#define	BOARD_WIN_SY		( 6 )		///< �E�B���h�EY�T�C�Y


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BoardMake( FIELDSYS_WORK * repw );
static void BoardDelete( FIELDSYS_WORK * repw );
static BOOL BoarsScroll_Up( FIELDSYS_WORK * repw );
static BOOL BoarsScroll_Down( FIELDSYS_WORK * repw );


//--------------------------------------------------------------------------------------------
/**
 * �Ŕ��[�N�m��
 *
 * @param	heap	�q�[�vID
 *
 * @return	�m�ۂ������[�N
 */
//--------------------------------------------------------------------------------------------
void * BoardWorkAlloc( u32 heap )
{
	void * buf = sys_AllocMemory( heap, sizeof(BOARD_WORK) );
	memset( buf, 0, sizeof(BOARD_WORK) );
	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ��[�N���
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardWorkDelete( BOARD_WORK * wk )
{
	if( wk->flg != 0 ){
		GF_BGL_BmpWinDel( &wk->win );
	}
	sys_FreeMemoryEz( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕf�[�^�Z�b�g
 *
 * @param	wk		���[�N
 * @param	type	�Ŕ^�C�v
 * @param	map		�}�b�vID�i�O���t�B�b�NID�j
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardDataSet( BOARD_WORK * wk, u16 type, u16 map )
{
	wk->type = type;
	wk->map  = map;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ��N�G�X�g���s
 *
 * @param	wk		���[�N
 * @param	req		���N�G�X�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardSetRequest( BOARD_WORK * wk, u8 req )
{
	wk->req = req;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�FBMP�E�B���h�E�f�[�^
 *
 * @param	wk		���[�N
 *
 * @return	BMP�E�B���h�E�f�[�^
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * BoardWinGet( BOARD_WORK * wk )
{
	return &wk->win;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�[�^�擾�F�Ŕ^�C�v
 *
 * @param	wk		���[�N
 *
 * @return	�Ŕ^�C�v
 */
//--------------------------------------------------------------------------------------------
u8 BoardTypeGet( BOARD_WORK * wk )
{
	return wk->type;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ����I���`�F�b�N
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �I��"
 * @retval	"FALSE = ���쒆"
 */
//--------------------------------------------------------------------------------------------
BOOL BoardReqEndCheck( BOARD_WORK * wk )
{
	if( wk->req == BOARD_REQ_WAIT ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ��C������
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardMain( FIELDSYS_WORK * repw )
{
	BOARD_WORK * wk = repw->board;

	switch( wk->req ){
	case BOARD_REQ_WAIT:	// �ҋ@
		break;

	case BOARD_REQ_ADD:		// �ŔE�B���h�E�쐬
		BoardMake( repw );
		wk->req = BOARD_REQ_WAIT;
		break;

	case BOARD_REQ_DOWN:	// �ŔE�B���h�E��������
		if( BoarsScroll_Down( repw ) == 1 ){
			wk->req = BOARD_REQ_WAIT;
		}
		break;

	case BOARD_REQ_UP:		// �ŔE�B���h�E���グ��
		if( BoarsScroll_Up( repw ) == 1 ){
			wk->req = BOARD_REQ_WAIT;
		}
		break;

	case BOARD_REQ_DEL:		// �ŔE�B���h�E�j��
		BoardDelete( repw );
		wk->req = BOARD_REQ_WAIT;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���N�G�X�g�𑦎��s
 *
 * @param	repw	�t�B�[���h���[�N
 * @param	req		���N�G�X�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardSetDirect( FIELDSYS_WORK * repw, u8 req )
{
	BoardSetRequest( repw->board, req );
	BoardMain( repw );
}


//--------------------------------------------------------------------------------------------
/**
 * �Ŕ쐬
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardMake( FIELDSYS_WORK * repw )
{
	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, BOARD_INIT_SCROLL_Y );

	// �Ŕ��쐬
	if( repw->board->flg == 0 ){
		FldBoardBmpAdd( repw->bgl, &repw->board->win, repw->board->type, FLD_MBGFRM_FONT );
		repw->board->flg = 1;
	}
	FldBoardWinPut( &repw->board->win, repw->board->type, repw->board->map );
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ폜
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardDelete( FIELDSYS_WORK * repw )
{
	if( repw->board->flg == 0 ){ return; }	// �Ŕ��쐬

	GF_BGL_BmpWinDel( &repw->board->win );
	GF_BGL_ScrFill(
		repw->bgl, FLD_MBGFRM_FONT, 0,
		BOARD_WIN_PX, BOARD_WIN_PY, BOARD_WIN_SX, BOARD_WIN_SY, GF_BGL_SCRWRT_PALNL );
	GF_BGL_LoadScreenReq( repw->bgl, FLD_MBGFRM_FONT );
	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );

	repw->board->flg = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �ŔX�N���[���C��
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @retval	"1 = �I��"
 * @retval	"0 = �X�N���[����"
 */
//--------------------------------------------------------------------------------------------
static BOOL BoarsScroll_Up( FIELDSYS_WORK * repw )
{
	int	scroll = GF_BGL_ScrollGetY( repw->bgl, FLD_MBGFRM_FONT );

	if( scroll == 0 ){ return 1; }

	if( !( scroll > BOARD_INIT_SCROLL_Y && scroll < 0 ) ){
		GF_BGL_ScrollSet(
			repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, BOARD_INIT_SCROLL_Y );
	}

	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_INC, BOARD_SCROLL_VAL );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �ŔX�N���[���A�E�g
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @retval	"1 = �I��"
 * @retval	"0 = �X�N���[����"
 */
//--------------------------------------------------------------------------------------------
static BOOL BoarsScroll_Down( FIELDSYS_WORK * repw )
{
	int	scroll = GF_BGL_ScrollGetY( repw->bgl, FLD_MBGFRM_FONT );

	if( scroll == BOARD_INIT_SCROLL_Y ){
		GF_BGL_ScrFill(
			repw->bgl, FLD_MBGFRM_FONT, 0,
			BOARD_WIN_PX, BOARD_WIN_PY, BOARD_WIN_SX, BOARD_WIN_SY, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( repw->bgl, FLD_MBGFRM_FONT );
		GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );
		return 1;
	}

	if( !( scroll > BOARD_INIT_SCROLL_Y && scroll < 0 ) ){
		GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );
	}

	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_DEC, BOARD_SCROLL_VAL );

	return 0;
}
