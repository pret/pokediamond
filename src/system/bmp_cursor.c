//============================================================================================
/**
 * @file	bmp_cursor.c
 * @brief	BitmapWindowにメニュー選択用のカーソルを描画する
 * @author	taya
 * @date	2006.01.12
 */
//============================================================================================
#include "common.h"
#include "system\arc_util.h"
#include "gflib\heapsys.h"
#include "gflib\bg_system.h"
#include "gflib\strbuf_family.h"
#include "system\fontproc.h"

#include "system\bmp_cursor.h"





enum {
	CURSOR_BMP_SIZE = 0x20 * 4,

	DEFAULT_LETTER_COLOR = 0x01,
	DEFAULT_SHADOW_COLOR = 0x02,
	DEFAULT_GROUND_COLOR = 0x0F,
};

struct _BMPCURSOR {
	GF_PRINTCOLOR  color;
	STRBUF*        strbuf;
};



BMPCURSOR* BMPCURSOR_Create( u32 heapID )
{
	static const STRCODE str[] = {
		cursor_, EOM_, 
	};

	BMPCURSOR*  bmpCursor = sys_AllocMemory( heapID, sizeof(BMPCURSOR) );
	if( bmpCursor )
	{
		bmpCursor->color = GF_PRINTCOLOR_MAKE(DEFAULT_LETTER_COLOR, DEFAULT_SHADOW_COLOR, DEFAULT_GROUND_COLOR);
		bmpCursor->strbuf = STRBUF_Create( 4, heapID );
		STRBUF_SetStringCode( bmpCursor->strbuf, str );
	}
	return bmpCursor;
}

void BMPCURSOR_Delete( BMPCURSOR* bmpCursor )
{
	GF_ASSERT(bmpCursor!=NULL);
	if(bmpCursor)
	{
		if( bmpCursor->strbuf )
		{
			STRBUF_Delete( bmpCursor->strbuf );
		}
		sys_FreeMemoryEz( bmpCursor );
	}
}

void BMPCURSOR_ChangeColor( BMPCURSOR* bmpCursor, GF_PRINTCOLOR color )
{
	GF_ASSERT(bmpCursor!=NULL);
	if(bmpCursor)
	{
		bmpCursor->color = color;
	}
}



void BMPCURSOR_Print( const BMPCURSOR* bmpCursor, GF_BGL_BMPWIN* win, u32 x, u32 y )
{
	GF_STR_PrintColor( win, FONT_SYSTEM, bmpCursor->strbuf, x, y, MSG_NO_PUT, bmpCursor->color, NULL );
	GF_BGL_BmpWinCgxOn( win );
}

