//=============================================================================================
/**
 * @file	debug_3d_draw_count.c
 * @brief	�f�o�b�O�p�`��֘A�J�E���g�i�|���S�����Ƃ��j
 */
//=============================================================================================
#ifdef PM_DEBUG

#include <nitro.h>
#include <nnsys.h>
#include "debug_3d_draw_count.h"

//----- �|���S���`��̉񐔂𒲂ׂ邽�߂�DEBUG����
typedef struct{
	int NNS_AddVertexNum;
	int NNS_AddPolygonNum;
	int NNS_AddDrawNum;
	int VertexNum;
	int PolygonNum;
	int DrawNum;

	int TexBlock;
	int PlttBlock;

	NNSiGfdLnkVramBlock *texture_p;
	NNSiGfdLnkVramBlock *pal_p;
}DEBUG_DRAW_COUNT;

static DEBUG_DRAW_COUNT DebugDrawCount;

//------------------------------------------------------------------
/**
 * 3D�`��̂��߂ɒ��ׂ����l��ޔ�
 *
*/
//------------------------------------------------------------------
void D_3D_DC_DrawPolygonCountUp(void)
{
	DebugDrawCount.NNS_AddVertexNum  = DebugDrawCount.VertexNum;
	DebugDrawCount.NNS_AddPolygonNum = DebugDrawCount.PolygonNum;
	DebugDrawCount.NNS_AddDrawNum       = DebugDrawCount.DrawNum;

	DebugDrawCount.VertexNum  = 0;
	DebugDrawCount.PolygonNum = 0;
	DebugDrawCount.DrawNum    = 0;
}

//------------------------------------------------------------------
/**
 * NITROSYSTEM�ɓn�����|���S���̐���Ԃ�
 *
 * @param	int �|���S����
*/
//------------------------------------------------------------------
int D_3D_DC_DrawPolygonGet(void)
{
	return DebugDrawCount.NNS_AddPolygonNum;
}

//------------------------------------------------------------------
/**
 * NITROSYSTEM�ɓn�������_�̐���Ԃ�
 *
 * @param	int	���_��
*/
//------------------------------------------------------------------
int D_3D_DC_DrawVertexGet(void)
{
	return DebugDrawCount.NNS_AddVertexNum;
} 

//------------------------------------------------------------------
/**
 * NITROSYSTEM����|���S���`�悵���񐔂�Ԃ�
 *
 * @return	int	�`�搔
*/
//------------------------------------------------------------------
int D_3D_DC_DrawNumGet(void)
{
	return DebugDrawCount.NNS_AddDrawNum;
}

//==============================================================================
/**
 * �����N�h�u�q�`�l�}�l�[�W���[�ƃp���b�g�}�l�[�W���[�̃|�C���^��ۑ�
 *
 * @param   texp		�e�N�X�`���}�l�[�W���[
 * @param   palp		�p���b�g�}�l�[�W���[
 * @param	inTexBlock	�e�N�X�`���u���b�N�T�C�Y
 * @param	inPlttBlockSize	�p���b�g�u���b�N�T�C�Y
 *
 * @retval  none		
 */
//==============================================================================
void D_3D_DC_VramManPSet(NNSiGfdLnkVramBlock *texp, NNSiGfdLnkVramBlock *palp,
						const int inTexBlock, const int inPlttBlock)
{
	DebugDrawCount.texture_p = texp;
	DebugDrawCount.pal_p     = palp;
	DebugDrawCount.TexBlock  = inTexBlock;
	DebugDrawCount.PlttBlock  = inPlttBlock;
}

//==============================================================================
/**
 * VRAM�ւ̃e�N�X�`��]����Ԃ��擾����
 *
 *
 * @retval  int		�g�p���Ă���u�q�`�l�e��
 */
//==============================================================================
int  D_3D_DC_VramTexSizeGet(void)
{
	int size = 0;
	int i;
	
	NNSiGfdLnkVramBlock *tex = DebugDrawCount.texture_p;
	
	
	for(i=0;i<DebugDrawCount.TexBlock;i++){
		//�����N�hVRAM�}�l�[�W���[�̐擪��T��
		if((tex->pBlkPrev==0 && tex->pBlkNext!=0) || (tex->pBlkPrev==0 && tex->pBlkNext==0)){		
			break;
		}
		tex++;
	}

	while(tex->pBlkNext!=0){	// �����N���������葫���Ď��֓n���Ă���
		size += tex->szByte;
		tex = (NNSiGfdLnkVramBlock *)tex->pBlkNext;
	}
	size += tex->szByte;		//�Ō�̃����N���VRAM�]����������

	// VRAM�}�l�[�W���[���ۑ����Ă���̂́u�g�p���Ă��Ȃ��ʁv�Ȃ̂ő��ʂ�������ĕԂ�
	return (DebugDrawCount.TexBlock*1024)-size;	
}


//==============================================================================
/**
 * �����N�hPAL�}�l�[�W���[�̓]����Ԃ��擾����
 *
 *
 * @retval  int		�����N�hPAL�}�l�[�W���[�̓]���o�C�g��
 */
//==============================================================================
int  D_3D_DC_VramPalSizeGet(void)
{
	int size = 0;
	int i;
	
	NNSiGfdLnkVramBlock *tex = DebugDrawCount.pal_p;
	
	
	for(i=0;i<DebugDrawCount.PlttBlock;i++){
		//�����N�hPALL�}�l�[�W���[�̐擪��T��
		if((tex->pBlkPrev==0 && tex->pBlkNext!=0) || (tex->pBlkPrev==0 && tex->pBlkNext==0)){		
			break;
		}
		tex++;
	}

	while(tex->pBlkNext!=0){	// �����N���������葫���Ď��֓n���Ă���
		size += tex->szByte;
		tex = (NNSiGfdLnkVramBlock *)tex->pBlkNext;
	}
	size += tex->szByte;		//�Ō�̃����N���VRAM�]����������

	// PAL�}�l�[�W���[���ۑ����Ă���̂́u�g�p���Ă��Ȃ��ʁv�Ȃ̂ő��ʂ�������ĕԂ�
	return (DebugDrawCount.PlttBlock*1024)-size;	
}

//==============================================================================
/**
 * �J�E���g�A�b�v
 *
 * @param   object_p		�����_�[�n�a�i		
 *
 * @retval  none
 */
//==============================================================================
void D_3D_DC_CountNum(NNSG3dRenderObj* object_p)
{
	//���f�����O�f�[�^���\�[�X���璸�_�����擾���đ���
	DebugDrawCount.VertexNum  += object_p->resMdl->info.numVertex;
	//���f�����O�f�[�^���\�[�X����|���S�������擾���đ���
	DebugDrawCount.PolygonNum += object_p->resMdl->info.numPolygon;		
	DebugDrawCount.DrawNum++;
}

#endif	//PM_DEBUG

