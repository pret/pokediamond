//******************************************************************************
/**
 *
 * @file	fieldobj_draw_0.c
 * @brief	フィールドOBJ 基本描画系その0
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "fieldobj_draw_legendpoke.h"

#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	BLACT00_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s16 old_dir;
	s16 frame;
	int old_state;
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
}BLACT00_WORK;

#define BLACT00_WORK_SIZE (sizeof(BLACT00_WORK))

//--------------------------------------------------------------
///	BLACTKOIKING_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s8 old_dir;
	s8 frame;
	s8 wait;
	s8 old_state;
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
}BLACTKOIKING_WORK;

#define BLACTKOIKING_WORK_SIZE (sizeof(BLACTKOIKING_WORK))

//--------------------------------------------------------------
///	BLACTHERO_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	s8 old_dir;
	s8 frame;
	s8 old_state;
	u8 be_dash_bit:1;
	u8 seq_no:7;
	
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
}BLACTHERO_WORK;

#define BLACTHERO_WORK_SIZE (sizeof(BLACTHERO_WORK))

//--------------------------------------------------------------
///	MODEL00_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	EOA_PTR eoa;
}MODEL00_WORK;

#define MODEL00_WORK_SIZE (sizeof(MODEL00_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
void FieldOBJ_DrawBlAct00_Init( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawBlAct00_Delete( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawBlAct00_Push( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawBlAct00_Pop( FIELD_OBJ_PTR fldobj );

void FieldOBJ_DrawBlAct00_Draw( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawBlAct00AnmNon_Draw( FIELD_OBJ_PTR fldobj );

static void DrawBlAct00Draw_STA_STOP(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_32F_16F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_8F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_4F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_2F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_6F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );
static void DrawBlAct00Draw_STA_WALK_3F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir );

void (* const DATA_DrawBlAct00_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACT00_WORK *, int );

void (* const DATA_DrawBlActPcwoman_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACT00_WORK *, int );

static void DrawBlActeroDraw_STA_DASH_4F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir );

void (* const DATA_DrawBlActHero_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int );

static void DrawBlActHeroDraw_STA_TAKE_OFF_16F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir );
static void DrawBlActHeroDraw_STA_TAKE_OFF_8F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir );

void (* const DATA_DrawBlActHeroCycle_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int );

void FieldOBJ_DrawModel00_Init( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawModel00_Draw( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawModel00_Delete( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawModel00_Push( FIELD_OBJ_PTR fldobj );
void FieldOBJ_DrawModel00_Pop( FIELD_OBJ_PTR fldobj );

static void Draw_BlActAnmFrameStepSet( BLACT_WORK_PTR act, int step_frame );
static void Draw_BlActAnmFrameStopSet( BLACT_WORK_PTR act );
static void Draw_BlActAnmFrameStepSetOffsChg( BLACT_WORK_PTR act, int offs, int step_frame );
static void Draw_BlActAnmFrameStopSetOffsChg( BLACT_WORK_PTR act, int offs );
static void Draw_BlActFlagVanishSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act );

//==============================================================================
//	BlAct00
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクターポインタ取得
 * @param
 * @retval
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FieldOBJ_DrawBlAct00_BlActPtrGet( FIELD_OBJ_PTR fldobj )
{
	int code = FieldOBJ_OBJCodeGet( fldobj );
	
	switch( code ){
	case HERO:
	case HEROINE:
	case CYCLEHERO:
	case CYCLEHEROINE:
	case SPHERO:
	case SPHEROINE:
	case SWIMHERO:
	case SWIMHEROINE:
	case WATERHERO:
	case WATERHEROINE:
	case SAVEHERO:
	case SAVEHEROINE:
	case CONTESTHERO:
	case CONTESTHEROINE:
	case FISHINGHERO:
	case FISHINGHEROINE:
	case POKEHERO:
	case POKEHEROINE:
	case BANZAIHERO:
	case BANZAIHEROINE:
		{
			BLACTHERO_WORK *work;
			work = FieldOBJ_DrawProcWorkGet( fldobj );
			return( work->act );
		}
	case KOIKING:
		{
			BLACTKOIKING_WORK *work;
			work = FieldOBJ_DrawProcWorkGet( fldobj );
			return( work->act );
		}
	case SPPOKE1:
	case SPPOKE2:
	case SPPOKE3:
		{
			return( FieldOBJ_DrawLegend_GetBlActWorkPtr(fldobj) );
		}
	default:
		{
			BLACT00_WORK *work;
			work = FieldOBJ_DrawProcWorkGet( fldobj );
			return( work->act );
		}
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * BlAct00 初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00_Init( FIELD_OBJ_PTR fldobj )
{
	BLACT00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, BLACT00_WORK_SIZE );
	work->old_dir = DIR_NOT;
	FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	
	if( work->act != NULL ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00_Delete( FIELD_OBJ_PTR fldobj )
{
	BLACT00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDelete( fldobj, &work->act );
}

//--------------------------------------------------------------
/**
 * BlAct00 退避。
 * 描画に必要な情報を退避し、描画で使用したモノを削除
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00_Push( FIELD_OBJ_PTR fldobj )
{
	BLACT00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

//--------------------------------------------------------------
/**
 * BlAct00 復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00_Pop( FIELD_OBJ_PTR fldobj )
{
	int ret;
	BLACT00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

//==============================================================================
//	BlAct00	描画
//==============================================================================
//--------------------------------------------------------------
/**
 * BlAct00 描画。
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACT00_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	GF_ASSERT( state < DRAW_STA_MAX && "FieldOBJ_DrawBlAct00_Draw()描画ステータス異常" );
	DATA_DrawBlAct00_DrawTbl[state]( fldobj, act, work, dir );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlAct00 描画。アニメなし
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00AnmNon_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,no;
	BLACT00_WORK *work;
	BLACT_WORK_PTR act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;													//追加中
	}
	
	act = work->act;
	
	if( act == NULL ){
		return;
	}
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlAct00 描画。１パターンアニメ
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlAct00AnmOneP_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,no;
	BLACT00_WORK *work;
	BLACT_WORK_PTR act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;													//追加中
	}
	
	act = work->act;
	
	if( act == NULL ){
		return;
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_STOP
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_STOP(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else{
		Draw_BlActAnmFrameStopSet( act );
	}
	
	BLACT_AnmFrameChg( act, 0 );	//画面反映
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_32F 16F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_32F_16F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_05 );
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_8F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_8F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_4F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_4F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_2 );
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_2F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_2F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_4 );
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_6F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_6F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}
	
	if( work->old_state != DRAW_STA_WALK_6F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_2,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_2, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
			
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_3F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_3F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}
		
	if(	work->old_state != DRAW_STA_WALK_3F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_3,
			BLACTANM_FRAME_2,
			BLACTANM_FRAME_3, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * BlAct00 DRAW_STA_WALK_7F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACT00_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlAct00Draw_STA_WALK_7F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}
	
	if( work->old_state != DRAW_STA_WALK_7F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_2,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,
			BLACTANM_FRAME_1, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
			
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
///	BlAct00 描画テーブル
//--------------------------------------------------------------
static void (* const DATA_DrawBlAct00_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACT00_WORK *, int ) =
{
	DrawBlAct00Draw_STA_STOP,
	DrawBlAct00Draw_STA_WALK_32F_16F,
	DrawBlAct00Draw_STA_WALK_32F_16F,
	DrawBlAct00Draw_STA_WALK_8F,
	DrawBlAct00Draw_STA_WALK_4F,
	DrawBlAct00Draw_STA_WALK_2F,
	DrawBlAct00Draw_STA_WALK_6F,
	DrawBlAct00Draw_STA_WALK_3F,
	DrawBlAct00Draw_STA_WALK_7F,
};

//==============================================================================
//	BlActPcwoman
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActPcwoman 描画。
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActPcWoman_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACT00_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	GF_ASSERT( state < DRAW_STA_PCWOMAN_MAX &&
			"FieldOBJ_DrawBlActPcwoman_Draw()描画ステータス異常" );
	DATA_DrawBlActPcwoman_DrawTbl[state]( fldobj, act, work, dir );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActPcwoman DRAW_STA_STOP
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActPcwoman_STA_STOP(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( dir != work->old_dir || work->old_state == DRAW_STA_PC_BOW ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else{
		Draw_BlActAnmFrameStopSet( act );
	}
	
	BLACT_AnmFrameChg( act, 0 );	//画面反映
}

//--------------------------------------------------------------
/**
 * BlActPcwoman DRAW_STA_PC_BOW
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActPcwoman_STA_PC_BOW(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACT00_WORK *work, int dir )
{
	if( work->old_state != DRAW_STA_PC_BOW ){
		BLACT_AnmOffsChg( act, 4 );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
}

//--------------------------------------------------------------
///	BlActPcwoman 描画テーブル
//--------------------------------------------------------------
static void (* const DATA_DrawBlActPcwoman_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACT00_WORK *, int ) =
{
	DrawBlActPcwoman_STA_STOP,
	DrawBlAct00Draw_STA_WALK_32F_16F,
	DrawBlAct00Draw_STA_WALK_32F_16F,
	DrawBlAct00Draw_STA_WALK_8F,
	DrawBlAct00Draw_STA_WALK_4F,
	DrawBlAct00Draw_STA_WALK_2F,
	DrawBlAct00Draw_STA_WALK_6F,
	DrawBlAct00Draw_STA_WALK_3F,
	DrawBlAct00Draw_STA_WALK_7F,
	
	DrawBlActPcwoman_STA_PC_BOW,
};

//==============================================================================
//	BlActKoiking
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActKoiking 初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActKoiking_Init( FIELD_OBJ_PTR fldobj )
{
	BLACTKOIKING_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, BLACTKOIKING_WORK_SIZE );
	work->old_dir = DIR_NOT;
	work->wait = gf_rand() % 16;
	FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	
	if( work->act != NULL ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * BlActKoiking 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActKoiking_Delete( FIELD_OBJ_PTR fldobj )
{
	BLACTKOIKING_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
}

//--------------------------------------------------------------
/**
 * BlActKoiking 退避。
 * 描画に必要な情報を退避し、描画で使用したモノを削除
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActKoiking_Push( FIELD_OBJ_PTR fldobj )
{
	BLACTKOIKING_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

//--------------------------------------------------------------
/**
 * BlActKoiking 復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActKoiking_Pop( FIELD_OBJ_PTR fldobj )
{
	int ret;
	BLACTKOIKING_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

//--------------------------------------------------------------
/**
 * BlActKoiking 描画。常にぴちぴち
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActKoiking_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTKOIKING_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	if( work->wait ){
		work->wait--;
		BLACT_AnmFrameChg( act, 0 );
	}else{
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
		work->frame++;
		
		if( work->frame >= 32 ){
			work->frame = 0;
			work->wait = gf_rand() % 16;
		}
	}
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//==============================================================================
//	BlActBird
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActBird 描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActBird_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACT00_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	switch( state ){
	case DRAW_STA_STOP:
		{
			int no;
			
			if( dir == DIR_UP || dir == DIR_DOWN ){
				no = 0;
			}else{
				no = 1;
			}
			
			if( BLACT_AnmOffsGet(act) != no || work->old_state == DRAW_STA_STOP ){
				BLACT_AnmOffsChg( act, no );
				BLACT_AnmFrameSetOffs( act, 0 );
				BLACT_AnmFrameChg( act, 0 );
			}
			
			BLACT_AnmFrameChg( act, 0 );
		}
		break;
	default:
		{
			int no;
			fx32 frame = 0;
			
			if( dir == DIR_UP || dir == DIR_DOWN ){
				no = 0;
			}else{
				no = 1;
			}
			
			if( BLACT_AnmOffsGet(act) != no ){
				BLACT_AnmOffsChg( act, no );
				BLACT_AnmFrameSetOffs( act, 0 );
			}
			
			BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
		}
		
		break;
	}
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//==============================================================================
//	BlActHero
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActHero 初期化。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHero_Init( FIELD_OBJ_PTR fldobj )
{
	BLACTHERO_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, BLACTHERO_WORK_SIZE );
	work->old_dir = DIR_NOT;
	FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	
	if( work->act != NULL ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHero_Delete( FIELD_OBJ_PTR fldobj )
{
	BLACTHERO_WORK *work;
	VecFx32 vec = {0,0,0};
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_VecDrawOffsSet( fldobj, &vec );
}

//--------------------------------------------------------------
/**
 * BlActHero 退避。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHero_Push( FIELD_OBJ_PTR fldobj )
{
	BLACTHERO_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDelete( fldobj, &work->act );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

//--------------------------------------------------------------
/**
 * BlActHero 復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHero_Pop( FIELD_OBJ_PTR fldobj )
{
	int ret;
	BLACTHERO_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		FieldOBJ_BlActAddRegularGuest( fldobj, &work->act );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

//==============================================================================
//	BlActHero 描画
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActHero 自機描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHero_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	GF_ASSERT( state < DRAW_STA_MAX_HERO && "FieldOBJ_DrawBlActHero_Draw()描画ステータス異常" );
	DATA_DrawBlActHero_DrawTbl[state]( fldobj, act, work, dir );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_STOP
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_STOP(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->be_dash_bit = FALSE;
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		//次のフレームで停止絵に変える
		work->be_dash_bit = TRUE;
	}else if( work->be_dash_bit == TRUE ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
		work->be_dash_bit = FALSE;
	}else{
		Draw_BlActAnmFrameStopSet( act );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_32F 16F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_32F_16F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int no;
	
	if( dir != work->old_dir ){
		no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		work->be_dash_bit = TRUE;
		return;
	}else if( work->be_dash_bit == TRUE ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
		work->be_dash_bit = FALSE;
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_05 );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_8F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_8F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int no;
	
	if( dir != work->old_dir ){
		no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_4F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_4F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_2 );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_2F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_2F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_4 );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_6F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_6F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
	
	if( work->old_state != DRAW_STA_WALK_6F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_1,BLACTANM_FRAME_1,BLACTANM_FRAME_2,
			BLACTANM_FRAME_1,BLACTANM_FRAME_1,BLACTANM_FRAME_2, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_3F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_3F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
		
	if(	work->old_state != DRAW_STA_WALK_3F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_3,BLACTANM_FRAME_2,BLACTANM_FRAME_3, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_WALK_7F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_WALK_7F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	if( dir != work->old_dir ){
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->frame = 0;
	}else if( work->old_state == DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStopSetOffsChg( act, FieldOBJ_BlActAnmOffsNo_DirWalkGet(dir) );
	}
	
	if( work->old_state != DRAW_STA_WALK_7F ){
		work->frame = 0;
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		fx32 tbl[] = {
			BLACTANM_FRAME_2,BLACTANM_FRAME_1,BLACTANM_FRAME_1,BLACTANM_FRAME_1,
			BLACTANM_FRAME_1,BLACTANM_FRAME_1,BLACTANM_FRAME_1, 0 };
				
		BLACT_AnmFrameChg( act, tbl[work->frame] );
		work->frame++;
			
		if( tbl[work->frame] == 0 ){
			work->frame = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_DASH_4F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_DASH_4F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int no;
	
	if( dir != work->old_dir ){
		no = FieldOBJ_BlActAnmOffsNo_DirDashGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state != DRAW_STA_DASH_4F ){
		Draw_BlActAnmFrameStepSetOffsChg(
			act, FieldOBJ_BlActAnmOffsNo_DirDashGet(dir), BLACTANM_STEP_DASH_FRAME );
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
}

//--------------------------------------------------------------
///	BlActHero 描画テーブル
//--------------------------------------------------------------
static void (* const DATA_DrawBlActHero_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int ) =
{
	DrawBlActHeroDraw_STA_STOP,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_8F,
	DrawBlActHeroDraw_STA_WALK_4F,
	DrawBlActHeroDraw_STA_WALK_2F,
	DrawBlActHeroDraw_STA_WALK_6F,
	DrawBlActHeroDraw_STA_WALK_3F,
	DrawBlActHeroDraw_STA_WALK_7F,
	DrawBlActHeroDraw_STA_DASH_4F,
};

//==============================================================================
//	BlActHeroCycle
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActHeroCycle 描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroCycle_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	GF_ASSERT( state < DRAW_STA_MAX_CYCLEHERO &&
			"FieldOBJ_DrawBlActHero_Draw()描画ステータス異常" );
	
	if( work->old_state == DRAW_STA_STOP &&
		state != work->old_state && work->be_dash_bit == FALSE ){
		work->old_dir = DIR_NOT;
	}
	
	DATA_DrawBlActHeroCycle_DrawTbl[state]( fldobj, act, work, dir );
	
	work->old_dir = dir;
	work->old_state = state;
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHeroCycle DRAW_STA_STOP
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroCycleDraw_STA_STOP(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int dirno[4] = { 6, 7, 8, 9 };
	int no = dirno[dir];
	
	if( dir != work->old_dir ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->be_dash_bit = FALSE;
	}else if( work->old_state != DRAW_STA_STOP ){
		work->be_dash_bit = TRUE;
	}else if( work->be_dash_bit == TRUE ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		work->be_dash_bit = FALSE;
	}else{
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
	
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_TAKE_OFF_4F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_TAKE_OFF_16F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int no;
	
	no = FieldOBJ_BlActAnmOffsNo_DirTakeOFFGet( dir );
	
	if( dir != work->old_dir || work->old_state != DRAW_STA_STOP ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state != DRAW_STA_TAKE_OFF_16F ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( BLACT_AnmOffsGet(act) != no ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_05 );
	}
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_TAKE_OFF_8F
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroDraw_STA_TAKE_OFF_8F(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	int no;
	
	no = FieldOBJ_BlActAnmOffsNo_DirTakeOFFGet( dir );
	
	if( dir != work->old_dir ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( work->old_state != DRAW_STA_TAKE_OFF_8F ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}else if( BLACT_AnmOffsGet(act) != no ){
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
		
	if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
}

//--------------------------------------------------------------
///	BlActHeroCycle 描画テーブル
//--------------------------------------------------------------
#if 0	//old
static void (* const DATA_DrawBlActHeroCycle_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int ) =
{
	DrawBlActHeroCycleDraw_STA_STOP,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_8F,
	DrawBlActHeroDraw_STA_WALK_4F,
	DrawBlActHeroDraw_STA_WALK_2F,
	DrawBlActHeroDraw_STA_WALK_6F,
	DrawBlActHeroDraw_STA_WALK_3F,
	DrawBlActHeroDraw_STA_TAKE_OFF_16F,
	DrawBlActHeroDraw_STA_TAKE_OFF_8F,
};
#else
static void (* const DATA_DrawBlActHeroCycle_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int ) =
{
	DrawBlActHeroCycleDraw_STA_STOP,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_32F_16F,
	DrawBlActHeroDraw_STA_WALK_8F,
	DrawBlActHeroDraw_STA_WALK_4F,
	DrawBlActHeroDraw_STA_WALK_6F,
	DrawBlActHeroDraw_STA_WALK_6F,
	DrawBlActHeroDraw_STA_WALK_6F,
	DrawBlActHeroDraw_STA_TAKE_OFF_16F,
	DrawBlActHeroDraw_STA_TAKE_OFF_8F,
};
#endif

//==============================================================================
//	BlActHeroFishing
//==============================================================================
void (* const DATA_DrawBlActHeroFishing_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int );
static void DrawBlActHeroFishOffset( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, int dir );

//--------------------------------------------------------------
///	釣りアニメオフセット番号　方向
//--------------------------------------------------------------
static const int DATA_FishAnmOffsNoDirTbl[] =
{ 0, 1, 2, 3 };

//--------------------------------------------------------------
/**
 * BlActHeroFishing 描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroFishing_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( act == NULL ||
		FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	GF_ASSERT( state < DRAW_STA_MAX_FISH &&
			"FieldOBJ_DrawBlActHero_Draw()描画ステータス異常" );
	DATA_DrawBlActHeroFishing_DrawTbl[state]( fldobj, act, work, dir );
	DrawBlActHeroFishOffset( fldobj, act, dir );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_FISH_END		0x00
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroFishDraw_STA_FISH_END(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	fx32 frame;
	
	if( dir != work->old_dir || work->old_state != DRAW_STA_FISH_END ){
		BLACT_AnmOffsChg( act, DATA_FishAnmOffsNoDirTbl[dir] );
		BLACT_AnmFrameSetOffs( act, NUM_FX32(15) );
	}
	
	frame = BLACT_AnmFrameGetOffs( act );
	frame -= BLACTANM_FRAME_1;
	if( frame < 0 ){ frame = 0; }
	BLACT_AnmFrameSetOffs( act, frame );
	BLACT_AnmFrameChg( act, 0 );
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_FISH_START
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroFishDraw_STA_FISH_START(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	fx32 frame;
	
	if( dir != work->old_dir || work->old_state != DRAW_STA_FISH_START ){
		BLACT_AnmOffsChg( act, DATA_FishAnmOffsNoDirTbl[dir] );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_FISH_ON
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroFishDraw_STA_FISH_ON(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	fx32 frame;
	
	if( dir != work->old_dir || work->old_state != DRAW_STA_FISH_ON ){
		BLACT_AnmOffsChg( act, DATA_FishAnmOffsNoDirTbl[dir] );
		BLACT_AnmFrameSetOffs( act, NUM_FX32(15) );
		work->seq_no = 0;
	}
	
	frame = BLACT_AnmFrameGetOffs( act );
	
	switch( work->seq_no ){
	case 0:
		frame -= BLACTANM_FRAME_1;
		if( frame <= NUM_FX32(10) ){ work->seq_no++; }
		break;
	case 1:
		frame += BLACTANM_FRAME_1;
		if( frame >= NUM_FX32(15) ){ work->seq_no++; work->frame = 0; }
		break;
	case 2:
		work->frame++;
		if( work->frame >= 30 ){ work->frame = 0; work->seq_no = 0; }
	}
	
	BLACT_AnmFrameSetOffs( act, frame );
	BLACT_AnmFrameChg( act, 0 );
}

//--------------------------------------------------------------
/**
 * BlActHero DRAW_STA_FISH_HIT
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	work	BLACTHERO_WORK *
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroFishDraw_STA_FISH_HIT(
		FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, BLACTHERO_WORK *work, int dir )
{
	fx32 frame;
	
	if( dir != work->old_dir || work->old_state != DRAW_STA_FISH_HIT ){
		BLACT_AnmOffsChg( act, DATA_FishAnmOffsNoDirTbl[dir] );
		BLACT_AnmFrameSetOffs( act, NUM_FX32(15) );
	}
	
	frame = BLACT_AnmFrameGetOffs( act ) - BLACTANM_FRAME_1;
	if( frame < 0 ){ frame = 0; }
	BLACT_AnmFrameSetOffs( act, frame );
	BLACT_AnmFrameChg( act, 0 );
}

//--------------------------------------------------------------
/**
 * 釣りアニメ番号別にオフセットセット
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @param	dir		表示方向DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void DrawBlActHeroFishOffset( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act, int dir )
{
	VecFx32 vec = {0,0,0};
	int frame = FX32_NUM( BLACT_AnmFrameGet(act) ); 
	
	switch( dir ){
	case DIR_UP:
		break;
	case DIR_DOWN:
		if( frame >= 24 ){ vec.z = NUM_FX32(6); }
		break;
	case DIR_LEFT:
		if( frame < 40 ){ vec.x = NUM_FX32(1); }
		else{ vec.x = NUM_FX32(-5); }
		break;
	case DIR_RIGHT:
		if( frame < 56 ){ vec.x = NUM_FX32(-1); }
		else{ vec.x = NUM_FX32(5); }
		break;
	}
	
	FieldOBJ_VecDrawOffsSet( fldobj, &vec );
}

//--------------------------------------------------------------
///	BlActHero 描画テーブル
//--------------------------------------------------------------
static void (* const DATA_DrawBlActHeroFishing_DrawTbl[])(
		FIELD_OBJ_PTR, BLACT_WORK_PTR, BLACTHERO_WORK *, int ) =
{
	DrawBlActHeroFishDraw_STA_FISH_END,
	DrawBlActHeroFishDraw_STA_FISH_START,
	DrawBlActHeroFishDraw_STA_FISH_ON,
	DrawBlActHeroFishDraw_STA_FISH_HIT,
};

//==============================================================================
//	BlActHero　その他
//==============================================================================
//--------------------------------------------------------------
/**
 * BlActHeroSwim 描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroSwim_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	{
		int no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
		BLACT_AnmFrameChg( act, 0 );
	}
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHeroSp 描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroSp_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	if( BLACT_AnmOffsGet(act) != 0 ){
		BLACT_AnmOffsChg( act, 0 );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHeroWater 描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroWater_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	switch( state ){
	case DRAW_STA_STOP:
		if( BLACT_AnmOffsGet(act) != 1 ){
			BLACT_AnmOffsChg( act, 1 );
			BLACT_AnmFrameSetOffs( act, 0 );
		}
		
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
		break;
	default:
		if( BLACT_AnmOffsGet(act) != 0 ){
			BLACT_AnmOffsChg( act, 0 );
			BLACT_AnmFrameSetOffs( act, 0 );
		}
		
		BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	}
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//--------------------------------------------------------------
/**
 * BlActHeroPoketch 描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroPoketch_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,no;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	
	if( dir != work->old_dir ){
		no = FieldOBJ_BlActAnmOffsNo_DirWalkGet( dir );
		BLACT_AnmOffsChg( act, no );
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
	
	work->old_dir = dir;
	work->old_state = FieldOBJ_DrawStatusGet( fldobj );
}

//--------------------------------------------------------------
/**
 * BlActHeroBanzai 描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawBlActHeroBanzai_Draw( FIELD_OBJ_PTR fldobj )
{
	int dir,state;
	BLACTHERO_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	BLACT_WORK_PTR act = work->act;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){		//追加中
		return;
	}
	
	if( act == NULL ){
		return;
	}
	
	dir = FieldOBJ_DirDispGet( fldobj );
	state = FieldOBJ_DrawStatusGet( fldobj );
	
	if( state != work->old_state ){
		if( state == DRAW_STA_BANZAI ){
			BLACT_AnmOffsChg( act, 0 );
		}else{
			BLACT_AnmOffsChg( act, 1);
		}
		
		BLACT_AnmFrameSetOffs( act, 0 );
	}
	
	BLACT_AnmFrameChg( act, BLACTANM_FRAME_1 );
	
	work->old_dir = dir;
	work->old_state = state;
	
	FieldOBJ_BlActPosSet( fldobj, act );
	Draw_BlActFlagVanishSet( fldobj, act );
}

//==============================================================================
//	ビルボードパーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 一歩停止フレームセット。
 * 余分フレームを削除し、停止アニメに反映。
 * @param	act		BLACT_WORK_PTR
 * @param	step_frame	一歩分のフレーム
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Draw_BlActAnmFrameStepSet( BLACT_WORK_PTR act, int step_frame )
{
	fx32 frame,mod;
	
	frame = BLACT_AnmFrameGetOffs( act );
	frame /= FX32_ONE;
	mod = frame % step_frame;
	frame -= mod;
	frame *= FX32_ONE;
	
	BLACT_AnmFrameSetOffs( act, frame );
	BLACT_AnmFrameChg( act, 0 );	//画面反映のみ
}

//--------------------------------------------------------------
/**
 * 標準停止フレームセット。
 * 余分フレームを削除し、停止アニメに反映。
 * @param	act		BLACT_WORK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Draw_BlActAnmFrameStopSet( BLACT_WORK_PTR act )
{
	Draw_BlActAnmFrameStepSet( act, BLACTANM_STEP_FRAME );
}

//--------------------------------------------------------------
/**
 * 現在の停止フレームを合わせた別オフセット停止
 * @param	act		BLACT_WORK_PTR
 * @param	offs	アニメオフセット
 * @param	step_frame	一歩分のフレーム
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Draw_BlActAnmFrameStepSetOffsChg( BLACT_WORK_PTR act, int offs, int step_frame )
{
	fx32 frame;
	
	Draw_BlActAnmFrameStepSet( act, step_frame );
	frame = BLACT_AnmFrameGetOffs( act );
	BLACT_AnmOffsChg( act, offs );
	BLACT_AnmFrameSetOffs( act, frame );
}

//--------------------------------------------------------------
/**
 * 現在の標準停止フレームを合わせた別オフセット停止
 * @param	act		BLACT_WORK_PTR
 * @param	offs	アニメオフセット
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Draw_BlActAnmFrameStopSetOffsChg( BLACT_WORK_PTR act, int offs )
{
	fx32 frame;
	
	Draw_BlActAnmFrameStopSet( act );
	frame = BLACT_AnmFrameGetOffs( act );
	BLACT_AnmOffsChg( act, offs );
	BLACT_AnmFrameSetOffs( act, frame );
}

//--------------------------------------------------------------
/**
 * 表示、非表示
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	act		BLACT_WORK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Draw_BlActFlagVanishSet( FIELD_OBJ_PTR fldobj, BLACT_WORK_PTR act )
{
	int vanish = TRUE;
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) == TRUE ){
		vanish = FALSE;
	}
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_GET_ERROR) == TRUE ){
		if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_HEIGHT_VANISH_OFF) == FALSE){
			vanish = FALSE;
		}
	}
		
	BLACT_ObjDrawFlagSet( act, vanish );
}

//==============================================================================
///	Model00
//==============================================================================
//--------------------------------------------------------------
/**
 * Model00 看板　初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Board_Init( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, MODEL00_WORK_SIZE );
	work->eoa = FE_FldOBJBoard_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 雪玉　初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_SnowBall_Init( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, MODEL00_WORK_SIZE );
	work->eoa = FE_FldOBJSnowBall_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 本　初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Book_Init( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, MODEL00_WORK_SIZE );
	work->eoa = FE_FldOBJBook_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 ドア２　初期化。
 * 描画の為の初期化を行う。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Door2_Init( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkInit( fldobj, MODEL00_WORK_SIZE );
	work->eoa = FE_FldOBJDoor2_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 描画。
 * フィールドOBJから描画に必要な情報を取得し、描画する。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Draw( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * Model00 削除関数。
 * 描画で使用したモノを削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Delete( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->eoa != NULL ){
		FE_EoaDelete( work->eoa );
		work->eoa = NULL;
	}
}

//--------------------------------------------------------------
/**
 * Model00 退避。
 * 描画に必要な情報を退避し、描画で使用したモノを削除
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Push( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->eoa != NULL ){
		FE_EoaDelete( work->eoa );
		work->eoa = NULL;
	}
}

//--------------------------------------------------------------
/**
 * Model00 看板　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Board_Pop( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	GF_ASSERT( work->eoa == NULL &&
			"FieldOBJ_DrawModel00_Pop()アクター初期化が出来ていない\n" );
	
	work->eoa = FE_FldOBJBoard_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 雪玉　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_SnowBall_Pop( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	GF_ASSERT( work->eoa == NULL &&
			"FieldOBJ_DrawModel00_Pop()アクター初期化が出来ていない\n" );
	
	work->eoa = FE_FldOBJSnowBall_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 本　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Book_Pop( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	GF_ASSERT( work->eoa == NULL &&
			"FieldOBJ_DrawModel00_Pop()アクター初期化が出来ていない\n" );
	
	work->eoa = FE_FldOBJBook_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * Model00 ドア２　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawModel00_Door2_Pop( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	GF_ASSERT( work->eoa == NULL &&
			"FieldOBJ_DrawModel00_Pop()アクター初期化が出来ていない\n" );
	
	work->eoa = FE_FldOBJDoor2_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * 雪球破壊開始　雪球専用
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSnowBallBreakSet( FIELD_OBJ_PTR fldobj )
{
	MODEL00_WORK *work;
	work = FieldOBJ_DrawProcWorkGet( fldobj );
	FE_FldOBJSnowBall_BreakAnimeSet( work->eoa );
	work->eoa = NULL;
}

