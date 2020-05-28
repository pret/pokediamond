//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_bg.c
 *	@brief		BGオブジェクト
 *	@author		tomoya takahashi
 *	@data		2005.09.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "bg_system.h"
#include "include/system/arc_util.h"
#include "system/lib_pack.h"

#define	__IMC_BG_H_GLOBAL
#include "include/application/imageClip/imc_bg.h"

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
//	BGスクロールタスク
//	
//=====================================
typedef struct {
	IMC_BG* imc_bg;			// 今表示しているBG
	IMC_BG_ADD	new_bg;		// 新しいBGの登録データ
	BOOL*	end_flg;		// 終了フラグ

	int count;
	int add_x;
	int add_y;

	int ret_scr_x;		// 元のScroll位置
	int ret_scr_y;		// 元のScroll位置
} IMC_BG_SCR_TASK;

//-------------------------------------
//	Vブランク　キャラクタデータ転送タスク
//=====================================
typedef struct {
	GF_BGL_INI* ini;
	NNSG2dCharacterData* p_char;
	void* p_buff;	
	int bg_frame;
	int char_ofs;
} IMC_BG_CHARACTER_TRANS;

//-------------------------------------
//	Vブランク　パレットデータ転送タスク
//=====================================
typedef struct {
	NNSG2dPaletteData* p_pltt;
	void* p_buff;	
	int pltype;	// パレット転送先
	int ofs;
	int size;
} IMC_BG_PALETTE_TRANS;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void imc_bg_set_screen_charofs( const NNSG2dScreenData* scrn, int char_offs );

static void imc_bg_addCore( IMC_BG_ADD* add, int* scrn_width, int* scrn_height );

static void imc_bg_scrTsk( TCB_PTR tcb, void* work );

static void imc_bg_scrnChg( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int width, int height, int x, int y, int char_offs, int pltt_offs );

static void imc_bg_charTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID );
static void imc_bg_plttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
static void imc_bg_charTransTsk( TCB_PTR tcb, void* p_work );
static void imc_bg_plttTransTsk( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGデータの登録 & 新規変更
 *
 *	@param	obj		BGオブジェ
 *	@param	add		登録データ
 *	@param	heap	使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_MakaObj( IMC_BG* obj, IMC_BG_ADD* add )
{
	// データ設定
	obj->bg_ini		= add->bg_ini;
	obj->x			= add->x / 8;	
	obj->y			= add->y / 8;	
	obj->frame		= add->frame;	
	obj->pltt_offs	= add->pltt_offs;
	obj->pltt_num	= add->pltt_num;
	obj->char_offs	= add->char_offs;
	obj->arc_file	= add->arc_file;
	obj->scrn_arc	= add->scrn_arc;
	
	
	// BG設定
	imc_bg_addCore( add, &obj->width_char, &obj->height_char );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGデータの破棄
 *
 *	@param	obj		BGオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_DeleteObj( IMC_BG* obj )
{
	GF_BGL_ScrClear( obj->bg_ini, obj->frame );	

	memset( obj, 0, sizeof( IMC_BG ) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGアニメーション初期化
 *
 *	@param	anm		アニメBGデータ格納先
 *	@param	init	初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_AnmInit( IMC_BG_ANM* anm, IMC_BG_ANM_INIT* init )
{
	anm->bg			= init->bg;
	anm->scrn_arc01	= init->scrn_arc;
	anm->timing		= init->timing;
	anm->count		= 0;
	anm->scrn_no	= 0;
	anm->heap		= init->heap;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アニメーション更新
 *
 *	@param	anm		アニメーションBG
 *	@param	frame	進めるフレーム値
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_Anm( IMC_BG_ANM* anm, int frame )
{
	NNSG2dScreenData*	scrn;
	void*				scrn_buf;
	int					arc_id;
	
	anm->count += frame;

	if( anm->count > anm->timing ){
		anm->count = 0;

		// スクリーンファイル選択
		if( anm->scrn_no == 0 ){
			arc_id = anm->scrn_arc01;
			anm->scrn_no = 1;
		}else{
			arc_id = anm->bg->scrn_arc;
			anm->scrn_no = 0;
		}
		
		// スクリーンデータ書き出し
		scrn_buf = ArcUtil_ScrnDataGet(anm->bg->arc_file, arc_id,
				FALSE, &scrn, anm->heap);

		// スクリーンデータ転送
		imc_bg_scrnChg( anm->bg->bg_ini, anm->bg->frame, scrn,
				anm->bg->width_char, anm->bg->height_char,
				anm->bg->x, anm->bg->y,
				anm->bg->char_offs, anm->bg->pltt_offs );

		sys_FreeMemoryEz( scrn_buf );	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGアニメを終了させる
 *
 *	@param	anm		アニメーションBG
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_AnmDelete( IMC_BG_ANM* anm )
{
	NNSG2dScreenData*	scrn;
	void*				scrn_buf;

	// 絵をデフォの絵にしてメモリクリーン
	// スクリーンデータ書き出し
	scrn_buf = ArcUtil_ScrnDataGet(anm->bg->arc_file, anm->bg->scrn_arc,
			FALSE, &scrn, anm->heap);

	// スクリーンデータ転送
	imc_bg_scrnChg( anm->bg->bg_ini, anm->bg->frame, scrn,
			anm->bg->width_char, anm->bg->height_char,
			anm->bg->x, anm->bg->y,
			anm->bg->char_offs, anm->bg->pltt_offs );

	sys_FreeMemoryEz( scrn_buf );	

	memset( anm, 0, sizeof(IMC_BG_ANM) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGをScrollさせます。
 *
 *	@param	obj		今表示しているBG
 *	@param	scr_bg	スクロール先BG
 *	@param	scr_dis	スクロールさせる値
 *	@param	scr_syncスクロールに使うシンク数
 *	@param	end_flg	終了検知フラグ
 *
 *	@return	none
 *
 * 最終的にはscr_bgの方のBGが画面に出るようになります
 *
 * またBGデータ配置が
 * 256x256で
 * した128~255の部分にキャラクタがあるようになっている必要があります。
 *
 */
//-----------------------------------------------------------------------------
void IMC_BG_ScrollReq( IMC_BG* obj, IMC_BG_ADD* scr_bg, int scr_x, int scr_y, int scr_sync, BOOL* end_flg )
{
	IMC_BG_SCR_TASK* scr_tsk;
	TCB_PTR tcb;

	// タスク登録
	tcb = PMDS_taskAdd( imc_bg_scrTsk, sizeof(IMC_BG_SCR_TASK), 0, HEAPID_IMAGECLIP_DATA );
	
	// ワーク取得
	scr_tsk = TCB_GetWork( tcb );

	// 各データ設定
	scr_tsk->imc_bg = obj;
	scr_tsk->new_bg = *scr_bg;
	scr_tsk->end_flg = end_flg;
	
	scr_tsk->count	= scr_sync;
	scr_tsk->add_x	= scr_x / scr_sync;
	scr_tsk->add_y	= scr_y / scr_sync;
	scr_tsk->ret_scr_x = GF_BGL_ScrollGetX( obj->bg_ini, obj->frame );
	scr_tsk->ret_scr_y = GF_BGL_ScrollGetY( obj->bg_ini, obj->frame );

	// スクロールして、画面に出す絵を配置
	scr_bg->char_offs = IMC_BG_SCR_OFS;
	scr_bg->pltt_offs = IMC_BG_SCR_PLTT_OFS;
	scr_bg->x		  -= scr_x;
	scr_bg->y		  -= scr_y;
	scr_bg->heap	= HEAPID_IMAGECLIP_DRAW;
	imc_bg_addCore( scr_bg, NULL, NULL );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スクリーンデータのキャラクタネームの値をオフセット分ずらす
 *
 *	@param	scrn			スクリーンデータ
 *	@param	char_offs		キャラクタオフセット	キャラクタ単位
 *
 *	@return	none
 *
 * キャラクタネーム最大値チェックをしていないので注意してください
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_set_screen_charofs( const NNSG2dScreenData* scrn, int char_offs )
{
	int i;							// ループ用
	u16* scrndata;					// スクリーンデータ
	int size = scrn->szByte / 2;	// ループ回数	２=2byte
	
	// スクリーンデータ代入
	scrndata = (u16*)scrn->rawData;

	for(i=0; i<size; i++){

		scrndata[ i ] += char_offs;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	画面に絵が出るまでの処理をまとめた関数
 *
 *	@param	add				BG登録データ
 *	@param	scrn_width		スクリーンデータの幅格納先（キャラクタ単位）
 *	@param	scrn_height		スクリーンデータの高さ格納先（キャラクタ単位）
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_addCore( IMC_BG_ADD* add, int* scrn_width, int* scrn_height )
{
	int pltype;	// パレット転送先
	NNSG2dScreenData* scrn;
	void* scrn_buf;
	int height, width;
	int x, y;

	x = add->x / 8;
	y = add->y / 8;
	
	// キャラクタデータ転送
	imc_bg_charTransReq( add->arc_file, add->char_arc,
			add->bg_ini, add->frame, add->char_offs, add->heap);

	// パレットデータ転送
	if(add->frame < GF_BGL_FRAME0_S){	
		pltype = PALTYPE_MAIN_BG;
	}else{
		pltype = PALTYPE_SUB_BG;
	}
	imc_bg_plttTransReq( add->arc_file, add->pltt_arc,
			pltype, add->pltt_offs*32, add->pltt_num*32,  add->heap );

	// スクリーンデータ書き出し
	scrn_buf = ArcUtil_ScrnDataGet(add->arc_file, add->scrn_arc,
			FALSE, &scrn, add->heap);

	// 幅　高さ代入
	width = scrn->screenWidth/8;
	height = scrn->screenHeight/8;
	
	// スクリーンデータ転送
	imc_bg_scrnChg( add->bg_ini, add->frame, scrn, width, height, x, y, add->char_offs, add->pltt_offs );

	sys_FreeMemoryEz( scrn_buf );	

	if(scrn_width){
		*scrn_width = width;
	}
	if(scrn_height){
		*scrn_height = height;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スクロールタスク
 *
 *	@param	tcb			タスクオブジェ
 *	@param	work		データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_scrTsk( TCB_PTR tcb, void* work )
{
	IMC_BG_SCR_TASK* task = work;

	task->count --;
	
	if( task->count >= 0 ){
		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_X_DEC, task->add_x );

		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_Y_DEC, task->add_y );
	}else{
		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_X_SET, task->ret_scr_x );

		GF_BGL_ScrollReq( task->imc_bg->bg_ini, task->imc_bg->frame, GF_BGL_SCROLL_Y_SET, task->ret_scr_y );

		IMC_BG_MakaObj( task->imc_bg, &task->new_bg );

		if( task->end_flg ){
			*task->end_flg = TRUE;
		}
		
		// 終了
		PMDS_taskDel( tcb );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スクリーンデータ設定関数
 *
 *	@param	bg_ini		BGシステムデータ
 *	@param	frame		BGフレーム
 *	@param	scrn		スクリーンデータ
 *	@param	width		幅
 *	@param	height		高さ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	chr_offs	キャラクタオフセット
 *	@param	pltt_offs	パレットオフセット
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imc_bg_scrnChg( GF_BGL_INI* bg_ini, int frame, const NNSG2dScreenData* scrn, int width, int height, int x, int y, int char_offs, int pltt_offs )
{
	// キャラクタオフセット設定
	imc_bg_set_screen_charofs( scrn, char_offs );
	
	// 書きだし
	GF_BGL_ScrWriteExpand(
				bg_ini, frame,
				x, y,
				width, height,
				scrn->rawData,
				0, 0,
				width, height );
	
	GF_BGL_ScrPalChange( bg_ini, frame,
				x, y,
				width,height,
			pltt_offs);
	
	GF_BGL_LoadScreenV_Req(bg_ini, frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータ転送リクエスト
 *
 *	@param	fileIdx		アーカイブファイルインデックス
 *	@param	dataIdx		データインデックス
 *	@param	bgl			BGデータ
 *	@param	frm			ﾌﾚｰﾑナンバー
 *	@param	offs		オフセット
 *	@param	heapID		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_bg_charTransReq( u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 heapID )
{
	IMC_BG_CHARACTER_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(IMC_BG_CHARACTER_TRANS) );
	memset( p_tw, 0, sizeof(IMC_BG_CHARACTER_TRANS) );

	// キャラクタデータ読み込み
	p_tw->p_buff = ArcUtil_CharDataGet( fileIdx, dataIdx, FALSE, &p_tw->p_char, heapID );

	// 転送データ格納
	p_tw->ini = bgl;
	p_tw->bg_frame = frm;
	p_tw->char_ofs = offs;

	// タスク登録
	VWaitTCB_Add( imc_bg_charTransTsk, p_tw, 128 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータ転送リクエスト
 *
 *	@param	fileIdx		アーカイブファイルインデックス
 *	@param	dataIdx		データインデックス
 *	@param	palType		パレット転送先
 *	@param	offs		オフセット
 *	@param	transSize	転送size
 *	@param	heapID		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imc_bg_plttTransReq( u32 fileIdx, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID )
{
	IMC_BG_PALETTE_TRANS* p_tw;

	p_tw = sys_AllocMemory( heapID, sizeof(IMC_BG_PALETTE_TRANS) );
	memset( p_tw, 0, sizeof(IMC_BG_PALETTE_TRANS) );

	// キャラクタデータ読み込み
	p_tw->p_buff = ArcUtil_PalDataGet( fileIdx, dataIdx, &p_tw->p_pltt, heapID );

	// 転送データ格納
	p_tw->pltype = palType;
	p_tw->ofs = offs;
	p_tw->size = transSize;

	// タスク登録
	VWaitTCB_Add( imc_bg_plttTransTsk, p_tw, 128 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	キャラクタデータ転送タスク
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imc_bg_charTransTsk( TCB_PTR tcb, void* p_work )
{
	IMC_BG_CHARACTER_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_char->pRawData, p_tw->p_char->szByte );
	GF_BGL_LoadCharacter( p_tw->ini, p_tw->bg_frame, 
			p_tw->p_char->pRawData, p_tw->p_char->szByte, p_tw->char_ofs );

	// メモリ解放
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレットデータ転送タスク
 *
 *	@param	tcb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imc_bg_plttTransTsk( TCB_PTR tcb, void* p_work )
{
	IMC_BG_PALETTE_TRANS* p_tw = p_work;


	DC_FlushRange( p_tw->p_pltt->pRawData, p_tw->size );

	if( p_tw->pltype == PALTYPE_MAIN_BG ){
		GX_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}else if( p_tw->pltype == PALTYPE_SUB_BG ){
		GXS_LoadBGPltt( p_tw->p_pltt->pRawData, p_tw->ofs, p_tw->size );
	}

	// メモリ解放
	TCB_Delete( tcb );
	sys_FreeMemoryEz( p_tw->p_buff );
	sys_FreeMemoryEz( p_tw );
}
