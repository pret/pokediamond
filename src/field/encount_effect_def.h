//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		eccount_effect_def.h
 *@brief	エンカウントエフェクトのタスク作成に必要なデータ
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ECCOUNT_EFFECT_DEF_H__
#define __ECCOUNT_EFFECT_DEF_H__

#include "field_hblank.h"
#include "system/clact_util.h"

#undef GLOBAL
#ifdef	__ECCOUNT_EFFECT_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



#define TCB_TSK_PRI	(5)
#define TCB_VWAIT_BR_TSK_PRI	(10)


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	汎用動作
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} ENC_MOVE_WORK;
GLOBAL void ENC_MoveReq( ENC_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
GLOBAL BOOL	ENC_MoveMain( ENC_MOVE_WORK* p_work );

//-------------------------------------
//	汎用動作
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	int count;
	int count_max;
} ENC_MOVE_WORK_FX;
GLOBAL void ENC_MoveReqFx( ENC_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max );
GLOBAL BOOL	ENC_MoveMainFx( ENC_MOVE_WORK_FX* p_work );

//-------------------------------------
//	汎用加速動作
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 s_s;	// 初速度
	fx32 s_a;	// 加速度
	int count;
	int count_max;
} ENC_ADDMOVE_WORK_FX;
GLOBAL void ENC_AddMoveReqFx( ENC_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max );
GLOBAL BOOL	ENC_AddMoveMainFx( ENC_ADDMOVE_WORK_FX* p_work );




//-------------------------------------
//
//	エンカウントエフェクトワーク
//
//=====================================
typedef struct{
	int seq;
	int wait;
	int count;
	void* work;		// 各自、自由に使用
	FIELDSYS_WORK *fsw;
	BOOL* end;		// 終了ﾁｪｯｸ用
	BOOL hblank_flg;// Hブランクフラグ
	BOOL wipe_flag;
}ENCOUNT_EFFECT_WORK;



//----------------------------------------------------------------------------
/**
 *
 *@brief	最初のフラッシュの表現をするタスクを実行する
 *				ブライトネスを使用し、画面がピカピカ点滅します。
 *
 *@param	disp	メイン画面にかける:MASK_MAIN_DISPLAY
 *					サブ画面にかける:MASK_SUB_DISPLAY
 *					両画面にかける:MASK_DOUBLE_DISPLAY
 *@param	bright_color		ﾌﾞﾗｲﾄﾈｽカラー
 *@param	sub_bright_color	サブ面ﾌﾞﾗｲﾄﾈｽカラー
 *@param	end		終了したらTRUEを返すフラグ
 *@param	flash_num			フラッシュ回数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void EncountFlashTask(int disp, u32 bright_color, u32 sub_bright_color, BOOL* end, u32 flash_num);

//-------------------------------------
//
//	Hブランク用関数郡
//
//=====================================
// Hブランク終了チェック
GLOBAL BOOL ENC_HBlankEndCheck( ENCOUNT_EFFECT_WORK* p_work );

// 横に画面を割る
GLOBAL void ENC_BG_Cut_Start(ENCOUNT_EFFECT_WORK* p_ew);

// ドット単位で画面を横に切る
typedef struct _ENC_HB_BG_SLICE ENC_HB_BG_SLICE;

GLOBAL ENC_HB_BG_SLICE* ENC_BG_Slice_Alloc( void );
GLOBAL void ENC_BG_Slice_Delete( ENC_HB_BG_SLICE* p_work );
GLOBAL void ENC_BG_Slice_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s );
GLOBAL void ENC_BG_Slice_Change( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s );

// ウィンドウで斜めに画面を隠していく
typedef struct _ENC_HB_BG_WND_SLANT ENC_HB_BG_WND_SLANT;

GLOBAL ENC_HB_BG_WND_SLANT* ENC_BG_WndSlant_Alloc( void );
GLOBAL void ENC_BG_WndSlant_Delete( ENC_HB_BG_WND_SLANT* p_work );
GLOBAL void ENC_BG_WndSlant_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_SLANT* p_eff, u32 sync, fx32 x_ss, fx32 y_ss );

// カットイン用　ジグザグウィンドウ
typedef struct _ENC_HB_BG_WND_ZIGUZAGU	ENC_HB_BG_WND_ZIGUZAGU;

GLOBAL ENC_HB_BG_WND_ZIGUZAGU* ENC_BG_WndZiguzagu_Alloc( void );
GLOBAL void ENC_BG_WndZiguzagu_Delete( ENC_HB_BG_WND_ZIGUZAGU* p_work );
GLOBAL void ENC_BG_WndZiguzagu_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_ZIGUZAGU* p_eff, u32 sync, u32 dot, u32 width, u32 wnd_msk_in, u32 wnd_msk_out );



//-------------------------------------
//	
//	ﾏｽﾀｰブライトネス関連
//	
//=====================================
typedef struct {
	ENC_MOVE_WORK brightness;
	int disp;
} BR_BRIGHTNESS_FADE;
GLOBAL void ENC_SetMstBrightness( int disp, int no );
GLOBAL void ENC_ChangeMstBrightness( BR_BRIGHTNESS_FADE* p_data, int start, int end, int disp, int sync );
GLOBAL BOOL ENC_ChangeMstBrightnessMain( BR_BRIGHTNESS_FADE* p_data );
GLOBAL void ENC_V_SetMstBrightness( int disp, int no );


//-----------------------------------------------------------------------------
/**
 *
 *		BG設定関連
 *
 */
//-----------------------------------------------------------------------------
#define ENC_BG_AFFINE_FRAME		( GF_BGL_FRAME3_M )

GLOBAL void ENC_BG_SetAffineCont( GF_BGL_INI* p_bgl );	// これでアフィンBGをしようできるように変更する　変更に1シンク使用する
GLOBAL void ENC_BG_SetAffineBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, GF_BGL_INI* p_bgl );
GLOBAL void ENC_BG_SetNormalBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, u32 pltt_no, u32 pltt_num, GF_BGL_INI* p_bgl, u32 frame );

typedef struct {
	GF_BGL_INI* p_bgl;
	MtxFx22 mtx;
	u32 frame;
	int cx;
	int cy;
	int sc_x;
} ENC_BG_SET_AFFINEPARAM;
#define ENC_BG_SET_AFFINE_MTX_PRI	( 1024 )
GLOBAL void ENC_BG_SetAffineMtx( ENC_BG_SET_AFFINEPARAM* p_work, GF_BGL_INI* p_bgl, u32 frame, fx32 scale_x, fx32 scale_y, u16 rota, int cx, int cy, int sc_x );


// ビットマップウィンドウ塗りつぶしオブジェクト
typedef struct _ENC_BMP_FILL_OBJ ENC_BMP_FILL_OBJ;

GLOBAL ENC_BMP_FILL_OBJ* ENC_BMP_FillObjAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillObjDelete( ENC_BMP_FILL_OBJ* p_work );
GLOBAL void ENC_BMP_FillObjStart( ENC_BMP_FILL_OBJ* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col );
GLOBAL BOOL ENC_BMP_FillObjMain( ENC_BMP_FILL_OBJ* p_work );

// ビットマップブロック状塗りつぶしオブジェクト
typedef struct _ENC_BMP_FILL_BLOCK ENC_BMP_FILL_BLOCK;

GLOBAL ENC_BMP_FILL_BLOCK* ENC_BMP_FillBlockAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillBlockDelete( ENC_BMP_FILL_BLOCK* p_work );
GLOBAL void ENC_BMP_FillBlockStart( ENC_BMP_FILL_BLOCK* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col );
GLOBAL BOOL ENC_BMP_FillBlockMain( ENC_BMP_FILL_BLOCK* p_work );

// ビットマップブロック埋め尽くしシステム
typedef struct _ENC_BMP_FILL_BLOCK_MOVE ENC_BMP_FILL_BLOCK_MOVE;

GLOBAL ENC_BMP_FILL_BLOCK_MOVE* ENC_BMP_FillBlockMoveAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillBlockMoveDelete( ENC_BMP_FILL_BLOCK_MOVE* p_work );
GLOBAL void ENC_BMP_FillBlockMoveStart( ENC_BMP_FILL_BLOCK_MOVE* p_work, u8 sync, u8 start, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_FillBlockMoveMain( ENC_BMP_FILL_BLOCK_MOVE* p_work );

// 円形BMP塗りつぶしオブジェクト
typedef struct _ENC_BMP_CIRCLE_FILL ENC_BMP_CIRCLE_FILL;

GLOBAL ENC_BMP_CIRCLE_FILL* ENC_BMP_CircleFillAlloc( u32 heapID );
GLOBAL void ENC_BMP_CircleFillDelete( ENC_BMP_CIRCLE_FILL* p_work );
GLOBAL void ENC_BMP_CircleFillStart( ENC_BMP_CIRCLE_FILL* p_work, u8 sync, u16 s_rota, u16 e_rota, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_CircleFillMain( ENC_BMP_CIRCLE_FILL* p_work );


// フラッシュアウト　オブジェ
typedef struct _ENC_BMP_FLASH_OUT ENC_BMP_FLASH_OUT;
GLOBAL ENC_BMP_FLASH_OUT* ENC_BMP_FlashOutAlloc( u32 heapID );
GLOBAL void ENC_BMP_FlashOutDelete( ENC_BMP_FLASH_OUT* p_work );
GLOBAL void ENC_BMP_FlashOutStart( ENC_BMP_FLASH_OUT* p_work, u8 sync, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_FlashOutMain( ENC_BMP_FLASH_OUT* p_work );


//-----------------------------------------------------------------------------
/**
 *
 *		OAM設定関連
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	セルアクターパック
//=====================================
typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[4];	// リソースマネージャ
} ENC_CLACT_SYS;
//-------------------------------------
//	セルアクターリソースオブジェパック
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR resobj[4];
	CLACT_HEADER head;
} ENC_CLACT_RES_WORK;

// システム初期化
GLOBAL void ENC_CLACT_Init( ENC_CLACT_SYS* p_sys, int work_num, int res_num );
GLOBAL void ENC_CLACT_Delete( ENC_CLACT_SYS* p_sys );

// 簡単リソース読み込み
GLOBAL void ENC_CLACT_ResLoadEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id );
GLOBAL void ENC_CLACT_ResDeleteEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work );
GLOBAL void ENC_CLACT_ResColorChange( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb );

// アクター登録
GLOBAL CLACT_WORK_PTR ENC_CLACT_Add( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri );

// OAM汎用
GLOBAL VecFx32 ENC_MakeVec( fx32 x, fx32 y, fx32 z );

// ソフトウェアスプライトキャラクタデータの転送
#define ENC_OAM_TR_CHAR_CUT_CX	( 1 )	// これだけずらしたところから抜き出す
GLOBAL void ENC_CLACT_ResSetSoftSpriteDataTrOam( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb, u32 ofs_cx );

// OAM面をウィンドウを矩形で設定
typedef struct{
	u8 x1;
	u8 x2;
	u8 y1;
	u8 y2;
	u8 wnd_no;
	u8 dummy[3];
} ENC_WND_SETPOSITION;
#define ENC_SET_WND_SCALE_TCB_PRI	( 1024 )
GLOBAL void ENC_WND_SetScaleWnd( fx32 y, int bottom_y, fx32 scale, int height, int wndno, ENC_WND_SETPOSITION* p_work );
GLOBAL int ENC_WND_SetScaleWndToolMakeBottomY( fx32 scale, int c_y, int half_height );

// VブランクMaster輝度操作タスク
#define ENC_SET_MSTBRI_TCB_PRI	( 1024 )
GLOBAL void ENC_SetMasterBrightnessVblank( int* p_setnum );


#undef	GLOBAL
#endif		// __ECCOUNT_EFFECT_DEF_H__

