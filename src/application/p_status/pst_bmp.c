//============================================================================================
/**
 * @file	pst_bmp.c
 * @brief	�|�P�����X�e�[�^�X���BMP
 * @author	Hiroyuki Nakamura
 * @date	2005.11.15
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "system/buflen.h"
#include "system/window.h"
#include "battle/battle_common.h"
#include "contest/contest.h"
#include "contest/con_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/poke_number.h"
#include "poketool/poke_memo.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_pokestatus.h"
#include "itemtool/item.h"
#include "ribbon.h"

#define	PST_BMP_H_GLOBAL
#include "application/p_status.h"
#include "pst_sys.h"
#include "pst_obj.h"
#include "pst_bmp.h"
#include "pst_bmp_def.h"
#include "pst_snd_def.h"


//============================================================================================
//	�萔��`
//============================================================================================
// ������\�����[�h
enum {
	STR_MODE_LEFT = 0,	// ���l��
	STR_MODE_RIGHT,		// �E�l��
	STR_MODE_CENTER,	// ����
};

/*
#define	TMP_MSG_STR_SIZ		( 32 )		// �W�J�����T�C�Y ( 16x2 )
#define	TMP_NUM_STR_SIZ		( 16 )		// �W�J�����T�C�Y ( 8x2 )
*/

#define	PSTCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	PSTCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 14, 0 ) )		// �t�H���g�J���[�F��
#define	PSTCOL_N_BLUE	( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��
#define	PSTCOL_N_RED	( GF_PRINTCOLOR_MAKE( 5, 6, 0 ) )		// �t�H���g�J���[�F��
#define	PSTCOL_W_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 15 ) )		// �t�H���g�J���[�F��


#define	P5_WAZA_PX	( 1 )
#define	P5_WAZA_PY	( 2 )
#define	P5_PP_PX	( 16 )
#define	P5_PP_PY	( 16 )
#define	P5_PPNUM_PX	( 40+20 )
#define	P5_PPNUM_PY	( 16 )


#define	FILL_TITLE_PX	( 0 )		// �y�[�W�^�C�g���N���AX���W
#define	FILL_TITLE_PY	( 0 )		// �y�[�W�^�C�g���N���AY���W
#define	FILL_TITLE_SX	( 32 )		// �y�[�W�^�C�g���N���AX�T�C�Y
#define	FILL_TITLE_SY	( 2 )		// �y�[�W�^�C�g���N���AY�T�C�Y

#define	FILL_PARAM_PX	( 14 )		// �y�[�W�p�����[�^�N���AX���W
#define	FILL_PARAM_PY	( 2 )		// �y�[�W�p�����[�^�N���AY���W
#define	FILL_PARAM_SX	( 18 )		// �y�[�W�p�����[�^�N���AX�T�C�Y
#define	FILL_PARAM_SY	( 22 )		// �y�[�W�p�����[�^�N���AY�T�C�Y

#define	CND_TASTE_PY	( 16 )		// ���\��X���W

#define	P2_MEMO_PX		( 0 )	// �g���[�i�[�����\��X���W
#define	P2_MEMO_PY		( 0 )	// �g���[�i�[�����\��Y���W


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void StrPut( PST_WORK * wk, GF_BGL_BMPWIN * win, u32 col, u32 mode );
static void DefStr( PST_WORK * wk, u32 widx, u32 midx, u32 col, u32 mode );
static void PST_DefaultStrPut( PST_WORK * wk );
static void WazaPut( PST_WORK * wk, u32 pos );

static void PST_Page1BmpPut( PST_WORK * wk );
static void PST_Page2BmpPut( PST_WORK * wk );
static void PST_Page3BmpPut( PST_WORK * wk );
static void PST_Page4BmpPut( PST_WORK * wk );
static void PST_Page5BmpPut( PST_WORK * wk );
static void PST_Page6BmpPut( PST_WORK * wk );
static void PST_Page7BmpPut( PST_WORK * wk );
static void PST_Page8BmpPut( PST_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// ��{�������BMP�f�[�^
static const BMPWIN_DAT DefaultBmpData[] =
{
	{	// �u�|�P�������傤�ق��v
		GF_BGL_FRAME1_M, WIN_P1_TITLE_PX, WIN_P1_TITLE_PY,
		WIN_P1_TITLE_SX, WIN_P1_TITLE_SY, WIN_P1_TITLE_PAL, WIN_P1_TITLE_CGX
	},
	{	// �u�g���[�i�[�����v
		GF_BGL_FRAME1_M, WIN_P2_TITLE_PX, WIN_P2_TITLE_PY,
		WIN_P2_TITLE_SX, WIN_P2_TITLE_SY, WIN_P2_TITLE_PAL, WIN_P2_TITLE_CGX
	},
	{	// �u�|�P�����̂���傭�v
		GF_BGL_FRAME1_M, WIN_P3_TITLE_PX, WIN_P3_TITLE_PY,
		WIN_P3_TITLE_SX, WIN_P3_TITLE_SY, WIN_P3_TITLE_PAL, WIN_P3_TITLE_CGX
	},
	{	// �u�R���f�B�V�����v
		GF_BGL_FRAME1_M, WIN_P4_TITLE_PX, WIN_P4_TITLE_PY,
		WIN_P4_TITLE_SX, WIN_P4_TITLE_SY, WIN_P4_TITLE_PAL, WIN_P4_TITLE_CGX
	},
	{	// �u���������킴�v
		GF_BGL_FRAME1_M, WIN_P5_TITLE_PX, WIN_P5_TITLE_PY,
		WIN_P5_TITLE_SX, WIN_P5_TITLE_SY, WIN_P5_TITLE_PAL, WIN_P5_TITLE_CGX
	},
	{	// �u�R���e�X�g�킴�v
		GF_BGL_FRAME1_M, WIN_P6_TITLE_PX, WIN_P6_TITLE_PY,
		WIN_P6_TITLE_SX, WIN_P6_TITLE_SY, WIN_P6_TITLE_PAL, WIN_P6_TITLE_CGX
	},
	{	// �u�������́v
		GF_BGL_FRAME1_M, WIN_MOTIMONO_PX, WIN_MOTIMONO_PY,
		WIN_MOTIMONO_SX, WIN_MOTIMONO_SY, WIN_MOTIMONO_PAL, WIN_MOTIMONO_CGX
	},
	{	// �u������No.�v
		GF_BGL_FRAME1_M, WIN_P1_ZUKANNO_PX, WIN_P1_ZUKANNO_PY,
		WIN_P1_ZUKANNO_SX, WIN_P1_ZUKANNO_SY, WIN_P1_ZUKANNO_PAL, WIN_P1_ZUKANNO_CGX
	},
	{	// �u�Ȃ܂��v
		GF_BGL_FRAME1_M, WIN_P1_NAME_PX, WIN_P1_NAME_PY,
		WIN_P1_NAME_SX, WIN_P1_NAME_SY, WIN_P1_NAME_PAL, WIN_P1_NAME_CGX
	},
	{	// �u�^�C�v�v
		GF_BGL_FRAME1_M, WIN_P1_TYPE_PX, WIN_P1_TYPE_PY,
		WIN_P1_TYPE_SX, WIN_P1_TYPE_SY, WIN_P1_TYPE_PAL, WIN_P1_TYPE_CGX
	},
	{	// �u����v
		GF_BGL_FRAME1_M, WIN_P1_OYA_PX, WIN_P1_OYA_PY,
		WIN_P1_OYA_SX, WIN_P1_OYA_SY, WIN_P1_OYA_PAL, WIN_P1_OYA_CGX
	},
	{	// �uIDNo.�v
		GF_BGL_FRAME1_M, WIN_P1_IDNO_PX, WIN_P1_IDNO_PY,
		WIN_P1_IDNO_SX, WIN_P1_IDNO_SY, WIN_P1_IDNO_PAL, WIN_P1_IDNO_CGX
	},
	{	// �u���񂴂��́@�������񂿁v
		GF_BGL_FRAME1_M, WIN_P1_NOWEXP_PX, WIN_P1_NOWEXP_PY,
		WIN_P1_NOWEXP_SX, WIN_P1_NOWEXP_SY, WIN_P1_NOWEXP_PAL, WIN_P1_NOWEXP_CGX
	},
	{	// �u���̃��x���܂Łv
		GF_BGL_FRAME1_M, WIN_P1_NEXTLV_PX, WIN_P1_NEXTLV_PY,
		WIN_P1_NEXTLV_SX, WIN_P1_NEXTLV_SY, WIN_P1_NEXTLV_PAL, WIN_P1_NEXTLV_CGX
	},
	{	// �u���Ɓv
		GF_BGL_FRAME1_M, WIN_P1_ATO_PX, WIN_P1_ATO_PY,
		WIN_P1_ATO_SX, WIN_P1_ATO_SY, WIN_P1_ATO_PAL, WIN_P1_ATO_CGX
	},
	{	// �uHP�v
		GF_BGL_FRAME1_M, WIN_P3_HP_PX, WIN_P3_HP_PY,
		WIN_P3_HP_SX, WIN_P3_HP_SY, WIN_P3_HP_PAL, WIN_P3_HP_CGX
	},
	{	// �u���������v
		GF_BGL_FRAME1_M, WIN_P3_POW_PX, WIN_P3_POW_PY,
		WIN_P3_POW_SX, WIN_P3_POW_SY, WIN_P3_POW_PAL, WIN_P3_POW_CGX
	},
	{	// �u�ڂ�����v
		GF_BGL_FRAME1_M, WIN_P3_DEF_PX, WIN_P3_DEF_PY,
		WIN_P3_DEF_SX, WIN_P3_DEF_SY, WIN_P3_DEF_PAL, WIN_P3_DEF_CGX
	},
	{	// �u�Ƃ������v
		GF_BGL_FRAME1_M, WIN_P3_SPP_PX, WIN_P3_SPP_PY,
		WIN_P3_SPP_SX, WIN_P3_SPP_SY, WIN_P3_SPP_PAL, WIN_P3_SPP_CGX
	},
	{	// �u�Ƃ��ڂ��v
		GF_BGL_FRAME1_M, WIN_P3_SPD_PX, WIN_P3_SPD_PY,
		WIN_P3_SPD_SX, WIN_P3_SPD_SY, WIN_P3_SPD_PAL, WIN_P3_SPD_CGX
	},
	{	// �u���΂₳�v
		GF_BGL_FRAME1_M, WIN_P3_AGI_PX, WIN_P3_AGI_PY,
		WIN_P3_AGI_SX, WIN_P3_AGI_SY, WIN_P3_AGI_PAL, WIN_P3_AGI_CGX
	},
	{	// �u�Ƃ������v
		GF_BGL_FRAME1_M, WIN_P3_SPA_PX, WIN_P3_SPA_PY,
		WIN_P3_SPA_SX, WIN_P3_SPA_SY, WIN_P3_SPA_PAL, WIN_P3_SPA_CGX
	},
	{	// �u���Â�v
		GF_BGL_FRAME1_M, WIN_P4_KEDUYA_PX, WIN_P4_KEDUYA_PY,
		WIN_P4_KEDUYA_SX, WIN_P4_KEDUYA_SY, WIN_P4_KEDUYA_PAL, WIN_P4_KEDUYA_CGX
	},
	{	// �u���������v
		GF_BGL_FRAME1_M, WIN_P4_SEIKAKU_PX, WIN_P4_SEIKAKU_PY,
		WIN_P4_SEIKAKU_SX, WIN_P4_SEIKAKU_SY, WIN_P4_SEIKAKU_PAL, WIN_P4_SEIKAKU_CGX
	},
	{	// �u���ǂ�v
		GF_BGL_FRAME1_M, WIN_P5_MODORU_PX, WIN_P5_MODORU_PY,
		WIN_P5_MODORU_SX, WIN_P5_MODORU_SY, WIN_P5_MODORU_PAL, WIN_P5_MODORU_CGX
	},
	{	// �u�Ԃ�邢�v
		GF_BGL_FRAME1_M, WIN_P5_BUNRUI_PX, WIN_P5_BUNRUI_PY,
		WIN_P5_BUNRUI_SX, WIN_P5_BUNRUI_SY, WIN_P5_BUNRUI_PAL, WIN_P5_BUNRUI_CGX
	},
	{	// �u����傭
		GF_BGL_FRAME1_M, WIN_P5_IRYOKU_PX, WIN_P5_IRYOKU_PY,
		WIN_P5_IRYOKU_SX, WIN_P5_IRYOKU_SY, WIN_P5_IRYOKU_PAL, WIN_P5_IRYOKU_CGX
	},
	{	// �u�߂����イ�v
		GF_BGL_FRAME1_M, WIN_P5_HIT_PX, WIN_P5_HIT_PY,
		WIN_P5_HIT_SX, WIN_P5_HIT_SY, WIN_P5_HIT_PAL, WIN_P5_HIT_CGX
	},
	{	// �u���ǂ�܂��v
		GF_BGL_FRAME1_M, WIN_P8_MODORIMASU_PX, WIN_P8_MODORIMASU_PY,
		WIN_P8_MODORIMASU_SX, WIN_P8_MODORIMASU_SY, WIN_P8_MODORIMASU_PAL, WIN_P8_MODORIMASU_CGX
	},
	{	// �u�A�s�[���|�C���g�v
		GF_BGL_FRAME1_M, WIN_P6_AP_POINT_PX, WIN_P6_AP_POINT_PY,
		WIN_P6_AP_POINT_SX, WIN_P6_AP_POINT_SY, WIN_P6_AP_POINT_PAL, WIN_P6_AP_POINT_CGX
	},
	{	// �u�����Ă��邩���v
		GF_BGL_FRAME1_M, WIN_P7_MOTTEIRU_PX, WIN_P7_MOTTEIRU_PY,
		WIN_P7_MOTTEIRU_SX, WIN_P7_MOTTEIRU_SY, WIN_P7_MOTTEIRU_PAL, WIN_P7_MOTTEIRU_CGX
	},
	{	// �u���˂񃊃{���v
		GF_BGL_FRAME1_M, WIN_P7_TITLE_PX, WIN_P7_TITLE_PY,
		WIN_P7_TITLE_SX, WIN_P7_TITLE_SY, WIN_P7_TITLE_PAL, WIN_P7_TITLE_CGX
	},
	{	// �A�C�e����
		GF_BGL_FRAME1_M, WIN_ITEMNAME_PX, WIN_ITEMNAME_PY,
		WIN_ITEMNAME_SX, WIN_ITEMNAME_SY, WIN_ITEMNAME_PAL, WIN_ITEMNAME_CGX
	},
	{	// ���x��
		GF_BGL_FRAME1_M, WIN_LV_PX, WIN_LV_PY,
		WIN_LV_SX, WIN_LV_SY, WIN_LV_PAL, WIN_LV_CGX
	},
	{	// �j�b�N�l�[��
		GF_BGL_FRAME1_M, WIN_NICKNAME_PX, WIN_NICKNAME_PY,
		WIN_NICKNAME_SX, WIN_NICKNAME_SY, WIN_NICKNAME_PAL, WIN_NICKNAME_CGX
	},
	{	// �K�C�h���b�Z�[�W
		GF_BGL_FRAME1_M, WIN_GUIDE_PX, WIN_GUIDE_PY,
		WIN_GUIDE_SX, WIN_GUIDE_SY, WIN_GUIDE_PAL, WIN_GUIDE_CGX
	}
};

/*
	{	// �u���킵���v
		GF_BGL_FRAME1_M, WIN_P5_KUWASIKU_PX, WIN_P5_KUWASIKU_PY,
		WIN_P5_KUWASIKU_SX, WIN_P5_KUWASIKU_SY, WIN_P5_KUWASIKU_PAL, WIN_P5_KUWASIKU_CGX
	},
	{	// �u���ꂩ���v
		GF_BGL_FRAME1_M, WIN_P5_IREKAE_PX, WIN_P5_IREKAE_PY,
		WIN_P5_IREKAE_SX, WIN_P5_IREKAE_SY, WIN_P5_IREKAE_PAL, WIN_P5_IREKAE_CGX
	},
	{	// �u�����Ă��v
		GF_BGL_FRAME1_M, WIN_P5_KETTEI_PX, WIN_P5_KETTEI_PY,
		WIN_P5_KETTEI_SX, WIN_P5_KETTEI_SY, WIN_P5_KETTEI_PAL, WIN_P5_KETTEI_CGX
	},
	{	// �u���ǂ�v
		GF_BGL_FRAME1_M, WIN_P8_MODORU_PX, WIN_P8_MODORU_PY,
		WIN_P8_MODORU_SX, WIN_P8_MODORU_SY, WIN_P8_MODORU_PAL, WIN_P8_MODORU_CGX
	},
*/

// �y�[�W�P�i�|�P�������j
static const BMPWIN_DAT Page1BmpData[] =
{
	{	// �}��No.
		GF_BGL_FRAME1_M, A_WIN_P1_LIBNUM_PX, A_WIN_P1_LIBNUM_PY,
		A_WIN_P1_LIBNUM_SX, A_WIN_P1_LIBNUM_SY, A_WIN_P1_LIBNUM_PAL, A_WIN_P1_LIBNUM_CGX
	},
	{	// ���O
		GF_BGL_FRAME1_M, A_WIN_P1_NAME_PX, A_WIN_P1_NAME_PY,
		A_WIN_P1_NAME_SX, A_WIN_P1_NAME_SY, A_WIN_P1_NAME_PAL, A_WIN_P1_NAME_CGX
	},
	{	// �e��
		GF_BGL_FRAME1_M, A_WIN_P1_OYANAME_PX, A_WIN_P1_OYANAME_PY,
		A_WIN_P1_OYANAME_SX, A_WIN_P1_OYANAME_SY, A_WIN_P1_OYANAME_PAL, A_WIN_P1_OYANAME_CGX
	},
	{	// IDNo.
		GF_BGL_FRAME1_M, A_WIN_P1_IDNO_PX, A_WIN_P1_IDNO_PY,
		A_WIN_P1_IDNO_SX, A_WIN_P1_IDNO_SY, A_WIN_P1_IDNO_PAL, A_WIN_P1_IDNO_CGX
	},
	{	// ���݂̌o���l
		GF_BGL_FRAME1_M, A_WIN_P1_NOWEXP_PX, A_WIN_P1_NOWEXP_PY,
		A_WIN_P1_NOWEXP_SX, A_WIN_P1_NOWEXP_SY, A_WIN_P1_NOWEXP_PAL, A_WIN_P1_NOWEXP_CGX
	},
	{	// ���̃��x���܂�@
		GF_BGL_FRAME1_M, A_WIN_P1_NEXTEXP_PX, A_WIN_P1_NEXTEXP_PY,
		A_WIN_P1_NEXTEXP_SX, A_WIN_P1_NEXTEXP_SY, A_WIN_P1_NEXTEXP_PAL, A_WIN_P1_NEXTEXP_CGX
	}
};

// �y�[�W�Q�i�g���[�i�[�����j
static const BMPWIN_DAT Page2BmpData[] =
{
	{	// �g���[�i�[����
		GF_BGL_FRAME1_M, A_WIN_P2_TMEMO_PX, A_WIN_P2_TMEMO_PY,
		A_WIN_P2_TMEMO_SX, A_WIN_P2_TMEMO_SY, A_WIN_P2_TMEMO_PAL, A_WIN_P2_TMEMO_CGX
	}
};

// �y�[�W�R�i�|�P�����\�́j
static const BMPWIN_DAT Page3BmpData[] =
{
	{	// HP/MHP
		GF_BGL_FRAME1_M, A_WIN_P3_HP_PX, A_WIN_P3_HP_PY,
		A_WIN_P3_HP_SX, A_WIN_P3_HP_SY, A_WIN_P3_HP_PAL, A_WIN_P3_HP_CGX
	},
	{	// �U��
		GF_BGL_FRAME1_M, A_WIN_P3_POW_PX, A_WIN_P3_POW_PY,
		A_WIN_P3_POW_SX, A_WIN_P3_POW_SY, A_WIN_P3_POW_PAL, A_WIN_P3_POW_CGX
	},
	{	// �h��
		GF_BGL_FRAME1_M, A_WIN_P3_DEF_PX, A_WIN_P3_DEF_PY,
		A_WIN_P3_DEF_SX, A_WIN_P3_DEF_SY, A_WIN_P3_DEF_PAL, A_WIN_P3_DEF_CGX
	},
	{	// ���U
		GF_BGL_FRAME1_M, A_WIN_P3_SPP_PX, A_WIN_P3_SPP_PY,
		A_WIN_P3_SPP_SX, A_WIN_P3_SPP_SY, A_WIN_P3_SPP_PAL, A_WIN_P3_SPP_CGX
	},
	{	// ���h
		GF_BGL_FRAME1_M, A_WIN_P3_SPD_PX, A_WIN_P3_SPD_PY,
		A_WIN_P3_SPD_SX, A_WIN_P3_SPD_SY, A_WIN_P3_SPD_PAL, A_WIN_P3_SPD_CGX
	},
	{	// �f����
		GF_BGL_FRAME1_M, A_WIN_P3_AGI_PX, A_WIN_P3_AGI_PY,
		A_WIN_P3_AGI_SX, A_WIN_P3_AGI_SY, A_WIN_P3_AGI_PAL, A_WIN_P3_AGI_CGX
	},
	{	// ������
		GF_BGL_FRAME1_M, A_WIN_P3_SPANAME_PX, A_WIN_P3_SPANAME_PY,
		A_WIN_P3_SPANAME_SX, A_WIN_P3_SPANAME_SY, A_WIN_P3_SPANAME_PAL, A_WIN_P3_SPANAME_CGX
	},
	{	// ��������
		GF_BGL_FRAME1_M, A_WIN_P3_SPAINFO_PX, A_WIN_P3_SPAINFO_PY,
		A_WIN_P3_SPAINFO_SX, A_WIN_P3_SPAINFO_SY, A_WIN_P3_SPAINFO_PAL, A_WIN_P3_SPAINFO_CGX
	}
};

// �y�[�W�T�i�Z�j
static const BMPWIN_DAT Page5BmpData[] =
{
	{	// �Z���P
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA1_PX, A_WIN_P5_WAZA1_PY,
		A_WIN_P5_WAZA1_SX, A_WIN_P5_WAZA1_SY, A_WIN_P5_WAZA1_PAL, A_WIN_P5_WAZA1_CGX
	},
	{	// �Z���Q
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA2_PX, A_WIN_P5_WAZA2_PY,
		A_WIN_P5_WAZA2_SX, A_WIN_P5_WAZA2_SY, A_WIN_P5_WAZA2_PAL, A_WIN_P5_WAZA2_CGX
	},
	{	// �Z���R
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA3_PX, A_WIN_P5_WAZA3_PY,
		A_WIN_P5_WAZA3_SX, A_WIN_P5_WAZA3_SY, A_WIN_P5_WAZA3_PAL, A_WIN_P5_WAZA3_CGX
	},
	{	// �Z���S
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA4_PX, A_WIN_P5_WAZA4_PY,
		A_WIN_P5_WAZA4_SX, A_WIN_P5_WAZA4_SY, A_WIN_P5_WAZA4_PAL, A_WIN_P5_WAZA4_CGX
	},
	{	// �Z���T
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA5_PX, A_WIN_P5_WAZA5_PY,
		A_WIN_P5_WAZA5_SX, A_WIN_P5_WAZA5_SY, A_WIN_P5_WAZA5_PAL, A_WIN_P5_WAZA5_CGX
	},
	{	// �З�
		GF_BGL_FRAME1_M, A_WIN_P5_ATC_PX, A_WIN_P5_ATC_PY,
		A_WIN_P5_ATC_SX, A_WIN_P5_ATC_SY, A_WIN_P5_ATC_PAL, A_WIN_P5_ATC_CGX
	},
	{	// ����
		GF_BGL_FRAME1_M, A_WIN_P5_HIT_PX, A_WIN_P5_HIT_PY,
		A_WIN_P5_HIT_SX, A_WIN_P5_HIT_SY, A_WIN_P5_HIT_PAL, A_WIN_P5_HIT_CGX
	},
	{	// �Z����
		GF_BGL_FRAME1_M, A_WIN_P5_INFO_PX, A_WIN_P5_INFO_PY,
		A_WIN_P5_INFO_SX, A_WIN_P5_INFO_SY, A_WIN_P5_INFO_PAL, A_WIN_P5_INFO_CGX
	}
};

// �y�[�W�U�i�R���e�X�g�Z�j
static const BMPWIN_DAT Page6BmpData[] =
{
	{	// �Z���P
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA1_PX, A_WIN_P5_WAZA1_PY,
		A_WIN_P5_WAZA1_SX, A_WIN_P5_WAZA1_SY, A_WIN_P5_WAZA1_PAL, A_WIN_P5_WAZA1_CGX
	},
	{	// �Z���Q
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA2_PX, A_WIN_P5_WAZA2_PY,
		A_WIN_P5_WAZA2_SX, A_WIN_P5_WAZA2_SY, A_WIN_P5_WAZA2_PAL, A_WIN_P5_WAZA2_CGX
	},
	{	// �Z���R
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA3_PX, A_WIN_P5_WAZA3_PY,
		A_WIN_P5_WAZA3_SX, A_WIN_P5_WAZA3_SY, A_WIN_P5_WAZA3_PAL, A_WIN_P5_WAZA3_CGX
	},
	{	// �Z���S
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA4_PX, A_WIN_P5_WAZA4_PY,
		A_WIN_P5_WAZA4_SX, A_WIN_P5_WAZA4_SY, A_WIN_P5_WAZA4_PAL, A_WIN_P5_WAZA4_CGX
	},
	{	// �Z���T
		GF_BGL_FRAME1_M, A_WIN_P5_WAZA5_PX, A_WIN_P5_WAZA5_PY,
		A_WIN_P5_WAZA5_SX, A_WIN_P5_WAZA5_SY, A_WIN_P5_WAZA5_PAL, A_WIN_P5_WAZA5_CGX
	},
	{	// �Z����
		GF_BGL_FRAME1_M, A_WIN_P6_INFO_PX, A_WIN_P6_INFO_PY,
		A_WIN_P6_INFO_SX, A_WIN_P6_INFO_SY, A_WIN_P6_INFO_PAL, A_WIN_P6_INFO_CGX
	}
};

// �y�[�W�V�i�L�O���{���j
static const BMPWIN_DAT Page7BmpData[] =
{
	{	// ???��
		GF_BGL_FRAME1_M, A_WIN_P7_NUM_PX, A_WIN_P7_NUM_PY,
		A_WIN_P7_NUM_SX, A_WIN_P7_NUM_SY, A_WIN_P7_NUM_PAL, A_WIN_P7_NUM_CGX
	},
	{	// ???/???
		GF_BGL_FRAME1_M, A_WIN_P7_MAX_PX, A_WIN_P7_MAX_PY,
		A_WIN_P7_MAX_SX, A_WIN_P7_MAX_SY, A_WIN_P7_MAX_PAL, A_WIN_P7_MAX_CGX
	},
	{	// ���{����
		GF_BGL_FRAME1_M, A_WIN_P7_NAME_PX, A_WIN_P7_NAME_PY,
		A_WIN_P7_NAME_SX, A_WIN_P7_NAME_SY, A_WIN_P7_NAME_PAL, A_WIN_P7_NAME_CGX
	},
	{	// ���{������
		GF_BGL_FRAME1_M, A_WIN_P7_INFO_PX, A_WIN_P7_INFO_PY,
		A_WIN_P7_INFO_SX, A_WIN_P7_INFO_SY, A_WIN_P7_INFO_PAL, A_WIN_P7_INFO_CGX
	}
};



// �|���g�֘A�̃R���f�B�V�����y�[�W
static const BMPWIN_DAT PorutoCndBmpData[] =
{
	{	// �u�����Ă��v
		GF_BGL_FRAME1_M, A_WIN_COND_KETTEI_PX, A_WIN_COND_KETTEI_PY,
		A_WIN_COND_KETTEI_SX, A_WIN_COND_KETTEI_SY, A_WIN_COND_KETTEI_PAL, A_WIN_COND_KETTEI_CGX
	},
	{	// �u�����Ȃ��ׂ��́v
		GF_BGL_FRAME1_M, A_WIN_COND_LIKE_PX, A_WIN_COND_LIKE_PY,
		A_WIN_COND_LIKE_SX, A_WIN_COND_LIKE_SY, A_WIN_COND_LIKE_PAL, A_WIN_COND_LIKE_CGX
	},
	{	// ���b�Z�[�W
		GF_BGL_FRAME1_M, A_WIN_COND_MSG_PX, A_WIN_COND_MSG_PY,
		A_WIN_COND_MSG_SX, A_WIN_COND_MSG_SY, A_WIN_COND_MSG_PAL, A_WIN_COND_MSG_CGX
	}
/*
	{	// �u���ǂ�v
		GF_BGL_FRAME1_M, A_WIN_COND_MODORU_PX, A_WIN_COND_MODORU_PY,
		A_WIN_COND_MODORU_SX, A_WIN_COND_MODORU_SY, A_WIN_COND_MODORU_PAL, A_WIN_COND_MODORU_CGX
	},
*/
};













void PokeStatus_DefaultBmpAdd( PST_WORK * wk )
{
	u16	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->def_win[i], &DefaultBmpData[i] );
		GF_BGL_BmpWinDataFill( &wk->def_win[i], 0 );
	}
	PST_DefaultStrPut( wk );
	PokeStatus_NickNamePut( wk );
	PokeStatus_LvPut( wk );
	PokeStatus_ItemPut( wk );

/*
	OS_Printf( "PST_ADD_WIN : %d\n", ADD_WIN_PAGE_CGX );

	OS_Printf(
		"PST BMP -�g���[�i�[���� : %d\n",
		A_WIN_P2_TMEMO_CGX+A_WIN_P2_TMEMO_SX*A_WIN_P2_TMEMO_SY );
	OS_Printf(
		"PST BMP -�Z : %d\n",
		A_WIN_P6_INFO_CGX+A_WIN_P6_INFO_SX*A_WIN_P6_INFO_SY );
*/
/*
	OS_Printf(
		"PST BMP -�f�t�H���g : %d\n", WIN_NICKNAME_CGX+WIN_NICKNAME_SX*WIN_NICKNAME_SY );
	OS_Printf(
		"PST BMP -�|�P������� : %d\n",
		A_WIN_P1_NEXTEXP_CGX+A_WIN_P1_NEXTEXP_SX*A_WIN_P1_NEXTEXP_SY );
	OS_Printf(
		"PST BMP -�g���[�i�[���� : %d\n",
		A_WIN_P2_TMEMO_CGX+A_WIN_P2_TMEMO_SX*A_WIN_P2_TMEMO_SY );
	OS_Printf(
		"PST BMP -�|�P�����\�� : %d\n",
		A_WIN_P3_SPAINFO_CGX+A_WIN_P3_SPAINFO_SX*A_WIN_P3_SPAINFO_SY );
	OS_Printf(
		"PST BMP -�Z : %d\n",
		A_WIN_P5_WAZA5_CGX+A_WIN_P5_WAZA5_SX*A_WIN_P5_WAZA5_SY );
*/
}

void PokeStatus_PageBmpAdd( PST_WORK * wk )
{
	const BMPWIN_DAT * dat;
	u32	i;

	switch( wk->page ){
	case PST_PAGE_INFO:
		dat = Page1BmpData;
		wk->add_win_max = ADD_WIN_P1_MAX;
		break;
	case PST_PAGE_MEMO:
		dat = Page2BmpData;
		wk->add_win_max = ADD_WIN_P2_MAX;
		break;
	case PST_PAGE_PARAM:
		dat = Page3BmpData;
		wk->add_win_max = ADD_WIN_P3_MAX;
		break;
	case PST_PAGE_B_SKILL:
		dat = Page5BmpData;
		wk->add_win_max = ADD_WIN_P5_MAX;
		break;
	case PST_PAGE_C_SKILL:
		dat = Page6BmpData;
		wk->add_win_max = ADD_WIN_P6_MAX;
		break;
	case PST_PAGE_RIBBON:
		dat = Page7BmpData;
		wk->add_win_max = ADD_WIN_P7_MAX;
		break;

	case PST_PAGE_CONDITION:
	case PST_PAGE_RET:
		if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
			return;
		}
		dat = PorutoCndBmpData;
		wk->add_win_max = ADD_WIN_COND_MAX;
		break;

	default:
		return;
	}

	wk->add_win = GF_BGL_BmpWinAllocGet( HEAPID_POKESTATUS, wk->add_win_max );
	for( i=0; i<wk->add_win_max; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->add_win[i], &dat[i] );
	}
}

void PokeStatus_PageBmpFree( PST_WORK * wk )
{
	switch( wk->page ){
	case PST_PAGE_INFO:
	case PST_PAGE_MEMO:
	case PST_PAGE_PARAM:
	case PST_PAGE_B_SKILL:
	case PST_PAGE_C_SKILL:
	case PST_PAGE_RIBBON:
		break;

	case PST_PAGE_CONDITION:
	case PST_PAGE_RET:
		if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
			return;
		}
		break;

	default:
		return;
	}

	GF_BGL_BmpWinFree( wk->add_win, wk->add_win_max );
}

void PokeStatus_BmpFreeAll( PST_WORK * wk )
{
	u32	i;

	PokeStatus_PageBmpFree( wk );
	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &wk->def_win[i] );
	}
}


//============================================================================================
//	�j�b�N�l�[��������
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �j�b�N�l�[���E���ʕ\��
 *
 * @param	wk		�X�e�[�^�X��ʃ��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_NickNamePut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	u32	siz;

	win = &wk->def_win[WIN_NICKNAME];

	GF_BGL_BmpWinDataFill( win, 0 );

	// �j�b�N�l�[��
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->pp.nickname, 0, 0, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );

	// ����
	if( wk->pp.sex_put == 0 ){
		if( wk->pp.sex == PARA_MALE ){
			MSGMAN_GetString( wk->msg_man, mes_status_01_02, wk->msg_buf );
			StrPut( wk, win, PSTCOL_N_BLUE, STR_MODE_RIGHT );
		}else if( wk->pp.sex == PARA_FEMALE ){
			MSGMAN_GetString( wk->msg_man, mes_status_01_03, wk->msg_buf );
			StrPut( wk, win, PSTCOL_N_RED, STR_MODE_RIGHT );
		}
	}

	GF_BGL_BmpWinOnVReq( win );
}


//============================================================================================
//	���x��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���x���\��
 *
 * @param	wk		�X�e�[�^�X��ʃ��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_LvPut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->def_win[WIN_LV];

	GF_BGL_BmpWinDataFill( win, 0 );

	if( wk->pp.tamago == 0 ){
		NUMFONT_WriteMark( wk->num_font, NUMFONT_MARK_LV, win, 0, 5 );

		str = MSGMAN_AllocString( wk->msg_man, mes_status_01_04 );
		WORDSET_RegisterNumber(
			wk->wset, 0, wk->pp.lv, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );

		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			NUMFONT_MARK_WIDTH, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	}

	GF_BGL_BmpWinOnVReq( win );
}

//============================================================================================
//	�A�C�e��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���\��
 *
 * @param	wk		�X�e�[�^�X��ʃ��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_ItemPut( PST_WORK * wk )
{
	STRBUF * str;

	GF_BGL_BmpWinDataFill( &wk->def_win[WIN_ITEMNAME], 0 );

	if( wk->pp.item != 0 ){
		WORDSET_RegisterItemName( wk->wset, 0, wk->pp.item );
		str = MSGMAN_AllocString( wk->msg_man, mes_status_01_06 );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_status_01_07, wk->msg_buf );
	}
	StrPut( wk, &wk->def_win[WIN_ITEMNAME], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_MOTIMONO] );
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_ITEMNAME] );
}

//--------------------------------------------------------------------------------------------
/**
 * �K�C�h���b�Z�[�W�\��
 *
 * @param	wk		�X�e�[�^�X��ʃ��[�N
 * @param	midx	���b�Z�[�W�C���f�b�N�X
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeStatus_GuideStrPut( PST_WORK * wk, u32 midx )
{
	GF_BGL_BmpWinDataFill( &wk->def_win[WIN_GUIDE], 0 );
	DefStr( wk, WIN_GUIDE, midx, PSTCOL_N_WHITE, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_GUIDE] );
}





//--------------------------------------------------------------------------------------------
/**
 * �����̃|�P�������`�F�b�N
 *
 * @param	wk		�X�e�[�^�X��ʃ��[�N
 *
 * @retval	"TRUE = �����̃|�P����"
 * @retval	"FALSE = ���l�̃|�P����"
 */
//--------------------------------------------------------------------------------------------
static BOOL PST_PokeOyaCheck( PST_WORK * wk )
{
	if( ( wk->pp.id == wk->dat->player_id ) &&
		( wk->pp.oya_sex == wk->dat->player_sex ) &&
		( STRBUF_Compare( wk->pp.oya, wk->player_name ) == 0 ) ){

		return TRUE;
	}
	return FALSE;
}








static void StrPut( PST_WORK * wk, GF_BGL_BMPWIN * win, u32 col, u32 mode )
{
	u8	siz;
	u8	wsx;
	u8	px;

	switch( mode ){
	case STR_MODE_LEFT:		// ���l��
		px = 0;
		break;
	case STR_MODE_RIGHT:	// �E�l��
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( win ) * 8;
		px  = wsx - siz;
		break;
	case STR_MODE_CENTER:	// ����
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		wsx = GF_BGL_BmpWinGet_SizeX( win ) * 8;
		px  = (wsx-siz)/2;
		break;
	}
	GF_STR_PrintColor( win, FONT_SYSTEM, wk->msg_buf, px, 0, MSG_NO_PUT, col, NULL );
}

static void DefStr( PST_WORK * wk, u32 widx, u32 midx, u32 col, u32 mode )
{
	u8	siz;
	u8	wsx;
	u8	px;

	MSGMAN_GetString( wk->msg_man, midx, wk->msg_buf );
	StrPut( wk, &wk->def_win[widx], col, mode );
}




static void NumPrmSet( PST_WORK * wk, u32 msg_id, u32 num, u8 keta, u8 type )
{
	STRBUF * str_buf;

	str_buf = MSGMAN_AllocString( wk->msg_man, msg_id );
	WORDSET_RegisterNumber( wk->wset, 0, num, keta, type, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str_buf );
	STRBUF_Delete( str_buf );
}

//--------------------------------------------------------------------------------------------
/**
 * "??/??"�\��
 *
 * @param	wk			�X�e�[�^�X��ʃ��[�N
 * @param	widx		�E�B���h�E�C���f�b�N�X
 * @param	sra_id		"/"�̃��b�Z�[�WID
 * @param	now_id		���ݒl�̃��b�Z�[�WID
 * @param	max_id		�ő�l�̃��b�Z�[�WID
 * @param	now_prm		���ݒl
 * @param	max_prm		�ő�l
 * @param	keta		�\������
 * @param	px			�\��X���W�i���S�j
 * @param	py			�\��Y���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NumSraMaxStrPut(
				PST_WORK * wk, u32 widx,
				u32 sra_id, u32 now_id, u32 max_id,
				u16 now_prm, u16 max_prm, u8 keta, u8 px, u8 py )
{
	GF_BGL_BMPWIN * win;
	u32	siz;
	u16	spx;
	u16	mpx;

	win = &wk->add_win[widx];

	MSGMAN_GetString( wk->msg_man, sra_id, wk->msg_buf );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	spx = px - siz / 2;
	mpx = spx + siz;

	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, spx, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	NumPrmSet( wk, now_id, now_prm, keta, NUM_MODE_LEFT );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, spx-siz, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	NumPrmSet( wk, max_id, max_prm, keta, NUM_MODE_LEFT );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf, mpx, py, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
}



static void PST_DefaultStrPut( PST_WORK * wk )
{
	// �u�|�P�������傤�ق��v
	DefStr( wk, WIN_P1_TITLE, mes_status_02_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�g���[�i�[�����v
	DefStr( wk, WIN_P2_TITLE, mes_status_03_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�|�P�����̂���傭�v
	DefStr( wk, WIN_P3_TITLE, mes_status_04_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�R���f�B�V�����v
	DefStr( wk, WIN_P4_TITLE, mes_status_05_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���������킴�v
	DefStr( wk, WIN_P5_TITLE, mes_status_06_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�R���e�X�g�킴�v
	DefStr( wk, WIN_P6_TITLE, mes_status_07_01, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// �u�������́v
	DefStr( wk, WIN_MOTIMONO, mes_status_01_05, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// �u������No.�v
	DefStr( wk, WIN_P1_ZUKANNO, mes_status_02_02, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�Ȃ܂��v
	DefStr( wk, WIN_P1_NAME, mes_status_02_04, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�^�C�v�v
	DefStr( wk, WIN_P1_TYPE, mes_status_02_06, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u����v
	DefStr( wk, WIN_P1_OYA, mes_status_02_07, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �uIDNo.�v
	DefStr( wk, WIN_P1_IDNO, mes_status_02_09, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���񂴂��́@�������񂿁v
	DefStr( wk, WIN_P1_NOWEXP, mes_status_02_11, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���̃��x���܂Łv
	DefStr( wk, WIN_P1_NEXTLV, mes_status_02_13, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���Ɓv
	DefStr( wk, WIN_P1_ATO, mes_status_02_14, PSTCOL_N_BLACK, STR_MODE_LEFT );

	// �uHP�v
	DefStr( wk, WIN_P3_HP, mes_status_04_02, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���������v
	DefStr( wk, WIN_P3_POW, mes_status_04_03, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�ڂ�����v
	DefStr( wk, WIN_P3_DEF, mes_status_04_04, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�Ƃ������v
	DefStr( wk, WIN_P3_SPP, mes_status_04_05, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�Ƃ��ڂ��v
	DefStr( wk, WIN_P3_SPD, mes_status_04_06, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u���΂₳�v
	DefStr( wk, WIN_P3_AGI, mes_status_04_07, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �u�Ƃ������v
	DefStr( wk, WIN_P3_SPA, mes_status_04_08, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// �u���Â�v
	DefStr( wk, WIN_P4_KEDUYA, mes_status_05_02, PSTCOL_N_WHITE, STR_MODE_LEFT );

//	WIN_P4_SEIKAKU,		// �u���������v

	// �u���ǂ�v
//	DefStr( wk, WIN_P5_MODORU, mes_status_06_19, PSTCOL_N_WHITE, STR_MODE_LEFT );
	{
		MSGMAN_GetString( wk->msg_man, mes_status_06_19, wk->msg_buf );
		GF_STR_PrintColor(
			&wk->def_win[WIN_P5_MODORU], FONT_SYSTEM,
			wk->msg_buf, 0, P5_WAZA_PY, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );
	}

	// �Ԃ�邢
	DefStr( wk, WIN_P5_BUNRUI, mes_status_06_22, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// ����傭
	DefStr( wk, WIN_P5_IRYOKU, mes_status_06_20, PSTCOL_N_WHITE, STR_MODE_LEFT );
	// �߂����イ
	DefStr( wk, WIN_P5_HIT, mes_status_06_21, PSTCOL_N_WHITE, STR_MODE_LEFT );

	// �u���ǂ�܂��v
	DefStr( wk, WIN_P8_MODORIMASU, mes_status_08_02, PSTCOL_N_WHITE, STR_MODE_CENTER );

	// �u�A�s�[���|�C���g�v
	DefStr( wk, WIN_P6_AP_POINT, mes_status_07_04, PSTCOL_N_BLACK, STR_MODE_CENTER );

	// �u�����Ă��邩���v
	DefStr( wk, WIN_P7_MOTTEIRU, mes_status_10_04, PSTCOL_N_BLACK, STR_MODE_LEFT );
	// �u���˂񃊃{���v
	DefStr( wk, WIN_P7_TITLE, mes_status_10_01, PSTCOL_N_WHITE, STR_MODE_LEFT );
}



void PokeStatus_PageBmpPut( PST_WORK * wk )
{
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0,
		FILL_TITLE_PX, FILL_TITLE_PY, FILL_TITLE_SX, FILL_TITLE_SY, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0,
		FILL_PARAM_PX, FILL_PARAM_PY, FILL_PARAM_SX, FILL_PARAM_SY, GF_BGL_SCRWRT_PALNL );

	switch( wk->page ){
	case PST_PAGE_INFO:
		PST_Page1BmpPut( wk );
		break;
	case PST_PAGE_MEMO:
		PST_Page2BmpPut( wk );
		break;
	case PST_PAGE_PARAM:
		PST_Page3BmpPut( wk );
		break;
	case PST_PAGE_CONDITION:
		PST_Page4BmpPut( wk );
		break;
	case PST_PAGE_B_SKILL:
		PST_Page5BmpPut( wk );
		break;
	case PST_PAGE_C_SKILL:
		PST_Page6BmpPut( wk );
		break;
	case PST_PAGE_RIBBON:
		PST_Page7BmpPut( wk );
		break;
	case PST_PAGE_RET:
		PST_Page8BmpPut( wk );
		break;
	}
}


static void PST_Page1BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_TITLE] );		// �u�|�P�������傤�ق��v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_ZUKANNO] );	// �u������No.�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NAME] );		// �u�Ȃ܂��v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_TYPE] );		// �u�^�C�v�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_OYA] );		// �u����v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_IDNO] );		// �uIDNo.�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NOWEXP] );		// �u���񂴂��́@�������񂿁v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_NEXTLV] );		// �u���̃��x���܂Łv
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P1_ATO] );		// �u���Ɓv

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_LIBNUM], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_OYANAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_IDNO], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NOWEXP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P1_NEXTEXP], 0 );

	{	// �}��No.
		u32	num = PMNumber_GetPokeNumber( wk->dat->zukan_mode, wk->pp.mons );

		if( num != 0 ){
			NumPrmSet( wk, mes_status_02_03, num, 3, NUM_MODE_ZERO );
		}else{
			MSGMAN_GetString( wk->msg_man, mes_status_02_16, wk->msg_buf );
		}
	}

	if( wk->pp.rare == 0 ){
		StrPut( wk, &wk->add_win[ADD_WIN_P1_LIBNUM], PSTCOL_N_BLACK, STR_MODE_LEFT );
	}else{
		StrPut( wk, &wk->add_win[ADD_WIN_P1_LIBNUM], PSTCOL_N_RED, STR_MODE_LEFT );
	}

	// ���O
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P1_NAME], FONT_SYSTEM,
		wk->pp.monsname, 0, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	// �e��
	if( wk->pp.oya_sex == 0 ){
		GF_STR_PrintColor(
			&wk->add_win[ADD_WIN_P1_OYANAME], FONT_SYSTEM,
			wk->pp.oya, 0, 0, MSG_NO_PUT, PSTCOL_N_BLUE, NULL );
	}else{
		GF_STR_PrintColor(
			&wk->add_win[ADD_WIN_P1_OYANAME], FONT_SYSTEM,
			wk->pp.oya, 0, 0, MSG_NO_PUT, PSTCOL_N_RED, NULL );
	}

	// IDNo.
	NumPrmSet( wk, mes_status_02_10, ( wk->pp.id & 0xffff ), 5, NUM_MODE_ZERO );
	StrPut( wk, &wk->add_win[ADD_WIN_P1_IDNO], PSTCOL_N_BLACK, STR_MODE_LEFT );

	// ���݂̌o���l
	NumPrmSet( wk, mes_status_02_12, wk->pp.now_exp, 7, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P1_NOWEXP], PSTCOL_N_BLACK, STR_MODE_LEFT );

	// ���̃��x���܂�@
/* ���r�T�t�@�̈�ĉ���Lv100�ȏ�̌o���l�ɂȂ邽�߁A�}�C�i�X�\���ɂȂ��Ă��܂��s��Ώ� */
#if T1653_060815_FIX	// �Ώ���
	if( wk->pp.lv < 100 ){
		NumPrmSet( wk, mes_status_02_15, wk->pp.next_lv_exp-wk->pp.now_exp, 7, NUM_MODE_LEFT );
	}else{
		NumPrmSet( wk, mes_status_02_15, 0, 7, NUM_MODE_LEFT );
	}
#else					// �Ώ��O
	NumPrmSet( wk, mes_status_02_15, wk->pp.next_lv_exp-wk->pp.now_exp, 7, NUM_MODE_LEFT );
#endif	// T1653_060815_FIX
	StrPut( wk, &wk->add_win[ADD_WIN_P1_NEXTEXP], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_LIBNUM] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_OYANAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_IDNO] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NOWEXP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P1_NEXTEXP] );
}


#define	TRMEMO_MSGWRITE( msgdata ){												\
	if( msgdata.msg != NULL	){													\
		GF_STR_PrintColor(	win, FONT_SYSTEM, msgdata.msg,						\
							P2_MEMO_PX, P2_MEMO_PY + (msgdata.line-1) * 16,		\
							MSG_NO_PUT, PSTCOL_N_BLACK, NULL );					\
	}																			\
}

static void PST_Page2MemoPut( GF_BGL_BMPWIN* win, POKEMON_PARAM* pp, BOOL mine )
{
	TRMEMO_DATA* trdata = TrainerMemoGet( pp, mine, HEAPID_POKESTATUS );

	TRMEMO_MSGWRITE( trdata->character1 )
	TRMEMO_MSGWRITE( trdata->encount )
	TRMEMO_MSGWRITE( trdata->character2 )
	TRMEMO_MSGWRITE( trdata->palate )
	TRMEMO_MSGWRITE( trdata->eggstatus )

	TrainerMemoFree( trdata );
}

static void PST_Page2BmpPut( PST_WORK * wk )
{
	STRBUF * str;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P2_TITLE] );		// �u�g���[�i�[�����v

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P2_TMEMO], 0 );

	{
		void* pp = PokeStatusPokeParamGet( wk );	//�|�P�����f�[�^�|�C���^�擾
		BOOL	orner_flag = PST_PokeOyaCheck( wk );

		//�|�P�����f�[�^�̎�ޔ���
		if( wk->dat->ppt == PST_PP_TYPE_POKEPASO ){
			{
				//�p�\�R���̏ꍇ�A�莝���p�f�[�^�ɃR���o�[�g���Ă���
				POKEMON_PARAM* pp_tmp = PokemonParam_AllocWork( HEAPID_POKESTATUS );

				PokeReplace( pp, pp_tmp );
				PST_Page2MemoPut( &wk->add_win[ADD_WIN_P2_TMEMO], pp_tmp, orner_flag );
		
				sys_FreeMemoryEz( pp_tmp );
			}
		} else {
			//���̑��ʏ�
			PST_Page2MemoPut( &wk->add_win[ADD_WIN_P2_TMEMO], pp, orner_flag );
		}
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P2_TMEMO] );
}

static void PST_Page3BmpPut( PST_WORK * wk )
{
	u32	siz;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_TITLE] );		// �u�|�P�����̂���傭�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_HP] );			// �uHP�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_POW] );		// �u���������v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_DEF] );		// �u�ڂ�����v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPP] );		// �u�Ƃ������v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPD] );		// �u�Ƃ��ڂ��v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_AGI] );		// �u���΂₳�v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P3_SPA] );		// �u�Ƃ������v

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_HP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_POW], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_DEF], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPP], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPD], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_AGI], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPANAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P3_SPAINFO], 0 );

	// HP/MHP
	siz = GF_BGL_BmpWinGet_SizeX( &wk->add_win[ADD_WIN_P3_HP] ) * 8;
	NumSraMaxStrPut(
		wk, ADD_WIN_P3_HP, mes_status_04_09,
		mes_status_04_11, mes_status_04_10,
		wk->pp.hp, wk->pp.mhp, 3, siz/2, 0 );

	// �U��
	NumPrmSet( wk, mes_status_04_12, wk->pp.atc, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_POW], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// �h��
	NumPrmSet( wk, mes_status_04_13, wk->pp.def, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_DEF], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// ���U
	NumPrmSet( wk, mes_status_04_14, wk->pp.spa, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_SPP], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// ���h
	NumPrmSet( wk, mes_status_04_15, wk->pp.spd, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_SPD], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// �f����
	NumPrmSet( wk, mes_status_04_16, wk->pp.agi, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P3_AGI], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	{
		MSGDATA_MANAGER * man;
		STRBUF * str;
		
		// ������
		WORDSET_RegisterTokuseiName( wk->wset, 0, wk->pp.tokusei );
		str = MSGMAN_AllocString( wk->msg_man, mes_status_04_17 );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
		STRBUF_Delete( str );
		StrPut( wk, &wk->add_win[ADD_WIN_P3_SPANAME], PSTCOL_N_BLACK, STR_MODE_LEFT );

		// ��������
		man = MSGMAN_Create(
				MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_tokuseiinfo_dat, HEAPID_POKESTATUS );
		MSGMAN_GetString( man, wk->pp.tokusei, wk->msg_buf );
		MSGMAN_Delete( man );
		StrPut( wk, &wk->add_win[ADD_WIN_P3_SPAINFO], PSTCOL_N_BLACK, STR_MODE_LEFT );
	}

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_HP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_POW] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_DEF] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPP] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPD] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_AGI] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPANAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P3_SPAINFO] );
}


static void PST_Page4BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P4_TITLE] );			// �u�R���f�B�V�����v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P4_KEDUYA] );			// �u���Â�v

	if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_LIKE], 0 );

	MSGMAN_GetString( wk->msg_man, mes_status_09_03, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_COND_LIKE], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->msg_man, mes_status_09_04+wk->pp.like, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_COND_LIKE], FONT_SYSTEM,
		wk->msg_buf, 0, CND_TASTE_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_LIKE] );

	if( wk->dat->mode == PST_MODE_PORUTO ){
		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_KETTEI], 0 );
//		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_MODORU], 0 );

		MSGMAN_GetString( wk->msg_man, mes_status_09_01, wk->msg_buf );
		StrPut( wk, &wk->add_win[ADD_WIN_COND_KETTEI], PSTCOL_N_WHITE, STR_MODE_LEFT );

//		MSGMAN_GetString( wk->msg_man, mes_status_09_02, wk->msg_buf );
//		StrPut( wk, &wk->add_win[ADD_WIN_COND_MODORU], PSTCOL_N_WHITE, STR_MODE_LEFT );

		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_KETTEI] );
//		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_MODORU] );

		PokeStatus_A_ButtonMarkPut( wk, &wk->add_win[ADD_WIN_COND_KETTEI] );
	}
}

static void PST_Page5BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_TITLE] );			// �u���������킴�v

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PokeStatus_GuideStrPut( wk, mes_status_06_29 );		// �u�����Ă��v
	}else{
		PokeStatus_GuideStrPut( wk, mes_status_06_02 );		// �u���킵���v
	}
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA2], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA3], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA4], 0 );

	WazaPut( wk, 0 );
	WazaPut( wk, 1 );
	WazaPut( wk, 2 );
	WazaPut( wk, 3 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA2] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA3] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA4] );
}

static void PST_Page6BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P6_TITLE] );			// �u�R���e�X�g�킴�v

	if( wk->dat->mode == PST_MODE_WAZAADD ){
		PokeStatus_GuideStrPut( wk, mes_status_07_03 );			// �u�����Ă��v
	}else{
		PokeStatus_GuideStrPut( wk, mes_status_07_02 );			// �u���킵���v
	}
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA1], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA2], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA3], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_WAZA4], 0 );

	WazaPut( wk, 0 );
	WazaPut( wk, 1 );
	WazaPut( wk, 2 );
	WazaPut( wk, 3 );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA1] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA2] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA3] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_WAZA4] );
}

static void PST_Page7BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P7_TITLE] );			// �u���˂񃊃{���v
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P7_MOTTEIRU] );		// �u�����Ă��邩���v

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_NUM], 0 );
	NumPrmSet( wk, mes_status_10_05, wk->ribbon_max, 3, NUM_MODE_LEFT );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_NUM], PSTCOL_N_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_NUM] );

	if( wk->ribbon_max != 0 ){
		PokeStatus_GuideStrPut( wk, mes_status_10_02 );				// �u���킵���v
		PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );
	}
}

static void PST_Page8BmpPut( PST_WORK * wk )
{
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P8_MODORIMASU] );		// �u���ǂ�܂��v
	PokeStatus_GuideStrPut( wk, mes_status_08_01 );				// �u���ǂ�v
	PokeStatus_A_ButtonMarkPut( wk, &wk->def_win[WIN_GUIDE] );

	if( wk->dat->mode != PST_MODE_PORUTO && wk->dat->mode != PST_MODE_CONDITION ){
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_COND_LIKE], 0 );

	MSGMAN_GetString( wk->msg_man, mes_status_09_03, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_COND_LIKE], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->msg_man, mes_status_09_04+wk->pp.like, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_COND_LIKE], FONT_SYSTEM,
		wk->msg_buf, 0, CND_TASTE_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_COND_LIKE] );
}


void PokeStatus_RibbonPosNumPut( PST_WORK * wk )
{
	STRBUF * str;
	u8	px;
	u8	siz;

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_MAXNUM], 0 );

	// �ő吔
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_08 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->ribbon_max, 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	px  = A_WIN_P7_MAX_SX * 8 - siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		wk->msg_buf, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	// �X���b�V��
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_07 );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	px -= siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		str, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	// �J�[�\���ʒu
	str = MSGMAN_AllocString( wk->msg_man, mes_status_10_06 );
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->ribbon_pos+wk->ribbon_scr*4+1,
		3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
	px -= siz;
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P7_MAXNUM], FONT_SYSTEM,
		wk->msg_buf, px, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_MAXNUM] );
}

void PokeStatus_RibbonInfoPut( PST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_NAME], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P7_INFO], 0 );

	MSGMAN_GetString( wk->rbn_man, RIBBON_DataGet(wk->ribbon_num,RIBBON_PARA_NAME), wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_NAME], PSTCOL_N_WHITE, STR_MODE_LEFT );

	MSGMAN_GetString( wk->rbn_man, RIBBON_InfoGet(wk->dat->ribbon,wk->ribbon_num), wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P7_INFO], PSTCOL_N_BLACK, STR_MODE_LEFT );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_NAME] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P7_INFO] );
}



static void WazaPut( PST_WORK * wk, u32 pos )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;
	u16	waza;
	u8	npp, mpp;

	win = &wk->add_win[ADD_WIN_P5_WAZA1+pos];

	if( pos != 4 ){
		waza = wk->pp.waza[pos];
		npp  = wk->pp.wpp[pos];
		mpp  = wk->pp.mpp[pos];
	}else{
		waza = wk->dat->waza;
		npp  = WT_PPMaxGet( waza, 0 );
		mpp  = npp;
	}

	// �Z��
	MSGMAN_GetString( wk->wman, waza, wk->msg_buf );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, wk->msg_buf,
		P5_WAZA_PX, P5_WAZA_PY, MSG_NO_PUT, PSTCOL_N_WHITE, NULL );

	// PP
	if( waza != 0 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_08, wk->msg_buf );
		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			P5_PP_PX, P5_PP_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
		NumSraMaxStrPut(
			wk, ADD_WIN_P5_WAZA1+pos, mes_status_04_09,
			mes_status_06_09+pos, mes_status_06_14+pos,
			npp, mpp, 2, P5_PPNUM_PX, P5_PPNUM_PY );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_status_06_27, wk->msg_buf );
		siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, wk->msg_buf, 0 );
		GF_STR_PrintColor(
			win, FONT_SYSTEM, wk->msg_buf,
			P5_PPNUM_PX-siz/2, P5_PP_PY, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );
	}
}


void PokeStatus_WazaInfoPut( PST_WORK * wk, u32 waza )
{
	MSGDATA_MANAGER * man;
	u32	siz;
	u32	prm;

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_BUNRUI] );	// �Ԃ�邢
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_IRYOKU] );	// ����傭
	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_HIT] );	// �߂����イ

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_ATC], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_HIT], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_INFO], 0 );

	// �З�
	prm = WT_WazaDataParaGet( waza, ID_WTD_damage );
	if( prm <= 1 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_28, wk->msg_buf );
	}else{
		NumPrmSet( wk, mes_status_06_23, prm, 3, NUM_MODE_LEFT );
	}
	StrPut( wk, &wk->add_win[ADD_WIN_P5_ATC], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// ����
	prm = WT_WazaDataParaGet(waza,ID_WTD_hitprobability);
	if( prm == 0 ){
		MSGMAN_GetString( wk->msg_man, mes_status_06_28, wk->msg_buf );
	}else{
		NumPrmSet( wk, mes_status_06_24, prm, 3, NUM_MODE_LEFT );
	}
	StrPut( wk, &wk->add_win[ADD_WIN_P5_HIT], PSTCOL_N_BLACK, STR_MODE_RIGHT );

	// ����
	man = MSGMAN_Create(
			MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazainfo_dat, HEAPID_POKESTATUS );
	MSGMAN_GetString( man, waza, wk->msg_buf );
	StrPut( wk, &wk->add_win[ADD_WIN_P5_INFO], PSTCOL_N_BLACK, STR_MODE_LEFT );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_ATC] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_HIT] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_INFO] );
}

void PokeStatus_WazaInfoOff( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_BUNRUI] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_IRYOKU] );
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_HIT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_ATC] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_HIT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_INFO] );
}

void PokeStatus_SkillCancelPut( PST_WORK * wk )
{
	if( wk->dat->waza != 0 ){
		GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA5], 0 );
		WazaPut( wk, 4 );
		GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA5] );
	}else{
		GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P5_MODORU] );
	}
}

void PokeStatus_SkillCancelDel( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P5_MODORU] );
	GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );
}




void PokeStatus_SkillChgRewrite( PST_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1+wk->cur_pos], 0 );
	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P5_WAZA1+wk->sub_cur], 0 );

	WazaPut( wk, wk->cur_pos );
	WazaPut( wk, wk->sub_cur );

	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1+wk->cur_pos] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P5_WAZA1+wk->sub_cur] );
}


void PokeStatus_WazaOboeErrorMsgPut( PST_WORK * wk )
{
	GF_BGL_BMPWIN * win;

	if( wk->page == PST_PAGE_B_SKILL ){
//		PokeStatus_WazaInfoOff( wk );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_ATC] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_HIT] );
		GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P5_INFO] );
		win = &wk->add_win[ADD_WIN_P5_INFO];
	}else{
//		PokeStatus_ContestWazaInfoOff( wk );
		win = &wk->add_win[ADD_WIN_P6_INFO];
	}
	GF_BGL_BmpWinDataFill( win, 0 );
	MSGMAN_GetString( wk->msg_man, mes_status_06_30, wk->msg_buf );
	StrPut( wk, win, PSTCOL_N_BLACK, STR_MODE_LEFT );
	GF_BGL_BmpWinOnVReq( win );
}


void PokeStatus_ContestWazaInfoPut( PST_WORK * wk, u32 waza )
{
	MSGDATA_MANAGER * man;
	u32	ap_no;
	u32	msg_id;

	GF_BGL_BmpWinDataFill( &wk->add_win[ADD_WIN_P6_INFO], 0 );

	ap_no  = WT_WazaDataParaGet( waza, ID_WTD_ap_no );
	msg_id = ConTool_GetListAPSetumeiMsgID( ap_no );

	man = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_wazaexplain_dat, HEAPID_POKESTATUS );

	MSGMAN_GetString( man, msg_id, wk->msg_buf );
	GF_STR_PrintColor(
		&wk->add_win[ADD_WIN_P6_INFO], FONT_SYSTEM,
		wk->msg_buf, 0, 0, MSG_NO_PUT, PSTCOL_N_BLACK, NULL );

	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->def_win[WIN_P6_AP_POINT] );
	GF_BGL_BmpWinOnVReq( &wk->add_win[ADD_WIN_P6_INFO] );
}

void PokeStatus_ContestWazaInfoOff( PST_WORK * wk )
{
	GF_BGL_BmpWinOffVReq( &wk->def_win[WIN_P6_AP_POINT] );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_P6_INFO] );
}





void PokeStatus_CondUpMsgPut( PST_WORK * wk, u8 num )
{
	GF_BGL_BMPWIN * win;
	u32	midx;

	switch( num ){
	case 0:		// �������悳
		midx = mes_status_09_09_01;
		break;
	case 1:		// ��������
		midx = mes_status_09_09_03;
		break;
	case 2:		// ���킢��
		midx = mes_status_09_09_04;
		break;
	case 3:		// ��������
		midx = mes_status_09_09_05;
		break;
	case 4:		// �����܂���
		midx = mes_status_09_09_02;
		break;
	case PST_MSG_PRMNONE:	// �ω��Ȃ�
		midx = mes_status_09_09_06;
		break;
	default:	// �H�ׂ��Ȃ�
		midx = mes_status_09_09_07;
	}

	win = &wk->add_win[ADD_WIN_COND_MSG];
	BmpTalkWinWrite( win, WINDOW_TRANS_OFF, PST_CGX_TALKWIN, PST_PAL_TALKWIN );
	GF_BGL_BmpWinDataFill( win, 15 );
	MSGMAN_GetString( wk->msg_man, midx, wk->msg_buf );
	GF_STR_PrintColor( win, FONT_TALK, wk->msg_buf, 0, 0, MSG_NO_PUT, PSTCOL_W_BLACK, NULL );
	GF_BGL_BmpWinOnVReq( win );
}
