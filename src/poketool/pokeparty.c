//============================================================================================
/**
 * @file	pokeparty.c
 * @brief	ポケモンパーティ操作
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.13
 */
//============================================================================================


#include	"common.h"
#include	"poketool/poke_tool.h"
#include	"poke_tool_def.h"
#include	"system/gamedata.h"

#include	"poketool/pokeparty.h"

//手持ちポケモンデータ取得のため
#include	"system/savedata.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ポケモンパーティー構造体の定義
 *
 * 最大で6体までのポケモンをまとめて保持できるようになっている。
 */
//----------------------------------------------------------
struct _POKEPARTY {
	///	保持できるポケモン数の最大
	int PokeCountMax;
	///	現在保持しているポケモン数
	int PokeCount;
	///	ポケモンデータ
	struct pokemon_param member[TEMOTI_POKEMAX];
};

//----------------------------------------------------------
/**
 * @brief	指定位置が正しいかどうかの判定
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	pos		ポケモンの位置（０オリジン）
 */
//----------------------------------------------------------
#define	PARTY_POS_ASSERT(party, pos)	{\
	GF_ASSERT((pos) >= 0);				\
	GF_ASSERT_MSG((pos) < (party)->PokeCount, "pos(%d) >= PokeCount(%d)\n",pos, (party)->PokeCount); \
	GF_ASSERT((pos) < (party)->PokeCountMax) \
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	POKEPARTY構造体のサイズ取得
 * @return	int	POKEPARTY構造体の大きさ
 */
//----------------------------------------------------------
int PokeParty_GetWorkSize(void)
{
	return sizeof(POKEPARTY);
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTY構造体のワーク確保
 * @param	heapID		メモリを確保するヒープへのポインタ
 * @return	POKEPARTYへのポインタ
 */
//----------------------------------------------------------
POKEPARTY * PokeParty_AllocPartyWork(u32 heapID)
{
	POKEPARTY * party;

	party = sys_AllocMemory(heapID, sizeof(POKEPARTY));
	PokeParty_InitWork(party);

	return party;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYの初期化処理
 * @param	party	POKEPARTY構造体へのポインタ
 */
//----------------------------------------------------------
void PokeParty_InitWork(POKEPARTY * party)
{
	PokeParty_Init(party, TEMOTI_POKEMAX);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	POKEPARTYの初期化処理
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	max		POKEPARTYが保持できる最大のポケモン数
 */
//----------------------------------------------------------
void PokeParty_Init(POKEPARTY * party, int max)
{
	int i;
	GF_ASSERT(max <= TEMOTI_POKEMAX);
	memset(party, 0, sizeof(POKEPARTY));
	party->PokeCount = 0;
	party->PokeCountMax = max;
	for (i = 0; i < TEMOTI_POKEMAX; i++) {
		PokeParaInit(&party->member[i]);
	}
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYにポケモンを加える
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	poke	加えるポケモンへのデータ
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//----------------------------------------------------------
BOOL PokeParty_Add(POKEPARTY * party, POKEMON_PARAM * poke)
{
	if (party->PokeCount >= party->PokeCountMax) {
		//手持ちがいっぱい
		return FALSE;
	}
	party->member[party->PokeCount] = *poke;
	party->PokeCount ++;

	return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYからポケモンを取り除く
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	pos		取り除くポケモンの位置（０オリジン）
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//----------------------------------------------------------
BOOL PokeParty_Delete(POKEPARTY * party, int pos)
{
	int i;
	PARTY_POS_ASSERT(party, pos);
	GF_ASSERT( party->PokeCount > 0 );

	for (i = pos ;i < party->PokeCount - 1; i ++) {
		party->member[i] = party->member[i + 1];
	}
	PokeParaInit(&party->member[i]);
	party->PokeCount--;

	return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYから手持ち数を取得
 * @param	party	POKEPARTY構造体へのポインタ
 * @retval	手持ち数
 */
//----------------------------------------------------------
int	PokeParty_GetPokeCount(const POKEPARTY * party)
{
	return party->PokeCount;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYからポケモンへのポインタを取得
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	pos		参照したいポケモンの位置（０オリジン）
 * @retval	POKEMON_PARAM	指定したポケモンへのポインタ
 */
//----------------------------------------------------------
POKEMON_PARAM * PokeParty_GetMemberPointer(const POKEPARTY * party, int pos)
{
	PARTY_POS_ASSERT(party, pos);
	return (POKEMON_PARAM*)&party->member[pos];
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYへポケモンデータを強制セット
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	pos		セットしたいポケモンの位置（０オリジン）
 * @param	pp		セットしたいポケモンデータ
 *
 * ボックスから拾ってきたポケモンと「入れ替える」処理に便利なので作成した。
 * 通常、メンバーの追加には PokeParty_Add を使ってください。  taya
 *
 */
//----------------------------------------------------------
void PokeParty_SetMemberData( POKEPARTY* party, int pos, POKEMON_PARAM* pp )
{
	int cnt;

	PARTY_POS_ASSERT(party, pos);

	cnt = PokeParaGet(&(party->member[pos]), ID_PARA_poke_exist, NULL) - PokeParaGet(pp, ID_PARA_poke_exist, NULL);
	party->member[pos] = *pp;
	party->PokeCount += cnt;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTY内でポケモンの位置を入れ替える
 * @param	party	POKEPARTY構造体へのポインタ
 * @param	pos1	ポケモンの位置（０オリジン）
 * @param	pos2	ポケモンの位置（０オリジン）
 * @retval	TRUE	成功
 * @retval	FALSE	失敗
 */
//----------------------------------------------------------
BOOL PokeParty_ExchangePosition(POKEPARTY * party, int pos1, int pos2)
{
	struct pokemon_param * temp;

	PARTY_POS_ASSERT(party, pos1);
	PARTY_POS_ASSERT(party, pos2);

	temp = sys_AllocMemory(HEAPID_BASE_SYSTEM, sizeof(struct pokemon_param));
	*temp = party->member[pos1];
	party->member[pos1] = party->member[pos2];
	party->member[pos2] = *temp;
	sys_FreeMemoryEz(temp);

	return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTYのコピー
 * @param	src		POKEPARTY構造体へのポインタ
 * @param	dst		POKEPARTY構造体へのポインタ
 */
//----------------------------------------------------------
void PokeParty_Copy(const POKEPARTY * src, POKEPARTY * dst)
{
	*dst = *src;
}

//----------------------------------------------------------
/**
 * @brief	POKEPARTY内にモンスターがいるかどうか？
 * @param	ppt		チェックするPOKEPARTY構造体へのポインタ
 * @param	mons_no	いるかチェックするモンスターナンバー
 * @return	FALSE:いない　TRUE:いる
 */
//----------------------------------------------------------
BOOL PokeParty_PokemonCheck(const POKEPARTY * ppt, int mons_no)
{
	int				i;

	for(i=0;i<ppt->PokeCount;i++){
		if(PokeParaGet((POKEMON_PARAM*)&ppt->member[i],ID_PARA_monsno,NULL)==mons_no){
			break;
		}
	}

	return (i!=ppt->PokeCount);
}

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	手持ちポケモンデータの取得
 * @param	sv	セーブデータへのポインタ
 * @return	POKEPARTY	手持ちポケモンデータへのポインタ
 */
//----------------------------------------------------------
POKEPARTY * SaveData_GetTemotiPokemon(SAVEDATA * sv)
{
	POKEPARTY * party;
	party = (POKEPARTY *)SaveData_Get(sv, GMDATA_ID_TEMOTI_POKE);
	return party;
}

//----------------------------------------------------------
/**
 * @brief	デバッグ：ダミーパーティの生成
 * @param	party	POKEPARTY構造体へのポインタ
 */
//----------------------------------------------------------
void Debug_PokeParty_MakeParty(POKEPARTY * party)
{
	struct pokemon_param poke;
	int i;
	PokeParty_Init(party, TEMOTI_POKEMAX);
	for (i = 0; i < 3; i++) {
		PokeParaInit(&poke);
		PokeParaSet(&poke, 392 + i, 99, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
		PokeParty_Add(party, &poke);
	}
}

// 外部参照インデックスを作る時のみ有効(ゲーム中は無効)
#ifdef CREATE_INDEX
void *Index_Get_PokeCount_Offset(POKEPARTY *pt){ return &pt->PokeCount; }
#endif
