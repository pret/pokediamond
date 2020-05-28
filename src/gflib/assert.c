//==============================================================================
/**
 *
 *@file		assert.c
 *@brief	アサート
 *@author	taya
 *@date		2005.08.08
 *
 */
//==============================================================================
#include "common.h"
#include "gflib\assert.h"

#ifdef GF_ASSERT_ENABLED


//==============================================================================================
//
// 実機表示処理
//
//==============================================================================================

// この定義を有効にすると、デバッガ動作中でも強制的に情報を画面出力する
//#define  FORCE_OUTPUT_LCD

#include  "gflib\bg_system.h"
#include  "gflib\strbuf_family.h"
#include  "system\fontproc.h"

static u8 OutputLcdFlag = FALSE;
static u8 ScreenInitializedFlag = FALSE;

static int  PrintPosY = 0;
static int  PrintPosX = 0;
static GF_BGL_BMPWIN   BmpWin = {0};
static GF_BGL_INI*     BglSys = NULL;


static const u16       PaletteData[] = { 0x0000, 0x7fff, 0x4e73, 0x70a3 };
enum {
	COL_LETTER = 1,
	COL_SHADOW,
	COL_GROUND,
};

//------------------------------------------------------------------
/**
 * DS画面出力時の初期化を行う
 */
//------------------------------------------------------------------
static void InitAssertScreen(void)
{
	if( ScreenInitializedFlag )
	{
		return;
	}

	if( OutputLcdFlag )
	{
		GF_Disp_GX_VisibleControlInit();
		GX_SetVisiblePlane( 0 );

		GX_ResetBankForBG();
		GX_SetBankForBG( GX_VRAM_BG_128_A );
		GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
		GX_SetGraphicsMode( GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
		G2_BlendNone();
		GX_SetMasterBrightness(0);
		GX_SetVisibleWnd(GX_WNDMASK_NONE);

		{
			static const GF_BGL_BGCNT_HEADER  frm_header = {
				0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
				GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000,
				GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
			};

			BglSys = GF_BGL_BglIniAlloc(HEAPID_BASE_SYSTEM);
			GF_BGL_BGControlSet( BglSys, GF_BGL_FRAME0_M,  &frm_header, GF_BGL_MODE_TEXT );
			GF_BGL_BmpWinAdd( BglSys, &BmpWin, GF_BGL_FRAME0_M, 0, 0, 32, 24, 0, 0 );
			GX_LoadBGPltt(PaletteData, 0, sizeof(PaletteData));

			GF_BGL_BmpWinDataFill(&BmpWin, COL_GROUND);
		}

		PrintPosX = PrintPosY = 0;
	}

	ScreenInitializedFlag = TRUE;
}


static void GF_ASSERT_VPrintfCore(const char *fmt, va_list vlist)
{
	enum {
		TMP_BUFFER_SIZE = 512,
		UNKNOWN_CHARCODE = h_nakag_,
		IGNORE_CHARCODE  = 0xfffe,
	};

	char*   buf; 
	STRBUF* strbuf; 

	buf = sys_AllocMemory(HEAPID_BASE_SYSTEM, TMP_BUFFER_SIZE);
	strbuf = STRBUF_Create(TMP_BUFFER_SIZE, HEAPID_BASE_SYSTEM);

	if( (buf!=NULL) && (strbuf!=NULL) )
	{
		unsigned char* p;
		STRCODE code;
		int  line_cnt = 0;

		OS_VSNPrintf(buf, TMP_BUFFER_SIZE, fmt, vlist);
		p = (unsigned char*)buf;
		while( *p != '\0' )
		{
			// 2byte文字の1byte目
			if( ((*p >= 0x81) && (*p <= 0x9f)) || ((*p >= 0xe0) && (*p <= 0xff)) )
			{
				code = UNKNOWN_CHARCODE;
				p += 2;
			}
			else
			{
				static const struct {
					unsigned char  sjis_code;
					STRCODE        gf_code;
				}code_translate_tbl[] = {
					{  ' ',   h_spc_ },
					{  '!',   h_gyoe_ },
					{  '?',   h_hate_ },
					{  '(',   h_MaruKako__ },
					{  ')',   h_MaruKakot__ },
					{  '-',   h_bou_ },
					{  '+',   h_plus_ },
					{  '*',   times_ },
					{  ':',   h_colon_ },
					{  ';',   h_semicolon_ },
					{  ',',   h_comma_ },
					{  '.',   h_period_ },
					{  '_',   h_bou_ },
					{  '=',   h_equal_ },
					{  '/',   h_sura_ },
					{  '\'',  us_h_quote1_ },
					{  '\r',  IGNORE_CHARCODE },
				};
				int i;

				do {
					if( (*p >= 'a') && (*p <= 'z' ) ){ code = h_a__ + (*p - 'a'); break; }
					if( (*p >= 'A') && (*p <= 'Z' ) ){ code = h_A__ + (*p - 'A'); break; }
					if( (*p >= '0') && (*p <= '9' ) ){ code = h_n0_ + (*p - '0'); break; }
					if( (*p == '\n') )
					{
						code = CR_;
						line_cnt++;
						break;
					}

					for(i=0; i<NELEMS(code_translate_tbl); i++)
					{
						if( *p == code_translate_tbl[i].sjis_code )
						{
							code = code_translate_tbl[i].gf_code;
							break;
						}
					}
					if( i == NELEMS(code_translate_tbl) )
					{
						code = UNKNOWN_CHARCODE;
					}

				}while(0);

				p++;
			}

			if( code != IGNORE_CHARCODE )
			{
				STRBUF_AddChar(strbuf, code);
			}
		}/* while(*p != '\0') */

		GF_STR_PrintColor( &BmpWin, FONT_SYSTEM, strbuf, PrintPosX, PrintPosY, MSG_ALLPUT,
			GF_PRINTCOLOR_MAKE(COL_LETTER, COL_SHADOW, COL_GROUND),  NULL );

		if( line_cnt )
		{
			PrintPosY += (line_cnt * 16);
			PrintPosX = 0;
		}
		else
		{
			PrintPosX += FontProc_GetPrintStrWidth( FONT_SYSTEM, strbuf, 0 );
		}

		STRBUF_Delete(strbuf);
		sys_FreeMemoryEz(buf);
	}
}

//==============================================================================================
//
// 文字列表示処理（実行環境に応じて出力先を デバッガ／実機 に振り分ける）
//
//==============================================================================================
static void GF_ASSERT_VPrintf( const char *fmt, va_list vlist )
{
	InitAssertScreen();

	if( OutputLcdFlag )
	{
		GF_ASSERT_VPrintfCore( fmt, vlist );
	}
	else
	{
		OS_TVPrintf( fmt, vlist );
	}
}


void GF_ASSERT_Printf( const char* fmt, ... )
{
    va_list vlist;

    va_start(vlist, fmt);
    GF_ASSERT_VPrintf(fmt, vlist);
    va_end(vlist);
}




//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * アサートメッセージ表示後のキー待ちループ
 */
//------------------------------------------------------------------
static void BreakAssertKeyWait(void)
{
	#define ESCAPE_KEY_MASK	(PAD_BUTTON_X|PAD_BUTTON_Y)

	while(1){
		OS_WaitAnyIrq();

		sys_MainKeyRead();

		if((sys.cont & ESCAPE_KEY_MASK) == ESCAPE_KEY_MASK){
			break;
		}

		
	}
	#undef ESCAPE_KEY_MASK
}

//------------------------------------------------------------------
/**
 * アサート失敗箇所のソース情報を出力
 */
//------------------------------------------------------------------
static void PrintBaseMessage(const char* filename, unsigned int line_no)
{
	GF_ASSERT_Printf("  **** ASSERTION FAILED ! **** \n");
	GF_ASSERT_Printf(filename);
	GF_ASSERT_Printf("(%d)\n", line_no);
}


//==============================================================================================
//==============================================================================================


static struct {
	u8           waitFlag;
	u32          lineNum;
	const char*  fileName;
	const char*  string;
	char         vprintBuf[ 256 ];
}IntrPrintWork;

//------------------------------------------------------------------
/**
 * アサートシステム初期化（プログラム起動時に１回だけ呼ぶ）
 */
//------------------------------------------------------------------
void GF_AssertInit( void )
{
	#ifndef FORCE_OUTPUT_LCD
	OutputLcdFlag = ((OS_GetConsoleType() & OS_CONSOLE_MASK ) != OS_CONSOLE_ISDEBUGGER);
	#else
	OutputLcdFlag = TRUE;
	#endif

	IntrPrintWork.waitFlag = FALSE;
}

//------------------------------------------------------------------
/**
 * アサート監視（メインループ内で呼び続ける）
 */
//------------------------------------------------------------------
void GF_AssertMain( void )
{
	if( IntrPrintWork.waitFlag )
	{
		PrintBaseMessage( IntrPrintWork.fileName, IntrPrintWork.lineNum );
		GF_ASSERT_Printf( "%s\n", IntrPrintWork.string );
		BreakAssertKeyWait();
		IntrPrintWork.waitFlag = FALSE;
	}
}


static BOOL IsIntrPrintNecessary( void )
{
	if( OutputLcdFlag && (OS_GetProcMode() == OS_PROCMODE_IRQ) )
	{
		return TRUE;
	}
	return FALSE;
}

//==============================================================================================
//==============================================================================================


//------------------------------------------------------------------
/**
 * アサート失敗時にマクロで呼び出される関数本体（通常版）
 *
 * @param   filename		呼び出しソースファイル名
 * @param   line_no			呼び出しソースファイル行番号
 * @param   exp				マクロ引数
 *
 */
//------------------------------------------------------------------
void GF_AssertProc(const char* filename, unsigned int line_no, const char* exp)
{
	if( IntrPrintWork.waitFlag == FALSE )
	{
		if( IsIntrPrintNecessary() == FALSE )
		{
			PrintBaseMessage(filename, line_no);
			GF_ASSERT_Printf("%s\n", exp);
			BreakAssertKeyWait();
		}
		else
		{
			IntrPrintWork.waitFlag = TRUE;
			IntrPrintWork.fileName = filename;
			IntrPrintWork.lineNum  = line_no;
			IntrPrintWork.string   = exp;
		}
	}
}
//------------------------------------------------------------------
/**
 * アサート失敗時にマクロで呼び出される関数本体（書式付き文字列表示版）
 *
 * @param   filename		
 * @param   line_no		
 * @param   exp			
 *
 */
//------------------------------------------------------------------
void GF_AssertMsgProc( const char* filename, unsigned int line_no, const char* fmt, ... )
{
	if( IntrPrintWork.waitFlag == FALSE )
	{
		va_list vlist;

		if( IsIntrPrintNecessary() == FALSE )
		{
			PrintBaseMessage(filename, line_no);
			va_start(vlist, fmt);
			GF_ASSERT_VPrintf(fmt, vlist);
			va_end(vlist);
			GF_ASSERT_Printf("\n");
			BreakAssertKeyWait();
		}
		else
		{
			IntrPrintWork.waitFlag = TRUE;
			IntrPrintWork.fileName = filename;
			IntrPrintWork.lineNum  = line_no;

			va_start( vlist, fmt );
			OS_VSNPrintf( IntrPrintWork.vprintBuf, sizeof(IntrPrintWork.vprintBuf), fmt, vlist );
			va_end( vlist );
			IntrPrintWork.string = IntrPrintWork.vprintBuf;
		}
	}

}

#endif  /* #ifdef GF_ASSERT_ENABLE */

//==============================================================================================
//==============================================================================================

#include "system\assert_warning_reset.h"
#include "communication\comm_state.h"

void GF_AssertFailedWarningCall( void )
{
	if( CommStateIsInitialize() && (OS_GetProcMode() != OS_PROCMODE_IRQ) )
	{
		AssertWarningResetCall();
	}
}


