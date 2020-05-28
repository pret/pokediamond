//============================================================================================
/**
 * @file	encount_effect.c
 * @bfief	エンカウント処理
 * @author	GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "field_event.h"
#include "motion_bl.h"
#include "system/arc_util.h"

#include "fieldmap_work.h"
#include "fieldsys.h"

#include "battle/attr_def.h"
#include "ev_pokemon.h"

#include "system/palanm.h"


#define __ENCOUNT_EFFECT_H_GLOBAL__
#include "encount_effect.h"
#define __ECCOUNT_EFFECT_DEF_H_GLOBAL
#define __ECCOUNT_EFFECT_DEF_H_GLOBAL_VAL
#include "encount_effect_def.h"

#include "ecnt_tomo.h"
#include "encount_effect_sub.h"


//-----------------------------------------------------------------------------
//
// エンカウント用関数テーブル
//
//=============================================================================
static const TCB_FUNC EncountEffectTask[] ={

	EncountEffect_Field_GrassLevelLow,
	EncountEffect_Field_GrassLevelHigh,
	EncountEffect_Field_WaterLevelLow,
	EncountEffect_Field_WaterLevelHigh,
	EncountEffect_Field_DanLevelLow,
	EncountEffect_Field_DanLevelHigh,
	EncountEffect_Trainer_GrassLevelLow,
	EncountEffect_Trainer_GrassLevelHigh,
	EncountEffect_Trainer_WaterLevelLow,
	EncountEffect_Trainer_WaterLevelHigh,
	EncountEffect_Trainer_DanLevelLow,
	EncountEffect_Trainer_DanLevelHigh,

	EncountEffect_SPTR_IwaGym,			// クロガネジム
	EncountEffect_SPTR_KusaGym,         // ハクタイジム
	EncountEffect_SPTR_MizuGym,         // ノモセジム
	EncountEffect_SPTR_KakutouGym,      // トバリジム
	EncountEffect_SPTR_GoosutoGym,      // ヨスガトジム
	EncountEffect_SPTR_KooriGym,        // キッサキジム
	EncountEffect_SPTR_HaganeGym,       // ミオジム
	EncountEffect_SPTR_DenkiGym,        // ナギサジム

	EncountEffect_SPTR_Siten00,
	EncountEffect_SPTR_Siten01,
	EncountEffect_SPTR_Siten02,
	EncountEffect_SPTR_Siten03,

	EncountEffect_SPTR_Chanpion,

	EncountEffect_Legend_Normal,
	EncountEffect_Legend_Package,
	
	EncountEffect_Ginga_Normal,
	EncountEffect_Ginga_Special,

	EncountEffect_Special_Tower,
	EncountEffect_Special_Double,

	
/*	EncountEffectMotionBl00,
	EncountEffectMotionBl01,//*/

};

//-------------------------------------
//	
//	ビットマップ操作
//	
//=====================================
// ビットマップウィンドウ塗りつぶしオブジェクト
typedef struct _ENC_BMP_FILL_OBJ{
	ENC_MOVE_WORK move_x;
	ENC_MOVE_WORK move_y;
	GF_BGL_BMPWIN* p_bmp;
	u8 width;
	u8 height;
	u8 move_flg;
	u8 col;
} ;

// ビットマップウィンドウブロック上塗りつぶしオブジェクト
typedef struct _ENC_BMP_FILL_BLOCK{
	ENC_MOVE_WORK move_x;
	ENC_MOVE_WORK move_y;
	GF_BGL_BMPWIN* p_bmp;
	u8 width;
	u8 height;
	u8 move_flg;
	u8 col;
} ;

static void ENC_BMP_Fill( GF_BGL_BMPWIN* p_bmp, s32 top, s32 bottom, s32 left, s32 right, u8 col );

// ビットマップブロック埋め尽くしシステム
#define ENCOUNT_BLOCK_MOVE_WIDTH	( 32 )	// ブロックサイズ
#define ENCOUNT_BLOCK_MOVE_HEIGHT	( 32 )	// ブロックサイズ
#define ENCOUNT_BLOCK_MOVE_MAT_Y	( -16 )	// 開始座標
#define ENCOUNT_BLOCK_MOVE_MOVE_Y	( 192 + ENCOUNT_BLOCK_MOVE_MAT_Y )	// 移動距離
#define ENCOUNT_BLOCK_MOVE_OBJNUM	( 48 )	// xブロックで埋める
#define ENCOUNT_BLOCK_MOVE_X_NUM	( 8 )	// 横の数
#define ENCOUNT_BLOCK_MOVE_Y_NUM	( 6 )	// 縦の数
static const u8 ENCOUNT_BLOCK_MOVE_MoveParam[ ENCOUNT_BLOCK_MOVE_X_NUM ] = {	// 出てくるx座標の順番テーブル
	 0, 2, 5, 7, 1, 6, 3, 4 
};
typedef struct _ENC_BMP_FILL_BLOCK_MOVE{
	GF_BGL_BMPWIN* p_bmp;
	ENC_BMP_FILL_BLOCK* p_block[ ENCOUNT_BLOCK_MOVE_OBJNUM ];
	u8	block_count;
	u8	block_end_count;
	u8	move_sync;
	u8	start_sync;
	s8	wait;
	u8	col;
	u8	init_flg;
	u8	dummy[1];
};

// 円形ビットマップ塗りつぶし
typedef struct _ENC_BMP_CIRCLE_FILL{
	GF_BGL_BMPWIN* p_bmp;
	ENC_MOVE_WORK rota;
	u8 move_flg;
	u8 col;
	u8 dummy[2];
};
static void EncBmpCircleFill_Fill( GF_BGL_BMPWIN* p_bmp, u16 last_rota, u16 now_rota, u8 col );

// フラッシュアウト　オブジェ
#define ENC_BMP_FLASH_CIRCLE_NUM	( 8 )
static const u16 FlashOutParam[8][2] = {
	{ 0, 23 },
	{ 45, 22 },
	{ 45, 68 },
	{ 90, 67 },		// ここは固定　これじゃないとうまくいかない
	{ 91, 113 },	// ここは固定　これじゃないとうまくいかない
	{ 135, 112 },
	{ 135, 158 },
	{ 180, 157 },
};
typedef struct _ENC_BMP_FLASH_OUT {
	ENC_BMP_CIRCLE_FILL* p_circle[ ENC_BMP_FLASH_CIRCLE_NUM ];
	u8 move_flg;
	u8 dummy[3];
};


//-------------------------------------
//	
//	ﾌﾞﾗｲﾄﾈｽ関係
//	
//=====================================

static void ENC_BrightnessVset( TCB_PTR tcb, void* work );

//-------------------------------------
//
//	最初のピカピカのタスク
//
//=====================================
typedef struct{
	int seq;
	u32 flash_num;
	int count;
	int disp;		// 画面指定
	u32 end_bright;
	u32 sub_bright;
	BR_BRIGHTNESS_FADE br_main;
	BR_BRIGHTNESS_FADE br_sub;
	BOOL* end;		// 終了ﾁｪｯｸ用
} BR_FLASH_TASK;
#define FLASH_EFF_SYNC_SUB	( 8 )
#define FLASH_EFF_SYNC_ONE	( 3 )

// 開始エフェクトタスク（最初の光るものなどを制御）
static void BR_FlashTask(TCB_PTR tcb, void *work);
enum{
	FADE_SUB_EFFECT,
	FADE_EFFECT,
	FADE_WAIT,
	FADE_RET_EFFECT,
	FADE_RET_WAIT,
	END_EFFECT,
};

//-------------------------------------
//
//	Hブランク用
//
//=====================================
//---------------------------
// BGを横に割るHBlank用
//===========================
typedef struct {
	int x;			// 今の移動位置
	int speed;		// 速度
	BOOL* end_check;// 終了チェック
} ENC_HB_BG_CUT;
#define ENC_HB_BG_CUT_ST	(100)		// 加速度
#define ENC_HB_BG_CUT_END_X	(25000)
static void ENC_BG_Cut_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);

//-------------------------------------
//	ｘドットごとに左右に分けて移動
//=====================================
typedef struct _ENC_HB_BG_SLICE{
	ENC_ADDMOVE_WORK_FX move_x;
	u32 dot;
	u32 seq;
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// 終了チェック
} ;
#define END_HB_BG_SLICE_TCB_PRI	( 1024 )
#define END_HB_BG_SLICE_INIT_TCB_PRI	( 1024 )
static void ENC_BG_Slice_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_Slice_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_Slice_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_Slice_End( ENC_HB_BG_SLICE* p_work );


//-------------------------------------
// ウィンドウで斜めに画面を隠していく
//=====================================
typedef struct _ENC_HB_BG_WND_SLANT{
	ENC_ADDMOVE_WORK_FX move_x;
	ENC_ADDMOVE_WORK_FX move_y;
	u32 cut_y;
	u32 seq;
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// 終了チェック
};
#define END_HB_BG_WND_SLANT_TCB_PRI	( 1024 )
#define END_HB_BG_WND_SLANT_INIT_TCB_PRI	( 1024 )
#define END_HB_BG_WND_SLANT_CUT_Y	( 96 )
#define END_HB_BG_WND_SLANT_MOVE_X	( 255*FX32_ONE )
#define END_HB_BG_WND_SLANT_MOVE_Y	( 96*FX32_ONE )
static void ENC_BG_WndSlant_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndSlant_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndSlant_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_WndSlant_End( ENC_HB_BG_WND_SLANT* p_work );

// カットイン用　ジグザグウィンドウ
typedef struct _ENC_HB_BG_WND_ZIGUZAGU{
	ENC_MOVE_WORK move_x;
	u32 seq;
	u8  ziguzagu_buf[ 192 ];
	FIELD_HBLANK_SYS* p_hsys;
	FIELD_HBLANK_OBJ* p_hobj;
	TCB_PTR tcb;
	BOOL* end_check;// 終了チェック
} ;
#define ENC_BG_WND_ZIGUZAGU_MOVE_S		( 0 )
#define ENC_BG_WND_ZIGUZAGU_MOVE_E		( 255 )
#define END_HB_BG_WND_ZIGUZAGU_TCB_PRI	( 1024 )
#define END_HB_BG_WND_ZIGUZAGU_INIT_TCB_PRI	( 1024 )
static void ENC_BG_WndZiguzagu_SetUp_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndZiguzagu_Tcb( TCB_PTR tcb, void* p_work );
static void ENC_BG_WndZiguzagu_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work);
static void ENC_BG_WndZiguzagu_End( ENC_HB_BG_WND_ZIGUZAGU* p_work );



//-------------------------------------
//	グラフィック類
//=====================================
#define ENC_BG_AFFINCONT_TASK	( 1024 )
static void ENC_BG_AffinContSetTcb( TCB_PTR tcb, void* work );

// OAM
static void ENC_OAM_TransOamPltt( CLACT_WORK_PTR clact, void* data, u32 size );
static void ENC_OAM_TransOamChar( CLACT_WORK_PTR clact, void* data, u32 size );
#define ENC_OAM_TR_CHAR_SIZE_X	( 64 )	// OAMキャラクタ単位サイズ
#define ENC_OAM_TR_CHAR_SIZE_Y	( 64 )	// OAMキャラクタ単位サイズ
#define ENC_OAM_TR_CHAR_ONELINE	( 8*8 )
#define ENC_OAM_TR_CHAR_BUFF_SIZE 	( 0x800 )// キャラクタバッファサイズ
#define ENC_OAM_TR_CHAR_CUT_Y	( 0 )	// これだけずらしたところから抜き出す
static void* ENC_OAM_TrCharMake( const NNSG2dCharacterData* cp_chardata, u32 heap, u32* p_size, u32 ofs_cx );

static void ENC_WND_SetWndPositionVWait( TCB_PTR tcb, void* p_work );


//----------------------------------------------------------------------------
/**
 *
 *@brief	エンカウントエフェクト開始
 *
 *@param	No		エンカウントエフェクトNO
 *@param	*fsw	フィールドシステムワークのポインタ
 *@param	end		終了チェック用　TRUE：終了した 
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectStart(int No, FIELDSYS_WORK *fsw, BOOL* end )
{
	TCB_PTR tcb;
	ENCOUNT_EFFECT_WORK *eew;
	tcb = PMDS_taskAdd(EncountEffectTask[No], sizeof(ENCOUNT_EFFECT_WORK), TCB_TSK_PRI, HEAPID_FIELD);
	eew = TCB_GetWork(tcb);
	eew->fsw = fsw;
	eew->end = end;		// 終了フラグ設定
	if(eew->end != NULL){
		*(eew->end) = FALSE;
	}
	eew->hblank_flg = FALSE;
}





//-----------------------------------------------------------------------------
//
//	最初のピカピカ用タスク開始関数
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	最初のフラッシュの表現をするタスクを実行する
 *					
 *@param	disp	メイン画面にかける:MASK_MAIN_DISPLAY
 *					サブ画面にかける:MASK_SUB_DISPLAY
 *					両画面にかける:MASK_DOUBLE_DISPLAY
 *
 *@param	end		終了したらTRUEを返すフラグ
 *@param	flash_num	フラッシュ回数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void EncountFlashTask(int disp, u32 bright_color, u32 sub_bright_color, BOOL* end, u32 flash_num )
{
	TCB_PTR tcb;
	BR_FLASH_TASK *eew;

	eew = sys_AllocMemory( HEAPID_FIELD, sizeof(BR_FLASH_TASK) );
	memset( eew, 0, sizeof(BR_FLASH_TASK) );
	TCB_Add( BR_FlashTask, eew, TCB_TSK_PRI );
	
	eew->end = end;		// 終了フラグ設定
	if(eew->end != NULL){
		*(eew->end) = FALSE;
	}
	eew->disp = disp;
	eew->end_bright = bright_color;
	eew->sub_bright = sub_bright_color;
	eew->flash_num	= flash_num;
}

//------------------------------------------------------------------
/**
 * 
 * エフェクト
 *
 * 最初のピカピカ表現
 * 
 * @param   tcb		タスクポインタ
 * @param   work	ワークポインタ
 *
 * @retval  none		
 *
 * ピカピカ　20シンク使用
 */
//------------------------------------------------------------------
static void BR_FlashTask(TCB_PTR tcb, void *work)
{
	BR_FLASH_TASK *eew = work;

	switch(eew->seq){
	case FADE_SUB_EFFECT:
		if(eew->disp == MASK_MAIN_DISPLAY){
			//ブラックアウト
//			ChangeBrightnessRequest( 40,-16,0, eew->plane, MASK_SUB_DISPLAY);
			ENC_ChangeMstBrightness( &eew->br_sub, 0, eew->sub_bright, MASK_SUB_DISPLAY, FLASH_EFF_SYNC_SUB );
		}else{
			if(eew->disp == MASK_SUB_DISPLAY){
				//ブラックアウト
//				ChangeBrightnessRequest(40,-16,0, eew->plane, MASK_MAIN_DISPLAY);
				ENC_ChangeMstBrightness( &eew->br_sub, 0, eew->sub_bright, MASK_MAIN_DISPLAY, FLASH_EFF_SYNC_SUB );
			}
		}
		eew->seq++;
		break;

	case FADE_EFFECT:
		//ホワイトアウト
//		ChangeBrightnessRequest(4,16,0,eew->plane,eew->disp);
		ENC_ChangeMstBrightness( &eew->br_main, 0, eew->end_bright, eew->disp, FLASH_EFF_SYNC_ONE );
		eew->seq++;
		break;
		
	case FADE_WAIT:
		if( ENC_ChangeMstBrightnessMain( &eew->br_main ) ){
			eew->seq++;
		}
		break;
	case FADE_RET_EFFECT:
		//ホワイトイン
//		ChangeBrightnessRequest(4,0,16,eew->plane,eew->disp);
		ENC_ChangeMstBrightness( &eew->br_main, eew->end_bright, 0, eew->disp, FLASH_EFF_SYNC_ONE );
		eew->seq++;
		break;
		
	case FADE_RET_WAIT:
		if( ENC_ChangeMstBrightnessMain( &eew->br_main ) ){
			
			eew->count++;
			if(eew->count==eew->flash_num){
				eew->seq = END_EFFECT;
			}else{
				eew->seq = FADE_EFFECT;
			}
		}
		break;
	case END_EFFECT:		// メインエフェクトに移動
		eew->seq = 0;
		eew->count = 0;

		if(eew->end != NULL){
			*(eew->end) = TRUE;		// タスク終了を報告
		}

		TCB_Delete(tcb);	//タスク終了
		sys_FreeMemoryEz( eew );
		return ;
	}

	// サブ面フェード
	ENC_ChangeMstBrightnessMain( &eew->br_sub );
}


//----------------------------------------------------------------------------
//
//
//	エフェクト用Hブランク関数郡
//
//
//============================================================================
// Hブランク終了チェック
//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク終了チェック
 *	@param	p_work 
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ENC_HBlankEndCheck( ENCOUNT_EFFECT_WORK* p_work )
{
	return p_work->hblank_flg;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG面を全て横にカットスタート
 *
 *@param	p_ew	ｴﾌｪｸﾄワーク
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_Cut_Start(ENCOUNT_EFFECT_WORK* p_ew)
{
	ENC_HB_BG_CUT* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_CUT) );
	memset( p_work, 0, sizeof(ENC_HB_BG_CUT) );
	FLDHBLANK_OBJ_Add( p_ew->fsw->fldmap->hblanksys, ENC_BG_Cut_HBlank, p_work );
	p_ew->hblank_flg = FALSE;
	p_work->end_check = &p_ew->hblank_flg;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG面を全て横にカットする
 *
 *@param	p_hobj	hブランクオブジェクト
 *@param	p_work	ワーク
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Cut_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_CUT* hbw = (ENC_HB_BG_CUT*)p_work;
	int v_count;		// Vカウント
	int	x_num;			// BGオフセットに設定する値

	// Vカウンタを取得し、０の時は移動値を計算する
	v_count = GX_GetVCount();
	if(v_count == 0){

		if((hbw->x + hbw->speed) <= ENC_HB_BG_CUT_END_X){
			hbw->x += hbw->speed;			// 移動
			hbw->speed += ENC_HB_BG_CUT_ST;	// 加速
		}else{
			
			*hbw->end_check = TRUE;
			FLDHBLANK_OBJ_Delete( p_hobj );
			sys_FreeMemoryEz( p_work );
			return ;
		}
	}

	// 96未満を左、96以上を右に移動させる
	x_num = hbw->x / 100;
	if(v_count >= 96){
		x_num = -x_num;
	}
	G2_SetBG0Offset(x_num, 0);
	G2_SetBG1Offset(x_num, 0);
	G2_SetBG2Offset(x_num, 0);
	G2_SetBG3Offset(x_num, 0);
}



//----------------------------------------------------------------------------
/**
 *	@brief	動作初期化
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_MoveReq( ENC_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_MoveMain( ENC_MOVE_WORK* p_work )
{
	int w_x;

	// 現在座標取得
	w_x = p_work->dis_x * p_work->count;
	w_x = w_x / p_work->count_max;

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作初期化
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_MoveReqFx( ENC_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
{
	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_MoveMainFx( ENC_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// 現在座標取得
	w_x = FX_Mul( p_work->dis_x, p_work->count << FX32_SHIFT );
	w_x = FX_Div( w_x, p_work->count_max << FX32_SHIFT );
	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	加速動作汎用　初期化
 *
 *	@param	p_work	ワーク
 *	@param	s_x		開始座標
 *	@param	e_x		終了座標
 *	@param	s_s		開始速度
 *	@param	count_max ｶｳﾝﾀ値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_AddMoveReqFx( ENC_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max )
{
	fx32 t_x_t;	// タイムの２乗
	fx32 vot;	// 初速度＊タイム
	fx32 dis;
	fx32 a;

	dis = e_x - s_x;
	
	// 加速値を求める
	// a = 2(x - vot)/(t*t)
	t_x_t = (count_max * count_max) << FX32_SHIFT;
	vot = FX_Mul( s_s, count_max * FX32_ONE );
	vot = dis - vot;
	vot = FX_Mul( vot, 2*FX32_ONE );
	a = FX_Div( vot, t_x_t );

	p_work->x = s_x;
	p_work->s_x = s_x;
	p_work->s_s = s_s;
	p_work->s_a = a;
	p_work->count = 0;
	p_work->count_max = count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	加速動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_AddMoveMainFx( ENC_ADDMOVE_WORK_FX* p_work )
{
	fx32 dis;
	fx32 t_x_t;
	fx32 calc_work;
	fx32 vot;
	
	// 等加速度運動
	// dis = vot + 1/2( a*(t*t) )
	vot = FX_Mul( p_work->s_s, p_work->count << FX32_SHIFT );
	t_x_t = (p_work->count * p_work->count) << FX32_SHIFT;
	calc_work = FX_Mul( p_work->s_a, t_x_t );
	calc_work = FX_Div( calc_work, 2*FX32_ONE );	// 1/2(a*(t*t))
	dis = vot + calc_work;	///<移動距離

	p_work->x = p_work->s_x + dis;


	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ﾏｽﾀｰブライトネス設定
 *
 *	@param	disp	面
 *	@param	no		値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_SetMstBrightness( int disp, int no )
{
	// ブライトネス解除
	if( disp == MASK_MAIN_DISPLAY ){
		GX_SetMasterBrightness(no);
	}else{
		GXS_SetMasterBrightness(no);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾏｽﾀｰブライトネス変更　フェードデータ格納
 *
 *	@param	p_data		格納先
 *	@param	start		開始値
 *	@param	end			終了値
 *	@param	disp		面
 *	@param	sync		シンク数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_ChangeMstBrightness( BR_BRIGHTNESS_FADE* p_data, int start, int end, int disp, int sync )
{
	p_data->disp = disp;
	ENC_MoveReq( &p_data->brightness, start, end, sync );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾏｽﾀｰブライトネス変更　フェードメイン
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_ChangeMstBrightnessMain( BR_BRIGHTNESS_FADE* p_data )
{
	BOOL result;
	result = ENC_MoveMain( &p_data->brightness );
	
	// Vブランク期間中に設定しないときれいにフェードしない
	VWaitTCB_Add( ENC_BrightnessVset, p_data, TCB_VWAIT_BR_TSK_PRI );
	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Vブランク期間中にﾌﾞﾗｲﾄﾈｽ値を設定するタスク
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *	Vブランク期間中に設定しないときれいにフェードしない
 */
//-----------------------------------------------------------------------------
static void ENC_BrightnessVset( TCB_PTR tcb, void* work )
{
	BR_BRIGHTNESS_FADE* p_data = work;
	ENC_SetMstBrightness( p_data->disp, p_data->brightness.x );
	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ワーク作成
 *
 *	@param	none
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_SLICE* ENC_BG_Slice_Alloc( void )
{
	ENC_HB_BG_SLICE* p_work;
	
	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_SLICE) );
	memset( p_work, 0, sizeof(ENC_HB_BG_SLICE) );

	// ウィンドウマスク設定
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	破棄
 *
 *	@param	p_work 
 *
 *	@return none	
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Delete( ENC_HB_BG_SLICE* p_work )
{
	if( p_work->p_hobj != NULL ){
		ENC_BG_Slice_End( p_work );
	}

	// ウィンドウマスク破棄
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGSlice開始
 *
 *	@param	p_ew	エフェクトワーク
 *	@param	p_eff	BGスライス
 *	@param	dot		分割ドット数	1ドットごとなら1
 *	@param	sync	エフェクト完了シンク数
 *	@param	s_x		開始x値
 *	@param	e_x		終了X値
 *	@param	s_s		初速度
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s )
{
	// 開始済み
	GF_ASSERT( p_eff->p_hobj == NULL );
	
	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->dot			= dot;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_AddMoveReqFx( &p_eff->move_x, s_x, e_x, s_s, sync );

	if( s_x >= 0 ){
		G2_SetWnd0Position( 0, 0, 255 - s_x, 192 );
		G2_SetWnd1Position( 0, 0, 1 + s_x, 192 );	// +1しないとあわない
	}else{
		G2_SetWnd0Position( 0, 0, 255 + s_x, 192 );
		G2_SetWnd1Position( 0, 0, 1 - s_x, 192 );	// +1しないとあわない
	}
	
	// 動さタスク登録関数
	VWaitTCB_Add( ENC_BG_Slice_SetUp_Tcb, p_eff, END_HB_BG_SLICE_INIT_TCB_PRI );
}

// 設定関数
static void ENC_BG_Slice_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_SLICE* p_eff = p_work;

	p_eff->tcb = VWaitTCB_Add( ENC_BG_Slice_Tcb, p_eff, END_HB_BG_SLICE_TCB_PRI );
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_Slice_HBlank, p_eff );

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	カットパラメータ変更関数
 *
 *	@param	p_ew	ワーク
 *	@param	p_work	ワーク
 *	@param	dot		ドット数
 *	@param	sync	シンク数
 *	@param	s_x		ｘ開始位置
 *	@param	e_x		ｘ終了位置
 *	@param	s_s		初速度
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_Slice_Change( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_work, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s )
{
	// もう終了済みならエラー
	GF_ASSERT( ENC_HBlankEndCheck( p_ew ) == FALSE );	

	p_work->dot			= dot;
	p_work->seq			= 0;
	ENC_AddMoveReqFx( &p_work->move_x, s_x, e_x, s_s, sync );
}


//----------------------------------------------------------------------------
/**
 *	@brief	BGスライスタスク
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_SLICE* p_data = p_work;
	s32 num;
	
	switch( p_data->seq ){
	case 0:
		if( ENC_AddMoveMainFx( &p_data->move_x ) ){
			p_data->seq ++;
		}
		num = p_data->move_x.x >> FX32_SHIFT;
		if( num >= 0 ){
			G2_SetWnd0Position( 0, 0, 255 - num, 192 );
			G2_SetWnd1Position( 0, 0, 1 + num, 192 );	// +1しないとあわない
		}else{
			G2_SetWnd0Position( 0, 0, 255 + num, 192 );
			G2_SetWnd1Position( 0, 0, 1 - num, 192 );	// +1しないとあわない
		}
		break;

	case 1:	// Hブランクで上の値が反映されるので１シンク待つ　終了
		ENC_BG_Slice_End( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGスライス終了
 *
 *	@param	p_work ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_End( ENC_HB_BG_SLICE* p_work )
{
	// ウィンドウマスク設定
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	G2_SetWnd0Position( 0,0,0,0 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BGスライス　Hブランクコールバック
 *
 *	@param	p_hobj	オブジェクト
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BG_Slice_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_SLICE* p_data = p_work;
	int v_count;		// Vカウント
	int	x_num;			// BGオフセットに設定する値

	// Vカウンタを取得し、０の時は移動値を計算する
	v_count = GX_GetVCount();
	
	if( ((v_count / p_data->dot) % 2) == 0 ){
		x_num = p_data->move_x.x >> FX32_SHIFT;
	}else{
		x_num = -p_data->move_x.x >> FX32_SHIFT;
	}
	G2_SetBG0Offset(x_num, 0);
	G2_SetBG1Offset(x_num, 0);
	G2_SetBG2Offset(x_num, 0);
	G2_SetBG3Offset(x_num, 0);

	if( x_num >= 0 ){
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	}else{
		GX_SetVisibleWnd( GX_WNDMASK_W1 );
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	}
}


//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief		ワーク確保
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_WND_SLANT* ENC_BG_WndSlant_Alloc( void )
{
	ENC_HB_BG_WND_SLANT* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_WND_SLANT) );
	memset( p_work, 0, sizeof(ENC_HB_BG_WND_SLANT) );
	
	// ウィンドウマスク設定
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWnd1InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief		ワーク破棄
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndSlant_Delete( ENC_HB_BG_WND_SLANT* p_work )
{
	if( p_work->p_hobj != NULL ){
		ENC_BG_WndSlant_End( p_work );
	}

	// ウィンドウマスク破棄
	GX_SetVisibleWnd( GX_WNDMASK_NONE );

	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief	開始
 *
 *	@param	p_ew		エンカウントエフェクトワーク
 *	@param	p_eff		エフェクトワーク
 *	@param	sync		シンク数
 *	@param	x_ss		X方向初速度
 *	@param	y_ss		Y方向初速度
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndSlant_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_SLANT* p_eff, u32 sync, fx32 x_ss, fx32 y_ss )
{
	// 開始済み
	GF_ASSERT( p_eff->p_hobj == NULL );
	
	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->cut_y		= END_HB_BG_WND_SLANT_CUT_Y;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_AddMoveReqFx( &p_eff->move_x, 0, END_HB_BG_WND_SLANT_MOVE_X, x_ss, sync );
	ENC_AddMoveReqFx( &p_eff->move_y, 0, END_HB_BG_WND_SLANT_MOVE_Y, y_ss, sync );

	G2_SetWnd0Position( 0, 0, 255, 192 );
	G2_SetWnd1Position( 0, 0, 255, 192 );
	
	// 動さタスク登録関数
	VWaitTCB_Add( ENC_BG_WndSlant_SetUp_Tcb, p_eff, END_HB_BG_WND_SLANT_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief	セットアップタスク
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_SLANT* p_eff = p_work;

	p_eff->tcb = VWaitTCB_Add( ENC_BG_WndSlant_Tcb, p_eff, END_HB_BG_WND_SLANT_TCB_PRI );
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_WndSlant_HBlank, p_eff );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief	動さタスク
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_SLANT* p_data = p_work;
	s32 x_num;
	s32 y_num;
	
	switch( p_data->seq ){
	case 0:
		ENC_AddMoveMainFx( &p_data->move_y );
		if( ENC_AddMoveMainFx( &p_data->move_x ) ){
			p_data->seq ++;
		}
		x_num = p_data->move_x.x >> FX32_SHIFT;
		y_num = p_data->move_y.x >> FX32_SHIFT;
		G2_SetWnd0Position( 0, 0, 255 - x_num, 96 - y_num );
		G2_SetWnd1Position( x_num, 96 + y_num, 255, 192);
		break;

	case 1:	// Hブランクで上の値が反映されるので１シンク待つ　終了
		ENC_BG_WndSlant_End( p_work );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief	Hブランク関数
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_WND_SLANT* p_data = p_work;
	int v_count;		// Vカウント
	int	x_num;			// BGオフセットに設定する値
	int	y_num;			// BGオフセットに設定する値

	// Vカウンタを取得し、０の時は移動値を計算する
	v_count = GX_GetVCount();
	
	if( v_count <= p_data->cut_y ){
		GX_SetVisibleWnd( GX_WNDMASK_W0 );
	}else{
		GX_SetVisibleWnd( GX_WNDMASK_W1 );
	}
}

//----------------------------------------------------------------------------
/**
 *		【ウィンドウ斜めカット】
 *	@brief	終了関数
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndSlant_End( ENC_HB_BG_WND_SLANT* p_work )
{
	// ウィンドウマスク設定
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );	
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_NONE, FALSE );	
	G2_SetWnd0Position( 0,0,0,0 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}




//----------------------------------------------------------------------------
/**
 *	@brief	アフィンBG設定
 *
 *	@param	p_bgl	BGL
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineCont( GF_BGL_INI* p_bgl )
{
	VWaitTCB_Add( ENC_BG_AffinContSetTcb, p_bgl, ENC_BG_AFFINCONT_TASK );
}

//----------------------------------------------------------------------------
/**
 *	@brief		あふぃんBG設定
 */
//-----------------------------------------------------------------------------
static void ENC_BG_AffinContSetTcb( TCB_PTR tcb, void* work )
{
	GF_BGL_INI* p_bgl = work;

	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_1,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );	

	{	// MAIN DISP（エフェクト１）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet( p_bgl, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, GF_BGL_FRAME1_M );
		// 表示OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	}

	{	// MAIN DISP（エフェクト２）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet( p_bgl, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, GF_BGL_FRAME2_M );
		// 表示OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	}

	{	// アフィンBG
		GF_BGL_BGCNT_HEADER AffBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			0, TRUE, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bgl, ENC_BG_AFFINE_FRAME );
		GF_BGL_BGControlSet( p_bgl, ENC_BG_AFFINE_FRAME, &AffBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ClearCharSet( ENC_BG_AFFINE_FRAME, 32, 0, HEAPID_FIELD );
		GF_BGL_ScrClear( p_bgl, ENC_BG_AFFINE_FRAME );

		// 表示OFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	アフィンBG設定
 *
 *	@param	scrn_idx		スクリーンインデックス
 *	@param	char_idx		キャラクタインデックス
 *	@param	pltt_idx		パレットインデックス
 *	@param	p_bgl			BGL
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, GF_BGL_INI* p_bgl )
{

	// グラフィック読み込み
	ArcUtil_PalSet( ARC_ENCOUNTEFFECT, pltt_idx, PALTYPE_MAIN_BG, 0, 0, HEAPID_FIELD );
	ArcUtil_BgCharSet( ARC_ENCOUNTEFFECT, char_idx, p_bgl, ENC_BG_AFFINE_FRAME, 0, 0, FALSE, HEAPID_FIELD );
	ArcUtil_ScrnSet( ARC_ENCOUNTEFFECT, scrn_idx, p_bgl, ENC_BG_AFFINE_FRAME, 0, 0, FALSE, HEAPID_FIELD );
}

//----------------------------------------------------------------------------
/**
 *	@brief	通常BG設定
 *
 *	@param	scrn_idx	スクリーンインデックス
 *	@param	char_idx	キャラクタインデックス
 *	@param	pltt_idx	パレットインデックス
 *	@param	pltt_no		パレットナンバー
 *	@param	pltt_num	パレット数
 *	@param	p_bgl		BGL
 *	@param	frame		BGフレーム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetNormalBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, u32 pltt_no, u32 pltt_num, GF_BGL_INI* p_bgl, u32 frame )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// グラフィック読み込み
	ArcUtil_PalSet( ARC_ENCOUNTEFFECT, pltt_idx, PALTYPE_MAIN_BG, pltt_no*32, pltt_num*32, HEAPID_FIELD );
	ArcUtil_BgCharSet( ARC_ENCOUNTEFFECT, char_idx, p_bgl, frame, 0, 0, FALSE, HEAPID_FIELD );

	// スクリーンデータ読み込み
	buff = ArcUtil_ScrnDataGet( ARC_ENCOUNTEFFECT, scrn_idx, FALSE, &p_scrn, HEAPID_FIELD );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bgl, frame,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	// パレットをあわせる
	GF_BGL_ScrPalChange( p_bgl, frame,
			0, 0, 
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8,
			pltt_no );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req( p_bgl, frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief		アフィンスクロール設定タスク
 */
//-----------------------------------------------------------------------------
static void ENC_BG_SetAffineMtxTcb( TCB_PTR tcb, void* p_work )
{
	ENC_BG_SET_AFFINEPARAM* p_data = p_work;

	GF_BGL_AffineScrollSet( p_data->p_bgl, p_data->frame, 
			GF_BGL_SCROLL_X_SET, p_data->sc_x,
			&p_data->mtx, p_data->cx, p_data->cy );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アフィンデータ設定関数
 *
 *	@param	p_bgl		BGL
 *	@param	frame		フレーム
 *	@param	scale_x		拡縮x
 *	@param	scale_y		拡縮y
 *	@param	rota		回転
 *	@param	cx			中心X　（ドット単位）
 *	@param	cy			中心Y　（ドット単位）
 *	@param	sc_x		スクロール座標
 *	@param	sc_y		スクロール座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BG_SetAffineMtx( ENC_BG_SET_AFFINEPARAM* p_work, GF_BGL_INI* p_bgl, u32 frame, fx32 scale_x, fx32 scale_y, u16 rota, int cx, int cy, int sc_x )
{
	
	MTX_Identity22( &p_work->mtx );

	// 拡大回転行列作成
	MTX_Rot22( &p_work->mtx, FX_SinIdx( rota ), FX_CosIdx( rota ) );
	MTX_ScaleApply22( &p_work->mtx, &p_work->mtx, FX_Div( FX32_ONE, scale_x ), FX_Div( FX32_ONE, scale_y ) );

	p_work->p_bgl	= p_bgl;
	p_work->frame	= frame;
	p_work->cx		= cx;
	p_work->cy		= cy;
	p_work->sc_x	= sc_x;
	VWaitTCB_Add( ENC_BG_SetAffineMtxTcb, p_work, ENC_BG_SET_AFFINE_MTX_PRI );
}


//-----------------------------------------------------------------------------
/**
 *
 *		OAM設定関連
 *
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターセットなど作成
 *
 *	@param	p_sys		ワーク
 *	@param	work_num	ワーク数
 *	@param	res_num		リソース数
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_Init( ENC_CLACT_SYS* p_sys, int work_num, int res_num )
{
	int i;
	
	// セルアクターセット作成
	p_sys->cas = CLACT_U_SetEasyInit( work_num, &p_sys->renddata, HEAPID_FIELD );

	// リソースマネージャ作成
	for( i=0; i<4; i++ ){
		p_sys->resMan[i] = CLACT_U_ResManagerInit( res_num, i, HEAPID_FIELD );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	システム情報破棄
 *
 *	@param	p_sys	システムワーク
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_Delete( ENC_CLACT_SYS* p_sys )
{
	int i;
	
	CLACT_DestSet( p_sys->cas );
	
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerDelete( p_sys->resMan[i] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	単純なリソース読み込み
 *
 *	@param	p_sys		管理システム
 *	@param	p_work		データ格納先
 *	@param	pltt_idx	パレット
 *	@param	pltt_num	パレット読み込み数
 *	@param	char_idx	キャラクタ
 *	@param	cel_idx		セル
 *	@param	anm_idx		アニメ
 *	@param	cont_id		管理ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResLoadEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id )
{
	// キャラクタ
	p_work->resobj[0] = CLACT_U_ResManagerResAddArcChar_AllocType( p_sys->resMan[0],
			ARC_ENCOUNTEFFECT, char_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD, ALLOC_BOTTOM );

	// パレット
	p_work->resobj[1] = CLACT_U_ResManagerResAddArcPltt( p_sys->resMan[1],
			ARC_ENCOUNTEFFECT, pltt_idx, FALSE, cont_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, pltt_num, HEAPID_FIELD );

	// セル
	p_work->resobj[2] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[2],
			ARC_ENCOUNTEFFECT, cel_idx, FALSE, cont_id,
			CLACT_U_CELL_RES, HEAPID_FIELD );

	// アニメ
	p_work->resobj[3] = CLACT_U_ResManagerResAddArcKindCell( p_sys->resMan[3],
			ARC_ENCOUNTEFFECT, anm_idx, FALSE, cont_id,
			CLACT_U_CELLANM_RES, HEAPID_FIELD );


	// Vram転送
	CLACT_U_CharManagerSetAreaCont( p_work->resobj[0] );	
	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[0] );
	CLACT_U_PlttManagerSetCleanArea( p_work->resobj[1] );	
//	CLACT_U_ResManagerResOnlyDelete( p_work->resobj[1] );
//	パレットは破棄しない、途中でパレットを変更することがあるため

	// ヘッダー作成
	CLACT_U_MakeHeader( &p_work->head,
			cont_id, cont_id, cont_id, cont_id,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_sys->resMan[0], p_sys->resMan[1], 
			p_sys->resMan[2], p_sys->resMan[3], NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	単純リソース破棄
 *
 *	@param	p_sys	システムワーク
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResDeleteEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work )
{
	int i;
	CLACT_U_CharManagerDelete( p_work->resobj[0] );
	CLACT_U_PlttManagerDelete( p_work->resobj[1] );

	// リソース完全破棄
	for( i=0; i<4; i++ ){
		CLACT_U_ResManagerResDelete( p_sys->resMan[i], p_work->resobj[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カラーパレット変更
 *
 *	@param	clact		セルアクターワーク
 *	@param	p_work		ワーク
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResColorChange( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb )
{
	SOFT_SPRITE_ARC ssa;
	NNSG2dPaletteData* p_pltt;
	void* p_pltt_buff;
	u16* dest;

	TrTypeGraArcDataGet( &ssa, tr_type );

	// データ作成先
	dest = sys_AllocMemory( heap, 32 );

	// キャラクタとパレット取得
	p_pltt_buff = ArcUtil_PalDataGet( ssa.arc_no, ssa.index_pal, &p_pltt, heap );

	SoftFade( p_pltt->pRawData, dest, 16, evy, next_rgb );

	// パレット転送
	ENC_OAM_TransOamPltt( clact, dest, 32 );

	sys_FreeMemoryEz( dest );
	sys_FreeMemoryEz( p_pltt_buff );
}


//----------------------------------------------------------------------------
/**
 *	@brief	アクター登録
 *
 *	@param	p_sys		システムワーク
 *	@param	p_work		リソースワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	z			ｚ座標
 *	@param	pri			優先順位
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
CLACT_WORK_PTR ENC_CLACT_Add( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri )
{
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;

	add.ClActSet	= p_sys->cas;
	add.ClActHeader	= &p_work->head;
	add.mat.x		= x;
	add.mat.y		= y;
	add.mat.z		= z;
	add.pri			= pri;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= HEAPID_FIELD;

	act = CLACT_AddSimple( &add );
	GF_ASSERT( act );
	return act;
} 

//----------------------------------------------------------------------------
/**
 *	@brief	ベクトル作成
 *
 *	@param	x	ｘ値
 *	@param	y	ｙ値
 *	@param	z	ｚ値
 *
 *	@return	ベクトル
 */
//-----------------------------------------------------------------------------
VecFx32 ENC_MakeVec( fx32 x, fx32 y, fx32 z )
{
	VecFx32 vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのキャラクタとパレットをトレーナーの者にする
 *
 *	@param	clact		セルデータ
 *	@param	heap		ヒープ
 *	@param	tr_type		トレーナータイプ
 *
 *	@param ofs_cx		切り取るXキャラクタオフセット値
 */
//-----------------------------------------------------------------------------
void ENC_CLACT_ResSetSoftSpriteDataTrOam( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb, u32 ofs_cx )
{
	SOFT_SPRITE_ARC ssa;
	void* p_char;
	NNSG2dCharacterData* p_chardata;
	u32* p_charbuff; 
	u32 size;
		
	TrTypeGraArcDataGet( &ssa, tr_type );

	// キャラクタとパレット取得
	p_char = ArcUtil_CharDataGet( ssa.arc_no, ssa.index_chr, FALSE, &p_chardata, heap );

	// 復号
	SoftSpriteChrMask( (u8*)p_chardata->pRawData );

	// パレットはこの処理で行う
	ENC_CLACT_ResColorChange( clact, heap, tr_type, evy, next_rgb );
	
	// OAM用キャラクタデータ生成
	p_charbuff = ENC_OAM_TrCharMake( p_chardata, heap, &size, ofs_cx );

	// キャラクタ転送
	ENC_OAM_TransOamChar( clact, p_charbuff, size );

	sys_FreeMemoryEz( p_charbuff );
	sys_FreeMemoryEz( p_char );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カット引用OAMキャラクタの生成
 *
 *	@param	p_chardata		ソフトウェアスプライト用キャラクタデータ
 *	@param	heap			ヒープ
 *	@param	ofs_cx			これだけずらしたところから抜き出す
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void* ENC_OAM_TrCharMake( const NNSG2dCharacterData* cp_chardata, u32 heap, u32* p_size, u32 ofs_cx )
{
	u32 * p_charbuff;
	int i, j;
	int char_idx;
	int raw_char_idx;
	const u32 * cp_char_raw = cp_chardata->pRawData; 

	p_charbuff = sys_AllocMemory( heap, ENC_OAM_TR_CHAR_BUFF_SIZE );


	for( i=0; i<ENC_OAM_TR_CHAR_SIZE_Y; i++ ){
		raw_char_idx = ((i+ENC_OAM_TR_CHAR_CUT_Y) * cp_chardata->W );
		char_idx = ((i/8)*ENC_OAM_TR_CHAR_ONELINE) + (i%8);

		for( j=0; j<ENC_OAM_TR_CHAR_SIZE_X / 8; j++ ){
			p_charbuff[ char_idx + (j*8) ] = cp_char_raw[ raw_char_idx + j + ofs_cx ];
		}
	}

	*p_size = ENC_OAM_TR_CHAR_BUFF_SIZE;

	return p_charbuff;
}

//----------------------------------------------------------------------------
/**
 *	@brief		OAMのパレット再転送
 *
 */
//-----------------------------------------------------------------------------
static void ENC_OAM_TransOamPltt( CLACT_WORK_PTR clact, void* data, u32 size )
{
	NNSG2dImagePaletteProxy * pltt;

	pltt = CLACT_PaletteProxyGet( clact );
	DC_FlushRange( data, size );
	GX_LoadOBJPltt( 
			data,
			NNS_G2dGetImagePaletteLocation( pltt, NNS_G2D_VRAM_TYPE_2DMAIN ),
			size );
}

//----------------------------------------------------------------------------
/**
 *	@brief		キャラクタデータ再転送
 */
//-----------------------------------------------------------------------------
static void ENC_OAM_TransOamChar( CLACT_WORK_PTR clact, void* data, u32 size )
{
	NNSG2dImageProxy * p_char;

	p_char = CLACT_ImageProxyGet( clact );
	DC_FlushRange( data, size );
	GX_LoadOBJ( 
			data,
			NNS_G2dGetImageLocation( p_char, NNS_G2D_VRAM_TYPE_2DMAIN ),
			size );
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップウィンドウ塗りつぶしオブジェクト】
 *	@brief	ワークの確保
 *
 *	@param	heapID	ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_OBJ* ENC_BMP_FillObjAlloc( u32 heapID )
{
	ENC_BMP_FILL_OBJ* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FILL_OBJ) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_OBJ) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップウィンドウ塗りつぶしオブジェクト】
 *	@brief	ワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillObjDelete( ENC_BMP_FILL_OBJ* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップウィンドウ塗りつぶしオブジェクト】
 *	@brief	動さ開始
 *
 *	@param	p_work		ワーク
 *	@param	s_x			塗りつぶし開始ｘ座標
 *	@param	e_x			塗りつぶし終了ｘ座標
 *	@param	s_y			塗りつぶし開始ｙ座標
 *	@param	e_y			塗りつぶし終了ｙ座標
 *	@param	sync		シンク数
 *	@param	p_bmp		ビットマップ
 *	@param	width		幅
 *	@param	height		高さ
 *	@param	col			塗りつぶすパレット番号
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillObjStart( ENC_BMP_FILL_OBJ* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col )
{
	GF_ASSERT( p_work->move_flg == FALSE );

	// 動さパラメータ
	ENC_MoveReq( &p_work->move_x, s_x, e_x, sync );
	ENC_MoveReq( &p_work->move_y, s_y, e_y, sync );

	// その他パラメータ
	p_work->p_bmp	= p_bmp;	// 塗りつぶすビットマップ
	p_work->width	= width;	// 塗りつぶし幅
	p_work->height	= height;	// 塗りつぶし高さ
	p_work->col		= col;		// 塗りつぶしカラー番号

	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップウィンドウ塗りつぶしオブジェクト】
 *	@brief	動さメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillObjMain( ENC_BMP_FILL_OBJ* p_work )
{
	BOOL result;
	s16 top, bottom, left, right;
	if( p_work->move_flg == FALSE ){
		return TRUE;
	}
	
	result = ENC_MoveMain( &p_work->move_x );
	ENC_MoveMain( &p_work->move_y );

	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;

	// ビットマップ塗りつぶし
	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, p_work->col );

	return result;
}


//----------------------------------------------------------------------------
/**
 *		【ビットマップブロック上塗りつぶしオブジェクト】
 *	@brief	ワークの確保
 *
 *	@param	heapID	ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_BLOCK* ENC_BMP_FillBlockAlloc( u32 heapID )
{
	ENC_BMP_FILL_BLOCK* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FILL_BLOCK) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_BLOCK) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップブロック上塗りつぶしオブジェクト】
 *	@brief	ワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockDelete( ENC_BMP_FILL_BLOCK* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップブロック上塗りつぶしオブジェクト】
 *	@brief	動さ開始
 *
 *	@param	p_work		ワーク
 *	@param	s_x			塗りつぶし開始ｘ座標
 *	@param	e_x			塗りつぶし終了ｘ座標
 *	@param	s_y			塗りつぶし開始ｙ座標
 *	@param	e_y			塗りつぶし終了ｙ座標
 *	@param	sync		シンク数
 *	@param	p_bmp		ビットマップ
 *	@param	width		幅
 *	@param	height		高さ
 *	@param	col			塗りつぶすパレット番号
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockStart( ENC_BMP_FILL_BLOCK* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col )
{
	GF_ASSERT( p_work->move_flg == FALSE );

	// 動さパラメータ
	ENC_MoveReq( &p_work->move_x, s_x, e_x, sync );
	ENC_MoveReq( &p_work->move_y, s_y, e_y, sync );

	// その他パラメータ
	p_work->p_bmp	= p_bmp;	// 塗りつぶすビットマップ
	p_work->width	= width;	// 塗りつぶし幅
	p_work->height	= height;	// 塗りつぶし高さ
	p_work->col		= col;		// 塗りつぶしカラー番号

	p_work->move_flg = TRUE;
}

//----------------------------------------------------------------------------
/**
 *		【ビットマップブロック上塗りつぶしオブジェクト】
 *	@brief	動さメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillBlockMain( ENC_BMP_FILL_BLOCK* p_work )
{
	BOOL result;
	s16 top, bottom, left, right;
	if( p_work->move_flg == FALSE ){
		return TRUE;
	}

	// 1つ前を消す
	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;
	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, 0 );
	
	result = ENC_MoveMain( &p_work->move_x );
	ENC_MoveMain( &p_work->move_y );

	left = p_work->move_x.x - (p_work->width/2);
	top = p_work->move_y.x - (p_work->height/2);
	right = left + p_work->width;
	bottom = top + p_work->height;

	ENC_BMP_Fill( p_work->p_bmp, top, bottom, left, right, p_work->col );

	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ塗りつぶし　矩形
 *
 *	@param	p_bmp		ワーク
 *	@param	top			上
 *	@param	bottom		下
 *	@param	left		左
 *	@param	right		右
 *	@param	col			カラー番号
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ENC_BMP_Fill( GF_BGL_BMPWIN* p_bmp, s32 top, s32 bottom, s32 left, s32 right, u8 col )
{
	// 画面外チェック
	if( (right <= 0) || (bottom <= 0) ){
		return ;
	}

	// 一緒なら描画しない
	if( (left == right) || (top == bottom) ){
		return ;
	}
	
	if( left < 0 ){
		left = 0;
	}
	if( right > 256 ){
		right = 256;
	}
	if( top < 0 ){
		top = 0;
	}
	if( bottom > 256 ){
		bottom = 256;
	}

	// ビットマップ塗りつぶし
	GF_BGL_BmpWinFill( p_bmp, col,
			left,
			top,
			right - left,
			bottom - top );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ワーク確保
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_BMP_FILL_BLOCK_MOVE* ENC_BMP_FillBlockMoveAlloc( u32 heapID )
{
	ENC_BMP_FILL_BLOCK_MOVE* p_work;
	int i;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_BMP_FILL_BLOCK_MOVE) );
	memset( p_work, 0, sizeof(ENC_BMP_FILL_BLOCK_MOVE) );

	// オブジェクト作成
	for( i=0; i<ENCOUNT_BLOCK_MOVE_OBJNUM; i++ ){
		p_work->p_block[i] = ENC_BMP_FillBlockAlloc( heapID );
	}
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockMoveDelete( ENC_BMP_FILL_BLOCK_MOVE* p_work )
{
	int i;
	
	// ブロックオブジェ破棄
	for( i=0; i<ENCOUNT_BLOCK_MOVE_OBJNUM; i++ ){
		ENC_BMP_FillBlockDelete( p_work->p_block[i] );
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	動さ開始
 *	
 *	@param	p_work	ワーク
 *	@param	sync	１つのオブジェが動くシンク数
 *	@param	start	１つのオブジェ発射タイミング
 *	@param	p_bmp	ビットマップ
 *	@param	col		カラー
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FillBlockMoveStart( ENC_BMP_FILL_BLOCK_MOVE* p_work, u8 sync, u8 start, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	p_work->p_bmp		= p_bmp;
	p_work->col			= col;
	p_work->move_sync	= sync;
	p_work->start_sync	= start;
	p_work->block_count = 0;
	p_work->block_end_count = 0;
	p_work->wait		= 0;
	p_work->init_flg	= 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン関数
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FillBlockMoveMain( ENC_BMP_FILL_BLOCK_MOVE* p_work )
{
	int x, s_y, e_y;
	int i;
	BOOL result;
	
	if( p_work->init_flg == 0 ){
		return TRUE;
	}
	
	// 発射部
	if( p_work->block_count < ENCOUNT_BLOCK_MOVE_OBJNUM ){
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->wait = p_work->start_sync;

			x = ENCOUNT_BLOCK_MOVE_MoveParam[ p_work->block_count % ENCOUNT_BLOCK_MOVE_X_NUM ];
			x = (ENCOUNT_BLOCK_MOVE_WIDTH/2) + (x * ENCOUNT_BLOCK_MOVE_WIDTH);
			s_y = ENCOUNT_BLOCK_MOVE_MAT_Y - ((p_work->block_count/ENCOUNT_BLOCK_MOVE_X_NUM) * ENCOUNT_BLOCK_MOVE_HEIGHT);
			e_y = ENCOUNT_BLOCK_MOVE_MOVE_Y - ((p_work->block_count/ENCOUNT_BLOCK_MOVE_X_NUM) * ENCOUNT_BLOCK_MOVE_HEIGHT);
			// 発射
			ENC_BMP_FillBlockStart( 
					p_work->p_block[ p_work->block_count ],
					x, x,
					s_y, e_y,
					p_work->move_sync, p_work->p_bmp,
					ENCOUNT_BLOCK_MOVE_WIDTH, ENCOUNT_BLOCK_MOVE_HEIGHT,
					p_work->col );

			p_work->block_count ++;
		}
	}
	

	// 動さ部
	for( i=p_work->block_end_count; i<p_work->block_count; i++ ){
		result = ENC_BMP_FillBlockMain( p_work->p_block[i] );
		if( result == TRUE ){
			p_work->block_end_count++;
		}
	}

	// 全動さ終了チェック
	if( (p_work->block_end_count >= ENCOUNT_BLOCK_MOVE_OBJNUM) &&
		(result == TRUE) ){
		p_work->init_flg = FALSE;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【円形　BMP　塗りつぶしオブジェ】
 *	@brief	ワーク確保
 *
 *	@param	heapID	ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_BMP_CIRCLE_FILL* ENC_BMP_CircleFillAlloc( u32 heapID )
{
	ENC_BMP_CIRCLE_FILL* p_work;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_CIRCLE_FILL) );
	memset( p_work, 0, sizeof(ENC_BMP_CIRCLE_FILL) );
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		【円形　BMP　塗りつぶしオブジェ】
 *	@brief	ワーク破棄
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BMP_CircleFillDelete( ENC_BMP_CIRCLE_FILL* p_work )
{
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		【円形　BMP　塗りつぶしオブジェ】
 *	@brief	エフェクト開始
 *
 *	@param	p_work	ワーク
 *	@param	sync	シンク数
 *	@param	s_rota	開始回転角		(反転して反対側も作成するため 0～179の角度)
 *	@param	e_rota	終了回転角		(反転して反対側も作成するため 0～179の角度)
 *	@param	p_bmp	ビットマップ
 *	@param	col		塗りつぶしカラー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BMP_CircleFillStart( ENC_BMP_CIRCLE_FILL* p_work, u8 sync, u16 s_rota, u16 e_rota, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	p_work->p_bmp		= p_bmp;
	p_work->col			= col;
	p_work->move_flg	= 1;
	ENC_MoveReq( &p_work->rota, s_rota, e_rota, sync );
}

//----------------------------------------------------------------------------
/**
 *		【円形　BMP　塗りつぶしオブジェ】
 *	@brief	メイン関数
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_CircleFillMain( ENC_BMP_CIRCLE_FILL* p_work )
{
	BOOL result;
	u16 last_rota;
	
	if( p_work->move_flg == 0 ){
		return TRUE;
	}

	// 前の角度
	last_rota = p_work->rota.x;

	// 実行
	result = ENC_MoveMain( &p_work->rota );

	// 描画処理
	EncBmpCircleFill_Fill( p_work->p_bmp, last_rota, p_work->rota.x, p_work->col );	

	if( result == TRUE ){
		p_work->move_flg = 0;
		return TRUE;
	}
	return FALSE;
}

// タンジェント計算
static inline fx32 getTanX( u16 rota )
{
	return FX_Div(FX_SinIdx(rota), FX_CosIdx(rota));
}

//----------------------------------------------------------------------------
/**
 *		【円形　BMP　塗りつぶしオブジェ】
 *	@brief	円形　ビットマップ塗りつぶし　実動さ
 *
 *	@param	p_bmp		ビットマップウィンドウ
 *	@param	last_rota	前の角度
 *	@param	now_rota	今の角度
 *	@param	col			カラー
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EncBmpCircleFill_Fill( GF_BGL_BMPWIN* p_bmp, u16 last_rota, u16 now_rota, u8 col )
{
	int now_x, last_x, tmp;
	int re_now_x, re_last_x;	// フリップ
	int i;
	int y;
	fx32 now_tan_x, last_tan_x;

	// タンジェント値を求める
	now_tan_x = getTanX( now_rota );
	last_tan_x = getTanX( last_rota );

	// 各高さでのX座標を求めその値で塗りつぶす
	for( i=0; i<96; i++ ){

		y = 95 - i;

		now_x = FX_Mul( now_tan_x, y*FX32_ONE ) >> FX32_SHIFT;
		last_x = FX_Mul( last_tan_x, y*FX32_ONE ) >> FX32_SHIFT;

		// 中心座標からの値にする
		re_now_x = 128 + now_x;
		re_last_x = 128 + last_x;
		now_x = 128 - now_x;
		last_x = 128 - last_x;

		//　だいしょうを整える
		if( last_x > now_x ){
			tmp = last_x;
			last_x = now_x;
			now_x = tmp;
		}
		if( re_last_x > re_now_x ){
			tmp = re_last_x;
			re_last_x = re_now_x;
			re_now_x = tmp;
		}

//		OS_Printf( "left %d right %d now_rota %d last_rota %d\n", last_x, now_x, now_rota / 182, last_rota / 182 );

		
		
		ENC_BMP_Fill( p_bmp, i, i+1, last_x, now_x+1, col );
		ENC_BMP_Fill( p_bmp, 191 - i, 192 - i, re_last_x, re_now_x+1, col );
	}
}


//----------------------------------------------------------------------------
/**
 *		【フラッシュアウト】
 *	@brief	ワーク確保
 *	
 *	@param	heapID	ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
ENC_BMP_FLASH_OUT* ENC_BMP_FlashOutAlloc( u32 heapID )
{
	ENC_BMP_FLASH_OUT* p_work;
	int i;

	p_work = sys_AllocMemory( heapID, sizeof(ENC_BMP_FLASH_OUT) );
	memset( p_work, 0, sizeof(ENC_BMP_FLASH_OUT) );
	
	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		p_work->p_circle[i] =  ENC_BMP_CircleFillAlloc( heapID );
	}
	
	return p_work;
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュアウト】
 *	@brief	ワーク破棄
 *
 *	@param	p_work ワーク
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FlashOutDelete( ENC_BMP_FLASH_OUT* p_work )
{
	int i;

	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		ENC_BMP_CircleFillDelete( p_work->p_circle[i] );
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュアウト】
 *	@brief	エフェクト開始
 *
 *	@param	p_work	ワーク
 *	@param	sync	シンク数
 *	@param	p_bmp	ビットマップ
 *	@param	col		塗りつぶしカラー番号
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_BMP_FlashOutStart( ENC_BMP_FLASH_OUT* p_work, u8 sync, GF_BGL_BMPWIN* p_bmp, u8 col )
{
	int i;

	// 塗りつぶしオブジェクト初期化
	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		ENC_BMP_CircleFillStart( p_work->p_circle[i],
				sync, 
				FX_GET_ROTA_NUM( FlashOutParam[i][0] ), 
				FX_GET_ROTA_NUM( FlashOutParam[i][1] ), 
				p_bmp,
				col );
	}
	p_work->move_flg = 1;

	// 最初に93  99ドットを塗りつぶす
	ENC_BMP_Fill( p_bmp, 93, 99, 0, 256, col );
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュアウト】
 *	@brief	フラッシュアウトメイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL ENC_BMP_FlashOutMain( ENC_BMP_FLASH_OUT* p_work )
{
	int i;
	BOOL result;
	
	if( p_work->move_flg == 0 ){
		return TRUE;
	}

	for( i=0; i<ENC_BMP_FLASH_CIRCLE_NUM; i++ ){
		result = ENC_BMP_CircleFillMain( p_work->p_circle[i] );
	}

	if( result == TRUE ){
		p_work->move_flg = 0;
		return TRUE;
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	ぎざぎざウィンドウ動さ
 */
//-----------------------------------------------------------------------------
ENC_HB_BG_WND_ZIGUZAGU* ENC_BG_WndZiguzagu_Alloc( void )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_work;

	p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(ENC_HB_BG_WND_ZIGUZAGU) );
	memset( p_work, 0, sizeof(ENC_HB_BG_WND_ZIGUZAGU) );

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	ワークの破棄
 *
 *	@param	p_work 
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndZiguzagu_Delete( ENC_HB_BG_WND_ZIGUZAGU* p_work )
{
	if( p_work->tcb != NULL ){
		ENC_BG_WndZiguzagu_End( p_work );	
	}
	sys_FreeMemoryEz( p_work );
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	関数開始
 *
 *	@param	p_ew		エンカウントエフェクトワーク
 *	@param	p_eff		エフェクトワーク
 *	@param	sync		シンク数
 *	@param	dot			左右切り替えドット数
 *	@param	width		左右幅
 *	@param	wnd_msgk_in		ウィンドウマスク	中
 *	@param	wnd_msgk_out	ウィンドウマスク	外
 */
//-----------------------------------------------------------------------------
void ENC_BG_WndZiguzagu_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_ZIGUZAGU* p_eff, u32 sync, u32 dot, u32 width, u32 wnd_msk_in, u32 wnd_msk_out )
{
	int i;
	int count;
	int set_w;
	
	// 開始済み
	GF_ASSERT( p_eff->tcb == NULL );

	p_ew->hblank_flg	= FALSE;
	p_eff->p_hsys		= p_ew->fsw->fldmap->hblanksys;
	p_eff->seq			= 0;
	p_eff->end_check	= &p_ew->hblank_flg;
	ENC_MoveReq( &p_eff->move_x, ENC_BG_WND_ZIGUZAGU_MOVE_S, ENC_BG_WND_ZIGUZAGU_MOVE_E, sync );
	
	// ジグザグ作成
	for( i=0; i<192; i++ ){
		// 設定幅を求める
		count = i % dot;
		set_w = count * width;
		set_w = set_w / dot;

		// ジグザグに設定
		if( ((i/dot) % 2) == 0 ){
			p_eff->ziguzagu_buf[ i ] = set_w;
		}else{
			p_eff->ziguzagu_buf[ i ] = width - set_w;
		}
	}

	// ウィンドウマスク設定
	G2_SetWnd0InsidePlane( wnd_msk_in, TRUE );
	G2_SetWndOutsidePlane( wnd_msk_out, FALSE );	
	G2_SetWnd0Position( 0, 0, 0, 192 );
	GX_SetVisibleWnd( GX_WNDMASK_W0 );

	// 初期化タスク生成
	VWaitTCB_Add( ENC_BG_WndZiguzagu_SetUp_Tcb, p_eff, END_HB_BG_WND_ZIGUZAGU_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	ジグザグ動さタスク生成
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_SetUp_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;

	
	// Hブランク関数登録
	p_eff->p_hobj = FLDHBLANK_OBJ_Add( p_eff->p_hsys, ENC_BG_WndZiguzagu_HBlank, p_eff );

	
	p_eff->tcb = VWaitTCB_Add( ENC_BG_WndZiguzagu_Tcb, p_eff, END_HB_BG_WND_ZIGUZAGU_TCB_PRI );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	メイン動さタスク
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_Tcb( TCB_PTR tcb, void* p_work )
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;
	BOOL result;

	switch( p_eff->seq ){
	case 0:
		result = ENC_MoveMain( &p_eff->move_x );
		if( result == TRUE ){
			p_eff->seq++;
		}
		break;

	case 1:
		ENC_BG_WndZiguzagu_End( p_eff );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	Hブランク関数
 */	
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_HBlank(FIELD_HBLANK_OBJ* p_hobj, void* p_work)
{
	ENC_HB_BG_WND_ZIGUZAGU* p_eff = p_work;
	int set_x;
	int v_count;		// Vカウント

	// Vカウンタを取得し、０の時は移動値を計算する
	v_count = GX_GetVCount();
	
	if( v_count < 192 ){
		set_x = p_eff->ziguzagu_buf[v_count] + p_eff->move_x.x;
		if( set_x > 255 ){
			set_x = 255;
		}
		G2_SetWnd0Position( 0, 0, set_x, 192 );
	}
}

//----------------------------------------------------------------------------
/**
 *	【ジグザグウィンドウ】
 *	@brief	終了処理
 */
//-----------------------------------------------------------------------------
static void ENC_BG_WndZiguzagu_End( ENC_HB_BG_WND_ZIGUZAGU* p_work )
{
	// ウィンドウマスク破棄
	GX_SetVisibleWnd( GX_WNDMASK_NONE );
	
	*(p_work->end_check) = TRUE;
	FLDHBLANK_OBJ_Delete( p_work->p_hobj );
	p_work->p_hobj = NULL;
	TCB_Delete( p_work->tcb );
	p_work->tcb = NULL;
}




//----------------------------------------------------------------------------
/**
 *	@brief	エンカウントエフェクトナンバー取得関数
 *
 *	@param	data	データ
 *
 *	@return	エンカウントエフェクトナンバー
 *
 *
 *	対応
 *		通信　バトルタワー
 *		ダブルバトル
 *		野生戦
 *		トレーナー戦
 *
 *	未対応
 *		特殊トレーナー
 *		特殊ポケモン
 */
//-----------------------------------------------------------------------------
#define ENCEFF_FIELD	(0)	// 野生戦
#define ENCEFF_TRAINER	(1)	// TRAINER戦
#define ENCEFF_GRASS	(0)	// 草
#define ENCEFF_WATER	(1)	// 水
#define ENCEFF_DAN		(2)	// ダンジョン
u32 ENCEFF_GetEffectNo( const BATTLE_PARAM * p_battleparam )
{
	int lv;
	int area;
	int type;
	POKEMON_PARAM* p_my_poke;
	POKEMON_PARAM* p_enemy_poke;
	int mypoke_lev, enemypoke_lev;

	// バトルﾀｲﾌﾟから大体を分岐させる
	if( p_battleparam->fight_type & FIGHT_TYPE_TRAINER ){
		
		type = ENCEFF_TRAINER;
		
	}else if( (p_battleparam->fight_type & (FIGHT_TYPE_MOVE|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_GET_DEMO)) ||
		(p_battleparam->fight_type == FIGHT_TYPE_YASEI) ){		// 野生は0なので&で取れないためこうする
		
		type = ENCEFF_FIELD;
	}else{

		GF_ASSERT( 0 );	// 対応していません。
		type = 0;
	}

	// フィールド（野生）　トレーナーのときは、レベルと地形から
	// エフェクトが変わる
	// レベルチェック
	p_my_poke = EvPoke_GetLivingPokemonTop( p_battleparam->poke_party[CLIENT_NO_MINE] );
	p_enemy_poke = EvPoke_GetLivingPokemonTop( p_battleparam->poke_party[CLIENT_NO_ENEMY] );
	mypoke_lev = PokeParaGet( p_my_poke, ID_PARA_level, NULL );
	enemypoke_lev = PokeParaGet( p_enemy_poke, ID_PARA_level, NULL );
	lv = enemypoke_lev - mypoke_lev;
	
	// エリアチェック
	switch( p_battleparam->ground_id ){
	case GROUND_ID_GRAVEL:
	case GROUND_ID_SANDS:
	case GROUND_ID_LAWN:
	case GROUND_ID_POOL:
	case GROUND_ID_ROCK:
	case GROUND_ID_SNOW:
	case GROUND_ID_ICE:
	case GROUND_ID_BOG:
	case GROUND_ID_BRIDGE:
	case GROUND_ID_FLOOR:
	case GROUND_ID_ALL:
		area = ENCEFF_GRASS * 2;	// lowとhiがあるから
		break;
	case GROUND_ID_WATER:
		area = ENCEFF_WATER * 2;	// lowとhiがあるから
		break;
	case GROUND_ID_CAVE:
		area = ENCEFF_DAN * 2;	// lowとhiがあるから
		break;
	}
	if( lv > 0 ){
		area ++;	// hiなので
	}

	return (type*6) + area;
} 


//----------------------------------------------------------------------------
/**
 *	@brief	OAM面をウィンドウを矩形で設定　拡大縮小可能
 *
 *	@param	y		中心ｙ
 *	@param	scale	拡縮値
 *	@param	height　高さ
 *	@param	bottom_y底辺までの長さ	底辺が高さの半分より小さいときがあるため
 *	@param	wndno	使用ウィンドウ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ENC_WND_SetScaleWnd( fx32 y, int bottom_y, fx32 scale, int height, int wndno, ENC_WND_SETPOSITION* p_work )
{
	int c_y;
	int set_height;

	c_y = (y>>FX32_SHIFT);

	set_height = FX_Mul( height*FX32_ONE, scale ) >> FX32_SHIFT;
	set_height /= 2;

	p_work->x1 = 0;
	p_work->x2 = 255;
	p_work->y1 = c_y - set_height;
	p_work->y2 = bottom_y;

	VWaitTCB_Add( ENC_WND_SetWndPositionVWait, p_work, ENC_SET_WND_SCALE_TCB_PRI );
}
//----------------------------------------------------------------------------
/**
 *	@brief	ツール　拡大率時の底辺の高さを求める
 *
 *	@param	scale			拡縮値
 *	@param	c_y				中心Y座標
 *	@param	half_height		底辺へのサイズ
 *
 *	@return		底辺座標
 */
//-----------------------------------------------------------------------------
int ENC_WND_SetScaleWndToolMakeBottomY( fx32 scale, int c_y, int half_height )
{
	half_height = FX_Mul( half_height * FX32_ONE, scale ) >> FX32_SHIFT;

	return c_y + half_height;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウポジション　Vブランク設定
 */
//-----------------------------------------------------------------------------
static void ENC_WND_SetWndPositionVWait( TCB_PTR tcb, void* p_work )
{
	ENC_WND_SETPOSITION* p_data = p_work;

	if( p_data->wnd_no == 0 ){
		// Vブランク期間に設定
		G2_SetWnd0Position( p_data->x1, p_data->y1, p_data->x2, p_data->y2  );
	}else{
		// Vブランク期間に設定
		G2_SetWnd1Position( p_data->x1, p_data->y1, p_data->x2, p_data->y2  );
	}

	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	VブランクMaster輝度設定関数
 */
//-----------------------------------------------------------------------------
static void EncSetMstBrightnessSetVTcb( TCB_PTR tcb, void* p_work )
{
	int * p_data = p_work;
	GX_SetMasterBrightness( *p_data );
	TCB_Delete(tcb);
}

//----------------------------------------------------------------------------
/**
 *	@brief	VブランクMaster輝度設定関数
 *	@param	p_setnum	設定数参照ポインタ
 */
//-----------------------------------------------------------------------------
void ENC_SetMasterBrightnessVblank( int* p_setnum )
{
	VWaitTCB_Add( EncSetMstBrightnessSetVTcb, p_setnum, ENC_SET_MSTBRI_TCB_PRI );	
}
