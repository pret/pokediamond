//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_glb_state.c
 *@brief	�t�B�[���h�I�u�W�F�ɉe����^����f�[�^�S
 *@author	tomoya takahashi
 *@data		2005.06.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "field_glb_state.h"

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


//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�E�}�e���A���̃O���[�o���X�e�[�g�f�[�^
 *			�ۑ��̈���쐬
 *
 *@param	none
 *
 *@return	GLST_DATA*	�쐬���āA�����������f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLST_DATA_PTR GLST_Init(void)
{
	GLST_DATA* p_data;
	p_data = sys_AllocMemory(HEAPID_FIELD, sizeof(GLST_DATA));
	MI_CpuClear32(p_data, sizeof(GLST_DATA));

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�E�}�e���A���̃O���[�o���X�e�[�g�f�[�^
 *			�ۑ��̈���J��
 *
 *@param	pGLST_Data		�ۑ��̈�̃|�C���^���i�[���Ă���ϐ��̃A�h���X
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_Delete(GLST_DATA_PTR* pGLST_Data)
{
	sys_FreeMemory(HEAPID_FIELD, *pGLST_Data);
	*pGLST_Data = NULL;
}


//-----------------------------------------------------------------------------
//
//	�f�[�^�̔��f�֐��S
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	�ݒ�����O���[�o���X�e�[�g�ɐݒ�
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	flag		���𔽉f������̂�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_Reflect(GLST_DATA_PTR GLST_Data, int flag)
{
	int i;		// ���[�v�p
	
	// ���C�g
	for(i=0;i<4;i++){
		if(flag & (1<<i)){		// �t���O�������Ă��邩�`�F�b�N
			NNS_G3dGlbLightVector(i,
					GLST_Data->lightVec[i].x,
					GLST_Data->lightVec[i].y,
					GLST_Data->lightVec[i].z);
		}
		if(flag & (1<<(i+4))){	// �t���O�������Ă��邩�`�F�b�N
			NNS_G3dGlbLightColor(i,
					GLST_Data->Color[i]);
		}
	}
	// �}�e���A��
	if(flag & (GLST_DIFF | GLST_AMB)){
		NNS_G3dGlbMaterialColorDiffAmb(
				GLST_Data->Diff,
				GLST_Data->Amb,
				GLST_Data->IsSetVtxColor);
	}
	if(flag & (GLST_SPEC | GLST_EMI)){
		NNS_G3dGlbMaterialColorSpecEmi(
				GLST_Data->Spec,
				GLST_Data->Emi,
				GLST_Data->IsShininess);
	}
	// �|���S���A�g���r���[�g
	if(flag >= GLST_LIGHT_FLAG){
		NNS_G3dGlbPolygonAttr( GLST_Data->LightFlag,
				GLST_Data->polyMode,
				GLST_Data->cullMode,
				GLST_Data->polygonID,
				GLST_Data->alpha,
				GLST_Data->misc);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ݒ�������f�����\�[�X�ɐݒ�
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	pMdl	���f�����\�[�X
 *@param	flag	���𔽉f������̂�
 *
 * �����C�g�i�O�`�R�j�̐ݒ�͍s��Ȃ��̂Œ��ӂ��Ă��������B
 * 
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_ReflectMdl(GLST_DATA_PTR GLST_Data, NNSG3dResMdl* pMdl, int flag)
{
	int i;		// ���[�v�p
	
	// �}�e���A��
	if(flag & GLST_DIFF){
		NNS_G3dMdlSetMdlDiffAll(pMdl, GLST_Data->Diff);
	}
	if(flag & GLST_AMB){
		NNS_G3dMdlSetMdlAmbAll(pMdl, GLST_Data->Amb);
	}
	if(flag & GLST_SPEC){
		NNS_G3dMdlSetMdlSpecAll(pMdl, GLST_Data->Spec);
	}
	if(flag & GLST_EMI){
		NNS_G3dMdlSetMdlEmiAll(pMdl, GLST_Data->Emi);
	}
	// �|���S���A�g���r���[�g
	if(flag & GLST_LIGHT_FLAG){
		NNS_G3dMdlSetMdlLightEnableFlagAll(pMdl, GLST_Data->LightFlag);
	}
	if(flag & GLST_POLYGON_MODE){
		NNS_G3dMdlSetMdlPolygonModeAll(pMdl, GLST_Data->polyMode);
	}
	if(flag & GLST_CULL_MODE){
		NNS_G3dMdlSetMdlCullModeAll(pMdl, GLST_Data->cullMode);
	}
	if(flag & GLST_POLYGON_ID){
		NNS_G3dMdlSetMdlPolygonIDAll(pMdl, GLST_Data->polygonID);
	}
	if(flag & GLST_ALPHA){
		NNS_G3dMdlSetMdlAlphaAll(pMdl, GLST_Data->alpha);
	}
	if(flag & GLST_FOG){
		NNS_G3dMdlSetMdlFogEnableFlagAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_FOG);
	}
	if(flag & GLST_DEPTH_TEST){
		NNS_G3dMdlSetMdlDepthTestCondAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_DEPTHTEST_DECAL);
	}
	if(flag & GLST_1DOT){
		NNS_G3dMdlSetMdl1DotAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_DISP_1DOT);
	}
	if(flag & GLST_FAR_CLIP){
		NNS_G3dMdlSetMdlFarClipAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_FAR_CLIPPING);
	}
	if(flag & GLST_XLDEPTH_UPDATE){
		NNS_G3dMdlSetMdlXLDepthUpdateAll(pMdl, GLST_Data->misc & GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
	}
}

//-----------------------------------------------------------------------------
//
//	�f�[�^�̎擾�֐��S
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	GXRgb��ԗΐɕ�������
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	rgb			��������f�[�^
 *@param	r,g,b		�F���i�[����|�C���^
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void GLST_GetRGB(GXRgb dat, u8* r, u8* g, u8* b)
{
	*r = (dat >> 10)&0x1f;
	*g = (dat >> 5)&0x1f;
	*b = (dat >> 0)&0x1f;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�x�N�g���f�[�^�擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *@param	lightID		�擾���郉�C�gID
 *
 *@return	VecFx16		�x�N�g���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
VecFx16 GLST_GetLightVector(GLST_DATA_PTR GLST_Data, int lightID)
{
	return GLST_Data->lightVec[lightID];
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�J���[�f�[�^�擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *@param	lightID		�擾���郉�C�gID
 *
 *@return	GXRgb	�F�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetLightColor(GLST_DATA_PTR GLST_Data, int lightID)
{
	return GLST_Data->Color[lightID];
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�B�t���[�Y�F���擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	GXRgb	�F�f�[�^	
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialDiff(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Diff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�B�t���[�Y�F�𒸓_�J���[�Ɏg�p���Ă��邩�擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	BOOL		�g�p:TRUE	�s�g�p:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GLST_GetMaterialDiffVtxColor(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->IsSetVtxColor;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A���r�G���g�F���擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	GXRgb	�F�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialAmb(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Amb;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�y�L�����[�F���擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	GXRgb	�F�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialSpec(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Spec;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���ʔ��ˋP�x�e�[�u�����g�p���邩
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	BOOL		�g�p:TRUE	�s�g�p:FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GLST_GetMaterialSpecShininess(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->IsShininess;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�G�~�b�V�����F���擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	GXRgb	�F�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GXRgb GLST_GetMaterialEmi(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->Emi;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ǂ̃��C�g�𔽉f�����邩���ʂ���t���O���擾
 *
 *@param	GLST_Data	�ۑ��̈�|�C���^
 *
 *@return	int	���C�g�t���O	(�P�`�S�r�b�g�̃I��/�I�t�Ń`�F�b�N)
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlLightFlag(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->LightFlag;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�|���S�����[�h���擾
 *
 *@param	GLST_Data		�ۑ��̈�|�C���^
 *
 *@return	GXPolygonMode	�|���S�����[�h
 *
 *
 */
//-----------------------------------------------------------------------------
GXPolygonMode GLST_GetMdlPolyMode(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->polyMode;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�����O���[�h���擾
 *
 *@param	GLST_Data		�ۑ��̈�|�C���^
 *
 *@return	GXCull			�J�����O���[�h
 *
 *
 */
//-----------------------------------------------------------------------------
GXCull GLST_GetMdlCullMode(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->cullMode;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�|���S��ID���擾
 *
 *@param	GLST_Data		�ۑ��̈�|�C���^
 *
 *@return	int				�|���S��ID
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlPolyID(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->polygonID;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���l���擾
 *
 *@param	GLST_Data		�ۑ��̈�|�C���^
 *
 *@return	int				���l
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlAlpha(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->alpha;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̑��t���O���擾
 *
 *@param	GLST_Data		�ۑ��̈�|�C���^
 *
 *@return	int				misc	���̑��̃t���O
 *
 *
 */
//-----------------------------------------------------------------------------
int GLST_GetMdlMisc(GLST_DATA_PTR GLST_Data)
{
	return GLST_Data->misc;
}
//-----------------------------------------------------------------------------
//
//	�f�[�^�̐ݒ�֐��S
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�x�N�g���ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	lightID		���C�g�ԍ�	(0�`3)
 *@param	x,y,z		�x�N�g���̒l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_LightVector(GLST_DATA_PTR GLST_Data, int lightID, fx16 x, fx16 y, fx16 z)
{
	GLST_Data->lightVec[lightID].x = x;
	GLST_Data->lightVec[lightID].y = y;
	GLST_Data->lightVec[lightID].z = z;

	// ���f
	NNS_G3dGlbLightVector(lightID,
					GLST_Data->lightVec[lightID].x,
					GLST_Data->lightVec[lightID].y,
					GLST_Data->lightVec[lightID].z);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�J���[�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	lightID		���C�g�ԍ�	(0�`3)
 *@param	rgb			���C�g�̒l
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_LightColor(GLST_DATA_PTR GLST_Data, int lightID, GXRgb rgb)
{
	GLST_Data->Color[lightID] = rgb;
	
	// ���f
	NNS_G3dGlbLightColor(lightID,
			GLST_Data->Color[lightID]);
			
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�f�B�t���[�Y�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	rgb				�F
 *@param	IsSetVtxColor	���_�J���[�Ƃ��Ă��悤���邩
 *@param	setDiffAmb		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialDiff(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsSetVtxColor, BOOL setDiffAmb)
{
	GLST_Data->Diff=rgb;
	GLST_Data->IsSetVtxColor = IsSetVtxColor;

	if(setDiffAmb == TRUE){
		GLST_Reflect(GLST_Data, GLST_DIFF);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A���r�G���g�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	rgb				�F
 *@param	setDiffAmb		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialAmb(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setDiffAmb)
{
	GLST_Data->Amb = rgb;

	if(setDiffAmb == TRUE){
		GLST_Reflect(GLST_Data, GLST_AMB);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�X�y�L�����[�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	rgb				�F
 *@param	IsShininess		���ʔ��ˋP�x�e�[�u���̃f�B�Z�[�u��/�C�l�[�u���t���O
 *@param	setSpecEmi		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialSpec(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsShininess, BOOL setSpecEmi)
{
	GLST_Data->Spec = rgb;
	GLST_Data->IsShininess = IsShininess;

	if(setSpecEmi == TRUE){
		GLST_Reflect(GLST_Data, GLST_SPEC);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�G�~�b�V�����ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	rgb				�F
 *@param	setSpecEmi		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MaterialEmi(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setSpecEmi)
{
	GLST_Data->Emi = rgb;

	if(setSpecEmi == TRUE){
		GLST_Reflect(GLST_Data, GLST_EMI);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�g�t���O�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	light			�ǂ̃��C�g�̐ݒ肩
 *@param	on_off			���C�g��_��:TRUE	���C�g������:FALSE
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlLightFlag(GLST_DATA_PTR GLST_Data, int light, BOOL on_off, BOOL setPolyAttr)
{
	if(on_off == TRUE){
		if(GLST_Data->LightFlag & light){
			return;
		}
	}else{
		if(!(GLST_Data->LightFlag & light)){
			return;
		}
	}
	
	GLST_Data->LightFlag ^= light;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_LIGHT_FLAG);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�|���S�����[�h�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	polyMode		�|���S�����[�h
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlPolyMode(GLST_DATA_PTR GLST_Data, GXPolygonMode polyMode, BOOL setPolyAttr)
{
	GLST_Data->polyMode = polyMode;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_POLYGON_MODE);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�����O���[�h�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	cullMode		�J�����O���[�h
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlCullMode(GLST_DATA_PTR GLST_Data, GXCull cullMode, BOOL setPolyAttr)
{
	GLST_Data->cullMode = cullMode;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_CULL_MODE);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�|���S��ID�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	polygonID		�|���S��ID
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlPolyID(GLST_DATA_PTR GLST_Data, int polygonID, BOOL setPolyAttr)
{
	GLST_Data->polygonID = polygonID;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_POLYGON_ID);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A���t�@�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	alpha			���l
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlAlpha(GLST_DATA_PTR GLST_Data, int alpha, BOOL setPolyAttr)
{
	GLST_Data->alpha = alpha;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_ALPHA);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���̑��̃t���O�ݒ�	
 *
 *@param	GLDT_Data	�O���[�o���ȏ��
 *@param	flag			�t���O�̒l�i�e�t���O�̘_���a�j
 *@param	on_off			�t���O�𗧂Ă�̂�(TRUE)�A���낷�̂�(FALSE)
 *@param	setPolyAttr		���f�����邩	TRUE:���f������
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void GLST_MdlMisc(GLST_DATA_PTR GLST_Data, int flag, BOOL on_off, BOOL setPolyAttr)
{
	if(on_off == TRUE){
		if(GLST_Data->misc & flag){
			return;
		}
	}else{
		if(!(GLST_Data->misc & flag)){
			return;
		}
	}

	GLST_Data->misc ^= flag;

	if(setPolyAttr == TRUE){
		GLST_Reflect(GLST_Data, GLST_LIGHT_FLAG);
	}
}
