//==============================================================================
/**
 * @file	field_ananuke.h
 * @brief	�t�B�[���h�@���Ȃʂ��̂Ђ��@���Ȃق�@�e���|�[�g
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_ANANUKE_H_FILE
#define FIELD_ANANUKE_H_FILE

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	���@��^�C�v
//--------------------------------------------------------------
typedef enum
{
	ANATYPE_ANA,		///<������
	ANATYPE_ANAHORI,	///<�����@��
	ANATYPE_TEL,		///<�e���|�[�g
}ANATYPE;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * EventWorkSet_AnanukeMapChange( FIELDSYS_WORK *fsys, u32 heap_id );
extern BOOL GMEVENT_AnanukeMapChange( GMEVENT_CONTROL *event );

extern void * EventWorkSet_AnanukeMapIn( FIELDSYS_WORK *fsys, u32 heap_id, ANATYPE type );
extern BOOL GMEVENT_AnanukeMapIn( GMEVENT_CONTROL *event );

extern void * EventWorkSet_AnawohoruMapChange( FIELDSYS_WORK *, POKEMON_PARAM *, u32 heap_id);
extern BOOL GMEVENT_AnawohoruMapChange( GMEVENT_CONTROL *event );

extern void * EventWorkSet_TeleportMapChange(FIELDSYS_WORK *, POKEMON_PARAM *, u32 );
extern BOOL GMEVENT_TeleportMapChange( GMEVENT_CONTROL *event );

//���I�[�o�[���C�ŃA�N�Z�X�s�ɂȂ�̂ŁA�폜	20060712 saito
///extern BOOL EventCheck_Ananuke( int zone_id );

#endif //FIELD_ANANUKE_H_FILE
