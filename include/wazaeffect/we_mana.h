//==============================================================================
/**
 * @file	we_mana.h
 * @brief	�Z�G�t�F�N�g�p�V�X�e��
 * @author	goto
 * @date	2005.06.22(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	_WE_MANA_H_
#define _WE_MANA_H_

#include "battle/battle_common.h"
#include "battle/scio.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "system/softsprite.h"

#include "system/gra_tool.h"

// =============================================================================
//
//
//	�������p
//	
//		[ _WE-SYS_ ]		WE-SYS
//
//
// =============================================================================

// -----------------------------------------
//
//	WE_SYS�̍\����*
//
// -----------------------------------------
typedef struct _TWE_SYS  *	WE_SYS_PTR;


// -----------------------------------------
//
//	BTL_SYS�̍\����*
//
// -----------------------------------------
typedef struct _TBTL_SYS *	BTL_SYS_PTR;


// -----------------------------------------
//
//	SE_SYS�̍\����*
//
// -----------------------------------------
typedef struct _TSE_SYS  *	SE_SYS_PTR;


// -----------------------------------------
//
//	HC_SYS�̍\����*
//
// -----------------------------------------
typedef struct _THC_SYS  *	HC_SYS_PTR;


// -----------------------------------------
//
//	HC_SCROLL_SYS�̍\����*
//
// -----------------------------------------
typedef struct _HC_SUB_SYS * HC_SUB_PTR;


// -----------------------------------------
//
//	�Z�G�t�F�N�g�̔w�i�A�[�N�f�[�^
//
// -----------------------------------------
typedef struct {

	int arc_index;		///< �A�[�NID
	int	chr_id;			///< �L����ID
	int pal_id;			///< �p���b�gID
	int scr_id;			///< �X�N���[��ID
	
	int pal_start;		///< �w�i�Ɏg�p����p���b�g�J�n�ʒu
	int pal_num;		///< �w�i�Ɏg�p����p���b�g�{��

} TWES_HAIKEI_ARC;

// -----------------------------------------
//
//	�Z�G�t�F�N�g�R�[�����Ƀo�g������󂯓n����郁���o
//
// -----------------------------------------
typedef struct {

	CATS_SYS_PTR		csp;						///< CSP
	GF_BGL_INI*			bgl;						///< BGL*
	PALETTE_FADE_PTR	pfd;						///< PFD*
	EXCHR_PARAM*		excp[CLIENT_MAX];			///< �L�����o�b�t�@
	u8 			 		client_type[ CLIENT_MAX ];	///< �N���C�A���gType
	SOFT_SPRITE*		ss[ CLIENT_MAX ];			///< �\�t�g�X�v���C�g
	u32					fight_type;					///< �t�@�C�g�^�C�v
	u16					mons_no[CLIENT_MAX];		///< �|�P����NO
	u8 			 		sex[ CLIENT_MAX ];			///< ����
	u8					rare[ CLIENT_MAX ];			///< ���A�t���O
	u8					form_no[CLIENT_MAX];		///< �|�P�����t�H����NO
	u32					personal_rnd[CLIENT_MAX];	///< �|�P����������
	u32					waza_kouka[CLIENT_MAX];		///< �Z���ʃt���O
	
	int					eff_arc_id;					///< �G�t�F�N�g�̎��(�A�[�J�C�uID)
	TWES_HAIKEI_ARC		haikei_data;				///< �w�i�f�[�^
	
	PERAPVOICE*			perap_voice;				///< �y���b�v
	u8*					bg_area;					///< �o�g���̔w�i
	u16*				pal_area;					///< �o�g���̃p���b�g
	
} WES_CALL_BTL_EX_PARAM;


// ---------------------------
//
//	�ϐg�Ƃ��悤
//
// ---------------------------
typedef struct {
	
	int					at_client_no;				///< �ϐg���鑤
	int					df_client_no;				///< �ϐg����鑤 at == df �Ȃ�������]	
	
	EXCHR_PARAM*		excp[CLIENT_MAX];			///< �L�����o�b�t�@
	SOFT_SPRITE*		ss[ CLIENT_MAX ];			///< �\�t�g�X�v���C�g
	u16					mons_no[CLIENT_MAX];		///< �|�P����NO
	u8					sex[CLIENT_MAX];			///< �|�P��������
	u8					rare[CLIENT_MAX];			///< �|�P�������A�t���O
	u8					form_no[CLIENT_MAX];		///< �|�P�����t�H����No
	u32					personal_rnd[CLIENT_MAX];	///< �|�P����������
	u8 			 		client_type[ CLIENT_MAX ];	///< �N���C�A���gType
	
} WAZA_POKE_CHANGE_PARAM;

// =========================================
//
//
//	���O���Q�ƁFWE-SYS�{��	[ _WE-SYS_ ]
//
//
// =========================================

// -----------------------------------------
//
//	WE-SYS �쐬
//
// -----------------------------------------
extern WE_SYS_PTR WES_Create(int heap_area);


// -----------------------------------------
//
//	WE-SYS �R���e�X�g�p�t���O����֐�
//
// -----------------------------------------
extern void WES_ContestFlag_Set(WE_SYS_PTR we_sys, BOOL flag);
extern BOOL WES_ContestFlag_Get(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	WE-SYS �j��
//
// -----------------------------------------
extern BOOL	WES_Delete(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	�Z�Ăяo��
//
// -----------------------------------------
extern BOOL WES_Call(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no);
extern BOOL WES_Call_Ex(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no,
						WES_CALL_BTL_EX_PARAM* wcbep);


// -----------------------------------------
//
//	���s
//	
// -----------------------------------------
extern BOOL	WES_Executed(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	�G�t�F�N�g�I���`�F�b�N
//
// -----------------------------------------
extern BOOL IsWES_Executed(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	�G�t�F�N�g�̏�����
//
// -----------------------------------------
extern BOOL WES_Reset(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	WE-SYS ����`�F�b�N
//
// -----------------------------------------
extern BOOL IsWES(WE_SYS_PTR we_sys);


#endif
