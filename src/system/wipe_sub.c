//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_sub.c
 *@brief	��ʂ��肩�����C�v����
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "string.h"
#include "calctool.h"
#include "system/wipe_def.h"
#include "system/wipe.h"
#include "include/gflib/sdkdef.h"
#include "include/system/brightness.h"

#define __WIPE_SUB_H_GLOBAL
#include "system/wipe_sub.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define SUM_NUM_MINI	(128)
#define ROTA_NUM(x)		((0xffff*(x))/360)

// �h�A�p
// ���̒l��,���̊J���Ă���l������Ɗp�x���o�Ă���
#define	WIPE_DOOR_ROTA_NUM	(21)
//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�}�X�^�[�u���C�g�l�X�t�F�[�h���[�N
//	
//=====================================
typedef struct {
	int a_count;	// �ω����i�i�K���j
	int piece_sync;	// �P�Ђ̃V���N��
	int sync_c;		// �V���N�J�E���g

	int set_num;
	int end_num;
	int add_num;
	int disp;
	
} WIPE_BRIGHTNESS_FADE;


//-------------------------------------
//	
//	�E�B���h�E���W���p�b�N
//	
//=====================================
typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} WIPE_WND_POSITION;


//-------------------------------------
//	
//	�E�B���h�E�ό`�\����
//
//	�V���b�^�[�E�C��/�A�E�g
//	�X���C�h�E�C��/�A�E�g
//	�V���b�^�[�E�C��/�A�E�g
//	�{�b�N�X�E�C��/�A�E�g
//	�����p�\���̂ł��B
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// �J�n���W
	WIPE_WND_POSITION add;	// ���Z���W
	WIPE_WND_POSITION ed;	// �I�����W

	int disp;		// ��
	int wnd_no;		// �E�B���h�E�i���o�[
	
	int a_count;	// �ω����i�i�K���j
	int piece_sync;	// �P�Ђ̃V���N��
	int sync_c;		// �V���N�J�E���g
	int fade_flg;	// �t�F�[�h�t���O

	WNDP_SYS_PTR wnd_sys;
} WIPE_TYPE_WND_MOVE;

//-------------------------------------
//	
//	�E�B���h�E�ό`�������p
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// �J�n���W
	WIPE_WND_POSITION ed;	// �I�����W

	u8 wnd_no;		// �E�B���h�E�i���o�[

	u8 in_wnd;		// �E�B���h�E�̒�
	u8 out_wnd;	// �E�B���h�E�̊O

	u8 fade_flg;	// �t�F�[�h�t���O

} WIPE_TYPE_WND_MOVE_FP;


//-------------------------------------
//	
//	�E�B���h�E�ό`�\����
//	�E�B���h�E���Q�g���Ƃ��悤
//
//	�X�v���b�g�E�C��/�A�E�g
//	
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE wnd0;
	WIPE_TYPE_WND_MOVE wnd1;
} WIPE_TYPE_WND_DMOVE;

//-------------------------------------
//	
//	HBlank����wnd�f�[�^
//	�\����
//	
//=====================================
typedef struct {
	short	wnd_data[2][192];	// wnd�f�[�^
	short	wnd_tmp[2][192];		// ���C�����[�v�v�Z�p
	
	int wnd_no;		// �E�B���h�E�i���o�[
} WIPE_TYPE_HB_WND_ONE;

//-------------------------------------
//	
//	Hblank����wnd�f�[�^��
//	���˂��\����
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND_ONE* data;
	int wnd_data_num;
	int disp;		// ��
} WIPE_TYPE_HB_WND;


//-------------------------------------
//	
//	HBlank���g�p���~��wnd�ŕ`���V�X�e����
//	�\����
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_circle;	// HblankCIRCLE�f�[�^
	int	r;		// ���a
	int x;		// ���S���W
	int y;
	int add_r;		// ���a�ω��l
	int a_count;	// �ω����i�i�K���j
	int piece_sync;	// �P�Ђ̃V���N��
	int sync_c;		// �V���N�J�E���g
	int heap;		// �g�p����q�[�v
	int fade_flg;	// �t�F�[�h�t���O

	WNDP_SYS_PTR wnd_sys;	// �E�B���h�E�ݒ�f�[�^�ۑ��̈�
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
} WIPE_TYPE_WND_CIRCLE;

//-------------------------------------
//	
//	HBlank���g�p���~��wnd�ŕ`���V�X�e��
//	�p�b�N�֐��̈���
//	
//=====================================
typedef struct {
	int r;
	int e_r;
	short x;
	short y;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_CIRCLE_FP;

//-------------------------------------
//	
//	HBlank���g�p���J�[�e����wnd�ŕ`���V�X�e����
//	�\����
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_c;	// Hblank�f�[�^
	int rota;		// �J���p�x
	int rota_add;	// �P��ŊJ���p�x
	int a_count;	// �ω����i�i�K���j
	int piece_sync;	// �P�Ђ̃V���N��
	int sync_c;		// �V���N�J�E���g
	int fade_flg;	// �t�F�[�h�t���O

	WNDP_SYS_PTR wnd_sys;
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N

	int heap;		// �g�p����q�[�v
} WIPE_TYPE_WND_CURTAIN;

//-------------------------------------
//	
//	HBlank���g�p���J�[�e����\������V�X�e��
//	�p�b�N�֐��̈���
//	
//=====================================
typedef struct {
	int rota;
	int e_rota;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_CURTAIN_FP;


//-------------------------------------
//	
//	HBlank���g�p���h�A��wnd�ŕ`���V�X�e����
//	�\����
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_d;	// Hblank�f�[�^
	int open_max;	// �ő�̊J������
	int open_r;		// �J����]�l
	int open_r_a;	// �����l
	int a_count;	// �ω����i�i�K���j
	int piece_sync;	// �P�Ђ̃V���N��
	int sync_c;		// �V���N�J�E���g
	int fade_flg;	// �t�F�[�h�t���O

	WNDP_SYS_PTR wnd_sys;
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
	int heap;		// �g�p����q�[�v
} WIPE_TYPE_WND_DOOR;

//-------------------------------------
//	
//	HBlank���g�p���h�A��\������V�X�e��
//	�p�b�N�֐��̈���
//	
//=====================================
typedef struct {
	int s_d;
	int e_d;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_DOOR_FP;

//-------------------------------------
//	
//	�������ꂽ�E�B���h�E�̊e�X�̐ݒ�
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// �J�n���W
	WIPE_WND_POSITION add;	// ���Z���W
	WIPE_WND_POSITION ed;	// �I�����W
} WIPE_TYPE_WND_D_PIECE;

//-------------------------------------
//	
//	�P�̃E�B���h�E�𕡐��̃E�B���h�E
//	�g�p���Ă��邩�̂悤�Ɏg�p����
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb_divi;		// Hblank�ݒ�f�[�^
	
	WIPE_TYPE_WND_D_PIECE* piece_tbl;		// ���������f�[�^
	int						piece_num;		// �E�B���h�E������

	int a_count;		// �ω����i�i�K���j
	int piece_sync;		// �P�Ђ̃V���N��
	int sync_c;			// �V���N�J�E���g
	int fade_flg;	// �t�F�[�h�t���O

	WNDP_SYS_PTR wnd_sys;	// �E�B���h�EVblank�ύX�V�X�e���̃��[�N
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
	int heap;			// �g�p����q�[�v
} WIPE_TYPE_WND_DIVI;

//-------------------------------------
//	
//	�P�̃E�B���h�E�𕡐��̃E�B���h�E
//	�g�p���Ă��邩�̂悤�Ɏg�p����	
//	�����p
//=====================================
typedef struct {
	const WIPE_WND_POSITION* p_st;	// ���������e�X�̊J�n���W	�D�揇�ʁi�O�����j
	const WIPE_WND_POSITION* p_ed;	// ���������e�X�̏I�����W
	u8 divi_num;				// ������
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_DIVI_FP;


//-------------------------------------
//	
//	�X�N�����[�P�̃f�[�^
//	
//=====================================
typedef struct {
	int	rota;		// ���݂̉�]�p
	int s_rota;		// ��]�p�x�����l
	int add_num_rota;	// ��]�p�x�̍ő�ω��l
} WIPE_TYPE_WND_SCREW_ONE;

//-------------------------------------
//	
//	�X�N�����[�f�[�^�\����
//
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb;		// Hblank�ݒ�f�[�^
	
	WIPE_TYPE_WND_SCREW_ONE screw;	// �X�N�����[�f�[�^

	int a_count_max;	// �ω����i�i�K���j�ő吔
	int a_count;		// �ω����i�i�K���j�J�E���g�l
	int piece_sync;		// �P�Ђ̃V���N��
	int sync_c;			// �V���N�J�E���g
	int fade_flg;		// �t�F�[�h�t���O
	int heap;			// �q�[�v

	WNDP_SYS_PTR wnd_sys;	// �E�B���h�EVblank�ύX�V�X�e���̃��[�N
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
} WIPE_TYPE_WND_SCREW;

//-------------------------------------
//	
//	�X�N�����[����֐�����
//	
//=====================================
typedef struct {
	int	s_rota;		// �J�n��]�p
	int	e_rota;		// �I����]�p
	
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_SCREW_FP;

//-------------------------------------
//	
//	�t���b�V���S�����f�[�^
//	
//=====================================
typedef struct {
	int	rota;		// ���݂̉�]�p
	int s_rota;		// ��]�p�x�����l
	int add_num_rota;	// ��]�p�x�̍ő�ω��l
} WIPE_TYPE_WND_FLASH_FOUR_ONE;

//-------------------------------------
//	
//	�t���b�V���S�����f�[�^�\����
//
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb;		// Hblank�ݒ�f�[�^
	
	WIPE_TYPE_WND_FLASH_FOUR_ONE screw;	// �X�N�����[�f�[�^

	int a_count_max;	// �ω����i�i�K���j�ő吔
	int a_count;		// �ω����i�i�K���j�J�E���g�l
	int piece_sync;		// �P�Ђ̃V���N��
	int sync_c;			// �V���N�J�E���g
	int fade_flg;		// �t�F�[�h�t���O
	int heap;			// �q�[�v

	WNDP_SYS_PTR wnd_sys;	// �E�B���h�EVblank�ύX�V�X�e���̃��[�N
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
} WIPE_TYPE_WND_FLASH_FOUR;

//-------------------------------------
//	
//	�t���b�V���S��������֐�����
//	
//=====================================
typedef struct {
	int	s_rota;		// �J�n��]�p
	int	e_rota;		// �I����]�p
	
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_FLASH_FOUR_FP;

//-------------------------------------
//	V����WND����@H�u�����N���[�N
//=====================================
typedef struct {
	u8 in_out_write[ 192 ];	// in_wnd out_wnd�t���O
	u8 in_out_read[ 192 ];	// in_wnd out_wnd�t���O
	
	int wnd_no;
} WIPE_TYPE_WND_VMOVE_HDATA;

//-------------------------------------
//	V����WND����@���˂��f�[�^
//=====================================
typedef struct {
	WIPE_TYPE_WND_VMOVE_HDATA data[2];
	u8 wnd_data_num;	// �E�B���h�E�g�p��(�ő�2)
	u8 disp;		// ��
} WIPE_TYPE_WND_VMOVE;
enum{
	WIPE_WND_VMOVE_INWND,
	WIPE_WND_VMOVE_OUTWND
};

//-------------------------------------
//	
//	�c����H�u�����N�g�p�E�B���h�E����
//	�V�X�e��
//	
//=====================================
//-------------------------------------
//	����f�[�^
//
//	in_out�̗̈悪s_y����e_y�ւƍL�����Ă����܂�
//=====================================
typedef struct {
	u8 s_y;		
	u8 e_y;
	u8 in_out;		// WIPE_WND_VMOVE_INWND, WIPE_WND_VMOVE_OUTWND
} WIPE_TYPE_WND_VMOVE_DATA;

//-------------------------------------
//	�Ǘ��f�[�^
//=====================================
typedef struct {
	WIPE_TYPE_WND_VMOVE HblankData;	// H�u�����N�f�[�^

	const WIPE_TYPE_WND_VMOVE_DATA* p_param;
	int param_num;

	int a_count_max;	// �ω����i�i�K���j�ő吔
	int a_count;		// �ω����i�i�K���j�J�E���g�l
	int piece_sync;		// �P�Ђ̃V���N��
	int sync_c;			// �V���N�J�E���g
	int fade_flg;		// �t�F�[�h�t���O
	int heap;			// �q�[�v

	WNDP_SYS_PTR wnd_sys;	// �E�B���h�EVblank�ύX�V�X�e���̃��[�N
	WIPE_HBLANK* p_wipehb;	// ���C�vHBlank���[�N
} WIPE_TYPE_WND_VMOVE_CONT;

//-------------------------------------
//	�p�����[�^
//=====================================
typedef struct {
	const WIPE_TYPE_WND_VMOVE_DATA* cp_data;
	u8 data_num;
	u8 fade_flg;
} WIPE_TYPE_WND_VMOVE_PARAM;


//-------------------------------------
//
//	
//		�|�P�������C�v
//
//	
//=====================================
//-------------------------------------
//	�p�����[�^
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE_FP wnd_move;
	WIPE_TYPE_WND_VMOVE_PARAM wnd_split;
	fx32 sync_div_par;	// �V���N���̊����iwnd_move�̊����j
} WIPE_TYPE_WND_PESOCOM_PARAM;

//-------------------------------------
//	���[�N
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE wnd_move;
	WIPE_TYPE_WND_VMOVE_CONT wnd_split;
	WIPE_TYPE_WND_PESOCOM_PARAM* p_param;
	u8 sub_divi;
	u8 seq;	// �V�[�P���X
	u8 fade_flg;
	u8 dummy;
} WIPE_TYPE_WND_PESOCOM;




//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// �e��v�Z�p
static fx32 sum_tan(int rota);
static int sub_rota_height_width_one( int rota, int height );
static void sum_rota_height_width(int rota, int* depth, int work_num, int s_h);
static int sum_triangle_height(int rota, int undefground);
static int sum_add_num(int st, int ed, int divi);
static int sum_add_wnd_width(int num1, int num2);
static void sum_add_wnd(WIPE_WND_POSITION* num, WIPE_WND_POSITION* add);
static void sum_set_wnd_position(WIPE_WND_POSITION* st, WIPE_WND_POSITION* ed, WIPE_WND_POSITION* add, const WIPE_WND_POSITION* set_st, const WIPE_WND_POSITION* set_ed, int division );

// �E�B���h�E�����p
static void scchg_WndEnd(int flag, WNDP_SYS_PTR wnd_sys, int disp);
static void scchg_h_Wnd(void* work);
static void scchg_h_WndMake(WIPE_TYPE_HB_WND* data, int flag, int disp, int heap);
static void scchg_h_WndDel(WIPE_TYPE_HB_WND* data);
static void scchg_v_h_WndDel( TCB_PTR tcb, void* work );
static void scchg_main_h_WndDel( WIPE_TYPE_HB_WND* data );
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndNoDataGet(WIPE_TYPE_HB_WND* data, int wnd_no);
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndIdxDataGet(WIPE_TYPE_HB_WND* data, int idx);
static void scchg_WndSwap(TCB_PTR tcb, void* work);
static void scchg_WndSetUp(WNDP_SYS_PTR wnd_sys, int in_wnd, int out_wnd, int wnd_no, int disp, int x1, int y1, int x2, int y2, int fade_flg);
static void scchg_WndVisible(WNDP_SYS_PTR wnd_sys, int plane, int disp, int fade_flg);

// �E�B���h�EY���쏈���p
static void scchg_h_VMoveWndInit( WIPE_TYPE_WND_VMOVE* p_wnddata, int disp, int data_num, int wnd_no0, int wnd_no1 );

static void scchg_h_VMoveWnd_SwapReq( WIPE_TYPE_WND_VMOVE* p_wnddata );
static void scchg_h_VMoveWnd_Start( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap );
static void scchg_h_VMoveWnd_End( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap );

static void scchg_h_VMoveWnd_Swap( TCB_PTR tcb, void* p_work );
static void scchg_h_VMoveWnd_Main( void* p_work );


// �u���C�g�l�X�t�F�[�h�����p
static void scchg_FadeInit(WIPE_SYS_WIPE_WORK* wipe, int fade_flag);
static BOOL scchg_FadePack(WIPE_SYS_WIPE_WORK* wipe);
static BOOL scchg_FadeCalcMain( WIPE_BRIGHTNESS_FADE* data );

// �l�p�\���E�B���h�E�����p
static void scchg_WndMovePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram );
static BOOL scchg_WndMovePack(WIPE_SYS_WIPE_WORK* wipe);

static void scchg_WndMoveDoublePackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram1, const WIPE_TYPE_WND_MOVE_FP* pram2);
static BOOL scchg_WndMoveDoublePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndMoveInit(WIPE_TYPE_WND_MOVE* data, const WIPE_TYPE_WND_MOVE_FP* pram, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys);
static BOOL scchg_WndMoveMain(WIPE_TYPE_WND_MOVE* data);

// �~�\���E�B���h�E�����p
static void scchg_WndCirclePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CIRCLE_FP* param );
static BOOL scchg_WndCirclePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndCircleInit(WIPE_TYPE_WND_CIRCLE* data, const WIPE_TYPE_WND_CIRCLE_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap);
static BOOL scchg_WndCircleMain(WIPE_TYPE_WND_CIRCLE* data);
static void scchg_WndCircleSum(WIPE_TYPE_WND_CIRCLE* work);

// �J�[�e���^�E�B���h�E�\���p
static void scchg_WndCurtainPackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CURTAIN_FP* param);
static BOOL scchg_WndCurtainPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndCurtainInit(WIPE_TYPE_WND_CURTAIN* data, const WIPE_TYPE_WND_CURTAIN_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndCurtainMain(WIPE_TYPE_WND_CURTAIN* data);
static void scchg_WndCurtainSum(WIPE_TYPE_WND_CURTAIN* work);

// �h�A�^�E�B���h�E�\���p

static void scchg_WndDoorPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DOOR_FP* param);
static BOOL scchg_WndDoorPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndDoorInit(WIPE_TYPE_WND_DOOR* data, const WIPE_TYPE_WND_DOOR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndDoorMain(WIPE_TYPE_WND_DOOR* data);
static void scchg_WndDoorSum(WIPE_TYPE_WND_DOOR* work);

// 1�E�B���h�E���������V�X�e��
static void scchg_WndDivisionPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DIVI_FP* param);
static BOOL scchg_WndDivisionPack(WIPE_SYS_WIPE_WORK* wipe);
static BOOL scchg_WndDivisionMain(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionInit(WIPE_TYPE_WND_DIVI* data, const WIPE_TYPE_WND_DIVI_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static void scchg_WndDivisionEnd(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionSum(WIPE_TYPE_WND_DIVI* work);
static void scchg_WndDivisionMainSub(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionSumSub(WIPE_TYPE_HB_WND* hb_divi, WIPE_WND_POSITION* set);

// �X�N�����[
static void scchg_WndScrewPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_SCREW_FP* param);
static BOOL scchg_WndScrewPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndScrewInit(WIPE_TYPE_WND_SCREW* data, WIPE_TYPE_WND_SCREW_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndScrewMain(WIPE_TYPE_WND_SCREW* data);
static void scchg_WndScrewEnd(WIPE_TYPE_WND_SCREW* data);
static void scchg_WndScrewSum(WIPE_TYPE_WND_SCREW* work);
static void scchg_WndScrewOneAdd( WIPE_TYPE_WND_SCREW_ONE* p_data, int count, int count_max );

// �t���b�V���@�S
static void scchg_WndFlashFourPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_FLASH_FOUR_FP* param);
static BOOL scchg_WndFlashFourPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndFlashFourInit(WIPE_TYPE_WND_FLASH_FOUR* data, WIPE_TYPE_WND_FLASH_FOUR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndFlashFourMain(WIPE_TYPE_WND_FLASH_FOUR* data);
static void scchg_WndFlashFourEnd(WIPE_TYPE_WND_FLASH_FOUR* data);
static void scchg_WndFlashFourSum(WIPE_TYPE_WND_FLASH_FOUR* work);
static void scchg_WndFlashFourOneAdd( WIPE_TYPE_WND_FLASH_FOUR_ONE* p_data, int count, int count_max );


// H�u�����N�g�p	�E�B���h�EY�����ړ��V�X�e��
static void scchg_WndWndVMovePackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_VMOVE_PARAM* param);
static BOOL scchg_WndWndVMovePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndWndVMoveInit(WIPE_TYPE_WND_VMOVE_CONT* data, WIPE_TYPE_WND_VMOVE_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndVMoveMain(WIPE_TYPE_WND_VMOVE_CONT* data);
static void scchg_WndWndVMoveEnd(WIPE_TYPE_WND_VMOVE_CONT* data);
static void scchg_WndWndVMoveSum(WIPE_TYPE_WND_VMOVE_CONT* work);
static void scchg_WndWndVMoveSub_Core( const WIPE_TYPE_WND_VMOVE_DATA* p_one, WIPE_TYPE_WND_VMOVE_HDATA* p_buff, int count, int count_max );


// �p�\�R�����C�v
static void scchg_WndWndPesocomPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_PESOCOM_PARAM* param);
static BOOL scchg_WndWndPesocomPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndWndPesocomInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndPesocomMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe );
static void scchg_WndWndPesocomOutInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndPesocomOutMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe );



//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�F�[�h�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	BOOL	TRUE�F�I���@FALSE�F���s
 *
 * �t�F�[�h�A�E�g
 *	��ʂ����X�ɈÂ��Ȃ��Ă���
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc00(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_BRI;
		
		scchg_FadeInit(wipe, WIPE_FADE_OUT);
		return FALSE;
	}
	return scchg_FadePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�F�[�h�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	BOOL	TRUE�F�I���@FALSE�F���s
 *
 *  �t�F�[�h�C��
 *		��ʂ����X�ɖ��邭�Ȃ�A��ʂ��\�������
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc01(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_BRI;
		
		scchg_FadeInit(wipe, WIPE_FADE_IN);
		return FALSE;
	}
	return scchg_FadePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�V���b�^�[�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	noen
 *
 * �ォ�牺�ւ̃V���b�^�[�A�E�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc02(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			0, 192, WIPE_WND_VMOVE_OUTWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_OUT
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�V���b�^�[�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �ォ�牺�ւ̃V���b�^�[�C��
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc03(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			0, 192, WIPE_WND_VMOVE_INWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_IN
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�V���b�^�[�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	noen
 *
 * �������ւ̃V���b�^�[�A�E�g
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc04(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			192, 0, WIPE_WND_VMOVE_OUTWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_OUT
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�V���b�^�[�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �������ւ̃V���b�^�[�C��
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc05(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			192, 0, WIPE_WND_VMOVE_INWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_IN
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X���C�h�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc06(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{0,0,0,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X���C�h�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc07(WIPE_SYS_WIPE_WORK* wipe)
{

	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,0,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN	
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �c�@��ʏ㉺����
 * 
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc08(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 0, 96, WIPE_WND_VMOVE_OUTWND },
			{ 192, 96, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �c�@��ʒ�������
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc09(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 96, 0, WIPE_WND_VMOVE_INWND },
			{ 96, 192, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �c�@��ʒ�������
 * 
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc10(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 96, 0, WIPE_WND_VMOVE_OUTWND },
			{ 96, 192, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * �c�@��ʏ㉺����
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc11(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 0, 96, WIPE_WND_VMOVE_INWND },
			{ 192, 96, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * ���@��ʍ��E����
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc12(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,0,128,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * ���@��ʒ�������
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc13(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,0,128,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * ���@��ʒ�������
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc14(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_MOVE_FP param1 = {
			{128,0,128,192},
			{0,0,128,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};
		static const WIPE_TYPE_WND_MOVE_FP param2 = {
			{128,0,128,192},
			{128,0,255,192},
			WNDP_WND_1,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};
	
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMoveDoublePackInit(wipe, &param1, &param2);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMoveDoublePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�v���b�g�E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 * ���@��ʍ��E����
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc15(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_MOVE_FP param1 = {
			{0,0,128,192},
			{128,0,128,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};
		static const WIPE_TYPE_WND_MOVE_FP param2 = {
			{128,0,255,192},
			{128,0,128,192},
			WNDP_WND_1,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};
	
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMoveDoublePackInit(wipe, &param1, &param2);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMoveDoublePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�z�[���E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc16(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			256,0,
			128,96,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�z�[���E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�C��
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc17(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,256,
			128,96,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g���l���E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc18(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			512,0,
			128,288,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g���l���E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�C��
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc19(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,512,
			128,288,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );
		
		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�[�e���E�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc20(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CURTAIN_FP param = {
			ROTA_NUM(90),
			0,
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCurtainPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndCurtainPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�[�e���E�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc21(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CURTAIN_FP param = {
			0,
			ROTA_NUM(90),// tan90�͒l�s��ɂȂ�̂ŁA���������90�ɂ��Ă��܂��B
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCurtainPackInit(wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndCurtainPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�{�b�N�X�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none	
 *
 * �O���璆
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc22(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,96,128,96},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�{�b�N�X�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 * ������O
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc23(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,96,128,96},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�{�b�N�X�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none	
 *
 *	������O
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc24(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,96,128,96},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);
		
		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�{�b�N�X�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 * �O���璆
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc25(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,96,128,96},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc26(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_DOOR_FP param = {
			ROTA_NUM(90),
			ROTA_NUM(0),
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDoorPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
		
	return scchg_WndDoorPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc27(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_DOOR_FP param = {
			ROTA_NUM(0),
			ROTA_NUM(90),
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDoorPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndDoorPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I���^�l�[�g�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc28(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_WND_POSITION st[] = {
			{0,0,255,48},
			{0,47,255,96},
			{0,96,255,144},
			{0,144,255,192}
		};
		static const WIPE_WND_POSITION ed[] = {
			{0,0,0,48},
			{255,47,255,96},
			{0,96,0,144},
			{255,144,255,192}
		};
		WIPE_TYPE_WND_DIVI_FP param;
		
		param.p_st			= st;
		param.p_ed			= ed;
		param.divi_num		= 4;
		param.wnd_no		= WNDP_WND_0;
		param.in_wnd		= GX_BLEND_ALL;
		param.out_wnd		= GX_BLEND_PLANEMASK_BD;
		param.fade_flg		= WIPE_FADE_OUT;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDivisionPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndDivisionPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I���^�l�[�g�E�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc29(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_WND_POSITION st[] = {
			{255,0,255,48},
			{0,47,0,96},
			{255,96,255,144},
			{0,144,0,192}
		};
		static const WIPE_WND_POSITION ed[] = {
			{0,0,255,48},
			{0,47,255,96},
			{0,96,255,144},
			{0,144,255,192}
		};
		WIPE_TYPE_WND_DIVI_FP param;
		
		param.p_st			= st;
		param.p_ed			= ed;
		param.divi_num		= 4;
		param.wnd_no		= WNDP_WND_0;
		param.in_wnd		= GX_BLEND_ALL;
		param.out_wnd		= GX_BLEND_PLANEMASK_BD;
		param.fade_flg		= WIPE_FADE_IN;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDivisionPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndDivisionPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�u���C���h�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc30(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[3] = {
			{ 0, 64, WIPE_WND_VMOVE_OUTWND },
			{ 64, 128, WIPE_WND_VMOVE_OUTWND },
			{ 128, 192, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			3,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�u���C���h�E�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc31(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[3] = {
			{ 64, 0, WIPE_WND_VMOVE_INWND },
			{ 128, 64, WIPE_WND_VMOVE_INWND },
			{ 192, 128, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			3,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�N�����[�E�A�E�g
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc32(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_SCREW_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(179),	
			GX_BLEND_PLANEMASK_BD,
			GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndScrewPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndScrewPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�N�����[�E�C��
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc33(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_SCREW_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(179),	
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndScrewPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndScrewPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t���b�V���E�A�E�g�@�S
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc34(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_FLASH_FOUR_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(45), 
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndFlashFourPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndFlashFourPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t���b�V���E�C��	�S
 *
 *@param	wipe	���C�v���[�N
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc35(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_FLASH_FOUR_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(45),	// 45�ɂ����Ȃ��ƌ��Ԃ������Ă��܂����B
			GX_BLEND_PLANEMASK_BD,
			GX_BLEND_ALL,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndFlashFourPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndFlashFourPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g���l���E�A�E�g	�ォ��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�A�E�g
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc36(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			512,0,
			128,-80,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g���l���E�C��		�ォ��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *	�~�`�t�F�[�h�C��
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc37(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,512,
			128,-80,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X���C�h�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	noen
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc38(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,0,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X���C�h�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc39(WIPE_SYS_WIPE_WORK* wipe)
{

	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{0,0,0,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN	
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p�\�R���@�A�E�g
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	noen
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc40(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_VMOVE_DATA split_data[2] = {
			{0, 94, WIPE_WND_VMOVE_OUTWND},
			{192, 98, WIPE_WND_VMOVE_OUTWND},
		};
		static WIPE_TYPE_WND_PESOCOM_PARAM param ={
			{
				{0,94,255,98},
				{128,96,128,96},
				WNDP_WND_0,
				GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
				WIPE_FADE_OUT
			},
			{
				NULL,
				2,
				WIPE_FADE_OUT
			},
			FX32_CONST( 0.70f )
		};
		param.wnd_split.cp_data = split_data;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndPesocomPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndWndPesocomPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p�\�R���@�C��
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc41(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_VMOVE_DATA split_data[2] = {
			{94, 0, WIPE_WND_VMOVE_INWND},
			{98, 192, WIPE_WND_VMOVE_INWND},
		};
		static WIPE_TYPE_WND_PESOCOM_PARAM param ={
			{
				{128,96,128,96},
				{0,94,255,98},
				WNDP_WND_0,
				GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
				WIPE_FADE_IN
			},
			{
				NULL,
				2,
				WIPE_FADE_IN
			},
			FX32_CONST( 0.70f )
		};
		param.wnd_split.cp_data = split_data;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndPesocomPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndWndPesocomPack(wipe);
}



//-----------------------------------------------------------------------------
//
//	�e���C�v�Ŏg�p����֐��S
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�^���W�F���g�v�Z
 *
 *@param	rota		��]�p
 *
 *@return	fx32		tan(rota)�̒l
 *
 *	�^���W�F���g�͊p�x�X�O�̂Ƃ��́A�s��l�ɂȂ�̂Œ��ӂ��Ă�������
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32 sum_tan(int rota)
{
	return FX_Div(FX_SinIdx(rota), FX_CosIdx(rota));
}
//----------------------------------------------------------------------------
/**
 *	@brief	��]�p�ƍ������畝�����߂�
 *
 *	@param	rota		��]�p�x
 *	@param	height		����
 *
 *	@return	��
 */
//-----------------------------------------------------------------------------
static int sub_rota_height_width_one( int rota, int height )
{
	fx32	tan;			// �^���W�F���g�v�Z�p
	fx32	width;			// ���v�Z�p

	// �^���W�F���g�v�Z
	tan = sum_tan(rota);
	
	// �^���W�F���g���g�p���A���̊p�x�ŁA�����̎��̕������߂�
	width = FX_Mul(tan, height << FX32_SHIFT);
	width >>= FX32_SHIFT;
	
	return width;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p����o�b�t�@�ɂ��̊p�x�ŁA�����̂Ƃ��̕������߂�
 *
 *@param	rota		��]�p
 *@param	depth		���i�[���[�N
 *@param	work_num	���[�N�̔z��v�f��
 *@param	s_h			�����J�n�n�_�i�v�f�������[�v�ł܂킷�j
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_rota_height_width(int rota, int* depth, int work_num, int s_h)
{
	int i;
	fx32	tan;			// �^���W�F���g�v�Z�p
	fx32	width, height;	// ���v�Z�p
	int st,ed;

	// �^���W�F���g�v�Z
	tan = sum_tan(rota);
	
	// �eY���W�ł̕���������
	for(i=s_h;i<work_num;i++){
		// �^���W�F���g���g�p���A���̊p�x�ŁA�����̎��̕������߂�
		height = i<<FX32_SHIFT;
		width = FX_Mul(tan, height);
		width >>= FX32_SHIFT;
		*(depth+i) = width;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�O�p�`�̊p�x�ƒ�ӂ��獂�������߂�
 *
 *@param	rota			�p�x
 *@param	underground		��ӂ̒���
 *
 *@return	int		����
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_triangle_height(int rota, int underground)
{
	fx32 tan;
	fx32 ug;
	int h;

	tan = sum_tan(rota);
	ug = (underground/2) << FX32_SHIFT;
	h = FX_Div(ug ,tan);
	return h;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	����������P��ɑ����l�����߂�
 *
 *@param	st		�J�n�_
 *@param	ed		�I���_
 *@param	divi	������
 *
 *@return	int		"SUM_NUM_MINI�{�ɂ��ꂽ1��ɑ����l"
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_add_num(int st, int ed, int divi)
{
	int add;

	add = ed - st;
	add *= SUM_NUM_MINI;
	add /= divi;
	return add;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E���W�𕝂��O�`�Q�T�T�𒴂��Ȃ��悤�ɑ���
 *
 *@param	num1		�����l�P
 *@param	num2		�����l�Q
 *
 *@return	int		�������l
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_add_wnd_width(int num1, int num2)
{
	int num;

	num = num1+num2;
	if(num < 0){
		num = 0;
	}
	if(num > 255){
		num = 255;
	}

	return num;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�|�W�V�����f�[�^�𑫂�����
 *
 *@param	num		�������ޒl�ւ̃|�C���^	
 *@param	add		�����l�ւ̃|�C���^
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_add_wnd(WIPE_WND_POSITION* num, WIPE_WND_POSITION* add)
{
	num->x1 += add->x1;
	num->y1 += add->y1;
	num->x2 += add->x2;
	num->y2 += add->y2;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�[�^��ݒ肷��
 *
 *@param	st			�J�n
 *@param	ed			�I��
 *@param	add			�����l
 *@param	set_st		�J�n���W�ݒ�f�[�^
 *@param	set_ed		�I�����W�ݒ�f�[�^
 *@param	division	������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_set_wnd_position(WIPE_WND_POSITION* st, WIPE_WND_POSITION* ed, WIPE_WND_POSITION* add, const WIPE_WND_POSITION* set_st, const WIPE_WND_POSITION* set_ed, int division )
{
	// ���W��ݒ�
	st->x1 = set_st->x1*SUM_NUM_MINI;
	st->y1 = set_st->y1*SUM_NUM_MINI;
	st->x2 = set_st->x2*SUM_NUM_MINI;
	st->y2 = set_st->y2*SUM_NUM_MINI;

	*ed = *set_ed;

	// �ړ��l���v�Z
	add->x1 = sum_add_num(set_st->x1, set_ed->x1, division);
	add->y1 = sum_add_num(set_st->y1, set_ed->y1, division);
	add->x2 = sum_add_num(set_st->x2, set_ed->x2, division);
	add->y2 = sum_add_num(set_st->y2, set_ed->y2, division);
}


//----------------------------------------------------------------------------
/**
 *@brief	�t�F�[�h�������p�b�N�����֐�	������
 *
 *@param	wipe		���C�v���[�N
 *@param	fade_flag	�t�F�[�h�E�C��
						�t�F�[�h�E�A�E�g	�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_FadeInit(WIPE_SYS_WIPE_WORK* wipe, int fade_flag)
{
	int start, end;					// �J�n�A�I���u���C�g�l�X�l
	WIPE_BRIGHTNESS_FADE* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof( WIPE_BRIGHTNESS_FADE ) );
	memset( wipe->wipe_work, 0, sizeof( WIPE_BRIGHTNESS_FADE ) );
	data = wipe->wipe_work;

	// �u���C�g�l�X�ݒ�
	// �J�n�u���C�g�l�X�l
	if( fade_flag == WIPE_FADE_IN ){
		if(wipe->color == WIPE_FADE_WHITE){
			start	= BRIGHTNESS_WHITE;
			end		= BRIGHTNESS_NORMAL;
		}else if(wipe->color == WIPE_FADE_BLACK){
			start	= BRIGHTNESS_BLACK;
			end		= BRIGHTNESS_NORMAL;
		}else{

			// �ꉞ�����悤�ɂ��Ă���
			start	= BRIGHTNESS_BLACK;
			end		= BRIGHTNESS_NORMAL;
			// �����ȊO�̐ݒ�
			GF_ASSERT_MSG( 0, "color %x", wipe->color );
		}
	}else{
		if(wipe->color == WIPE_FADE_WHITE){
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_WHITE;
		}else if(wipe->color == WIPE_FADE_BLACK){
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_BLACK;
		}else{

			// �ꉞ�����悤�ɂ��Ă���
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_BLACK;
			// �����ȊO�̐ݒ�
			GF_ASSERT_MSG( 0, "color %x", wipe->color );
		}
	}
	WIPE_SetMstBrightness( wipe->disp, start );
	

	// �u���C�g�l�X�ω��l�p�����[�^�ݒ�
	data->a_count		= wipe->division;
	data->piece_sync	= wipe->piece_sync;
	data->sync_c		= 0;
	data->set_num		= start * SUM_NUM_MINI;
	data->end_num		= end * SUM_NUM_MINI;
	data->add_num		= sum_add_num( start, end, wipe->division );
	data->disp			= wipe->disp;

	wipe->sequence++;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�F�[�h�������p�b�N�����֐�
 *
 *@param	wipe		���C�v���[�N
 *
 *@return	BOOL	�I���FTRUE	���s�FFALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_FadePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_BRIGHTNESS_FADE* data = wipe->wipe_work;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l

	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_FadeCalcMain(data);
		if(ret == TRUE){
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;

	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�u���C�g�l�X�t�F�[�h�v�Z���C��
 *
 *	@param	data	���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_FadeCalcMain( WIPE_BRIGHTNESS_FADE* data )
{
	BOOL ret = FALSE;
	
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;
	
			data->set_num += data->add_num;
		}else{
			data->set_num = data->end_num;
			ret = TRUE;
		}
		WIPE_SetMstBrightness( data->disp, data->set_num / SUM_NUM_MINI );
	}

	return ret;
}

// H�u�����N��p
static inline void wndp_setWndPosition_HBlank(int x1, int y1, int x2, int y2, int wnd_no, int disp)
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd0Position(x1,y1,x2,y2);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd0Position(x1,y1,x2,y2);
			}
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd1Position(x1,y1,x2,y2);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd1Position(x1,y1,x2,y2);
			}
		}
	}
}

static inline void set_H_WndData( WIPE_TYPE_HB_WND* shb, int v_c, int i )
{
	WIPE_TYPE_HB_WND_ONE* one;

	one = scchg_h_WndIdxDataGet(shb, i);	// �C���f�b�N�X�̃f�[�^�擾
	wndp_setWndPosition_HBlank(one->wnd_data[0][v_c], 0, one->wnd_data[1][v_c], 192, one->wnd_no, shb->disp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E��`��Hblank�֐�
 *
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_Wnd(void* work)
{
	WIPE_TYPE_HB_WND* shb = (WIPE_TYPE_HB_WND*)work;
	int v_c;
	int i;

	GF_ASSERT(work);

	v_c = GX_GetVCount();

	if(v_c < 192){
		v_c ++;
		if( v_c > 191 ){
			v_c -= 192;
		}

		if( shb->wnd_data_num == 1 ){
			set_H_WndData( shb, v_c, 0 );
		}else{
			set_H_WndData( shb, v_c, 0 );
			set_H_WndData( shb, v_c, 1 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	H�u�����N�E�B���h�E�f�[�^�쐬
 *
 *@param	data	�f�[�^�i�[��
 *@param	flag	�E�B���h�E�f�[�^�t���O
 *@param	disp	�\����
 *@param	heap	�g�p����q�[�v
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_WndMake(WIPE_TYPE_HB_WND* data, int flag, int disp, int heap)
{
	switch(flag){
	case WNDP_WND_0:	// �ǂ��炩�Е��̂Ƃ�
	case WNDP_WND_1:
		data->data = sys_AllocMemory(heap, sizeof(WIPE_TYPE_HB_WND_ONE));
		data->wnd_data_num	= 1;
		data->disp			= disp;
		data->data->wnd_no	= flag;		// flag = WND�i���o�[
		break;
	case 2:
		{
			int i;
			data->data = sys_AllocMemory(heap, sizeof(WIPE_TYPE_HB_WND_ONE)*2);
			data->wnd_data_num	= 2;
			data->disp			= disp;
			for(i=0;i<2;i++){			// �E�B���h�E�f�[�^�ݒ�
				data->data[i].wnd_no	= i;
			}
		}
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�f�[�^�j��
 *
 *@param	data	�j������E�B���h�E�f�[�^
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_WndDel(WIPE_TYPE_HB_WND* data)
{
//	VWaitTCB_Add( scchg_v_h_WndDel, data, WIPE_VBLANK_WND_DELETE_TCB );
	scchg_main_h_WndDel( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���ۂ�V�u�����N���Ƀ��[�N��j������֐�
 *
 *	@param	tcb		�^�X�N���[�N
 *	@param	work	�f�[�^
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_h_WndDel( TCB_PTR tcb, void* work )
{
	WIPE_TYPE_HB_WND* data = work;

	scchg_main_h_WndDel( data );

	TCB_Delete(tcb);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ۂɃ��[�N��j������֐�
 *
 *	@param	data 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_main_h_WndDel( WIPE_TYPE_HB_WND* data )
{
	sys_FreeMemoryEz(data->data);	
	data->data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�i���o�[�̃E�B���h�E�f�[�^���擾
 *
 *@param	wnd_no	�擾����E�B���h�E�i���o�[	
 *
 *@return	�E�B���h�E�f�[�^	�����Ƃ�NULL
 *
 *
 */
//-----------------------------------------------------------------------------
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndNoDataGet(WIPE_TYPE_HB_WND* data, int wnd_no)
{
	int i;

	for(i=0;i<data->wnd_data_num;i++){
		if(data->data[i].wnd_no == wnd_no){
			return (data->data + i);
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�C���f�b�N�X�̃E�B���h�E�f�[�^�擾
 *
 *@param	data	�擾��
 *@param	idx		�C���f�b�N�X
 *
 *@return	�E�B���h�E�f�[�^	�����Ƃ�NULL
 *
 *
 */
//-----------------------------------------------------------------------------
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndIdxDataGet(WIPE_TYPE_HB_WND* data, int idx)
{
	GF_ASSERT(data->wnd_data_num > idx);

	return (data->data + idx);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�����[�v�Ōv�Z�����E�B���h�E�̌`�̃o�b�t�@��
 *			���f�e�[�u���ɑ��
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	work	�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndSwap(TCB_PTR tcb, void* work)
{
	WIPE_TYPE_HB_WND*	swc = (WIPE_TYPE_HB_WND*)work;
	WIPE_TYPE_HB_WND_ONE* one;
	int i;

	for(i=0;i<swc->wnd_data_num;i++){
		one = scchg_h_WndIdxDataGet(swc, i);		// �C���f�b�N�X�̃f�[�^�擾
		memcpy(one->wnd_data, one->wnd_tmp, sizeof(short)*2*192);	// sizeof(short)*2*192
	}
	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E����̌㏈��
 *
 *@param	flag		WIPE_FADE_IN:�t�F�[�h�C��	WIPE_FADE_OUT:�t�F�[�h�A�E�g
 *@param	wnd_sys		�E�B���h�EVblank�������[�N
 *@param	disp		�\����
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndEnd(int flag, WNDP_SYS_PTR wnd_sys, int disp)
{
	if(flag == WIPE_FADE_IN){
		// �t�F�[�h�E�C�����I��������g�p�����E�B���h�E�̕\�����I�t
		WNDP_V_SetVisibleWnd(wnd_sys, GX_WNDMASK_NONE, disp);

	}else{

		// �E�B���h�E0����ʂ����ς��ɍL����
		WNDP_V_SetVisibleWnd(wnd_sys, GX_WNDMASK_W0, disp);
		WNDP_V_SetWndInsidePlane(wnd_sys, GX_BLEND_ALL, FALSE, 0, disp);
		WNDP_V_SetWndPosition(wnd_sys, 0,0,0,0,0, disp);	
		WNDP_V_SetWndOutsidePlane(wnd_sys, GX_BLEND_PLANEMASK_BD, FALSE, disp);	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E���g�p�ł����Ԃɂ���
 *
 *@param	wnd_sys		�E�B���h�EVblank�ݒ�V�X�e���p���[�N
 *@param	in_wnd		�E�B���h�E���ݒ�
 *@param	out_wnd		�E�B���h�E�O�ݒ�
 *@param	wnd_no		�E�B���h�E�i���o�[
 *@param	disp		�E�B���h�E�\����
 *@param	x1			�E�B���h�E���W
 *@param	y1
 *@param	x2
 *@param	y2
 *@param	fade_flg	�t�F�[�h�t���O
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndSetUp(WNDP_SYS_PTR wnd_sys, int in_wnd, int out_wnd, int wnd_no, int disp, int x1, int y1, int x2, int y2, int fade_flg)
{
	// �E�B���h�E�̓��O��ݒ�
	if( fade_flg == WIPE_FADE_IN ){
		// �t�F�[�h�C��
		WNDP_SetWndInsidePlane(in_wnd, FALSE, wnd_no, disp);
		WNDP_SetWndOutsidePlane(out_wnd, FALSE, disp);
		WNDP_SetWndPosition(x1,y1,x2,y2, wnd_no, disp);
	}else{
		// �t�F�[�h�A�E�g
		WNDP_V_SetWndInsidePlane(wnd_sys, in_wnd, FALSE, wnd_no, disp);
		WNDP_V_SetWndOutsidePlane(wnd_sys, out_wnd, FALSE, disp);
		WNDP_V_SetWndPosition(wnd_sys, x1,y1,x2,y2, wnd_no, disp);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�E�B���h�E�\����\���ݒ�
 *
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	plane		�\���E�B���h�E��
 *	@param	disp		�\�����
 *	@param	fade_flg	�t�F�[�h�C���E�A�E�g�t���O
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndVisible(WNDP_SYS_PTR wnd_sys, int plane, int disp, int fade_flg)
{
	if(fade_flg == WIPE_FADE_IN){

		WNDP_SetVisibleWnd( plane, disp );
	}else{

		WNDP_V_SetVisibleWnd(wnd_sys, plane, disp);
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�c�����@H�u�����N�g�p�@�E�B���h�E����
 *
 *	@param	p_wnddata	���[�N
 *	@param	disp		��
 *	@param	data_num	�E�B���h�E�g�p��	(1 or 2)
 *	@param	wnd_no0		���[�N�O�̃E�B���h�E�i���o�[
 *	@param	wnd_no1		���[�N�P�̃E�B���h�E�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWndInit( WIPE_TYPE_WND_VMOVE* p_wnddata, int disp, int data_num, int wnd_no0, int wnd_no1 )
{
	memset( p_wnddata, 0, sizeof(WIPE_TYPE_WND_VMOVE) );

	if( data_num == 1 ){
		p_wnddata->data[0].wnd_no	= wnd_no0;
		p_wnddata->wnd_data_num		= data_num;
		p_wnddata->disp				= disp;
	}else{
		p_wnddata->data[0].wnd_no = wnd_no0;
		p_wnddata->data[1].wnd_no = wnd_no1;
		p_wnddata->wnd_data_num		= data_num;
		p_wnddata->disp				= disp;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X���b�v�o�b�t�@���N�G�X�g
 *
 *	@param	p_wnddata	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_SwapReq( WIPE_TYPE_WND_VMOVE* p_wnddata )
{
	VWaitTCB_Add(scchg_h_VMoveWnd_Swap, p_wnddata, WIPE_VBLANK_WND_SWAP_TCB );
}

//----------------------------------------------------------------------------
/**
 *	@brief	����J�n�@V�u�����N��������J�n���܂��B
 *
 *	@param	p_wnddata ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Start( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap )
{
	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(p_wipehb, p_wnddata, scchg_h_VMoveWnd_Main, p_wnddata->disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	����I��
 *
 *	@param	p_wnddata	V�u�����N��������I�����܂��B
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_End( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap )
{
	WIPE_V_HBlankDelete(p_wipehb, p_wnddata->disp, heap);
}


//----------------------------------------------------------------------------
/**
 *	@brief	�X���b�v�o�b�t�@
 *
 *	@param	tcb			�^�X�N�|�C���^
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Swap( TCB_PTR tcb, void* p_work )
{
	WIPE_TYPE_WND_VMOVE* p_wnddata = p_work;
	int i;
	
	for( i=0; i<2; i++ ){
		memcpy( p_wnddata->data[i].in_out_read, p_wnddata->data[i].in_out_write, sizeof(u8)*192 );
	}

	TCB_Delete( tcb );
}

static inline void wndp_SetWndOutsidePlane_HBlank( int wnd, BOOL effect, int disp )
{
	if(disp == WNDP_DISP_MAIN){
		if( GX_IsHBlank() ){
			G2_SetWndOutsidePlane(wnd, effect);
		}
	}else{
		if( GX_IsHBlank() ){
			G2S_SetWndOutsidePlane(wnd, effect);
		}
	}
}
static inline void wndp_SetWndInsidePlane_HBlank( int wnd, BOOL effect, int wnd_no, int disp )
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd0InsidePlane(wnd, effect);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd0InsidePlane(wnd, effect);
			}
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd1InsidePlane(wnd, effect);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd1InsidePlane(wnd, effect);
			}
		}
	}
}

static inline void set_H_VMoveWndData( WIPE_TYPE_WND_VMOVE* shb, int v_c, int i )
{
	WIPE_TYPE_WND_VMOVE_HDATA* one;

	one = &shb->data[ i ];
	if( one->in_out_read[ v_c ] == WIPE_WND_VMOVE_INWND ){
		wndp_SetWndOutsidePlane_HBlank( GX_BLEND_ALL, TRUE,  shb->disp );
		wndp_SetWndInsidePlane_HBlank( GX_BLEND_PLANEMASK_BD, TRUE, one->wnd_no, shb->disp );
	}else{
		wndp_SetWndOutsidePlane_HBlank( GX_BLEND_PLANEMASK_BD, TRUE,  shb->disp );
		wndp_SetWndInsidePlane_HBlank( GX_BLEND_ALL, TRUE, one->wnd_no, shb->disp );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	H�u�����N�f�[�^�ݒ�
 *
 *	@param	p_work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Main( void* p_work )
{
	WIPE_TYPE_WND_VMOVE* shb = (WIPE_TYPE_WND_VMOVE*)p_work;
	int v_c;
	int i;

	GF_ASSERT(p_work);

	v_c = GX_GetVCount();

	if(v_c < 192){
		
		v_c ++;
		if( v_c > 191 ){
			v_c -= 192;
		}
		
		if( shb->wnd_data_num == 1 ){
			set_H_VMoveWndData( shb, v_c, 0 );
		}else{
			set_H_VMoveWndData( shb, v_c, 0 );
			set_H_VMoveWndData( shb, v_c, 1 );
		}
	}
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�B���h�E����p�b�N�������֐�
 *
 *	@param	wipe	���C�v�f�[�^
 *	@param	param	�E�B���h�E����f�[�^
 *
 * @return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMovePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram )
{
	WIPE_TYPE_WND_MOVE* wwm;

	// �t�F�[�h�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_MOVE));
	
	wwm = (WIPE_TYPE_WND_MOVE*)wipe->wipe_work;
	
	scchg_WndMoveInit(wwm, pram, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
	
	// �E�B���h�E�I��
	if(pram->wnd_no == 0){
		scchg_WndVisible(wipe->wnd_sys, GX_WNDMASK_W0, wwm->disp, wwm->fade_flg);
	}else{
		scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W1, wwm->disp, wwm->fade_flg);
	}
	
	wipe->sequence++;		// ���C�������
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E����p�b�N
 *
 *@param	wipe	���C�v�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMovePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_MOVE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_MOVE*)wipe->wipe_work;
	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_WndMoveMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;

	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Q�̃E�B���h�E�𓯎��ɓ������֐��̏�����
 *
 *@param	wipe		���C�v�\����
 *@param	pram1		�E�B���h�E�O�̈����f�[�^
 *@param	pram2		�E�B���h�E�P�̈����f�[�^
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMoveDoublePackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram1, const WIPE_TYPE_WND_MOVE_FP* pram2)
{
	WIPE_TYPE_WND_DMOVE* wwm;

	// �t�F�[�h�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DMOVE));
	wwm = (WIPE_TYPE_WND_DMOVE*)wipe->wipe_work;
	scchg_WndMoveInit(&wwm->wnd0, pram1, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
	scchg_WndMoveInit(&wwm->wnd1, pram2, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);

	scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W0|GX_WNDMASK_W1, wipe->disp, wwm->wnd0.fade_flg);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�Q�̃E�B���h�E�𓯎��ɓ������֐��̏�����
 *
 *@param	wipe		���C�v�\����
 *	
 *@retval	TRUE		�I��
 *@retval	FALSE		���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMoveDoublePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DMOVE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_DMOVE*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndMoveMain(&wwm->wnd0);
		ret += scchg_WndMoveMain(&wwm->wnd1);
		if(ret == 2){
			scchg_WndEnd(wwm->wnd0.fade_flg, wipe->wnd_sys, wipe->disp);
//			scchg_WndEnd(wwm->wnd1.fade_flg, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�ό`�����̏�����
 *
 *@param	data		�f�[�^�i�[��
 *@param	param		�E�B���h�E�ό`�f�[�^
 *@param	division	����������
 *@param	piece_sync	�P�Ђ̃V���N��
 *@param	disp		�\����
 *@param	wnd_sys		�E�B���h�E�V�X�e���|�C���^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMoveInit(WIPE_TYPE_WND_MOVE* data, const WIPE_TYPE_WND_MOVE_FP* pram, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys)
{
	// ���W��ݒ�
	sum_set_wnd_position(&data->st, &data->ed, &data->add, &pram->st, &pram->ed, division);

	// �f�[�^�ݒ�
	data->disp			= disp;
	data->wnd_no		= pram->wnd_no;
	data->a_count		= division;
	data->piece_sync	= piece_sync;
	data->sync_c		= 0;
	data->wnd_sys		= wnd_sys;
	data->fade_flg		= pram->fade_flg;

	// �E�B���h�E�̓��O��ݒ�
	scchg_WndSetUp(wnd_sys, pram->in_wnd, pram->out_wnd, pram->wnd_no, disp,
			pram->st.x1,pram->st.y1,
			pram->st.x2,pram->st.y2,
			data->fade_flg);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�̌`��ό`������
 *
 *@param	data	�E�B���h�E�ό`�f�[�^
 *
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMoveMain(WIPE_TYPE_WND_MOVE* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;
	
			// �����Z
			sum_add_wnd(&data->st, &data->add);
		}else{
			WNDP_V_SetWndPosition(data->wnd_sys, data->ed.x1,data->ed.y1,data->ed.x2,data->ed.y2, data->wnd_no, data->disp);

			return TRUE;
		}

		WNDP_V_SetWndPosition(data->wnd_sys, data->st.x1/SUM_NUM_MINI,data->st.y1/SUM_NUM_MINI,data->st.x2/SUM_NUM_MINI,data->st.y2/SUM_NUM_MINI, data->wnd_no, data->disp);//*/
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�E�B���h�E�ŉ~��`���V�X�e��
 *
 *	@param	wipe	���C�v���[�N
 *	@param	param	�������f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCirclePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CIRCLE_FP* param )
{
	WIPE_TYPE_WND_CIRCLE* wwm;
	
	// ���C�v�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_CIRCLE));
	wwm = (WIPE_TYPE_WND_CIRCLE*)wipe->wipe_work;
	scchg_WndCircleInit(wwm, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);

	// ���C�������
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�ŉ~��`���V�X�e��
 *
 *@param	wipe		���C�v���[�N
 *
 *@return	BOOL		TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCirclePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_CIRCLE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_CIRCLE*)wipe->wipe_work;
	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_WndCircleMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_circle);	// �E�B���h�E�ݒ�f�[�^�j��
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
		
	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�~�`��V�X�e����������
 *
 *@param	data			�f�[�^�i�[��
 *@param	param			���C�v�f�[�^
 *@param	division		����������
 *@param	piece_sync		�P�Ђ̃V���N��
 *@param	disp			�\����
 *@param	wnd_sys			�E�B���h�E�V�X�e���|�C���^
 *@param	heap			�g�p����q�[�vID
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleInit(WIPE_TYPE_WND_CIRCLE* data, const WIPE_TYPE_WND_CIRCLE_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap)
{
	int add_r;
	WIPE_TYPE_HB_WND_ONE* one;

	// �ω��l�����߂�
	add_r = sum_add_num(param->r, param->e_r, division);

	// �f�[�^��ݒ�
	scchg_h_WndMake(&data->hb_circle, param->wnd_no, disp, heap);
	data->r					= param->r*SUM_NUM_MINI;
	data->x					= param->x;
	data->y					= param->y;
	data->add_r				= add_r;
	data->a_count			= division;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndCircleSum(data);	// 1��v�Z����
	VWaitTCB_Add(scchg_WndSwap,&data->hb_circle, WIPE_VBLANK_WND_SWAP_TCB );

	// �E�B���h�E�ݒ�
	one = scchg_h_WndIdxDataGet(&data->hb_circle, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, param->wnd_no, disp,
			one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);

	// �E�B���h�E�I��
	if(param->wnd_no == 0){
		scchg_WndVisible( wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg );
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}
	
	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_circle, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�~�`�惁�C������
 *
 *@param	data	�E�B���h�E�ό`�f�[�^
 *
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCircleMain(WIPE_TYPE_WND_CIRCLE* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->r += data->add_r;	
			scchg_WndCircleSum(data);
			VWaitTCB_Add(scchg_WndSwap,&data->hb_circle, WIPE_VBLANK_WND_SWAP_TCB );
		}else{

			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_circle.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�~�f�[�^�v�Z�T�u�֐�
 *
 *@param	c_r		���a�iSUM_NUM_MINI�ł������l�j
 *@param	c_x		���S���W
 *@param	c_y		���S���W
 *@param	n_h		���̍���
 *@param	st		�E�B���h�E���̊J�n�_
 *@param	ed		�E�B���h�E���̏I���_
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleSumSub(int c_r, int c_x, int c_y, int n_h, int* st, int* ed)
{
	fx32 r;			// ���a
	fx32 height;	// ����
	fx32 width;		// ��

	// �R�����̒藝�ō��̍�������~�̕������߂�
	
	r = c_r / SUM_NUM_MINI;

	height = n_h - c_y;
	if(height < 0){
		height = -height;
	}
	
	if(height >= r){
		*st = 0;
		*ed = 0;
	}else{
		// ���a���畝�����߂�
		height <<= FX32_SHIFT;
		r <<= FX32_SHIFT;
		width = FX_Sqrt(FX_Mul(r,r) - FX_Mul(height,height));
		width >>= FX32_SHIFT;

		// �E�B���h�E�̊J�n�_��ݒ�
		*st = c_x - width;
		if(*st < 0){
			*st = 0;
		}
		*ed = *st + (width*2);
		if(*ed > 255){
			*ed = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�~�f�[�^�̌v�Z���s��
 *
 *@param	work		�~�`��V�X�e���̃f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleSum(WIPE_TYPE_WND_CIRCLE* work)
{
	WIPE_TYPE_HB_WND* shb = &work->hb_circle;
	int i;			// ���[�v�p
	int st;			// �E�B���h�E�J�n�_
	int ed;			// �E�B���h�E�I���_
	int roop_end;
	WIPE_TYPE_HB_WND_ONE* one;

	// �C���f�b�N�X�O�̃E�B���h�E�f�[�^���擾
	one = scchg_h_WndIdxDataGet(shb, 0);

	// ���a����ʓ��ɂ���Ƃ���
	// ���S�܂ŕ������߂��牺�����̓R�s�[����悤�ɂ���
	for(i=0;i < 192;i++){
		if(i <= work->y){		// ���a�܂ł͕��ʂ̋��߂�
			scchg_WndCircleSumSub(work->r, work->x, work->y, i, &st, &ed);
		}else{
			if(i <= (work->y*2)){		// ���a���甼�a�̂Q�{�܂ł�,�R�s�[
				st = one->wnd_tmp[0][(work->y*2)-i];
				ed = one->wnd_tmp[1][(work->y*2)-i];
			}else{				// ���̑��͕��ʂɋ��߂�
				scchg_WndCircleSumSub(work->r, work->x, work->y, i, &st, &ed);
			}
		}
		
		one->wnd_tmp[0][i] = st;
		one->wnd_tmp[1][i] = ed;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E���J�[�e���̂悤�ɕ\�����鏉�����֐�
 *
 *@param	wipe		���C�v���[�N
 *@param	param		�֐�����
 *
 *	rota		�J�n�p�x		�p�x�͂O�`�W�X�ł��肢���܂�
 *	e_rota		�I���p�x		�܂����W�A���l�ł���K�v������܂��B
 *	wnd_no		�E�B���h�E�i���o�[
 *	in_wnd		�E�B���h�E���̖�
 *	out_wnd		�E�B���h�E�O�̖�
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainPackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CURTAIN_FP* param)
{
	WIPE_TYPE_WND_CURTAIN* wwm;

	// �t�F�[�h�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_CURTAIN));
	wwm = (WIPE_TYPE_WND_CURTAIN*)wipe->wipe_work;
	scchg_WndCurtainInit(wwm, param,wipe->division, wipe->piece_sync,  wipe->disp,  wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E���J�[�e���̂悤�ɕ\������
 *
 *@param	wipe		���C�v���[�N
 *
 *@return	BOOL	TRUE�F�I��	FALSE�F���s
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCurtainPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_CURTAIN* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_CURTAIN*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndCurtainMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_c);
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�ł̃J�[�e���`��J�n
 *
 *@param	data		�J�[�e���`��f�[�^
 *@param	param		�J�[�e������f�[�^
 *@param	division	�����̕�����
 *@param	piece_sync	�P�Ђ̃V���N��
 *@param	disp		�E�B���h�E�\����
 *@param	wnd_sys		�E�B���h�EVblank�����V�X�e���̃��[�N
 *@param	p_wipehb	���C�vH�u�����N���[�N
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainInit(WIPE_TYPE_WND_CURTAIN* data, const WIPE_TYPE_WND_CURTAIN_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one;
	
	data->rota_add = sum_add_num(param->rota, param->e_rota, division);

	// �f�[�^�ݒ�
	scchg_h_WndMake(&data->hb_c, param->wnd_no, disp, heap);
	data->rota		= param->rota*SUM_NUM_MINI;
	data->a_count	= division;
	data->piece_sync = piece_sync;
	data->sync_c	= 0;
	data->wnd_sys	= wnd_sys;	
	data->p_wipehb	= p_wipehb;
	data->heap		= heap;
	data->fade_flg	= param->fade_flg;
	
	scchg_WndCurtainSum(data);	// 1��v�Z����
	VWaitTCB_Add(scchg_WndSwap,&data->hb_c, WIPE_VBLANK_WND_SWAP_TCB );

	// �E�B���h�E�\���ݒ�
	// �E�B���h�E�ݒ�
	one = scchg_h_WndIdxDataGet(&data->hb_c, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd,
			param->wnd_no, disp, one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);

	// �E�B���h�E�I��
	if(param->wnd_no == 0){
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}
	

	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_c, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�J�[�e���\���̃��C������
 *
 *@param	data	�E�B���h�E����f�[�^
 *	
 *@return	BOOL	TRUE�F�I��	FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCurtainMain(WIPE_TYPE_WND_CURTAIN* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->rota += data->rota_add;
			scchg_WndCurtainSum(data);		// �v�Z
			VWaitTCB_Add(scchg_WndSwap,&data->hb_c, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// �����I��
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_c.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E���J�[�e���̂悤�ɕ\������f�[�^���v�Z
 *
 *@param	work		�E�B���h�E����f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainSum(WIPE_TYPE_WND_CURTAIN* work)
{
	int i;
	int st, ed;
	int width[192];
	WIPE_TYPE_HB_WND_ONE* one;

	// �C���f�b�N�X�O�̃E�B���h�E�f�[�^���擾
	one = scchg_h_WndIdxDataGet(&work->hb_c, 0);

	// �p�x����e�����ł̕������߂�
	sum_rota_height_width(work->rota/SUM_NUM_MINI, width, 192, 0);

	// �eY���W�ł̕���������
	for(i=0;i<192;i++){
		one->wnd_tmp[0][i] = sum_add_wnd_width(128, -width[i]);
		one->wnd_tmp[1][i] = sum_add_wnd_width(128, width[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�t�F�[�h�p�b�N�֐�	�������֐�
 *
 *@param	wipe		���C�v���[�N
 *@param	param		�h�A�f�[�^
 *	s_d			�J�n�J���p�x	�iROTA_NUM(0)�`ROTA_NUM(90)�j
 *	e_d			�I���J���p�x	�iROTA_NUM(0)�`ROTA_NUM(90)�j
 *	wnd_no		�g�p�E�B���h�E�i���o�[
 *	in_wnd		�E�B���h�E���ʐݒ�
 *	out_wnd		�E�B���h�E�O�ʐݒ�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DOOR_FP* param)
{
	WIPE_TYPE_WND_DOOR* wwm;
	// �t�F�[�h�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DOOR));
	wwm = (WIPE_TYPE_WND_DOOR*)wipe->wipe_work;
	scchg_WndDoorInit(wwm, param, wipe->division, wipe->piece_sync,  wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�t�F�[�h�p�b�N�֐�
 *
 *@param	wipe		���C�v���[�N
 *
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDoorPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DOOR* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_DOOR*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndDoorMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_d);
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�Ńh�A�t�F�[�h������
 *
 *@param	data		�f�[�^�i�[��
 *@param	param		�h�A����f�[�^
 *@param	division	����������
 *@param	piece_sync	�P�Ђ̃V���N��
 *@param	disp		�E�B���h�E�\����
 *@param	wnd_no		�g�p�E�B���h�E�i���o�[
 *@param	wnd_sys		�E�B���h�EVblank�ݒ胏�[�N
 *@param	wipe_hb		���C�vH�u�����N���[�N
 *@param	heap		�g�p����q�[�v
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorInit(WIPE_TYPE_WND_DOOR* data, const WIPE_TYPE_WND_DOOR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int add_num;
	WIPE_TYPE_HB_WND_ONE* one;

	// �P��ŊJ���h�A�̋������v�Z
	add_num	= (param->e_d - param->s_d);
	add_num	/= division;

	// �f�[�^�ݒ�
	scchg_h_WndMake(&data->hb_d, param->wnd_no, disp, heap);
	data->open_max		= 128*FX32_ONE;	// �����̔����̒l�ōl����
	data->open_r		= param->s_d;
	data->open_r_a		= add_num;
	data->a_count	= division;
	data->piece_sync= piece_sync;
	data->sync_c	= 0;
	data->wnd_sys	= wnd_sys;
	data->p_wipehb	= p_wipehb;
	data->heap		= heap;
	data->fade_flg	= param->fade_flg;

	// �h�A�v�Z
	scchg_WndDoorSum(data);
	VWaitTCB_Add(scchg_WndSwap,&data->hb_d, WIPE_VBLANK_WND_SWAP_TCB );
	
	// �E�B���h�E�ݒ�
	one = scchg_h_WndIdxDataGet(&data->hb_d, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 
			param->wnd_no, disp,
			one->wnd_tmp[0][96], 0, one->wnd_tmp[1][96], 192,
			data->fade_flg);	// �X�U����ɂ���ׂ�

	// �E�B���h�E�I��
	if(param->wnd_no == 0){
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}

	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_d, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�t�F�[�h���C��
 *
 *@param	data		�h�A�f�[�^
 *
 *@return	BOOL		TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDoorMain(WIPE_TYPE_WND_DOOR* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->open_r += data->open_r_a;
			scchg_WndDoorSum(data);		// �v�Z
			VWaitTCB_Add(scchg_WndSwap, &data->hb_d, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// �����I��
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_d.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�h�A�^�̃E�B���h�E�v�Z
 *
 *@param	work		�h�A�f�[�^
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorSum(WIPE_TYPE_WND_DOOR* work)
{
	int i;
	int tri_h;		// ���s���\���̂Q���ӎO�p�`�̍���
	int rota;		// ���s���\���̂Q���ӎO�p�`�̒��_�̊p�x
	int tri_data[192];	// ���s���\���̂Q���ӎO�p�`�̌`�f�[�^
	int tri_n;		// tri_data�e�[�u���̗v�f��
	int h_open;		// ���̊J���Ă���l�̔���
	int set_w;		// �E�B���h�E�ɐݒ肷�镝
	int st, ed;		// �J�n�_�A�I���_
	WIPE_TYPE_HB_WND_ONE* one;	// �E�B���h�E�ݒ�f�[�^

	// �C���f�b�N�X�O�̃E�B���h�E���擾
	one = scchg_h_WndIdxDataGet(&work->hb_d, 0);

	// ���̊J���l�����߂�
	h_open = FX_Mul(FX_SinIdx(work->open_r), work->open_max);
	h_open >>= FX32_SHIFT;
	
	rota = h_open*2;						// ���̊J���l�����߂�
	rota = rota / WIPE_DOOR_ROTA_NUM;		// �Q���ӎO�p�`�̍ēx�̊p�x�����߂�
	rota += 1;								// 90�x���
	rota = 180 - (rota*2);					// �O�p�`�̒��_�̊p�x�����߂�
	rota = ROTA_NUM(rota);					// FX�̌v�Z�Ŏg�p����p�x�̒P�ʂɂ���
	rota /= 2;								// �������߂邽�ߔ����̊p�x�ɂ���
	tri_h = sum_triangle_height(rota, 256);	// �O�p�`�̍������擾
	tri_h >>= FX32_SHIFT;					// fx32����int��
	GF_ASSERT(tri_h < 192);

	sum_rota_height_width(rota, tri_data, tri_h, 0);	// �O�p�`�̌`�f�[�^�����߂�
	
	// �h�A�^�̃E�B���h�E�f�[�^���쐬
	for(i=0;i<96;i++){

		// �E�B���h�E�ɐݒ肷�镝�����߂�
		tri_n = tri_h - (i+1);
		set_w = h_open;
		if(tri_n > 0){
			if(tri_data[tri_n] > set_w){
				set_w = tri_data[tri_n];
			}
		}

		// �J�n�_�I���_�����߂�
		st = sum_add_wnd_width(128, -set_w);
		ed = sum_add_wnd_width(128, set_w);

		// �E�B���h�E�ɐݒ肷��
		one->wnd_tmp[0][i] = st;
		one->wnd_tmp[1][i] = ed;
		one->wnd_tmp[0][191 - i] = st;
		one->wnd_tmp[1][191 - i] = ed;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�P�E�B���h�E���������t�F�[�h�p�b�N
 *
 *	@param	wipe		���C�v���[�N
 *	@param	param		�����t�F�[�h�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DIVI_FP* param)
{
	WIPE_TYPE_WND_DIVI* wwm;
	// �t�F�[�h�J�n
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DIVI));
	wwm = (WIPE_TYPE_WND_DIVI*)wipe->wipe_work;
	scchg_WndDivisionInit(wwm, param, wipe->division, wipe->piece_sync,  wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�E�B���h�E���������t�F�[�h�p�b�N
 *
 *@param	wipe		���C�v���[�N
 *	
 *@return	BOOL	TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDivisionPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DIVI* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_DIVI*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndDivisionMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndDivisionEnd(wwm);	// �����E�B���h�E�f�[�^�j��
		scchg_h_WndDel(&wwm->hb_divi);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�P�E�B���h�E�����t�F�[�h������
 *
 *@param	data		�f�[�^�i�[��
 *@param	param		�P�E�B���h�E�����f�[�^
 *@param	division	����������
 *@param	piece_sync	���������P�Ђ̃V���N��
 *@param	disp		�E�B���h�E�\����
 *@param	wnd_sys		�E�B���h�EVblank�ݒ�V�X�e�����[�N
 *@param	p_wipehb	���C�v�pH�u�����N���[�N
 *@param	heap		�g�p����q�[�v
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionInit(WIPE_TYPE_WND_DIVI* data, const WIPE_TYPE_WND_DIVI_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int i;
	WIPE_TYPE_HB_WND_ONE* one;
	
	// �����f�[�^�쐬
	// �������A���b�N
	data->piece_tbl = sys_AllocMemory(heap, sizeof(WIPE_TYPE_WND_D_PIECE)*param->divi_num);
	GF_ASSERT(data->piece_tbl != NULL);
	data->piece_num = param->divi_num;

	// �f�[�^�i�[
	for(i=0;i<param->divi_num;i++){

		sum_set_wnd_position(&data->piece_tbl[i].st, &data->piece_tbl[i].ed, &data->piece_tbl[i].add, (param->p_st+i), (param->p_ed+i), division);
	}

	// �f�[�^�ݒ�
	scchg_h_WndMake(&data->hb_divi, param->wnd_no, disp, heap);
	data->a_count		= division;
	data->piece_sync	= piece_sync;
	data->sync_c		= 0;
	data->wnd_sys		= wnd_sys;
	data->p_wipehb		= p_wipehb;
	data->heap			= heap;
	data->fade_flg		= param->fade_flg;

	// �����v�Z
	scchg_WndDivisionSum(data);
	VWaitTCB_Add(scchg_WndSwap,&data->hb_divi, WIPE_VBLANK_WND_SWAP_TCB );
	
	// �E�B���h�E�ݒ�
	one = scchg_h_WndIdxDataGet(&data->hb_divi, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, param->wnd_no, disp,
			one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);	// �X�U����ɂ���ׂ�

	// �E�B���h�E�I��
	if(param->wnd_no == 0){
		scchg_WndVisible(data->wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(data->wnd_sys,GX_WNDMASK_W1, disp, data->fade_flg);
	}

	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_divi, scchg_h_Wnd, disp, heap);
}
	

//----------------------------------------------------------------------------
/**
 *
 *@brief	1�E�B���h�E�𕪊����Ă��ꂼ��œ�����
 *
 *@param	data		���������E�B���h�E�f�[�^
 *
 *@return	BOOL		TRUE�F�I��		FALSE�F���s
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDivisionMain(WIPE_TYPE_WND_DIVI* data)
{
	
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count - 1) > 0){
			data->a_count--;

			// ������
			scchg_WndDivisionMainSub(data);			
			
			scchg_WndDivisionSum(data);		// �v�Z
			VWaitTCB_Add(scchg_WndSwap,&data->hb_divi, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// �����I��
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_divi.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�X�̕����f�[�^��j������
 *
 *@param	data	�E�B���h�E�����f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionEnd(WIPE_TYPE_WND_DIVI* data)
{
	// �m�ۂ��������������
	sys_FreeMemoryEz( data->piece_tbl);
	data->piece_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�X�̃f�[�^���E�B���h�E�̐ݒ�f�[�^�ɕϊ�
 *
 *@param	work		�P�E�B���h�E�����f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionSum(WIPE_TYPE_WND_DIVI* work)
{
	int i;		// ���[�v�p
	WIPE_TYPE_HB_WND_ONE* one;
	
	one = scchg_h_WndIdxDataGet(&work->hb_divi, 0);
	memset(one->wnd_tmp, 0, 768);	// �N���A

	// �v�f�O����ԗD�揇�ʂ������Ȃ�悤�ɍŌ�̗v�f����f�[�^��ݒ肵�Ă���
	for(i = (work->piece_num-1); i >= 0; i--){
		scchg_WndDivisionSumSub(&work->hb_divi, &work->piece_tbl[i].st);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�E�B���h�E�����f�[�^�v�Z�T�u�֐�
 *
 *@param	hb_divi		H�u�����N�ݒ�f�[�^
 *@param	set			�ݒ�f�[�^
 *
 *@return	none
 *
 * �ݒ肷��
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionSumSub(WIPE_TYPE_HB_WND* hb_divi, WIPE_WND_POSITION* set)
{
	int i;		// ���[�v�p
	WIPE_TYPE_HB_WND_ONE* one;
	WIPE_WND_POSITION set_data;
	
	one = scchg_h_WndIdxDataGet(hb_divi, 0);

	set_data.x1 = set->x1 / SUM_NUM_MINI;
	set_data.y1 = set->y1 / SUM_NUM_MINI;
	set_data.x2 = set->x2 / SUM_NUM_MINI;
	set_data.y2 = set->y2 / SUM_NUM_MINI;

	for( i = set_data.y1; i < set_data.y2; i++ ){
		one->wnd_tmp[0][i] = set_data.x1;
		one->wnd_tmp[1][i] = set_data.x2;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C���֐��̓����֐�
 *
 *@param	data		�f�[�^
 *
 *@return	none
 *
 * ���ۂɕ������ꂽ���ꂼ��̃E�B���h�E�𓮂���
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionMainSub(WIPE_TYPE_WND_DIVI* data)
{
	int i;		// ���[�v�p

	// ���ꂼ�ꓮ����
	for(i=0;i<data->piece_num;i++){
		sum_add_wnd(&data->piece_tbl[i].st, &data->piece_tbl[i].add);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[�֐�������
 *
 *	@param	wipe		���C�v
 *	@param	param		�p�����[�^
 *	@param	flag		�t�F�[�h�C���A�E�g�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_SCREW_FP* param)
{
	WIPE_TYPE_WND_SCREW* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_SCREW) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_SCREW) );
	data = wipe->wipe_work;
	scchg_WndScrewInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[���C�v���C������
 *
 *	@param	wipe		���C�v
 *	
 *	@retval	TRUE		�I��
 *	@retval	FALSE		���s
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndScrewPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_SCREW* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_SCREW*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndScrewMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndScrewEnd(wwm);	// �E�B���h�E�f�[�^�j��
		scchg_h_WndDel(&wwm->hb);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[�������֐�
 *
 *	@param	data		���[�N
 *	@param	param		�p�����[�^
 *	@param	division	������
 *	@param	piece_sync	�V���N��
 *	@param	disp		���
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	p_wipehb	H�u�����N�֐��V�X�e��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewInit(WIPE_TYPE_WND_SCREW* data, WIPE_TYPE_WND_SCREW_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;

	// �ω��l�����߂�
	data->screw.rota		= 0;
	data->screw.s_rota		= param->s_rota;
	data->screw.add_num_rota = param->e_rota - param->s_rota;

	// �f�[�^��ݒ�
	scchg_h_WndMake(&data->hb, 2, disp, heap);
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndScrewOneAdd(&data->screw, data->a_count, data->a_count_max);
	scchg_WndScrewSum(data);	// 1��v�Z����
	VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );

	// �E�B���h�E�ݒ�
	one0 = scchg_h_WndIdxDataGet(&data->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&data->hb, 1);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 0, disp,
			one0->wnd_tmp[0][0], 0, one0->wnd_tmp[1][0], 192,
			data->fade_flg);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 1, disp,
			one1->wnd_tmp[0][0], 0, one1->wnd_tmp[1][0], 192,
			data->fade_flg);

	// �E�B���h�E�I��
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0|GX_WNDMASK_W1, disp, data->fade_flg );

	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[���C���֐�
 *
 *	@param	data	���[�N
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		���s
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndScrewMain(WIPE_TYPE_WND_SCREW* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// ������
			scchg_WndScrewOneAdd(&data->screw, data->a_count, data->a_count_max);
			scchg_WndScrewSum(data);		// �v�Z
			VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// �����I��
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb.disp, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[���[�N�j���֐�
 *
 *	@param	data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewEnd(WIPE_TYPE_WND_SCREW* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N�����[�f�[�^�v�Z�֐�
 *
 *	@param	work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewSum(WIPE_TYPE_WND_SCREW* work)
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	u16 rota_num;
	int x1, x2;
	int i;


	// �E�B���h�E0����	�E�B���h�E1 �E���Ōv�Z���܂�
	// �E�B���h�E�e�[�u���ɒl��ݒ�
	// �E�B���h�E0�� �I�_128  �n�_128-(y*tan(rota))
	// �E�B���h�E1�� �n�_128  �I�_128+(y*tan(rota))
	// �p�x90�ȏ�ɂȂ�����
	// �E�B���h�E0�� �I�_128-(y*tan(rota))  �n�_0
	// �E�B���h�E1�� �n�_128+(y*tan(rota))  �I�_255
	
	rota_num = work->screw.rota % FX_GET_ROTA_NUM( 90 );
	
	one0 = scchg_h_WndIdxDataGet(&work->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&work->hb, 1);
	// �l���₷���̂ŁA�E�B���h�E1�̕��Ōv�Z����
	// �v�Z���ʂ��T�u��XY���]���Đݒ肷��
	for( i=0; i<96; i++ ){
		if( work->screw.rota < FX_GET_ROTA_NUM( 90 ) ){
			x1 = 128;

			// ��]�p�ƍ�����������R�p�`�̕������߂�
			x2 = sub_rota_height_width_one( rota_num, (96 - i) );

			if( x2 > 127 ){
				x2 = 127;
			}
			
			one0->wnd_tmp[0][191 - i] = x1 - x2;
			one0->wnd_tmp[1][191 - i] = x1;

			one1->wnd_tmp[0][i] = x1;
			one1->wnd_tmp[1][i] = x1 + x2;
		}else{
			one0->wnd_tmp[0][191 - i] = 0;
			one0->wnd_tmp[1][191 - i] = 128;

			one1->wnd_tmp[0][i] = 128;
			one1->wnd_tmp[1][i] = 255;
		}
	}

	for( i=96; i<192; i++ ){
		if( work->screw.rota < FX_GET_ROTA_NUM( 90 ) ){
			one0->wnd_tmp[0][191 - i] = 128;
			one0->wnd_tmp[1][191 - i] = 128;

			one1->wnd_tmp[0][i] = 128;
			one1->wnd_tmp[1][i] = 128;
		}else{
			// ��]�p�ƍ�����������R�p�`�̕������߂�
			x1 = sub_rota_height_width_one( FX_GET_ROTA_NUM( 90 ) - rota_num, (i - 96) );

			if( x1 > 127 ){
				x1 = 127;
			}
			
			one0->wnd_tmp[0][191 - i] = 0;
			one0->wnd_tmp[1][191 - i] = 128 - x1;
			
			one1->wnd_tmp[0][i] = 128 + x1;
			one1->wnd_tmp[1][i] = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�P�f�[�^�̌v�Z
 *
 *	@param	p_data		���[�N
 *	@param	count		���ݶ���
 *	@param	count_max	�����ő吔
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewOneAdd( WIPE_TYPE_WND_SCREW_ONE* p_data, int count, int count_max )
{
	int rota_w;
	
	rota_w = p_data->add_num_rota * count;
	rota_w = rota_w / count_max;
	p_data->rota = rota_w + p_data->s_rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V�����C�v�@�S����
 *
 *	@param	wipe		���C�v���[�N
 *	@param	param		�p�����[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_FLASH_FOUR_FP* param)
{
	WIPE_TYPE_WND_FLASH_FOUR* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_FLASH_FOUR) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_FLASH_FOUR) );
	data = wipe->wipe_work;
	scchg_WndFlashFourInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V���@�S����
 *
 *	@param	wipe	���C�v���[�N
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		���s
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndFlashFourPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_FLASH_FOUR* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_FLASH_FOUR*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndFlashFourMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndFlashFourEnd(wwm);	// �E�B���h�E�f�[�^�j��
		scchg_h_WndDel(&wwm->hb);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V���@�S�����@����������
 *
 *	@param	data		���[�N
 *	@param	param		�p�����[�^
 *	@param	division	������
 *	@param	piece_sync	�V���N��
 *	@param	disp		���
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	p_wipehb	H�u�����N�֐��V�X�e��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourInit(WIPE_TYPE_WND_FLASH_FOUR* data, WIPE_TYPE_WND_FLASH_FOUR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	
	// �ω��l�����߂�
	data->screw.rota		= param->s_rota;
	data->screw.s_rota		= param->s_rota;
	data->screw.add_num_rota = param->e_rota - param->s_rota;

	// �f�[�^��ݒ�
	scchg_h_WndMake(&data->hb, 2, disp, heap);
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndFlashFourSum(data);	// 1��v�Z����
	VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );

	// �E�B���h�E�ݒ�
	one0 = scchg_h_WndIdxDataGet(&data->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&data->hb, 1);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 0, disp,
			0, 0, 255, 192,
			data->fade_flg);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 1, disp,
			0, 0, 255, 192,
			data->fade_flg);

	// �E�B���h�E�I��
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0|GX_WNDMASK_W1, disp, data->fade_flg );

	// Hblank�֐���ݒ�
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V���@�S�������C���֐�
 *
 *	@param	data	���[�N
 *
 *	@retval	TRUE		�I��
 *	@retval	FALSE		���s
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndFlashFourMain(WIPE_TYPE_WND_FLASH_FOUR* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// ������
			scchg_WndFlashFourOneAdd(&data->screw, data->a_count, data->a_count_max);
			scchg_WndFlashFourSum(data);		// �v�Z
			VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// �����I��
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb.disp, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V���S�����j���֐�
 *
 *	@param	data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourEnd(WIPE_TYPE_WND_FLASH_FOUR* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t���b�V���S�����֐�	�v�Z
 *
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourSum(WIPE_TYPE_WND_FLASH_FOUR* work)
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	u16 rota_num;
	int x1, x2;
	int i;

	rota_num = work->screw.rota;
	
	one0 = scchg_h_WndIdxDataGet(&work->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&work->hb, 1);

	// �E��̕�������ɂS�̃u���b�N�̒l��ݒ肵�Ă���
	// �O�`�S�T�ނŊ��S�ɕ���
	for( i=0; i<96; i++ ){
		// ��]�p�ƍ�����������R�p�`�̕������߂�
		x1 = sub_rota_height_width_one( rota_num, (96 - i) );
		x2 = sub_rota_height_width_one( FX_GET_ROTA_NUM(90) - rota_num, (96 - i) );
		if( x1 > 127 ){
			x1 = 127;
		}
		if( x2 > 127 ){
			x2 = 127;
		}

		// ����
		one0->wnd_tmp[0][i] = 128 - x2;
		one0->wnd_tmp[1][i] = 128 - x1;
		
		// ����
		one0->wnd_tmp[0][191 - i] = 128 - x2;
		one0->wnd_tmp[1][191 - i] = 128 - x1;
		
		// �E��
		one1->wnd_tmp[0][i] = 128 + x1;
		one1->wnd_tmp[1][i] = 128 + x2;
		
		// �E��
		one1->wnd_tmp[0][191 - i] = 128 + x1;
		one1->wnd_tmp[1][191 - i] = 128 + x2;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�x�v�Z����
 *
 *	@param	p_data		���[�N
 *	@param	count		���ݶ���
 *	@param	count_max	�����ő吔
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourOneAdd( WIPE_TYPE_WND_FLASH_FOUR_ONE* p_data, int count, int count_max )
{
	int rota_w;
	
	rota_w = p_data->add_num_rota * count;
	rota_w = rota_w / count_max;
	
	p_data->rota = rota_w + p_data->s_rota;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�EH�u�����N�g�p�@�c����@������
 *
 *	@param	wipe		���C�v���[�N
 *	@param	param		�p�����[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMovePackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_VMOVE_PARAM* param)
{
	WIPE_TYPE_WND_VMOVE_CONT* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_VMOVE_CONT) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_VMOVE_CONT) );
	data = wipe->wipe_work;
	scchg_WndWndVMoveInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�EH�u�����N�g�p�@�c����	����
 *
 *	@param	wipe		���C�v���[�N
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndVMovePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_VMOVE_CONT* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_VMOVE_CONT*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndWndVMoveMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndWndVMoveEnd(wwm);	// �E�B���h�E�f�[�^�j��
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�EH�u�����N�g�p�@�c����	������
 *
 *	@param	data		���[�N
 *	@param	param		�p�����[�^
 *	@param	division	������
 *	@param	piece_sync	�V���N��
 *	@param	disp		���
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	p_wipehb	H�u�����N�֐��V�X�e��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveInit(WIPE_TYPE_WND_VMOVE_CONT* data, WIPE_TYPE_WND_VMOVE_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	// H�u�����N���[�N������
	scchg_h_VMoveWndInit( &data->HblankData, disp, 1, WNDP_WND_0, 0 );
	// �������[�N�l��ݒ�
	if( param->fade_flg == WIPE_FADE_IN ){
		memset( data->HblankData.data[0].in_out_write, WIPE_WND_VMOVE_OUTWND, sizeof( u8 ) * 192 );
		memset( data->HblankData.data[0].in_out_read, WIPE_WND_VMOVE_OUTWND, sizeof( u8 ) * 192 );
	}else{
		memset( data->HblankData.data[0].in_out_write, WIPE_WND_VMOVE_INWND, sizeof( u8 ) * 192 );
		memset( data->HblankData.data[0].in_out_read, WIPE_WND_VMOVE_INWND, sizeof( u8 ) * 192 );
	}


	// �f�[�^�e�[�u���ݒ�
	data->p_param = param->cp_data;
	data->param_num = param->data_num;
	data->fade_flg = param->fade_flg;
	data->heap	= heap;

	// �ω����ƃV���N���ݒ�
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb		= p_wipehb;

	// H�u�����N�֐��ݒ�
	scchg_h_VMoveWnd_Start( p_wipehb, &data->HblankData, heap );


	// �E�B���h�E�ݒ�
	if( param->fade_flg == WIPE_FADE_OUT ){
		scchg_WndSetUp(wnd_sys, GX_BLEND_PLANEMASK_BD, GX_BLEND_ALL, WNDP_WND_0, disp, 0, 0, 0, 0, param->fade_flg);
	}else{
		scchg_WndSetUp(wnd_sys, GX_BLEND_ALL, GX_BLEND_PLANEMASK_BD, WNDP_WND_0, disp, 0, 0, 0, 0, param->fade_flg);
	}

	// �E�B���h�E�I��
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg );

}

//----------------------------------------------------------------------------
/**
 *	@brief	���C������
 *
 *	@param	data	���[�N
 *
 *	@retval	 TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndVMoveMain(WIPE_TYPE_WND_VMOVE_CONT* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// ������
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// ������
			scchg_WndWndVMoveSum(data);		// �v�Z
			scchg_h_VMoveWnd_SwapReq( &data->HblankData );
		}else{
			// �����I��
			scchg_h_VMoveWnd_End(data->p_wipehb, &data->HblankData, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�j���֐�
 *	
 *	@param	data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveEnd(WIPE_TYPE_WND_VMOVE_CONT* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�N�Ƀf�[�^�ݒ�֐�
 *
 *	@param	work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveSum(WIPE_TYPE_WND_VMOVE_CONT* work)
{
	int i;
	WIPE_TYPE_WND_VMOVE_HDATA* p_buff;
	const WIPE_TYPE_WND_VMOVE_DATA* cp_one;

	// �������ݐ�o�b�t�@
	p_buff = &work->HblankData.data[0];

	for( i=0; i<work->param_num; i++ ){
		cp_one = &work->p_param[i];
		scchg_WndWndVMoveSub_Core( cp_one, p_buff, work->a_count, work->a_count_max );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�v�ZCore
 *
 *	@param	p_one		�P�̓���f�[�^
 *	@param	p_buff		�������ݐ�o�b�t�@�f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveSub_Core( const WIPE_TYPE_WND_VMOVE_DATA* p_one, WIPE_TYPE_WND_VMOVE_HDATA* p_buff, int count, int count_max )
{
	int i;
	int sum_work;	// �v�Z���[�N
	int e_y_sum;	// �I��Y���W�̌v�Z����
	int min_y;
	int max_y;
	int set_wndmsk;

	sum_work = (p_one->e_y - p_one->s_y) * count;
	e_y_sum = sum_work / count_max;
	e_y_sum += p_one->s_y;

	// for���ł܂킷���ߍŏ�Y�ƍő�Y�����߂�
	if( p_one->s_y <= p_one->e_y ){
		min_y = p_one->s_y;
		max_y = p_one->e_y;

		set_wndmsk = p_one->in_out;
	}else{
		min_y = p_one->e_y;
		max_y = p_one->s_y;
		if( p_one->in_out == WIPE_WND_VMOVE_INWND ){
			set_wndmsk = WIPE_WND_VMOVE_OUTWND;
		}else{
			set_wndmsk = WIPE_WND_VMOVE_INWND;
		}
	}

	for( i=min_y; i<max_y; i++ ){
		// �}�X�N�؂�ւ�
		if( i==e_y_sum ){
			if( set_wndmsk == WIPE_WND_VMOVE_INWND ){
				set_wndmsk = WIPE_WND_VMOVE_OUTWND;
			}else{
				set_wndmsk = WIPE_WND_VMOVE_INWND;
			}
		}
		p_buff->in_out_write[ i ] = set_wndmsk;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R���@���C�v�@�������@�p�b�N
 *
 *	@param	wipe		���C�v���[�N
 *	@param	param		�p�����[�^
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_PESOCOM_PARAM* param)
{
	WIPE_TYPE_WND_PESOCOM* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_PESOCOM) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_PESOCOM) );
	data = wipe->wipe_work;


	if( param->wnd_move.fade_flg == WIPE_FADE_IN ){
		scchg_WndWndPesocomInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
	}else{
		scchg_WndWndPesocomOutInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
	}

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R�����C�v�@���C���@�p�b�N
 *
 *	@param	wipe	���C�v���[�N
 *
 *	@retval	TRUE	�I��
 *	@ratval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_PESOCOM* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// ���̊֐��̖߂�l
	
	wwm = (WIPE_TYPE_WND_PESOCOM*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		if( wwm->fade_flg == WIPE_FADE_IN ){
			ret = scchg_WndWndPesocomMain(wwm, wipe);
		}else{
			ret = scchg_WndWndPesocomOutMain(wwm, wipe);
		}
		if(ret == TRUE){
			scchg_WndEnd(wipe->fade_inout, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R�����C�v�@������
 *
 *	@param	data		���[�N
 *	@param	param		�p�����[�^
 *	@param	division	������
 *	@param	piece_sync	�V���N��
 *	@param	disp		���
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	p_wipehb	H�u�����N�֐��V�X�e��
 *	@param	heap		�q�[�v
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int move_divi;

	move_divi = FX_Mul( division * FX32_ONE, param->sync_div_par ) >> FX32_SHIFT;
	data->sub_divi = division - move_divi;

	// �p�����[�^�ۑ�
	data->p_param = param;
	data->fade_flg = param->wnd_move.fade_flg;

	// wnd_move
	scchg_WndMoveInit(&data->wnd_move, &param->wnd_move, move_divi, piece_sync, disp, wnd_sys);
	if(param->wnd_move.wnd_no == 0){	// �E�B���h�E�I��
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0,disp, param->wnd_move.fade_flg);
	}else{
		scchg_WndVisible(wnd_sys,GX_WNDMASK_W1, disp, param->wnd_move.fade_flg);
	}

	data->seq = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R���@���C�v�@���C������
 *
 *	@param	data
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe )
{
	BOOL result;
	BOOL ret = FALSE;
	
	switch( data->seq ){
	case 0:
		result = scchg_WndMoveMain( &data->wnd_move );
		if( result == TRUE ){
			data->seq ++;

			// split_divi
			scchg_WndWndVMoveInit(&data->wnd_split, &data->p_param->wnd_split, data->sub_divi, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
		}
		break;

	case 1:
		result = scchg_WndWndVMoveMain( &data->wnd_split );
		if( result == TRUE ){
			ret = TRUE;
			data->seq ++;
		}
		break;

	case 2:
		ret = TRUE;
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R���@���C�v�A�E�g�@������
 *
 *	@param	data		���[�N
 *	@param	param		�p�����[�^
 *	@param	division	������
 *	@param	piece_sync	�V���N��
 *	@param	disp		���
 *	@param	wnd_sys		�E�B���h�E�V�X�e��
 *	@param	p_wipehb	H�u�����N�֐��V�X�e��
 *	@param	heap		�q�[�v
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomOutInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int split_divi;

	data->sub_divi = FX_Mul( division * FX32_ONE, param->sync_div_par ) >> FX32_SHIFT;
	split_divi = division - data->sub_divi;

	// �p�����[�^�ۑ�
	data->p_param = param;
	data->fade_flg = param->wnd_move.fade_flg;

	// split_divi
	scchg_WndWndVMoveInit(&data->wnd_split, &data->p_param->wnd_split, split_divi,piece_sync, disp, wnd_sys, p_wipehb, heap );

	data->seq = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�\�R���@���C�v�A�E�g�@���C������
 *
 *	@param	data
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomOutMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe )
{
	BOOL result;
	BOOL ret = FALSE;
	
	switch( data->seq ){
	case 0:
		result = scchg_WndWndVMoveMain( &data->wnd_split );
		if( result == TRUE ){
			data->seq ++;

			// wnd_move
			scchg_WndMoveInit(&data->wnd_move, &data->p_param->wnd_move, data->sub_divi, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
			if(data->p_param->wnd_move.wnd_no == 0){	// �E�B���h�E�I��
				scchg_WndVisible(wipe->wnd_sys, GX_WNDMASK_W0, wipe->disp, data->p_param->wnd_move.fade_flg);
			}else{
				scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W1, wipe->disp, data->p_param->wnd_move.fade_flg);
			}
		}
		break;

	case 1:
		result = scchg_WndMoveMain( &data->wnd_move );
		if( result == TRUE ){
			ret = TRUE;
			data->seq ++;
		}
		break;

	case 2:
		ret = TRUE;
		break;
	}

	return ret;
}

