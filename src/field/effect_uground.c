//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		effect_uground.c
 *@brief	地下マップフェードエンカウント
 *@author	tomoya takahashi 
 *@data		2005.08.03
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define CLACT_OLD_NONE
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "system/snd_tool.h"
#include "field_event.h"
#include "system/palanm.h"
#include "system/mystatus.h"


#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/wipe.h"

#include "player.h"


#define __EFFECT_UGROUND_H_GLOBAL
#include "effect_uground.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define UNDER_TCB_PRI	(5)




////////////////////////////////////////////////////////////
//
//	描画システム用
//
///////////////////////////////////////////////////////////
#define DRAW_2D_RES_NUM		(4)		// 管理するリソースの種類
#define DRAW_2D_OBJ_TBL_NUM	(2)		// 管理するオブジェテーブル数


//-------------------------------------
//	
//	動作関数戻り値
//	
//=====================================
enum{
	EFCT_SYSRET_END,		// エラーコード
	EFCT_SYSRET_OK,			// 正常
	EFCT_SYSRET_FADE,		// フェード開始
} EFCT_UG_SYSRET;


//-------------------------------------
//	
//	全体に共通
//	
//=====================================
#define EFECT_UGCOMMON_OBJ_MAT_X	(112*FX32_ONE)
#define EFECT_UGCOMMON_OBJ_MAT_Y	(69*FX32_ONE)


//-------------------------------------
//	
//	タスク００
//	地下マップへのフェード１
//	
//=====================================
enum{
	EFCT_UG00_PLAYER_OFF,	// プレイヤーを消す
	EFCT_UG00_SHADOW,		// 影作成
	EFCT_UG00_OBJ_MOVE,		// オブジェクト移動
	EFCT_UG00_FADE_WAIT,	// ブラックフェード待ち
	EFCT_UG00_OAMCLEAN,		// OAMCLEAN
	EFCT_UG00_DELETE,		// 破棄
};
#define EFCT_UG00_SHADOW_COUNT	(7)		// これになったら終了
#define EFCT_UG00_OBJ_JUMP_DIS	(16*FX32_ONE)	// ジャンプ力
#define	EFCT_UG00_OBJ_CNNUM		(0x8000/16)	// カウンタ足す値
#define EFCT_UG00_OBJ_END		(0x8000)	// カウンタ終了
#define EFCT_UG00_FADE_START	(EFCT_UG00_OBJ_CNNUM*16)	// フェード開始

#define EFCT_UG00_BR_MSK		( PLANEMASK_BG0| PLANEMASK_BG2| PLANEMASK_BG3| PLANEMASK_BD )
#define EFCT_UG00_BR_SYNC		( 2 )
#define EFCT_UG00_BR_S			( 0 )
#define EFCT_UG00_BR_E			( -8 )

#define EFCT_UG00_BR_WAIT		( 6 )


//-------------------------------------
//	
//	タスク０１
//	地下マップへのフェード２
//	
//=====================================
enum{
	EFCT_UG01_OBJ_OFF,
	EFCT_UG01_START,		// 開始
	EFCT_UG01_OBJ_MOVE,		// オブジェクト移動
	EFCT_UG01_BG_FADE,		// BGをフェードインさせる
	EFCT_UG01_OAMCLEAN,		// OAMCLEAN
	EFCT_UG01_DELETE,		// 破棄
};
#define EFCT_UG01_END	(EFECT_UGCOMMON_OBJ_MAT_Y)			// オブジェの高さがこれになったらオブジェの移動終了
#define EFCT_UG01_REST	(384*FX32_ONE)			// オブジェの高さがこれになったらオブジェの移動終了
#define EFCT_UG01_MOVE	(FX32_ONE*8)			// 移動スピード
#define EFCT_UG01_BG	(16)						// BG面を動かすスピード
#define EFCT_UG01_OBJ_MAT_Y	(192*FX32_ONE)		// オブジェクト開始位置
#define EFCT_UG01_OBJ_MAT_REST_Y	(-32*FX32_ONE)	// オブジェクト開始位置

//-------------------------------------
//	
//	タスク０２
//	地下マップへのフェード３
//	
//=====================================
enum{
	EFCT_UG02_PLAYER_OFF,	// プレイヤーを消す
	EFCT_UG02_START,		// 開始
	EFCT_UG02_BG_FADE,		// BGをフェードインさせる
	EFCT_UG02_OBJ_MOVE,		// オブジェクト移動
	EFCT_UG02_FADE_WAIT,	// フェードアウト
	EFCT_UG02_OAMCLEAN,		// OAM初期化
	EFCT_UG02_DELETE,		// 破棄
};
#define EFCT_UG02_REST	(-32*FX32_ONE)			// オブジェの高さがこれになったらオブジェの移動終了
#define EFCT_UG02_END	(192*FX32_ONE)			// オブジェの高さがこれになったらオブジェの移動終了
#define EFCT_UG02_MOVE	(FX32_ONE*8)			// 移動スピード
#define EFCT_UG02_BG	(32)					// BG面を動かすスピード
#define EFCT_UG02_FADE_S	(300*FX32_ONE)		// ホワイトアウトはじめるタイミング
#define EFCT_UG02_ROTA_SA	(FX32_CONST(0.20f))	// 回転加速度
#define EFCT_UG02_ROTA_SE	(2*FX32_ONE)		// 回転加速最速

#define EFCT_UG02_OBJ_MAT_REST_Y (384*FX32_ONE)		// オブジェクト開始位置

//-------------------------------------
//	
//	タスク０３
//	地下マップへのフェード４
//	
//=====================================
enum{
	EFCT_UG03_START,		// 開始
	EFCT_UG03_FADEIN_M,		// メイン画面フェードイン
	EFCT_UG03_FADEIN_MW,	// フェードイン待ち
	EFCT_UG03_OBJ_MOVE,		// オブジェクト動作
	EFCT_UG03_OBJ_SHADOW,	// オブジェクト動作
	EFCT_UG03_OAMCLEAN,		// OAMCLEAN
	EFCT_UG03_DELETE,		// 破棄
};

#define EFCT_UG03_ROTA_S	(2*FX32_ONE)		// 回転初速
#define EFCT_UG03_ROTA_SA	(FX32_CONST(0.40f))	// 回転加速度
#define EFCT_UG03_ROTA_SE	(0)					// 回転加速最速
#define EFCT_UG03_SHADOW_COUNT	(8)		// これになったら終了
#define EFCT_UG03_OBJ_JUMP_DIS	(32*FX32_ONE)	// ジャンプ力
#define	EFCT_UG03_OBJ_CNNUM		(0x8000/8)	// カウンタ足す値
#define EFCT_UG03_OBJ_END		(0x8000)	// カウンタ終了
#define EFCT_UG03_FADE_START	(EFCT_UG00_OBJ_CNNUM*10)	// フェード開始
#define EFCT_UG03_OBJ_DEL_WAIT	( 6 )

#define EFCT_UG03_BR_MSK		( PLANEMASK_BG0| PLANEMASK_BG2| PLANEMASK_BG3| PLANEMASK_BD )
#define EFCT_UG03_BR_SYNC		( 2 )
#define EFCT_UG03_BR_S			( -8 )
#define EFCT_UG03_BR_E			( 0 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	描画システムデータ
//	
//=====================================
typedef struct {
	/* ２ｄシステムデータ  */
	CLACT_SET_PTR			clactSet;						// セルアクターセット
	CLACT_HEADER_TBL_PTR	clactHeader;					// ヘッダー
	CLACT_U_RES_MANAGER_PTR	resMan[DRAW_2D_RES_NUM];		// リソースマネージャ
	CLACT_U_RES_OBJ_TBL*	resObjTbl[DRAW_2D_OBJ_TBL_NUM];	// リソースオブジェテーブル
	int						resObjNum[DRAW_2D_RES_NUM];		// それぞれのリソースオブジェ数
	CLACT_U_EASYRENDER_DATA	renddata;						// 簡易レンダーデータ
	

	/* 3dシステムデータ（今はなし） */

} EFCT_UG_DRAWSYS;

//-------------------------------------
//	
//	地下マップフェードエフェクト
//	オブジェクト構造体
//	
//=====================================
typedef struct _EFCT_UG_OBJ{
	void*		data;		// このサイズ内に各データを入れる
	
	/* データ作成関数 */
	void (*init)(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);

	/* データ破棄関数 */
	void (*delete)(struct _EFCT_UG_OBJ* data);
	
	/* 動作関数 */
	int (*move)(struct _EFCT_UG_OBJ* data);
} EFCT_UG_OBJ;


//-------------------------------------
//	
//	地下マップフェードエフェクト構造体
//	
//=====================================
typedef struct _EFCT_UG_DATA{
	/* フィールドシステムワーク */
	FIELDSYS_WORK* fsys;

	/* 描画システムデータ */
	EFCT_UG_DRAWSYS	drawsys;
	
	/* オブジェクトデータ */
	EFCT_UG_OBJ	objdata[2];
	int			obj_num;	// オブジェクト数
	
	/* シーケンスデータ */
	int			seq;

	/* フェードなどの終了感知領域 */
	int			wait;

	BOOL*	end;
} EFCT_UG_DATA;


//-----------------------------------------------------------------------------
//
//		個々のオブジェクト用
//
//=============================================================================
//-------------------------------------
//	
//	主人公オブジェクト
//	
//=====================================
typedef struct {
	VecFx32			matrix;		// 座標
	CLACT_WORK_PTR	cl;			// セルアクター
	int				count;		// 動作カウンタ
} EFCT_UG_HERO;

typedef struct {
	VecFx32			matrix;		// 座標
	CLACT_WORK_PTR	cl;			// セルアクター
	int				seq;		// シーケンス
	int				count;		// 動作カウンタ
} EFCT_UG_HERO_EX;

//-------------------------------------
//	
//	影オブジェクト
//	
//=====================================
typedef struct {
	VecFx32			matrix;		// 座標
	CLACT_WORK_PTR	cl;			// セルアクター
	int				count;		// 動作カウンタ
} EFCT_UG_SHADOW;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void UGround00(TCB_PTR tcb, void* work);		// 地下マップフェード00	地面にもぐってく
static void UGround01(TCB_PTR tcb, void* work);		// 地下マップフェード01	地下に降りる
static void UGround02(TCB_PTR tcb, void* work);		// 地下マップフェード02	地下から上る
static void UGround03(TCB_PTR tcb, void* work);		// 地下マップフェード03	地上に出る

static EFCT_UG_DATA* UGroundAdd(TCB_FUNC func, FIELDSYS_WORK* fsys, u32 resload_vram);
static void UGroundDelete(TCB_PTR tcb, EFCT_UG_DATA* data);
void initDrawSys(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram);
static void deleteDrawSys(EFCT_UG_DRAWSYS* data);		// 描画システムの破棄
static void makeObj(EFCT_UG_DATA* data, EFCT_UG_OBJ* obj, int num);	// オブジェクトデータの作成
static CLACT_WORK_PTR addCellAct(EFCT_UG_DRAWSYS* drawsys, int act_no, VecFx32* mat,int pri, int drawarea);
static void deleteObj(EFCT_UG_OBJ* obj);// オブジェクトデータの破棄
static void initBG(GF_BGL_INI* bgl);	// BG面の初期化
static void destBG(GF_BGL_INI* bgl);		// BG面の初期化
static void loadBG(GF_BGL_INI* bgl, const char* p_char, const char* p_pltt,const char* p_screen, int pltt_no, int frame, int charoffs);

//static void maskBGScrollInit(int sc_mask, int other_mask);
//static void maskBGScroll(GF_BGL_INI* bgl,int plane_mask, int h, int v);
//static void maskBGScrollDelete(void);

/////////////////////////////////////////////////////////////////////
//
//		２ｄ表示システム用関数郡
//
////////////////////////////////////////////////////////////////////
static void init2DDrawSys(EFCT_UG_DRAWSYS* data);	// ２ｄの描画システム初期化
static void load2DResFile(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram);
static int loadOneData(CLACT_U_RES_MANAGER_PTR resMan, CLACT_U_RES_OBJ_TBL** resObjTbl, const char* path);

static void delete2DDrawSys(EFCT_UG_DRAWSYS* data);	// ２ｄの描画システム初期化
//---------------------------------------------------------
//
//	個々のオブジェクト用
//
//=========================================================
//---------地下フェードジャンプ主人公
static void initObj00(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj00(struct _EFCT_UG_OBJ* data);
static int  moveObj00(struct _EFCT_UG_OBJ* data);
//---------地下フェード広がる影
static void initObj01(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj01(struct _EFCT_UG_OBJ* data);
static int  moveObj01(struct _EFCT_UG_OBJ* data);
//---------地下フェード落ちる主人公
static void initObj02(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj02(struct _EFCT_UG_OBJ* data);
static int  moveObj02(struct _EFCT_UG_OBJ* data);
//---------地下フェード上る主人公
static void initObj03(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj03(struct _EFCT_UG_OBJ* data);
static int  moveObj03(struct _EFCT_UG_OBJ* data);
//---------地下フェード地上に出てくる主人公
static void initObj04(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj04(struct _EFCT_UG_OBJ* data);
static int  moveObj04(struct _EFCT_UG_OBJ* data);
//---------地下フェード縮む影
static void initObj05(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data);
static void deleteObj05(struct _EFCT_UG_OBJ* data);
static int  moveObj05(struct _EFCT_UG_OBJ* data);


// 男女キャラクタ　CLACT　データパス
const static char* BoyGirlCharPathTbl[ 2 ] = {
	"data/uground_char.resdat",
	"data/uground_char2.resdat",
};

const static char* BoyGirlPlttPathTbl[ 2 ] = {
	"data/uground_pltt.resdat",
	"data/uground_pltt2.resdat",
};


const static u8 UnderGroundEff_VramTbl[ 4 ] = {
	NNS_G2D_VRAM_TYPE_2DMAIN,
	NNS_G2D_VRAM_TYPE_MAX,
	NNS_G2D_VRAM_TYPE_MAX,
	NNS_G2D_VRAM_TYPE_2DMAIN,
};


//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェード00
 *
 *@param	tcb		タスクデータ
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround00(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret[2];		// ２オブジェ用戻り値
	int i;			// ループ用
	int last_seq;

	last_seq = data->seq; 

	if(data->drawsys.clactSet){
		// セルアクターメイン関数
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG00_PLAYER_OFF:
		// イベントlockクリア
		FieldOBJ_MovePauseClear( Player_FieldOBJGet( data->fsys->player ) );
		// プレイヤーを消す
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG00_SHADOW:		// 影作成
		makeObj(data, &data->objdata[0], 0);		// 主人公作成
		makeObj(data, &data->objdata[1], 1);		// 影作成
		data->obj_num = 2;
		data->seq ++;
		break;

	case EFCT_UG00_OBJ_MOVE:		// オブジェクトを動作させる
		for(i=0;i<data->obj_num;i++){
			ret[i] = data->objdata[i].move(&data->objdata[i]);
		}
		// ブラックフェード開始を検知
		if(ret[0] == EFCT_SYSRET_FADE){
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		}

		// 終了検知
		for(i=0;i<data->obj_num;i++){
			if(ret[i] != EFCT_SYSRET_END ){
				break;
			}
		}
		if(i == data->obj_num){
			data->seq++;		// 次へ
		}
		break;

	case EFCT_UG00_FADE_WAIT:	// フェード待ち
		if( WIPE_SYS_EndCheck() ){
			data->seq++;
		}
		break;

	case EFCT_UG00_OAMCLEAN:
		for(i=0;i<data->obj_num;i++){
			deleteObj(&data->objdata[i]);
		}
		data->seq++;
		break;

	case EFCT_UG00_DELETE:
		*(data->end) = TRUE;

		// 大本システムも破棄
		UGroundDelete(tcb, data);
		break;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェード01
 *
 *@param	tcb		タスクデータ
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround01(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret;
	int last_seq;
	u16 clearPal=0;

	last_seq = data->seq; 

	if(last_seq != EFCT_UG01_DELETE){
		// セルアクターメイン関数
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG01_OBJ_OFF:
		// プレイヤーを消す
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG01_START:
		//maskBGScrollInit(GX_WND_PLANEMASK_BG2, GX_WND_PLANEMASK_BG3);
//		maskBGScrollInit(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_OBJ);
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, -255, 0);
		
		GF_BGL_PaletteSet( GF_BGL_FRAME0_S, &clearPal, 2, 0 );	// パレットクリア
		
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);		// BG0面オフ
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);		// BG1面オフ
	
		
		// OBJのみブライトネス解除	
		makeObj(data, &data->objdata[0], 2);		// 主人公作成
	
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		
		// 落下音
		Snd_SePlay( SE_UG_CHG_DOWN );

		data->obj_num = 1;
		data->seq++;
		break;
	

	case EFCT_UG01_OBJ_MOVE:		// オブジェクトを動作させる
		ret = data->objdata[0].move(&data->objdata[0]);

		// 終了検知
		if((ret == EFCT_SYSRET_END) && (WIPE_SYS_EndCheck())){
			// 着地音
			Snd_SePlay( SE_LANDING );
			data->seq++;		// 次へ
			data->wait = -255;
		}
		break;
		
	case EFCT_UG01_BG_FADE:
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, data->wait, 0);
		data->wait += EFCT_UG01_BG;
		if(data->wait > 0){
//			maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
			data->seq++;
			// プレイヤーを表示
			Player_DispON_OFF_Set( data->fsys->player, TRUE );
		
		}
		break;

	case EFCT_UG01_OAMCLEAN:
		deleteObj(&data->objdata[0]);
		data->seq++;
		break;

	case EFCT_UG01_DELETE:		// 終了なのでデータ破棄
		*(data->end) = TRUE;
		// 大本システムも破棄
		UGroundDelete(tcb, data);
//		maskBGScrollDelete();
		break;
	}

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェード02	地上へのフェード
 *
 *@param	tcb		タスクデータ
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround02(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret;
	int last_seq;

	last_seq = data->seq;

	if(last_seq != EFCT_UG02_DELETE){
		// セルアクターメイン関数
		CLACT_Draw(data->drawsys.clactSet);
	}

	switch(data->seq){
	case EFCT_UG02_PLAYER_OFF:
		// プレイヤーを消す
		Player_DispON_OFF_Set( data->fsys->player, FALSE );
		data->seq++;
		break;

	case EFCT_UG02_START:
//		maskBGScrollInit(GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, GX_WND_PLANEMASK_BG1|GX_WND_PLANEMASK_OBJ);
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
		
		makeObj(data, &data->objdata[0], 3);		// 主人公作成

		// 浮上音
		Snd_SePlay( SE_UG_CHG_UP );

		data->obj_num = 1;
		data->seq++;
		break;

	case EFCT_UG02_BG_FADE:		// BG面フェード
//		maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, data->wait, 0);
		data->wait -= EFCT_UG02_BG;
		if(data->wait < -255){
//			maskBGScroll(data->fsys->bgl, GF_BGL_FRAME0_S, 0, 0);
//			maskBGScrollDelete();
			GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);

			data->seq++;
		}
		break;

	case EFCT_UG02_OBJ_MOVE:
		ret = data->objdata[0].move(&data->objdata[0]);

		// ホワイトフェード開始を検知
		if(ret == EFCT_SYSRET_FADE){
			data->wait = 0;
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_WHITE, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		}
		
		// 終了検知
		if(ret == EFCT_SYSRET_END){
			data->seq++;		// 次へ
		}
		break;

	case EFCT_UG02_FADE_WAIT:		// フェード待ち
		if( WIPE_SYS_EndCheck() ){
			data->wait = 0;
			data->seq++;
		}
		break;

	case EFCT_UG02_OAMCLEAN:
		deleteObj(&data->objdata[0]);
		data->seq++;
		break;
	
	case EFCT_UG02_DELETE:		// 終了なのでデータ破棄
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);

		*(data->end) = TRUE;
		
		// 大本システムも破棄
		UGroundDelete(tcb, data);
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェード03
 *
 *@param	tcb		タスクデータ
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGround03(TCB_PTR tcb, void* work)
{
	EFCT_UG_DATA* data = (EFCT_UG_DATA*)work;
	int ret[2];		// ２オブジェ用戻り値
	int i;			// ループ用
	int last_seq;

	last_seq = data->seq;

	if(last_seq != EFCT_UG03_DELETE){
		// セルアクターメイン関数
		CLACT_Draw(data->drawsys.clactSet);
	}
	
	switch(data->seq){
	case EFCT_UG03_START:
		// プレイヤーを消す
		Player_DispON_OFF_Set( data->fsys->player, FALSE );

		makeObj(data, &data->objdata[0], 4);		// 主人公作成
		makeObj(data, &data->objdata[1], 5);		// 影作成
		data->obj_num = 2;
		data->seq++;
		break;

	case EFCT_UG03_FADEIN_M:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_FIELD );
		data->seq++;
		break;
		
	case EFCT_UG03_FADEIN_MW:	// サブフェードイン待ち
		if( WIPE_SYS_EndCheck() ){
			// 主人公回転音
			Snd_SePlay( SE_UG_CHG_TURN );
			data->seq++;
		}
		break;


	case EFCT_UG03_OBJ_MOVE:		// オブジェクトを動作させる
		ret[0] = data->objdata[0].move(&data->objdata[0]);

		if( ret[0] == EFCT_SYSRET_END ){
			// プレイヤーを表示
			Player_DispON_OFF_Set( data->fsys->player, TRUE );

			data->wait = EFCT_UG03_OBJ_DEL_WAIT;
			data->seq++;		// 次へ
		}
		break;

	case EFCT_UG03_OBJ_SHADOW:
		ret[1] = data->objdata[1].move(&data->objdata[1]);

		if( data->wait <= 0 ){
			if( data->wait == 0 ){
				deleteObj(&data->objdata[0]);
				data->wait --;
			}
		}else{
			data->wait--;
		}

		if( ret[1] == EFCT_SYSRET_END ){
			data->seq++;		// 次へ
		}
		break;

	case EFCT_UG03_OAMCLEAN:
		deleteObj(&data->objdata[1]);
		data->seq++;
		break;

	case EFCT_UG03_DELETE:		// 終了なのでデータ破棄

		*(data->end) = TRUE;
		// 大本システムも破棄
		UGroundDelete(tcb, data);
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェードエフェクト
 *
 *@param	fsys	フィールドシステムワーク
 *@param	no		エフェクトナンバー
 *@param	end		終了チェックフラグ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void StartUnderGroundEffect(FIELDSYS_WORK* fsys, int no, BOOL* end)
{
	EFCT_UG_DATA* data;
		
	/* オブジェクト作成 */
	switch(no){
	case EFCT_UG_DOWN00:
		data = UGroundAdd(UGround00, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_DOWN01:
		data = UGroundAdd(UGround01, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_UP00:
		data = UGroundAdd(UGround02, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	case EFCT_UG_UP01:
		data = UGroundAdd(UGround03, fsys, UnderGroundEff_VramTbl[ no ]);
		break;
	}

	data->end = end;
	data->fsys = fsys;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	地下エフェクトデータ作成
 *
 *@param	func	動作タスク
 *@param	fsys	フィールドシステム
 *@param	resload_vram	リソース読み込みVRAM
 *
 *@return	EFCT_UG_DATA*	データ
 *
 *
 */
//-----------------------------------------------------------------------------
EFCT_UG_DATA* UGroundAdd(TCB_FUNC func, FIELDSYS_WORK* fsys, u32 resload_vram )
{
	EFCT_UG_DATA* data;
	TCB_PTR tcb;
	int boy_girl;
	MYSTATUS* status;

		
	/* オブジェクト作成 */
	tcb = PMDS_taskAdd(func, sizeof(EFCT_UG_DATA), UNDER_TCB_PRI, HEAPID_FIELD);
	data = TCB_GetWork(tcb);

	/* 主人公が男か女か取得 */
	status = SaveData_GetMyStatus( fsys->savedata );
	boy_girl = MyStatus_GetMySex( status );
	
	/* 描画システム作成 */
	initDrawSys(&data->drawsys, boy_girl, resload_vram );

	return data;
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	地下マップフェードデータ破棄
 *
 *@param	tcb		タスクポインタ
 *@param	data	破棄データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void UGroundDelete(TCB_PTR tcb, EFCT_UG_DATA* data)
{
	// 描画システム破棄
	deleteDrawSys(&data->drawsys);

	PMDS_taskDel(tcb);	//タスク終了	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画システムを初期化＆データの読み込み
 *
 *@param	data		描画システムデータ
 *@param	boy_girl	男か女か
 *@param	resload_vram	読み込むVRAM
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initDrawSys(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram)
{
	// 描画システム初期化
	init2DDrawSys(data);

	// リソース読み込み
	load2DResFile(data, boy_girl, resload_vram);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	描画データの破棄
 *
 *@param	data		描画システムデータ
 *
 *@return	none 
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteDrawSys(EFCT_UG_DRAWSYS* data)
{
	delete2DDrawSys(data);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	２ｄ描画システム作成
 *
 *@param	data		描画システムデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void init2DDrawSys(EFCT_UG_DRAWSYS* data)
{
	// 簡易セルアクターセット作成
	// 上で作成した共有OAMマネージャを使用してレンダラーを作成し、
	// セルアクターセットの作成を行う
	data->clactSet = CLACT_U_SetEasyInit( 2, &data->renddata, HEAPID_FIELD );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	２ｄリソースを読み込む
 *
 *@param	data
 *@param	boy_girl	男か女か
 *@param	resload_vram	読み込むVRAM
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void load2DResFile(EFCT_UG_DRAWSYS* data, int boy_girl, u32 resload_vram)
{
	int i;
	void* buff;
	
	// リソースマネージャ作成
	for(i=0;i<DRAW_2D_RES_NUM;i++){
		data->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_FIELD);
	}

	// リソース読み込み
	// キャラクタ
	data->resObjNum[ CLACT_U_CHAR_RES ] = loadOneData(
			data->resMan[ CLACT_U_CHAR_RES ], 
			&data->resObjTbl[ CLACT_U_CHAR_RES ],
			BoyGirlCharPathTbl[ boy_girl ] );

	// 読み込むVRAM設定
	for( i=0; i<data->resObjTbl[ CLACT_U_CHAR_RES ]->tbl_now; i++ ){
		CLACT_U_ResManagerSetResObjVramType( data->resObjTbl[ CLACT_U_CHAR_RES ]->tbl[ i ], resload_vram );
	}
	
	// パレット
	data->resObjNum[ CLACT_U_PLTT_RES ] = loadOneData(
			data->resMan[ CLACT_U_PLTT_RES ], 
			&data->resObjTbl[ CLACT_U_PLTT_RES ],
			BoyGirlPlttPathTbl[ boy_girl ] );

	// 読み込むVRAM設定
	for( i=0; i<data->resObjTbl[ CLACT_U_PLTT_RES ]->tbl_now; i++ ){
		CLACT_U_ResManagerSetResObjVramType( data->resObjTbl[ CLACT_U_PLTT_RES ]->tbl[ i ], resload_vram );
	}


	// セル
	data->resObjNum[ CLACT_U_CELL_RES ] = loadOneData(
			data->resMan[ CLACT_U_CELL_RES ], 
			NULL,
			"data/uground_cell.resdat");
	// セルアニメ
	data->resObjNum[ CLACT_U_CELLANM_RES ] = loadOneData(
			data->resMan[ CLACT_U_CELLANM_RES ], 
			NULL,
			"data/uground_cellanm.resdat");

	// キャラクタマネージャに登録
	// Vramに配置します。
	CLACT_U_CharManagerSetsAreaCont(data->resObjTbl[0]);

	// パレットマネージャに登録
	// Vramに配置します。
	CLACT_U_PlttManagerSetsCleanArea(data->resObjTbl[1]);


	// セルアクターヘッダ読み込み
	buff = sys_LoadFile( HEAPID_FIELD, "data/uground_clact.cldat" );
	data->clactHeader = CLACT_U_MakeHeaderBinary(
			buff, HEAPID_FIELD,
			data->resMan[ CLACT_U_CHAR_RES ], 
			data->resMan[ CLACT_U_PLTT_RES ], 
			data->resMan[ CLACT_U_CELL_RES ],
			data->resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL);
	sys_FreeMemoryEz( buff );
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースタイプのリソースをヘッダーデータから読み込ム
 *
 *@param	resMan		リソースマネージャ(作成済み)
 *@param	resObjTbl	リソースオブジェテーブル受け取り先
 *@param	path		ロムヘッダパス
 *
 *@return	int		テーブル数
 *
 *
 */
//-----------------------------------------------------------------------------
static int loadOneData(CLACT_U_RES_MANAGER_PTR resMan, CLACT_U_RES_OBJ_TBL** resObjTbl, const char* path)
{
	CLACT_U_RES_HEADER_PTR res_head;		// リソースヘッダ
	CLACT_U_RES_OBJ_TBL* work;
	int	tbl_num;							// ヘッダ内テーブル数
	void* buff;
	

	res_head = sys_AllocMemoryLo( HEAPID_FIELD, CLACT_U_ResManagerGetHeaderSize() );

	// ヘッダ読み込み
	buff = sys_LoadFile( HEAPID_FIELD, path );
	CLACT_U_ResManagerHeaderLoadBinary(buff, res_head, HEAPID_FIELD);
	sys_FreeMemoryEz( buff );

	// ヘッダ数分のリソースオブジェテーブル作成
	if(resObjTbl != NULL){
		tbl_num		= CLACT_U_ResManagerHeaderSetDataNum(res_head);
		*resObjTbl	= CLACT_U_ResManagerResObjTblMake(tbl_num, HEAPID_FIELD);
		work = *resObjTbl;
	}else{
		work = NULL;
	}

	// リソース読み込み
	// キャラクタデータ読み込み
	tbl_num = CLACT_U_ResManagerResAddsHd(
				resMan,
				res_head,
				work,
				HEAPID_FIELD);

	// ヘッダ破棄
	CLACT_U_ResManagerHeaderFree(res_head);

	// ヘッダで確保したワーク破棄
	sys_FreeMemoryEz(res_head);

	return tbl_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	２D描画システムデータ破棄
 *
 *@param	data		描画システムデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delete2DDrawSys(EFCT_UG_DRAWSYS* data)
{
	int i;
	
	// セットの破棄
	CLACT_DestSet(data->clactSet);
	data->clactSet = NULL;
	
	// セルアクターヘッダー破棄
	CLACT_U_CLACT_HeaderTblDelete(data->clactHeader);
	data->clactHeader = NULL;

	// キャラクタデータ破棄
	CLACT_U_CharManagerDeletes( data->resObjTbl[ CLACT_U_CHAR_RES ] );
	
	// パレットデータ破棄
	CLACT_U_PlttManagerDeletes( data->resObjTbl[ CLACT_U_PLTT_RES ] );

	// キャラクタとパレットのリソースオブジェテーブルを破棄
	for(i=0;i<2;i++){
		CLACT_U_ResManagerResObjTblDelete(data->resObjTbl[i]);
	}

	// リソースマネージャ破棄
	for(i=0;i< DRAW_2D_RES_NUM;i++){
		CLACT_U_ResManagerDelete(data->resMan[i]);
	}
	
//	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
//	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクトの作成
 *
 *@param	data	エフェクトデータ
 *@param	obj		データ入力するオブジェ
 *@param	num		数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void makeObj(EFCT_UG_DATA* data, EFCT_UG_OBJ* obj, int num)
{
	memset(obj, 0, sizeof(EFCT_UG_OBJ));

	switch(num){
	case 0:
		obj->init	= initObj00;
		obj->delete = deleteObj00;
		obj->move	= moveObj00;
		break;
	case 1:
		obj->init	= initObj01;
		obj->delete = deleteObj01;
		obj->move	= moveObj01;
		break;
	case 2:
		obj->init	= initObj02;
		obj->delete = deleteObj02;
		obj->move	= moveObj02;
		break;
	case 3:
		obj->init	= initObj03;
		obj->delete = deleteObj03;
		obj->move	= moveObj03;
		break;
	case 4:
		obj->init	= initObj04;
		obj->delete = deleteObj04;
		obj->move	= moveObj04;
		break;
	case 5:
		obj->init	= initObj05;
		obj->delete = deleteObj05;
		obj->move	= moveObj05;
		break;
	}

	obj->init(&data->drawsys, obj);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターに登録
 *
 *@param	drawsys		描画システム
 *@param	act_no		アクターナンバー
 *@param	mat			座標
 *@param	pri			表示優先順位
 *@param	drawarea	描画エリア(最初の）
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_WORK_PTR addCellAct(EFCT_UG_DRAWSYS* drawsys, int act_no, VecFx32* mat, int pri, int drawarea)
{
	CLACT_ADD ca;
	CLACT_WORK_PTR obj;
	VecFx32 sca = {FX32_ONE, FX32_ONE, FX32_ONE};
	
	memset(&ca,0,sizeof(CLACT_ADD));
	ca.ClActSet		= drawsys->clactSet;
	ca.ClActHeader	= &drawsys->clactHeader->tbl[act_no];
	ca.mat			= *mat;
	ca.sca			= sca;
	ca.pri			= pri;
	ca.DrawArea		= drawarea;
	ca.heap			= HEAPID_FIELD;
	
	obj = CLACT_Add(&ca);
	GF_ASSERT(obj&&("セルアクター登録失敗\n"));

	return obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクト
 *
 *@param	data
 *@param	obj
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj(EFCT_UG_OBJ* obj)
{
	obj->delete( obj);
	memset(obj, 0, sizeof(EFCT_UG_OBJ));
}

//---------------------------------------------------------
//
//	個々のオブジェクト用
//
//=========================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェクトの登録
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェクトデータ登録テーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj00(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO));
	
	obj_w = (EFCT_UG_HERO*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェを破棄
 *
 *@param	data		オブジェデータ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj00(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェクトの動作関数
 *
 *@param	data	主人公オブジェクト
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj00(struct _EFCT_UG_OBJ* data)
{
	VecFx32	mat;	// セル描画座標
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	// ジャンプさせる
	// 頂上付近でフェード開始
	// 地面に到達したら終了
	if(obj_w->count <= EFCT_UG00_OBJ_END){
		mat = obj_w->matrix;
		mat.y -= FX_Mul(FX_SinIdx(obj_w->count), EFCT_UG00_OBJ_JUMP_DIS);
		CLACT_SetMatrix(obj_w->cl, &mat);		// 座標を設定
		obj_w->count += EFCT_UG00_OBJ_CNNUM;
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
	
		if(obj_w->count == EFCT_UG00_FADE_START){	//頂上でフェード開始
			return EFCT_SYSRET_FADE;
		}else{
			return EFCT_SYSRET_OK;
		}
	}
	
	return EFCT_SYSRET_END;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	影作成
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj01(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_SHADOW));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_SHADOW));
	
	obj_w = (EFCT_UG_SHADOW*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = 96*FX32_ONE;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 1, &obj_w->matrix,1, 1);
}
void deleteObj01(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	影を動かす
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj01(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	// 影を大きくして、最後まで大きくなったら終了
	if(obj_w->count < EFCT_UG00_SHADOW_COUNT){
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
		obj_w->count++;
		return EFCT_SYSRET_OK;	
	}

	return EFCT_SYSRET_END;	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	落ちていくオブジェクト
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェクトデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj02(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO));
	
	obj_w = (EFCT_UG_HERO*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFCT_UG01_OBJ_MAT_Y;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	落ちるオブジェ破棄関数
 *
 *@param	data
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj02(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	落ちるオブジェクト
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int  moveObj02(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO* obj_w = (EFCT_UG_HERO*)data->data;
	

	obj_w->matrix.y += EFCT_UG01_MOVE;
	CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// 座標を設定
	CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);

	if(obj_w->count == 0){
		if(obj_w->matrix.y >= EFCT_UG01_REST){
			obj_w->matrix.y = EFCT_UG01_OBJ_MAT_REST_Y;
			obj_w->count++;
		}
	}else{
		if(obj_w->matrix.y >= EFCT_UG01_END){
			obj_w->matrix.y = EFCT_UG01_END;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// 座標を設定
			return EFCT_SYSRET_END;
		}
	}
	
	return EFCT_SYSRET_OK;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクト初期化
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェクトデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj03(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO_EX));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO_EX));
	
	obj_w = (EFCT_UG_HERO_EX*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);

	//アニメーションSequence変更
	CLACT_AnmChg(obj_w->cl, 1);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	破棄関数
 *
 *@param	data
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj03(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	動作関数
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int  moveObj03(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	int	ret	= EFCT_SYSRET_OK;	// 戻り値

	switch(obj_w->seq){
	case 0:		// 回転を早くする
		obj_w->count += EFCT_UG02_ROTA_SA;
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		
		if(obj_w->count >= EFCT_UG02_ROTA_SE){
			obj_w->seq++;
		}
		break;
	
	case 1:
		if(obj_w->matrix.y > EFCT_UG02_REST){
			obj_w->matrix.y -= EFCT_UG02_MOVE;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// 座標を設定
			CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		}else{
			obj_w->matrix.y = EFCT_UG02_OBJ_MAT_REST_Y;
			obj_w->seq++;
		}	
		break;
	
	case 2:
		obj_w->matrix.y -= EFCT_UG02_MOVE;
		CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// 座標を設定
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		if((obj_w->matrix.y < EFCT_UG02_FADE_S)){
			ret = EFCT_SYSRET_FADE;
			obj_w->seq++;
		}
		break;

	case 3:
		if(obj_w->matrix.y > EFCT_UG02_END){
			obj_w->matrix.y -= EFCT_UG02_MOVE;
			CLACT_SetMatrix(obj_w->cl, &obj_w->matrix);		// 座標を設定
			CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		}else{
			obj_w->seq++;
		}
		break;

	case 4:
		ret = EFCT_SYSRET_END;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェクトの登録
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェクトデータ登録テーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj04(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_HERO_EX));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_HERO_EX));
	
	obj_w = (EFCT_UG_HERO_EX*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = EFECT_UGCOMMON_OBJ_MAT_Y;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 0, &obj_w->matrix, 0, 1);
	
	//アニメーションSequence変更
	CLACT_AnmChg(obj_w->cl, 1);
	obj_w->count = EFCT_UG03_ROTA_S;

	// 描画フラグオフ
	CLACT_SetDrawFlag(obj_w->cl, 0);
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェを破棄
 *
 *@param	data		オブジェデータ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void deleteObj04(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	主人公オブジェクトの動作関数
 *
 *@param	data	主人公オブジェクト
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj04(struct _EFCT_UG_OBJ* data)
{
	VecFx32	mat;	// セル描画座標
	EFCT_UG_HERO_EX* obj_w = (EFCT_UG_HERO_EX*)data->data;
	int	ret	= EFCT_SYSRET_OK;	// 戻り値
	
	switch(obj_w->seq){
	case 0:
		// 描画フラグオン
		CLACT_SetDrawFlag(obj_w->cl, 1);
		obj_w->seq++;
		break;
	case 1:
		if(obj_w->count <= EFCT_UG03_OBJ_END){
			mat = obj_w->matrix;
			mat.y -= FX_Mul(FX_SinIdx(obj_w->count), EFCT_UG03_OBJ_JUMP_DIS);
			CLACT_SetMatrix(obj_w->cl, &mat);		// 座標を設定
			obj_w->count += EFCT_UG03_OBJ_CNNUM;
			CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
	
		}else{
			obj_w->seq++;
		}
		break;
	case 2:		// 回転を遅くする
		obj_w->count -= EFCT_UG03_ROTA_SA;
		CLACT_AnmFrameChg(obj_w->cl, obj_w->count);
		
		if(obj_w->count <= EFCT_UG03_ROTA_SE){
			obj_w->seq++;
		}
		break;
	case 3:
		ret = EFCT_SYSRET_END;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	影作成
 *
 *@param	drawsys		描画データ
 *@param	data		オブジェデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void initObj05(EFCT_UG_DRAWSYS* drawsys, struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w;
	
	// オブジェクトの作成
	data->data = sys_AllocMemory(HEAPID_FIELD, sizeof(EFCT_UG_SHADOW));
	SDK_ASSERT(data->data);
	memset(data->data, 0, sizeof(EFCT_UG_SHADOW));
	
	obj_w = (EFCT_UG_SHADOW*)data->data;
	obj_w->matrix.x = EFECT_UGCOMMON_OBJ_MAT_X;
	obj_w->matrix.y = 96*FX32_ONE;
	
	// セルの登録
	obj_w->cl = addCellAct(drawsys, 1, &obj_w->matrix, 1, 1);

	//アニメーションSequence変更
	CLACT_AnmChg(obj_w->cl, 1);
}
void deleteObj05(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	if(data->data != NULL){
		// セルアクター削除
		CLACT_Delete(obj_w->cl);

		// オブジェクト破棄
		sys_FreeMemory(HEAPID_FIELD, data->data);
		data->data = NULL;
	}
}
//----------------------------------------------------------------------------
/**
 *
 *@brief	影を動かす
 *
 *@param	data
 *
 *@retval	EFCT_SYSRET_OK		正常
 *@retval	EFCT_SYSRET_FADE	フェード開始
 *@retval	EFCT_SYSRET_END		終了
 *
 *
 */
//-----------------------------------------------------------------------------
int moveObj05(struct _EFCT_UG_OBJ* data)
{
	EFCT_UG_SHADOW* obj_w = (EFCT_UG_SHADOW*)data->data;
	
	// 影を大きくして、最後まで大きくなったら終了
	if(obj_w->count < EFCT_UG03_SHADOW_COUNT){
		CLACT_AnmFrameChg(obj_w->cl, FX32_ONE);
		obj_w->count++;
		return EFCT_SYSRET_OK;	
	}

	return EFCT_SYSRET_END;	
}
