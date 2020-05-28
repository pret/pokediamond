//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_subwin.h
 *	@brief		�T�u�E�B���h�E
 *	@author		tomoya takahashi
 *	@data		2005.10.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_SUBWIN_H__
#define __IMC_SUBWIN_H__
#include "bg_system.h"
#include "include/application/imageClip/imc_bg.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/contest/contest.h"
#include "include/savedata/config.h"

#undef GLOBAL
#ifdef	__IMC_SUBWIN_H_GLOBAL
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
//	�������}�X�N
//	
//=====================================
enum{
	IMC_SUBWIN_INITMASK_CLEAN	= 1 << 0,	// �ŏ��̏�����
	IMC_SUBWIN_INITMASK_BG		= 1 << 1,	// BG�ʂ̏�����
	IMC_SUBWIN_INITMASK_BMP		= 1 << 2,	// bmp�E�B���h�E�ʂ̏����� 
	IMC_SUBWIN_INITMASK_ACCE_COUNT = 1 << 3,// �A�N�Z�T���J�E���g��ʂ̏����� 
	IMC_SUBWIN_INITMASK_TIME_COUNT = 1 << 4,// �^�C���J�E���g��ʂ̏����� 
	IMC_SUBWIN_INITMASK_RANKBMP = 1 << 5,	// �����N��BMP�E�B���h�E
};

#define IMC_SUBWIN_DEFAULT_INIT	(IMC_SUBWIN_INITMASK_CLEAN | IMC_SUBWIN_INITMASK_BG | IMC_SUBWIN_INITMASK_BMP | IMC_SUBWIN_INITMASK_ACCE_COUNT)
#define IMC_SUBWIN_CONTEST_INIT	(IMC_SUBWIN_INITMASK_CLEAN | IMC_SUBWIN_INITMASK_BG | IMC_SUBWIN_INITMASK_BMP | IMC_SUBWIN_INITMASK_ACCE_COUNT | IMC_SUBWIN_INITMASK_TIME_COUNT | IMC_SUBWIN_INITMASK_RANKBMP)

//---------------------------------------------------------
//	�A�N�Z�T�������֌W
//---------------------------------------------------------
// �A�N�Z�T���A�C�R���������[�N�̍ő吔
#define IMC_SUBWIN_ACCECOUNT_ICON_MAX	( IMC_RBOX_ACCE_CONTEST_MAX )


//---------------------------------------------------------
//	�^�C�������֌W		�����]�����[�h
//---------------------------------------------------------
#define IMC_SUBWIN_NUM_KETA	(2)		// ����
enum{
	IMC_SUBWIN_NUM_TRANS_OYA,		// �e
	IMC_SUBWIN_NUM_TRANS_CHILD,		// �q
	IMC_SUBWIN_NUM_TRANS_NONE,		// �Ȃ�ł��Ȃ�
};
#define IMC_SUBWIN_NUM_POP_TCB_PRI	( 128 )
#define IMC_SUBWIN_NUM_PUSH_TCB_PRI	( 64 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�A�C�R���f�[�^
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[IMC_DRAW_USE_RES_NUM];
	CLACT_WORK_PTR	icon[IMC_SUBWIN_ACCECOUNT_ICON_MAX];
	int acce_num;
	int acce_max;
} IMC_SUBWIN_ACCEICON;

//-------------------------------------
//	���샏�[�N
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	int count;
	int count_max;
} IMC_SUBWIN_MOVE_WORK;


//-------------------------------------
//	�^�C���J�E���g�O���t�B�b�N�p
//	�̪�ă��[�N
//=====================================
typedef struct {
	BOOL init_flg;	// TRUE	���쒆 FALSE	�񓮍쒆
	CLACT_WORK_PTR	num[IMC_SUBWIN_NUM_KETA];
	VecFx32 mat[IMC_SUBWIN_NUM_KETA];
	IMC_SUBWIN_MOVE_WORK	scale;
	IMC_SUBWIN_MOVE_WORK	x;
	IMC_SUBWIN_MOVE_WORK	y;
} IMC_SUBWIN_TIME_EFFECT;


//-------------------------------------
//	�^�C���������[�N
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[IMC_DRAW_USE_RES_NUM];
	CLACT_WORK_PTR	num[IMC_SUBWIN_NUM_KETA];
	GF_BGL_BMPWIN*	bmp;
	int count;
	int master_count;		// �ʐM�̐e�p����
	TCB_PTR	CountTCB;		// count�̒l������������TCB
	TCB_PTR MstTransTCB;	// Ͻ�������̒l��]������TCB
	CON_IMC_LOCAL* p_comm_data;	// �ʐM�f�[�^
	IMC_SUBWIN_TIME_EFFECT counter_eff;	// �J�E���^�[�̪��

	BOOL pal_chg;	// �p���b�g�ύX�ς݃`�F�b�N
} IMC_SUBWIN_TIMECOUNT;


//-------------------------------------
//	
//	�T�u��ʍ\����
//	
//=====================================
typedef struct {
	IMC_BG			bg;			// BG��
	GF_BGL_BMPWIN*	bmp;		// �r�b�g�}�b�v�E�B���h�E
	CLACT_SET_PTR		clactSet;			// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR* p_resMan;	// ���\�[�X�}�l�[�W��

	IMC_SUBWIN_ACCEICON	acce_icon;	// �A�N�Z�T���A�C�R�����[�N
	IMC_SUBWIN_TIMECOUNT counter;	// �J�E���^�[
	GF_BGL_BMPWIN*	rankbmp;		// �����N������r�b�g�}�b�v�E�B���h�E
	
	int init_flg;				// �������ς݃`�F�b�N�t���O

	// �R���t�B�O�f�[�^
	int wnd_no;
	u32 wait;

	STRBUF* p_glb_str;	// �O���[�o��������o�b�t�@
} IMC_SUBWIN;

typedef struct {
	GF_BGL_INI* bg_ini;
	CLACT_SET_PTR		clactSet;			// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR* p_resMan;	// ���\�[�X�}�l�[�W��

	// �R���t�B�O
	const CONFIG* cp_config;

	// �A�N�Z�T�������p
	int acce_max;		// �A�C�R����

	// �e�[�}�p
	int rank_msgid;		// �����N���b�Z�[�WID
	int rank_strid;		// �����N������ID

	// �^�C�}�[�p
	int count_max;		// �ő�J�E���g�l
	CON_IMC_LOCAL* p_comm_data;	// �ʐM�f�[�^
} IMC_SUBWIN_INIT;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u�E�B���h�E�̏�����
 *
 *	@param	subwin		�T�u�E�B���h�E�\����
 *	@param	init		�������f�[�^
 *	@param	init_mask	�������}�X�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Init( IMC_SUBWIN* subwin, IMC_SUBWIN_INIT* init, int init_mask );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u�E�B���h�E�j��
 *
 *	@param	subwin	�T�u�E�B���h�E
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Delete( IMC_SUBWIN* subwin );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C���֐�
 *
 *	@param	subwin	�T�u�E�B���h�E
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Main( IMC_SUBWIN* subwin );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�ɕ������\��
 *
 *	@param	subwin	�T�u�E�B���h�E�I�u�W�F
 *	@param	arcID	�A�[�J�C�uID
 *	@param	dataID	�f�[�^ID
 *	@param	msgID	�\�����郁�b�Z�[�WID
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_SetBmpWin( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID );
GLOBAL s32 IMC_SUBWIN_SetBmpWinWait( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID );
GLOBAL void IMC_SUBWIN_EndBmpWinWait( IMC_SUBWIN* subwin );	// �m�ۂ��Ă������[�N���͂�

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�Z�T���J�E���g�A�C�R���`��ݒ�
 *
 *	@param	subwin		���[�N
 *	@param	acce_num	���݂̃A�N�Z�T����
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_SetAcceIcon( IMC_SUBWIN* subwin, int acce_num );

//----------------------------------------------------------------------------
/**
 *	@brief	���̃J�E���^�[�l�擾�֐�
 *
 *	@param	subwin	�T�u�E�B���h�E
 *
 *	@return	�J�E���^�[�̒l
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_SUBWIN_GetCounterNowNum( const IMC_SUBWIN* subwin );
GLOBAL void IMC_SUBWIN_SetCounterNowNum( IMC_SUBWIN* subwin, int count );

//----------------------------------------------------------------------------
/**
 *	@brief	�J�E���^�[�̪�Ă̏I���`�F�b�N
 *
 *	@param	subwin	�T�u�E�B���h�E
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_SUBWIN_GetCounterEffectEnd( const IMC_SUBWIN* subwin );

#ifdef PM_DEBUG
GLOBAL void IMC_SUBWIN_DEBUG_SetBmpWin( IMC_SUBWIN* p_data, int msgID_1, int msgID_2 );
GLOBAL void IMC_SUBWIN_DEBUG_CountTimeSet( IMC_SUBWIN* p_data, int num );
#endif

#undef	GLOBAL
#endif		// __IMC_SUBWIN_H__

