//============================================================================================
/**
 * @file	config.c
 * @brief	設定関連アクセス
 * @author	tamada	GAME FREAK Inc.
 * @date	2006.01.27
 *
 */
//============================================================================================

#include "savedata/savedata.h"
#include "misc_local.h"
#include "config_local.h"
//#include "savedata/config.h"
#include "gflib/system.h"

#include "common.h"

//============================================================================================
//============================================================================================
#define	MSG_SPEED_SLOW		( 8 )		///< メッセージ速度：遅い
#define	MSG_SPEED_NORMAL	( 4 )		///< メッセージ速度：普通
#define	MSG_SPEED_FAST		( 1 )		///< メッセージ速度：速い


//============================================================================================
//============================================================================================


//----------------------------------------------------------
//---------------------------------------------------------
int CONFIG_GetWorkSize(void)
{
	return sizeof(CONFIG);
}

//----------------------------------------------------------
//---------------------------------------------------------
CONFIG * CONFIG_AllocWork(u32 heapID)
{
	CONFIG * cfg;
	cfg = sys_AllocMemory(heapID, sizeof(CONFIG));
	CONFIG_Init(cfg);
	return cfg;
}

//----------------------------------------------------------
//---------------------------------------------------------
void CONFIG_Copy(const CONFIG * from, CONFIG * to)
{
	MI_CpuCopy8(from, to, sizeof(CONFIG));
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_Init(CONFIG * cfg)
{
	MI_CpuFill8(cfg, 0, sizeof(CONFIG));
	cfg->msg_speed = MSGSPEED_NORMAL;
	cfg->sound_mode = SOUNDMODE_STEREO;
	cfg->battle_rule = BATTLERULE_IREKAE;
	cfg->wazaeff_mode = WAZAEFF_MODE_ON;
	cfg->input_mode = INPUTMODE_NORMAL;
	cfg->window_type = WINTYPE_01;
}

//============================================================================================
//============================================================================================
/**
 *	@brief	キーコンフィグをゲームに反映する
 */
void config_SetKeyConfig(SAVEDATA* sv,INPUTMODE mode)
{
	CONFIG* config;
	
	if(sv != NULL){
		mode = CONFIG_GetInputMode(SaveData_GetConfig(sv));
	}
	switch(mode){
	case INPUTMODE_START_X:
		sys.key_control_mode = KEYCONTROL_PATTERN1;
		break;
#if 0
	case INPUTMODE_X_Y:
		sys.key_control_mode = KEYCONTROL_PATTERN2;
		break;
#endif
	case INPUTMODE_L_A:
		sys.key_control_mode = KEYCONTROL_PATTERN3;
		break;
	case INPUTMODE_NORMAL:
	default:
		sys.key_control_mode = KEYCONTROL_NORMAL;
		break;
	}
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
MSGSPEED CONFIG_GetMsgSpeed(const CONFIG * cfg)
{
	return cfg->msg_speed;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_SetMsgSpeed(CONFIG * cfg, MSGSPEED speed)
{
	cfg->msg_speed = speed;
}

//----------------------------------------------------------
/**
 * @brief	設定データから文字描画速度を取得
 * @param	cfg		コンフィグデータ
 * @return	文字描画速度
 */
//---------------------------------------------------------
u8 CONFIG_GetMsgPrintSpeed( const CONFIG * cfg )
{
	int speed = CONFIG_GetMsgSpeed(cfg);
	if (speed == 0){
		return MSG_SPEED_SLOW;
	} else if (speed == 1) {
		return MSG_SPEED_NORMAL;
	} else {
		return MSG_SPEED_FAST;
	}
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
SOUNDMODE CONFIG_GetSoundMode(const CONFIG * cfg)
{
	return cfg->sound_mode;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_SetSoundMode(CONFIG * cfg, SOUNDMODE snd_mode)
{
	cfg->sound_mode = snd_mode;
}

//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
WAZAEFF_MODE CONFIG_GetWazaEffectMode(const CONFIG * cfg)
{
	return cfg->wazaeff_mode;
}

//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
void CONFIG_SetWazaEffectMode(CONFIG * cfg, WAZAEFF_MODE mode)
{
	cfg->wazaeff_mode = mode;
}
//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
BATTLERULE CONFIG_GetBattleRule(const CONFIG * cfg)
{
	return cfg->battle_rule;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_SetBattleRule(CONFIG * cfg, BATTLERULE rule)
{
	cfg->battle_rule = rule;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
INPUTMODE CONFIG_GetInputMode(const CONFIG * cfg)
{
	return cfg->input_mode;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_SetInputMode(CONFIG * cfg, INPUTMODE mode)
{
	cfg->input_mode = mode;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
WINTYPE CONFIG_GetWindowType(const CONFIG * cfg)
{
	return cfg->window_type;
}

//----------------------------------------------------------
/**
 */
//---------------------------------------------------------
void CONFIG_SetWindowType(CONFIG * cfg, WINTYPE type)
{
	cfg->window_type = type;
}
