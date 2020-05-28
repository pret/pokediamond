//============================================================================================
/**
 * @file	numfont.c
 * @brief	�����t�H���g��舵��
 * @author	taya
 * @date	2005.09.30
 */
//============================================================================================
#include  "common.h"

#include  "gflib\msg_print.h"
#include  "gflib\bg_system.h"
#include  "system\arc_util.h"
#include  "system\font_arc.h"

#include  "system\numfont.h"

// �t�H���g�̃r�b�g��p�^�[��
enum {
	BIT_BACK = 0,
	BIT_LETTER = 1,
	BIT_SHADOW = 2,

	BIT_BB = (BIT_BACK << 4) | BIT_BACK,
	BIT_BL = (BIT_BACK << 4) | BIT_LETTER,
	BIT_BS = (BIT_BACK << 4) | BIT_SHADOW,
	BIT_LB = (BIT_LETTER << 4) | BIT_BACK,
	BIT_LL = (BIT_LETTER << 4) | BIT_LETTER,
	BIT_LS = (BIT_LETTER << 4) | BIT_SHADOW,
	BIT_SB = (BIT_SHADOW << 4) | BIT_BACK,
	BIT_SL = (BIT_SHADOW << 4) | BIT_LETTER,
	BIT_SS = (BIT_SHADOW << 4) | BIT_SHADOW,
};

// ���̂��萔
enum {
	CHAR_MARK_START = 10 * 0x20,
	STRBUF_SIZE = 16,		// 16������Ώ[��
};

//--------------------------------------------------------------
/**
 *	�L���L�����f�[�^�̃p�����[�^
 */
//--------------------------------------------------------------
static const struct {
	u16 offset;		///< �擪����̃I�t�Z�b�g
	u16 width;		///< �`�敝�i�h�b�g�j
}MarkCharParam[] = {
	{  CHAR_MARK_START+0x00,	NUMFONT_NUM_WIDTH },
	{  CHAR_MARK_START+0x20,	NUMFONT_MARK_WIDTH },
	{  CHAR_MARK_START+0x60,	NUMFONT_MARK_WIDTH },
	{  CHAR_MARK_START+0xa0,	NUMFONT_MARK_WIDTH },
	{  CHAR_MARK_START+0xe0,	NUMFONT_MARK_WIDTH },
	{  CHAR_MARK_START+0x120,	NUMFONT_MARK_WIDTH },
	{  CHAR_MARK_START+0x160,	NUMFONT_MARK_WIDTH },
};

//--------------------------------------------------------------
/**
 *	�V�X�e�����[�N��`
 */
//--------------------------------------------------------------
struct _NUMFONT {
	void*					databuf;
	NNSG2dCharacterData*	charData;
	STRCODE					strbuf[STRBUF_SIZE];
	u32						colBack;
};


//------------------------------------------------------------------
/**
 * �����t�H���g�쐬
 *
 * @param   colLetter	�����F�ԍ�
 * @param   colShadow	�e�F�ԍ�
 * @param   colBack		�w�i�F�ԍ�
 * @param   heapID		�q�[�v�h�c
 *
 * @retval  NUMFONT*	�����t�H���g���̂ւ̃|�C���^�i���e�͔���J�j
 */
//------------------------------------------------------------------
NUMFONT*  NUMFONT_Create( u32 colLetter, u32 colShadow, u32 colBack, u32 heapID )
{
	NUMFONT* numfont = sys_AllocMemory( heapID, sizeof(NUMFONT) );
	if( numfont )
	{
		u32 i;
		u8* bit;

		numfont->databuf = ArcUtil_CharDataGet( ARC_FONT, NARC_font_num_lz_dat, TRUE, &numfont->charData, heapID );
		bit = numfont->charData->pRawData;
		for( i = 0; i < numfont->charData->szByte; i++)
		{
			switch( bit[i] ){
			case BIT_BB: bit[i] = (colBack << 4) | (colBack); break;
			case BIT_BL: bit[i] = (colBack << 4) | (colLetter); break;
			case BIT_BS: bit[i] = (colBack << 4) | (colShadow); break;
			case BIT_LB: bit[i] = (colLetter << 4) | (colBack); break;
			case BIT_LL: bit[i] = (colLetter << 4) | (colLetter); break;
			case BIT_LS: bit[i] = (colLetter << 4) | (colShadow); break;
			case BIT_SB: bit[i] = (colShadow << 4) | (colBack); break;
			case BIT_SL: bit[i] = (colShadow << 4) | (colLetter); break;
			case BIT_SS: bit[i] = (colShadow << 4) | (colShadow); break;
			}
		}
		numfont->colBack = colBack;
	}
	return numfont;
}
//------------------------------------------------------------------
/**
 * �����t�H���g�}�l�[�W���j��
 *
 * @param   numfont		�����t�H���g�|�C���^
 *
 */
//------------------------------------------------------------------
void NUMFONT_Delete( NUMFONT* numfont )
{
	if( numfont )
	{
		if( numfont->databuf )
		{
			sys_FreeMemoryEz( numfont->databuf );
		}
		sys_FreeMemoryEz( numfont );
	}
}
//------------------------------------------------------------------
/**
 * �L���`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L���^�C�v
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j

 *
 */
//------------------------------------------------------------------
void NUMFONT_WriteMark( NUMFONT* numfont, NUMFONT_MARK mark, GF_BGL_BMPWIN* win, u32 x, u32 y )
{
	GF_BGL_BmpWinPrint( win, (u8*)(numfont->charData->pRawData) + MarkCharParam[mark].offset,
		0, 0, MarkCharParam[mark].width, NUMFONT_HEIGHT, x, y, MarkCharParam[mark].width, NUMFONT_HEIGHT );
/*
	GF_BGL_BmpWinPrint( win, (u8*)(numfont->charData->pRawData) + MarkCharParam[mark].offset,
		0, 0, MarkCharParam[mark].width, NUMFONT_HEIGHT, x, y, NUMFONT_MARK_WIDTH, NUMFONT_HEIGHT );
*/
}
//------------------------------------------------------------------
/**
 * ���l�`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		�`�����
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
void NUMFONT_WriteNumber( NUMFONT* numfont, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y )
{
	int i;

	PM_NumMsgSet( numfont->strbuf, num, mode, keta );
	for(i = 0; numfont->strbuf[i] != EOM_; i++)
	{
		if( numfont->strbuf[i] >= n0_ && numfont->strbuf[i] <= n9_ )
		{
			GF_BGL_BmpWinPrint( win, (u8*)(numfont->charData->pRawData) + ((numfont->strbuf[i]-n0_) * 0x20 ),
					0, 0, NUMFONT_NUM_WIDTH, NUMFONT_HEIGHT, x, y, NUMFONT_NUM_WIDTH, NUMFONT_HEIGHT );
		}
		else
		{
			GF_BGL_BmpWinFill( win, numfont->colBack, x, y, NUMFONT_NUM_WIDTH, NUMFONT_HEIGHT );
		}
		x += NUMFONT_NUM_WIDTH;
	}
}

//------------------------------------------------------------------
/**
 * �L���Ɛ������Z�b�g�ŕ`��
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L�����
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		���l�`�����
 * @param   win			�`���E�B���h�E
 * @param   x			�`���w���W�i�h�b�g�j
 * @param   y			�`���x���W�i�h�b�g�j
 *
 */
//------------------------------------------------------------------
void NUMFONT_WriteSet( NUMFONT* numfont, NUMFONT_MARK mark, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y )
{
	NUMFONT_WriteMark( numfont, mark, win, x, y );
	NUMFONT_WriteNumber( numfont, num, keta, mode, win, x+NUMFONT_MARK_WIDTH, y );
}


//------------------------------------------------------------------
/**
 * ���l�`��(�w��o�b�t�@�ɑ΂��ăL�����N�^�f�[�^�̂ݏ�������)
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   num			���l
 * @param   keta		�ő包��
 * @param   mode		�`�����
 * @param   buf			�`���o�b�t�@
 *
 */
//------------------------------------------------------------------
void NUMFONT_WriteNumberCGXOnly( NUMFONT* numfont, s32 num, u32 keta, 
	NUMFONT_DRAW_MODE mode, void *buf)
{
	int i;
	u8 fill_code;
	u8 *write_buf;
	
	write_buf = buf;
	fill_code = numfont->colBack | (numfont->colBack<<4);
	PM_NumMsgSet( numfont->strbuf, num, mode, keta );
	for(i = 0; numfont->strbuf[i] != EOM_; i++)
	{
		if( numfont->strbuf[i] >= n0_ && numfont->strbuf[i] <= n9_ )
		{
			MI_CpuCopy32((u8*)(numfont->charData->pRawData) + ((numfont->strbuf[i]-n0_) * 0x20 ),
				&write_buf[i * 0x20], 0x20);
		}
		else
		{
			MI_CpuFill8(&write_buf[i * 0x20], fill_code, 0x20);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �L���`��(�w��o�b�t�@�ɑ΂��ăL�����N�^�f�[�^�̂ݏ�������)
 *
 * @param   numfont		�����t�H���g�|�C���^
 * @param   mark		�L���^�C�v
 * @param   buf			�W�J�o�b�t�@��ւ̃|�C���^
 *
 * @retval  
 *
 * buf�� �u(NUMFONT_MARK_WIDTH / 8) * (NUMFONT_HEIGHT / 8) * 32�v �̃T�C�Y���K�v�ł��B
 */
//--------------------------------------------------------------
void NUMFONT_WriteMarkCGXOnly( NUMFONT* numfont, NUMFONT_MARK mark, void *buf)
{
	MI_CpuCopy32((u8*)(numfont->charData->pRawData) + MarkCharParam[mark].offset,
		buf, (MarkCharParam[mark].width / 8) * 0x20);
}

