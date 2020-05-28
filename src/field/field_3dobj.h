//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_3dobj.h
 *	@brief		�t�B�[���h�RD�I�u�W�F�N�g�ȈՍ쐬
 *	@author		tomoya takahashi
 *	@data		2006.04.25
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_3DOBJ_H__
#define __FIELD_3DOBJ_H__

#include <nnsys.h>

#undef GLOBAL
#ifdef	__FIELD_3DOBJ_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *	�y�g�p��̒��Ӂz
 *		�Ensb�`��2�ȏ�̂��̂��������ē���邱�Ƃ��o���܂��B
 *		�@���������̃V�X�e���ł́A
 *		�@���̒��̃C���f�b�N�X0�Ԗڂ̂��̂������K�p���܂��B
 *
 *		�E���k�ɔ�Ή��ł��B
 */
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��]�����萔
//=====================================
enum{
	FLD_3DROTA_WAY_X,
	FLD_3DROTA_WAY_Y,
	FLD_3DROTA_WAY_Z,
	FLD_3DROTA_WAY_NUM,
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�RD�I�u�W�F�N�g
//	���f���@�e�N�X�`��
//	��ނɂP�ł悢���̂ł��B
//=====================================
typedef struct {
	void*					pResMdl;		// ���f���ް�
	NNSG3dResMdlSet*		pModelSet;		// ���f���Z�b�g
	NNSG3dResMdl*			pModel;			// ���f�����\�[�X
	NNSG3dResTex*			pMdlTex;		// ���f���ɓ\��t����e�N�X�`��
} FLD_3DOBJ_MDL;

//-------------------------------------
//	�RD�I�u�W�F�N�g
//	�A�j��
//	��ނɂP�ł悢���̂ł��B
//=====================================
typedef struct {
	void*					pResAnm;		// �A�j�����\�[�X
	void*					pOneResAnm;		// 1�؂��������\�[�X
	NNSG3dAnmObj*			pAnmObj;			// �A�j���[�V�����I�u�W�F
	fx32 frame;
	BOOL res_copy;
} FLD_3DOBJ_ANM;

//-------------------------------------
//	�RD�`��I�u�W�F�N�g
//	�o�������I�u�W�F�N�g�̐����K�v�Ȃ��̂ł��B
//=====================================
typedef struct {
	NNSG3dRenderObj			render;		// �����_�[�I�u�W�F�N�g
	VecFx32 matrix;	// ���W
	VecFx32 scale;	// �g�k
	BOOL	draw_flg;	// �`��t���O
	u16		rota[ FLD_3DROTA_WAY_NUM ];// ��]�pX
	u16		dummy;
} FLD_3DOBJ;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// ���f��
GLOBAL void FLD_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap );
GLOBAL void FLD_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl );

// �A�j��
GLOBAL void FLD_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator );
GLOBAL void FLD_3DObjAnmLoad_Data( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, void* p_data, NNSFndAllocator* pallocator );
GLOBAL void FLD_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator );
GLOBAL BOOL FLD_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm, fx32 add );
GLOBAL void FLD_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm, fx32 add );
GLOBAL void FLD_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num );
GLOBAL fx32 FLD_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm );

// �`��I�u�W�F
GLOBAL void FLD_3DObjInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* cp_mdl );
GLOBAL void FLD_3DObjAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm );
GLOBAL void FLD_3DObjDraw( FLD_3DOBJ* p_draw );
GLOBAL void FLD_3DObjSetDraw( FLD_3DOBJ* p_draw, BOOL flag );
GLOBAL BOOL FLD_3DObjGetDraw( const FLD_3DOBJ* cp_draw );
GLOBAL void FLD_3DObjSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_3DObjGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
GLOBAL void FLD_3DObjSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_3DObjGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
GLOBAL void FLD_3DObjSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way );
GLOBAL u16 FLD_3DObjGetRota( FLD_3DOBJ* p_draw, u32 way );



#undef	GLOBAL
#endif		// __FIELD_3DOBJ_H__

