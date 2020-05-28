//=============================================================================================
/**
 * @file	calctool.h
 * @brief	�v�Z�֌W
 * @author	mori
 * @date	2004.10.28
 *
 */
//=============================================================================================
#ifndef	__CALCTOOL_H__
#define	__CALCTOOL_H__
#undef GLOBAL
#ifdef __CALCTOOL_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#include "assert.h"


//=============================================================================================
//	�萔��`
//=============================================================================================
#define	AFFINE_MAX_NORMAL	( 0 )	// �g�k�̊p�x��0�`0xffff�Ōv�Z
#define	AFFINE_MAX_256		( 1 )	// �g�k�̊p�x��0�`255�Ōv�Z
#define	AFFINE_MAX_360		( 2 )	// �g�k�̊p�x��0�`359�Ōv�Z

#define FX_GET_ROTA_NUM(x)	( (x*0xffff) / 360 )	// FX_SinIdx CosIdx�̈����̉�]�l�����߂�

#define GF_RAND_MAX			( 0xffff )		// gf_rand()�̍ő吔
#define GF_MT_RAND_MAX		( 0xffffffff )	// gf_mtRand()�̍ő吔

//=============================================================================================
//	�v���g�^�C�v�錾
//=============================================================================================
#define ERRCHECK_ON_DEG_TO_XXX	//���̒�`�𖳌��ɂ����DEG�֐��̃G���[�`�F�b�N�𖳌��ɂł���

GLOBAL const fx32 FixSinCosTbl[360+90];
GLOBAL const u16 RotKey360Tbl[360];
 #define _Sin360( a ) (FixSinCosTbl[(a)])
 #define _Cos360( a ) (FixSinCosTbl[(a)+90])
 #define _RotKey( a ) (RotKey360Tbl[a])
/**
 *	@brief	�x���@�Ŏw�肵���p�x����A���ꂼ��̑Ή�����l���擾����
 *	@param	deg	u16:0-359�܂ł̕ϐ�
 */
 ///SinIdx(),CosIdx(),Index�L�[�̒l��Ԃ�(��荞�݂Ȃ�)
 GLOBAL fx32 Sin360(u16 deg);
 GLOBAL fx32 Cos360(u16 deg);
 GLOBAL u16	RotKey(u16 deg);
 ///SinIdx(),CosIdx(),Index�L�[�̒l��Ԃ�(��荞�݂���)
 GLOBAL fx32 Sin360R(u16 deg);
 GLOBAL fx32 Cos360R(u16 deg);
 GLOBAL u16	RotKeyR(u16 deg);
 ///SinIdx(),CosIdx()�̒l��Ԃ�(fx32�^�������Ɏ��A��荞�݂���)
 GLOBAL fx32 Sin360FX(fx32 deg);
 GLOBAL fx32 Cos360FX(fx32 deg);

GLOBAL u32 gf_get_seed(void);		// �����̎�̎擾
GLOBAL void gf_srand(u32 seed);		// �����̏�����
GLOBAL u16 gf_rand(void);			// �����擾�i0 - 65535)
GLOBAL u32 gf_fix_rand( u32 seed );	// ���n���Ď擾���闐��

GLOBAL void gf_mtSrand(u32 s);		// MT�������������֐�
GLOBAL u32 gf_mtRand(void);			// MT�������擾

//==============================================================================
/**
 *	�m���v�Z�p�����_���擾�֐�
 * 
 * @param   inDinominate	�m������
 *
 * @retval  u16		0�`inDinominate-1�̐�
 */
//==============================================================================
inline u16 gf_p_rand(const u16 inDinominate)
{
	GF_ASSERT(inDinominate != 0);
	if (inDinominate <= 1){
		return 0;
	}else{
		u16 per;
		u16 val;
		per = (0xffff/inDinominate)+1;
		val = gf_rand()/per;
		GF_ASSERT((val<inDinominate)&&"ERROR:Random Calc Error!");//�O�̂���
		return val;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BG�EOBJ��Affine�p�ϊ��s����쐬 ( 2D )
 *
 * @param	mtx			�ϊ��s��i�[�ꏊ
 * @param	rad			�p�x ( MAX = 0xffff )
 * @param	scale_x		X�����̊g�嗦
 * @param	scale_y		Y�����̊g�嗦
 * @param	mode		�p�x�ϊ����[�h
 *
 * @return	�ϊ��s��
 *
 * @li	mode = AFFINE_MAX_256 : theta < 256
 * @li	mode = AFFINE_MAX_360 : theta < 360
 * @li	scale_x(y) = FX32_ONE : �P�{
 */
//--------------------------------------------------------------------------------------------
GLOBAL void AffineMtxMake_2D( MtxFx22 * mtx, u16 rad, fx32 scale_x, fx32 scale_y, u8 mode );


///==========================================
//�x�N�g�����Z�n�̃}�N��
///==========================================
//�x�N�g���R�s�[
#define VEC_COPY(a,b)	{ \
 (a)->x = (b)->x;	\
 (a)->y = (b)->y;	\
 (a)->z = (b)->z;	\
}

//�x�N�g����Z
#define VEC_MUL(dest,a,b)	{	\
 (dest)->x = FX_Mul((a)->x,(b)->x);	\
 (dest)->y = FX_Mul((a)->y,(b)->y);	\
 (dest)->z = FX_Mul((a)->z,(b)->z);	\
}
//�x�N�g�����Z
#define VEC_DIV(dest,a,b)	{	\
 (dest)->x = FX_Div((a)->x,(b)->x);	\
 (dest)->y = FX_Div((a)->y,(b)->y);	\
 (dest)->z = FX_Div((a)->z,(b)->z);	\
}
//�x�N�g���̎����{
#define VEC_APPLYM(dest,a,fval) {	\
 (dest)->x = FX_MUL((a)->x,fval);	\
 (dest)->y = FX_MUL((a)->y,fval);	\
 (dest)->z = FX_MUL((a)->z,fval);	\
}
//�x�N�g���������Ŋ���
#define VEC_APPLYD(dest,a,fval) {	\
 (dest)->x = FX_Div((a)->x,fval);	\
 (dest)->y = FX_Div((a)->y,fval);	\
 (dest)->z = FX_Div((a)->z,fval);	\
}


//-----------------------------------------------------------------------------
/**
 *		
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	���ʂQ���_����Q�[�t���Ǝ���]�����l���擾����
 *
 *	@param	x0		A�_�����W
 *	@param	y0		A�_�����W
 *	@param	x1		B�_�����W
 *	@param	y1		B�_�����W
 *
 *	@return	�Q�[�t���Ǝ���]���������l
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorMove( s32 x0, s32 y0, s32 x1, s32 y1 );


//----------------------------------------------------------------------------
/**
 *	@brief	���ʂQ���_����C�ӂ̓���l���擾����
 *
 *	@param	x0		A�_�����W
 *	@param	y0		A�_�����W
 *	@param	x1		B�_�����W
 *	@param	y1		B�_�����W
 *	@param	roopnum	�P��]��\������
 *
 *	@return	roopnum�P�ʂ̓���l
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorNum( s32 x0, s32 y0, s32 x1, s32 y1, u16 roopnum );


//----------------------------------------------------------------------------
/**
 *	@brief	���ʂQ���_����C�ӂ̓���l���擾����
 *
 *	@param	x0		A�_�����W
 *	@param	y0		A�_�����W
 *	@param	x1		B�_�����W
 *	@param	y1		B�_�����W
 *	@param	r		����a	���̔��a�ŏ�ňړ��������������߂܂�
 *
 *	@return	�ړ�����
 *
 *	���p���@
 *		r�̉~�������߁A�ړ��������~���̉��p�[�Z���g�ɓ����邩�ɂ��A��]�p�x�����߂邱�Ƃ��o���܂�
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectorDistance( s32 x0, s32 y0, s32 x1, s32 y1, u32 r );

//----------------------------------------------------------------------------
/**
 *	@brief	���a�Ƌ������猻�݂̉�]�p���擾����
 *
 *	@param	r		���a
 *	@param	dist	�ړ�����
 *
 *	@return	�ړ���������
 */
//-----------------------------------------------------------------------------
GLOBAL s32 CalcTool_CircleVectroDistRotaGet( u16 r, s32 dist );


#undef GLOBAL
#endif	/*__CALCTOOL_H__*/
