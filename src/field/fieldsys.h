//=============================================================================
/**
 * @file	fieldsys.h	
 * @brief	フィールドマップシステム
 * @author	GAME FREAK inc.
 */
//=============================================================================
#ifndef	__FIELDSYS_H__
#define	__FIELDSYS_H__

//==============================================================================
//	include
//==============================================================================
#include "field_common.h"

#include "savedata/savedata_def.h"	//SAVEDATA参照のため
#include "system/pms_data.h"
#include "worldmap_def.h"
#include "mapresource_def.h"

#include "field_glb_state.h"
#include "fog_sys.h"
#include "field_light.h"
#include "weather_sys_def.h"
#include "field_anime_def.h"

#include "system\procsys.h"

#include "fieldobj.h"
#include "player.h"
#include "field/poketch.h"

#include "field_3d_anime.h"
#include "div_map.h"
#include "map_tool.h"
#include "ug_radar.h"

#include "place_name.h"

#include "field_effect.h"
#include "board.h"
#include "comm_union.h"
#include "comm_union_view.h"

#include "union_board.h"

#include "sway_grass_enc.h"

#include "field/location.h"

#include "application\tradelist.h"

#include "sp_attribute_def.h"
#include "floor_touch.h"
#include "honey_tree_enc.h"
#include "savedata/fnote_mem.h"

#include "itemtool/myitem.h"

#include "savedata/b_tower.h"
#include "b_tower_scr.h"

#include "savedata/regulation.h"

#include "map_mode.h"

#include "application/zukanlist/zkn_data_work.h"

//--------------------------------------------------------------
//	extern
//--------------------------------------------------------------
#undef GLOBAL
#ifdef __FIELDSYS_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	ビルボードアクタ
//--------------------------------------------------------------
enum
{
	FIELDSYS_BLACTSET_FIELD_OBJ = 0,	///<フィールドOBJ add kaga
	FIELDSYS_BLACTSET_DEBUG_KUSA,		///<仮草用 add kaga
	FIELDSYS_BLACTSET_COMM,				///<通信エフェクト add ohno
	FIELDSYS_BLACTSET_FIELD_EFFECT,		///<フィールドエフェクト add kaga
	
	FIELDSYS_BLACTSET_NUM,				///<ビルボードアクターセット登録数
};

//--------------------------------------------------------------
//	フィールドエフェクト
//--------------------------------------------------------------
#define FE_EFFECT_MAX			(FE_PROC_MAX)
#define FE_HEAP_SIZE			(0x18000)
//#define FE_EOA_MAX				(64)	///<フィールドエフェクト　EOA最大数
#define FE_EOA_MAX				(80)	///<フィールドエフェクト　EOA最大数
#define FE_BLACT_MAX			(32)	///<フィールドエフェクト　ビルボード最大数
#define FE_BLACT_MDL_MAX		(32)
#define FE_BLACT_MDL_HEAP_SIZE	(0x0500*(FE_BLACT_MDL_MAX/2))
#define FE_BLACT_ANM_MAX		(32)
#define FE_BLACT_ANM_HEAP_SIZE	(0x0080*(FE_BLACT_ANM_MAX/2))
#define FE_BLACT_TEX_MAX		(32)
#define FE_BLACT_TEX_HEAP_SIZE	(0x0800*FE_BLACT_TEX_MAX)

//------------------------------------------------------------------
///	サブ画面の種類
//------------------------------------------------------------------
typedef enum {
	FIELD_SUBSCRN_POKETCH = 1,		///<通常（ポケッチ）
	FIELD_SUBSCRN_UNDER,			///<炭鉱（レーダー画面）
	FIELD_SUBSCRN_UNION,			///<ユニオンルーム (掲示板画面)
	FIELD_SUBSCRN_NO_POKETCH,		///<ポケッチなし、ボールのみ画面

	FIELD_SUBSCRN_MAX,
}FIELD_SUBSCRN_TYPE;

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	制御ワーク用定義
//--------------------------------------------------------------
typedef struct _CONTROL_WORK CONTROL_WORK;

//--------------------------------------------------------------
///	ENCOUNT_CHECK構造体
//--------------------------------------------------------------
typedef struct {
	u16	walk_count;		// 歩数カウンタ
//	u16	before_attr;	// 前回のアトリビュート
//	u16	plus_per;		// 確率プラス値
	u16	WinPokeCount;
}ENCOUNT_CHECK;

//--------------------------------------------------------------
///EVENTDATA構造体へのポインタ
//--------------------------------------------------------------
typedef struct EVENT_DATA EVENT_DATA;

//--------------------------------------------------------------
//--------------------------------------------------------------
typedef struct MMDL_WORK MMDL_WORK;

//--------------------------------------------------------------
/**
 * @brief	フィールドマップ内限定ワーク
 *
 * FIELDSYS_WORKのメンバの中で、フィールドマップ内でしか
 * アクセスしないものはこちらへ移すこと。
 */
//--------------------------------------------------------------
typedef struct FIELDMAP_WORK FIELDMAP_WORK;

//--------------------------------------------------------------
///システムコントロールワーク構造体
//--------------------------------------------------------------
struct _FIELDSYS_WORK	{

	CONTROL_WORK * ctrl;	///<制御用ワーク

	FIELDMAP_WORK * fldmap;

	GF_BGL_INI * bgl;		///<BGLデータ

	SAVEDATA * savedata;	///<セーブされるゲーム進行データ

	GMEVENT_CONTROL * event;	///<イベント制御

	EVENT_DATA * eventdata;		///<ゾーン毎イベントデータ

	FIELD_SUBSCRN_TYPE subscreen;	///<サブ画面の種類指定
	//fldmapに移動	POKETCH_WORK * poketch;

	LOCATION_WORK * location;		///<位置情報

	GF_CAMERA_PTR	camera_ptr;		//カメラポインタ
	DMC_PTR	map_cont_dat;	//分割ロード構造体の経由参照用ポインタ
	
	WORLD_MAP_PTR World;

	MAP_RESOURCE_PTR MapResource;	//フィールド表示リソース参照用ポインタ
	MMDL_WORK * mmdl;			///<エリア別動作モデルリストデータへのポインタ
	
	///PCD_PTR player_cont_dat;//自機座標構造体の経由参照用ポインタ
	FIELD_OBJ_SYS_PTR fldobjsys;	//フィールドOBJ参照*
	PLAYER_STATE_PTR player;	//自機情報参照ポインタ
	
	FE_SYS *fes;				//フィールドエフェクト参照ポインタ
	
	GLST_DATA_PTR		glst_data;		// ライト・マテリアルの状態保存領域
	FOG_DATA_PTR		fog_data;		// フォグの状態保存領域
	LIGHT_CONT_PTR		light_cont_data;// １日表現ライト・マテリアル操作データ
	//fldmapに移動	WEATHER_MANAGER_PTR weather_data;	// 天気データ
	//fldmapに移動	FIELD_ANIME_PTR		field_trans_anime;	// 転送アニメシステム
	FLD_3D_ANM_MNG_PTR		field_3d_anime;
	ANIME_CONT_MNG_PTR	AnimeContMng;
	SMD_PTR				SpMatData;
	MTL_CONST_PTR		map_tool_list;
///	DFL_CONST_PTR		div_func_list;
	DIV_MAP_MODE		DivMapMode;
	//fldmapに移動	PNC_PTR				place_name_cont;//地名表示

	BOARD_WORK * board;		// 看板表示
	
	BOOL	main_mode_flag;

	UG_RADAR_WORK    *UnderGroundRadar;		// 炭鉱レーダーワーク参照用ポインタ
	MAP_MODE MapMode;		//地上か地下かを判別するのに使用
	const MAP_MODE_DATA * MapModeData;

	ENCOUNT_CHECK	encount;	// エンカウントチェック用ワーク
	COMM_UNIONROOM_WORK *union_work;			// ユニオンルーム用ワークポインタ
	COMM_UNIONROOM_VIEW *union_view;			// ユニオンルーム描画処理用ワーク
	UNION_BOARD_WORK    *union_board;			// ユニオンルーム掲示板（サブ画面）ワーク
	TRADELIST_WORK      *tradelist_work;

	TP_TO_3D_PTR		TpTo3DPtr;				//3D床面とのタッチ判定用

	int	startmenu_pos;					//フィールド/地下のメニューのカーソル位置

	SWAY_GRASS_PTR SwayGrass;
	BAG_CURSOR * bag_cursor;			//バッグのカーソル情報
	FNOTE_DATA * fnote;					//対象冒険ノートページへのポインタ
	EHL_PTR	ExHeightList;
	M3DOL_PTR Map3DObjExp;			//拡張配置モデル

	HTD_PTR HoneyTreePtr;			//蜜塗り用

	BTOWER_SCRWORK*	btower_wk;		///<バトルタワー制御用ワークポインタ
    const REGULATION* regulation;     ///< 今回適用されるレギュレーションポインタ
	ZKN_DATA_WORK*	p_zukandata;	///<図鑑グローバルデータ
	BOOL scope_mode_flag;				///<望遠鏡モードフラグ
};



//==============================================================================
//	外部参照
//==============================================================================
GLOBAL void FieldSystemProc_SeqHold(void);
GLOBAL void FieldSystemProc_SeqHoldEnd(void);


extern const PROC_DATA FieldProcData;

extern BOOL GameSystem_CheckSubProcExists(FIELDSYS_WORK * fsys);
extern void GameSystem_StartSubProc(FIELDSYS_WORK * fsys, const PROC_DATA * proc, void * param);

extern BOOL GameSystem_CheckFieldProcExists(FIELDSYS_WORK * fsys);
extern BOOL GameSystem_CheckFieldMain(FIELDSYS_WORK * fsys);
extern void GameSystem_CreateFieldProc(FIELDSYS_WORK * fsys);
extern void GameSystem_FinishFieldProc(FIELDSYS_WORK * fsys);

//たぶんデバッグでしか使用しない
extern void GameSystem_FinishGame(FIELDSYS_WORK * fsys);


GLOBAL struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

extern GF_BGL_INI * FieldBglIniGet( void * fsys );
extern SAVEDATA * GameSystem_GetSaveData(void * fsys);


#undef GLOBAL


//サブプロセスの参照宣言はこの中に…
#include "field_subproc.h"

#endif	/* __FIELDSYS_H__ */
