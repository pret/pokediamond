//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fog_sys.c
 *@brief	�t�H�O�V�X�e��
 *@author	tomoya takahashi
 *@data		2005.04.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __FOG_SYS_H_GLOBAL
#include "common.h"
#include "fog_sys.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t�H�O�f�[�^�\����
//=====================================
typedef struct _FOG_DATA{
	BOOL	flag;		// on/off�t���O----(TRUE / FALSE)
	s32		fog_mode;	// �t�H�O���[�h----�J���[�ƃA���t�@�ɂ�����/�A���t�@�݂̂�����(0 / 1)
	s32		fog_slope;	// �����肮����----(0�`10)	0<10�ŔZ���ł�
	int		offset;		// �ǂ̃f�v�X�l���炩���邩

	GXRgb	color;		// �t�H�O�J���[
	int alpha;			// ��(0�`31)	BG�ւ̓��ߓx

	char	fog_tbl_data[32];		// �R�Q�i�K�̃t�H�O�e�[�u��	(�Z�x��0�`127)
}FOG_DATA;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t�H�O�f�[�^�ۑ��̈���쐬
//-------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�f�[�^�ۑ��̈���쐬
 *
 *@param	none
 *
 *@return	FOG_DATA_PTR	�쐬���ꂽ�t�H�O�f�[�^�ۑ��̈�
 *
 *
 */
//-----------------------------------------------------------------------------
FOG_DATA_PTR FogSys_Init(void)
{
	FOG_DATA_PTR fog_data;
	fog_data = sys_AllocMemory(HEAPID_FIELD, sizeof(FOG_DATA));
	MI_CpuClear32(fog_data, sizeof(FOG_DATA));

	return fog_data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�f�[�^�ۑ��̈��j��
 *
 *@param	pFogData	�t�H�O�f�[�^�ۑ��̈�̃|�C���^���w���A�h���X
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void FogSys_Delete(FOG_DATA_PTR* pFogData)
{
	sys_FreeMemory(HEAPID_FIELD, *pFogData);
	*pFogData = NULL;
}

//-------------------------------------
//	���̃t�H�O�̏�Ԃ��擾
//-------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	ON/OFF�t���O���擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	BOOL	ON:TRUE		OFF:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GetFogFlag(FOG_DATA_PTR FogData)
{
	return FogData->flag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O���[�h���擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	int			�t�H�O���[�h
 *
 *
 */
//-----------------------------------------------------------------------------
int GetFogMode(FOG_DATA_PTR FogData)
{
	return FogData->fog_mode;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�̂��������擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	int			�t�H�O�̂������l
 *
 *
 */
//-----------------------------------------------------------------------------
int GetFogSlope(FOG_DATA_PTR FogData)
{
	return FogData->fog_slope;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�̂�����n�߂�f�v�X�l�擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	int			�t�H�O�̂�����n�߂�f�v�X�l
 *
 *
 */
//-----------------------------------------------------------------------------
int GetFogOffset(FOG_DATA_PTR FogData)
{
	return FogData->offset;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�J���[�擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	GXRgb		�t�H�O�J���[
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GetFogColor(FOG_DATA_PTR FogData)
{
	return FogData->color;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�̃��l���擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ���
 *
 *@return	int			���l
 *
 *
 */
//-----------------------------------------------------------------------------
int GetFogAlpha(FOG_DATA_PTR FogData)
{
	return FogData->alpha;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�e�[�u���擾
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *
 *@return	const char*	�t�H�O�e�[�u���|�C���^	(�v�f����32�ł�)
 *
 *
 */
//-----------------------------------------------------------------------------
const char* GetFogTbl(FOG_DATA_PTR FogData)
{
	return FogData->fog_tbl_data;
}

//-------------------------------------
//	�t�H�O�f�[�^��ݒ�
//-------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�f�[�^��ۑ��̈�ɐݒ肵�A�`��ɔ��f������
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *@param	cont		����t���O			�l��ύX�������f�[�^��ނ̒萔���b�Ŏw�肷��FOG_SYS_ALL�͑S�Đݒ�
 *@param	flag		�t�H�O�t���O
 *@param	fogMode		�t�H�O���[�h
 *@param	fogSlope	�t�H�O�̂�����
 *@param	offset		�t�H�O�̂�����n�߂�f�v�X�l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SetFogData(FOG_DATA_PTR FogData, int cont, BOOL flag, int fogMode, int fogSlope, int offset)
{
	if(cont & FOG_SYS_FLAG){
		FogData->flag		= flag;
	}
	if(cont & FOG_SYS_MODE){
		FogData->fog_mode	= fogMode;
	}
	if(cont & FOG_SYS_SLOPE){
		FogData->fog_slope	= fogSlope;
	}
	if(cont & FOG_SYS_OFFSET){
		FogData->offset		= offset;
	}

	G3X_SetFog(FogData->flag,
			FogData->fog_mode,
			FogData->fog_slope,
			FogData->offset);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�J���[��ۑ��̈�ɐݒ肵�A�`��ɔ��f
 *
 *@param	FogData		�t�H�O�f�[�^�ۑ��̈�
 *@param	cont		����t���O			�l��ύX�������f�[�^��ނ̒萔���b�Ŏw�肷��FOG_SYS_ALL�͑S�Đݒ�
 *@param	color		�J���[
 *@param	alpha		���l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SetFogColor(FOG_DATA_PTR FogData,int cont,  GXRgb color, int alpha)
{
	if(cont & FOG_SYS_RGB){
		FogData->color = color;
	}
	if(cont & FOG_SYS_ALPHA){
		FogData->alpha = alpha;
	}

	G3X_SetFogColor(FogData->color, FogData->alpha);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�H�O�e�[�u����ۑ��̈�ɐݒ肵�A�`��ɔ��f
 *
 *@param	FogData			�t�H�O�f�[�^�ۑ��̈�
 *@param	char* fog_tbl	�t�H�O�e�[�u��
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void SetFogTbl(FOG_DATA_PTR FogData, const char* fog_tbl)
{
	MI_CpuCopy32(fog_tbl, FogData->fog_tbl_data, 32);
	
	G3X_SetFogTable((u32*)FogData->fog_tbl_data);	
}
