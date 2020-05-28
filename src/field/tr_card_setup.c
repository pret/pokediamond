//============================================================================================
/**
 * @file	tr_card_setup.c
 * @bfief	トレーナーカード情報セットアップ
 * @author	Nozomu Saito
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "field/field.h"
#include "system/mystatus.h"
#include "system/zukanwork.h"
#include "application/trainer_card.h"
#include "savedata/trainercard_data.h"
#include "savedata/record.h"
#include "savedata/playtime.h"
#include "ev_time.h"
#include "comm_union.h"
#include "field/eventflag.h"
#include "contest/contest_def.h"
#include "sysflag.h"
#include "savedata/undergrounddata.h"

#include "tr_card_setup.h"

#define COMM_NUM_MAX	(999999)
#define BATTLE_WIN_MAX	(9999)
#define BATTLE_LOSE_MAX	(9999)
#define TRADE_MAX		(99999)

static void TRCSET_SetTrCardDataCommon(	const u8 inBadgeBrushFlg,
										const u8 inVersion,
										const u8 inCardRank,
										const u8 inGymReaderMask,
										const u8 inCountryCode,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataFace(	const u16 inID,
										const u8  inSex,
										const STRCODE *inName,
										const u32 inMoney,
										const u32 inPokeBook,
										const BOOL inPokeBookFlg,
										const u32 inScore,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataTime(	const u8 inClearFlg,
										const PLAYTIME *inPlayTime,
										const RTCDate *inStartDate,
										const RTCDate *inClearDate,
										const RTCTime *inClearTime,
										const u8 TimeUpdate,
										TR_CARD_DATA *outTrCardData);

static void TRCSET_SetTrCardDataBack(	const u32 inCommNum,
										const u32 inCommBattleWin,
										const u32 inCommBattleLose,
										const u32 inCommTrade,
										const u8 *inSignData,
										TR_CARD_DATA *outTrCardData);
static void TRCSET_SetTrCardDataBadge(	MYSTATUS *inMySt, FIELDSYS_WORK *fsys, TR_CARD_DATA *outTrCardData );

static BOOL SetupTrCardEvent(GMEVENT_CONTROL * event);

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報を収集して、データを作成
 *
 * @param	inBadgeBrushFlg		バッジ磨き有効有無
 * @param	inTimeUpdate		時間更新フラグ
 * @;aram	inGymRaederMask		ジムリーダーマスク
 * @param	inUnionTrNo			ユニオントレーナーナンバー（0～15）　指定しないときは,UNION_TR_NONE
 * @param	fsys				フィールドシステムポインタ
 * @param	outTrCardData		トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_MakeTrainerInfo(const u8 inBadgeBrushFlg,
							const u8 inTimeUpdate,
							const u8 inGymReaderMask,
							const u8 inUnionTrNo,
							FIELDSYS_WORK *fsys, 
							TR_CARD_DATA *outTrCardData)
{
	MYSTATUS *my_st;
	RECORD *rec;
	SAVEDATA * sv;
	sv = GameSystem_GetSaveData(fsys);
	my_st = SaveData_GetMyStatus(sv);
	rec = SaveData_GetRecord(sv);

	outTrCardData->UnionTrNo = inUnionTrNo;

	{
		u8 rank;
		//ランク算出
		rank = TRCSET_GetCardRank(fsys);
	
		TRCSET_SetTrCardDataCommon( inBadgeBrushFlg, PM_VERSION, rank,
									inGymReaderMask, MyStatus_GetRegionCode(my_st), outTrCardData);
	}
	
	TRCSET_SetTrCardDataFace(	MyStatus_GetID_Low(my_st),
								MyStatus_GetMySex(my_st),
								MyStatus_GetMyName(my_st),
								MyStatus_GetGold(my_st),
								ZukanWork_GetZukanPokeSeeCount( SaveData_GetZukanWork(fsys->savedata) ),
								ZukanWork_GetZukanGetFlag(SaveData_GetZukanWork(fsys->savedata)),
								RECORD_Score_Get(rec),
								outTrCardData);

	{
		RTCDate start_date;	//開始年月日
		RTCDate clear_date;	//クリア年月日
		RTCTime time;		//クリア時間

		PLAYTIME *play_time;

		play_time = SaveData_GetPlayTime(sv);
		
		EVTIME_GetGameStartDateTime(fsys, &start_date, &time);
		EVTIME_GetGameClearDateTime(fsys, &clear_date, &time);

		TRCSET_SetTrCardDataTime(	SysFlag_GameClearCheck( SaveData_GetEventWork( fsys->savedata ) ),
									play_time,
									&start_date,
									&clear_date,
									&time,
									inTimeUpdate,
									outTrCardData);
	}

	{
		u32 count,win,lose,trade;
		TR_CARD_SV_PTR trc_ptr;
		trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
		
		//通信回数	ワイヤレスコンテスト+ワイヤレス交換+WiFi交換+ワイヤレス対戦+WiFi対戦+ワイヤレスポルト
		count = RECORD_Get(rec, RECID_CONTEST_COMM_ENTRY)+
				RECORD_Get(rec, RECID_COMM_TRADE)+RECORD_Get(rec, RECID_WIFI_TRADE)+
				RECORD_Get(rec, RECID_COMM_BATTLE)+RECORD_Get(rec, RECID_WIFI_BATTLE)+
				RECORD_Get(rec, RECID_PORUTO_COMM);
		//勝ち数	ワイヤレス+WiFi
		win = RECORD_Get(rec, RECID_COMM_BTL_WIN)+RECORD_Get(rec, RECID_WIFI_BTL_WIN);
		//負け数	ワイヤレス+WiFi
		lose = RECORD_Get(rec, RECID_COMM_BTL_LOSE)+RECORD_Get(rec, RECID_WIFI_BTL_LOSE);
		//通信交換	ワイヤレス+WiFi
		trade = RECORD_Get(rec, RECID_COMM_TRADE)+RECORD_Get(rec, RECID_WIFI_TRADE);

		TRCSET_SetTrCardDataBack(	count,
									win,
									lose,
									trade,
									TRCSave_GetSighnDataPtr(trc_ptr),
									outTrCardData);
	}

	TRCSET_SetTrCardDataBadge( my_st, fsys, outTrCardData );

	{
		int i,tmp=0;
		u8 *p = (u8*)outTrCardData;
		for(i=0;i<sizeof(TR_CARD_DATA);i++){
			tmp ^= p[i];
		}
		outTrCardData->_xor = tmp;
	}

	
	
	outTrCardData->reached  = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカードメモリアロケーション
 *
 * @param	inHeapID		ヒープID
 *
 * @return	TR_CARD_DATA*	トレーナーカードデータポインタ
 */
//--------------------------------------------------------------------------------------------
TR_CARD_DATA *TRCSET_AllocTrainerCardData( const u16 inHeapID )
{
	TR_CARD_DATA * tcd = sys_AllocMemory( inHeapID, sizeof(TR_CARD_DATA) );
	memset( tcd, 0, sizeof(TR_CARD_DATA) );

	return tcd; 
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカードメモリ解放
 *
 * @param	*outData	解放するメモリ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_FreeTrainerCardData( TR_CARD_DATA *outData )
{
	sys_FreeMemoryEz(outData);
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカードランク取得
 *
 * @param
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
u8 TRCSET_GetCardRank(FIELDSYS_WORK *fsys)
{
	u8 rank;
	SAVEDATA * sv;
	RECORD *rec;
	EVENTWORK *ev;
	SB_RECORD_DATA* sbd;
	
	sv = GameSystem_GetSaveData(fsys);
	rec = SaveData_GetRecord(sv);
	ev = SaveData_GetEventWork(sv);
	sbd = SaveData_GetSecretBaseRecord(sv);
	rank = TR_CARD_RANK_NORMAL;
	
	//殿堂入り（クリアフラグ）
	if ( SysFlag_GameClearCheck( ev ) ){
		rank++;
	}
	//全国図鑑完成（イベント系ポケモンを除くポケモンをゲットしているか）
	if ( ZukanWork_CheckZenkokuComp(SaveData_GetZukanWork(sv)) ){
		rank++;
	}
	//バトルタワー100連勝（タイプはなんでも）
	if ( (RECORD_Get(rec,RECID_RENSHOU_SINGLE )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_DOUBLE )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_MULTI )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_COMM_MULTI )>=100)||
		 (RECORD_Get(rec,RECID_RENSHOU_WIFI )>=100) ){ 
		rank++;
	}
	//コンテストマスター優勝（タイプはなんでも）
	if ( SysFlag_ConMasterCheck( ev, CONTYPE_STYLE )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_BEAUTIFUL )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_CLEVER )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_STRONG )||
		 SysFlag_ConMasterCheck( ev, CONTYPE_CUTE ) ){
		rank++;
	}
	//地下マスター
	
	if ( SecretBaseRecordGetUGRank(sbd) == UG_RANK_MASTER ){
		rank++;
	}
	return rank;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報セット
 *
 * @param	inBadgeBrushFlg		バッジ磨き有効有無
 * @param	inVersion			バージョン
 * @param	inCardRank			カードランク
 * @param	inGymReaderMask		ジムリーダーマスク
 * @param	inCoutryCode		国コード
 * @param	outTrCardData		トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataCommon(	const u8 inBadgeBrushFlg,
										const u8 inVersion,
										const u8 inCardRank,
										const u8 inGymReaderMask,
										const u8 inCountryCode,
										TR_CARD_DATA *outTrCardData)
{
	//バッジ磨きアプリ有効フラグ
	outTrCardData->BrushValid = inBadgeBrushFlg;
	//ソフトバージョン
	outTrCardData->Version = inVersion;
	//カードランク;
	outTrCardData->CardRank = inCardRank;
	//国コード
	outTrCardData->CountryCode = inCountryCode;
	//ジムリーダーマスク
	outTrCardData->GymReaderMask = inGymReaderMask;

	//擬似別バージョン処理
#ifdef PM_DEBUG
	if (sys.cont && PAD_BUTTON_L){
		outTrCardData->Version = VERSION_DP_NEXT;
		outTrCardData->GymReaderMask = 0x5a;
	}
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報セット(表面)
 *
 * @param	inID			トレーナーID
 * @param	inSex			性別
 * @param	inName			なまえ
 * @param	inMoney			おこづかい
 * @param	inPokeBook		図鑑モンスター数
 * @param	inPokeBookFlg	図鑑所持フラグ
 * @param	inScore			スコア
 * @param	outTrCardData	トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataFace(	const u16 inID,
										const u8  inSex,
										const STRCODE *inName,
										const u32 inMoney,
										const u32 inPokeBook,
										const BOOL inPokeBookFlg,
										const u32 inScore,
										TR_CARD_DATA *outTrCardData)
{
	//トレーナーID
	outTrCardData->TrainerID = inID;
	//性別
	outTrCardData->TrSex = inSex;
	//トレーナー名
	PM_strncpy( outTrCardData->TrainerName, inName, PERSON_NAME_SIZE+EOM_SIZE );
//	outTrCardData->TrainerName = inName;
	//おこづかい
	outTrCardData->Money = inMoney;
	//ずかん
	outTrCardData->PokeBook = inPokeBook;
	//ずかん持ってるか
	outTrCardData->PokeBookFlg = inPokeBookFlg;
	//スコア
	outTrCardData->Score = inScore;

}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報セット(時間)
 * 
 * @param	inClearFlg		クリアフラグ
 * @param	inPlayTime		プレイ時間
 * @param	inStartDate		開始年月日
 * @param	inClearDate		クリア年月日
 * @param	inClearTime		クリア時間
 * @param	outTrCardData	トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataTime(	const u8 inClearFlg,
										const PLAYTIME *inPlayTime, 
										const RTCDate *inStartDate,
										const RTCDate *inClearDate,
										const RTCTime *inClearTime,
										const u8 inTimeUpdate,
										TR_CARD_DATA *outTrCardData)
{
	//プレイ時間
	outTrCardData->PlayTime_h = PLAYTIME_GetHour(inPlayTime);
	outTrCardData->PlayTime_m = PLAYTIME_GetMinute(inPlayTime);
	//開始年月日
	outTrCardData->Start_y = inStartDate->year;
	outTrCardData->Start_m = inStartDate->month;
	outTrCardData->Start_d = inStartDate->day;
	if (inClearFlg){
		//クリア年月日
		outTrCardData->Clear_y = inClearDate->year;
		outTrCardData->Clear_m = inClearDate->month;
		outTrCardData->Clear_d = inClearDate->day;
		//クリア時間
		outTrCardData->ClearTime_h = inClearTime->hour;
		outTrCardData->ClearTime_m = inClearTime->minute;
	}else{
		//クリア年月日
		outTrCardData->Clear_y = 0;
		outTrCardData->Clear_m = 0;
		outTrCardData->Clear_d = 0;
		//クリア時間
		outTrCardData->ClearTime_h = 0;
		outTrCardData->ClearTime_m = 0;
	}
	
	//時間更新フラグ
	outTrCardData->TimeUpdate = inTimeUpdate;
	//時間更新フラグがたっているならば、プレイ時間構造体のポインタをセット
	if (inTimeUpdate){
		outTrCardData->PlayTime = inPlayTime;
	}else{
		outTrCardData->PlayTime = NULL;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報セット(裏面)
 *
 * @param	inCommNum			通信回数
 * @param	inCommBattleWin		通信対戦勝ち数
 * @param	inCommBattleLose	通信対戦負け数
 * @param	inCommTrade			交換回数
 * @param	outTrCardData		トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataBack(	const u32 inCommNum,
										const u32 inCommBattleWin,
										const u32 inCommBattleLose,
										const u32 inCommTrade,
										const u8 *inSignData,
										TR_CARD_DATA *outTrCardData)
{
	//通信回数
	outTrCardData->CommNum = inCommNum;
	if (outTrCardData->CommNum > COMM_NUM_MAX){
		outTrCardData->CommNum = COMM_NUM_MAX;
	}
	
	//通信戦闘回数
	outTrCardData->CommBattleWin = inCommBattleWin;
	outTrCardData->CommBattleLose = inCommBattleLose;
	if (outTrCardData->CommBattleWin > BATTLE_WIN_MAX){
		outTrCardData->CommBattleWin = BATTLE_WIN_MAX;
	}
	if (outTrCardData->CommBattleLose > BATTLE_LOSE_MAX){
		outTrCardData->CommBattleLose = BATTLE_LOSE_MAX;
	}
	//通信交換
	outTrCardData->CommTrade = inCommTrade;
	if (outTrCardData->CommTrade > TRADE_MAX){
		outTrCardData->CommTrade = TRADE_MAX;
	}
	//サインデータをセーブデータからコピー
	MI_CpuCopy8( inSignData, outTrCardData->SignRawData, SIGN_SIZE_X*SIGN_SIZE_Y*8 );
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード情報セット(表面)
 *
 * @param	inMySt			マイステータス
 * @param	fsys			フィールドシステムポインタ
 * @param	outTrCardData	トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TRCSET_SetTrCardDataBadge(	MYSTATUS *inMySt, FIELDSYS_WORK *fsys, TR_CARD_DATA *outTrCardData )
{
	u8 i;
	TR_CARD_SV_PTR trc_ptr;
	TR_BADGE_DATA_PTR badge_ptr;
	trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
	badge_ptr = TRCSave_GetBadgeDataPtr(trc_ptr);
	
	for(i=0;i<8;i++){
		//バッジ所持フラグ
		if (MyStatus_GetBadgeFlag(inMySt, i)){
			outTrCardData->BadgeData[i].BadgeHold = 1;
		}else{
			outTrCardData->BadgeData[i].BadgeHold = 0;
		}
		
		//磨き具合
		outTrCardData->BadgeData[i].BadgeScruchCount = TRCSave_GetBadgeScruchCount(i, badge_ptr);
	}
}

//--------------------------------------------------------------------------------------------
/**
 * バッジ磨き回数更新
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inTrCardData	トレーナーカードデータポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TRCSET_UpdateBadgeScruchCount(FIELDSYS_WORK *fsys, const TR_CARD_DATA *inTrCardData)
{
	u8 i;
	TR_CARD_SV_PTR trc_ptr;
	TR_BADGE_DATA_PTR badge_ptr;
	trc_ptr = TRCSave_GetSaveDataPtr(fsys->savedata);
	badge_ptr = TRCSave_GetBadgeDataPtr(trc_ptr);

	for(i=0;i<8;i++){
		TRCSave_SetBadgeScruchCount(i, inTrCardData->BadgeData[i].BadgeScruchCount, badge_ptr);
	}
}

//==============================================================================
// トレーナーカードワークイベントで使用する構造体
//==============================================================================
typedef struct{
	int	seq;
	TR_CARD_DATA *partner;
	
}COMM_TRAINER_EVENT_WORK;

//==============================================================================
/**
 * 通信用トレーナーカード作成
 * 
 * @param	fsys		フィールドシステムポインタ
 *
 * @retval  none
 */
//==============================================================================
void TRCSET_SetupTrCardEvent(FIELDSYS_WORK * fsys)
{
	// イベントワーク作成
	COMM_TRAINER_EVENT_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(COMM_TRAINER_EVENT_WORK));
	wk->seq = 0;

	// トレーナーカードワーク作成＋相手のトレーナーカードポインタを取得
	wk->partner = (TR_CARD_DATA*)Union_TrainerCardWorkInit(fsys->union_work);
	
	FieldEvent_Call(fsys->event, SetupTrCardEvent, wk);
}

//==============================================================================
/**
 * 通信用トレーナーカード作成イベント
 * 
 * @param	@param	event	イベントポインタ
 *
 * @retval  BOOL	TRUE:イベント終了　FALSE：イベント継続
 */
//==============================================================================
static BOOL SetupTrCardEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	COMM_TRAINER_EVENT_WORK *wk  = FieldEvent_GetSpecialWork(event);

	switch(wk->seq){
	case 0:
		//トレーナーカードデータ送信
		Union_SendTrainerCardData(fsys->union_work);
		OS_Printf("カード領域確保\n");
		wk->seq = 1;
	case 1:
		// 相手のカードデータを受信した
		if(wk->partner->reached!=0){
			OS_Printf("カードデータ受信\n");
			wk->seq = 10;
		}
		break;
		

	case 10:
		// 相手のトレーナーカード閲覧開始
		FieldTrCard_SetProc( fsys, wk->partner );	
		OS_Printf("カード表示開始\n");
		wk->seq = 11;
		break;
	case 11:
		// サブプロセス終了待ち
		if( !FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {

			// トレーナーカードワークを解放
			Union_trainerCardWorkFree(fsys->union_work);

			// イベントワーク解放
			sys_FreeMemoryEz(wk);
			return TRUE;
		}
		break;
	}

	return FALSE;
}


