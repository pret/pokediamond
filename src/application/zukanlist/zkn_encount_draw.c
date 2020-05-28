//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_encount_draw.c
 *	@brief		�G���J�E���g�f�[�^�`��V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.02.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "bg_system.h"

#define __ZKN_ENCOUNT_DRAW_H_GLOBAL
#include "include/application/zukanlist/zkn_encount_draw.h"

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
#define GRID_MUDDY_MUSK_NONE	( 0 )
#define GRID_MUDDY_MUSK_U		( 1<<0 )	// 1
#define GRID_MUDDY_MUSK_D		( 1<<1 )	// 2
#define GRID_MUDDY_MUSK_L		( 1<<2 )	// 4
#define GRID_MUDDY_MUSK_R		( 1<<3 )	// 8
#define GRID_MUDDY_MUSK_UL		( 1<<4 )	// 10
#define GRID_MUDDY_MUSK_UR		( 1<<5 )	// 20
#define GRID_MUDDY_MUSK_DL		( 1<<6 )	// 40
#define GRID_MUDDY_MUSK_DR		( 1<<7 )	// 80

#define 	GRIDCHK_MUDDY_MUSK_U			( GRID_MUDDY_MUSK_U )
#define 	GRIDCHK_MUDDY_MUSK_D			( GRID_MUDDY_MUSK_D )
#define 	GRIDCHK_MUDDY_MUSK_L			( GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_R			( GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UD			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D )
#define 	GRIDCHK_MUDDY_MUSK_UL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_UR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_DL			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_DR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_LR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UDL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_UDR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_ULR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_DLR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UDLR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_TUL			( GRID_MUDDY_MUSK_UL )
#define 	GRIDCHK_MUDDY_MUSK_TUR			( GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_TDL			( GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TDR			( GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTUR		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_TULTDL		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TULTDR		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TURTDL		( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TURTDR		( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TDLTDR		( GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDL	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTDLTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TURTDLTDR	( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDLTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_UTDLTDR		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_DTULTUR		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_LTURTDR		( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_RTULTDL		( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_ULTDR		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_URTDL		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_DLTUR		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_DRTUL		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_UTDL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DL )
#define		GRIDCHK_MUDDY_MUSK_UTDR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DR )
#define		GRIDCHK_MUDDY_MUSK_DTUL			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_DTUR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UR )
#define		GRIDCHK_MUDDY_MUSK_LTUR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR )
#define		GRIDCHK_MUDDY_MUSK_LTDR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_DR )
#define		GRIDCHK_MUDDY_MUSK_RTUL			( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_RTDL			( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_DL )







//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void PrintMain( GF_BGL_BMPWIN* win, u8* char_buff, u16 char_sizex, u16 char_sizey, int grid_size, int chip_no, u8 win_x, u8 win_y );

static void MuddyMain( u8* p_buff, int x, int y, int size_x, int size_y );

static int GetGridChipData( u8* p_buff, int x, int y, int size_x, int size_y );

static void GetGrid8Data( u8* p_buff, int* p_mask8, int x, int y, int size_x, int size_y );
static int GetMuddyChip( int mask8 );

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�f�[�^�쐬
 *
 *	@param	win				�r�b�g�}�b�v�E�B���h�E
 *	@param	char_buff		�L�����N�^�o�b�t�@
 *	@param	char_size_x		�L�����N�^�T�C�Y��
 *	@param	char_size_y		�L�����N�^�T�C�Y��
 *	@param	grid_size		1�O���b�h�s�N�Z���T�C�Y
 *	@param	p_buff			�O���t�B�b�N�o�b�t�@
 *	@param	size_x			�o�b�t�@���T�C�Y
 *	@param	size_y			�o�b�t�@�c�T�C�Y
 *	@param	win_x			bitmap�E�B���h�E�ɏ������ލ��W��
 *	@param	win_y			bitmap�E�B���h�E�ɏ������ލ��W��
 *	@param	win_size_x		bitmap�E�B���h�E�̃T�C�Y��
 *	@param	win_size_y		bitmap�E�B���h�E�̃T�C�Y��
 *
 *	@return	none
 *
 *	�T�C�Y�͑S���s�N�Z��
 */
//-----------------------------------------------------------------------------
void ZKN_ENCOUNTDRAW_PrintChar( GF_BGL_BMPWIN * win, u8* char_buff, u16 char_sizex, u16 char_sizey, u8 grid_size, u8* p_buff, u8 size_x, u8 size_y, u16 win_x, u16 win_y )
{
	int i, j;


	// �`�b�v�f�[�^��������
	for( i=0; i<size_y; i++ ){

		for( j=0; j<size_x; j++ ){

			// ��������
			PrintMain( win, char_buff,	
					char_sizex, char_sizey,
					grid_size, p_buff[ (i*size_y)+j ],	// chipdata
					win_x + (j * grid_size),
					win_y + (i * grid_size) );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���b�h�f�[�^�̊��炩�O���t�B�b�N�쐬
 *
 *	@param	p_buff	�o�b�t�@
 *	@param	size_x	�o�b�t�@�T�C�Y��
 *	@param	size_y	�o�b�t�@�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ENCOUNTDRAW_MakeMuddyData( u8* p_buff, u8 size_x, u8 size_y )
{
	int i,j;
	
	for( i=0; i<size_y; i++ ){

		for( j=0; j<size_x; j++ ){
			MuddyMain( p_buff, j, i, size_x, size_y );
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�E�ւ̏������݃��C��
 *
 *	@param	win			bmp�E�B���h�E
 *	@param	char_buff	�L�����N�^�o�b�t�@
 *	@param	char_sizex	�L�����N�^�T�C�Y��
 *	@param	char_sizey	�L�����N�^�T�C�Y��
 *	@param	grid_size	�O���b�h�T�C�Y
 *	@param	chip_no		�`�b�v�i���o�[
 *	@param	win_x		�E�B���h�E�������ݍ��W��
 *	@param	win_y		�E�B���h�E�������ݍ��W��
 *	@param	win_size_x	�E�B���h�E�T�C�Y��
 *	@param	win_size_y	�E�B���h�E�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PrintMain( GF_BGL_BMPWIN* win, u8* char_buff, u16 char_sizex, u16 char_sizey, int grid_size, int chip_no, u8 win_x, u8 win_y )
{
	int chip_x;
	int chip_y;

	if( chip_no != ZKN_ENCOUNT_DRAW_MUDDY_NONE ){
		
		chip_x = chip_no * grid_size;
		chip_y = chip_x / char_sizex;
		chip_x = chip_x % char_sizex;

		GF_BGL_BmpWinPrint( win, char_buff,
				chip_x, chip_y, char_sizex, char_sizey,
				win_x, win_y, grid_size, grid_size );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O���b�h�f�[�^�Ɋۂߍ��݃O���t�B�b�N�i���o�[��ݒ�
 *
 *	@param	p_buff		�O���b�h�o�b�t�@
 *	@param	x			�`�F�b�N�����W
 *	@param	y			�`�F�b�N�����W
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MuddyMain( u8* p_buff, int x, int y, int size_x, int size_y )
{
	int mask8;
	int chip_no;
	
	// ���g���J���Ȃ�`�F�b�N
	if( p_buff[ (y * size_x) + x ] == ZKN_ENCOUNT_DRAW_MUDDY_NONE ){
		
		// �W�����`�b�v�f�[�^�擾
		GetGrid8Data( p_buff, &mask8, x, y, size_x, size_y );

		// �ۂߍ��݃`�b�v�i���o�[�擾
		chip_no = GetMuddyChip( mask8 );

		// �i�[
		p_buff[ (y * size_x) + x ] = chip_no;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O���b�h�̃`�b�v�f�[�^���擾
 *
 *	@param	p_buff	�o�b�t�@
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	�`�b�v�f�[�^	�Ȃ��Ƃ� -1
 */
//-----------------------------------------------------------------------------
static int GetGridChipData( u8* p_buff, int x, int y, int size_x, int size_y )
{
	if( (x < 0) || (x >= size_x) ){
		return -1;
	}
	if( (y < 0) || (y >= size_y) ){
		return -1;
	}

	return  p_buff[ (y*size_x) + x ];
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	xy�𒆐S�ɂ������̂W�_�f�[�^�擾
 *
 *	@param	p_buff		�o�b�t�@
 *	@param	p_8buff		�W�_�f�[�^�擾�o�b�t�@
 *	@param	x			�o�b�t�@�����W
 *	@param	y			�o�b�t�@�����W
 *	@param	size_x		�o�b�t�@�T�C�Y��
 *	@param	size_y		�o�b�t�@�T�C�Y��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void GetGrid8Data( u8* p_buff, int* p_mask8, int x, int y, int size_x, int size_y )
{
	int chip_data;


	*p_mask8 = 0;
	
	// �W�����̓_������
	// ��
	if( GetGridChipData( p_buff, x, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_U;
	}
	// ��
	if( GetGridChipData( p_buff, x, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_D;
	}
	// ��
	if( GetGridChipData( p_buff, x - 1, y, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_L;
	}
	// �E
	if( GetGridChipData( p_buff, x + 1, y, size_x,  size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_R;
	}

	// �΂߂͗��e�������Ƃ������`�F�b�N����
	// ����
	if( (((*p_mask8) & GRID_MUDDY_MUSK_U) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_L) == 0) ){
		if( GetGridChipData( p_buff, x - 1, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_UL;
		}
	}

	// �E��
	if( (((*p_mask8) & GRID_MUDDY_MUSK_U) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_R) == 0) ){
		if( GetGridChipData( p_buff, x + 1, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_UR;
		}
	}
	// ����
	if( (((*p_mask8) & GRID_MUDDY_MUSK_D) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_L) == 0) ){
		if( GetGridChipData( p_buff, x - 1, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_DL;
		}
	}
	// �E��
	if( (((*p_mask8) & GRID_MUDDY_MUSK_D) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_R) == 0) ){
		if( GetGridChipData( p_buff, x + 1, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_DR;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ۂߍ��݃`�b�v�f�[�^�쐬
 *
 *	@param	p_8buff		�W�����`�b�v�f�[�^
 *
 *	@return	�ۂߍ��݃f�[�^
 */
//-----------------------------------------------------------------------------
static int GetMuddyChip( int mask8 )
{
	int ret;
	
	switch( mask8 ){
	case 0:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_NONE;
		break;
	case GRIDCHK_MUDDY_MUSK_U:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_U;
		break;
	case GRIDCHK_MUDDY_MUSK_D:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_D;
		break;
	case GRIDCHK_MUDDY_MUSK_L:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_L;
		break;
	case GRIDCHK_MUDDY_MUSK_R:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_R;
		break;
	case GRIDCHK_MUDDY_MUSK_UD:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UD;
		break;
	case GRIDCHK_MUDDY_MUSK_UL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UL;
		break;
	case GRIDCHK_MUDDY_MUSK_UR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UR;
		break;
	case GRIDCHK_MUDDY_MUSK_DL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DL;
		break;
	case GRIDCHK_MUDDY_MUSK_DR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DR;
		break;
	case GRIDCHK_MUDDY_MUSK_LR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LR;
		break;
	case GRIDCHK_MUDDY_MUSK_UDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDL;
		break;
	case GRIDCHK_MUDDY_MUSK_UDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDR;
		break;
	case GRIDCHK_MUDDY_MUSK_ULR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_ULR;
		break;
	case GRIDCHK_MUDDY_MUSK_DLR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DLR;
		break;
	case GRIDCHK_MUDDY_MUSK_UDLR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDLR;
		break;
	case GRIDCHK_MUDDY_MUSK_TUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TUL;
		break;
	case GRIDCHK_MUDDY_MUSK_TUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TUR;
		break;
	case GRIDCHK_MUDDY_MUSK_TDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_DTULTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTULTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_RTULTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTULTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_ULTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_ULTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_URTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_URTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_DLTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DLTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_DRTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DRTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_DTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_DTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_RTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_RTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTDL;
		break;

	default:
		// ��������
		GF_ASSERT_MSG( 0, "%x", mask8 );
		break;
	}

	return ret;
}

