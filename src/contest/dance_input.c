//==============================================================================
/**
 * @file	dance_input.c
 * @brief	���Z�͕�����͉�ʏ���
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "dance.h"
#include "dance_tcb_pri.h"
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

#include "dance_tool.h"
#include "con_tool.h"
#include "dance_id.h"
#include "dance_input.h"
#include "battle/wazatype_panel.h"
#include "gflib/touchpanel.h"
#include "contype_icon.h"
#include "poketool/waza_tool.h"
#include "aci_tool.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"

#include "msgdata/msg_cmsg_dance.h"
#include "system/fontoam.h"



//==============================================================================
//	�萔��`
//==============================================================================
///�P���t�H���gOBJ�̏������d���̂ōŏ��ɐ������āA�Ȍ�A�o�j�b�V����ON,OFF����ōs��
///�O�����܂Œʂ�K�v�Ȏ��ɐ������āA�K�v�Ȃ��Ȃ�����폜����
#define FONTOBJ_VANISH		(1)


//--------------------------------------------------------------
//	���[�J��TCB�v���C�I���e�B
//--------------------------------------------------------------
#define VWAIT_TCBPRI_CGR_REQ			(8)
#define VWAIT_TCBPRI_FRAMEVISIBLE		(10)
#define VWAIT_TCBPRI_BACKSCRN_VISIBLE	(10)
#define VWAIT_TCBPRI_CGRPARAM_TRANS		(20)



//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///BG�w��Ȃ�
#define NONE_ID			(0xffff)

///BG�g�p�ʐ�
#define DCI_BG_NUM		(4)

///BG�L�����N�^��VRAM�g�p�T�C�Y
#define BG_VRAM_SIZE	(0x8000 - (0x800 * DCI_BG_NUM))

///�W���p���b�g�f�[�^�g�p�{��
#define BASE_PLTT_NUM	(16)

///makedata_no�����l(���g�p���)
#define MAKEDATA_NO_INIT	(-1)

///�R���e�X�g���͉�ʂŎg�p�o����BG��CGR�T�C�Y
#define DCI_BG_CGR_SIZE			(0x6000)

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

///�{�^���J���[�J�n�ʒu(�J���[�P��)
#define BUTTON_COLOR_START		(0*16)
///�{�^���J���[�̐�(�J���[�P��)
#define BUTTON_COLOR_NUM		(16 * 4)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�L�����N�^�W�J�̈�ID
enum{
	EXPAND_CHAR_WALL,
	EXPAND_CHAR_COMMAND,
	
	EXPAND_CHAR_BUTTON_ANM,
	
	EXPAND_CHAR_MAX,
};

///�p���b�g�W�J�̈�ID
enum{
	EXPAND_PALETTE_WALL,
	EXPAND_PALETTE_COMMAND,
	
	EXPAND_PALETTE_MAX,
};

///�X�N���[���W�J�̈�ID
enum{
	EXPAND_SCREEN_WALL_PANEL,
	EXPAND_SCREEN_WALL_BF,
	EXPAND_SCREEN_COMMAND_PANEL,
	EXPAND_SCREEN_BACKGROUND,
	
	EXPAND_SCREEN_MAX,
};

//--------------------------------------------------------------
//	�X�N���[���X�N���[���l
//--------------------------------------------------------------
///TYPE_A��BG�\�����Ƀ^�b�`�p�l���������ꂽ����Y�����ɃX�N���[��������l(�G�t�F�N�g��)
#define SCRN_SCROLL_A_EFF_Y				(16)//(-2)
///TYPE_A��BG�\�����Ƀ^�b�`�p�l���������ꂽ����Y�����ɃX�N���[��������l(�G�t�F�N�g��)
#define SCRN_SCROLL_BACK_A_EFF_Y		(-4)//(1)
///SCRN_SCROLL_BACK_A_EFF_Y�̌�ɒ�ʒu�ɖ߂��܂ł̃X�N���[���l
#define SCRN_SCROLL_RESET_A_EFF_Y		(-(SCRN_SCROLL_A_EFF_Y + SCRN_SCROLL_BACK_A_EFF_Y))

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
	FA_NO_CONRANK = 0,
	FA_NO_CONTYPE,
	
	//COMMAND
#if FONTOBJ_VANISH
	FA_NO_FORWARD,
#else
	FA_NO_FORWARD = 0,			///<�܂�
#endif
	FA_NO_BACK,					///<������
	FA_NO_LEFT,					///<�Ђ���
	FA_NO_RIGHT,				///<�݂�
	
	
	FA_NO_MAX = FA_NO_RIGHT + 1,		///<�t�H���gOBJ����x�ɏo����ő吔
};

///�t�H���gOBJ�̕\�����W
enum{
	//-- ���COMMAND --//
	FA_POS_FORWARD_X = 0x10 * 8,	//X�͒��S���W
	FA_POS_FORWARD_Y = 0x3 * 8,
	FA_POS_BACK_X = 0x10 * 8,	//X�͒��S���W
	FA_POS_BACK_Y = 0xf * 8,
	FA_POS_LEFT_X = 0x6 * 8,	//X�͒��S���W
	FA_POS_LEFT_Y = 0x8 * 8,
	FA_POS_RIGHT_X = 0x1a * 8,	//X�͒��S���W
	FA_POS_RIGHT_Y = 0x8 * 8,
};

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
	PALOFS_COMMAND = 0,
	PALOFS_CONRANK = 0,
};

#define MSGCOLOR_COMMAND		(GF_PRINTCOLOR_MAKE(1, 1, 0xb))
#define MSGCOLOR_CONRANK		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��

//--------------------------------------------------------------
//	�G�t�F�N�gTCB
//--------------------------------------------------------------
///�p�l�����^�b�`������A�G�t�F�N�g�ő҂t���[����
#define SCRN_TOUCH_WAIT	(2)
///�p�l�����^�b�`������A�G�t�F�N�g�ő҂t���[����
#define SCRN_TOUCH_ANM_WAIT	(2)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�{�^���L�����]���p�̃T�C�YX(�L�����N�^�P��)
#define BUTTON_CGR_SIZE_X		(6)
///�{�^���L�����]���p�̃T�C�YY(�L�����N�^�P��)
#define BUTTON_CGR_SIZE_Y		(12)
///�{�^���L�����]���p�O���t�B�b�N�̃A�j���p�^�[����
#define BUTTON_ANM_NUM	(3)

///paracgr�\���̂Ŏg�p����A�N�^�[�|�C���^�̐�
#define PARACGR_CAP_MAX			(3)


//==============================================================================
//	�\���̒�`
//==============================================================================
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

///�G�t�F�N�gTCB�p�̃��[�N
typedef struct{
	s16 seq;
	s16 wait;
	union{
		struct{		//CGR�]���p(�ėp)
			CGR_TRANS_PARAM *ctp;
			const CGR_TRANS_RECTDATA *ctp_rd_ptr[BUTTON_ANM_NUM];
			CATS_ACT_PTR cap[PARACGR_CAP_MAX];	///<�ꏏ�ɃX�N���[��������A�N�^�[�ւ̃|�C���^
			u32 transcgr_id[BUTTON_ANM_NUM];
			int tp_ret;
			u16 arc_id;
			u16 char_x_len;
			u8 fa_no;						///<�Ώۃt�H���gOBJ�A�N�^�[���[�N�̓Y����
		}paracgr;
	};
}DCI_EFFECT_WORK;

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

///�R���e�X�g���͉�ʐ��䃏�[�N
typedef struct _DCI_PARAM{
	CONTEST_SYSTEM *consys;
	DANCE_SYSTEM_PARAM *sys;
	void *scene_work;	///<�V�[�����ɈقȂ�K�v�ƂȂ�f�[�^�ނւ̃|�C���^
	TCB_PTR effect_tcb;	///<�G�t�F�N�g����TCB�ւ̃|�C���^
	EFFBG_WRITE_PARAM ewp;	///<�G�t�F�N�gBG���������p�����[�^

	//�t�H���gOAM
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���g�V�X�e���ւ̃|�C���^
	FONT_ACTOR font_actor[FA_NO_MAX];	///<�t�H���g�A�N�^�[���[�N
	
	u16 cgr_trans_req;		///<V�u�����N�]��CGR���N�G�X�g
	s8 makedata_no;		///<���ݎg�p���Ă���BgMakeData�̔ԍ�
	
	DCI_EFFECT_WORK effect_work;	///<�G�t�F�N�gTCB�p���[�N
	
	u8 *expand_char[EXPAND_CHAR_MAX];
	u16 *expand_screen[EXPAND_SCREEN_MAX];
	u16 *expand_palette[EXPAND_PALETTE_MAX];
}DCI_PARAM;

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
		u16 scr_id[DCI_BG_NUM];		///<�g�p�X�N���[���̃A�[�J�C�uID
	};
	union{
		struct{
			u16 pri0;		///<BG0�ʂ̃v���C�I���e�B
			u16 pri1;		///<BG1�ʂ̃v���C�I���e�B
			u16 pri2;
			u16 pri3;
		};
		u16 pri[DCI_BG_NUM];		///<BG�̃v���C�I���e�B
	};
	
	//�^�b�`�p�l��
	const RECT_HIT_TBL *tpd;	///<�g�p����^�b�`�p�l���f�[�^�ւ̃|�C���^
	const int *tpd_ret;			///<�^�b�`�p�l���̌���
	
	//�֐��|�C���^
	void (*callback_bg)(DCI_PARAM_PTR, int, int);	///<BGCreate���ɌĂяo���֐�
	int (*callback_tp)(DCI_PARAM_PTR, int);			///<�^�b�`�p�l���������ɌĂяo���֐�
}BG_MAKE_DATA;


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code);
static CGR_TRANS_PARAM * Sub_CgrTransParamSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x);
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x);
static void * DINPUT_WorkInit(void);
static void BGCallback_CommandSelect(DCI_PARAM_PTR dci, int select_bg, int force_put);
static int TPCallback_CommandSelect(DCI_PARAM_PTR dci, int tp_ret);
static BOOL Sub_CgrTransEndCheck(CGR_TRANS_PARAM *ctp);
static void Sub_CgrTransNowCopy(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, int char_len_x);
static void Sub_CgrParamTrans(CGR_TRANS_PARAM *ctp);
static void Sub_BackScrnOnlyVisible(void);
static void Sub_TouchEndDelete(DCI_PARAM_PTR dci);
static void Sub_SceneOBJDelete(DCI_PARAM_PTR dci, int sys_exit);
static void EffectTCB_Add(TCB_FUNC func, DCI_PARAM_PTR dci);
static void EffectTCB_Delete(DCI_PARAM_PTR dci);
static void Effect_ButtonDown(TCB_PTR tcb, void *work);
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work);
static void VWait_CgrRequest(TCB_PTR tcb, void *work);
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work);
static void VWait_CgrParamTrans(TCB_PTR tcb, void *work);
static void CommandFontObjCreate(DCI_PARAM_PTR dci);
static void Sub_FontOamCreate(DCI_PARAM_PTR dci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center);
static void Sub_FontOamDeleteAll(DCI_PARAM_PTR dci);
static void Sub_FontOamVanishAll(DCI_PARAM_PTR dci, int vanish);
static void WallFontObjCreate(DCI_PARAM_PTR dci);
static void BGCallback_Wall(DCI_PARAM_PTR dci, int select_bg, int force_put);
static void DINPUT_DefaultExpandBGSet(DCI_PARAM_PTR dci);
static void DINPUT_DefaultExpandBGFree(DCI_PARAM_PTR dci);




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
static const RECT_HIT_TBL CommandSelectTouchData[] = {
	//TOP BOTTOM LEFT RIGHT
	{0*8, 10*8, 11*8, 0x15*8},		//DANCE_TP_JUMP
	{12*8, 0x16*8, 11*8, 0x15*8},	//DANCE_TP_ADVANCE
	{5*8, 15*8, 1*8, 11*8},		//DANCE_TP_LEFT
	{5*8, 15*8, 0x15*8, 0x1f*8},	//DANCE_TP_RIGHT
	{ RECT_HIT_END, 0, 0, 0 }
};
///�Z�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int CommandSelectTouchRet[NELEMS(CommandSelectTouchData) - 1] = {
	DANCE_TP_JUMP,
	DANCE_TP_ADVANCE,
	DANCE_TP_LEFT,
	DANCE_TP_RIGHT,
};
///�Z�I���̃^�b�`�p�l��INDEX(CommandSelectTouchRet�̏���)
enum{
	DANCE_INDEX_JUMP,
	DANCE_INDEX_ADVANCE,
	DANCE_INDEX_LEFT,
	DANCE_INDEX_RIGHT,
};


//==============================================================================
//	
//==============================================================================
///BG�쐬�f�[�^(�������̕��т�ǉ��A�ύX������DINPUT_TYPE_???�̒�`���ύX���邱�ƁI�I)
static const BG_MAKE_DATA BgMakeData[] = {
	{//WALL
		EXPAND_CHAR_WALL,	//CON_SUB_NCGR_BIN,
		EXPAND_PALETTE_WALL,	//CONTEST_SUB_NCLR,
		{
			EXPAND_SCREEN_WALL_PANEL,	//CON_TIT_NSCR_BIN,		//�p�l��
			NONE_ID,		//���g
			EXPAND_SCREEN_WALL_BF,	//CON_SUB_BG_NSCR_BIN,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		NULL,				//�^�b�`�p�l���f�[�^
		NULL,				//�^�b�`�p�l������
		BGCallback_Wall,				//BG�쐬���̃R�[���o�b�N�֐�
		NULL,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//COMMAND
		EXPAND_CHAR_COMMAND,	//CON_DANCE_BUT_NCGR_BIN,
		EXPAND_PALETTE_COMMAND,	//CONTEST_DANCE_SUB_BG_NCLR,
		{
			EXPAND_SCREEN_COMMAND_PANEL,	//CON_DANCE_BUT_NSCR_BIN,		//�p�l��
			NONE_ID,		//���g
			EXPAND_SCREEN_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		CommandSelectTouchData,				//�^�b�`�p�l���f�[�^
		CommandSelectTouchRet,					//�^�b�`�p�l������
		BGCallback_CommandSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_CommandSelect,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
};



//==============================================================================
//
//	
//
//==============================================================================
///�R�}���h�I���p�l��������������CGR�A�j���]���͈�
static const CGR_TRANS_RECTDATA CommandSelectCgrTransRect[][WAZA_TEMOTI_MAX] = {
	{
		{0, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_JUMP
		{18, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_LEFT
		{12, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
	{
		{0, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_JUMP
		{18, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_LEFT
		{12, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
	{
		{0, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_JUMP
		{18, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_LEFT
		{12, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
};


//==============================================================================
//
//	
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   DI�V�X�e�����[�N�̊m�ۂƏ�����
 *
 * @retval  �m�ۂ���DI�V�X�e�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
static void * DINPUT_WorkInit(void)
{
	DCI_PARAM *dci;

	dci = sys_AllocMemory(HEAPID_DANCE, sizeof(DCI_PARAM));
	MI_CpuClear8(dci, sizeof(DCI_PARAM));
	
	dci->makedata_no = MAKEDATA_NO_INIT;
	
	return dci;
}

//--------------------------------------------------------------
/**
 * @brief   BG�\����W���t���[���\���Őݒ肷��
 * @param   bgl		BGL�f�[�^
 */
//--------------------------------------------------------------
void DINPUT_DefaultFrameSet(GF_BGL_INI *bgl)
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
void DINPUT_FrameExit(GF_BGL_INI *bgl)
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
void * DINPUT_SystemInit(CONTEST_SYSTEM *consys, DANCE_SYSTEM_PARAM *sys)
{
	DCI_PARAM *dci;
	
	//���[�N�m��
	dci = DINPUT_WorkInit();
	dci->consys = consys;
	dci->sys = sys;
	
	//�t���[���\���ݒ�	�����ł�邩�͔����H
//	DINPUT_DefaultFrameSet(bgl);

	//�t�H���gOAM�V�X�e���쐬
	dci->fontoam_sys = FONTOAM_SysInit(FA_NO_MAX, HEAPID_DANCE);

	//BG�W�J
	DINPUT_DefaultExpandBGSet(dci);

	return dci;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g���͉�ʂ̃V�X�e�����������
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void DINPUT_SystemFree(DCI_PARAM_PTR dci)
{
	DINPUT_DefaultExpandBGFree(dci);

	Sub_SceneOBJDelete(dci, TRUE);
	FONTOAM_SysDelete(dci->fontoam_sys);
	sys_FreeMemoryEz(dci);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g���͉�ʂōŏ��ɃZ�b�g���Ă����풓�A�N�^�[�̓o�^���s��
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void DINPUT_DefaultActorSet(DCI_PARAM_PTR dci)
{
#if FONTOBJ_VANISH
	WallFontObjCreate(dci);
	CommandFontObjCreate(dci);
	Sub_FontOamVanishAll(dci, FALSE);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ���͉�ʂŎg�p����BG�֘A�f�[�^��S�ēW�J�̈�Ƀ��[�h���Ă���
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DINPUT_DefaultExpandBGSet(DCI_PARAM_PTR dci)
{
	NNSG2dCharacterData *char_data;
	NNSG2dScreenData *scrn_data;
	void *arc_data;
	
	dci->expand_char[EXPAND_CHAR_WALL] = sys_AllocMemory(HEAPID_DANCE, BG_VRAM_SIZE);
	dci->expand_char[EXPAND_CHAR_COMMAND] = sys_AllocMemory(HEAPID_DANCE, BG_VRAM_SIZE);
	dci->expand_char[EXPAND_CHAR_BUTTON_ANM] = sys_AllocMemory(HEAPID_DANCE, 
		BUTTON_CGR_SIZE_X * BUTTON_CGR_SIZE_Y * 0x20 * BUTTON_ANM_NUM);

	dci->expand_screen[EXPAND_SCREEN_WALL_PANEL] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_WALL_BF] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_COMMAND_PANEL] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_BACKGROUND] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	
	dci->expand_palette[EXPAND_PALETTE_WALL] = sys_AllocMemory(HEAPID_DANCE, 0x200);
	dci->expand_palette[EXPAND_PALETTE_COMMAND] = sys_AllocMemory(HEAPID_DANCE, 0x200);
	
	//-- �L�����N�^ --//
	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_SUB_NCGR_BIN, 1, &char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_WALL], BG_VRAM_SIZE);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_NCGR_BIN, 1, 
		&char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_COMMAND], BG_VRAM_SIZE);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_ANIM_NCGR_BIN, 1, 
		&char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_BUTTON_ANM], 
		BUTTON_CGR_SIZE_X * BUTTON_CGR_SIZE_Y * 0x20 * BUTTON_ANM_NUM);
	sys_FreeMemoryEz(arc_data);
	
	//-- �X�N���[�� --//
	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_TIT_NSCR_BIN, 1, &scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_WALL_PANEL], 0x800);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_SUB_BG_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_WALL_BF], 0x800);
	sys_FreeMemoryEz(arc_data);
	
	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_COMMAND_PANEL], 0x800);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_DANCE_SUB_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_BACKGROUND], 0x800);
	sys_FreeMemoryEz(arc_data);

	//-- �p���b�g --//
	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_SUB_NCLR, HEAPID_DANCE, 0x200, 0, 
		dci->expand_palette[EXPAND_PALETTE_WALL]);
	//�v���[�g���������㏑��
	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_SUBTIT_NCLR, HEAPID_DANCE, 32, 
		16 * dci->sys->c_game->type, 
		&dci->expand_palette[EXPAND_PALETTE_WALL][PLATE_PALNO * 16]);

	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_DANCE_SUB_BG_NCLR, HEAPID_DANCE, 0x200, 0, 
		dci->expand_palette[EXPAND_PALETTE_COMMAND]);
}

//--------------------------------------------------------------
/**
 * @brief   ���[�h���Ă�����BG�֌W�f�[�^��S�ĉ������
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DINPUT_DefaultExpandBGFree(DCI_PARAM_PTR dci)
{
	int i;
	
	for(i = 0; i < EXPAND_CHAR_MAX; i++){
		sys_FreeMemoryEz(dci->expand_char[i]);
	}
	for(i = 0; i < EXPAND_SCREEN_MAX; i++){
		sys_FreeMemoryEz(dci->expand_screen[i]);
	}
	for(i = 0; i < EXPAND_PALETTE_MAX; i++){
		sys_FreeMemoryEz(dci->expand_palette[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w��^�C�v��BG��ʂ��`������
 *
 * @param   dci				DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(DINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 * @param   work			�V�[�����ɈقȂ�K�v�ȃf�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void DINPUT_CreateBG(DCI_PARAM_PTR dci, int select_bg, int force_put, void *scene_work)
{
	const BG_MAKE_DATA *bmd, *old_bmd;
	int i;
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	dci->scene_work = scene_work;
	bgl = dci->sys->bgl;
	csp = dci->sys->csp;
	crp = dci->sys->crp;
	
	if(dci->makedata_no == MAKEDATA_NO_INIT){
		force_put = TRUE;
		old_bmd = NULL;
	}
	else{
		old_bmd = &BgMakeData[dci->makedata_no];
	}
	bmd = &BgMakeData[select_bg];

	//�w�i�ȊO�͑S�Ĕ�\��
//	Sub_BackScrnOnlyVisible();
	
	//�eBG�ʂ�BG�v���C�I���e�B�X�V
	{
		for(i = 0; i < DCI_BG_NUM; i++){
			GF_BGL_PrioritySet(GF_BGL_FRAME0_S + i, bmd->pri[i]);
		}
	}
	
	//CGR
	if(1){	//CGR�]���A�j�����s���Ȃ�L����ID�������ł��K���]�����Ă����Ȃ��ƃA�j�����߂�Ȃ�
//	if(bmd->cgr_id != NONE_ID && (force_put == TRUE || bmd->cgr_id != old_bmd->cgr_id)){
	//	ArcUtil_BgCharSet(ARC_CONTEST_BG, bmd->cgr_id, bgl, GF_BGL_FRAME0_S, 
	//		0, DCI_BG_CGR_SIZE, 1, HEAPID_DANCE);
		dci->cgr_trans_req = bmd->cgr_id;
		VWaitTCB_Add(VWait_CgrRequest, dci, VWAIT_TCBPRI_CGR_REQ);
	}
	//PALETTE
	if(bmd->pal_id != NONE_ID && (force_put == TRUE || bmd->pal_id != old_bmd->pal_id)){
	//	PaletteWorkSet_Arc(dci->sys->pfd, ARC_CONTEST_BG, bmd->pal_id, HEAPID_DANCE, 
	//		FADE_SUB_BG, 0, 0);
		PaletteWorkSet(dci->sys->pfd, dci->expand_palette[bmd->pal_id], FADE_SUB_BG, 0, 0x200);
	}
	//SCREEN
	for(i = 0; i < DCI_BG_NUM; i++){
		if(bmd->scr_id[i] != NONE_ID 
				&& (force_put == TRUE || bmd->scr_id[i] != old_bmd->scr_id[i])){
		//	ArcUtil_ScrnSet(ARC_CONTEST_BG, bmd->scr_id[i], bgl, 
		//		GF_BGL_FRAME0_S + i, 0, 0, 1, HEAPID_DANCE);
			GF_BGL_ScreenBufSet(bgl, GF_BGL_FRAME0_S + i, dci->expand_screen[bmd->scr_id[i]], 
				0x800);
			GF_BGL_LoadScreenV_Req(bgl, GF_BGL_FRAME0_S + i);
		}
	}
	
	dci->makedata_no = select_bg;

//	G2S_SetBlendAlpha(BLD_PLANE_1, BLD_PLANE_2, BLD_ALPHA_1, BLD_ALPHA_2);

	Sub_SceneOBJDelete(dci, FALSE);
	//�R�[���o�b�N�֐��Ăяo��
	if(bmd->callback_bg != NULL){
		bmd->callback_bg(dci, select_bg, force_put);
	}

	VWaitTCB_Add(VWait_FrameVisibleUpdate, dci, VWAIT_TCBPRI_FRAMEVISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l����Ԃ𒲂ׂ�
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
int DINPUT_TouchCheck(DCI_PARAM_PTR dci)
{
	int tp_ret, hit, ret;
	const BG_MAKE_DATA *bmd;
	
	GF_ASSERT(dci->makedata_no != MAKEDATA_NO_INIT);
	
	bmd = &BgMakeData[dci->makedata_no];
	if(bmd->tpd == NULL){
		return RECT_HIT_NONE;
	}
	
	GF_ASSERT(bmd->tpd_ret != NULL);
	
	hit = GF_TP_RectHitTrg(bmd->tpd);
	if(hit == RECT_HIT_NONE){
		if(bmd->tpd_ret == CommandSelectTouchRet){
			//�L�[���̓`�F�b�N
			if(sys.trg & (PAD_BUTTON_A | PAD_KEY_RIGHT)){
				hit = DANCE_INDEX_RIGHT;
			}
			else if(sys.trg & (PAD_BUTTON_B | PAD_KEY_DOWN)){
				hit = DANCE_INDEX_ADVANCE;
			}
			else if(sys.trg & (PAD_BUTTON_X | PAD_KEY_UP)){
				hit = DANCE_INDEX_JUMP;
			}
			else if(sys.trg & (PAD_BUTTON_Y | PAD_KEY_LEFT)){
				hit = DANCE_INDEX_LEFT;
			}
		}
	}
	
	if(hit == RECT_HIT_NONE){
		tp_ret = RECT_HIT_NONE;
	}
	else{
		tp_ret = bmd->tpd_ret[hit];
	}
	
	//�R�[���o�b�N�֐��Ăяo��
	if(bmd->callback_tp != NULL){
		tp_ret = bmd->callback_tp(dci, tp_ret);
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���I�����Ă��邩�`�F�b�N
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I�����Ă���B�@FALSE:�I�����Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL DINPUT_EffectEndCheck(DCI_PARAM_PTR dci)
{
	if(dci->effect_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ݎg�p���Ă���BgMakeData�̔ԍ����擾����
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
int DINPUT_MakeDataNoGet(DCI_PARAM_PTR dci)
{
	return dci->makedata_no;
}


//==============================================================================
//
//	BG�쐬���ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_WALL��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   dci				DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(DINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_Wall(DCI_PARAM_PTR dci, int select_bg, int force_put)
{
#if FONTOBJ_VANISH
	Sub_FontOamVanishAll(dci, TRUE);
#else
	WallFontObjCreate(dci);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_WALL�Ŏg�p����t�H���gOBJ�𐶐�����
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void WallFontObjCreate(DCI_PARAM_PTR dci)
{
	STRBUF *rank_src, *type_src;
	u32 rank_id, type_id;
	MSGDATA_MANAGER *man;
	
	//���Z�͕���̃��b�Z�[�W�t�@�C���ɓ����Ă���̂ł����ňꎞ�I�Ƀ}�l�[�W���[�쐬
	man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, HEAPID_DANCE);

	rank_id = ConTool_GetRankMsgID(dci->sys->c_game->rank, dci->sys->c_game->mode, 
		dci->consys->sio_flag);
	type_id = ConTool_GetTypeMsgID(dci->sys->c_game->type, dci->sys->c_game->mode);
	
	rank_src = MSGMAN_AllocString(man, rank_id);
	type_src = MSGMAN_AllocString(man, type_id);
	
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_CONRANK], 
		rank_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		D_PLTTID_SUB_FONTACT, FONT_CONRANK_POS_X, FONT_CONRANK_POS_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_CONTYPE], 
		type_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		D_PLTTID_SUB_FONTACT, FONT_CONTYPE_POS_X, FONT_CONTYPE_POS_Y, FONTOAM_CENTER);
	
	STRBUF_Delete(rank_src);
	STRBUF_Delete(type_src);

	MSGMAN_Delete(man);
}

//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_A��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   dci				DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(DINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_CommandSelect(DCI_PARAM_PTR dci, int select_bg, int force_put)
{
#if FONTOBJ_VANISH
	Sub_FontOamVanishAll(dci, TRUE);
#else
	CommandFontObjCreate(dci);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �R�}���h�I����ʂ̃t�H���gOBJ�𐶐�����
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void CommandFontObjCreate(DCI_PARAM_PTR dci)
{
	STRBUF *forward_src, *back_src, *left_src, *right_src;
	MSGDATA_MANAGER *msg_man;

	msg_man = dci->sys->dance_msg;
	if(dci->sys->jump_up[dci->sys->c_game->my_breeder_no] == TRUE){
		forward_src = MSGMAN_AllocString(msg_man, CDMSG_FORWARD);
	}
	else{
		forward_src = MSGMAN_AllocString(msg_man, CDMSG_FORWARD_02);
	}
	back_src = MSGMAN_AllocString(msg_man, CDMSG_BACK);
	left_src = MSGMAN_AllocString(msg_man, CDMSG_LEFT);
	right_src = MSGMAN_AllocString(msg_man, CDMSG_RIGHT);

	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_FORWARD], forward_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_FORWARD_X, FA_POS_FORWARD_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_BACK], back_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_BACK_X, FA_POS_BACK_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_LEFT], left_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_LEFT_X, FA_POS_LEFT_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_RIGHT], right_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_RIGHT_X, FA_POS_RIGHT_Y, FONTOAM_CENTER);
	
	STRBUF_Delete(forward_src);
	STRBUF_Delete(back_src);
	STRBUF_Delete(left_src);
	STRBUF_Delete(right_src);
}



//==============================================================================
//
//	�^�b�`�p�l���������ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_COMMAND�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   dci			DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_CommandSelect(DCI_PARAM_PTR dci, int tp_ret)
{
	int fa_no;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case DANCE_TP_JUMP:
		fa_no = FA_NO_FORWARD;
		break;
	case DANCE_TP_ADVANCE:
		fa_no = FA_NO_BACK;
		break;
	case DANCE_TP_LEFT:
		fa_no = FA_NO_LEFT;
		break;
	case DANCE_TP_RIGHT:
		fa_no = FA_NO_RIGHT;
		break;
	}
	
	EffectTCB_Add(Effect_ButtonDown, dci);
	dci->effect_work.paracgr.transcgr_id[0] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.transcgr_id[1] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.transcgr_id[2] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.char_x_len = BUTTON_CGR_SIZE_X * BUTTON_ANM_NUM;
	dci->effect_work.paracgr.arc_id = ARC_CONTEST_BG;
	dci->effect_work.paracgr.ctp_rd_ptr[0] = &CommandSelectCgrTransRect[0][tp_ret];
	dci->effect_work.paracgr.ctp_rd_ptr[1] = &CommandSelectCgrTransRect[1][tp_ret];
	dci->effect_work.paracgr.ctp_rd_ptr[2] = &CommandSelectCgrTransRect[2][tp_ret];
	dci->effect_work.paracgr.tp_ret = tp_ret;
	dci->effect_work.paracgr.fa_no = fa_no;
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
 * @brief   CGR�]���A�j�����s�����߂̃p�����[�^���Z�b�g���܂�
 *
 * @param   dci				DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   frame_no		�t���[��NO
 * @param   arc_id			ARC�C���f�b�N�X
 * @param   cgr_id			�]���O���t�B�b�N��CGRID(0xffffffff�̏ꍇ�̓N���A���܂�)
 * @param   rd				�]���͈̓f�[�^�̃|�C���^(cgr_id��0xffffffff�̏ꍇ��src�̒l�͓K����OK)
 * @param   char_len_x		�]���O���t�B�b�N�̉��T�C�Y(�L�����N�^�P��)
 *							cgr_id��0xfffffffff�̏ꍇ��0�ō\���܂���
 *
 * @retval  CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransParamSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
//	void *arc_data;
//	NNSG2dCharacterData *char_data;
	CGR_TRANS_PARAM *ctp;
	
	ctp = sys_AllocMemory(HEAPID_DANCE, sizeof(CGR_TRANS_PARAM));
	MI_CpuClear8(ctp, sizeof(CGR_TRANS_PARAM));
	
	if(cgr_id != 0xffffffff){
		//����expand�ς݂Ȃ̂ŕK�v�Ȃ��Ȃ��� 2006.04.06(��)
		//ctp->arc_data = ArcUtil_CharDataGet(arc_id, cgr_id, 1, &char_data, HEAPID_DANCE);
		//ctp->raw_data = char_data->pRawData;
		ctp->raw_data = dci->expand_char[cgr_id];
	}
	ctp->x_len = char_len_x * 0x20;	//char_data->W * 0x20;
	
	ctp->rd = *rd;
	ctp->dest_vram = GF_BGL_CgxGet(frame_no);
	
	return ctp;
}

//--------------------------------------------------------------
/**
 * @brief   CGR�]���A�j�����s���^�X�N�𐶐����܂�
 *
 * @param   frame_no		�t���[��NO
 * @param   arc_id			ARC�C���f�b�N�X
 * @param   cgr_id			�]���O���t�B�b�N��CGRID(0xffffffff�̏ꍇ�̓N���A���܂�)
 * @param   rd				�]���͈̓f�[�^�̃|�C���^(cgr_id��0xffffffff�̏ꍇ��src�̒l�͓K����OK)
 * @param   char_len_x		�]���O���t�B�b�N�̉��T�C�Y(�L�����N�^�P��)
 *							cgr_id��0xfffffffff�̏ꍇ��0�ō\���܂���
 *
 * @retval  CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 *
 * ���̊֐��g�p��A�K��Sub_CgrTransEndCheck�֐����g�p���A�I���m�F���s���Ă��������B
 * Sub_CgrTransEndCheck�֐����Ń��[�N�̉�������Ȃǂ��s���Ă��܂��B
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
	CGR_TRANS_PARAM *ctp;

	ctp = Sub_CgrTransParamSet(dci, frame_no, arc_id, cgr_id, rd, char_len_x);
	ctp->v_tcb = VWaitTCB_Add(VWait_CgrParamTrans, ctp, VWAIT_TCBPRI_CGRPARAM_TRANS);
	return ctp;
}

//--------------------------------------------------------------
/**
 * @brief   CGR�]���A�j���^�X�N���I�����Ă��邩�m�F
 * @param   ctp		CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 * @retval  TRUE:�I���B�@FALSE:���s��
 *
 * TRUE��Ԃ����A������CGR�]���A�j���p�����[�^���[�N�̉���������s���܂��B
 */
//--------------------------------------------------------------
static BOOL Sub_CgrTransEndCheck(CGR_TRANS_PARAM *ctp)
{
	if(ctp->v_tcb == NULL){
		if(ctp->arc_data != NULL){
			sys_FreeMemoryEz(ctp->arc_data);
		}
		sys_FreeMemoryEz(ctp);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   CGR�]���A�j����V�u�����N�^�X�N�𗘗p�����ɂ������s���܂�
 *
 * @param   frame_no		�t���[��NO
 * @param   arc_id			ARC�C���f�b�N�X
 * @param   cgr_id			�]���O���t�B�b�N��CGRID(0xffffffff�̏ꍇ�̓N���A���܂�)
 * @param   rd				�]���͈̓f�[�^�̃|�C���^(cgr_id��0xffffffff�̏ꍇ��src�̒l�͓K����OK)
 * @param   char_len_x		�]���O���t�B�b�N�̉��T�C�Y(�L�����N�^�P��)
 *							cgr_id��0xfffffffff�̏ꍇ��0�ō\���܂���
 *
 * @retval  CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 *
 * ���̊֐��g�p��A�K��Sub_CgrTransEndCheck�֐����g�p���A�I���m�F���s���Ă��������B
 * Sub_CgrTransEndCheck�֐����Ń��[�N�̉�������Ȃǂ��s���Ă��܂��B
 */
//--------------------------------------------------------------
static void Sub_CgrTransNowCopy(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
	CGR_TRANS_PARAM *ctp;
	
	ctp = Sub_CgrTransParamSet(dci, frame_no, arc_id, cgr_id, rd, char_len_x);
	Sub_CgrParamTrans(ctp);
	if(ctp->arc_data != NULL){
		sys_FreeMemoryEz(ctp->arc_data);
	}
	sys_FreeMemoryEz(ctp);
}

//--------------------------------------------------------------
/**
 * @brief   CGR�]���A�j�����s���܂�
 * @param   ctp		CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_CgrParamTrans(CGR_TRANS_PARAM *ctp)
{
	int x, y, dest_x_len;
	u32 src_y, dest_y;
	
	dest_x_len = 32*32;
	
	src_y = ctp->rd.src_y * ctp->x_len;
	dest_y = ctp->rd.dest_y * dest_x_len;
	
	for(y = 0; y < ctp->rd.size_y; y++){
		if(ctp->raw_data != NULL){
			MI_CpuCopy16(&ctp->raw_data[ctp->x_len * y + src_y + ctp->rd.src_x*0x20], 
				&ctp->dest_vram[dest_x_len * y + dest_y + ctp->rd.dest_x*0x20],
				ctp->rd.size_x * 0x20);
		}
		else{
			MI_CpuClear16(&ctp->dest_vram[dest_x_len * y + dest_y + ctp->rd.dest_x*0x20],
				ctp->rd.size_x * 0x20);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOAM���쐬����
 *
 * @param   dci			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   font_actor	���������t�H���gOAM�֘A�̃��[�N�����
 * @param   str			������
 * @param   font_type	�t�H���g�^�C�v(FONT_SYSTEM��)
 * @param   color		�t�H���g�J���[�\��
 * @param   pal_offset	�p���b�g�ԍ��I�t�Z�b�g
 * @param   pal_id		�o�^�J�n�p���b�gID
 * @param   x			���WX
 * @param   y			���WY
 * @param   pos_center  FONTOAM_LEFT(X���[���W) or FONTOAM_CENTER(X���S���W)
 */
//--------------------------------------------------------------
static void Sub_FontOamCreate(DCI_PARAM_PTR dci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center)
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
	
	bgl = dci->sys->bgl;
	crp = dci->sys->crp;
	
	//������̃h�b�g������A�g�p����L���������Z�o����
	{
		font_len = FontProc_GetPrintStrWidth(font_type, str, PANEL_MSG_MARGIN);
		char_len = font_len / 8;
		if(FX_ModS32(font_len, 8) != 0){
			char_len++;
		}
	}

	//BMP�쐬
	{
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, char_len, 16 / 8, 0, 0);
		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
			PANEL_MSG_MARGIN, 0, NULL);
//		GF_STR_PrintColor(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, NULL );
	}

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB,  HEAPID_DANCE);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
	
	//���W�ʒu�C��
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
//	y += SUB_SURFACE_Y_INTEGER - 8;
	y += (DANCE_SUB_ACTOR_DISTANCE / FX32_ONE) - 8;
	
	finit.fontoam_sys = dci->fontoam_sys;
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
	finit.heap = HEAPID_DANCE;
	
	fontoam = FONTOAM_Init(&finit);
//	FONTOAM_SetPaletteOffset(fontoam, pal_offset);
	FONTOAM_SetPaletteOffsetAddTransPlttNo(fontoam, pal_offset);
	FONTOAM_SetMat(fontoam, x, y);
	
	//�������
	GF_BGL_BmpWinDel(&bmpwin);
	
	font_actor->fontoam = fontoam;
	font_actor->cma = cma;
	font_actor->font_len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���t�H���gOAM��S�č폜������
 * @param   dci		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_FontOamDeleteAll(DCI_PARAM_PTR dci)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(dci->font_actor[i].fontoam != NULL){
			FONTOAM_Delete(dci->font_actor[i].fontoam);
			CharVramAreaFree(&dci->font_actor[i].cma);
			dci->font_actor[i].fontoam = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���t�H���gOBJ�S�Ẵo�j�b�V���t���O�𑀍삷��
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   vanish	�o�j�b�V���t���O(TRUE(�\��) or FALSE(��\��))
 */
//--------------------------------------------------------------
static void Sub_FontOamVanishAll(DCI_PARAM_PTR dci, int vanish)
{
	CATS_RES_PTR crp;
	int i;
	int start, end;
	
	if(vanish == TRUE){
		if(dci->makedata_no == DINPUT_TYPE_WALL){
			start = FA_NO_CONRANK;
			end = FA_NO_CONTYPE;
		}
		else{
			start = FA_NO_FORWARD;
			end = FA_NO_RIGHT;
		}
	}
	else{
		start = 0;
		end = FA_NO_MAX-1;
	}
	
	crp = dci->sys->crp;
	for(i = start; i <= end; i++){
		if(dci->font_actor[i].fontoam != NULL){
			FONTOAM_SetDrawFlag(dci->font_actor[i].fontoam, vanish);
		}
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
	
	for(i = 0; i < DCI_BG_NUM; i++){
		if(1){//GF_BGL_FRAME0_S + i != DANCESUB_FRAME_BACK){
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
 * @param   none		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_TouchEndDelete(DCI_PARAM_PTR dci)
{
	Sub_SceneOBJDelete(dci, FALSE);
	VWaitTCB_Add(VWait_BackScrnOnlyVisible, dci, VWAIT_TCBPRI_BACKSCRN_VISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   BG�^�C�v���؂�ւ�閈�ɍ폜����K�v�̂���OBJ��Delete����
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   sys_exit	TRUE:�V�X�e���̏I���ɂ��폜�B�@FALSE:��ʕύX�A�G�t�F�N�g�ł̍폜��
 */
//--------------------------------------------------------------
static void Sub_SceneOBJDelete(DCI_PARAM_PTR dci, int sys_exit)
{
#if FONTOBJ_VANISH
	if(sys_exit == TRUE){
		Sub_FontOamDeleteAll(dci);
	}
	else{
		Sub_FontOamVanishAll(dci, FALSE);
	}
#else
	Sub_FontOamDeleteAll(dci);
#endif
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
 * @param   dci			DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Add(TCB_FUNC func, DCI_PARAM_PTR dci)
{
	GF_ASSERT(dci->effect_tcb == NULL);
	
	MI_CpuClear8(&dci->effect_work, sizeof(DCI_EFFECT_WORK));
	dci->effect_tcb = TCB_Add(func, dci, TCBPRI_DINPUT_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���폜����
 * @param   dci		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Delete(DCI_PARAM_PTR dci)
{
	if(dci->effect_tcb != NULL){
		TCB_Delete(dci->effect_tcb);
		dci->effect_tcb = NULL;
		MI_CpuClear8(&dci->effect_work, sizeof(DCI_EFFECT_WORK));
	}
}


//--------------------------------------------------------------
/**
 * @brief   �p�l���������L�����]���A�j�������s���ď��������܂��B
 *          1�̃p�l���ɑ΂���1�̃t�H���gOBJ���Z�b�g�ɂȂ��Ă�����̗p�̔ėp�^�X�N�ł�
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_ButtonDown(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int i;
	
	bgl = dci->sys->bgl;
	
	switch(dci->effect_work.seq){
	case 0:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[0], dci->effect_work.paracgr.ctp_rd_ptr[0],
			dci->effect_work.paracgr.char_x_len);
		
		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 0, SCRN_SCROLL_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 1:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 2:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_ANM_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;
	case 3:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[1], dci->effect_work.paracgr.ctp_rd_ptr[1],
			dci->effect_work.paracgr.char_x_len);
		
		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_BACK_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 4:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 5:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;

	case 6:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[2], dci->effect_work.paracgr.ctp_rd_ptr[2],
			dci->effect_work.paracgr.char_x_len);

		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_RESET_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_RESET_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 7:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 8:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;

	default:
		//Sub_TouchEndDelete(dci);
		EffectTCB_Delete(dci);
		return;
	}
}









//==============================================================================
//
//	V�u�����N����
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �e�t���[����Visible�ݒ���s��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	const BG_MAKE_DATA *bmd;
	int i;

	bmd = &BgMakeData[dci->makedata_no];
	
	//�eBG�ʂ̕\���E��\���ݒ�
	for(i = 0; i < DCI_BG_NUM; i++){
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
 * @brief   ���N�G�X�gCGR�]��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_CgrRequest(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	
	if(dci->cgr_trans_req != NONE_ID){
		GF_BGL_LoadCharacter(dci->sys->bgl, GF_BGL_FRAME0_S, 
			dci->expand_char[dci->cgr_trans_req], BG_VRAM_SIZE, 0);
		dci->cgr_trans_req = NONE_ID;
	}
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�ȊO�̃t���[���S�Ă��\���ɂ���
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	DI�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;

	Sub_BackScrnOnlyVisible();
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   V�u�����N����CGR�]���A�j�������s���܂�
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_CgrParamTrans(TCB_PTR tcb, void *work)
{
	CGR_TRANS_PARAM *ctp = work;
	
	Sub_CgrParamTrans(ctp);
	ctp->v_tcb = NULL;
	TCB_Delete(tcb);
}






//==============================================================================
//
//	�c�[��
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �{�^���t�F�[�h
 *
 * @param   dci			DI�V�X�e�����[�N�ւ̃|�C���^
 * @param   color		�ύX��̃J���[
 * @param   evy			EVY�l
 */
//--------------------------------------------------------------
void DINPUT_FadeSet(DCI_PARAM_PTR dci, u16 color, u8 evy)
{
	SoftFadePfd(dci->sys->pfd, FADE_SUB_BG, BUTTON_COLOR_START, BUTTON_COLOR_NUM, evy, color);
}

