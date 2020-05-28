
//==============================================================================================
/**
 * @file	d_battle.c
 * @brief	戦闘用デバッグツール
 * @author	sogabe
 * @date	2006.04.14
 */
//==============================================================================================

#ifdef PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "msgdata/msg_debug_battle.h"
#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/gauge.h"
#include "battle/server_tool.h"
#include "poketool/monsno.h"
#include "poketool/waza_tool.h"
#include "battle/attr_def.h"
#include "battle/wazano_def.h"
#include "battle/chr_def.h"
#include "battle/tokusyu_def.h"
#include "battle/fight.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "system/wordset.h"
#include "itemtool/itemsym.h"
#include "itemtool/myitem.h"

#include "system/main.h"
#include "savedata/savedata.h"

#include "system/bmp_menu.h"
#include "system/window.h"

#include "battle/fight_def.h"		///<ServerParam内にデバッグパラメータメンバを追加しているため、許可
#include "battle/server_def.h"		///<ServerParam内にデバッグパラメータメンバを追加しているため、許可

//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================

void	DebugBattleInit(BATTLE_WORK *bw);
BOOL	DebugBattleMain(BATTLE_WORK *bw);
BOOL	DebugBattlePokemonReshuffle(BATTLE_WORK *bw,int client_no,int *pos);

void	DebugSoftSpritePosPut(BATTLE_WORK *bw);

static	void	DebugBattleScreenMake(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleAddStatusSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleStatusSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleCommandSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleYubihuruDebugSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);

static	void	DebugBattleWazaSelect(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattlePokemonSelect(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);

static	void	DB_AddStatusPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_TokuseiPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_SoubiPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_DamageLockPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_ReshuffleControlPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_OsyaberiRankPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_CriticalPut(DEBUG_BATTLE_PARAM *dbp);
static	void	DB_RemainHeapPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);

static	void	DB_MonsNamePut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_MonsStatusAllPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_MonsStatusPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos);

static	void	DB_CommandPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_CommandDataPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_WazaPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_DirPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_PokemonPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos);

static	void	DB_YubihuruDebugPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DB_YubihuruDebugWazaPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos,int mode);

static	void	CursorMove(DEBUG_BATTLE_PARAM *dbp,int pos);

static	void	DebugBattleClientNoInit(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp);
static	void	DebugBattleNumPut(DEBUG_BATTLE_PARAM *dbp,int x,int y,int param,int keta,int pos,int mode);
static	int		DebugBattleNumCalc(DEBUG_BATTLE_PARAM *dbp,u32 *param,int keta,int min,int max,int mode);
static	int		DebugBattleSelMonsNoCalc(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos,int ofs);

#define	PAD_BUTTON_ALL	(PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y)

#define	CURSOR_X		(0)
#define	CURSOR_Y		(0)

#define	ADD_STATUS_X		(16)
#define	ADD_STATUS_Y		(0)
#define	ADD_TOKUSEI_X		(16)
#define	ADD_TOKUSEI_Y		(16)
#define	ADD_SOUBI_X			(16)
#define	ADD_SOUBI_Y			(32)
#define	DAMAGE_LOCK_X		(16)
#define	DAMAGE_LOCK_Y		(48)
#define	RESHUFFLE_CONTROL_X	(16)
#define	RESHUFFLE_CONTROL_Y	(64)
#define	OSYABERI_RANK_X		(16)
#define	OSYABERI_RANK_Y		(80)
#define	CRITICAL_X			(16)
#define	CRITICAL_Y			(96)

#define	ADD_STATUS_MAX		(7-1)	//追加効果100%系のページの項目数（0オリジンなので、-1する）

#define	REMAIN_HEAP_X	(16)
#define	REMAIN_HEAP_Y	(112)

#define	TYPE_X			(16)
#define	TYPE_Y			(0)

#define	MONS_NAME_X		(32)
#define	MONS_NAME_Y		(0)

#define	STATUS_X		(16)
#define	STATUS_Y		(16)

#define	STATUS_NUM_X	(72)
#define	STATUS_NUM_Y	(16)

#define	COMMAND_X		(16)
#define	COMMAND_Y		(16)

#define	COMMAND_DATA_X	(16)
#define	COMMAND_DATA_Y	(32)

#define	WAZA_X			(16)
#define	WAZA_Y			(32)

#define	DIR_X			(16)
#define	DIR_Y			(48)

#define	POKEMON_X		(16)
#define	POKEMON_Y		(32)

#define	YUBIHURU_DEBUG_X	(16)
#define	YUBIHURU_DEBUG_Y	(0)

#define	YUBIHURU_WAZA_X	(16)
#define	YUBIHURU_WAZA_Y	(16)

enum{
	SEQ_ADD_STATUS=0,	///<追加効果100%系
	SEQ_STATUS,			///<ポケモンパラメータ操作
	SEQ_COMMAND,		///<選択コマンド操作
	SEQ_YUBIHURU_DEBUG,	///<ゆびをふるデバッグ

	SEQ_END				///<この上に追加
};

enum{
	NUM_CALC_NONE=0,
	NUM_CALC_MOVE,
	NUM_CALC_CHANGE,
	NUM_CALC_END,
};

enum{
	MONS_NAME=0,
	MONS_STATUS_POW,
	MONS_STATUS_DEF,
	MONS_STATUS_AGI,
	MONS_STATUS_SPEPOW,
	MONS_STATUS_SPEDEF,
	MONS_STATUS_HIT,
	MONS_STATUS_AVOID
};

enum{
	MODE_NORMAL=0,
	MODE_ACTIVE,
	MODE_LOOP,
	MODE_STOP,
	MODE_DEFAULT_PARAM,
	MODE_DEFAULT_WAZA,
};

#define	NORMAL_LETTER	(1)
#define	NORMAL_SHADOW	(2)
#define	NORMAL_GROUND	(15)

#define	ACTIVE_LETTER	(3)
#define	ACTIVE_SHADOW	(2)
#define	ACTIVE_GROUND	(15)

#define	CURSOR_LETTER	(4)
#define	CURSOR_SHADOW	(2)
#define	CURSOR_GROUND	(15)

#define	PARA_UP_LETTER	(4)
#define	PARA_UP_SHADOW	(2)
#define	PARA_UP_GROUND	(15)

#define	PARA_DOWN_LETTER	(5)
#define	PARA_DOWN_SHADOW	(2)
#define	PARA_DOWN_GROUND	(15)

#define	COL_NORMAL		(GF_PRINTCOLOR_MAKE(NORMAL_LETTER,NORMAL_SHADOW,NORMAL_GROUND))
#define	COL_ACTIVE		(GF_PRINTCOLOR_MAKE(ACTIVE_LETTER,ACTIVE_SHADOW,ACTIVE_GROUND))
#define	COL_CURSOR		(GF_PRINTCOLOR_MAKE(CURSOR_LETTER,CURSOR_SHADOW,CURSOR_GROUND))
#define	COL_PARA_UP		(GF_PRINTCOLOR_MAKE(PARA_UP_LETTER,PARA_UP_SHADOW,PARA_UP_GROUND))
#define	COL_PARA_DOWN	(GF_PRINTCOLOR_MAKE(PARA_DOWN_LETTER,PARA_DOWN_SHADOW,PARA_DOWN_GROUND))

static	const	u16	pal[]={
		GX_RGB(31,31,31),				//0:白
		GX_RGB(13,13,13),				//1:濃い灰
		GX_RGB(24,24,24),				//2:薄い灰
		GX_RGB(15,31,15),				//3:うすみどり
		GX_RGB(31,15,15),				//4:うすあか
		GX_RGB(15,15,31),				//5:うすあお
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB(31,31,31),				//15:白
};

//--------------------------------------------------------------
/**
 * @brief	デバッグバトルツール初期化
 *
 * @param	bw		戦闘用パラメータ構造体
 */
//--------------------------------------------------------------
void	DebugBattleInit(BATTLE_WORK *bw)
{
	GF_BGL_INI			*bgl;
	PALETTE_FADE_PTR	pfd;
	DEBUG_BATTLE_PARAM	*dbp;

	dbp=&bw->server_param->dbp;
	dbp->win=BattleWorkGF_BGL_BMPWINGet(bw,MENU_WIN_NO);
	dbp->seq_no=0;
	dbp->page=0;
	dbp->pos=0;
	dbp->client_no=0;
	dbp->msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_debug_battle_dat,HEAPID_BATTLE);
	dbp->msg_buf=STRBUF_Create(0x100,HEAPID_BATTLE);

	bgl=BattleWorkGF_BGL_INIGet(bw);
	pfd=BattleWorkPfdGet(bw);

	bw->bld_init_req=1;

	G2_SetBG0Priority(BATTLE_3DBG_PRIORITY+1);
	GF_BGL_PrioritySet(BATTLE_FRAME_WINDOW,BATTLE_BGPRI_EFFECT);
	GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,BATTLE_BGPRI_WINDOW);

	BattleGaugePriSet(bw,GAUGE_DEFAULT_BGPRI+2);

	MenuWinCgxSet(bgl,GF_BGL_FRAME2_M,MENU_WIN_CGX_START,MENU_TYPE_SYSTEM,HEAPID_BATTLE);
	PaletteWorkSet_Arc(pfd, ARC_WINFRAME, MenuWinPalArcGet(), HEAPID_BATTLE, FADE_MAIN_BG, 0x20, MENU_WIN_PAL_NO*0x10);
	PaletteWorkSet(pfd, &pal, FADE_MAIN_BG, (MENU_WIN_PAL_NO+1)*0x10, 0x20);
	GF_BGL_BmpWinAdd(bgl,dbp->win,GF_BGL_FRAME2_M, 1,1,30,16,MENU_WIN_PAL_NO+1,MENU_MSG_START);
	GF_BGL_BmpWinDataFill(dbp->win,0x0f);
	BmpMenuWinWrite(dbp->win,WINDOW_TRANS_ON,MENU_WIN_CGX_START,MENU_WIN_PAL_NO);
	
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_ON);
}

//--------------------------------------------------------------
/**
 * @brief	デバッグバトルツールMAIN
 *
 * @param	bw		戦闘用パラメータ構造体
 *
 * @retval	FALSE:実行中 TRUE:デバッグモード終了
 */
//--------------------------------------------------------------
BOOL	DebugBattleMain(BATTLE_WORK *bw)
{
	DEBUG_BATTLE_PARAM	*dbp;

	dbp=&bw->server_param->dbp;

	switch(dbp->seq_no){
	case 0:
		DebugBattleScreenMake(bw,dbp);
		dbp->seq_no=1;
		break;
	case 1:
		DebugBattleSequence(bw,dbp);
		if(sys.trg&PAD_BUTTON_L){
			if(dbp->page==0){
				dbp->page=SEQ_END-1;
			}
			else{
				dbp->page--;
			}
			dbp->seq_no=0;
			dbp->sub_seq_no=0;
		}
		if(sys.trg&PAD_BUTTON_R){
			if(dbp->page==SEQ_END-1){
				dbp->page=0;
			}
			else{
				dbp->page++;
			}
			dbp->seq_no=0;
			dbp->sub_seq_no=0;
		}
		if(sys.trg & PAD_BUTTON_START){
			dbp->seq_no=2;
		}
		break;
	case 2:
		BmpMenuWinClear(dbp->win,WINDOW_TRANS_ON);
		GF_BGL_BmpWinDel(dbp->win);
		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_BGL_PrioritySet(BATTLE_FRAME_WINDOW,BATTLE_BGPRI_WINDOW);
		GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,BATTLE_BGPRI_EFFECT);
	
		BattleGaugePriSet(bw,GAUGE_DEFAULT_BGPRI);

		dbp->seq_no=0;

		sys_FreeMemoryEz(dbp->msg_buf);
		MSGMAN_Delete(dbp->msg_m);

		return TRUE;
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	デバッグバトルツールポケモン入れ替え制御
 *
 * @param[in]	bw			戦闘用パラメータ構造体
 * @param[in]	client_no	制御するClientNo
 * @param[out]	pos			入れ替えるポケモンのSelMonsNo
 *
 * @retval	FALSE:実行中 TRUE:デバッグモード終了
 */
//--------------------------------------------------------------
BOOL	DebugBattlePokemonReshuffle(BATTLE_WORK *bw,int client_no,int *pos)
{
	DEBUG_BATTLE_PARAM	*dbp;

	dbp=&bw->server_param->dbp;

	switch(dbp->seq_no){
	case 0:
		if(((bw->server_param->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE)==0)||
		   ((dbp->debug_flag&DEBUG_FLAG_RESHUFFLE_CONTROL)==0)){
			return TRUE;
		}
		DebugBattleInit(bw);
		dbp->client_no=client_no;
		dbp->sel_mons=*pos;
		DB_PokemonPut(bw,dbp,*pos);
		dbp->seq_no++;
		break;
	case 1:
		if(sys.trg & PAD_BUTTON_A){
			dbp->sel_mons=DebugBattleSelMonsNoCalc(bw,dbp,dbp->sel_mons,1);
			DB_PokemonPut(bw,dbp,dbp->sel_mons);
		}
		if(sys.trg & PAD_BUTTON_B){
			dbp->sel_mons=DebugBattleSelMonsNoCalc(bw,dbp,dbp->sel_mons,-1);
			DB_PokemonPut(bw,dbp,dbp->sel_mons);
		}
		if(sys.trg & PAD_BUTTON_START){
			dbp->seq_no=2;
		}
		break;
	case 2:
		BmpMenuWinClear(dbp->win,WINDOW_TRANS_ON);
		GF_BGL_BmpWinDel(dbp->win);
		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_BGL_PrioritySet(BATTLE_FRAME_WINDOW,BATTLE_BGPRI_WINDOW);
		GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,BATTLE_BGPRI_EFFECT);
	
		BattleGaugePriSet(bw,GAUGE_DEFAULT_BGPRI);

		*pos=dbp->sel_mons;
		dbp->seq_no=0;

		sys_FreeMemoryEz(dbp->msg_buf);
		MSGMAN_Delete(dbp->msg_m);

		return TRUE;
		break;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	デバッグバトルソフトスプライト座標表示
 *
 * @param[in]	bw			戦闘用パラメータ構造体
 */
//--------------------------------------------------------------
#define	TYPE_AA_X	(0)
#define	TYPE_AA_Y	(8*3)
#define	TYPE_AA_V	(8*6)
#define	TYPE_BB_X	(128)
#define	TYPE_BB_Y	(128+8*3)
#define	TYPE_BB_V	(128+8*6)

#define	TYPE_A_X	(0)
#define	TYPE_A_Y	(8*3)
#define	TYPE_A_V	(8*6)
#define	TYPE_C_X	(8*9)
#define	TYPE_C_Y	(8*12)
#define	TYPE_C_V	(8*15)

#define	TYPE_D_X	(80)
#define	TYPE_D_Y	(80+8*3)
#define	TYPE_D_V	(80+8*6)
#define	TYPE_B_X	(80+8*9)
#define	TYPE_B_Y	(80+8*12)
#define	TYPE_B_V	(80+8*15)

extern	SOFT_SPRITE	*CT_CPSoftSpriteGet(CLIENT_PARAM *cp);
void	DebugSoftSpritePosPut(BATTLE_WORK *bw)
{
	GF_BGL_BMPWIN	*win;
	CLIENT_PARAM	*cp;
	SOFT_SPRITE		*ss;
	STRBUF			*msg_buf;
	int				client_no;

	win=BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO);
	msg_buf=BattleWorkSTRBUFGet(bw);

	GF_BGL_BmpWinDataFill(win,0xff);

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_D_X,0,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_D_Y,0,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_D_V,0,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_D_V,0,0,COL_NORMAL,NULL);
		}

		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_B_X,0,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_B_Y,0,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_B_V,0,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_B_V,0,0,COL_NORMAL,NULL);
		}

		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_A);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_A_X,16,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_A_Y,16,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_A_V,16,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_A_V,16,0,COL_NORMAL,NULL);
		}

		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_C);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_C_X,16,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_C_Y,16,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_C_V,16,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_C_V,16,0,COL_NORMAL,NULL);
		}
	}
	else{
		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_BB);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_BB_X,0,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_BB_Y,0,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_BB_V,0,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_BB_V,0,0,COL_NORMAL,NULL);
		}

		client_no=BattleWorkClientNoGet(bw,CLIENT_TYPE_AA);
		cp=BattleWorkClientParamGet(bw,client_no);
		ss=CT_CPSoftSpriteGet(cp);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_X),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_AA_X,16,0,COL_NORMAL,NULL);
		STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_POS_Y),3,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_AA_Y,16,0,COL_NORMAL,NULL);
		if(SoftSpriteParaGet(ss,SS_PARA_VANISH)){
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_VANISH),1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_AA_V,16,0,COL_NORMAL,NULL);
		}
		else{
			STRBUF_SetNumber(msg_buf,SoftSpriteParaGet(ss,SS_PARA_ALPHA),2,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintColor(win,FONT_SYSTEM,msg_buf,TYPE_AA_V,16,0,COL_NORMAL,NULL);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	デバッグ画面生成
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleScreenMake(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinDataFill(dbp->win,0xff);

	dbp->pos=0;
	DebugBattleClientNoInit(bw,dbp);

	switch(dbp->page){
	case SEQ_ADD_STATUS:
		DB_AddStatusPut(dbp);
		DB_TokuseiPut(dbp);
		DB_SoubiPut(dbp);
		DB_DamageLockPut(dbp);
		DB_ReshuffleControlPut(dbp);
		DB_OsyaberiRankPut(dbp);
		DB_CriticalPut(dbp);
#ifdef DEBUG_ONLY_FOR_sogabe
		DB_RemainHeapPut(bw,dbp);
#endif DEBUG_ONLY_FOR_sogabe
		break;
	case SEQ_STATUS:
		DB_MonsNamePut(bw,dbp);
		DB_MonsStatusAllPut(bw,dbp);
		break;
	case SEQ_COMMAND:
		DB_MonsNamePut(bw,dbp);
		DB_CommandPut(bw,dbp);
		DB_CommandDataPut(bw,dbp);
		break;
	case SEQ_YUBIHURU_DEBUG:
		{
			int	i;

			DB_YubihuruDebugPut(bw,dbp);
			for(i=0;i<7;i++){
				DB_YubihuruDebugWazaPut(bw,dbp,i,MODE_NORMAL);
			}
		}
		break;
	}
	CursorMove(dbp,dbp->pos);
}

//--------------------------------------------------------------
/**
 * @brief	デバッグシーケンス
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	switch(dbp->page){
	case SEQ_ADD_STATUS:
		DebugBattleAddStatusSequence(bw,dbp);
		break;
	case SEQ_STATUS:
		DebugBattleStatusSequence(bw,dbp);
		break;
	case SEQ_COMMAND:
		DebugBattleCommandSequence(bw,dbp);
		break;
	case SEQ_YUBIHURU_DEBUG:
		DebugBattleYubihuruDebugSequence(bw,dbp);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	デバッグシーケンス（追加効果100%系）
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleAddStatusSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	if(sys.trg & PAD_KEY_UP){
		if(dbp->pos==0){
			CursorMove(dbp,ADD_STATUS_MAX);
		}
		else{
			CursorMove(dbp,dbp->pos-1);
		}
	}
	if(sys.trg & PAD_KEY_DOWN){
		if(dbp->pos<ADD_STATUS_MAX){
			CursorMove(dbp,dbp->pos+1);
		}
		else{
			CursorMove(dbp,0);
		}
	}
	if(sys.trg & PAD_BUTTON_ALL){
		switch(dbp->pos){
		case 0:
			dbp->debug_flag^=DEBUG_FLAG_ADD_STATUS;
			DB_AddStatusPut(dbp);
			break;
		case 1:
			dbp->debug_flag^=DEBUG_FLAG_TOKUSYU;
			DB_TokuseiPut(dbp);
			break;
		case 2:
			dbp->debug_flag^=DEBUG_FLAG_SOUBI;
			DB_SoubiPut(dbp);
			break;
		case 3:
			dbp->debug_flag^=DEBUG_FLAG_DAMAGE_LOCK;
			DB_DamageLockPut(dbp);
			break;
		case 4:
			dbp->debug_flag^=DEBUG_FLAG_RESHUFFLE_CONTROL;
			DB_ReshuffleControlPut(dbp);
			break;
		case 5:
			if((sys.trg & PAD_BUTTON_A)&&(dbp->osyaberi_rank<3)){
				dbp->osyaberi_rank++;
			}
			if((sys.trg & PAD_BUTTON_B)&&(dbp->osyaberi_rank>0)){
				dbp->osyaberi_rank--;
			}
			DB_OsyaberiRankPut(dbp);
			break;
		case 6:
			dbp->debug_flag^=DEBUG_FLAG_CRITICAL;
			DB_CriticalPut(dbp);
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	デバッグシーケンス（ポケモンステータス変更系）
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleStatusSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	if(sys.trg & PAD_KEY_UP){
		if(dbp->pos==0){
			CursorMove(dbp,7);
		}
		else{
			CursorMove(dbp,dbp->pos-1);
		}
	}
	if(sys.trg & PAD_KEY_DOWN){
		if(dbp->pos<7){
			CursorMove(dbp,dbp->pos+1);
		}
		else{
			CursorMove(dbp,0);
		}
	}
	if(sys.trg & PAD_BUTTON_A){
		switch(dbp->pos){
		case MONS_NAME:
			if(dbp->client_no+1<bw->client_set_max){
				dbp->client_no++;
			}
			else{
				dbp->client_no=0;
			}
			DB_MonsNamePut(bw,dbp);
			DB_MonsStatusAllPut(bw,dbp);
			break;
		case MONS_STATUS_POW:
		case MONS_STATUS_DEF:
		case MONS_STATUS_AGI:
		case MONS_STATUS_SPEPOW:
		case MONS_STATUS_SPEDEF:
		case MONS_STATUS_HIT:
		case MONS_STATUS_AVOID:
			{
				int	pos;
				int	para;

				pos=dbp->pos-1;
				para=ST_ServerPokemonServerParamGet(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,NULL);

				if(para<12){
					para++;
					ST_ServerPokemonServerParamPut(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,&para);
					DB_MonsStatusPut(bw,dbp,pos);
				}
			}
			break;
		}
	}
	if(sys.trg & PAD_BUTTON_B){
		switch(dbp->pos){
		case MONS_NAME:
			if(dbp->client_no>0){
				dbp->client_no--;
			}
			else{
				dbp->client_no=bw->client_set_max-1;
			}
			DB_MonsNamePut(bw,dbp);
			DB_MonsStatusAllPut(bw,dbp);
			break;
		case MONS_STATUS_POW:
		case MONS_STATUS_DEF:
		case MONS_STATUS_AGI:
		case MONS_STATUS_SPEPOW:
		case MONS_STATUS_SPEDEF:
		case MONS_STATUS_HIT:
		case MONS_STATUS_AVOID:
			{
				int	pos;
				int	para;

				pos=dbp->pos-1;
				para=ST_ServerPokemonServerParamGet(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,NULL);

				if(para>0){
					para--;
					ST_ServerPokemonServerParamPut(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,&para);
					DB_MonsStatusPut(bw,dbp,pos);
				}
			}
			break;
		}
	}
	if(sys.trg & PAD_BUTTON_X){
		switch(dbp->pos){
		case MONS_NAME:
			if(dbp->client_no+1<bw->client_set_max){
				dbp->client_no++;
			}
			else{
				dbp->client_no=0;
			}
			DB_MonsNamePut(bw,dbp);
			DB_MonsStatusAllPut(bw,dbp);
			break;
		case MONS_STATUS_POW:
		case MONS_STATUS_DEF:
		case MONS_STATUS_AGI:
		case MONS_STATUS_SPEPOW:
		case MONS_STATUS_SPEDEF:
		case MONS_STATUS_HIT:
		case MONS_STATUS_AVOID:
			{
				int	pos;
				int	para;

				pos=dbp->pos-1;
				para=12;
				ST_ServerPokemonServerParamPut(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,&para);
				DB_MonsStatusPut(bw,dbp,pos);
			}
			break;
		}
	}
	if(sys.trg & PAD_BUTTON_Y){
		switch(dbp->pos){
		case MONS_NAME:
			if(dbp->client_no>0){
				dbp->client_no--;
			}
			else{
				dbp->client_no=bw->client_set_max-1;
			}
			DB_MonsNamePut(bw,dbp);
			DB_MonsStatusAllPut(bw,dbp);
			break;
		case MONS_STATUS_POW:
		case MONS_STATUS_DEF:
		case MONS_STATUS_AGI:
		case MONS_STATUS_SPEPOW:
		case MONS_STATUS_SPEDEF:
		case MONS_STATUS_HIT:
		case MONS_STATUS_AVOID:
			{
				int	pos;
				int	para;

				pos=dbp->pos-1;
				para=0;
				ST_ServerPokemonServerParamPut(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,&para);
				DB_MonsStatusPut(bw,dbp,pos);
			}
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	デバッグシーケンス（ポケモン操作系）
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleCommandSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;
	int	command;
	int	max_tbl[]={3,2,2,1};

	command=sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]-SERVER_FIGHT_COMMAND_NO;

	//何か編集されたら、ポケモン入れ替え制御もONにする
	if(sys.trg & PAD_BUTTON_ALL){
		dbp->debug_flag|=DEBUG_FLAG_RESHUFFLE_CONTROL;
	}

	switch(dbp->pos){
	case 0:
		if(sys.trg & PAD_BUTTON_ALL){
			if(bw->fight_type&FIGHT_TYPE_2vs2){
				dbp->client_no^=2;
				if(sp->no_reshuffle_client&No2Bit(dbp->client_no)){
					dbp->client_no^=2;
				}
				DB_MonsNamePut(bw,dbp);
				DB_CommandPut(bw,dbp);
				DB_CommandDataPut(bw,dbp);
			}
		}
		break;
	case 1:
		//アイテム、にげるは、なしの方向で
		if(sys.trg & PAD_BUTTON_ALL){
			if(sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]==SERVER_FIGHT_COMMAND_NO){
				if((ST_ServerReshuffleCheck(bw,sp,dbp->client_no)==TRUE)&&
				   (ST_EscapeNGCheck(bw,sp,dbp->client_no,NULL)==FALSE)){
					sp->client_act_work[dbp->client_no][ACT_PARA_SELECT_COMMAND]=SELECT_POKEMON_COMMAND;
					sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]=SERVER_POKEMON_COMMAND_NO;
					sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=
						DebugBattleSelMonsNoCalc(bw,dbp,6,NULL);
					sp->reshuffle_sel_mons_no[dbp->client_no]=sp->client_act_work[dbp->client_no][ACT_PARA_WORK];
					DB_CommandPut(bw,dbp);
					DB_CommandDataPut(bw,dbp);
				}
			}
			else{
				sp->client_act_work[dbp->client_no][ACT_PARA_SELECT_COMMAND]=SELECT_FIGHT_COMMAND;
				sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]=SERVER_FIGHT_COMMAND_NO;
				sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=1;
				DB_CommandPut(bw,dbp);
				DB_CommandDataPut(bw,dbp);
			}
		}
		break;
	case 2:
		switch(sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]){
		case SERVER_FIGHT_COMMAND_NO:
			DebugBattleWazaSelect(bw,dbp);
			break;
		case SERVER_POKEMON_COMMAND_NO:
			DebugBattlePokemonSelect(bw,dbp);
			break;
		}
		break;
	case 3:
		{
			int	pos;
			int	waza_no;

			pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK]-1;
			waza_no=ST_ServerPokemonServerParamGet(sp,dbp->client_no,ID_PSP_waza1+pos,NULL);
			if(WT_WazaDataParaGet(waza_no,ID_WTD_attackrange)==RANGE_NORMAL){
				if(sys.trg & PAD_BUTTON_A){
					do{
						if(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]==bw->client_set_max-1){
							sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=0;
						}
						else{
							sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]++;
						}
					}while(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]==dbp->client_no);
					DB_DirPut(bw,dbp);
				}
				if(sys.trg & PAD_BUTTON_B){
					do{
						if(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]==0){
							sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=bw->client_set_max-1;
						}
						else{
							sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]--;
						}
					}while(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]==dbp->client_no);
					DB_DirPut(bw,dbp);
				}
			}
		}
		break;
	}
	if(sys.trg & PAD_KEY_UP){
		if(dbp->pos==0){
			CursorMove(dbp,max_tbl[command]);
		}
		else{
			CursorMove(dbp,dbp->pos-1);
		}
	}
	if(sys.trg & PAD_KEY_DOWN){
		if(dbp->pos<max_tbl[command]){
			CursorMove(dbp,dbp->pos+1);
		}
		else{
			CursorMove(dbp,0);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	デバッグシーケンス（ゆびをふるデバッグ）
 *
 * @param	dbp		戦闘デバッグ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DebugBattleYubihuruDebugSequence(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;
	int	pos;

	pos=dbp->pos-1;

	switch(dbp->sub_seq_no){
	case 0:
		switch(dbp->pos){
		case 0:
			if(sys.trg & PAD_BUTTON_A){
				if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_SET){
					dbp->debug_flag&=DEBUG_FLAG_YUBIHURU_DEBUG_SET_OFF;
					dbp->debug_flag|=DEBUG_FLAG_YUBIHURU_DEBUG_RANGE;
					dbp->yubihuru_no=dbp->yubihuru_waza[0];
				}
				else if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_RANGE){
					dbp->debug_flag&=DEBUG_FLAG_YUBIHURU_DEBUG_RANGE_OFF;
				}
				else{
					dbp->debug_flag|=DEBUG_FLAG_YUBIHURU_DEBUG_SET;
					dbp->yubihuru_no=0;
				}
				DB_YubihuruDebugPut(bw,dbp);
			}
			if(sys.trg & PAD_BUTTON_B){
				if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_SET){
					dbp->debug_flag&=DEBUG_FLAG_YUBIHURU_DEBUG_SET_OFF;
				}
				else if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_RANGE){
					dbp->debug_flag&=DEBUG_FLAG_YUBIHURU_DEBUG_RANGE_OFF;
					dbp->debug_flag|=DEBUG_FLAG_YUBIHURU_DEBUG_SET;
					dbp->yubihuru_no=0;
				}
				else{
					dbp->debug_flag|=DEBUG_FLAG_YUBIHURU_DEBUG_RANGE;
					dbp->yubihuru_no=dbp->yubihuru_waza[0];
				}
				dbp->yubihuru_no=0;
				DB_YubihuruDebugPut(bw,dbp);
			}
			break;
		default:
			if(sys.trg & PAD_BUTTON_A){
				dbp->sub_seq_no=1;
			}
			break;
		}
		if(sys.trg & PAD_KEY_UP){
			if(dbp->pos==0){
				CursorMove(dbp,7);
			}
			else{
				CursorMove(dbp,dbp->pos-1);
			}
		}
		if(sys.trg & PAD_KEY_DOWN){
			if(dbp->pos<7){
				CursorMove(dbp,dbp->pos+1);
			}
			else{
				CursorMove(dbp,0);
			}
		}
		break;
	case 1:
		DB_YubihuruDebugWazaPut(bw,dbp,pos,MODE_ACTIVE);
		dbp->sub_seq_no++;
	case 2:
		switch(DebugBattleNumCalc(dbp,&dbp->yubihuru_waza[pos],3,0,WAZANO_MAX,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_SET){
				dbp->yubihuru_no=0;
			}
			else if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_RANGE){
				dbp->yubihuru_no=dbp->yubihuru_waza[0];
			}
		case NUM_CALC_MOVE:
			DB_YubihuruDebugWazaPut(bw,dbp,pos,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DB_YubihuruDebugWazaPut(bw,dbp,pos,MODE_NORMAL);
			dbp->sub_seq_no=0;
			break;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	技選択Act
 */
//--------------------------------------------------------------
static	void	DebugBattleWazaSelect(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	int	waza_max;
	int	pos;
	int	waza_no;
	int	client_no;
	SERVER_PARAM	*sp=bw->server_param;

	waza_max=ST_ServerWazaCountGet(bw,sp,dbp->client_no);

	if(waza_max==1){
		return;
	}
			
	if(sys.trg & PAD_BUTTON_A){
		if(waza_max==sp->client_act_work[dbp->client_no][ACT_PARA_WORK]){
			sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=1;
		}
		else{
			sp->client_act_work[dbp->client_no][ACT_PARA_WORK]++;
		}
		DB_WazaPut(bw,dbp);
		pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK]-1;
		waza_no=ST_ServerPokemonServerParamGet(sp,dbp->client_no,ID_PSP_waza1+pos,NULL);
		sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=
			ST_ServerDefenceClientSet(bw,sp,dbp->client_no,waza_no,1,0);
		if(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]!=dbp->client_no){
			sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=0;
		}
		DB_DirPut(bw,dbp);
	}
	if(sys.trg & PAD_BUTTON_B){
		if(sp->client_act_work[dbp->client_no][ACT_PARA_WORK]==1){
			sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=waza_max;
		}
		else{
			sp->client_act_work[dbp->client_no][ACT_PARA_WORK]--;
		}
		DB_WazaPut(bw,dbp);
		pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK]-1;
		waza_no=ST_ServerPokemonServerParamGet(sp,dbp->client_no,ID_PSP_waza1+pos,NULL);
		sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=
			ST_ServerDefenceClientSet(bw,sp,dbp->client_no,waza_no,1,0);
		if(sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]!=dbp->client_no){
			sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO]=0;
		}
		DB_DirPut(bw,dbp);
	}
	sp->waza_no_pos[dbp->client_no]=sp->client_act_work[dbp->client_no][ACT_PARA_WORK]-1;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン選択Act
 */
//--------------------------------------------------------------
static	void	DebugBattlePokemonSelect(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	int	pos;
	SERVER_PARAM	*sp=bw->server_param;

	if(sys.trg & PAD_BUTTON_A){
		pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK];
		sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=DebugBattleSelMonsNoCalc(bw,dbp,pos,1);
		sp->reshuffle_sel_mons_no[dbp->client_no]=sp->client_act_work[dbp->client_no][ACT_PARA_WORK];
		DB_PokemonPut(bw,dbp,sp->reshuffle_sel_mons_no[dbp->client_no]);
	}
	if(sys.trg & PAD_BUTTON_B){
		pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK];
		sp->client_act_work[dbp->client_no][ACT_PARA_WORK]=DebugBattleSelMonsNoCalc(bw,dbp,pos,-1);
		sp->reshuffle_sel_mons_no[dbp->client_no]=sp->client_act_work[dbp->client_no][ACT_PARA_WORK];
		DB_PokemonPut(bw,dbp,sp->reshuffle_sel_mons_no[dbp->client_no]);
	}
}

//--------------------------------------------------------------
/**
 * @brief	追加効果100%項目Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_AddStatusPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,ADD_STATUS_X,ADD_STATUS_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_ADD_STATUS){
		MSGMAN_GetString(dbp->msg_m,DB_ADD_STATUS_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_ADD_STATUS_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,ADD_STATUS_X,ADD_STATUS_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	特性発動100%項目Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_TokuseiPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,ADD_TOKUSEI_X,ADD_TOKUSEI_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_TOKUSYU){
		MSGMAN_GetString(dbp->msg_m,DB_TOKUSEI_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_TOKUSEI_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,ADD_TOKUSEI_X,ADD_TOKUSEI_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	装備効果100%項目Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_SoubiPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,ADD_SOUBI_X,ADD_SOUBI_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_SOUBI){
		MSGMAN_GetString(dbp->msg_m,DB_SOUBI_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_SOUBI_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,ADD_SOUBI_X,ADD_SOUBI_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	ダメージ乱数を固定
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_DamageLockPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,DAMAGE_LOCK_X,DAMAGE_LOCK_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_DAMAGE_LOCK){
		MSGMAN_GetString(dbp->msg_m,DB_DAMAGE_LOCK_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_DAMAGE_LOCK_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,DAMAGE_LOCK_X,DAMAGE_LOCK_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン入れ替えを制御
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_ReshuffleControlPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,RESHUFFLE_CONTROL_X,RESHUFFLE_CONTROL_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_RESHUFFLE_CONTROL){
		MSGMAN_GetString(dbp->msg_m,DB_RESHUFFLE_CONTROL_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_RESHUFFLE_CONTROL_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,RESHUFFLE_CONTROL_X,RESHUFFLE_CONTROL_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	おしゃべりランク固定を制御
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_OsyaberiRankPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,OSYABERI_RANK_X,OSYABERI_RANK_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_OSYABERI_POWER0+dbp->osyaberi_rank,dbp->msg_buf);

	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,OSYABERI_RANK_X,OSYABERI_RANK_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	急所かならずを制御
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_CriticalPut(DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,CRITICAL_X,CRITICAL_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_CRITICAL){
		MSGMAN_GetString(dbp->msg_m,DB_CRITICAL_ON,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_CRITICAL_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,CRITICAL_X,CRITICAL_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	ヒープの残りメモリを表示
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_RemainHeapPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	u32	remain_memory;

	GF_BGL_BmpWinFill(dbp->win,0x0f,REMAIN_HEAP_X,REMAIN_HEAP_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_REMAIN_HEAP,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,REMAIN_HEAP_X,REMAIN_HEAP_Y,0,COL_NORMAL,NULL);

//	remain_memory=sys_GetHeapFreeSize(HEAPID_BATTLE);
//	remain_memory=(u32)&bw->server_param->psp;
	remain_memory=(u32)bw->server_param;

	STRBUF_SetNumber(dbp->msg_buf,remain_memory,10,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,REMAIN_HEAP_X+12*8,REMAIN_HEAP_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	モンスター名Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_MonsNamePut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	MSGDATA_MANAGER			*msg_m;

	GF_BGL_BmpWinFill(dbp->win,0x0f,TYPE_X,TYPE_Y,28*8,16);

	//ClientType
	MSGMAN_GetString(dbp->msg_m,DB_CLIENT_TYPE_AA+BattleWorkClientTypeGet(bw,dbp->client_no),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,TYPE_X,TYPE_Y,0,COL_NORMAL,NULL);
	
	//モンスター名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_monsname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,ST_ServerPokemonServerParamGet(bw->server_param,dbp->client_no,ID_PSP_monsno,NULL),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,MONS_NAME_X,MONS_NAME_Y,0,COL_NORMAL,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);
}

//--------------------------------------------------------------
/**
 * @brief	モンスターステータスPut
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_MonsStatusAllPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	int	pos;

	for(pos=0;pos<7;pos++){
		DB_MonsStatusPut(bw,dbp,pos);
	}
}

//--------------------------------------------------------------
/**
 * @brief	モンスターステータスPut
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_MonsStatusPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos)
{
	int	para;

	GF_BGL_BmpWinFill(dbp->win,0x0f,STATUS_X,STATUS_Y+16*pos,28*8,16);

	//STATUS
	MSGMAN_GetString(dbp->msg_m,DB_STATUS_POW+pos,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,STATUS_X,STATUS_Y+16*pos,0,COL_NORMAL,NULL);

	//ステータス値
	para=ST_ServerPokemonServerParamGet(bw->server_param,dbp->client_no,ID_PSP_abiritycnt_pow+pos,NULL);
	STRBUF_SetNumber(dbp->msg_buf,para,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,STATUS_NUM_X,STATUS_NUM_Y+16*pos,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	コマンドPut
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_CommandPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;
	int				command;

	GF_BGL_BmpWinFill(dbp->win,0x0f,COMMAND_X,COMMAND_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_COMMAND,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,COMMAND_X,COMMAND_Y,0,COL_NORMAL,NULL);

	command=sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]-SERVER_FIGHT_COMMAND_NO;

	MSGMAN_GetString(dbp->msg_m,DB_COMMAND_FIGHT+command,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,COMMAND_X+12*5,COMMAND_Y,0,COL_NORMAL,NULL);

}

//--------------------------------------------------------------
/**
 * @brief	コマンドデータPut
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_CommandDataPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;

	GF_BGL_BmpWinFill(dbp->win,0x0f,COMMAND_DATA_X,COMMAND_DATA_Y,28*8,16*7);

	switch(sp->client_act_work[dbp->client_no][ACT_PARA_ACT_NO]){
	case SERVER_FIGHT_COMMAND_NO:
		DB_WazaPut(bw,dbp);
		DB_DirPut(bw,dbp);
		break;
	case SERVER_POKEMON_COMMAND_NO:
		DB_PokemonPut(bw,dbp,sp->client_act_work[dbp->client_no][ACT_PARA_WORK]);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	選択技Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_WazaPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;
	MSGDATA_MANAGER	*msg_m;
	int				pos;
	int				pp;

	GF_BGL_BmpWinFill(dbp->win,0x0f,WAZA_X,WAZA_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_WAZA,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,WAZA_X,WAZA_Y,0,COL_NORMAL,NULL);

	pos=sp->client_act_work[dbp->client_no][ACT_PARA_WORK]-1;
	
	//技名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_wazaname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,ST_ServerPokemonServerParamGet(sp,dbp->client_no,ID_PSP_waza1+pos,NULL),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,WAZA_X+12*5,WAZA_Y,0,COL_NORMAL,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);

	//PP
	pp=ST_ServerPokemonServerParamGet(bw->server_param,dbp->client_no,ID_PSP_pp1+pos,NULL);
	STRBUF_SetNumber(dbp->msg_buf,pp,2,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,WAZA_X+12*14,WAZA_Y,0,COL_NORMAL,NULL);

}

//--------------------------------------------------------------
/**
 * @brief	攻撃対象Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_DirPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM	*sp=bw->server_param;
	MSGDATA_MANAGER	*msg_m;
	int				pos;

	GF_BGL_BmpWinFill(dbp->win,0x0f,DIR_X,DIR_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_DIR,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,DIR_X,DIR_Y,0,COL_NORMAL,NULL);

	pos=sp->client_act_work[dbp->client_no][ACT_PARA_CLIENT_NO];
	
	//ClientType
	MSGMAN_GetString(dbp->msg_m,DB_CLIENT_TYPE_AA+BattleWorkClientTypeGet(bw,pos),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,DIR_X+12*5,DIR_Y,0,COL_NORMAL,NULL);
	
	//モンスター名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_monsname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,ST_ServerPokemonServerParamGet(bw->server_param,pos,ID_PSP_monsno,NULL),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,DIR_X+12*6,DIR_Y,0,COL_NORMAL,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);
}

//--------------------------------------------------------------
/**
 * @brief	入れ替え対象Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_PokemonPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos)
{
	SERVER_PARAM	*sp=bw->server_param;
	MSGDATA_MANAGER	*msg_m;
	POKEPARTY		*poke_party;
	POKEMON_PARAM	*pp;

	GF_BGL_BmpWinFill(dbp->win,0x0f,POKEMON_X,POKEMON_Y,28*8,16);

	MSGMAN_GetString(dbp->msg_m,DB_POKEMON,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,POKEMON_X,POKEMON_Y,0,COL_NORMAL,NULL);

	poke_party=BattleWorkPokePartyGet(bw,dbp->client_no);
	pp=BattleWorkPokemonParamGet(bw,dbp->client_no,pos);

	//sel_mons_no
	STRBUF_SetNumber(dbp->msg_buf,pos+1,1,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,POKEMON_X+12*5,POKEMON_Y,0,COL_NORMAL,NULL);

	//モンスター名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_monsname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,PokeParaGet(pp,ID_PARA_monsno,NULL),dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,POKEMON_X+12*6,POKEMON_Y,0,COL_NORMAL,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);
}

//--------------------------------------------------------------
/**
 * @brief	ゆびをふるデバッグPut
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_YubihuruDebugPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,YUBIHURU_DEBUG_X,YUBIHURU_DEBUG_Y,28*8,16);

	if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_SET){
		MSGMAN_GetString(dbp->msg_m,DB_YUBIHURU_SET,dbp->msg_buf);
	}
	else if(dbp->debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_RANGE){
		MSGMAN_GetString(dbp->msg_m,DB_YUBIHURU_RANGE,dbp->msg_buf);
	}
	else{
		MSGMAN_GetString(dbp->msg_m,DB_YUBIHURU_OFF,dbp->msg_buf);
	}
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,YUBIHURU_DEBUG_X,YUBIHURU_DEBUG_Y,0,COL_NORMAL,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	ゆびをふるデバッグ技Put
 *
 * @param	sp		サーバ用パラメータ構造体
 */
//--------------------------------------------------------------
static	void	DB_YubihuruDebugWazaPut(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos,int mode)
{
	MSGDATA_MANAGER	*msg_m;

	GF_BGL_BmpWinFill(dbp->win,0x0f,YUBIHURU_WAZA_X,YUBIHURU_WAZA_Y+16*pos,28*8,16);

	//waza_no
//	STRBUF_SetNumber(dbp->msg_buf,dbp->yubihuru_waza[pos],3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
//	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,YUBIHURU_WAZA_X,YUBIHURU_WAZA_Y+16*pos,0,COL_NORMAL,NULL);
	DebugBattleNumPut(dbp,YUBIHURU_WAZA_X,YUBIHURU_WAZA_Y+16*pos,dbp->yubihuru_waza[pos],3,dbp->cur_pos_keta,mode);

	//技名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_wazaname_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,dbp->yubihuru_waza[pos],dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,YUBIHURU_WAZA_X+12*3,YUBIHURU_WAZA_Y+16*pos,0,COL_NORMAL,NULL);

	//メッセージマネージャ関連削除
	MSGMAN_Delete(msg_m);
}

//==============================================================================================
//
//	メニューカーソル移動
//
//==============================================================================================
static	void	CursorMove(DEBUG_BATTLE_PARAM *dbp,int pos)
{
	GF_BGL_BmpWinFill(dbp->win,0x0f,CURSOR_X,CURSOR_Y+16*dbp->pos,12,16);
	MSGMAN_GetString(dbp->msg_m,DB_CURSOR,dbp->msg_buf);
	GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,CURSOR_X,CURSOR_Y+16*pos,0,COL_NORMAL,NULL);
	dbp->pos=pos;
}

//==============================================================================================
//
//	ページ毎のClientNo初期化処理
//
//==============================================================================================
static	void	DebugBattleClientNoInit(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp)
{
	SERVER_PARAM		*sp=bw->server_param;

	dbp->client_no=0;

	if(dbp->page==SEQ_COMMAND){
		dbp->client_no=1;
		if(sp->no_reshuffle_client&No2Bit(dbp->client_no)){
			dbp->client_no^=2;
		}
	}
}

//==============================================================================================
//
//	数値表示
//
//==============================================================================================
static	void	DebugBattleNumPut(DEBUG_BATTLE_PARAM *dbp,int x,int y,int param,int keta,int pos,int mode)
{
	int		i;
	int		data,ofs;
	int		keta_tbl[10]={
		1000000000,
		100000000,
		10000000,
		1000000,
		100000,
		10000,
		1000,
		100,
		10,
		1,
	};

	ofs=0;
	for(i=0;i<keta;i++){
		data=param/keta_tbl[10-keta+i];
		param%=keta_tbl[10-keta+i];
		STRBUF_SetNumber(dbp->msg_buf,data,1,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
		if(mode==MODE_NORMAL){
			GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_NORMAL,NULL);
		}
		else{
			if((keta-1)-i==pos){
				GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_CURSOR,NULL);
			}
			else{
				GF_STR_PrintColor(dbp->win,FONT_SYSTEM,dbp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_ACTIVE,NULL);
			}
		}
		ofs+=FontProc_GetPrintStrWidth(FONT_SYSTEM,dbp->msg_buf,0);
	}
}

//==============================================================================================
//
//	数値編集
//
//==============================================================================================
static	int	DebugBattleNumCalc(DEBUG_BATTLE_PARAM *dbp,u32 *param,int keta,int min,int max,int mode)
{
	int ret=NUM_CALC_NONE;
	u32	calc_work[]={
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};

	if((sys.repeat & PAD_KEY_LEFT)&&(dbp->cur_pos_keta<(keta-1))){
		dbp->cur_pos_keta++;
		ret=NUM_CALC_MOVE;
	}
	else if((sys.repeat & PAD_KEY_RIGHT)&&(dbp->cur_pos_keta)){
		dbp->cur_pos_keta--;
		ret=NUM_CALC_MOVE;
	}
	else if(sys.repeat & PAD_KEY_UP){
		if(mode==MODE_LOOP){
			if((param[0]+calc_work[dbp->cur_pos_keta])>max){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[dbp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]+calc_work[dbp->cur_pos_keta])>max){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[dbp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.repeat & PAD_KEY_DOWN){
		if(mode==MODE_LOOP){
			if((param[0]<calc_work[dbp->cur_pos_keta])||((param[0]-calc_work[dbp->cur_pos_keta])<min)){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[dbp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]<calc_work[dbp->cur_pos_keta])||((param[0]-calc_work[dbp->cur_pos_keta])<min)){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[dbp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.trg & PAD_BUTTON_A){
		dbp->cur_pos_keta=0;
		ret=NUM_CALC_END;
	}

	return ret;
}

//==============================================================================================
//
//	繰り出せるSelMonsNoを返す
//
//==============================================================================================
static	int		DebugBattleSelMonsNoCalc(BATTLE_WORK *bw,DEBUG_BATTLE_PARAM *dbp,int pos,int ofs)
{
	SERVER_PARAM		*sp=bw->server_param;
	POKEPARTY			*poke_party;
	POKEMON_PARAM		*pp;
	int					client_no,client_pair_no;

	client_no=dbp->client_no;
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)||
	   (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)){
		client_pair_no=client_no;
	}
	else{
		client_pair_no=BattleWorkPartnerClientNoGet(bw,client_no);
	}

	poke_party=BattleWorkPokePartyGet(bw,dbp->client_no);
	if(pos==6){
		for(pos=0;pos<PokeParty_GetPokeCount(poke_party);pos++){
			pp=BattleWorkPokemonParamGet(bw,dbp->client_no,pos);
			if((PokeParaGet(pp,ID_PARA_hp,NULL))&&
			   (sp->sel_mons_no[client_no]!=pos)&&
			   (sp->sel_mons_no[client_pair_no]!=pos)){
				break;
			}
		}
	}
	else{
		pos+=ofs;
		if(pos>=PokeParty_GetPokeCount(poke_party)){
			pos=0;
		}
		else if(pos<0){
			pos=PokeParty_GetPokeCount(poke_party)-1;
		}
		do{
			pp=BattleWorkPokemonParamGet(bw,dbp->client_no,pos);
			if((PokeParaGet(pp,ID_PARA_hp,NULL))&&
			   (sp->sel_mons_no[client_no]!=pos)&&
			   (sp->sel_mons_no[client_pair_no]!=pos)){
				break;
			}
			else{
				pos+=ofs;
				if(pos>=PokeParty_GetPokeCount(poke_party)){
					pos=0;
				}
				else if(pos<0){
					pos=PokeParty_GetPokeCount(poke_party)-1;
				}
			}
		}while(1);
	}
	return pos;
}

#endif //PM_DEBUG
