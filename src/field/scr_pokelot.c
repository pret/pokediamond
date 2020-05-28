//============================================================================================
/**
 * @file	scr_pokelot.c
 * @bfief	ポケモンクジ			※非常中領域に移動すると動作しません
 * @author	Tomomichi Ohta
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

#include "scr_tool.h"
#include "poketool/boxdata.h"

#include "scr_pokelot.h"
#include "poketool/boxdata.h"

//===========================================
// マクロ
//===========================================
#define POKELOT_MAXNUMBER  (65535)  // 当選ナンバー最大値

//===========================================
// プロトタイプ
//===========================================
static u8 check_hit_keta(u16 val1, u16 val2);


//============================================================================================
//						クジ関連
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * クジのあたり番号取得
 * @brief   クジのあたり番号取得
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
#define POKELOT_MAXNUMBER  (65535)  /* 当選ナンバー最大値*/

BOOL EvCmdGetKujiAtariNum(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk			= VMGetWork( core );
	u32 value;

	value = SysWork_pokelot_value_get(ev);
	*ret_wk = (u16)(value % (POKELOT_MAXNUMBER+1));

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * クジのあたりチェック
 * @brief   クジのあたりチェック
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKujiAtariChk(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	POKEMON_PARAM * poke;
	POKEMON_PASO_PARAM* ppp;
	BOX_DATA* boxData = SaveData_GetBoxData( fsys->savedata );
	u16* ret_wk1			= VMGetWork( core );
	u16* ret_wk2			= VMGetWork( core );
	u16* ret_wk3			= VMGetWork( core );
	u16 num			= VMGetWorkValue( core );
	u16 max,i,j;
	u16 t_keta,t_no;
	u16 pc_keta,pc_no;
	u32 id;
	u8  keta;
	u32 pos, trayno, monsno;

	max = PokeParty_GetPokeCount(SaveData_GetTemotiPokemon(fsys->savedata));

	for(t_keta=0,t_no=0,i=0;i<max;i++){
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), i);

		//モンスター番号取得(0以外ならタマゴ）
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) == 0 ){

			id = (PokeParaGet( poke, ID_PARA_id_no, NULL ) & 0xffff);

			keta = check_hit_keta(num, id);	//桁数取得
			if((keta > 0)&&(t_keta < keta)) {		//初回or上回ったとき
				t_keta = keta;
				t_no = i;
			}
		}
	}


	for( pc_keta = 0, pc_no = 0,trayno = 0; trayno < BOX_MAX_TRAY; trayno++ ) {
		for( pos = 0; pos < BOX_MAX_POS; pos++ ){
			ppp = BOXDAT_GetPokeDataAddress( boxData, trayno, pos );
			monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
			if( monsno ){
				if( PokePasoParaGet( ppp, ID_PARA_tamago_flag, NULL ) == 0 ){

					id = (PokePasoParaGet( ppp, ID_PARA_id_no, NULL ) & 0xffff);

					keta = check_hit_keta(num, id);	//桁数取得
					if((keta > 0)&&(pc_keta < keta)) {		//初回or上回ったとき
						pc_keta = keta;
						pc_no = trayno * BOX_MAX_POS + pos;
					}
				}
			}
		}
	}

	if((t_keta == 0)&&(pc_keta==0)){		//どちらも外れ
		*ret_wk1 = 0;
		*ret_wk2 = 0;
		*ret_wk3 = 0;
	}else{
		if(t_keta >= pc_keta){		//手持ちのほうが上を当たっている(or同じ）
			*ret_wk1 = t_no;
			*ret_wk2 = t_keta;
			*ret_wk3 = 0;
		}else{						//PCのほうが上
			*ret_wk1 = pc_no;
			*ret_wk2 = pc_keta;
			*ret_wk3 = 1;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * クジのあたり番号初期化
 * @brief   クジのあたり番号初期化
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKujiAtariInit(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	SysWorkInitPokeLot(ev);

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

#if 0
/*==============================================================
==  AnswerWork に入っているナンバーで当選チェック
==  【結果】
==    ScriptParameter0  ... 0(はずれ）～4（特等）
==  ※ScriptParameter1  ... もらえるアイテムナンバー
==  ※ScriptParameter2  ... 当選ポケモンが（0:てもち 1:ボックス）
==  ※StrTempBuffer0   ... 当選ポケモン名
==
==  ※当選しなかった場合、これらの値は内容が保証されません
==============================================================*/
void CheckPokeLotNumber(void)
{
	u32 id;
	u16 monsbox, monspos, i, j;
	u8  keta;

	ScriptParameter0 = 0;
	monsbox = monspos = 0;

	// 手持ちチェック
	for(i = 0; i < TEMOTI_POKEMAX; i++)
	{
		if(PokeParaGet(PokeParaMine+i, ID_monsno) != 0)
		{
			if(PokeParaGet(PokeParaMine+i, ID_tamago_flag) == 0)
			{
				id = (PokeParaGet(PokeParaMine + i, ID_id_no) & 0xffff);
				keta = check_hit_keta(AnswerWork, id);
				if(keta > ScriptParameter0 && keta > 1)
				{
					ScriptParameter0 = keta - 1;
					monsbox = BOX_KAZU;
					monspos = i;
				}
			}
		}else{
			break;
		}
	}

	// ボックスチェック
	for(i = 0; i < BOX_KAZU; i++)
	{
		for(j = 0; j < BOX_PM_KAZU; j++)
		{
			if(PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_monsno) != 0)
			{
				if(PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_tamago_flag) == 0)
				{
					id = (PokePasoParaGet(&(BoxData.PPPBox[i][j]), ID_id_no) & 0xffff);
					keta = check_hit_keta(AnswerWork, id);
					if(keta > ScriptParameter0 && keta > 1)
					{
						ScriptParameter0 = keta - 1;
						monsbox = i;
						monspos = j;
					}
				}
			}
		}
	}

	// 当選していた
	if(ScriptParameter0)
	{
		ScriptParameter1 = PokeLotPrizeTable[ScriptParameter0-1];
		if(monsbox == BOX_KAZU){
			ScriptParameter2 = 0;
			PokeParaGet(PokeParaMine + monspos, ID_nickname, StrTempBuffer0);
		}else{
			ScriptParameter2 = 1;
			PokePasoParaGet(&(BoxData.PPPBox[monsbox][monspos]), ID_nickname, StrTempBuffer0);
		}
		NickNameCutOff(StrTempBuffer0);
	}
}
#endif


/*====================================================*/
/*  一致桁数を計算                                    */
/*  val1, val2   比較する数値                         */
/*  return:  一致桁数（0～5）                         */
/*====================================================*/
static u16 V1 = 0, V2 = 0;

static u8 check_hit_keta(u16 val1, u16 val2)
{
	u8  i, hit;

	hit = 0;

	for(i = 0; i < 5; i++)
	{
		V1 = val1 % 10;
		V2 = val2 % 10;
		if((val1%10) != (val2%10)){ break; }
		val1 /= 10;
		val2 /= 10;
		hit++;
	}

	return hit;
}

/*====================================================*/
/*====================================================*/
