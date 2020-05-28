//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_drawglb.c
 *	@brief		�}�ӕ`��O���[�o���f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/gflib/display.h"
#include "include/poketool/poke_tool.h"
#include "include/system/fontproc.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/system/arc_util.h"

#include "include/application/zukanlist/zkn_drawglb.h"

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
#define ZKN_DRAWGLB_POKEGRA_BACK_OFS	(0)


// �J�[�\���A�j��
#define ZKN_CURSOR_ANM_COUNT_HALF	( 32 )		// �����J�E���^�̒���
#define ZKN_CURSOR_ANM_COUNT_MAX	( ZKN_CURSOR_ANM_COUNT_HALF*2 )		// �����J�E���^�̍ő�
#define ZKN_CURSOR_ANM_DIS			( 4 )		// �J�[�\���A�j���̓�����
#define ZKN_CORSOR_ANM_TCB_PRI		( 1 )		// �^�X�N�D�揇��

// �J�[�\�����W�ύX����
#define ZKN_CURSOR_MOVE_SYNC		( 3 )		// ����V���N��
#define ZKN_CORSOR_MOVE_TCB_PRI		( 0 )		// �^�X�N�D�揇��

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
static void ZknBgSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknBgRelease( GF_BGL_INI* p_bg );

static void ZknFontBgBmpWinMake( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void ZknFontBgBmpWinDelete( ZKN_GLB_DRAWDATA* p_drawglb );

static void ZknSoftSpriteInit( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void ZknSoftSpriteDelete( ZKN_GLB_DRAWDATA* p_drawglb );

static void ZknPokeNameTblResLoad( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknPokeNameTblResRelease( ZKN_GLB_DRAWDATA* p_draw );
static void ZknPokeNameTblActAdd( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknPokeNameTblActDelete( ZKN_GLB_DRAWDATA* p_draw );

static void ZknCursorResInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknCursorResDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorActInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
static void ZknCursorActDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmAdd( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorAnmTcb( TCB_PTR tcb, void* work );
static void ZknCursorSetMatrixLocal( ZKN_UTIL_CURSOR_OBJ* p_obj, int def_x, int def_y, int size_x, int size_y );
static void ZknCursorMoveTcbAdd( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorMoveTcbDelete( ZKN_GLB_DRAWDATA* p_draw );
static void ZknCursorMoveSet( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int size_x, int size_y );
static void ZknCursorMoveTcb( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӕ`��O���[�o���f�[�^������
 *
 *	@param	p_draw		�`��O���[�o���f�[�^
 *	@param	heap		�q�[�vID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	GF_BGL_SYS_HEADER bg_header;
	ZKN_FONTOAM_SYS_INIT fontoam_init;

	// �O���t�B�b�N�t�@�C���q�[�v�n���h���I�[�v��
	p_draw->p_graphic_arc_handl = ArchiveDataHandleOpen( ARC_ZUKAN_GRA, heap );


	// BG�V�X�e���̍쐬
	p_draw->p_bg = GF_BGL_BglIniAlloc( heap );

	// BG�Z�b�g�A�b�v
	bg_header.dispMode	= GX_DISPMODE_GRAPHICS;
	bg_header.bgMode	= GX_BGMODE_0;
	bg_header.bgModeSub	= GX_BGMODE_1;
	bg_header.bg0_2Dor3D= GX_BG0_AS_3D;
	GF_BGL_InitBG( &bg_header );

	// BG������
	ZknBgSetUp( p_draw->p_bg, heap );

	// font��ʗp�r�b�g�}�b�v�쐬
	ZknFontBgBmpWinMake( p_draw, heap );

	// �Z���A�N�^�[�Z�b�g
	p_draw->clact_set = CLACT_U_SetEasyInit( ZKN_CLACT_SET_WORK_NUM, &p_draw->oam_rend, heap );

	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	p_draw->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CHAR_RES, heap );
	p_draw->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_PLTT_RES, heap );
	p_draw->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CELL_RES, heap );
	p_draw->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( ZKN_CLACT_RES_DATA_TBL_NUM, CLACT_U_CELLANM_RES, heap );

	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	// �t�H���gOAM�V�X�e���쐬
	fontoam_init.clact_set	= p_draw->clact_set;
	fontoam_init.p_bg		= p_draw->p_bg;
	fontoam_init.work_num	= ZKN_FONTOAM_WORK_NUM;
	fontoam_init.heap		= heap;
	p_draw->fontoam_sys = ZKN_FONTOAM_InitSys( &fontoam_init );

	// �t�H���g�f�[�^�ǂݍ���
	FontProc_LoadFont( FONT_BUTTON, heap );
	

	// �\�t�g�E�F�A�}�l�[�W��
	ZknSoftSpriteInit( p_draw, heap );


	// �|�P�������X�g�p���\�[�X�ǂݍ��݁��A�N�^�[�o�^
	ZknPokeNameTblResLoad( p_draw, heap );
	ZknPokeNameTblActAdd( p_draw, heap );

	// �J�[�\���p���\�[�X�ǂݍ��݁��A�N�^�[�o�^
	ZknCursorResInit( p_draw, heap );
	ZknCursorActInit( p_draw, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃO���[�o���`��f�[�^�j��
 *
 *	@param	p_draw		�`��O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	
	// �A�N�^�[�j�������\�[�X�j��
	ZknPokeNameTblActDelete( p_draw );
	ZknPokeNameTblResRelease( p_draw );

	// �J�[�\���p���\�[�X�j�����A�N�^�[�j��
	ZknCursorActDelete( p_draw );
	ZknCursorResDelete( p_draw );
	
	// ������`��p�r�b�g�}�b�v�j��
	ZknFontBgBmpWinDelete( p_draw );

	// BG�j��
	ZknBgRelease( p_draw->p_bg );

	
	// BG�V�X�e��
	sys_FreeMemoryEz( p_draw->p_bg );

	// �Z���A�N�^�[�Z�b�g
	CLACT_DestSet( p_draw->clact_set );

	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_draw->res_manager[ CLACT_U_CELLANM_RES ] );

	// FONTOAM
	ZKN_FONTOAM_DeleteSys( p_draw->fontoam_sys );

	// ������t�H���g�j��
	FontProc_UnloadFont( FONT_BUTTON );

	// �\�t�g�E�F�A�}�l�[�W��
	ZknSoftSpriteDelete( p_draw );

	// �A�[�J�C�u�n���h�������
	ArchiveDataHandleClose( p_draw->p_graphic_arc_handl );

	memset( p_draw, 0, sizeof( ZKN_GLB_DRAWDATA ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӕ`��O���[�o���f�[�^�@���`��V�X�e���@�`�揈��
 *
 *	@param	p_draw	�`��O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataMain( ZKN_GLB_DRAWDATA* p_draw )
{
	// �Z���A�N�^�[�`��
	CLACT_Draw( p_draw->clact_set );
	
	// �J�����Z�b�g�A�b�v
	NNS_G2dSetupSoftwareSpriteCamera();
	
	// �\�t�g�E�F�A�X�v���C�g�`��
	SoftSpriteMain( p_draw->soft_sprite_man );
	SWSP_SysDraw( p_draw->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank�֐�
 *
 *	@param	p_draw		�`��O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GlbDrawDataVBlank( ZKN_GLB_DRAWDATA* p_draw )
{
	GF_BGL_VBlankFunc( p_draw->p_bg );

	// �\�t�g�E�F�A�X�v���C�g
	SoftSpriteTextureTrans( p_draw->soft_sprite_man );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�ݒ�
 *
 *	@param	p_draw		�`��f�[�^
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	sex			����		-1�̂Ƃ��f�t�H
 *	@param	dir			����
 *	@param	col			���A�J���[��
 *	@param	form_no		�t�H�[���i���o�[�@�֌W�Ȃ��Ƃ��O
 *	@param	rnd			�ő̗���			�֌W�Ȃ��Ƃ��O
 *
 *	@return	none
 *
 *	sex
		PARA_MALE=0,		����
		PARA_FEMALE,		�߂�
		PARA_UNK,			�Ȃ�

	dir
		PARA_FRONT:����
		PARA_BACK:�w��
	
	col
		PARA_NORMAL:�m�[�}��
		PARA_RARE:���A
 */
//----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y )
{
	ZKN_GlbPokemonGraphicSet_Idx( p_draw, mons_no, sex, dir, col, form_no, rnd, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O�����W��ݒ�
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int x, int y )
{
	ZKN_GlbPokemonGraphicSetMatrix_Idx( p_draw, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O�����W���擾
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicGetMatrix( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y )
{
	ZKN_GlbPokemonGraphicGetMatrix_Idx( p_draw, x, y, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����I�u�W�F�N�g�擾
 *
 *	@param	p_draw	�`��f�[�^
 *
 *	@return	�\�t�g�E�F�A�X�v���C�g
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_GlbPokemonGraphicGet( const ZKN_GLB_DRAWDATA* cp_draw )
{
	return ZKN_GlbPokemonGraphicGet_Idx( cp_draw, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	cp_draw
 *	@param	flag 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicDrawFlagSet( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag )
{
	ZKN_GlbPokemonGraphicDrawFlagSet_Idx( cp_draw, flag, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�ݒ�
 *
 *	@param	p_draw		�`��f�[�^
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	sex			����		-1�̂Ƃ��f�t�H
 *	@param	dir			����
 *	@param	col			���A�J���[��
 *	@param	form_no		�t�H�[���i���o�[	�֌W�Ȃ��Ƃ��O
 *	@param	rnd			�ő̗���			�֌W�Ȃ��Ƃ��O
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	idx			�C���f�b�N�X
 *
 *	@return	none
 *
 *	sex
		PARA_MALE=0,		����
		PARA_FEMALE,		�߂�
		PARA_UNK,			�Ȃ�

	dir
		PARA_FRONT:����
		PARA_BACK:�w��
	
	col
		PARA_NORMAL:�m�[�}��
		PARA_RARE:���A
 */
//----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSet_Idx( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y, int idx )
{
	SOFT_SPRITE_ARC poke_arc;
	s16 height;
	
	// ���܂ł̂�j��
	if( p_draw->soft_sprite[idx] ){
		SoftSpriteDel( p_draw->soft_sprite[idx] );
	}

	// sex �� -1�̂Ƃ��͕��ʂ̐��ʂ�ݒ�
	if( sex == -1 ){
		sex = PokeSexGetMonsNo( mons_no, 0 );
	}

	// �|�P�����O���t�B�b�N�f�[�^�擾
	PokeGraArcDataGet( &poke_arc, mons_no, sex, dir, col, form_no, rnd );		//�Ō�̈����́AFormNo�ƌ������ł� by soga 2006.05.01 �m�F���܂��� by tomoya

	// ��������
	if( dir == PARA_BACK ){
		height = PokeHeightGet( mons_no, sex, dir, form_no, rnd);
		height += ZKN_DRAWGLB_POKEGRA_BACK_OFS;	// �}�ӂł̍�����
	}else{
		height = 0;
	}

	// �o�^
	p_draw->soft_sprite[idx] = SoftSpriteAdd( 
			p_draw->soft_sprite_man,
			&poke_arc,
			x, y+height, 0, 0,
			NULL, NULL
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O�����W��ݒ�
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	x		�����W
 *	@param	y		�����W
 *	@param	idx		�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicSetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int idx )
{
	SoftSpriteParaSet( p_draw->soft_sprite[idx], SS_PARA_POS_X, x );
	SoftSpriteParaSet( p_draw->soft_sprite[idx], SS_PARA_POS_Y, y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O�����W���擾
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *	@param	idx		�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicGetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y, int idx )
{
	*x = SoftSpriteParaGet( p_draw->soft_sprite[idx], SS_PARA_POS_X );
	*y = SoftSpriteParaGet( p_draw->soft_sprite[idx], SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����I�u�W�F�N�g�擾
 *
 *	@param	p_draw	�`��f�[�^
 *	@param	idx		�C���f�b�N�X
 *
 *	@return	�\�t�g�E�F�A�X�v���C�g
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_GlbPokemonGraphicGet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, int idx )
{
	return cp_draw->soft_sprite[idx];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	cp_draw
 *	@param	flag 
 *	@param	idx			�C���f�b�N�X
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokemonGraphicDrawFlagSet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag, int idx )
{
	if( cp_draw->soft_sprite[idx] == NULL ){
		return ;
	}
	
	if( flag == TRUE ){
		SoftSpriteParaSet( cp_draw->soft_sprite[idx], SS_PARA_VANISH, FALSE );
	}else{
		SoftSpriteParaSet( cp_draw->soft_sprite[idx], SS_PARA_VANISH, TRUE );
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������X�g�̃e�[�u���A�N�^�[�擾
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	�A�N�^�[
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ZKN_GlbPokeNameTblClactGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.pokelist_tbl );

	return p_draw->pokelist_data_draw.pokelist_tbl;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������X�g�̃A�C�R���A�N�^�[�擾
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	�A�N�^�[
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ZKN_GlbPokeNameIconClactGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.pokelist_icon );

	return p_draw->pokelist_data_draw.pokelist_icon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������ݒ�
 *
 *	@param	p_draw			�`��O���[�o��
 *	@param	p_fontoam_init	�ӂ����OAM�������f�[�^
 *	@param	char_size		�L�����N�^�]���̈�T�C�Y
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode )
{
	ZKN_GlbPokeNameTblSet_Minute( &p_draw->pokelist_data_draw, p_fontoam_init, char_size, mons_no, zkn_mode );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���ۂɃ|�P�������ݒ�
 *
 *	@param	p_data				�f�[�^
 *	@param	p_fontoam_init		�t�H���g�������f�[�^
 *	@param	char_size			�L�����N�^�T�C�Y
 *	@param	mons_no				�����X�^�[�i���o�[ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode )
{
	// �����X�^�[���ꏏ�Ȃ牽�����Ȃ�
	if( (mons_no == p_data->mons_no) && (zkn_mode == p_data->zkn_mode) ){
		FONTOAM_SetDrawFlag( p_data->p_pokename->p_fontoam, TRUE );
		return ;
	}else{
		p_data->mons_no = mons_no;
		p_data->zkn_mode = zkn_mode;
	}
	
	// ���܂ł̂�j��
	if( p_data->p_pokename ){
		ZKN_FONTOAM_Delete( p_data->p_pokename );
	}
	
	if( char_size != 0 ){
		p_data->p_pokename = ZKN_FONTOAM_MakeCharOfs( p_fontoam_init, char_size );
	}else{
		p_data->p_pokename = ZKN_FONTOAM_Make( p_fontoam_init );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P������OAM�f�[�^�擾
 *
 *	@param	p_draw �`��O���[�o��
 *
 *	@return	OAM�f�[�^
 */
//-----------------------------------------------------------------------------
ZKN_FONTOAM_DATA* ZKN_GlbPokeNameTblGet( const ZKN_GLB_DRAWDATA* p_draw )
{
	GF_ASSERT( p_draw->pokelist_data_draw.p_pokename );

	return  p_draw->pokelist_data_draw.p_pokename;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u���p���\�[�X�I�u�W�F�擾
 *
 *	@param	p_draw		�`��O���[�o��
 *	@param	res_type	���\�[�X�^�C�v
 *
 *	@return	���\�[�X�I�u�W�F
 *
 *	res_type
		CLACT_U_CHAR_RES,		// �L�����N�^���\�[�X���Ǘ�
		CLACT_U_PLTT_RES,		// �p���b�g���\�[�X���Ǘ�
		CLACT_U_CELL_RES,		// �Z�����\�[�X���Ǘ�
		CLACT_U_CELLANM_RES,	// �Z���A�j�����\�[�X���Ǘ�
 */
//-----------------------------------------------------------------------------
CLACT_U_RES_OBJ_PTR ZKN_GlbPokeNameTblResObjGet( const ZKN_GLB_DRAWDATA* p_draw, int res_type )
{
	GF_ASSERT( res_type <= CLACT_U_CELLANM_RES );
	
	return p_draw->pokelist_data_draw.pokelist_res_obj[ res_type ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u����OAM���[�h��ݒ�
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	mode	OAM���[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblObjModeSet( const ZKN_GLB_DRAWDATA* p_draw, GXOamMode mode )
{
	CLACT_ObjModeSet( p_draw->pokelist_data_draw.pokelist_tbl, mode );
	CLACT_ObjModeSet( p_draw->pokelist_data_draw.pokelist_icon, mode );
	FONTOAM_ObjModeSet( p_draw->pokelist_data_draw.p_pokename->p_fontoam, mode );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������X�g��BG�D�揇�ʐݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	pri		�`��BGpriority
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblBGPriSet( const ZKN_GLB_DRAWDATA* p_draw, int pri )
{
	CLACT_BGPriorityChg( p_draw->pokelist_data_draw.pokelist_tbl, pri );
	CLACT_BGPriorityChg( p_draw->pokelist_data_draw.pokelist_icon, pri );
	FONTOAM_SetBGPriority( p_draw->pokelist_data_draw.p_pokename->p_fontoam, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	p_draw
 *	@param	flag 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblDrawFlagSet( const ZKN_GLB_DRAWDATA* p_draw, BOOL flag )
{
	if( p_draw->pokelist_data_draw.pokelist_tbl ){
		CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_tbl, flag );
	}
	if( p_draw->pokelist_data_draw.pokelist_icon ){
		CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_icon, flag );
	}
	if( p_draw->pokelist_data_draw.p_pokename->p_fontoam ){
		FONTOAM_SetDrawFlag( p_draw->pokelist_data_draw.p_pokename->p_fontoam, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�e�B�e�B�@�Ǝ��t�F�[�h�C���@�A�E�g�V�X�e��
 *
 *	@param	p_fade		�t�F�[�h�f�[�^
 *	@param	sync		�V���N��
 *	@param	brightness_s�u���C�g�l�X�J�n�l
 *	@param	brightness_e�u���C�g�l�X�I���l
 *	@param	s_alpha		�J�n���l	
 *	@param	e_alpha		�I�����l	
 *	@param	plane1		���Ώ̖ʂP	
 *	@param	plane2		���Ώ̖ʂQ	�i�Ώ̖ʂQ�͐�΂�BD���������܂��j
 *	@param	disp_flag	���C�����T�u��
 *
 *	@return	none
 *
 *	disp_flag
	ZKN_UTIL_FADE_MAIN,
	ZKN_UTIL_FADE_SUB,
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_ChangeFadeRequest( ZKN_UTIL_FADE_SYS* p_fade, u8 sync, int brightness_s, int brightness_e, int s_alpha, int e_alpha, BRIGHT_PLANEMASK plane1, BRIGHT_PLANEMASK plane2, int disp_flag )
{
	// ���C�����T�u��
	p_fade->disp_flag = disp_flag;

	// �Ώ̖�
	p_fade->plane1 = plane1;
	p_fade->plane2 = plane2 | PLANEMASK_BD;
	
	// �t�F�[�h�f�[�^
	p_fade->brightness_s		= brightness_s;
	p_fade->brightness_dis		= brightness_e - brightness_s;
	p_fade->alpha_s				= s_alpha;
	p_fade->alpha_dis			= e_alpha - s_alpha;
	p_fade->count_max			= sync;
	p_fade->count				= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�e�B�e�B�@�Ǝ��t�F�[�h�C���@�A�E�g�V�X�e��
 *
 *	@param	p_fade	�t�F�[�h�f�[�^
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLB_ChangeFadeMain( ZKN_UTIL_FADE_SYS* p_fade )
{
	int set_alpha, set_brightness;

	if( ZKN_GLB_ChangeFadeEndCheck( p_fade ) == FALSE ){
		
		set_alpha = ZKN_GLB_GetFadeAlpha( p_fade );
		set_brightness = ZKN_GLB_GetFadeBrightness( p_fade );

		// �ݒ�
		if( p_fade->disp_flag == ZKN_UTIL_FADE_MAIN ){
			G2_SetBlendBrightnessExt( p_fade->plane1, p_fade->plane2,
					set_alpha, 0,
					set_brightness );
		}else{
			G2S_SetBlendBrightnessExt( p_fade->plane1, p_fade->plane2,
					set_alpha, 0,
					set_brightness );
		}

		// �J�E���g
		p_fade->count++;
	}

	return ZKN_GLB_ChangeFadeEndCheck( p_fade );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃��l���擾
 *
 *	@param	p_fade 
 *
 *	@return	���l
 */
//-----------------------------------------------------------------------------
int ZKN_GLB_GetFadeAlpha( ZKN_UTIL_FADE_SYS* p_fade )
{
	fx32 alpha;

	alpha = FX_Mul( p_fade->alpha_dis << FX32_SHIFT, p_fade->count << FX32_SHIFT );
	alpha = FX_Div( alpha, p_fade->count_max << FX32_SHIFT );

	return (alpha >> FX32_SHIFT) + p_fade->alpha_s;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̃u���C�g�l�X�l���擾
 *
 *	@param	p_fade 
 *
 *	@return	�u���C�g�l�X�l
 */
//-----------------------------------------------------------------------------
int ZKN_GLB_GetFadeBrightness( ZKN_UTIL_FADE_SYS* p_fade )
{
	fx32 brightness;

	brightness = FX_Mul( p_fade->brightness_dis << FX32_SHIFT, p_fade->count << FX32_SHIFT );
	brightness = FX_Div( brightness, p_fade->count_max << FX32_SHIFT );
	
	return (brightness >> FX32_SHIFT) + p_fade->brightness_s;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���`�F�b�N
 *
 *	@param	p_fade	�t�F�[�h���[�N
 *
 *	@retval TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLB_ChangeFadeEndCheck( ZKN_UTIL_FADE_SYS* p_fade )
{
	if( p_fade->count <= p_fade->count_max ){
		return FALSE;
	}

	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O���p���b�g�t�F�[�h�l��ݒ�
 *
 *	@param	p_draw		�`��O���[�o��
 *	@param	p_fade		�t�F�[�h�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_SpritePokeGraPalFade( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade )
{
	SOFT_SPRITE* ssp;
	int brightness;

	brightness = -ZKN_GLB_GetFadeBrightness( p_fade );
	
	// �|�P�����\�t�g�p���b�g�t�F�[�h
	ssp = ZKN_GlbPokemonGraphicGet( p_draw );
	SoftSpritePalFadeSet( ssp, brightness, brightness, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O���p���b�g�t�F�[�h�l��ݒ�
 *
 *	@param	p_draw		�`��O���[�o��
 *	@param	p_fade		�t�F�[�h�f�[�^
 *	@param	idx			�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLB_SpritePokeGraPalFade_Idx( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade, int idx )
{
	SOFT_SPRITE* ssp;
	int brightness;

	brightness = -ZKN_GLB_GetFadeBrightness( p_fade );
	
	// �|�P�����\�t�g�p���b�g�t�F�[�h
	ssp = ZKN_GlbPokemonGraphicGet_Idx( p_draw, idx );
	SoftSpritePalFadeSet( ssp, brightness, brightness, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���I�u�W�F�N�g�ɍ��W��ݒ�
 *
 *	@param	cp_cursor	�J�[�\���V�X�e��
 *	@param	p_draw		�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixCursorSys( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw )
{
	int x,y,size_x,size_y;
	
	// ���W�ƃT�C�Y���擾
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�����W��ݒ�
 *
 *	@param�@p_draw		�`��O���[�o��	
 *	@param	def_x		�f�t�H���g�w
 *	@param	def_y		�f�t�H���g�x
 *	@param	size_x		�J�[�\���T�C�Y�w
 *	@param	size_y		�J�[�\���T�C�Y�x
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y )
{
	ZknCursorMoveSet( p_draw, def_x, def_y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��n�m�n�e�e
 *
 *	@param	p_obj	�`��I�u�W�F
 *	@param	flag	�t���O
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, int flag )
{
	int i;

	// �`��n�m�n�e�e
	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		CLACT_SetDrawFlag( p_obj->cursor[i], flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��ONOFF�擾
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@retval	TRUE	�`��ON
 *	@retval	FALSE	�`��OFF
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_CursorGetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj )
{
	return CLACT_GetDrawFlag( p_obj->cursor[0] );	// ��\����0
}

//----------------------------------------------------------------------------
/**
 *	@brief	����A�j���n�m�n�e�e�t���O
 *
 *	@param	p_obj	�J�[�\���I�u�W�F�N�g
 *	@param	anm		�A�j���t���O
 *
 *	@return	none
 *
 *	anm
 *		TRUE	�X�g�b�v
 *		FALSE	�Đ�
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetAnimeStopFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, BOOL anm )
{
	p_obj->anm_stop = anm;

	// �J�n�Ȃ�J�E���^������
	if( anm == FALSE ){
		p_obj->anm_count = 0;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ړ��A�j���Ȃ��̍��W�ݒ�@�������p
 *
 *	@param	cp_cursor	�J�[�\���V�X�e��
 *	@param	p_draw		�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw )
{
	int x, y, size_x, size_y;

	// ���W�ƃT�C�Y���擾
	ZKN_CURSOR_GetMat( cp_cursor, &x, &y );
	ZKN_CURSOR_GetSize( cp_cursor, &size_x, &size_y );

	// ���W�ݒ�
	ZKN_UTIL_CursorSetMatrixNotAnm( p_draw, x, y, size_x, size_y );
}
//----------------------------------------------------------------------------
/**
 *	@brief	�ړ��A�j���Ȃ��̍��W�ݒ�@�������p
 *
 *	@param	p_draw
 *	@param	def_x
 *	@param	def_y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_CursorSetMatrixNotAnm( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y )
{
	p_draw->cursor.x = def_x;
	p_draw->cursor.y = def_y;
	p_draw->cursor.size_x = size_x;
	p_draw->cursor.size_y = size_y;

	// ���W�ݒ�
	ZknCursorSetMatrixLocal( &p_draw->cursor, p_draw->cursor.x, p_draw->cursor.y,
			p_draw->cursor.size_x, p_draw->cursor.size_y );

	p_draw->cursor_move.ta_x = def_x;
	p_draw->cursor_move.ta_y = def_y;
	p_draw->cursor_move.ta_size_x = size_x;
	p_draw->cursor_move.ta_size_y = size_y;
	p_draw->cursor_move.move_stop = FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	����
 *
 *	@param	p_work			���샏�[�N
 *	@param	s_x				�J�nx���W
 *	@param	e_x				�I��x���W
 *	@param	s_y				�J�ny���W
 *	@param	e_y				�I��y���W
 *	@param	count_max		�J�E���g�ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_MoveReq( ZKN_UTIL_MOVE_WORK* p_work, int s_x, int e_x, int s_y, int e_y, int count_max )
{
	p_work->x = s_x;
	p_work->y = s_y;

	p_work->s_x = s_x;
	p_work->s_y = s_y;
	p_work->dis_x = e_x - s_x;
	p_work->dis_y = e_y - s_y;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���상�C��
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_MoveMain( ZKN_UTIL_MOVE_WORK* p_work )
{
	fx32 w_x, w_y;



	// ���ݍ��W�擾
	w_x = FX_Mul( p_work->dis_x << FX32_SHIFT, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	w_y = FX_Mul( p_work->dis_y << FX32_SHIFT, p_work->count << FX32_SHIFT );
	w_y = FX_Div( w_y, p_work->count_max << FX32_SHIFT );

	
	p_work->x = (w_x >> FX32_SHIFT) + p_work->s_x;
	p_work->y = (w_y >> FX32_SHIFT) + p_work->s_y;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�[�J�C�u�t�@�C���n���h�����擾����
 *
 *	@param	p_draw	�`���ް�
 *
 *	@return	�A�[�J�C�u�t�@�C���n���h��
 */
//-----------------------------------------------------------------------------
ARCHANDLE* ZKN_GLBDATA_ArcHandlGet( ZKN_GLB_DRAWDATA* p_draw )
{
	return p_draw->p_graphic_arc_handl;
}

//------------------------------------------------------------------
/**
 * �A�[�J�C�u�f�[�^�̓ǂݏo���i�������m�ۂ���j
 *
 * @param   p_draw			�`���۰����ް�
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   compressedFlag	���k����Ă��邩�H
 * @param	heapID			�g�p����q�[�v
 *
 * @retval  void*			�ǂݏo���̈�|�C���^
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_Arc_Load(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, u32 heapID)
{
	void* arcData;
	
	arcData = ArchiveDataLoadAllocByHandle( p_draw->p_graphic_arc_handl, dataIdx, heapID );

	if( arcData != NULL )
	{
		if( compressedFlag )
		{
			void* data;

			data = sys_AllocMemory( heapID, MI_GetUncompressedSize( arcData ) );
			if( data )
			{
				MI_UncompressLZ8( arcData, data );
				sys_FreeMemoryEz( arcData );
			}
			arcData = data;
		}
	}

	return arcData;
}

//------------------------------------------------------------------
/**
 * BG����ް��� VRAM �]��
 *
 * @param   p_draw			�`���۰����ް�
 * @param   dataIndex		�������ް����ޯ��
 * @param   bgl				BGL�ް�
 * @param   frm				�]�����ڰ�����
 * @param   offs			�]���̾�āi��גP�ʁj
 * @param	transSize		�]�����黲�ށi�޲ĒP�� ==0�őS�]���j
 * @param   compressedFlag	���k����Ă����ް����H
 * @param   heapID			�ް��ǂݍ��݁E�������؂Ƃ��Ďg��˰��ID
 *
 * @return  �]�������f�[�^�T�C�Y�i�o�C�g�j
 */
//------------------------------------------------------------------
u32 ZKN_GLBDATA_BgCharSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedBGCharacterData( arcData, &charData ) )
		{
			if( transSize == 0 )
			{
				transSize = charData->szByte;
			}
			GF_BGL_LoadCharacter(bgl, frm, charData->pRawData, transSize, offs);
		}

		sys_FreeMemoryEz( arcData );
	}
    return transSize;
}
//------------------------------------------------------------------
/**
 * ��گ��ް� �� VRAM �]��
 *
 * @param   p_draw			�`���۰����ް�
 * @param   dataIdx		�������ް����ޯ��
 * @param   palType		��گē]��������
 * @param   offs		��گē]����̾��
 * @param   transSize	��گē]�����ށi0 �őS�]���j
 * @param   heapID		�ް��ǂݍ��������؂Ƃ��Ďg��˰��ID
 *
 */
//------------------------------------------------------------------
void ZKN_GLBDATA_PalSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	static void (* const load_func[])(const void*, u32, u32) = {
		GX_LoadBGPltt,
		GX_LoadOBJPltt,
		GX_LoadBGExtPltt,
		GX_LoadOBJExtPltt,
		GXS_LoadBGPltt,
		GXS_LoadOBJPltt,
		GXS_LoadBGExtPltt,
		GXS_LoadOBJExtPltt,
	};

	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, FALSE, heapID );

	if( arcData != NULL )
	{
		NNSG2dPaletteData* palData;

		if( NNS_G2dGetUnpackedPaletteData( arcData, &palData ) )
		{
			if( transSize == 0 )
			{
				transSize = palData->szByte;
			}
			DC_FlushRange( palData->pRawData, transSize );
			load_func[ palType ]( palData->pRawData, offs, transSize );
		}

		sys_FreeMemoryEz( arcData );
	}
}
//--------------------------------------------------------------------------------------------
/**
 * ��ذ��ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   p_draw			�`���۰����ް�
 * @param   arcIndex		[in] �������ް����ޯ��
 * @param   compressedFlag	[in] ���k����Ă����ް����H
 * @param   scrnData		[out] ��ذ��ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			[in] ˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//--------------------------------------------------------------------------------------------
void* ZKN_GLBDATA_ScrnDataGet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID)
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedScreenData( arcData, scrnData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//------------------------------------------------------------------
/**
 * ��گ��ް���۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   p_draw			�`���۰����ް�
 * @param   arcIndex		�������ް����ޯ��
 * @param   palData			��گ��ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID			˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_PalDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID )
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, FALSE, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedPaletteData( arcData, palData ) == FALSE )
		{
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}
//------------------------------------------------------------------
/**
 * ����ް��� ۰�ނ��� Unpack ���邾���ł��B����͊e���ŁB
 *
 * @param   p_draw			�`���۰����ް�
 * @param   dataIdx				[in] �ް����ޯ��
 * @param   compressedFlag		[in] ���k����Ă��邩
 * @param   charData			[out] ����ް����ڽ��ێ������߲���̱��ڽ
 * @param   heapID				[in] ˰��ID
 *
 * @retval  void*		۰�ނ����ް��̐擪�߲��
 */
//------------------------------------------------------------------
void* ZKN_GLBDATA_CharDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID )
{
	void* arcData = ZKN_GLBDATA_Arc_Load( p_draw, dataIdx, compressedFlag, heapID );

	if( arcData != NULL )
	{
		if( NNS_G2dGetUnpackedBGCharacterData( arcData, charData ) == FALSE)
		{
			// ���s������NULL
			sys_FreeMemoryEz( arcData );
			return NULL;
		}
	}
	return arcData;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�f�[�^�ݒ�
 *
 *	@param	p_bg	BG�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknBgSetUp( GF_BGL_INI* p_bg, int heap )
{
	// ���C����� BG1��		�����񏑂����ݖ�
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_FONT_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_FONT_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_FONT_M );
	}

	// ���C����� BG2��		���[�e�B���e�B��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_M );
	}

	// 3D��
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 2 );
	// BG0ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );


	// ���C����� BG3��		�w�i��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_M );
	}


	// �T�u��� BG1��		���[�e�B���e�B��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_S, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_S, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_S );
	}

	// �T�u��� BG2��		�w�i��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_S, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_S, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_S );
	}

	// �T�u��� BG3��		�g�kBG��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x400, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x10000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_AFFINE_S, &bg_cnt_header, GF_BGL_MODE_AFFINE );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 64, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_AFFINE_S );
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�R���g���[���f�[�^�j��
 *
 *	@param	p_bg	BG�R���g���[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknBgRelease( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_S );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_AFFINE_S );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_S );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	������`��p�r�b�g�}�b�v�쐬
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFontBgBmpWinMake( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	// �r�b�g�}�b�v�E�B���h�E�o�^
	GF_BGL_BmpWinAdd( p_drawglb->p_bg, &p_drawglb->bmp_mfont,
			ZKN_BG_FRM_FONT_M, 0, 0, ZKN_BG_FONTBMP_CX, ZKN_BG_FONTBMP_CY, ZKN_BG_FONT_COLOR, 0 );

	// �N���[��
	GF_BGL_BmpWinDataFill( &p_drawglb->bmp_mfont, 0 );

	// �\��
	GF_BGL_BmpWinOn( &p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����`��p�r�b�g�}�b�v�f�[�^�j��
 *
 *	@param	p_drawglb		�`��O���[�o���f�[�^�j��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFontBgBmpWinDelete( ZKN_GLB_DRAWDATA* p_drawglb )
{
	GF_BGL_BmpWinDel( &p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g������
 *
 *	@param	p_drawglb	�`��f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoftSpriteInit( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;
	int i;

	// �|�P�����f�[�^�]���̈��Vram���m�ہ��]���A�h���X�ƃT�C�Y��ݒ�
	p_drawglb->soft_sprite_man = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(ZKN_POKEGRA_TEX_SIZE, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(ZKN_POKEGRA_PLTT_SIZE, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			p_drawglb->soft_sprite_man,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			p_drawglb->soft_sprite_man,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

/*
	OS_Printf( 
			" addr %x size %x \n",
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	OS_Printf( 
			" addr %x size %x \n ",
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );
//*/

	//������
	for( i=0; i<ZKN_DRAWGLB_POKEGRA_NUM; i++ ){
		p_drawglb->soft_sprite[i] = NULL;
	}



	// �|�P�O���ȊO�̃X�v���C�g�V�X�e��
	{
		SWSP_SYSDATA swsp_sys_data = {
			ZKN_SWSP_OBJNUM,
			ZKN_SWSP_CHARNUM,			
			ZKN_SWSP_PLTTNUM,
			0
		};
		swsp_sys_data.heap = heap;

		p_drawglb->swsp_sys = SWSP_SysInit( &swsp_sys_data );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g�j��
 *
 *	@param	p_drawglb	�`��f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoftSpriteDelete( ZKN_GLB_DRAWDATA* p_drawglb )
{
	int i;
	
	for( i=0; i<ZKN_DRAWGLB_POKEGRA_NUM; i++ ){

		if( p_drawglb->soft_sprite[i] ){
			SoftSpriteDel( p_drawglb->soft_sprite[i] );
		}
	}
	
	// �|�P�����`��X�v���C�g�f�[�^�j��
	SoftSpriteEnd( p_drawglb->soft_sprite_man );


	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SysDelete( p_drawglb->swsp_sys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u�����\�[�X�ǂݍ���
 *
 *	@param	p_draw	�`��f�[�^
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblResLoad( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	ZKN_POKELIST_DATA_OAM_DATA* p_darw_data = &p_draw->pokelist_data_draw;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw );

	
	// �L�����N�^�f�[�^�ǂݍ���
	p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_draw->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_oam_main_lzh_NCGR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_darw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_handle, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_darw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );



	// �Z���f�[�^�ǂݍ���
	p_darw_data->pokelist_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_oam_main_lzh_NCER,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_darw_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_oam_main_lzh_NANR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����l�[���e�[�u�����\�[�X�ǂݍ���
 *
 *	@param	p_data
 *	@param	pp_res_manager
 *	@param	heap 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblResLoad_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	// �L�����N�^�f�[�^�ǂݍ���
	p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( pp_res_manager[ CLACT_U_CHAR_RES ], 
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NCGR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( pp_res_manager[ CLACT_U_PLTT_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_DRAWGLB_POKENAME_TBL_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );



	// �Z���f�[�^�ǂݍ���
	p_data->pokelist_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELL_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NCER,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			ARC_ZUKAN_GRA, NARC_zukan_zkn_oam_main_lzh_NANR,
			TRUE, ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u�����\�[�X�j��
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblResRelease( ZKN_GLB_DRAWDATA* p_draw )
{
	ZKN_POKELIST_DATA_OAM_DATA* p_draw_data = &p_draw->pokelist_data_draw;

	CLACT_U_CharManagerDelete( p_draw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����l�[���e�[�u���@���\�[�X�j��
 *
 *	@param	p_data
 *	@param	pp_res_manager 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblResRelease_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	CLACT_U_CharManagerDelete( p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CHAR_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_PLTT_RES ],
			p_data->pokelist_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELL_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			p_data->pokelist_res_obj[ CLACT_U_CELLANM_RES ] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�A�N�^�[�o�^
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblActAdd( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �e�[�u������
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->pokelist_data_draw.pokelist_tbl = CLACT_AddSimple( &add );
	// ��\��
	CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_tbl, FALSE );
	CLACT_DrawPriorityChg( p_draw->pokelist_data_draw.pokelist_tbl, 1 );

	// �A�C�R������
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->pokelist_data_draw.pokelist_icon = CLACT_AddSimple( &add );
	// ��\��
	CLACT_SetDrawFlag( p_draw->pokelist_data_draw.pokelist_icon, FALSE );
	CLACT_AnmChg( p_draw->pokelist_data_draw.pokelist_icon, 1 );


	// ���O�͓o�^���Ȃ�
	p_draw->pokelist_data_draw.p_pokename = NULL;
	p_draw->pokelist_data_draw.mons_no = 0;
	p_draw->pokelist_data_draw.zkn_mode = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u���A�N�^�[�j��
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeNameTblActDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	CLACT_Delete( p_draw->pokelist_data_draw.pokelist_tbl );
	p_draw->pokelist_data_draw.pokelist_tbl = NULL;
	CLACT_Delete( p_draw->pokelist_data_draw.pokelist_icon );
	p_draw->pokelist_data_draw.pokelist_icon = NULL;
	if(p_draw->pokelist_data_draw.p_pokename){
		ZKN_FONTOAM_Delete( p_draw->pokelist_data_draw.p_pokename );
		p_draw->pokelist_data_draw.p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����l�[���e�[�u���A�N�^�[�o�^
 *
 *	@param	p_data
 *	@param	clact_set
 *	@param	pp_res_manager
 *	@param	heap 
 *	@param	bg_pri
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblActAdd_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int bg_pri )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			ZKN_DRAWGLB_POKENAME_TBL_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, bg_pri,
			pp_res_manager[ CLACT_U_CHAR_RES ],
			pp_res_manager[ CLACT_U_PLTT_RES ],
			pp_res_manager[ CLACT_U_CELL_RES ],
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �e�[�u������
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->pokelist_tbl = CLACT_AddSimple( &add );
	// ��\��
	CLACT_SetDrawFlag( p_data->pokelist_tbl, FALSE );
	CLACT_DrawPriorityChg( p_data->pokelist_tbl, 1 );

	// �A�C�R������
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->pokelist_icon = CLACT_AddSimple( &add );
	// ��\��
	CLACT_SetDrawFlag( p_data->pokelist_icon, FALSE );
	CLACT_AnmChg( p_data->pokelist_icon, 1 );


	// ���O�͓o�^���Ȃ�
	p_data->p_pokename = NULL;
	p_data->mons_no = 0;
	p_data->zkn_mode = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����l�[���e�[�u���A�N�^�[�j��
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblActDelete_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data )
{
	CLACT_Delete( p_data->pokelist_tbl );
	p_data->pokelist_tbl = NULL;
	CLACT_Delete( p_data->pokelist_icon );
	p_data->pokelist_icon = NULL;
	if(p_data->p_pokename){
		ZKN_FONTOAM_Delete( p_data->p_pokename );
		p_data->p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����l�[���e�[�u���`��@ONOFF
 *
 *	@param	p_data		�|�P�����l�[���e�[�u��
 *	@param	flag		�`��@ON�@OFF�@�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GlbPokeNameTblDrawFlagSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, BOOL flag )
{
	if( p_data->pokelist_tbl ){
		CLACT_SetDrawFlag( p_data->pokelist_tbl, flag );
	}
	if( p_data->pokelist_icon ){
		CLACT_SetDrawFlag( p_data->pokelist_icon, flag );
	}
	if( p_data->p_pokename->p_fontoam ){
		FONTOAM_SetDrawFlag( p_data->p_pokename->p_fontoam, flag );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���@���\�[�X�ǂݍ��ݏ���
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorResInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw );

	
	// �J�[�\���p���\�[�X
	// �L�����N�^�f�[�^�ǂݍ���
	p_cursor->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_lzh_NCGR, TRUE,
			ZKN_CUSOR_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_cursor->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_NCLR, FALSE, 
			ZKN_CUSOR_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_CURSOR_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_cursor->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_cursor_oam_sub_lzh_NCER, TRUE,
			ZKN_CUSOR_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_cursor->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_cursor_oam_sub_lzh_NANR, TRUE,
			ZKN_CUSOR_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�����\�[�X�̔j��
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorResDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	CLACT_U_CharManagerDelete( p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_cursor->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_cursor->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_cursor->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_cursor->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			p_cursor->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�� �A�N�^�[�̓o�^
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorActInit( ZKN_GLB_DRAWDATA* p_draw, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	int i;
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			ZKN_CUSOR_RES_ID,
			ZKN_CUSOR_RES_ID, 
			ZKN_CUSOR_RES_ID,
			ZKN_CUSOR_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_draw->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	add.mat.y		= SUB_SURFACE_Y + (100 * FX32_ONE);	// 0���Ə��ʂɈڂ邽��
	add.mat.x		= (100 * FX32_ONE);

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		p_cursor->cursor[i] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_cursor->cursor[i], i );
	}
	ZKN_UTIL_CursorSetDrawFlag( p_cursor, FALSE );


	// �J�[�\���A�j���o�^
	ZknCursorAnmAdd( p_draw );

	// �J�[�\������^�X�N�o�^
	ZknCursorMoveTcbAdd( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���A�N�^�[�̔j��
 *		
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorActDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	int i;
	ZKN_UTIL_CURSOR_OBJ* p_cursor = &p_draw->cursor;

	// �J�[�\������A�j���j��
	ZknCursorMoveTcbDelete( p_draw );

	// �J�[�\���A�j���j��
	ZknCursorAnmDelete( p_draw );

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		CLACT_Delete( p_cursor->cursor[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӃJ�[�\���A�j���^�X�N�o�^
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmAdd( ZKN_GLB_DRAWDATA* p_draw )
{
	p_draw->cursor_anm_tcb = TCB_Add( ZknCursorAnmTcb, &p_draw->cursor, ZKN_CORSOR_ANM_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���A�j���j��
 *
 *	@param	p_draw
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	TCB_Delete( p_draw->cursor_anm_tcb );
}	

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӃJ�[�\���A�j���^�X�N
 *
 *	@param	tcb
 *	@param	wrok 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorAnmTcb( TCB_PTR tcb, void* work )
{
	ZKN_UTIL_CURSOR_OBJ* p_cursor = work;
	int i;
	int size_x, size_y;
	fx32 calc;
	int count;
	
	// ��~���������`�F�b�N
	if( p_cursor->anm_stop ){
		ZknCursorSetMatrixLocal( p_cursor, p_cursor->x, p_cursor->y,
				p_cursor->size_x, p_cursor->size_y );
		return ;
	}

	p_cursor->anm_count = (p_cursor->anm_count + 1) % ZKN_CURSOR_ANM_COUNT_MAX;

	// �J�E���^�l���擾
	if( p_cursor->anm_count < ZKN_CURSOR_ANM_COUNT_HALF ){
		count = p_cursor->anm_count;
	}else{
		// 1�𑫂� ZKN_CURSOR_ANM_COUNT_HALF��==��count�ɂ��Ȃ����߂ɂ����
		// �s���B"=="�ɂȂ�Ƃ��̈�u�̂�size_x, y�̒l���ς���Ă��܂��A�����ڂ���
		count = ZKN_CURSOR_ANM_COUNT_MAX - (p_cursor->anm_count + 1);
	}

	// �T�C�Y�����߂�
	calc = FX_Mul( ZKN_CURSOR_ANM_DIS << FX32_SHIFT, count << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_CURSOR_ANM_COUNT_HALF << FX32_SHIFT );
	calc >>= FX32_SHIFT;
	size_x = p_cursor->size_x + calc;
	size_y = p_cursor->size_y + calc;

	ZknCursorSetMatrixLocal( p_cursor, p_cursor->x, p_cursor->y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W�ݒ�̂ݍs��
 *
 *	@param	p_obj
 *	@param	def_x
 *	@param	def_y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknCursorSetMatrixLocal( ZKN_UTIL_CURSOR_OBJ* p_obj, int def_x, int def_y, int size_x, int size_y )
{
	VecFx32 mat;
	int x, y;
	int i;

	for( i=0; i<ZKN_CURROS_MAT_RECT_NUM; i++ ){
		// ���W�擾
		ZKN_CURSOR_UTIL_GetRectMat( i, &x, &y, def_x, def_y, size_x, size_y );
		mat.x = x << FX32_SHIFT;
		mat.y = (y << FX32_SHIFT) + SUB_SURFACE_Y;

		//�@�ݒ�
		CLACT_SetMatrix( p_obj->cursor[ i ], &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���ړ��p�����[�^�ݒ�
 *
 *	@param	p_draw
 *	@param	x
 *	@param	y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------

static void ZknCursorMoveSet( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int size_x, int size_y )
{
	ZKN_UTIL_CURSOR_OBJ_MOVE* p_cursor_move = &p_draw->cursor_move;


	// ���̃^�[�Q�b�g���W�ƈႤ�Ƃ��̂ݐݒ�
	if( (p_cursor_move->ta_x == x) &&
		(p_cursor_move->ta_y == y) &&
		(p_cursor_move->ta_size_x == size_x) &&
		(p_cursor_move->ta_size_y == size_y) ){
		return;
	}

	//�@�J�[�\���|�C���^�ݒ�
	p_cursor_move->p_cursor = &p_draw->cursor;
	
	// ���̍��W�@�T�C�Y����V���W�T�C�Y�ɕύX����
	// ���W
	ZKN_UTIL_MoveReq( &p_cursor_move->mat_move,
			p_cursor_move->p_cursor->x, x,
			p_cursor_move->p_cursor->y, y,
			ZKN_CURSOR_MOVE_SYNC );

	// �T�C�Y
	ZKN_UTIL_MoveReq( &p_cursor_move->size_move,
			p_cursor_move->p_cursor->size_x, size_x,
			p_cursor_move->p_cursor->size_y, size_y,
			ZKN_CURSOR_MOVE_SYNC );


	p_cursor_move->ta_x = x;
	p_cursor_move->ta_y = y;
	p_cursor_move->ta_size_x = size_x;
	p_cursor_move->ta_size_y = size_y;

	// ����J�n
	p_cursor_move->move_stop = TRUE;

/*	OS_Printf( "	p_cursor_move->ta_x %d\n", p_cursor_move->ta_x );
	OS_Printf( "	p_cursor_move->ta_y %d\n", p_cursor_move->ta_y );
	OS_Printf( "	p_cursor_move->ta_size_x %d\n", p_cursor_move->ta_size_x );
	OS_Printf( "	p_cursor_move->ta_size_y %d\n", p_cursor_move->ta_size_y );//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���ړ�
 *
 *	@param	tcb		�^�X�N�f�[�^
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcb( TCB_PTR tcb, void* p_work )
{
	ZKN_UTIL_CURSOR_OBJ_MOVE* p_cursor_move = p_work;
	BOOL check;

	// ����������Ă��Ȃ���Γ��삵�Ȃ�
	if( p_cursor_move->move_stop == FALSE ){
		return ;
	}

	// ���삳����
	check = ZKN_UTIL_MoveMain( &p_cursor_move->mat_move );		
	ZKN_UTIL_MoveMain( &p_cursor_move->size_move );		


	//�@�l���ύX���ꂽ��
	// ���W�T�C�Y��ݒ�
	p_cursor_move->p_cursor->x = p_cursor_move->mat_move.x;
	p_cursor_move->p_cursor->y = p_cursor_move->mat_move.y;
	p_cursor_move->p_cursor->size_x = p_cursor_move->size_move.x;
	p_cursor_move->p_cursor->size_y = p_cursor_move->size_move.y;

	// �I��������I���
	if( check == TRUE ){
		p_cursor_move->move_stop = FALSE;
	}

/*	OS_Printf( "p_cursor_move->p_cursor->x %d\n", p_cursor_move->p_cursor->x );
	OS_Printf( "p_cursor_move->p_cursor->y %d\n", p_cursor_move->p_cursor->y );
	OS_Printf( "p_cursor_move->p_cursor->size_x %d\n", p_cursor_move->p_cursor->size_x );
	OS_Printf( "p_cursor_move->p_cursor->size_y %d\n", p_cursor_move->p_cursor->size_y );//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	����TCB��o�^����
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcbAdd( ZKN_GLB_DRAWDATA* p_draw )
{
	p_draw->cursor_move_tcb = TCB_Add( ZknCursorMoveTcb, &p_draw->cursor_move, ZKN_CORSOR_MOVE_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����TCB��j��
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknCursorMoveTcbDelete( ZKN_GLB_DRAWDATA* p_draw )
{
	TCB_Delete( p_draw->cursor_move_tcb );
	p_draw->cursor_move_tcb = NULL;
}
