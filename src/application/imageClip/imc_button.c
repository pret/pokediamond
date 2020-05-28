//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_button.c
 *	@brief		��ʉ��̃{�^������V�X�e��
 *	@author		tomoya takahashi 
 *	@data		2005.10.08
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "include/system/clact_util.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "msg_print.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "assert.h"
#include "system.h"
#include "string.h"
#include "pltt_manager.h"
#include "include/application/imageClip/imc_snd_def.h"

#define __IMC_BUTTON_H_GLOBAL
#include "include/application/imageClip/imc_button.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_BTTN_PRI	(2)

//-------------------------------------
//	
//	�G��ON	OFF�t���[����
//	
//=====================================
#define	IMC_BTTN_DRAW_OFF	(0)
#define	IMC_BTTN_DRAW_HALF	(1)
#define	IMC_BTTN_DRAW_ON	(2)
#define	IMC_BTTN_DRAW_HALF2	(3)


//-------------------------------------
//	
//	�t�H���g�{�^���̕�����I�t�Z�b�g�ʒu
//	
//=====================================
#define IMC_FONTBTTN_DRAW_X		(16)
#define IMC_FONTBTTN_DRAW_Y_OFF	(19)
#define IMC_FONTBTTN_DRAW_Y_ON	(15)
#define IMC_FONTBTTN_PLTT_OFS_OFF	(3)
#define IMC_FONTBTTN_PLTT_OFS_ON	(4)

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

static void imcBttnNoFunc( IMC_BUTTON* bttn, void* work );


//-----------------------------------------------------------------------------
/**
*		�C���[�W�N���b�v�p
*/
//-----------------------------------------------------------------------------
static void makeBttn( IMC_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, int x, int y, int sx, int sy );
static void makeFontBttn( IMC_FONT_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, CONST_FONTOAM_SYS_PTR fnt_sys, const GF_BGL_BMPWIN* bmp, int x, int y, int sx, int sy );
static void makeHitTbl( TP_HIT_TBL* p_hit, int bttn_no, int x, int y, int sx, int sy );

static void loadBttnRes( IMC_DRAW_DATA* drawData );
static void loadBttnEndCkRes( IMC_DRAW_DATA* drawData );
static void deleteBttnCharPltt( IMC_DRAW_DATA* drawData );

static GF_BGL_BMPWIN* getBttnStr( IMC_DRAW_DATA* drawData, u32 arcID, u32 dataID, u32 msgID, int bmp_x, int bmp_y );
static void deleteBttnStr( GF_BGL_BMPWIN* win );

static void IMCBTTN_normalAnm( IMC_BUTTON* bttn, int state );
static void IMCBTTN_sndStart( IMC_BUTTON* bttn, int se, int timing, int state );
static void IMC_BTTN_FontAnm( IMC_FONT_BUTTON* bttn, int state );

static void IMC_BTTN_Move( IMC_BUTTON* bttn, int x, int y );
static void IMC_FONTBTTN_Move( IMC_FONT_BUTTON* bttn, int x, int y );

// �R�[���o�b�N�֐�
static void IMC_IMCBTTN_Call( u32 button, u32 event, void* work );

// static void IMCBTTN_ace_bg_snd_anm( IMC_BUTTON_DATA* data, int flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���̏�����
 *
 *	@param	button		�{�^���I�u�W�F�̃|�C���^ 
 *	@param	init		�������f�[�^�\����		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_Init( IMC_BUTTON* button, IMC_BUTTON_INIT* init )
{

	GF_ASSERT( button );
	GF_ASSERT( init );

	button->clact_w = CLACT_Add( init->clact );
	GF_ASSERT( button->clact_w );

	// �f�[�^�i�[
	button->start_flg	= init->start_flg;
	button->work		= init->work;
	if(init->buttonFunc){
		button->func		= init->buttonFunc;
	}else{
		button->func		= imcBttnNoFunc;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������\��t���{�^���쐬
 *
 *	@param	button	������{�^��
 *	@param	init	�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FontBttnInit( IMC_FONT_BUTTON* button, IMC_FONT_BUTTON_INIT* init )
{
	FONTOAM_INIT fontoam_init;
	
	IMC_BTTN_Init( &button->button, &init->bttn_init );

	fontoam_init.fontoam_sys	= init->fntoam_sys;
	fontoam_init.bmp			= init->bmp;
	fontoam_init.clact_set		= init->bttn_init.clact->ClActSet;
	fontoam_init.pltt			= init->pltt;
	fontoam_init.parent			= button->button.clact_w;
	fontoam_init.char_ofs		= init->char_ofs;
	fontoam_init.x				= init->fnt_x;
	fontoam_init.y				= init->fnt_y;
	fontoam_init.bg_pri			= 0;
	fontoam_init.soft_pri		= 0;
	fontoam_init.draw_area		= init->bttn_init.clact->DrawArea;
	fontoam_init.heap			= init->bttn_init.clact->heap;

	button->font = FONTOAM_Init( &fontoam_init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���̔j��
 *
 *	@param	button	�{�^���I�u�W�F�N�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_Delete( IMC_BUTTON* button )
{
	// �A�N�^�[�j��
	CLACT_Delete( button->clact_w );

	// ������
	memset( button, 0, sizeof(IMC_BUTTON) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���g����t���{�^���j��
 *
 *	@param	button	�{�^���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FontBttnDelete( IMC_FONT_BUTTON* button )
{
	IMC_BTTN_Delete( &button->button );

	FONTOAM_Delete( button->font );

	memset( button, 0, sizeof(IMC_FONT_BUTTON) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���V�X�e�����C���֐�
 *
 *	@param	button	�{�^���\����
 *	@param	state	���̃{�^�����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_DoFunc( IMC_BUTTON* button, int state )
{
	// ����֐������s���邩�`�F�b�N
	if( state == button->start_flg ){

		button->func( button, button->work );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���@BG�@�ύX�{�^������������Ԃɂ���
 *
 *	@param	button			�{�^���\����
 *	@param	button_no		�{�^���i���o�[
 *
 *	@return	none
 *
 * button_no
	IMC_BTTN_ACE,		// �A�N�Z�T���ύX�Ɉڂ�
	IMC_BTTN_BG,		// BG�ύX�Ɉڂ�
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_OnAB( IMC_BUTTON_DATA* button, int button_no, int event )
{
	int i;		// ���[�v�p
	IMC_BUTTON* bttn;	
	
	// flg�̃I�u�W�F�N�g�͉����ꂽ�G��
	// ���̑��̃I�u�W�F�N�g�̃{�^���𗣂�����Ԃɂ���
	for( i=IMC_BTTN_ACE; i<=IMC_BTTN_BG; i++ ){

		bttn = button->bttn + i;
		
		if( i != button_no ){
			// �������G�ɂ���
			IMC_BTTN_PopGra( bttn );
		}else{
			if( event == IMC_BTTN_PUSH_F ){
				// �������G�ɂ���
				IMC_BTTN_HalfGra( bttn );
				// �{�^������������
				Snd_SePlay( IMC_SE_BUTTON_ON );
			}else if( event == IMC_BTTN_PUSH ){

				// �[��������
				IMC_BTTN_PushGra( bttn );
			}else{

				// �������G�ɂ���
				IMC_BTTN_HalfGra( bttn );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����֐����{�^���ɐݒ�
 *
 *	@param	button		�{�^���\����
 *	@param	func		����֐�
 *	@param	work		���[�N
 *	@param	start_flg	����֐����s�^�C�~���O
 *
 *	@return	none
 *
 *	start_flg
		IMC_BTTN_NOPUSH,		// ������Ă��Ȃ�
		IMC_BTTN_PUSH,			// ������Ă���
		IMC_BTTN_PUSH_F,		// �����ꂽ�u��
		IMC_BTTN_POP,			// �����ꂽ�u��
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_FuncSet( IMC_BUTTON* button, IMCBUTTON_FUNC func, void* work, int start_flg )
{
	GF_ASSERT( button );
	
	button->start_flg	= start_flg;
	button->work		= work;
	button->func		= func;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������Ȃ��֐�
 *
 *	@param	bttn
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void imcBttnNoFunc( IMC_BUTTON* bttn, void* work )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����ꂽ�Ƃ��̃G�t�F�N�g
 *
 *	@param	bttn	�{�^���\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_PushGra( IMC_BUTTON* bttn )
{
	// �G��������Ԃɂ���
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_ON );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����ꂽ�Ƃ��̃G�t�F�N�g
 *
 *	@param	bttn	�{�^���\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_PopGra( IMC_BUTTON* bttn )
{
	// �G�𗣂���Ԃɂ���
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_OFF );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���Ԃ̂Ƃ��̊G�ɂ���
 *
 *	@param	bttn	�{�^���\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BTTN_HalfGra( IMC_BUTTON* bttn )
{
	// �G�𒆊ԏ�Ԃɂ���
	CLACT_AnmFrameSet( bttn->clact_w, IMC_BTTN_DRAW_HALF );
}



//-----------------------------------------------------------------------------
/**
*			�C���[�W�N���b�v�p�֐��S
*	jump
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	
 *	@brief	�C���[�W�N���b�v�p�{�^���̍쐬
 *
 *	@param	button		�{�^���\����
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Init( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData )
{
	GF_BGL_BMPWIN* bmp;
	
	// OAM�t�H���g�V�X�e���쐬
	button->fntoam_sys = FONTOAM_SysInit( 1, HEAPID_IMAGECLIP_DATA );

	// ���\�[�X�ǂݍ���
	loadBttnRes( drawData );

	
	// �p���b�g���߂���{�^��
	// �`��f�[�^�Ɠ����蔻��e�[�u���̍쐬
	makeBttn( &button->bttn[ IMC_BTTN_RET ], IMC_BTTN_RET, drawData,
			IMC_BTTN_RET_X, IMC_BTTN_RET_Y,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_RET,
			IMC_BTTN_RET_X, IMC_BTTN_RET_Y + IMC_BTTN_HIT_Y_OFS,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// �p���b�g���߂����đO�ɖ߂��{�^��
	// �`��f�[�^�Ɠ����蔻��e�[�u���̍쐬
	makeBttn( &button->bttn[ IMC_BTTN_RETB ], IMC_BTTN_RETB, drawData,
			IMC_BTTN_RETB_X, IMC_BTTN_RET_Y,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_RETB,
			IMC_BTTN_RETB_X, IMC_BTTN_RET_Y + IMC_BTTN_HIT_Y_OFS,
			IMC_BTTN_RET_SIZE_X, IMC_BTTN_RET_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// �A�N�Z�T���ύX�Ɉڂ�{�^��
	// �`��f�[�^�Ɠ����蔻��e�[�u���̍쐬
	makeBttn( &button->bttn[ IMC_BTTN_ACE ], IMC_BTTN_ACE, drawData,
			IMC_BTTN_ACE_X, IMC_BTTN_Y,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_ACE,
			IMC_BTTN_ACE_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	// BG�ύX�Ɉڂ�{�^��
	// �`��f�[�^�Ɠ����蔻��e�[�u���̍쐬
	makeBttn( &button->bttn[ IMC_BTTN_BG ], IMC_BTTN_BG, drawData,
			IMC_BTTN_BG_X, IMC_BTTN_Y,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y);
	makeHitTbl( button->hit, IMC_BTTN_BG,
			IMC_BTTN_BG_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_NOR_SIZE_X, IMC_BTTN_NOR_SIZE_Y - IMC_BTTN_HIT_Y_OFS);
	
	
	// END�ύX�Ɉڂ�{�^��
	// �`��f�[�^�Ɠ����蔻��e�[�u���̍쐬
	// �t�H���g�f�[�^�ǂݍ���
	FontProc_LoadFont( FONT_BUTTON, HEAPID_IMAGECLIP_DRAW );
	// �������
	// �r�b�g�}�b�v�E�B���h�E�쐬
	bmp = getBttnStr( drawData, ARC_MSG, NARC_msg_imageclip_dat,
			imgclip_end,
			IMC_BTTN_END_SIZE_X / 8,
			IMC_BTTN_END_SIZE_Y / 8);
	// ��������{�^���쐬
	makeFontBttn( &button->bttn_end, IMC_BTTN_END, drawData, 
			button->fntoam_sys, bmp,
			IMC_BTTN_END_X, IMC_BTTN_Y,
			IMC_BTTN_END_SIZE_X, IMC_BTTN_END_SIZE_Y );
	makeHitTbl( button->hit, IMC_BTTN_END,
			IMC_BTTN_END_X, IMC_BTTN_Y + IMC_BTTN_HIT_Y_OFS_NOR_END,
			IMC_BTTN_END_SIZE_X, IMC_BTTN_END_SIZE_Y - IMC_BTTN_HIT_Y_OFS );
	// �������
	// �r�b�g�}�b�v�E�B���h�E�j��
	deleteBttnStr( bmp );
	// ������t�H���g�j��
	FontProc_UnloadFont( FONT_BUTTON );

	// �I���{�^���L��
	button->bttn_end_do = TRUE;
	
	// ���\�[�X�j��
	deleteBttnCharPltt( drawData );


	// �f�t�H���g�ŃA�N�Z�T���ύX�Ɉڂ�{�^����ύX
	IMC_BTTN_PushGra( &button->bttn[ IMC_BTTN_ACE ] );

	// �{�^���}�l�[�W���ɓo�^
	button->bttn_man = BMN_Create( button->hit, IMC_BTTN_MAX, IMC_IMCBTTN_Call, button, HEAPID_IMAGECLIP_DATA );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�p�{�^���̔j��
 *
 *	@param	button		�{�^���\����
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Delete( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData )
{
	int i;

	// �Z���A�Z���A�j���A�L�����N�^Vram�G���A�@�p���b�gVram�G���A���
	for( i=0;i<IMC_BTTN_MAX;i++ ){
		IMC_DRAW_CLACT_DeleteCellRes( drawData, i );
		IMC_DRAW_CLACT_DeleteCellAnmRes( drawData, i );
		DelChar( i );
	}
	DelPltt( IMC_BTTN_RES_MAN_PLTT );
	DelPltt( IMC_BTTN_RES_MAN_PLTT_FONT );

	for( i=0; i<IMC_BTTN_NORM_MAX; i++ ){
		IMC_BTTN_Delete( &button->bttn[ i ] );
	}

	// �t�H���g�f�[�^���g�p���Ă����L�����N�^�̈�j��
	CharVramAreaFree( &button->bttn_end.char_vram );
	
	IMC_BTTN_FontBttnDelete( &button->bttn_end );

	FONTOAM_SysDelete( button->fntoam_sys );

	// �{�^���}�l�[�W���j��
	BMN_Delete( button->bttn_man );
	button->bttn_man = NULL;
}

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�C���[�W�N���b�v�{�^�����C��
 *
 *	@param	button	�{�^�����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Main( IMC_BUTTON_DATA* button )
{
	GF_ASSERT( button->bttn_man );
	
	BMN_Main( button->bttn_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����I��
 *
 *	@param	button	�{�^��
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_EndEx( IMC_BUTTON_DATA* button )
{
	if( button->bttn_end_do == TRUE ){
		// �A�j��
		IMCBTTN_normalAnm( &button->bttn_end.button, IMC_BTTN_PUSH );
		// �I���{�^���̏ꍇ�̓t�H���g�f�[�^�̍��W��������
		IMC_BTTN_FontAnm( &button->bttn_end, IMC_BTTN_PUSH_F );
		// ����炷
		IMCBTTN_sndStart( &button->bttn_end.button, IMC_SE_BUTTON_ENDON, IMC_BTTN_PUSH_F, IMC_BTTN_PUSH );
		// ����
		IMC_BTTN_DoFunc( &button->bttn_end.button, button->bttn_end.button.start_flg );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j����ԃ��Z�b�g
 *
 *	@param	button 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Reset( IMC_BUTTON_DATA* button )
{
	IMCBTTN_normalAnm( &button->bttn_end.button, IMC_BTTN_AREA_OVER );
	IMC_BTTN_FontAnm( &button->bttn_end, IMC_BTTN_AREA_OVER );

	// �{�^����Ԑݒ�
	IMC_IMCBTTN_OnAB( button, IMC_BTTN_ACE, IMC_BTTN_AREA_OVER );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�S�{�^���𑫂��Z�ړ�������
 *
 *	@param	button		�{�^���\����
 *	@param	x			�������l
 *	@param	y			�������l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_Move( IMC_BUTTON_DATA* button, int x, int y )
{
	int i;			// ���[�v�p

	for(i=0; i<IMC_BTTN_NORM_MAX; i++ ){
		IMC_BTTN_Move( button->bttn + i, x, y );
	}
	IMC_FONTBTTN_Move( &button->bttn_end, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����֐���ݒ�
 *
 *	@param	button		�{�^���f�[�^
 *	@param	button_no	�{�^���i���o�[
 *	@param	func		����֐�
 *	@param	work		���[�N
 *	@param	start_flg	�֐������s����^�C�~���O
 *
 *	@return	none
 *
 *	start_flg
		IMC_BTTN_NOPUSH,		// ������Ă��Ȃ�
		IMC_BTTN_PUSH,			// ������Ă���
		IMC_BTTN_PUSH_F,		// �����ꂽ�u��
		IMC_BTTN_POP,			// �����ꂽ�u��
 *
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_FuncSet( IMC_BUTTON_DATA* button, int button_no, IMCBUTTON_FUNC func, void* work, int start_flg )
{
	GF_ASSERT( button );

	if( button_no < IMC_BTTN_NORM_MAX ){
		IMC_BTTN_FuncSet( 
				&button->bttn[ button_no ],
				func, work, 
				start_flg);
	}else{
		IMC_BTTN_FuncSet( 
				&button->bttn_end.button,
				func, work, 
				start_flg);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���̕\����\���ݒ�
 *
 *	@param	button		�{�^�����[�N
 *	@param	button_no	�{�^���i���o�[
 *	@param	flag		�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_IMCBTTN_DrawSet( IMC_BUTTON_DATA* button, int button_no, BOOL flag )
{
	GF_ASSERT( button );

	if( button_no < IMC_BTTN_NORM_MAX ){
		CLACT_SetDrawFlag( 
				button->bttn[ button_no ].clact_w, flag );
	}else{
		CLACT_SetDrawFlag( 
				button->bttn_end.button.clact_w, flag );
		FONTOAM_SetDrawFlag( 
				button->bttn_end.font, flag );

		if( flag == TRUE ){
			button->bttn_end_do = TRUE;
		}else{
			button->bttn_end_do = FALSE;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�p�{�^���R�[���o�b�N�֐�
 *
 *	@param	button		�{�^��ID
 *	@param	event		�C�x���g
 *	@param	work		���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_IMCBTTN_Call( u32 button, u32 event, void* work )
{
	IMC_BUTTON_DATA* data = work;
	
	switch( button ){
	case IMC_BTTN_RET:
		// �A�j��
		IMCBTTN_normalAnm( &data->bttn[ IMC_BTTN_RET ], event );
		// ����炷
		IMCBTTN_sndStart( &data->bttn[ IMC_BTTN_RET ], IMC_SE_RET_BUTTON_ON, IMC_BTTN_PUSH_F, event );
		// ����
		IMC_BTTN_DoFunc( &data->bttn[ IMC_BTTN_RET ], event );
		break;

	case IMC_BTTN_RETB:
		// �A�j��
		IMCBTTN_normalAnm( &data->bttn[ IMC_BTTN_RETB ], event );
		// ����炷
		IMCBTTN_sndStart( &data->bttn[ IMC_BTTN_RETB ], IMC_SE_RET_BUTTON_ON, IMC_BTTN_PUSH_F, event );
		// ����
		IMC_BTTN_DoFunc( &data->bttn[ IMC_BTTN_RETB ], event );
		break;
		
	case IMC_BTTN_ACE:
	case IMC_BTTN_BG:
		// �{�^����Ԑݒ�
		IMC_IMCBTTN_OnAB( data, button, event );
		// ����
		IMC_BTTN_DoFunc( &data->bttn[ button ], event );
		break;
		
	case IMC_BTTN_END:
		if( data->bttn_end_do == TRUE ){
			// �A�j��
			IMCBTTN_normalAnm( &data->bttn_end.button, event );
			// �I���{�^���̏ꍇ�̓t�H���g�f�[�^�̍��W��������
			IMC_BTTN_FontAnm( &data->bttn_end, event );
			// ����炷
			IMCBTTN_sndStart( &data->bttn_end.button, IMC_SE_BUTTON_ENDON, IMC_BTTN_PUSH_F, event );
			// ����
			IMC_BTTN_DoFunc( &data->bttn_end.button, event );
		}
		break;

	default:
		GF_ASSERT_MSG( 0, "�����ɂ���̂͂�������\n" );
		break;
	}
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���i���o�[�̃{�^���쐬
 *
 *	@param	bttn		�{�^���f�[�^
 *	@param	bttn_no		�{�^���i���o�[
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	sx			���T�C�Y
 *	@param	sy			���T�C�Y
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeBttn( IMC_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, int x, int y, int sx, int sy )
{
	IMC_BUTTON_INIT init;
	CLACT_HEADER head;
	CLACT_ADD	add;
	
	// �w�b�_�[�쐬
	CLACT_U_MakeHeader( 
			&head, 
			bttn_no, IMC_BTTN_RES_MAN_PLTT, 
			bttn_no, bttn_no,
			CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^�f�[�^�쐬
	add.ClActSet	= drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x		= x << FX32_SHIFT;
	add.mat.y		= y << FX32_SHIFT;
	add.mat.z		= 0;
	add.pri			= IMC_BTTN_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	init.clact	= &add;
	init.buttonFunc = NULL;
	init.work		= NULL;
	init.start_flg	= IMC_BTTN_POP;
	
	IMC_BTTN_Init( bttn, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���g�{�^��
 *
 *	@param	bttn		�t�H���g�{�^���f�[�^
 *	@param	bttn_no		�{�^���i���o�[	
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	fnt_sys		�t�H���g�V�X�e��
 *	@param	pltt		�p���b�g�v���N�V
 *	@param	bmp			�r�b�g�}�b�v�E�B���h�E
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	sx			���T�C�Y
 *	@param	sy			���T�C�Y
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeFontBttn( IMC_FONT_BUTTON* bttn, int bttn_no, IMC_DRAW_DATA* drawData, CONST_FONTOAM_SYS_PTR fnt_sys, const GF_BGL_BMPWIN* bmp, int x, int y, int sx, int sy )
{
	IMC_FONT_BUTTON_INIT init;
	CLACT_HEADER head;
	CLACT_ADD	add;
	CLACT_U_RES_OBJ_PTR pltt_obj;
	int char_size;
	BOOL check;

	
	// �Z���A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( 
			&head, 
			bttn_no, IMC_BTTN_RES_MAN_PLTT, 
			bttn_no, bttn_no,
			CLACT_U_HEADER_DATA_NONE,CLACT_U_HEADER_DATA_NONE,
			0, 0,
			drawData->resMan[ CLACT_U_CHAR_RES ],
			drawData->resMan[ CLACT_U_PLTT_RES ],
			drawData->resMan[ CLACT_U_CELL_RES ],
			drawData->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL );


	// �Z���A�N�^�[�o�^�f�[�^�쐬
	add.ClActSet	= drawData->clactSet;
	add.ClActHeader = &head;
	add.mat.x		= x << FX32_SHIFT;
	add.mat.y		= y << FX32_SHIFT;
	add.mat.z		= 0;
	add.pri			= IMC_BTTN_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	// ��������{�^���쐬�f�[�^
	init.bttn_init.clact	= &add;
	init.bttn_init.buttonFunc = NULL;
	init.bttn_init.work		= NULL;
	init.bttn_init.start_flg= IMC_BTTN_POP;
	init.fntoam_sys			= fnt_sys;
	init.bmp				= bmp;
	init.fnt_x				= IMC_FONTBTTN_DRAW_X;
	init.fnt_y				= IMC_FONTBTTN_DRAW_Y_OFF;

	// �p���b�g�v���N�V�擾
	pltt_obj = CLACT_U_ResManagerGetIDResObjPtr( drawData->resMan[ CLACT_U_PLTT_RES ], IMC_BTTN_RES_MAN_PLTT_FONT );
	init.pltt				= CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );

	// �L�����N�^�I�t�Z�b�g�𒲂ׂ�
	char_size = FONTOAM_NeedCharSize( bmp, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_IMAGECLIP_DATA );

	// �L�����N�^�f�[�^��VRAM�̈�m��
	check = CharVramAreaAlloc( char_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DMAIN, &bttn->char_vram );
	GF_ASSERT_MSG( check, "�{�^�������p�L�����N�^�f�[�^�̈�m�ێ��s" );
	init.char_ofs			= bttn->char_vram.alloc_ofs;
	
	// ��������{�^���쐬
	IMC_BTTN_FontBttnInit( bttn, &init );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����蔻��e�[�u���Ƀf�[�^��ݒ�
 *
 *	@param	p_hit		�����蔻��e�[�u��
 *	@param	bttn_no		�{�^���i���o�[
 *	@param	x			���゘���W
 *	@param	y			���゙���W
 *	@param	sx			��
 *	@param	sy			����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void makeHitTbl( TP_HIT_TBL* p_hit, int bttn_no, int x, int y, int sx, int sy )
{
	p_hit[ bttn_no ].rect.top		= y;
	p_hit[ bttn_no ].rect.left		= x;
	p_hit[ bttn_no ].rect.bottom	= y + sy;
	p_hit[ bttn_no ].rect.right		= x + sx;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�{�^���f�[�^�ǂݍ���
 *
 *	@param	drawData	�`��V�X�e���f�[�^ 
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
static void loadBttnRes( IMC_DRAW_DATA* drawData )
{
	int i;		// ���[�v�p
	
	for( i=0; i<IMC_BTTN_MAX; i++ ){
		// �L�����N�^
		IMC_DRAW_CLACT_LoadCharData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CHAR_GET( i ),
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, i);
		// �Z��
		IMC_DRAW_CLACT_LoadCellData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CELL_GET( i ),
				FALSE, i);
		// �Z���A�j��
		IMC_DRAW_CLACT_LoadCellAnmData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_CANM_GET( i ),
				FALSE, i);
	}

	// �p���b�g
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM, IMC_BTTN_RES_MAN_PLTT);

	// �t�H���g�p�p���b�g
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT_FONT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM_FONT, IMC_BTTN_RES_MAN_PLTT_FONT);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I���`�F�b�N�{�^���p
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadBttnEndCkRes( IMC_DRAW_DATA* drawData )
{
	int i;		// ���[�v�p
	
	for( i=0; i<IMC_BTTN_ENDCK_MAX; i++ ){
		// �L�����N�^
		IMC_DRAW_CLACT_LoadCharData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CHAR,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, i);
		// �Z��
		IMC_DRAW_CLACT_LoadCellData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CELL,
				FALSE, i);
		// �Z���A�j��
		IMC_DRAW_CLACT_LoadCellAnmData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ENDCK_ARC_CANM,
				FALSE, i);
	}

	// �p���b�g
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM, IMC_BTTN_RES_MAN_PLTT);

	// �t�H���g�p�p���b�g
	IMC_DRAW_CLACT_LoadPlttData( 
				drawData, ARC_IMAGECLIP_GRA,
				IMC_BTTN_ARC_FILE_PLTT_FONT,
				FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 
				IMC_BTTN_PLTT_LOAD_NUM_FONT, IMC_BTTN_RES_MAN_PLTT_FONT);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���ƃL�����N�^�͔j��
 *
 *	@param	drawData	�`��f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttnCharPltt( IMC_DRAW_DATA* drawData )
{
	int i;		//���[�v�p

	for(i=0;i<IMC_BTTN_MAX;i++){
		IMC_DRAW_CLACT_DeleteCharRes( drawData, i );
	}

	IMC_DRAW_CLACT_DeletePlttRes( drawData, IMC_BTTN_RES_MAN_PLTT );
	IMC_DRAW_CLACT_DeletePlttRes( drawData, IMC_BTTN_RES_MAN_PLTT_FONT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���ʂ̃A�j��
 *
 *	@param	bttn	�{�^���\����
 *	@param	state	���̏��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_normalAnm( IMC_BUTTON* bttn, int state )
{
	if( state == IMC_BTTN_PUSH_F ){

		// ���Ԃ̊G
		IMC_BTTN_HalfGra( bttn );

	}else if( state == IMC_BTTN_PUSH ){

		// �������G�ɂ���
		IMC_BTTN_PushGra( bttn );

	}else if( (state == IMC_BTTN_POP) ||
			(state == IMC_BTTN_AREA_OVER) ){
		
		// �������G�ɂ���
		IMC_BTTN_PopGra( bttn );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���{�^���p�A�j��
 *
 *	@param	bttn	�{�^�������[�N
 *	@param	state	�X�e�[�^�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_EndButtonAnm( IMC_BUTTON* bttn, int state )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���g�{�^���̃t�H���g�f�[�^�̃A�j���[�V�������Ǘ�
 *
 *	@param	bttn	�t�H���g�{�^���\����
 *	@param	state	���̏��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_BTTN_FontAnm( IMC_FONT_BUTTON* bttn, int state )
{
	if( state == IMC_BTTN_PUSH_F ){

		// �������G�ɂ���
		FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_ON );

		// �p���b�g�I�t�Z�b�g��ύX
		FONTOAM_SetPaletteNo( bttn->font, IMC_FONTBTTN_PLTT_OFS_ON );
	}else{
		
		if( state == IMC_BTTN_POP ){

			// �������G�ɂ���
			FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_OFF );
		}
		
		if( state == IMC_BTTN_AREA_OVER ){
			// �������G�ɂ���
			FONTOAM_SetMat( bttn->font, IMC_FONTBTTN_DRAW_X, IMC_FONTBTTN_DRAW_Y_OFF );
			// �p���b�g�I�t�Z�b�g��ύX
			FONTOAM_SetPaletteNo( bttn->font, IMC_FONTBTTN_PLTT_OFS_OFF );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���ʉ��J�n
 *
 *	@param	bttn		�{�^���I�u�W�F
 *	@param	se			�炷SE
 *	@param	state		���̏��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_sndStart( IMC_BUTTON* bttn, int se, int timing, int state )
{
	if( state == timing ){

		// �{�^������������
		Snd_SePlay( se );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���p������쐬
 *
 *	@param	drawData	�`��V�X�e���f�[�^
 *	@param	arcID		�A�[�J�C�uID
 *	@param	dataID		�f�[�^ID
 *	@param	msgID		���b�Z�[�WID
 *	@param	bmp_x		�쐬����r�b�g�}�b�v�̑傫��
 *	@param	bmp_y		�쐬����r�b�g�}�b�v�̑傫��
 *
 *	@return	�쐬�����r�b�g�}�b�v
 *
 *
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* getBttnStr( IMC_DRAW_DATA* drawData, u32 arcID, u32 dataID, u32 msgID, int bmp_x, int bmp_y )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	GF_BGL_BMPWIN* bmp;

	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, arcID, dataID, HEAPID_IMAGECLIP_DATA );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgID );


	bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DRAW, 1 );
	GF_BGL_BmpWinInit( bmp );
	GF_BGL_BmpWinObjAdd( drawData->BG_Ini, bmp, bmp_x, bmp_y, 0, 0 );

	// �����񏑂�����
	GF_STR_PrintColor( bmp, FONT_BUTTON, str, 0, 0, MSG_NO_PUT, GF_PRINTCOLOR_MAKE(1,2,3), NULL );

	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	return bmp;
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������j��
 *
 *	@param	win 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttnStr( GF_BGL_BMPWIN* win )
{
	GF_BGL_BmpWinFree( win, 1 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���𓮂���
 *
 *	@param	bttn		�{�^���f�[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_BTTN_Move( IMC_BUTTON* bttn, int x, int y )
{
	const VecFx32* get_mat;
	VecFx32	mat;	

	get_mat = CLACT_GetMatrix( bttn->clact_w );
	mat = *get_mat;
	mat.x += x << FX32_SHIFT;
	mat.y += y << FX32_SHIFT;
	CLACT_SetMatrix( bttn->clact_w, &mat );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t�H���g�{�^���𓮂���
 *
 *	@param	bttn		�t�H���g�{�^��
 *	@param	x			�������l
 *	@param	y			�������l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void IMC_FONTBTTN_Move( IMC_FONT_BUTTON* bttn, int x, int y )
{
	IMC_BTTN_Move( &bttn->button, x, y );
	FONTOAM_ReflectParentMat( bttn->font );
}

#if 0
// �A�N�Z�T���@BG�@�T�E���h�ύX�{�^���̓G�t�F�N�g���ɂ͉����Ȃ����߁A
// �����Ă��Ȃ����ƂɂȂ�Ƃ�������̂ŁA
// �{�^���V�X�e�����ōs�����Ƃ��ł��Ȃ��B
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���@BG�@�T�E���h	�̃A�j���[�V����
 *
 *	@param	data	�C���[�W�N���b�v�{�^���f�[�^
 *	@param	flg		�t���O	
 *
 *	@return	none
 *
 * flg
	IMC_BTTN_ACE,		// �A�N�Z�T���ύX
	IMC_BTTN_BG,		// BG�ύX
 *
 */
//-----------------------------------------------------------------------------
static void IMCBTTN_ace_bg_snd_anm( IMC_BUTTON_DATA* data, int flg )
{
	IMC_BUTTON* bttn;
	int state;
	int i;		// ���[�v�p
	
	bttn = &data->bttn[ flg ];

	state = IMC_BTTN_GetState( bttn );
	if( state == IMC_BTTN_PUSH_F ){

		// flg�̃I�u�W�F�N�g�͉����ꂽ�G��
		// ���̑��̃I�u�W�F�N�g�̃{�^���𗣂�����Ԃɂ���
		for( i=IMC_BTTN_ACE; i<=IMC_BTTN_SND; i++ ){

			bttn = data->bttn + i;
			
			if( i != flg ){
				// �������G�ɂ���
				IMC_BTTN_PopGra( bttn );
			}else{
				// �������G�ɂ���
				IMC_BTTN_PushGra( bttn );
			}
		}
	}
}
#endif

