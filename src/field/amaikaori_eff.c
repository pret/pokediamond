//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		amaikaori_eff.c
 *	@brief		甘い香りエフェクト
 *	@author		tomoya takahashi
 *	@data		2006.05.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldmap_work.h"
#include "weather_sys.h"
#include "fieldmap.h"
#include "src/fielddata/script/common_scr_def.h"
#include "script.h"
#include "include/system/snd_tool.h"
#include "zonedata.h"

#define	__AMAIKAORI_EFF_H_GLOBAL
#include "amaikaori_eff.h"
#include "encount_set.h"

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
#define AMAIKAORI_USE_BG_MSK	( GX_PLANEMASK_BG2 )
#define AMAIKAORI_USE_BG_FRM	( FLD_MBGFRM_EFFECT2 )
#define AMAIKAORI_USE_PLTT		( 6 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	動作ワーク
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} AMAIKAORI_MOVE_WORK;

//-------------------------------------
//	甘い香りワーク
//=====================================
typedef struct {
	AMAIKAORI_MOVE_WORK alpha;
	BOOL end;
} AMAIKAORI_WORK;

#ifdef FIELD_AMAIKAORI_DEBUG
static int AMAIKAORI_ALPHA_S =		(0);
static int AMAIKAORI_ALPHA_E =		(10);
static int AMAIKAORI_ALPHA_COUNT =	( 19 );
static int AMAIKAORI_ALPHA_COUNT_END =	( 15 );
static int AMAIKAORI_EVENT_WEATHER_COMM_WAIT =	( 20 );
static int AMAIKAORI_EVENT_ALPHA_MAX_WAIT =	( 22 );
static int AMAIKAORI_DEBUG_SEQ = (0);
#else
#define AMAIKAORI_ALPHA_S			(0)
#define AMAIKAORI_ALPHA_E			(10)
#define AMAIKAORI_ALPHA_COUNT		( 19 )
#define AMAIKAORI_ALPHA_COUNT_END	( 15 )
#define AMAIKAORI_EVENT_WEATHER_COMM_WAIT	( 20 )
#define AMAIKAORI_EVENT_ALPHA_MAX_WAIT	( 22 )
#endif
#define AMAIKAORI_TSK_PRI			( 1024 )

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void Amaikaori_SetUpBG( GF_BGL_INI* bg_ini );
static void AmaikaoriMoveReq( AMAIKAORI_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
static BOOL	AmaikaoriMoveMain( AMAIKAORI_MOVE_WORK* p_work );

#ifdef FIELD_AMAIKAORI_DEBUG
void AmaikaoriDebugMain( TCB_PTR tcb, void* p_work )
{
	if( sys.trg & PAD_BUTTON_SELECT ){
		AMAIKAORI_DEBUG_SEQ = (AMAIKAORI_DEBUG_SEQ + 1) % 6;
		switch( AMAIKAORI_DEBUG_SEQ ){
		case 0:
			OS_Printf( "開始α値\n" );
			break;

		case 1:
			OS_Printf( "終了α値\n" );
			break;

		case 2:
			OS_Printf( "α加算ｶｳﾝﾀ\n" );
			break;

		case 3:
			OS_Printf( "α減算ｶｳﾝﾀ\n" );
			break;

		case 4:
			OS_Printf( "天気でだめなときのコメント待ち\n" );
			break;
			
		case 5:
			OS_Printf( "α最大時のウエイト\n" );
			break;
		}
	}

	if( sys.trg & PAD_BUTTON_L ){
		OS_Printf( "全データ表示\n" );
		OS_Printf( "開始α値 %d\n", AMAIKAORI_ALPHA_S );
		OS_Printf( "終了α値 %d\n", AMAIKAORI_ALPHA_E );
		OS_Printf( "α加算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT );
		OS_Printf( "α減算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT_END );
		OS_Printf( "天気でだめなときのコメント待ち %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
	}
	
	switch( AMAIKAORI_DEBUG_SEQ ){
	case 0:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_S ++;
			OS_Printf( "開始α値 %d\n", AMAIKAORI_ALPHA_S );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_S --;
			OS_Printf( "開始α値 %d\n", AMAIKAORI_ALPHA_S );
		}
		break;

	case 1:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_E ++;
			OS_Printf( "終了α値 %d\n", AMAIKAORI_ALPHA_E );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_E --;
			OS_Printf( "終了α値 %d\n", AMAIKAORI_ALPHA_E );
		}
		break;

	case 2:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_COUNT ++;
			OS_Printf( "α加算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_COUNT --;
			OS_Printf( "α加算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT );
		}
		break;

	case 3:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_ALPHA_COUNT_END ++;
			OS_Printf( "α減算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT_END );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_ALPHA_COUNT_END --;
			OS_Printf( "α減算ｶｳﾝﾀ %d\n", AMAIKAORI_ALPHA_COUNT_END );
		}
		break;

	case 4:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_EVENT_WEATHER_COMM_WAIT ++;
			OS_Printf( "天気でだめなときのコメント待ち %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_EVENT_WEATHER_COMM_WAIT --;
			OS_Printf( "天気でだめなときのコメント待ち %d\n", AMAIKAORI_EVENT_WEATHER_COMM_WAIT );
		}
		break;
	case 5:
		if( sys.repeat & PAD_BUTTON_A ){
			AMAIKAORI_EVENT_ALPHA_MAX_WAIT ++;
			OS_Printf( "α最大値時のウエイト %d\n", AMAIKAORI_EVENT_ALPHA_MAX_WAIT );
		}else if( sys.repeat & PAD_BUTTON_Y ){
			AMAIKAORI_EVENT_ALPHA_MAX_WAIT --;
			OS_Printf( "α最大値時のウエイト %d\n", AMAIKAORI_EVENT_ALPHA_MAX_WAIT );
		}
		break;
	}
}
#endif



//----------------------------------------------------------------------------
/**
 *	@brief	初期化処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	AMAIKAORI_WORK* p_data = p_work;
	
	Amaikaori_SetUpBG( p_fsys->bgl );
	AmaikaoriMoveReq( &p_data->alpha, AMAIKAORI_ALPHA_S, AMAIKAORI_ALPHA_E, AMAIKAORI_ALPHA_COUNT );
	p_data->end = FALSE;
	// Alpha設定
	G2_SetBlendAlpha( AMAIKAORI_USE_BG_MSK, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD, AMAIKAORI_ALPHA_S, 16 - AMAIKAORI_ALPHA_S );

	
	GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 0 );

	// BGON
	GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_ON );

	// 音ならす  
	Snd_SePlay( SE_AMAIKAORI );
}
static void FLDMAP_AmaikaoriEndEff_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	AMAIKAORI_WORK* p_data = p_work;
	
	Amaikaori_SetUpBG( p_fsys->bgl );
	AmaikaoriMoveReq( &p_data->alpha, AMAIKAORI_ALPHA_E, AMAIKAORI_ALPHA_S, AMAIKAORI_ALPHA_COUNT_END );
	p_data->end = FALSE;
	// Alpha設定
	G2_SetBlendAlpha( AMAIKAORI_USE_BG_MSK, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BD, AMAIKAORI_ALPHA_E, 16 - AMAIKAORI_ALPHA_E );

	
}

//----------------------------------------------------------------------------
/**
 *	@brief	破棄処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{

}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	BOOL result;
	AMAIKAORI_WORK* p_data = p_work;

	if( p_data->end == TRUE ){
		return ;
	}

	result = AmaikaoriMoveMain( &p_data->alpha );
	if( result ){
		p_data->end = TRUE;
	}
	G2_ChangeBlendAlpha( p_data->alpha.x, 16 - p_data->alpha.x );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
}




//----------------------------------------------------------------------------
/**
 *	@brief	甘い香りエフェクト開始
 *
 *	@param	fsys	フィールドシステムワーク
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_Amaikaori_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_AmaikaoriData = {
		AMAIKAORI_TSK_PRI,
		sizeof(AMAIKAORI_WORK),
		FLDMAP_Amaikaori_Init,
		FLDMAP_Amaikaori_Delete,
		FLDMAP_Amaikaori_Main,
		FLDMAP_Amaikaori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_AmaikaoriData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	甘い香りワーク破棄
 *
 *	@param	p_eff	エフェクトワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_Amaikaori_End( FLDMAPFUNC_WORK* p_eff )
{
	FLDMAPFUNC_Delete( p_eff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	甘い香り終了チェック
 *	
 *	@param	p_eff	エフェクトワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_Amaikaori_EndCheck( FLDMAPFUNC_WORK* p_eff )
{
	AMAIKAORI_WORK* p_data = FLDMAPFUNC_GetFreeWork( p_eff );
	return p_data->end;
}



//----------------------------------------------------------------------------
/**
 *	@brief	甘い香り終了エフェクト
 *
 *	@param	fsys フィールドシステムワーク
 *
 *	@return
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_AmaikaoriEndEff_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_AmaikaoriData = {
		AMAIKAORI_TSK_PRI,
		sizeof(AMAIKAORI_WORK),
		FLDMAP_AmaikaoriEndEff_Init,
		FLDMAP_Amaikaori_Delete,
		FLDMAP_Amaikaori_Main,
		FLDMAP_Amaikaori_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_AmaikaoriData );
	return p_fwk;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG設定
 */
//-----------------------------------------------------------------------------
static void Amaikaori_SetUpBG( GF_BGL_INI* bg_ini )
{
	GXRgb color = GX_RGB( 31, 10, 23 );
	u8* p_char_buff;
	
	// カラーパレット転送
	GF_BGL_PaletteSet( AMAIKAORI_USE_BG_FRM, &color, sizeof(short), (AMAIKAORI_USE_PLTT * 32) + 2 );


	// キャラクタデータ
	p_char_buff = sys_AllocMemory( HEAPID_FIELD, sizeof(u8)*32 );
	memset( p_char_buff, 0x11, sizeof(u8)*32 );
	GF_BGL_LoadCharacter( bg_ini, AMAIKAORI_USE_BG_FRM, p_char_buff, sizeof(u8)*32, 1 );
	sys_FreeMemoryEz( p_char_buff );

	// スクリーンデータ
	GF_BGL_ScrClearCode( bg_ini, AMAIKAORI_USE_BG_FRM, (AMAIKAORI_USE_PLTT << 12) | 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	汎用動作リクエスト
 *	
 *	@param	p_work	ワーク
 *	@param	s_x		開始値
 *	@param	e_x		終了値
 *	@param	count_max	カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void AmaikaoriMoveReq( AMAIKAORI_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	汎用動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL	AmaikaoriMoveMain( AMAIKAORI_MOVE_WORK* p_work )
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











//-----------------------------------------------------------------------------
/**
 *		イベント
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	シーケンス
//=====================================
enum{
	FLDMAP_AMAIKAORI_WEATHER_CHECK,		// 天気チェック
	FLDMAP_AMAIKAORI_START_0,	// エフェクト開始
	FLDMAP_AMAIKAORI_END_0,		// 終了チェック
	FLDMAP_AMAIKAORI_MAX_WAIT,	// 最高にかかった状態でweight
	FLDMAP_AMAIKAORI_START_1,	// エンカウントしないときの　エフェクト開始
	FLDMAP_AMAIKAORI_END_1,		// エンカウントしないときの　終了チェック
	FLDMAP_AMAIKAORI_ENCOUNT,	// エンカウントスタート
	FLDMAP_AMAIKAORI_WEATHER_END,		// 天気のせいであまいかおりを出せなかったとき
	FLDMAP_AMAIKAORI_NOENCOUNT,	// エンカウントしなかったとき
	FLDMAP_AMAIKAORI_SCRPT_END,	// スクリプト終了
};

//-------------------------------------
//	甘い香りイベントワーク
//=====================================
typedef struct _EVENT_AMAIKAORI_EFF_WORK{
	FLDMAPFUNC_WORK* p_fwk;
	BOOL bd_bg_flip;	// 霧のときBDとBGを切り替える
	u16 seq;
	s16 wait;
} ;

// 霧のときBGとBDを切り替える
#define AMAIKAORI_FOG_BG_PL	(6)
#define AMAIKAORI_FOG_BG_PL_OFS	((AMAIKAORI_FOG_BG_PL*32)+4)
#define AMAIKAORI_FOG_BG_PL_DAT	( 0x7fff )
#define AMAIKAORI_FOG_BG_CHR_OFS	(2)
#define AMAIKAORI_FOG_BG_CHR_DAT	(2)
#define AMAIKAORI_FOG_BG_SCR_DAT	( (AMAIKAORI_FOG_BG_PL<<12) | (AMAIKAORI_FOG_BG_CHR_OFS) )

//----------------------------------------------------------------------------
/**
 *	@brief	BDを黒にリセット
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_BDReset( FIELDSYS_WORK* fsys )
{
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME2_M, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	霧BGをBDにフリップ
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------
static void FLDMAP_Amaikaori_BGFlipBD( FIELDSYS_WORK* fsys )
{
	// バックドロップを真っ白に
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME2_M, AMAIKAORI_FOG_BG_PL_DAT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BDを霧BGにフリップ
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------

static void FLDMAP_Amaikaori_BDFlipBG( FIELDSYS_WORK* fsys )
{
	u16	col = AMAIKAORI_FOG_BG_PL_DAT;

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	
	// BGを真っ白に
	G2_SetBG2Priority(3);
	GF_BGL_PaletteSet( FLD_MBGFRM_EFFECT2, &col, 2, AMAIKAORI_FOG_BG_PL_OFS );
	GF_BGL_CharFill( fsys->bgl, FLD_MBGFRM_EFFECT2, AMAIKAORI_FOG_BG_CHR_DAT, 1, AMAIKAORI_FOG_BG_CHR_OFS );	// 1キャラ目を真っ白にする
	GF_BGL_ScrClearCode( fsys->bgl, FLD_MBGFRM_EFFECT2, AMAIKAORI_FOG_BG_SCR_DAT );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

	// バックドロップ黒
	FLDMAP_Amaikaori_BDReset( fsys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BDをメッセージBGにフリップ
 *
 *	@param	fsys 
 */
//-----------------------------------------------------------------------------

static void FLDMAP_Amaikaori_BDFlipMessegeBG( FIELDSYS_WORK* fsys )
{
	u16	col = AMAIKAORI_FOG_BG_PL_DAT;

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	
	// BGを真っ白に
	G2_SetBG3Priority(3);
	GF_BGL_PaletteSet( FLD_MBGFRM_FONT, &col, 2, AMAIKAORI_FOG_BG_PL_OFS );
	GF_BGL_CharFill( fsys->bgl, FLD_MBGFRM_FONT, AMAIKAORI_FOG_BG_CHR_DAT, 1, AMAIKAORI_FOG_BG_CHR_OFS );	// 1キャラ目を真っ白にする

	GF_BGL_ScrClearCode( fsys->bgl, FLD_MBGFRM_FONT, AMAIKAORI_FOG_BG_SCR_DAT );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

	// バックドロップ黒
	FLDMAP_Amaikaori_BDReset( fsys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BD　と　BG面を切り返る　再仮想にBGを出しているもののみできる
 *
 *	@param	fsys	フィールドシステム
 *
 *	@retval	TRUE	切り替える
 *	@retval	FALSE	切り替えない
 */
//-----------------------------------------------------------------------------
#define FLDMAP_AMAIKAORI_DBG_CHG_WEATHER	(1)
static BOOL FLDMAP_Amaikaori_BD_BG_ChangeCheck( FIELDSYS_WORK* fsys )
{
	static const u32 FldmapAmaikaoriDBGWeather[ FLDMAP_AMAIKAORI_DBG_CHG_WEATHER ] = {
		WEATHER_SYS_FOG,
	};
	u32 weather_no;
	int i;
	weather_no = WEATHER_GetNow( fsys->fldmap->weather_data );

	for( i=0; i<FLDMAP_AMAIKAORI_DBG_CHG_WEATHER; i++ ){
		if( weather_no == FldmapAmaikaoriDBGWeather[i] ){
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	甘い香りが出来る天気かチェック
 *	@retval	TRUE	出来る
 *	@retval	FALSE	出来ない
 */
//-----------------------------------------------------------------------------
#define FLDMAP_AMAIKAORI_NONE_WEATHER	( 16 )
static BOOL FLDMAP_Amaikaori_WeatherCheck( FIELDSYS_WORK* fsys )
{
	static const u32 FldmapAmaikaoriNoWeather[ FLDMAP_AMAIKAORI_NONE_WEATHER ] = {
		WEATHER_SYS_RAIN,
		WEATHER_SYS_STRAIN,
		WEATHER_SYS_SPARK,
		WEATHER_SYS_SNOW,
		WEATHER_SYS_SNOWSTORM,
		WEATHER_SYS_SNOWSTORM_H,
		WEATHER_SYS_SANDSTORM,
		WEATHER_SYS_SNOW_STORM_BG,// BG使用吹雪	OAM FOG BG
		WEATHER_SYS_STORM,		// 砂嵐		OAM FOG
		WEATHER_SYS_MIST1,			// 霧払いの霧	FOG	BG
		WEATHER_SYS_MIST2,			// 霧払いの霧	FOG	BG
		WEATHER_SYS_FLASH,			// フラッシュ		BG
		WEATHER_SYS_CLOUDINESS,		// 曇り		BG	
		WEATHER_SYS_VOLCANO,		// 火山灰	OAM FOG BG
		WEATHER_SYS_MYSTIC,
		WEATHER_SYS_SPARK_EFF,
	};
	u32 weather_no;
	int i;
	weather_no = WEATHER_GetNow( fsys->fldmap->weather_data );

	for( i=0; i<FLDMAP_AMAIKAORI_NONE_WEATHER; i++ ){
		
		if( weather_no == FldmapAmaikaoriNoWeather[i] ){
			return FALSE;
		}
	}
	return TRUE;
}

// エフェクト終了関数
static void FLDMAP_Amaikaori_WorkDelete( EVENT_AMAIKAORI_EFF_WORK* p_work )
{
	if( p_work->p_fwk ){
		FLDMAP_Amaikaori_End( p_work->p_fwk );	
		p_work->p_fwk = NULL;
	}
	sys_FreeMemoryEz( p_work );
}


// ワークサイズ
u32 FLDMAP_Amaikaori_WorkSize( void )
{
	return sizeof( EVENT_AMAIKAORI_EFF_WORK );
}


//----------------------------------------------------------------------------
/**
 *	@brief	甘い香りイベント　制御部分	ワークのはきもします　確保は外
 *
 *	@param	event	イベントワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_AmaikaoriEvent( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_AMAIKAORI_EFF_WORK* p_work = FieldEvent_GetSpecialWork(event);
	
	switch( p_work->seq ){
	case FLDMAP_AMAIKAORI_WEATHER_CHECK:		// 天気チェック
		if( FLDMAP_Amaikaori_WeatherCheck( fsys ) == TRUE ){
			p_work->seq = FLDMAP_AMAIKAORI_START_0;

			// 霧のときBDとBGを入れ替え
			p_work->bd_bg_flip = FLDMAP_Amaikaori_BD_BG_ChangeCheck( fsys );
			if( p_work->bd_bg_flip ){
				FLDMAP_Amaikaori_BGFlipBD( fsys );
			}
			
		}else{
			p_work->seq = FLDMAP_AMAIKAORI_WEATHER_END;
			p_work->wait = AMAIKAORI_EVENT_WEATHER_COMM_WAIT;	// 1秒のweight
		}
		break;
		
	case FLDMAP_AMAIKAORI_START_0:	// エフェクト開始
		p_work->p_fwk = FLDMAP_Amaikaori_Start( fsys );		
		p_work->seq  = FLDMAP_AMAIKAORI_END_0;
		// BGON
		GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 0 );
		GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_ON );
		break;
		
	case FLDMAP_AMAIKAORI_END_0:		// 終了チェック
		if( FLDMAP_Amaikaori_EndCheck( p_work->p_fwk ) ){
			p_work->wait = AMAIKAORI_EVENT_ALPHA_MAX_WAIT;
			p_work->seq  = FLDMAP_AMAIKAORI_MAX_WAIT;
		}
		break;


	case FLDMAP_AMAIKAORI_MAX_WAIT:	// 最高にかかった状態でweight
		p_work->wait --;
		// ゾーンがエンカウントOKかチェック
		if( ZoneData_GetEncountFlag(fsys->location->zone_id) ){
			if( p_work->wait < 0 ){
				{
					//アトリビュートチェック
					u8 attr;
					int x,z;

					x = Player_NowGPosXGet( fsys->player );
					z = Player_NowGPosZGet( fsys->player );
					attr = (u8)GetAttributeLSB( fsys, x, z );
					if (EncSet_CheckEncount( fsys, attr)){
						// エンカウントする
						p_work->seq = FLDMAP_AMAIKAORI_ENCOUNT;
					}else{
						// エンカウントしない
						p_work->seq = FLDMAP_AMAIKAORI_START_1;
					}
				}
			}
		}else{
			// エンカウントしない
			p_work->seq = FLDMAP_AMAIKAORI_START_1;
		}
		break;
		
	case FLDMAP_AMAIKAORI_START_1:	// エンカウントしないときの　エフェクト開始
		FLDMAP_Amaikaori_End( p_work->p_fwk );	// 今までのエフェクトワーク破棄
		p_work->p_fwk = FLDMAP_AmaikaoriEndEff_Start( fsys );
		p_work->seq = FLDMAP_AMAIKAORI_END_1;
		break;
		
	case FLDMAP_AMAIKAORI_END_1:		// エンカウントしないときの　終了チェック
		if( FLDMAP_Amaikaori_EndCheck( p_work->p_fwk ) ){
			// BGOFF
			GF_Disp_GX_VisibleControl( AMAIKAORI_USE_BG_MSK, VISIBLE_OFF );
			G2_BlendNone();
			GF_BGL_PrioritySet( AMAIKAORI_USE_BG_FRM, 3 );

			p_work->seq = FLDMAP_AMAIKAORI_NOENCOUNT;
		}
		break;
		
	case FLDMAP_AMAIKAORI_ENCOUNT:	// エンカウントスタート
		{
			BOOL rc;

			// ワーク破棄
			FLDMAP_Amaikaori_WorkDelete( p_work );

			// 霧エンカウントするので、メッセージ面に
			// しろBGをフリップする
			if( p_work->bd_bg_flip ){
				FLDMAP_Amaikaori_BDFlipMessegeBG( fsys );
			}

			rc = SetSweetEncount(fsys, event);
			GF_ASSERT(rc);
		}
		break;	// ここからは、エンカウントエフェクトに移行される
		
	case FLDMAP_AMAIKAORI_WEATHER_END:		// 天気のせいであまいかおりを出せなかったとき
		p_work->wait --;
		if( p_work->wait < 0 ){
			// メッセージ表示
			EventCall_Script( event, SCRID_SWEET_WEATHER, NULL, NULL );
			p_work->seq = FLDMAP_AMAIKAORI_SCRPT_END;
		}
		break;
		
	case FLDMAP_AMAIKAORI_NOENCOUNT:	// エンカウントしなかったとき
		// メッセージ表示
		EventCall_Script( event, SCRID_SWEET_NO_ENC, NULL, NULL );

		p_work->seq = FLDMAP_AMAIKAORI_SCRPT_END;
		break;

	case FLDMAP_AMAIKAORI_SCRPT_END:
		// ワーク破棄
		FLDMAP_Amaikaori_WorkDelete( p_work );

		// 霧のときBGとBDを切り替える
		if( p_work->bd_bg_flip ){
			FLDMAP_Amaikaori_BDFlipBG( fsys );
		}

		return TRUE;

	default:
		// おかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}
