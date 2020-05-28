//******************************************************************************
/**
 *
 * @file	player.h
 * @brief	���@
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#ifndef PLAYER_H_FILE
#define PLAYER_H_FILE

//==============================================================================
//	�f�o�b�O
//==============================================================================
//----
#ifdef PM_DEBUG
//----
//����`�Ŏ��@�f�o�b�O�@�\�S��OFF
#define PLAYER_DEBUG
//----
#endif	//PM_DEBUG
//----

//----
#ifdef PLAYER_DEBUG
//----
//��`���鎖�Ńf�o�b�O�ړ��\
#define PLAYER_DEBUG_MOVE
//��`�ŉ��̓t���O�̃C�x���g�`�F�b�N���s��
//#define DEBUG_JIKI_KAIRIKI_FLAG_CHECK_ON
//��`�őꉺ��o�O����
//#define DEBUG_JIKI_TAKIKUDARI_BUG_ON
//----
#endif //PLAYER_DEBUG
//----

//==============================================================================
//	incldue
//==============================================================================
#include "fieldobj.h"
#include "div_map_cont_def.h"
#include "eoa.h"

#include "player_code.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	�����Ԃ�\���l
//--------------------------------------------------------------
enum
{
	OBJ_MOVE_VALUE_STOP = 0,								///<��~��Ԃł���
	OBJ_MOVE_VALUE_WALK,									///<�ړ����ł���
	OBJ_MOVE_VALUE_TURN,									///<�U�������Ԃł���
};

//--------------------------------------------------------------
///	�����
//--------------------------------------------------------------
enum
{
	OBJ_MOVE_STATE_OFF = 0,									///<���얳��
	OBJ_MOVE_STATE_START,									///<����J�n
	OBJ_MOVE_STATE_ON,										///<���쒆
	OBJ_MOVE_STATE_END,										///<����I��
};

//--------------------------------------------------------------
///	���@�ړ�����߂�l
//--------------------------------------------------------------
#define JIKI_MOVE_HIT_BIT_NON		(0)						///<��Q������
#define JIKI_MOVE_HIT_BIT_ATTR		(1<<0)					///<�A�g���r���[�g�q�b�g
#define JIKI_MOVE_HIT_BIT_OBJ		(1<<1)					///<OBJ���m�̏Փ�
#define JIKI_MOVE_HIT_BIT_JUMP		(1<<2)					///<�W�����v�q�b�g
#define JIKI_MOVE_HIT_BIT_EXIT		(1<<3)					///<�o������q�b�g
#define JIKI_MOVE_HIT_BIT_TAKE_OFF	(1<<4)					///<�W�����v��q�b�g
#define JIKI_MOVE_HIT_BIT_WATER		(1<<5)					///<���q�b�g
#define JIKI_MOVE_HIT_BIT_BRIDGEHV	(1<<6)					///<��{���q�b�g

//#define JIKI_MOVE_HIT_BIT_KAIRIKI	(1<<3)					///<�����肫�q�b�g->�C�x���g��
//#define JIKI_MOVE_HIT_BIT_SWIM		(1<<4)				///<�Ȃ݂̂�q�b�g->�C�x���g��

//--------------------------------------------------------------
///	���@�C�x���g
//--------------------------------------------------------------
typedef enum
{
	HERO_EVBIT_NON				= 0,						///<�C�x���g�w��@����
	HERO_EVBIT_PERMIT_KAIRIKI	= (1<<0),					///<���̓C�x���g������
	HERO_EVBIT_PREMIT_TAKINOBORI = (1<<1),					///<��o��C�x���g������
}HERO_EVBIT;

//--------------------------------------------------------------
///	�L�[�@�{�^��
//--------------------------------------------------------------
#define JIKI_DASH_BUTTON			(PAD_BUTTON_B)	///<�_�b�V���ł���{�^��
#define JIKI_GEAR_CHG_BUTTON		(PAD_BUTTON_B)			///<�M�A�`�F���W�{�^��

//----
#ifdef PLAYER_DEBUG_MOVE
//----
#define DEBUG_WALK_PAD				(PAD_BUTTON_R)			//�f�o�b�O�ړ��\�{�^��
//----
#endif
//----

//--------------------------------------------------------------
///	���@���x
//--------------------------------------------------------------
enum
{
	JIKI_SPEED_0 = 0,										///<���x0(1)
	JIKI_SPEED_1,
	JIKI_SPEED_2,
	JIKI_SPEED_3,
};

#define JIKI_SPEED_SNOWBALL_BREAK (JIKI_SPEED_1)			///<��ʔj�󑬓x

#define JIKI_SPEED_CYCLE3		(JIKI_SPEED_2)				///<�R�����x
#define JIKI_SPEED_CYCLE4_TOP	(JIKI_SPEED_3)				///<�S���ō����x
#define JIKI_SPEED_BRAKE_ON		(JIKI_SPEED_2)				///<�u���[�L�J�n���x

#define JIKI_SPEED_VALUE_1		(1)							///<�P��

//--------------------------------------------------------------
///	���@�t���[���X�s�[�h
//--------------------------------------------------------------
enum
{
	JIKI_FRAME_SPEED_32F = 0,
	JIKI_FRAME_SPEED_16F,
	JIKI_FRAME_SPEED_8F,
	JIKI_FRAME_SPEED_6F,
	JIKI_FRAME_SPEED_4F,
	JIKI_FRAME_SPEED_2F,
};

#define JIKI_FRAME_SPEED_NORMAL (JIKI_FRAME_SPEED_8F)

//--------------------------------------------------------------
///	�M�A�R�C�S����
//--------------------------------------------------------------
enum
{
	GEAR_3 = 0,
	GEAR_4,
	GEAR_NOT,
};

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
//	PLAYER_STATE_PTR��`
//--------------------------------------------------------------
typedef struct _TAG_PLAYER_STATE * PLAYER_STATE_PTR;
typedef struct _TAG_PLAYER_STATE * const CONST_PLAYER_STATE_PTR;

//--------------------------------------------------------------
//	PLAYER_SAVEDATA�\����
//--------------------------------------------------------------
typedef struct
{
	u16 gear_type;										///<���݂̎��]�ԃM�A�^�C�v
	u16 shoes_flag;										///<B�_�b�V������V���[�Y�t���O
	u32 form;											///<���@�`��
}PLAYER_SAVE_DATA;

#define PLAYER_SAVE_DATA_SIZE (sizeof(PLAYER_SAVE_DATA))

//==============================================================================
//	�O���錾
//==============================================================================
//--------------------------------------------------------------
//	player.c
//--------------------------------------------------------------
extern PLAYER_STATE_PTR Player_Init( CONST_FIELD_OBJ_SYS_PTR fos,
		int x, int z, int dir, int form, int sex, PLAYER_SAVE_DATA *save );
extern PLAYER_STATE_PTR Player_FieldOBJUseRecover(
		CONST_FIELD_OBJ_SYS_PTR fos, PLAYER_SAVE_DATA *save, int sex );
extern void Player_DrawInit( PLAYER_STATE_PTR jiki );
extern void Player_Delete( PLAYER_STATE_PTR jiki );
extern void Player_DeleteAll( PLAYER_STATE_PTR jiki );
extern FIELD_OBJ_PTR Player_FieldOBJSearch( CONST_FIELD_OBJ_SYS_PTR fos );

extern int Player_DirGet( const PLAYER_STATE_PTR jiki );
extern void Player_DirSet( PLAYER_STATE_PTR jiki,  int dir );
extern int Player_DirMoveGet( const PLAYER_STATE_PTR jiki );
extern int Player_NowGPosXGet( const PLAYER_STATE_PTR jiki );
extern int Player_NowGPosZGet( const PLAYER_STATE_PTR jiki );
extern int Player_OldGPosXGet( const PLAYER_STATE_PTR jiki );
extern int Player_OldGPosZGet( const PLAYER_STATE_PTR jiki );
extern void Player_VecPosGet( const PLAYER_STATE_PTR jiki, VecFx32 *vec );
extern const VecFx32 * Player_VecPosPtrGet( const PLAYER_STATE_PTR jiki );
extern VecFx32 * Player_VecDrawOffsPtrGet( PLAYER_STATE_PTR jiki );
extern void Player_MoveValueSet( PLAYER_STATE_PTR jiki,  int val );
extern int Player_MoveValueGet( const PLAYER_STATE_PTR jiki );
extern void Player_MoveStateSet( PLAYER_STATE_PTR jiki,  int state );
extern int Player_MoveStateGet( const PLAYER_STATE_PTR jiki );
extern void Player_DispON_OFF_Set( PLAYER_STATE_PTR jiki,  int flag );
extern int Player_DispON_OFF_Get( const PLAYER_STATE_PTR jiki );
extern void Player_FieldOBJSet( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj );
extern FIELD_OBJ_PTR Player_FieldOBJGet( PLAYER_STATE_PTR jiki );
extern CONST_FIELD_OBJ_PTR Player_ConstFieldOBJGet( const PLAYER_STATE_PTR jiki );
extern void Player_FormSet( PLAYER_STATE_PTR jiki, int form );
extern int Player_FormGet( PLAYER_STATE_PTR jiki );
extern void Player_RequestBit_ON( PLAYER_STATE_PTR jiki, u32 bit );
extern void Player_RequestBit_Set( PLAYER_STATE_PTR jiki, u32 bit );
extern u32 Player_RequestBit_Get( PLAYER_STATE_PTR jiki );
extern void Player_SexSet( PLAYER_STATE_PTR jiki, int sex );
extern int Player_SexGet( PLAYER_STATE_PTR jiki );
extern int Player_MoveSpeedGet( PLAYER_STATE_PTR jiki );
extern void Player_MoveSpeedSet( PLAYER_STATE_PTR jiki, int speed );
extern void Player_MoveSpeedClear( PLAYER_STATE_PTR jiki );
extern int Player_MoveSpeedAdd( PLAYER_STATE_PTR jiki, int add, int max );
extern void Player_InputKeyDirXSet( PLAYER_STATE_PTR jiki, int dir );
extern int Player_InputKeyDirXGet( PLAYER_STATE_PTR jiki );
extern void Player_InputKeyDirZSet( PLAYER_STATE_PTR jiki, int dir );
extern int Player_InputKeyDirZGet( PLAYER_STATE_PTR jiki );
extern void Player_InputKeyDirSet( PLAYER_STATE_PTR jiki, int dir_x, int dir_z );
extern void Player_JointEoaSet( PLAYER_STATE_PTR jiki, EOA_PTR eoa );
extern EOA_PTR Player_JointEoaGet( PLAYER_STATE_PTR jiki );
extern PLAYER_SAVE_DATA * Player_SaveDataPtrGet( PLAYER_STATE_PTR jiki );
extern void Player_AcmdCodeSet( PLAYER_STATE_PTR jiki, u32 ac );
extern u32 Player_AcmdCodeGet( PLAYER_STATE_PTR jiki );
extern u32 Player_SEWalkLRNumGet( PLAYER_STATE_PTR jiki );
extern void Player_SEWalkLRNumInc( PLAYER_STATE_PTR jiki );

extern void Player_GPosNowUpdate( const PLAYER_STATE_PTR jiki );
extern void Player_GPosAddDir( PLAYER_STATE_PTR jiki,  int dir );
extern void Player_VecPosInit( PLAYER_STATE_PTR jiki, const VecFx32 *vec, int dir );
extern void Player_GPosInit( PLAYER_STATE_PTR jiki, int x, int z, int dir );
extern void Player_VecPosYSet( PLAYER_STATE_PTR jiki, fx32 y );
extern void Player_HeightGet_ON_OFF( PLAYER_STATE_PTR jiki, int flag );
extern void Player_HeightGetSet_ON_OFF( PLAYER_STATE_PTR jiki, int flag );
extern int Player_OBJCodeSexGet( int code );
extern int Player_FormSexOBJCodeGet( int form, int sex );
extern u32 Player_FormRequestGet( int form );
extern int Player_OBJCodeFormGet( int code );
extern PLAYER_STATE_PTR Player_FieldSysWorkPlayerGet( FIELDSYS_WORK *fsys );

extern void Player_MoveBitSet_Force( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_Force( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_UnderOFF( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_UnderOFF( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_CycleBrake( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_CycleBrake( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_CyclingRoad( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_CyclingRoad( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_DeepSwampOFF( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_DeepSwampOFF( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_SandFloatSet( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_SandFloat( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_StepON( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_StepOFF( PLAYER_STATE_PTR jiki );
extern int Player_MoveBitCheck_Step( PLAYER_STATE_PTR jiki );
extern void Player_MoveBitSet_ForceSaveSpeed( PLAYER_STATE_PTR jiki, int flag );
extern int Player_MoveBitCheck_ForceSaveSpeed( PLAYER_STATE_PTR jiki );

extern void Player_SaveDataInit( PLAYER_SAVE_DATA *save );
extern int Player_SaveDataDashCheck( PLAYER_SAVE_DATA *save );
extern void Player_SaveDataDashSet( PLAYER_SAVE_DATA *save, int flag );
extern int Player_SaveDataGearCheck( PLAYER_SAVE_DATA *save );
extern void Player_SaveDataGearSet( PLAYER_SAVE_DATA *save, int gear );
extern void Player_SaveDataGetGearSet( PLAYER_STATE_PTR jiki, int gear );
extern int Player_SaveDataGetGearGet( PLAYER_STATE_PTR jiki );
extern u32 Player_SaveDataFormGet( PLAYER_SAVE_DATA *save );
extern void Player_SaveDataFormSet( PLAYER_SAVE_DATA *save, u32 form );
extern void Player_SaveDataGetFormSet( PLAYER_STATE_PTR jiki, u32 form );
extern u32 Player_SaveDataGetFormGet( PLAYER_STATE_PTR jiki );

//--------------------------------------------------------------
//	player_move.c
//--------------------------------------------------------------
extern void Player_MoveControl(
	PLAYER_STATE_PTR jiki, DMC_CONST_PTR dmc, int dir, u16 key_trg, u16 key_prs, BOOL touch );
extern int Player_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir );
extern void Player_MoveStateUpdate( PLAYER_STATE_PTR jiki );
extern void Player_MoveStateClear( PLAYER_STATE_PTR jiki );
extern int Player_MoveForceStopCheck( PLAYER_STATE_PTR jiki );
extern void Player_MoveForceStop( PLAYER_STATE_PTR jiki, int dir );

extern u32 Player_MoveHitCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );

extern int Player_KeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs );
extern int Player_MoveCancellCheck( PLAYER_STATE_PTR jiki );
extern int Player_KeyDashCheck( PLAYER_STATE_PTR jiki, u16 prs );
extern int Player_AcmdCodeDashCheck( PLAYER_STATE_PTR jiki );
extern int Player_MoveSelectValueCheck( PLAYER_STATE_PTR jiki, int dir );

extern u32 Player_KeyMoveSelectAcmdCodeGet(
		PLAYER_STATE_PTR jiki, u16 trg, u16 prs, int speed, int dash, int hit );
extern int Player_AcmdSetCheck( PLAYER_STATE_PTR jiki );
extern void Player_AcmdSet( PLAYER_STATE_PTR jiki, u32 ac );
extern u32 Player_NextDirAttrGet( PLAYER_STATE_PTR jiki, int dir );
extern void Player_DirNextGridPosGet( PLAYER_STATE_PTR jiki, int dir, int *gx, int *gz );
extern void Player_DirFrontGridPosGet( PLAYER_STATE_PTR jiki, int *gx, int *gz );

//--------------------------------------------------------------
//	player_event.c
//--------------------------------------------------------------
extern void Player_RequestSet( PLAYER_STATE_PTR jiki, u32 req );
extern void Player_Request( PLAYER_STATE_PTR jiki );

extern int Player_EventMoveCheck(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag );

extern void Player_EventNaminoriStart( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
extern void EventCmd_NaminoriCall( GMEVENT_CONTROL *event, int dir, int poke_useno );

extern void Player_EventKabeNoboriStart( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
extern void EventCmd_KabeNoboriCall( GMEVENT_CONTROL *event, int dir, int poke_useno );

//extern int Player_EventAttrCheck_Naminori( PLAYER_STATE_PTR jiki, u32 attr );
extern int Player_EventAttrCheck_Naminori( PLAYER_STATE_PTR jiki, u32 nattr, u32 fattr );

extern int Player_EventAttrCheck_KabeNobori( u32 attr, int dir );

extern void Player_EventTakiNoboriStart( FIELDSYS_WORK *fsys, int dir );
extern void EventCmd_TakiNoboriCall( GMEVENT_CONTROL *event, int dir, int poke_useno );

extern void Player_EventContestHeroChangeStart( FIELDSYS_WORK *fsys );
extern void EventCmd_ContestHeroChange( GMEVENT_CONTROL *event );

extern void Player_EventPoketchChange( PLAYER_STATE_PTR jiki );
extern void Player_EventPoketchCancel( PLAYER_STATE_PTR jiki );

extern TCB_PTR Player_ReportDrawProcSet( FIELDSYS_WORK *fsys );
extern void Player_ReportDrawProcDelete( TCB_PTR tcb );

//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
#ifdef PLAYER_DEBUG
extern void DEBUG_Player_Init( PLAYER_STATE_PTR jiki );
#endif
	
#endif //PLAYER_H_FILE
