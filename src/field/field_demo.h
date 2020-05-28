//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_demo.h
 *	@brief		�t�B�[���h��ł̊ȒP�ȃf������
 *	@author		tomoya takahashi	
 *	@data		2006.04.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_DEMO_H__
#define __FIELD_DEMO_H__

#include "fieldmap_func.h"

#undef GLOBAL
#ifdef	__FIELD_DEMO_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *		�t�B�[���h�}�b�v�^�X�N����
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�`���|�P�����o��
//	Start		�J�n
//	EndCheck	�I���҂�[TRUE] 
//	End			�I���i�j���j
//=====================================
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_LegendPokeApp_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_LegendPokeApp_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLDMAP_DEMO_LegendPokeApp_EndCheck( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	�������b�J�̕��o
//	Start		�J�n
//	End			�I���i�j���j
//=====================================
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_BlackRing_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_BlackRing_End( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	����̗�
//	Start		�J�n
//	End			�I���i�j���j
//=====================================
enum{
	FLDMAP_DEMO_ANTEGG_CUT00,
	FLDMAP_DEMO_ANTEGG_CUT01,
	FLDMAP_DEMO_ANTEGG_CUT02,
};
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_AntEgg_Start( FIELDSYS_WORK* fsys, u32 cut );
GLOBAL void FLDMAP_DEMO_AntEgg_End( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	��͕��o
//	Start		�J�n
//	GetState	�g��I���`�F�b�N[FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT]
//	EndReq		�I�����N�G�X�g
//	GetState	�I���`�F�b�N[FLDMAP_DEMO_GINGA_SEQ_END]
//	End			�I���i�j���j
//=====================================
enum{
	FLDMAP_DEMO_GINGA_SEQ_START,		// �G�t�F�N�g�J�n
	FLDMAP_DEMO_GINGA_SEQ_SCALEUP,		// ��͊g��
	FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT,	// �I�����N�G�X�g�҂�
	FLDMAP_DEMO_GINGA_SEQ_ENDREQ,		// �I���G�t�F�N�g�J�n
	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT,	// ��͏k��
	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF,	// ��͏k���{���邭
	FLDMAP_DEMO_GINGA_SEQ_END			// �I��
};

GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_Ginga_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_Ginga_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL void FLDMAP_DEMO_Ginga_EndReq( FLDMAPFUNC_WORK* p_demo );
GLOBAL u32 FLDMAP_DEMO_Ginga_GetState( FLDMAPFUNC_WORK* p_demo );


//-----------------------------------------------------------------------------
/**
 *
 *	��ʗh�炵�C�x���g
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FLD_MAP_DEMO_ZishinEventCall(GMEVENT_CONTROL *event);
GLOBAL void FLD_MAP_DEMO_MioZishinEventCall(GMEVENT_CONTROL *event);


//-----------------------------------------------------------------------------
/**
 *
 *			���́A�X�̴̪�ĒP��
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		��ʗh�炵
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��ʗh�炵���[�N
//=====================================
typedef struct _FLD_DEMO_SHAKE_SCRN FLD_DEMO_SHAKE_SCRN;

GLOBAL FLD_DEMO_SHAKE_SCRN* FLD_DEMO_ShakeScrn_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_ShakeScrn_Free( FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_Start( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width, fx32 height, u32 one_sync, u32 count, GF_CAMERA_PTR copy_camera );
GLOBAL BOOL FLD_DEMO_ShakeScrn_EndCheck( FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_Main( FLD_DEMO_SHAKE_SCRN* p_data );

GLOBAL u32 FLD_DEMO_ShakeScrn_GetNowCount( const FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL fx32 FLD_DEMO_ShakeScrn_GetNowShakeWidth( const FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_SetNowShakeWidth( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width );


//-----------------------------------------------------------------------------
/**
 *		�t���b�V��		
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t���b�V�����[�N
//=====================================
typedef struct _FLD_DEMO_FLASH FLD_DEMO_FLASH;

GLOBAL FLD_DEMO_FLASH* FLD_DEMO_Flash_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_Flash_Free( FLD_DEMO_FLASH* p_data );
GLOBAL void FLD_DEMO_Flash_Start( FLD_DEMO_FLASH* p_data, u32 alphamax, u32 out_sync, u32 in_sync );
GLOBAL BOOL FLD_DEMO_Flash_EndCheck( FLD_DEMO_FLASH* p_data );
GLOBAL void FLD_DEMO_Flash_Main( FLD_DEMO_FLASH* p_data );
GLOBAL int FLD_DEMO_Flash_GetAlpha( const FLD_DEMO_FLASH* cp_data );



//-----------------------------------------------------------------------------
/**
 *		�f�����		�R���e�E
 *
 *		��̓f�����ĂԑO�ɃT�u�ʂ̔j�����s���Ă���K�v������܂�
*/
//-----------------------------------------------------------------------------
// �V�X�e���S�̂̏������j���^�X�N
#define FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI	( 1024 )

// �`��V�X�e���̃Z�b�g�A�b�v�pTCB�@�D�揇��	
#define FLD_DEMO_GINGA_MOTIONBL_SETUP_TCB_PRI	( 1023 )	// ���[�V�����u���[
#define FLD_DEMO_GINGA_DRAWDATA_SETUP_TCB_PRI	( 1024 )	// BG

// ���݂̏��
enum{
	FLD_DEMO_GINGA_MOTIONBL_INIT,	// ��������
	FLD_DEMO_GINGA_MOTIONBL_SCALEUP,	// �g�咆
	FLD_DEMO_GINGA_MOTIONBL_REQWAIT,	// �k�����N�G�X�g�҂�
	FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN,	// �k����
	FLD_DEMO_GINGA_MOTIONBL_DELETE,	// �j��������
	FLD_DEMO_GINGA_MOTIONBL_END		// �S��ƏI�� or �������O
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
typedef struct _FLD_DEMO_GINGA FLD_DEMO_GINGA;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL FLD_DEMO_GINGA* FLD_DEMO_GINGA_Alloc( FIELDSYS_WORK * fsys );
GLOBAL void FLD_DEMO_GINGA_Free( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_Init( FLD_DEMO_GINGA* p_data, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_DEMO_GINGA_Main( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_EndReq( FLD_DEMO_GINGA* p_data );
GLOBAL u32 FLD_DEMO_GINGA_GetState( const FLD_DEMO_GINGA* cp_data );
GLOBAL void FLD_DEMO_GINGA_Draw( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_SetMotionBlNum( FLD_DEMO_GINGA* p_data, int a, int b );



//-----------------------------------------------------------------------------
/**
 *
 *		�C�A�E�G�A�o��		�R���e�@
 *
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�A�G�A�o��@���[�N
//=====================================
typedef struct _FLD_DEMO_LEGENDPOKE_APP FLD_DEMO_LEGENDPOKE_APP;

GLOBAL FLD_DEMO_LEGENDPOKE_APP* FLD_DEMO_LegendPokeApp_Alloc( u32 heapID, FIELDSYS_WORK * fsys );
GLOBAL void FLD_DEMO_LegendPokeApp_Free( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Start( FLD_DEMO_LEGENDPOKE_APP* p_data, u32 legendpoke_id );
GLOBAL BOOL FLD_DEMO_LegendPokeApp_EndCheck( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Main( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Draw( FLD_DEMO_LEGENDPOKE_APP* p_data );


//-----------------------------------------------------------------------------
/**
 *
 *		�C�A�E�G�A�𒆐S���������o��		�R���e�B
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C�A�E�G�A�𒆐S�ɂ�����o���@���[�N
//=====================================
typedef struct _FLD_DEMO_BLACK_RING FLD_DEMO_BLACK_RING;

GLOBAL FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_BlackRing_Free( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_Start( FLD_DEMO_BLACK_RING* p_data, u16 grid_x, u16 grid_y, u16 grid_z );
GLOBAL void FLD_DEMO_BlackRing_Main( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_Draw( FLD_DEMO_BLACK_RING* p_data );


//-----------------------------------------------------------------------------
/**
 *
 *		����̗����o��		�R���e�B
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	����̗��@���[�N
//=====================================
typedef struct _FLD_DEMO_ANTEGG FLD_DEMO_ANTEGG;

// �ȉ��̂S�̊֐��́A���ʂŎg�p����
GLOBAL FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Cut_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_AntEgg_Cut_Free( FLD_DEMO_ANTEGG* p_data );
GLOBAL void FLD_DEMO_AntEgg_Cut_Main( FLD_DEMO_ANTEGG* p_data );
GLOBAL void FLD_DEMO_AntEgg_Cut_Draw( FLD_DEMO_ANTEGG* p_data );

// �J�n�֐����������Ďg�p����
//-------------------------------------
//	�J�b�g�O�O
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut00_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	�J�b�g�O�P
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut01_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	�J�b�g�O�Q
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut02_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );


//-----------------------------------------------------------------------------
/**
 *
 *		����̗��̎��̍������O	�R���e�B
 * 
 */
//-----------------------------------------------------------------------------
// �ȉ��̂S�̊֐��́A���ʂŎg�p����
GLOBAL FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_AntEggCat_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Free( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Main( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Draw( FLD_DEMO_BLACK_RING* p_data );

// �J�n�֐����������Ďg�p����
//-------------------------------------
//	�J�b�g�O�O
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat00_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	�J�b�g�O�P
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat01_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	�J�b�g�O�Q
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat02_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );


//-----------------------------------------------------------------------------
/**
 * 
 *		�t�B�[���h�S�̂��Â�����
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	��Ԓ萔	
//=====================================
enum{
	FLD_DEMO_DARKLIGHT_INIT,	// ������
	FLD_DEMO_DARKLIGHT_FADEOUT,	// �Â��Ȃ��Ă��܂��B
	FLD_DEMO_DARKLIGHT_ENDWAIT,	// �I�����N�G�X�g�҂��B
	FLD_DEMO_DARKLIGHT_FADEIN,	// ���邭�Ȃ��Ă��܂��B
	FLD_DEMO_DARKLIGHT_END,		// �S�H���I��
};

//-------------------------------------
//	���x�̒ႢLIGHT���t�B�[���h�S�̂ɂ�����
//=====================================
typedef struct _FLD_DEMO_DARKLIGHT FLD_DEMO_DARKLIGHT;

GLOBAL FLD_DEMO_DARKLIGHT* FLD_DEMO_DarkLight_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys );
GLOBAL void FLD_DEMO_DarkLight_Free( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL void FLD_DEMO_DarkLight_Start( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL void FLD_DEMO_DarkLight_Main( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL u32 FLD_DEMO_DarkLight_GetState( const FLD_DEMO_DARKLIGHT* cp_data );
GLOBAL void FLD_DEMO_DarkLight_EndReq( FLD_DEMO_DARKLIGHT* p_data );

//-----------------------------------------------------------------------------
/**
 *
 *
 *		�A���̃^�}�S���o�J�n�f��
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�A���̗����o�J�n�f��
//=====================================
typedef struct _FLD_DEMO_ARITAMA_START FLD_DEMO_ARITAMA_START;

GLOBAL FLD_DEMO_ARITAMA_START* FLD_DEMO_AriTamaStart_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys );
GLOBAL void FLD_DEMO_AriTamaStart_Free( FLD_DEMO_ARITAMA_START* p_data );
GLOBAL void FLD_DEMO_AriTamaStart_Start( FLD_DEMO_ARITAMA_START* p_data, u32 legendpoke_id );
GLOBAL BOOL FLD_DEMO_AriTamaStart_Main( FLD_DEMO_ARITAMA_START* p_data );
GLOBAL void FLD_DEMO_AriTamaStart_Draw( FLD_DEMO_ARITAMA_START* p_data );

#undef	GLOBAL
#endif		// __FIELD_DEMO_H__

