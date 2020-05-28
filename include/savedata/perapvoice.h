//============================================================================================
/**
 * @file	perapvoice.h
 * @brief	ぺラップ声データ用ヘッダ
 * @date	2006.04.06
 */
//============================================================================================

#ifndef	__PERAPVOICE_H__
#define	__PERAPVOICE_H__


//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
/**
 * @brief	ぺラップ声データへの不完全型定義
 */
//---------------------------------------------------------------------------
typedef struct PERAPVOICE PERAPVOICE;

//---------------------------------------------------------------------------
/**
 * @brief		記録する声データの大きさ
 */
//---------------------------------------------------------------------------
#define	PERAPVOICE_LENGTH		(1000)

#define PERAPVOICE_DATA_LENGTH	(PERAPVOICE_LENGTH+4)

//============================================================================================
//============================================================================================
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern PERAPVOICE * SaveData_GetPerapVoice(SAVEDATA * sv);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern void PERAPVOICE_Init(PERAPVOICE * pv);
extern int PERAPVOICE_GetWorkSize(void);
extern PERAPVOICE * PERAPVOICE_AllocWork(int heapID);

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern BOOL PERAPVOICE_GetExistFlag(const PERAPVOICE * pv);
extern void PERAPVOICE_ClearExistFlag( PERAPVOICE * pv );
extern void PERAPVOICE_SetVoiceData(PERAPVOICE * pv, const s8 * src);
extern void PERAPVOICE_CopyData(PERAPVOICE * des, const PERAPVOICE * src);
extern const void * PERAPVOICE_GetVoiceData(const PERAPVOICE * pv);
extern void PERAPVOICE_ExpandVoiceData( s8 *des, const s8 *src );

#endif	__PERAPVOICE_H__
