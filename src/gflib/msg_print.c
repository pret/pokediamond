//=============================================================================================
/**
 * @file	msg_print.c
 * @brief	ビットマップ文字列表示用システム
 * @author	tetsu
 * @date	2003.03.17
 *
 * @data	2004.11.04 AGB -> NDS
 * @author	Hiroyuki Nakamura
 */
//=============================================================================================
#include <nitro.h>
#include "gflib/assert.h"
#include "system.h"
#include "bg_system.h"
#include "tcb.h"

#define	__MSG_PRINT_H_GLOBAL
#include "msg_print.h"

#include "system\fontproc.h"
#include "system/arc_util.h"
#include "system/font_arc.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "gflib/display.h"
#include "gflib/char_manager.h"
#include "gflib/pltt_manager.h"


typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ
	CLACT_HEADER_TBL_PTR	clh;		// ヘッダー
	CLACT_U_RES_MANAGER_PTR	resMan[4];	// リソースマネージャ
	CLACT_U_RES_OBJ_TBL * resObjTbl[2];	// リソースオブジェテーブル
	int resObjNum[4];					// それぞれのリソースオブジェ数
	CLACT_WORK_PTR	cwp;
}TRG_CURSOR;



//==================================================================
//	変数 ＆ 関数宣言
//==================================================================
static PRINT_RESULT	MSG_PrintDataSet( GF_BGL_INI * ini, MSG_DATA_HEADER * mdh_p );
static PRINT_RESULT GF_MSG_PrintDataSet( MSG_DATA_HEADER * mdh_p );
static void GF_MSG_PrintMain( TCB_PTR tcb, void *work );
static u8 SetNewPrintTask(TCB_FUNC func, void* work, u32 task_pri);
static void DeletePrintTask( u8 index );


static void DispIconInit( MSG_DATA_HEADER* mdh );
static void DispIconExit( MSG_DATA_HEADER* mdh );
static u8*  DispIconCreate(void);


static const MSG_FONT_HEADER*	font_header = NULL;

static u8				msg_main_pause = 0;
//static MSG_DATA_HEADER	mdh_buf = {0};



//---------------------------------------------------------------------------------------------
/**
 *	文字表示システム初期化関数
 *
 * @param	フォント関数群ヘッダ
 *
 * @retval	なし
 */
//---------------------------------------------------------------------------------------------
void MSG_PrintSysInit( const MSG_FONT_HEADER * header )
{
	font_header = header;
}







//==============================================================================================
//
// 文字出力タスクを管理するための仕組み
//
//==============================================================================================


enum {
	PRINTTASK_MAX = 8	// 文字出力タスクを登録できる総数
};
static TCB_PTR			PrintTaskTable[PRINTTASK_MAX] = {0};


//------------------------------------------------------------------
/**
 * 新しい文字表示タスクをセットする
 *
 * @retval  u8		セットしたタスクのインデックス値
 */
//------------------------------------------------------------------
static u8 SetNewPrintTask(TCB_FUNC func, void* work, u32 task_pri)
{
	int i;

	for( i=0; i<PRINTTASK_MAX; i++ ){
		if( PrintTaskTable[i] == NULL )
		{
			PrintTaskTable[i] = PrintTCB_Add(func, work, task_pri);
			if( PrintTaskTable[i] == NULL )
			{
				i = PRINTTASK_MAX;
			}
			break;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * 文字表示タスクを停止・削除する
 *
 * @param   index		タスクインデックス値
 *
 */
//------------------------------------------------------------------
static void DeletePrintTask( u8 index )
{
	GF_ASSERT(index < PRINTTASK_MAX);
	GF_ASSERT(PrintTaskTable[index]!=NULL);

	if( index < PRINTTASK_MAX && PrintTaskTable[index] != NULL )
	{
//		void *work = TCB_GetWork(PrintTaskTable[index]);
		MSG_DATA_HEADER * work = TCB_GetWork(PrintTaskTable[index]);
		if(work)
		{
			DispIconExit( work );
			sys_FreeMemoryEz(work);
		}
		TCB_Delete(PrintTaskTable[index]);
		PrintTaskTable[index] = NULL;
	}
}

//------------------------------------------------------------------
/**
 * 指定インデックスの文字表示タスクが終了しているかチェック
 *
 * @param   index		インデックス値
 *
 * @retval  BOOL		TRUEで終了している／FALSEで動作中
 */
//------------------------------------------------------------------
static BOOL CheckPrintTaskWorking( u8 index )
{
	return PrintTaskTable[index] != NULL;
}

//-------------------------------------------------------------------------------------
/**
 *	文字表示初期化関数
 *
 * @param	なし
 *
 * @retval	なし
 */
//-------------------------------------------------------------------------------------
void MSG_PrintInit(void)
{
	int i;

	for(i=0; i<PRINTTASK_MAX; i++)
	{
		PrintTaskTable[i] = NULL;
	}
}
//---------------------------------------------------------------------------------------------
/*
 * 文字表示終了チェック関数
 *
 * @param	msg_index	メッセージインデックス
 *
 * @retval	0	終了
 * @retval	1	処理中
 */
//---------------------------------------------------------------------------------------------
u8 GF_MSG_PrintEndCheck( u8 msg_index )
{
	return CheckPrintTaskWorking(msg_index);
}

//------------------------------------------------------------------
/**
 * 文字表示のタスクを強制停止する
 *
 * @param   msg_index		メッセージインデックス
 *
 */
//------------------------------------------------------------------
void GF_STR_PrintForceStop( u8 msg_index )
{
	DeletePrintTask( msg_index );
}



#include "gflib/strbuf_family.h"


//------------------------------------------------------------------------------
/**
 * BitmapWindow の内部CGX領域に文字を描画する（簡易版）
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		フォントＩＤ
 * @param   msg			[in]  描画文字列が格納されている文字バッファ
 * @param   xofs		描画開始点Ｘ座標（ドット単位）
 * @param   yofs		描画開始点Ｙ座標（ドット単位）
 * @param   wait		１文字描画ごとのウェイトフレーム数（※）
 * @param   callback	１文字描画ごとのコールバック関数アドレス（不要ならNULL）
 *
 * @retval  u8			生成される文字描画ルーチンのインデックス
 *
 * ※ wait に MSG_NO_PUT を指定した場合、キャラ領域に対する描画のみが実行される
 *            MSG_ALLPUT を指定した場合、キャラ領域描画＋BitmapWindowスクリーン作成＋それらのVRam転送が行われる
 *            それ以外の値を指定した場合、
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintSimple( GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;		//使用フォントINDEX
	mph.start_x		= xofs;			//ウインドウ内表示開始Xオフセット
	mph.start_y		= yofs;			//ウインドウ内表示開始Yオフセット
	mph.write_x		= xofs;			//ウインドウ内描画Xオフセット
	mph.write_y		= yofs;			//ウインドウ内描画Yオフセット
	mph.space_x		= font_header[fontID].space_x;	//文字間隔X
	mph.space_y		= font_header[fontID].space_y;	//文字間隔Y
	mph.style		= font_header[fontID].style;		//フォントスタイル
	mph.f_col		= font_header[fontID].f_col;		//文字色ナンバー
	mph.b_col		= font_header[fontID].b_col;		//背景色ナンバー
	mph.s_col		= font_header[fontID].s_col;		//影色　ナンバー
	mph.dot_tbl		= 0;			//拡大用ドットテーブル
	mph.dot_wy		= 0;			//拡大時のY座標の描画補正値

	return GF_STR_Print( &mph, wait, call_back );
}

//------------------------------------------------------------------------------
/**
 * BitmapWindow の内部CGX領域に文字を描画する（カラー指定版）
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		フォントＩＤ
 * @param   msg			[in]  描画文字列が格納されている文字バッファ
 * @param   xofs		描画開始点Ｘ座標（ドット単位）
 * @param   yofs		描画開始点Ｙ座標（ドット単位）
 * @param   wait		１文字描画ごとのウェイトフレーム数（※）
 * @param   col			描画に使う色番号（GF_PRINTCOLOR_MAKEマクロを使用すること）
 * @param   callback	１文字描画ごとのコールバック関数アドレス（不要ならNULL）
 *
 * @retval  u8			生成される文字描画ルーチンのインデックス
 *
 * ※ wait に MSG_NO_PUT を指定した場合、キャラ領域に対する描画のみが実行される
 *            MSG_ALLPUT を指定した場合、キャラ領域描画＋BitmapWindowスクリーン作成＋それらのVRam転送が行われる
 *            それ以外の値を指定した場合、
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintColor(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, pStrPrintCallBack call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;		//使用フォントINDEX
	mph.start_x		= xofs;			//ウインドウ内表示開始Xオフセット
	mph.start_y		= yofs;			//ウインドウ内表示開始Yオフセット
	mph.write_x		= xofs;			//ウインドウ内描画Xオフセット
	mph.write_y		= yofs;			//ウインドウ内描画Yオフセット
	mph.space_x		= font_header[fontID].space_x;	//文字間隔X
	mph.space_y		= font_header[fontID].space_y;	//文字間隔Y
	mph.style		= font_header[fontID].style;		//フォントスタイル
	mph.f_col		= GF_PRINTCOLOR_GET_LETTER(col);
	mph.s_col		= GF_PRINTCOLOR_GET_SHADOW(col);
	mph.b_col		= GF_PRINTCOLOR_GET_GROUND(col);
	mph.dot_tbl		= 0;			//拡大用ドットテーブル
	mph.dot_wy		= 0;			//拡大時のY座標の描画補正値

	return GF_STR_Print( &mph, wait, call_back );
}

//------------------------------------------------------------------------------
/**
 * BitmapWindow の内部CGX領域に文字を描画する（カラー＆字間・行間指定版）
 *
 * @param   win			[out] BitmapWindow
 * @param   fontID		フォントＩＤ
 * @param   msg			[in]  描画文字列が格納されている文字バッファ
 * @param   xofs		描画開始点Ｘ座標（ドット単位）
 * @param   yofs		描画開始点Ｙ座標（ドット単位）
 * @param   wait		１文字描画ごとのウェイトフレーム数（※）
 * @param   col			描画に使う色番号（GF_PRINTCOLOR_MAKEマクロを使用すること）
 * @param   xspc		文字ごとの間隔（ドット単位）
 * @param   yspc		行ごとの間隔（ドット単位）
 * @param   callback	１文字描画ごとのコールバック関数アドレス（不要ならNULL）
 *
 * @retval  u8			生成される文字描画ルーチンのインデックス
 *
 * ※ wait に MSG_NO_PUT を指定した場合、キャラ領域に対する描画のみが実行される
 *            MSG_ALLPUT を指定した場合、キャラ領域描画＋BitmapWindowスクリーン作成＋それらのVRam転送が行われる
 *            それ以外の値を指定した場合、
 *
 */
//------------------------------------------------------------------------------
u8 GF_STR_PrintExpand(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, u32 xspc, u32 yspc, pStrPrintCallBack  call_back )
{
	MSG_PRINT_HEADER	mph;

	mph.strbuf		= msg;
	mph.bmpwin		= win;
	mph.fnt_index	= fontID;	//使用フォントINDEX
	mph.start_x		= xofs;		//ウインドウ内表示開始Xオフセット
	mph.start_y		= yofs;		//ウインドウ内表示開始Yオフセット
	mph.write_x		= xofs;		//ウインドウ内描画Xオフセット
	mph.write_y		= yofs;		//ウインドウ内描画Yオフセット
	mph.space_x		= xspc;		//文字間隔X
	mph.space_y		= yspc;		//文字間隔Y
	mph.style		= font_header[fontID].style;		//フォントスタイル
	mph.f_col		= GF_PRINTCOLOR_GET_LETTER(col);
	mph.s_col		= GF_PRINTCOLOR_GET_SHADOW(col);
	mph.b_col		= GF_PRINTCOLOR_GET_GROUND(col);
	mph.dot_tbl		= 0;			//拡大用ドットテーブル
	mph.dot_wy		= 0;			//拡大時のY座標の描画補正値

	return GF_STR_Print( &mph, wait, call_back );

}

//------------------------------------------------------------------
/**
 * BitmapWindow の内部CGX領域に文字を描画する
 *
 * @param   mph_p			
 * @param   wait			
 * @param   call_back		
 *
 * @retval  u8			生成される文字描画ルーチンのインデックス
 */
//------------------------------------------------------------------
u8 GF_STR_Print( const MSG_PRINT_HEADER* mph_p, u32 wait, pStrPrintCallBack call_back )
{
	MSG_DATA_HEADER * mdh_p;
	int i;

	if(font_header == NULL){
		return 0xff;		//フォントデータ取得プログラムが設定されていない
	}

	mdh_p = sys_AllocMemory( HEAPID_BASE_SYSTEM, sizeof(MSG_DATA_HEADER) );

	//表示データ設定
	mdh_p->sw				= 1;
	mdh_p->seq				= 0;
	mdh_p->wait				= wait;
	mdh_p->waitwork			= 0;
	mdh_p->scrwork			= 0;
	mdh_p->callback_cont_flag = 0;
	for( i=0; i<MDH_WORKSIZE; i++){
		mdh_p->userwork[i]	= 0;
	}
	mdh_p->mph				= *mph_p;
	mdh_p->mph.msg = STRBUF_GetStringCodePointer(mdh_p->mph.strbuf);
	mdh_p->call_back		= call_back;
	msg_main_pause = 0;

	DispIconInit( mdh_p );

	// １文字ごとにウェイトを持たせた描画（タスク処理）
	if((wait != MSG_NO_PUT)&&(wait != MSG_ALLPUT))
	{
		mdh_p->wait--;			//wait値補正(0～)
		mdh_p->wait_flg = 1;
		mdh_p->msg_index = SetNewPrintTask(GF_MSG_PrintMain, mdh_p, 1);
		return mdh_p->msg_index;
	}
	// 一括描画
	else
	{
		u32 error_check;

		mdh_p->wait= 0;
		mdh_p->wait_flg = 0;
		error_check = 0;	//とりあえず気休め程度に
		FntDataColorSet(mph_p->f_col, mph_p->b_col, mph_p->s_col);

		while(error_check < 1024){
			//文字描画(一括)
			if(GF_MSG_PrintDataSet( mdh_p ) == PRINT_RESULT_END){
				break;
			}
			error_check++;
		}

		if(wait != MSG_NO_PUT){
			//ディスプレイ転送(キャラクタ一括)
			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );
		}

		DispIconExit( mdh_p );
		sys_FreeMemoryEz( mdh_p );
		return PRINTTASK_MAX;
	}
}






//---------------------------------------------------------------------------------------------
/**
 *	文字表示メイン関数
 *
 * @param	なし
 *
 * @retval	なし
 */
//---------------------------------------------------------------------------------------------
static void GF_MSG_PrintMain( TCB_PTR tcb, void *work )
{
	MSG_DATA_HEADER * mdh_p;
	PRINT_RESULT	result;

	if(msg_main_pause){	return; }		// メイン中断

	mdh_p = (MSG_DATA_HEADER *)work;

	if( mdh_p->callback_cont_flag == FALSE )
	{

		mdh_p->callback_arg = 0;
		FntDataColorSet(mdh_p->mph.f_col, mdh_p->mph.b_col, mdh_p->mph.s_col);

		//フォントデータ取得
		result = GF_MSG_PrintDataSet( mdh_p );

		//フォントデータ取得関数返り値による処理分岐
		switch( result ){
		case PRINT_RESULT_WRITE:
			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );

		case PRINT_RESULT_COMMAND:
			//文字描画ごとのコールバック関数呼び出し
			if(mdh_p->call_back != NULL){
				mdh_p->callback_cont_flag = (mdh_p->call_back)( &(mdh_p->mph), mdh_p->callback_arg );
			}
			break;

		case PRINT_RESULT_END:
			DeletePrintTask( mdh_p->msg_index );
			break;
		}
	}
	else
	{
		mdh_p->callback_cont_flag = (mdh_p->call_back)( &(mdh_p->mph), mdh_p->callback_arg );
	}
}

//---------------------------------------------------------------------------------------------
/*
 *	文字データ取得
 */
//---------------------------------------------------------------------------------------------
static PRINT_RESULT GF_MSG_PrintDataSet( MSG_DATA_HEADER * mdh_p )
{
	PRINT_RESULT  res;

	//各種フォントシステムプログラムの呼び出し(コード判定)
	do{
		res = FontDataPrint( mdh_p->mph.fnt_index, mdh_p );

	}while(res == PRINT_RESULT_LOOP);

	return res;
}





















//---------------------------------------------------------------------------------------------
/*
 *	FntDataSet8x8_2bit を呼ぶ前に、色番号をセットしておく（高速化のため）
 *
 * @param	col_f	文字色番号
 * @param	col_b	背景色番号
 * @param	col_s	影色番号
 */
//---------------------------------------------------------------------------------------------
#define DOTTBL_USE

#ifdef DOTTBL_USE
static u16 DotTbl[256];
#else
static u16 Col_b4, Col_b8, Col_b12;
static u16 Col_f4, Col_f8, Col_f12;
static u16 Col_s4, Col_s8, Col_s12;
#endif
static u16 Col_b, Col_f, Col_s;

void FntDataColorSet(u8 col_f, u8 col_b, u8 col_s)
{
#ifdef DOTTBL_USE
	int d1,d2,d3,d4,n;
	u32 col[4];

	col[0] = 0;
	col[1] = col_f;
	col[2] = col_s;
	col[3] = col_b;

	Col_b = col_b;
	Col_f = col_f;
	Col_s = col_s;

	n = 0;
	for(d1=0; d1<4; d1++){
		for(d2=0; d2<4; d2++){
			for(d3=0; d3<4; d3++){
				for(d4=0; d4<4; d4++){
					DotTbl[n++] =	(col[d4]<<12) | 
									(col[d3]<<8) |
									(col[d2]<<4) |
									(col[d1]);
				}
			}
		}
	}

#else
	Col_b = col_b;
	Col_f = col_f;
	Col_s = col_s;

	Col_b4 = col_b << 4;
	Col_b8 = col_b << 8;
	Col_b12 = col_b << 12;

	Col_f4 = col_f << 4;
	Col_f8 = col_f << 8;
	Col_f12 = col_f << 12;

	Col_s4 = col_s << 4;
	Col_s8 = col_s << 8;
	Col_s12 = col_s << 12;
#endif
}

void FntDataColorBackUp(u8* col_f, u8* col_b, u8* col_s)
{
	*col_b = Col_b; 
	*col_f = Col_f;
	*col_s = Col_s;
}

void FntDataColorRecover(u8* col_f, u8* col_b, u8* col_s)
{
	FntDataColorSet(*col_f,*col_b,*col_s);
}

//---------------------------------------------------------------------------------------------
/*
 *	文字データ設定
 *
 * @param	radrs		読み込みデータ開始アドレス
 * @param	wadrs		書き込みデータバッファアドレス
 *
 * @retval	x_size		文字Ｘサイズ(文字詰め用)
 */
//---------------------------------------------------------------------------------------------
#include "gflib\apptimer.h"
void FntDataSet8x8_2bit(u32 radrs,u32 wadrs)
{
	u32 dat;
	u16 *src;
	u16 *dst;

	src = (u16*)radrs;
	dst = (u16*)wadrs;


	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src++) << 24) >> 24;
	*dst++ = DotTbl[ dat ];

	dat = (u32)(*src) >> 8;
	*dst++ = DotTbl[ dat ];
	dat = (u32)((*src) << 24) >> 24;
	*dst = DotTbl[ dat ];

}
//---------------------------------------------------------------------------------------------
/*
 *	FntDataColorSet で設定した色番号を取得
 *
 * @param	mode	モード（enum COLOR_GET_MODE : msg_print.h）
 *
 * @retval	色番号
 */
//---------------------------------------------------------------------------------------------
u8 FntDataColorGet(u8 mode)
{
	switch(mode){
	case  COLOR_F: return Col_f;
	case  COLOR_B: return Col_b;
	case  COLOR_S: return Col_s;
	}
	return 0;
}











static void DispIconInit(MSG_DATA_HEADER* mdh)
{
	mdh->disp_icon = NULL;
}

static u8 * DispIconCreate(void)
{
	NNSG2dCharacterData * dat;
	void * arc;
	u8 * icon;

	icon = sys_AllocMemory( HEAPID_BASE_SYSTEM, 3*4 * 4 * 0x20 );
	arc  = ArcUtil_CharDataGet( ARC_FONT, NARC_font_dis_change_ncgr, 0, &dat, HEAPID_BASE_SYSTEM );
	MI_CpuCopy32( dat->pRawData, icon, 3*4 * 4 * 0x20 );
	sys_FreeMemoryEz( arc );

	return icon;
}

void GF_MSG_PrintDispIcon( MSG_DATA_HEADER * mdh, u16 px, u16 py, u16 pat )
{
	GF_BGL_BMPWIN * win = mdh->mph.bmpwin;
	u8 * iconcgx;

	if(mdh->disp_icon == NULL)
	{
		mdh->disp_icon = DispIconCreate();
	}

	iconcgx = mdh->disp_icon;
	iconcgx = &iconcgx[pat*12*0x20];

	px = ( GF_BGL_BmpWinGet_SizeX( win ) - 3 ) * 8;
	py = 0;
	GF_BGL_BmpWinPrint( win, iconcgx, 0, 0, 24, 32, px, py, 24, 32 );
}

static void DispIconExit( MSG_DATA_HEADER* mdh )
{
	if( mdh->disp_icon )
	{
		sys_FreeMemoryEz( mdh->disp_icon );
		mdh->disp_icon = NULL;
	}
}
