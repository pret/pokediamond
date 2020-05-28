/**
 *	@file	poruto.c
 *	@brief	ポルトセーブデータ 制御
 *	@author	Miyuki Iwasawa
 *	@date	06.2.28
 */

#include "common.h"
#include "savedata/savedata.h"
#include "savedata/poruto.h"
#include "savedata/poruto_util.h"
#include "savedata/poruto_local.h"

/**
 *	@brief	ポルトデータサイズ取得
 */
int PorutoData_GetWorkSize(void)
{
	return sizeof(PORUTO_DATA);
}

/**
 *	@brief	そのポルトデータが有効かどうか返す
 */
BOOL PorutoData_IsEnable(PORUTO_DATA* dat)
{
	if(dat->flavor == PORUTO_FLAVOR_NULL){
		return FALSE;
	}
	return TRUE;
}

/**
 *	@brief	ポルトデータクリア
 */
void PorutoData_Clear(PORUTO_DATA* dat)
{
	dat->flavor = PORUTO_FLAVOR_NULL;
	dat->spicy = 0;
	dat->astringent = 0;
	dat->sweet = 0;
	dat->bitter = 0;
	dat->sour = 0;
	dat->taste = 0;
	dat->pad_dmy = 0;
}

/**
 *	@brief	ポルトデータワーク作成
 */
PORUTO_DATA* PorutoData_AllocWork(int heapID)
{
	PORUTO_DATA* dat;

	dat = sys_AllocMemoryLo(heapID,sizeof(PORUTO_DATA));
	PorutoData_Clear(dat);
	return dat;
}

/**
 *	@brief	ポルトデータコピー
 */
void PorutoData_Copy(PORUTO_DATA* src,PORUTO_DATA* dest)
{
	dest->flavor = src->flavor;
	dest->spicy = src->spicy;
	dest->astringent = src->astringent;
	dest->sweet = src->sweet;
	dest->bitter = src->bitter;
	dest->sour = src->sour;
	dest->taste = src->taste;
	dest->pad_dmy = src->pad_dmy;
}

/**
 *	@brief	ポルトのパラメータを取得
 *
 *	@param	dat
 *	@param	id	enum PORUTO_PARAID型(poruto_def.h参照)
 *
 *	@return	u8:取得したパラメータ
 */
u8 PorutoData_GetParam(PORUTO_DATA* dat,PORUTO_PARAID id)
{
	switch(id){
	case PORUTO_PARAID_FLAVOR:
		return dat->flavor;
	case PORUTO_PARAID_SPICY:
		return dat->spicy;
	case PORUTO_PARAID_ASTR:
		return dat->astringent;
	case PORUTO_PARAID_SWEET:
		return dat->sweet;
	case PORUTO_PARAID_BITTER:
		return dat->bitter;
	case PORUTO_PARAID_SOUR:
		return dat->sour;
	case PORUTO_PARAID_TASTE:
	default:
		return dat->taste;
	}
}
	
/**
 *	@brief	ポルトのパラメータをセット
 *
 *	@param	dat
 *	@param	value	セットしたいデータ
 *	@param	id	enum PORUTO_PARAID型(poruto_def.h参照)
 *
 */
void PorutoData_SetParam(PORUTO_DATA* dat,u8 valid,PORUTO_PARAID id)
{
	if(id == PORUTO_PARAID_FLAVOR){
		if(valid < PORUTO_FLAVOR_MAX){
			dat->flavor = valid;
		}
		return;	
	}
	if(valid >= PORUTO_PARAM_MAX){
		return;
	}
	switch(id){
	case PORUTO_PARAID_SPICY:
		dat->spicy = valid;
		break;
	case PORUTO_PARAID_ASTR:
		dat->astringent = valid;
		break;
	case PORUTO_PARAID_SWEET:
		dat->sweet = valid;
		break;
	case PORUTO_PARAID_BITTER:
		dat->bitter = valid;
		break;
	case PORUTO_PARAID_SOUR:
		dat->sour = valid;
		break;
	case PORUTO_PARAID_TASTE:
		dat->taste = valid;
		break;
	default:
		break;
	}
	return;
}

//不味いポルトを生成
static void porudata_MakeNoGoodPoruto(PORUTO_DATA *dat,u8 taste)
{
	int ct;
	u8 id;

	ct = 0;
	do{
		id = gf_rand()%PORUTO_FTYPE_NUM;
		if(dat->param[id+1] != 0){
			continue;
		}
		dat->param[id+1] = 2;
		++ct;
	}while(ct < 3);
	dat->flavor = PORUTO_FLAVOR_NGOOD;
	dat->taste = taste;
}

/**
 *	@brief	味と旨味からポルトの種類を決定し、パラメータをセットして返す
 *
 *	@param	dat	PORUTO_DATA*:パラメータをセットするポルトデータ型構造体
 *	@param	prm	u8[5]:5種類の味値を格納
 *	@param	taste	旨味値を格納
 *	@param	mazui	強制的に不味いポルトになるかどうか？ TRUEならまずいポルト
 *
 *	@return	PORUTO_FLAVORID	作成されたポルトのフレバーID
 */
PORUTO_FLAVORID PorutoData_CalcParam(PORUTO_DATA* dat,u8 *prm,u8 taste,BOOL mazui)
{
	int i,fct = 0;
	u8	kind[5];	
	u8	maro_f = 0,fid = 0;

	fid = PORUTO_FLAVOR_NGOOD;

	if(mazui){
		//まずいポルト
		porudata_MakeNoGoodPoruto(dat,taste);
		return fid;
	}
	
	//持っている味値の数を演算
	for(i = 0;i < 5;i++){
		if(prm[i]){
			if(prm[i] >=  50){
				maro_f = 1;	//まろやかフラグ
			}
			kind[fct++] = i;
		}
	}
	
	switch(fct){
	case 0:	//まずいポルト
		porudata_MakeNoGoodPoruto(dat,taste);
		return fid;
	case 1:	//味が一つ
		fid = kind[0]*5+kind[0];
		break;
	case 2:	//味が二つ
		if(prm[kind[0]] >= prm[kind[1]]){
			fid = kind[0]*5+kind[1];
		}else{
			fid = kind[1]*5+kind[0];
		}
		break;
	case 3:	//こってり
		fid = PORUTO_FLAVOR_HEAVY;
		break;
	case 4:	//くどい
	case 5:
		fid = PORUTO_FLAVOR_THICK;
		break;
	}
	if(maro_f){	//味値が50を越えたものが一つでもあればまろやか
		fid = PORUTO_FLAVOR_MILD;
	}
	//パラメータ格納
	for(i = 0;i < 5;i++){
		dat->param[i+1] = prm[i];
	}
	//味値と旨味値を格納
	dat->flavor = fid;
	dat->taste = taste;
	return fid;
}

/**
 *	@brief	ポルトパラメータ取得(配列版)
 *
 *	＊呼び出し側でデータの取得場所を用意するバージョン
 *	　u8[PORUTO_PARAID_NUM] 分のメモリエリアが必要
 */
void PorutoData_GetParamArray(PORUTO_DATA* dat,u8* array)
{
	array[PORUTO_PARAID_FLAVOR] = dat->flavor;
	array[PORUTO_PARAID_SPICY] = dat->spicy;
	array[PORUTO_PARAID_ASTR] = dat->astringent;
	array[PORUTO_PARAID_SWEET] = dat->sweet;
	array[PORUTO_PARAID_BITTER] = dat->bitter;
	array[PORUTO_PARAID_SOUR] = dat->sour;
	array[PORUTO_PARAID_TASTE] = dat->taste;
}

/**
 *	@brief	ポルトパラメータ取得(配列,メモリ確保版)
 *
 *	＊関数内で必要なバッファを取得して返すバージョン
 *	　呼び出し側で明示的なメモリ解放が必要
 */
u8* PorutoData_GetParamArrayMem(PORUTO_DATA* dat,int heapID)
{
	u8* array;

	array = sys_AllocMemory(heapID,PORUTO_PARAID_NUM);
	array[PORUTO_PARAID_FLAVOR] = dat->flavor;
	array[PORUTO_PARAID_SPICY] = dat->spicy;
	array[PORUTO_PARAID_ASTR] = dat->astringent;
	array[PORUTO_PARAID_SWEET] = dat->sweet;
	array[PORUTO_PARAID_BITTER] = dat->bitter;
	array[PORUTO_PARAID_SOUR] = dat->sour;
	array[PORUTO_PARAID_TASTE] = dat->taste;
	return array;
}

/**
 *	@brief	ポルトのレベルを取得
 */
u8 PorutoData_GetLevel(PORUTO_DATA* dat)
{
	u8	type = 0;
	u8	level = 0;

	type = dat->flavor / PORUTO_FTYPE_NUM;
	switch(type){
	case PORUTO_FTYPE_SPICY:
		level = dat->spicy;
		break;
	case PORUTO_FTYPE_ASTR:
		level = dat->astringent;
		break;
	case PORUTO_FTYPE_SWEET:
		level = dat->sweet;
		break;
	case PORUTO_FTYPE_BITTER:
		level = dat->bitter;
		break;
	case PORUTO_FTYPE_SOUR:
		level = dat->sour;
		break;
	case PORUTO_FTYPE_MIX:
	default:
		//ミックス系は一番高いパラメータを探す
		level = dat->spicy;
		if(level < dat->astringent){
			level = dat->astringent;
		}
		if(level < dat->sweet){
			level = dat->sweet;
		}
		if(level < dat->bitter){
			level = dat->bitter;
		}
		if(level < dat->sour){
			level = dat->sour;
		}
		break;
	}
	if(level > PORUTO_PARAM_VMAX){
		return PORUTO_PARAM_VMAX;
	}
	return level;
}

//=================================================================
// ポルトセーブデータブロックアクセス系
//=================================================================

/**
 *	@brief	セーブデータブロックへのポインタを取得
 */
PORUTO_BLOCK* SaveData_GetPorutoBlock(SAVEDATA* sv)
{
	return SaveData_Get(sv,GMDATA_ID_PORUTODATA);
}

/**
 *	@brief	ポルトセーブデータサイズ取得
 */
int PORUTO_GetSaveWorkSize(void)
{
	return sizeof(PORUTO_DATA)*PORUTO_STOCK_MAX;
}

/**
 *	@brief	ポルトデータ配列初期化
 */
void PORUTO_Init(PORUTO_BLOCK* block)
{
	int i = 0;
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PorutoData_Clear(&block->poruto[i]);
	}
}

/**
 *	@brief	ポルトセーブデータの空き領域を探す
 *
 *	@retval	PORUTO_DATA_NULL	空き領域がない
 *	@retval "その他"			空き領域のIndexNo
 */
u16 PORUTO_SearchNullData(PORUTO_BLOCK* block)
{
	u16 i;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(block->poruto[i].flavor == PORUTO_FLAVOR_NULL){
			return i;
		}
	}
	return PORUTO_DATA_NULL;
}

/**
 *	@brief	ポルトデータをセーブデータ空き領域に追加する
 *
 *	@retval	PORUTO_DATA_NULL	空き領域がなくて追加できなかった
 *	@retval "その他"			追加した領域のindex
 */
u16 PORUTO_AddData(PORUTO_BLOCK* block,PORUTO_DATA* dat) 
{
	u16	idx = PORUTO_SearchNullData(block);

	if(idx == PORUTO_DATA_NULL){
		return idx;
	}
	//追加
	PorutoData_Copy(dat,&block->poruto[idx]);
	return idx;
}

/**
 *	@brief	ポルトデータをセーブデータから削除する(index指定)
 *
 */
BOOL PORUTO_DelData(PORUTO_BLOCK* block,u16 idx) 
{
	if(idx >= PORUTO_STOCK_MAX){
		return FALSE;
	}
	//削除
	PorutoData_Clear(&block->poruto[idx]);
	return TRUE;
}

/**
 *	@brief	指定したindex先の次の有効データのindexを返す
 *
 */
static u16	poruto_GetNextValiableIndex(PORUTO_BLOCK* block,u16 now)
{
	u16	i;

	for(i = now;i < PORUTO_STOCK_MAX;i++){
		if(block->poruto[i].flavor != PORUTO_FLAVOR_NULL){
			//有効データ発見
			return i;
		}
	}
	//有効データは見つからなかった
	return 0xFFFF;
}
/**
 *	@brief	ポルトセーブデータを整理する
 *
 *	＊データ配列の穴空きを詰める
 */
void PORUTO_DataAdjust(PORUTO_BLOCK* block)
{
	u16 i,j,tmp;
	u16	s,d,rest;

	//残りの数初期化
	rest = PORUTO_STOCK_MAX;

	for(i = 0;i < rest;i++){
		if(block->poruto[i].flavor != PORUTO_FLAVOR_NULL){
			continue;
		}
		s = i;
		tmp = poruto_GetNextValiableIndex(block,s);
		if(tmp == 0xFFFF){
			//これ以上先に有効データはない
			break;	//終了
		}
		d = tmp;
		tmp = d-s;
		for(;d < rest;s++,d++){
			PorutoData_Copy(&block->poruto[d],&block->poruto[s]);
			PorutoData_Clear(&block->poruto[d]);
		}
		rest -= tmp;
	}
}

/**
 *	@brief	ポルトデータをセーブデータから取得する(index指定)
 *
 *	＊引き渡されたPORUTO_DATA構造体型領域へ、セーブデータをコピーして返す
 */
void PORUTO_GetData(PORUTO_BLOCK* block,u16 idx,PORUTO_DATA* dest)
{
	if(idx >= PORUTO_STOCK_MAX){
		PorutoData_Clear(dest);
		return;
	}
	//取得
	PorutoData_Copy(&block->poruto[idx],dest);
	return ;
}

/**
 *	@brief	ポルトデータをセーブデータから取得する(index指定/メモリ確保版)
 *
 *	＊PORUTO_DATA構造体型領域を確保し、セーブデータをコピーして返す
 *	　呼び出し側が明示的に解放すること！
 */
PORUTO_DATA* PORUTO_GetDataAlloc(PORUTO_BLOCK* block,u16 idx,int heapID)
{
	PORUTO_DATA* dest;
	
	dest = PorutoData_AllocWork(heapID);
	
	if(idx >= PORUTO_STOCK_MAX){
		PorutoData_Clear(dest);
		return NULL;
	}
	
	//取得
	PorutoData_Copy(&block->poruto[idx],dest);
	return dest;
}

/**
 *	@brief	セーブデータ領域にある有効なポルトデータ数を返す
 */
u16	PORUTO_GetDataNum(PORUTO_BLOCK* block)
{
	u16	num = 0,i;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(PorutoData_IsEnable(&block->poruto[i])){
			++num;
		}
	}
	return num;
}

#ifdef PM_DEBUG
/**
 *	@brief	ポルトデバッグ　データ全部消す
 */
void PorutoDebug_AllDataDelete(PORUTO_BLOCK* block)
{
	u16	i = 0;

	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PorutoData_Clear(&block->poruto[i]);
	}
}

/**
 *	適当なパラメータをランダム生成する
 */
#define PARA_DMYMAX	(99)
#define PARA_DMYNMAX	(48)
static void porudeb_CreateRndParam(PORUTO_DATA* dat,u8 level)
{
	u8	main,sub;
	u8	param[PORUTO_PARAID_NUM];

	MI_CpuClear8(param,PORUTO_PARAID_NUM);

	//メインの味を決める
	main = gf_rand()%PORUTO_FTYPE_MAX;

	//ミックスする味を決める
	sub = gf_rand()%PORUTO_FTYPE_NUM;

	if(main == PORUTO_FTYPE_MIX){
		u8 i,j,ct;
		switch(sub){
		case 0:	//まずい
			for(ct = 0;ct < 3;ct++){
				j = gf_rand()%PORUTO_FTYPE_NUM;
				for(i = 0;i < PORUTO_FTYPE_NUM;i++){
					if(param[j] == 0){
						break;
					}
					j = (j+1)%PORUTO_FTYPE_NUM;	
				}
				param[j] = 2;
			}
			dat->flavor = PORUTO_FLAVOR_NGOOD;
			break;
		case 1:	//まろやか
			i = gf_rand()%PORUTO_FTYPE_NUM;
			j = gf_rand()%PORUTO_FTYPE_NUM;
			param[i] = gf_rand()%(PARA_DMYMAX-PORUTO_MILD_VALUE)+PORUTO_MILD_VALUE;
			param[j] = gf_rand()%(PARA_DMYMAX-PORUTO_MILD_VALUE)+PORUTO_MILD_VALUE;
			dat->flavor = PORUTO_FLAVOR_MILD;
			break;
		default:
			for(ct = 0;ct < (sub+1);ct++){
				j = gf_rand()%PORUTO_FTYPE_NUM;
				for(i = 0;i < PORUTO_FTYPE_NUM;i++){
					if(param[j] == 0){
						break;
					}
					j = (j+1)%PORUTO_FTYPE_NUM;	
				}
				param[j] = gf_rand()%(PARA_DMYMAX-1)+1;
			}
			if(sub == 2){
				dat->flavor = PORUTO_FLAVOR_HEAVY;
			}else{
				dat->flavor = PORUTO_FLAVOR_THICK;
			}
			break;
		}
	}else{
		//メイン
		param[main] = gf_rand()%(PARA_DMYNMAX)+2;
		//サブ
		if(sub != main){	//メイン以下の値を設定
			param[sub] = gf_rand()%(param[main]-1)+1;
		}
		dat->flavor = main*PORUTO_FTYPE_NUM+sub;	//味決定
	}
	//旨味を決定
	if(level > 99){
		dat->taste = 99;//gf_rand()%PARA_DMYMAX;
	}else{
		dat->taste = level;
	}

	//他のパラメータを書き出し
	dat->spicy = param[0];
	dat->astringent = param[1];
	dat->sweet = param[2];
	dat->bitter = param[3];
	dat->sour = param[4];
}

/**
 *	@brief	ポルトデバッグ　テキトーなポルトを指定した数追加
 */
u16 PorutoDebug_AddRndData(PORUTO_BLOCK* block,u16 num)
{
	u16	ret = 0,i;
	
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		if(PorutoData_IsEnable(&block->poruto[i])){
			continue;
		}
		//ランダムなパラメータを入れる
		porudeb_CreateRndParam(&block->poruto[i],ret+1);
		if(++ret >= num){
			return ret;
		}
	}
	return ret;
}

#endif	//PM_DEBUG
