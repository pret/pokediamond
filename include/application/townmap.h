/**
 *	@file	worldmap.h
 *	@brief	ワールドマップモジュール　メインヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	05.09.07
 */

#ifndef _TOWN_MAP_H_
#define _TOWN_MAP_H_


#include "field/field_common.h"
#include "field/sysflag.h"

//上位モジュールデータIO
typedef struct _TMAP_IO_DAT{
	u8	mode;	///<動作モード保存	
	int	retval;	///<Return value
}TMAP_IO_DAT;

///外部公開構造体型
///タウンマップ呼び出しモードID
typedef enum{
	TMAP_MNORMAL = 0,	///<タウンマップモード
	TMAP_MJUMP,			///<空を飛ぶ
	TMAP_MBG,			///<BG話しかけモード
	TMAP_NTENKI,		///<お天気ニュース
	TMAP_MNEWS,			///<大量発生
	TMAP_MODE_MAX = 3,		///<モード数
}TMAP_MODE;

///足跡データ構造体
typedef struct _TMAP_FOOT{
	int	x;
	int	z;
	u16	dir;
	u16	valid;
}TMAP_FOOT;
#define TMAP_FVIEW_MAX	(5)

///セーブフラグ引継ぎデータ構造体
typedef union{
	struct{
		u8	ex01_f:2;
		u8	ex01:2;
		u8	ex02_f:2;
		u8	ex02:2;
	};
	u8	flag;
}TMAP_FLAGS;
#define TMAP_BLOCK_MAX	(200)
/**
 *	@brief	到着フラグindex取得
 */
#define TMAP_ARRIVEDATA_MAX	(20)

///タウンマップパラメータ引継ぎ構造体
typedef struct {
	int player_x;	///<プレイヤーワールドグリッド座標
	int player_z;	///<プレイヤーワールドグリッド座標
	int zone_id;	///<現在のゾーンID
	int	player_sex;	///<プレイヤーの性別
	int	retval;	///<戻り値
	int	ret_x;
	int ret_z;
	int ret_zone;
	
	TMAP_FOOT	foot[TMAP_FVIEW_MAX];
	TMAP_FLAGS	flags[TMAP_BLOCK_MAX];
	u8			arrive[TMAP_ARRIVEDATA_MAX+1];	///<到着フラグ
	
	u8	mode;		///<動作モード保存	
	u8	flag_num;	///<フラグ数
	u16	view_f;	///<Viewフラグ

#ifdef PM_DEBUG
	int	debug_f;	///<デバッグmake時のみ有効なフラグ
#endif	//PM_DEBUG
}TOWNMAP_PARAM;

/**
 *	@brief	フィールド ワールドマップモジュール呼び出し
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	mode	u8:呼び出しモード(enum WMAP_MODE)
 *	@param	work	void*:ワークの引継ぎ
 *
 *	@retval	0:成功
 *	@retval else	失敗
 */
extern void FieldTMap_SetProc(FIELDSYS_WORK *fsys, TOWNMAP_PARAM * tp);

/**
 *	@brief	タウンマップモジュールへ引き継ぐパラメータをセット
 *
 *	@param	fsys	FIELDSYS_WORK型へのポインタ
 *	@param	mode	u8:モジュールの動作モード(townmap.hで定義)
 *
 *	@return	確保したTOWNMAP_PARAM型へのポインタ
 *
 *	@li	この関数内で確保されたメモリ領域は、呼び出し側モジュールで
 *		解放すること！
 */
extern TOWNMAP_PARAM* FieldTMap_SetParam(FIELDSYS_WORK *fsys,u8 mode);

/**
 *	@brief	フィールド タウンマップモジュールデータセット
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	tp	TOWNMAP_PARAM*:データを格納する構造体型へのポインタ
 *	@param	mode	u8:呼び出しモード(enum TMAP_MODE)
 */
extern void FieldTMap_CallDataSet(FIELDSYS_WORK* fsys,TOWNMAP_PARAM *tp,int mode);

///オーバーレイプロセス
extern PROC_RESULT TMapProc_Init( PROC *proc,int *seq);
extern PROC_RESULT TMapProc_Main( PROC *proc,int *seq);
extern PROC_RESULT TMapProc_End( PROC *proc,int *seq);


/**
	1,メインモジュールの初期化
	2,サブモジュールの初期化

	,メインモジュール制御
	,サブモジュール制御
	,メイン画像描画
	,サブ画像描画
	
	2,サブモジュール終了
	,メインモジュール終了
	
*/
#endif	//_TOWN_MAP_H_

