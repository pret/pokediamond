
#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"

#include "savedata/custom_ball.h"
#include "savedata/custom_ball_local.h"
#include "include/application/seal_id.h"

//--------------------------------------------------------------
/**
 * @brief	カスタムボールのサイズを取得
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CustomBall_GetWorkSize(void)
{
	return sizeof(CB_SAVE_DATA);
}


//--------------------------------------------------------------
/**
 * @brief	カスタムボールのワークを作成
 *
 * @param	heap_id	
 *
 * @retval	CB_SAVE_DATA*	
 *
 */
//--------------------------------------------------------------
CB_SAVE_DATA*	CustomBall_AllocSaveData(u32 heap_id)
{
	CB_SAVE_DATA* csd = NULL;
	int size;
	
	size = CustomBall_GetWorkSize();
	
	csd = sys_AllocMemory(heap_id, size); 
	
	CustomBall_Init(csd);
	
	return csd;
}


//--------------------------------------------------------------
/**
 * @brief	カスタムボールの初期化
 *
 * @param	csd	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CustomBall_Init(CB_SAVE_DATA* csd)
{
	int size;
	
	size = CustomBall_GetWorkSize();
	
	MI_CpuFill8(csd, 0, size);
}



// =============================================================================
//
//
//	■ツールっぽいもの
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	セーブデータをコピーする
 *
 * @param	from	
 * @param	to	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_SaveData_Copy(const CB_SAVE_DATA* from, CB_SAVE_DATA* to)
{
	MI_CpuCopy8(from, to, sizeof(CB_SAVE_DATA));
}


//--------------------------------------------------------------
/**
 * @brief	コア(Edit)データをコピーする
 *
 * @param	from	
 * @param	to	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_CoreData_Copy(const CB_CORE* from, CB_CORE* to)
{
	MI_CpuCopy8(from, to, sizeof(CB_CORE));
}


//--------------------------------------------------------------
/**
 * @brief	シールデータをコピーする
 *
 * @param	from	
 * @param	to	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_Tool_SealData_Copy(const CB_SEAL* from, CB_SEAL* to)
{
	MI_CpuCopy8(from, to, sizeof(CB_SEAL));
}




// =============================================================================
//
//
//	■セーブデータへのアクセス関数
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	カスタムボールのセーブデータを取得する
 *
 * @param	sv	
 *
 * @retval	CB_SAVE_DATA*	
 *
 */
//--------------------------------------------------------------
CB_SAVE_DATA* CB_SaveData_AllDataGet(SAVEDATA* sv)
{
	CB_SAVE_DATA* cbs = NULL;
	
	cbs = SaveData_Get(sv, GMDATA_ID_CUSTOM_BALL);
	
	return cbs;
}


//--------------------------------------------------------------
/**
 * @brief	コア(Edit)データを取得する
 *
 * @param	save	
 * @param	no	
 *
 * @retval	CB_CORE*	
 *
 */
//--------------------------------------------------------------
CB_CORE* CB_SaveData_CoreDataGet(CB_SAVE_DATA* save, int no)
{
	GF_ASSERT(no < CB_DEF_CORE_MAX);
	
	return &save->cb_core[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	コアデータを設定する
 *
 * @param	save	
 * @param	core	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_SaveData_CoreDataSet(CB_SAVE_DATA* save, CB_CORE* core, int no)
{
	CB_CORE* to;
	
	GF_ASSERT(no < CB_DEF_CORE_MAX);

	to = CB_SaveData_CoreDataGet(save, no);

	CB_Tool_CoreData_Copy(core, to);
}


//--------------------------------------------------------------
/**
 * @brief	シールデータを取得する
 *
 * @param	core	
 * @param	no	
 *
 * @retval	CB_SEAL*	
 *
 */
//--------------------------------------------------------------
CB_SEAL* CB_SaveData_SealDataGet(CB_CORE* core, int no)
{
	GF_ASSERT(no < CB_DEF_SEAL_MAX);

	return &core->cb_seal[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	シールデータを設定する
 *
 * @param	save	
 * @param	core	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_SaveData_SealDataSet(CB_CORE* core, CB_SEAL* seal, int no)
{
	CB_SEAL* to;
	
	GF_ASSERT(no < CB_DEF_SEAL_MAX);
	
	to = CB_SaveData_SealDataGet(core, no);
	
	CB_Tool_SealData_Copy(seal, to);
}


//--------------------------------------------------------------
/**
 * @brief	シールのIDを取得する
 *
 * @param	seal	
 *
 * @retval	u8	
 *
 */
//--------------------------------------------------------------
u8 CB_SaveData_SealIDGet(const CB_SEAL* seal)
{
	return seal->seal_id;
}


//--------------------------------------------------------------
/**
 * @brief	シールの座標Xを取得する
 *
 * @param	seal	
 *
 * @retval	u8	
 *
 */
//--------------------------------------------------------------
u8 CB_SaveData_SealPXGet(const CB_SEAL* seal)
{
	return seal->x;
}


//--------------------------------------------------------------
/**
 * @brief	シールの座標Yを取得する
 *
 * @param	seal	
 *
 * @retval	u8	
 *
 */
//--------------------------------------------------------------
u8 CB_SaveData_SealPYGet(const CB_SEAL* seal)
{
	return seal->y;
}


//--------------------------------------------------------------
/**
 * @brief	アイテムデータの取得
 *
 * @param	save	
 *
 * @retval	CB_ITEM_DATA*	
 *
 */
//--------------------------------------------------------------
CB_ITEM_DATA* CB_SaveData_ItemDataGet(CB_SAVE_DATA* save)
{
	return &save->cb_item;
}


//--------------------------------------------------------------
/**
 * @brief	アイテムの種類取得
 *
 * @param	save	
 * @param	no	
 *
 * @retval	u8	
 *
 */
//--------------------------------------------------------------
u8 CB_SaveData_ItemTypeGet(const CB_ITEM_DATA* item, int no)
{
	return 0;
}


//--------------------------------------------------------------
/**
 * @brief	アイテムの種類設定
 *
 * @param	save	
 * @param	no	
 * @param	type	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_SaveData_ItemTypeSet(CB_ITEM_DATA* item, int no, int type)
{
	;
}


//--------------------------------------------------------------
/**
 * @brief	アイテムの個数取得
 *
 * @param	save	
 * @param	no	
 *
 * @retval	u8	
 *
 */
//--------------------------------------------------------------
u8 CB_SaveData_ItemNumGet(const CB_ITEM_DATA* item, int no)
{
	GF_ASSERT(no != 0);
	
	OS_Printf("id = %2d, num = %2d\n", no - CB_DEF_INDEX_ORIGIN, item->seal[ no - CB_DEF_INDEX_ORIGIN ]);
	
	return item->seal[ no - CB_DEF_INDEX_ORIGIN ];
}

///< カプセルだけ使える
u8 CB_SaveData_ItemNumGet_CBO(const CB_ITEM_DATA* item, int no)
{
	return item->seal[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	シールを持っているかチェック
 *
 * @param	save	
 * @param	id	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
BOOL CB_Tool_IsSeal(const CB_SAVE_DATA* save, int id)
{
	int i,j;
	
	if (save->cb_item.seal[ id ] != 0){
		return TRUE;
	}
	
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		for (j = 0; j < CB_DEF_SEAL_MAX; j++){
			
			if (save->cb_core[ i ].cb_seal[ j ].seal_id == (id + 1)){
				
				return TRUE;
				
			}
			
		}
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	コアデータからシールを検出
 *
 * @param	cb_core	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL CB_Tool_IsSealCore(const CB_CORE* cb_core, int id)
{
	int i,j;
		
	for (j = 0; j < CB_DEF_SEAL_MAX; j++){
		
		if (cb_core->cb_seal[ j ].seal_id == (id + 1)){
			
			return TRUE;
			
		}
		
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	カプセルに貼られたシールが何枚あるかチェック
 *
 * @param	save	
 * @param	id	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
int CB_Tool_IsSealTotalNum(const CB_SAVE_DATA* save, int id)
{
	int i,j;
	
	int num;
	
	num = 0;
	
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		for (j = 0; j < CB_DEF_SEAL_MAX; j++){

			if (save->cb_core[ i ].cb_seal[ j ].seal_id == (id + 1)){
				
				num++;
				
			}
			
		}
	}
	return num;
}

//--------------------------------------------------------------
/**
 * @brief	アイテムの個数設定
 *
 * @param	save	
 * @param	no	
 * @param	stock	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_SaveData_ItemNumSet(CB_ITEM_DATA* item, int no, int stock)
{
	item->seal[ no ] = stock;
}

//--------------------------------------------------------------
/**
 * @brief	アイテムの個数変更
 *
 * @param	save	
 * @param	no	
 * @param	stock	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void CB_SaveData_ItemNumAdd(CB_ITEM_DATA* save, int no, s16 stock)
{
	save->seal[ no ] += stock;
}


//--------------------------------------------------------------
/**
 * @brief	加減する
 *
 * @param	save	
 * @param	no	
 * @param	stock	
 *
 * @retval	BOOL	FALSE = 加減できなかった
 *
 */
//--------------------------------------------------------------
BOOL CB_SaveData_ItemNumAddCheck(CB_SAVE_DATA* save, int no, s16 stock)
{
	int num;
	int total;
	
	///< すでにマックス
	
	num = CB_Tool_IsSealTotalNum(save, no - CB_DEF_INDEX_ORIGIN);
	
	total = num + save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ];
	
	if (stock < 0){
		///< 減らす
		if (save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] + stock >= 0){
			save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] += stock;
		}
		else {
			return FALSE;
		}
	}
	else {
		///< 増やす
		OS_Printf("now set = %2d, now num = %2d, add = %2d\n", num, save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ], stock);
		if (total + stock <= CB_DEF_SEAL_STOCK_MAX){
			save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] += stock;
		}
		else {
			return FALSE;
		}
	}
	return TRUE;
}


BOOL CB_SaveData_ItemNumAddCheck_CBO(CB_SAVE_DATA* save, int no, s16 stock)
{
	int num;
	int total;
	
	///< すでにマックス
	
	num = CB_Tool_IsSealTotalNum(save, no - CB_DEF_INDEX_ORIGIN);
	
	total = num;// + save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ];
	
	if (stock < 0){
		///< 減らす
		if (save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] + stock >= 0){
			save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] += stock;
		}
		else {
			return FALSE;
		}
	}
	else {
		///< 増やす
		OS_Printf("now set = %2d, now num = %2d, add = %2d\n", num, save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ], stock);
		if (total + stock <= CB_DEF_SEAL_STOCK_MAX){
			save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] += stock;
			if (save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] >= CB_DEF_SEAL_STOCK_MAX){
				save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] = CB_DEF_SEAL_STOCK_MAX;
			}
		}
		else {
			return FALSE;
		}
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	追加できるかチェック (実際に加減しない)
 *
 * @param	save	
 * @param	no	
 * @param	stock	
 *
 * @retval	BOOL	TRUE = できる
 *
 */
//--------------------------------------------------------------
BOOL CB_SaveData_IsAddIt(CB_SAVE_DATA* save, int no, s16 stock)
{
	int num;
	int total;
	
	///< すでにマックス
	
	num = CB_Tool_IsSealTotalNum(save, no - CB_DEF_INDEX_ORIGIN);
	
	total = num + save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ];
	
	if (stock < 0){
		///< 減らす
		if (save->cb_item.seal[ no - CB_DEF_INDEX_ORIGIN ] + stock >= 0){
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		///< 増やす
		if (total + stock <= CB_DEF_SEAL_STOCK_MAX){
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	return TRUE;	
}

//--------------------------------------------------------------
/**
 * @brief	何種類のシールを持っているか
 *
 * @param	save	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CB_Tool_SealCllectionGet(const CB_SAVE_DATA* save)
{
	int i;
	int num;
	
	num = 0;
	
	#if 0
	for (i = 0; i < CB_DEF_ITEM_DATA_NUM; i++){
		if (save->cb_item.seal[i] != 0){
			num++;
		}
	}
	#endif
	
	for (i = CB_DEF_INDEX_ORIGIN; i < CB_DEF_ITEM_DATA_NUM; i++){
		
		if (CB_Tool_SealTotalNumGet(save, i) != 0){
			num++;
		}
		
	}
	
	return num;
}


//--------------------------------------------------------------
/**
 * @brief	そのシールの総数
 *
 * @param	save	
 * @param	id	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int CB_Tool_SealTotalNumGet(const CB_SAVE_DATA* save, int id)
{
	int num;
	int total;
	
	num = CB_Tool_IsSealTotalNum(save, id - CB_DEF_INDEX_ORIGIN);
	
	total = num + save->cb_item.seal[ id - CB_DEF_INDEX_ORIGIN ];
	
	return total;
}














#ifdef PM_DEBUG

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
void Debug_CB_SaveData_Poke_Sample(SAVEDATA * save, int mode)
{
	int i;
	int id = 1;
	int poke_cnt;
	POKEMON_PARAM* pp;
	POKEPARTY* pparty = SaveData_GetTemotiPokemon(save);
	poke_cnt = PokeParty_GetPokeCount(pparty);

	for (i = 0; i < poke_cnt; i++){
		pp = PokeParty_GetMemberPointer(pparty, i);
		PokeParaPut(pp, ID_PARA_cb_id, (u8*)(&id));
		id++;
	}
}

void Debug_CB_SaveData_Sample(CB_SAVE_DATA* save, int mode)
{
	CB_ITEM_DATA* item;
	
	item = CB_SaveData_ItemDataGet(save);
	
	{
		int i;
		
		switch(mode){
		case DEBUG_CB_MODE_CLEAR:
		//	item->seal[ SEAL_ID_ALPHA_A - CB_DEF_INDEX_ORIGIN ] = 99;
		//	break;
			for (i = CB_DEF_INDEX_ORIGIN; i < CB_DEF_ITEM_DATA_NUM; i++){
				if (i % 2){
					item->seal[ i - CB_DEF_INDEX_ORIGIN ] = 80;
				}
				else {
					item->seal[ i - CB_DEF_INDEX_ORIGIN ] = i;
				}
			}
			break;
		case DEBUG_CB_MODE_ITEM_FULL:
			for (i = CB_DEF_INDEX_ORIGIN; i < 5; i++){
				item->seal[ i - CB_DEF_INDEX_ORIGIN ] = 3;
			}
			for (;i< CB_DEF_ITEM_DATA_NUM; i++){
				item->seal[ i - CB_DEF_INDEX_ORIGIN ] = 0;
			}
			break;
		case DEBUG_CB_MODE_ITEM_RANDOM:
			for (i = CB_DEF_INDEX_ORIGIN; i < CB_DEF_ITEM_DATA_NUM; i++){
				item->seal[ i - CB_DEF_INDEX_ORIGIN] = 6; ///< 適当
			}
			{
				CB_CORE core;				
				core.cb_seal[0].seal_id = 1;
				core.cb_seal[1].seal_id = 2;
				core.cb_seal[2].seal_id = 3;
				core.cb_seal[3].seal_id = 0;
				core.cb_seal[4].seal_id = 0;
				core.cb_seal[5].seal_id = 3;
				core.cb_seal[6].seal_id = 1;
				core.cb_seal[7].seal_id = 2;
				for (i = 0; i < 8; i++){
					core.cb_seal[i].x = 140 + (gf_rand() % 100);		
					core.cb_seal[i].y =  20 + (gf_rand() % 100);
				}
				CB_SaveData_CoreDataSet(save, &core, 0);
				CB_SaveData_CoreDataSet(save, &core, 1);
				CB_SaveData_CoreDataSet(save, &core, 2);
				CB_SaveData_CoreDataSet(save, &core, 3);
				CB_SaveData_CoreDataSet(save, &core, 4);
				CB_SaveData_CoreDataSet(save, &core, 6);
				CB_SaveData_CoreDataSet(save, &core, 8);
				CB_SaveData_CoreDataSet(save, &core,10);
				CB_SaveData_CoreDataSet(save, &core,11);
			}
			break;
		}

	}
}

void Debug_CB_Set(POKEMON_PARAM* pp)
{
	int id;
	CB_CORE core;
	
	id = 1;

	PokeParaPut(pp, ID_PARA_cb_id, (u8*)(&id));
#if 1
	{
		int i;
		
		for (i = 0; i < 8; i++){
			core.cb_seal[ i ].seal_id = 25;
			core.cb_seal[ i ].x = 190;
			core.cb_seal[ i ].y = 70;
		}
		
		PokeParaPut(pp, ID_PARA_cb_core, &core);
		return;
	}
#endif

	{
		int i;
		
		for (i = 0; i < 8; i++){
			core.cb_seal[ i ].seal_id = 0;
			core.cb_seal[ i ].x = 190;
			core.cb_seal[ i ].y = 70;
		}
		core.cb_seal[ 0 ].seal_id = 56;
		core.cb_seal[ 1 ].seal_id = 55;
		core.cb_seal[ 2 ].seal_id = 77;
		core.cb_seal[ 0 ].x = 160;
		core.cb_seal[ 0 ].y = 40;
		core.cb_seal[ 1 ].x = 190;
		core.cb_seal[ 1 ].y = 40;
		core.cb_seal[ 2 ].x = 210;
		core.cb_seal[ 2 ].y = 40;
		
		core.cb_seal[ 3 ].seal_id = 56;
		core.cb_seal[ 4 ].seal_id = 55;
		core.cb_seal[ 5 ].seal_id = 76;
		core.cb_seal[ 3 ].x = 160;
		core.cb_seal[ 3 ].y = 80;
		core.cb_seal[ 4 ].x = 190;
		core.cb_seal[ 4 ].y = 80;
		core.cb_seal[ 5 ].x = 210;
		core.cb_seal[ 5 ].y = 80;
		
		core.cb_seal[ 6 ].seal_id = 79;
		core.cb_seal[ 7 ].seal_id = 80;
	}
	
	PokeParaPut(pp, ID_PARA_cb_core, &core);
}

#endif

