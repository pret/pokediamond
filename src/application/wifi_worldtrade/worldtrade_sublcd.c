//============================================================================================
/**
 * @file	worldtrade_sublcd.c
 * @bfief	世界交換サブ画面処理
 * @author	Akito Mori
 * @date	06.04.16
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "gflib/touchpanel.h"
#include "gflib/tcb.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "system/bmp_menu.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "field/comm_union_beacon.h"

#include "savedata/wifilist.h"
#include "savedata/zukanwork.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "../record/record.naix"			// グラフィックアーカイブ定義


//==============================================================================
// 構造体定義
//==============================================================================
typedef struct{
	int seq;
	int heroy;
	int sex;
	WORLDTRADE_WORK *wk;
}HERO_DEMO_WORK;


//==============================================================================
// プロトタイプ宣言
//==============================================================================
static void HeroDemoTask(  TCB_PTR tcb, void *work  );
static void HeroReturnDemoTask(  TCB_PTR tcb, void *work  );
static void SetSubLcdObj_Pos( CLACT_WORK_PTR act, int x, int y );
static void HeroAnimeChange( HERO_DEMO_WORK *hdw, int animeno );
static void LoadFieldObjData( WORLDTRADE_WORK *wk );
static void TransFieldObjData( NNSG2dCharacterData *CharaData, NNSG2dPaletteData *PalData, int id, int view, int sex );
static int ObjAppearNoGet( int objno );



//==============================================================================
// 定数定義
//==============================================================================

#define HERO_START_POSX	( 128 )
#define HERO_START_POSY	( -40 )

#define HERO_LAND_POSY	( 160 )

#define HERO_STOP_POSY	( 130 )

#define OBJPOS1_X	( 128 )
#define OBJPOS2_X	(  88+8 )
#define OBJPOS3_X	( 168-8 )
#define OBJPOS4_X	(  56+8 )
#define OBJPOS5_X	( 200-8 )
#define OBJPOS6_X	(  40+8 )
#define OBJPOS7_X	( 216-8 )

#define OBJPOS1_Y	( 40 +16-2 )
#define OBJPOS2_Y	( 44 +16-5 )
#define OBJPOS3_Y	( 56 +16-2 )
#define OBJPOS4_Y	( 88 +16-2 )


#define FIELD_OBJ_NO_START			( 14 )
#define FIELD_OBJ_STAND_NO_START	( 17 )

// 人物OBJキャラグラフィックファイルのバイト数
#define FIELDOBJ_NCG_SIZE	(256*256/2)

//==============================================================================
// 検索結果ＯＢＪの座標
//==============================================================================
static const u16 obj_postable[][2]={
	{ OBJPOS1_X,  OBJPOS1_Y },
	{ OBJPOS2_X,  OBJPOS2_Y },
	{ OBJPOS3_X,  OBJPOS2_Y },
	{ OBJPOS4_X,  OBJPOS3_Y },
	{ OBJPOS5_X,  OBJPOS3_Y },
	{ OBJPOS6_X,  OBJPOS4_Y },
	{ OBJPOS7_X,  OBJPOS4_Y },
};


//==============================================================================
/**
 * @brief   下画面セルアクター表示登録
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdActorAdd( WORLDTRADE_WORK *wk, int sex )
{
	CLACT_ADD add;
	int i;

	
	// ついでにフィールドＯＢＪグラフィック読み込み
	LoadFieldObjData( wk );

	WorldTrade_MakeCLACT( &add,  wk, &wk->clActHeader_sub, NNS_G2D_VRAM_TYPE_2DSUB );

	// 主人公アクター登録
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.mat.x = FX32_ONE *   HERO_START_POSX;
	add.mat.y = FX32_ONE * ( 130 ) + NAMEIN_SUB_ACTOR_DISTANCE;
	wk->SubActWork[0] = CLACT_Add(&add);
	CLACT_SetAnmFlag(wk->SubActWork[0],1);

	// 上を向いて立つ
	CLACT_AnmChg( wk->SubActWork[0], 3+sex*7 );
	CLACT_SetDrawFlag( wk->SubActWork[0], 1 );
	
	// 検索結果ＯＢＪ登録＆隠す
	for(i=0;i<7;i++){
		wk->SubActWork[i+1] = CLACT_Add(&add);
		CLACT_SetAnmFlag(wk->SubActWork[i+1],1);
		CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_NO_START+i*4 );
		CLACT_SetDrawFlag( wk->SubActWork[i+1], 0 );
		SetSubLcdObj_Pos( wk->SubActWork[i+1], obj_postable[i][0], obj_postable[i][1] );
	}

}

//==============================================================================
/**
 * @brief   主人公登場デモ
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_HeroDemo( WORLDTRADE_WORK *wk, int sex )
{
	
	// 主人公＆検索結果ＯＢＪ登録
	WorldTrade_SubLcdActorAdd( wk, sex );
	
	// デモタスク登録
	{
		HERO_DEMO_WORK *hdw;

		wk->demotask = PMDS_taskAdd( HeroDemoTask, sizeof(HERO_DEMO_WORK), 5, HEAPID_WORLDTRADE);
		hdw          = TCB_GetWork(wk->demotask);
		hdw->seq     = 0;
		hdw->heroy   = HERO_START_POSY;
		hdw->sex     = sex;
		hdw->wk      = wk;

		// くるくる回る
		HeroAnimeChange( hdw, 0 );
		Snd_SePlay( SE_GTC_PLAYER_IN );
	}
}


//------------------------------------------------------------------
/**
 * @brief   主人公の性別に合わせてアニメ変更をかける
 *
 * @param   wk		
 * @param   animeno		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroAnimeChange( HERO_DEMO_WORK *hdw, int animeno )
{
	CLACT_AnmChg( hdw->wk->SubActWork[0], animeno+hdw->sex*7 );
}

enum{
	HERO_DEMO_FALL=0,
	HERO_DEMO_FALL_STOP,
	HERO_DEMO_WALK,
	HERO_DEMO_WALK_STOP,
};

//------------------------------------------------------------------
/**
 * @brief   主人公の動きタスク
 *          (くるくる降りてくる→ゆっくり止まる→上にむかって歩く）
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroDemoTask(  TCB_PTR tcb, void *work  )
{
	int i;
	HERO_DEMO_WORK *hdw = (HERO_DEMO_WORK *)work;
	WORLDTRADE_WORK *wk = hdw->wk;

	switch(hdw->seq){
	// 主人公落ちてくる
	case HERO_DEMO_FALL:
		if( hdw->heroy > HERO_LAND_POSY ){
			hdw->heroy = HERO_LAND_POSY;
			hdw->seq = HERO_DEMO_FALL_STOP;
			// 回転がゆっくりになって止まる
			HeroAnimeChange( hdw, 1 );
		}
		hdw->heroy+=5;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		break;

	// 主人公回転終了
	case HERO_DEMO_FALL_STOP:
		if( !CLACT_AnmActiveCheck( wk->SubActWork[0] ) ){
			HeroAnimeChange( hdw, 2 );
			hdw->seq = HERO_DEMO_WALK;
		}
		break;

	// 上に向かって歩く
	case HERO_DEMO_WALK:
		if( hdw->heroy <HERO_STOP_POSY ){
			hdw->heroy = HERO_STOP_POSY;
			hdw->seq = HERO_DEMO_WALK_STOP;
			// 回転がゆっくりになって止まる
			HeroAnimeChange( hdw, 3 );

		}
		hdw->heroy-=2;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		
		break;

	// デモ終了（たぶん機械のスイッチＯＮとかが走る）
	case HERO_DEMO_WALK_STOP:

		Snd_SePlay( SE_GTC_ON );
		hdw->wk->demo_end = 1;
		PMDS_taskDel(tcb);
		break;
	}


}

//==============================================================================
/**
 * @brief   主人公さようならデモ
 *
 * @param   wk		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_ReturnHeroDemo( WORLDTRADE_WORK *wk, int sex )
{

	// デモタスク登録
	{
		HERO_DEMO_WORK *hdw;

		wk->demotask = PMDS_taskAdd( HeroReturnDemoTask, sizeof(HERO_DEMO_WORK), 5, HEAPID_WORLDTRADE);
		hdw          = TCB_GetWork(wk->demotask);
		hdw->seq     = 0;
		hdw->heroy   = HERO_STOP_POSY;
		hdw->sex     = sex;
		hdw->wk      = wk;

		// 下に向かって歩く
		HeroAnimeChange( hdw, 5 );
		Snd_SePlay( SE_GTC_OFF );

	}
}


enum{
	R_HERO_DEMO_WALK=0,
	R_HERO_DEMO_WALK_STOP,
	R_HERO_DEMO_RISE,
	R_HERO_DEMO_RISE_END,
};

//------------------------------------------------------------------
/**
 * @brief   主人公の動きタスク
 *          (くるくる降りてくる→ゆっくり止まる→上にむかって歩く）
 *
 * @param   tcb		
 * @param   work		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void HeroReturnDemoTask(  TCB_PTR tcb, void *work  )
{
	int i;
	HERO_DEMO_WORK *hdw = (HERO_DEMO_WORK *)work;
	WORLDTRADE_WORK *wk = hdw->wk;

	switch(hdw->seq){
	// 主人公下に向かって歩く
	case R_HERO_DEMO_WALK:
		if( hdw->heroy > HERO_LAND_POSY ){
			hdw->heroy = HERO_LAND_POSY;
			hdw->seq = R_HERO_DEMO_WALK_STOP;
			// 回転し始める
			HeroAnimeChange( hdw, 6 );
		}
		hdw->heroy+=2;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		break;

	// 主人公回転し始める
	case R_HERO_DEMO_WALK_STOP:
		if( !CLACT_AnmActiveCheck( wk->SubActWork[0] ) ){
			HeroAnimeChange( hdw, 0 );
			hdw->seq = R_HERO_DEMO_RISE;
			Snd_SePlay( SE_GTC_PLAYER_OUT );
		}
		break;

	// 主人公登っていく
	case R_HERO_DEMO_RISE:
		if( hdw->heroy <-20 ){
			hdw->seq = R_HERO_DEMO_RISE_END;
			// もう画面外なのでなんでもいい
			HeroAnimeChange( hdw, 3 );
		}
		hdw->heroy-=5;
		SetSubLcdObj_Pos( wk->SubActWork[0], HERO_START_POSX, hdw->heroy );
		
		break;

	// 画面から消えたら隠して終了
	case R_HERO_DEMO_RISE_END:

		hdw->wk->demo_end = 1;
		PMDS_taskDel(tcb);
		break;
	}


}



//------------------------------------------------------------------
/**
 * @brief   サブ画面アクターの座標を代入する
 *
 * @param   act		アクターのポインタ
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetSubLcdObj_Pos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x );
	mat.y = FX32_CONST( y - 8 ) + NAMEIN_SUB_ACTOR_DISTANCE;
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}

// 検索結果ＯＢＪをタッチするための座標テーブル
static const RECT_HIT_TBL obj_touchtbl[]={
	{	OBJPOS1_Y-16, OBJPOS1_Y+16, OBJPOS1_X-16, OBJPOS1_X+16,},
	{	OBJPOS2_Y-16, OBJPOS2_Y+16, OBJPOS2_X-16, OBJPOS2_X+16,},
	{	OBJPOS2_Y-16, OBJPOS2_Y+16, OBJPOS3_X-16, OBJPOS3_X+16,},
	{	OBJPOS3_Y-16, OBJPOS3_Y+16, OBJPOS4_X-16, OBJPOS4_X+16,},
	{	OBJPOS3_Y-16, OBJPOS3_Y+16, OBJPOS5_X-16, OBJPOS5_X+16,},
	{	OBJPOS4_Y-16, OBJPOS4_Y+16, OBJPOS6_X-16, OBJPOS6_X+16,},
	{	OBJPOS4_Y-16, OBJPOS4_Y+16, OBJPOS7_X-16, OBJPOS7_X+16,},
	{RECT_HIT_END,0,0,0},		// 終了データ
};

//------------------------------------------------------------------
/**
 * @brief   下画面のＯＢＪタッチチェック
 *
 * @param   max		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int WorldTrade_SubLcdObjHitCheck( int max )
{
	int button=GF_TP_RectHitTrg( obj_touchtbl );
	if( button != RECT_HIT_NONE ){
		if(button<max){
			return button;
		}
	}
	

	return -1;
}

//==============================================================================
/**
 * @brief   検索結果の数だけＯＢＪを表示させる
 *
 * @param   wk		
 * @param   num		検索Hitした人数
 * @param   flag	0:登場アニメいらない	1:登場アニメさせる
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdMatchObjAppear( WORLDTRADE_WORK *wk, int num, int flag )
{
	int i;

	// 登場SE
	if(num!=0 && flag==1){
		Snd_SePlay( SE_GTC_APPEAR );
	}

	// 検索人数分
	for(i=0;i<SEARCH_POKE_MAX;i++){

		if(i<num){
			// HITした方を登場させる
			int view = wk->DownloadPokemonData[i].trainerType;
			int sex  = wk->DownloadPokemonData[i].gender;

			OS_TPrintf("OBJ登場 view=%02x, sex=%d\n", view, sex);
		
			TransFieldObjData( wk->FieldObjCharaData, wk->FieldObjPalData, i, view, sex );

			// アニメさせるかさせないか
			if(flag){
				CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_NO_START+i*4 );
			}else{
				CLACT_AnmChg( wk->SubActWork[i+1], FIELD_OBJ_STAND_NO_START+i*4 );
			}
			CLACT_SetDrawFlag( wk->SubActWork[i+1], 1 );
		}else{

			// 表示OFF
			CLACT_SetDrawFlag( wk->SubActWork[i+1], 0 );
		}
	}
	
}


//------------------------------------------------------------------
/**
 * @brief   ニトロキャラクター上でOBJが立っているセルアニメは何番か？
 *
 * @param   objno		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ObjAppearNoGet( int objno )
{
	return FIELD_OBJ_NO_START + objno*4;
}

//==============================================================================
/**
 * @brief   検索結果ＯＢＪを全てひっこめる
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void WorldTrade_SubLcdMatchObjHide( WORLDTRADE_WORK *wk )
{
	int i;
	for(i=0;i<7;i++){
		if(CLACT_GetDrawFlag(wk->SubActWork[i+1])){
			if(CLACT_AnmGet(wk->SubActWork[i+1]) != ObjAppearNoGet( i )+1){
				CLACT_AnmChg( wk->SubActWork[i+1], ObjAppearNoGet( i )+1 );
			}
		}
	}
}


//------------------------------------------------------------------
/**
 * @brief   フィールドOBJ画像読み込み（ユニオンと自機）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LoadFieldObjData( WORLDTRADE_WORK *wk )
{
	// パレット読み込み
	wk->FieldObjPalBuf = ArcUtil_PalDataGet( ARC_RECORD_GRA, NARC_record_union_chara_nclr, &(wk->FieldObjPalData), HEAPID_WORLDTRADE );

	// 画像読み込み
	wk->FieldObjCharaBuf = ArcUtil_CharDataGet( ARC_RECORD_GRA, NARC_record_union_chara_lz_ncgr,  1, &(wk->FieldObjCharaData), HEAPID_WORLDTRADE );
	DC_FlushRange( wk->FieldObjCharaData, FIELDOBJ_NCG_SIZE );

}

#define OBJ_TRANS_SIZE	( 4*4 )
static const u16 obj_offset[]={
	( 32*9                    )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*1 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*2 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*3 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*4 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*5 )*0x20,
	( 32*9 + OBJ_TRANS_SIZE*6 )*0x20,
};


//------------------------------------------------------------------
/**
 * @brief   渡されたユニオン見た目コードからフィールドOBJのキャラを転送する
 *
 * @param   id		
 * @param   view		
 * @param   sex		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransFieldObjData( NNSG2dCharacterData *CharaData, NNSG2dPaletteData *PalData, int id, int view, int sex )
{
	int pos;
	u8 *chara, *pal;
	
	// ユニオンキャラを転送

	pos   = UnionView_GetCharaNo( sex, view );

	chara = (u8*)CharaData->pRawData;
	pal   = (u8*)PalData->pRawData;

	GXS_LoadOBJ( &chara[(OBJ_TRANS_SIZE*3)*pos*0x20], obj_offset[id], OBJ_TRANS_SIZE*0x20 );
	GXS_LoadOBJPltt( &pal[pos*32], (id+2)*32, 32 );

	OS_Printf("ID=%d のユニオン見た目は %d アイコン番号は %d\n", id, view, pos);



	
	
}

//------------------------------------------------------------------
/**
 * @brief   フィールドOBJ画像解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void FreeFieldObjData( WORLDTRADE_WORK *wk )
{
	if(wk->demo_end){
		sys_FreeMemoryEz( wk->FieldObjPalBuf  );
                      
		sys_FreeMemoryEz( wk->FieldObjCharaBuf );
	}
}
