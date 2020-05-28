//============================================================================================
/**
 * @file	poketch_a05c.c
 * @bfief	ポケッチ（アプリNoa05：ドットアート）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "gflib\touchpanel.h"

#include "poketch_a05.h"
#include "poketch_prv.h"

//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;
	u8        quit_req_flag;

	u32       prev_x;
	u32       prev_y;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	u8	loadBuf[ POKETCH_DOTART_DATA_BYTESIZE ];

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_IDLE,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A05_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void InitVparam( APPWORK* wk, VIEWPARAM* vpara );
static inline u8 GetDotBit( const u8* buf, int p );
static inline void SetDotBit( u8* buf, int p, int dot );
static void dotData_load( APPWORK* wk, VIEWPARAM* vpara, POKETCH_DATA* pdat );
static void dotData_save( APPWORK* wk, VIEWPARAM* vpara, POKETCH_DATA* pdat );
static void dotData_initialize( VIEWPARAM* vpara );
static void CleanupWork( APPWORK *wk );
static void A05_DataSaveProc( void* wk_adrs );
static void Poketch_A05_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A05_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A05_Init, Poketch_A05_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 * @param   conwk		アプリが本体から情報を取得する際に必要となるワーク（アプリへは非公開）
 * @param   bgl			BGLモジュールヘッダ
 * @param   param		カラー・モノクロなど動作タイプ（アプリ依存）
 */
//------------------------------------------------------------------
static BOOL Poketch_A05_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A05_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				PoketchSetAppSaveProc( A05_DataSaveProc, wk );
				return TRUE;
			}
		}
		sys_FreeMemoryEz( wk );
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワークのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param )
{
	wk->conwk = conwk;
	InitVparam( wk, &(wk->vpara) );

	if( Poketch_A05_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->prev_x = FIELD_WIDTH+1;
		wk->prev_y = FIELD_HEIGHT+1;

		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 描画パラメータの初期化
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void InitVparam( APPWORK* wk, VIEWPARAM* vpara )
{
	POKETCH_DATA* pdat = PoketchGetSaveData(wk->conwk);
	if( PoketchData_DotArt_GetModifiedFlag( pdat ) )
	{
		dotData_load( wk, vpara, pdat );
	}
	else
	{
		dotData_initialize( vpara );
	}
}



static inline u8 GetDotBit( const u8* buf, int p )
{
	return ((buf[ (p/4) ] >> ((p&3)*2)) & 3);
}
static inline void SetDotBit( u8* buf, int p, int dot )
{
	buf[ (p/4) ] |= ((dot&3) << ((p&3)*2));
}


static void dotData_load( APPWORK* wk, VIEWPARAM* vpara, POKETCH_DATA* pdat )
{
	int x, y, p;

	PoketchData_DotArt_GetBitData( pdat, wk->loadBuf );

	p = 0;
	for(y=0; y<FIELD_HEIGHT; y++)
	{
		for(x=0; x<FIELD_WIDTH; x++)
		{
			vpara->dot[y][x] = GetDotBit( wk->loadBuf, p++ ) + 1;
		}
	}
}

static void dotData_save( APPWORK* wk, VIEWPARAM* vpara, POKETCH_DATA* pdat )
{
	int x, y, p;

	MI_CpuClear8( wk->loadBuf, POKETCH_DOTART_DATA_BYTESIZE );

	p = 0;
	for(y=0; y<FIELD_HEIGHT; y++)
	{
		for(x=0; x<FIELD_WIDTH; x++)
		{
			SetDotBit( wk->loadBuf, p++, vpara->dot[y][x]-1 );
		}
	}

	PoketchData_DotArt_SetBitData( pdat, wk->loadBuf );
}


static void dotData_initialize( VIEWPARAM* vpara )
{
	static const u8 FieldInitializeTable[FIELD_HEIGHT][FIELD_WIDTH] = {
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1, },
		{ 1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1, },
		{ 1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,4,1, },
		{ 1,1,1,4,1,1,4,4,4,1,4,1,4,1,4,4,4,1,4,4,4,1,4,1, },
		{ 1,1,1,4,1,1,4,1,4,1,4,1,4,1,4,1,1,1,4,1,4,1,1,1, },
		{ 1,1,1,4,1,1,4,4,4,1,4,4,4,1,4,4,4,1,4,1,4,1,4,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
	};

	int x, y;

	for(y=0; y<FIELD_HEIGHT; y++)
	{
		for(x=0; x<FIELD_WIDTH; x++)
		{
			vpara->dot[y][x] = FieldInitializeTable[y][x];
		}
	}
}


//------------------------------------------------------------------
/**
 * ワークのクリーンアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CleanupWork( APPWORK *wk )
{
	dotData_save( wk, &wk->vpara, PoketchGetSaveData(wk->conwk) );

	Poketch_A05_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}

//------------------------------------------------------------------
/**
 * フィールドでのセーブ時に呼び出される
 *
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void A05_DataSaveProc( void* wk_adrs )
{
	APPWORK* wk = wk_adrs;
	dotData_save( wk, &wk->vpara, PoketchGetSaveData(wk->conwk) );
}

//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A05_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		if( seqtbl[wk->main_seq](wk) )
		{
			CleanupWork( wk );
			TCB_Delete(tcb);
			PoketchNoticeAppEnd( wk->conwk );
		}
	}
	else
	{
		SDK_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * アプリ終了関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A05_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
}

//------------------------------------------------------------------
/**
 * シーケンス変更
 *
 * @param   wk		ワークポインタ
 * @param   seq		変更後のシーケンスナンバー
 *
 */
//------------------------------------------------------------------
static void ChangeSeq(APPWORK *wk, u32 seq)
{
	if(wk->quit_req_flag == FALSE)
	{
		wk->main_seq = seq;
	}
	else
	{
		wk->main_seq = SEQ_QUIT;
	}
	wk->seq = 0;
}


//------------------------------------------------------------------
/**
 * シーケンス：画面構築
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A05_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A05_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_IDLE );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：入力待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if(Poketch_A05_WaitViewCommand( wk->vwk, CMD_FIELD_UPDATE ))
	{
		u32 x, y;
		if( PoketchGetTPCont(&x, &y) )
		{
			if(x >= FIELD_XORG_PIXEL && y >= FIELD_YORG_PIXEL )
			{
				x = (x - FIELD_XORG_PIXEL) / 8;
				y = (y - FIELD_YORG_PIXEL) / 8;

				if( x < FIELD_WIDTH && y < FIELD_HEIGHT )
				{
					if( (wk->prev_x!=x || wk->prev_y!=y)
					||	(GF_TP_GetTrg()==TRUE)
					){
						wk->vpara.dot[y][x]++;
						if( wk->vpara.dot[y][x] > 4 )
						{
							wk->vpara.dot[y][x] = 1;
						}
						wk->prev_x = x;
						wk->prev_y = y;
						Poketch_A05_SetViewCommand( wk->vwk, CMD_FIELD_UPDATE );
					}
				}
			}
		}
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：終了処理
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqQuit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A05_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A05_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
