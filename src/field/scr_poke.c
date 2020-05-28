//============================================================================================
/**
 * @file	scr_poke.c
 * @bfief	スクリプトコマンド：ポケモン操作関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"

#include <nitro/code16.h> 
#include "system/pm_str.h"
#include "system\msgdata.h"			//MSGMAN_GetString
#include "system/brightness.h"		//ChangeBrightnessRequest
#include "system\wordset.h"			//WordSet_RegistPlayerName
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/get_text.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_data.h"
#include "system/wipe.h"
#include "system/placename.h"

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "poketool/boxdata.h"

#include "..\application\p_status\ribbon.h"

#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"
#include "ev_time.h"

#include "battle/attr_def.h"
#include "zonedata.h"

#include "d_print.h"
#include "sodateya.h"

#include "ev_pokemon.h"				//EvPoke_Add
#include "poketool/poke_memo.h"

#include "scr_poke.h"
#include "msgdata/msg_place_name_tokusyu.h"
#include "itemtool/itemsym.h"
#include "itemtool/itemequip.h"
#include "itemtool/item.h"


//============================================================================================
//
//	コマンド
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * ポケモンを手持ちに加える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddPokemon(VM_MACHINE * core)
{
	int place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);
	int ground_id = GROUND_ID_ALL;
	POKEPARTY * temoti;
	FIELDSYS_WORK * fsys	= core->fsys;
	u16 monsno				= VMGetWorkValue(core);
	u16 lv					= VMGetWorkValue(core);
	u16 itemno				= VMGetWorkValue(core);
	u16* ret_wk				= VMGetWork( core );

	//06.05.19
	//AGBのポケモン追加は、手持ちがいっぱいの時は、ボックスに転送されるようになっていて、
	//どちらに追加したか(追加できなかった)が戻り値になっていた

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	*ret_wk = EvPoke_Add(HEAPID_WORLD, fsys->savedata, monsno, lv, itemno, place_id, ground_id);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	手持ちの位置ナンバーから、ポケモン番号へ変換
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiMonsNo(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* in_wk				= VMGetWork( core );
	u16* out_wk				= VMGetWork( core );

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), *in_wk);

	//モンスター番号取得
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
		*out_wk = PokeParaGet(poke,ID_PARA_monsno,NULL);
	}else{	//タマゴ
		*out_wk = 0;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	手持ちポケモンのご主人様チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMonsOwnChk(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	MYSTATUS* my		= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16* in_wk				= VMGetWork( core );
	u16* out_wk				= VMGetWork( core );
	u16 poke_id,my_id;

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), *in_wk);

	//ポケモンのID
	poke_id = PokeParaGet( poke, ID_PARA_id_no, NULL );

	my_id = MyStatus_GetID(my);

	if(poke_id == my_id){	//一致
		*out_wk = 0;
	}else{					//不一致
		*out_wk = 1;
	}

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * タマゴを手持ちに加える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddTamago(VM_MACHINE * core)
{
	int index;
	u8	max;
	BOOL result;
	POKEPARTY * temoti;
	POKEMON_PARAM* poke_param;
	FIELDSYS_WORK * fsys	= core->fsys;
	MYSTATUS	  * my      = SaveData_GetMyStatus(fsys->savedata);
	u16 monsno				= VMGetWorkValue(core);
	u16 msgid				= VMGetWorkValue(core);

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);

	max = PokeParty_GetPokeCount(temoti);
	if(max<6){		//※念のため。ポケモンが最大数のときに呼ばれても飛ばないように
		poke_param = PokemonParam_AllocWork(HEAPID_WORLD);
		PokeParaInit(poke_param);

		index = PlaceName_IndexToParamNumber( PLACENAME_TYPE_GAME_EVENT, msgid );
		OS_Printf( "msgid = %d\n", msgid );
		OS_Printf( "index = %d\n", index );
		PokemonTamagoSet_forEvent(poke_param,monsno,1, my, TRMEMO_SODATEYA_PLACESET, index);

		result = PokeParty_Add(temoti, poke_param);
		sys_FreeMemoryEz(poke_param);
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンの技を置き換える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChgPokeWaza( VM_MACHINE * core )
{
	u16 poke_pos, waza_pos, waza_no;
	poke_pos = VMGetWorkValue(core);
	waza_pos = VMGetWorkValue(core);
	waza_no = VMGetWorkValue(core);
	EvPoke_ChangeWaza(SaveData_GetTemotiPokemon(core->fsys->savedata),
			poke_pos, waza_pos, waza_no);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンが指定された技を覚えているかチェック（１体）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeWaza( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 waza	= VMGetWorkValue(core);
	u16 tno		= VMGetWorkValue(core);
	u16 my_waza;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk = 0;
	//たまごチェック
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		return 0;
	}

	//ワザリストからチェック
	if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza) ){
		*ret_wk = 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンが指定された技を覚えているかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeWazaGroup( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 waza	= VMGetWorkValue(core);
	u16 my_waza;
	u8	i,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for( i=0, *ret_wk=6 ; i<max; i++ ){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//たまごチェック
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
			continue;
		}

		//ワザリストからチェック
		if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza) ||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza) ){
			*ret_wk = i;		//持っているポケモンのリスト上の並びを返す
			break;
		}

	}

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンが毒で死んだかどうかの認証
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdApprovePoisonDead(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16 num;
	u16 * ret_wk;
	ret_wk = VMGetWork(core);
	num = VMGetWorkValue(core);
	pp = PokeParty_GetMemberPointer(SaveData_GetTemotiPokemon(core->fsys->savedata), num);
	*ret_wk = EvPoke_ApprovePoisonDead(pp);
	OS_Printf("POS:%d RESULT:%d\n",num, *ret_wk);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	手持ちポケモンのレベルチェック（引数の数)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeLevelChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 level			= VMGetWorkValue( core );
	u8 i,max,ct;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	*ret_wk = 0;
	for(i=0,ct=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//モンスター番号取得(0以外ならタマゴ）
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){

			//引数以下のポケモンがいるかチェック
			if( PokeParaGet( poke, ID_PARA_level, NULL ) <= level ){
				ct++;
			}

		}
	}

	*ret_wk = ct;

	return 0;

}

//--------------------------------------------------------------------------------------------
/**
 *	手持ちポケモンのレベル取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeLevelGet(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 tno			= VMGetWorkValue( core );

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk = 0;
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
		*ret_wk = PokeParaGet( poke, ID_PARA_level, NULL );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 性格ゲット
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeSeikaku(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);
	u8 max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	if(tno >= max) {		//持っているポケモン以上の番号のとき
		*ret_wk = 0;
		return 0;
	}

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//タマゴチェック
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		*ret_wk = 0;
		return 0;
	}

	//性格取得
	*ret_wk = PokeSeikakuGet(poke);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 特定の性格のポケモンがいるかをチェック
 * 0xff:いない 0～5:手持ち番号
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkPokeSeikakuAll(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 seikaku_no	= VMGetWorkValue(core);
	u8 max,i;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	*ret_wk = 0xff;
	for(i=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//タマゴでないときのみチェック
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//性格チェック
			if(PokeSeikakuGet(poke) == seikaku_no){
				*ret_wk = i;
				break;
			}
		}

	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * なつき度の取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk			= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//ポケモンのなつき度取得
	*ret_wk = PokeParaGet( poke, ID_PARA_friend, NULL );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * なつき度を増やす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 add_value			= VMGetWorkValue( core );
	u16 tno	= VMGetWorkValue(core);
	u16 value;
	u32 place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//ポケモンのなつき度取得
	value = PokeParaGet( poke, ID_PARA_friend, NULL );

#if 0
	value += add_value;
	if(value > 255) {			//なつき度Max=255
		value = 255;
	}
#else
	if( add_value > 0 ){
		// 装備効果
		if( ItemParamGet(PokeParaGet(poke,ID_PARA_item,NULL),ITEM_PRM_EQUIP,HEAPID_WORLD) == SOUBI_NATUKIDOUP ){
			add_value = add_value * 150 / 100;
		}
		// 捕獲ボール
		if( PokeParaGet( poke, ID_PARA_get_ball, NULL ) == ITEM_GOOZYASUBOORU ){
			add_value++;
		}
		// 捕獲場所
		if( PokeParaGet( poke, ID_PARA_get_place, NULL ) == place_id ){
			add_value++;
		}
	}

	value += add_value;
	if( value > FRIEND_MAX ){
		value = FRIEND_MAX;
	}
#endif

	//ポケモンのなつき度セット
	PokeParaPut( poke, ID_PARA_friend, &value );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * なつき度を減らす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubNatsuki( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 sub_value			= VMGetWorkValue( core );
	u16 tno	= VMGetWorkValue(core);
	u16 value;

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	//ポケモンのなつき度取得
	value = PokeParaGet( poke, ID_PARA_friend, NULL );

	if(sub_value > value) {
		value = 0;
	}else{
		value -= sub_value;
	}

	//ポケモンのなつき度セット
	PokeParaPut( poke, ID_PARA_friend, &value );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンのコンテストステータス取得(かっこよさ、かわいさ等)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeContestStatusGet( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	u16 pos		= VMGetWorkValue( core );
	u16 con_type = VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	*ret_wk = PokeParaGet(poke, ID_PARA_style + con_type, NULL);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	先頭のポケモンを返す（タマゴを抜かした）
 */
//-----------------------------------------------------------------------------
BOOL EvCmdFrontPokemon(VM_MACHINE * core)
{
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = GetFrontPokemon(core->fsys->savedata);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	手持ちポケモンのタイプを取得
 */
//-----------------------------------------------------------------------------
BOOL EvCmdTemotiPokeType(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk1				= VMGetWork( core );
	u16* ret_wk2				= VMGetWork( core );
	u16 tno		= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	*ret_wk1 = PokeParaGet( poke, ID_PARA_type1, NULL );
	*ret_wk2 = PokeParaGet( poke, ID_PARA_type2, NULL );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン数取得
 * @brief   手持ちのポケモン数を調べて返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount( VM_MACHINE * core )
{
	int max;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	//今後、タマゴ等によって出力を分けるかも

	*ret_wk = max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン数取得(タマゴを除く）
 * @brief   手持ちのポケモン数を調べて返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount2( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//モンスター番号取得(0以外ならタマゴじゃない）
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			poke_max++;
		}
	}

	*ret_wk = poke_max;

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * ポケモン数取得(タマゴと瀕死を除く）
 * @brief   手持ちのポケモン数を調べて返す(戦闘可能なポケモン数)
 *	no = 無視する手持ち番号(6:なし、0～5)
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount3( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	u16 no			= VMGetWorkValue( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		if(i==no) continue;
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);
		//モンスター番号取得(0以外ならタマゴじゃない）
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//瀕死除外チェック(0==瀕死)
			if( PokeParaGet( poke,ID_PARA_hp , NULL ) != 0 ){
				poke_max++;
			}
		}
	}

	*ret_wk = poke_max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン総数（手持ち＋ボックス）取得(タマゴと、手持ちの瀕死を除く）
 *
 * ※現在使用されていません
 * 
 * @brief   手持ちのポケモン数を調べて返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPokeCount4( VM_MACHINE * core )
{
	int max,poke_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	BOX_DATA* boxDat = SaveData_GetBoxData( fsys->savedata );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,poke_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//モンスター番号取得(0以外ならタマゴじゃない）
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//瀕死除外チェック(0==瀕死)
			if( PokeParaGet( poke,ID_PARA_hp , NULL ) != 0 ){
				poke_max++;
			}
		}
	}

	poke_max += BOXDAT_GetPokeExistCount2Total( boxDat );

	*ret_wk = poke_max;

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * タマゴ数取得
 * @brief   手持ちのポケモン数を調べて返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetTamagoCount( VM_MACHINE * core )
{
	int max,tamago_max,i;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(i=0,tamago_max=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//タマゴ数取得
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL )){
//※場合によっては、ダメタマゴチェックをいれるかも（仕様により）
			tamago_max++;
		}
	}

	*ret_wk = tamago_max;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンのポケルスへの感染をチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdChkTemotiPokerus( VM_MACHINE * core )
{
	u16 i, max;
	u16 * wk;
	u32 pokerus;
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;

	wk = VMGetWork( core );


	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	//ポケルスを持っているかcheck
	*wk = 0;
	for(i=0;i<max;i++){
		//ポケモンへのポインタ取得
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		pokerus = PokeParaGet(poke, ID_PARA_pokerus, NULL);

		if(pokerus!=0){
			*wk = 1;
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 手持ちポケモンの性別取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeSexGet( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	u16 pos		= VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	*ret_wk = PokeParaGet(poke, ID_PARA_sex, NULL);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	技忘れ関連：持っている技をカウント
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	0
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaCount( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 t_no	= VMGetWorkValue( core );
	u8 i;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_no);

	//たまごチェック
	if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
		*ret_wk =0;
		return 0;
	}

	i=0;
	if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza2, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza3, NULL ) != 0)){
		i++;
	}

	if( (PokeParaGet( poke, ID_PARA_waza4, NULL ) != 0)){
		i++;
	}

	*ret_wk = i;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	技忘れ関連：ワザを消去
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	0
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaDel( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u32	buf;
	u8 i;

	u16 t_num = VMGetWorkValue(core);
	u16 w_num = VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_num);

	PokeParaWazaDelPos(poke,w_num);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　手持ちのわざ番号を、わざ番号へ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiWazaNo( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;

	u16* ret_wk	= VMGetWork( core );
	u16 t_num = VMGetWorkValue(core);
	u16 w_num = VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_num);

	*ret_wk = PokeParaGet( poke, ID_PARA_waza1+w_num, NULL );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	メールを持っているかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeMailChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16* ret_wk	= VMGetWork( core );
	u16 tno	= VMGetWorkValue(core);

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);
	*ret_wk = PokeParaGet(poke, ID_PARA_item, NULL);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	持っているメールを削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokeMailDel(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	u16 tno	= VMGetWorkValue(core);
	u16 itemno;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), tno);

	itemno = 0;	//持っていない状態へ
	PokeParaPut( poke, ID_PARA_item, &itemno );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　手持ちに特定のポケモンがいるかをチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiPokeChk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16		num = VMGetWorkValue(core);
	u8 i,max;
	u16 poke_no;

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	max = PokeParty_GetPokeCount(temoti);

	*ret_wk = FALSE;
	for(i=0;i<max;i++){
		//ポケモンへのポインタ取得
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//タマゴは除外
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){
			//ポケモンナンバー取得
			poke_no = PokeParaGet( poke, ID_PARA_monsno, NULL );

			if(num == poke_no){		//一致
				*ret_wk = TRUE;
				break;
			}
		}

	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	「リボン」の取得数（１ポケモン）
 *	
 */
//-----------------------------------------------------------------------------

BOOL EvCmdChkRibbonCount(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk	= VMGetWork( core );
	u16		tno	= VMGetWorkValue(core);
	u16 i,cnt;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	for(i=0,cnt=0;i<RIBBON_MAX;i++){
		if(PokeParaGet(pp, RIBBON_DataGet(i, RIBBON_PARA_POKEPARA ), NULL) != 0){
			cnt++;
		}
	}

	*ret_wk = cnt;

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	「リボン」の取得数（全手持ちポケモン合計の種類）
 *	
 */
//-----------------------------------------------------------------------------

BOOL EvCmdChkRibbonCountAll(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16 i,j,cnt,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(core->fsys->savedata));

	//poke party取得
	temoti = SaveData_GetTemotiPokemon(core->fsys->savedata);

	for(i=0,cnt=0;i<RIBBON_MAX;i++){
		for(j=0;j<max;j++){
			pp = PokeParty_GetMemberPointer( temoti, j);
			//タマゴチェック
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){
				break;
			}

			if(PokeParaGet(pp, RIBBON_DataGet(i, RIBBON_PARA_POKEPARA ), NULL) != 0){
				cnt++;
				break;
			}

		}
	}

	*ret_wk = cnt;

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	「リボン」をもっているか
 *	0:なし　1:あり
 */
//-----------------------------------------------------------------------------
BOOL EvCmdChkRibbon(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk	= VMGetWork( core );
	u16		tno	= VMGetWorkValue(core);
	u16		rno	= VMGetWorkValue(core);
	u8	flag = 1;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	*ret_wk = PokeParaGet(pp, RIBBON_DataGet(rno, RIBBON_PARA_POKEPARA ), NULL);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	「リボン」をセット
 */
//-----------------------------------------------------------------------------
BOOL EvCmdSetRibbon(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16		rno	= VMGetWorkValue(core);
	u8	flag = 1;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	PokeParaPut(pp, RIBBON_DataGet(rno, RIBBON_PARA_POKEPARA ), &flag);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *　ダメタマゴチェック全体版(手持ちにいる:TRUE,いない:FALSE)
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDameTamagoChkAll(VM_MACHINE * core)
{

	POKEMON_PARAM * pp;
	POKEPARTY * temoti;
	u16* ret_wk	= VMGetWork( core );
	u16 i,j,max;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(core->fsys->savedata));

	//poke party取得
	temoti = SaveData_GetTemotiPokemon(core->fsys->savedata);

	//仕様上、ダメタマゴ　＝　タマゴ＆ダメタマゴフラグが立っている
	for(i=0;i<RIBBON_MAX;i++){
		for(j=0;j<max;j++){
			pp = PokeParty_GetMemberPointer( temoti, j);
			if( PokeParaGet( pp, ID_PARA_tamago_flag, NULL ) != 0 ){			//タマゴチェック
				if( PokeParaGet( pp, ID_PARA_fusei_tamago_flag, NULL ) != 0 ){	//ダメタマゴチェック
					*ret_wk = TRUE;
					return 0;

				}
			}
		}
	}

	*ret_wk = FALSE;

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//未使用
BOOL EvCmdGetTemotiPokeNum( VM_MACHINE * core )
{

	return 0;
}

//============================================================================================
//============================================================================================
