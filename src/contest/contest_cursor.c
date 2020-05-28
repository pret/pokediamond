//==============================================================================
/**
 * @file	contest_cursor.c
 * @brief	コンテスト下画面用カーソル
 * @author	matsuda
 * @date	2006.03.27(月)
 *
 * battle_cursor.cの名称違い。オーバーレイの関係で使えなかったので別名にして用意した
 */
//==============================================================================
#include "common.h"
#include "battle\graphic\batt_obj_def.h"
#include "battle\graphic\batt_bg_def.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "battle/battle_tcb_pri.h"

#include "contest/contest_cursor.h"


//==============================================================================
//	定数定義
//==============================================================================
///戦闘カーソルのアクターポインタ配列番号
enum{
	CCURSOR_ACT_LU,		///<左上カーソル
	CCURSOR_ACT_RU,		///<右上カーソル
	CCURSOR_ACT_LD,		///<左下カーソル
	CCURSOR_ACT_RD,		///<右下カーソル
	
	CCURSOR_ACT_EX,		///<特別カーソル
	
	CCURSOR_ACT_NUM,	///<戦闘カーソルのアクター使用数
};

///カーソルOBJUpdateのTCBプライオリティ
#define TCBPRI_CCURSOR					(40000)

//==============================================================================
//	構造体定義
//==============================================================================
///戦闘カーソルワーク
typedef struct _CCURSOR_WORK{
	CATS_ACT_PTR cap[CCURSOR_ACT_NUM];
	TCB_PTR update_tcb;
}CCURSOR_WORK;

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
static void CCURSOR_ObjectUpdate(TCB_PTR tcb, void *work);
void CCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
void CCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
CCURSOR_PTR CCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
void CCURSOR_ActorDelete(CCURSOR_PTR cursor);
void CCURSOR_PosSetON(CCURSOR_PTR cursor, int left, int right, int top, int bottom);
void CCURSOR_ExPosSetON(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type);
void CCURSOR_OFF(CCURSOR_PTR cursor);



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
void CCURSOR_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
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
void CCURSOR_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
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
CCURSOR_PTR CCURSOR_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri)
{
	CCURSOR_WORK *cursor;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	int i;
	
	obj_head = BCursorObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = char_id;
	obj_head.id[CLACT_U_PLTT_RES] = pal_id;
	obj_head.id[CLACT_U_CELL_RES] = cell_id;
	obj_head.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_head.pri = soft_pri;
	obj_head.bg_pri = bg_pri;
	
	cursor = sys_AllocMemory(heap_id, sizeof(CCURSOR_WORK));
	MI_CpuClear8(cursor, sizeof(CCURSOR_WORK));
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
		cursor->cap[i] = CATS_ObjectAdd_S(csp, crp, &obj_head);
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
	
	cursor->update_tcb = TCB_Add(CCURSOR_ObjectUpdate, cursor, TCBPRI_CCURSOR);
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
void CCURSOR_ActorDelete(CCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
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
void CCURSOR_IndividualPosSetON_Surface(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y, fx32 surface_y)
{
	int i;
	
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_LU], lu_x, lu_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_RU], ru_x, ru_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_LD], ld_x, ld_y, surface_y);
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_RD], rd_x, rd_y, surface_y);

	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_LU], CCURSOR_ANMTYPE_LU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_RU], CCURSOR_ANMTYPE_RU);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_LD], CCURSOR_ANMTYPE_LD);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_RD], CCURSOR_ANMTYPE_RD);

	for(i = 0; i < CCURSOR_ACT_EX; i++){
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
void CCURSOR_IndividualPosSetON(CCURSOR_PTR cursor, int lu_x, int lu_y, int ru_x, int ru_y,
	int ld_x, int ld_y, int rd_x, int rd_y)
{
	CCURSOR_IndividualPosSetON_Surface(cursor, lu_x, lu_y, ru_x, ru_y, ld_x, ld_y, rd_x, rd_y,
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
void CCURSOR_PosSetON(CCURSOR_PTR cursor, int left, int right, int top, int bottom)
{
	CCURSOR_IndividualPosSetON(cursor, left, top, right, top, left, bottom, right, bottom);
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
void CCURSOR_PosSetON_Surface(CCURSOR_PTR cursor, int left, int right, int top, int bottom,
	fx32 surface_y)
{
	CCURSOR_IndividualPosSetON_Surface(cursor, left, top, right, top, left, bottom, right, bottom,
		surface_y);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルの座標セットと表示のONを行います
 *
 * @param   cursor			戦闘カーソルワークへのポインタ
 * @param   x				座標X
 * @param   y				座標Y
 * @param   anm_type		アニメタイプ(CCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void CCURSOR_ExPosSetON_Surface(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type,
	fx32 surface_y)
{
	CATS_ObjectPosSetCap_SubSurface(cursor->cap[CCURSOR_ACT_EX], x, y, surface_y);
	CATS_ObjectAnimeSeqSetCap(cursor->cap[CCURSOR_ACT_EX], anm_type);
	CATS_ObjectEnableCap(cursor->cap[CCURSOR_ACT_EX], CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルの座標セットと表示のONを行います
 *
 * @param   cursor			戦闘カーソルワークへのポインタ
 * @param   x				座標X
 * @param   y				座標Y
 * @param   anm_type		アニメタイプ(CCURSOR_ANMTYPE_???)
 */
//--------------------------------------------------------------
void CCURSOR_ExPosSetON(CCURSOR_PTR cursor, int x, int y, CCURSOR_ANMTYPE anm_type)
{
	CCURSOR_ExPosSetON_Surface(cursor, x, y, anm_type, SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルを全て表示OFFする
 * @param   cursor		戦闘カーソルワークへのポインタ
 */
//--------------------------------------------------------------
void CCURSOR_OFF(CCURSOR_PTR cursor)
{
	int i;
	
	for(i = 0; i < CCURSOR_ACT_NUM; i++){
		CATS_ObjectEnableCap(cursor->cap[i], CATS_ENABLE_FALSE);
	}
}

//--------------------------------------------------------------
/**
 * @brief   戦闘カーソルの特別カーソルのみ表示OFFする
 * @param   cursor		戦闘カーソルワークへのポインタ
 */
//--------------------------------------------------------------
void CCURSOR_ExOFF(CCURSOR_PTR cursor)
{
	CATS_ObjectEnableCap(cursor->cap[CCURSOR_ACT_EX], CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   カーソルアニメUpdate処理
 * @param   tcb			TCBへのポインタ
 * @param   work		カーソルワークへのポインタ
 */
//--------------------------------------------------------------
static void CCURSOR_ObjectUpdate(TCB_PTR tcb, void *work)
{
	CCURSOR_WORK *cursor = work;
	int i;
	
	if(CATS_ObjectEnableGetCap(cursor->cap[CCURSOR_ACT_LU]) == CATS_ENABLE_FALSE){
		return;
	}
	
	for(i = 0; i < CCURSOR_ACT_EX; i++){
		CATS_ObjectUpdateCap(cursor->cap[i]);
	}
	if(CATS_ObjectEnableGetCap(cursor->cap[CCURSOR_ACT_EX]) == CATS_ENABLE_TRUE){
		CATS_ObjectUpdateCap(cursor->cap[CCURSOR_ACT_EX]);
	}
}

