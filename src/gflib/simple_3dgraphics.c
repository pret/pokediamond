/*---------------------------------------------------------------------------*
  Project:  PokemonDS
  File:     simple_3dgraphics.c

  ��{�R�c�O���t�B�b�N�V�X�e��

 *---------------------------------------------------------------------------*/
#include <nitro.h>
#include <nnsys.h>
#include <nnsys/g3d/binres/res_print.h>

#include "system.h"
#include "display.h"
#include "bg_system.h"
#include "g3d_system.h"

#define	__SIMPLE_3DGRAPHICS_H_GLOBAL
#include "simple_3dgraphics.h"

#include "tcb.h"

#include "gflib_os_print.h"
#include "gflib/assert.h"
#include "assert.h"

#ifdef	PM_DEBUG
#include "debug_3d_draw_count.h"
#endif	//PM_DEBUG

typedef struct VRAM_MANAGER_MEM_tag
{
	void *PalMem;
	void *TexMem;
}VRAM_MANAGER_MEM;

static VRAM_MANAGER_MEM_PTR AllocVramManegerMem(const int inPalSize,
												const int inTexSize,
												const int inHeapID);
static void FreeVramManegerMem(VRAM_MANAGER_MEM_PTR *ptr);

void simple_LoadG3DModelAlrady(NNSG3dResMdl** model, NNSG3dResFileHeader** resFile);
void simple_Setup3DParams(const G3D_SETUP_PARAM *inParam);
void simple_FreeVRAMManager(VRAM_MANAGER_MEM_PTR *ptr);
//------------------------------------------------------------------
//                      ���f���ǂݍ��݊֐�
//------------------------------------------------------------------

void simple_LoadG3DModel(const u8 mode, const char* path, NNSG3dResMdl** model, NNSG3dResFileHeader** resFile)
{
    NNSG3dResTex*        texture = NULL;
    BOOL status;

    *resFile = sys_LoadFile(mode,path);
    NNS_G3D_NULL_ASSERT(*resFile);

	// �e�N�X�`����Vram�ɓW�J����Ă��Ȃ����`�F�b�N
	texture = NNS_G3dGetTex(*resFile);	// �e�N�X�`�����\�[�X�擾
	if(texture != NULL){
		if(TexKeyLive(texture) == FALSE){	// �e�N�X�`����Vram�ɓW�J����Ă��Ȃ����`�F�b�N
			///OS_Printf("�e�N�X�`����VRAM�ɓW�J����Ă��Ȃ��̂ŁA�����œW�J\n");
			//������DMA�]������̂Ńt���b�V������
			DC_FlushRange(*resFile,(*resFile)->fileSize);
			// �f�t�H���g�̏������֐����R�[�����ăZ�b�g�A�b�v����
			status = NNS_G3dResDefaultSetup(*resFile);
			NNS_G3D_ASSERTMSG(status, "NNS_G3dResDefaultSetup failed");
		}
	}
    
    // G3D: ���f���̎擾
    // nsbmd�̓��f���𕡐��܂ނ��Ƃ��ł���̂ŁA�C���f�b�N�X(���f�����P�̏ꍇ��0)
    // ���w�肵�ĂP�̃��f���ւ̃|�C���^���擾����B
    // --------------------------------------------------------------------
    *model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
}

//���\�[�X�m�ۍςݗp
void simple_LoadG3DModelAlrady(NNSG3dResMdl** model, NNSG3dResFileHeader** resFile)
{
    NNSG3dResTex*        texture = NULL;
    BOOL status;

	// �e�N�X�`����Vram�ɓW�J����Ă��Ȃ����`�F�b�N
	texture = NNS_G3dGetTex(*resFile);	// �e�N�X�`�����\�[�X�擾
	if(texture != NULL){
		if(TexKeyLive(texture) == FALSE){	// �e�N�X�`����Vram�ɓW�J����Ă��Ȃ����`�F�b�N
			OS_Printf("���O�Ƀe�N�X�`�����W�J����Ă��̂ŁA�e�N�X�`�����u�q�`�l�ɓW�J���܂�\n");
			//������DMA�]������̂Ńt���b�V������
			DC_FlushRange(*resFile,(*resFile)->fileSize);
			// �f�t�H���g�̏������֐����R�[�����ăZ�b�g�A�b�v����
			status = NNS_G3dResDefaultSetup(*resFile);
			NNS_G3D_ASSERTMSG(status, "NNS_G3dResDefaultSetup failed");
		}
	}
    
    // G3D: ���f���̎擾
    // nsbmd�̓��f���𕡐��܂ނ��Ƃ��ł���̂ŁA�C���f�b�N�X(���f�����P�̏ꍇ��0)
    // ���w�肵�ĂP�̃��f���ւ̃|�C���^���擾����B
    // --------------------------------------------------------------------
    *model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*resFile), 0);
}

//------------------------------------------------------------------
//                      �R�c�I�u�W�F�N�g�Z�b�g�֐�
//------------------------------------------------------------------

void simple_3DModelSet
	(const u8 mode,
	 const char* path,NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile) 
{
	simple_LoadG3DModel(mode,path,model,resFile);
	SDK_ASSERTMSG(model, "load failed");
	NNS_G3dRenderObjInit(object_p, *model);
}


void simple_3DModelSetResFileAlready
	(NNSG3dRenderObj* object_p,
	 NNSG3dResMdl** model, NNSG3dResFileHeader** resFile) 
{
	simple_LoadG3DModelAlrady(model,resFile);
	GF_ASSERT(model&&"load failed");
	SDK_ASSERTMSG(model, "load failed");
	NNS_G3dRenderObjInit(object_p, *model);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�e�N�X�`���L�[������U���Ă��邩�`�F�b�N
 *
 *@param	pTex		�e�N�X�`�����\�[�X�|�C���^
 *	
 *@return	bool		true	����U���Ă�
 *						false	����U���Ă��Ȃ�
 *
 */
//-----------------------------------------------------------------------------
BOOL TexKeyLive( NNSG3dResTex* pTex )
{
	// ���ʂ̃e�N�X�`����4*4�e�N�Z�����k�e�N�X�`��
	// ��Vram�ɓW�J����Ă��邩���`�F�b�N
	if((pTex->texInfo.flag & NNS_G3D_RESTEX_LOADED) ||
	   (pTex->tex4x4Info.flag & NNS_G3D_RESTEX4x4_LOADED)){
		return TRUE;
	}
	
	return FALSE;
}

//------------------------------------------------------------------
//                      �R�c�a�f�`��֐�
//------------------------------------------------------------------
void simple_3DModelDraw
(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p)
{
#ifdef	PM_DEBUG
	D_3D_DC_CountNum(object_p);	//�f�o�b�O�J�E���g
#endif
	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);
	// �p�x�ݒ�
	NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();
	
	NNS_G3dDraw(object_p);
//  NNS_G3dGeFlushBuffer();
}

//------------------------------------------------------------------
//                      �����R�c�a�f�`��֐�
//------------------------------------------------------------------
void simple_3DModelDraw_1mat1shape
(NNSG3dRenderObj* object_p,VecFx32* trans_p,MtxFx33* rot_p,VecFx32* scale_p)
{
#ifdef	PM_DEBUG
	D_3D_DC_CountNum(object_p);	//�f�o�b�O�J�E���g
#endif
	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);
	// �p�x�ݒ�
	NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();
    
    NNS_G3dDraw1Mat1Shp(object_p->resMdl,0,0,TRUE);
    
    NNS_G3dGeFlushBuffer();
}

//------------------------------------------------------------------
//                      �R�c�a�f�������֐�
//------------------------------------------------------------------
static GF_G3DMAN* g3Dman = NULL;
static void simpleSetUp(void);

void simple_3DBGInit(const u8 inMode)
{
	g3Dman = GF_G3DMAN_Init
		(inMode, GF_G3DMAN_LNK, GF_G3DTEX_256K, GF_G3DMAN_LNK, GF_G3DPLT_64K, simpleSetUp );
#ifdef	PM_DEBUG
#ifdef DEBUG_3DDRAW_COUNT
	D_3D_DC_VramManPSet(g3Dman->tex_memory, g3Dman->plt_memory, 256, 64);
#endif	
#endif	
}

static void simpleSetUp(void)
{
	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend( TRUE );		// �A���t�@�u�����h�@�I��
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//------------------------------------------------------------------
void simple_3DBGExit(void)
{
	GF_G3D_Exit( g3Dman );
}

//------------------------------------------------------------------
BOOL BindTexture(void* pResData, NNSG3dResTex* pTex)
{
	//�o�C���h����
	NNSG3dResMdlSet* mdlSet = NNS_G3dGetMdlSet((NNSG3dResFileHeader*) pResData);
	NNS_G3D_NULL_ASSERT(mdlSet);
	if (pTex){
		BOOL rc;
		// ���f���Z�b�g�̃o�C���h
		rc = NNS_G3dBindMdlSet(mdlSet, pTex);
#ifdef PN_DEBUG		
		if (!rc){
			OS_Printf("�e�N�X�`���o�C���h�Ɏ��s\n");
		}
#endif	
#ifdef TEXTURE_BIND_PRINT_ON		
		OS_Printf("TextureBind!!\n");
#endif		
		return TRUE;
	}
	return FALSE;
}

//�e�N�X�`����VRAM�ւ̃��[�h
BOOL LoadVRAMTexture(NNSG3dResTex* tex)
{
	if(tex == NULL){
		return FALSE;
	}
	
	tex->texInfo.vramKey = 0;
	{
        u32 szTex, szTex4x4, szPltt;
        BOOL sucTex    = TRUE;
        BOOL sucTex4x4 = TRUE;
        BOOL sucPltt   = TRUE;
        NNSG3dTexKey keyTex;
        NNSG3dTexKey keyTex4x4;
        NNSG3dPlttKey keyPltt;

		if (tex){
			// �K�v�ȃT�C�Y���擾
            szTex    = NNS_G3dTexGetRequiredSize(tex);
            szTex4x4 = NNS_G3dTex4x4GetRequiredSize(tex);
            szPltt   = NNS_G3dPlttGetRequiredSize(tex);

            if (szTex > 0){
				// ���݂���΃e�N�X�`���C���[�W�X���b�g�Ɋm��
                keyTex = NNS_GfdAllocTexVram(szTex, FALSE, 0);
                if (keyTex == NNS_GFD_ALLOC_ERROR_TEXKEY){
                    sucTex = FALSE;
                }
            }
            else{
				keyTex = 0;
            }

			if (szTex4x4 > 0){
				// ���݂���΃e�N�X�`���C���[�W�X���b�g�Ɋm��
                keyTex4x4 = NNS_GfdAllocTexVram(szTex4x4, TRUE, 0);
                if (keyTex4x4 == NNS_GFD_ALLOC_ERROR_TEXKEY){
					sucTex4x4 = FALSE;
                }
            }
            else{
				keyTex4x4 = 0;
            }

            if (szPltt > 0){
                // ���݂���΃e�N�X�`���p���b�g�X���b�g�Ɋm��
                keyPltt = 
                    NNS_GfdAllocPlttVram(szPltt,
                                        tex->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4,
                                        0);
                if (keyPltt == NNS_GFD_ALLOC_ERROR_PLTTKEY){
                    sucPltt = FALSE;
                }
            }
            else{
			     keyPltt = 0;
            }

            if (!sucTex){
                // ���s���̃��[���o�b�N����
                int status;
#ifdef PM_DEBUG
				OS_Printf("�e�N�X�`���擾�s��%d/%d\n",szTex,D_3D_DC_VramTexSizeGet());
#endif
				status = NNS_GfdFreeTexVram(keyTex);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreeTexVram failed");
				GF_ASSERT(!status&&"NNS_GfdFreeTexVram failed");
				
                return FALSE;
            }
			if (!sucTex4x4){
                // ���s���̃��[���o�b�N����
                int status;

                status = NNS_GfdFreeTexVram(keyTex4x4);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreeTexVram failed");
				GF_ASSERT(!status&&"NNS_GfdFree4x4TexVram failed");
				
                return FALSE;
            }
			if (!sucPltt){
                // ���s���̃��[���o�b�N����
                int status;

                status = NNS_GfdFreePlttVram(keyPltt);
                NNS_G3D_ASSERTMSG(!status, "NNS_GfdFreePlttVram failed");
				GF_ASSERT(!status&&"NNS_GfdFreePlttVram failed");

                return FALSE;
            }

            // �L�[�̃A�T�C��
            NNS_G3dTexSetTexKey(tex, keyTex, keyTex4x4);
            NNS_G3dPlttSetPlttKey(tex, keyPltt);

			//DMA�]������̂Ńt���b�V������
			DC_FlushRange( tex, tex->header.size );
            // VRAM�ւ̃��[�h
            NNS_G3dTexLoad(tex, TRUE);
            NNS_G3dPlttLoad(tex, TRUE);
        }
		
    }
    return TRUE;
}

//==============================================================================
/**
 * 3D�֘A�p�����[�^�̐ݒ�
 *
 * @param   inParam		�Z�b�g�A�b�v�p�����[�^		
 *
 * @retval  none		
 */
//==============================================================================
void simple_Setup3DParams(const G3D_SETUP_PARAM *inParam)
{
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_ASSERT(inParam->Priority<=3&&"�l���s��");
    G2_SetBG0Priority(inParam->Priority);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(inParam->ShadeMode);					//�V�F�[�f�B���O
    G3X_AntiAlias(inParam->AntiAlias);					//�A���`�G�C���A�X
    //G2_BlendNone(); 
	G3X_AlphaTest(inParam->AlphaTest, inParam->Ref);	// �A���t�@�e�X�g
	G3X_AlphaBlend(inParam->AlphaBlend);				// �A���t�@�u�����h

	{
		const G3D_CLEAR_COLOR *col;
		col = &(inParam->ClearColor);
		// �N���A�J���[�̐ݒ�
		G3X_SetClearColor(col->RGB,	// clear color
			              col->Alpha,				// clear alpha
				          col->Depth,			// clear depth
					      col->PolygonID,				// clear polygon ID
						  col->Fog				// fog
						 );
	}

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//==============================================================================
/**
 * VRAM�}�l�[�W���[�������̉��
 *
 * @param   inParam		�Z�b�g�A�b�v�p�����[�^		
 *
 * @retval  none		
 */
//==============================================================================
void simple_FreeVRAMManager(VRAM_MANAGER_MEM_PTR *ptr)
{
	if ((*ptr) != NULL){
		FreeVramManegerMem(ptr);
	}
}

//==============================================================================
/**
 * VRAM�}�l�[�W���[�̐ݒ�
 *
 * @param   inPalSize		�p���b�g�T�C�Y
 * @param   inTexSize		�e�N�X�`���T�C�Y
 * @param   inHeapID		�q�[�vID
 *
 * @retval  VRAM_MANAGER_MEM_PTR	�m�ۂ����������|�C���^
 */
//==============================================================================
static VRAM_MANAGER_MEM_PTR AllocVramManegerMem(const int inPalSize,
												const int inTexSize,
												const int inHeapID)
{
	VRAM_MANAGER_MEM_PTR ptr;

	ptr = sys_AllocMemory( inHeapID, sizeof(VRAM_MANAGER_MEM) );
	ptr->PalMem = sys_AllocMemory( inHeapID, inPalSize );
	ptr->TexMem = sys_AllocMemory( inHeapID, inTexSize );

	return ptr;
}

//==============================================================================
/**
 * VRAM�}�l�[�W���[�̐ݒ�
 *
 * @param   inPalSize		�p���b�g�T�C�Y
 * @param   inTexSize		�e�N�X�`���T�C�Y
 * @param   inHeapID		�q�[�vID
 *
 * @retval  VRAM_MANAGER_MEM_PTR	�m�ۂ����������|�C���^
 */
//==============================================================================
static void FreeVramManegerMem(VRAM_MANAGER_MEM_PTR *ptr)
{
	sys_FreeMemoryEz((*ptr)->PalMem);
	sys_FreeMemoryEz((*ptr)->TexMem);
	sys_FreeMemoryEz(*ptr);
	*ptr = NULL;
}
