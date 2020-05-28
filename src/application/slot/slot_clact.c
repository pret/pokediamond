//******************************************************************************
/**
 * 
 * @file	slot_clact.c
 * @brief	ミニゲーム　スロット　セルアクター
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "slot_local.h"

#include "system/render_oam.h"
#include "system/clact_util.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	構造体定義
//--------------------------------------------------------------
typedef struct _TAG_CLACTRESOBJ CLACTRESOBJ;

//--------------------------------------------------------------
///	CLACTRESOBJ構造体
//--------------------------------------------------------------
typedef struct _TAG_CLACTRESOBJ
{
	u16 id;
	u16 trans_flag;
	CLACT_U_RES_OBJ_PTR resobj;
};

#define CLACTRESOBJ_SIZE (sizeof(CLACTRESOBJ))

//--------------------------------------------------------------
///	CLACTSETDATA構造体
//--------------------------------------------------------------
typedef struct _TAG_CLACTSETDATA
{
	u32 heap_id;
	u8 resobj_char_max;
	u8 resobj_pltt_max;
	u8 resobj_cell_max;
	u8 resobj_anm_max;
	u8 resobj_char_nonid;
	u8 resobj_pltt_nonid;
	u8 resobj_cell_nonid;
	u8 resobj_anm_nonid;
	CLACT_SET_PTR clact_set;
	CLACT_U_EASYRENDER_DATA clact_easydata;
	NNSG2dCellTransferState *cellTransArray;
	CLACT_U_RES_MANAGER_PTR clact_resm_char;
	CLACT_U_RES_MANAGER_PTR clact_resm_pltt;
	CLACT_U_RES_MANAGER_PTR clact_resm_cell;
	CLACT_U_RES_MANAGER_PTR clact_resm_anm;
	CLACTRESOBJ *clact_resobj_char;
	CLACTRESOBJ *clact_resobj_pltt;
	CLACTRESOBJ *clact_resobj_cell;
	CLACTRESOBJ *clact_resobj_anm;
};

#define CLACTSETDATA_SIZE (sizeof(CLACTSETDATA))

//==============================================================================
//	static
//==============================================================================
static void ClActCharVIntrTCB( TCB_PTR tcb, void *wk );
static void ClActPlttVIntrTCB( TCB_PTR tcb, void *wk );

//==============================================================================
//	セルアクター　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * セルアクターセットデータ初期化
 * @param	heap_id		HEAPID
 * @param	actmax		アクター最大数
 * @param	transmax	転送セルアクター最大数
 * @param	charmax		キャラ登録最大数
 * @param	plttmax		パレット登録最大数
 * @param	cellmax		セル登録最大数
 * @param	anmmax		アニメ登録最大数
 * @param	charnonid	キャラ登録時に無しと判断するID
 * @param	plttnonid	パレット登録時に無しと判断するID
 * @param	cellnonid	セル登録時に無しと判断するID
 * @param	anmnonid	アニメ登録時に無しと判断するID
 * @retval	nothing
 */
//--------------------------------------------------------------
CLACTSETDATA * ClActSetDataInit(
		u32 heap_id,
		u32 actmax, u32 transmax,
		u32 charmax, u32 plttmax, u32 cellmax, u32 anmmax,
		u32 charnonid, u32 plttnonid, u32 cellnonid, u32 anmnonid )
{
	CLACTSETDATA *set = sys_AllocMemory( heap_id, CLACTSETDATA_SIZE );
	GF_ASSERT( set != NULL );
	
	//ヒープIDセット
	set->heap_id = heap_id;
	
	//パラメタ初期化
	set->resobj_char_max = charmax;
	set->resobj_pltt_max = plttmax;
	set->resobj_cell_max = cellmax;
	set->resobj_anm_max = anmmax;
	set->resobj_char_nonid = charnonid;
	set->resobj_pltt_nonid = plttnonid;
	set->resobj_cell_nonid = cellnonid;
	set->resobj_anm_nonid = anmnonid;
	
	//セルアクター初期化
	set->clact_set = CLACT_U_SetEasyInit( actmax, &set->clact_easydata, heap_id );
	
	//転送マネージャ初期化
	set->cellTransArray = InitCellTransfer( transmax, heap_id );
	initVramTransferManagerHeap( transmax, heap_id );
	
	//リソース初期化
	set->clact_resm_char = CLACT_U_ResManagerInit( charmax, CLACT_U_CHAR_RES, heap_id );
	set->clact_resm_pltt = CLACT_U_ResManagerInit( plttmax, CLACT_U_PLTT_RES, heap_id );
	set->clact_resm_cell = CLACT_U_ResManagerInit( cellmax, CLACT_U_CELL_RES, heap_id );
	set->clact_resm_anm = CLACT_U_ResManagerInit( anmmax, CLACT_U_CELLANM_RES, heap_id );
	
	//リソースOBJ初期化
	set->clact_resobj_char = sys_AllocMemory( heap_id, CLACTRESOBJ_SIZE * charmax );
	set->clact_resobj_pltt = sys_AllocMemory( heap_id, CLACTRESOBJ_SIZE * plttmax );
	set->clact_resobj_cell = sys_AllocMemory( heap_id, CLACTRESOBJ_SIZE * cellmax );
	set->clact_resobj_anm = sys_AllocMemory( heap_id, CLACTRESOBJ_SIZE * anmmax );
	
	{
		u32 i;
		
		for( i = 0; i < charmax; set->clact_resobj_char[i].id = charnonid, i++ ){};
		for( i = 0; i < plttmax; set->clact_resobj_pltt[i].id = plttnonid, i++ ){};
		for( i = 0; i < cellmax; set->clact_resobj_cell[i].id = cellnonid, i++ ){};
		for( i = 0; i < anmmax; set->clact_resobj_anm[i].id = anmnonid, i++ ){};
	}
	
	return( set );
}

//--------------------------------------------------------------
/**
 * セルアクターセットデータ削除
 * @param	clactset	CLACTSETDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActSetDataDelete( CLACTSETDATA *set )
{
	u32 i;
	
	//VRAMに展開されたキャラ、パレット削除
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id != set->resobj_char_nonid ){
			CLACT_U_CharManagerDelete( set->clact_resobj_char[i].resobj );
		}
	}
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id != set->resobj_pltt_nonid ){
			CLACT_U_PlttManagerDelete( set->clact_resobj_pltt[i].resobj );
		}
	}
	
	//セル、アニメ展開領域破棄
	for( i = 0; i < set->resobj_cell_max; i++ ){
		if( set->clact_resobj_cell[i].id != set->resobj_cell_nonid ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_cell[i].resobj );
		}
	}
	
	for( i = 0; i < set->resobj_anm_max; i++ ){
		if( set->clact_resobj_anm[i].id != set->resobj_anm_nonid ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_anm[i].resobj );
		}
	}
	
	CLACT_U_ResManagerDelete( set->clact_resm_char );
	CLACT_U_ResManagerDelete( set->clact_resm_pltt );
	CLACT_U_ResManagerDelete( set->clact_resm_cell );
	CLACT_U_ResManagerDelete( set->clact_resm_anm );
	
	sys_FreeMemoryEz( set->clact_resobj_char );
	sys_FreeMemoryEz( set->clact_resobj_pltt );
	sys_FreeMemoryEz( set->clact_resobj_cell );
	sys_FreeMemoryEz( set->clact_resobj_anm );
	
	//セル転送マネージャ削除
	DellVramTransferManager();
	DeleteCellTransfer( set->cellTransArray );
	
	//アクター全部削除
	CLACT_DelAllSet( set->clact_set );
	//セルアクター破棄
	CLACT_DestSet( set->clact_set );
	
	//開放
	sys_FreeMemoryEz( set );
}

//--------------------------------------------------------------
/**
 * セルアクターセットデータ　描画
 * @param	set			CLACTSETDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActSetDataDraw( CLACTSETDATA *set )
{
	CLACT_Draw( set->clact_set );
	UpdateCellTransfer();
}

//--------------------------------------------------------------
/**
 * キャラ登録
 * @param	set		CLACTSETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id 登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActCharAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == set->resobj_char_nonid ){
			set->clact_resobj_char[i].id = id;
			set->clact_resobj_char[i].trans_flag = FALSE;
			set->clact_resobj_char[i].resobj =
				CLACT_U_ResManagerResAddArcChar_ArcHandle(
					set->clact_resm_char, hand, arcid, FALSE, id,
					type, set->heap_id );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActCharAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * 指定されたキャラIDをVRAMエリアへセット
 * @param	set		CLACTSETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActCharVramAreaSet( CLACTSETDATA *set, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == id ){
			CLACT_U_CharManagerSetAreaCont( set->clact_resobj_char[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActCharAreaCont()ID異常" );
}

//--------------------------------------------------------------
/**
 * 指定されたキャラIDで展開した領域を破棄
 * @param	set		CLACTSETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActCharResDelete( CLACTSETDATA *set, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_char[i].id == id ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_char[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActCharResDelete()ID異常" );
}

//--------------------------------------------------------------
/**
 * Vブランク　キャラ転送
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ClActCharVIntrTCB( TCB_PTR tcb, void *wk )
{
	CLACTRESOBJ *caresobj = wk;
	
	if( caresobj->trans_flag == FALSE && caresobj->resobj != NULL ){
		CLACT_U_CharManagerSetAreaCont( caresobj->resobj );
		caresobj->trans_flag = TRUE;
	}
	
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * パレット登録
 * @param	set		CLACTSETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActPlttAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_pltt[i].id == set->resobj_pltt_nonid ){
			set->clact_resobj_pltt[i].id = id;
			set->clact_resobj_pltt[i].trans_flag = FALSE;
			set->clact_resobj_pltt[i].resobj =
				CLACT_U_ResManagerResAddArcPltt_ArcHandle(
					set->clact_resm_pltt, hand, arcid, FALSE, id,
					type, 1, set->heap_id );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActPlttAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * 指定されたパレットIDをVRAMエリアへセット
 * @param	set		CLACTSETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActPlttVramAreaSet( CLACTSETDATA *set, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id == id ){
			CLACT_U_PlttManagerSetCleanArea( set->clact_resobj_pltt[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActPlttAreaCont()ID異常" );
}

//--------------------------------------------------------------
/**
 * 指定されたパレットIDで展開した領域を破棄
 * @param	set		CLACTSETDATA
 * @param	id		登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActPlttResDelete( CLACTSETDATA *set, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id == id ){
			CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_pltt[i].resobj );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActPlttResDelete()ID異常" );
}

//--------------------------------------------------------------
/**
 * Vブランク　パレット転送
 * @param	tcb	TCB_PTR
 * @param	wk	tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void ClActPlttVIntrTCB( TCB_PTR tcb, void *wk )
{
	CLACTRESOBJ *caresobj = wk;
	
	if( caresobj->trans_flag == FALSE && caresobj->resobj != NULL ){
		CLACT_U_PlttManagerSetCleanArea( caresobj->resobj );
		caresobj->trans_flag = TRUE;
	}
	
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * 指定されたパレットIDのプロキシを取得
 * @param	set		CLACTSETDATA
 * @param	id	登録ID
 * @retval	NNSG2dImageProxy NNSG2dImageProxy
 */
//--------------------------------------------------------------
const NNSG2dImagePaletteProxy * ClActPlttProxyGet( CLACTSETDATA *set, u32 id )
{
	u32 i;
	CLACT_U_RES_OBJ_PTR reso;
	const NNSG2dImagePaletteProxy *proxy;
	
	for( i = 0; i < set->resobj_pltt_max; i++ ){
		if( set->clact_resobj_pltt[i].id == id ){
			reso = set->clact_resobj_pltt[i].resobj;
			proxy = CLACT_U_PlttManagerGetProxy( reso, NULL );
			return( proxy );
		}
	}
	
	GF_ASSERT( 0 && "ClActPlttProxyGet()ID無し" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * セル登録
 * @param	set		CLACTSETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActCellAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_cell[i].id == set->resobj_cell_nonid ){
			set->clact_resobj_cell[i].id = id;
			set->clact_resobj_cell[i].trans_flag = FALSE;
			set->clact_resobj_cell[i].resobj =
				CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
					set->clact_resm_cell, hand, arcid, FALSE, id, 
					CLACT_U_CELL_RES, set->heap_id );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActCellAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * アニメ登録
 * @param	set		CLACTSETDATA
 * @param	hand	ARCHANDLE *
 * @param	arcid	アーカイブデータインデックス
 * @param	id	登録ID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActAnmAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id )
{
	u32 i;
	
	for( i = 0; i < set->resobj_char_max; i++ ){
		if( set->clact_resobj_anm[i].id == set->resobj_anm_nonid ){
			set->clact_resobj_anm[i].id = id;
			set->clact_resobj_anm[i].trans_flag = FALSE;
			set->clact_resobj_anm[i].resobj =
				CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
					set->clact_resm_anm, hand, arcid, FALSE, id, 
					CLACT_U_CELLANM_RES, set->heap_id );
			return;
		}
	}
	
	GF_ASSERT( 0 && "ClActAnmAdd()登録できない" );
}

//--------------------------------------------------------------
/**
 * セルアクター　指定IDで登録されているグラフィックを削除
 * @param	clactset	CLACTSETDATA
 * @param	charid		キャラID。削除しない場合はnonID
 * @param	plttid		パレットID。削除しない場合はnonID
 * @param	cellid		セルID。削除しない場合はnonID
 * @param	anmid		アニメID。削除しない場合はnonID
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActGraphicDelete( CLACTSETDATA *set, u32 charid, u32 plttid, u32 cellid, u32 anmid )
{
	u32 i;
	
	if( charid != set->resobj_char_nonid ){					//キャラ
		for( i = 0; i < set->resobj_char_max; i++ ){
			if( set->clact_resobj_char[i].id == charid ){
				CLACT_U_CharManagerDelete( set->clact_resobj_char[i].resobj );
				CLACT_U_ResManagerResDelete(
					set->clact_resm_char, set->clact_resobj_char[i].resobj );
				set->clact_resobj_char[i].id = set->resobj_char_nonid;
				break;
			}
		}
	}
	
	if( plttid != set->resobj_pltt_nonid ){					//パレット
		for( i = 0; i < set->resobj_pltt_max; i++ ){
			if( set->clact_resobj_pltt[i].id == plttid ){
				CLACT_U_PlttManagerDelete( set->clact_resobj_pltt[i].resobj );
				CLACT_U_ResManagerResDelete(
					set->clact_resm_pltt, set->clact_resobj_pltt[i].resobj );
				set->clact_resobj_pltt[i].id = set->resobj_pltt_nonid;
				break;
			}
		}
	}
	
	if( cellid != set->resobj_cell_nonid ){					//セル
		for( i = 0; i < set->resobj_cell_max; i++ ){
			if( set->clact_resobj_cell[i].id == cellid ){
				CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_cell[i].resobj );
				CLACT_U_ResManagerResDelete(
					set->clact_resm_cell, set->clact_resobj_cell[i].resobj );
				set->clact_resobj_cell[i].id = set->resobj_cell_nonid;
				break;
			}
		}
	}
	
	if( anmid != set->resobj_anm_nonid ){					//アニメ
		for( i = 0; i < set->resobj_anm_max; i++ ){
			if( set->clact_resobj_anm[i].id == anmid ){
				CLACT_U_ResManagerResOnlyDelete( set->clact_resobj_anm[i].resobj );
				CLACT_U_ResManagerResDelete(
					set->clact_resm_anm, set->clact_resobj_anm[i].resobj );
				set->clact_resobj_anm[i].id = set->resobj_anm_nonid;
				break;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * アクター追加
 * @param	set			CLACTSETDATA
 * @param	mtx			表示座標
 * @param	char_id		キャラクタデータID
 * @param	pltt_id		パレットデータID
 * @param	cell_id		セルデータID
 * @param	cellanm_id	セルアニメーションID	無いときはCLACT_U_HEADER_DATA_NONE
 * @param	bg_pri		BGプライオリティ
 * @param	act_pri		アクタープライオリティ
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActAdd( CLACTSETDATA *set, CLACT_WORK_EX *actwork,
		const VecFx32 *vec, u32 drawtype, int celltrans,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri )
{
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;
	CLACT_WORK_PTR act;
	
	if( cellanm_id == set->resobj_anm_nonid ){
		cellanm_id = CLACT_U_HEADER_DATA_NONE;
	}
	
	CLACT_U_MakeHeader(
		&head, char_id, pltt_id, cell_id, cellanm_id,
		CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
		celltrans,
		bg_pri,
		set->clact_resm_char,
		set->clact_resm_pltt,
		set->clact_resm_cell,
		set->clact_resm_anm,
		NULL, NULL );
	
	if( celltrans == CELL_TRANS ){
//		head.pImageProxy = GetCharVramTransProxyCopy( head.pImageProxy );
		actwork->pImageProxy = head.pImageProxy;
		actwork->trans_flag = CELL_TRANS;
	}else{
		actwork->trans_flag = CELL_VRAM;
	}
	
	add.ClActSet = set->clact_set;
	add.ClActHeader = &head;
	add.mat = *vec;
	add.pri = act_pri;
	add.DrawArea = drawtype;
	add.heap = set->heap_id;
		
	actwork->act = CLACT_AddSimple( &add );
	GF_ASSERT( actwork->act != NULL && "CLACT_AddSimple() Error" );
}

//--------------------------------------------------------------
/**
 * アクター破棄
 * @param	actwork	CLACT_WORK_EX
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActDelete( CLACT_WORK_EX *actwork )
{
	if( actwork->trans_flag == CELL_TRANS ){
		CLACT_U_CharManagerDeleteVramTransferProxy( actwork->pImageProxy );
	}
	
	CLACT_Delete( actwork->act );
	actwork->act = NULL;
}

//--------------------------------------------------------------
/**
 * セルアクターの座標を取得
 * @param	act		CLACT_WORK_PTR
 * @param	mtx		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActMatrixGet( CLACT_WORK_PTR act, VecFx32 *mtx )
{
	const VecFx32 *cmtx = CLACT_GetMatrix( act );
	*mtx = *cmtx;
}

//--------------------------------------------------------------
/**
 * セルアクターの拡縮率を取得
 * @param	act		CLACT_WORK_PTR
 * @param	mtx		座標格納先
 * @retval	nothing
 */
//--------------------------------------------------------------
void ClActScaleGet( CLACT_WORK_PTR act, VecFx32 *scale )
{
	const VecFx32 *cscale = CLACT_GetScale( act );
	*scale = *cscale;
}
