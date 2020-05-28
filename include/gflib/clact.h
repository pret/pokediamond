//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact.h
 *@brief	�Z���A�N�^�[
 *@author	tomoya takahashi
 *@data		2005.05.19
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef _CLACT_H__
#define	_CLACT_H__

#include <nnsys.h>

#undef	GLOBAL
#ifdef	_CLACT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------

//--------------------------------------------------------------
//	OAM�^�C�v
//--------------------------------------------------------------
#define OAMTYPE_8x8				(0)						// OAM�A�N�^�[�w�b�_ OAM�^ 8x8
#define OAMTYPE_16x16			(1)						// 16x16
#define OAMTYPE_32x32			(2)						// 32x32
#define OAMTYPE_64x64			(3)						// 64x64
#define OAMTYPE_16x8			(4)						// 16x8
#define OAMTYPE_32x8			(5)						// 32x8
#define OAMTYPE_32x16			(6)						// 32x16
#define OAMTYPE_64x32			(7)						// 64x32
#define OAMTYPE_8x16			(8)						// 8x16
#define OAMTYPE_8x32			(9)						// 8x32
#define OAMTYPE_16x32			(10)					// 16x32
#define OAMTYPE_32x64			(11)					// 32x64

//--------------------------------------------------------------
//	OAM BG�v���C�I���e�B
//--------------------------------------------------------------
#define OAMBGPRI_0				(0)
#define OAMBGPRI_1				(1)
#define OAMBGPRI_2				(2)
#define OAMBGPRI_3				(3)

//--------------------------------------------------------------
//	OAM �p���b�gNo
//--------------------------------------------------------------
#define OAMPALNO_0				(0)
#define OAMPALNO_1				(1)
#define OAMPALNO_2				(2)
#define OAMPALNO_3				(3)
#define OAMPALNO_4				(4)
#define OAMPALNO_5				(5)
#define OAMPALNO_6				(6)
#define OAMPALNO_7				(7)
#define OAMPALNO_8				(8)
#define OAMPALNO_9				(9)
#define OAMPALNO_10				(10)
#define OAMPALNO_11				(11)
#define OAMPALNO_12				(12)
#define OAMPALNO_13				(13)
#define OAMPALNO_14				(14)
#define OAMPALNO_15				(15)

//--------------------------------------------------------------
//	OAM�g�k�p�����[�^�ԍ�
//--------------------------------------------------------------
#define OAMAFFNO_0				(0)
#define OAMAFFNO_1				(1)
#define OAMAFFNO_2				(2)
#define OAMAFFNO_3				(3)
#define OAMAFFNO_4				(4)
#define OAMAFFNO_5				(5)
#define OAMAFFNO_6				(6)
#define OAMAFFNO_7				(7)
#define OAMAFFNO_8				(8)
#define OAMAFFNO_9				(9)
#define OAMAFFNO_10				(10)
#define OAMAFFNO_11				(11)
#define OAMAFFNO_12				(12)
#define OAMAFFNO_13				(13)
#define OAMAFFNO_14				(14)
#define OAMAFFNO_15				(15)
#define OAMAFFNO_16				(16)
#define OAMAFFNO_17				(17)
#define OAMAFFNO_18				(18)
#define OAMAFFNO_19				(19)
#define OAMAFFNO_20				(20)
#define OAMAFFNO_21				(21)
#define OAMAFFNO_22				(22)
#define OAMAFFNO_23				(23)
#define OAMAFFNO_24				(24)
#define OAMAFFNO_25				(25)
#define OAMAFFNO_26				(26)
#define OAMAFFNO_27				(27)
#define OAMAFFNO_28				(28)
#define OAMAFFNO_29				(29)
#define OAMAFFNO_30				(30)
#define OAMAFFNO_31				(31)

//--------------------------------------------------------------
//	OBJ�L�����T�C�Y 16�F
//--------------------------------------------------------------
#define OBJ_CHAR_SIZE			(32)					// OBJ 1�L�����T�C�Y 32byte
#define OBJSIZE_8x8				(OBJ_CHAR_SIZE*1)		// 8x8�L�����T�C�Y
#define OBJSIZE_16x16			(OBJ_CHAR_SIZE*4)		// 16x16
#define OBJSIZE_32x32			(OBJ_CHAR_SIZE*16)		// 32x32
#define OBJSIZE_64x64			(OBJ_CHAR_SIZE*64)		// 64x64
#define OBJSIZE_16x8			(OBJ_CHAR_SIZE*2)		// 16x8
#define OBJSIZE_32x8			(OBJ_CHAR_SIZE*4)		// 32x8
#define OBJSIZE_32x16			(OBJ_CHAR_SIZE*8)		// 32x16
#define OBJSIZE_64x32			(OBJ_CHAR_SIZE*32)		// 64x32
#define OBJSIZE_8x16			(OBJ_CHAR_SIZE*2)		// 8x16
#define OBJSIZE_8x32			(OBJ_CHAR_SIZE*4)		// 8x32
#define OBJSIZE_16x32			(OBJ_CHAR_SIZE*8)		// 16x32
#define OBJSIZE_32x64			(OBJ_CHAR_SIZE*32)		// 32x64

//--------------------------------------------------------------
//	OBJ�L�����T�C�Y 256�F
//--------------------------------------------------------------
#define OBJ_CHAR_SIZE256		(64)					// OBJ 1�L�����T�C�Y 64byte
#define OBJSIZE256_8x8			(OBJ_CHAR_SIZE256*1)	// OBJ8x8�L�����T�C�Y
#define OBJSIZE256_16x16		(OBJ_CHAR_SIZE256*4)	// 16x16
#define OBJSIZE256_32x32		(OBJ_CHAR_SIZE256*16)	// 32x32
#define OBJSIZE256_64x64		(OBJ_CHAR_SIZE256*64)	// 64x64
#define OBJSIZE256_16x8			(OBJ_CHAR_SIZE256*2)	// 16x8
#define OBJSIZE256_32x8			(OBJ_CHAR_SIZE256*4)	// 32x8
#define OBJSIZE256_32x16		(OBJ_CHAR_SIZE256*8)	// 32x16
#define OBJSIZE256_64x32		(OBJ_CHAR_SIZE256*32)	// 64x32
#define OBJSIZE256_8x16			(OBJ_CHAR_SIZE256*2)	// 8x16
#define OBJSIZE256_8x32			(OBJ_CHAR_SIZE256*4)	// 8x32
#define OBJSIZE256_16x32		(OBJ_CHAR_SIZE256*8)	// 16x32
#define OBJSIZE256_32x64		(OBJ_CHAR_SIZE256*32)	// 32x64

//--------------------------------------------------------------
//	OBJ�L������
//--------------------------------------------------------------
#define OBJNO_8x8				(1)						// 8x8OBJ�L������1
#define	OBJNO_16x16				(4)						// 16x16
#define	OBJNO_32x32				(16)					// 32x32
#define	OBJNO_64x64				(64)					// 64x64
#define	OBJNO_16x8				(2)						// 16x8
#define	OBJNO_32x8				(4)						// 32x8
#define	OBJNO_32x16				(8)						// 32x16
#define	OBJNO_64x32				(32)					// 64x32
#define	OBJNO_8x16				(2)						// 8x16
#define	OBJNO_8x32				(4)						// 8x32
#define	OBJNO_16x32				(8)						// 16x32
#define	OBJNO_32x64				(32)					// 32x64




//-------------------------------------
/// �`����
//	�X�̃��[�N�ɐݒ肷��`��t���O
//	�f�t�H�̓����_���[�`��
enum{
	CLACT_DRAW_NONE,		// �`�悵�Ȃ�
	CLACT_DRAW_RENDERER,	// �����_���[�`��
};

//-------------------------------------
//	
//	�A�t�B���A�{�p�A�t�B���A�A�t�B���Ȃ�
//	�t���O
//	
//=====================================
enum{
	CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
	CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
	CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
};

//-------------------------------------
//	
//	�������ւ̃t���b�v
//	
//=====================================
enum{
	CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
	CLACT_FLIP_H,			// �t���b�v��������
	CLACT_FLIP_V,			// �t���b�v��������
	CLACT_FLIP_HV,			// �������t���b�v
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
typedef struct _CLACT_SET*		CLACT_SET_PTR;			// �Z���A�N�^�[�Z�b�g�|�C���^
typedef const struct _CLACT_SET* CONST_CLACT_SET_PTR;	// �R���X�g�^

typedef struct CLACT_WORK_tag*	CLACT_WORK_PTR;			// �Z���A�N�^�[�Z�b�g�|�C���^
typedef const struct CLACT_WORK_tag* CONST_CLACT_WORK_PTR;	// �Z���A�N�^�[�Z�b�g�|�C���^



//-------------------------------------
//
//	�Z���A�N�^�[�Z�b�g�쐬�֐�
//						�����\����
//
//=====================================
typedef struct{
	int		WorkNum;		// �Z���A�N�^�[����\���̔z��

	// OAM�}�l�[�W���|�C���^
//	NNSG2dOamManagerInstance* pMainMan;
//	NNSG2dOamManagerInstance* pSubMan;

	// �����_���[�|�C���^
	// �����_���[�`����s���Ƃ��́A
	// �쐬���Ă���o�^���Ă��������B
	NNSG2dRendererInstance*		pRender;			// �`��p Renderer
	
	int	heap;				// �g�p����q�[�v
}CLACT_SETDATA;

//-------------------------------------
///	�w�b�_�[�f�[�^	
typedef struct _CLACT_HEADER{
	const NNSG2dImageProxy*				pImageProxy;	// �L�����N�^/�e�N�X�`���v���L�V
	const NNSG2dCharacterData*			pCharData;		// �L�����N�^�f�[�^		�iVram�]�����̂ݕK�v�j
	const NNSG2dImagePaletteProxy*		pPaletteProxy;	// �p���b�g�v���L�V
	NNSG2dCellDataBank*					pCellBank;		// �Z���f�[�^
    const NNSG2dCellAnimBankData*       pAnimBank;		// �Z���A�j���[�V����		�i�����Ƃ�NULL�j
	const NNSG2dMultiCellDataBank*      pMCBank;		// �}���`�Z���f�[�^			�i�����Ƃ�NULL�j
    const NNSG2dMultiCellAnimBankData*  pMCABank;		// �}���`�Z���A�j���[�V����	�i�����Ƃ�NULL�j
	
	int  flag;				//�]���A�j���m�F�p�̃t���O
	u8	 priority;			// BG�ʂƂ̗D��x

}CLACT_HEADER;

typedef struct _CLACT_HEADER*	CLACT_HEADER_PTR;		// �Z���A�N�^�[�w�b�_�[�|�C���^

//-------------------------------------
//
//	�Z���A�N�^�[�o�^�\����
//
//=====================================
typedef struct{
	CLACT_SET_PTR	ClActSet;	// �Z���A�N�^�[�Z�b�g
	const CLACT_HEADER*	ClActHeader;// �w�b�_�[�f�[�^
	VecFx32				mat;		// ���W		
	VecFx32				sca;		// �g��l
	u16					rot;		// ��]		(0�`65535)
	u32					pri;		// �D�揇��
	int					DrawArea;	// �`���
		// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
		// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB

	int					heap;		// �g�p����q�[�v
}CLACT_ADD;

//-------------------------------------
//
//	�Z���A�N�^�[�V���v���o�^�\����
//
//=====================================
typedef struct{
	CLACT_SET_PTR	ClActSet;	// �Z���A�N�^�[�Z�b�g
	const CLACT_HEADER*	ClActHeader;// �w�b�_�[�f�[�^
	VecFx32				mat;		// ���W
	u32					pri;		// �D�揇��
	int					DrawArea;	// �`���
		// main�ɓo�^�FNNS_G2D_VRAM_TYPE_2DMAIN
		// sub�ɓo�^ �FNNS_G2D_VRAM_TYPE_2DSUB
	

	int					heap;		// �g�p����q�[�v
}CLACT_ADD_SIMPLE;

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//=============================================================================
//
//		�A�N�^�[�Z�b�g����֐�
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̏�����
 *
 *@param	pSetData		�Z���A�N�^�[�Z�b�g�쐬�f�[�^
 *
 *@retval	CLACT_SET_PTR			�쐬�����Z���A�N�^�[�Z�b�g�̃|�C���^
 *@retval	NULL					���s
 *
 * �Z���A�N�^�[�Z�b�g���쐬
 *
 */
 //----------------------------------------------------------------------------
GLOBAL CLACT_SET_PTR CLACT_InitSet( const CLACT_SETDATA* pSetData );

//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̔j��
 *
 *@param	ClActSet			�j������Z���A�N�^�[�Z�b�g�|�C���^
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSet��NULL)
 *
 * �Z���A�N�^�[�Z�b�g��j������
 *		���s���Ă����A�N�^�[�I�u�W�F����ĉ��
 *
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DestSet( CLACT_SET_PTR ClActSet );

//-----------------------------------------------------------------------------
/**
 *@brief			�Z���A�N�^�[�Z�b�g�̕`��t���O��ݒ�
 *
 *@param	ClActSet			�j������Z���A�N�^�[�Z�b�g�|�C���^
 *@param	flag				0:��`��	1:�`��
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSet��NULL)
 *
 *	�o�^����Ă���Z���S�Ă�`��/��`�悷�邩��ݒ�
 *
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DrawFlagSet( CLACT_SET_PTR ClActSet, u8 flag );

//-----------------------------------------------------------------------------
/**
 *@brief				�`�悷��
 *
 *@param	pClAct		�Z���A�N�^�[�Z�b�g
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_Draw( CONST_CLACT_SET_PTR pClAct );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o�^����Ă��郌���_���[���擾
 *
 *@param	pClAct			�Z���A�N�^�[
 *
 *@retval	NNSG2dRendererInstance*		OAM�}�l�[�W��
 *@retval	NULL						�ݒ肳��Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dRendererInstance* CLACT_RenderGet( CONST_CLACT_SET_PTR pClAct);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���[��ݒ�
 *
 *@param	pClAct		�Z���A�N�^�[
 *@param	pRender		�����_���[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_RenderSet( CLACT_SET_PTR pClAct, NNSG2dRendererInstance* pRender);


//-----------------------------------------------------------------------------
/**
 *@brief			�S�A�N�^�[�j��
 *
 *@param	ClActSet		�Z���A�N�^�[�Z�b�g�C���f�b�N�X
 *
 *@retval	TRUE	����
 *@retval	FALSE	���s	(ClActSetIdx��NULL)
 */
 //----------------------------------------------------------------------------
GLOBAL BOOL CLACT_DelAllSet( CLACT_SET_PTR ClActSet );


//=============================================================================
//
//		�Z���A�N�^�[���[�N����֐�
//
//=============================================================================
//-----------------------------------------------------------------------------
/**
 *@brief		�Z���A�N�^�[�f�[�^������
 *						
 *
 *@param	pWork		����������(0 Clear)�f�[�^
 *
 *@return	none
 *
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_WorkClear( CLACT_WORK_PTR pWork );

//-----------------------------------------------------------------------------
/**
 *@brief		�Z���A�N�^�[���[�N�̎擾
 *						
 *
 *@param	ClActSetIdx		�Z���A�N�^�[�Z�b�g�C���f�b�N�X
 *@param	ClActIdx		�Z���A�N�^�[���[�N�C���f�b�N�X
 *
 *@retval	CLACT_WORK_PTR	����
 *@retval	NULL			���s
 *
 */
//----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR CLACT_GetWork(CONST_CLACT_SET_PTR ClActSet, s16 ClActIdx);

//-----------------------------------------------------------------------------
/**
 *@brief			�ǉ�����
 *
 *@param	add		�o�^�f�[�^
 *
 *@retval	CLACT_WORK_PTR		�o�^�����A�N�^�[�|�C���^
 *@retval	NULL				���s
 */
// ----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR CLACT_Add(const CLACT_ADD* add);

//-----------------------------------------------------------------------------
/**
 *@brief			�V���v���ǉ�����
 *
 *@param	add		�o�^�f�[�^
 *
 *@retval	CLACT_WORK_PTR		�o�^�����A�N�^�[�|�C���^
 *@retval	NULL				���s
 */
// ----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR CLACT_AddSimple(const CLACT_ADD_SIMPLE* add);

//-----------------------------------------------------------------------------
/**
 *@brief			�폜����
 *
 *@param	del		�폜����A�N�^�[���[�N
 *
 *@return	none
 * 
 */
// ----------------------------------------------------------------------------
GLOBAL void CLACT_Delete(CLACT_WORK_PTR del);

//----------------------------------------------------------------------------
/**
 *
 *@brief	���W��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Matrix		���W
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���ϊ����W��ݒ�
 *
 *	@param	act			�A�N�^�[
 *	@param	Matrix		�A�t�B���ϊ��𔽉f������I�t�Z�b�g���W
 *
 *	@return	none
 *
 * �A�N�^�[�ɐݒ肳��Ă�����W + �A�t�B���ϊ����W
 * �̈ʒu�ŉ�]�g��k�����s���܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetAffineMatrix(CLACT_WORK_PTR act, const VecFx32* Matrix);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	Scale	�g��l
 *
 *@return	none
 *
 * �ݒ肵�Ă��A�t�B���t���O��
 *	CLACT_AFFINE_NORMAL��CLACT_AFFINE_DOUBLE�łȂ��Ɣ��f����܂���B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetScale(CLACT_WORK_PTR act, const VecFx32* Scale);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l��ݒ肵�A�A�t�B���t���O��ݒ肷��
 *
 *@param	act		�A�N�^�[
 *@param	Scale	�g��l
 *@param	affine	�A�t�B���t���O
 *
 *@return	none
 *
 *affine�t���O
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetScaleAffine(CLACT_WORK_PTR act, const VecFx32* Scale, int affine);

//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Rotation	��]�p		(0�`65535)
 *
 *@return	none
 *
 * �ݒ肵�Ă��A�t�B���t���O��
 *	CLACT_AFFINE_NORMAL��CLACT_AFFINE_DOUBLE�łȂ��Ɣ��f����܂���B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetRotation(CLACT_WORK_PTR act, u16 Rotation);

//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p��ݒ肵�ăA�t�B���t���O��ݒ�
 *
 *@param	act			�A�N�^�[
 *@param	Rotation	��]�p		(0�`65535)
 *@param	affine		�A�t�B���t���O
 *
 *@return	none
 *
 *affine�t���O
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetRotationAffine(CLACT_WORK_PTR act, u16 Rotation, int affine);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	flag	�`��t���O	0:��`��	1:�����_���[�`��
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetDrawFlag(CLACT_WORK_PTR act, int flag);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���t���O��ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	flag	�I�[�g�A�j���t���O	0:��A�j��	1:�I�[�g�A�j��
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetAnmFlag(CLACT_WORK_PTR act, int flag);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���[�V�����t���[����ݒ�
 *
 *@param	act		�A�N�^�[
 *@param	frame	�P�V���N�ɐi�߂�t���[����
 *
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetAnmFrame(CLACT_WORK_PTR act, fx32 frame);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���ϊ��p�����[�^
 *
 *	@param	act		�A�N�^�[
 *	@param	param	�A�t�B���ϊ��p�����[�^
 *
 *	@return	none
 *
 * param
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetAffineParam( CLACT_WORK_PTR act, int param );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���b�v�̐ݒ�
 *
 *	@param	act		�A�N�^�[
 *	@param	flag	�t���b�v�t���O 
 *
 *	@return	none
 *
 * flag
 *	enum{
 * 		CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
 * 		CLACT_FLIP_H,			// �t���b�v��������
 *		CLACT_FLIP_V,			// �t���b�v��������
 *		CLACT_FLIP_HV,			// �������t���b�v
 *	};
 *
 *	"�A�t�B���ϊ��t���O��CLACT_AFFINE_NONE�ɂ��܂�"
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_SetFlip( CLACT_WORK_PTR act, int flag );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���W���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	���W
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL const VecFx32* CLACT_GetMatrix(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�A�t�B���ϊ����W���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	���W
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL const VecFx32* CLACT_GetAffineMatrix(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�g��l���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	VecFx32	�g��l
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL const VecFx32* CLACT_GetScale(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	��]�p�x���擾
 *
 *@param	act		�A�N�^�[
 *
 *@return	u16		��]�p�x	(0�`65535)
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u16 CLACT_GetRotation(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��t���O���擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	int		0:��`��	1:�`��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_GetDrawFlag(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���t���O���擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	int		0:��A�j��	1:�I�[�g�A�j���[�V����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_GetAnmFlag(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�I�[�g�A�j���[�V�����t���[�����擾
 *
 *@param	act	�A�N�^�[
 *
 *@return	fx32		�P�V���N�ɐi�߂�t���[����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL fx32 CLACT_GetAnmFrame(CONST_CLACT_WORK_PTR act);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�t�B���p�����[�^	�擾
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	int		�A�t�B���p�����[�^
 *
 * ret
 *	enum{
 *		CLACT_AFFINE_NONE,		// �A�t�B���ϊ��Ȃ�
 *		CLACT_AFFINE_NORMAL,	// �A�t�B���ϊ�
 *		CLACT_AFFINE_DOUBLE,	// �{�p�A�t�B���ϊ�
 *	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_GetAffineParam( CONST_CLACT_WORK_PTR act );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�t���b�v�ݒ���擾
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	int		�t���b�v�ݒ�
 *
 * ret
 *	enum{
 * 		CLACT_FLIP_NONE,		// �t���b�v�Ȃ�
 * 		CLACT_FLIP_H,			// �t���b�v��������
 *		CLACT_FLIP_V,			// �t���b�v��������
 *		CLACT_FLIP_HV,			// �������t���b�v
 *	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_GetFlip( CONST_CLACT_WORK_PTR act );

//-----------------------------------------------------------------------------
/*
 * ���������ɃA�j���[�V�����V�[�P���X��ύX���܂��B
 * 
 *@brief	�A�j���[�V�����̃V�[�P���X���`�F���W����
 *
 *@param	actCell�F�Z���A�N�^�[
 *@param	num�F�V�[�P���X�i���o�[
 *
 *@return	none
 *
 *	�����V�[�P���X�i���o�[�ł��V�[�P���X�ύX���s���t���[���O����A�j����
 *	�͂��߂܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_AnmChg( CLACT_WORK_PTR actCell, u32 num );

//-----------------------------------------------------------------------------
/*
 * ���A�j���[�V�����V�[�P���X���������ύX���܂��B
 * 
 *@brief	�A�j���[�V�����̃V�[�P���X���`�F���W����
 *
 *@param	actCell�F�Z���A�N�^�[
 *@param	num�F�V�[�P���X�i���o�[
 *
 *@return	none
 *
 * �A�j���[�V�����V�[�P���X�������Ƃ��͉����s���܂���B
 *
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_AnmChgCheck( CLACT_WORK_PTR actCell, u32 num );

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V�������X�^�[�g
 *
 *	@param	actCell		�Z���A�N�^�|
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_AnmReStart( CLACT_WORK_PTR actCell );

//----------------------------------------------------------------------------
/**
 *
 *@brief	���݂̃A�j���[�V�����V�[�P���X���擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return			�A�j���[�V�����V�[�P���X�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_AnmGet( CONST_CLACT_WORK_PTR actCell );

//-----------------------------------------------------------------------------
/**	
 *@brief	�A�j���[�V����������
 *
 *@param	actCell�F����\����
 *@param	num�F�t���[����i�߂�l
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_AnmFrameChg( CLACT_WORK_PTR actCell, fx32 num );

//-----------------------------------------------------------------------------
/**	
 *@brief	�A�j���[�V�����t���[�����Z�b�g
 *
 *@param	actCell�F����\����
 *@param	num�F�Z�b�g����A�j���[�V���� ���ޯ���l
 *				���̒l��NitroCharacter�ɐݒ肳��Ă���CellAnm��No�̍��ڂ̐���������܂��B
 *
 *@return	none
 */
//----------------------------------------------------------------------------
GLOBAL void CLACT_AnmFrameSet( CLACT_WORK_PTR actCell, u16 num );

//-----------------------------------------------------------------------------
/**	
 *@brief				�A�j���[�V�����t���[�����擾
 *
 *@param	actCell�F����\����
 *
 *@return	�����ޯ���l
 *				���̒l��NitroCharacter�ɐݒ肳��Ă���CellAnm��No�̍��ڂ̐���������܂��B
 */
//----------------------------------------------------------------------------
GLOBAL u16 CLACT_AnmFrameGet( CONST_CLACT_WORK_PTR actCell);


//-----------------------------------------------------------------------------
/**
 *@brief	BG�ʂƂ̗D��x��ύX����
 *
 *@param	actCell�F����\����
 *@param	Priority�F�D��x
 *
 *@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_BGPriorityChg( CLACT_WORK_PTR actCell, u8 Priority );

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG�ʂƂ̕`��D��x���擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u8			�D��x
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u8 CLACT_BGPriorityGet( CONST_CLACT_WORK_PTR actCell);

//-----------------------------------------------------------------------------
/**
 * ��OAM�����̃p���b�g�i���o�[������悤�ɂȂ�܂��B
 *
 *@brief				�p���b�g�i���o�[��ύX
 *
 *@param	actCell			����\����
 *@param	pltt_num		�ύX����p���b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_PaletteNoChg( CLACT_WORK_PTR actCell, u32 pltt_num );

//-----------------------------------------------------------------------------
/**
 * ��CLACT_PaletteNoChg�̌��ʂɃp���b�g�]���擪�i���o�[�����Z���܂��B
 *
 *@brief				�p���b�g�i���o�[��ύX
 *
 *@param	actCell			����\����
 *@param	pltt_num		�ύX����p���b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_PaletteNoChgAddTransPlttNo( CLACT_WORK_PTR actCell, u32 pltt_num );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�i���o�[�擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32		���̃p���b�g�i���o�[
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_PaletteNoGet( CONST_CLACT_WORK_PTR actCell );

//-----------------------------------------------------------------------------
/**
 * ��OAM�A�g���r���[�g�ɐݒ肳��Ă���p���b�g�i���o�[�ɉ��Z����܂��B
 *	 �����AOAM�A�g���r���[�g�̃J���[�p���b�gNo���Q�ŃI�t�Z�b�g�ɂQ��
 *	 �ݒ肷��ƁA�S�̃J���[�p���b�g���Q�Ƃ���悤�ɂȂ�܂�
 * 
 *@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *@param	actCell		����\����
 *@param	pltt_num	�p���b�g�I�t�Z�b�g�i���o�[
 * 
 *@return	none
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_PaletteOffsetChg( CLACT_WORK_PTR actCell, u32 pltt_num );

//----------------------------------------------------------------------------
/**
 * ��CLACT_PaletteOffsetChg�֐��̌��ʂɃp���b�g�̓]����擪�p���b�g�i���o�[�����Z���܂��B
 *
 *@brief	�p���b�g�I�t�Z�b�g��ݒ�
 *
 *	@param	act		�A�N�^�[
 *
 *	@return	�p���b�g�i���o�[
 *
 *
 * ���p���b�g�i���o�[�ݒ�ƃp���b�g�I�t�Z�b�g�ݒ�͓������܂���B
 *�@�@���p���b�g�i���o�[��ݒ肷��ƃI�t�Z�b�g�̒l�͔��f����Ȃ��Ȃ�܂��B
 *	�@���I�t�Z�b�g�l��ݒ肵���Ƃ��̓p���b�g�i���o�[�����f����Ȃ��Ȃ�܂��B
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_PaletteOffsetChgAddTransPlttNo( CLACT_WORK_PTR act, u32 pltt_num );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�p���b�g�I�t�Z�b�g�l�擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32		���̃p���b�g�I�t�Z�b�g�l
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_PaletteOffsetGet( CONST_CLACT_WORK_PTR actCell );

//-----------------------------------------------------------------------------
/**
 *@brief	�`��D�揇�ʂ�ݒ�
 *
 *@param	actCell		����\����
 *@param	Priority	�D�揇��
 *				
 * 
 *@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void CLACT_DrawPriorityChg( CLACT_WORK_PTR actCell, u32 Priority );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�`��D�揇�ʂ��擾
 *
 *@param	actCell		�A�N�^�[
 *
 *@return	u32			�`��D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 CLACT_DrawPriorityGet( CONST_CLACT_WORK_PTR actCell );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�v���N�V�f�[�^��ݒ�
 *
 *	@param	act			�A�N�^�[
 *	@param	pImageProxy	�ݒ肷��C���[�W�v���N�V
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_ImageProxySet( CLACT_WORK_PTR act, const NNSG2dImageProxy* pImageProxy );

//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�v���N�V�f�[�^���擾
 *
 *	@param	act			�A�N�^�[
 *
 *	@return	�A�N�^�[���������Ă���C���[�W�v���N�V
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy * CLACT_ImageProxyGet( CLACT_WORK_PTR act );


//--------------------------------------------------------------
/**
 * @brief	�v���N�V�f�[�^��ݒ�
 *
 * @param	act	
 * @param	PaletteProxy	
 *
 * @retval	GLOBAL void	
 *
 */
//--------------------------------------------------------------
GLOBAL void CLACT_PaletteProxySet( CLACT_WORK_PTR act, const NNSG2dImagePaletteProxy*  PaletteProxy);

//--------------------------------------------------------------
/**
 * @brief	�v���N�V�f�[�^���擾
 *
 * @param	act	
 *
 * @retval	�A�N�^�[���������Ă�v���N�V
 *
 */
//--------------------------------------------------------------
GLOBAL NNSG2dImagePaletteProxy * CLACT_PaletteProxyGet( CLACT_WORK_PTR act );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ�
 *
 *	@param	act		�A�N�^�[���[�N
 *	@param	flag	�t���O	TRUE�����U�C�NON	FALSE�����U�C�NOFF
 *
 *	@return	none
 *
 * ���U�C�NOFF�̎��ł��A�j�g���L�����N�^�Ń��U�C�NON�ɂ���OAM��
 * ���U�C�N���������ĕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_MosaicSet( CLACT_WORK_PTR act, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���U�C�N�ݒ��Ԃ��擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	TRUE	���U�C�N��ON
 *	@retval	FALSE	���U�C�N��OFF	�i�j�g���L�����N�^�Őݒ肵�Ă�Ƃ��͔��f�����j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_MosaicGet( CONST_CLACT_WORK_PTR act );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VRAM�^�C�v���擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	VRAM�^�C�v
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNS_G2D_VRAM_TYPE CLACT_VramTypeGet( CONST_CLACT_WORK_PTR act );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�^�[���A�j���[�V���������`�F�b�N
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	TRUE	�A�j���[�V������
 *	@retval	FALSE	�X�g�b�v
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_AnmActiveCheck( CLACT_WORK_PTR act );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���[�h��ݒ�
 *
 *	@param	act			�A�N�^�[���[�N
 *	@param	objmode		�I�u�W�F���[�h 
 *
 *	@return	none
 *
 *	�I�u�W�F���[�h��GX_OAM_MODE_NORMAL�ɂ����NitroCharacter�Őݒ肵��
 *	�I�u�W�F���[�h�ŕ`�悳��܂��B
 *	
	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
	GX_OAM_MODE_XLU			������OBJ 
	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_ObjModeSet( CLACT_WORK_PTR act, GXOamMode objmode );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�I�u�W�F���[�h���擾
 *
 *	@param	act		�A�N�^�[���[�N
 *
 *	@retval	GX_OAM_MODE_NORMAL		�m�[�}��OBJ 
 *	@retval	GX_OAM_MODE_XLU			������OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJ�E�B���h�E 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	�r�b�g�}�b�vOBJ 
 *
 *	�I�u�W�F���[�h��GX_OAM_MODE_NORMAL�̎���NitroCharacter�Őݒ肵��
 *	�I�u�W�F���[�h�ŕ`�悳��܂��B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXOamMode CLACT_ObjModeGet( CONST_CLACT_WORK_PTR act );


//----------------------------------------------------------------------------
/**
 *	@brief	OAM���W�X�^�N���A�@���C��
 *
 *	@param	heap �q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_UtilOamRamClear_Main( int heap );

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���W�X�^�N���A�@�T�u
 *
 *	@param	heap �q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_UtilOamRamClear_Sub( int heap );


#undef	GLOBAL
#endif

