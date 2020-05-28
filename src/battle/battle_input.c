//==============================================================================
/**
 * @file	battle_input.c
 * @brief	�퓬���͉�ʏ���
 * @author	matsuda
 * @date	2005.10.12(��)
 */
//==============================================================================
#include "common.h"
#include "graphic\batt_obj_def.h"
#include "graphic\batt_bg_def.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "battle_input.h"
#include "gflib/touchpanel.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/fontproc.h"
#include "gflib/msg_print.h"
#include "application/app_tool.h"
#include "battle/fight_tool.h"
#include "battle_id.h"
#include "client_tool_def.h"
#include "system\msgdata.h"
#include "msgdata/msg_fightmsg_dp.h"
#include "system\pm_str.h"
#include "battle/battle_tcb_pri.h"
#include "battle/wazatype_icon.h"
#include "poketool/waza_tool.h"
#include "system/buflen.h"
#include "battle/wazatype_panel.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/palanm.h"
#include "system/fontoam.h"
#include "poketool/pokeicon.h"
#include "battle/battle_cursor.h"
#include "battle/battle_snd_def.h"
#include "battle/client_tool.h"
#include "battle_input_type.h"
#include "system/pmfprint.h"
#include "battle/finger_cursor.h"
#include "battle/battle_server.h"


#define HAIKEI_CHG	1	//1:�ύX��
#define PP_CHANGE	1
//1:Sub_FontOamData�n�̃��b�Z�[�W�������g��
//���ۂ�Sub_FontOamData�n���g�p����ꍇ�́A������1�ɂ�����A
//Sub_FontOamCreate��S��Sub_FontOamDataRewrite�ɒu��������K�v������܂��B
#define SUBFONT_OAM	0

//==============================================================================
//	�萔��`
//==============================================================================

//�f�o�b�O�p��`�F�P��S_MSG���g�p���������Ȍ`�B�O��S_MSG�Ή�Expand���p�ӂ����܂ł̎b�菈��
#define S_MSG_DEBUG		(0)

//--------------------------------------------------------------
//	�Q�[���p�����[�^
//--------------------------------------------------------------
///�w�i�t�F�[�h��EVY�l
#define BACKFADE_EVY		(6)
///�w�i�t�F�[�h�̃t�F�[�h��̃J���[
#define BACKFADE_COLOR		(0x0000)
///�w�i�t�F�[�h�̃t�F�[�h�r�b�g
#define BACKFADE_FADEBIT	(0x0001)
///�w�i�t�F�[�h�̃t�F�[�h�E�F�C�g
#define BACKFADE_FADE_WAIT	(-2)

//--------------------------------------------------------------
//	���C�A�j��
//--------------------------------------------------------------
///���C�A�j���̃A�j���i�K(�p�[�Z���e�[�W)
enum{
	MOTIVATION_ANM_HIGH = 94,		//16����1 �����؎̂�
	MOTIVATION_ANM_MIDDLE = 87,		//8����1 �����؎̂�
	MOTIVATION_ANM_LOW = 75,		//4����1 �����؎̂�
};

///���C�A�j���^�C�v
enum{
	MOTIVATION_ANM_TYPE_HIGH,
	MOTIVATION_ANM_TYPE_MIDDLE,
	MOTIVATION_ANM_TYPE_LOW,
};

///���C�A�j���F�A�j����]���Z�l
#define MOTIVATION_ADD_ROTATION		(0x0800)
///���C�A�j���F�A�j���ړ���X(����8�r�b�g����)
#define MOTIVATION_ADD_X			(0x0180)
///���C�A�j���F�A�j���t���[����(���̃t���[�����o�߂�����A�j���܂�Ԃ�)
#define MOTIVATION_ANM_FRAME		(2)
///���C�A�j���F�A�j���J��Ԃ���
#define MOTIVATION_ANM_LOOP			(1)
///���C�A�j���F�E�F�C�g�ɉ��Z���郉���_����
#define MOTIVATION_ANM_WAIT_RANDOM	(8)

///���C�A�j���E�F�C�g
enum{
	MOTIVATION_WAIT_HIGH = 10,
	MOTIVATION_WAIT_MIDDLE = 60,
	MOTIVATION_WAIT_LOW = 150,
};

//--------------------------------------------------------------
//	���[�J��TCB�v���C�I���e�B
//--------------------------------------------------------------
#define VWAIT_TCBPRI_FRAMEVISIBLE		(10)
#define VWAIT_TCBPRI_BACKSCRN_VISIBLE	(10)
#define VWAIT_TCBPRI_CGRPARAM_TRANS		(20)


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///BG�w��Ȃ�
#define NONE_ID			(0xffff)

///�p�l���t���[����
#define BI_FRAME_PANEL	(GF_BGL_FRAME0_S)
///�p�l��BGNO��
#define BI_BGNO_PANEL	(0)
///���g�t���[����
#define BI_FRAME_BF		(GF_BGL_FRAME1_S)
///���gBGNO��
#define BI_BGNO_BF		(1)
///�w�i�t���[����
#define BI_FRAME_BACK	(GF_BGL_FRAME2_S)
///�w�iBGNO��
#define BI_BGNO_BACK	(2)
///�G�t�F�N�g�t���[����(���g�X���C�h�p)
#define BI_FRAME_EFF	(GF_BGL_FRAME3_S)
///�G�t�F�N�gBGNO��(���g�X���C�h�p)
#define BI_BGNO_EFF		(3)

///��������1�Ώۖ�
#define BLD_PLANE_1		(GX_BLEND_PLANEMASK_BG1)
///��������2�Ώۖ�
#define BLD_PLANE_2		(GX_BLEND_BGALL)
///��1�Ώۖʂɑ΂��郿�u�����f�B���O�W��
#define BLD_ALPHA_1		(0x1b)	//(9)
///��2�Ώۖʂɑ΂��郿�u�����f�B���O�W��
#define BLD_ALPHA_2		(4)	//(8)

///BG�g�p�ʐ�
#define BI_BG_NUM		(4)

///�W���p���b�g�f�[�^�g�p�{��
#define BASE_PLTT_NUM	(7)

///makedata_no�����l(���g�p���)
#define MAKEDATA_NO_INIT	(-1)

///�v���C���[�̕ǎ��T�C�Y(�o�C�g�P��)
#define BG_PLAYER_WALL_SIZE		(32 * 12 * 0x20)
///�퓬���͉�ʂŎg�p�o����BG��CGR�T�C�Y
#define BI_BG_CGR_SIZE			(0x6000 - BG_PLAYER_WALL_SIZE)
///�v���C���[�̕ǎ��]���I�t�Z�b�g�ʒu(�L�����P��)
#define BG_PLAYER_WALL_OFFSET	(BI_BG_CGR_SIZE / 0x20)

///BG�X�N���[���̃N���A�R�[�h
#define BG_CLEAR_CODE			(0x6000 / 0x20 - 1)

///�t�H���gOAM�f�[�^��BMP�L�����N�^�T�C�YX(�ő啶�����̋Z���)
#define FONTOAMDATA_BMP_X_SIZE		(7 * 14 / 8)

///�I���o���Ȃ��p�l���̊G�̃p���b�g�ԍ�
#define BI_NOT_SELECT_PANEL_PALNO		(0xe)	//(6)

///�^�b�`�������̔w�i�p���b�g�ύX�J���[�J�n�ʒu
#define BACKGROUND_CHANGE_PAL_START		(0xb)

///�|�P�����A�C�R���w��Ȃ�
#define NOT_POKE_ICON			(0xff)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�X�N���[���o�b�t�@�ԍ�
enum{
	SCRNBUF_BACKGROUND,
	SCRNBUF_COMMAND,
	SCRNBUF_COMMAND_WAZA,
	SCRNBUF_WAZA,
	SCRNBUF_POKESELE,
	SCRNBUF_POKESELE_WAKU,
	SCRNBUF_YESNO,
	
	SCRNBUF_MAX,
};

///�X�N���[���o�b�t�@�ɑΉ������X�N���[���f�[�^��ID
///	��SCRNBUF�ƕ��т𓯂��ɂ��Ă������ƁI�I
ALIGN4 static const u16 ScrnArcDataNo[] = {
	BATTLE_WBG0B_NSCR_BIN,		//SCRNBUF_BACKGROUND,
	BATTLE_WBG1A_NSCR_BIN,		//SCRNBUF_COMMAND
	BATTLE_WBG2A_NSCR_BIN,		//SCRNBUF_COMMAND_WAZA
	BATTLE_WBG1B_NSCR_BIN,		//SCRNBUF_WAZA
	BATTLE_WBG1C_NSCR_BIN,		//SCRNBUF_POKESELE
	BATTLE_WBG3A_NSCR_BIN,		//SCRNBUF_POKESELE_WAKU
	BATTLE_WBG1D_NSCR_BIN,		//SCRNBUF_YESNO
};

//--------------------------------------------------------------
//	�X�N���[�����������I�t�Z�b�g
//--------------------------------------------------------------
///�u���������v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_A_FIGHT	(4)
///�u�o�b�O�v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_A_ITEM		(7)
///�u�|�P�����v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_A_POKEMON	(7)
///�u�ɂ���v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_A_ESCAPE	(6)

///�u�Z�P�`�S�v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_B_WAZA		(7)
///�Z�I����ʂ́u���ǂ�v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_B_MODORU	(6)

///������������߂܂����H�u�͂��v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_ESCAPE_YES	(3)
///������������߂܂����H�u�͂��v�R�}���h�̃L�����l�[���ɑ������ރI�t�Z�b�g
#define SCRN_ADD_ESCAPE_NO	(3)

//--------------------------------------------------------------
//	�X�N���[���X�N���[���l
//--------------------------------------------------------------
///TYPE_A��BG�\�����Ƀ^�b�`�p�l���������ꂽ����Y�����ɃX�N���[��������l(�G�t�F�N�g��)
#define SCRN_SCROLL_A_EFF_Y		(-2)
///
#define SCRN_SCROLL_BACK_A_EFF_Y	(1)

///�g�^�C�v
enum{
	WAKU_TYPE_A,
	WAKU_TYPE_B,
	WAKU_TYPE_C,
	
	WAKU_TYPE_NONE,		///<���g�Ȃ�
};

#define WAKU_SP_INIT		(0.09f)
#define WAKU_SP_SUB			(0.025f)
#define WAKU_EFF_FRAME		(6)

//--------------------------------------------------------------
//	�A���X�N���[��
//--------------------------------------------------------------
///�p�l���A��BG�̃X�N���[���R�[�h
#define JOINT_SCRN_CODE		(0x02a4)

//--------------------------------------------------------------
//	�^�b�`�t�F�[�h
//--------------------------------------------------------------
///�^�b�`�������̃{�^���t�F�[�hEVY
#define TOUCH_FADE_EVY		(10 << 8)
///�^�b�`�������̃{�^���t�F�[�hEVY���Z�l
#define TOUCH_FADE_ADD_EVY	(TOUCH_FADE_EVY / 2)

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
	//���A
	FA_NO_FIGHT = 0,		///<��������
	FA_NO_ITEM,
	FA_NO_POKEMON,
	FA_NO_ESCAPE,
	
	//���B
	FA_NO_WAZA_1 = 0,
	FA_NO_WAZA_2,
	FA_NO_WAZA_3,
	FA_NO_WAZA_4,
	FA_NO_WAZA_MODORU,
	FA_NO_PPMSG_1,
	FA_NO_PPMSG_2,
	FA_NO_PPMSG_3,
	FA_NO_PPMSG_4,
	FA_NO_PP_1,
	FA_NO_PP_2,
	FA_NO_PP_3,
	FA_NO_PP_4,
	
	//���C
	FA_NO_NAME_A = 0,
	FA_NO_NAME_B,
	FA_NO_NAME_C,
	FA_NO_NAME_D,
	FA_NO_NAME_MODORU,
	
	//���D
	FA_NO_ESCAPE_YES = 0,
	FA_NO_ESCAPE_NO,
	
	//�|�P�����I��
	FA_NO_POKE_A = 0,
	FA_NO_POKE_B,
	FA_NO_POKE_C,
	FA_NO_POKE_D,
	FA_NO_POKE_CANCEL,
	
	FA_NO_MAX = FA_NO_PP_4 + 1,			///<�t�H���gOBJ����x�ɏo����ő吔
};

///�t�H���gOBJ�̕\�����W
enum{
	//-- ���A --//
	FA_POS_FIGHT_X = 0x10 * 8,		//X�͒��S���W
	FA_POS_FIGHT_Y = 0xa * 8 + 4,
	FA_POS_ITEM_X = 5 * 8,
	FA_POS_ITEM_Y = 0x15 * 8 + 2,
	FA_POS_POKEMON_X = 0x1b * 8,
	FA_POS_POKEMON_Y = FA_POS_ITEM_Y,
	FA_POS_ESCAPE_X = 0x10 * 8,
	FA_POS_ESCAPE_Y = FA_POS_ITEM_Y + 8,
	
	//-- ���B --//
	FA_POS_WAZA_1_X = 8 * 8,	//X�͒��S���W
	FA_POS_WAZA_1_Y = 6 * 8-2,
	FA_POS_WAZA_2_X = 0x18 * 8,
	FA_POS_WAZA_2_Y = FA_POS_WAZA_1_Y,
	FA_POS_WAZA_3_X = FA_POS_WAZA_1_X,
	FA_POS_WAZA_3_Y = FA_POS_WAZA_1_Y + 8*8,
	FA_POS_WAZA_4_X = FA_POS_WAZA_2_X,
	FA_POS_WAZA_4_Y = FA_POS_WAZA_3_Y,
	FA_POS_WAZA_MODORU_X = 0x10 * 8,
	FA_POS_WAZA_MODORU_Y = FA_POS_ESCAPE_Y,

	//-- ���D --//
	FA_POS_ESCAPE_YES_X = 0x10 * 8,			//X�͒��S���W
	FA_POS_ESCAPE_YES_Y = 0x8 * 8 + 4,
	FA_POS_ESCAPE_NO_X = FA_POS_ESCAPE_YES_X,
	FA_POS_ESCAPE_NO_Y = 0x11 * 8 + 4,
};

//�Z�^�C�v�A�C�R���̕\�����W
ALIGN4 static const u16 WazaIconPos[][2] = {	//0:X, 1:Y
	{4*8, 			FA_POS_WAZA_1_Y + 16},
	{0x14*8,			FA_POS_WAZA_2_Y + 16},
	{4*8, 			FA_POS_WAZA_3_Y + 16},
	{0x14*8, 			FA_POS_WAZA_4_Y + 16},
};

//�uPP�v�̕\�����W
ALIGN4 static const u16 PPMsgPos[][2] = {	//0:X, 1:Y
	{4*8 + 28-1, 		FA_POS_WAZA_1_Y + 16},
	{0x14*8 + 28-1,	FA_POS_WAZA_2_Y + 16},
	{4*8 + 28-1, 		FA_POS_WAZA_3_Y + 16},
	{0x14*8 + 28-1,	FA_POS_WAZA_4_Y + 16},
};
//����PP(���l)�̕\�����W
ALIGN4 static const u16 NowPPPos[][2] = {	//0:X, 1:Y
	{4*8 + 44, 		FA_POS_WAZA_1_Y + 16},
	{0x14*8 + 44,		FA_POS_WAZA_2_Y + 16},
	{4*8 + 44, 		FA_POS_WAZA_3_Y + 16},
	{0x14*8 + 44,		FA_POS_WAZA_4_Y + 16},
};

//�Z���ނ̕\�����W(X�F���[���W)
ALIGN4 static const u16 WazaClassPos[][2] = {	//0:X, 1:Y
	{11*8, 8*8 - 16,},
	{0x1b*8, 8*8 - 16,},
	{11*8, 0x11*8 - 16,},
	{0x1b*8, 0x11*8 - 16,},
};

//�|�P�����I��(�Z���ʔ͈�)�̕\�����W
ALIGN4 static const u16 PokeSelePos[][2] = {	//0:X, 1:Y
	{7*8 + 4, 0xe*8 + 4},			//A
	{0x18*8 + 4, 4*8},				//B
	{0x18*8 + 4, 0xe*8 + 4},		//C
	{7*8 + 4, 4*8},					//D
	{0x10*8, FA_POS_WAZA_MODORU_Y},	//���ǂ�
};

//�|�P�����A�C�R���̕\�����W
ALIGN4 static const u16 PokeIconPos[][2] = {	//0:X, 1:Y
	{7*8 + 4, 0xe*8 + 4},			//A
	{0x18*8 + 4, 7*8},				//B
	{0x18*8 + 4, 0xe*8 + 4},		//C
	{7*8 + 4, 7*8},					//D
};

//--------------------------------------------------------------
//	�p���b�g�֘A��`
//--------------------------------------------------------------
///�t�H���gOBJ�̃p���b�g�ԍ��I�t�Z�b�g
enum{
	PALOFS_FIGHT = 2,
	PALOFS_ITEM = 2,
	PALOFS_POKEMON = 2,
	PALOFS_ESCAPE = 2,
	
	PALOFS_WAZA = 3,
	PALOFS_PP = 4,
	PALOFS_WAZA_MODORU = 2,
	
	PALOFS_SYSMSG = 3,
	PALOFS_ESCAPE_YES = 2,
	PALOFS_ESCAPE_NO = 2,
	
	PALOFS_CLASS = 3,
	
	PALOFS_POKESELE = 6,
	PALOFS_POKESELE_MODORU = PALOFS_WAZA_MODORU,
};

#define MSGCOLOR_FIGHT			(GF_PRINTCOLOR_MAKE(1, 2, 3))
#define MSGCOLOR_ITEM			(GF_PRINTCOLOR_MAKE(4, 5, 6))
#define MSGCOLOR_POKEMON		(GF_PRINTCOLOR_MAKE(7, 8, 9))
#define MSGCOLOR_ESCAPE			(GF_PRINTCOLOR_MAKE(10, 11, 12))

#define MSGCOLOR_WAZA			(GF_PRINTCOLOR_MAKE(7, 8, 9))
#define MSGCOLOR_PP_BLACK		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_PP_YELLOW		(GF_PRINTCOLOR_MAKE(3, 4, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_PP_ORANGE		(GF_PRINTCOLOR_MAKE(5, 6, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_PP_RED			(GF_PRINTCOLOR_MAKE(7, 8, 0))	//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_WAZA_MODORU	(GF_PRINTCOLOR_MAKE(10, 11, 12))

#define MSGCOLOR_SYSMSG			(GF_PRINTCOLOR_MAKE(9, 8, 0))//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��
#define MSGCOLOR_ESCAPE_YES		(GF_PRINTCOLOR_MAKE(1, 2, 3))
#define MSGCOLOR_ESCAPE_NO		(GF_PRINTCOLOR_MAKE(10, 11, 12))

#define MSGCOLOR_CLASS			(GF_PRINTCOLOR_MAKE(7, 8, 0))//FONT_SYSTEM�Ȃ̂Ŕw�i�����F�w��

#define MSGCOLOR_POKESELE_ENEMY	(GF_PRINTCOLOR_MAKE(1, 2, 3))
#define MSGCOLOR_POKESELE_MINE	(GF_PRINTCOLOR_MAKE(4, 5, 6))
#define MSGCOLOR_POKESELE_MODORU	(MSGCOLOR_WAZA_MODORU)

//--------------------------------------------------------------
//	�G�t�F�N�gTCB
//--------------------------------------------------------------
///�p�l�����^�b�`�������̃^�b�`�A�j���E�F�C�g
#define SCRN_TOUCH_ANM_WAIT		0//(1)
///�p�l�����^�b�`������A�G�t�F�N�g�ő҂t���[����
#define SCRN_TOUCH_WAIT			0//(1)	//(2)


//--------------------------------------------------------------
//	�莝���{�[��
//--------------------------------------------------------------
///�莝���{�[��(���@��)�̃A�N�^�[�\�t�g�v���C�I���e�B
#define SOFTPRI_STOCK_MINE		(10)
///�莝���{�[��(�G����)�̃A�N�^�[�\�t�g�v���C�I���e�B
#define SOFTPRI_STOCK_ENEMY		(11)

///�莝���{�[��(���@��)�̍��[�̎莝���{�[��X���W
#define STOCK_MINE_BASE_POS_X		(12)
///�莝���{�[��(���@��)�̍��[�̎莝���{�[��Y���W
#define STOCK_MINE_BASE_POS_Y		(13)
///�莝���{�[��(���@��)�̘A���Ń{�[����z�u���鎞�̊ԊuX��
#define STOCK_MINE_BASE_SPACE_X		(19)

///�莝���{�[��(�G��)�̍��[�̎莝���{�[��X���W
#define STOCK_ENEMY_BASE_POS_X		(246)
///�莝���{�[��(�G��)�̍��[�̎莝���{�[��Y���W
#define STOCK_ENEMY_BASE_POS_Y		(9)
///�莝���{�[��(�G��)�̘A���Ń{�[����z�u���鎞�̊ԊuX��
#define STOCK_ENEMY_BASE_SPACE_X	(-12)

///�퓬�J�[�\���̃A�N�^�[�\�t�g�v���C�I���e�B
#define SOFTPRI_CURSOR				(5)
///�퓬�J�[�\����BG�v���C�I���e�B
#define BGPRI_CURSOR				(0)

//--------------------------------------------------------------
//	�Z�^�C�v
//--------------------------------------------------------------
///�Z�^�C�v�̃p���b�g�J�n�ʒu
#define WAZATYPE_START_PALPOS	(8)

//--------------------------------------------------------------
//	�R�}���h�I����ʁF�X���C�h�C���G�t�F�N�g
//--------------------------------------------------------------
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E0�̏������WX
#define COMMANDIN_WND_START_X0		(0)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E0�̏������WX
#define COMMANDIN_WND_END_X0		(255)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E1�̏������WX
#define COMMANDIN_WND_START_X1		(0)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E1�̏������WX
#define COMMANDIN_WND_END_X1		(255)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E0�̏������WY
#define COMMANDIN_WND_START_Y0		(0)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E0�̏������WY
#define COMMANDIN_WND_END_Y0		(18 * 8)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E1�̏������WY
#define COMMANDIN_WND_START_Y1		(COMMANDIN_WND_END_Y0)
///�R�}���h�I�����IN�G�t�F�N�g�F�E�B���h�E1�̏������WY
#define COMMANDIN_WND_END_Y1		(192)

#define COMMANDIN_SCR_X0_START		(255 * 100)
#define COMMANDIN_SCR_Y1_START		(40 * 100)
///�R�}���h�C���X���C�h�G�t�F�N�g�ɂ�����t���[����
#define COMMANDIN_EFF_FRAME			(4)	//(8)
#define COMMANDIN_SCR_X0_ADD		(COMMANDIN_SCR_X0_START / COMMANDIN_EFF_FRAME)
#define COMMANDIN_SCR_Y1_ADD		(COMMANDIN_SCR_Y1_START / COMMANDIN_EFF_FRAME)

//--------------------------------------------------------------
//	�ߊl�f��
//--------------------------------------------------------------
///�ߊl�f���p�w�J�[�\���F�\�t�g�v���C�I���e�B
#define FINGER_SOFTPRI		(10)
///�ߊl�f���p�w�J�[�\���FBG�v���C�I���e�B
#define FINGER_BGPRI		(0)
///�ߊl�f���p�w�J�[�\���F�^�b�`����܂ł̃E�F�C�g
#define FINGER_TOUCH_WAIT	(60)


//==============================================================================
//	�\���̒�`
//==============================================================================
///�R�}���h�I����ʁF�X�N���[���C���G�t�F�N�g���[�N
typedef struct{
	BI_PARAM_PTR bip;	///<BI�V�X�e�����[�N�ւ̃|�C���^
	TCB_PTR vtask_tcb;	///<V�u�����N����^�X�N�̃|�C���^
	
	s16 x0_l;		///<100�̏��Z������
	s16 y1_d;
	s16 set_x0_l;
	s16 set_y1_d;
	s16 h_set_y1_d;
	
	u8 client_type;
	u8 seq;
}COMMAND_IN_EFF_WORK;

typedef struct{
	s16 x;
	s16 y;
}POINT_S16;

///�X�N���[�������������͈͎̔w��\����
typedef struct{
	u8 top;
	u8 bottom;
	u8 left;
	u8 right;
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

///�{�^���̃A�j���p�^�[����
#define BUTTON_ANM_NUM			(2)

///�G�t�F�N�gTCB�p�̃��[�N
typedef struct{
	s16 seq;
	s16 wait;
	union{
		struct{		//�ėp
			u8 fa_no;						///<�Ώۃt�H���gOBJ�A�N�^�[���[�N�̓Y����
		}para;
		struct{		//�Z�I��p
			int tp_ret;
		}waza;
		struct{		//CGR�]���p(�ėp)
//			CGR_TRANS_PARAM *ctp;
//			const CGR_TRANS_RECTDATA *ctp_rd_ptr[BUTTON_ANM_NUM];
//			u32 transcgr_id[BUTTON_ANM_NUM];
			const s16 *scrn_offset;
			const REWRITE_SCRN_RECT *scrn_range;
			int tp_ret;
			u8 scrnbuf_no;
			u8 fa_no;						///<�Ώۃt�H���gOBJ�A�N�^�[���[�N�̓Y����
			u8 pokeicon_no;					///<�Ώۃ|�P�A�C�R���A�N�^�[���[�N�̓Y����
			u8 waku_type;
			POINT_S16 waku_pos;
		}paracgr;
		struct{
			CGR_TRANS_PARAM *ctp[CLIENT_MAX];
			CGR_TRANS_PARAM *purple_ctp;
			NNSG2dCharacterData *cgr_char_data;
			void *cgr_arc_data;
			int tp_ret;
		}pokesele;
		s16 work[2];
	};
}BI_EFFECT_WORK;

///�J���[�G�t�F�N�gTCB�p�̃��[�N
typedef struct{
	int tp_ret;
	s16 evy;		///<EVY�l(����8�r�b�g����)
	s16 evy_add;	///<EVY�����Z�l(����8�r�b�g����)
	u8 seq;
	u8 pal_pos;	///<�t�F�[�h�Ώۂ̃p���b�g�ԍ�
}BI_COLOR_EFF_WORK;

///�G�t�F�N�gBG���������p�����[�^
typedef struct{
	const REWRITE_SCRN_RECT *rsr;	///<�X�N���[�����������͈̓f�[�^�ւ̃|�C���^
	u8 rsr_num;						///<rsr�f�[�^��
	s8 add_charname;				///<�L�����N�^�l�[���ɑ������ރI�t�Z�b�g�l
}EFFBG_WRITE_PARAM;

///���g���[�N
typedef struct{
	struct _BI_PARAM *bip;
	CATS_ACT_PTR cap;
	f32 add_sp;
	s32 work;
	s32 wait;
	u8 type;
}BLACK_WAKU_WORK;

///�t�H���g�A�N�^�[���[�N
typedef struct{
	FONTOAM_OBJ_PTR fontoam;
	CHAR_MANAGER_ALLOCDATA cma;
	u16 font_len;
}FONT_ACTOR;

///���C�A�j���p���[�N
typedef struct{
	s16 x_offset;			///<X���W�I�t�Z�b�g(����8�r�b�g����)
	u8 motivation;			///<���݂̃��`�x�[�V����(0�`100)
	u8 seq;
	u8 anm_type;
	u8 wait;
	u8 count;				///<�ړ��t���[�����J�E���g
	u8 count_max;			///<�ړ��t���[���ő吔(���̕��ړ�������܂�Ԃ�)
	u8 loop;				///<�A�j���J��Ԃ���
}MOTIVATION_WORK;

///�J�[�\���ړ��p���[�N
typedef struct{
	u8 cursor_on;			///<TRUE�F�J�[�\���\�����
	s8 y_menu;				///<�K�w���j���[�̈ʒu(Y)
	s8 x_menu;				///<�������j���[�̈ʒu(X)
	
	u8 dummy;
}CURSOR_MOVE;

///�V�[�����[�N
typedef union{
	BINPUT_SCENE_COMMAND bsc;
	BINPUT_SCENE_WAZA bsw;
	BINPUT_SCENE_POKE bsp;
	BINPUT_SCENE_YESNO bsy;
}SCENE_WORK;

///�t�H���gOAM�쐬���A�O����BMP�w�肷��ꍇ�Ɏg�p
typedef struct{
	GF_BGL_BMPWIN bmpwin;
	u16 char_len;
	u16 font_len;
}FONT_EX_BMPWIN;

///�`�揈���������ׁ̈A���炩���߃f�[�^���쐬���Ă����ׂ̃��[�N
typedef struct{
	BINPUT_WAZA_PARAM wazapara;				///<�f�[�^��r�p�Ɍ��݂̃p�����[�^�ۑ�
	
	//�Z�^�C�v�A�C�R���F�L�����f�[�^�W�J������
	u16 *typeicon_cgx[WAZA_TEMOTI_MAX];		///<�Z�^�C�v�A�C�R���F�L�����f�[�^�W�J������
	
	//�t�H���gOAM�Ɋ֘A�t����BMPWIN
	FONT_EX_BMPWIN exbmp_waza[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_pp[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_ppmax[WAZA_TEMOTI_MAX];
}MEMORY_DECORD_WORK;

///�퓬���͉�ʐ��䃏�[�N
typedef struct _BI_PARAM{
	BATTLE_WORK *bw;
	TCB_PTR ball_tcb;		///<�{�[�����C�A�j��TCB�ւ̃|�C���^
	TCB_PTR effect_tcb;	///<�G�t�F�N�g����TCB�ւ̃|�C���^
	TCB_PTR color_eff_tcb;	///<�J���[�G�t�F�N�g����TCB�ւ̃|�C���^
	EFFBG_WRITE_PARAM ewp;	///<�G�t�F�N�gBG���������p�����[�^
	
	//�V�[�����[�N
	SCENE_WORK scene;	///<�V�[�����ɈقȂ�K�v�ȃf�[�^��
	
	//�X�N���[���o�b�t�@
	u16 *scrn_buf[SCRNBUF_MAX];	///<�X�N���[���o�b�t�@
	//�p���b�g�o�b�t�@
	u16 *pal_buf;				///<�p���b�g�o�b�t�@
	
	u16 *background_pal_normal;	///<�ʏ펞�̔w�i�p�p���b�g
	u16 *background_pal_touch;	///<�^�b�`���Ă��鎞�̔w�i�p�p���b�g
	TCB_PTR background_tcb;		///<�w�i�p���b�g�؂�ւ��Ď��^�X�N�ւ̃|�C���^
	
	MEMORY_DECORD_WORK memory_decord[CLIENT_MAX];	///<�������ׁ̈A���炩���߃f�[�^���쐬���Ă���
	
	//�t�H���gOAM
	FONTOAM_SYS_PTR fontoam_sys;	///<�t�H���g�V�X�e���ւ̃|�C���^
	FONT_ACTOR font_actor[FA_NO_MAX];	///<�t�H���g�A�N�^�[���[�N
	FONTOAM_OAM_DATA_PTR font_oamdata;
	
	//�莝���{�[��
	CATS_ACT_PTR stock_mine_cap[POKEMON_TEMOTI_MAX];	///<���@���莝���{�[���A�N�^�[�|�C���^
	CATS_ACT_PTR stock_enemy_cap[POKEMON_TEMOTI_MAX];	///<�G���莝���{�[���A�N�^�[�|�C���^
	
	//�Z�^�C�v�A�C�R��
	CATS_ACT_PTR icon_cap[WAZA_TEMOTI_MAX];		///<�Z�^�C�v�A�C�R���A�N�^�[�|�C���^
	//�Z���ރA�C�R��
	CATS_ACT_PTR kindicon_cap[WAZA_TEMOTI_MAX];		///<�Z���ރA�C�R���A�N�^�[�|�C���^
	//�|�P�����A�C�R��
	CATS_ACT_PTR pokeicon_cap[CLIENT_MAX];		///<�|�P�����A�C�R���A�N�^�[�|�C���^
	TCB_PTR      pokeicon_tcb[CLIENT_MAX];		///<�|�P�����A�C�R���A�N�^�[�A�j���X�V�^�X�N
	
	//���C�A�j��
	MOTIVATION_WORK motivation_work[POKEMON_TEMOTI_MAX];	///<���C�A�j���p���[�N
	
	//�g�傷�鍕�g
	BLACK_WAKU_WORK waku;

	//�w�i�t�F�[�h
	TCB_PTR backfade_tcb;			///<�w�i�t�F�[�h����^�X�N�ւ̃|�C���^
	u8 backfade_seq;				///<�w�i�t�F�[�h����^�X�N�̃V�[�P���X�ԍ�
	u8 backfade_flag;				///<�w�i�t�F�[�h�̌���̃t�F�[�h���
	
	u8 client_type;		///<�N���C�A���g�^�C�v
	s8 makedata_no;		///<���ݎg�p���Ă���BgMakeData�̔ԍ�
	u8 pokesele_type;	///<�|�P�����I���̎��͈̔̓^�C�v
	u8 sex;				///<�w�i���o�����̐���
	u8 touch_invalid;	///<TRUE:�^�b�`��������
	u8 command_modoru_type;		///<TRUE:�R�}���h�I����ʂ́u�ɂ���v���u���ǂ�v�ɂȂ��Ă���
	
	//�풓�t�F�[�h
	u8 def_fade_dir;		///<0:�{�����ւ̃t�F�[�h�A1:�|�����ւ̃t�F�[�h
	s16 def_fade_evy;		///<�풓�t�F�[�h��EVY�l(����8�r�b�g����)
	u8 waku_fade_dir;		///<�g�p�A0:�{�����ւ̃t�F�[�h�A1:�|�����ւ̃t�F�[�h
	s16 waku_fade_evy;		///<�g�p�A�풓�t�F�[�h��EVY�l(����8�r�b�g����)
	TCB_PTR def_fade_tcb;	///<�풓�t�F�[�h���s�^�X�N�ւ̃|�C���^
	
	BI_EFFECT_WORK effect_work;	///<�G�t�F�N�gTCB�p���[�N
	BI_COLOR_EFF_WORK color_work;	///<�J���[�G�t�F�N�gTCB�p���[�N

	s32 wall_x;					///<�w�i�X�N���[�����WX(����8�r�b�g����)
	s32 wall_sp_x;				///<�w�i�X�N���[�����xX(����8�r�b�g����)
	s32 wall_end_x;				///<�w�i�X�N���[�����WX(����8�r�b�g����)
	
	BCURSOR_PTR cursor;			///<�J�[�\�����[�N�ւ̃|�C���^
	CURSOR_MOVE cursor_move;	///<�J�[�\���ړ��p���[�N
	u8 decend_key;				///<TRUE:����{�^�����������̂��J�[�\��
	
	//�ߊl�f���p���[�N
	struct{
		FINGER_PTR finger;
		u8 main_seq;
		u8 sub_seq;
		u8 sub_wait;
	}demo;
	
}BI_PARAM;

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
		u16 scr_id[BI_BG_NUM];		///<�g�p�X�N���[���̃A�[�J�C�uID
	};
	union{
		struct{
			u16 pri0;		///<BG0�ʂ̃v���C�I���e�B
			u16 pri1;		///<BG1�ʂ̃v���C�I���e�B
			u16 pri2;
			u16 pri3;
		};
		u16 pri[BI_BG_NUM];		///<BG�̃v���C�I���e�B
	};
	
	//�^�b�`�p�l��
	const RECT_HIT_TBL *tpd;	///<�g�p����^�b�`�p�l���f�[�^�ւ̃|�C���^
	const int *tpd_ret;			///<�^�b�`�p�l���̌���
	const u8 *tpd_pal;			///<�^�b�`���������̃p�l���̃p���b�g�ԍ��f�[�^�ւ̃|�C���^
	
	//�J�[�\���ړ�
	int (*cursor_move_func)(BI_PARAM_PTR, int);	///<�L�[���͂��������̃R�[���o�b�N�֐�
	void (*cursor_save_func)(BI_PARAM_PTR, int);	///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
	
	//�֐��|�C���^
	void (*callback_bg)(BI_PARAM_PTR, int, int);	///<BGCreate���ɌĂяo���֐�
	int (*callback_tp)(BI_PARAM_PTR, int, int);			///<�^�b�`�p�l���������ɌĂяo���֐�
}BG_MAKE_DATA;


//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void * BINPUT_WorkInit(void);
static void BGCallback_CommandIn(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_CommandSelect(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_CommandInFightOnly(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_FightOnly(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_ParkCommandIn(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_ParkCommand(BI_PARAM_PTR bip, int select_bg, int force_put);
static int TPCallback_A(BI_PARAM_PTR bip, int tp_ret, int panel_pal);
static int TPCallback_Waza(BI_PARAM_PTR bip, int tp_ret, int panel_pal);
static void BGCallback_Waza(BI_PARAM_PTR bip, int select_bg, int force_put);
static void Sub_ScrnAddOffset(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl,
	int frame_no, int add_charname);
static void Sub_ScrnCopy(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int src_frame, int dest_frame);
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code);
static void Sub_ScrnTouchChange(GF_BGL_INI *bgl, const REWRITE_SCRN_RECT rsr[], int rsr_num, 
	int add_charname);
static void Sub_ScrnTouchChangeReverse(GF_BGL_INI *bgl, const REWRITE_SCRN_RECT rsr[], 
	int rsr_num, int add_charname);
static void Sub_WazaTypeIconCreateAll(BI_PARAM_PTR bip);
static void Sub_WazaTypeIconDeleteAll(BI_PARAM_PTR bip);
static void Sub_WazaKindIconCreateAll(BI_PARAM_PTR bip);
static void Sub_WazaKindIconDeleteAll(BI_PARAM_PTR bip);
static void EffectTCB_Add(TCB_FUNC func, BI_PARAM_PTR bip);
static void EffectTCB_Delete(BI_PARAM_PTR bip);
static void Effect_ScrnTouch(TCB_PTR tcb, void *work);
static void Effect_WazaScrnTouch(TCB_PTR tcb, void *work);
static int TPCallback_D(BI_PARAM_PTR bip, int tp_ret, int panel_pal);
static int TPCallback_PokeSele(BI_PARAM_PTR bip, int tp_ret, int panel_pal);
static void BGCallback_YesNo(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_Wasureru(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_Akirameru(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_NextPokemon(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_ChangePokemon(BI_PARAM_PTR bip, int select_bg, int force_put);
static void BGCallback_PokeSelect(BI_PARAM_PTR bip, int select_bg, int force_put);
static void Sub_WazaTypeCGRTrans(BI_PARAM_PTR bip, int waza_type, int waza_pos);
static void Sub_WazaTypeNotTemotiChainCGRTrans(BI_PARAM_PTR bip, int waza_pos);
static void Sub_PokemonNotPanelTrans(BI_PARAM_PTR bip, int poke_pos);
static int Sub_StockBallAnmSeqGet(u8 status);
static void BINPUT_StockBallActorResourceFree(BI_PARAM_PTR bip);
void BINPUT_StockBallAnimeUpdate(BI_PARAM_PTR bip, u8 stock_mine[], u8 stock_enemy[]);
void BINPUT_StockBallON(BI_PARAM_PTR bip);
void BINPUT_StockBallOFF(BI_PARAM_PTR bip);
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work);
static void Sub_BackScrnOnlyVisible(void);
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work);
static void Sub_TouchEndDelete(BI_PARAM_PTR bip, int obj, int bg);
static void Sub_SceneOBJDelete(BI_PARAM_PTR bip);
static void Effect_ButtonDown(TCB_PTR tcb, void *work);
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(
	int frame_no, u32 cgr_id, const CGR_TRANS_RECTDATA *rd, NNSG2dCharacterData **loaded_char);
static BOOL Sub_CgrTransEndCheck(CGR_TRANS_PARAM *ctp);
static void VWait_CgrParamTrans(TCB_PTR tcb, void *work);
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work);
static void Effect_PokeSeleButtonDown(TCB_PTR tcb, void *work);
static void Sub_PokeSelectPanelConnectRange(BI_PARAM_PTR bip, int target, u8 *connect_range, 
	int check_exist);
static void Sub_PokeSelectHitRange(BI_PARAM_PTR bip, u8 *hit_range, int check_exist);
static void Sub_CgrParamTrans(CGR_TRANS_PARAM *ctp);
static void ColorEffTCB_Add(TCB_FUNC func, BI_PARAM_PTR bip);
static void ColorEffTCB_Delete(BI_PARAM_PTR bip);
static void ColorEffTCB_PointFadeSet(BI_PARAM_PTR bip, int pal_pos);
static void ColorEff_PointFade(TCB_PTR tcb, void *work);
void BINPUT_PlayerBG_SetX(BI_PARAM_PTR bip, int x);
void BINPUT_PlayerBG_ScrollX(BI_PARAM_PTR bip, int sp_x, int end_x);
static void PlayerBGScrollX(TCB_PTR tcb, void *work);
static void Waku_ResourceLoad(BI_PARAM_PTR bip, int waku_type);
static void Waku_ResourceFree(BI_PARAM_PTR bip, int waku_type);
static CATS_ACT_PTR Waku_ActorSet(BI_PARAM_PTR bip, int waku_type, int x, int y);
static void Waku_ActorDel(BI_PARAM_PTR bip, CATS_ACT_PTR cap);
static void Waku_ActorResourceSet(BI_PARAM_PTR bip, int waku_type, int x, int y);
static void Waku_ActorResourceDel(BI_PARAM_PTR bip);
static void Waku_MoveTCB(TCB_PTR tcb, void *work);
static void ColorEffTCB_PokeSeleFadeSet(BI_PARAM_PTR bip, int tp_ret);
static void ColorEff_PokeSeleFade(TCB_PTR tcb, void *work);
static void Sub_FontOamCreate(BI_PARAM_PTR bip, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, FONT_EX_BMPWIN *ex_bmpwin);
static void Sub_FontOamDeleteAll(BI_PARAM_PTR bip);
static void Sub_PokeIconResourceLoad(BI_PARAM_PTR bip);
static void Sub_PokeIconResourceFree(BI_PARAM_PTR bip);
static void Sub_PokeIconActorAllDel(BI_PARAM_PTR bip);
static CATS_ACT_PTR Sub_PokeIconCharActorSet(BI_PARAM_PTR bip, POKEMON_PARAM *pp, int client_type,
	int hp, int maxhp, int status);
static void PokeIconAnimeUpdate(TCB_PTR tcb, void *work);
static void CommandInEffTask(TCB_PTR tcb, void *work);
static void VBlankTCB_CommandInEff(TCB_PTR tcb, void *work);
static void HBlank_CommandInEff(void *work);
static GF_PRINTCOLOR PP_FontColorGet(int pp, int pp_max);
static void Sub_FontOamDataInit(BI_PARAM_PTR bip);
static void Sub_FontOamDataExit(BI_PARAM_PTR bip);
static void Sub_FontOamDataRewrite(BI_PARAM_PTR bip, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id,
	int x, int y, int pos_center);
static void Sub_FontOamDataEnableAllOff(BI_PARAM_PTR bip);
void BINPUT_BackFadeReq(BI_PARAM_PTR bip, int fade_dir);
static void BackFadeTask(TCB_PTR tcb, void *work);
BOOL BINPUT_BackFadeExeCheck(BI_PARAM_PTR bip);
static void DefaultFadeAnimeTask(TCB_PTR tcb, void *work);
static void StockBallMain(TCB_PTR tcb, void *work);
static int CursorCheck(BI_PARAM_PTR bip);
static int CursorMove_CommandSelect(BI_PARAM_PTR bip, int init_flag);
static int CursorMove_WazaSelect(BI_PARAM_PTR bip, int init_flag);
static int CursorMove_PokeSelect(BI_PARAM_PTR bip, int init_flag);
static int CursorMove_YesNo(BI_PARAM_PTR bip, int init_flag);
static u32 CursorMove_KeyCheckMove(CURSOR_MOVE *move, int x_menu_num, int y_menu_num, 
	const u8 *move_data);
static void CursorSave_CommandSelect(BI_PARAM_PTR bip, int index);
static void CursorSave_WazaSelect(BI_PARAM_PTR bip, int index);
static void CursorSave_PokeSelect(BI_PARAM_PTR bip, int index);
static void Sub_ScrnOffsetRewrite(BI_PARAM_PTR bip, const s16 *scrn_offset, 
	const REWRITE_SCRN_RECT *range, int scrnbuf_no, int anm_no);
static MEMORY_DECORD_WORK *MemoryDecordWorkGet(BI_PARAM_PTR bip, int client_type);
static void MemoryDecordWorkFree(BI_PARAM_PTR bip);
static void FontLenGet(const STRBUF *str, FONT_TYPE font_type, 
	int *ret_dot_len, int *ret_char_len);
static void FontExBmpwin_FontSet(BI_PARAM_PTR bip, const STRBUF *str, FONT_TYPE font_type, 	
	FONT_EX_BMPWIN *ex_bmp, GF_PRINTCOLOR color);
static void Sub_JointScreenWrite(BI_PARAM_PTR bip);
static int CursorMove_ParkCommandSelect(BI_PARAM_PTR bip, int init_flag);
static void BackGroundTouchPaletteCheck(TCB_PTR tcb, void *work);
static int CaptureDemo_Main(BI_PARAM_PTR bip);
static int CaptureDemoSeq_CommandFight(BI_PARAM_PTR bip);
static int CaptureDemoSeq_Waza(BI_PARAM_PTR bip);
static int CaptureDemoSeq_CommandBag(BI_PARAM_PTR bip);

//--------------------------------------------------------------
//	�C�����C���֐��̃v���g�^�C�v�錾
//--------------------------------------------------------------
inline void SubInline_EffBgWriteParamSet(EFFBG_WRITE_PARAM *ewp, const REWRITE_SCRN_RECT *rsr, 
	u8 rsr_num, s8 add_charname);


//==============================================================================
//	�f�[�^
//==============================================================================
///�퓬���͉�ʗp��BG�t���[���\��
static const GF_BGL_BGCNT_HEADER BiBgCntDat[] = {
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

//==============================================================================
//	BG�L���������ւ��f�[�^
//==============================================================================
///�u���������v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT FightRsr[] = {
	{3, 13, 1, 0x1e},
};
///�u�A�C�e���v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT ItemRsr[] = {
	{0xe, 0x12, 1, 0xe},
	{0x13, 0x16, 1, 0x9},
};
///�u�|�P�����v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT PokemonRsr[] = {
	{0xe, 0x12, 0x11, 0x1e},
	{0x13, 0x16, 0x16, 0x1e},
};
///�u�ɂ���v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT EscapeRsr[] = {
	{0x13, 0x17, 0xb, 0x14},
};

///�u�Z�P�v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT Skill1Rsr[] = {
	{1, 9, 0, 0xf},
};
///�u�Z�Q�v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT Skill2Rsr[] = {
	{1, 9, 0x10, 0x1f},
};
///�u�Z�R�v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT Skill3Rsr[] = {
	{0xa, 0x12, 0, 0xf},
};
///�u�Z�S�v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT Skill4Rsr[] = {
	{0xa, 0x12, 0x10, 0x1f},
};
///�Z�I����ʂ́u���ǂ�v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT SkillModoruRsr[] = {
	{0x13, 0x17, 0x1, 0x1e},
};

///������������߂܂����H�́u�͂��v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT EscapeYesRsr[] = {
	{4, 12, 1, 0x1e},
};
///������������߂܂����H�́u�������v�p�l����BG�����ւ�
static const REWRITE_SCRN_RECT EscapeNoRsr[] = {
	{14, 21, 1, 0x1e},
};

//============================================================================================
//	�^�b�`�p�l���̈�ݒ�
//============================================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�R�}���h�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL BattleMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{3*8, 0x12*8, 0*8, 255},			//��������
	{0x12*8, 0x18*8, 0*8, 0xa*8},		//�o�b�O
	{0x12*8, 0x18*8, 0x16*8, 255},	//�|�P����
	{0x13*8, 0x18*8, 0xb*8, 0x15*8},	//�ɂ���
	{ RECT_HIT_END, 0, 0, 0 }
};
///�R�}���h�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int BattleMenuTouchRet[NELEMS(BattleMenuTouchData) - 1] = {
	SELECT_FIGHT_COMMAND,		//��������
	SELECT_ITEM_COMMAND,		//�o�b�O
	SELECT_POKEMON_COMMAND,		//�|�P����
	SELECT_ESCAPE_COMMAND,		//�ɂ���
};
///�R�}���h�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 BattleMenuPaletteNo[NELEMS(BattleMenuTouchData) - 1] = {
	1,		//��������
	2,		//�o�b�O
	3,		//�|�P����
	4,		//�ɂ���
};

///�J�[�\���ړ��F�R�}���h�I���̐������j���[�̍ő吔
#define CURSOR_COMMAND_SELECT_X_MENU_NUM		(3)
///�J�[�\���ړ��F�R�}���h�I���̃��j���[�̊K�w�̐�
#define CURSOR_COMMAND_SELECT_Y_MENU_NUM		(2)// + 1)
///�R�}���h�I���̃^�b�`�p�l��INDEX(BattleMenuTouchRet�̏���)
enum{
	COMMSELE_INDEX_FIGHT,
	COMMSELE_INDEX_ITEM,
	COMMSELE_INDEX_POKEMON,
	COMMSELE_INDEX_ESCAPE,
};
///�J�[�\���ړ��F�R�}���h�I���̈ړ��͈̓f�[�^(TouchData��index�ԍ�)
ALIGN4 static const u8 CursorMoveDataCommandSelect[CURSOR_COMMAND_SELECT_Y_MENU_NUM][CURSOR_COMMAND_SELECT_X_MENU_NUM] = {
	{COMMSELE_INDEX_FIGHT, COMMSELE_INDEX_FIGHT, COMMSELE_INDEX_FIGHT},		//��������
	{COMMSELE_INDEX_ITEM, COMMSELE_INDEX_ESCAPE, COMMSELE_INDEX_POKEMON},//�o�b�O�A�ɂ���A�|�P����
	//�o�b�Oor�|�P�����̉ӏ��ŉ�����������u�ɂ���v�Ɉړ�����悤��3�i�ڂ����
//	{COMMSELE_INDEX_ESCAPE, COMMSELE_INDEX_ESCAPE, COMMSELE_INDEX_ESCAPE},//�ɂ���A�ɂ���A�ɂ���
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�u���������v�݂̂̃R�}���h�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL FightOnlyBattleMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{3*8, 0x12*8, 0*8, 255},			//��������
	{ RECT_HIT_END, 0, 0, 0 }
};

///�J�[�\���ړ��F�u���������v�݂̂̃R�}���h�I���̐������j���[�̍ő吔
#define CURSOR_COMMAND_FIGHTONLY_X_MENU_NUM		(1)
///�J�[�\���ړ��F�u���������v�݂̂̃R�}���h�I���̃��j���[�̊K�w�̐�
#define CURSOR_COMMAND_FIGHTONLY_Y_MENU_NUM		(1)

//--------------------------------------------------------------
//	�|�P�p�[�N
//--------------------------------------------------------------
///�u�{�[���v�Ɓu������v�݂̂̃R�}���h�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL ParkCommandMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{5*8, 0x10*8, 3*8, 0x1d*8},			//��������
	{0x13*8, 0x18*8, 0xb*8, 0x15*8},	//�ɂ���
	{ RECT_HIT_END, 0, 0, 0 }
};

///�|�P�p�[�N�p�R�}���h�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int ParkMenuTouchRet[NELEMS(BattleMenuTouchData) - 1] = {
	SELECT_FIGHT_COMMAND,		//��������
	SELECT_ESCAPE_COMMAND,		//�ɂ���
};
///�|�P�p�[�N�p�R�}���h�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 ParkMenuPaletteNo[NELEMS(BattleMenuTouchData) - 1] = {
	1,		//��������
	4,		//�ɂ���
};

///�J�[�\���ړ��F�R�}���h�I���̐������j���[�̍ő吔
#define CURSOR_PARK_COMMAND_SELECT_X_MENU_NUM		(1)
///�J�[�\���ړ��F�R�}���h�I���̃��j���[�̊K�w�̐�
#define CURSOR_PARK_COMMAND_SELECT_Y_MENU_NUM		(2)
///�R�}���h�I���̃^�b�`�p�l��INDEX(ParkMenuTouchRet�̏���)
enum{
	PARKSELE_INDEX_FIGHT,
	PARKSELE_INDEX_ESCAPE,
};
///�J�[�\���ړ��F�R�}���h�I���̈ړ��͈̓f�[�^(TouchData��index�ԍ�)
ALIGN4 static const u8 CursorMoveDataParkCommandSelect[CURSOR_PARK_COMMAND_SELECT_Y_MENU_NUM][CURSOR_PARK_COMMAND_SELECT_X_MENU_NUM] = {
	{PARKSELE_INDEX_FIGHT},		//��������
	{PARKSELE_INDEX_ESCAPE},	//�ɂ���
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�Z�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL SkillMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{0x13*8, 0x18*8, 1*8, 0x1f*8},		//�L�����Z��
	{3*8, 10*8, 0*8, 0x10*8},		//�Z1
	{3*8, 10*8, 0x10*8, 255},	//�Z2
	{0xb*8, 0x12*8, 0*8, 0x10*8},	//�Z3
	{0xb*8, 0x12*8, 0x10*8, 255},	//�Z4
	{ RECT_HIT_END, 0, 0, 0 }
};
///�Z�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int SkillMenuTouchRet[NELEMS(SkillMenuTouchData) - 1] = {
	SELECT_CANCEL,				//�L�����Z��
	SELECT_SKILL_1,
	SELECT_SKILL_2,
	SELECT_SKILL_3,
	SELECT_SKILL_4,
};
///�Z�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 SkillMenuPaletteNo[NELEMS(SkillMenuTouchData) - 1] = {
	4,		//SELECT_CANCEL,				//�L�����Z��
	8,		//SELECT_SKILL_1,
	9,		//SELECT_SKILL_2,
	0xa,	//SELECT_SKILL_3,
	0xb,	//SELECT_SKILL_4,
};

///�J�[�\���ړ��F�Z�I���̐������j���[�̍ő吔
#define CURSOR_WAZA_SELECT_X_MENU_NUM		(2)
///�J�[�\���ړ��F�Z�I���̃��j���[�̊K�w�̐�
#define CURSOR_WAZA_SELECT_Y_MENU_NUM		(3)
///�Z�I���̃^�b�`�p�l��INDEX(SkillMenuTouchRet�̏���)
enum{
	WAZASELE_INDEX_CANCEL,
	WAZASELE_INDEX_SKILL_1,
	WAZASELE_INDEX_SKILL_2,
	WAZASELE_INDEX_SKILL_3,
	WAZASELE_INDEX_SKILL_4,
};
///�J�[�\���ړ��F�Z�I���̈ړ��͈̓f�[�^
ALIGN4 static const u8 CursorMoveDataWazaSelect[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM] = {
	{WAZASELE_INDEX_SKILL_1, WAZASELE_INDEX_SKILL_2},		//�Z�P�A�Z�Q
	{WAZASELE_INDEX_SKILL_3, WAZASELE_INDEX_SKILL_4},		//�Z�R�A�Z�S
	{WAZASELE_INDEX_CANCEL, WAZASELE_INDEX_CANCEL},		//�L�����Z���A�L�����Z��
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�u������������߂܂����H�v�I���^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL EscapeMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{5*8, 0xc*8, 1*8, 0x1f*8},		//�͂�
	{0xe*8, 0x15*8, 1*8, 0x1f*8},		//������
	{ RECT_HIT_END, 0, 0, 0 }
};
///�u������������߂܂����H�v�I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int EscapeMenuTouchRet[NELEMS(EscapeMenuTouchData) - 1] = {
	TRUE,			//�͂�
	SELECT_CANCEL,			//������
};
///�u������������߂܂����H�v�I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 EscapeMenuPaletteNo[NELEMS(EscapeMenuTouchData) - 1] = {
	1,		//TRUE,			//�͂�
	4,		//SELECT_CANCEL,			//������
};
///�J�[�\���ړ��F�u�͂�/�������v�̐������j���[�̍ő吔
#define CURSOR_YESNO_SELECT_X_MENU_NUM		(1)
///�J�[�\���ړ��F�u�͂�/�������v�̃��j���[�̊K�w�̐�
#define CURSOR_YESNO_SELECT_Y_MENU_NUM		(2)
///�Z�I���̃^�b�`�p�l��INDEX(SkillMenuTouchRet�̏���)
enum{
	YESNO_INDEX_TRUE,
	YESNO_INDEX_CANCEL,
};
///�J�[�\���ړ��F�u�͂�/�������v�̈ړ��͈̓f�[�^
ALIGN4 static const u8 CursorMoveDataYesNoSelect[CURSOR_YESNO_SELECT_Y_MENU_NUM][CURSOR_YESNO_SELECT_X_MENU_NUM] = {
	{YESNO_INDEX_TRUE},
	{YESNO_INDEX_CANCEL},
};

//--------------------------------------------------------------
//	�|�P�����I��(�Z����)
//--------------------------------------------------------------
///�|�P�����I��(�Z����)�^�b�`�p�l���̈�ݒ�
static const RECT_HIT_TBL PokeSeleMenuTouchData[] = {
	//UP DOWN LEFT RIGHT
	{0xb*8, 0x12*8, 0*8, 0xf*8},			//�^�[�Q�b�gA
	{1*8, 0xa*8, 0x11*8, 255},		//�^�[�Q�b�gB
	{0xb*8, 0x12*8, 0x11*8, 255},		//�^�[�Q�b�gC
	{1*8, 0xa*8, 0*8, 0xf*8},			//�^�[�Q�b�gD
	{0x13*8, 0x18*8, 1*8, 0x1f*8},		//�L�����Z��
	{ RECT_HIT_END, 0, 0, 0 }
};
///�|�P�����I���^�b�`�p�l���̃^�b�`���ʕԎ�
static const int PokeSeleMenuTouchRet[NELEMS(PokeSeleMenuTouchData) - 1] = {
	SELECT_TARGET_A,		//�^�[�Q�b�gA
	SELECT_TARGET_B,		//�^�[�Q�b�gB
	SELECT_TARGET_C,		//�^�[�Q�b�gC
	SELECT_TARGET_D,		//�^�[�Q�b�gD
	SELECT_CANCEL,			//���ǂ�
};
///�|�P�����I���^�b�`�p�l���̊e�p�l���̃p���b�g�ԍ�
ALIGN4 static const u8 PokeSeleMenuPaletteNo[NELEMS(PokeSeleMenuTouchData) - 1] = {
	6,		//SELECT_TARGET_A,		//�^�[�Q�b�gA
	0xc,	//SELECT_TARGET_B,		//�^�[�Q�b�gB
	0xd,	//SELECT_TARGET_C,		//�^�[�Q�b�gC
	5,		//SELECT_TARGET_D,		//�^�[�Q�b�gD
	4,		//SELECT_CANCEL,			//���ǂ�
};

///�|�P�����I���̃^�b�`�p�l��INDEX(PokeSeleMenuTouchRet�̏���)
enum{
	POKESELE_INDEX_TARGET_A,
	POKESELE_INDEX_TARGET_B,
	POKESELE_INDEX_TARGET_C,
	POKESELE_INDEX_TARGET_D,
	POKESELE_INDEX_TARGET_CANCEL,
};

///�J�[�\���ړ��F�|�P�����I��(�P���I���̏ꍇ)�̐������j���[�̍ő吔
#define CURSOR_POKE_SELECT_X_MENU_NUM		(2)
///�J�[�\���ړ��F�|�P�����I��(�P���I���̏ꍇ)�̃��j���[�̊K�w�̐�
#define CURSOR_POKE_SELECT_Y_MENU_NUM		(3)
///�J�[�\���ړ��F�|�P�����I��(�P���I���̏ꍇ)�̈ړ��͈̓f�[�^
ALIGN4 static const u8 CursorMoveDataPokeSelect[CURSOR_POKE_SELECT_Y_MENU_NUM][CURSOR_POKE_SELECT_X_MENU_NUM] = {
	{POKESELE_INDEX_TARGET_D, POKESELE_INDEX_TARGET_B},
	{POKESELE_INDEX_TARGET_A, POKESELE_INDEX_TARGET_C},
	{POKESELE_INDEX_TARGET_CANCEL, POKESELE_INDEX_TARGET_CANCEL},
};

//==============================================================================
//	
//==============================================================================
///BG�쐬�f�[�^(�������̕��т�ǉ��A�ύX������BINPUT_TYPE_???�̒�`���ύX���邱�ƁI�I)
static const BG_MAKE_DATA BgMakeData[] = {
	{//BINPUT_TYPE_WALL
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			NONE_ID,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		NULL,				//�^�b�`�p�l���f�[�^
		NULL,				//�^�b�`�p�l������
		NULL,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		NULL,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		NULL,				//BG�쐬���̃R�[���o�b�N�֐�
		NULL,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_COMMAND_IN
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandIn,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_COMMAND_IN_2		2�̖�
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandIn,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_A
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_A_2		2�̖�
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_COMMAND_IN_FIGHTONLY
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		FightOnlyBattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandInFightOnly,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_FIGHTONLY
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			SCRNBUF_COMMAND_WAZA,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		FightOnlyBattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_FightOnly,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_COMMAND_IN_SAFARI
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandIn,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_A_SAFARI
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		BattleMenuTouchData,				//�^�b�`�p�l���f�[�^
		BattleMenuTouchRet,					//�^�b�`�p�l������
		BattleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_CommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_CommandSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_CommandSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_COMMAND_IN_PARK
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			NONE_ID,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		ParkCommandMenuTouchData,				//�^�b�`�p�l���f�[�^
		ParkMenuTouchRet,					//�^�b�`�p�l������
		ParkMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_ParkCommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_ParkCommandIn,			//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_PARK
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_COMMAND,		//�p�l��
			NONE_ID,		//�Z�I���p�l���̉e
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 3, 3, 0},
		ParkCommandMenuTouchData,				//�^�b�`�p�l���f�[�^
		ParkMenuTouchRet,					//�^�b�`�p�l������
		ParkMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_ParkCommandSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_ParkCommand,			//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_A,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_WAZA
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_WAZA,		//�p�l��
			NONE_ID,					//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		SkillMenuTouchData,				//�^�b�`�p�l���f�[�^
		SkillMenuTouchRet,				//�^�b�`�p�l������
		SkillMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_WazaSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_WazaSelect,			///<�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_Waza,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_Waza,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_POKE
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_POKESELE,		//�p�l��
			SCRNBUF_POKESELE_WAKU,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		PokeSeleMenuTouchData,				//�^�b�`�p�l���f�[�^
		PokeSeleMenuTouchRet,				//�^�b�`�p�l������
		PokeSeleMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_PokeSelect,				//�L�[���͂��������̃R�[���o�b�N�֐�
		CursorSave_PokeSelect,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_PokeSelect,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_PokeSele,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_YESNO
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_YESNO,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		EscapeMenuTouchData,				//�^�b�`�p�l���f�[�^
		EscapeMenuTouchRet,				//�^�b�`�p�l������
		EscapeMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_YesNo,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_YesNo,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_D,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_WASURERU
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_YESNO,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		EscapeMenuTouchData,				//�^�b�`�p�l���f�[�^
		EscapeMenuTouchRet,				//�^�b�`�p�l������
		EscapeMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_YesNo,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_Wasureru,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_D,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_AKIRAMERU
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_YESNO,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		EscapeMenuTouchData,				//�^�b�`�p�l���f�[�^
		EscapeMenuTouchRet,				//�^�b�`�p�l������
		EscapeMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_YesNo,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_Akirameru,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_D,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_NEXT_POKEMON
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_YESNO,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		EscapeMenuTouchData,				//�^�b�`�p�l���f�[�^
		EscapeMenuTouchRet,				//�^�b�`�p�l������
		EscapeMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_YesNo,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_NextPokemon,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_D,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
	{//BINPUT_TYPE_CHANGE_POKEMON
		BATTLE_W_NCGR_BIN,
		BATTLE_W_NCLR,
		{
			SCRNBUF_YESNO,		//�p�l��
			NONE_ID,		//���g
			SCRNBUF_BACKGROUND,		//�w�i
			NONE_ID,							//���g�X���C�h�p
		},
		{2, 1, 3, 0},
		EscapeMenuTouchData,				//�^�b�`�p�l���f�[�^
		EscapeMenuTouchRet,				//�^�b�`�p�l������
		EscapeMenuPaletteNo,				//�^�b�`�p�l���̊e�p���b�g�̃p���b�g�ԍ�
		CursorMove_YesNo,				//�L�[���͂��������̃R�[���o�b�N�֐�
		NULL,				//�L�[�ʒu�L���̃R�[���o�b�N�֐�
		BGCallback_ChangePokemon,				//BG�쐬���̃R�[���o�b�N�֐�
		TPCallback_D,				//�^�b�`�p�l���������̃R�[���o�b�N�֐�
	},
};


//==============================================================================
//
//	�A�N�^�[�w�b�_
//
//==============================================================================
///�莝���{�[���F���@���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S StockObjParam_Mine = {
	STOCK_MINE_BASE_POS_X, STOCK_MINE_BASE_POS_Y, 0,		//x, y, z
	0, SOFTPRI_STOCK_MINE, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_STOCK_MINE,	//�L����
		PLTTID_INPUT_COMMON,	//�p���b�g
		CELLID_STOCK_MINE,	//�Z��
		CELLANMID_STOCK_MINE,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�莝���{�[���F�G���A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S StockObjParam_Enemy = {
	STOCK_ENEMY_BASE_POS_X, STOCK_ENEMY_BASE_POS_Y, 0,		//x, y, z
	0, SOFTPRI_STOCK_ENEMY, 1,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_STOCK_ENEMY,	//�L����
		PLTTID_INPUT_COMMON,	//�p���b�g
		CELLID_STOCK_ENEMY,	//�Z��
		CELLANMID_STOCK_ENEMY,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�Z�^�C�v�A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S WazaTypeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, 100, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_WAZATYPE_ICON_1,	//�L����
		PLTTID_WAZATYPE_ICON,	//�p���b�g
		CELLID_WAZATYPE_ICON,	//�Z��
		CELLANMID_WAZATYPE_ICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�Z���ރA�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S WazaKindIconObjParam = {
	0, 0, 0,		//x, y, z
	0, 100, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_WAZAKIND_ICON_1,	//�L����
		PLTTID_WAZAKIND_ICON,	//�p���b�g
		CELLID_WAZAKIND_ICON,	//�Z��
		CELLANMID_WAZAKIND_ICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///���g�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S BlackWakuObjParam = {
	0, 0, 0,		//x, y, z
	0, 150, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		0,	//�L����
		0,	//�p���b�g
		0,	//�Z��
		0,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�|�P�����A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S PokeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, 100, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DSUB,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_POKEICON_B,				//�L����
		PLTTID_POKEICON,				//�p���b�g
		CELLID_POKEICON,				//�Z��
		CELLANMID_POKEICON,				//�Z���A�j��
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
ALIGN4 static const u16 WazaTypeCgrPos[] = {0, 6, 12, 18};


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
#define SCRN_NO_NOT_TOUCH_0		(0x260)
///�����Ȃ��p�l���̃X�N���[���I�t�Z�b�g�����߂鎞�̕␳�l
///�������Ȃ��p�l���͉�����p�l������1�i���Ȃ��ʒu���炵���f�[�^���Ȃ��̂�
#define SCRN_NO_NOT_TOUCH_HOSEI	(32)

//--------------------------------------------------------------
//	�R�}���h�I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�R�}���h�I���u���������v�A�j��0�A����
#define SCRN_NO_COMMAND_FIGHT_0		(0x20)
///�X�N���[���ԍ��F�R�}���h�I���u���������v�A�j��1�A����
#define SCRN_NO_COMMAND_FIGHT_1		(0xe0)
///�X�N���[���ԍ��F�R�}���h�I���u���������v�A�j��2�A����
#define SCRN_NO_COMMAND_FIGHT_2		(0x1a0)

///�X�N���[���ԍ��F�R�}���h�I���u�o�b�O�v�A�j��0�A����
#define SCRN_NO_COMMAND_ITEM_0		(0x5)
///�X�N���[���ԍ��F�R�}���h�I���u�o�b�O�v�A�j��1�A����
#define SCRN_NO_COMMAND_ITEM_1		(0xc5)
///�X�N���[���ԍ��F�R�}���h�I���u�o�b�O�v�A�j��2�A����
#define SCRN_NO_COMMAND_ITEM_2		(0x185)

///�X�N���[���ԍ��F�R�}���h�I���u�|�P�����v�A�j��0�A����
#define SCRN_NO_COMMAND_POKEMON_0	(0x8)
///�X�N���[���ԍ��F�R�}���h�I���u�|�P�����v�A�j��1�A����
#define SCRN_NO_COMMAND_POKEMON_1	(0xc8)
///�X�N���[���ԍ��F�R�}���h�I���u�|�P�����v�A�j��2�A����
#define SCRN_NO_COMMAND_POKEMON_2	(0x188)

///�X�N���[���ԍ��F�R�}���h�I���u�ɂ���v�A�j��0�A����
#define SCRN_NO_COMMAND_ESCAPE_0	(0x1d)
///�X�N���[���ԍ��F�R�}���h�I���u�ɂ���v�A�j��1�A����
#define SCRN_NO_COMMAND_ESCAPE_1	(0xdd)
///�X�N���[���ԍ��F�R�}���h�I���u�ɂ���v�A�j��2�A����
#define SCRN_NO_COMMAND_ESCAPE_2	(0x19d)

///�R�}���h�I���p�l�������������̃{�^���A�j���p�X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 CommandButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//SELECT_FIGHT_COMMAND
		SCRN_NO_COMMAND_FIGHT_0 - SCRN_NO_COMMAND_FIGHT_0,
		SCRN_NO_COMMAND_FIGHT_1 - SCRN_NO_COMMAND_FIGHT_0,
		SCRN_NO_COMMAND_FIGHT_2 - SCRN_NO_COMMAND_FIGHT_0,
	},
	{//SELECT_ITEM_COMMAND
		SCRN_NO_COMMAND_ITEM_0 - SCRN_NO_COMMAND_ITEM_0,
		SCRN_NO_COMMAND_ITEM_1 - SCRN_NO_COMMAND_ITEM_0,
		SCRN_NO_COMMAND_ITEM_2 - SCRN_NO_COMMAND_ITEM_0,
	},
	{//SELECT_POKEMON_COMMAND
		SCRN_NO_COMMAND_POKEMON_0 - SCRN_NO_COMMAND_POKEMON_0,
		SCRN_NO_COMMAND_POKEMON_1 - SCRN_NO_COMMAND_POKEMON_0,
		SCRN_NO_COMMAND_POKEMON_2 - SCRN_NO_COMMAND_POKEMON_0,
	},
	{//SELECT_ESCAPE_COMMAND
		SCRN_NO_COMMAND_ESCAPE_0 - SCRN_NO_COMMAND_ESCAPE_0,
		SCRN_NO_COMMAND_ESCAPE_1 - SCRN_NO_COMMAND_ESCAPE_0,
		SCRN_NO_COMMAND_ESCAPE_2 - SCRN_NO_COMMAND_ESCAPE_0,
	},
};

///�R�}���h�I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT CommandButtonScrnRect[] = {
	{4, 0xf, 2, 0x1d},
	{0x11, 0x17, 0, 0x9},
	{0x11, 0x17, 0x16, 0x1f},
	{0x12, 0x17, 0xb, 0x14},
};

//--------------------------------------------------------------
//	�Z�I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_0_0		(0x11)
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_0_1		(0xd1)
///�X�N���[���ԍ��F�Z�I���u�Z0�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_0_2		(0x191)

///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_1_0		(0x14)
///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_1_1		(0xd4)
///�X�N���[���ԍ��F�Z�I���u�Z1�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_1_2		(0x194)

///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_2_0		(0x17)
///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_2_1		(0xd7)
///�X�N���[���ԍ��F�Z�I���u�Z2�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_2_2		(0x197)

///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��0�A����
#define SCRN_NO_WAZA_SKILL_3_0		(0x1a)
///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��1�A����
#define SCRN_NO_WAZA_SKILL_3_1		(0xda)
///�X�N���[���ԍ��F�Z�I���u�Z3�v�A�j��2�A����
#define SCRN_NO_WAZA_SKILL_3_2		(0x19a)

///�X�N���[���ԍ��F�Z�I���u�L�����Z���v�A�j��0�A����
#define SCRN_NO_WAZA_CANCEL_0		(0x1d)
///�X�N���[���ԍ��F�Z�I���u�L�����Z���v�A�j��1�A����
#define SCRN_NO_WAZA_CANCEL_1		(0xdd)
///�X�N���[���ԍ��F�Z�I���u�L�����Z���v�A�j��2�A����
#define SCRN_NO_WAZA_CANCEL_2		(0x19d)

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
	{//SELECT_CANCEL
		SCRN_NO_WAZA_CANCEL_0 - SCRN_NO_WAZA_CANCEL_0,
		SCRN_NO_WAZA_CANCEL_1 - SCRN_NO_WAZA_CANCEL_0,
		SCRN_NO_WAZA_CANCEL_2 - SCRN_NO_WAZA_CANCEL_0,
	},
};

///�Z�I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonScrnRect[] = {
	{2, 9, 0, 0xf},
	{2, 9, 0x10, 0x1f},
	{0xa, 0x11, 0, 0xf},
	{0xa, 0x11, 0x10, 0x1f},
	{0x12, 0x17, 1, 0x1e},
};

///�Z�I���p�l���������Ȃ��{�^���ɂ��鎞�̃X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 WazaButtonNotTouchScrnOffset[] = {
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_0_0 - SCRN_NO_NOT_TOUCH_HOSEI,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_1_0 - SCRN_NO_NOT_TOUCH_HOSEI,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_2_0 - SCRN_NO_NOT_TOUCH_HOSEI,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_3_0 - SCRN_NO_NOT_TOUCH_HOSEI,	//SELECT_SKILL_1
};

///�Z�I���p�l���������Ȃ��{�^���ɂ��鎞�̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonNotTouchScrnRect[] = {
	{3, 9, 0, 0xf},
	{3, 9, 0x10, 0x1f},
	{0xb, 0x11, 0, 0xf},
	{0xb, 0x11, 0x10, 0x1f},
};

//--------------------------------------------------------------
//	�|�P�����I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_A�v�A�j��0�A����
#define SCRN_NO_POKEMON_A_0		(0x8)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_A�v�A�j��1�A����
#define SCRN_NO_POKEMON_A_1		(0xc8)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_A�v�A�j��2�A����
#define SCRN_NO_POKEMON_A_2		(0x188)

///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_B�v�A�j��0�A����
#define SCRN_NO_POKEMON_B_0		(0xb)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_B�v�A�j��1�A����
#define SCRN_NO_POKEMON_B_1		(0xcb)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_B�v�A�j��2�A����
#define SCRN_NO_POKEMON_B_2		(0x18b)

///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_C�v�A�j��0�A����
#define SCRN_NO_POKEMON_C_0		(0xe)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_C�v�A�j��1�A����
#define SCRN_NO_POKEMON_C_1		(0xce)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_C�v�A�j��2�A����
#define SCRN_NO_POKEMON_C_2		(0x18e)

///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_D�v�A�j��0�A����
#define SCRN_NO_POKEMON_D_0		(0x5)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_D�v�A�j��1�A����
#define SCRN_NO_POKEMON_D_1		(0xc5)
///�X�N���[���ԍ��F�|�P�����I���uCLIENT_TYPE_D�v�A�j��2�A����
#define SCRN_NO_POKEMON_D_2		(0x185)

///�X�N���[���ԍ��F�|�P�����I���u�L�����Z���v�A�j��0�A����
#define SCRN_NO_POKEMON_CANCEL_0		(0x1d)
///�X�N���[���ԍ��F�|�P�����I���u�L�����Z���v�A�j��1�A����
#define SCRN_NO_POKEMON_CANCEL_1		(0xdd)
///�X�N���[���ԍ��F�|�P�����I���u�L�����Z���v�A�j��2�A����
#define SCRN_NO_POKEMON_CANCEL_2		(0x19d)

///�|�P�����I���p�l�������������̃{�^���A�j���p�X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 PokemonButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//A
		SCRN_NO_POKEMON_A_0 - SCRN_NO_POKEMON_A_0,
		SCRN_NO_POKEMON_A_1 - SCRN_NO_POKEMON_A_0,
		SCRN_NO_POKEMON_A_2 - SCRN_NO_POKEMON_A_0,
	},
	{//B
		SCRN_NO_POKEMON_B_0 - SCRN_NO_POKEMON_B_0,
		SCRN_NO_POKEMON_B_1 - SCRN_NO_POKEMON_B_0,
		SCRN_NO_POKEMON_B_2 - SCRN_NO_POKEMON_B_0,
	},
	{//C
		SCRN_NO_POKEMON_C_0 - SCRN_NO_POKEMON_C_0,
		SCRN_NO_POKEMON_C_1 - SCRN_NO_POKEMON_C_0,
		SCRN_NO_POKEMON_C_2 - SCRN_NO_POKEMON_C_0,
	},
	{//D
		SCRN_NO_POKEMON_D_0 - SCRN_NO_POKEMON_D_0,
		SCRN_NO_POKEMON_D_1 - SCRN_NO_POKEMON_D_0,
		SCRN_NO_POKEMON_D_2 - SCRN_NO_POKEMON_D_0,
	},
	{//CANCEL
		SCRN_NO_POKEMON_CANCEL_0 - SCRN_NO_POKEMON_CANCEL_0,
		SCRN_NO_POKEMON_CANCEL_1 - SCRN_NO_POKEMON_CANCEL_0,
		SCRN_NO_POKEMON_CANCEL_2 - SCRN_NO_POKEMON_CANCEL_0,
	},
};

///�|�P�����I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT PokemonButtonScrnRect[] = {
	{0xa, 0x11, 0, 0xe},
	{0, 9, 0x11, 0x1f},
	{0xa, 0x11, 0x11, 0x1f},
	{0, 9, 0, 0xe},
	{0x12, 0x17, 1, 0x1e},
};

///�|�P�����I���p�l���������Ȃ��p�l���ɂ��鎞�̃X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 PokemonButtonNotTouchScrnOffset[] = {
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_POKEMON_A_0 - SCRN_NO_NOT_TOUCH_HOSEI,		//A
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_POKEMON_B_0 - SCRN_NO_NOT_TOUCH_HOSEI,		//B
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_POKEMON_C_0 - SCRN_NO_NOT_TOUCH_HOSEI,		//C
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_POKEMON_D_0 - SCRN_NO_NOT_TOUCH_HOSEI,		//D
};

///�|�P�����I���p�l���������Ȃ��p�l���ɂ��鎞�̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT PokemonButtonNotTouchScrnRect[] = {
	{0xb, 0x11, 0, 0xe},
	{1, 9, 0x11, 0x1f},
	{0xb, 0x11, 0x11, 0x1f},
	{1, 9, 0, 0xe},
};

//--------------------------------------------------------------
//	�u�͂��E�������v�I��
//--------------------------------------------------------------
///�X�N���[���ԍ��F�͂��E�������I���u�������v�A�j��0�A����
#define SCRN_NO_NO_0		(0x246)
///�X�N���[���ԍ��F�͂��E�������I���u�������v�A�j��1�A����
#define SCRN_NO_NO_1		(0x24b)
///�X�N���[���ԍ��F�͂��E�������I���u�������v�A�j��2�A����
#define SCRN_NO_NO_2		(0x250)

///�X�N���[���ԍ��F�͂��E�������I���u�͂��v�A�j��0�A����
#define SCRN_NO_YES_0		(0x20)
///�X�N���[���ԍ��F�͂��E�������I���u�͂��v�A�j��1�A����
#define SCRN_NO_YES_1		(0xe0)
///�X�N���[���ԍ��F�͂��E�������I���u�͂��v�A�j��2�A����
#define SCRN_NO_YES_2		(0x1a0)

///�͂��E�������I���p�l�������������̃{�^���A�j���p�X�N���[���I�t�Z�b�g�l
ALIGN4 static const s16 YesNoButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//������
		SCRN_NO_NO_0 - SCRN_NO_NO_0,
		SCRN_NO_NO_1 - SCRN_NO_NO_0,
		SCRN_NO_NO_2 - SCRN_NO_NO_0,
	},
	{//�͂�
		SCRN_NO_YES_0 - SCRN_NO_YES_0,
		SCRN_NO_YES_1 - SCRN_NO_YES_0,
		SCRN_NO_YES_2 - SCRN_NO_YES_0,
	},
};

///�͂��E�������I���p�l�������������̃X�N���[���A�j�����������͈�
ALIGN4 static const REWRITE_SCRN_RECT YesNoButtonScrnRect[] = {
	{0xd, 0x14, 0, 0x1f},		//������
	{4, 0xb, 0, 0x1f},			//�͂�
};


//==============================================================================
//
//	�g�|�W�V����
//
//==============================================================================
///�R�}���h�I����ʂł̘g�̓o����W
static const POINT_S16 CommandWakuPos[] = {
	{0x10 * 8, 9 * 8 + 4},		//SELECT_FIGHT_COMMAND
	{0x5 * 8, 0x14 * 8 + 4},		//SELECT_ITEM_COMMAND
	{0x1b * 8, 0x14 * 8 + 4},		//SELECT_POKEMON_COMMAND
	{0x10 * 8, 0x15 * 8},		//SELECT_ESCAPE_COMMAND
};

///�Z�I����ʂł̘g�̓o����W
static const POINT_S16 WazaWakuPos[] = {
	{0x10 * 8, 9 * 8 + 4},		//SELECT_SKILL_1
	{0x5 * 8, 0x14 * 8},		//SELECT_SKILL_2
	{0x1b * 8, 0x14 * 8},		//SELECT_SKILL_3
	{0x10 * 8, 0x15 * 8},		//SELECT_SKILL_4
};

///�|�P�����I����ʂł̘g�̓o����W
static const POINT_S16 PokemonWakuPos[] = {
	{0x10 * 8, 9 * 8 + 4},		//A
	{0x5 * 8, 0x14 * 8},		//B
	{0x1b * 8, 0x14 * 8},		//C
	{0x10 * 8, 0x15 * 8},		//D
};


//==============================================================================
//
//	���̑��̃f�[�^
//
//==============================================================================
///�\��BG���̑I���o����|�P�����@TRUE�F�I���o����@FALSE�F�o���Ȃ�
ALIGN4 static const PokeSelectHitRange[][CLIENT_MAX] = {
	//CLIENT_TYPE_A, B, C, D�̏�
	{TRUE,	TRUE,	TRUE,	TRUE},		//POKESELE_A_B_C_D
	{FALSE,	TRUE,	FALSE,	TRUE},		//POKESELE_BD
	{FALSE,	TRUE,	TRUE,	TRUE},		//POKESELE_BCD
	{TRUE,	TRUE,	TRUE,	TRUE},		//POKESELE_ABCD
	{TRUE,	FALSE,	FALSE,	FALSE},		//POKESELE_A
	{TRUE,	FALSE,	TRUE,	FALSE},		//POKESELE_AC
	{FALSE,	FALSE,	TRUE,	FALSE},		//POKESELE_C
	{TRUE,	TRUE,	FALSE,	TRUE},		//POKESELE_ABD
	{FALSE,	TRUE,	TRUE,	TRUE},		//POKESELE_B_C_D
	{TRUE,	TRUE,	FALSE,	TRUE},		//POKESELE_A_B_D
	{TRUE,	FALSE,	TRUE,	FALSE},		//POKESELE_A_C
	{FALSE,	TRUE,	FALSE,	TRUE},		//POKESELE_B_D
};

///�g�^�C�v���̃L����ID�Ȃǂ̃e�[�u��
ALIGN4 static const u32 WakuTypeID[][3] = {	//char, cell, anm
	{
		BATTLE_W_WAKU1_NCGR_BIN,
		BATTLE_W_WAKU1_NCER_BIN,
		BATTLE_W_WAKU1_NANR_BIN,
	},
	{
		BATTLE_W_WAKU2_NCGR_BIN,
		BATTLE_W_WAKU2_NCER_BIN,
		BATTLE_W_WAKU2_NANR_BIN,
	},
	{
		BATTLE_W_WAKU3_NCGR_BIN,
		BATTLE_W_WAKU3_NCER_BIN,
		BATTLE_W_WAKU3_NANR_BIN,
	},
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
static void * BINPUT_WorkInit(void)
{
	BI_PARAM *bip;

	bip = sys_AllocMemory(HEAPID_BATTLE, sizeof(BI_PARAM));
	MI_CpuClear8(bip, sizeof(BI_PARAM));
	
	bip->makedata_no = MAKEDATA_NO_INIT;
	
	return bip;
}

//--------------------------------------------------------------
/**
 * @brief   BG�\����W���t���[���\���Őݒ肷��
 * @param   bgl		BGL�f�[�^
 */
//--------------------------------------------------------------
void BINPUT_DefaultFrameSet(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(BiBgCntDat); i++){
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S + i, &BiBgCntDat[i], GF_BGL_MODE_TEXT);
		//GF_BGL_ScrClear(bgl, GF_BGL_FRAME0_S + i);
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
void BINPUT_FrameExit(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(BiBgCntDat); i++){
		GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S + i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �퓬���͉�ʂ̃V�X�e����������
 * @param   bgl		BGL�f�[�^
 * @param   sex		����(�j���ʕǎ��̑I���ɕK�v)
 * @retval  Alloc�����퓬���͉�ʂ̃V�X�e�����[�N�̃|�C���^
 */
//--------------------------------------------------------------
void * BINPUT_SystemInit(BATTLE_WORK *bw, int sex)
{
	BI_PARAM *bip;
	PALETTE_FADE_PTR pfd;

	//���[�N�m��
	bip = BINPUT_WorkInit();
	bip->bw = bw;
	bip->sex = sex;

	pfd = BattleWorkPfdGet(bw);
	
	//�t���[���\���ݒ�	�����ł�邩�͔����H
//	BINPUT_DefaultFrameSet(bgl);

#if SUBFONT_OAM	//Sub_FontOamData�n�̃��b�Z�[�W���g�p����ꍇ�̏���
	{
		//OBJ�풓�p���b�g�]��
		CATS_LoadResourcePlttWorkArc(BattleWorkPfdGet(bip->bw), FADE_SUB_OBJ, csp, crp, 
			ARC_BATT_OBJ, BATTLE_WOBJ_NCLR, 0, 
			BASE_PLTT_NUM, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_INPUT_FONTOBJ_COMMON);

		Sub_FontOamDataInit(bip);
	}
#else
	//�t�H���gOAM�V�X�e���쐬
	bip->fontoam_sys = FONTOAM_SysInit(FA_NO_MAX, HEAPID_BATTLE);
#endif

	//�풓�t�F�[�h�^�X�N����
	bip->def_fade_tcb = TCB_Add(DefaultFadeAnimeTask, bip, TCBPRI_BINPUT_DEF_COLOR_EFFECT);
	
	//�X�N���[���S�ǂݍ���
	{
		NNSG2dScreenData *scrnData;
		void *arc_data;
		int i;
		
		for(i = 0; i < SCRNBUF_MAX; i++){
			//�X�N���[���o�b�t�@�m��
			bip->scrn_buf[i] = sys_AllocMemory(HEAPID_BATTLE, 0x800);

			//�X�N���[���ǂݍ���
			arc_data = ArcUtil_ScrnDataGet(ARC_BATT_BG, ScrnArcDataNo[i], 1, 
				&scrnData, HEAPID_BATTLE);
			MI_CpuCopy32(scrnData->rawData, bip->scrn_buf[i], 0x800);
			sys_FreeMemoryEz(arc_data);
		}
	}

	//�p���b�g�ǂݍ���
	{
		u16 *def_wk;

		bip->pal_buf = sys_AllocMemory(HEAPID_BATTLE, 0x200);
		PaletteWorkSet_Arc(pfd, ARC_BATT_BG, BATTLE_W_NCLR, HEAPID_BATTLE, 
			FADE_SUB_BG, 0, 0);
		def_wk = PaletteWorkDefaultWorkGet(pfd, FADE_SUB_BG);
		MI_CpuCopy16(def_wk, bip->pal_buf, 0x200);
	}
	
	//MEMORY_DECORD_WORK������
	{
		int i, client;
		for(client = 0; client < CLIENT_MAX; client++){
			MI_CpuFill8(&bip->memory_decord[client].wazapara, 0xff, sizeof(BINPUT_WAZA_PARAM));
		}
	}
	
	//�Z�^�C�v�A�C�R���p�W�J�������m��
	{
		int i, client;
		for(client = 0; client < CLIENT_MAX; client++){
			for(i = 0; i < WAZA_TEMOTI_MAX; i++){
				bip->memory_decord[client].typeicon_cgx[i] = sys_AllocMemory(HEAPID_BATTLE, 
					APP_OamTypeToSize(WAZATYPEICON_OAMTYPE));
			}
		}
	}
	
	//�w�i�p���b�g
	{
		NNSG2dPaletteData *pal_data;
		void *arc_data;
	
		bip->background_pal_normal = sys_AllocMemory(HEAPID_BATTLE, 0x20);
		bip->background_pal_touch = sys_AllocMemory(HEAPID_BATTLE, 0x20);
		MI_CpuCopy16(bip->pal_buf, bip->background_pal_normal, 0x20);

		arc_data = ArcUtil_PalDataGet(ARC_BATT_BG, BATTLE_W_ANI_NCLR, &pal_data, HEAPID_BATTLE);
		MI_CpuCopy16(pal_data->pRawData, bip->background_pal_touch, 0x20);
		sys_FreeMemoryEz(arc_data);
		
		MsgPrintBattleSkipPushFlagClear();
		MsgPrintBattleWaitPushFlagClear();
		bip->background_tcb = TCB_Add(BackGroundTouchPaletteCheck, bip, TCBPRI_BACKGROUND_PAL);
	}

	return bip;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬���͉�ʂ̃V�X�e�����������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_SystemFree(BI_PARAM_PTR bip)
{
	int i;
	
	Sub_SceneOBJDelete(bip);
	BINPUT_StockBallActorResourceFree(bip);
	
	BINPUT_DefaultDataFree(bip);
	
#if SUBFONT_OAM
//	Sub_FontOamDataExit(bip);
#endif
	FONTOAM_SysDelete(bip->fontoam_sys);
	
	TCB_Delete(bip->def_fade_tcb);
	
	for(i = 0; i < SCRNBUF_MAX; i++){
		sys_FreeMemoryEz(bip->scrn_buf[i]);
	}
	sys_FreeMemoryEz(bip->pal_buf);
	
	MemoryDecordWorkFree(bip);
	
	sys_FreeMemoryEz(bip->background_pal_normal);
	sys_FreeMemoryEz(bip->background_pal_touch);
	TCB_Delete(bip->background_tcb);
	
	sys_FreeMemoryEz(bip);
}

//--------------------------------------------------------------
/**
 * @brief   �풓�L�����̓W�J�Ȃǂ��s��
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_DefaultDataSet(BI_PARAM_PTR bip)
{
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	int i;
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	pfd = BattleWorkPfdGet(bip->bw);

	//�L�����f�[�^VRAM�]��
	{
		ArcUtil_BgCharSet(ARC_BATT_BG, BATTLE_W_NCGR_BIN, bgl, GF_BGL_FRAME0_S, 
			0, 0x6000, 1, HEAPID_BATTLE);
	}

	//�Z�^�C�v�A�C�R��
	WazaTypeIcon_CellAnmResourceLoad(csp, crp, CELLID_WAZATYPE_ICON, CELLANMID_WAZATYPE_ICON);
	WazaTypeIcon_PlttWorkResourceLoad(BattleWorkPfdGet(bip->bw), FADE_SUB_OBJ, csp, crp, 
		NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_WAZATYPE_ICON);
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		WazaTypeIcon_CharResourceLoad(csp, crp, NNS_G2D_VRAM_TYPE_2DSUB, 
			NORMAL_TYPE, CHARID_WAZATYPE_ICON_1 + i);
	}

	//�ߊl�f���p�w�J�[�\��
	if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_GET_DEMO){
		FINGER_ResourceLoad(csp, crp, pfd, CHARID_FINGER_CURSOR, PLTTID_FINGER_CURSOR,
			CELLID_FINGER_CURSOR, CELLANMID_FINGER_CURSOR);
		bip->demo.finger = FINGER_ActorCreate(csp, crp, HEAPID_BATTLE,
			CHARID_FINGER_CURSOR, PLTTID_FINGER_CURSOR, CELLID_FINGER_CURSOR, 
			CELLANMID_FINGER_CURSOR, FINGER_SOFTPRI, FINGER_BGPRI);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �풓�L�����̔j��
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_DefaultDataFree(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	//-- �Z�^�C�v�A�C�R�� --//
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		WazaTypeIcon_CharResourceFree(crp, CHARID_WAZATYPE_ICON_1 + i);
	}
	WazaTypeIcon_PlttResourceFree(crp, PLTTID_WAZATYPE_ICON);
	WazaTypeIcon_CellAnmResourceFree(crp, CELLID_WAZATYPE_ICON, CELLANMID_WAZATYPE_ICON);

	//�ߊl�f���p�w�J�[�\��
	if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_GET_DEMO){
		FINGER_ActorDelete(bip->demo.finger);
		FINGER_ResourceFree(crp, 
			CHARID_FINGER_CURSOR, PLTTID_FINGER_CURSOR, 
			CELLID_FINGER_CURSOR, CELLANMID_FINGER_CURSOR);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w��^�C�v��BG��ʂ��`������
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 * @param   work			�V�[�����ɈقȂ�K�v�ȃf�[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_CreateBG(BI_PARAM_PTR bip, int select_bg, int force_put, void *scene_work)
{
	const BG_MAKE_DATA *bmd, *old_bmd;
	int i;
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	if(scene_work != NULL){
		MI_CpuCopy8(scene_work, &bip->scene, sizeof(SCENE_WORK));
	}
	bip->touch_invalid = FALSE;
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	if(bip->makedata_no == MAKEDATA_NO_INIT){
		force_put = TRUE;
		old_bmd = NULL;
	}
	else{
		old_bmd = &BgMakeData[bip->makedata_no];
	}
	bmd = &BgMakeData[select_bg];

	//�w�i�ȊO�͑S�Ĕ�\��
//	Sub_BackScrnOnlyVisible();
	
	//CGR
#if 1
	if(0){	//�L�����f�[�^�͏�������鎖���Ȃ��̂ŉ������Ȃ�
#else
	if(bmd->cgr_id != NONE_ID && (force_put == TRUE || bmd->cgr_id != old_bmd->cgr_id)){
#endif
		ArcUtil_BgCharSet(ARC_BATT_BG, bmd->cgr_id, bgl, GF_BGL_FRAME0_S, 
			0, BI_BG_CGR_SIZE, 1, HEAPID_BATTLE);
		if(bip->sex == PM_MALE){
			ArcUtil_BgCharSet(ARC_BATT_BG, BATTLE_W_BOY_NCGR_BIN, bgl, GF_BGL_FRAME0_S,
				BG_PLAYER_WALL_OFFSET, BG_PLAYER_WALL_SIZE, 1, HEAPID_BATTLE);
		}
		else{
			ArcUtil_BgCharSet(ARC_BATT_BG, BATTLE_W_GIRL_NCGR_BIN, bgl, GF_BGL_FRAME0_S,
				BG_PLAYER_WALL_OFFSET, BG_PLAYER_WALL_SIZE, 1, HEAPID_BATTLE);
		}
	}
	//PALETTE
#if 1
	if(1){
#else
	if(bmd->pal_id != NONE_ID && (force_put == TRUE || bmd->pal_id != old_bmd->pal_id)){
#endif
		PaletteWorkSet(BattleWorkPfdGet(bip->bw), bip->pal_buf, FADE_SUB_BG, 0, 0x200);
	}
	//SCREEN
	for(i = 0; i < BI_BG_NUM; i++){
		if(bmd->scr_id[i] != NONE_ID 
				&& (force_put == TRUE || bmd->scr_id[i] != old_bmd->scr_id[i])){
			GF_BGL_ScreenBufSet(bgl, GF_BGL_FRAME0_S + i, bip->scrn_buf[bmd->scr_id[i]], 0x800);
			GF_BGL_LoadScreenV_Req(bgl, GF_BGL_FRAME0_S + i);
		}
	}
	
	//OBJ�p���b�g�]��
	//��check �ŏ���1�񂾂��̓o�^�����A�Ƃ肠���������� 2006.05.09(��)
	CATS_LoadResourcePlttWorkArc(BattleWorkPfdGet(bip->bw), FADE_SUB_OBJ, csp, crp, 
		ARC_BATT_OBJ, BATTLE_WOBJ_NCLR, 0, 
		BASE_PLTT_NUM, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_INPUT_COMMON);

	bip->makedata_no = select_bg;

	//�u�����h�ݒ�
	G2S_SetBlendAlpha(BLD_PLANE_1, BLD_PLANE_2, BLD_ALPHA_1, BLD_ALPHA_2);

	Sub_SceneOBJDelete(bip);
	//�R�[���o�b�N�֐��Ăяo��
	if(bmd->callback_bg != NULL){
		bmd->callback_bg(bip, select_bg, force_put);
	}

	VWaitTCB_Add(VWait_FrameVisibleUpdate, bip, VWAIT_TCBPRI_FRAMEVISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   �莝���{�[���Ŏg�p���郊�\�[�X�̃��[�h�ƃA�N�^�[�̐���
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 *
 * ���̊֐��ŃA�N�^�[������A�A�N�^�[�͕\��OFF�̏�ԂɂȂ��Ă��܂��B
 */
//--------------------------------------------------------------
void BINPUT_StockBallActorResourceLoad(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	GF_ASSERT(bip->stock_mine_cap[0] == NULL && bip->stock_enemy_cap[0] == NULL);
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	//-- ���\�[�X�ǂݍ��� --//
	//�p���b�g�@�t�H���gOBJ�Ƌ���(���͉�ʂ�1�̃t�@�C���ɑS�������Ă�)�̂ł����ł͂��Ȃ��Ă�����
//	CATS_LoadResourcePlttArc(csp, crp, ARC_BATT_OBJ, BATTLE_WOBJ_NCLR, 0, 
//		1, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_INPUT_FONTOBJ_COMMON);

	//���@��
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, BATTLE_STOCK_M_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_STOCK_MINE);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, BATTLE_STOCK_M_NCER_BIN, 1, 
		CELLID_STOCK_MINE);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		BATTLE_STOCK_M_NANR_BIN, 1, CELLANMID_STOCK_MINE);

	//�G��
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, BATTLE_STOCK_E_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_STOCK_ENEMY);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, BATTLE_STOCK_E_NCER_BIN, 1, 
		CELLID_STOCK_ENEMY);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		BATTLE_STOCK_E_NANR_BIN, 1, CELLANMID_STOCK_ENEMY);
	

	//-- �A�N�^�[���� --//
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		bip->stock_mine_cap[i] = CATS_ObjectAdd_S(csp, crp, &StockObjParam_Mine);
		CATS_ObjectPosSet_SubSurface(bip->stock_mine_cap[i]->act, 
			STOCK_MINE_BASE_POS_X + STOCK_MINE_BASE_SPACE_X * i, STOCK_MINE_BASE_POS_Y,
			BATTLE_SUB_ACTOR_DISTANCE);
		CATS_ObjectAffineSetCap(bip->stock_mine_cap[i], CLACT_AFFINE_NORMAL);
		
		bip->stock_enemy_cap[i] = CATS_ObjectAdd_S(csp, crp, &StockObjParam_Enemy);
		CATS_ObjectPosSet_SubSurface(bip->stock_enemy_cap[i]->act, 
			STOCK_ENEMY_BASE_POS_X + STOCK_ENEMY_BASE_SPACE_X * i, STOCK_ENEMY_BASE_POS_Y,
			BATTLE_SUB_ACTOR_DISTANCE);
	}
	
	BINPUT_StockBallOFF(bip);
	
	GF_ASSERT(bip->ball_tcb == NULL);
	bip->ball_tcb = TCB_Add(StockBallMain, bip, TCBPRI_BINPUT_EFFECT);
	
	
	//-- ���łɂ����Ő퓬�J�[�\�������� --//
	{
		PALETTE_FADE_PTR pfd;
		pfd = BattleWorkPfdGet(bip->bw);
		BCURSOR_ResourceLoad(csp, crp, pfd, CHARID_BATTLE_CURSOR, PLTTID_BATTLE_CURSOR,
			CELLID_BATTLE_CURSOR, CELLANMID_BATTLE_CURSOR);
		bip->cursor = BCURSOR_ActorCreate(csp, crp, HEAPID_BATTLE, CHARID_BATTLE_CURSOR, 
			PLTTID_BATTLE_CURSOR, CELLID_BATTLE_CURSOR, CELLANMID_BATTLE_CURSOR, 
			SOFTPRI_CURSOR, BGPRI_CURSOR);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���{�[���̃��\�[�X�ƃA�N�^�[�����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BINPUT_StockBallActorResourceFree(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	GF_ASSERT(bip->stock_mine_cap[0] != NULL && bip->stock_enemy_cap[0] != NULL);
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	//-- ���\�[�X��� --//
	CATS_FreeResourceChar(crp, CHARID_STOCK_MINE);
	CATS_FreeResourceCell(crp, CELLID_STOCK_MINE);
	CATS_FreeResourceCellAnm(crp, CELLANMID_STOCK_MINE);

	CATS_FreeResourceChar(crp, CHARID_STOCK_ENEMY);
	CATS_FreeResourceCell(crp, CELLID_STOCK_ENEMY);
	CATS_FreeResourceCellAnm(crp, CELLANMID_STOCK_ENEMY);

	//���ʃp���b�g���ꉞ�����ō폜
	CATS_FreeResourcePltt(crp, PLTTID_INPUT_COMMON);
	
	//-- �A�N�^�[�폜 --//
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		CATS_ActorPointerDelete_S(bip->stock_mine_cap[i]);
		bip->stock_mine_cap[i] = NULL;
		CATS_ActorPointerDelete_S(bip->stock_enemy_cap[i]);
		bip->stock_enemy_cap[i] = NULL;
	}
	
	TCB_Delete(bip->ball_tcb);
	bip->ball_tcb = NULL;

	//-- �퓬�J�[�\�� --//
	BCURSOR_ResourceFree(crp, CHARID_BATTLE_CURSOR, PLTTID_BATTLE_CURSOR,
		CELLID_BATTLE_CURSOR, CELLANMID_BATTLE_CURSOR);
	BCURSOR_ActorDelete(bip->cursor);
}

//--------------------------------------------------------------
/**
 * @brief   �莝�����C�A�j���F���C���^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void StockBallMain(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	int i;
	MOTIVATION_WORK *mw;
	enum{
		SEQ_INIT,		//������
		SEQ_WAIT,		//�E�F�C�g
		SEQ_FIRST,		//�s��
		SEQ_BACK,		//�߂�
		SEQ_RET,		//���̈ʒu��
	};
	
#if 0	//SEQ_INIT�̃A�N�^�[�\���A��\���Ŕ��肷��悤�ɕύX 2006.07.13(��)
		//�łȂ��Ɠr������̂܂܎���ʂōĊJ���Ă��܂�
	switch(bip->makedata_no){
	case BINPUT_COMMAND_IN:
	case BINPUT_COMMAND_IN_2:
	case BINPUT_TYPE_A:
	case BINPUT_TYPE_A_2:
		break;
	default:
		return;
	}
#endif
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		mw = &bip->motivation_work[i];
		switch(mw->seq){
		case SEQ_INIT:
		default:
			if(CATS_ObjectEnableGet(bip->stock_mine_cap[i]->act) == CATS_ENABLE_FALSE){
				break;
			}
		#if 0
			if(mw->motivation >= MOTIVATION_ANM_HIGH){
				mw->anm_type = MOTIVATION_ANM_TYPE_HIGH;
				mw->wait = MOTIVATION_WAIT_HIGH;
			}
			else if(mw->motivation >= MOTIVATION_ANM_MIDDLE){
				mw->anm_type = MOTIVATION_ANM_TYPE_MIDDLE;
				mw->wait = MOTIVATION_WAIT_MIDDLE;
			}
			else if(mw->motivation >= MOTIVATION_ANM_LOW){
				mw->anm_type = MOTIVATION_ANM_TYPE_LOW;
				mw->wait = MOTIVATION_WAIT_LOW;
			}
		#else
			if(mw->motivation >= MOTIVATION_ANM_MIDDLE){
				mw->anm_type = MOTIVATION_ANM_TYPE_HIGH;
				mw->wait = MOTIVATION_WAIT_HIGH;
			}
		#endif
			else{
				break;
			}
			mw->wait += gf_rand() % MOTIVATION_ANM_WAIT_RANDOM;
			mw->count_max = MOTIVATION_ANM_FRAME;
			mw->seq++;
			break;
		case SEQ_WAIT:
			if(mw->wait > 0){
				mw->wait--;
				break;
			}
			mw->seq++;
			break;
		case SEQ_FIRST:
		case SEQ_RET:
			CATS_ObjectRotationAddCap(bip->stock_mine_cap[i], MOTIVATION_ADD_ROTATION);

			mw->x_offset += MOTIVATION_ADD_X;
			CATS_ObjectPosSetCap_SubSurface(bip->stock_mine_cap[i],
				STOCK_MINE_BASE_POS_X + STOCK_MINE_BASE_SPACE_X * i + mw->x_offset / 0x100, 
				STOCK_MINE_BASE_POS_Y, BATTLE_SUB_ACTOR_DISTANCE);
			
			mw->count++;
			if(mw->count >= mw->count_max){
				mw->count = 0;
				if(mw->seq == SEQ_FIRST){
					mw->seq++;
				}
				else{
					CATS_ObjectRotationSetCap(bip->stock_mine_cap[i], 0);
					CATS_ObjectPosSetCap_SubSurface(bip->stock_mine_cap[i],
						STOCK_MINE_BASE_POS_X + STOCK_MINE_BASE_SPACE_X * i, 
						STOCK_MINE_BASE_POS_Y, BATTLE_SUB_ACTOR_DISTANCE);
					mw->x_offset = 0;
					
					if(mw->loop < MOTIVATION_ANM_LOOP){
						mw->loop++;
						if(mw->count_max > 1){
							mw->count_max--;
						}
						mw->seq = SEQ_FIRST;
					}
					else{
						mw->loop = 0;
						mw->seq = SEQ_INIT;
					}
				}
			}
			break;
		case SEQ_BACK:
			CATS_ObjectRotationAddCap(bip->stock_mine_cap[i], -MOTIVATION_ADD_ROTATION);

			mw->x_offset -= MOTIVATION_ADD_X;
			CATS_ObjectPosSetCap_SubSurface(bip->stock_mine_cap[i],
				STOCK_MINE_BASE_POS_X + STOCK_MINE_BASE_SPACE_X * i + mw->x_offset / 0x100, 
				STOCK_MINE_BASE_POS_Y, BATTLE_SUB_ACTOR_DISTANCE);
			
			mw->count++;
			if(mw->count >= mw->count_max * 2){
				mw->count = 0;
				mw->seq++;
			}
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���|�P�����̃��`�x�[�V�����p�����[�^���Z�b�g����
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   motivation		�莝�����̃��`�x�[�V�������������z��ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_TemotiMotivationParamSet(BI_PARAM_PTR bip, const u8 *motivation)
{
	int i;
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		bip->motivation_work[i].motivation = motivation[i];
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���{�[���̃A�j�����ŐV�̏���������čX�V����
 *
 * @param   bip					BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   stock_mine[]		���@���̎莝���{�[�����
 * @param   stock_enemy[]		�G���̎莝���{�[�����
 */
//--------------------------------------------------------------
void BINPUT_StockBallAnimeUpdate(BI_PARAM_PTR bip, u8 stock_mine[], u8 stock_enemy[])
{
	int i, anm_seq;

	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		//���@
		anm_seq = Sub_StockBallAnmSeqGet(stock_mine[i]);
		CLACT_AnmChg(bip->stock_mine_cap[i]->act, anm_seq);
		CATS_ObjectUpdate(bip->stock_mine_cap[i]->act);
		//�G
		anm_seq = Sub_StockBallAnmSeqGet(stock_enemy[i]);
		CLACT_AnmChg(bip->stock_enemy_cap[i]->act, anm_seq);
		CATS_ObjectUpdate(bip->stock_enemy_cap[i]->act);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���{�[����\������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_StockBallON(BI_PARAM_PTR bip)
{
	int i;

	GF_ASSERT(bip->stock_mine_cap[0] != NULL && bip->stock_enemy_cap[0] != NULL);
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		CATS_ObjectEnable(bip->stock_mine_cap[i]->act, CATS_ENABLE_TRUE);
	}
	
	if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_TRAINER){
		for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
			CATS_ObjectEnable(bip->stock_enemy_cap[i]->act, CATS_ENABLE_TRUE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �莝���{�[���̕\��������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_StockBallOFF(BI_PARAM_PTR bip)
{
	int i;

	GF_ASSERT(bip->stock_mine_cap[0] != NULL && bip->stock_enemy_cap[0] != NULL);
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		CATS_ObjectEnable(bip->stock_mine_cap[i]->act, CATS_ENABLE_FALSE);
		CATS_ObjectEnable(bip->stock_enemy_cap[i]->act, CATS_ENABLE_FALSE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l����Ԃ𒲂ׂ�
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
int BINPUT_TouchCheck(BI_PARAM_PTR bip)
{
	int tp_ret, hit, ret, panel_pal;
	const BG_MAKE_DATA *bmd;
	int cursor_check = 0;
	
	GF_ASSERT(bip->makedata_no != MAKEDATA_NO_INIT);
	
	bmd = &BgMakeData[bip->makedata_no];
	if(bmd->tpd == NULL || bip->touch_invalid == TRUE){
		return RECT_HIT_NONE;
	}
	
	GF_ASSERT(bmd->tpd_ret != NULL);
	
	//�ߊl�f���`�F�b�N
	if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_GET_DEMO){
		hit = CaptureDemo_Main(bip);
	}
	else{	//�ʏ폈��
		hit = GF_TP_RectHitTrg(bmd->tpd);
		if(hit == RECT_HIT_NONE){
			hit = CursorCheck(bip);
			cursor_check++;
		}
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
		tp_ret = bmd->callback_tp(bip, tp_ret, panel_pal);
		if(tp_ret != RECT_HIT_NONE){
			if(bmd->cursor_save_func != NULL){
				bmd->cursor_save_func(bip, hit);
			}
			MI_CpuClear8(&bip->cursor_move, sizeof(CURSOR_MOVE));
			BCURSOR_OFF(bip->cursor);
			if(cursor_check > 0){
				bip->decend_key = TRUE;
			}
			else{
				bip->decend_key = FALSE;
			}
		}
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���I�����Ă��邩�`�F�b�N
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I�����Ă���B�@FALSE:�I�����Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL BINPUT_EffectEndCheck(BI_PARAM_PTR bip)
{
	if(bip->effect_tcb == NULL && bip->color_eff_tcb == NULL && bip->waku.cap == NULL
			&& BINPUT_BackFadeExeCheck(bip) == TRUE){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʔ͈͂���\������BG�^�C�v���擾����
 * @param   range		�Z���ʔ͈�
 * @param   client_type	�N���C�A���g�^�C�v
 * @retval  BG�^�C�v(POKESELE_???)
 */
//--------------------------------------------------------------
int BINPUT_RangeBgTypeGet(int range, int client_type)
{
	switch(range){
	case RANGE_NORMAL:
		return (client_type == CLIENT_TYPE_C) ? POKESELE_A_B_D : POKESELE_B_C_D;
	case RANGE_NONE:
	case RANGE_RANDOM:
	case RANGE_MINE:
		return (client_type == CLIENT_TYPE_C) ? POKESELE_C : POKESELE_A;
	case RANGE_DOUBLE:
	case RANGE_MAKIBISHI:
		return POKESELE_BD;
	case RANGE_TRIPLE:
		return (client_type == CLIENT_TYPE_C) ? POKESELE_ABD : POKESELE_BCD;
	case RANGE_TEDASUKE:
		return (client_type == CLIENT_TYPE_C) ? POKESELE_A : POKESELE_C;
	case RANGE_FIELD:
		return POKESELE_ABCD;
	case RANGE_TUBOWOTUKU:
		return POKESELE_A_C;
	case RANGE_MINE_DOUBLE:
		return POKESELE_AC;
	case RANGE_SAKIDORI:
		return POKESELE_B_D;
	default:
		GF_ASSERT(0 && "���݂��Ȃ������W�^�C�v�ł�");
		return POKESELE_A_B_C_D;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ǎ��̃X�N���[�����WX��ݒ肷��
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   x		���WX(����)
 */
//--------------------------------------------------------------
void BINPUT_PlayerBG_SetX(BI_PARAM_PTR bip, int x)
{
	GF_BGL_INI *bgl;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);

	bip->wall_x = x * 0x100;
	GF_BGL_ScrollSet(bgl, BI_FRAME_BACK, GF_BGL_SCROLL_X_SET, x);
	BINPUT_PlayerBG_MaskWindow(bip);
}

//--------------------------------------------------------------
/**
 * @brief   ���݂̕ǎ��̈ʒu�ɂ���ăE�B���h�E�̃}�X�N������������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BINPUT_PlayerBG_MaskWindow(BI_PARAM_PTR bip)
{
	int x1;
	
	GXS_SetVisibleWnd(GX_WNDMASK_W0);
	G2S_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
		| GX_WND_PLANEMASK_BG3| GX_WND_PLANEMASK_OBJ, TRUE);
	
	G2S_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1
		| GX_WND_PLANEMASK_BG3| GX_WND_PLANEMASK_OBJ, TRUE);
	
	x1 = 255 - (bip->wall_x / 0x100);
	if(x1 < 0){
		x1 = 0;
	}
	G2S_SetWnd0Position(x1, 0, 255, 192);
}

//--------------------------------------------------------------
/**
 * @brief   �ǎ����X�N���[��������
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   sp_x		�X�N���[�����x(����8�r�b�g����)
 * @param   end_x		�X�N���[����~���WX(����)
 */
//--------------------------------------------------------------
void BINPUT_PlayerBG_ScrollX(BI_PARAM_PTR bip, int sp_x, int end_x)
{
	if(bip->wall_x == end_x * 0x100){
		return;		//���ɒ�~���W�ɓ��B���Ă���
	}
	
	bip->wall_sp_x = sp_x;
	bip->wall_end_x = end_x << 8;
	TCB_Add(PlayerBGScrollX, bip, TCBPRI_BINPUT_PLAYER_SCROLL_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �ǎ��X�N���[���^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void PlayerBGScrollX(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	int end = FALSE;
	GF_BGL_INI *bgl;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	bip->wall_x += bip->wall_sp_x;
	if((bip->wall_sp_x <= 0 && bip->wall_x <= bip->wall_end_x) ||
			(bip->wall_sp_x > 0 && bip->wall_x >= bip->wall_end_x)){
		bip->wall_x = bip->wall_end_x;
		end = TRUE;
	}
	GF_BGL_ScrollSet(bgl, BI_FRAME_BACK, GF_BGL_SCROLL_X_SET, bip->wall_x / 0x100);
	BINPUT_PlayerBG_MaskWindow(bip);
	
	if(end == TRUE){
		GF_BGL_ScrClearCode(bgl, BI_FRAME_EFF, BG_CLEAR_CODE);	//�G�t�F�N�g�ʃN���A
		GF_BGL_VisibleSet(BI_FRAME_EFF, VISIBLE_OFF);
		GF_BGL_PrioritySet(BI_FRAME_EFF, 0);
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�g�ʂɑ΂��ĕǎ��̊G��ݒ肷��
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 *
 * �w�i�̎�l���O���t�B�b�N�X�N���[�����́A�}�X�N���ꂽ�����̔w�i�͗l�`��p�ł��B
 */
//--------------------------------------------------------------
void BINPUT_EffBGWallSet(BI_PARAM_PTR bip)
{
	GF_BGL_INI *bgl;

	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	GF_BGL_ScrollSet(bgl, BI_FRAME_EFF, GF_BGL_SCROLL_X_SET, 0);
	GF_BGL_ScrollSet(bgl, BI_FRAME_EFF, GF_BGL_SCROLL_Y_SET, 0);

//	ArcUtil_ScrnSet(ARC_BATT_BG, BATTLE_WBG0B_NSCR_BIN, bgl, BI_FRAME_EFF, 0, 0, 1, HEAPID_BATTLE);
//	GF_BGL_VisibleSet(BI_FRAME_EFF, VISIBLE_ON);
	GF_BGL_PrioritySet(BI_FRAME_EFF, 3);
}


//==============================================================================
//
//	BG�쐬���ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �X���C�h�G�t�F�N�g�Z�b�g
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   client_type		�N���C�A���g�^�C�v
 */
//--------------------------------------------------------------
static void BG_SlideSetInit(BI_PARAM_PTR bip, int client_type)
{
	BOOL ret;
	COMMAND_IN_EFF_WORK *ciew;

	//�^�b�`�p�l������
	bip->touch_invalid = TRUE;
	
	//�E�B���h�E�}�X�N�ݒ�
	G2S_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2
		| GX_WND_PLANEMASK_BG3, TRUE);
	
	G2S_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, TRUE);	//�㑤
	G2S_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, TRUE);	//����
	
	G2S_SetWnd0Position(COMMANDIN_WND_START_X0, COMMANDIN_WND_START_Y0, 
		COMMANDIN_WND_END_X0, COMMANDIN_WND_END_Y0);
	G2S_SetWnd1Position(COMMANDIN_WND_START_X1, COMMANDIN_WND_START_Y1, 
		COMMANDIN_WND_END_X1, COMMANDIN_WND_END_Y1);
	
	GXS_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);
	
	ciew = sys_AllocMemory(HEAPID_BATTLE, sizeof(COMMAND_IN_EFF_WORK));
	MI_CpuClear8(ciew, sizeof(COMMAND_IN_EFF_WORK));
	ciew->bip = bip;
	ciew->client_type = client_type;
	ciew->x0_l = -COMMANDIN_SCR_X0_START;
	ciew->y1_d = COMMANDIN_SCR_Y1_START;
	ciew->set_x0_l = (COMMANDIN_SCR_X0_START - ciew->x0_l) / 100;
	ciew->set_y1_d = (COMMANDIN_SCR_Y1_START - ciew->y1_d) / 100;
	
	Snd_SePlay(SEQ_SE_DP_SLIDEIN);
	TCB_Add(CommandInEffTask, ciew, TCBPRI_BINPUT_COMMAND_IN_EFFECT);

	//H�u�����N�֐��ݒ�
	ret = sys_HBlankIntrSet(HBlank_CommandInEff, ciew);
	GF_ASSERT(ret == TRUE);	//H�u�����N�֐��Z�b�g���s
	//V�u�����N�^�X�N����
	ciew->vtask_tcb = VIntrTCB_Add(VBlankTCB_CommandInEff, ciew, 10);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_COMMAND_IN��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_CommandIn(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	int client_type;
	
	client_type = bip->scene.bsc.client_type;
	
	//��ʍ\�z
	BGCallback_CommandSelect(bip, select_bg, force_put);
	//�X���C�h�G�t�F�N�g�Z�b�g
	BG_SlideSetInit(bip, client_type);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_A��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_CommandSelect(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	STRBUF *fight_src, *item_src, *pokemon_src, *escape_src;
	MSGDATA_MANAGER *msg_man;
	int client_type;
	BINPUT_SCENE_COMMAND *bsc;
	
	bsc = &bip->scene.bsc;
	client_type = bsc->client_type;
	msg_man = BattleWorkFightMsgGet(bip->bw);
	
	bip->client_type = client_type;
	
	if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_SAFARI){
		fight_src = MSGMAN_AllocString(msg_man, SafariCommnadBallMsg);
		item_src = MSGMAN_AllocString(msg_man, SafariCommnadEsaMsg);
		pokemon_src = MSGMAN_AllocString(msg_man, SafariCommnadDoroMsg);
	}
	else if(BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_POKE_PARK){
		fight_src = MSGMAN_AllocString(msg_man, ParkCommnadBallMsg);
		item_src = MSGMAN_AllocString(msg_man, SafariCommnadEsaMsg);
		pokemon_src = MSGMAN_AllocString(msg_man, SafariCommnadDoroMsg);
	}
	else{
		fight_src = MSGMAN_AllocString(msg_man, CommandFightMsg);
		item_src = MSGMAN_AllocString(msg_man, CommandBagMsg);
		pokemon_src = MSGMAN_AllocString(msg_man, CommandPokemonMsg);
	}

//	if(*client_type == CLIENT_TYPE_C && (BattleWorkFightTypeGet(bip->bw) & FIGHT_TYPE_MULTI) == 0){
	if(BattleWorkEscCanCheck(bip->bw, BattleWorkClientNoGet(bip->bw, client_type)) == TRUE){
		escape_src = MSGMAN_AllocString(msg_man, CommandModoruMsg);
		bip->command_modoru_type = TRUE;
	}
	else{
		escape_src = MSGMAN_AllocString(msg_man, CommandEscapeMsg);
		bip->command_modoru_type = FALSE;
	}
	
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_FIGHT], fight_src, 
		FONT_BUTTON, MSGCOLOR_FIGHT, PALOFS_FIGHT, PLTTID_INPUT_FIGHT, 
		FA_POS_FIGHT_X, FA_POS_FIGHT_Y, FONTOAM_CENTER, NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ITEM], item_src, FONT_BUTTON, 
		MSGCOLOR_ITEM, PALOFS_ITEM,
		PLTTID_INPUT_ITEM, FA_POS_ITEM_X, FA_POS_ITEM_Y, FONTOAM_CENTER, NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_POKEMON], pokemon_src, FONT_BUTTON, 
		MSGCOLOR_POKEMON, PALOFS_POKEMON,
		PLTTID_INPUT_POKEMON, FA_POS_POKEMON_X, FA_POS_POKEMON_Y, FONTOAM_CENTER, NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE], escape_src, FONT_BUTTON, 
		MSGCOLOR_ESCAPE, PALOFS_ESCAPE,
		PLTTID_INPUT_ESCAPE, FA_POS_ESCAPE_X, FA_POS_ESCAPE_Y, FONTOAM_CENTER, NULL);

	STRBUF_Delete(fight_src);
	STRBUF_Delete(item_src);
	STRBUF_Delete(pokemon_src);
	STRBUF_Delete(escape_src);

	//�|�P�����A�C�R��
	if((BattleWorkFightTypeGet(bip->bw) & (FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)) == 0){
		POKEMON_PARAM *pp;
		CATS_ACT_PTR cap;
		int x, y;
		
		//���\�[�X���[�h���A�N�^�[����
		pp = BattleWorkPokemonParamGet(bip->bw, bsc->client_no, bsc->sel_mons_no);
		Sub_PokeIconResourceLoad(bip);
		cap = Sub_PokeIconCharActorSet(bip, pp, client_type, 
			bsc->icon_hp, bsc->icon_hpmax, bsc->icon_status);

		//���W�ݒ�
		FONTOAM_GetMat(bip->font_actor[FA_NO_FIGHT].fontoam, &x, &y);
		if(client_type == CLIENT_TYPE_C){
			x += bip->font_actor[FA_NO_FIGHT].font_len + POKEICON_SIZE_X/2;
		}
		else{
			x -= POKEICON_SIZE_X/2;
		}
		CATS_ObjectPosSetCap_SubSurface(cap, x, y - BATTLE_SUB_ACTOR_DISTANCE_INTEGER, 
			BATTLE_SUB_ACTOR_DISTANCE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_COMMAND_IN_FIGHTONLY��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_CommandInFightOnly(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	int client_type;
	
	client_type = bip->scene.bsc.client_type;
	
	//��ʍ\�z
	BGCallback_FightOnly(bip, select_bg, force_put);
	
	//�X���C�h�G�t�F�N�g�Z�b�g
	BG_SlideSetInit(bip, client_type);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_FIGHTONLY��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_FightOnly(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	int client_type;
	
	client_type = bip->scene.bsc.client_type;
	
	//��ʍ\�z
	BGCallback_CommandSelect(bip, select_bg, force_put);
	
	//�s�K�v�ȃX�N���[�����N���A(�o�b�O�A�|�P�����A�ɂ���)
	{
		GF_BGL_INI *bgl;
		
		bgl = BattleWorkGF_BGL_INIGet(bip->bw);
		GF_BGL_ScrFill(bgl, BI_FRAME_PANEL, BG_CLEAR_CODE, 
			0, 0x10, 32, 8, GF_BGL_SCRWRT_PALIN);
		GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_BF);
	}
	
	//�s�K�v�ȃt�H���gOAM���o�j�b�V��
	FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_ITEM].fontoam, FALSE);
	FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_POKEMON].fontoam, FALSE);
	FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_ESCAPE].fontoam, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_COMMAND_IN_FIGHTONLY��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_ParkCommandIn(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	int client_type;
	
	client_type = bip->scene.bsc.client_type;
	
	//��ʍ\�z
	BGCallback_ParkCommand(bip, select_bg, force_put);
	
	//�X���C�h�G�t�F�N�g�Z�b�g
	BG_SlideSetInit(bip, client_type);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_FIGHTONLY��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_ParkCommand(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	int client_type;
	
	client_type = bip->scene.bsc.client_type;
	
	//��ʍ\�z
	BGCallback_CommandSelect(bip, select_bg, force_put);
	
	//�s�K�v�ȃX�N���[�����N���A(�o�b�O�A�|�P����)
	{
		GF_BGL_INI *bgl;
		
		bgl = BattleWorkGF_BGL_INIGet(bip->bw);
		GF_BGL_ScrFill(bgl, BI_FRAME_PANEL, BG_CLEAR_CODE, 
			0, 0x10, 10, 8, GF_BGL_SCRWRT_PALIN);
		GF_BGL_ScrFill(bgl, BI_FRAME_PANEL, BG_CLEAR_CODE, 
			0x16, 0x10, 10, 8, GF_BGL_SCRWRT_PALIN);
		GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_BF);
	}
	
	//�s�K�v�ȃt�H���gOAM���o�j�b�V��
	FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_ITEM].fontoam, FALSE);
	FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_POKEMON].fontoam, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_WAZA��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_Waza(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	BINPUT_SCENE_WAZA *bsw;
	int i;
	MSGDATA_MANAGER *msg_man;
	MEMORY_DECORD_WORK *mdw;
	GF_PRINTCOLOR color;
	
	bsw = &bip->scene.bsw;
	GF_ASSERT(bsw != NULL);

	bip->client_type = bsw->client_type;
	msg_man = BattleWorkFightMsgGet(bip->bw);
	
	mdw = MemoryDecordWorkGet(bip, bsw->client_type);
	
	//�Z�^�C�v�A�C�R��
	Sub_WazaTypeIconCreateAll(bip);
	//�Z���ރA�C�R��
//	Sub_WazaKindIconCreateAll(bip);

	//�Z��
	{
		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_WAZA_1], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_INPUT_WAZA_1, FA_POS_WAZA_1_X, FA_POS_WAZA_1_Y, FONTOAM_CENTER, 
			&mdw->exbmp_waza[0]);

		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_WAZA_2], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_INPUT_WAZA_2, FA_POS_WAZA_2_X, FA_POS_WAZA_2_Y, FONTOAM_CENTER,
			&mdw->exbmp_waza[1]);

		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_WAZA_3], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_INPUT_WAZA_3, FA_POS_WAZA_3_X, FA_POS_WAZA_3_Y, FONTOAM_CENTER,
			&mdw->exbmp_waza[2]);

		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_WAZA_4], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_INPUT_WAZA_4, FA_POS_WAZA_4_X, FA_POS_WAZA_4_Y, FONTOAM_CENTER,
			&mdw->exbmp_waza[3]);
	}

	//PP num/max
	{
		for(i = 0; i < 4; i++){
			color = PP_FontColorGet(bsw->pp[i], bsw->ppmax[i]);
			Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_PP_1 + i], NULL, FONT_SYSTEM, 
				color, PALOFS_PP, PLTTID_INPUT_PPMSG_1, 
				NowPPPos[i][0], NowPPPos[i][1], FONTOAM_LEFT, &mdw->exbmp_pp[i]);

			Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_PPMSG_1 + i], NULL, FONT_SYSTEM, 
				color, PALOFS_PP, PLTTID_INPUT_PPMSG_1, 
				PPMsgPos[i][0], PPMsgPos[i][1], FONTOAM_LEFT, &mdw->exbmp_ppmax[i]);
		}
	}

	//���ǂ�
	{
		STRBUF *modoru_src;
		
		modoru_src = MSGMAN_AllocString(msg_man, WazaModoruMsg);
		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_WAZA_MODORU], modoru_src, FONT_BUTTON, 
			MSGCOLOR_WAZA_MODORU, PALOFS_WAZA_MODORU, 
			PLTTID_INPUT_WAZA_CANCEL, FA_POS_WAZA_MODORU_X, FA_POS_WAZA_MODORU_Y, FONTOAM_CENTER,
			NULL);
		STRBUF_Delete(modoru_src);
	}

	//-- �Z�^�C�v����CGR��]�� --//
	{
		int waza_type;
		
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			if(bsw->wazano[i] != 0){
				waza_type = WT_WazaDataParaGet(bsw->wazano[i], ID_WTD_wazatype);
				Sub_WazaTypeCGRTrans(bip, waza_type, i);
			}
			else{
				Sub_WazaTypeNotTemotiChainCGRTrans(bip, i);
				break;
			}
		}
	}

	//-- �莝���Z���Ȃ����̓t�H���gOBJ��\�� --//
	{
		GF_BGL_INI *bgl;
		
		bgl = BattleWorkGF_BGL_INIGet(bip->bw);
		if(bsw->wazano[0] == 0){
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_WAZA_1].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PPMSG_1].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PP_1].fontoam, FALSE);
		}
		if(bsw->wazano[1] == 0){
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_WAZA_2].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PPMSG_2].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PP_2].fontoam, FALSE);
		}
		if(bsw->wazano[2] == 0){
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_WAZA_3].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PPMSG_3].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PP_3].fontoam, FALSE);
		}
		if(bsw->wazano[3] == 0){
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_WAZA_4].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PPMSG_4].fontoam, FALSE);
			FONTOAM_SetDrawFlag(bip->font_actor[FA_NO_PP_4].fontoam, FALSE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_D��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_YesNo(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	MSGDATA_MANAGER *msg_man;
	STRBUF *yes_src, *no_src;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	
	yes_src = MSGMAN_AllocString(msg_man, BattleYesMsg);
	no_src = MSGMAN_AllocString(msg_man, BattleNoMsg);

	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_YES], yes_src, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_YES, PALOFS_ESCAPE_YES,
		PLTTID_INPUT_ESCAPE_YES, FA_POS_ESCAPE_YES_X, FA_POS_ESCAPE_YES_Y, FONTOAM_CENTER,
		NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_NO], no_src, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_NO, PALOFS_ESCAPE_NO,
		PLTTID_INPUT_ESCAPE_NO, FA_POS_ESCAPE_NO_X, FA_POS_ESCAPE_NO_Y, FONTOAM_CENTER,
		NULL);
	
	STRBUF_Delete(yes_src);
	STRBUF_Delete(no_src);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_WASURERU��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_Wasureru(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	MSGDATA_MANAGER *msg_man;
	STRBUF *yes_src, *no_src;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	
	yes_src = MSGMAN_AllocString(msg_man, battle_WazaWasureru_Msg);
	no_src = MSGMAN_AllocString(msg_man, battle_WazaWasurenai_Msg);

	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_YES], yes_src, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_YES, PALOFS_ESCAPE_YES,
		PLTTID_INPUT_ESCAPE_YES, FA_POS_ESCAPE_YES_X, FA_POS_ESCAPE_YES_Y, FONTOAM_CENTER,
		NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_NO], no_src, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_NO, PALOFS_ESCAPE_NO,
		PLTTID_INPUT_ESCAPE_NO, FA_POS_ESCAPE_NO_X, FA_POS_ESCAPE_NO_Y, FONTOAM_CENTER,
		NULL);
	
	STRBUF_Delete(yes_src);
	STRBUF_Delete(no_src);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_AKIRAMERU��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_Akirameru(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	MSGDATA_MANAGER *msg_man;
	STRBUF *yes_src, *no_src, *yes_dest, *no_dest;
	WORDSET *wordset;
	BINPUT_SCENE_YESNO *bsy;
	
	bsy = &bip->scene.bsy;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	wordset = BattleWorkWORDSETGet(bip->bw);
	
	yes_src = MSGMAN_AllocString(msg_man, battle_WazaAkirameru_Msg);
	no_src = MSGMAN_AllocString(msg_man, battle_WazaAkiramenai_Msg);

	yes_dest = STRBUF_Create(BUFLEN_BI_WASURERU, HEAPID_BATTLE);
	no_dest = STRBUF_Create(BUFLEN_BI_WASURENAI, HEAPID_BATTLE);
	
	WORDSET_RegisterWazaName(wordset, 0, bsy->waza_no);
	WORDSET_ExpandStr(wordset, yes_dest, yes_src);
	WORDSET_ExpandStr(wordset, no_dest, no_src);

	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_YES], yes_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_YES, PALOFS_ESCAPE_YES,
		PLTTID_INPUT_ESCAPE_YES, FA_POS_ESCAPE_YES_X, FA_POS_ESCAPE_YES_Y, FONTOAM_CENTER,
		NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_NO], no_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_NO, PALOFS_ESCAPE_NO,
		PLTTID_INPUT_ESCAPE_NO, FA_POS_ESCAPE_NO_X, FA_POS_ESCAPE_NO_Y, FONTOAM_CENTER,
		NULL);
	
	STRBUF_Delete(yes_src);
	STRBUF_Delete(no_src);
	STRBUF_Delete(yes_dest);
	STRBUF_Delete(no_dest);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_NEXT_POKEMON��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_NextPokemon(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	MSGDATA_MANAGER *msg_man;
	STRBUF *yes_src, *no_src, *yes_dest, *no_dest;
	WORDSET *wordset;
	BINPUT_SCENE_YESNO *bsy;
	
	bsy = &bip->scene.bsy;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	wordset = BattleWorkWORDSETGet(bip->bw);
	
	yes_src = MSGMAN_AllocString(msg_man, NextPokeYesMsg);
	no_src = MSGMAN_AllocString(msg_man, NextPokeNoMsg);

	yes_dest = STRBUF_Create(BUFLEN_BI_NEXT_POKEMON, HEAPID_BATTLE);
	no_dest = STRBUF_Create(BUFLEN_BI_NEXT_ESCAPE, HEAPID_BATTLE);
	
	WORDSET_RegisterWazaName(wordset, 0, bsy->waza_no);
	WORDSET_ExpandStr(wordset, yes_dest, yes_src);
	WORDSET_ExpandStr(wordset, no_dest, no_src);

	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_YES], yes_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_YES, PALOFS_ESCAPE_YES,
		PLTTID_INPUT_ESCAPE_YES, FA_POS_ESCAPE_YES_X, FA_POS_ESCAPE_YES_Y, FONTOAM_CENTER,
		NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_NO], no_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_NO, PALOFS_ESCAPE_NO,
		PLTTID_INPUT_ESCAPE_NO, FA_POS_ESCAPE_NO_X, FA_POS_ESCAPE_NO_Y, FONTOAM_CENTER,
		NULL);
	
	STRBUF_Delete(yes_src);
	STRBUF_Delete(no_src);
	STRBUF_Delete(yes_dest);
	STRBUF_Delete(no_dest);
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_CHANGE_POKEMON��BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_ChangePokemon(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	MSGDATA_MANAGER *msg_man;
	STRBUF *yes_src, *no_src, *yes_dest, *no_dest;
	WORDSET *wordset;
	BINPUT_SCENE_YESNO *bsy;
	
	bsy = &bip->scene.bsy;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	wordset = BattleWorkWORDSETGet(bip->bw);
	
	yes_src = MSGMAN_AllocString(msg_man, TorikaeruYesMsg);
	no_src = MSGMAN_AllocString(msg_man, TorikaeruNoMsg);

	yes_dest = STRBUF_Create(BUFLEN_BI_CHANGE_POKEMON, HEAPID_BATTLE);
	no_dest = STRBUF_Create(BUFLEN_BI_CHANGE_NOT, HEAPID_BATTLE);
	
	WORDSET_RegisterWazaName(wordset, 0, bsy->waza_no);
	WORDSET_ExpandStr(wordset, yes_dest, yes_src);
	WORDSET_ExpandStr(wordset, no_dest, no_src);

	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_YES], yes_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_YES, PALOFS_ESCAPE_YES,
		PLTTID_INPUT_ESCAPE_YES, FA_POS_ESCAPE_YES_X, FA_POS_ESCAPE_YES_Y, FONTOAM_CENTER,
		NULL);
	Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_ESCAPE_NO], no_dest, FONT_BUTTON, 
		MSGCOLOR_ESCAPE_NO, PALOFS_ESCAPE_NO,
		PLTTID_INPUT_ESCAPE_NO, FA_POS_ESCAPE_NO_X, FA_POS_ESCAPE_NO_Y, FONTOAM_CENTER,
		NULL);
	
	STRBUF_Delete(yes_src);
	STRBUF_Delete(no_src);
	STRBUF_Delete(yes_dest);
	STRBUF_Delete(no_dest);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����I����BGCreate���ɌĂ΂��R�[���o�b�N�֐�
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   select_bg		�\��BG�^�C�v(BINPUT_TYPE_???)
 * @param   force_put		TRUE:�����]���AFALSE:���ɓ����f�[�^���]������Ă���Ȃ�ē]���͂��Ȃ�
 */
//--------------------------------------------------------------
static void BGCallback_PokeSelect(BI_PARAM_PTR bip, int select_bg, int force_put)
{
	BINPUT_SCENE_POKE *bsp;
	int i;
	MSGDATA_MANAGER *msg_man;
	u8 hit_range[CLIENT_MAX];
	STRBUF *monsname_p, *monsname_src;
	POKEMON_PARAM *pp;
	POKEMON_PASO_PARAM *ppp;
	WORDSET *wordset;
	GF_PRINTCOLOR color;
	u8 client_type_buf[CLIENT_TYPE_MAX];
	u8 client_no_buf[CLIENT_TYPE_MAX];
	int client_no;
	
	bsp = &bip->scene.bsp;
	bip->pokesele_type = bsp->pokesele_type;
	bip->client_type = bsp->client_type;
	msg_man = BattleWorkFightMsgGet(bip->bw);
	wordset = BattleWorkWORDSETGet(bip->bw);
	
	Sub_PokeSelectHitRange(bip, hit_range, FALSE);
	
	Sub_PokeIconResourceLoad(bip);
	
	Sub_JointScreenWrite(bip);
	
	BattleClientTypeBufMake(bip->bw, client_type_buf);
	BattleClientNoBufMake(bip->bw, client_no_buf);

	//�|�P������
	monsname_p = STRBUF_Create(BUFLEN_BI_POKESELENAME, HEAPID_BATTLE);
	for(i = 0; i < CLIENT_MAX; i++){
		client_no = client_no_buf[CLIENT_TYPE_A + i];
		OS_TPrintf("client_no:%d client_type:%d\n",client_no,CLIENT_TYPE_A+i);
		if(bsp->dspp[client_no].exist == TRUE && hit_range[i] == TRUE){
			
			if(bsp->dspp[client_no].sex == PARA_MALE){
				monsname_src = MSGMAN_AllocString(msg_man, TargetPokemonMaleMsg);
			}
			else if(bsp->dspp[client_no].sex == PARA_FEMALE){
				monsname_src = MSGMAN_AllocString(msg_man, TargetPokemonFemaleMsg);
			}
			else{
				monsname_src = MSGMAN_AllocString(msg_man, TargetPokemonMsg);
			}
		#if 0
			pp = BattleWorkPokemonParamGet(bip->bw, client_type_buf[i], bsp->dspp[i].sel_mons_no);
		#else
			pp = BattleWorkPokemonParamGet(bip->bw, client_no, bsp->dspp[client_no].sel_mons_no);
		#endif
			ppp = PPPPointerGet(pp);
			WORDSET_RegisterPokeNickName(wordset, 0, ppp);
			WORDSET_ExpandStr(wordset, monsname_p, monsname_src);

			if(i & 1){
				color = MSGCOLOR_POKESELE_ENEMY;
			}
			else{
				color = MSGCOLOR_POKESELE_MINE;
			}
			Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_POKE_A + i], monsname_p, FONT_BUTTON, 
				color, PALOFS_POKESELE,
				PLTTID_INPUT_POKE, PokeSelePos[i][0], PokeSelePos[i][1], FONTOAM_CENTER, NULL);
			
			STRBUF_Delete(monsname_src);
			
			{//�|�P�����A�C�R��
				switch(i){
				case 1:
					Sub_PokeIconCharActorSet(bip, pp, CLIENT_TYPE_B, bsp->dspp[client_no].hp, 
						bsp->dspp[client_no].hpmax, bsp->dspp[client_no].status);
					break;
				case 3:
					Sub_PokeIconCharActorSet(bip, pp, CLIENT_TYPE_D, bsp->dspp[client_no].hp, 
						bsp->dspp[client_no].hpmax, bsp->dspp[client_no].status);
					break;
				}
			}
		}
		else{		//�I���o���Ȃ��|�P����
		#if 0 //2006.05.10(��)
			if(hit_range[i] == TRUE){
				//�ʏ�I���o����񂾂��ǁA���S�ȂǂőI���o���Ȃ��|�P�����Ɍ���ǃp�l���]��
				Sub_PokemonNotPanelTrans(bip, i);
			}
		#else
			if(hit_range[i] == FALSE){
				//���X�I���o���Ȃ��p�l���̂݁A�ǃp�l����]������
				//���S�ȂǂőI���o���Ȃ��̂̓W���C���gOBJ�̓s���㌳�̂܂܎c��
				Sub_PokemonNotPanelTrans(bip, i);
			}
		#endif
		}
	}
	STRBUF_Delete(monsname_p);
	
	//���ǂ�
	{
		STRBUF *modoru_src;
		
		modoru_src = MSGMAN_AllocString(msg_man, DirModoruMsg);
		Sub_FontOamCreate(bip, &bip->font_actor[FA_NO_POKE_CANCEL], modoru_src, FONT_BUTTON, 
			MSGCOLOR_POKESELE_MODORU, PALOFS_POKESELE_MODORU,
			PLTTID_INPUT_POKE, PokeSelePos[CLIENT_MAX][0], PokeSelePos[CLIENT_MAX][1], 
			FONTOAM_CENTER, NULL);
		STRBUF_Delete(modoru_src);
	}
}

//==============================================================================
//
//	�^�b�`�p�l���������ɌĂ΂��R�[���o�b�N�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_A�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_A(BI_PARAM_PTR bip, int tp_ret, int panel_pal)
{
	int fa_no, waku_type, pokeicon_no;
	
	pokeicon_no = NOT_POKE_ICON;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case SELECT_FIGHT_COMMAND:
		fa_no = FA_NO_FIGHT;
		waku_type = WAKU_TYPE_A;

		switch(bip->client_type){
		case CLIENT_TYPE_AA:
			pokeicon_no = bip->client_type;
			break;
		case CLIENT_TYPE_A:
		case CLIENT_TYPE_C:
			pokeicon_no = bip->client_type - CLIENT_TYPE_A;
			break;
		}
		break;
	case SELECT_ITEM_COMMAND:
		fa_no = FA_NO_ITEM;
		waku_type = WAKU_TYPE_B;
		break;
	case SELECT_POKEMON_COMMAND:
		fa_no = FA_NO_POKEMON;
		waku_type = WAKU_TYPE_B;
		break;
	case SELECT_ESCAPE_COMMAND:
		fa_no = FA_NO_ESCAPE;
		waku_type = WAKU_TYPE_B;
		break;
	}

	ColorEffTCB_PointFadeSet(bip, panel_pal);

	EffectTCB_Add(Effect_ButtonDown, bip);
	bip->effect_work.paracgr.scrn_offset = CommandButtonScrnOffset[tp_ret - SELECT_FIGHT_COMMAND];
	bip->effect_work.paracgr.scrn_range = &CommandButtonScrnRect[tp_ret - SELECT_FIGHT_COMMAND];
	bip->effect_work.paracgr.scrnbuf_no = SCRNBUF_COMMAND;
	bip->effect_work.paracgr.tp_ret = tp_ret;
	bip->effect_work.paracgr.fa_no = fa_no;
	bip->effect_work.paracgr.pokeicon_no = pokeicon_no;
	bip->effect_work.paracgr.waku_type = waku_type;
	bip->effect_work.paracgr.waku_pos = CommandWakuPos[tp_ret - SELECT_FIGHT_COMMAND];
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_WAZA�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_Waza(BI_PARAM_PTR bip, int tp_ret, int panel_pal)
{
	BINPUT_SCENE_WAZA *bsw;
	u32 transcgr_id[BUTTON_ANM_NUM];
	u32 rd_no;
	const CGR_TRANS_RECTDATA *ctr[BUTTON_ANM_NUM];
	const s16 *scrn_offset;
	const REWRITE_SCRN_RECT *scrn_range;
	
	if(tp_ret == RECT_HIT_NONE){
		return tp_ret;
	}
	
	bsw = &bip->scene.bsw;
	if(tp_ret >= SELECT_SKILL_1 && tp_ret <= SELECT_SKILL_4){
		if(bsw->wazano[tp_ret - SELECT_SKILL_1] == 0){
			return RECT_HIT_NONE;	//�����ꂽ�ꏊ�̎莝���Z���Ȃ�
		}
	}
	
	rd_no = tp_ret - SELECT_SKILL_1;
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return RECT_HIT_NONE;
	case SELECT_SKILL_1:
	case SELECT_SKILL_2:
	case SELECT_SKILL_3:
	case SELECT_SKILL_4:
		scrn_offset = WazaButtonScrnOffset[tp_ret - SELECT_SKILL_1];
		scrn_range = &WazaButtonScrnRect[tp_ret - SELECT_SKILL_1];
		break;
	case SELECT_CANCEL:
		scrn_offset = WazaButtonScrnOffset[NELEMS(WazaButtonScrnOffset) - 1];
		scrn_range = &WazaButtonScrnRect[NELEMS(WazaButtonScrnOffset) - 1];
		break;
	}

	ColorEffTCB_PointFadeSet(bip, panel_pal);

	EffectTCB_Add(Effect_WazaButtonDown, bip);
	bip->effect_work.paracgr.scrn_offset = scrn_offset;
	bip->effect_work.paracgr.scrn_range = scrn_range;
	bip->effect_work.paracgr.scrnbuf_no = SCRNBUF_WAZA;
	bip->effect_work.paracgr.tp_ret = tp_ret;
//	bip->effect_work.paracgr.fa_no = fa_no;
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_D�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_D(BI_PARAM_PTR bip, int tp_ret, int panel_pal)
{
	int fa_no;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case TRUE:
		fa_no = FA_NO_ESCAPE_YES;
		break;
	case SELECT_CANCEL:
		fa_no = FA_NO_ESCAPE_NO;
		break;
	}

	ColorEffTCB_PointFadeSet(bip, panel_pal);

	EffectTCB_Add(Effect_ButtonDown, bip);
	if(tp_ret == TRUE){
		bip->effect_work.paracgr.scrn_offset = YesNoButtonScrnOffset[1];
		bip->effect_work.paracgr.scrn_range = &YesNoButtonScrnRect[1];
	}
	else{
		bip->effect_work.paracgr.scrn_offset = YesNoButtonScrnOffset[0];
		bip->effect_work.paracgr.scrn_range = &YesNoButtonScrnRect[0];
	}
	bip->effect_work.paracgr.scrnbuf_no = SCRNBUF_YESNO;
	bip->effect_work.paracgr.tp_ret = tp_ret;
	bip->effect_work.paracgr.fa_no = fa_no;
	bip->effect_work.paracgr.waku_type = WAKU_TYPE_NONE;
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   BINPUT_TYPE_D�Ń^�b�`�p�l���������ɌĂяo�����R�[���o�b�N�֐�
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret		�^�b�`�p�l������(bmd->tpd_ret�̒l��RECT_HIT_NONE)
 * @param   panel_pal	�������p�l���̃p���b�g�ԍ�
 * 
 * @retval  tp_ret��Ԃ�(�����̒��ŕύX����K�v���Ȃ��Ȃ�A�����œn���ꂽ�l�����̂܂ܕԂ�)
 */
//--------------------------------------------------------------
static int TPCallback_PokeSele(BI_PARAM_PTR bip, int tp_ret, int panel_pal)
{
	BINPUT_SCENE_POKE *bsp;
	u8 hit_range[CLIENT_MAX];
	
	bsp = &bip->scene.bsp;
	
	Sub_PokeSelectHitRange(bip, hit_range, TRUE);
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case SELECT_TARGET_A:
		if(hit_range[CLIENT_TYPE_A - CLIENT_TYPE_A] == FALSE){
			return RECT_HIT_NONE;
		}
		break;
	case SELECT_TARGET_B:
		if(hit_range[CLIENT_TYPE_B - CLIENT_TYPE_A] == FALSE){
			return RECT_HIT_NONE;
		}
		break;
	case SELECT_TARGET_C:
		if(hit_range[CLIENT_TYPE_C - CLIENT_TYPE_A] == FALSE){
			return RECT_HIT_NONE;
		}
		break;
	case SELECT_TARGET_D:
		if(hit_range[CLIENT_TYPE_D - CLIENT_TYPE_A] == FALSE){
			return RECT_HIT_NONE;
		}
		break;
	case SELECT_CANCEL:
		ColorEffTCB_PointFadeSet(bip, NELEMS(PokeSeleMenuPaletteNo) - 1);
		
		EffectTCB_Add(Effect_ButtonDown, bip);
		bip->effect_work.paracgr.scrn_offset 
			= PokemonButtonScrnOffset[NELEMS(PokemonButtonScrnOffset) - 1];
		bip->effect_work.paracgr.scrn_range 
			= &PokemonButtonScrnRect[NELEMS(PokemonButtonScrnRect) - 1];
		bip->effect_work.paracgr.scrnbuf_no = SCRNBUF_POKESELE;
		bip->effect_work.paracgr.tp_ret = tp_ret;
		bip->effect_work.paracgr.fa_no = FA_NO_POKE_CANCEL;
		bip->effect_work.paracgr.waku_type = WAKU_TYPE_NONE;
		return tp_ret;
	}

	//�g�X�N���[���N���A
	{
		GF_BGL_INI *bgl;
		bgl = BattleWorkGF_BGL_INIGet(bip->bw);
		GF_BGL_ScrClearCode(bgl, BI_FRAME_BF, BG_CLEAR_CODE);
		GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_BF);
	}
	
	//ColorEffTCB_PointFadeSet(bip, panel_pal);
	ColorEffTCB_PokeSeleFadeSet(bip, tp_ret);

	EffectTCB_Add(Effect_PokeSeleButtonDown, bip);
	bip->effect_work.pokesele.tp_ret = tp_ret;
	return tp_ret;
}



//==============================================================================
//
//	�T�u�֐�
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̃��\�[�X�����[�h����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * 
 * �L�����̃��\�[�X�̓A�N�^�[�����ƈꏏ�ɂ��̂ŁA�����ł͓o�^���܂���
 */
//--------------------------------------------------------------
static void Sub_PokeIconResourceLoad(BI_PARAM_PTR bip)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int cell_id, char_id, anm_id;
	PALETTE_FADE_PTR pfd;

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	pfd = BattleWorkPfdGet(bip->bw);

	//�p���b�g
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, POKEICON_PAL_MAX, 
		NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_POKEICON);
	//�Z��
	CATS_LoadResourceCellArc(csp, crp, ARC_POKEICON, 
		PokeIconAnmCellArcIndexGet(), 0, CELLID_POKEICON);
	//�Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, crp, ARC_POKEICON, PokeIconAnmCellAnmArcIndexGet(), 0, CELLANMID_POKEICON);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���̃��\�[�X��S�ĉ������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_PokeIconResourceFree(BI_PARAM_PTR bip)
{
	CATS_RES_PTR crp;

	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	CATS_FreeResourceChar(crp, CHARID_POKEICON_COMMAND);
	CATS_FreeResourceChar(crp, CHARID_POKEICON_B);
	CATS_FreeResourceChar(crp, CHARID_POKEICON_D);
	CATS_FreeResourceCell(crp, CELLID_POKEICON);
	CATS_FreeResourceCellAnm(crp, CELLANMID_POKEICON);
	CATS_FreeResourcePltt(crp, PLTTID_POKEICON);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���A�N�^�[��S�č폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_PokeIconActorAllDel(BI_PARAM_PTR bip)
{
	int i;
	
	for(i = 0; i < CLIENT_MAX; i++){
		if(bip->pokeicon_cap[i] != NULL){
			CATS_ActorPointerDelete_S(bip->pokeicon_cap[i]);
			bip->pokeicon_cap[i] = NULL;
		}
		if(bip->pokeicon_tcb[i] != NULL){
			TCB_Delete(bip->pokeicon_tcb[i]);
			bip->pokeicon_tcb[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���A�N�^�[�𐶐�����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   pp				�Ώۂ̃|�P�����p�����[�^
 * @param   client_type		CIENT_TYPE_???
 *
 * @retval  ���������|�P�����A�C�R���A�N�^�[�̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR Sub_PokeIconCharActorSet(BI_PARAM_PTR bip, POKEMON_PARAM *pp, int client_type,
	int hp, int maxhp, int status)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	u32 char_id;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	CATS_ACT_PTR cap;
	int tbl_no;
	
	if(client_type >= CLIENT_TYPE_A){
		tbl_no = client_type - CLIENT_TYPE_A;	//0origin�ɏC��
	}
	else{
		tbl_no = client_type;	//AA or BB
	}
	
	GF_ASSERT(bip->pokeicon_cap[tbl_no] == NULL);
	GF_ASSERT(bip->pokeicon_tcb[tbl_no] == NULL);
	
	switch(client_type){	//�퓬���͉�ʂł͓G�̂ݕ\��
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		char_id = CHARID_POKEICON_COMMAND;
		break;
	case CLIENT_TYPE_B:
		char_id = CHARID_POKEICON_B;
		break;
	case CLIENT_TYPE_D:
		char_id = CHARID_POKEICON_D;
		break;
	default:
		GF_ASSERT(0 && "�ݒ肳��Ă��܂���");
		return NULL;
	}

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	//�L�������\�[�X
	CATS_LoadResourceCharArc(csp, crp, ARC_POKEICON, PokeIconCgxArcIndexGetByPP(pp),
		0, NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	
	//�A�N�^�[
	obj_param = PokeIconObjParam;
	obj_param.id[CLACT_U_CHAR_RES] = char_id;
	obj_param.x = PokeIconPos[tbl_no][0];
	obj_param.y = PokeIconPos[tbl_no][1];
	cap = CATS_ObjectAdd_S(csp, crp, &obj_param);
	CATS_ObjectPosSetCap_SubSurface(cap, obj_param.x, obj_param.y, BATTLE_SUB_ACTOR_DISTANCE);
	//�p���b�g�؂�ւ�
//	monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
//	egg = PokeParaGet(pp, ID_PARA_tamago_flag, NULL);
	CLACT_PaletteOffsetChgAddTransPlttNo(cap->act, PokeIconPalNumGetByPP(pp));
	
	{//�A�C�R���A�j���ݒ�
		int anmno = 0;
		
		if(hp == 0 || status == COMSEL_STATUS_DEAD){
			anmno = POKEICON_ANM_DEATH;
		}
		else if(status == COMSEL_STATUS_NG){
			anmno = POKEICON_ANM_STCHG;
		}
		else{
			switch(GetHPGaugeDottoColor(hp, maxhp, GAUGE_HP_DOTTOMAX)){
			case HP_DOTTO_MAX:
				anmno = POKEICON_ANM_HPMAX;
				break;
			case HP_DOTTO_GREEN:	// ��
				anmno = POKEICON_ANM_HPGREEN;
				break;
			case HP_DOTTO_YELLOW:	// ��
				anmno = POKEICON_ANM_HPYERROW;
				break;
			case HP_DOTTO_RED:		// ��
				anmno = POKEICON_ANM_HPRED;
				break;
			}
			CATS_ObjectAnimeSeqSetCap(cap, anmno);
			//CATS_ObjectAutoAnimeSetCap(cap, CATS_ANM_AUTO_ON);	//�I�[�g�A�j��
		}
		OS_TPrintf("anmno = %d, hp = %d, max = %d, status = %d\n", anmno, hp, maxhp, status);
	}
	
	CATS_ObjectUpdateCap(cap);
	bip->pokeicon_cap[tbl_no] = cap;
	bip->pokeicon_tcb[tbl_no] = TCB_Add(PokeIconAnimeUpdate, cap, TCBPRI_BINPUT_EFFECT);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����A�C�R���A�j���X�V����
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	�|�P�����A�C�R���A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void PokeIconAnimeUpdate(TCB_PTR tcb, void *work)
{
	CATS_ACT_PTR cap = work;
	CATS_ObjectUpdateCap(cap);
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����̃X�e�[�^�X����莝���{�[���̃A�j���V�[�P���X�ԍ����擾����
 * @param   status		�|�P�����̃X�e�[�^�X(COMSEL_STATUS_???)
 * @retval  �莝���{�[���̃A�j���V�[�P���X�ԍ�
 */
//--------------------------------------------------------------
static int Sub_StockBallAnmSeqGet(u8 status)
{
	int anm_seq;
	
	switch(status){
	case COMSEL_STATUS_NONE:
	default:
		anm_seq = STOCK_ANMSEQ_NONE;
		break;
	case COMSEL_STATUS_ALIVE:
		anm_seq = STOCK_ANMSEQ_ALIVE;
		break;
	case COMSEL_STATUS_DEAD:
		anm_seq = STOCK_ANMSEQ_DEAD;
		break;
	case COMSEL_STATUS_NG:
		anm_seq = STOCK_ANMSEQ_NG;
		break;
	}
	return anm_seq;
}

//--------------------------------------------------------------
/**
 * @brief   ewp��Sub_ScrnTouchChange�֐��p�̃p�����[�^���Z�b�g����
 *
 * @param   ewp				�G�t�F�N�gBG���������p�����[�^�����
 * @param   rsr				���������͈�
 * @param   rsr_num			rsr�f�[�^��
 * @param   add_charname	�L�����N�^�[�l�[���ɑ������ޒl(�}�C�i�X���L��)
 * @param   fa_no			�Ώۃt�H���gOBJ�A�N�^�[���[�N�̓Y����
 */
//--------------------------------------------------------------
inline void SubInline_EffBgWriteParamSet(EFFBG_WRITE_PARAM *ewp, const REWRITE_SCRN_RECT *rsr, 
	u8 rsr_num, s8 add_charname)
{
	ewp->rsr = rsr;
	ewp->rsr_num = rsr_num;
	ewp->add_charname = add_charname;
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���������ɓ��삳����BG�X�N���[�������������ЂƂ܂Ƃ߂ɂ�������
 *
 * @param   bgl					BGL�f�[�^
 * @param   rsr[]				���������͈�
 * @param   rsr_num				rsr�f�[�^��
 * @param   add_charname		�L�����N�^�[�l�[���ɑ������ޒl(�}�C�i�X���L��)
 */
//--------------------------------------------------------------
static void Sub_ScrnTouchChange(GF_BGL_INI *bgl, const REWRITE_SCRN_RECT rsr[], int rsr_num, 
	int add_charname)
{
	u16 *eff_scrn;
	u32 eff_size;
	
	//�G�t�F�N�g�ʂ̃X�N���[�����N���A
	eff_scrn = GF_BGL_ScreenAdrsGet(bgl, BI_FRAME_EFF);
	eff_size = GF_BGL_ScreenSizGet(bgl, BI_FRAME_EFF);
	MI_CpuClear16(eff_scrn, eff_size);
	
	Sub_ScrnAddOffset(rsr, rsr_num, bgl, BI_FRAME_PANEL, add_charname);
	Sub_ScrnCopy(rsr, rsr_num, bgl, BI_FRAME_BF, BI_FRAME_EFF);
	Sub_ScrnErase(rsr, rsr_num, bgl, BI_FRAME_BF, BG_CLEAR_CODE);
	
//	GF_BGL_ScrollSet(bgl, BI_FRAME_EFF, GF_BGL_SCROLL_Y_SET, SCRN_SCROLL_A_EFF_Y);
	GF_BGL_VisibleSet(BI_FRAME_EFF, VISIBLE_ON);

	GF_BGL_LoadScreenReq(bgl, BI_FRAME_PANEL);
	GF_BGL_LoadScreenReq(bgl, BI_FRAME_BF);
	GF_BGL_LoadScreenReq(bgl, BI_FRAME_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`�p�l���������ɓ��삳����BG�X�N���[�������������ЂƂ܂Ƃ߂ɂ�������
 *
 * @param   bgl					BGL�f�[�^
 * @param   rsr[]				���������͈�
 * @param   rsr_num				rsr�f�[�^��
 * @param   add_charname		�L�����N�^�[�l�[���ɑ������ޒl(�}�C�i�X���L��)
 */
//--------------------------------------------------------------
static void Sub_ScrnTouchChangeReverse(GF_BGL_INI *bgl, const REWRITE_SCRN_RECT rsr[], 
	int rsr_num, int add_charname)
{
	u16 *eff_scrn;
	u32 eff_size;
	
	GF_BGL_VisibleSet(BI_FRAME_EFF, VISIBLE_OFF);
	
	Sub_ScrnAddOffset(rsr, rsr_num, bgl, BI_FRAME_PANEL, -add_charname);
	Sub_ScrnCopy(rsr, rsr_num, bgl, BI_FRAME_EFF, BI_FRAME_BF);

	GF_BGL_LoadScreenReq(bgl, BI_FRAME_PANEL);
	GF_BGL_LoadScreenReq(bgl, BI_FRAME_BF);
	GF_BGL_LoadScreenReq(bgl, BI_FRAME_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���[���o�b�t�@��ǂݎ��A�L�����N�^�[�l�[���Ɏw��l����������
 *
 * @param   rsr[]				���������͈�
 * @param   rsr_num				rsr�f�[�^��
 * @param   screen_buf			�X�N���[���o�b�t�@�ւ̃|�C���^
 * @param   add_charname		�L�����N�^�[�l�[���ɑ������ޒl(�}�C�i�X���L��)
 */
//--------------------------------------------------------------
static void Sub_ScrnAddOffset(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl,
	int frame_no, int add_charname)
{
	int i, x, y, charname;
	u16 *screen_buf, *buf;
	
	screen_buf = GF_BGL_ScreenAdrsGet(bgl, frame_no);
	GF_ASSERT(screen_buf != NULL);
	
	for(i = 0; i < rsr_num; i++){
		for(y = rsr[i].top; y <= rsr[i].bottom; y++){
			buf = &screen_buf[0x20 * y];
			for(x = rsr[i].left; x <= rsr[i].right; x++){
				charname = (buf[x] & GX_SCRFMT_TEXT_CHARNAME_MASK) + add_charname;
				buf[x] -= buf[x] & GX_SCRFMT_TEXT_CHARNAME_MASK;
				buf[x] |= charname;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w��͈͂̃X�N���[����ʂ̃X�N���[���o�b�t�@�ɃR�s�[����
 *
 * @param   rsr[]			�R�s�[�͈�
 * @param   rsr_num			rsr�f�[�^��
 * @param   bgl				BGL�f�[�^
 * @param   src_frame		�R�s�[���X�N���[���̃t���[��No
 * @param   dest_frame		�R�s�[��X�N���[���̃t���[��No
 */
//--------------------------------------------------------------
static void Sub_ScrnCopy(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int src_frame, int dest_frame)
{
	u16 *src_buf, *dest_buf;
	int i, y;
	
	src_buf = GF_BGL_ScreenAdrsGet(bgl, src_frame);
	dest_buf = GF_BGL_ScreenAdrsGet(bgl, dest_frame);
	GF_ASSERT(src_buf != NULL);
	GF_ASSERT(dest_frame != NULL);

	for(i = 0; i < rsr_num; i++){
		for(y = rsr[i].top; y <= rsr[i].bottom; y++){
			MI_CpuCopy16(&src_buf[0x20*y + rsr[i].left], &dest_buf[0x20*y + rsr[i].left], 
				(rsr[i].right - rsr[i].left + 1) * 2);
		}
	}
}

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
 * @param   frame_no		�t���[��NO
 * @param   cgr_id			�]���O���t�B�b�N��CGRID(0xffffffff�̏ꍇ�̓N���A���܂�)
 * @param   rd				�]���͈̓f�[�^�̃|�C���^(cgr_id��0xffffffff�̏ꍇ��src�̒l�͓K����OK)
 *
 * @retval  CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransParamSet(int frame_no, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, NNSG2dCharacterData **loaded_char)
{
	void *arc_data;
	NNSG2dCharacterData *char_data;
	CGR_TRANS_PARAM *ctp;
	
	ctp = sys_AllocMemory(HEAPID_BATTLE, sizeof(CGR_TRANS_PARAM));
	MI_CpuClear8(ctp, sizeof(CGR_TRANS_PARAM));
	
	if(cgr_id != 0xffffffff){
		if(loaded_char == NULL){
			ctp->arc_data = ArcUtil_CharDataGet(ARC_BATT_BG, cgr_id, 1, &char_data, HEAPID_BATTLE);
			ctp->raw_data = char_data->pRawData;
			ctp->x_len = char_data->W * 0x20;
		}
		else{
			ctp->arc_data = NULL;
			ctp->raw_data = (*loaded_char)->pRawData;
			ctp->x_len = (*loaded_char)->W * 0x20;
		}
	}
	
	ctp->rd = *rd;
	ctp->dest_vram = GF_BGL_CgxGet(frame_no);
	
	return ctp;
}

//--------------------------------------------------------------
/**
 * @brief   CGR�]���A�j�����s���^�X�N�𐶐����܂�
 *
 * @param   frame_no		�t���[��NO
 * @param   cgr_id			�]���O���t�B�b�N��CGRID(0xffffffff�̏ꍇ�̓N���A���܂�)
 * @param   rd				�]���͈̓f�[�^�̃|�C���^(cgr_id��0xffffffff�̏ꍇ��src�̒l�͓K����OK)
 * @param   loaded_char		�֐��O�Ő�ɃL�������A�[�J�C�u���Ă���ꍇ�́A�����œn��
 *                          NULL�̏ꍇ�͒��ŃL�����A�[�J�C�u���s���܂��B
 *
 * @retval  CGR�]���A�j���p�����[�^���[�N�ւ̃|�C���^
 *
 * ���̊֐��g�p��A�K��Sub_CgrTransEndCheck�֐����g�p���A�I���m�F���s���Ă��������B
 * Sub_CgrTransEndCheck�֐����Ń��[�N�̉�������Ȃǂ��s���Ă��܂��B
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(int frame_no, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, NNSG2dCharacterData **loaded_char)
{
	CGR_TRANS_PARAM *ctp;

	ctp = Sub_CgrTransParamSet(frame_no, cgr_id, rd, loaded_char);
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

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOAM���쐬����
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   font_actor	���������t�H���gOAM�֘A�̃��[�N�����
 * @param   str			������(ex_bmpwin���g�p����ꍇ��NULL��OK)
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
static void Sub_FontOamCreate(BI_PARAM_PTR bip, FONT_ACTOR *font_actor, const STRBUF *str, 
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
	
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
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

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB,  HEAPID_BATTLE);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
	
	//���W�ʒu�C��
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
	y += BATTLE_SUB_ACTOR_DISTANCE_INTEGER - 8;
	
	finit.fontoam_sys = bip->fontoam_sys;
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
	finit.heap = HEAPID_BATTLE;
	
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
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_FontOamDeleteAll(BI_PARAM_PTR bip)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(bip->font_actor[i].fontoam != NULL){
			FONTOAM_Delete(bip->font_actor[i].fontoam);
			CharVramAreaFree(&bip->font_actor[i].cma);
			bip->font_actor[i].fontoam = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ������`��ׂ̈̃t�H���gOAM���쐬����
 *          (FONTOAM_OAMDATA���g�p�����o�[�W�����F�����񏑂������\)
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   font_actor	���������t�H���gOAM�֘A�̃��[�N�����
 *
 * �쐬�����t�H���gOAM�X�ɕ�������������ނ͕̂ʓrSub_FontOamDataRewrite���g�p���܂�
 */
//--------------------------------------------------------------
static void Sub_FontOamDataInit(BI_PARAM_PTR bip)
{
	FONTOAM_INIT finit;
	GF_BGL_BMPWIN bmpwin;
	CHAR_MANAGER_ALLOCDATA cma;
	int vram_size;
	FONTOAM_OBJ_PTR fontoam;
	GF_BGL_INI *bgl;
	CATS_RES_PTR crp;
	int font_len, char_len;
	FONTOAM_OAM_DATA_PTR oamdata;
	int i;
	
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	//BMP�쐬
	{
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, FONTOAMDATA_BMP_X_SIZE, 16 / 8, 0, 0);
//		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
//			PANEL_MSG_MARGIN, 0, NULL);
	}

	oamdata = FONTOAM_OAMDATA_Make(&bmpwin, HEAPID_BATTLE);
	vram_size = FONTOAM_OAMDATA_NeedCharSize(oamdata, NNS_G2D_VRAM_TYPE_2DSUB);
	
	finit.fontoam_sys = bip->fontoam_sys;
	finit.bmp = &bmpwin;
	finit.clact_set = CATS_GetClactSetPtr(crp);
	finit.pltt = CATS_PlttProxy(crp, PLTTID_INPUT_FONTOBJ_COMMON);
	finit.parent = NULL;
	finit.x = 0;
	finit.y = BATTLE_SUB_ACTOR_DISTANCE_INTEGER;
	finit.bg_pri = PANEL_MSG_BGPRI;
	finit.soft_pri = PANEL_MSG_SOFTPRI;
	finit.draw_area = NNS_G2D_VRAM_TYPE_2DSUB;
	finit.heap = HEAPID_BATTLE;

	for(i = 0; i < FA_NO_MAX; i++){
		CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
		
		finit.char_ofs = cma.alloc_ofs;
		
		fontoam = FONTOAM_OAMDATA_Init(&finit, oamdata);
		
		bip->font_actor[i].fontoam = fontoam;
		bip->font_actor[i].cma = cma;
	}
	
	//BMP�������
	GF_BGL_BmpWinDel(&bmpwin);
	
	bip->font_oamdata = oamdata;
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOAM��S�č폜�A�������
 *          (FONTOAM_OAMDATA���g�p�����o�[�W�����F�����񏑂������\)
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_FontOamDataExit(BI_PARAM_PTR bip)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		FONTOAM_OAMDATA_Delete(bip->font_actor[i].fontoam);
		CharVramAreaFree(&bip->font_actor[i].cma);
		bip->font_actor[i].fontoam = NULL;
	}
	
	FONTOAM_OAMDATA_Free(bip->font_oamdata);
	bip->font_oamdata = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �쐬�ς݂̃t�H���gOAM�ɑ΂��ĕ������`�悷��
 *          (FONTOAM_OAMDATA���g�p�����o�[�W�����F�����񏑂������\)
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   font_actor	�g�p����t�H���gOAM�֘A�̃��[�N�ւ̃|�C���^
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
static void Sub_FontOamDataRewrite(BI_PARAM_PTR bip, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id,
	int x, int y, int pos_center)
{
	FONTOAM_OBJ_PTR fontoam;
	GF_BGL_BMPWIN bmpwin;
	GF_BGL_INI *bgl;
	int font_len, char_len;
	
//	return;
	
	fontoam = font_actor->fontoam;
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	//������̃h�b�g������A�g�p����L���������Z�o����
	{
		font_len = FontProc_GetPrintStrWidth(font_type, str, PANEL_MSG_MARGIN);
		char_len = font_len / 8;
		if(FX_ModS32(font_len, 8) != 0){
			char_len++;
		}
	}
	
	//�t�H���gOAM������������
	{
		//BMP�쐬
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, FONTOAMDATA_BMP_X_SIZE, 16 / 8, 0, 0);
//		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
//			PANEL_MSG_MARGIN, 0, NULL);
		
		//�t�H���gOAM�ɏ���������BMP���Z�b�g
		FONTOAM_OAMDATA_ResetBmp(fontoam, bip->font_oamdata, &bmpwin, HEAPID_BATTLE);

		//BMP�������
		GF_BGL_BmpWinDel(&bmpwin);
	}

	//���W�ʒu�C��
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
	y += BATTLE_SUB_ACTOR_DISTANCE_INTEGER - 8;

	//�t�H���gOAM�p�����[�^�ύX
	FONTOAM_SetPaletteOffsetAddTransPlttNo(fontoam, pal_offset);
	FONTOAM_SetMat(fontoam, x, y);

	font_actor->font_len = font_len;
	FONTOAM_SetDrawFlag(font_actor->fontoam, TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOAM��S�Ĕ�\���ɂ���
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_FontOamDataEnableAllOff(BI_PARAM_PTR bip)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(bip->font_actor[i].fontoam != NULL){
			FONTOAM_SetDrawFlag(bip->font_actor[i].fontoam, FALSE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�l���A���X�N���[������������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_JointScreenWrite(BI_PARAM_PTR bip)
{
	u8 hit_range[CLIENT_MAX], connect_range[CLIENT_MAX];
	int x, y;
	u16 *scrn, *write_scrn;
	GF_BGL_INI *bgl;

	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	scrn = GF_BGL_ScreenAdrsGet(bgl, BI_FRAME_BF);
	
	Sub_PokeSelectHitRange(bip, hit_range, FALSE);
	
	//-- CLIENT_TYPE_A��B��2�̘A���ӏ��������ׂ��4�̃p�l���̘A���S�Ă��`�F�b�N�o���� --//
	
	//CLIENT_TYPE_A
	if(hit_range[0] == TRUE){
		Sub_PokeSelectPanelConnectRange(bip, SELECT_TARGET_A, connect_range, FALSE);
		
		if(connect_range[SELECT_TARGET_C - SELECT_TARGET_A] == TRUE){
			//A-C���q�����Ă���
			for(y = 12; y <= 16; y++){
				write_scrn = &scrn[y * 32];
				for(x = 0xf; x <= 0x10; x++){
					write_scrn[x] = JOINT_SCRN_CODE;
				}
			}
		}
		if(connect_range[SELECT_TARGET_D - SELECT_TARGET_A] == TRUE){
			//A-D���q�����Ă���
			for(y = 10; y <= 10; y++){
				write_scrn = &scrn[y * 32];
				for(x = 2; x <= 12; x++){
					write_scrn[x] = JOINT_SCRN_CODE;
				}
			}
		}
	}
	
	//CLIENT_TYPE_B
	if(hit_range[1] == TRUE){
		Sub_PokeSelectPanelConnectRange(bip, SELECT_TARGET_B, connect_range, FALSE);

		if(connect_range[SELECT_TARGET_C - SELECT_TARGET_A] == TRUE){
			//B-C���q�����Ă���
			for(y = 10; y <= 10; y++){
				write_scrn = &scrn[y * 32];
				for(x = 0x13; x <= 0x1d; x++){
					write_scrn[x] = JOINT_SCRN_CODE;
				}
			}
		}
		if(connect_range[SELECT_TARGET_D - SELECT_TARGET_A] == TRUE){
			//B-D���q�����Ă���
			for(y = 3; y <= 7; y++){
				write_scrn = &scrn[y * 32];
				for(x = 0xf; x <= 0x10; x++){
					write_scrn[x] = JOINT_SCRN_CODE;
				}
			}
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief   �w��N���C�A���g�^�C�v��MEMORY_DECORD_WORK���擾����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   client_type		�N���C�A���g�^�C�v
 *
 * @retval  MEMORY_DECORD_WORK�ւ̃|�C���^
 */
//--------------------------------------------------------------
static MEMORY_DECORD_WORK *MemoryDecordWorkGet(BI_PARAM_PTR bip, int client_type)
{
	if(client_type >= CLIENT_TYPE_A){
		client_type -= CLIENT_TYPE_A;
	}
	return &bip->memory_decord[client_type];
}

//--------------------------------------------------------------
/**
 * @brief   MEMORY_DECORD_WORK���������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void MemoryDecordWorkFree(BI_PARAM_PTR bip)
{
	int i, client;

	for(client = 0; client < CLIENT_MAX; client++){
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			sys_FreeMemoryEz(bip->memory_decord[client].typeicon_cgx[i]);
			if(bip->memory_decord[client].exbmp_waza[i].bmpwin.chrbuf != NULL){
				GF_BGL_BmpWinDel(&bip->memory_decord[client].exbmp_waza[i].bmpwin);
			}
			if(bip->memory_decord[client].exbmp_pp[i].bmpwin.chrbuf != NULL){
				GF_BGL_BmpWinDel(&bip->memory_decord[client].exbmp_pp[i].bmpwin);
			}
			if(bip->memory_decord[client].exbmp_ppmax[i].bmpwin.chrbuf != NULL){
				GF_BGL_BmpWinDel(&bip->memory_decord[client].exbmp_ppmax[i].bmpwin);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�p�����[�^�̃f�[�^���������ɓW�J����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   client_type		�N���C�A���g�^�C�v
 * @param   wazapara		�Z�p�����[�^
 */
//--------------------------------------------------------------
void BINPUT_WazaParaMemoryDecord(BI_PARAM_PTR bip, int client_type, 
	const BINPUT_WAZA_PARAM *wazapara)
{
	MEMORY_DECORD_WORK *mdw;
	void *arc_data;
	NNSG2dCharacterData *char_data;
	int char_size, i, waza_type;
	STRBUF *wazaname_p;
	STRBUF *pp_p;
	STRBUF *pp_src;
	STRBUF *ppmsg_src;
	WORDSET *wordset;
	GF_PRINTCOLOR color;
	MSGDATA_MANAGER *msg_man;
	
	msg_man = BattleWorkFightMsgGet(bip->bw);
	mdw = MemoryDecordWorkGet(bip, client_type);
	
	OS_TPrintf("client_type = %d\n", client_type);
	
	char_size = APP_OamTypeToSize(WAZATYPEICON_OAMTYPE);

	ppmsg_src = MSGMAN_AllocString(msg_man, PPMsg);
	wordset = BattleWorkWORDSETGet(bip->bw);
	pp_p = STRBUF_Create(BUFLEN_BI_WAZAPP, HEAPID_BATTLE);
	pp_src = MSGMAN_AllocString(msg_man, PPNowMaxMsg);

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazapara->wazano[i] != mdw->wazapara.wazano[i] && wazapara->wazano[i] != 0){
			//�Z�^�C�v�A�C�R��
			waza_type = WT_WazaDataParaGet(wazapara->wazano[i], ID_WTD_wazatype);
			arc_data = ArcUtil_CharDataGet(WazaTypeIcon_ArcIDGet(), 
				WazaTypeIcon_CgrIDGet(waza_type), WAZATYPEICON_COMP_CHAR, 
				&char_data, HEAPID_BATTLE);
			MI_CpuCopy32(char_data->pRawData, mdw->typeicon_cgx[i], char_size);
			sys_FreeMemoryEz(arc_data);
		}
		
		if(mdw->exbmp_waza[i].bmpwin.chrbuf == NULL 
				|| (wazapara->wazano[i] != mdw->wazapara.wazano[i] && wazapara->wazano[i] != 0)){
			//BMPWIN�F�Z��
			wazaname_p = MSGDAT_UTIL_GetWazaName(wazapara->wazano[i], HEAPID_BATTLE);
			FontExBmpwin_FontSet(bip, wazaname_p, FONT_BUTTON, &mdw->exbmp_waza[i], MSGCOLOR_WAZA);
			STRBUF_Delete(wazaname_p);
		}
		
		if(mdw->exbmp_pp[i].bmpwin.chrbuf == NULL || mdw->exbmp_ppmax[i].bmpwin.chrbuf == NULL
				|| wazapara->wazano[i] != 0 || wazapara->wazano[i] != mdw->wazapara.wazano[i]
				|| wazapara->pp[i] != mdw->wazapara.pp[i]
				|| wazapara->ppmax[i] != mdw->wazapara.ppmax[i]){
			
			WORDSET_RegisterNumber(wordset, 0, wazapara->pp[i], 2, 
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_ZENKAKU);
			WORDSET_RegisterNumber(wordset, 1, wazapara->ppmax[i], 2, 
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_ZENKAKU);
			WORDSET_ExpandStr(wordset, pp_p, pp_src);
			color = PP_FontColorGet(wazapara->pp[i], wazapara->ppmax[i]);
			
			if(mdw->exbmp_pp[i].bmpwin.chrbuf == NULL
					|| wazapara->wazano[i] != mdw->wazapara.wazano[i]
					|| wazapara->pp[i] != mdw->wazapara.pp[i]){
				//BMPWIN�FPP
				FontExBmpwin_FontSet(bip, pp_p, FONT_SYSTEM, &mdw->exbmp_pp[i], color);
			}
			if(mdw->exbmp_ppmax[i].bmpwin.chrbuf == NULL
					|| wazapara->wazano[i] != mdw->wazapara.wazano[i]
					|| wazapara->pp[i] != mdw->wazapara.pp[i]){
				//BMPWIN�FPPMAX
				FontExBmpwin_FontSet(bip, ppmsg_src, FONT_SYSTEM, &mdw->exbmp_ppmax[i], color);
			}
		}
	}

	STRBUF_Delete(ppmsg_src);
	STRBUF_Delete(pp_src);
	STRBUF_Delete(pp_p);
	
	mdw->wazapara = *wazapara;
}

//--------------------------------------------------------------
/**
 * @brief   FONT_EX_BMPWIN�ɑ΂��ăt�H���g�f�[�^���쐬���A�Z�b�g����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   str				������ւ̃|�C���^
 * @param   font_type		�t�H���g�^�C�v
 * @param   ex_bmpwin		�f�[�^�����
 * @param   color			�����J���[
 */
//--------------------------------------------------------------
static void FontExBmpwin_FontSet(BI_PARAM_PTR bip, const STRBUF *str, FONT_TYPE font_type, 	
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
	GF_BGL_BmpWinObjAdd(BattleWorkGF_BGL_INIGet(bip->bw), &ex_bmp->bmpwin, char_len, 16 / 8, 0, 0);
	GF_STR_PrintExpand(&ex_bmp->bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
		PANEL_MSG_MARGIN, 0, NULL);
}


//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R����S�Đ�������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_WazaTypeIconCreateAll(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	BINPUT_SCENE_WAZA *bsw;
	int waza_type;
	int ret;
	MEMORY_DECORD_WORK *mdw;
	
	bsw = &bip->scene.bsw;
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	mdw = MemoryDecordWorkGet(bip, bip->client_type);
	
	obj_param = WazaTypeIconObjParam;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		GF_ASSERT(bip->icon_cap[i] == NULL);
		if(bsw->wazano[i] != 0){
			waza_type = WT_WazaDataParaGet(bsw->wazano[i], ID_WTD_wazatype);

			obj_param.id[CLACT_U_CHAR_RES] = CHARID_WAZATYPE_ICON_1 + i;
			obj_param.x = WazaIconPos[i][0];
			obj_param.y = WazaIconPos[i][1];
			bip->icon_cap[i] = WazaTypeIcon_ActorCreate(csp, crp, 
				waza_type, &obj_param);
			CATS_ObjectPosSetCap_SubSurface(bip->icon_cap[i], obj_param.x, obj_param.y, 
				BATTLE_SUB_ACTOR_DISTANCE);

			{//�L�����]��
				void *obj_vram;
				NNSG2dImageProxy * image;
				
				obj_vram = G2S_GetOBJCharPtr();
				image = CLACT_ImageProxyGet(bip->icon_cap[i]->act);
				MI_CpuCopy16(mdw->typeicon_cgx[i], (void*)((u32)obj_vram
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DSUB]), 
					APP_OamTypeToSize(WAZATYPEICON_OAMTYPE));
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v�A�C�R����S�č폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_WazaTypeIconDeleteAll(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(bip->icon_cap[i] != NULL){
			WazaTypeIcon_ActorDelete(bip->icon_cap[i]);
			bip->icon_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R����S�Đ�������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_WazaKindIconCreateAll(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	int waza_kind;
	BINPUT_SCENE_WAZA *bsw;

	bsw = &bip->scene.bsw;
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	obj_param = WazaKindIconObjParam;
	WazaTypeIcon_PlttWorkResourceLoad(BattleWorkPfdGet(bip->bw), FADE_SUB_OBJ, 
		csp, crp, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_WAZAKIND_ICON);
	WazaTypeIcon_CellAnmResourceLoad(csp, crp, CELLID_WAZAKIND_ICON, CELLANMID_WAZAKIND_ICON);
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		GF_ASSERT(bip->kindicon_cap[i] == NULL);
		if(bsw->wazano[i] != 0){
			waza_kind = WT_WazaDataParaGet(bsw->wazano[i], ID_WTD_kind);
			WazaKindIcon_CharResourceLoad(csp, crp, NNS_G2D_VRAM_TYPE_2DSUB, 
				waza_kind, CHARID_WAZAKIND_ICON_1 + i);
			
			obj_param.id[CLACT_U_CHAR_RES] = CHARID_WAZAKIND_ICON_1 + i;
			obj_param.x = WazaClassPos[i][0];
			obj_param.y = WazaClassPos[i][1];
			bip->kindicon_cap[i] = WazaKindIcon_ActorCreate(csp, crp, 
				waza_kind, &obj_param);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ރA�C�R����S�č폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_WazaKindIconDeleteAll(BI_PARAM_PTR bip)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(bip->kindicon_cap[i] != NULL){
			WazaKindIcon_ActorDelete(bip->kindicon_cap[i]);
			WazaKindIcon_CharResourceFree(crp, CHARID_WAZAKIND_ICON_1 + i);
			bip->kindicon_cap[i] = NULL;
		}
	}
#if 0	//�Z�^�C�v�A�C�R���̃��\�[�X���풓�ɂȂ����̂ŁA����ID���g�p���Ă��邱���������Ȃ�
	WazaKindIcon_PlttResourceFree(crp, PLTTID_WAZAKIND_ICON);
	WazaKindIcon_CellAnmResourceFree(crp, CELLID_WAZAKIND_ICON, CELLANMID_WAZAKIND_ICON);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �Z�^�C�v����CGR�f�[�^������������
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waza_type		�Z�^�C�v(�莝�������̏ꍇ��-1)
 * @param   waza_pos		�莝���̋Z�̈ʒu(0�`3)
 */
//--------------------------------------------------------------
static void Sub_WazaTypeCGRTrans(BI_PARAM_PTR bip, int waza_type, int waza_pos)
{
#if 0
	GF_BGL_INI *bgl;
	u32 screen_type;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	screen_type = GF_BGL_ScreenTypeGet(bgl, BI_FRAME_PANEL);
	
	if(waza_type == -1){	//�莝������̏ꍇ�̓f�t�H���g��OK
		WazaPanel_EasyCharLoad(bgl, waza_type, HEAPID_BATTLE, BI_FRAME_PANEL, 
			WazaTypeCgrPos[waza_pos], screen_type);
	}
#endif
	WazaPanel_EasyPalLoad(BattleWorkPfdGet(bip->bw), waza_type, HEAPID_BATTLE, FADE_SUB_BG, 
		WAZATYPE_START_PALPOS + waza_pos);
}

//--------------------------------------------------------------
/**
 * @brief   �莝�������̋Z�^�C�v����CGR�f�[�^���܂Ƃ߂ăZ�b�g
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waza_pos		�莝�������̋Z�̊J�n�ʒu(0�`3)
 */
//--------------------------------------------------------------
static void Sub_WazaTypeNotTemotiChainCGRTrans(BI_PARAM_PTR bip, int waza_pos)
{
#if 0
	GF_BGL_INI *bgl;
	u32 screen_type;
	PALETTE_FADE_PTR pfd;
	int i;
	
	pfd = BattleWorkPfdGet(bip->bw);
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	screen_type = GF_BGL_ScreenTypeGet(bgl, BI_FRAME_PANEL);
	
	WazaPanel_EasyCharLoad_ChainSet(bgl, -1, HEAPID_BATTLE, BI_FRAME_PANEL, 
		&WazaTypeCgrPos[waza_pos], WAZA_TEMOTI_MAX - waza_pos, screen_type);
	for(i = waza_pos; i < WAZA_TEMOTI_MAX; i++){
		WazaPanel_EasyPalLoad(pfd, -1, HEAPID_BATTLE, FADE_SUB_BG, 
			WAZATYPE_START_PALPOS + i);
	}
#else
	PALETTE_FADE_PTR pfd;
	int i;
	
	pfd = BattleWorkPfdGet(bip->bw);
	
	for(i = waza_pos; i < WAZA_TEMOTI_MAX; i++){
		Sub_ScrnOffsetRewrite(bip, &WazaButtonNotTouchScrnOffset[i], 
			&WazaButtonNotTouchScrnRect[i], SCRNBUF_WAZA, 0);
		PaletteWorkSet(pfd, &bip->pal_buf[BI_NOT_SELECT_PANEL_PALNO * 16], 
			FADE_SUB_BG, (WAZATYPE_START_PALPOS + i) * 16, 0x20);
	}
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �I���o���Ȃ��|�P�����̃p�l�����Z�b�g����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   poke_pos		�|�P�����̈ʒu(CLIENT_TYPE_???)
 */
//--------------------------------------------------------------
static void Sub_PokemonNotPanelTrans(BI_PARAM_PTR bip, int poke_pos)
{
	PALETTE_FADE_PTR pfd;
	int i;
	const u8 PokePalNo[] = {6, 0xc, 0xd, 5};	//CLIENT_TYPE��
	GF_BGL_INI *bgl;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	pfd = BattleWorkPfdGet(bip->bw);
	
	Sub_ScrnOffsetRewrite(bip, &PokemonButtonNotTouchScrnOffset[poke_pos], 
		&PokemonButtonNotTouchScrnRect[poke_pos], SCRNBUF_POKESELE, 0);
	PaletteWorkSet(pfd, &bip->pal_buf[BI_NOT_SELECT_PANEL_PALNO * 16], 
		FADE_SUB_BG, PokePalNo[poke_pos] * 16, 0x20);

	GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_PANEL);
	
	//�g�̍폜
	GF_BGL_ScrFill(bgl, BI_FRAME_BF, BG_CLEAR_CODE, 
		PokemonButtonNotTouchScrnRect[poke_pos].left,
		PokemonButtonNotTouchScrnRect[poke_pos].top,
		PokemonButtonNotTouchScrnRect[poke_pos].right 
		- PokemonButtonNotTouchScrnRect[poke_pos].left + 1,
		PokemonButtonNotTouchScrnRect[poke_pos].bottom 
		- PokemonButtonNotTouchScrnRect[poke_pos].top + 1,
		GF_BGL_SCRWRT_PALIN);
	GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_BF);
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�ȊO�̃t���[����S�Ĕ�\���ɂ���
 */
//--------------------------------------------------------------
static void Sub_BackScrnOnlyVisible(void)
{
	int i;
	
	for(i = 0; i < BI_BG_NUM; i++){
		if(GF_BGL_FRAME0_S + i != BI_FRAME_BACK){
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
 * @param   obj			TRUE�FOBJ�폜
 * @param   bg			TRUE�FBG�폜
 */
//--------------------------------------------------------------
static void Sub_TouchEndDelete(BI_PARAM_PTR bip, int obj, int bg)
{
	if(obj == TRUE){
		Sub_SceneOBJDelete(bip);
	}
	if(bg == TRUE){
		VWaitTCB_Add(VWait_BackScrnOnlyVisible, bip, VWAIT_TCBPRI_BACKSCRN_VISIBLE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   BG�^�C�v���؂�ւ�閈�ɍ폜����K�v�̂���OBJ��Delete����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Sub_SceneOBJDelete(BI_PARAM_PTR bip)
{
	Sub_WazaTypeIconDeleteAll(bip);
	Sub_WazaKindIconDeleteAll(bip);
	
#if SUBFONT_OAM
	Sub_FontOamDataEnableAllOff(bip);
#else
	Sub_FontOamDeleteAll(bip);
#endif

	Sub_PokeIconResourceFree(bip);
	Sub_PokeIconActorAllDel(bip);
}

//--------------------------------------------------------------
/**
 * @brief   ���ݕ\�����̃|�P�����I��BG�ŁA�ǂ̃|�P�������I���\�Ȃ̂����擾����
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   hit_range		���ʑ����(CLIENT_MAX���̔z��v�f�������[�N�̃|�C���^)
 * @param   check_exist		TRUE=�T�[�o�[����n����Ă���exist�t���O����������B
 *
 * hit_range�ɓ���l��TRUE�Ȃ�ΑI���\�AFALSE�͑I��s�ł��B
 */
//--------------------------------------------------------------
static void Sub_PokeSelectHitRange(BI_PARAM_PTR bip, u8 *hit_range, int check_exist)
{
	BINPUT_SCENE_POKE *bsp;
	int i;
	u8 client_no_buf[CLIENT_TYPE_MAX];
	int client_no;
	
	bsp = &bip->scene.bsp;
	BattleClientNoBufMake(bip->bw, client_no_buf);
	for(i = 0; i < CLIENT_MAX; i++){
		client_no = client_no_buf[CLIENT_TYPE_A + i];
		if(check_exist == TRUE && bsp->dspp[client_no].exist == FALSE){
			hit_range[i] = FALSE;
		}
		else{
			hit_range[i] = PokeSelectHitRange[bip->pokesele_type][i];
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �I�������|�P�����ƃp�l�����q�����Ă�����̂��擾����
 *
 * @param   bip					BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   target				�I�������|�P����(SELECT_TARGET_A��)
 * @param   connect_range		���ʑ����(CLIENT_MAX���̔z��v�f�������[�N�̃|�C���^)
 * @param   check_exist		TRUE=�T�[�o�[����n����Ă���exist�t���O����������B
 *
 * connect_range�ɓ���l��TRUE�Ȃ�ΐڑ��AFALSE�͐ڑ����Ă��܂���B
 */
//--------------------------------------------------------------
static void Sub_PokeSelectPanelConnectRange(BI_PARAM_PTR bip, int target, u8 *connect_range, 
	int check_exist)
{
	BINPUT_SCENE_POKE *bsp;
	int i;
	
	bsp = &bip->scene.bsp;
	switch(bip->pokesele_type){
	case POKESELE_A_B_C_D:
	case POKESELE_B_C_D:
	case POKESELE_A_B_D:
	case POKESELE_A_C:
	case POKESELE_B_D:
		for(i = 0; i < CLIENT_MAX; i++){
			if(i == target - SELECT_TARGET_A){
				connect_range[i] = TRUE;
			}
			else{
				connect_range[i] = FALSE;
			}
		}
		break;
	default:
		Sub_PokeSelectHitRange(bip, connect_range, check_exist);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ���g�̃��\�[�X�o�^
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waku_type		�g�^�C�v(WAKU_TYPE_???)
 */
//--------------------------------------------------------------
static void Waku_ResourceLoad(BI_PARAM_PTR bip, int waku_type)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int cell_id, char_id, anm_id;
	PALETTE_FADE_PTR pfd;

	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	pfd = BattleWorkPfdGet(bip->bw);
	
	char_id = WakuTypeID[waku_type][0];
	cell_id = WakuTypeID[waku_type][1];
	anm_id = WakuTypeID[waku_type][2];

	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, CHARID_BLACK_WAKU_A + waku_type);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, cell_id, 1, 
		CELLID_BLACK_WAKU_A + waku_type);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		anm_id, 1, CELLANMID_BLACK_WAKU_A + waku_type);

	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp, 
		ARC_BATT_OBJ, BATT_WAKU_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, PLTTID_BLACK_WAKU);
}

//--------------------------------------------------------------
/**
 * @brief   ���g�̃��\�[�X���
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waku_type	�g�^�C�v
 */
//--------------------------------------------------------------
static void Waku_ResourceFree(BI_PARAM_PTR bip, int waku_type)
{
	CATS_RES_PTR crp;
	
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);

	CATS_FreeResourceChar(crp, CHARID_BLACK_WAKU_A + waku_type);
	CATS_FreeResourceCell(crp, CELLID_BLACK_WAKU_A + waku_type);
	CATS_FreeResourceCellAnm(crp, CELLANMID_BLACK_WAKU_A + waku_type);
	
	CATS_FreeResourcePltt(crp, PLTTID_BLACK_WAKU);
}

//--------------------------------------------------------------
/**
 * @brief   ���g�̃A�N�^�[����
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waku_type	�g�^�C�v
 * @param   x		���WX
 * @param   y		���WY
 *
 * @retval  ���������A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CATS_ACT_PTR Waku_ActorSet(BI_PARAM_PTR bip, int waku_type, int x, int y)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	
	obj_head = BlackWakuObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = CHARID_BLACK_WAKU_A + waku_type;
	obj_head.id[CLACT_U_PLTT_RES] = PLTTID_BLACK_WAKU;
	obj_head.id[CLACT_U_CELL_RES] = CELLID_BLACK_WAKU_A + waku_type;
	obj_head.id[CLACT_U_CELLANM_RES] = CELLANMID_BLACK_WAKU_A + waku_type;
	
	cap = CATS_ObjectAdd_S(csp, crp, &obj_head);
	CATS_ObjectAffineSet(cap->act, CLACT_AFFINE_DOUBLE);	//�g�k�E�{�pON
//	CATS_ObjectObjModeSetCap(cap, GX_OAM_MODE_XLU);	//������ON
	CATS_ObjectUpdate(cap->act);
	CATS_ObjectPosSetCap_SubSurface(cap, x, y, BATTLE_SUB_ACTOR_DISTANCE);
	
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   ���g�A�N�^�[�̍폜
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   cap		���g�A�N�^�[�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Waku_ActorDel(BI_PARAM_PTR bip, CATS_ACT_PTR cap)
{
	CATS_ActorPointerDelete_S(cap);
}

//--------------------------------------------------------------
/**
 * @brief   ���g�̃��\�[�X�ƃA�N�^�[�̃Z�b�g
 *
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   waku_type	�g�^�C�v
 * @param   x			���WX
 * @param   y			���WY
 */
//--------------------------------------------------------------
static void Waku_ActorResourceSet(BI_PARAM_PTR bip, int waku_type, int x, int y)
{
	GF_ASSERT(bip->waku.cap == NULL);
	
	if(waku_type == WAKU_TYPE_NONE){
		return;
	}
	
	bip->waku.type = waku_type;
	Waku_ResourceLoad(bip, waku_type);
	bip->waku.cap = Waku_ActorSet(bip, waku_type, x, y);
	
	bip->waku.bip = bip;
	bip->waku.wait = 0;
	bip->waku.work = *((u16 *)HW_DB_BG_PLTT);	//�o�b�N�O���E���h�̐F���擾
	bip->waku.add_sp = WAKU_SP_INIT;
	TCB_Add(Waku_MoveTCB, &bip->waku, TCBPRI_BINPUT_BLACK_WAKU_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   ���g�̃��\�[�X�ƃA�N�^�[���폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Waku_ActorResourceDel(BI_PARAM_PTR bip)
{
	GF_ASSERT(bip->waku.cap != NULL);

	Waku_ResourceFree(bip, bip->waku.type);
	Waku_ActorDel(bip, bip->waku.cap);
	bip->waku.cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   ���g�g�哮��^�X�N
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void Waku_MoveTCB(TCB_PTR tcb, void *work)
{
	BLACK_WAKU_WORK *waku = work;
	
	CATS_ObjectScaleAdd(waku->cap->act, waku->add_sp, waku->add_sp);
	waku->add_sp -= WAKU_SP_SUB;
	if(waku->add_sp < 0){
		waku->add_sp = 0;
	}
//	CATS_ObjectScaleSetCap(waku->cap, 2, 2);

	//�J���[�t�F�[�h
	{
		PALETTE_FADE_PTR pfd;
		int palette_pos;
		u32 evy;
		
		pfd = BattleWorkPfdGet(waku->bip->bw);
		palette_pos = CLACT_PaletteNoGet(waku->cap->act);
		evy = ((16 << 8) / WAKU_EFF_FRAME * waku->wait + 0x0080) >> 8;
		SoftFadePfd(pfd, FADE_SUB_OBJ, palette_pos * 16, 16, evy, waku->work);
	}

	waku->wait++;
	if(waku->wait > WAKU_EFF_FRAME){
		//Waku_ActorResourceDel(waku->bip);
		TCB_Delete(tcb);
		return;
	}
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
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Add(TCB_FUNC func, BI_PARAM_PTR bip)
{
	GF_ASSERT(bip->effect_tcb == NULL);
	
	MI_CpuClear8(&bip->effect_work, sizeof(BI_EFFECT_WORK));
	bip->effect_tcb = TCB_Add(func, bip, TCBPRI_BINPUT_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �G�t�F�N�gTCB���폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void EffectTCB_Delete(BI_PARAM_PTR bip)
{
	if(bip->effect_tcb != NULL){
		TCB_Delete(bip->effect_tcb);
		bip->effect_tcb = NULL;
		MI_CpuClear8(&bip->effect_work, sizeof(BI_EFFECT_WORK));
	}
}

//--------------------------------------------------------------
/**
 * @brief   �J���[�G�t�F�N�gTCB�𐶐�����
 *
 * @param   func		TCB�ɃZ�b�g����֐��|�C���^
 * @param   bip			BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEffTCB_Add(TCB_FUNC func, BI_PARAM_PTR bip)
{
	GF_ASSERT(bip->color_eff_tcb == NULL);
	
	MI_CpuClear8(&bip->color_work, sizeof(BI_COLOR_EFF_WORK));
	bip->color_eff_tcb = TCB_Add(func, bip, TCBPRI_BINPUT_COLOR_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   �J���[�G�t�F�N�gTCB���폜����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEffTCB_Delete(BI_PARAM_PTR bip)
{
	if(bip->color_eff_tcb != NULL){
		TCB_Delete(bip->color_eff_tcb);
		bip->color_eff_tcb = NULL;
		MI_CpuClear8(&bip->color_work, sizeof(BI_COLOR_EFF_WORK));
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����I��p�̃J���[�t�F�[�h�^�X�N�𐶐�
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   tp_ret	
 */
//--------------------------------------------------------------
static void ColorEffTCB_PokeSeleFadeSet(BI_PARAM_PTR bip, int tp_ret)
{
	return;		//���点�Ȃ��悤�ɂ��� 2006.05.26(��)
	
	ColorEffTCB_Add(ColorEff_PokeSeleFade, bip);
	bip->color_work.tp_ret = tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   ����̈ʒu�̃J���[�������t�F�[�h������^�X�N�𐶐�����
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   pal_pos	�t�F�[�h������p���b�g�ԍ�
 */
//--------------------------------------------------------------
static void ColorEffTCB_PointFadeSet(BI_PARAM_PTR bip, int pal_pos)
{
	return;		//���点�Ȃ��悤�ɂ��� 2006.05.26(��)
	
	if(pal_pos == 0xff){
		return;
	}
	
	ColorEffTCB_Add(ColorEff_PointFade, bip);
	bip->color_work.pal_pos = pal_pos;
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
	BI_PARAM_PTR bip = work;
	BI_COLOR_EFF_WORK *cw;
	GF_BGL_INI *bgl;
	PALETTE_FADE_PTR pfd;
	int i, end;
	
	cw = &bip->color_work;
	pfd = BattleWorkPfdGet(bip->bw);
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
		
	#if 0
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
			ColorEffTCB_Delete(bip);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�����I��p�̃J���[�t�F�[�h�^�X�N
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ColorEff_PokeSeleFade(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	BI_COLOR_EFF_WORK *cw;
	GF_BGL_INI *bgl;
	PALETTE_FADE_PTR pfd;
	int i, end;
	u8 connect_range[CLIENT_MAX];
	
	cw = &bip->color_work;
	pfd = BattleWorkPfdGet(bip->bw);
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

		Sub_PokeSelectPanelConnectRange(bip, cw->tp_ret, connect_range, TRUE);
		for(i = 0; i < CLIENT_MAX; i++){
			if(connect_range[i] == TRUE){
			#if 0
				//�S�̂��Â�
				SoftFadePfd(pfd, FADE_SUB_BG, PokeSeleMenuPaletteNo[i] * 16, 
					16, cw->evy >> 8, 0x0000);
				//�g��������
				SoftFadePfd(pfd, FADE_SUB_BG, PokeSeleMenuPaletteNo[i] * 16 + 3, 1, 
					cw->evy >> 8, 0x7fff);
			#else
				SoftFadePfd(pfd, FADE_SUB_BG, PokeSeleMenuPaletteNo[i] * 16, 
					16, (cw->evy >> 8) / 2, 0x7fff);
				//�S�̂��Â�
				SoftFadePfd(pfd, FADE_SUB_BG, PokeSeleMenuPaletteNo[i] * 16 + 1, 
					1, cw->evy >> 8, 0x7b1a);
				//�g��������
				SoftFadePfd(pfd, FADE_SUB_BG, PokeSeleMenuPaletteNo[i] * 16 + 0xa, 1, 
					cw->evy >> 8, 0x4634);
			#endif
			}
		}
		
		if(end == TRUE){
			ColorEffTCB_Delete(bip);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���[����������
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   scrn_offset		���Z����X�N���[���l
 * @param   range			�X�N���[�����������͈�
 * @param   scrnbuf_no		���f�[�^�ƂȂ�X�N���[���o�b�t�@�̔ԍ�
 * @param   anm_no			�A�j���ԍ�
 */
//--------------------------------------------------------------
static void Sub_ScrnOffsetRewrite(BI_PARAM_PTR bip, const s16 *scrn_offset, 
	const REWRITE_SCRN_RECT *range, int scrnbuf_no, int anm_no)
{
	int x, y;
	GF_BGL_INI *bgl;
	u16 *scrn, *write_scrn;
	u16 *src_scrn, *read_scrn;
	int add_scrn;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	scrn = GF_BGL_ScreenAdrsGet(bgl, BI_FRAME_PANEL);
	src_scrn = bip->scrn_buf[scrnbuf_no];
	add_scrn = scrn_offset[anm_no];
	
	for(y = range->top; y <= range->bottom; y++){
		write_scrn = &scrn[y * 32];
		read_scrn = &src_scrn[y * 32];
		for(x = range->left; x <= range->right; x++){
			write_scrn[x] = read_scrn[x] + add_scrn;
		}
	}
	
	GF_BGL_LoadScreenV_Req(bgl, BI_FRAME_PANEL);
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
	BI_PARAM_PTR bip = work;
	GF_BGL_INI *bgl;
	int x, y;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	switch(bip->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(bip, bip->effect_work.paracgr.scrn_offset, 
			bip->effect_work.paracgr.scrn_range, bip->effect_work.paracgr.scrnbuf_no, 2);

		FONTOAM_GetMat(bip->font_actor[bip->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(bip->font_actor[bip->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_A_EFF_Y);
		
		if(bip->effect_work.paracgr.pokeicon_no != NOT_POKE_ICON
				&& bip->pokeicon_cap[bip->effect_work.paracgr.pokeicon_no] != NULL){
			CATS_ObjectPosMoveCap(bip->pokeicon_cap[bip->effect_work.paracgr.pokeicon_no], 
				0, SCRN_SCROLL_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;
	case 1:
		bip->effect_work.wait++;
		if(bip->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		
		bip->effect_work.wait = 0;
		bip->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(bip, bip->effect_work.paracgr.scrn_offset, 
			bip->effect_work.paracgr.scrn_range, bip->effect_work.paracgr.scrnbuf_no, 1);
		
		FONTOAM_GetMat(bip->font_actor[bip->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(bip->font_actor[bip->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_BACK_A_EFF_Y);

		if(bip->effect_work.paracgr.pokeicon_no != NOT_POKE_ICON
				&& bip->pokeicon_cap[bip->effect_work.paracgr.pokeicon_no] != NULL){
			CATS_ObjectPosMoveCap(bip->pokeicon_cap[bip->effect_work.paracgr.pokeicon_no], 
				0, SCRN_SCROLL_BACK_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;

	default:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(bip, TRUE, FALSE);
			EffectTCB_Delete(bip);
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
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	GF_BGL_INI *bgl;
	int x, y;
	int fa_waza, fa_pp, fa_ppmsg;
	int cap_icon, kind_icon, wazano;
	BINPUT_SCENE_WAZA *bsw;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	bsw = &bip->scene.bsw;

	switch(bip->effect_work.paracgr.tp_ret){
	case SELECT_SKILL_1:
		fa_waza = FA_NO_WAZA_1;
		fa_pp = FA_NO_PP_1;
		fa_ppmsg = FA_NO_PPMSG_1;
		cap_icon = 0;
		kind_icon = 0;
		wazano = bsw->wazano[0];
		break;
	case SELECT_SKILL_2:
		fa_waza = FA_NO_WAZA_2;
		fa_pp = FA_NO_PP_2;
		fa_ppmsg = FA_NO_PPMSG_2;
		cap_icon = 1;
		kind_icon = 1;
		wazano = bsw->wazano[1];
		break;
	case SELECT_SKILL_3:
		fa_waza = FA_NO_WAZA_3;
		fa_pp = FA_NO_PP_3;
		fa_ppmsg = FA_NO_PPMSG_3;
		cap_icon = 2;
		kind_icon = 2;
		wazano = bsw->wazano[2];
		break;
	case SELECT_SKILL_4:
		fa_waza = FA_NO_WAZA_4;
		fa_pp = FA_NO_PP_4;
		fa_ppmsg = FA_NO_PPMSG_4;
		cap_icon = 3;
		kind_icon = 3;
		wazano = bsw->wazano[3];
		break;
	case SELECT_CANCEL:
	default:
		fa_waza = 0;
		fa_pp = 0;
		fa_ppmsg = 0;
		cap_icon = 0;
		kind_icon = 0;
		wazano = 0;
		break;
	}
	
	switch(bip->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(bip, bip->effect_work.paracgr.scrn_offset, 
			bip->effect_work.paracgr.scrn_range, bip->effect_work.paracgr.scrnbuf_no, 2);

		if(bip->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(bip->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_pp].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_pp].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_ppmsg].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_ppmsg].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(bip->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				if(bip->kindicon_cap[cap_icon] != NULL){
					CATS_ObjectPosMove(bip->kindicon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				}
			}
		}
		else{
			FONTOAM_GetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;
	case 1:
		bip->effect_work.wait++;
		if(bip->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		bip->effect_work.wait = 0;
		bip->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(bip, bip->effect_work.paracgr.scrn_offset, 
			bip->effect_work.paracgr.scrn_range, bip->effect_work.paracgr.scrnbuf_no, 1);
		
		if(bip->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(bip->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_pp].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_pp].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_ppmsg].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_ppmsg].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(bip->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_BACK_A_EFF_Y);
				if(bip->kindicon_cap[cap_icon] != NULL){
					CATS_ObjectPosMove(bip->kindicon_cap[cap_icon]->act, 
						0, SCRN_SCROLL_BACK_A_EFF_Y);
				}
			}
		}
		else{
			FONTOAM_GetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;

	default:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(bip, TRUE, TRUE);
			EffectTCB_Delete(bip);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�l���������L�����]���A�j�������s���ď��������܂��B
 *          �|�P�����I����(�Z���ʔ͈�)��p�ł��B
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_PokeSeleButtonDown(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	GF_BGL_INI *bgl;
	int x, y;
	u8 connect_range[CLIENT_MAX];
	int i;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	switch(bip->effect_work.seq){
	case 0:
		Sub_PokeSelectPanelConnectRange(bip, bip->effect_work.pokesele.tp_ret, 
			connect_range, TRUE);
		
		for(i = 0; i < CLIENT_MAX; i++){
			if(connect_range[i] == TRUE){
				Sub_ScrnOffsetRewrite(bip, PokemonButtonScrnOffset[i], 
					&PokemonButtonScrnRect[i], SCRNBUF_POKESELE, 2);

				if(bip->font_actor[FA_NO_POKE_A + i].fontoam != NULL){
					FONTOAM_GetMat(bip->font_actor[FA_NO_POKE_A + i].fontoam, &x, &y);
					FONTOAM_SetMat(bip->font_actor[FA_NO_POKE_A + i].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
				}
				if(bip->pokeicon_cap[i] != NULL){
					CATS_ObjectPosMoveCap(bip->pokeicon_cap[i], 0, SCRN_SCROLL_A_EFF_Y);
				}
			}
		}
		bip->effect_work.seq++;
		break;
	case 1:
		bip->effect_work.wait++;
		if(bip->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		bip->effect_work.wait = 0;
		bip->effect_work.seq++;
		//break;

	case 2:
		Sub_PokeSelectPanelConnectRange(bip, bip->effect_work.pokesele.tp_ret, 
			connect_range, TRUE);

		for(i = 0; i < CLIENT_MAX; i++){
			if(connect_range[i] == TRUE){
				Sub_ScrnOffsetRewrite(bip, PokemonButtonScrnOffset[i], 
					&PokemonButtonScrnRect[i], SCRNBUF_POKESELE, 1);

				if(bip->font_actor[FA_NO_POKE_A + i].fontoam != NULL){
					FONTOAM_GetMat(bip->font_actor[FA_NO_POKE_A + i].fontoam, &x, &y);
					FONTOAM_SetMat(bip->font_actor[FA_NO_POKE_A + i].fontoam, 
						x, y + SCRN_SCROLL_BACK_A_EFF_Y);
				}
				if(bip->pokeicon_cap[i] != NULL){
					CATS_ObjectPosMoveCap(bip->pokeicon_cap[i], 0, SCRN_SCROLL_BACK_A_EFF_Y);
				}
			}
		}
		
		bip->effect_work.seq++;
		break;
	case 3:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			bip->effect_work.wait = 0;
			bip->effect_work.seq++;
		}
		break;

	default:
		Sub_TouchEndDelete(bip, TRUE, TRUE);
		EffectTCB_Delete(bip);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ewp�ɓ����Ă���f�[�^�����ɃX�N���[�����������G�t�F�N�g�����s����
 *          1�̃p�l���ɑ΂���1�̃t�H���gOBJ���Z�b�g�ɂȂ��Ă�����̗p�̔ėp�^�X�N�ł�
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_ScrnTouch(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	GF_BGL_INI *bgl;
	int x, y;

	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	
	switch(bip->effect_work.seq){
	case 0:
		Sub_ScrnTouchChange(bgl, bip->ewp.rsr, bip->ewp.rsr_num, bip->ewp.add_charname);

		FONTOAM_GetMat(bip->font_actor[bip->effect_work.para.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(bip->font_actor[bip->effect_work.para.fa_no].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
		
		bip->effect_work.seq++;
		break;
	case 1:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			bip->effect_work.wait = 0;
			bip->effect_work.seq++;
		}
		break;
	case 20:
		Sub_ScrnTouchChangeReverse(bgl, bip->ewp.rsr, bip->ewp.rsr_num, bip->ewp.add_charname);

		FONTOAM_GetMat(bip->font_actor[bip->effect_work.para.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(bip->font_actor[bip->effect_work.para.fa_no].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
		
		bip->effect_work.seq++;
		break;
	default:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(bip, TRUE, TRUE);
			EffectTCB_Delete(bip);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �Z�I��p�̃X�N���[�����������G�t�F�N�g�����s����
 *
 * @param   tcb		TCB�ւ̃|�C���^
 * @param   work	BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Effect_WazaScrnTouch(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	GF_BGL_INI *bgl;
	int x, y;
	int fa_waza, fa_pp, fa_ppmsg;
	int cap_icon, kind_icon, wazano;
	BINPUT_SCENE_WAZA *bsw;
	
	bgl = BattleWorkGF_BGL_INIGet(bip->bw);
	bsw = &bip->scene.bsw;
	
	switch(bip->effect_work.waza.tp_ret){
	case SELECT_SKILL_1:
		fa_waza = FA_NO_WAZA_1;
		fa_pp = FA_NO_PP_1;
		fa_ppmsg = FA_NO_PPMSG_1;
		cap_icon = 0;
		kind_icon = 0;
		wazano = bsw->wazano[0];
		break;
	case SELECT_SKILL_2:
		fa_waza = FA_NO_WAZA_2;
		fa_pp = FA_NO_PP_2;
		fa_ppmsg = FA_NO_PPMSG_2;
		cap_icon = 1;
		kind_icon = 1;
		wazano = bsw->wazano[1];
		break;
	case SELECT_SKILL_3:
		fa_waza = FA_NO_WAZA_3;
		fa_pp = FA_NO_PP_3;
		fa_ppmsg = FA_NO_PPMSG_3;
		cap_icon = 2;
		kind_icon = 2;
		wazano = bsw->wazano[2];
		break;
	case SELECT_SKILL_4:
		fa_waza = FA_NO_WAZA_4;
		fa_pp = FA_NO_PP_4;
		fa_ppmsg = FA_NO_PPMSG_4;
		cap_icon = 3;
		kind_icon = 3;
		wazano = bsw->wazano[3];
		break;
	case SELECT_CANCEL:
	default:
		fa_waza = 0;
		fa_ppmsg = 0;
		fa_pp = 0;
		cap_icon = 0;
		kind_icon = 0;
		wazano = 0;
		break;
	}
	
	switch(bip->effect_work.seq){
	case 0:
		Sub_ScrnTouchChange(bgl, bip->ewp.rsr, bip->ewp.rsr_num, bip->ewp.add_charname);

		if(bip->effect_work.waza.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(bip->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_pp].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_pp].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_ppmsg].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_ppmsg].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(bip->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				if(bip->kindicon_cap[cap_icon] != NULL){
					CATS_ObjectPosMove(bip->kindicon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				}
			}
		}
		else{
			FONTOAM_GetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;
	case 1:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			bip->effect_work.wait = 0;
			bip->effect_work.seq++;
		}
		break;
	case 20:
		Sub_ScrnTouchChangeReverse(bgl, bip->ewp.rsr, bip->ewp.rsr_num, bip->ewp.add_charname);

		if(bip->effect_work.waza.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(bip->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_pp].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_pp].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(bip->font_actor[fa_ppmsg].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[fa_ppmsg].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(bip->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				if(bip->kindicon_cap[cap_icon] != NULL){
					CATS_ObjectPosMove(bip->kindicon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				}
			}
		}
		else{
			FONTOAM_GetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, &x, &y);
			FONTOAM_SetMat(bip->font_actor[FA_NO_WAZA_MODORU].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
		}
		
		bip->effect_work.seq++;
		break;
	default:
		bip->effect_work.wait++;
		if(bip->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(bip, TRUE, TRUE);
			EffectTCB_Delete(bip);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   PP�̕\���F���擾����
 *
 * @param   pp			���݂�PP
 * @param   pp_max		�ő�PP
 *
 * @retval  �J���[
 */
//--------------------------------------------------------------
static GF_PRINTCOLOR PP_FontColorGet(int pp, int pp_max)
{
	if(pp == 0){
		return MSGCOLOR_PP_RED;
	}
	if(pp_max == pp){
		return MSGCOLOR_PP_BLACK;
	}
	if(pp_max <= 2){
		if(pp == 1){
			return MSGCOLOR_PP_ORANGE;
		}
	}
	else if(pp_max <= 7){
		switch(pp){
		case 1:
			return MSGCOLOR_PP_ORANGE;
		case 2:
			return MSGCOLOR_PP_YELLOW;
		}
	}
	else{
		if(pp <= pp_max / 4){
			return MSGCOLOR_PP_ORANGE;
		}
		if(pp <= pp_max / 2){
			return MSGCOLOR_PP_YELLOW;
		}
	}
	return MSGCOLOR_PP_BLACK;
}



//==============================================================================
//
//	�R�}���h�I����ʃX�N���[���C���G�t�F�N�g
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �R�}���h�I����ʁF�X�N���[���C���G�t�F�N�g���s�^�X�N
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void CommandInEffTask(TCB_PTR tcb, void *work)
{
	COMMAND_IN_EFF_WORK *ciew = work;
	GF_BGL_INI *bgl;
	
	bgl = BattleWorkGF_BGL_INIGet(ciew->bip->bw);
	
	switch(ciew->seq){
	case 0:
		ciew->x0_l += COMMANDIN_SCR_X0_ADD;
		ciew->y1_d -= COMMANDIN_SCR_Y1_ADD;
		ciew->set_x0_l = (COMMANDIN_SCR_X0_START - ciew->x0_l) / 100;
		ciew->set_y1_d = -ciew->y1_d / 100;
		
		if(ciew->x0_l >= COMMANDIN_WND_START_X0 || ciew->y1_d <= COMMANDIN_WND_START_Y0){
			ciew->x0_l = COMMANDIN_WND_START_X0;
			ciew->y1_d = COMMANDIN_WND_START_Y1;
			ciew->set_x0_l = COMMANDIN_WND_START_X0 / 100;
			ciew->set_y1_d = COMMANDIN_WND_START_Y0 / 100;
			ciew->seq++;
		}

		break;
		
	case 1:
		ciew->bip->touch_invalid = FALSE;
		TCB_Delete(ciew->vtask_tcb);
		sys_HBlankIntrStop();
		GXS_SetVisibleWnd(GX_WNDMASK_NONE);
		
		BINPUT_BackFadeReq(ciew->bip, BINPUT_BACKFADE_DARK);
		ciew->seq++;
		break;
	default:
		if(BINPUT_BackFadeExeCheck(ciew->bip) == FALSE){
			break;
		}
		
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_Y_SET, 0);

		BattleWorkCommandSelectFlagSet(ciew->bip->bw, SLIDE_IN_AFTER);

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R�}���h�I����ʃX�N���[���C���G�t�F�N�g�FV�u�����N�]���^�X�N
 *
 * @param   tcb		
 * @param   work		
 */
//--------------------------------------------------------------
static void VBlankTCB_CommandInEff(TCB_PTR tcb, void *work)
{
	COMMAND_IN_EFF_WORK *ciew = work;
	GF_BGL_INI *bgl;
	s32 set_x, set_y, x;
	
	bgl = BattleWorkGF_BGL_INIGet(ciew->bip->bw);
	
	if(ciew->client_type == CLIENT_TYPE_C){
		x = 255 - ciew->set_x0_l;
		if(x > 0){
			x = 0;
		}
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, x);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, 255 - ciew->set_x0_l);
		set_x = -ciew->x0_l / 100;
	}
	else{
		x = ciew->set_x0_l;
		if(x < 0){
			x = 0;
		}
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, x);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, ciew->set_x0_l);
		set_x = COMMANDIN_WND_END_X0 + ciew->x0_l / 100;
	}
	GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_Y_SET, 0);
	GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_Y_SET, 0);

	set_y = COMMANDIN_WND_START_Y1 + (ciew->y1_d) / 100;
	if(set_x < 0){
		set_x = 0;
	}
	else if(set_x > 255){
		set_x = 255;
	}
	if(set_y > 192){
		set_y = 192;
	}
	else if(set_y < 0){
		set_y = 0;
	}
	
	if(ciew->client_type == CLIENT_TYPE_C){
		G2S_SetWnd0Position(COMMANDIN_WND_START_X0, COMMANDIN_WND_START_Y0, 
			set_x, COMMANDIN_WND_END_Y0);
	}
	else{
		if(set_x == 0){
			set_x = 1;	//RIGHT��0�n�܂�ɂ��āA�E�[����͂��Ă���ׂ̃P�A
		}
		G2S_SetWnd0Position(set_x, COMMANDIN_WND_START_Y0, 
			0/*COMMANDIN_WND_END_X0*/, COMMANDIN_WND_END_Y0);
	}
	G2S_SetWnd1Position(COMMANDIN_WND_START_X1, COMMANDIN_WND_START_Y1, 
		COMMANDIN_WND_END_X0, set_y);
		
	ciew->h_set_y1_d = ciew->set_y1_d;
}

//--------------------------------------------------------------
/**
 * @brief   �R�}���h�I����ʃX�N���[���C���G�t�F�N�g�FH�u�����N���荞�݊֐�
 *
 * @param   work		
 */
//--------------------------------------------------------------
static void HBlank_CommandInEff(void *work)
{
	COMMAND_IN_EFF_WORK *ciew = work;
	s32 vcount, x;
	
	vcount = GX_GetVCount();
	if(vcount == COMMANDIN_WND_START_Y1){
		GF_BGL_INI *bgl = BattleWorkGF_BGL_INIGet(ciew->bip->bw);
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, COMMANDIN_WND_START_X1);
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_Y_SET, ciew->h_set_y1_d);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, COMMANDIN_WND_START_X1);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_Y_SET, ciew->h_set_y1_d);
	}
	else if(vcount > 192){
		GF_BGL_INI *bgl = BattleWorkGF_BGL_INIGet(ciew->bip->bw);
		if(ciew->client_type == CLIENT_TYPE_C){
			x = 255 - ciew->set_x0_l;
			if(x > 0){
				x = 0;
			}
			GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, 255 - ciew->set_x0_l);
			GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, 255 - ciew->set_x0_l);
		}
		else{
			x = ciew->set_x0_l;
			if(x < 0){
				x = 0;
			}
			GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_X_SET, ciew->set_x0_l);
			GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_X_SET, ciew->set_x0_l);
		}
		GF_BGL_ScrollSet(bgl, BI_FRAME_PANEL, GF_BGL_SCROLL_Y_SET, 0);
		GF_BGL_ScrollSet(bgl, BI_FRAME_BF, GF_BGL_SCROLL_Y_SET, 0);
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
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	const BG_MAKE_DATA *bmd;
	int i;

	bmd = &BgMakeData[bip->makedata_no];
	
	//�eBG�ʂ̕\���E��\���ݒ�
	for(i = 0; i < BI_BG_NUM; i++){
		if(bmd->scr_id[i] == NONE_ID){
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		}
		else{
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_ON);
		}
	}

	//�eBG�ʂ�BG�v���C�I���e�B�X�V
	for(i = 0; i < BI_BG_NUM; i++){
		GF_BGL_PrioritySet(GF_BGL_FRAME0_S + i, bmd->pri[i]);
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
	BI_PARAM_PTR bip = work;

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
//	�w�i�t�F�[�h
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �퓬���͉�ʁA�w�i�t�F�[�h���N�G�X�g
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   fade_dir		BINPUT_BACKFADE_???
 */
//--------------------------------------------------------------
void BINPUT_BackFadeReq(BI_PARAM_PTR bip, int fade_dir)
{
#if 0	//�t�F�[�h�Ȃ��Ȃ��� 2006.05.19(��)
	if(bip->backfade_flag == fade_dir){
		return;		//���Ƀ��N�G�X�g������ԂɂȂ��Ă���
	}

	if(bip->backfade_tcb != NULL){
		GF_ASSERT(0 && "�w�i�t�F�[�h�̃��N�G�X�g�����ɓ��쒆�ł��I\n");
		return;
	}
	
	bip->backfade_seq = 0;
	bip->backfade_flag = fade_dir;
	bip->backfade_tcb = TCB_Add(BackFadeTask, bip, TCBPRI_BINPUT_BACKFADE);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�t�F�[�h���s�^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BackFadeTask(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	
	switch(bip->backfade_seq){
	case 0:
		if(bip->backfade_flag == BINPUT_BACKFADE_DARK){
			PaletteFadeReq(BattleWorkPfdGet(bip->bw), PF_BIT_SUB_BG, BACKFADE_FADEBIT, 
				BACKFADE_FADE_WAIT, 0, BACKFADE_EVY, BACKFADE_COLOR);
		}
		else{
			PaletteFadeReq(BattleWorkPfdGet(bip->bw), PF_BIT_SUB_BG, BACKFADE_FADEBIT, 
				BACKFADE_FADE_WAIT, BACKFADE_EVY, 0, BACKFADE_COLOR);
		}
		bip->backfade_seq++;
		break;
	default:
		if(PaletteFadeCheck(BattleWorkPfdGet(bip->bw)) == 0){
			bip->backfade_seq = 0;
			TCB_Delete(tcb);
			bip->backfade_tcb = NULL;
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w�i�t�F�[�h�����s����Ă��邩�m�F
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I�����Ă���B�@FALSE:�����Ă���
 */
//--------------------------------------------------------------
BOOL BINPUT_BackFadeExeCheck(BI_PARAM_PTR bip)
{
	if(bip->backfade_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}

///�풓�t�F�[�h��EVY�ő�l
#define DEF_FADE_EVY_MAX			(10)
///�풓�t�F�[�h��EVY���Z�l
#define DEF_FADE_EVY_ADD			(0x0080)
///�풓�t�F�[�h�̃J���[�R�[�h
#define DEF_FADE_COLOR				(0x7b1a)

///�풓�t�F�[�h�F�g��EVY�ő�l
#define DEF_FADE_WAKU_EVY_MAX		(16)
///�풓�t�F�[�h�F�g��EVY���Z�l
#define DEF_FADE_WAKU_EVY_ADD		(0x0200)
///�풓�t�F�[�h�F�g�̃J���[�R�[�h
#define DEF_FADE_WAKU_COLOR			(0x7fff)
//--------------------------------------------------------------
/**
 * @brief   �풓�t�F�[�h���s�^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DefaultFadeAnimeTask(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	int i;
	u16 color;
	PALETTE_FADE_PTR pfd;
	s16 evy;
	
	pfd = BattleWorkPfdGet(bip->bw);
	
	if(PaletteFadeCheck(pfd) != 0){
		return;		//�S�̃t�F�[�h���͎��s���Ȃ�
	}

#if 0		//��ʑS�̃t�F�[�h��~ 2006.05.12(��)
	color = DEF_FADE_COLOR;
	evy = bip->def_fade_evy >> 8;
	
	//�p���b�g���f
	for(i = 1; i < 7; i++){
		SoftFadePfd(pfd, FADE_SUB_BG, 16 * i + 0xa, 1, evy, color);
	}
	for(i = 8; i < 0xf; i++){
		SoftFadePfd(pfd, FADE_SUB_BG, 16 * i + 0xa, 1, evy, color);
	}
	
	//EVY�X�V
	if(bip->def_fade_dir == 0){
		bip->def_fade_evy += DEF_FADE_EVY_ADD;
	}
	else{
		bip->def_fade_evy -= DEF_FADE_EVY_ADD;
	}
	if(bip->def_fade_evy >= (DEF_FADE_EVY_MAX+1) << 8){
		bip->def_fade_evy = (DEF_FADE_EVY_MAX-1) << 8;
		bip->def_fade_dir = 1;
	}
	else if(bip->def_fade_evy <= 0){
		bip->def_fade_evy = 1 << 8;
		bip->def_fade_dir = 0;
	}
#endif
	
	//-- �|�P�����I����ʂ݂̂̏풓�t�F�[�h --//
	{
		SoftFadePfd(pfd, FADE_SUB_BG, 16 * 0 + 1, 1, bip->waku_fade_evy >> 8, DEF_FADE_WAKU_COLOR);
		//EVY�X�V
		if(bip->waku_fade_dir == 0){
			bip->waku_fade_evy += DEF_FADE_WAKU_EVY_ADD;
		}
		else{
			bip->waku_fade_evy -= DEF_FADE_WAKU_EVY_ADD;
		}
		if(bip->waku_fade_evy >= (DEF_FADE_WAKU_EVY_MAX+1) << 8){
			bip->waku_fade_evy = (DEF_FADE_WAKU_EVY_MAX-1) << 8;
			bip->waku_fade_dir = 1;
		}
		else if(bip->waku_fade_evy <= 0){
			bip->waku_fade_evy = 1 << 8;
			bip->waku_fade_dir = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �^�b�`����Ă��鎞�͔w�i�̃p���b�g���p�̃p���b�g�ɕύX����
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void BackGroundTouchPaletteCheck(TCB_PTR tcb, void *work)
{
	BI_PARAM_PTR bip = work;
	PALETTE_FADE_PTR pfd;
	u16 *trans_wk;
	int size;
	int msg_skip, msg_wait;
	
	msg_skip = MsgPrintBattleSkipPushFlagGet();
	msg_wait = MsgPrintBattleWaitPushFlagGet();
	MsgPrintBattleSkipPushFlagClear();
	MsgPrintBattleWaitPushFlagClear();
	
	pfd = BattleWorkPfdGet(bip->bw);
	if(PaletteFadeCheck(pfd) != 0){
		return;
	}
	
	trans_wk = PaletteWorkTransWorkGet(pfd, FADE_SUB_BG);
	size = (16 - BACKGROUND_CHANGE_PAL_START) * 2;
	if(sys.tp_cont && (msg_skip == 1 || msg_wait == 1)){
		if(memcmp(&trans_wk[BACKGROUND_CHANGE_PAL_START], 
				&bip->background_pal_normal[BACKGROUND_CHANGE_PAL_START], size) == 0){
			MI_CpuCopy16(&bip->background_pal_touch[BACKGROUND_CHANGE_PAL_START], 
				&trans_wk[BACKGROUND_CHANGE_PAL_START], size);
		}
	}
	else{
		if(memcmp(&trans_wk[BACKGROUND_CHANGE_PAL_START], 
				&bip->background_pal_touch[BACKGROUND_CHANGE_PAL_START], size) == 0){
			MI_CpuCopy16(&bip->background_pal_normal[BACKGROUND_CHANGE_PAL_START], 
				&trans_wk[BACKGROUND_CHANGE_PAL_START], size);
		}
	}
}


//==============================================================================
//
//	�L�[����
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �L�[���͔��菈��
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorCheck(BI_PARAM_PTR bip)
{
	CURSOR_MOVE *move;
	const BG_MAKE_DATA *bmd;

	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	
	if(bmd->cursor_move_func == NULL){
		return RECT_HIT_NONE;
	}
	
	if(move->cursor_on == FALSE){
		if(bip->decend_key == TRUE || 
				(sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y
				|PAD_KEY_RIGHT|PAD_KEY_LEFT|PAD_KEY_UP|PAD_KEY_DOWN))){
			if(bip->decend_key == FALSE){
				Snd_SePlay(BCURSOR_MOVE_SE);	//�L�[�������ăJ�[�\����\������������炷
			}
			move->cursor_on = TRUE;
			bip->decend_key = FALSE;
			bmd->cursor_move_func(bip, TRUE);
		}
		return RECT_HIT_NONE;
	}
	
	return bmd->cursor_move_func(bip, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F�R�}���h�I��
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_CommandSelect(BI_PARAM_PTR bip, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int i, index, client_no;
	CURSOR_SAVE *cursor_save;
	
	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	client_no = BattleWorkClientNoGet(bip->bw, bip->client_type);
	cursor_save = CT_CursorSavePtrGet(BattleWorkClientParamGet(bip->bw, client_no));
	
	if(init_flag == TRUE){
		move->x_menu = cursor_save->command_x;
		move->y_menu = cursor_save->command_y;
		index = CursorMoveDataCommandSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}
	
	switch(bip->makedata_no){
	case BINPUT_TYPE_FIGHTONLY:
	case BINPUT_COMMAND_IN_FIGHTONLY:
		key = CursorMove_KeyCheckMove(move, 
			CURSOR_COMMAND_FIGHTONLY_X_MENU_NUM, CURSOR_COMMAND_FIGHTONLY_Y_MENU_NUM,
			CursorMoveDataCommandSelect[0]);
		break;
	default:
		index = CursorMoveDataCommandSelect[move->y_menu][move->x_menu];
		if(index == COMMSELE_INDEX_ESCAPE && (sys.trg & PAD_KEY_UP)){
			;	//�u�ɂ���v�ɃJ�[�\���������Ă��鎞�́h��L�[�h�͖���
		}
		else{
			key = CursorMove_KeyCheckMove(move, 
				CURSOR_COMMAND_SELECT_X_MENU_NUM, CURSOR_COMMAND_SELECT_Y_MENU_NUM,
				CursorMoveDataCommandSelect[0]);
			if(key == 0 && index == COMMSELE_INDEX_FIGHT){
				//�u���������v�ɃJ�[�\���������Ă���ꍇ�A���E�L�[����������|�P�����A�o�b�O�֍s��
				if(sys.trg & PAD_KEY_LEFT){
					move->x_menu = 0;
					move->y_menu = 1;
					Snd_SePlay(BCURSOR_MOVE_SE);
					key = PAD_KEY_LEFT;
				}
				else if(sys.trg & PAD_KEY_RIGHT){
					move->x_menu = 2;
					move->y_menu = 1;
					Snd_SePlay(BCURSOR_MOVE_SE);
					key = PAD_KEY_RIGHT;
				}
			}
		}
	#if 0	//3�i�ځu�ɂ���v�̏����͂Ȃ��Ȃ��� 2006.06.29(��)
		if(move->y_menu == 2){
			//3�i�ڂ́u�ɂ���v�ɃJ�[�\�����ړ������ꍇ��2�i�ڂ̐��K�̏ꏊ��
			//�u�ɂ���v�ɃJ�[�\�����ړ�������
			move->y_menu = 1;
			move->x_menu = 1;
		}
	#endif
		break;
	}
	
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataCommandSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataCommandSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		if(bip->command_modoru_type == TRUE){
			for(i = 0; i < bmd->tpd[i].rect.top != RECT_HIT_END; i++){
				if(SELECT_ESCAPE_COMMAND == bmd->tpd_ret[i]){
					return i;
				}
			}
		}
		break;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ʒu�ۑ��F�R�}���h�I��
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   index			�I����������
 */
//--------------------------------------------------------------
static void CursorSave_CommandSelect(BI_PARAM_PTR bip, int index)
{
	CURSOR_SAVE *cursor_save;
	int client_no, x, y;
	
	client_no = BattleWorkClientNoGet(bip->bw, bip->client_type);
	if(index != COMMSELE_INDEX_ESCAPE || BattleWorkEscCanCheck(bip->bw, client_no) == FALSE){
		cursor_save = CT_CursorSavePtrGet(BattleWorkClientParamGet(bip->bw, client_no));
		for(y = 0; y < CURSOR_COMMAND_SELECT_Y_MENU_NUM; y++){
			for(x = 0; x < CURSOR_COMMAND_SELECT_X_MENU_NUM; x++){
				if(index == CursorMoveDataCommandSelect[y][x]){
					cursor_save->command_x = x;
					cursor_save->command_y = y;
					return;
				}
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F�|�P�p�[�N�p�R�}���h�I��
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_ParkCommandSelect(BI_PARAM_PTR bip, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int i, index;
	
	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	
	if(init_flag == TRUE){
		move->x_menu = 0;
		move->y_menu = 0;
		index = CursorMoveDataParkCommandSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}
	
	key = CursorMove_KeyCheckMove(move, 
		CURSOR_PARK_COMMAND_SELECT_X_MENU_NUM, CURSOR_PARK_COMMAND_SELECT_Y_MENU_NUM,
		CursorMoveDataParkCommandSelect[0]);
	
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataParkCommandSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataParkCommandSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		break;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F�Z�I��
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_WazaSelect(BI_PARAM_PTR bip, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;
	u8 move_data[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM];
	BINPUT_SCENE_WAZA *bsw;
	CURSOR_SAVE *cursor_save;

	cursor_save = CT_CursorSavePtrGet(
		BattleWorkClientParamGet(bip->bw, BattleWorkClientNoGet(bip->bw, bip->client_type)));
	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	bsw = &bip->scene.bsw;
	
	if(init_flag == TRUE){
		move->x_menu = cursor_save->waza_x;
		move->y_menu = cursor_save->waza_y;
		index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		if(index != WAZASELE_INDEX_CANCEL && bsw->wazano[index - WAZASELE_INDEX_SKILL_1] == 0){
			cursor_save->waza_x = 0;
			cursor_save->waza_y = 0;
			move->x_menu = 0;
			move->y_menu = 0;
			index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		}
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	MI_CpuCopy8(CursorMoveDataWazaSelect, move_data, 
		CURSOR_WAZA_SELECT_Y_MENU_NUM * CURSOR_WAZA_SELECT_X_MENU_NUM);
#if 0	//�莝���Z���Ȃ��ꏊ���J�[�\�����ړ��o����悤�ɕύX 2006.05.27(�y)
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(bsw->wazano[i] == 0){
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
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		for(i = 0; i < bmd->tpd[i].rect.top != RECT_HIT_END; i++){
			if(SELECT_CANCEL == bmd->tpd_ret[i]){
				return i;
			}
		}
		break;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ʒu�ۑ��F�Z�I��
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   index			�I����������
 */
//--------------------------------------------------------------
static void CursorSave_WazaSelect(BI_PARAM_PTR bip, int index)
{
	CURSOR_SAVE *cursor_save;
	int client_no, x, y;

	if(index == WAZASELE_INDEX_CANCEL){
		return;
	}
	
	client_no = BattleWorkClientNoGet(bip->bw, bip->client_type);
	cursor_save = CT_CursorSavePtrGet(BattleWorkClientParamGet(bip->bw, client_no));
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
 * @brief   �J�[�\���ړ��F�|�P�����I��
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_PokeSelect(BI_PARAM_PTR bip, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int i, index;
	int plural = FALSE;
	u8 hit_range[CLIENT_MAX], connect_range[CLIENT_MAX];
	u8 move_data[CURSOR_POKE_SELECT_Y_MENU_NUM][CURSOR_POKE_SELECT_X_MENU_NUM];
	int y, x, x_menu_num, y_menu_num;
	int left, right, top, bottom, ex_x, ex_y;
	int first_top, first_bottom, first_left, first_right;
	int second_top, second_bottom, second_left, second_right;
	int l_bottom, r_bottom;
	BCURSOR_ANMTYPE ex_anm;
	CURSOR_SAVE *cursor_save;

	cursor_save = CT_CursorSavePtrGet(
		BattleWorkClientParamGet(bip->bw, BattleWorkClientNoGet(bip->bw, bip->client_type)));
	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	
	MI_CpuCopy8(CursorMoveDataPokeSelect, move_data, 
		CURSOR_POKE_SELECT_Y_MENU_NUM * CURSOR_POKE_SELECT_X_MENU_NUM);
	Sub_PokeSelectHitRange(bip, hit_range, TRUE);
	Sub_PokeSelectHitRange(bip, connect_range, FALSE);
	
	for(y = 0; y < 2;y ++){
		for(x = 0; x < 2; x++){
		#if 0
			//if(hit_range[move_data[y][x]] == FALSE){
		#else	//����ł��鏊�ł��J�[�\���ړ��o����悤�ɂ��Ȃ��ƁA�Ⴆ�΁A
				//CLIENT_TYPE_B,C,D�ɒP���I���o����ꍇ�AB�����S���Ă����
				//�����J�[�\���ʒu��D�̏ꍇ�AC�ɃJ�[�\�������킹�鎖���o���Ȃ��Ȃ�
			if(connect_range[move_data[y][x]] == FALSE){
		#endif
				//MoveData�őI���o���Ȃ��ꏊ��0xff�Ŗ��߂�
				move_data[y][x] = 0xff;
			}
		}
	}
	
	switch(bip->pokesele_type){
	//�P���I��
	default:
	case POKESELE_A_B_C_D:
	case POKESELE_A:
	case POKESELE_C:
	case POKESELE_B_C_D:
	case POKESELE_A_B_D:
	case POKESELE_A_C:
	case POKESELE_B_D:
		x_menu_num = CURSOR_POKE_SELECT_X_MENU_NUM;
		y_menu_num = CURSOR_POKE_SELECT_Y_MENU_NUM;
		break;
	
	//�����I��
	case POKESELE_BD:
	case POKESELE_BCD:
	case POKESELE_ABCD:
	case POKESELE_AC:
	case POKESELE_ABD:
		plural = TRUE;
		x_menu_num = 1;
		y_menu_num = 2;
		//��i���W
		if(connect_range[CLIENT_TYPE_D - CLIENT_TYPE_A] == TRUE 
				&& connect_range[CLIENT_TYPE_B - CLIENT_TYPE_A] == TRUE){
			first_left = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.left+8;
			first_right = bmd->tpd[POKESELE_INDEX_TARGET_B].rect.right-8;
			first_top = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.top+8;
			first_bottom = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.bottom-8;
		}
		else if(connect_range[CLIENT_TYPE_D - CLIENT_TYPE_A] == TRUE 
				&& connect_range[CLIENT_TYPE_B - CLIENT_TYPE_A] == FALSE){
			first_left = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.left+8;
			first_right = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.right-8;
			first_top = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.top+8;
			first_bottom = bmd->tpd[POKESELE_INDEX_TARGET_D].rect.bottom-8;
		}
		else if(connect_range[CLIENT_TYPE_D - CLIENT_TYPE_A] == FALSE 
				&& connect_range[CLIENT_TYPE_B - CLIENT_TYPE_A] == TRUE){
			first_left = bmd->tpd[POKESELE_INDEX_TARGET_B].rect.left+8;
			first_right = bmd->tpd[POKESELE_INDEX_TARGET_B].rect.right-8;
			first_top = bmd->tpd[POKESELE_INDEX_TARGET_B].rect.top+8;
			first_bottom = bmd->tpd[POKESELE_INDEX_TARGET_B].rect.bottom-8;
		}
		else{
			first_left = -1;
			first_right = -1;
			first_top = -1;
			first_bottom = -1;
		}
		//���i���W
		if(connect_range[CLIENT_TYPE_A - CLIENT_TYPE_A] == TRUE 
				&& connect_range[CLIENT_TYPE_C - CLIENT_TYPE_A] == TRUE){
			second_left = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.left+8;
			second_right = bmd->tpd[POKESELE_INDEX_TARGET_C].rect.right-8;
			second_top = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.top+8;
			second_bottom = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.bottom-8;
		}
		else if(connect_range[CLIENT_TYPE_A - CLIENT_TYPE_A] == TRUE 
				&& connect_range[CLIENT_TYPE_C - CLIENT_TYPE_A] == FALSE){
			second_left = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.left+8;
			second_right = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.right-8;
			second_top = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.top+8;
			second_bottom = bmd->tpd[POKESELE_INDEX_TARGET_A].rect.bottom-8;
		}
		else if(connect_range[CLIENT_TYPE_A - CLIENT_TYPE_A] == FALSE 
				&& connect_range[CLIENT_TYPE_C - CLIENT_TYPE_A] == TRUE){
			second_left = bmd->tpd[POKESELE_INDEX_TARGET_C].rect.left+8;
			second_right = bmd->tpd[POKESELE_INDEX_TARGET_C].rect.right-8;
			second_top = bmd->tpd[POKESELE_INDEX_TARGET_C].rect.top+8;
			second_bottom = bmd->tpd[POKESELE_INDEX_TARGET_C].rect.bottom-8;
		}
		else{
			second_left = -1;
			second_right = -1;
			second_top = -1;
			second_bottom = -1;
		}
		//��`���W��EX���W�����߂�
		ex_x = -1;
		ex_y = -1;
		l_bottom = -1;
		r_bottom = -1;
		//��
		if(first_left == second_left){
			left = first_left;
		}
		else if(first_left != -1 && second_left == -1){
			left = first_left;
		}
		else if(first_left == -1 && second_left != -1){
			left = second_left;
		}
		else{
			left = first_left;
			ex_x = second_left;
			ex_anm = BCURSOR_ANMTYPE_LD;
		}
		//�E
		if(first_right == second_right){
			right = first_right;
		}
		else if(first_right != -1 && second_right == -1){
			right = first_right;
		}
		else if(first_right == -1 && second_right != -1){
			right = second_right;
		}
		else{
			right = first_right;
			ex_x = second_right;
			ex_anm = BCURSOR_ANMTYPE_RD;
		}
		//��
		if(first_top != -1 && second_top == -1){
			top = first_top;
		}
		else if(first_top == -1 && second_top != -1){
			top = second_top;
		}
		else{
			top = first_top;
			ex_y = first_bottom;
		}
		//��
		if(first_bottom != -1 && second_bottom == -1){
			bottom = first_bottom;
		}
		else if(first_bottom == -1 && second_bottom != -1){
			bottom = second_bottom;
		}
		else{
			bottom = second_bottom;
			ex_y = second_bottom;
			if(ex_anm == BCURSOR_ANMTYPE_LD){
				r_bottom = first_bottom;
			}
			else{
				l_bottom = first_bottom;
			}
		}
		break;
	}
	
	if(init_flag == TRUE){
		if(plural == FALSE){
			//�J�[�\�������ʒu����(��check �ŏI�I�ɂ͎d�l���ɂ���ʂ�A�Z���̃f�t�H���g�I���ʒu��
			//�T�[�o�[������炤�悤�ɂ��Ȃ��Ƒʖ�)
			if(cursor_save->poke_save_type == bip->pokesele_type){//bip->makedata_no){
				move->x_menu = cursor_save->poke_x;
				move->y_menu = cursor_save->poke_y;
			}
			else if(hit_range[CLIENT_TYPE_D - CLIENT_TYPE_A] == TRUE){
				move->x_menu = 0;
				move->y_menu = 0;
			}
			else if(hit_range[CLIENT_TYPE_B - CLIENT_TYPE_A] == TRUE){
				move->x_menu = 1;
				move->y_menu = 0;
			}
			else if(hit_range[CLIENT_TYPE_A - CLIENT_TYPE_A] == TRUE){
				move->x_menu = 0;
				move->y_menu = 1;
			}
			else{// if(hit_range[CLIENT_TYPE_C - CLIENT_TYPE_A] == TRUE){
				move->x_menu = 1;
				move->y_menu = 1;
			}
			index = CursorMoveDataPokeSelect[move->y_menu][move->x_menu];
			BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
				bmd->tpd[index].rect.right-8, 
				bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
				BATTLE_SUB_ACTOR_DISTANCE);
		}
		else{
		#if 0
			if(cursor_save->poke_save_type == bip->pokesele_type){//bip->makedata_no){
				move->x_menu = cursor_save->poke_x;
				move->y_menu = cursor_save->poke_y;
				if(top == second_top && move->y_menu > 0){
					move->y_menu = 0;
				}
			}
			else{
				move->x_menu = 0;
				move->y_menu = 0;
			}
		#else
			//�����I���̎���1�ӏ��̑ΏۑI���Ɓu���ǂ�v�����Ȃ̂ŁA�J�[�\���L�����Ӗ��Ȃ��̂�
			//0�Œ�ɂ���B�ނ���J�[�\���L�����P���I��p�ɂȂ��Ă���̂ō��̂܂܋L���ʒu
			//���̗p����ƕs����o�� 2006.07.07(��)
			move->x_menu = 0;
			move->y_menu = 0;
		#endif
			OS_TPrintf("move->x_menu = %d, move->y_menu = %d\n", move->x_menu, move->y_menu);
			OS_TPrintf("first_bottom = %d, second_bottom = %d, r_bottom = %d, l_bottom = %d\n",
				first_bottom, second_bottom, r_bottom, l_bottom);
			OS_TPrintf("ex_x = %d, \n", ex_x);
			if((r_bottom == -1 && l_bottom == -1) || ex_x == -1){
				BCURSOR_PosSetON_Surface(bip->cursor, left, right, top, bottom,
					BATTLE_SUB_ACTOR_DISTANCE);
			}
			else if(r_bottom != -1 && l_bottom == -1){
				BCURSOR_IndividualPosSetON_Surface(bip->cursor, left, top, right, top, 
					left, r_bottom, right, bottom, BATTLE_SUB_ACTOR_DISTANCE);
			}
			else{
				BCURSOR_IndividualPosSetON_Surface(bip->cursor, left, top, right, top, 
					left, bottom, right, l_bottom, BATTLE_SUB_ACTOR_DISTANCE);
			}
			if(ex_x != -1){
				BCURSOR_ExPosSetON_Surface(bip->cursor, ex_x, ex_y, ex_anm, 
					BATTLE_SUB_ACTOR_DISTANCE);
			}
		}
		return RECT_HIT_NONE;
	}
	
	if(plural == FALSE){
		key = CursorMove_KeyCheckMove(move, x_menu_num, y_menu_num, move_data[0]);
	}
	else{
		key = CursorMove_KeyCheckMove(move, x_menu_num, y_menu_num, NULL);
	}
	
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		if(plural == FALSE){
			index = CursorMoveDataPokeSelect[move->y_menu][move->x_menu];
			BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
				bmd->tpd[index].rect.right-8, 
				bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
				BATTLE_SUB_ACTOR_DISTANCE);
		}
		else{
			if(move->y_menu == 0){
				if((l_bottom == -1 && r_bottom == -1) || ex_x == -1){
					BCURSOR_PosSetON_Surface(bip->cursor, left, right, top, bottom,
						BATTLE_SUB_ACTOR_DISTANCE);
				}
				else if(r_bottom != -1 && l_bottom == -1){
					BCURSOR_IndividualPosSetON_Surface(bip->cursor, left, top, right, top, 
						left, r_bottom, right, bottom, BATTLE_SUB_ACTOR_DISTANCE);
				}
				else{
					BCURSOR_IndividualPosSetON_Surface(bip->cursor, left, top, right, top, 
						left, bottom, right, l_bottom, BATTLE_SUB_ACTOR_DISTANCE);
				}
				if(ex_x != -1){
					BCURSOR_ExPosSetON_Surface(bip->cursor, ex_x, ex_y, ex_anm,
						BATTLE_SUB_ACTOR_DISTANCE);
				}
				else{
					BCURSOR_ExOFF(bip->cursor);
				}
			}
			else{
				BCURSOR_PosSetON_Surface(bip->cursor, 
					bmd->tpd[POKESELE_INDEX_TARGET_CANCEL].rect.left+8, 
					bmd->tpd[POKESELE_INDEX_TARGET_CANCEL].rect.right-8, 
					bmd->tpd[POKESELE_INDEX_TARGET_CANCEL].rect.top+8, 
					bmd->tpd[POKESELE_INDEX_TARGET_CANCEL].rect.bottom-8,
					BATTLE_SUB_ACTOR_DISTANCE);
				BCURSOR_ExOFF(bip->cursor);
			}
		}
		break;
	case PAD_BUTTON_DECIDE:
		if(plural == TRUE){
			//�����I���̏ꍇ
			if(move->y_menu > 0){
				return POKESELE_INDEX_TARGET_CANCEL;
			}
			else{
				for(i = 0; i < CLIENT_MAX; i++){
					if(hit_range[i] == TRUE){
						//�����I���Ȃ̂ŁA�L���Ȃ�Ȃ�Ԃ��̂͂ǂ�ł�����
						return POKESELE_INDEX_TARGET_A + i;
					}
				}
			}
		}
		else{
			//�P���I��
			index = CursorMoveDataPokeSelect[move->y_menu][move->x_menu];
			if(index == POKESELE_INDEX_TARGET_CANCEL
					|| hit_range[index - POKESELE_INDEX_TARGET_A] == TRUE){
				return index;	//���S�m�F���đ��v�Ȃ炻�̂܂ܕԂ�
			}
		}
		break;
	case PAD_BUTTON_CANCEL:
		return POKESELE_INDEX_TARGET_CANCEL;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ʒu�ۑ��F�|�P�����I��
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   index			�I����������
 */
//--------------------------------------------------------------
static void CursorSave_PokeSelect(BI_PARAM_PTR bip, int index)
{
	CURSOR_SAVE *cursor_save;
	int client_no, x, y;

	if(index == POKESELE_INDEX_TARGET_CANCEL){
		return;
	}
	
	client_no = BattleWorkClientNoGet(bip->bw, bip->client_type);
	cursor_save = CT_CursorSavePtrGet(BattleWorkClientParamGet(bip->bw, client_no));
	cursor_save->poke_save_type = bip->pokesele_type;	//bip->makedata_no;
	for(y = 0; y < CURSOR_POKE_SELECT_Y_MENU_NUM; y++){
		for(x = 0; x < CURSOR_POKE_SELECT_X_MENU_NUM; x++){
			if(index == CursorMoveDataPokeSelect[y][x]){
				cursor_save->poke_x = x;
				cursor_save->poke_y = y;
				OS_TPrintf("save x = %d, y = %d\n", x, y);
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ��F2��
 *
 * @param   bip				BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   init_flag		TRUE:����������
 *
 * @retval  ����(������Ȃ��̏ꍇ��RECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_YesNo(BI_PARAM_PTR bip, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;

	move = &bip->cursor_move;
	bmd = &BgMakeData[bip->makedata_no];
	
	if(init_flag == TRUE){
		index = CursorMoveDataYesNoSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	key = CursorMove_KeyCheckMove(move, 
		CURSOR_YESNO_SELECT_X_MENU_NUM, CURSOR_YESNO_SELECT_Y_MENU_NUM,
		CursorMoveDataYesNoSelect[0]);
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataYesNoSelect[move->y_menu][move->x_menu];
		BCURSOR_PosSetON_Surface(bip->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			BATTLE_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		index = CursorMoveDataYesNoSelect[move->y_menu][move->x_menu];
		return index;
	case PAD_BUTTON_CANCEL:
		return YESNO_INDEX_CANCEL;
	}

	return RECT_HIT_NONE;
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
	
	if(move->x_menu >= x_menu_num){
		move->x_menu = x_menu_num - 1;
	}
	if(move->y_menu >= y_menu_num){
		move->y_menu = y_menu_num - 1;
	}
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
		Snd_SePlay(BCURSOR_MOVE_SE);
	}
	else{
		if(ret_key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT)){
			return 0;
		}
	}

	return ret_key;
}

//--------------------------------------------------------------
/**
 * @brief   ����{�^�����������̂��L�[���������A�^�b�`�����������擾
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�L�[�Ō��肵�Ă��B�@FALSE:�^�b�`�p�l���Ō��肵�Ă�
 */
//--------------------------------------------------------------
int BINPUT_CursorDecendGet(BI_PARAM_PTR bip)
{
	return bip->decend_key;
}

//--------------------------------------------------------------
/**
 * @brief   ����{�^�����������̂��L�[���������A�^�b�`�����������Z�b�g
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @param   TRUE:�L�[�Ō���B�@FALSE:�^�b�`�p�l���Ō���
 */
//--------------------------------------------------------------
void BINPUT_CursorDecendSet(BI_PARAM_PTR bip, int decend_key)
{
	bip->decend_key = decend_key;
}


//==============================================================================
//
//	�ߊl�f��
//
//==============================================================================
///�ߊl�f���V�[�P���X�e�[�u��
static int (* const CaptureDemoSeqTbl[])(BI_PARAM_PTR bip) = {
	CaptureDemoSeq_CommandFight,
	CaptureDemoSeq_Waza,
//	CaptureDemoSeq_CommandBag,
};

//--------------------------------------------------------------
/**
 * @brief   �ߊl�f���Ăяo�����C������
 *
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static int CaptureDemo_Main(BI_PARAM_PTR bip)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	int tp_ret;
	
	csp = BattleWorkCATS_SYS_PTRGet(bip->bw);
	crp = BattleWorkCATS_RES_PTRGet(bip->bw);
	pfd = BattleWorkPfdGet(bip->bw);

	tp_ret = RECT_HIT_NONE;
	
	if(BattleWorkDemoSeqNoGet(bip->bw) == 0){
		GF_ASSERT(bip->demo.main_seq < NELEMS(CaptureDemoSeqTbl));
		tp_ret = CaptureDemoSeqTbl[bip->demo.main_seq](bip);
	}
	else{
		tp_ret = CaptureDemoSeq_CommandBag(bip);
	}
	
	if(tp_ret != RECT_HIT_NONE){
		bip->demo.sub_seq = 0;
		bip->demo.sub_wait = 0;
		bip->demo.main_seq++;
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   �ߊl�f���V�[�P���X�F�R�}���h�I������������
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  �������{�^��
 */
//--------------------------------------------------------------
static int CaptureDemoSeq_CommandFight(BI_PARAM_PTR bip)
{
	switch(bip->demo.sub_seq){
	case 0:
		FINGER_PosSetON_Surface(bip->demo.finger, FA_POS_FIGHT_X, FA_POS_FIGHT_Y - 24,
			BATTLE_SUB_ACTOR_DISTANCE);
		FINGER_TouchReq(bip->demo.finger, FINGER_TOUCH_WAIT);
		bip->demo.sub_seq++;
		break;
	default:
		if(FINGER_TouchAnimeCheck(bip->demo.finger) == TRUE){
			bip->demo.sub_seq++;
			return COMMSELE_INDEX_FIGHT;
		}
		break;
	}
	
	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �ߊl�f���V�[�P���X�F�Z�P
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  �������{�^��
 */
//--------------------------------------------------------------
static int CaptureDemoSeq_Waza(BI_PARAM_PTR bip)
{
	switch(bip->demo.sub_seq){
	case 0:
		FINGER_PosSetON_Surface(bip->demo.finger, FA_POS_WAZA_1_X, FA_POS_WAZA_1_Y - 24,
			BATTLE_SUB_ACTOR_DISTANCE);
		FINGER_TouchReq(bip->demo.finger, FINGER_TOUCH_WAIT);
		bip->demo.sub_seq++;
		break;
	default:
		if(FINGER_TouchAnimeCheck(bip->demo.finger) == TRUE){
			bip->demo.sub_seq++;
			return WAZASELE_INDEX_SKILL_1;
		}
		break;
	}
	
	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   �ߊl�f���V�[�P���X�F�R�}���h�I�����o�b�O
 * @param   bip		BI�V�X�e�����[�N�ւ̃|�C���^
 * @retval  �������{�^��
 */
//--------------------------------------------------------------
static int CaptureDemoSeq_CommandBag(BI_PARAM_PTR bip)
{
	switch(bip->demo.sub_seq){
	case 0:
		bip->demo.sub_wait++;
		if(bip->demo.sub_wait > 60){
			bip->demo.sub_wait = 0;
			bip->demo.sub_seq++;
		}
		break;
	case 1:
		FINGER_PosSetON_Surface(bip->demo.finger, FA_POS_ITEM_X, FA_POS_ITEM_Y - 24,
			BATTLE_SUB_ACTOR_DISTANCE);
		FINGER_TouchReq(bip->demo.finger, FINGER_TOUCH_WAIT);
		bip->demo.sub_seq++;
		break;
	default:
		if(FINGER_TouchAnimeCheck(bip->demo.finger) == TRUE){
			bip->demo.sub_seq++;
			return COMMSELE_INDEX_ITEM;
		}
		break;
	}
	
	return RECT_HIT_NONE;
}

