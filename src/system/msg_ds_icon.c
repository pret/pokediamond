//============================================================================================
/**
 * @file	msg_ds_icon.c
 * @brief	画面注目アイコン処理
 * @author	Hiroyuki Nakamura
 * @date	2006.02.22
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/lib_pack.h"

#define	MSG_DS_ICON_H_GLOBAL
#include "system/msg_ds_icon.h"


//============================================================================================
//	定数定義
//============================================================================================
typedef void (*dsiFunc)(void*,u16*);	// 関数ポインタ型

// アイコン制御ワーク
typedef struct {
	TCB_PTR tcb;			// TCB
	dsiFunc func;			// パレット転送関数ポインタ
	PALETTE_FADE_PTR pfd;	// パレットフェードワーク
	u16	def_pal[16];		// 初期パレット
	u16	tmp_pal[16];		// 転送パレット
	u8	disp;				// 書き換え画面
	u8	pal;				// パレット番号
	u8	seq;				// シーケンス
	u8	cnt;				// カウンタ
}DSI_WORK;

// 処理シーケンス
enum {
	SEQ_START = 0,	// 開始
	SEQ_DRAW,		// 転送
	SEQ_STOP,		// 停止
	SEQ_FREE,		// 解放
};

#define	BACK_COL_POS	( 15 )		// 背景カラーの位置
#define	CHG_PLTT_POS	( 0x7800 )	// 書き換えカラー位置( 下位から0,1,2,...15 )
#define	CHG_COUNT_MAX	( 32 )		// カウント最大
#define	NO_PUT_COUNT	( 24 )		// 非表示カウント


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void PaletteCangeTask( TCB_PTR tcb, void * work );
static u8 PalettePut( DSI_WORK * wk );
static void DsiFuncVram_M( void * work, u16 * pal );
static void DsiFuncVram_S( void * work, u16 * pal );
static void DsiFuncWork_M( void * work, u16 * pal );
static void DsiFuncWork_S( void * work, u16 * pal );


//--------------------------------------------------------------------------------------------
/**
 * アイコン点滅タスクセット
 *
 * @param	pfd		パレットフェードデータ( NULLの場合、VRAMに直接書き込む )
 * @param	disp	転送画面
 * @param	pal		パレット番号
 * @param	heap	ヒープID
 *
 * @return	タスクワーク
 */
//--------------------------------------------------------------------------------------------
void * MSG_DsIconFlashAdd( PALETTE_FADE_PTR pfd, u16 disp, u16 pal, u32 heap )
{
	DSI_WORK * wk;
	TCB_PTR	tcb;
	u16 * pltt;

	tcb = PMDS_taskAdd( PaletteCangeTask, sizeof(DSI_WORK), 0, heap );
	wk  = (DSI_WORK *)TCB_GetWork( tcb );

	if( pfd != NULL ){
		if( disp == MSG_DSI_MAINDISP ){
			pltt = PaletteWorkDefaultWorkGet( pfd, FADE_MAIN_BG );
			wk->func = DsiFuncWork_M;
		}else{
			pltt = PaletteWorkDefaultWorkGet( pfd, FADE_SUB_BG );
			wk->func = DsiFuncWork_S;
		}
	}else{
		if( disp == MSG_DSI_MAINDISP ){
			pltt = (u16 *)GF_MMAP_MainBgPlttAddr();
			wk->func = DsiFuncVram_M;
		}else{
			pltt = (u16 *)GF_MMAP_SubBgPlttAddr();
			wk->func = DsiFuncVram_S;
		}
	}
	MI_CpuCopy16( &pltt[pal*16], wk->def_pal, 0x20 );
	MI_CpuCopy16( &pltt[pal*16], wk->tmp_pal, 0x20 );
	wk->tcb  = tcb;
	wk->pfd  = pfd;
	wk->disp = disp;
	wk->pal  = pal;
	wk->seq  = SEQ_DRAW;
	wk->cnt  = 0;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * タスクのシーケンスを外部コントロール
 *
 * @param	work	タスクワーク
 * @param	req		リクエスト
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MSG_DsIconFlashReq( void * work, u8 req )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	switch( req ){
	case MSG_DSI_REQ_START:
		wk->seq = SEQ_START;
		break;
	case MSG_DSI_REQ_STOP:
		wk->seq = SEQ_STOP;
		break;
	case MSG_DSI_REQ_FREE:
		wk->seq = SEQ_FREE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * タスクを外部から削除
 *
 * @param	work	タスクワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MSG_DsIconFlashDelete( void * work )
{
	DSI_WORK * wk = (DSI_WORK *)work;
	PMDS_taskDel( wk->tcb );
}

//--------------------------------------------------------------------------------------------
/**
 * メインタスク
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteCangeTask( TCB_PTR tcb, void * work )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	switch( wk->seq ){
	case SEQ_START:
		wk->cnt = 0;
		wk->seq = SEQ_DRAW;
		break;

	case SEQ_DRAW:
		if( PalettePut( wk ) == TRUE ){
			wk->func( wk, wk->tmp_pal );
		}
		wk->cnt++;
		if( wk->cnt == CHG_COUNT_MAX ){
			wk->cnt = 0;
		}
		break;

	case SEQ_STOP:
		break;

	case SEQ_FREE:
		wk->func( wk, wk->def_pal );
		PMDS_taskDel( tcb );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレットワーク書き換え
 *
 * @param	wk		ワーク
 *
 * @retval	"TRUE = 変更した"
 * @retval	"FALSE = 変更してない"
 */
//--------------------------------------------------------------------------------------------
static u8 PalettePut( DSI_WORK * wk )
{
	u32	i;

	if( wk->cnt == 0 ){
		for( i=0; i<16; i++ ){
			if( ( CHG_PLTT_POS & (1<<i) ) == 0 ){
				continue;
			}
			wk->tmp_pal[i] = wk->def_pal[i];
		}
		return TRUE;
	}else if( wk->cnt == NO_PUT_COUNT ){
		for( i=0; i<16; i++ ){
			if( ( CHG_PLTT_POS & (1<<i) ) == 0 ){
				continue;
			}
			wk->tmp_pal[i] = wk->def_pal[BACK_COL_POS];
		}
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * パレット転送
 *
 * @param	work	ワーク
 * @aram	pal		転送パレットデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DsiFuncVram_M( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	GF_BGL_PaletteSet( GF_BGL_FRAME0_M, pal, 0x20, wk->pal*0x20 );
}

static void DsiFuncVram_S( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	GF_BGL_PaletteSet( GF_BGL_FRAME0_S, pal, 0x20, wk->pal*0x20 );
}

static void DsiFuncWork_M( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	PaletteWorkSet( wk->pfd, pal, FADE_MAIN_BG, wk->pal*16, 0x20 );
}

static void DsiFuncWork_S( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	PaletteWorkSet( wk->pfd, pal, FADE_SUB_BG, wk->pal*16, 0x20 );
}
