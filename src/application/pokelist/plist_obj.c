//============================================================================================
/**
 * @file	plist_obj.c
 * @brief	ポケモンリストOBJ処理
 * @author	Hiroyuki Nakamura
 * @date	05.10.05
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/window.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/bmp_menu.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_regulation.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "application/app_tool.h"

#define	PLIST_OBJ_H_GLOBAL
#include "application/pokelist.h"
#include "plist_sys.h"
#include "plist_obj.h"
#include "application/plist_gra.naix"


//============================================================================================
//	定数定義
//============================================================================================
#define	CLA_SUB_SURFACE_OFFSET	( 256 * FX32_ONE )	// サブ画面のサーフェースオフセット


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void PokeListIconCellActMake( PLIST_WORK * wk );
static u8 IconMonsCheck( PL_PANEL_DATA * dat );


//============================================================================================
//	グローバル変数
//============================================================================================




//---------------------------------------------------------------------------------------------
/**
 * セルアクター初期化
 *
 * @param	wk		ポケモンリストワーク
 *
 * @return	none
 */
//---------------------------------------------------------------------------------------------
void PokeListCellActorInit( PLIST_WORK * wk )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// SUB DISP OBJ ON

	initVramTransferManagerHeap( 32, HEAPID_POKELIST );

	wk->csp = CATS_AllocMemory( HEAPID_POKELIST );
	wk->crp = CATS_ResourceCreate( wk->csp );

	{
		TCATS_OAM_INIT	coi = {
			0, 128,
			0, 32,
			0, 128,
			0, 32,
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			PLIST_ACT_MAX+6,		// ＋ポケモンアイコン
			1024,
			1024,
			GX_OBJVRAMMODE_CHAR_1D_32K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit( wk->csp, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->csp, wk->crp, PLIST_ACT_MAX+6 );
	}

	{
		CLACT_U_EASYRENDER_DATA * rd = CATS_EasyRenderGet(wk->csp);
		CLACT_U_SetSubSurfaceMatrix( rd, 0, CLA_SUB_SURFACE_OFFSET );
	}

	{
		TCATS_RESOURCE_FILE_LIST list = {
			"data/plist_chr.resdat",		// キャラクタ
			"data/plist_pal.resdat",		// パレット
			"data/plist_cell.resdat",		// セル
			"data/plist_canm.resdat",		// セルアニメ
			NULL,							// マルチセル
			NULL,							// マルチセルアニメ
			"data/plist_h.cldat"			// ヘッダー
		};
		CATS_ResourceLoadBinary( wk->csp, wk->crp, &list );
	}
}




void PokeListIconAdd( PLIST_WORK * wk, u8 pos, u16 px, u16 py )
{
	POKEMON_PARAM * pp;
	TCATS_OBJECT_ADD_PARAM	prm;
	u32	egg;

	pp = PokeParty_GetMemberPointer( wk->dat->pp, pos );

	wk->panel[pos].mons_px = px;
	wk->panel[pos].mons_py = py;

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp,
		ARC_POKEICON, PokeIconCgxArcIndexGetByPP(pp), 0, PLA_CHAR_ID_ICON1+pos );

	egg = PokeParaGet( pp, ID_PARA_tamago_flag, NULL );

	prm.no = PLA_CHAR_ID_ICON1+pos;		///< リソース内データの登録番号

	prm.x = px;				///< [ X ] 座標
	prm.y = py;				///< [ Y ] 座標
	prm.z = 0;				///< [ Z ] 座標

	prm.anm = 0;													///< アニメ番号
	prm.pri = 0;													///< 優先順位
	prm.pal = PokeIconPalNumGet(wk->panel[pos].mons,wk->panel[pos].form,egg)+3;	///< パレット番号
	prm.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;							///< 描画エリア

	prm.param1 = 0;
	prm.param2 = 0;
	prm.param3 = 0;
	prm.param4 = 0;

	wk->panel[pos].icon_cwp = CATS_ObjectAdd( wk->csp, wk->crp, &prm );
}






//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static const TCATS_OBJECT_ADD_PARAM	ActAddParam[] =
{
	{
		PLA_CHAR_ID_CURSOR,
		64, 24, 0,
		1, 3, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_CURSOR,
		64, 72, 0,
		2, 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_ENTER,
		232, 168, 0,
		2, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_ENTER,
		232, 184, 0,
		2, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_STATUS,
		36, 44, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_STATUS,
		164, 52, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_STATUS,
		36, 92, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_STATUS,
		164, 100, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_STATUS,
		36, 140, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_STATUS,
		164, 148, 0,
		0, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},
	{
		PLA_CHAR_ID_ITEM,
		164, 148, 0,
		2, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN,
		0, 0, 0, 0
	},

	{
		PLA_CHAR_ID_BUTTON_EF,
		164, 148, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB,
		0, 0, 0, 0
	}
};




void PokeListCellActSet( PLIST_WORK * wk )
{
	u32	i;

	wk->act_work[PLIST_ACT_CURSOR1] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[0] );
	wk->act_work[PLIST_ACT_CURSOR2] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[1] );
	wk->act_work[PLIST_ACT_ENTER] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[2] );
	wk->act_work[PLIST_ACT_EXIT] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[3] );

	wk->act_work[PLIST_ACT_BUTTON_EF] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[22] );

	for( i=0; i<6; i++ ){
		wk->act_work[PLIST_ACT_ST1+i] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[4+i] );
		wk->panel[i].st_px = ActAddParam[4+i].x;
		wk->panel[i].st_py = ActAddParam[4+i].y;
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_ST1+i], 0 );
		wk->act_work[PLIST_ACT_ITEM1+i] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[10+i] );
		wk->act_work[PLIST_ACT_CB1+i] = CATS_ObjectAdd( wk->csp, wk->crp, &ActAddParam[16+i] );
	}
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR2], 0 );
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_BUTTON_EF], 0 );
}

void PokeListBallActSet( PLIST_WORK * wk, u8 pos, u16 px, u16 py )
{
	TCATS_OBJECT_ADD_PARAM	prm;

	prm.no = PLA_CHAR_ID_BALL;		///< リソース内データの登録番号

	prm.x = px;				///< [ X ] 座標
	prm.y = py;				///< [ Y ] 座標
	prm.z = 0;				///< [ Z ] 座標

	prm.anm = 0;			///< アニメ番号
	prm.pri = 1;			///< 優先順位
	prm.pal = 0;			///< パレット番号
	prm.d_area = NNS_G2D_VRAM_TYPE_2DMAIN;	///< 描画エリア

	prm.param1 = 0;
	prm.param2 = 0;
	prm.param3 = 0;
	prm.param4 = 0;

	wk->act_work[PLIST_ACT_BALL1+pos] = CATS_ObjectAdd( wk->csp, wk->crp, &prm );
}


void PokeListCellActRerease( PLIST_WORK * wk )
{
	CATS_ResourceDestructor( wk->csp, wk->crp );
	CATS_FreeMemory( wk->csp );
}



void PokeList_StatusIconChg( PLIST_WORK * wk, u8 pos, u8 st )
{
	CLACT_WORK_PTR * awk = &wk->act_work[PLIST_ACT_ST1+pos];

	if( st == PL_ST_NONE ){
		CLACT_SetDrawFlag( *awk, 0 );
		return;
	}
	CLACT_AnmChg( *awk, st );
	CLACT_SetDrawFlag( *awk, 1 );
}

void PokeList_ItemIconChg( PLIST_WORK * wk, u8 pos, u16 item )
{
	CLACT_WORK_PTR * awk = &wk->act_work[PLIST_ACT_ITEM1+pos];

	if( item == 0 ){
		CLACT_SetDrawFlag( *awk, 0 );
		return;
	}
	if( ItemMailCheck( item ) == TRUE ){
		CLACT_AnmChg( *awk, 1 );
	}else{
		CLACT_AnmChg( *awk, 0 );
	}
	CLACT_SetDrawFlag( *awk, 1 );
}

void PokeList_MailIconChg( PLIST_WORK * wk, u8 pos )
{
	CLACT_WORK_PTR * awk = &wk->act_work[PLIST_ACT_ITEM1+pos];

	CLACT_AnmChg( *awk, 1 );
	CLACT_SetDrawFlag( *awk, 1 );
}

void PokeList_ItemIconPosSet( PLIST_WORK * wk, u8 pos, s16 x, s16 y )
{
	CLACT_WORK_PTR * awk = &wk->act_work[PLIST_ACT_ITEM1+pos];

	wk->panel[pos].item_px = x+8;
	wk->panel[pos].item_py = y+8;
	CATS_ObjectPosSet( *awk, wk->panel[pos].item_px, wk->panel[pos].item_py );
}

void PokeList_CustomIconPosSet( PLIST_WORK * wk, u8 pos )
{
	CATS_ObjectPosSet(
		wk->act_work[PLIST_ACT_CB1+pos], wk->panel[pos].item_px+8, wk->panel[pos].item_py );
}

void PokeList_CustomIconChg( PLIST_WORK * wk, u8 pos )
{
	CLACT_WORK_PTR * awk = &wk->act_work[PLIST_ACT_CB1+pos];

	if( wk->panel[pos].cb == 0 ){
		CLACT_SetDrawFlag( *awk, 0 );
		return;
	}
	CLACT_SetDrawFlag( *awk, 1 );
}






static void PokeIconAnmChg( CLACT_WORK_PTR awp, u8 anm )
{
	if( CLACT_AnmGet( awp ) == anm ){ return; }
	CLACT_AnmFrameSet( awp, 0 );
	CLACT_AnmChg( awp, anm );
}

static u8 PokeIconAnmCheck( PL_PANEL_DATA * dat )
{
	if( dat->hp == 0 ){
		OS_Printf( "HP : %d\n", dat->hp );
		return POKEICON_ANM_DEATH;
	}

	if( dat->st != PL_ST_NONE && dat->st != PL_ST_POKERUS && dat->st != PL_ST_HINSI ){
		return POKEICON_ANM_STCHG;
	}

	switch( GetHPGaugeDottoColor( dat->hp, dat->mhp, PL_HP_DOTTO_MAX ) ){
	case HP_DOTTO_MAX:
		return POKEICON_ANM_HPMAX;
	case HP_DOTTO_GREEN:	// 緑
		return POKEICON_ANM_HPGREEN;
	case HP_DOTTO_YELLOW:	// 黄
		return POKEICON_ANM_HPYERROW;
	case HP_DOTTO_RED:		// 赤
		return POKEICON_ANM_HPRED;
	}

	return POKEICON_ANM_DEATH;
}

void PokeIconAnime( PLIST_WORK * wk )
{
	PL_PANEL_DATA * dat;
	u16	i;
	u16	anm;


	for( i=0; i<6; i++ ){
		dat = &wk->panel[i];
		if( dat->flg == 0 ){ continue; }

		if( wk->chg_wk.flg == 1 && ( wk->chg_wk.pos[0] == i || wk->chg_wk.pos[1] == i ) ){
			anm = POKEICON_ANM_DEATH;
		}else{
			anm = PokeIconAnmCheck( dat );
		}

		PokeIconAnmChg( dat->icon_cwp, anm );
		CLACT_AnmFrameChg( dat->icon_cwp, FX32_ONE );

		if( wk->pos == i && anm != POKEICON_ANM_DEATH && anm != POKEICON_ANM_STCHG ){
			if( CLACT_AnmFrameGet( dat->icon_cwp ) == 0 ){
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py-3 );
			}else{
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py+1 );
			}
			continue;
		}
		CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py );
	}
}

static u8 IconMonsCheck( PL_PANEL_DATA * dat )
{
	// ？アイコン
	if( dat->mons == 0 || dat->mons > MONSNO_END ){
		return FALSE;
	}
	return TRUE;
}



void PokeList_SelCursorChgDirect( PLIST_WORK * wk, u8 pos, u8 pal )
{
	u8	px, py;

	PointerWkPosGet( &wk->mv_tbl[pos], &px, &py );

	CLACT_AnmChg(
		wk->act_work[PLIST_ACT_CURSOR1], PokeListSelCursorCheck( wk->dat->type, pos ) );
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 1 );
	CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR1], px, py );
	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], pal );
}



//--------------------------------------------------------------------------------------------
/**
 * サブボタンエフェクト
 */
//--------------------------------------------------------------------------------------------
void PokeListObj_SubButtonEffInit( PLIST_WORK * wk, s16 x, s16 y )
{
	VecFx32 vec;
		
	vec.x = x * FX32_ONE;
	vec.y = y * FX32_ONE;
	vec.y +=  CLA_SUB_SURFACE_OFFSET;
	vec.z = 0;
	
	CLACT_SetMatrix( wk->act_work[PLIST_ACT_BUTTON_EF], &vec );	

	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_BUTTON_EF], 1 );
//	CATS_ObjectPosSet( wk->act_work[PLIST_ACT_BUTTON_EF], x, y );
	CLACT_AnmFrameSet( wk->act_work[PLIST_ACT_BUTTON_EF], 0 );
	CLACT_AnmChg( wk->act_work[PLIST_ACT_BUTTON_EF], 0 );
}

void PokeListObj_SubButtonEffMain( PLIST_WORK * wk )
{
	if( CLACT_GetDrawFlag( wk->act_work[PLIST_ACT_BUTTON_EF] ) == 1 ){
		CLACT_AnmFrameChg( wk->act_work[PLIST_ACT_BUTTON_EF], FX32_ONE );

		if( CLACT_AnmFrameGet( wk->act_work[PLIST_ACT_BUTTON_EF] ) == 2 ){
			CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_BUTTON_EF], 0 );
		}
	}
}
