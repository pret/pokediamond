//============================================================================================
/**
 * @file	config.h
 * @brief	設定データアクセス用ヘッダ
 * @author	tamada GAME FREAK inc.
 * @date	2006.01.26
 */
//============================================================================================
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	設定データ型定義
 */
//----------------------------------------------------------
typedef struct _CONFIG CONFIG;

//---------------------------------------------------------------------------
/**
 * @brief	設定データ構造体定義
 *
 * 他の構造体のメンバーに入れるなど、扱いやすくするために公開した。
 * しかし、内部へのアクセスは必ずアクセス関数経由のみにすること。
 */
//---------------------------------------------------------------------------
struct _CONFIG {
	u16 msg_speed:4;			///<MSGSPEED		ＭＳＧ送りの速度
	u16 sound_mode:2;			///<SOUNDMODE		サウンド出力
	u16 battle_rule:1;			///<BATTLERULE		戦闘ルール
	u16 wazaeff_mode:1;			///<WAZAEFF_MODE	わざエフェクト
	u16 input_mode:2;			///<INPUTMODE		入力モード
	u16 window_type:5;			///<WINTYPE			ウィンドウタイプ
	u16 dummy:1;
};

//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
typedef enum {
	MSGSPEED_SLOW = 0,		///<メッセージ表示＝「おそい」
	MSGSPEED_NORMAL,		///<メッセージ表示＝「ふつう」
	MSGSPEED_FAST,			///<メッセージ表示＝「はやい」
	MSGSPEED_MAX,			///<
}MSGSPEED;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	WAZAEFF_MODE_ON = 0,		///<戦闘アニメ＝「みる」
	WAZAEFF_MODE_OFF,			///<戦闘アニメ＝「みない」
	WAZAEFF_MODE_MAX,			///<
}WAZAEFF_MODE;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	BATTLERULE_IREKAE = 0,
	BATTLERULE_KACHINUKI,
	BATTLERULE_MAX,
}BATTLERULE;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	SOUNDMODE_STEREO = 0,	///<サウンド出力=「ステレオ」
	SOUNDMODE_MONO,			///<サウンド出力=「モノラル」
//	SOUNDMODE_HEADPHONE,	///<サウンド出力=「ヘッドホン」06.02.14廃止 iwasawa
	SOUNDMODE_MAX,			///<
}SOUNDMODE;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	INPUTMODE_NORMAL = 0,	///<ボタン設定＝「ノーマル」
	INPUTMODE_START_X,		///<ボタン設定＝「START=X」
//	INPUTMODE_X_Y,			///<ボタン設定＝「X←→Y」06.05.30廃止
	INPUTMODE_L_A,			///<ボタン設定＝「L=A」06.07.12廃止 07.19復活
	INPUTMODE_MAX,			///<
}INPUTMODE;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum{
	WINTYPE_01,
	WINTYPE_02,
	WINTYPE_03,
	WINTYPE_04,
	WINTYPE_05,
	WINTYPE_06,
	WINTYPE_07,
	WINTYPE_08,
	WINTYPE_09,
	WINTYPE_10,
	WINTYPE_11,
	WINTYPE_12,
	WINTYPE_13,
	WINTYPE_14,
	WINTYPE_15,
	WINTYPE_16,
	WINTYPE_17,
	WINTYPE_18,
	WINTYPE_19,
	WINTYPE_20,
	WINTYPE_MAX,
}WINTYPE;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int CONFIG_GetWorkSize(void);
extern CONFIG * CONFIG_AllocWork(u32 heapID);
extern void CONFIG_Copy(const CONFIG * from, CONFIG * to);

//----------------------------------------------------------
//	CONFIG操作のための関数
//----------------------------------------------------------
extern void CONFIG_Init(CONFIG * cfg);

/**
 *	@brief	キーコンフィグをゲームに反映する
 */
extern void config_SetKeyConfig(SAVEDATA* sv,INPUTMODE mode);
static inline void CONFIG_SetKeyConfigFormSave(SAVEDATA* sv)
{
	config_SetKeyConfig(sv,0);
}
static inline void CONFIG_SetKeyConfig(INPUTMODE mode)
{
	config_SetKeyConfig(NULL,mode);
}

//	はなしのはやさ
extern MSGSPEED CONFIG_GetMsgSpeed(const CONFIG * cfg);
extern void CONFIG_SetMsgSpeed(CONFIG * cfg, MSGSPEED speed);
extern u8 CONFIG_GetMsgPrintSpeed( const CONFIG * cfg );

//	せんとう　アニメ
extern WAZAEFF_MODE CONFIG_GetWazaEffectMode(const CONFIG * cfg);
extern void CONFIG_SetWazaEffectMode(CONFIG * cfg, WAZAEFF_MODE mode);

//	しあいの　ルール
extern BATTLERULE CONFIG_GetBattleRule(const CONFIG * cfg);
extern void CONFIG_SetBattleRule(CONFIG * cfg, BATTLERULE rule);

//	サウンド
extern SOUNDMODE CONFIG_GetSoundMode(const CONFIG * cfg);
extern void CONFIG_SetSoundMode(CONFIG * cfg, SOUNDMODE snd_mode);

//	ボタンモード
extern INPUTMODE CONFIG_GetInputMode(const CONFIG * cfg);
extern void CONFIG_SetInputMode(CONFIG * cfg, INPUTMODE mode);

//	ウィンドウタイプ
extern WINTYPE CONFIG_GetWindowType(const CONFIG * cfg);
extern void CONFIG_SetWindowType(CONFIG * cfg, WINTYPE type);

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern CONFIG * SaveData_GetConfig(SAVEDATA * sv);

//----------------------------------------------------------
//	デバッグ用データ生成のための関数
//----------------------------------------------------------
//extern void Debug_Config_Make(CONFIG * cfg, const STRCODE * name, int sex);

#endif //__CONFIG_H__
