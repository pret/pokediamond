//============================================================================================
/**
 * @file	pms_word.h
 * @bfief	簡易会話用単語データ取り扱い
 * @author	taya
 * @date	06.01.20
 */
//============================================================================================
#ifndef __PMS_WORD_H__
#define __PMS_WORD_H__

#include "system\pms_data.h"

typedef struct _PMSW_MAN	PMSW_MAN;


extern PMSW_MAN* PMSW_MAN_Create(u32 heapID);
extern void PMSW_MAN_Delete( PMSW_MAN* man );
extern void PMSW_MAN_CopyStr( PMSW_MAN* man, PMS_WORD  pms_word, STRBUF* buf );
extern void PMSW_GetStr( PMS_WORD pms_word, STRBUF* dst );
extern PMS_WORD  PMSW_GetWordNumberByGmmID( u32 gmmID, u32 wordID );


extern int PMSW_GetDupWordCount( PMS_WORD word );
extern PMS_WORD PMSW_GetDupWord( PMS_WORD word, int idx );


//===================================================================================
// セーブデータ処理
//===================================================================================
#include "savedata\savedata.h"

typedef struct _PMSW_SAVEDATA	PMSW_SAVEDATA;

//--------------------------------------------------
/**
 *	各国あいさつことばのID
 *	（gmmと連動しているため順番は固定）
 */
//--------------------------------------------------
typedef enum {
	PMSW_AISATSU_JP,	// 日本語
	PMSW_AISATSU_EN,	// 英語
	PMSW_AISATSU_FR,	// フランス語
	PMSW_AISATSU_IT,	// イタリア語
	PMSW_AISATSU_GE,	// ドイツ語
	PMSW_AISATSU_SP,	// スペイン語

	PMSW_AISATSU_HIDE_MAX,
}PMSW_AISATSU_ID;


//--------------------------------------------------
/**
 *	難解ことばの最大数
 */
//--------------------------------------------------
enum {
	PMSW_NANKAI_WORD_MAX = 32,
};


extern PMSW_SAVEDATA* SaveData_GetPMSW( SAVEDATA* sv );

extern BOOL PMSW_GetNankaiFlag( const PMSW_SAVEDATA* saveData, u32 id );
extern u32 PMSW_SetNewNankaiWord( PMSW_SAVEDATA* saveData );
extern PMS_WORD  PMSW_NankaiWord_to_PMSWORD( u32 id );
extern BOOL PMSW_GetAisatsuFlag( const PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id );
extern BOOL PMSW_CheckNankaiWordComplete( PMSW_SAVEDATA* saveData );
extern void PMSW_SetAisatsuFlag( PMSW_SAVEDATA* saveData, PMSW_AISATSU_ID id );



// セーブデータ処理システム用
extern u32 PMSW_GetSaveDataSize(void);
extern void PMSW_InitSaveData( void* work );


#endif

