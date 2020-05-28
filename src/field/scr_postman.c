//============================================================================================
/**
 * @file	scr_postman.c
 * @brief	ふしぎ配達員スクリプト＆処理
 * @author	tamada GAME FREAK inc. -> k.ohno
 * @date	2006.05.26
 */
//============================================================================================


#include "common.h"
#include "script.h"
#include "fieldsys.h"

#include "scrcmd_def.h"
#include "scr_postman.h"
#include "strbuf_family.h"

#include "poketool/pokeparty.h"
#include "ev_pokemon.h"
#include "system/wordset.h"
#include "system/placename.h"
#include "msgdata/msg_place_name_haihu.h"

#include "battle/attr_def.h"
#include "poketool/monsno.h"
#include "poketool/poke_memo.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_haitatu.h"
#include "msgdata/msg_bc_seal_name.h"

#include "savedata/fushigi_data.h"
#include "savedata/regulation.h"
#include "savedata/zukanwork.h"
#include "savedata/undergrounddata.h"
#include "savedata/custom_ball.h"
#include "savedata/imageclip_data.h"
#include "savedata/sp_ribbon.h"
#include "savedata/get_poke.h"

#include "system/debug_flag.h"
#include "itemtool/itemsym.h"

#include "../application/p_status/ribbon.h"

#include "syswork.h"

//============================================================================================
//============================================================================================

//-----------------------------------------------------------------------------
/**
 * @brief	メッセージ生成に必要なワーク
 */
//-----------------------------------------------------------------------------
typedef struct {
	FIELDSYS_WORK * fsys;
	WORDSET * wordset;
	void * slot;
}MSG_WORK;

//-----------------------------------------------------------------------------
///受け取りチェック関数の型定義
//-----------------------------------------------------------------------------
typedef BOOL (*RECEIVE_CHECK_FUNC)(FIELDSYS_WORK * fsys, void *);

//-----------------------------------------------------------------------------
///受け取り処理関数の型定義
//-----------------------------------------------------------------------------
typedef void (*RECEIVE_FUNC)(FIELDSYS_WORK * , void *);

//-----------------------------------------------------------------------------
///受け取りOKメッセージ生成関数の型定義
//-----------------------------------------------------------------------------
typedef void (*GET_OK_MSG)(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id);

//-----------------------------------------------------------------------------
///受け取りNGメッセージ生成関数の型定義
//-----------------------------------------------------------------------------
typedef void (*GET_NG_MSG)(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id);

//-----------------------------------------------------------------------------
/**
 * @brief	ふしぎなおくりもの種類ごとの配達員の振る舞い関数まとめ
 */
//-----------------------------------------------------------------------------
typedef struct {
	RECEIVE_CHECK_FUNC	check_func;		///<受け取りチェック関数
	RECEIVE_FUNC		receive_func;	///<受け取り処理関数
	GET_OK_MSG			ok_msg_func;	///<受け取りOKメッセージ生成関数
	GET_NG_MSG			ng_msg_func;	///<受け取りNGメッセージ生成関数
}MP_ACTION;


static const MP_ACTION MPActionTable[11];



//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	メッセージ生成に必要なワークを生成
 */
//-----------------------------------------------------------------------------
static void MakeMsgWork(MSG_WORK * msgwk, FIELDSYS_WORK * fsys, WORDSET * wordset, void * slot)
{
	msgwk->fsys = fsys;
	msgwk->wordset = wordset;
	msgwk->slot = slot;
}

//-----------------------------------------------------------------------------
/**
 * @brief	おくりもののIDを取得する
 */
//-----------------------------------------------------------------------------
static int MP_GetGiftID(FIELDSYS_WORK * fsys)
{
    int index = FUSHIGIDATA_GetSlotType(FUSHIGIDATA_CheckSlotData());

#ifdef DEBUG_ONLY_FOR_ohno
    OS_TPrintf("おくりものindex = %d\n",index);
#endif
    return index;
}

//-----------------------------------------------------------------------------
/**
 * @brief	おくりもののデータを取得する
 */
//-----------------------------------------------------------------------------
static void * MP_GetSlotWork(FIELDSYS_WORK * fsys)
{
    return FUSHIGIDATA_GetSlotPtr(FUSHIGIDATA_CheckSlotData());
}
//-----------------------------------------------------------------------------
/**
 * @brief	おくりもののデータを削除する
 */
//-----------------------------------------------------------------------------
static void MP_EraseSlotData(FIELDSYS_WORK * fsys)
{
	FUSHIGIDATA_RemoveSlot(FUSHIGIDATA_CheckSlotData());
}

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	ふしぎ配達員
 */
//-----------------------------------------------------------------------------
BOOL EvCmdMysteryPostMan(VM_MACHINE * core)
{
    switch (VMGetU16(core)) {
      case POSTMAN_CMD_INIT:
        // 初期化
        FUSHIGIDATA_InitSlot(core->fsys->savedata, HEAPID_EVENT);
        break;
      case POSTMAN_CMD_END:
        // 終了処理
        FUSHIGIDATA_FinishSlot(core->fsys->savedata, FALSE);
        break;
      case POSTMAN_CMD_SAVE_END:
        // セーブして終了
        FUSHIGIDATA_FinishSlot(core->fsys->savedata, TRUE);
        break;
      case POSTMAN_CMD_PRESENT_CHECK:
        //贈り物の存在チェック
		{
            u16 * ret_wk = VMGetWork(core);
			if (MP_GetGiftID(core->fsys) != 0) {
				*ret_wk = 1;
			} else {
				*ret_wk = 0;
			}
		}
		break;
      case POSTMAN_CMD_GET_PRESENT_ID:
		//贈り物の種類ID取得
		{
			u16 * ret_wk = VMGetWork(core);
			*ret_wk = MP_GetGiftID(core->fsys);
		}
		break;
	case POSTMAN_CMD_RECEIVE_CHECK:
		//個別の受け取り可能チェック
		{
			u16 * ret_wk = VMGetWork(core);
			const MP_ACTION * mpact = &MPActionTable[MP_GetGiftID(core->fsys) - 1];
			*ret_wk = mpact->check_func(core->fsys, MP_GetSlotWork(core->fsys));
		}
		break;
	case POSTMAN_CMD_RECEIVE_PRESENT:
		//個別の受け取り処理
		{
			const MP_ACTION * mpact = &MPActionTable[MP_GetGiftID(core->fsys) - 1];
			mpact->receive_func(core->fsys, MP_GetSlotWork(core->fsys));
			MP_EraseSlotData(core->fsys);
		}
		break;
	case POSTMAN_CMD_ENABLE_MSG:
		//受け取りメッセージIDを取得
		{
			MSG_WORK msgwk;
			const MP_ACTION * mpact = &MPActionTable[MP_GetGiftID(core->fsys) - 1];
			WORDSET** wordset = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_WORDSET);
			u16 * arc_id = VMGetWork(core);
			u16 * msg_id = VMGetWork(core);
			MakeMsgWork(&msgwk, core->fsys, *wordset, MP_GetSlotWork(core->fsys));
			mpact->ok_msg_func(&msgwk, arc_id, msg_id);
		}
		break;
	case POSTMAN_CMD_DISABLE_MSG:
		//受け取れないメッセージIDを取得
		{
			MSG_WORK msgwk;
			const MP_ACTION * mpact = &MPActionTable[MP_GetGiftID(core->fsys) - 1];
			WORDSET** wordset = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_WORDSET);
			u16 * arc_id = VMGetWork(core);
			u16 * msg_id = VMGetWork(core);
			MakeMsgWork(&msgwk, core->fsys, *wordset, MP_GetSlotWork(core->fsys));
			mpact->ng_msg_func(&msgwk, arc_id, msg_id);
		}
		break;
	}
	return 0;
}

//============================================================================================
//
//		マナフィー
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL Pokemon_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
	POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
	if (PokeParty_GetPokeCount(party) < 6) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Manafi_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
	EvPoke_AddTamago(HEAPID_EVENT, fsys->savedata, MONSNO_MANAFI, TRUE, PLACENAME_TYPE_EXT_EVENT, MAPNAME_RENJA);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Manafi_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
	*arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_14;
	WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
}

//============================================================================================
// ポケモン
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Pokemon_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    MYSTATUS* pMy = SaveData_GetMyStatus(fsys->savedata);
    POKEPARTY* party;
    POKEMON_PARAM* pPP;
    BOOL bResult;
    POKEMON_PARAM *pPPTemp = NULL;
    u32 id, rnd, new_rnd, sum;
    u32 oya_id;
    int placeID;
    u8 *buf;
    u8 *ribbon;

    pPP = (POKEMON_PARAM*)&pGift->pokemon.data;
    ribbon = (u8 *)&pGift->pokemon.ribbon;
    placeID = PokeParaGet(pPP, ID_PARA_get_place, NULL);

    // 個体乱数の再設定処理
    rnd = PokeParaGet(pPP, ID_PARA_personal_rnd, NULL);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("設定されていた固体乱数 = %08X\n", rnd);
#endif
    id = PokeParaGet(pPP, ID_PARA_id_no, NULL);
    new_rnd = gf_fix_rand((u32)OS_GetTick());
    if(rnd == POKEMON_RND_FULL_RANDOM){		// 完全なる乱数
      ;
    } else if(rnd == POKEMON_RND_EXCEPT_RARE){	// レアを除く乱数
      while(PokeRareGetPara(id, new_rnd)){
	new_rnd = gf_fix_rand( new_rnd );
      }
    } else {
      new_rnd = rnd;
    }
    // 固体乱数を新しく設定する
    PokeParaPersonalRndChange(pPP, new_rnd);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("新しい固体乱数 = %08X\n", new_rnd);
#endif
    
    // パワー乱数の再設定
    sum =
      PokeParaGet(pPP, ID_PARA_hp_rnd, 0)     + PokeParaGet(pPP, ID_PARA_pow_rnd, 0) +
      PokeParaGet(pPP, ID_PARA_def_rnd, 0)    + PokeParaGet(pPP, ID_PARA_agi_rnd, 0) +
      PokeParaGet(pPP, ID_PARA_spepow_rnd, 0) + PokeParaGet(pPP, ID_PARA_spedef_rnd, 0);
    if(sum == 0){
      rnd = gf_rand();
      new_rnd = (rnd & (0x001F <<  0)) >>  0;
      PokeParaPut(pPP, ID_PARA_hp_rnd,    (u8 *)&new_rnd);
      new_rnd = (rnd & (0x001F <<  5)) >>  5;
      PokeParaPut(pPP, ID_PARA_pow_rnd,   (u8 *)&new_rnd);
      new_rnd = (rnd & (0x001F << 10)) >> 10;
      PokeParaPut(pPP, ID_PARA_def_rnd,   (u8 *)&new_rnd);
      rnd = gf_rand();
      new_rnd = (rnd & (0x001F <<  0)) >>  0;
      PokeParaPut(pPP, ID_PARA_agi_rnd,   (u8 *)&new_rnd);
      new_rnd = (rnd & (0x001F <<  5)) >>  5;
      PokeParaPut(pPP, ID_PARA_spepow_rnd,(u8 *)&new_rnd);
      new_rnd = (rnd & (0x001F << 10)) >> 10;
      PokeParaPut(pPP, ID_PARA_spedef_rnd,(u8 *)&new_rnd);
    }

    // リボン処理
    buf = SaveData_GetSpRibbon(fsys->savedata);
    if(PokeParaGet(pPP, ID_PARA_sinou_red_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_RED)] = ribbon[0];
    if(PokeParaGet(pPP, ID_PARA_sinou_green_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_GREEN)] = ribbon[1];
    if(PokeParaGet(pPP, ID_PARA_sinou_blue_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_BLUE)] = ribbon[2];
    if(PokeParaGet(pPP, ID_PARA_sinou_festival_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_FESTIVAL)] = ribbon[3];
    if(PokeParaGet(pPP, ID_PARA_sinou_carnival_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_CARNIVAL)] = ribbon[4];
    if(PokeParaGet(pPP, ID_PARA_sinou_classic_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_CLASSIC)] = ribbon[5];
    if(PokeParaGet(pPP, ID_PARA_sinou_premiere_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SINOU_PREMIERE)] = ribbon[6];
    if(PokeParaGet(pPP, ID_PARA_marine_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_MARINE)] = ribbon[7];
    if(PokeParaGet(pPP, ID_PARA_land_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_LAND)] = ribbon[8];
    if(PokeParaGet(pPP, ID_PARA_sky_ribbon, 0))
      buf[RIBBON_SaveIndexGet(RIBBON_ID_SKY)] = ribbon[9];

    // 親名を変更「しない」場合は今の親名を覚えておいて、後で上書きする
    if(pGift->pokemon.parentType == MYSTERYPOKE_PARENTNAME_THROW){
        STRBUF* pName = MyStatus_CreateNameString(pMy, HEAPID_EVENT);
        u32 id = MyStatus_GetID(pMy);
        u32 sex = MyStatus_GetMySex(pMy);
        pPPTemp = PokemonParam_AllocWork( HEAPID_EVENT );
        PokeCopyPPtoPP(pPP,pPPTemp);
        // 親名を変更する場合
        PokeParaPut(pPPTemp,ID_PARA_oyaname_buf, pName);
	// 親のIDをコピー
        PokeParaPut(pPPTemp,ID_PARA_id_no,       &id);
	// 親の性別をコピー
        PokeParaPut(pPPTemp,ID_PARA_oyasex,      &sex);
        pPP = pPPTemp;
        STRBUF_Delete(pName);
    }
    
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("捕まえた日付: %d.%d.%d\n",
	       PokeParaGet(pPP,ID_PARA_get_year, 0),
	       PokeParaGet(pPP,ID_PARA_get_month, 0),
	       PokeParaGet(pPP,ID_PARA_get_day, 0));
    OS_TPrintf("捕まえた場所: %d\n", PokeParaGet(pPP,ID_PARA_get_place, 0));
    OS_TPrintf("生まれた日付: %d.%d.%d\n",
	       PokeParaGet(pPP,ID_PARA_birth_year, 0),
	       PokeParaGet(pPP,ID_PARA_birth_month, 0),
	       PokeParaGet(pPP,ID_PARA_birth_day, 0));
    OS_TPrintf("生まれた場所: %d\n\n", PokeParaGet(pPP,ID_PARA_birth_place, 0));
#endif
    
    // トレーナーメモの設定
    TrainerMemoSetPP(pPP, pMy, TRMEMO_FUSHIGI_PLACESET, 
		     PlaceName_IndexToParamNumber( PLACENAME_TYPE_EXT_EVENT, placeID), 
		     HEAPID_EVENT);

#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_TPrintf("捕まえた日付: %d.%d.%d\n",
	       PokeParaGet(pPP,ID_PARA_get_year, 0),
	       PokeParaGet(pPP,ID_PARA_get_month, 0),
	       PokeParaGet(pPP,ID_PARA_get_day, 0));
    OS_TPrintf("捕まえた場所: %d\n", PokeParaGet(pPP,ID_PARA_get_place, 0));
    OS_TPrintf("生まれた日付: %d.%d.%d\n",
	       PokeParaGet(pPP,ID_PARA_birth_year, 0),
	       PokeParaGet(pPP,ID_PARA_birth_month, 0),
	       PokeParaGet(pPP,ID_PARA_birth_day, 0));
    OS_TPrintf("生まれた場所: %d\n", PokeParaGet(pPP,ID_PARA_birth_place, 0));
#endif
    
    // 最後で再計算する
    PokeParaCalc(pPP);

    // セーブエリアへ置く
    party = SaveData_GetTemotiPokemon(fsys->savedata);
    bResult = PokeParty_Add(party, pPP);
    if (bResult) {
		// ポケモンを手に入れたら呼び出す！
		SaveData_GetPokeRegister( fsys->savedata, pPP );
    }
    if(pPPTemp){
        sys_FreeMemoryEz(pPPTemp);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Pokemon_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    POKEMON_PARAM* pPP;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_08;

    pPP = (POKEMON_PARAM*)&pGift->pokemon.data;
    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterPokeMonsName(msgwk->wordset, 1, PPPPointerGet(pPP));

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Pokemon_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
	*arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_05;
}

//============================================================================================
// たまご 
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Tamago_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
#if 1
  // 処理は全てポケモンと同じ
  Pokemon_ReceiveFunc(fsys, slot);
#else
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    MYSTATUS* pMy = SaveData_GetMyStatus(fsys->savedata);
    POKEPARTY* party;
    POKEMON_PARAM* pPP;
    BOOL bResult;
    POKEMON_PARAM *pPPTemp = NULL;

    pPP = (POKEMON_PARAM*)pGift->egg.data;
    if(pGift->pokemon.parentType == MYSTERYPOKE_PARENTNAME_MY){
        // 親名を変更する場合
        STRBUF* pName = MyStatus_CreateNameString(pMy, HEAPID_EVENT);
        u32 id = MyStatus_GetID(pMy);
        pPPTemp = PokemonParam_AllocWork( HEAPID_EVENT );
        PokeCopyPPtoPP(pPP,pPPTemp);
        PokeParaPut(pPPTemp,ID_PARA_oyaname_buf, pName);
        PokeParaPut(pPPTemp,ID_PARA_id_no,       &id);
        pPP = pPPTemp;
        STRBUF_Delete(pName);
    }
	party = SaveData_GetTemotiPokemon(fsys->savedata);
	bResult = PokeParty_Add(party, pPP);
//  if (bResult) {  //卵に図鑑必要なし
//  	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
//  	ZukanWork_SetPokeGet(zw, pPP);
//  }
    if(pPPTemp){
        sys_FreeMemoryEz(pPPTemp);
    }
#endif
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Tamago_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    POKEMON_PARAM* pPP;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_09;

    pPP = (POKEMON_PARAM*)pGift->egg.data;
    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterPokeMonsName(msgwk->wordset, 1, PPPPointerGet(pPP));
}

//============================================================================================
// アイテム
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Item_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);

    return MyItem_AddCheck(myitem, pGift->item.itemNo, 1, HEAPID_EVENT);
}

//-----------------------------------------------------------------------------
static void Item_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
	u16 ret;
    u16 item_no =  pGift->item.itemNo;

    MyItem_AddItem( myitem, item_no, 1, HEAPID_EVENT );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Item_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  pGift->item.itemNo;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_10;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Item_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    MYITEM* myitem = SaveData_GetMyItem(msgwk->fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  pGift->item.itemNo;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_06;
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//============================================================================================
// ルール
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Regulation_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    return TRUE;   // 上書きするのみなのでOK
}

//-----------------------------------------------------------------------------
static void Regulation_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    const REGULATION* pReg = (const REGULATION*)pGift;

    SaveData_SetRegulation(fsys->savedata, pReg);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Regulation_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    const REGULATION* pReg = (const REGULATION*)pGift;
    STRBUF* pBuf;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_11;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
    pBuf = Regulation_CreateCupName(pReg, HEAPID_EVENT);
    WORDSET_RegisterWord(msgwk->wordset, 1, pBuf, PM_MALE, TRUE, PM_LANG);
    STRBUF_Delete(pBuf);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Regulation_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    // 呼ばれることが無いが一応
    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_07;
}

//============================================================================================
// 秘密基地グッズ
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL UGGoods_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    int num = UnderGroundGetNumGoodsPCItem(SaveData_GetUnderGroundData(fsys->savedata));

    if(num < UG_ITEM_PC_NUM_MAX){
        return TRUE;
    }
    return FALSE;
}

//-----------------------------------------------------------------------------
static void UGGoods_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    int goodsNo = pGift->goods.goodsNo;

    UnderGroundAddGoodsPCItem(SaveData_GetUnderGroundData(fsys->savedata), goodsNo);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void UGGoods_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    int goodsNo = pGift->goods.goodsNo;
    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_12;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
    WORDSET_RegisterUGGoodsName(msgwk->wordset, 1, goodsNo);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void UGGoods_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_07;
}

//============================================================================================
// アクセサリ
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Accessory_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    int accType = pGift->accessory.accType;
    int accNo = pGift->accessory.accNo;

    switch(accType){
      case MYSTERYGIFT_ACCTYPE_SEAL:
        return CB_SaveData_IsAddIt(CB_SaveData_AllDataGet(fsys->savedata), accNo,1);
      case MYSTERYGIFT_ACCTYPE_CLIP:
        return TRUE;
      case MYSTERYGIFT_ACCTYPE_BG:
        return TRUE;
    }
    return FALSE;
}

//-----------------------------------------------------------------------------
static void Accessory_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    int accType = pGift->accessory.accType;
    int accNo = pGift->accessory.accNo;


    switch(accType){
      case MYSTERYGIFT_ACCTYPE_SEAL:
        CB_SaveData_ItemNumAddCheck(CB_SaveData_AllDataGet(fsys->savedata), accNo,1);
        break;
      case MYSTERYGIFT_ACCTYPE_CLIP:
        ImcSaveData_AddAcceFlag(ImcSaveData_GetItemSaveData(SaveData_GetImcSaveData(fsys->savedata)), accNo,1);
        break;
      case MYSTERYGIFT_ACCTYPE_BG:
        ImcSaveData_SetBGFlag(ImcSaveData_GetItemSaveData(SaveData_GetImcSaveData(fsys->savedata)), accNo);
        break;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Accessory_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    int accType = pGift->accessory.accType;
    int accNo = pGift->accessory.accNo;

    switch(accType){
      case MYSTERYGIFT_ACCTYPE_SEAL:
        WORDSET_RegisterSealName(msgwk->wordset, 1, accNo);
        break;
      case MYSTERYGIFT_ACCTYPE_CLIP:
        WORDSET_RegisterAccessoryName(msgwk->wordset, 1, accNo);
        break;
      case MYSTERYGIFT_ACCTYPE_BG:
        WORDSET_RegisterImageClibBgName(msgwk->wordset, 1, accNo);
        break;
    }
    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_13;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Accessory_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_07;
}

//============================================================================================
// メンバーズカード
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Card_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);

    return MyItem_AddCheck(myitem, ITEM_MENBAAZUKAADO, 1, HEAPID_EVENT);
}

//-----------------------------------------------------------------------------
static void Card_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	u16 ret;
    u16 item_no =  ITEM_MENBAAZUKAADO;

    MyItem_AddItem( myitem, item_no, 1, HEAPID_EVENT );
	//ダークのイベント許可！
	SysWork_HaihuEventWorkSet(ev, HAIHUEVENT_ID_D30);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Card_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_MENBAAZUKAADO;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_15;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Card_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    MYITEM* myitem = SaveData_GetMyItem(msgwk->fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_MENBAAZUKAADO;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_06;
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//============================================================================================
// オーキドの手紙
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Ookido_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);

    return MyItem_AddCheck(myitem, ITEM_OOKIDONOTEGAMI, 1, HEAPID_EVENT);
}

//-----------------------------------------------------------------------------
static void Ookido_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	u16 ret;
    u16 item_no =  ITEM_OOKIDONOTEGAMI;

    MyItem_AddItem( myitem, item_no, 1, HEAPID_EVENT );
	//エウリスのイベント許可！
	SysWork_HaihuEventWorkSet(ev, HAIHUEVENT_ID_D18);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Ookido_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_OOKIDONOTEGAMI;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_16;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Ookido_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    MYITEM* myitem = SaveData_GetMyItem(msgwk->fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_OOKIDONOTEGAMI;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_06;
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//============================================================================================
// てんかいのふえ
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Whistle_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);

    return MyItem_AddCheck(myitem, ITEM_TENKAINOHUE, 1, HEAPID_EVENT);
}

//-----------------------------------------------------------------------------
static void Whistle_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    MYITEM* myitem = SaveData_GetMyItem(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	u16 ret;
    u16 item_no =  ITEM_TENKAINOHUE;

    MyItem_AddItem( myitem, item_no, 1, HEAPID_EVENT );
	//アウスのイベント許可！
	SysWork_HaihuEventWorkSet(ev, HAIHUEVENT_ID_D05);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Whistle_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_TENKAINOHUE;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_17;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Whistle_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    MYITEM* myitem = SaveData_GetMyItem(msgwk->fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);
    u16 item_no =  ITEM_TENKAINOHUE;

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_06;
	WORDSET_RegisterItemName(msgwk->wordset, 1, item_no);
}

//============================================================================================
// ぽけっち
//============================================================================================
//-----------------------------------------------------------------------------
static BOOL Poketch_ReceiveCheckFunc(FIELDSYS_WORK * fsys, void * slot)
{
    POKETCH_DATA* pPoketch = SaveData_GetPoketchData(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);

    return PoketchData_GetPoketchGetFlag(pPoketch);
}

//-----------------------------------------------------------------------------
static void Poketch_ReceiveFunc(FIELDSYS_WORK * fsys, void * slot)
{
    POKETCH_DATA* pPoketch = SaveData_GetPoketchData(fsys->savedata);
    GIFT_PRESENT* pGift = MP_GetSlotWork(fsys);
    
    PoketchData_AddApplication( pPoketch, pGift->poketch.id );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Poketch_OKMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_19;

    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
	WORDSET_RegisterPoketchAppName(msgwk->wordset, 1, pGift->poketch.id);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void Poketch_NGMsgFunc(MSG_WORK * msgwk, u16 * arc_id, u16 * msg_id)
{
    GIFT_PRESENT* pGift = MP_GetSlotWork(msgwk->fsys);

    *arc_id = NARC_msg_haitatu_dat;
	*msg_id = msg_haitatu_20;
    WORDSET_RegisterPlayerName(msgwk->wordset, 0, SaveData_GetMyStatus(msgwk->fsys->savedata));
}






//============================================================================================
//
//		ふしぎ配達員アクションテーブル
//
//============================================================================================
static const MP_ACTION MPActionTable[] = {
	{   // ポケモン
		Pokemon_ReceiveCheckFunc,
		Pokemon_ReceiveFunc,
		Pokemon_OKMsgFunc,
		Pokemon_NGMsgFunc,
	},
	{   //たまご
		Pokemon_ReceiveCheckFunc,
		Tamago_ReceiveFunc,
		Tamago_OKMsgFunc,
		Pokemon_NGMsgFunc,
	},
	{   //どうぐ
		Item_ReceiveCheckFunc,
		Item_ReceiveFunc,
		Item_OKMsgFunc,
		Item_NGMsgFunc,
	},
	{   //ルール
		Regulation_ReceiveCheckFunc,
		Regulation_ReceiveFunc,
		Regulation_OKMsgFunc,
		Regulation_NGMsgFunc,
	},
	{   //秘密基地グッズ
		UGGoods_ReceiveCheckFunc,
		UGGoods_ReceiveFunc,
		UGGoods_OKMsgFunc,
		UGGoods_NGMsgFunc,
	},
	{   //アクセサリー
		Accessory_ReceiveCheckFunc,
		Accessory_ReceiveFunc,
		Accessory_OKMsgFunc,
		Accessory_NGMsgFunc,
	},
	{   //マナフィー
		Pokemon_ReceiveCheckFunc,
		Manafi_ReceiveFunc,
		Manafi_OKMsgFunc,
		Pokemon_NGMsgFunc,
	},
	{   //メンバーズカード
		Card_ReceiveCheckFunc,
		Card_ReceiveFunc,
		Card_OKMsgFunc,
		Card_NGMsgFunc,
	},
	{   //オーキドの手紙
		Ookido_ReceiveCheckFunc,
		Ookido_ReceiveFunc,
		Ookido_OKMsgFunc,
		Ookido_NGMsgFunc,
	},
	{   //てんかいのふえ
		Whistle_ReceiveCheckFunc,
		Whistle_ReceiveFunc,
		Whistle_OKMsgFunc,
		Whistle_NGMsgFunc,
	},
	{   //ぽけっち
		Poketch_ReceiveCheckFunc,
		Poketch_ReceiveFunc,
		Poketch_OKMsgFunc,
		Poketch_NGMsgFunc,
	},
};




