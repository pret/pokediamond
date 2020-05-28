//============================================================================================
/**
 * @file	pmsiv_edit.c
 * @bfief	簡易会話入力画面（描画下請け：編集欄）
 * @author	taya
 * @date	06.02.07
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\strbuf_family.h"
#include "system\arc_util.h"
#include "system\window.h"
#include "system\buflen.h"
#include "system\pms_word.h"
#include "system\winframe.naix"
#include "system\msgdata.h"
#include "system\bmp_cursor.h"
#include "msgdata\msg_pms_input.h"
#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pms_input_view.h"


//======================================================================
enum {
	INPUTAREA_PALTYPE_MAX = 10,

	STR_TMPBUF_LEN = 128,	// 表示前のテンポラリとして使用。最大文字数。
};

enum {
	EDITAREA_WIN_X = 3,
	EDITAREA_WIN_Y = 1,
	EDITAREA_WIN_WIDTH = 27,
	EDITAREA_WIN_HEIGHT = 4,
	EDITAREA_WIN_CHARSIZE = EDITAREA_WIN_WIDTH*EDITAREA_WIN_HEIGHT,

	MESSAGE_WIN_X = 2,
	MESSAGE_WIN_Y = 21,
	MESSAGE_WIN_WIDTH = 27,
	MESSAGE_WIN_HEIGHT = 2,
	MESSAGE_WIN_CHARSIZE = MESSAGE_WIN_WIDTH*MESSAGE_WIN_HEIGHT,

	YESNO_WIN_X = 23,
	YESNO_WIN_Y = 15,
	YESNO_WIN_WIDTH = 8,
	YESNO_WIN_HEIGHT = 4,
	YESNO_WIN_CHARSIZE = YESNO_WIN_WIDTH*YESNO_WIN_HEIGHT,

	// 単語領域位置情報（ドット単位、中心点）
	WORDAREA_SINGLE_X = (128- EDITAREA_WIN_X*8),
	WORDAREA_SINGLE_Y = 16,
	WORDAREA_DOUBLE_X1 = 48,
	WORDAREA_DOUBLE_Y1 = 16,
	WORDAREA_DOUBLE_X2 = 160,
	WORDAREA_DOUBLE_Y2 = WORDAREA_DOUBLE_Y1,

	WORDAREA_X_MARGIN = 2,	// 前後文字列との余白（ドット）


	WORDAREA_WIDTH = 96,
	WORDAREA_HEIGHT = 16,
	EDITAREA_LINE_HEIGHT = 16,


	LFFT_ARROW_OBJ_XPOS = 6,
	LFFT_ARROW_OBJ_YPOS = 24,
	RIGHT_ARROW_OBJ_XPOS = 250,
	RIGHT_ARROW_OBJ_YPOS = LFFT_ARROW_OBJ_YPOS,

	ALLCOVER_CURSOR_XPOS = 128,
	ALLCOVER_CURSOR_YPOS = 24,
};


enum {
	YESNOWIN_CURSOR_OX = 0,
	YESNOWIN_CURSOR_OY = 0,

	YESNOWIN_STR_OX = 14,
	YESNOWIN_STR_OY = 0,

	YESONOWIN_LINE_HEIGHT = 16,
};


enum {
	EDITAREA_WIN_BASE_COLOR_LETTER = 0x03,
	EDITAREA_WIN_BASE_COLOR_SHADOW = 0x04,
	EDITAREA_WIN_BASE_COLOR_GROUND = 0x0d,

	EDITAREA_WIN_WORD_COLOR_LETTER = 0x05,
	EDITAREA_WIN_WORD_COLOR_SHADOW = 0x06,
	EDITAREA_WIN_WORD_COLOR_GROUND = 0x0e,

	MESSAGE_WIN_COL_LETTER = 0x01,
	MESSAGE_WIN_COL_SHADOW = 0x02,
	MESSAGE_WIN_COL_GROUND = 0x09,

	YESNOWIN_COL_LETTER = 0x01,
	YESNOWIN_COL_SHADOW = 0x02,
	YESNOWIN_COL_GROUND = 0x09,
};

//--------------------------------------------------------------
/**
 *	文章解析ルーチンの戻り値
 */
//--------------------------------------------------------------
enum {
	PMS_ANALYZE_RESULT_STR,
	PMS_ANALYZE_RESULT_TAG,
	PMS_ANALYZE_RESULT_CR,
	PMS_ANALYZE_RESULT_END,
};

//======================================================================
typedef struct {
	s16  x;
	s16  y;
}POS;

typedef struct {
	STRBUF*	src;
	const STRCODE*	p;
	int  state;
}PMS_ANALYZE_WORK;


//======================================================================
//--------------------------------------------------------------
/**
 *	
 */
//--------------------------------------------------------------
struct _PMSIV_EDIT {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;

	GF_BGL_BMPWIN      win_edit;
	GF_BGL_BMPWIN      win_message;
	GF_BGL_BMPWIN      win_yesno;
	CLACT_WORK_PTR     cursor_actor;
	CLACT_WORK_PTR     arrow_left_actor;
	CLACT_WORK_PTR     arrow_right_actor;

	MSGDATA_MANAGER*   msgman;
	STRBUF*            tmpbuf;
	BMPCURSOR*         bmp_cursor;

	POS                word_pos[PMS_INPUT_WORD_MAX];
	u32                word_pos_max;
	u32                yesnowin_frame_charpos;

	PMS_ANALYZE_WORK   awk;

	u16   pal_data[INPUTAREA_PALTYPE_MAX][16];
};


//==============================================================
// Prototype
//==============================================================
static void setup_pal_datas( PMSIV_EDIT* wk );
static void update_editarea_palette( PMSIV_EDIT* wk );
static void setup_wordarea_pos( PMSIV_EDIT* wk );
static void setup_obj( PMSIV_EDIT* wk );
static u32 print_sentence( PMSIV_EDIT* wk );
static void setup_pms_analyze( PMS_ANALYZE_WORK* awk, PMSIV_EDIT* wk );
static void cleanup_pms_analyze( PMS_ANALYZE_WORK* awk );
static int prog_pms_analyze( PMS_ANALYZE_WORK* awk, STRBUF* buf );
static void wordpos_to_orgpos( const POS* wordpos, POS* orgpos);
static void wordpos_to_lcdpos( const POS* wordpos, POS* lcdpos );
static void fill_wordarea( GF_BGL_BMPWIN* win, const POS* wordpos );
static void print_wordarea( PMSIV_EDIT* wk, GF_BGL_BMPWIN* win, const POS* wordpos, PMS_WORD word );
static void set_cursor_anm( PMSIV_EDIT* wk, BOOL active_flag );




//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   mwk		
 * @param   dwk		
 *
 * @retval  PMSIV_EDIT*		
 */
//------------------------------------------------------------------
PMSIV_EDIT*  PMSIV_EDIT_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk )
{
	PMSIV_EDIT*  wk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMSIV_EDIT) );

	wk->vwk = vwk;
	wk->mwk = mwk;
	wk->dwk = dwk;

	wk->cursor_actor = NULL;
	wk->arrow_left_actor = NULL;
	wk->arrow_right_actor = NULL;

	wk->tmpbuf = STRBUF_Create( STR_TMPBUF_LEN, HEAPID_PMS_INPUT_VIEW );
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_pms_input_dat, HEAPID_PMS_INPUT_VIEW );
	wk->bmp_cursor = BMPCURSOR_Create( HEAPID_PMS_INPUT_VIEW );

	return wk;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_EDIT_Delete( PMSIV_EDIT* wk )
{
	if( wk->bmp_cursor )
	{
		BMPCURSOR_Delete( wk->bmp_cursor );
	}
	if( wk->cursor_actor )
	{
		CLACT_Delete( wk->cursor_actor );
	}
	if( wk->arrow_left_actor )
	{
		CLACT_Delete( wk->arrow_left_actor );
	}
	if( wk->arrow_right_actor )
	{
		CLACT_Delete( wk->arrow_right_actor );
	}
	if( wk->msgman )
	{
		MSGMAN_Delete( wk->msgman );
	}
	if( wk->tmpbuf )
	{
		STRBUF_Delete( wk->tmpbuf );
	}

	GF_BGL_BmpWinDel(&wk->win_edit);
	GF_BGL_BmpWinDel(&wk->win_message);
	GF_BGL_BmpWinDel(&wk->win_yesno);

	sys_FreeMemoryEz( wk );
}



//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_EDIT_SetupGraphicDatas( PMSIV_EDIT* wk )
{
	GF_BGL_INI* bgl;
	u32 charpos;

	bgl = PMSIView_GetBGL( wk->vwk );


	setup_pal_datas( wk );

	ArcUtil_ScrnSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main0_lz_nscr, bgl,
		FRM_MAIN_EDITAREA, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );

	charpos = ArcUtil_BgCharSet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main0_lz_ncgr, bgl,
		FRM_MAIN_EDITAREA, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );
	charpos /= 0x20;


// BitmapWindow setup
	GF_BGL_BmpWinAdd(	bgl, &wk->win_edit, FRM_MAIN_EDITAREA, 
						EDITAREA_WIN_X, EDITAREA_WIN_Y, EDITAREA_WIN_WIDTH, EDITAREA_WIN_HEIGHT,
						PALNUM_MAIN_EDITAREA, charpos );
	charpos += EDITAREA_WIN_CHARSIZE;


	GF_BGL_BmpWinAdd(	bgl, &wk->win_message, FRM_MAIN_EDITAREA, 
						MESSAGE_WIN_X, MESSAGE_WIN_Y, MESSAGE_WIN_WIDTH, MESSAGE_WIN_HEIGHT,
						PALNUM_MAIN_CATEGORY, charpos );
	charpos += MESSAGE_WIN_CHARSIZE;


	GF_BGL_BmpWinAdd(	bgl, &wk->win_yesno, FRM_MAIN_EDITAREA, 
						YESNO_WIN_X, YESNO_WIN_Y, YESNO_WIN_WIDTH, YESNO_WIN_HEIGHT,
						PALNUM_MAIN_CATEGORY, charpos );
	charpos += YESNO_WIN_CHARSIZE;


// window frame setup
	ArcUtil_BgCharSet( ARC_WINFRAME, NARC_winframe_system_ncgr, bgl,
 			FRM_MAIN_EDITAREA, charpos, 0, FALSE, HEAPID_PMS_INPUT_VIEW );
 	wk->yesnowin_frame_charpos = charpos;
	charpos += 9;

	ArcUtil_PalSet( ARC_WINFRAME, NARC_winframe_system_nclr, PALTYPE_MAIN_BG, PALNUM_MAIN_SYSWIN*0x20,
		0x20, HEAPID_PMS_INPUT_VIEW );

	TalkWinGraphicSet( bgl, FRM_MAIN_EDITAREA, charpos, PALNUM_MAIN_TALKWIN,
						PMSI_GetTalkWindowType( wk->mwk ),
						HEAPID_PMS_INPUT_VIEW );

	BmpTalkWinScreenSet( &wk->win_message, charpos, PALNUM_MAIN_TALKWIN );

	GF_BGL_BmpWinMakeScrn( &wk->win_edit );
	GF_BGL_BmpWinMakeScrn( &wk->win_message );


//
	setup_wordarea_pos(wk);
	PMSIV_EDIT_UpdateEditArea( wk );
	PMSIV_EDIT_SetSystemMessage( wk, PMSIV_MSG_GUIDANCE );

	// PMSIV_EDIT_UpdateEditArea で単語数が確定するので、その後に。
	setup_obj( wk );

	GF_BGL_LoadScreenReq( bgl, FRM_MAIN_EDITAREA );

}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_pal_datas( PMSIV_EDIT* wk )
{
	NNSG2dPaletteData*  palDat;
	void*   data_ptr;

	// 一度全てVRAM転送する
	ArcUtil_PalSet( ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main_nclr, PALTYPE_MAIN_BG,
		 0, 14*0x20, HEAPID_PMS_INPUT_VIEW );

	// 後の色変え用にヒープにも読み込んでおく
	data_ptr = ArcUtil_PalDataGet( ARC_PMSI_GRAPHIC, NARC_pmsi_bg_main_nclr, &palDat, HEAPID_PMS_INPUT_VIEW );

	MI_CpuCopy16( palDat->pRawData, wk->pal_data, sizeof(wk->pal_data) );
	DC_FlushRange( wk->pal_data, sizeof(wk->pal_data) );


	sys_FreeMemoryEz( data_ptr );
}

static void update_editarea_palette( PMSIV_EDIT* wk )
{
	if( PMSI_GetInputMode(wk->mwk) == PMSI_MODE_SENTENCE )
	{
		int pal = 1 + PMSI_GetSentenceType(wk->mwk);

		GX_LoadBGPltt( wk->pal_data[pal], PALNUM_MAIN_EDITAREA*0x20, 0x20 );
	}
	else
	{
		GX_LoadBGPltt( wk->pal_data[0], PALNUM_MAIN_EDITAREA*0x20, 0x20 );
	}
}



static void setup_wordarea_pos( PMSIV_EDIT* wk )
{
	switch(PMSI_GetInputMode(wk->mwk)){
	case PMSI_MODE_SINGLE:
		wk->word_pos[0].x = WORDAREA_SINGLE_X;
		wk->word_pos[0].y = WORDAREA_SINGLE_Y;
		wk->word_pos_max = 1;
		break;

	case PMSI_MODE_DOUBLE:
		wk->word_pos[0].x = WORDAREA_DOUBLE_X1;
		wk->word_pos[0].y = WORDAREA_DOUBLE_Y1;
		wk->word_pos[1].x = WORDAREA_DOUBLE_X2;
		wk->word_pos[1].y = WORDAREA_DOUBLE_Y2;
		wk->word_pos_max = 2;
		break;

	case PMSI_MODE_SENTENCE:
		// 文章モードの場合、文章内容によって位置が変わるので
		// ここでは何もしない
		wk->word_pos_max = 0;
		break;
	}

}

static void setup_obj( PMSIV_EDIT* wk )
{
	CLACT_HEADER  header;
	POS  actpos;

	if( wk->word_pos_max )
	{
		wordpos_to_lcdpos( &wk->word_pos[0], &actpos );
	}
	else
	{
		actpos.x = ALLCOVER_CURSOR_XPOS;
		actpos.y = ALLCOVER_CURSOR_YPOS;
	}

	PMSIView_SetupDefaultActHeader( wk->vwk, &header, PMSIV_LCD_MAIN, BGPRI_MAIN_EDITAREA );
	wk->cursor_actor = PMSIView_AddActor( wk->vwk, &header, actpos.x, actpos.y,
			ACTPRI_EDITAREA_CURSOR, NNS_G2D_VRAM_TYPE_2DMAIN );

	set_cursor_anm( wk, TRUE );

	wk->arrow_left_actor = PMSIView_AddActor( wk->vwk, &header, LFFT_ARROW_OBJ_XPOS, LFFT_ARROW_OBJ_YPOS,
			ACTPRI_EDITAREA_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_AnmChg( wk->arrow_left_actor, ANM_EDITAREA_ARROW_LEFT );

	wk->arrow_right_actor = PMSIView_AddActor( wk->vwk, &header, RIGHT_ARROW_OBJ_XPOS, RIGHT_ARROW_OBJ_YPOS,
			ACTPRI_EDITAREA_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );

	CLACT_AnmChg( wk->arrow_right_actor, ANM_EDITAREA_ARROW_RIGHT );

	if( PMSI_GetInputMode( wk->mwk ) != PMSI_MODE_SENTENCE )
	{
		CLACT_SetDrawFlag( wk->arrow_right_actor, FALSE );
		CLACT_SetDrawFlag( wk->arrow_left_actor, FALSE );
	}

}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_EDIT_UpdateEditArea( PMSIV_EDIT* wk )
{
	update_editarea_palette( wk );

	GF_BGL_BmpWinDataFill( &wk->win_edit, EDITAREA_WIN_BASE_COLOR_GROUND );

	switch(PMSI_GetInputMode(wk->mwk)){
	case PMSI_MODE_SINGLE:
		fill_wordarea( &wk->win_edit, &wk->word_pos[0] );
		print_wordarea( wk, &wk->win_edit, &(wk->word_pos[0]), PMSI_GetEditWord(wk->mwk, 0) );
		break;
	case PMSI_MODE_DOUBLE:
		fill_wordarea( &wk->win_edit, &wk->word_pos[0] );
		fill_wordarea( &wk->win_edit, &wk->word_pos[1] );
		print_wordarea( wk, &wk->win_edit, &(wk->word_pos[0]), PMSI_GetEditWord(wk->mwk, 0) );
		print_wordarea( wk, &wk->win_edit, &(wk->word_pos[1]), PMSI_GetEditWord(wk->mwk, 1) );
		break;
	case PMSI_MODE_SENTENCE:
		wk->word_pos_max = print_sentence( wk );
		OS_TPrintf("word max:%d\n", wk->word_pos_max);
		break;
	}

	GF_BGL_BmpWinCgxOn( &wk->win_edit );
}


//------------------------------------------------------------------
/**
 * 選択されている文章を解析、整形してプリントする。
 * 解析時に判定して必要な単語数を返す
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
static u32 print_sentence( PMSIV_EDIT* wk )
{
	STRBUF* buf = PMSI_GetEditSourceString( wk->mwk, HEAPID_PMS_INPUT_VIEW );
	int x, y, word_pos;
	BOOL cont_flag;
	PMS_WORD  word_code;

	x = y = word_pos = 0;
	cont_flag = TRUE;

	setup_pms_analyze( &wk->awk, wk );

	while( cont_flag )
	{
		switch( prog_pms_analyze( &(wk->awk), buf ) ){
		case PMS_ANALYZE_RESULT_STR:
			GF_STR_PrintColor( &wk->win_edit, PMSI_FONT_EDITAREA_BASE, buf, x, y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(EDITAREA_WIN_BASE_COLOR_LETTER, EDITAREA_WIN_BASE_COLOR_SHADOW, EDITAREA_WIN_BASE_COLOR_GROUND),
				NULL);
			x += FontProc_GetPrintStrWidth(PMSI_FONT_EDITAREA_BASE, buf, 0);
			break;

		case PMS_ANALYZE_RESULT_TAG:
			x += WORDAREA_X_MARGIN;
			wk->word_pos[word_pos].x = x + (WORDAREA_WIDTH/2);
			wk->word_pos[word_pos].y = y + (WORDAREA_HEIGHT/2);
			fill_wordarea( &wk->win_edit, &(wk->word_pos[word_pos]) );
			word_code = PMSI_GetEditWord(wk->mwk, word_pos);
			if( word_code != PMS_WORD_NULL )
			{
				print_wordarea( wk, &wk->win_edit, &(wk->word_pos[word_pos]), word_code );
			}
			word_pos++;
			x += (WORDAREA_X_MARGIN+WORDAREA_WIDTH);
			break;

		case PMS_ANALYZE_RESULT_CR:
			y += EDITAREA_LINE_HEIGHT;
			x = 0;
			break;

		case PMS_ANALYZE_RESULT_END:
			cont_flag = FALSE;
			break;
		}
	}

	cleanup_pms_analyze( &wk->awk );
	STRBUF_Delete( buf );

	return word_pos;
}

//======================================================================================
//======================================================================================
enum {
	PMS_ANALYZE_STATE_STR,
	PMS_ANALYZE_STATE_TAG,
	PMS_ANALYZE_STATE_CR,
	PMS_ANALYZE_STATE_END,
};

static void setup_pms_analyze( PMS_ANALYZE_WORK* awk, PMSIV_EDIT* wk )
{
	awk->src = PMSI_GetEditSourceString( wk->mwk, HEAPID_PMS_INPUT_VIEW );
	awk->p = STRBUF_GetStringCodePointer( awk->src );

	if( *(awk->p) == _CTRL_TAG )
	{
		awk->state = PMS_ANALYZE_STATE_TAG;
	}
	else
	{
		awk->state = PMS_ANALYZE_STATE_STR;
	}
}

static void cleanup_pms_analyze( PMS_ANALYZE_WORK* awk )
{
	STRBUF_Delete( awk->src );
}

static int prog_pms_analyze( PMS_ANALYZE_WORK* awk, STRBUF* buf )
{
	const STRCODE* bp = awk->p;
	int ret;

	switch( awk->state ){
	case PMS_ANALYZE_STATE_STR:
		while( awk->state == PMS_ANALYZE_STATE_STR )
		{
			switch( *(awk->p) ){
			case CR_:
				awk->state = PMS_ANALYZE_STATE_CR;
				break;
			case EOM_:
				awk->state = PMS_ANALYZE_STATE_END;
				break;
			case _CTRL_TAG:
				awk->state = PMS_ANALYZE_STATE_TAG;
				break;
			default:
				awk->p++;
				break;
			}
		}
		STRBUF_SetStringCodeOrderLength( buf, bp, (awk->p-bp)+1 );
		return PMS_ANALYZE_RESULT_STR;

	case PMS_ANALYZE_STATE_TAG:
		awk->p = STRCODE_SkipTag(awk->p);
		ret = PMS_ANALYZE_RESULT_TAG;
		break;

	case PMS_ANALYZE_STATE_CR:
		awk->p++;
		ret = PMS_ANALYZE_RESULT_CR;
		break;

	case PMS_ANALYZE_STATE_END:
	default:
		return PMS_ANALYZE_RESULT_END;
	}

	switch( *(awk->p) ){
	case CR_:
		awk->state = PMS_ANALYZE_STATE_CR;
		break;
	case EOM_:
		awk->state = PMS_ANALYZE_STATE_END;
		break;
	case _CTRL_TAG:
		awk->state = PMS_ANALYZE_STATE_TAG;
		break;
	default:
		awk->state = PMS_ANALYZE_STATE_STR;
		break;
	}

	return ret;


}
//======================================================================================
//======================================================================================

static void wordpos_to_orgpos( const POS* wordpos, POS* orgpos)
{
	orgpos->x = wordpos->x - (WORDAREA_WIDTH/2);
	orgpos->y = wordpos->y - (WORDAREA_HEIGHT/2);
}
static void wordpos_to_lcdpos( const POS* wordpos, POS* lcdpos )
{
	lcdpos->x = wordpos->x + EDITAREA_WIN_X * 8;
	lcdpos->y = wordpos->y + EDITAREA_WIN_Y * 8;
}

static void fill_wordarea( GF_BGL_BMPWIN* win, const POS* wordpos )
{
	POS   drawpos;

	wordpos_to_orgpos( wordpos, &drawpos );

	GF_BGL_BmpWinFill( win, EDITAREA_WIN_WORD_COLOR_GROUND,
			drawpos.x, drawpos.y,
			WORDAREA_WIDTH, WORDAREA_HEIGHT );
}

static void print_wordarea( PMSIV_EDIT* wk, GF_BGL_BMPWIN* win, const POS* wordpos, PMS_WORD word )
{
	if( word != PMS_WORD_NULL )
	{
		POS  print_pos;
		u32  write_xpos;

		wordpos_to_orgpos( wordpos, &print_pos );

		PMSW_GetStr(word, wk->tmpbuf);
		write_xpos = (print_pos.x + (WORDAREA_WIDTH / 2)) - (FontProc_GetPrintStrWidth(PMSI_FONT_EDITAREA_WORD, wk->tmpbuf, 0) / 2);
		GF_STR_PrintColor( win, PMSI_FONT_EDITAREA_WORD, wk->tmpbuf, print_pos.x, print_pos.y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(EDITAREA_WIN_WORD_COLOR_LETTER, EDITAREA_WIN_WORD_COLOR_SHADOW, EDITAREA_WIN_WORD_COLOR_GROUND),
				NULL);
	}
}

//======================================================================================
//======================================================================================
u32 PMSIV_EDIT_GetWordPosMax( const PMSIV_EDIT* wk )
{
	return wk->word_pos_max;
}

//======================================================================================
//======================================================================================
#include "system\wordset.h"
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_EDIT_SetSystemMessage( PMSIV_EDIT* wk, u32 msg_type )
{
	GF_BGL_BmpWinDataFill( &wk->win_message, MESSAGE_WIN_COL_GROUND);

	switch( msg_type ){
	case PMSIV_MSG_GUIDANCE:
	#if 1
		{
			WORDSET* wordset = WORDSET_CreateEx(2, 60, HEAPID_BASE_SYSTEM);
			STRBUF*  exbuf = STRBUF_Create( 300, HEAPID_BASE_SYSTEM );

			WORDSET_RegisterItemPocketWithIcon( wordset, 0, 0 );
			MSGMAN_GetString( wk->msgman, info00 + PMSI_GetGuidanceType(wk->mwk), wk->tmpbuf );
			WORDSET_ExpandStr( wordset, exbuf, wk->tmpbuf );
			GF_STR_PrintColor( &wk->win_message, PMSI_FONT_MESSAGE, exbuf, 0, 0, MSG_NO_PUT,
					GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
					NULL);


			STRBUF_Delete(exbuf);
			WORDSET_Delete(wordset);
		}
	#else
		MSGMAN_GetString( wk->msgman, info00 + PMSI_GetGuidanceType(wk->mwk), wk->tmpbuf );
		GF_STR_PrintColor( &wk->win_message, PMSI_FONT_MESSAGE, wk->tmpbuf, 0, 0, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
				NULL);
	#endif
		break;

	case PMSIV_MSG_CONFIRM_DECIDE:
		MSGMAN_GetString( wk->msgman, msg_00, wk->tmpbuf );
		GF_STR_PrintColor( &wk->win_message, PMSI_FONT_MESSAGE, wk->tmpbuf, 0, 0, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
				NULL);
		break;

	case PMSIV_MSG_WARN_INPUT:
		MSGMAN_GetString( wk->msgman, msg_01, wk->tmpbuf );
		GF_STR_PrintColor( &wk->win_message, PMSI_FONT_MESSAGE, wk->tmpbuf, 0, 0, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
				NULL);
		break;

	case PMSIV_MSG_CONFIRM_CANCEL:
		MSGMAN_GetString( wk->msgman, msg_02, wk->tmpbuf );
		GF_STR_PrintColor( &wk->win_message, PMSI_FONT_MESSAGE, wk->tmpbuf, 0, 0, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
				NULL);
		break;

	}

	GF_BGL_BmpWinCgxOn( &wk->win_message );

}

void PMSIV_EDIT_StopCursor( PMSIV_EDIT* wk )
{
	set_cursor_anm( wk, FALSE );
}
void PMSIV_EDIT_ActiveCursor( PMSIV_EDIT* wk )
{
	set_cursor_anm( wk, TRUE );
}
void PMSIV_EDIT_VisibleCursor( PMSIV_EDIT* wk, BOOL flag )
{
	CLACT_SetDrawFlag( wk->cursor_actor, flag );
	set_cursor_anm( wk, TRUE );
}


void PMSIV_EDIT_StopArrow( PMSIV_EDIT* wk )
{
	if( PMSI_GetInputMode( wk->mwk ) == PMSI_MODE_SENTENCE )
	{
		CLACT_SetDrawFlag( wk->arrow_left_actor, FALSE );
		CLACT_SetDrawFlag( wk->arrow_right_actor, FALSE );
	}
}
void PMSIV_EDIT_ActiveArrow( PMSIV_EDIT* wk )
{
	if( PMSI_GetInputMode( wk->mwk ) == PMSI_MODE_SENTENCE )
	{
		CLACT_SetDrawFlag( wk->arrow_left_actor, TRUE );
		CLACT_SetDrawFlag( wk->arrow_right_actor, TRUE );

		CLACT_AnmChg( wk->arrow_left_actor, ANM_EDITAREA_ARROW_LEFT );
		CLACT_AnmChg( wk->arrow_right_actor, ANM_EDITAREA_ARROW_RIGHT );
	}
}


void PMSIV_EDIT_MoveCursor( PMSIV_EDIT* wk, int pos )
{
	VecFx32  mtx;

	if( wk->word_pos_max )
	{
		POS  actpos;

		wordpos_to_lcdpos( &wk->word_pos[pos], &actpos );
		mtx.x = actpos.x * FX32_ONE;
		mtx.y = actpos.y * FX32_ONE;
		mtx.z = 0;
	}
	else
	{
		mtx.x = ALLCOVER_CURSOR_XPOS * FX32_ONE;
		mtx.y = ALLCOVER_CURSOR_YPOS * FX32_ONE;
		mtx.z = 0;

		CLACT_SetMatrix( wk->cursor_actor, &mtx );
	}
	CLACT_SetMatrix( wk->cursor_actor, &mtx );
	set_cursor_anm( wk, TRUE );
}


static void set_cursor_anm( PMSIV_EDIT* wk, BOOL active_flag )
{
	if( wk->word_pos_max != 0 )
	{
		if( active_flag )
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_EDITAREA_CURSOR_ACTIVE );
		}
		else
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_EDITAREA_CURSOR_STOP );
		}
	}
	else
	{
		if( active_flag )
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_EDITAREA_ALLCOVER_CURSOR_ACTIVE );
		}
		else
		{
			CLACT_AnmChg( wk->cursor_actor, ANM_EDITAREA_ALLCOVER_CURSOR_STOP );
		}
	}
}



//======================================================================================
//======================================================================================


void PMSIV_EDIT_DispYesNoWin( PMSIV_EDIT* wk, int cursor_pos )
{
	GF_BGL_BmpWinDataFill( &wk->win_yesno, YESNOWIN_COL_GROUND );

	MSGMAN_GetString( wk->msgman, str_yes, wk->tmpbuf );
	GF_STR_PrintColor( &wk->win_yesno, PMSI_FONT_YESNO, wk->tmpbuf, YESNOWIN_STR_OX, YESNOWIN_STR_OY, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
			NULL);

	MSGMAN_GetString( wk->msgman, str_no, wk->tmpbuf );
	GF_STR_PrintColor( &wk->win_yesno, PMSI_FONT_YESNO, wk->tmpbuf, YESNOWIN_STR_OX, YESNOWIN_STR_OY+YESONOWIN_LINE_HEIGHT, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(MESSAGE_WIN_COL_LETTER, MESSAGE_WIN_COL_SHADOW, MESSAGE_WIN_COL_GROUND),
			NULL);

	BmpMenuWinWrite( &wk->win_yesno, FALSE, wk->yesnowin_frame_charpos, PALNUM_MAIN_SYSWIN );
	BMPCURSOR_Print( wk->bmp_cursor, &wk->win_yesno, YESNOWIN_CURSOR_OX, YESNOWIN_CURSOR_OY+(cursor_pos*YESONOWIN_LINE_HEIGHT) );

	GF_BGL_BmpWinOn( &wk->win_yesno );

}

void PMSIV_EDIT_MoveYesNoCursor( PMSIV_EDIT* wk, int pos )
{
//	void GF_BGL_BmpWinFill( GF_BGL_BMPWIN * win, u8 col, u16 px, u16 py, u16 sx, u16 sy )
	GF_BGL_BmpWinFill( &wk->win_yesno, YESNOWIN_COL_GROUND, 0, 0, YESNOWIN_STR_OX, YESNO_WIN_HEIGHT*8 );
	BMPCURSOR_Print( wk->bmp_cursor, &wk->win_yesno, YESNOWIN_CURSOR_OX, YESNOWIN_CURSOR_OY+(pos*YESONOWIN_LINE_HEIGHT) );

}

void PMSIV_EDIT_EraseYesNoWin( PMSIV_EDIT* wk )
{
	BmpMenuWinClear( &wk->win_yesno, FALSE );
	GF_BGL_BmpWinOff( &wk->win_yesno );
}
