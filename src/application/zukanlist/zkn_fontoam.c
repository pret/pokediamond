//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fontoam.c
 *	@brief		�}�Ӄt�H���gOAM�V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.01.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "msg_print.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "include/application/zukanlist/zkn_drawglb.h"


#define __ZKN_FONTOAM_H_GLOBAL
#include "include/application/zukanlist/zkn_fontoam.h"

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
//	FONT_OAM�V�X�e��
//=====================================
typedef struct _ZKN_FONTOAM_SYS{
	FONTOAM_SYS_PTR		fontoam_sys;	// �t�H���g�V�X�e���f�[�^
	CLACT_SET_PTR		clact_set;		// �Z���A�N�^�[�Z�b�g
	GF_BGL_INI*			p_bg;			// bg�V�X�e��
	ZKN_FONTOAM_DATA*	p_datatbl;		// �f�[�^�e�[�u��
	int		data_num;					// �o�^�\��
	int		heap;						// �g�p����q�[�v
} ZKN_FONTOAM_SYS;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------

static BOOL CheckFontOamDataLive( ZKN_FONTOAM_DATA* p_data );
static ZKN_FONTOAM_DATA* CleanFontOamDataGet( ZKN_FONTOAM_SYS_PTR fontoam_sys );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���gOAM�V�X�e��������
 *	
 *	@param	cp_init		�������f�[�^
 *
 *	@return	�t�H���gOAM�V�X�e���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_SYS_PTR ZKN_FONTOAM_InitSys( const ZKN_FONTOAM_SYS_INIT* cp_init )
{
	ZKN_FONTOAM_SYS_PTR p_fontoam;

	// �������m��
	p_fontoam = sys_AllocMemory( cp_init->heap, sizeof(ZKN_FONTOAM_SYS) );
	GF_ASSERT( p_fontoam );
	memset( p_fontoam, 0, sizeof(ZKN_FONTOAM_SYS) );

	// �t�H���gOAM�V�X�e���쐬
	p_fontoam->fontoam_sys = FONTOAM_SysInit( cp_init->work_num, cp_init->heap );

	// �f�[�^�i�[���[�N�쐬
	p_fontoam->p_datatbl = sys_AllocMemory( cp_init->heap, sizeof(ZKN_FONTOAM_DATA) * cp_init->work_num );
	GF_ASSERT( p_fontoam->p_datatbl );
	memset( p_fontoam->p_datatbl, 0, sizeof(ZKN_FONTOAM_DATA) * cp_init->work_num );
	p_fontoam->data_num = cp_init->work_num;

	// �Z���A�N�^�[�Z�b�g�ݒ�
	p_fontoam->clact_set = cp_init->clact_set;

	// BGL�ݒ�
	p_fontoam->p_bg = cp_init->p_bg;

	// �q�[�vID�ݒ�
	p_fontoam->heap	= cp_init->heap;

	return p_fontoam;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄt�H���g�V�X�e���j��
 *
 *	@param	fontoam_sys		�}�Ӄt�H���g�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteSys( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_ASSERT( fontoam_sys );
	
	ZKN_FONTOAM_DeleteAll( fontoam_sys );

	sys_FreeMemoryEz( fontoam_sys->p_datatbl );

	FONTOAM_SysDelete( fontoam_sys->fontoam_sys );
	
	memset( fontoam_sys, 0, sizeof(ZKN_FONTOAM_SYS) );

	sys_FreeMemoryEz( fontoam_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������OAM�쐬
 *
 *	@param	cp_init 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_FONTOAM_Make( const ZKN_FONTOAM_INIT* cp_init )
{
	int char_size;

	// �L�����N�^�f�[�^�]���̈�m��
	char_size = FONTOAM_NeedCharSize( cp_init->p_bmp, cp_init->draw_area, cp_init->heap ); 

	return ZKN_FONTOAM_MakeCharOfs( cp_init, char_size );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�]���̈�f�[�^���w�肵���쐬
 *	
 *	@param	cp_init			�������f�[�^
 *	@param	char_size		�L�����N�^�T�C�Y	
 *
 *	@return	�쐬�f�[�^
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_FONTOAM_MakeCharOfs( const ZKN_FONTOAM_INIT* cp_init, int char_size )
{
	FONTOAM_INIT fo_init;
	ZKN_FONTOAM_DATA* p_make_data;

	// �󂢂Ă���e�[�u�����擾
	p_make_data = CleanFontOamDataGet( cp_init->zkn_fontoam );
	// �����Ȃ�
	GF_ASSERT( p_make_data );

	// �L�����N�^�f�[�^�]���̈�m��
	CharVramAreaAlloc( char_size, CHARM_CONT_AREACONT, cp_init->draw_area, &p_make_data->char_data );
	
	// �t�H���gOAM�쐬
	fo_init.fontoam_sys = cp_init->zkn_fontoam->fontoam_sys;
	fo_init.bmp			= cp_init->p_bmp;
	fo_init.clact_set	= cp_init->zkn_fontoam->clact_set;
	fo_init.pltt		= cp_init->pltt;
	fo_init.parent		= cp_init->parent;
	fo_init.char_ofs	= p_make_data->char_data.alloc_ofs;	
	fo_init.x			= cp_init->x;
	fo_init.y			= cp_init->y;
	fo_init.bg_pri		= cp_init->bg_pri;
	fo_init.soft_pri	= cp_init->soft_pri;
	fo_init.draw_area	= cp_init->draw_area;
	fo_init.heap		= cp_init->heap;
	p_make_data->p_fontoam = FONTOAM_Init( &fo_init );

	return p_make_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���gOAM�f�[�^�j��
 *
 *	@param	p_fontoam 
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_Delete( ZKN_FONTOAM_DATA* p_fontoam )
{
	// �t�H���g�f�[�^�j��
	FONTOAM_Delete( p_fontoam->p_fontoam );

	// �L�����N�^�Ǘ��̈�j��
	CharVramAreaFree( &p_fontoam->char_data );

	// ������
	memset( p_fontoam, 0, sizeof(ZKN_FONTOAM_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Ǘ����Ă���FONTOAM�f�[�^�j��
 *
 *	@param	fontoam_sys		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteAll( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	int i;		// ���[�v�p

	// �S�f�[�^�j��
	for( i=0; i<fontoam_sys->data_num; i++ ){
		if( CheckFontOamDataLive( &fontoam_sys->p_datatbl[ i ] ) ){
			ZKN_FONTOAM_Delete( &fontoam_sys->p_datatbl[ i ] );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�E�B���h�E�쐬
 *
 *	@param	fontoam_sys		�t�H���g�V�X�e��
 *	@param	bmp_x			�r�b�g�}�b�v�T�C�Y	�i�L�����N�^�j
 *	@param	bmp_y			�r�b�g�}�b�v�T�C�Y	�i�L�����N�^�j
 *
 *	@return	�r�b�g�}�b�v�E�B���h�E
 *
 *
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_FONTOAM_GetBmp( ZKN_FONTOAM_SYS_PTR fontoam_sys, int bmp_x, int bmp_y )
{
	GF_BGL_BMPWIN* p_bmp;
	
	p_bmp = GF_BGL_BmpWinAllocGet( fontoam_sys->heap, 1 );
	GF_BGL_BmpWinInit( p_bmp );
	GF_BGL_BmpWinObjAdd( fontoam_sys->p_bg, p_bmp, bmp_x, bmp_y, 0, 0 );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�E�B���h�E�j��
 *
 *	@param	win		�r�b�g�}�b�v�E�B���h�E
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_DeleteBmp( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinFree( win, 1 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����񏑂�����
 *
 *	@param	fontoam_sys	�t�H���gOAM�V�X�e��
 *	@param	win			�E�B���h�E	
 *	@param	dataID		�f�[�^ID
 *	@param	msgID		���b�Z�[�WID
 *	@param	bmp_x		�\�����W	�i�L�����N�^�P�ʁj
 *	@param	bmp_y		�\�����W	�i�L�����N�^�P�ʁj
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_PrintBmpStr( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, u32 dataid, u32 msgid, int bmp_x, int bmp_y )
{
	MSGDATA_MANAGER* p_msg_data;
	STRBUF* p_str;

	p_msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, dataid, fontoam_sys->heap );
	GF_ASSERT( p_msg_data );
	p_str = MSGMAN_AllocString( p_msg_data, msgid );

	// �����񏑂�����
	GF_STR_PrintColor( win, FONT_BUTTON, p_str, bmp_x, bmp_y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );

	STRBUF_Delete( p_str );
	MSGMAN_Delete( p_msg_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�̂���ʒu��STRBUF�̕��������������
 *
 *	@param	fontoam_sys	�t�H���gOAM�V�X�e��
 *	@param	win			�E�B���h�E	
 *	@param	str			������f�[�^
 *	@param	bmp_x		�\�����W	�i�L�����N�^�P�ʁj
 *	@param	bmp_y		�\�����W	�i�L�����N�^�P�ʁj
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_FONTOAM_PrintBmpStrBuf( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, STRBUF* str, int bmp_x, int bmp_y )
{
	// �����񏑂�����
	GF_STR_PrintColor( win, FONT_BUTTON, str, bmp_x, bmp_y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����̃t�H���gOAM�f�[�^�Ƀf�[�^�������Ă��邩�`�F�b�N
 *
 *	@param	p_data �f�[�^
 *
 *	@retval	TRUE		�����Ă���
 *	@retval	FALSE		�����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckFontOamDataLive( ZKN_FONTOAM_DATA* p_data )
{
	if( p_data->p_fontoam ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�󂢂Ă���FONTOAM�f�[�^�擾
 *
 *	@param	fontoam_sys		�t�H���gOAM�V�X�e��
 *
 *	@return	�J����FONTOAM�f�[�^ �󂢂Ă���e�[�u���������Ƃ�NULL
 *	
 *
 */
//-----------------------------------------------------------------------------
static ZKN_FONTOAM_DATA* CleanFontOamDataGet( ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	int i;

	for( i=0; i<fontoam_sys->data_num; i++ ){
		if( CheckFontOamDataLive( &fontoam_sys->p_datatbl[ i ] ) == FALSE ){
			return &fontoam_sys->p_datatbl[ i ];
		}
	}


	return NULL;
}
