//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		render_oam.c
 *@brief	�����_���[�p�O���[�o��OAM�}�l�[�W���V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "gflib/clact.h"

#define	__RENDER_OAM_H_GLOBAL
#include "include/system/render_oam.h"

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
//	
//	�O���[�o��OAM�}�l�[�W���f�[�^
//	
//=====================================
typedef struct{
	NNSG2dOamManagerInstance MainMan;	// ���C��OAM
	NNSG2dOamManagerInstance SubMan;	// �T�uOAM
	int heap;
} REND_OAM_DATA;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static BOOL CallBackAddOamMain( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ );
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ );
static u16 CallBackAddAffineMain( const MtxFx22* mtx );
static u16 CallBackAddAffineSub( const MtxFx22* mtx );


// ����͒ʐM�A�C�R���p���m�ۂ��܂���
static void	REND_OAMInit_Simple(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap);


//-----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
*/
//-----------------------------------------------------------------------------
static REND_OAM_DATA* RendOam;		//�@�����_���ŗp��OAM�f�[�^

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_�����g��OAM�}�l�[�W���̍쐬
 *
 *@param	mainOamStart		���C��OAM�Ǘ��J�n�ԍ�
 *@param	mainOamNum			���C��OAM�Ǘ���
 *@param	mainAffineStart		���C���A�t�B���Ǘ��J�n�ԍ�
 *@param	mainAffineNum		���C���A�t�B���Ǘ���
 *@param	subOamStart			�T�uOAM�Ǘ��J�n�ԍ�
 *@param	subOamNum			�T�uOAM�Ǘ���
 *@param	subAffineStart		�T�u�A�t�B���Ǘ��J�n�ԍ�
 *@param	subAffineNum		�T�u�A�t�B���Ǘ���
 *@param	heap				�g�p�q�[�v
 *
 *@return	none
 *
 * �����ō쐬���ꂽOAM�}�l�[�W�����F�Ŏg�p���鎖�ɂȂ�܂��B
 *
 *
 * ���C���ʂ�0�`4��ʐM�A�C�R�����g�p���邽�߁@
 * �������Ȃ��Ă��f�t�H���g�ŒʐM�p�Ɋm�ۂ��܂�
 *
 *
 */
//-----------------------------------------------------------------------------
void	REND_OAMInit(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap)
{
	int mo_start;
	int mo_num;
	int ma_start;
	int ma_num;
	
	// �K��4�`124�̊Ԃ̒l�ɂ���
	if( mainOamStart < 4 ){
		mo_start = 4;

		if( mainOamNum > 124 ){
			mo_num	 = mainOamNum - (4 - mainOamStart);
		}else{
			mo_num = mainOamNum;
		}
	}else{
		mo_start = mainOamStart;
		mo_num	 = mainOamNum;
	}

	// �K��1�`31�̊Ԃ̒l�ɂ���
	if( mainAffineStart < 1 ){
		ma_start = 1;

		if( mainAffineNum > 30 ){
			ma_num	 = mainAffineNum - (1 - mainAffineStart);
		}else{
			ma_num = mainAffineNum;
		}
	}else{
		ma_start = mainAffineStart;
		ma_num	 = mainAffineNum;
	}
	
	REND_OAMInit_Simple( mo_start, mo_num, ma_start, 
			ma_num,  subOamStart, subOamNum, subAffineStart, 
			subAffineNum, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_�����g��OAM�}�l�[�W���̍쐬
 *
 *@param	mainOamStart		���C��OAM�Ǘ��J�n�ԍ�
 *@param	mainOamNum			���C��OAM�Ǘ���
 *@param	mainAffineStart		���C���A�t�B���Ǘ��J�n�ԍ�
 *@param	mainAffineNum		���C���A�t�B���Ǘ���
 *@param	subOamStart			�T�uOAM�Ǘ��J�n�ԍ�
 *@param	subOamNum			�T�uOAM�Ǘ���
 *@param	subAffineStart		�T�u�A�t�B���Ǘ��J�n�ԍ�
 *@param	subAffineNum		�T�u�A�t�B���Ǘ���
 *@param	heap				�g�p�q�[�v
 *
 *@return	none
 *
 * �����ō쐬���ꂽOAM�}�l�[�W�����F�Ŏg�p���鎖�ɂȂ�܂��B
 */
//-----------------------------------------------------------------------------
static void	REND_OAMInit_Simple(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap)
{
	BOOL result;
	
	GF_ASSERT(RendOam == NULL);

	// �O���[�o���f�[�^�쐬
	RendOam = sys_AllocMemory(heap, sizeof(REND_OAM_DATA));
	GF_ASSERT(RendOam);
	RendOam->heap = heap;

	// ���C��OAM�o�b�t�@�쐬
	result = NNS_G2dGetNewOamManagerInstance(
			&RendOam->MainMan,
			mainOamStart, mainOamNum,
			mainAffineStart, mainAffineNum,
			NNS_G2D_OAMTYPE_MAIN );

	GF_ASSERT( result );

	// �T�uOAM�o�b�t�@�쐬
	result = NNS_G2dGetNewOamManagerInstance(
			&RendOam->SubMan,
			subOamStart, subOamNum,
			subAffineStart, subAffineNum,
			NNS_G2D_OAMTYPE_SUB );

	GF_ASSERT( result );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_�����g�p����OAM�}�l�[�W����OAM�]�����s���܂��B
 *
 *@param	none
 *
 *@return	none
 *
 * �S�̂łP��s�������ő��v�ł��B
 * ���̊֐����P�t���[���ŕ�����ĂԂƐ���ɕ\������܂���B
 *
 */
//-----------------------------------------------------------------------------
void REND_OAMTrans(void)
{
	if(RendOam){
		NNS_G2dApplyAndResetOamManagerBuffer( &RendOam->MainMan );
		NNS_G2dApplyAndResetOamManagerBuffer( &RendOam->SubMan );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���p�̃O���[�o��OAM�}�l�[�W���f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void REND_OAM_Delete(void)
{
	GF_ASSERT(RendOam);
	
	// OAM���W�X�^������
	REND_OAM_UtilOamRamClear_Main( RendOam->heap );	
	REND_OAM_UtilOamRamClear_Sub( RendOam->heap );	

	sys_FreeMemoryEz(RendOam);
	RendOam = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��������
 *
 *@param	pSurface		����������T�[�t�F�[�X�̎��̂̃|�C���^
 *@param	pRect			�T�[�t�F�[�X�̋�`
 *@param	type			�T�[�t�F�[�X�^�C�v
 *@param	pSetRenderer	���̃T�[�t�F�[�X��ݒ肷�郌���_���[�i�ݒ肵�Ȃ��Ƃ��́@NULL�j
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void REND_OAM_SetSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer)
{
	GF_ASSERT(RendOam&&("����������Ă��܂���"));
	
	// �T�[�t�F�[�X������
	if(type == NNS_G2D_SURFACETYPE_MAIN2D){
		RNDP_InitSurface(pSurface, pRect,
				CallBackAddOamMain, CallBackAddAffineMain,
				RNDP_CallBackCulling, type,
				pSetRenderer);
	}else{
		RNDP_InitSurface(pSurface, pRect,
				CallBackAddOamSub, CallBackAddAffineSub,
				RNDP_CallBackCulling, type,
				pSetRenderer);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���p�̃O���[�o��OAM�}�l�[�W���f�[�^���쐬�ς݂��`�F�b�N
 *
 *@param	none
 *
 *@retval	TURE		�쐬����Ă���
 *@retval	FALSE		�쐬����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL REND_OAM_Live(void)
{
	if(RendOam == NULL){
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�}�l�[�W���C���X�^���X�擾
 *
 *	@param	flag	���C����ʗp���T�u��ʗp��
 *
 *	@return	OAM�}�l�[�W���[�C���X�^���X
 *
 * flag
	REND_OAM_MAIN,		// ���C�����
	REND_OAM_SUB,		// �T�u���
 */
//-----------------------------------------------------------------------------
NNSG2dOamManagerInstance* REND_OAM_GetOamManagerInstance( int flag )
{
	NNSG2dOamManagerInstance* p_ret;
	
	// ����������Ă��܂���
	GF_ASSERT( RendOam );
	
	if( flag == REND_OAM_MAIN ){
		p_ret = &RendOam->MainMan;
	}else{
		p_ret = &RendOam->SubMan;
	}

	return p_ret;
}


//----------------------------------------------------------------------------
/**
 * [���C����ʗp]
 *	@brief	OAMRAM�̃N���A
 *
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void REND_OAM_UtilOamRamClear_Main( int heap )
{
	CLACT_UtilOamRamClear_Main( heap );
}

//----------------------------------------------------------------------------
/**
 * [�T�u��ʗp]
 *	@brief	OAMRAM�̃N���A
 *
 *	@param	heap	�q�[�v
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void REND_OAM_UtilOamRamClear_Sub( int heap )
{
	CLACT_UtilOamRamClear_Sub( heap );
}


//	Oam Affine �o�^�֐��쐬��
//-----------------------------------------------------------------------------
/**
 *@brief				OAM��ǉ����邽�߂ɌĂ΂��R�[���o�b�N�֐�
 *
 *@param	pOam�F�ǉ����ׂ�OAM�ւ̃|�C���^
 *@param	affineIndex�F����OAM���g�p����Affine�C���f�b�N�X
 *@param	BOOL �F�{�pAffine���ǂ���
 *
 *@retval	�����FTRUE
 *@retval	���s�FFALSE
 *
 ----------------------------------------------------------------------------*/
// ���C����ʗp
static BOOL CallBackAddOamMain( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	BOOL ret;
	ret = NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->MainMan, pOam, affineIndex );
	GF_ASSERT( ret );		// �o�^�I�[�o�[

	return ret;
}

// �T�u��ʗp
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	BOOL ret;
    ret = NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->SubMan, pOam, affineIndex );
	GF_ASSERT( ret );		// �o�^�I�[�o�[

	return ret;
}


//-----------------------------------------------------------------------------
/**
 *@brief	Affine�p�����[�^��ǉ����邽�߂ɌĂ΂��֐��ł��B
 *
 *@param	mtx�F�ǉ����ׂ�Affine�ϊ��s��ւ̃|�C���^
 *
 *@return	�ǉ�����Affine�p�����[�^��Index
 *
 */
 //----------------------------------------------------------------------------
// ���C����ʗp
static u16 CallBackAddAffineMain( const MtxFx22* mtx )
{
	u16 ret;
    ret =  NNS_G2dEntryOamManagerAffine( &RendOam->MainMan, mtx );
	GF_ASSERT( ret != NNS_G2D_OAM_AFFINE_IDX_NONE );
	
	return ret;
}

// �T�u��ʗp
static u16 CallBackAddAffineSub( const MtxFx22* mtx )
{
	u16 ret;
    ret = NNS_G2dEntryOamManagerAffine( &RendOam->SubMan, mtx );
	GF_ASSERT( ret != NNS_G2D_OAM_AFFINE_IDX_NONE );

	return ret;
}
