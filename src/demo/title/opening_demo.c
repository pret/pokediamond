//============================================================================================
/**
 * @file	opening_demo.c
 * @brief	�I�[�v�j���O�f��
 * @author	Nozomu Saito
 * @date	2006.05.31
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "system/brightness.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/main.h"

#include "op_demo.naix"
#include "titledemo.naix"

#include "field/field.h"
#include "demo/title.h"
#include "opening_kira_obj.h"
#include "opening_demo_obj.h"
#include "op_poke_cutin.h"

#include "op_frame_def.h"

#ifdef PM_DEBUG
//#define COPYRIGHT_SKIP		//<<�L���ɂ���ƒ��쌠�����X�L�b�v�ł��܂�
#endif

#define PAL_ONE_SIZE	(2)		//�Q�o�C�g

//�V�[��1
#define	COPY_LIGHT_FRAME	(GF_BGL_FRAME1_M)
#define	GAME_FREAK_LOGO_M_FRAME	(GF_BGL_FRAME2_M)
#define	GAME_FREAK_LOGO_S_FRAME	(GF_BGL_FRAME2_S)
#define	BACK_BASE_M_FRAME	(GF_BGL_FRAME3_M)
#define	BACK_BASE_S_FRAME	(GF_BGL_FRAME3_S)

#define BLD_MASK_COPY_LIGHT		(GX_BLEND_PLANEMASK_BG1)
#define BLD_MASK_GF_LOGO_M		(GX_BLEND_PLANEMASK_BG2)
#define BLD_MASK_BACK_BASE_M	(GX_BLEND_PLANEMASK_BG3)
#define BLD_MASK_GF_LOGO_S		(GX_BLEND_PLANEMASK_BG2)
#define BLD_MASK_BACK_BASE_S	(GX_BLEND_PLANEMASK_BG3)

#define COPY_LIGHT_BLD_IN_COUNT_MAX	(6)	//�u�����h���鑬�x6�t���ɂP��ύX
#define COPY_LIGHT_BLD_COUNT_MAX	(4)	//�u�����h���鑬�x4�t���ɂP��ύX
#define OPDEMO_BRIGHTNESS_SYNC	(18)


//�V�[��2
#define TITLE_LOGO_WHITE_IN_SYNC	(8)
#define BG_ON	(1)
#define BG_OFF	(2)
#define G256_FRAME		(GF_BGL_FRAME3_M)
#define TOWN_FRAME		(GF_BGL_FRAME1_M)
#define SKY_FRAME		(GF_BGL_FRAME2_M)
#define WB_TITLE_FRAME	(GF_BGL_FRAME0_S)
#define OPD_BTL_PAL_NUM	(7)	//1�f�[�^������̐퓬�a�f�p���b�g�{��
#define TOWN_BG_SPEED	(-1)	//��a�f�̈ړ��X�s�[�h
#define SKY_BG_SPEED	(1)	//��a�f�̈ړ��X�s�[�h
#define BATTLE_BG_SPEED	(-16)	//�o�g���a�f�X�N���[���X�s�[�h

#define SCENE2_DISP_CHG_SYNC	(4)		//�V�[��2�o�g���ʐ؂�ւ��u���b�N�C���A�E�g�X�s�[�h
#define SCENE2_TOWN_SCROLL_MARGIN	(24)
#define SCENE2_SKY_SCROLL_MARGIN	(3)
#define SCENE2_BATTLE_SCROLL_MARGIN	(1)

#define OP_MAP_BLOCK_MAX	(6)
#define SONOO_TOWN_HEIGHT	(FX32_ONE*16*5)
#define SCENE2_KIRA_MAX		(16)
#define	SCENE2_KIRA_MARGIN1	(4)
#define	SCENE2_KIRA_MARGIN2	(16)

//�V�[��3
#define MT_CLOUD_FRAME	(GF_BGL_FRAME1_M)
#define MT_TENGAN_FRAME	(GF_BGL_FRAME2_M)
#define MT_LAKE_FRAME	(GF_BGL_FRAME3_M)
#define MT_THUNDER_FRAME	(GF_BGL_FRAME0_M)
#define MT_CLOUD_SUB_FRAME	(GF_BGL_FRAME1_S)

#define TENGAN_WH_OUT_SYNC	(18)
#define TENGAN_AFF_VAL	(0x400)
#define TENGAN_AFF_VAL2	(0x800)
//#define LAKE_AFF_VAL	(0x40)
#define AFF_LIMIT_1	(0x3000)
//#define LAVE_AFF_LIMIT	(0xa80)

#define SCENE3_START_IN_SYNC	(120)		//�V�[��3�J�n�u���b�N�C���X�s�[�h

typedef enum {
	BTL_PAL_NAETORU,
	BTL_PAL_HIKOZARU,
	BTL_PAL_POTTYAMA,
	BTL_PAL_RIVAL,
	BTL_PAL_MAX
};

typedef enum{
	DISP_MAIN,
	DISP_SUB,
};

typedef struct BLOCK_3D_DATA_tag
{
	NNSG3dRenderObj			RenderObj;
	NNSG3dResFileHeader* ResFile;
}BLOCK_3D_DATA;

typedef struct SCENE2_3D_DATA_tag
{
	void			*TexFile;		//�e�N�X�`���[�t�@�C�����̂ւ̃|�C���^
	NNSG3dResTex	*Texture;
	GF_CAMERA_PTR CameraPtr;		//�J����
	BLOCK_3D_DATA	Block[OP_MAP_BLOCK_MAX];
}SCENE2_3D_DATA;

typedef struct SCENE3_THUNDER_DATA_tag
{
	u8 Request;
	u8 NowPalTblNo;	//�p���b�g�e�[�u���ԍ�
	u8 Margin;		//�p���b�g�ύX�Ԋu
	u8 Counter;
}SCENE3_THUNDER_DATA;


//�R�s�[���C�g�`�Q�[�t�����S�܂ł̃f�[�^�\����
typedef struct SCENE1_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;			//init�V�[�P���X�ʉ߂������H
	u8 LoadOK;			//load�V�[�P���X�ʉ߂������H
	u16 Wait;
	u8 Alpha;
	u8 Counter;
	u8 BlendEnd;
	GF_BGL_INI *bgl;
	TCB_PTR	BlendTcb;
	OPD_K_G_MNG_PTR KiraGeneMngPtr;
	u8 *SkipOKPtr;
}SCENE1_WORK;

//�^�C�g���`�o�g���܂ł̃f�[�^�\����
typedef struct SCENE2_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;				//init�V�[�P���X�ʉ߂������H
	u8 LoadOK;				//load�V�[�P���X�ʉ߂������H
	u8 Load3DOK;			//load3D�V�[�P���X��ʉ߂������H
	u8 Disp3DFlg;			//��B�t���O
	u8 KiraMargin;
	u8 KiraMarginCore;
	int BG_ScrollMargin;	//�X�N���[���Z�b�g�Ԋu
	GF_BGL_INI *bgl;
	OPD_OBJ_PTR	ObjWorkPtr;
	OPD_KIRA_DATLST_PTR KiraListPtr;
	OPD_SSM_PTR OpSsmPtr;
	void *PalDataBuf[BTL_PAL_MAX];		//�p���b�g�f�[�^�S��
	NNSG2dPaletteData *PalData[BTL_PAL_MAX];	//�p���b�g�f�[�^�S��
	SCENE2_3D_DATA Data;
}SCENE2_WORK;

//�e���K���U���V�[���̃f�[�^�\����
typedef struct SCENE3_WORK_tag
{
	u8 Seq;
	u8 SceneSeq;
	u8 InitOK;			//init�V�[�P���X�ʉ߂������H
	u8 LoadOK;			//load�V�[�P���X�ʉ߂������H
//	u8 TenganAffMargin;	//�e���K���U���X�P�[���ύX�Ԋu
//	u8 LakeAffMargin;	//�΃X�P�[���ύX�Ԋu
	fx32 TenganSc;		//�e���K���U���X�P�[��
	fx32 LakeSc;		//�΃X�P�[��
	
	GF_BGL_INI *bgl;
	void *PalDataBuf;		//�p���b�g�f�[�^
	NNSG2dPaletteData *PalData;	//�p���b�g�f�[�^
	SCENE3_THUNDER_DATA ThunderData;
}SCENE3_WORK;

///	�^�C�g���S�̐���p���[�N�\����
typedef struct OPENING_DEMO_WORK_tag
{
	int	heapID;
	int FrameCounter;
	BOOL SkipFlg;

	GF_BGL_INI*		bgl;	// BG�}�l�[�W��
	GF_G3DMAN*		g3Dman;	// 3D�}�l�[�W��

	u32 RandSeed;

	SCENE1_WORK		SceneWork1;
	SCENE2_WORK		SceneWork2;
	SCENE3_WORK		SceneWork3;

	u8 SkipOK;

}OPENING_DEMO_WORK;

extern const PROC_DATA TitleProcData;
extern void		Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);
FS_EXTERN_OVERLAY( title );

static PROC_RESULT OpDemo_Init(PROC * proc, int * seq);
static PROC_RESULT OpDemo_Main(PROC * proc, int * seq);
static PROC_RESULT OpDemo_Exit(PROC * proc, int * seq);

static BOOL GemeFreakLogoScene(OPENING_DEMO_WORK * wk);
static BOOL Title_3D_BattleScene(OPENING_DEMO_WORK * wk);
static BOOL MtTenganScene(OPENING_DEMO_WORK * wk);

static void SetUp3D(void);
static void Scene_LoadPal(	NNSG2dPaletteData *inPalData, const u8 inDispMS,
							const u8 inPalNum, const u8 inStart, const u8 inDst);

//=================================================================================================
//
// �o�q�n�b��`�e�[�u��
//
//=================================================================================================
const PROC_DATA OpDemoProcData = {
	OpDemo_Init,
	OpDemo_Main,
	OpDemo_Exit,
	NO_OVERLAY_ID
};

const int ModelArcTbl[OP_MAP_BLOCK_MAX] = {
	NARC_op_demo_titlemap05_20_nsbmd,
	NARC_op_demo_titlemap05_21_nsbmd,
	NARC_op_demo_titlemap06_20_nsbmd,
	NARC_op_demo_titlemap06_19_nsbmd,
	NARC_op_demo_titlemap06_18_nsbmd,
	NARC_op_demo_titlemap06_17_nsbmd, 
};

//�J�����ݒ�
static const GF_CAMERA_PARAM CameraData = {
	0x29aec1,
	{
		-0x29fe,0,0
	},
	GF_CAMERA_PERSPECTIV,
	0x05c1,
	0	//dummy
};

//�G�b�W�}�[�L���O�e�[�u��
static const GXRgb gEdgeColor[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};

//���C�g�p�����[�^
const VecFx32 LightVec[4] = {
	{-2043,-3548,110},
	{0,0,0},
	{0,0,4096},
	{0,0,4096},
};

const GXRgb LightColor[4] = {
	GX_RGB(24,24,18),
	GX_RGB(0,0,0),
	GX_RGB(2,2,12),
	GX_RGB(31,31,31),	
};

//----------------------------------
//�u�q�`�l�ݒ�
//----------------------------------
static void OpDemo_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_80_EF,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0_G				// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}
//----------------------------------
//�u�q�`�l�ݒ�i�^�C�g���`3�c�`�o�g���j
//----------------------------------
static void OpDemo_Scene2_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_32_FG,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E				// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//�u�q�`�l�ݒ�i�e���K���U���j
//----------------------------------
static void OpDemo_Scene3_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_256_AB,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,	// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_NONE,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_NONE,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_NONE,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_NONE				// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//
//	�Q�c�a�f���������I��
//
//----------------------------------
static void OpDemo2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BG���C�u�����p�������m��
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BG�V�X�e���ݒ�
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}

	
	{	// �R�s�[���C�g �a�f�ݒ�(���C��1)
		GF_BGL_BGCNT_HEADER CopyLight_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//�v���C�I���e�B0
		};
		GF_BGL_BGControlSet( wk->bgl, COPY_LIGHT_FRAME, &CopyLight_Data, GF_BGL_MODE_TEXT );
	}

	{	// �Q�[�t�����S �a�f�ݒ�(���C��2)
		GF_BGL_BGCNT_HEADER GF_Logo_m_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//�v���C�I���e�B1
		};
		GF_BGL_BGControlSet( wk->bgl, GAME_FREAK_LOGO_M_FRAME, &GF_Logo_m_Data, GF_BGL_MODE_TEXT );
	}

	{	// �x�[�X�w�i �a�f�ݒ�(���C��3)
		GF_BGL_BGCNT_HEADER GF_Back_m_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//�v���C�I���e�B2
		};
		GF_BGL_BGControlSet( wk->bgl, BACK_BASE_M_FRAME, &GF_Back_m_Data, GF_BGL_MODE_TEXT );
	}

	{	// �Q�[�t�����S �a�f�ݒ�(�T�u2)
		GF_BGL_BGCNT_HEADER GF_Logo_s_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//�v���C�I���e�B1
		};
		GF_BGL_BGControlSet( wk->bgl, GAME_FREAK_LOGO_S_FRAME, &GF_Logo_s_Data, GF_BGL_MODE_TEXT );
	}

	{	// �x�[�X�w�i �a�f�ݒ�(�T�u3)
		GF_BGL_BGCNT_HEADER GF_Back_s_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x8000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//�v���C�I���e�B2
		};
		GF_BGL_BGControlSet( wk->bgl, BACK_BASE_S_FRAME, &GF_Back_s_Data, GF_BGL_MODE_TEXT );
	}

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x0000 );	//�w�i�F�������i���C����ʁj
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//�w�i�F�������i�T�u��ʁj
}

//----------------------------------
//
//	�Q�c�a�f���������I��
//
//----------------------------------
static void OpDemo_Scene2_2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BG���C�u�����p�������m��
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BG�V�X�e���ݒ�
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}

	//�X�N���[���x�[�X�I�t�Z�b�g��0x10000���炷
	GX_SetBGScrOffset(GX_BGSCROFFSET_0x10000);

	{	// 256��� �a�f�ݒ�(���C��3)
		GF_BGL_BGCNT_HEADER G256_Data = {
			0, 0, 0x2000, 0,
			GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE			//�v���C�I���e�B3
		};
		GF_BGL_BGControlSet( wk->bgl, G256_FRAME, &G256_Data, GF_BGL_MODE_TEXT );
	}

	{	// �X �a�f�ݒ�(���C��1)
		GF_BGL_BGCNT_HEADER Town_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,		//�X�Ƌ󓯂��L����
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//�v���C�I���e�B1
		};
		GF_BGL_BGControlSet( wk->bgl, TOWN_FRAME, &Town_Data, GF_BGL_MODE_TEXT );
	}

	{	// �� �a�f�ݒ�(���C��2)
		GF_BGL_BGCNT_HEADER Sky_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x14000,		//�X�Ƌ󓯂��L����
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//�v���C�I���e�B2
		};
		GF_BGL_BGControlSet( wk->bgl, SKY_FRAME, &Sky_Data, GF_BGL_MODE_TEXT );
	}

	{	// �Q�[�t�����S �a�f�ݒ�(�T�u0)
		GF_BGL_BGCNT_HEADER GF_Logo_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//�v���C�I���e�B0
		};
		GF_BGL_BGControlSet( wk->bgl, WB_TITLE_FRAME, &GF_Logo_Data, GF_BGL_MODE_TEXT );
	}

///	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, 0x0000 );	//�w�i�F�������i���C����ʁj
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//�w�i�F�������i�T�u��ʁj
}

//----------------------------------
//
//	�Q�c�a�f������
//
//----------------------------------
static void OpDemo_Scene3_2DBgSet( OPENING_DEMO_WORK* wk )
{
	//BG���C�u�����p�������m��
	wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);

	{	// BG�V�X�e���ݒ�
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_2,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}
	
	//�X�N���[���x�[�X�I�t�Z�b�g��0x10000���炷
	GX_SetBGScrOffset(GX_BGSCROFFSET_0x10000);	
	
	{	// �e���K���U���_ �a�f�ݒ�(���C��1)
		GF_BGL_BGCNT_HEADER Cloud_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xc000, GX_BG_CHARBASE_0x00000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE			//�v���C�I���e�B3
		};
		GF_BGL_BGControlSet( wk->bgl, MT_CLOUD_FRAME, &Cloud_Data, GF_BGL_MODE_TEXT );
	}

	{	// �e���K���U���R �a�f�ݒ�(���C��2)
		GF_BGL_BGCNT_HEADER Tengan_Data = {
			0, 0, 0x1000, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xc800, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE			//�v���C�I���e�B1
		};
		GF_BGL_BGControlSet( wk->bgl, MT_TENGAN_FRAME, &Tengan_Data, GF_BGL_MODE_AFFINE );
	}

	{	// �e���K���U���� �a�f�ݒ�(���C��3)
		GF_BGL_BGCNT_HEADER Lake_Data = {
			0, 0, 0x4000, 0,
			GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//�v���C�I���e�B0
		};
		GF_BGL_BGControlSet( wk->bgl, MT_LAKE_FRAME, &Lake_Data, GF_BGL_MODE_AFFINE );
	}
	
	{	// �e���K���U���� �a�f�ݒ�(���C��0)
		GF_BGL_BGCNT_HEADER Thunder_Data = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xb800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE			//�v���C�I���e�B2
		};
		GF_BGL_BGControlSet( wk->bgl, MT_THUNDER_FRAME, &Thunder_Data, GF_BGL_MODE_TEXT );
	}

	{	// �e���K���U���_ �a�f�ݒ�(�T�u1)
		GF_BGL_BGCNT_HEADER Cloud_SubData = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE			//�v���C�I���e�B0
		};
		GF_BGL_BGControlSet( wk->bgl, MT_CLOUD_SUB_FRAME, &Cloud_SubData, GF_BGL_MODE_TEXT );
	}

	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0x0000 );	//�w�i�F�������i�T�u��ʁj
}

//----------------------------------
//
//	�R�c���������I��
//
//----------------------------------
static void OpDemo3D_Init( OPENING_DEMO_WORK* wk )
{
	NNSGfdTexKey texKey;
	NNSGfdPlttKey plttKey;
	u32 tex_addrs, pltt_addrs;
	
	wk->g3Dman = GF_G3DMAN_Init(wk->heapID, 
			GF_G3DMAN_LNK, GF_G3DTEX_128K, GF_G3DMAN_LNK, GF_G3DPLT_64K, SetUp3D );

	
	// �|�P�����f�[�^�]���̈��Vram���m�ہ��]���A�h���X�ƃT�C�Y��ݒ�	
	texKey = NNS_GfdAllocTexVram(0x2000*4, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(0x20*4, FALSE, NNS_GFD_ALLOC_FROM_LOW);

	tex_addrs = NNS_GfdGetTexKeyAddr(texKey);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(plttKey);
	OS_TPrintf("�I�[�v�j���O�|�P�����p�Ɋm�ۂ����e�N�X�`��Vram�̐擪�A�h���X��%d\n", tex_addrs);
	OS_TPrintf("�I�[�v�j���O�|�P�����p�Ɋm�ۂ����p���b�gVram�̐擪�A�h���X��%d\n", pltt_addrs);
}

static void SetUp3D(void)
{
	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
    G2_SetBG0Priority(0);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend( TRUE );		// �A���t�@�u�����h�@�I��
	G3X_EdgeMarking( TRUE );
	G3X_SetEdgeColorTable(gEdgeColor);
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
static void Scene1_VBlankFunc(void* work)
{
	
	OPENING_DEMO_WORK* wk = work;
//	GF_BGL_VBlankFunc(wk->bgl);

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();

}

//----------------------------------
//�u�a�k�`�m�j�֐�
//----------------------------------
static void Scene2_VBlankFunc(void* work)
{
	
	OPENING_DEMO_WORK* wk = work;
//	GF_BGL_VBlankFunc(wk->bgl);

	// �����_�����LOAM�}�l�[�W��Vram�]��
	REND_OAMTrans();

	OPD_Poke_VBlank(wk->SceneWork2.OpSsmPtr);

}

//--------------------------------------------------------------------------------------------
/**
 * �E�B���h�E�ݒ�
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void Scene2_SetWindow(void)
{
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane(	GX_WND_PLANEMASK_BG0|
							GX_WND_PLANEMASK_BG1|
							GX_WND_PLANEMASK_BG2|
							GX_WND_PLANEMASK_BG3|
							GX_WND_PLANEMASK_OBJ, 1 );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, 1 );
	G2_SetWnd0Position( 0, 32, 255, 159 );
}

//----------------------------------
//�o�q�n�b������
//----------------------------------
static PROC_RESULT OpDemo_Init(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk;
	int	heapID;

	heapID = HEAPID_OP_DEMO;

	BrightnessChgInit();
	
	//�}�X�^�[�P�x�������Ă���
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrSet( NULL,NULL );		// HBlank�Z�b�g

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
///	GX_SetVisiblePlane(0);
///	GXS_SetVisiblePlane(0);

	sys_KeyRepeatSpeedSet(4,8);
	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x60000 );

	wk = PROC_AllocWork(proc,sizeof(OPENING_DEMO_WORK),heapID);
	memset(wk,0,sizeof(OPENING_DEMO_WORK));

	wk->heapID = heapID;

	wk->SkipFlg = FALSE;

#ifdef COPYRIGHT_SKIP
	wk->SkipOK = 1;
#else
	//�n�߂̓X�L�b�v�s��
	wk->SkipOK = 0;
#endif
	//�R�c�`��X�C�b�`
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();

	//�����̎�ޔ�
	wk->RandSeed = gf_get_seed();
	
	//����������
	gf_srand(0);

	return	PROC_RES_FINISH;
}

//----------------------------------
//�o�q�n�b���C��
//----------------------------------
static PROC_RESULT OpDemo_Main(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk = PROC_GetWork( proc );
#if 0	
	if (sys.trg & PAD_BUTTON_X){
		OS_Printf("frame:%d\n",wk->FrameCounter);
		GF_ASSERT(0);
	}
#endif
	if ( (wk->SkipOK)&&( (sys.trg & PAD_BUTTON_A)||(sys.trg & PAD_BUTTON_START) ) )
	{
		wk->SkipFlg = TRUE;
		sys.DS_Boot_Flag = FALSE;	//�u�[�g�t���O�Z�b�g
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_WHITE );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_WHITE );
	}

	switch(*seq){
	case 0:
		wk->SceneWork1.SkipOKPtr = &wk->SkipOK;
		(*seq)++;
		break;
	case 1:	
		if ( GemeFreakLogoScene(wk) ){
			//���̃V�[�P���X
			(*seq)++;
		}
		break;
	case 2:
		if ( Title_3D_BattleScene(wk) ){
			//���̃V�[�P���X
			(*seq)++;
		}
		break;
	case 3:
		if ( MtTenganScene(wk) ){
			//���̃V�[�P���X
			(*seq)++;
		}
		break;
	case 4:
		if (wk->FrameCounter >= FM_END){
			return	PROC_RES_FINISH;
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if (wk->SkipFlg){
		OS_Printf("�X�L�b�v�ɂ��A���C���v���Z�X�I��\n");
		return	PROC_RES_FINISH;
	}

	wk->FrameCounter++;
	return	PROC_RES_CONTINUE;
}

static PROC_RESULT OpDemo_Exit(PROC * proc, int * seq)
{
	OPENING_DEMO_WORK * wk = PROC_GetWork( proc );
	//���C�v�̋����I��
	WIPE_SYS_ExeEnd();

	//�����̎한�A
	gf_srand(wk->RandSeed);
	
	PROC_FreeWork( proc );				// ���[�N�J��
	sys_DeleteHeap( HEAPID_OP_DEMO );
	
	Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
	
	return	PROC_RES_FINISH;
}

static void Scene1_Init(OPENING_DEMO_WORK * wk);
static void Scene1_Load(SCENE1_WORK *scene_wk);
static BOOL Scene1_Main(SCENE1_WORK *scene_wk, const int inCounter);
static void Scene1_End(OPENING_DEMO_WORK * wk);
static void TCB_BlendInCopyLight( TCB_PTR tcb, void* work );
static void TCB_BlendOutCopyLight( TCB_PTR tcb, void* work );
static void TCB_BlendInGFLogoM( TCB_PTR tcb, void* work );
static void TCB_BlendInGFLogoS( TCB_PTR tcb, void* work );

//�R�s�[���C�g�E�Q�[�t�����S�̕\���V�[��
static BOOL GemeFreakLogoScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork1.Seq);
	
	if (wk->SkipFlg){
		(*seq) = 3;		//�X�L�b�v���s
	}
	
	switch(*seq){
	case 0:		//������
		Scene1_Init(wk);
		(*seq)++;
		break;
	case 1:			//�O���t�B�b�N���[�h
		Scene1_Load(&wk->SceneWork1);
		(*seq)++;
		break;
	case 2:			//���C��
		if ( Scene1_Main( &wk->SceneWork1, wk->FrameCounter ) ){
			(*seq)++;
		}
		break;
	case 3:			//�I��
		Scene1_End(wk);
		
		return TRUE;
	}
	return FALSE;
}

static void Scene1_Init(OPENING_DEMO_WORK * wk)
{
	OpDemo_VramBankSet();
	OpDemo2DBgSet(wk);
	wk->SceneWork1.bgl = wk->bgl;
	wk->SceneWork1.KiraGeneMngPtr = OPDKira_AllocGeneMng();

	sys_VBlankFuncChange(Scene1_VBlankFunc,(void*)wk);

	wk->SceneWork1.InitOK = 1;	//init�ʉ�
}

static void Scene1_Load(SCENE1_WORK *scene_wk)
{
	//--�Q�[�t�����S�f�[�^���[�h
	//�L����(�P�t�@�C���ɂȂ��Ă�̂œ�ʂɑ���B�����Ă�������ق�����������)
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_NCGR,
						scene_wk->bgl, GAME_FREAK_LOGO_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_NCGR,
						scene_wk->bgl, GAME_FREAK_LOGO_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);	
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_m_NSCR,
						scene_wk->bgl, GAME_FREAK_LOGO_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_s_NSCR,
						scene_wk->bgl, GAME_FREAK_LOGO_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�p���b�g
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_op_demoBG0_NCLR,
						PALTYPE_MAIN_BG, 0, 0, HEAPID_OP_DEMO );
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_op_demoBG0_NCLR,
						PALTYPE_SUB_BG, 0, 0, HEAPID_OP_DEMO );
	
	//--�R�s�[���C�g�f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_cp_light_NCGR,
						scene_wk->bgl, COPY_LIGHT_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_cp_light_NSCR,
						scene_wk->bgl, COPY_LIGHT_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�p���b�g
	ArcUtil_PalSet( ARC_OP_DEMO, NARC_op_demo_cp_light_NCLR,
						PALTYPE_MAIN_BG, 0, PAL_ONE_SIZE*16*1, HEAPID_OP_DEMO );	//�O�ԂɂP�U�F���[�h
	
	//--�x�[�X�w�i���[�h
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_back_NSCR,
						scene_wk->bgl, BACK_BASE_M_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG0_logo_back_NSCR,
						scene_wk->bgl, BACK_BASE_S_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);


	//--�����a�f�ݒ�
	//BG0�E�㉺��ʃQ�[�t�����S��\��
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	//�x�[�X�w�i�ƃR�s�[���C�g���u�����h
	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, 0, 16);

	OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// �u�u�����N�҂�
	//�}�X�^�[�P�x��߂�
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );

	GF_Disp_DispOn();
}

static BOOL Scene1_Main(SCENE1_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);

	KiraGenerateMain(scene_wk->KiraGeneMngPtr, inCounter);
	
	switch(*seq){
	case 0:	//�R�s�[���C�g�u�����h�C��
		scene_wk->Counter = 0;
		scene_wk->Alpha = 0;
		scene_wk->BlendEnd = 0;
		scene_wk->BlendTcb = TCB_Add( TCB_BlendInCopyLight, scene_wk, 0 );
		//�a�f�l�J�n
		Snd_DataSetByScene( SND_SCENE_TITLE, SEQ_TITLE00, 1 );
		(*seq)++;
		break;
	case 1:	//�悫�Ƃ���ŃR�s�[���C�g�u�����h�A�E�g
		if ( (scene_wk->BlendEnd)&&(inCounter >= FM_COPY_LIGHT_OUT) ){
			scene_wk->Counter = 0;
			scene_wk->Alpha = 16;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendOutCopyLight, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 2:	//�Q�[�t�����S�u�����h�C��
		if ( (scene_wk->BlendEnd)&&(inCounter>=FM_FG_LOGO_IN) ){
			//�R�s�[���C�g�ʔ�\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
			//�u�����h�����ݒ�
			G2_SetBlendAlpha( BLD_MASK_GF_LOGO_M, BLD_MASK_BACK_BASE_M, 0, 16);
			G2S_SetBlendAlpha( BLD_MASK_GF_LOGO_S, BLD_MASK_BACK_BASE_S, 0, 16);
			//�Q�[�t�����S�ʕ\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			
			scene_wk->Counter = 0;
			scene_wk->Alpha = 0;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendInGFLogoM, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 3:	//����ʃu�����h�C��
		if ( (scene_wk->BlendEnd) ){
			scene_wk->Counter = 0;
			scene_wk->Alpha = 0;
			scene_wk->BlendEnd = 0;
			scene_wk->BlendTcb = TCB_Add( TCB_BlendInGFLogoS, scene_wk, 0 );
			(*seq)++;
		}
		break;
	case 4:	//����ʏ��ʂ̏��őS���u���b�N�A�E�g
		if ( (scene_wk->BlendEnd)&&(inCounter>=FM_GF_LOGO_OUT) ){
			//���C�v�X�^�[�g	�z���C�g�C��
			WIPE_SYS_Start(	WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 5:
		if ( WIPE_SYS_EndCheck() ){
			return TRUE;
		}
	}
	return FALSE;
}

static void Scene1_End(OPENING_DEMO_WORK * wk)
{
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	
	if (wk->SceneWork1.InitOK){
		//�W�F�l���[�^�[���
		OPDKira_FreeGeneMng(wk->SceneWork1.KiraGeneMngPtr);
		//�a�f�k���
		GF_BGL_BGControlExit( wk->bgl, COPY_LIGHT_FRAME );
		GF_BGL_BGControlExit( wk->bgl, GAME_FREAK_LOGO_M_FRAME );
		GF_BGL_BGControlExit( wk->bgl, GAME_FREAK_LOGO_S_FRAME );
		GF_BGL_BGControlExit( wk->bgl, BACK_BASE_M_FRAME );
		GF_BGL_BGControlExit( wk->bgl, BACK_BASE_S_FRAME );
		sys_FreeMemoryEz( wk->bgl );
		wk->SceneWork1.InitOK = 0;
	}

	//�^�X�N�������Ă���Ȃ�ΏI��
	if (wk->SceneWork1.BlendTcb != NULL){
		GF_ASSERT(wk->SkipFlg);
		OS_Printf("�X�L�b�v�ɂ��ATCB���O���������܂���\n");
		TCB_Delete(wk->SceneWork1.BlendTcb);
		wk->SceneWork1.BlendTcb = NULL;
	}
}

//�R�s�[���C�h�u�����h�C���s�b�a
static void TCB_BlendInCopyLight( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_IN_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);
}

//�R�s�[���C�h�u�����h�A�E�g�s�b�a
static void TCB_BlendOutCopyLight( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha--;
	}

	if (s_work->Alpha == 0){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
		*(s_work->SkipOKPtr) = 1;	//�X�L�b�v����
	}

	G2_SetBlendAlpha( BLD_MASK_COPY_LIGHT, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);

}

//���C����ʂf�e���S�u�����h�C���s�b�a
static void TCB_BlendInGFLogoM( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2_SetBlendAlpha( BLD_MASK_GF_LOGO_M, BLD_MASK_BACK_BASE_M, s_work->Alpha, 16);
}

//�T�u��ʂf�e���S�u�����h�C���s�b�a
static void TCB_BlendInGFLogoS( TCB_PTR tcb, void* work )
{
	SCENE1_WORK *s_work = work;

	s_work->Counter++;
	if (s_work->Counter >= COPY_LIGHT_BLD_COUNT_MAX){
		s_work->Counter = 0;
		s_work->Alpha++;
	}

	if (s_work->Alpha >= 16){
		TCB_Delete(tcb);
		s_work->BlendTcb = NULL;
		s_work->BlendEnd = 1;
	}

	G2S_SetBlendAlpha( BLD_MASK_GF_LOGO_S, BLD_MASK_BACK_BASE_S, s_work->Alpha, 16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

static void Scene2_Init(OPENING_DEMO_WORK * wk);
static void Scene2_Load(SCENE2_WORK *scene_wk);
static void Scene2_Load3D(SCENE2_WORK *scene_wk);
static void Scene2_Disp3D(SCENE2_WORK *scene_wk);
static BOOL Scene2_Main(SCENE2_WORK *scene_wk, const int inCounter);
static void Scene2_ScrollTown(SCENE2_WORK *scene_wk);
static void Scene2_ScrollSky(SCENE2_WORK *scene_wk);
static void Scene2_ScrollBattle(SCENE2_WORK *scene_wk);
static void Scene2_CameraMoveMain(SCENE2_WORK *scene_wk, const int inCounter);
static void Scene2_End(OPENING_DEMO_WORK * wk);

//�^�C�g���\���`3�c�`�o�g���̃V�[��
static BOOL Title_3D_BattleScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork2.Seq);

	if (wk->SkipFlg){
		(*seq) = 4;		//�X�L�b�v���s
	}
	
	switch(*seq){
	case 0:		//������
		Scene2_Init(wk);
		(*seq)++;
		break;
	case 1:			//�O���t�B�b�N���[�h
		Scene2_Load(&wk->SceneWork2);
		(*seq)++;
		break;
	case 2:
		Scene2_Load3D(&wk->SceneWork2);
		wk->SceneWork2.Disp3DFlg = 1;	//��B�t���O�I��
		(*seq)++;
		break;
	case 3:			//���C��
		if ( Scene2_Main( &wk->SceneWork2, wk->FrameCounter ) ){
			(*seq)++;
		}
		OPD_Obj_DrawActor( wk->SceneWork2.ObjWorkPtr );
		if (wk->SceneWork2.Disp3DFlg){
			Scene2_Disp3D(&wk->SceneWork2);
		}else{
			OPD_Poke_Main( wk->SceneWork2.OpSsmPtr );
		}
		break;
	case 4:			//�I��
		Scene2_End(wk);
		return TRUE;
	}
	return FALSE;
}

static void Scene2_Init(OPENING_DEMO_WORK * wk)
{
	u8 i;
	int obj_work_size;
	int ssm_size;
	OpDemo_Scene2_VramBankSet();
	OpDemo_Scene2_2DBgSet(wk);
	OpDemo3D_Init(wk);

	obj_work_size = OPD_Obj_GetWorkSize();
	ssm_size = OPD_Poke_GetSSMSize();
	
	wk->SceneWork2.ObjWorkPtr = sys_AllocMemory(HEAPID_OP_DEMO, obj_work_size);
	wk->SceneWork2.KiraListPtr = OPDKira_CreateList(SCENE2_KIRA_MAX);
	wk->SceneWork2.OpSsmPtr = sys_AllocMemory(HEAPID_OP_DEMO, ssm_size);
	memset(wk->SceneWork2.ObjWorkPtr, 0, obj_work_size);
	memset(wk->SceneWork2.OpSsmPtr, 0, ssm_size);

	wk->SceneWork2.KiraMarginCore = SCENE2_KIRA_MARGIN1;
	
	OPD_Poke_Init(wk->SceneWork2.OpSsmPtr);

	wk->SceneWork2.bgl = wk->bgl;

	//�R�c�`��X�C�b�`	�������C���ɂ���
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();

	for(i=0;i<4;i++){
		//���C�g�Z�b�g
		NNS_G3dGlbLightVector(i,
							LightVec[i].x,
							LightVec[i].y,
							LightVec[i].z);
		NNS_G3dGlbLightColor(i, LightColor[i]);
	}

	//�O���[�o���X�e�[�g��������
	NNS_G3dGlbMaterialColorDiffAmb(
				GX_RGB(16,16,16),
				GX_RGB(10,12,12),
				FALSE);
	
	NNS_G3dGlbMaterialColorSpecEmi(
				GX_RGB(18,18,18),
				GX_RGB(14,14,14),
				FALSE);
	
	// �|���S���A�g���r���[�g
	NNS_G3dGlbPolygonAttr(
				13,		//<���C�g1�ȊO�L���i1101�j
				GX_POLYGONMODE_MODULATE,
				GX_CULL_BACK,
				0,
				31,
				GX_POLYGON_ATTR_MISC_FOG);
	
	sys_VBlankFuncChange(Scene2_VBlankFunc,(void*)wk);

	//�^�C�g�����S�̋P�x���グ�Ă���
	SetBrightness( BRIGHTNESS_WHITE, GX_BLEND_PLANEMASK_BG0, MASK_SUB_DISPLAY );
	
	wk->SceneWork2.InitOK = 1;		//init�ʉ�
}

static void Scene2_End(OPENING_DEMO_WORK * wk)
{	
	u8 i;

	//�E�B���h�E�I�t
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	if (wk->SceneWork2.Load3DOK){
		//�J�����폜
		GFC_PurgeCamera();
		GFC_FreeCamera(wk->SceneWork2.Data.CameraPtr);
		//���f�����O�f�[�^�폜
		for (i=0;i<OP_MAP_BLOCK_MAX;i++){
			sys_FreeMemoryEz(wk->SceneWork2.Data.Block[i].ResFile);
		}
		//�e�N�X�`���폜
		sys_FreeMemoryEz(wk->SceneWork2.Data.TexFile);
		wk->SceneWork2.Load3DOK = 0;
	}

	if (wk->SceneWork2.LoadOK){
		//�A�N�^�[�֘A���
		OPD_Obj_EndCellActor( wk->SceneWork2.ObjWorkPtr );
		//�p���b�g���
		for(i=0;i<BTL_PAL_MAX;i++){
			sys_FreeMemoryEz(wk->SceneWork2.PalDataBuf[i]);
		}
		wk->SceneWork2.LoadOK = 0;
	}

	if (wk->SceneWork2.InitOK){
		//�L���G�t�F�N�g���
		if (wk->SceneWork2.KiraListPtr != NULL){
			OPDKira_FreeList(wk->SceneWork2.KiraListPtr);
			wk->SceneWork2.KiraListPtr = NULL;
		}
		if (wk->SceneWork2.ObjWorkPtr != NULL){
			sys_FreeMemoryEz(wk->SceneWork2.ObjWorkPtr);
			wk->SceneWork2.ObjWorkPtr = NULL;
		}
		if (wk->SceneWork2.OpSsmPtr != NULL){
			//�X�v���C�g�E�p�[�e�B�N�����
			OPD_Poke_End(wk->SceneWork2.OpSsmPtr);
			sys_FreeMemoryEz(wk->SceneWork2.OpSsmPtr);
			wk->SceneWork2.OpSsmPtr = NULL;
		}
	
		//bgl���
		GF_BGL_BGControlExit( wk->bgl, G256_FRAME );
		GF_BGL_BGControlExit( wk->bgl, TOWN_FRAME );
		GF_BGL_BGControlExit( wk->bgl, SKY_FRAME );
		GF_BGL_BGControlExit( wk->bgl, WB_TITLE_FRAME );
		sys_FreeMemoryEz( wk->bgl );

		//3D���
		GF_G3D_Exit( wk->g3Dman );
		wk->SceneWork2.InitOK = 0;
	}

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g	
}

static void Scene2_Load(SCENE2_WORK *scene_wk)
{
	u8 i;
	ARCHANDLE* pal_handle;

	const int pal_arc_idx[BTL_PAL_MAX] = {
		NARC_op_demo_op_demoBG2_btl1_NCLR,
		NARC_op_demo_op_demoBG2_btl2_NCLR,
		NARC_op_demo_op_demoBG2_btl3_NCLR,
		NARC_op_demo_op_demoBG2_btl4_NCLR
	};
	
	//�p���b�g�A�[�J�C�u�n���h���I�[�v��
	pal_handle  = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO);

	for (i=0;i<BTL_PAL_MAX;i++){
		scene_wk->PalDataBuf[i] = ArchiveDataLoadAllocByHandle( pal_handle, pal_arc_idx[i], HEAPID_OP_DEMO );
		if( scene_wk->PalDataBuf[i] != NULL )
		{
			if( NNS_G2dGetUnpackedPaletteData( scene_wk->PalDataBuf[i], &scene_wk->PalData[i] ) == FALSE ){
				sys_FreeMemoryEz( scene_wk->PalData[i] );
				GF_ASSERT(0);
			}
		}else{
			GF_ASSERT(0);
		}
	}
	
	//�n���h���N���[�Y
	ArchiveDataHandleClose( pal_handle );

	//--256�o�g���w�ʃf�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG2_btl_NCGR,
						scene_wk->bgl, G256_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG2_btl_NSCR,
						scene_wk->bgl, G256_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�p���b�g
	Scene_LoadPal(scene_wk->PalData[0], DISP_MAIN, 10, 0, 0);		//10�{���[�h

	//--256�^�C�g���f�[�^���[�h
	{
		int cgxID,palID,scrID;
#if 0		
		if( CasetteVersion == VERSION_DIAMOND ){
			cgxID = NARC_op_demo_d_logo01_NCGR;
			palID = NARC_op_demo_d_logo01_NCLR;
			scrID = NARC_op_demo_d_logo01_NSCR;
		} else {
			cgxID = NARC_op_demo_P_logo01_NCGR;
			palID = NARC_op_demo_P_logo01_NCLR;
			scrID = NARC_op_demo_p_logo01_NSCR;
		}
#endif
		cgxID = NARC_op_demo_g_logo2_NCGR;
		palID = NARC_op_demo_g_logo2_NCLR;
		scrID = NARC_op_demo_g_logo_NSCR;
		
		//�L����
		ArcUtil_BgCharSet(ARC_OP_DEMO, cgxID,
							scene_wk->bgl, WB_TITLE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		//�X�N���[��
		ArcUtil_ScrnSet(ARC_OP_DEMO, scrID,
							scene_wk->bgl, WB_TITLE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

		//�p���b�g
		ArcUtil_PalSet(ARC_OP_DEMO, palID,
							PALTYPE_SUB_BG,0,16*2*8,HEAPID_OP_DEMO);	//�W�{���[�h
	}
	//--��E���f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_NCGR,
						scene_wk->bgl, TOWN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_town_NSCR,
						scene_wk->bgl, TOWN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG1_sky_NSCR,
						scene_wk->bgl, SKY_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//--�A�N�^�[�Z�b�g
	OPD_Obj_InitCellActor( scene_wk->ObjWorkPtr );
	OPD_Obj_SetActor( scene_wk->ObjWorkPtr );
	
	//--�L���L���A�N�^�[�Z�b�g
	OPD_Obj_SetKiraActor( scene_wk->ObjWorkPtr,
						  scene_wk->KiraListPtr );

	//--�����a�f�ݒ�
	//�S����\��
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );

	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );

	scene_wk->LoadOK = 1;		//load�ʉ�
}

static void Scene2_Load3D(SCENE2_WORK *scene_wk)
{
	u8 i;
	ARCHANDLE* handle;
	BOOL status;
	NNSG3dResMdlSet* model_set;
	NNSG3dResMdl *model;
	//�e�N�X�`�����[�h
	scene_wk->Data.TexFile = ArchiveDataLoadMalloc(	ARC_OP_DEMO,
													NARC_op_demo_titlemap_texset_nsbtx,
													HEAPID_OP_DEMO );

	scene_wk->Data.Texture = NNS_G3dGetTex((NNSG3dResFileHeader*) scene_wk->Data.TexFile );	// �e�N�X�`�����\�[�X�擾

	{
		BOOL rc;
		rc = LoadVRAMTexture(scene_wk->Data.Texture);
		GF_ASSERT(rc && "�I�[�v�j���O�F�e�N�X�`����VRAM�m�ێ��s");
	}

	//���̂�j��
	{
		u8* texImgStartAddr;
		u32 newSize;

		GF_ASSERT(scene_wk->Data.Texture->texInfo.ofsTex != 0);
		texImgStartAddr = (u8*)scene_wk->Data.Texture + scene_wk->Data.Texture->texInfo.ofsTex;
		// �q�[�v�̐擪����e�N�X�`���C���[�W�܂ł̃T�C�Y
		newSize = (u32)(texImgStartAddr - (u8*)scene_wk->Data.TexFile);
		sys_CutMemoryBlockSize( scene_wk->Data.TexFile, newSize );
	}

	//�A�[�J�C�u�n���h���I�[�v��
	handle = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO );
	
	for (i=0;i<OP_MAP_BLOCK_MAX;i++){
		//���f�����O�f�[�^�����[�h
		scene_wk->Data.Block[i].ResFile = ArchiveDataLoadAllocByHandle( handle, ModelArcTbl[i], HEAPID_OP_DEMO );

		//�e�N�X�`���o�C���h
		status = BindTexture(scene_wk->Data.Block[i].ResFile, scene_wk->Data.Texture);
		GF_ASSERT(status&&"BindTexture failed");
	
		model_set = NNS_G3dGetMdlSet(scene_wk->Data.Block[i].ResFile);

		GF_ASSERT(model_set->dict.numEntry==1&&"���f���Z�b�g�̒��ɕ������f��������");

		model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(scene_wk->Data.Block[i].ResFile), 0);
		GF_ASSERT(model&&"load failed");
		NNS_G3dRenderObjInit(&scene_wk->Data.Block[i].RenderObj, model);

		//���f�����O�f�[�^�̓O���[�o���X�e�[�g���g�p����
		NNS_G3dMdlUseGlbDiff(model);			// �f�B�t���[�Y
		NNS_G3dMdlUseGlbAmb(model);				// �A���r�G���g
		NNS_G3dMdlUseGlbSpec(model);			// �X�y�L�����[
		NNS_G3dMdlUseGlbEmi(model);				// �G�~�b�V����
	
		NNS_G3dMdlUseGlbLightEnableFlag(model);
	}
	//�n���h���N���[�Y
	ArchiveDataHandleClose( handle );
	
	scene_wk->Data.CameraPtr = GFC_AllocCamera(HEAPID_OP_DEMO);	//�J�����쐬
	{
		VecFx32 target = {0,0,FX32_ONE*16*6};
		//�J�����Z�b�g
		GFC_InitCameraTDA( &target,
			CameraData.Distance,	// ����
			&CameraData.Angle,	//
			CameraData.PerspWay,	// ���ˉe�̊p�x
			CameraData.View,
			FALSE,				//�o�C���h���Ȃ�
			scene_wk->Data.CameraPtr
			);
		GFC_SetCameraPerspWay(0x0981,scene_wk->Data.CameraPtr);

		//�\�m�I�^�E���̍����ɂ��킹��
		{
			VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
			GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
		}

		GFC_AttachCamera(scene_wk->Data.CameraPtr);
	}
	scene_wk->Load3DOK = 1;		//3Dload�ʉ�
	
}

static void Scene2_Disp3D(SCENE2_WORK *scene_wk)
{
	u8 i;
	MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
	VecFx32 trans = {0,0,0};
	GF_G3X_Reset();
	GFC_CameraLookAt();

	for(i=0;i<OP_MAP_BLOCK_MAX;i++){
		simple_3DModelDraw(	&scene_wk->Data.Block[i].RenderObj,
							&trans,
							&rotate_tmp,
							&scale);
	}
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
}

static BOOL Scene2_Main(SCENE2_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);

	if (!scene_wk->KiraMargin){
		Scene2_KiraGenerateMain(scene_wk->KiraListPtr);
	}
	scene_wk->KiraMargin = (scene_wk->KiraMargin+1)%scene_wk->KiraMarginCore;
	
	switch(*seq){
	case 0:	//�^�C�~���O������āA�o�[���I�ƃ|�P�������S
		if (inCounter >= FM_TITLE_LOGO_IN){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
			//�^�C�g�����S�̋P�x�����ɖ߂�
			ChangeBrightnessRequest(TITLE_LOGO_WHITE_IN_SYNC, BRIGHTNESS_NORMAL, BRIGHTNESS_WHITE,
								GX_BLEND_PLANEMASK_BG0, MASK_SUB_DISPLAY);
			(*seq)++;
		}
		break;
	case 1:
/**		
		//�悫�Ƃ���ŉ��ʃz���C�g�A�E�g
		if (inCounter >= FM_TITLE_WHITE_OUT){
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
*/
		//��l���A�j���J�n
		OPD_Obj_OnOffHeroHeroineAnime( scene_wk->ObjWorkPtr, 1 );
		(*seq)++;
		break;
	case 2:
		if (inCounter==FM_KIRA_DISP_START){
			GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
		}

		if ( /*WIPE_SYS_EndCheck()&&*/(inCounter>=FM_SKY_CAMERA_START) ){
			//���C���S���E�n�a�i�\���i���ۂ�3�c�ʂ��������Ȃ�
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0|GX_PLANEMASK_BG1|
										GX_PLANEMASK_BG2, VISIBLE_ON );
			//�z���C�g�C��
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );

			scene_wk->KiraMarginCore = SCENE2_KIRA_MARGIN2;
			
			(*seq)++;
		}
		break;
	case 3:	//�C��������A3�c�J�����ړ��V�[���i����2�c�ʂ̕\���͂��Ă����j
		if ( /*(inCounter>=FM_SKY_CAMERA_START)*/1 ){
			//��B
			Scene2_CameraMoveMain(scene_wk,inCounter);
			//���X���C�h
			OPD_Obj_SlideInBird(scene_wk->ObjWorkPtr, inCounter);
			if (inCounter >= FM_3D_WHITE_OUT){
				//��B�I���z���C�g�A�E�g���N�G�X�g
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 4:
		//��B
		Scene2_CameraMoveMain(scene_wk,inCounter);
		//���X���C�h
		OPD_Obj_SlideInBird(scene_wk->ObjWorkPtr, inCounter);
		//�z���C�g�A�E�g�҂�
		if ( WIPE_SYS_EndCheck()&&(inCounter >= FM_HERO_WALK) ){
			//�j��l���\��
			OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 1 );
			//�E�B���h�E�\��
			Scene2_SetWindow();
			//3D���f���h���[�֐��𖳌�
			scene_wk->Disp3DFlg = 0;
			//�z���C�g�C�����N�G�X�g
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x7fff,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 5:	//��l���j����
		//���X�N���[��
		Scene2_ScrollTown(scene_wk);	
		//�z���C�g�C���҂�
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter >= FM_NAETORU_SETUP){
				//�悫�Ƃ���ŁA�u���b�N�A�E�g����
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 6:	//�u���b�N�A�E�g�����牺�L����
		if ( WIPE_SYS_EndCheck() ){
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
							 GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD,
					         0,0);
			//��E���a�f��\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|GX_PLANEMASK_BG2, VISIBLE_OFF );
			//�o�g���a�f�E3�c�ʕ\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
			//�n�a�i�u���C�g�l�X���Ƃ�
///			G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_BLACK);
			//�j��l���p���b�g�ύX�i���j
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_BLACK);
			//�u���b�N�C������
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 7:	//�i�G�g���J�b�g�C��
		//�o�g���a�f�X�N���[��
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_NAETORU, inCounter) ){
				//�u���b�N�A�E�g����
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;

	case 8:
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter >= FM_RIVAL_SETUP){
				//��l���A�j���J�n
				OPD_Obj_OnOffHeroHeroineAnime( scene_wk->ObjWorkPtr, 1 );
				//�j��l����\��
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 0 );
				//����l���\��
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, 1 );
				//�n�a�i�u���C�g�l�X�߂�
///				G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_NORMAL);
				//�j��l���p���b�g�ύX�i���ɖ߂��j
				OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_NORMAL);
				//�퓬�p���b�g�ύX�i���C�o���j
				Scene_LoadPal(scene_wk->PalData[BTL_PAL_RIVAL], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
				//���C�o���\��
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_RIVAL, 1 );
				//�u���b�N�C������
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 9:	//���C�o���X���C�h�C��
		//�o�g���a�f�X�N���[��
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck()&&(inCounter >= FM_RIVAL_SLIDE_IN) ){
			if ( OPD_Obj_SlideInRival(scene_wk->ObjWorkPtr) ){
				if (inCounter>=FM_HIKOZARU_SETUP){
					//�u���b�N�A�E�g����
					WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
								WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
					(*seq)++;
				}
			}
		}
		break;

	case 10:
		if ( WIPE_SYS_EndCheck() ){
			//�n�a�i�u���C�g�l�X���Ƃ�
///			G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_BLACK);
			//����l���p���b�g�ύX�i���j
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_BLACK);
			//�퓬�p���b�g�ύX(�q�R�U��)
			Scene_LoadPal(scene_wk->PalData[BTL_PAL_HIKOZARU], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
			//���C�o����\��
			OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_RIVAL, 0 );
			//�u���b�N�C������
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 11:	//�q�R�U���J�b�g�C��
		//�o�g���a�f�X�N���[��
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_HIKOZARU, inCounter) ){
				//�u���b�N�A�E�g����
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 12:
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter>FM_HEROINE_SETUP){			
				//�n�a�i�u���C�g�l�X�߂�
///				G2_SetBlendBrightnessExt(PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, 0,0,BRIGHTNESS_NORMAL);
				//����l���p���b�g�ύX�i���ɖ߂��j
				OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_NORMAL);
				//��a�f�\��
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
				//�j��l���\��
				OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HERO, 1 );
				//����l���ʒu�ύX
				OPD_Obj_ChangeHeroinePos( scene_wk->ObjWorkPtr );
				//�A�j���ύX
				OPD_Obj_ChangeHeroHeroineAnime(scene_wk->ObjWorkPtr, 4);
				//�u���b�N�C������
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				scene_wk->BG_ScrollMargin = 0;	//�X�N���[���ɔ���������
				(*seq)++;
			}
		}
		break;		
	case 13:	//���΂�����
		//BG�X�N���[��
		Scene2_ScrollSky(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if (inCounter>FM_POTTYAMA_SETUP){
				//�u���b�N�A�E�g����
				WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
				scene_wk->BG_ScrollMargin = 0;	//�X�N���[���ɔ���������
				(*seq)++;
			}
		}
		break;
	case 14:
		if ( WIPE_SYS_EndCheck() ){
			//��l���p���b�g�ύX
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HERO, CHG_MODE_BLACK);
			OPD_Obj_ChangeCollor(scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, CHG_MODE_BLACK);
			//�퓬�p���b�g�ύX(�|�b�`���})
			Scene_LoadPal(scene_wk->PalData[BTL_PAL_POTTYAMA], DISP_MAIN, OPD_BTL_PAL_NUM, 0, 0);
			//����l����\��
			///OPD_Obj_DispOnOff( scene_wk->ObjWorkPtr, ACT_WORK_HEROINE, 0 );
			//��a�f��\��
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
			//�u���b�N�C������
			WIPE_SYS_Start(	WIPE_PATTERN_M, WIPE_TYPE_FADEIN,
							WIPE_TYPE_FADEIN,0x0000,SCENE2_DISP_CHG_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 15:	//�|�`���}�J�b�g�C��
		//�o�g���a�f�X�N���[��
		Scene2_ScrollBattle(scene_wk);
		if ( WIPE_SYS_EndCheck() ){
			if ( OPD_Poke_CutIn(scene_wk->OpSsmPtr, CUT_IN_POTTYAMA, inCounter) ){
				//�`���[�������u���b�N�A�E�g
///				ChangeBrightnessRequest(SCENE2_END_OUT_SYNC, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL,
///						PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);
				WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0000,OPDEMO_BRIGHTNESS_SYNC,1,HEAPID_OP_DEMO );
				(*seq)++;
			}
		}
		break;
	case 16:
		//�o�g���a�f�X�N���[��
		Scene2_ScrollBattle(scene_wk);
		//�u���b�N�A�E�g�҂�
		if ( WIPE_SYS_EndCheck() ){
			(*seq)++;
		}
		break;
	case 17:	//�I��
		return TRUE;
		break;
	}	
	return FALSE;
}

static void Scene_LoadPal(NNSG2dPaletteData *inPalData, const u8 inDispMS,
						  const u8 inPalNum, const u8 inStart, const u8 inDst)
{
	u16 * adr;
	DC_FlushRange( inPalData->pRawData, 2*16*inPalNum );	//inPalNum�{�����t���b�V��
	adr = inPalData->pRawData;
	//16�p���b�ginStart�Ԗڂ���inPalNum�{�����[�h
	if (inDispMS == DISP_MAIN){
		GX_LoadBGPltt( &adr[inStart], inDst, 2*16*inPalNum );
	}else{
		GXS_LoadBGPltt( &adr[inStart], inDst, 2*16*inPalNum );
	}
}

static void Scene2_ScrollTown(SCENE2_WORK *scene_wk)
{
	if (scene_wk->BG_ScrollMargin++ > SCENE2_TOWN_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, TOWN_FRAME, GF_BGL_SCROLL_Y_INC, TOWN_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
	}
}

static void Scene2_ScrollSky(SCENE2_WORK *scene_wk)
{
	if (scene_wk->BG_ScrollMargin++ > SCENE2_SKY_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, SKY_FRAME, GF_BGL_SCROLL_X_INC, SKY_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
	}
}

static void Scene2_ScrollBattle(SCENE2_WORK *scene_wk)
{
///	if (scene_wk->BG_ScrollMargin++ > SCENE2_BATTLE_SCROLL_MARGIN){
		GF_BGL_ScrollSet( scene_wk->bgl, G256_FRAME, GF_BGL_SCROLL_X_INC, BATTLE_BG_SPEED );
		scene_wk->BG_ScrollMargin = 0;
///	}
}

#define ANGLE_MOVE	(-0x980)

static void Scene2_CameraMoveMain(SCENE2_WORK *scene_wk, const int inCounter)
{
	VecFx32 move = {0,0,0};
	if (inCounter<=FM_CAMEA1_END){
		//�J�����Y�[��
		{
			u16 persp_way;
			persp_way = GFC_GetCameraPerspWay(scene_wk->Data.CameraPtr);
			if (persp_way-32>0x05c1){
				GFC_AddCameraPerspWay(-32,scene_wk->Data.CameraPtr);
			}else{
				GFC_SetCameraPerspWay(0x05c1,scene_wk->Data.CameraPtr);
			}
		}
		//��ɕ��s�ړ�
		move.z -= FX32_ONE*2;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
		if (inCounter == FM_CAMEA1_END){
			VecFx32 target = {-(FX32_ONE*16*8),0,-(FX32_ONE*16*(32-4))};
			//�J�����Z�b�g
			GFC_InitCameraTDA( &target,
				CameraData.Distance,	// ����
				&CameraData.Angle,	//
				CameraData.PerspWay,	// ���ˉe�̊p�x
				CameraData.View,
				FALSE,				//�o�C���h���Ȃ�
				scene_wk->Data.CameraPtr
			);
			//�\�m�I�^�E���̍����ɂ��킹��
			{
				VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
				GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
			}
			//�p�x����
			{
				CAMERA_ANGLE angle = {0,ANGLE_MOVE,0,0};
				GFC_AddCameraAngleRot(&angle,scene_wk->Data.CameraPtr);
			}
		}
	}else if(inCounter<=FM_CAMEA2_END){
		//�E�ɕ��s�ړ�
		move.x += FX32_ONE;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
		if (inCounter == FM_CAMEA2_END){
			VecFx32 target = {FX32_ONE*16*32,0,-(FX32_ONE*16*32*4)+(FX32_ONE*16*16)};
			//�J�����Z�b�g
			GFC_InitCameraTDA( &target,
				CameraData.Distance,	// ����
				&CameraData.Angle,	//
				CameraData.PerspWay,	// ���ˉe�̊p�x
				CameraData.View,
				FALSE,				//�o�C���h���Ȃ�
				scene_wk->Data.CameraPtr
			);
			GFC_SetCameraPerspWay(0x05c1,scene_wk->Data.CameraPtr);
			//�\�m�I�^�E���̍����ɂ��킹��
			{
				VecFx32 move = {0,SONOO_TOWN_HEIGHT,0};
				GFC_ShiftCamera(&move,scene_wk->Data.CameraPtr);
			}
		}
	}else {
		//���ɕ��s�ړ��i�悫�Ƃ���ŁA�J���������j
		if (inCounter>=FM_CAM_ZOOM_OUT_START){
			u16 persp_way;
			persp_way = GFC_GetCameraPerspWay(scene_wk->Data.CameraPtr);
			if (persp_way+32<0x4000){
				GFC_AddCameraPerspWay(32,scene_wk->Data.CameraPtr);
			}
		}
		move.z += 4*FX32_ONE;
		GFC_ShiftCamera(&move, scene_wk->Data.CameraPtr);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//�V�[��3�i�e���K���U���j
static void Scene3_Init(OPENING_DEMO_WORK * wk);
static void Scene3_Load(SCENE3_WORK *scene_wk);
static BOOL Scene3_Main(SCENE3_WORK *scene_wk, const int inCounter);
static void Scene3_End(OPENING_DEMO_WORK * wk);
static void Scene3_Affine(SCENE3_WORK *scene_wk);
static void Scene3_Affine2(SCENE3_WORK *scene_wk);
static void RequestThunder(SCENE3_THUNDER_DATA *outData);
static void ThunderMain(SCENE3_WORK *scene_wk);

static BOOL MtTenganScene(OPENING_DEMO_WORK * wk)
{
	u8 *seq = &(wk->SceneWork3.Seq);
	if (wk->SkipFlg){
		(*seq) = 3;		//�X�L�b�v���s
	}
	
	switch(*seq){
	case 0:		//������
		Scene3_Init(wk);
		(*seq)++;
		break;
	case 1:			//�O���t�B�b�N���[�h
		Scene3_Load(&wk->SceneWork3);
		(*seq)++;
		break;
	case 2:			//���C��
		if ( Scene3_Main( &wk->SceneWork3, wk->FrameCounter ) ){
			(*seq)++;
		}
		break;
	case 3:			//�I��
		Scene3_End(wk);
		return TRUE;
	}
	return FALSE;
}

static void Scene3_Init(OPENING_DEMO_WORK * wk)
{
	int obj_work_size;
	int ssm_size;
	OpDemo_Scene3_VramBankSet();
	OpDemo_Scene3_2DBgSet(wk);

	wk->SceneWork3.bgl = wk->bgl;

	//�}�X�^�[�P�x���O�ɂ���
	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
	//�J���[������ʖ���
	G2_BlendNone();

	wk->SceneWork3.InitOK = 1;	//init�ʉ�
}

static void Scene3_Load(SCENE3_WORK *scene_wk)
{
	ARCHANDLE* pal_handle;
/**
	const int pal_arc_idx[BTL_PAL_MAX] = {
		NARC_op_demo_op_demoBG2_btl1_NCLR,
		NARC_op_demo_op_demoBG2_btl2_NCLR,
		NARC_op_demo_op_demoBG2_btl3_NCLR,
		NARC_op_demo_op_demoBG2_btl4_NCLR
	};
*/	
	//�p���b�g�A�[�J�C�u�n���h���I�[�v��
	pal_handle  = ArchiveDataHandleOpen( ARC_OP_DEMO, HEAPID_OP_DEMO);

	scene_wk->PalDataBuf = ArchiveDataLoadAllocByHandle( pal_handle, NARC_op_demo_op_demoBG3_NCLR, HEAPID_OP_DEMO );
	if( scene_wk->PalDataBuf != NULL )
	{
		if( NNS_G2dGetUnpackedPaletteData( scene_wk->PalDataBuf, &scene_wk->PalData ) == FALSE ){
			sys_FreeMemoryEz( scene_wk->PalData );
			GF_ASSERT(0);
		}
	}else{
		GF_ASSERT(0);
	}
	
	//�n���h���N���[�Y
	ArchiveDataHandleClose( pal_handle );

	//�p���b�g
	Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 9, 0, 0);		//9�{���[�h
	Scene_LoadPal(scene_wk->PalData, DISP_SUB, 9, 0, 0);		//9�{���[�h
	
	//--�_�f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG_cloud_NCGR,
						scene_wk->bgl, MT_CLOUD_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_cloud_NSCR,
						scene_wk->bgl, MT_CLOUD_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--�R�f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_tengan_NCGR,
						scene_wk->bgl, MT_TENGAN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_tengan_NSCR,
						scene_wk->bgl, MT_TENGAN_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--�΃f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_lake_NCGR,
						scene_wk->bgl, MT_LAKE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_lake_NSCR,
						scene_wk->bgl, MT_LAKE_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

	//--���f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_thunder_NCGR,
						scene_wk->bgl, MT_THUNDER_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_thunder_NSCR,
						scene_wk->bgl, MT_THUNDER_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);

	//--�T�u�_�f�[�^���[�h
	//�L����
	ArcUtil_BgCharSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG_cloud_m_NCGR,
						scene_wk->bgl, MT_CLOUD_SUB_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
	//�X�N���[��
	ArcUtil_ScrnSet(ARC_OP_DEMO, NARC_op_demo_op_demoBG3_cloud_m_NSCR,
						scene_wk->bgl, MT_CLOUD_SUB_FRAME, 0, 0, FALSE, HEAPID_OP_DEMO);
		
	//--�����a�f�ݒ�
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1|
							   GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF   );
	
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );

	//�΂a�f�͉�48�L��������̂Œ������낦����
	GF_BGL_ScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_X_INC, ((48-32)*8/2) );
	//affine������
	{
		MtxFx22 mtx;
		fx32 rScale_x,rScale_y;
	
		rScale_x = FX_Inv(0x1000);
		rScale_y = FX_Inv(0x1000);
		mtx._00 = rScale_x;
		mtx._01 = 0;
	    mtx._10 = 0;
		mtx._11 = rScale_y;
		
		SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup
		GF_BGL_AffineSet( scene_wk->bgl, MT_TENGAN_FRAME, &mtx, 128, 96 );
		GF_BGL_AffineSet( scene_wk->bgl, MT_LAKE_FRAME, &mtx, 192, 96 );
	}
	
	scene_wk->LoadOK = 1;		//load�ʉ�
}

static BOOL Scene3_Main(SCENE3_WORK *scene_wk, const int inCounter)
{
	u8 *seq = &(scene_wk->SceneSeq);
	
	switch(*seq){
	case 0:	//�������u���b�N�C��
		if (inCounter>=FM_TENGAN_IN){
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
								WIPE_TYPE_FADEIN,0x0000,SCENE3_START_IN_SYNC,1,HEAPID_OP_DEMO );
			(*seq)++;
		}
		break;
	case 1:
		if ( WIPE_SYS_EndCheck() ){
			(*seq)++;
			scene_wk->TenganSc = 0x1000;
			scene_wk->LakeSc = 0x1000;
		}
		break;
	case 2://�悫�Ƃ���ŗ��ʃz���C�g�A�E�g
		//�a�f�X�N���[���E�g�k���C��
		if (inCounter==FM_THUNDER1){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER2){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER3){
			RequestThunder(&scene_wk->ThunderData);
		}
		if (inCounter==FM_THUNDER4){
			RequestThunder(&scene_wk->ThunderData);
		}

		if (inCounter>=FM_MT_AFFINE){
			Scene3_Affine(scene_wk);
		}
		
		if ( (inCounter>=FM_TENGAN_OUT) ){
			WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x7fff,TENGAN_WH_OUT_SYNC,1,HEAPID_OP_DEMO );
			Scene3_Affine2(scene_wk);
			(*seq)++;
		}
		break;
	case 3:	//�z���C�g�A�E�g�҂�
		Scene3_Affine2(scene_wk);
		if( WIPE_SYS_EndCheck() ){
			return TRUE;
		}
	}

	ThunderMain(scene_wk);
	
	return FALSE;
}

static void Scene3_End(OPENING_DEMO_WORK * wk)
{
	if (wk->SceneWork3.InitOK){
		//bgl���
		GF_BGL_BGControlExit( wk->bgl, MT_CLOUD_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_TENGAN_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_LAKE_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_THUNDER_FRAME );
		GF_BGL_BGControlExit( wk->bgl, MT_CLOUD_SUB_FRAME );
		sys_FreeMemoryEz( wk->bgl );
		wk->SceneWork3.InitOK = 0;
	}
	if (wk->SceneWork3.LoadOK){		//load�ʉ�
		//�p���b�g���
		sys_FreeMemoryEz(wk->SceneWork3.PalDataBuf);
		wk->SceneWork3.LoadOK = 0;
	}
}

static void Scene3_Affine(SCENE3_WORK *scene_wk)
{
	MtxFx22 tengan_mtx, lake_mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv(scene_wk->TenganSc);
	rScale_y = FX_Inv(scene_wk->TenganSc);
    tengan_mtx._00 = rScale_x;
    tengan_mtx._01 = 0;
    tengan_mtx._10 = 0;
    tengan_mtx._11 = rScale_y;
	
	rScale_x = FX_Inv(scene_wk->LakeSc);
	rScale_y = FX_Inv(scene_wk->LakeSc);
    lake_mtx._00 = rScale_x;
    lake_mtx._01 = 0;
    lake_mtx._10 = 0;
    lake_mtx._11 = rScale_y;
	
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup

	
	if (scene_wk->TenganSc + TENGAN_AFF_VAL <= AFF_LIMIT_1){
		scene_wk->TenganSc += TENGAN_AFF_VAL;
		GF_BGL_AffineScrollSet( scene_wk->bgl, MT_TENGAN_FRAME, GF_BGL_SCROLL_Y_INC, 1,
									&tengan_mtx, 128, 90 );
		scene_wk->LakeSc += TENGAN_AFF_VAL;
		GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, 1,
								&lake_mtx, 192, 90 );
	}
	
/**	
	if (++scene_wk->LakeAffMargin>=AFF_MARGIN){
		if (scene_wk->LakeSc-LAKE_AFF_VAL > LAVE_AFF_LIMIT){
			scene_wk->LakeSc -= LAKE_AFF_VAL;
			GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, -1,
									&lake_mtx, 192, 144 );
		}
		scene_wk->LakeAffMargin = 0;
	}
*/	
}

static void Scene3_Affine2(SCENE3_WORK *scene_wk)
{
	MtxFx22 tengan_mtx, lake_mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv(scene_wk->TenganSc);
	rScale_y = FX_Inv(scene_wk->TenganSc);
    tengan_mtx._00 = rScale_x;
    tengan_mtx._01 = 0;
    tengan_mtx._10 = 0;
    tengan_mtx._11 = rScale_y;
	
	rScale_x = FX_Inv(scene_wk->LakeSc);
	rScale_y = FX_Inv(scene_wk->LakeSc);
    lake_mtx._00 = rScale_x;
    lake_mtx._01 = 0;
    lake_mtx._10 = 0;
    lake_mtx._11 = rScale_y;
	
    SVC_WaitVBlankIntr();          // Waiting the end of VBlank interrup

	
	scene_wk->TenganSc += TENGAN_AFF_VAL2;
	GF_BGL_AffineScrollSet( scene_wk->bgl, MT_TENGAN_FRAME, GF_BGL_SCROLL_Y_INC, 1,
							&tengan_mtx, 128, 90 );
	scene_wk->LakeSc += TENGAN_AFF_VAL2;
	GF_BGL_AffineScrollSet( scene_wk->bgl, MT_LAKE_FRAME, GF_BGL_SCROLL_Y_INC, 1,
							&lake_mtx, 192, 90 );	
}

static u8 MtThunder[4] = {8,7,6,0};
static u8 CloudThunder[4] = {5,4,3,1};
static u8 ThunderWait[4] = {8,6,6,4};

static void RequestThunder(SCENE3_THUNDER_DATA *outData)
{
	outData->Request = 1;
	outData->Counter = 6;
	outData->NowPalTblNo = 0;
	//���a�f�I��
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
}

static void ThunderMain(SCENE3_WORK *scene_wk)
{
	SCENE3_THUNDER_DATA *data = &scene_wk->ThunderData;
	if (data->Request){

		if (data->Counter >= ThunderWait[data->NowPalTblNo]){
			//�p���b�g�ύX
			Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 1, 16*MtThunder[data->NowPalTblNo], 0);		//�R
			Scene_LoadPal(scene_wk->PalData, DISP_MAIN, 1, 16*CloudThunder[data->NowPalTblNo], 16*2);	//�_
			Scene_LoadPal(scene_wk->PalData, DISP_SUB, 1, 16*CloudThunder[data->NowPalTblNo], 16*2);	//�_
			data->Counter = 0;
			data->NowPalTblNo++;
			if (data->NowPalTblNo >= 4){
				data->Request = 0;
			}
		}else{
			data->Counter++;
		}

		if ( (data->NowPalTblNo==0)&&(data->Counter >= ThunderWait[0]) ){
			//���a�f�I�t
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		}
	}
}
