//=========================================================================
//	
//	pmfprint.h
//
//=========================================================================
#ifndef _PMFPRINT_H_
#define _PMFPRINT_H_


#undef GLOBAL
#ifdef __PMFPRINT_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#undef GLOBAL_WORK
#ifdef __PMFRINT_H_GLOBAL__
#define GLOBAL_WORK //
#else
#define GLOBAL_WORK extern
#endif

//=========================================================================
//	定義
//=========================================================================
#define	MSG_SKIP_OFF	(0)
#define	MSG_SKIP_ON		(1)

#define	CURSOR_FIELD	(0)
#define	CURSOR_BATTLE	(1)

#define	MSG_AUTO_OFF		(0)
#define	MSG_AUTO_ON			(1)
#define	MSG_AUTO_SKIP_ON	(3)

#define	MSG_TP_OFF		(0)
#define	MSG_TP_ON		(1)

#define MSGSPEED_FIX_OFF	(0)
#define MSGSPEED_FIX_ON		(1)

//メッセージ表示ウェイト定義
#define AUTO_MSGWAIT	(3)		//(1)
#define AUTO_MSGTRGWAIT	(100)	//(96)	//(49)	//(120)

///表示文字列設定構造体
typedef struct {
u8		fmode:4;	//文字の大きさ
u8		skip_f:1;	//スキップ判定フラグ
u8		dummy:3;

u8		cur_wait:5;	//トリガー待ちカーソルウェイトワーク
u8		cur_anm:2;	//トリガー待ちカーソルアニメワーク
u8		modechg_f:1;//文字大きさ変更フラグ

u8		rep_wait:8;	//リプレイ中ウェイトワーク
}MSG_PRINT_USER;

///表示設定
typedef struct {
u8		skip_f:1;		//スキップ判定フラグ
u8		cursor_type:1;	//カーソルパターン
u8		auto_f:1;		//カーソル自動送り
u8		speed_fix:1;	//メッセージ速度一定 add by matsuda 2004.03.09(火)
u8		tp_f:1;			//タッチパネル送り
u8		auto_f_skip:1;	//カーソル自動送り中のキー送り判定フラグ

u8		btl_skip_f:1;	//戦闘用：スキップ中か
u8		btl_wait_f:1;	//戦闘用：▼を送ったか

}MSG_PRINT_MODE;



GLOBAL_WORK MSG_PRINT_MODE msg_print_flag;



GLOBAL void PokeFontTrgCursorCgxSet( u16 cgx );

//--------------------------------------------------------------------------------------------
/**
 * スキップ設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_SKIP_OFF : スキップ無効
 *	flg = MSG_SKIP_ON  : スキップ有効
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MsgPrintSkipFlagSet( int flg );

//--------------------------------------------------------------------------------------------
/**
 * 自動送り設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_AUTO_OFF : 自動送り無効
 *	flg = MSG_AUTO_ON  : 自動送り有効
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MsgPrintAutoFlagSet( int flg );

//--------------------------------------------------------------------------------------------
/**
 * タッチパネル送り設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_TP_OFF : タッチパネル無効
 *	flg = MSG_TP_ON  : タッチパネル有効
 */
//--------------------------------------------------------------------------------------------
GLOBAL void MsgPrintTouchPanelFlagSet( int flg );




GLOBAL u8 MsgPrintBattleSkipPushFlagGet(void);
GLOBAL void MsgPrintBattleSkipPushFlagClear(void);
GLOBAL u8 MsgPrintBattleWaitPushFlagGet(void);
GLOBAL void MsgPrintBattleWaitPushFlagClear(void);


//=============================================================================================
/**
 *		トリガー待ちカーソル表示
 */
//=============================================================================================
GLOBAL void	PokeFontTriggerCursorAnimeInit(MSG_DATA_HEADER* mdh_p);

GLOBAL void	PokeFontTriggerCursorAnime2( MSG_DATA_HEADER* mdh_p);
GLOBAL void PokeFontTriggerCursorAnimeExit2( MSG_DATA_HEADER* mdh_p );

GLOBAL BOOL PokeFontTriggerWaitReplayCheck(MSG_DATA_HEADER* mdh_p);

GLOBAL BOOL PokeFontTriggerWait( MSG_DATA_HEADER* mdh_p );

GLOBAL BOOL PokeFontTriggerWait2(MSG_DATA_HEADER* mdh_p);

//=============================================================================================
/**
 *		トリガー待ちカーソル表示(外部制御)
 *		u8 win_index			:表示ビットマップＩＮＤＥＸ
 *		u16 x,u16 y,			:表示ビットマップ内座標
 *		u8 b_col,				:表示ビットマップ背景色
 *		u8 mode,				:０：カーソル制御、１：カーソル消去
 *		u8* wait,u8* anime		:関数使用ワークポインタ（書き込み可指定）
 */
//=============================================================================================
enum{
	MSG_TRG_CURSOR_PUT = 0,
	MSG_TRG_CURSOR_CLS,
};
GLOBAL void	MsgTriggerCursorAnime(u8 win_index,u16 x,u16 y,u8 b_col,u8 mode,u8* wait,u8* anime);










//--------------------------------------------------------------------------------------
/**
 * 文字列の描画に必要な幅（ドット数）を計算
 *
 * @param   fnt_index		フォントインデックス
 * @param   str				文字列
 * @param   spc				文字ごとの間隔（== SPACE_DEFAULTを指定でデフォルト値）
 *
 * @retval  u32			描画に必要な幅（ドット）
 *
 * I_MSG_, S_MSG_, C_FCHG_ に対応。
 * CR_を含む複数行の場合、最も大きい行の幅を返す。
 *
 */
//--------------------------------------------------------------------------------------
#define SPACE_DEFAULT  (-1)
GLOBAL u32 PokeStrWidthGet(u8 fnt_index, const u8* str, s16 spc);

//--------------------------------------------------------------
/**
 * @brief   文字データ取得(→戦闘ウインドウＯＢＪ用)※特殊コードは無視
 *
 * @param	buf			フォントデータ格納バッファポインタ
 * @param	fnt_index	フォント指定コード
 * @param	msg			メッセージデータポインタ
 */
//--------------------------------------------------------------
GLOBAL u16 PokeFontPrintFontData(void* buf,u8 fnt_index,const void* msg);



//------------------------------------------------------------------
/**
 *	文字BITMAPデータ取得
 *
 * @param	ini			BGLデータ
 * @param	mdh_p		メッセージデータ構造体ポインタ
 *
 * @retval	w_flag		文字取得パラメータ
 */
//------------------------------------------------------------------
GLOBAL PRINT_RESULT PokeFontPrint( MSG_DATA_HEADER * mdh_p );

#undef GLOBAL


#endif
