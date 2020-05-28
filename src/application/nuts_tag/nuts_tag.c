//============================================================================================
/**
 * @file	nuts_tag.c
 * @brief	�؂̎��^�O��ʏ���
 * @author	Hiroyuki Nakamura
 * @date	06.01.25
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_kinomi_tag.h"
#include "itemtool/itemsym.h"
#include "itemtool/nuts.h"
#include "application/app_tool.h"
#include "communication/wm_icon.h"

#define	NUTS_TAG_H_GLOBAL
#include "ntag_dat.h"
#include "application/nuts_tag.h"
#include "ntag_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
#define	NUTS_TAG_MAX		( 63 )					// �^�O���i�O�I���W���j

enum {
	WIN_NUTS_TITLE = 0,		// �u���̂݃^�O�v
	WIN_NUTS_NAME,			// �؂̎���
	WIN_KARAI,				// ���F���炢
	WIN_SIBUI,				// ���F���Ԃ�
	WIN_AMAI,				// ���F���܂�
	WIN_NIGAI,				// ���F�ɂ���
	WIN_SUPPAI,				// ���F�����ς�
	WIN_SIZE,				// �u���������v
	WIN_SIZE_NUM,			// �傫���l
	WIN_HARD,				// �u�������v
	WIN_HARD_NUM,			// �d���l
	WIN_INFO,				// ����
	WIN_MAX
};

typedef struct {
	VecFx16	lt;		// ����
	VecFx16	rt;		// �E��
	VecFx16	lu;		// ����
	VecFx16	ru;		// �E��
}NTAG_CONDISION_VTX;

typedef struct {
	GF_BGL_INI * bgl;						// BGL�f�[�^

	GF_BGL_BMPWIN	win[WIN_MAX];			// BMP�E�B���h�E�f�[�^�i�ʏ�j

	MSGDATA_MANAGER * mman;		// ���b�Z�[�W�f�[�^�}�l�[�W��
	WORDSET * wset;				// �P��Z�b�g
	NUMFONT * nfnt;				// 8x8�t�H���g

	GF_CAMERA_PTR	camera;		// �J����

	NTAG_CONDISION_VTX	cvtx[4];	// �\�����W
	NTAG_CONDISION_VTX	pvtx[4];	// �v���X�l
	NTAG_CONDISION_VTX	mvtx[4];	// �ő�l
	u32	con_mv_cnt;

	NTAG_DATA * dat;

	NUTSDATA * nuts;

//	BOOL	wipe_flg;

	u8	blend_flg;
	u8	blend_cnt;

}NTAG_WORK;

enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_CHANGE,
	SEQ_OUT
};

// �p���b�g��`
#define	NTAG_TITLE_PAL		( 2 )		// �u���̂݃^�O�v�����p���b�g
#define	NTAG_NUTS_PAL		( 3 )		// �؂̎��O���t�B�b�N�p���b�g
#define	NTAG_SYSFONT_PAL	( 15 )		// �V�X�e���t�H���g�p���b�g

#define	TITLE_BACK_COL		( 4 )		// �u���̂݃^�O�v�̔w�i�J���[
// �t�H���g�J���[
#define	PCOL_TITLE	(GF_PRINTCOLOR_MAKE(1,2,TITLE_BACK_COL))	// �t�H���g�J���[�F�u���̂݃^�O�v�p
#define	PCOL_N_BLACK	( GF_PRINTCOLOR_MAKE( 1, 2, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_WHITE	( GF_PRINTCOLOR_MAKE( 15, 2, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_BLUE		( GF_PRINTCOLOR_MAKE( 7, 8, 0 ) )		// �t�H���g�J���[�F��
#define	PCOL_N_RED		( GF_PRINTCOLOR_MAKE( 3, 4, 0 ) )		// �t�H���g�J���[�F��

#define	HEADER_STR_FRM		( GF_BGL_FRAME3_M )

// BMP�֘A
// �؂̎��̊G�i���ۂ�BMP�ł͂Ȃ��j
#define	NUTS_GRA_FRM		( GF_BGL_FRAME1_M )
#define	NUTS_GRA_PX			( 2 )
#define	NUTS_GRA_PY			( 5 )
#define	NUTS_GRA_SX			( 8 )
#define	NUTS_GRA_SY			( 8 )
#define	NUTS_GRA_PAL		( NTAG_NUTS_PAL )
#define	NUTS_GRA_CGX		( 1 )
// �u���̂݃^�O�v
#define	BMP_NUTS_TITLE_FRM	( GF_BGL_FRAME3_M )
#define	BMP_NUTS_TITLE_PX	( 1 )
#define	BMP_NUTS_TITLE_PY	( 0 )
#define	BMP_NUTS_TITLE_SX	( 12 )
#define	BMP_NUTS_TITLE_SY	( 2 )
#define	BMP_NUTS_TITLE_PAL	( NTAG_TITLE_PAL )
#define	BMP_NUTS_TITLE_CGX	( 1024 - BMP_NUTS_TITLE_SX * BMP_NUTS_TITLE_SY )
// �؂̎���
#define	BMP_NUTS_NAME_FRM	( GF_BGL_FRAME1_M )
#define	BMP_NUTS_NAME_PX	( 1 )
#define	BMP_NUTS_NAME_PY	( 3 )
#define	BMP_NUTS_NAME_SX	( 10 )
#define	BMP_NUTS_NAME_SY	( 2 )
#define	BMP_NUTS_NAME_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_NUTS_NAME_CGX	( NUTS_GRA_CGX + NUTS_GRA_SX * NUTS_GRA_SY )
// �傫���l
#define	BMP_SIZ_NUM_FRM	( GF_BGL_FRAME1_M )
#define	BMP_SIZ_NUM_PX	( 8 )
#define	BMP_SIZ_NUM_PY	( 13 )
#define	BMP_SIZ_NUM_SX	( 6 )
#define	BMP_SIZ_NUM_SY	( 2 )
#define	BMP_SIZ_NUM_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_SIZ_NUM_CGX	( BMP_NUTS_NAME_CGX + BMP_NUTS_NAME_SX * BMP_NUTS_NAME_SY )
// �d���l
#define	BMP_HARD_NUM_FRM	( GF_BGL_FRAME1_M )
#define	BMP_HARD_NUM_PX		( 8 )
#define	BMP_HARD_NUM_PY		( 15 )
#define	BMP_HARD_NUM_SX		( 15 )
#define	BMP_HARD_NUM_SY		( 2 )
#define	BMP_HARD_NUM_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_HARD_NUM_CGX	( BMP_SIZ_NUM_CGX + BMP_SIZ_NUM_SX * BMP_SIZ_NUM_SY )
// ����
#define	BMP_INFO_FRM	( GF_BGL_FRAME1_M )
#define	BMP_INFO_PX		( 2 )
#define	BMP_INFO_PY		( 17 )
#define	BMP_INFO_SX		( 28 )
#define	BMP_INFO_SY		( 6 )
#define	BMP_INFO_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_INFO_CGX	( BMP_HARD_NUM_CGX + BMP_HARD_NUM_SX * BMP_HARD_NUM_SY )

// ���F���炢
#define	BMP_KARAI_FRM	( HEADER_STR_FRM )
#define	BMP_KARAI_PX	( 20 )
#define	BMP_KARAI_PY	( 1 )
#define	BMP_KARAI_SX	( 5 )
#define	BMP_KARAI_SY	( 2 )
#define	BMP_KARAI_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_KARAI_CGX	( 512 )
// ���F���Ԃ�
#define	BMP_SIBUI_FRM	( HEADER_STR_FRM )
#define	BMP_SIBUI_PX	( 27 )
#define	BMP_SIBUI_PY	( 6 )
#define	BMP_SIBUI_SX	( 5 )
#define	BMP_SIBUI_SY	( 2 )
#define	BMP_SIBUI_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_SIBUI_CGX	( BMP_KARAI_CGX + BMP_KARAI_SX * BMP_KARAI_SY )
// ���F���܂�
#define	BMP_AMAI_FRM	( HEADER_STR_FRM )
#define	BMP_AMAI_PX		( 24 )
#define	BMP_AMAI_PY		( 12 )
#define	BMP_AMAI_SX		( 5 )
#define	BMP_AMAI_SY		( 2 )
#define	BMP_AMAI_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_AMAI_CGX	( BMP_SIBUI_CGX + BMP_SIBUI_SX * BMP_SIBUI_SY )
// ���F�ɂ���
#define	BMP_NIGAI_FRM	( HEADER_STR_FRM )
#define	BMP_NIGAI_PX	( 16 )
#define	BMP_NIGAI_PY	( 12 )
#define	BMP_NIGAI_SX	( 5 )
#define	BMP_NIGAI_SY	( 2 )
#define	BMP_NIGAI_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_NIGAI_CGX	( BMP_AMAI_CGX + BMP_AMAI_SX * BMP_AMAI_SY )
// ���F�����ς�
#define	BMP_SUPPAI_FRM	( HEADER_STR_FRM )
#define	BMP_SUPPAI_PX	( 12 )
#define	BMP_SUPPAI_PY	( 6 )
#define	BMP_SUPPAI_SX	( 6 )
#define	BMP_SUPPAI_SY	( 2 )
#define	BMP_SUPPAI_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_SUPPAI_CGX	( BMP_NIGAI_CGX + BMP_NIGAI_SX * BMP_NIGAI_SY )
// �u���������v
#define	BMP_SIZE_FRM	( HEADER_STR_FRM )
#define	BMP_SIZE_PX		( 2 )
#define	BMP_SIZE_PY		( 13 )
#define	BMP_SIZE_SX		( 6 )
#define	BMP_SIZE_SY		( 2 )
#define	BMP_SIZE_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_SIZE_CGX	( BMP_SUPPAI_CGX + BMP_SUPPAI_SX * BMP_SUPPAI_SY )
// �u�������v
#define	BMP_HARD_FRM	( HEADER_STR_FRM )
#define	BMP_HARD_PX		( 2 )
#define	BMP_HARD_PY		( 15 )
#define	BMP_HARD_SX		( 6 )
#define	BMP_HARD_SY		( 2 )
#define	BMP_HARD_PAL	( NTAG_SYSFONT_PAL )
#define	BMP_HARD_CGX	( BMP_SIZE_CGX + BMP_SIZE_SX * BMP_SIZE_SY )


#define	BMP_PUT_SEQ_MAX	( 8 )	// BMP�\���V�[�P���X�ő�l

#define	NUTS_NAME_PX	( 40 )	// �؂̎����\��X�ʒu
#define	NAME_NO_PY		( 5 )	// �uNo.�v�\��Y�ʒu
#define	HARD_PX			( 0 )	// �d���l�\��X�ʒu
#define	SIZE_PX			( 0 )	// �傫���l�\��X�ʒu


/*
	�R���f�B�V�����i���j�Q�[�W�͂S�̎l�p�|���S���ŕ\������Ă���B
	�l�p�|���S���̕��т�
			�Q�@�P
			�R�@�S
	�ƂȂ��Ă���B
	���_�̂h�c�͍�����P�Ƃ��Ď��v���B
*/

// �Q�[�W�P
// ���_�̍ő���W
/*
#define	COND_P1_X1_MAX	( 1664 )
#define	COND_P1_Y1_MAX	( 2986 )
#define	COND_P1_X2_MAX	( 2814 )
#define	COND_P1_Y2_MAX	( 1839 )
#define	COND_P1_X3_MAX	( 2366 )
#define	COND_P1_Y3_MAX	( 129 )
#define	COND_P1_X4_MAX	( 1664 )
#define	COND_P1_Y4_MAX	( 1495 )
*/
#define	COND_P1_X1_MAX	( 1664 )
#define	COND_P1_Y1_MAX	( 2986 )
#define	COND_P1_X2_MAX	( 2796 )
#define	COND_P1_Y2_MAX	( 1856 )
#define	COND_P1_X3_MAX	( 2400 )
#define	COND_P1_Y3_MAX	( 167 )
#define	COND_P1_X4_MAX	( 1664 )
#define	COND_P1_Y4_MAX	( 1410 )
// ���_�̍ŏ����W
#define	COND_P1_X1_MIN	( COND_P1_X1_MAX )
#define	COND_P1_Y1_MIN	( COND_P1_Y4_MAX+(COND_P1_Y1_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X2_MIN	( COND_P1_X4_MAX+(COND_P1_X2_MAX-COND_P1_X4_MAX)/8 )
#define	COND_P1_Y2_MIN	( COND_P1_Y4_MAX+(COND_P1_Y2_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X3_MIN	( COND_P1_X4_MAX+(COND_P1_X3_MAX-COND_P1_X4_MAX)/8 )
#define	COND_P1_Y3_MIN	( COND_P1_Y4_MAX+(COND_P1_Y3_MAX-COND_P1_Y4_MAX)/8 )
#define	COND_P1_X4_MIN	( COND_P1_X4_MAX )
#define	COND_P1_Y4_MIN	( COND_P1_Y4_MAX )

// �Q�[�W�Q
// ���_�̍ő���W
/*
#define	COND_P2_X1_MAX	( 546 )
#define	COND_P2_Y1_MAX	( 1876 )
#define	COND_P2_X2_MAX	( 1704 )
#define	COND_P2_Y2_MAX	( 2989 )
#define	COND_P2_X3_MAX	( 1704 )
#define	COND_P2_Y3_MAX	( 1495 )
#define	COND_P2_X4_MAX	( 992 )
#define	COND_P2_Y4_MAX	( 129 )
*/
#define	COND_P2_X1_MAX	( 575 )
#define	COND_P2_Y1_MAX	( 1856 )
#define	COND_P2_X2_MAX	( 1704 )
#define	COND_P2_Y2_MAX	( 2986 )
#define	COND_P2_X3_MAX	( 1704 )
#define	COND_P2_Y3_MAX	( 1410 )
#define	COND_P2_X4_MAX	( 960 )
#define	COND_P2_Y4_MAX	( 167 )
// ���_�̍ŏ����W
#define	COND_P2_X1_MIN	( COND_P2_X3_MAX+(COND_P2_X1_MAX-COND_P2_X3_MAX)/8 )
#define	COND_P2_Y1_MIN	( COND_P2_Y3_MAX+(COND_P2_Y1_MAX-COND_P2_Y3_MAX)/8 )
#define	COND_P2_X2_MIN	( COND_P2_X2_MAX )
#define	COND_P2_Y2_MIN	( COND_P2_Y3_MAX+(COND_P2_Y2_MAX-COND_P2_Y3_MAX)/8 )
#define	COND_P2_X3_MIN	( COND_P2_X3_MAX )
#define	COND_P2_Y3_MIN	( COND_P2_Y3_MAX )
#define	COND_P2_X4_MIN	( COND_P2_X3_MAX+(COND_P2_X4_MAX-COND_P2_X3_MAX)/8 )
#define	COND_P2_Y4_MIN	( COND_P2_Y3_MAX+(COND_P2_Y4_MAX-COND_P2_Y3_MAX)/8 )

// �Q�[�W�R
// ���_�̍ő���W
#define	COND_P3_X1_MAX	( COND_P2_X1_MAX )
#define	COND_P3_Y1_MAX	( COND_P2_Y1_MAX )
#define	COND_P3_X2_MAX	( COND_P2_X3_MAX )
#define	COND_P3_Y2_MAX	( COND_P2_Y3_MAX )
#define	COND_P3_X3_MAX	( COND_P1_X3_MAX )
#define	COND_P3_Y3_MAX	( COND_P1_Y3_MAX )
#define	COND_P3_X4_MAX	( COND_P2_X4_MAX )
#define	COND_P3_Y4_MAX	( COND_P2_Y4_MAX )
// ���_�̍ŏ����W
#define	COND_P3_X1_MIN	( COND_P3_X2_MAX+(COND_P3_X1_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y1_MIN	( COND_P3_Y2_MAX+(COND_P3_Y1_MAX-COND_P3_Y2_MAX)/8 )
#define	COND_P3_X2_MIN	( COND_P3_X2_MAX )
#define	COND_P3_Y2_MIN	( COND_P3_Y2_MAX )
#define	COND_P3_X3_MIN	( COND_P3_X2_MAX+(COND_P3_X3_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y3_MIN	( COND_P3_Y2_MAX+(COND_P3_Y3_MAX-COND_P3_Y2_MAX)/8 )
#define	COND_P3_X4_MIN	( COND_P3_X2_MAX+(COND_P3_X4_MAX-COND_P3_X2_MAX)/8 )
#define	COND_P3_Y4_MIN	( COND_P3_Y2_MAX+(COND_P3_Y4_MAX-COND_P3_Y2_MAX)/8 )

// �Q�[�W�S
// ���_�̍ő���W
#define	COND_P4_X1_MAX	( COND_P1_X4_MAX )
#define	COND_P4_Y1_MAX	( COND_P1_Y4_MAX )
#define	COND_P4_X2_MAX	( COND_P1_X2_MAX )
#define	COND_P4_Y2_MAX	( COND_P1_Y2_MAX )
#define	COND_P4_X3_MAX	( COND_P1_X3_MAX )
#define	COND_P4_Y3_MAX	( COND_P1_Y3_MAX )
#define	COND_P4_X4_MAX	( COND_P2_X4_MAX )
#define	COND_P4_Y4_MAX	( COND_P2_Y4_MAX )
// ���_�̍ŏ����W
#define	COND_P4_X1_MIN	( COND_P4_X1_MAX )
#define	COND_P4_Y1_MIN	( COND_P4_Y1_MAX )
#define	COND_P4_X2_MIN	( COND_P4_X1_MAX+(COND_P4_X2_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y2_MIN	( COND_P4_Y1_MAX+(COND_P4_Y2_MAX-COND_P4_Y1_MAX)/8 )
#define	COND_P4_X3_MIN	( COND_P4_X1_MAX+(COND_P4_X3_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y3_MIN	( COND_P4_Y1_MAX+(COND_P4_Y3_MAX-COND_P4_Y1_MAX)/8 )
#define	COND_P4_X4_MIN	( COND_P4_X1_MAX+(COND_P4_X4_MAX-COND_P4_X1_MAX)/8 )
#define	COND_P4_Y4_MIN	( COND_P4_Y1_MAX+(COND_P4_Y4_MAX-COND_P4_Y1_MAX)/8 )

#define	COND_PRM_MAX	( 50 )	// �p�����[�^�ő�l

// �P�p�����[�^������̃T�C�Y�v�Z�}�N��
#define	PRM_SIZ(max,min)	( FX_F32_TO_FX16( FX_FX16_TO_F32(max-min)/COND_PRM_MAX ) )

// �\�����W�v�Z�p�p�����[�^
typedef struct {
	VecFx16	max;	// �ő���W
	VecFx16	min;	// �ŏ����W
	VecFx16	siz;	// �P������̃T�C�Y
}CONDITION_VTX_CALC;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void NutsTagVBlank( void * work );

static void NutsTagVramBankSet(void);
static void NutsTagBgSet( GF_BGL_INI * ini );
static void NutsTagBgExit( GF_BGL_INI * ini );
static void NutsTagBgGraphicSet( NTAG_WORK * wk );
static void NutsTagAlphaSet(void);
static void NutsTagMsgManCreate( NTAG_WORK * wk );
static void NutsTagMsgManDelete( NTAG_WORK * wk );
static void NutsTagBmpWinSet( NTAG_WORK * wk );
static void NutsTagBmpWinExit( GF_BGL_BMPWIN * win );
static void NutsGraphicSet( NTAG_WORK * wk );
static void NTAG_BmpPut( NTAG_WORK * wk, u8 seq );
static void NTAG_BmpPutAll( NTAG_WORK * wk );

static int SeqInFunc( NTAG_WORK * wk );
static int SeqMainFunc( NTAG_WORK * wk );
static int SeqChangeFunc( NTAG_WORK * wk );
static u8 SeqOutFunc( NTAG_WORK * wk );

static u32 NextTagGet( u32 * tbl, u32 now, s32 mv );
static void TagChange( NTAG_WORK * wk );

static void NTAG_3DInit(void);
static void NTAG_3DMain( NTAG_WORK * wk );
static void NTAG_3DRelease( NTAG_WORK * wk );
static void NTAG_CameraInit( NTAG_WORK * wk );
static void NTAG_ConditionParamInit( NTAG_WORK * wk );
static void NTAG_ConditionParamMake( NTAG_WORK * wk );
static void NTAG_ConditionPlus( NTAG_WORK * wk );
static void ConditionGagePut( NTAG_CONDISION_VTX * vtx );
static void ConditionParamPlus( VecFx16 * p, VecFx16 * m );
static void ConditionMoveMake( VecFx16 * now, VecFx16 * max, VecFx16 * move );
static void ConditionMaxMake( const CONDITION_VTX_CALC * cnst, VecFx16 * make, u8 prm );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================

// BMP�f�[�^
static const BMPWIN_DAT NutsTagBmpData[] =
{
	{	// �u���̂݃^�O�v
		BMP_NUTS_TITLE_FRM, BMP_NUTS_TITLE_PX, BMP_NUTS_TITLE_PY,
		BMP_NUTS_TITLE_SX, BMP_NUTS_TITLE_SY, BMP_NUTS_TITLE_PAL, BMP_NUTS_TITLE_CGX
	},
	{	// �؂̎���
		BMP_NUTS_NAME_FRM, BMP_NUTS_NAME_PX, BMP_NUTS_NAME_PY,
		BMP_NUTS_NAME_SX, BMP_NUTS_NAME_SY, BMP_NUTS_NAME_PAL, BMP_NUTS_NAME_CGX
	},
	{	// ���F���炢
		BMP_KARAI_FRM, BMP_KARAI_PX, BMP_KARAI_PY,
		BMP_KARAI_SX, BMP_KARAI_SY, BMP_KARAI_PAL, BMP_KARAI_CGX
	},
	{	// ���F���Ԃ�
		BMP_SIBUI_FRM, BMP_SIBUI_PX, BMP_SIBUI_PY,
		BMP_SIBUI_SX, BMP_SIBUI_SY, BMP_SIBUI_PAL, BMP_SIBUI_CGX
	},
	{	// ���F���܂�
		BMP_AMAI_FRM, BMP_AMAI_PX, BMP_AMAI_PY,
		BMP_AMAI_SX, BMP_AMAI_SY, BMP_AMAI_PAL, BMP_AMAI_CGX
	},
	{	// ���F�ɂ���
		BMP_NIGAI_FRM, BMP_NIGAI_PX, BMP_NIGAI_PY,
		BMP_NIGAI_SX, BMP_NIGAI_SY, BMP_NIGAI_PAL, BMP_NIGAI_CGX
	},
	{	// ���F�����ς�
		BMP_SUPPAI_FRM, BMP_SUPPAI_PX, BMP_SUPPAI_PY,
		BMP_SUPPAI_SX, BMP_SUPPAI_SY, BMP_SUPPAI_PAL, BMP_SUPPAI_CGX
	},
	{	// �u���������v
		BMP_SIZE_FRM, BMP_SIZE_PX, BMP_SIZE_PY,
		BMP_SIZE_SX, BMP_SIZE_SY, BMP_SIZE_PAL, BMP_SIZE_CGX
	},
	{	// �傫���l
		BMP_SIZ_NUM_FRM, BMP_SIZ_NUM_PX, BMP_SIZ_NUM_PY,
		BMP_SIZ_NUM_SX, BMP_SIZ_NUM_SY, BMP_SIZ_NUM_PAL, BMP_SIZ_NUM_CGX
	},
	{	// �u�������v
		BMP_HARD_FRM, BMP_HARD_PX, BMP_HARD_PY,
		BMP_HARD_SX, BMP_HARD_SY, BMP_HARD_PAL, BMP_HARD_CGX
	},
	{	// �d���l
		BMP_HARD_NUM_FRM, BMP_HARD_NUM_PX, BMP_HARD_NUM_PY,
		BMP_HARD_NUM_SX, BMP_HARD_NUM_SY, BMP_HARD_NUM_PAL, BMP_HARD_NUM_CGX
	},
	{	// ����
		BMP_INFO_FRM, BMP_INFO_PX, BMP_INFO_PY,
		BMP_INFO_SX, BMP_INFO_SY, BMP_INFO_PAL, BMP_INFO_CGX
	}
};

// �R���f�B�V�����i���j�Q�[�W�f�[�^
static const CONDITION_VTX_CALC	ConPrm[][4] =
{
	{	// �Q�[�W�P
		{	// ����
			{ COND_P1_X1_MAX, COND_P1_Y1_MAX, 0 },
			{ COND_P1_X1_MIN, COND_P1_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P1_X1_MAX,COND_P1_X1_MIN),PRM_SIZ(COND_P1_Y1_MAX,COND_P1_Y1_MIN),0 }
		},
		{	// �E��
			{ COND_P1_X2_MAX, COND_P1_Y2_MAX, 0 },
			{ COND_P1_X2_MIN, COND_P1_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P1_X2_MAX,COND_P1_X2_MIN),PRM_SIZ(COND_P1_Y2_MAX,COND_P1_Y2_MIN),0 }
		},
		{	// �E��
			{ COND_P1_X3_MAX, COND_P1_Y3_MAX, 0 },
			{ COND_P1_X3_MIN, COND_P1_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P1_X3_MAX,COND_P1_X3_MIN),PRM_SIZ(COND_P1_Y3_MAX,COND_P1_Y3_MIN),0 }
		},
		{	// ����
			{ COND_P1_X4_MAX, COND_P1_Y4_MAX, 0 },
			{ COND_P1_X4_MIN, COND_P1_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P1_X4_MAX,COND_P1_X4_MIN),PRM_SIZ(COND_P1_Y4_MAX,COND_P1_Y4_MIN),0 }
		}
	},
	{	// �Q�[�W�Q
		{	// ����
			{ COND_P2_X1_MAX, COND_P2_Y1_MAX, 0 },
			{ COND_P2_X1_MIN, COND_P2_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P2_X1_MAX,COND_P2_X1_MIN),PRM_SIZ(COND_P2_Y1_MAX,COND_P2_Y1_MIN),0 }
		},
		{	// �E��
			{ COND_P2_X2_MAX, COND_P2_Y2_MAX, 0 },
			{ COND_P2_X2_MIN, COND_P2_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P2_X2_MAX,COND_P2_X2_MIN),PRM_SIZ(COND_P2_Y2_MAX,COND_P2_Y2_MIN),0 }
		},
		{	// �E��
			{ COND_P2_X3_MAX, COND_P2_Y3_MAX, 0 },
			{ COND_P2_X3_MIN, COND_P2_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P2_X3_MAX,COND_P2_X3_MIN),PRM_SIZ(COND_P2_Y3_MAX,COND_P2_Y3_MIN),0 }
		},
		{	// ����
			{ COND_P2_X4_MAX, COND_P2_Y4_MAX, 0 },
			{ COND_P2_X4_MIN, COND_P2_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P2_X4_MAX,COND_P2_X4_MIN),PRM_SIZ(COND_P2_Y4_MAX,COND_P2_Y4_MIN),0 }
		}
	},
	{	// �Q�[�W�R
		{	// ����
			{ COND_P3_X1_MAX, COND_P3_Y1_MAX, 0 },
			{ COND_P3_X1_MIN, COND_P3_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P3_X1_MAX,COND_P3_X1_MIN),PRM_SIZ(COND_P3_Y1_MAX,COND_P3_Y1_MIN),0 }
		},
		{	// �E��
			{ COND_P3_X2_MAX, COND_P3_Y2_MAX, 0 },
			{ COND_P3_X2_MIN, COND_P3_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P3_X2_MAX,COND_P3_X2_MIN),PRM_SIZ(COND_P3_Y2_MAX,COND_P3_Y2_MIN),0 }
		},
		{	// �E��
			{ COND_P3_X3_MAX, COND_P3_Y3_MAX, 0 },
			{ COND_P3_X3_MIN, COND_P3_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P3_X3_MAX,COND_P3_X3_MIN),PRM_SIZ(COND_P3_Y3_MAX,COND_P3_Y3_MIN),0 }
		},
		{	// ����
			{ COND_P3_X4_MAX, COND_P3_Y4_MAX, 0 },
			{ COND_P3_X4_MIN, COND_P3_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P3_X4_MAX,COND_P3_X4_MIN),PRM_SIZ(COND_P3_Y4_MAX,COND_P3_Y4_MIN),0 }
		}
	},
	{	// �Q�[�W�S
		{	// ����
			{ COND_P4_X1_MAX, COND_P4_Y1_MAX, 0 },
			{ COND_P4_X1_MIN, COND_P4_Y1_MIN, 0 },
			{ PRM_SIZ(COND_P4_X1_MAX,COND_P4_X1_MIN),PRM_SIZ(COND_P4_Y1_MAX,COND_P4_Y1_MIN),0 }
		},
		{	// �E��
			{ COND_P4_X2_MAX, COND_P4_Y2_MAX, 0 },
			{ COND_P4_X2_MIN, COND_P4_Y2_MIN, 0 },
			{ PRM_SIZ(COND_P4_X2_MAX,COND_P4_X2_MIN),PRM_SIZ(COND_P4_Y2_MAX,COND_P4_Y2_MIN),0 }
		},
		{	// �E��
			{ COND_P4_X3_MAX, COND_P4_Y3_MAX, 0 },
			{ COND_P4_X3_MIN, COND_P4_Y3_MIN, 0 },
			{ PRM_SIZ(COND_P4_X3_MAX,COND_P4_X3_MIN),PRM_SIZ(COND_P4_Y3_MAX,COND_P4_Y3_MIN),0 }
		},
		{	// ����
			{ COND_P4_X4_MAX, COND_P4_Y4_MAX, 0 },
			{ COND_P4_X4_MIN, COND_P4_Y4_MIN, 0 },
			{ PRM_SIZ(COND_P4_X4_MAX,COND_P4_X4_MIN),PRM_SIZ(COND_P4_Y4_MAX,COND_P4_Y4_MIN),0 }
		}
	}
};


//============================================================================================
//	�v���Z�X�֐�
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F������
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT NutsTagProc_Init( PROC * proc, int * seq )
{
	NTAG_WORK * wk;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();				// HBlank��~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	G2_BlendNone();
	G2S_BlendNone();

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_NUTSTAG, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(NTAG_WORK), HEAPID_NUTSTAG );
	memset( wk, 0, sizeof(NTAG_WORK) );
	wk->dat  = PROC_GetParentWork( proc );
	wk->bgl  = GF_BGL_BglIniAlloc( HEAPID_NUTSTAG );
	wk->nuts = Nuts_DataLoad( wk->dat->now_tag, HEAPID_NUTSTAG );

	APP_WipeStart( APP_WIPE_IN, HEAPID_NUTSTAG );

	NutsTagVramBankSet();				// VRAM�ݒ�
	NutsTagBgSet( wk->bgl );			// BG�ݒ�
	NutsTagBgGraphicSet( wk );			// BG�O���t�B�b�N�Z�b�g
	NutsTagAlphaSet();

	NutsTagMsgManCreate( wk );
	sys_KeyRepeatSpeedSet( 4, 8 );

	InitTPSystem();						// �^�b�`�p�l���V�X�e��������
	InitTPNoBuff(4);

	NutsGraphicSet( wk );

	NutsTagBmpWinSet( wk );				// BMP�E�B���h�E�ݒ�
	NTAG_BmpPutAll( wk );

	NTAG_CameraInit( wk );
	NTAG_ConditionParamInit( wk );

	sys_VBlankFuncChange( NutsTagVBlank, wk );	// VBlank�Z�b�g

//	Snd_DataSetByScene( SND_SCENE_SUB_BAG, 0, 0 );	// �T�E���h�f�[�^���[�h(�o�b�O)(BGM���p��)

	WirelessIconEasyUnion();
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F���C��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT NutsTagProc_Main( PROC * proc, int * seq )
{
	NTAG_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		*seq = SeqInFunc( wk );
		break;

	case SEQ_MAIN:
		*seq = SeqMainFunc( wk );
		break;

	case SEQ_CHANGE:
		*seq = SeqChangeFunc( wk );
		break;

	case SEQ_OUT:
		if( SeqOutFunc( wk ) == TRUE ){
			return PROC_RES_FINISH;
		}
		break;
	}

//	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_INC, 1 );
//	GF_BGL_ScrollReq( wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_INC, 1 );

	NTAG_3DMain( wk );

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �v���Z�X�֐��F�I��
 *
 * @param	proc	�v���Z�X�f�[�^
 * @param	seq		�V�[�P���X
 *
 * @return	������
 */
//--------------------------------------------------------------------------------------------
PROC_RESULT NutsTagProc_End( PROC * proc, int * seq )
{
	NTAG_WORK * wk  = PROC_GetWork( proc );

	NutsTagBmpWinExit( wk->win );	// BMP�E�B���h�E�J��
	NutsTagBgExit( wk->bgl );		// BGL�폜
	StopTP();						// �^�b�`�p�l���I��

	NutsTagMsgManDelete( wk );

	NTAG_3DRelease( wk );

	sys_FreeMemoryEz( wk->nuts );

	PROC_FreeWork( proc );					// ���[�N�J��

	sys_VBlankFuncChange( NULL, NULL );		// VBlank�Z�b�g

	sys_DeleteHeap( HEAPID_NUTSTAG );

	G2_BlendNone();

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank����
 *
 * @param	work	���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagVBlank( void * work )
{
	NTAG_WORK * wk = work;

	GF_BGL_VBlankFunc( wk->bgl );

	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * VRAM�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagVramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g

		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g

		GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g

		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g

		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG�ݒ�
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagBgSet( GF_BGL_INI * ini )
{
	{	// BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	NTAG_3DInit();

	{	// NUTS & INFO (BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	{	// FRAME (CHAR)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrollReq( ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, 8 );
	}

	{	// TITLE (CHAR&BMP)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_NUTSTAG );
}

//--------------------------------------------------------------------------------------------
/**
 * BG���
 *
 * @param	ini		BGL�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagBgExit( GF_BGL_INI * ini )
{
	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, VISIBLE_OFF );

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );

	sys_FreeMemory( HEAPID_NUTSTAG, ini );
}


//--------------------------------------------------------------------------------------------
/**
 * �O���t�B�b�N�f�[�^�Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagBgGraphicSet( NTAG_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_NTAG_GRA, NARC_ntag_gra_kinomi_bg_NCGR,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_NUTSTAG );
	ArcUtil_ScrnSet(
		ARC_NTAG_GRA, NARC_ntag_gra_kinomi_bg_NSCR,
		wk->bgl, GF_BGL_FRAME2_M, 0, 0, 0, HEAPID_NUTSTAG );
	ArcUtil_ScrnSet(
		ARC_NTAG_GRA, NARC_ntag_gra_kinomi_bg02_NSCR,
		wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_NUTSTAG );
	ArcUtil_PalSet(
		ARC_NTAG_GRA, NARC_ntag_gra_kinomi_bg_NCLR, PALTYPE_MAIN_BG, 0, 0, HEAPID_NUTSTAG );

	{	// �؂̎��̊G���X�N���[���ɓW�J
		u16	* buf;
		u32	i;

		buf = (u16 *)sys_AllocMemory( HEAPID_NUTSTAG, 8*8*2 );

		for( i=0; i<8*8; i++ ){
			buf[i] = (NUTS_GRA_PAL<<12) + NUTS_GRA_CGX + i;
		}
		GF_BGL_ScrWrite(
			wk->bgl, NUTS_GRA_FRM, buf, NUTS_GRA_PX, NUTS_GRA_PY, NUTS_GRA_SX, NUTS_GRA_SY );

		sys_FreeMemoryEz( buf );
		GF_BGL_LoadScreenReq( wk->bgl, NUTS_GRA_FRM );
	}

	SystemFontPaletteLoad( PALTYPE_MAIN_BG, NTAG_SYSFONT_PAL*0x20, HEAPID_NUTSTAG );
}

//--------------------------------------------------------------------------------------------
/**
 * �������ݒ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagAlphaSet(void)
{
	G2_SetBlendAlpha(
		GX_BLEND_PLANEMASK_BG0,
		GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3, 23, 8 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagMsgManCreate( NTAG_WORK * wk )
{
	wk->mman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_kinomi_tag_dat,HEAPID_NUTSTAG );
	wk->nfnt = NUMFONT_Create( 15, 2, FBMP_COL_NULL, HEAPID_NUTSTAG );
	wk->wset = WORDSET_Create( HEAPID_NUTSTAG );
}

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�֘A�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagMsgManDelete( NTAG_WORK * wk )
{
	MSGMAN_Delete( wk->mman );
	NUMFONT_Delete( wk->nfnt );
	WORDSET_Delete( wk->wset );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagBmpWinSet( NTAG_WORK * wk )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->win[i], &NutsTagBmpData[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�폜
 *
 * @param	win		BMP�E�B���h�E�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsTagBmpWinExit( GF_BGL_BMPWIN * win )
{
	u32	i;

	for( i=0; i<WIN_MAX; i++ ){
		GF_BGL_BmpWinDel( &win[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �Œ蕶���𒆉��ɕ\��
 *
 * @param	wk		���[�N
 * @param	widx	�E�B���h�E�C���f�b�N�X
 * @param	midx	���b�Z�[�W�C���f�b�N�X
 * @param	col		�J���[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpStrPut( NTAG_WORK * wk, u32 widx, u32 midx, u32 col )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	siz;

	win = &wk->win[widx];
	str = MSGMAN_AllocString( wk->mman, midx );
	siz = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str,
		(GF_BGL_BmpWinGet_SizeX(win)*8-siz)/2, 0, MSG_NO_PUT, col, NULL );
	STRBUF_Delete( str );
	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���̂݃^�O�v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpTitlePut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_NUTS_TITLE], TITLE_BACK_COL );
	NTAG_BmpStrPut( wk, WIN_NUTS_TITLE, mes_kinomi_tag_01_01, PCOL_TITLE );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���炢�v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpKaraiPut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_KARAI], 0 );
	NTAG_BmpStrPut( wk, WIN_KARAI, mes_kinomi_tag_02_01, PCOL_N_WHITE );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���Ԃ��v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpSibuiPut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_SIBUI], 0 );
	NTAG_BmpStrPut( wk, WIN_SIBUI, mes_kinomi_tag_02_02, PCOL_N_WHITE );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���܂��v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpAmaiPut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_AMAI], 0 );
	NTAG_BmpStrPut( wk, WIN_AMAI, mes_kinomi_tag_02_03, PCOL_N_WHITE );
}

//--------------------------------------------------------------------------------------------
/**
 * �u�ɂ����v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNigaiPut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_NIGAI], 0 );
	NTAG_BmpStrPut( wk, WIN_NIGAI, mes_kinomi_tag_02_04, PCOL_N_WHITE );
}

//--------------------------------------------------------------------------------------------
/**
 * �u�����ς��v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpSuppaiPut( NTAG_WORK * wk )
{
	GF_BGL_BmpWinDataFill( &wk->win[WIN_SUPPAI], 0 );
	NTAG_BmpStrPut( wk, WIN_SUPPAI, mes_kinomi_tag_02_05, PCOL_N_WHITE );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎����\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsNamePut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;

	win = &wk->win[WIN_NUTS_NAME];

	GF_BGL_BmpWinDataFill( win, 0 );

	NUMFONT_WriteMark( wk->nfnt, NUMFONT_MARK_NO, win, 0, NAME_NO_PY );

	str = MSGMAN_AllocString( wk->mman, mes_kinomi_tag_03_01 );
	exp = STRBUF_Create( (2+1)*2, HEAPID_NUTSTAG );	// (2��+EOM_)x2(���[�J���C�Y�p�Ɉꉞ)
	WORDSET_RegisterNumber(
		wk->wset, 0, wk->dat->now_tag+1, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, NUMFONT_MARK_WIDTH, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	str = NutsNameGetAlloc( wk->dat->now_tag, HEAPID_NUTSTAG );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, NUTS_NAME_PX, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �����\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsInfoPut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win = &wk->win[WIN_INFO];

	GF_BGL_BmpWinDataFill( win, 0 );

	str = NutsInfoGetAlloc( wk->dat->now_tag, HEAPID_NUTSTAG );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_BLACK, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �u�������v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsHardPut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win  = &wk->win[WIN_HARD];

	GF_BGL_BmpWinDataFill( win, 0 );

	str = MSGMAN_AllocString( wk->mman, mes_kinomi_tag_05_01 );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �d���l�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsHardNumPut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	u32	hard;

	win  = &wk->win[WIN_HARD_NUM];

	GF_BGL_BmpWinDataFill( win, 0 );

	hard = Nuts_ParamGet( wk->nuts, NUTS_PRM_HARDNESS );
	if( hard != 0 ){ hard--; }
	str  = MSGMAN_AllocString( wk->mman, mes_kinomi_tag_05_02+hard );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, HARD_PX, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �u���������v�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsSizePut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;

	win  = &wk->win[WIN_SIZE];

	GF_BGL_BmpWinDataFill( win, 0 );

	str = MSGMAN_AllocString( wk->mman, mes_kinomi_tag_04_01 );
	GF_STR_PrintColor( win, FONT_SYSTEM, str, 0, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * �傫���l�\��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpNutsSizeNumPut( NTAG_WORK * wk )
{
	GF_BGL_BMPWIN * win;
	STRBUF * str;
	STRBUF * exp;
	u32	size;

	win  = &wk->win[WIN_SIZE_NUM];

	GF_BGL_BmpWinDataFill( win, 0 );

	size = Nuts_ParamGet( wk->nuts, NUTS_PRM_SIZE );
	str  = MSGMAN_AllocString( wk->mman, mes_kinomi_tag_04_02 );
	exp  = STRBUF_Create( 32, HEAPID_NUTSTAG );
	WORDSET_RegisterNumber(
		wk->wset, 0, size/10, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber(
		wk->wset, 1, size%10, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	WORDSET_ExpandStr( wk->wset, exp, str );
	GF_STR_PrintColor(
		win, FONT_SYSTEM, exp, SIZE_PX, 0, MSG_NO_PUT, PCOL_N_WHITE, NULL );
	STRBUF_Delete( str );
	STRBUF_Delete( exp );

	GF_BGL_BmpWinOnVReq( win );
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�\��
 *
 * @param	wk		���[�N
 * @param	seq		�V�[�P���X
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpPut( NTAG_WORK * wk, u8 seq )
{
	switch( seq ){
	case 0:
		NTAG_BmpTitlePut( wk );
		break;
	case 1:
		NTAG_BmpKaraiPut( wk );
		break;
	case 2:
		NTAG_BmpNutsNamePut( wk );
		break;
	case 3:
		NTAG_BmpSuppaiPut( wk );
		NTAG_BmpSibuiPut( wk );
		break;
	case 4:
		NTAG_BmpAmaiPut( wk );
		NTAG_BmpNigaiPut( wk );
		break;
	case 5:
		NTAG_BmpNutsSizePut( wk );
		NTAG_BmpNutsSizeNumPut( wk );
		break;
	case 6:
		NTAG_BmpNutsHardPut( wk );
		NTAG_BmpNutsHardNumPut( wk );
		break;
	case 7:
		NTAG_BmpNutsInfoPut( wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP�\���i�S�āj
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_BmpPutAll( NTAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BMP_PUT_SEQ_MAX; i++ ){
		NTAG_BmpPut( wk, (u8)i );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F������
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int SeqInFunc( NTAG_WORK * wk )
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG2, 16, 0 );
		return SEQ_MAIN;
	}
	return SEQ_IN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�R���g���[��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int SeqMainFunc( NTAG_WORK * wk )
{
	u32	next;

	if( sys.cont & PAD_KEY_UP ){
		next = NextTagGet( wk->dat->tag_flg, wk->dat->now_tag, -1 );
		if( wk->dat->now_tag != next ){
			wk->dat->now_tag = next;
			wk->blend_cnt = 0;
			wk->blend_flg = 0;

			if( wk->dat->cur == 3 && wk->dat->scr != 0 ){
				wk->dat->scr--;
			}else{
				wk->dat->cur--;
			}

			return SEQ_CHANGE;
		}
		return SEQ_MAIN;
	}
	if( sys.cont & PAD_KEY_DOWN ){
		next = NextTagGet( wk->dat->tag_flg, wk->dat->now_tag, 1 );
		if( wk->dat->now_tag != next ){
			wk->dat->now_tag = next;
			wk->blend_cnt = 0;
			wk->blend_flg = 0;

			if( wk->dat->cur == 5 && wk->dat->scr + 9 < wk->dat->max ){
				wk->dat->scr++;
			}else{
				wk->dat->cur++;
			}

			return SEQ_CHANGE;
		}
		return SEQ_MAIN;
	}

	if( ( sys.trg & PAD_BUTTON_CANCEL ) || ( sys.tp_trg ) ){
		APP_WipeStart( APP_WIPE_OUT, HEAPID_NUTSTAG );
		return SEQ_OUT;
	}
	return SEQ_MAIN;
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�I��
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static u8 SeqOutFunc( NTAG_WORK * wk )
{
	return WIPE_SYS_EndCheck();
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���V�[�P���X�F�^�O�؂�ւ�
 *
 * @param	wk		���[�N
 *
 * @return	�ڍs����V�[�P���X
 */
//--------------------------------------------------------------------------------------------
static int SeqChangeFunc( NTAG_WORK * wk )
{
	int	seq = SEQ_CHANGE;

	if( wk->blend_flg == 0 ){
		wk->blend_cnt += 4;
		if( wk->blend_cnt == 16 ){
			wk->blend_flg = 1;
		}
	}else if( wk->blend_flg == 1 ){
		TagChange( wk );
		wk->blend_flg = 2;
	}else{
		wk->blend_cnt -= 4;
		if( wk->blend_cnt == 0 ){
			wk->blend_flg = 0;
			seq = SEQ_MAIN;
		}
	}
	G2_ChangeBlendAlpha( 16-wk->blend_cnt, wk->blend_cnt );

	return seq;
}


//--------------------------------------------------------------------------------------------
/**
 * �؂̎��O���t�B�b�N�]��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NutsGraphicSet( NTAG_WORK * wk )
{
	ArcUtil_BgCharSet(
		ARC_NTAG_GRA, NutsCgxArcGet(wk->dat->now_tag),
		wk->bgl, NUTS_GRA_FRM, NUTS_GRA_CGX, 0, 0, HEAPID_NUTSTAG );
	ArcUtil_PalSet(
		ARC_NTAG_GRA, NutsPalArcGet(wk->dat->now_tag),
		PALTYPE_MAIN_BG, NUTS_GRA_PAL*0x20, 0x20, HEAPID_NUTSTAG );
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��̊G�̃L�����̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�؂̎��ԍ�
 *
 * @return	�L�����̃A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32	NutsCgxArcGet( u32 id )
{
	return NARC_ntag_gra_kinomi_001_NCGR + id;
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��̊G�̃L�����̃A�[�J�C�u�C���f�b�N�X�擾�i�A�C�e���ԍ��j
 *
 * @param	item	�A�C�e���ԍ�
 *
 * @return	�L�����̃A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 NutsCgxArcGet_Item( u32 item )
{
	return NutsCgxArcGet( item - NUTS_START_ITEMNUM );
}


//--------------------------------------------------------------------------------------------
/**
 * �؂̎��̊G�̃p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�؂̎��ԍ�
 *
 * @return	�p���b�g�̃A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32	NutsPalArcGet( u32 id )
{
	return NARC_ntag_gra_kinomi_001_NCLR + id;
}

//--------------------------------------------------------------------------------------------
/**
 * �؂̎��̊G�̃p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾�i�A�C�e���ԍ��j
 *
 * @param	item	�A�C�e���ԍ�
 *
 * @return	�p���b�g�̃A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 NutsPalArcGet_Item( u32 item )
{
	return NutsPalArcGet( item - NUTS_START_ITEMNUM );
}


//--------------------------------------------------------------------------------------------
/**
 * ���̃^�O���擾
 *
 * @param	tbl		�\���e�[�u��
 * @param	now		�\�����̃^�OID
 * @param	mv		�؂�ւ�����
 *
 * @return	���̃^�OID
 */
//--------------------------------------------------------------------------------------------
static u32 NextTagGet( u32 * tbl, u32 now, s32 mv )
{
	s32	i = (s32)now;

	if( mv < 0 ){
		if( now != 0 ){
			while(1){
				i -= 1;
				if( TagPutFlagGet( tbl, (u16)i ) == TRUE ){
					now = (u32)i;
					mv++;
					if( mv == 0 ){ break; }
				}
				if( i == 0 ){ break; }
			}
		}
	}else{
		if( now != NUTS_TAG_MAX ){
			while(1){
				i += 1;
				if( TagPutFlagGet( tbl, (u16)i ) == TRUE ){
					now = (u16)i;
					mv--;
					if( mv == 0 ){ break; }
				}
				if( i == NUTS_TAG_MAX ){ break; }
			}
		}
	}

	return now;
}

//--------------------------------------------------------------------------------------------
/**
 * �^�O�؂�ւ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TagChange( NTAG_WORK * wk )
{
	sys_FreeMemoryEz( wk->nuts );
	wk->nuts = Nuts_DataLoad( wk->dat->now_tag, HEAPID_NUTSTAG );
	NTAG_BmpPutAll( wk );

	NutsGraphicSet( wk );

	NTAG_ConditionParamMake( wk );

	GF_BGL_LoadScreenReq( wk->bgl, NUTS_GRA_FRM );
}


//============================================================================================
//	3D�֘A
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 3D�֘A������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_3DInit(void)
{
	// �������iNITRO-SDK�̃T���v������j
	G3X_Init();
	G3X_InitMtxStack();
	G3X_SetShading( GX_SHADING_TOON );
	G3X_AlphaTest( FALSE, 0 );
	G3X_AlphaBlend( TRUE );
	G3X_AntiAlias( TRUE );
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, 0, 0, 0 );
	G3X_SetClearColor( 0, 0, 0x7fff, 63, FALSE );
    G3_SwapBuffers( GX_SORTMODE_AUTO, GX_BUFFERMODE_Z );
	G3_ViewPort( 0, 0, 255, 191 );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority( 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * 3D�֘A���C��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_3DMain( NTAG_WORK * wk )
{
	GF_G3X_Reset();
	GFC_CameraLookAt();

	G3_MtxMode( GX_MTXMODE_PROJECTION );
	G3_Identity();
	G3_MtxMode( GX_MTXMODE_POSITION_VECTOR );
	G3_Identity();

	ConditionGagePut( wk->cvtx );

	NTAG_ConditionPlus( wk );

	G3_SwapBuffers( GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z );
}

//--------------------------------------------------------------------------------------------
/**
 * 3D�֘A�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_3DRelease( NTAG_WORK * wk )
{
	GFC_FreeCamera( wk->camera );	// �J�����폜
}

//--------------------------------------------------------------------------------------------
/**
 * �J�����ݒ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_CameraInit( NTAG_WORK * wk )
{
	VecFx32	camera_pos = {0,0,0x10000};
	CAMERA_ANGLE angle = {0,0,0};
	fx32	distance   = 0x10000;
	u16		perspway   = 0x05c1;

	wk->camera = GFC_AllocCamera( HEAPID_NUTSTAG );

	GFC_InitCameraCDA( &camera_pos, distance, &angle, perspway, GF_CAMERA_ORTHO, wk->camera );
	GFC_SetCameraClip( 0, FX32_CONST(100), wk->camera );	// �N���b�v�ݒ�(near-far)
	GFC_PurgeCameraTarget( wk->camera );
	GFC_AttachCamera( wk->camera );
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W�\��
 *
 * @param	vtx		�|���S���\�����W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
//static u8 d_vtx_flg;
//static u8 d_vtx_pos;
static void ConditionGagePut( NTAG_CONDISION_VTX * vtx )
{
	G3_PolygonAttr(
		GX_LIGHTMASK_NONE,			// no lights
		GX_POLYGONMODE_MODULATE,	// modulation mode
		GX_CULL_NONE,				// cull none
		18,							// polygon ID(0 - 63)
		24,							// alpha(0 - 31)
		0 );						// OR of GXPolygonAttrMisc's value

    G3_Begin( GX_BEGIN_QUADS );
    {
		u32	i;

		for( i=0; i<4; i++ ){
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].lt.x, vtx[i].lt.y, vtx[i].lt.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].rt.x, vtx[i].rt.y, vtx[i].rt.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].ru.x, vtx[i].ru.y, vtx[i].ru.z );
			G3_Color( GX_RGB(8,31,15) );
			G3_Vtx( vtx[i].lu.x, vtx[i].lu.y, vtx[i].lu.z );
		}
	}
    G3_End();

/*
	G3_PolygonAttr(
		GX_LIGHTMASK_NONE,			// no lights
		GX_POLYGONMODE_MODULATE,	// modulation mode
		GX_CULL_NONE,				// cull none
		18,							// polygon ID(0 - 63)
		20,							// alpha(0 - 31)
		0 );						// OR of GXPolygonAttrMisc's value

	if( sys.trg & PAD_BUTTON_SELECT ){
		d_vtx_flg = (d_vtx_flg+1)&3;
		OS_Printf( "VTX ID : %d\n", d_vtx_flg );
		return;
	}

	if( sys.trg & PAD_BUTTON_A ){
		d_vtx_pos = (d_vtx_pos+1)&3;
		OS_Printf( "POL ID : %d\n", d_vtx_pos );
		return;
	}

	if( sys.trg & PAD_BUTTON_START ){
		OS_Printf( "LT : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].lt.x, vtx[d_vtx_pos].lt.y, vtx[d_vtx_pos].lt.z );
		OS_Printf( "RT : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].rt.x, vtx[d_vtx_pos].rt.y, vtx[d_vtx_pos].rt.z );
		OS_Printf( "RU : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].ru.x, vtx[d_vtx_pos].ru.y, vtx[d_vtx_pos].ru.z );
		OS_Printf( "LU : x = %d, y = %d, z = %d\n", vtx[d_vtx_pos].lu.x, vtx[d_vtx_pos].lu.y, vtx[d_vtx_pos].lu.z );
//		d_vtx_flg = (d_vtx_flg+1)&3;
		return;
	}

	if( sys.cont & PAD_BUTTON_L ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.x -= 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.x -= 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.x -= 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.x -= 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_R ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.x += 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.x += 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.x += 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.x += 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_X ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.y -= 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.y -= 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.y -= 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.y -= 1;
		}
		return;
	}

	if( sys.cont & PAD_BUTTON_Y ){
		if( d_vtx_flg == 0 ){
			vtx[d_vtx_pos].lt.y += 1;
		}else if( d_vtx_flg == 1 ){
			vtx[d_vtx_pos].rt.y += 1;
		}else if( d_vtx_flg == 2 ){
			vtx[d_vtx_pos].ru.y += 1;
		}else if( d_vtx_flg == 3 ){
			vtx[d_vtx_pos].lu.y += 1;
		}
		return;
	}

    G3_Begin( GX_BEGIN_QUADS );
    {
		u32	i;

		for( i=d_vtx_pos; i<d_vtx_pos+1; i++ ){
			if( d_vtx_flg == 0 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].lt.x, vtx[i].lt.y, vtx[i].lt.z );
			if( d_vtx_flg == 1 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].rt.x, vtx[i].rt.y, vtx[i].rt.z );
			if( d_vtx_flg == 2 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].ru.x, vtx[i].ru.y, vtx[i].ru.z );
			if( d_vtx_flg == 3 ){
				G3_Color( GX_RGB(0,0,0) );
			}else{
				G3_Color( GX_RGB(8,31,15) );
			}
			G3_Vtx( vtx[i].lu.x, vtx[i].lu.y, vtx[i].lu.z );
		}
	}
    G3_End();
*/
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����W�ύX
 *
 * @param	p		�\�����W
 * @param	m		�ύX�l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionParamPlus( VecFx16 * p, VecFx16 * m )
{
	p->x += m->x;
	p->y += m->y;
	p->z += m->z;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W����
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_ConditionPlus( NTAG_WORK * wk )
{
	u32	i;

	if( wk->con_mv_cnt == 4 ){ return; }

	if( wk->con_mv_cnt == 3 ){
		for( i=0; i<4; i++ ){
			wk->cvtx[i] = wk->mvtx[i];
		}
	}else{
		for( i=0; i<4; i++ ){
			ConditionParamPlus( &wk->cvtx[i].lt, &wk->pvtx[i].lt );
			ConditionParamPlus( &wk->cvtx[i].rt, &wk->pvtx[i].rt );
			ConditionParamPlus( &wk->cvtx[i].lu, &wk->pvtx[i].lu );
			ConditionParamPlus( &wk->cvtx[i].ru, &wk->pvtx[i].ru );
		}
	}

	wk->con_mv_cnt++;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_ConditionParamInit( NTAG_WORK * wk )
{
	u32	i;

	wk->cvtx[0].lt = ConPrm[0][3].min;
	wk->cvtx[0].rt = ConPrm[0][3].min;
	wk->cvtx[0].lu = ConPrm[0][3].min;
	wk->cvtx[0].ru = ConPrm[0][3].min;

	wk->cvtx[1].lt = ConPrm[1][2].min;
	wk->cvtx[1].rt = ConPrm[1][2].min;
	wk->cvtx[1].lu = ConPrm[1][2].min;
	wk->cvtx[1].ru = ConPrm[1][2].min;

	wk->cvtx[2].lt = ConPrm[2][1].min;
	wk->cvtx[2].rt = ConPrm[2][1].min;
	wk->cvtx[2].lu = ConPrm[2][1].min;
	wk->cvtx[2].ru = ConPrm[2][1].min;

	wk->cvtx[3].lt = ConPrm[3][0].min;
	wk->cvtx[3].rt = ConPrm[3][0].min;
	wk->cvtx[3].lu = ConPrm[3][0].min;
	wk->cvtx[3].ru = ConPrm[3][0].min;

	NTAG_ConditionParamMake( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W�ő�l�Z�b�g
 *
 * @param	cnst	���W�f�[�^
 * @param	make	�쐬�ꏊ
 * @param	prm		�p�����[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionMaxMake( const CONDITION_VTX_CALC * cnst, VecFx16 * make, u8 prm )
{
	if( prm == 0xff ){
		*make = cnst->max;
	}else if( prm == 0 ){
		*make = cnst->min;
	}else{
		make->x = cnst->min.x + cnst->siz.x * prm;
		make->y = cnst->min.y + cnst->siz.y * prm;
		make->z = cnst->min.z + cnst->siz.z * prm;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W����l�Z�b�g
 *
 * @param	now		���݂̍��W
 * @param	max		�ő���W
 * @param	move	�P������̓���l
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConditionMoveMake( VecFx16 * now, VecFx16 * max, VecFx16 * move )
{
	move->x = FX_F32_TO_FX16( FX_FX16_TO_F32(max->x-now->x)/4 );
	move->y = FX_F32_TO_FX16( FX_FX16_TO_F32(max->y-now->y)/4 );
	move->z = FX_F32_TO_FX16( FX_FX16_TO_F32(max->z-now->z)/4 );
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����Q�[�W����p�����[�^�쐬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NTAG_ConditionParamMake( NTAG_WORK * wk )
{
	u32	i;

	// �ő�l���Z�b�g
	ConditionMaxMake( &ConPrm[0][0], &wk->mvtx[0].lt, Nuts_ParamGet(wk->nuts,NUTS_PRM_KARAI) );
	ConditionMaxMake( &ConPrm[0][1], &wk->mvtx[0].rt, Nuts_ParamGet(wk->nuts,NUTS_PRM_SIBUI) );
	ConditionMaxMake( &ConPrm[0][2], &wk->mvtx[0].ru, Nuts_ParamGet(wk->nuts,NUTS_PRM_AMAI) );
	ConditionMaxMake( &ConPrm[0][3], &wk->mvtx[0].lu, 0 );

	ConditionMaxMake( &ConPrm[1][0], &wk->mvtx[1].lt, Nuts_ParamGet(wk->nuts,NUTS_PRM_SUPPAI) );
	ConditionMaxMake( &ConPrm[1][1], &wk->mvtx[1].rt, Nuts_ParamGet(wk->nuts,NUTS_PRM_KARAI) );
	ConditionMaxMake( &ConPrm[1][2], &wk->mvtx[1].ru, 0 );
	ConditionMaxMake( &ConPrm[1][3], &wk->mvtx[1].lu, Nuts_ParamGet(wk->nuts,NUTS_PRM_NIGAI) );

	ConditionMaxMake( &ConPrm[2][0], &wk->mvtx[2].lt, Nuts_ParamGet(wk->nuts,NUTS_PRM_SUPPAI) );
	ConditionMaxMake( &ConPrm[2][1], &wk->mvtx[2].rt, 0 );
	ConditionMaxMake( &ConPrm[2][2], &wk->mvtx[2].ru, Nuts_ParamGet(wk->nuts,NUTS_PRM_AMAI) );
	ConditionMaxMake( &ConPrm[2][3], &wk->mvtx[2].lu, Nuts_ParamGet(wk->nuts,NUTS_PRM_NIGAI) );

	ConditionMaxMake( &ConPrm[3][0], &wk->mvtx[3].lt, 0 );
	ConditionMaxMake( &ConPrm[3][1], &wk->mvtx[3].rt, Nuts_ParamGet(wk->nuts,NUTS_PRM_SIBUI) );
	ConditionMaxMake( &ConPrm[3][2], &wk->mvtx[3].ru, Nuts_ParamGet(wk->nuts,NUTS_PRM_AMAI) );
	ConditionMaxMake( &ConPrm[3][3], &wk->mvtx[3].lu, Nuts_ParamGet(wk->nuts,NUTS_PRM_NIGAI) );

	// �v���X�l���v�Z
	for( i=0; i<4; i++ ){
		ConditionMoveMake( &wk->cvtx[i].lt, &wk->mvtx[i].lt, &wk->pvtx[i].lt );
		ConditionMoveMake( &wk->cvtx[i].rt, &wk->mvtx[i].rt, &wk->pvtx[i].rt );
		ConditionMoveMake( &wk->cvtx[i].lu, &wk->mvtx[i].lu, &wk->pvtx[i].lu );
		ConditionMoveMake( &wk->cvtx[i].ru, &wk->mvtx[i].ru, &wk->pvtx[i].ru );
	}

	wk->con_mv_cnt = 0;
}
