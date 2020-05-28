//==============================================================================
/**
 * @file	we_sys.c
 * @brief	�Z�G�t�F�N�g�p�̃V�X�e��
 * @author	goto
 * @date	2005.06.22(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 *
 */
//==============================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"

#include "system/arc_tool.h"

#include "wazatool.h"

#include "we_sys.h"							///< �Z�G�t�F�N�g�p�̃V�X�e��.h

#include "west_sp.h"						///< �Z�G�t�F�N�g�p�T�|�[�g.h

#include "battle_particle.h"				///< �p�[�e�B�N���p
#include "wp_tbl.h"							///< �p�[�e�B�N���p

#include "battle/battle_tcb_pri.h"			///< TCB pri
#include "battle/battle_id.h"				///< �A�[�J�C�u�f�[�^
#include "battle/fight_tool.h"				///< 

#include "include/battle/attr_def.h"		///< 
#include "include/battle/wazano_def.h"		///< 
#include "include/battle/battle_server.h"	///< 
#include "include/poketool/poke_tool.h"		///< 

#include "battle/graphic/batt_bg_def.h"		///< �A�[�J�C�u�f�[�^
#include "battle/graphic/batt_obj_def.h"		///< �A�[�J�C�u�f�[�^
#include "system/arc_tool.h"				///< �A�[�J�C�u�p
#include "system/arc_util.h"				///< �A�[�J�C�u�p

#include "system/brightness.h"				///< �P�x�ύX
#include "system/gra_tool.h"

#include "we_tool.h"
#include "we_def.h"

#include "contest/contest.h"

#include "battle/bc_common.h"

/*
///�w�i�̃t�F�[�hbit(�Z�G�t�F�N�g�p)
#define ACTIN_HAIKEI_FADE_BIT		(0x0007)
///�Z�G�t�F�N�gBG�p�p���b�g�̃t�F�[�hbit
#define ACTIN_WAZAEFF_FADE_BIT		(0x0300)
///�w�i�̃t�F�[�hbit�{�Z�G�t�F�N�gBG�p�p���b�g(�Z�G�t�F�N�g�p)
#define ACTIN_EFFBG_ALL_FADE_BIT	(ACTIN_HAIKEI_FADE_BIT | ACTIN_WAZAEFF_FADE_BIT)
*/

#define WES_OFS_ID(n)		((n) * 5000)

#define WES_HAIKEI_S_EV1	(0)
#define WES_HAIKEI_S_EV2	(31)
#define WES_HAIKEI_E_EV1	(31)
#define WES_HAIKEI_E_EV2	(0)
#define WES_HAIKEI_FO_WAIT	(0)
#define WES_HAIKEI_FI_WAIT	(WES_HAIKEI_FO_WAIT)
#define WES_HAIKEI_PAL		(0x00FF)

#define PO_ARC_ID			(ARC_BATT_OBJ)		///< �|�P�����摜�̃A�[�NID
#define FREE_TIME			(2)

#ifdef PM_DEBUG

//#define WE_SYS_DEBUG_ALLOC_SIZE_ON

u64 g_nWazaEffectHeapState = 0;
int	g_nDebugCameraType	   = 0;

#endif

// ----------------------------------------
//
//	�� �퓬�ň�����\����
//		[ BTL_SYS_PTR ]
//		�Ƃ肠�����A�K���ȃ����o�����Ă���
//
// ----------------------------------------
typedef struct _TBTL_SYS {
	
	u8	command_code;						///< ���߃R�[�h�C���f�b�N�X
	u8	mode;								///< �퓬�E�R���e�X�g�E�R���N�[���H
	u16	waza_no;							///< �G�t�F�N�g���o���Z�i���o�[
	
	s32 waza_eff_damage;					///< �Z�Ŏ󂯂�_���[�W(�񕜂̎���[ + ])
	u16	waza_eff_power;						///< �o�Ă���Z�̈З�
	u16	waza_eff_natuki;					///< �Ȃ��x
	u32	waza_eff_weather;					///< �V��
	u16 waza_eff_cnt;						///< �Z�G�t�F�N�g�̃J�E���^(����ԂƂ�)
	u16	waza_eff_ground_id;					///< �Z�G�t�F�N�g�̒n�`�f�[�^
	
	u16	at_client_no;						///< �U�����̃N���C�A���g�ԍ�(����)
	u16	df_client_no;						///< �h�䑤�̃N���C�A���g�ԍ�(�Ώ�)
	
	int	this_ptc_no;						///< �o�^�������_��ptcno;
	
	PTC_PTR		ptc[PARTICLE_GLOBAL_MAX];	///< �p�[�e�B�N���V�X�e��
	EMIT_PTR	emit[PARTICLE_EMIT_MAX];	///< �G�~�b�^�[�̐�
	
	CATS_SYS_PTR	csp;					///< �Z���A�N�^�[�Ǘ�
	EXCHR_PARAM*	excp[CLIENT_MAX];		///< �W�J���ꂽ�|�P�����f�[�^�i�[�\���̂̃|�C���^
	u8				client_type[CLIENT_MAX];///< �N���C�A���g�^�C�v
	SOFT_SPRITE*	ss[CLIENT_MAX];			///< �\�t�g�X�v���C�g
	u32				fight_type;				///< �t�@�C�g�^�C�v
	u16				mons_no[CLIENT_MAX];	///< �|�P����NO
	u8				sex[CLIENT_MAX];		///< �|�P��������
	u8				rare[CLIENT_MAX];		///< ���A�t���O
	u8				form_no[CLIENT_MAX];	///< �|�P�����t�H����No
	u32				personal_rnd[CLIENT_MAX];	///<�|�P����������
	u32				waza_kouka[CLIENT_MAX];		///< �Z���ʃt���O
	
	PERAPVOICE*		perap_voice;			///< �y���b�v
	u8*				bg_area;				///< �o�g���̔w�i
	u16*			pal_area;				///< �p���b�g

	int				henshin_flag;			///< �ւ񂵂�t���O�i32bit������Ȃ����ǁA4�o�C�g���E�␳�j

} TBTL_SYS;

// ----------------------------------------
//
//	�� ���[�v�p�\����
//		���݂̃V�[�P���X�ʒu�ȊO�ɂ�
//		�J��Ԃ����񐔂��K�v�Ȃ̂ō\����
//
// ----------------------------------------
typedef struct _TLOOP_SYS {
	
	u32* seq_adrs;							///< ���݂̃V�[�P���X�ʒu
	u8	 n_cnt;								///< ���݂̃J�E���^
	u8	 e_cnt;								///< �J��Ԃ���
	BOOL active;							///< �g�p����Ă��邩
	
} TLOOP_SYS;

typedef struct {
	
	WE_SYS_PTR		wsp;
	
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap;
	
	BOOL			flag;
	
} PT_DROP_SYS;

// ----------------------------------------
//
//	�� �Z�G�t�F�N�g�V�X�e���Ǘ��\����
//		[ WE_SYS_PTR ]
//		���ڂ̃����o�Q�Ɩh�~�̕�����
//		TWE_SYS_PTR �����̃��[�U�[�������^
//
// ----------------------------------------
typedef struct _TWE_SYS {
	
	int	 heap_area;								///< �q�[�v�G���A
	int	 eff_arc_id;

	BOOL contest_active;						///< �R���e�X�g�Ƃ��ē��쒆���H TRUE = ���쒆
	BOOL active;								///< �V�X�e��������\���H	TRUE = ���쒆
	BOOL waza_eff_active;						///< �G�t�F�N�g�����쒆���H TRUE = ���s��

	void* arc_data_adrs;						///< �A�[�J�C�u����擾�����|�C���^
	u32*  waza_eff_seq_adrs;					///< ���݂̃V�[�P���X�ʒu (4byte�P�ʂňړ� = u32)
	u32*  waza_eff_seq_adrs_j[ WE_JUMP_MAX ];	///< ���݂̃V�[�P���X�ʒu (�W�����v�p)
	TLOOP_SYS loop[ WE_LOOP_MAX ];				///< ���݂̃V�[�P���X�ʒu (���[�v�p�\����)
	PT_DROP_SYS pds[ 2 ];   

	u8	 camera_mode[PARTICLE_GLOBAL_MAX];
	u8	 camera_flag[PARTICLE_GLOBAL_MAX];
	s8	waza_se_pan;							///< SE���߂Őݒ肳���Pan�̒l	
	u8	waza_eff_wait;							///< ���߂Őݒ肳���E�F�C�g������
	
	// �Ǘ��ȂǂɎg��
	u16 waza_eff_num;							///< ���ݓo�^����Ă���AOBJ��TCB�̑���
	u16	waza_se_num;							///< ���ݓo�^����Ă���ASE�̑���
	
	s32	waza_eff_gp_wk[ WE_GENE_WK_MAX ];		///< �Z�G�t�F�N�g�ŗ��p�ł���e���|����

	pWeFunc waza_eff_exe;						///< ���ݎ��s���̃V�[�P���X
	
	// �퓬�p�̃��[�N
	BTL_SYS_PTR btl_sys;						///< �퓬������炤�p�����[�^�i�[�\����
	GF_BGL_INI* bgl;							///< BGL
	PALETTE_FADE_PTR pfd;						///< PFD
	
	CATS_RES_PTR	crp[ WE_CRP_MAX ];			///< ���\�[�X�Ǘ�
	CATS_ACT_PTR	cap[ WE_CAP_MAX ];			///< OAM��CAP
	TCATS_OBJECT_ADD_PARAM_S coap;				///< �ݒ�ۑ�
	
	// �|�P�����h���b�v�p
	CATS_RES_PTR	poke_crp;					///< �|�P����OAM�h���b�v��CRP
	CATS_ACT_PTR	poke_cap[ WE_POKE_CAP_MAX ];///< �|�P����OAM�h���b�v��CAP
	BOOL			poke_cap_use[ WE_POKE_CAP_MAX ];
	AMO_SYS_PTR		poke_amos[WE_POKE_CAP_MAX ];///< �|�P����OAM�ǔ�SYS
	AMB_SYS_PTR		poke_ambs;					///< �|�P����BG�ǔ�SYS
	
	// �`�F�b�N�p�Ȃ�
	u8	haikei_chg_flag;						///< �w�i�؂�ւ��t���O
	u8	se_end_timer;							///< SE�̏I���҂��������I�Ɍ��߂邽�߂̃J�E���^
	u8	free_time;								///< �V�ю���
	u8	sub1;

	// �w�i�p
	HC_SUB_PTR		hc_sub_ptr;					///< �w�i�T�u�V�X�e��
	TWES_HAIKEI_ARC haikei_data;				///< �w�i�f�[�^
	
	int				haikei_fade_bit;
	u8				bg_pri[ 4 ];
	
} TWE_SYS;


// -----------------------------------------
//
//	�� �T�E���h�p�̔ėp�\����
//		[ SE_SYS_PTR ]
//
// -----------------------------------------
typedef struct _TSE_SYS {

	u8	mode;				///< �R���g���[�����[�h
	
	u8	seq;				///< �V�[�P���X�Ǘ�
	u8	gene_seq;			///< �ėp�V�[�P���X
	u8	wait;				///< �E�F�C�g
	u8	gene_wait;			///< �ėp�E�F�C�g
	
	int	s_pan;				///< �J�n�ʒu�̃p��
	int	e_pan;				///< �I���ʒu�̃p��
	int	a_pan;				///< ���Z����p���̒l
	int	n_pan;				///< ���݂̃p��
	
	u8	repeat;				///< �J��Ԃ���

	u16 se_no;				///< SE�̔ԍ�
	
	u32	wk[ WE_SE_WK_MAX ];	///< �ėp���[�N
	
	WE_SYS_PTR we_sys;		///< WE-SYS�̃��[�N
	
} TSE_SYS;


// -----------------------------------------
//
//	���w�i�؂�ւ��p�̔ėp�\����
//		[ HC_SYS_PTR ]
//
// -----------------------------------------
typedef struct _THC_SYS {
	
	int	sub_seq;
	
	u8	mode;
	u8	seq;
	u8	gene_seq;
	u8	wait;

	u8	gene_wait;
	u8	ev1;
	u8	ev2;
	u8	ev1_e;
	u8	ev2_e;
	u8	fade_type;			///< �������� �f�t�H���g��
	
	int bg_id;				///< ��������BG�ԍ�
	int ch_mode;			///< �؂�ւ����[�h
	int ch_sbit;			///< �؂�ւ�����Bit
	
	int gp_wk[ WE_GENE_WK_MAX ];	///< GP_Work�̃R�s�[

	u16	move_flag:1;		///< �ړ��t���O
	u16 laster_flag:1;		///< ���X�^�[�t���O
	u16	dmy_flag:14;
	
	WE_SYS_PTR	we_sys;		///< WE_SYS�̃��[�N
	
} THC_SYS;

typedef struct {

	WAZATOOL_SCRLASTER_PTR	ptr;
	s16						x;
	s16						y;
	u8						start;
	u8						end;	
	
} HC_LASTER;


#define HC_LASTER_VOFS	(8)
#define HC_LASTER_MAX	((WAZATOOL_DEFLASTER_BUFF_SIZE - 64) / HC_LASTER_VOFS)

typedef struct {
	
	s16 start;
	s16 end;
	
	s16	speed;
	s16 ofs;
	int init;
	
} HC_LASTER_DATA;

typedef struct {
	
	HC_LASTER_DATA lst[ HC_LASTER_MAX ];

	WAZATOOL_DEFLASTER_PTR	dlp;
	
} HC_LASTER_SYS;

static void HaikeiSubSystem_LasterScroll(TCB_PTR tcb, void* work);
static const s16 speed_tbl[] = {
	32, 28, 24, 20, 16, 12,  8,  4, 
	 4,  8, 12, 16, 20, 24, 28, 32,
};

// -----------------------------------------
//
//	���w�i�؂�ւ��p�̓���ėp�\����
//		[ HC_SUB_PTR ]
//
// -----------------------------------------
typedef struct _HC_SUB_SYS {
	
	GF_BGL_INI* bgl;
	
	s16		pos_x;
	s16		pos_y;
	s16		speed_x;
	s16		speed_y;
	int		frm1;
	int		frm2;

	BOOL	active;
	BOOL	destroy;
	
	HC_LASTER_SYS* hls;

} HC_SUB_SYS;


// -----------------------------------------
//
//	���|�P�����ǔ��p�̍\����
//
// -----------------------------------------
typedef struct _TAUTO_MOVE_SYS {
	
	u8 wait;				///< wait
	u8 frame;				///< �X�V
	SOFT_SPRITE* ssp;		///< �\�t�g�X�v���C�g
	TCB_PTR		 am_tcb;	///< TCB_PTR
	
} TAUTO_MOVE_SYS;

///< OAM
typedef struct _TAMO_SYS {

	CATS_ACT_PTR	cap;	
	TAUTO_MOVE_SYS	ams;
	
} TAMO_SYS;

///< BG
typedef struct _TAMB_SYS {
	
	GF_BGL_INI*		bgl;
	TAUTO_MOVE_SYS	ams;
	
} TAMB_SYS;

// ============================================================================
//
//
//	����p�f�o�b�O�֐�
//
//
// ============================================================================


// =============================================================================
//
//
//	���v���g�^�C�v
//
//
// =============================================================================
static void WazaEffectWait(WE_SYS_PTR we_sys);
static void WazaEffectExecuted(WE_SYS_PTR we_sys);
static TCB_PTR WazaEffectTCB_Add(u8 mode, WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
static void WazaEffectTCB_Delete(u8 mode, WE_SYS_PTR we_sys, TCB_PTR tcb);

//--------------------------------------------------------------
/**
 * @brief	�Z�G�t�F�N�g�̎��s�҂�
 *
 * @param	we_sys	WE-SYS�̏�����
 *
 * @retval	none	
 *
 *		WEST_WAIT_ACT
 */
//--------------------------------------------------------------
static void WazaEffectWait(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_eff_wait == 0) {				///< wait���ݒ肳��Ă���Ȃ�҂�
		we_sys->waza_eff_wait == 0;					///< �O�̂���
		we_sys->waza_eff_exe = WazaEffectExecuted;	///< ���s�֐��ɑJ�ڂ���
	}
	else {
		we_sys->waza_eff_wait--;					///< wait�f�N�������g
	}
}


//--------------------------------------------------------------
/**
 * @brief	�Z�G�t�F�N�g�̎��s [ ���ۂɃR�}���h���s���ꏊ ]
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 *		WazaEffectAct
 */
//--------------------------------------------------------------
static void WazaEffectExecuted(WE_SYS_PTR we_sys)
{
	pWeFunc func;
	
	do {
		///< ���s�֐�
		func = WazaEffectCommandGet(*(we_sys->waza_eff_seq_adrs));
		func(we_sys);
		
	} while (we_sys->waza_eff_wait == 0			///< �Z�E�F�C�g = 0
		 &&  we_sys->waza_eff_active == TRUE);	///< �G�t�F�N�g���A�N�e�B�u
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS��pTCB�̍쐬
 *
 * @param	mode		EFFECT / SOUND
 * @param	we_sys	
 * @param	TCB_FUNC	
 * @param	work	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static TCB_PTR WazaEffectTCB_Add(u8 mode, WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;
	
	switch(mode){
	case ENUM_WETCB_EFFECT:
		we_sys->waza_eff_num++;
		break;
	case ENUM_WETCB_SOUND:
		we_sys->waza_se_num++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	tcb = TCB_Add(func, work, pri);
	
	return tcb;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS��pTCB�̔j��
 *
 * @param	mode	
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WazaEffectTCB_Delete(u8 mode, WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	switch(mode){
	case ENUM_WETCB_EFFECT:
		we_sys->waza_eff_num--;
		break;
	case ENUM_WETCB_SOUND:
		we_sys->waza_se_num--;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	TCB_Delete(tcb);
}









// =============================================================================
//
//
//	���O���Q�Ɗ֐�
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief   WE_SYS �̏�����
 *
 * @param 	heap_area	�q�[�v�G���A
 *
 * @retval	WE_SYS_PTR	NULL���߂鎞�͏��������s
 *
 */
//--------------------------------------------------------------
WE_SYS_PTR WES_Create(int heap_area)
{
	int i;

	WE_SYS_PTR we_sys = NULL;
	
	///< ���C���V�X�e���̏�����
	we_sys = sys_AllocMemory(heap_area, sizeof(TWE_SYS));
	
	if (we_sys == NULL){
		GF_ASSERT(we_sys != NULL);
		return NULL;
	}
	memset(we_sys, 0, sizeof(TWE_SYS));
	
	///< HEAPID���������m�ۂƓ����ɐݒ�
	we_sys->heap_area = heap_area;
	
	///< �퓬�Ƃ��ē���
	we_sys->contest_active = FALSE;

	
	///< �퓬�V�X�e���̏�����
	we_sys->btl_sys = sys_AllocMemory(we_sys->heap_area, sizeof(TBTL_SYS));
	
	if (we_sys->btl_sys == NULL){
		GF_ASSERT(we_sys->btl_sys != NULL);
		return NULL;
	}
	memset(we_sys->btl_sys, 0, sizeof(TBTL_SYS));	
	
	we_sys->active = FALSE;						///< �������Ȃ̂�FALSE

	we_sys->waza_eff_seq_adrs = NULL;			///< �V�X�e�����[�N�̏������Ȃ�
	
	for (i = 0; i < WE_CRP_MAX; i++){			///< CLACT�p���[�N�̏�����
		we_sys->crp[i] = NULL;
	}
	
	for (i = 0; i < WE_POKE_CAP_MAX; i++){		///< �|�P���������ǔ��̏�����
		we_sys->poke_amos[i] = NULL;	
	}
	we_sys->poke_ambs = NULL;
	

	we_sys->active = TRUE;						///< ���������Ȃ̂�TRUE
	
	return we_sys;
}


//--------------------------------------------------------------
/**
 * @brief	�R���e�X�g�p�t���O�Z�b�g
 *
 * @param	we_sys	
 * @param	flag				TRUE = �R���e�X�g FALSE = ����ȊO
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WES_ContestFlag_Set(WE_SYS_PTR we_sys, BOOL flag)
{
	GF_ASSERT(we_sys != NULL);
	
	we_sys->contest_active  = flag;
}


//--------------------------------------------------------------
/**
 * @brief	�R���e�X�g�p�t���O�`�F�b�N
 *
 * @param	we_sys	
 *
 * @retval	BOOL				TRUE = �R���e�X�g
 *
 */
//--------------------------------------------------------------
BOOL WES_ContestFlag_Get(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);
	
	return we_sys->contest_active;
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysHeapAreaGet(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);
	
	return we_sys->heap_area;
}

//--------------------------------------------------------------
/**
 * @brief	WE_SYS �̔j��
 *
 * @param	we_sys	WE_SYS�p�̃��[�N
 *
 * @retval	BOOL	TRUE = ����
 *
 */
//--------------------------------------------------------------
BOOL WES_Delete(WE_SYS_PTR we_sys)
{
	// �V�X�e���̓���`�F�b�N
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}
	
	sys_FreeMemoryEz(we_sys->btl_sys);
	sys_FreeMemoryEz(we_sys);
		
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�Z�G�t�F�N�g�̃R�[��
 *
 * @param	we_sys	WE_SYS�p�̃��[�N
 * @param	btl_sys	�퓬�p�̃��[�N�G���A
 * @param	waza_no	�Z�ԍ�
 *
 * @retval	BOOL	TURE = ����
 *
 *	�Z�ԍ�����A�Ή�����Z�̐擪�A�h���X��waza_eff_seq_adrs�ɓ����
 *	
 *
 */
//--------------------------------------------------------------
BOOL WES_Call(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no)
{
	return WES_Call_Ex(we_sys, btl_sys, waza_no, NULL);
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 * @param	btl_sys	
 * @param	waza_no	
 * @param	bgl	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WES_Call_Ex(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no,
				 WES_CALL_BTL_EX_PARAM* wcbep)
{
	int i;
	
	int set_waza_no;
	
	set_waza_no = waza_no;
	
//	OS_Printf("�R�[��No = %d\n", waza_no);
//	OS_Printf("�A�[�NID = %d\n", wcbep->eff_arc_id);

#ifdef PM_DEBUG

	g_nWazaEffectHeapState = sys_GetHeapState( we_sys->heap_area );

#endif

	// ----- �G�t�F�N�g�p�̊�{�̃u�����h -----
	DefaultBlendSet();
	
	// ----- �V�X�e���̓���`�F�b�N -----
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}

	// ----- �J�������[�h�̏����� -----
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		we_sys->camera_mode[i] = WE_CAMERA_TYPE_ORTHO;
		we_sys->camera_flag[i] = 0;
	}

	
	// ----- WE-SYS���̏����� -----
	for (i = 0; i < WE_GENE_WK_MAX; i++){		///< �ėp���[�N������
		we_sys->waza_eff_gp_wk[i] = 0;
	}
	
	for (i = 0; i < WE_LOOP_MAX; i++){			///< ���[�v�p���[�N������
		we_sys->loop[i].active  = FALSE;
		we_sys->loop[i].seq_adrs = NULL;
		we_sys->loop[i].n_cnt	= 0;
		we_sys->loop[i].e_cnt	= 0;
	}
	
	// ----- �퓬���[�N�̎󂯓n�� -----
	we_sys->btl_sys->command_code		= btl_sys->command_code;
	we_sys->btl_sys->mode				= btl_sys->mode;
	we_sys->btl_sys->waza_no			= btl_sys->waza_no;			///< �Z�ԍ� = waza_no�Ɠ���

	we_sys->btl_sys->waza_eff_damage	= btl_sys->waza_eff_damage;	
	we_sys->btl_sys->waza_eff_power		= btl_sys->waza_eff_power;
	we_sys->btl_sys->waza_eff_natuki	= btl_sys->waza_eff_natuki;
	we_sys->btl_sys->waza_eff_weather	= btl_sys->waza_eff_weather;
	we_sys->btl_sys->waza_eff_cnt		= btl_sys->waza_eff_cnt;
	we_sys->btl_sys->waza_eff_ground_id	= btl_sys->ground_id;
	we_sys->btl_sys->at_client_no		= btl_sys->at_client_no;
	we_sys->btl_sys->df_client_no		= btl_sys->df_client_no;
	we_sys->btl_sys->henshin_flag		= btl_sys->henshin_flag;
#if 1
//	OS_Printf("��-----�������T�[�o�[������炤�f�[�^������-----��\n");
//	OS_Printf("waza_eff_damage	= %3d\n", btl_sys->waza_eff_damage);
//	OS_Printf("waza_eff_power	= %3d\n", btl_sys->waza_eff_power);
//	OS_Printf("waza_eff_natuki	= %3d\n", btl_sys->waza_eff_natuki);
//	OS_Printf("waza_eff_weather	= %3d\n", btl_sys->waza_eff_weather);
//	OS_Printf("waza_eff_cnt		= %3d\n", btl_sys->waza_eff_cnt);
//	OS_Printf("ground_id		= %3d\n", btl_sys->ground_id);
//	OS_Printf("at_client_no		= %3d\n", btl_sys->at_client_no);
//	OS_Printf("df_client_no		= %3d\n", btl_sys->df_client_no);
//	OS_Printf("��-----�������T�[�o�[������炤�f�[�^������-----��\n");
//	we_sys->btl_sys->waza_eff_cnt = 0;
#endif
	we_sys->btl_sys->csp				= wcbep->csp;
	GF_ASSERT(wcbep->csp != NULL);
	we_sys->bgl							= wcbep->bgl;
	we_sys->pfd							= wcbep->pfd;
	we_sys->btl_sys->fight_type			= wcbep->fight_type;
	
	for (i = 0; i < CLIENT_MAX; i++){
		we_sys->btl_sys->excp[i]		= wcbep->excp[i];
		we_sys->btl_sys->client_type[i] = wcbep->client_type[i];
		we_sys->btl_sys->ss[i] 		 	= wcbep->ss[i];
		we_sys->btl_sys->mons_no[i]		= wcbep->mons_no[i];
		we_sys->btl_sys->sex[i]			= wcbep->sex[i];
		we_sys->btl_sys->rare[i]		= wcbep->rare[i];
		we_sys->btl_sys->form_no[i]		= wcbep->form_no[i];
		we_sys->btl_sys->personal_rnd[i]= wcbep->personal_rnd[i];
		we_sys->btl_sys->waza_kouka[i]	= wcbep->waza_kouka[i];
	}
	
	we_sys->haikei_data					= wcbep->haikei_data;
	we_sys->btl_sys->perap_voice		= wcbep->perap_voice;
	we_sys->btl_sys->pal_area			= wcbep->pal_area;			///< �p���b�g
	we_sys->btl_sys->bg_area			= wcbep->bg_area;			///< �o�g���̔w�i

	
	// ----- �A�[�J�C�u����̎擾 -----
	if (set_waza_no == WAZANO_HIMITUNOTIKARA){
		
		int HimitunoTikara_WazaTbl[] = {
			WAZANO_DOROKAKE,				///< ����(���l)		�ǂ납��
			WAZANO_DOROKAKE,				///< ����(���l)		�ǂ납��
			WAZANO_NIIDORUAAMU,				///< �Ő�(�����܂�)	�j�[�h���A�[��
			WAZANO_NIIDORUAAMU,				///< �Ő�(�����܂�)	�j�[�h���A�[��
			WAZANO_IWAOTOSI,				///< �┧(���A)		���킨�Ƃ�
			WAZANO_IWAOTOSI,				///< �┧(���A)		���킨�Ƃ�
			WAZANO_YUKINADARE,				///< �ጴ			�䂫�Ȃ���
			WAZANO_MIZUNOHADOU,				///< ����			�݂��̂͂ǂ�
			WAZANO_KOORINOTUBUTE,			///< �X��			������Ԃ�
			WAZANO_NOSIKAKARI,				///< ��				�̂�������
			WAZANO_MADDOSYOTTO,				///< ���n			�}�b�h�V���b�g
			WAZANO_KAZEOKOSI,				///< �݋�			����������
			WAZANO_NOSIKAKARI,				///< �ȊO			�̂�������
		};
		
		if (we_sys->btl_sys->waza_eff_ground_id >= GROUND_ID_ALL){
			set_waza_no = WAZANO_TORAIATAKKU;
		}
		else {
			set_waza_no = HimitunoTikara_WazaTbl[ we_sys->btl_sys->waza_eff_ground_id ];
		}		
	//	OS_Printf("[ �Z ]:�Ђ݂̂����� �Ȃ̂� ���肩���܂���B\n�n�` = %2d\n�ZNO = %3d\n",we_sys->btl_sys->waza_eff_ground_id, set_waza_no);
	}
	
	if (set_waza_no == 0
	||	set_waza_no >  WAZANO_MAX){
		set_waza_no = WAZANO_HATAKU;
	}
#if 0
	if (wcbep->eff_arc_id == ARC_WAZA_EFF
	&&	WES_ContestFlag_Get(we_sys) == FALSE){
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
	}
#endif
	we_sys->eff_arc_id	  = wcbep->eff_arc_id;
	we_sys->arc_data_adrs = ArchiveDataLoadMalloc(we_sys->eff_arc_id, set_waza_no, we_sys->heap_area );
	
	if (we_sys->arc_data_adrs == NULL){
		GF_ASSERT(we_sys->arc_data_adrs != NULL);
		return FALSE;
	}
	we_sys->waza_eff_seq_adrs = (u32*)we_sys->arc_data_adrs;

	// ----- BG�v���C�I���e�B�̕ۑ�
	we_sys->bg_pri[ 0 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME0_M);
	we_sys->bg_pri[ 1 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME1_M);
	we_sys->bg_pri[ 2 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME2_M);
	we_sys->bg_pri[ 3 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME3_M);
	
	// ----- OAM��CAP������ -----
	for (i = 0; i < WE_CAP_MAX; i++){
		we_sys->cap[i] = NULL;
	}

	for (i = 0; i < WE_POKE_CAP_MAX; i++){
		we_sys->poke_cap[i] = NULL;
		we_sys->poke_cap_use[i] = FALSE;
	}
	
	// ----- �T�u�V�X�e�� -----
	we_sys->hc_sub_ptr = NULL;
	

	// ----- ���s�֐��̓o�^ -----
	we_sys->waza_eff_exe = WazaEffectExecuted;	///< ���s�֐��̃A�h���X

	we_sys->waza_eff_wait = 0;					///< �G�t�F�N�g�p�E�F�C�g
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		we_sys->haikei_fade_bit = ACTIN_HAIKEI_FADE_BIT;
	}
	else {
		we_sys->haikei_fade_bit = WES_HAIKEI_PAL;
	}
	
	we_sys->waza_eff_active = TRUE;				///< �Z�G�t�F�N�g�̓���ON

	return TRUE;
}	

//--------------------------------------------------------------
/**
 * @brief	�Z�G�t�F�N�g�̎��s
 *
 * @param	we_sys	WE_SYS �̃��[�N
 *
 * @retval	BOOL	TRUE = ����		FALSE = �ُ�
 *
 */
//--------------------------------------------------------------
BOOL WES_Executed(WE_SYS_PTR we_sys)
{
	// �V�X�e���̓���󋵃`�F�b�N
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}
		
	we_sys->waza_eff_exe(we_sys);

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�Z�G�t�F�N�g�̏I���`�F�b�N
 *
 * @param	we_sys	
 *
 * @retval	BOOL	TRUE = ���쒆	FALSE = �ُ�
 *
 */
//--------------------------------------------------------------
BOOL IsWES_Executed(WE_SYS_PTR we_sys)
{
	return (we_sys->waza_eff_active == TRUE) ? TRUE : FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g�̏�����
 *
 * @param	we_sys	
 *
 * @retval	BOOL	TRUE = ����		FALSE = �ُ�
 *
 */
//--------------------------------------------------------------
BOOL WES_Reset(WE_SYS_PTR we_sys)
{
	if (we_sys->arc_data_adrs == NULL){
		GF_ASSERT(we_sys->arc_data_adrs);
		return FALSE;
	}

	sys_FreeMemoryEz(we_sys->arc_data_adrs);
#if 0
#ifdef PM_DEBUG
	{
		u64 now_state;
		
		now_state = sys_GetHeapState( we_sys->heap_area );
		
#ifdef WE_SYS_DEBUG_ALLOC_SIZE_ON

		{		
			int cnt[2];
			cnt[0] = (now_state >> 32);
			cnt[1] = (g_nWazaEffectHeapState >> 32);
			OS_Printf("now cnt = %ld \n", cnt[0]);
			OS_Printf("old cnt = %ld \n", cnt[1]);
			OS_Printf("now siz = %ld \n", (now_state & 0x00000000FFFFFFFF));
			OS_Printf("old siz = %ld \n", (g_nWazaEffectHeapState & 0x00000000FFFFFFFF));
		}
#endif

		GF_ASSERT((g_nWazaEffectHeapState == now_state) && "�s��v");
	}
#endif
#endif	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	WE_SYS�����쒆���H
 *
 * @param	we_sys	WE_SYS���[�N
 *
 * @retval	BOOL	TRUE = ���쒆 FALSE = ������A�܂��̓��[�N��NULL
 *
 */
//--------------------------------------------------------------
BOOL IsWES(WE_SYS_PTR we_sys)
{
	if (we_sys == NULL){
		return FALSE;
	}
	
	return (we_sys->active == TRUE) ? TRUE : FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS�p �G�t�F�N�gTCB�쐬
 *
 * @param	we_sys	
 * @param	func	
 * @param	work	
 * @param	pri	
 *
 * @retval	TCB_PTR	
 *
 */
//--------------------------------------------------------------
TCB_PTR WEEffect_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;
	
	tcb = WazaEffectTCB_Add(ENUM_WETCB_EFFECT, we_sys, func, work, pri);
	
	return tcb;
}

TCB_PTR WEEffect_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work)
{
	TCB_PTR tcb;
	
	tcb = WazaEffectTCB_Add(ENUM_WETCB_EFFECT, we_sys, func, work, TCBPRI_WE_SUPPORT);
	
	return tcb;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS�p �T�E���hTCB�쐬
 *
 * @param	we_sys	
 * @param	func	
 * @param	work	
 * @param	pri	
 *
 * @retval	TCB_PTR	
 *
 */
//--------------------------------------------------------------
TCB_PTR WESound_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;

	tcb = WazaEffectTCB_Add(ENUM_WETCB_SOUND, we_sys, func, work, pri);

	return tcb;
}

TCB_PTR WESound_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work)
{
	TCB_PTR tcb;

	tcb = WazaEffectTCB_Add(ENUM_WETCB_SOUND, we_sys, func, work, TCBPRI_SE_CONTROL);

	return tcb;
}

//--------------------------------------------------------------
/**
 * @brief	WE-SYS�p �G�t�F�N�g�pTCB�j��
 *
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WEEffect_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	WazaEffectTCB_Delete(ENUM_WETCB_EFFECT, we_sys, tcb);
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS�p �T�E���hTCB�j��
 *
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WESound_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	WazaEffectTCB_Delete(ENUM_WETCB_SOUND, we_sys, tcb);
}





// =============================================================================
//
//
//	���퓬�p�p�����[�^�[���n���֐�
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�A�^�b�N���N���C�A���g�ԍ��擾
 *
 * @param	we_sys	
 *
 * @retval	u16			�A�^�b�N���N���C�A���g�ԍ��擾
 *
 */
//--------------------------------------------------------------
u16 WeSysATNoGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->at_client_no;
}


//--------------------------------------------------------------
/**
 * @brief	�f�B�t�F���X���N���C�A���g�ԍ��擾
 *
 * @param	we_sys	
 *
 * @retval	u16			�f�B�t�F���X���N���C�A���g�ԍ��擾
 *
 */
//--------------------------------------------------------------
u16 WeSysDFNoGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->df_client_no;
}


//--------------------------------------------------------------
/**
 * @brief	PTC�|�C���^�擾�֐�
 *
 * @param	we_sys	
 *
 * @retval	PTC_PTR		PTC�|�C���^�擾�֐�
 *
 */
//--------------------------------------------------------------
PTC_PTR WeSysPTCPointerGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->ptc[we_sys->btl_sys->this_ptc_no];
}

PTC_PTR WeSysPTCPointerNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->ptc[no];
}

//--------------------------------------------------------------
/**
 * @brief	�G�~�b�^�[�̃|�C���^�擾
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
EMIT_PTR WeSysEMITPointerGet(WE_SYS_PTR we_sys, int no)
{
	EMIT_PTR emit;
	
	emit = we_sys->btl_sys->emit[no];
	
	return emit;
}


//--------------------------------------------------------------
/**
 * @brief	BGL�̃|�C���^�擾�֐�
 *
 * @param	we_sys	
 *
 * @retval	BGL_INI*	
 *
 */
//--------------------------------------------------------------
GF_BGL_INI* WeSysBGLPointerGet(WE_SYS_PTR we_sys)
{
	return we_sys->bgl;
}


//--------------------------------------------------------------
/**
 * @brief	�ėp���[�N�̒l���擾
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	s32	
 *
 */
//--------------------------------------------------------------
s32 WeSysGPWorkGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT(no < WE_GENE_WK_MAX);
	
	return we_sys->waza_eff_gp_wk[no];
}


//--------------------------------------------------------------
/**
 * @brief	OAM��CAP���擾
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR WeSysOamCapGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT( no < WE_CAP_MAX );
	GF_ASSERT(we_sys != NULL);
	GF_ASSERT(we_sys->cap[ no ] != NULL);

	return we_sys->cap[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������CAP���擾����
 *
 * @param	we_sys			
 * @param	no					�ԍ�
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR WeSysPokeCapGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT( no < WE_POKE_CAP_MAX );
	GF_ASSERT(we_sys != NULL);
	GF_ASSERT(we_sys->poke_cap[ no ] != NULL);

	return we_sys->poke_cap[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������CRP���擾����
 *
 * @param	we_sys	
 *
 * @retval	CATS_RES_PTR	
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR WeSysPokeCrpGet(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);

	return we_sys->poke_crp;
}


//--------------------------------------------------------------
/**
 * @brief	CRP���擾���� 0����
 *
 * @param	we_sys	
 *
 * @retval	CATS_RES_PTR	
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR WeSysCrpGet(WE_SYS_PTR we_sys)
{
	return we_sys->crp[0];
}


//--------------------------------------------------------------
/**
 * @brief	CSP�̎擾
 *
 * @param	we_sys	
 *
 * @retval	CATS_SYS_PTR	
 *
 */
//--------------------------------------------------------------
CATS_SYS_PTR WeSysCspGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->csp;
}

// =============================================================================
//
//
//
//	���T�E���h�R���g���[���֘A	[ _SOUND_CONTROL_ ]
//
//
//
// =============================================================================
static SE_SYS_PTR SeControlInit(WE_SYS_PTR we_sys);
static void	SeControlStart(WE_SYS_PTR we_sys, SE_SYS_PTR ss);

static void SeControl_MainTCB(TCB_PTR tcb, void* work);

static BOOL	SeControl_None(SE_SYS_PTR ss);

static BOOL SeControl_PanFlow(SE_SYS_PTR ss);
static BOOL SeControl_PanFlowFix(SE_SYS_PTR ss);
static BOOL SeControl_PanFlowAF(SE_SYS_PTR ss);

static BOOL SeControl_Repeat(SE_SYS_PTR ss);
static BOOL SeControl_WaitPlay(SE_SYS_PTR ss);

// -----------------------------------------
//
//
//	���T�E���h�p��TCB���X�g
//
//
// -----------------------------------------
static BOOL (* const SeControlTCB[])(SE_SYS_PTR ss) = {

	SeControl_None,			// ����Ȃ�
	SeControl_PanFlow,		// �p���̕ύX
	SeControl_PanFlowFix,	// PanFlow�Ɠ����͓�������
	SeControl_PanFlowAF,	// PanFlow�Ɠ����͓�������
	
	SeControl_Repeat,		// ���s�[�g
	SeControl_WaitPlay,		// wait���҂��Ă���Đ�
};


//--------------------------------------------------------------
/**
 * @brief	�T�E���h�R���g���[���̏�����
 *
 * @param	we_sys
 *
 * @retval	static SE_SYS_PTR	
 *
 */
//--------------------------------------------------------------
static SE_SYS_PTR SeControlInit(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = sys_AllocMemory(we_sys->heap_area, sizeof(TSE_SYS));
	
	if (ss == NULL){
		GF_ASSERT(0 && "SeControl�̏��������s");
		return NULL;
	}
	memset(ss, 0, sizeof(TSE_SYS));
	
	we_sys->waza_se_num++;
	
	return ss;
}


//--------------------------------------------------------------
/**
 * @brief	�T�E���h�R���g���[��TCB�쐬
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static void	SeControlStart(WE_SYS_PTR we_sys, SE_SYS_PTR ss)
{
	ss->we_sys = we_sys;
	
	TCB_Add(SeControl_MainTCB, ss, TCBPRI_SE_CONTROL);
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[���̕���TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void SeControl_MainTCB(TCB_PTR tcb, void* work)
{
	BOOL active;
	SE_SYS_PTR ss = (SE_SYS_PTR)work;
	
	active = SeControlTCB[ss->mode](ss);
	
	if (active == FALSE){
		if (ss->we_sys->waza_se_num != 0){
			ss->we_sys->waza_se_num--;
		}
		sys_FreeMemoryEz(ss);
		TCB_Delete(tcb);
	}
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[�� �_�~�[
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_None(SE_SYS_PTR ss)
{
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[�� PanFlow
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlow(SE_SYS_PTR ss)
{
	BOOL active;
	s8	now_pan;
	
	if (ss->gene_wait++ < ss->wait){
		return TRUE;
	}
	
	active = TRUE;
	ss->gene_wait = 0;

	//ss->n_pan = ss->s_pan;
	ss->n_pan += ss->a_pan;
	
	if (ss->a_pan == 0){
		active = FALSE;	
	}
	else if (ss->s_pan < ss->e_pan){
		if (ss->n_pan >= ss->e_pan){
			active = FALSE;
		}
	}
	else {
		if (ss->n_pan <= ss->e_pan){
			active = FALSE;
		}
	}
	
	Snd_SePanSetAll(ss->n_pan);
	
//	OS_Printf("���݂̃p���̐ݒ� ��� %4d\n", ss->n_pan);
	
	if (Snd_SePlayCheck(ss->se_no) == FALSE){
		if (active == TRUE){
//			OS_Printf("�p���̈ړ����I����ĂȂ����A�r�d���Ȃ�I����Ă���̂łs�b�a���I��\n");
		}		
		return FALSE;
	}
	
	return active;
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[�� PanFlowFix
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlowFix(SE_SYS_PTR ss)
{
	return SeControl_PanFlow(ss);
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[�� PanFlowAF
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlowAF(SE_SYS_PTR ss)
{
	return SeControl_PanFlow(ss);
}


//--------------------------------------------------------------
/**
 * @brief	SE�R���g���[�� Repeat
 *
 * @param	ss	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static BOOL SeControl_Repeat(SE_SYS_PTR ss)
{
	BOOL active;
	
	if (ss->gene_wait++ < ss->wait){
		return TRUE;
	}
	
	active = TRUE;
	ss->gene_wait = 0;

	ss->repeat--;

	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->n_pan);
	
	if (ss->repeat == 0){
		active = FALSE;
	}
	
	return active;
}


//--------------------------------------------------------------
/**
 * @brief	wait���҂��Ă���SE���Đ�����
 *
 * @param	ss	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL SeControl_WaitPlay(SE_SYS_PTR ss)
{
	BOOL active;
	
	active = TRUE;
	
	if ((ss->wait--) == 0){
		
		Snd_SePlay(ss->se_no);
		Snd_SePanSet(ss->se_no, 0xffff, ss->n_pan);
	
		active = FALSE;
	}

	return active;
}












// =============================================================================
//
//
//
//	���R�}���h	[ _COMMAND_ ]
//
//
//
// =============================================================================
// =============================================================================
//
//
//	���v���g�^�C�v�錾
//
//
// =============================================================================
static void WEST_WAIT(WE_SYS_PTR we_sys);
static void WEST_WAIT_FLAG(WE_SYS_PTR we_sys);
static void WEST_LOOP_LABEL(WE_SYS_PTR we_sys);
static void WEST_LOOP(WE_SYS_PTR we_sys);
static void WEST_SEQEND(WE_SYS_PTR we_sys);
static void WEST_SE(WE_SYS_PTR we_sys);
static void WEST_POKEBG(WE_SYS_PTR we_sys);
static void WEST_POKEBG_RESET(WE_SYS_PTR we_sys);
static void WEST_BLDALPHA_SET(WE_SYS_PTR we_sys);
static void WEST_BLDALPHA_RESET(WE_SYS_PTR we_sys);
static void WEST_SEQ_CALL(WE_SYS_PTR we_sys);
static void WEST_END_CALL(WE_SYS_PTR we_sys);
static void WEST_WORK_SET(WE_SYS_PTR we_sys);
static void WEST_WORK_CLEAR(WE_SYS_PTR we_sys);
static void WEST_HENSIN_ON(WE_SYS_PTR we_sys);
static void WEST_HENSIN_ON_RC(WE_SYS_PTR we_sys);
static void WEST_TURN_CHK(WE_SYS_PTR we_sys);
static void WEST_TURN_JP(WE_SYS_PTR we_sys);
static void WEST_SEQ_JP(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHG(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_PARA_CHG(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_RECOVER(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_HALF_WAIT(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHG_WAIT(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_SET(WE_SYS_PTR we_sys);
static void WEST_SEPLAY_PAN(WE_SYS_PTR we_sys);
static void WEST_SEPAN(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOW(WE_SYS_PTR we_sys);
static void WEST_SE_REPEAT(WE_SYS_PTR we_sys);
static void WEST_SE_WAITPLAY(WE_SYS_PTR we_sys);
static void WEST_BLDCNT_SET(WE_SYS_PTR we_sys);
static void WEST_SE_TASK(WE_SYS_PTR we_sys);
static void WEST_SEWAIT_FLAG(WE_SYS_PTR we_sys);
static void WEST_WORKCHK_JP(WE_SYS_PTR we_sys);
static void WEST_POKEBG_DROP(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_INIT(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_DROP(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_FREE(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_DROP_RESET(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_AUTO_STOP(WE_SYS_PTR we_sys);
static void WEST_CAMERA_CHG(WE_SYS_PTR we_sys);
static void WEST_CAMERA_REVERCE(WE_SYS_PTR we_sys);
static void WEST_POKEBG_DROP_RESET(WE_SYS_PTR we_sys);
static void WEST_CONTEST_CHK_JP(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHKCHG(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOWFIX(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOW_AF(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET2(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET3(WE_SYS_PTR we_sys);
static void WEST_POKE_BANISH_ON(WE_SYS_PTR we_sys);
static void WEST_POKE_BANISH_OFF(WE_SYS_PTR we_sys);
static void WEST_PARTY_ATTACK_BGOFF(WE_SYS_PTR we_sys);
static void WEST_PARTY_ATTACK_BGEND(WE_SYS_PTR we_sys);
static void WEST_SE_STOP(WE_SYS_PTR we_sys);
static void WEST_SIDE_JP(WE_SYS_PTR we_sys);
static void WEST_TENKI_JP(WE_SYS_PTR we_sys);
static void WEST_CONTEST_JP(WE_SYS_PTR we_sys);
static void WEST_PTAT_JP(WE_SYS_PTR we_sys);
static void WEST_VOICE_PLAY(WE_SYS_PTR we_sys);
static void WEST_VOICE_WAIT_STOP(WE_SYS_PTR we_sys);

/// �V�K�R�}���h
static void WEST_FUNC_CALL(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_EMIT_SET(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_SEP(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_PTAT(WE_SYS_PTR we_sys);
static void WEST_WAIT_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_LOAD_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_LOAD_PARTICLE_EX(WE_SYS_PTR we_sys);
static void WEST_EXIT_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_EX_DATA(WE_SYS_PTR we_sys);
static void WEST_OLDACT_FUNC_CALL(WE_SYS_PTR we_sys);

/// CLACT �֘A�R�}���h
static void WEST_CATS_RES_INIT(WE_SYS_PTR we_sys);
static void WEST_CATS_CHAR_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_PLTT_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_CELL_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_CELL_ANM_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_ACT_ADD(WE_SYS_PTR we_sys);
static void WEST_CATS_ACT_ADD_EZ(WE_SYS_PTR we_sys);
static void WEST_CATS_RES_FREE(WE_SYS_PTR we_sys);
static void WEST_POKE_OAM_ENABLE(WE_SYS_PTR we_sys);

static void WEST_PT_DROP(WE_SYS_PTR we_sys);
static void WEST_PT_DROP_RESET(WE_SYS_PTR we_sys);


/// �f�o�b�O
static void WEST_KEY_WAIT(WE_SYS_PTR we_sys);

/// �C�����C���֐�
static inline TAP  AdrsParamGetEx(u32* adrs, u8 s_byte, u8 byte);	///< �f�[�^�擾
static inline TAP  AdrsParamGet(u32* adrs, u8 byte);					///< �f�[�^�擾
static inline TAP  SeqAdrsGet(u32* adrs);							///< �f�[�^�擾


















// =============================================================================
//
//
//	���e�[�u��	[ _COMMAND_TABLE_ ]
//
//
// =============================================================================
static const pWeFunc WazaEffectCmdList[] = {
	WEST_WAIT,
	WEST_WAIT_FLAG,
	WEST_LOOP_LABEL,
	WEST_LOOP,
	WEST_SEQEND,
	WEST_SE,
	WEST_POKEBG,
	WEST_POKEBG_RESET,
	WEST_BLDALPHA_SET,
	WEST_BLDALPHA_RESET,
	WEST_SEQ_CALL,
	WEST_END_CALL,
	WEST_WORK_SET,
	WEST_TURN_CHK,
	WEST_TURN_JP,
	WEST_SEQ_JP,
	WEST_HAIKEI_CHG,
	WEST_HAIKEI_PARA_CHG,
	WEST_HAIKEI_RECOVER,
	WEST_HAIKEI_HALF_WAIT,
	WEST_HAIKEI_CHG_WAIT,
	WEST_HAIKEI_SET,
	WEST_SEPLAY_PAN,
	WEST_SEPAN,
	WEST_SEPAN_FLOW,
	WEST_SE_REPEAT,
	WEST_SE_WAITPLAY,
	WEST_BLDCNT_SET,
	WEST_SE_TASK,
	WEST_SEWAIT_FLAG,
	WEST_WORKCHK_JP,
	WEST_POKEBG_DROP,
	WEST_POKEBG_DROP_RESET,
	WEST_CONTEST_CHK_JP,
	WEST_HAIKEI_CHKCHG,
	WEST_SEPAN_FLOWFIX,
	WEST_SEPAN_FLOW_AF,
	WEST_BGPRI_GAPSET,
	WEST_BGPRI_GAPSET2,
	WEST_BGPRI_GAPSET3,
	WEST_POKE_BANISH_ON,
	WEST_POKE_BANISH_OFF,
	WEST_PARTY_ATTACK_BGOFF,
	WEST_PARTY_ATTACK_BGEND,
	WEST_SE_STOP,
	
	// �V�K�o�^
	WEST_FUNC_CALL,				///< �w�肳�ꂽ�֐����Ăяo��
	WEST_ADD_PARTICLE,			///< �p�[�e�B�N����o�^����
	WEST_ADD_PARTICLE_EMIT_SET,	///< �p�[�e�B�N���G�~�b�^�w��o�[�W����
	WEST_ADD_PARTICLE_SEP,		///< �p�[�e�B�N���G�~�b�^�w�� ����
	WEST_ADD_PARTICLE_PTAT,		///< �p�[�e�B�N���G�~�b�^�w�� ����
	WEST_WAIT_PARTICLE,			///< �p�[�e�B�N���̏I���҂�
	WEST_LOAD_PARTICLE,			///< �p�[�e�B�N���̃��\�[�X�ǂݍ���
	WEST_LOAD_PARTICLE_EX,		///< �p�[�e�B�N���̃��\�[�X�ǂݍ���
	WEST_EXIT_PARTICLE,			///< �p�[�e�B�N���̃��\�[�X���
	WEST_OLDACT_FUNC_CALL,		///< ���Z�G�t�F�N�g�݊��p�A�N�^�[�����֐��Ăяo��
	WEST_EX_DATA,				///< �f�[�^���`
	WEST_POKEOAM_RES_INIT,		///< �|�P������OAM�ɗ��Ƃ����߂̃��\�[�X�쐬
	WEST_POKEOAM_RES_LOAD,		///< �|�P������OAM�ɗ��Ƃ����߂̃��\�[�X�쐬
	WEST_POKEOAM_DROP,			///< �|�P������OAM�ɗ��Ƃ�
	WEST_POKEOAM_RES_FREE,		///< �|�P������OAM�ɗ��Ƃ����߂Ɏg�p�������\�[�X���
	WEST_POKEOAM_DROP_RESET,	///< �|�P������OAM���
	WEST_POKEOAM_AUTO_STOP,		///< �|�P������OAM�̎����ǔ��̒�~
	WEST_CAMERA_CHG,			///< �J�����̃��[�h�ݒ�
	WEST_CAMERA_REVERCE,		///< �J�������]
	WEST_SIDE_JP,				///< �T�C�h�̈ʒu�ŃW�����v����
	WEST_VOICE_PLAY,			///< ���� �Đ�
	WEST_VOICE_WAIT_STOP,		///< ���� �҂��{��~
	WEST_WORK_CLEAR,			///< ���[�N������
	WEST_HENSIN_ON,				///< �ϐg
	WEST_HENSIN_ON_RC,			///< �ϐg���ǂ�
	WEST_TENKI_JP,				///< �V�C�W�����v
	WEST_CONTEST_JP,			///< �R���e�X�g�W�����v
	WEST_PTAT_JP,				///< �p�[�e�B�A�^�b�N

	WEST_CATS_RES_INIT,			///< ���\�[�X������
	WEST_CATS_CHAR_RES_LOAD,	///< ���\�[�X�ǂݍ���
	WEST_CATS_PLTT_RES_LOAD,	///< ���\�[�X�ǂݍ���
	WEST_CATS_CELL_RES_LOAD,	///< ���\�[�X�ǂݍ���
	WEST_CATS_CELL_ANM_RES_LOAD,///< ���\�[�X�ǂݍ���
	WEST_CATS_ACT_ADD,			///< OBJ�o�^
	WEST_CATS_ACT_ADD_EZ,		///< OBJ�o�^
	WEST_CATS_RES_FREE,			///< ���\�[�X���
	WEST_POKE_OAM_ENABLE,
	WEST_PT_DROP,
	WEST_PT_DROP_RESET,
	
	// ----- �f�o�b�O�p�̓R�R�����` -----
	WEST_KEY_WAIT,			///< �f�o�b�O
};

#define EFFECT_CMD_MAX	(NELEMS(WazaEffectCmdList))








// =============================================================================
//
//
//	���C�����C���֐��E�}�N��	[ _INLINE_MACRO_ ]
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	��{�u�����h�ݒ���s�Ȃ�
 *
 * @param	none	
 *
 * @retval	static inline void	
 *
 */
#define BATTLE_DEFAULT_BLEND_PLANE_1	(GX_BLEND_PLANEMASK_NONE)
#define BATTLE_DEFAULT_BLEND_PLANE_2	(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 |	\
										 GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD)
#define BATTLE_DEFAULT_BLEND_EV_1		(8)
#define BATTLE_DEFAULT_BLEND_EV_2		(8)
//--------------------------------------------------------------
void DefaultBlendSet(void)
{	
	G2_SetBlendAlpha(BATTLE_DEFAULT_BLEND_PLANE_1,
					  BATTLE_DEFAULT_BLEND_PLANE_2,
					  BATTLE_DEFAULT_BLEND_EV_1,
					  BATTLE_DEFAULT_BLEND_EV_2);
}

//--------------------------------------------------------------
/**
 * @brief	�w��o�C�g���f�[�^���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 * @param	s_byte	�J�n����o�C�g�ʒu
 * @param	byte	�擾����o�C�g��
 *
 * @retval	TAP	�l
 *
 */
//--------------------------------------------------------------
static inline TAP AdrsParamGetEx(u32* adrs, u8 s_byte, u8 byte)
{
	TAP val = adrs[s_byte];
	
	if (byte != 1){
		GF_ASSERT(0);
#ifdef WE_SYS_INF_OS_PRINT
//		OS_Printf("AdrsParamGetEx --- byte != 1 err!\n");
#endif
	}
	
	return val;
	
#if 0
	///< u8 �w��o�C�g�����擾���邽�߂̂���
	///< ���݂́A4byte�Œ�Ȃ̂œ��ɕK�v�Ȃ�
	int i;
	TAP val;
	
	// �^���w��byte���傫���ꍇ�G���[
	if (byte > sizeof(TAP)){
		OS_Printf("byte size over\n");
	}

	val = adrs[s_byte];
	
	for (i = s_byte + 1; i < s_byte + byte; i++){
		val += (adrs[i] << (i * 8));
	}
	
	return val;
#endif
}


//--------------------------------------------------------------
/**
 * @brief	�w��o�C�g���f�[�^���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 * @param	byte	�擾����o�C�g��
 *
 * @retval	TAP		�l
 *
 */
//--------------------------------------------------------------
static inline TAP AdrsParamGet(u32* adrs, u8 byte)
{
	TAP val;

	val = AdrsParamGetEx(adrs, 0, byte);

	return val;
}


//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�A�h���X���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 *
 * @retval	TAP		�l
 *
 */
//--------------------------------------------------------------
static inline TAP SeqAdrsGet(u32* adrs)
{
	return AdrsParamGet(adrs, 1);
}


// ----------------------------------------
//
//	�w��T�C�Y���A�h���X��i�߂�}�N��
//		�i�߂�A�h���X�̌^�Ɉˑ�����
//
// -----------------------------------------
#define ADRS_CMD(n, m)			((n) += (m))


// -----------------------------------------
//
//	�^�T�C�Y���A�h���X��i�߂�}�N��
//		�ŏ��P�ʂŃA�h���X���i��
//		ADRS_CMD �𗘗p����̂Ō^�Ɉˑ�����
//
// -----------------------------------------
#define ADRS_SHIFT(n)			(ADRS_CMD(n, 1))





// =============================================================================
//
//
//	�������Q��	[ _COMMAND_LIST_ ]
//
//	�����p�R�}���h���x��
//
//		[ _DEBUG_TOOL_ ]			�f�o�b�O�E�R�}���h�n			
//		[ _COMMAND_TOOL_ ]			�c�[���֘A
//		[ _COMMAND_PARTICLE_ ]		�p�[�e�B�N���֘A
//		[ _COMMAND_JUMP_ ]			�W�����v�֘A
//		[ _COMMAND_POKEMON_ ]		�|�P�����֘A
//		[ _COMMAND_BG_ ]			BG����֘A
//		[ _COMMAND_SOUND_ ]			�T�E���h�֘A
//		[ _COMMAND_REG_ ]			���W�X�^����֘A
//		[ _COMMAND_CLACT_ ]			�A�N�^�[����֘A
//
//
// =============================================================================
// =========================================
//
//	���f�o�b�O�E�R�}���h�n
//		[ _DEBUG_TOOL_ ]
//
// =========================================
static void WEST_KEY_WAIT(WE_SYS_PTR we_sys)
{
	we_sys->waza_eff_wait = 1;
	
//	OS_Printf("we_sys����KEY_WAIT�����s����Ă��܂��B\n[ L ] + [ START ]�Ŕ����܂��B\n");
	
	if(sys.cont & PAD_BUTTON_L){					///< �G�t�F�N�g0�܂ő҂�
		if(sys.cont & PAD_BUTTON_R){
			if (sys.trg & PAD_BUTTON_X){
				ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				we_sys->waza_eff_wait = 0;	
			}
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	�E�F�C�g��ݒ肵�āAWazaEffWait �֑J��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_wait = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_exe = WazaEffectWait;
}


//--------------------------------------------------------------
/**
 * @brief	�G�t�F�N�g���I������܂ŁA�E�F�C�g��ݒ肷��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT_FLAG(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_eff_num == 0){					///< �G�t�F�N�g0�܂ő҂�
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
	}
	else {											///< �G�t�F�N�g�����݂���Ȃ�
		we_sys->waza_eff_wait = 1;					///< ���1����Ă������ƂŃX�L�b�v�ł���
	}
}


//--------------------------------------------------------------
/**
 * @brief	���[�N�ɒl���Z�b�g����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORK_SET(WE_SYS_PTR we_sys)
{
	u32	index;
	u32 param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (index < WE_GENE_WK_MAX){
		we_sys->waza_eff_gp_wk[index] = param;
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	���[�N������
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORK_CLEAR(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}
}

int WazaEffParaGet(WE_SYS_PTR we_sys, int para_id)
{
	int dat = 0;
	
	switch(para_id){
	case WE_PARA_DAMAGE:
		dat = we_sys->btl_sys->waza_eff_damage;
		break;
	case WE_PARA_POW:
		dat = we_sys->btl_sys->waza_eff_power;
		break;
	case WE_PARA_NATUKI:
		dat = we_sys->btl_sys->waza_eff_natuki;
		break;
	case WE_PARA_WEATHER:
		dat = we_sys->btl_sys->waza_eff_weather;
		break;
	case WE_PARA_TURN:
		dat = we_sys->btl_sys->waza_eff_cnt;
		break;
	case WE_PARA_GROUND_ID:
		dat = we_sys->btl_sys->waza_eff_ground_id;
		break;
	default:
		dat = 0;
		break;
	}
	
	return dat;
}
void WeSys_PokeChangeParamMake(WE_SYS_PTR we_sys, WAZA_POKE_CHANGE_PARAM* para, int type)
{
	int i;
	
	for (i = 0; i < CLIENT_MAX; i++){
		para->excp[ i ] 		= we_sys->btl_sys->excp[ i ];
		para->ss[ i ]			= we_sys->btl_sys->ss[ i ];
		para->mons_no[ i ]		= we_sys->btl_sys->mons_no[ i ];
		para->sex[ i ]			= we_sys->btl_sys->sex[ i ];
		para->rare[ i ]			= we_sys->btl_sys->rare[ i ];
		para->form_no[ i ]		= we_sys->btl_sys->form_no[ i ];
		para->personal_rnd[ i ]	= we_sys->btl_sys->personal_rnd[ i ];
		para->client_type[ i ]	= we_sys->btl_sys->client_type[ i ];
	}
	
	switch(type){
	case WE_HENSIN_DF:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->df_client_no;
		break;
		
	case WE_HENSIN_AT:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
		
	case WE_HENSIN_MIGAWARI:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
			
	case WE_HENSIN_YOKODORI:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
		
	default:
		OS_Printf("�ϐg���@�����ݒ�\n");
		GF_ASSERT(0);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HENSIN_ON(WE_SYS_PTR we_sys)
{
	int type;
	
	WAZA_POKE_CHANGE_PARAM para;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	WeSys_PokeChangeParamMake(we_sys, &para, type);
	
	if (type == WE_HENSIN_MIGAWARI){
		MigawariChrSet(&para, we_sys->heap_area);
	}
	else if (type == WE_HENSIN_YOKODORI){
		YokodoriChrSet(&para, we_sys->heap_area);
	}
	else {
		HenshinChrSet(&para, we_sys->heap_area);
	}
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HENSIN_ON_RC(WE_SYS_PTR we_sys)
{
	int type;
	
	WAZA_POKE_CHANGE_PARAM para;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	WeSys_PokeChangeParamMake(we_sys, &para, type);
	
	HenshinChrPop(&para, we_sys->heap_area);
}


//--------------------------------------------------------------
/**
 * @brief	���[�v���x��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOOP_LABEL(WE_SYS_PTR we_sys)
{
	int i;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	///< ���[�v���x���̈ʒu���쐬
	for (i = 0; i < WE_LOOP_MAX; i++){
		if (we_sys->loop[i].active == TRUE){ continue; }
		
		we_sys->loop[i].active = TRUE;
		we_sys->loop[i].n_cnt  = 0;
		we_sys->loop[i].e_cnt  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
		we_sys->loop[i].seq_adrs = we_sys->waza_eff_seq_adrs;
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	���[�v
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOOP(WE_SYS_PTR we_sys)
{
	int i;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = WE_LOOP_MAX - 1; i >= 0; i--){
		if (we_sys->loop[i].active == FALSE){ continue; }

		we_sys->loop[i].n_cnt++;
		
		if (we_sys->loop[i].n_cnt == we_sys->loop[i].e_cnt){	///< �w��񐔃��[�v����
			we_sys->loop[i].active = FALSE;
		}
		else {													///< ���[�v�񐔂��c���Ă���
			we_sys->waza_eff_seq_adrs = we_sys->loop[i].seq_adrs;
		}
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�R�}���h�I��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQEND(WE_SYS_PTR we_sys)
{
	int i;
	int em_num = 0;
	
	if (we_sys->free_time < 1){
		we_sys->waza_eff_wait = 1;
		we_sys->free_time++;
		return;
	}
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (we_sys->btl_sys->ptc[i]){
			em_num += Particle_GetEmitterNum(we_sys->btl_sys->ptc[i]);
		}
	}

	// -------------------------------------
	//
	//	�G�t�F�N�g�Ȃǂ̏I���`�F�b�N
	//
	// -------------------------------------
	if (em_num != 0										///< �G�~�b�^�[�̐���0����Ȃ�
	||	we_sys->waza_eff_num != 0						///< �����G�t�F�N�g���o�Ă���
	||	we_sys->waza_se_num  != 0						///< SE���Đ�����Ă���
	){
		we_sys->waza_eff_wait = 1;						///< wait = 1
		we_sys->se_end_timer  = 0;						///< timer = 0
		return;
	}

	// -------------------------------------
	//
	//	SE�̍Đ��`�F�b�N
	//
	// -------------------------------------
	if (Snd_SePlayCheckAll()){							///< SE���Đ�����Ă����ꍇ
		we_sys->se_end_timer++;

		if (we_sys->se_end_timer > WE_SE_END_TIMER){	///< �I��3�b�͑҂�
			// �G�t�F�N�g�֘ASE���Ƃ߂�
			;
			;
			we_sys->se_end_timer = 0;
			we_sys->waza_eff_wait = 0;
		}
		else {
			we_sys->waza_eff_wait = 1;
			return;
		}
	}
	we_sys->se_end_timer = 0;
	we_sys->free_time = 0;
	
	// -------------------------------------
	//
	//	�V�X�e�������N���A
	//
	// -------------------------------------
	for (i = 0; i < WE_JUMP_MAX; i++){					///< jump��A�h���X������
		we_sys->waza_eff_seq_adrs_j[i] = NULL;
	}
	
	for (i = 0; i < WE_LOOP_MAX; i++){					///< loop��A�h���X�������Ȃ�
		we_sys->loop[i].seq_adrs = NULL;
		we_sys->loop[i].n_cnt 	 = 0;
		we_sys->loop[i].e_cnt	 = 0;
		we_sys->loop[i].active	 = FALSE;
	}
	
	for (i = 0; i < WE_CRP_MAX; i++){					///< CLACT�p���[�N�̏�����
		if (we_sys->crp[i] != NULL){
			CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->crp[i]);
		}
		we_sys->crp[i] = NULL;
	}
	
	for (i = 0; i < WEDEF_AUTO_MOVE_MAX; i++){			///< �����ǔ����[�N�̏�����
		WeSysAutoMoveStop(we_sys, i);
	}
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (we_sys->btl_sys->ptc[i]){							///< �p�[�e�B�N���̃V�X�e���I��
			Wp_Exit(we_sys->btl_sys->ptc[i]);
			we_sys->btl_sys->ptc[i] = NULL;
		}
	}
	
	if (we_sys->hc_sub_ptr != NULL){					///< �T�u�V�X�e����~
		we_sys->hc_sub_ptr = NULL;
	}
	
	if (WES_ContestFlag_Get(we_sys) == FALSE){
		BattleDefaultBlendSet();
		// �L�����N�^�f�[�^�N���A
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(we_sys) ,BT_BGL_FrameGet(we_sys, WES_BF_EFFECT) );
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	}
	else {
		ActinExTool_DefaultBlendSet();
	}
	
	GF_BGL_PrioritySet(GF_BGL_FRAME0_M, we_sys->bg_pri[ 0 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME1_M, we_sys->bg_pri[ 1 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME2_M, we_sys->bg_pri[ 2 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME3_M, we_sys->bg_pri[ 3 ]);

	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_X_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_Y_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
	
//	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	we_sys->waza_eff_active = FALSE;					///< �V�X�e���̒�~	
}



// =========================================
//
//	���p�[�e�B�N���n
//		[ _COMMAND_PARTICLE_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N���̓o�^
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_ADD_PARTICLE(WE_SYS_PTR we_sys)
{

	u32	index;
	u32 cb_no;
	u32	no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �p�[�e�B�N���ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �R�[���o�b�N�֐��̔ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], index, cb_no, we_sys);
}

static void WEST_ADD_PARTICLE_EMIT_SET(WE_SYS_PTR we_sys)
{

	u32	index;
	u32 cb_no;
	u32	no;
	u32	emit_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	emit_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �p�[�e�B�N���ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �R�[���o�b�N�֐��̔ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;
	
	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[emit_no] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], index, cb_no, we_sys);
}

static int ParticleSepIndexGet(WE_SYS_PTR we_sys)
{
	int index;
	int	at, df;
	int	at_no, df_no;
	
	int	 index_tbl[][ 6 ] = {
		///	aa	bb		a	b		c	d
		{ 0xFF,    1, 0xFF, 0xFF, 0xFF, 0xFF },	// aa
		{    4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// bb
		{ 0xFF, 0xFF, 0xFF,    3, 0xFF,    1 },	// a
		{ 0xFF, 0xFF,    6, 0xFF,    4, 0xFF },	// b
		{ 0xFF, 0xFF, 0xFF,    1, 0xFF,    2 },	// c
		{ 0xFF, 0xFF,    4, 0xFF,    5, 0xFF },	// d
	};
	
	at_no = WeSysATNoGet(we_sys);
	df_no = WeSysDFNoGet(we_sys);
	
	at = WET_ClientTypeGet(we_sys, at_no);
	df = WET_ClientTypeGet(we_sys, df_no);
	
	index = index_tbl[ at ][ df ];
	
	GF_ASSERT(index != 0xFF);

	return index - 1;
}

static int ParticlePtAtIndexGet(WE_SYS_PTR we_sys)
{
	int index;
	int	at, df;
	int	at_no, df_no;
	
	int	 index_tbl[][ 6 ] = {
		///	aa	bb		a	b		c	d
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// aa
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// bb
		{ 0xFF, 0xFF, 0xFF, 0xFF,    0, 0xFF },	// a
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    1 },	// b
		{ 0xFF, 0xFF,    1, 0xFF, 0xFF, 0xFF },	// c
		{ 0xFF, 0xFF, 0xFF,    0, 0xFF, 0xFF },	// d
	};
	
	at_no = WeSysATNoGet(we_sys);
	df_no = WeSysDFNoGet(we_sys);
	
	at = WET_ClientTypeGet(we_sys, at_no);
	df = WET_ClientTypeGet(we_sys, df_no);
	
	index = index_tbl[ at ][ df ];
	
	GF_ASSERT(index != 0xFF);

	return index;
}

static void WEST_ADD_PARTICLE_SEP(WE_SYS_PTR we_sys)
{
	int i;
	u32	index[ 6 ];
	u32 cb_no;
	u32	no;
	u32	set_index;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	for (i = 0; i < 6; i++){
		index[ i ] = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �p�[�e�B�N���ԍ�
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);		
	}

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �R�[���o�b�N�֐��̔ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	{
		int id;
		
		id = ParticleSepIndexGet(we_sys);
		
		set_index = index[ id ];
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], set_index, cb_no, we_sys);
}


static void WEST_ADD_PARTICLE_PTAT(WE_SYS_PTR we_sys)
{
	int i;
	u32	index[ 4 ];
	u32 cb_no;
	u32	no;
	u32	set_index;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	for (i = 0; i < 4; i++){
		index[ i ] = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �p�[�e�B�N���ԍ�
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);		
	}

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);				///< �R�[���o�b�N�֐��̔ԍ�
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	{
		int id;
		
		id = ParticlePtAtIndexGet(we_sys);
		
		set_index = index[ id ];
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], set_index, cb_no, we_sys);
}


//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N���̏I���҂�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT_PARTICLE(WE_SYS_PTR we_sys)
{
	int i;
	int em_num;
	
	em_num = 0;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		
		if (we_sys->btl_sys->ptc[i] == NULL){ continue; }
		
		em_num += Particle_GetEmitterNum(we_sys->btl_sys->ptc[i]);	///< �G�~�b�^���̎擾
	}
	
	if (em_num == 0){											///< �G�~�b�^�� = 0�Ȃ�I�����Ă�
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N���̃��\�[�X�̓ǂݍ���
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOAD_PARTICLE(WE_SYS_PTR we_sys)
{
	u32 index;
	u32	no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	
	GF_ASSERT(we_sys->btl_sys->ptc[no] == NULL);
	
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

#ifdef PARTICLE_VBLANK_LOAD
//	OS_Printf(">> �p�[�e�B�N����VBlank�Ń��[�h���܂��B\n");
	we_sys->btl_sys->ptc[no] = Wp_Init(we_sys->heap_area, index, FALSE);
	
	we_sys->waza_eff_wait = PARTICLE_VBLANK_LOAD_WAIT;	
	we_sys->waza_eff_exe  = WazaEffectWait;
#else
	we_sys->btl_sys->ptc[no] = Wp_Init(we_sys->heap_area, index, TRUE);
#endif
}

static void WEST_LOAD_PARTICLE_EX(WE_SYS_PTR we_sys)
{
	u32 index;
	u32 arc_no;
	u32	no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	arc_no = ARC_SAMPLE_PARTICLE;
	
	
	GF_ASSERT(we_sys->btl_sys->ptc[no] == NULL);
	
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
#ifdef PARTICLE_VBLANK_LOAD
//	OS_Printf(">> �p�[�e�B�N����VBlank�Ń��[�h���܂��B\n");
	we_sys->btl_sys->ptc[no] = Wp_InitEx(we_sys->heap_area, arc_no, index, FALSE);
	
	we_sys->waza_eff_wait = PARTICLE_VBLANK_LOAD_WAIT;	
	we_sys->waza_eff_exe  = WazaEffectWait;
#else
	we_sys->btl_sys->ptc[no] = Wp_InitEx(we_sys->heap_area, arc_no, index, TRUE);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N���̃��\�[�X�̉��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_EXIT_PARTICLE(WE_SYS_PTR we_sys)
{
	u32	no;
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Wp_Exit(we_sys->btl_sys->ptc[no]);
	we_sys->btl_sys->ptc[no] = NULL;
}



// =========================================
//
//	���W�����v�n
//		[ _COMMAND_JUMP_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	�֐��W�����v
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQ_CALL(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < WE_JUMP_MAX; i++){
		// �擪���珇�ɊJ���Ă���ꏊ��T��
		if (we_sys->waza_eff_seq_adrs_j[i] != NULL){ continue; }
		
		we_sys->waza_eff_seq_adrs_j[i] = we_sys->waza_eff_seq_adrs + 1;
		
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
		

		return;
	}	
}


//--------------------------------------------------------------
/**
 * @brief	�֐��W�����v������ǂ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_END_CALL(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = WE_JUMP_MAX - 1; i >= 0; i--){
		if (we_sys->waza_eff_seq_adrs_j[i] == NULL){ continue; }
		
		we_sys->waza_eff_seq_adrs = we_sys->waza_eff_seq_adrs_j[i];	

		we_sys->waza_eff_seq_adrs_j[i] = NULL;

		return;
	}
}



//--------------------------------------------------------------
/**
 * @brief	�w�肵�����[�N�ԍ��Ɠ����l�Ȃ�΃W�����v
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORKCHK_JP(WE_SYS_PTR we_sys)
{
	u32 index;
	u32 param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	index = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (param == we_sys->waza_eff_gp_wk[index]){
		we_sys->waza_eff_seq_adrs = (u32*)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�R���e�X�g�̏ꍇ�͎w��A�h���X�ɔ��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CONTEST_CHK_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (WeSysModeGet(we_sys->btl_sys)){
		we_sys->waza_eff_seq_adrs = (u32*)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	�w�肳�ꂽ�֐����Ăяo���R�}���h
 *			�A�h���X����Q�Ƃ������
 *			�Ăяo���֐��̃A�h���X
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_FUNC_CALL(WE_SYS_PTR we_sys)
{
	int i;
	u32 id;
	u32 cnt;
	pWeFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	func = WazaEffectSupportFuncGet(id);
	
	cnt  = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	for (; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}

	func(we_sys);
}


//--------------------------------------------------------------
/**
 * @brief	�^�[�����ɉ����āA�V�[�P���X�̐؂�ւ����s��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TURN_CHK(WE_SYS_PTR we_sys)
{
	int turn;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->btl_sys->waza_eff_cnt & 1){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	
}


//--------------------------------------------------------------
/**
 * @brief	�T�C�h�ŃV�[�P���X�؂�ւ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SIDE_JP(WE_SYS_PTR we_sys)
{
	int type;
	int side;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	
	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (type == 0){
		side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	}
	else {
		side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);
	}
	
	if (side == SIDE_ENEMY){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}

	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
}


//--------------------------------------------------------------
/**
 * @brief	�V�C�Ő؂�ւ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TENKI_JP(WE_SYS_PTR we_sys)
{
	int tenki;
	int tenki_tbl[] = {	///< tenki�����
		FIELD_CONDITION_AME_ALL,
		FIELD_CONDITION_SUNAARASHI_ALL,
		FIELD_CONDITION_HARE_ALL,
		FIELD_CONDITION_ARARE_ALL,
	};
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	tenki = we_sys->btl_sys->waza_eff_weather;

	if (tenki != 0){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		{
			int i;
			for (i = 0; i < NELEMS(tenki_tbl); i++){
				
				if (tenki & tenki_tbl[i]){
					break;
				}
				else {
					ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				}
				
				#if 0
				if (tenki != tenki_tbl[ i ]){
					ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				}
				else {
					break;
				}
				#endif
			}
		}	
	}
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
}



//--------------------------------------------------------------
/**
 * @brief	�R���e�X�g��p
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CONTEST_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�[�A�^�b�N
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_PTAT_JP(WE_SYS_PTR we_sys)
{
	int at_side;
	int df_side;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	at_side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	df_side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);
	
	if (at_side == df_side){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w��^�[���Ɠ����Ȃ�΁A�V�[�P���X�؂�ւ����s��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TURN_JP(WE_SYS_PTR we_sys)
{
	int cnt;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	if (cnt == we_sys->btl_sys->waza_eff_cnt){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	�w��A�h���X�ɃW�����v����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQ_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
}



// =========================================
//
//	���|�P�����֘A
//		[ _COMMAND_POKEMON_ ]
//
// =========================================

static int WEST_Tool_DropPokeClientNoGet(WE_SYS_PTR we_sys, int flag);

//--------------------------------------------------------------
/**
 * @brief	����t���O����A�N���C�A���g�ԍ����擾����
 *
 * @param	we_sys	
 * @param	flag	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static int WEST_Tool_DropPokeClientNoGet(WE_SYS_PTR we_sys, int flag)
{
	int no;
	
	switch(flag){
	case WEDEF_DROP_M1:
		no = we_sys->btl_sys->at_client_no;
		break;

	case WEDEF_DROP_E1:
		no = we_sys->btl_sys->df_client_no;
		break;

	case WEDEF_DROP_M2:
		no = WET_AllySideClientNoGet(we_sys, we_sys->btl_sys->at_client_no);
		break;

	case WEDEF_DROP_E2:
		no = WET_AllySideClientNoGet(we_sys, we_sys->btl_sys->df_client_no);
		break;
	
	case WEDEF_DROP_A:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_AA || type == CLIENT_TYPE_A){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
		}
		break;
	case WEDEF_DROP_B:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_BB || type == CLIENT_TYPE_B){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
		}
		break;
	case WEDEF_DROP_C:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_C){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
		}
		break;
	case WEDEF_DROP_D:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_D){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
		}
		break;
	}
	
	return no;
}



//--------------------------------------------------------------
/**
 * @brief	OAM�������Ń\�t�g�X�v���C�g��ǔ�����TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_Tool_AutoMoveOAM_TCB(TCB_PTR tcb, void* work)
{
	AMO_SYS_PTR wk = (AMO_SYS_PTR)work;
	
	s16 px;
	s16 py;
	
	if (wk->ams.frame != 0){
		wk->ams.wait++;
		if (wk->ams.wait != wk->ams.frame){ return; }
		wk->ams.wait = 0;
	}

	px = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_X);
	py = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_Y);
	py -= SoftSpriteParaGet(wk->ams.ssp, SS_PARA_SHADOW_HEIGHT);
	
	CATS_ObjectPosSetCap(wk->cap, px, py);	
}


//--------------------------------------------------------------
/**
 * @brief	BG�������Ń\�t�g�X�v���C�g��ǔ�����TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_Tool_AutoMoveBG_TCB(TCB_PTR tcb, void* work)
{
	AMB_SYS_PTR wk = (AMB_SYS_PTR)work;
	
	s16 px;
	s16 py;
	
	if (wk->ams.frame != 0){
		wk->ams.wait++;
		if (wk->ams.wait != wk->ams.frame){ return; }
		wk->ams.wait = 0;
	}

	px = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_X);
	py = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_Y);
	py -= SoftSpriteParaGet(wk->ams.ssp, SS_PARA_SHADOW_HEIGHT);
	
	GF_BGL_ScrollSet(wk->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -(px-40));
	GF_BGL_ScrollSet(wk->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -(py-40));
}


//--------------------------------------------------------------
/**
 * @brief	�����ǔ��̏I��
 *
 * @param	we_sys	
 * @param	stop_tr	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSysAutoMoveStop(WE_SYS_PTR we_sys, int stop_tr)
{
	if (stop_tr == WEDEF_AM_STOP_BG){
		if (we_sys->poke_ambs != NULL){
			TCB_Delete(we_sys->poke_ambs->ams.am_tcb);
			sys_FreeMemoryEz(we_sys->poke_ambs);
			we_sys->poke_ambs = NULL;
		}
	}
	else {
		if (we_sys->poke_amos[ stop_tr ] != NULL){
			TCB_Delete(we_sys->poke_amos[ stop_tr ]->ams.am_tcb);
			sys_FreeMemoryEz(we_sys->poke_amos[ stop_tr ]);
			we_sys->poke_amos[ stop_tr ] = NULL;
		}
	}
}

static void WEST_POKEBG(WE_SYS_PTR we_sys)
{
}
static void WEST_POKEBG_RESET(WE_SYS_PTR we_sys)
{
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������BG�ɗ��Ƃ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 *	flag =	0 �U���|�P������BG��
 *			1 �Ώۃ|�P������BG��
 *			2 �U���|�P�����̑�����BG��
 *			3 �Ώۃ|�P�����̑�����BG��
 *
 *	auto_move = 0 �ړ����ʂ�BG�ɔ��f���Ȃ�
 *				1 �ړ����ʂ�BG�ɔ��f����
 */
//--------------------------------------------------------------
static void WEST_POKEBG_DROP(WE_SYS_PTR we_sys)
{	
	void* oam_temp = NULL;
	int flag;
	int auto_move;
	int client_no;
	int arcID;
	int index_pal;
	int index_screen;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	auto_move = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	arcID	  = we_sys->btl_sys->excp[client_no]->arcID;
	index_pal = we_sys->btl_sys->excp[client_no]->pal_index;
	oam_temp  = we_sys->btl_sys->excp[client_no]->exchr_buffer;
	
	if (WES_ContestFlag_Get(we_sys) == TRUE
	&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
		index_screen = PB_F_512_SCREEN_ID;		///< ���]
	}
	else {
		index_screen = PB_N_512_SCREEN_ID;		///< �ʏ�
	}

	{
		u8* adrs = GF_BGL_CgxGet(BATTLE_FRAME_EFFECT);
		
		MI_CpuFill8(adrs, 0, 10 * 10 * 2 * 0x20);
	}

//	GF_BGL_ScrClear(we_sys->bgl, BATTLE_FRAME_EFFECT);
//	GF_BGL_ScrClearCode( we_sys->bgl, BATTLE_FRAME_EFFECT, 64 );

	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);

	GF_BGL_LoadCharacter(we_sys->bgl, BATTLE_FRAME_EFFECT, oam_temp,  POKE_TEX_SIZE, 0);
	
	PaletteWorkSet_Arc(we_sys->pfd,
					   arcID, index_pal,
					   we_sys->heap_area, FADE_MAIN_BG, 0, WEDEF_BG_POKE_COL_POS);

	ArcUtil_ScrnSet(ARC_BATT_BG,
					index_screen,
					we_sys->bgl,
					BATTLE_FRAME_EFFECT,0,0,0,we_sys->heap_area);
	
	///< �����ǔ�TCB�ݒ�
	if (auto_move == WEDEF_POKE_AUTO_ON){
		TCB_PTR tcb;
		
		we_sys->poke_ambs = sys_AllocMemory(we_sys->heap_area, sizeof(TAMO_SYS));
		we_sys->poke_ambs->bgl		 = we_sys->bgl;
		we_sys->poke_ambs->ams.ssp   = WeSysSoftSpritePointerGet(we_sys, client_no);
		we_sys->poke_ambs->ams.wait  = 0;
		we_sys->poke_ambs->ams.frame = 0;
		
		tcb = TCB_Add(WEST_Tool_AutoMoveBG_TCB, we_sys->poke_ambs, 0x1001);
		
		we_sys->poke_ambs->ams.am_tcb = tcb;
	}
	
	///< ���W���|�P�����ɂ��킹��
	{
		s16 px;
		s16 py;

		px = SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_POS_X);
		py = SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_POS_Y);
		py -= SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_SHADOW_HEIGHT);
		
		GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -(px-40));
		GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -(py-40));
	}

	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT, BT_3DPriorityGet(we_sys));
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������BG���Ƃ������Z�b�g
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEBG_DROP_RESET(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		u8* adrs = GF_BGL_CgxGet(BATTLE_FRAME_EFFECT);
		
		MI_CpuFill8(adrs, 0, 10 * 10 * 2 * 0x20);
	}	
//	GF_BGL_ScrClearCode(we_sys->bgl, BATTLE_FRAME_EFFECT, 0x64);
//	GF_BGL_ScrClear(we_sys->bgl, BATTLE_FRAME_EFFECT);

	WeSysAutoMoveStop(we_sys, WEDEF_AM_STOP_BG);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������OAM���\�[�X������
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_INIT(WE_SYS_PTR we_sys)
{
	///< ���\�[�X�̍쐬
	int obj_num = WE_POKE_CAP_MAX;
	TCATS_RESOURCE_NUM_LIST crnl = {
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX, 0, 0 };
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	we_sys->poke_crp = CATS_ResourceCreate(we_sys->btl_sys->csp);
	
	CATS_ClactSetInit(we_sys->btl_sys->csp, we_sys->poke_crp, obj_num);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(we_sys->btl_sys->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
	
	CATS_ResourceManagerInit(we_sys->btl_sys->csp, we_sys->poke_crp, &crnl);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P����OAM���\�[�X���[�h
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_id[6];
	int use_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	use_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_id[0] = CHARID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[1] = PLTTID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[2] = CELLID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[3] = CELLANMID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[4] = 0;
	res_id[5] = 0;

	///< �]��
	CATS_LoadResourceCharArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 PO_ARC_ID, PO_CHAR_ID, 0,
							 NNS_G2D_VRAM_TYPE_2DMAIN, res_id[0]);

	CATS_LoadResourcePlttWorkArc(we_sys->pfd, FADE_MAIN_OBJ,
								 we_sys->btl_sys->csp, we_sys->poke_crp,
								 PO_ARC_ID, PO_PLTT_ID, 0,
								 NNS_G2D_VRAM_TYPE_2DMAIN, 1, res_id[1]);

	CATS_LoadResourceCellArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 PO_ARC_ID, PO_CELL_ID, 0, res_id[2]);

	CATS_LoadResourceCellAnmArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 	PO_ARC_ID,	PO_CELLANM_ID, 0, res_id[3]);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P������OAM�h���b�v
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_DROP(WE_SYS_PTR we_sys)
{	
	u8* oam_temp = NULL;
	CATS_ACT_PTR cap = NULL;
	int res_id[6];

	int flag;
	int auto_move;
	int cap_id;
	int use_no;
	int client_no;
	int arcID;
	int index_pal;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	auto_move = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	use_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	res_id[0] = CHARID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[1] = PLTTID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[2] = CELLID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[3] = CELLANMID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[4] = 0;
	res_id[5] = 0;
	
	/// �N���C�A���gNo�̎擾
	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	
	arcID	  = we_sys->btl_sys->excp[client_no]->arcID;
	index_pal = we_sys->btl_sys->excp[client_no]->pal_index;
	oam_temp  = we_sys->btl_sys->excp[client_no]->exchr_buffer;
	{
		///< OAM�o�^
		TCATS_OBJECT_ADD_PARAM_S coap;
		SOFT_SPRITE* ssp = WeSysSoftSpritePointerGet(we_sys, client_no);
		int defence_client;
		int i;
		s16 px;
		s16 py;
		
		if (ssp != NULL){
			px = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
			py = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
			py -= SoftSpriteParaGet(ssp, SS_PARA_SHADOW_HEIGHT);
			
		}

		
		coap.x		= px;
		coap.y		= py;
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < 6; i++){
			coap.id[i] = res_id[i];
		}
		
		cap = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->poke_crp, &coap);
		
		if (ssp == NULL){
			CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
		}
		else {
			int vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
			
			if (vf == 1){
				CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
			}			
		}
		
		if (WES_ContestFlag_Get(we_sys) == TRUE
		&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
			CATS_ObjectFlipSetCap(cap, CLACT_FLIP_H);
		}
	}
	
	if (WeSysSoftSpritePointerGet(we_sys, client_no) != NULL)
	{
		///< �_�~�[�L�����ɐ����L������]�����Ȃ���
		NNSG2dImageProxy * image;
		
		image = CLACT_ImageProxyGet(cap->act);
				
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
			image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
			oam_temp,
			POKE_TEX_SIZE);
	}
	
	if (WeSysSoftSpritePointerGet(we_sys, client_no) != NULL)
	{
		///< �_�~�[�p���b�g�ɐ����ȃp���b�g��]�����Ȃ���
		NNSG2dImagePaletteProxy* palette;
		int pal_no;
		
		palette = CLACT_PaletteProxyGet(cap->act);
		
		pal_no = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
		
		PaletteWorkSet_Arc(we_sys->pfd, arcID, index_pal, we_sys->heap_area,
						   FADE_MAIN_OBJ, 0x20, pal_no*16);
	}
		
	GF_ASSERT(we_sys->poke_cap[ cap_id ] == NULL);
	
	we_sys->poke_cap[ cap_id ] = cap;
	we_sys->poke_cap_use[ cap_id ] = TRUE;
	
	///< �����ǔ�TCB�ݒ�
	if (auto_move == WEDEF_POKE_AUTO_ON){		
		TCB_PTR tcb;
		
		if (WeSysSoftSpritePointerGet(we_sys, client_no) == NULL){ return; }
		
		we_sys->poke_amos[ cap_id ] = sys_AllocMemory(we_sys->heap_area, sizeof(TAMO_SYS));
		we_sys->poke_amos[ cap_id ]->cap	   = cap;
		we_sys->poke_amos[ cap_id ]->ams.ssp   = WeSysSoftSpritePointerGet(we_sys, client_no);
		we_sys->poke_amos[ cap_id ]->ams.wait  = 0;
		we_sys->poke_amos[ cap_id ]->ams.frame = 0;
		
		tcb = TCB_Add(WEST_Tool_AutoMoveOAM_TCB, we_sys->poke_amos[ cap_id ], 0x1001);
		
		we_sys->poke_amos[ cap_id ]->ams.am_tcb = tcb;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�|�P����OAM�h���b�v�p���\�[�X�폜
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_FREE(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->poke_crp != NULL){
		CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->poke_crp);
	}
	we_sys->poke_crp = NULL;
}


//--------------------------------------------------------------
/**
 * @brief	�|�P����OAM�̉��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_DROP_RESET(WE_SYS_PTR we_sys)
{
	int cap_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (we_sys->poke_cap[cap_id] != NULL){
		CATS_ActorPointerDelete_S(we_sys->poke_cap[cap_id]);
	}
	we_sys->poke_cap_use[ cap_id ] = FALSE;
	we_sys->poke_cap[cap_id] = NULL;
}


static void PDS_Tcb(TCB_PTR tcb, void* work)
{
	PT_DROP_SYS* wk = work;
	
	if (wk->flag == FALSE){
		TCB_Delete(tcb);
		return;
	}
	
	if (wk->wsp->poke_crp != NULL){
		CATS_Draw(wk->crp);	
	}
}

static void WEST_PT_DROP(WE_SYS_PTR we_sys)
{	
	int type;
	int no;
	int cap_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->pds[no].wsp  = we_sys;
	we_sys->pds[no].crp  = we_sys->poke_crp;
	we_sys->pds[no].cap  = we_sys->poke_cap[ cap_no ];
	we_sys->pds[no].flag = TRUE;
	
	CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
	
	if (IsWeSysBattleMode2vs2(we_sys) == TRUE)
	{
		int at, df;
		
		at = WET_ClientTypeGet(we_sys, WeSysATNoGet(we_sys));
		df = WET_ClientTypeGet(we_sys, WeSysDFNoGet(we_sys));
		
		{
			int vf;
			int client_no;
			SOFT_SPRITE* ssp;
			
			client_no = WEST_Tool_DropPokeClientNoGet(we_sys, type);
			ssp = WeSysSoftSpritePointerGet(we_sys, client_no);
			
			if (ssp != NULL){
				vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
			}
			else {
				vf = 0;
			}
			
			if (vf == 1){
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_TRUE);
			}
		}
	
		switch(type){
		case WEDEF_DROP_M1:			
			if (at == CLIENT_TYPE_B
			||	at == CLIENT_TYPE_C){
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
			}
			#if 0
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			}
			#endif
			break;
		case WEDEF_DROP_M2:
			if (at == CLIENT_TYPE_D
			||	at == CLIENT_TYPE_A){
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
			}
			#if 0
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			}
			#endif
			break;
		case WEDEF_DROP_E1:
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_B:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_C:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			}
			break;
		case WEDEF_DROP_E2:
			switch(df){
			case CLIENT_TYPE_A:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_D:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			}
			break;
		}
		TCB_Add(PDS_Tcb, &we_sys->pds[no], 0x1000);
	}	
}

static void WEST_PT_DROP_RESET(WE_SYS_PTR we_sys)
{
	int no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->pds[no].flag = FALSE;
}



//--------------------------------------------------------------
/**
 * @brief	�|�P����OAM�̎����ǔ���~
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_AUTO_STOP(WE_SYS_PTR we_sys)
{
	int cap_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	WeSysAutoMoveStop(we_sys, cap_id);
}


//--------------------------------------------------------------
/**
 * @brief	�J�����̃��[�h�w��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CAMERA_CHG(WE_SYS_PTR we_sys)
{
	int no;
	int mode;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	mode = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	we_sys->camera_mode[no] = mode;
}


//--------------------------------------------------------------
/**
 * @brief	�J�������]
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WEST_CAMERA_REVERCE(WE_SYS_PTR we_sys)
{
	int no;
	int flag;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	we_sys->camera_flag[no] = flag;
}


static void WEST_POKE_BANISH_ON(WE_SYS_PTR we_sys)
{
}
static void WEST_POKE_BANISH_OFF(WE_SYS_PTR we_sys)
{
}

// =========================================
//
//	���w�i�֘A
//		[ _COMMAND_BG_ ]
//
// =========================================

// -----------------------------------------
//
//	���w�i�؂�ւ����[�h
//
// -----------------------------------------
enum ETCB_HAIKEI_MODE {
	
	ENUM_HMODE_NONE = 0,					///< �����������Ă��Ȃ�
	ENUM_HMODE_CHG,							///< �w�i�؂�ւ�
	ENUM_HMODE_HALF,						///< �t�F�[�h�̒���

};

static BOOL HaikeiChange_ParamRev(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int gp_index);


static void HaikeiChange_DataSet(HC_SYS_PTR wk, WE_SYS_PTR we_sys, int frm, int id);
static int	HaikeiChange_BitCheck(int mode, int flag);
static int	HaikeiChange_BitReset(int* mode, int flag);

static void HaikeiSubSystemFirstCall(HC_SYS_PTR wk);

///< �؂�ւ��֐�
static BOOL HaikeiChange_Blend(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiChange_Fade(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiChange_None(TCB_PTR tcb, HC_SYS_PTR wk);

///< ���A�֐�
static BOOL HaikeiRecover_Blend(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiRecover_Fade(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiRecover_None(TCB_PTR tcb, HC_SYS_PTR wk);

static BOOL (* const HaikeiChange_Table[])(TCB_PTR tcb, HC_SYS_PTR wk) = {
	HaikeiChange_Blend,
	HaikeiChange_Fade,
	HaikeiChange_None,

	HaikeiRecover_Blend,
	HaikeiRecover_Fade,
	HaikeiRecover_None,
};

///< �T�u�֐�
static BOOL HaikeiSubSystem_None(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Move(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Stop(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Exit(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_LasterScroll_Init(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_LasterScroll_Stop(HC_SYS_PTR wk);

static BOOL HaikeiSubSystem_Drop(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Recover(HC_SYS_PTR wk);

static BOOL (* const HaikeiChange_SubTable[])(HC_SYS_PTR wk) = {
	HaikeiSubSystem_None,
	HaikeiSubSystem_Move,
	HaikeiSubSystem_Stop,
	HaikeiSubSystem_Exit,
	HaikeiSubSystem_None,
	HaikeiSubSystem_LasterScroll_Init,
	HaikeiSubSystem_LasterScroll_Stop,
};


//--------------------------------------------------------------
/**
 * @brief	�w�i�p�����[�^�[���]�`�F�b�N
 *
 * @param	we_sys	
 * @param	gp_index	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_ParamRev(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int gp_index)
{
	int at_side;
	int df_side;
	
	at_side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	df_side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);

	if (hcs->gp_wk[ gp_index ] == 2){			///< ��ɂ���Ĕ��]
		
		if (at_side == df_side){
			
			if (df_side == SIDE_MINE){
				
				return FALSE;
				
			}
			else {
				
				return TRUE;
				
			}
			
		}
		else if (df_side == SIDE_MINE){
			
			return TRUE;
			
		}
		
	}
	else if (hcs->gp_wk[ gp_index ] != 0){			///< ��ɂ���Ĕ��]
		
		if (df_side == SIDE_MINE){
			
			return TRUE;
			
		}
		
	}
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��f�[�^�ݒ�
 *
 * @param	we_sys	
 * @param	frm	
 * @param	id	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiChange_DataSet(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int frm, int id)
{
//	OS_Printf("�w��w�i�f�[�^�@= %3d\n",id);
	
	ArcUtil_BgCharSet(WE_HAIKEI_ARC,
					  WeSysHaikeiDataIDGet( id, 0 ),
					  we_sys->bgl,
					  frm, 0, 0, 1, we_sys->heap_area);

	PaletteWorkSet_Arc(we_sys->pfd,
					   WE_HAIKEI_ARC, WeSysHaikeiDataIDGet( id, 1),
					   we_sys->heap_area, FADE_MAIN_BG, 0x20, WEDEF_BG_DATA_COL_POS);
					   
	GF_BGL_ScrClear(we_sys->bgl, frm);
	
	{
		int idx = 2;
		
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			idx = 4;
		}
		else if (HaikeiChange_ParamRev(hcs, we_sys, WEDEF_GP_INDEX_SCREEN_R) == TRUE){
			idx = 3;
		}
		
		ArcUtil_ScrnSet(WE_HAIKEI_ARC,
						WeSysHaikeiDataIDGet( id, idx ),
						we_sys->bgl,
						frm, 0, 0, 1, we_sys->heap_area);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ�Bit�`�F�b�N
 *
 * @param	mode	���[�h
 * @param	flag	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static int HaikeiChange_BitCheck(int mode, int flag)
{
	int bit;
	int no;

	if (((mode<<WEDEF_HAIKEI_SHIFT) & flag) == flag){
		bit = 1;
	}
	else {
		bit = 0;
	}

	return bit;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ�Bit�𗎂Ƃ�
 *
 * @param	mode	
 * @param	flag	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static int	HaikeiChange_BitReset(int* mode, int flag)
{
	int bit;
	int no;
	
	no   = WEDEF_BIT_SHIFT(flag) >> WEDEF_HAIKEI_SHIFT;
	bit  = ((*mode) &= 0xffffffff ^ (1 << no));

	return bit;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ���̃T�u�V�X�e�����s
 *
 * @param	wk	
 *
 * @retval	none	
 *
 *		���t�F�[�h�A�E�g��ɌĂ΂��T�u�R�[��
 *
 */
//--------------------------------------------------------------
static void HaikeiSubSystemFirstCall(HC_SYS_PTR wk)
{
	int i;
	int id;
	int call_id;
	
	const u32 first_call_no[] = {		///< ����N�����郂�[�hID
		WEDEF_HAIKEI_SBIT_MOVE,
		WEDEF_HAIKEI_SBIT_STOP,
		WEDEF_HAIKEI_SBIT_LASTER,
		WEDEF_HAIKEI_SBIT_LASTER_STOP,
	};
	
	for (i = 0; i < NELEMS(first_call_no); i++){
		
		if (HaikeiChange_BitCheck(wk->ch_sbit, first_call_no[i]) == 0){ continue; }

		id		= 0;
		call_id = WEDEF_HAIKEI_SBIT_SHIFT(first_call_no[i]);
		
		call_id = first_call_no[i] >> WEDEF_HAIKEI_SHIFT;
		while (call_id >= 2){
			call_id /= 2;
			id++;						
		};
		
		HaikeiChange_SubTable[id](wk);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��p�������ς݃|�C���^�̎擾
 *
 * @param	we_sys	
 *
 * @retval	HC_SYS_PTR	
 *
 */
//--------------------------------------------------------------
static HC_SYS_PTR HaikeiControlInit(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR hcs = NULL;
	
	hcs = sys_AllocMemory(we_sys->heap_area, sizeof(THC_SYS));
	
	if (hcs == NULL){
		GF_ASSERT(0 && "HaikeiControl�̏��������s");
		return NULL;
	}
	memset(hcs, 0, sizeof(THC_SYS));
	
	hcs->sub_seq = 0;
	hcs->seq     = 0;
	hcs->we_sys  = we_sys;
	
	hcs->ev1	 = WES_HAIKEI_S_EV1;
	hcs->ev2	 = WES_HAIKEI_S_EV2;
	hcs->ev1_e	 = WES_HAIKEI_E_EV1 - 2;
	hcs->ev2_e	 = WES_HAIKEI_E_EV2 + 2;
	
	///< ��������~���[�h
	if (WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_VALUE) == 1){
		hcs->ev1	= 0;
		hcs->ev2	= 31;
		hcs->ev1_e	= 15;
		hcs->ev2_e	= 7;
	}
	if (WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_VALUE) == 2){
		hcs->ev1	= 7;
		hcs->ev2	= 15;
		hcs->ev1_e	= 31 - 2;
		hcs->ev2_e	= 0  + 2;
	}
	
	{
		int i;
		
		for (i = 0; i < WE_GENE_WK_MAX; i++){
			hcs->gp_wk[ i ] = we_sys->waza_eff_gp_wk[ i ];
		}
	}
	
	we_sys->haikei_chg_flag = ENUM_HMODE_CHG;
	
	return hcs;
}


//--------------------------------------------------------------
/**
 * @brief	[ �w�i�؂�ւ� ] ���u�����h
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_Blend(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< �G�t�F�N�g�ʂɔw�i�Ɠ���BG��W�J
		WeSysBaseBGSet(wk->we_sys, BATTLE_FRAME_EFFECT);
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_BGPriorityGet(wk->we_sys, WES_BF_EFFECT);

			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND,	pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
		}
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);

		wk->seq++;
		break;

	case 1:
		///< ���l�̏�����
		{

			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
			if (WES_ContestFlag_Get(wk->we_sys) != TRUE){
				GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_16);
			}
			HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);		
		
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, wk->ev2, wk->ev1);

			HaikeiSubSystemFirstCall(wk);			
		}
		wk->seq++;
		
	case 2:
		///< ���t�F�[�h
		{
			int ev_sw = 0;
			if (wk->ev1 < wk->ev1_e){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > wk->ev2_e){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = wk->ev1_e;
				wk->ev2 = wk->ev2_e;
				wk->seq++;
			}
			G2_ChangeBlendAlpha(wk->ev2, wk->ev1);
			
			if (wk->seq != 2){
				return FALSE;
			}
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}


static BOOL HaikeiRecover_Blend(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< �w�iBG���G�t�F�N�g�ʂɓW�J
	//	WeSysBaseBGSet(wk->we_sys, BATTLE_FRAME_EFFECT);
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
		wk->seq++;

	case 1:
		///< ���l�̏�����
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_BGPriorityGet(wk->we_sys, WES_BF_EFFECT);

			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND,	pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);

			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, wk->ev1, wk->ev2);

			HaikeiSubSystemFirstCall(wk);			
		}
		wk->seq++;

	case 2:
		///< ���t�F�[�h
		{
			int ev_sw = 0;
			if (wk->ev1 < wk->ev1_e){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > wk->ev2_e){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = wk->ev1_e + 2;
				wk->ev2 = wk->ev2_e - 2;
				wk->seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	
	case 3:
		///< �G�t�F�N�g�ʂɔw�i���c���A�w�i�𕜋A������
		if (wk->move_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< �w�i�T�u�V�X�e����~
		}
		if (wk->laster_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< �w�i�T�u�V�X�e����~
		}
		
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);

		GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_CHRBASE,	GX_BG_CHARBASE_0x10000);
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR,	GX_BG_COLORMODE_256);

			WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
			WeSys_BattlePaletteTrans(wk->we_sys);
		}
		else {
					
			ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
							  wk->we_sys->haikei_data.chr_id,
							  wk->we_sys->bgl,
							  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);
							  
			PaletteWorkSet_Arc(wk->we_sys->pfd,
							   wk->we_sys->haikei_data.arc_index,
							   wk->we_sys->haikei_data.pal_id,
							   wk->we_sys->heap_area, FADE_MAIN_BG,
							   wk->we_sys->haikei_data.pal_num * 0x20,
							   wk->we_sys->haikei_data.pal_start);

		}
		ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
						wk->we_sys->haikei_data.scr_id,
						wk->we_sys->bgl,
						BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		wk->seq++;
		break;
	
	case 4:
		///< �G�t�F�N�g�ʂ����Z�b�g����
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			BattleDefaultBlendSet();
		}
		else {
			ActinExTool_DefaultBlendSet();
		}
		WeSysBaseBGReset(wk->we_sys, BATTLE_FRAME_EFFECT);
		wk->seq++;
		break;

	default:
		return FALSE;
	}

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	[ �w�i�؂�ւ� ] �t�F�[�h����
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_Fade(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
		
	case 0:
		///< �t�F�[�h�J�n
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FO_WAIT, 0, 16, 0);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, 0x200, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FO_WAIT, 0, 16, 0xFFFF);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, 0x200, 16, 0xFFFF);
		}
		wk->seq++;
	
	case 1:
		///< �t�F�[�h�I�� ���[�h�ؑ�
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }
		
		GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_16);
		HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);

		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FI_WAIT, 16, 0, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FI_WAIT, 16, 0, 0xFFFF);
		}
	
		HaikeiSubSystemFirstCall(wk);
		wk->we_sys->haikei_chg_flag = ENUM_HMODE_HALF;

		wk->seq++;
		break;
	
	default:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }
		
		return FALSE;		
	}
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	[ �w�i���A ] �t�F�[�h
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiRecover_Fade(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< �N��
		HaikeiSubSystemFirstCall(wk);
		wk->seq++;
	
	case 1:
		///< �t�F�[�h�J�n
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FO_WAIT,  0, 16, 0);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, wk->we_sys->haikei_fade_bit, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FO_WAIT,  0, 16, 0xFFFF);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, wk->we_sys->haikei_fade_bit, 16, 0xFFFF);
		}
		wk->seq++;
		
	case 2:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }

		if (wk->move_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< �w�i�T�u�V�X�e����~
		}
		if (wk->laster_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< �w�i�T�u�V�X�e����~
		}
		
		GF_BGL_VisibleSet(BATTLE_FRAME_BACKGROUND, VISIBLE_OFF);	///< �J���[���[�h�̕ύX�̂���BG��OFF
	
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_256);
				
			WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
			WeSys_BattlePaletteTrans(wk->we_sys);
		}
		else {	
			ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
							  wk->we_sys->haikei_data.chr_id,
							  wk->we_sys->bgl,
							  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);

			PaletteWorkSet_Arc(wk->we_sys->pfd,
							   wk->we_sys->haikei_data.arc_index,
							   wk->we_sys->haikei_data.pal_id,
							   wk->we_sys->heap_area, FADE_MAIN_BG,
							   wk->we_sys->haikei_data.pal_num * 0x20,
							   wk->we_sys->haikei_data.pal_start);
		}
		
		ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
						wk->we_sys->haikei_data.scr_id,
						wk->we_sys->bgl,
						BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		
		GF_BGL_VisibleSet(BATTLE_FRAME_BACKGROUND, VISIBLE_ON);		///< ���ׂēW�J���BG��ON
		wk->seq++;

	case 3:
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FI_WAIT, 16, 0, 0);
		//	ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, WES_HAIKEI_PAL, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FI_WAIT, 16, 0, 0xFFFF);
		//	ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, WES_HAIKEI_PAL, 16, 0xFFFF);
		}
		wk->seq++;
	
	default:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }

		wk->we_sys->haikei_chg_flag = ENUM_HMODE_HALF;
		wk->seq++;
		return FALSE;
	}
	return TRUE;
}


static BOOL HaikeiChange_None(TCB_PTR tcb, HC_SYS_PTR wk)
{
	HaikeiSubSystemFirstCall(wk);

	return FALSE;
}

static BOOL HaikeiRecover_None(TCB_PTR tcb, HC_SYS_PTR wk)
{
	HaikeiSubSystemFirstCall(wk);
	
	if (wk->move_flag == 1){
		BT_HaikeiSubSystemStop(wk->we_sys);						///< �w�i�T�u�V�X�e����~
	}

	return FALSE;
}

// =============================================================================
//
//
//	���w�i�؂�ւ��T�u�V�X�e��
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�X�N���[��TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiSubSysmte_Scroll(TCB_PTR tcb, void* work)
{
	HC_SUB_PTR wk = (HC_SUB_PTR)work;
	
	if (wk->destroy == TRUE){
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
		return;
	}

	wk->pos_x += wk->speed_x;
	wk->pos_y += wk->speed_y;
	
	if (wk->speed_x != 0){
		GF_BGL_ScrollSet(wk->bgl, wk->frm1, GF_BGL_SCROLL_X_SET, wk->pos_x);
	}
	
	if (wk->speed_y != 0){
		GF_BGL_ScrollSet(wk->bgl, wk->frm1, GF_BGL_SCROLL_Y_SET, wk->pos_y);	
	}
}


//--------------------------------------------------------------
/**
 * @brief	�T�u�V�X�e����~
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BT_HaikeiSubSystemStop(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys);

	if (we_sys->hc_sub_ptr == NULL){ return; }
	
	we_sys->hc_sub_ptr->destroy = TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�T�u�V�X�e���t���[���؂�ւ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BT_HaikeiSubSystemFrameChange(WE_SYS_PTR we_sys)
{
	int frm;

//	GF_ASSERT(we_sys);
//	GF_ASSERT(we_sys->hc_sub_ptr);
	
	frm = we_sys->hc_sub_ptr->frm1;
	we_sys->hc_sub_ptr->frm1 = we_sys->hc_sub_ptr->frm2;
	we_sys->hc_sub_ptr->frm2 = frm;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�t�F�[�h�r�b�g�擾
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	BT_HaikeiFadeBit(WE_SYS_PTR we_sys)
{
	return we_sys->haikei_fade_bit;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e��
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_None(HC_SYS_PTR wk)
{
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e�� [ �w�i�X�N���[�� ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Move(HC_SYS_PTR wk)
{
	int i;
	HC_SUB_PTR hs;
	
	hs = sys_AllocMemory(wk->we_sys->heap_area, sizeof(HC_SUB_SYS));
	
	hs->bgl		= wk->we_sys->bgl;

	hs->pos_x	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_BGPOS_X ];
	hs->pos_y	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_BGPOS_Y ];
	hs->speed_x	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_SPEED_X ];
	hs->speed_y	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_SPEED_Y ];
	hs->frm1	= BATTLE_FRAME_BACKGROUND;//BATTLE_FRAME_EFFECT;
	hs->frm2	= BATTLE_FRAME_BACKGROUND;
	
	if (HaikeiChange_ParamRev(wk, wk->we_sys, WEDEF_GP_INDEX_SPEED_R) == TRUE){
		hs->speed_x *= -1;
		hs->speed_y *= -1;
		hs->pos_x	*= -1;
		hs->pos_y	*= -1;
	}
	
	hs->active  = TRUE;
	hs->destroy = FALSE;
	
	wk->we_sys->hc_sub_ptr = hs;
	
	wk->move_flag = 1;
	
	TCB_Add(HaikeiSubSysmte_Scroll, hs, 0x1001);
	
	return FALSE;
}

static BOOL HaikeiSubSystem_LasterScroll_Init(HC_SYS_PTR wk)
{
	int i, j;
	WE_SYS_PTR wsp;
	HC_SUB_PTR hs;
	
	wsp = wk->we_sys;
	
	hs = sys_AllocMemory(wk->we_sys->heap_area, sizeof(HC_SUB_SYS));
	hs->hls = sys_AllocMemory(wsp->heap_area, sizeof(HC_LASTER_SYS));
	
	wsp->hc_sub_ptr = hs;
	
	wk->laster_flag = 1;
	hs->destroy = FALSE;

	hs->hls->dlp = WazaTool_InitDefLaster(WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wsp, WES_BF_BACKGROUND)),
										  WazaTool_GetLasterBuffMatrixData(0, 0),
										  wsp->heap_area);
	for (i = 0; i < HC_LASTER_MAX; i++){
		hs->hls->lst[i].start	 = (i * HC_LASTER_VOFS);
		hs->hls->lst[i].end		 = (hs->hls->lst[i].start + HC_LASTER_VOFS);
		hs->hls->lst[i].speed	 = speed_tbl[i];
		hs->hls->lst[i].ofs		 = 0;
		hs->hls->lst[i].init	 = WazaTool_GetLasterBuffMatrixData(0, 0);
		
		if (HaikeiChange_ParamRev(wk, wk->we_sys, WEDEF_GP_INDEX_SPEED_R) == TRUE){
			hs->hls->lst[i].speed	 *= -1;
		}
	}
	
	TCB_Add(HaikeiSubSystem_LasterScroll, hs, 0x1000);	
	
	return FALSE;
}


static BOOL HaikeiSubSystem_LasterScroll_Stop(HC_SYS_PTR wk)
{
	WE_SYS_PTR wsp;
	HC_SUB_PTR hs;
	
	wsp = wk->we_sys;
	hs	= wk->we_sys->hc_sub_ptr;
	
	wk->laster_flag = 1;
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	���X�^�[�X�N���[��
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiSubSystem_LasterScroll(TCB_PTR tcb, void* work)
{
	int	 i, j;
	u32* buff;
	HC_LASTER_SYS* wk = (HC_LASTER_SYS*)(((HC_SUB_PTR)work)->hls);
	HC_SUB_PTR hs = (HC_SUB_PTR)work;
	
	if (hs->destroy == TRUE){
		WazaTool_DeleteDefLaster(hs->hls->dlp);
		sys_FreeMemoryEz(hs->hls);
		sys_FreeMemoryEz(hs);
		TCB_Delete(tcb);
		return;
	}
	
	buff = WazaTool_GetDefLasterWriteBuff(wk->dlp);

	for (i = 0; i < HC_LASTER_MAX; i++){
		
		wk->lst[i].ofs += wk->lst[i].speed;
		
		for (j = wk->lst[i].start; j < wk->lst[i].end; j++){
			s16 now_x, now_y;
			
			now_x = wk->lst[i].init & 0xffff;
			now_y = wk->lst[i].init >> 16;

			buff[j] = WazaTool_GetLasterBuffMatrixData(now_x + wk->lst[i].ofs, now_y);
		}	
	}
}


//--------------------------------------------------------------
/**
 * @brief	��{�w�i���G�t�F�N�g�ʂɕ`��
 *
 * @param	wsp	
 * @param	frm	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSysBaseBGSet(WE_SYS_PTR wsp, int frm)
{
	int pri = BT_BGPriorityGet(wsp, WES_BF_BACKGROUND);

	GF_BGL_PrioritySet(frm,	pri);
	GF_BGL_VisibleSet(frm, VISIBLE_OFF);

	if (WES_ContestFlag_Get(wsp) == TRUE){
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x10000);
	}
	else {
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_COLOR,	GX_BG_COLORMODE_256);
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x10000);
	}
	
	GF_BGL_ScrClear(wsp->bgl, frm);	

	if (WES_ContestFlag_Get(wsp) == TRUE){
		ArcUtil_BgCharSet(wsp->haikei_data.arc_index,
						  wsp->haikei_data.chr_id,
						  wsp->bgl,frm,0,0,1,wsp->heap_area);
	}
	else {
		WeSys_BattleBGDraw(wsp, frm);
	}
	
	ArcUtil_ScrnSet(wsp->haikei_data.arc_index,
					wsp->haikei_data.scr_id,
					wsp->bgl,frm,0,0,1,wsp->heap_area);
//	GF_BGL_VisibleSet(frm, VISIBLE_ON);
}

void WeSysBaseBGReset(WE_SYS_PTR wsp, int frm)
{
	int pri = BT_BGPriorityGet(wsp, WES_BF_EFFECT);

	GF_BGL_PrioritySet(frm,	pri);

	if (WES_ContestFlag_Get(wsp) == TRUE){
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
	}
	else {
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_COLOR,	GX_BG_COLORMODE_16);
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
	}
	GF_BGL_ScrClear(wsp->bgl, frm);
}

//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e�� [ 256��16���[�h�ϊ� ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Drop(HC_SYS_PTR wk)
{	
	GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR,	GX_BG_COLORMODE_16);
	
	HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);

	///< �w�i�X�N���[���t���O�������Ă���ꍇ�ABG����ւ����ɔw�i�X�N���[���ʂ����ւ���	
	if (wk->move_flag == 1){
		BT_HaikeiSubSystemFrameChange(wk->we_sys);
	}
	
	///< ���X�^�[�t���O�������Ă���ꍇ�ABG����ւ����Ƀ��X�^�[�����ʂ����ւ���
	if (wk->laster_flag == 1){
		if (wk->we_sys->hc_sub_ptr->hls->dlp != NULL){
			int now_addr = WazaTool_GetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp);
			int bg_addr  = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND));
			int eff_addr = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT));
			if (now_addr == bg_addr){
				WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, eff_addr);
			}
			else {
				WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, bg_addr);
			}
		}
	}
	
	GF_BGL_ScrClear(wk->we_sys->bgl, BATTLE_FRAME_EFFECT);
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e�� [ 16��256���[�h�ϊ� ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Recover(HC_SYS_PTR wk)
{
	switch(wk->sub_seq){
	case 0:
		///< �D��x�؂�ւ�+���A�f�[�^��������
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_3DPriorityGet(wk->we_sys);

			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND, pri2+1);
			
			///< �w�i�X�N���[���t���O�������Ă���ꍇ�ABG����ւ����ɔw�i�X�N���[���ʂ����ւ���				
			if (wk->move_flag == 1){
				BT_HaikeiSubSystemFrameChange(wk->we_sys);
			}

			///< ���X�^�[�t���O�������Ă���ꍇ�ABG����ւ����Ƀ��X�^�[�����ʂ����ւ���
			if (wk->laster_flag == 1){
				if (wk->we_sys->hc_sub_ptr->hls->dlp != NULL){
					int now_addr = WazaTool_GetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp);
					int bg_addr  = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND));
					int eff_addr = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT));
					if (now_addr == bg_addr){
						WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, eff_addr);
					}
					else {
						WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, bg_addr);
					}
				}
			}
		}
		wk->sub_seq++;
		break;
	
	case 1:
		///< �D��x�ύX
		if (wk->move_flag != 1){	
			GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
			GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
		}
	
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_Y_SET, 0);

		HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_EFFECT, wk->bg_id);

		wk->sub_seq++;			
		break;
	
	case 2:
		///< �D��x�؂�ւ�+���f�[�^��������
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND, pri1);
			
			if (WES_ContestFlag_Get(wk->we_sys) == TRUE){
				ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
								  wk->we_sys->haikei_data.chr_id,
					 			  wk->we_sys->bgl,
								  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);

				PaletteWorkSet_Arc(wk->we_sys->pfd,
								   wk->we_sys->haikei_data.arc_index,
								   wk->we_sys->haikei_data.pal_id,
								   wk->we_sys->heap_area, FADE_MAIN_BG,
								   wk->we_sys->haikei_data.pal_num * 0x20,
								   wk->we_sys->haikei_data.pal_start);
			}
			else {
				GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_256);
				WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
				WeSys_BattlePaletteTrans(wk->we_sys);
			}

			ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
							wk->we_sys->haikei_data.scr_id,
							wk->we_sys->bgl,
							BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		}
		wk->sub_seq++;
		break;
	
	default:
		wk->sub_seq = 0;
		return FALSE;
	}					

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e�� [ �w�i�̒�~ ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Stop(HC_SYS_PTR wk)
{
	wk->move_flag = 1;
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��T�u�V�X�e�� [ �T�u�V�X�e���̒�~ ] 
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Exit(HC_SYS_PTR wk)
{
	BT_HaikeiSubSystemStop(wk->we_sys);
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��p��TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiChange_TCB(TCB_PTR tcb, void* work)
{
	HC_SYS_PTR wk = (HC_SYS_PTR)work;
	BOOL active;
	
	active = HaikeiChange_Table[ wk->ch_mode ](tcb, wk);
	
	if (active == FALSE){		
		wk->we_sys->haikei_chg_flag = ENUM_HMODE_NONE;
		
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHG(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int temp;
	
	wk = HaikeiControlInit(we_sys);
	
	wk->fade_type = WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_TYPE);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	temp = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->ch_mode = (temp & 0x0000FFFF);
	wk->ch_sbit = (temp & 0xFFFF0000) >> WEDEF_HAIKEI_SHIFT;
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�p�����[�^�[�ύX
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_PARA_CHG(WE_SYS_PTR we_sys)
{
	int id;
	s16	param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	switch(id){
	case WEDEF_GP_INDEX_SPEED_X:
		we_sys->hc_sub_ptr->speed_x = param;
		break;
	case WEDEF_GP_INDEX_SPEED_Y:
		we_sys->hc_sub_ptr->speed_y = param;
		break;
	case WEDEF_GP_INDEX_BGPOS_X:
		we_sys->hc_sub_ptr->pos_x = param;
		break;
	case WEDEF_GP_INDEX_BGPOS_Y:
		we_sys->hc_sub_ptr->pos_x = param;
		break;
	default:
		break;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i���A
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_RECOVER(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int temp;
	
	wk = HaikeiControlInit(we_sys);
	
	wk->fade_type = WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_TYPE);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	temp = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->ch_mode = (temp & 0x0000FFFF) + WEDEF_HAIKEI_MODE_END;
	wk->ch_sbit = (temp & 0xFFFF0000) >> WEDEF_HAIKEI_SHIFT;
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ����ԑ҂�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_HALF_WAIT(WE_SYS_PTR we_sys)
{
	if (we_sys->haikei_chg_flag == ENUM_HMODE_HALF){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
//		OS_Printf("�w�i�؂�ւ��҂��I���ł�\n");
	}
	else {
		we_sys->waza_eff_wait = 1;
//		OS_Printf("�w�i�؂�ւ��҂��ł�\n");
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�؂�ւ��҂�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHG_WAIT(WE_SYS_PTR we_sys)
{
	if (we_sys->haikei_chg_flag == ENUM_HMODE_NONE){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�w�i�̏u�Ԑ؂�ւ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_SET(WE_SYS_PTR we_sys)
{
	int bg_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ArcUtil_BgCharSet(WE_HAIKEI_ARC,
					  WeSysHaikeiDataIDGet( bg_id, 0),
					  we_sys->bgl,
					  GF_BGL_FRAME3_M,0,0,1,we_sys->heap_area);
	
	ArcUtil_PalSet(WE_HAIKEI_ARC,
				   WeSysHaikeiDataIDGet( bg_id, 1),
				   PALTYPE_MAIN_BG,0,0,we_sys->heap_area);
	
	ArcUtil_ScrnSet(WE_HAIKEI_ARC,
					WeSysHaikeiDataIDGet( bg_id, 2),
					we_sys->bgl,
					GF_BGL_FRAME3_M,0,0,1,we_sys->heap_area);
}


//--------------------------------------------------------------
/**
 * @brief	�V�[�����Ƃ̔w�i�ݒ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHKCHG(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int bg1, bg2, bg3;
	
	wk = HaikeiControlInit(we_sys);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg1 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< ����
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg2 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �G
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg3 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< �R���e�X�g
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->bg_id = bg3;
	}
	else {
		if (WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no) == SIDE_MINE){
			wk->bg_id = bg2;
		}
		else {
			wk->bg_id = bg1;
		}
	}
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}

/// �Ƃ肠��������Ȃ��B
static void WEST_BGPRI_GAPSET(WE_SYS_PTR we_sys)
{
}
static void WEST_BGPRI_GAPSET2(WE_SYS_PTR we_sys)
{
}
static void WEST_BGPRI_GAPSET3(WE_SYS_PTR we_sys)
{
}
static void WEST_PARTY_ATTACK_BGOFF(WE_SYS_PTR we_sys)
{
}
static void WEST_PARTY_ATTACK_BGEND(WE_SYS_PTR we_sys)
{
}

// =========================================
//
//	���T�E���h�֘A
//		[ _COMMAND_SOUND_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	SE���Đ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE(WE_SYS_PTR we_sys)
{
	u16 se_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	se_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SePlay(se_no);
}


//--------------------------------------------------------------
/**
 * @brief	SE�̒�~
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_STOP(WE_SYS_PTR we_sys)
{
	u16 se_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	se_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SeStopBySeqNo(se_no, 0);
}


//--------------------------------------------------------------
/**
 * @brief	�p����ݒ肵��SE��炷
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPLAY_PAN(WE_SYS_PTR we_sys)
{
	u16 se_no;
	int	pan;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan   = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = WeSysSePanGet(we_sys, pan);
	
	Snd_SePlay(se_no);
	Snd_SePanSet(se_no, 0xffff, pan);	
}


//--------------------------------------------------------------
/**
 * @brief	�p���̐ݒ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN(WE_SYS_PTR we_sys)
{
	int pan;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = WeSysSePanGet(we_sys, pan);

	Snd_SePanSetAll(pan);
}


//--------------------------------------------------------------
/**
 * @brief	���Ԋu�Ńp����ύX����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOW(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;

	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = WeSysSePanGet(we_sys, ss->s_pan);
	ss->e_pan = WeSysSePanGet(we_sys, ss->e_pan);

	ss->a_pan = WeSysSePanAddGet(ss->s_pan, ss->e_pan, ss->a_pan);
//	OS_Printf("�J�n�p�� = %4d\n", ss->s_pan);
//	OS_Printf("�I���p�� = %4d\n", ss->e_pan);
//	OS_Printf("���Z�p�� = %4d\n", ss->a_pan);
	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	���Ԋu�Ńp����ύX����(�G�����̈ʒu�֌W�Ȃ�)
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOWFIX(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW_FIX;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	�p���̒l�����Ԋu�ŕύX���Ă���
 *			�p�[�e�B�̂��Ƃ͍l�����Ȃ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOW_AF(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = WeSysSePanGet(we_sys, ss->s_pan);
	ss->e_pan = WeSysSePanGet(we_sys, ss->e_pan);
	ss->a_pan = WeSysSePanGet(we_sys, ss->a_pan);

	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	�w��񐔃��s�[�g����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_REPEAT(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_REPEAT;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->wait = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->repeat = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->gene_wait = ss->wait;
	
	ss->n_pan = WeSysSePanGet(we_sys, ss->n_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	wait���ԑ҂��Ă���Đ�����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_WAITPLAY(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_WAIT_PLAY;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = WeSysSePanGet(we_sys, ss->n_pan);

	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	SE�p��TCB���쐬����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_TASK(WE_SYS_PTR we_sys)
{
}


//--------------------------------------------------------------
/**
 * @brief	�Ȃ�I���܂�wait
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEWAIT_FLAG(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_se_num){
		we_sys->waza_eff_wait = 1;
		we_sys->se_end_timer = 0;
		return;
	}

	if (Snd_SePlayCheckAll()){							///< SE���Đ�����Ă����ꍇ
		we_sys->se_end_timer++;

		if (we_sys->se_end_timer > WE_SE_END_TIMER){	///< �I��3�b�͑҂�
			// �G�t�F�N�g�֘ASE���Ƃ߂�
			;
			;
			we_sys->se_end_timer = 0;
		}
		else {
			we_sys->waza_eff_wait = 1;
			return;
		}
	}
	else {
		we_sys->waza_eff_wait = 0;
		we_sys->se_end_timer = 0;
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


// =========================================
//
//	�����W�X�^����n
//		[ _COMMAND_REG_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	���u�����h���s�Ȃ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_BLDALPHA_SET(WE_SYS_PTR we_sys)
{
	u16 eva;
	u16 evb;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	eva = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	evb = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	G2S_SetBlendAlpha(ENUM_WES_BLD_PLANE_1,
					  ENUM_WES_BLD_PLANE_2, eva, evb);
}


//--------------------------------------------------------------
/**
 * @brief	���u�����h������
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_BLDALPHA_RESET(WE_SYS_PTR we_sys)
{
	DefaultBlendSet();
}


static void WEST_BLDCNT_SET(WE_SYS_PTR we_sys)
{
}

// =============================================================================
//
//
//	���A�N�^�[�֘A
//		[ _COMMAND_CLACT_ ]
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	���\�[�X�V�X�e���̏�����
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_RES_INIT(WE_SYS_PTR we_sys)
{
	int i;
	int res_no;
	int obj_num;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	obj_num = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	GF_ASSERT(we_sys->crp[res_no] == NULL);
	
	we_sys->crp[res_no] = CATS_ResourceCreate(we_sys->btl_sys->csp);
	
	GF_ASSERT(we_sys->crp[res_no] != NULL);
	
	///< ������
	CATS_ClactSetInit(we_sys->btl_sys->csp, we_sys->crp[res_no], obj_num);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(we_sys->btl_sys->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
	
	{
		TCATS_RESOURCE_NUM_LIST crnl;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			crnl.res_num[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		CATS_ResourceManagerInit(we_sys->btl_sys->csp, we_sys->crp[res_no], &crnl);
	}
}


//--------------------------------------------------------------
/**
 * @brief	�L�������\�[�X�ǂݍ���
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CHAR_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCharArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CHAR, arc_id, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, arc_id + EFF_ARC_ID_BASE);
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�g���\�[�X�ǂݍ���
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_PLTT_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	int pal_num;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pal_num = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	

	CATS_LoadResourcePlttWorkArc(we_sys->pfd, FADE_MAIN_OBJ,
								 we_sys->btl_sys->csp, we_sys->crp[res_no],
							 	 ARC_WER_PLTT, arc_id, 0, NNS_G2D_VRAM_TYPE_2DMAIN, pal_num, arc_id + EFF_ARC_ID_BASE);	
}


//--------------------------------------------------------------
/**
 * @brief	�Z�����\�[�X�ǂݍ���
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CELL_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCellArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CELL, arc_id, TRUE, arc_id + EFF_ARC_ID_BASE);	
}


//--------------------------------------------------------------
/**
 * @brief	�Z���A�j�����\�[�X�ǂݍ���
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CELL_ANM_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCellAnmArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CELLANM, arc_id, TRUE, arc_id + EFF_ARC_ID_BASE);		
}


//--------------------------------------------------------------
/**
 * @brief	�A�N�^�[�o�^
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_ACT_ADD(WE_SYS_PTR we_sys)
{
	int i;
	int func_id;
	int res_no;
	int cnt;
	CATS_ACT_PTR cap;
	pWeClactFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	func_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		TCATS_OBJECT_ADD_PARAM_S coap;
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);
		
		coap.x		= GetWazaEffPos(we_sys, defence_client, PM_X);
		coap.y		= GetWazaEffPos(we_sys, defence_client, PM_Y);
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			coap.id[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs) + EFF_ARC_ID_BASE;
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		
		we_sys->coap = coap;
		
		cap  = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->crp[res_no], &coap);
	}
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	for (; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}
	
	func = WazaEffectSupportFuncGet_CATS(func_id);
	
	func(we_sys, we_sys->btl_sys->csp, we_sys->crp[res_no], cap);
}


//--------------------------------------------------------------
/**
 * @brief	�A�N�^�[�̓o�^�̂ݍs�Ȃ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_ACT_ADD_EZ(WE_SYS_PTR we_sys)
{
	int i;
	int res_no;
	int cap_id;
	CATS_ACT_PTR cap;
	pWeClactFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		TCATS_OBJECT_ADD_PARAM_S coap;
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);
		
		coap.x		= GetWazaEffPos(we_sys, defence_client, PM_X);
		coap.y		= GetWazaEffPos(we_sys, defence_client, PM_Y);
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			coap.id[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs) + EFF_ARC_ID_BASE;
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		
		we_sys->coap = coap;
		
		cap  = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->crp[res_no], &coap);
		
		GF_ASSERT(we_sys->cap[ cap_id ] == NULL);
		
		we_sys->cap[ cap_id ] = cap;
	}
}


//--------------------------------------------------------------
/**
 * @brief	���\�[�X�j��
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_RES_FREE(WE_SYS_PTR we_sys)
{
	int res_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->crp[res_no] != NULL){
		CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->crp[res_no]);
	}
	we_sys->crp[res_no] = NULL;
}

static void WEST_POKE_OAM_ENABLE(WE_SYS_PTR we_sys)
{
	int no;
	int flag;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_ObjectEnableCap(we_sys->poke_cap[no], flag);
}

//--------------------------------------------------------------
/**
 * @brief	�f�[�^���`
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 * WeSysExDataGet�֐����g�p���Ē�`���Ă���f�[�^���擾���܂��B
 * C�\�[�XWeSysExDataGet�֐����g�p���A�l�擾�A�A�h���X�ړ�������̂�we_sys.c�̃V�X�e���ォ��
 * ������ʉ߂��鎖�̓G���[�����ɂȂ�܂��B
 *
 * ��)
 * 	FUNC_CALL	WEST_SP_TEST_1, 0, 0
 * 	EX_DATA		3, 100, 200, 150
 * �̂悤�ɂ����ꍇ�AFUNC_CALL�ŌĂяo���ꂽ�֐��̒���WeSysExDataGet�֐��ŉ���EX_DATA���̃f�[�^��
 * �擾���A�h���X��i�߂�K�v������܂��B�����擾���Ȃ������ꍇ�Awe_sys.c����Ă΂�鎖�ɂȂ�A
 * �G���[���������ƂȂ�܂��B
 */
//--------------------------------------------------------------
static void WEST_EX_DATA(WE_SYS_PTR we_sys)
{
	GF_ASSERT((0)&&"EX_DATA�����s����܂���");
}

//--------------------------------------------------------------
/**
 * @brief	�����Đ�
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_VOICE_PLAY(WE_SYS_PTR we_sys)
{
	int type;
	s16 pan;
	int vol;
	int mons_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = (s16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	pan = WeSysSePanGet(we_sys, pan);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	vol = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	mons_no = we_sys->btl_sys->mons_no[ we_sys->btl_sys->at_client_no ];
//	OS_Printf("mons_no = %d we_sys\n", mons_no);

	PokeVoicePlaySet(we_sys->btl_sys->perap_voice, type, mons_no, pan, vol, we_sys->btl_sys->henshin_flag, we_sys->heap_area);

//	Snd_PMVoicePlayEx( type, mons_no, pan, vol, we_sys->heap_area);

}

//--------------------------------------------------------------
/**
 * @brief	�����҂��{��~
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_VOICE_WAIT_STOP(WE_SYS_PTR we_sys)
{
	int frame;
		
	if( Snd_PMVoicePlayCheck() == 0 ){	//�Đ��I�����Ă�����
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		frame = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
		we_sys->waza_eff_wait = 0;
		Snd_PMVoiceStop( frame );
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}

//--------------------------------------------------------------
/**
 * @brief	�w�肳�ꂽ�֐����Ăяo���R�}���h
 *			�A�h���X����Q�Ƃ������
 *			�Ăяo���֐��̃A�h���X
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_OLDACT_FUNC_CALL(WE_SYS_PTR we_sys)
{
#if 0
	int i;
	u32 id;
	u32 ah_no;
	u32 cnt, soft_pri;
	pWeOldActFunc func;
	CLACT_WORK_PTR act;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ah_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	soft_pri = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	func = WazaEffectSupportFuncGet_OLDACT(id);

	cnt  = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}

#if 0	//�A�N�^�[�ύX�̂��߁A�Ƃ肠����FIX
	//�A�N�^�[����
	{
		TCAT_ADD_DATA cad = {
			0,								//�A�N�^�[�w�b�_�[�̒��̓o�^OBJ�̔ԍ� 0����
			128,128,						//x, y
			0, WAZAEFF_ACT_SOFTPRI, 0,		//anm, soft_pri, pal
			NNS_G2D_VRAM_TYPE_2DMAIN,		//d_area
		};
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);

		cad.x = GetWazaEffPos(we_sys, defence_client, PM_X);
		cad.y = GetWazaEffPos(we_sys, defence_client, PM_Y);
		cad.pri = soft_pri;
		
		//���������ݒ肷��K�v���聫������
		//cad.no = 0;
		//cal.palno = 0;
		
		act = CAT_Clact_Add(we_sys->cat_sys[ah_no], &cad);
	}
#endif

	func(we_sys, we_sys->btl_sys->csp, we_sys->crp[ah_no], act);
#endif
}


// =============================================================================
//
//
//	���O���Q��
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�e�[�u������R�}���h���擾����
 *
 * @param	id		�R�}���h�ԍ�
 *
 * @retval	pWeFunc	�R�}���h�֐�
 *
 */
//--------------------------------------------------------------
pWeFunc WazaEffectCommandGet(u32 id)
{
	if (id > EFFECT_CMD_MAX){
		return NULL;
	}
	
	return WazaEffectCmdList[id];
}


//--------------------------------------------------------------
/**
 * @brief	���[�h�`�F�b�N����(�퓬�E�R���e�X�g�E�R���N�[��)
 *
 * @param	btl_sys	
 *
 * @retval	BOOL	
 *
 *
 */
//--------------------------------------------------------------
int WeSysModeGet(BTL_SYS_PTR btl_sys)
{
	return btl_sys->mode;
}


//--------------------------------------------------------------
/**
 * @brief	�p���̏�Ԃ��擾����
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
s8	WeSysSePanGet(WE_SYS_PTR we_sys, s8 pan)
{
	int pan_fix;
	
	pan_fix = pan;
	
	{
		int at = WeSysATNoGet(we_sys);
		int df = WeSysDFNoGet(we_sys);
		int at_side = WET_SideCheck(we_sys, at);
		int df_side = WET_SideCheck(we_sys, df);
	#if 1
			
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			///< A to B
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			pan_fix *= -1;
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_MINE
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			if (pan_fix > 0){
				pan_fix *= -1;
			}
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			if (pan_fix < 0){
				pan_fix *= -1;
			}
			
		}
	#else
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			if (pan < 0){
				pan_fix *= -1;
			}
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			if (pan > 0){
				pan_fix *= -1;
			}			
			
		}
		else {
				
			if (pan > 0){
				pan_fix *= -1;
			}
		}
	#endif
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pan_fix *= -1;
	}
	
//	OS_Printf("pan [ s = %4d ] | [ e = %4d ]\n", pan, pan_fix);
	
	return pan_fix;
}


//--------------------------------------------------------------
/**
 * @brief	�p���̏�Ԃ��擾����@�U���p
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	s8	
 *
 */
//--------------------------------------------------------------
s8 WeSysSePanAttackGet(WE_SYS_PTR we_sys, s8 pan)
{
	int pan_fix;
	
	pan_fix = pan;
	
	{
		int at = WeSysATNoGet(we_sys);
		int df = WeSysDFNoGet(we_sys);
		int at_side = WET_SideCheck(we_sys, at);
		int df_side = WET_SideCheck(we_sys, df);
			
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			pan_fix *= -1;
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_MINE
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			pan_fix *= -1;
			
		}
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pan_fix *= -1;
	}
		
//	OS_Printf("�܂��̃p���̐ݒ� ��� %4d\n", pan);
//	OS_Printf("���݂̃p���̐ݒ� ��� %4d\n", pan_fix);
	
	return pan_fix;
}


//--------------------------------------------------------------
/**
 * @brief	�J�n�`�I�_�ɂ��A�p���̉��Z�l�����߂�
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	s8	
 *
 */
//--------------------------------------------------------------
s8 WeSysSePanAddGet(s8 s_pan, s8 e_pan,  s8 a_pan)
{
	s8 pan;
	
	if (s_pan < e_pan){
		pan = +abs(a_pan);
	}
	else if (s_pan > e_pan){
		pan = -abs(a_pan);
	}
	else {
		pan = 0;
	}
	
	return pan;
}

//--------------------------------------------------------------
/**
 * @brief   EX_DATA�Œ�`���Ă���f�[�^����擾
 *
 * @param   we_sys		
 * @param   data[]		�擾�f�[�^�����(num�Ŏw�肵�����K�v)
 * @param   num			�擾�f�[�^��(EX_DATA�Ɏw�肵�����ƈ�v���Ă���K�v������܂�)
 *
 * @retval  TRUE:�����AFALSE:���s
 */
//--------------------------------------------------------------
BOOL WeSysExDataGet(WE_SYS_PTR we_sys, int data[], int num)
{
	int cnt, i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if(cnt != num){
		GF_ASSERT(cnt == num);
		return FALSE;
	}
	
	for(i = 0; i < num; i++){
		data[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	���O�Őݒ肳��Ă����o�^�p�����[�^�[�̎擾
 *
 * @param	we_sys	
 *
 * @retval	TCATS_OBJECT_ADD_PARAM_S	
 *
 */
//--------------------------------------------------------------
TCATS_OBJECT_ADD_PARAM_S WeSysCoapGet(WE_SYS_PTR we_sys)
{
	return we_sys->coap;
}


//--------------------------------------------------------------
/**
 * @brief	�N���C�A���g�̃^�C�v���擾����
 *
 * @param	we_sys
 * @param	no			�N���C�A���g�ԍ�
 *
 * @retval	int
 *
 */
//--------------------------------------------------------------
int WeSysClientTypeGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->client_type[no];
}



//--------------------------------------------------------------
/**
 * @brief	����
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysSexGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->sex[no];	
}


//--------------------------------------------------------------
/**
 * @brief	�����X�^�[�ԍ�
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysMonsNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->mons_no[no];	
}

//--------------------------------------------------------------
/**
 * @brief	�t�H����No
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysFormNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->form_no[no];	
}

//--------------------------------------------------------------
/**
 * @brief	������
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysPersonalRndGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->personal_rnd[no];	
}

//--------------------------------------------------------------
/**
 * @brief	�\�t�g�X�v���C�g�̃|�C���^�擾
 *
 * @param	we_sys	
 * @param	no			�N���C�A���g�ԍ�
 *
 * @retval	SOFT_SPRITE*	
 *
 */
//--------------------------------------------------------------
SOFT_SPRITE* WeSysSoftSpritePointerGet(WE_SYS_PTR we_sys, int no)
{
	if (we_sys->btl_sys->ss[no] == NULL){
		return NULL;
	}
	
	if(SoftSpriteExistCheck(we_sys->btl_sys->ss[no])){
		return we_sys->btl_sys->ss[no];
	}
	else{
		return NULL;
	}
}


//--------------------------------------------------------------
/**
 * @brief	PFD
 *
 * @param	we_sys	
 *
 * @retval	PALETTE_FADE_PTR	
 *
 */
//--------------------------------------------------------------
PALETTE_FADE_PTR WeSysPFDGet(WE_SYS_PTR we_sys)
{
	return we_sys->pfd;
}


//--------------------------------------------------------------
/**
 * @brief	�p���b�gID�̎擾
 *
 * @param	we_sys	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysPalIDGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->pal_index;
}

int WeSysArcIDGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->arcID;
}

//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃I�t�Z�b�g�擾
 *
 * @param	we_sys	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysPokeOfsGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->height;
}


//--------------------------------------------------------------
/**
 * @brief	2��2�����ׂ�
 *
 * @param	we_sys	
 *
 * @retval	BOOL			TRUE = 2vs2
 *
 */
//--------------------------------------------------------------
BOOL IsWeSysBattleMode2vs2(WE_SYS_PTR we_sys)
{
	u32 bit;
	
	bit = (we_sys->btl_sys->fight_type & FIGHT_TYPE_2vs2);

	return (bit != 0) ? TRUE : FALSE;
}

BOOL BT_WazaKoukaCheck(WE_SYS_PTR we_sys, int client_no)
{
	int para;
	
	para = we_sys->btl_sys->waza_kouka[ client_no ] & WAZAKOUKA_KIE;
	
	return (para != 0) ? TRUE : FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	�J�����̃��[�h���擾
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysCameraTypeGet(int no, WE_SYS_PTR we_sys)
{
	return we_sys->camera_mode[no];
}

//--------------------------------------------------------------
/**
 * @brief	3D�ʂ̃v���C�I���e�B�擾
 *
 * @param	we_sys	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_3DPriorityGet(WE_SYS_PTR we_sys)
{
	int pri;
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pri = ACTIN_3DBG_PRIORITY;
	}
	else {
		pri = BATTLE_3DBG_PRIORITY;
	}
	
	return pri;
}


//--------------------------------------------------------------
/**
 * @brief	BG�̃t���[�����擾����
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGL_FrameGet(WE_SYS_PTR we_sys, int type)
{
	int frame;
	int frm[][3] = {
		{
			BATTLE_FRAME_WINDOW,
			BATTLE_FRAME_EFFECT,
			BATTLE_FRAME_BACKGROUND
		},
		{
			ACTIN_FRAME_WINDOW,
			ACTIN_FRAME_EFFECT,
			ACTIN_FRAME_BACKGROUND
		},
	};
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		frame = frm[ 1 ][ type ];
	}
	else {
		
		frame = frm[ 0 ][ type ];
	}

	return frame;
}


//--------------------------------------------------------------
/**
 * @brief	BGNO�擾
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGL_BGNoGet(WE_SYS_PTR we_sys, int type)
{
	int bgno;
	int no[][3] = {
		{
			BATTLE_BGNO_WINDOW,
			BATTLE_BGNO_EFFECT,
			BATTLE_BGNO_BACKGROUND
		},
		{
			ACTIN_BGNO_WINDOW,
			ACTIN_BGNO_EFFECT,
			ACTIN_BGNO_BACKGROUND
		},
	};
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		bgno = no[ 1 ][ type ];
	}
	else {
		
		bgno = no[ 0 ][ type ];
	}
	
	return bgno;
}


//--------------------------------------------------------------
/**
 * @brief	BG�v���C�I���e�B�擾
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGPriorityGet(WE_SYS_PTR we_sys, int type)
{
	int pri;
	
	switch(type){
	case WES_BF_WINDOW:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_WINDOW;
		}
		else {
			pri = BATTLE_BGPRI_WINDOW;
		}
		break;
		
	case WES_BF_EFFECT:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_EFFECT;
		}
		else {
			pri = BATTLE_BGPRI_EFFECT;
		}
		break;
		
	case WES_BF_BACKGROUND:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_BACKGROUND;
		}
		else {
			pri = BATTLE_BGPRI_BACKGROUND;
		}
		break;
		
	case WES_BF_3DFRAME:
		return BT_3DPriorityGet(we_sys);
	//	return BATTLE_3DBG_PRIORITY;
		break;
	}
	
	return pri;
}


//--------------------------------------------------------------
/**
 * @brief	�J�������[�h�̐ݒ�
 *
 * @param	we_sys	
 * @param	mode	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WE_SYS_CameraModeSet(WE_SYS_PTR we_sys, int mode)
{
#ifdef PM_DEBUG
	g_nDebugCameraType = mode;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	BG��������
 *
 * @param	wsp	
 * @param	frame	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSys_BattleBGDraw(WE_SYS_PTR wsp, int frame)
{
	GF_BGL_LoadCharacter(wsp->bgl, frame, wsp->btl_sys->bg_area, 0x10000, 0);
}

//--------------------------------------------------------------
/**
 * @brief	�p���b�g
 *
 * @param	wsp	
 * @param	frame	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSys_BattlePaletteTrans(WE_SYS_PTR wsp)
{
	PaletteWorkSet(wsp->pfd, wsp->btl_sys->pal_area, FADE_MAIN_BG, 0, 0x200);
}


//--------------------------------------------------------------
/**
 * @brief	�t���b�v�`�F�b�N
 *
 * @param	we_sys	
 * @param	flag	
 *
 * @retval	1BOOL	
 *
 */
//--------------------------------------------------------------
BOOL ContestFlipCheck(WE_SYS_PTR we_sys, int flag)
{
	int client_no;
	
	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	
	
	if (WES_ContestFlag_Get(we_sys) == TRUE
	&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
		
		return TRUE;
		
	}

	return FALSE;
}


// -----------------------------------------
//
//	���w�i�̃f�[�^�e�[�u��
//
// -----------------------------------------
#if 0
static const int WE_HaikeiData_Table[][ 5 ] = {
	{
		EFFECT_BG01_NCGR_BIN,
		EFFECT_BG01_NCLR,
		EFFECT_BG01_NSCR_BIN,
		EFFECT_BG01_NSCR_BIN,		
		EFFECT_BG01_NSCR_BIN,		
	},
	{	
		EFFECT_057_NCGR_BIN,
		EFFECT_057_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057B_NSCR_BIN,	
	},
	{
		EFFECT_059_NCGR_BIN,
		EFFECT_059_NCLR,
		EFFECT_059A_NSCR_BIN,
		EFFECT_059B_NSCR_BIN,
		EFFECT_059B_NSCR_BIN,
	},
	{
		BG_069_EARTH_NCGR_BIN,
		BG_069_EARTH_NCLR,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
	},
	{
		BG_094_PSYCHO1_NCGR_BIN,
		BG_094_PSYCHO_NCLR,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
	},
	{
		BG_090_JIWARE_NCGR_BIN,
		BG_090_JIWARE_NCLR,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE2_NSCR_BIN,
		BG_090_JIWARE2_NSCR_BIN,
	},
	{
		BG_236_MOON_NCGR_BIN,
		BG_236_MOON_NCLR,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
	},
	{
		BG_327_BLUESKY_NCGR_BIN,
		BG_327_BLUESKY_NCLR,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
	},
	{
		BG_322_COSMOS_NCGR_BIN,
		BG_322_COSMOS_NCLR,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
	},
	{
		BG_433_WIREROOM_NCGR_BIN,
		BG_433_WIREROOM_NCLR,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
	},
	{	///< ��イ��������
		BG_434_SHTINGSTAR_NCGR_BIN,
		BG_434_SHTINGSTAR_NCLR,
		BG_434_SHTINGSTAR1_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
	},
	{	///< �{���e�b�J�[
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		/*
		BG_344_VOLTAICER_NCGR_BIN,
		BG_344_VOLTAICER_NCLR,
		BG_344_VOLTAICER_NSCR_BIN,
		BG_344_VOLTAICER_NSCR_BIN,
		BG_344_VOLTAICER_NSCR_BIN,
		*/
	},
	{	///< �C���t�@�C�g
		BG_370_SPEED_NCGR_BIN,
		BG_370_SPEED_NCLR,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
	},
	{	///< �n�[�h�v�����g
		BG_338_GREENLEAF_NCGR_BIN,
		BG_338_GREENLEAF_NCLR,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
	},
	{	///< �ł񂶂ق�
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
	},
	{	///< �������E�����Ȃ�ق̂��E�u���X�g�o�[��
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
	},
	{	///< ��������
		BG_126_DAIMONJI_NCGR_BIN,
		BG_126_DAIMONJI_NCLR,
		BG_126_DAIMONJI1_NSCR_BIN,
		BG_126_DAIMONJI2_NSCR_BIN,
		BG_126_DAIMONJI3_NSCR_BIN,
	},
	{	///< �T�C�N����
		BG_177_CYCLONE_NCGR_BIN,
		BG_177_CYCLONE_NCLR,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,
	},
	{	///< ���΂�
		BG_120_SMALLBANG_NCGR_BIN,
		BG_120_SMALLBANG_NCLR,
		BG_120_SMALLBANG1_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
	},
	{	///< ���K�g���L�b�N
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
	},
	{	///< ���Ă݃^�b�N��
		BG_038_BASHISHI_NCGR_BIN,
		BG_038_BASHISHI_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< �͂�����������
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_063_DEPTHSPD_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
	},
	{	///< ���݂Ȃ�
		BG_087_DARKCLOUD_NCGR_BIN,
		BG_087_DARKCLOUD_NCLR,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,
	},
	{	///< �݂��̂͂ǂ�
		BG_352_SEABED_NCGR_BIN,
		BG_352_SEABED_NCLR,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,
	},
	{	///< ������イ
		EFFECT_057_NCGR_BIN,
		EFFECT_330_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057B_NSCR_BIN,	
	},
	///< 06.06.07
	{	///< �M�K�C���p�N�g
		BG_025_FIREWORKS_NCGR_BIN,
		BG_416_FIREWORKS_Y_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
	},
	{	///< �p���[�E�B�b�v
		BG_038_BASHISHI_NCGR_BIN,
		BG_438_BASHISHI_G_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< �E�b�h�n���}�[
		BG_038_BASHISHI_NCGR_BIN,
		BG_452_BASHISHI_YG_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< �\�[���[�r�[��
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_076_DEPTHSPD_Y_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< �S�b�h�o�[�h
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< �n�C�h���J�m��
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_308_DEPTHSPD_B_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< �u���C�u�o�[�h
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< �������p���`�E�I�[�o�[�q�[�g�E�t���A�h���C�u
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,
	},
	{	///< ������
		BG_171_NIGHTMARE_NCGR_BIN,
		BG_171_NIGHTMARE_NCLR,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
	},
	{	///< �˂�肫
		BG_093_WILLPOWER_NCGR_BIN,
		BG_093_WILLPOWER_NCLR,
		BG_093_WILLPOWER1_NSCR_BIN,
		BG_093_WILLPOWER2_NSCR_BIN,
		BG_093_WILLPOWER3_NSCR_BIN,
	},
	{	///< �����̂ڂ�
		BG_127_WATERFALL_NCGR_BIN,
		BG_127_WATERFALL_NCLR,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
	},
	{	///< �n�C�h���|���v�E�~�X�g�{�[��
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< �n�C�h���|���v�E�~�X�g�{�[��
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< �͂ǂ�����
		BG_056_JUZU_NCGR_BIN,
		BG_396_JUZU_Y_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< ����������
		BG_056_JUZU_NCGR_BIN,
		BG_411_JUZU_R_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< �_�X�g�V���[�g
		BG_056_JUZU_NCGR_BIN,
		BG_441_JUZU_P_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< ���[�t�X�g�[��
		BG_437_LEAFSTORM_NCGR_BIN,
		BG_437_LEAFSTORM_NCLR,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
	},
	{	///< ���񂹂��ق�
		BG_439_SPEED_NCGR_BIN,
		BG_439_SPEED_NCLR,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
	},
	{	///< ����͂̂���
		BG_457_SMALLBANG_NCGR_BIN,
		BG_457_SMALLBANG_NCLR,
		BG_457_SMALLBANG1_NSCR_BIN,
		BG_457_SMALLBANG2_NSCR_BIN,
		BG_457_SMALLBANG3_NSCR_BIN,
	},
	{	///< �o�[�X�g�G�R�[
		BG_460_ECHO_NCGR_BIN,
		BG_460_ECHO_NCLR,
		BG_460_ECHO1_NSCR_BIN,
		BG_460_ECHO2_NSCR_BIN,
		BG_460_ECHO3_NSCR_BIN,
	},
	{	///< �݂��Â��̂܂�
		BG_461_CRESCENT_NCGR_BIN,
		BG_461_CRESCENT_NCLR,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
	},
	{	///< �}�O�}�X�g�[��
		BG_463_MAGMA_NCGR_BIN,
		BG_463_MAGMA_NCLR,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
	},
	{	///< �_�[�N�z�[��
		BG_464_DOWNER_NCGR_BIN,
		BG_464_DOWNER_NCLR,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
	},
	{	///< �V�[�h�t���A
		BG_465_EMISSION_NCGR_BIN,
		BG_465_EMISSION_NCLR,
		BG_465_EMISSION1_NSCR_BIN,
		BG_465_EMISSION2_NSCR_BIN,
		BG_465_EMISSION3_NSCR_BIN,
	},
	{	///< �V���h�[�_�C�u
		BG_467_SPEED_NCGR_BIN,
		BG_467_SPEED_NCLR,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
	},
};
#endif

static const int Haikei_BG_Table[][ 5 ] = {
	{	///< 025
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 223
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 224
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 276
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 354
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 416
		BG_025_FIREWORKS_NCGR_BIN,
		BG_416_FIREWORKS_Y_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 038
		BG_038_BASHISHI_NCGR_BIN,
		BG_038_BASHISHI_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 438
		BG_038_BASHISHI_NCGR_BIN,
		BG_438_BASHISHI_G_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 452
		BG_038_BASHISHI_NCGR_BIN,
		BG_452_BASHISHI_YG_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 056
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 296
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 396
		BG_056_JUZU_NCGR_BIN,
		BG_396_JUZU_Y_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 411
		BG_056_JUZU_NCGR_BIN,
		BG_411_JUZU_R_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 441
		BG_056_JUZU_NCGR_BIN,
		BG_441_JUZU_P_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 063
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_063_DEPTHSPD_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 076
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_076_DEPTHSPD_Y_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 413
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 308
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_308_DEPTHSPD_B_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 143
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 087
		BG_087_DARKCLOUD_NCGR_BIN,
		BG_087_DARKCLOUD_NCLR,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,	
	},
	{	///< 093
		BG_093_WILLPOWER_NCGR_BIN,
		BG_093_WILLPOWER_NCLR,
		BG_093_WILLPOWER1_NSCR_BIN,
		BG_093_WILLPOWER2_NSCR_BIN,
		BG_093_WILLPOWER3_NSCR_BIN,	
	},
	{	///< 120
		BG_120_SMALLBANG_NCGR_BIN,
		BG_120_SMALLBANG_NCLR,
		BG_120_SMALLBANG1_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
		BG_120_SMALLBANG3_NSCR_BIN,	
	},
	{	///< 126
		BG_126_DAIMONJI_NCGR_BIN,
		BG_126_DAIMONJI_NCLR,
		BG_126_DAIMONJI1_NSCR_BIN,
		BG_126_DAIMONJI2_NSCR_BIN,
		BG_126_DAIMONJI3_NSCR_BIN,	
	},
	{	///< 127
		BG_127_WATERFALL_NCGR_BIN,
		BG_127_WATERFALL_NCLR,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,	
	},
	{	///< 171
		BG_171_NIGHTMARE_NCGR_BIN,
		BG_171_NIGHTMARE_NCLR,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,	
	},
	{	///< 177
		BG_177_CYCLONE_NCGR_BIN,
		BG_177_CYCLONE_NCLR,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,	
	},
	{	///< 192
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,	
	},
	{	///< 344
		BG_192_LIGHTNING_NCGR_BIN,
		BG_344_LIGHTNING_BL_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,	
	},
	{	///< 200
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 221
		BG_200_FIRE_NCGR_BIN,
		BG_221_FIRE_O_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 307
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 264
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 315
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 394
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 338
		BG_338_GREENLEAF_NCGR_BIN,
		BG_338_GREENLEAF_NCLR,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,	
	},
	{	///< 352
		BG_352_SEABED_NCGR_BIN,
		BG_352_SEABED_NCLR,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,	
	},
	{	///< 370
		BG_370_SPEED_NCGR_BIN,
		BG_370_SPEED_NCLR,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED3_NSCR_BIN,	
	},
	{	///< 434
		BG_434_SHTINGSTAR_NCGR_BIN,
		BG_434_SHTINGSTAR_NCLR,
		BG_434_SHTINGSTAR1_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,	
	},
	{	///< 437
		BG_437_LEAFSTORM_NCGR_BIN,
		BG_437_LEAFSTORM_NCLR,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,	
	},
	{	///< 439
		BG_439_SPEED_NCGR_BIN,
		BG_439_SPEED_NCLR,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,	
	},
	{	///< 457
		BG_457_SMALLBANG_NCGR_BIN,
		BG_457_SMALLBANG_NCLR,
		BG_457_SMALLBANG1_NSCR_BIN,
		BG_457_SMALLBANG2_NSCR_BIN,
		BG_457_SMALLBANG3_NSCR_BIN,	
	},
	{	///< 460
		BG_460_ECHO_NCGR_BIN,
		BG_460_ECHO_NCLR,
		BG_460_ECHO1_NSCR_BIN,
		BG_460_ECHO2_NSCR_BIN,
		BG_460_ECHO3_NSCR_BIN,	
	},
	{	///< 461
		BG_461_CRESCENT_NCGR_BIN,
		BG_461_CRESCENT_NCLR,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,	
	},
	{	///< 463
		BG_463_MAGMA_NCGR_BIN,
		BG_463_MAGMA_NCLR,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,	
	},
	{	///< 464
		BG_464_DOWNER_NCGR_BIN,
		BG_464_DOWNER_NCLR,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,	
	},
	{	///< 465
		BG_465_EMISSION_NCGR_BIN,
		BG_465_EMISSION_NCLR,
		BG_465_EMISSION1_NSCR_BIN,
		BG_465_EMISSION2_NSCR_BIN,
		BG_465_EMISSION3_NSCR_BIN,	
	},
	{	///< 467
		BG_467_SPEED_NCGR_BIN,
		BG_467_SPEED_NCLR,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,	
	},
	{	///< 097
		EFFECT_BG01_NCGR_BIN,
		EFFECT_BG01_NCLR,
		EFFECT_BG01_NSCR_BIN,
		EFFECT_BG01_NSCR_BIN,		
		EFFECT_BG01_NSCR_BIN,		
	},
	{	///< 057
		EFFECT_057_NCGR_BIN,
		EFFECT_057_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057A_NSCR_BIN,	
	},
	{	///< 330
		EFFECT_057_NCGR_BIN,
		EFFECT_330_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057A_NSCR_BIN,	
	},
	{	///< 059
		EFFECT_059_NCGR_BIN,
		EFFECT_059_NCLR,
		EFFECT_059B_NSCR_BIN,	/// r
		EFFECT_059A_NSCR_BIN,
		EFFECT_059A_NSCR_BIN,
	},
	{	///< 069
		BG_069_EARTH_NCGR_BIN,
		BG_069_EARTH_NCLR,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
	},
	{	///< 094
		BG_094_PSYCHO1_NCGR_BIN,
		BG_094_PSYCHO_NCLR,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
	},
	{	///< 090
		BG_090_JIWARE_NCGR_BIN,
		BG_090_JIWARE_NCLR,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE1_NSCR_BIN,
	},
	{	///< 236
		BG_236_MOON_NCGR_BIN,
		BG_236_MOON_NCLR,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
	},
	{	///< 327
		BG_327_BLUESKY_NCGR_BIN,
		BG_327_BLUESKY_NCLR,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
	},
	{	///< 322
		BG_322_COSMOS_NCGR_BIN,
		BG_322_COSMOS_NCLR,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
	},
	{	///< 433
		BG_433_WIREROOM_NCGR_BIN,
		BG_433_WIREROOM_NCLR,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
	},
};

//--------------------------------------------------------------
/**
 * @brief	�w�i�f�[�^�̎擾
 *
 * @param	id	
 * @param	no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysHaikeiDataIDGet(int id, int no)
{
#if 1

	return Haikei_BG_Table[ id ][ no ];

#else

	return WE_HaikeiData_Table[ id ][ no ];

#endif
}


// =============================================================================
//
//
//	��
//
//
// =============================================================================
OAM_DROP_SYS* OAM_Drop_Init(BATTLE_WORK* bw, int heap, int client_no)
{
	int i;
	int pri_tbl[] = { 0, 0, 20, 10, 10, 20 };
	OAM_DROP_SYS* wk;
	
	wk = sys_AllocMemory(heap, sizeof(OAM_DROP_SYS));
	
	wk->heap	  = heap;
	wk->client_no = client_no;
	
	wk->sys.csp = BattleWorkCATS_SYS_PTRGet(bw);
	wk->sys.crp = BattleWorkCATS_RES_PTRGet(bw);
	wk->sys.pfd = BattleWorkPfdGet(bw);
	
	{		
		for(i = 0; i < CLIENT_MAX; i++){
			wk->cap[i]  = NULL;
			wk->excp[i] = BattleWorkExChrClientParamGet(bw, i);	///< �L�����o�b�t�@
		}
		BattleClientTypeBufMake(bw, &(wk->client_type[0]));		///< �N���C�A���gType
		BattleSoftSpriteBufMake(bw, &(wk->ss[0]));				///< �\�t�g�X�v���C�g
	}
	
	{
		int res_id[ 6 ];
			
		for (i = 0; i < CLIENT_MAX; i++){
			
			if (i != wk->client_no
			&&	wk->client_no != OAM_DROP_ALL){ continue; }
			
			///< ����
			res_id[ 0 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 1 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 2 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 3 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 4 ] = 0;
			res_id[ 5 ] = 0;
			
		//	OS_Printf("pal id = %6d\n", res_id[ 1 ]);
				
			CATS_LoadResourceCharArc(wk->sys.csp, wk->sys.crp,
									 ARC_BATT_OBJ, PO_CHAR_ID, 0,
									 NNS_G2D_VRAM_TYPE_2DMAIN, res_id[0]);

			CATS_LoadResourcePlttWorkArc(wk->sys.pfd, FADE_MAIN_OBJ,
										 wk->sys.csp, wk->sys.crp,
										 ARC_BATT_OBJ, PO_PLTT_ID, 0,
										 NNS_G2D_VRAM_TYPE_2DMAIN, 1, res_id[1]);

			CATS_LoadResourceCellArc(wk->sys.csp, wk->sys.crp,
									 ARC_BATT_OBJ, PO_CELL_ID, 0, res_id[2]);

			CATS_LoadResourceCellAnmArc(wk->sys.csp, wk->sys.crp,
									 	ARC_BATT_OBJ, PO_CELLANM_ID, 0, res_id[3]);
		}		
	}
	
	
	{
		
		int i;
		int arcID;
		int palID;
		void* oam_temp;
		int res_id[ 6 ];
		CATS_ACT_PTR cap;
		
		for (i = 0; i < CLIENT_MAX; i++){
			
			if (i != wk->client_no
			&&	wk->client_no != OAM_DROP_ALL){ continue; }
			
			///< ����
			wk->res_id[ i ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 0 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 1 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 2 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 3 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 4 ] = 0;
			res_id[ 5 ] = 0;
			
			arcID	 = wk->excp[ i ]->arcID;
			palID	 = wk->excp[ i ]->pal_index;
			oam_temp = wk->excp[ i ]->exchr_buffer;
			
			///< �o�^
			{
				int n;
				TCATS_OBJECT_ADD_PARAM_S coap;
				SOFT_SPRITE*			 ssp;
				s16 px,py;
				
				ssp = wk->ss[ i ];
				
				if (ssp != NULL){
					
					px = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
					py = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);					
					py -= SoftSpriteParaGet(ssp, SS_PARA_SHADOW_HEIGHT);
					
				}
				else {
					continue;
				}
					
					
				coap.x		= px;
				coap.y		= py;
				coap.z		= 0;		
				coap.anm	= 0;
				coap.pri	= pri_tbl[ wk->client_type[i] ];
				coap.pal	= 0;
				coap.d_area = CATS_D_AREA_MAIN;
				coap.bg_pri = WAZAEFF_ACT_BGPRI;
				coap.vram_trans = 0;
				
					
				for (n = 0; n < 6; n++){
					coap.id[ n ] = res_id[ n ];
				}
				cap = CATS_ObjectAdd_S(wk->sys.csp, wk->sys.crp, &coap);
				CATS_ObjectUpdateCap(cap);
				wk->cap[i] = cap;

				if (ssp == NULL){
					CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
				}
				else if (SoftSpriteExistCheck(ssp) == FALSE){
					CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
				}
				else {
					int vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
					
					if (vf == 1){
						CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
					}
				}
				
				if (ssp != NULL)
				{
					///< �_�~�[�L�����ɐ����L������]�����Ȃ���
					NNSG2dImageProxy * image;
					
					image = CLACT_ImageProxyGet(cap->act);
							
					AddVramTransferManager(
						NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
						image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
						oam_temp,
						POKE_TEX_SIZE);
				}
				
				if (ssp != NULL)
				{
					///< �_�~�[�p���b�g�ɐ����ȃp���b�g��]�����Ȃ���
					NNSG2dImagePaletteProxy* palette;
					int pal_no;
					
					palette = CLACT_PaletteProxyGet(cap->act);
					
					pal_no = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
					
					PaletteWorkSet_Arc(wk->sys.pfd, arcID, palID, wk->heap, FADE_MAIN_OBJ, 0x20, pal_no*16);
				}
			}
		}
	}
	
	return wk;
}


OAM_DROP_SYS* OAM_DropAll_Init(BATTLE_WORK* bw, int heap)
{
	OAM_DROP_SYS* wk;
	
	wk	= OAM_Drop_Init(bw, heap, OAM_DROP_ALL);
	
	return wk;
}


void OAM_DropAll_End(OAM_DROP_SYS* ods)
{
	int i;
	
	for (i = 0; i < 4; i++){
		
		if (ods->cap[i] == NULL){ continue; }
		
		CATS_FreeResourceChar(ods->sys.crp, ods->res_id[i]);
		CATS_FreeResourcePltt(ods->sys.crp, ods->res_id[i]);
		CATS_ActorPointerDelete_S(ods->cap[i]);
	}
	
	sys_FreeMemoryEz(ods);
}

void OAM_Drop_End(OAM_DROP_SYS* ods, int client_no)
{
	int i;
	
	for (i = 0; i < 4; i++){
		
		if (i != client_no){ continue; }
		
		if (ods->cap[i] == NULL){ continue; }
		
		CATS_FreeResourceChar(ods->sys.crp, ods->res_id[i]);
		CATS_FreeResourcePltt(ods->sys.crp, ods->res_id[i]);
		CATS_ActorPointerDelete_S(ods->cap[i]);
	}
	
	sys_FreeMemoryEz(ods);
}

//--------------------------------------------------------------
/**
 * @brief	ods���Ǘ�����N���C�A���g�i���o�[�̃A�N�^�[���擾
 *
 * @param	ods	
 * @param	client_no	
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR OAM_Drop_CapGet(OAM_DROP_SYS* ods, int client_no)
{
	GF_ASSERT(ods != NULL);
	
	return ods->cap[ client_no ];
}

int OAM_Drop_ClientTypeGet(OAM_DROP_SYS* ods)
{
	GF_ASSERT(ods != NULL);
	
	return ods->client_type[ ods->client_no ];	
}

