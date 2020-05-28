//******************************************************************************
/**
 *
 * @file	fieldobj_seed.c
 * @brief	フィールドOBJ 木の実
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "map_tool.h"
#include "fieldobj.h"
#include "field_effect.h"
#include "seedsys.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	デバッグ
//--------------------------------------------------------------
//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	MOVE_SEED_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	u16 state;
	u16 harvest_flag;
}MOVE_SEED_WORK;

#define MOVE_SEED_WORK_SIZE (sizeof(MOVE_SEED_WORK))

//--------------------------------------------------------------
//	DRAW_SEED_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	int draw_code;
	int draw_state;
	BLACT_WORK_PTR act;
	FIELD_OBJ_BLACTANM_PUSH act_push;
}DRAW_SEED_WORK;

#define DRAW_SEED_WORK_SIZE (sizeof(DRAW_SEED_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static int Seed_OBJCodeGet( int kind, int growth );

//==============================================================================
//	木の実
//==============================================================================
//--------------------------------------------------------------
/**
 * OBJコードが木の実かチェック
 * @param	code	HERO等
 * @retval	int		TRUE=木の実
 */
//--------------------------------------------------------------
int FieldOBJ_OBJCodeSeedCheck( int code )
{
	if( code == SEED ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJから種専用OBJコード取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		SEED等 OBJCODEMAX=無し
 */
//--------------------------------------------------------------
int FieldOBJ_OBJCodeSeedGet( CONST_FIELD_OBJ_PTR fldobj )
{
	{
		MOVE_SEED_WORK *move = FieldOBJ_MoveProcWorkGet( (FIELD_OBJ_PTR)fldobj );
	
		if( move->state == SEEDSTAT_NOTHING ){
			return( OBJCODEMAX );
		}
	}
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == TRUE ){
		DRAW_SEED_WORK *draw = FieldOBJ_DrawProcWorkGet( (FIELD_OBJ_PTR)fldobj );
		
		if( draw->draw_state != SEEDSTAT_NOTHING ){
			return( draw->draw_code );
		}
	}
	
	return( OBJCODEMAX );
}

//--------------------------------------------------------------
/**
 * 木の実収穫を知らせる
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_SeedHarvestFlagSet( FIELD_OBJ_PTR fldobj )
{
	MOVE_SEED_WORK *move = FieldOBJ_MoveProcWorkGet( fldobj );
	move->harvest_flag = TRUE;
}

//==============================================================================
//	木の実動作
//==============================================================================
//--------------------------------------------------------------
/**
 * MV_SEED　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSeed_Init( FIELD_OBJ_PTR fldobj )
{
	MOVE_SEED_WORK *work;
	
	work = FieldOBJ_MoveProcWorkInit( fldobj, MOVE_SEED_WORK_SIZE );
	work->state = SEEDSTAT_NOTHING;
}

//--------------------------------------------------------------
/**
 * MV_SEED　動作
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSeed_Move( FIELD_OBJ_PTR fldobj )
{
	MOVE_SEED_WORK *work;
	
	work = FieldOBJ_MoveProcWorkGet( fldobj );
	work->state = SeedSys_GetSeedStatus( FieldOBJ_FieldSysWorkGet(fldobj), fldobj );
}

//--------------------------------------------------------------
/**
 * MV_SEED　削除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_MoveSeed_Delete( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	木の実　描画
//==============================================================================
//--------------------------------------------------------------
/**
 * 木の実描画　初期化
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSeed_Init( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkInit( fldobj, DRAW_SEED_WORK_SIZE );
	work->draw_code = OBJCODEMAX;
	work->draw_state = SEEDSTAT_NOTHING;
	
	FE_FldOBJSeedGround_Add( fldobj );
}

//--------------------------------------------------------------
/**
 * 木の実描画　描画
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSeed_Draw( FIELD_OBJ_PTR fldobj )
{
	MOVE_SEED_WORK *move = FieldOBJ_MoveProcWorkGet( fldobj );
	DRAW_SEED_WORK *draw = FieldOBJ_DrawProcWorkGet( fldobj );
//	u32 new_state = move->state;
	u32 new_state = SeedSys_GetSeedStatus( FieldOBJ_FieldSysWorkGet(fldobj), fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){			//追加中
		return;
	}
	
	if( new_state != draw->draw_state ){							//更新
		FieldOBJ_BlActDeleteCodeCancel( fldobj, &draw->act, draw->draw_code );
		
		draw->draw_code = Seed_OBJCodeGet(							//新しい木の実OBJコード取得
				SeedSys_GetSeedType(FieldOBJ_FieldSysWorkGet(fldobj),fldobj),
				new_state );
		
		if( draw->draw_code != OBJCODEMAX ){						//表示すべき実がある
			if( draw->draw_state != SEEDSTAT_NOTHING ){
				FE_FldOBJSeedEff_Add( fldobj );
			}
			
			FieldOBJ_BlActAddRegularGuestCode( fldobj, &draw->act, draw->draw_code );
		}else{
			if( draw->draw_state != SEEDSTAT_NOTHING && 			//過去育成あり
				move->harvest_flag == FALSE ){						//収穫ではない
				FE_FldOBJSeedEff_Add( fldobj );
			}
		}
		
		move->harvest_flag = FALSE;
	}
	
	draw->draw_state = new_state;
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){			//追加中
		return;
	}
	
	if( draw->act != NULL ){
		FieldOBJ_BlActPosSet( fldobj, draw->act );
		
		if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
			BLACT_AnmFrameChg( draw->act, BLACTANM_FRAME_1 );
		}
		
		FieldOBJ_BlActFlagVanishSet( fldobj, draw->act );
	}
}

#if 0
void FieldOBJ_DrawSeed_Draw( FIELD_OBJ_PTR fldobj )
{
	MOVE_SEED_WORK *move = FieldOBJ_MoveProcWorkGet( fldobj );
	DRAW_SEED_WORK *draw = FieldOBJ_DrawProcWorkGet( fldobj );
	u32 new_state = move->state;
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){			//追加中
		return;
	}
	
	if( new_state != draw->draw_state ){							//更新
		if( draw->act != NULL ){									//現在のアクターを削除する
			FieldOBJ_BlActDeleteCode( fldobj, &draw->act, draw->draw_code );
		}
		
		draw->draw_code = Seed_OBJCodeGet(							//新しい木の実OBJコード取得
				SeedSys_GetSeedType(FieldOBJ_FieldSysWorkGet(fldobj),fldobj),
				new_state );
		
		if( draw->draw_code != OBJCODEMAX ){						//表示すべき実がある
			if( draw->draw_state != SEEDSTAT_NOTHING ){
				FE_FldOBJSeedEff_Add( fldobj );
			}
			
			FieldOBJ_BlActAddRegularGuestCode( fldobj, &draw->act, draw->draw_code );
		}else{
			if( draw->draw_state != SEEDSTAT_NOTHING && 			//過去育成あり
				move->harvest_flag == FALSE ){						//収穫ではない
				FE_FldOBJSeedEff_Add( fldobj );
			}
		}
		
		move->harvest_flag = FALSE;
	}
	
	draw->draw_state = new_state;
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){			//追加中
		return;
	}
	
	if( draw->act != NULL ){
		FieldOBJ_BlActPosSet( fldobj, draw->act );
		
		if( FieldOBJ_DrawPauseCheck(fldobj) == FALSE ){
			BLACT_AnmFrameChg( draw->act, BLACTANM_FRAME_1 );
		}
		
		FieldOBJ_BlActFlagVanishSet( fldobj, draw->act );
	}
}
#endif

//--------------------------------------------------------------
/**
 * 木の実描画　削除
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSeed_Delete( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDeleteCodeCancel( fldobj, &work->act, work->draw_code );
}

#if 0
void FieldOBJ_DrawSeed_Delete( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	FieldOBJ_BlActDelete( fldobj, &work->act );
}
#endif

//--------------------------------------------------------------
/**
 * 木の実描画　退避
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSeed_Push( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
	}
	
	FieldOBJ_BlActDeleteCodeCancel( fldobj, &work->act, work->draw_code );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
}

#if 0
void FieldOBJ_DrawSeed_Push( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPush( work->act, &work->act_push );
		FieldOBJ_BlActDeleteCode( fldobj, &work->act, work->draw_code );
		
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}
#endif

//--------------------------------------------------------------
/**
 * 木の実描画　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawSeed_Pop( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		if( work->draw_code != OBJCODEMAX ){
			FieldOBJ_BlActAddRegularGuestCode( fldobj, &work->act, work->draw_code );
		}else{
			FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
		}
		
		FE_FldOBJSeedGround_Add( fldobj );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}

#if 0
void FieldOBJ_DrawSeed_Pop( FIELD_OBJ_PTR fldobj )
{
	DRAW_SEED_WORK *work = FieldOBJ_DrawProcWorkGet( fldobj );
	
	if( FieldOBJ_BlActAddPracFlagCheck(fldobj) == TRUE ){
		return;
	}
	
	if( work->act == NULL ){
		if( work->draw_code != OBJCODEMAX ){
			FieldOBJ_BlActAddRegularGuestCode( fldobj, &work->act, work->draw_code );
		}
		
		FE_FldOBJSeedGround_Add( fldobj );
	}
	
	if( work->act != NULL ){
		FieldOBJ_BlActAnmPop( work->act, &work->act_push );
		FieldOBJ_BlActPosSet( fldobj, work->act );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_DRAW_PUSH );
	}
}
#endif

//==============================================================================
//	木の実　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 木の実種類、成長段階からOBJコード取得
 * @param	kind		種類 1origin
 * @param	growth		成長段階
 * @retval	int			SEED00等 OBJCODEMAX=無し
 */
//--------------------------------------------------------------
static int Seed_OBJCodeGet( int kind, int growth )
{
	switch( growth ){
	case SEEDSTAT_NOTHING:		return( OBJCODEMAX );
	case SEEDSTAT_UNDERGROUND:	return( OBJCODEMAX );
	default:
		{
			kind--;			//1ori->0ori
			
			#ifdef PM_DEBUG
			if( kind < 0 || kind >= 64 ){
				OS_Printf("木の実種類が異常です!! 木の実種類=0x%x\n",kind+1);GF_ASSERT(0);
			}
			#endif
			
			{
				const OBJCODE_SEEDDATA *tbl = &DATA_OBJCodeSeedDataTbl[kind];
				switch( growth ){
				case SEEDSTAT_HUTABA:		return( SEED00 );
				case SEEDSTAT_MIKI:			return( tbl->code_miki );
				case SEEDSTAT_FLOWER:		return( tbl->code_flower );
				case SEEDSTAT_FRUIT:		return( tbl->code_fruit );
				}
			}
		}
	}
	
	GF_ASSERT( 0 && "木の実成長値が異常です\n" );
	return( OBJCODEMAX );
}

