//==============================================================================
/**
 * @file	battle_cursor.c
 * @brief	戦闘下画面用カーソル
 * @author	matsuda
 * @date	2006.03.27(月)
 */
//==============================================================================
#include "common.h"
#include "graphic\batt_obj_def.h"
#include "graphic\batt_bg_def.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "battle/battle_tcb_pri.h"

#include "battle/battle_cursor.h"


//==============================================================================
//	定数定義
//==============================================================================
///戦闘カーソルのアクターポインタ配列番号
enum{
	BCURSOR_ACT_LU,		///<左上カーソル
	BCURSOR_ACT_RU,		///<右上カーソル
	BCURSOR_ACT_LD,		///<左下カーソル
	BCURSOR_ACT_RD,		///<右下カーソル
	
	BCURSOR_ACT_EX,		///<特別カーソル
	
	BCURSOR_ACT_NUM,	///<戦闘カーソルのアクター使用数
};

//==============================================================================
//	構造体定義
//==============================================================================
///戦闘カーソルワーク
typedef struct _BCURSOR_WORK{
	CATS_ACT_PTR cap[BCURSOR_ACT_NUM];
	TCB_PTR update_tcb;
}BCURSOR_WORK;

//==============================================================================
//	データ
//==============================================================================
///AA用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S BCursorObjParam = {
	0, 0, 0,		//x, y, z
	0, 0, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		0,	//キャラ
		0,	//パレット
		0,	//セル
		0,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	0,			//BGプライオリティ
	0,			//Vram転送フラグ
};

//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void BCURSOR_ObjectUpdate(TCB_PTR tcb, void *work);
void BCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
void BCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
BCURSOR_PTR BCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
void BCURSOR_ActorDelete(BCURSOR_PTR cursor);
void BCURSOR_PosSetON(BCURSOR_PTR cursor, int left, int right, int top, int bottom);
void BCURSOR_ExPosSetON(BCURSOR_PTR cursor, int x, int y, BCURSOR_ANMTYPE anm_type);
void BCURSOR_OFF(BCURSOR_PTR cursor);



//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルのリソースをロードする
 *
 * @param   csp			
 * @param   crp			
 * @param   pfd			
 * @param   char_id		キャラID
 * @param   pal_id		パレットID
 * @param   cell_id		セルID
 * @param   anm_id		アニメID
 */
//--------------------------------------------------------------
void BCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp, 
		ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, pal_id);
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, BATTLE_CURSOR_OAM_SUB_NCER_BIN, 1, 
		cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		BATTLE_CURSOR_OAM_SUB_NANR_BIN, 1, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルのリソースを解放する
 *
 * @param   crp			
 * @param   char_id		キャラID
 * @param   pal_id		パレットID
 * @param   cell_id		セルID
 * @param   anm_id		アニメID
 */
//--------------------------------------------------------------
void BCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceChar(crp, char_id);
	CATS_FreeResourcePltt(crp, pal_id);
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルのアクターを生成します
 *
 * @param   csp		
 * @param   crp		
 * @param   heap_id		ヒープID
 * @param   char_id		キャラID
 * @param   pal_id		パレットID
 * @param   cell_id		セルID
 * @param   anm_id		アニメID
 * @param   soft_pri	ソフトプライオリティ
 * @param   bg_pri		BGプライオリティ
 *
 * @retval  生成された戦闘カーソルワークのポインタ
 *
 * 戦闘カーソルワークの生成とUpdate用TCBの生成も同時に行います
 * 生成時は表示OFFになっています。
 */
//--------------------------------------------------------------
BCURSOR_PTR BCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri)
{
	BCURSOR_WORK *cursor;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	int i;
	
	obj_head = BCursorObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = char_id;
	obj_head.id[CLACT_U_PLTT_RES] = pal_id;
	obj_head.id[CLACT_U_CELL_RES] = cell_id;
	obj_head.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_head.pri = soft_pri;
	obj_head.bg_pri = bg_pri;
	
	cursor = sys_AllocMemory(heap_id, sizeof(BCURSOR_WORK));
	MI_CpuClear8(cursor, sizeof(BCURSOR_WORK));
	
	for(i = 0; i < BCURSOR_ACT_NUM; i++){
		cursor->cap[i] = CATS_ObjectAdd_S(csp, crp, &obj_head);
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
	
	cursor->update_tcb = TCB_Add(BCURSOR_ObjectUpdate, cursor, TCBPRI_BCURSOR);
	return cursor;
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルアクターを削除します
 *
 * @param   cursor		戦闘カーソルワークへのポインタ
 *
 * 戦闘カーソルワークの解放と、Update用TCBの削除も行います
 */
//--------------------------------------------------------------
void BCURSOR_ActorDelete(BCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < BCURSOR_ACT_NUM; i++){
		CATS_ActorPointerDelete_S(cursor->cap[i]);
	}
	
	TCB_Delete(cursor->update_tcb);
	sys_FreeMemoryEz(cursor);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの座標セットと表示のONを行います(全て個別に指定)
 *
 * @param   cursor		戦闘カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void BCURSOR_IndividualPosSetON_Surface(BCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y, fx32 surface_y)
{
	int i;
	
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[BCURSOR_ACT_LU], lu_x, lu_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[BCURSOR_ACT_RU], ru_x, ru_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[BCURSOR_ACT_LD], ld_x, ld_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[BCURSOR_ACT_RD], rd_x, rd_y, surface_y);

	CATS_ObjectAnimeSeqSetCap(cursor->cap[BCURSOR_ACT_LU], BCURSOR_ANMTYPE_LU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[BCURSOR_ACT_RU], BCURSOR_ANMTYPE_RU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[BCURSOR_ACT_LD], BCURSOR_ANMTYPE_LD);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[BCURSOR_ACT_RD], BCURSOR_ANMTYPE_RD);

	for(i = 0; i < BCURSOR_ACT_EX; i++){
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_TRUE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの座標セットと表示のONを行います(全て個別に指定)
 *
 * @param   cursor		戦闘カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void BCURSOR_IndividualPosSetON(BCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y)
{
	BCURSOR_IndividualPosSetON_Surface(cursor, lu_x, lu_y, ru_x, ru_y, ld_x, ld_y, rd_x, rd_y,
		SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの座標セットと表示のONを行います(矩形で指定)
 *
 * @param   cursor		戦闘カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void BCURSOR_PosSetON(BCURSOR_PTR cursor, int left, int right, int top, int bottom)
{
	BCURSOR_IndividualPosSetON(cursor, left, top, right, top, left, bottom, right, bottom);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの座標セットと表示のONを行います(矩形で指定)
 *
 * @param   cursor		戦闘カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void BCURSOR_PosSetON_Surface(BCURSOR_PTR cursor, int left, int right, int top, int bottom,
	fx32 surface_y)
{
	BCURSOR_IndividualPosSetON_Surface(cursor, left, top, right, top, left, bottom, right, bottom,
		surface_y);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルの座標セットと表示のONを行います
 *
 * @param   cursor			戦闘カーソルワークへのポインタ
 * @param   x				座標X
 * @param   y				座標Y
 * @param   anm_type		アニメタイプ(BCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void BCURSOR_ExPosSetON_Surface(BCURSOR_PTR cursor, int x, int y, BCURSOR_ANMTYPE anm_type,
	fx32 surface_y)
{
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[BCURSOR_ACT_EX], x, y, surface_y);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[BCURSOR_ACT_EX], anm_type);
	CATS_ObjectEnableCap(cursor->cap[BCURSOR_ACT_EX], CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルの座標セットと表示のONを行います
 *
 * @param   cursor			戦闘カーソルワークへのポインタ
 * @param   x				座標X
 * @param   y				座標Y
 * @param   anm_type		アニメタイプ(BCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void BCURSOR_ExPosSetON(BCURSOR_PTR cursor, int x, int y, BCURSOR_ANMTYPE anm_type)
{
	BCURSOR_ExPosSetON_Surface(cursor, x, y, anm_type, SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルを全て表示OFFする
 * @param   cursor		戦闘カーソルワークへのポインタ
 */
//--------------------------------------------------------------
void BCURSOR_OFF(BCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < BCURSOR_ACT_NUM; i++){
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルのみ表示OFFする
 * @param   cursor		戦闘カーソルワークへのポインタ
 */
//--------------------------------------------------------------
void BCURSOR_ExOFF(BCURSOR_PTR cursor)
{
	CATS_ObjectEnableCap(cursor->cap[BCURSOR_ACT_EX], CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   カーソルアニメUpdate処理
 * @param   tcb			TCBへのポインタ
 * @param   work		カーソルワークへのポインタ
 */
//--------------------------------------------------------------
static void BCURSOR_ObjectUpdate(TCB_PTR tcb, void *work)
{
	BCURSOR_WORK *cursor = work;
	int i;
	
	if(CATS_ObjectEnableGetCap(cursor->cap[BCURSOR_ACT_LU]) == CATS_ENABLE_FALSE){
		return;
	}
	
	for(i = 0; i < BCURSOR_ACT_EX; i++){
		CATS_ObjectUpdateCap(cursor->cap[i]);
	}
	if(CATS_ObjectEnableGetCap(cursor->cap[BCURSOR_ACT_EX]) == CATS_ENABLE_TRUE){
		CATS_ObjectUpdateCap(cursor->cap[BCURSOR_ACT_EX]);
	}
}

