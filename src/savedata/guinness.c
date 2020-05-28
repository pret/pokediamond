/**
 *	@brief	ギネスホールセーブデータ領域定義
 *	
 */

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/mystatus.h"
#include "savedata/record.h"
#include "savedata/randomgroup.h"
#include "system/gamedata.h"
#include "gflib/msg_print.h"
#include "guinness_local.h"

#define __GUINNESS_H_GLOBAL
#include "savedata/guinness.h"

#include "system/pm_str.h"	//特別
#include "gflib/strbuf_family.h"	//特別

/**
 * タイプ別ギネスデータのアクセステーブル
 *
 * 0:タイプ内データブロック数
 * 1:GNSIDオフセット
 */
static const u8 rankingTable[][2] = {
	{6,0},{4,6},{3,10}
}; 

///タイプ別のブロック数を返す
u8 GNSRank_GetTypeBlockNum(GNSTYPE type) 
{
	return rankingTable[type][0];
}
///タイプ別のGNSIDオフセットを返す
u8 GNSRank_GetTypeGNSIDOfs(GNSTYPE type)
{
	return rankingTable[type][1];
}

/**
 *	@brief	ギネスデータ　クリア
 */
void GNS_DataClear(GUINNESS_DATA* dat)
{
	dat->groupID = 0;
	dat->record = 0;
	PM_strclearEOM_(dat->name,PERSON_NAME_SIZE+EOM_SIZE);
}

/**
 *	@brief	ギネスデータ　コピー
 */
void GNS_DataCopy(const GUINNESS_DATA* src,GUINNESS_DATA* dest)
{
	dest = (GUINNESS_DATA*)src;
}

/**
 *	@brief	ギネスデータが有効かどうか？
 *
 *	＊名前文字列がNULL文字列なら空
 */
BOOL GNS_IsEnable(GUINNESS_DATA* dat)
{
	if(PM_strlen(dat->name) == 0){
		return FALSE;
	}
	return TRUE;
}

/**
 *	@brief	ギネスホール　データサイズ
 */
int	GuinnessData_GetWorkSize(void)
{
	return sizeof(GUINNESS);
}

/**
 *	@brief	ギネスホール　データ初期化
 */
void GuinnessData_Init(GUINNESS* dat)
{
	int i,j;
	
	MI_CpuClear8(dat,sizeof(GUINNESS));

	for(i = 0;i < GNS_BLOCK_NUM;i++){
		for(j = 0;j < GNS_DATA_NUM;j++){
			GNS_DataClear(&(dat->block[i].dat[j]));
		}
	}
}

/**
 *	@brief	ギネスホール　データブロックへのポインタを取得
 */
GUINNESS* SaveData_GetGuinnessData(SAVEDATA* sv)
{
	return SaveData_Get(sv,GMDATA_ID_GUINNESS);
}

/**
 *	@brief	ギネス　指定したデータを消去する
 */
void GuinnessData_DelRecord(GUINNESS* dat,GNSID id,u8 idx)
{
	int i;
	GUINNESS_BLOCK* bp;
	
	if(idx >= GNS_DATA_NUM){
		GF_ASSERT(idx < GNS_DATA_NUM && "GNS Recoed Del -> idx over\n")
		return;	//何もしない
	}
	bp = &(dat->block[id]);

	for(i = idx;i < (GNS_DATA_NUM-1);i++){
		bp->dat[i] = bp->dat[i+1];
	}
	GNS_DataClear(&(bp->dat[(GNS_DATA_NUM-1)]));
}
/**
 *	@brief	ギネス　レコード送信データサイズ取得
 */
int GuinnessRecord_GetWorkSize(void)
{
	return sizeof(GUINNESS_RECORD);
}

/**
 *	@brief	自分の記録をu32[GNS_RECORD_NUM]配列に格納して返す
 *
 *	＊呼び出し側がきちんとメモリ解放すること
 */
static u32* guinness_AllocMyRecord(SAVEDATA* sv,int heapID)
{
	int i;
	u32	value;
	RECORD*	record;
	u32* data;
	
	static const int recid[] = {
		RECID_RENSHOU_SINGLE,
		RECID_RENSHOU_DOUBLE,
		RECID_RENSHOU_MULTI,
		RECID_RENSHOU_COMM_MULTI,
		RECID_RENSHOU_WIFI,
		RECID_BTOWER_WIN,	//RECID_BTOWER_CHALLENGE
		RECID_KILL_POKE,
		RECID_CAPTURE_POKE,
		RECID_TAMAGO_HATCHING,
		RECID_FISHING_SUCCESS,
		RECID_CONTEST_GPX,	
		RECID_CONTEST_ENTRY,
		RECID_CONTEST_RIBBON_GET,
	};
	record = SaveData_GetRecord(sv);
	data = sys_AllocMemoryLo(heapID,4*GNS_RECORD_NUM);

	for(i = 0;i < GNS_RECORD_NUM;i++){
		switch(i){
		case GNSID_GLB_WIN:	//平均勝ち抜き数
			value = RECORD_Get(record,RECID_BTOWER_CHALLENGE);
			if(value > 0){
				value = RECORD_Get(record,RECID_BTOWER_WIN)/value;	
			}
			data[i] = value;
			break;
		case GNSID_GLC_GPX:	//コンテスト優勝回数
			value = RECORD_Get(record,RECID_CONTEST_GPX);
			value += RECORD_Get(record,RECID_CONTEST_COMM_GPX);
			data[i] = value;
			break;
		case GNSID_GLC_GPXPER:	//コンテスト優勝率
			value = RECORD_Get(record,RECID_CONTEST_ENTRY);
			value += RECORD_Get(record,RECID_CONTEST_COMM_ENTRY);
			if(value > 0){
				value = (data[GNSID_GLC_GPX]*100)/value;
			}
			data[i] = value;
			break;
		default:
			data[i] = RECORD_Get(record,recid[i]);
		}
	}
	return data;
}

/**
 *	@brief	ギネス　レコード送信データ作成
 */
void* GuinnessRecord_SendDataAlloc(SAVEDATA* sv,int heapID)
{
	int i;
	u32	groupID,value;
	GUINNESS_RECORD* gp;
	STRBUF* name;
	MYSTATUS* my = SaveData_GetMyStatus(sv);
	u32	*record;
	

	gp = sys_AllocMemoryLo(heapID,sizeof(GUINNESS_RECORD));
	MI_CpuClear8(gp,sizeof(GUINNESS_RECORD));

	//ランダムグループID取得
	groupID = RandomGroup_GetRandomSeed(
			SaveData_GetRandomGroup(sv),RANDOMGROUP_MYUSE );

	//名前取得
	name = MyStatus_CreateNameString(my,heapID);
	
	//自分の記録を取得
	record = guinness_AllocMyRecord(sv,heapID);

	for(i = 0;i < GNS_RECORD_NUM;i++){
		value = 0;
		gp->dat[i].groupID = groupID;
		STRBUF_GetStringCode(name,gp->dat[i].name,PERSON_NAME_SIZE+EOM_SIZE);
		gp->dat[i].record = record[i];
	}
	sys_FreeMemoryEz(record);
	STRBUF_Delete(name);

	return gp;
}

//グループIDが変更されているかどうか
static BOOL gnsRecord_IsUpdateGroupData(GUINNESS* gnsSave,u32 groupID)
{
	int i,j;
	
	for(i = GNS_RECORD_NUM;i < GNS_BLOCK_NUM;i++){
		for(j = 0;j < GNS_DATA_NUM;j++){
			if(GNS_IsEnable(&(gnsSave->block[i].dat[j]))){
				if(gnsSave->block[i].dat[j].groupID != groupID){
					return TRUE;
				}else{
					return FALSE;
				}
			}
		}
	}
	return FALSE;
}
//ブロックを一旦破棄する
static void gnsRecord_ClearBlockData(GUINNESS_BLOCK* block)
{
	int i;
	for(i = 0;i < GNS_DATA_NUM;i++){
		GNS_DataClear(&(block->dat[i]));
	}
}

//グループレコードを一旦破棄する
static void gnsRecord_ClearGroupData(GUINNESS* gns)
{
	int i;
	for(i = GNS_RECORD_NUM;i < GNS_BLOCK_NUM;i++){
		gnsRecord_ClearBlockData(&(gns->block[i]));
	}
}
#define RECMIX_NUM	(5+GNS_DATA_NUM)

typedef struct _RECMIX{
	int	snum;	//ソースの数
	int	lnum;	//受信データの数
	int	dnum;	//有効データ総数

	GUINNESS_DATA*	pList[RECMIX_NUM];
	GUINNESS_DATA*	pSrc[GNS_DATA_NUM];
	GUINNESS_BLOCK	block;	//ブロックデータの実体ワーク
}RECMIX;

//同じプレイヤーのデータかどうか判別
static BOOL gnsRecord_IsSamePlayer(const GUINNESS_DATA* d1,const GUINNESS_DATA* d2)
{
	if(d1->groupID != d2->groupID){
		return FALSE;
	}
	if(PM_strcmp(d1->name,d2->name)){
		return FALSE;
	}
	return TRUE;
}

/**
 *	@brief	同じプレイヤーのデータが受信データ内にあるか？
 */
static BOOL gnsRecord_IsSamePlayerExist(RECMIX* wk,const GUINNESS_DATA* src)
{
	int i;

	for(i = 0;i < wk->lnum;i++){
		if(gnsRecord_IsSamePlayer(wk->pList[i],src)){
			return TRUE;
		}
	}
	return FALSE;
}

//レコードソート
static void gnsRecord_GetMixData(GUINNESS* gns,RECMIX* wk,u32 groupID,u8 id,u8 mode,
		GUINNESS_RECORD** src,u8 num,int heapID)
{
	int i,j;
	GUINNESS_DATA*	tmp;
	GUINNESS_BLOCK* gp;
	
	MI_CpuClear8(wk,sizeof(RECMIX));

	if(mode == 0){	//グローバル
		gp = &(gns->block[id]);

		//データ実体をテンポラリにコピーして保存
		MI_CpuCopy8(gp,&(wk->block),sizeof(GUINNESS_BLOCK));

		//グローバル受信データへのポインタ取得
		for(i = 0;i < num;i++){
			wk->pList[wk->lnum++] = &(src[i]->dat[id]);
		}
	
		for(i = 0;i < GNS_DATA_NUM;i++){
			if(!GNS_IsEnable(&(wk->block.dat[i]))){
				continue;
			}
			if(gnsRecord_IsSamePlayerExist(wk,&(wk->block.dat[i]))){
				continue;	//同じ人のデータがある時は受信データ優先
			}
			wk->pSrc[wk->snum++] = &(wk->block.dat[i]);
		}
	}else{	//グループ
		gp = &(gns->block[id+GNS_RECORD_NUM]);
		
		//データ実体をテンポラリにコピーして保存
		MI_CpuCopy8(gp,&(wk->block),sizeof(GUINNESS_BLOCK));

		//グループ受信データへのポインタ取得
		for(i = 0;i < num;i++){
			if(	(src[i]->dat[id].groupID == 0) ||
				(src[i]->dat[id].groupID != groupID)){
				continue;
			}
			wk->pList[wk->lnum++] = &(src[i]->dat[id]);
		}
		//自分のデータ取得
		for(i = 0;i < GNS_DATA_NUM;i++){
			if(!GNS_IsEnable(&(wk->block.dat[i]))){
				continue;
			}
			if(wk->block.dat[i].groupID != groupID){
				continue;
			}
			if(gnsRecord_IsSamePlayerExist(wk,&(wk->block.dat[i]))){
				continue;	//同じ人のデータがある時は受信データ優先
			}
			wk->pSrc[wk->snum++] = &(wk->block.dat[i]);
		}
	}
	//ソートデータの総数を取得
	wk->dnum = wk->lnum+wk->snum;
	//データリスト連結
	for(i = 0;i < wk->snum;i++){
		wk->pList[i+wk->lnum] = wk->pSrc[i];
	}
	//ソート
	for(i = 0;i < (wk->dnum-1);i++){
		for(j = (wk->dnum-1);j > i;j--){
			if(wk->pList[i]->record >= wk->pList[j]->record){
				continue;
			}
			tmp = wk->pList[i];
			wk->pList[i] = wk->pList[j];
			wk->pList[j] = tmp;
		}
	}
	//セーブデータに反映
	gnsRecord_ClearBlockData(gp);
	for(i = 0;(i < GNS_DATA_NUM && i < wk->dnum);i++ ){
		gp->dat[i] = *(wk->pList[i]);
	}
}

//各種レコードを収集する
static void gnsRecord_DataCorrect(GUINNESS* gns,u32 groupID,u8 id,GUINNESS_RECORD** src,u8 num,int heapID)
{
	int i,j;
	RECMIX* wk;

	wk = sys_AllocMemoryLo(heapID,sizeof(RECMIX));

	//グローバル
	gnsRecord_GetMixData(gns,wk,groupID,id,0,src,num,heapID);
	
	//グループ
	if(groupID != 0){
		gnsRecord_GetMixData(gns,wk,groupID,id,1,src,num,heapID);
	}

	sys_FreeMemoryEz(wk);
#if 0
	int	snum,rnum,dnum;
	GUINNESS_DATA*	tmp;
	GUINNESS_DATA*	pList[RECMIX_NUM];
	GUINNESS_DATA*	pSrc[GNS_DATA_NUM];
	GUINNESS_BLOCK*	gp0,*gp1;
	GUINNESS_BLOCK	glb,grp;
#if 1
	gp0 = &(gns->block[id]);
	gp1 = &(gns->block[id+GNS_RECORD_NUM]);

	MI_CpuClear8(&glb,sizeof());
	MI_CpuClear8(pList,4*RECMIX_NUM);
	MI_CpuClear8(pSrc,4*GNS_DATA_NUM);

	//セーブ済み有効データへのポインタ取得
	snum = 0;
	rnum = 0;
	for(i = 0;i < GNS_DATA_NUM;i++){
		if(GNS_IsEnable(&(gp0->dat[i]))){
			pSrc[snum++] = &(gp0->dat[i]);
		}
	}
	//グローバル受信データへのポインタ取得
	for(i = 0;i < num;i++){
		pList[i] = &(src[i]->dat[id]);
	}
	rnum = num;
	dnum = snum+rnum;
	
	//セーブ済みデータ結合
	for(i = 0;i < snum;i++){
		pList[rnum+i] = pSrc[i];
	}
	//ソート
	for(i = 0;i < (dnum-1);i++){
		for(j = (dnum-1);j > i;j--){
			if(pList[i]->record >= pList[j]->record){
				continue;
			}
			tmp = pList[i];
			pList[i] = pList[j];
			pList[j] = tmp;
		}
	}
	//グローバルセーブデータに反映
	gnsRecord_ClearBlockData(gp0);
	for(i = 0;(i < GNS_DATA_NUM && i < dnum);i++ ){
		gp0->dat[i] = *(pList[i]);
	}

	MI_CpuClear8(pList,4*RECMIX_NUM);
	MI_CpuClear8(pSrc,4*GNS_DATA_NUM);
	snum = 0;
	rnum = 0;
	
	//セーブ済みデータへのポインタ取得
	for(i = 0;i < GNS_DATA_NUM;i++){
		if(GNS_IsEnable(&(gp1->dat[i])) && (gp1->dat[i].groupID == groupID)){
			pSrc[snum++] = &(gp1->dat[i]);
		}
	}
	//グループ受信データへのポインタ取得
	for(i = 0;i < num;i++){
		if(src[i]->dat[id].groupID == groupID){
			pList[rnum++] = &(src[i]->dat[id]);
		}
	}
	dnum = snum+rnum;

	//セーブ済みデータ結合
	for(i = 0;i < snum;i++){
		pList[rnum+i] = pSrc[i];
	}
	//ソート
	for(i = 0;i < (dnum-1);i++){
		for(j = (dnum-1);j > i;j--){
			if(pList[i]->record >= pList[j]->record){
				continue;
			}
			tmp = pList[i];
			pList[i] = pList[j];
			pList[j] = tmp;
		}
	}
	//グループセーブデータに反映
	gnsRecord_ClearBlockData(gp1);
	for(i = 0;(i < GNS_DATA_NUM && i < dnum);i++ ){
		gp1->dat[i] = *(pList[i]);
	}
#endif
#endif
}

/**
 *	@brief	ギネス　レコードMix
 */
void GuinnessRecord_RecvDataMix(SAVEDATA* sv,int myid,u8 datanum,const void** array,int heapID)
{
	u8 i,dat_num;
	u32	groupID;
	GUINNESS_RECORD	*src[5];
	GUINNESS*	gnsSave;
	GNS_RANKING*	gnsRank;

	//ギネスセーブデータ取得
	gnsSave = SaveData_GetGuinnessData(sv);

	//ランダムグループID取得
	groupID = RandomGroup_GetRandomSeed(
			SaveData_GetRandomGroup(sv),RANDOMGROUP_MYUSE );

#if 0
	//自分のランダムグループIDが変更されているかチェック
	if(gnsRecord_IsUpdateGroupData(gnsSave,groupID)){
		//一旦グループレコード破棄
		gnsRecord_ClearGroupData(gnsSave);
	}
#endif
	dat_num = 0;
	for(i = 0;i < datanum;i++){
		if(i == myid){
			continue;	//自分はパス
		}
		if(array[i] == NULL){
			continue;	//NULLデータならパス
		}
		src[dat_num++] = (GUINNESS_RECORD*)array[i];
	}
	if(dat_num == 0){
		return;	//他人のデータがない
	}

	//各データを収集&ソートする
	for(i = 0;i < GNS_RECORD_NUM;i++){
		gnsRecord_DataCorrect(gnsSave,
			groupID,i,src,dat_num,heapID);
	}
	return;
}

/**
 *	@brief	ギネスランキングデータ　自分のレコードを取得
 *
 *	@return	GNS_RANKING*
 *
 *	＊GNS_RANKINGデータ型メモリを確保し、データを格納して返す
 *	
 *	　GNSRank_FreeRankingData()関数を必ず用いて
 *	　呼び出し側がきちんとメモリ解放すること！
 *	  sys_FreeMemoryで解放しちゃダメ	
 */
GNS_RANKING* GNSRank_AllocMyData(SAVEDATA* sv,GNSTYPE type,int heapID)
{
	int i,ofs;
	u32	groupID;
	GNS_RANKING* rp;
	u32	*record;
	MYSTATUS* my;
	
	my = SaveData_GetMyStatus(sv);
	rp = sys_AllocMemory(heapID,sizeof(GNS_RANKING));
	MI_CpuClear8(rp,sizeof(GNS_RANKING));
	
	//ランダムグループID取得
	groupID = RandomGroup_GetRandomSeed(
			SaveData_GetRandomGroup(sv),RANDOMGROUP_MYUSE );
	//自分の記録を取得
	record = guinness_AllocMyRecord(sv,heapID);
	
	rp->num = GNSRank_GetTypeBlockNum(type);
	ofs = GNSRank_GetTypeGNSIDOfs(type);
	for(i = 0;i < rp->num;i++){
		rp->rank[i].groupID = groupID;
		rp->rank[i].record = record[i+ofs];
		rp->rank[i].name = MyStatus_CreateNameString(my,heapID);
	}

	sys_FreeMemoryEz(record);
	return rp;
}

/**
 *	@brief	ギネスランキングデータ取得
 *
 *	@return	
 *	＊GNS_RANKINGデータ型メモリを確保しデータをコピーして返す
 *
 *	　GNSRank_FreeRankingData()関数を必ず用いて
 *	　呼び出し側がきちんとメモリ解放すること！
 *	  sys_FreeMemoryで解放しちゃダメ	
 */
GNS_RANKING* GNSRank_AllocRankingData(GUINNESS* gns,GNSID id,int heapID) 
{
	int i;
	GNS_RANKING* rp;
	GUINNESS_BLOCK* bp;
	
	rp = sys_AllocMemory(heapID,sizeof(GNS_RANKING));
	MI_CpuClear8(rp,sizeof(GNS_RANKING));

	bp = &(gns->block[id]);

	for(i = 0;i < GNS_DATA_NUM;i++){
		if(!GNS_IsEnable(&(bp->dat[i]))){
			continue;
		}
		rp->rank[rp->num].groupID = bp->dat[i].groupID;
		rp->rank[rp->num].record = bp->dat[i].record;

		rp->rank[rp->num].name = STRBUF_Create(PERSON_NAME_SIZE+EOM_SIZE,heapID);
		STRBUF_SetStringCode(rp->rank[rp->num].name,bp->dat[i].name);
		++rp->num;
	}
	return rp;
}

/**
 *	@brief	ギネスランキングデータ解放
 *
 *	＊GNSRank_GetRankingData()関数を用いて取得した
 *	　メモリ領域を開放する
 */
void GNSRank_FreeRankingData(GNS_RANKING* dat)
{
	int i;

	for(i = 0;i < GNS_DATA_NUM;i++){
		if(dat->rank[i].name != NULL){
			STRBUF_Delete(dat->rank[i].name);
		}
	}
	MI_CpuClear8(dat,sizeof(GNS_RANKING));
	sys_FreeMemoryEz(dat);
	dat = NULL;
}

/**
 *	@brief	ギネスランキングデータセット
 *
 *	ランキングソート済みデータをGNS_RANKING型に格納して
 *	引渡し、セーブデータにセットする
 */
void GNSRank_SetRankingData(GUINNESS* gns,GNSID id,GNS_RANKING* dat)
{
	int i;
	GUINNESS_BLOCK* bp;

	bp = &(gns->block[id]);

	for(i = 0;i < GNS_DATA_NUM;i++){
		GNS_DataClear(&bp->dat[i]);
		if(i >= dat->num){
			continue;
		}
		bp->dat[i].groupID = dat->rank[i].groupID;
		bp->dat[i].record = dat->rank[i].record;
		STRBUF_GetStringCode(dat->rank[i].name,bp->dat[i].name,
			PERSON_NAME_SIZE+EOM_SIZE);
	}
}

#ifdef PM_DEBUG
#include "system/msgdata.h"
#include "gflib/calctool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_trname.h"

/**
 *	@brief	ギネスランキングデータ　ダミー生成
 */
void DebugGNSRank_MakeDmyRankingData(GUINNESS* gns)
{
	int i,j;
	u32	randid,randid2;
	u16	randmax,randmax2;
	MSGDATA_MANAGER *msgMan;
	static const int max[] = {9999,9999,9999,9999,9999,8,
						65535,65535,65535,65535,
						9999,101,65535
	};
	msgMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_trname_dat,HEAPID_WORLD);
	
	randid2 = ((int)(gf_rand())<<16) | gf_rand();

	for(i = 0;i < GNS_RECORD_NUM;i++){
		randmax = max[i];
		randmax2 = max[i];
		for(j = 0;j < GNS_DATA_NUM;j++){
			gns->block[i].dat[j].groupID = ((int)(gf_rand())<<16)|gf_rand();
			randmax = gf_rand()%randmax;
			gns->block[i].dat[j].record = randmax;
			MSGMAN_GetStr(msgMan,j+1,gns->block[i].dat[j].name);
			
			gns->block[i+13].dat[j].groupID = randid2; 
			randmax2 = gf_rand()%randmax2;
			gns->block[i+13].dat[j].record = randmax2;
			MSGMAN_GetStr(msgMan,j+13,gns->block[i+GNS_RECORD_NUM].dat[j].name);
		}
	}
	MSGMAN_Delete(msgMan);
}


#endif	//PM_DEBUG

