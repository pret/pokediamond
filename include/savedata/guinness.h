/**
 *	@brief	ギネスホール　セーブデータアクセス
 */

#ifndef __H_GUINNESS_H__
#define __H_GUINNESS_H__

#define GNS_RECORD_NUM	(13)	//レコード内のデータ数
#define GNS_BLOCK_NUM	(GNS_RECORD_NUM*2)	//ブロック数
#define GNS_DATA_NUM	(6)		//1ブロックのデータ数

///ギネスデータタイプID
typedef enum{
 GNSTYPE_BTL,		///<バトル
 GNSTYPE_POKE,		///<ポケモン
 GNSTYPE_CONTEST,	///<コンテスト
}GNSTYPE;

///ギネスブロックデータID
typedef enum{
 GNSID_GLB_SINGLE,		///<グローバル　タワーシングル最大連勝
 GNSID_GLB_DOUBLE,		///<グローバル　タワーダブル最大連勝
 GNSID_GLB_MULTI,		///<グローバル　タワーAIマルチ最大連勝
 GNSID_GLB_CMULTI,		///<グローバル　タワー通信マルチ最大連勝
 GNSID_GLB_WIFI,		///<グローバル　タワーWifi最大連勝
 GNSID_GLB_WIN,			///<グローバル　タワー平均勝ち抜き数
 GNSID_GLP_KILL,		///<グローバル　倒したポケモン数
 GNSID_GLP_CAPUTURE,	///<グローバル　捕まえたポケモン数
 GNSID_GLP_HATCHING,	///<グローバル　孵したポケモン数
 GNSID_GLP_FISHING,		///<グローバル　釣り上げたポケモン数
 GNSID_GLC_GPX,			///<グローバル　コンテスト優勝
 GNSID_GLC_GPXPER,		///<グローバル　コンテスト優勝率
 GNSID_GLC_RIBBON,		///<グローバル　コンテストリボン獲得数
 
 GNSID_GRB_SINGLE,		///<グループ　タワーシングル最大連勝
 GNSID_GRB_DOUBLE,		///<グループ　タワーダブル最大連勝
 GNSID_GRB_MULTI,		///<グループ　タワーAIマルチ最大連勝
 GNSID_GRB_CMULTI,		///<グループ　タワー通信マルチ最大連勝
 GNSID_GRB_WIFI,		///<グループ　タワーWifi最大連勝
 GNSID_GRB_WIN,			///<グループ　タワー平均勝ち抜き数
 GNSID_GRP_KILL,		///<グループ　倒したポケモン数
 GNSID_GRP_CAPUTURE,	///<グループ　捕まえたポケモン数
 GNSID_GRP_HATCHING,	///<グループ　孵したポケモン数
 GNSID_GRP_FISHING,		///<グループ　釣り上げたポケモン数
 GNSID_GRC_GPX,			///<グループ　コンテスト優勝
 GNSID_GRC_GPXPER,		///<グループ　コンテスト優勝率
 GNSID_GRC_RIBBON,		///<グループ　コンテストリボン獲得数
}GNSID;

/**
 *	@brief	ギネスランキングデータ公開データ型
 *
 *	ギネスのランキングデータを取得するとき、この型で個々のデータを扱う
 */
typedef struct _GNS_RECORD{
	u32	groupID;
	u32	record;
	STRBUF	*name;
}GNS_RECORD;

typedef struct _GNS_RANKING{
	int				num;	//有効データ数
	GNS_RECORD	rank[GNS_DATA_NUM];	//個々のデータ
}GNS_RANKING;

/**
 * @brief	ギネスホールセーブデータ構造体への不完全型ポインタ
 *
 * 中身は見えませんがポインタ経由で参照できます
 */
typedef struct _GUINNESS_DATA	GUINNESS_DATA;
typedef struct _GUINNESS_BLOCK	GUINNESS_BLOCK;
typedef struct _GUINNESS_RECORD	GUINNESS_RECORD;
typedef struct _GUINNESS	GUINNESS;

#undef GLOBAL
#ifdef __GUINNESS_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

//===================================================================
///ギネスデータ関連
//===================================================================
/**
 *	@brief	ギネスデータ　クリア
 */
GLOBAL void GNS_DataClear(GUINNESS_DATA* dat);
/**
 *	@brief	ギネスデータが有効かどうか？
 *
 *	＊名前文字列がNULL文字列なら空
 */
GLOBAL BOOL GNS_IsEnable(GUINNESS_DATA* dat);

/**
 *	@brief	ギネスデータ　コピー
 */
GLOBAL void GNS_DataCopy(const GUINNESS_DATA* src,GUINNESS_DATA* dest);

//===================================================================
///ギネスホールデータ関連
//===================================================================
/**
 *	@brief	ギネスホール　データサイズ
 */
GLOBAL int	GuinnessData_GetWorkSize(void);

/**
 *	@brief	ギネスホール　データ初期化
 */
GLOBAL void GuinnessData_Init(GUINNESS* dat);

/**
 *	@brief	ギネスホール　データブロックへのポインタを取得
 */
GLOBAL GUINNESS* SaveData_GetGuinnessData(SAVEDATA* sv);

/**
 *	@brief	ギネス　指定したデータを消去する
 */
GLOBAL void GuinnessData_DelRecord(GUINNESS* dat,GNSID id,u8 idx);

//===================================================================
///ギネス　レコードデータ関連
//===================================================================
/**
 *	@brief	ギネス　レコード送信データサイズ取得
 */
GLOBAL int GuinnessRecord_GetWorkSize(void);

/**
 *	@brief	ギネス　レコード送信データ作成
 */
GLOBAL void* GuinnessRecord_SendDataAlloc(SAVEDATA* sv,int heapID);

/**
 *	@brief	ギネス　レコードMix
 */
GLOBAL void GuinnessRecord_RecvDataMix(SAVEDATA* sv,
		int myid,u8 datanum,const void** array,int heapID);

//===================================================================
///ギネスランキングデータ関連
//===================================================================
///タイプ別のブロック数を返す
GLOBAL u8 GNSRank_GetTypeBlockNum(GNSTYPE type);
///タイプ別のGNSIDオフセットを返す
GLOBAL u8 GNSRank_GetTypeGNSIDOfs(GNSTYPE type);

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
GNS_RANKING* GNSRank_AllocMyData(SAVEDATA* sv,GNSTYPE type,int heapID);

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
GLOBAL GNS_RANKING* GNSRank_AllocRankingData(GUINNESS* gns,GNSID id,int heapID);

/**
 *	@brief	ギネスランキングデータ解放
 *
 *	＊GNSRank_GetRankingData()関数を用いて取得した
 *	　メモリ領域を開放する
 */
GLOBAL void GNSRank_FreeRankingData(GNS_RANKING* dat);

/**
 *	@brief	ギネスランキングデータセット
 *
 *	ランキングソート済みデータをGNS_RANKING型に格納して
 *	引渡し、セーブデータにセットする
 */
GLOBAL void GNSRank_SetRankingData(GUINNESS* gns,GNSID id,GNS_RANKING* dat);


#ifdef PM_DEBUG
/**
 *	@brief	デバッグ専用　ギネスランキングデータ　ダミー生成
 */
GLOBAL void DebugGNSRank_MakeDmyRankingData(GUINNESS* gns);

#endif	//PM_DEBUG





#endif	//__H_GUINNESS_H__
