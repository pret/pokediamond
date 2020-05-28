//==============================================================================
/**
 * @file	field_fishing.h
 * @brief	�t�B�[���h�@�C�x���g�@�ނ�
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_FISHING_H_FILE
#define FIELD_FISHING_H_FILE

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	�ނ�Ǝ��
//--------------------------------------------------------------
typedef enum
{
	FISHINGROD_BAD,			///<�ڂ�̂肴��
	FISHINGROD_GOOD,		///<�����肴��
	FISHINGROD_GREAT,		///<�������肴��
}FISHINGROD_TYPE;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * EventWorkSet_Fishing( FIELDSYS_WORK *fsys, u32 heap_id, FISHINGROD_TYPE type );
extern BOOL GMEVENT_Fishing( GMEVENT_CONTROL *event );

extern TCB_PTR FieldFishing_Init( FIELDSYS_WORK *fsys, FISHINGROD_TYPE type, BOOL hit );
extern int FieldFishing_EndCheck( TCB_PTR tcb );
extern int FieldFishing_ResultGet( TCB_PTR tcb );
extern void FieldFishing_Delete( TCB_PTR tcb );

#endif //FIELD_FISHING_H_FILE
