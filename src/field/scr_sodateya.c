//============================================================================================
/**
 * @file	scr_sodateya.c
 * @bfief	スクリプトコマンド：そだてや関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "savedata/sodateyadata.h"
#include "sodateya.h"

#include "scr_sodateya.h"

//============================================================================================
//
//	コマンド
//
//============================================================================================


//============================================================================================
//
//	育て屋関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * そだてや　名前の取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaName( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );

	SodateyaNameSet(SaveData_GetSodateyaWork(sv),*wordset);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * そだてや　じいさんの状態取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaZiisan( VM_MACHINE * core )
{
	u16 * work;
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	work = VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	*work = SodateyaZiisannCheck(sodateya);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *			そだてやにいるタマゴを消去
 * @brief   そだてや用のワークから、タマゴがいる情報をクリアする
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdDelSodateyaEgg( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	DelSodateyaTamagoSub(sodateya);

	return 0;
}


BOOL EvCmdGetSodateyaEgg( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	POKEPARTY     *temoti   = SaveData_GetTemotiPokemon(fsys->savedata);
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );

	PokeTamagoDel(sodateya, temoti, my );

//作成中 060302 by tomo
//xxxxx

	return 0;
}


BOOL EvCmdHikitoriPoke( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SODATEYA_WORK *sodateya;
	POKEPARTY * temoti;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	SAVEDATA * sv = fsys->savedata;
	u16 *ret_wk		= VMGetWork(core);
	u8 no		= VMGetWorkValue(core);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	temoti = SaveData_GetTemotiPokemon(fsys->savedata);

	*ret_wk = PokeHikitoriSub(temoti,*wordset,sodateya,no);

	return 0;
}

// =================================================================
/**
 * @brief 引き取り料金取得
 * @param  none
 * @retval  料金を返す（引数として、ワークに番号をセットする必要があります）
 * @retval  文字バッファ０へ料金セット、料金をワークへ返す
 */
// =================================================================
BOOL EvCmdHikitoriRyoukin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SODATEYA_WORK *sodateya;
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	SAVEDATA * sv = fsys->savedata;
	u16 * work  = VMGetWork(core);
	u8 no		= VMGetWorkValue(core);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*work = PokeHikitoriRyoukinSub(sodateya,no,*wordset);
	return 0;
}

BOOL EvCmdSodatePokeLevelStr( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 *ret_wk		= VMGetWork( core );
	u16 no			= VMGetWorkValue( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	*ret_wk = SodatePokeLevelSet(sodateya,no,*wordset );

	return 0;
}

BOOL EvCmdMsgAzukeSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEPARTY * temoti;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 wk_no			= VMGetU16( core );		//※現在は０固定なので使用せず
	u16 no				= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	*ret_wk = SodateyaAzukeName(temoti,no,*wordset );

	return 0;
}

BOOL EvCmdSetSodateyaPoke( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	POKEPARTY * temoti;
	u8 no				= VMGetWorkValue(core);

	temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));
	PokeSodateSet(temoti,no,sodateya,sv);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * そだてやスクリプト：引き取りLIST用ポケモン名をセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdHikitoriListNameSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	u8	buf_id		= VMGetWorkValue( core );
	u8	buf2_id		= VMGetWorkValue( core );
	u8	buf3_id		= VMGetWorkValue( core );
	u8	no			= VMGetWorkValue( core );

	SodateyaListNameSet(SaveData_GetSodateyaWork(sv),buf_id,buf2_id,buf3_id,no,*wordset);
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * そだてやスクリプト：預けている2体の相性ゲット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaAishou( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	u16* ret_wk	= VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*ret_wk = SodateyaGetAffinity( sodateya );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * そだてやスクリプト：タマゴがうまれているか（１：いる、０：いない）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetSodateyaTamagoCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	SODATEYA_WORK *sodateya;
	u16* ret_wk	= VMGetWork( core );

	sodateya = (SODATEYA_WORK *)(SaveData_Get(sv,GMDATA_ID_SODATEYA));

	*ret_wk = SodateyaWork_GetEggFlag(sodateya);

	return 0;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
/*未使用マンド*/


//060625 使用しません
BOOL EvCmdHikitoriList( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	return 0;
}

//060625 使用しません
BOOL EvCmdMsgSodateyaAishou( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	return 0;
}

//060625 使用しません
BOOL EvCmdMsgExpandBuf( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	return 0;
}

//060625 使用しません
BOOL EvCmdSodateyaPokeList( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
