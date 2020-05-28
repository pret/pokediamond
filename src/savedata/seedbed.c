//============================================================================================
/**
 * @file	seedbed.c
 * @author	tamada
 * @date	2005.02.01
 * @brief	きのみ状態データ操作
 */
//============================================================================================

#include "common.h"

#include "seedbed_local.h"
#include "savedata/seedbed.h"

#include "gflib/system.h"
#include "itemtool/nuts.h"

#ifdef	DEBUG_ONLY_FOR_tamada
#define	DEBUG_SEED_INFO
#endif

#ifdef	DEBUG_SEED_INFO
#define	PUT_SEED_INFO(s,i)	PrintSeedInfo((s),(i))
#else
#define	PUT_SEED_INFO(s,i)	/* Do Nothing */
#endif

//============================================================================================
//				定義
//============================================================================================
enum {
		///成長を繰り返す最大数
		SEED_ROUND_MAX		=	10,

		///実がなった状態での成長時間係数
		FRUIT_TIME_RATE		=	4,

		///	土のHP最大値
		GROUND_HP_MAX	= 100,

		///	きのみHPの最大値
		SEED_HP_BASE = 5,
		SEED_HP_MID	= 3,
};

static void InitSeed(SEEDBED * s);
static int get_grow_time(const SEED_TABLE * prm, int type, int compost);
//============================================================================================
//
//
//		セーブデータインターフェイス
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	きのみ状態データサイズの取得
 * @return	int		きのみ状態データのサイズ
 */
//----------------------------------------------------------
int SEEDBED_GetWorkSize(void)
{
	return sizeof(SEEDBED) * SEEDBED_MAX;
}

//----------------------------------------------------------
/**
 * @brief	きのみ状態データ用メモリ確保
 * @param	heapID		確保するヒープの指定
 * @return	SEEDBED		きのみ状態データ全体へのポインタ
 */
//----------------------------------------------------------
SEEDBED * SEEDBED_AllocWork(u32 heapID)
{
	SEEDBED * sbed;
	sbed = sys_AllocMemory(heapID, sizeof(SEEDBED) * SEEDBED_MAX);
	return sbed;
}

//----------------------------------------------------------
/**
 * @brief	きのみ状態データ全体の初期化
 * @param	SEEDBED		きのみ状態データ全体へのポインタ
 */
//----------------------------------------------------------
void SEEDBED_Init(SEEDBED * sbed)
{
	int i;
	MI_CpuClear8(sbed, sizeof(SEEDBED) * SEEDBED_MAX);

	for (i = 0; i < SEEDBED_MAX; i++) {
		sbed[i].stat = SEEDSTAT_NOTHING;
		sbed[i].type = 0;
	}
}

//----------------------------------------------------------
/**
 * @brief	きのみの初期状態セット
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	heapID
 * @param	init_data
 * @param	max
 */
//----------------------------------------------------------
void SEEDBED_SetDefaultData(SEEDBED * sbed, int heapID, const u16 * init_data, int max)
{
	int i;
	SEED_TABLE * prm = SEEDBED_CreateParamTable(heapID);

	for (i = 0; i < SEEDBED_MAX || i < max; i++) {
		InitSeed(&sbed[i]);
			sbed[i].type = init_data[i * 2] - NUTS_START_ITEMNUM + 1;
			sbed[i].stat = SEEDSTAT_FRUIT;
			sbed[i].grow_time = get_grow_time(prm, sbed[i].type, sbed[i].compost) * FRUIT_TIME_RATE;
			sbed[i].nuts_count = init_data[i * 2 + 1];
			sbed[i].ground_hp = GROUND_HP_MAX;
			sbed[i].seed_hp = SEED_HP_MID;
	}
	sys_FreeMemoryEz(prm);
}

//----------------------------------------------------------
/**
 * @brief	きのみ成長処理判定用テーブルの生成
 * @param	heapID
 */
//----------------------------------------------------------
SEED_TABLE * SEEDBED_CreateParamTable(int heapID)
{
	int i;
	SEED_TABLE * tbl;
	NUTSDATA * data;
	ARCHANDLE * hdl;
	hdl = Nuts_DataHandleGet(heapID);
	tbl = sys_AllocMemory(heapID, sizeof(SEED_TABLE) * ITEM_NUTS_MAX);
	for (i = 0; i < ITEM_NUTS_MAX; i++) {
		data = Nuts_DataLoadHandle(hdl, i, heapID);
		tbl[i].grow_speed = Nuts_ParamGet(data, NUTS_PRM_SPEED);
		tbl[i].root_power = Nuts_ParamGet(data, NUTS_PRM_ABSORPTION);
		tbl[i].nuts_rate = Nuts_ParamGet(data, NUTS_PRM_MAGNIFICATION);
		sys_FreeMemoryEz(data);
	}
	Nuts_DataHandleClose(hdl);
	return tbl;
}



//============================================================================================
//
//		内部ツール関数
//
//============================================================================================
#ifdef	DEBUG_SEED_INFO
//----------------------------------------------------------
/**
 * @brief	デバッグ情報の表示
 * @param	bed
 * @param	i
 */
//----------------------------------------------------------
static void PrintSeedInfo(const SEEDBED * bed, int i)
{
	const SEEDBED * s = bed + i;
	if (s->stat == SEEDSTAT_NOTHING) {
		return;
	}
	OS_Printf("SEED (ID:%03d) FLAG:%d STAT:%d TYPE:%02d\n",
			i, s->growth_flag, s->stat, s->type);
	OS_Printf("     COMPOST:%d GROUND:%03d NUTS:%d\n",
			s->compost, s->ground_hp, s->nuts_count);
	OS_Printf("     HP:%02d ROUND:%d gtime:%d dtime:%d\n",
			s->seed_hp, s->seed_count,s->grow_time, s->dry_time);
}
#endif

//----------------------------------------------------------
/**
 * @brief	きのみデータ初期化
 * @param	s	きのみ状態データへのポインタ
 */
//----------------------------------------------------------
static void InitSeed(SEEDBED * s)
{
	s->type = 0;
	s->stat = SEEDSTAT_NOTHING;
	s->grow_time = 0;
	s->dry_time = 0;
	s->seed_count = 0;
	s->nuts_count = 0;
	s->ground_hp = 0;
	s->seed_hp = 0;
	s->compost = SEEDCOMPOST_NOTHING;
	s->growth_flag = FALSE;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int count_nuts(SEEDBED * s, const SEED_TABLE * prm)
{
	//木の実HP　×　実の倍率
	return	prm[s->type -1].nuts_rate * s->seed_hp;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_grow_time(const SEED_TABLE * prm, int type, int compost)
{
	int time;
	time = prm[type - 1].grow_speed * 60;
	if (compost == SEEDCOMPOST_SUKUSUKU) {
		time = (time * 3) / 4;		// base * 0.75
	} else if (compost == SEEDCOMPOST_YURURI) {
		time = time + (time / 2);	// base * 1.5
	}
	return time;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_root_power(const SEED_TABLE * prm, int type, int compost)
{
	int power = prm[type - 1].root_power;
	if (compost == SEEDCOMPOST_YURURI) {
		return power / 2;
	} else if (compost == SEEDCOMPOST_SUKUSUKU) {
		return power + power / 2;
	} else {
		return power;
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_nuts_time_rate(const SEEDBED * s)
{
	//ミナールコヤシを使っているとき、実が生っている時間が1.5倍になる
	if (s->compost == SEEDCOMPOST_MINAARU) {
		return FRUIT_TIME_RATE + 2;
	} else {
		return FRUIT_TIME_RATE;
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_round_max(const SEEDBED * s)
{
	//ねばりこやしを使っているとき、寿命が５回増える
	if (s->compost == SEEDCOMPOST_NEBARI) {
		return SEED_ROUND_MAX + 5;
	} else {
		return SEED_ROUND_MAX;
	}
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
static int get_life_time(SEEDBED * s)
{
	//成長を繰り返して消えるまでの長さ
	//最初の土の中+（芽+茎+花+実) * SEED_ROUND_MAX;
	//LIFE_TIME_LEN		=	1+(1+1+1+FRUIT_TIME_RATE) * SEED_ROUND_MAX,
	return 1 + (1+1+1+get_nuts_time_rate(s)) * get_round_max(s);
}



//============================================================================================
//
//
//		きのみ状態アクセス用外部公開関数
//
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	きのみの状態取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @return	SEEDSTAT	きのみの状態（seedbed.hの定義を参照）
 */
//----------------------------------------------------------
SEEDSTAT SEEDBED_GetSeedStatus(const SEEDBED * sbed, int id)
{
	return sbed[id].stat;
}
//----------------------------------------------------------
/**
 * @brief	きのみの種類を取得
 * @param	sbed		きのみ状態データへのポインタ
 * @param	id			きのみを指定するID
 * @return	int			きのみの種類（０～ITEM_NUTS_MAX)
 */
//----------------------------------------------------------
int SEEDBED_GetSeedType(const SEEDBED * sbed, int id)
{
	return sbed[id].type;
}
//----------------------------------------------------------
/**
 * @brief	水やりの状態を取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @return	SEEDGROUND	水やり状態（seedbed.hの定義を参照）
 */
//----------------------------------------------------------
SEEDGROUND SEEDBED_GetGroundStatus(const SEEDBED * sbed, int id)
{
	int gr_hp;
	gr_hp = sbed[id].ground_hp;

	if (gr_hp == 0) {
		return SEEDGROUND_DRY;
	} else if (gr_hp <= 50) {
		return SEEDGROUND_WET;
	} else {
		return SEEDGROUND_FULL;
	}
}
//----------------------------------------------------------
/**
 * @brief	きのみのHPを取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @return	int			きのみのHP（０～１０）
 */
//----------------------------------------------------------
int SEEDBED_GetSeedHP(const SEEDBED * sbed, int id)
{
	return	sbed[id].seed_hp;
}


//----------------------------------------------------------
/**
 * @brief	きのみを植える
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @param	prm			きのみの種類毎パラメータテーブル
 * @param	type		きのみの種類
 */
//----------------------------------------------------------
void SEEDBED_SetNuts(SEEDBED * sbed, int id, const SEED_TABLE * prm, int type)
{
	//InitSeed(&sbed[id]);
	sbed[id].type = type;
	sbed[id].stat = SEEDSTAT_UNDERGROUND;
	sbed[id].grow_time = get_grow_time(prm, type, sbed[id].compost);
	sbed[id].dry_time = 0;
	sbed[id].seed_count = 0;
	sbed[id].nuts_count = 0;
	sbed[id].ground_hp = GROUND_HP_MAX;
	sbed[id].seed_hp = SEED_HP_BASE;
	//sbed[id].compost = co;
	sbed[id].growth_flag = TRUE;
	PUT_SEED_INFO(sbed,id);
}


//----------------------------------------------------------
/**
 * @brief	水をあげる
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 */
//----------------------------------------------------------
void SEEDBED_SetSeedWater(SEEDBED * sbed, int id)
{
	sbed[id].ground_hp = GROUND_HP_MAX;
	PUT_SEED_INFO(sbed, id);
}

//----------------------------------------------------------
/**
 * @brief	成長フラグの取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @return	BOOL		TRUEのとき、成長する
 */
//----------------------------------------------------------
BOOL SEEDBED_GetGrowthFlag(const SEEDBED * sbed, int id)
{
	return sbed[id].growth_flag;
}

//----------------------------------------------------------
/**
 * @brief	成長フラグのセット
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @param	flag		TRUEのとき、成長する
 */
//----------------------------------------------------------
void SEEDBED_SetGrowthFlag(SEEDBED * sbed, int id, BOOL flag)
{
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_Printf("SEED:%d %s\n",id, (flag?"ON":"OFF"));
#endif
	sbed[id].growth_flag = flag;
}

//----------------------------------------------------------
/**
 * @brief	コヤシの種類を取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @param	compost		コヤシの指定
 */
//----------------------------------------------------------
SEEDCOMPOST SEEDBED_GetCompost(const SEEDBED * sbed, int id)
{
	return sbed[id].compost;
}

//----------------------------------------------------------
/**
 * @brief	コヤシをセットする
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 * @param	compost		コヤシの指定
 */
//----------------------------------------------------------
void SEEDBED_SetCompost(SEEDBED * sbed, int id, SEEDCOMPOST compost)
{
	sbed[id].compost = compost;
	PUT_SEED_INFO(sbed,id);
}
//----------------------------------------------------------
/**
 * @brief	きのみの数を取得
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 */
//----------------------------------------------------------
int SEEDBED_GetSeedCount(const SEEDBED * sbed, int id)
{
	PUT_SEED_INFO(sbed, id);
	return sbed[id].nuts_count;
}

//----------------------------------------------------------
/**
 * @brief	きのみを収穫
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	id			きのみを指定するID
 */
//----------------------------------------------------------
int SEEDBED_GetHarvest(SEEDBED * sbed, int id)
{
	int harvest;
	harvest = sbed[id].nuts_count;
	InitSeed(&sbed[id]);
	PUT_SEED_INFO(sbed,id);
	return harvest;
}

//-------------------------------------------------------------------------
/**
 * @brief	きのみを育てる
 * @param	sbed		きのみ状態データへのポインタ
 * @param	prm		きのみの種類毎パラメータテーブル
 */
//-------------------------------------------------------------------------
static void SeedGrowth(SEEDBED *s, const SEED_TABLE * prm)
{
	switch (s->stat) {

	case SEEDSTAT_NOTHING:		// 植えていない
		GF_ASSERT(0);
		break;

	case SEEDSTAT_UNDERGROUND:	// 植えた直後
	case SEEDSTAT_HUTABA:		// 双葉、発芽直後
	case SEEDSTAT_MIKI:			// 幹、成長後
		s->stat ++;
		break;

	case SEEDSTAT_FLOWER:		// 花
		s->nuts_count = count_nuts(s, prm);
		if (s->nuts_count < 2) {
			//最低2個は実がなる
			s->nuts_count = 2;
		}
		s->stat ++;
		break;

	case SEEDSTAT_FRUIT:		// 実がなった状態
		s->nuts_count = 0;
		s->stat = SEEDSTAT_HUTABA;
		//s->ground_hp = GROUND_HP_MAX;
		s->seed_hp = SEED_HP_BASE;
		s->seed_count ++;
		if (s->seed_count == get_round_max(s)) {
			InitSeed(s);
		}
		break;
	}
}

//----------------------------------------------------------
/**
 * @brief	水の吸収処理
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	prm			きのみの種類毎パラメータテーブル
 * @param	minute		進んだ時間（分単位）
 */
//----------------------------------------------------------
static void AbsorbWater(SEEDBED * s, const SEED_TABLE * prm, int count)
{
	int dec_count;
	int root_pow;
	int rest_count;
	if (s->stat == SEEDSTAT_FRUIT) {
		//実がなっている状態ではＨＰは変化しない
		return;
	}
	root_pow = get_root_power(prm, s->type, s->compost);
	count += s->dry_time;
	dec_count = count / 60;		//1時間＝１ポイント
	s->dry_time = count % 60;	//あまりは集計しておく
	if (dec_count == 0) {
		return;
	}
	if (s->ground_hp >= root_pow * dec_count) {
		s->ground_hp -= root_pow * dec_count;
		return;
	}

	if (s->ground_hp > 0) {
		//土のHPを減らすのに何時間必要か（切り上げ）で計算
		rest_count = (s->ground_hp + (root_pow - 1)) / root_pow;
		dec_count -= rest_count;
		s->ground_hp = 0;
	}

	//水に余地がなくなったのでポイントだけきのみHPを減らす
	if (s->seed_hp > dec_count) {
		s->seed_hp -= dec_count;
	} else {
		s->seed_hp = 0;
	}
}

//----------------------------------------------------------
/**
 * @brief	きのみを成長させる
 * @param	sbed		きのみ状態データ全体へのポインタ
 * @param	prm		きのみの種類毎パラメータテーブル
 * @param	minute		進んだ時間（分単位）
 */
//----------------------------------------------------------
void SEEDBED_Growth(SEEDBED * sbed, const SEED_TABLE * prm, int minute)
{
	int i;
	s32 count;
	SEEDBED * s;

	for (i = 0; i < SEEDBED_MAX; i++) {
		s = &sbed[i];
		if ( s->type == 0
				|| s->stat == SEEDSTAT_NOTHING
				|| s->growth_flag == FALSE) {
			//種類指定がない、木の実が植えられていない、成長しない場合は次へ
			continue;
		}
		if (minute >= get_grow_time(prm, s->type, s->compost) * get_life_time(s)) {
			//寿命以上の時間が経過した場合は初期化する
			InitSeed(s);
			continue;
		}

		//成長カウント処理
		count = minute;

		while (s->stat != SEEDSTAT_NOTHING && count != 0) {
			if (s->grow_time > count) {
				//水吸収カウント処理
				AbsorbWater(s, prm, count);
				s->grow_time -= count;
				count = 0;
				break;
			}else{
				//水吸収カウント処理
				AbsorbWater(s, prm, s->grow_time);
				//成長する
				SeedGrowth(s, prm);
				//次の段階までのカウントをセット
				count -= s->grow_time;
				s->grow_time = get_grow_time(prm, s->type, s->compost);
				if (s->stat == SEEDSTAT_FRUIT) {
					s->grow_time *= get_nuts_time_rate(s);
				}
				PUT_SEED_INFO(sbed,i);
			}
		}

	}
}


