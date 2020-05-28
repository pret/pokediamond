//==============================================================================
/**
 * @file	cb_sys.h
 * @brief	�ȒP�Ȑ���������
 * @author	goto
 * @date	2006.04.03(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef __CB_SYS_H__
#define __CB_SYS_H__

#include "field/field_common.h"

#include "savedata/custom_ball.h"

#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"
#include "system/touch_subwindow.h"

#include "include/application/imageClip/imc_hand.h"
#include "system\font_arc.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_ball_custom.h"
#include "include/msgdata/msg_bc_seal_name.h"
#include "include/msgdata/msg_seal_comment.h"

#include "touchpanel_system.h"
#include "touchpanel.h"
#include "gflib/button_man.h"
#include "wazaeffect/ball_effect.h"
#include "include/poketool/poke_tool.h"
#include "include/system/fontoam.h"

#include "include/system/softsprite.h"

#include "seal_id.h"

extern const PROC_DATA CustomBallProcData;		///< �v���Z�X��`�f�[�^

#define CB_DEF_EDIT_OFF			(0)
#define CB_DEF_EDIT_ON			(1)

#define CB_DEF_PAGE_ITEMS		(8)
#define CB_DEF_PAGE_MAX			(CB_DEF_ITEM_DATA_NUM / CB_DEF_PAGE_ITEMS)

#define CB_DEF_BTN_PAL_NUM		(3)
#define CB_DEF_UD_BTN_PAL_NO	(1)
#define CB_DEF_EYE_BTN_PAL_NO	(1)
#define CB_DEF_BTN_PAL_NO		(0)
#define CB_DEF_CUR_BTN_PAL_NO	(2)

#ifdef PM_DEBUG

//#define CUSTOM_BALL_DOSNT_EXECUTED

#endif

// ------------------------------------
//
//	�������тɂ��邩�ǂ���
//
// ------------------------------------
#define SEAL_SBS

/// ----- ��` ----------------------

#define CB_DEF_SEAL_OFS_X	(+7 * 8)
#define CB_DEF_SEAL_OFS_Y	(-2 * 8)

#define CB_DEF_POKE_RETURN_WAIT	(30)

#define CB_DEF_FADE_GRAY	(10)

#define SEAL_HIT_SIZE_X		(10)
#define SEAL_HIT_SIZE_Y		(10)
#define SEAL_SIZE_16x16		(0)
#define SEAL_SIZE_32x32		(1)

#define SEAL_CHAR_START		(CB__SEAL_00_NCGR_BIN)

#define SEAL_NUM_PRINT_X	(-1 + 8)
#define SEAL_NUM_PRINT_Y	(0)

/// -----------------------------------

#define CB_DEF_POKE_NOT_INDEX	(0xff)
#define CB_DEF_HEAP_SIZE		(0x80000)

#define CB_DEF_MSG_END_KEY		(PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | \
								 PAD_KEY_UP	  | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT)


#define CB_DEF_OBJ_MAX					(64 + 64)		///< main + sub
#define CB_DEF_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

#define CB_DEF_STRING_BG_FRM			(GF_BGL_FRAME1_M)
#define CB_DEF_SINGLE_BG_FRM			(GF_BGL_FRAME2_M)
#define CB_DEF_FIELD_BG_FRM				(GF_BGL_FRAME3_M)

#define CB_DEF_STRING_SUB_BG_FRM		(GF_BGL_FRAME0_S)
#define CB_DEF_BALL_SUB_BG_FRM			(GF_BGL_FRAME1_S)
#define CB_DEF_EDIT_SUB_BG_FRM			(GF_BGL_FRAME3_S)
#define CB_DEF_LIST_SUB_BG_FRM			(GF_BGL_FRAME2_S)

#define CB_PLANE_LIST					(GX_PLANEMASK_BG2)

enum {
	CB_BG_PRI_SCR_STRING = 0,
	CB_BG_PRI_SCR_SELECT = 2,
	CB_BG_PRI_SCR_FIELD  = 3,
	CB_BG_PRI_SCR_FIELD_TOP  = 1,
	
	CB_BG_PRI_SCR_SUB_STRING = 0,
	CB_BG_PRI_SCR_LIST = 1,
	CB_BG_PRI_SCR_BALL = 2,
	CB_BG_PRI_SCR_EDIT_TOP = 1,
	CB_BG_PRI_SCR_EDIT = 3,
};

enum {
	///< �|�P�����A�C�R��
	CB_ENUM_ICON_CHAR_ID	= 15000,
	CB_ENUM_ICON_PLTT_ID	= 16000,
	CB_ENUM_ICON_CELL_ID	= 17000,
	CB_ENUM_ICON_CELLANM_ID = 18000,
	
	///< �V�[��
	CB_ENUM_SEAL_CHAR_ID	= 20000,
	CB_ENUM_SEAL_PLTT_ID	= 21000,
	CB_ENUM_SEAL_CELL_ID	= 22000,
	CB_ENUM_SEAL_CELLANM_ID = 23000,
	
	///< �{�^��
	CB_ENUM_BTN_CHAR_ID		= 25000,
	CB_ENUM_BTN_EYE_CHAR_ID	= 35000,
	CB_ENUM_BTN_PLTT_ID		= 26000,
	CB_ENUM_BTN_CELL_ID		= 27000,
	CB_ENUM_BTN_CELLANM_ID	= 28000,
	CB_ENUM_BTN_SEAL		= 0,
	CB_ENUM_BTN_ETC			= 1,
	
	///< �{�^���J���[
	CB_ENUM_FONT_OMA_BTN_PLTT_ID = 30000,
	
	///< �҂��҂�	
	CB_ENUM_PIKO_CHAR_ID		= 45000,
	CB_ENUM_PIKO_PLTT_ID		= CB_ENUM_BTN_PLTT_ID,
	CB_ENUM_PIKO_CELL_ID		= 47000,
	CB_ENUM_PIKO_CELLANM_ID		= 48000,
};
#define CB_DEF_ARC_ID_POKE_ICON_GET(n)	((n) + CB_ENUM_ICON_CHAR_ID)
#define CB_DEF_ARC_ID_SEAL_GET(n)		((n) + CB_ENUM_SEAL_CHAR_ID)
#define CB_DEF_ARC_ID_BTN_GET(n)		((n) + CB_ENUM_BTN_CHAR_ID)

#define CB_DEF_ARC_ID_OFS		(11000)
#define CB_DEF_ARC_ID_GET(n)	((n) + CB_DEF_ARC_ID_OFS)

#define CB_DEF_ROW				(3)
#define CB_DEF_LINE				(4)
#define CB_DEF_CUR_MOVE_UD(n)	(n / CB_DEF_LINE)


///< �p���b�g(�㉺�Ǘ�)
enum {
	///< ����
	CB_ENUM_PAL_SEL_BG		= 0,
	CB_ENUM_PAL_FLD_BG		= 1,

	CB_ENUM_PAL_FRAME		= 12,
	CB_ENUM_PAL_MENU,
	CB_ENUM_PAL_FONT,
	CB_ENUM_PAL_BACK,

	///< �����
	CB_ENUM_PAL_BALL_BG		= 0,
	CB_ENUM_PAL_EDIT_BG		= 1,
	CB_ENUM_PAL_LIST_BG		= 3,
	CB_ENUM_PAL_SWITCH		= 5,
	CB_ENUM_PAL_SWITCH_RESERVED,
	
	CB_ENUM_PAL_NUM			= 11,
};

///< OBJ�D��x(�㉺�Ǘ�)
enum {
	CB_ENUM_BG_PRI_T_OBJ	= CB_BG_PRI_SCR_SELECT,

	CB_ENUM_OAM_PRI_BALL	= 40,
	CB_ENUM_OAM_PRI_ICON	= 10,
	CB_ENUM_OAM_PRI_CUR_1	= 20,
	CB_ENUM_OAM_PRI_CUR_2	= 25,
	
	CB_ENUM_BG_PRI_B_OBJ	= 1,
	CB_ENUM_BG_PRI_B_OBJ2	= 1,
	CB_ENUM_OAM_BTN_PRI		= 60,
};

///< �{�[���̏��
enum {
	CB_ENUM_BALL_STATE_FREE = 0,		///< �t���[
	CB_ENUM_BALL_STATE_CUSTOM,			///< �ҏW�ς�
	CB_ENUM_BALL_STATE_CUSTOM_SET,		///< �ҏW�ς݂��|�P�����ɃZ�b�g
	CB_ENUM_BALL_STATE_FREE_SET,		///< �t���[�Ń|�P�����ɃZ�b�g
};

///< �E�B���h�E�̎��
enum {
	CB_ENUM_WIN_T_MAIN		= 0,		///< ���ʂ̊�{���b�Z�[�W�E�B���h�E
	CB_ENUM_WIN_T_SEL,					///< ���ʂ̑I���E�B���h�E
	
	CB_ENUM_WIN_B_MAIN,					///< ����ʂ̊�{���b�Z�[�W
	CB_ENUM_WIN_B_LIST_1,				///< ���X�g
	CB_ENUM_WIN_B_LIST_2,				///< ���X�g
	CB_ENUM_WIN_B_LIST_3,				///< ���X�g
	CB_ENUM_WIN_B_LIST_4,				///< ���X�g
	CB_ENUM_WIN_B_LIST_5,				///< ���X�g
	CB_ENUM_WIN_B_LIST_6,				///< ���X�g
	CB_ENUM_WIN_B_LIST_7,				///< ���X�g
	CB_ENUM_WIN_B_LIST_8,				///< ���X�g
	
	CB_ENUM_WIN_MAX,
};

enum {
	CB_ENUM_WIN_B_BTN_1 = 0,
	CB_ENUM_WIN_B_BTN_2,
	
	CB_ENUM_WIN_SUB_MAX
};


#define CB_DEF_BMPWIN_MAX				(CB_ENUM_WIN_MAX)

///< �T�u�V�[�P���X
enum {
	///< �ҏW
	CBS_CUSTOM_INIT			= 0,
	CBS_CUSTOM_T_FADE_OUT,
	CBS_CUSTOM_T_FADE_OUT_WAIT,
	CBS_CUSTOM_T_FIELD_FADE_OUT_WAIT,
	CBS_CUSTOM_MAIN,
	CBS_CUSTOM_CON,		///< pt�m�F
	CBS_CUSTOM_DEC,		///< �����Ă�
	CBS_CUSTOM_END,		///< ��߂�
	CBS_CUSTOM_T_FADE_IN,
	CBS_CUSTOM_T_FADE_IN_2,
	CBS_CUSTOM_T_FADE_IN_WAIT,
};

enum {
	///< �I��
	CBS_SELECT_INIT			= 0,
	CBS_SELECT_WIPE_IN,
	CBS_SELECT_WIPE_IN_WAIT,
	CBS_SELECT_MAIN,
	CBS_SELECT_MENU,
	CBS_SELECT_WIPE_OUT,
	CBS_SELECT_WIPE_OUT_WAIT,
};

enum {
	///< �Z�b�g
	CBS_SET_INIT			= 0,
	CBS_SET_WIPE_OUT,
	CBS_SET_WIPE_OUT_WAIT,
};

enum {
	///< �͂���
	CBS_REM_INIT			= 0,
	CBS_REM_MAIN,
	CBS_REM_END,
};

enum {
	///< ���ꂩ��
	CBS_CHANGE_INIT			= 0,
	CBS_CHANGE_MAIN,
	CBS_CHANGE_KEY_WAIT,
	CBS_CHANGE_END,
};



#define CB_DEF_KEEP_SEQ_SET		(0xff)
	
#define CB_DEF_WIN_USE_BTW_WIN_OFS		(0)	///< �g��BMP�̊Ԃɂ����C�x�߃L����

// ---- �������������牺��ʂœ����ݒ���g�� -----
#define CB_DEF_WIN_T_TALK_CHAR_OFS		(1)		///< �g�̃L�����J�n�ʒu
#define CB_DEF_WIN_T_MENU_CHAR_OFS		(CB_DEF_WIN_T_TALK_CHAR_OFS + TALK_WIN_CGX_SIZ)
#define CB_DEF_WIN_T_USE_OFS			(CB_DEF_WIN_T_MENU_CHAR_OFS + MENU_WIN_CGX_SIZ)	///< bmpwin�ǉ��J�n�ʒu
#define CB_DEF_WIN_CHAR_OFS				(CB_DEF_WIN_USE_BTW_WIN_OFS + CB_DEF_WIN_T_USE_OFS)
// ---- �������R�R�܂œ����ݒ� -----


// ---- ���������ʃE�B���h�E ----
#define CB_DEF_WIN_T_MAIN_X				(2)
#define CB_DEF_WIN_T_MAIN_Y				(21)
#define CB_DEF_WIN_T_MAIN_SX			(27)	///< 
#define CB_DEF_WIN_T_MAIN_SY			(2)
#define CB_DEF_WIN_T_MAIN_SIZE			(CB_DEF_WIN_T_MAIN_SX * CB_DEF_WIN_T_MAIN_SY)
#define CB_DEF_WIN_T_MAIN_SIZE_END		(CB_DEF_WIN_T_MAIN_SIZE + CB_DEF_WIN_CHAR_OFS)

#define CB_DEF_WIN_T_MENU_X				(21)
#define CB_DEF_WIN_T_MENU_Y_1			(15-2)
#define CB_DEF_WIN_T_MENU_Y_2			(11)
#define CB_DEF_WIN_T_MENU_SX			(9)
#define CB_DEF_WIN_T_MENU_SY_1			(4+2)
#define CB_DEF_WIN_T_MENU_SY_2			(8)
#define CB_DEF_WIN_T_MENU_SIZE			(CB_DEF_WIN_T_MENU_SX * CB_DEF_WIN_T_MENU_SY_2)	///< �ł����ق��Ōv�Z
#define CB_DEF_WIN_T_MENU_SIZE_END		(CB_DEF_WIN_T_MENU_SIZE + CB_DEF_WIN_T_MAIN_SIZE_END)
// ---- ���������ʃE�B���h�E�ݒ� ----


// ---- ����������ʃE�B���h�E�ݒ� ----
#define CB_DEF_WIN_B_MAIN_X				(2)			///< ���C��
#define CB_DEF_WIN_B_MAIN_Y				(1)
#define CB_DEF_WIN_B_MAIN_SX			(27)
#define CB_DEF_WIN_B_MAIN_SY			(4)
#define CB_DEF_WIN_B_MAIN_SIZE			(CB_DEF_WIN_B_MAIN_SX * CB_DEF_WIN_B_MAIN_SY)
#define CB_DEF_WIN_B_MAIN_SIZE_END		(CB_DEF_WIN_B_MAIN_SIZE + CB_DEF_WIN_CHAR_OFS)

#define CB_DEF_WIN_LIST_X1				(4-1)
#define CB_DEF_WIN_LIST_X2				(11-1)
#define CB_DEF_WIN_LIST_W				(3+1)//3
#define CB_DEF_WIN_LIST_H				(2)//2

#ifdef SEAL_SBS

	///< ������
	#define CB_DEF_WIN_B_LIST_1_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_1_Y			(2)
	#define CB_DEF_WIN_B_LIST_1_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_1_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_1_SIZE		(CB_DEF_WIN_B_LIST_1_SX * CB_DEF_WIN_B_LIST_1_SY)
	#define CB_DEF_WIN_B_LIST_1_SIZE_END	(CB_DEF_WIN_B_LIST_1_SIZE + CB_DEF_WIN_B_MAIN_SIZE_END)

	#define CB_DEF_WIN_B_LIST_2_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_2_Y			(2)
	#define CB_DEF_WIN_B_LIST_2_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_2_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_2_SIZE		(CB_DEF_WIN_B_LIST_2_SX * CB_DEF_WIN_B_LIST_2_SY)
	#define CB_DEF_WIN_B_LIST_2_SIZE_END	(CB_DEF_WIN_B_LIST_2_SIZE + CB_DEF_WIN_B_LIST_1_SIZE_END)

	#define CB_DEF_WIN_B_LIST_3_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_3_Y			(5)
	#define CB_DEF_WIN_B_LIST_3_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_3_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_3_SIZE		(CB_DEF_WIN_B_LIST_3_SX * CB_DEF_WIN_B_LIST_3_SY)
	#define CB_DEF_WIN_B_LIST_3_SIZE_END	(CB_DEF_WIN_B_LIST_3_SIZE + CB_DEF_WIN_B_LIST_2_SIZE_END)

	#define CB_DEF_WIN_B_LIST_4_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_4_Y			(5)
	#define CB_DEF_WIN_B_LIST_4_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_4_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_4_SIZE		(CB_DEF_WIN_B_LIST_4_SX * CB_DEF_WIN_B_LIST_4_SY)
	#define CB_DEF_WIN_B_LIST_4_SIZE_END	(CB_DEF_WIN_B_LIST_4_SIZE + CB_DEF_WIN_B_LIST_3_SIZE_END)

	#define CB_DEF_WIN_B_LIST_5_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_5_Y			(8)
	#define CB_DEF_WIN_B_LIST_5_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_5_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_5_SIZE		(CB_DEF_WIN_B_LIST_5_SX * CB_DEF_WIN_B_LIST_5_SY)
	#define CB_DEF_WIN_B_LIST_5_SIZE_END	(CB_DEF_WIN_B_LIST_5_SIZE + CB_DEF_WIN_B_LIST_4_SIZE_END)

	#define CB_DEF_WIN_B_LIST_6_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_6_Y			(8)
	#define CB_DEF_WIN_B_LIST_6_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_6_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_6_SIZE		(CB_DEF_WIN_B_LIST_6_SX * CB_DEF_WIN_B_LIST_6_SY)
	#define CB_DEF_WIN_B_LIST_6_SIZE_END	(CB_DEF_WIN_B_LIST_6_SIZE + CB_DEF_WIN_B_LIST_5_SIZE_END)

	#define CB_DEF_WIN_B_LIST_7_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_7_Y			(11)
	#define CB_DEF_WIN_B_LIST_7_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_7_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_7_SIZE		(CB_DEF_WIN_B_LIST_7_SX * CB_DEF_WIN_B_LIST_7_SY)
	#define CB_DEF_WIN_B_LIST_7_SIZE_END	(CB_DEF_WIN_B_LIST_7_SIZE + CB_DEF_WIN_B_LIST_6_SIZE_END)

	#define CB_DEF_WIN_B_LIST_8_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_8_Y			(11)
	#define CB_DEF_WIN_B_LIST_8_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_8_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_8_SIZE		(CB_DEF_WIN_B_LIST_8_SX * CB_DEF_WIN_B_LIST_8_SY)
	#define CB_DEF_WIN_B_LIST_8_SIZE_END	(CB_DEF_WIN_B_LIST_8_SIZE + CB_DEF_WIN_B_LIST_7_SIZE_END)


#else

	///< �c����
	#define CB_DEF_WIN_B_LIST_1_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_1_Y			(2)
	#define CB_DEF_WIN_B_LIST_1_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_1_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_1_SIZE		(CB_DEF_WIN_B_LIST_1_SX * CB_DEF_WIN_B_LIST_1_SY)
	#define CB_DEF_WIN_B_LIST_1_SIZE_END	(CB_DEF_WIN_B_LIST_1_SIZE + CB_DEF_WIN_B_MAIN_SIZE_END)

	#define CB_DEF_WIN_B_LIST_2_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_2_Y			(5)
	#define CB_DEF_WIN_B_LIST_2_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_2_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_2_SIZE		(CB_DEF_WIN_B_LIST_2_SX * CB_DEF_WIN_B_LIST_2_SY)
	#define CB_DEF_WIN_B_LIST_2_SIZE_END	(CB_DEF_WIN_B_LIST_2_SIZE + CB_DEF_WIN_B_LIST_1_SIZE_END)

	#define CB_DEF_WIN_B_LIST_3_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_3_Y			(8)
	#define CB_DEF_WIN_B_LIST_3_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_3_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_3_SIZE		(CB_DEF_WIN_B_LIST_3_SX * CB_DEF_WIN_B_LIST_3_SY)
	#define CB_DEF_WIN_B_LIST_3_SIZE_END	(CB_DEF_WIN_B_LIST_3_SIZE + CB_DEF_WIN_B_LIST_2_SIZE_END)

	#define CB_DEF_WIN_B_LIST_4_X			(CB_DEF_WIN_LIST_X1)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_4_Y			(11)
	#define CB_DEF_WIN_B_LIST_4_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_4_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_4_SIZE		(CB_DEF_WIN_B_LIST_4_SX * CB_DEF_WIN_B_LIST_4_SY)
	#define CB_DEF_WIN_B_LIST_4_SIZE_END	(CB_DEF_WIN_B_LIST_4_SIZE + CB_DEF_WIN_B_LIST_3_SIZE_END)

	#define CB_DEF_WIN_B_LIST_5_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_5_Y			(2)
	#define CB_DEF_WIN_B_LIST_5_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_5_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_5_SIZE		(CB_DEF_WIN_B_LIST_5_SX * CB_DEF_WIN_B_LIST_5_SY)
	#define CB_DEF_WIN_B_LIST_5_SIZE_END	(CB_DEF_WIN_B_LIST_5_SIZE + CB_DEF_WIN_B_LIST_4_SIZE_END)

	#define CB_DEF_WIN_B_LIST_6_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_6_Y			(5)
	#define CB_DEF_WIN_B_LIST_6_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_6_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_6_SIZE		(CB_DEF_WIN_B_LIST_6_SX * CB_DEF_WIN_B_LIST_6_SY)
	#define CB_DEF_WIN_B_LIST_6_SIZE_END	(CB_DEF_WIN_B_LIST_6_SIZE + CB_DEF_WIN_B_LIST_5_SIZE_END)

	#define CB_DEF_WIN_B_LIST_7_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_7_Y			(8)
	#define CB_DEF_WIN_B_LIST_7_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_7_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_7_SIZE		(CB_DEF_WIN_B_LIST_7_SX * CB_DEF_WIN_B_LIST_7_SY)
	#define CB_DEF_WIN_B_LIST_7_SIZE_END	(CB_DEF_WIN_B_LIST_7_SIZE + CB_DEF_WIN_B_LIST_6_SIZE_END)

	#define CB_DEF_WIN_B_LIST_8_X			(CB_DEF_WIN_LIST_X2)			///< ���X�g
	#define CB_DEF_WIN_B_LIST_8_Y			(11)
	#define CB_DEF_WIN_B_LIST_8_SX			(CB_DEF_WIN_LIST_W)
	#define CB_DEF_WIN_B_LIST_8_SY			(CB_DEF_WIN_LIST_H)
	#define CB_DEF_WIN_B_LIST_8_SIZE		(CB_DEF_WIN_B_LIST_8_SX * CB_DEF_WIN_B_LIST_8_SY)
	#define CB_DEF_WIN_B_LIST_8_SIZE_END	(CB_DEF_WIN_B_LIST_8_SIZE + CB_DEF_WIN_B_LIST_7_SIZE_END)

#endif

#define CB_DEF_TPBG_CHAR_OFS			(CB_DEF_WIN_B_LIST_8_SIZE_END)

#define CB_DEF_SW_X						(25)
#define CB_DEF_SW_Y						(6)
// ---- ����������ʃE�B���h�E�ݒ� ----


#define CB_DEF_ICON_OFS_X				(-16)
#define CB_DEF_ICON_OFS_Y				(+12)

enum {
	CB_MODE_SELECT = 0,		///< �ҏW�Ώۂ�I�ԉ��
	CB_MODE_EDIT,			///< �ҏW���
	CB_MODE_SETTING_SET,	///< �Z�b�e�B���O -- �͂߂�
	CB_MODE_SETTING_REMOVE,	///< �Z�b�e�B���O -- �͂���
	CB_MODE_CHANGE,			///< ����ւ�
	CB_MODE_END,			///< �I�� �Ƃɂ����Ō�̓R�R���o�R����݌v
};

#define CB_DEF_MODE_MAX		(CB_MODE_END)

enum {
	CB_ENUM_MENU_FUNC_RET_NONE = 0,
	CB_ENUM_MENU_FUNC_RET_SEQ_PREV,
	CB_ENUM_MENU_FUNC_RET_SEQ_NEXT,
};

// -----------------------------------------
//
//	�����b�Z�[�W�֘A
//
// -----------------------------------------
#define CB_DEF_MSG_ARC				(NARC_msg_ball_custom_dat)		///< �ʏ탁�b�Z�[�W
#define CB_SEAL_MSG_ARC				(NARC_msg_bc_seal_name_dat)		///< �V�[���̖��O
#define CB_SEAL_COMMENT_MSG_ARC		(NARC_msg_seal_comment_dat)		///< �V�[���̐���

#define CB_DEF_MENU_MSG_LEN		(30*2)
#define CB_DEF_INFO_MSG_LEN		(30*2)

#define CB_DEF_NOT_HOLD			(0xFF)
//#define CB_DEF_NOT_ADD			(0xEE)

#define CB_DEF_INFO_MSG_START	(msg_info_00_01)
enum {
	CB_MSG_ID_CLEAR  = 0xFFFF,					///< �N���A
	CB_MSG_ID_CB_SEL = CB_DEF_INFO_MSG_START,	///< �J�v�Z���I��ł�������
	CB_MSG_ID_CB_HDYD,							///< �J�v�Z���ǂ�����H
	CB_MSG_ID_CB_REM,							///< �J�v�Z�����͂�����
	CB_MSG_ID_CB_REP,							///< �ǂ�Ɠ���ւ���H
	CB_MSG_ID_CB_REP_END,						///< ����ւ���
	CB_MSG_ID_EDIT_END,							///< �J�v�Z���ɃV�[�����͂���
	CB_MSG_ID_CON,								///< �m�F��
	CB_MSG_ID_END_QUE,							///< �J�v�Z���f�U�C����ς��Ȃ��ł�߂܂����H
	CB_MSG_ID_NG,								///< ���������Ȃ���I
	CB_MSG_ID_ZERO,								///< �����V�[���Ȃ���I
};

enum {
	CB_PROC_NEXT_MODE_END = 0,					///< �I��
	CB_PROC_NEXT_MODE_LIST,						///< ���X�g
};

// -----------------------------------------
//
//	���ʏ�z�u�{�^��
//
// -----------------------------------------
#define CB_DEF_MAIN_BG_PAL	(0)
#define CB_DEF_MAIN_BG2_PAL	(1)
#define CB_DEF_SUB_BG_PAL	(0)
enum {
	CB_ENUM_BHIT_SEAL_1 = 0,	///< seal ��
	CB_ENUM_BHIT_SEAL_2,
	CB_ENUM_BHIT_SEAL_3,
	CB_ENUM_BHIT_SEAL_4,
	CB_ENUM_BHIT_SEAL_5,		///< seal �E
	CB_ENUM_BHIT_SEAL_6,
	CB_ENUM_BHIT_SEAL_7,
	CB_ENUM_BHIT_SEAL_8,
	CB_ENUM_BHIT_UP,
	CB_ENUM_BHIT_DOWN,
	CB_ENUM_BHIT_CON,
	CB_ENUM_BHIT_DEC,
	CB_ENUM_BHIT_END,
	
	CB_ENUM_BTN_NUM,		///< BHIT_SEAL�Ɉ��p��
};

enum {
	CB_BHIT_SEAL_0	= CB_ENUM_BTN_NUM,
	CB_BHIT_SEAL_1,
	CB_BHIT_SEAL_2,
	CB_BHIT_SEAL_3,
	CB_BHIT_SEAL_4,
	CB_BHIT_SEAL_5,
	CB_BHIT_SEAL_6,
	CB_BHIT_SEAL_7,
	
	CB_BHIT_SEAL_MAX,
};

#define CB_DEF_HIT_TBL_MAX	(CB_BHIT_SEAL_MAX)	///< �Œ�{�^���{�V�[��

typedef struct {
	
	CATS_ACT_PTR	cap[ CB_ENUM_BTN_NUM ];
	
} TUSUALLY_BTN;


typedef struct {
	
	int no;			///< ���y�[�W�ڂ�
	int max;		///< ���y�[�W�܂ł��邩
	
	u8	item[ CB_DEF_PAGE_ITEMS ];	///< ���݂̃A�C�e��
	
} TPAGE_DATA;

// -----------------------------------------
//
//	�� �f�[�^�\�z�p
//
// -----------------------------------------
typedef struct {

	int 			poke_cnt;					///< �莝���̃J�Y
	POKEMON_PARAM*	poke_para[ TEMOTI_POKEMAX ];///< �莝���|�P����
	POKEPARTY*		pparty;
	CB_SAVE_DATA*	save_data;					///< �Z�[�u�f�[�^
	CONFIG*			cfg;						///< config
	SAVEDATA*		save;						///< save
	
	u8				select_pos;
	u8				proc_next_mode;
	
} CB_PROC_WORK;

enum {
	CB_ENUM_FONT_OAM_1 = 0,
	CB_ENUM_FONT_OAM_2,
	CB_ENUM_FONT_OAM_MAX,
};

// -----------------------------------------
//
//	�� ���C�����[�N
//
// -----------------------------------------
///< system
typedef struct {

	int					hold;					///< �V�[���z�[���h
	BOOL				main_tp_active;			///< ���C���p�l���̑���t���O
	
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;

	GF_BGL_INI*			bgl;
	PALETTE_FADE_PTR	pfd;
	GF_BGL_BMPWIN		win[ CB_ENUM_WIN_MAX ];
	BMP_MENULIST_DATA*	bml;
	BMPMENU_WORK*		bmw;
	
	SOFT_SPRITE_MANAGER* ssm_p;
	SOFT_SPRITE*		 ssp;
	int					 height;
	
	IMC_HAND			pen;		///< hand
	
	BUTTON_MAN*			btn;
	
	RECT_HIT_TBL		hit_tbl[ CB_DEF_HIT_TBL_MAX ];
	
	TOUCH_SW_SYS*		tss;
	
	BES_PTR				bes;
	BMS_PTR				bms;
	
	GF_G3DMAN*			g3Dman;
	
	/// --- font
	FONTOAM_SYS_PTR		fontoam_sys;
	FONTOAM_OBJ_PTR		font_obj[ CB_ENUM_FONT_OAM_MAX ];
	CHAR_MANAGER_ALLOCDATA	font_vram[ CB_ENUM_FONT_OAM_MAX ];
	
	BOOL				sub_tcb_active;
	
	POKE_ANM_SYS_PTR	pas;
	
	BOOL				bEdit;
	
} CB_SYS;

///< �}�[�N�{�[��
typedef struct {
	
	int poke_idx;								///< �|�P�����Ɏ������Ă��邩
	int edit_flag;								///< �ҏW�ς݂�
	CATS_ACT_PTR	cap;						///< OBJ
	
} CB_MARK_OBJ;

///< �G�f�B�b�g�f�[�^
typedef struct {
	
	int	poke_idx;								///< �Z�[�u�Ɨ��ށA�����Ă�|�P����NO
	CB_CORE*		core;						///< �Z�[�u�Ɨ��ށA�R�A�f�[�^
	
} CB_EDIT_DATA;

///< �V�[���f�[�^
typedef struct {
	BOOL			pop;						///< �|�b�v�������H
	
	u8				id;							///< �V�[��ID
	u8				x;
	u8				y;
	
	CATS_ACT_PTR	cap;

	RECT_HIT_TBL*	hit;						///< �����蔻��
	
} CB_SEAL_ONE;

typedef struct _CB_SEAL_ONE * SEAL_PTR;

///< main
typedef struct {
	
	CB_PROC_WORK*		cb_pw;					///< �O��������炤�f�[�^(save)

	CB_EDIT_DATA		cb_edit_data[ CB_DEF_CORE_MAX ];///< �ҏW���̃J�X�^���{�[��
	CB_ITEM_DATA*		cb_item_data;			///< �����V�[��
	
	CB_CORE				backup_edit;			///< �o�b�N�A�b�v �ҏW
	u8					backup_item[ CB_DEF_ITEM_DATA_NUM ];

	CB_SYS	sys;								///< �V�X�e��

	CB_MARK_OBJ			mo[ CB_DEF_CORE_MAX ];	///< �}�[�NOBJ
	CATS_ACT_PTR		cap_cur[2];
	CATS_ACT_PTR		icon[ TEMOTI_POKEMAX ];	///< �莝���|�P�����A�C�R��
	CATS_ACT_PTR		piko[ 4 ];

	CB_SEAL_ONE			seal[ CB_DEF_SEAL_MAX ];///< �V�[��
	int					seal_pri[ CB_DEF_SEAL_MAX ];

	int	select[2];								///< �I�𒆃{�[��

	int mode;									///< ��ʂ̃��[�h
	int next_mode;								///< ���̃��[�h
	int seq;									///< ��ʓ��ł̃V�[�P���X
	int keep_seq;								///< �ۑ�����V�[�P���X
	int sub_seq;								///< �T�u�V�[�P���X
	int sub_work;
	
	TUSUALLY_BTN		button_obj;				///< �ʏ�z�u����Ă���{�^��
	TPAGE_DATA			page;					///< �y�[�W���

	POKEMON_PARAM*		test_pp;

} CB_MAIN_WORK;



///< ���j���[
typedef struct {

	int	msg_id;
	u32 param;
	
} TCB_MENU_PARAM;

extern const TCB_MENU_PARAM CB_ParamTable[ CB_DEF_MODE_MAX ];


typedef int (*pCB_Menu_Func)(CB_MAIN_WORK* cbmw);

extern void CB_Test_PokemonSSP_Add(CB_MAIN_WORK* cbmw);
extern void CB_Test_PokemonSSP_AnimeInit(CB_MAIN_WORK* cbmw);
extern void CB_Test_PokemonSSP_Del(CB_MAIN_WORK* cbmw);
extern void CB_Test_PokemonSSP_Vanish(CB_MAIN_WORK* cbmw, int flag);

extern void BackupEditData_Make(CB_MAIN_WORK* cbmw);
extern void BackupEditData_Recover(CB_MAIN_WORK* cbmw);
extern void BackupItemData_Make(CB_MAIN_WORK* cbmw);
extern void BackupItemData_Recover(CB_MAIN_WORK* cbmw);
	
///< cb_main.c
extern BOOL CustomMain_Executed(CB_MAIN_WORK* cbmw);
extern void CB_Tool_SystemInit(int heap);
extern void CB_Tool_SystemDelete(int heap);
extern void CB_Tool_Battle_VramBankSet(GF_BGL_INI *bgl);
extern void CB_Tool_VBlank(void* work);
extern void CB_Tool_ButtonInit(CB_MAIN_WORK* cbmw);

// font oam
extern void FontOam_SysInit(CB_MAIN_WORK* cbmw);
extern void FontOam_SysDelete(CB_MAIN_WORK* cbmw);
extern void FontOam_ResourceLoad(CB_MAIN_WORK* cbmw);
extern void FontOam_Add(CB_MAIN_WORK* cbmw);
extern void FontOam_Enable(CB_MAIN_WORK* cbmw, BOOL flag);
extern void FontOam_Create(CB_MAIN_WORK* cbmw, int no, int x, int y, int pal_offset);

///< cb_sys.c
extern BOOL CB_Sys_IsSubTCB(CB_MAIN_WORK* cbmw);
extern void CB_Sys_MainTPSet(CB_MAIN_WORK* cbmw, BOOL active);
extern int CB_Tool_IsEdit(CB_CORE* core);
extern int CB_Tool_BallStatusCheck(CB_MAIN_WORK* cbmw, int no);
extern void CB_Tool_ButtonAnime(CATS_ACT_PTR cap, int event);
extern void CB_Tool_ButtonAutoUpdate(CB_MAIN_WORK* cbmw);
extern void CB_Tool_ButtonCallBack( u32 button, u32 event, void* work );
extern u8 CBProc_SelectPosGet(CB_PROC_WORK* pw);
extern void CBProc_SelectPosSet(CB_PROC_WORK* pw, u8 pos);
extern POKEMON_PARAM* CBProc_PokeParaGet(CB_PROC_WORK* pw, int no);
extern u8 CBProc_SelectPosGet(CB_PROC_WORK* pw);
extern void CBProc_SelectPosSet(CB_PROC_WORK* pw, u8 pos);
extern u8 CBProc_NextModeGet(CB_PROC_WORK* pw);
extern void CBProc_NextModeSet(CB_PROC_WORK* pw, u8 mode);
extern void CustomBallEdit_Start(FIELDSYS_WORK *fsys);
extern void EventCmd_CustomBallEditProc(GMEVENT_CONTROL * event, SAVEDATA* save);
extern void CB_Tool_TestPokemonCreate(CB_MAIN_WORK* cbmw);
extern void CB_Tool_DefaultBlendSet(void);

///< cb_seal.c
extern void HitTable_CreateCap(RECT_HIT_TBL* tbl, CATS_ACT_PTR cap, BOOL tp_set);

extern void CBS_ResLoad(CB_MAIN_WORK* cbmw, u8 one_id, u8 id);
extern void CBS_LoadInit(CB_MAIN_WORK* cbmw);
extern int	CBS_SearchPop(CB_MAIN_WORK* cbmw, u8 id);
extern BOOL CBS_IsPop(CB_MAIN_WORK* cbmw);
extern BOOL CBS_Add(CB_MAIN_WORK* cbmw, u8 id);
extern void CBS_PriSetTop(CB_MAIN_WORK* cbmw, u8 id);
extern BOOL CBS_SealHold(CB_MAIN_WORK* cbmw, u32 event, u8 id);
extern void CBS_Delete(CB_MAIN_WORK* cbmw);
extern void CBS_Enable(CB_MAIN_WORK* cbmw, int flag);

extern BOOL CBS_ReleasePointCheck(CB_MAIN_WORK* cbmw, int id);
extern void CBS_Release(CB_MAIN_WORK* cbmw, int id);
extern void CBS_ReleasePointCheckTypeSet(CB_MAIN_WORK* cbmw, int id);

extern int  CBS_PtoP(s16 x1, s16 y1, s16 x2, s16 y2);

extern BOOL CBS_CheckEditData(CB_MAIN_WORK* cbmw);
extern void CBS_OldEditDataSet(CB_MAIN_WORK* cbmw);
extern void CBS_EditDataRefrect(CB_MAIN_WORK* cbmw, int id);
extern void CBS_EditData_Save(CB_MAIN_WORK* cbmw);
extern void CBS_TestCoreData_Create(CB_CORE* core, CB_MAIN_WORK* cbmw);

extern void CBS_Pri_HitTbl_Sort(CB_MAIN_WORK* cbmw);

extern void CBS_Seal_ViewPosSet(CB_MAIN_WORK* cbmw);
extern void CBS_Seal_EditPosSet(CB_MAIN_WORK* cbmw);


extern int CBS_PublicTool_RangeGet(CB_SEAL* seal);
extern int CBS_PublicTool_RangeWaitGet(CB_SEAL* seal);


///< cb_disp.c
extern void CB_BMP_SelectWinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, CB_MAIN_WORK* cbmw, int no);
extern void CB_BMP_SelectWinDel(CB_MAIN_WORK* cbmw);
extern void CB_SelectThisPosGet(int pos, s16* x, s16* y);
extern void CB_Tool_PokeIcon_Load(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Add(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_CheckPosSetup(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Update(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Del(CB_MAIN_WORK* cbmw);
extern void CB_Tool_MarkObj_SetUp(CB_MAIN_WORK* cbmw);
extern void CB_Tool_CatsInit(CB_SYS* sys);
extern void CB_Tool_CatsDelete(CB_SYS* sys);
extern void SubObj_ResLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, int chr_id, int pal_id, int cel_id, int cla_id, int vram, int pal_tg, int palnum);
extern void CB_Tool_SubSelect_ObjAdd(CB_MAIN_WORK* cbmw);
extern void SubSelect_ObjRefrect(CB_MAIN_WORK* cbmw);
extern void CB_Tool_CoreDataChange(CB_MAIN_WORK* cbmw, int from, int to);
extern void SubSelect_ObjUpdate(CB_MAIN_WORK* cbmw);
extern void SubSelect_ObjDelete(CB_MAIN_WORK* cbmw);
extern void CB_BMP_WindowResLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype);
extern void CB_BMP_WindowResLoad_Sub(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype);
extern void CB_BMP_InfoMessageSet(GF_BGL_BMPWIN * win, int mes_id);
extern void CB_BMP_WindowAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs);
extern void CB_BMP_WindowAddSimple(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs);
extern void CB_BMP_SealNumWinAdd(CB_MAIN_WORK* cbmw);
extern void CB_BMP_SealNumWinPrint(CB_MAIN_WORK* cbmw);
extern void CB_BMP_SealNumWinPrint_No(CB_MAIN_WORK* cbmw, int no);
extern void CB_BMP_SealNumWinDel(CB_MAIN_WORK* cbmw);
extern void CB_BMP_SealNameSet(GF_BGL_BMPWIN * win, int id);
extern void CB_DispOn(void);
extern void CB_WipeFadeIn(void);
extern void CB_WipeFadeOut(void);
extern void CB_Select_TopResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Select_BottomResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Edit_BottomResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_SealBTN_ResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_ResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Add(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Enable(CB_MAIN_WORK* cbmw, int flag);
extern void CB_Tool_BTN_Update(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Delete(CB_MAIN_WORK* cbmw);
extern void CB_Particle_Init(void);
extern void CB_Particle_Main(void);

extern void PageData_Create(CB_MAIN_WORK* cbmw, int page_no);
extern void PageData_ResourceLoad(CB_MAIN_WORK* cbmw);
extern void PageData_Add(CB_MAIN_WORK* cbmw);
extern void PageData_Del(CB_MAIN_WORK* cbmw);

extern void CB_View_Scroll(CB_MAIN_WORK* cbmw, s8 r_vec, int wait);


extern void Piko_ResLoad(CB_MAIN_WORK* cbmw);
extern void Piko_Add(CB_MAIN_WORK* cbmw);
extern void Piko_Delete(CB_MAIN_WORK* cbmw);
extern void Piko_Update(CB_MAIN_WORK* cbmw);
extern void Piko_Enable(CB_MAIN_WORK* cbmw, int flag);


extern void			CBSimpleSetUp(void);
extern GF_G3DMAN*	CB_3D_Init(void);

///< 

extern void CBS_SVSort(CB_MAIN_WORK* cbmw);

extern void CB_Tool_CoreDataRemove(CB_MAIN_WORK* cbmw, int this);


// =============================================================================
//
//
//	���V�[���f�[�^�擾�֐�
//
//
// =============================================================================
enum {
	CB_SEAL_DMY	= 0,

	CB_SEAL_HART01,			// �n�[�g�V�[���` 
	CB_SEAL_HART02,         // �n�[�g�V�[���a
	CB_SEAL_HART03,         // �n�[�g�V�[���b
	CB_SEAL_HART04,         // �n�[�g�V�[���c
	CB_SEAL_HART05,         // �n�[�g�V�[���d
	CB_SEAL_HART06,         // �n�[�g�V�[���e
	CB_SEAL_STAR01,         // �X�^�[�V�[���`
	CB_SEAL_STAR02,         // �X�^�[�V�[���a
	CB_SEAL_STAR03,         // �X�^�[�V�[���b
	CB_SEAL_STAR04,         // �X�^�[�V�[���c
	CB_SEAL_STAR05,         // �X�^�[�V�[���d
	CB_SEAL_STAR06,         // �X�^�[�V�[���e
	CB_SEAL_LINE01,         // ���C���V�[���`
	CB_SEAL_LINE02,         // ���C���V�[���a
	CB_SEAL_LINE03,         // ���C���V�[���b
	CB_SEAL_LINE04,         // ���C���V�[���c
	CB_SEAL_KEMURI01,       // �X���[�N�V�[���`
	CB_SEAL_KEMURI02,       // �X���[�N�V�[���a
	CB_SEAL_KEMURI03,       // �X���[�N�V�[���b
	CB_SEAL_KEMURI04,       // �X���[�N�V�[���c
	CB_SEAL_TUNDER01,       // �G���L�V�[���`
	CB_SEAL_TUNDER02,       // �G���L�V�[���a
	CB_SEAL_TUNDER03,       // �G���L�V�[���b
	CB_SEAL_TUNDER04,       // �G���L�V�[���c
	CB_SEAL_BALL01,         // �o�u���V�[���`
	CB_SEAL_BALL02,         // �o�u���V�[���a
	CB_SEAL_BALL03,         // �o�u���V�[���b
	CB_SEAL_BALL04,         // �o�u���V�[���c
	CB_SEAL_FIRE01,         // �t�@�C�A�V�[���`
	CB_SEAL_FIRE02,         // �t�@�C�A�V�[���a
	CB_SEAL_FIRE03,         // �t�@�C�A�V�[���b
	CB_SEAL_FIRE04,         // �t�@�C�A�V�[���c
	CB_SEAL_PAPER01,        // �p�[�e�B�V�[���`
	CB_SEAL_PAPER02,        // �p�[�e�B�V�[���a
	CB_SEAL_PAPER03,        // �p�[�e�B�V�[���b
	CB_SEAL_PAPER04,        // �p�[�e�B�V�[���c
	CB_SEAL_HANA01,         // �t�����[�V�[���`
	CB_SEAL_HANA02,         // �t�����[�V�[���a
	CB_SEAL_HANA03,         // �t�����[�V�[���b
	CB_SEAL_HANA04,         // �t�����[�V�[���c
	CB_SEAL_HANA05,         // �t�����[�V�[���d
	CB_SEAL_HANA06,         // �t�����[�V�[���e
	CB_SEAL_ONPU01,         // �\���O�V�[���`
	CB_SEAL_ONPU02,         // �\���O�V�[���a
	CB_SEAL_ONPU03,         // �\���O�V�[���b
	CB_SEAL_ONPU04,         // �\���O�V�[���c
	CB_SEAL_ONPU05,         // �\���O�V�[���d
	CB_SEAL_ONPU06,         // �\���O�V�[���e
	CB_SEAL_ONPU07,         // �\���O�V�[���f
	CB_SEAL_ALPHA_A,        // �`�V�[��
	CB_SEAL_ALPHA_B,        // �a�V�[��
	CB_SEAL_ALPHA_C,        // �b�V�[��
	CB_SEAL_ALPHA_D,        // �c�V�[��
	CB_SEAL_ALPHA_E,        // �d�V�[��
	CB_SEAL_ALPHA_F,        // �e�V�[��
	CB_SEAL_ALPHA_G,        // �f�V�[��
	CB_SEAL_ALPHA_H,        // �g�V�[��
	CB_SEAL_ALPHA_I,        // �h�V�[��
	CB_SEAL_ALPHA_J,        // �i�V�[��
	CB_SEAL_ALPHA_K,        // �j�V�[��
	CB_SEAL_ALPHA_L,        // �k�V�[��
	CB_SEAL_ALPHA_M,        // �l�V�[��
	CB_SEAL_ALPHA_N,        // �m�V�[��
	CB_SEAL_ALPHA_O,        // �n�V�[��
	CB_SEAL_ALPHA_P,        // �o�V�[��
	CB_SEAL_ALPHA_Q,        // �p�V�[��
	CB_SEAL_ALPHA_R,        // �q�V�[��
	CB_SEAL_ALPHA_S,        // �r�V�[��
	CB_SEAL_ALPHA_T,        // �s�V�[��
	CB_SEAL_ALPHA_U,        // �t�V�[��
	CB_SEAL_ALPHA_V,        // �u�V�[��
	CB_SEAL_ALPHA_W,        // �v�V�[��
	CB_SEAL_ALPHA_X,        // �w�V�[��
	CB_SEAL_ALPHA_Y,        // �x�V�[��
	CB_SEAL_ALPHA_Z,        // �y�V�[��
	CB_SEAL_ALPHA_MARK_1,   // �т�����V�[��
	CB_SEAL_ALPHA_MARK_2,	// �͂ĂȃV�[��
	CB_SEAL_SP_1,           // ���L�b�h�V�[��
	CB_SEAL_SP_2,           // �΂��͂V�[��
	CB_SEAL_SP_3,           // �L���L���V�[��
};

extern int Seal_Li_CharArcGet(u8 id);
extern int Seal_CharArcGet(u8 id);
extern int Seal_NameGet(u8 id);
extern int Seal_EffectGet(u8 id);
extern int Seal_TypeGet(u8 id);
extern int Seal_PriceGet(u8 id);
extern int Seal_CommentGet(u8 id);


#endif

