//============================================================================================
/**
 * @file	demo_ending_common.h
 * @brief	エンディングデモ共通ヘッダ
 * @author	taya
 * @date	2006.06.01
 */
//============================================================================================
#ifndef __DEMO_ENDING_COMMON_H__
#define __DEMO_ENDING_COMMON_H__

#include "gflib\bg_system.h"
#include "gflib\clact.h"
#include "system\wipe.h"
#include "system\brightness.h"
#include "system\arc_util.h"
#include "ending.naix"



typedef struct _ENDING_DEMO_WORK	ENDING_DEMO_WORK;
typedef struct _ENDING_CLANM_PACK	ENDING_CLANM_PACK;


#ifdef PM_DEBUG
// これらの定義を有効にすると各シーンをすぐに終わる
//#define DEBUG_FASTMODE
//#define DEBUG_FASTMODE_SCENE7
#endif

//---------------------------------------------
/**
 *	タスクプライオリティ
 */
//---------------------------------------------
enum {
	// 通常タスク


	// VWaitタスク
	TASKPRI_STAFFLIST = 0,
	TASKPRI_BGCHANGE_EFFECT,
	TASKPRI_SCENE7_PALANIM,

	// Vintrタスク
	TASKPRI_SCENE3_POKEMOVE = 0,
	TASKPRI_SCENE7_STARMOVE = 0,
	TASKPRI_OAM_TRANS,
};

//---------------------------------------------
/**
 *	アクタープライオリティ
 */
//---------------------------------------------
enum {
	ACTPRI_HERO = 0,
	ACTPRI_POKEMON,
	ACTPRI_CIRCLE,
	ACTPRI_STAR,
	ACTPRI_STARLINE,
	ACTPRI_ISLAND,
};
//---------------------------------------------
/**
 *	キャラ配置
 */
//---------------------------------------------
enum {
	OBJ_CHARPOS_HERO = 1024,
	OBJ_PALPOS_HERO = 0,


	OBJ_CHARPOS_ISLAND = 0,
	OBJ_PALPOS_ISLAND = 0x0f,

	OBJ_CHARPOS_STAR = 0,
	OBJ_PALPOS_STAR = 0x0f,

	OBJ_CHARPOS_POKE_CIRCLE = 0,
	OBJ_CHARPOS_POKEMON = OBJ_CHARPOS_POKE_CIRCLE + 200,
	OBJ_PALPOS_POKE = 0x0e,	// 14, 15 をポケモンシルエットと円形で使う

};
//---------------------------------------------
/**
 *	3D 地面タイプ
 */
//---------------------------------------------
enum {
	ENDING_GRND_MORNING,
	ENDING_GRND_EVENING,
	ENDING_GRND_NIGHT,
};

//---------------------------------------------
/**
 *	プレイヤーアニメパターン
 */
//---------------------------------------------
enum {
	ENDING_PLAYER_ANM_MORNING,
	ENDING_PLAYER_ANM_EVENING,
	ENDING_PLAYER_ANM_NIGHT,
};
//---------------------------------------------
/**
 *	定数
 */
//---------------------------------------------
enum {
	COMMON_BGPAL_USE_SIZE = 12,

	COMMOM_FONT_PALPOS = 0,		///< メイン・サブ共通フォントパレット位置
	COMMON_BG_PALPOS = 16 - COMMON_BGPAL_USE_SIZE,

	SCENE_FADE_FRAMES = 32,

	DIFF_MAIN_SUB_LCD = 208,

	SCENE_BRIGHT_PLANEMASK = PLANEMASK_BG0|PLANEMASK_BG2|PLANEMASK_BG3|PLANEMASK_OBJ,
	CUTIN_BRIGHT_PLANEMASK = PLANEMASK_BG2|PLANEMASK_BG3|PLANEMASK_OBJ,
};


//---------------------------------------------
/**
 *	ポケモンアクター生成用パラメータ
 */
//---------------------------------------------
typedef struct {

	u16  number;
	u8   sex;
	u8   form;
	u32  rand;

}POKE_ACT_PARAM;


//============================================================================
//============================================================================

typedef struct _ENDING_BGCHANGE_WORK		ENDING_BGCHANGE_WORK;

extern ENDING_BGCHANGE_WORK*  Ending_BGChange_Start( ENDING_DEMO_WORK* mainWk, int main_sub, int priority, int wait );
extern BOOL Ending_BGChange_Wait( ENDING_BGCHANGE_WORK* wk );
extern void Ending_BGChange_Quit( ENDING_BGCHANGE_WORK* wk );

extern ENDING_CLANM_PACK*  Ending_LoadCellAnim( u32 arcID, u32 cellDatID, u32 animDatID );
extern void Ending_UnloadCellAnim( ENDING_CLANM_PACK* pack );

extern void Ending_SetActHeader( CLACT_HEADER* header, ENDING_CLANM_PACK* res,
	NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* pltProxy, u32 bgPri );

extern CLACT_WORK_PTR Ending_AddActor( ENDING_DEMO_WORK* wk, CLACT_HEADER*  actHeader, u32 x, u32 y, u32 actPri,
		 int drawArea, BOOL drawFlag );

extern CLACT_WORK_PTR  Ending_GetHeroActor( ENDING_DEMO_WORK* wk );

extern void* Ending_GetProcParam( ENDING_DEMO_WORK* wk );

extern int EndingDemo_GetPokeActCount( ENDING_DEMO_WORK* wk );
extern const POKE_ACT_PARAM* EndingDemo_GetPokeActParamTable( ENDING_DEMO_WORK* wk );
extern BOOL Ending_GetListEndFlag( ENDING_DEMO_WORK* wk );

extern void EndingDemo_DispEndString_Start( ENDING_DEMO_WORK* wk );
extern BOOL EndingDemo_DispEndString_Wait( ENDING_DEMO_WORK* wk );

extern void Ending_Change3dGroundType( ENDING_DEMO_WORK* wk, int type );

//============================================================================
//============================================================================
extern void* Ending_Scene1Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene1InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene1Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene1Main( void* wk_ptr, int* seq );

extern void* Ending_Scene2Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene2InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene2Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene2Main( void* wk_ptr, int* seq );

extern void* Ending_Scene3Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene3InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene3Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene3Main( void* wk_ptr, int* seq );

extern void* Ending_Scene4Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene4InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene4Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene4Main( void* wk_ptr, int* seq );

extern void* Ending_Scene5Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene5InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene5Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene5Main( void* wk_ptr, int* seq );

extern void* Ending_Scene6Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene6InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene6Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene6Main( void* wk_ptr, int* seq );

extern void* Ending_Scene7Init( ENDING_DEMO_WORK* mainWork, GF_BGL_INI* bgl );
extern BOOL Ending_Scene7InitWait( void* wk_ptr, int* seq );
extern BOOL Ending_Scene7Quit( void* wk_ptr, int* seq );
extern BOOL Ending_Scene7Main( void* wk_ptr, int* seq );


#endif  /* __DEMO_ENDING_COMMON_H__ */
