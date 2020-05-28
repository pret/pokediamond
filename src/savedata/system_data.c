//============================================================================================
/**
 * @file	system_data.c
 * @brief	未分類セーブデータのアクセス
 * @author	tamada	GAME FREAK Inc.
 * @date	2006.01.26
 *
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/system_data.h"

#include "gflib/assert.h"

//#include "common.h"
//#include "gflib/system.h"

//#include "system/gamedata.h"

//#include "savedata/savedata.h"

#include "savedata/gametime.h"




//============================================================================================
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	SYSTEMDATA構造体の定義
 *
 */
//---------------------------------------------------------------------------
struct SYSTEMDATA {
	s64 RTCOffset;			///<DS本体のRTCオフセット情報（RTCを操作した値）
	u8 MacAddress[6];		///<DS本体のMACアドレス
	u8 birth_month;			///<DS本体にプレイヤーが入力した誕生月
	u8 birth_day;			///<DS本体にプレイヤーが入力した誕生日
	GMTIME gametime;		///<ゲーム内時間データへのポインタ
	u8 WiFiMPOpenFlag;		///<Wi-Fi不思議な贈り物オープンフラグ
	u8 BeaconMPOpenFlag;	///<ビーコン不思議な贈り物オープンフラグ
	s32 profileId;			///< GTS・Wifiバトルタワーログイン用GameSpyID（初めて取得したGameSpyIdを保存する）
	u32 reserve[3];			///<予約領域
};

//============================================================================================
//
//		主にセーブシステムから呼ばれる関数
//
//============================================================================================

//---------------------------------------------------------------------------
/**
 * @brief	SYSTEMDATA構造体のサイズ取得
 * @return	int		SYSTEMDATA構造体のサイズ
 */
//---------------------------------------------------------------------------
int SYSTEMDATA_GetWorkSize(void)
{
	return sizeof(SYSTEMDATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	セーブデータ初期化
 * @param	sys		システムセーブデータへのポインタ
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_Init(SYSTEMDATA * sys)
{
	MI_CpuClearFast(sys, sizeof(SYSTEMDATA));
	GMTIME_Init(&sys->gametime);	//念のため
}


//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	システムデータへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	SYSTEMDATA	システムデータワークへのポインタ
 */
//---------------------------------------------------------------------------
SYSTEMDATA * SaveData_GetSystemData(SAVEDATA * sv)
{
	return SaveData_Get(sv, GMDATA_ID_SYSTEM_DATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	ゲーム内時間ワークへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	GMTIME		ゲーム内時間用ワークへのポインタ　
 */
//---------------------------------------------------------------------------
GMTIME * SaveData_GetGameTime(SAVEDATA * sv)
{
	SYSTEMDATA * system;

	system = SaveData_GetSystemData(sv);
	return &system->gametime;
}

//============================================================================================
//
//			システム情報操作・参照関数
//
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	現在のDS情報からシステムデータを更新する
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_Update(SYSTEMDATA * sysdt)
{
	OSOwnerInfo info;
	sysdt->RTCOffset = OS_GetOwnerRtcOffset();
	OS_GetMacAddress(sysdt->MacAddress);
	OS_GetOwnerInfo(&info);
	sysdt->birth_month = info.birthday.month;
	sysdt->birth_day = info.birthday.day;
}

//---------------------------------------------------------------------------
/**
 * @brief	保持しているMACアドレスと現在のDSのMACアドレスを比較
 * @param	sysdt		システムデータへのポインタ
 * @retval	TRUE		MACアドレスが一致した
 * @retval	FALSE		MACアドレスが一致しなかった
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_IdentifyMACAddress(const SYSTEMDATA * sysdt)
{
	int i;
	u8 adr[6];
	OS_GetMacAddress(adr);
	for (i = 0; i < 6; i++) {
		if (sysdt->MacAddress[i] != adr[i]) {
			return FALSE;
		}
	}
	return TRUE;
}

//---------------------------------------------------------------------------
/**
 * @brief	MACアドレスの取得
 * @param	sysdt		システムデータへのポインタ
 * @return	u8 * MACアドレス配列へのポインタ
 */
//---------------------------------------------------------------------------
const u8 * SYSTEMDATA_GetMacAddress(const SYSTEMDATA * sysdt)
{
	return sysdt->MacAddress;
}

//---------------------------------------------------------------------------
/**
 * @brief	保持しているRTCオフセットと現在のDSのRTCオフセットを比較
 * @param	sysdt		システムデータへのポインタ
 * @retval	TRUE		RTCオフセットが一致した
 * @retval	FALSE		RTCオフセットが一致しなかった
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_IdentifyRTCOffset(const SYSTEMDATA * sysdt)
{
	return (OS_GetOwnerRtcOffset() == sysdt->RTCOffset);
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
u8 SYSTEMDATA_GetBirthMonth(const SYSTEMDATA * sysdt)
{
	return sysdt->birth_month;
}

//---------------------------------------------------------------------------
/**
 */
//---------------------------------------------------------------------------
u8 SYSTEMDATA_GetBirthDay(const SYSTEMDATA * sysdt)
{
	return sysdt->birth_day;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi不思議な贈り物オープンフラグの取得
 * @param	sysdt		システムデータへのポインタ
 * @retval	BOOL
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_GetBeaconMPOpenFlag(const SYSTEMDATA * sysdt)
{
	return sysdt->BeaconMPOpenFlag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi不思議な贈り物オープンフラグの取得
 * @param	sysdt		システムデータへのポインタ
 * @param	flag		セットするBOOL値
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetBeaconMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag)
{
	sysdt->BeaconMPOpenFlag = flag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi不思議な贈り物オープンフラグの取得
 * @param	sysdt		システムデータへのポインタ
 * @retval	BOOL
 */
//---------------------------------------------------------------------------
BOOL SYSTEMDATA_GetWifiMPOpenFlag(const SYSTEMDATA * sysdt)
{
	return sysdt->WiFiMPOpenFlag;
}

//---------------------------------------------------------------------------
/**
 * @brief	Wi-Fi不思議な贈り物オープンフラグの取得
 * @param	sysdt		システムデータへのポインタ
 * @param	flag		セットするBOOL値
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetWifiMPOpenFlag(SYSTEMDATA * sysdt, BOOL flag)
{
	sysdt->WiFiMPOpenFlag = flag;
}


//---------------------------------------------------------------------------
/**
 * @brief	GTS・Wifiバトルタワー用Idの取得
 * @param	sysdt		システムデータへのポインタ
 * @param	profileId	[out]GameSpyプロファイルIDを出力するポインタ
 * @param	FriendKey	[out]ともだちコードを出力するポインタ
 * @param	u64			ともだちコードの値（初めて取得したFriendKeyをずっと保持）
 */
//---------------------------------------------------------------------------
s32 SYSTEMDATA_GetDpwInfo( const SYSTEMDATA * sysdt )
{

	return sysdt->profileId;

}

//---------------------------------------------------------------------------
/**
 * @brief	GTS・Wifiバトルタワー用Idの設定(初回のみ代入できる）
 * @param	sysdt		システムデータへのポインタ
 * @param	none
 */
//---------------------------------------------------------------------------
void SYSTEMDATA_SetDpwInfo( SYSTEMDATA * sysdt, s32 profileId )
{

	// GTS・Wifiバトルタワー用のID・ともだちコードが
	// 一回も登録されていなかった場合登録する
	if( sysdt->profileId==0 ){

		// 一度登録したら、GameSpyIdが変更になっても変わらない
		sysdt->profileId = profileId;

	}
}

//============================================================================================
//
//
//			ゲーム内時間参照・操作関数
//
//
//============================================================================================
#include "system/pm_rtc.h"
//------------------------------------------------------------------
/**
 * @brief	時間関連データの取得
 */
//------------------------------------------------------------------
void GMTIME_Init(GMTIME * gt)
{
	gt->use_flag = TRUE;
	GF_RTC_GetDateTime(&gt->sv_date, &gt->sv_time);
	gt->sv_day = RTC_ConvertDateToDay(&gt->sv_date);
	gt->start_sec = RTC_ConvertDateTimeToSecond(&gt->sv_date, &gt->sv_time);
	gt->clear_sec = 0;
	gt->penalty_time = 0;
}

//------------------------------------------------------------------
/**
 * @brief	ペナルティモードかどうかの取得
 * @param	gt		ゲーム内時間へのポインタ
 * @return	BOOL	TRUEのとき、ペナルティモード
 */
//------------------------------------------------------------------
BOOL GMTIME_IsPenaltyMode(const GMTIME * gt)
{
	if (gt->penalty_time != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	ペナルティ時間を減らす
 * @param	gt			ゲーム内時間へのポインタ
 * @param	diff_minute	減らす時間
 */
//------------------------------------------------------------------
void GMTIME_CountDownPenaltyTime(GMTIME * gt, int diff_minute)
{
	//セーブデータにゴミが入っていた場合の対策
	if (gt->penalty_time > 24 * 60) {
		gt->penalty_time = 24 * 60;
	}

	if (gt->penalty_time < diff_minute) {
		gt->penalty_time = 0;
	} else {
		gt->penalty_time -= diff_minute;
	}
}

//------------------------------------------------------------------
/**
 * @brief	ペナルティ時間をセットする
 * @param	gt			ゲーム内時間へのポインタ
 *
 * 24時間ペナルティ！
 */
//------------------------------------------------------------------
void GMTIME_SetPenaltyTime(GMTIME * gt)
{
	//ペナルティ時間をセットする
	gt->penalty_time = 60 * 24;	//24時間

	//時間経過を今からにする
	GF_RTC_GetDateTime(&gt->sv_date, &gt->sv_time);
	gt->sv_day = RTC_ConvertDateToDay(&gt->sv_date);
}

// 外部参照インデックスを作る時のみ有効(ゲーム中は無効)
#ifdef CREATE_INDEX
void *Index_Get_Profile_Offset(SYSTEMDATA *sys){ return &sys->profileId; }
#endif
