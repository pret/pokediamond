//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel_draw.h
 *@brief	�^�b�`�p�l������\������
 *@author	tomoya takahashi
 *@data		2005.03.29
 *
 *	gflib/touchpanel_system����ڐA
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#ifndef __TOUCHPANEL_DRAW_H__
#define	__TOUCHPANEL_DRAW_H__

#undef	GLOBAL
#ifdef	__TOUCHPANEL_DRAW_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define		TP_WIN_CGX		( 1024 )		// �E�B���h�E�ݒ�̒l

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
/// �u���V�f�[�^�\����
typedef struct
{
	u16* pCharData;			// �u���V�f�[�^			
				
	u16 SizeX;				// �T�C�YX
	u16 SizeY;				// �T�C�YY
} TP_BRUSH_DATA;


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
/// �^�b�`�y������n���ĕ`�悷��V�X�e��
GLOBAL void DrawTPInit( GF_BGL_INI* bgl, int gf_bgl_frame, u32 width, u32 height, u32 x, u32 y, const u16* p_pltt, int heap );	// �`��ݒ�֐�
GLOBAL void DrawTPDelete(GF_BGL_INI* bgl, u16 pltt );							// �`��V�X�e���j���֐�
GLOBAL void DrawTPChgPltt( int gf_bgl_frame, const u16* p_pltt );									// �p���b�g��ς���
GLOBAL void DrawTP(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num );	// �T�C�Y��TP�f�[�^��`�悷��
GLOBAL void DrawTPInOut(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
						 u16 check_num, TP_PICTURE_DATA* pData );						// ���O���������`��
GLOBAL u32 DrawTPSync(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num, u16 sync, u32* p_count );
GLOBAL void DrawTPLine(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data, u16 check_num );			// ����`��
GLOBAL void DrawTPLineInOut(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
							 u16 check_num, TP_PICTURE_DATA* pData );					// ���O���������`��
GLOBAL void DrawTPPoint(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data );						// �_��`��
GLOBAL void DrawTPClean(GF_BGL_INI* bgl, u16 pltt_num );						// �N���A
GLOBAL void DrawTPPaste( GF_BGL_INI* bgl );								// ���ۂɉ�ʂɕ`��(��̊֐����g�p�����Ղ�
																// �s���K�v������)
GLOBAL void DrawTPOldMatDest( void );							// �ۑ����Ă���P�O�̍��p��j������
																// �V��������`���Ƃ��Ɏg�p����
GLOBAL void MakeTPBrush( TP_BRUSH_DATA* p_brush, u16 pltt, u16 size_x, u16 size_y, int heap );			// �u���V�f�[�^���쐬
GLOBAL void MakeTPGraphicBrush( TP_BRUSH_DATA* p_brush, const u16* p_char, u16 size_x, u16 size_y, int heap );	// �G�̃u���V�f�[�^���쐬
GLOBAL void DestTPBrush( TP_BRUSH_DATA* p_brush );		// �u���V�f�[�^��j��


//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

