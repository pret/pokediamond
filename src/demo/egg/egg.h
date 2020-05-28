//==============================================================================
/**
 * @file	egg.c
 * @brief	���܂��f��
 * @author	goto
 * @date	2006.05.20(�y)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	__EGG_H__
#define __EGG_H__

#include "common.h"
#include "field/field_common.h"

#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"
#include "system/touch_subwindow.h"

#include "system\font_arc.h"
#include "system\particle.h"

#include "include/application/namein.h"
#include "include/system/softsprite.h"


// -----------------------------------------
//
//	�� public
//
// -----------------------------------------
extern const PROC_DATA EGG_ProcData;

// =============================================================================
//
//
//	����`�Ƃ�
//
//
// =============================================================================

#define EGG_DEMO_HEAP_SIZE				(0x40000)
#define EGG_DEMO_VRAM_TRANSFER_TASK_NUM	(BATTLE_VRAM_TRANSFER_TASK_NUM)

///< EGG_Demo_Main �p�V�[�P���X
enum EEGG_Demo_Main {
	EDMS_INIT	= 0,		///< ������
	EDMS_MAIN,				///< ���C��
	EDMS_NAME_IN_INIT,		///< ���O
	EDMS_NAME_IN_MAIN,		///< ���͑҂�
	EDMS_NAME_IN_EXIT,		///< ���O���͊���
	EDMS_EXIT,				///< �I��
	EDMS_FREE,				///< ���
};

///< window ID
enum {
	EDWIN_MESSAGE = 0,		///< ���b�Z�[�W
	EDWIN_SELECT,			///< �͂��E������
	
	EDWIN_MAX,
};

///< palette ID
enum {
	
	///< main
	EDPAL_BG = 0,
	
	EDPAL_FRAME = 12,
	EDPAL_MENU,
	EDPAL_FONT,
	EDPAL_BACK,
	
	///< sub
	
	EDPAL_SUB_BG = 0,
	
};

///< id
enum {
	EDID_EGG_NCGR = 20000,
	EDID_EGG_NCLR,
	EDID_EGG_NCER,
	EDID_EGG_NANR,
	
	EDID_WND_NCGR = 25000,
	EDID_WND_NCLR,
	EDID_WND_NCER,
	EDID_WND_NANR,
};

///< �V�[�P���X
enum EGG_MAIN_DEMO {
	
	EMD_SEQ_INIT = 0,
	EMD_SEQ_FADE_IN,
	EMD_SEQ_FADE_IN_WAIT,
	
	EMD_SEQ_DEMO_1,
	EMD_SEQ_DEMO_2,
	EMD_SEQ_DEMO_3,
	EMD_SEQ_DEMO_4,
	EMD_SEQ_DEMO_5,
	EMD_SEQ_DEMO_MSG_1,			///< �z����������
	EMD_SEQ_DEMO_MSG_2,
	EMD_SEQ_DEMO_MSG_2_2,
	EMD_SEQ_DEMO_MSG_3,
	EMD_SEQ_DEMO_SEL_1,			///< �͂��E������
	EMD_SEQ_DEMO_SEL_2,
	EMD_SEQ_DEMO_SEL_3,
	
	EMD_SEQ_FADE_OUT,
	EMD_SEQ_FADE_OUT_WAIT,
	EMD_SEQ_END,
};

///< ���[�h
enum {
	EDM_MODE_NORMAL = 0,
	EDM_MODE_SPECIAL,
};

#define EGG_DEMO_NEAR			(FX32_ONE)			///< �J����
#define EGG_DEMO_FAR			(FX32_ONE * 900)

#define EGG_DEMO_CHAR_OFS		(20)				///< �C�x��

#define EGG_DEMO_TALK_CHAR_OFS	(EGG_DEMO_CHAR_OFS)
#define EGG_DEMO_MENU_CHAR_OFS	(EGG_DEMO_TALK_CHAR_OFS + TALK_WIN_CGX_SIZ)
#define EGG_DEMO_WIN_CHAR_OFS	(EGG_DEMO_MENU_CHAR_OFS + MENU_WIN_CGX_SIZ)

#define EGG_DEMO_TALK_WIN_S		(EGG_DEMO_WIN_CHAR_OFS)
#define EGG_DEMO_TALK_WIN_X		(2)
#define EGG_DEMO_TALK_WIN_Y		(19)
#define EGG_DEMO_TALK_WIN_W		(27)
#define EGG_DEMO_TALK_WIN_H		(4)
#define EGG_DEMO_TALK_WIN_SIZ	(EGG_DEMO_TALK_WIN_S + (EGG_DEMO_TALK_WIN_W * EGG_DEMO_TALK_WIN_H))

#define EGG_DEMO_YN_WIN_S		(EGG_DEMO_TALK_WIN_SIZ)
#define EGG_DEMO_YN_WIN_X		(25)
#define EGG_DEMO_YN_WIN_Y		(13)
#define EGG_DEMO_YN_WIN_W		(6)
#define EGG_DEMO_YN_WIN_H		(4)
#define EGG_DEMO_YN_WIN_SIZ		(EGG_DEMO_YN_WIN_S + (EGG_DEMO_YN_WIN_W * EGG_DEMO_YN_WIN_H))

#define EGG_DEMO_PT_WAIT_0		(25)
#define EGG_DEMO_PT_WAIT_1		(10)
#define EGG_DEMO_PT_WAIT_2		(1)
#define EGG_DEMO_SP_PT_WAIT_0	(160)

enum {
	
	EGG_MOVE_SHAKE_1 = 0,
	EGG_MOVE_SHAKE_2 = 1,
	EGG_MOVE_SHAKE_3 = 2,
	EGG_MOVE_SHAKE_4 = 3,
	EGG_MOVE_SHAKE_5 = 4,
	
};

// =============================================================================
//
//
//	���\���̂Ƃ�
//
//
// =============================================================================
// -----------------------------------------
//
//	���v���b�N�R�[���p�����[�^
//
// -----------------------------------------
typedef struct {
	
	POKEMON_PARAM*	pp;				///< �ӂ�����|�P����
	CONFIG*			cfg;			///< config	
	MYSTATUS*		my;
	u16				bgmno;			///< BGM�i���o�[
	
} EGG_CALL_PARAM;


// -----------------------------------------
//
//	���v���b�N�p���C�����[�N
//
// -----------------------------------------
typedef struct {
	
	int			seq;
	
	BOOL			is_name_set;
	NAMEIN_PARAM*	namein;
	
	EGG_CALL_PARAM	param;
	
} EGG_PROC_WORK;


// -----------------------------------------
//
//	���p�[�e�B�N���o�^�p���[�N
//
// -----------------------------------------
typedef struct {
	
	int heap_id;
	
	int spa_id;
//	int	spr_id;
	
} EGG_PARTICLE_PARAM;


// -----------------------------------------
//
//	���p�[�e�B�N���Ǘ�
//
// -----------------------------------------
typedef struct  {
	
	EGG_PARTICLE_PARAM	param;
	
	EMIT_PTR			emit;
	PTC_PTR				ptc;
	
} EGG_PARTICLE_SYS;

// -----------------------------------------
//
//	���V�X�e���p���[�N
//
// -----------------------------------------
typedef struct {
	
	GF_BGL_INI*				bgl;
	PALETTE_FADE_PTR		pfd;
	
	int						msg_index;
	int						msg_speed;
	
	int						win_type;			///< config ����
	GF_BGL_BMPWIN			win[ EDWIN_MAX ];
	
	GF_G3DMAN*				g3Dman;
	SOFT_SPRITE_MANAGER*	ssm_p;
	
	EGG_PARTICLE_SYS*		egg_pt;
	
	BMP_MENULIST_DATA*		bml;
	BMPMENU_WORK*			bmw;
	
	CATS_RES_PTR			crp;
	CATS_SYS_PTR			csp;
	POKE_ANM_SYS_PTR		pas;				///< pokemon anime
	
} COMMON_SYS_WORK;


// -----------------------------------------
//
//	���f���p���[�N
//
// -----------------------------------------
typedef struct {
	
	int		seq;
	int		cnt;
	
} EGG_DEMO_CAT_WORK;


// -----------------------------------------
//
//	�����C�����[�N
//
// -----------------------------------------
typedef struct {
	
	///< ----- �V�X�e���I�Ȃ���
	
	EGG_PROC_WORK*		epwk;		///< �v���b�N���[�N
	
	COMMON_SYS_WORK 	sys;		///< �V�X�e��
	
	///< ----- ���̑�
	int					mode;
	int					seq;
	
	int					sub_cnt;
	int					sub_seq;
	
	SOFT_SPRITE*		ssp_poke;	///< �|�P����
//	SOFT_SPRITE*		ssp_egg;	///< ���܂�
	
	CATS_ACT_PTR		egg;
	CATS_ACT_PTR		wnd_t;
	CATS_ACT_PTR		wnd_b;
	
	EGG_DEMO_CAT_WORK	demo;
		
} EGG_MAIN_WORK;

// =============================================================================
//
//
//	���v���g�^�C�v�Ƃ�
//
//
// =============================================================================






///< egg_disp.c
extern void EggDisp_SystemInit(void);
extern void EggDisp_DefaultBlendSet(void);
extern GF_G3DMAN* EggDisp_3D_Init(void);
extern void EggDisp_3DSetUp(void);
extern void EggDisp_3DVramInit(void);
extern void EggDisp_VramBankSet(GF_BGL_INI* bgl);
extern void EggDisp_VBlank(void* work);
extern void EggDisp_ParticleMain(void);

extern void EggDisp_WipeFadeIn(void);
extern void EggDisp_WipeFadeOut(void);

extern void EggDisp_BMP_WindowResLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype);
extern void EggDisp_BMP_WindowAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs, int pal);
extern int	EggDisp_BMP_MessageSet(GF_BGL_BMPWIN * win, int mes_id, POKEMON_PARAM* pp, int speed);
extern void EggDisp_BMP_WindowDel(GF_BGL_BMPWIN* win);

extern void EggDisp_BG_ResourceLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd);
extern void EggDisp_SubBG_ResourceLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd);

extern void EggDisp_SelWindowAdd(EGG_MAIN_WORK* emwk, GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs, int pal);
extern void EggDisp_SelWindowDel(EGG_MAIN_WORK* emwk);


// --- particle
extern EGG_PARTICLE_SYS* EggParticle_Init(EGG_PARTICLE_PARAM* param);
extern void EggParticle_SprSet(EGG_PARTICLE_SYS* eps, int no);
extern BOOL EggParticle_Main(EGG_PARTICLE_SYS* eps);
extern void EggParticle_End(EGG_PARTICLE_SYS* eps);
extern void EggParticle_PtcExit(PTC_PTR ptc);

// --- oam
extern void EggOAM_ResourceLoad(EGG_MAIN_WORK* emwk);
extern void EggOAM_Add(EGG_MAIN_WORK* emwk);
extern void EggOAM_Delete(EGG_MAIN_WORK* emwk);
extern BOOL EggOam_DemoMove(EGG_MAIN_WORK* emwk, int count);
enum {
	EGG_DEMO_MOVE_MAIN = 0,
	EGG_DEMO_MOVE_PARTICLE,
	EGG_DEMO_MOVE_END,
};
extern int	EggOam_DemoMoveEx(EGG_MAIN_WORK* emwk, int count);

// --- ssp
extern void EggPoke_Add(EGG_MAIN_WORK* emwk);
extern void EggPoke_Anm(EGG_MAIN_WORK* emwk);
extern void EggPoke_Del(EGG_MAIN_WORK* emwk);
extern void EggPoke_Vanish(EGG_MAIN_WORK* emwk, int flag);

extern void EggOAM_CatsInit(COMMON_SYS_WORK* sys);
extern void EggOAM_CatsDelete(COMMON_SYS_WORK* sys);


///< egg_main.c
extern BOOL EggMain_Executed(EGG_MAIN_WORK* emwk);








///< proc �Ăяo��
extern void EventCmd_EGGProc(GMEVENT_CONTROL * event, void* param);


///< �f�o�b�O�Ăяo��
extern void DebugEGG_DemoStart(FIELDSYS_WORK *fsys);
extern void DebugEGG_DemoStartMana(FIELDSYS_WORK *fsys);

#endif

