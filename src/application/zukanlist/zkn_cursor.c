//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_cursor.c
 *	@brief		�}��cursor����V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "include/gflib/system.h"
#include "include/gflib/assert.h"
#include <string.h>

#define	__ZKN_CURSOR_H_GLOBAL
#include "include/application/zukanlist/zkn_cursor.h"

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

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	cursor�V�X�e��
//=====================================
typedef struct _ZKN_CURSOR {
	const ZKN_CURSOR_ONEDATA* p_data;
	int max_x;
	int max_y;
	int now_x;
	int now_y;
} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static int inline GetNowIdx( const ZKN_CURSOR* cp_cursor );
static int inline GetIdx( const ZKN_CURSOR* cp_cursor, int x, int y );
static void MoveXCursor( ZKN_CURSOR* p_cursor, int param );
static void MoveYCursor( ZKN_CURSOR* p_cursor, int param );

static void ZknCursorContAddX( ZKN_CURSOR* p_cursor, int param );
static void ZknCursorContAddY( ZKN_CURSOR* p_cursor, int param );
static void inline ZknCursorContSetX( ZKN_CURSOR* p_cursor, int param );
static void inline ZknCursorContSetY( ZKN_CURSOR* p_cursor, int param );
static void ZknCursorContSetContID( ZKN_CURSOR* p_cursor, int param );

//----------------------------------------------------------------------------
/**
 *	@brief	�}��CURSOR�V�X�e�����[�N�m��
 *
 *	@param	heap	�q�[�v
 *
 *	@return	CURSOR�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
ZKN_CURSOR* ZKN_CURSOR_Alloc( int heap )
{
	ZKN_CURSOR* p_cursor;

	p_cursor = sys_AllocMemory( heap, sizeof(ZKN_CURSOR) );
	memset( p_cursor, 0, sizeof(ZKN_CURSOR) );

	return p_cursor;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��CURSOR�V�X�e�����[�N�j��
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Free( ZKN_CURSOR* p_cursor )
{
	sys_FreeMemoryEz( p_cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��CURSOR�V�X�e��������
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	cp_data		CURSOR�f�[�^
 *	@param	max_x		X�����f�[�^��
 *	@param	max_y		Y�����f�[�^��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Init( ZKN_CURSOR* p_cursor, const ZKN_CURSOR_ONEDATA* cp_data, int max_x, int max_y )
{
	memset( p_cursor, 0, sizeof(ZKN_CURSOR) );
	p_cursor->p_data = cp_data;
	p_cursor->max_x = max_x;
	p_cursor->max_y	= max_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��CURSOR�V�X�e���R���g���[��
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	cont		����R�}���h
 *	@param	param		����l
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_Cont( ZKN_CURSOR* p_cursor, int cont, int param )
{
	int i;
	
	switch( cont ){
	case ZKN_CURSOR_CONT_ADD_X:		// X�����ړ�	
		ZknCursorContAddX( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_ADD_Y:		// Y�����ړ�	
		ZknCursorContAddY( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_X:		// X�����ݒ�	
		ZknCursorContSetX( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_Y:		// Y�����ݒ�	
		ZknCursorContSetY( p_cursor, param );
		break;
		
	case ZKN_CURSOR_CONT_SET_CONTID:	// �Ǘ�ID�̈ʒu�ɃJ�[�\�����ړ�
		ZknCursorContSetContID( p_cursor, param );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂���ʒu�̊Ǘ�ID���擾
 *
 *	@param	cp_cursor	CURSOR�V�X�e�����[�N
 *
 *	@return	�Ǘ�ID
 */
//-----------------------------------------------------------------------------
int ZKN_CURSOR_GetContID( const ZKN_CURSOR* cp_cursor )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	return cp_cursor->p_data[ now_idx ].cont_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����CURSOR�ʒu�̍��W���擾
 *
 *	@param	cp_cursor	CURSOR�V�X�e�����[�N
 *	@param	p_x			X���W�i�[��
 *	@param	p_y			Y���W�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetMat( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	
	*p_x = cp_cursor->p_data[ now_idx ].x;
	*p_y = cp_cursor->p_data[ now_idx ].y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����CURSOR�ʒu�̗̈�T�C�Y���擾
 *
 *	@param	cp_cursor	CURSOR�V�X�e�����[�N
 *	@param	p_x			X�T�C�Y�i�[��
 *	@param	p_y			Y�T�C�Y�i�[��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetSize( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y )
{
	int now_idx;
	
	now_idx = GetNowIdx( cp_cursor );
	
	*p_x = cp_cursor->p_data[ now_idx ].size_x;
	*p_y = cp_cursor->p_data[ now_idx ].size_y;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���P�f�[�^�̓��e���i�[
 *
 *	@param	p_data		�i�[��
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	size_x		���T�C�Y
 *	@param	size_y		���T�C�Y
 *	@param	movex_id	X��������ID
 *	@param	movey_id	Y��������ID
 *	@param	cont_id		���[�U�[�Ǘ�ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_SetOneData( ZKN_CURSOR_ONEDATA* p_data, int x, int y, int size_x, int size_y, int movex_id, int movey_id, int cont_id )
{
	p_data->x = x;
	p_data->y = y;
	p_data->size_x = size_x;
	p_data->size_y = size_y;
	p_data->movex_id = movex_id;
	p_data->movey_id = movey_id;
	p_data->cont_id  = cont_id;
}


//----------------------------------------------------------------------------
/**
 *	@brief	4���̍��W���擾
 *
 *	@param	cp_cursor	�J�[�\���V�X�e�����[�N
 *	@param	way			�ʒu 
 *	@param	p_x			�����W�i�[��
 *	@param	p_y			�����W�i�[��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_GetRectMat( const ZKN_CURSOR* cp_cursor, int way, int* p_x, int* p_y )
{
	int x, y;
	int size_x, size_y;

	// ���W�̎擾
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );

	// �T�C�Y�̎擾
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );

	// ���W�����߂�
	ZKN_CURSOR_UTIL_GetRectMat( way, p_x, p_y, x, y, size_x, size_y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�T�C�Y�ƒ��S���W����e�ʒu�̍��W���擾
 *
 *	@param	way			����
 *	@param	p_x			X���W�i�[��
 *	@param	p_y			Y���W�i�[��
 *	@param	def_x		���SX
 *	@param	def_y		���SY
 *	@param	size_x		�T�C�YX
 *	@param	size_y		�T�C�YY
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_CURSOR_UTIL_GetRectMat( int way, int* p_x, int* p_y, int def_x, int def_y, int size_x, int size_y )
{
	// X���W�ݒ�
	if( (way == ZKN_CURSOR_MAT_TOP_LEFT) ||
		(way == ZKN_CURSOR_MAT_BOTTOM_LEFT) ){
		def_x -= size_x / 2;	
	}else{
		def_x += size_x / 2;	
	}
	
	// Y���W�ݒ�
	if( (way == ZKN_CURSOR_MAT_TOP_LEFT) ||
		(way == ZKN_CURSOR_MAT_TOP_RIGHT) ){
		def_y -= size_y / 2;	
	}else{
		def_y += size_y / 2;	
	}

	*p_x = def_x;
	*p_y = def_y;
}


//-----------------------------------------------------------------------------
/**
 *				�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���̃f�[�^�z��v�f�����擾
 *
 *	@param	cp_cursor	CURSOR�V�X�e�����[�N
 *
 *	@return	�z��v�f��
 */
//-----------------------------------------------------------------------------
static int inline GetNowIdx( const ZKN_CURSOR* cp_cursor )
{
	int now_idx;
	
	now_idx = cp_cursor->now_y * cp_cursor->max_x;
	now_idx += cp_cursor->now_x;

	return now_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃f�[�^�z��v�f�����擾
 *
 *	@param	cp_cursor	CURSOR�V�X�e�����[�N
 *	@param	x			�擾������X
 *	@param	y			�擾������Y
 *
 *	�ő�T�C�Y��cp_cursor�̂��̂��g�p����
 *
 *	@return	�z��v�f��
 */
//-----------------------------------------------------------------------------
static int inline GetIdx( const ZKN_CURSOR* cp_cursor, int x, int y )
{
	int now_idx;
	
	now_idx = y * cp_cursor->max_x;
	now_idx += x;

	return now_idx;
}


//----------------------------------------------------------------------------
/**
 *	@brief	X������CURSOR�𓮂���
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	param		�������l	(-1 or 1)
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MoveXCursor( ZKN_CURSOR* p_cursor, int param )
{
	int move_x;
	const ZKN_CURSOR_ONEDATA* p_data;
	int data_idx;
	int move_param;

	GF_ASSERT( (param == -1) || (param == 1) );
	
	move_param = 0;

	// �ݒ���W�����߂�
	do{
		// �ړ�������l���v�Z
		move_param += param;
		move_x = p_cursor->now_x + move_param;

		// ���ő吔OR�Œᐔ�����������I���
		if( (move_x < 0) || (move_x >= p_cursor->max_x) ){
			break;
		}

		// �ړ�������Ƃ���̃f�[�^���擾
		data_idx = GetIdx( p_cursor, move_x, p_cursor->now_y );
		p_data = &p_cursor->p_data[ data_idx ];

	}while( p_data->movex_id == ZKN_CURSOR_MOVE_SKIP );

	// X����L���͈͓��Ȃ�l��ݒ�
	if( (move_x >= 0) && (move_x < p_cursor->max_x) ){
		// �ړ����đ��v���`�F�b�N
		if( p_data->movex_id == ZKN_CURSOR_MOVE_NORMAL ){
			// �l�𔽉f
			p_cursor->now_x = move_x;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief�@Y������CURSOR�𓮂���
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	param		�������l	(-1 or 1)
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MoveYCursor( ZKN_CURSOR* p_cursor, int param )
{
	int move_y;
	const ZKN_CURSOR_ONEDATA* p_data;
	int data_idx;
	int move_param;

	GF_ASSERT( (param == -1) || (param == 1) );
	
	move_param = 0;

	// �ݒ���W�����߂�
	do{
		// �ړ�������l���v�Z
		move_param += param;
		move_y = p_cursor->now_y + move_param;

		// �c�ő吔OR�Œᐔ�����������I���
		if( (move_y < 0) || (move_y >= p_cursor->max_y) ){
			break;
		}

		// �ړ�������Ƃ���̃f�[�^���擾
		data_idx = GetIdx( p_cursor, p_cursor->now_x, move_y );
		p_data = &p_cursor->p_data[ data_idx ];

	}while( p_data->movey_id == ZKN_CURSOR_MOVE_SKIP );

	// X����L���͈͓��Ȃ�l��ݒ�
	if( (move_y >= 0) && (move_y < p_cursor->max_y) ){
		// �ړ����đ��v���`�F�b�N
		if( p_data->movex_id == ZKN_CURSOR_MOVE_NORMAL ){
			// �l�𔽉f
			p_cursor->now_y = move_y;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	X������param�̐������i��
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	param		�i�߂�l
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContAddX( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int way;
	int abs;
	
	// �v���X�}�C�i�X�����߂�
	abs = MATH_ABS( param );
	way = param / abs;
	
	for( i=0; i<abs; i++ ){
		MoveXCursor( p_cursor, way );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y������param�̐������i��
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	param		�i�߂�l
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContAddY( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int way;
	int abs;
	
	// �v���X�}�C�i�X�����߂�
	abs = MATH_ABS( param );
	way = param / abs;
	
	for( i=0; i<abs; i++ ){
		MoveYCursor( p_cursor, way );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���ʒu��param�ɂ���
 *
 *	@param	p_cursor	CURSOR�ʒu
 *	@param	param		�ݒ�l
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void inline ZknCursorContSetX( ZKN_CURSOR* p_cursor, int param )
{
	GF_ASSERT( (param >= 0) && (param < p_cursor->max_x) );	
	p_cursor->now_x = param;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���ʒu��param�ɂ���
 *
 *	@param	p_cursor	CURSOR�ʒu
 *	@param	param		�ݒ�l
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void inline ZknCursorContSetY( ZKN_CURSOR* p_cursor, int param )
{
	GF_ASSERT( (param >= 0) && (param < p_cursor->max_y) );	
	p_cursor->now_y = param;
}

//----------------------------------------------------------------------------
/**
 *	@brief	param�̊Ǘ�ID��CURSOR�ʒu�Ɉړ�
 *
 *	@param	p_cursor	CURSOR�V�X�e�����[�N
 *	@param	param		�Ǘ�ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorContSetContID( ZKN_CURSOR* p_cursor, int param )
{
	int i;
	int data_num = p_cursor->max_x * p_cursor->max_y;

	for( i=0; i<data_num; i++ ){
		
		if( p_cursor->p_data[i].cont_id == param ){
			p_cursor->now_x = i % p_cursor->max_x;
			p_cursor->now_y = i / p_cursor->max_x;
			break;
		}
	}
}
