//============================================================================================
/**
 * @file	syswork.c
 * @bfief	プログラム、スクリプトからアクセスされるシステムワーク操作
 * @author	Satoshi Nohara
 * @date	06.03.12
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "script.h"
#include "field/evwkdef.h"
#include "syswork.h"
#include "sysflag.h"				//SysFlag_
#include "poketool/monsno.h"		//ポケモンナンバー

#include "savedata/randomgroup.h"

//============================================================================================
//
//	プロトタイプ宣言
//
//============================================================================================
static BOOL SysWork_Set( EVENTWORK* ev, u16 work, u16 no );
static u16 SysWork_Get( EVENTWORK* ev, u16 work );
BOOL SysWork_FirstPokeNoSet( EVENTWORK* ev, u16 no );
u16 SysWork_FirstPokeNoGet( EVENTWORK* ev );
u16 SysWork_RivalPokeNoGet( EVENTWORK* ev );
u16 SysWork_SupportPokeNoGet( EVENTWORK* ev );


//============================================================================================
//
//	関数
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * システムワークセット
 *
 * @param	ev			EVENTWORKへのポインタ
 * @param	work		ワークナンバー
 * @param	no			セットする値
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
static BOOL SysWork_Set( EVENTWORK* ev, u16 work, u16 no )
{
	u16* p	= EventWork_GetEventWorkAdrs( ev, work );

	if( (work < SVWK_START) || (work > SCWK_START ) ){
		GF_ASSERT( (0) && "不正なワークIDが渡されました！" );
		return FALSE;
	}

	if( p == NULL ){
		return FALSE;
	}

	*p = no;
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * システムワークゲット
 *
 * @param	ev			EVENTWORKのポインタ
 * @param	work		ワークナンバー
 *
 * @return	"ワークの値"
 */
//--------------------------------------------------------------------------------------------
static u16 SysWork_Get( EVENTWORK* ev, u16 work )
{
	u16* p	= EventWork_GetEventWorkAdrs( ev, work );

	if( p == NULL ){
		return 0;
	}

	return *p;
}


//============================================================================================
//
//	連れ歩きトレーナーID格納ワーク関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 連れ歩きトレーナーID格納ワークセット
 *
 * @param	ev			EVENTWORKへのポインタ
 * @param	no			トレーナーID
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_PairTrainerIDSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_PAIR_TRAINER_ID, no );
}

//--------------------------------------------------------------------------------------------
/**
 * 連れ歩きトレーナーID格納ワークゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"トレーナーID"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_PairTrainerIDGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_PAIR_TRAINER_ID );
}


//============================================================================================
//
//	最初のポケモンナンバー関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモンナンバーセット
 *
 * @param	ev			EVENTWORKへのポインタ
 * @param	no			ポケモンナンバー
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_FirstPokeNoSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_FIRST_POKE_NO, no );
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモンナンバーゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"最初のポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_FirstPokeNoGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );
}

//--------------------------------------------------------------------------------------------
/**
 * ライバルのポケモンナンバーゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"ライバルのポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RivalPokeNoGet( EVENTWORK* ev )
{
	u16 rival;
	u16 first = SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );

#if 1
	if( first == MONSNO_NAETORU ){
		rival = MONSNO_HIKOZARU;
	}else if( first == MONSNO_HIKOZARU ){
		rival = MONSNO_POTTYAMA;
	}else{
		rival = MONSNO_NAETORU;
	}
#endif

	return rival;
}

//--------------------------------------------------------------------------------------------
/**
 * サポートのポケモンナンバーゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"サポートのポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_SupportPokeNoGet( EVENTWORK* ev )
{
	u16 support;
	u16 first = SysWork_Get( ev, SYS_WORK_FIRST_POKE_NO );

#if 1
	if( first == MONSNO_NAETORU ){
		support = MONSNO_POTTYAMA;
	}else if( first == MONSNO_HIKOZARU ){
		support = MONSNO_NAETORU;
	}else{
		support = MONSNO_HIKOZARU;
	}
#endif

	return support;
}


//============================================================================================
//
//	おおきさくらべ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 現在の記録を取得
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"個体値"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_OokisaRecordGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_OOKISA_RECORD );
}

//--------------------------------------------------------------------------------------------
/**
 * 記録を書き換える
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no			個体値
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_OokisaRecordSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_OOKISA_RECORD, no );
}


//============================================================================================
//
//	バトルサーチャー関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * マップ遷移した時のリセット処理
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Sys_BtlSearcherReset( EVENTWORK* ev )
{
	SysFlag_BtlSearcherUseReset( ev );		//使用中を解除
	SysWork_BtlSearcherClearSet( ev, 0 );	//クリアカウント初期化
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * バッテリーカウントを取得
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_BtlSearcherBatteryGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_BTL_SEARCHER_BATTERY );
}

//--------------------------------------------------------------------------------------------
/**
 * バッテリーカウントをセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_BtlSearcherBatterySet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_BTL_SEARCHER_BATTERY, no );
}

//--------------------------------------------------------------------------------------------
/**
 * クリアカウントを取得
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_BtlSearcherClearGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_BTL_SEARCHER_CLEAR );
}

//--------------------------------------------------------------------------------------------
/**
 * クリアカウントをセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_BtlSearcherClearSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_BTL_SEARCHER_CLEAR, no );
}




//============================================================================================
//
//
//			配布イベント関連
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	それぞれの配布イベントに対応したマジックナンバーを返す
 */
//--------------------------------------------------------------------------------------------
static get_haihu_magicnumber(int ex_event_id)
{
	static const u16 magic_number[] = {
		0x1209,
		0x1112,
		0x1123,
	};
	GF_ASSERT(0 <= ex_event_id && ex_event_id < NELEMS(magic_number));
	return magic_number[ex_event_id];
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HaihuEventWorkSet(EVENTWORK * ev, int haihu_id)
{
	SysWork_Set(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id, get_haihu_magicnumber(haihu_id));
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HaihuEventWorkClear(EVENTWORK * ev, int haihu_id)
{
	SysWork_Set(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id, 0);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysWork_HaihuEventWorkCheck(EVENTWORK * ev, int haihu_id)
{
	if (SysWork_Get(ev, SYS_WORK_HAIHU_EVENT01 + haihu_id) == get_haihu_magicnumber(haihu_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//============================================================================================
//
//
//			隠しマップ関連
//
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	それぞれに対応したマジックナンバーを返す
 */
//--------------------------------------------------------------------------------------------
static get_hidemap_magicnumber(int hidemap_id)
{
	static const u16 magic_number[] = {
		0x0208,
		0x0229,
		0x0312,
		0x1028,
	};
	GF_ASSERT(0 <= hidemap_id && hidemap_id < 4);
	return magic_number[hidemap_id];

}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HideMapWorkSet(EVENTWORK * ev, int hidemap_id)
{
	SysWork_Set(ev, SYS_WORK_HIDEMAP_01 + hidemap_id, get_hidemap_magicnumber(hidemap_id));
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_HideMapWorkClear(EVENTWORK * ev, int hidemap_id)
{
	SysWork_Set(ev, SYS_WORK_HIDEMAP_01 + hidemap_id, 0);
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL SysWork_HideMapWorkCheck(EVENTWORK * ev, int hidemap_id)
{
	if(SysWork_Get(ev, SYS_WORK_HIDEMAP_01 + hidemap_id) == get_hidemap_magicnumber(hidemap_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}


//--------------------------------------------------------------------------------------------
/**
 * 自然公園の総歩数クリア
 *
 * @param	ev			EVENTWORKへのポインタ
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_ParkWalkCountClear( EVENTWORK* ev)
{
	return SysWork_Set( ev, SYS_WORK_PARK_WALK_COUNT, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * 自然公園の総歩数ゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"最初のポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_ParkWalkCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_PARK_WALK_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 * 自然公園の総歩数を＋１
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"最初のポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_ParkWalkCountPlus( EVENTWORK* ev )
{
	u16 count;
	count = SysWork_Get( ev, SYS_WORK_PARK_WALK_COUNT );
	if(count < 10000) {		//※他での使用を考慮して多めに（自然公園のみなら２００でOK）
		count++;
	}else{
		count = 10000;
	}
	return SysWork_Set( ev, SYS_WORK_PARK_WALK_COUNT, count );
}

//--------------------------------------------------------------------------------------------
/**
 * 新聞社締め切りカウンタを取得
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_NewsDaysCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_NEWS_DAYS_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 * 新聞社締め切りカウンタをセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_NewsDaysCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_NEWS_DAYS_COUNT, no );
}

//--------------------------------------------------------------------------------------------
//			ポケモンクジ関連
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
/**
 * ポケモンクジ乱数に値をセット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWork_pokelot_value_set( EVENTWORK* ev ,u32 val)
{
	u16 L, H;

	H = (val >> 16) & 0xffff;
	L = val & 0xffff;
	SysWork_Set( ev, SYS_WORK_POKELOT_RND1, L );
	SysWork_Set( ev, SYS_WORK_POKELOT_RND1, H );

}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンクジ乱数の値をゲット
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
u32 SysWork_pokelot_value_get(EVENTWORK* ev)
{
	u16 L, H;
	L = SysWork_Get( ev, SYS_WORK_POKELOT_RND1 );
	H = SysWork_Get( ev, SYS_WORK_POKELOT_RND2 );
	return ((H<<16)|L);
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンクジ乱数の値を初期化
 *  ゲーム開始時の初期化処理
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkInitPokeLot(EVENTWORK* ev)
{
	u16  L, H;

	L = gf_rand();
	H = gf_rand();
	OS_Printf("PokeLot L[%d] H[%d]\n",L,H);
	SysWork_pokelot_value_set(ev,(H<<16) | L);
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンクジ乱数の値を初期化
 * 日数経過による更新処理
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkUpdatePokeLot(SAVEDATA *sv,u16 days)
{
	EVENTWORK * ev = SaveData_GetEventWork(sv);
	u32  value;

	value = RandomGroup_GetDefaultRandom(SaveData_GetRandomGroup(sv));

	value = value * 1103515245L + 12345;

	SysWork_pokelot_value_set(ev,value);
}


//--------------------------------------------------------------------------------------------
/**
 * １日１回、ポケモンのレベルと同じ数のとき、アイテムをくれるおじさん
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_PokeLevelNoGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_POKE_LEVEL_NO );
}

//--------------------------------------------------------------------------------------------
/**
 * １日１回、ポケモンのレベルと同じ数のとき、アイテムをくれるおじさん
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_PokeLevelNoSet( EVENTWORK* ev ,u16 no)
{
	return SysWork_Set( ev, SYS_WORK_POKE_LEVEL_NO, no );
}

//--------------------------------------------------------------------------------------------
/**
 * １日１回、ポケモンのレベルと同じ数のとき、アイテムをくれるおじさん
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SysWorkUpdatePokeLevelNo(SAVEDATA *sv)
{
	EVENTWORK * ev = SaveData_GetEventWork(sv);
	u32  value;

	value = (gf_rand() % 98) + 2;		//2-99
	SysWork_PokeLevelNoSet(ev,value);
}

//--------------------------------------------------------------------------------------------
/**
 * 地下会話カウントを取得(ミカゲ専用)
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTalkCountGet( EVENTWORK* ev )
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_UG_TALK_COUNT );
	OS_Printf("SYS_WORK_UG_TALK_COUNT [%d]\n",count);
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * 地下会話カウントをセット(ミカゲ専用)
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTalkCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TALK_COUNT , no );
}



//--------------------------------------------------------------------------------------------
/**
 * 地下会話カウントを取得
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTalkCount2Get( EVENTWORK* ev )
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_UG_TALK_COUNT2 );
	OS_Printf("SYS_WORK_UG_TALK_COUNT2 [%d]\n",count);
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * 地下会話カウントをセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTalkCount2Set( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TALK_COUNT2 , no );
}

//--------------------------------------------------------------------------------------------
/**
 * レンチャン数をゲット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	カウント
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RensyouCountGet( EVENTWORK* ev)
{
	u16		count;
	count = SysWork_Get( ev, SYS_WORK_RENSYOU_COUNT );
	return count;
}

//--------------------------------------------------------------------------------------------
/**
 * レンチャン数をセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_RensyouCountSet( EVENTWORK* ev, u16 no )
{
	OS_Printf("SYS_WORK_RENSYOU_COUNT <- [%d]\n",no);
	return SysWork_Set( ev, SYS_WORK_RENSYOU_COUNT , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	デパート購入回数
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"最初のポケモンナンバー"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_RegularCountPlus( EVENTWORK* ev )
{
	u16 count;
	count = SysWork_Get( ev, SYS_WORK_DEPART_COUNT );
	if(count < 10000) {		//※ループしないようにリミットつき
		count++;
	}else{
		count = 10000;
	}
	return SysWork_Set( ev, SYS_WORK_DEPART_COUNT, count );
}

//--------------------------------------------------------------------------------------------
/**
 *	デパート購入回数
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_RegularCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_DEPART_COUNT );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下で道具をあげた人数の累計
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGToolGiveCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_TOOL_GIVE_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下で道具をあげた人数をセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGToolGiveCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TOOL_GIVE_COUNT	 , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でかせきを掘った回数の累計
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGKasekiDigCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_KASEKI_DIG_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でかせきを掘った回数をセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGKasekiDigCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_KASEKI_DIG_COUNT , no );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でトラップにかけた回数の累計
 *
 * @param	ev		EVENTWORKのポインタ
 *
 * @return	"カウント"
 */
//--------------------------------------------------------------------------------------------
u16 SysWork_UGTrapHitCountGet( EVENTWORK* ev )
{
	return SysWork_Get( ev, SYS_WORK_UG_TRAP_HIT_COUNT	 );
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でトラップにかけた回数をセット
 *
 * @param	ev		EVENTWORKへのポインタ
 * @param	no		セットカウント
 *
 * @return	"TRUE=セット出来た、FALSE=セット出来なかった"
 */
//--------------------------------------------------------------------------------------------
BOOL SysWork_UGTrapHitCountSet( EVENTWORK* ev, u16 no )
{
	return SysWork_Set( ev, SYS_WORK_UG_TRAP_HIT_COUNT , no );
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
u16 SysWork_FriendlyStepCountGet(EVENTWORK * ev)
{
	return SysWork_Get(ev, SYS_WORK_FRIENDLY_COUNT);
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void SysWork_FriendlyStepCountSet(EVENTWORK * ev, u16 step)
{
	SysWork_Set(ev, SYS_WORK_FRIENDLY_COUNT, step);
}

