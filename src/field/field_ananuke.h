//==============================================================================
/**
 * @file	field_ananuke.h
 * @brief	フィールド　あなぬけのひも　あなほり　テレポート
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
///	穴掘りタイプ
//--------------------------------------------------------------
typedef enum
{
	ANATYPE_ANA,		///<穴抜け
	ANATYPE_ANAHORI,	///<穴を掘る
	ANATYPE_TEL,		///<テレポート
}ANATYPE;

//==============================================================================
//	外部参照
//==============================================================================
extern void * EventWorkSet_AnanukeMapChange( FIELDSYS_WORK *fsys, u32 heap_id );
extern BOOL GMEVENT_AnanukeMapChange( GMEVENT_CONTROL *event );

extern void * EventWorkSet_AnanukeMapIn( FIELDSYS_WORK *fsys, u32 heap_id, ANATYPE type );
extern BOOL GMEVENT_AnanukeMapIn( GMEVENT_CONTROL *event );

extern void * EventWorkSet_AnawohoruMapChange( FIELDSYS_WORK *, POKEMON_PARAM *, u32 heap_id);
extern BOOL GMEVENT_AnawohoruMapChange( GMEVENT_CONTROL *event );

extern void * EventWorkSet_TeleportMapChange(FIELDSYS_WORK *, POKEMON_PARAM *, u32 );
extern BOOL GMEVENT_TeleportMapChange( GMEVENT_CONTROL *event );

//↓オーバーレイでアクセス不可になるので、削除	20060712 saito
///extern BOOL EventCheck_Ananuke( int zone_id );

#endif //FIELD_ANANUKE_H_FILE
