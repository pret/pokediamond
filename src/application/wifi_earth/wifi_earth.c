//============================================================================================
/**
 *	
 */
//============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "savedata/savedata_def.h"
#include "savedata/config.h"

#define __WIFIEARTH_H_GLOBAL__
#include "application/wifi_earth.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/palanm.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/wordset.h"

#include "msgdata/msg_earth.h"
#include "msgdata/msg_wifi_place_msg_world.h"
#include "savedata/wifihistory.h"
#include "wifi_earth_place.naix"
#include "wifi_earth.naix"

#include "application/wifi_country.h"

//============================================================================================
//	定数定義
//============================================================================================
//#define WIFI_ERATH_DEBUG

//地点登録最大数
#define WORLD_PLACE_NUM_MAX	(0x400)	//だいたい１０００国くらいとる

//メッセージバッファサイズ
#define EARTH_STRBUF_SIZE	(0x400)
#define EARTH_NAME_SIZE		(64)

//ＢＧ透明パレット
#define EARTH_NULL_PALETTE		(0x4753)

//ＢＧコントロール定数
#define EARTH_TEXT_PLANE		(GF_BGL_FRAME2_S)
#define EARTH_ICON_PLANE		(GF_BGL_FRAME2_M)
#define EARTH_BACK_S_PLANE		(GF_BGL_FRAME3_S)
#define EARTH_BACK_M_PLANE		(GF_BGL_FRAME3_M)
#define PALSIZE					(2*16)
#define DOTSIZE					(8)

// パレット転送位置
#define	EARTH_BACK_PAL			(0)	//４本分
#define	EARTH_SYSFONT_PAL		(4)
#define EARTH_ICONWIN_PAL		(5)
#define EARTH_TALKWIN_PAL		(6)
#define EARTH_MENUWIN_PAL		(7)

// 会話ウィンドウキャラ（window.h参照）
#define EARTH_TALKWINCHR_SIZ	(TALK_WIN_CGX_SIZ)
#define EARTH_TALKWINCHR_NUM	(512-EARTH_TALKWINCHR_SIZ)

// メニューウィンドウキャラ（window.h参照）
#define EARTH_MENUWINCHR_SIZ	(MENU_WIN_CGX_SIZ)
#define EARTH_MENUWINCHR_NUM	(EARTH_TALKWINCHR_NUM - EARTH_MENUWINCHR_SIZ)

// メッセージウィンドウ（fldbmp.h参照、ＣＧＸ以外フィールドと同じ：コメントは数値）
#define	EARTH_MSG_WIN_PX		(2)
#define	EARTH_MSG_WIN_PY		(19)
#define	EARTH_MSG_WIN_SX		(27)
#define	EARTH_MSG_WIN_SY		(4)
#define	EARTH_MSG_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_MSG_WIN_CGX		(EARTH_MENUWINCHR_NUM-(EARTH_MSG_WIN_SX*EARTH_MSG_WIN_SY))

// はい/いいえウィンドウ（fldbmp.h参照、ＣＧＸ以外フィールドと同じ：コメントは数値）
#define	EARTH_YESNO_WIN_PX		(25)
#define	EARTH_YESNO_WIN_PY		(13)
#define	EARTH_YESNO_WIN_SX		(6)
#define	EARTH_YESNO_WIN_SY		(4)
#define	EARTH_YESNO_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_YESNO_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_YESNO_WIN_SX*EARTH_YESNO_WIN_SY))

// メインメニューウィンドウ
#define	EARTH_MENU_WIN_PX		(19)
#define	EARTH_MENU_WIN_PY		(11)
#define	EARTH_MENU_WIN_SX		(12)
#define	EARTH_MENU_WIN_SY		(6)
#define	EARTH_MENU_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_MENU_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_MENU_WIN_SX*EARTH_MENU_WIN_SY))

// 国リストウィンドウ
#define	EARTH_PLACE_WIN_PX		(3)
#define	EARTH_PLACE_WIN_PY		(2)
#define	EARTH_PLACE_WIN_SX		(26)
#define	EARTH_PLACE_WIN_SY		(14)
#define	EARTH_PLACE_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_PLACE_WIN_CGX		(EARTH_MSG_WIN_CGX-(EARTH_PLACE_WIN_SX*EARTH_PLACE_WIN_SY))

// 情報ウィンドウ
#define	EARTH_INFO_WIN_PX		(2)
#define	EARTH_INFO_WIN_PY		(1)
#define	EARTH_INFO_WIN_SX		(27)
#define	EARTH_INFO_WIN_SY		(6)
#define	EARTH_INFO_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_INFO_WIN_CGX		(EARTH_YESNO_WIN_CGX-(EARTH_INFO_WIN_SX*EARTH_INFO_WIN_SY))

// アイコンウィンドウ
#define	EARTH_ICON_WIN_PX		(25)
#define	EARTH_ICON_WIN_PY		(21)
#define	EARTH_ICON_WIN_SX		(6)
#define	EARTH_ICON_WIN_SY		(2)
#define	EARTH_ICON_WIN_PAL		(EARTH_SYSFONT_PAL)
#define	EARTH_ICON_WIN_CGX		(EARTH_MENUWINCHR_NUM-(EARTH_ICON_WIN_SX*EARTH_ICON_WIN_SY))

//地球モデル初期化定義
#define INIT_EARTH_TRANS_XVAL	(0)
#define INIT_EARTH_TRANS_YVAL	(0)
#define INIT_EARTH_TRANS_ZVAL	(0)
#define INIT_EARTH_SCALE_XVAL	(FX32_ONE)
#define INIT_EARTH_SCALE_YVAL	(FX32_ONE)
#define INIT_EARTH_SCALE_ZVAL	(FX32_ONE)
#define INIT_EARTH_ROTATE_XVAL	(0x1980)	//東京をデフォルト位置にする
#define INIT_EARTH_ROTATE_YVAL	(0xcfe0)	//東京をデフォルト位置にする
#define INIT_EARTH_ROTATE_ZVAL	(0)

//カメラ初期化定義
#define INIT_CAMERA_TARGET_XVAL	(0)
#define INIT_CAMERA_TARGET_YVAL	(0)
#define INIT_CAMERA_TARGET_ZVAL	(0)
#define INIT_CAMERA_POS_XVAL	(0)
#define INIT_CAMERA_POS_YVAL	(0)
#define INIT_CAMERA_POS_ZVAL	(0x128000)
#define INIT_CAMERA_DISTANCE_NEAR	(0x050000)
#define INIT_CAMERA_DISTANCE_FAR	(0x128000)
#define INIT_CAMERA_PERSPWAY	(0x05c1)
#define INIT_CAMERA_CLIP_NEAR	(0)
#define INIT_CAMERA_CLIP_FAR	(FX32_ONE*100)
#define CAMERA_ANGLE_MIN		(-0x4000+0x200)
#define CAMERA_ANGLE_MAX		(0x4000-0x200)

//ライト初期化定義
#define USE_LIGHT_NUM			(0)
#define LIGHT_VECDEF			(FX32_ONE-1)
#define INIT_LIGHT_ANGLE_XVAL	(0)
#define INIT_LIGHT_ANGLE_YVAL	(0)
#define INIT_LIGHT_ANGLE_ZVAL	(-LIGHT_VECDEF)

//動作処理用定数
#define CAMERA_MOVE_SPEED_NEAR	(0x20)	//カメラ近距離時上下左右移動スピード	
#define CAMERA_MOVE_SPEED_FAR	(0x200)	//カメラ遠距離時上下左右移動スピード
#define CAMERA_INOUT_SPEED	(0x8000)	//カメラ遠近移動スピード
#define MARK_SCALE_INCDEC	(0x80)		//地点マーク遠近移動中拡縮比率
#define EARTH_LIMIT_ROTATE_XMIN	(0x1300)	//日本拡大地図の縦回転リミット下限（沖縄）
#define EARTH_LIMIT_ROTATE_XMAX	(0x2020)	//日本拡大地図の縦回転リミット上限（北海道稚内）
#define EARTH_LIMIT_ROTATE_YMIN	(0xcc80)	//日本拡大地図の横回転リミット下限（北海道釧路）
#define EARTH_LIMIT_ROTATE_YMAX	(0xd820)	//日本拡大地図の横回転リミット上限（沖縄）

//メイン関数シーケンスナンバー定義
enum{
	EARTHDEMO_SEQ_MODELLOAD = 0,					//モデルデータロード
	EARTHDEMO_SEQ_DISPON,							//描画ＯＮ
	EARTHDEMO_SEQ_WELCOME_MSG,						//「ようこそ」
	EARTHDEMO_SEQ_MAINMENU,							//メインメニュー設定
	EARTHDEMO_SEQ_MAINMENU_SELECT,					//メインメニュー選択モード
	EARTHDEMO_SEQ_REGISTRATIONMENU,					//登録メニュー設定
	EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT,			//登録メニュー選択モード
	EARTHDEMO_SEQ_REGISTRATIONLIST_NATION,			//国別登録リスト設定
	EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT,	//国別登録リスト選択モード
	EARTHDEMO_SEQ_REGISTRATIONLIST_AREA,			//地域別登録リスト設定
	EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT,		//地域別登録リスト選択モード
	EARTHDEMO_SEQ_FINAL_REGISTRATION,				//登録最終確認設定
	EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO,			//登録最終確認
	EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT,		//登録最終確認選択モード
	EARTHDEMO_SEQ_EARTH_DISPON,						//３Ｄ地球儀モードＯＮ
	EARTHDEMO_SEQ_MOVE_EARTH,						//メイン動作
	EARTHDEMO_SEQ_MOVE_CAMERA,						//カメラ遠近移動
	EARTHDEMO_SEQ_END,								//終了処理開始
	EARTHDEMO_SEQ_EXIT,								//終了
};

//メッセージ関数シーケンスナンバー定義
enum{
	MSGSET = 0,
	MSGDRAW,
	MSGWAIT,
};

//メッセージ関数動作指定定義
enum {
	A_BUTTON_WAIT = 0,
	A_BUTTON_NOWAIT,
};

//登録メニューＩＤナンバー定義
enum{
	MENU_WORLD = 0,
	MENU_REGISTRATION,
	MENU_END,
};

//地球回転モード定義
enum {
	JAPAN_MODE = 0,
	GLOBAL_MODE,
};

//カメラ距離フラグ定義
enum {
	CAMERA_FAR = 0,
	CAMERA_NEAR,
};

//３Ｄ描画フラグ定義
enum {
	DRAW3D_DISABLE = 0,
	DRAW3D_ENABLE,
	DRAW3D_BANISH,
};

//地点データ表示カラー定義（モデル選択によって色替え：wifihistory定義に沿う順番にする）
enum {
	MARK_NULL = 0,	//未通信場所
	MARK_BLUE,		//本日はじめて通信した
	MARK_YELLOW,	//通信済
	MARK_RED,		//自分の登録場所
	MARK_GREEN,		//カーソル
};

//============================================================================================
//	構造体定義
//============================================================================================
//データ設定構造体（国バイナリデータ）
typedef struct EARTH_DATA_NATION_tag
{
	u16 flag;
	s16 x;
	s16 y;
}EARTH_DATA_NATION;

//データ設定構造体（地域バイナリデータ）
typedef struct EARTH_DATA_AREA_tag
{
	s16 x;
	s16 y;
}EARTH_DATA_AREA;

//データ構造体（国地域テーブルデータ）
typedef struct EARTH_AREATABLE_tag
{
	u16		nationID;
	u16		msg_arcID;
	const char* place_dataID;
}EARTH_AREATABLE;

//リストデータ構造体（バイナリデータ→実際に使用するリスト用データに変換）
typedef struct EARTH_DEMO_LIST_DATA_tag
{
	s16 x;
	s16 y;
	MtxFx33 rotate;	//相対回転行列をあらかじめ計算して保存
	u16	col;
	u16	nationID;
	u16	areaID;
}EARTH_DEMO_LIST_DATA;

//リストデータ構造体（バイナリデータ→実際に使用するリスト用データに変換）
typedef struct EARTH_DEMO_LIST_tag
{
	u32	listcount;
	EARTH_DEMO_LIST_DATA	place[WORLD_PLACE_NUM_MAX];
}EARTH_DEMO_LIST;

//ワーク構造体
typedef struct EARTH_DEMO_WORK_tag
{
	//ヒープ設定ワーク
	int	heapID;

	//セーブデータポインタ
	WIFI_HISTORY*	wifi_sv;
	CONFIG*			config;	

	//地点リストワーク
	EARTH_DEMO_LIST	placelist;

	//ＢＧシステムポインタ
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;
	GF_BGL_BMPWIN		listwin;
	GF_BGL_BMPWIN		iconwin;
	GF_BGL_BMPWIN		infowin;
	BMPLIST_WORK*		bmplist;
	BMP_MENULIST_DATA*	bmplistdata;
	BMPMENU_WORK*		yesnowin;

	//メッセージマネージャポインタ
	MSGDATA_MANAGER*	msg_man;
	int		msgseq;
	int		msgID;
	STRBUF* msgstr;
	WORDSET*			wordset;

	//モデルロードワーク
	NNSG3dRenderObj			renderobj;			//終了時要ヒープ開放
	NNSG3dResMdl*			resmodel;
	NNSG3dResFileHeader* 	resfileheader;

	NNSG3dRenderObj			mark_renderobj[5];	//終了時要ヒープ開放
	NNSG3dResMdl*			mark_resmodel[5];
	NNSG3dResFileHeader* 	mark_resfileheader[5];

	//モデル設定ワーク
	VecFx32 trans;
	VecFx32 scale;
	VecFx32	rotate;

	VecFx32	mark_scale;

	//カメラ設定ワーク
	GF_CAMERA_PTR camera_p;
	CAMERA_ANGLE camera_angle;
	u16 camera_status;

	//ライト設定ワーク
	VecFx32	light_vec;

	//動作処理ワーク
	int		Draw3Dsw;
	BOOL	fade_end_flag;
	BOOL	Japan_ROM_mode;
	u16		earth_mode;
	u16		rotate_speed;

	//タッチパネル検出保存ワーク
	int tp_result;
	int tp_seq;
	int tp_x;
	int tp_y;
	int tp_lenx;
	int tp_leny;
	int tp_count;

	//地点登録テンポラリ
	int		my_nation;
	int		my_area;
	int		my_nation_tmp;
	int		my_area_tmp;
	BOOL	my_worldopen_flag;

	int		info_mode;

#ifdef WIFI_ERATH_DEBUG
	int debug_work[8];
#endif	

}EARTH_DEMO_WORK;

//ビットマップリスト構造体
typedef struct EARTH_BMPLIST_tag
{
	u32 msgID;
	u32 retID;
}EARTH_BMPLIST;

//============================================================================================
//	グローバル関数定義
//============================================================================================
void	WIFI_RegistratonInit(SAVEDATA* savedata);
BOOL	WIFI_NationAreaNameGet(int nationID,int areaID,
								STRBUF* nation_str,STRBUF* area_str,int heapID);
BOOL	WIFI_LocalAreaExistCheck(int nationID);

//============================================================================================
//	ローカル関数定義
//============================================================================================
PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq);
PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq);
PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq);

static void Earth_VramBankSet(void);
static void Earth_BGsysSet(void);
static void Earth_BGdataLoad( EARTH_DEMO_WORK * wk );
static void Earth_BGdataRelease( EARTH_DEMO_WORK * wk );

static void EarthListLoad( EARTH_DEMO_WORK * wk );
static void EarthListSet( EARTH_DEMO_WORK * wk,u32 index, s16 x,s16 y,u16 nationID,u16 areaID );
static void EarthList_NationAreaListSet( EARTH_DEMO_WORK * wk );
static int	EarthAreaTableGet(int nationID);

static void Earth_TouchPanel( EARTH_DEMO_WORK * wk );
static void Earth_TouchPanelParamGet
	( int prevx,int prevy,int* dirx_p,int* lenx_p,int* diry_p,int* leny_p );

static BOOL Earth_MsgPrint( EARTH_DEMO_WORK * wk,u32 msgID,int button_mode );
static void Earth_BmpListAdd( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win,const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,const EARTH_BMPLIST* list);
static void Earth_BmpListAddGmmAll( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win, const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,u32 listarcID);
static void Earth_BmpListDel( EARTH_DEMO_WORK* wk );

static void Earth_MyPlaceInfoWinSet( EARTH_DEMO_WORK* wk );
static void Earth_MyPlaceInfoWinSet2( EARTH_DEMO_WORK* wk, int nation, int area );
static void Earth_MyPlaceInfoWinRelease( EARTH_DEMO_WORK* wk );
static void Earth_PosInfoPut( EARTH_DEMO_WORK* wk );

static void Earth_ModelLoad( EARTH_DEMO_WORK * wk );
static void Earth_ModelRelease( EARTH_DEMO_WORK * wk );
static void EarthDataInit( EARTH_DEMO_WORK * wk );
static void EarthCameraInit( EARTH_DEMO_WORK * wk );
static void EarthLightInit( EARTH_DEMO_WORK * wk );

static BOOL Earth3D_Control( EARTH_DEMO_WORK * wk,int keytrg,int keycont );
static BOOL Earth3D_CameraMoveNearFar( EARTH_DEMO_WORK * wk );
static void Earth3D_Draw( EARTH_DEMO_WORK * wk );
static void EarthVecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src );
static void EarthVecFx32_to_MtxFx33_place( MtxFx33* dst, VecFx32* src );

#ifdef WIFI_ERATH_DEBUG
static void EarthDebugWinRotateInfoWrite( EARTH_DEMO_WORK * wk );
static void EarthDebugWinNameInfoWrite( EARTH_DEMO_WORK * wk );
static void EarthDebugNationMarkSet( EARTH_DEMO_WORK * wk );
static void EarthDebugAreaMarkSet( EARTH_DEMO_WORK * wk );
#endif	

//============================================================================================
//	外部関数定義
//============================================================================================
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);
extern u8 MsgSpeedGet(void);

#if	0	//呼び出し側へ移動
//============================================================================================
//	ＰＲＯＣ定義データ
//============================================================================================
const PROC_DATA Earth_Demo_proc_data = {
	Earth_Demo_Init,
	Earth_Demo_Main,
	Earth_Demo_Exit,
	NO_OVERLAY_ID,
};
#endif


//============================================================================================
//	ＢＧ定義データ
//============================================================================================
static const GF_BGL_BGCNT_HEADER Earth_Demo_BGtxt_header = {
	0,0,					//初期表示ＸＹ設定
	0x800,0,				//スクリーンバッファサイズ(0 = 使用しない)＆オフセット
	GF_BGL_SCRSIZ_256x256,	//スクリーンサイズ
	GX_BG_COLORMODE_16,		//カラーモード
	GX_BG_SCRBASE_0x7000, 	//スクリーンベースブロック
	GX_BG_CHARBASE_0x00000,	//キャラクタベースブロック 
	GX_BG_EXTPLTT_01,		//拡張パレット選択(使用しない設定のときは無視される)
	0,						//表示プライオリティー
	0,						//エリアオーバーフラグ
	0,						//
	FALSE					//モザイク設定
};

static const GF_BGL_BGCNT_HEADER Earth_Demo_Back_header = {
	0,0,					//初期表示ＸＹ設定
	0x800,0,				//スクリーンバッファサイズ(0 = 使用しない)＆オフセット
	GF_BGL_SCRSIZ_256x256,	//スクリーンサイズ
	GX_BG_COLORMODE_16,		//カラーモード
	GX_BG_SCRBASE_0x7800, 	//スクリーンベースブロック
	GX_BG_CHARBASE_0x04000,	//キャラクタベースブロック 
	GX_BG_EXTPLTT_01,		//拡張パレット選択(使用しない設定のときは無視される)
	3,						//表示プライオリティー
	0,						//エリアオーバーフラグ
	0,						//
	FALSE					//モザイク設定
};

static const BMPWIN_DAT EarthMsgWinData =
{
	EARTH_TEXT_PLANE,	//ウインドウ使用フレーム
	EARTH_MSG_WIN_PX,EARTH_MSG_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_MSG_WIN_SX,EARTH_MSG_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_MSG_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_MSG_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const BMPWIN_DAT EarthYesNoWinData =
{
	EARTH_TEXT_PLANE,	//ウインドウ使用フレーム
	EARTH_YESNO_WIN_PX,EARTH_YESNO_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_YESNO_WIN_SX,EARTH_YESNO_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_YESNO_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_YESNO_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const BMPWIN_DAT EarthMenuWinData =
{
	EARTH_TEXT_PLANE,	//ウインドウ使用フレーム
	EARTH_MENU_WIN_PX,EARTH_MENU_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_MENU_WIN_SX,EARTH_MENU_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_MENU_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_MENU_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const BMPWIN_DAT EarthPlaceListWinData =
{
	EARTH_TEXT_PLANE,	//ウインドウ使用フレーム
	EARTH_PLACE_WIN_PX,EARTH_PLACE_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_PLACE_WIN_SX,EARTH_PLACE_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_PLACE_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_PLACE_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const BMPWIN_DAT EarthInfoWinData =
{
	EARTH_TEXT_PLANE,	//ウインドウ使用フレーム
	EARTH_INFO_WIN_PX,EARTH_INFO_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_INFO_WIN_SX,EARTH_INFO_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_INFO_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_INFO_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const BMPWIN_DAT EarthIconWinData =
{
	EARTH_ICON_PLANE,	//ウインドウ使用フレーム
	EARTH_ICON_WIN_PX,EARTH_ICON_WIN_PY,//ウインドウ領域の左上XY座標（キャラ単位指定）
	EARTH_ICON_WIN_SX,EARTH_ICON_WIN_SY,//ウインドウ領域のXYサイズ（キャラ単位指定）
	EARTH_ICON_WIN_PAL,	//ウインドウ領域のパレットナンバー 
	EARTH_ICON_WIN_CGX,	//ウインドウキャラ領域の開始キャラクタナンバー
};

static const EARTH_BMPLIST MenuList[] =
{
	{mes_earth_02_05,MENU_WORLD},
	{mes_earth_02_06,MENU_REGISTRATION},
	{mes_earth_02_07,MENU_END},
};

static const BMPLIST_HEADER MenuListHeader = {
	/* 表示文字データポインタ(プログラム設定) */NULL,/* カーソル移動ごとのコールバック関数 */NULL,
	/* 一列表示ごとのコールバック関数 */NULL,/* 対応ビットマップ(プログラム設定) */NULL,
	/* リスト項目数 */NELEMS(MenuList),/* 表示最大項目数 */NELEMS(MenuList),		
	/* ラベル表示Ｘ座標 */0,/* 項目表示Ｘ座標 */12,/* カーソル表示Ｘ座標 */0,/* 表示Ｙ座標 */0,
	/* 文字色 */FBMP_COL_BLACK,/* 背景色 */FBMP_COL_WHITE,/* 文字影色 */FBMP_COL_BLK_SDW,		
	/* 文字間隔Ｘ */0,/* 文字間隔Ｙ */16,/* ページスキップタイプ */BMPLIST_NO_SKIP,		
	/* 文字指定 */FONT_SYSTEM,/*ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)*/0,						
};

static const BMPLIST_HEADER PlaceListHeader = {
	/* 表示文字データポインタ(プログラム設定) */NULL,/* カーソル移動ごとのコールバック関数 */NULL,
	/* 一列表示ごとのコールバック関数 */NULL,/* 対応ビットマップ(プログラム設定) */NULL,
	/* リスト項目数(プログラム設定) */0,/* 表示最大項目数 */7,		
	/* ラベル表示Ｘ座標 */0,/* 項目表示Ｘ座標 */12,/* カーソル表示Ｘ座標 */0,/* 表示Ｙ座標 */0,
	/* 文字色 */FBMP_COL_BLACK,/* 背景色 */FBMP_COL_WHITE,/* 文字影色 */FBMP_COL_BLK_SDW,		
	/* 文字間隔Ｘ */0,/* 文字間隔Ｙ */16,/* ページスキップタイプ */BMPLIST_LRKEY_SKIP,		
	/* 文字指定 */FONT_SYSTEM,/*ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)*/0,						
};

//============================================================================================
//
//	メイン関数
//
//============================================================================================
//============================================================================================
//	初期化プロセス
//============================================================================================
PROC_RESULT Earth_Demo_Init(PROC * proc, int * seq)
{
	EARTH_DEMO_WORK * wk;
	int	heapID = HEAPID_WIFIEARTH;

	//ＶＨ関数停止
	sys_VBlankFuncChange( NULL, NULL );
	sys_HBlankIntrSet( NULL,NULL );

	//ＢＧ表示停止
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	//ヒープエリア作成
	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x080000 );

	//ワークエリア取得
	wk = PROC_AllocWork( proc, sizeof(EARTH_DEMO_WORK), heapID );
	memset( wk, 0, sizeof(EARTH_DEMO_WORK) );
	wk->heapID = heapID;

	//日本語版かどうかの判別フラグ
	if( CasetteLanguage == LANG_JAPAN ){
		// 日本語バージョンでは日本しか登録できない
		wk->Japan_ROM_mode = TRUE;
	} else {
		// 日本語バージョン以外は最初から地球儀が全部見える
		wk->Japan_ROM_mode = FALSE;
	}
#ifdef PM_DEBUG
	// Ｌボタンをおしていると入力情報をクリアした上で世界から入力できる
	if(sys.cont & PAD_BUTTON_L){
		SAVEDATA* sv = PROC_GetParentWork( proc );
		WIFI_RegistratonInit( sv );
		wk->Japan_ROM_mode = FALSE;
	}
#endif
	//セーブデータポインタ作成
	{
		SAVEDATA* sv = PROC_GetParentWork( proc );

		wk->wifi_sv = SaveData_GetWifiHistory( sv );
		wk->my_nation = WIFIHISTORY_GetMyNation( wk->wifi_sv );
		wk->my_area = WIFIHISTORY_GetMyArea( wk->wifi_sv );
		wk->my_worldopen_flag = WIFIHISTORY_GetWorldFlag( wk->wifi_sv );
		wk->config	= SaveData_GetConfig( sv );	
	}

	//ＶＲＡＭ設定
	Earth_VramBankSet();

	//ＢＧライブラリ設定
	Earth_BGsysSet();
	simple_3DBGInit( wk->heapID );
	wk->bgl = GF_BGL_BglIniAlloc( wk->heapID );
	GF_Disp_DispOn();
	
	//メッセージ表示システム初期化
	MSG_PrintInit();
	wk->wordset = WORDSET_CreateEx( WORDSET_DEFAULT_SETNUM, EARTH_NAME_SIZE, wk->heapID );

	//カメラライブラリ設定
	wk->camera_p = GFC_AllocCamera( wk->heapID );

	//３Ｄ描画スイッチ設定
	wk->Draw3Dsw = DRAW3D_DISABLE;
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();

	//キーシステム設定
	sys_KeyRepeatSpeedSet( 4, 8 );

	//地域リストデータ作成
	EarthListLoad(wk);

	return	PROC_RES_FINISH;
}

//============================================================================================
//	メインプロセス
//============================================================================================
PROC_RESULT Earth_Demo_Main(PROC * proc, int * seq)
{
	EARTH_DEMO_WORK * wk  = PROC_GetWork( proc );
	PROC_RESULT sys_result = PROC_RES_CONTINUE;

	switch(*seq){
	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MODELLOAD://モデルデータロード

		//メッセージデータ読み込み
		wk->msg_man = MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_earth_dat,wk->heapID );

		Earth_ModelLoad(wk);	//モデルロードメイン
		Earth_BGdataLoad(wk);	//ＢＧデータロード

		//輝度変更セット（ＩＮ）
		wk->fade_end_flag = FALSE;
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEIN,WIPE_TYPE_FADEIN,
						WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,wk->heapID);

		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_ON );
		GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_ON );

		*seq = EARTHDEMO_SEQ_DISPON;
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_DISPON:	//描画ＯＮ

		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち
			*seq = EARTHDEMO_SEQ_WELCOME_MSG;
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_WELCOME_MSG:	//「ようこそ」

		if(Earth_MsgPrint(wk,mes_earth_01_01,A_BUTTON_NOWAIT) == TRUE){
			//住んでいる場所入力済？
			if(wk->my_nation == 0){
				//未登録
				*seq = EARTHDEMO_SEQ_MAINMENU;	//メインメニュー設定へ
			}else{
				//登録済
				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//３Ｄ地球儀モードＯＮへ
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MAINMENU:	//メインメニュー設定

		if(Earth_MsgPrint(wk,mes_earth_01_02,A_BUTTON_NOWAIT) == TRUE){
			//選択リスト表示
			Earth_BmpListAdd(wk,&wk->listwin,&EarthMenuWinData,&MenuListHeader,MenuList);
			*seq = EARTHDEMO_SEQ_MAINMENU_SELECT;	//選択モードへ
		}
		break;

	case EARTHDEMO_SEQ_MAINMENU_SELECT:	//メインメニュー選択モード
		{
			int list_result = BmpListMain(wk->bmplist);

			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//選択リスト削除処理
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
			case MENU_WORLD:	//「いちらん」
				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//３Ｄ地球儀モードＯＮへ
				break;
			case MENU_REGISTRATION:	//「とうろく」
				*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//登録メニュー設定へ
				break;
			case BMPLIST_CANCEL:
			case MENU_END:	//「やめる」
				*seq = EARTHDEMO_SEQ_END;	//終了処理へ
				break;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_REGISTRATIONMENU:	//登録メニュー設定

		if(Earth_MsgPrint(wk,mes_earth_01_03,A_BUTTON_NOWAIT) == TRUE){
			//はい/いいえウィンドウ表示
			wk->yesnowin = BmpYesNoSelectInit(wk->bgl,&EarthYesNoWinData,
											EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,
											wk->heapID);
			*seq = EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT;	//選択モードへ
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONMENU_SELECT:	//登録メニュー選択モード
		{
			u32 list_result = BmpYesNoSelectMain(wk->yesnowin,wk->heapID);

			switch(list_result){
			case 0:		//「はい」
				if(wk->Japan_ROM_mode == TRUE){
					wk->my_nation_tmp = country103;	//日本語版限定処理（国入力スキップ）
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA;	//地域別登録リスト選択へ
				}else{
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION;//国別登録リスト選択へ
				}
				break;
			case BMPMENU_CANCEL:	//「いいえ」
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_NATION:	//国別登録リスト設定

		if(Earth_MsgPrint(wk,mes_earth_01_04,A_BUTTON_NOWAIT) == TRUE){
		
			wk->my_nation_tmp = 0;//登録情報テンポラリ初期化
			Earth_BmpListAddGmmAll(wk,&wk->listwin,&EarthPlaceListWinData,
								&PlaceListHeader,NARC_msg_wifi_place_msg_world_dat);

			*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT;	//国別登録リスト選択へ
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_NATION_SELECT:	//国別登録リスト選択モード
		{
			int list_result = BmpListMain(wk->bmplist);
#ifdef WIFI_ERATH_DEBUG
			EarthDebugNationMarkSet(wk);
#endif
			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//選択リスト削除処理
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
				{
					wk->my_nation_tmp = list_result;	//国登録

					if(WIFI_LocalAreaExistCheck(wk->my_nation_tmp) == TRUE){
						//地域が存在する場合
						*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA;	//地域別登録リスト選択へ
					}else{
						//地域が存在しない場所の登録
						wk->my_area_tmp = 0;				//地域登録（なし）
						*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION;	//国地域登録最終確認へ
					}
				}
				break;
			case BMPLIST_CANCEL:	//「いいえ」キャンセル
				//*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//登録メニューへ
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_AREA:	//地域別登録リスト設定

		if(Earth_MsgPrint(wk,mes_earth_01_05,A_BUTTON_NOWAIT) == TRUE){
			wk->my_area_tmp = 0;//登録情報テンポラリ初期化
			Earth_BmpListAddGmmAll(wk,&wk->listwin,&EarthPlaceListWinData,&PlaceListHeader,
						WIFI_COUNTRY_CountryCodeToPlaceMsgDataID(wk->my_nation_tmp));

			*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT;	//地域別登録リスト選択へ
		}
		break;

	case EARTHDEMO_SEQ_REGISTRATIONLIST_AREA_SELECT:	//地域別登録リスト選択モード
		{
			int list_result = BmpListMain(wk->bmplist);
#ifdef WIFI_ERATH_DEBUG
			EarthDebugAreaMarkSet(wk);
#endif
			if(list_result == BMPLIST_NULL){
				break;
			}
			Earth_BmpListDel(wk);//選択リスト削除処理
			Snd_SePlay( SEQ_SE_DP_SELECT );

			switch(list_result){
			default:
				wk->my_area_tmp = list_result;			//地域登録
				*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION;	//国地域登録最終確認へ
				break;
			case BMPLIST_CANCEL://キャンセル
				if(wk->Japan_ROM_mode == TRUE){
					//*seq = EARTHDEMO_SEQ_REGISTRATIONMENU;	//登録メニューへ(日本版の場合)
					*seq = EARTHDEMO_SEQ_MAINMENU;
				} else {
					*seq = EARTHDEMO_SEQ_REGISTRATIONLIST_NATION;	//国別登録リスト設定へ
				}
			}
		}
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION:	//登録最終確認設定
		Earth_MyPlaceInfoWinSet2( wk, wk->my_nation_tmp, wk->my_area_tmp );//登録地名表示
		*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO;	//登録最終確認へ
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION_YESNO:	//登録最終確認

		if(Earth_MsgPrint(wk,mes_earth_01_06,A_BUTTON_NOWAIT) == TRUE){
			//はい/いいえウィンドウ表示
			wk->yesnowin = BmpYesNoSelectInit(wk->bgl,&EarthYesNoWinData,
											EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,
											wk->heapID);
			*seq = EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT;	//登録最終確認選択モードへ
		}
		break;

	case EARTHDEMO_SEQ_FINAL_REGISTRATION_SELECT:	//登録最終確認選択モード
		{
			u32 list_result = BmpYesNoSelectMain(wk->yesnowin,wk->heapID);

			switch(list_result){
			case 0:		//「はい」
				Earth_MyPlaceInfoWinRelease( wk );
				//登録データセーブ
				WIFIHISTORY_SetMyNationArea(wk->wifi_sv,wk->my_nation_tmp,wk->my_area_tmp);
				wk->my_nation = wk->my_nation_tmp;
				wk->my_area = wk->my_area_tmp;

				*seq = EARTHDEMO_SEQ_EARTH_DISPON;	//３Ｄ地球儀モードＯＮへ
				break;
			case BMPMENU_CANCEL:	//「いいえ」
				Earth_MyPlaceInfoWinRelease( wk );
				*seq = EARTHDEMO_SEQ_MAINMENU;
				break;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_EARTH_DISPON:	//３Ｄ地球儀モードＯＮ
		//日本語版？
		if((wk->Japan_ROM_mode == TRUE)&&(wk->my_worldopen_flag == FALSE)){
			//日本語版で海外のモードが開いていない場合は日本限定マップ
			wk->earth_mode = JAPAN_MODE;
		}else{
			//その他、世界マップ
			wk->earth_mode = GLOBAL_MODE;
		}
		EarthDataInit(wk);					//地球データ初期化
		EarthList_NationAreaListSet(wk);	//登録地域データ設定
		EarthCameraInit(wk);				//カメラ初期化
		EarthLightInit(wk);					//ライト初期化

		//メッセージ画面クリア
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		//「やめる」アイコンＯＮ
		BmpMenuWinWrite(&wk->iconwin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

		//住んでいる場所入力済？
		if(wk->my_nation != 0){
			Earth_MyPlaceInfoWinSet( wk );//登録地名表示
		}
		Earth_PosInfoPut( wk );
		wk->info_mode = 0;

		wk->Draw3Dsw = DRAW3D_ENABLE;//３Ｄ描画スイッチ設定ＯＮ

		*seq = EARTHDEMO_SEQ_MOVE_EARTH;
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_MOVE_EARTH:	//地球回転
		{
			u16 camera_status_backup = wk->camera_status;

			//タッチパネルコントロール
			Earth_TouchPanel(wk);

			//終了判定
			if((sys.trg & PAD_BUTTON_B)||(wk->tp_result & PAD_BUTTON_B)){
				//「やめる」アイコンＯＦＦ
				BmpMenuWinClear(&wk->iconwin,WINDOW_TRANS_ON);
				Snd_SePlay( SEQ_SE_DP_DECIDE );

				GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);

				//住んでいる場所入力済？
				if(wk->my_nation == 0){
					//メニュー画面へ
					wk->Draw3Dsw = DRAW3D_BANISH;//３Ｄ画面消去→スイッチ設定ＯＦＦ
					*seq = EARTHDEMO_SEQ_MAINMENU;
				}else{
					Earth_MyPlaceInfoWinRelease( wk );
					*seq = EARTHDEMO_SEQ_END;//終了
				}
			}else{
				if( (sys.trg & PAD_BUTTON_X)&&(wk->info_mode == 0) ){
					wk->info_mode = 1;
					Earth_PosInfoPut( wk );
					if( wk->info_mode == 1 ){
						Snd_SePlay( SEQ_SE_DP_DECIDE );
					}
					break;
				}
				if((sys.trg & (PAD_BUTTON_X|PAD_BUTTON_A|PAD_BUTTON_B))&&(wk->info_mode == 1)){
					wk->info_mode = 0;
					Earth_PosInfoPut( wk );
					break;
				}
				{
					BOOL move_flag;
					//地球回転コントロール
					move_flag = Earth3D_Control(wk, sys.trg, sys.cont);

					if( (move_flag == TRUE)&&(wk->info_mode == 1) ){
						wk->info_mode = 0;
						Earth_PosInfoPut( wk );
					}
				}
				//カメラ遠近移動判定
				if(camera_status_backup != wk->camera_status){
					*seq = EARTHDEMO_SEQ_MOVE_CAMERA;
					Snd_SePlay( SEQ_SE_DP_DECIDE );
				}
			}
		}
#ifdef WIFI_ERATH_DEBUG
		EarthDebugWinRotateInfoWrite(wk);//デバッグ情報表示
#endif
		break;

	case EARTHDEMO_SEQ_MOVE_CAMERA:	//カメラ距離移動
		{
			BOOL end_flag = Earth3D_CameraMoveNearFar(wk);

			if(end_flag == TRUE){
				*seq = EARTHDEMO_SEQ_MOVE_EARTH;
			}
		}
		break;

	//-----------------------------------------------------------
	case EARTHDEMO_SEQ_END:		//終了処理
		wk->fade_end_flag = FALSE;//輝度変更待ちフラグリセット
		WIPE_SYS_Start(	WIPE_PATTERN_WMS,WIPE_TYPE_FADEOUT,WIPE_TYPE_FADEOUT,
						WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,wk->heapID);
		*seq = EARTHDEMO_SEQ_EXIT;
		break;

	case EARTHDEMO_SEQ_EXIT:	//終了

		if(WIPE_SYS_EndCheck() == TRUE){	//輝度変更待ち

			wk->Draw3Dsw = DRAW3D_ENABLE;//３Ｄ描画スイッチ設定ＯＦＦ
			//ＢＧデータ破棄
			Earth_BGdataRelease(wk);
			//モデルデータ破棄
			Earth_ModelRelease(wk);
			//メッセージデータ破棄
			MSGMAN_Delete(wk->msg_man);

			(*seq) = 0;
			sys_result = PROC_RES_FINISH;	//終了フラグ
		}
		break;
	}
	Earth3D_Draw(wk);		//３Ｄ描画エンジン

	return	sys_result;
}

//============================================================================================
//	終了プロセス
//============================================================================================
PROC_RESULT Earth_Demo_Exit(PROC * proc, int * seq)
	
{
	EARTH_DEMO_WORK * wk  = PROC_GetWork( proc );
	int	heapID = wk->heapID;

	//ＢＧ表示停止
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2 , VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3 , VISIBLE_OFF );

	//各種内部確保ワーク開放
	GFC_FreeCamera(wk->camera_p);
	WORDSET_Delete( wk->wordset );
	simple_3DBGExit();
	sys_FreeMemoryEz(wk->bgl);

	//ＶＨ関数停止
	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	//ワーク開放
	PROC_FreeWork( proc );

	//ヒープ開放
	sys_DeleteHeap( heapID );

	sys.disp3DSW = DISP_3D_TO_MAIN;

	return	PROC_RES_FINISH;
}

//============================================================================================
//
//	ローカル関数（メインシステム関連）
//
//============================================================================================
//----------------------------------
//ＶＲＡＭ設定
//----------------------------------
static void Earth_VramBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------
//ＢＧシステム設定
//----------------------------------
static void Earth_BGsysSet(void )
{
	GF_BGL_SYS_HEADER BGsys_data = {GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D};

	GF_BGL_InitBG(&BGsys_data);
}


//============================================================================================
//
//	ローカル関数（地域データ取得関連）
//
//============================================================================================
//----------------------------------
//地点リストロード
//----------------------------------
static void EarthListLoad( EARTH_DEMO_WORK * wk )
{
	//地点リスト総数初期化
	wk->placelist.listcount = 0;

	{//地点マーク回転初期化（国データバイナリデータロード）
		void* filep;
		EARTH_DATA_NATION* listp;
		u32	size;
		int	i,listcount;

		filep = ArcUtil_LoadEx( ARC_WIFI_EARCH_PLACE, NARC_wifi_earth_place_place_pos_wrd_dat, 
								FALSE, wk->heapID, ALLOC_TOP, &size );

		listp = (EARTH_DATA_NATION*)filep;	//ファイル読み込み用に変換
		listcount = size/6;				//地点数取得（データ長：１地点につき６バイト）

		listp++;	//1originのため読み飛ばし
		for(i=1;i<listcount;i++){
			if(listp->flag != 2){	//2の場合は地域リストが存在する
				EarthListSet(wk,wk->placelist.listcount,listp->x,listp->y,i,0);
				wk->placelist.listcount++;
			}
			listp++;
		}
		sys_FreeMemoryEz(filep);
	}
	{//地点マーク回転初期化（地域データバイナリデータロード）
		void* filep;
		EARTH_DATA_AREA* listp;
		u32	size, data_id;
		int	i,datLen,index,listcount;

		index = 1;	//1orgin
		datLen = WIFI_COUNTRY_GetDataLen();

		while(index < datLen){

			data_id = WIFI_COUNTRY_DataIndexToPlaceDataID( index );
			filep = ArcUtil_LoadEx( ARC_WIFI_EARCH_PLACE, data_id, FALSE, 
									wk->heapID, ALLOC_TOP, &size );

			listp = (EARTH_DATA_AREA*)filep;	//ファイル読み込み用に変換
			listcount = size/4;		//地点数取得（データ長：１地点につき４バイト）

			listp++;	//1originのため読み飛ばし
			for(i=1;i<listcount;i++){//1orgin
				EarthListSet(wk,wk->placelist.listcount,listp->x,listp->y,
								WIFI_COUNTRY_DataIndexToCountryCode(index),i);
				wk->placelist.listcount++;
				listp++;
			}
			sys_FreeMemoryEz(filep);
			index++;
		}
	}
}

//----------------------------------
//リスト登録
//----------------------------------
static void EarthListSet( EARTH_DEMO_WORK * wk,u32 index,s16 x,s16 y,u16 nationID,u16 areaID )
{
	MtxFx33 rotMtx = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
	VecFx32 rotVec;

	wk->placelist.place[index].x = x;	//Ｘ回転オフセット取得
	wk->placelist.place[index].y = y;	//Ｙ回転オフセット取得
	
	rotVec.x = x;
	rotVec.y = y;
	rotVec.z = INIT_EARTH_ROTATE_ZVAL;
	EarthVecFx32_to_MtxFx33_place(&rotMtx,&rotVec);	//初期位置からの相対座標計算
	wk->placelist.place[index].rotate = rotMtx;

	//マーク色設定(wifihistory定義に沿うこと)
	wk->placelist.place[index].col = WIFIHISTORY_GetStat(wk->wifi_sv,nationID,areaID);

	wk->placelist.place[index].nationID = nationID;	//該当国ＩＤ
	wk->placelist.place[index].areaID = areaID;		//該当地域ＩＤ
}

//----------------------------------
//登録地域情報セット
//----------------------------------
static void EarthList_NationAreaListSet( EARTH_DEMO_WORK * wk )
{
	int	i;

	for(i=0;i<wk->placelist.listcount;i++){
		if((wk->placelist.place[i].nationID == wk->my_nation)	//該当国ＩＤ
			&&(wk->placelist.place[i].areaID == wk->my_area)){	//該当地域ＩＤ

			wk->placelist.place[i].col = MARK_RED;	//マーク色設定
			wk->rotate.x  = wk->placelist.place[i].x;	//地球儀連動
			wk->rotate.y  = wk->placelist.place[i].y;	//地球儀連動
		}
	}
}

//----------------------------------
//ローカルエリア存在チェック
//----------------------------------
static int	EarthAreaTableGet(int nationID)
{
	return WIFI_COUNTRY_CountryCodeToDataIndex( nationID );
}


//============================================================================================
//
//	ローカル関数（タッチパネル関連）
//
//============================================================================================
static void Earth_TouchPanel( EARTH_DEMO_WORK * wk )
{
	int dirx,lenx,diry,leny;

	wk->tp_result = 0;

	if(sys.tp_trg){
		if(	(sys.tp_x >= ((EARTH_ICON_WIN_PX) * DOTSIZE))&&
			(sys.tp_x <= ((EARTH_ICON_WIN_PX + EARTH_ICON_WIN_SX) * DOTSIZE))&&
			(sys.tp_y >= ((EARTH_ICON_WIN_PY) * DOTSIZE))&&
			(sys.tp_y <= ((EARTH_ICON_WIN_PY + EARTH_ICON_WIN_SY) * DOTSIZE))){
			//「やめる」
			wk->tp_result = PAD_BUTTON_B;
			return;
		} else {
			wk->tp_seq = 0;
			wk->tp_lenx = 0;
			wk->tp_leny = 0;
			wk->tp_count = 0;
			wk->tp_result = 0;
			//初回の検出位置を保存
			wk->tp_x = sys.tp_x;
			wk->tp_y = sys.tp_y;
			wk->tp_count = 4;
		}
	}
	if(sys.tp_cont){
		switch(wk->tp_seq){
		case 0:
			//最初のカウントはトリガー認識用に無視
			if(!wk->tp_count){
				wk->tp_seq++;
			}else{
				wk->tp_count--;
			}
		case 1:
			Earth_TouchPanelParamGet(wk->tp_x,wk->tp_y,&dirx,&lenx,&diry,&leny);
			wk->tp_result = dirx | diry;
			wk->tp_lenx = lenx;
			wk->tp_leny = leny;
			wk->tp_x = sys.tp_x;
			wk->tp_y = sys.tp_y;
			break;
		}
	}else{
		if(wk->tp_count){
			wk->tp_result = PAD_BUTTON_A;
		}
		wk->tp_seq = 0;
		wk->tp_lenx = 0;
		wk->tp_leny = 0;
		wk->tp_count = 0;
	}
}

static void Earth_TouchPanelParamGet
	( int prevx,int prevy,int* dirx_p,int* lenx_p,int* diry_p,int* leny_p )
{
	int x_dir = 0;
	int y_dir = 0;
	int x_len = 0;
	int y_len = 0;

	//Ｘ方向＆移動幅取得
	if(sys.tp_x != 0xffff){
		x_len = sys.tp_x - prevx;
		if(x_len < 0){
			x_len ^= -1;
			x_dir = PAD_KEY_RIGHT;
		}else{
			if(x_len > 0){
				x_dir = PAD_KEY_LEFT;
			}
		}
	}
	x_len &= 0x3f;	//リミッター
	*dirx_p = x_dir;
	*lenx_p = x_len;

	//Ｙ方向＆移動幅取得
	if(sys.tp_y != 0xffff){
		y_len = sys.tp_y - prevy;
		if(y_len < 0){
			y_len ^= -1;
			y_dir = PAD_KEY_DOWN;
		}else{
			if(y_len > 0){
				y_dir = PAD_KEY_UP;
			}
		}
	}
	y_len &= 0x3f;	//リミッター
	*diry_p = y_dir;
	*leny_p = y_len;
}


//============================================================================================
//
//	ローカル関数（２Ｄ関連）
//
//============================================================================================
//----------------------------------
//ＢＧ設定
//----------------------------------
static void Earth_BGdataLoad( EARTH_DEMO_WORK * wk )
{
	//--------サブＢＧ面-------------------------------------------
	//テキストＢＧ面コントロール設定
	GF_BGL_BGControlSet(wk->bgl,EARTH_TEXT_PLANE,&Earth_Demo_BGtxt_header,GF_BGL_MODE_TEXT);
	GF_BGL_ScrClear(wk->bgl,EARTH_TEXT_PLANE);//テキストＢＧ面クリア
	//背景ＢＧ面コントロール設定
	GF_BGL_BGControlSet(wk->bgl,EARTH_BACK_S_PLANE,&Earth_Demo_Back_header,GF_BGL_MODE_TEXT);
	ArcUtil_BgCharSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCGR,wk->bgl,
						EARTH_BACK_S_PLANE,0,0,0,wk->heapID);
	ArcUtil_PalSet(		ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCLR,PALTYPE_SUB_BG,
						EARTH_BACK_PAL*PALSIZE,PALSIZE*4,wk->heapID);
	ArcUtil_ScrnSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NSCR,wk->bgl,
						EARTH_BACK_S_PLANE,0,0,0,wk->heapID);

	//メッセージウインドウキャラ＆パレット読み込み（ウインドウ外側）
	TalkWinGraphicSet(	wk->bgl,EARTH_TEXT_PLANE,
						EARTH_TALKWINCHR_NUM,EARTH_TALKWIN_PAL,
						CONFIG_GetWindowType(wk->config),wk->heapID);
	//メニューウインドウキャラ＆パレット読み込み（ウインドウ外側）
	MenuWinGraphicSet(	wk->bgl,EARTH_TEXT_PLANE,
						EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,0,wk->heapID);

	//フォントパレット読み込み
	SystemFontPaletteLoad( PALTYPE_SUB_BG, EARTH_SYSFONT_PAL*PALSIZE, wk->heapID );
	//NULLキャラ＆パレット設定
	GF_BGL_ClearCharSet( EARTH_TEXT_PLANE, 32, 0, wk->heapID );
	GF_BGL_BackGroundColorSet( EARTH_TEXT_PLANE,EARTH_NULL_PALETTE );

	//メッセージウインドウビットマップ作成（ウインドウ内側）
	GF_BGL_BmpWinAddEx(wk->bgl,&wk->msgwin,&EarthMsgWinData );
	GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,//bmp,col,startX,startY,sizeX,sizeY
			EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
	//メッセージウインドウ初期表示
	BmpTalkWinWrite(&wk->msgwin,WINDOW_TRANS_ON,EARTH_TALKWINCHR_NUM,EARTH_TALKWIN_PAL);

	//メッセージシステム初期化
	wk->msgseq = MSGSET;

	//--------メインＢＧ面------------------------------------------
	//アイコンＢＧ面コントロール設定
	GF_BGL_BGControlSet(wk->bgl,EARTH_ICON_PLANE,&Earth_Demo_BGtxt_header,GF_BGL_MODE_TEXT);
	GF_BGL_ScrClear(wk->bgl,EARTH_ICON_PLANE);//アイコンＢＧ面クリア
	//背景ＢＧ面コントロール設定
	GF_BGL_BGControlSet(wk->bgl,EARTH_BACK_M_PLANE,&Earth_Demo_Back_header,GF_BGL_MODE_TEXT);
	ArcUtil_BgCharSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCGR,wk->bgl,
						EARTH_BACK_M_PLANE,0,0,0,wk->heapID);
	ArcUtil_PalSet(		ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NCLR,PALTYPE_MAIN_BG,
						EARTH_BACK_PAL*PALSIZE,PALSIZE*4,wk->heapID);
	ArcUtil_ScrnSet(	ARC_WIFI_EARTH,NARC_wifi_earth_earth_bg_NSCR,wk->bgl,
						EARTH_BACK_M_PLANE,0,0,0,wk->heapID);

	//メニューウインドウキャラ＆パレット読み込み（ウインドウ外側）
	MenuWinGraphicSet(	wk->bgl,EARTH_ICON_PLANE,
						EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL,0,wk->heapID);

	//フォントパレット読み込み
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, EARTH_SYSFONT_PAL*PALSIZE, wk->heapID );
	//NULLキャラ＆パレット設定
	GF_BGL_ClearCharSet( EARTH_ICON_PLANE, 32, 0, wk->heapID );
	GF_BGL_BackGroundColorSet( EARTH_ICON_PLANE,0x0000 );
	{
		STRBUF* back_str = STRBUF_Create(16, wk->heapID);

		//ボタンフォントのロード
		FontProc_LoadFont( FONT_BUTTON, wk->heapID );
		//ボタンフォントパレットのロード
		{//パレットデータがないので直接作成
			u16 col1 = 0x4e56;
			u16 col2 = 0x3571;
			u16 col3 = 0x208c;
			u16 col4 = 0x7fff;

			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col1, 2, EARTH_SYSFONT_PAL*PALSIZE+1*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col2, 2, EARTH_SYSFONT_PAL*PALSIZE+2*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col3, 2, EARTH_SYSFONT_PAL*PALSIZE+3*2 );
			GF_BGL_PaletteSet( EARTH_ICON_PLANE, &col4, 2, EARTH_SYSFONT_PAL*PALSIZE+15*2 );
		}
		//メッセージウインドウビットマップ作成（ウインドウ内側）
		GF_BGL_BmpWinAddEx(wk->bgl,&wk->iconwin,&EarthIconWinData );
		GF_BGL_BmpWinFill(&wk->iconwin,FBMP_COL_WHITE,0,0,
				EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		//文字列の取得（やめる）
		MSGMAN_GetString(wk->msg_man,mes_earth_02_07,back_str);
		//文字列の表示
		GF_STR_PrintSimple(&wk->iconwin,FONT_BUTTON,back_str,0,0,MSG_NO_PUT,NULL);
		STRBUF_Delete(back_str);

		//ボタンフォントの破棄
		FontProc_UnloadFont( FONT_BUTTON );
	}
}

static void Earth_BGdataRelease( EARTH_DEMO_WORK * wk )
{
	GF_BGL_BmpWinDel(&wk->iconwin);
	GF_BGL_BmpWinDel(&wk->msgwin);
	GF_BGL_BGControlExit(wk->bgl,EARTH_ICON_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_TEXT_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_BACK_M_PLANE);
	GF_BGL_BGControlExit(wk->bgl,EARTH_BACK_S_PLANE);
}

//----------------------------------
//メッセージ表示
//----------------------------------
static BOOL Earth_MsgPrint( EARTH_DEMO_WORK * wk,u32 msgID,int button_mode )
{
	BOOL result = FALSE;

	switch(wk->msgseq){
	case MSGSET:
		//領域クリア
		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,//bmp,col,startX,startY,sizeX,sizeY
				EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);

		//文字列バッファの作成
		wk->msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

		//文字列の取得
		MSGMAN_GetString(wk->msg_man,msgID,wk->msgstr);

		//文字列の表示
		wk->msgID = GF_STR_PrintSimple(	&wk->msgwin,FONT_TALK,wk->msgstr,0,0,
										CONFIG_GetMsgPrintSpeed( wk->config ),NULL);

		wk->msgseq = MSGDRAW;
		break;

	case MSGDRAW:
		//文字列描画待ち
		if(!(GF_MSG_PrintEndCheck(wk->msgID))){
			STRBUF_Delete(wk->msgstr);
			wk->msgseq = MSGWAIT;
		}
		break;

	case MSGWAIT:
		//終了待ち
		if((button_mode != A_BUTTON_WAIT)||(sys.trg & PAD_BUTTON_A)){
			wk->msgseq = MSGSET;
			result = TRUE;
		}
	}
	return result;
}

//----------------------------------
//リスト表示用コールバック
//----------------------------------
static void Earth_BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	if( mode == 0 ){//初期化時は鳴らさない
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

//----------------------------------
//リスト表示:BmpList設定参照
//----------------------------------
static void Earth_BmpListAdd( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win,const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,const EARTH_BMPLIST* list)
{
	BMPLIST_HEADER	listheader_tmp;
	int	i;

	//メニュービットマップ追加
	GF_BGL_BmpWinAddEx(wk->bgl,win,windata);
	//メニューリスト用文字列バッファ作成
	wk->bmplistdata = BMP_MENULIST_Create(listheader->count,wk->heapID);
	//メニューリスト用文字列バッファ取得
	for( i=0; i<listheader->count; i++ ){
		BMP_MENULIST_AddArchiveString(wk->bmplistdata,wk->msg_man,list[i].msgID,list[i].retID);
	}
	//メニュービットマップリストヘッダ作成
	listheader_tmp = *listheader;
	listheader_tmp.list = wk->bmplistdata;
	listheader_tmp.win  = win;
	listheader_tmp.call_back = Earth_BmpListMoveSeCall;
	//メニュービットマップリスト作成
	wk->bmplist = BmpListSet(&listheader_tmp,0,0,wk->heapID);

	//ウインドウ（外枠）描画
	BmpMenuWinWrite(listheader_tmp.win,WINDOW_TRANS_OFF,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);
	//ＶＲＡＭ転送
	GF_BGL_BmpWinOn(win);
}

//----------------------------------
//リスト表示２:gmmファイル一括、リスト選択返り値はリストの順番と同じ(1orgin)
//----------------------------------
static void Earth_BmpListAddGmmAll( EARTH_DEMO_WORK * wk,
							GF_BGL_BMPWIN* win, const BMPWIN_DAT* windata,
							const BMPLIST_HEADER* listheader,u32 listarcID)
{
	BMPLIST_HEADER	listheader_tmp;
	MSGDATA_MANAGER*	msg_man;
	u32	listcount;
	int	i;

	//メニュービットマップ追加
	GF_BGL_BmpWinAddEx(wk->bgl,win,windata);
		
	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,listarcID,wk->heapID );
	//メッセージ総数取得
	listcount = MSGMAN_GetMessageCount(msg_man);

	//メニューリスト用文字列バッファ作成
	wk->bmplistdata = BMP_MENULIST_Create(listcount,wk->heapID);

	//メニューリスト用文字列バッファ取得
	for( i=1; i<listcount; i++ ){	//1オリジンのため
		BMP_MENULIST_AddArchiveString(wk->bmplistdata,msg_man,i,i);//BMP,man,msgID,param
	}
	//メッセージデータ破棄
	MSGMAN_Delete(msg_man);

	//メニュービットマップリストヘッダ作成
	listheader_tmp = *listheader;
	listheader_tmp.list = wk->bmplistdata;
	listheader_tmp.count = listcount-1;	//1originのため補正
	listheader_tmp.win  = win;
	listheader_tmp.call_back = Earth_BmpListMoveSeCall;
	//メニュービットマップリスト作成
	wk->bmplist = BmpListSet(&listheader_tmp,0,0,wk->heapID);

	//ウインドウ（外枠）描画
	BmpMenuWinWrite(listheader_tmp.win,WINDOW_TRANS_OFF,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);
	//ＶＲＡＭ転送
	GF_BGL_BmpWinOn(win);
}

//----------------------------------
//リスト削除
//----------------------------------
static void Earth_BmpListDel( EARTH_DEMO_WORK* wk )
{
	//選択リスト削除処理
	BmpMenuWinClear(&wk->listwin,WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&wk->listwin);
	BmpListExit(wk->bmplist,NULL,NULL);
	BMP_MENULIST_Delete(wk->bmplistdata);
}

//----------------------------------
//登録地名表示ウインドウ
//----------------------------------
static void Earth_MyPlaceInfoWinSet( EARTH_DEMO_WORK* wk )
{
	STRBUF* msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	
	STRBUF* msgtmp = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

	GF_BGL_BmpWinAddEx(wk->bgl,&wk->infowin,&EarthInfoWinData );
	GF_BGL_BmpWinFill(	&wk->infowin,FBMP_COL_WHITE,0,0,
						EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
	BmpMenuWinWrite(&wk->infowin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

	WORDSET_RegisterCountryName( wk->wordset, 0, wk->my_nation );
	WORDSET_RegisterLocalPlaceName( wk->wordset, 1, wk->my_nation, wk->my_area );

	//文字列の取得
	MSGMAN_GetString(wk->msg_man,mes_earth_03_01,msgtmp);
	WORDSET_ExpandStr( wk->wordset, msgstr, msgtmp );

	//文字列の表示
	GF_STR_PrintSimple(	&wk->infowin, FONT_SYSTEM, msgstr, 0, 0, MSG_ALLPUT, NULL );

	STRBUF_Delete( msgtmp );
	STRBUF_Delete( msgstr );

	GF_BGL_BmpWinOn(&wk->infowin);
}

static void Earth_MyPlaceInfoWinSet2( EARTH_DEMO_WORK* wk, int nation, int area )
{
	STRBUF* str1 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );
	STRBUF* str2 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );

	GF_BGL_BmpWinAddEx(wk->bgl,&wk->infowin,&EarthInfoWinData );
	GF_BGL_BmpWinFill(	&wk->infowin,FBMP_COL_WHITE,0,0,
						EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
	BmpMenuWinWrite(&wk->infowin,WINDOW_TRANS_ON,EARTH_MENUWINCHR_NUM,EARTH_MENUWIN_PAL);

	WIFI_NationAreaNameGet(	nation, area, str1, str2, wk->heapID );
	if( area != 0 ){
		GF_STR_PrintSimple(&wk->infowin,FONT_SYSTEM,str2,0,16,MSG_NO_PUT,NULL);
	}
	GF_STR_PrintSimple(&wk->infowin,FONT_SYSTEM,str1,0,0,MSG_ALLPUT,NULL);
	STRBUF_Delete(str2);
	STRBUF_Delete(str1);

	GF_BGL_BmpWinOn(&wk->infowin);
}

static void Earth_MyPlaceInfoWinRelease( EARTH_DEMO_WORK* wk )
{
	BmpMenuWinClear(&wk->infowin,WINDOW_TRANS_ON);
	GF_BGL_BmpWinDel(&wk->infowin);
}

//----------------------------------
//地名表示
//----------------------------------
static void Earth_PosInfoPut( EARTH_DEMO_WORK* wk )
{
	if( wk->info_mode == 0 ){
		{
			STRBUF* msgstr = STRBUF_Create(EARTH_STRBUF_SIZE, wk->heapID);	

			GF_BGL_BmpWinFill(	&wk->msgwin,FBMP_COL_WHITE,0,0,
								EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
			MSGMAN_GetString(wk->msg_man,mes_earth_03_02,msgstr);
			GF_STR_PrintSimple(	&wk->msgwin, FONT_TALK, msgstr, 0, 0, MSG_ALLPUT, NULL );
			STRBUF_Delete( msgstr );
		}
	} else {
		//カーソル位置地名表示
		{
			int		i;
			BOOL	search_result = FALSE;
			s16		minx = (s16)(wk->rotate.x - 0x30);
			s16		maxx = (s16)(wk->rotate.x + 0x30);
			s16		miny = (s16)(wk->rotate.y - 0x30);
			s16		maxy = (s16)(wk->rotate.y + 0x30);

			for(i=0;i<wk->placelist.listcount;i++){
				if( (wk->placelist.place[i].x > minx)&&(wk->placelist.place[i].x < maxx)
					&&(wk->placelist.place[i].y > miny)&&(wk->placelist.place[i].y < maxy)
					 &&(wk->placelist.place[i].col != MARK_NULL) ){
					{
						STRBUF* str1 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );
						STRBUF* str2 = STRBUF_Create(EARTH_NAME_SIZE, wk->heapID );

						GF_BGL_BmpWinFill(	&wk->msgwin,FBMP_COL_WHITE,0,0,
											EARTH_INFO_WIN_SX*DOTSIZE,EARTH_INFO_WIN_SY*DOTSIZE);
						WIFI_NationAreaNameGet(	wk->placelist.place[i].nationID,
												wk->placelist.place[i].areaID,
												str1,str2,wk->heapID);
						if( wk->placelist.place[i].areaID != 0 ){
							GF_STR_PrintSimple(&wk->msgwin,FONT_TALK,str2,0,16,MSG_NO_PUT,NULL);
						}
						GF_STR_PrintSimple(&wk->msgwin,FONT_TALK,str1,0,0,MSG_ALLPUT,NULL);
						STRBUF_Delete(str2);
						STRBUF_Delete(str1);

						search_result = TRUE;
					}
				}
			}
			if( search_result == FALSE ){
				wk->info_mode = 0;
			}
		}
	}
}


//============================================================================================
//
//	ローカル関数（３Ｄ関連）
//
//============================================================================================
//----------------------------------
//３Ｄデータロード関数＆３Ｄデータ開放関数
//----------------------------------
static void Earth_ModelLoad( EARTH_DEMO_WORK * wk )
{
	wk->resfileheader = ArchiveDataLoadMalloc	//地球モデル
						( ARC_WIFI_EARTH, NARC_wifi_earth_wifi_earth_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready( &wk->renderobj, &wk->resmodel, &wk->resfileheader );
	
	wk->mark_resfileheader[MARK_RED] = ArchiveDataLoadMalloc	//地点マークモデル（赤）
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_r_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_RED],
										&wk->mark_resmodel[MARK_RED],
										&wk->mark_resfileheader[MARK_RED]);

	wk->mark_resfileheader[MARK_GREEN] = ArchiveDataLoadMalloc	//地点マークモデル（緑）
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_g_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_GREEN],
										&wk->mark_resmodel[MARK_GREEN],
										&wk->mark_resfileheader[MARK_GREEN]);

	wk->mark_resfileheader[MARK_BLUE] = ArchiveDataLoadMalloc	//地点マークモデル（青）
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_b_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_BLUE],
										&wk->mark_resmodel[MARK_BLUE],
										&wk->mark_resfileheader[MARK_BLUE]);

	wk->mark_resfileheader[MARK_YELLOW] = ArchiveDataLoadMalloc	//地点マークモデル（黄）
						( ARC_WIFI_EARTH, NARC_wifi_earth_earth_mark_y_nsbmd, wk->heapID );
	simple_3DModelSetResFileAlready(	&wk->mark_renderobj[MARK_YELLOW],
										&wk->mark_resmodel[MARK_YELLOW],
										&wk->mark_resfileheader[MARK_YELLOW]);
}

static void Earth_ModelRelease( EARTH_DEMO_WORK * wk )
{
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_YELLOW]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_BLUE]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_GREEN]);
	sys_FreeMemoryEz(wk->mark_resfileheader[MARK_RED]);
	sys_FreeMemoryEz(wk->resfileheader);
}

//----------------------------------
//モデル関連データ初期化（地点データロードあり）
//----------------------------------
static void EarthDataInit( EARTH_DEMO_WORK * wk )
{
	{//地球の座標初期化（地点マークと共有）
		
		wk->trans.x	= INIT_EARTH_TRANS_XVAL; 
		wk->trans.y	= INIT_EARTH_TRANS_YVAL; 
		wk->trans.z	= INIT_EARTH_TRANS_ZVAL; 
	}
	{//地球のスケール初期化
		wk->scale.x	= INIT_EARTH_SCALE_XVAL;
		wk->scale.y	= INIT_EARTH_SCALE_YVAL;
		wk->scale.z	= INIT_EARTH_SCALE_ZVAL;
	}
	{//地球の回転初期化
		wk->rotate.x  = INIT_EARTH_ROTATE_XVAL;
		wk->rotate.y  = INIT_EARTH_ROTATE_YVAL;
		wk->rotate.z  = INIT_EARTH_ROTATE_ZVAL;
	}
	{//地点マークスケール初期化
		wk->mark_scale.x  = INIT_EARTH_SCALE_XVAL;
		wk->mark_scale.y  = INIT_EARTH_SCALE_YVAL;
		wk->mark_scale.z  = INIT_EARTH_SCALE_ZVAL;
	}
}

//----------------------------------
//カメラ初期化
//----------------------------------
static void EarthCameraInit( EARTH_DEMO_WORK * wk )
{
	VecFx32	target_pos	= 	{ INIT_CAMERA_TARGET_XVAL,
							  INIT_CAMERA_TARGET_YVAL,
							  INIT_CAMERA_TARGET_ZVAL };
	VecFx32	camera_pos	=	{ INIT_CAMERA_POS_XVAL,
							  INIT_CAMERA_POS_YVAL,
							  INIT_CAMERA_POS_ZVAL };

	//カメラライブラリ初期化
	GFC_InitCameraTC(	&target_pos,&camera_pos,
						INIT_CAMERA_PERSPWAY,
						GF_CAMERA_PERSPECTIV,
						FALSE,
						wk->camera_p);

	//クリップ関連設定
	GFC_SetCameraClip(INIT_CAMERA_CLIP_NEAR,INIT_CAMERA_CLIP_FAR,wk->camera_p);
	GFC_SetCameraView(GF_CAMERA_PERSPECTIV,wk->camera_p);
	//カメラＯＮ
	GFC_AttachCamera(wk->camera_p);

	if(wk->earth_mode == JAPAN_MODE){
		//カメラ距離フラグ初期化（開始時は近距離）
		wk->camera_status = CAMERA_NEAR;
	}else{
		//カメラ距離フラグ初期化（開始時は遠距離）
		wk->camera_status = CAMERA_FAR;
	}
	while(1){
		//カメラ設定
		if(Earth3D_CameraMoveNearFar(wk) == TRUE){
			break;
		}
	}
}

//----------------------------------
//ライト初期化
//----------------------------------
static void EarthLightInit( EARTH_DEMO_WORK * wk )
{
	wk->light_vec.x = INIT_LIGHT_ANGLE_XVAL;
	wk->light_vec.y = INIT_LIGHT_ANGLE_YVAL;
	wk->light_vec.z = INIT_LIGHT_ANGLE_ZVAL;
	NNS_G3dGlbLightVector(USE_LIGHT_NUM,wk->light_vec.x,wk->light_vec.y,wk->light_vec.z);
	//NNS_G3dGlbLightVector(1,-LIGHT_VECDEF,-LIGHT_VECDEF,-LIGHT_VECDEF);
}

//----------------------------------
//３Ｄ回転計算
//----------------------------------
static void  EarthVecFx32_to_MtxFx33( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotY33(	dst,FX_SinIdx((u16)src->y),FX_CosIdx((u16)src->y));

	MTX_RotX33(	&tmp,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_SinIdx((u16)src->z),FX_CosIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

//----------------------------------
//３Ｄ回転計算(相対)
//----------------------------------
static void  EarthVecFx32_to_MtxFx33_place( MtxFx33* dst, VecFx32* src )
{
	MtxFx33 tmp;

	MTX_RotY33(	dst,FX_SinIdx((u16)src->x),FX_CosIdx((u16)src->x));

	MTX_RotX33(	&tmp,FX_SinIdx((u16)-src->y),FX_CosIdx((u16)-src->y));
	MTX_Concat33(dst,&tmp,dst);

	MTX_RotZ33(	&tmp,FX_CosIdx((u16)src->z),FX_SinIdx((u16)src->z));
	MTX_Concat33(dst,&tmp,dst);
}

//----------------------------------
//地球操作関数
//----------------------------------
static BOOL Earth3D_Control( EARTH_DEMO_WORK * wk,int keytrg,int keycont )
{
	u16 rotate_speed_x;
	u16 rotate_speed_y;
	s16 rotate_x;
	s16 rotate_y;
	BOOL result = FALSE;

	rotate_x = wk->rotate.x;
	rotate_y = wk->rotate.y;

	//カメラ遠近移動判定（世界地球儀モードのみ）
	if((keytrg & PAD_BUTTON_A)||(wk->tp_result & PAD_BUTTON_A)){
		if(wk->earth_mode == GLOBAL_MODE){
			if(wk->camera_status == CAMERA_FAR){
				wk->camera_status = CAMERA_NEAR;
			}else{
				wk->camera_status = CAMERA_FAR;
			}
		}
		result = TRUE;
		return result;
	}
	//カメラ移動スピード初期設定
	if(wk->camera_status == CAMERA_FAR){
		//遠距離
		if((wk->tp_lenx)||(wk->tp_leny)){ //タッチパネル入力あり
			rotate_speed_x = CAMERA_MOVE_SPEED_FAR/8 * wk->tp_lenx;
			rotate_speed_y = CAMERA_MOVE_SPEED_FAR/8 * wk->tp_leny;
		}else{
			rotate_speed_x = CAMERA_MOVE_SPEED_FAR;
			rotate_speed_y = CAMERA_MOVE_SPEED_FAR;
		}
	}else{
		//近距離
		if((wk->tp_lenx)||(wk->tp_leny)){ //タッチパネル入力あり
			rotate_speed_x = CAMERA_MOVE_SPEED_NEAR/8 * wk->tp_lenx;
			rotate_speed_y = CAMERA_MOVE_SPEED_NEAR/8 * wk->tp_leny;
		}else{
			rotate_speed_x = CAMERA_MOVE_SPEED_NEAR;
			rotate_speed_y = CAMERA_MOVE_SPEED_NEAR;
		}
	}
	//カメラ上下左右移動判定
	if((keycont & PAD_KEY_LEFT)||(wk->tp_result & PAD_KEY_LEFT)){
		if(wk->earth_mode == GLOBAL_MODE){
			wk->rotate.y += rotate_speed_x;
		}else{
			//if((u16)wk->rotate.y < EARTH_LIMIT_ROTATE_YMAX){
			if(rotate_y < (s16)EARTH_LIMIT_ROTATE_YMAX){
				wk->rotate.y += rotate_speed_x;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_RIGHT)||(wk->tp_result & PAD_KEY_RIGHT)){
		if(wk->earth_mode == GLOBAL_MODE){
			wk->rotate.y -= rotate_speed_x;
		}else{
			//if((u16)wk->rotate.y > EARTH_LIMIT_ROTATE_YMIN){
			if(rotate_y > (s16)EARTH_LIMIT_ROTATE_YMIN){
				wk->rotate.y -= rotate_speed_x;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_UP)||(wk->tp_result & PAD_KEY_UP)){
		if(wk->earth_mode == GLOBAL_MODE){
			//if(((u16)(wk->rotate.x + rotate_speed_y)) < CAMERA_ANGLE_MAX){
			if((rotate_x + rotate_speed_y) < CAMERA_ANGLE_MAX){
				wk->rotate.x += rotate_speed_y;
			}else{
				wk->rotate.x = CAMERA_ANGLE_MAX;
			}
		}else{
			//if((u16)wk->rotate.x < EARTH_LIMIT_ROTATE_XMAX){
			if(rotate_x < (s16)EARTH_LIMIT_ROTATE_XMAX){
				wk->rotate.x += rotate_speed_y;
			}
		}
		result = TRUE;
	}
	if((keycont & PAD_KEY_DOWN)||(wk->tp_result & PAD_KEY_DOWN)){
		if(wk->earth_mode == GLOBAL_MODE){
			//if(((u16)(wk->rotate.x - rotate_speed_y)) > CAMERA_ANGLE_MIN){
			if((rotate_x - rotate_speed_y) > CAMERA_ANGLE_MIN){
				wk->rotate.x -= rotate_speed_y;
			}else{
				wk->rotate.x = CAMERA_ANGLE_MIN;
			}
		}else{
			//if((u16)wk->rotate.x > EARTH_LIMIT_ROTATE_XMIN){
			if(rotate_x > (s16)EARTH_LIMIT_ROTATE_XMIN){
				wk->rotate.x -= rotate_speed_y;
			}
		}
		result = TRUE;
	}
	return result;
}

//----------------------------------
//カメラ遠近移動関数
//----------------------------------
static BOOL Earth3D_CameraMoveNearFar( EARTH_DEMO_WORK * wk )
{
	fx32 distance = GFC_GetCameraDistance(wk->camera_p);
	BOOL result = FALSE;

	switch(wk->camera_status){

	case CAMERA_NEAR://近づく
		if(distance > (INIT_CAMERA_DISTANCE_NEAR + CAMERA_INOUT_SPEED)){
			distance -= CAMERA_INOUT_SPEED;
			wk->mark_scale.x -= MARK_SCALE_INCDEC;
			wk->mark_scale.y = wk->mark_scale.x;
		}else{
			distance = INIT_CAMERA_DISTANCE_NEAR;
			result = TRUE;
		}
		break;

	case CAMERA_FAR://遠ざかる
		if(distance < (INIT_CAMERA_DISTANCE_FAR - CAMERA_INOUT_SPEED)){
			distance += CAMERA_INOUT_SPEED;
			wk->mark_scale.x += MARK_SCALE_INCDEC;
			wk->mark_scale.y = wk->mark_scale.x;
		}else{
			distance = INIT_CAMERA_DISTANCE_FAR;
			result = TRUE;
		}
		break;
	}
	GFC_SetCameraDistance(distance,wk->camera_p);

	return result;
}

//----------------------------------
//３Ｄ描画関数
//----------------------------------
static void Earth3D_Draw( EARTH_DEMO_WORK * wk )
{
	MtxFx33 rotate_world = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};

	//描画フラグ判定
	switch(wk->Draw3Dsw){

	case DRAW3D_DISABLE:
		break;

	case DRAW3D_BANISH:
		GF_G3X_Reset();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		wk->Draw3Dsw = DRAW3D_DISABLE;
		break;

	case DRAW3D_ENABLE:
		GF_G3X_Reset();
		GFC_CameraLookAt();
		{
			//グローバル回転行列取得
			EarthVecFx32_to_MtxFx33(&rotate_world,&wk->rotate);
	
			//地球描画
			simple_3DModelDraw(&wk->renderobj,&wk->trans,&rotate_world,&wk->scale);
			//GF_G3D_Draw_1mat1shape(&wk->renderobj,&wk->trans,&rotate_world,&wk->scale);
	
			//中心マーク描画（基準点のため回転なし）
			{
				MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
				simple_3DModelDraw(&wk->mark_renderobj[MARK_GREEN],
						&wk->trans,&rotate_tmp,&wk->mark_scale);
				//GF_G3D_Draw_1mat1shape(&wk->mark_renderobj[MARK_GREEN],
				//		&wk->trans,&rotate_tmp,&wk->mark_scale);
			}
	
			//地点マーク描画
			{
				MtxFx33 rotate_tmp = {FX32_ONE,0,0,0,FX32_ONE,0,0,0,FX32_ONE};
				int	i;
	
				for(i=0;i<wk->placelist.listcount;i++){
					MTX_Concat33(&wk->placelist.place[i].rotate,&rotate_world,&rotate_tmp);
	
					if(wk->placelist.place[i].col != MARK_NULL){
						simple_3DModelDraw(	&wk->mark_renderobj[wk->placelist.place[i].col],
											&wk->trans,&rotate_tmp,&wk->mark_scale);
						//GF_G3D_Draw_1mat1shape(	&wk->mark_renderobj[wk->placelist.place[i].col],
						//					&wk->trans,&rotate_tmp,&wk->mark_scale);
					}
				}
			}
		}
		GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO,GX_BUFFERMODE_W);
		break;
	}
}
	
//============================================================================================
//
//	グローバル関数（地域データ取得関連）
//
//============================================================================================
//============================================================================================
/**
 *	地域データ初期化（セーブワークの初期化）
 *
 * @param	
 * @retval
 */
//============================================================================================
void	WIFI_RegistratonInit(SAVEDATA* savedata)
{
	WIFI_HISTORY* wh = SaveData_GetWifiHistory(savedata);

	WIFIHISTORY_SetMyNationArea(wh,0,0);
	WIFIHISTORY_SetWorldFlag(wh,FALSE);
}

//============================================================================================
/**
 *	国名取得
 *
 * @param[in]	nationID	国ＩＤ
 * @param[in]	areaID		地域ＩＤ
 * @param[in]	nation_str	国名格納バッファポインタ
 * @param[in]	area_str	地域名格納バッファポインタ
 * @param[in]	heapID		テンポラリヒープＩＤ
 *
 * @retval	FALSE:地域がない国　TRUE:地域がある国
 */
//============================================================================================
BOOL	WIFI_NationAreaNameGet(int nationID,int areaID,
								STRBUF* nation_str,STRBUF* area_str,int heapID)
{
	MSGDATA_MANAGER*	msg_man;
	int areaIndex = EarthAreaTableGet(nationID);	//地域データテーブルＩＮＤＥＸ取得
	BOOL result;

	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
							NARC_msg_wifi_place_msg_world_dat,heapID );

	MSGMAN_GetString(msg_man,nationID,nation_str);//国名取得

	MSGMAN_Delete(msg_man);

	if(areaIndex == 0){
		//地域が存在しない国の場合「なし」という文字列を一応セット
		areaIndex = 1;
		areaID = 0;
		result = FALSE;
	}else{
		result = TRUE;
	}
	msg_man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
							WIFI_COUNTRY_DataIndexToPlaceMsgDataID(areaIndex), heapID );

	MSGMAN_GetString(msg_man,areaID,area_str);//地域名取得
	
	MSGMAN_Delete(msg_man);

	return result;
}

//============================================================================================
/**
 *	ローカルエリア存在チェック
 *
 * @param[in]	nationID	国ＩＤ
 *
 * @retval	FALSE:地域なし　TRUE:地域あり
 */
//============================================================================================
BOOL	WIFI_LocalAreaExistCheck(int nationID)
{
	if(EarthAreaTableGet(nationID)){
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------
// デバッグ
//----------------------------------
#ifdef WIFI_ERATH_DEBUG
static void EarthDebugWinRotateInfoWrite( EARTH_DEMO_WORK * wk )
		
{
	STRBUF* str1 = STRBUF_Create(10, HEAPID_BASE_DEBUG);
	STRBUF* str2 = STRBUF_Create(10, HEAPID_BASE_DEBUG);

	STRBUF_SetHexNumber( str1, (u16)wk->rotate.x, 4, 
						NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	STRBUF_SetHexNumber( str2, (u16)wk->rotate.y, 4, 
						NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 0, 0, MSG_NO_PUT, NULL );
	GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 0, 16, MSG_ALLPUT, NULL );

	STRBUF_Delete(str2);
	STRBUF_Delete(str1);
}

static void EarthDebugWinNameInfoWrite( EARTH_DEMO_WORK * wk )
		
{
	STRBUF	*str1,*str2;
	int	i;

	if(!wk->debug_work[0]){
		for(i=0;i<wk->placelist.listcount;i++){
			if((wk->placelist.place[i].x == (s16)wk->rotate.x)
				&&(wk->placelist.place[i].y == (s16)wk->rotate.y)){
	
				str1 = STRBUF_Create(EARTH_NAME_SIZE, HEAPID_BASE_DEBUG);
				str2 = STRBUF_Create(EARTH_NAME_SIZE, HEAPID_BASE_DEBUG);

				WIFI_NationAreaNameGet(	wk->placelist.place[i].nationID,
										wk->placelist.place[i].areaID,
										str1,str2,wk->heapID);
				GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 16*4, 0, MSG_NO_PUT, NULL );
				GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 16*4, 16, MSG_ALLPUT, NULL );

				STRBUF_Delete(str2);
				STRBUF_Delete(str1);

				wk->debug_work[0] = 1;
			}
		}
	}else{
		str1 = STRBUF_Create(10, HEAPID_BASE_DEBUG);
		str2 = STRBUF_Create(10, HEAPID_BASE_DEBUG);

		GF_BGL_BmpWinFill(&wk->msgwin,FBMP_COL_WHITE,0,0,
							EARTH_MSG_WIN_SX*DOTSIZE,EARTH_MSG_WIN_SY*DOTSIZE);
		STRBUF_SetHexNumber( str1, (u16)wk->rotate.x, 4, 
							NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		STRBUF_SetHexNumber( str2, (u16)wk->rotate.y, 4, 
							NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
		GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str1, 0, 0, MSG_NO_PUT, NULL );
		GF_STR_PrintSimple(&wk->msgwin, FONT_SYSTEM, str2, 0, 16, MSG_ALLPUT, NULL );

		STRBUF_Delete(str2);
		STRBUF_Delete(str1);

		wk->debug_work[0] = 0;
	}
}

static void EarthDebugNationMarkSet( EARTH_DEMO_WORK * wk )
{
	u16 pattern_flag = WIFIHIST_STAT_NODATA;
	u16 cursor_pos;
	int	nationID;

	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_NEW;
	}
	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_EXIST;
	}
	if(pattern_flag == WIFIHIST_STAT_NODATA){
		return;
	}
	BmpListDirectPosGet(wk->bmplist,&cursor_pos);

	nationID = cursor_pos+1;	//1origin

	if(WIFI_LocalAreaExistCheck(nationID) == FALSE){
		//地域が存在しない場合のみ設定
		WIFIHISTORY_SetStat(wk->wifi_sv,nationID,0,pattern_flag);
	}
	EarthListLoad(wk);	//reload
}

static void EarthDebugAreaMarkSet( EARTH_DEMO_WORK * wk )
{
	u16 pattern_flag = WIFIHIST_STAT_NODATA;
	u16 cursor_pos;
	int	areaID;

	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_NEW;
	}
	if(sys.trg & PAD_BUTTON_SELECT){
		pattern_flag = WIFIHIST_STAT_EXIST;
	}
	if(pattern_flag == WIFIHIST_STAT_NODATA){
		return;
	}
	BmpListDirectPosGet(wk->bmplist,&cursor_pos);

	areaID = cursor_pos+1;	//1origin

	WIFIHISTORY_SetStat(wk->wifi_sv,wk->my_nation_tmp,areaID,pattern_flag);
	EarthListLoad(wk);	//reload
}

#endif



















