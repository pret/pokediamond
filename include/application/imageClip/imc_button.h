//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_button.h
 *	@brief		��ʉ��̃{�^������V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.10.08
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_BUTTON_H__
#define __IMC_BUTTON_H__

#include "bg_system.h"
#include "clact.h"
#include "button_man.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "touchpanel.h"
#include "include/system/fontoam.h"
#include "char_manager.h"

#undef GLOBAL
#ifdef	__IMC_BUTTON_H_GLOBAL
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
//	
//	���̃{�^���̏��
//	����֐��𓮂����^�C�~���O
//	
//=====================================
enum{
	IMC_BTTN_PUSH_F		= BMN_EVENT_TOUCH,		// �����ꂽ�u��
	IMC_BTTN_POP		= BMN_EVENT_RELEASE,	// �����ꂽ
	IMC_BTTN_PUSH		= BMN_EVENT_HOLD,		// ������Ă���
	IMC_BTTN_AREA_OVER	= BMN_EVENT_SLIDEOUT,	// �{�^���G���A�O
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�{�^���\����	
//	
//=====================================
typedef struct _IMC_BUTTON{
	// �`�敔
	CLACT_WORK_PTR clact_w;	// �A�N�^�[���[�N
	
	// ���암
	int start_flg;		// ����֐��𓮂����^�C�~���O
	void*	work;		// ����֐��ɓn�����[�N
	// ����֐�	�{�^���̓���Ŏ����ɔ�����������
	void (*func)(struct _IMC_BUTTON* button, void* work);
} IMC_BUTTON;

// ����\����
typedef void (*IMCBUTTON_FUNC)( IMC_BUTTON* button, void* work );

//-------------------------------------
//	
//	�{�^���쐬�\����
//	
//=====================================
typedef struct {
	CLACT_ADD*		clact;			// �Z���A�N�^�[�o�^�f�[�^

	IMCBUTTON_FUNC	buttonFunc;		// ����֐�
	void*			work;			// ����ɓn�����[�N
	int				start_flg;		// �ǂ̃^�C�~���O�ɓ���֐������s���邩
/*						IMC_BTTN_NOPUSH,		// ������Ă��Ȃ�
						IMC_BTTN_PUSH,			// ������Ă���
						IMC_BTTN_PUSH_F,		// �����ꂽ�u��
						IMC_BTTN_POP,			// �����ꂽ	
						IMC_BTTN_AREA_OVER,		// �{�^���G���A�O */
} IMC_BUTTON_INIT;

//-------------------------------------
//	
//	�t�H���g�t���{�^��
//	
//=====================================
typedef struct {
	IMC_BUTTON button;
	FONTOAM_OBJ_PTR font;
	CHAR_MANAGER_ALLOCDATA char_vram;
} IMC_FONT_BUTTON;

//-------------------------------------
//	
//	�{�^���쐬�\����
//	
//=====================================
typedef struct {
	IMC_BUTTON_INIT bttn_init;		// �{�^���������f�[�^
	const GF_BGL_BMPWIN* bmp;		// �L�����N�^�f�[�^
	CONST_FONTOAM_SYS_PTR fntoam_sys;	// OAM�t�H���g�V�X�e���f�[�^
	const NNSG2dImagePaletteProxy* pltt;// �p���b�g�v���N�V
	int				fnt_x;			// �I�t�Z�b�g�ʒu
	int				fnt_y;			// �I�t�Z�b�g�ʒu
	int				char_ofs;		// �L�����N�^�I�t�Z�b�g
} IMC_FONT_BUTTON_INIT;

//-----------------------------------------------------------------------------
/**
*		�C���[�W�N���b�v�p
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�C���[�W�N���b�v�p�{�^���\����	
//	
//=====================================
typedef struct {
	IMC_BUTTON	bttn[IMC_BTTN_NORM_MAX];
	IMC_FONT_BUTTON bttn_end;
	BOOL bttn_end_do;
	FONTOAM_SYS_PTR fntoam_sys;

	// �����蔻��p�e�[�u��
	BUTTON_MAN* bttn_man;
	TP_HIT_TBL hit[ IMC_BTTN_MAX ];
} IMC_BUTTON_DATA;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief
 *
 *	@param	button		�{�^���I�u�W�F�̃|�C���^ 
 *	@param	init		�������f�[�^�\����		 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_Init( IMC_BUTTON* button, IMC_BUTTON_INIT* init );
GLOBAL void IMC_BTTN_FontBttnInit( IMC_FONT_BUTTON* button, IMC_FONT_BUTTON_INIT* init );

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
GLOBAL void IMC_BTTN_Delete( IMC_BUTTON* button );
GLOBAL void IMC_BTTN_FontBttnDelete( IMC_FONT_BUTTON* button );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�{�^���V�X�e������֐����s
 *
 *	@param	button	�{�^���\����
 *	@param	state	���̃{�^�����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_DoFunc( IMC_BUTTON* button, int state );

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
		IMC_BTTN_PUSH,			// ������Ă���
		IMC_BTTN_PUSH_F,		// �����ꂽ�u��
		IMC_BTTN_POP,			// �����ꂽ�u��
		IMC_BTTN_AREA_OVER		// �{�^���G���A�O
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_FuncSet( IMC_BUTTON* button, IMCBUTTON_FUNC func, void* work, int start_flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����ꂽ�Ƃ��̊G�ɂ���
 *
 *	@param	bttn	�{�^���\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_PushGra( IMC_BUTTON* bttn );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����ꂽ�Ƃ��̊G�ɂ���
 *
 *	@param	bttn	�{�^���\����
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_BTTN_PopGra( IMC_BUTTON* bttn );

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
GLOBAL void IMC_BTTN_HalfGra( IMC_BUTTON* bttn );


//-----------------------------------------------------------------------------
/**
*	�C���[�W�N���b�v�p
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
GLOBAL void IMC_IMCBTTN_Init( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�p�{�^���̔j��
 *
 *	@param	button		�{�^���\����
 *	@param	drawData	�`��V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_Delete( IMC_BUTTON_DATA* button, IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
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
GLOBAL void IMC_IMCBTTN_Main( IMC_BUTTON_DATA* button );


//----------------------------------------------------------------------------
/**
 *	@brief	�����I��
 *
 *	@param	button	�{�^��
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_EndEx( IMC_BUTTON_DATA* button );


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j����ԃ��Z�b�g
 *
 *	@param	button 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_Reset( IMC_BUTTON_DATA* button );

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
GLOBAL void IMC_IMCBTTN_Move( IMC_BUTTON_DATA* button, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���@BG�@�ύX�{�^������������Ԃɂ���
 *
 *	@param	button			�{�^���\����
 *	@param	button_no		�{�^���i���o�[
 *	@param	event			�C�x���g�f�[�^
 *
 *	@return	none
 *
 * button_no
	IMC_BTTN_ACE,		// �A�N�Z�T���ύX�Ɉڂ�
	IMC_BTTN_BG,		// BG�ύX�Ɉڂ�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_OnAB( IMC_BUTTON_DATA* button, int button_no, int event );

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
		IMC_BTTN_AREA_OVER		// �{�^���G���A�O
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_IMCBTTN_FuncSet( IMC_BUTTON_DATA* button, int button_no, IMCBUTTON_FUNC func, void* work, int start_flg );

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
GLOBAL void IMC_IMCBTTN_DrawSet( IMC_BUTTON_DATA* button, int button_no, BOOL flag );


#undef	GLOBAL
#endif		// __IMC_BUTTON_H__

