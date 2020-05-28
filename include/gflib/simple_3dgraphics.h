//=============================================================================================
/**
 * @file	simple_3dgraphic.h
 * @brief	��{�R�c�O���t�B�b�N�V�X�e��
 */
//=============================================================================================
#ifndef __SIMPLE_3DGRAPHIC_H__
#define __SIMPLE_3DGRAPHIC_H__

#include "system.h"


#undef GLOBAL
#ifdef __SIMPLE_3DGRAPHICS_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#define LINK_VRAM_MANAGER	//�����N�hVRAM�}�l�[�W���[���g�p

#include "tcb.h"

typedef void (*pCallBackFunc)(void *);	// �֐��|�C���^�^
typedef void (*pSetTexAnmCallBackFunc)(NNSG3dRenderObj* ,
		NNSG3dAnmObj* ,
		NNSG3dResMdl* ,
		NNSG3dResTex* );	// �֐��|�C���^�^

typedef struct VRAM_MANAGER_MEM_tag * VRAM_MANAGER_MEM_PTR;

typedef struct G3D_CLEAR_COLOR_tag
{
	GXRgb RGB;		//�N���A�J���[��RGB����
	int Alpha;		//0 <= alpha <= 31
	int Depth;		//�N���A�f�v�X�l
	int PolygonID;	//�A�g���r���[�g�o�b�t�@�̃|���S��ID�����l
	BOOL Fog;		//�A�g���r���[�g�o�b�t�@�̃t�H�O��L���ɂ��邩�ǂ����̑I��
}G3D_CLEAR_COLOR;

typedef enum{
	GF_SHADING_TOON = GX_SHADING_TOON,
	GF__SHADING_HIGHLIGHT = GX_SHADING_HIGHLIGHT,
}GF_SHADE_MODE;

typedef struct G3D_SETUP_PARAM_tag
{
	GF_SHADE_MODE ShadeMode;		//�V�F�[�f�B���O���[�h
	int Priority;		//3D�ʃv���C�I���e�B(0�`3)
	int Ref;			//���e�X�g���s���ꍇ�̔�r�l
	BOOL AntiAlias;		//�A���`�G�C���A�X�L��
	BOOL EdgeMarking;	//�G�b�W�}�[�L���O�L��
	BOOL AlphaTest;		//���e�X�g�L��
	BOOL AlphaBlend;	//���u�����h�L��
	//�N���A�J���[���
	G3D_CLEAR_COLOR ClearColor;
}G3D_SETUP_PARAM;

typedef enum{
	LINKED_VRAM_MANAGER,
	FRM_VRAM_MANAGER,
}VRAM_MANAGER_TYPE;

typedef struct VRAM_MAN_PARAM_tag
{
	VRAM_MANAGER_TYPE Type;
	union {
		struct{
			u32 TexSzByte;
			u32	TexSzByteFor4x4;
		};
		struct{
			u16 TexSlot;
			u16 dummy[3];
		};
	};
	u32 PalSzByte;
}VRAM_MAN_PARAM;

/*---------------------------------------------------------------------------*
	�O���[�o���֐�
 *---------------------------------------------------------------------------*/
GLOBAL BOOL TexKeyLive( NNSG3dResTex* pTex );	// �e�N�X�`���L�[������U���Ă��邩�`�F�b�N

GLOBAL void simple_3DModelSetResFileAlready
	(NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile);

GLOBAL void simple_3DBGInit(const u8 inMode);
GLOBAL void simple_3DBGExit(void);

GLOBAL void simple_LoadG3DModel
	(const u8 mode,
	 const char* path,
	 NNSG3dResMdl** model,
	 NNSG3dResFileHeader** resFile);

GLOBAL void simple_3DModelDraw
		(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p);
GLOBAL void simple_3DModelDraw_1mat1shape
        (NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p);

GLOBAL void simple_3DModelSet
	(const u8 mode,
	 const char* path,NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model,NNSG3dResFileHeader** resFile);

GLOBAL BOOL LoadVRAMTexture(NNSG3dResTex* tex);
GLOBAL BOOL BindTexture(void* pResData, NNSG3dResTex* pTex);

#undef GLOBAL



#endif
