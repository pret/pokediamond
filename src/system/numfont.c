//============================================================================================
/**
 * @file	numfont.c
 * @brief	数字フォント取り扱い
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

// フォントのビット列パターン
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

// そのた定数
enum {
	CHAR_MARK_START = 10 * 0x20,
	STRBUF_SIZE = 16,		// 16桁あれば充分
};

//--------------------------------------------------------------
/**
 *	記号キャラデータのパラメータ
 */
//--------------------------------------------------------------
static const struct {
	u16 offset;		///< 先頭からのオフセット
	u16 width;		///< 描画幅（ドット）
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
 *	システムワーク定義
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
 * 数字フォント作成
 *
 * @param   colLetter	文字色番号
 * @param   colShadow	影色番号
 * @param   colBack		背景色番号
 * @param   heapID		ヒープＩＤ
 *
 * @retval  NUMFONT*	数字フォント実体へのポインタ（内容は非公開）
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
 * 数字フォントマネージャ破棄
 *
 * @param   numfont		数字フォントポインタ
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
 * 記号描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号タイプ
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）

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
 * 数値描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		描画方式
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）
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
 * 記号と数字をセットで描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号種類
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		数値描画方式
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）
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
 * 数値描画(指定バッファに対してキャラクタデータのみ書き込み)
 *
 * @param   numfont		数字フォントポインタ
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		描画方式
 * @param   buf			描画先バッファ
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
 * @brief   記号描画(指定バッファに対してキャラクタデータのみ書き込み)
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号タイプ
 * @param   buf			展開バッファ先へのポインタ
 *
 * @retval  
 *
 * bufは 「(NUMFONT_MARK_WIDTH / 8) * (NUMFONT_HEIGHT / 8) * 32」 のサイズが必要です。
 */
//--------------------------------------------------------------
void NUMFONT_WriteMarkCGXOnly( NUMFONT* numfont, NUMFONT_MARK mark, void *buf)
{
	MI_CpuCopy32((u8*)(numfont->charData->pRawData) + MarkCharParam[mark].offset,
		buf, (MarkCharParam[mark].width / 8) * 0x20);
}

