//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_demo.c
 *	@brief		フィールド上での簡単なデモ処理
 *	@author		tomoya takahashi	
 *	@data		2006.04.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#include "include/system/swsprite.h"
#include "include/system/arc_util.h"
#include "demo_climax.naix"
#include "fieldmap.h"
#include "fieldmap_work.h"
#include "fieldsys.h"
#include "motion_bl.h"
#include "field_subscreen.h"
#include "fieldobj_draw_legendpoke.h"
#include "field_3dobj.h"
#include "src/fielddata/eventdata/zone_d05r0114evc.h"
#include "field_light.h"

#include "system/snd_tool.h"

#define	__FIELD_DEMO_H_GLOBAL
#include "field_demo.h"

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
#ifdef PM_DEBUG
//#define FIELD_DEMO_DEBUG		// デバックタスクをまわすか？
#endif // PM_DEBUG 

#ifdef FIELD_DEMO_DEBUG
static int FIELD_DEMO_DEBUG_STOP = 0;
static TCB_PTR pFieldDemoDebugTcb = NULL;
static void FieldDemoDebugTcb( TCB_PTR tcb, void* p_work );
static void FieldDemoDebugStart( void );
static void FieldDemoDebugEnd( void );
#endif // FIELD_DEMO_DEBUG


#define USE_HEAPID		( HEAPID_FIELD )


//-------------------------------------
//	音定義
//=====================================
#define FLD_DEMO_LEGENDEFF_SND_00	( SEQ_SE_DP_CLIMAX01 )		// シュー
#define FLD_DEMO_LEGENDEFF_SND_01	( SEQ_SE_DP_CLIMAX03 )		// ぼりー
#define FLD_DEMO_LEGENDEFF_SND_02	( SEQ_SE_DP_CLIMAX06 )		// ぴかー	フラッシュ
#define FLD_DEMO_LEGENDEFF_SND_03	( SEQ_SE_DP_CLIMAX09 )		// ゴーゴゴゴ	画面揺らし
#define FLD_DEMO_LEGENDEFF_SND_04	( SEQ_SE_DP_CLIMAX10 )		// ウィン	
#define FLD_DEMO_LEGENDEFF_SND_05	( SEQ_SE_DP_CLIMAX12 )		// シューン

//#define FLD_DEMO_LEGENDEFF_SND_06	( SEQ_SE_DP_CLIMAX16 )		// プシュー
#define FLD_DEMO_LEGENDEFF_SND_06	( SEQ_SE_DP_CLIMAX15 )		// プシュー




//-----------------------------------------------------------------------------
/**
 * 
 *			【デモ用モーションブラー設定関数】
 * 
 */
//-----------------------------------------------------------------------------
#define FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI (1024)
//-------------------------------------
//	動作シーケンス
//=====================================
enum{
	FLD_DEMO_MOTIONBL_SEQ_BGINIT,
	FLD_DEMO_MOTIONBL_SEQ_BLINIT,
	FLD_DEMO_MOTIONBL_SEQ_ENDWAIT,
	FLD_DEMO_MOTIONBL_SEQ_BLEND,
	FLD_DEMO_MOTIONBL_SEQ_BGRESET,
	FLD_DEMO_MOTIONBL_SEQ_END,
};



//-------------------------------------
//	モーションブラーワーク
//=====================================
typedef struct {
	FIELDSYS_WORK* p_fsys;
	// 保存領域
	GF_BGL_DISPVRAM vrambank;		// VRAMバンク設定
	// モーションブラー
	MOTION_BL_PTR motion_bl;

	int eva;
	int evb;

	u32 seq;		// シーケンス
} FLD_DEMO_MOTIONBL;

static void FLD_DEMO_MOTIONBL_Init( FLD_DEMO_MOTIONBL* p_data, FIELDSYS_WORK* p_fsys, int eva, int evb );
static void FLD_DEMO_MOTIONBL_Main( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_EndReq( FLD_DEMO_MOTIONBL* p_data );
static u32 FLD_DEMO_MOTIONBL_GetState( const FLD_DEMO_MOTIONBL* cp_data );

static void FLD_DEMO_MOTIONBL_GetNowVramBank( GF_BGL_DISPVRAM* p_vrambank );
static void FLD_DEMO_MOTIONBL_SetUpBnk( void );
static void FLD_DEMO_MOTIONBL_SetUpBGIni( GF_BGL_INI* p_bg );
static void FLD_DEMO_MOTIONBL_SetUpBGIni_Field( GF_BGL_INI* p_bg );
static void FLD_DEMO_MOTIONBL_DeleteBGIni( GF_BGL_INI* p_bgini );
static MOTION_BL_PTR FLD_DEMO_MOTIONBL_MotionBlInit( int eva, int evb );
static void FLD_DEMO_MOTIONBL_MotionBlDelete( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( FLD_DEMO_MOTIONBL* p_data );
static void FLD_DEMO_MOTIONBL_ResetDrawSystemReq( FLD_DEMO_MOTIONBL* p_data );

static void FLD_DEMO_MOTIONBL_MotionBlDeleteTcb( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_MOTIONBL_ResetDrawSystemTCB( TCB_PTR tcb, void* p_work );


//----------------------------------------------------------------------------
/**
 *	@brief	モーションブラー初期化
 *
 *	@param	p_data		ワーク
 *	@param	p_fsys		フィールドシステム
 *	@param	eva			描画された絵ブレンド係数
 *	@parem	evb			VRAM_Cブレンド係数
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_Init( FLD_DEMO_MOTIONBL* p_data, FIELDSYS_WORK* p_fsys, int eva, int evb )
{
	p_data->p_fsys = p_fsys;
	FLD_DEMO_MOTIONBL_GetNowVramBank( &p_data->vrambank );
	p_data->seq = 0;
	p_data->eva = eva;
	p_data->evb = evb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	モーションブラーメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_Main( FLD_DEMO_MOTIONBL* p_data )
{
	switch( p_data->seq ){
	case FLD_DEMO_MOTIONBL_SEQ_BGINIT:
		FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BLINIT:
		p_data->motion_bl = FLD_DEMO_MOTIONBL_MotionBlInit( p_data->eva, p_data->evb );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_ENDWAIT:
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BLEND:
		FLD_DEMO_MOTIONBL_MotionBlDelete( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_BGRESET:
		FLD_DEMO_MOTIONBL_ResetDrawSystemReq( p_data );
		p_data->seq++;
		break;
		
	case FLD_DEMO_MOTIONBL_SEQ_END:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	モーションブラー終了リクエスト
 *
 *	@param	p_data	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_EndReq( FLD_DEMO_MOTIONBL* p_data )
{
	GF_ASSERT( p_data->seq == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT );
	p_data->seq = FLD_DEMO_MOTIONBL_SEQ_BLEND;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在のシーケンスを取得
 *
 *	@param	cp_data		ワーク
 *
 *	@return		FLD_DEMO_MOTIONBL_SEQ_BGINIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BLINIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_ENDWAIT,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BLEND,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_BGRESET,
 *	@return     FLD_DEMO_MOTIONBL_SEQ_END,
 */             
//-----------------------------------------------------------------------------
static u32 FLD_DEMO_MOTIONBL_GetState( const FLD_DEMO_MOTIONBL* cp_data )
{
	return cp_data->seq;
}


//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	VRAMバンク状態の取得
 *
 *	@param	p_vrambank	格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_GetNowVramBank( GF_BGL_DISPVRAM* p_vrambank )
{
	p_vrambank->main_bg			= GX_GetBankForBG();
	p_vrambank->main_bg_expltt	= GX_GetBankForBGExtPltt();
	p_vrambank->sub_bg			= GX_GetBankForSubBG();
	p_vrambank->sub_bg_expltt	= GX_GetBankForSubBGExtPltt();
	p_vrambank->main_obj		= GX_GetBankForOBJ();
	p_vrambank->main_obj_expltt	= GX_GetBankForOBJExtPltt();
	p_vrambank->sub_obj			= GX_GetBankForSubOBJ();
	p_vrambank->sub_obj_expltt	= GX_GetBankForSubOBJExtPltt();
	p_vrambank->teximage		= GX_GetBankForTex();
	p_vrambank->texpltt			= GX_GetBankForTexPltt();
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	climaxデモ　バンク設定
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBnk( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_32_FG,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_NONE,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}	

//----------------------------------------------------------------------------
/**	
 *			【デモ用モーションブラー設定関数】
 *	@brief		BGコントロール作成
 *	@param		BGコントロールデータ
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBGIni( GF_BGL_INI* p_bg )
{
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0, GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0, VISIBLE_ON );

	{	// MAIN DISP（メッセージ）
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x4000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_23,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, FLD_MBGFRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 32, 0, USE_HEAPID );
		GF_BGL_ScrClear( p_bg, FLD_MBGFRM_FONT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	モーションブラー状態セットリクエスト
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemReq( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モーションブラー状態リセットリクエスト
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_ResetDrawSystemReq( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_ResetDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_ResetDrawSystemTCB, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	描画システム設定タスク
 *
 *	@param	tcb			タスクワーク
 *	@param	p_work		ワーク
 *	
 *	@return	none
 *
 *	Vブランク期間内で行わないと画面にごみが出ると思うので、
 *	タスクで新しい描画設定を行う
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpDrawSystemTCB( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_drawsys = p_work;

	// バンク設定
	FLD_DEMO_MOTIONBL_SetUpBnk();

	// BGコントロール設定
	FLD_DEMO_MOTIONBL_DeleteBGIni(p_drawsys->p_fsys->bgl);
	FLD_DEMO_MOTIONBL_SetUpBGIni( p_drawsys->p_fsys->bgl );

	// 破棄
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	描画システムデータをもとに戻す
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_ResetDrawSystemTCB( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_drawsys = p_work;

	// VRAMバンク設定
	GF_Disp_SetBank( &p_drawsys->vrambank );

	// BGコントロール再作成
	FLD_DEMO_MOTIONBL_DeleteBGIni(p_drawsys->p_fsys->bgl);
	FLD_DEMO_MOTIONBL_SetUpBGIni_Field( p_drawsys->p_fsys->bgl );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	BGシステムワーク破棄
 *
 *	@param	p_bgini		BGシステムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_DeleteBGIni( GF_BGL_INI* p_bgini )
{
	Fieldmap_BgExit( p_bgini );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	フィールド用GFコントロール設定
 *	@param	BGシステムワーク
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_SetUpBGIni_Field( GF_BGL_INI* p_bg )
{
	Fieldmap_BgSet( p_bg );

	GF_Disp_GX_VisibleControl(
		GX_PLANEMASK_BG0, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	モーションブラー初期化
 *
 *	@param	eva		係数A　現在描画されたもの
 *	@param	evb		係数B　今VRAMに保存されているもの
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static MOTION_BL_PTR FLD_DEMO_MOTIONBL_MotionBlInit( int eva, int evb )
{
	MOTION_BL_PTR motion_bl;
	
	// モーションブラー設定
	{
		MOTION_BL_DATA mb = {
			GX_DISPMODE_VRAM_C,
			GX_BGMODE_0,
			GX_BG0_AS_3D,
			
			GX_CAPTURE_SIZE_256x192,
			GX_CAPTURE_MODE_AB,
			GX_CAPTURE_SRCA_2D3D,
			GX_CAPTURE_SRCB_VRAM_0x00000,
			GX_CAPTURE_DEST_VRAM_C_0x00000,
			0,
			0,
			USE_HEAPID
		};
		mb.eva = eva;
		mb.evb = evb;

		motion_bl = MOTION_BL_Init(&mb);
	}	
		

	return motion_bl;
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	モーションブラー破棄
 *
 *	@param	data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_MotionBlDelete( FLD_DEMO_MOTIONBL* p_data )
{
//	VIntrTCB_Add( FLD_DEMO_MOTIONBL_MotionBlDeleteTcb, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
	VWaitTCB_Add( FLD_DEMO_MOTIONBL_MotionBlDeleteTcb, p_data, FLD_DEMO_MOTIONBL_DRAWDATA_SETUP_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *			【デモ用モーションブラー設定関数】
 *	@brief	モーションブラー破棄TCB
 *
 *	@param	tcb			TCBワーク
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MOTIONBL_MotionBlDeleteTcb( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_MOTIONBL* p_data = p_work;
	
	// 元に戻す
	MOTION_BL_Delete(&p_data->motion_bl, GX_DISPMODE_GRAPHICS, GX_BGMODE_0,GX_BG0_AS_3D);
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェ影ONOFF
 *
 *	@param	fsys	フィールドシステム
 *	@param	objid	オブジェID
 *	@param	flg		フラグ TRUE：OFF　FALSE：ON
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_ObjShadowVanish( FIELDSYS_WORK* fsys, u32 objid, BOOL flg )
{
	FIELD_OBJ_PTR fldobj;
	fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, objid );

	if( flg == TRUE ){
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}else{
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
	}
}





//-----------------------------------------------------------------------------
/**
 *
 *		フィールドマップタスク動作
 *
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_SetFieldObjSysOfs( FIELD_OBJ_SYS_PTR fos, const VecFx32 *vec )
{
	int no = 0;
	FIELD_OBJ_PTR fldobj;

	while( FieldOBJSys_FieldOBJSearch( fos, &fldobj, &no, FLDOBJ_STA_BIT_USE ) == TRUE ){
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, vec );
	}
}
static void FLDMAP_DEMO_ReSetFieldObjSysOfs( FIELD_OBJ_SYS_PTR fos )
{
	VecFx32 ofs;
	int no = 0;
	FIELD_OBJ_PTR fldobj;

	ofs.x = 0;
	ofs.y = 0;
	ofs.z = 0;
	while( FieldOBJSys_FieldOBJSearch( fos, &fldobj, &no, FLDOBJ_STA_BIT_USE ) == TRUE ){
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &ofs );
	}
}


//-------------------------------------
//	地震イベントワーク
//=====================================
typedef struct {
	FLD_DEMO_SHAKE_SCRN* p_zishin;
	int wait;
	u32 last_count;
	u32 seq;
} EVENT_ZISHIN_WORK;
#define EVENT_ZISHIN_WIDTH	( FX32_CONST( 2.0f ) )
#define EVENT_ZISHIN_SHAKE_SYNC	( 1 )	// １つのゆれのシンク数
#define EVENT_ZISHIN_SHAKE_COUNT	( 16 )	// ゆれ数

//----------------------------------------------------------------------------
/**
 *	@brief	地震イベントメイン
 */
//-----------------------------------------------------------------------------
static BOOL FLD_MAP_DEMO_ZishinEventMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case 0:
		FLD_DEMO_ShakeScrn_Main( p_work->p_zishin );
		if( FLD_DEMO_ShakeScrn_EndCheck( p_work->p_zishin ) == TRUE ){
			p_work->seq ++;
		}
		break;

	case 1:
		FLD_DEMO_ShakeScrn_Free( p_work->p_zishin );	
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------------
/**
 *	@brief	地震イベント発生
 *
 *	@param	ev	イベントワーク
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗
 */
//-----------------------------------------------------------------------------
void FLD_MAP_DEMO_ZishinEventCall(GMEVENT_CONTROL *event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(EVENT_ZISHIN_WORK) );
	memset( p_work, 0, sizeof(EVENT_ZISHIN_WORK) );

	p_work->p_zishin = FLD_DEMO_ShakeScrn_Alloc( HEAPID_FIELD );
	FLD_DEMO_ShakeScrn_Start( p_work->p_zishin, EVENT_ZISHIN_WIDTH, 0, EVENT_ZISHIN_SHAKE_SYNC, EVENT_ZISHIN_SHAKE_COUNT, fsys->camera_ptr );
	
	FieldEvent_Call( event, FLD_MAP_DEMO_ZishinEventMain, p_work );
}


// ミオシティ用地震
#define EVENT_MIO_ZISHIN_WIDTH	( FX32_CONST( 4.0f ) )
#define EVENT_MIO_ZISHIN_SHAKE_SYNC	( 1 )	// １つのゆれのシンク数
#define EVENT_MIO_ZISHIN_SHAKE_COUNT	( 24 )	// ゆれ数
#define EVENT_MIO_ZISHIN_SHAKE_DIV	( 8*FX32_ONE )
#define EVENT_MIO_BGM_FADE_OUT_SYNC	( 1 )
#define EVENT_MIO_BGM_FADE_IN_SYNC	( 16 )
#define EVENT_MIO_WAIT				( 16 )

enum{
	EVENT_MIO_ZISHIN_FADEOUT,
	EVENT_MIO_ZISHIN_FADEOUT_WAIT,
	EVENT_MIO_ZISHIN_START_WAIT,
	EVENT_MIO_ZISHIN_MAIN,
	EVENT_MIO_ZISHIN_END_WAIT,
	EVENT_MIO_ZISHIN_FADEIN,
	EVENT_MIO_ZISHIN_FADEIN_WAIT,
	EVENT_MIO_ZISHIN_END,
};

static void FLD_MAP_Demo_MioZishinShakeWidthSub( EVENT_ZISHIN_WORK* p_work )
{
	fx32 width = FLD_DEMO_ShakeScrn_GetNowShakeWidth( p_work->p_zishin );
	fx32 set_width;
	u32 count = FLD_DEMO_ShakeScrn_GetNowCount( p_work->p_zishin );

	if( p_work->last_count != count ){
		p_work->last_count = count;

		set_width = FX_Div( width, EVENT_MIO_ZISHIN_SHAKE_DIV );
		set_width = width - set_width;
		FLD_DEMO_ShakeScrn_SetNowShakeWidth( p_work->p_zishin, set_width );
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	地震イベントメイン
 */
//-----------------------------------------------------------------------------
static BOOL FLD_MAP_DEMO_MioZishinEventMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case EVENT_MIO_ZISHIN_FADEOUT:		// BGMフェードアウト（一瞬）
		Snd_BgmFadeOut( 0, EVENT_MIO_BGM_FADE_OUT_SYNC );
		p_work->seq ++;
		break;

	case EVENT_MIO_ZISHIN_FADEOUT_WAIT:
		if( Snd_FadeCheck() == 0 ){
			p_work->seq ++;
			p_work->wait = EVENT_MIO_WAIT;
		}
		break;

	case EVENT_MIO_ZISHIN_START_WAIT:
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->seq ++;	
			Snd_SePlay(	SE_SHAKE );		// ゆれ音開始
		}
		break;
	
	case EVENT_MIO_ZISHIN_MAIN:
		FLD_DEMO_ShakeScrn_Main( p_work->p_zishin );
		// ゆれ数が変わったらゆれ幅を減らす
		FLD_MAP_Demo_MioZishinShakeWidthSub( p_work );
		if( FLD_DEMO_ShakeScrn_EndCheck( p_work->p_zishin ) == TRUE ){
			Snd_SeStopBySeqNo( SE_SHAKE, 0 );	// ゆれ音停止
			p_work->seq ++;
			p_work->wait = EVENT_MIO_WAIT;
		}
		break;

	case EVENT_MIO_ZISHIN_END_WAIT:
		p_work->wait --;
		if( p_work->wait <= 0 ){
			p_work->seq ++;
		}
		break;

	case EVENT_MIO_ZISHIN_FADEIN:
		Snd_BgmFadeIn( BGM_VOL_MAX, EVENT_MIO_BGM_FADE_IN_SYNC, BGM_FADEIN_START_VOL_MIN );
		p_work->seq ++;
		break;

	case EVENT_MIO_ZISHIN_FADEIN_WAIT:
		if( Snd_FadeCheck() == 0 ){
			p_work->seq ++;
		}
		break;

	case EVENT_MIO_ZISHIN_END:
		FLD_DEMO_ShakeScrn_Free( p_work->p_zishin );	
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------------
/**
 *	@brief	地震イベント発生
 *
 *	@param	ev	イベントワーク
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗
 */
//-----------------------------------------------------------------------------
void FLD_MAP_DEMO_MioZishinEventCall(GMEVENT_CONTROL *event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_ZISHIN_WORK* p_work = sys_AllocMemory( HEAPID_FIELD, sizeof(EVENT_ZISHIN_WORK) );
	memset( p_work, 0, sizeof(EVENT_ZISHIN_WORK) );

	p_work->p_zishin = FLD_DEMO_ShakeScrn_Alloc( HEAPID_FIELD );
	FLD_DEMO_ShakeScrn_Start( p_work->p_zishin, EVENT_MIO_ZISHIN_WIDTH, 0, EVENT_MIO_ZISHIN_SHAKE_SYNC, EVENT_MIO_ZISHIN_SHAKE_COUNT, fsys->camera_ptr );
	
	// 残りゆれ数を設定
	p_work->last_count = FLD_DEMO_ShakeScrn_GetNowCount( p_work->p_zishin );
	FieldEvent_Call( event, FLD_MAP_DEMO_MioZishinEventMain, p_work );
}



//-----------------------------------------------------------------------------
/**
 *		伝説ポケモン出現
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	伝説ポケモン出現シーケンス
//=====================================
enum{
	FLDMAP_DEMO_LEGEND_MOTION_BP_SET,
	FLDMAP_DEMO_LEGEND_MOTION_BP_SET_WAIT,
	FLDMAP_DEMO_LEGEND_START,
	FLDMAP_DEMO_LEGEND_EFF_WAIT,
	FLDMAP_DEMO_LEGEND_END_WAIT,
	FLDMAP_DEMO_LEGEND_FLASH,
	FLDMAP_DEMO_LEGEND_MOTION_BP_END,
	FLDMAP_DEMO_LEGEND_MOTION_BP_END_WAIT,
	FLDMAP_DEMO_LEGEND_ARITAMA_ON,
	FLDMAP_DEMO_LEGEND_ARITAMA_SHADOWOFF_WAIT,
	FLDMAP_DEMO_LEGEND_ARITAMA_WAIT,
	FLDMAP_DEMO_LEGEND_END,
};
#define FLDMAP_DEMO_LEGEND_TASK_PRI	( 1024 )
#define FLDMAP_DEMO_LEGEND_OBJID	( D05R0114_SPPOKE_01 )	// 出現させるイアエアの管理ID
#define FLDMAP_DEMO_LEGEND_EFFSTART	( 240 )		// エフェクト開始

//-------------------------------------
//	ばんばんば～ん　フラッシュ
//=====================================
typedef struct {
	u32 seq;
	s32 wait;
	FLD_DEMO_FLASH* p_flash;			// FLDMAP_DEMO_LEGENDからもらう
} FLDMAP_DEMO_LEGEND_BANBANFLASH;
enum{
	FLD_DEMO_LEGEND_BANBANFLASH_FLASHWAIT,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH00,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH01,
	FLD_DEMO_LEGEND_BANBANFLASH_FLASH02,
	FLD_DEMO_LEGEND_BANBANFLASH_END,
};

// プロトタイプ
static void FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff, FLD_DEMO_FLASH* p_flash );
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff );


//-------------------------------------
//	画面揺らし＆フラッシュエフェクト
//=====================================
typedef struct {
	u32 seq;
	s32 wait;
	FLD_DEMO_SHAKE_SCRN* p_shake;		// FLDMAP_DEMO_LEGENDからもらう
	FLD_DEMO_FLASH* p_flash;			// FLDMAP_DEMO_LEGENDからもらう
	GF_CAMERA_PTR copy_camera;			// カメラ
} FLDMAP_DEMO_LEGEND_SHAKEFLASH;
// シーケンス
enum{
	FLD_DEMO_LEGEND_SHAKEFLASH_START,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00,
	FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02,
	FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01,
	FLD_DEMO_LEGEND_SHAKEFLASH_END,
};
#define FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX	( 13 )	// α最大値

#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_X	( FX32_CONST( 2.0f ) )	// ゆれ幅
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC	( 1 )	// １つのゆれのシンク数
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_COUNT	( 8 )	// ゆれ数

#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00_WAIT	( 0 )	// ウエイト
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00_WAIT	( 80 )	// ウエイト
#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01_WAIT	( 32 )	// ウエイト
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00_WAIT	( 60 )	// ウエイト
#define FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02_WAIT	( 60 )	// ウエイト
#define FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01_WAIT	( 40 )	// ウエイト

#define FLD_DEMO_LEGEND_BANBAN_START_WAIT	( 32 )

#define FLD_DEMO_LEGEND_SHADOW_OFF_WAIT	( 72 )

// プロトタイプ
static void FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff, FLD_DEMO_SHAKE_SCRN* p_shake, FLD_DEMO_FLASH* p_flash, GF_CAMERA_PTR copy_camera );
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff );

//-------------------------------------
//	伝説ポケモン出現ワーク
//=====================================
typedef struct {
	u32 seq;		// シーケンス
	s32 count;		// 汎用ｶｳﾝﾀ
	
	FLD_DEMO_MOTIONBL motion_bl;		// モーションブラー

	FLD_DEMO_LEGENDPOKE_APP* p_legend;
	FLD_DEMO_SHAKE_SCRN* p_shake;
	FLD_DEMO_FLASH* p_flash;
	FLD_DEMO_ARITAMA_START* p_aritama;	// アリの卵開始

	FLDMAP_DEMO_LEGEND_SHAKEFLASH shakeflash;	// ゆれフラッシュコントロール
	FLDMAP_DEMO_LEGEND_BANBANFLASH banbanflash;	// ばんばんば～んフラッシュ
} FLDMAP_DEMO_LEGEND;

#define FLD_DEMO_LEGEND_MOTIONBL_EVA	( 8 )
#define FLD_DEMO_LEGEND_MOTIONBL_EVB	( 8 )

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	初期化処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	memset( p_lgd, 0, sizeof(FLDMAP_DEMO_LEGEND) );

	//	イアエア出現
	p_lgd->p_legend = FLD_DEMO_LegendPokeApp_Alloc( USE_HEAPID, p_fsys );
	// 地震
	p_lgd->p_shake = FLD_DEMO_ShakeScrn_Alloc( USE_HEAPID );
	// フラッシュ
	p_lgd->p_flash = FLD_DEMO_Flash_Alloc( USE_HEAPID );
	// シーケンス
	p_lgd->seq = 0;

#ifdef FIELD_DEMO_DEBUG
	FieldDemoDebugStart();
#endif
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	破棄処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	// イアエア出現
	FLD_DEMO_LegendPokeApp_Free( p_lgd->p_legend );
	// アリの卵
	FLD_DEMO_AriTamaStart_Free( p_lgd->p_aritama );
	// 地震
	FLD_DEMO_ShakeScrn_Free( p_lgd->p_shake );
	// フラッシュ
	FLD_DEMO_Flash_Free( p_lgd->p_flash );

#ifdef FIELD_DEMO_DEBUG
	FieldDemoDebugEnd();
#endif
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	メイン処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;
	BOOL check[2];
	BOOL result;

#ifdef FIELD_DEMO_DEBUG
	if( FIELD_DEMO_DEBUG_STOP == 1 ){
		return ;
	}
#endif
	
	// 処理の分岐部
	switch( p_lgd->seq ){
	case FLDMAP_DEMO_LEGEND_MOTION_BP_SET:	// モーションブラー設定
		FLD_DEMO_MOTIONBL_Init( &p_lgd->motion_bl, p_fsys, FLD_DEMO_LEGEND_MOTIONBL_EVA, FLD_DEMO_LEGEND_MOTIONBL_EVB );
		
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_SET_WAIT:
		FLD_DEMO_MOTIONBL_Main( &p_lgd->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_lgd->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT ){
			p_lgd->seq ++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_START:
		FLD_DEMO_LegendPokeApp_Start( p_lgd->p_legend, FLDMAP_DEMO_LEGEND_OBJID );
		p_lgd->count = FLDMAP_DEMO_LEGEND_EFFSTART;
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_EFF_WAIT:
		p_lgd->count--;
		if( p_lgd->count < 0 ){
			FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( &p_lgd->shakeflash, p_lgd->p_shake, p_lgd->p_flash, p_fsys->camera_ptr );
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_END_WAIT:
		check[0] = FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( &p_lgd->shakeflash );
		check[1] = FLD_DEMO_LegendPokeApp_EndCheck( p_lgd->p_legend );
		// 動作部
		if( (check[0] == TRUE) && (check[1] == TRUE) ){
			FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( &p_lgd->banbanflash, p_lgd->p_flash );
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_FLASH:
		check[0] = FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( &p_lgd->banbanflash );

		// 真っ白状態でありの卵読み込む
		// テクスチャサイズが大きく、画面に影響がでるため
		if( p_lgd->banbanflash.seq == FLD_DEMO_LEGEND_BANBANFLASH_FLASH02 ){
			if( FLD_DEMO_Flash_GetAlpha( p_lgd->banbanflash.p_flash ) == FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX ){
				// アリの卵
				p_lgd->p_aritama = FLD_DEMO_AriTamaStart_Alloc( USE_HEAPID, p_fsys );
			}
		}
		
		if( check[0] == TRUE ){
			p_lgd->seq++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_END:	// モーションブラー破棄
		FLD_DEMO_MOTIONBL_EndReq( &p_lgd->motion_bl );
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_MOTION_BP_END_WAIT:
		FLD_DEMO_MOTIONBL_Main( &p_lgd->motion_bl );

		if( FLD_DEMO_MOTIONBL_GetState( &p_lgd->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_END ){
			p_lgd->seq ++;
		}
		break;

	case FLDMAP_DEMO_LEGEND_ARITAMA_ON:
		FLD_DEMO_AriTamaStart_Start( p_lgd->p_aritama, FLDMAP_DEMO_LEGEND_OBJID );
		p_lgd->count = FLD_DEMO_LEGEND_SHADOW_OFF_WAIT;
		p_lgd->seq ++;
		break;

	case FLDMAP_DEMO_LEGEND_ARITAMA_SHADOWOFF_WAIT:
		p_lgd->count --;
		if( p_lgd->count <= 0 ){	
			FLD_DEMO_ObjShadowVanish( p_fsys, FLDMAP_DEMO_LEGEND_OBJID, TRUE );
			p_lgd->seq ++;
		}

	case FLDMAP_DEMO_LEGEND_ARITAMA_WAIT:
		result = FLD_DEMO_AriTamaStart_Main( p_lgd->p_aritama );
		if( result == TRUE ){

			FLD_DEMO_ObjShadowVanish( p_fsys, FLDMAP_DEMO_LEGEND_OBJID, FALSE );
			p_lgd->seq ++;
		}
		break;
		
	case FLDMAP_DEMO_LEGEND_END:
		break;


	default:
		break;
	}
	
	FLD_DEMO_LegendPokeApp_Main( p_lgd->p_legend );
	FLD_DEMO_ShakeScrn_Main( p_lgd->p_shake );
	FLD_DEMO_Flash_Main( p_lgd->p_flash );
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_LEGEND* p_lgd = p_work;

	FLD_DEMO_LegendPokeApp_Draw( p_lgd->p_legend );
	if( p_lgd->p_aritama ){
		FLD_DEMO_AriTamaStart_Draw( p_lgd->p_aritama );
	}
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	伝説ポケモン出現　デモ開始
 *
 *	@param	fsys	フィールドシステムワーク
 *
 *	@return	デモワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_LegendPokeApp_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_LegendPokeAppData = {
		FLDMAP_DEMO_LEGEND_TASK_PRI,
		sizeof(FLDMAP_DEMO_LEGEND),
		FLDMAP_DEMO_LegendPokeApp_Init,
		FLDMAP_DEMO_LegendPokeApp_Delete,
		FLDMAP_DEMO_LegendPokeApp_Main,
		FLDMAP_DEMO_LegendPokeApp_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_LegendPokeAppData );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	伝説ポケモン出現	デモ終了
 *
 *	@param	p_demo	デモワーク
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_LegendPokeApp_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	デモ終了チェック
 *
 *	@param	p_demo 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL FLDMAP_DEMO_LegendPokeApp_EndCheck( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_LEGEND* p_lgd = FLDMAPFUNC_GetFreeWork( p_demo );
	if( p_lgd->seq == FLDMAP_DEMO_LEGEND_END ){
		return TRUE;
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	揺らし＆フラッシュ	初期化
 *
 *	@param	p_eff		エフェクトワーク
 *	@param	p_shake		揺らしオブジェ
 *	@param	p_flash		フラッシュオブジェ
 *	@param	copy_camera	カメラ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Init( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff, FLD_DEMO_SHAKE_SCRN* p_shake, FLD_DEMO_FLASH* p_flash, GF_CAMERA_PTR copy_camera )
{
	p_eff->seq	= 0;
	p_eff->wait = 0; 
	p_eff->p_shake = p_shake;
	p_eff->p_flash = p_flash;
	p_eff->copy_camera = copy_camera;
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	揺らし＆フラッシュ	メイン
 *
 *	@param	p_eff	エフェクトワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_ShakeFlash_Main( FLDMAP_DEMO_LEGEND_SHAKEFLASH* p_eff )
{
	switch( p_eff->seq ){
	case FLD_DEMO_LEGEND_SHAKEFLASH_START:
		p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00_WAIT;
		p_eff->seq++;
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 16 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00_WAIT;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 24 );
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_X, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_COUNT, p_eff->copy_camera );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH01:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 27 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE00:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, 3*FX32_ONE, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, 10, p_eff->copy_camera );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02_WAIT;
		}
		break;

	case FLD_DEMO_LEGEND_SHAKEFLASH_FLASH02:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 8, 32 );
			p_eff->seq++;
			p_eff->wait = FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01_WAIT;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_FLASH01:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 16 );
			FLD_DEMO_ShakeScrn_Start( p_eff->p_shake, 4*FX32_ONE, 0, FLD_DEMO_LEGEND_SHAKEFLASH_SHAKE_SYNC, 12, p_eff->copy_camera );
			p_eff->seq++;
		}
		break;
		
	case FLD_DEMO_LEGEND_SHAKEFLASH_END:
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	バンバンフラッシュ	初期化
 *
 *	@param	p_eff		エフェクトワーク
 *	@param	p_flash		フラッシュオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Init( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff, FLD_DEMO_FLASH* p_flash )
{
	p_eff->seq	= 0;
	p_eff->wait = FLD_DEMO_LEGEND_BANBAN_START_WAIT; 
	p_eff->p_flash = p_flash;
}

//----------------------------------------------------------------------------
/**
 *		【伝説ポケモン出現】
 *	@brief	バンバンフラッシュ	メイン
 *
 *	@param	p_eff	エフェクトワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL FLDMAP_DEMO_LegendPokeApp_Eff_BanBanFlash_Main( FLDMAP_DEMO_LEGEND_BANBANFLASH* p_eff )
{
	switch( p_eff->seq ){
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASHWAIT:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			p_eff->seq ++;
		}
		break;

	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH00:
		FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 8 );
		p_eff->seq++;
		p_eff->wait = 16;
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH01:
		p_eff->wait --;
		
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 8 );
			p_eff->seq++;
			p_eff->wait = 16;
		}
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_FLASH02:
		p_eff->wait --;
		
		if( p_eff->wait < 0 ){
			FLD_DEMO_Flash_Start( p_eff->p_flash, FLD_DEMO_LEGEND_SHAKEFLASH_ALPHAMAX, 4, 32 );
			p_eff->seq++;
			p_eff->wait = 40;
		}
		break;
		
	case FLD_DEMO_LEGEND_BANBANFLASH_END:
		p_eff->wait --;
		if( p_eff->wait < 0 ){
			return TRUE;
		}
		break;
	}

	return FALSE;
}





//-----------------------------------------------------------------------------
/**
 * 
 *		黒いワッカ放出
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	黒ワッカ放出シーケンス
//=====================================
enum{
	FLDMAP_DEMO_BLACKRING_END,
};
#define FLDMAP_DEMO_BLACKRING_TASK_PRI	( 1024 )
#define FLDMAP_DEMO_BLACKRING_OBJID	( D05R0114_SPPOKE_01 )	// 出現させるイアエアの管理ID

//-------------------------------------
//	黒いワッカ放出ワーク
//=====================================
typedef struct {
	FLD_DEMO_BLACK_RING* p_blackring;
} FLDMAP_DEMO_BLACKRING;

//----------------------------------------------------------------------------
/**
 *		【黒いワッカ放出】
 *	@brief	初期化処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;
	FIELD_OBJ_PTR fldobj;
	u16 x, y, z;
	
	// イアエアを求める
	fldobj = FieldOBJSys_OBJIDSearch( p_fsys->fldobjsys, FLDMAP_DEMO_BLACKRING_OBJID );
	GF_ASSERT( fldobj );
	x = FieldOBJ_NowPosGX_Get( fldobj );
	y = 0;	// 0共通
	z = FieldOBJ_NowPosGZ_Get( fldobj );

	// 黒ワッカ
	p_br->p_blackring = FLD_DEMO_BlackRing_Alloc( USE_HEAPID );

	// 黒Ring放出
	FLD_DEMO_BlackRing_Start( p_br->p_blackring, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *		【黒いワッカ放出】
 *	@brief	破棄処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;
	
	// 黒ワッカ
	FLD_DEMO_BlackRing_Free( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		【黒いワッカ放出】
 *	@brief	メイン処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;

	// 黒ワッカメイン
	FLD_DEMO_BlackRing_Main( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		【黒いワッカ放出】
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_BlackRing_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_BLACKRING* p_br = p_work;

	// 黒ワッカ描画
	FLD_DEMO_BlackRing_Draw( p_br->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *	@brief	黒いワッカ放出　デモ開始
 *
 *	@param	fsys	フィールドシステムワーク
 *
 *	@return	デモワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_BlackRing_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_BLACKRING_TASK_PRI,
		sizeof(FLDMAP_DEMO_BLACKRING),
		FLDMAP_DEMO_BlackRing_Init,
		FLDMAP_DEMO_BlackRing_Delete,
		FLDMAP_DEMO_BlackRing_Main,
		FLDMAP_DEMO_BlackRing_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	黒いワッカ放出　デモ終了
 *
 *	@param	p_demo ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_BlackRing_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//-----------------------------------------------------------------------------
/**
 * 
 *		ありの卵
 * 
 */
//-----------------------------------------------------------------------------
#define FLDMAP_DEMO_ANTEGG_TASK_PRI	( 1024 )

//-------------------------------------
//	ありの卵ワーク
//=====================================
typedef struct {
	u32 seq;		// シーケンス
	FLD_DEMO_ANTEGG* p_antegg;
	FLD_DEMO_BLACK_RING* p_blackring;
} FLDMAP_DEMO_ANTEGG;

//----------------------------------------------------------------------------
/**
 *		【ありの卵】
 *	@brief	初期化処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEggCut00_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

#if ( PM_VERSION == VERSION_DIAMOND )

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0x1701, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xc8a55, p_fsys->camera_ptr );
	matrix.x = 0x2280ef;
	matrix.y = 0xca424;
	matrix.z = 0x268c50;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x22a2;
	angle.y = 0xf800;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 2*FX32_ONE, 2000*FX32_ONE, p_fsys->camera_ptr );

#elif( PM_VERSION == VERSION_PEARL )

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0x10c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xD5052, p_fsys->camera_ptr );
	matrix.x = 0x1bffbd;
	matrix.y = 0xaa361;
	matrix.z = 0x25dfdc;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x19a3;
	angle.y = 0x90c;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 14*FX32_ONE, 2031*FX32_ONE, p_fsys->camera_ptr );

#endif


	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut00_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat00_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}
static void FLDMAP_DEMO_AntEggCut01_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0xf81, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0x17e532, p_fsys->camera_ptr );
	matrix.x = 0xf99d58;
	matrix.y = 0xc5502;
	matrix.z = 0x28cf549;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x642;
	angle.y = 0xeda0;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );
	GFC_SetCameraClip( 88*FX32_ONE, 2000*FX32_ONE, p_fsys->camera_ptr );

	// LIGHT設定変更
	DellLightCont( &p_fsys->light_cont_data );
	p_fsys->light_cont_data = InitLightCont( p_fsys->glst_data, LIGHT_TYPE3 );

	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut01_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat01_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}
static void FLDMAP_DEMO_AntEggCut02_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0x4c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0x26bec1, p_fsys->camera_ptr );
	matrix.x = 0x1df5dfd;
	matrix.y = 0x73a0c;
	matrix.z = 0x2b9f4a2;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x4c2;
	angle.y = 0xa40;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 176*FX32_ONE, 1480*FX32_ONE, p_fsys->camera_ptr );


	// LIGHT設定変更
	DellLightCont( &p_fsys->light_cont_data );
	p_fsys->light_cont_data = InitLightCont( p_fsys->glst_data, LIGHT_TYPE3 );

	p_dwk->p_antegg = FLD_DEMO_AntEgg_Cut_Alloc( USE_HEAPID );
	p_dwk->p_blackring = FLD_DEMO_BlackRing_AntEggCat_Alloc( USE_HEAPID );
	matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
	FLD_DEMO_AntEgg_Cut02_Start( p_dwk->p_antegg, matrix.x, matrix.y, matrix.z );
	FLD_DEMO_BlackRing_AntEggCat02_Start( p_dwk->p_blackring, matrix.x, matrix.y, matrix.z );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵】
 *	@brief	破棄処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Free( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Free( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵】
 *	@brief	メイン処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Main( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Main( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵】
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_AntEgg_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_ANTEGG* p_dwk = p_work;

	FLD_DEMO_AntEgg_Cut_Draw( p_dwk->p_antegg );
	FLD_DEMO_BlackRing_AntEggCat_Draw( p_dwk->p_blackring );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ありの卵　デモ開始
 *
 *	@param	fsys		フィールドシステムワーク
 *	@param	cut			カット
 *
 *	@return	デモワーク
 *
 *	FLDMAP_DEMO_ANTEGG_CUT00		カット00
 *	FLDMAP_DEMO_ANTEGG_CUT01		カット01
 *	FLDMAP_DEMO_ANTEGG_CUT02		カット02
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_AntEgg_Start( FIELDSYS_WORK* fsys, u32 cut )
{
	static FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_ANTEGG_TASK_PRI	,
		sizeof(FLDMAP_DEMO_ANTEGG),
		NULL,
		FLDMAP_DEMO_AntEgg_Delete,
		FLDMAP_DEMO_AntEgg_Main,
		FLDMAP_DEMO_AntEgg_Draw
	};
	static const FLDMAPFUNC_CREATE FLDMAP_DEMO_Create[] = {
		FLDMAP_DEMO_AntEggCut00_Init,
		FLDMAP_DEMO_AntEggCut01_Init,
		FLDMAP_DEMO_AntEggCut02_Init,
	};
	FLDMAPFUNC_WORK* p_fwk;

	FLDMAP_DEMO_Data.create_func = FLDMAP_DEMO_Create[ cut ];
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ありの卵　デモ終了
 *
 *	@param	p_demo	デモワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_AntEgg_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}



//-----------------------------------------------------------------------------
/**
 * 
 *		銀河放出
 * 
 */
//-----------------------------------------------------------------------------
#define FLDMAP_DEMO_GINGA_TASK_PRI		( 1024 )
#define FLDMAP_DEMO_GINGA_Y_OFS			( FX32_CONST( 0x2 ) )
#define FLDMAP_DEMO_GINGA_DARKOFF_WAIT	( 64 )
//-------------------------------------
//	銀河放出ワーク
//=====================================
typedef struct {
	u32 seq;		// シーケンス
	u32 wait;		// 待ち時間などに使用
	FLD_DEMO_GINGA* p_ginga;	//　銀河放出
	FLD_DEMO_DARKLIGHT* p_dark;	// ダークライト
} FLDMAP_DEMO_GINGA;

//----------------------------------------------------------------------------
/**
 *		【銀河放出】
 *	@brief	初期化処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Init(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;

	p_dwk->p_ginga = FLD_DEMO_GINGA_Alloc( p_fsys );
	p_dwk->p_dark = FLD_DEMO_DarkLight_Alloc( USE_HEAPID, p_fsys );
	p_dwk->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *		【銀河放出】
 *	@brief	破棄処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Delete(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;
	
	FLD_DEMO_GINGA_Free( p_dwk->p_ginga );
	FLD_DEMO_DarkLight_Free( p_dwk->p_dark );
}

//----------------------------------------------------------------------------
/**
 *		【銀河放出】
 *	@brief	メイン処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Main(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;
	u32 result[2];
	VecFx32 matrix;

	switch( p_dwk->seq ){
	case FLDMAP_DEMO_GINGA_SEQ_START:
		matrix = GFC_GetLookTarget( p_fsys->camera_ptr );
		FLD_DEMO_GINGA_Init( p_dwk->p_ginga, matrix.x, matrix.y + FLDMAP_DEMO_GINGA_Y_OFS, matrix.z );
		FLD_DEMO_DarkLight_Start( p_dwk->p_dark );
		p_dwk->seq++;
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEUP:
		result[0] = FLD_DEMO_GINGA_GetState( p_dwk->p_ginga );
		result[1] = FLD_DEMO_DarkLight_GetState( p_dwk->p_dark );
		
		if( (result[0] == FLD_DEMO_GINGA_MOTIONBL_REQWAIT) &&
			(result[1] == FLD_DEMO_DARKLIGHT_ENDWAIT)){	
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT:
		break;

	case FLDMAP_DEMO_GINGA_SEQ_ENDREQ:
		FLD_DEMO_GINGA_EndReq( p_dwk->p_ginga );
		p_dwk->wait = FLDMAP_DEMO_GINGA_DARKOFF_WAIT;
		p_dwk->seq++;
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT:
		p_dwk->wait --;
		if( p_dwk->wait <= 0 ){
			FLD_DEMO_DarkLight_EndReq( p_dwk->p_dark );
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF:
		result[0] = FLD_DEMO_GINGA_GetState( p_dwk->p_ginga );
		result[1] = FLD_DEMO_DarkLight_GetState( p_dwk->p_dark );
		
		if( (result[0] == FLD_DEMO_GINGA_MOTIONBL_END) &&
			(result[1] == FLD_DEMO_DARKLIGHT_END)){	
			p_dwk->seq++;
		}
		break;
		
	case FLDMAP_DEMO_GINGA_SEQ_END:
		break;

	default:
		break;
	}
	
	FLD_DEMO_GINGA_Main( p_dwk->p_ginga );
	FLD_DEMO_DarkLight_Main( p_dwk->p_dark );
}

//----------------------------------------------------------------------------
/**
 *		【銀河放出】
 *	@brief	描画処理
 */
//-----------------------------------------------------------------------------
static void FLDMAP_DEMO_Ginga_Draw(FLDMAPFUNC_WORK * p_fwk, FIELDSYS_WORK * p_fsys, void * p_work)
{
	FLDMAP_DEMO_GINGA* p_dwk = p_work;


	FLD_DEMO_GINGA_Draw( p_dwk->p_ginga );
}


//----------------------------------------------------------------------------
/**
 *	@brief	銀河デモ開始
 *
 *	@param	fsys	フィールドシステムワーク
 *
 *	@return	デモワーク
 */
//-----------------------------------------------------------------------------
FLDMAPFUNC_WORK* FLDMAP_DEMO_Ginga_Start( FIELDSYS_WORK* fsys )
{
	static const FLDMAPFUNC_DATA FLDMAP_DEMO_Data = {
		FLDMAP_DEMO_GINGA_TASK_PRI,
		sizeof(FLDMAP_DEMO_GINGA),
		FLDMAP_DEMO_Ginga_Init,
		FLDMAP_DEMO_Ginga_Delete,
		FLDMAP_DEMO_Ginga_Main,
		FLDMAP_DEMO_Ginga_Draw
	};
	FLDMAPFUNC_WORK* p_fwk;
	p_fwk = FLDMAPFUNC_Create( fsys->fldmap->fmapfunc_sys, &FLDMAP_DEMO_Data );
	return p_fwk;
}

//----------------------------------------------------------------------------
/**
 *	@brief	銀河デモ　終了
 *
 *	@param	p_demo	デモワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_Ginga_End( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAPFUNC_Delete( p_demo );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了リクエスト
 *
 *	@param	p_demo	デモワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLDMAP_DEMO_Ginga_EndReq( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_GINGA* p_dwk = FLDMAPFUNC_GetFreeWork( p_demo );
	p_dwk->seq = FLDMAP_DEMO_GINGA_SEQ_ENDREQ;
}

//----------------------------------------------------------------------------
/**
 *	@brief	銀河の現在のシーケンス取得
 *
 *	@param	p_demo	デモワーク
 *
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_START,		// エフェクト開始
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEUP,		// 銀河拡大
 * 	@retval	FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT,	// 終了リクエスト待ち
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_ENDREQ,		// 終了エフェクト開始
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT,	// 銀河縮
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF,	// 銀河縮小＋明るく
 *	@retval	FLDMAP_DEMO_GINGA_SEQ_END			// 終了
 */         
//-----------------------------------------------------------------------------
u32 FLDMAP_DEMO_Ginga_GetState( FLDMAPFUNC_WORK* p_demo )
{
	FLDMAP_DEMO_GINGA* p_dwk = FLDMAPFUNC_GetFreeWork( p_demo );
	return p_dwk->seq;
}




//-----------------------------------------------------------------------------
/**
 *
 *		ここからは、個々のエフェクト単体
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *
 *
 *		汎用動作
 * 
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
//	動作ワーク
//=====================================
typedef struct {
	s32 data;
	s32 s_data;
	s32 add_data;
	s32 count_max;
} FLD_DEMO_MOVE_PARAM;

//-------------------------------------
//	動作ワーク
//=====================================
typedef struct {
	fx32 data;
	fx32 s_data;
	fx32 add_data;
	s32 count_max;
} FLD_DEMO_MOVE_PARAM_FX;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit( FLD_DEMO_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count );
static BOOL FLD_DEMO_MoveMain( FLD_DEMO_MOVE_PARAM* p_data, s32 count );
static void FLD_DEMO_MoveInit_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, fx32 s_num, fx32 e_num, s32 count );
static BOOL FLD_DEMO_MoveMain_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, s32 count );

// モデル
static void FLD_DEMO_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap );
static void FLD_DEMO_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl );

// アニメ
static void FLD_DEMO_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator );
static void FLD_DEMO_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator );
static BOOL FLD_DEMO_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjAnmLoopAdd( FLD_3DOBJ_ANM* p_anm, fx32 add );
static void FLD_DEMO_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num );
static fx32 FLD_DEMO_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm );

// 描画オブジェ
static void FLD_DEMO_3DObjDrawInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* cp_mdl );
static void FLD_DEMO_3DObjDrawAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm );
static void FLD_DEMO_3DObjDrawDraw( FLD_3DOBJ* p_draw );
static void FLD_DEMO_3DObjDrawSetDraw( FLD_3DOBJ* p_draw, BOOL flag );
static BOOL FLD_DEMO_3DObjDrawGetDraw( const FLD_3DOBJ* cp_draw );
static void FLD_DEMO_3DObjDrawSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_3DObjDrawGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
static void FLD_DEMO_3DObjDrawSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_3DObjDrawGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z );
static void FLD_DEMO_3DObjDrawSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way );
static u16 FLD_DEMO_3DObjDrawGetRota( FLD_3DOBJ* p_draw, u32 way );



//----------------------------------------------------------------------------
/**
 *	@brief	動作パラメータ
 *
 *	@param	p_data	ワーク
 *	@param	s_num	開始値
 *	@param	e_num	終了値
 *	@param	count	最大カウント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit( FLD_DEMO_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作計算部分
 *
 *	@param	p_data
 *	@param	count	現在カウント
 *
 *	@retval TRUE	終了
 *	@retval	FALSE	つうじょう
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_MoveMain( FLD_DEMO_MOVE_PARAM* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	s32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// 計算
	num = p_data->add_data * local_count;
	num = num / p_data->count_max;
	num += p_data->s_data;

	// 設定
	p_data->data = num;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	FX３２　での汎用計算関数
 *
 *	@param	p_data		ワーク
 *	@param	s_num		開始値
 *	@param	e_num		終了値
 *	@param	count		ｶｳﾝﾀ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_MoveInit_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, fx32 s_num, fx32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	FX３２　汎用動作関数メイン
 *
 *	@param	p_data	ワーク
 *	@param	count	カウント値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_MoveMain_FX( FLD_DEMO_MOVE_PARAM_FX* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	fx32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// 計算
	num = FX_Mul( p_data->add_data, local_count << FX32_SHIFT );
	num = FX_Div( num, p_data->count_max << FX32_SHIFT );
	num += p_data->s_data;

	// 設定
	p_data->data = num;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dモデル読み込み
 *
 *	@param	p_mdl		モデルワーク
 *	@param	arc_idx		アーカイブID
 *	@param	data_idx	データIDX
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjMdlLoad( FLD_3DOBJ_MDL* p_mdl, u32 arc_idx, u32 data_idx, u32 heap )
{
	FLD_3DObjMdlLoad( p_mdl, arc_idx, data_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデルワーク破棄
 *
 *	@param	p_mdl モデルワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjMdlDelete( FLD_3DOBJ_MDL* p_mdl )
{
	FLD_3DObjMdlDelete( p_mdl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dアニメデータ読み込み
 *
 *	@param	p_anm		アニメワーク
 *	@param	cp_mdl		モデルワーク
 *	@param	arc_idx		アーカイブファイルID
 *	@param	data_idx	データIDX
 *	@param	heap		ヒープ
 *	@param	pallocator	アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoad( FLD_3DOBJ_ANM* p_anm, const FLD_3DOBJ_MDL* cp_mdl, u32 arc_idx, u32 data_idx, u32 heap, NNSFndAllocator* pallocator )
{
	FLD_3DObjAnmLoad( p_anm, cp_mdl, arc_idx, data_idx, heap, pallocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dアニメデータ破棄
 *
 *	@param	p_anm		アニメワーク
 *	@param	pallocator	アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmDelete( FLD_3DOBJ_ANM* p_anm, NNSFndAllocator* pallocator )
{
	FLD_3DObjAnmDelete( p_anm, pallocator );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生
 *
 *	@param	p_anm	アニメオブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoop( FLD_3DOBJ_ANM* p_anm )
{
	FLD_3DObjAnmLoop( p_anm, FX32_ONE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生で進める値を指定できる
 *
 *	@param	p_anm	アニメオブジェクト
 *	@param	add		進める値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmLoopAdd( FLD_3DOBJ_ANM* p_anm, fx32 add )
{
	FLD_3DObjAnmLoop( p_anm, add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループなし再生
 *
 *	@param	p_anm アニメワーク
 *
 *	@retval	TRUE	再生終了
 *	@retval	FALSE	再生途中
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_3DObjAnmNoLoop( FLD_3DOBJ_ANM* p_anm )
{
	return FLD_3DObjAnmNoLoop( p_anm, FX32_ONE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	アニメ値設定
 *
 *	@param	p_anm	アニメオブジェ
 *	@param	num		設定値
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjAnmSet( FLD_3DOBJ_ANM* p_anm, fx32 num )
{
	FLD_3DObjAnmSet( p_anm, num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメフレーム取得
 *
 *	@param	p_anm	アニメオブジェ
 *
 *	@return	フレーム数
 */
//-----------------------------------------------------------------------------
static fx32 FLD_DEMO_3DObjAnmGet( const FLD_3DOBJ_ANM* cp_anm )
{
	return FLD_3DObjAnmGet( cp_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画オブジェクト初期化
 *
 *	@param	p_draw	ワーク
 *	@param	p_mdl	モデルワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawInit( FLD_3DOBJ* p_draw, FLD_3DOBJ_MDL* p_mdl )
{
	FLD_3DObjInit( p_draw, p_mdl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメデータをリンク
 *
 *	@param	p_draw	ワーク
 *	@param	p_anm	アニメワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawAddAnm( FLD_3DOBJ* p_draw, FLD_3DOBJ_ANM* p_anm )
{
	FLD_3DObjAddAnm( p_draw, p_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデル描画
 *
 *	@param	p_draw 描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawDraw( FLD_3DOBJ* p_draw )
{
	FLD_3DObjDraw( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ設定
 *
 *	@param	p_draw	ワーク
 *	@param	flag	フラグ
 *
 *	@return	none
 *
 *	flag
 *		TRUE	表示
 *		FALSE	非表示
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetDraw( FLD_3DOBJ* p_draw, BOOL flag )
{
	FLD_3DObjSetDraw( p_draw, flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグ取得
 *
 *	@param	cp_draw		ワーク
 *
 *	@retval	TRUE	表示
 *	@retval	FALSE	非表示
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_3DObjDrawGetDraw( const FLD_3DOBJ* cp_draw )
{
	return FLD_3DObjGetDraw( cp_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標設定
 *	
 *	@param	p_draw		ワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	z			ｚ座標
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetMatrix( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	FLD_3DObjSetMatrix( p_draw, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標取得
 *
 *	@param	p_draw	ワーク
 *	@param	p_x		格納先
 *	@param	p_y		格納先
 *	@param	p_z		格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawGetMatrix( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	FLD_3DObjGetMatrix( p_draw, p_x, p_y, p_z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	x		ｘ拡縮値
 *	@param	y		ｙ拡縮値
 *	@param	z 		ｚ拡縮値
 *
 *	@return	noen
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetScale( FLD_3DOBJ* p_draw, fx32 x, fx32 y, fx32 z )
{
	FLD_3DObjSetScale( p_draw, x, y, z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値を取得
 *
 *	@param	p_draw	描画ワーク
 *	@param	p_x		ｘ座標取得先
 *	@param	p_y		ｙ座標取得先
 *	@param	p_z		ｚ座標取得先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawGetScale( FLD_3DOBJ* p_draw, fx32* p_x, fx32* p_y, fx32* p_z )
{
	FLD_3DObjGetScale( p_draw, p_x, p_y, p_z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転各設定
 *
 *	@param	p_draw	描画ワーク
 *	@param	rota	回転角
 *	@param	way		方向
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_3DObjDrawSetRota( FLD_3DOBJ* p_draw, u16 rota, u32 way )
{
	FLD_3DObjSetRota( p_draw, rota, way );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ワーク	回転角取得
 *	
 *	@param	p_draw	描画ワーク
 *	@param	way		方向
 *
 *	@return	回転角
 */
//-----------------------------------------------------------------------------
static u16 FLD_DEMO_3DObjDrawGetRota( FLD_3DOBJ* p_draw, u32 way )
{
	return FLD_3DObjGetRota( p_draw, way );
}








//-----------------------------------------------------------------------------
/**
 *
 *
 *		【画面揺らし】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	シーケンス
//=====================================
enum{
	FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT,
	FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_BACK,
	FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_FRONT,
	FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_BACK,
	FLD_DEMO_SHAKE_SCRN_SEQ_CLEAN,
	FLD_DEMO_SHAKE_SCRN_SEQ_END,
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	画面揺らしワーク
//=====================================
typedef struct _FLD_DEMO_SHAKE_SCRN{
	GF_CAMERA_PTR p_camera;		// カメラ構造体
	GF_CAMERA_PTR p_fld_camera;	// フィールドで使用されているカメラ構造体
	FLD_DEMO_MOVE_PARAM_FX move_x;
	FLD_DEMO_MOVE_PARAM_FX move_y;
	VecFx32 target;
	VecFx32 def_mat;
	u32 seq;					// シーケンス
	u32 move_count;				// 動作ｶｳﾝﾀ
	u32 shake_count;			// 揺らし数
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_Clean( FLD_DEMO_SHAKE_SCRN* p_data );
static BOOL FldScrn_ShakeScrn_Move( FLD_DEMO_SHAKE_SCRN* p_data );
static void FldScrn_ShakeScrn_DataSet( FLD_DEMO_SHAKE_SCRN* p_data, fx32 x, fx32 y );


//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	画面揺らしワーク作成
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
FLD_DEMO_SHAKE_SCRN* FLD_DEMO_ShakeScrn_Alloc( u32 heapID )
{
	FLD_DEMO_SHAKE_SCRN* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_SHAKE_SCRN) );
	memset( p_data, 0, sizeof(FLD_DEMO_SHAKE_SCRN) );

	// カメラ作成
	p_data->p_camera = GFC_AllocCamera( heapID );

	// シーケンスを終了にしておく
	p_data->seq  = FLD_DEMO_SHAKE_SCRN_SEQ_END;
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	画面揺らしワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Free( FLD_DEMO_SHAKE_SCRN* p_data )
{
	// カメラ破棄
	GFC_FreeCamera( p_data->p_camera );
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	カメラ揺らし開始
 *
 *	@param	p_data			データ格納先
 *	@param	width			揺らし幅
 *	@param	height			揺らし高さ
 *	@param	one_sync		揺らしの1ぺん(０からwidth移動する期間)
 *	@param	count			揺らし回数
 *	@param	copy_camera		いまフィールドで使われているカメラ
 *
 * one_syncについて
 *	0からwidth移動する期間のシンク数です。
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Start( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width, fx32 height, u32 one_sync, u32 count, GF_CAMERA_PTR copy_camera )
{
	// ワーク初期化
	FldScrn_ShakeScrn_Clean( p_data );

	// カメラデータコピー
	GFC_CopyCamera( copy_camera, p_data->p_camera );
	// 現在のターゲット座標取得
	p_data->target = GFC_GetLookTarget( copy_camera );
	p_data->def_mat = p_data->target;
	// ターゲット座標バインド
	GFC_BindCameraTarget( &p_data->target, p_data->p_camera );
	// カメラを有効化
	GFC_AttachCamera( p_data->p_camera );
	// フィールドで使用されているカメラ保存
	p_data->p_fld_camera = copy_camera;
		
	// 動作ワーク設定
	FLD_DEMO_MoveInit_FX( &p_data->move_x, 0, width, one_sync );
	FLD_DEMO_MoveInit_FX( &p_data->move_y, 0, height, one_sync );

	// ゆれる回数
	p_data->shake_count = count;

	// ごごごごご
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_03 );
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	画面揺らしメイン関数
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_Main( FLD_DEMO_SHAKE_SCRN* p_data )
{
	BOOL check;
	
	switch( p_data->seq ){
	case FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT:
		p_data->move_count ++;
		check = FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, p_data->move_x.data, p_data->move_y.data );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_BACK:
		p_data->move_count --;
		FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, p_data->move_x.data, p_data->move_y.data );
		if( p_data->move_count <= 0 ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_FRONT:
		p_data->move_count ++;
		check = FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, -p_data->move_x.data, -p_data->move_y.data );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_RIGHTDOWN_BACK:
		p_data->move_count --;
		FldScrn_ShakeScrn_Move( p_data );
		FldScrn_ShakeScrn_DataSet( p_data, -p_data->move_x.data, -p_data->move_y.data );
		if( p_data->move_count <= 0 ){

			// 揺らし数が０になったら終わり
			p_data->shake_count --;
			if( p_data->shake_count > 0 ){
				p_data->seq = FLD_DEMO_SHAKE_SCRN_SEQ_LEFTUP_FRONT;
			}else{
				p_data->seq ++;
			}
		}
		break;

	case FLD_DEMO_SHAKE_SCRN_SEQ_CLEAN:
		// カメラを元に戻す
		GFC_AttachCamera( p_data->p_fld_camera );
		p_data->seq ++;
		break;
		
	case FLD_DEMO_SHAKE_SCRN_SEQ_END:
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	カメラ揺らし終了チェック
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_ShakeScrn_EndCheck( FLD_DEMO_SHAKE_SCRN* p_data )
{
	if( p_data->seq == FLD_DEMO_SHAKE_SCRN_SEQ_END ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	ワークの初期化
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_Clean( FLD_DEMO_SHAKE_SCRN* p_data )
{
	memset( &p_data->move_x, 0, sizeof(FLD_DEMO_MOVE_PARAM_FX) );
	memset( &p_data->move_y, 0, sizeof(FLD_DEMO_MOVE_PARAM_FX) );
	memset( &p_data->target, 0, sizeof(VecFx32) );
	p_data->seq = 0;					// シーケンス
	p_data->move_count = 0;				// 動作ｶｳﾝﾀ
	p_data->shake_count = 0;			// 揺らし数
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	計算
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL FldScrn_ShakeScrn_Move( FLD_DEMO_SHAKE_SCRN* p_data )
{
	BOOL check;
	check = FLD_DEMO_MoveMain_FX( &p_data->move_x, p_data->move_count );
	FLD_DEMO_MoveMain_FX( &p_data->move_y, p_data->move_count );
	return check;
}

//----------------------------------------------------------------------------
/**
 *		【画面揺らし】
 *	@brief	ワーク足し算
 *
 *	@param	p_data	ワーク
 *	@param	x		ｘ方向
 *	@param	y		ｙ方向
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldScrn_ShakeScrn_DataSet( FLD_DEMO_SHAKE_SCRN* p_data, fx32 x, fx32 y )
{
	p_data->target.x = p_data->def_mat.x + x;
	p_data->target.y = p_data->def_mat.y + y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在残りゆれ数を返す
 *
 *	@param	p_data	ワーク
 *
 *	@return	残りゆれ数
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_ShakeScrn_GetNowCount( const FLD_DEMO_SHAKE_SCRN* p_data )
{
	return p_data->shake_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在のゆれ幅を返す
 *
 *	@param	p_data	ワーク
 *
 *	@return	ゆれ幅
 */
//-----------------------------------------------------------------------------
fx32 FLD_DEMO_ShakeScrn_GetNowShakeWidth( const FLD_DEMO_SHAKE_SCRN* p_data )
{
	return p_data->move_x.add_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゆれ幅を設定
 *
 *	@param	p_data	ワーク
 *	@param	width	ゆれ幅
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_ShakeScrn_SetNowShakeWidth( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width )
{
	p_data->move_x.add_data = width;
}




//-----------------------------------------------------------------------------
/**
 *
 *
 *		【フラッシュ】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	フラッシュシーケンス
//=====================================
enum{
	FLD_DEMO_FLASH_ADD,
	FLD_DEMO_FLASH_SUB,
	FLD_DEMO_FLASH_CLEAN,
	FLD_DEMO_FLASH_END
};

#define FLD_DEMO_FLASH_ALPHASET_TCB	( 1024 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	フラッシュワーク
//=====================================
typedef struct _FLD_DEMO_FLASH{
	FLD_DEMO_MOVE_PARAM alpha;	// α動作
	int count;					// ｶｳﾝﾀ
	u32 alphamax;				// α最大値
	u32 in_sync;				// フラッシュイン時のシンク数
	int seq;
	TCB_PTR	setalpha_tcb;		// α値を設定するTCB
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FldDemo_FlashSetAlphaTcb( TCB_PTR tcb, void* p_work );

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	フラッシュワーク確保　グラフィックデータ設定
 *
 *	@param	heapID	ヒープ
 *	@param	p_bgini	BGコントロール
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_FLASH* FLD_DEMO_Flash_Alloc( u32 heapID )
{
	FLD_DEMO_FLASH* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_FLASH) );
	memset( p_data, 0, sizeof(FLD_DEMO_FLASH) );

	// シーケンスを終了シーケンスにする
	p_data->seq = FLD_DEMO_FLASH_END;

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	フラッシュ破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Free( FLD_DEMO_FLASH* p_data )
{
	if( p_data->setalpha_tcb ){
		TCB_Delete( p_data->setalpha_tcb );
		p_data->setalpha_tcb = NULL;
	} 
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	フラッシュ開始
 *
 *	@param	p_data		ワーク
 *	@param	alphamax	最大α値
 *	@param	out_sync	フラッシュアウトシンク数
 *	@param	out_sync	フラッシュインシンク数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Start( FLD_DEMO_FLASH* p_data, u32 alphamax, u32 out_sync, u32 in_sync )
{
	// 今動作中のときは、タスクだけ破棄する
	if(p_data->seq != FLD_DEMO_FLASH_END){ 
		if( p_data->setalpha_tcb != NULL ){
			TCB_Delete( p_data->setalpha_tcb );
			p_data->setalpha_tcb = NULL;
		} 
	}
	
	FLD_DEMO_MoveInit( &p_data->alpha, 0, alphamax, out_sync );
	p_data->count = 0;
	p_data->seq = FLD_DEMO_FLASH_ADD;
	p_data->in_sync = in_sync;
	p_data->alphamax = alphamax;

	// ﾏｽﾀｰ輝度
	GX_SetMasterBrightness( p_data->alpha.data );

	// α値設定タスク登録
//	p_data->setalpha_tcb = VIntrTCB_Add( FldDemo_FlashSetAlphaTcb, p_data, FLD_DEMO_FLASH_ALPHASET_TCB );
	p_data->setalpha_tcb = VWaitTCB_Add( FldDemo_FlashSetAlphaTcb, p_data, FLD_DEMO_FLASH_ALPHASET_TCB );

	// フラッシュ！
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_02 );
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	終了チェック
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_Flash_EndCheck( FLD_DEMO_FLASH* p_data )
{
	if( p_data->seq == FLD_DEMO_FLASH_END ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	フラッシュメイン処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_Flash_Main( FLD_DEMO_FLASH* p_data )
{
	BOOL check;
	
	switch( p_data->seq ){
	case FLD_DEMO_FLASH_ADD:
		p_data->count++;
		check = FLD_DEMO_MoveMain( &p_data->alpha, p_data->count );

		if( check == TRUE ){
			FLD_DEMO_MoveInit( &p_data->alpha, p_data->alphamax, 0, p_data->in_sync );
			p_data->count = 0;
			p_data->seq ++;
		}
		break;
		
	case FLD_DEMO_FLASH_SUB:
		p_data->count++;
		check = FLD_DEMO_MoveMain( &p_data->alpha, p_data->count );
		if( check == TRUE ){
			p_data->seq ++;
		}
		break;

	case FLD_DEMO_FLASH_CLEAN:
		// α設定TCB破棄
		TCB_Delete( p_data->setalpha_tcb );
		p_data->setalpha_tcb = NULL;

		p_data->seq ++;
		break;
		
	case FLD_DEMO_FLASH_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のα値を取得
 */
//-----------------------------------------------------------------------------
int FLD_DEMO_Flash_GetAlpha( const FLD_DEMO_FLASH* cp_data )
{
	return cp_data->alpha.data;
}

//----------------------------------------------------------------------------
/**
 *		【フラッシュ】
 *	@brief	α値Vブランク期間設定タスク
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_FlashSetAlphaTcb( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_FLASH* p_data = p_work;
	// α設定
	GX_SetMasterBrightness( p_data->alpha.data );
}





//-----------------------------------------------------------------------------
/**
 *
 *
 *		【銀河デモ】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define FLD_DEMO_GINGA_MOTION_BL_EVA	( 8 )
#define FLD_DEMO_GINGA_MOTION_BL_EVB	( 8 )


// 描画関係
// ソフトウェアスプライト
#define FLD_DEMO_GINGA_SWSP_OBJNUM		(1)		// SWSPオブジェクト数
#define FLD_DEMO_GINGA_SWSP_CHARNUM	(1)		// SWSPオブジェクト数
#define FLD_DEMO_GINGA_SWSP_PLTTNUM	(1)		// SWSPオブジェクト数


//-------------------------------------
//	銀河オブジェクトデータ
//=====================================
#define FLD_DEMO_GINGA_OBJ_ROTA_ADD		( FX32_CONST( 2.0f ) )
#define FLD_DEMO_GINGA_OBJ_ROTA_SUB		( -FX32_CONST(0.050f) )
#define FLD_DEMO_GINGA_OBJ_SUB_ROTA_ADD	( -FX32_CONST( 40.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_S	( FX32_CONST( 0.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_E	( FX32_CONST( 1.0f ) )
#define FLD_DEMO_GINGA_OBJ_SCAL_COUNT	( 128 )	// 拡大にかかる値
#define FLD_DEMO_GINGA_OBJ_SCAL_SUB_COUNT	( 32 )	// 縮小にかかる値
#define FLD_DEMO_GINGA_OBJ_WAIT_COUNT		( 8 )	// 拡大から縮小の時の、weight
#define FLD_DEMO_GINGA_OBJ_FLASH_S_NUM	( FX32_CONST( 0.40f ) )

enum{
	FLD_DEMO_GINGA_OBJ_SCALE_UP,
	FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT,
	FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH,
	FLD_DEMO_GINGA_OBJ_ROTA_STOP,
	FLD_DEMO_GINGA_OBJ_WAIT,
	FLD_DEMO_GINGA_OBJ_SCALE_DOWN,
};

#define FLD_DEMO_GINGA_ANM_NUM	(2)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	銀河オブジェクト
//=====================================
typedef struct {
	FLD_3DOBJ		draw;		// 描画オブジェクト
	FLD_3DOBJ_MDL	mdl;		// モデル
	FLD_3DOBJ_ANM	anm[FLD_DEMO_GINGA_ANM_NUM];		// アニメ

	FLD_DEMO_FLASH* p_flash;	// フラッシュオブジェクト

	// 動作パラメータ
	FLD_DEMO_MOVE_PARAM_FX scale;
	int count;
	int wait;
	TCB_PTR tcb;
	s32 rota_add;
	u16 rota;
	u16 seq;	// シーケンス

	fx32 x_scale_way;	// 1or-1
} FLD_DEMO_CLM_GINGA;


//-------------------------------------
//	フィールドグラフィック状態保存領域
//=====================================
typedef struct _FLD_DEMO_GINGA{
	FIELDSYS_WORK * fsys;			// フィールドシステム
	
	FLD_DEMO_MOTIONBL motion_bl;

	// 銀河オブジェクト
	FLD_DEMO_CLM_GINGA ginga;


	// アロケータ
	NNSFndAllocator allocator;

	// ステータス
	u32 status;

	// ローカルシーケンス
	u32 sub_sequence;

	fx32 x;
	fx32 y;
	fx32 z;
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

static void FLD_DEMO_GINGA_DeleteReq( FLD_DEMO_GINGA* p_data );


// 初期化　破棄　大本タスク
static void FLD_DEMO_CLM_InitDrawSystem( TCB_PTR tcb, void* p_work );
static void FLD_DEMO_CLM_DeleteDrawSystem( TCB_PTR tcb, void* p_work );

// ソフトウェアスプライト初期化 破棄
static SWSP_SYS_PTR FLD_DEMO_CLM_InitSwsp( void );
static void FLD_DEMO_CLM_DeleteSwsp( SWSP_SYS_PTR swsp );

// 銀河オブジェクト
static void FLD_DEMO_CLM_GingaObjInit( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator, u32 heapID, fx32 x, fx32 y, fx32 z );
static void FLD_DEMO_CLM_GingaObjDelete( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator );
static BOOL FLD_DEMO_CLM_GingaObjMain( FLD_DEMO_CLM_GINGA* p_obj );
static void FLD_DEMO_CLM_GingaObjEndReq( FLD_DEMO_CLM_GINGA* p_obj );


//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	銀河デモワーク作成
 *
 *	@param	heapID	ヒープ
 *	@param	fsys	フィールドシステム
 *
 *	@return	銀河ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_GINGA* FLD_DEMO_GINGA_Alloc( FIELDSYS_WORK * fsys )
{
	FLD_DEMO_GINGA* p_tmp;
	p_tmp = sys_AllocMemory( USE_HEAPID, sizeof(FLD_DEMO_GINGA) );
	memset( p_tmp, 0, sizeof(FLD_DEMO_GINGA) );

	// FSYSを保存
	p_tmp->fsys = fsys;

	// 状態を終了にしておく
	p_tmp->status = FLD_DEMO_GINGA_MOTIONBL_END;

	// アロケータ作成
	sys_InitAllocator( &p_tmp->allocator, USE_HEAPID, 32 );

	return p_tmp;
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	ワーク破棄処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Free( FLD_DEMO_GINGA* p_data )
{
	// 破棄出来ません
	GF_ASSERT( p_data->status == FLD_DEMO_GINGA_MOTIONBL_END );
	sys_FreeMemoryEz( p_data );
}


//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	処理初期化
 *
 *	@param	p_data	銀河ワーク
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	z		ｚ座標
 *
 *	@return	フィールドグラフィック状態保存領域
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Init( FLD_DEMO_GINGA* p_data, fx32 x, fx32 y, fx32 z )
{
	// 状態設定
	p_data->status = FLD_DEMO_GINGA_MOTIONBL_INIT;

	// 表示座標を格納
	p_data->x = x;
	p_data->y = y;
	p_data->z = z;

	// 初期化タスク登録
	TCB_Add( FLD_DEMO_CLM_InitDrawSystem, p_data, FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	銀河デモ終了リクエスト
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 *
 *	このリクエストで銀河がしぼんでデモが終わります
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_EndReq( FLD_DEMO_GINGA* p_data )
{
	GF_ASSERT( p_data->status == FLD_DEMO_GINGA_MOTIONBL_REQWAIT );

	p_data->status = FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN;
	FLD_DEMO_CLM_GingaObjEndReq( &p_data->ginga );
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	銀河デモ破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_GINGA_DeleteReq( FLD_DEMO_GINGA* p_data )
{
	p_data->sub_sequence = 0;
	p_data->status = FLD_DEMO_GINGA_MOTIONBL_DELETE;

	// 破棄タスク登録
	TCB_Add( FLD_DEMO_CLM_DeleteDrawSystem, p_data, FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI );
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	現在の状態取得
 *	
 *	@param	cp_data	ワーク
 *
 *	@retval	DEMO_GINGA_MOTIONBL_INIT,			// 初期化中
 *	@retval	FLD_DEMO_GINGA_MOTIONBL_SCALEUP,	// 拡大中
 * 	@retval	FLD_DEMO_GINGA_MOTIONBL_REQWAIT,	// 縮小リクエスト待ち
 *	@retval	FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN,	// 縮小中
 *	@retval	DEMO_GINGA_MOTIONBL_DELTE,			// 破棄処理中
 *	@retval	DEMO_GINGA_MOTIONBL_END				// 全作業終了 or 初期化前
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_GINGA_GetState( const FLD_DEMO_GINGA* cp_data )
{
	return cp_data->status;
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	モーションブラー係数の設定
 *
 *	@param	p_data		ワーク
 *	@param	a			Capture元係数
 *	@param	b			Capture先係数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_SetMotionBlNum( FLD_DEMO_GINGA* p_data, int a, int b )
{
	MOTION_BL_ParamChg( p_data->motion_bl.motion_bl, a, b );
}


//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	デモ描画処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Draw( FLD_DEMO_GINGA* p_data )
{
	if( (p_data->status == FLD_DEMO_GINGA_MOTIONBL_INIT) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_DELETE) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_END) ){
		return ;
	}
	
	// クリア
	G3_Identity();	

	NNS_G3dGePushMtx();
	{
		FLD_DEMO_3DObjDrawDraw( &p_data->ginga.draw );
	}
	NNS_G3dGePopMtx(1);
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	メイン関数
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_GINGA_Main( FLD_DEMO_GINGA* p_data )
{
	BOOL result;
	
	if( (p_data->status == FLD_DEMO_GINGA_MOTIONBL_INIT) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_DELETE) ||
		(p_data->status == FLD_DEMO_GINGA_MOTIONBL_END) ){
		return ;
	}
	
	result = FLD_DEMO_CLM_GingaObjMain( &p_data->ginga );

	// 銀河のシーケンスがFLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT
	// になったら縮小リクエスト待ち状態
	if( p_data->status == FLD_DEMO_GINGA_MOTIONBL_SCALEUP ){
		if( p_data->ginga.seq == FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT ){
			p_data->status = FLD_DEMO_GINGA_MOTIONBL_REQWAIT;
		}
	}

	// 終了リクエスト
	if( result == TRUE ){
		FLD_DEMO_GINGA_DeleteReq( p_data );
	}
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	描画システム　初期化タスク
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_InitDrawSystem( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_GINGA* p_data = p_work;

	switch( p_data->sub_sequence ){
		
	case 0:
		FLD_DEMO_MOTIONBL_Init( &p_data->motion_bl, p_data->fsys, FLD_DEMO_GINGA_MOTION_BL_EVA, FLD_DEMO_GINGA_MOTION_BL_EVB );
		p_data->sub_sequence ++;
		break;

	case 1:
		FLD_DEMO_MOTIONBL_Main( &p_data->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_data->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_ENDWAIT ){
			p_data->sub_sequence ++;
		}
		break;

	case 2:	// 描画システムとワークの作成
		FLD_DEMO_CLM_GingaObjInit( &p_data->ginga, &p_data->allocator, USE_HEAPID,
			p_data->x, p_data->y, p_data->z	);
		p_data->sub_sequence++;
		break;
		
	case 3:
		p_data->status = FLD_DEMO_GINGA_MOTIONBL_SCALEUP;
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	描画システム　破棄タスク
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_DeleteDrawSystem( TCB_PTR tcb, void* p_work )
{
	FLD_DEMO_GINGA* p_data = p_work;

	switch( p_data->sub_sequence ){
	case 0:	// グラフィック破棄
		FLD_DEMO_CLM_GingaObjDelete( &p_data->ginga, &p_data->allocator );
		p_data->sub_sequence++;
		break;

	case 1:	// モーションブラー破棄　画面リセット
		FLD_DEMO_MOTIONBL_EndReq( &p_data->motion_bl );
		p_data->sub_sequence++;
		break;

	case 2:
		FLD_DEMO_MOTIONBL_Main( &p_data->motion_bl );
		if( FLD_DEMO_MOTIONBL_GetState( &p_data->motion_bl ) == FLD_DEMO_MOTIONBL_SEQ_END ){
			p_data->sub_sequence ++;
		}
		break;
		
	case 3:
		p_data->status = FLD_DEMO_GINGA_MOTIONBL_END;
		TCB_Delete( tcb );
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	ソフトウェアスプライト初期化
 *
 *	@return	ソフトウェアスプライトワーク
 */
//-----------------------------------------------------------------------------
static SWSP_SYS_PTR FLD_DEMO_CLM_InitSwsp( void )
{
	SWSP_SYSDATA swsp_sys_data = {
		FLD_DEMO_GINGA_SWSP_OBJNUM,
		FLD_DEMO_GINGA_SWSP_CHARNUM,			
		FLD_DEMO_GINGA_SWSP_PLTTNUM,
		0
	};
	swsp_sys_data.heap = USE_HEAPID;
	return SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	ソフトウェアスプライト破棄
 *
 *	@param	swsp	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_DeleteSwsp( SWSP_SYS_PTR swsp )
{
	// ソフトウェアスプライト
	SWSP_SysDelete( swsp );
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	銀河オブジェクト初期化
 *
 *	@param	p_obj			オブジェクト
 *	@param	pallocator		アロケータ
 *	@param	heapID			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjInit( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator, u32 heapID, fx32 x, fx32 y, fx32 z )
{
	int i;


	// フラッシュオブジェクト作成
	p_obj->p_flash = FLD_DEMO_Flash_Alloc( USE_HEAPID );
	
	// モデルデータ読み込み
	FLD_DEMO_3DObjMdlLoad( &p_obj->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ginga_nsbmd, heapID );

	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		// アニメ読み込み
		FLD_DEMO_3DObjAnmLoad( &p_obj->anm[i], &p_obj->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ginga_nsbca+i, heapID, pallocator );
	}
	// 描画モデル初期化
	FLD_DEMO_3DObjDrawInit( &p_obj->draw, &p_obj->mdl );
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_obj->draw, &p_obj->anm[i] );
	}
	// ざひょう
	FLD_DEMO_3DObjDrawSetMatrix( &p_obj->draw, x, y, z );
	// かくしゅくパラメータ
	FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_GINGA_OBJ_SCAL_S, FLD_DEMO_GINGA_OBJ_SCAL_E, FLD_DEMO_GINGA_OBJ_SCAL_COUNT );
	p_obj->count = 0;
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, p_obj->scale.data, p_obj->scale.data, p_obj->scale.data );
	// 回転加算値
	p_obj->rota_add  = FLD_DEMO_GINGA_OBJ_ROTA_ADD;
	// シーケンス
	p_obj->seq = FLD_DEMO_GINGA_OBJ_SCALE_UP;

	p_obj->x_scale_way = FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	銀河オブジェクト破棄
 *	
 *	@param	p_obj	オブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjDelete( FLD_DEMO_CLM_GINGA* p_obj, NNSFndAllocator* pallocator )
{
	int i;
	
	//　モデル破棄
	FLD_DEMO_3DObjMdlDelete( &p_obj->mdl );
	
	//　アニメ破棄
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_obj->anm[i], pallocator );
	}

	FLD_DEMO_Flash_Free( p_obj->p_flash );

	memset( p_obj, 0, sizeof(FLD_DEMO_CLM_GINGA) );
}

//----------------------------------------------------------------------------
/**
 *		【銀河デモ】
 *	@brief	銀河オブジェクトメイン
 *
 *	@param	p_obj	オブジェクト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL FLD_DEMO_CLM_GingaObjMain( FLD_DEMO_CLM_GINGA* p_obj )
{
	BOOL result;
	int i;
	
	// 拡大縮小
	result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, FX_Mul( p_obj->scale.data, p_obj->x_scale_way ), FX32_ONE, p_obj->scale.data );

	// アニメ
	for( i=0; i<FLD_DEMO_GINGA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoopAdd( &p_obj->anm[i], p_obj->rota_add );	
	}

	// フラッシュメイン
	FLD_DEMO_Flash_Main( p_obj->p_flash );

	switch( p_obj->seq ){
	case FLD_DEMO_GINGA_OBJ_SCALE_UP:
		if( result != TRUE ){
			p_obj->count ++;
		}else{
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_SCALE_DOWN_WAIT:
		break;
		
	case FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH:
		p_obj->rota_add += FLD_DEMO_GINGA_OBJ_ROTA_SUB;

		if( p_obj->rota_add <= FLD_DEMO_GINGA_OBJ_FLASH_S_NUM ){
			FLD_DEMO_Flash_Start( p_obj->p_flash, 16, 12, 28 );
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_ROTA_STOP:
		p_obj->rota_add += FLD_DEMO_GINGA_OBJ_ROTA_SUB;

		if( p_obj->rota_add <= 0 ){
			p_obj->seq++;

			// 待ち時間
			p_obj->wait = FLD_DEMO_GINGA_OBJ_WAIT_COUNT;
		}
		break;

	case FLD_DEMO_GINGA_OBJ_WAIT:	// 待ち
		p_obj->wait --;
		if( p_obj->wait <= 0 ){
			// 引き算シーケンス
			p_obj->seq++;

			// 回転角度
			p_obj->rota_add = FLD_DEMO_GINGA_OBJ_SUB_ROTA_ADD;

			// 反転
			p_obj->x_scale_way = -FX32_ONE;
			FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, FX_Mul( p_obj->scale.data, p_obj->x_scale_way ), p_obj->scale.data, p_obj->scale.data );

			// かくしゅく
			FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_GINGA_OBJ_SCAL_E, FLD_DEMO_GINGA_OBJ_SCAL_S, FLD_DEMO_GINGA_OBJ_SCAL_SUB_COUNT );
			p_obj->count = 0;
		}
		break;
		
	case FLD_DEMO_GINGA_OBJ_SCALE_DOWN:
		if( result != TRUE ){
			p_obj->count ++;
		}else{
			// カウントダウン（縮小時）でresultがTUREなら終わり		
			if( p_obj->seq == FLD_DEMO_GINGA_OBJ_SCALE_DOWN ){
				return TRUE;
			}
		}
		break;
	
	default:
		break;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了リクエスト
 *
 *	@param	p_obj	銀河オブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_CLM_GingaObjEndReq( FLD_DEMO_CLM_GINGA* p_obj )
{
	// 回転ストップ
	p_obj->seq = FLD_DEMO_GINGA_OBJ_ROTA_STOP_FLASH;
}



//-----------------------------------------------------------------------------
/**
 *
 *		【イア・エア登場】
 *
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// デモ処理の流れ
enum{
	FLD_DEMO_LEGENDPOKE_APP_STARTWAIT,
	FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN,
	FLD_DEMO_LEGENDPOKE_APP_POKE_APP_REQ,
	FLD_DEMO_LEGENDPOKE_APP_POKE_APP,
	FLD_DEMO_LEGENDPOKE_APP_CLEAR,
	FLD_DEMO_LEGENDPOKE_APP_END,
};


// 伝説ポケモン定数
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S	( 0 )
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E	( FX32_CONST( 1.50f ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_SCALE_EDOWN	( FX32_CONST( 1 ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_COUNT		( 6 )
#define FLD_DEMO_LEGEND_POKE_OBJ_COUNTDOWN	( 2 )
#define FLD_DEMO_LEGEND_POKE_OBJ_MOVE_Y		( FX32_CONST( 32 ) )
#define FLD_DEMO_LEGEND_POKE_OBJ_MOVE_COUNT	( 44 )
enum{
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_DOWN,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_MOVE,
	FLD_DEMO_LEGENDPOKEOBJ_SEQ_END,
};

// 3Dｴﾌｪｸﾄ定数
enum{
	FLD_DEMO_LEGENDEFF_ANMOBJ_CA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_MA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_TA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_VA,
	FLD_DEMO_LEGENDEFF_ANMOBJ_NUM,
};
enum{
	FLD_DEMO_LEGENDEFF_SEQ_ANM,
	FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT,
	FLD_DEMO_LEGENDEFF_SEQ_FADEOUT,
	FLD_DEMO_LEGENDEFF_SEQ_END,
};

#define FLD_DEMO_LEGENDEFF_MOVE_Y_OFS	( 0x0*FX32_ONE )	// ポケモンのY座標だと足物を中心にするのでポケモンの中心にでるようにする
#define FLD_DEMO_LEGENDEFF_MOVE_Z_OFS	( -0x10*FX32_ONE )	// ポケモンのz座標だとポケモンとかぶるので奥にする
#define FLD_DEMO_LEGENDEFF_MOVE_Y_DIS	( FX32_CONST( 0xF8 ) )
#define FLD_DEMO_LEGENDEFF_MOVE_SYNC	( 84 )
#define FLD_DEMO_LEGENDEFF_MOVE_SYNC_OUT	( 16 )


//-------------------------------------
//	音ウエイト
//=====================================
#define FLD_DEMO_LEGENDDEFF_SND_00_WAIT	( 82 )
#define FLD_DEMO_LEGENDDEFF_SND_01_WAIT	( 72 )
#define FLD_DEMO_LEGENDDEFF_SND_04_WAIT	( 300 )
#define FLD_DEMO_LEGENDDEFF_SND_05_WAIT	( 132 )



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	伝説ポケモン動作ワーク
//=====================================
typedef struct {
	FIELD_OBJ_PTR p_fldobj;
	FLD_DEMO_MOVE_PARAM_FX scale;
	FLD_DEMO_MOVE_PARAM_FX move;
	int count;
	int seq;
} FLD_DEMO_LEGENDPOKE;

//-------------------------------------
//	伝説ポケモンの３Dｴﾌｪｸﾄオブジェクト
//=====================================
typedef struct {
	FLD_3DOBJ		draw;		// 描画オブジェクト
	FLD_3DOBJ_MDL		mdl;		// モデル
	FLD_3DOBJ_ANM		anm[FLD_DEMO_LEGENDEFF_ANMOBJ_NUM];	// アニメ
	u32 seq;
	FLD_DEMO_MOVE_PARAM_FX scale;
	int count;

	int snd_count;	// 音カウント
	int snd_seq;

#ifdef FIELD_DEMO_DEBUG
	u32 debug_count;
#endif
} FLD_DEMO_LEGEND3D_EFF;


//-------------------------------------
//	イアエア登場　ワーク
//=====================================
typedef struct _FLD_DEMO_LEGENDPOKE_APP{
	u32 seq;		// シーケンス
	FIELDSYS_WORK * fsys;	// フィールドシステム
	FLD_DEMO_LEGENDPOKE legend_poke;// 伝説ポケモン
	FLD_DEMO_LEGEND3D_EFF legend_eff;// 3DｴﾌｪｸﾄOBJ
	NNSFndAllocator allocator;
	u32 heapID;

};

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjInit( FLD_DEMO_LEGENDPOKE* p_obj, FIELDSYS_WORK * fsys, u32 obj_id );
static void FldDemo_LegendPokeObjStart( FLD_DEMO_LEGENDPOKE* p_obj );
static BOOL FldDemo_LegendPokeObjMain( FLD_DEMO_LEGENDPOKE* p_obj );
static BLACT_WORK_PTR FldDemo_LegendPokeObjFldobjGetActor( FLD_DEMO_LEGENDPOKE* p_obj );
static void FldDemo_LefendPokeObjScaleSet( BLACT_WORK_PTR act, fx32 scale );

static void FldDemo_LegendEffObjAlloc( FLD_DEMO_LEGEND3D_EFF* p_eff, u32 heapID, NNSFndAllocator* p_allocator );
static void FldDemo_LegendEffObjInit( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 x, fx32 y, fx32 z );
static void FldDemo_LegendEffObjDelete( FLD_DEMO_LEGEND3D_EFF* p_eff, NNSFndAllocator* p_allocator );
static u32 FldDemo_LegendEffObjMain( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjDraw( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjEndReq( FLD_DEMO_LEGEND3D_EFF* p_eff );
static void FldDemo_LegendEffObjMoveY( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 y );

static void FldDemo_LegendEffObjSndMain( FLD_DEMO_LEGEND3D_EFF* p_eff );

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ワーク作成
 *
 *	@param	heapID		ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_LEGENDPOKE_APP* FLD_DEMO_LegendPokeApp_Alloc( u32 heapID, FIELDSYS_WORK * fsys )
{
	FLD_DEMO_LEGENDPOKE_APP* p_data;
	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_LEGENDPOKE_APP) );
	memset( p_data, 0, sizeof(FLD_DEMO_LEGENDPOKE_APP) );
	p_data->fsys = fsys;
	p_data->seq = FLD_DEMO_LEGENDPOKE_APP_STARTWAIT;
	p_data->heapID = heapID;

	// アロケーター作成
	sys_InitAllocator( &p_data->allocator, heapID, 32 );

	// ｴﾌｪｸﾄグラフィックファイル初期化
	FldDemo_LegendEffObjAlloc( &p_data->legend_eff, p_data->heapID, &p_data->allocator );
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Free( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	// ｴﾌｪｸﾄ破棄
	FldDemo_LegendEffObjDelete( &p_data->legend_eff, &p_data->allocator );
	
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	デモ開始
 *
 *	@param	p_data			ワーク
 *	@param	legendpoke_id	伝説ポケモンフィールドオブジェ管理ID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Start( FLD_DEMO_LEGENDPOKE_APP* p_data, u32 legendpoke_id )
{
	VecFx32 mat;
	
	// 伝説ポケモンワーク作成
	FldDemo_LegendPokeObjInit( &p_data->legend_poke, p_data->fsys, legendpoke_id );

	// ポケモンの座標取得
	FieldOBJ_VecPosGet( p_data->legend_poke.p_fldobj, &mat );


	// ポケモンの足元からポケモンの中心へ表示Y位置を変更
	mat.y += FLD_DEMO_LEGENDEFF_MOVE_Y_OFS;
	mat.z += FLD_DEMO_LEGENDEFF_MOVE_Z_OFS;
	

	// ｴﾌｪｸﾄのワーク作成
	FldDemo_LegendEffObjInit( &p_data->legend_eff, mat.x, mat.y, mat.z );

	// 開始
	p_data->seq  = FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	フィールドオブジェクト終了チェック
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_LegendPokeApp_EndCheck( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	if( (p_data->seq == FLD_DEMO_LEGENDPOKE_APP_STARTWAIT) ||
		(p_data->seq == FLD_DEMO_LEGENDPOKE_APP_END) ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	メイン処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Main( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	switch( p_data->seq ){
	case FLD_DEMO_LEGENDPOKE_APP_STARTWAIT:
		break;

	case FLD_DEMO_LEGENDPOKE_APP_EFF_MAIN:
		{
			u32 seq;
			seq = FldDemo_LegendEffObjMain( &p_data->legend_eff );
			if( seq == FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT ){
				p_data->seq ++;
			}
		}
		break;

	case FLD_DEMO_LEGENDPOKE_APP_POKE_APP_REQ:
		// ポケモン出現
		FldDemo_LegendPokeObjStart( &p_data->legend_poke );
		// ｴﾌｪｸﾄ終了
		FldDemo_LegendEffObjEndReq( &p_data->legend_eff );

		FldDemo_LegendEffObjMain( &p_data->legend_eff );
		p_data->seq ++;
		break;
		
	case FLD_DEMO_LEGENDPOKE_APP_POKE_APP:
		FldDemo_LegendEffObjMain( &p_data->legend_eff );
		if( FldDemo_LegendPokeObjMain( &p_data->legend_poke ) ){
			p_data->seq ++;
		}
		break;

	case FLD_DEMO_LEGENDPOKE_APP_CLEAR:
		p_data->seq ++;
		break;
		
	case FLD_DEMO_LEGENDPOKE_APP_END:
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	描画処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
void FLD_DEMO_LegendPokeApp_Draw( FLD_DEMO_LEGENDPOKE_APP* p_data )
{
	if( FLD_DEMO_LegendPokeApp_EndCheck( p_data ) == TRUE ){
		return;
	}
	
	FldDemo_LegendEffObjDraw( &p_data->legend_eff );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	伝説ポケモンワークの初期化
 *
 *	@param	p_obj	オブジェクト
 *	@param	fsys	フィールドシステム
 *	@param	obj_id	オブジェクトID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjInit( FLD_DEMO_LEGENDPOKE* p_obj, FIELDSYS_WORK* fsys, u32 obj_id )
{
	// フィールドオブジェクト取得
	p_obj->p_fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, obj_id );
	GF_ASSERT( p_obj->p_fldobj );
	
	p_obj->count = 0;
	p_obj->seq = FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	アニメ処理開始
 *
 *	@param	p_obj	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendPokeObjStart( FLD_DEMO_LEGENDPOKE* p_obj )
{
	BLACT_WORK_PTR p_act;
	VecFx32 ofs;

	// アクターワーク取得
	p_act = FldDemo_LegendPokeObjFldobjGetActor( p_obj );
	
	// 動作開始
	p_obj->seq = FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP;

	// フィールドオブジェ動作開始
	FieldOBJ_StatusBitSet_Vanish( p_obj->p_fldobj, FALSE );

	// アクターの拡縮値設定
	FldDemo_LefendPokeObjScaleSet( p_act, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S );

	// 拡縮
	FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_S, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E, FLD_DEMO_LEGEND_POKE_OBJ_COUNT );

	// 移動
	FLD_DEMO_MoveInit_FX( &p_obj->move, FLD_DEMO_LEGEND_POKE_OBJ_MOVE_Y, 0, FLD_DEMO_LEGEND_POKE_OBJ_MOVE_COUNT );

	// 座標を変更
	// Yオフセット設定
	ofs.x = 0;
	ofs.y = p_obj->move.data;
	ofs.z = 0;
	FieldOBJ_VecDrawOffsOutSideSet( p_obj->p_fldobj, &ofs );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	伝説ポケモンメイン処理
 *
 *	@param	p_obj	オブジェクト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	動作中
 */
//-----------------------------------------------------------------------------
static BOOL FldDemo_LegendPokeObjMain( FLD_DEMO_LEGENDPOKE* p_obj )
{
	BLACT_WORK_PTR p_act;	// アクターワーク
	BOOL result;
	VecFx32 ofs;

	// アクターワーク取得
	p_act = FldDemo_LegendPokeObjFldobjGetActor( p_obj );

	switch( p_obj->seq ){
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_STARTWAIT:
		break;
		
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_UP:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
		FldDemo_LefendPokeObjScaleSet( p_act, p_obj->scale.data );
		if( result == TRUE ){
			// 拡縮
			FLD_DEMO_MoveInit_FX( &p_obj->scale, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_E, FLD_DEMO_LEGEND_POKE_OBJ_SCALE_EDOWN, FLD_DEMO_LEGEND_POKE_OBJ_COUNTDOWN );
			p_obj->count = 0;
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_SCALE_DOWN:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
		FldDemo_LefendPokeObjScaleSet( p_act, p_obj->scale.data );
		if( result == TRUE ){
			p_obj->count = 0;
			p_obj->seq++;
		}
		break;

	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_MOVE:
		p_obj->count++;
		result = FLD_DEMO_MoveMain_FX( &p_obj->move, p_obj->count );
		// Yオフセット設定
		ofs.x = 0;
		ofs.y = p_obj->move.data;
		ofs.z = 0;
		FieldOBJ_VecDrawOffsOutSideSet( p_obj->p_fldobj, &ofs );
		if( result == TRUE ){
			p_obj->seq++;
		}
		break;
		
	case FLD_DEMO_LEGENDPOKEOBJ_SEQ_END:
		return TRUE;
	
	default:
		break;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	伝説ぽけもんワークからビルボードアクター取得
 *
 *	@param	p_obj	ワーク
 *
 *	@return	ビルボードアクター
 */
//-----------------------------------------------------------------------------
static BLACT_WORK_PTR FldDemo_LegendPokeObjFldobjGetActor( FLD_DEMO_LEGENDPOKE* p_obj )
{
	LEGENDPOKE_WORK* p_legend_w;

	p_legend_w = FieldOBJ_DrawLegend_GetWrokPtr( p_obj->p_fldobj );
	return FieldOBJ_DrawLegend_GetBlactPtr( p_legend_w );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	拡縮値設定
 *
 *	@param	act		ビルボードアクター
 *	@param	scale	拡縮値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LefendPokeObjScaleSet( BLACT_WORK_PTR act, fx32 scale )
{
	VecFx32	scale_vec;
	scale_vec.x = scale;
	scale_vec.y = FX32_ONE;
	scale_vec.z = FX32_ONE;
	BLACT_ScaleSet( act, &scale_vec );
}


//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ｴﾌｪｸﾄオブジェ　描画初期化
 *
 *	@param	p_eff		ｴﾌｪｸﾄワーク
 *	@param	heapID		ヒープID
 *	@param	p_allocator	アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjAlloc( FLD_DEMO_LEGEND3D_EFF* p_eff, u32 heapID, NNSFndAllocator* p_allocator )
{
	int i;
	
	// モデル読み込み
	FLD_DEMO_3DObjMdlLoad( &p_eff->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_kurotama_nsbmd, heapID );	

	// アニメ読み込み
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_eff->anm[i],
				&p_eff->mdl, ARC_FIELD_DEMO_CLI_GRA,
				NARC_demo_climax_kurotama_nsbca + i, 
				heapID, p_allocator );
	}

	// 描画オブジェクト作成
	FLD_DEMO_3DObjDrawInit( &p_eff->draw, &p_eff->mdl );
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_eff->draw, &p_eff->anm[i] );
	}

	// 表示OFF
	FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, FALSE );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ｴﾌｪｸﾄオブジェクト初期化
 *
 *	@param	p_eff			ｴﾌｪｸﾄオブジェクト
 *	@param	x				x座標
 *	@param	y				y座標
 *	@param	z				z座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjInit( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 x, fx32 y, fx32 z )
{
	int i;

	// 動作設定
	FLD_DEMO_3DObjDrawSetMatrix( &p_eff->draw, x, y, z );

	FLD_DEMO_3DObjDrawSetScale( &p_eff->draw, FX32_ONE, FX32_ONE, FX32_ONE );

	// フレーム数設定
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmSet( &p_eff->anm[i], 0 );
	}
	p_eff->count = 0;
	p_eff->seq = 0;
	
	p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_00_WAIT;
	p_eff->snd_seq = 0;

#ifdef FIELD_DEMO_DEBUG
	p_eff->debug_count = 0;
#endif

	// 表示ON
	FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, TRUE );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ｴﾌｪｸﾄオブジェクト破棄
 *
 *	@param	p_eff			ｴﾌｪｸﾄオブジェクト
 *	@param	p_allocator		アロケータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjDelete( FLD_DEMO_LEGEND3D_EFF* p_eff, NNSFndAllocator* p_allocator )
{
	int i;
	// モデル破棄
	FLD_DEMO_3DObjMdlDelete( &p_eff->mdl );

	// アニメ破棄
	for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_eff->anm[ i ], p_allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *		【イア・エア登場】
 *	@brief	ｴﾌｪｸﾄオブジェクトメイン関数
 *
 *	@param	p_eff	ｴﾌｪｸﾄオブジェクト
 *
 * @retval	シーケンス
 */
//-----------------------------------------------------------------------------
static u32 FldDemo_LegendEffObjMain( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	BOOL result;
	int i;

#ifdef FIELD_DEMO_DEBUG
	p_eff->debug_count ++;

	if( sys.trg & PAD_BUTTON_L ){
		OS_Printf( "p_eff->debug_count %d\n", p_eff->debug_count );
	}
#endif
	
	switch( p_eff->seq ){
	case FLD_DEMO_LEGENDEFF_SEQ_ANM:		// アニメ
		// ループなしアニメ
		for( i=0; i<FLD_DEMO_LEGENDEFF_ANMOBJ_NUM; i++ ){
			result = FLD_DEMO_3DObjAnmNoLoop( &p_eff->anm[i] );
		}
		
		if( result == TRUE ){
			p_eff->seq ++;
		}
		break;

	case FLD_DEMO_LEGENDEFF_SEQ_FEDEOUT_WAIT:
		break;

	case FLD_DEMO_LEGENDEFF_SEQ_FADEOUT:	// フェードアウト
		p_eff->count  ++;
		result = FLD_DEMO_MoveMain_FX( &p_eff->scale, p_eff->count );
		FLD_DEMO_3DObjDrawSetScale( &p_eff->draw, p_eff->scale.data, p_eff->scale.data, p_eff->scale.data );
		if( result == TRUE ){
			p_eff->seq++;
			// 表示OFF
			FLD_DEMO_3DObjDrawSetDraw( &p_eff->draw, FALSE );
		}
		break;
		
	case FLD_DEMO_LEGENDEFF_SEQ_END:
		break;

	defautl:
		break;
	}

	// 音メイン
	FldDemo_LegendEffObjSndMain( p_eff );

	return p_eff->seq;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y座標設定関数
 *
 *	@param	p_eff	ワーク
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjMoveY( FLD_DEMO_LEGEND3D_EFF* p_eff, fx32 y )
{
	VecFx32 matrix;

	// 座標取得
	FLD_DEMO_3DObjDrawGetMatrix( &p_eff->draw, &matrix.x,  &matrix.y, &matrix.z );
	// 設定
	matrix.y = y;
	FLD_DEMO_3DObjDrawSetMatrix( &p_eff->draw, matrix.x, matrix.y, matrix.z );
}

//----------------------------------------------------------------------------
/**
 *	@brief	おと鳴らしメイン
 *
 *	@param	p_eff ワーク
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjSndMain( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	switch( p_eff->snd_seq ){
	case 0:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_00 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_01_WAIT;
			p_eff->snd_seq = 1;
		}
		break;
	
	case 1:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_01 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_04_WAIT;
			p_eff->snd_seq = 2;
		}
		break;

	case 2:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_04 );
			p_eff->snd_count = FLD_DEMO_LEGENDDEFF_SND_05_WAIT;
			p_eff->snd_seq = 3;
		}
		break;

	case 3:
		p_eff->snd_count --;
		if( p_eff->snd_count < 0 ){
			Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_05 );
			p_eff->snd_seq = 4;
		}
		break;

	case 4:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｴﾌｪｸﾄ終了リクエスト
 *
 *	@param	p_eff	ｴﾌｪｸﾄオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjEndReq( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	p_eff->seq = FLD_DEMO_LEGENDEFF_SEQ_FADEOUT;
	p_eff->count = 0;

	// 拡縮設定
	FLD_DEMO_MoveInit_FX( &p_eff->scale, FX32_ONE, 0, FLD_DEMO_LEGENDEFF_MOVE_SYNC_OUT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｴﾌｪｸﾄオブジェクト描画
 *
 *	@param	p_eff ｴﾌｪｸﾄワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldDemo_LegendEffObjDraw( FLD_DEMO_LEGEND3D_EFF* p_eff )
{
	FLD_DEMO_3DObjDrawDraw( &p_eff->draw );
}


//-----------------------------------------------------------------------------
/**
 *
 *		【イア・エアを中心からわっか出現】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define FLD_DEMO_BLACK_RING_NUM	( 3 )
//-------------------------------------
//	状態
//=====================================
enum{
	FLD_DEMO_BLACKRING_STANDBY,
	FLD_DEMO_BLACKRING_DO,

	// リングオブジェクト
	FLD_DEMO_BLACKRINGOBJ_STANDBY = 0,
	FLD_DEMO_BLACKRINGOBJ_DO,
};

// グラフィックNO
#define FLD_DEMO_BLACK_RING_IMD	( NARC_demo_climax_ring_t_nsbmd )
//int FLD_DEMO_BLACK_RING_IMD	= NARC_demo_climax_ring_h_nsbmd;

// 黒帯描画開始タイミング
#define FLD_DEMO_BLACK_RING_START_TIMING	( 64 )

// 1黒帯オブジェクト
#define FLD_DEMO_BLACKRING_OBJ_SSCALE	(0)
#define FLD_DEMO_BLACKRING_OBJ_ESCALE	( FX32_CONST(16) )
#define FLD_DEMO_BLACKRING_OBJ_SYNC		(96)
#define FLD_DEMO_BLACKRING_OBJ_OFS_X	(GRID_HALF_FX32)
#define FLD_DEMO_BLACKRING_OBJ_GRID_Y	(10)
#define FLD_DEMO_BLACKRING_OBJ_GRID_Z	(1)
//int FLD_DEMO_BLACKRING_OBJ_GRID_Y	= 2;
//int FLD_DEMO_BLACKRING_OBJ_GRID_Z	= 1;

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	わっかオブジェクト
//=====================================
typedef struct {
	u32 status;					// ステータス
	FLD_3DOBJ draw;	// 描画ワーク
	FLD_DEMO_MOVE_PARAM_FX scale;	// 拡縮パラメータ
	int count;
} FLD_DEMO_BLACK_RING_OBJ;


//-------------------------------------
//	イア・エアを中心にわっか出現　ワーク
//=====================================
typedef struct _FLD_DEMO_BLACK_RING{
	FLD_3DOBJ_MDL mdl;			// モデル
	FLD_DEMO_BLACK_RING_OBJ blackring[ FLD_DEMO_BLACK_RING_NUM ];
	u32 status;					// ステータス
	s32 start_count;
	s32 start_count_max;
	fx32 x;
	fx32 y;
	fx32 z;
	u16 rota_x;
	u16 rota_y;
	u16 rota_z;
};


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc_Core( u32 heapID, u32 dataIdx );
static void FLD_DEMO_BlackRing_Free_Core( FLD_DEMO_BLACK_RING* p_data );
static void FLD_DEMO_BlackRing_Start_Core( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z, s32 start_count, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_BlackRing_Main_Core( FLD_DEMO_BLACK_RING* p_data );
static void FLD_DEMO_BlackRing_Draw_Core( FLD_DEMO_BLACK_RING* p_data );

static void FLD_DEMO_BlackRingObj_Init( FLD_DEMO_BLACK_RING_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl );
static void FLD_DEMO_BlackRingObj_Delete( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static void FLD_DEMO_BlackRingObj_Start( FLD_DEMO_BLACK_RING_OBJ* p_obj, fx32 s_scale, fx32 e_scale, int sync, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_BlackRingObj_Main( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static void FLD_DEMO_BlackRingObj_Draw( FLD_DEMO_BLACK_RING_OBJ* p_obj );
static FLD_DEMO_BLACK_RING_OBJ* FLD_DEMO_BlackRingCleanObjGet( FLD_DEMO_BLACK_RING* p_data );


//----------------------------------------------------------------------------
/**
 *		【黒リング】
 *	@brief	ワーク確保Core
 *
 *	@param	heapID		ヒープ
 *	@param	dataIdx		データIDX
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc_Core( u32 heapID, u32 dataIdx )
{
	FLD_DEMO_BLACK_RING* p_data;
	int i;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_BLACK_RING) );
	memset( p_data, 0, sizeof(FLD_DEMO_BLACK_RING) );
	
	// モデル読み込み
	FLD_DEMO_3DObjMdlLoad( &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, dataIdx, heapID );

	// 描画初期化
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Init( &p_data->blackring[i], &p_data->mdl );
	}
	p_data->status = FLD_DEMO_BLACKRING_STANDBY;

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【黒リング】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Free_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;

	// 描画初期化
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Delete( &p_data->blackring[i] );
	}
	
	// モデルデータ破棄
	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【黒リング】
 *	@brief　ｴﾌｪｸﾄ開始
 *
 *	@param	p_data	ワーク
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	z		ｚ座標
 *	@param	start_count	開始カウント値
 *	@param	rota_x	y軸回転角
 *	@param	rota_y	y軸回転角
 *	@param	rota_z	z軸回転角
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Start_Core( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z, s32 start_count, u16 rota_x, u16 rota_y, u16 rota_z )
{
	GF_ASSERT( p_data->status == FLD_DEMO_BLACKRING_STANDBY );

	p_data->start_count = 0;
	p_data->x = x;
	p_data->y = y;
	p_data->z = z;
	p_data->rota_x = rota_x;
	p_data->rota_y = rota_y;
	p_data->rota_z = rota_z;
	p_data->start_count_max = start_count;
	p_data->status = FLD_DEMO_BLACKRING_DO;
}

//----------------------------------------------------------------------------
/**
 *		【黒リング】
 *	@brief	ｴﾌｪｸﾄメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Main_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;
	FLD_DEMO_BLACK_RING_OBJ* p_obj;
	
	// 発射管理部
	p_data->start_count --;
	if( p_data->start_count < 0 ){
		p_data->start_count = p_data->start_count_max;
	
		p_obj = FLD_DEMO_BlackRingCleanObjGet( p_data );
		GF_ASSERT( p_obj );	// 空きオブジェなし

		// オブジェ動作開始
		FLD_DEMO_BlackRingObj_Start( p_obj, 
				FLD_DEMO_BLACKRING_OBJ_SSCALE,
				FLD_DEMO_BLACKRING_OBJ_ESCALE,
				FLD_DEMO_BLACKRING_OBJ_SYNC,
				p_data->x, 
				p_data->y, 
				p_data->z,
				p_data->rota_x,
				p_data->rota_y,
				p_data->rota_z
				);
	}

	// オブジェクト動作部
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Main( &p_data->blackring[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *		【黒リング】
 *	@brief	ｴﾌｪｸﾄ描画
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRing_Draw_Core( FLD_DEMO_BLACK_RING* p_data )
{
	int i;
	// オブジェクト描画部
	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		FLD_DEMO_BlackRingObj_Draw( &p_data->blackring[ i ] );
	}
}







//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	ワーク確保
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc( u32 heapID )
{
	return FLD_DEMO_BlackRing_Alloc_Core( heapID, FLD_DEMO_BLACK_RING_IMD );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Free( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Free_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	デモスタート
 *
 *	@param	p_data	ワーク
 *	@param	grid_x	イアエア位置グリッドｘ
 *	@param	grid_y	イアエア位置グリッドｙ
 *	@param	grid_z	イアエア位置グリッドｚ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Start( FLD_DEMO_BLACK_RING* p_data, u16 grid_x, u16 grid_y, u16 grid_z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			GRID_SIZE_FX32( grid_x ) + FLD_DEMO_BLACKRING_OBJ_OFS_X,
			GRID_SIZE_FX32( grid_y ) + GRID_SIZE_FX32( FLD_DEMO_BLACKRING_OBJ_GRID_Y ),
			GRID_SIZE_FX32( grid_z ) + GRID_SIZE_FX32( FLD_DEMO_BLACKRING_OBJ_GRID_Z ),
			FLD_DEMO_BLACK_RING_START_TIMING, 0, 0, 0 );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	デモメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Main( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Main_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	描画
 *
 *	@param	p_data	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_Draw( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Draw_Core( p_data );
}



//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	リングオブジェクト初期化
 *
 *	@param	p_obj		ワーク
 *	@param	p_mdl		モデル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Init( FLD_DEMO_BLACK_RING_OBJ* p_obj, FLD_3DOBJ_MDL* p_mdl )
{
	memset( p_obj, 0, sizeof(FLD_DEMO_BLACK_RING_OBJ) );
	
	// オブジェクト初期化
	FLD_DEMO_3DObjDrawInit( &p_obj->draw, p_mdl );
	FLD_DEMO_3DObjDrawSetDraw( &p_obj->draw, FALSE );	// 表示OFF
	p_obj->status = FLD_DEMO_BLACKRINGOBJ_STANDBY;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	リングオブジェクト破棄
 *
 *	@param	p_obj	オブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Delete( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	memset( p_obj, 0, sizeof(FLD_DEMO_BLACK_RING_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	リングオブジェクト　動作開始
 *
 *	@param	p_obj		オブジェクト
 *	@param	s_scale		拡縮開始値
 *	@param	e_scale		拡縮終了値
 *	@param	sync		シンク数
 *	@param	x			ｘ座標
 *	@param  y			ｙ座標
 *	@param	z			ｚ座標
 *	@param	rota_x		ｘ軸回転角
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Start( FLD_DEMO_BLACK_RING_OBJ* p_obj, fx32 s_scale, fx32 e_scale, int sync, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z )
{
	// 多重呼び出しチェック
	GF_ASSERT( p_obj->status == FLD_DEMO_BLACKRINGOBJ_STANDBY );

	// 動作初期化
	FLD_DEMO_MoveInit_FX( &p_obj->scale, s_scale, e_scale, sync );

	// 描画初期化
	FLD_DEMO_3DObjDrawSetDraw( &p_obj->draw, TRUE );
	FLD_DEMO_3DObjDrawSetMatrix( &p_obj->draw, x, y, z );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, s_scale, FX32_ONE, s_scale );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_x, FLD_3DROTA_WAY_X );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_y, FLD_3DROTA_WAY_Y );
	FLD_DEMO_3DObjDrawSetRota( &p_obj->draw, rota_z, FLD_3DROTA_WAY_Z );

	p_obj->status = FLD_DEMO_BLACKRINGOBJ_DO;
	p_obj->count = 0;
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	リングオブジェクトメイン処理
 *
 *	@param	p_obj	オブジェクトワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Main( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	BOOL result;

	if( p_obj->status == FLD_DEMO_BLACKRINGOBJ_STANDBY ){
		return ;
	}
	
	// 拡縮値を変更する
	p_obj->count ++;
	result = FLD_DEMO_MoveMain_FX( &p_obj->scale, p_obj->count );
	FLD_DEMO_3DObjDrawSetScale( &p_obj->draw, p_obj->scale.data, FX32_ONE, p_obj->scale.data );

	if( result == TRUE ){
		p_obj->status = FLD_DEMO_BLACKRINGOBJ_STANDBY;
	}
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	リングオブジェクト描画処理
 *
 *	@param	p_obj	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_BlackRingObj_Draw( FLD_DEMO_BLACK_RING_OBJ* p_obj )
{
	FLD_DEMO_3DObjDrawDraw( &p_obj->draw );
}

//----------------------------------------------------------------------------
/**
 *		【イア・エアを中心からわっか出現】
 *	@brief	空いているリングオブジェクト取得
 *
 *	@param	p_data	オブジェクトワーク
 *
 *	@return	空いているオブジェクトワーク
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_BLACK_RING_OBJ* FLD_DEMO_BlackRingCleanObjGet( FLD_DEMO_BLACK_RING* p_data )
{
	int i;

	for( i=0; i<FLD_DEMO_BLACK_RING_NUM; i++ ){
		if( p_data->blackring[i].status == FLD_DEMO_BLACKRINGOBJ_STANDBY ){
			return &p_data->blackring[i];
		}
	}
	return NULL;
}





//-----------------------------------------------------------------------------
/**
 *
 *		【ありの卵を出す】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#ifdef PM_DEBUG
//#define FLD_DEMO_ANT_DEBUG
#endif

#ifdef FLD_DEMO_ANT_DEBUG
int FLD_DEMO_ANTEGG_DEBUG_SEQ = 0;

int FLD_DEMO_ANTEGG_CUT00_ROTA_X =	( 62623 );
int FLD_DEMO_ANTEGG_CUT00_ROTA_Y = 	( 32949 );
int FLD_DEMO_ANTEGG_CUT00_ROTA_Z = 	( 32942 );
int FLD_DEMO_ANTEGG_CUT00_OFS_X	 = 	( 170920 );
int FLD_DEMO_ANTEGG_CUT00_OFS_Y	 = 	( -225940 );
int FLD_DEMO_ANTEGG_CUT00_OFS_Z	 =	( -747638 );
#else



#endif


//-------------------------------------
//	シーン００
//=====================================
#if ( PM_VERSION == VERSION_DIAMOND )

#define FLD_DEMO_ANTEGG_CUT00_ROTA_X	( 62623 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Y	( 32949 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Z	( 32942 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_X		( 170920 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Y		( -225940 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Z		( -747638 )

#elif( PM_VERSION == VERSION_PEARL )

#define FLD_DEMO_ANTEGG_CUT00_ROTA_X	( 58983 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Y	( 30219 )
#define FLD_DEMO_ANTEGG_CUT00_ROTA_Z	( 34216 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_X		( -307200 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Y		( -87729 )
#define FLD_DEMO_ANTEGG_CUT00_OFS_Z		( -629017 )

#endif



#define FLD_DEMO_ANTEGG_CUT01_ROTA_X	( 58801 )
#define FLD_DEMO_ANTEGG_CUT01_ROTA_Y	( 49507 )
#define FLD_DEMO_ANTEGG_CUT01_ROTA_Z	( 32760 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_X		( 1141327 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_Y		( 323947 )
#define FLD_DEMO_ANTEGG_CUT01_OFS_Z		( -598296 )

#define FLD_DEMO_ANTEGG_CUT02_ROTA_X	( 59165 )
#define FLD_DEMO_ANTEGG_CUT02_ROTA_Y	( 21301 )
#define FLD_DEMO_ANTEGG_CUT02_ROTA_Z	( 31122 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_X		( -811008 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_Y		( 356351 )
#define FLD_DEMO_ANTEGG_CUT02_OFS_Z		( -2162696 )



#define FLD_DEMO_ANTEGG_ANM_NUM	(3)	// ３ｄアニメーション数

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ありの卵　ワーク
//=====================================
typedef struct _FLD_DEMO_ANTEGG {
	FLD_3DOBJ draw;		// 描画ワーク
	FLD_3DOBJ_MDL mdl;		// モデル
	FLD_3DOBJ_ANM anm[FLD_DEMO_ANTEGG_ANM_NUM];	// アニメ

	NNSFndAllocator allocator;	// アロケータ
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Alloc( u32 heapID, u32 dataIdx );
static void FLD_DEMO_AntEgg_Free( FLD_DEMO_ANTEGG* p_data );
static void FLD_DEMO_AntEgg_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z );
static void FLD_DEMO_AntEgg_Main( FLD_DEMO_ANTEGG* p_data );
static void FLD_DEMO_AntEgg_Draw( FLD_DEMO_ANTEGG* p_data );



//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	ワーク確保
 *
 *	@param	heapID	ヒープID
 *	@param	dataIdx	データインデックス　アーカイブデータ
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
static FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Alloc( u32 heapID, u32 dataIdx )
{
	FLD_DEMO_ANTEGG* p_data;
	int i;
	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_ANTEGG) );
	memset( p_data, 0, sizeof(FLD_DEMO_ANTEGG) );

	// アロケータ作成
	sys_InitAllocator( &p_data->allocator, heapID, 32 );	

	// モデル読み込み
	FLD_DEMO_3DObjMdlLoad( &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, dataIdx, heapID );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_data->anm[i], &p_data->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_aritama_nsbta + i, heapID, &p_data->allocator );
	}
	FLD_DEMO_3DObjDrawInit( &p_data->draw, &p_data->mdl );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_data->draw, &p_data->anm[i] );
	}
	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, FALSE );

	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Free( FLD_DEMO_ANTEGG* p_data )
{
	int i;

	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_data->anm[i], &p_data->allocator );
	}
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	卵スタート
 *
 *	@param	p_data	ワーク
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	z		ｚ座標
 *	@param	rota_x	回転角ｘ
 *	@param	rota_y	回転角ｙ
 *	@param	rota_z	回転角ｚ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z, u16 rota_x, u16 rota_y, u16 rota_z )
{
	FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, 
			x, 
			y, 
			z );

	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_x, FLD_3DROTA_WAY_X );
	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_z, FLD_3DROTA_WAY_Z );
	FLD_DEMO_3DObjDrawSetRota( &p_data->draw, rota_y, FLD_3DROTA_WAY_Y );
	

	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, TRUE );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	卵動作メイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Main( FLD_DEMO_ANTEGG* p_data )
{
	int i;
	
	// アニメ処理が追加される予定
	for( i=0; i<FLD_DEMO_ANTEGG_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoop( &p_data->anm[i] );
	}
	
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	ありの卵描画
 *
 *	@param	p_data ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FLD_DEMO_AntEgg_Draw( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_3DObjDrawDraw( &p_data->draw );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	ありの卵　ワーク作成
 *
 *	@param	heapID 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Cut_Alloc( u32 heapID )
{
	return FLD_DEMO_AntEgg_Alloc( heapID, NARC_demo_climax_aritama_nsbmd );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	ありの卵　ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Free( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_AntEgg_Free( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	メイン処理
 *
 *	@param	p_data 　ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Main( FLD_DEMO_ANTEGG* p_data )
{
	VecFx32 matrix;

	FLD_DEMO_AntEgg_Main( p_data );

#ifdef FLD_DEMO_ANT_DEBUG
	if( sys.tp_trg ){
		FLD_DEMO_ANTEGG_DEBUG_SEQ = (FLD_DEMO_ANTEGG_DEBUG_SEQ + 1) % 3;
		if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 0 ){
			OS_Printf( "回転\n" );
		}else if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 1 ){
			OS_Printf( "座標\n" );
		}else if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 2 ){
			OS_Printf( "黒Ring\n" );
		}
	}

	switch(FLD_DEMO_ANTEGG_DEBUG_SEQ){
	case 0:	
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Y += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Y %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Y -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Y %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Y );
			}
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_Y, FLD_3DROTA_WAY_Y );
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_Z += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Z %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				FLD_DEMO_ANTEGG_CUT00_ROTA_Z -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_Z %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
			}
			// ｚ軸１８０度回転
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_Z, FLD_3DROTA_WAY_Z );
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				FLD_DEMO_ANTEGG_CUT00_ROTA_X += FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_X %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				FLD_DEMO_ANTEGG_CUT00_ROTA_X -= FX_GET_ROTA_NUM( 1 );
				OS_Printf( "ROTA_X %d\n", FLD_DEMO_ANTEGG_CUT00_ROTA_X );
			}
			FLD_DEMO_3DObjDrawSetRota( &p_data->draw, FLD_DEMO_ANTEGG_CUT00_ROTA_X, FLD_3DROTA_WAY_X );
		}
		break;

	case 1:
		FLD_DEMO_3DObjDrawGetMatrix( &p_data->draw, &matrix.x, &matrix.y, &matrix.z );
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.x += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_X += FX32_CONST( 1 );
				OS_Printf( "MATRIX_X %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.x -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_X -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_X %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_X );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.y += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Y += FX32_CONST( 1 );
				OS_Printf( "MATRIX_Y %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.y -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Y -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_Y %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Y );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				matrix.z += FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Z += FX32_CONST( 1 );
				OS_Printf( "MATRIX_Z %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				matrix.z -= FX32_CONST( 1 );
				FLD_DEMO_ANTEGG_CUT00_OFS_Z -= FX32_CONST( 1 );
				OS_Printf( "MATRIX_Z %d\n", FLD_DEMO_ANTEGG_CUT00_OFS_Z );
			}
			FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, matrix.x, matrix.y, matrix.z );
		}
		break;

	default:
		break;
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す】
 *	@brief	描画処理
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut_Draw( FLD_DEMO_ANTEGG* p_data )
{
	FLD_DEMO_AntEgg_Draw( p_data );
}


//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す　カット００】
 *	@brief	デモ開始
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点座標ｘ
 *	@param	y	カメラ注目点座標ｙ
 *	@param	z	カメラ注目点座標ｚ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut00_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT00_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT00_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT00_OFS_Z,
			FLD_DEMO_ANTEGG_CUT00_ROTA_X,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Z );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す　カット０１】
 *	@brief	デモ開始
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点座標ｘ
 *	@param	y	カメラ注目点座標ｙ
 *	@param	z	カメラ注目点座標ｚ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut01_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT01_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT01_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT01_OFS_Z,
			FLD_DEMO_ANTEGG_CUT01_ROTA_X,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Z );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵を出す　カット０２】
 *	@brief	デモ開始
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点座標ｘ
 *	@param	y	カメラ注目点座標ｙ
 *	@param	z	カメラ注目点座標ｚ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AntEgg_Cut02_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_AntEgg_Start( p_data,
			x + FLD_DEMO_ANTEGG_CUT02_OFS_X,
			y + FLD_DEMO_ANTEGG_CUT02_OFS_Y,
			z + FLD_DEMO_ANTEGG_CUT02_OFS_Z,
			FLD_DEMO_ANTEGG_CUT02_ROTA_X,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Z );
}



//-----------------------------------------------------------------------------
/**
 *
 *		【ありの卵の時の黒リング	コンテ③】
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		定数定義
 */
//-----------------------------------------------------------------------------

#ifdef FLD_DEMO_ANT_DEBUG
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X =	(0xfffc2000);
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y =	(0xfffb1000);
int FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z =	(0xfff30000);
#else


#endif



// カメラ注目点からの距離
#if ( PM_VERSION == VERSION_DIAMOND )

#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X	(0x11000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y	(0xfff91000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z	(0xfff35000)

#elif( PM_VERSION == VERSION_PEARL )

#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X	(0xfffc2000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y	(0xfffb1000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z	(0xfff30000)

#endif

#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_X	(0x252000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Y	(0x43000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Z	(0xfffc8000)

#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_X	(0xffeb4000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Y	(0xffff3000)
#define FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Z	(0xffe3c000)



//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ありの卵の時の黒リング
 *
 *	@param	heapID	ヒープID
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_AntEggCat_Alloc( u32 heapID )
{
	return FLD_DEMO_BlackRing_Alloc_Core( heapID, NARC_demo_climax_ring_t_nsbmd );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Free( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Free_Core( p_data );

}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ｴﾌｪｸﾄメイン
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Main( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Main_Core( p_data );

#ifdef FLD_DEMO_ANT_DEBUG
	if( FLD_DEMO_ANTEGG_DEBUG_SEQ == 2 ){
		if( sys.cont & PAD_BUTTON_R ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->y += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y += FX32_ONE;
				OS_Printf( "MAT_Y %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y );
			}else if( sys.cont & PAD_BUTTON_Y ){
				p_data->y -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y -= FX32_ONE;
				OS_Printf( "MAT_Y %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y );
			}
		}

		if( sys.cont & PAD_BUTTON_L ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->z += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z += FX32_ONE;
				OS_Printf( "MAT_Z %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z );
			}else if( sys.cont & PAD_BUTTON_Y ){

				p_data->z -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z -= FX32_ONE;
				OS_Printf( "MAT_Z %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z );
			}
		}

		if( sys.cont & PAD_BUTTON_START ){
			if( sys.cont & PAD_BUTTON_A ){
				p_data->x += FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X += FX32_ONE;
				OS_Printf( "MAT_X %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X );
			}else if( sys.cont & PAD_BUTTON_Y ){

				p_data->x -= FX32_ONE;
				FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X -= FX32_ONE;
				OS_Printf( "MAT_X %x\n", FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X );
			}
		}
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ｴﾌｪｸﾄ描画
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat_Draw( FLD_DEMO_BLACK_RING* p_data )
{
	FLD_DEMO_BlackRing_Draw_Core( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ｴﾌｪｸﾄ開始	カット00
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点　ｘ座標
 *	@param	y	カメラ注目点　ｙ座標	
 *	@param	z	カメラ注目点　ｚ座標 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat00_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT00_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT00_ROTA_X,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT00_ROTA_Z
			);
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ｴﾌｪｸﾄ開始	カット01
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点　ｘ座標
 *	@param	y	カメラ注目点　ｙ座標	
 *	@param	z	カメラ注目点　ｚ座標 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat01_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT01_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT01_ROTA_X,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT01_ROTA_Z
			);
}

//----------------------------------------------------------------------------
/**
 *		【ありの卵の時の黒リング	コンテ③】
 *	@brief	ｴﾌｪｸﾄ開始	カット02
 *
 *	@param	p_data	ワーク
 *	@param	x	カメラ注目点　ｘ座標
 *	@param	y	カメラ注目点　ｙ座標	
 *	@param	z	カメラ注目点　ｚ座標 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_BlackRing_AntEggCat02_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z )
{
	FLD_DEMO_BlackRing_Start_Core( p_data, 
			x + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_X,
			y + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Y,
			z + FLD_DEMO_BLACKRING_ANTEGGCUT02_OBJ_OFS_Z,
			FLD_DEMO_BLACK_RING_START_TIMING,
			FLD_DEMO_ANTEGG_CUT02_ROTA_X,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Y,
			FLD_DEMO_ANTEGG_CUT02_ROTA_Z
			);
}


//-----------------------------------------------------------------------------
/**
 * 
 *		フィールド全体を暗くする
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		定数定義
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		構造体定義
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	明度の低いLIGHTをフィールド全体にかける
//=====================================
typedef struct _FLD_DEMO_DARKLIGHT{
	FIELDSYS_WORK* p_fsys;	// フィールドシステム
	const LIGHT_CONT_DATA* p_lightdata;		// LIGHTデータ
	u32 light_num;			// LIGHTデータ数
	u32 light_count;		// LIGHTｶｳﾝﾀ
	u32 light_set;			// 今設定中のLIGHTデータ
	u32 status;				// 動作状態
};

//-----------------------------------------------------------------------------
/**
 *		プロトタイプ宣言
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		グローバル変数
 */
//-----------------------------------------------------------------------------
#define FLD_DEMO_DARKLIGHT_LIGHTDATANUM	( 3 )
static const LIGHT_CONT_DATA FLD_DEMO_DARKLIGHT_LIGHTDATA[ FLD_DEMO_DARKLIGHT_LIGHTDATANUM ] = {
	{
		8,				// LIGHT終了ｶｳﾝﾀ値
		0xD,			// LIGHT反映フラグ
		{				// LIGHTカラー
			GX_RGB(13, 11, 11),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHTベクトル
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(13, 13, 14),// ディフューズ
		GX_RGB(13, 12, 12),// アンビエント
		GX_RGB(13, 11, 14),// スペキュラー
		GX_RGB(11, 9, 10) // 放射
	},
	{
		16,				// LIGHT終了ｶｳﾝﾀ値
		0xD,			// LIGHT反映フラグ
		{				// LIGHTカラー
			GX_RGB(11, 9, 9),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHTベクトル
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(11, 11, 12),// ディフューズ
		GX_RGB(13, 12, 12),// アンビエント
		GX_RGB(13, 11, 14),// スペキュラー
		GX_RGB(11, 9, 10) // 放射
	},
	{
		24,				// LIGHT終了ｶｳﾝﾀ値
		0xD,			// LIGHT反映フラグ
		{				// LIGHTカラー
			GX_RGB(9, 8, 8),
			GX_RGB(0, 0, 0),
			GX_RGB(10, 3, 0),
			GX_RGB(31, 31, 31),
		},	
		{				// LIGHTベクトル
			{-2022,-3561,93},
			{0,0,4096},	
			{0,0,4096},
			{0,0,4096},
		},
		GX_RGB(10, 9, 9),// ディフューズ
		GX_RGB(11, 10, 10),// アンビエント
		GX_RGB(13, 11, 14),// スペキュラー
		GX_RGB(11, 9, 10) // 放射
	},
};

//----------------------------------------------------------------------------
/**
 *		【フィールド全体を暗くする】
 *	@brief	ワーク確保
 *
 *	@param	heapID	ヒープID
 *	@param	p_fsys	フィールドシステム 
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_DARKLIGHT* FLD_DEMO_DarkLight_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys )
{
	FLD_DEMO_DARKLIGHT* p_data;

	p_data = sys_AllocMemory( heapID, sizeof(FLD_DEMO_DARKLIGHT) );
	memset( p_data, 0, sizeof(FLD_DEMO_DARKLIGHT) );
	p_data->p_fsys = p_fsys;
	p_data->status = FLD_DEMO_DARKLIGHT_INIT;
	
	return p_data;
}

//----------------------------------------------------------------------------
/**
 *		【フィールド全体を暗くする】
 *	@brief	ワーク破棄
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Free( FLD_DEMO_DARKLIGHT* p_data )
{
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *		【フィールド全体を暗くする】
 *	@brief	デモ開始
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Start( FLD_DEMO_DARKLIGHT* p_data )
{
	p_data->p_lightdata = FLD_DEMO_DARKLIGHT_LIGHTDATA;
	p_data->light_num = FLD_DEMO_DARKLIGHT_LIGHTDATANUM;
	p_data->light_count = 0;
	p_data->light_set = 0;
	p_data->status = FLD_DEMO_DARKLIGHT_FADEOUT;

	// LIGHT反映中止
	SetLightContReflect( p_data->p_fsys->light_cont_data, FALSE );
}

//----------------------------------------------------------------------------
/**
 *		【フィールド全体を暗くする】
 *	@brief	メイン関数
 *
 *	@param	p_data ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_Main( FLD_DEMO_DARKLIGHT* p_data )
{
	switch( p_data->status ){
	case FLD_DEMO_DARKLIGHT_FADEOUT:	// 暗くなっています。
		p_data->light_count ++;
		if( p_data->p_lightdata[ p_data->light_set ].lightEnd <= p_data->light_count ){
			if( (p_data->light_set + 1) >= p_data->light_num ){
				p_data->status++;
			}else{
				p_data->light_set ++;
				DataSetLightCont( &p_data->p_lightdata[ p_data->light_set ], p_data->p_fsys->glst_data );
			}
		}
		break;
		
	case FLD_DEMO_DARKLIGHT_ENDWAIT:	// 終了リクエスト待ち。
		break;
		
	case FLD_DEMO_DARKLIGHT_FADEIN:	// 明るくなっています。
		p_data->light_count --;
		
		if( p_data->light_set > 0 ){
			if( p_data->p_lightdata[ p_data->light_set - 1 ].lightEnd > p_data->light_count ){
				p_data->light_set --;
				DataSetLightCont( &p_data->p_lightdata[ p_data->light_set ], p_data->p_fsys->glst_data );
			}
		}else{
			if( 0 >= p_data->light_count ){

				// LIGHT復帰
				SetLightContReflect( p_data->p_fsys->light_cont_data, TRUE );
				p_data->status++;
			}
		}
		break;
		
	case FLD_DEMO_DARKLIGHT_END:		// 全工程終了
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *		【フィールド全体を暗くする】
 *	@brief	現在状態取得
 *
 *	@param	cp_data	ワーク
 *	
 *	@retval	FLD_DEMO_DARKLIGHT_INIT,	// 初期化
 *	@retval	FLD_DEMO_DARKLIGHT_FADEOUT,	// 暗くなっています。
 * 	@retval	FLD_DEMO_DARKLIGHT_ENDWAIT,	// 終了リクエスト待ち。
 * 	@retval	FLD_DEMO_DARKLIGHT_FADEIN,	// 明るくなっています。
 *	@retval	FLD_DEMO_DARKLIGHT_END,		// 全工程終了
 */
//-----------------------------------------------------------------------------
u32 FLD_DEMO_DarkLight_GetState( const FLD_DEMO_DARKLIGHT* cp_data )
{
	return cp_data->status;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了リクエスト
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_DarkLight_EndReq( FLD_DEMO_DARKLIGHT* p_data )
{
	GF_ASSERT_MSG( p_data->status == FLD_DEMO_DARKLIGHT_ENDWAIT, "status %d", p_data->status );
	p_data->status = FLD_DEMO_DARKLIGHT_FADEIN;
}



//-----------------------------------------------------------------------------
/**
 *
 *
 *		アリのタマゴ放出開始デモ
 *
 */
//-----------------------------------------------------------------------------
enum{
	FLD_DEMO_ARITAMA_ANM_CA,
	FLD_DEMO_ARITAMA_ANM_MA,
	FLD_DEMO_ARITAMA_ANM_TA,
	FLD_DEMO_ARITAMA_ANM_VA,
	FLD_DEMO_ARITAMA_ANM_NUM
};
//-------------------------------------
//	アリの卵放出開始デモ
//=====================================
typedef struct _FLD_DEMO_ARITAMA_START{
	FLD_3DOBJ draw;		// 描画ワーク
	FLD_3DOBJ_MDL mdl;		// モデル
	FLD_3DOBJ_ANM anm[FLD_DEMO_ARITAMA_ANM_NUM];	// アニメ
	FIELDSYS_WORK* p_fsys;	// フィールドシステム
	NNSFndAllocator allocator;	// アロケータ
};



//----------------------------------------------------------------------------
/**
 *	@brief	アリの卵開始　メモリ確保
 *
 *	@param	heapID		ヒープID
 *	@param	p_fsys		フィールドシステム
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FLD_DEMO_ARITAMA_START* FLD_DEMO_AriTamaStart_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys )
{
	FLD_DEMO_ARITAMA_START * p_work;
	int i;
	p_work = sys_AllocMemory( heapID, sizeof(FLD_DEMO_ARITAMA_START) );
	memset( p_work, 0, sizeof(FLD_DEMO_ARITAMA_START) );

	// fieldsys
	p_work->p_fsys = p_fsys;

	// アロケータ作成
	sys_InitAllocator( &p_work->allocator, heapID, 32 );	

	// モデル読み込み
	FLD_DEMO_3DObjMdlLoad( &p_work->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ari_start_nsbmd, heapID );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmLoad( &p_work->anm[i], &p_work->mdl, ARC_FIELD_DEMO_CLI_GRA, NARC_demo_climax_ari_start_nsbca + i, heapID, &p_work->allocator );
	}
	FLD_DEMO_3DObjDrawInit( &p_work->draw, &p_work->mdl );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjDrawAddAnm( &p_work->draw, &p_work->anm[i] );
	}
	FLD_DEMO_3DObjDrawSetDraw( &p_work->draw, FALSE );

	return p_work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アリの卵開始　ワーク破棄
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Free( FLD_DEMO_ARITAMA_START* p_data )
{
	int i;

	FLD_DEMO_3DObjMdlDelete( &p_data->mdl );
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		FLD_DEMO_3DObjAnmDelete( &p_data->anm[i], &p_data->allocator );
	}
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アリの卵放出	開始
 *
 *	@param	p_data			ワーク
 *	@param	legendpoke_id	伝説ポケモンOBJID
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Start( FLD_DEMO_ARITAMA_START* p_data, u32 legendpoke_id )
{
	VecFx32 mat;
	FIELD_OBJ_PTR fldobj;
	fldobj = FieldOBJSys_OBJIDSearch( p_data->p_fsys->fldobjsys, legendpoke_id );
	

	// ポケモンの座標取得
	FieldOBJ_VecPosGet( fldobj, &mat );
	
	FLD_DEMO_3DObjDrawSetMatrix( &p_data->draw, 
			mat.x,
			mat.y,
			mat.z );

	FLD_DEMO_3DObjDrawSetDraw( &p_data->draw, TRUE );
	// プシュー
	Snd_SePlay( FLD_DEMO_LEGENDEFF_SND_06 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アリの卵放出アニメ　メイン
 *
 *	@param	p_data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FLD_DEMO_AriTamaStart_Main( FLD_DEMO_ARITAMA_START* p_data )
{
	int i;
	BOOL retval;
	
	// アニメ処理が追加される予定
	for( i=0; i<FLD_DEMO_ARITAMA_ANM_NUM; i++ ){
		retval = FLD_DEMO_3DObjAnmNoLoop( &p_data->anm[i] );
	}
	return retval;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
void FLD_DEMO_AriTamaStart_Draw( FLD_DEMO_ARITAMA_START* p_data )
{
	FLD_DEMO_3DObjDrawDraw( &p_data->draw );
}



#ifdef FIELD_DEMO_DEBUG
static void FieldDemoDebugStart( void )
{
	pFieldDemoDebugTcb = TCB_Add( FieldDemoDebugTcb, NULL, 0 );
}

static void FieldDemoDebugEnd( void )
{
	TCB_Delete( pFieldDemoDebugTcb );
}

static void FieldDemoDebugTcb( TCB_PTR tcb, void* p_work )
{
	// 動さ停止
	if( sys.tp_trg ){
		FIELD_DEMO_DEBUG_STOP ^= 1;

		OS_Printf( "停止:1 再生:0 %d\n", FIELD_DEMO_DEBUG_STOP );
	}

	// 値変更
	if( sys.cont & PAD_BUTTON_L ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
	if( sys.cont & PAD_BUTTON_R ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
	if( sys.cont & PAD_BUTTON_START ){
		if( sys.repeat & PAD_BUTTON_A ){
//			OS_Printf( "%d\n", );
		}
		if( sys.repeat & PAD_BUTTON_Y ){
//			OS_Printf( "%d\n", );
		}
	}
}
#endif // FIELD_DEMO_DEBUG
