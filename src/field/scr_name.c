//============================================================================================
/**
 * @file	scr_name.c
 * @bfief	スクリプトコマンド：名前関連
 * @author	Satoshi Nohara
 * @date	06.06.23
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

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "gflib/strbuf_family.h"	//許可制
#include "sysflag.h"
#include "syswork.h"

#include "..\application\p_status\ribbon.h"

#include "scr_tool.h"
#include "itemtool/item.h"
#include "itemtool/nuts.h"
#include "savedata/misc.h"
#include "msgdata\msg.naix"			//NARC_msg_??_dat

#include "poketool/boxdata.h"

#include "scr_name.h"

#include "field/union_beacon_tool.h"//UnionView_GetTrainerType
#include "comm_union_beacon.h"		//Union_BeaconChange


//============================================================================================
//
//	プロトタイプ宣言
//
//============================================================================================
static STRBUF * PokeNameGetAlloc( u16 id, u32 heap );


//============================================================================================
//
//	コマンド
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * プレイヤー名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPlayerName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);

	WORDSET_RegisterPlayerName( *wordset, idx, SaveData_GetMyStatus(GameSystem_GetSaveData(fsys)) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ライバル名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdRivalName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);

	WORDSET_RegisterRivalName( *wordset, idx, fsys->savedata );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サポート名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSupportName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);

	WORDSET_RegisterSupportName( *wordset, idx, fsys->savedata );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokemonName(VM_MACHINE * core ) 
{
	POKEMON_PARAM * poke;
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 pos					= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), pos);

	//POKEMON_PARAMからPOKEMON_PASO_PARAMに渡しているので注意！(田谷さんに確認済み)
	WORDSET_RegisterPokeMonsName( *wordset, idx, (POKEMON_PASO_PARAM*)poke );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdItemName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 itemno				= VMGetWorkValue(core);

	WORDSET_RegisterItemName( *wordset, idx, itemno );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケット名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPocketName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 pocket				= VMGetWorkValue(core);

	//WORDSET_RegisterItemPocketName( *wordset, idx, pocket );		//アイコンなし
	WORDSET_RegisterItemPocketWithIcon( *wordset, idx, pocket );	//アイコンあり

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アイテム技名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdItemWazaName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 itemno				= VMGetWorkValue(core);
	u16 wazano;

	//技マシンナンバーから技ナンバーを取得
	wazano = GetWazaNoItem(itemno);

	WORDSET_RegisterWazaName( *wordset, idx, wazano );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 技名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 wazano				= VMGetWorkValue(core);

	WORDSET_RegisterWazaName( *wordset, idx, wazano );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 数値を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdNumberName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 number				= VMGetWorkValue(core);

	WORDSET_RegisterNumber( *wordset, idx, number, GetNumKeta(number), 
							NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 数値を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdNumberNameEx(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 number				= VMGetWorkValue(core);
	u8	dtype = VMGetU8(core);
	u8	keta = VMGetU8(core);

	if(dtype == NUMBER_DISPTYPE_LEFT){
		keta = GetNumKeta(number);
	}
	WORDSET_RegisterNumber( *wordset, idx, number, keta, 
							dtype, NUMBER_CODETYPE_DEFAULT );
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ニックネームを指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdNickName(VM_MACHINE * core ) 
{
	POKEMON_PARAM * poke;
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 pos					= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), pos);

	//POKEMON_PARAMからPOKEMON_PASO_PARAMに渡しているので注意！(田谷さんに確認済み)
	WORDSET_RegisterPokeNickName( *wordset, idx, (POKEMON_PASO_PARAM*)poke );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ニックネームを指定バッファに登録(PC上のポケモン)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdNickNamePC(VM_MACHINE * core ) 
{
	POKEMON_PASO_PARAM* ppp;
	FIELDSYS_WORK * fsys	= core->fsys;
	BOX_DATA* boxData = SaveData_GetBoxData( fsys->savedata );
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 num					= VMGetWorkValue(core);
	u32 pos,trayno;

	pos		= num % BOX_MAX_POS;
	trayno	= num / BOX_MAX_POS;

	ppp = BOXDAT_GetPokeDataAddress( boxData, trayno, pos );
	WORDSET_RegisterPokeNickName( *wordset, idx, ppp);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチソフト名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPoketchName(VM_MACHINE * core ) 
{
	POKEMON_PARAM * poke;
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 app_id				= VMGetWorkValue(core);

	WORDSET_RegisterPoketchAppName( *wordset, idx, app_id );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナー種別を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrTypeName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 type				= VMGetWorkValue(core);

	//OS_Printf( "type = %d\n", type );
	WORDSET_RegisterTrTypeName( *wordset, idx, type );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 主人公のトレーナー種別を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMyTrTypeName(VM_MACHINE * core ) 
{
	int msg_id;
	FIELDSYS_WORK * fsys	= core->fsys;
	MYSTATUS* my			= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);

	//見た目番号から、トレーナーの文字列IDを取得
	msg_id = UnionView_GetTrainerInfo( MyStatus_GetMySex(my), 
										MyStatus_GetTrainerView(my), UNIONVIEW_MSGTYPE );

	//WORDSET_RegisterTrTypeName( *wordset, idx, MyStatus_GetTrainerView(my) );
	WORDSET_RegisterTrTypeName( *wordset, idx, msg_id );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * モンスターナンバーからポケモン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPokemonNameExtra(VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 mons				= VMGetWorkValue(core);
	u16 sex					= VMGetU16(core);
	u8 flag					= VMGetU8(core);
	STRBUF* buf				= PokeNameGetAlloc( mons, HEAPID_FIELD );

	//単語セット
	//バッファID
	//文字列
	//性別コード
	//単／複（TRUEで単数）
	//言語コード
	WORDSET_RegisterWord( *wordset, idx, buf, sex, flag, PM_LANG );
	STRBUF_Delete( buf );
	return 0;
}

static STRBUF * PokeNameGetAlloc( u16 id, u32 heap )
{
	MSGDATA_MANAGER* man;
	STRBUF* str;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, heap );
	str = MSGMAN_AllocString( man, id );

	MSGMAN_Delete( man );
	return str;
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdFirstPokemonName(VM_MACHINE * core )
{
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 mons				= SysWork_FirstPokeNoGet( SaveData_GetEventWork(core->fsys->savedata) );
	STRBUF* buf				= PokeNameGetAlloc( mons, HEAPID_FIELD );

	//単語セット
	//バッファID
	//文字列
	//性別コード
	//単／複（TRUEで単数）
	//言語コード
	WORDSET_RegisterWord( *wordset, idx, buf, PM_MALE, TRUE, PM_LANG );
	STRBUF_Delete( buf );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ライバルのポケモン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdRivalPokemonName(VM_MACHINE * core )
{
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 mons				= SysWork_RivalPokeNoGet( SaveData_GetEventWork(core->fsys->savedata) );
	STRBUF* buf				= PokeNameGetAlloc( mons, HEAPID_FIELD );

	//単語セット
	//バッファID
	//文字列
	//性別コード
	//単／複（TRUEで単数）
	//言語コード
	WORDSET_RegisterWord( *wordset, idx, buf, PM_MALE, TRUE, PM_LANG );
	STRBUF_Delete( buf );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サポートのポケモン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSupportPokemonName(VM_MACHINE * core )
{
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 mons				= SysWork_SupportPokeNoGet(SaveData_GetEventWork(core->fsys->savedata));
	STRBUF* buf				= PokeNameGetAlloc( mons, HEAPID_FIELD );

	//単語セット
	//バッファID
	//文字列
	//性別コード
	//単／複（TRUEで単数）
	//言語コード
	WORDSET_RegisterWord( *wordset, idx, buf, PM_MALE, TRUE, PM_LANG );
	STRBUF_Delete( buf );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * グッズ名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGoodsName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 itemno				= VMGetWorkValue(core);

	WORDSET_RegisterUGGoodsName( *wordset, idx , itemno);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トラップ名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrapName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 trapno				= VMGetWorkValue(core);

	WORDSET_RegisterUGTrapName( *wordset, idx , trapno);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * タマ名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTamaName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 tamano				= VMGetWorkValue(core);

	WORDSET_RegisterUGItemName( *wordset, idx , tamano);
	return 0;
}




//--------------------------------------------------------------------------------------------
/**
 * ゾーン名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdZoneName( VM_MACHINE * core )
{
	STRBUF* strbuf		= STRBUF_Create(BUFLEN_PLACE_NAME, HEAPID_FIELD);
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx				= VMGetU8(core);
	u16 zone_id			= VMGetWorkValue(core);

	//ゾーンIDから地名を取得
	PNC_GetPlaceNameFromZoneID( zone_id, HEAPID_FIELD, strbuf );

	//単語セット
	//バッファID
	//文字列
	//性別コード
	//単／複（TRUEで単数）
	//言語コード
	WORDSET_RegisterWord( *wordset, idx, strbuf, PM_MALE, TRUE, PM_LANG );
	STRBUF_Delete(strbuf);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	きのみの名前をwordsetに格納する
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdNutsName(VM_MACHINE * core)
{
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx = VMGetU8(core);				//入力１：埋め込みバッファ指定
	u16 nuts_id = VMGetWorkValue(core);	//入力２：きのみID
	u16 count = VMGetWorkValue(core);	//入力３：きのみの数
	STRBUF * buf = NutsNameGetAlloc(nuts_id - NUTS_START_ITEMNUM /* + 1 */, HEAPID_EVENT);
	//本当はWORDSET_RegisterNutsNameがあるといいね。
//void WORDSET_RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* word, u32 sex, BOOL singular_flag, u32 lang )
	WORDSET_RegisterWord(*wordset, idx, buf, PM_MALE, (count < 2? TRUE:FALSE), PM_LANG);
	STRBUF_Delete(buf);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	性格の名前をwordsetに格納する
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeikakuName(VM_MACHINE * core)
{
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx				= VMGetU8(core);
	u16 seikaku			= VMGetWorkValue(core);

	WORDSET_RegisterSeikaku( *wordset, idx, seikaku );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アクセサリー名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAcceName(VM_MACHINE * core ) 
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 acceno				= VMGetWorkValue(core);

	WORDSET_RegisterAccessoryName( *wordset, idx, acceno );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * r224石碑名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMonumantName(VM_MACHINE * core ) 
{
	STRBUF*	word;
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);

	word = STRBUF_Create(10+EOM_SIZE,HEAPID_WORLD);
	STRBUF_SetStringCode( word,
		MISC_GetMonumentName(SaveData_GetMisc(core->fsys->savedata)));

	WORDSET_RegisterWord( *wordset, idx, word, PM_MALE, FALSE, CasetteLanguage);

	STRBUF_Delete(word);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　手持ちのわざ名をバッファへ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTemotiWazaName( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * poke;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx		= VMGetU8(core);
	u16 t_num = VMGetWorkValue(core);
	u16 w_num = VMGetWorkValue(core);
	u16 wazano;

	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), t_num);

	wazano = PokeParaGet( poke, ID_PARA_waza1+w_num, NULL );

	WORDSET_RegisterWazaName( *wordset, idx, wazano );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	「リボン」名をバッファへセット
 */
//-----------------------------------------------------------------------------
BOOL EvCmdRibbonName(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx		= VMGetU8(core);
	u16	rno		= VMGetWorkValue(core);
	u16 mes_rno;

	mes_rno = RIBBON_DataGet(rno, RIBBON_PARA_NAME);

	WORDSET_RegisterRibbonName( *wordset, idx, mes_rno );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * シール名を指定バッファに登録
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSealName(VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 idx					= VMGetU8(core);
	u16 sealno				= VMGetWorkValue(core);

	sealno -= 1;			//1origin->0rigin
	WORDSET_RegisterSealName( *wordset, idx , sealno);
	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
