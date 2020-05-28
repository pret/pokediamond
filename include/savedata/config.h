//============================================================================================
/**
 * @file	config.h
 * @brief	�ݒ�f�[�^�A�N�Z�X�p�w�b�_
 * @author	tamada GAME FREAK inc.
 * @date	2006.01.26
 */
//============================================================================================
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�ݒ�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _CONFIG CONFIG;

//---------------------------------------------------------------------------
/**
 * @brief	�ݒ�f�[�^�\���̒�`
 *
 * ���̍\���̂̃����o�[�ɓ����ȂǁA�����₷�����邽�߂Ɍ��J�����B
 * �������A�����ւ̃A�N�Z�X�͕K���A�N�Z�X�֐��o�R�݂̂ɂ��邱�ƁB
 */
//---------------------------------------------------------------------------
struct _CONFIG {
	u16 msg_speed:4;			///<MSGSPEED		�l�r�f����̑��x
	u16 sound_mode:2;			///<SOUNDMODE		�T�E���h�o��
	u16 battle_rule:1;			///<BATTLERULE		�퓬���[��
	u16 wazaeff_mode:1;			///<WAZAEFF_MODE	�킴�G�t�F�N�g
	u16 input_mode:2;			///<INPUTMODE		���̓��[�h
	u16 window_type:5;			///<WINTYPE			�E�B���h�E�^�C�v
	u16 dummy:1;
};

//----------------------------------------------------------
/**
 */
//----------------------------------------------------------
typedef enum {
	MSGSPEED_SLOW = 0,		///<���b�Z�[�W�\�����u�������v
	MSGSPEED_NORMAL,		///<���b�Z�[�W�\�����u�ӂ��v
	MSGSPEED_FAST,			///<���b�Z�[�W�\�����u�͂₢�v
	MSGSPEED_MAX,			///<
}MSGSPEED;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	WAZAEFF_MODE_ON = 0,		///<�퓬�A�j�����u�݂�v
	WAZAEFF_MODE_OFF,			///<�퓬�A�j�����u�݂Ȃ��v
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
	SOUNDMODE_STEREO = 0,	///<�T�E���h�o��=�u�X�e���I�v
	SOUNDMODE_MONO,			///<�T�E���h�o��=�u���m�����v
//	SOUNDMODE_HEADPHONE,	///<�T�E���h�o��=�u�w�b�h�z���v06.02.14�p�~ iwasawa
	SOUNDMODE_MAX,			///<
}SOUNDMODE;

//----------------------------------------------------------
//----------------------------------------------------------
typedef enum {
	INPUTMODE_NORMAL = 0,	///<�{�^���ݒ聁�u�m�[�}���v
	INPUTMODE_START_X,		///<�{�^���ݒ聁�uSTART=X�v
//	INPUTMODE_X_Y,			///<�{�^���ݒ聁�uX����Y�v06.05.30�p�~
	INPUTMODE_L_A,			///<�{�^���ݒ聁�uL=A�v06.07.12�p�~ 07.19����
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
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//----------------------------------------------------------
extern int CONFIG_GetWorkSize(void);
extern CONFIG * CONFIG_AllocWork(u32 heapID);
extern void CONFIG_Copy(const CONFIG * from, CONFIG * to);

//----------------------------------------------------------
//	CONFIG����̂��߂̊֐�
//----------------------------------------------------------
extern void CONFIG_Init(CONFIG * cfg);

/**
 *	@brief	�L�[�R���t�B�O���Q�[���ɔ��f����
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

//	�͂Ȃ��̂͂₳
extern MSGSPEED CONFIG_GetMsgSpeed(const CONFIG * cfg);
extern void CONFIG_SetMsgSpeed(CONFIG * cfg, MSGSPEED speed);
extern u8 CONFIG_GetMsgPrintSpeed( const CONFIG * cfg );

//	����Ƃ��@�A�j��
extern WAZAEFF_MODE CONFIG_GetWazaEffectMode(const CONFIG * cfg);
extern void CONFIG_SetWazaEffectMode(CONFIG * cfg, WAZAEFF_MODE mode);

//	�������́@���[��
extern BATTLERULE CONFIG_GetBattleRule(const CONFIG * cfg);
extern void CONFIG_SetBattleRule(CONFIG * cfg, BATTLERULE rule);

//	�T�E���h
extern SOUNDMODE CONFIG_GetSoundMode(const CONFIG * cfg);
extern void CONFIG_SetSoundMode(CONFIG * cfg, SOUNDMODE snd_mode);

//	�{�^�����[�h
extern INPUTMODE CONFIG_GetInputMode(const CONFIG * cfg);
extern void CONFIG_SetInputMode(CONFIG * cfg, INPUTMODE mode);

//	�E�B���h�E�^�C�v
extern WINTYPE CONFIG_GetWindowType(const CONFIG * cfg);
extern void CONFIG_SetWindowType(CONFIG * cfg, WINTYPE type);

//----------------------------------------------------------
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern CONFIG * SaveData_GetConfig(SAVEDATA * sv);

//----------------------------------------------------------
//	�f�o�b�O�p�f�[�^�����̂��߂̊֐�
//----------------------------------------------------------
//extern void Debug_Config_Make(CONFIG * cfg, const STRCODE * name, int sex);

#endif //__CONFIG_H__
