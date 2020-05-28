//============================================================================================
/**
 * @file	pokepark_data.c
 * @date	2006.06.01
 * @author	tamada / mitsuhara
 * @brief	AGB→DS用セーブデータ関連
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/pokepark_data.h"

#include "gflib/assert.h"


//本当は他のディレクトリの中に手を突っ込んでインクルードするような
//ことはやるべきでないが仕方なく…

#include "../poketool/poke_tool_def.h"
#include "poketool/poke_tool.h"
#include "system/pm_rtc.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ポケパーク用セーブデータの定義
 */
//------------------------------------------------------------------
#define POKEPARK_HISTORY_SIZE		20
struct POKEPARK_DATA {
  POKEMON_PARAM mons[POKEPARK_MONS_MAX];
  u32 AgbTrainerID[POKEPARK_HISTORY_SIZE];	// 移動したカセットのトレーナーID
  s64 CheckTime[POKEPARK_HISTORY_SIZE];		// 移動した時刻
  s64 RTCOffset;				// 時間をずらした累積(比較用)
  u8 MacAddress[6];				// ポケモンを移動したDS本体のMacアドレス
};

//============================================================================================
//
//		主にセーブシステムから呼ばれる関数
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	セーブデータサイズの取得
 * @return	int		ポケパーク用セーブデータのサイズ
 */
//------------------------------------------------------------------
int POKEPARKDATA_GetWorkSize(void)
{
	return sizeof(POKEPARK_DATA);
}

//------------------------------------------------------------------
/**
 * @brief	セーブデータ初期化
 * @param	ppark		ポケパーク用セーブデータへのポインタ
 */
//------------------------------------------------------------------
void POKEPARKDATA_Init(POKEPARK_DATA * ppark)
{
	int i;
	MI_CpuClearFast(ppark, sizeof(POKEPARK_DATA));
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		PokeParaInit(&ppark->mons[i]);
		GF_ASSERT(PokeParaGet(&ppark->mons[i], ID_PARA_poke_exist, NULL) == 0);
	}
}
// POKEMON_PARAMのみを初期化する
void POKEPARKDATA_PreInit(POKEPARK_DATA * ppark)
{
  int i;
  MI_CpuClearFast(ppark->mons, sizeof(POKEMON_PARAM) * POKEPARK_MONS_MAX);
  for (i = 0; i < POKEPARK_MONS_MAX; i++) {
    PokeParaInit(&ppark->mons[i]);
    GF_ASSERT(PokeParaGet(&ppark->mons[i], ID_PARA_poke_exist, NULL) == 0);
  }
}

//============================================================================================
//
//
//				ローカル関数
//
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	セーブする管理用インデックスを返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int POKEPARKDATA_GetMasterIndex(POKEPARK_DATA *ppark, u32 agb_id)
{
  int i, index;
  s64 min;
  // 同じトレーナーIDを探す
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == agb_id)
      return i;
  }
  // 空いている場所を返す
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == 0)
      return i;
  }
  // 一番時間が経過している場所を返す
  min = 0x7FFFFFFF;	// 68years
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->CheckTime[i] < min){
      min = ppark->CheckTime[i];
      index = i;
    }
  }
  return index;
}


//============================================================================================
//
//
//				操作関数
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ポケモンデータの設定
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_SetData(POKEPARK_DATA *ppark, POKEMON_PASO_PARAM *ppp, int index)
{
  PokeReplace(ppp, &ppark->mons[index]);
}


//------------------------------------------------------------------
/**
 * @brief	管理用データをセット
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_SetMasterData(POKEPARK_DATA *ppark, u32 agb_id)
{
  int index = POKEPARKDATA_GetMasterIndex(ppark, agb_id);
  ppark->AgbTrainerID[index] = agb_id;
  ppark->CheckTime[index] = GF_RTC_GetDateTimeBySecond();
  ppark->RTCOffset = OS_GetOwnerRtcOffset();
  OS_GetMacAddress(ppark->MacAddress);
}

//------------------------------------------------------------------
/**
 * @brief	ポケパークデータをコピーで取得する
 * @param	ppark			ポケパークデータへのポインタ
 * @param	index			取得するポケモンのインデックスナンバー
 * @param	pp				コピー先のポケモンパラメータへのポインタ
 */
//------------------------------------------------------------------
void POKEPARKDATA_CopyPokemonParam(const POKEPARK_DATA * ppark, int index, POKEMON_PARAM * pp)
{
	GF_ASSERT(index < POKEPARK_MONS_MAX);
	*pp = ppark->mons[index];
}

//------------------------------------------------------------------
//------------------------------------------------------------------
int POKEPARKDATA_CountPokemon(const POKEPARK_DATA * ppark)
{
	int i,n;
	for (n = 0, i = 0; i <POKEPARK_MONS_MAX; i++) {
		if (PokeParaGet((POKEMON_PARAM *)&ppark->mons[i], ID_PARA_poke_exist, NULL)) {
			n++;
		}
	}
	return n;
}


//------------------------------------------------------------------
/**
 * @brief	履歴と一致するＩＤが存在するか返す
 * @param	ppark			ポケパークデータへのポインタ
 * @param	agb_id			トレーナーＩＤ
 * @return	0: なかった　それ以外は前回からの秒数
 */
//------------------------------------------------------------------
int POKEPARKDATA_CheckHistoryID(const POKEPARK_DATA *ppark, u32 agb_id)
{
  int i;
  s64 now = GF_RTC_GetDateTimeBySecond();

  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == agb_id){
      return now - ppark->CheckTime[i];
    }
  }
  return 0;
}


//------------------------------------------------------------------
/**
 * @brief	セーブされているMacアドレスと本体のMacアドレスを比較
 * @param	ppark			ポケパークデータへのポインタ
 * @return	TRUE: 一致　FALSE: 不一致
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_CheckMacAddress(const POKEPARK_DATA *ppark)
{
  int i;
  u8 mac[6];
  
  // MACアドレスのチェック
  OS_GetMacAddress(mac);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("セーブされているMACアドレス: %02X-%02X-%02X-%02X-%02X-%02X\n",
	     ppark->MacAddress[0], ppark->MacAddress[1], ppark->MacAddress[2],
	     ppark->MacAddress[3], ppark->MacAddress[4], ppark->MacAddress[5]);
  OS_TPrintf("　　　　　本体のMACアドレス: %02X-%02X-%02X-%02X-%02X-%02X\n",
	     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
#endif  
  for(i = 0; i < 6; i++){
    if(mac[i] != ppark->MacAddress[i])
      return FALSE;
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	時間をずらされたかを返す
 * @param	ppark			ポケパークデータへのポインタ
 * @return	TRUE: ずらされてない　FALSE: ずらされた
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_CheckRTCOffset(const POKEPARK_DATA *ppark)
{
  return ppark->RTCOffset == OS_GetOwnerRtcOffset();
}


//------------------------------------------------------------------
/**
 * @brief	新規セーブかどうかを返す
 * @param	ppark			ポケパークデータへのポインタ
 * @return	TRUE: 新規セーブ　FALSE: それ以外
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_isNewSave(const POKEPARK_DATA *ppark)
{
  int i;
  u8 code;
  
  for(code = 0, i = 0; i < 6; i++)
    code |= ppark->MacAddress[i];

  if(code == 0)
    // 新規セーブデータが作成されたばかりはTRUEを返す
    return TRUE;
  return FALSE;
}


#ifdef	PM_DEBUG
//------------------------------------------------------------------
/**
 * @brief	ポケモンデータの設定
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_Debug_SetData(POKEPARK_DATA *ppark, int index,
		int mons_no, int level, int pow, u32 rnd, u32 id)
{
  PokeParaSet(&ppark->mons[index], mons_no, level, pow, RND_SET, rnd, ID_SET, id);
}

#endif

