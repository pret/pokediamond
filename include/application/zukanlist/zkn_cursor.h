//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_cursor.h
 *	@brief		�}��cursor����V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_CURSOR_H__
#define __ZKN_CURSOR_H__

#undef GLOBAL
#ifdef	__ZKN_CURSOR_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	����ID
//=====================================
enum{
	ZKN_CURSOR_MOVE_NORMAL,		// �ʏ폈��
	ZKN_CURSOR_MOVE_STOP,		// �X�g�b�v������
	ZKN_CURSOR_MOVE_SKIP,		// �X�L�b�v������
};

//-------------------------------------
//	����R�}���h
//=====================================
enum{
	ZKN_CURSOR_CONT_ADD_X,		// X�����ړ�	
	ZKN_CURSOR_CONT_ADD_Y,		// Y�����ړ�	
	ZKN_CURSOR_CONT_SET_X,		// X�����ݒ�	
	ZKN_CURSOR_CONT_SET_Y,		// Y�����ݒ�	
	ZKN_CURSOR_CONT_SET_CONTID,	// �Ǘ�ID�̈ʒu�ɃJ�[�\�����ړ�
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	cursor1�f�[�^
//=====================================
typedef struct {
	int x;			// X���W
	int y;			// Y���W
	int size_x;		// X�T�C�Y
	int size_y;		// Y�T�C�Y
	int movex_id;	// X��������ID
	int movey_id;	// Y��������ID
	int cont_id;	// ���[�U�[�Ǘ�ID
} ZKN_CURSOR_ONEDATA;

// �Ǘ��V�X�e��
typedef struct _ZKN_CURSOR ZKN_CURSOR;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_CURSOR* ZKN_CURSOR_Alloc( int heap );
GLOBAL void ZKN_CURSOR_Free( ZKN_CURSOR* p_cursor );

GLOBAL void ZKN_CURSOR_Init( ZKN_CURSOR* p_cursor, const ZKN_CURSOR_ONEDATA* cp_data, int max_x, int max_y );
GLOBAL void ZKN_CURSOR_Cont( ZKN_CURSOR* p_cursor, int cont, int param );
GLOBAL int ZKN_CURSOR_GetContID( const ZKN_CURSOR* cp_cursor );
GLOBAL void ZKN_CURSOR_GetMat( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y );
GLOBAL void ZKN_CURSOR_GetSize( const ZKN_CURSOR* cp_cursor, int* p_x, int* p_y );

GLOBAL void ZKN_CURSOR_SetOneData( ZKN_CURSOR_ONEDATA* p_data, int x, int y, int size_x, int size_y, int movex_id, int movey_id, int cont_id );


//�@�`��֌W
enum{
	ZKN_CURSOR_MAT_TOP_LEFT,
	ZKN_CURSOR_MAT_TOP_RIGHT,
	ZKN_CURSOR_MAT_BOTTOM_LEFT,
	ZKN_CURSOR_MAT_BOTTOM_RIGHT,
	ZKN_CURROS_MAT_RECT_NUM
};
GLOBAL void ZKN_CURSOR_GetRectMat( const ZKN_CURSOR* cp_cursor, int way, int* p_x, int* p_y );


//-----------------------------------------------------------------------------
/**
 *			�ėp�֐�
 */
//-----------------------------------------------------------------------------
GLOBAL void ZKN_CURSOR_UTIL_GetRectMat( int way, int* p_x, int* p_y, int def_x, int def_y, int size_x, int size_y );

#undef	GLOBAL
#endif		// __ZKN_CURSOR_H__

