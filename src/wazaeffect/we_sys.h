//==============================================================================
/**
 * @file	we_sys.h
 * @brief	�Z�G�t�F�N�g�p�V�X�e��
 * @author	goto
 * @date	2005.06.22(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	_WE_SYS_H_
#define _WE_SYS_H_

#include "wazaeffect/we_mana.h"
#include "system/particle.h"
#include "include/battle/bc_common.h"

// =============================================================================
//
//
//	�������p
//	
//		[ _WE-SYS_ ]		WE-SYS
//		[ _EXPLANATION_ ]	WE-SYS�̐���
//		[ _COMMAND_ ]		�R�}���h
//
//
// =============================================================================

// -----------------------------------------
//
//	�������ǔ��p
//
// -----------------------------------------
typedef struct _TAMO_SYS * AMO_SYS_PTR;		///< �����ǔ��p�\����
typedef struct _TAMB_SYS * AMB_SYS_PTR;


// -----------------------------------------
//
//	�f�o�b�O
//
// -----------------------------------------
//#define WE_SYS_CMD_OS_PRINT				///< �L�� = �R�}���h����Print
//#define WE_SYS_INF_OS_PRINT				///< �L�� = ����Print

// -----------------------------------------
//
//	�Z�G�t�F�N�g�p�֐��|�C���^�^
//
// -----------------------------------------
typedef void (*pWeFunc)(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	�Z�G�t�F�N�g�p �Z���A�N�^�[�T�|�[�g�֐�
//
// -----------------------------------------
typedef void (*pWeClactFunc)(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);


// -----------------------------------------
//
//	���Z�G�t�F�N�g�p �A�N�^�[�o�^�֐�
//
// -----------------------------------------
typedef void (*pWeOldActFunc)(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CLACT_WORK_PTR act);


// -----------------------------------------
//
//	�A�h���X�p�����[�^�^
//
// -----------------------------------------
typedef int	TAP;

extern void DefaultBlendSet(void);

// =========================================
//
//
//	��DEFINE
//
//
// =========================================

#define WE_JUMP_MAX			(3)				///< �W�����v���߂����q�ɂ����ۂ̍ő吔
#define WE_LOOP_MAX			(3)				///< ���[�v���߂����q�ɂ����ۂ̍ő吔
#define WE_GENE_WK_MAX		(8 + 2)			///< �ėp���[�N /// 060515 �v�����Ȃ��g��
#define WE_SE_WK_MAX		(7)				///< SE�p�̃��[�N��
#define WE_SE_END_TIMER		(90)			///< 3�b�ԑ҂�
#define WE_CRP_MAX			(4)				///< CRP�̍ő吔
#define WE_CAP_MAX			(10)			///< CAP�̕ۑ���
#define WE_POKE_CAP_MAX		(4 + 1)			///< �|�P������OAM�Ƀh���b�v�ł��鐔 5�Ԗڂ͎g�p�֎~

#define WE_HAIKEI_ARC		(ARC_BATT_BG)	///< �w�i�̃A�[�J�C�u����Ă�ID

#define PARTICLE_EMIT_MAX	(20)			///< �p�[�e�B�N���̃G�~�b�^�[�̐�

#define PARTICLE_VBLANK_LOAD
#define PARTICLE_VBLANK_LOAD_WAIT	(2)

// =========================================
//
//
//	��ENUM
//
//
// =========================================
// -----------------------------------------
//
//	���T�E���h�R���g���[��
//
// -----------------------------------------
enum ESE_SYS_MODE {

	ENUM_SEC_NON 		= 0,				///< ����Ȃ�
	ENUM_SEC_PAN_FLOW,						///< �p��-�ʒu�֌W�l��
	ENUM_SEC_PAN_FLOW_FIX,					///< �p��-PT����
	ENUM_SEC_PAN_FLOW_AF,					///< �p��-�U�����l��
	
	ENUM_SEC_REPEAT,						///< ���s�[�g
	
	ENUM_SEC_WAIT_PLAY,						///< wait���ԑ҂��Ă���Đ�

};

// -----------------------------------------
//
//	��TCB�o�^���[�h
//
// -----------------------------------------
enum ETCB_MODE {

	ENUM_WETCB_NONE		= 0,				///< ���ɂȂ�
	ENUM_WETCB_EFFECT,						///< �G�t�F�N�g�p
	ENUM_WETCB_SOUND,						///< �T�E���h�p

};

// -----------------------------------------
//
//	�����̑��̒�`
//
// -----------------------------------------
enum EWES_DEFINE {
	
	///< ���u�����h�Ώۃv���[��
	ENUM_WES_BLD_PLANE_1 = GX_BLEND_PLANEMASK_BG0,
	ENUM_WES_BLD_PLANE_2 = GX_BLEND_PLANEMASK_BG1,
	
};

// =========================================
//
//
//	���O���Q�ƁFWE-SYS�T�|�[�g
//
//
// =========================================

// -----------------------------------------
//
// WE-SYS��p �G�t�F�N�g�pTCB_Add
//
// -----------------------------------------
extern TCB_PTR WEEffect_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
extern TCB_PTR WEEffect_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work);


// -----------------------------------------
//
// WE-SYS��p �T�E���h�pTCB_Add
//
// -----------------------------------------
extern TCB_PTR WESound_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
extern TCB_PTR WESound_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work);


// -----------------------------------------
//
// WE-SYS��p �G�t�F�N�g�pTCB_Delete
//
// -----------------------------------------
extern void WEEffect_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb);


// -----------------------------------------
//
// WE-SYS��p �T�E���h�pTCB_Delete
//
// -----------------------------------------
extern void WESound_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb);


// =========================================
//
//
//	���O���Q�ƁF�R�}���h [ _COMMAND_ ]
//
//
// =========================================
// -----------------------------------------
//
// �R�}���h�̎擾
//
// -----------------------------------------
extern pWeFunc WazaEffectCommandGet(u32 id);


// -----------------------------------------
//
// �R���e�X�g�Ȃ̂��`�F�b�N����
//
// -----------------------------------------
extern int WeSysModeGet(BTL_SYS_PTR blt_sys);


// -----------------------------------------
//
//	�p���̏�Ԃ��擾����
//
// -----------------------------------------
extern s8 WeSysSePanGet(WE_SYS_PTR we_sys, s8 pan);


// -----------------------------------------
//
//	�p���̏�Ԃ��擾����@�U���p
//
// -----------------------------------------
extern s8 WeSysSePanAttackGet(WE_SYS_PTR we_sys, s8 pan);


// -----------------------------------------
//
//	�J�n�`�I�_�ɂ��A�p���̉��Z�l�����߂�
//
// -----------------------------------------
extern s8 WeSysSePanAddGet(s8 s_pan, s8 e_pan,  s8 a_pan);


// -----------------------------------------
//
//	WE-SYS�̃����o�A�N�Z�X�֐� ��{�I��Get�̂�
//
// -----------------------------------------
extern int				WeSysHeapAreaGet(WE_SYS_PTR we_sys);
extern u16				WeSysATNoGet(WE_SYS_PTR we_sys);
extern u16				WeSysDFNoGet(WE_SYS_PTR we_sys);
extern PTC_PTR			WeSysPTCPointerGet(WE_SYS_PTR we_sys);
extern PTC_PTR			WeSysPTCPointerNoGet(WE_SYS_PTR we_sys, int no);
extern EMIT_PTR			WeSysEMITPointerGet(WE_SYS_PTR we_sys, int no);
extern GF_BGL_INI*		WeSysBGLPointerGet(WE_SYS_PTR we_sys);
extern s32				WeSysGPWorkGet(WE_SYS_PTR we_sys, int no);
extern BOOL				WeSysExDataGet(WE_SYS_PTR we_sys, int data[], int num);
extern TCATS_OBJECT_ADD_PARAM_S WeSysCoapGet(WE_SYS_PTR we_sys);

extern CATS_ACT_PTR		WeSysOamCapGet(WE_SYS_PTR we_sys, int no);
extern CATS_ACT_PTR		WeSysPokeCapGet(WE_SYS_PTR we_sys, int no);
extern CATS_RES_PTR		WeSysPokeCrpGet(WE_SYS_PTR we_sys);
extern CATS_RES_PTR		WeSysCrpGet(WE_SYS_PTR we_sys);
extern CATS_SYS_PTR		WeSysCspGet(WE_SYS_PTR we_sys);

extern int				WeSysClientTypeGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysSexGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysMonsNoGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysFormNoGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysPersonalRndGet(WE_SYS_PTR we_sys, int no);
extern SOFT_SPRITE*		WeSysSoftSpritePointerGet(WE_SYS_PTR we_sys, int no);
extern void				WeSysAutoMoveStop(WE_SYS_PTR we_sys, int stop_tr);
extern PALETTE_FADE_PTR WeSysPFDGet(WE_SYS_PTR we_sys);
extern int				WeSysPalIDGet(WE_SYS_PTR we_sys, int client_no);
extern int				WeSysArcIDGet(WE_SYS_PTR we_sys, int client_no);
extern int				WeSysPokeOfsGet(WE_SYS_PTR we_sys, int client_no);

extern int				WeSysHaikeiDataIDGet(int id, int no);
extern void				WeSysBaseBGSet(WE_SYS_PTR wsp, int frm);				///< ��{�w�i��ݒ肷��
extern void				WeSysBaseBGReset(WE_SYS_PTR wsp, int frm);				///< ��{�w�i��ݒ肷��

extern BOOL				IsWeSysBattleMode2vs2(WE_SYS_PTR we_sys);
extern void				WeSys_BattleBGDraw(WE_SYS_PTR wsp, int frame);
extern void				WeSys_BattlePaletteTrans(WE_SYS_PTR wsp);

// �퓬�̒�`�擾�֐� (�R���e�X�g�`�F�b�N����)
#define	WES_BF_WINDOW		(0)
#define	WES_BF_EFFECT		(1)
#define	WES_BF_BACKGROUND	(2)
#define	WES_BF_3DFRAME		(3)

extern int				BT_3DPriorityGet(WE_SYS_PTR we_sys);
extern int				BT_BGL_FrameGet(WE_SYS_PTR we_sys, int type);
extern int				BT_BGL_BGNoGet(WE_SYS_PTR we_sys, int type);
extern int				BT_BGPriorityGet(WE_SYS_PTR we_sys, int type);

///< �퓬�f�[�^����G�t�F�N�g�̉e�����y�ڂ�����
enum {
	WE_PARA_DAMAGE = 0,		///< �_���[�W
	WE_PARA_POW,			///< �З�
	WE_PARA_NATUKI,			///< �Ȃ�
	WE_PARA_WEATHER,		///< �V��
	WE_PARA_TURN,			///< �^�[���� waza_eff_cnt
	WE_PARA_GROUND_ID,		///< �n�`�f�[�^
};

extern int WazaEffParaGet(WE_SYS_PTR we_sys, int para_id);


extern void WeSys_PokeChangeParamMake(WE_SYS_PTR we_sys, WAZA_POKE_CHANGE_PARAM* para, int type);
extern void	HenshinChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);
extern void	HenshinChrPop(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);

extern BOOL ContestFlipCheck(WE_SYS_PTR we_sys, int flag);	///< flag == WEDEF_DROP_M1 E1 M2 E2

extern BOOL BT_WazaKoukaCheck(WE_SYS_PTR we_sys, int client_no);

/// �T�u

extern void	BT_HaikeiSubSystemStop(WE_SYS_PTR we_sys);
extern void	BT_HaikeiSubSystemFrameChange(WE_SYS_PTR we_sys);
extern int	BT_HaikeiFadeBit(WE_SYS_PTR we_sys);

/// �J����
extern int	WeSysCameraTypeGet(int no, WE_SYS_PTR we_sys);

/// ��Ƀf�o�b�O�Ŏg��
extern void WE_SYS_CameraModeSet(WE_SYS_PTR we_sys, int mode);

// =============================================================================
//
//
//	��OAM���Ƃ��@�퓬�V�X�e������
//
//
// =============================================================================
#define OAM_DROP_ALL	(0xFF)
typedef struct {

	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	PALETTE_FADE_PTR	pfd;
	
} OAM_DROP_PARAM;

typedef struct {
	
	int heap;
	int client_no;
	
	OAM_DROP_PARAM	sys;
	
	int				res_id[ CLIENT_MAX ];
	CATS_ACT_PTR	cap[ CLIENT_MAX ];			///< CAP
	EXCHR_PARAM*	excp[ CLIENT_MAX ];			///< �L�����o�b�t�@
	u8 			 	client_type[ CLIENT_MAX ];	///< �N���C�A���gType
	SOFT_SPRITE*	ss[ CLIENT_MAX ];			///< �\�t�g�X�v���C�g
	
} OAM_DROP_SYS;

extern OAM_DROP_SYS* OAM_Drop_Init(BATTLE_WORK* bw, int heap, int client_no);
extern OAM_DROP_SYS* OAM_DropAll_Init(BATTLE_WORK* bw, int heap);
extern void			 OAM_Drop_End(OAM_DROP_SYS* ods, int client_no);
extern void			 OAM_DropAll_End(OAM_DROP_SYS* ods);
extern CATS_ACT_PTR	 OAM_Drop_CapGet(OAM_DROP_SYS* ods, int client_no);
extern int 			 OAM_Drop_ClientTypeGet(OAM_DROP_SYS* ods);

// =============================================================================
//
//
//	��WE-SYS ���� [ _EXPLANATION_ ]
//
//
// =============================================================================
/* ----- explanation -----

	��WE-SYS�ł̃^�X�N�o�^
	
	01.�͂��߂�
		�^�X�N��o�^����R�}���h�̔p�~�A�֐��Ăяo�����g���ē�����TCB_Add
		TCB�̓��[�N�������Ƃ��Ă���̂ŁA
		�R�}���h���Ń��[�N��p�ӂ���̂͂ǁ[���Ǝv���āB
	
	02.���p���@
		�G�t�F�N�g�A�T�E���h�Ɋւ��Ă͓Ǝ���TCB_Add�𗘗p���邱��
		�֐��Ăяo���̒��ŁA�T�E���h�A�G�t�F�N�g�Ɋւ���TCB���쐬����ꍇ��
		��p�֐��œo�^�E�J�����s���܂��B
		����ȊO�̃^�X�N�Ɋւ��ẮA�K��͂���܂���
		�֐��Ăяo���Ŏg�p�����֐��̌^�͌��܂��Ă��܂�
		
		�Etypedef void (*pWeFunc)(WE_SYS_PTR we_sys);
	
	03.���ӓ_
		WE_SYS_PTR�̃��[�N�́A�o�^����TCB���ł͊J�����Ȃ����I
		�����̊֐��Ăяo���ł���L�̌^�̊֐����w�肵�Ă��������B(TCB_Add���邾���ł�)
	
	���g����
	��)
	
	�ǉ�����TCB�̃��[�N		--	typedef struct { 
									WE_SYS_PTR ws;		///< �K�{
									int attack;
									int	count;
								} TSAMPLE_WORK;
									
	�ǉ�������TCB			--	void SampleTCB(TCB_PTR, void* work);
	�R�}���h�ŌĂяo���֐�	--	void SampleTCBCall(WE_SYS_PTR we_sys);
	
	// ------------------------------------------------------------
	//
	//	�Ăяo���p	(�R�}���h�̈����ɂ���֐��ł�)
	//
	// ------------------------------------------------------------
	void SampleTCBCallSampleTCBCall(WE_SYS_PTR we_sys){
		
		SAMPLE_WORK* wk;
		
		wk = sys_AllocMemory(���);
		
		///< �R�R����p�r�ɂ���ĕς��܂�
		
		///< 01.�Z�p��TCB�o�^
		wk->ws = we_sys;								///< �R�R�Ń|�C���^�n���Ă�������
		WEEffect_TCB_Add(wk->ws, SampleTCB, wk, 0x1000);

		///< 02.�T�E���h�p��TCB�o�^
		wk->ws = we_sys;								///< �R�R�Ń|�C���^�n���Ă�������
		WESound_TCB_Add(wk->ws, SampleTCB, wk, 0x1000);

		///< 03.������TCB�o�^
		TCB_Add(SampleTCB, wk, 0x1000);					///< ���ʂɎg���Ă�������
	}
	
	// ------------------------------------------------------------
	//
	//	����TCB
	//
	// ------------------------------------------------------------	
	void SampleTCB(TCB_PTR tcb, void* work){
		
		TSAMPLE_WORK* wk = (TSAMPLE_WORK*)work;
		
		///< �폜���@���o�^���@�ɂ���ĈقȂ�܂�
		
		///< 01.�Z�p��TCB�j��
		WEEffect_TCB_Delete(wk->ws, tcb);
		
		///< 02.�T�E���h�p��TCB�j��
		WESound_TCB_Delete(wk->ws, tcb);
		
		///< 03.������TCB�j��
		TCB_Delete(tcb);
		
		///< WE_SYS_PTR �̊J���͍s��Ȃ�����
		sys_FreeMemory(wk);
	}

----- explanation -----	*/

#endif


