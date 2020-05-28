//============================================================================================
/**
 * @file	undergrounddata.c
 * @brief	地下アイテムデータアクセス用ソース
 * @author	k.ohno
 * @date	2006.2.21
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/undergrounddata.h"
#include "undergrounddata_local.h"

#include "field/ug_itemtype.h"
#include "../fielddata/base_goods/goods_id_def.h"
#include "itemtool/itemsym.h"
#include "system/pm_rtc.h"

//============================================================================================
//============================================================================================



u16 _convertList[] = {
    ITEM_MANMARUISI,         //まんまる	KASEKI_SUN
    ITEM_KANAMEISI,         //かなめ	KASEKI_SUN
    ITEM_TAIYOUNOISI,        //たいようのいし	KASEKI_SUN
    ITEM_HOSINOKAKERA,       //ほしのかけら	KASEKI_STAR
    ITEM_TUKINOISI,          //つきのいし	KASEKI_MOON
    ITEM_KATAIISI,           //かたいいし	KASEKI_HARD
    ITEM_KAMINARINOISI,      //かみなりのいし	KASEKI_KAMINARI
    ITEM_KAWARAZUNOISI,      //かわらずのいし	KASEKI_KAWARAZU
    ITEM_HONOONOISI,         //ほのおのいし	KASEKI_HONOO
    ITEM_MIZUNOISI,          //みずのいし	KASEKI_MIZU
    ITEM_RIIHUNOISI,         //リーフのいし	KASEKI_REAF
    ITEM_KINNOTAMA,          //きんのたま	KASEKI_GOLD
    ITEM_KAINOKASEKI,        //かいのカセキ	KASEKI_KAI
    ITEM_KOURANOKASEKI,      //こうらのカセキ	KASEKI_KOURA
    ITEM_TUMENOKASEKI,       //ツメのカセキ	KASEKI_TSUME
    ITEM_NEKKONOKASEKI,      //ねっこのカセキ	KASEKI_NEKKO
    ITEM_HIMITUNOKOHAKU,     //ひみつのコハク	KASEKI_KOHAKU
    ITEM_KITYOUNAHONE,          //きちょうなホネ	KASEKI_BONE
    ITEM_GENKINOKAKERA,   // げんきのかけら
    ITEM_GENKINOKATAMARI,  // げんきのかたまり
    ITEM_AKAIKAKERA,				// あかいかけら
    ITEM_AOIKAKERA,				// あおいかけら
    ITEM_KIIROIKAKERA,			// きいろいかけら
    ITEM_MIDORINOKAKERA,				// みどりのかけら
    ITEM_HAATONOUROKO,			// ハートのウロコ
    ITEM_TATENOKASEKI,				// たてのカセキ
    ITEM_ZUGAINOKASEKI,				// ずがいのカセキ
    ITEM_HIKARINONENDO,// ひかりのねんど
    ITEM_KUROITEKKYUU,				// くろいてっきゅう
    ITEM_TUMETAIIWA,				// つめたいいわ
    ITEM_SARASARAIWA,			// さらさらいわ
    ITEM_ATUIIWA,			// あついいわ
    ITEM_SIMETTAIWA,				// しめったいわ
    ITEM_HINOTAMAPUREETO,			// ひのたまプレート
    ITEM_SIZUKUPUREETO,			// しずくプレート
    ITEM_IKAZUTIPUREETO,				// いかずちプレート
    ITEM_MIDORINOPUREETO,				// みどりのプレート
    ITEM_TURARANOPUREETO,				// つららのプレート
    ITEM_KOBUSINOPUREETO,				// こぶしのプレート
    ITEM_MOUDOKUPUREETO,				// もうどくプレート
    ITEM_DAITINOPUREETO,				// だいちのプレート
    ITEM_AOZORAPUREETO,				// あおぞらプレート
    ITEM_HUSIGINOPUREETO,				// ふしぎのプレート
    ITEM_TAMAMUSIPUREETO,				// たまむしプレート
    ITEM_GANSEKIPUREETO,				// がんせきプレート
    ITEM_MONONOKEPUREETO,				// もののけプレート
    ITEM_RYUUNOPUREETO,				// りゅうのプレート
    ITEM_KOWAMOTEPUREETO,				// こわもてプレート
    ITEM_KOUTETUPUREETO,				// こうてつプレート
};

static void _addEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int add);


//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int UnderGroundData_GetWorkSize(void)
{
    return sizeof(UNDERGROUNDDATA);
}

//----------------------------------------------------------
/**
 * @brief	地下アイテムワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	UNDERGROUNDDATA*	取得したワークへのポインタ
 */
//----------------------------------------------------------
UNDERGROUNDDATA* UnderGroundData_AllocWork(u32 heapID)
{
	UNDERGROUNDDATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(UNDERGROUNDDATA));
	UnderGroundData_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	UNDERGROUNDDATAのコピー
 * @param	from	コピー元UNDERGROUNDDATAへのポインタ
 * @param	to		コピー先UNDERGROUNDDATAへのポインタ
 */
//----------------------------------------------------------
void UnderGroundData_Copy(const UNDERGROUNDDATA *pFrom, UNDERGROUNDDATA* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(UNDERGROUNDDATA));
}

//----------------------------------------------------------
/**
 * @brief	ワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int SecretBaseData_GetWorkSize(void)
{
	return sizeof(SECRETBASEDATA);
}

//----------------------------------------------------------
/**
 * @brief	地下ステータスワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	SECRETBASEDATA*	取得したワークへのポインタ
 */
//----------------------------------------------------------
SECRETBASEDATA* SecretBaseData_AllocWork(u32 heapID)
{
	SECRETBASEDATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(SECRETBASEDATA));
	SecretBaseData_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	レコード部分のワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int SecretBaseRecord_GetWorkSize(void)
{
	return sizeof(SB_RECORD_DATA);
}

//----------------------------------------------------------
/**
 * @brief	地下ステータスレコードワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	SB_RECORD_DATA*	取得したワークへのポインタ
 */
//----------------------------------------------------------
SB_RECORD_DATA* SecretBaseRecord_AllocWork(u32 heapID)
{
	SB_RECORD_DATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(SB_RECORD_DATA));
	MI_CpuFill8(reg, 0, sizeof(SB_RECORD_DATA));
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	SECRETBASEDATAのコピー
 * @param	from	コピー元SECRETBASEDATAへのポインタ
 * @param	to		コピー先SECRETBASEDATAへのポインタ
 */
//----------------------------------------------------------
void SecretBaseData_Copy(const SECRETBASEDATA *pFrom, SECRETBASEDATA* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(SECRETBASEDATA));
}


//============================================================================================
//
//	UNDERGROUNDDATA操作のための関数
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	地下ステータスデータの初期化
 * @param	pSBData		UNDERGROUNDDATAワークへのポインタ
 */
//----------------------------------------------------------
void UnderGroundData_Init(UNDERGROUNDDATA* pSBData)
{
    u32 randSeed = 0;
    RTCDate date;
    RTCTime time;

    GF_RTC_GetDateTime(&date, &time);
    randSeed = (((((((u32)date.year * 32ULL + date.month) * 32ULL)
                   + date.day) * 32ULL + time.hour) * 32ULL + time.minute)
                * 32ULL + (time.second + sys.vsync_counter));
    MI_CpuFill8(pSBData, 0, sizeof(UNDERGROUNDDATA));
    pSBData->randSeed = randSeed;
#ifdef DEBUG_ONLY_FOR_ohno

    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_DIAMOND, 10);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_PEARL, 10);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_RED, 20);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_BLUE, 20);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_GREEN, 20);

    UnderGroundAddGoodsBagItem(pSBData, GOODS_BOX01);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_TABLE02_2);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_CHAIR_L01);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_SHELF02);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_UG_POKE_22);
#endif
    pSBData->bNewDay = TRUE;
}


static int _getBagTreasureItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    for(i = 0;i < SECRETBASE_GOODS_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] != GOODS_INVALID ){
            return i;
        }
    }
    return -1;
}

static int _getBagGoodsItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] != GOODS_INVALID ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

static int _getFreeBagGoodsItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] == GOODS_INVALID ){
            return i;
        }
    }
    return -1;
}

static int _getFreeBagStoneItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] == STONE_TYPE_NONE ){ // 空き
            return i;
        }
    }
    return -1;
}

static int _getBagStoneItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] != STONE_TYPE_NONE ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

static int _getFreeBagTreasureItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] == STONE_TYPE_NONE ){
            return i;
        }
    }
    return -1;
}

static int _getFreeBagTrapItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] == UG_TRAPTYPE_NONE ){ // 空き
            return i;
        }
    }
    return -1;
}

static int _getBagTrapItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] != UG_TRAPTYPE_NONE ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

//----------------------------------------------------------
/**
 * @brief	地下データの日数に関係した処理
 * @param   pSave        セーブデータ構造体
 * @param	diff_days    経過日数
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataDayUpdate(SAVEDATA* pSave, int diff_days)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);
    MATHRandContext16 rand;
    u8 upper[]={0,2,2,4,4,5};
    u8 add[]={0,1,1,3,3,5};
    int day,dayMax,carat,type,i;
    
    if(diff_days <= 0){  // 負の日付更新にどうするかは不明
        return;
    }
    dayMax = diff_days;   // 玉の成長は９９までしかないのでそれ以上はカット
    if(diff_days > UG_STONE_CARAT_MAX){
        dayMax = UG_STONE_CARAT_MAX;
    }
    MATH_InitRand16(&rand, pUGData->randSeed);
    for(day = 0; day < dayMax; day++){
        for(i = 0; i < UG_STONE_PLACE_NUM_MAX; i++){
            if(pUGData->groundStoneType[i] != STONE_TYPE_NONE){
                type = pUGData->groundStoneType[i];
                carat = MATH_Rand16(&rand, upper[type]) + add[type];
                if((pUGData->groundStoneCaratAdd[i] + carat) < UG_STONE_CARAT_MAX){
                    pUGData->groundStoneCaratAdd[i] += carat;
                }
                else{
                    pUGData->groundStoneCaratAdd[i] = UG_STONE_CARAT_MAX;
                    break;
                }
            }
        }
    }
    pUGData->randSeed = gf_fix_rand(pUGData->randSeed + diff_days);
    pUGData->bNewDay = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	地下データの時間に関係した処理
 * @param   pSave        セーブデータ構造体
 * @param	diff_minute    経過分
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataMinUpdate(SAVEDATA* pSave, s32 diff_minute, BOOL bPenaltyMode)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if( (diff_minute < 0)  || (bPenaltyMode) ){  // 負には対応しないペナルティー時にはカウントしない
        return;
    }
    if( pUGData->sendGoodsMinTimer < diff_minute ) {
        pUGData->sendGoodsMinTimer = 0;
    }
    else{
        pUGData->sendGoodsMinTimer -= diff_minute;
    }
}

//----------------------------------------------------------
/**
 * @brief	地下データのロード直後に呼ぶ処理
 * @param   pSave        セーブデータ構造体
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataLoadUpdate(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if((pUGData->sendGoodsMinTimer == 0) &&
       (pUGData->sendGoodsSaveInfo == _GOODS_SEND_NOT)){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NONE;
    }
    if((pUGData->sendGoodsMinTimer == 0) &&
       (pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN)){
        pUGData->sendGoodsMinTimer = _PENALTY_TIME;
    }
    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NOT;
    }
}

//----------------------------------------------------------
/**
 * @brief	地下に行くSAVE前に呼ぶ処理
 * @param   pSave        セーブデータ構造体
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataBeforeUGSave(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_NONE){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_UNDERIN;
    }
}

//----------------------------------------------------------
/**
 * @brief	地下から抜け出す場合の処理
 * @param   pSave        セーブデータ構造体
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataAfterUG(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NONE;
    }
}

//----------------------------------------------------------
/**
 * @brief	グッズをあげられる状態かどうか
 * @param   pSave        セーブデータ構造体
 * @return	none
 */
//----------------------------------------------------------

BOOL UnderGroundDataIsGoodsSend(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_NOT){
        return FALSE;
    }
    return TRUE;
}


//----------------------------------------------------------
/**
 * @brief	地上でディアルガかパルキアを倒した時にONにする
 * @param   pUGData        地下データ構造体
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundSetDiamondPearlEvent(UNDERGROUNDDATA* pUGData)
{
    pUGData->groundStoneGetBit = TRUE;
}

BOOL UnderGroundIsDiamondPearlEvent(UNDERGROUNDDATA* pUGData)
{
    return pUGData->groundStoneGetBit;
}

//----------------------------------------------------------
/**
 * @brief	旗を追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	pMyStatus    とった人のMYSTATUS
 * @return	none   必ず成功する
 */
//----------------------------------------------------------

void UnderGroundAddFlag(UNDERGROUNDDATA* pUGData, const MYSTATUS* pMyStatus)
{
	int i = pUGData->newFlagNo;

    GF_ASSERT_RETURN(i < UG_FLAG_NUM_MAX,);
    MI_CpuCopy8(MyStatus_GetMyName(pMyStatus), pUGData->name[i], (sizeof(STRCODE) * (PERSON_NAME_SIZE+EOM_SIZE)));
    pUGData->id[i] = MyStatus_GetID(pMyStatus);
    pUGData->region_code[i] = MyStatus_GetRegionCode(pMyStatus);
    pUGData->rom_code[i] = MyStatus_GetRomCode(pMyStatus);
    pUGData->newFlagNo++;
    if(pUGData->newFlagNo >= UG_FLAG_NUM_MAX){
        pUGData->newFlagNo = 0;
    }
}

//----------------------------------------------------------
/**
 * @brief	旗を読み込む
 * @param   pUGData      地下アイテムデータ構造体
 * @param   heapID       HEAP
 * @param	index        取り出す順番
 * @return	MYSTATUS*    空の場合はNULL
 */
//----------------------------------------------------------

MYSTATUS* UnderGroundGetFlag(const UNDERGROUNDDATA* pUGData,int heapID,int index)
{
    int size = (sizeof(STRCODE) * (PERSON_NAME_SIZE+EOM_SIZE));
    int i;
    MYSTATUS* pMy;
    int no = pUGData->newFlagNo - index - 1;

    if(no < 0){
        no += UG_FLAG_NUM_MAX;
    }
    if(pUGData->name[no][0] != 0){
        pMy = MyStatus_AllocWork(heapID);
        MyStatus_SetMyName(pMy, pUGData->name[no]);
        MyStatus_SetRomCode(pMy, pUGData->rom_code[no]);
        MyStatus_SetRegionCode(pMy, pUGData->region_code[no]);
        MyStatus_SetID(pMy, pUGData->id[no]);
        return pMy;
    }
    return NULL;
}


//----------------------------------------------------------
/**
 * @brief	日によって変わる乱数シードを得る
 * @param   pUGData      地下アイテムデータ構造体
 * @return	日によって変わる乱数シード
 */
//----------------------------------------------------------
u32 UnderGroundGetDayRandSeed(UNDERGROUNDDATA* pUGData)
{
    return pUGData->randSeed;
}

//----------------------------------------------------------
/**
 * @brief	宝袋からアイテムを取り出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	bDelete      実際に取り出してここから無くなる場合TRUE 読みだけの場合FALSE
 * @return	ITEM_TYPE 空になったら ITEM_DUMMY_DATA
 */
//----------------------------------------------------------
int UnderGroundGetTreasureBagItem(UNDERGROUNDDATA* pUGData, BOOL bDelete)
{
    int i = _getBagTreasureItemIndex(pUGData);
    int ugitem;

    if(i == -1){
        return ITEM_DUMMY_DATA;
    }
    ugitem = pUGData->bagTreasure[i];
    GF_ASSERT_RETURN(DIG_PARTS_TREASURE_MIN <= ugitem, ITEM_HUTOIHONE);
    GF_ASSERT_RETURN(ugitem < DIG_PARTS_TREASURE_MAX, ITEM_HUTOIHONE);
    ugitem -= DIG_PARTS_TREASURE_MIN;
    if(bDelete){
        pUGData->bagTreasure[i] = DIG_PARTS_NONE;  // 消す
    }
    return _convertList[ugitem];
}

//----------------------------------------------------------
/**
 * @brief	おたから＞アイテム変換
 * @return	ITEM_TYPE 空になったら ITEM_DUMMY_DATA
 */
//----------------------------------------------------------
int UnderGroundTreasureItem2Item(int treasureType)
{
    GF_ASSERT_RETURN(DIG_PARTS_TREASURE_MIN <= treasureType, ITEM_HUTOIHONE);
    GF_ASSERT_RETURN(treasureType < DIG_PARTS_TREASURE_MAX, ITEM_HUTOIHONE);
    treasureType -= DIG_PARTS_TREASURE_MIN;
    return _convertList[treasureType];
}

//----------------------------------------------------------
/**
 * @brief	パソコンのグッズへ追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	goodsNo      グッズ番号
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo)
{
    int i;

    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            pUGData->pcGoods[i] = goodsNo;
            return TRUE;
        }
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	パソコンのグッズへ追加できるかチェック
 * @param   pUGData      地下アイテムデータ構造体
 * @param	goodsNo      グッズ番号(ダミー）
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddChkGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo)
{
    int i;

    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            return TRUE;
        }
    }
    return FALSE;
}



//----------------------------------------------------------
/**
 * @brief	パソコンにグッズがいくつ入っているか確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @return	グッズ数
 */
//----------------------------------------------------------
int UnderGroundGetNumGoodsPCItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	パソコンのグッズを確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	グッズ番号 無い場合は GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundGetGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->pcGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	パソコンからグッズをとりだす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @param	goodsIndex      配置の順番
 * @return	グッズ番号 無い場合は GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundDelGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    // 飾っているものを引き出せないのであらかじめ検査すること
    GF_ASSERT_RETURN(!UnderGroundIsEntryGoodsPCItem(pUGData, listIndex),);

    ix = listIndex;
    type = pUGData->pcGoods[ix];
    for(i = ix ; i < UG_ITEM_PC_NUM_MAX-1; i++){
        pUGData->pcGoods[i] = pUGData->pcGoods[i+1];
    }
    pUGData->pcGoods[UG_ITEM_PC_NUM_MAX-1] = GOODS_INVALID;

    _addEntryGoodsPCItem(pUGData, listIndex, -1); //エントリー順番を下げる
    return type;
}

//----------------------------------------------------------
/**
 * @brief	パソコンのグッズを順番変更
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       今の位置
 * @param	nextIndex       今度の位置
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeGoodsPcItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0,change = -1;
    u8 pcGoods[UG_ITEM_PC_NUM_MAX];

    MI_CpuCopy8(pUGData->pcGoods,pcGoods,UG_ITEM_PC_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_PC_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->pcGoods[j] = pcGoods[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->pcGoods[j] = pcGoods[listIndex];
            j++;
        }
    }

    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] == (listIndex+1)){
            change = i;
            break;
        }
    }
	
	_addEntryGoodsPCItem(pUGData, nextIndex, 1); //エントリー順番をあげる
    _addEntryGoodsPCItem(pUGData, listIndex, -1); //エントリー順番を下げる
    
    if(change != -1){
        if(listIndex<nextIndex){
            pUGData->secretBasePlace[ change ] = nextIndex+1;
        }
        else{
            pUGData->secretBasePlace[ change ] = nextIndex+2;
        }
    }
}


//----------------------------------------------------------
/**
 * @brief	パソコンからグッズを飾る為にとりだす
 *          実際には取り出さず、マークをつけます
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @param	goodsIndex      配置の順番
 * @return	グッズ番号 無い場合は GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int goodsIndex)
{
    int i,ix;

    GF_ASSERT_RETURN(goodsIndex >= SECRETBASE_PC_NUM_MAX, GOODS_INVALID);
    GF_ASSERT_RETURN(goodsIndex <= SECRETBASE_GOODS_NUM_MAX, GOODS_INVALID);
    pUGData->secretBasePlace[goodsIndex - SECRETBASE_PC_NUM_MAX] = listIndex + 1;
    return pUGData->pcGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	リスト番号のアイテムが飾られているかどうかを返します
 * @param   pUGData       地下アイテムデータ構造体
 * @param	listIndex     メニューリストの順番 UnderGroundEntryGoodsPCItemで渡したものと同じ
 * @return	飾っている場合TRUE
 */
//----------------------------------------------------------

BOOL UnderGroundIsEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i;
    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] == (listIndex+1)){
            return TRUE;
        }
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	パソコンへ飾ってあったグッズをもどす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	goodsIndex	グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundTrashGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsIndex)
{
    if((goodsIndex - SECRETBASE_PC_NUM_MAX) >= SECRETBASE_GOODS_NUM_MAX){
        return;
    }
    pUGData->secretBasePlace[goodsIndex - SECRETBASE_PC_NUM_MAX] = 0;
}

//----------------------------------------------------------
/**
 * @brief	パソコンへ飾ってあったグッズを全部もどす
 * @param   pUGData      地下アイテムデータ構造体
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundTrashAllGoodsPCItem(UNDERGROUNDDATA* pUGData)
{
    MI_CpuFill8(pUGData->secretBasePlace, 0, SECRETBASE_GOODS_NUM_MAX);
}

//----------------------------------------------------------
/**
 * @brief	かざってあるデータindexをaddします
 * @param   pUGData       地下アイテムデータ構造体
 * @param	listIndex     このアイテムを抜き出したので　これ以降のindexを変更
 * @return	none
 */
//----------------------------------------------------------

static void _addEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int add)
{
    int i;
    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] > (listIndex+1)){
            pUGData->secretBasePlace[ i ] += add;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	バッグにグッズがいくつ入っているか確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @return	グッズ数
 */
//----------------------------------------------------------
int UnderGroundGetNumGoodsBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] == GOODS_INVALID ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	バッグのグッズを確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	グッズ番号 無い場合は UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	バッグからグッズをとりだす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @return	グッズ番号 無い場合は UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagGoods[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagGoods[i] = pUGData->bagGoods[i+1];
    }
    pUGData->bagGoods[UG_ITEM_BAG_NUM_MAX-1] = GOODS_INVALID;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	バッグへグッズを追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	goodsType    グッズType
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType)
{
    int i;

    i = _getFreeBagGoodsItemIndex(pUGData);
    if(i != -1){
        pUGData->bagGoods[i] = goodsType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	バッグへグッズを追加可能かチェック
 * @param   pUGData      地下アイテムデータ構造体
 * @param	goodsType    グッズType
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddChkGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType)
{
    int i;

    i = _getFreeBagGoodsItemIndex(pUGData);
    if(i != -1){
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	バッグのグッズを順番変更
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       今の位置
 * @param	nextIndex       今度の位置
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagGoods[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagGoods,bagGoods,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagGoods[j] = bagGoods[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagGoods[j] = bagGoods[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	かばんにたまがいくつ入っているか確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @return	たま数
 */
//----------------------------------------------------------
int UnderGroundGetNumStoneBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] == STONE_TYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	かばんのたまを確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	たま番号 無い場合は STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagStone[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	かばんのたまのおおきさを確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	たまCarat番号 無い場合は1
 */
//----------------------------------------------------------
int UnderGroundGetStoneCaratBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagStoneCarat[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	かばんからたまをとりだす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @param	goodsIndex      配置の順番
 * @return	たま番号 無い場合は STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagStone[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagStone[i] = pUGData->bagStone[i+1];
        pUGData->bagStoneCarat[i] = pUGData->bagStoneCarat[i+1];
    }
    pUGData->bagStone[UG_ITEM_BAG_NUM_MAX-1] = STONE_TYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	かばんたまいれへ追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	stoneType    タマType
 * @param	carat        タマの大きさ
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddStoneBagItem(UNDERGROUNDDATA* pUGData, int stoneType, int carat)
{
    int i;

    i = _getFreeBagStoneItemIndex(pUGData);
    if(i != -1){
        pUGData->bagStone[i] = stoneType;
        pUGData->bagStoneCarat[i] = carat;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	バッグのたまを順番変更
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       今の位置
 * @param	nextIndex       今度の位置
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagStone[UG_ITEM_BAG_NUM_MAX];
    u8 bagStoneCarat[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagStone,bagStone,UG_ITEM_BAG_NUM_MAX);
    MI_CpuCopy8(pUGData->bagStoneCarat,bagStoneCarat,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagStone[j] = bagStone[i];
            pUGData->bagStoneCarat[j] = bagStoneCarat[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagStone[j] = bagStone[listIndex];
            pUGData->bagStoneCarat[j] = bagStoneCarat[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	バッグにおたからがいくつ入っているか確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @return	おたから数
 */
//----------------------------------------------------------
int UnderGroundGetNumTreasureBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] == STONE_TYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	バッグのおたからを確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	おたから番号 無い場合は STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetTreasureBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagTreasure[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	バッグからおたからをとりだす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @param	goodsIndex      配置の順番
 * @return	おたから番号 無い場合は STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagTreasure[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagTreasure[i] = pUGData->bagTreasure[i+1];
    }
    pUGData->bagTreasure[UG_ITEM_BAG_NUM_MAX-1] = STONE_TYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	バッグへおたからを追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	treasureType    おたからType
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddTreasureBagItem(UNDERGROUNDDATA* pUGData, int treasureType)
{
    int i;

    i = _getFreeBagTreasureItemIndex(pUGData);
    if(i != -1){
        pUGData->bagTreasure[i] = treasureType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	バッグのおたからを順番変更
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       今の位置
 * @param	nextIndex       今度の位置
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagTreasure[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagTreasure,bagTreasure,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagTreasure[j] = bagTreasure[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagTreasure[j] = bagTreasure[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	バッグに罠がいくつ入っているか確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @return	罠数
 */
//----------------------------------------------------------
int UnderGroundGetNumTrapBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] == UG_TRAPTYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	バッグの罠を確認する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index      0～の連番  
 * @return	罠番号 無い場合は UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetTrapBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i;

    return pUGData->bagTrap[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	バッグから罠をとりだす
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       メニューリストの順番
 * @return	罠番号 無い場合は UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagTrap[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagTrap[i] = pUGData->bagTrap[i+1];
    }
    pUGData->bagTrap[UG_ITEM_BAG_NUM_MAX-1] = UG_TRAPTYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	バッグへ罠を追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	treasureType    罠Type
 * @return	入らなかったらFALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddTrapBagItem(UNDERGROUNDDATA* pUGData, int trapType)
{
    int i;

    i = _getFreeBagTrapItemIndex(pUGData);
    if(i != -1){
        pUGData->bagTrap[i] = trapType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	バッグの罠を順番変更
 * @param   pUGData      地下アイテムデータ構造体
 * @param	listIndex       今の位置
 * @param	nextIndex       今度の位置
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagTrap[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagTrap,bagTrap,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagTrap[j] = bagTrap[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagTrap[j] = bagTrap[listIndex];
            j++;
        }
    }
}


#define UG_TRAP_PLACE_NUM_MAX (16)  // 配置する罠の最大数
//----------------------------------------------------------
/**
 * @brief	地面へ自然の罠を追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	trapType    罠Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,);
    pUGData->groundNatureTrapType[index]=trapType;
    pUGData->groundNatureTrapPos[index][0] = x;
    pUGData->groundNatureTrapPos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundNatureTrapPos[index][2] = z;
}

//----------------------------------------------------------
/**
 * @brief	地面へから罠タイプを引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠タイプ
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    return pUGData->groundNatureTrapType[index];
}

//----------------------------------------------------------
/**
 * @brief	地面から罠X座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠X座標
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos;
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    pos = pUGData->groundNatureTrapPos[index][0];
    pos += (pUGData->groundNatureTrapPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から罠Z座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠Z座標
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos;
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    pos = pUGData->groundNatureTrapPos[index][2];
    pos += (pUGData->groundNatureTrapPos[index][1] << 4) & 0xf00;
    return pos;
}


//----------------------------------------------------------
/**
 * @brief	自然の罠を消す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	trapType    罠Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundDelNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int index)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,);
    pUGData->groundNatureTrapType[index] = UG_TRAPTYPE_NONE;
    MI_CpuClear8(pUGData->groundNatureTrapPos[index],3);
}

//----------------------------------------------------------
/**
 * @brief	地面へ罠を追加する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	trapType    罠Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z,int order)
{
    GF_ASSERT_RETURN(index < UG_TRAP_PLACE_NUM_MAX,);
    pUGData->groundTrapType[index]=trapType;
    pUGData->groundTrapPos[index][0] = x;
    pUGData->groundTrapPos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundTrapPos[index][2] = z;
    pUGData->groundTrapOrder[index]=order;
}

//----------------------------------------------------------
/**
 * @brief	地面へから罠タイプを引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠タイプ
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundTrapType[index];
}

//----------------------------------------------------------
/**
 * @brief	地面から罠X座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠X座標
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundTrapPos[index][0];

    pos += (pUGData->groundTrapPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から罠Z座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠Z座標
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundTrapPos[index][2];

    pos += (pUGData->groundTrapPos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から生成順番を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	order
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemOrder(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundTrapOrder[index];
}


//----------------------------------------------------------
/**
 * @brief	地面へ石をうめる
 * @param   pUGData      地下アイテムデータ構造体
 * @param	stoneType    石Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat, int addCarat)
{
    GF_ASSERT_RETURN(index < UG_STONE_PLACE_NUM_MAX,);
    pUGData->groundStoneType[index] = stoneType;
    pUGData->groundStonePos[index][0] = x;
    pUGData->groundStonePos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundStonePos[index][2] = z;
    pUGData->groundStoneCarat[index] = carat;
    pUGData->groundStoneCaratAdd[index] = addCarat;
}

//----------------------------------------------------------
/**
 * @brief	地面へ石を埋める  埋めるときには成長が０
 * @param   pUGData      地下アイテムデータ構造体
 * @param	stoneType    石Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundBuryStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat)
{
    UnderGroundAddStoneGroundItem(pUGData, stoneType, index, x, z, carat, 0);
}

//----------------------------------------------------------
/**
 * @brief	地面へから石タイプを引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	罠タイプ
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneType[index];
}

//----------------------------------------------------------
/**
 * @brief	地面から石X座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石X座標
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundStonePos[index][0];

    pos += (pUGData->groundStonePos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から石Z座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石Z座標
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundStonePos[index][2];

    pos += (pUGData->groundStonePos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から石の大きさを引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石の大きさ
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCarat(UNDERGROUNDDATA* pUGData,int index)
{
    int carat = pUGData->groundStoneCarat[index]+pUGData->groundStoneCaratAdd[index];

    if(carat > UG_STONE_CARAT_MAX){
        carat = UG_STONE_CARAT_MAX;
    }
    return carat;
}

//----------------------------------------------------------
/**
 * @brief	地面から石のオリジナルの大きさを引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石の大きさ
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCaratOrg(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneCarat[index];
}

//----------------------------------------------------------
/**
 * @brief	地面から石の増加分を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石の大きさ
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCaratMul(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneCaratAdd[index];
}

//----------------------------------------------------------
/**
 * @brief	地面へ化石を記録する
 * @param   pUGData      地下アイテムデータ構造体
 * @param	x,z  位置だけ記憶
 * @return	index
 */
//----------------------------------------------------------
int UnderGroundAddFossilGroundItem(UNDERGROUNDDATA* pUGData, int x,int z)
{
    int i;
    
    for(i = 0;i < UG_FOSSIL_PLACE_NUM_MAX;i++){
        if((pUGData->groundFossilPos[i][0] == 0) &&
           (pUGData->groundFossilPos[i][1] == 0) &&
           (pUGData->groundFossilPos[i][2] == 0) ){
            pUGData->groundFossilPos[i][0] = x;
            pUGData->groundFossilPos[i][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
            pUGData->groundFossilPos[i][2] = z;
            return i;
        }
    }
    return 0;
}

//----------------------------------------------------------
/**
 * @brief	化石データを消去
 * @param   pUGData      地下アイテムデータ構造体
 * @param	x,z  位置だけ記憶
 * @return	index
 */
//----------------------------------------------------------
void UnderGroundDelFossilGroundItem(UNDERGROUNDDATA* pUGData, int index)
{
    GF_ASSERT_RETURN(index < UG_FOSSIL_PLACE_NUM_MAX,);
    MI_CpuFill8( pUGData->groundFossilPos[index] , 0, 3);
}

//----------------------------------------------------------
/**
 * @brief	地面から石X座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石X座標
 */
//----------------------------------------------------------

int UnderGroundGetFossilGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundFossilPos[index][0];

    pos += (pUGData->groundFossilPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	地面から石Z座標を引き出す
 * @param   pUGData      地下アイテムデータ構造体
 * @param	index  記憶バッファの順番
 * @return	石Z座標
 */
//----------------------------------------------------------

int UnderGroundGetFossilGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundFossilPos[index][2];

    pos += (pUGData->groundFossilPos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	化石を掘るのは初めてかどうか
 * @param   pUGData      地下アイテムデータ構造体
 * @return	TRUEなら化石配置
 */
//----------------------------------------------------------

BOOL UnderGroundIsFirstFossil(UNDERGROUNDDATA* pUGData)
{
    return (pUGData->bFossilFirst==FALSE);
}

//----------------------------------------------------------
/**
 * @brief	化石を掘るのは初めてFLGをON
 * @param   pUGData      地下アイテムデータ構造体
 * @return	TRUEなら化石配置
 */
//----------------------------------------------------------

void UnderGroundSetFirstFossil(UNDERGROUNDDATA* pUGData)
{
    pUGData->bFossilFirst = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	化石を新しく配置するかどうか
 * @param   pUGData      地下アイテムデータ構造体
 * @return	TRUEなら化石配置
 */
//----------------------------------------------------------

BOOL UnderGroundIsNewDay(UNDERGROUNDDATA* pUGData)
{
    return pUGData->bNewDay;
}

//----------------------------------------------------------
/**
 * @brief	化石を配置し終わったらフラグを消去
 * @param   pUGData      地下アイテムデータ構造体
 * @return  none
 */
//----------------------------------------------------------

void UnderGroundResetNewDay(UNDERGROUNDDATA* pUGData)
{
    pUGData->bNewDay = FALSE;
}

//----------------------------------------------------------
/**
 * @brief	掘った化石を記録 （レアプレートだけ記憶）
 * @param   pUGData      地下アイテムデータ構造体
 * @param   type         掘った化石種類
 * @return  none
 */
//----------------------------------------------------------

void UnderGroundSetFossilDig(UNDERGROUNDDATA* pUGData,int type)
{
    if((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON)){
        return;
    }
    pUGData->digBit |= (0x0001 << (type - DIG_PARTS_PLATE_FIRE));
}

//----------------------------------------------------------
/**
 * @brief	この化石を出してよいのか検査
 * @param   pUGData      地下アイテムデータ構造体
 * @param   type         掘った化石種類
 * @return  none
 */
//----------------------------------------------------------

BOOL UnderGroundIsFossilAdvent(UNDERGROUNDDATA* pUGData,int type)
{
    if((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON)){
        return TRUE;
    }
    if((pUGData->digBit & (0x0001 << (type - DIG_PARTS_PLATE_FIRE))) ){
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	地下を歩いた歩数をカウント
 * @param   pUGData      地下アイテムデータ構造体
 * @return	order
 */
//----------------------------------------------------------

void UnderGroundCountWalk(UNDERGROUNDDATA* pUGData)
{
    if(pUGData->walk >= (_MAX_WALK_COUNT-1)){
        pUGData->walk = 0;
    }
    else{
        pUGData->walk++;
    }
}

//----------------------------------------------------------
/**
 * @brief	地下を歩いた歩数を引き出す（１００歩でリセット）
 * @param   pUGData      地下アイテムデータ構造体
 * @return	歩数
 */
//----------------------------------------------------------

int UnderGroundGetWalkNum(UNDERGROUNDDATA* pUGData)
{
    return pUGData->walk;
}

//----------------------------------------------------------
/**
 * @brief	地下ステータスデータの初期化
 * @param	pSBData		SECRETBASEDATAワークへのポインタ
 */
//----------------------------------------------------------
void SecretBaseData_Init(SECRETBASEDATA* pSBData)
{
	MI_CpuFill8(pSBData, 0, sizeof(SECRETBASEDATA));
}

//----------------------------------------------------------
/**
 * @brief	地下ステータスデータの初期化(レコード以外)
 * @param	pSBData		SECRETBASEDATAワークへのポインタ
 */
//----------------------------------------------------------

void SecretBaseData_Reform(SECRETBASEDATA* pSBData)
{
    MI_CpuClear8(pSBData->goodsPos,SECRETBASE_GOODS_NUM_MAX*sizeof(SB_GOODS));
    MI_CpuClear8(pSBData->rockPos,SECRETBASE_LOCK_NUM_MAX*sizeof(SB_LOCK));
    pSBData->xpos=0;         // ドアの位置
    pSBData->zpos=0;
    pSBData->dir=0;        // 外に出てるドアの方向
    pSBData->bMake=0;     //  作ったかどうか
}

//----------------------------------------------------------
/**
 * @brief	秘密基地を一時的に消す
 * @param	pSBData	 SECRETBASEDATAワークポインタ
 */
//----------------------------------------------------------

void SecretBaseData_SetMakeDown(SECRETBASEDATA* pSBData)
{
    pSBData->bMake = FALSE;     //  作ったかどうか
}

//----------------------------------------------------------
/**
 * @brief	グッズの位置を設定する  消す場合には全部０    廃止予定
 * @param	pSBData	 SECRETBASEDATAワークポインタ
 * @param	goodsIndex	グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @param   type    グッズタイプ
 * @param	x,z      位置
 */
//----------------------------------------------------------
void SecretBaseData_SetGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int type, int x, int z)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,);
    GF_ASSERT_RETURN(x < 32,);
    GF_ASSERT_RETURN(z < 32,);
    GF_ASSERT_RETURN(pSBData,);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return;  // パソコンの位置は要らない
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // グッズが入っている
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].x = x;
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].z = z;
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].type = type;
    }
    else{  // 残りは岩
        pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x = x;
        pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z = z;
    }
}

//----------------------------------------------------------
/**
 * @brief	グッズの位置を変更する  消す場合には全部０
 * @param	pSBData	 SECRETBASEDATAワークポインタ
 * @param	goodsIndex	グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @param	x,z      位置
 */
//----------------------------------------------------------
void SecretBaseData_ChangeGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int x, int z)
{
    int type = SecretBaseData_GetGoodsType(pSBData, goodsIndex);
    SecretBaseData_SetGoodsPosition(pSBData, goodsIndex, type, x, z);
}

//----------------------------------------------------------
/**
 * @brief	パソコンのtypeを得る
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @return 	グッズタイプ+パソコンタイプ
 */
//----------------------------------------------------------

static int _getPCType(const SECRETBASEDATA* pSBData)
{
    int num = pSBData->recordData.flagDeliveryCount;
    
    if(FLAG_PLATINA_LV_NUM <= num){
        return GOODS_FLAG_PLATINA_PC;
    }
    else if(FLAG_GOLD_LV_NUM <= num){
        return GOODS_FLAG_GOLD_PC;
    }
    else if(FLAG_SILVER_LV_NUM <= num){
        return GOODS_FLAG_SILVER_PC;
    }
    else if(FLAG_BRONZE_LV_NUM <= num){
        return GOODS_FLAG_BRONZE_PC;
    }
    return GOODS_FLAG_NORMAL_PC;
}

//----------------------------------------------------------
/**
 * @brief	グッズtypeを得る
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @param	goodsIndex	  グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	グッズタイプ
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsType(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,GOODS_INVALID);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _getPCType(pSBData);
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // グッズが入っている
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].type;
    }
    else if( (pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x != _INVALID_POS)
             && (pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z != _INVALID_POS) ){
        // 残りは岩
        return GOODS_BIG_ROCK;
    }
    return GOODS_INVALID;
}

//----------------------------------------------------------
/**
 * @brief	グッズx位置を得る
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @param	goodsIndex	  グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	グッズx座標
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsXPos(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,_PCPOS_X);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _PCPOS_X;
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // グッズが入っている
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].x;
    }
      // 残りは岩
    return pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x;
}

//----------------------------------------------------------
/**
 * @brief	グッズz位置を得る
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @param	goodsIndex	  グッズの順番 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	グッズz座標
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsZPos(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,_PCPOS_Z);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _PCPOS_Z;
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // グッズが入っている
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].z;
    }
    // 残りは岩
    return pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z;
}

//----------------------------------------------------------
/**
 * @brief	岩をどのくらい保持していないといけないかを返す
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @return 	岩保持数
 */
//----------------------------------------------------------
int SecretBaseData_GetPlaceRockLimit(const SECRETBASEDATA* pSBData)
{
    if(pSBData->recordData.flagDeliveryCount >=  FLAG_PLATINA_LV_NUM){
        return 0;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_GOLD_LV_NUM){
        return 6;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_SILVER_LV_NUM){
        return 11;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_BRONZE_LV_NUM){
        return 15;
    }
    return 16;
}

//----------------------------------------------------------
/**
 * @brief	配置物をいくつまで置いていいのかを返す
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @return 	置いていいグッズの数
 */
//----------------------------------------------------------
int SecretBaseData_GetPlaceGoodsLimit(const SECRETBASEDATA* pSBData)
{
    if(pSBData->recordData.flagDeliveryCount >=  FLAG_PLATINA_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_GOLD_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_SILVER_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_BRONZE_LV_NUM){
        return 12;
    }
    return 10;
}

//==============================================================================
/**
 * ちかポイント	旗をとったり、罠にかけたときにもらえるポイント。
 * @param   none
 * @retval  ちかポイント
 */
//==============================================================================
int SecretBaseRecordGetPoint(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->pointCount;
}

//==============================================================================
/**
 * 地下称号をえる
 * @param   none
 * @retval  ちかRANK
 */
//==============================================================================
int SecretBaseRecordGetUGRank(const SB_RECORD_DATA* pSBRecord)
{

    if(4 == SecretBaseRecordGetFlagType(pSBRecord)){
        return UG_RANK_MASTER;
    }
    return UG_RANK_BEGINNER;
}


//==============================================================================
/**
 * ちかポイント	旗をとったり、罠にかけたときにもらえるポイント加算
 * @param   add  加算  か 減算ポイント
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetPoint(SB_RECORD_DATA* pSBRecord, int add)
{
    pSBRecord->pointCount = add;
}

//==============================================================================
/**
 * であった人の人数	通信相手と話した回数です。同じ人でも１０回までカウントします。
 * @param   none
 * @retval  であった人の人数
 */
//==============================================================================
int SecretBaseRecordGetTalkNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->talkCount;
}

//==============================================================================
/**
 * であった人の人数	通信相手と話した回数です。同じ人でも１０回までカウントします。
 * @param   
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetTalkNum(SB_RECORD_DATA* pSBRecord, int meetNetID)
{
    if(pSBRecord->talkCount < _MAX){
        pSBRecord->talkCount++;
    }
}

//==============================================================================
/**
 * 道具をあげた回数	誰かに道具を上げた回数。同じ人にあげてもカウントします。
 * @param   
 * @retval  none
 */
//==============================================================================
int SecretBaseRecordGetSendItemNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->sendItemCount;
}

//==============================================================================
/**
 * 道具をあげた回数	誰かに道具を上げた回数。同じ人にあげてもカウントします。
 * @param   
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetSendItemNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->sendItemCount < _MAX){
        pSBRecord->sendItemCount++;
    }
}

//==============================================================================
/**
 * ハタをとった回数	相手のハタをとった回数です。同じ人でもカウントします。
 * @param   none
 * @retval  ハタをとった回数
 */
//==============================================================================
int SecretBaseRecordGetFlagConquerNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagConquerCount;
}

//==============================================================================
/**
 * ハタをとった回数	相手のハタをとった回数です。同じ人でもカウントします。
 * @param   none
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFlagConquerNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagConquerCount < _MAX){
        pSBRecord->flagConquerCount++;
    }
}

//----------------------------------------------------------
/**
 * @brief	パソコンの旗のtypeを得る
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @return 	ハタランク
 */
//----------------------------------------------------------

int SecretBaseRecordGetFlagType(const SB_RECORD_DATA* pSBRecord)
{
    int num = pSBRecord->flagDeliveryCount;
    
    if(FLAG_PLATINA_LV_NUM <= num){
        return 4;
    }
    else if(FLAG_GOLD_LV_NUM <= num){
        return 3;
    }
    else if(FLAG_SILVER_LV_NUM <= num){
        return 2;
    }
    else if(FLAG_BRONZE_LV_NUM <= num){
        return 1;
    }
    return 0;
}

//==============================================================================
/**
 * ハタを納品した回数	相手のハタを納品した回数です。同じ人でもカウントします。
 * @param   none
 * @retval  none
 */
//==============================================================================
int SecretBaseRecordGetFlagDeliveryNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagDeliveryCount;
}

//==============================================================================
/**
 * ハタを納品した回数	相手のハタを納品した回数です。同じ人でもカウントします。
 * @param   none
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagDeliveryCount < _MAX){
        pSBRecord->flagDeliveryCount++;
    }
}

//==============================================================================
/**
 * ハタを納品した回数	相手のハタを納品した回数です。同じ人でもカウントします。
 * @param   none
 * @retval  none
 */
//==============================================================================
#ifdef PM_DEBUG
void D_SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord,int num)
{
    pSBRecord->flagDeliveryCount = num;
}
#endif

//==============================================================================
/**
 * タマを掘った回数	ミニゲームで、タマを掘り出した回数です。埋めたタマを掘り出してもカウントします。
 * @param   none
 * @retval  タマを掘った回数
 */
//==============================================================================
int SecretBaseRecordGetStoneNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->stoneCount;
}

//==============================================================================
/**
 * タマを掘った回数	ミニゲームで、タマを掘り出した回数です。埋めたタマを掘り出してもカウントします。
 * @param   add  増加分
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetStoneNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->stoneCount > (_MAX - add))){
        pSBRecord->stoneCount = _MAX;
    }
    else{
        pSBRecord->stoneCount += add;
    }
}

//==============================================================================
/**
 * 化石を掘った回数	化石を掘った回数です。ミニゲームで手に入れた化石の数です。
 * @param   none
 * @retval  タマを掘った回数
 */
//==============================================================================
int SecretBaseRecordGetFossilNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->fossilCount;
}

//==============================================================================
/**
 * 化石を掘った回数	化石を掘った回数です。ミニゲームで手に入れた化石の数です。
 * @param   add   増加分
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFossilNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->fossilCount > (_MAX - add))){
        pSBRecord->fossilCount = _MAX;
    }
    else{
        pSBRecord->fossilCount += add;
    }
}

//==============================================================================
/**
 * 宝を掘った回数	宝を掘った回数です。ミニゲームで手に入れた宝の数です。
 * @param   none
 * @retval  宝を掘った回数
 */
//==============================================================================

int SecretBaseRecordGetTreasureNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->treasureCount;
}

//==============================================================================
/**
 * 宝を掘った回数	宝を掘った回数です。ミニゲームで手に入れた宝の数です。
 * @param   add   増加分
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTreasureNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->treasureCount > (_MAX - add))){
        pSBRecord->treasureCount = _MAX;
    }
    else{
        pSBRecord->treasureCount += add;
    }
}

//==============================================================================
/**
 * トラップをかけた回数	相手をトラップにかけた回数です。
 * @param   none
 * @retval  トラップをかけた回数
 */
//==============================================================================

int SecretBaseRecordGetTrapConquerNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapConquerCount;
}

//==============================================================================
/**
 * トラップをかけた回数	相手をトラップにかけた回数です。
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapConquerNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapConquerCount < _MAX){
        pSBRecord->trapConquerCount++;
    }
}

//==============================================================================
/**
 * トラップにかかった回数	自分がトラップにかかった回数です。
 * @param   none
 * @retval  トラップにかかった回数
 */
//==============================================================================

int SecretBaseRecordGetTrapTumbleNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapTumbleCount;
}

//==============================================================================
/**
 * トラップにかかった回数	自分がトラップにかかった回数です。
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapTumbleNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapTumbleCount < _MAX){
        pSBRecord->trapTumbleCount++;
    }
}

//==============================================================================
/**
 * 人を助けた回数	トラップにかかっている人を助けた回数です。
 * @param   none
 * @retval  人を助けた回数
 */
//==============================================================================

int SecretBaseRecordGetTrapRescueNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapRescueCount;
}

//==============================================================================
/**
 * 人を助けた回数	トラップにかかっている人を助けた回数です。
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapRescueNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapRescueCount < _MAX){
        pSBRecord->trapRescueCount++;
    }
}

//==============================================================================
/**
 * 道具をもらった回数	誰かに道具をもらった回数です。同じひとからもらっても、カウントします。
 * @param   none
 * @retval  道具をもらった回数
 */
//==============================================================================

int SecretBaseRecordGetItemRecvNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->itemRecvCount;
}

//==============================================================================
/**
 * 道具をもらった回数	誰かに道具をもらった回数です。同じひとからもらっても、カウントします。
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetItemRecvNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->itemRecvCount < _MAX){
        pSBRecord->itemRecvCount++;
    }
}

//==============================================================================
/**
 * 旗をとられた回数	誰かにハタをとられた回数です。
 * @param   none
 * @retval  旗をとられた回数
 */
//==============================================================================

int SecretBaseRecordGetFlagStealNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagStealCount;
}

//==============================================================================
/**
 * 旗をとられた回数	誰かにハタをとられた回数です。
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetFlagStealNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagStealCount < _MAX){
        pSBRecord->flagStealCount++;
    }
}

//==============================================================================
/**
 * 旗を取り返した回数	ハタを取り返した回数です。
 * @param   none
 * @retval  旗をとられた回数
 */
//==============================================================================

int SecretBaseRecordGetFlagReverseNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagReverseCount;
}

void SecretBaseRecordSetFlagReverseNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagReverseCount < _MAX){
        pSBRecord->flagReverseCount++;
    }
}

//==============================================================================
/**
 * 引っ越しした回数	引っ越しをした回数です。
 * @param   none
 * @retval  引っ越しした回数
 */
//==============================================================================

int SecretBaseRecordGetRelocateNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->relocateCount;
}

void SecretBaseRecordSetRelocateNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->relocateCount < _MAX){
        pSBRecord->relocateCount++;
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地位置を設定する
 * @param	pSec			秘密基地データ
 * @param	x,z,dir			出口の場所
 * @return	none
 */
//---------------------------------------------------------------------------
void SecretBaseSetSecretBasePosition(SECRETBASEDATA* pSec,int x,int z,int dir)
{
    pSec->xpos = x;         // ドアの位置
    pSec->zpos = z;
    pSec->dir = dir;        // 外に出てるドアの方向
    pSec->bMake = TRUE;     //  作ったかどうか
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地位置Xを得るする
 * @param	pSec			秘密基地データ
 * @param	x,z,dir			出口の場所
 * @return	none
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionX(const SECRETBASEDATA* pSec)
{
    return pSec->xpos;         // ドアの位置
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地位置Zを得るする
 * @param	pSec			秘密基地データ
 * @return	z			出口の場所
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionZ(const SECRETBASEDATA* pSec)
{
    return pSec->zpos;
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地位置方向を得るする
 * @param	pSec			秘密基地データ
 * @return	dir			出口の場所
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionDir(const SECRETBASEDATA* pSec)
{
    return pSec->dir;
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地作ったことがあるかどうか
 * @param	pSec			秘密基地データ
 * @return	作っていたらTRUE
 */
//---------------------------------------------------------------------------
BOOL SecretBaseIsSecretBaseMake(const SECRETBASEDATA* pSec)
{
    return pSec->bMake;     //  作ったかどうか
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地データを取り出す
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	SECRETBASEDATA	秘密基地データポインタ
 */
//---------------------------------------------------------------------------
SECRETBASEDATA* SaveData_GetSecretBaseData(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return &ugd->base;
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地レコードデータを取り出す
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	SB_RECORD_DATA	秘密基地レコードデータポインタ
 */
//---------------------------------------------------------------------------
SB_RECORD_DATA* SaveData_GetSecretBaseRecord(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return &ugd->base.recordData;
}

//---------------------------------------------------------------------------
/**
 * @brief	秘密基地レコードデータを取り出す
 * @param	pSec			秘密基地データ
 * @return	SB_RECORD_DATA	秘密基地レコードデータポインタ
 */
//---------------------------------------------------------------------------
SB_RECORD_DATA* SecretBaseGetSecretBaseRecord(SECRETBASEDATA* pSec)
{
	return &pSec->recordData;
}

//---------------------------------------------------------------------------
/**
 * @brief	地下アイテムデータをセーブから取り出す
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	UNDERGROUNDDATA	地下アイテムデータポインタ
 */
//---------------------------------------------------------------------------
UNDERGROUNDDATA* SaveData_GetUnderGroundData(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return ugd;
}


#ifdef PM_DEBUG

//----------------------------------------------------------
/**
 * @brief	デバッグ用：地下宝物をかばんに
 * @param	pSBData	      UNDERGROUNDDATAワークポインタ
 * @param	type     地下アイテムタイプ
 */
//----------------------------------------------------------
void Debug_UnderGroundData_AddTreasure(UNDERGROUNDDATA* pUGData, int type)
{
    int i = _getFreeBagTreasureItemIndex(pUGData);
    if(i == -1){
        return;
    }
    GF_ASSERT(DIG_PARTS_TREASURE_MIN <= type);
    GF_ASSERT(type < DIG_PARTS_TREASURE_MAX);
    pUGData->bagTreasure[i] = type;
}

static SB_LOCK* _getFreeLockBuff(SECRETBASEDATA* pSBData)
{
    int i;
    for(i = 0;i < SECRETBASE_LOCK_NUM_MAX; i++){
        if( (pSBData->rockPos[i].x == _INVALID_POS) &&
            (pSBData->rockPos[i].z == _INVALID_POS) ){
            return &pSBData->rockPos[i];
        }
    }
    return NULL;
}

static SB_GOODS* _getFreeGoodsBuff(SECRETBASEDATA* pSBData)
{
    int i;
    for(i = 0;i < SECRETBASE_GOODS_NUM_MAX; i++){
        if( pSBData->goodsPos[i].type == GOODS_INVALID ){
            return &pSBData->goodsPos[i];
        }
    }
    return NULL;
}

//----------------------------------------------------------
/**
 * @brief	デバッグ用：グッズ設置  (パソコンへも登録します)
 * @param	pSBData	      SECRETBASEDATAワークポインタ
 * @param	name	名前文字列へのポインタ
 * @param	sex		性別指定
 */
//----------------------------------------------------------
void Debug_SecretBaseData_AddGoods(SECRETBASEDATA* pSBData, int goodsType, int x, int z)
{
    if(GOODS_BIG_ROCK == goodsType){
        SB_LOCK* pLock = _getFreeLockBuff(pSBData);
        if(pLock != NULL){
            pLock->x = x;
            pLock->z = z;
        }
    }
    else if(goodsType < GOODS_BIG_ROCK){  // パソコンは固定位置
    }
    else{
        SB_GOODS* pGoods = _getFreeGoodsBuff(pSBData);
        if(pGoods != NULL){
            pGoods->type = goodsType;
            pGoods->x = x;
            pGoods->z = z;
        }
    }
}


#endif //PM_DEBUG
