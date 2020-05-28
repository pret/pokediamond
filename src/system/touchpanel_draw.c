//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel_draw.c
 *@brief	�^�b�`�p�l�����̕`��
 *@author	tomoya takahashi
 *@data		2005.03.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#define __TOUCHPANEL_DRAW_H_GLOBAL
#include "touchpanel_draw.h"

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
//-------------------------------------
// �^�b�`�p�l�����`��p
static void drawPoint(GF_BGL_INI* bgl, u16 x, u16 y, TP_BRUSH_DATA brush_data );					// �_�̕`��
static void drawLine(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2, TP_BRUSH_DATA brush_data );	// ���C��������
static void drawLineInOut(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2,
		TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
		TP_PICTURE_DATA* pData );	// ���C����̓��O������s�����C��������
static u32 getOffset( u16 x, u16 y, u16* p_shift, u32 char_width );				// �L�����N�^�f�[�^�I�t�Z�b�g�����߂�	

// �f�o�b�N�p�x�N�g���f�[�^�`��
static void drawVect(GF_BGL_INI* bgl, Vec2DS32* p_point1, Vec2DS32* p_point2 );

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN*	TouchPanelDrawDataIdx;	// �o���v�f�[�^�̃C���f�b�N�X
static TPData	TouchPanelOld;			// ��O�̕`����
static u8		TouchPanelDrawInit=0;	// �`��V�X�e���������������̃t���O


//
/// �^�b�`�y�����̕`��p�֐�
//
//----------------------------------------------------------------------------
/**
 *
 * @brief	�^�b�`�y���̕`����ƃr�b�g�}�b�v�̍쐬
 *
 * @param	gf_bgl_frame�Fbg_system�̕`��BG�̃i���o�[
 * @param	width �F�`�敝
 * @param	height�F�`�捂��
 * @param	x	  �F�`��J�n�_��
 * @param	y	  �F�`��J�n�_����
 * @param	p_pltt�F�g�p����p���b�g�f�[�^
 * @param	heap	�g�p����q�[�v
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPInit(GF_BGL_INI* bgl, int gf_bgl_frame, u32 width, u32 height, u32 x, u32 y, const u16* p_pltt, int heap)
{
	//
	// �^�b�`�y���`��p�̃r�b�g�}�b�v���쐬���ăp���b�g�����[�h����
	//
	// Control���쐬
	GF_BGL_BGCNT_HEADER		bg =		// BG�̐ݒ�
	{
		0,0,
//		GF_BGL_SCRSIZ_256_256,			// �`��͈͕�(32*32��)
		0x800,			// �`��͈͕�(32*32��)
		0,
		GX_BG_SCRSIZE_TEXT_256x256,
		GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x0000,
		GX_BG_CHARBASE_0x04000,
		GX_BG_EXTPLTT_01,
		0,
		0,
		0,
		FALSE
	};

	
	// ������
	TouchPanelDrawInit = 1;
	
	//
	// �R�����[���Z�b�g���Z�b�g���L�����N�^���쐬
	//
	GF_BGL_BGControlSet(bgl, gf_bgl_frame, &bg, GF_BGL_MODE_TEXT );
	
	TouchPanelDrawDataIdx = GF_BGL_BmpWinAllocGet(heap, 1);
	GF_BGL_BmpWinAdd(bgl, TouchPanelDrawDataIdx,
			gf_bgl_frame, x, y,
			width, height, 0, TP_WIN_CGX - (width * height) );
	
	// �p���b�g���[�h
	DrawTPChgPltt( gf_bgl_frame, p_pltt );

	// �e��f�[�^�Z�b�g
	TouchPanelOld.touch = 0;


	
	// ��ʂ��N���A
	DrawTPClean(bgl, 0 );
	GF_BGL_BmpWinOn(TouchPanelDrawDataIdx );					// �`��
}

//----------------------------------------------------------------------------
/**
 *
 * @brief	�p���b�g��ς���
 * 
 * @param	gf_bgl_frame�Fbg_system�̕`��BG�̃i���o�[
 * @param	p_pltt�F�g�p����p���b�g�f�[�^
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPChgPltt( int gf_bgl_frame, const u16* p_pltt )
{
	// �p���b�g���[�h
	if( gf_bgl_frame < GF_BGL_FRAME0_S ){
		GX_LoadBGPltt( (const void *)p_pltt, 0, sizeof(u16)*16 );
	}
	else{
		GXS_LoadBGPltt( (const void *)p_pltt, 0, sizeof(u16)*16 );
	}
}

//----------------------------------------------------------------------------
/**
 *
 * @brief	�^�b�`�p�l���`��V�X�e���̔j��
 * 
 * @param	pltt�F�p���b�g�i���o�[
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPDelete(GF_BGL_INI* bgl, u16 pltt )
{
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );

	DrawTPClean(bgl, pltt );
	DrawTPPaste(bgl);
	GF_BGL_BmpWinDel( TouchPanelDrawDataIdx );
	sys_FreeMemoryEz(TouchPanelDrawDataIdx);
	
	// ������
	TouchPanelDrawInit = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���ۂɉ�ʂɕ`��
 *
 *@param	none
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPPaste( GF_BGL_INI* bgl )
{
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );
	
	//
	// ���ۂɉ�ʂɕ`�悷��
	//
	GF_BGL_BmpWinCgxOn(TouchPanelDrawDataIdx );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l������`��
 *
 *@param	pBuff�F�^�b�`�p�l�����o�b�t�@
 *@param	size�F�o�b�t�@�T�C�Y
 *@param	brush_data�F�g�p����u���V�f�[�^
 *@param	check_num�F�^�b�`�p�l����񂪂���ȏ㗣��Ă�����V��������`���l
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTP(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num )
{
	int i;			// ���[�v�p
	
	for( i = 0; i < size; i++ )
	{
		DrawTPLine(bgl, pBuff[ i ], brush_data, check_num );		// ��������
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���O��������ă^�b�`�p�l������`��
 *
 *@param	pBuff�F�^�b�`�p�l�����o�b�t�@
 *@param	size�F�o�b�t�@�T�C�Y
 *@param	in_brush_data�F�̈���̂Ƃ��g�p����u���V�f�[�^
 *@param	out_brush_data�F�̈�O�̂Ƃ��g�p����u���V�f�[�^
 *@param	check_num�F�^�b�`�p�l����񂪂���ȏ㗣��Ă�����V��������`���l
 *@param	pData�F�G�̃f�[�^
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPInOut(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
						 u16 check_num, TP_PICTURE_DATA* pData )
{
	int i;			// ���[�v�p

	
	for( i = 0; i < size; i++ )
	{
		DrawTPLineInOut(bgl, pBuff[ i ], in_brush_data, out_brush_data, check_num, pData );		// ��������
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l������`��
 *@brief	sync�̒l���`�悵�čs���܂�
 *
 *@param	pBuff�F�^�b�`�p�l�����o�b�t�@
 *@param	size�F�o�b�t�@�T�C�Y
 *@param	brush_data�F�g�p����u���V�f�[�^
 *@param	check_num�F�^�b�`�p�l����񂪂���ȏ㗣��Ă�����V��������`���l
 *@param	sync�F�I�[�g�T���v�����O�̂P�t���[���ɃT���v�����O����l
 *@param	p_count�F�g�p����J�E���^(�O���[�o��)
 * 
 *@retval	�O�F���s�@
 *@retval	�P�F�I��
 *
 */
//-----------------------------------------------------------------------------
u32 DrawTPSync(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num, u16 sync, u32* p_count )
{
	int i;			// ���[�v�p
	int num;		// �I���̐�
	u32 ret = 0;	// �߂�l

	// ���[�v�̏I���̐����Z�b�g
	num = *p_count + sync;
	if( num > size ){
		num = size;
		ret = 1;
	}
	
	for( i = *p_count; i < num; i++ ){
		DrawTPLine(bgl, pBuff[ i ], brush_data, check_num );		// ��������
	}

	*p_count = i;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l������`��i�_��`��j
 *
 *@param	Buff�F�^�b�`�p�l�����o�b�t�@
 *@param	brush_data�F�g�p����u���V�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPPoint(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data )
{	
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );
	
	//
	// init�Ŏ擾�����o���v�f�[�^�̃L�����N�^�f�[�^�ɓ_������
	//
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		drawPoint(bgl, Buff.x, Buff.y, brush_data );		// �_������
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l������`��i���ɂ���j
 *
 *@param	Buff�F�^�b�`�p�l�����o�b�t�@
 *@param	brush_data�F�g�p����u���V�f�[�^
 *@param	check_num�F�V���������n�߂�Ƃ��̂P�O�Ƃ̍ő卷
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPLine(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data, u16 check_num )
{	
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );
	
	// ��O���^�b�`�������Ȃ���ΐV���������n�߂�
	if( TouchPanelOld.touch == TP_TOUCH_OFF ){
		TouchPanelOld = Buff;
	}else{
		// ���܂�ɂ��P�O�̒l�Ƃ̍�������Ƃ��͐V���������n�߂�
		if( (((TouchPanelOld.x - Buff.x) > check_num) ||
			((TouchPanelOld.y - Buff.y) > check_num)) ||
			(((TouchPanelOld.x - Buff.x) < -check_num) ||
			((TouchPanelOld.y - Buff.y) < -check_num)))
		{
			TouchPanelOld = Buff;
		}
	}
	
	// �^�b�`���Ă�����`��
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		//
		// init�Ŏ擾�����o���v�f�[�^�̃L�����N�^�f�[�^�ɓ_������
		//
		drawLine(bgl, TouchPanelOld.x, TouchPanelOld.y, Buff.x, Buff.y, brush_data );		// �_������

		// �f�[�^���Z�b�g
		TouchPanelOld = Buff;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�^�b�`�p�l������`��i���ɂ���j���O������s���ĕ`��
 *
 *@param	Buff�F�^�b�`�p�l�����o�b�t�@
 *@param	in_brush_data�F�̈���̂Ƃ��g�p����u���V�f�[�^
 *@param	out_brush_data�F�̈�O�̂Ƃ��g�p����u���V�f�[�^
 *@param	check_num�F�^�b�`�p�l����񂪂���ȏ㗣��Ă�����V��������`���l
 *@param	pData�F�G�̃f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPLineInOut(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
					  u16 check_num, TP_PICTURE_DATA* pData )
{	
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );
	
	// ��O���^�b�`�������Ȃ���ΐV���������n�߂�
	if( TouchPanelOld.touch == TP_TOUCH_OFF ){
		TouchPanelOld = Buff;
	}else{
		// ���܂�ɂ��P�O�̒l�Ƃ̍�������Ƃ��͐V���������n�߂�
		if( (((TouchPanelOld.x - Buff.x) > check_num) ||
			((TouchPanelOld.y - Buff.y) > check_num)) ||
			(((TouchPanelOld.x - Buff.x) < -check_num) ||
			((TouchPanelOld.y - Buff.y) < -check_num)))
		{
			TouchPanelOld = Buff;
		}
	}
	
	// �^�b�`���Ă�����`��
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		//
		// init�Ŏ擾�����o���v�f�[�^�̃L�����N�^�f�[�^�ɓ_������
		//
		drawLineInOut(bgl, TouchPanelOld.x, TouchPanelOld.y, Buff.x, Buff.y, in_brush_data, out_brush_data, pData );		// �_������

		// �f�[�^���Z�b�g
		TouchPanelOld = Buff;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�o���v���N���[������
 *
 *@param	pltt_num�F�h��Ԃ��p���b�g�i���o�[
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPClean(GF_BGL_INI* bgl, u16 pltt_num )
{
	// ����������Ă��邩�`�F�b�N
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem����������Ă��܂���\n" );

	//
	// �p���b�g�i���o�[�̐F�ŃN���[������
	//
	GF_BGL_BmpWinDataFill(TouchPanelDrawDataIdx, pltt_num );			// �h��Ԃ�
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�ۑ����Ă���P�O�̍��W������������
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPOldMatDest( void )
{
	// ������
	TouchPanelOld.touch = TP_TOUCH_OFF;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�u���V�f�[�^���쐬����
 *
 *@param	p_brush�F�u���V�f�[�^
 *@param	pltt�F�p���b�g�i���o�[
 *@param	size_x�F���T�C�Y
 *@param	size_y�F���ăT�C�Y
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MakeTPBrush( TP_BRUSH_DATA* p_brush, u16 pltt, u16 size_x, u16 size_y, int heap )
{
	int i, j;
	int make_size;		// �L�����N�^�f�[�^�̃T�C�Y
	u16 shift;			// �V�t�g����l
	u32 offset;			// �I�t�Z�b�g�l

	
	//
	// �u���V�f�[�^���쐬����
	// �L�����N�^�͐�΂ɂW�̔{���ɂ���
	// �������������������Ȃ��Ƃ��͂O������
	//
	// �L�����N�^�f�[�^�T�C�Y�����߂�
	p_brush->SizeX = size_x;
	p_brush->SizeY = size_y;
	if( (p_brush->SizeX % 8) != 0 ){
		p_brush->SizeX += (8 - (size_x % 8));
	}
	if( (p_brush->SizeY % 8) != 0 ){
		p_brush->SizeY += (8 - (size_y % 8));
	}

	
	p_brush->pCharData = (u16*)sys_AllocMemory( heap, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

	// 0�ŏ�����
	for( i = 0; i < (p_brush->SizeX / 4) * p_brush->SizeY; i++ ){
		p_brush->pCharData[ i ] = 0;
	}


	// �L�����N�^�����p���b�g�̐F�œh��Ԃ�
	for( i = 0; i < size_y; i++ ){
		for( j = 0; j < size_x; j++ ){
			// ���W�ʒu�̃I�t�Z�b�g�����߂�
			offset = getOffset( j, i, &shift, p_brush->SizeX / 8 );

			// �I�t�Z�b�g�̈ʒu�Ɋi�[
			*(p_brush->pCharData + offset) |= pltt << shift;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�G�̃u���V�f�[�^���쐬����
 *@brief	�T�C�Y�͕K���L�����N�^�P�ʁi�W�j�ł��肢���܂�
 *
 *@param	p_brush�F�u���V�f�[�^
 *@param	p_char�F�G�̃L�����N�^�f�[�^
 *@param	size_x�F���T�C�Y
 *@param	size_y�F���ăT�C�Y
 *@param	heap	�g�p����q�[�v
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MakeTPGraphicBrush( TP_BRUSH_DATA* p_brush, const u16* p_char, u16 size_x, u16 size_y, int heap )
{
	int i, j;
	int make_size;		// �L�����N�^�f�[�^�̃T�C�Y
	u16 shift;			// �V�t�g����l
	u32 offset;			// �I�t�Z�b�g�l

	
	//
	// �u���V�f�[�^���쐬����
	// �L�����N�^�͐�΂ɂW�̔{���ɂ���
	// �������������������Ȃ��Ƃ��͂O������
	//
	// �L�����N�^�f�[�^�T�C�Y�����߂�
	p_brush->SizeX = size_x;
	p_brush->SizeY = size_y;

	
	p_brush->pCharData = (u16*)sys_AllocMemory( heap, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

	// �R�s�[
	MI_CpuCopy16( p_char, p_brush->pCharData, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�u���V�f�[�^��j������
 *
 *@param	p_brush�F�u���V�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DestTPBrush( TP_BRUSH_DATA* p_brush )
{
	//
	// �u���V�f�[�^�j��
	//
	sys_FreeMemoryEz( p_brush->pCharData );
	p_brush->pCharData = NULL;
}
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	����`�悷��
 *
 *@param	x1�F�`��J�n�����W
 *@param	y1�F�`��J�n�����W
 *@param	x2�F�`��I�������W
 *@param	y2�F�`��I�������W
 *@param	brush_data�F�u���V�f�[�^
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void drawLine(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2, TP_BRUSH_DATA brush_data )
{
	u16 width, height;			// ���C���̕��ƍ���
	int i;						// ���[�v�p
	u16 min;					// ���W�̍Œ�̒l�i�P�Â�����ق��j
	u16 max;					// ���W�̍ő�̒l�i�P�Â�����ق��j
	u16 base;					// �x�[�X�̒l�imin�̍��W�̎��̒l�j
	u16 px, py;					// �s�N�Z���ʒu
	s32 vec_heigt;				// �����̌X��
	
	
	// �����ƕ����擾
	width = (u16) ((x1 >= x2) ? (x1 - x2) : (x2 - x1));  // �����擾
    height = (u16) ((y1 >= y2) ? (y1 - y2) : (y2 - y1)); // �������擾

	
	// �傫���ق����P�h�b�g�Â�������W�ɂ���
	if( width > height ){
		if( x1 >= x2 ){
			min = x2;
			max = x1;
			base = y2;
	
			// �X�������߂�
			vec_heigt = ((y2 - y1) * 10000) / (x2 - x1);
		}else{
			min = x1;
			max = x2;
			base = y1;

			// �X�������߂�
			vec_heigt = ((y1 - y2) * 10000) / (x1 - x2);
		} 

		// ���ɉ����ē_��`��
		for( i = min; i < max; i++ ){
			px = i;
			py = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			drawPoint(bgl, px, py, brush_data );
		}
	}else{
		if( y1 >= y2 ){
			min = y2;
			max = y1;
			base = x2;
	
			// �X�������߂�
			vec_heigt = ((x2 - x1) * 10000) / (y2 - y1);
		}else{
			min = y1;
			max = y2;
			base = x1;

			// �X�������߂�
			vec_heigt = ((x1 - x2) * 10000) / (y1 - y2);
		} 

		// ���ɉ����ē_��`��
		for( i = min; i < max; i++ ){
			px = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			py = i;
			drawPoint( bgl, px, py, brush_data );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���O���肵�Ȃ������`�悷��
 *
 *@param	u16 x1�F�`��J�n�����W
 *@param	u16 y1�F�`��J�n�����W
 *@param	u16 x2�F�`��I�������W
 *@param	u16 y2�F�`��I�������W
 *@param	TP_BRUSH_DATA in_brush_data�F�̈���u���V�f�[�^
 *@param	TP_BRUSH_DATA out_brush_data�F�̈�O�u���V�f�[�^
 *@param	TP_PICTURE_DATA* pData�F�G�̃f�[�^
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
static void drawLineInOut(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2,
		TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
		TP_PICTURE_DATA* pData )
{
	u16 width, height;			// ���C���̕��ƍ���
	int i;						// ���[�v�p
	u16 min;					// ���W�̍Œ�̒l�i�P�Â�����ق��j
	u16 max;					// ���W�̍ő�̒l�i�P�Â�����ق��j
	u16 base;					// �x�[�X�̒l�imin�̍��W�̎��̒l�j
	u16 px, py;					// �s�N�Z���ʒu
	s32 vec_heigt;				// �����̌X��
	
	
	// �����ƕ����擾
	width = (u16) ((x1 >= x2) ? (x1 - x2) : (x2 - x1));  // �����擾
    height = (u16) ((y1 >= y2) ? (y1 - y2) : (y2 - y1)); // �������擾

	
	// �傫���ق����P�h�b�g�Â�������W�ɂ���
	if( width > height ){
		if( x1 >= x2 ){
			min = x2;
			max = x1;
			base = y2;
	
			// �X�������߂�
			vec_heigt = ((y2 - y1) * 10000) / (x2 - x1);
		}else{
			min = x1;
			max = x2;
			base = y1;

			// �X�������߂�
			vec_heigt = ((y1 - y2) * 10000) / (x1 - x2);
		} 

		// ���ɉ����ē_��`��
		for( i = min; i < max; i++ ){
			px = i;
			py = (u16) (base + ((vec_heigt * (i - min)) / 10000));

			// ���O����
			if( CheckTPPictureInOut( pData, px, py ) == 1 ){
				drawPoint(bgl, px, py, in_brush_data );
			}else{	
				drawPoint(bgl, px, py, out_brush_data );
			}
		}
	}else{
		if( y1 >= y2 ){
			min = y2;
			max = y1;
			base = x2;
	
			// �X�������߂�
			vec_heigt = ((x2 - x1) * 10000) / (y2 - y1);
		}else{
			min = y1;
			max = y2;
			base = x1;

			// �X�������߂�
			vec_heigt = ((x1 - x2) * 10000) / (y1 - y2);
		} 

		// ���ɉ����ē_��`��
		for( i = min; i < max; i++ ){
			px = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			py = i;
			
			// ���O����
			if( CheckTPPictureInOut( pData, px, py ) == 1 ){
				drawPoint(bgl, px, py, in_brush_data );
			}else{	
				drawPoint(bgl, px, py, out_brush_data );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�_��`�悷��
 *
 *@param	u16 x�F�`�悘���W
 *@param	u16 y�F�`�悙���W
 *@param	TP_BRUSH_DATA brush_data�F�u���V�f�[�^
 *
 *@return
 *
 */
//-----------------------------------------------------------------------------
static void drawPoint(GF_BGL_INI* bgl, u16 x, u16 y, TP_BRUSH_DATA brush_data )
{
	s32		draw_start_x = 0;		// ��ʊO�ɊG����яo���Ƃ��ɂǂ�����`������邩
	s32		draw_start_y = 0;		// ��ʊO�ɊG����яo���Ƃ��ɂǂ�����`������邩
	int		i;						// ���[�v�p
	u32		offset;					// �I�t�Z�b�g
	u16		shift;					// �V�t�g

	
	// �I�[�o�[����l���v�Z
	// 0�ȉ��`�F�b�N
	if( x - (brush_data.SizeX / 2) < 0 ){
		draw_start_x = -(x - (brush_data.SizeX / 2));

	}
	if( y - (brush_data.SizeY / 2) < 0 ){
		draw_start_y = -(y - (brush_data.SizeY / 2));
	}

	

	// �`��
	// ���ɂ���Ă���Ƃ��͂P�i����������
	if( draw_start_x == 0 ){
		GF_BGL_BmpWinPrint( 
				TouchPanelDrawDataIdx,
				brush_data.pCharData,
				draw_start_x,
				draw_start_y,
				brush_data.SizeX - draw_start_x,
				brush_data.SizeY - draw_start_y,
				x - (brush_data.SizeX / 2) + draw_start_x,
				y - (brush_data.SizeY / 2) + draw_start_y,
				brush_data.SizeX - draw_start_x,
				brush_data.SizeY - draw_start_y );
	}else{
		// �P�i���`��
		for( i = draw_start_y; i < brush_data.SizeY; i++ ){
			// �����̃I�t�Z�b�g�����߂�
			offset = getOffset( 0, i, &shift, brush_data.SizeX / 8 );
			
			GF_BGL_BmpWinPrint( 
					TouchPanelDrawDataIdx,
					(brush_data.pCharData + offset),
					draw_start_x,
					0,
					brush_data.SizeX - draw_start_x,
					1,
					x - (brush_data.SizeX / 2) + draw_start_x,
					y - (brush_data.SizeY / 2) + i,
					brush_data.SizeX - draw_start_x,
					1 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�L�����N�^�f�[�^�I�t�Z�b�g�����߂�
 *
 *@param	u16 x,y�F���W�l
 *@param	u16* p_shift�F�V�t�g����l�i�[�p
 *@param	u32 char_width�F�W���W�̐�
 *
 *@return	u32	�^�F�I�t�Z�b�g�l(u16*�^�p)
 *
 */
//-----------------------------------------------------------------------------
static u32 getOffset( u16 x, u16 y, u16* p_shift, u32 char_width )
{
	u32	offset;			// �I�t�Z�b�g�l
	u16 char_off_y;		// �P�L�����N�^�f�[�^���̃I�t�Z�b�g
	u16 char_off_x;		// �P�L�����N�^�f�[�^���̃I�t�Z�b�g

	
	//
	// ���W�l����u16�^(�Q�o�C�g)�p�̃I�t�Z�b�g�����߂�
	//
	// �L�����N�^�P�ʂ̔z��̑傫�������߂�	
	// ���̈ʒu�̃L�����N�^�I�t�Z�b�g�����߂�
	offset = ((y / 8) * char_width) + (x / 8);

	// �W��\������̂ɕK�v��U16�̐���������
	offset *= 16;

	// �L�����N�^���̃I�t�Z�b�g�����߂�
	char_off_y = y % 8;
	char_off_x = x % 8;
	char_off_y *= 2;				// 2���L�����N�^�f�[�^�̉��͂W�@�W���i�[����ɂ�u16��2�K�v
	char_off_y += char_off_x / 4;	// 4��u16�ɂ͂S�s�N�Z�����̐F�����邩��S�ȏ�̂Ƃ��͂P���炵���ʒu���I�t�Z�b�g�ɂ���
	char_off_x %= 4;				// ��char_off_y�łS�ȏ�̂Ƃ��̃I�t�Z�b�g�����炵���̂łS�̂��܂�̒l�ɂ���(�V�t�g����l)
	char_off_x *= 4;				// ����ŃV�t�g����l

	// �V�t�g����l�i�[
	*p_shift = char_off_x;	

	return offset + char_off_y;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	�x�N�g���f�[�^��`�悷��
 *				(�f�o�b�N�p�@�@���O����p�f�[�^��`�悷�邽�߂ɍ쐬���܂���)
 *
 *@param	Vec2DS32* p_point1�F���_�ƃx�N�g���f�[�^
 *@param	Vec2DS32* p_point2�F���_�ƃx�N�g���f�[�^
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
static void drawVect(GF_BGL_INI* bgl, Vec2DS32* p_point1, Vec2DS32* p_point2 )
{	
	TP_BRUSH_DATA brush;
	
	MakeTPBrush( &brush, 3, 4, 4 );
	
	//
	// �x�N�g���f�[�^��`�悷��
	//
	drawLine( bgl, p_point1->x, p_point1->y, p_point2->x, p_point2->y, brush );

	DestTPBrush( &brush );
}
#endif
