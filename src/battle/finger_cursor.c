//==============================================================================
/**
 * @file	finger_cursor.c
 * @brief	指カーソル
 * @author	matsuda
 * @date	2006.06.13(火)
 */
//==============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "system/clact_tool.h"
#include "system/palanm.h"
#include "battle/battle_tcb_pri.h"

#include "battle/finger_cursor.h"
#include "src/demo/ev_pokeselect.naix"


//==============================================================================
//	定数定義
//==============================================================================
///Sin角度加算値(整数100倍)
#define FINGER_ADD_ANGLE		(10 * 100)
///Sin移動ふり幅
#define FINGER_FURIHABA			(14)

///タッチアニメした時の座標オフセットY
#define FINGER_TOUCH_OFFSET_Y	(8)
///タッチアニメした時の座標戻りオフセットY
#define FINGER_TOUCH_BACK_Y		(2)
///タッチアニメをする前の停止ウェイト
#define FINGER_TOUCH_ANIME_BEFORE_WAIT	(3)
///タッチアニメした時のアニメウェイト
#define FINGER_TOUCH_ANIME_WAIT	(2)

//==============================================================================
//	構造体定義
//==============================================================================
///指カーソルワーク
typedef struct _FINGER_WORK{
	CATS_ACT_PTR cap;
	TCB_PTR update_tcb;
	int x;
	int y;
	int angle;
	fx32 surface_y;
	
	s16 touch_wait;
	u8 touch_req;
	u8 touch_occurrence;
	
	u8 touch_anime_flag;
	u8 touch_anime_seq;
	u8 touch_anime_wait;
}FINGER_WORK;

//==============================================================================
//	データ
//==============================================================================
///AA用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S FingerObjParam = {
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
void FINGER_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
void FINGER_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id);
FINGER_PTR FINGER_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri);
void FINGER_ActorDelete(FINGER_PTR finger);
void FINGER_PosSetON(FINGER_PTR finger, int x, int y);
void FINGER_OFF(FINGER_PTR finger);
static void FINGER_ObjectUpdate(TCB_PTR tcb, void *work);
static void FINGER_SubWorkClear(FINGER_PTR finger);



//--------------------------------------------------------------
/**
 * @brief   指カーソルのリソースをロードする
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
void FINGER_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp, 
		ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_cursol_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DSUB, pal_id);
	CATS_LoadResourceCharArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, char_id);
	CATS_LoadResourceCellArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NCER, 0, cell_id);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_EV_POKESELECT_GRA, 
		NARC_ev_pokeselect_psel_cursol_NANR, 0, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルのリソースを解放する
 *
 * @param   crp			
 * @param   char_id		キャラID
 * @param   pal_id		パレットID
 * @param   cell_id		セルID
 * @param   anm_id		アニメID
 */
//--------------------------------------------------------------
void FINGER_ResourceFree(CATS_RES_PTR crp, u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id)
{
	CATS_FreeResourceChar(crp, char_id);
	CATS_FreeResourcePltt(crp, pal_id);
	CATS_FreeResourceCell(crp, cell_id);
	CATS_FreeResourceCellAnm(crp, anm_id);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルのアクターを生成します
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
 * @retval  生成された指カーソルワークのポインタ
 *
 * 指カーソルワークの生成とUpdate用TCBの生成も同時に行います
 * 生成時は表示OFFになっています。
 */
//--------------------------------------------------------------
FINGER_PTR FINGER_ActorCreate(CATS_SYS_PTR csp, CATS_RES_PTR crp, int heap_id,
	u32 char_id, u32 pal_id, u32 cell_id, u32 anm_id, u32 soft_pri, u32 bg_pri)
{
	FINGER_WORK *finger;
	TCATS_OBJECT_ADD_PARAM_S obj_head;
	
	obj_head = FingerObjParam;
	obj_head.id[CLACT_U_CHAR_RES] = char_id;
	obj_head.id[CLACT_U_PLTT_RES] = pal_id;
	obj_head.id[CLACT_U_CELL_RES] = cell_id;
	obj_head.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_head.pri = soft_pri;
	obj_head.bg_pri = bg_pri;
	
	finger = sys_AllocMemory(heap_id, sizeof(FINGER_WORK));
	MI_CpuClear8(finger, sizeof(FINGER_WORK));
	
	finger->cap = CATS_ObjectAdd_S(csp, crp, &obj_head);
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_FALSE);
	
	finger->surface_y = SUB_SURFACE_Y;
	finger->update_tcb = TCB_Add(FINGER_ObjectUpdate, finger, TCBPRI_FINGER);
	return finger;
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルアクターを削除します
 *
 * @param   finger		指カーソルワークへのポインタ
 *
 * 指カーソルワークの解放と、Update用TCBの削除も行います
 */
//--------------------------------------------------------------
void FINGER_ActorDelete(FINGER_PTR finger)
{
	CATS_ActorPointerDelete_S(finger->cap);
	
	TCB_Delete(finger->update_tcb);
	sys_FreeMemoryEz(finger);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルの座標セットと表示のONを行います(サーフェース指定)
 *
 * @param   finger		指カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void FINGER_PosSetON_Surface(FINGER_PTR finger, int x, int y, fx32 surface_y)
{
	FINGER_SubWorkClear(finger);
	
	finger->x = x;
	finger->y = y;
	finger->surface_y = surface_y;
	CATS_ObjectPosSetCap_SubSurface(finger->cap, x, y, surface_y);
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルの座標セットと表示のONを行います
 *
 * @param   finger		指カーソルワークへのポインタ
 * @param   left		左座標
 * @param   right		右座標
 * @param   top			上座標
 * @param   bottom		下座標
 */
//--------------------------------------------------------------
void FINGER_PosSetON(FINGER_PTR finger, int x, int y)
{
	FINGER_PosSetON_Surface(finger, x, y, SUB_SURFACE_Y);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルを全て表示OFFする
 * @param   finger		指カーソルワークへのポインタ
 */
//--------------------------------------------------------------
void FINGER_OFF(FINGER_PTR finger)
{
	CATS_ObjectEnableCap(finger->cap, CATS_ENABLE_FALSE);
	FINGER_SubWorkClear(finger);
}

//--------------------------------------------------------------
/**
 * @brief   指カーソルにタッチアニメリクエストを発行する
 *
 * @param   finger		指カーソルワークへのポインタ
 * @param   wait		タッチアニメを発動するまでのウェイト
 *
 * タッチアニメが発動したかどうかは、FINGER_TouchAnimeCheckで確認出来ます。
 * タッチアニメはwaitが0になっていて、なおかつSinカーブ移動で一番下を指している時に発動します。
 */
//--------------------------------------------------------------
void FINGER_TouchReq(FINGER_PTR finger, int wait)
{
	finger->touch_wait = wait;
}

//--------------------------------------------------------------
/**
 * @brief   タッチアニメが発動したかチェック
 *
 * @param   finger		指カーソルワークへのポインタ
 *
 * @retval  TRUE:発動した。　FALSE:発動していない
 */
//--------------------------------------------------------------
BOOL FINGER_TouchAnimeCheck(FINGER_PTR finger)
{
	return finger->touch_occurrence;
}

//--------------------------------------------------------------
/**
 * @brief   カーソルアニメUpdate処理
 * @param   tcb			TCBへのポインタ
 * @param   work		カーソルワークへのポインタ
 */
//--------------------------------------------------------------
static void FINGER_ObjectUpdate(TCB_PTR tcb, void *work)
{
	FINGER_WORK *finger = work;
	
	if(finger->touch_occurrence == TRUE){
		finger->touch_occurrence = FALSE;
	}
	
	if(finger->touch_wait > 0){
		finger->touch_wait--;
		if(finger->touch_wait == 0){
			finger->touch_req = TRUE;
		}
	}
	
	if(CATS_ObjectEnableGetCap(finger->cap) == CATS_ENABLE_FALSE){
		return;
	}
	
	//Sinカーブ移動
	if(finger->touch_anime_flag == FALSE){
		int offset_y;
		
		finger->angle += FINGER_ADD_ANGLE;
		if(finger->angle >= 180*100){
			finger->angle -= 180*100;
			if(finger->touch_req == TRUE){
				finger->touch_anime_flag = TRUE;
				finger->touch_req = FALSE;
			}
		}
		
		if(finger->touch_anime_flag == FALSE){
			offset_y = FX_Mul(Sin360(finger->angle / 100), FINGER_FURIHABA << FX32_SHIFT) 
				/ FX32_ONE;
			CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, finger->y - offset_y,
				finger->surface_y);
		}
	}
	
	//タッチアニメ
	if(finger->touch_anime_flag == TRUE){
		switch(finger->touch_anime_seq){
		case 0:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_BEFORE_WAIT){
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		case 1:
			CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, 
				finger->y + FINGER_TOUCH_OFFSET_Y, finger->surface_y);
			finger->touch_occurrence = TRUE;
			finger->touch_anime_seq++;
			break;
		case 2:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_WAIT){
				CATS_ObjectPosSetCap_SubSurface(finger->cap, finger->x, 
					finger->y + FINGER_TOUCH_BACK_Y, finger->surface_y);
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		case 3:
			finger->touch_anime_wait++;
			if(finger->touch_anime_wait > FINGER_TOUCH_ANIME_WAIT){
				FINGER_OFF(finger);
				finger->touch_anime_wait = 0;
				finger->touch_anime_seq++;
			}
			break;
		default:
			break;
		}
	}
	
	CATS_ObjectUpdateCap(finger->cap);
}

//--------------------------------------------------------------
/**
 * @brief   色々なサブパラメータをクリアする
 * @param   finger		指カーソルワークへのポインタ
 */
//--------------------------------------------------------------
static void FINGER_SubWorkClear(FINGER_PTR finger)
{
	finger->angle = 0;
	finger->touch_anime_flag = FALSE;
	finger->touch_anime_seq = 0;
	finger->touch_anime_wait = 0;
}
