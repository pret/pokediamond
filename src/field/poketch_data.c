//============================================================================================
/**
 * @file	poketch_data.c
 * @bfief	ポケッチデータアクセス用ソース
 * @author	taya GAME FREAK inc.
 * @date	2005.10.27
 */
//============================================================================================

#include "system/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"
#include "gflib/system.h"
#include "system/savedata.h"
#include "poketool\pokeicon.h"

#include "field/poketch_data.h"



//============================================================================================
//============================================================================================
enum {
	APP_REGIST_MAX = 32,	///< アプリの最大数と合わないが、セーブデータサイズをいじりたくないのでこのまま
	POKETCH_DEFAULT_APPNO = POKETCH_APPID_DWATCH,	// デフォルトで登録されてるアプリ
};


//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ポケッチデータ用構造体定義
 */
//----------------------------------------------------------
struct _POKETCH_DATA {
	u8		get_flag : 1;		///< ポケッチを取得したフラグ
	u8		pedometer_flag : 1;	///< アプリ『万歩計』を取得したフラグ
	u8		dotart_modified_flag : 1;	///< アプリ『ドットアート』編集したフラグ
	u8		color_type : 3;		///< カラータイプ（0～7）
	u8		 : 2;

	s8		app_count;			///< 登録されているアプリ数
	s8		app_index;			///< 現在表示中のアプリ（登録テーブルインデックス）


	u8		app_flag[APP_REGIST_MAX];	///< 取得したアプリID登録テーブル

	u32		pedometer;			///< 『万歩計』歩数

	u16		alarm_switch : 1;		///< アプリ『アラーム時計』スイッチ
	u16		alarm_hour   : 5;		///< アプリ『アラーム時計』時
	u16		alarm_minute : 6;		///< アプリ『アラーム時計』分
	u16		 : 4;

	//-------------------
	u8		dotart_data[POKETCH_DOTART_DATA_BYTESIZE];	///< 『ドットアート』保存データ

	//-------------------
	u32		calendar_markbit;	///< 『カレンダー』マークビットフラグ
	u8		calendar_month;		///< 『カレンダー』マークした月

	//-------------------
	struct {
		u8   x;
		u8   y;
	}mark_map_pos[ POKETCH_MAP_MARK_MAX ];	///< 『マップマーキング』マーク位置

	//--------------------
	struct {
		u16  monsno;
		u16  iconPattern;
	}poke_history[ POKETCH_POKE_HISTORY_COUNT_MAX ];

};

//============================================================================================
//	セーブデータシステムが依存する関数
//============================================================================================

//------------------------------------------------------------------
/**
 * ワークサイズ取得
 *
 * @retval  int		ワークサイズ
 */
//------------------------------------------------------------------
int PoketchData_GetWorkSize(void)
{
	return sizeof(POKETCH_DATA);
}
//------------------------------------------------------------------
/**
 * ワーク用メモリをアロケート＆初期化して返す
 *
 * @param   heapID		アロケート用ヒープＩＤ
 *
 * @retval  POKETCH_DATA *		初期化済みワーク領域のポインタ
 */
//------------------------------------------------------------------
POKETCH_DATA * PoketchData_AllocWork(u32 heapID)
{
	POKETCH_DATA * pk;
	pk = sys_AllocMemory(heapID, sizeof(POKETCH_DATA));
	PoketchData_Init( pk );
	return pk;
}

//============================================================================================
//	POKETCH_DATA操作のための関数
//============================================================================================

//------------------------------------------------------------------
/**
 * ワーク領域初期化
 *
 * @param   poketch_data		ワークポインタ
 *
 */
//------------------------------------------------------------------
void PoketchData_Init(POKETCH_DATA* poketch_data)
{
	enum {
		DEFAULT_APPNO = POKETCH_APPID_DWATCH,
	};

	int i;

	for(i=0; i<APP_REGIST_MAX; i++)
	{
		poketch_data->app_flag[i] = 0;
	}
	poketch_data->app_count = 0;
	poketch_data->app_index = 0;
	poketch_data->get_flag = FALSE;
	poketch_data->color_type = POKETCH_COLOR_TYPE0;

	// 万歩計
	poketch_data->pedometer_flag = FALSE;
	poketch_data->pedometer = 0;

	// アラーム時計
	poketch_data->alarm_switch = FALSE;
	poketch_data->alarm_hour = 0;
	poketch_data->alarm_minute = 0;

	// カレンダー
	poketch_data->calendar_month = 1;
	poketch_data->calendar_markbit = 0;

	// マーキングマップ
	{
		static const struct {
			u8  x;
			u8  y;
		}initialPos[POKETCH_MAP_MARK_MAX] = {
			{ 104, 152 }, { 120, 152 }, { 136, 152 },
			{ 152, 152 }, { 168, 152 }, { 184, 152 },
		};
		for(i=0; i<POKETCH_MAP_MARK_MAX; i++)
		{
			poketch_data->mark_map_pos[i].x = initialPos[i].x;
			poketch_data->mark_map_pos[i].y = initialPos[i].y;
		}
	}

	// ポケモンヒストリー
	for(i=0; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		poketch_data->poke_history[i].monsno = 0;
		poketch_data->poke_history[i].iconPattern = 0;
	}

	// ドットアート
	poketch_data->dotart_modified_flag = 0;



	PoketchData_AddApplication(poketch_data, DEFAULT_APPNO);
}
//------------------------------------------------------------------
/**
 * ポケッチを手に入れたフラグをセットする
 *
 * @param   poketch_data		ワークポインタ
 *
 */
//------------------------------------------------------------------
void PoketchData_SetPoketchGetFlag( POKETCH_DATA* poketch_data )
{
	poketch_data->get_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * ポケッチを手に入れたフラグを取得する
 *
 * @param   poketch_data		ワークポインタ
 *
 */
//------------------------------------------------------------------
BOOL PoketchData_GetPoketchGetFlag( POKETCH_DATA* poketch_data )
{
	return poketch_data->get_flag;
}
//------------------------------------------------------------------
/**
 * 登録されているアプリケーションの数を取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  int		登録されているアプリケーションの数
 */
//------------------------------------------------------------------
int PoketchData_GetApplicationCount(const POKETCH_DATA * poketch_data)
{
	return poketch_data->app_count;
}
//------------------------------------------------------------------
/**
 * あといくつアプリを登録できるか取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  int		いくつ登録できるか
 */
//------------------------------------------------------------------
int PoketchData_GetRestApplicationSpace( POKETCH_DATA* poketch_data )
{
	return POKETCH_APPID_MAX - poketch_data->app_count;
}
//------------------------------------------------------------------
/**
 * すでにアプリが登録されているかチェック
 *
 * @param   poketch_data	ワークポインタ
 * @param   app_id			アプリケーションID
 *
 * @retval  BOOL	TRUEで登録済み
 */
//------------------------------------------------------------------
BOOL PoketchData_CheckApplicationRegisterd( POKETCH_DATA* poketch_data, int app_id )
{
	return poketch_data->app_flag[app_id];
}
//------------------------------------------------------------------
/**
 * 新しいアプリケーションを追加
 *
 * @param   poketch_data		ワークポインタ
 * @param   app_id				アプリケーションID
 *
 * @retval  BOOL		TRUEで登録成功／FALSEで失敗（もういっぱい）
 */
//------------------------------------------------------------------
BOOL PoketchData_AddApplication(POKETCH_DATA * poketch_data, int app_id)
{
	GF_ASSERT( app_id >= 0 && app_id < POKETCH_APPID_MAX );

	if( poketch_data->app_count < POKETCH_APPID_MAX )
	{
		if( poketch_data->app_flag[ app_id ] == FALSE )
		{
			poketch_data->app_flag[ app_id ] = TRUE;
			poketch_data->app_count++;

			if( app_id == POKETCH_APPID_PEDOMETER )
			{
				poketch_data->pedometer_flag = TRUE;
			}

			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 現在表示中のアプリケーションIDを取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  int		アプリケーションID
 *
 * ※アプリケーションID = 時計、メモ帳等、アプリの種類を識別するID.
 */
//------------------------------------------------------------------
int PoketchData_GetNowApplication(const POKETCH_DATA* poketch_data)
{
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * 表示中アプリを１つ前へ切り替える
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  int		切り替え後のアプリケーション番号
 */
//------------------------------------------------------------------
int PoketchData_SetApplicationPosNext( POKETCH_DATA* poketch_data )
{
	int  i = poketch_data->app_index;

	while(1)
	{
		if( ++i >= POKETCH_APPID_MAX )
		{
			i = 0;
		}
		if( i == poketch_data->app_index )
		{
			break;
		}
		if( poketch_data->app_flag[i] )
		{
			break;
		}
	}
	poketch_data->app_index = i;
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * 表示中アプリを１つ後ろへ切り替える
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  int		切り替え後のアプリケーション番号
 */
//------------------------------------------------------------------
int PoketchData_SetApplicationPosPrev( POKETCH_DATA* poketch_data )
{
	int  i = poketch_data->app_index;

	while(1)
	{
		if( --i < 0 )
		{
			i = POKETCH_APPID_MAX - 1;
		}
		if( i == poketch_data->app_index )
		{
			break;
		}
		if( poketch_data->app_flag[i] )
		{
			break;
		}
	}
	poketch_data->app_index = i;
	return poketch_data->app_index;
}
//------------------------------------------------------------------
/**
 * 表示中アプリを指定登録番号の物に切り替える
 *
 * @param   poketch_data	ワークポインタ
 * @param   pos				登録番号
 *
 */
//------------------------------------------------------------------
void PoketchData_SetApplicationPos( POKETCH_DATA* poketch_data, int pos )
{
	if( pos >= 0 && pos < poketch_data->app_count )
	{
		int i;
		for(i=0; i<POKETCH_APPID_MAX; i++)
		{
			if( poketch_data->app_flag[i] )
			{
				if( pos == 0 )
				{
					poketch_data->app_index = i;
					break;
				}
				else
				{
					pos--;
				}
			}
		}
		
	}
	else
	{
		GF_ASSERT(0);
	}
}

//------------------------------------------------------------------
/**
 * カラータイプを取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  u32		カラータイプ
 */
//------------------------------------------------------------------
u32 PoketchData_GetColorType( const POKETCH_DATA* poketch_data )
{
	GF_ASSERT(poketch_data);
	return poketch_data->color_type;
}
//------------------------------------------------------------------
/**
 * カラータイプを設定
 *
 * @param   poketch_data		ワークポインタ
 */
//------------------------------------------------------------------
void PoketchData_SetColorType( POKETCH_DATA* poketch_data, u32 color_type )
{
	GF_ASSERT(poketch_data);
	GF_ASSERT(color_type < POKETCH_COLOR_TYPE_MAX);
	poketch_data->color_type = color_type;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * 『万歩計』の歩数を取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  u32		万歩計歩数
 */
//------------------------------------------------------------------
u32 PoketchData_GetPedometer( const POKETCH_DATA* poketch_data )
{
	return poketch_data->pedometer;
}
//------------------------------------------------------------------
/**
 * 『万歩計』の歩数をセット
 *
 * @param   poketch_data		ワークポインタ
 * @param   pos					セットする歩数
 */
//------------------------------------------------------------------
void PoketchData_SetPedometer( POKETCH_DATA* poketch_data, u32 count )
{
	if( poketch_data->pedometer_flag )
	{
		poketch_data->pedometer = count;
	}
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * 『アラーム時計』のスイッチオン／オフフラグを取得
 *
 * @param   poketch_data		ワークポインタ
 *
 * @retval  BOOL			
 */
//------------------------------------------------------------------
BOOL PoketchData_GetAlarmSwitchFlag( const POKETCH_DATA* poketch_data )
{
	return poketch_data->alarm_switch;
}
//------------------------------------------------------------------
/**
 * 『アラーム時計』の設定時刻を取得
 *
 * @param   poketch_data		ワークポインタ
 * @param   hour				設定時刻（時）を受け取る変数のポインタ
 * @param   min					設定時刻（分）を受け取る変数のポインタ
 *
 */
//------------------------------------------------------------------
void PoketchData_GetAlarmTime( const POKETCH_DATA* poketch_data, u32* hour, u32* min )
{
	*hour = poketch_data->alarm_hour;
	*min = poketch_data->alarm_minute;
}
//------------------------------------------------------------------
/**
 * 『アラーム時計』の設定更新
 *
 * @param   poketch_data	ワークポインタ
 * @param   switch_flag		スイッチオン／オフフラグ
 * @param   hour			設定時刻（時）
 * @param   min				設定時刻（分）
 *
 */
//------------------------------------------------------------------
void PoketchData_SetAlarm( POKETCH_DATA* poketch_data, BOOL switch_flag, u32 hour, u32 min )
{
	poketch_data->alarm_switch = switch_flag;
	poketch_data->alarm_hour = hour;
	poketch_data->alarm_minute = min;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * カレンダーの日付ビットをセット
 *
 * @param   poketch_data	ポケッチデータポインタ
 * @param   month			セットする月
 * @param   day				セットする日
 *
 */
//------------------------------------------------------------------
void PoketchData_Calendar_SetMark( POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		poketch_data->calendar_markbit |= (1 << (day-1));
	}
	else
	{
		poketch_data->calendar_month = month;
		poketch_data->calendar_markbit = (1 << (day-1));
	}
}
//------------------------------------------------------------------
/**
 * カレンダーの日付ビットをクリア
 *
 * @param   poketch_data	ポケッチデータポインタ
 * @param   month			クリアする月
 * @param   day				クリアする日
 *
 */
//------------------------------------------------------------------
void PoketchData_Calendar_ClearMark( POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		poketch_data->calendar_markbit &= ~(1 << (day-1));
	}
	else
	{
		poketch_data->calendar_month = month;
		poketch_data->calendar_markbit = 0;
	}
}
//------------------------------------------------------------------
/**
 * カレンダーの日付ビットを取得
 *
 * @param   poketch_data	ポケッチデータポインタ
 * @param   month			月
 * @param   day				日
 *
 * @retval  BOOL		TRUEならビットON
 */
//------------------------------------------------------------------
BOOL PoketchData_Calendar_GetMark( const POKETCH_DATA* poketch_data, u32 month, u32 day )
{
	if( poketch_data->calendar_month == month )
	{
		return (poketch_data->calendar_markbit >> (day-1)) & 1;
	}
	else
	{
		return FALSE;
	}
}


//==============================================================================================
//==============================================================================================

void PoketchData_MarkMap_SetMarkPos( POKETCH_DATA* poketch_data, int id, u8 x, u8 y )
{
	GF_ASSERT(id < POKETCH_MAP_MARK_MAX);

	poketch_data->mark_map_pos[id].x = x;
	poketch_data->mark_map_pos[id].y = y;
}
void PoketchData_MarkMap_GetMarkPos( const POKETCH_DATA* poketch_data, int id, u8* x, u8* y )
{
	GF_ASSERT(id < POKETCH_MAP_MARK_MAX);

	*x = poketch_data->mark_map_pos[id].x;
	*y = poketch_data->mark_map_pos[id].y;
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * アプリ『ドットアート』　一度でも内容が編集されたことがあるか？
 *
 * @param   poketch_data		ポケッチデータポインタ
 *
 * @retval  BOOL		TRUEで編集されたことあり
 */
//------------------------------------------------------------------
BOOL PoketchData_DotArt_GetModifiedFlag( const POKETCH_DATA* poketch_data )
{
	return poketch_data->dotart_modified_flag;
}
//------------------------------------------------------------------
/**
 * アプリ『ドットアート』	ビットデータ取得
 *
 * @param   poketch_data		ポケッチデータポインタ
 * @param   dst					データ取得先バッファ
 *
 */
//------------------------------------------------------------------
void PoketchData_DotArt_GetBitData( const POKETCH_DATA* poketch_data, u8* dst )
{
	if( poketch_data->dotart_modified_flag )
	{
		MI_CpuCopy8( poketch_data->dotart_data, dst, POKETCH_DOTART_DATA_BYTESIZE );
	}
}
//------------------------------------------------------------------
/**
 * アプリ『ドットアート』	編集したビットデータ保存
 *
 * @param   poketch_data		ポケッチデータポインタ
 * @param   src					ビットデータアドレス
 *
 */
//------------------------------------------------------------------
void PoketchData_DotArt_SetBitData( POKETCH_DATA* poketch_data, const u8* src )
{
	MI_CpuCopy8( src, poketch_data->dotart_data, POKETCH_DOTART_DATA_BYTESIZE );
	poketch_data->dotart_modified_flag = 1;
}



//==============================================================================================
// ポケモンヒストリー（手に入れたポケモンを記録）
//==============================================================================================


//------------------------------------------------------------------
/**
 * 『ポケモンヒストリー』記録追加
 *
 * @param   poketch_data		ポケッチデータポインタ
 * @param   ppp					ポケモンパラメータ
 *
 */
//------------------------------------------------------------------
void PoketchData_PokeHistory_Add( POKETCH_DATA* poketch_data, const POKEMON_PASO_PARAM* ppp )
{
	int max;

	max = PoketchData_PokeHistory_GetRecordCount( poketch_data );
	if( max >= POKETCH_POKE_HISTORY_COUNT_MAX )
	{
		int i;
		for(i=0; i<(POKETCH_POKE_HISTORY_COUNT_MAX-1); i++)
		{
			poketch_data->poke_history[i] = poketch_data->poke_history[i+1];
		}
		max = POKETCH_POKE_HISTORY_COUNT_MAX - 1;
	}

	poketch_data->poke_history[max].monsno = PokePasoParaGet((POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno, NULL);
	poketch_data->poke_history[max].iconPattern = PokeIconCgxPatternGet( ppp );
}

//------------------------------------------------------------------
/**
 * 『ポケモンヒストリー』記録件数を返す
 *
 * @param   poketch_data		ポケッチデータポインタ
 *
 * @retval  int		記録件数
 */
//------------------------------------------------------------------
int PoketchData_PokeHistory_GetRecordCount( const POKETCH_DATA* poketch_data )
{
	int i;
	for(i=0; i<POKETCH_POKE_HISTORY_COUNT_MAX; i++)
	{
		if( poketch_data->poke_history[i].monsno == 0 )
		{
			return i;
		}
	}
	return i;
}

//------------------------------------------------------------------
/**
 * 『ポケモンヒストリー』記録されたデータを取得
 *
 * @param   poketch_data	ポケッチデータポインタ
 * @param   index			旧い順 0origin インデックス
 * @param   monsno			[out]モンスターナンバーを受け取る
 * @param   iconPattern		[out]アイコンパターンナンバーを受け取る
 *
 */
//------------------------------------------------------------------
void PoketchData_PokeHistory_GetRecord( const POKETCH_DATA* poketch_data, int index, int* monsno, int* iconPattern )
{
	GF_ASSERT(index<POKETCH_POKE_HISTORY_COUNT_MAX);
	GF_ASSERT(poketch_data->poke_history[index].monsno);

	*monsno = poketch_data->poke_history[index].monsno;
	*iconPattern = poketch_data->poke_history[index].iconPattern;
}



//============================================================================================
//	セーブデータ取得のための関数
//============================================================================================
POKETCH_DATA * SaveData_GetPoketchData(SAVEDATA * sv)
{
	POKETCH_DATA * pk;
	pk = SaveData_Get(sv, GMDATA_ID_POKETCH_DATA);
	return pk;
}



//============================================================================================
//	デバッグ用
//============================================================================================
#ifdef PM_DEBUG
void PoketchData_AddAllApplication( POKETCH_DATA* poketch_data )
{
	#if 1
	int i;
	for(i=0; i<POKETCH_APPID_MAX; i++)
	{
		if(i == POKETCH_DEFAULT_APPNO)
		{
			continue;
		}
		PoketchData_AddApplication(poketch_data, i);
	}
	#else
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_POKELIST);
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_KITCHEN_TIMER);
	PoketchData_AddApplication(poketch_data, POKETCH_APPID_PEDOMETER );
	#endif
}
#endif
