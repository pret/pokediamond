//============================================================================================
/**
 * @file	ship_demo.c
 * @brief	�D�f��
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================

#include "common.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "application/app_tool.h"
#include "system/snd_tool.h"
#include "arc/ship_demo.naix"

#include "ship_demo.h"

#define ANIME_TYPE_NUM	(4)

#define	ANM_ICA	(0)


typedef struct SHIP_DEMO_WORK_tag
{
//	SHIPDEMO_DAT *Dat;				//�O���f�[�^
	GF_CAMERA_PTR CameraPtr;//�J����
	NNSG3dRenderObj			RenderObj;
	NNSG3dResMdl* Model;
	NNSG3dResFileHeader* ResFile;
	void *AnmMem[ANIME_TYPE_NUM];
	NNSFndAllocator AnimeAllocator;
	NNSG3dAnmObj* AnmObj[ANIME_TYPE_NUM];
	VecFx32 Target;	//�����_
	u8 Dir;
	u8 EndFlg;
}SHIP_DEMO_WORK;

typedef struct ARC_TBL_tag
{
	u16 nsbmd;
	u16 anime[ANIME_TYPE_NUM];
}ARC_TBL;

static void InitDisp( void );
static void SetVramBank(void);
static void LoadData(SHIP_DEMO_WORK *wk);

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


//�A�[�J�C�u�C���f�b�N�X�e�[�u��
static ARC_TBL ArcTbl[4] = {
	{
		NARC_ship_demo_c_demo_D_nsbmd,
		{
			NARC_ship_demo_c_demo_D_nsbca,
			NARC_ship_demo_c_demo_D_nsbma,
			NARC_ship_demo_c_demo_D_nsbta,
			NARC_ship_demo_c_demo_D_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_L_nsbmd,
		{
			NARC_ship_demo_c_demo_L_nsbca,
			NARC_ship_demo_c_demo_L_nsbma,
			NARC_ship_demo_c_demo_L_nsbta,
			NARC_ship_demo_c_demo_L_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_R_nsbmd,
		{
			NARC_ship_demo_c_demo_R_nsbca,
			NARC_ship_demo_c_demo_R_nsbma,
			NARC_ship_demo_c_demo_R_nsbta,
			NARC_ship_demo_c_demo_R_nsbtp
		}
	},
	{
		NARC_ship_demo_c_demo_U_nsbmd,
		{
			NARC_ship_demo_c_demo_U_nsbca,
			NARC_ship_demo_c_demo_U_nsbma,
			NARC_ship_demo_c_demo_U_nsbta,
			NARC_ship_demo_c_demo_U_nsbtp
		}
	}
};

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
PROC_RESULT ShipDemoProc_Init( PROC * proc, int * seq )
{
	u8 i;
	SHIP_DEMO_WORK *wk;
	SHIPDEMO_DAT *dat;
	
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_SHIPDEMO, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(SHIP_DEMO_WORK), HEAPID_SHIPDEMO );
	memset( wk, 0, sizeof(SHIP_DEMO_WORK) );
	dat = PROC_GetParentWork( proc );
	
	//�i�s�������擾
	wk->Dir = dat->Dir;
	wk->EndFlg = FALSE;
	
	wk->CameraPtr = GFC_AllocCamera(HEAPID_SHIPDEMO);	//�J�����쐬
	InitDisp();
		
	//�f�[�^���[�h
	LoadData(wk);
	{
		VecFx32 target = {0,0,0};
		//�J�����Z�b�g
		GFC_InitCameraTDA( &target,
			CameraData.Distance,	// ����
			&CameraData.Angle,	//
			CameraData.PerspWay,	// ���ˉe�̊p�x
			CameraData.View,
			FALSE,				//�o�C���h���Ȃ�
			wk->CameraPtr
			);

		GFC_AttachCamera(wk->CameraPtr);
	}
	for(i=0;i<4;i++){
		//���C�g�Z�b�g
		NNS_G3dGlbLightVector(i,
							dat->LightDataPtr->lightVec[i].x,
							dat->LightDataPtr->lightVec[i].y,
							dat->LightDataPtr->lightVec[i].z);
		NNS_G3dGlbLightColor(i, dat->LightDataPtr->Color[i]);
	}

	//�O���[�o���X�e�[�g��������
	NNS_G3dGlbMaterialColorDiffAmb(
				dat->LightDataPtr->Diff,
				dat->LightDataPtr->Amb,
				dat->LightDataPtr->IsSetVtxColor);
	
	NNS_G3dGlbMaterialColorSpecEmi(
				dat->LightDataPtr->Spec,
				dat->LightDataPtr->Emi,
				dat->LightDataPtr->IsShininess);
	
	// �|���S���A�g���r���[�g
	NNS_G3dGlbPolygonAttr(
				dat->LightDataPtr->LightFlag,
				dat->LightDataPtr->polyMode,
				dat->LightDataPtr->cullMode,
				dat->LightDataPtr->polygonID,
				dat->LightDataPtr->alpha,
				dat->LightDataPtr->misc);
		
	APP_WipeStart( APP_WIPE_IN, HEAPID_SHIPDEMO );
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
PROC_RESULT ShipDemoProc_Main( PROC * proc, int * seq )
{
	u8 i;
	BOOL end_flg;
	MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 scale = {FX32_ONE,FX32_ONE,FX32_ONE};
	VecFx32 trans = {0,0,0};

	SHIP_DEMO_WORK * wk = PROC_GetWork( proc );

	switch(*seq){
	case 0:
		//���J�n
		Snd_SePlay( SE_SHIP_RUN );
		(*seq)++;
		break;
	case 1:
		if (!wk->EndFlg){
			//ica�A�j���I�������o
			if (wk->AnmObj[ANM_ICA]->frame+FX32_ONE == NNS_G3dAnmObjGetNumFrame(wk->AnmObj[ANM_ICA])){
				wk->EndFlg = TRUE;
				//�u���b�N�A�E�g���N�G�X�g
				APP_WipeStart( APP_WIPE_OUT, HEAPID_SHIPDEMO );
			}
		}else{
			//���C�v�A�E�g�҂�
			if (WIPE_SYS_EndCheck() ){
				return PROC_RES_FINISH;
			}
		}
	}

	for (i=0;i<ANIME_TYPE_NUM;i++){
		if (wk->AnmObj[i]->frame+FX32_ONE < NNS_G3dAnmObjGetNumFrame(wk->AnmObj[i])){
			//�A�j���t���[���X�V
			wk->AnmObj[i]->frame += (FX32_ONE);
		}
	}
	
	//�`��
	GF_G3X_Reset();
	GFC_CameraLookAt();
	simple_3DModelDraw(	&wk->RenderObj,
						&trans,
						&rotate_tmp,
						&scale);
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL,GX_BUFFERMODE_W);

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
PROC_RESULT ShipDemoProc_End( PROC * proc, int * seq )
{
	u8 i;
	SHIP_DEMO_WORK * wk = PROC_GetWork( proc );
	//�A�j�����
	for(i=0;i<ANIME_TYPE_NUM;i++){
		NNS_G3dFreeAnmObj(	&wk->AnimeAllocator, wk->AnmObj[i]);
		sys_FreeMemoryEz(wk->AnmMem[i]);
	}
	//���f�����O�f�[�^���
	sys_FreeMemoryEz(wk->ResFile);
	//�J�������
	GFC_FreeCamera(wk->CameraPtr);
	//���[�N���
	PROC_FreeWork( proc );
	//3�c�֘A�I��
	simple_3DBGExit();
	//�q�[�v���
	sys_DeleteHeap( HEAPID_SHIPDEMO );
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 * ��ʏ�����
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void InitDisp( void )
{
	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g
	sys_HBlankIntrStop();				// HBlank��~

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	SetVramBank();				// VRAM�ݒ�
	simple_3DBGInit(HEAPID_SHIPDEMO);
	G3X_EdgeMarking( TRUE );
	//�G�b�W�}�[�L���O�e�[�u���Z�b�g
	G3X_SetEdgeColorTable(gEdgeColor);
	GF_Disp_DispSelect();	//3�c�ʐݒ�i��ɂ��邩�A���ɂ��邩�j
	

}

//===========================================================================
/**
 * 
 * �u�q�`�l�o���N�ݒ�
 *
 */
//===========================================================================
static void SetVramBank(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_32_H,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_16_F,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_01_AB,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0123_E			// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 * @brief	�D�f���f�[�^���[�h
 *
 * @param	wk		�D�f�����[�N
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void LoadData(SHIP_DEMO_WORK *wk)
{
	u8 i;
	NNSG3dResTex *texture;
	void *pAnmRes;
	ARCHANDLE* handle;
	//�A�[�J�C�u�n���h���I�[�v��
	handle = ArchiveDataHandleOpen( ARC_SHIP_DEMO, HEAPID_SHIPDEMO );
	//�A�j���A���P�[�^
	sys_InitAllocator(&wk->AnimeAllocator,HEAPID_SHIPDEMO,4);
	
	//���f�����O�f�[�^�����[�h
	wk->ResFile = ArchiveDataLoadAllocByHandle( handle, ArcTbl[wk->Dir].nsbmd, HEAPID_SHIPDEMO );
	simple_3DModelSetResFileAlready( &wk->RenderObj, &wk->Model, &wk->ResFile );
	texture = NNS_G3dGetTex(wk->ResFile);	// �e�N�X�`�����\�[�X�擾
	
	//���f�����O�f�[�^�̓O���[�o���X�e�[�g���g�p����
	NNS_G3dMdlUseGlbDiff(wk->Model);			// �f�B�t���[�Y
	NNS_G3dMdlUseGlbAmb(wk->Model);				// �A���r�G���g
	NNS_G3dMdlUseGlbSpec(wk->Model);			// �X�y�L�����[
	NNS_G3dMdlUseGlbEmi(wk->Model);				// �G�~�b�V����	
	
	for(i=0;i<ANIME_TYPE_NUM;i++){
		//�A�j���[�V���������[�h
		wk->AnmMem[i] = ArchiveDataLoadAllocByHandle( handle, ArcTbl[wk->Dir].anime[i], HEAPID_SHIPDEMO );
		pAnmRes = NNS_G3dGetAnmByIdx(wk->AnmMem[i], 0);
		// �K�v�ʂ̃��������A���P�[�g����B
		wk->AnmObj[i] = NNS_G3dAllocAnmObj( &wk->AnimeAllocator, // �g�p����A���P�[�^���w��
				                             pAnmRes,    // �A�j���[�V�������\�[�X���w��
						                     wk->Model);    // ���f�����\�[�X���w��
	
		//�C�j�V�����C�Y
		NNS_G3dAnmObjInit(wk->AnmObj[i], // �A�j���[�V�����I�u�W�F�N�g�ւ̃|�C���^
		                  pAnmRes, // �A�j�����\�[�X�ւ̃|�C���^
			              wk->Model,  // NNSG3dResMdl�ւ̃|�C���^
				          texture );  // NNSG3dResTex�ւ̃|�C���^
		//�A�j���o�C���h
		NNS_G3dRenderObjAddAnmObj( &wk->RenderObj, wk->AnmObj[i] );
	}
	//�n���h���N���[�Y
	ArchiveDataHandleClose( handle );
}
