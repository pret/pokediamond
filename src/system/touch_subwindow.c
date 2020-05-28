//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		touch_subwindow.c
 *	@brief		�T�u��ʁ@�G���E�B���h�E�{�^���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/gflib/button_man.h"

#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/touch_subwindow.naix"

#include "include/system/snd_tool.h"

#define __TOUCH_SUBWINDOW_H_GLOBAL 
#include "include/system/touch_subwindow.h"

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
// �e�o�b�t�@�E���[�N�̐�
enum{		
	TOUCH_SW_BUF_YES,
	TOUCH_SW_BUF_NO,
	TOUCH_SW_BUF_NUM,


	TOUCH_SW_BUF_NO_TOUCH,	// �^�b�`���ꂽ���`�F�b�N���̐G���Ă��Ȃ��萔
};
#define TOUCH_SW_Y_OFS	( 32 )	// NO�̕��̃I�t�Z�b�g

// �A�j���[�V�����֌W
#define TOUCH_SW_ANIME_NUM		( 4 )		// �A�j���[�V������
#define TOUCH_SW_ANIME_SP		( FX32_ONE )// �A�j���X�s�[�h
#define TOUCH_SW_ANIME_TIMING	( FX32_ONE * 1 )

// ���̃��[�N���̏��
enum{
	TOUCH_SW_PARAM_NODATA,	// ��
	TOUCH_SW_PARAM_DO,		// ���s�f�[�^�i�[
};

// VRAM�]���^�X�N
#define TOUCH_SW_VRAM_TRANS_TSK_PRI	( 128 )

#define TOUCH_FLG_INIT	( 0x8 )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�A�j���f�[�^
//=====================================
typedef struct {
	const fx32* cp_anime_tbl;
	u32 tbl_num;
	fx32 frame;
} TOUCH_SW_ANIME;


//-------------------------------------
//	�{�^���f�[�^�������f�[�^
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	u32 bg_frame;			// BG�i���o�[
	u32 fileidx;	// �A�[�J�C�u�t�@�C��
	u32 scrn_arcidx[ TOUCH_SW_ANIME_NUM ];	// �X�N���[���f�[�^
	u32 char_offs;	// �L�����N�^�I�t�Z�b�g
	u32 pltt_offs;	// �p���b�g�I�t�Z�b�g
	const fx32* cp_anime_tbl;	// �A�j���e�[�u��
	u32 tbl_num;				// �e�[�u����
	u8 ofs_x;		// ��
	u8 ofs_y;		// ��
} TOUCH_SW_BUTTON_PARAM;

//-------------------------------------
//	1�{�^���f�[�^
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	u32 bg_frame;			// BG�i���o�[
	void* p_scrn_buff[ TOUCH_SW_ANIME_NUM ];		// �X�N���[���o�b�t�@
	NNSG2dScreenData* p_scrn[ TOUCH_SW_ANIME_NUM ];	// �X�N���[���f�[�^
	TOUCH_SW_ANIME anime;
	u8 ofs_x;	// �����W
	u8 ofs_y;	// �����W
	u8 anm_idx;	// ���̔��f����Ă���X�N���[��IDX
	u8 dummy1;
} TOUCH_SW_BUTTON;

//-------------------------------------
//	�L�����N�^�f�[�^�]���^�X�N
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	NNSG2dCharacterData* p_char;
	void* p_buff;	
	int bg_frame;
	int char_ofs;
} TOUCH_SW_CHARACTER_TRANS;

//-------------------------------------
//	V�u�����N�@�p���b�g�f�[�^�]���^�X�N
//=====================================
typedef struct {
	NNSG2dPaletteData* p_pltt;
	void* p_buff;	
	int pltype;	// �p���b�g�]����
	int ofs;
	int size;
} TOUCH_SW_PALETTE_TRANS;


//-------------------------------------
//	�V�X�e�����[�N
//=====================================
typedef struct _TOUCH_SW_SYS{
	BUTTON_MAN* p_button_man;// �{�^���}�l�[�W��
	TP_HIT_TBL hit_tbl[ TOUCH_SW_BUF_NUM ];		// �{�^���f�[�^
	TOUCH_SW_BUTTON button[ TOUCH_SW_BUF_NUM ];	// �{�^���f�[�^
	GF_BGL_INI* p_bgl;		// BGL�V�X�e�����[�N
	u32 bg_frame;			// BG�i���o�[
	u32 heapid;				// �g�p�q�[�vID
	fx32 anime_tbl[ TOUCH_SW_ANIME_NUM ];	// �A�j���e�[�u��
	u8 x;					// x���W�i��׸��P�ʁj
	u8 y;					// y���W�i��׸��P�ʁj
	u8 button_move_flag;	// �{�^������t���O
	u8 now_work_param : 4;	// ���݂̃��[�N���̏��
	u8 touch_flg: 4;		// �^�b�`�����u�Ԋ��m
};


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void TouchSW_CleanWork( TOUCH_SW_SYS* p_touch_sw, u32 heapid );

//-------------------------------------
//	������x�������܂Ƃ߂��֐�
//=====================================
static void TouchSW_SYS_CharTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_PlttTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_ButtonInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );
static void TouchSW_SYS_ButtonManaInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );

//-------------------------------------
//	�{�^������V�X�e��
//=====================================
static void TouchSW_ButtonCallBack( u32 button_no, u32 event, void* p_work );

//-------------------------------------
//	�{�^�����[�N����֐��S
//=====================================
static void TouchSW_ButtonInit( TOUCH_SW_BUTTON* p_bttn, const TOUCH_SW_BUTTON_PARAM* cp_param, u32 heapid );
static BOOL TouchSW_ButtonMain( TOUCH_SW_BUTTON* p_bttn );
static void TouchSW_ButtonDelete( TOUCH_SW_BUTTON* p_bttn );
static void TouchSW_FrameScrnSet( TOUCH_SW_BUTTON* p_bttn );


//-------------------------------------
//	�A�j���f�[�^����֐�
//=====================================
static void TouchSW_AnimeInit( TOUCH_SW_ANIME* p_anime, const fx32* cp_anime_tbl, u32 tbl_num );
static void TouchSW_AnimeAdd( TOUCH_SW_ANIME* p_anime, fx32 frame );
static void TouchSW_AnimeSet( TOUCH_SW_ANIME* p_anime, fx32 frame );
static fx32 TouchSW_AnimeGet( const TOUCH_SW_ANIME* cp_anime );
static u32 TouchSW_AnimeIdxGet( const TOUCH_SW_ANIME* cp_anime );

//-------------------------------------
//	�L�����N�^�f�[�^�@�p���b�g�f�[�^�]��
//=====================================
static void TouchSW_CharTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID );
static void TouchSW_PlttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
static void TouchSW_CharTransTsk( TCB_PTR tcb, void* p_work );
static void TouchSW_PlttTransTsk( TCB_PTR tcb, void* p_work );


//-------------------------------------
//	�X�N���[���̔��f���s��
//=====================================
static void TouchSW_ScrnSet( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int x, int y );
static void TouchSW_ScrnCharOfsSet( const NNSG2dScreenData* scrn, int char_offs );
static void TouchSW_ScrnPlttOfsSet( const NNSG2dScreenData* scrn, int pltt_offs );

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����[�N�쐬
 *	
 *	@param	heapid	�g�p�q�[�vID 
 *	
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
TOUCH_SW_SYS* TOUCH_SW_AllocWork( u32 heapid )
{
	TOUCH_SW_SYS* p_touch_sw;
	p_touch_sw = sys_AllocMemory( heapid, sizeof(TOUCH_SW_SYS) );

	// ���[�N������
	TouchSW_CleanWork( p_touch_sw, heapid );

	return p_touch_sw;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����[�N�j��
 *	
 *	@param	p_touch_sw	�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_FreeWork( TOUCH_SW_SYS* p_touch_sw )
{
	// ���s�f�[�^�i�[�ς݂Ȃ烊�Z�b�g
	if( p_touch_sw->now_work_param == TOUCH_SW_PARAM_DO ){
		TOUCH_SW_Reset( p_touch_sw );
	}
	sys_FreeMemoryEz( p_touch_sw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e��������
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *	@param	cp_param	�V�X�e������f�[�^
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_Init( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	
	// �f�[�^�i�[
	p_touch_sw->p_bgl		= cp_param->p_bgl;
	p_touch_sw->bg_frame	= cp_param->bg_frame;
	p_touch_sw->x			= cp_param->x;
	p_touch_sw->y			= cp_param->y;

	// �L�����N�^�f�[�^�]��
	TouchSW_SYS_CharTrans( p_touch_sw, cp_param );

	// �p���b�g�f�[�^�]��
	TouchSW_SYS_PlttTrans( p_touch_sw, cp_param );
	
	// �{�^���f�[�^������
	TouchSW_SYS_ButtonInit( p_touch_sw, cp_param );

	// �{�^���}�l�[�W��������
	TouchSW_SYS_ButtonManaInit( p_touch_sw, cp_param );

	// ���s�f�[�^�ێ�
	p_touch_sw->now_work_param = TOUCH_SW_PARAM_DO;

	// �^�b�`�t���O
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����C������
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// �����Ȃ�
 *	@retval	TOUCH_SW_RET_YES	// �͂�
 *	@retval	TOUCH_SW_RET_NO	// ������
 *	@retval	TOUCH_SW_RET_YES_TOUCH	// �͂��������u��
 *	@retval	TOUCH_SW_RET_NO_TOUCH	// �������������u��
 */
//-----------------------------------------------------------------------------
u32 TOUCH_SW_MainMC( TOUCH_SW_SYS* p_touch_sw )
{
	u32 ret;

	// �^�b�`�t���O������
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;

	ret = TOUCH_SW_Main( p_touch_sw );

	// �����ꂽ�u�Ԃ��Ԃ�
	if( ret == TOUCH_SW_RET_NORMAL ){
		if( p_touch_sw->touch_flg == BMN_EVENT_TOUCH ){
			if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_YES ){
				return TOUCH_SW_RET_YES_TOUCH;
			}else{
				return TOUCH_SW_RET_NO_TOUCH;
			}
		}
	}
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����C������
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// �����Ȃ�
 *	@retval	TOUCH_SW_RET_YES	// �͂�
 *	@retval	TOUCH_SW_RET_NO		// ������
 */
//-----------------------------------------------------------------------------
u32 TOUCH_SW_Main( TOUCH_SW_SYS* p_touch_sw )
{
	BOOL check;
	
	// ���s�f�[�^�ݒ�ς�
	GF_ASSERT( p_touch_sw->now_work_param == TOUCH_SW_PARAM_DO );
	
	// �G�����{�^���������Ƃ��̓{�^���}�l�[�W�������s
	if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_NO_TOUCH ){
		BMN_Main( p_touch_sw->p_button_man );
	}

	// �{�^����G���Ă�����G�����{�^���𓮍�
	check = FALSE;
	if( p_touch_sw->button_move_flag != TOUCH_SW_BUF_NO_TOUCH ){

		check = TouchSW_ButtonMain( &p_touch_sw->button[ p_touch_sw->button_move_flag ] );
	}

	// �A�j���I���̂Ƃ��͂͂��������������܂���
	if( check == TRUE ){
		if( p_touch_sw->button_move_flag == TOUCH_SW_BUF_YES ){
			return TOUCH_SW_RET_YES;
		}else{
			return TOUCH_SW_RET_NO;
		}
	}

	return TOUCH_SW_RET_NORMAL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e���f�[�^���Z�b�g	(Init�̑O�̏�Ԃɂ���@����Ȃ���������Ȃ�)
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void TOUCH_SW_Reset( TOUCH_SW_SYS* p_touch_sw )
{
	int i;
	
	// �{�^���}�l�[�W���j��
	BMN_Delete( p_touch_sw->p_button_man );

	// �{�^���f�[�^�j��
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){
		TouchSW_ButtonDelete( &p_touch_sw->button[ i ] );
	}

	// ���[�N������
	TouchSW_CleanWork( p_touch_sw, p_touch_sw->heapid );
}



//-----------------------------------------------------------------------------
/**
 *		static �֐�
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�̏�����
 *
 *	@param	p_touch_sw 
 *	@param	heapid
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_CleanWork( TOUCH_SW_SYS* p_touch_sw, u32 heapid )
{
	memset( p_touch_sw, 0, sizeof(TOUCH_SW_SYS) );

	p_touch_sw->now_work_param = TOUCH_SW_PARAM_NODATA;	// ��ID
	p_touch_sw->heapid = heapid;
	p_touch_sw->button_move_flag = TOUCH_SW_BUF_NO_TOUCH;
	p_touch_sw->touch_flg = TOUCH_FLG_INIT;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^�]������
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_CharTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	// �L�����N�^�f�[�^�]��
	TouchSW_CharTransReq( ARC_TOUCH_SUBWINDOW_GRA, NARC_touch_subwindow_yes_no_dutton_lzh_NCGR, 
			p_touch_sw->p_bgl, p_touch_sw->bg_frame, cp_param->char_offs,
			p_touch_sw->heapid );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^�]��
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_PlttTrans( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	u32 pal_type;
	if( p_touch_sw->bg_frame < GF_BGL_FRAME0_S ){
		pal_type = PALTYPE_MAIN_BG;
	}else{
		pal_type = PALTYPE_SUB_BG;
	}
	TouchSW_PlttTransReq( ARC_TOUCH_SUBWINDOW_GRA, NARC_touch_subwindow_yes_no_button_NCLR,
			pal_type,
			cp_param->pltt_offs * 32, TOUCH_SW_USE_PLTT_NUM * 32,
			p_touch_sw->heapid );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���f�[�^������
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_ButtonInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	int i,j;
	TOUCH_SW_BUTTON_PARAM bt_pr;

	// �{�^���A�j���f�[�^�쐬
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		p_touch_sw->anime_tbl[ i ] = TOUCH_SW_ANIME_TIMING * (i+1);
	}

	// �{�^���f�[�^�쐬
	bt_pr.ini		= p_touch_sw->p_bgl;
	bt_pr.bg_frame	= p_touch_sw->bg_frame;
	bt_pr.fileidx	= ARC_TOUCH_SUBWINDOW_GRA;
	bt_pr.char_offs = cp_param->char_offs;
	bt_pr.pltt_offs	= cp_param->pltt_offs;
	bt_pr.cp_anime_tbl = p_touch_sw->anime_tbl;
	bt_pr.tbl_num	= TOUCH_SW_ANIME_NUM;
	bt_pr.ofs_x		= p_touch_sw->x;
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){

		// �X�N���[���f�[�^�C���f�b�N�X�o�b�t�@�쐬
		for( j=0; j<TOUCH_SW_ANIME_NUM; j++ ){
			bt_pr.scrn_arcidx[ j ] = NARC_touch_subwindow_yes_button01_lzh_NSCR + (j * TOUCH_SW_BUF_NUM) + i;
		}

		// Y�I�t�Z�b�g�l
		bt_pr.ofs_y = (i*(TOUCH_SW_Y_OFS/8)) + p_touch_sw->y;

		// �p���b�g�I�t�Z�b�g
		bt_pr.pltt_offs += i;

		// �{�^��������
		TouchSW_ButtonInit( &p_touch_sw->button[i], &bt_pr, p_touch_sw->heapid );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���}�l�[�W��������
 *
 *	@param	p_touch_sw
 *	@param	cp_param 
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
static void TouchSW_SYS_ButtonManaInit( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param )
{
	int i;
	
	// �{�^�������蔻��f�[�^�쐬
	for( i=0; i<TOUCH_SW_BUF_NUM; i++ ){
		p_touch_sw->hit_tbl[ i ].rect.top	= (p_touch_sw->y*8) + (i*TOUCH_SW_Y_OFS);
		p_touch_sw->hit_tbl[ i ].rect.bottom = (p_touch_sw->y*8) + (i*TOUCH_SW_Y_OFS) + (TOUCH_SW_USE_SCRN_Y*8);
		p_touch_sw->hit_tbl[ i ].rect.left	= (p_touch_sw->x*8);
		p_touch_sw->hit_tbl[ i ].rect.right	= (p_touch_sw->x*8) + (TOUCH_SW_USE_SCRN_X*8);
	}
	
	p_touch_sw->p_button_man = BMN_Create( p_touch_sw->hit_tbl, TOUCH_SW_BUF_NUM, 
							TouchSW_ButtonCallBack, p_touch_sw, p_touch_sw->heapid );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���}�l�[�W���R�[���o�b�N
 *
 *	@param	button_no
 *	@param	event
 *	@param	p_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	TOUCH_SW_SYS* p_touch_sw = p_work;

	p_touch_sw->touch_flg = event;

	if( event == BMN_EVENT_TOUCH ){	
		// �G�����{�^���ۑ�
		p_touch_sw->button_move_flag = button_no;

		Snd_SePlay( SE_TOUCH_SUB_WIN );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^�����[�N������
 *
 *	@param	p_bttn		�{�^�����[�N
 *	@param	cp_param	�{�^���������f�[�^
 *	@param	heapid		�q�[�vID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonInit( TOUCH_SW_BUTTON* p_bttn, const TOUCH_SW_BUTTON_PARAM* cp_param, u32 heapid )
{
	int i;
	
	// �A�j���f�[�^�o�^
	TouchSW_AnimeInit( &p_bttn->anime, cp_param->cp_anime_tbl, cp_param->tbl_num );

	// �f�[�^���
	p_bttn->ini		= cp_param->ini;
	p_bttn->bg_frame= cp_param->bg_frame;
	p_bttn->ofs_x	= cp_param->ofs_x;
	p_bttn->ofs_y	= cp_param->ofs_y;

	// �X�N���[�����[�N�ǂݍ���
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		p_bttn->p_scrn_buff[i] = ArcUtil_ScrnDataGet( cp_param->fileidx, cp_param->scrn_arcidx[i], 
				TRUE, &p_bttn->p_scrn[ i ], heapid );

		// �L�����N�^�I�t�Z�b�g��ݒ�
		TouchSW_ScrnCharOfsSet( p_bttn->p_scrn[ i ], cp_param->char_offs );
		// �p���b�g�I�t�Z�b�g��ݒ�
		TouchSW_ScrnPlttOfsSet( p_bttn->p_scrn[ i ], cp_param->pltt_offs );
	}
	
	// �X�N���[���̔��f���s��
	TouchSW_FrameScrnSet( p_bttn );
	p_bttn->anm_idx = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^�����[�N�@����	�i�A�j���j
 *
 *	@param	p_bttn		�{�^�����[�N
 *
 *	@retval	TRUE	�{�^���̃A�j�����I������	
 *	@retval	FALSE	�{�^���̃A�j���r��
 */
//-----------------------------------------------------------------------------
static BOOL TouchSW_ButtonMain( TOUCH_SW_BUTTON* p_bttn )
{
	u32 new_anime = TouchSW_AnimeIdxGet( &p_bttn->anime );
	
	// �A�j����i�߁@�ŏI�A�j���t���[���ɍs������I���
	if( p_bttn->anm_idx != new_anime ){
		TouchSW_FrameScrnSet( p_bttn );
		p_bttn->anm_idx = new_anime;

	}

	// �A�j���I�����m
	if( new_anime == (p_bttn->anime.tbl_num - 1) ){
		return TRUE;
	}

	// �A�j����i�߂�
	TouchSW_AnimeAdd( &p_bttn->anime, TOUCH_SW_ANIME_SP );


	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���f�[�^�j��
 *
 *	@param	p_bttn		�{�^�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ButtonDelete( TOUCH_SW_BUTTON* p_bttn )
{
	int i;
	
	// �X�N���[���̈��������
	GF_BGL_ScrFill( p_bttn->ini, p_bttn->bg_frame, 0, 
			p_bttn->ofs_x, p_bttn->ofs_y,
			p_bttn->p_scrn[0]->screenWidth/8, p_bttn->p_scrn[0]->screenHeight/8, 0 );
	GF_BGL_LoadScreenV_Req( p_bttn->ini, p_bttn->bg_frame );

	// ���[�N�j��
	for( i=0; i<TOUCH_SW_ANIME_NUM; i++ ){
		sys_FreeMemoryEz( p_bttn->p_scrn_buff[ i ] );
	}

	memset( p_bttn, 0, sizeof( TOUCH_SW_BUTTON ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���̃t���[�����̃X�N���[����ݒ�
 *
 *	@param	p_bttn		�{�^�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_FrameScrnSet( TOUCH_SW_BUTTON* p_bttn )
{
	u32 idx = TouchSW_AnimeIdxGet( &p_bttn->anime );

	TouchSW_ScrnSet( p_bttn->ini, p_bttn->bg_frame,
			p_bttn->p_scrn[ idx ], p_bttn->ofs_x, p_bttn->ofs_y );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���f�[�^������
 *	
 *	@param	p_anime			�A�j�����[�N
 *	@param	cp_anime_tbl	�A�j���e�[�u��
 *	@param	tbl_num			�A�j���e�[�u����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeInit( TOUCH_SW_ANIME* p_anime, const fx32* cp_anime_tbl, u32 tbl_num )
{
	p_anime->cp_anime_tbl	= cp_anime_tbl;
	p_anime->tbl_num		= tbl_num;
	p_anime->frame			= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���t���[����i�߂�
 *
 *	@param	p_anime		�A�j�����[�N
 *	@param	frame		�t���[����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeAdd( TOUCH_SW_ANIME* p_anime, fx32 frame )
{
	p_anime->frame += frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���t���[����ݒ肷��
 *
 *	@param	p_anime		�A�j�����[�N
 *	@param	frame		�t���[����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_AnimeSet( TOUCH_SW_ANIME* p_anime, fx32 frame )
{
	p_anime->frame = frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���t���[�����擾
 *
 *	@param	cp_anime	�A�j�����[�N
 *
 *	@return	�t���[����	
 */
//-----------------------------------------------------------------------------
static fx32 TouchSW_AnimeGet( const TOUCH_SW_ANIME* cp_anime )
{
	return cp_anime->frame;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̃A�j���C���f�b�N�X�����擾
 *
 *	@param	cp_anime	�A�j�����[�N
 *
 *	@return	�A�j���C���f�b�N�X��	�i���Ԗڂ̃X�N���[����\�����邩�j
 */
//-----------------------------------------------------------------------------
static u32 TouchSW_AnimeIdxGet( const TOUCH_SW_ANIME* cp_anime )
{
	int i;

	for( i=0; i<cp_anime->tbl_num; i++ ){

		//�@���̃C���f�b�N�X�̍Ō�̒l�ȉ��̂Ƃ��͂��̃C���f�b�N�X
		if( cp_anime->cp_anime_tbl[ i ] >= cp_anime->frame ){
			return i;
		}
	}
	return cp_anime->tbl_num - 1;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^�]�����N�G�X�g
 *
 *	@param	fileIdx		�A�[�J�C�u�t�@�C���C���f�b�N�X
 *	@param	dataIdx		�f�[�^�C���f�b�N�X
 *	@param	bgl			BG�f�[�^
 *	@param	frm			�ڰуi���o�[
 *	@param	offs		�I�t�Z�b�g
 *	@param	heapID		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_CharTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID )
{
	TOUCH_SW_CHARACTER_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(TOUCH_SW_CHARACTER_TRANS) );
	memset( p_tw, 0, sizeof(TOUCH_SW_CHARACTER_TRANS) );

	// �L�����N�^�f�[�^�ǂݍ���
	p_tw->p_buff = ArcUtil_CharDataGet( fileIdx, dataIdx, TRUE, &p_tw->p_char, heapID );

	// �]���f�[�^�i�[
	p_tw->ini = bgl;
	p_tw->bg_frame = frm;
	p_tw->char_ofs = offs;

	// �^�X�N�o�^
	VWaitTCB_Add( TouchSW_CharTransTsk, p_tw, TOUCH_SW_VRAM_TRANS_TSK_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^�]�����N�G�X�g
 *
 *	@param	fileIdx		�A�[�J�C�u�t�@�C���C���f�b�N�X
 *	@param	dataIdx		�f�[�^�C���f�b�N�X
 *	@param	palType		�p���b�g�]����
 *	@param	offs		�I�t�Z�b�g
 *	@param	transSize	�]��size
 *	@param	heapID		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_PlttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	TOUCH_SW_PALETTE_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(TOUCH_SW_PALETTE_TRANS) );
	memset( p_tw, 0, sizeof(TOUCH_SW_PALETTE_TRANS) );

	// �L�����N�^�f�[�^�ǂݍ���
	p_tw->p_buff = ArcUtil_PalDataGet( fileIdx, dataIdx, &p_tw->p_pltt, heapID );

	// �]���f�[�^�i�[
	p_tw->pltype = palType;
	p_tw->ofs = offs;
	p_tw->size = transSize;

	// �^�X�N�o�^
	VWaitTCB_Add( TouchSW_PlttTransTsk, p_tw, TOUCH_SW_VRAM_TRANS_TSK_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�f�[�^�]���^�X�N
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_CharTransTsk( TCB_PTR tcb, void* p_work )
{
	TOUCH_SW_CHARACTER_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_char->pRawData, p_tw->p_char->szByte );
	GF_BGL_LoadCharacter( p_tw->ini, p_tw->bg_frame, 
			p_tw->p_char->pRawData, p_tw->p_char->szByte, p_tw->char_ofs );

	// ���������
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�f�[�^�]���^�X�N
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void TouchSW_PlttTransTsk( TCB_PTR tcb, void* p_work )
{
	TOUCH_SW_PALETTE_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_pltt->pRawData, p_tw->size );

	if( p_tw->pltype == PALTYPE_MAIN_BG ){
		GX_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}else if( p_tw->pltype == PALTYPE_SUB_BG ){
		GXS_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}

	// ���������
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N���[���f�[�^�]��
 *
 *	@param	bg_ini		BG�V�X�e�����[�N
 *	@param	frame		BG�i���o�[
 *	@param	scrn		�X�N���[�����[�N
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnSet( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int x, int y )
{
	// ��������
	GF_BGL_ScrWriteExpand(
				bg_ini, frame,
				x, y,
				scrn->screenWidth / 8, scrn->screenHeight / 8,
				scrn->rawData,
				0, 0,
				scrn->screenWidth / 8, scrn->screenHeight / 8 );
	
	GF_BGL_LoadScreenV_Req(bg_ini, frame );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�N���[���f�[�^�̃L�����N�^�l�[���̒l���I�t�Z�b�g�����炷
 *
 *	@param	scrn			�X�N���[���f�[�^
 *	@param	char_offs		�L�����N�^�I�t�Z�b�g	�L�����N�^�P��
 *
 *	@return	none
 *
 * �L�����N�^�l�[���ő�l�`�F�b�N�����Ă��Ȃ��̂Œ��ӂ��Ă�������
 *
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnCharOfsSet( const NNSG2dScreenData* scrn, int char_offs )
{
	int i;							// ���[�v�p
	u16* scrndata;					// �X�N���[���f�[�^
	int size = scrn->szByte / 2;	// ���[�v��	�Q=2byte
	
	// �X�N���[���f�[�^���
	scrndata = (u16*)scrn->rawData;
	for(i=0; i<size; i++){

		scrndata[ i ] += char_offs;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�I�t�Z�b�g���X�N���[���o�b�t�@�ɐݒ�
 *
 *	@param	scrn		�X�N���[���o�b�t�@
 *	@param	pltt_offs	�p���b�g�I�t�Z�b�g	(�p���b�g�{���P��)
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void TouchSW_ScrnPlttOfsSet( const NNSG2dScreenData* scrn, int pltt_offs )
{
	int i;							// ���[�v�p
	u16* scrndata;					// �X�N���[���f�[�^
	int size = scrn->szByte / 2;	// ���[�v��	�Q=2byte
	
	// �X�N���[���f�[�^���
	scrndata = (u16*)scrn->rawData;
	for(i=0; i<size; i++){

		scrndata[ i ] &= 0x0fff;
		scrndata[ i ] |= pltt_offs << 12;
	}
}
