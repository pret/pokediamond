//============================================================================================
/**
 * @file	bounding_box.c
 * @brief	3D���f���̃J�������O���菈��
 * @author	Nozomu Saito
 * @date	2005.10.28
 */
//============================================================================================

#include "bounding_box.h"

#ifdef PM_DEBUG
///#define DRAW_BOUNDING_BOX	//�o�E���f�B���O�{�b�N�X�\��
#endif //PM_DEBUG


static void SetBoxSize( const fx16 x,
						const fx16 y,
						const fx16 z,
						const fx16 width,
						const fx16 height,
						const fx16 depth,
						GXBoxTestParam *outBox);

static u32 CheckBoundingBox( const GXBoxTestParam	*inBox );
static void CulcFx32toFx16(const fx32 inFx32, fx16 *outFx16, int *outMul);

#ifdef DRAW_BOUNDING_BOX
static void DrawBox( const GXBoxTestParam *inBox );
#endif //DRAW_BOUNDING_BOX

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�����O�`�F�b�N
 *
 *@param	object_p		�����_�[�I�u�W�F
 *@param	trans_p			���s�ړ��l
 *@param	rot_p			��]�s��
 *@param	scale_p			�g�k�l
 *
 *@return	u32			0�ȊO�̒l�ł���΁A�{�b�N�X�̈ꕔ�܂��͑S�������̐ϓ�
 *						0�ł���΁A�{�b�N�X�̑S�Ă����̐ϊO
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModel(	const NNSG3dResMdl* model_p,
							const VecFx32* trans_p,
							const MtxFx33* rot_p,
							const VecFx32* scale_p )
{
	u32 check_ret;		// �`�F�b�N�̖߂�l�p
	GXBoxTestParam bounding_box;
	VecFx32 obj_box_trans;
	NNSG3dResMdlInfo*	model_info;		// ���f���f�[�^����{�b�N�X�e�X�g�p�p�����[�^�擾�p

	obj_box_trans = *trans_p;
	
	model_info = NNS_G3dGetMdlInfo( model_p );			// ���f�����\�[�X�C���t�H�f�[�^�擾

	SetBoxSize( 
			model_info->boxX,
			model_info->boxY,
			model_info->boxZ,
			model_info->boxW,	// ��
			model_info->boxH,	// ����
			model_info->boxD,	// ���s��
			&bounding_box);

	//
	// ���W���Z�b�g
	//
	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(&obj_box_trans);
	// �p�x�ݒ�
	NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();		//�@�W�I���g���R�}���h��]��

	
	// ��̃{�b�N�X�e�X�g�̔��̒l��posScale�ł����邱�Ƃɂ��{���̒l�ɂȂ�
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( model_info->boxPosScale,
					model_info->boxPosScale,
					model_info->boxPosScale );
	
	//
	// �`�F�b�N
	//
	check_ret = CheckBoundingBox(&bounding_box);	// �`�F�b�N

#ifdef DRAW_BOUNDING_BOX
	// �{�b�N�X�e�X�g�̔���`��@����Ń`�F�b�N�p�̃{�b�N�X���ǂ��ɕ`�悳��Ă��邩���킩��܂�
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX
	
	NNS_G3dGePopMtx(1);

	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�����O�`�F�b�N(���\�[�X���g�p���Ȃ�)
 *
 *@param	trans_p			���s�ړ��l
 *@param	rot_p			��]�s��
 *@param	scale_p			�g�k�l
 *
 *@return	u32			0�ȊO�̒l�ł���΁A�{�b�N�X�̈ꕔ�܂��͑S�������̐ϓ�
 *						0�ł���΁A�{�b�N�X�̑S�Ă����̐ϊO
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModelNonResource(	const VecFx32* trans_p,
									const fx32 inBoxW,
									const fx32 inBoxH,
									const fx32 inBoxD
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ )
{
	u32 check_ret;		// �`�F�b�N�̖߂�l�p
	GXBoxTestParam bounding_box;

	BOUNDING_BOX	box;

	BB_MakeBoundingBox(inBoxW, inBoxH, inBoxD, &box);

	SetBoxSize( 
			0,
			0,
			0,
			box.w,	// ��
			box.h,	// ����
			box.d,	// ���s��
			&bounding_box);

	//
	// ���W���Z�b�g
	//
	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);
	// �p�x�ݒ�
	///NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	///NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();		//�@�W�I���g���R�}���h��]��

	// ��̃{�b�N�X�e�X�g�̔��̒l��posScale�ł����邱�Ƃɂ��{���̒l�ɂȂ�
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( box.ScaleW*FX32_ONE,
					box.ScaleH*FX32_ONE,
					box.ScaleD*FX32_ONE );

	check_ret = CheckBoundingBox(&bounding_box);	// �`�F�b�N

#ifdef DRAW_BOUNDING_BOX
	// �{�b�N�X�e�X�g�̔���`��@����Ń`�F�b�N�p�̃{�b�N�X���ǂ��ɕ`�悳��Ă��邩���킩��܂�
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX

	NNS_G3dGePopMtx(1);
	
	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�J�����O�`�F�b�N(���\�[�X���g�p���Ȃ�)
 *
 *@param	trans_p			���s�ړ��l
 *@param	rot_p			��]�s��
 *@param	scale_p			�g�k�l
 *
 *@return	u32			0�ȊO�̒l�ł���΁A�{�b�N�X�̈ꕔ�܂��͑S�������̐ϓ�
 *						0�ł���΁A�{�b�N�X�̑S�Ă����̐ϊO
 *
 */
//-----------------------------------------------------------------------------
u32	BB_CullingCheck3DModelNonResQuick(	const VecFx32* trans_p,
									const BOUNDING_BOX *inBox
									/*const MtxFx33* rot_p*/
									/*const VecFx32* scale_p*/ )
{
	u32 check_ret;		// �`�F�b�N�̖߂�l�p
	GXBoxTestParam bounding_box;

	SetBoxSize( 
			0,
			0,
			0,
			inBox->w,	// ��
			inBox->h,	// ����
			inBox->d,	// ���s��
			&bounding_box);

	//
	// ���W���Z�b�g
	//
	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);
	// �p�x�ݒ�
	///NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	///NNS_G3dGlbSetBaseScale(scale_p);
	
	NNS_G3dGlbFlush();		//�@�W�I���g���R�}���h��]��

	// ��̃{�b�N�X�e�X�g�̔��̒l��posScale�ł����邱�Ƃɂ��{���̒l�ɂȂ�
	NNS_G3dGePushMtx();
	NNS_G3dGeScale( inBox->ScaleW*FX32_ONE,
					inBox->ScaleH*FX32_ONE,
					inBox->ScaleD*FX32_ONE );

	check_ret = CheckBoundingBox(&bounding_box);	// �`�F�b�N

#ifdef DRAW_BOUNDING_BOX
	// �{�b�N�X�e�X�g�̔���`��@����Ń`�F�b�N�p�̃{�b�N�X���ǂ��ɕ`�悳��Ă��邩���킩��܂�
	DrawBox(&bounding_box);
#endif //DRAW_BOUNDING_BOX

	NNS_G3dGePopMtx(1);
	
	return check_ret;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�E���f�B���O�{�b�N�X�̍쐬
 *
 *@param	inBoxW			��
 *@param	inBoxH			����
 *@param	inBoxD			���s��
 *@param	outBox			�쐬����o�E���f�B���O�{�b�N�X�̃o�b�t�@
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void BB_MakeBoundingBox(const fx32 inBoxW, const fx32 inBoxH, const fx32 inBoxD, BOUNDING_BOX *outBox)
{
	CulcFx32toFx16(inBoxW, &outBox->w, &outBox->ScaleW);
	CulcFx32toFx16(inBoxH, &outBox->h, &outBox->ScaleH);
	CulcFx32toFx16(inBoxD, &outBox->d, &outBox->ScaleD);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�E���f�B���O�{�b�N�X�Z�b�g
 *
 *@param	x		�X���W
 *@param	y		�Y���W
 *@param	z		�Z���W
 *@param	width	��
 *@param	height	����
 *@param	depth	���s��
 *@param	outBox	�{�b�N�X�e�X�g�p�p�����[�^�i�[�A�h���X
 *
 *@return	�Ȃ� 
 *
 */
//-----------------------------------------------------------------------------
static void SetBoxSize( const fx16 x,
						const fx16 y,
						const fx16 z,
						const fx16 width,
						const fx16 height,
						const fx16 depth,
						GXBoxTestParam *outBox)
{
	//
	// �p�����[�^���Z�b�g
	//
	outBox->x		= x;				// ����̂����W	
	outBox->y		= y;				// ����̂����W
	outBox->z		= z;				// ����̂����W
	outBox->width	= width;			// �l�p�̕�
	outBox->height	= height;			// �l�p�̍���
	outBox->depth	= depth;			// �����̂̉��s��
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�{�b�N�X�`�F�b�N
 *
 *@param	inBox	�{�b�N�X�e�X�g�p�p�����[�^�ւ̃|�C���^
 *
 *@return	u32		0�ȊO�̒l�ł���΁A�{�b�N�X�̈ꕔ�܂��͑S�������̐ϓ�
 *					0�ł���΁A�{�b�N�X�̑S�Ă����̐ϊO 
 *
 */
//-----------------------------------------------------------------------------
static u32 CheckBoundingBox( const GXBoxTestParam	*inBox )
{
	s32 result = 1;			// ����

	// �|���S���ݒ���s��
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,         
			GX_POLYGONMODE_MODULATE,
			GX_CULL_NONE,           
			0,                      
			0,                      
			GX_POLYGON_ATTR_MISC_FAR_CLIPPING
			| GX_POLYGON_ATTR_MISC_DISP_1DOT
			);

	//�|���S���A�g���r���[�g���f 
	NNS_G3dGeBegin( GX_BEGIN_TRIANGLES );							
	NNS_G3dGeEnd();	

	//
	// �{�b�N�X�e�X�g
	//
	NNS_G3dGeBoxTest( inBox );

	//
	// ���������
	//
	NNS_G3dGeFlushBuffer();

	//
	// ���ݒ肳��Ă���{�b�N�X�����̐ϓ����`�F�b�N
	//
	while ( G3X_GetBoxTestResult(&result) != 0 ) ;

	return result;
}

#ifdef DRAW_BOUNDING_BOX
//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�E���f�B���O�{�b�N�X��`��
 *
 *@param	inBox	�{�b�N�X�e�X�g�p�p�����[�^�ւ̃|�C���^
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
static void DrawBox( const GXBoxTestParam *inBox )
{
	//
	// ����`��
	//
	NNS_G3dGePolygonAttr(
			GX_LIGHTMASK_0,				// ���C�g�𔽉f���Ȃ�
			GX_POLYGONMODE_MODULATE,	// ���W�����[�V�������[�h
			GX_CULL_BACK,				// �J���o�b�N���s��
			1,							// �|���S���h�c
			31,							// �A���t�@�l
			GX_POLYGON_ATTR_MISC_NONE
			);
	
	// �`��J�n
	NNS_G3dGeBegin(GX_BEGIN_QUADS);           // ���_���X�g�̊J�n
                                        // (�l�p�`�|���S���ł̕`��錾)
	{
		NNS_G3dGeNormal(0, 1 << 9, 0);
		NNS_G3dGeColor(GX_RGB(16,16,16));
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z + inBox->depth);
		
		NNS_G3dGeNormal(0, -1 << 9, 0);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z + inBox->depth);
		
		NNS_G3dGeNormal(1 << 9, 0, 0);
		NNS_G3dGeVtx(   inBox->x + inBox->width,
						inBox->y,
					    inBox->z);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x + inBox->width,
						inBox->y + inBox->height,
						inBox->z);
		
		NNS_G3dGeNormal(-1 << 9, 0, 0);
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
					    inBox->z + inBox->depth);
		NNS_G3dGeVtx(	inBox->x,
						inBox->y,
						inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z );
		NNS_G3dGeVtx(   inBox->x,
						inBox->y + inBox->height,
					    inBox->z + inBox->depth);
						
	}
	NNS_G3dGeEnd();                            // ���_���X�g�̏I��
}
#endif //DRAW_BOUNDING_BOX

//----------------------------------------------------------------------------
/**
 *
 *@brief	fx32��fx16�ɗ��Ƃ����ޏ���
 *
 *@param	inFx32		fx32�̒l
 *@param	outFx16		���Ƃ�����fx16
 *@param	outMul		���̒l�ɖ߂����߂̔{����
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void CulcFx32toFx16(const fx32 inFx32, fx16 *outFx16, int *outMul)
{
	int i;
	u8 shift_count;
	u32 val32;
	u16 val16;
	shift_count = 0;
	val32 = (u32)inFx32;
	while(0x00007fff<=val32){
		val32 = (val32>>1);
		shift_count++;
	}
	val16 = val32;
	*outFx16 = (fx16)val16;
	(*outMul) = 1;
	for (i=0;i<shift_count;i++){
		(*outMul) *= 2;
	}
}
