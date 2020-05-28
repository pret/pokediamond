//============================================================================================
/**
 * @file	sxy.h
 * @brief	イベント関連処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.30
 */
//============================================================================================
#ifndef SXY_H
#define SXY_H
#undef GLOBAL
#ifdef SXY_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
#define	EVENT_ID_NONE	( 0xffff )		///<イベントデータなし

// BG話しかけイベントタイプ
enum {
	BG_TALK_TYPE_NORMAL = 0,	// ノーマル
	BG_TALK_TYPE_BOARD,			// 看板
	BG_TALK_TYPE_HIDE,			// 隠しアイテム
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 会話キャラOBJ取得
 *
 * @param	repw	フィールドデータ
 * @param	obj		キャラデータ格納場所
 *
 * @retval	"TRUE = キャラがいる"
 * @retval	"FALSE = キャラがいない"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 TalkObjEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );

//--------------------------------------------------------------------------------------------
/**
 * BG話しかけイベントのID取得
 *
 * @param	repw	フィールドデータ
 * @param	data	BG話しかけデータ
 * @param	size	BG話しかけデータ数
 *
 * @retval	"EVENT_ID_NONE = データなし"
 * @retvel	"EVENT_ID_NONE != BGデータのID"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 TalkBgEventCheck( FIELDSYS_WORK * repw, void * data, int size );

GLOBAL u16 TalkAutoBgBoardEventCheck( FIELDSYS_WORK * repw, void * data, int size );
GLOBAL u8 TalkAutoObjBoardEventCheck( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );


//--------------------------------------------------------------------------------------------
/**
 * POSイベントID取得
 *
 * @param	repw	フィールドデータ
 * @param	data	POSイベントデータ
 * @param	size	POSイベントデータ数
 *
 * @retval	"EVENT_ID_NONE = データなし"
 * @retvel	"EVENT_ID_NONE != POSイベントデータのID"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 PosEventCheck( FIELDSYS_WORK * repw, void * data, int size );

//--------------------------------------------------------------------------------------------
/**
 * @brief	目の前のOBJをサーチ
 * @param	repw	フィールドデータ
 * @param	obj		キャラデータ格納場所
 *
 * 存在しないときNULLが返る
 */
//--------------------------------------------------------------------------------------------
extern void SXY_HeroFrontObjGet( FIELDSYS_WORK * repw, FIELD_OBJ_PTR * obj );

#undef	GLOBAL
#endif	/* SXY_H */
