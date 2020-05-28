//==============================================================================
/**
 * @file	actin_input.c
 * @brief	���Z�͕�����͉�ʏ���
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "con_tool.h"
#include "actin_id.h"
#include "actin_input.h"
#include "battle/wazatype_panel.h"
#include "gflib/touchpanel.h"
#include "contype_icon.h"
#include "poketool/waza_tool.h"
#include "aci_tool.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/fontoam.h"
#include "msgdata/msg_cmsg_acting.h"

#include "contest/contest_cursor.h"



//==============================================================================
//	�萔��`
//==============================================================================
//�f�o�b�O�p��`�F�P��S_MSG���g�p���������Ȍ`�B�O��S_MSG�Ή�Expand���p�ӂ����܂ł̎b�菈��
#define S_MSG_DEBUG		(0)

//--------------------------------------------------------------
//	���b�Z�[�W�֌W
//--------------------------------------------------------------
///S_MSG�Ŏg�p����ԍ��F�|�P�����I��(�Z�͈�)�̎��̃|�P������
#define S_MSG_POKESELE_NAME		(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�X�N���[���o�b�t�@�ԍ�
enum{
	SCRNBUF_BACKGROUND,
	SCRNBUF_TITLE,
	SCRNBUF_COMMAND_WAZA,
	SCRNBUF_COMMAND_JUDGE,
	SCRNBUF_COMMAND_BACKGROUND,
	
	SCRNBUF_MAX,
};

///�X�N���[���o�b�t�@�ɑΉ������X�N���[���f�[�^��ID
///	��SCRNBUF�ƕ��т𓯂��ɂ��Ă������ƁI�I
ALIGN4 static const u16 ScrnArcDataNo[] = {
	CON_SUB_BG_NSCR_BIN,
	CON_TIT_NSCR_BIN,
	CON_WAZA_BUT_NSCR_BIN,
	CON_SINSA_BUT_NSCR_BIN,
	CON_ENGI_SUB_BG_NSCR_BIN,
};


///�p���b�g�o�b�t�@�ԍ�
enum{
	PALBUF_TITLE,
	PALBUF_COMMAND,
	
	PALBUF_MAX,
};

///�p���b�g�o�b�t�@�ɑΉ������X�N���[���f�[�^��ID
///	��PALBUF�ƕ��т𓯂��ɂ��Ă������ƁI�I
ALIGN4 static const u16 PaletteArcDataNo[] = {
	CONTEST_SUB_NCLR,
	CON_ENGI_BUT_NCLR,
};

//--------------------------------------------------------------
//	���[�J��TCB�v���C�I���e�B
//--------------------------------------------------------------
#define VWAIT_TCBPRI_CGRTRANS			(10)
#define VWAIT_TCBPRI_FRAMEVISIBLE		(10)
#define VWAIT_TCBPRI_BACKSCRN_VISIBLE	(10)
#define VWAIT_TCBPRI_CGRPARAM_TRANS		(20)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�A���Z�g�p�ׁ̈A�I���o���Ȃ��Ȃ��Ă��鎞�̃p�l���t�F�[�hEVY
#define NOT_TOUCH_WAZA_EVY		(8)
///�A���Z�g�p�ׁ̈A�I���o���Ȃ��Ȃ��Ă��鎞�̃p�l���t�F�[�h�J���[
#define NOT_TOUCH_WAZA_COLOR	(0x6f39)
///�A���Z�g�p�ׁ̈A�I���o���Ȃ��Ȃ��Ă���Z��1���Ȃ��ꍇ�̏������p�����[�^
#define NOT_TOUCH_WAZA_POS_NULL	(0xff)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///BG�w��Ȃ�
#define NONE_ID			(0xffff)

///BG�g�p�ʐ�
#define ACI_BG_NUM		(4)

///�W���p���b�g�f�[�^�g�p�{��
#define BASE_PLTT_NUM	(16)

///makedata_no�����l(���g�p���)
#define MAKEDATA_NO_INIT	(-1)

///�R���e�X�g���͉�ʂŎg�p�o����BG��CGR�T�C�Y
#define ACI_BG_CGR_SIZE			(0x6000)

///BG�X�N���[���̃N���A�R�[�h
#define BG_CLEAR_CODE			(0)

///��������1�Ώۖ�
#define BLD_PLANE_1		(GX_BLEND_PLANEMASK_BG0)
///��������2�Ώۖ�
#define BLD_PLANE_2		(GX_BLEND_BGALL)
///��1�Ώۖʂɑ΂��郿�u�����f�B���O�W��
#define BLD_ALPHA_1		(9)
///��2�Ώۖʂɑ΂��郿�u�����f�B���O�W��
#define BLD_ALPHA_2		(8)

///�R���e�X�g�����N�A�^�C�v��\������v���[�g�����̃p���b�g�ԍ�
#define PLATE_PALNO		(2)

///�I���o���Ȃ��p�l���̊G�̃p���b�g�ԍ�
#define ACI_NOT_SELECT_PANEL_PALNO		(0x8)

///�R�}���h�I����ʂ̃o�b�N�O���E���h�̃p���b�g�ԍ�
#define COMMAND_BACKGROUND_PALNO		(0xe)

//--------------------------------------------------------------
//	�X�N���[���X�N���[���l
//--------------------------------------------------------------
///TYPE_A��BG�\�����Ƀ^�b�`�p�l���������ꂽ����Y�����ɃX�N���[��������l(�G�t�F�N�g��)
#define SCRN_SCROLL_A_EFF_Y				(-2)
///TYPE_A��BG�\�����Ƀ^�b�`�p�l���������ꂽ����Y�����ɃX�N���[��������l(�G�t�F�N�g��)
#define SCRN_SCROLL_BACK_A_EFF_Y		(1)

//--------------------------------------------------------------
//	�^�b�`�t�F�[�h
//--------------------------------------------------------------
///�^�b�`�������̃{�^���t�F�[�hEVY
#define TOUCH_FADE_EVY		(10 << 8)
///�^�b�`�������̃{�^���t�F�[�hEVY���Z�l
#define TOUCH_FADE_ADD_EVY	(TOUCH_FADE_EVY / 2)

//--------------------------------------------------------------
//	�J�[�\��
//--------------------------------------------------------------
///�J�[�\���̃A�N�^�[�\�t�g�v���C�I���e�B
#define SOFTPRI_CURSOR				(5)
///�J�[�\����BG�v���C�I���e�B
#define BGPRI_CURSOR				(0)

//--------------------------------------------------------------
//	�t�H���gOBJ
//--------------------------------------------------------------
///�t�H���gOBJ�̕����ԊuX
#define PANEL_MSG_MARGIN		(0)
///�t�H���gOBJ�̍ő�g�pOAM��
#define PANEL_MSG_MAXOAM		(8)
///�t�H���gOBJ�̃A�N�^�[�\�t�g�v���C�I���e�B
#define PANEL_MSG_SOFTPRI		(100)
///�t�H���gOBJ��BG�v���C�I���e�B
#define PANEL_MSG_BGPRI			(0)

enum{
	FONTOAM_LEFT,		///<X���[���W
	FONTOAM_CENTER,		///<X���S���W
};

///�t�H���gOBJ�A�N�^�[���[�N�Ŏg�p����Y�����̈ʒu
enum{
	//WALL
	FA_NO_CONRANK = 0,				///<�R���e�X�g�����N
	FA_NO_CONTYPE,				///<�R���e�X�g�^�C�v
	
	//WAZA
	FA_NO_WAZA_1 = 0,			///<�莝���Z1
	FA_NO_WAZA_2,				///<�莝���Z2
	FA_NO_WAZA_3,				///<�莝���Z3
	FA_NO_WAZA_4,				///<�莝���Z4
	FA_NO_SETUMEI_1_U,			///<�Z1�̐�����i
	FA_NO_SETUMEI_2_U,			///<�Z1�̐�����i
	FA_NO_SETUMEI_3_U,			///<�Z1�̐�����i
	FA_NO_SETUMEI_4_U,			///<�Z1�̐�����i
	FA_NO_SETUMEI_1_D,			///<�Z2�̐������i
	FA_NO_SETUMEI_2_D,			///<�Z2�̐������i
	FA_NO_SETUMEI_3_D,			///<�Z2�̐������i
	FA_NO_SETUMEI_4_D,			///<�Z2�̐������i
	
	//JUDGE
	FA_NO_JUDGE_1 = 0,
	FA_NO_JUDGE_2,
	FA_NO_JUDGE_3,
	FA_NO_JUDGE_MODORU,
	
	FA_NO_MAX = FA_NO_SETUMEI_4_D + 1,		///<�t�H���gOBJ����x�ɏo����ő吔
};

///�Z���t�H���gOBJ�̕\�����W
ALIGN4 static const u16 FontWazaPos[][2] = {	//0:X, 1:Y
	{2 * 8 + 3, 4 * 8},		//X�͍��[���W
	{0x12 * 8 + 3, 4 * 8},
	{2 * 8 + 3, 0x10 * 8},
	{0x12 * 8 + 3, 0x10 * 8},
};

///�Z�������t�H���gOBJ�̕\�����W
ALIGN4 static const u16 FontSetumeiPos[][2][2] = {	//[no][UP,DOWN][X,Y]
	{
		{2 * 8 + 3, 8 * 8},		//X�͍��[���W
		{2 * 8 + 3, 10 * 8},		//X�͍��[���W
	},
	{
		{0x12 * 8 + 3, 8 * 8},
		{0x12 * 8 + 3, 10 * 8},
	},
	{
		{2 * 8 + 3, 0x14 * 8},
		{2 * 8 + 3, 0x16 * 8},
	},
	{
		{0x12 * 8 + 3, 0x14 * 8},
		{0x12 * 8 + 3, 0x16 * 8},
	},
};

///�R�����t�H���gOBJ�̕\�����W
ALIGN4 static const u16 FontJudgePos[][2] = {	//X,Y
	{5 * 8, 9 * 8},		//X�̓Z���^�[���W
	{16 * 8, 9 * 8},
	{0x1b * 8, 9 * 8},
};

///�R���I����ʁF�u���ǂ�v�̃t�H���gOBJ�\�����WX(�Z���^�[���W)
#define FONT_JUDGE_MODORU_X		(128)
///�R���I����ʁF�u���ǂ�v�̃t�H���gOBJ�\�����WY
#define FONT_JUDGE_MODORU_Y		(0x14 * 8 + 4)

///�R���e�X�g�����N�t�H���gOBJ�̕\�����WX
#define FONT_CONRANK_POS_X		(128)
///�R���e�X�g�����N�t�H���gOBJ�̕\�����WY
#define FONT_CONRANK_POS_Y		(8*0x10-1)
///�R���e�X�g�^�C�v�t�H���gOBJ�̕\�����WX
#define FONT_CONTYPE_POS_X		(128)
///�R���e�X�g�^�C�v�t�H���gOBJ�̕\�����WY
#define FONT_CONTYPE_POS_Y		(8*0x14-1)

//--------------------------------------------------------------
//	�p���b�g�֘A��`
//--------------------------------------------------------------
///�t�H���gOBJ�̃p���b�g�ԍ��I�t�Z�b�g
enum{
	PALOFS_CONRANK = 0,
	PALOFS_WAZA = 0,
	PALOFS_SETUMEI = 0,
	PALOFS_JUDGE = 0,
};

#define MSGCOLOR_CONRANK		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_WAZA			(GF_PRINTCOLOR_MAKE(1, 7, 8))
#define MSGCOLOR_SETUMEI		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_JUDGE			(GF_PRINTCOLOR_MAKE(1, 9, 0xa))

//--------------------------------------------------------------
//	�G�t�F�N�gTCB
//--------------------------------------------------------------
///�p�l�����^�b�`������A�G�t�F�N�g�ő҂t���[����
#define SCRN_TOUCH_WAIT			(0)
///�p�l�����^�b�`������A�G�t�F�N�g�ő҂t���[����
#define SCRN_TOUCH_ANM_WAIT		(0)

//--------------------------------------------------------------
//	�Z�^�C�v
//--------------------------------------------------------------
///�Z�^�C�v�̃p���b�g�J�n�ʒu
#define WAZATYPE_START_PALPOS	(4)

//--------------------------------------------------------------
//	AP�l
//--------------------------------------------------------------
///AP�l�n�[�g�̕\�����W
ALIGN4 static const AppHeartPos[][2] = {	//X, Y
	{7*8 + 4 + 3, 6*8 + 4},
	{0x17*8 + 4 + 3, 6*8 + 4},
	{7*8 + 4 + 3, 0x12*8 + 4},
	{0x17*8 + 4 + 3, 0x12*8 + 4},
};
///AP�l�n�[�g�ׂ̗̃n�[�g�Ԃ̃X�y�[�X
#define APP_HEART_SPACE_X		(8)


//==============================================================================
//	�\���̒�`
//==============================================================================
///���Z�͓��͉�ʃJ�[�\���ʒu�L��
typedef struct{
	s8 waza_x;
	s8 waza_y;
	s8 judge_x;
	s8 judge_y;
}ACI_CURSOR_SAVE;

///�J�[�\���ړ��p���[�N
typedef struct{
	u8 cursor_on;			///<TRUE�F�J�[�\���\�����
	s8 y_menu;				///<�K�w���j���[�̈ʒu(Y)
	s8 x_menu;				///<�������j���[�̈ʒu(X)
	
	u8 dummy;
}CURSOR_MOVE;

///�X�N���[�������������͈͎̔w��\����
typedef struct{
	s32 top;
	s32 bottom;
	s32 left;
	s32 right;
}REWRITE_SCRN_RECT;

///CGR�]���A�j�����s���͈̔̓f�[�^
typedef struct{
	u16 dest_x;			///<�]����X�J�n�ʒu(�L�����P��)
	u16 dest_y;			///<�]����Y�J�n�ʒu(�L�����P��)
	u16 src_x;			///<�]����X�J�n�ʒu(�L�����P��)
	u16 src_y;			///<�]����Y�J�n�ʒu(�L�����P��)
	u16 size_x;			///<X�]���T�C�Y(�L�����P��)
	u16 size_y;			///<Y�]���T�C�Y(�L�����P��)
}CGR_TRANS_RECTDATA;

///CGR�]���A�j�����s���̃p�����[�^
typedef struct{
	TCB_PTR v_tcb;		///<V�u�����N�]�������s����TCB�̃|�C���^
	u8 *dest_vram;		///<VRAM�]����A�h���X
	void *arc_data;		///<�A�[�J�C�u�����L�����t�@�C���̃|�C���^
	u8 *raw_data;		///<�A�[�J�C�u�����L�����t�@�C���̃L�����f�[�^�擪�A�h���X
	CGR_TRANS_RECTDATA rd;	///<CGR�]���A�j�����s���͈̔̓f�[�^
	u16 x_len;			///<�L�����t�@�C����X��(�o�C�g�P��)
}CGR_TRANS_PARAM;

///paracgr�\���̂Ŏg�p����A�N�^�[�|�C���^�̐�
#define PARACGR_CAP_MAX			(3)
///�{�^���̃A�j���p�^�[����
#define BUTTON_ANM_NUM			(2)

///�G�t�F�N�gTCB�p�̃��[�N
typedef struct{
	s16 seq;
	s16 wait;
	union{
		struct{		//CGR�]���p(�ėp)
			CATS_ACT_PTR cap[PARACGR_CAP_MAX];	///<�ꏏ�ɃX�N���[��������A�N�^�[�ւ̃|�C���^

//			CGR_TRANS_PARAM *ctp;
//			const CGR_TRANS_RECTDATA *ctp_rd_ptr[BUTTON_ANM_NUM];
//			u32 transcgr_id[BUTTON_ANM_NUM];
			const s16 *scrn_offset;
			const REWRITE_SCRN_RECT *scrn_range;
			int tp_ret;
			u8 scrnbuf_no;

			u8 fa_no;						///<�Ώۃt�H���gOBJ�A�N�^�[���[�N�̓Y����
		}paracgr;
	};
}ACI_EFFECT_WORK;

///�J���[�G�t�F�N�gTCB�p�̃��[�N
typedef struct{
	int tp_ret;
	s16 evy;		///<EVY�l(����8�r�b�g����)
	s16 evy_add;	///<EVY�����Z�l(����8�r�b�g����)
	u8 seq;
	u8 pal_pos;	///<�t�F�[�h�Ώۂ̃p���b�g�ԍ�
}ACI_COLOR_EFF_WORK;

///�G�t�F�N�gBG���������p�����[�^
typedef struct{
	const REWRITE_SCRN_RECT *rsr;	///<�X�N���[�����������͈̓f�[�^�ւ̃|�C���^
	u8 rsr_num;						///<rsr�f�[�^��
	s8 add_charname;				///<�L�����N�^�l�[���ɑ������ރI�t�Z�b�g�l
}EFFBG_WRITE_PARAM;

///�t�H���g�A�N�^�[���[�N
typedef struct{
	FONTOAM_OBJ_PTR fontoam;
	CHAR_MANAGER_ALLOCDATA cma;
	u16 font_len;
}FONT_ACTOR;

///�t�H���gOAM�쐬���A�O����BMP�w�肷��ꍇ�Ɏg�p
typedef struct{
	GF_BGL_BMPWIN bmpwin;
	u16 char_len;
	u16 font_len;
}FONT_EX_BMPWIN;

///�`�揈���������ׁ̈A���炩���߃f�[�^���쐬���Ă����ׂ̃��[�N
typedef struct{
	//�t�H���gOAM�Ɋ֘A�t����BMPWIN
	FONT_EX_BMPWIN exbmp_waza[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_explain_u[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_explain_d[WAZA_TEMOTI_MAX];

	FONT_EX_BMPWIN exbmp_judge[JUDGE_MAX];
	
	u8 ap_no[WAZA_TEMOTI_MAX];
	u8 con_type[WAZA_TEMOTI_MAX];
}MEMORY_DECORD_WORK;

///�R���e�X�g���͉�ʐ��䃏�[�N
typedef struct _ACI_PARAM{
	CONTEST_SYSTEM *consys;
	ACTIN_SYSTEM_PARAM *sys;
	ACTIN_GAME_PARAM *a_game;
	void *scene_work;	///<�V�[�����ɈقȂ�K�v�ƂȂ�f�[�^�ނւ̃|�C���^
	TCB_PTR effect_tcb;	///<�G�t�F�N�g����TCB�ւ̃|�C���^
	TCB_PTR color_eff_tcb;	///<�J���[�G�t�F�N�g����TCB�ւ̃|�C���^
	EFFBG_WRITE_PARAM ewp;	///<�G�t�F�N�gBG���������p�����[�^

	//�X�N���[���o�b�t�@
	u16 *scrn_buf[SCRNBUF_MAX];	///<�X�N���[���o�b�t�@
	//�p���b�g�o�b�t�@
	u16 *pal_buf[PALBUF_MAX];				///<�p���b�g�o�b�t�@

	//�t�H���gOAM
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���g�V�X�e���ւ̃|�C���^
	FONT_ACTOR font_actor[FA_NO_MAX];	///<�t�H���g�A�N�^�[���[�N
	
	//�R���e�X�g�^�C�v�A�C�R��
	CATS_ACT_PTR icon_cap[WAZA_TEMOTI_MAX];		///<�R���e�X�g�^�C�v�A�C�R���A�N�^�[�|�C���^
	//�����R���n�[�g
	CATS_ACT_PTR special_heart_cap;			///<�����R���n�[�g�̃A�N�^�[�|�C���^
	//AP�l�E�W�Q�l�n�[�g
	CATS_ACT_PTR app_heart_cap[WAZA_TEMOTI_MAX][APP_HEART_MAX];	///<AP�l�n�[�g�̃A�N�^�[�|�C���^
	
	MEMORY_DECORD_WORK memory_decord;
	void *cgr_arc_data;
	NNSG2dCharacterData *cgr_char_data;
	
	s8 makedata_no;		///<���ݎg�p���Ă���BgMakeData�̔ԍ�
	u8 not_touch_pos;	///<�A���g�p�s�Z�̎莝���ʒu(�s�Z���Ȃ��ꍇ��NOT_TOUCH_WAZA_POS_NULL)
	
	ACI_EFFECT_WORK effect_work;	///<�G�t�F�N�gTCB�p���[�N
	ACI_COLOR_EFF_WORK color_work;	///<�J���[�G�t�F�N�gTCB�p���[�N

	ACI_CURSOR_SAVE cursor_save;	///<�J�[�\���Z�[�u�p���[�N
	CCURSOR_PTR cursor;			///<�J�[�\�����[�N�ւ̃|�C���^
	CURSOR_MOVE cursor_move;	///<�J�[�\���ړ��p���[�N
	u8 decend_key;				///<TRUE:����{�^�����������̂��J�[�\��
}ACI_PARAM;

///BG�쐬�f�[�^�\����
typedef struct{
	u16 cgr_id;			///<�g�pCGR�̃A�[�J�C�uID
	u16 pal_id;			///<�g�p�p���b�g�̃A�[�J�C�uID
	union{
		struct{
			u16 scr0_id;
			u16 scr1_id;
			u16 scr2_id;
			u16 scr3_id;
		};
		u16 scr_id[ACI_BG_NUM];		///<�g�p�X�N���[���̃A�[�J�C�uID
	};
	union{
		struct{
			u16 pri0;		///<BG0�ʂ̃v���C�I���e�B
			u16 pri1;		///<BG1�ʂ̃v���C�I���e�B
			u16 pri2;
			u16 pri3;
		};
		u16 pri[ACI_BG_NUM];		///<BG�̃v���C�I���e�B
	};
	
	//�^�b�`�p�l��
	const RECT_HIT_TBL *tpd;	///<�g�p����^�b�`�p�l���f�[�^�ւ̃|�C���^
	const int *tpd_ret;			///<�^�b�`�p�l���̌���
	const u8 *tpd_pal;			///<�^�b�`���������̃p�l���̃p���b�g�ԍ��f�[�^�ւ̃|�C���^

	//�J�[�\���ړ�
	int (*cursor_move_func)(ACI_PARAM_PTR, int);	///<�L�[���͂��������̃R�[���o�b�N�֐�
	void (*cursor_save_func)(ACI_PARAM_PTR, int);	///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
	
	//�֐��|�C���^
	void (*callback_bg)(ACI_PARAM_PTR, int, int);	///<BGCreate���ɌĂяo���֐�
	int (*callback_tp)(ACI_PARAM_PTR, int, int);	///<�^�b�`�p�l���������ɌĂяo���֐�
}BG_MAKE_DATA;


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void * AINPUT_WorkInit(void);
static void BGCallback_Wall(ACI_PARAM_PTR aci, int select_bg, int force_put);
static void BGCallback_WazaSelect(ACI_PARAM_PTR aci, int select_bg, int force_put);
static void BGCallback_JudgeSelect(ACI_PARAM_PTR aci, int select_bg, int force_put);
static int TPCallback_WazaSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal);
static int TPCallback_JudgeSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal);
static void Sub_SubHeartJudgeDeleteAll(ACI_PARAM_PTR aci);
static void Sub_AppHeartDeleteAll(ACI_PARAM_PTR aci);
static void Sub_SceneOBJDelete(ACI_PARAM_PTR aci);
static void Sub_ConTypeIconCreateAll(ACI_PARAM_PTR aci, u16 wazano[]);
static void Sub_ConTypeIconDeleteAll(ACI_PARAM_PTR aci);
static void Sub_WazaTypeCGRTrans(ACI_PARAM_PTR aci, int waza_type, int waza_pos);
static void Sub_BackScrnOnlyVisible(void);
static void Sub_TouchEndDelete(ACI_PARAM_PTR aci);
static void EffectTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci);
static void EffectTCB_Delete(ACI_PARAM_PTR aci);
static void Effect_ButtonDown(TCB_PTR tcb, void *work);
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work);
static void VWait_CgrTrans(TCB_PTR tcb, void *work);
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work);
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work);
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code);
static void Sub_FontOamCreate(ACI_PARAM_PTR aci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, FONT_EX_BMPWIN *ex_bmpwin);
static void Sub_FontOamDeleteAll(ACI_PARAM_PTR aci);
void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
void AINPUT_FrameExit(GF_BGL_INI *bgl);
void *AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, ACTIN_GAME_PARAM *a_game);
void AINPUT_SystemFree(ACI_PARAM_PTR aci);
void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work);
int AINPUT_TouchCheck(ACI_PARAM_PTR aci);
BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci);
static void MemoryDecordWorkFree(ACI_PARAM_PTR aci);
static void FontExBmpwin_FontSet(ACI_PARAM_PTR aci, const STRBUF *str, FONT_TYPE font_type,
	FONT_EX_BMPWIN *ex_bmp, GF_PRINTCOLOR color);
static void FontLenGet(const STRBUF *str, FONT_TYPE font_type, int *ret_dot_len, 
	int *ret_char_len);
static void ColorEff_PointFade(TCB_PTR tcb, void *work);
static void ColorEffTCB_PointFadeSet(ACI_PARAM_PTR aci, int pal_pos);
static int CursorCheck(ACI_PARAM_PTR aci);
static int CursorMove_WazaSelect(ACI_PARAM_PTR aci, int init_flag);
static void CursorSave_WazaSelect(ACI_PARAM_PTR aci, int index);
static int CursorMove_JudgeSelect(ACI_PARAM_PTR aci, int init_flag);
static void CursorSave_JudgeSelect(ACI_PARAM_PTR aci, int index);
static u32 CursorMove_KeyCheckMove(CURSOR_MOVE *move, int x_menu_num, int y_menu_num, 
	const u8 *move_data);

//==============================================================================
//	�O���f�[�^
//==============================================================================
#include "con_engi_type_ncl_txt.dat"

//==============================================================================
//	�f�[�^
//==============================================================================
///�R���e�X�g���͉�ʗp��BG�t���[���\��
static const GF_BGL_BGCNT_HEADER AciBgCntDat[] = {
	{//GF_BGL_FRAME0_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME1_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME2_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME3_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
};

//============================================================================================
//	�^�b�`�p�l���̈�ݒ�
//============================================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�Z�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL WazaSelectTouchData[] = {
	//UP DOWN LEFT RIGHT
	{1*8, 12*8, 1*8, 0xf*8},		//�Z�P
	{1*8, 12*8, 0x11*8, 0x1f*8},	//�Z�Q
	{13*8, 0x18*8, 1*8, 0xf*8},		//�Z�R
	{13*8, 0x18*8, 0x11*8, 0x1f*8},	//�Z�S
	{ RECT_HIT_END, 0, 0, 0 }
};
///�Z�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int WazaSelectTouchRet[NELEMS(WazaSelectTouchData) - 1] = {
	ACTIN_TP_WAZA_1,			//�Z1
	ACTIN_TP_WAZA_2,			//�Z2
	ACTIN_TP_WAZA_3,			//�Z3
	ACTIN_TP_WAZA_4,			//�Z4
};
///�R�}���h�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 WazaSelectPaletteNo[NELEMS(WazaSelectTouchData) - 1] = {
	WAZATYPE_START_PALPOS + 0,		//�Z1
	WAZATYPE_START_PALPOS + 1,		//�Z2
	WAZATYPE_START_PALPOS + 2,		//�Z3
	WAZATYPE_START_PALPOS + 3,		//�Z4
};

///�J�[�\���ړ��F�Z�I���̐������j���[�̍ő吔
#define CURSOR_WAZA_SELECT_X_MENU_NUM		(2)
///�J�[�\���ړ��F�Z�I���̃��j���[�̊K�w�̐�
#define CURSOR_WAZA_SELECT_Y_MENU_NUM		(2)
///�Z�I���̃^�b�`�p�l��INDEX(WazaSelectTouchRet�̏���)
enum{
	WAZASELE_INDEX_SKILL_1,
	WAZASELE_INDEX_SKILL_2,
	WAZASELE_INDEX_SKILL_3,
	WAZASELE_INDEX_SKILL_4,
};
///�J�[�\���ړ��F�Z�I���̈ړ��͈̓f�[�^
ALIGN4 static const u8 CursorMoveDataWazaSelect[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM] = {
	{WAZASELE_INDEX_SKILL_1, WAZASELE_INDEX_SKILL_2},		//�Z�P�A�Z�Q
	{WAZASELE_INDEX_SKILL_3, WAZASELE_INDEX_SKILL_4},		//�Z�R�A�Z�S
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�R���I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL JudgeSelectTouchData[] = {
	//UP DOWN LEFT RIGHT
	{1*8, 0x10*8, 0*8, 10*8},		//�R���P
	{1*8, 0x10*8, 11*8, 0x15*8},		//�R���Q
	{1*8, 0x10*8, 0x16*8, 255},		//�R���R
	{0x11*8, 0x18*8, 0, 255},			//���ǂ�
	{ RECT_HIT_END, 0, 0, 0 }
};
///�R���I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int JudgeSelectTouchRet[NELEMS(JudgeSelectTouchData) - 1] = {
	ACTIN_TP_JUDGE_1,		//�R���P
	ACTIN_TP_JUDGE_2,		//�R���Q
	ACTIN_TP_JUDGE_3,		//�R���R
	ACTIN_TP_JUDGE_MODORU,	//���ǂ�
};
///�R�}���h�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 JudgeSelectPaletteNo[NELEMS(JudgeSelectTouchData) - 1] = {
	0,		//�R��1
	1,		//�R��2
	2,		//�R��3
	3,		//���ǂ�
};

///�J�[�\���ړ��F�Z�I���̐������j���[�̍ő吔
#define CURSOR_JUDGE_SELECT_X_MENU_NUM		(3)
///�J�[�\���ړ��F�Z�I���̃��j���[�̊K�w�̐�
#define CURSOR_JUDGE_SELECT_Y_MENU_NUM		(2)
///�Z�I���̃^�b�`�p�l��INDEX(JudgeSelectTouchRet�̏���)
enum{
	JUDGESELE_INDEX_1,
	JUDGESELE_INDEX_2,
	JUDGESELE_INDEX_3,
	JUDGESELE_INDEX_CANCEL,
};
///�J�[�\���ړ��F�Z�I���̈ړ��͈̓f�[�^
ALIGN4 static const u8 CursorMoveDataJudgeSelect[CURSOR_JUDGE_SELECT_Y_MENU_NUM][CURSOR_JUDGE_SELECT_X_MENU_NUM] = {
	{JUDGESELE_INDEX_1, JUDGESELE_INDEX_2, JUDGESELE_INDEX_3},		//�R���P�C�Q�C�R
	{JUDGESELE_INDEX_CANCEL, JUDGESELE_INDEX_CANCEL, JUDGESELE_INDEX_CANCEL},		//�L�����Z��
};


//==============================================================================
//	
//==============================================================================
///BG�쐬�f�[�^(�������̕��т�ǉ��A�ύX������AINPUT_TYPE_???�̒�`���ύX���邱�ƁI�I)
static const BG_MAKE_DATA BgMakeData[] = {
	{//WALL
		CON_SUB_NCGR_BIN,
		PALBUF_TITLE,
		{
			SCRNBUF_TITLE,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		NULL,				//�^�b�`�p�l���f�[�^
		NULL,				//�^�b�`�p�l������
		NULL,				//�^�b�`�p���b�g�ԍ�
		NULL,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_Wall,				//BG�쐬���̃R�[���o�b�N�֐�
		NULL,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//HEART_WALL
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			NONE_ID,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_COMMAND_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		NULL,				//�^�b�`�p�l���f�[�^
		NULL,				//�^�b�`�p�l������
		NULL,				//�^�b�`�p���b�g�ԍ�
		NULL,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		NULL,				//BG�쐬���̃R�[���o�b�N�֐�
		NULL,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//WAZA
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			SCRNBUF_COMMAND_WAZA,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_COMMAND_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		WazaSelectTouchData,				//�^�b�`�p�l���f�[�^
		WazaSelectTouchRet,					//�^�b�`�p�l������
		WazaSelectPaletteNo,				//�^�b�`�p���b�g�ԍ�
		CursorMove_WazaSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_WazaSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_WazaSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_WazaSelect,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//JUDGE
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			SCRNBUF_COMMAND_JUDGE,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_COMMAND_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		JudgeSelectTouchData,				//�^�b�`�p�l���f�[�^
		JudgeSelectTouchRet,				//�^�b�`�p�l������
		JudgeSelectPaletteNo,				//�^�b�`�p���b�g�ԍ�
		CursorMove_JudgeSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_JudgeSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_JudgeSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_JudgeSelect,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
};


//==============================================================================
//
//	�A�N�^�[�w�b�_
//
//==============================================================================
///�R���e�X�g�^�C�v�A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S ConTypeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, 100, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_CONTYPE_ICON_1,	//�L����
		PLTTID_OBJ_COMMON_SUB,	//�p���b�g
		CELLID_CONTYPE_ICON,	//�Z��
		CELLANMID_CONTYPE_ICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};


//==============================================================================
//
//	�Z�^�C�v
//
//==============================================================================
///�Z�̋Z�^�C�v�L�����]���ʒu(�L�����N�^�P��)
ALIGN4 static const u16 WazaTypeCgrPos[] = {0+1, 6+1, 12+1, 18+1};

///�R���e�X�g�^�C�v�A�C�R���̍��W
ALIGN4 static const u16 WazaIconPos[][2] = {	//X, Y
	{4*8 + 4 + 3, 6*8},
	{0x14*8 + 4 + 3, 6*8},
	{4*8 + 4 + 3, 0x12*8},
	{0x14*8 + 4 + 3, 0x12*8},
};

//==============================================================================
//
//	
//
//==============================================================================
///�{�^���̉��������̃A�j���p�^�[����
#define BUTTON_ANM_MAX		(3)

//--------------------------------------------------------------
//	�����Ȃ��p�l��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�����Ȃ��p�l���@�A�j��0�A����
#define SCRN_NO_NOT_TOUCH_0		(0x220)

//--------------------------------------------------------------
//	�Z�I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_0_0		(0xc)
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_0_1		(0xcc)
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_0_2		(0x18c)

///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_1_0		(0xf)
///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_1_1		(0xcf)
///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_1_2		(0x18f)

///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_2_0		(0x12)
///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_2_1		(0xd2)
///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_2_2		(0x192)

///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_3_0		(0x15)
///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_3_1		(0xd5)
///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_3_2		(0x195)

///�Z�I���p�l�������������̃{�^���A�j���p�X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 WazaButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//SELECT_SKILL_1
		SCRN_NO_WAZA_SKILL_0_0 - SCRN_NO_WAZA_SKILL_0_0,
		SCRN_NO_WAZA_SKILL_0_1 - SCRN_NO_WAZA_SKILL_0_0,
		SCRN_NO_WAZA_SKILL_0_2 - SCRN_NO_WAZA_SKILL_0_0,
	},
	{//SELECT_SKILL_2
		SCRN_NO_WAZA_SKILL_1_0 - SCRN_NO_WAZA_SKILL_1_0,
		SCRN_NO_WAZA_SKILL_1_1 - SCRN_NO_WAZA_SKILL_1_0,
		SCRN_NO_WAZA_SKILL_1_2 - SCRN_NO_WAZA_SKILL_1_0,
	},
	{//SELECT_SKILL_3
		SCRN_NO_WAZA_SKILL_2_0 - SCRN_NO_WAZA_SKILL_2_0,
		SCRN_NO_WAZA_SKILL_2_1 - SCRN_NO_WAZA_SKILL_2_0,
		SCRN_NO_WAZA_SKILL_2_2 - SCRN_NO_WAZA_SKILL_2_0,
	},
	{//SELECT_SKILL_4
		SCRN_NO_WAZA_SKILL_3_0 - SCRN_NO_WAZA_SKILL_3_0,
		SCRN_NO_WAZA_SKILL_3_1 - SCRN_NO_WAZA_SKILL_3_0,
		SCRN_NO_WAZA_SKILL_3_2 - SCRN_NO_WAZA_SKILL_3_0,
	},
};

///�Z�I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonScrnRect[] = {
	{0, 11, 1, 14},
	{0, 11, 0x11, 0x1e},
	{12, 0x17, 1, 14},
	{12, 0x17, 0x11, 0x1e},
};

///�Z�I���p�l���������Ȃ��{�^���ɂ��鎞�̃X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 WazaButtonNotTouchScrnOffset[] = {
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_0_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_1_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_2_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_3_0,	//SELECT_SKILL_1
};

///�Z�I���p�l���������Ȃ��{�^���ɂ��鎞�̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonNotTouchScrnRect[] = {
	{1, 11, 1, 14},
	{1, 11, 0x11, 0x1e},
	{13, 0x17, 1, 14},
	{13, 0x17, 0x11, 0x1e},
};

//--------------------------------------------------------------
//	�R���I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�R���I���u�R��0�v�A�j��0�A����
#define SCRN_NO_JUDGE_0_0		(0x0)
///�X�N���[���ԍ��F�R���I���u�R��0�v�A�j��1�A����
#define SCRN_NO_JUDGE_0_1		(0xc0)
///�X�N���[���ԍ��F�R���I���u�R��0�v�A�j��2�A����
#define SCRN_NO_JUDGE_0_2		(0x180)

///�X�N���[���ԍ��F�R���I���u�R��1�v�A�j��0�A����
#define SCRN_NO_JUDGE_1_0		(0x3)
///�X�N���[���ԍ��F�R���I���u�R��1�v�A�j��1�A����
#define SCRN_NO_JUDGE_1_1		(0xc3)
///�X�N���[���ԍ��F�R���I���u�R��1�v�A�j��2�A����
#define SCRN_NO_JUDGE_1_2		(0x183)

///�X�N���[���ԍ��F�R���I���u�R��2�v�A�j��0�A����
#define SCRN_NO_JUDGE_2_0		(0x6)
///�X�N���[���ԍ��F�R���I���u�R��2�v�A�j��1�A����
#define SCRN_NO_JUDGE_2_1		(0xc6)
///�X�N���[���ԍ��F�R���I���u�R��2�v�A�j��2�A����
#define SCRN_NO_JUDGE_2_2		(0x186)

///�X�N���[���ԍ��F�R���I���u�L�����Z���v�A�j��0�A����
#define SCRN_NO_JUDGE_CANCEL_0	(0x9)
///�X�N���[���ԍ��F�R���I���u�L�����Z���v�A�j��1�A����
#define SCRN_NO_JUDGE_CANCEL_1	(0xc9)
///�X�N���[���ԍ��F�R���I���u�L�����Z���v�A�j��2�A����
#define SCRN_NO_JUDGE_CANCEL_2	(0x189)

///�R���I���p�l�������������̃{�^���A�j���p�X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 JudgeButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//JUDGE_1
		SCRN_NO_JUDGE_0_0 - SCRN_NO_JUDGE_0_0,
		SCRN_NO_JUDGE_0_1 - SCRN_NO_JUDGE_0_0,
		SCRN_NO_JUDGE_0_2 - SCRN_NO_JUDGE_0_0,
	},
	{//JUDGE_2
		SCRN_NO_JUDGE_1_0 - SCRN_NO_JUDGE_1_0,
		SCRN_NO_JUDGE_1_1 - SCRN_NO_JUDGE_1_0,
		SCRN_NO_JUDGE_1_2 - SCRN_NO_JUDGE_1_0,
	},
	{//JUDGE_3
		SCRN_NO_JUDGE_2_0 - SCRN_NO_JUDGE_2_0,
		SCRN_NO_JUDGE_2_1 - SCRN_NO_JUDGE_2_0,
		SCRN_NO_JUDGE_2_2 - SCRN_NO_JUDGE_2_0,
	},
	{//CANCEL
		SCRN_NO_JUDGE_CANCEL_0 - SCRN_NO_JUDGE_CANCEL_0,
		SCRN_NO_JUDGE_CANCEL_1 - SCRN_NO_JUDGE_CANCEL_0,
		SCRN_NO_JUDGE_CANCEL_2 - SCRN_NO_JUDGE_CANCEL_0,
	},
};

///�R���I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT JudgeButtonScrnRect[] = {
	{0, 0xf, 0, 9},
	{0, 0xf, 11, 0x14},
	{0, 0xf, 0x16, 0x1f},
	{0x10, 0x17, 0, 0x1f},
};



//==============================================================================
//
//	
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   BI�V�X�e�����[�N�̊m�ۂƏ�����
 *
 * @retval  �m�ۂ���BI�V�X�e�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
static void * AINPUT_WorkInit(void)
{
	ACI_PARAM *aci;

	aci = sys_AllocMemory(HEAPID_ACTIN, sizeof(ACI_PARAM));
	MI_CpuClear8(aci, sizeof(ACI_PARAM));
	
	aci->makedata_no = MAKEDATA_NO_INIT;
	
	return aci;
}

//--------------------------------------------------------------
/**
 * @brief   BG�\����W���t���[���\���Őݒ肷��
 * @param   bgl		BGL�f�[�^
 */
//--------------------------------------------------------------
void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(AciBgCntDat); i++){
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S + i, &AciBgCntDat[i], GF_BGL_MODE_TEXT);
		GF_BGL_ScrClearCode(bgl, GF_BGL_FRAME0_S + i, BG_CLEAR_CODE);
		GF_BGL_ScrollSet(bgl, GF_BGL_FRAME0_S + i, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, GF_BGL_FRAME0_S + i, GF_BGL_SCROLL_Y_SET, 0);
	}
}

//--------------------------------------------------------------
/**
 * @brief   BG�t���[���I������
 * @param   bgl		BGL�f�[�^
 */
//--------------------------------------------------------------
void AINPUT_FrameExit(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(AciBgCntDat); i++){
		GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S + i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g���͉�ʂ̃V�X�e����������
 * @param   bgl		BGL�f�[�^
 * @retval  Alloc�����R���e�X�g���͉�ʂ̃V�X�e�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
void * AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, ACTIN_GAME_PARAM *a_game)
{
	ACI_PARAM *aci;
	
	//���[�N�m��
	aci = AINPUT_WorkInit();
	aci->consys = consys;
	aci->sys = sys;
	aci->a_game = a_game;
	
	//�t���[���\���ݒ�	�����ł�邩�͔����H
//	AINPUT_DefaultFrameSet(bgl);

	//�t�H���gOAM�V�X�e���쐬
	aci->fontoam_sys = FONTOAM_SysInit(FA_NO_MAX, HEAPID_ACTIN);

	//�X�N���[���S�ǂݍ���
	{
		NNSG2dScreenData *scrnData;
		void *arc_data;
		int i;
		
		for(i = 0; i < SCRNBUF_MAX; i++){
			//�X�N���[���o�b�t�@�m��
			aci->scrn_buf[i] = sys_AllocMemory(HEAPID_ACTIN, 0x800);

			//�X�N���[���ǂݍ���
			arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, ScrnArcDataNo[i], 1, 
				&scrnData, HEAPID_ACTIN);
			MI_CpuCopy32(scrnData->rawData, aci->scrn_buf[i], 0x800);
			sys_FreeMemoryEz(arc_data);
		}
	}

	//�p���b�g�ǂݍ���
	{
		u16 *def_wk;
		PALETTE_FADE_PTR pfd;
		int i;
		
		pfd = aci->sys->pfd;
		
		for(i = 0; i < PALBUF_MAX; i++){
			aci->pal_buf[i] = sys_AllocMemory(HEAPID_ACTIN, 0x200);
			PaletteWorkSet_Arc(pfd, ARC_CONTEST_BG, PaletteArcDataNo[i], HEAPID_ACTIN, 
				FADE_SUB_BG, 0, 0);
			def_wk = PaletteWorkDefaultWorkGet(pfd, FADE_SUB_BG);
			MI_CpuCopy16(def_wk, aci->pal_buf[i], 0x200);
		}
	}

	return aci;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g���͉�ʂ̃V�X�e�����������
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AINPUT_SystemFree(ACI_PARAM_PTR aci)
{
	int i;
	
	Sub_SceneOBJDelete(aci);
	FONTOAM_SysDelete(aci->fontoam_sys);

	//-- �J�[�\�� --//
	CCURSOR_ResourceFree(aci->sys->crp, CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR,
		CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR);
	CCURSOR_ActorDelete(aci->cursor);

	for(i = 0; i < SCRNBUF_MAX; i++){
		sys_FreeMemoryEz(aci->scrn_buf[i]);
	}
	for(i = 0; i < PALBUF_MAX; i++){
		sys_FreeMemoryEz(aci->pal_buf[i]);
	}
	
	MemoryDecordWorkFree(aci);

	sys_FreeMemoryEz(aci);
}

//--------------------------------------------------------------
/**
 * @brief   �w��^�C�v��BG��ʂ��`������
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(AINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 * @param   work			�V�[�����ɈقȂ�K�v�ȃf�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work)
{
	const BG_MAKE_DATA *bmd, *old_bmd;
	int i;
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	aci->scene_work = scene_work;
	bgl = aci->sys->bgl;
	csp = aci->sys->csp;
	crp = aci->sys->crp;
	
	if(aci->makedata_no == MAKEDATA_NO_INIT){
		force_put = TRUE;
		old_bmd = NULL;
	}
	else{
		old_bmd = &BgMakeData[aci->makedata_no];
	}
	bmd = &BgMakeData[select_bg];

	//�w�i�ȊO�͑S�Ĕ�\��
//	Sub_BackScrnOnlyVisible();
	
	//�eBG�ʂ�BG�v���C�I���e�B�X�V
	{
		for(i = 0; i < ACI_BG_NUM; i++){
			GF_BGL_PrioritySet(GF_BGL_FRAME0_S + i, bmd->pri[i]);
		}
	}
	
	//PALETTE
//	if(bmd->pal_id != NONE_ID && (force_put == TRUE || bmd->pal_id != old_bmd->pal_id)){
	if(1){
		PaletteWorkSet(aci->sys->pfd, aci->pal_buf[bmd->pal_id], FADE_SUB_BG, 0, 0x200);
	}
	//SCREEN
	for(i = 0; i < ACI_BG_NUM; i++){
		if(bmd->scr_id[i] != NONE_ID 
				&& (force_put == TRUE || bmd->scr_id[i] != old_bmd->scr_id[i])){
			GF_BGL_ScreenBufSet(bgl, GF_BGL_FRAME0_S + i, aci->scrn_buf[bmd->scr_id[i]], 0x800);
			GF_BGL_LoadScreenV_Req(bgl, GF_BGL_FRAME0_S + i);
		}
	}
	
	aci->makedata_no = select_bg;

//	G2S_SetBlendAlpha(BLD_PLANE_1, BLD_PLANE_2, BLD_ALPHA_1, BLD_ALPHA_2);

	Sub_SceneOBJDelete(aci);
	//�R�[���o�b�N�֐��Ăяo��
	if(bmd->callback_bg != NULL){
		bmd->callback_bg(aci, select_bg, force_put);
	}

	//CGR	��������Vblank�œ]������܂Ŋm�ۂ����܂܂Ȃ̂ŁA�Ō�ɂ���
//	if(1){	//CGR�]���A�j�����s���Ȃ�L����ID�������ł��K���]�����Ă����Ȃ��ƃA�j�����߂�Ȃ�
	if(bmd->cgr_id != NONE_ID && (force_put == TRUE || bmd->cgr_id != old_bmd->cgr_id)){
//		ArcUtil_BgCharSet(ARC_CONTEST_BG, bmd->cgr_id, bgl, GF_BGL_FRAME0_S, 
//			0, ACI_BG_CGR_SIZE, 1, HEAPID_ACTIN);
		aci->cgr_arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, bmd->cgr_id, 1, 
			&aci->cgr_char_data, HEAPID_ACTIN);
		VWaitTCB_Add(VWait_CgrTrans, aci, VWAIT_TCBPRI_CGRTRANS);
	}

	VWaitTCB_Add(VWait_FrameVisibleUpdate, aci, VWAIT_TCBPRI_FRAMEVISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l����Ԃ𒲂ׂ�
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
int AINPUT_TouchCheck(ACI_PARAM_PTR aci)
{
	int tp_ret, hit, ret, panel_pal;
	const BG_MAKE_DATA *bmd;
	int cursor_check = 0;
	
	GF_ASSERT(aci->makedata_no != MAKEDATA_NO_INIT);
	
	bmd = &BgMakeData[aci->makedata_no];
	if(bmd->tpd == NULL){
		return RECT_HIT_NONE;
	}
	
	GF_ASSERT(bmd->tpd_ret != NULL);
	
	hit = GF_TP_RectHitTrg(bmd->tpd);
	if(hit == RECT_HIT_NONE){
		hit = CursorCheck(aci);
		cursor_check++;
	}
	
	if(hit == RECT_HIT_NONE){
		tp_ret = RECT_HIT_NONE;
		panel_pal = 0xff;
	}
	else{
		tp_ret = bmd->tpd_ret[hit];
		panel_pal = bmd->tpd_pal[hit];
	}
	
	//�R�[���o�b�N�֐��Ăяo��
	if(bmd->callback_tp != NULL){
		tp_ret = bmd->callback_tp(aci, tp_ret, panel_pal);
		if(tp_ret != RECT_HIT_NONE){
			if(bmd->cursor_save_func != NULL){
				bmd->cursor_save_func(aci, hit);
			}
			MI_CpuClear8(&aci->cursor_move, sizeof(CURSOR_MOVE));
			CCURSOR_OFF(aci->cursor);
			if(cursor_check > 0){
				aci->decend_key = TRUE;
			}
			else{
				aci->decend_key = FALSE;
			}
		}
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���I�����Ă��邩�`�F�b�N
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I�����Ă���B�@FALSE:�I�����Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci)
{
	if(aci->effect_tcb == NULL && aci->color_eff_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}



//==============================================================================
//
//	BG�쐬���ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_WALL��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(AINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_Wall(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	STRBUF *rank_src, *type_src;
	u32 rank_id, type_id;
	
	rank_id = ConTool_GetRankMsgID(aci->sys->c_game->rank, aci->sys->c_game->mode, 
		aci->consys->sio_flag);
	type_id = ConTool_GetTypeMsgID(aci->sys->c_game->type, aci->sys->c_game->mode);
	
	rank_src = MSGMAN_AllocString(aci->sys->actin_msg, rank_id);
	type_src = MSGMAN_AllocString(aci->sys->actin_msg, type_id);
	
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_CONRANK], 
		rank_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		PLTTID_SUB_FONTACT, FONT_CONRANK_POS_X, FONT_CONRANK_POS_Y, FONTOAM_CENTER, NULL);
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_CONTYPE], 
		type_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		PLTTID_SUB_FONTACT, FONT_CONTYPE_POS_X, FONT_CONTYPE_POS_Y, FONTOAM_CENTER, NULL);
	
	STRBUF_Delete(rank_src);
	STRBUF_Delete(type_src);
	
	PaletteWorkSetEx_Arc(aci->sys->pfd, ARC_CONTEST_BG, CONTEST_SUBTIT_NCLR, HEAPID_ACTIN, 
		FADE_SUB_BG, 0x20, PLATE_PALNO * 16, 16 * aci->sys->c_game->type);
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_A��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(AINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_WazaSelect(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	u16 wazano[WAZA_TEMOTI_MAX], appeal_no[WAZA_TEMOTI_MAX];
	int i;
	STRBUF *waza_src;
	STRBUF *setumei_u_src, *setumei_d_src;
	u32 u_id, d_id;
	MEMORY_DECORD_WORK *mdw;

	mdw = &aci->memory_decord;
	aci->not_touch_pos = NOT_TOUCH_WAZA_POS_NULL;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		wazano[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
		if(wazano[i] != 0){
			appeal_no[i] = mdw->ap_no[i];
		}
		else{
			appeal_no[i] = 0;
		}
		
		//�Z��
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_WAZA_1 + i], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_SUB_FONTACT, FontWazaPos[i][0], FontWazaPos[i][1], FONTOAM_LEFT, 
			&mdw->exbmp_waza[i]);
		
		//�Z�����F��i
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_SETUMEI_1_U + i], 
			NULL, FONT_SYSTEM, MSGCOLOR_SETUMEI, PALOFS_SETUMEI,
			PLTTID_SUB_FONTACT, FontSetumeiPos[i][0][0], FontSetumeiPos[i][0][1], FONTOAM_LEFT,
			&mdw->exbmp_explain_u[i]);
		
		//�Z�����F���i
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_SETUMEI_1_D + i], 
			NULL, FONT_SYSTEM, MSGCOLOR_SETUMEI, PALOFS_SETUMEI,
			PLTTID_SUB_FONTACT, FontSetumeiPos[i][1][0], FontSetumeiPos[i][1][1], FONTOAM_LEFT,
			&mdw->exbmp_explain_d[i]);
		
		//�莝���Z���Ȃ��Ȃ�A�t�H���gOBJ�o�j�b�V�������g����
		if(wazano[i] == 0){
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_WAZA_1 + i].fontoam, FALSE);
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_SETUMEI_1_U + i].fontoam, FALSE);
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_SETUMEI_1_D + i].fontoam, FALSE);
		}
	}

	//-- �Z�^�C�v����CGR��]�� --//
	{
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			if(wazano[i] != 0){
				int con_type;
				con_type = mdw->con_type[i];
				Sub_WazaTypeCGRTrans(aci, con_type, i);
			}
			else{
				Sub_WazaTypeCGRTrans(aci, -1, i);
			}
		}
	}

	//-- 2�x�A���g�p�Z�`�F�b�N --//
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] != 0 
				&& AT_WazaConsecutiveCheck(aci->a_game, aci->sys->c_game->my_breeder_no, 
				wazano[i]) == FALSE){
			//2�x�A���g�p�ŘA�����Z�ł��Ȃ��̂Ȃ�A�Â����ă^�b�`�o���Ȃ��悤�ɂ���
		//	SoftFadePfd(aci->sys->pfd, FADE_SUB_BG, (WAZATYPE_START_PALPOS + i) * 16, 16, 
		//		NOT_TOUCH_WAZA_EVY, NOT_TOUCH_WAZA_COLOR);
			PaletteWorkSet(aci->sys->pfd, 
				&aci->pal_buf[PALBUF_COMMAND][ACI_NOT_SELECT_PANEL_PALNO * 16], 
				FADE_SUB_BG, (WAZATYPE_START_PALPOS + i) * 16, 0x20);
			
			GF_ASSERT(aci->not_touch_pos == NOT_TOUCH_WAZA_POS_NULL && "2�ȏ�̋Z���A���g�p�s��ԂɂȂ��Ă��܂�");
			aci->not_touch_pos = i;
		}
	}

	//�R���e�X�g�^�C�v�A�C�R��
	Sub_ConTypeIconCreateAll(aci, wazano);
	
	//AP�l�E�W�Q�l
	{
		int ap_point;
		int heart_num, loop;
		
		//�A�N�^�[�Z�b�g
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			if(wazano[i] == 0){
				continue;
			}
			ap_point = ConTool_GetAPWaza_App(appeal_no[i]);
			heart_num = MATH_IAbs(ap_point) / APP_APPEAL_ICON_ONE_POINT;
			GF_ASSERT(heart_num <= APP_HEART_MAX);
			for(loop = 0; loop < heart_num; loop++){
				GF_ASSERT(aci->app_heart_cap[i][loop] == NULL);
				aci->app_heart_cap[i][loop] = ACIT_AppHeartActorSet(
					aci->sys->csp, aci->sys->crp, 
					AppHeartPos[i][0] + APP_HEART_SPACE_X * loop, 
					AppHeartPos[i][1], ap_point);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_B��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(AINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_JudgeSelect(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	int i;
	GF_BGL_INI *bgl;
	STRBUF *modoru_src;
	MEMORY_DECORD_WORK *mdw;

	mdw = &aci->memory_decord;
	bgl = aci->sys->bgl;

	for(i = 0; i < JUDGE_MAX; i++){
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_JUDGE_1 + i], 
			NULL, FONT_BUTTON, MSGCOLOR_JUDGE, PALOFS_JUDGE,
			PLTTID_SUB_FONTACT, FontJudgePos[i][0], FontJudgePos[i][1], FONTOAM_CENTER, 
			&mdw->exbmp_judge[i]);
	}
	
	modoru_src = MSGMAN_AllocString(aci->sys->actin_msg, CAMSG_MODORU);
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_JUDGE_1 + i], 
			modoru_src, FONT_BUTTON, 
			MSGCOLOR_JUDGE, PALOFS_JUDGE,
			PLTTID_SUB_FONTACT, FONT_JUDGE_MODORU_X, FONT_JUDGE_MODORU_Y, FONTOAM_CENTER, NULL);
	STRBUF_Delete(modoru_src);
	
	//�����R���̈�̃n�[�g�A�C�R��
	aci->special_heart_cap = ACIT_SubHeartJudgeActorAdd(aci->sys->csp, 
		aci->sys->crp, aci->sys->c_game->special_judge_no);
}



//==============================================================================
//
//	�^�b�`�p�l���������ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_A�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_WazaSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal)
{
	u32 rd_no;
	int wazano;
	const s16 *scrn_offset;
	const REWRITE_SCRN_RECT *scrn_range;
	
	rd_no = tp_ret;
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return RECT_HIT_NONE;
	case ACTIN_TP_WAZA_1:
	case ACTIN_TP_WAZA_2:
	case ACTIN_TP_WAZA_3:
	case ACTIN_TP_WAZA_4:
		wazano = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + tp_ret, NULL);
		if(wazano == 0 || aci->not_touch_pos == (tp_ret - ACTIN_TP_WAZA_1)){
			return RECT_HIT_NONE;	//�����ꂽ�ꏊ�̎莝���Z���Ȃ�
		}
		scrn_offset = WazaButtonScrnOffset[rd_no];
		scrn_range = &WazaButtonScrnRect[rd_no];
		break;
	}
	
	ColorEffTCB_PointFadeSet(aci, panel_pal);
	
	EffectTCB_Add(Effect_WazaButtonDown, aci);
	aci->effect_work.paracgr.scrn_offset = scrn_offset;
	aci->effect_work.paracgr.scrn_range = scrn_range;
	aci->effect_work.paracgr.scrnbuf_no = SCRNBUF_COMMAND_WAZA;
	aci->effect_work.paracgr.tp_ret = tp_ret;
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_B�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_JudgeSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal)
{
	int fa_no;
	int special;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case ACTIN_TP_JUDGE_1:
		fa_no = FA_NO_JUDGE_1;
		break;
	case ACTIN_TP_JUDGE_2:
		fa_no = FA_NO_JUDGE_2;
		break;
	case ACTIN_TP_JUDGE_3:
		fa_no = FA_NO_JUDGE_3;
		break;
	case ACTIN_TP_JUDGE_MODORU:
		fa_no = FA_NO_JUDGE_MODORU;
		break;
	}
	
	//�����R����I���������`�F�b�N
	special = (tp_ret == aci->sys->c_game->special_judge_no) ? TRUE:FALSE;

	ColorEffTCB_PointFadeSet(aci, panel_pal);
	
	EffectTCB_Add(Effect_ButtonDown, aci);
	aci->effect_work.paracgr.scrn_offset = JudgeButtonScrnOffset[tp_ret];
	aci->effect_work.paracgr.scrn_range = &JudgeButtonScrnRect[tp_ret];
	aci->effect_work.paracgr.scrnbuf_no = SCRNBUF_COMMAND_JUDGE;
	aci->effect_work.paracgr.tp_ret = tp_ret;
	aci->effect_work.paracgr.fa_no = fa_no;
	if(special == TRUE){
		aci->effect_work.paracgr.cap[0] = aci->special_heart_cap;
	}

	return tp_ret;
}




//==============================================================================
//
//	�T�u�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �w��͈͂̃X�N���[���o�b�t�@���w��R�[�h�ŃN���A����
 *
 * @param   rsr[]			�N���A�͈�
 * @param   rsr_num			rsr�f�[�^��
 * @param   bgl				BGL�f�[�^
 * @param   frame_no		�t���[���ԍ�
 * @param   clear_code		�N���A�[�R�[�h
 */
//--------------------------------------------------------------
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code)
{
	u16 *buf;
	int i, y;
	
	buf = GF_BGL_ScreenAdrsGet(bgl, frame_no);
	GF_ASSERT(buf != NULL);

	for(i = 0; i < rsr_num; i++){
		for(y = rsr[i].top; y <= rsr[i].bottom; y++){
			MI_CpuFill16(&buf[0x20*y + rsr[i].left], clear_code, 
				(rsr[i].right - rsr[i].left + 1) * 2);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOAM���쐬����
 *
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   font_actor	���������t�H���gOAM�֘A�̃��[�N�����
 * @param   str			������
 * @param   font_type	�t�H���g�^�C�v(FONT_SYSTEM��)
 * @param   color		�t�H���g�J���[�\��
 * @param   pal_offset	�p���b�g�ԍ��I�t�Z�b�g
 * @param   pal_id		�o�^�J�n�p���b�gID
 * @param   x			���WX
 * @param   y			���WY
 * @param   pos_center  FONTOAM_LEFT(X���[���W) or FONTOAM_CENTER(X���S���W)
 * @param   ex_bmpwin	�Ăяo�����Ńt�H���gOAM�Ɋ֘A�t����BMPWIN�������Ă���ꍇ�͂����œn���B
 *          			NULL�̏ꍇ�͒��ō쐬����܂��B(ex_bmpwin���g�p����ꍇ��str��NULL��OK)
 */
//--------------------------------------------------------------
static void Sub_FontOamCreate(ACI_PARAM_PTR aci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, FONT_EX_BMPWIN *ex_bmpwin)
{
	FONTOAM_INIT finit;
	GF_BGL_BMPWIN bmpwin;
	CHAR_MANAGER_ALLOCDATA cma;
	int vram_size;
	FONTOAM_OBJ_PTR fontoam;
	GF_BGL_INI *bgl;
	CATS_RES_PTR crp;
	int font_len, char_len;
	
	GF_ASSERT(font_actor->fontoam == NULL);
	
	bgl = aci->sys->bgl;
	crp = aci->sys->crp;
	
	//������̃h�b�g������A�g�p����L���������Z�o����
	if(ex_bmpwin == NULL){
		FontLenGet(str, font_type, &font_len, &char_len);
	}
	else{
		font_len = ex_bmpwin->font_len;
		char_len = ex_bmpwin->char_len;
	}

	//BMP�쐬
	if(ex_bmpwin == NULL){
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, char_len, 16 / 8, 0, 0);
		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
			PANEL_MSG_MARGIN, 0, NULL);
//		GF_STR_PrintColor(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, NULL );
	}
	else{
		bmpwin = ex_bmpwin->bmpwin;
	}

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB,  HEAPID_ACTIN);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
	
	//���W�ʒu�C��
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
//	y += SUB_SURFACE_Y_INTEGER - 8;
	y += ACTIN_SUB_ACTOR_DISTANCE_INTEGER - 8;
	
	finit.fontoam_sys = aci->fontoam_sys;
	finit.bmp = &bmpwin;
	finit.clact_set = CATS_GetClactSetPtr(crp);
	finit.pltt = CATS_PlttProxy(crp, pal_id);
	finit.parent = NULL;
	finit.char_ofs = cma.alloc_ofs;
	finit.x = x;
	finit.y = y;
	finit.bg_pri = PANEL_MSG_BGPRI;
	finit.soft_pri = PANEL_MSG_SOFTPRI;
	finit.draw_area = NNS_G2D_VRAM_TYPE_2DSUB;
	finit.heap = HEAPID_ACTIN;
	
	fontoam = FONTOAM_Init(&finit);
//	FONTOAM_SetPaletteOffset(fontoam, pal_offset);
	FONTOAM_SetPaletteOffsetAddTransPlttNo(fontoam, pal_offset);
	FONTOAM_SetMat(fontoam, x, y);
	
	//�������
	if(ex_bmpwin == NULL){
		GF_BGL_BmpWinDel(&bmpwin);
	}
	
	font_actor->fontoam = fontoam;
	font_actor->cma = cma;
	font_actor->font_len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���t�H���gOAM��S�č폜������
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_FontOamDeleteAll(ACI_PARAM_PTR aci)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(aci->font_actor[i].fontoam != NULL){
			FONTOAM_Delete(aci->font_actor[i].fontoam);
			CharVramAreaFree(&aci->font_actor[i].cma);
			aci->font_actor[i].fontoam = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �����R���n�[�g��S�č폜����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_SubHeartJudgeDeleteAll(ACI_PARAM_PTR aci)
{
	if(aci->special_heart_cap != NULL){
		ACIT_SubHeartJudgeActorDel(aci->special_heart_cap);
		aci->special_heart_cap = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   AP�l�n�[�g��S�č폜����
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_AppHeartDeleteAll(ACI_PARAM_PTR aci)
{
	int i, k;
	
	for(k = 0; k < WAZA_TEMOTI_MAX; k++){
		for(i = 0; i < APP_HEART_MAX; i++){
			if(aci->app_heart_cap[k][i] != NULL){
				ACIT_AppHeartActorDel(aci->app_heart_cap[k][i]);
				aci->app_heart_cap[k][i] = NULL;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R����S�Đ�������
 *
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   wazano[]	�莝���̋Z�ԍ����������z��ւ̃|�C���^(WAZA_TEMOTI_MAX�����鎖!)
 */
//--------------------------------------------------------------
static void Sub_ConTypeIconCreateAll(ACI_PARAM_PTR aci, u16 wazano[])
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	int con_type;

	csp = aci->sys->csp;
	crp = aci->sys->crp;

	obj_param = ConTypeIconObjParam;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		GF_ASSERT(aci->icon_cap[i] == NULL);
		if(wazano[i] != 0){
			con_type = aci->memory_decord.con_type[i];
			
			obj_param.id[CLACT_U_CHAR_RES] = CHARID_CONTYPE_ICON_1 + i;
			obj_param.x = WazaIconPos[i][0];
			obj_param.y = WazaIconPos[i][1];
			aci->icon_cap[i] = ConTypeIcon_ActorCreate(csp, crp, 
				con_type, &obj_param);
			CATS_ObjectPosSetCap_SubSurface(aci->icon_cap[i], obj_param.x, obj_param.y, 
				ACTIN_SUB_ACTOR_DISTANCE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v�A�C�R����S�č폜����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_ConTypeIconDeleteAll(ACI_PARAM_PTR aci)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	csp = aci->sys->csp;
	crp = aci->sys->crp;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aci->icon_cap[i] != NULL){
			ConTypeIcon_ActorDelete(aci->icon_cap[i]);
			aci->icon_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���[����������
 *
 * @param   aci				ACI�V�X�e�����[�N�ւ̃|�C���^
 * @param   scrn_offset		���Z����X�N���[���l
 * @param   range			�X�N���[�����������͈�
 * @param   scrnbuf_no		���f�[�^�ƂȂ�X�N���[���o�b�t�@�̔ԍ�
 * @param   anm_no			�A�j���ԍ�
 */
//--------------------------------------------------------------
static void Sub_ScrnOffsetRewrite(ACI_PARAM_PTR aci, const s16 *scrn_offset, 
	const REWRITE_SCRN_RECT *range, int scrnbuf_no, int anm_no)
{
	int x, y;
	GF_BGL_INI *bgl;
	u16 *scrn, *write_scrn;
	u16 *src_scrn, *read_scrn;
	int add_scrn;
	
	bgl = aci->sys->bgl;
	scrn = GF_BGL_ScreenAdrsGet(bgl, ACTINSUB_FRAME_PANEL);
	src_scrn = aci->scrn_buf[scrnbuf_no];
	add_scrn = scrn_offset[anm_no];
	
	for(y = range->top; y <= range->bottom; y++){
		write_scrn = &scrn[y * 32];
		read_scrn = &src_scrn[y * 32];
		for(x = range->left; x <= range->right; x++){
			write_scrn[x] = read_scrn[x] + add_scrn;
		}
	}
	
	GF_BGL_LoadScreenV_Req(bgl, ACTINSUB_FRAME_PANEL);
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v����CGR�f�[�^������������
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @param   waza_pos		�莝���̋Z�̈ʒu(0�`3)
 */
//--------------------------------------------------------------
static void Sub_WazaTypeCGRTrans(ACI_PARAM_PTR aci, int con_type, int waza_pos)
{
#if 0
	GF_BGL_INI *bgl;
	u32 screen_type;
	
	bgl = aci->sys->bgl;
	screen_type = GF_BGL_ScreenTypeGet(bgl, ACTINSUB_FRAME_PANEL);
	
	WazaPanel_EasyCharLoad(bgl, waza_type, HEAPID_ACTIN, ACTINSUB_FRAME_PANEL, 
		WazaTypeCgrPos[waza_pos], screen_type);
	WazaPanel_EasyPalLoad(aci->sys->pfd, waza_type, HEAPID_ACTIN, FADE_SUB_BG, 
		WAZATYPE_START_PALPOS + waza_pos);
#endif
	const u16 * const type_pal_tbl[] = {
		&con_engi_type_ncl[16 * 3],		//CONTYPE_STYLE
		&con_engi_type_ncl[16 * 4],		//CONTYPE_BEAUTIFUL
		&con_engi_type_ncl[16 * 1],		//CONTYPE_CUTE
		&con_engi_type_ncl[16 * 2],		//CONTYPE_CLEVER
		&con_engi_type_ncl[16 * 0],		//CONTYPE_STRONG
	};
	
	if(con_type != -1){
		PaletteWorkSet(aci->sys->pfd, type_pal_tbl[con_type], FADE_SUB_BG, 
			(WAZATYPE_START_PALPOS + waza_pos) * 16, 0x20);
	}
	else{
		Sub_ScrnOffsetRewrite(aci, &WazaButtonNotTouchScrnOffset[waza_pos], 
			&WazaButtonNotTouchScrnRect[waza_pos], SCRNBUF_COMMAND_WAZA, 0);
		PaletteWorkSet(aci->sys->pfd, 
			&aci->pal_buf[PALBUF_COMMAND][ACI_NOT_SELECT_PANEL_PALNO * 16], 
			FADE_SUB_BG, (WAZATYPE_START_PALPOS + waza_pos) * 16, 0x20);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�ȊO�̃t���[����S�Ĕ�\���ɂ���
 */
//--------------------------------------------------------------
static void Sub_BackScrnOnlyVisible(void)
{
	int i;
	
	for(i = 0; i < ACI_BG_NUM; i++){
		if(GF_BGL_FRAME0_S + i != ACTINSUB_FRAME_BACK){
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		}
		else{
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_ON);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�l���^�b�`�G�t�F�N�g�I����A�w�i�݂̂ɂ��邽�߂̏�����F�X����(�t�H���gOBJ�̍폜�Ƃ�)
 * @param   none		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_TouchEndDelete(ACI_PARAM_PTR aci)
{
	Sub_SceneOBJDelete(aci);
//	VWaitTCB_Add(VWait_BackScrnOnlyVisible, aci, VWAIT_TCBPRI_BACKSCRN_VISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   BG�^�C�v���؂�ւ�閈�ɍ폜����K�v�̂���OBJ��Delete����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_SceneOBJDelete(ACI_PARAM_PTR aci)
{
	Sub_SubHeartJudgeDeleteAll(aci);
	Sub_AppHeartDeleteAll(aci);
	Sub_ConTypeIconDeleteAll(aci);
	Sub_FontOamDeleteAll(aci);
}



//==============================================================================
//
//	�G�t�F�N�gTCB
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB�𐶐�����
 *
 * @param   func		TCB�ɃZ�b�g����֐��|�C���^
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci)
{
	GF_ASSERT(aci->effect_tcb == NULL);
	
	MI_CpuClear8(&aci->effect_work, sizeof(ACI_EFFECT_WORK));
	aci->effect_tcb = TCB_Add(func, aci, TCBPRI_AINPUT_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���폜����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Delete(ACI_PARAM_PTR aci)
{
	if(aci->effect_tcb != NULL){
		TCB_Delete(aci->effect_tcb);
		aci->effect_tcb = NULL;
		MI_CpuClear8(&aci->effect_work, sizeof(ACI_EFFECT_WORK));
	}
}


//--------------------------------------------------------------
/**
 * @brief   �p�l���������L�����]���A�j�������s���ď��������܂��B
 *          1�̃p�l���ɑ΂���1�̃t�H���gOBJ���Z�b�g�ɂȂ��Ă�����̗p�̔ėp�^�X�N�ł�
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_ButtonDown(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int i;
	
	bgl = aci->sys->bgl;
	
	switch(aci->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 2);
		
		FONTOAM_GetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(aci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(aci->effect_work.paracgr.cap[i]->act, 0, SCRN_SCROLL_A_EFF_Y);
			}
		}
		
		aci->effect_work.seq++;
		break;
	case 1:
		aci->effect_work.wait++;
		if(aci->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		aci->effect_work.wait = 0;
		aci->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 1);
		
		FONTOAM_GetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(aci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(aci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_BACK_A_EFF_Y);
			}
		}
		
		aci->effect_work.seq++;
		break;
	default:
		aci->effect_work.wait++;
		if(aci->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(aci);
			EffectTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�l���������L�����]���A�j�������s���ď��������܂��B
 *          �Z�I������p�ł��B
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	ACI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int fa_waza, fa_up, fa_down;
	int cap_icon, wazano;
	u16 wazano_array[WAZA_TEMOTI_MAX];
	int i, wazapos;
	
	bgl = aci->sys->bgl;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		wazano_array[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
	}

	switch(aci->effect_work.paracgr.tp_ret){
	case ACTIN_TP_WAZA_1:
		fa_waza = FA_NO_WAZA_1;
		fa_up = FA_NO_SETUMEI_1_U;
		fa_down = FA_NO_SETUMEI_1_D;
		cap_icon = 0;
		wazano = wazano_array[0];
		wazapos = 0;
		break;
	case ACTIN_TP_WAZA_2:
		fa_waza = FA_NO_WAZA_2;
		fa_up = FA_NO_SETUMEI_2_U;
		fa_down = FA_NO_SETUMEI_2_D;
		cap_icon = 1;
		wazano = wazano_array[1];
		wazapos = 1;
		break;
	case ACTIN_TP_WAZA_3:
		fa_waza = FA_NO_WAZA_3;
		fa_up = FA_NO_SETUMEI_3_U;
		fa_down = FA_NO_SETUMEI_3_D;
		cap_icon = 2;
		wazano = wazano_array[2];
		wazapos = 2;
		break;
	case ACTIN_TP_WAZA_4:
		fa_waza = FA_NO_WAZA_4;
		fa_up = FA_NO_SETUMEI_4_U;
		fa_down = FA_NO_SETUMEI_4_D;
		cap_icon = 3;
		wazano = wazano_array[3];
		wazapos = 3;
		break;
//	case SELECT_CANCEL:		���̏��L�����Z���͂Ȃ��@2005.12.03(�y)
	default:
		fa_waza = 0;
		fa_up = 0;
		fa_down = 0;
		cap_icon = 0;
		wazano = 0;
		break;
	}
	
	switch(aci->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 2);
		
		if(1){	//aci->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(aci->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_up].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_up].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_down].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_down].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(aci->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				for(i = 0; i < APP_HEART_MAX; i++){
					if(aci->app_heart_cap[wazapos][i] != NULL){
						CATS_ObjectPosMove(aci->app_heart_cap[wazapos][i]->act, 0, 
							SCRN_SCROLL_A_EFF_Y);
					}
				}
			}
		}
		else{
		#if 0	//���̂Ƃ���L�����Z���Ȃ� 2005.12.02(��)
			FontOBJ_PosGet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, &x, &y);
			FontOBJ_PosSet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, 
				x, y + SCRN_SCROLL_A_EFF_Y);
		#endif
		}
		
		aci->effect_work.seq++;
		break;
	case 1:
		aci->effect_work.wait++;
		if(aci->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		aci->effect_work.wait = 0;
		aci->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 1);
		
		if(1){	//aci->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(aci->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_up].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_up].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_down].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_down].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(aci->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_BACK_A_EFF_Y);
				for(i = 0; i < APP_HEART_MAX; i++){
					if(aci->app_heart_cap[wazapos][i] != NULL){
						CATS_ObjectPosMove(aci->app_heart_cap[wazapos][i]->act, 0, 
							SCRN_SCROLL_BACK_A_EFF_Y);
					}
				}
			}
		}
		else{
		#if 0	//���̂Ƃ���L�����Z���Ȃ� 2005.12.02(��)
			FontOBJ_PosGet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, &x, &y);
			FontOBJ_PosSet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, 
				x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		#endif
		}
		
		aci->effect_work.seq++;
		break;
	default:
		aci->effect_work.wait++;
		if(aci->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(aci);
			EffectTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �J���[�G�t�F�N�gTCB�𐶐�����
 *
 * @param   func		TCB�ɃZ�b�g����֐��|�C���^
 * @param   aci			BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEffTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci)
{
	GF_ASSERT(aci->color_eff_tcb == NULL);
	
	MI_CpuClear8(&aci->color_work, sizeof(ACI_COLOR_EFF_WORK));
	aci->color_eff_tcb = TCB_Add(func, aci, TCBPRI_AINPUT_COLOR_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �J���[�G�t�F�N�gTCB���폜����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEffTCB_Delete(ACI_PARAM_PTR aci)
{
	if(aci->color_eff_tcb != NULL){
		TCB_Delete(aci->color_eff_tcb);
		aci->color_eff_tcb = NULL;
		MI_CpuClear8(&aci->color_work, sizeof(ACI_COLOR_EFF_WORK));
	}
}

//--------------------------------------------------------------
/**
 * @brief   ����̈ʒu�̃J���[�������t�F�[�h������^�X�N�𐶐�����
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   pal_pos	�t�F�[�h������p���b�g�ԍ�
 */
//--------------------------------------------------------------
static void ColorEffTCB_PointFadeSet(ACI_PARAM_PTR aci, int pal_pos)
{
	if(pal_pos == 0xff){
		return;
	}
	
	ColorEffTCB_Add(ColorEff_PointFade, aci);
	aci->color_work.pal_pos = pal_pos;
}

//--------------------------------------------------------------
/**
 * @brief   ����̈ʒu�̃J���[�������t�F�[�h������
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEff_PointFade(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	ACI_COLOR_EFF_WORK *cw;
	PALETTE_FADE_PTR pfd;
	int i, end;
	
	cw = &aci->color_work;
	pfd = aci->sys->pfd;
	end = FALSE;
	
	switch(cw->seq){
	case 0:
		cw->evy = TOUCH_FADE_EVY;
		cw->evy_add = -TOUCH_FADE_ADD_EVY;
		//�ŏ��̌v�Z���𑫂�����ł���
		cw->evy -= cw->evy_add;
		
		cw->seq++;
		//break;
	case 1:
		cw->evy += cw->evy_add;
		if(cw->evy_add >= 0 && cw->evy >= (16<<8)){
			cw->evy = 16<<8;
			end = TRUE;
		}
		else if(cw->evy_add < 0 && cw->evy <= 0){
			cw->evy = 0;
			end = TRUE;
		}
		
	#if 1
		//�S�̂𔒂�
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, cw->evy >> 8, 0x7fff);
	#elif 0
		//�S�̂��Â�
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, cw->evy >> 8, 0x0000);
		//�g��������
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 3, 1, cw->evy >> 8, 0x7fff);
	#else
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, (cw->evy >> 8) / 2, 0x7fff);
		//�S�̂��Â�
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 1, 1, cw->evy >> 8, 0x7b1a);
		//�g��������
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 0xa, 1, cw->evy >> 8, 0x4634);
	#endif
		if(end == TRUE){
			ColorEffTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   MEMORY_DECORD_WORK���������
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void MemoryDecordWorkFree(ACI_PARAM_PTR aci)
{
	int i, client;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aci->memory_decord.exbmp_waza[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_waza[i].bmpwin);
		}
		if(aci->memory_decord.exbmp_explain_u[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_explain_u[i].bmpwin);
		}
		if(aci->memory_decord.exbmp_explain_d[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_explain_d[i].bmpwin);
		}
	}

	for(i = 0; i < JUDGE_MAX; i++){
		if(aci->memory_decord.exbmp_judge[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_judge[i].bmpwin);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�p�����[�^�̃f�[�^���������ɓW�J����
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   wazano			�Z�ԍ��̓������z��ւ̃|�C���^(WAZA_TEMOTI_MAX��)
 */
//--------------------------------------------------------------
void AINPUT_WazaParaMemoryDecord(ACI_PARAM_PTR aci, u16 wazano[])
{
	MEMORY_DECORD_WORK *mdw;
	int i;
	STRBUF *wazaname_p;
	STRBUF *setumei_u_src, *setumei_d_src, *judge_src;
	u32 u_id, d_id;
	
	mdw = &aci->memory_decord;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] != 0){
			mdw->ap_no[i] = WT_WazaDataParaGet(wazano[i], ID_WTD_ap_no);
			mdw->con_type[i] = WT_WazaDataParaGet(wazano[i], ID_WTD_contype);
		}
		else{
			mdw->ap_no[i] = 0;
			mdw->con_type[i] = 0;
		}
		
		//BMPWIN�F�Z��
		wazaname_p = MSGDAT_UTIL_GetWazaName(wazano[i], HEAPID_ACTIN);
		FontExBmpwin_FontSet(aci, wazaname_p, FONT_BUTTON, &mdw->exbmp_waza[i], MSGCOLOR_WAZA);
		STRBUF_Delete(wazaname_p);
		
		//BMPWIN:�Z����
		ConTool_GetAPSetumeiMsgID(mdw->ap_no[i], &u_id, &d_id);
		setumei_u_src = MSGMAN_AllocString(aci->sys->explain_msg, u_id);
		setumei_d_src = MSGMAN_AllocString(aci->sys->explain_msg, d_id);
		FontExBmpwin_FontSet(aci, setumei_u_src, FONT_SYSTEM, &mdw->exbmp_explain_u[i], 
			MSGCOLOR_SETUMEI);
		FontExBmpwin_FontSet(aci, setumei_d_src, FONT_SYSTEM, &mdw->exbmp_explain_d[i], 
			MSGCOLOR_SETUMEI);
		STRBUF_Delete(setumei_u_src);
		STRBUF_Delete(setumei_d_src);
	}
	
	//�R����
	for(i = 0; i < JUDGE_MAX; i++){
		judge_src = ADV_MSGDAT_GetJudgeName(aci->sys->c_game->jd[i].name_id, HEAPID_ACTIN);
		FontExBmpwin_FontSet(aci, judge_src, FONT_BUTTON, &mdw->exbmp_judge[i], 
			MSGCOLOR_JUDGE);
		STRBUF_Delete(judge_src);
	}

	//-- ���łɂ����ŃJ�[�\�������� --//
	{
		CCURSOR_ResourceLoad(aci->sys->csp, aci->sys->crp, aci->sys->pfd, 
			CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR,
			CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR);
		aci->cursor = CCURSOR_ActorCreate(aci->sys->csp, aci->sys->crp, HEAPID_ACTIN, 
			CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR, CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR, 
			SOFTPRI_CURSOR, BGPRI_CURSOR);
	}
}

//--------------------------------------------------------------
/**
 * @brief   FONT_EX_BMPWIN�ɑ΂��ăt�H���g�f�[�^���쐬���A�Z�b�g����
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   str				������ւ̃|�C���^
 * @param   font_type		�t�H���g�^�C�v
 * @param   ex_bmpwin		�f�[�^�����
 * @param   color			�����J���[
 */
//--------------------------------------------------------------
static void FontExBmpwin_FontSet(ACI_PARAM_PTR aci, const STRBUF *str, FONT_TYPE font_type, 	
	FONT_EX_BMPWIN *ex_bmp, GF_PRINTCOLOR color)
{
	int font_len, char_len;
	
	FontLenGet(str, font_type, &font_len, &char_len);
	ex_bmp->font_len = font_len;
	ex_bmp->char_len = char_len;
	if(ex_bmp->bmpwin.chrbuf != NULL){
		GF_BGL_BmpWinDel(&ex_bmp->bmpwin);
	}
	GF_BGL_BmpWinInit(&ex_bmp->bmpwin);
	GF_BGL_BmpWinObjAdd(aci->sys->bgl, &ex_bmp->bmpwin, char_len, 16 / 8, 0, 0);
	GF_STR_PrintExpand(&ex_bmp->bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
		PANEL_MSG_MARGIN, 0, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   ������̒������擾����
 *
 * @param   str				������ւ̃|�C���^
 * @param   font_type		�t�H���g�^�C�v
 * @param   ret_dot_len		�h�b�g�������
 * @param   ret_char_len	�L�����������
 */
//--------------------------------------------------------------
static void FontLenGet(const STRBUF *str, FONT_TYPE font_type, int *ret_dot_len, int *ret_char_len)
{
	int dot_len, char_len;
	
	//������̃h�b�g������A�g�p����L���������Z�o����
	dot_len = FontProc_GetPrintStrWidth(font_type, str, PANEL_MSG_MARGIN);
	char_len = dot_len / 8;
	if(FX_ModS32(dot_len, 8) != 0){
		char_len++;
	}
	
	*ret_dot_len = dot_len;
	*ret_char_len = char_len;
}



//==============================================================================
//
//	�L�[����
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �L�[���͔��菈��
 * @param   aci		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorCheck(ACI_PARAM_PTR aci)
{
	CURSOR_MOVE *move;
	const BG_MAKE_DATA *bmd;

	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];
	
	if(bmd->cursor_move_func == NULL){
		return RECT_HIT_NONE;
	}
	
	if(move->cursor_on == FALSE){
		if(aci->decend_key == TRUE || 
				(sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y
				|PAD_KEY_RIGHT|PAD_KEY_LEFT|PAD_KEY_UP|PAD_KEY_DOWN))){
			if(aci->decend_key == FALSE){
				Snd_SePlay(ASE_CCURSOR_MOVE_SE);	//�L�[�������ăJ�[�\����\������������炷
			}
			move->cursor_on = TRUE;
			aci->decend_key = FALSE;
			bmd->cursor_move_func(aci, TRUE);
		}
		return RECT_HIT_NONE;
	}
	
	return bmd->cursor_move_func(aci, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F�Z�I��
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_WazaSelect(ACI_PARAM_PTR aci, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;
	u8 move_data[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM];
	ACI_CURSOR_SAVE *cursor_save;
	u16 wazano[WAZA_TEMOTI_MAX];
	
	cursor_save = &aci->cursor_save;
	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];
	for(i = 0;i < WAZA_TEMOTI_MAX; i++){
		wazano[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
	}

	if(init_flag == TRUE){
		move->x_menu = cursor_save->waza_x;
		move->y_menu = cursor_save->waza_y;
		index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		if(wazano[index - WAZASELE_INDEX_SKILL_1] == 0){
			cursor_save->waza_x = 0;
			cursor_save->waza_y = 0;
			move->x_menu = 0;
			move->y_menu = 0;
			index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		}
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	MI_CpuCopy8(CursorMoveDataWazaSelect, move_data, 
		CURSOR_WAZA_SELECT_Y_MENU_NUM * CURSOR_WAZA_SELECT_X_MENU_NUM);
#if 0	//�莝���Z���Ȃ��ꏊ���J�[�\�����ړ��o����悤�ɕύX 2006.05.27(�y)
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] == 0){
			((u8*)move_data)[i] = 0xff;	//�莝���Z���Ȃ����͔͈͂���͂���
		}
	}
#endif
	
	key = CursorMove_KeyCheckMove(move, 
		CURSOR_WAZA_SELECT_X_MENU_NUM, CURSOR_WAZA_SELECT_Y_MENU_NUM,
		move_data[0]);
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		break;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ʒu�ۑ��F�R�}���h�I��
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   index			�I����������
 */
//--------------------------------------------------------------
static void CursorSave_WazaSelect(ACI_PARAM_PTR aci, int index)
{
	ACI_CURSOR_SAVE *cursor_save;
	int x, y;

	cursor_save = &aci->cursor_save;
	for(y = 0; y < CURSOR_WAZA_SELECT_Y_MENU_NUM; y++){
		for(x = 0; x < CURSOR_WAZA_SELECT_X_MENU_NUM; x++){
			if(index == CursorMoveDataWazaSelect[y][x]){
				cursor_save->waza_x = x;
				cursor_save->waza_y = y;
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F�R���I��
 *
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_JudgeSelect(ACI_PARAM_PTR aci, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;
	u8 move_data[CURSOR_JUDGE_SELECT_Y_MENU_NUM][CURSOR_JUDGE_SELECT_X_MENU_NUM];
	ACI_CURSOR_SAVE *cursor_save;
	
	cursor_save = &aci->cursor_save;
	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];

	if(init_flag == TRUE){
		move->x_menu = cursor_save->judge_x;
		move->y_menu = cursor_save->judge_y;
		index = CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	MI_CpuCopy8(CursorMoveDataJudgeSelect, move_data, 
		CURSOR_JUDGE_SELECT_Y_MENU_NUM * CURSOR_JUDGE_SELECT_X_MENU_NUM);
	
	key = CursorMove_KeyCheckMove(move, 
		CURSOR_JUDGE_SELECT_X_MENU_NUM, CURSOR_JUDGE_SELECT_Y_MENU_NUM,
		move_data[0]);
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		return JUDGESELE_INDEX_CANCEL;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ʒu�ۑ��F�R�}���h�I��
 * @param   aci				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   index			�I����������
 */
//--------------------------------------------------------------
static void CursorSave_JudgeSelect(ACI_PARAM_PTR aci, int index)
{
	ACI_CURSOR_SAVE *cursor_save;
	int client_no, x, y;

	if(index == JUDGESELE_INDEX_CANCEL){
		return;
	}
	
	cursor_save = &aci->cursor_save;
	for(y = 0; y < CURSOR_JUDGE_SELECT_Y_MENU_NUM; y++){
		for(x = 0; x < CURSOR_JUDGE_SELECT_X_MENU_NUM; x++){
			if(index == CursorMoveDataJudgeSelect[y][x]){
				cursor_save->judge_x = x;
				cursor_save->judge_y = y;
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �L�[���͂ɂ��J�[�\���ړ�����
 *
 * @param   move			�J�[�\���ړ��p���[�N�ւ̃|�C���^
 * @param   x_menu_num		���������̃��j���[��
 * @param   y_menu_num		���������̃��j���[��
 * @param   move_data		�ړ��f�[�^�ւ̃|�C���^(�ړ��悪�����ꏊ�Ȃ�ړ����Ȃ�����ɕK�v)
 *                          ���̔��肪�K�v�łȂ��Ȃ�NULL��OK
 *
 * @retval  �����ꂽ�L�[
 */
//--------------------------------------------------------------
static u32 CursorMove_KeyCheckMove(CURSOR_MOVE *move, int x_menu_num, int y_menu_num, 
	const u8 *move_data)
{
	int old_y_menu, old_x_menu;
	u32 ret_key;
	
	old_x_menu = move->x_menu;
	old_y_menu = move->y_menu;
	
	if(sys.trg & PAD_KEY_UP){
		move->y_menu--;
		if(move->y_menu < 0){
			move->y_menu = 0;//y_menu_num - 1;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->y_menu--;
				if(move->y_menu < 0){
					move->y_menu = old_y_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_UP;
	}
	else if(sys.trg & PAD_KEY_DOWN){
		move->y_menu++;
		if(move->y_menu >= y_menu_num){
			move->y_menu = y_menu_num - 1;//0;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->y_menu++;
				if(move->y_menu >= y_menu_num){
					move->y_menu = old_y_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_DOWN;
	}
	else if(sys.trg & PAD_KEY_LEFT){
		move->x_menu--;
		if(move->x_menu < 0){
			move->x_menu = 0;//x_menu_num - 1;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->x_menu--;
				if(move->x_menu < 0){
					move->x_menu = old_x_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_LEFT;
	}
	else if(sys.trg & PAD_KEY_RIGHT){
		move->x_menu++;
		if(move->x_menu >= x_menu_num){
			move->x_menu = x_menu_num-1;//0;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->x_menu++;
				if(move->x_menu >= x_menu_num){
					move->x_menu = old_x_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_RIGHT;
	}
	else if(sys.trg & PAD_BUTTON_DECIDE){
		ret_key = PAD_BUTTON_DECIDE;
	}
	else if(sys.trg & PAD_BUTTON_CANCEL){
		ret_key = PAD_BUTTON_CANCEL;
	}
	else{
		return 0;
	}
	
	if(move_data != NULL){
		int old_index, new_index;

		old_index = move_data[x_menu_num * old_y_menu + old_x_menu];
		new_index = move_data[x_menu_num * move->y_menu + move->x_menu];
		
		//�J�[�\���ړ���ʒu�m�F
		if(old_index == new_index){
			//�ړ����index���ς��Ȃ��̂ł���΃J�[�\�����W�̈ړ��͂��Ȃ�
			move->x_menu = old_x_menu;
			move->y_menu = old_y_menu;
		}
	}

	if(move->x_menu != old_x_menu || move->y_menu != old_y_menu){
		Snd_SePlay(ASE_CCURSOR_MOVE_SE);
	}
	else{
		if(ret_key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT)){
			return 0;
		}
	}

	return ret_key;
}



//==============================================================================
//
//	V�u�����N����
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   CGR�]�����s��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_CgrTrans(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;

	GF_BGL_LoadCharacter(aci->sys->bgl, GF_BGL_FRAME0_S, aci->cgr_char_data->pRawData, 
		ACI_BG_CGR_SIZE, 0);
	sys_FreeMemoryEz(aci->cgr_arc_data);
	aci->cgr_arc_data = NULL;
	
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   �e�t���[����Visible�ݒ���s��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	const BG_MAKE_DATA *bmd;
	int i;

	bmd = &BgMakeData[aci->makedata_no];
	
	//�eBG�ʂ̕\���E��\���ݒ�
	for(i = 0; i < ACI_BG_NUM; i++){
		if(bmd->scr_id[i] == NONE_ID){
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		}
		else{
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_ON);
		}
	}
	
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�ȊO�̃t���[���S�Ă��\���ɂ���
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;

	Sub_BackScrnOnlyVisible();
	TCB_Delete(tcb);
}

