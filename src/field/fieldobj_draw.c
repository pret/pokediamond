//******************************************************************************
/**
 *
 * @file	fieldobj_draw.c
 * @brief	フィールドOBJ 描画系
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
#ifdef PM_DEBUG
//#define DEBUG_DRAW
#endif

//==============================================================================
//	プロトタイプ
//==============================================================================
static void FldOBJSys_ArcHandleOpen( FIELD_OBJ_SYS_PTR fos );
static void FldOBJSys_ArcHandleClose( FIELD_OBJ_SYS_PTR fos );

static const OBJCODE_STATE * FldOBJ_OBJCodeDrawStateGet( int code );

#ifdef DEBUG_DRAW
static void DEBUG_Print( void );
#endif

//==============================================================================
//	フィールドOBJ　描画システム
//==============================================================================
//--------------------------------------------------------------
/**
 * FIELD OBJ 描画系初期化
 * @param	fos			FIELD_OBJ_SYS_PTR
 * @param	tex_max		テクスチャを登録できる最大人数
 * @param	reg_tex_max	tex_max中、常に常駐する最大人数
 * @param	tex_tbl		常に常駐する人物をまとめたテーブル BABYBOY1等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DrawInit( FIELD_OBJ_SYS_PTR fos,
		int tex_max, int reg_tex_max, const int *tex_tbl )
{
	int max,pri;
	FIELD_OBJ_BLACT_CONT *cont;
	
	GF_ASSERT( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_INIT_COMP) == 0 &&
			"FieldOBJSys_DrawInit()が重ねて呼び出れています\n" );
	
	FldOBJSys_ArcHandleOpen( fos );
	
	max = FieldOBJSys_OBJMaxGet( fos );
	pri = FieldOBJSys_TCBStandardPriorityGet( fos ) - 1; //ゲストビルボード追加処理は標準より上
	cont = FieldOBJSys_BlActContGet( fos );
	
	FieldOBJ_BlActCont_Init( cont, fos, max, pri, tex_max, reg_tex_max, tex_tbl );
	
	{
		FIELD_OBJ_RENDER_CONT_PTR rdcont = FieldOBJ_RenderCont_Init( fos, HEAPID_FIELD );
		FieldOBJSys_RenderContSet( fos, rdcont );
		FieldOBJ_RenderCont_RegistInit( rdcont, DATA_FIELDOBJ_RenderOBJMax );
	}
	
	FieldOBJSys_StatusBit_ON( fos, FLDOBJSYS_STA_BIT_DRAW_INIT_COMP );
	
	OS_Printf( "フィールドOBJ 描画処理を初期化しました\n" );
	
#ifdef DEBUG_DRAW	
	DEBUG_Print();
#endif
}

//--------------------------------------------------------------
/**
 * FIELD OBJ 描画処理を削除
 * @param	fos		FIELD_OBJ_SYS_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJSys_DrawDelete( FIELD_OBJ_SYS_PTR fos )
{
	int ret;
	
	ret = FieldOBJSys_DrawInitCompCheck( fos );
	GF_ASSERT( ret == TRUE && "フィールドOBJ 描画処理削除が二重に呼び出されています\n" );
	
	FieldOBJ_BlActCont_Delete( FieldOBJSys_BlActContGet(fos) );
	
	{
		FIELD_OBJ_RENDER_CONT_PTR rdcont = FieldOBJSys_RenderContGet( fos );
		FieldOBJ_RenderCont_Delete( rdcont );
		FieldOBJSys_RenderContSet( fos, NULL );
	}
	
	FieldOBJSys_StatusBit_OFF( fos, FLDOBJSYS_STA_BIT_DRAW_INIT_COMP );
	FldOBJSys_ArcHandleClose( fos );
	
	OS_Printf( "フィールドOBJ 描画処理を削除しました\n" );
}

//==============================================================================
//	アーカイブ
//==============================================================================
//--------------------------------------------------------------
/**
 * アーカイブハンドルセット
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_ArcHandleOpen( FIELD_OBJ_SYS_PTR fos )
{
	ARCHANDLE *handle = ArchiveDataHandleOpen( ARC_MMODEL, HEAPID_FIELD );
	FieldOBJSys_ArcHandleSet( fos, handle );
}

//--------------------------------------------------------------
/**
 * アーカイブハンドルクローズ
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJSys_ArcHandleClose( FIELD_OBJ_SYS_PTR fos )
{
	ARCHANDLE *handle = FieldOBJSys_ArcHandleGet( fos );
	ArchiveDataHandleClose( handle );
}

//==============================================================================
//	フィールドOBJ 描画処理
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_Draw( FIELD_OBJ_PTR fldobj )
{
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	if( FieldOBJSys_StatusBit_Check(fos,FLDOBJSYS_STA_BIT_DRAW_PROC_STOP) ){
		return;
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_DRAW_PROC_INIT_COMP) == FALSE ){
		return;
	}
	
	if( FieldOBJ_MovePauseCheck(fldobj) == FALSE || FieldOBJ_StatusBitCheck_Acmd(fldobj) ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//==============================================================================
//	フィールドOBJ 描画ステータス
//==============================================================================
//--------------------------------------------------------------
/**
 * OBJコードから描画ステータス取得
 * @param	fldobj	 FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
const OBJCODE_STATE * FieldOBJ_OBJCodeDrawStateGet( CONST_FIELD_OBJ_PTR fldobj )
{
	int code = FieldOBJ_OBJCodeGet( fldobj );
	const OBJCODE_STATE *state = FldOBJ_OBJCodeDrawStateGet( code );
	return( state );
}

//--------------------------------------------------------------
/**
 * DATA_FieldOBJCodeDrawStateTbl[]取得
 * @param	code	HERO等
 * @retval	OBJCODE_STATE codeに対応したOBJCODE_STATE
 */
//--------------------------------------------------------------
static const OBJCODE_STATE * FldOBJ_OBJCodeDrawStateGet( int code )
{
	const OBJCODE_STATE *state = DATA_FieldOBJCodeDrawStateTbl;
	do{ if(state->code==code){return(state);} state++; }while( state->code != OBJCODEMAX );
	OS_Printf( "FldOBJ_OBJCodeDrawStateGet() OBJ CODE ERROR!! CODE = 0x%x\n", code );
	GF_ASSERT( 0 );
	return( NULL );
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJ 描画ポーズチェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		TRUE=描画ポーズ
 */
//--------------------------------------------------------------
int FieldOBJ_DrawPauseCheck( CONST_FIELD_OBJ_PTR fldobj )
{
	if( FieldOBJ_MovePauseCheck(fldobj) == TRUE ){
		if( FieldOBJ_StatusBitCheck_Acmd(fldobj) == FALSE ){
			return( TRUE );
		}
	}
	
	if( FieldOBJ_StatusBit_Check(fldobj,FLDOBJ_STA_BIT_PAUSE_ANM) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * アーカイブデータロード
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	datID	アーカイブデータID
 * @param	fb		TRUE=sys_AllocMemory() FALSE=sys_AllocMemoryLo()
 * @retval	void*	取得したデータ
 */
//--------------------------------------------------------------
void * FieldOBJ_DrawArcDataAlloc( CONST_FIELD_OBJ_SYS_PTR fos, u32 datID, int fb )
{
	void *buf;
	ARCHANDLE *handle = FieldOBJSys_ArcHandleGet( fos );
	u32 size = ArchiveDataSizeGetByHandle( handle, datID );
	
	if( fb == TRUE ){
		buf = sys_AllocMemory( HEAPID_FIELD, size );
	}else{
		buf = sys_AllocMemoryLo( HEAPID_FIELD, size );
	}
	
	ArchiveDataLoadByHandle( handle, datID, buf );
	return( buf );
}

//--------------------------------------------------------------
/**
 * フィールドOBJ　基本座標＋オフセットを取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	vec		座標格納先
 * @retval	void*	取得したデータ
 */
//--------------------------------------------------------------
void FieldOBJ_DrawVecPosTotalGet( CONST_FIELD_OBJ_PTR fldobj, VecFx32 *vec )
{
	VecFx32 vec_pos,vec_offs,vec_out,vec_attr;
	
	FieldOBJ_VecPosGet( fldobj, &vec_pos );
	FieldOBJ_VecDrawOffsGet( fldobj, &vec_offs );
	FieldOBJ_VecDrawOffsOutSideGet( fldobj, &vec_out );
	FieldOBJ_VecAttrOffsGet( fldobj, &vec_attr );
	
	vec->x = vec_pos.x + vec_offs.x + vec_out.x + vec_attr.x;
	vec->y = vec_pos.y + vec_offs.y + vec_out.y + vec_attr.y;
	vec->z = vec_pos.z + vec_offs.z + vec_out.z + vec_attr.z;
}

//--------------------------------------------------------------
/**
 * 方向をセットする。描画系も併せて更新
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		方向、DIR_UP等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DirDispDrawSet( FIELD_OBJ_PTR fldobj, int dir )
{
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	
	if( FieldOBJ_StatusBitCheck_DrawProcInitComp(fldobj) == TRUE ){
		FieldOBJ_DrawProcCall( fldobj );
	}
}

//==============================================================================
//	描画無し
//==============================================================================
//--------------------------------------------------------------
/**
 * 描画無し　初期化
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Init( FIELD_OBJ_PTR fldobj )
{
	FieldOBJ_StatusBitSet_Vanish( fldobj, TRUE );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_SHADOW_VANISH );
}

//--------------------------------------------------------------
/**
 * 描画無し　描画
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Draw( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画無し　削除
 * @param	fldobj	FIELD_OBJ_PTR 
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Delete( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画無し　退避
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Push( FIELD_OBJ_PTR fldobj )
{
}

//--------------------------------------------------------------
/**
 * 描画無し　復帰
 * 退避した情報を元に再描画。
 * @param	fldobj		FIELD_OBJ_PTR 
 * @retval	int			TRUE=初期化成功
 */
//--------------------------------------------------------------
void FieldOBJ_DrawNon_Pop( FIELD_OBJ_PTR fldobj )
{
}

//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_DRAW
#include "fieldobj_test.c"

static void DEBUG_Print( void )
{
	u32 i;
	
	OS_Printf( "const OBJCODE_STATE DATA_FieldOBJCodeStateTbl[] =\n" );
	OS_Printf( "{\r\n" );
	
	for( i = 0; i <= KOIKING; i++ ){
		OS_Printf( " {" );
		OS_Printf( "%s,", DEBUGDATA_CharTbl[i] );
		OS_Printf( "FLDOBJ_DRAWTYPE_BLACT," );
		OS_Printf( "FLDOBJ_SHADOW_ON," );
		OS_Printf( "FLDOBJ_FOOTMARK_NORMAL," );
		OS_Printf( "FLDOBJ_REFLECT_BLACT," );
		OS_Printf( "0},\r\n" );
		{ u32 f; for( f = 0; f < 0xffffffff; f++ ){}; }
	}
	
	{
		int j;
		for( j = 0; j < 2; j++ ){};
	}
}
#endif	//DEBUG_DRAW
