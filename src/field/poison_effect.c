//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		poison_effect.c
 *	@brief		毒ｴﾌｪｸﾄ
 *	@author		tomoya takahashi
 *	@data		2006.04.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "include/system/laster.h"
#include "include/system/snd_tool.h"

#define	__POISON_EFFECT_H_GLOBAL
#include "poison_effect.h"

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
#define POISON_COUNT		( 3 )		// 動作ｶｳﾝﾀ

#ifdef PM_DEBUG
static int POISON2_X = (3);	// この値分ずらす
static int POISON2_Y = (10);	// これい１回方向をかえる
void DEBUG_Poison( void );
#else
#define POISON2_X (3)	// この値分ずらす
#define POISON2_Y (10)	// これい１回方向をかえる
#endif
//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ワーク	
//=====================================
typedef struct _POISON_EFFECT_WORK{
	u32		status;
	int		count;
	int		seq;
	u16		HblBuff0[ 192 ];
	u16		HblBuff1[ 192 ];
	LASTER_SYS_PTR p_laster;
	FIELD_HBLANK_SYS* p_hblanksys;
	FIELD_HBLANK_OBJ* p_hblank;
	BOOL	HblRef;		// HBLANKで値を設定するか
	TCB_PTR	do_tcb;
	TCB_PTR vblank_tcb;
	TCB_PTR vwaitblank_tcb;
} ;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void PoisonEffTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffVblankTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffVWaitblankTcb( TCB_PTR tcb, void* p_work );
static void PoisonEffHBlank( POISON_EFFECT_WORK* p_poison );
static void PoisonMakeBuff( u16* buff, int key, int key_max );
static void PoisonEffeHBlankCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work );
static void POISON_EFFE_HBlank( POISON_EFFECT_WORK* p_poison );
static void POISON_EFFE_VBlank( POISON_EFFECT_WORK* p_poison );
static void PoisonWorkDoEnd( POISON_EFFECT_WORK* p_poison );

//----------------------------------------------------------------------------
/**
 *	@brief	毒ｴﾌｪｸﾄワーク作成
 *
 *	@param	heap	ヒープ
 *	@param	p_sys	フィールドHブランク管理システム
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
POISON_EFFECT_WORK* POISON_EFFE_Init( u32 heap, FIELD_HBLANK_SYS* p_sys )
{
	POISON_EFFECT_WORK* p_poison;

	p_poison = sys_AllocMemory( heap, sizeof(POISON_EFFECT_WORK) );
	memset( p_poison, 0, sizeof(POISON_EFFECT_WORK) );

	// STANDBY状態
	p_poison->status = POISON_EFFE_STANDBY;

	// ラスターワーク作成
	p_poison->p_laster = LASTER_Init( heap, p_poison->HblBuff0, p_poison->HblBuff1 );

	// Hブランクシステムワーク保持
	p_poison->p_hblanksys = p_sys;

	return p_poison;
}

//----------------------------------------------------------------------------
/**
 *	@brief	毒ｴﾌｪｸﾄワーク破棄
 *
 *	@param	p_poison	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void POISON_EFFE_Delete( POISON_EFFECT_WORK* p_poison )
{
	// TCB破棄
	if( p_poison->status == POISON_EFFE_DO ){
		PoisonWorkDoEnd( p_poison );
	}

	// ラスター破棄
	LASTER_Delete( p_poison->p_laster );

	// メモリ破棄
	sys_FreeMemoryEz( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	毒ｴﾌｪｸﾄスタート
 *	
 *	@param	p_poison	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void POISON_EFFE_Start( POISON_EFFECT_WORK* p_poison )
{
	// 多重呼び出しチェック
	GF_ASSERT( p_poison->status == POISON_EFFE_STANDBY );

	// Hブランク	初期化
	p_poison->p_hblank = FLDHBLANK_OBJ_Add( p_poison->p_hblanksys, PoisonEffeHBlankCallBack, p_poison );
	
	// タスク呼び出し
	// バッファないデータ操作タスク
	p_poison->do_tcb = TCB_Add( PoisonEffTcb, p_poison, POISON_TCB_PRI );
	// バッファ反映スイッチタスク	Vブランク期間
	p_poison->vblank_tcb = VIntrTCB_Add( PoisonEffVblankTcb, p_poison, POISON_TCB_PRI );
	//	ダブルバッファスイッチ処理タスク	Vブランク期間終了後
	p_poison->vwaitblank_tcb = VIntrTCB_Add( PoisonEffVWaitblankTcb, p_poison, POISON_TCB_PRI );

	// 初期化
	memset( p_poison->HblBuff0, 0, sizeof(u16) * 192 );
	memset( p_poison->HblBuff1, 0, sizeof(u16) * 192 );
	p_poison->status = POISON_EFFE_DO;
	p_poison->seq = 0;

	// 音再生
	Snd_SePlay( SE_POISON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	毒ｴﾌｪｸﾄ状態取得
 *
 *	@param	cp_poison ワーク
 *
 *	@retval	POISON_EFFE_STANDBY		開始待ち
 *	@retval	POISON_EFFE_DO			実行中
 */         
//-----------------------------------------------------------------------------
u32 POISON_EFFE_GetStatus( const POISON_EFFECT_WORK* cp_poison )
{
	return cp_poison->status;
}


//----------------------------------------------------------------------------
/**
 *	@brief	タスクワーク
 *
 *	@param	tcb		TCBデータ
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* data = p_work;
	u16* buff;


	
	switch( data->seq ){
	case 0:		// 初期化
		data->count = POISON_COUNT;
		data->seq++;
		break;

	case 1:		// 減算
		data->count --;
		buff = LASTER_GetWriteBuff( data->p_laster );
		PoisonMakeBuff( buff, POISON_COUNT - data->count, POISON_COUNT );
		if( data->count <= 0 ){
			data->count = POISON_COUNT;
			data->seq++;
		}
		break;
	
	case 2:		// 加算
		data->count --;
		buff = LASTER_GetWriteBuff( data->p_laster );
		PoisonMakeBuff( buff, data->count, POISON_COUNT );
		if( data->count <= 0 ){
			data->seq++;
		}
		break;

	// 終了
	case 3:
		PoisonWorkDoEnd( data );
		// BG0面のH方向スクロール設定
		G3X_SetHOffset( 0 );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	HBlank処理
 *
 *	@param	p_poison ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffHBlank( POISON_EFFECT_WORK* p_poison )
{
	const u16* cp_buff;
	int count;
	count = GX_GetVCount();
	cp_buff = LASTER_GetReadBuff( p_poison->p_laster );
	if( count < 192 ){
		count++;	// 次の高さのデータを設定
		if( count >= 192 ){
			count -= 192;
		}
		
		// BG0面のH方向スクロール設定
		if( GX_IsHBlank() ){
			G3X_SetHOffset( cp_buff[ count ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	keyに対応した値をバッファに追加
 *
 *	@param	buff		バッファ
 *	@param	key			キー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonMakeBuff( u16* buff, int key, int key_max )
{
	int i;
	int calc_x;
	BOOL switch_f = TRUE;


	calc_x = POISON2_X * key;
	calc_x = calc_x / key_max;

	for( i=0; i<192; i++ ){

		if( (i % POISON2_Y) == 0 ){
			switch_f ^= 1;
		}

		if( switch_f ){
			buff[ i ] = calc_x;
		}else{
			buff[ i ] = -calc_x;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlankTCB
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffVblankTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* data = p_work;

	// この時点で1回反映させたので
	// 次の1シンクは反映させない
	data->HblRef = FALSE;

	// BG0面のH方向スクロール設定
	G3X_SetHOffset( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク処理
 *
 *	@param	p_obj		Hブランクオブジェクト
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffeHBlankCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work )
{
	POISON_EFFECT_WORK* p_poison = p_work;
	POISON_EFFE_HBlank( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク期間処理
 *
 *	@param	p_poison 毒ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void POISON_EFFE_HBlank( POISON_EFFECT_WORK* p_poison )
{
	if( p_poison->status == POISON_EFFE_DO ){

		// 反映を1シンクずつにする
		// 半透明っぽくなる効果を狙う
		if( p_poison->HblRef == TRUE ){
			PoisonEffHBlank( p_poison );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Vブランク待ち後タスク処理
 *
 *	@param	tcb		タスクワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonEffVWaitblankTcb( TCB_PTR tcb, void* p_work )
{
	POISON_EFFECT_WORK* p_poison = p_work;
	POISON_EFFE_VBlank( p_poison );
}
//----------------------------------------------------------------------------
/**
 *	@brief	Vブランク期間処理
 *
 *	@param	p_poison	毒ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void POISON_EFFE_VBlank( POISON_EFFECT_WORK* p_poison )
{
	if( p_poison->status == POISON_EFFE_DO ){
		LASTER_VBlank( p_poison->p_laster );
		p_poison->HblRef = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	毒ｴﾌｪｸﾄ実行状態クリア
 *
 *	@param	p_poison	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PoisonWorkDoEnd( POISON_EFFECT_WORK* p_poison )
{
	// Hブランク処理破棄
	FLDHBLANK_OBJ_Delete( p_poison->p_hblank );
	p_poison->p_hblank = NULL;
	
	TCB_Delete( p_poison->do_tcb );
	p_poison->do_tcb = NULL;
	TCB_Delete( p_poison->vblank_tcb );
	p_poison->vblank_tcb = NULL;
	TCB_Delete( p_poison->vwaitblank_tcb );
	p_poison->vwaitblank_tcb = NULL;
	p_poison->status = POISON_EFFE_STANDBY;

}


#ifdef PM_DEBUG
void DEBUG_Poison( void )
{
	if( sys.cont & PAD_BUTTON_R ){
		if( sys.trg & PAD_BUTTON_Y ){
			POISON2_X --;
			OS_Printf( "x幅 %d \n", POISON2_X );
		}else if( sys.trg & PAD_BUTTON_A ){
			POISON2_X ++;
			OS_Printf( "x幅 %d \n", POISON2_X );
		}
	}
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.trg & PAD_BUTTON_Y ){
			POISON2_Y --;
			OS_Printf( "y幅 %d \n", POISON2_Y );
		}else if( sys.trg & PAD_BUTTON_A ){
			POISON2_Y ++;
			OS_Printf( "y幅 %d \n", POISON2_Y );
		}
	}
}
#endif

