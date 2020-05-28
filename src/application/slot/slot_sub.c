//******************************************************************************
/**
 * 
 * @file	slot_sub.c
 * @brief	ミニゲーム　スロット　サブ
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "slot_local.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
#ifdef DEBUG_ON_SLOT
//#define DEBUG_BEND_FONT_COUNT 12
//#define DEBUG_BEND_FONT_COIN 724
#endif

//--------------------------------------------------------------
///	シンボル
//--------------------------------------------------------------
#define BIGFONT_OFFS_Y (16)

//--------------------------------------------------------------
///	リールセルアニメNo
//--------------------------------------------------------------
typedef enum
{
	REELANMNO_RED7 = 0,
	REELANMNO_BLUE7,
	REELANMNO_REPLAY,
	REELANMNO_CHERRY,
	REELANMNO_PIKA,
	REELANMNO_STONE,
}REELANMNO;

//--------------------------------------------------------------
///	転送フラグ
//--------------------------------------------------------------
typedef enum
{
	TRANS_NON = 0,
	TRANS_SET,
	TRANS_END,
}TRANSFLAG;

//==============================================================================
//	struct
//==============================================================================
//--------------------------------------------------------------
///	MBALLWORK
//--------------------------------------------------------------
typedef struct
{
	MBALLMT move_type;
	u32 seq_no;
	u32 end_flag;
	vu32 trans_flag;
	BALLTYPE type;
	
	VecFx32 mtx;
	VecFx32 offs;
	u32 angle;
	u32 frame;
	int no;
	
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}MBALLWORK;

//==============================================================================
//	static
//==============================================================================
static const EOA_H_NPP DATA_EoaH_Reel;

static const EOA_H_NPP DATA_EoaH_CreditFont;

//static const EOA_H_NPP DATA_EoaH_WinLoseFont;

//static EOA_PTR EoaMBall_Set( SLOTMAIN *main, BALLTYPE type );
//static void EoaMBall_MoveTypeChange( EOA_PTR eoa, MBALLMT type );
//static int EoaMBall_MoveEndCheck( EOA_PTR eoa );

static void MBall_GraphicInit( MBALLWORK *work, BALLTYPE type );
static void MBall_GraphicDelete( SLOTMAIN *main );
static void MBall_VramTransTCB( TCB_PTR tcb, void *wk );
static void MBall_VramResDeleteTCB( TCB_PTR tcb, void *wk );
static void MBall_ClActAdd( SLOTMAIN *main, CLACT_WORK_EX *actwork, const VecFx32 *mtx );

static const REELANMNO DATA_ReelTypeCellAnimeNoTbl[REEL_PATTERN_MAX];
static const fx32 DATA_CreditFontXOffsetTbl[10];
static const fx32 DATA_PayOutFontXOffsetTbl[10];

static const CELLARCDATA DATA_MonsBallArcDataTbl[BALL_MAX];
static const CELLARCDATA DATA_PipArcDataTbl[PIP_MAX];

//==============================================================================
//	eoa	スロット絵柄
//==============================================================================
//--------------------------------------------------------------
///	REELHEAD
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	fx32 offs_y;
	REEL_NUM reel_no;
}REELHEAD;

//--------------------------------------------------------------
///	REELWORK
//--------------------------------------------------------------
typedef struct
{
	REELHEAD head;
	CLACT_WORK_EX actwork;
}REELWORK;

//--------------------------------------------------------------
/**
 * スロット絵柄初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_ReelPatternInit( SLOTMAIN *main )
{
	REEL_NUM reel;
	fx32 x,y;
	EOA_PTR eoa;
	REELHEAD head;
	VecFx32 mtx = {0,0,0};
	
	head.main = main;
	
	for( reel = 0, x = NUM_FX32(40+28); reel < REEL_MAX; reel++, x += NUM_FX32(60) ){
		for( y = 0; y < NUM_FX32(160); y += NUM_FX32(32) ){
			mtx.x = x;
			head.reel_no = reel;
			head.offs_y = y;
			eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_Reel, &mtx, 0, &head, TCBPRI_REEL );
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA スロット絵柄　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaReel_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	REELWORK *work = wk;
	const REELHEAD *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->head.main->clactset, &work->actwork, &mtx, G2D_2DMAIN, CELL_VRAM,
		SLOT_CHARID_REEL, SLOT_PLTTID_REEL, SLOT_CELLID_REEL,
		SLOT_ANMID_REEL, BGPRI3, CAPRI_REEL );
	
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA スロット絵柄　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaReel_Delete( EOA_PTR eoa, void *wk )
{
	REELWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA スロット絵柄　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaReel_Move( EOA_PTR eoa, void *wk )
{
	int reel;
	u32 no;
	fx32 y;
	VecFx32 mtx;
	REELWORK *work = wk;
	
	reel = work->head.reel_no;
	y = work->head.main->reel_dot_y[reel] + work->head.offs_y;
	y %= NUM_FX32( REEL_PT_V_MAX );
	
	EOA_MatrixGet( eoa, &mtx );
	mtx.y = y + NUM_FX32( REEL_PT_V_OFFSET ) + work->head.main->reel_offs_y[reel];
	CLACT_SetMatrix( work->actwork.act, &mtx );
	
	y = REEL_PT_V_DG( y );
	
	no = DATA_ReelTypeCellAnimeNoTbl[
		Slot_ReelPatternGet(work->head.main, reel, FX32_NUM(y)) ];
	
	if( no != CLACT_AnmGet(work->actwork.act) ){
		CLACT_AnmChg( work->actwork.act, no );
		CLACT_AnmFrameSet( work->actwork.act, 0 );
	}
}

//--------------------------------------------------------------
/**
 * EOA スロット絵柄　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaReel_Draw( EOA_PTR eoa, void *wk )
{
	REELWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA 絵柄
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Reel =
{
	sizeof(REELWORK),
	eoaReel_Init,
	eoaReel_Delete,
	eoaReel_Move,
	eoaReel_Draw,
};

//==============================================================================
//	EOA 文字　クレジット
//==============================================================================
//--------------------------------------------------------------
///	CREDITFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	u32 keta;
	u32 keta_a;
	CLACT_WORK_EX actwork;
}CREDITFWORK;

//--------------------------------------------------------------
/**
 * クレジット初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_CreditFontInit( SLOTMAIN *main )
{
	u32 keta;
	VecFx32 mtx = {NUM_FX32(108),NUM_FX32(180),0};
	
	for( keta = 1; keta < 100000; keta *= 10, mtx.x -= NUM_FX32(8) ){
		EOA_Add_NPP( main->eoa_sys,&DATA_EoaH_CreditFont, &mtx, keta, main, TCBPRI_CREDITFONT );
	}
}

//--------------------------------------------------------------
/**
 * EOA クレジット　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaCreditFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	CREDITFWORK *work = wk;
	
	work->keta = EOA_AddParamGet( eoa );
	work->keta_a = work->keta * 10;
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DMAIN, CELL_VRAM,
		SLOT_CHARID_CREDITFONT, SLOT_PLTTID_CREDITFONT, SLOT_CELLID_CREDITFONT,
		SLOT_ANMID_CREDITFONT, BGPRI1, CAPRI_CREDITFONT );
	
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA クレジット　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaCreditFont_Delete( EOA_PTR eoa, void *wk )
{
	CREDITFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA クレジット　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaCreditFont_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	CREDITFWORK *work = wk;
	u32 coin = work->main->credit;
	
	if( work->keta > 1 &&  coin < work->keta ){
		CLACT_SetDrawFlag( work->actwork.act, 0 );
		return;
	}
	
	CLACT_SetDrawFlag( work->actwork.act, 1 );
	
	coin %= work->keta_a;
	coin /= work->keta;
	
	if( coin != CLACT_AnmGet(work->actwork.act) ){
		CLACT_AnmChg( work->actwork.act, coin );
		CLACT_AnmReStart( work->actwork.act );
	}
	
	EOA_MatrixGet( eoa, &mtx );
	mtx.x += DATA_CreditFontXOffsetTbl[coin];
	CLACT_SetMatrix( work->actwork.act, &mtx );
}

//--------------------------------------------------------------
/**
 * EOA クレジット　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaCreditFont_Draw( EOA_PTR eoa, void *wk )
{
	CREDITFWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H クレジット
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_CreditFont =
{
	sizeof(CREDITFWORK),
	eoaCreditFont_Init,
	eoaCreditFont_Delete,
	eoaCreditFont_Move,
	eoaCreditFont_Draw,
};

//==============================================================================
//	EOA　文字　ペイアウト
//==============================================================================
static const EOA_H_NPP DATA_EoaH_PayOutFont;

//--------------------------------------------------------------
///	PAYOUTFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	u32 keta;
	u32 keta_a;
	CLACT_WORK_EX actwork;
}PAYOUTFWORK;

//--------------------------------------------------------------
/**
 * ペイアウト初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_PayOutFontInit( SLOTMAIN *main )
{
	u32 keta;
	VecFx32 mtx = {NUM_FX32(180),NUM_FX32(180),0};
	
	for( keta = 1; keta < 100000; keta *= 10, mtx.x -= NUM_FX32(8) ){
		EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_PayOutFont, &mtx, keta, main, TCBPRI_CREDITFONT);
	}
}

//--------------------------------------------------------------
/**
 * EOA ペイアウト　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaPayOutFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	PAYOUTFWORK *work = wk;
	
	work->keta = EOA_AddParamGet( eoa );
	work->keta_a = work->keta * 10;
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DMAIN, CELL_VRAM,
		SLOT_CHARID_CREDITFONT, SLOT_PLTTID_CREDITFONT, SLOT_CELLID_CREDITFONT,
		SLOT_ANMID_CREDITFONT, BGPRI1, CAPRI_CREDITFONT );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ペイアウト　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPayOutFont_Delete( EOA_PTR eoa, void *wk )
{
	PAYOUTFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA ペイアウト　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPayOutFont_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	PAYOUTFWORK *work = wk;
	u32 coin = work->main->payout;
	
	if( coin < work->keta ){
		CLACT_SetDrawFlag( work->actwork.act, 0 );
		return;
	}
	
	CLACT_SetDrawFlag( work->actwork.act, 1 );
	
	coin %= work->keta_a;
	coin /= work->keta;
	
	if( coin != CLACT_AnmGet(work->actwork.act) ){
		CLACT_AnmChg( work->actwork.act, coin );
		CLACT_AnmReStart( work->actwork.act );
	}
	
	EOA_MatrixGet( eoa, &mtx );
	mtx.x += DATA_PayOutFontXOffsetTbl[coin];
	CLACT_SetMatrix( work->actwork.act, &mtx );
}

//--------------------------------------------------------------
/**
 * EOA ペイアウト　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPayOutFont_Draw( EOA_PTR eoa, void *wk )
{
	CREDITFWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H ペイアウト
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_PayOutFont =
{
	sizeof(PAYOUTFWORK),
	eoaPayOutFont_Init,
	eoaPayOutFont_Delete,
	eoaPayOutFont_Move,
	eoaPayOutFont_Draw,
};

//==============================================================================
//	WIN LOSE文字
//==============================================================================
#if 0	//中止
//--------------------------------------------------------------
///	WINLOSEFWORK
//--------------------------------------------------------------
typedef struct
{
	WLFTYPE old_type;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}WINLOSEFWORK;

//--------------------------------------------------------------
/**
 * WINLOSEF初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_WinLoseFontInit( SLOTMAIN *main )
{
	VecFx32 mtx = { NUM_FX32(16), NUM_FX32(73), 0 };
	EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_WinLoseFont, &mtx, 0, main, TCBPRI_CREDITFONT );
}

//--------------------------------------------------------------
/**
 * EOA WINLOSE 初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaWinLoseFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	WINLOSEFWORK *work = wk;
	
	work->old_type = WLF_NON;
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DMAIN, CELL_VRAM,
		SLOT_CHARID_WIN_LOSE, SLOT_PLTTID_FONT, SLOT_CELLID_WIN_LOSE,
		SLOT_ANMID_WIN_LOSE, BGPRI1, CAPRI_CREDITFONT );
	
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA WIN LOSE 削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaWinLoseFont_Delete( EOA_PTR eoa, void *wk )
{
	WINLOSEFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA WIN LOSE 動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaWinLoseFont_Move( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	WINLOSEFWORK *work = wk;
	WLFTYPE type = work->main->win_lose_type;
	
	if( type == WLF_NON ){
		CLACT_SetDrawFlag( work->actwork.act, 0 );
	}else if( type != work->old_type ){
		int no = 0;
		if( type == WLF_LOSE ){ no = 1; }
		
		CLACT_AnmChg( work->actwork.act, no );
		CLACT_AnmFrameSet( work->actwork.act, 0 );
		CLACT_SetDrawFlag( work->actwork.act, 1 );
	}
	
	EOA_MatrixGet( eoa, &mtx );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	work->old_type = type;
}

//--------------------------------------------------------------
/**
 * EOA WIN LOSE 描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaWinLoseFont_Draw( EOA_PTR eoa, void *wk )
{
	WINLOSEFWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H WIN LOSE
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_WinLoseFont =
{
	sizeof(WINLOSEFWORK),
	eoaWinLoseFont_Init,
	eoaWinLoseFont_Delete,
	eoaWinLoseFont_Move,
	eoaWinLoseFont_Draw,
};
#endif

//==============================================================================
//	モンスターボール　EOA
//==============================================================================
static const EOA_H_NPP DATA_EoaH_MBall;
static int (* const * const DATA_eoaMBallMoveTbl[MBALLMT_MAX])( MBALLWORK *work );

//--------------------------------------------------------------
/**
 * EOAモンスターボール追加
 * @param	main	SLOTMAIN
 * @retval	eoa		EOAモンスターボール
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_MBallSet( SLOTMAIN *main, BALLTYPE type )
{
	EOA_PTR eoa;
	VecFx32 mtx = {NUM_FX32(0),NUM_FX32(400),0};
	
#ifdef PM_DEBUG	
	if( !(type >= BALL_MON && type < BALL_MAX) ){
		GF_ASSERT( 0 && "SlotSubEoa_MBallSet() ball type error" );
	}
#endif
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_MBall, &mtx, type, main, TCBPRI_MBALL );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOAモンスターボール動作変更
 * @param	eoa		EOA_PTR
 * @param	type	MBALLMT
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_MBallMoveTypeChange( EOA_PTR eoa, MBALLMT type )
{
	MBALLWORK *work = EOA_LocalWorkGet( eoa );
	
#ifdef PM_DEBUG
	if( work->move_type == MBALLMT_INIT && work->end_flag == FALSE ){
		GF_ASSERT( 0 && "MBALLMT_INIT Not End" );	//アクターの初期化もまだなんだぜ？
	}
#endif
	
	work->move_type = type;
	work->seq_no = 0;
	work->end_flag = FALSE;
	work->frame = 0;
}

//--------------------------------------------------------------
/**
 * EOAモンスターボール　表示、非表示
 * @param	eoa		EOA_PTR
 * @param	vanish	TRUE=非表示　FALSE=表示
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_MBallVanishSet( EOA_PTR eoa, int vanish )
{
	MBALLWORK *work = EOA_LocalWorkGet( eoa );
	
	if( vanish == TRUE ){
		CLACT_SetDrawFlag( work->actwork.act, 0 );
	}else{
		CLACT_SetDrawFlag( work->actwork.act, 1 );
	}
}

//--------------------------------------------------------------
/**
 * EOAモンスターボール動作終了チェック
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
int SlotSubEoa_MBallMoveEndCheck( EOA_PTR eoa )
{
	MBALLWORK *work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA モンスターボール　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常終了
 */
//--------------------------------------------------------------
static int eoaMBall_Init( EOA_PTR eoa, void *wk )
{
	MBALLWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	work->type = EOA_AddParamGet( eoa );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA モンスターボール　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaMBall_Delete( EOA_PTR eoa, void *wk )
{
	MBALLWORK *work = wk;
	
	if( work->actwork.act != NULL ){
		MBall_GraphicDelete( work->main );
		ClActDelete( &work->actwork );
	}
}

//--------------------------------------------------------------
/**
 * EOA モンスターボール　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaMBall_Move( EOA_PTR eoa, void *wk )
{
	int ret;
	MBALLWORK *work = wk;
	int (* const * movetbl)( MBALLWORK * );
	
	do{
		movetbl = DATA_eoaMBallMoveTbl[work->move_type];
		ret = movetbl[work->seq_no]( work );
	}while( ret == TRUE );
}

//--------------------------------------------------------------
/**
 * EOA モンスターボール　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaMBall_Draw( EOA_PTR eoa, void *wk )
{
	MBALLWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H モンスターボール
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_MBall =
{
	sizeof(MBALLWORK),
	eoaMBall_Init,
	eoaMBall_Delete,
	eoaMBall_Move,
	eoaMBall_Draw,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　初期化　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Init_Init( MBALLWORK *work )
{
	MBall_GraphicInit( work, work->type );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　初期化　アクター追加
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Init_InitWait( MBALLWORK *work )
{
	if( work->trans_flag == TRANS_END ){
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　初期化　アクター追加
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Init_ActAdd( MBALLWORK *work )
{
	VecFx32 mtx = { NUM_FX32(0), NUM_FX32(192+224), 0 };
	MBall_ClActAdd( work->main, &work->actwork, &mtx );
	work->end_flag = TRUE;
	work->seq_no++;
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　終了　共通
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_End( MBALLWORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　初期化まとめ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_Init[])( MBALLWORK *work ) =
{
	eoaMBallMove_Init_Init,
	eoaMBallMove_Init_InitWait,
	eoaMBallMove_Init_ActAdd,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　転がり開始　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_SpinStart_Init( MBALLWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(192), 0 };
	VecFx32 scale = { 0x2000, 0x2000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, 0 );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, 0 );
	CLACT_AnmFrameSet( work->actwork.act, 0 );
	Snd_SePlay( SE_SLOT_BALL_FALL_DOWN );
	
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　転がり開始　移動
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 * 192-160=32,200
 */
//--------------------------------------------------------------
static int eoaMBallMove_SpinStart_Move( MBALLWORK *work )
{
	VecFx32 mtx,scale;
	
	ClActMatrixGet( work->actwork.act, &mtx );
	ClActScaleGet( work->actwork.act, &scale );
	
	mtx.y -= (FX32_ONE*3) + (FX32_ONE/1);
	scale.x -= 0x01c7;
	scale.y -= 0x01c7;
	
	work->frame++;
	
	if( work->frame >= 9 ){
		mtx.y = SUBD_NFX32( 160 );
		scale.x = 0x1000;
		scale.y = 0x1000;
		work->frame = 0;
		work->seq_no++;
	}
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　転がり開始　アニメ終了待ち
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 * 192-160=32,200
 */
//--------------------------------------------------------------
static int eoaMBallMove_SpinStart_Wait( MBALLWORK *work )
{
	work->frame++;
	
	if( work->frame >= 3 ){
		work->frame = 0;
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　回転開始まとめ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_SpinStart[])( MBALLWORK *work ) =
{
	eoaMBallMove_SpinStart_Init,
	eoaMBallMove_SpinStart_Move,
	eoaMBallMove_SpinStart_Wait,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ボール開く　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Open_Init( MBALLWORK *work )
{
	CLACT_AnmChg( work->actwork.act, MBALLANMNO_OPEN );
	CLACT_AnmReStart( work->actwork.act );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	
	Snd_SePlay( SE_SLOT_BALL_OPEN );
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ボール開く　ウェイト
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Open_Wait( MBALLWORK *work )
{
	work->frame++;
	
	if( work->frame >= 4 ){
		work->frame = 0;
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　開くまとめ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_Open[])( MBALLWORK *work ) =
{
	eoaMBallMove_Open_Init,
	eoaMBallMove_Open_Wait,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ボール閉じる　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Close_Init( MBALLWORK *work )
{
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160), 0 };
	
	work->mtx = mtx;
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, 0 );
	CLACT_AnmChg( work->actwork.act, MBALLANMNO_CLOSE );
	CLACT_AnmReStart( work->actwork.act );
	
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ボール閉じる　落下
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Close_Move( MBALLWORK *work )
{
	VecFx32 mtx;
	fx32 offs[8] = { NUM_FX32(-8),NUM_FX32(0),
		NUM_FX32(-6),NUM_FX32(0),
		NUM_FX32(-4),NUM_FX32(0),
		NUM_FX32(-2),NUM_FX32(0)};
	
	mtx = work->mtx;
	mtx.y += offs[work->frame/2];
	CLACT_SetMatrix( work->actwork.act, &mtx );
	
	work->frame++;
	
	if( work->frame >= 16  ){
		work->frame = 0;
		work->end_flag = TRUE;
		work->seq_no++;
	}	
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　ボール閉じる
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_Close[])( MBALLWORK *work ) =
{
	eoaMBallMove_Close_Init,
	eoaMBallMove_Close_Move,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　画面外へ　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_SpinOut_Init( MBALLWORK *work )
{
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160), 0 };
	
	work->mtx = mtx;
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, 0 );
	CLACT_AnmChg( work->actwork.act, MBALLANMNO_BACK );
	CLACT_AnmReStart( work->actwork.act );
//	Snd_SePlay( SEQ_SE_DP_053 );
	
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　画面外へ　移動
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_SpinOut_Move( MBALLWORK *work )
{
	fx32 frame;
	VecFx32 mtx,scale;
	
	ClActMatrixGet( work->actwork.act, &mtx );
	ClActScaleGet( work->actwork.act, &scale );
	
	mtx.y += (FX32_ONE*4);
	scale.x += 0x01c7;
	scale.y += 0x01c7;
	
	work->frame++;
	
	if( work->frame >= 10 ){
		mtx.y = SUBD_NFX32( 256 );
		scale.x = 0x1000;
		scale.y = 0x1000;
		work->frame = 0;
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　画面外へ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_SpinOut[])( MBALLWORK *work ) =
{
	eoaMBallMove_SpinOut_Init,
	eoaMBallMove_SpinOut_Move,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ゆらゆら　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Shake_Init( MBALLWORK *work )
{
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160), 0 };
	VecFx32 offs = { 0,0,0 };
	
	work->mtx = mtx;
	work->offs = offs;
	work->frame = 0;
	work->no = 0;
	work->angle = 0;
	work->end_flag = TRUE;	//何時でも終了可能
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, 0 );
	CLACT_AnmChg( work->actwork.act, MBALLANMNO_STOP );
	CLACT_AnmReStart( work->actwork.act );
	
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA MBALL動作　ゆらゆら　動作
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Shake_Move( MBALLWORK *work )
{
	u32 angle[8] = { -16, 0, 16, 0, 16, 0, -16, 0 };
	fx32 vec[8] = { NUM_FX32(-2), 0, NUM_FX32(2), 0, NUM_FX32(2), 0, NUM_FX32(-2), 0 };
	u32 frame[8] = { 4, 1, 4, 8, 4, 1, 4, 8 };
	
	work->angle += angle[work->no];
	work->mtx.x += vec[work->no];
	work->frame++;
	
	if( work->frame >= frame[work->no] ){
		work->no++;
		
		if( work->no >= 8 ){
			work->no = 0;
		}
		
		work->frame = 0;
	}
	
	CLACT_SetMatrix( work->actwork.act, &work->mtx );
	CLACT_SetRotation( work->actwork.act, work->angle );
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　ゆらゆらまとめ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_Shake[])( MBALLWORK *work ) =
{
	eoaMBallMove_Shake_Init,
	eoaMBallMove_Shake_Move,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
/**
 * EOA MBALL動作　停止　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaMBallMove_Stop_Init( MBALLWORK *work )
{
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160), 0 };
	VecFx32 offs = { 0,0,0 };
	
	work->mtx = mtx;
	work->offs = offs;
	work->end_flag = TRUE;	//何時でも終了可能
	
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, 0 );
	CLACT_AnmChg( work->actwork.act, MBALLANMNO_STOP );
	CLACT_AnmReStart( work->actwork.act );
	
	work->seq_no++;
	return( TRUE );
}

//--------------------------------------------------------------
///	EOA MBALL動作　停止まとめ
//--------------------------------------------------------------
static int (* const DATA_eoaMBallMoveTbl_Stop[])( MBALLWORK *work ) =
{
	eoaMBallMove_Stop_Init,
	eoaMBallMove_End,
};

//--------------------------------------------------------------
///	EOA MBALL動作テーブル
//--------------------------------------------------------------
static int (* const * const DATA_eoaMBallMoveTbl[MBALLMT_MAX])( MBALLWORK *work ) =
{
	DATA_eoaMBallMoveTbl_Init, 
	DATA_eoaMBallMoveTbl_SpinStart,
	DATA_eoaMBallMoveTbl_Open,
	DATA_eoaMBallMoveTbl_Close,
	DATA_eoaMBallMoveTbl_SpinOut,
	DATA_eoaMBallMoveTbl_Shake,
	DATA_eoaMBallMoveTbl_Stop,
};

//==============================================================================
//	モンスターボール　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * モンスターボールグラフィック初期化
 * @param	main	SLOTMAIN
 * @param	type	ボールタイプ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MBall_GraphicInit( MBALLWORK *work, BALLTYPE type )
{
	TCB_PTR tcb;
	SLOTMAIN *main = work->main;
	const CELLARCDATA *arcdata;
	
	GF_ASSERT( type < BALL_MAX && "MBall_GraphicInit() balltype error" );
	arcdata = &DATA_MonsBallArcDataTbl[type];
	
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, arcdata->char_id, SLOT_CHARID_MBALL );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, arcdata->pltt_id, SLOT_PLTTID_MBALL );
	ClActCellAdd( main->clactset,
		main->arc_handle, arcdata->cell_id, SLOT_CELLID_MBALL );
	ClActAnmAdd( main->clactset,
		main->arc_handle, arcdata->anm_id, SLOT_ANMID_MBALL );
	
	tcb = VIntrTCB_Add( MBall_VramTransTCB, work, VINTRTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
	tcb = VWaitTCB_Add( MBall_VramResDeleteTCB, work, VWAITTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
}

//--------------------------------------------------------------
/**
 * モンスターボールグラフィック削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MBall_GraphicDelete( SLOTMAIN *main )
{
	ClActGraphicDelete( main->clactset,
		SLOT_CHARID_MBALL, SLOT_PLTTID_MBALL, SLOT_CELLID_MBALL, SLOT_ANMID_MBALL );
}

//--------------------------------------------------------------
/**
 * ボールグラフィックVRAM転送
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MBall_VramTransTCB( TCB_PTR tcb, void *wk )
{
	MBALLWORK *work = wk;
	SLOTMAIN *main = work->main;
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_MBALL );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_MBALL );
	work->trans_flag = TRANS_SET;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * ボールグラフィックVRAM転送後のリソース破棄
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void MBall_VramResDeleteTCB( TCB_PTR tcb, void *wk )
{
	MBALLWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	if( work->trans_flag == TRANS_SET ){
		ClActPlttResDelete( main->clactset, SLOT_PLTTID_MBALL );
		work->trans_flag = TRANS_END;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * モンスターボール　セルアクター追加
 * @param	main	SLOTMAIN 
 * @param	mtx		座標
 * @retval	CLACT_WORK_PTR	CLACT_WORK_PTR
 */
//--------------------------------------------------------------
static void MBall_ClActAdd( SLOTMAIN *main, CLACT_WORK_EX *actwork, const VecFx32 *mtx )
{
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x1000,0x1000,0};
	
	ClActAdd( main->clactset, actwork, mtx, G2D_2DSUB, CELL_TRANS,
			SLOT_CHARID_MBALL, SLOT_PLTTID_MBALL, SLOT_CELLID_MBALL,
			SLOT_ANMID_MBALL, BGPRI2, CAPRI_MBALL );
	
	CLACT_SetAffineParam( actwork->act, CLACT_AFFINE_DOUBLE );
	CLACT_SetAffineMatrix( actwork->act, &affoffs );
	CLACT_SetScale( actwork->act, &scale );
	CLACT_SetRotation( actwork->act, RotKeyR(0) );
	CLACT_SetAnmFlag( actwork->act, 1 );
}

//==============================================================================
//	ボール煙
//==============================================================================
//--------------------------------------------------------------
/// BALLEFFWORK	
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 end_flag;
	u32 frame;
	vu32 trans_flag;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}BALLEFFWORK;

static const EOA_H_NPP DATA_EoaH_BallEff;
static void BallEff_GraphicInit( BALLEFFWORK *work );

//--------------------------------------------------------------
/**
 * EOAボール煙追加
 * @param	main	SLOTMAIN
 * @retval	eoa		EOA
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BallEffSet( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = {NUM_FX32(128),SUBD_NFX32(160-16),0};
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_BallEff, &mtx, 0, main, TCBPRI_BALLEFF );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOAボール煙動作終了チェック
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
int SlotSubEoa_BallEffEndCheck( EOA_PTR eoa )
{
	BALLEFFWORK *work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA ボール煙　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常終了
 */
//--------------------------------------------------------------
static int eoaBallEff_Init( EOA_PTR eoa, void *wk )
{
	BALLEFFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	BallEff_GraphicInit( work );

	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ボール煙　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBallEff_Delete( EOA_PTR eoa, void *wk )
{
	BALLEFFWORK *work = wk;
	
	if( work->actwork.act != NULL ){
		ClActGraphicDelete( work->main->clactset,
			SLOT_CHARID_BALLEFF, SLOT_PLTTID_BALLEFF, SLOT_CELLID_BALLEFF, SLOT_ANMID_BALLEFF );
		ClActDelete( &work->actwork );
	}
}

//--------------------------------------------------------------
/**
 * EOA ボール煙　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBallEff_Move( EOA_PTR eoa, void *wk )
{
	BALLEFFWORK *work = wk;
	
	switch( work->seq_no ){
	case 0:
		if( work->trans_flag != TRANS_END ){
			return;
		}
		
		{
			VecFx32 mtx;
			EOA_MatrixGet( eoa, &mtx );
			ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_TRANS,
				SLOT_CHARID_BALLEFF, SLOT_PLTTID_BALLEFF, SLOT_CELLID_BALLEFF,
				SLOT_ANMID_BALLEFF, BGPRI2, CAPRI_BALLEFF );
			CLACT_SetAnmFlag( work->actwork.act, 1 );
			work->seq_no++;
		}
	case 1:
		work->frame++;
		
		if( work->frame < 15 ){
			return;
		}
		
		work->seq_no++;
		work->end_flag = TRUE;
		break;
	case 2:
		ClActGraphicDelete( work->main->clactset,
			SLOT_CHARID_BALLEFF, SLOT_PLTTID_BALLEFF, SLOT_CELLID_BALLEFF, SLOT_ANMID_BALLEFF );
		ClActDelete( &work->actwork );
		work->seq_no++;
	case 3:
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA ボール煙　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBallEff_Draw( EOA_PTR eoa, void *wk )
{
	BALLEFFWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H ボール煙
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BallEff =
{
	sizeof(BALLEFFWORK),
	eoaBallEff_Init,
	eoaBallEff_Delete,
	eoaBallEff_Move,
	eoaBallEff_Draw,
};

//--------------------------------------------------------------
/**
 * ボールエフェクトVRAM転送
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void BallEff_VramTransTCB( TCB_PTR tcb, void *wk )
{
	BALLEFFWORK *work = wk;
	SLOTMAIN *main = work->main;
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BALLEFF );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_BALLEFF );
	work->trans_flag = TRANS_SET;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * ボールエフェクトVRAM転送後のリソース開放
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void BallEff_VramResDeleteTCB( TCB_PTR tcb, void *wk )
{
	BALLEFFWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	if( work->trans_flag == TRANS_SET ){
		ClActPlttResDelete( main->clactset, SLOT_PLTTID_BALLEFF );
		work->trans_flag = TRANS_END;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ボール煙グラフィック　初期化
 * @param	main	SLOTMAIN
 * @param	type	ボールタイプ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void BallEff_GraphicInit( BALLEFFWORK *work )
{
	TCB_PTR tcb;
	SLOTMAIN *main = work->main;
	
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_ball_eff_NCGR, SLOT_CHARID_BALLEFF );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_ball_eff_NCLR, SLOT_PLTTID_BALLEFF );
	ClActCellAdd( main->clactset,
		main->arc_handle, NARC_slot_ball_eff_NCER, SLOT_CELLID_BALLEFF );
	ClActAnmAdd( main->clactset,
		main->arc_handle, NARC_slot_ball_eff_NANR, SLOT_ANMID_BALLEFF );
	
	tcb = VIntrTCB_Add( BallEff_VramTransTCB, work, VINTRTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
	tcb = VWaitTCB_Add( BallEff_VramResDeleteTCB, work, VWAITTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
}

//==============================================================================
//	ピッピ
//==============================================================================
//--------------------------------------------------------------
///	PIPWORK
//--------------------------------------------------------------
typedef struct
{
	u32 testseqno;
	PIPMT move_type;
	u32 seq_no;
	u32 end_flag;
	u32 trans_flag;
	int frame;
	PIPTYPE piptype;
	void *rare_buf;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}PIPWORK;

static const EOA_H_NPP DATA_EoaH_Pip;
static int (* const * const DATA_eoaPipMoveTbl[PIPMT_MAX])( PIPWORK *work );

//--------------------------------------------------------------
/**
 * ピッピグラフィック転送
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pip_VramTransTCB( TCB_PTR tcb, void *wk )
{
	PIPWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_PIP );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_PIP );
	
#if 0	
	if( work->piptype == PIP_RARE ){
		u32 vram;
		NNSG2dPaletteData *pPltt;
		const NNSG2dImagePaletteProxy *proxy;
		
		NNS_G2dGetUnpackedPaletteData( work->rare_buf, &pPltt );
		proxy = ClActPlttProxyGet( main->clactset, SLOT_PLTTID_PIP );
		vram = NNS_G2dGetImagePaletteLocation( proxy, G2D_2DSUB );
		
 		DC_FlushRange( (void*)pPltt->pRawData, 32 );
		GX_LoadOBJPltt( pPltt->pRawData, vram, 32 );
	}
#endif
	
	work->trans_flag = TRANS_SET;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * ピッピグラフィック転送後のリソース破棄
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pip_VramResDeleteTCB( TCB_PTR tcb, void *wk )
{
	PIPWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	if( work->trans_flag == TRANS_SET ){
		ClActPlttResDelete( main->clactset, SLOT_PLTTID_PIP );
#if 0	
		if( work->piptype == PIP_RARE ){
			sys_FreeMemoryEz( work->rare_buf );
		}
#endif		
		work->trans_flag = TRANS_END;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ピッピグラフィック追加
 * @param	PIPWORK	PIPWORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pip_GraphicInit( PIPWORK *work )
{
	TCB_PTR tcb;
	SLOTMAIN *main = work->main;
	const CELLARCDATA *arcdata = &DATA_PipArcDataTbl[work->piptype];
	
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, arcdata->char_id, SLOT_CHARID_PIP );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, arcdata->pltt_id, SLOT_PLTTID_PIP );
	ClActCellAdd( main->clactset,
		main->arc_handle, arcdata->cell_id, SLOT_CELLID_PIP );
	ClActAnmAdd( main->clactset,
		main->arc_handle, arcdata->anm_id, SLOT_ANMID_PIP );
#if 0	
	if( work->piptype == PIP_RARE ){
		work->rare_buf = SlotArc_DataLoad( main, NARC_slot_pippi_rare_NCLR, FALSE );
	}
#endif
	
	tcb = VIntrTCB_Add( Pip_VramTransTCB, work, VINTRTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
	tcb = VWaitTCB_Add( Pip_VramResDeleteTCB, work, VWAITTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
}

//--------------------------------------------------------------
/**
 * EOAピッピ追加
 * @param	main	SLOTMAIN
 * @param	piptype	PIPTYPE
 * @retval	eoa		EOAモンスターボール
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_PipSet( SLOTMAIN *main, PIPTYPE type )
{
	EOA_PTR eoa;
	VecFx32 mtx = {NUM_FX32(128),NUM_FX32(160),0};
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_Pip, &mtx, type, main, TCBPRI_PIP );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOAピッピ動作変更
 * @param	eoa		EOA_PTR
 * @param	type	MBALLMT
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotSubEoa_PipMoveTypeChange( EOA_PTR eoa, PIPMT type )
{
	PIPWORK *work = EOA_LocalWorkGet( eoa );

#ifdef PM_DEBUG
	if( work->move_type == PIPMT_INIT && work->end_flag == FALSE ){
		GF_ASSERT( 0 && "PIPMT_INIT Not End" );	//アクターの初期化もまだなんだぜ？
	}
#endif
	
	work->move_type = type;
	work->seq_no = 0;
	work->end_flag = FALSE;
	work->frame = 0;
}

//--------------------------------------------------------------
/**
 * EOAピッピ動作終了チェック
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
int SlotSubEoa_PipMoveEndCheck( EOA_PTR eoa )
{
	PIPWORK *work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA ピッピ　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常終了
 */
//--------------------------------------------------------------
static int eoaPip_Init( EOA_PTR eoa, void *wk )
{
	PIPWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	work->piptype = EOA_AddParamGet( eoa );
	Pip_GraphicInit( work );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ピッピ　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPip_Delete( EOA_PTR eoa, void *wk )
{
	PIPWORK *work = wk;
	
	if( work->actwork.act != NULL ){
		SLOTMAIN *main = work->main;
		ClActGraphicDelete( main->clactset,
			SLOT_CHARID_PIP, SLOT_PLTTID_PIP, SLOT_CELLID_PIP, SLOT_ANMID_PIP );
		ClActDelete( &work->actwork );
	}
}

//--------------------------------------------------------------
/**
 * EOA ピッピ　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPip_Move( EOA_PTR eoa, void *wk )
{
	int ret;
	PIPWORK *work = wk;
	int (* const * movetbl)( PIPWORK * );
	
	do{
		movetbl = DATA_eoaPipMoveTbl[work->move_type];
		ret = movetbl[work->seq_no]( work );
	}while( ret == TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ピッピ　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPip_Draw( EOA_PTR eoa, void *wk )
{
	PIPWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H ピッピ
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Pip =
{
	sizeof(PIPWORK),
	eoaPip_Init,
	eoaPip_Delete,
	eoaPip_Move,
	eoaPip_Draw,
};

//--------------------------------------------------------------
/**
 * EOA ピッピ動作　初期化　初期化
 * @param	work	PIPWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Init_Init( PIPWORK *work )
{
	if( work->trans_flag == TRANS_END ){
		VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(256), 0 };
		VecFx32 affoffs = { 0, 0, 0 };
		VecFx32 scale = { 0x1000, 0x1000, 0 };
		
		ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_TRANS,
			SLOT_CHARID_PIP, SLOT_PLTTID_PIP, SLOT_CELLID_PIP,
			SLOT_ANMID_PIP, BGPRI2, CAPRI_PIP );
		CLACT_SetAffineParam( work->actwork.act, CLACT_AFFINE_DOUBLE );
		CLACT_SetAffineMatrix( work->actwork.act, &affoffs );
		CLACT_SetRotation( work->actwork.act, RotKeyR(0) );
		work->end_flag = TRUE;
		work->seq_no++;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA PIP動作　終了　共通
 * @param	work	PIPWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_End( PIPWORK *work )
{
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　初期化
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Init[])( PIPWORK *work ) =
{
	eoaPipMove_Init_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　登場　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Start_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x0400, 0x0400, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_START );
	CLACT_SetAnmFrame( work->actwork.act, 0 );
	CLACT_SetAnmFlag( work->actwork.act, 0 );
	
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA PIP動作　登場　移動
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Start_Move( PIPWORK *work )
{
	VecFx32 mtx,scale;
	
	ClActMatrixGet( work->actwork.act, &mtx );
	ClActScaleGet( work->actwork.act, &scale );
	
//	mtx.y -= NUM_FX32( 2 );
	scale.x += 0xc0;
	scale.y += 0xc0;
	
	work->frame++;
	
	if( work->frame >= 16 ){
		mtx.y = SUBD_NFX32( 160 - 32 );
		scale.x = 0x1000;
		scale.y = 0x1000;
		work->frame = 0;
		work->seq_no++;
		
		Snd_PMVoicePlay( MONSNO_PIPPI );
	}
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA PIP動作　登場　アニメ待ち
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Start_Wait( PIPWORK *work )
{
	CLACT_AnmFrameChg( work->actwork.act, NUM_FX32(1) );
	work->frame++;
	
	if( work->frame >= 9 ){
		work->frame = 0;
		work->seq_no++;
		work->end_flag = TRUE;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　登場
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Start[])( PIPWORK *work ) =
{
	eoaPipMove_Start_Init,
	eoaPipMove_Start_Move,
	eoaPipMove_Start_Wait,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　戻る　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Back_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_START );
	CLACT_SetAnmFrame( work->actwork.act, 0 );
	CLACT_SetAnmFlag( work->actwork.act, 0 );
	Snd_SePlay( SE_SLOT_PIPPI_BALL_IN );
	
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA PIP動作　戻る　移動
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Back_Move( PIPWORK *work )
{
	VecFx32 mtx,scale;
	
	ClActMatrixGet( work->actwork.act, &mtx );
	ClActScaleGet( work->actwork.act, &scale );
	
	scale.x -= 0x180;
	scale.y -= 0x180;
	
	work->frame++;
	
	if( work->frame >= 8 ){
		mtx.y = SUBD_NFX32( 272 );
		scale.x = 0x1000;
		scale.y = 0x1000;
		work->frame = 0;
		work->seq_no++;
		work->end_flag = TRUE;
	}
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　戻る
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Back[])( PIPWORK *work ) =
{
	eoaPipMove_Back_Init,
	eoaPipMove_Back_Move,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　立ち　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Stand_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_STOP );
	CLACT_SetAnmFlag( work->actwork.act, 0 );
	CLACT_SetAnmFrame( work->actwork.act, 0 );
	CLACT_AnmReStart( work->actwork.act );
	
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　立ち
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Stand[])( PIPWORK *work ) =
{
	eoaPipMove_Stand_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　パタパタ　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_PataPata_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	CLACT_SetAnmFrame( work->actwork.act, FX32_ONE/2 );
	
	if( CLACT_AnmGet(work->actwork.act) != PIPANMNO_PATAPATA ){
		CLACT_AnmChg( work->actwork.act, PIPANMNO_PATAPATA );
		CLACT_AnmReStart( work->actwork.act );
	}
	
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　パタパタ
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_PataPata[])( PIPWORK *work ) =
{
	eoaPipMove_PataPata_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　中央指し　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Naka_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_NAKA );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	CLACT_SetAnmFrame( work->actwork.act, FX32_ONE );
	CLACT_AnmReStart( work->actwork.act );
	
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　中央指し
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Naka[])( PIPWORK *work ) =
{
	eoaPipMove_Naka_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　左指し　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Left_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_LEFT );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	CLACT_SetAnmFrame( work->actwork.act, FX32_ONE );
	CLACT_AnmReStart( work->actwork.act );
	
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　左指し
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Left[])( PIPWORK *work ) =
{
	eoaPipMove_Left_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　右指し　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Right_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_AnmChg( work->actwork.act, PIPANMNO_RIGHT );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	CLACT_SetAnmFrame( work->actwork.act, FX32_ONE );
	CLACT_AnmReStart( work->actwork.act );
	
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　右指し
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Right[])( PIPWORK *work ) =
{
	eoaPipMove_Right_Init,
	eoaPipMove_End,
};

//--------------------------------------------------------------
/**
 * EOA PIP動作　万歳　初期化
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Banzai_Init( PIPWORK *work )
{
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(160-32), 0 };
	VecFx32 scale = { 0x1000, 0x1000, 0 };
	
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetMatrix( work->actwork.act, &mtx );
	CLACT_SetAnmFlag( work->actwork.act, 0 );
	CLACT_SetAnmFrame( work->actwork.act, FX32_ONE );
	
	CLACT_AnmChg( work->actwork.act, PIPANMNO_NAKA );
	CLACT_AnmReStart( work->actwork.act );
	
	work->frame = 0;
	work->end_flag = TRUE;
	work->seq_no++;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * EOA PIP動作　万歳　アニメ
 * @param	work	MBALLWORK
 * @retval	int		TRUE=再帰要求
 */
//--------------------------------------------------------------
static int eoaPipMove_Banzai_Anm( PIPWORK *work )
{
	CLACT_AnmFrameChg( work->actwork.act, FX32_ONE );
	
	if( CLACT_AnmActiveCheck(work->actwork.act) == FALSE ){
		work->frame++;
		
		if( work->frame >= 8 ){
			work->frame = 0;
			CLACT_AnmReStart( work->actwork.act );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
///	EOA PIP動作　万歳
//--------------------------------------------------------------
static int (* const DATA_eoaPipMoveTbl_Banzai[])( PIPWORK *work ) =
{
	eoaPipMove_Banzai_Init,
	eoaPipMove_Banzai_Anm,
	eoaPipMove_End,
};

//--------------------------------------------------------------
///	EOA PIP動作テーブル
//--------------------------------------------------------------
static int (* const * const DATA_eoaPipMoveTbl[PIPMT_MAX])( PIPWORK *work ) =
{
	DATA_eoaPipMoveTbl_Init,
	DATA_eoaPipMoveTbl_Start,
	DATA_eoaPipMoveTbl_Back,
	DATA_eoaPipMoveTbl_Stand,
	DATA_eoaPipMoveTbl_PataPata,
	DATA_eoaPipMoveTbl_Naka,
	DATA_eoaPipMoveTbl_Left,
	DATA_eoaPipMoveTbl_Right,
	DATA_eoaPipMoveTbl_Banzai,
};

//==============================================================================
//	ピカチュウ
//==============================================================================
//--------------------------------------------------------------
///	PIKAWORK 
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 end_flag;
	u32 frame;
	u32 count;
	vu32 trans_flag;
	VecFx32 mtx;
	VecFx32 offs;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork0;
	CLACT_WORK_EX actwork1;
}PIKAWORK;

static const EOA_H_NPP DATA_EoaH_Pika;

//--------------------------------------------------------------
/**
 * ピカチュウVRAM転送
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pika_VramTransTCB( TCB_PTR tcb, void *wk )
{
	PIKAWORK *work = wk;
	SLOTMAIN *main = work->main;
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_PIKA );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_PIKA );
	work->trans_flag = TRANS_SET;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * ピカチュウVRAM転送後のリソース破棄
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pika_VramResDeleteTCB( TCB_PTR tcb, void *wk )
{
	PIKAWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	if( work->trans_flag = TRANS_SET ){
		ClActPlttResDelete( main->clactset, SLOT_PLTTID_PIKA );
		work->trans_flag = TRANS_END;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ピカチュウグラフィック　初期化
 * @param	work	PIKAWORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Pika_GraphicInit( PIKAWORK *work )
{
	TCB_PTR tcb;
	SLOTMAIN *main = work->main;
	
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_pika_NCGR, SLOT_CHARID_PIKA );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_pika_NCLR, SLOT_PLTTID_PIKA );
	ClActCellAdd( main->clactset,
		main->arc_handle, NARC_slot_slot_pika_NCER, SLOT_CELLID_PIKA );
	ClActAnmAdd( main->clactset,
		main->arc_handle, NARC_slot_slot_pika_NANR, SLOT_ANMID_PIKA );
	
	tcb = VIntrTCB_Add( Pika_VramTransTCB, work, VINTRTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
	tcb = VWaitTCB_Add( Pika_VramResDeleteTCB, work, VWAITTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
}

//--------------------------------------------------------------
/**
 * EOAピカチュウ追加
 * @param	main	SLOTMAIN
 * @retval	eoa		EOA
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_PikaSet( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { 0, 0, 0 };
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_Pika, &mtx, 0, main, TCBPRI_PIKA );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOAピカチュウ動作終了チェック
 * @param	eoa		EOA_PTR
 * @retval	int		TRUE=終了
 */
//--------------------------------------------------------------
int SlotSubEoa_PikaEndCheck( EOA_PTR eoa )
{
	PIKAWORK *work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA 　ピカチュウ　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常終了
 */
//--------------------------------------------------------------
static int eoaPika_Init( EOA_PTR eoa, void *wk )
{
	PIKAWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	Pika_GraphicInit( work );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ピカチュウ　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPika_Delete( EOA_PTR eoa, void *wk )
{
	PIKAWORK *work = wk;
	
	if( work->actwork0.act != NULL ){
		ClActGraphicDelete( work->main->clactset,
			SLOT_CHARID_PIKA, SLOT_PLTTID_PIKA, SLOT_CELLID_PIKA, SLOT_ANMID_PIKA );
		ClActDelete( &work->actwork0 );
		
		if( work->actwork1.act != NULL ){
			ClActDelete( &work->actwork1 );
		}
	}
}

//--------------------------------------------------------------
/**
 * ピカチュウ　座標操作
 * @param
 * @retval
 */
//--------------------------------------------------------------
static void eoaPika_PosSet( EOA_PTR eoa,
	fx32 x, fx32 y, fx32 ax, fx32 ay, CLACT_WORK_PTR act, int no )
{
	VecFx32 mtx0,mtx1;
	
	EOA_MatrixGet( eoa, &mtx0 );
	mtx0.x += ax;
	mtx0.y += ay;
	EOA_MatrixSet( eoa, &mtx0 );
	
	if( no == 0 ){
		mtx1.x = x + mtx0.x;
	}else{
		mtx1.x = x - mtx0.x;
	}
	
	mtx1.y = y - mtx0.y;
	CLACT_SetMatrix( act, &mtx1 );
}	

//--------------------------------------------------------------
/**
 * EOA ピカチュウ　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPika_Move( EOA_PTR eoa, void *wk )
{
	PIKAWORK *work = wk;
	
	switch( work->seq_no ){
	case 0:
		if( work->trans_flag != TRANS_END ){
			return;
		}
		
		{
			VecFx32 mtx = { 0, SUBD_NFX32(256), 0 };
			ClActAdd( work->main->clactset, &work->actwork0, &mtx, G2D_2DSUB, CELL_TRANS,
				SLOT_CHARID_PIKA, SLOT_PLTTID_PIKA, SLOT_CELLID_PIKA,
				SLOT_ANMID_PIKA, BGPRI2, CAPRI_PIKA );
			ClActAdd( work->main->clactset, &work->actwork1, &mtx, G2D_2DSUB, CELL_TRANS,
				SLOT_CHARID_PIKA, SLOT_PLTTID_PIKA, SLOT_CELLID_PIKA,
				SLOT_ANMID_PIKA, BGPRI2, CAPRI_PIKA );
			CLACT_SetFlip( work->actwork1.act, CLACT_FLIP_H );
			work->seq_no++;
		}
	case 1:	//登場
		{
			int flag = FALSE;
			VecFx32 mtx0,mtx1;
			EOA_MatrixGet( eoa, &mtx0 );
			
			mtx0.x += NUM_FX32( 8 );
			mtx0.y += NUM_FX32( 8 );
			
			if( mtx0.x >= NUM_FX32(64) ){
				mtx0.x = NUM_FX32( 64 );
				flag++;
			}
			
			if( mtx0.y >= NUM_FX32(56) ){
				mtx0.y = NUM_FX32( 64 );
				flag++;
			}
			
			EOA_MatrixSet( eoa, &mtx0 );
			
			mtx1.x = NUM_FX32(-32) + mtx0.x;
			mtx1.y = SUBD_NFX32(228) - mtx0.y;
			CLACT_SetMatrix( work->actwork0.act, &mtx1 );
			
			mtx1.x = NUM_FX32(288) - mtx0.x;
			mtx1.y = SUBD_NFX32(228) - mtx0.y;
			CLACT_SetMatrix( work->actwork1.act, &mtx1 );
			
			if( flag == 2 ){
				work->seq_no++;
			}
		}
		
		break;
	case 2:
		work->frame++;
			
		if( work->frame < 8 ){
			break;
		}
				
		work->frame = 0;
		work->seq_no++;
	case 3:
		eoaPika_PosSet( eoa,
			NUM_FX32(-32), SUBD_NFX32(228), NUM_FX32(-2), NUM_FX32(-4), work->actwork0.act, 0 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 4:
		eoaPika_PosSet( eoa,
			NUM_FX32(-32), SUBD_NFX32(228), NUM_FX32(2), NUM_FX32(4), work->actwork0.act, 0 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 5:
		eoaPika_PosSet( eoa,
			NUM_FX32(288), SUBD_NFX32(228), NUM_FX32(-2), NUM_FX32(-4), work->actwork1.act, 1 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 6:
		eoaPika_PosSet( eoa,
			NUM_FX32(288), SUBD_NFX32(228), NUM_FX32(2), NUM_FX32(4), work->actwork1.act, 1 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			
			work->count++;
			
			if( work->count < 2 ){
				work->seq_no = 3;
			}else{
				work->count = 0;
				work->seq_no++;
			}
		}
		
		break;
	case 7:
		work->frame++;
		
		if( work->frame < 8 ){
			break;
		}
		
		work->frame = 0;
		work->seq_no++;
	case 8:
		eoaPika_PosSet( eoa,
			NUM_FX32(-32), SUBD_NFX32(228), NUM_FX32(-2), NUM_FX32(-4), work->actwork0.act, 0 );
		eoaPika_PosSet( eoa,
			NUM_FX32(288), SUBD_NFX32(228), NUM_FX32(0), NUM_FX32(0), work->actwork1.act, 1 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 9:
		eoaPika_PosSet( eoa,
			NUM_FX32(-32), SUBD_NFX32(228), NUM_FX32(2), NUM_FX32(4), work->actwork0.act, 0 );
		eoaPika_PosSet( eoa,
			NUM_FX32(288), SUBD_NFX32(228), NUM_FX32(0), NUM_FX32(0), work->actwork1.act, 1 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			work->frame = 0;
			
			work->count++;
			
			if( work->count < 2 ){
				work->seq_no = 8;
			}else{
				work->count = 0;
				work->seq_no++;
			}
		}
		
		break;
	case 10:
		eoaPika_PosSet( eoa,
			NUM_FX32(-32), SUBD_NFX32(228), NUM_FX32(-8), NUM_FX32(-8), work->actwork0.act, 0 );
		eoaPika_PosSet( eoa,
			NUM_FX32(288), SUBD_NFX32(228), NUM_FX32(0), NUM_FX32(0), work->actwork1.act, 1 );
		
		work->frame++;
		
		if( work->frame >= 4 ){
			ClActDelete( &work->actwork0 );
			ClActDelete( &work->actwork1 );
			ClActGraphicDelete( work->main->clactset,
				SLOT_CHARID_PIKA, SLOT_PLTTID_PIKA, SLOT_CELLID_PIKA, SLOT_ANMID_PIKA );
		}
		
		work->seq_no++;
		work->end_flag = TRUE;
	}
}

//--------------------------------------------------------------
/**
 * EOA ピカチュウ　描画
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaPika_Draw( EOA_PTR eoa, void *wk )
{
	PIKAWORK *work = wk;
}

//--------------------------------------------------------------
///	EOA_H ピカチュウ
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Pika =
{
	sizeof(PIKAWORK),
	eoaPika_Init,
	eoaPika_Delete,
	eoaPika_Move,
	eoaPika_Draw,
};

//==============================================================================
//	EOA 文字　ボーナス
//==============================================================================
//--------------------------------------------------------------
///	BONUSFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}BONUSFWORK;

static const EOA_H_NPP DATA_EoaH_BonusFont;

//--------------------------------------------------------------
/**
 * ボーナス文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BonusFontInit( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(24), SUBD_NFX32(8), 0 };
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_BonusFont, &mtx, 0, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ボーナスフォント　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaBonusFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	BONUSFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_VRAM,
		SLOT_CHARID_BONUSFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_BONUSFONT,
		SLOT_ANMID_BONUSFONT, BGPRI2, CAPRI_BONUS_FONT );
	
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBonusFont_Delete( EOA_PTR eoa, void *wk )
{
	BONUSFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBonusFont_Move( EOA_PTR eoa, void *wk )
{
	int flag = TRUE;
	BONUSFWORK *work = wk;
	DDISPCONTROL *dcont = &work->main->ddispcont;
	
	if( dcont->bonus_font_vanish_flag == TRUE ){
		flag = FALSE;
	}
	
	CLACT_SetDrawFlag( work->actwork.act, flag );
}

//--------------------------------------------------------------
///	EOA ボーナス文字　ヘッダー
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BonusFont =
{
	sizeof(BONUSFWORK),
	eoaBonusFont_Init,
	eoaBonusFont_Delete,
	eoaBonusFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA 文字　大文字ボーナス
//==============================================================================
//--------------------------------------------------------------
///	BIGBONUSFWORK
//--------------------------------------------------------------
typedef struct
{
	int frame;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}BIGBONUSFWORK;

static const EOA_H_NPP DATA_EoaH_BigBonusFont;

//--------------------------------------------------------------
/**
 * ボーナス大文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BigBonusFontInit( SLOTMAIN *main )
{
	VecFx32 mtx;
	EOA_PTR eoa;
	
	mtx.x = NUM_FX32( 128 - (((6 + 5)*8)/2) );	//6=bonus 5=keta
	mtx.y = SUBD_NFX32( 96 + BIGFONT_OFFS_Y );
	eoa = EOA_Add_NPP(main->eoa_sys, &DATA_EoaH_BigBonusFont, &mtx, 0, main, TCBPRI_BONUSFONT);
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス大文字 初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaBigBonusFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x2000, 0x2000, 0 };
	BIGBONUSFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_VRAM,
		SLOT_CHARID_BONUSFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_BONUSFONT,
		SLOT_ANMID_BONUSFONT, BGPRI2, CAPRI_BONUS_FONT );
	
	CLACT_SetAffineParam( work->actwork.act, CLACT_AFFINE_DOUBLE );
	CLACT_SetAffineMatrix( work->actwork.act, &affoffs );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, RotKeyR(0) );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス大文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigBonusFont_Delete( EOA_PTR eoa, void *wk )
{
	BIGBONUSFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス大文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigBonusFont_Move( EOA_PTR eoa, void *wk )
{
	int flag = TRUE;
	BIGBONUSFWORK *work = wk;
	
	work->frame++;
	
	if( work->frame >= 45 ){
		EOA_Delete( eoa );
	}
}

//--------------------------------------------------------------
///	EOA ボーナス大文字　ヘッダー
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BigBonusFont =
{
	sizeof(BIGBONUSFWORK),
	eoaBigBonusFont_Init,
	eoaBigBonusFont_Delete,
	eoaBigBonusFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA 文字　ゲット
//==============================================================================
//--------------------------------------------------------------
///	GETFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}GETFWORK;

static const EOA_H_NPP DATA_EoaH_GetFont;

//--------------------------------------------------------------
/**
 * ゲット文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_GetFontInit( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(200), SUBD_NFX32(184), 0 };
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_GetFont, &mtx, 0, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ゲット文字　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaGetFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	BONUSFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_VRAM,
		SLOT_CHARID_GETFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_GETFONT,
		SLOT_ANMID_GETFONT, BGPRI2, CAPRI_BONUS_FONT );
	
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ゲット文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaGetFont_Delete( EOA_PTR eoa, void *wk )
{
	GETFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA ゲット文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaGetFont_Move( EOA_PTR eoa, void *wk )
{
	int flag = TRUE;
	GETFWORK *work = wk;
	DDISPCONTROL *dcont = &work->main->ddispcont;
	
	if( dcont->bonus_font_vanish_flag == TRUE ){
		flag = FALSE;
	}
	
	CLACT_SetDrawFlag( work->actwork.act, flag );
}

//--------------------------------------------------------------
///	EOA ゲット文字　ヘッダー
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_GetFont =
{
	sizeof(GETFWORK),
	eoaGetFont_Init,
	eoaGetFont_Delete,
	eoaGetFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA 文字　ゲット大文字
//==============================================================================
//--------------------------------------------------------------
///	BIGGETFWORK
//--------------------------------------------------------------
typedef struct
{
	int frame;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork;
}BIGGETFWORK;

static const EOA_H_NPP DATA_EoaH_BigGetFont;

//--------------------------------------------------------------
/**
 * ゲット大文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BigGetFontInit( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(200), SUBD_NFX32(184), 0 };
	mtx.x = NUM_FX32( 128 - (((10 + 5)*8)/2) );	//6=bonus 5=keta 7=bonus-keta
	mtx.y = SUBD_NFX32( 96 - BIGFONT_OFFS_Y );
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_BigGetFont, &mtx, 0, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ゲット大文字 初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaBigGetFont_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x2000, 0x2000, 0 };
	BIGGETFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	ClActAdd( work->main->clactset, &work->actwork, &mtx, G2D_2DSUB, CELL_VRAM,
		SLOT_CHARID_GETFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_GETFONT,
		SLOT_ANMID_GETFONT, BGPRI2, CAPRI_BONUS_FONT );
	
	CLACT_SetAffineParam( work->actwork.act, CLACT_AFFINE_DOUBLE );
	CLACT_SetAffineMatrix( work->actwork.act, &affoffs );
	CLACT_SetScale( work->actwork.act, &scale );
	CLACT_SetRotation( work->actwork.act, RotKeyR(0) );
	CLACT_SetAnmFlag( work->actwork.act, 1 );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ゲット大文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigGetFont_Delete( EOA_PTR eoa, void *wk )
{
	BIGGETFWORK *work = wk;
	ClActDelete( &work->actwork );
}

//--------------------------------------------------------------
/**
 * EOA ゲット大文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigGetFont_Move( EOA_PTR eoa, void *wk )
{
	int flag = TRUE;
	BIGGETFWORK *work = wk;
	
	work->frame++;
	
	if( work->frame >= 45 ){
		EOA_Delete( eoa );
	}
}

//--------------------------------------------------------------
///	EOA ゲット大文字　ヘッダー
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BigGetFont =
{
	sizeof(BIGGETFWORK),
	eoaBigGetFont_Init,
	eoaBigGetFont_Delete,
	eoaBigGetFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA　文字　ボーナスカウント
//==============================================================================
//--------------------------------------------------------------
///	BCOUNTFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	CLACT_WORK_EX actwork[2];
}BCOUNTFWORK;

static const EOA_H_NPP DATA_EoaH_BCountFont;

//--------------------------------------------------------------
/**
 * ボーナスカウント文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BCountFontInit( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(14), SUBD_NFX32(8), 0 };
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_BCountFont, &mtx, 0, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ボーナスカウント文字 初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaBCountFont_Init( EOA_PTR eoa, void *wk )
{
	int i;
	VecFx32 mtx;
	BCOUNTFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	for( i = 0; i < 2; i++ ){
		ClActAdd( work->main->clactset, &work->actwork[i], &mtx, G2D_2DSUB, CELL_VRAM,
			SLOT_CHARID_BONUSGETFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_BONUSGETFONT,
			SLOT_ANMID_BONUSGETFONT, BGPRI2, CAPRI_BONUS_FONT );
		CLACT_SetDrawFlag( work->actwork[i].act, 0 );
		CLACT_SetAnmFlag( work->actwork[i].act, 1 );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ボーナスカウント文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBCountFont_Delete( EOA_PTR eoa, void *wk )
{
	BCOUNTFWORK *work = wk;
	ClActDelete( &work->actwork[0] );
	ClActDelete( &work->actwork[1] );
}

//--------------------------------------------------------------
/**
 * EOA ボーナスカウント文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBCountFont_Move( EOA_PTR eoa, void *wk )
{
	BCOUNTFWORK *work = wk;
	DDISPCONTROL *dcont = &work->main->ddispcont;
	
	CLACT_SetDrawFlag( work->actwork[0].act, FALSE );
	CLACT_SetDrawFlag( work->actwork[1].act, FALSE );
	
	if( dcont->bonus_font_vanish_flag == TRUE ){
		return;
	}
	
	{
		VecFx32 mtx = { NUM_FX32(52), SUBD_NFX32(8), 0 };
		u32 i=0,c,count;
		
		count = work->main->bonus_count;
		
		if( count > 99 ){
			count = 99;
		}
		
		c = (count % 100) / 10;
		
		if( c ){
			CLACT_SetMatrix( work->actwork[i].act, &mtx );
			CLACT_AnmChg( work->actwork[i].act, c );
			CLACT_AnmReStart( work->actwork[i].act );
			CLACT_SetDrawFlag( work->actwork[i].act, TRUE );
			mtx.x += NUM_FX32( 8 );
			i++;
		}
		
		c = (count % 10);
		
		CLACT_SetMatrix( work->actwork[i].act, &mtx );
		CLACT_AnmChg( work->actwork[i].act, c );
		CLACT_AnmReStart( work->actwork[i].act );
		CLACT_SetDrawFlag( work->actwork[i].act, TRUE );
	}
}

//--------------------------------------------------------------
///	EOA_H ボーナスカウント文字
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BCountFont =
{
	sizeof(CREDITFWORK),
	eoaBCountFont_Init,
	eoaBCountFont_Delete,
	eoaBCountFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA ゲット枚数文字
//==============================================================================
//--------------------------------------------------------------
///	GETCOINFWORK
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	CLACT_WORK_EX actwork[5];
}GETCOINFWORK;

static const EOA_H_NPP DATA_EoaH_GetCoinFont;

//--------------------------------------------------------------
/**
 * ゲット枚数文字初期化
 * @param	main	SLOTMAIN
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_GetCountFontInit( SLOTMAIN *main )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(14), SUBD_NFX32(8), 0 };
	
	eoa = EOA_Add_NPP( main->eoa_sys, &DATA_EoaH_GetCoinFont, &mtx, 0, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA 獲得枚数初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaGetCoinFont_Init( EOA_PTR eoa, void *wk )
{
	int i;
	VecFx32 mtx = { NUM_FX32(220), SUBD_NFX32(184), 0 };
	GETCOINFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	
	for( i = 0; i < 5; i++, mtx.x += NUM_FX32(8) ){
		ClActAdd( work->main->clactset, &work->actwork[i], &mtx, G2D_2DSUB, CELL_VRAM,
			SLOT_CHARID_BONUSGETFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_BONUSGETFONT,
			SLOT_ANMID_BONUSGETFONT, BGPRI2, CAPRI_BONUS_FONT );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 獲得枚数　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaGetCoinFont_Delete( EOA_PTR eoa, void *wk )
{
	GETCOINFWORK *work = wk;
	int i; for( i = 0; i < 5; i++ ){ ClActDelete( &work->actwork[i] ); }
}

//--------------------------------------------------------------
/**
 * EOA 獲得枚数　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaGetCoinFont_Move( EOA_PTR eoa, void *wk )
{
	int i;
	GETCOINFWORK *work = wk;
	DDISPCONTROL *dcont = &work->main->ddispcont;
	
	{
		int draw = TRUE;
		if( dcont->bonus_font_vanish_flag == TRUE ){ draw = FALSE; }
		for( i = 0; i < 5; CLACT_SetDrawFlag(work->actwork[i].act,draw), i++ ){}
		if( draw == FALSE ){ return; }
	}
	
	{
		int keta;
		int i = 0,c,count;
		
		count = work->main->bonus_get_coin;
		
		if( count > SLOT_COIN_MAX ){
			count = SLOT_COIN_MAX;
		}
		
		for( keta = 10000; keta >= 1; keta /= 10, i++ ){
			c = (count % (keta*10)) / keta;
			CLACT_AnmChg( work->actwork[i].act, c );
			CLACT_AnmReStart( work->actwork[i].act );
		}
	}
}

//--------------------------------------------------------------
///	EOA_H 獲得枚数
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_GetCoinFont =
{
	sizeof(GETCOINFWORK),
	eoaGetCoinFont_Init,
	eoaGetCoinFont_Delete,
	eoaGetCoinFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA 枚数大文字
//==============================================================================
//--------------------------------------------------------------
///	BIGGETCOINFWORK
//--------------------------------------------------------------
typedef struct
{
	BIGFONTTYPE type;
	u32 param;
	u32 keta;
	int frame;
	int add_count;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork[5];
}BIGCOUNTFWORK;

static const EOA_H_NPP DATA_EoaH_BigCountFont;

//--------------------------------------------------------------
/**
 * 枚数大文字初期化
 * @param	main	SLOTMAIN
 * @param	type	BIGFONTTYPE
 * @retval	EOA_PTR	eoa
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_BigCountFont( SLOTMAIN *main, BIGFONTTYPE type )
{
	EOA_PTR eoa;
	VecFx32 mtx = {0,0,0};
	u32 param;
	
	eoa = EOA_Add_NPP(
		main->eoa_sys, &DATA_EoaH_BigCountFont, &mtx, type, main, TCBPRI_BONUSFONT );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA　枚数大文字　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaBigCountFont_Init( EOA_PTR eoa, void *wk )
{
	int i,keta,c;
	VecFx32 mtx;
	VecFx32 affoffs = { 0,0,0 };
	VecFx32 scale = { 0x2000,0x2000,0};
	BIGCOUNTFWORK *work = wk;
	SLOTMAIN *main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	
	work->type = EOA_AddParamGet( eoa );
	work->main = main;
	
	if( work->type == BIGFONT_COUNT ){
		work->param = main->bonus_continue_count;
#ifdef DEBUG_BEND_FONT_COUNT
		work->param = DEBUG_BEND_FONT_COUNT;
#endif
		if( work->param > 999 ){ work->param = 999; }
		if( work->param >= 100 ){ work->keta = 3; }
		else if( work->param >= 10 ){ work->keta = 2; }
		else{ work->keta = 1; }
		mtx.x = NUM_FX32( 128 + (((4 + 5)*16)/2) );	//6=bonus 5=keta
		mtx.y = SUBD_NFX32( 96 + BIGFONT_OFFS_Y );
	}else{
		work->param = main->bonus_get_coin;
#ifdef DEBUG_BEND_FONT_COIN
		work->param = DEBUG_BEND_FONT_COIN;
#endif
		if( work->param > 99999 ){ work->param = 99999; }
		if( work->param >= 10000 ){ work->keta = 5; }
		else if( work->param >= 1000 ){ work->keta = 4; }
		else if( work->param >= 100 ){ work->keta = 3; }
		else if( work->param >= 10 ){ work->keta = 2; }
		else{ work->keta = 1; }
		mtx.x = NUM_FX32( 128 + (((4 + 5)*16)/2) );	//6=bonus 5=keta
		mtx.y = SUBD_NFX32( 96 - BIGFONT_OFFS_Y );
	}
	
	for( i = 0, keta = 1; i < work->keta; i++, keta *= 10, mtx.x -= NUM_FX32(16) ){
		ClActAdd( work->main->clactset, &work->actwork[i], &mtx, G2D_2DSUB, CELL_VRAM,
			SLOT_CHARID_BONUSGETFONT, SLOT_PLTTID_BONUSFONT, SLOT_CELLID_BONUSGETFONT,
			SLOT_ANMID_BONUSGETFONT, BGPRI2, CAPRI_BONUS_FONT );
		
		CLACT_SetAffineParam( work->actwork[i].act, CLACT_AFFINE_DOUBLE );
		CLACT_SetAffineMatrix( work->actwork[i].act, &affoffs );
		CLACT_SetScale( work->actwork[i].act, &scale );
		CLACT_SetRotation( work->actwork[i].act, RotKeyR(0) );
		
		c = (work->param % (keta*10)) / keta;
		CLACT_AnmChg( work->actwork[i].act, c );
		CLACT_AnmReStart( work->actwork[i].act );
	}
	
	work->add_count = i;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 枚数大文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigCountFont_Delete( EOA_PTR eoa, void *wk )
{
	int i;
	BIGCOUNTFWORK *work = wk;
	
	for( i = 0; i < work->add_count; i++ ){
		ClActDelete( &work->actwork[i] );
	}
}

//--------------------------------------------------------------
/**
 * EOA 枚数大文字　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaBigCountFont_Move( EOA_PTR eoa, void *wk )
{
	int i;
	BIGCOUNTFWORK *work = wk;
	
	work->frame++;
	
	if( work->frame >= 45 ){
		EOA_Delete( eoa );
	}
}

//--------------------------------------------------------------
///	EOA_H 枚数大文字
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_BigCountFont =
{
	sizeof(BIGCOUNTFWORK),
	eoaBigCountFont_Init,
	eoaBigCountFont_Delete,
	eoaBigCountFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	EOA ボーナス回数文字
//==============================================================================
//--------------------------------------------------------------
///	MOONFWORK
//--------------------------------------------------------------
typedef struct
{
	int frame;
	int add_count;
	SLOTMAIN *main;
	CLACT_WORK_EX actwork[3];
}MOONFWORK;

static const EOA_H_NPP DATA_EoaH_MoonFont;

//--------------------------------------------------------------
/**
 * ボーナス回数文字初期化
 * @param	main	SLOTMAIN
 * @param	count	表示数値
 * @retval	EOA_PTR	EOA
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_MoonFontInit( SLOTMAIN *main, u32 count )
{
	EOA_PTR eoa;
	VecFx32 mtx = { NUM_FX32(128), SUBD_NFX32(32), 0 };
	
	if( count > 999 ){
		count = 999;
	}
	
	eoa = EOA_Add_NPP( main->eoa_sys,&DATA_EoaH_MoonFont,&mtx, count, main, TCBPRI_BONUSFONT );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA	ボーナス回数文字　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常 FALSE=異常
 */
//--------------------------------------------------------------
static int eoaMoonFont_Init( EOA_PTR eoa, void *wk )
{
	int i;
	u32 count,keta,no;
	VecFx32 mtx;
	MOONFWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	count = EOA_AddParamGet( eoa );
	EOA_MatrixGet( eoa, &mtx );
	
	if( count >= 100 ){
		keta = 100;
		work->add_count = 3;
		mtx.x -= NUM_FX32( 16 );
	}else if( count >= 10 ){
		keta = 10;
		work->add_count = 2;
		mtx.x -= NUM_FX32( 8 );
	}else{
		keta = 1;
		work->add_count = 1;
	}
	
	for( i = 0; i < work->add_count; i++, mtx.x += NUM_FX32(16), keta /= 10 ){
		ClActAdd( work->main->clactset, &work->actwork[i], &mtx, G2D_2DSUB, CELL_VRAM,
			SLOT_CHARID_MOONFONT, SLOT_PLTTID_MOONFONT, SLOT_CELLID_MOONFONT,
			SLOT_ANMID_MOONFONT, BGPRI2, CAPRI_BONUS_FONT );
		
		no = (count % (keta*10)) / keta;
		CLACT_AnmChg( work->actwork[i].act, no ); 
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ボーナス回数文字　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaMoonFont_Delete( EOA_PTR eoa, void *wk )
{
	MOONFWORK *work = wk;
	int i;
	for( i = 0; i < work->add_count; i++ ){ ClActDelete( &work->actwork[i] ); }
}

//--------------------------------------------------------------
/**
 * EOA ボーナス回数　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaMoonFont_Move( EOA_PTR eoa, void *wk )
{
	int i;
	MOONFWORK *work = wk;
	
	work->frame++;
	
	if( work->frame >= 60 ){
		EOA_Delete( eoa );
	}
}

//--------------------------------------------------------------
///	EOA_H ボーナス回数　文字
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_MoonFont =
{
	sizeof(MOONFWORK),
	eoaMoonFont_Init,
	eoaMoonFont_Delete,
	eoaMoonFont_Move,
	EOA_DrawProcDummy,
};

//==============================================================================
//	ビッグヒット絵柄	
//==============================================================================
//--------------------------------------------------------------
///	BIGHITWORK
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int end_flag;
	int trans_flag;
	int frame;
	int count;
	int graphic_del;
	REEL_PATTERN type;
	LINENO line;
	CLACT_WORK_EX actwork[3];
	SLOTMAIN *main;
}BIGHITWORK;

static const EOA_H_NPP DATA_EoaH_ReelBigHit;
static void ReelBigHit_GraphicInit( BIGHITWORK *work );

//--------------------------------------------------------------
/**
 * リール大当たり絵柄表示
 * @parama	main	SLOTMAIN
 * @retval	EOA_PTR	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR SlotSubEoa_ReelBigHitInit( SLOTMAIN *main )
{
	VecFx32 mtx = { 0,0,0 };
	EOA_PTR eoa = EOA_Add_NPP( main->eoa_sys,
		&DATA_EoaH_ReelBigHit, &mtx, 0, main, TCBPRI_REEL_BIGHIT );
	return( eoa );
}

#define BIGHIT_Y(a) (NUM_FX32(REEL_PT_V_OFFSET)+(NUM_FX32(REEL_PT_V_SIZE*(a))))

static const VecFx32 DATA_ReelBigHitTbl[LINE_MAX][3] =
{
	{
		{ NUM_FX32(68), BIGHIT_Y(2), 0 },
		{ NUM_FX32(128), BIGHIT_Y(2), 0 },
		{ NUM_FX32(188), BIGHIT_Y(2), 0 },
	},
	{
		{ NUM_FX32(68), BIGHIT_Y(1), 0 },
		{ NUM_FX32(128), BIGHIT_Y(1), 0 },
		{ NUM_FX32(188), BIGHIT_Y(1), 0 },
	},
	{
		{ NUM_FX32(68), BIGHIT_Y(3), 0 },
		{ NUM_FX32(128), BIGHIT_Y(3), 0 },
		{ NUM_FX32(188), BIGHIT_Y(3), 0 },
	},
	{
		{ NUM_FX32(68), BIGHIT_Y(1), 0 },
		{ NUM_FX32(128), BIGHIT_Y(2), 0 },
		{ NUM_FX32(188), BIGHIT_Y(3), 0 },
	},
	{
		{ NUM_FX32(68), BIGHIT_Y(3), 0 },
		{ NUM_FX32(128), BIGHIT_Y(2), 0 },
		{ NUM_FX32(188), BIGHIT_Y(1), 0 },
	},
};

//--------------------------------------------------------------
/**
 * EOA 絵柄ビッグヒット　初期化
 * @param	eoa		EOA_PTR
 * @param	wk		EOA work
 * @retval	int		TRUE=正常終了
 */
//--------------------------------------------------------------
static int eoaReelBigHit_Init( EOA_PTR eoa, void *wk )
{
	u32 bit;
	BIGHITWORK *work = wk;
	
	work->main = (SLOTMAIN *)EOA_AddPtrGet( eoa );
	work->type = work->main->reel_hit_pattern;
	
	bit = work->main->reel_hit_line_bit;
	
	do{	if( (bit & 0x01) ){ break; }
		bit >>= 1; work->line++;
	}while( work->line < LINE_MAX );
	
	GF_ASSERT( work->line < LINE_MAX && "SLOT ERROR BIG PAT" );
	
	ReelBigHit_GraphicInit( work );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ビッグヒット絵柄　削除
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaReelBigHit_Delete( EOA_PTR eoa, void *wk )
{
	int i;
	BIGHITWORK *work = wk;
	
	if( work->graphic_del == FALSE ){
		for( i = 0; i < 3; i++ ){
			if( work->actwork[i].act != NULL ){
				ClActDelete( &work->actwork[i] );
			}
		}
	
		ClActGraphicDelete( work->main->clactset,
			SLOT_CHARID_BIGHIT, SLOT_PLTTID_MAX, SLOT_CELLID_BIGHIT, SLOT_ANMID_BIGHIT );
	}
}

//--------------------------------------------------------------
/**
 * EOA ビッグヒット絵柄　動作
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void eoaReelBigHit_Move( EOA_PTR eoa, void *wk )
{
	int i,flag;
	VecFx32 mtx;
	BIGHITWORK *work = wk;
	
	switch( work->seq_no ){
	case 0:
		if( work->trans_flag != TRANS_END ){
			break;
		}
		
		for( i = 0; i < 3; i++ ){
			mtx = DATA_ReelBigHitTbl[work->line][i];
			ClActAdd( work->main->clactset, &work->actwork[i], &mtx, G2D_2DMAX, CELL_VRAM,
			SLOT_CHARID_BIGHIT, SLOT_PLTTID_REEL, SLOT_CELLID_BIGHIT,
			SLOT_ANMID_BIGHIT, BGPRI1, CAPRI_BIGHIT_REEL );
			CLACT_SetAnmFlag( work->actwork[i].act, 1 );
		}
			
		work->seq_no++;
		break;
	case 1:
		for( i = 0, flag = FALSE; i < 3; i++ ){
			ClActMatrixGet( work->actwork[i].act, &mtx );
			mtx.y += NUM_FX32( 4 );
			
			if( mtx.y >= SUBD_NFX32(48) ){
				mtx.y = SUBD_NFX32( 48 );
			}else{
				flag = TRUE;			//move
			}
			
			CLACT_SetMatrix( work->actwork[i].act, &mtx );
		}
		
		if( flag == FALSE ){
			work->seq_no++;
		}
		
		break;
	case 2:
		work->frame++;
		
		if( work->frame >= 30 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 3:
		work->frame++;
		
		if( work->frame < 12 ){
			flag = FALSE;
		}else{
			flag = TRUE;
		}
		
		for( i = 0; i < 3; i++ ){
			CLACT_SetDrawFlag( work->actwork[i].act, flag );
		}
		
		if( work->frame >= 30 ){
			work->frame = 0;
			work->count++;
			
			if( work->count >= 3 ){
				work->count = 0;
				work->seq_no++;
			}
		}

		break;
	case 4:
		work->frame++;
		
		if( work->frame >= 30 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 5:
		for( i = 0; i < 3; i++ ){
			ClActDelete( &work->actwork[i] );
		}
		
		ClActGraphicDelete( work->main->clactset,
			SLOT_CHARID_BIGHIT, SLOT_PLTTID_MAX, SLOT_CELLID_BIGHIT, SLOT_ANMID_BIGHIT );
		
		work->seq_no++;
		work->end_flag = TRUE;
		work->graphic_del = TRUE;
	}
}

//--------------------------------------------------------------
///	EOA_H ビッグヒット絵柄
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_ReelBigHit =
{
	sizeof(BIGHITWORK),
	eoaReelBigHit_Init,
	eoaReelBigHit_Delete,
	eoaReelBigHit_Move,
	EOA_DrawProcDummy,
};

//--------------------------------------------------------------
/**
 * ビッグヒット絵柄　VRAM転送
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelBigHit_VramTransTCB( TCB_PTR tcb, void *wk )
{
	BIGHITWORK *work = wk;
	SLOTMAIN *main = work->main;
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BIGHIT );
	work->trans_flag = TRANS_SET;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * ビッグヒット絵柄　VRAM転送後のリソース開放
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelBigHit_VramResDeleteTCB( TCB_PTR tcb, void *wk )
{
	BIGHITWORK *work = wk;
	SLOTMAIN *main = work->main;
	
	if( work->trans_flag == TRANS_SET ){
		ClActCharResDelete( main->clactset, SLOT_CHARID_BIGHIT );
		work->trans_flag = TRANS_END;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * 絵柄ビッグヒット　グラフィック　初期化
 * @param	main	SLOTMAIN
 * @param	type	ボールタイプ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ReelBigHit_GraphicInit( BIGHITWORK *work )
{
	TCB_PTR tcb;
	SLOTMAIN *main = work->main;
	
	if( work->type == REEL_RED7 ){
		ClActCharAdd( main->clactset, G2D_2DMAX,
			main->arc_handle, NARC_slot_reel_7_NCGR, SLOT_CHARID_BIGHIT );
		ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_reel_7_NCER, SLOT_CELLID_BIGHIT );
		ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_reel_7_NANR, SLOT_ANMID_BIGHIT );
	}else{
		ClActCharAdd( main->clactset, G2D_2DMAX,
			main->arc_handle, NARC_slot_reel_ginga_NCGR, SLOT_CHARID_BIGHIT );
		ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_reel_ginga_NCER, SLOT_CELLID_BIGHIT );
		ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_reel_ginga_NANR, SLOT_ANMID_BIGHIT );
	}
	
	tcb = VIntrTCB_Add( ReelBigHit_VramTransTCB, work, VINTRTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
	tcb = VWaitTCB_Add( ReelBigHit_VramResDeleteTCB, work, VWAITTCBPRI_MBALLTRANS );
	GF_ASSERT( tcb != NULL );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	絵柄別セルアニメID	REEL_TYPEの並びに一致
//--------------------------------------------------------------
static const REELANMNO DATA_ReelTypeCellAnimeNoTbl[REEL_PATTERN_MAX] =
{
	REELANMNO_RED7,
	REELANMNO_BLUE7,
	REELANMNO_REPLAY,
	REELANMNO_CHERRY,
	REELANMNO_PIKA,
	REELANMNO_STONE,
};

//--------------------------------------------------------------
///	クレジット　文字別Xオフセット 0-9
//--------------------------------------------------------------
static const fx32 DATA_CreditFontXOffsetTbl[10] =
{
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
};

//--------------------------------------------------------------
///	ペイアウト　文字別Xオフセット 0-9
//--------------------------------------------------------------
static const fx32 DATA_PayOutFontXOffsetTbl[10] =
{
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
	NUM_FX32(0),
};

//--------------------------------------------------------------
///	モンスターボールまとめ BALLTYPEの並びに一致
//--------------------------------------------------------------
static const CELLARCDATA DATA_MonsBallArcDataTbl[BALL_MAX] =
{
 {NARC_slot_ball_mon_NCGR,NARC_slot_ball_mon_NCLR,NARC_slot_ball_mon_NCER,NARC_slot_ball_mon_NANR},
 {NARC_slot_ball_sup_NCGR,NARC_slot_ball_sup_NCLR,NARC_slot_ball_sup_NCER,NARC_slot_ball_sup_NANR},
 {NARC_slot_ball_hyp_NCGR,NARC_slot_ball_hyp_NCLR,NARC_slot_ball_hyp_NCER,NARC_slot_ball_hyp_NANR},
 {NARC_slot_ball_saf_NCGR,NARC_slot_ball_saf_NCLR,NARC_slot_ball_saf_NCER,NARC_slot_ball_saf_NANR},
 {NARC_slot_ball_pre_NCGR,NARC_slot_ball_pre_NCLR,NARC_slot_ball_pre_NCER,NARC_slot_ball_pre_NANR},
};

//--------------------------------------------------------------
///	ピッピまとめ BALLTYPEの並びに一致
//--------------------------------------------------------------
static const CELLARCDATA DATA_PipArcDataTbl[PIP_MAX] =
{
 {NARC_slot_slot_pippi_NCGR,NARC_slot_slot_pippi_NCLR,NARC_slot_slot_pippi_NCER,NARC_slot_slot_pippi_NANR},
 {NARC_slot_meta_pippi_NCGR,NARC_slot_slot_pippi_NCLR,NARC_slot_meta_pippi_NCER,NARC_slot_meta_pippi_NANR},
 {NARC_slot_slot_pippi_NCGR,NARC_slot_pippi_rare_NCLR,NARC_slot_slot_pippi_NCER,NARC_slot_slot_pippi_NANR},
};

