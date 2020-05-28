//============================================================================================
/**
 * @file	fushigi_data.c
 * @date	2006.04.28
 * @author	tamada / mitsuhara
 * @brief	ふしぎ通信用セーブデータ関連
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/fushigi_data.h"

#include "gflib/assert.h"

//============================================================================================
//============================================================================================

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);

#define UNIQ_TYPE			0xEDB88320L
#define FUSHIGI_DATA_NO_USED		0x00000000
#define FUSHIGI_DATA_MAX_EVENT		2048

#define FUSHIGI_MENU_FLAG		(FUSHIGI_DATA_MAX_EVENT - 1)

//------------------------------------------------------------------
/**
 * @brief	ふしぎデータの定義
 */
//------------------------------------------------------------------
struct FUSHIGI_DATA{
  u8 recv_flag[FUSHIGI_DATA_MAX_EVENT / 8];		//256 * 8 = 2048 bit
  u32 deli_type[GIFT_DELIVERY_MAX];			// 改竄チェック用コード
  u32 card_type[GIFT_CARD_MAX];
  GIFT_DELIVERY delivery[GIFT_DELIVERY_MAX];		// 配達員８つ
  GIFT_CARD card[GIFT_CARD_MAX];			// カード情報３つ
};


//============================================================================================
//
//		主にセーブシステムから呼ばれる関数
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	セーブデータサイズの取得
 * @return	int		ふしぎセーブデータのサイズ
 */
//------------------------------------------------------------------
int FUSHIGIDATA_GetWorkSize(void)
{
  return sizeof(FUSHIGI_DATA);
}
//------------------------------------------------------------------
/**
 * @brief	セーブデータ初期化
 * @param	fd		ふしぎセーブデータへのポインタ
 */
//------------------------------------------------------------------
void FUSHIGIDATA_Init(FUSHIGI_DATA * fd)
{
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("ふしぎデータ初期化\n");
  // この処理はsaveload_system.cのSVDT_Initで行われているので何もしない
  MI_CpuClearFast(fd, sizeof(FUSHIGI_DATA));
#endif
}

//============================================================================================
//
//		利用するために呼ばれるアクセス関数
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	配達員データの取得
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	index		配達員データのインデックス（０オリジン）
 * @return	GIFT_DATA	配達員データへのポインタ
 */
//------------------------------------------------------------------
GIFT_DELIVERY * FUSHIGIDATA_GetDeliData(FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_DELIVERY_MAX);

  if(fd->deli_type[index] == UNIQ_TYPE){
    // データが有効なのでポインタを返す
    return &fd->delivery[index];
  }
  // データが存在しない／壊れた／改造された？ので消去してNULLを返す
  fd->deli_type[index] = FUSHIGI_DATA_NO_USED;
  return (GIFT_DELIVERY *)NULL;
}

//------------------------------------------------------------------
/**
 * @brief	カードデータの取得
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	index		贈り物データのインデックス（０オリジン）
 * @return	GIFT_CARD	カードデータへのポインタ
 */
//------------------------------------------------------------------
GIFT_CARD *FUSHIGIDATA_GetCardData(FUSHIGI_DATA *fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);
  if(fd->card_type[index] != FUSHIGI_DATA_NO_USED)
    return &fd->card[index];
  return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	配達員データをセーブデータへ登録
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	p		データへのポインタ
 * @return	TRUE: セーブできた : FALSE: 空きスロットが無かった
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_SetDeliData(FUSHIGI_DATA *fd, const void *p, int link)
{
  int i;

  // セーブできる領域が無ければセーブ失敗
  if(FUSHIGIDATA_CheckDeliDataSpace(fd) == FALSE)	return FALSE;

  // ↓これ以降は容量的にはセーブに成功するはず
  
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(fd->deli_type[i] == FUSHIGI_DATA_NO_USED){
      MI_CpuCopy8(p, &fd->delivery[i], sizeof(GIFT_DELIVERY));
      fd->deli_type[i] = UNIQ_TYPE;
      fd->delivery[i].link = link;
      return TRUE;
    }
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	カードデータをセーブデータへ登録
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	p		データへのポインタ
 * @return	TRUE: セーブできた : FALSE: 空きスロットが無かった
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_SetCardData(FUSHIGI_DATA *fd, const void *p)
{
  int i;
  GIFT_CARD *gc = (GIFT_CARD *)p;

  // セーブできる領域が無ければセーブ失敗
  if(FUSHIGIDATA_CheckCardDataSpace(fd) == FALSE)	return FALSE;
  // 配達員を含むデータの場合は配達員側もチェック
  if(gc->beacon.delivery_flag == TRUE &&
     FUSHIGIDATA_CheckDeliDataSpace(fd) == FALSE)	return FALSE;

  // ↓これ以降は容量的にはセーブに成功するはず
  
  // カードをセーブする
  for(i = 0; i < GIFT_CARD_MAX; i++){
    if(fd->card_type[i] == FUSHIGI_DATA_NO_USED){
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("カードをセーブしました [%d]\n", i);
#endif
      MI_CpuCopy8(gc, &fd->card[i], sizeof(GIFT_CARD));
      fd->card_type[i] = UNIQ_TYPE;

      // 配達員をセーブする
      if(gc->beacon.delivery_flag == TRUE)
	FUSHIGIDATA_SetDeliData(fd, (const void *)&gc->gift_type, i+1);
  
      return TRUE;
    }
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	配達員データを抹消する
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	index		配達員データのインデックス
 * @return	TRUE: セーブできた : FALSE: 空きスロットが無かった
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_RemoveDeliData(FUSHIGI_DATA *fd, int index)
{
  index--;                                         // k.ohno --追加
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  fd->deli_type[index] = FUSHIGI_DATA_NO_USED;
  fd->delivery[index].link = 0;
  return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	カードデータを抹消する
 * @param	fd		ふしぎセーブデータへのポインタ
 * @return	TRUE: セーブできた : FALSE: 空きスロットが無かった
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_RemoveCardData(FUSHIGI_DATA *fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);
  fd->card_type[index] = FUSHIGI_DATA_NO_USED;
  // リンクされているカードも一緒に抹消
  FUSHIGIDATA_RemoveCardLinkDeli(fd, index + 1);

  return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	配達員データがセーブできるかチェック
 * @param	fd		ふしぎセーブデータへのポインタ
 * @return	TRUE: 空きがある : FALSE: 空きスロットが無い
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_CheckDeliDataSpace(FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(fd->deli_type[i] == FUSHIGI_DATA_NO_USED)
      return TRUE;
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	カードデータがセーブできるかチェック
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	size		データのサイズ
 * @return	TRUE: 空きがある : FALSE: 空きスロットが無い
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_CheckCardDataSpace(FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_CARD_MAX; i++){
    if(fd->card_type[i] == FUSHIGI_DATA_NO_USED)
      return TRUE;
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	贈り物データの存在チェック
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	index		贈り物データのインデックス（０オリジン）
 * @return	BOOL	TRUEの時、存在する
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsDelivery(const FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  
  if(fd->deli_type[index] == FUSHIGI_DATA_NO_USED)
    return FALSE;
  // ここで本来はデータのCRCチェックを入れた方がいいなぁ
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	カードデータが存在するか返す
 * @param	fd		ふしぎセーブデータへのポインタ
 * @return	BOOL	TRUEの時、存在する
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsCard(const FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);

  if(fd->card_type[index] == FUSHIGI_DATA_NO_USED)
    return FALSE;
  // ここで本来はデータのCRCチェックを入れた方がいいなぁ
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	セーブデータ内にカードデータが存在するか返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsCardAll(const FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_CARD_MAX; i++)
    if(FUSHIGIDATA_IsExistsCard(fd, i) == TRUE)
      return TRUE;
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	指定のカードにリンクされている配達員が存在するか
 * @param	※indexは１～３が有効
 * @return	TRUE: 配達員は存在する FALSE: 存在しない
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_GetCardLinkDeli(const FUSHIGI_DATA *fd, int index)
{
  int i;

#if 0
  for(i = 0; i < GIFT_DELIVERY_MAX; i++)
    OS_TPrintf("Deli[%d] : %d\n", i, fd->delivery[i].link);
#endif
  
  if(index){
    for(i = 0; i < GIFT_DELIVERY_MAX; i++){
      if(fd->delivery[i].link == index)
	return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	指定カードにリンクされている配達員を削除
 * @param	※indexは１～３が有効(無ければ何もしない)
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_RemoveCardLinkDeli(const FUSHIGI_DATA *fd, int index)
{
  int i;
  if(index){
    for(i = 0; i < GIFT_DELIVERY_MAX; i++){
      if(fd->delivery[i].link == index){
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_TPrintf("カードと一緒に %d 番のおくりものも消しました\n", i + 1);
#endif
	FUSHIGIDATA_RemoveDeliData((FUSHIGI_DATA *)fd, i + 1);
	return;
      }
    }
  }
}

//------------------------------------------------------------------
/**
 * @brief	指定のイベントはすでにもらったか返す
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	num		イベント番号
 * @return	BOOL	TRUEの時、すでにもらっている
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsEventRecvFlag(FUSHIGI_DATA * fd, int num)
{
  GF_ASSERT(num < FUSHIGI_DATA_MAX_EVENT);
  return !!(fd->recv_flag[num / 8] & (1 << (num & 7)));
}


//------------------------------------------------------------------
/**
 * @brief	指定のイベントもらったよフラグを立てる
 * @param	fd		ふしぎセーブデータへのポインタ
 * @param	num		イベント番号
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_SetEventRecvFlag(FUSHIGI_DATA * fd, int num)
{
  GF_ASSERT(num < FUSHIGI_DATA_MAX_EVENT);
  fd->recv_flag[num / 8] |= (1 << (num & 7));
}


//------------------------------------------------------------------
/**
 * @brief	ふしぎなおくりものを表示出来るか？
 * @param	NONE
 * @return	TRUE: 表示　FALSE: 表示しない
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsFushigiMenu(FUSHIGI_DATA *fd)
{
  return FUSHIGIDATA_IsEventRecvFlag(fd, FUSHIGI_MENU_FLAG);
}


//------------------------------------------------------------------
/**
 * @brief	ふしぎなおくりものの表示フラグをONにする
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_SetFushigiMenu(FUSHIGI_DATA *fd)
{
  FUSHIGIDATA_SetEventRecvFlag(fd, FUSHIGI_MENU_FLAG);
}


//============================================================================================
//
//		さらに上位の関数群　主にこちらを呼んでください
//
//============================================================================================

static FUSHIGI_DATA *_fushigi_ptr = NULL;

//------------------------------------------------------------------
/**
 * @brief	これ以下の関数を使うために必要な初期化
 * @param	sv		セーブデータ構造へのポインタ
 * @param	heap_id		ワークを取得するヒープのID
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_InitSlot(SAVEDATA * sv, int heap_id)
{
  LOAD_RESULT result;

  if(_fushigi_ptr == NULL){
    _fushigi_ptr = SaveData_GetFushigiData(sv);
  }
}

//------------------------------------------------------------------
/**
 * @brief	これ以下の関数を使い終わった後の後始末
 * @param	sv		セーブデータ構造へのポインタ
 * @param	flag		TRUE: セーブする / FALSE: セーブしない
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_FinishSlot(SAVEDATA * sv, int flag)
{
  SAVE_RESULT result;
  if(_fushigi_ptr){
#if 0
    if(flag == TRUE)
      SaveData_Save(sv);
#endif
    _fushigi_ptr = NULL;
  }
}
     
//------------------------------------------------------------------
/**
 * @brief	スロットにデータがあるか返す関数
 * @param	NONE
 * @return	BOOL	0..データなし: ≠0..データあり
*/
//------------------------------------------------------------------
int FUSHIGIDATA_CheckSlotData(void)
{
  int i;
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, i) == TRUE)
      return i + 1;
  }
  return 0;
}

//------------------------------------------------------------------
/**
 * @brief	指定番号のスロットデータのタイプを返す
 * @param	index		スロットのインデックス番号
 * @return	int		MYSTERYGIFT_TYPE_xxxxx
 *
 * ※インデックス番号はFUSHIGIDATA_CheckSlotDataで返された値
*/
//------------------------------------------------------------------
int FUSHIGIDATA_GetSlotType(int index)
{
#if 0
  int i;
  GIFT_DELIVERY *dv;

  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, i) == TRUE){
      dv = FUSHIGIDATA_GetDeliData(_fushigi_ptr, i);
      return (int)dv->gift_type;
    }
  }
  return MYSTERYGIFT_TYPE_NONE;
#else
  GIFT_DELIVERY *dv;

  if(index == 0)	return MYSTERYGIFT_TYPE_NONE;    //k.ohno --を外に出した
  index--;
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, index) == TRUE){
    dv = FUSHIGIDATA_GetDeliData(_fushigi_ptr, index);
    if(dv){                              //k.ohno データが壊れてるとNULLがくる
      return (int)dv->gift_type;
    }
  }
  return MYSTERYGIFT_TYPE_NONE;
#endif
}


//------------------------------------------------------------------
/**
 * @brief	指定番号のスロット構造体へのポインタを返す
 * @param	index		スロットのインデックス番号
 * @return	GIFT_PRESENT	構造体へのポインタ
 *
 * ※インデックス番号はFUSHIGIDATA_CheckSlotDataで返された値
 */
//------------------------------------------------------------------
GIFT_PRESENT *FUSHIGIDATA_GetSlotPtr(int index)
{
  if(index){
    index--;                          // k.ohno 追
    return &_fushigi_ptr->delivery[index].data;
  }
  return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	指定のスロットを消去する
 * @param	index		スロットのインデックス番号
 * @return	NONE
 *
 * ※インデックス番号はFUSHIGIDATA_CheckSlotDataで返された値
 */
//------------------------------------------------------------------
void FUSHIGIDATA_RemoveSlot(int index)
{
  FUSHIGIDATA_RemoveDeliData(_fushigi_ptr, index);
}

//------------------------------------------------------------------


#include "system/gamedata.h"         //k.ohno デバッグ用に追加
#include "savedata/regulation.h"      //k.ohno デバッグ用に追加
#include "regulation_local.h"       //k.ohno デバッグ用に追加
#include "system/msgdata.h"         //k.ohno デバッグ用に追加
#include "msgdata/msg.naix"         //k.ohno デバッグ用に追加
#include "msgdata/msg_debug_mitsuhara.h"  //k.ohno デバッグ用に追加
#include "msgdata/msg_debug_ohno.h"  //k.ohno デバッグ用に追加
#include "poketool/pokeparty.h"   //k.ohno デバッグ用に追加

static POKEMON_PARAM* _createPokeParam(u32 heapID );

//------------------------------------------------------------------
/**
 * @brief	デバッグ用にポケモンデータをセットする関数
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_DebugSetPokemon(void)
{
  REGULATION _dummycup = {
        {EOM_}, // gmmからとってくる
        80,//レベルの合計８０まで
        3,//３匹
        30,//ポケモンのレベル３０まで
        -20,//身長制限２．０ｍいか
        -20,// 体重制限２０ｋｇいか
        0,// 進化ポケモン参加できない
        0,// 特別なポケモン参加できない
        0,// 同じポケモン参加できない
        0,// 同じ道具持たせられない
        0,// 固定ダメージ技が必ず失敗
    };
  int no;
  GIFT_DELIVERY gd;
  GIFT_PRESENT_ACCESSORY gpacc;
  GIFT_PRESENT_POKEMON po;
  POKEMON_PARAM* pp;
    
    
  if(_fushigi_ptr == NULL)	return;
  FUSHIGIDATA_Init(_fushigi_ptr);

  gd.gift_type = MYSTERYGIFT_TYPE_MEMBERSCARD;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  gd.gift_type = MYSTERYGIFT_TYPE_LETTER;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  gd.gift_type = MYSTERYGIFT_TYPE_WHISTLE;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

  // ぽけ 親自分
  gd.gift_type = MYSTERYGIFT_TYPE_POKEMON;
  po.parentType = MYSTERYPOKE_PARENTNAME_MY;
  pp = _createPokeParam(HEAPID_FIELD);
#if 0
  MI_CpuCopy8(pp, &po.monsno, PokemonParam_GetWorkSize());
#endif
  MI_CpuCopy8(&po, &gd.data, sizeof(GIFT_PRESENT_POKEMON));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  sys_FreeMemoryEz(pp);

  // ぽけ 親そのまま
  gd.gift_type = MYSTERYGIFT_TYPE_POKEMON;
#if 0
  po.parentType = MYSTERYPOKE_PARENTNAME_THROW;
#endif
  pp = _createPokeParam(HEAPID_FIELD);
#if 0
  MI_CpuCopy8(pp, &po.monsno, PokemonParam_GetWorkSize());
#endif
  MI_CpuCopy8(&po, &gd.data, sizeof(GIFT_PRESENT_POKEMON));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  sys_FreeMemoryEz(pp);

    // たまご
  gd.gift_type = MYSTERYGIFT_TYPE_RANGEREGG;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

#if 0

    // SEAL
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_SEAL;
  gpacc.accNo = 79;//爆発シール
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  // CLIP
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_CLIP;
  gpacc.accNo = 99;//ながれぼし
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
    // haikei
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_BG;
  gpacc.accNo = 2;//
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

    // ぽけっち
  gd.gift_type = MYSTERYGIFT_TYPE_POKETCH;
  no = 1; //POKETCH_APPID_STOPWATCH
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  {  // ダミーレギュレーション作成
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_mitsuhara_dat, HEAPID_FIELD);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_regulation_dummy );
    gd.gift_type = MYSTERYGIFT_TYPE_RULE;
    Regulation_SetCupName(&_dummycup,pStr);
    MI_CpuCopy8(&_dummycup, &gd.data, sizeof(REGULATION));
    FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
    MSGMAN_Delete(msgman);
    STRBUF_Delete(pStr);
  }

  gd.gift_type = MYSTERYGIFT_TYPE_ITEM;
  no = 80;
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

  gd.gift_type = MYSTERYGIFT_TYPE_GOODS;
  no = 33;
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

#endif

    
}

//----------------------------------------------------------------------------
/**
 *	@brief	デバッグ用にポケモンを作る関数
 *	@param	heapID		    作業HEAP
 *	@return p_pp		ポケモンパラム
 */
//-----------------------------------------------------------------------------

static STRBUF* _dummyGetGmm(int heapID, int no)
{
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, heapID);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_debugohno_name01+no );
    MSGMAN_Delete(msgman);
    return pStr;
}

// ポケモン
typedef struct {
  u32 monsno;			// モンスターナンバー
  u32 hp_rnd;			// HP乱数
  u32 at_rnd;			// 攻撃乱数
  u32 df_rnd;			// 防御乱数
  u32 sp_rnd;			// 速さ乱数
  u32 sa_rnd;			// 特攻乱数
  u32 sd_rnd;			// 特防乱数
  u32 speabino;			// 特殊能力
  u32	mons_id;		// ID
  u32 style;			// かっこよさ
  u32 beautiful;		// うつくしさ
  u32 cute;			// かわいさ
  u32 clever;			// かしこさ
  u32 strong;			// たくましさ
  u32 mons_rnd;			// 固体乱数
  u32 item;			// アイテム
  u32 oya_sex;			// 親性別
  u32 fur;			// 毛艶
  u32 world_code;		// 親の国コード
} _DEBUG_POKEMON;

static POKEMON_PARAM* _createPokeParam(u32 heapID )
{
	STRBUF* str;
    POKEMON_PARAM* p_pp = PokemonParam_AllocWork( heapID );
    int level = 5;
    int trade_no = 0; 
    static _DEBUG_POKEMON debug_pokemon_data = {
    63,				// モンスターナンバー(MONSNO_KEESHI)
    15,				// HP乱数
    15,				// 攻撃乱数
    15,				// 防御乱数
    20,				// 速さ乱数
    25,				// 特攻乱数
    25,				// 特防乱数
    28,				// 特殊能力(TOKUSYU_SINKURO)
    25643,			// ID
    0,				// かっこよさ
    0,				// うつくしさ
    0,				// かわいさ
    0,				// かしこさ
    0,				// たくましさ
    117,			// 固体乱数
    155,			// アイテム(オレンのみ)
    1,				// 親性別(女)
    0,				// 毛艶
    1,				// 親の国コード(LANG_JAPAN)
  };

    
//	PokeParaInit(p_pp);
	// モンスターナンバー　レベル　固体乱数　ID設定
	PokeParaSet( p_pp, 
			debug_pokemon_data.monsno,
			level, POW_RND, 
			RND_SET, debug_pokemon_data.mons_rnd,
			ID_SET, debug_pokemon_data.mons_id );

	// ニックネーム
	str = _dummyGetGmm(HEAPID_EVENT,trade_no);
	PokeParaPut( p_pp, ID_PARA_nickname_buf, str );
	STRBUF_Delete(str);

	// 各種乱数設定
	PokeParaPut( p_pp, ID_PARA_hp_rnd, &debug_pokemon_data.hp_rnd );
	PokeParaPut( p_pp, ID_PARA_pow_rnd, &debug_pokemon_data.at_rnd );
	PokeParaPut( p_pp, ID_PARA_def_rnd, &debug_pokemon_data.df_rnd );
	PokeParaPut( p_pp, ID_PARA_agi_rnd, &debug_pokemon_data.sp_rnd );
	PokeParaPut( p_pp, ID_PARA_spepow_rnd, &debug_pokemon_data.sa_rnd );
	PokeParaPut( p_pp, ID_PARA_spedef_rnd, &debug_pokemon_data.sd_rnd );

	// 特性
	PokeParaPut( p_pp, ID_PARA_speabino, &debug_pokemon_data.speabino );

	// かっこよさなど
	PokeParaPut( p_pp, ID_PARA_style, &debug_pokemon_data.style );
	PokeParaPut( p_pp, ID_PARA_beautiful, &debug_pokemon_data.beautiful );
	PokeParaPut( p_pp, ID_PARA_cute, &debug_pokemon_data.cute );
	PokeParaPut( p_pp, ID_PARA_clever, &debug_pokemon_data.clever );
	PokeParaPut( p_pp, ID_PARA_strong, &debug_pokemon_data.strong );
	
	// アイテム
	PokeParaPut( p_pp, ID_PARA_item, &debug_pokemon_data.item );

	// 親の名前
 	str = _dummyGetGmm(HEAPID_EVENT,trade_no);
	PokeParaPut( p_pp, ID_PARA_oyaname_buf, str );
	STRBUF_Delete(str);

	// 親の性別	
	PokeParaPut( p_pp, ID_PARA_oyasex, &debug_pokemon_data.oya_sex );

	// 国コード
	PokeParaPut( p_pp, ID_PARA_country_code, &debug_pokemon_data.world_code );
    return p_pp;
}



/*  */
