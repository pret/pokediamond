//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_playsys.c
 *	@brief		�C���[�W�N���b�v�v���C���[
 *	@author		tomoya takahashi 
 *	@data		2005.12.27
 *
 *
 * �C���[�W�N���b�v�v���b�N���쐬���ĕ\������ȊO�̕��@��
 * �\������C���[�W�N���b�v�v���C���[
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <string.h>
#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "calc2d.h"
#include "include/system/lib_pack.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_rbox_player.h"
#include "include/system/arc_util.h"

#define __IMC_PLAYSYS_H_GLOBAL
#include "include/application/imageClip/imc_playsys.h"

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
#define IMC_PLAYSYS_OBJLIST_NUM	( IMC_RBOX_OBJ_CONTEST_MAX )
#define IMC_PLAYSYS_ACCE_NUM	( IMC_RBOX_ACCE_CONTEST_MAX )



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
typedef struct _IMC_PLAYERSYS{
	// �`��֌W
	IMC_DRAW_DATA drawSys;

	// �I�u�W�F�N�g���X�g�f�[�^
	IMC_OBJLIST_TBL	objListTbl;

	// �A�N�Z�T���f�[�^
	IMC_ACCESSORIE_OBJ_TBL* acce;

	// �E��ʃf�[�^
	IMC_RIGHT_BOX rbox;
	IMC_RBOX_PLAYER rbox_player;		// �E�{�b�N�X�v���C���[

	// �|�P�����f�[�^
	POKEMON_PARAM* poke_para;

	// �q�[�vID
	int		heap_id;

	// ���ݒ��S���W
	int x;
	int y;
	int center_ofs_x;	// ���S�܂ł̍��W
	int center_ofs_y;	// ���S�܂ł̍��W
	u16 rota_num;
	VecFx32 scale;
	GXRgb color;		// �S�̕`��J���[

	BOOL BG_use;				// BG�g�p�t���O

	BOOL draw_flag;			// �`��ON:TRUE OFF:FALSE
} IMC_PLAYERSYS;


//-------------------------------------
//	�E�{�b�N�X�@�������f�[�^
//=====================================
typedef struct {
	const IMC_SAVEDATA_POKEMON* p_poke;
	const IMC_SAVEDATA_ACCESSORIE* p_acce[ IMC_SAVEDATA_CONTEST_ACCE_NUM ];
	int acce_num;
	GF_BGL_INI* p_bg_ini;	// BG�V�X�e��	NOBG�̂Ƃ���NULL��OK
	int bg_id;				// BGID
							// GF_BGL_FRAME2_M�̃R���g���[���Z�b�g������ōs���܂��B
	int x;				// �S�̂̒��S
	int y;				// �S�̂̒��S
	int heap_id;		// �g�p����q�[�vID
} IMC_PLAYERSYS_INIT_LOCAL;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys( const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static IMC_PLAYERSYS_PTR initPlayerSys_NoBG( const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void initDrawSys( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void mainDrawSys( IMC_PLAYERSYS* p_sys );
static void deleteDrawSys( IMC_PLAYERSYS* p_sys );

static void initRightBox( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void initRightBoxBG( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );
static void deleteRightBox( IMC_PLAYERSYS* p_sys );
static void deleteRightBoxBG( IMC_PLAYERSYS* p_sys );

static void initWorkParam( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init );

static void setInitParamData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_PLAYERSYS_INIT* cp_param );
static void setTelevisionSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_TELEVISION_SAVEDATA* save_data );
static void setContestSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_CONTEST_SAVEDATA* save_data );

static void imc_draw_MakeLoadSWSP_player( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap );
static void loadAcceDataPlayer( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[����
 *
 *	@param	cp_init		�������f�[�^
 *	@param	save_data	�Z�[�u�f�[�^
 *
 *	@return	�������ꂽ�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;

	// �����f�[�^�ݒ�
	setInitParamData( &init_local, cp_init );

	// �Z�[�u�f�[�^�ݒ�
	setTelevisionSaveData( &init_local, save_data );
	
	return initPlayerSys( &init_local );
}

IMC_PLAYERSYS_PTR IMC_TelevisionPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;

	// �����f�[�^�ݒ�
	setInitParamData( &init_local, cp_init );

	// �Z�[�u�f�[�^�ݒ�
	setTelevisionSaveData( &init_local, save_data );
	
	return initPlayerSys_NoBG( &init_local );
}

IMC_PLAYERSYS_PTR IMC_ContestPlayerInit( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;
	
	// �����f�[�^�ݒ�
	setInitParamData( &init_local, cp_init );

	// �Z�[�u�f�[�^�ݒ�
	setContestSaveData( &init_local, save_data );
	
	return initPlayerSys( &init_local );
}

IMC_PLAYERSYS_PTR IMC_ContestPlayerInit_NoBG( const IMC_PLAYERSYS_INIT* cp_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	IMC_PLAYERSYS_INIT_LOCAL init_local;
	
	// �����f�[�^�ݒ�
	setInitParamData( &init_local, cp_init );

	// �Z�[�u�f�[�^�ݒ�
	setContestSaveData( &init_local, save_data );
	
	return initPlayerSys_NoBG( &init_local );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[���C��
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerMain( IMC_PLAYERSYS_PTR p_sys )
{
	if( p_sys->BG_use == TRUE ){
		// �E�{�b�N�X�v���C���[
		IMC_RBOX_PLAYER_Main( &p_sys->rbox_player );
	}

	// �`�揈��
	if( p_sys->draw_flag == TRUE ){
		mainDrawSys( p_sys );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���C���[�I��
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@retval	none
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerEnd( IMC_PLAYERSYS_PTR p_sys )
{
	// �E�{�b�N�X�j��
	if(p_sys->BG_use){
		deleteRightBoxBG( p_sys );
	}
	deleteRightBox( p_sys );

	// �A�N�Z�T���i�[�f�[�^�j��
	IMC_ACCE_ObjTblDelete( p_sys->acce );
	p_sys->acce = NULL;
	
	// �I�u�W�F�N�g���X�g�e�[�u���j��
	IMC_OBJLIST_TblDelete( &p_sys->objListTbl );
	
	// �`��V�X�e���j��
	deleteDrawSys( p_sys );

	// �|�P�����p�����[�^�j��
	sys_FreeMemoryEz( p_sys->poke_para );

	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank���Ԓ��ɌĂԊ֐�
 *
 *	@param	p_sys	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_PlayerVblank( IMC_PLAYERSYS_PTR p_sys )
{
	IMC_DRAW_VBlankPlayer( &p_sys->drawSys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�ݒ�
 *
 *	@param	p_sys	���[�N
 *	@param	flag	�`��t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag )
{
	p_sys->draw_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�擾
 *
 *	@param	p_sys	���[�N
 *
 *	@retval	TRUE	�`��
 *	@retval	FALSE	��`��
 */
//-----------------------------------------------------------------------------
BOOL IMC_Player_GetDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys )
{
	return p_sys->draw_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���`��@�t���OONOFF
 *	
 *	@param	p_sys		�V�X�e�����[�N
 *	@param	flag		�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetAcceDrawFlag( IMC_PLAYERSYS_PTR p_sys, BOOL flag )
{
	p_sys->drawSys.SWSP_DrawFlag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���`��@�t���O�擾
 *
 *	@param	p_sys		�V�X�e�����[�N
 *
 *	@retval	TRUE	�`��
 *	@retval	FALSE	��`��
 */
//-----------------------------------------------------------------------------
BOOL IMC_Player_GetAcceDrawFlag( CONST_IMC_PLAYERSYS_PTR p_sys )
{
	return p_sys->drawSys.SWSP_DrawFlag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W��ݒ�
 *
 *	@param	p_sys	�V�X�e��
 *	@param	x		x���W
 *	@param	y		y���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	IMC_RBOX_ListMatSet( &p_sys->rbox, p_sys->x, p_sys->y, x, y );

	//�@BG���g���Ă���Ƃ���BG�ʂ��ݒ�
	if( p_sys->BG_use ){
		GF_BGL_ScrollSet( p_sys->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_SET, IMC_RBOX_AREA_X - x );
		GF_BGL_ScrollSet( p_sys->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, IMC_RBOX_AREA_Y - y );
	}
	
	p_sys->x = x;
	p_sys->y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��],�g�厞�̒��S�I�t�Z�b�g�l��ݒ�
 *
 *	@param	p_sys	���[�N
 *	@param	x		���I�t�Z�b�g
 *	@param	y		���I�t�Z�b�g
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetRotScaleCenterOfs( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	p_sys->center_ofs_x = x;
	p_sys->center_ofs_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]�e�ݒ�
 *
 *	@param	p_sys		���[�N
 *	@param	rota		��]�p
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetRota( IMC_PLAYERSYS_PTR p_sys, u16 rota )
{
	p_sys->rota_num = rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g��k���l�ݒ�
 *
 *	@param	p_sys	���[�N
 *	@param	x		���g��
 *	@param	y		���g��
 *	@param	z		���g��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetScale( IMC_PLAYERSYS_PTR p_sys, fx32 x, fx32 y, fx32 z )
{
	p_sys->scale.x = x;
	p_sys->scale.y = y;
	p_sys->scale.z = z;
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����𒆐S�Ƃ������W�ƒ��S�I�t�Z�b�g�̐ݒ�
 *
 *	@param	p_sys	���[�N
 *	@param	x		�����W	�i�����͍���ł͂Ȃ��|�P�����̒��S���W�j
 *	@param	y		�����W	�i�����͍���ł͂Ȃ��|�P�����̒��S���W�j
 *
 *	@param	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPokeMatrix( IMC_PLAYERSYS_PTR p_sys, int x, int y )
{
	int pokex, pokey;
	int dis_x, dis_y;
	int pokesizx, pokesizy;
	int all_left, all_top;
	int c_x, c_y;

	// �|�P�����T�C�Y
	IMC_POKE_SizeGet( &p_sys->rbox.boxDraw.poke, &pokesizx, &pokesizy );

	//�@�|�P�������W
	IMC_RBOX_GetPokeMatrix( &p_sys->rbox, &pokex, &pokey );

	// �S�̂̈ړ��l�v�Z
	dis_x = x - pokex;
	dis_y = y - pokey;

	// �S�̂��ړ�
	all_left = p_sys->x + dis_x;
	all_top = p_sys->y + dis_y;
	IMC_Player_SetMatrix( p_sys, all_left, all_top );

	// ��]�@�g��@�̒��S���W��ݒ�
	c_x  = x - all_left; 
	c_y  = y - all_top; 
	IMC_Player_SetRotScaleCenterOfs( p_sys, c_x, c_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����̑��Ս��W��ݒ肷��
 *
 *	@param	p_sys	���[�N
 *	@param	x		�����W	�i�����͍���ł͂Ȃ��|�P�����̑������W�j
 *	@param	y		�����W	�i�����͍���ł͂Ȃ��|�P�����̑������W�j
 *	@param	height	���̃|�P�����̍���
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPokeMatrix_Ground( IMC_PLAYERSYS_PTR p_sys, int x, int y, int height )
{
	int oy;	// Y�I�t�Z�b�g�l
	fx32 scale_y_height;

	// ���S���瑫���܂ł̍����ɕύX
	height = (SOFT_SPRITE_SIZE_Y/2) - height;
	
	// ���S����̒l�̍��̊g��l�ł̒l�����߂�
	scale_y_height = FX_Mul( height * FX32_ONE, p_sys->scale.y );
	oy = scale_y_height >> FX32_SHIFT;

	IMC_Player_SetPokeMatrix( p_sys, x, y-oy );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��F�w��
 *
 *	@param	p_sys	�v���C���[�V�X�e��
 *	@param	color	�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetColor( IMC_PLAYERSYS_PTR p_sys, GXRgb color )
{
	p_sys->color = color;

	// �S�A�N�Z�T���A�|�P�����ɐF��ݒ�
	IMC_RBOX_SetObjColor( &p_sys->rbox, color );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��F�@�擾
 *
 *	@param	p_sys	�v���C���[�V�X�e��
 *
 *	@return	�F
 */
//-----------------------------------------------------------------------------
GXRgb IMC_Player_GetColor( CONST_IMC_PLAYERSYS_PTR cp_sys )
{
	return cp_sys->color;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�D�揇�ʂ�ݒ�	�擪�̃A�N�Z�T���̗D�揇��
 *
 *	@param	p_sys	���[�N
 *	@param	pri		�D�揇��
 */
//-----------------------------------------------------------------------------
void IMC_Player_SetPriority( IMC_PLAYERSYS_PTR p_sys, int pri )
{
	IMC_RBOX_SetObjPriorityMC( &p_sys->rbox, pri );
}

void IMC_Player_AddPriority( IMC_PLAYERSYS_PTR p_sys, int pri )
{
	IMC_RBOX_AddObjPriorityMC( &p_sys->rbox, pri );
}



//-----------------------------------------------------------------------------
/**
 *
 *			�v���C�x�[�g�֐�
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�v���C���[�V�X�e���쐬
 *
 *	@param	cp_init		�������f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys( const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_PLAYERSYS* p_sys;		// �C���[�W�N���b�v���[�N
	BOOL	check;				// �����p


	// �V�X�e�����[�N����
	p_sys = sys_AllocMemory( cp_init->heap_id, sizeof(IMC_PLAYERSYS) );
	memset( p_sys, 0, sizeof(IMC_PLAYERSYS) );

	// �q�[�vID
	p_sys->heap_id	= cp_init->heap_id;
	p_sys->poke_para = PokemonParam_AllocWork( cp_init->heap_id );
	ImcSaveData_GetUtilPokePara( cp_init->p_poke, p_sys->poke_para );

	// �`��f�[�^�ݒ���s���܂��B
	initDrawSys( p_sys, cp_init );
	// BG�ʂ��g�p����̂ŁA�\��
	IMC_DRAW_InitSysPlayerBG( &p_sys->drawSys, cp_init->p_bg_ini, cp_init->heap_id );

	// �I�u�W�F�N�g���X�g�e�[�u���쐬
	IMC_OBJLIST_TblInit( &p_sys->objListTbl, IMC_PLAYSYS_OBJLIST_NUM, cp_init->heap_id );
	
	// �A�N�Z�T���i�[�f�[�^�쐬
	p_sys->acce = IMC_ACCE_ObjTblInit( IMC_PLAYSYS_ACCE_NUM, cp_init->heap_id );

	// �E�{�b�N�X�f�[�^�쐬
	initRightBox( p_sys, cp_init );
	initRightBoxBG( p_sys, cp_init );

	// �E�{�b�N�X�v���C���[�ɓo�^
	IMC_RBOX_PLAYER_Init( &p_sys->rbox_player, &p_sys->rbox, cp_init->heap_id );

	p_sys->BG_use = TRUE;
	p_sys->draw_flag = TRUE;

	// ���W�Ȃǂ̏����f�[�^���
	initWorkParam( p_sys, cp_init );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�v���C���[�V�X�e���쐬		BG�Ȃ�Ver
 *
 *	@param	cp_init		�������f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static IMC_PLAYERSYS_PTR initPlayerSys_NoBG( const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_PLAYERSYS* p_sys;		// �C���[�W�N���b�v���[�N
	BOOL	check;				// �����p

	// �V�X�e�����[�N����
	p_sys = sys_AllocMemory( cp_init->heap_id, sizeof(IMC_PLAYERSYS) );
	memset( p_sys, 0, sizeof(IMC_PLAYERSYS) );

	// �q�[�vID
	p_sys->heap_id	= cp_init->heap_id;
	p_sys->poke_para = PokemonParam_AllocWork( cp_init->heap_id );
	ImcSaveData_GetUtilPokePara( cp_init->p_poke, p_sys->poke_para );

	// �`��f�[�^�ݒ���s���܂��B
	initDrawSys( p_sys, cp_init );

	// �I�u�W�F�N�g���X�g�e�[�u���쐬
	IMC_OBJLIST_TblInit( &p_sys->objListTbl, IMC_PLAYSYS_OBJLIST_NUM, cp_init->heap_id );
	
	// �A�N�Z�T���i�[�f�[�^�쐬
	p_sys->acce = IMC_ACCE_ObjTblInit( IMC_PLAYSYS_ACCE_NUM, cp_init->heap_id );

	// �E�{�b�N�X�f�[�^�쐬
	initRightBox( p_sys, cp_init );

	p_sys->BG_use = FALSE;
	p_sys->draw_flag = TRUE;


	// ���W�Ȃǂ̏����f�[�^���
	initWorkParam( p_sys, cp_init );

	return p_sys;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���f�[�^�쐬
 *
 *	@param	p_sys			�C���[�W�N���b�v�v���C���[�V�X�e��
 *	@param	cp_init			�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initDrawSys( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_DRAW_LOADRES_DATA loadData;	// �摜�f�[�^�ǂݍ��݃f�[�^

	// ��ʃf�[�^�ݒ�
//	IMC_DRAW_SetUp();

	// �`��V�X�e���쐬
	// �v���C���[�p�������֐����쐬���Ă���������
	// �ڍׁ@�K�v�ȕ`��V�X�e���̍쐬
	//	�\�t�g�E�F�A�X�v���C�g
	//	�A�N�Z�T���p�X�v���C�g�`��V�X�e��
	//	�A�N�Z�T���p�p���b�g�I�t�Z�b�g�e�[�u��
	SWSP_SYSDATA swsp;
	swsp.obj_num	= IMC_SPRITE_OBJ_NUM;
	swsp.char_num	= IMC_SPRITE_CHAR_NUM;
	swsp.pltt_num	= IMC_SPRITE_PLTT_NUM;
	swsp.heap		= cp_init->heap_id;
	IMC_DRAW_InitSysPlayer( &p_sys->drawSys, &swsp, cp_init->heap_id );

	// �`��f�[�^�쐬
	// �������v���C���[�p�������֐����쐬��
	// �A�N�Z�T���f�[�^����K�v�ȃe�N�X�`���A�p���b�g�̃e�[�u��
	// ���쐬
	imc_draw_MakeLoadSWSP_player( &p_sys->drawSys, &loadData, cp_init, cp_init->heap_id );

	// �`��f�[�^Vram�]��
	IMC_DRAW_LoadResource( &p_sys->drawSys, &loadData );

	// �`��f�[�^�j��
	IMC_DRAW_DestLoadSWSP( &loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e�����C���֐�
 *
 *	@param	p_sys	�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainDrawSys( IMC_PLAYERSYS* p_sys )
{
	IMC_DRAW_DrawSysPlayer( &p_sys->drawSys,
			p_sys->x + p_sys->center_ofs_x,
			p_sys->y + p_sys->center_ofs_y,
			p_sys->rota_num, &p_sys->scale );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��V�X�e���j���֐�
 *
 *	@param	p_sys	�C���[�W�N���b�v�v���C���[�V�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteDrawSys( IMC_PLAYERSYS* p_sys )
{
	// �`��f�[�^�j��
	IMC_DRAW_DeleteResource( &p_sys->drawSys );

	// �`��V�X�e���j��
	IMC_DRAW_DeleteSysPlayer( &p_sys->drawSys );
	if(p_sys->BG_use){
		IMC_DRAW_DeleteSysPlayerBG(&p_sys->drawSys);
	}

	// �`��ʐݒ�j��
//	IMC_DRAW_PutBack();
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�f�[�^�쐬
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *	@param	cp_init		�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBox( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	IMC_RIGHT_BOX_INIT	rbox_init;	// �E�{�b�N�X�������f�[�^
	int poke_x, poke_y, poke_pri;


	// �E�{�b�N�X�f�[�^�쐬
	// �`��f�[�^
	memset( &rbox_init, 0, sizeof(IMC_RIGHT_BOX_INIT) );
	rbox_init.SWSP_drawSys		= p_sys->drawSys.SWSP_drawSys;
	rbox_init.SWSP_charData		= p_sys->drawSys.SWSP_charData;
	rbox_init.SWSP_plttData		= p_sys->drawSys.SWSP_plttData;
	rbox_init.accePlttOfsTbl	= p_sys->drawSys.accePlttOfsTbl;
	rbox_init.SSM_drawSys		= p_sys->drawSys.SSM_drawSys;
	rbox_init.BG_Ini			= p_sys->drawSys.BG_Ini;

	rbox_init.acce		= p_sys->acce;			// �A�N�Z�T���f�[�^
	rbox_init.objListTbl= &p_sys->objListTbl;	// �I�u�W�F�N�g���X�g�e�[�u��
	rbox_init.acce_count_max = IMC_RBOX_OBJ_CONTEST_MAX;
	IMC_RBOX_InitSys( &p_sys->rbox, &rbox_init );
	
	// �|�P������o�^
	{
		SOFT_SPRITE_ARC	arc;
		poke_x = ImcSaveData_GetUtilPokeX( cp_init->p_poke );
		poke_y = ImcSaveData_GetUtilPokeY( cp_init->p_poke );
		poke_pri = ImcSaveData_GetUtilPokePri( cp_init->p_poke );
		IMC_RBOX_AddPokePlayer( &p_sys->rbox, p_sys->poke_para, &arc, poke_x, poke_y, poke_pri, cp_init->heap_id );
	}

	// �E�{�b�N�X�ɔz�u����f�[�^���쐬
	// �f�[�^����z�u���s���悤�ɂ���
	{
		int i;
		int x,y;
		int acce_no;
		s8 pri;
		for(i=0;i<cp_init->acce_num; i++){

			acce_no = ImcSaveData_GetUtilAcceNo( cp_init->p_acce[i] );
			x = ImcSaveData_GetUtilAcceMatX( cp_init->p_acce[i] );
			y = ImcSaveData_GetUtilAcceMatY( cp_init->p_acce[i] );
			pri = ImcSaveData_GetUtilAccePri( cp_init->p_acce[i] );
			
			// �E�A�N�Z�T���z�u
			IMC_RBOX_AddAccessorieEasy( &p_sys->rbox, acce_no, 
					x, y, pri );
		}
	}//*/

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�f�[�^�쐬		BG�ʏ�����
 *
 *	@param	p_sys		�C���[�W�N���b�v�v���C���[�V�X�e��
 *	@param	cp_init		�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBoxBG( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	// BG��\��
	// �f�[�^����BG�̃f�[�^NO��ݒ肷��
	IMC_RBOX_BGSet( &p_sys->rbox, cp_init->bg_id, cp_init->heap_id );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�{�b�N�X�f�[�^�j��
 *
 *	@param	p_sys 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteRightBox( IMC_PLAYERSYS* p_sys )
{
	// �E�{�b�N�X�z�u�f�[�^�j��
	IMC_RBOX_DeleteAccessorieAll( &p_sys->rbox );
	
	// �E�{�b�N�X�f�[�^�j��
	IMC_RBOX_DeleteSys( &p_sys->rbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�{�b�N�XBG
 *
 *	@param	p_sys 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void deleteRightBoxBG( IMC_PLAYERSYS* p_sys )
{
	// BG���N���[��
	IMC_RBOX_BGClean( &p_sys->rbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�f�[�^�̏����ݒ�
 *
 *	@param	p_sys	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initWorkParam( IMC_PLAYERSYS* p_sys, const IMC_PLAYERSYS_INIT_LOCAL* cp_init )
{
	// ���ݍ��W�ݒ�
	p_sys->x = IMC_RBOX_END_SX;
	p_sys->y = IMC_RBOX_END_SY;
	p_sys->center_ofs_x = (IMC_RBOX_AREA_WIDTH/2);
	p_sys->center_ofs_y = (IMC_RBOX_AREA_HEIGHT/2);

	// �X�P�[���l�ݒ�
	p_sys->scale.x = FX32_ONE;
	p_sys->scale.y = FX32_ONE;
	p_sys->scale.z = FX32_ONE;

	// ��]�p
	p_sys->rota_num = 0;

	// ���W�ݒ�
	IMC_Player_SetMatrix( p_sys, cp_init->x, cp_init->y );

	// �F
	p_sys->color = GX_RGB( 31,31,31 );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�������̒l����
 *
 *	@param	p_init		���������[�N
 *	@param	cp_param	�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setInitParamData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_PLAYERSYS_INIT* cp_param )
{
	p_init->p_bg_ini	= cp_param->p_bg_ini;
	p_init->x			= cp_param->x;
	p_init->y			= cp_param->y;
	p_init->heap_id		= cp_param->heap_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�A�N�Z�T���f�[�^�擾�֐�
 *
 *	@param	p_init		�i�[��
 *	@param	save_data	�Z�[�u�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setTelevisionSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_TELEVISION_SAVEDATA* save_data )
{
	int i;

	// �|�P����
	p_init->p_poke = ImcSaveData_GetTelevisionPokemon( save_data );
	
	// �A�N�Z�T��
	p_init->acce_num = 0;
	for( i=0; i<IMC_SAVEDATA_TELEVISION_ACCE_NUM; i++ ){
		// �A�N�Z�T���ݒ�`�F�b�N
		if( ImcSaveData_CheckTelevisionAcceDataSet( save_data, i ) ){
			p_init->p_acce[ p_init->acce_num ] = ImcSaveData_GetTelevisionAcce( save_data, i );
			p_init->acce_num ++;
		}
	}

	// BGID
	p_init->bg_id = ImcSaveData_GetTelevisionBgId( save_data );
}
//----------------------------------------------------------------------------
/**
 *	@brief	�R���e�X�g�A�N�Z�T���f�[�^�擾�֐�
 *
 *	@param	p_init		�i�[��
 *	@param	save_data	�Z�[�u�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setContestSaveData( IMC_PLAYERSYS_INIT_LOCAL* p_init, const IMC_CONTEST_SAVEDATA* save_data )
{
	int i;

	// �|�P����
	p_init->p_poke = ImcSaveData_GetContestPokemon( save_data );
	
	// �A�N�Z�T��
	p_init->acce_num = 0;
	for( i=0; i<IMC_SAVEDATA_CONTEST_ACCE_NUM; i++ ){
		// �A�N�Z�T���ݒ�`�F�b�N
		if( ImcSaveData_CheckContestAcceDataSet( save_data, i ) ){
			p_init->p_acce[ p_init->acce_num ] = ImcSaveData_GetContestAcce( save_data, i );
			p_init->acce_num ++;
		}
	}

	// BGID
	p_init->bg_id = ImcSaveData_GetContestBgId( save_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�v���C�g�p�̓ǂݍ��ރt�@�C�����쐬	�C���[�W�N���b�v�v���C���[�p
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	loadData	�쐬��
 *	@param	pp_acce		�A�N�Z�T���f�[�^�e�[�u��
 *	@param	acce_num	�A�N�Z�T����
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_draw_MakeLoadSWSP_player( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap )
{
	// SWSP�̃��\�[�X�o�^�f�[�^���������m��
	IMC_DRAW_SWSPResDataAllocMemory( loadData, heap );
	
	// �A�N�Z�T���p���\�[�X
	loadAcceDataPlayer( drawData, loadData, cp_init, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���f�[�^�̍쐬�@�v���C���[�ȂǗp
 *
 *	@param	drawData		�`��V�X�e���f�[�^
 *	@param	loadData		�ǂݍ��݃f�[�^�i�[��
 *	@param	pp_acce		�A�N�Z�T���f�[�^�e�[�u��
 *	@param	acce_num	�A�N�Z�T����
 *	@param	heap			�g�p����q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadAcceDataPlayer( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData, const IMC_PLAYERSYS_INIT_LOCAL* cp_init, int heap )
{
	int i;			// ���[�v�p
	int cont_id;	// �f�[�^�o�^��ID
	void* buff;
	int acce_no;

	// �A�N�Z�T���p�f�[�^�ǂݍ���
	for(i=0; i<cp_init->acce_num; i++ ){
		acce_no = ImcSaveData_GetUtilAcceNo( cp_init->p_acce[i] );

		// �Ǘ�ID�擾
		cont_id = IMC_ACCE_CHAR_CONT_ID( acce_no );
		
		// �������̂�o�^�ς݂łȂ����`�F�b�N
		if( RESM_CheckID( loadData->SWSP_charRes, cont_id ) == TRUE ){
			
			// �L�����N�^�f�[�^�擾
			buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
					IMC_ACCE_ARC_NO_GET( acce_no ),
					FALSE, heap, ALLOC_BOTTOM);

			// ���\�[�X�}�l�[�W���ɓo�^
			RESM_AddResNormal( loadData->SWSP_charRes, buff, cont_id );		

			// �A���p�b�N��̃f�[�^��o�^
			NNS_G2dGetUnpackedCharacterData( buff, &loadData->SWSP_charTbl[ cont_id ].res_file );
			
			// �X�v���C�g�`��V�X�e���|�C���^�ݒ�
			loadData->SWSP_charTbl[ cont_id ].s_sys = drawData->SWSP_drawSys;
		}
	}

	// �p���b�g�f�[�^�o�^
	buff = ArcUtil_Load(ARC_IMAGECLIP_GRA,
			IMC_DRAW_ACCESSORIE_PLTT_ARC, FALSE, heap, ALLOC_BOTTOM);
	
	// ���\�[�X�}�l�[�W���ɓo�^
	RESM_AddResNormal( loadData->SWSP_plttRes, buff, IMC_DRAW_ACCESSORIE_PLTT_ID );		
	
	// �A���p�b�N
	NNS_G2dGetUnpackedPaletteData( buff,
			&loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].res_file );

	// �`��V�X�e���f�[�^
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].s_sys = drawData->SWSP_drawSys;

	// �ǂݍ��݂���
	loadData->SWSP_plttTbl[ IMC_DRAW_ACCESSORIE_PLTT_ID ].load_num = IMC_DRAW_ACCESSORIE_PLTT_NUM;
	
}




#ifdef PM_DEBUG
#include "include/system/wipe.h"
#include "include/gflib/display.h"
#include "include/gflib/gf_gx.h"
#include "include/application/imageClip/imc_drawsys.h"

//-------------------------------------
//	�C���[�W�N���b�v�O���f�[�^
//=====================================
typedef struct {
	// �C���[�W�N���b�v�Z�[�u�̈�
	const IMC_TELEVISION_SAVEDATA* p_imc_one_data;
	GF_BGL_INI*		BG_Ini;
	IMC_PLAYERSYS_PTR p_player;
} IMC_PLAY_WORK;

// VBlank
static void IMC_PlayTelevision_Vblank( void* p_work )
{
	IMC_PLAY_WORK* p_ip = p_work;

	IMC_PlayerVblank( p_ip->p_player );
	GF_BGL_VBlankFunc( p_ip->BG_Ini );
}

// �`�F�b�N�p�v���b�N
PROC_RESULT IMC_PlayTelevision_ProcInit( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip;
	IMC_PROC_PLAY_WORK* p_proc_w;
	
	// �q�[�v�쐬
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// �C���[�W�N���b�v���[�N�쐬
	p_ip = PROC_AllocWork( proc, sizeof( IMC_PLAY_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( p_ip, 0, sizeof( IMC_PLAY_WORK ) );

	// V�u�����NH�u�����N�֐��ݒ�
	sys_VBlankFuncChange( IMC_PlayTelevision_Vblank, p_ip );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// �O������̃f�[�^���擾
	p_proc_w = PROC_GetParentWork( proc );

	// �`��֌W
	IMC_DRAW_SetUp();
	
	p_ip->BG_Ini = GF_BGL_BglIniAlloc( HEAPID_IMAGECLIP_DRAW );

	{
		IMC_PLAYERSYS_INIT init;
		init.p_bg_ini = p_ip->BG_Ini;
		init.x		  = 80;
		init.y		  = 16;
		init.heap_id  = HEAPID_IMAGECLIP_DRAW;
		p_ip->p_player = IMC_TelevisionPlayerInit( &init, p_proc_w->p_imc_one_data );
	}

	return PROC_RES_FINISH;
}

PROC_RESULT IMC_PlayTelevision_ProcMain( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip = PROC_GetWork( proc );
	
/*	static GXRgb color;

	if( sys.cont & PAD_BUTTON_L ){ OS_Printf( "color %x\n", ++color ); }
	if( sys.cont & PAD_BUTTON_R ){ OS_Printf( "color %x\n", --color ); }
	IMC_Player_SetColor( p_ip->p_player, color );//*/

	{
		//�R�c�`��J�n
		GF_G3X_Reset();

		NNS_G2dSetupSoftwareSpriteCamera();

		IMC_PlayerMain( p_ip->p_player );

		/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
	}



	switch( *seq ){
	case 0:
		(*seq) ++;
		break;

	case 1:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;
	
	case 2:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;

	case 3:
		if( sys.trg & PAD_BUTTON_A ){
			IMC_Player_SetAcceDrawFlag( p_ip->p_player, FALSE );
		}
		if( sys.trg & PAD_BUTTON_Y ){
			IMC_Player_SetAcceDrawFlag( p_ip->p_player, TRUE );
		}
		if( sys.trg & PAD_BUTTON_B ){
			(*seq)++;
		}
		break;

	case 4:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;

	case 5:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	return PROC_RES_CONTINUE;
}

PROC_RESULT IMC_PlayTelevision_ProcEnd( PROC* proc, int* seq )
{
	IMC_PLAY_WORK* p_ip = PROC_GetWork( proc );

	IMC_PlayerEnd( p_ip->p_player );

	// �`��V�X�e���j��
	sys_FreeMemoryEz( p_ip->BG_Ini );

	// �`��ʐݒ�j��
	IMC_DRAW_PutBack();

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// ���[�N�j��
	PROC_FreeWork( proc );

	// �q�[�v�j��
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );

	return PROC_RES_FINISH;
}

#endif

