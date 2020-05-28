//==============================================================================
/**
 * @file	cb_seal.c
 * @brief	シール
 * @author	goto
 * @date	2006.04.13(木)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"

#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"

#include "include/poketool/pokeicon.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"


#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"

#include "include/application/cb_sys.h"
#include "battle/battle_common.h"
#include "system/wipe.h"

#include "battle/graphic/batt_bg_def.h"
#include "include/application/cb_sys.h"
#include "data/cb_data_def.h"
#include "wazaeffect/ball_effect_tool.h"

#include "cb_snd_def.h"

#include <nitro/sinit.h>
#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
static void NitroStaticInit(void)
{
	Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);
}



#define SEAL_32x32_NCER		(CB__SEAL_01_NCER_BIN)
#define SEAL_32x32_NANR		(CB__SEAL_01_NANR_BIN)

///< プロトタイプ

static const RECT_HIT_TBL default_hit_rect = {
	SEAL_DEF_POS_X-16, SEAL_DEF_POS_Y-16,
	SEAL_DEF_POS_X+16, SEAL_DEF_POS_Y+16,
};

static void HitTable_Create(RECT_HIT_TBL* tbl, u8 x, u8 y)
{
	tbl->rect.top		= y - SEAL_HIT_SIZE_Y;
	tbl->rect.left		= x - SEAL_HIT_SIZE_X;
	tbl->rect.bottom	= y + SEAL_HIT_SIZE_Y;
	tbl->rect.right		= x + SEAL_HIT_SIZE_X;
}

static void HitTable_CreateDisp(RECT_HIT_TBL* tbl)
{
	tbl->rect.top		= 0;
	tbl->rect.left		= 0;
	tbl->rect.bottom	= 192;
	tbl->rect.right		= 255;
}

void HitTable_CreateCap(RECT_HIT_TBL* tbl, CATS_ACT_PTR cap, BOOL tp_set)
{
	s16 x,y;
	
	if (cap == NULL){
		return;
	}

	if (tp_set == TRUE){
		CATS_ObjectPosSetCap(cap, sys.tp_x, sys.tp_y);
		CATS_ObjectPosGetCap(cap, &x, &y);
		HitTable_CreateDisp(tbl);
	}
	else {
		CATS_ObjectPosGetCap(cap, &x, &y);
		HitTable_Create(tbl, x, y);
	}
}

void CBS_Seal_ViewPosSet(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].cap == NULL){ continue; }
		
		CATS_ObjectPosMoveCap(cbmw->seal[i].cap, -CB_DEF_SEAL_OFS_X, -CB_DEF_SEAL_OFS_Y);
	}
}

void CBS_Seal_EditPosSet(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].cap == NULL){ continue; }
		
		CATS_ObjectPosMoveCap(cbmw->seal[i].cap, CB_DEF_SEAL_OFS_X, CB_DEF_SEAL_OFS_Y);
	}
}

///< ロード＆初期化
void CBS_LoadInit(CB_MAIN_WORK* cbmw)
{
	int i;
	
	CB_CORE* core;
	
	core = cbmw->cb_edit_data[ cbmw->select[0] ].core;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (core->cb_seal[i].seal_id != 0){
			cbmw->seal[i].id  = core->cb_seal[i].seal_id;	///< セーブから引継ぎ
			cbmw->seal[i].x   = core->cb_seal[i].x;
			cbmw->seal[i].y	  = core->cb_seal[i].y;

			CBS_Add(cbmw, i);
			HitTable_CreateCap(cbmw->seal[i].hit, cbmw->seal[i].cap, FALSE);
		//	CATS_ObjectEnableCap(cbmw->seal[i].cap, CATS_ENABLE_TRUE);
		//	CATS_ObjectUpdateCap(cbmw->seal[i].cap);

			cbmw->seal[i].pop = TRUE;						///< OBJ登録後POPさせる
		}
		else {		
			cbmw->seal[i].pop = FALSE;
			cbmw->seal[i].id  = 0;
		}
	}
}

///< 空きを探す
int CBS_SearchPop(CB_MAIN_WORK* cbmw, u8 id)
{
	int i;
	u32 x, y;

	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop == TRUE){ continue; }

		cbmw->seal[i].id  = cbmw->page.item[id];
		cbmw->seal[i].x	  = SEAL_DEF_POS_X;
		cbmw->seal[i].y	  = SEAL_DEF_POS_Y;
		
		GF_TP_GetPointCont(&x, &y);
		cbmw->seal[i].x	  = x;
		cbmw->seal[i].y	  = y;
		
		CBS_Add(cbmw, i);
	//	HitTable_CreateCap(cbmw->seal[i].hit, cbmw->seal[i].cap, FALSE);
		CBS_PriSetTop(cbmw, i);
	//	CBS_Pri_HitTbl_Sort(cbmw);
		
		cbmw->seal[i].pop = TRUE;
		
		return i;
	}
	
	return CB_DEF_NOT_HOLD;
}

BOOL CBS_IsPop(CB_MAIN_WORK* cbmw)
{
	int i;
	u32 x, y;

	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop == TRUE){ continue; }
		
		return TRUE;
	}
	
	return FALSE;
}

#define CB_DEF_SEAL_ADD_TOP_PRI		(20)
#define CB_DEF_SEAL_ADD_DEF_PRI		(30)
void CBS_PriSetTop(CB_MAIN_WORK* cbmw, u8 id)
{
	int i;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop != TRUE){ continue; }		
		
		if (i == id){
			CATS_ObjectPriSetCap(cbmw->seal[i].cap, 0);
		}
		else {
			int pri = CATS_ObjectPriGetCap(cbmw->seal[i].cap);
			if (pri == 0){
				CATS_ObjectPriSetCap(cbmw->seal[i].cap, pri + 1);
			}
			else {
				CATS_ObjectPriSetCap(cbmw->seal[i].cap, pri + 2);
			}
		}
	}
}

void CBS_ResLoad(CB_MAIN_WORK* cbmw, u8 one_id, u8 id)
{
	int char_id;
	int char_add_id;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	
	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;	

	///< パレット
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp,
								 ARC_CUSTOM_BALL_GRA, CB_SEAL_NCLR, FALSE,
								 1, NNS_G2D_VRAM_TYPE_2DSUB,
								 CB_ENUM_SEAL_PLTT_ID + CB_SEAL_NCLR);	
	
	char_id = Seal_CharArcGet(one_id);
	char_add_id = CB_DEF_ARC_ID_SEAL_GET(id);

	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, char_id, TRUE,
							 NNS_G2D_VRAM_TYPE_2DSUB,
							 char_add_id);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB__SEAL_01_NCER_BIN, TRUE,
							 CB_ENUM_SEAL_CELL_ID + CB__SEAL_01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB__SEAL_01_NANR_BIN, TRUE,
								CB_ENUM_SEAL_CELLANM_ID + CB__SEAL_01_NANR_BIN);
}
/*
	for (i = CB_BHIT_SEAL_0; i < CB_BHIT_SEAL_MAX; i++){
		cbmw->sys.hit_tbl[i] = hit_tbl_dmy;
		cbmw->seal[i - CB_BHIT_SEAL_0].hit = &cbmw->sys.hit_tbl[i];
	}
*/
void CBS_Pri_HitTbl_Sort(CB_MAIN_WORK* cbmw)
{
	int i, j;
	int num;
	int pri[ CB_DEF_SEAL_MAX ];
	int idx[ CB_DEF_SEAL_MAX ];
	
	num = 0;
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		pri[ i ] = 0xFF;
		idx[ i ] = 0xFF;
		if (cbmw->seal[ i ].cap != NULL){
			pri[ i ] = CATS_ObjectPriGetCap(cbmw->seal[ i ].cap);
			idx[ i ] = i;
			num++;
		}
	}
	
	{
		int pri_tmp;
		int idx_tmp;
			
		for (i = 0; i < CB_DEF_SEAL_MAX - 1; i++){
			for (j = CB_DEF_SEAL_MAX - 1; j > i; j--){
				if (pri[ j - 1 ] > pri[ j ]){
					pri_tmp = pri[ j ];
					idx_tmp = idx[ j ];
	                pri[ j ] = pri[ j - 1 ];
	                idx[ j ] = idx[ j - 1 ];
					pri[ j - 1 ] = pri_tmp;
					idx[ j - 1 ] = idx_tmp;
				}
			}
		}
	}
	
	{
		RECT_HIT_TBL hit_tbl[ CB_DEF_HIT_TBL_MAX ];
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			hit_tbl[ i ] = cbmw->sys.hit_tbl[ i + CB_BHIT_SEAL_0 ];
		}
		
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			if (idx[i] == 0xFF){
				continue;
			}
			cbmw->sys.hit_tbl[ i + CB_BHIT_SEAL_0 ] = hit_tbl[ idx[i] ];
		}
		
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			if (idx[i] == 0xFF){
				continue;
			}
			cbmw->seal[ idx[ i ] ].hit = &cbmw->sys.hit_tbl[ i + CB_BHIT_SEAL_0 ];
		}
	
	}
#if 0
	int i, j;
	int tbl_tmp;
	int idx_tmp;
	int num;
	int pri_tbl[ CB_DEF_SEAL_MAX ];
	int pri_idx[ CB_DEF_SEAL_MAX ];
	
	num = 0;
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		if (cbmw->seal[ i ].cap != NULL){
			num++;
			pri_tbl[ i ] = CATS_ObjectPriGetCap(cbmw->seal[ i ].cap);	
		}
		else {
			pri_tbl[ i ] = 0xFF;	
		}
		pri_idx[ i ] = i;
	}
	OS_Printf("num = %2d\n", num);
	for (i = 0; i < CB_DEF_SEAL_MAX - 1; i++){
		for (j = CB_DEF_SEAL_MAX - 1; j > i; j--){
			if (pri_tbl[ j - 1 ] >= pri_tbl[ j ]){
				tbl_tmp = pri_tbl[ j ];
				idx_tmp = pri_idx[ j ];
                pri_tbl[ j ] = pri_tbl[ j - 1 ];
                pri_idx[ j ] = pri_idx[ j - 1 ];
				pri_tbl[ j - 1 ] = tbl_tmp;
				pri_idx[ j - 1 ] = idx_tmp;
			}
		}
	}

	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		OS_Printf("sort ID = %2d pri = %2d\n", pri_idx[ i ], pri_tbl[ i ]);
		
		if (cbmw->seal[ i ].cap != NULL){
			cbmw->seal[ i ].hit = &cbmw->sys.hit_tbl[ CB_ENUM_BTN_NUM + pri_idx[ num - 1 - i ] ];
			HitTable_CreateCap(cbmw->seal[ i ].hit, cbmw->seal[ i ].cap, FALSE);
			CATS_ObjectPriSetCap(cbmw->seal[ i ].cap, pri_tbl[ num - 1 - i ] + 1);	
			OS_Printf("change pri = %2d\n", pri_tbl[ num - 1 - i ]);
			OS_Printf("change idx = %2d\n", pri_idx[ num - 1 - i ]);
		}

	}
#endif		
}

void CBS_SVSort(CB_MAIN_WORK* cbmw)
{
	int i, j;
	int num;
	int pri[ CB_DEF_SEAL_MAX ];
	int idx[ CB_DEF_SEAL_MAX ];
	
	if (cbmw->sys.bEdit == FALSE){ return; }
	cbmw->sys.bEdit = FALSE;
	
	num = 0;
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		pri[ i ] = 0xFF;
		idx[ i ] = 0xFF;
		if (cbmw->seal[ i ].cap != NULL){
			pri[ i ] = CATS_ObjectPriGetCap(cbmw->seal[ i ].cap);
			idx[ i ] = i;
			num++;
		}
	}
	
	{
		int pri_tmp;
		int idx_tmp;
			
		for (i = 0; i < CB_DEF_SEAL_MAX - 1; i++){
			for (j = CB_DEF_SEAL_MAX - 1; j > i; j--){
				if (pri[ j - 1 ] >= pri[ j ]){
					pri_tmp = pri[ j ];
					idx_tmp = idx[ j ];
	                pri[ j ] = pri[ j - 1 ];
	                idx[ j ] = idx[ j - 1 ];
					pri[ j - 1 ] = pri_tmp;
					idx[ j - 1 ] = idx_tmp;
				}
			}
		}
	}
	
	{
		CB_CORE core;
		CB_CORE core_tmp;
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			core.cb_seal[i].seal_id = cbmw->seal[i].id;
			core.cb_seal[i].x		= cbmw->seal[i].x;
			core.cb_seal[i].y		= cbmw->seal[i].y;
		}
		core_tmp = core;
		
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			if (idx[i] == 0xFF){
				cbmw->seal[i].id = 0;
				cbmw->seal[i].x	 = 0;
				cbmw->seal[i].y	 = 0;
				continue;
			}
			
			cbmw->seal[i].id = core_tmp.cb_seal[ idx[i] ].seal_id;
			cbmw->seal[i].x	 = core_tmp.cb_seal[ idx[i] ].x;
			cbmw->seal[i].y	 = core_tmp.cb_seal[ idx[i] ].y;
			
			if (cbmw->seal[ idx[i] ].cap == NULL){ continue; }
			
			CATS_ObjectPriSetCap(cbmw->seal[ idx[i] ].cap, i);
			
//			CATS_ObjectPosSetCap(cbmw->seal[i].cap, cbmw->seal[i].x, cbmw->seal[i].y);		///< 追加
//			HitTable_Create(cbmw->seal[i].hit, cbmw->seal[i].x, cbmw->seal[i].y);			///< 追加
		}
	}
}

///< シールOBJを追加
BOOL CBS_Add(CB_MAIN_WORK* cbmw, u8 id)
{
	int char_id;
	int char_add_id;
	CB_SEAL_ONE* one;
	
	TCATS_OBJECT_ADD_PARAM_S coap;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;	
	
	one = &cbmw->seal[id];
	
	if (one->pop == TRUE){
		GF_ASSERT(0);
		return FALSE;
	}
	
	CBS_ResLoad(cbmw, one->id, id);
	
	coap.x		= one->x;
	coap.y		= one->y;
	coap.z		= 0;		
	coap.anm	= 0;
	coap.pal	= 0;
	coap.vram_trans = 0;

	coap.pri	= 0;
	coap.d_area = CATS_D_AREA_SUB;
	coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ;
	coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
	coap.id[5]	= CLACT_U_HEADER_DATA_NONE;

	char_id = Seal_CharArcGet(one->id);
	char_add_id = CB_DEF_ARC_ID_SEAL_GET(id);
	
	coap.id[0]	= char_add_id;
	coap.id[1]	= CB_ENUM_SEAL_PLTT_ID + CB_SEAL_NCLR;
	coap.id[2]	= CB_ENUM_SEAL_CELL_ID + CB__SEAL_01_NCER_BIN;
	coap.id[3]	= CB_ENUM_SEAL_CELLANM_ID + CB__SEAL_01_NANR_BIN;
	
	one->cap = CATS_ObjectAdd_S(csp, crp, &coap);
	CATS_ObjectUpdateCap(one->cap);
	
	return TRUE;
}


BOOL CBS_SealHold(CB_MAIN_WORK* cbmw, u32 event, u8 id)
{
	if (cbmw->seal[id].pop == FALSE){ return TRUE; }
	
	switch(event){
	case BMN_EVENT_TOUCH:
		if (cbmw->sys.hold == CB_DEF_NOT_HOLD){
			cbmw->sys.hold = id;
			CBS_PriSetTop(cbmw, id);
		}
		break;

	case BMN_EVENT_HOLD:
		{
			s16 x,y;
			if (cbmw->sys.hold == id){
				HitTable_CreateCap(cbmw->seal[id].hit, cbmw->seal[id].cap, TRUE);
				CBS_ReleasePointCheckTypeSet(cbmw, id);
				CBS_EditDataRefrect(cbmw, id);
			}
		}
		break;

	case BMN_EVENT_SLIDEOUT:
	case BMN_EVENT_RELEASE:
		{
			BOOL release;
							
			if (cbmw->sys.hold == CB_DEF_NOT_HOLD){
				release = CBS_ReleasePointCheck(cbmw, id);
				HitTable_CreateCap(cbmw->seal[id].hit, cbmw->seal[id].cap, FALSE);
				
				if (release == FALSE){
					CBS_Release(cbmw, id);
				}
				
				cbmw->sys.hold = CB_DEF_NOT_HOLD;
			}
		}
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return TRUE;
}

///< 全体削除
void CBS_Delete(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop != TRUE){ continue; }	
		
		CBS_Release(cbmw, i);
		
		/*
		CATS_ActorPointerDelete_S(cbmw->seal[i].cap);
		cbmw->seal[i].cap = NULL;
		cbmw->seal[i].pop = FALSE;
		*/
	}
}

///< 非表示
void CBS_Enable(CB_MAIN_WORK* cbmw, int flag)
{
	int i;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop != TRUE){ continue; }
		
		CATS_ObjectEnableCap(cbmw->seal[i].cap, flag);
		
	}	
}

///< てんとてんの距離
int  CBS_PtoP(s16 x1, s16 y1, s16 x2, s16 y2)
{
	int range;
	
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	
	range = FX_Sqrt( ((py*py)+(px*px)) * FX32_ONE ) / FX32_ONE;
	
	return range;
}

///< 中心からの距離がリリースポイント化チェック
BOOL CBS_ReleasePointCheck(CB_MAIN_WORK* cbmw, int id)
{
	int range;
	s16 x, y;
	
	if (cbmw->seal[id].pop == FALSE){ return TRUE; }
	
	CATS_ObjectPosGetCap(cbmw->seal[id].cap, &x, &y);
	
	range = BET_PtoP(x, y, SEAL_DEF_POS_X, SEAL_DEF_POS_Y);
	
	if (range > CB_RELEASE_RANGE){
		return FALSE;
	}
	
	return TRUE;
}


///< 解放
void CBS_Release(CB_MAIN_WORK* cbmw, int id)
{
	int char_id;
	int char_add_id;
	
	char_id = Seal_CharArcGet(cbmw->seal[id].id);
	char_add_id = CB_DEF_ARC_ID_SEAL_GET(id);
	
	CATS_FreeResourceChar(cbmw->sys.crp, char_add_id);
	CATS_ActorPointerDelete_S(cbmw->seal[id].cap);

	cbmw->seal[id].cap = NULL;
	cbmw->seal[id].pop = FALSE;	
	cbmw->seal[id].id  = 0;
	cbmw->seal[id].x   = 0;
	cbmw->seal[id].y   = 0;
	
	HitTable_Create(cbmw->seal[id].hit, 0, 0);
}

///< 解放位置にきてるときに半透明
void CBS_ReleasePointCheckTypeSet(CB_MAIN_WORK* cbmw, int id)
{
	BOOL range;
	
	range = CBS_ReleasePointCheck(cbmw, id);
	
	if (range == FALSE){
		CATS_ObjectObjModeSetCap(cbmw->seal[ id ].cap, GX_OAM_MODE_XLU);	
	}
	else {
		CATS_ObjectObjModeSetCap(cbmw->seal[ id ].cap, GX_OAM_MODE_NORMAL);	
	}
}

///< 元データとのチェック
BOOL CBS_CheckEditData(CB_MAIN_WORK* cbmw)
{
	int i;
	int sel;
	CB_CORE* core;
	
	sel = cbmw->select[0];
	
	core = cbmw->cb_edit_data[ sel ].core;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
//		if (cbmw->seal[i].pop == FALSE){ continue; }
		
		if (cbmw->seal[i].id != core->cb_seal[i].seal_id
		||	cbmw->seal[i].x  != core->cb_seal[i].x
		||	cbmw->seal[i].y  != core->cb_seal[i].y){
			return TRUE;
		}		
	}
	
	return FALSE;
}

void CBS_OldEditDataSet(CB_MAIN_WORK* cbmw)
{
	int i;
	int sel;
	CB_CORE* core;
	
	sel = cbmw->select[0];
	
	core = cbmw->cb_edit_data[ sel ].core;
	
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		if (cbmw->seal[i].pop == TRUE){
			CB_SaveData_ItemNumAddCheck(cbmw->cb_pw->save_data, cbmw->seal[i].id, +1);
		}
		
		cbmw->seal[i].id = core->cb_seal[i].seal_id;
		cbmw->seal[i].x  = core->cb_seal[i].x;
		cbmw->seal[i].y  = core->cb_seal[i].y;
	}
}

void CBS_EditDataRefrect(CB_MAIN_WORK* cbmw, int id)
{
	s16 x, y;
	
	CATS_ObjectPosGetCap(cbmw->seal[id].cap, &x, &y);
	
	cbmw->seal[id].x = (u8)x;
	cbmw->seal[id].y = (u8)y;
}

void CBS_EditData_Save(CB_MAIN_WORK* cbmw)
{
	int i;
	CB_CORE core;
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		core.cb_seal[i].seal_id = cbmw->seal[i].id;
		core.cb_seal[i].x = cbmw->seal[i].x;
		core.cb_seal[i].y = cbmw->seal[i].y;
	}

	CB_SaveData_CoreDataSet(cbmw->cb_pw->save_data, &core, cbmw->select[0]);
}

///< テストデータ作成
void CBS_TestCoreData_Create(CB_CORE* core, CB_MAIN_WORK* cbmw)
{
	int i;
	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		core->cb_seal[i].seal_id = cbmw->seal[i].id;
		core->cb_seal[i].x		 = cbmw->seal[i].x;
		core->cb_seal[i].y		 = cbmw->seal[i].y;
	}
}
