#ifndef __DEMO_TRADE_COMMON_H__
#define __DEMO_TRADE_COMMON_H__

#include "common.h"
#include "gflib\bg_system.h"
#include "gflib\strbuf.h"
#include "system\arc_util.h"
#include "system\clact_util.h"
#include "system\wordset.h"
#include "system\wipe.h"
#include "system\fontproc.h"
#include "msgdata\msg_demo_trade.h"

#include "demo\demo_trade.h"
#include "demo_trade_sound.h"
#include "demo_trade.naix"


// これを有効にすると実行させながら各種変数を調整できる
//#define RUNTIME_ADJUST


enum {
	VINTR_TASKPRI_DEFAULT = 0,
	VINTR_TASKPRI_MAIN,
};

enum {
	TASKPRI_DEFAULT = 0,
	TASKPRI_3D_DRAW,
};

enum {
	DT_LCD_DIFF = 40,
};


// アクターアニメid
enum {
	ANM_EFFECT,
	ANM_SPOTLIGHT,
	ANM_EFFECT_REV,
	ANM_STAR,
};

//======================================================================================

typedef struct _DEMO_TRADE_WORK  DEMO_TRADE_WORK;

extern GF_BGL_INI* DemoTrade_GetBgl( DEMO_TRADE_WORK* wk );
extern CLACT_SET_PTR DemoTrade_GetActSet( DEMO_TRADE_WORK* wk );
extern WORDSET*  DemoTrade_GetWordSet( DEMO_TRADE_WORK* wk );
extern STRBUF*  DemoTrade_GetStrBuf( DEMO_TRADE_WORK* wk );
extern MSGDATA_MANAGER* DemoTrade_GetMsgManager( DEMO_TRADE_WORK* wk );
extern const POKEMON_PASO_PARAM*  DemoTrade_GetSendPokeParam( DEMO_TRADE_WORK* wk );
extern const POKEMON_PASO_PARAM*  DemoTrade_GetRecvPokeParam( DEMO_TRADE_WORK* wk );
extern u32 DemoTrade_GetBGType( DEMO_TRADE_WORK* wk );
extern void DemoTrade_TransPokeGraphic( DEMO_TRADE_WORK* wk, int id, u32 bg_frame, u32 palno, BOOL animFlag );
extern void DemoTrade_SetupPokeScreen( DEMO_TRADE_WORK* wk, int id, u32 bg_frame, u32 palno, u32 xpos, u32 ypos );
extern u16 DemoTrade_GetSendPokeNumber( DEMO_TRADE_WORK* wk );
extern u16 DemoTrade_GetRecvPokeNumber( DEMO_TRADE_WORK* wk );
extern WINTYPE DemoTrade_GetWinFrameType( DEMO_TRADE_WORK* wk );
extern DEMO_TRADE_SEQFLAG DemoTrade_GetSeq( DEMO_TRADE_WORK* wk );
extern void DemoTrade_IRQ_FreeReq( void* adrs );

//======================================================================================
enum {
	DT_WAVE_PAL_SIZE = 0x60,		// 電波用パレットサイズ
};

typedef struct	_DT_WAVE_PALANM_CTRL	DT_WAVE_PALANM_CTRL;

extern DT_WAVE_PALANM_CTRL*  DT_WavePalAnm_Start( BOOL* runFlag, int direction );
extern void  DT_WavePalAnm_StopReq( DT_WAVE_PALANM_CTRL* cwk );
extern BOOL  DT_WavePalAnm_CheckStop( DT_WAVE_PALANM_CTRL* cwk );
extern void  DT_WavePalAnm_Quit( DT_WAVE_PALANM_CTRL* cwk );

//======================================================================================
typedef struct	_DT_DSIMG_AFFINE_CTRL	DT_DSIMG_AFFINE_CTRL;

extern DT_DSIMG_AFFINE_CTRL*  DT_DSAff_Start( GF_BGL_INI* bgl, fx32 startRatio, fx32 endRatio, fx32 startSpeed, fx32 ac, int type, volatile BOOL* endFlag );


//======================================================================================

typedef struct {
	void*					cellLoadPtr;
	void*					animLoadPtr;
	NNSG2dCellDataBank*		cellData;
	NNSG2dAnimBankData*		animData;
}DEMO_TRADE_CELLANIM;


extern void DemoTrade_LoadCellAnimDatas( DEMO_TRADE_CELLANIM* clpack, u32 arcID, u32 cellDatID, u32 animDatID );
extern void DemoTrade_UnloadCellAnimDatas( DEMO_TRADE_CELLANIM* clpack );
extern void DemoTrade_SetActHeader( CLACT_HEADER* header, DEMO_TRADE_CELLANIM* clpack, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* palProxy, u32 bgPri );
extern CLACT_WORK_PTR DemoTrade_AddActor( DEMO_TRADE_WORK* wk, CLACT_HEADER* header, u32 x, u32 y, u32 actPri, int drawArea);

//======================================================================================

extern void* DemoTrade_Scene0Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene0Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene0Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene1Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene1Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene1Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene2Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene2Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene2Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene3Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene3Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene3Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene4Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene4Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene4Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene5Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene5Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene5Main( void* wk_adrs, int* seq );

extern void* DemoTrade_Scene6Init( DEMO_TRADE_WORK* mainWork );
extern void DemoTrade_Scene6Quit( void* wk_adrs );
extern BOOL DemoTrade_Scene6Main( void* wk_adrs, int* seq );







//======================================================================================
#ifdef PM_DEBUG
extern BOOL DT_adjustValue32( s32* val , u32 val_unit, u32 key, const char* str );
extern BOOL DT_adjustValue16( s16* val , u16 val_unit, u32 key, const char* str );
#endif


#endif
