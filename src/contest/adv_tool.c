//==============================================================================
/**
 * @file	adv_tool.c
 * @brief	コンテスト全部門共通ツール
 * @author	matsuda
 * @date	2006.02.02(木)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "con_tool.h"
#include "actin.h"
#include "visual.h"
#include "dance.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/fontoam.h"

#include "adv_tool.h"
#include "contest_type.h"
#include "contest_snd_def.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "system/brightness.h"

#include "msgdata/msg.naix"

#include "contest/imc_acce_score.h"
#include "itemtool/itemsym.h"

#include <nitro/sinit.h>
#include "system/pm_overlay.h"
FS_EXTERN_OVERLAY(bc_common);
FS_EXTERN_OVERLAY(ol_imageclip);


//==============================================================================
//	定数定義
//==============================================================================
///装備アイテムによって発生するBPへの倍率効果：メインのコンテストタイプ(100だと等倍)
#define BP_ITEM_BAIRITU_MAIN		(110)
///装備アイテムによって発生するBPへの倍率効果：サブのコンテストタイプ(100だと等倍)
#define BP_ITEM_BAIRITU_SUB			(105)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void FlowerMoveTask(TCB_PTR tcb, void *work);
static void ContestSimpleSetUp(void);
static void ADV_FlashEffectMain(TCB_PTR tcb, void *work);


//==============================================================================
//	アクターヘッダ
//==============================================================================
///花柄模様アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S FlowerObjParam = {
	0, 0, 0,		//x, y, z
	0, 0, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		0,	//キャラ
		0,	//パレット
		0,	//セル
		0,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	3,			//BGプライオリティ
	0,			//Vram転送フラグ
};

//==============================================================================
//	データ
//==============================================================================
///花柄模様の座標とアニメシーケンス番号
static const struct{
	s16 x;				///<座標X
	s16 y;				///<座標Y
	s16 rotation;		///<回転速度
	u8 anm_seq;			///<初期アニメシーケンス
}FlowerPos[] = {
	{2 * 8 - 3, 0x15 * 8 + 4, -0x180, 1},
	{4 * 8 + 5, 0x15 * 8 - 4, 0x300, 1},
	{8 * 8, 0x16 * 8, -0x080, 0},
	{0x18 * 8, 0x16 * 8, 0x080, 0},
	{256-(4 * 8 + 5), 0x15 * 8 - 4, -0x300, 1},
	{256-(2 * 8 - 3), 0x15 * 8 + 4, 0x180, 1},
};



//--------------------------------------------------------------
/**
 * @brief   
 *
 * ProcDataで指定した以外のオーバーレイのロードを行う
 *
 */
//--------------------------------------------------------------
static void NitroStaticInit(void)
{
	Overlay_Load(FS_OVERLAY_ID(bc_common), OVERLAY_LOAD_NOT_SYNCHRONIZE);

	//イメージクリップオーバーレイ実行
	Overlay_Load(FS_OVERLAY_ID(ol_imageclip), OVERLAY_LOAD_NOT_SYNCHRONIZE);
}


//--------------------------------------------------------------
/**
 * @brief   コンテスト用3DBG初期化関数
 * 
 * @param   ヒープID
 */
//--------------------------------------------------------------
GF_G3DMAN * ADV_Contest_3D_Init(int heap_id)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(heap_id, GF_G3DMAN_LNK, GF_G3DTEX_256K, 
		GF_G3DMAN_LNK, GF_G3DPLT_32K, ContestSimpleSetUp);
	return g3Dman;
}

static void ContestSimpleSetUp(void)
{
	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// アルファテスト　　オフ
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト用3DBG終了処理
 *
 * @param   g3Dman		
 */
//--------------------------------------------------------------
void ADV_Contest_3D_Exit(GF_G3DMAN *g3Dman)
{
	GF_G3D_Exit(g3Dman);
}

//--------------------------------------------------------------
/**
 * @brief   メイン画面のフォントOAMを作成する
 *
 * @param   heap_id			ヒープID
 * @param   bgl				BGLへのポインタ
 * @param   crp				crpへのポインタ
 * @param   fontoam_sys		フォントシステムへのポインタ
 * @param   ret_fontoam		生成したフォントOAM代入先
 * @param   ret_cma			生成したフォントOAMのキャラ領域情報代入先
 * @param   str				文字列
 * @param   font_type		フォントタイプ(FONT_SYSTEM等)
 * @param   color			フォントカラー構成
 * @param   pal_offset		パレット番号オフセット
 * @param   pal_id			登録開始パレットID
 * @param   x				座標X
 * @param   y				座標Y
 * @param   pos_center  	FALSE(X左端座標) or TRUE(X中心座標)
 * @param   bg_pri			BGプライオリティ
 * @param   soft_pri		ソフトプライオリティ
 */
//--------------------------------------------------------------
void ADV_FontOamCreate(int heap_id, GF_BGL_INI *bgl, CATS_RES_PTR crp, 
	FONTOAM_SYS_PTR fontoam_sys, ADV_FONTACT *fontact, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, int bg_pri, int soft_pri)
{
	FONTOAM_INIT finit;
	GF_BGL_BMPWIN bmpwin;
	CHAR_MANAGER_ALLOCDATA cma;
	int vram_size;
	FONTOAM_OBJ_PTR fontoam;
	int font_len, char_len;
	int margin = 0;
	
	//文字列のドット幅から、使用するキャラ数を算出する
	{
		font_len = FontProc_GetPrintStrWidth(font_type, str, margin);
		char_len = font_len / 8;
		if(FX_ModS32(font_len, 8) != 0){
			char_len++;
		}
	}

	//BMP作成
	{
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, char_len, 16 / 8, 0, 0);
		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
			margin, 0, NULL);
//		GF_STR_PrintColor(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, NULL );
	}

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DMAIN,  heap_id);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DMAIN, &cma);
	
	//座標位置修正
	if(pos_center == TRUE){
		x -= font_len / 2;
	}
	y += MAIN_SURFACE_Y_INTEGER - 8;
	
	finit.fontoam_sys = fontoam_sys;
	finit.bmp = &bmpwin;
	finit.clact_set = CATS_GetClactSetPtr(crp);
	finit.pltt = CATS_PlttProxy(crp, pal_id);
	finit.parent = NULL;
	finit.char_ofs = cma.alloc_ofs;
	finit.x = x;
	finit.y = y;
	finit.bg_pri = bg_pri;
	finit.soft_pri = soft_pri;
	finit.draw_area = NNS_G2D_VRAM_TYPE_2DMAIN;
	finit.heap = heap_id;
	
	fontoam = FONTOAM_Init(&finit);
	if(pal_offset != 0){
		FONTOAM_SetPaletteOffset(fontoam, pal_offset);
	}
	FONTOAM_SetMat(fontoam, x, y);
	
	//解放処理
	GF_BGL_BmpWinDel(&bmpwin);
	
	fontact->fontoam = fontoam;
	fontact->cma = cma;
	fontact->len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   フォントOAMを削除する
 * @param   fontact		フォントアクターへのポインタ
 */
//--------------------------------------------------------------
void ADV_FontOamDelete(ADV_FONTACT *fontact)
{
	FONTOAM_Delete(fontact->fontoam);
	CharVramAreaFree(&fontact->cma);
}

//--------------------------------------------------------------
/**
 * @brief   フォントOAMの座標をセットする
 *
 * @param   fontact			フォントアクターへのポインタ
 * @param   x				座標X
 * @param   y				座標Y
 * @param   pos_center		FALSE(X左端座標) or TRUE(X中心座標)
 */
//--------------------------------------------------------------
void ADV_FontOamPosSet(ADV_FONTACT *fontact, int x, int y, int pos_center)
{
	//座標位置修正
	if(pos_center == TRUE){
		x -= fontact->len / 2;
	}
	y += MAIN_SURFACE_Y_INTEGER - 8;
	FONTOAM_SetMat(fontact->fontoam, x, y);
}


//--------------------------------------------------------------
/**
 * @brief   審判名をSTRBUFの形で取得する
 *
 * @param   judge_name_id		審判名ID
 * @param   heap_id				ヒープID
 *
 * @retval  審判名が入ったSTRBUFのポインタ
 *
 * ※戻り値のSTRBUFは呼び出し側で解放してやる事！(STRBUF_Delete)
 */
//--------------------------------------------------------------
STRBUF * ADV_MSGDAT_GetJudgeName(u32 judge_name_id, u32 heap_id)
{
	MSGDATA_MANAGER *man;
	STRBUF *str_buf;
	
	man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_judge_dat, heap_id);
	str_buf = MSGMAN_AllocString(man, judge_name_id);
	
	MSGMAN_Delete(man);
	return str_buf;
}

//--------------------------------------------------------------
/**
 * @brief   クリップの得点計算
 * @param   consys		コンテストシステムワークへのポインタ
 * @param   heap_id		一時的に使用するテンポラリヒープID
 */
//--------------------------------------------------------------
void ADV_ClipScoreCalc(CONTEST_SYSTEM *consys, int heap_id)
{
	u8 *theme_score;
	int i;
	
	OS_TPrintf("現在のテーマ＝%d\n", consys->c_game.theme);
	
	theme_score = IMC_ACCE_ScoreDataGet(heap_id, consys->c_game.theme);
	for(i = 0; i < BREEDER_MAX; i++){
		consys->c_game.score[i].clip = IMC_ACCE_ScoreGet(consys->c_game.imc_data[i], theme_score);
		OS_TPrintf("ブリーダー%dのクリップ獲得ポイント＝%d\n", i, consys->c_game.score[i].clip);
	}
	sys_FreeMemoryEz(theme_score);
}

//--------------------------------------------------------------
/**
 * @brief   BPの得点計算
 * @param   consys		コンテストシステムワークへのポインタ
 */
//--------------------------------------------------------------
void ADV_BPScoreCalc(CONTEST_SYSTEM *consys)
{
	int i, main, sub_1, sub_2, fur;
	u32 itemno;
	s32 bairitu, bp;
	
	for(i = 0; i < BREEDER_MAX; i++){
		itemno = PokeParaGet(consys->c_game.pp[i], ID_PARA_item, NULL);
		bairitu = 100;
		
		switch(consys->c_game.type){
		case CONTYPE_STYLE:
			main = PokeParaGet(consys->c_game.pp[i], ID_PARA_style, NULL);
			sub_1 = PokeParaGet(consys->c_game.pp[i], ID_PARA_strong, NULL);
			sub_2 = PokeParaGet(consys->c_game.pp[i], ID_PARA_beautiful, NULL);
			switch(itemno){
			case ITEM_AKAIBANDANA:
				bairitu = BP_ITEM_BAIRITU_MAIN;
				break;
			case ITEM_AOIBANDANA:
			case ITEM_KIIRONOBANDANA:
				bairitu = BP_ITEM_BAIRITU_SUB;
				break;
			}
			break;
		case CONTYPE_BEAUTIFUL:
			main = PokeParaGet(consys->c_game.pp[i], ID_PARA_beautiful, NULL);
			sub_1 = PokeParaGet(consys->c_game.pp[i], ID_PARA_style, NULL);
			sub_2 = PokeParaGet(consys->c_game.pp[i], ID_PARA_cute, NULL);
			switch(itemno){
			case ITEM_AOIBANDANA:
				bairitu = BP_ITEM_BAIRITU_MAIN;
				break;
			case ITEM_AKAIBANDANA:
			case ITEM_PINKUNOBANDANA:
				bairitu = BP_ITEM_BAIRITU_SUB;
				break;
			}
			break;
		case CONTYPE_CUTE:
			main = PokeParaGet(consys->c_game.pp[i], ID_PARA_cute, NULL);
			sub_1 = PokeParaGet(consys->c_game.pp[i], ID_PARA_beautiful, NULL);
			sub_2 = PokeParaGet(consys->c_game.pp[i], ID_PARA_clever, NULL);
			switch(itemno){
			case ITEM_PINKUNOBANDANA:
				bairitu = BP_ITEM_BAIRITU_MAIN;
				break;
			case ITEM_AOIBANDANA:
			case ITEM_MIDORINOBANDANA:
				bairitu = BP_ITEM_BAIRITU_SUB;
				break;
			}
			break;
		case CONTYPE_CLEVER:
			main = PokeParaGet(consys->c_game.pp[i], ID_PARA_clever, NULL);
			sub_1 = PokeParaGet(consys->c_game.pp[i], ID_PARA_cute, NULL);
			sub_2 = PokeParaGet(consys->c_game.pp[i], ID_PARA_strong, NULL);
			switch(itemno){
			case ITEM_MIDORINOBANDANA:
				bairitu = BP_ITEM_BAIRITU_MAIN;
				break;
			case ITEM_PINKUNOBANDANA:
			case ITEM_KIIRONOBANDANA:
				bairitu = BP_ITEM_BAIRITU_SUB;
				break;
			}
			break;
		case CONTYPE_STRONG:
			main = PokeParaGet(consys->c_game.pp[i], ID_PARA_strong, NULL);
			sub_1 = PokeParaGet(consys->c_game.pp[i], ID_PARA_clever, NULL);
			sub_2 = PokeParaGet(consys->c_game.pp[i], ID_PARA_style, NULL);
			switch(itemno){
			case ITEM_KIIRONOBANDANA:
				bairitu = BP_ITEM_BAIRITU_MAIN;
				break;
			case ITEM_MIDORINOBANDANA:
			case ITEM_AKAIBANDANA:
				bairitu = BP_ITEM_BAIRITU_SUB;
				break;
			}
			break;
		default:
			GF_ASSERT(0 && "不明なタイプです");
			return;
		}
		fur = PokeParaGet(consys->c_game.pp[i], ID_PARA_fur, NULL);
		
		bp = main + ((sub_1 + sub_2 + fur) / 2);
		OS_TPrintf("ブリーダー%d番のBP＝%d\n", i, bp);
		
		bp = bp * bairitu / 100;
		consys->c_game.score[i].bp = bp;
		OS_TPrintf("アイテム倍率効果=%d、修正後のBP＝%d\n", bairitu, bp);
	}
}


//--------------------------------------------------------------
/**
 * @brief   花柄模様のリソースロードする
 *
 * @param   csp		
 * @param   crp		
 * @param   pfd		
 */
//--------------------------------------------------------------
void ADV_FlowerResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int char_id, int pltt_id, int cell_id, int anm_id)
{
	if(char_id != -1){
		CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
			FLOWER_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, char_id);
	}
	if(pltt_id != -1){
		CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
			ARC_CONTEST_OBJ, CONTEST_VISUAL_OBJ_NCLR, 0, 
			1, NNS_G2D_VRAM_TYPE_2DMAIN, pltt_id);
	}
	if(cell_id != -1){
		CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
			FLOWER_NCER_BIN, 1, cell_id);
	}
	if(anm_id != -1){
		CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
			FLOWER_NANR_BIN, 1, anm_id);
	}
}

//--------------------------------------------------------------
/**
 * @brief   花柄模様リソースを解放する
 * @param   crp		
 */
//--------------------------------------------------------------
void ADV_FlowerResourceFree(CATS_RES_PTR crp, int char_id, int pltt_id, int cell_id, int anm_id)
{
	if(char_id != -1){
		CATS_FreeResourceChar(crp, char_id);
	}
	if(pltt_id != -1){
		CATS_FreeResourcePltt(crp, pltt_id);
	}
	if(cell_id != -1){
		CATS_FreeResourceCell(crp, cell_id);
	}
	if(anm_id != -1){
		CATS_FreeResourceCellAnm(crp, anm_id);
	}
}

//--------------------------------------------------------------
/**
 * @brief   花柄模様アクターを全て生成する
 *
 * @param   flower		
 * @param   csp		
 * @param   crp		
 * @param   char_id		
 * @param   pltt_id		
 * @param   cell_id		
 * @param   anm_id		
 * @param   pal_offset	パレット番号オフセット
 * @param   tcb_pri		TCBプライオリティ
 */
//--------------------------------------------------------------
void ADV_FlowerActorAddAll(FLOWER_WORK *flower, CATS_SYS_PTR csp, CATS_RES_PTR crp,	
	int char_id, int pltt_id, int cell_id, int anm_id, 
	int pal_offset, int soft_pri, int bg_pri, u32 tcb_pri)
{
	int i;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	
	GF_ASSERT(NELEMS(FlowerPos) == CON_FLOWER_MAX);
	
	obj_param = FlowerObjParam;
	obj_param.id[CLACT_U_CHAR_RES] = char_id;
	obj_param.id[CLACT_U_PLTT_RES] = pltt_id;
	obj_param.id[CLACT_U_CELL_RES] = cell_id;
	obj_param.id[CLACT_U_CELLANM_RES] = anm_id;
	obj_param.pal = pal_offset;
	obj_param.pri = soft_pri;
	obj_param.bg_pri = bg_pri;

	for(i = 0; i < CON_FLOWER_MAX; i++){
		flower->cap[i] = CATS_ObjectAdd_S(csp, crp, &obj_param);
		CATS_ObjectPosSetCap(flower->cap[i], FlowerPos[i].x, FlowerPos[i].y);
		CATS_ObjectAnimeSeqSetCap(flower->cap[i], FlowerPos[i].anm_seq);
		CATS_ObjectAffineSetCap(flower->cap[i], CLACT_AFFINE_NORMAL);
		CATS_ObjectUpdate(flower->cap[i]->act);
	}
	
	//動作タスク生成
	flower->tcb = TCB_Add(FlowerMoveTask, flower, tcb_pri);
}

//--------------------------------------------------------------
/**
 * @brief   花柄模様アクターを全て削除する
 * @param   flower		花柄模様アクター制御構造体
 */
//--------------------------------------------------------------
void ADV_FlowerActorDelAll(FLOWER_WORK *flower)
{
	int i;
	
	for(i = 0; i < CON_FLOWER_MAX; i++){
		CATS_ActorPointerDelete_S(flower->cap[i]);
	}
	TCB_Delete(flower->tcb);
	flower->tcb = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   花柄模様動作タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		花柄模様制御構造体ワークへのポインタ
 */
//--------------------------------------------------------------
static void FlowerMoveTask(TCB_PTR tcb, void *work)
{
	FLOWER_WORK *flower = work;
	int i;
	
	for(i = 0; i < CON_FLOWER_MAX; i++){
		CATS_ObjectRotationAddCap(flower->cap[i], FlowerPos[i].rotation);
	}
}


//--------------------------------------------------------------
/**
 * @brief   カメラのフラッシュエフェクトタスクを生成する
 *
 * @param   heap_id		ヒープID
 * @param   pfd			PFDへのポインタ
 * @param   tbl			フラッシュウェイトテーブルへのポインタ
 * @param   tbl_num		フラッシュウェイトテーブルの配列要素数
 * @param   loop		ループ回数(ADV_FLASH_EFF_LOOP_ETERNITYを指定すると無限ループ)
 *
 * @retval  生成したフラッシュエフェクトワークへのポインタ
 */
//--------------------------------------------------------------
ADV_FLASH_EFF_WORK * ADV_FlashEffectTaskSet(int heap_id, PALETTE_FADE_PTR pfd, 
	const u16 *tbl, int tbl_num, int loop, u32 tcb_pri)
{
	ADV_FLASH_EFF_WORK *flash;
	
	flash = sys_AllocMemory(heap_id, sizeof(ADV_FLASH_EFF_WORK));
	MI_CpuClear8(flash, sizeof(ADV_FLASH_EFF_WORK));
	
	flash->pfd = pfd;
	flash->tbl = tbl;
	flash->tbl_num = tbl_num;
	flash->loop = loop;
	
	flash->tcb = TCB_Add(ADV_FlashEffectMain, flash, tcb_pri);
	return flash;
}

//--------------------------------------------------------------
/**
 * @brief   カメラのフラッシュエフェクトタスク削除
 * @param   flash		フラッシュエフェクトワークへのポインタ
 */
//--------------------------------------------------------------
void ADV_FlashEffectTaskDel(ADV_FLASH_EFF_WORK *flash)
{
	GF_ASSERT(flash->tcb != NULL);
	TCB_Delete(flash->tcb);
	sys_FreeMemoryEz(flash);
}

//--------------------------------------------------------------
/**
 * @brief   カメラのフラッシュエフェクトが発動中かチェック
 *
 * @retval  TRUE：エフェクトは発動していない、FALSE:エフェクト発動中
 */
//--------------------------------------------------------------
BOOL ADV_FlashEffectCheck(void)
{
//	if(PaletteFadeCheck(flash->pfd) == 0){
//		return TRUE;
//	}
	if(IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) == TRUE){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   カメラのフラッシュエフェクト動作タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		フラッシュエフェクトワークへのポインタ
 */
//--------------------------------------------------------------
static void ADV_FlashEffectMain(TCB_PTR tcb, void *work)
{
	ADV_FLASH_EFF_WORK *flash = work;
	
//	if(PaletteFadeCheck(flash->pfd) != 0){
//		return;
//	}
	if(IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) == FALSE){
		return;
	}
	
	flash->timer++;
	if(flash->timer > flash->tbl[flash->tbl_pos]){
		ChangeBrightnessRequest(CON_CAMERA_FLASH_FRAME, BRIGHTNESS_NORMAL, CON_CAMERA_FLASH_EVY,
			PLANEMASK_ALL, MASK_MAIN_DISPLAY);
		Snd_SePlay(CSE_CAMERA_FLASH);
		
		flash->timer = 0;
		flash->tbl_pos++;
		if(flash->tbl_pos >= flash->tbl_num){
			if(flash->loop == 0){
				ADV_FlashEffectTaskDel(flash);
				return;
			}
			else if(flash->loop != ADV_FLASH_EFF_LOOP_ETERNITY){
				flash->loop--;
			}
			flash->tbl_pos = 0;
		}
	}
}
