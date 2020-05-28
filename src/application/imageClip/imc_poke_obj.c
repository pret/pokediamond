//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_poke_obj.c
 *	@brief		イメージクリップ　ポケモンデータ	
 *	@author		tomoya takahashi 
 *	@data		2005.09.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "system/arc_util.h"
#include "include/poketool/monsno.h"

#define __IMC_POKE_OBJ_H_GLOBAL
#include "include/application/imageClip/imc_poke_obj.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
/*
#define IMC_POKE_IN_SIZE_SML	(20)
#define IMC_POKE_IN_SIZE_MDL	(10)
#define IMC_POKE_IN_SIZE_BIG	(5)

#define IMC_POKE_IN_SML	(0)
#define IMC_POKE_IN_MDL	(1)
#define IMC_POKE_IN_BIG	(2)
#define IMC_POKE_IN_SIZE_NUM	( 3 )//*/


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static int GetInSize_SizeX( char* buff, int pokegra_x );
static void GetInSize_Draw( char* buff );

static void SetPokeHitTbl( RECT_HIT_TBL* p_tbl, int x, int y, int size_hx, int size_hy );

//-----------------------------------------------------------------------------
/**
*	今だけグローバル変数
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンのキャラクタデータを描画システムに登録
 *
 *	@param	drawData		描画システムデータ
 *	@param	arc_data		アーカイブデータ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_CharSet( IMC_DRAW_DATA* drawData, SOFT_SPRITE_ARC* arc_data )
{
	// キャラクタデータを登録
	void* buff;
	NNSG2dCharacterData* p_char;
	
	buff = ArcUtil_Load( arc_data->arc_no, arc_data->index_chr, FALSE, HEAPID_IMAGECLIP_DRAW, ALLOC_TOP );
	p_char = IMC_DRAW_SetCharData( drawData, buff, IMC_DRAW_POKE_CHAR_ID );

	SoftSpriteChrMask( (u8*)p_char->pRawData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ　ポケモンデータ作成
 *
 *	@param	poke			イメージクリップ　ポケモンデータ
 *	@param	sprite_man		ソフトウェアスプライトマネージャ
 *	@param	poke_para		ポケモンパラメータ構造体
 *	@param	arc_data		アーカイブファイルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_Init( IMC_POKE* poke, SOFT_SPRITE_MANAGER* sprite_man, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap )
{
	int monsno = PokeParaGet( poke_para, ID_PARA_monsno, NULL );

	// ポケモングラフィック取得
	PokeGraArcDataGetPP(arc_data, poke_para, PARA_FRONT);
	
	// 表示設定
	poke->sprite = SoftSpriteAdd( 
			sprite_man,
			arc_data,
			IMC_POKE_INIT_X,IMC_POKE_INIT_Y, 
			IMC_POKE_DEFAULT_PRI, 0, NULL, NULL);


	// データ作成
	{
		int x, y;
		IMC_POKE_SizeGet( poke, &x, &y );
		x /= 2;
		y /= 2;
		poke->hit_tbl.rect.top		= IMC_POKE_INIT_Y - y;
		poke->hit_tbl.rect.bottom	= IMC_POKE_INIT_Y + y;
		poke->hit_tbl.rect.left		= IMC_POKE_INIT_X - x;
		poke->hit_tbl.rect.right	= IMC_POKE_INIT_X + x;

		SetPokeHitTbl( &poke->hit_tbl, IMC_POKE_INIT_X, IMC_POKE_INIT_Y, x, y );
	}

	// 食い込んで良いサイズ設定
	{
		u8 height = PokeParaHeightGet( poke_para, PARA_FRONT );
		// キャラクタデータを登録
		void* buff;
		NNSG2dCharacterData* p_char;
		
		buff = ArcUtil_Load( arc_data->arc_no, arc_data->index_chr, FALSE, heap, ALLOC_TOP );
		NNS_G2dGetUnpackedCharacterData( buff, &p_char );

		SoftSpriteChrMask( (u8*)p_char->pRawData );	
		
		poke->ins_x = GetInSize_SizeX( p_char->pRawData, p_char->W*8 );
		poke->ins_y = height;

//		GetInSize_Draw( p_char->pRawData );

		sys_FreeMemoryEz( buff );
	}

	// ポケモンデータ保持
	poke->poke_para = poke_para;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ　ポケモンデータ破棄
 *
 *	@param	poke			イメージクリップ　ポケモンデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_Delete( IMC_POKE* poke )
{
	SoftSpriteDel( poke->sprite );
	memset( poke, 0, sizeof( IMC_POKE ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示優先順位を設定
 *
 *	@param	poke		ポケモンデータ
 *	@param	priority	優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_DrawPrioritySet( IMC_POKE* poke, int priority )
{
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_Z, priority );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示優先順位を取得
 *
 *	@param	poke		ポケモンデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_POKE_DrawPriorityGet( IMC_POKE* poke )
{
	return SoftSpriteParaGet( poke->sprite, SS_PARA_POS_Z );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標を設定
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_MatrixSet( IMC_POKE* poke, int x, int y )
{
	int size_x, size_y;
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_X, x );
	SoftSpriteParaSet( poke->sprite, SS_PARA_POS_Y, y );

	size_y /= 2;
	size_x /= 2;
	
	SetPokeHitTbl( &poke->hit_tbl, x, y, size_x, size_y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンとタッチパネルの当たり判定
 *
 *	@param	poke	ポケモンデータ
 *
 *	@retval	TRUE	あたり
 *	@retval	FALSE	あたらない
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHit( IMC_POKE* poke )
{
	return GF_TP_SingleHitCont( &poke->hit_tbl );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンと指定座標の当たり判定
 *
 *	@param	poke	ポケモンデータ
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@retval	TRUE	あたり
 *	@retval	FALSE	あたらない
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitSelf( IMC_POKE* poke, int x, int y )
{
	
	return GF_TP_SingleHitSelf( &poke->hit_tbl, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン座標を取得
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_MatrixGet( IMC_POKE* poke, int* x, int* y )
{
	*x = SoftSpriteParaGet( poke->sprite, SS_PARA_POS_X );
	*y = SoftSpriteParaGet( poke->sprite, SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンサイズを取得
 *
 *	@param	poke		ポケモンデータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_SizeGet( IMC_POKE* poke, int* x, int* y )
{
	*x = SOFT_SPRITE_SIZE_X;
	*y = SOFT_SPRITE_SIZE_Y;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う
 *
 *	@param	poke		オブジェクトデータ
 *	@param	offs_x		左上からのオフセットｘ座標
 *	@param	offs_y		左上からのオフセットｙ座標
 *	@param	char_data	キャラクタデータ	
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitEx( IMC_POKE* poke, int* offs_x, int* offs_y, NNSG2dCharacterData* char_data )
{
	int check;		// チェック用
	int size_x, size_y;	// サイズ	
	int x, y;		// 現在の中心座標
	
	// まず当たり判定を普通に行う
	check = IMC_POKE_TPHit( poke );
	if( check == FALSE ){
		return FALSE;
	}

	// 左上座標取得
	IMC_POKE_MatrixGet( poke, &x, &y );
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	x -= (size_x / 2);
	y -= (size_y / 2);

	// オフセット値を取得
	*offs_x = sys.tp_x - x;
	*offs_y = sys.tp_y - y;


	// その位置のキャラクタデータをチェック
	// 抜け色でないかをチェック
	check = IMC_DRAW_CharCheck( char_data, *offs_x, *offs_y, 0 );

	// colorナンバーが０なら返す
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う	座標指定
 *
 *	@param	poke		オブジェクトデータ
 *	@param	x			左上からのオフセットｘ座標
 *	@param	y			左上からのオフセットｙ座標
 *	@param	char_data	キャラクタデータ	
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_POKE_TPHitExSelf( IMC_POKE* poke, int x, int y, NNSG2dCharacterData* char_data )
{
	int check;		// チェック用
	int size_x, size_y;	// サイズ	
	int cx, cy;		// 現在の中心座標
	
	// まず当たり判定を普通に行う
	check = IMC_POKE_TPHitSelf( poke, x, y );
	if( check == FALSE ){
		return FALSE;
	}

	// 左上座標取得
	IMC_POKE_MatrixGet( poke, &cx, &cy );
	IMC_POKE_SizeGet( poke, &size_x, &size_y );
	cx -= (size_x / 2);
	cy -= (size_y / 2);

	// オフセット値を取得
	x -= cx;
	y -= cy;

	// その位置のキャラクタデータをチェック
	// 抜け色でないかをチェック
	check = IMC_DRAW_CharCheck( char_data, x, y, 0 );

	// colorナンバーが０なら返す
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンの食い込んでよいサイズを取得
 *
 *	@param	poke		オブジェクトデータ
 *	@param	ins_x		食い込んでよいサイズ取得領域
 *	@param	ins_y		食い込んでよいサイズ取得領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_POKE_InSizeGet( IMC_POKE* poke, int* ins_x, int* ins_y )
{
	*ins_x = poke->ins_x;
	*ins_y = poke->ins_y;
}




//-----------------------------------------------------------------------------
/**
*	プライベート関数
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンキャラクタデータから左端から最初の点の大きさを求める
 *
 *	@param	buff	バッファ
 *
 *	@return	左端からポケモンまでのサイズ
 */
//-----------------------------------------------------------------------------
#define IMC_POKE_CHAR_FMT_BIT	(4)	// 1ピクセルのビット数
#define IMC_POKE_CHAR_FMT_NUM	(2)	// 1byteに入る数
static int GetInSize_SizeX( char* buff, int pokegra_x )
{
	int i, j;
	int c_idx;
	int ofs_idx;
	u8 msk;

	for( i=0; i<SOFT_SPRITE_SIZE_X; i++ ){
		
		for( j=0; j<SOFT_SPRITE_SIZE_Y; j++ ){
			c_idx = ((j * pokegra_x) + i)/IMC_POKE_CHAR_FMT_NUM;
			ofs_idx = ((j * pokegra_x) + i)%IMC_POKE_CHAR_FMT_NUM;
			msk = 0xf << (IMC_POKE_CHAR_FMT_BIT * ofs_idx);
			if( (buff[ c_idx ] & msk) != 0 ){
				return i;
			}
		}
	}
	return SOFT_SPRITE_SIZE_X;
}

static void GetInSize_Draw( char* buff )
{
	int i, j;
	int c_idx;
	int ofs_idx;
	u8 msk;

	for( i=0; i<SOFT_SPRITE_SIZE_Y; i++ ){
		
		for( j=0; j<SOFT_SPRITE_SIZE_X; j++ ){
			c_idx = ((j * SOFT_SPRITE_SIZE_X) + i)/IMC_POKE_CHAR_FMT_NUM;
			ofs_idx = ((j * SOFT_SPRITE_SIZE_X) + i)%IMC_POKE_CHAR_FMT_NUM;
			msk = 0xf << (IMC_POKE_CHAR_FMT_BIT * ofs_idx);
			OS_Printf( "%02d", (buff[ c_idx ] & msk) >> IMC_POKE_CHAR_FMT_BIT );
		}
		OS_Printf( "\n" );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	当たり判定テーブルにデータ設定
 *	
 *	@param	p_tbl		テーブルワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	size_hx		ハーフサイズｘ
 *	@param	size_hy		ハーフサイズｙ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void SetPokeHitTbl( RECT_HIT_TBL* p_tbl, int x, int y, int size_hx, int size_hy )
{
	if( (y - size_hy) >= 0 ){
		p_tbl->rect.top		= y - size_hy;
	}else{
		p_tbl->rect.top		= 0;
	}
	if( (y + size_hy) <= 191 ){
		p_tbl->rect.bottom	= y + size_hy;
	}else{
		p_tbl->rect.bottom	= 191;
	}
	if( (x - size_hx) >= 0 ){
		p_tbl->rect.left	= x - size_hx;
	}else{
		p_tbl->rect.left	=0; 
	}
	if( (x + size_hx) <= 255 ){
		p_tbl->rect.right	= x + size_hx;
	}else{
		p_tbl->rect.right	= 255;
	}
}


#ifdef PM_DEBUG
//#include "include/application/imageClip/imc_subwin.h"
#include "include/msgdata/msg_debug_tomoya.h"
void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData );

static int DEBUG_poke	 = 0;
void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData )
{
	SOFT_SPRITE_ARC		arc;
	POKEMON_PARAM*		p_pp;
	BOOL chenge = FALSE;

	// 変更処理
	if( sys.trg & PAD_BUTTON_START ){
		DEBUG_poke = (1+DEBUG_poke) % MONSNO_END;
		chenge = TRUE;
	}
	if( sys.trg & PAD_BUTTON_SELECT ){
		DEBUG_poke--;
		if( DEBUG_poke < 0 ){
			DEBUG_poke += MONSNO_END;
		}
		chenge = TRUE;
	}

	// 変更
	if( chenge ){	
		p_pp = PokemonParam_AllocWork( heap );
		
		// ポケモンデータ作成
		PokeParaSet( p_pp, DEBUG_poke, 10, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0 );
		IMC_POKE_Delete( poke );
		IMC_POKE_Init( poke, drawData->SSM_drawSys, p_pp, &arc, heap );

		// 当たり判定用キャラクタワーク破棄
		RESM_DeleteResID( drawData->SWSP_charRes, IMC_DRAW_POKE_CHAR_ID );
		IMC_POKE_CharSet( drawData, &arc );
		sys_FreeMemoryEz( p_pp );
	}
}

#endif
