//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		swsprite.h
 *	@brief		�X�v���C�g�\���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2005.09.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __SWSPRITE_H__
#define __SWSPRITE_H__


#include <nnsys.h>

#undef GLOBAL
#ifdef	__SWSPRITE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
// UV�l�ݒ�擾�t���O
enum{
	SWSP_UVUL,		// ����
	SWSP_UVLR,		// �E��
};

// HV�t���b�v�ݒ�擾�t���O
enum{
	SWSP_FLIPH,		// H�t���b�v
	SWSP_FLIPV,		// V�t���b�v
};

// ��]�p�̐ݒ�擾�t���O
enum{
	SWSP_ROT_X,		// X����]�p�x
	SWSP_ROT_Y,		// Y����]�p�x
	SWSP_ROT_Z		// X����]�p�x
};


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	imageClip�p
//	�\�t�g�E�F�A�X�v���C�g�`��V�X�e��
//	�f�[�^�i�[�\����
//=====================================
typedef struct SWSP_SYS_tag*	SWSP_SYS_PTR;

//-------------------------------------
//	
//	�L�����N�^�f�[�^
//
//=====================================
typedef struct SWSP_CHAR_tag*	SWSP_CHAR_PTR;

//-------------------------------------
//	
//	�p���b�g�f�[�^
//	
//=====================================
typedef struct SWSP_PLTT_tag*	SWSP_PLTT_PTR;

//-------------------------------------
//	
//	�\�t�g�E�F�A�X�v���C�g�\���f�[�^
//	���P�ɂ܂Ƃ߂��I�u�W�F�N�g�f�[�^
//	
//=====================================
typedef struct SWSP_OBJ_tag*	SWSP_OBJ_PTR;



//-------------------------------------
//	
//	�V�X�e���o�^�f�[�^
//	
//=====================================
typedef struct {
	int obj_num;		// �\���I�u�W�F�N�g�o�^��
	int char_num;		// �L�����N�^�f�[�^�o�^��
	int pltt_num;		// �p���b�g�f�[�^�o�^��
	int heap;			// �g�p�q�[�v
} SWSP_SYSDATA;

//-------------------------------------
//	
//	�L�����N�^�o�^�f�[�^
//	
//=====================================
typedef struct {
	SWSP_SYS_PTR		s_sys;		// �\�t�g�E�F�A�X�v���C�g�V�X�e��
	NNSG2dCharacterData*	res_file;	// �L�����N�^���\�[�X
} SWSP_CHARDATA;

//-------------------------------------
//	
//	�p���b�g�o�^�f�[�^
//	
//=====================================
typedef struct {
	SWSP_SYS_PTR	s_sys;		// �\�t�g�E�F�A�X�v���C�g�V�X�e��
	NNSG2dPaletteData*	res_file;	// �p���b�g���\�[�X
	u32		load_num;				// �]���p���b�g��
} SWSP_PLTTDATA;

//-------------------------------------
//	
//	�\�t�g�E�F�A�X�v���C�g
//	�\���I�u�W�F�o�^�f�[�^
//	
//=====================================
typedef struct {
	SWSP_SYS_PTR	s_sys;	// �\�t�g�E�F�A�X�v���C�g�V�X�e��
	SWSP_CHAR_PTR	p_char;	// �g�p�L�����N�^
	SWSP_PLTT_PTR	p_pltt;	// �g�p�p���b�g
	s16					m_x;	// ���W��
	s16					m_y;	// ���W��
	u16					rota;	// ��]
	fx32				alpha;	// �����l
	int					pri;	// �\���D�揇��
	u16					pltt_offs;	// �p���b�g�I�t�Z�b�g
} SWSP_ADDDATA;




//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	imageClip�`��p�\�t�g�E�F�A�V�X�e��������
 *
 *	@param	data		�V�X�e���������f�[�^
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	SWSPRITE_PTR	�\�t�g�E�F�A�V�X�e���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_SYS_PTR SWSP_SysInit( const SWSP_SYSDATA* data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�V�X�e���j��
 *
 *	@param	data	�\�t�g�E�F�A�V�X�e���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SysDelete( SWSP_SYS_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�\������
 *
 *	@param		data �V�X�e�����̕\���I�u�W�F�N�g��\������
 *
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SysDraw( SWSP_SYS_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�̍\���̃T�C�Y��Ԃ�
 *
 *	@param	none
 *
 *	@return	int	�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int SWSP_GetCharDataSize( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�\���̂̃T�C�Y��Ԃ�
 *
 *	@param	none
 *
 *	@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int SWSP_GetPlttDataSize( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�f�[�^�\���̂̃T�C�Y���擾����
 *
 *	@param	none
 *
 *	@return	int		�T�C�Y
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int SWSP_GetSpriteDataSize( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_CHAR_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_CHAR_PTR SWSP_GetCharDataNo( SWSP_CHAR_PTR obj, int no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_PLTT_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_PLTT_PTR SWSP_GetPlttDataNo( SWSP_PLTT_PTR obj, int no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z��ŃI�u�W�F�N�g���i�[����̈��p�ӂ����Ƃ��̗v�f���̃f�[�^�擾�p�֐�
 *
 *	@param	obj		�I�u�W�F�N�g�|�C���^���i�[���Ă���z��
 *	@param	no		�擾����v�f��
 *
 *	@return	SWSP_OBJ_PTR	�v�f�̃f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_OBJ_PTR SWSP_GetSpriteDataNo( SWSP_OBJ_PTR obj, int no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�L�����N�^�f�[�^��ǂݍ���
 *
 *	@param	data	�ǂݍ��ރL�����N�^�f�[�^ 
 *
 *	@return	SWSP_CHAR_PTR	�ǂݍ��񂾃L�����N�^�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_CHAR_PTR SWSP_CharLoad( const SWSP_CHARDATA* data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�j��
 *
 *	@param	data	�L�����N�^�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_CharDelete( SWSP_CHAR_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�L�����N�^�f�[�^�S�j��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_CharDeleteAll( SWSP_SYS_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�p���b�g�f�[�^��ǂݍ���
 *
 *	@param	data	�ǂݍ��ރp���b�g�f�[�^ 
 *
 *	@return	SWSP_PLTT_PTR	�ǂݍ��񂾃p���b�g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_PLTT_PTR SWSP_PlttLoad( const SWSP_PLTTDATA* data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�p�p���b�g�f�[�^�j��
 *
 *	@param	data	�j������p���b�g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_PlttDelete( SWSP_PLTT_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�f�[�^�S�j��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_PlttDeleteAll( SWSP_SYS_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���o�^
 *
 *	@param	add		�o�^�f�[�^
 *
 *	@return	SWSP_OBJ_PTR	�\�t�g�E�F�A�X�v���C�g�I�u�W�F
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL SWSP_OBJ_PTR SWSP_Add( const SWSP_ADDDATA* add );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���f�[�^�j��
 *
 *	@param	sp_obj �j������\�t�g�E�F�A�X�v���C�g�I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_Delete( SWSP_OBJ_PTR sp_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\�t�g�E�F�A�X�v���C�g�\���f�[�^�S�j��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_DeleteAll( SWSP_SYS_PTR data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\��/��\���ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F�N�g
 *	@param	draw	�\��/�\��		(TRUE / FALSE)
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteDraw( SWSP_OBJ_PTR obj, BOOL draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\��/��\�����擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F�N�g
 *
 *	@retval	TRUE	�\��
 *	@retval	FALSE	��\��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL SWSP_GetSpriteDraw( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���W�ݒ�
 *
 *	@param	obj		�I�u�W�F	
 *	@param	x		���W��
 *	@param	y		���W��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpritePos( SWSP_OBJ_PTR obj, s16 x, s16 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���W���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2 ���W(�����o s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dSVec2 SWSP_GetSpritePos( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���S���W�ݒ�	(������W����̍��W)
 *
 *	@param	obj		�I�u�W�F	
 *	@param	x		���W��
 *	@param	y		���W��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteCenterPos( SWSP_OBJ_PTR obj, s16 x, s16 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g���S���W���擾 (������W����̍��W)
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2 ���W(�����o s16 x  s16 y)
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dSVec2 SWSP_GetSpriteCenterPos( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g��k���l��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		���g�k�l
 *	@param	y		���g�k�l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteScale( SWSP_OBJ_PTR obj, fx32 x, fx32 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�g��k���l���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�����W�擾��
 *	@param	y		�����W�擾��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_GetSpriteScale( SWSP_OBJ_PTR obj, fx32* x, fx32* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�T�C�Y��
 *	@param	y		�T�C�Y��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteSize( SWSP_OBJ_PTR obj, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�T�C�Y���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dSVec2	�X�v���C�g�T�C�Y�i�����o s16 x s16 y�j
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dSVec2 SWSP_GetSpriteSize( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�\���D�揇�ʂ�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	priority	�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpritePriority( SWSP_OBJ_PTR obj, int priority );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̕\���D�揇�ʂ�ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	int		�\���D�揇��
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int SWSP_GetSpritePriority( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃��l��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	alpha	���l
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteAlpha( SWSP_OBJ_PTR obj, u8 alpha );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃��l���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u8 SWSP_GetSpriteAlpha( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̐F��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	color		�f�B�t���[�Y�J���[
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteDiffColor( SWSP_OBJ_PTR obj, GXRgb color );

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̃f�B�t���[�Y�F���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *
 *	@retval	�J���[
 */
//-----------------------------------------------------------------------------
GLOBAL GXRgb SWSP_GetSpriteDiffColor( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃e�N�X�`���A�g���r���[�g��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	tex_attr	�e�N�X�`���A�g���r���[�g�|�C���^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteTexAttr( SWSP_OBJ_PTR obj, NNSG2dImageAttr* tex_attr );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃e�N�X�`���A�g���r���[�g���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	NNSG2dImageAttr*	�e�N�X�`���A�g���r���[�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageAttr* SWSP_GetSpriteTexAttr( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���A�h���X�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	tex_addr	�e�N�X�`���A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteTexAddr( SWSP_OBJ_PTR obj, u32 tex_addr );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�N�X�`���A�h���X���擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�e�N�X�`���A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 SWSP_GetSpriteTexAddr( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃p���b�g�A�h���X�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	pltt_addr	�p���b�g�A�h���X
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpritePlttAddr( SWSP_OBJ_PTR obj, u32 pltt_addr );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̃p���b�g�A�h���X�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�p���b�g�A�h���X
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 SWSP_GetSpritePlttAddr( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	pltt_offs	�p���b�g�I�t�Z�b�g
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpritePlttOffs( SWSP_OBJ_PTR obj, u32 pltt_offs );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�p���b�g�I�t�Z�b�g�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	u32		�I�t�Z�b�g
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 SWSP_GetSpritePlttOffs( SWSP_OBJ_PTR obj );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�t���b�v�ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	flip_flg	�t���b�v�t���O
 *	@param	flip		�t���b�v�����邩	TRUE�@������@FALSE�@�����Ȃ�
 *
 *	@return	none
 *
	// HV�t���b�v�ݒ�擾�t���O
	enum{
		SWSP_FLIPH,		// H�t���b�v
		SWSP_FLIPV,		// V�t���b�v
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg, BOOL flip );

//----------------------------------------------------------------------------
/**
 *
 *	@brief		�X�v���C�g�̃t���b�v���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	flip_flg	HV�t���b�v�t���O
 *
 *	@return	BOOL	TRUE	�t���b�v����	FALSE
 *
	// HV�t���b�v�ݒ�擾�t���O
	enum{
		SWSP_FLIPH,		// H�t���b�v
		SWSP_FLIPV,		// V�t���b�v
	};
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL SWSP_GetSpriteFlip( SWSP_OBJ_PTR obj, int flip_flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�pz��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	rota		�ݒ肷��p�x
 *
 *	@return
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteRotZ( SWSP_OBJ_PTR obj, u16 rota );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p�xZ���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *
 *	@return	u16		��]�p�x
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u16 SWSP_GetSpriteRotZ( SWSP_OBJ_PTR obj );


#if 0

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�gcolor��ݒ�i�|���S��color�j
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	color	�|���S��color
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteColor( SWSP_OBJ_PTR obj, GXRgb color );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�gcolor�擾
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *
 *	@return	GXRgb	color�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL GXRgb SWSP_GetSpriteColor( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g��UV�l��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	LR_flg		����@�E���t���O
 *	@param	u			U�l	�i���j
 *	@param	v			V�l	�i�c�j
 *
 *	@return	none
 *
 *
	// UV�l�ݒ�擾�t���O
	enum{
		SWSP_UVUL,		// ����
		SWSP_UVLR,		// �E��
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg, fx32 u, f32 v );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g��UV�l���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	LR_flg		����A�E���t���O
 *
 *	@return	NNSG2dFVec2 UV�l	�i�����o x=u  y=v�j
 *
	// UV�l�ݒ�擾�t���O
	enum{
		SWSP_UVUL,		// ����
		SWSP_UVLR,		// �E��
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dFVec2 SWSP_GetSpriteUV( SWSP_OBJ_PTR obj, int LR_flg  );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�̒��S��ݒ�
 *
 *	@param	obj		�X�v���C�g�I�u�W�F
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteRotO( SWSP_OBJ_PTR obj, s16 x, s16 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�v���C�g�̉�]���S���W�̎擾
 *
 *	@param	SWSP_OBJ_PTR obj	�X�v���C�g�I�u�W�F�N�g
 *
 *	@return	NNSG2dSVec2		��]���S���W	
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dSVec2 SWSP_GetSpriteRotO( SWSP_OBJ_PTR obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p��ݒ�
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	XYZ_flg		��]�p���̃t���O
 *	@param	rota		�ݒ肷��p�x
 *
 *	@return
 *
	// ��]�p�̐ݒ�擾�t���O
	enum{
		SWSP_ROT_X,		// X����]�p�x
		SWSP_ROT_Y,		// Y����]�p�x
		SWSP_ROT_Z		// X����]�p�x
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void SWSP_SetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg, u16 rota );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	��]�p�x���擾
 *
 *	@param	obj			�X�v���C�g�I�u�W�F
 *	@param	XYZ_flg		�擾�����]�p���̃t���O
 *
 *	@return	u16		��]�p�x
 *
	// ��]�p�̐ݒ�擾�t���O
	enum{
		SWSP_ROT_X,		// X����]�p�x
		SWSP_ROT_Y,		// Y����]�p�x
		SWSP_ROT_Z		// X����]�p�x
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u16 SWSP_GetSpriteRot( SWSP_OBJ_PTR obj, int XYZ_flg );
#endif


#undef	GLOBAL
#endif		// __SWSPRITE_H__
