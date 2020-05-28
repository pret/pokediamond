//============================================================================================
/**
 * @file	b_plist_anm.c
 * @brief	�퓬�p�|�P�������X�g��� �{�^������
 * @author	Hiroyuki Nakamura
 * @date	05.03.16
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "b_app_tool.h"

#define	B_PLIST_ANM_H_GLOBAL
#include "b_plist.h"
#include "b_plist_main.h"
#include "b_plist_anm.h"


//============================================================================================
//	�萔��`
//============================================================================================
// �{�^���A�j���p�^�[��
enum {
	BPL_BANM_PAT0 = 0,	// �ʏ�
	BPL_BANM_PAT1,		// �A�j���P
	BPL_BANM_PAT2,		// �A�j���Q
	BPL_BANM_NONE,		// �����Ȃ�
};

// �{�^���A�j���X�N���[���f�[�^
// �퓬���|�P�����̃v���[�g
#define	DAT_PX_MAINPOKE_1	( 0 )
#define	DAT_PY_MAINPOKE_1	( 0 )
#define	DAT_PX_MAINPOKE_2	( 0 )
#define	DAT_PY_MAINPOKE_2	( DAT_PY_MAINPOKE_1+BPL_BSY_PLATE )
#define	DAT_PX_MAINPOKE_3	( 0 )
#define	DAT_PY_MAINPOKE_3	( DAT_PY_MAINPOKE_2+BPL_BSY_PLATE )
#define	DAT_PX_MAINPOKE_4	( 0 )
#define	DAT_PY_MAINPOKE_4	( DAT_PY_MAINPOKE_3+BPL_BSY_PLATE )
// �T�u�|�P�����̃v���[�g
#define	DAT_PX_SUBPOKE_1	( 16 )
#define	DAT_PY_SUBPOKE_1	( 0 )
#define	DAT_PX_SUBPOKE_2	( 16 )
#define	DAT_PY_SUBPOKE_2	( DAT_PY_SUBPOKE_1+BPL_BSY_PLATE )
#define	DAT_PX_SUBPOKE_3	( 16 )
#define	DAT_PY_SUBPOKE_3	( DAT_PY_SUBPOKE_2+BPL_BSY_PLATE )
#define	DAT_PX_SUBPOKE_4	( 16 )
#define	DAT_PY_SUBPOKE_4	( DAT_PY_SUBPOKE_3+BPL_BSY_PLATE )
// ���߃{�^��
#define	DAT_PX_COMMAND_1	( 0 )
#define	DAT_PY_COMMAND_1	( 39 )
#define	DAT_PX_COMMAND_2	( DAT_PX_COMMAND_1 )
#define	DAT_PY_COMMAND_2	( DAT_PY_COMMAND_1+BPL_BSY_COMMAND )
#define	DAT_PX_COMMAND_3	( DAT_PX_COMMAND_1+BPL_BSX_COMMAND )
#define	DAT_PY_COMMAND_3	( DAT_PY_COMMAND_1 )
#define	DAT_PX_COMMAND_4	( DAT_PX_COMMAND_1+BPL_BSX_COMMAND )
#define	DAT_PY_COMMAND_4	( DAT_PY_COMMAND_1+BPL_BSY_COMMAND )
/*
#define	DAT_PX_COMMAND_1	( 0 )
#define	DAT_PY_COMMAND_1	( 39 )
#define	DAT_PX_COMMAND_2	( DAT_PX_COMMAND_1+BPL_BSX_COMMAND )
#define	DAT_PY_COMMAND_2	( DAT_PY_COMMAND_1 )
#define	DAT_PX_COMMAND_3	( DAT_PX_COMMAND_1 )
#define	DAT_PY_COMMAND_3	( DAT_PY_COMMAND_1+BPL_BSY_COMMAND )
#define	DAT_PX_COMMAND_4	( DAT_PX_COMMAND_1+BPL_BSX_COMMAND )
#define	DAT_PY_COMMAND_4	( DAT_PY_COMMAND_1+BPL_BSY_COMMAND )
*/
// �Z�؂�ւ��i��j
#define	DAT_PX_UP_1		( 0 )
#define	DAT_PY_UP_1		( 49 )
#define	DAT_PX_UP_2		( DAT_PX_UP_1+BPL_BSX_UPDOWN )
#define	DAT_PY_UP_2		( 49 )
#define	DAT_PX_UP_3		( DAT_PX_UP_2+BPL_BSX_UPDOWN )
#define	DAT_PY_UP_3		( 49 )
#define	DAT_PX_UP_4		( DAT_PX_UP_3+BPL_BSX_UPDOWN )
#define	DAT_PY_UP_4		( 49 )
// �Z�؂�ւ��i���j
#define	DAT_PX_DOWN_1	( 0 )
#define	DAT_PY_DOWN_1	( 54 )
#define	DAT_PX_DOWN_2	( DAT_PX_DOWN_1+BPL_BSX_UPDOWN )
#define	DAT_PY_DOWN_2	( 54 )
#define	DAT_PX_DOWN_3	( DAT_PX_DOWN_2+BPL_BSX_UPDOWN )
#define	DAT_PY_DOWN_3	( 54 )
#define	DAT_PX_DOWN_4	( DAT_PX_DOWN_3+BPL_BSX_UPDOWN )
#define	DAT_PY_DOWN_4	( 54 )
// �߂�{�^���T�C�Y
#define	DAT_PX_RET_1	( 26 )
#define	DAT_PY_RET_1	( 24 )
#define	DAT_PX_RET_2	( 26 )
#define	DAT_PY_RET_2	( DAT_PY_RET_1+BPL_BSY_RET )
#define	DAT_PX_RET_3	( 26 )
#define	DAT_PY_RET_3	( DAT_PY_RET_2+BPL_BSY_RET )
#define	DAT_PX_RET_4	( 26 )
#define	DAT_PY_RET_4	( DAT_PY_RET_3+BPL_BSY_RET )
// ����ւ��{�^��
#define	DAT_PX_CHG_1	( 0 )
#define	DAT_PY_CHG_1	( 0 )
#define	DAT_PX_CHG_2	( 0 )
#define	DAT_PY_CHG_2	( DAT_PY_CHG_1+BPL_BSY_CHG )
#define	DAT_PX_CHG_3	( 0 )
#define	DAT_PY_CHG_3	( DAT_PY_CHG_2+BPL_BSY_CHG )
// �Z�{�^���T�C�Y
#define	DAT_PX_WAZA_1	( 0 )
#define	DAT_PY_WAZA_1	( 51 )
#define	DAT_PX_WAZA_2	( DAT_PX_WAZA_1+BPL_BSX_WAZA )
#define	DAT_PY_WAZA_2	( DAT_PY_WAZA_1 )
#define	DAT_PX_WAZA_3	( DAT_PX_WAZA_1 )
#define	DAT_PY_WAZA_3	( DAT_PY_WAZA_1+BPL_BSY_WAZA )
#define	DAT_PX_WAZA_4	( DAT_PX_WAZA_2 )
#define	DAT_PY_WAZA_4	( DAT_PY_WAZA_3 )
// �Y���{�^���T�C�Y
#define	DAT_PX_DEL_1	( 0 )
#define	DAT_PY_DEL_1	( 24 )
#define	DAT_PX_DEL_2	( 0 )
#define	DAT_PY_DEL_2	( DAT_PY_DEL_1+BPL_BSY_DEL )
#define	DAT_PX_DEL_3	( 0 )
#define	DAT_PY_DEL_3	( DAT_PY_DEL_2+BPL_BSY_DEL )
// �R���e�X�g�؂�ւ��{�^���T�C�Y
#define	DAT_PX_CONTEST_1	( 20 )
#define	DAT_PY_CONTEST_1	( 49 )
#define	DAT_PX_CONTEST_2	( 20 )
#define	DAT_PY_CONTEST_2	( DAT_PY_CONTEST_1+BPL_BSY_CONTEST )
#define	DAT_PX_CONTEST_3	( 20 )
#define	DAT_PY_CONTEST_3	( DAT_PY_CONTEST_2+BPL_BSY_CONTEST )

// �Z�ʒu�{�^��
#define	DAT_PX_WP1	( 0 )
#define	DAT_PY_WP1	( 59 )
#define	DAT_PX_WP2	( 5 )
#define	DAT_PY_WP2	( 59 )
#define	DAT_PX_WP3	( 10 )
#define	DAT_PY_WP3	( 59 )

// �z�u�ʒu
#define	SCR_POKE1_PX		( 0 )
#define	SCR_POKE1_PY		( 0 )
#define	SCR_POKE2_PX		( 16 )
#define	SCR_POKE2_PY		( 1 )
#define	SCR_POKE3_PX		( 0 )
#define	SCR_POKE3_PY		( 6 )
#define	SCR_POKE4_PX		( 16 )
#define	SCR_POKE4_PY		( 7 )
#define	SCR_POKE5_PX		( 0 )
#define	SCR_POKE5_PY		( 12 )
#define	SCR_POKE6_PX		( 16 )
#define	SCR_POKE6_PY		( 13 )
#define	SCR_RETURN_PX		( 27 )
#define	SCR_RETURN_PY		( 19 )
#define	SCR_CHANGE_PX		( 1 )
#define	SCR_CHANGE_PY		( 1 )
#define	SCR_STATUS_L_PX		( 0 )
#define	SCR_STATUS_L_PY		( 19 )
#define	SCR_STATUS_R_PX		( 12 )
#define	SCR_STATUS_R_PY		( 19 )
#define	SCR_WAZASEL1_PX		( 13 )
#define	SCR_WAZASEL1_PY		( 19 )
#define	SCR_WAZASEL2_PX		( 12 )
#define	SCR_WAZASEL2_PY		( 19 )
#define	SCR_UP_PX			( 0 )
#define	SCR_UP_PY			( 19 )
#define	SCR_DOWN_PX			( 5 )
#define	SCR_DOWN_PY			( 19 )
#define	SCR_WAZA1_PX		( 0 )
#define	SCR_WAZA1_PY		( 6 )
#define	SCR_WAZA2_PX		( 16 )
#define	SCR_WAZA2_PY		( 6 )
#define	SCR_WAZA3_PX		( 0 )
#define	SCR_WAZA3_PY		( 12 )
#define	SCR_WAZA4_PX		( 16 )
#define	SCR_WAZA4_PY		( 12 )
#define	SCR_WAZA5_PX		( 8 )
#define	SCR_WAZA5_PY		( 18 )
#define	SCR_DEL_PX			( 0 )
#define	SCR_DEL_PY			( 19 )
#define	SCR_CONTEST_PX		( 23 )
#define	SCR_CONTEST_PY		( 0 )
#define	SCR_WP1_PX			( 11 )
#define	SCR_WP1_PY			( 19 )
#define	SCR_WP2_PX			( 16 )
#define	SCR_WP2_PY			( 19 )
#define	SCR_WP3_PX			( 11 )
#define	SCR_WP3_PY			( 21 )
#define	SCR_WP4_PX			( 16 )
#define	SCR_WP4_PY			( 21 )

#define	BMP_MV_PRM0_POKESEL		( 2 )
#define	BMP_MV_PRM1_POKESEL		( 3 )
#define	BMP_MV_PRM2_POKESEL		( 1 )

#define	BMP_MV_PRM0		( 2 )
#define	BMP_MV_PRM1		( 4 )
#define	BMP_MV_PRM2		( 2 )

#define	OBJ_MV_PRM0_POKESEL		( 2 )
#define	OBJ_MV_PRM1_POKESEL		( -3 )
#define	OBJ_MV_PRM2_POKESEL		( 1 )

#define	OBJ_MV_PRM0		( 2 )
#define	OBJ_MV_PRM1		( -4 )
#define	OBJ_MV_PRM2		( 2 )


typedef struct {
	u8	px;
	u8	py;
	u8	sx;
	u8	sy;
}BUTTON_ANM;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BPL_ScrnCopy( u16 * buf, u16 * scrn, u8 px, u8 py, u8 sx, u8 sy );
static u8 BPL_PokeChangeButtonCheck( BPLIST_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �{�^���X�N���[���f�[�^
static const BUTTON_ANM ButtonScreenAnm[] =
{
	{ SCR_POKE1_PX, SCR_POKE1_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����P
	{ SCR_POKE2_PX, SCR_POKE2_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����Q
	{ SCR_POKE3_PX, SCR_POKE3_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����R
	{ SCR_POKE4_PX, SCR_POKE4_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����S
	{ SCR_POKE5_PX, SCR_POKE5_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����T
	{ SCR_POKE6_PX, SCR_POKE6_PY, BPL_BSX_PLATE, BPL_BSY_PLATE },			// �|�P�����U
	{ SCR_RETURN_PX, SCR_RETURN_PY, BPL_BSX_RET, BPL_BSY_RET },				// �߂�
	{ SCR_CHANGE_PX, SCR_CHANGE_PY, BPL_BSX_CHG, BPL_BSY_CHG },				// ����ւ�
	{ SCR_STATUS_L_PX, SCR_STATUS_L_PY, BPL_BSX_COMMAND, BPL_BSY_COMMAND },	// ����������i���z�u�j
	{ SCR_STATUS_R_PX, SCR_STATUS_R_PY, BPL_BSX_COMMAND, BPL_BSY_COMMAND },	// ����������i�E�z�u�j
	{ SCR_WAZASEL1_PX, SCR_WAZASEL1_PY, BPL_BSX_COMMAND, BPL_BSY_COMMAND },	// �Z������
	{ SCR_WAZASEL2_PX, SCR_WAZASEL2_PY, BPL_BSX_COMMAND, BPL_BSY_COMMAND },	// �Z������i�P�Ɓj
	{ SCR_UP_PX, SCR_UP_PY, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN },				// �؂�ւ��i��j
	{ SCR_DOWN_PX, SCR_DOWN_PY, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN },			// �؂�ւ��i���j
	{ SCR_WAZA1_PX, SCR_WAZA1_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },				// �Z�P
	{ SCR_WAZA2_PX, SCR_WAZA2_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },				// �Z�Q
	{ SCR_WAZA3_PX, SCR_WAZA3_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },				// �Z�R
	{ SCR_WAZA4_PX, SCR_WAZA4_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },				// �Z�S
	{ SCR_CONTEST_PX, SCR_CONTEST_PY, BPL_BSX_CONTEST, BPL_BSY_CONTEST },	// �R���e�X�g�Z<->�키�Z

	{ SCR_WAZA1_PX, SCR_WAZA1_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�񕜂P
	{ SCR_WAZA2_PX, SCR_WAZA2_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�񕜂Q
	{ SCR_WAZA3_PX, SCR_WAZA3_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�񕜂R
	{ SCR_WAZA4_PX, SCR_WAZA4_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�񕜂S

	{ SCR_WAZA1_PX, SCR_WAZA1_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�Y��P
	{ SCR_WAZA2_PX, SCR_WAZA2_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�Y��Q
	{ SCR_WAZA3_PX, SCR_WAZA3_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�Y��R
	{ SCR_WAZA4_PX, SCR_WAZA4_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�Y��S
	{ SCR_WAZA5_PX, SCR_WAZA5_PY, BPL_BSX_WAZA, BPL_BSY_WAZA },		// �Z�Y��T

	{ SCR_DEL_PX, SCR_DEL_PY, BPL_BSX_DEL, BPL_BSY_DEL },			// �Y�ꂳ����i�퓬�j
	{ SCR_DEL_PX, SCR_DEL_PY, BPL_BSX_DEL, BPL_BSY_DEL },			// �Y�ꂳ����i�R���e�X�g�j

	{ SCR_WP1_PX, SCR_WP1_PY, BPL_BSX_WP, BPL_BSY_WP },		// �Z�؂�ւ��P
	{ SCR_WP2_PX, SCR_WP2_PY, BPL_BSX_WP, BPL_BSY_WP },		// �Z�؂�ւ��Q
	{ SCR_WP3_PX, SCR_WP3_PY, BPL_BSX_WP, BPL_BSY_WP },		// �Z�؂�ւ��R
	{ SCR_WP4_PX, SCR_WP4_PY, BPL_BSX_WP, BPL_BSY_WP },		// �Z�؂�ւ��S
};

static const u8 BtnBmpWin_Poke1[] = { WIN_P1_POKE1, 0xff };	// �|�P�����P
static const u8 BtnBmpWin_Poke2[] = { WIN_P1_POKE2, 0xff };	// �|�P�����Q
static const u8 BtnBmpWin_Poke3[] = { WIN_P1_POKE3, 0xff };	// �|�P�����R
static const u8 BtnBmpWin_Poke4[] = { WIN_P1_POKE4, 0xff };	// �|�P�����S
static const u8 BtnBmpWin_Poke5[] = { WIN_P1_POKE5, 0xff };	// �|�P�����T
static const u8 BtnBmpWin_Poke6[] = { WIN_P1_POKE6, 0xff };	// �|�P�����U

static const u8 BtnBmpWin_Change[] = { WIN_CHG_NAME, WIN_CHG_IREKAE, 0xff };	// �u���ꂩ����v
static const u8 BtnBmpWin_Status1[] = { WIN_CHG_STATUS, 0xff };					// �u�悳���݂�v
static const u8 BtnBmpWin_WazaSel1[] = { WIN_CHG_WAZACHECK, 0xff };				// �u�킴���݂�v

static const u8 BtnBmpWin_WazaSel2[] = { WIN_P3_WAZACHECK, 0xff };				// �u�킴���݂�v

static const u8 BtnBmpWin_Status2[] = { WIN_STW_STATUS, 0xff };					// �u�悳���݂�v

static const u8 BtnBmpWin_WazaBtn1[] = { WIN_STW_SKILL1_S, WIN_STW_SKILL1, 0xff };	// �Z�P
static const u8 BtnBmpWin_WazaBtn2[] = { WIN_STW_SKILL2_S, WIN_STW_SKILL2, 0xff };	// �Z�Q
static const u8 BtnBmpWin_WazaBtn3[] = { WIN_STW_SKILL3_S, WIN_STW_SKILL3, 0xff };	// �Z�R
static const u8 BtnBmpWin_WazaBtn4[] = { WIN_STW_SKILL4_S, WIN_STW_SKILL4, 0xff };	// �Z�S

static const u8 BtnBmpWin_WazaRcv1[] = { WIN_P7_SKILL1, 0xff };	// �Z�񕜂P
static const u8 BtnBmpWin_WazaRcv2[] = { WIN_P7_SKILL2, 0xff };	// �Z�񕜂Q
static const u8 BtnBmpWin_WazaRcv3[] = { WIN_P7_SKILL3, 0xff };	// �Z�񕜂R
static const u8 BtnBmpWin_WazaRcv4[] = { WIN_P7_SKILL4, 0xff };	// �Z�񕜂S

static const u8 BtnBmpWin_WazaDel1[] = { WIN_P5_SKILL1, 0xff };	// �Z�񕜂P
static const u8 BtnBmpWin_WazaDel2[] = { WIN_P5_SKILL2, 0xff };	// �Z�񕜂Q
static const u8 BtnBmpWin_WazaDel3[] = { WIN_P5_SKILL3, 0xff };	// �Z�񕜂R
static const u8 BtnBmpWin_WazaDel4[] = { WIN_P5_SKILL4, 0xff };	// �Z�񕜂S
static const u8 BtnBmpWin_WazaDel5[] = { WIN_P5_SKILL5, 0xff };	// �Z�񕜂T

static const u8 BtnBmpWin_Delete[] = { WIN_P6_WASURERU, 0xff };		// �u�킷���v
static const u8 BtnBmpWin_DelCon[] = { WIN_P8_WASURERU, 0xff };		// �u�킷���v


static const u8 * const ButtonBmpWinIndex[] = {
	BtnBmpWin_Poke1,	// BPL_BUTTON_POKE1
	BtnBmpWin_Poke2,	// BPL_BUTTON_POKE2
	BtnBmpWin_Poke3,	// BPL_BUTTON_POKE3
	BtnBmpWin_Poke4,	// BPL_BUTTON_POKE4
	BtnBmpWin_Poke5,	// BPL_BUTTON_POKE5
	BtnBmpWin_Poke6,	// BPL_BUTTON_POKE6
	NULL,				// BPL_BUTTON_RET

	BtnBmpWin_Change,	// BPL_BUTTON_POKE_CHG
	BtnBmpWin_Status1,	// BPL_BUTTON_STATUS1
	BtnBmpWin_Status2,	// BPL_BUTTON_STATUS2
	BtnBmpWin_WazaSel1,	// BPL_BUTTON_WAZASEL1
	BtnBmpWin_WazaSel2,	// BPL_BUTTON_WAZASEL2

	NULL,				// BPL_BUTTON_UP
	NULL,				// BPL_BUTTON_DOWN

	BtnBmpWin_WazaBtn1,	// BPL_BUTTON_WAZA1
	BtnBmpWin_WazaBtn2,	// BPL_BUTTON_WAZA2
	BtnBmpWin_WazaBtn3,	// BPL_BUTTON_WAZA3
	BtnBmpWin_WazaBtn4,	// BPL_BUTTON_WAZA4
	NULL,				// BPL_BUTTON_CONTEST

	BtnBmpWin_WazaRcv1,	// BPL_BUTTON_WAZARCV1
	BtnBmpWin_WazaRcv2,	// BPL_BUTTON_WAZARCV2
	BtnBmpWin_WazaRcv3,	// BPL_BUTTON_WAZARCV3
	BtnBmpWin_WazaRcv4,	// BPL_BUTTON_WAZARCV4

	BtnBmpWin_WazaDel1,	// BPL_BUTTON_WAZADEL1
	BtnBmpWin_WazaDel2,	// BPL_BUTTON_WAZADEL2
	BtnBmpWin_WazaDel3,	// BPL_BUTTON_WAZADEL3
	BtnBmpWin_WazaDel4,	// BPL_BUTTON_WAZADEL4
	BtnBmpWin_WazaDel5,	// BPL_BUTTON_WAZADEL5

	BtnBmpWin_Delete,	// BPL_BUTTON_WAZADEL_B
	BtnBmpWin_DelCon,	// BPL_BUTTON_WAZADEL_C

	NULL,				// BPL_BUTTON_WAZAPOS1
	NULL,				// BPL_BUTTON_WAZAPOS2
	NULL,				// BPL_BUTTON_WAZAPOS3
	NULL,				// BPL_BUTTON_WAZAPOS4
};

static const s16 ObjMvPrmPokeSel[] = {
	OBJ_MV_PRM0_POKESEL, OBJ_MV_PRM1_POKESEL, OBJ_MV_PRM2_POKESEL
};
static const s16 ObjMvPrm[] = { OBJ_MV_PRM0, OBJ_MV_PRM1, OBJ_MV_PRM2 };

static const u8 BmpMvPrmPokeSel[] = {
	BMP_MV_PRM0_POKESEL, BMP_MV_PRM1_POKESEL, BMP_MV_PRM2_POKESEL
};
static const u8 BmpMvPrm[] = { BMP_MV_PRM0, BMP_MV_PRM1, BMP_MV_PRM2 };





void BattlePokeList_ButtonScreenMake( BPLIST_WORK * wk, u16 * scrn )
{
	// �퓬���̃v���[�g�{�^��
	BPL_ScrnCopy(
		wk->btn_plate1[0], scrn,
		DAT_PX_MAINPOKE_1, DAT_PY_MAINPOKE_1, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate1[1], scrn,
		DAT_PX_MAINPOKE_2, DAT_PY_MAINPOKE_2, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate1[2], scrn,
		DAT_PX_MAINPOKE_3, DAT_PY_MAINPOKE_3, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate1[3], scrn,
		DAT_PX_MAINPOKE_4, DAT_PY_MAINPOKE_4, BPL_BSX_PLATE, BPL_BSY_PLATE );

	// �T���̃v���[�g�{�^��
	BPL_ScrnCopy(
		wk->btn_plate2[0], scrn,
		DAT_PX_SUBPOKE_1, DAT_PY_SUBPOKE_1, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate2[1], scrn,
		DAT_PX_SUBPOKE_2, DAT_PY_SUBPOKE_2, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate2[2], scrn,
		DAT_PX_SUBPOKE_3, DAT_PY_SUBPOKE_3, BPL_BSX_PLATE, BPL_BSY_PLATE );
	BPL_ScrnCopy(
		wk->btn_plate2[3], scrn,
		DAT_PX_SUBPOKE_4, DAT_PY_SUBPOKE_4, BPL_BSX_PLATE, BPL_BSY_PLATE );

	// ���߃{�^��
	BPL_ScrnCopy(
		wk->btn_command[0], scrn,
		DAT_PX_COMMAND_1, DAT_PY_COMMAND_1, BPL_BSX_COMMAND, BPL_BSY_COMMAND );
	BPL_ScrnCopy(
		wk->btn_command[1], scrn,
		DAT_PX_COMMAND_2, DAT_PY_COMMAND_2, BPL_BSX_COMMAND, BPL_BSY_COMMAND );
	BPL_ScrnCopy(
		wk->btn_command[2], scrn,
		DAT_PX_COMMAND_3, DAT_PY_COMMAND_3, BPL_BSX_COMMAND, BPL_BSY_COMMAND );
	BPL_ScrnCopy(
		wk->btn_command[3], scrn,
		DAT_PX_COMMAND_4, DAT_PY_COMMAND_4, BPL_BSX_COMMAND, BPL_BSY_COMMAND );

	// �؂�ւ��{�^���i��j
	BPL_ScrnCopy( wk->btn_up[0], scrn, DAT_PX_UP_1, DAT_PY_UP_1, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy( wk->btn_up[1], scrn, DAT_PX_UP_2, DAT_PY_UP_2, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy( wk->btn_up[2], scrn, DAT_PX_UP_3, DAT_PY_UP_3, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy( wk->btn_up[3], scrn, DAT_PX_UP_4, DAT_PY_UP_4, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );

	// �؂�ւ��{�^���i���j
	BPL_ScrnCopy(
		wk->btn_down[0], scrn, DAT_PX_DOWN_1, DAT_PY_DOWN_1, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy(
		wk->btn_down[1], scrn, DAT_PX_DOWN_2, DAT_PY_DOWN_2, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy(
		wk->btn_down[2], scrn, DAT_PX_DOWN_3, DAT_PY_DOWN_3, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );
	BPL_ScrnCopy(
		wk->btn_down[3], scrn, DAT_PX_DOWN_4, DAT_PY_DOWN_4, BPL_BSX_UPDOWN, BPL_BSY_UPDOWN );

	// �߂�{�^��
	BPL_ScrnCopy( wk->btn_ret[0], scrn, DAT_PX_RET_1, DAT_PY_RET_1, BPL_BSX_RET, BPL_BSY_RET );
	BPL_ScrnCopy( wk->btn_ret[1], scrn, DAT_PX_RET_2, DAT_PY_RET_2, BPL_BSX_RET, BPL_BSY_RET );
	BPL_ScrnCopy( wk->btn_ret[2], scrn, DAT_PX_RET_3, DAT_PY_RET_3, BPL_BSX_RET, BPL_BSY_RET );
	BPL_ScrnCopy( wk->btn_ret[3], scrn, DAT_PX_RET_4, DAT_PY_RET_4, BPL_BSX_RET, BPL_BSY_RET );

	// �Y���{�^��
	BPL_ScrnCopy( wk->btn_del[0], scrn, DAT_PX_DEL_1, DAT_PY_DEL_1, BPL_BSX_DEL, BPL_BSY_DEL );
	BPL_ScrnCopy( wk->btn_del[1], scrn, DAT_PX_DEL_2, DAT_PY_DEL_2, BPL_BSX_DEL, BPL_BSY_DEL );
	BPL_ScrnCopy( wk->btn_del[2], scrn, DAT_PX_DEL_3, DAT_PY_DEL_3, BPL_BSX_DEL, BPL_BSY_DEL );

	// �R���e�X�g�؂�ւ��{�^��
	BPL_ScrnCopy(
		wk->btn_contest[0], scrn,
		DAT_PX_CONTEST_1, DAT_PY_CONTEST_1, BPL_BSX_CONTEST, BPL_BSY_CONTEST );
	BPL_ScrnCopy(
		wk->btn_contest[1], scrn,
		DAT_PX_CONTEST_2, DAT_PY_CONTEST_2, BPL_BSX_CONTEST, BPL_BSY_CONTEST );
	BPL_ScrnCopy(
		wk->btn_contest[2], scrn,
		DAT_PX_CONTEST_3, DAT_PY_CONTEST_3, BPL_BSX_CONTEST, BPL_BSY_CONTEST );

	// �Z�ʒu�{�^��
	BPL_ScrnCopy( wk->btn_wp[0], scrn, DAT_PX_WP1, DAT_PY_WP1, BPL_BSX_WP, BPL_BSY_WP );
	BPL_ScrnCopy( wk->btn_wp[1], scrn, DAT_PX_WP2, DAT_PY_WP2, BPL_BSX_WP, BPL_BSY_WP );
	BPL_ScrnCopy( wk->btn_wp[2], scrn, DAT_PX_WP3, DAT_PY_WP3, BPL_BSX_WP, BPL_BSY_WP );
}

void BattlePokeList_ButtonScreenMake2( BPLIST_WORK * wk, u16 * scrn )
{
	// ����ւ��{�^��
	BPL_ScrnCopy( wk->btn_chg[0], scrn, DAT_PX_CHG_1, DAT_PY_CHG_1, BPL_BSX_CHG, BPL_BSY_CHG );
	BPL_ScrnCopy( wk->btn_chg[1], scrn, DAT_PX_CHG_2, DAT_PY_CHG_2, BPL_BSX_CHG, BPL_BSY_CHG );
	BPL_ScrnCopy( wk->btn_chg[2], scrn, DAT_PX_CHG_3, DAT_PY_CHG_3, BPL_BSX_CHG, BPL_BSY_CHG );

	// �Z�{�^��
	BPL_ScrnCopy(
		wk->btn_waza[0], scrn, DAT_PX_WAZA_1, DAT_PY_WAZA_1, BPL_BSX_WAZA, BPL_BSY_WAZA );
	BPL_ScrnCopy(
		wk->btn_waza[1], scrn, DAT_PX_WAZA_2, DAT_PY_WAZA_2, BPL_BSX_WAZA, BPL_BSY_WAZA );
	BPL_ScrnCopy(
		wk->btn_waza[2], scrn, DAT_PX_WAZA_3, DAT_PY_WAZA_3, BPL_BSX_WAZA, BPL_BSY_WAZA );
	BPL_ScrnCopy(
		wk->btn_waza[3], scrn, DAT_PX_WAZA_4, DAT_PY_WAZA_4, BPL_BSX_WAZA, BPL_BSY_WAZA );
}


static void BPL_ScrnCopy( u16 * buf, u16 * scrn, u8 px, u8 py, u8 sx, u8 sy )
{
	u16	i, j;

	for( i=0; i<sy; i++ ){
		for( j=0; j<sx; j++ ){
			buf[i*sx+j] = scrn[ (py+i)*32 + px+j ];
		}
	}
}


static u16 * BPL_ButtonScreenBufGet( BPLIST_WORK * wk, u8 id, u8 num, u8 pat )
{
	switch( id ){
	case BPL_BUTTON_POKE1:		// �|�P�����P
	case BPL_BUTTON_POKE2:		// �|�P�����Q
	case BPL_BUTTON_POKE3:		// �|�P�����R
	case BPL_BUTTON_POKE4:		// �|�P�����S
	case BPL_BUTTON_POKE5:		// �|�P�����T
	case BPL_BUTTON_POKE6:		// �|�P�����U
		if( pat == 0 ){
			return wk->btn_plate1[num];
		}else{
			return wk->btn_plate2[num];
		}

	case BPL_BUTTON_RET:		// �߂�
		return wk->btn_ret[num];

	case BPL_BUTTON_POKE_CHG:	// ����ւ�
		return wk->btn_chg[num];

	case BPL_BUTTON_STATUS1:	// ����������i���z�u�j
	case BPL_BUTTON_STATUS2:	// ����������i�E�z�u�j
	case BPL_BUTTON_WAZASEL1:	// �Z������
	case BPL_BUTTON_WAZASEL2:	// �Z������i�P�Ɓj
		return wk->btn_command[num];

	case BPL_BUTTON_UP:			// �؂�ւ��i��j
		return wk->btn_up[num];

	case BPL_BUTTON_DOWN:		// �؂�ւ��i���j
		return wk->btn_down[num];

	case BPL_BUTTON_WAZA1:		// �Z�P
	case BPL_BUTTON_WAZA2:		// �Z�Q
	case BPL_BUTTON_WAZA3:		// �Z�R
	case BPL_BUTTON_WAZA4:		// �Z�S
	case BPL_BUTTON_WAZARCV1:	// �Z�񕜂P
	case BPL_BUTTON_WAZARCV2:	// �Z�񕜂Q
	case BPL_BUTTON_WAZARCV3:	// �Z�񕜂R
	case BPL_BUTTON_WAZARCV4:	// �Z�񕜂S
	case BPL_BUTTON_WAZADEL1:	// �Z�Y��P
	case BPL_BUTTON_WAZADEL2:	// �Z�Y��Q
	case BPL_BUTTON_WAZADEL3:	// �Z�Y��R
	case BPL_BUTTON_WAZADEL4:	// �Z�Y��S
	case BPL_BUTTON_WAZADEL5:	// �Z�Y��T
		return wk->btn_waza[num];

	case BPL_BUTTON_WAZADEL_B:	// �Y�ꂳ����
	case BPL_BUTTON_WAZADEL_C:	// �Y�ꂳ����
		return wk->btn_del[num];

	case BPL_BUTTON_CONTEST:	// �R���e�X�g�Z<->�키�Z
		return wk->btn_contest[num];

	case BPL_BUTTON_WAZAPOS1:	// �Z�؂�ւ��P
	case BPL_BUTTON_WAZAPOS2:	// �Z�؂�ւ��Q
	case BPL_BUTTON_WAZAPOS3:	// �Z�؂�ւ��R
	case BPL_BUTTON_WAZAPOS4:	// �Z�؂�ւ��S
		return wk->btn_wp[num];
	}

	return NULL;
}

#define	POKE_SCRN_HP_PX		( 6 )
#define	POKE_SCRN_HP_PY		( 2 )
#define	POKE_SCRN_HP_SX		( 9 )
#define	POKE_SCRN_HP_SY		( 2 )
#define	POKE_COL_DEATH		( BPL_PAL_DN_PLATE << 12 )
#define	POKE_COL_MULTI		( BPL_PAL_MN_PLATE << 12 )
#define	WAZA_COL_DEL		( BPL_PAL_B_RED << 12 )


static void BPL_ButtonScreenMake( BPLIST_WORK * wk, u16 * buf, u8 id, u8 anm, u8 pat )
{
	u16 * scrn;
	u8	sx, sy;
	u8	i, j;

	scrn = BPL_ButtonScreenBufGet( wk, id, anm, pat );
	sx   = ButtonScreenAnm[id].sx;
	sy   = ButtonScreenAnm[id].sy;

	memcpy( buf, scrn, sx*sy*2 );

	switch( id ){
	case BPL_BUTTON_POKE1:		// �|�P�����P
	case BPL_BUTTON_POKE2:		// �|�P�����Q
	case BPL_BUTTON_POKE3:		// �|�P�����R
	case BPL_BUTTON_POKE4:		// �|�P�����S
	case BPL_BUTTON_POKE5:		// �|�P�����T
	case BPL_BUTTON_POKE6:		// �|�P�����U
		if( wk->poke[id-BPL_BUTTON_POKE1].mons == 0 ){ break; }
		if( wk->poke[id-BPL_BUTTON_POKE1].egg != 0 ){
			u16	fill[2];
			fill[0] = buf[ POKE_SCRN_HP_PY*sx+POKE_SCRN_HP_PX-1 ];
			fill[1] = buf[ (POKE_SCRN_HP_PY+1)*sx+POKE_SCRN_HP_PX-1 ];
			for( i=0; i<POKE_SCRN_HP_SY; i++ ){
				for( j=0; j<POKE_SCRN_HP_SX; j++ ){
					buf[ (POKE_SCRN_HP_PY+i)*sx+POKE_SCRN_HP_PX+j ] = fill[i];
				}
			}
		}else{
			if( wk->poke[id-BPL_BUTTON_POKE1].hp == 0 ){
				for( i=0; i<sx*sy; i++ ){
					buf[i] = ( buf[i] & 0xfff ) | POKE_COL_DEATH;
				}
			}else if( BattlePokeList_MultiPosCheck( wk, id-BPL_BUTTON_POKE1 ) == TRUE ){
				for( i=0; i<sx*sy; i++ ){
					buf[i] = ( buf[i] & 0xfff ) | POKE_COL_MULTI;
				}
			}
		}
		break;

	case BPL_BUTTON_WAZADEL5:	// �Z�Y��T
		for( i=0; i<sx*sy; i++ ){
			buf[i] = ( buf[i] & 0xfff ) | WAZA_COL_DEL;
		}
		break;

/*
	case BPL_BUTTON_STATUS1:	// ����������i���z�u�j
	case BPL_BUTTON_STATUS2:	// ����������i�E�z�u�j
	case BPL_BUTTON_WAZASEL1:	// �Z������
	case BPL_BUTTON_WAZASEL2:	// �Z������i�P�Ɓj
		return wk->btn_command[num];

	case BPL_BUTTON_WAZA1:		// �Z�P
	case BPL_BUTTON_WAZA2:		// �Z�Q
	case BPL_BUTTON_WAZA3:		// �Z�R
	case BPL_BUTTON_WAZA4:		// �Z�S
	case BPL_BUTTON_WAZARCV1:	// �Z�񕜂P
	case BPL_BUTTON_WAZARCV2:	// �Z�񕜂Q
	case BPL_BUTTON_WAZARCV3:	// �Z�񕜂R
	case BPL_BUTTON_WAZARCV4:	// �Z�񕜂S
	case BPL_BUTTON_WAZADEL1:	// �Z�Y��P
	case BPL_BUTTON_WAZADEL2:	// �Z�Y��Q
	case BPL_BUTTON_WAZADEL3:	// �Z�Y��R
	case BPL_BUTTON_WAZADEL4:	// �Z�Y��S
	case BPL_BUTTON_WAZADEL5:	// �Z�Y��T
		return wk->btn_waza[num];

	case BPL_BUTTON_WAZAPOS1:	// �Z�؂�ւ��P
	case BPL_BUTTON_WAZAPOS2:	// �Z�؂�ւ��Q
	case BPL_BUTTON_WAZAPOS3:	// �Z�؂�ւ��R
	case BPL_BUTTON_WAZAPOS4:	// �Z�؂�ւ��S
		return wk->btn_wp[num];
*/
	}
}

static void BPL_ButtonScreenWrite( BPLIST_WORK * wk, u8 id, u8 anm, u8 pat )
{
	u16 * buf = sys_AllocMemory( wk->dat->heap, ButtonScreenAnm[id].sx*ButtonScreenAnm[id].sy*2 );

	BPL_ButtonScreenMake( wk, buf, id, anm, pat );

	GF_BGL_ScrWrite(
		wk->bgl, GF_BGL_FRAME2_S, buf,
		ButtonScreenAnm[id].px, ButtonScreenAnm[id].py,
		ButtonScreenAnm[id].sx, ButtonScreenAnm[id].sy );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_S );

	sys_FreeMemoryEz( buf );
}

static void BPL_ButtonBmpWinShift( BPLIST_WORK * wk, u8 id, u8 anm )
{
	const u8 * tbl;
	u16	i;
	u8	dir, ofs;

	tbl = ButtonBmpWinIndex[id];
	if( tbl == NULL ){ return; }

	if( id == BPL_BUTTON_POKE1 || id == BPL_BUTTON_POKE2 || id == BPL_BUTTON_POKE3 ||
		id == BPL_BUTTON_POKE4 || id == BPL_BUTTON_POKE5 || id == BPL_BUTTON_POKE6 ){
		ofs = BmpMvPrmPokeSel[anm];
	}else{
		ofs = BmpMvPrm[anm];
	}

	switch( anm ){
	case 0:
		dir = GF_BGL_BMPWIN_SHIFT_D;
//		ofs = BMP_MV_PRM0;
		break;
	case 1:
		dir = GF_BGL_BMPWIN_SHIFT_U;
//		ofs = BMP_MV_PRM1;
		break;
	case 2:
		dir = GF_BGL_BMPWIN_SHIFT_D;
//		ofs = BMP_MV_PRM2;
		break;
	}

	if( id >= BPL_BUTTON_WAZA1 && id <= BPL_BUTTON_WAZA4 ){
		GF_BGL_BmpWinShift( &wk->add_win[tbl[wk->bmp_swap]], dir, ofs, 0 );
		GF_BGL_BmpWinOnVReq( &wk->add_win[tbl[wk->bmp_swap]] );
	}else{
		for( i=0; i<8; i++ ){
			if( tbl[i] == 0xff ){ break; }
			GF_BGL_BmpWinShift( &wk->add_win[tbl[i]], dir, ofs, 0 );
			GF_BGL_BmpWinOnVReq( &wk->add_win[tbl[i]] );
		}
	}
}


static void BPL_ButtonObjMove( BPLIST_WORK * wk, u8 id, u8 anm )
{
	switch( id ){
	case BPL_BUTTON_POKE1:		// �|�P�����P
	case BPL_BUTTON_POKE2:		// �|�P�����Q
	case BPL_BUTTON_POKE3:		// �|�P�����R
	case BPL_BUTTON_POKE4:		// �|�P�����S
	case BPL_BUTTON_POKE5:		// �|�P�����T
	case BPL_BUTTON_POKE6:		// �|�P�����U
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_STATUS1+id-BPL_BUTTON_POKE1], 0, ObjMvPrmPokeSel[anm] );
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_ITEM1+id-BPL_BUTTON_POKE1], 0, ObjMvPrmPokeSel[anm] );
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_POKE1+id-BPL_BUTTON_POKE1], 0, ObjMvPrmPokeSel[anm] );
		break;

	case BPL_BUTTON_POKE_CHG:	// ����ւ�
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], 0, ObjMvPrm[anm] );
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], 0, ObjMvPrm[anm] );
		break;

	case BPL_BUTTON_WAZA1:		// �Z�P
	case BPL_BUTTON_WAZA2:		// �Z�Q
	case BPL_BUTTON_WAZA3:		// �Z�R
	case BPL_BUTTON_WAZA4:		// �Z�S
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_WAZATYPE1+id-BPL_BUTTON_WAZA1], 0, ObjMvPrm[anm] );
		break;

	case BPL_BUTTON_WAZARCV1:	// �Z�񕜂P
	case BPL_BUTTON_WAZARCV2:	// �Z�񕜂Q
	case BPL_BUTTON_WAZARCV3:	// �Z�񕜂R
	case BPL_BUTTON_WAZARCV4:	// �Z�񕜂S
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_WAZATYPE1+id-BPL_BUTTON_WAZARCV1], 0, ObjMvPrm[anm] );
		break;

	case BPL_BUTTON_WAZADEL1:	// �Z�Y��P
	case BPL_BUTTON_WAZADEL2:	// �Z�Y��Q
	case BPL_BUTTON_WAZADEL3:	// �Z�Y��R
	case BPL_BUTTON_WAZADEL4:	// �Z�Y��S
	case BPL_BUTTON_WAZADEL5:	// �Z�Y��T
		CATS_ObjectPosMoveCap( wk->cap[BPL_CA_WAZATYPE1+id-BPL_BUTTON_WAZADEL1], 0, ObjMvPrm[anm] );
		break;
	}
}


void BattlePokeList_ButtonAnmInit( BPLIST_WORK * wk, u8 id )
{
	wk->btn_pat = 0;
	if( id >= BPL_BUTTON_POKE1 && id <= BPL_BUTTON_POKE6 ){
		if( BattlePokeList_PokeSetCheck( wk, id - BPL_BUTTON_POKE1 ) == 2 ){
			wk->btn_pat = 1;
		}
	}
	wk->btn_seq  = 0;
	wk->btn_cnt  = 0;
	wk->btn_id   = id;
	wk->btn_flg  = 1;
}

void BattlePokeList_ButtonAnmMain( BPLIST_WORK * wk )
{
	if( wk->btn_flg == 0 ){ return; }

	switch( wk->btn_seq ){
	case 0:
		BPL_ButtonScreenWrite( wk, wk->btn_id, 1, wk->btn_pat );
		BPL_ButtonBmpWinShift( wk, wk->btn_id, 1 );
		BPL_ButtonObjMove( wk, wk->btn_id, 1 );
		wk->btn_cnt = 0;
		wk->btn_seq = 1;
		break;

	case 1:
/*
		if( wk->btn_cnt < 1 ){
			wk->btn_cnt++;
			return;
		}
*/
		BPL_ButtonScreenWrite( wk, wk->btn_id, 2, wk->btn_pat );
		BPL_ButtonBmpWinShift( wk, wk->btn_id, 2 );
		BPL_ButtonObjMove( wk, wk->btn_id, 2 );
		wk->btn_cnt = 0;
		wk->btn_seq = 2;
		break;

	case 2:
/*
		if( wk->btn_cnt < 1 ){
			wk->btn_cnt++;
			return;
		}
*/
		BPL_ButtonScreenWrite( wk, wk->btn_id, 0, wk->btn_pat );
		BPL_ButtonBmpWinShift( wk, wk->btn_id, 0 );
		BPL_ButtonObjMove( wk, wk->btn_id, 0 );
		wk->btn_cnt = 0;
//		wk->btn_seq = 3;
		wk->btn_flg = 0;
		break;
/*
	case 3:
		wk->btn_flg = 0;
		break;
*/
	}
}

void BattlePokeList_ButtonPageScreenInit( BPLIST_WORK * wk, u8 page )
{
	u16	i, j;

	switch( page ){
	case BPLIST_PAGE_SELECT:		// �|�P�����I���y�[�W
		for( i=0; i<6; i++ ){
			j = BattlePokeList_PokeSetCheck( wk, i );
			if( j == 0 ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE1+i, BPL_BANM_NONE, 1 );
			}else if( j == 1 ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE1+i, BPL_BANM_PAT0, 0 );
			}else if( j == 2 ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE1+i, BPL_BANM_PAT0, 1 );
			}
		}
		if( wk->dat->mode == BPL_MODE_NO_CANCEL ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, BPL_BANM_NONE, 0 );
		}else{
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, BPL_BANM_PAT0, 0 );
		}
		break;

	case BPLIST_PAGE_POKE_CHG:		// �|�P��������ւ��y�[�W
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE_CHG, 0, 0 );
		if( wk->poke[wk->dat->sel_poke].egg != 0 ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_STATUS1, BPL_BANM_NONE, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZASEL1, BPL_BANM_NONE, 0 );
		}else{
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_STATUS1, BPL_BANM_PAT0, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZASEL1, BPL_BANM_PAT0, 0 );
		}
		break;

	case BPLIST_PAGE_MAIN:			// �X�e�[�^�X���C���y�[�W
		if( BPL_PokeChangeButtonCheck( wk ) == TRUE ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_UP, BPL_BANM_PAT0, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_DOWN, BPL_BANM_PAT0, 0 );
		}else{
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_UP, BPL_BANM_NONE, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_DOWN, BPL_BANM_NONE, 0 );
		}
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZASEL2, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		break;

	case BPLIST_PAGE_WAZA_SEL:		// �X�e�[�^�X�Z�I���y�[�W
		if( BPL_PokeChangeButtonCheck( wk ) == TRUE ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_UP, BPL_BANM_PAT0, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_DOWN, BPL_BANM_PAT0, 0 );
		}else{
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_UP, BPL_BANM_NONE, 0 );
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_DOWN, BPL_BANM_NONE, 0 );
		}
		for( i=0; i<4; i++ ){
			if( wk->poke[wk->dat->sel_poke].waza[i].id != 0 ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZA1+i, BPL_BANM_PAT0, 0 );
			}else{
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZA1+i, BPL_BANM_NONE, 0 );
			}
		}
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_STATUS2, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		break;

	case BPLIST_PAGE_SKILL:			// �X�e�[�^�X�Z�ڍ׃y�[�W
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		for( i=0; i<4; i++ ){
			if( wk->dat->sel_wp == i ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZAPOS1+i, BPL_BANM_PAT2, 0 );
			}else{
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZAPOS1+i, BPL_BANM_PAT0, 0 );
			}
		}
		break;

	case BPLIST_PAGE_PP_RCV:		// PP�񕜋Z�I���y�[�W
		for( i=0; i<4; i++ ){
			if( wk->poke[wk->dat->sel_poke].waza[i].id != 0 ){
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZARCV1+i, BPL_BANM_PAT0, 0 );
			}else{
				BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZARCV1+i, BPL_BANM_NONE, 0 );
			}
		}
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		break;

	case BPLIST_PAGE_WAZASET_BS:	// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
	case BPLIST_PAGE_WAZASET_CS:	// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�ڍׁj
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL1, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL2, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL3, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL4, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL5, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		if( wk->ev_contest == 1 ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_CONTEST, 0, 0 );
		}
		break;

	case BPLIST_PAGE_WAZASET_BI:	// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL_B, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		if( wk->ev_contest == 1 ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_CONTEST, 0, 0 );
		}
		break;

	case BPLIST_PAGE_WAZASET_CI:	// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�I���j
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_WAZADEL_C, 0, 0 );
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_RET, 0, 0 );
		if( wk->ev_contest == 1 ){
			BPL_ButtonScreenWrite( wk, BPL_BUTTON_CONTEST, 0, 0 );
		}
		break;
	}
}

void BattlePokeList_ButtonPalSet( BPLIST_WORK * wk, u8 page )
{
	if( page == BPLIST_PAGE_WAZA_SEL ){
		PaletteWorkSet( wk->pfd, &wk->wb_pal[16], FADE_SUB_BG, BPL_PAL_B_GREEN*16, 0x20 );
	}else{
		PaletteWorkSet( wk->pfd, &wk->wb_pal[0], FADE_SUB_BG, BPL_PAL_B_GREEN*16, 0x20 );
	}
}

static u8 BPL_PokeChangeButtonCheck( BPLIST_WORK * wk )
{
	u16	i, j;

	j = 0;
	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons != 0 && wk->poke[i].egg == 0 ){
			j++;
		}
	}
	if( j >= 2 ){
		return TRUE;
	}
	return FALSE;
}

// �m���񕜎��ɋ����I�Ƀv���[�g�̐F��ς���
void BPL_HPRcvButtonPut( BPLIST_WORK * wk )
{
	if( BattlePokeList_PokeSetCheck( wk, wk->dat->sel_poke ) == 2 ){
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE1+wk->dat->sel_poke, 0, 1 );
	}else{
		BPL_ButtonScreenWrite( wk, BPL_BUTTON_POKE1+wk->dat->sel_poke, 0, 0 );
	}
}
