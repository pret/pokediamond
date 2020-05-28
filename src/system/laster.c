//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		laster.c
 *	@brief		ラスターシステム
 *	@author		tomoya takahashi
 *	@data		2005.12.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "system/tcbman.h"

#define __LASTER_H_GLOBAL
#include "system/laster.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ラスターシステム構造体
//	
//=====================================
typedef struct _LASTER_SYS{
	// ラスターデータバッファ
	void* laster_buff[2];

	// ラスターデータの書き込み用バッファ指定フラグ
	u8	write_buff;	// 配列要素数を指定します (0 or 1)

	// バッファスイッチフラグ
	u8	switch_flag;	
/* 	LASTER_SWITCH_ON,	// バッファスイッチ有効
 	LASTER_SWITCH_OFF	// バッファスイッチ無効*/
	u8 dummy[2];

} LASTER_SYS;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスターシステム初期化
 *
 *	@param	heap	使用するヒープ
 *	@param	p_buff1	バッファ１
 *	@param	p_buff2	バッファ２
 *
 *	@return	作成したラスターシステム
 *
 */
//-----------------------------------------------------------------------------
LASTER_SYS_PTR LASTER_Init( int heap, void* p_buff1, void* p_buff2 )
{
	LASTER_SYS_PTR p_laster;

	p_laster = sys_AllocMemory( heap, sizeof(LASTER_SYS) );
	memset( p_laster, 0, sizeof(LASTER_SYS) );

	// スイッチ処理ON
	p_laster->switch_flag = LASTER_SWITCH_ON;

	// スイッチバッファ格納
	p_laster->laster_buff[ 0 ] = p_buff1;
	p_laster->laster_buff[ 1 ] = p_buff2;

	return p_laster;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスターシステム破棄
 *
 *	@param	lster	破棄するラスターシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_Delete( LASTER_SYS_PTR p_laster )
{
	GF_ASSERT( p_laster );

	sys_FreeMemoryEz( p_laster );
	p_laster = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	書き込み用ラスターバッファを取得
 *
 *	@param	cp_laster	ラスタースステム
 *
 *	@return	書き込み用ラスターバッファ
 *
 *
 */
//-----------------------------------------------------------------------------
void* LASTER_GetWriteBuff( CONST_LASTER_SYS_PTR cp_laster )
{
	GF_ASSERT( cp_laster );
	
	return cp_laster->laster_buff[ cp_laster->write_buff ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	参照用ラスターバッファを取得
 *
 *	@param	cp_laster	ラスターシステム
 *
 *	@return	参照用ラスターバッファ
 *
 *
 */
//-----------------------------------------------------------------------------
const void* LASTER_GetReadBuff( CONST_LASTER_SYS_PTR cp_laster )
{
	GF_ASSERT( cp_laster );
	
	return cp_laster->laster_buff[ cp_laster->write_buff ^ 1 ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	バッファスイッチフラグを設定します。
 *
 *	@param	p_laster	ラスターシステム
 *	@param	switch_flag	スイッチフラグ
 *
 *	@return	none
 *
 * switch_flag	
 *	LASTER_SWITCH_ON,	// バッファスイッチ有効
 *	LASTER_SWITCH_OFF	// バッファスイッチ無効
 *
 *	LASTERE_Init関数を呼んだ状態でバッファスイッチは有効になっています。
 * 
 */
//-----------------------------------------------------------------------------
void LASTER_SwitchFlagSet( LASTER_SYS_PTR p_laster, u8 switch_flag )
{
	GF_ASSERT( p_laster );
	
	p_laster->switch_flag = switch_flag;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター　Vブランク関数
 *
 *	@param	p_laster	ラスターシステム
 *
 *	@return	none
 *
 * バッファスイッチフラグが有効のとき
 *		書き込み用バッファを参照用に
 *		参照用バッファを書き込み用に　変更します。
 *
 *		変更後　新しく書き込みようになったバッファを０で初期化します。
 *
 */
//-----------------------------------------------------------------------------
void LASTER_VBlank( LASTER_SYS_PTR p_laster )
{
	if( p_laster == NULL ){
		return ;
	}
	
	// バッファスイッチ有効チェック
	if( p_laster->switch_flag == LASTER_SWITCH_OFF ){
		return ;
	}

	// ラスターバッファスイッチ
	p_laster->write_buff ^= 1;
}



//-----------------------------------------------------------------------------
/**
 *
 *		ラスターHブランクDMA転送関数
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスターで使用するDMAを停止する
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_DmaStop( void )
{
	MI_StopDma( LASTER_USE_DMA );
	MI_WaitDma( LASTER_USE_DMA );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	HブランクDMA転送パラメータ設定
 *
 *	@param	p_src		転送元
 *	@param	p_dest		転送先
 *	@param	szbyte		転送サイズ	（１回の転送で転送するサイズ）
 *	@param	dma_type
 *
 *	@return	none
 *
 *	LASTER_DMA_TYPE16,	16bit単位
 *	LASTER_DMA_TYPE32	32bit単位
 *
 */
//-----------------------------------------------------------------------------
void LASTER_DmaSet( const void* p_src, void* p_dest, int szbyte, int dma_type )
{
	
	// 転送タイプチェック
	if( dma_type == LASTER_DMA_TYPE32 ){
		MI_HBlankDmaCopy32( LASTER_USE_DMA, p_src, p_dest, szbyte );
	}else{
		MI_HBlankDmaCopy16( LASTER_USE_DMA, p_src, p_dest, szbyte );
	}
}


//-----------------------------------------------------------------------------
/**
 *		ラスタースクロール
 *			DMA転送使用
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ラスタースクロールワーク
//	
//=====================================
typedef struct _LASTER_SCROLL{
	// ラスターバッファ
	u32	buff1[ LASTER_SCROLL_BUFF_SIZE ];
	u32 buff2[ LASTER_SCROLL_BUFF_SIZE ];

	LASTER_SYS_PTR p_laster;	// ラスターシステム
	TCB_PTR	p_tcb;				// tcbワーク
	BOOL	end_flag;			// 終了フラグ


	// サインカーブテーブル
	s16 sinTbl[ LASTER_SCROLL_BUFF_SIZE ];

	u8 start;	// スクロール反映開始Y座標
	u8 end;		// スクロール反映終了Y座標
	
	u32	addr;		// DMA転送先
	u32	init_num;	// ワークを初期化する値
	
	s16 scr_now;	// スロール現在位置
	s16 scr_sp;	// スクロールスピード	整数*100 された数

} LASTER_SCROLL;

// DMA転送RAPPER
static void LASTER_ScrollDmaStop( void );
static void LASTER_ScrollDmaSet( CONST_LASTER_SCROLL_PTR cp_lstscr );


// ラスター用
static void LASTER_ScrollTcb( TCB_PTR tcb, void* work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロールオブジェ生成
 *
 *	@param	heap	ヒープ
 *
 *	@return	作成したラスタースクロールオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
LASTER_SCROLL_PTR LASTER_ScrollInit( int heap )
{
	LASTER_SCROLL_PTR p_lstscr;

	// オブジェクト生成
	p_lstscr = sys_AllocMemory( heap, sizeof(LASTER_SCROLL) );
	memset( p_lstscr, 0, sizeof(LASTER_SCROLL) );
	
	// ラスターシステム生成
	p_lstscr->p_laster = LASTER_Init( heap, p_lstscr->buff1, p_lstscr->buff2 );

	return p_lstscr;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロール開始
 *
 *	@param	start		ラスタースクロールさせる開始ｙ座標
 *	@param	end			ラスタースクロールさせる終了ｙ座標
 *	@param	add_r		sinカーブテーブル作成時の角度を足していく値(0～65535)
 *	@param	r_w			sinカーブの半径
 *	@param	scr_sp		ラスタースクロールスピード	整数*100した値	マイナス有効
 *	@param	bg_no		ラスターをかけるBGの番号
 *	@param	init_num	ワークを初期化する値
 *	@param	tsk_pri		タスク優先順位
 *
 *	@return	none
 *
 * bg_no
 * 		LASTER_SCROLL_MBG0,
 *		LASTER_SCROLL_MBG1,
 *		LASTER_SCROLL_MBG2,
 *		LASTER_SCROLL_MBG3,
 *		LASTER_SCROLL_SBG0,
 *		LASTER_SCROLL_SBG1,
 *		LASTER_SCROLL_SBG2,
 *		LASTER_SCROLL_SBG3
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollStart( LASTER_SCROLL_PTR p_lstscr, u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 init_num, u32 tsk_pri )
{
	GF_ASSERT( p_lstscr );
	GF_ASSERT_MSG( p_lstscr->p_tcb == NULL, "tcb登録済みです." );

	// 動作パラメータ設定
	p_lstscr->start		= start;
	p_lstscr->end		= end;
	p_lstscr->scr_now	= 0;
	p_lstscr->scr_sp	= scr_sp;
	p_lstscr->addr		= bg_no;
	p_lstscr->init_num	= init_num;

	// sinカーブ作成
	LASTER_ScrollMakeSinTbl( p_lstscr->sinTbl, LASTER_SCROLL_BUFF_SIZE, add_r, r_w );

	// tcb登録
	p_lstscr->p_tcb = TCB_Add( LASTER_ScrollTcb, p_lstscr, tsk_pri );	

	// ワークを初期化
	MI_CpuFill32( p_lstscr->buff1, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	MI_CpuFill32( p_lstscr->buff2, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロール終了
 *
 *	@param	p_lstscr	終了させるラスタースクロールワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollEnd( LASTER_SCROLL_PTR p_lstscr )
{
	void* buff;
	
	GF_ASSERT( p_lstscr );
	
	if( p_lstscr->p_tcb ){
		// TCBの破棄
		TCB_Delete( p_lstscr->p_tcb );
		p_lstscr->p_tcb = NULL;

		// 次に開始するときのために
		// 書き込み用バッファの初期化
		buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
		memset( buff, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロール破棄
 *
 *	@param	p_lstscr	ラスタースクロールワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDelete( LASTER_SCROLL_PTR p_lstscr )
{
	// タスク終了
	LASTER_ScrollEnd( p_lstscr );

	// DMA終了
	LASTER_ScrollDmaStop();
	
	// ラスターシステム破棄
	LASTER_Delete( p_lstscr->p_laster );

	// 全データ破棄
	sys_FreeMemoryEz( p_lstscr );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	バッファ取得
 *
 *	@param	p_lstscr	ラスタースクロールワーク
 *
 *	@return	バッファポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
void* LASTER_GetScrollWriteBuff( LASTER_SCROLL_PTR p_lstscr )
{
	return LASTER_GetWriteBuff( p_lstscr->p_laster );
}
const void* LASTER_GetScrollReadBuff( LASTER_SCROLL_PTR p_lstscr )
{
	return LASTER_GetReadBuff( p_lstscr->p_laster );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロールVブランク関数
 *
 *	@param	p_lstscr	ラスタースクロールワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
//	バッファスイッチ
void LASTER_ScrollVBuffSwitch( LASTER_SCROLL_PTR p_lstscr )
{
	void* buff;
	
	if( p_lstscr == NULL ){
		return ;
	}
	
	// タスクが動いているとき
	// ダブルバッファリングの実行
	if( p_lstscr->p_tcb ){
		// ラスターシステムVBlank関数実行
		LASTER_VBlank( p_lstscr->p_laster );

		// ワークを初期化
		buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
		MI_CpuFill32( buff, p_lstscr->init_num, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	}
}

// DMA設定
void LASTER_ScrollVDma( LASTER_SCROLL_PTR p_lstscr )
{
	if( p_lstscr == NULL ){
		return ;
	}
	
	// タスクが動いているとき
	// HブランクDMAの設定
	if( p_lstscr->p_tcb ){

		// DMA停止
		LASTER_ScrollDmaStop();
		// DMA転送設定
		LASTER_ScrollDmaSet( p_lstscr );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロールサインテーブル作成
 *
 *	@param	sinTbl	サインテーブル
 *	@param	num		配列要素数	u16 buff[ 10 ]; なら10を指定
 *	@param	add_r	回転角の増分値
 *	@param	r_w		半径幅
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollMakeSinTbl( s16* sinTbl, u32 num, u16 add_r, fx32 r_w )
{
	int i;	// ループ用
	u16 rota;

	// バッファサイズ分add_rずつ進めたsinカーブを
	// バッファに格納
	rota = 0;
	for( i=0; i<num; i++ ){
		sinTbl[ i ] = FX_Mul( FX_SinIdx( rota ), r_w) >> FX32_SHIFT;
		rota += add_r;	// 0～65535をループ
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スクロール計算TCB
 *
 *	@param	tcb		tcbワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void LASTER_ScrollTcb( TCB_PTR tcb, void* work )
{
	LASTER_SCROLL_PTR p_lstscr = work;
	int i;			// ループ用
	u32* w_buff;	// 書き込み用バッファ
	u8 write;		// 書き込み要素数
	s16	mat_x;		// x座標
	u16 mat_y;		// y座標

	// 書き込み用バッファ取得
	w_buff = LASTER_GetWriteBuff( p_lstscr->p_laster );
	
	// バッファにデータを設定
	write = p_lstscr->scr_now / 100;
	for( i=p_lstscr->start; i<=p_lstscr->end; i++ ){
		// 今の値取得
		mat_x = w_buff[ i ] & 0xffff;
		mat_y = w_buff[ i ] >> 16;
		
		// サインカーブ反映
		mat_x += p_lstscr->sinTbl[ write ];
		
		// 値設定
		w_buff[ i ] = (mat_y << 16) | (mat_x & 0xffff);
		
		write = (write + 1) % LASTER_SCROLL_BUFF_SIZE;
	}

	// スクロール位置計算
	p_lstscr->scr_now += p_lstscr->scr_sp;
	if( p_lstscr->scr_now >= (LASTER_SCROLL_BUFF_SIZE * 100) ){
		p_lstscr->scr_now %= (LASTER_SCROLL_BUFF_SIZE * 100);
	}else{
		if( p_lstscr->scr_now < 0 ){
			p_lstscr->scr_now += (LASTER_SCROLL_BUFF_SIZE * 100);
		}
	}
}

// DMA転送RAPPER
//----------------------------------------------------------------------------
/**
 *
 *	@brief	DMA転送終了
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDmaStop( void )
{
	LASTER_DmaStop();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	HブランクDMA転送設定
 *
 *	@param	cp_lstscr	ラスタースクロールワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void LASTER_ScrollDmaSet( CONST_LASTER_SCROLL_PTR cp_lstscr )
{
	const void* buff;

	GF_ASSERT( cp_lstscr );
	
	// 参照用バッファ取得
	buff = LASTER_GetReadBuff( cp_lstscr->p_laster );

	// フラッシュレンジ
	DC_FlushRange( buff, sizeof(u32) * LASTER_SCROLL_BUFF_SIZE );
	
	// HBlankDMA転送に設定
	LASTER_DmaSet( buff, (void*)cp_lstscr->addr, sizeof(u32), LASTER_DMA_TYPE32 );
}
