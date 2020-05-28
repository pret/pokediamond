//==============================================================================
/**
 * @file	cb_main.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.04.03(月)
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

#include "data/cb_data_def.h"

#include "system/pm_overlay.h"

#include "cb_snd_def.h"
#include "pokeanime/p_anm_sys.h"

#include "savedata/record.h"

///< バックアップ

void BackupEditData_Make(CB_MAIN_WORK* cbmw)
{
	CB_Tool_CoreData_Copy(cbmw->cb_edit_data[ cbmw->select[0] ].core, &cbmw->backup_edit);
#if 0
	{
		int i;
		OS_Printf("バックアップ\n");
		
		for (i = 0; i < 8; i++){
			CB_SEAL* seal = CB_SaveData_SealDataGet(cbmw->cb_edit_data[ cbmw->select[0] ].core, i);
			OS_Printf("seal id = %2d\n", CB_SaveData_SealIDGet(seal));
		}
	}
#endif
}

void BackupEditData_Recover(CB_MAIN_WORK* cbmw)
{
	CB_Tool_CoreData_Copy(&cbmw->backup_edit, cbmw->cb_edit_data[ cbmw->select[0] ].core);
#if 0
	{
		int i;
		OS_Printf("リカバー\n");
		
		for (i = 0; i < 8; i++){
			CB_SEAL* seal = CB_SaveData_SealDataGet(cbmw->cb_edit_data[ cbmw->select[0] ].core, i);
			OS_Printf("seal id = %2d\n", CB_SaveData_SealIDGet(seal));
		}
	}
#endif
}

void BackupItemData_Make(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_ITEM_DATA_NUM; i++){
		
		cbmw->backup_item[ i ] = CB_SaveData_ItemNumGet_CBO(cbmw->cb_item_data, i);
		
	}	
}

void BackupItemData_Recover(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_ITEM_DATA_NUM; i++){
		
		CB_SaveData_ItemNumSet(cbmw->cb_item_data, i, cbmw->backup_item[ i ]);
		
	}
}



void CB_Tool_DefaultBlendSet(void)
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					 GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2, 11, 7);
	G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					  GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 |
					  GX_BLEND_PLANEMASK_BG3, 7, 8);
}

void CB_Tool_TestPokemonCreate(CB_MAIN_WORK* cbmw)
{
	int i;
	int ret;
	POKEMON_PARAM* pp;
	
	if (cbmw->cb_edit_data[ cbmw->select[0] ].poke_idx != CB_DEF_POKE_NOT_INDEX){
		
		pp = cbmw->cb_pw->poke_para[ cbmw->cb_edit_data[ cbmw->select[0] ].poke_idx ];
		
		PokeCopyPPtoPP(pp, cbmw->test_pp);
		
		return;
	}
	
	for (i = 0; i < cbmw->cb_pw->poke_cnt; i++){
		
		pp = cbmw->cb_pw->poke_para[ i ];
		
		ret = PokeParaGet(pp, ID_PARA_tamago_flag, NULL);

		if (ret != 0){ continue; }
		
		PokeCopyPPtoPP(pp, cbmw->test_pp);
		
		break;
	}
}

///< OBJ関連
int CB_Tool_IsEdit(CB_CORE* core)
{
	int i;
	int edit = CB_DEF_EDIT_OFF;
	int seal_num;
	CB_SEAL* seal;

	seal_num = 0;

	for (i = 0; i < CB_DEF_SEAL_MAX; i++){
		
		seal = CB_SaveData_SealDataGet(core, i);
		
		if (CB_SaveData_SealIDGet(seal) != CB_DEF_SEAL_NONE){
			seal_num++;
		}
	}
	
	if (seal_num != 0){
		edit = CB_DEF_EDIT_ON;
	}
	
	return edit;
}

///< ボールの状態確認
int CB_Tool_BallStatusCheck(CB_MAIN_WORK* cbmw, int no)
{
	int poke;
	int edit;
	int flag;
	
	poke = cbmw->mo[no].poke_idx;
	edit = cbmw->mo[no].edit_flag;
	
	if (poke == CB_DEF_POKE_NOT_INDEX && edit == CB_DEF_EDIT_OFF){
		flag = CB_ENUM_BALL_STATE_FREE;
	}
	else if (poke == CB_DEF_POKE_NOT_INDEX && edit == CB_DEF_EDIT_ON){
		flag = CB_ENUM_BALL_STATE_CUSTOM;
	}
	else if (poke != CB_DEF_POKE_NOT_INDEX && edit == CB_DEF_EDIT_ON){
		flag = CB_ENUM_BALL_STATE_CUSTOM_SET;
	}
	else {
		flag = CB_ENUM_BALL_STATE_FREE_SET;
	}
	
	return flag;
}

static void CB_Sub_SeqChange(CB_MAIN_WORK* cbmw, int mode, int seq, int keep_seq)
{
	if (seq == CB_DEF_KEEP_SEQ_SET){
		cbmw->seq	= cbmw->keep_seq;
	}
	else {
		cbmw->seq	= seq;
	}
	cbmw->mode		= mode;
	cbmw->keep_seq	= keep_seq;
	cbmw->sub_seq	= 0;
}

///< めにゅー
static int CB_MENU_Cancel(CB_MAIN_WORK* cbmw)
{
	BmpMenuWinClear(&cbmw->sys.win[ 1 ], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinOff(&cbmw->sys.win[ 1 ]);
	BmpMenuExit(cbmw->sys.bmw, NULL);
	BMP_MENULIST_Delete(cbmw->sys.bml);	
	GF_BGL_BmpWinDel(&cbmw->sys.win[ 1 ]);
	
	return CB_ENUM_MENU_FUNC_RET_SEQ_PREV;
}


static int CB_MENU_Edit(CB_MAIN_WORK* cbmw)
{
	CB_Sub_SeqChange(cbmw, CB_MODE_EDIT, 0, CBS_SELECT_MAIN);

	return CB_ENUM_MENU_FUNC_RET_NONE;
}

static int CB_MENU_Set(CB_MAIN_WORK* cbmw)
{
	CBS_SVSort(cbmw);
	CBS_EditData_Save(cbmw);
	SubSelect_ObjRefrect(cbmw);
	
	CB_Sub_SeqChange(cbmw, CB_MODE_SETTING_SET, 0, 0);

	return CB_ENUM_MENU_FUNC_RET_NONE;
}

static int CB_MENU_Remove(CB_MAIN_WORK* cbmw)
{
	CB_Sub_SeqChange(cbmw, CB_MODE_SETTING_REMOVE, 0, CBS_SELECT_MAIN);

	return CB_ENUM_MENU_FUNC_RET_NONE;
}

static int CB_MENU_Change(CB_MAIN_WORK* cbmw)
{
	CB_Sub_SeqChange(cbmw, CB_MODE_CHANGE, 0, CBS_SELECT_MAIN);

	return CB_ENUM_MENU_FUNC_RET_NONE;
}


const TCB_MENU_PARAM CB_ParamTable[] = {
	{ msg_menu_00_01, (const u32)CB_MENU_Edit	},		///< へんしゅう
	{ msg_menu_00_02, (const u32)CB_MENU_Cancel },		///< やめる
	{ msg_menu_00_03, (const u32)CB_MENU_Set 	},		///< セット
	{ msg_menu_00_04, (const u32)CB_MENU_Remove },		///< はずす
	{ msg_menu_00_05, (const u32)CB_MENU_Change },		///< いれかえる
};

static BOOL CB_Sub_Select(CB_MAIN_WORK* cbmw);
static BOOL CB_Sub_Edit(CB_MAIN_WORK* cbmw);
static BOOL CB_Sub_SettingSet(CB_MAIN_WORK* cbmw);
static BOOL CB_Sub_SettingRemove(CB_MAIN_WORK* cbmw);
static BOOL CB_Sub_Change(CB_MAIN_WORK* cbmw);
static BOOL CB_Sub_End(CB_MAIN_WORK* cbmw);

static BOOL (* const CB_ModeTable[])(CB_MAIN_WORK* cbmw) = {
	CB_Sub_Select,
	CB_Sub_Edit,
	CB_Sub_SettingSet,
	CB_Sub_SettingRemove,
	CB_Sub_Change,
	CB_Sub_End,
};

BOOL CustomMain_Executed(CB_MAIN_WORK* cbmw)
{
	BOOL active;
	
	active = CB_ModeTable[ cbmw->mode ]( cbmw );
	
	CATS_Draw(cbmw->sys.crp);
	
	return active;
}

static BOOL	CB_Tool_CursorMove(int* cur)
{
	int* sel = cur;

	if (sys.repeat & PAD_KEY_RIGHT){
		(*sel)++;
		(*sel) %= CB_DEF_CORE_MAX;
	}
	else if (sys.repeat & PAD_KEY_LEFT){
		if (*sel > 0){
			(*sel)--;
		}
		else {
			*sel = CB_DEF_CORE_MAX - 1;
		}
	}
	else if (sys.repeat & PAD_KEY_UP){
		if (CB_DEF_CUR_MOVE_UD(*sel) != 0){
			(*sel) -= CB_DEF_LINE;
			(*sel) %= CB_DEF_CORE_MAX;
		}
		else {
			return FALSE;
		}					
	}
	else if (sys.repeat & PAD_KEY_DOWN){
		if (CB_DEF_CUR_MOVE_UD(*sel) != (CB_DEF_ROW - 1)){
			(*sel) += CB_DEF_LINE;
			(*sel) %= CB_DEF_CORE_MAX;
		}
		else {
			return FALSE;
		}				
	}
	else {
		return FALSE;
	}
	
	return TRUE;
}

///< 指定位置にいかないように移動する
static BOOL	CB_Tool_CursorMoveEx(int* cur, int pos)
{
	int move;
	int* sel = cur;
	int  pad;

	if (sys.repeat & PAD_KEY_RIGHT){
		pad = PAD_KEY_RIGHT;
	}
	else if (sys.repeat & PAD_KEY_LEFT){
		pad = PAD_KEY_LEFT;
	}
	else if (sys.repeat & PAD_KEY_UP){
		pad = PAD_KEY_UP;
	}
	else if (sys.repeat & PAD_KEY_DOWN){
		pad = PAD_KEY_DOWN;
	}
	else {
		return FALSE;
	}
	
	move = 0;
	do {

		switch(pad){
		case PAD_KEY_RIGHT:
			(*sel)++;
			(*sel) %= CB_DEF_CORE_MAX;
			break;
		case PAD_KEY_LEFT:
			if (*sel > 0){
				(*sel)--;
			}
			else {
				*sel = CB_DEF_CORE_MAX - 1;
			}
			break;
		case PAD_KEY_UP:
			if (CB_DEF_CUR_MOVE_UD(*sel) != 0){
				int tmp = *sel;
				tmp -= CB_DEF_LINE;
				tmp %= CB_DEF_CORE_MAX;
				if (tmp != pos){
					*sel = tmp;
				}
			}
			break;
		case PAD_KEY_DOWN:
			if (CB_DEF_CUR_MOVE_UD(*sel) != (CB_DEF_ROW - 1)){
				int tmp = *sel;
				tmp += CB_DEF_LINE;
				tmp %= CB_DEF_CORE_MAX;
				if (tmp != pos){
					*sel = tmp;
				}
			}
			move = 1;			
			break;
		}
		
		if (*sel != pos){
			move = 1;
		}
				
	} while(move == 0);
	
	return TRUE;
}

static void CB_Tool_CursorMovePosUpdate(CB_MAIN_WORK* cbmw, int no, BOOL sub_auto)
{
	s16 x, y;
	int sub = 0;
	
	if (no == 0){
		sub = 1;
	}
	
	CB_SelectThisPosGet(cbmw->select[no], &x, &y);
	CATS_ObjectPosSetCap(cbmw->cap_cur[no], x, y);
	
	if (sub_auto == TRUE){
		cbmw->select[sub] = cbmw->select[no];
		CB_SelectThisPosGet(cbmw->select[sub], &x, &y);
		CATS_ObjectPosSetCap(cbmw->cap_cur[sub], x, y);
	}	
}

static BOOL CB_Sub_Select(CB_MAIN_WORK* cbmw)
{	
	switch(cbmw->seq){
	case CBS_SELECT_INIT:
		///< OBJ+BG読み込み
		CB_Tool_PokeIcon_Load(cbmw);
		CB_Tool_PokeIcon_Add(cbmw);
		CB_Tool_PokeIcon_CheckPosSetup(cbmw);

		CB_Select_TopResLoad(cbmw);
		CB_Select_BottomResLoad(cbmw);
		CB_Edit_BottomResLoad(cbmw);
		CB_Tool_MarkObj_SetUp(cbmw);
		CB_Tool_SubSelect_ObjAdd(cbmw);
		CB_BMP_WindowAdd(cbmw->sys.bgl, &cbmw->sys.win[0], CB_DEF_STRING_BG_FRM,
						 CB_DEF_WIN_T_MAIN_X, CB_DEF_WIN_T_MAIN_Y,
						 CB_DEF_WIN_T_MAIN_SX, CB_DEF_WIN_T_MAIN_SY, CB_DEF_WIN_CHAR_OFS);
	
		CBS_LoadInit(cbmw);
		CBS_Enable(cbmw, CATS_ENABLE_TRUE);
		CBS_Seal_ViewPosSet(cbmw);
		
		///< 各ボタンのリソース読み込み、登録、非表示
		CB_Tool_BTN_ResLoad(cbmw);			///< ページ以外のOBJ
		CB_Tool_BTN_Add(cbmw);
		
		Piko_ResLoad(cbmw);
		Piko_Add(cbmw);

		BackupEditData_Make(cbmw);
		BackupItemData_Make(cbmw);
		PageData_Create(cbmw, cbmw->page.no);	///< ページ構築
		PageData_ResourceLoad(cbmw);			///< リソース読み込み
		PageData_Add(cbmw);						///< OBJ登録
		
		CB_Tool_BTN_Enable(cbmw, CATS_ENABLE_FALSE);
		Piko_Enable(cbmw, CATS_ENABLE_FALSE);
		
		FontOam_Add(cbmw);
		FontOam_Enable(cbmw, FALSE);
	
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
		CB_DispOn();
		CB_Sys_MainTPSet(cbmw, FALSE);
		
		cbmw->seq++;
		break;
		
	case CBS_SELECT_WIPE_IN:
		///< ワイプ
		CB_WipeFadeIn();
		cbmw->seq++;
		break;
	
	case CBS_SELECT_WIPE_IN_WAIT:
		///< ワイプ待ち
		if (WIPE_SYS_EndCheck() != TRUE){ break; }
		cbmw->seq++;
		
	case CBS_SELECT_MAIN:
		{
			BOOL is_input;
			int  old;
			int  now;
			
			if (GF_TP_GetTrg() == TRUE){
				CB_MENU_Edit(cbmw);
				break;
			}
			old = cbmw->select[0];
			is_input = CB_Tool_CursorMove(&(cbmw->select[0]));
			now = cbmw->select[0];
			cbmw->select[0] = old;

			if (is_input == TRUE){
				CBS_SVSort(cbmw);
				CBS_EditData_Save(cbmw);
				SubSelect_ObjRefrect(cbmw);
				cbmw->select[0] = now;
				CB_Tool_CursorMovePosUpdate(cbmw, 0, TRUE);
				CBS_Delete(cbmw);
				CBS_LoadInit(cbmw);
				CBS_Enable(cbmw, CATS_ENABLE_TRUE);
				CBS_Seal_ViewPosSet(cbmw);
				
				Snd_SePlay( CB_SE_CURSOR );
			}
			else if (sys.trg & PAD_BUTTON_A){
				cbmw->seq++;		
				CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_HDYD);
				CB_BMP_SelectWinAdd(cbmw->sys.bgl, &cbmw->sys.win[1], CB_DEF_STRING_BG_FRM, cbmw, cbmw->select[0]);
				
				Snd_SePlay( CB_SE_DEC_S );
			}
			else if (sys.trg & PAD_BUTTON_B){
				cbmw->seq = CBS_SELECT_WIPE_OUT;
				
				Snd_SePlay( SEQ_SE_DP_DECIDE );
			}
		}
		break;
	
	case CBS_SELECT_MENU:
		///< bmp
		{
			pCB_Menu_Func func;
			u32 ret = BmpMenuMain(cbmw->sys.bmw);
			
			switch(ret){
			case BMPMENU_CANCEL:
				CB_MENU_Cancel(cbmw);
				CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
				cbmw->seq = CBS_SELECT_MAIN;
				break;
			
			case BMPMENU_NULL:
				break;
			
			default:
				func = (pCB_Menu_Func)ret;
				if (func != NULL){
					int func_ret = func(cbmw);					
					if (func_ret != CB_ENUM_MENU_FUNC_RET_SEQ_PREV){
						CB_MENU_Cancel(cbmw);
						break;
					}
	
					CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
					cbmw->seq = CBS_SELECT_MAIN;
				}
				break;
			}
		}
		break;
	
	case CBS_SELECT_WIPE_OUT:
		///< 切り替え
		CB_WipeFadeOut();
		cbmw->seq++;
		break;
	
	case CBS_SELECT_WIPE_OUT_WAIT:
		///< ワイプまち
		if (WIPE_SYS_EndCheck() != TRUE){ break; }
		GF_BGL_BmpWinDel(&cbmw->sys.win[ 0 ]);
		SubSelect_ObjDelete(cbmw);	
		CB_Tool_PokeIcon_Del(cbmw);
		CB_Tool_BTN_Delete(cbmw);
		Piko_Delete(cbmw);
		PageData_Del(cbmw);					///< OBJ登録
		CBProc_NextModeSet(cbmw->cb_pw, CB_PROC_NEXT_MODE_END);
		return FALSE;
	}
	CB_Tool_PokeIcon_Update(cbmw);
	SubSelect_ObjUpdate(cbmw);

	return TRUE;
}


void CB_Tool_ButtonAnime(CATS_ACT_PTR cap, int event)
{
	switch(event){
	case BMN_EVENT_TOUCH:
		CATS_ObjectAnimeFrameSetCap(cap, 1);
		break;
	case BMN_EVENT_HOLD:
		CATS_ObjectAnimeFrameSetCap(cap, 2);
		break;
	case BMN_EVENT_RELEASE:
	case BMN_EVENT_SLIDEOUT:
		CATS_ObjectAnimeFrameSetCap(cap, 0);
		break;
	default:
		GF_ASSERT(0);
		break;
	}
}

typedef struct {
	
	int wait;
	CATS_ACT_PTR	cap;
	
	FONTOAM_OBJ_PTR font_obj;
	
} TBUTTON_ANIME;

/*
FONTOAM_SetMat( FONTOAM_OBJ_PTR fontoam, int x, int y );
FONTOAM_GetMat( CONST_FONTOAM_OBJ_PTR fontoam, int* x, int* y );
*/

static void FontOamPosSet(FONTOAM_OBJ_PTR obj, int ox, int oy)
{
	int x;
	int y;
	if (obj != NULL){
		FONTOAM_GetMat(obj, &x, &y);
		FONTOAM_SetMat(obj,  x + ox,  y + oy);
	}	
}

static void BA_Tcb(TCB_PTR tcb, void* work)
{
	TBUTTON_ANIME* wk = work;
	
	switch(wk->wait){
	case 3:
		FontOamPosSet(wk->font_obj, 0, -1);
		CATS_ObjectAnimeFrameSetCap(wk->cap, 2);
		wk->wait++;
		break;
	case 6:
		FontOamPosSet(wk->font_obj, 0, +2);
		CATS_ObjectAnimeFrameSetCap(wk->cap, 0);
		TCB_Delete(tcb);
		sys_FreeMemoryEz(wk);
		break;
	default:
		wk->wait++;
		break;
	};
}

static void BA_Init(CATS_ACT_PTR cap, FONTOAM_OBJ_PTR font_obj)
{
	TBUTTON_ANIME* wk;
	
	wk = sys_AllocMemory(HEAPID_CUSTOM_BALL, sizeof(TBUTTON_ANIME));
	
	wk->wait	 = 1;
	wk->cap		 = cap;
	wk->font_obj = font_obj;
	
	FontOamPosSet(wk->font_obj, 0, -1);
	
	TCB_Add(BA_Tcb, wk, 1000);
}

void CB_Tool_ButtonAutoUpdate(CB_MAIN_WORK* cbmw)
{
	int i;
	int seq;
#if 0
	for (i = CB_ENUM_BHIT_UP; i < CB_ENUM_BTN_NUM; i++){
		
		seq = CATS_ObjectAnimeFrameGetCap(cbmw->button_obj.cap[i]);
		
		switch(seq){
		case 0:
			continue;
		case 1:
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 2);
			break;
		case 2:
		default:
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 0);
			break;
		}
	}
#endif
#if 1
	for (i = CB_ENUM_BHIT_CON; i < CB_ENUM_BTN_NUM; i++){
		
		seq = CATS_ObjectAnimeFrameGetCap(cbmw->button_obj.cap[i]);
		
		switch(seq){
		case 0:
			continue;
		case 1:
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 2);
			break;
		case 2:
		default:
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 0);
			break;
		}
	}
#endif
}

void CB_Tool_ButtonCallBack( u32 button, u32 event, void* work )
{
	CB_MAIN_WORK* cbmw = (CB_MAIN_WORK*)work;
	
	if (cbmw->sys.main_tp_active == FALSE){	return;	}
	
	switch(button){
	case CB_ENUM_BHIT_UP:
		///< ページ↑切り替え
		if (event == BMN_EVENT_TOUCH){
			if (cbmw->page.no > 0){
				cbmw->page.no--;
			}
			else {
				cbmw->page.no = cbmw->page.max - 1;
			}
			
			PageData_Del(cbmw);
			PageData_Create(cbmw, cbmw->page.no);
			PageData_ResourceLoad(cbmw);
			PageData_Add(cbmw);
			CB_BMP_SealNumWinPrint(cbmw);
			
			Snd_SePlay( CB_SE_UP );
		}
		CB_Tool_ButtonAnime(cbmw->button_obj.cap[CB_ENUM_BHIT_UP], event);
		break;
		
	case CB_ENUM_BHIT_DOWN:
		///< ページ↓切り替え
		if (event == BMN_EVENT_TOUCH){
			cbmw->page.no++;
			cbmw->page.no %= cbmw->page.max;
			
			PageData_Del(cbmw);
			PageData_Create(cbmw, cbmw->page.no);
			PageData_ResourceLoad(cbmw);
			PageData_Add(cbmw);
			CB_BMP_SealNumWinPrint(cbmw);
			
			Snd_SePlay( CB_SE_DOWN );
		}
		CB_Tool_ButtonAnime(cbmw->button_obj.cap[CB_ENUM_BHIT_DOWN], event);
		break;
		
	case CB_ENUM_BHIT_CON:
		///< 確認ボタン
		if (event == BMN_EVENT_TOUCH){
			if (cbmw->seq != CBS_CUSTOM_CON){
				cbmw->seq = CBS_CUSTOM_CON;
				
				Snd_SePlay( CB_SE_PLAY );
			}
			BA_Init(cbmw->button_obj.cap[CB_ENUM_BHIT_CON], NULL);
		}
		CB_Tool_ButtonAnime(cbmw->button_obj.cap[CB_ENUM_BHIT_CON], event);
		break;
		
	case CB_ENUM_BHIT_DEC:
		///< 決定ボタン
		if (event == BMN_EVENT_TOUCH){
			if (cbmw->seq != CBS_CUSTOM_DEC){
				cbmw->seq = CBS_CUSTOM_DEC;
				
				CB_Sys_MainTPSet(cbmw, FALSE);				
				Snd_SePlay( CB_SE_DEC );
			}
			BA_Init(cbmw->button_obj.cap[CB_ENUM_BHIT_DEC], cbmw->sys.font_obj[0]);
		}
		CB_Tool_ButtonAnime(cbmw->button_obj.cap[CB_ENUM_BHIT_DEC], event);
		break;
		
	case CB_ENUM_BHIT_END:
		///< やめるボタン
		if (event == BMN_EVENT_TOUCH){
			if (cbmw->seq != CBS_CUSTOM_END){
				cbmw->seq = CBS_CUSTOM_END;
			
				CB_Sys_MainTPSet(cbmw, FALSE);
				Snd_SePlay( CB_SE_CAN );
			}
			BA_Init(cbmw->button_obj.cap[CB_ENUM_BHIT_END], cbmw->sys.font_obj[1]);
		}
		CB_Tool_ButtonAnime(cbmw->button_obj.cap[CB_ENUM_BHIT_END], event);
		break;
	
	case CB_ENUM_BHIT_SEAL_1:
	case CB_ENUM_BHIT_SEAL_2:
	case CB_ENUM_BHIT_SEAL_3:
	case CB_ENUM_BHIT_SEAL_4:
	case CB_ENUM_BHIT_SEAL_5:
	case CB_ENUM_BHIT_SEAL_6:
	case CB_ENUM_BHIT_SEAL_7:
	case CB_ENUM_BHIT_SEAL_8:
		///< シールポップボタン
		{
			int name_id;
			if (event == BMN_EVENT_TOUCH){
				
				if (CBS_IsPop(cbmw) == FALSE){
					///< もう空きが無い
				
					Snd_SePlay( CB_SE_LIMIT );
					
					CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_NG);
				}
				else {
					if (cbmw->page.item[button] != 0
					&&	CB_SaveData_ItemNumGet_CBO(cbmw->cb_item_data, cbmw->page.item[button] - 1) != 0){
						
						cbmw->sys.hold = CBS_SearchPop(cbmw, button);
										
						name_id = Seal_NameGet(cbmw->page.item[button]);
						
						CB_BMP_SealNameSet(&cbmw->sys.win[0], name_id);
						
						CB_SaveData_ItemNumAddCheck(cbmw->cb_pw->save_data, cbmw->page.item[button], -1);
						CB_BMP_SealNumWinPrint_No(cbmw, button);
					
						Snd_SePlay( CB_SE_POP );					
					}
					else {						
						if (cbmw->page.item[button] != 0){
							Snd_SePlay( CB_SE_LIMIT );
							CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_ZERO);
						}
					}
				}
			}
		}
		break;
		
	case CB_BHIT_SEAL_0:
	case CB_BHIT_SEAL_1:
	case CB_BHIT_SEAL_2:
	case CB_BHIT_SEAL_3:
	case CB_BHIT_SEAL_4:
	case CB_BHIT_SEAL_5:
	case CB_BHIT_SEAL_6:
	case CB_BHIT_SEAL_7:
		///< ドロップシール
		{
			int id;
			int name_id;
			
			if (event == BMN_EVENT_TOUCH){

				id = button - CB_BHIT_SEAL_0;

				CBS_SealHold(cbmw, event, id);
				OS_Printf("id 1= %2d\n", id);
				
				name_id = Seal_NameGet(cbmw->seal[id].id);
				OS_Printf("id 2= %2d\n", cbmw->seal[id].id);

				CB_BMP_SealNameSet(&cbmw->sys.win[0], name_id);

				Snd_SePlay( CB_SE_POP );					
			}
		}
		break;
		
	default:
		GF_ASSERT(0);
		break;
	}
}

///< 
BOOL CB_Sys_IsSubTCB(CB_MAIN_WORK* cbmw)
{
	return cbmw->sys.sub_tcb_active;
}

///< 
void CB_Sys_MainTPSet(CB_MAIN_WORK* cbmw, BOOL active)
{
	cbmw->sys.main_tp_active = active;
}

///< 動かないボタンの当たり判定
#ifdef SEAL_SBS
	///< 横並び
	static const RECT_HIT_TBL hit_tbl[] = {
		{ 16, 16 + 16,   8,   8 + 16	},	///< seal		
		{ 16, 16 + 16,  64,  64 + 16	},	///< seal
		{ 40, 40 + 16,   8,   8 + 16	},
		{ 40, 40 + 16,  64,  64 + 16	},
		{ 64, 64 + 16,   8,   8 + 16	},
		{ 64, 64 + 16,  64,  64 + 16	},
		{ 88, 88 + 16,   8,   8 + 16	},
		{ 88, 88 + 16,  64,  64 + 16	},
		
		{104,104 + 24,  8,   8 + 40	},	///< ↑
		{104,104 + 24, 56,  56 + 40	},	///< ↓
		{168,188,  18,  77	},			///< L
		{168,188,  97,  156	},			///< C
		{168,188, 178,  237	},			///< R
	};
#else
	static const RECT_HIT_TBL hit_tbl[] = {
		{ 16, 16 + 16,   8,   8 + 16	},	///< seal
		{ 40, 40 + 16,   8,   8 + 16	},
		{ 64, 64 + 16,   8,   8 + 16	},
		{ 88, 88 + 16,   8,   8 + 16	},
		
		{ 16, 16 + 16,  64,  64 + 16	},	///< seal
		{ 40, 40 + 16,  64,  64 + 16	},
		{ 64, 64 + 16,  64,  64 + 16	},
		{ 88, 88 + 16,  64,  64 + 16	},
		
		{104,104 + 24,  8,   8 + 40	},	///< ↑
		{104,104 + 24, 56,  56 + 40	},	///< ↓
		{168,188,  18,  77	},			///< L
		{168,188,  97,  156	},			///< C
		{168,188, 178,  237	},			///< R
	};
#endif

/// アタリ判定初期化
void CB_Tool_ButtonInit(CB_MAIN_WORK* cbmw)
{
	int i;
	const RECT_HIT_TBL hit_tbl_dmy = { 0, 0, 0, 0 };
	
	for (i = 0; i < CB_ENUM_BTN_NUM; i++){
		cbmw->sys.hit_tbl[i] = hit_tbl[i];
	}
	for ( ; i < CB_BHIT_SEAL_MAX; i++){
		cbmw->sys.hit_tbl[i] = hit_tbl_dmy;
		cbmw->seal[i - CB_BHIT_SEAL_0].hit = &cbmw->sys.hit_tbl[i];
	}
	
	cbmw->sys.btn = BMN_Create(cbmw->sys.hit_tbl, CB_DEF_HIT_TBL_MAX,
							   CB_Tool_ButtonCallBack, cbmw, HEAPID_CUSTOM_BALL);
}
void CB_Test_PokemonSSP_Add(CB_MAIN_WORK* cbmw)
{
#if 0
	SOFT_SPRITE_ARC ssa;

	int height;
	
	PokeGraArcDataGetPP(&ssa, cbmw->test_pp, PARA_FRONT);
	
	height	= PokeParaHeightGet(cbmw->test_pp, PARA_FRONT);
	
	cbmw->sys.height = height;
	
	cbmw->sys.ssp = SoftSpriteAdd(cbmw->sys.ssm_p, &ssa,
							   APPEAR_X_TYPE_BB,
							   APPEAR_Y_TYPE_BB + height,
							   APPEAR_Z_TYPE_BB,
							   0, NULL, NULL);
#else

	SOFT_SPRITE_ARC ssa;
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];
	
	int monsno;
	int height;
	
	PokeGraArcDataGetPP(&ssa, cbmw->test_pp, PARA_FRONT);

	monsno  = PokeParaGet(cbmw->test_pp, ID_PARA_monsno, NULL);
	height	= PokeParaHeightGet(cbmw->test_pp, PARA_FRONT);
	
	cbmw->sys.height = height;

	PokeAnmDataSet(&ssanm[0], monsno);
	
	cbmw->sys.ssp = SoftSpriteAdd(cbmw->sys.ssm_p, &ssa,
							   APPEAR_X_TYPE_BB,
							   APPEAR_Y_TYPE_BB + height,
							   APPEAR_Z_TYPE_BB,
							   0, &ssanm[0], NULL);
#endif
}

static void CB_Test_PokemonSSP_AnimeInit(CB_MAIN_WORK* cbmw)
{
	int monsno;
	int chr;
	
	monsno = PokeParaGet(cbmw->test_pp, ID_PARA_monsno, NULL);
	chr	   = PokeSeikakuGet(cbmw->test_pp);
	
	SoftSpriteAnimeSet(cbmw->sys.ssp, 1);
	PokePrgAnmDataSet(cbmw->sys.pas,
					  cbmw->sys.ssp, monsno, PARA_FRONT, chr, PARA_HFLIP_OFF, 0);
}

static void CB_Test_PokemonSSP_AppearInit(CB_MAIN_WORK* cbmw)
{
	SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_X, AFF_APPEAR_X_S);
	SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_Y, AFF_APPEAR_Y_S);	
}

#define	AFF_SPEED		(0x20)
static BOOL CB_Test_PokemonSSP_AppearMain(CB_MAIN_WORK* cbmw)
{
	if(SoftSpriteParaGet(cbmw->sys.ssp, SS_PARA_AFF_X) == AFF_APPEAR_X_B){
		return FALSE;
	}
	else if(SoftSpriteParaGet(cbmw->sys.ssp, SS_PARA_AFF_X) >= AFF_APPEAR_X_B){
		SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_X, AFF_APPEAR_X_B);
		SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_Y, AFF_APPEAR_Y_B);
		return FALSE;
	}
	else {
		SoftSpriteParaCalc(cbmw->sys.ssp, SS_PARA_AFF_X, AFF_SPEED);
		SoftSpriteParaCalc(cbmw->sys.ssp, SS_PARA_AFF_Y, AFF_SPEED);
		SoftSpriteOYCalc(cbmw->sys.ssp, cbmw->sys.height);
	}
	return TRUE;
}

static BOOL CB_Test_PokemonSSP_ReturnMain(CB_MAIN_WORK* cbmw)
{
	if(SoftSpriteParaGet(cbmw->sys.ssp, SS_PARA_AFF_X) == AFF_APPEAR_X_S){
		return FALSE;
	}
	else if(SoftSpriteParaGet(cbmw->sys.ssp, SS_PARA_AFF_X) <= AFF_APPEAR_X_S){
		SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_X, AFF_APPEAR_X_S);
		SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_AFF_Y, AFF_APPEAR_Y_S);
		return FALSE;
	}
	else {
		SoftSpriteParaCalc(cbmw->sys.ssp, SS_PARA_AFF_X, -AFF_SPEED);
		SoftSpriteParaCalc(cbmw->sys.ssp, SS_PARA_AFF_Y, -AFF_SPEED);
		SoftSpriteOYCalc(cbmw->sys.ssp, cbmw->sys.height);
	}
	return TRUE;
}

void CB_Test_PokemonSSP_Vanish(CB_MAIN_WORK* cbmw, int flag)
{
	SoftSpriteParaSet(cbmw->sys.ssp, SS_PARA_VANISH, flag);
}

void CB_Test_PokemonSSP_Del(CB_MAIN_WORK* cbmw)
{
	SoftSpriteDel(cbmw->sys.ssp);
}

static BOOL CB_Sub_Edit(CB_MAIN_WORK* cbmw)
{
	switch(cbmw->seq){
	case CBS_CUSTOM_INIT:
		///< 初期化
		CB_Sys_MainTPSet(cbmw, FALSE);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CLEAR);
		CB_BMP_SealNumWinAdd(cbmw);
		CB_BMP_SealNumWinPrint(cbmw);
		CB_View_Scroll(cbmw, +1, 4);
		
		BackupEditData_Make(cbmw);
		BackupItemData_Make(cbmw);
		
		cbmw->sys.bEdit = FALSE;
		
		cbmw->seq++;
		break;
		
	case CBS_CUSTOM_T_FADE_OUT:
		///< 上画面一部＋OBJフェード
		if (CB_Sys_IsSubTCB(cbmw) == TRUE){ break; }
		
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_BG,  (1 << CB_DEF_MAIN_BG_PAL)|(1 << CB_DEF_MAIN_BG2_PAL), 0,  0, 16, 0);
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF, 0,  0, 16, 0);
		
		///< 優先度変更
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
		GF_Disp_GXS_VisibleControl(CB_PLANE_LIST, VISIBLE_ON);
		GF_BGL_PrioritySet(CB_DEF_EDIT_SUB_BG_FRM, CB_BG_PRI_SCR_EDIT_TOP);
		CB_Tool_BTN_Enable(cbmw, CATS_ENABLE_TRUE);
		Piko_Enable(cbmw, CATS_ENABLE_TRUE);
		FontOam_Enable(cbmw, TRUE);
		cbmw->seq++;
		break;
		
	case CBS_CUSTOM_T_FADE_OUT_WAIT:
		///< フェード待ち
		if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
		GF_BGL_PrioritySet(CB_DEF_FIELD_BG_FRM, CB_BG_PRI_SCR_FIELD_TOP);
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_BG,  (1 << CB_DEF_MAIN_BG2_PAL), 0,  16, 0, 0);
		cbmw->seq++;
		break;	
	
	case CBS_CUSTOM_T_FIELD_FADE_OUT_WAIT:
		if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
		CB_Sys_MainTPSet(cbmw, TRUE);
		cbmw->seq++;
		break;
	
	case CBS_CUSTOM_MAIN:
		///< メイン
		break;
		
	case CBS_CUSTOM_CON:
		///< パーティクル確認
		{
			switch(cbmw->sub_seq){
			case 0:
				GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_BG,
							   (1 << CB_ENUM_PAL_BALL_BG) |
							   (1 << CB_ENUM_PAL_EDIT_BG) |
							   (1 << CB_ENUM_PAL_LIST_BG) |
							   (1 << CB_ENUM_PAL_NUM), 0, 0, CB_DEF_FADE_GRAY, 0);
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_OBJ, 0xFFFF, 0,  0, CB_DEF_FADE_GRAY, 0);
				CB_Sys_MainTPSet(cbmw, FALSE);
				cbmw->sub_work = 0;				
				CB_Tool_TestPokemonCreate(cbmw);
				CB_Test_PokemonSSP_Add(cbmw);
				CB_Test_PokemonSSP_Vanish(cbmw, 1);
				CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CON);
				cbmw->sub_seq++;
				break;
			
			case 1:
				///< ボールなげる
				if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
				
				{
					TBALL_MOVE_DATA bmd;

					bmd.type	= EBMT_STAY_BB;
					bmd.heap_id	= HEAPID_CUSTOM_BALL;
					bmd.mode	= EBMM_THROW;
					bmd.id		= BM_SUITABLE_ID;
					bmd.bg_pri	= BM_BG_PRI_CUSTOM;
					bmd.surface = 1;
					bmd.csp		= cbmw->sys.csp;
					bmd.pfd		= cbmw->sys.pfd;
					bmd.ball_id = PokeParaGet(cbmw->test_pp, ID_PARA_get_ball, NULL);

					cbmw->sys.bms	= BM_Init(&bmd);
					cbmw->sub_seq++;
				}
				break;
			case 2:
				///<
				{
					int		test_id;
					CB_CORE	test_core;
					TBALL_CUSTOM_PARAM bcp = { 0 };
					
					bcp.client_type = CLIENT_TYPE_BB;	
					bcp.pp			= cbmw->test_pp;
					
					test_id = cbmw->select[0] + 1;
					CBS_TestCoreData_Create(&test_core, cbmw);
					
					PokeParaPut(cbmw->test_pp, ID_PARA_cb_id,	(u8*)&test_id);
					PokeParaPut(cbmw->test_pp, ID_PARA_cb_core,	&test_core);
					
					cbmw->sys.bes	= BallEffect_Init(HEAPID_CUSTOM_BALL, &bcp);
					
					BallEffect_ResourceLoad(cbmw->sys.bes);
				}
				cbmw->sub_seq++;
				cbmw->sub_work = 0;
				break;
				
			case 3:
				
				if (BallEffect_IsLoadEnd(cbmw->sys.bes) != TRUE){
					break;
				}
			
				if (BM_IsOpen(cbmw->sys.bms) == TRUE){
					
					CB_Test_PokemonSSP_AppearMain(cbmw);
			
					BallEffect_ExecutedEz(cbmw->sys.bes);
					
					CB_Test_PokemonSSP_Vanish(cbmw, 0);
					CB_Test_PokemonSSP_AppearInit(cbmw);
					
					Snd_SePlay( CB_SE_BOMB );
				
					cbmw->sub_seq++;
				}
			
				break;
			
			case 4:
				{
					BOOL ret = CB_Test_PokemonSSP_AppearMain(cbmw);
					
					if (BM_EndCheck(cbmw->sys.bms) != FALSE){ break; }
					
					if (ret == FALSE){
														
						BM_Delete(cbmw->sys.bms);
						GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
						
						CB_Test_PokemonSSP_AnimeInit(cbmw);
						cbmw->sub_work = 0;
						cbmw->sub_seq++;
					#if 0	
						{
							int monsno = PokeParaGet(cbmw->test_pp, ID_PARA_monsno,	NULL);
							
							Snd_PMVoicePlayEx( PV_NORMAL, monsno, WAZA_SE_PAN_R, PV_VOL_MAX, HEAPID_CUSTOM_BALL );
						}
					#endif
					}
				}
				break;
			case 5:
				if (BallEffect_EndCheck(cbmw->sys.bes) != FALSE){ break; }
				if (PokeAnm_IsFinished(cbmw->sys.pas, 0) != TRUE){ break; }
				if (SoftSpriteAnimeEndCheck(cbmw->sys.ssp) != FALSE){ break; }
			#if 0
				if (Snd_PMVoicePlayCheck() != 0){
					Snd_PMVoiceStop(0);
					break;
				}
			#endif
				BallEffect_FreeMemory(cbmw->sys.bes);
				cbmw->sub_seq++;
				break;
				
			case 6:
				if ((++cbmw->sub_work) < CB_DEF_POKE_RETURN_WAIT){ break; }
				cbmw->sub_work = 0;
				{
					TBALL_MOVE_DATA bmd;

					bmd.type	= EBMT_STAY_BB;
					bmd.heap_id	= HEAPID_CUSTOM_BALL;
					bmd.mode	= EBMM_CLOSE;
					bmd.id		= BM_SUITABLE_ID;
					bmd.bg_pri	= BM_BG_PRI_CUSTOM;
					bmd.surface = 1;
					bmd.csp		= cbmw->sys.csp;
					bmd.pfd		= cbmw->sys.pfd;
					bmd.ball_id = PokeParaGet(cbmw->test_pp, ID_PARA_get_ball, NULL);

					cbmw->sys.bms	= BM_Init(&bmd);
					
					CB_Tool_DefaultBlendSet();
					GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
					
					cbmw->sub_seq++;
				}
				break;		 	
			
			case 7:
				{
					BOOL ret = CB_Test_PokemonSSP_ReturnMain(cbmw);
					
					if (BM_EndCheck(cbmw->sys.bms) == FALSE && ret == FALSE){								
						PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_BG,
									   (1 << CB_ENUM_PAL_BALL_BG) |
									   (1 << CB_ENUM_PAL_EDIT_BG) |
									   (1 << CB_ENUM_PAL_LIST_BG) |
									   (1 << CB_ENUM_PAL_NUM), 0,  CB_DEF_FADE_GRAY, 0, 0);
						PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_OBJ, 0xFFFF, 0,  CB_DEF_FADE_GRAY, 0, 0);
						CB_Test_PokemonSSP_Vanish(cbmw, 1);
						CB_Test_PokemonSSP_Del(cbmw);
						BM_Delete(cbmw->sys.bms);
						cbmw->sub_seq++;
					}
				}
				break;
			
			default:
				if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
				GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
				CB_Sys_MainTPSet(cbmw, TRUE);
				cbmw->sub_seq = 0;
				cbmw->seq = CBS_CUSTOM_MAIN;
				CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CLEAR);
				break;
			}
		}
		break;
		
	case CBS_CUSTOM_DEC:
		///< 決定
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_EDIT_END);
		///< ソート		
//		CBS_SVSort(cbmw);
		if (CBS_CheckEditData(cbmw) == TRUE){
			cbmw->sys.bEdit = TRUE;
		}
		CBS_EditData_Save(cbmw);
//		SubSelect_ObjRefrect(cbmw);
		SubSelect_ObjRefrect(cbmw);
		
//		CBS_Delete(cbmw);
//		CBS_LoadInit(cbmw);
		{
			///< カウントアップ処理
			RECORD* rec;
			
			rec = SaveData_GetRecord(cbmw->cb_pw->save);
			
			RECORD_Score_Add(rec, SCORE_ID_CUSTOM_CAPSULE);
		}
		{
		
			POKEMON_PARAM* pp;
	
			///< 上書き
			if (cbmw->mo[ cbmw->select[ 0 ] ].poke_idx != CB_DEF_POKE_NOT_INDEX){

				pp = cbmw->cb_pw->poke_para[ cbmw->mo[ cbmw->select[ 0 ] ].poke_idx ];
				
				PokeParaPut(pp,
							ID_PARA_cb_core,
							CB_SaveData_CoreDataGet(cbmw->cb_pw->save_data, cbmw->select[ 0 ]));	
				
			}
		}
		cbmw->seq = CBS_CUSTOM_T_FADE_IN;
		break;
		
	case CBS_CUSTOM_END:
		///< やめる
		{
			switch(cbmw->sub_seq){
			case 0:
				///< 薄暗く
				if (CBS_CheckEditData(cbmw) == FALSE){
					cbmw->seq = CBS_CUSTOM_T_FADE_IN;
					break;
				}
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_BG,
							   (1 << CB_ENUM_PAL_BALL_BG) |
							   (1 << CB_ENUM_PAL_EDIT_BG) |
							   (1 << CB_ENUM_PAL_LIST_BG) |
							   (1 << CB_ENUM_PAL_NUM), 0, 0, CB_DEF_FADE_GRAY, 0);
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_OBJ, 0xFFFF, 0,  0, CB_DEF_FADE_GRAY, 0);
				CB_Sys_MainTPSet(cbmw, FALSE);
				GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);
				cbmw->sub_seq++;
				break;
			
			case 1:				
				///< チェック
				if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
			//	CB_Tool_ButtonAutoUpdate(cbmw);								
				PaletteTrans_AutoSet(cbmw->sys.pfd, FALSE);
				CB_BMP_WindowAdd(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_MAIN ], CB_DEF_STRING_SUB_BG_FRM,
								 CB_DEF_WIN_B_MAIN_X,  CB_DEF_WIN_B_MAIN_Y,
								 CB_DEF_WIN_B_MAIN_SX, CB_DEF_WIN_B_MAIN_SY, CB_DEF_WIN_CHAR_OFS);
				{
					TOUCH_SW_PARAM tsp;
					
					tsp.p_bgl	  = cbmw->sys.bgl;
					tsp.bg_frame  = CB_DEF_STRING_SUB_BG_FRM;
					tsp.char_offs = CB_DEF_TPBG_CHAR_OFS;
					tsp.pltt_offs = CB_ENUM_PAL_SWITCH;
					tsp.x		  = CB_DEF_SW_X;
					tsp.y		  = CB_DEF_SW_Y;

					cbmw->sys.tss = TOUCH_SW_AllocWork(HEAPID_CUSTOM_BALL);
					
					TOUCH_SW_Init(cbmw->sys.tss, &tsp);
				}
				CB_BMP_InfoMessageSet(&cbmw->sys.win[CB_ENUM_WIN_B_MAIN], CB_MSG_ID_END_QUE);
				cbmw->sub_seq++;
				break;
				
			case 2:
				GF_Disp_GXS_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON);
				cbmw->sub_seq++;
								
			case 3:
				{
					u32 ret;
					
					ret = TOUCH_SW_Main(cbmw->sys.tss);
					
					switch(ret){
					case TOUCH_SW_RET_YES:
					case TOUCH_SW_RET_NO:
						cbmw->sub_work = ret;
						PaletteTrans_AutoSet(cbmw->sys.pfd, TRUE);
						TOUCH_SW_Reset(cbmw->sys.tss);
						TOUCH_SW_FreeWork(cbmw->sys.tss);
						BmpTalkWinClear(&cbmw->sys.win[ CB_ENUM_WIN_B_MAIN ], WINDOW_TRANS_OFF);
						GF_BGL_BmpWinOff(&cbmw->sys.win[ CB_ENUM_WIN_B_MAIN ]);
						GF_BGL_BmpWinDel(&cbmw->sys.win[ CB_ENUM_WIN_B_MAIN ]);
						cbmw->sub_seq++;
						break;
					
					case TOUCH_SW_RET_NORMAL:
					default:
						break;
					}
				}
				break;
			
			case 4:
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_BG,
							   (1 << CB_ENUM_PAL_BALL_BG) |
							   (1 << CB_ENUM_PAL_EDIT_BG) |
							   (1 << CB_ENUM_PAL_LIST_BG) |
							   (1 << CB_ENUM_PAL_NUM), 0,  CB_DEF_FADE_GRAY, 0, 0);
				PaletteFadeReq(cbmw->sys.pfd, PF_BIT_SUB_OBJ, 0xFFFF, 0,  CB_DEF_FADE_GRAY, 0, 0);
				cbmw->sub_seq++;
				break;
			
			case 5:
				if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
				switch(cbmw->sub_work){
				case TOUCH_SW_RET_YES:
					BackupEditData_Recover(cbmw);
					BackupItemData_Recover(cbmw);
					CB_BMP_SealNumWinPrint(cbmw);
					CBS_Delete(cbmw);
					CBS_LoadInit(cbmw);
					CBS_Enable(cbmw, CATS_ENABLE_TRUE);				
					cbmw->seq = CBS_CUSTOM_DEC;
					break;
					
				case TOUCH_SW_RET_NO:
					cbmw->seq = CBS_CUSTOM_MAIN;
					break;
					
				case TOUCH_SW_RET_NORMAL:
				default:
					break;
				}
				CB_Sys_MainTPSet(cbmw, TRUE);
				cbmw->sub_seq = 0;
			}
		}
		break;

	case CBS_CUSTOM_T_FADE_IN:
		///< バトル背景フェード
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_BG,  (1 << CB_DEF_MAIN_BG2_PAL), 0, 0, 16, 0);
	//	CB_Tool_ButtonAutoUpdate(cbmw);
		cbmw->seq++;
		break;
	
	case CBS_CUSTOM_T_FADE_IN_2:
		///< 上画面一部＋OBJフェード
		if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_BG,  (1 << CB_DEF_MAIN_BG_PAL), 0,  16, 0, 0);
		PaletteFadeReq(cbmw->sys.pfd, PF_BIT_MAIN_OBJ, 0xFFFF, 0,  16, 0, 0);
		
		GF_BGL_PrioritySet(CB_DEF_FIELD_BG_FRM, CB_BG_PRI_SCR_FIELD);
		GF_BGL_PrioritySet(CB_DEF_EDIT_SUB_BG_FRM, CB_BG_PRI_SCR_EDIT);
		GF_Disp_GXS_VisibleControl(CB_PLANE_LIST, VISIBLE_OFF);
		CB_Tool_BTN_Enable(cbmw, CATS_ENABLE_FALSE);
		Piko_Enable(cbmw, CATS_ENABLE_FALSE);
		FontOam_Enable(cbmw, FALSE);
		
		CB_View_Scroll(cbmw, -1, 4);
		CB_Sys_MainTPSet(cbmw, FALSE);
		cbmw->seq++;
		break;
		
	case CBS_CUSTOM_T_FADE_IN_WAIT:
		///< フェード待ち
		if (PaletteFadeCheck(cbmw->sys.pfd) != 0){ break; }
		if (CB_Sys_IsSubTCB(cbmw) == TRUE){ break; }
		CATS_ObjectEnableCap(cbmw->cap_cur[1], CATS_ENABLE_FALSE);
		CB_Sub_SeqChange(cbmw, CB_MODE_SELECT, CB_DEF_KEEP_SEQ_SET, 0);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
		CB_BMP_SealNumWinDel(cbmw);
		
		return TRUE;
	};
	
	///< タッチパネル
	if (cbmw->sys.hold == CB_DEF_NOT_HOLD){
		BMN_Main(cbmw->sys.btn);
	}
	else {
		u32 x, y;
		int id;
		BOOL bHit;
		
		id = cbmw->sys.hold;
		
		bHit = GF_TP_GetPointCont(&x, &y);
		
		if (bHit){
			int name_id;
			name_id = Seal_NameGet(cbmw->seal[id].id);
			CB_BMP_SealNameSet(&cbmw->sys.win[0], name_id);
			CATS_ObjectPosSetCap(cbmw->seal[id].cap, x, y);
			CBS_ReleasePointCheckTypeSet(cbmw, id);
			CBS_EditDataRefrect(cbmw, id);
		}
		else {
			BOOL release;
			
			release = CBS_ReleasePointCheck(cbmw, id);
			HitTable_CreateCap(cbmw->seal[id].hit, cbmw->seal[id].cap, FALSE);
			
			if (release == FALSE){
				CB_SaveData_ItemNumAddCheck_CBO(cbmw->cb_pw->save_data, cbmw->seal[id].id, +1);
				CB_BMP_SealNumWinPrint(cbmw);
				CBS_Release(cbmw, id);
			}
				
			Snd_SePlay( CB_SE_DROP );
			cbmw->sys.hold = CB_DEF_NOT_HOLD;
			CB_BMP_SealNameSet(&cbmw->sys.win[0], CB_MSG_ID_CLEAR);
			
		//	CBS_SVSort(cbmw);
		//	CBS_Pri_HitTbl_Sort(cbmw);
		}
	}
	
//	CB_Tool_ButtonAutoUpdate(cbmw);

	CB_Tool_BTN_Update(cbmw);
	Piko_Update(cbmw);
	CB_Tool_PokeIcon_Update(cbmw);
	SubSelect_ObjUpdate(cbmw);
	
	return TRUE;
}

static BOOL CB_Sub_SettingSet(CB_MAIN_WORK* cbmw)
{
	switch(cbmw->seq){
	case CBS_SET_INIT:
	//	CB_MENU_Cancel(cbmw);
		cbmw->seq++;
		
	case CBS_SET_WIPE_OUT:
		CB_WipeFadeOut();
		cbmw->seq++;
		break;
	
	case CBS_SET_WIPE_OUT_WAIT:
		if (WIPE_SYS_EndCheck() != TRUE){ break; }
		GF_BGL_BmpWinDel(&cbmw->sys.win[ 0 ]);
		SubSelect_ObjDelete(cbmw);	
		CB_Tool_PokeIcon_Del(cbmw);
		CB_Tool_BTN_Delete(cbmw);
		Piko_Delete(cbmw);
		PageData_Del(cbmw);					///< OBJ登録
		CBProc_NextModeSet(cbmw->cb_pw, CB_PROC_NEXT_MODE_LIST);

		return FALSE;
	}
	
	CB_Tool_PokeIcon_Update(cbmw);
	SubSelect_ObjUpdate(cbmw);
	
	return TRUE;
}

void CB_Tool_CoreDataRemove(CB_MAIN_WORK* cbmw, int this)
{
	int poke_idx;
	int poke_this;
	int none_data = 0;
	CB_CORE temp;
	
	///< ポケパラ操作
	poke_this = cbmw->cb_edit_data[ this ].poke_idx;
	if (poke_this != CB_DEF_POKE_NOT_INDEX){
		PokeParaPut(cbmw->cb_pw->poke_para[ poke_this ], ID_PARA_cb_id, (u8*)&none_data);
	}
	cbmw->cb_edit_data[ this ].poke_idx = CB_DEF_POKE_NOT_INDEX;

	SubSelect_ObjRefrect(cbmw);
}

static BOOL CB_Sub_SettingRemove(CB_MAIN_WORK* cbmw)
{
	switch(cbmw->seq){
	case CBS_REM_INIT:
		CB_Tool_CoreDataRemove(cbmw, cbmw->select[0]);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_REM);
	//	CB_MENU_Cancel(cbmw);
		cbmw->seq++;
		break;

	case CBS_REM_MAIN:
		if (sys.trg & CB_DEF_MSG_END_KEY){
			cbmw->seq++;
		}
		break;

	case CBS_REM_END:
		CB_Sub_SeqChange(cbmw, CB_MODE_SELECT, CB_DEF_KEEP_SEQ_SET, 0);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
		break;
	}	
	
	CB_Tool_PokeIcon_Update(cbmw);
	SubSelect_ObjUpdate(cbmw);
	
	return TRUE;
}
	
static BOOL CB_Sub_Change(CB_MAIN_WORK* cbmw)
{
	switch(cbmw->seq){
	case CBS_CHANGE_INIT:
		CATS_ObjectPriSetCap(cbmw->cap_cur[0], CB_ENUM_OAM_PRI_CUR_2);
		CATS_ObjectPriSetCap(cbmw->cap_cur[1], CB_ENUM_OAM_PRI_CUR_1);
		CATS_ObjectAnimeSeqSetCap(cbmw->cap_cur[0], 1);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_REP);
		CATS_ObjectEnableCap(cbmw->cap_cur[1], CATS_ENABLE_TRUE);
	//	CB_MENU_Cancel(cbmw);
		cbmw->seq++;
	
	case CBS_CHANGE_MAIN:
		{
			BOOL is_input;
			
//			is_input = CB_Tool_CursorMoveEx(&(cbmw->select[1]), cbmw->select[0]);
			is_input = CB_Tool_CursorMove(&(cbmw->select[1]));

			if (is_input == TRUE){
				CB_Tool_CursorMovePosUpdate(cbmw, 1, FALSE);
				
				Snd_SePlay( CB_SE_CURSOR );
			}
			else if (sys.trg & PAD_BUTTON_A){
				CB_Tool_CoreDataChange(cbmw, cbmw->select[0], cbmw->select[1]);
				CB_Tool_CursorMovePosUpdate(cbmw, 1, TRUE);
				CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_REP_END);
				cbmw->seq = CBS_CHANGE_KEY_WAIT;
				
				Snd_SePlay( CB_SE_DEC_S );
			}
			else if (sys.trg & PAD_BUTTON_B){
				CATS_ObjectEnableCap(cbmw->cap_cur[1], CATS_ENABLE_FALSE);
				CB_Tool_CursorMovePosUpdate(cbmw, 0, TRUE);
				cbmw->seq = CBS_CHANGE_END;
				
				Snd_SePlay( SEQ_SE_DP_DECIDE );
			}
		}
		break;
	case CBS_CHANGE_KEY_WAIT:
		if (sys.trg & CB_DEF_MSG_END_KEY){
			cbmw->seq = CBS_CHANGE_END;
		}
		break;
		
	case CBS_CHANGE_END:
		CATS_ObjectPriSetCap(cbmw->cap_cur[0], CB_ENUM_OAM_PRI_CUR_1);
		CATS_ObjectPriSetCap(cbmw->cap_cur[1], CB_ENUM_OAM_PRI_CUR_2);
		CB_Sub_SeqChange(cbmw, CB_MODE_SELECT, CB_DEF_KEEP_SEQ_SET, 0);
		CATS_ObjectAnimeSeqSetCap(cbmw->cap_cur[0], 0);
		CB_BMP_InfoMessageSet(&cbmw->sys.win[0], CB_MSG_ID_CB_SEL);
		break;
	}
	
	CB_Tool_PokeIcon_Update(cbmw);
	SubSelect_ObjUpdate(cbmw);
	
	return TRUE;
}

static BOOL CB_Sub_End(CB_MAIN_WORK* cbmw)
{
	return FALSE;
}

/*

	メインシステム

 */

//--------------------------------------------------------------
/**
 * @brief	基本的なシステム初期化
 *
 * @param	heap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_SystemInit(int heap)
{
	sys_VBlankFuncChange(NULL, NULL);	///< VBlankセット
	sys_HBlankIntrStop();				///< HBlank割り込み停止

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);
	
//	simple_3DBGInit(heap);				///< 簡易3D初期化
	
}


//--------------------------------------------------------------
/**
 * @brief	基本的なシステム破棄
 *
 * @param	heap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_SystemDelete(int heap)
{
//	simple_3DBGExit();

	sys_VBlankFuncChange( NULL, NULL );	///< VBlankセット
	sys_HBlankIntrStop();				///< HBlank割り込み停止
}


//--------------------------------------------------------------
/**
 * @brief	Vram設定
 *
 * @param	bgl	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_Battle_VramBankSet(GF_BGL_INI *bgl)
{
	GF_Disp_GX_VisibleControlInit();
//	WIPE_ResetBrightness(WIPE_DISP_MAIN);
//	WIPE_ResetBrightness(WIPE_DISP_SUB);
	
	
	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_STRING, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_SELECT, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_FIELD, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON);
	}
	
	///< サブ画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			{	/// font
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_SUB_STRING, 0, 0, FALSE
			},
			{	/// boal
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_BALL, 0, 0, FALSE
			},
			{	/// list
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_LIST, 0, 0, FALSE
			},
			{	/// edit
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				CB_BG_PRI_SCR_EDIT, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S, &TextBgCntDat[0], GF_BGL_MODE_TEXT);
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_S, &TextBgCntDat[1], GF_BGL_MODE_TEXT);
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_S, &TextBgCntDat[2], GF_BGL_MODE_TEXT);
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_S, &TextBgCntDat[3], GF_BGL_MODE_TEXT);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME0_S);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_S);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_S);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_S);
		GF_Disp_GXS_VisibleControl(CB_PLANE_LIST, VISIBLE_OFF);
	}
}


void CB_Tool_VBlank(void* work)
{
	CB_MAIN_WORK* wk = work;

	SoftSpriteTextureTrans(wk->sys.ssm_p);

	DoVramTransferManager();			///< Vram転送マネージャー実行
	CATS_RenderOamTrans();
	PaletteFadeTrans(wk->sys.pfd);
	
	GF_BGL_VBlankFunc(wk->sys.bgl);
	
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}


