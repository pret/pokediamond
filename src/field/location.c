//===========================================================================
/**
 * @file	location.c
 * @brief	�}�b�v�ʒu�̏������Ȃ�
 * @date	2006.06.02
 * @author	tamada GAME FREAK inc.
 *
 * debug_init.c --> fieldsys.c --> location.c�ɓƗ�
 */
//===========================================================================

#include "common.h"

#include "field/location.h"

#include "mapdefine.h"		//ZONE_ID_�`
#include "fieldobj_code.h"	//DIR_DOWN

#include "player.h"
#include "situation_local.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
//	�Q�[���J�n�ʒu�̒�`
//------------------------------------------------------------------
enum {
	//GAME_START_ZONE = ZONE_ID_T01R0102,
	GAME_START_ZONE = ZONE_ID_T01R0202,		//06.03.07�ύX
	GAME_START_X = 4,
	GAME_START_Z = 6,

	DEBUG_START_ZONE = ZONE_ID_C01,
	DEBUG_START_X = 174,
	DEBUG_START_Z = 764,

	GAME_START_EZONE = ZONE_ID_T01,
	GAME_START_EX = 116,
	GAME_START_EZ = 886,
};

//------------------------------------------------------------------
/**
 * @brief	LOCATION�ɏ����X�^�[�g�ʒu���Z�b�g
 */
//------------------------------------------------------------------
void LOCATION_SetFirstPos(LOCATION_WORK * location)
{
	static const LOCATION_WORK StartLocation = {
		GAME_START_ZONE,
		DOOR_ID_JUMP_CODE,
		GAME_START_X,
		GAME_START_Z,
		DIR_UP
	};
	*location = StartLocation;
}
//------------------------------------------------------------------
/**
 * @brief	EscapeLOCATION�ɏ����X�^�[�g�ʒu���Z�b�g
 */
//------------------------------------------------------------------
void LOCATION_SetFirstEscapePos(LOCATION_WORK * location)
{
	static const LOCATION_WORK EscapeLocation = {
		GAME_START_EZONE,
		DOOR_ID_JUMP_CODE,
		GAME_START_EX,
		GAME_START_EZ,
		DIR_DOWN
	};
	*location = EscapeLocation;
}

//------------------------------------------------------------------
/**
 * @brief	���݈ʒu�������X�^�[�g�ʒu�ɃZ�b�g����
 */
//------------------------------------------------------------------
void LOCATION_GameInit(SAVEDATA * sv)
{
	SITUATION * sit = SaveData_GetSituation(sv);
	LOCATION_WORK * now = Situation_GetNowLocation(sit);
	LOCATION_SetFirstPos(now);
}

#ifdef	PM_DEBUG
//------------------------------------------------------------------
/**
 * @brief	���݈ʒu���f�o�b�O�p�����J�n�ʒu�ɃZ�b�g����
 */
//------------------------------------------------------------------
void LOCATION_GameInit_Debug(SAVEDATA * sv)
{
	static const LOCATION_WORK DebugStartLocation = {
		DEBUG_START_ZONE,
		DOOR_ID_JUMP_CODE,
		DEBUG_START_X,
		DEBUG_START_Z,
		DIR_DOWN,
	};
	SITUATION * sit = SaveData_GetSituation(sv);
	LOCATION_WORK * now = Situation_GetNowLocation(sit);
	*now = DebugStartLocation;
}
#endif

