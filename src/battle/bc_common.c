//==============================================================================
/**
 * @file	bc_common.h
 * @brief	戦闘・コンテスト共通で使用されるソース
 * @author	matsuda
 * @date	2006.05.26(金)
 */
//==============================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/gamedata.h"

#include "battle/battle_server.h"
#include "battle/client.h"
#include "battle/fight.h"
#include "battle/fight_tool.h"
#include "battle/server_tool.h"
#include "battle/client_tool.h"
#include "battle/ground.h"
#include "battle/scio.h"
#include "battle/tr_ai.h"
#include "battle/battle_id.h"

#include "poketool/poke_tool.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"

#include "gflib/touchpanel.h"

#include "itemtool/itemsym.h"
#include "itemtool/myitem.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/snd_tool.h"
#include "system/softsprite.h"
#include "system/gra_tool.h"

#include "wazaeffect/we_sys.h"

#include "client_def.h"
#include "client_tool_def.h"

#include "b_plist.h"
#include "b_bag.h"
#include "gauge.h"
#include "battle/battle_tcb_pri.h"
#include "system/pm_str.h"
#include "system/msg_ds_icon.h"

#include "battle/graphic/batt_bg_def.h"

#include "wazaeffect/d_we.h"
#include "wazaeffect/d_tool.h"
#include "wazaeffect/ball_effect.h"
#include "wazaeffect/smptm_statuseffect.h"
#include "battle_input.h"

#include "msgdata/msg_fightmsg_dp.h"
#include "msgdata/msg_atkmsg.h"

#include "pokeanime/p_anm_sys.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "battle_snd_def.h"
#include "client_eff.h"

#include "battle/bc_common.h"

#include "poketool/pokegra/otherpoke.naix"
#include "poketool/pokegra/height_o.naix"

//==============================================================================
//	プロトタイプ宣言
//==============================================================================

static	void	HenshinChrSetAct(WAZA_POKE_CHANGE_PARAM *wpcp, int dir_client, int dir_type, int heap_id);

//==============================================================================
//	データ
//==============================================================================
//-----------------------------------------------------------------------------
//		エンカウント座標テーブル
//-----------------------------------------------------------------------------

const	s16	EncountPosTable[][3]={
	{ENCOUNT_X_TYPE_AA,ENCOUNT_Y_TYPE_AA,ENCOUNT_Z_TYPE_AA},
	{ENCOUNT_X_TYPE_BB,ENCOUNT_Y_TYPE_BB,ENCOUNT_Z_TYPE_BB},
	{ENCOUNT_X_TYPE_A,ENCOUNT_Y_TYPE_A,ENCOUNT_Z_TYPE_A},
	{ENCOUNT_X_TYPE_B,ENCOUNT_Y_TYPE_B,ENCOUNT_Z_TYPE_B},
	{ENCOUNT_X_TYPE_C,ENCOUNT_Y_TYPE_C,ENCOUNT_Z_TYPE_C},
	{ENCOUNT_X_TYPE_D,ENCOUNT_Y_TYPE_D,ENCOUNT_Z_TYPE_D},
};

const	s16	AppearPosTable[][2]={
	{APPEAR_X_TYPE_AA,MSG_X_TYPE_AA},
	{APPEAR_X_TYPE_BB,MSG_X_TYPE_BB},
	{APPEAR_X_TYPE_A, MSG_X_TYPE_AA},
	{APPEAR_X_TYPE_B, MSG_X_TYPE_BB},
	{APPEAR_X_TYPE_C, MSG_X_TYPE_AA},
	{APPEAR_X_TYPE_D, MSG_X_TYPE_BB},
};

const	s16	SlideInPosTable[][3]={
	{SLIDEIN_X_TYPE_AA,SLIDEIN_Y_TYPE_AA,SLIDEIN_Z_TYPE_AA},
	{SLIDEIN_X_TYPE_BB,SLIDEIN_Y_TYPE_BB,SLIDEIN_Z_TYPE_BB},
	{SLIDEIN_X_TYPE_AA,SLIDEIN_Y_TYPE_AA,SLIDEIN_Z_TYPE_AA},
	{SLIDEIN_X_TYPE_BB,SLIDEIN_Y_TYPE_BB,SLIDEIN_Z_TYPE_BB},
	{SLIDEIN_X_TYPE_AA,SLIDEIN_Y_TYPE_AA,SLIDEIN_Z_TYPE_AA},
	{SLIDEIN_X_TYPE_BB,SLIDEIN_Y_TYPE_BB,SLIDEIN_Z_TYPE_BB},
};

//============================================================================================
/**
 *	変身でキャラVRAMを書き換える処理
 *
 * @param[in]	wpcp	EXCHR_PARAM構造体
 */
//============================================================================================
void	HenshinChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id)
{
	HenshinChrSetAct(wpcp,wpcp->at_client_no,0,heap_id);
}

//============================================================================================
/**
 *	よこどりでキャラVRAMを書き換える処理
 *
 * @param[in]	wpcp	EXCHR_PARAM構造体
 */
//============================================================================================
void	YokodoriChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id)
{
	HenshinChrSetAct(wpcp,wpcp->df_client_no,1,heap_id);
}

//============================================================================================
/**
 *	変身などでキャラVRAMを書き換える処理
 *
 * @param[in]	wpcp	EXCHR_PARAM構造体
 */
//============================================================================================
static	void	HenshinChrSetAct(WAZA_POKE_CHANGE_PARAM *wpcp, int dir_client, int dir_type, int heap_id)
{
	SOFT_SPRITE_ARC	ssa_src;
	SOFT_SPRITE_ARC	*ssa_dest;
	int				mons_no;
	int				sex;
	int				dir;
	int				col;
	int				form_no;
	u32				rnd;
	int				pos_y;
	s8				height;
	s8				ofs_x;
	s8				ofs_y;
	u8				shadow;

	SoftSpriteSSAPush(wpcp->ss[wpcp->at_client_no]);

	mons_no	=wpcp->mons_no[wpcp->df_client_no];
	sex		=wpcp->sex[wpcp->df_client_no];
	col		=wpcp->rare[wpcp->df_client_no];
	form_no	=wpcp->form_no[wpcp->df_client_no];
	rnd		=wpcp->personal_rnd[wpcp->df_client_no];

	if(dir_type){
		if(wpcp->client_type[dir_client]&CLIENT_ENEMY_FLAG){
			dir=PARA_BACK;
		}
		else{
			dir=PARA_FRONT;
		}
	}
	else{
		if(wpcp->client_type[dir_client]&CLIENT_ENEMY_FLAG){
			dir=PARA_FRONT;
		}
		else{
			dir=PARA_BACK;
		}
	}

	PokeGraArcDataGet(&ssa_src,mons_no,sex,dir,col,form_no,rnd);
	ssa_dest=SoftSpriteArcPointerGetSS(wpcp->ss[wpcp->at_client_no]);

	*ssa_dest=ssa_src;

	SoftSpriteRecoverSS(wpcp->ss[wpcp->at_client_no]);

	Ex_ChangesInto_BattlePokeData(ssa_dest->arc_no,ssa_dest->index_chr,heap_id,wpcp->excp[wpcp->at_client_no]->exchr_buffer,
								  rnd, FALSE, dir, ssa_dest->strike_mons);
	wpcp->excp[wpcp->at_client_no]->arcID=ssa_dest->arc_no;
	wpcp->excp[wpcp->at_client_no]->pal_index=ssa_dest->index_pal;

	ofs_y=wpcp->excp[wpcp->at_client_no]->height=PokeHeightGet(mons_no,sex,dir,form_no,rnd);
	pos_y=CT_PokemonAppearPosGet(wpcp->client_type[wpcp->at_client_no],POS_ID_Y);
	SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_POS_Y,pos_y+ofs_y);

	//ポケモンの影情報更新
	if(dir==PARA_FRONT){
		ArchiveDataLoadOfs(&height,ARC_POKE_YOFS,0,mons_no,1);
		ArchiveDataLoadOfs(&ofs_x,ARC_POKE_SHADOW_OFX,0,mons_no,1);
		ArchiveDataLoadOfs(&shadow,ARC_POKE_SHADOW,0,mons_no,1);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_SIZE,shadow);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_Y,(pos_y+ofs_y)+(SHADOW_OFS-ofs_y));
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_OX,ofs_x);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_OY,SHADOW_OFS-ofs_y);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_HEIGHT,height);
	}
}

//============================================================================================
/**
 *	変身などでキャラVRAMを書き換えたものを戻す処理
 *
 * @param[in]	wpcp	EXCHR_PARAM構造体
 */
//============================================================================================
void	HenshinChrPop(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id)
{
	SOFT_SPRITE_ARC	*ssa;
	int				mons_no;
	int				sex;
	int				dir;
	int				form_no;
	u32				rnd;
	int				pos_y;

	SoftSpriteSSAPop(wpcp->ss[wpcp->at_client_no]);

	ssa=SoftSpriteArcPointerGetSS(wpcp->ss[wpcp->at_client_no]);

	mons_no	=wpcp->mons_no[wpcp->at_client_no];
	sex		=wpcp->sex[wpcp->at_client_no];
	form_no	=wpcp->form_no[wpcp->at_client_no];
	rnd		=wpcp->personal_rnd[wpcp->at_client_no];

	if(wpcp->client_type[wpcp->at_client_no]&CLIENT_ENEMY_FLAG){
		dir=PARA_FRONT;
	}
	else{
		dir=PARA_BACK;
	}

	Ex_ChangesInto_BattlePokeData(ssa->arc_no,ssa->index_chr,heap_id,wpcp->excp[wpcp->at_client_no]->exchr_buffer, rnd, FALSE, dir, ssa->strike_mons);
	wpcp->excp[wpcp->at_client_no]->arcID=ssa->arc_no;
	wpcp->excp[wpcp->at_client_no]->pal_index=ssa->index_pal;

	wpcp->excp[wpcp->at_client_no]->height=PokeHeightGet(mons_no,sex,dir,form_no,rnd);
	pos_y=CT_PokemonAppearPosGet(wpcp->client_type[wpcp->at_client_no],POS_ID_Y)+wpcp->excp[wpcp->at_client_no]->height;
	SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_POS_Y,pos_y);
}

//============================================================================================
/**
 *	みがわりのキャラVRAMを書き換える処理
 *
 * @param[in]	wpcp	EXCHR_PARAM構造体
 */
//============================================================================================
void	MigawariChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id)
{
	SOFT_SPRITE_ARC	ssa_src;
	SOFT_SPRITE_ARC	*ssa_dest;
	int				pos_y;
	int				index;
	u8				height;

	SoftSpriteSSAPush(wpcp->ss[wpcp->at_client_no]);

	ssa_src.arc_no=ARC_OTHER_POKE;
	ssa_src.index_pal=NARC_otherpoke_doll_migawari_NCLR;
	ssa_src.strike_mons=0;
	ssa_src.form_no=0;
	ssa_src.personal_rnd=0;

	if(wpcp->client_type[wpcp->at_client_no]&CLIENT_ENEMY_FLAG){
		ssa_src.index_chr=NARC_otherpoke_doll_migawari_frnt_NCBR;
		index=NARC_height_o_doll_migawari_frnt_bin;
	}
	else{
		ssa_src.index_chr=NARC_otherpoke_doll_migawari_back_NCBR;
		index=NARC_height_o_doll_migawari_back_bin;
	}

	ssa_dest=SoftSpriteArcPointerGetSS(wpcp->ss[wpcp->at_client_no]);

	*ssa_dest=ssa_src;

	SoftSpriteRecoverSS(wpcp->ss[wpcp->at_client_no]);

	ChangesInto_BattlePokeData(ssa_dest->arc_no,ssa_dest->index_chr,heap_id,wpcp->excp[wpcp->at_client_no]->exchr_buffer);
	wpcp->excp[wpcp->at_client_no]->arcID=ssa_src.arc_no;
	wpcp->excp[wpcp->at_client_no]->pal_index=ssa_src.index_pal;

	ArchiveDataLoad(&height,ARC_OTHER_HEIGHT,index);
	wpcp->excp[wpcp->at_client_no]->height=height;
	pos_y=CT_PokemonAppearPosGet(wpcp->client_type[wpcp->at_client_no],POS_ID_Y)+wpcp->excp[wpcp->at_client_no]->height;
	SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_POS_Y,pos_y);
	//ポケモンの影情報更新
	if(wpcp->client_type[wpcp->at_client_no]&CLIENT_ENEMY_FLAG){
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_SIZE,1);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_Y,pos_y+(SHADOW_OFS-height));
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_OX,0);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_OY,SHADOW_OFS-height);
		SoftSpriteParaSet(wpcp->ss[wpcp->at_client_no],SS_PARA_SHADOW_HEIGHT,0);
	}
}

//--------------------------------------------------------------
/**
 *	ポケモンのAppearPosを取得する
 *
 * @param[in]   client_type		取得するClientType
 * @param[in]   pos_id			取得する座標ID（client_tool.hに定義）
 */
//--------------------------------------------------------------
s16		CT_PokemonAppearPosGet(int client_type,int pos_id)
{
	if(pos_id==POS_ID_X){
		return	AppearPosTable[client_type][POS_APPEAR];
	}
	else{
		return EncountPosTable[client_type][pos_id];
	}
}
