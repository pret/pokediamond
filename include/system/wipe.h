//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe.h
 *@brief	DP画面切り替えシステム
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WIPE_H__
#define __WIPE_H__

#undef GLOBAL
#ifdef	__WIPE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	画面切り替えパターン番号
//	
//=====================================
#define 	WIPE_PATTERN_WMS		(0)		// 同時
#define 	WIPE_PATTERN_FMAS		(1)		// メイン画面からサブ画面
#define 	WIPE_PATTERN_FSAM		(2)		// サブ画面からメイン画面
#define 	WIPE_PATTERN_M			(3)		// メイン画面のみ
#define 	WIPE_PATTERN_S			(4)		// サブ画面のみ

//-------------------------------------
//	
//	ワイプパターン列挙	
//	ポケモンDP/DP:企画＆仕様/画面切り替え仕様参照
//	
//=====================================
#define 	WIPE_TYPE_FADEOUT				(0)// フェードアウト	黒					ブライトネス使用
#define 	WIPE_TYPE_FADEIN				(1)// フェードイン		黒					ブライトネス使用
#define 	WIPE_TYPE_SHUTTEROUT_DOWN		(2)// シャッターアウト	上から下			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SHUTTERIN_DOWN		(3)// シャッターイン	上から下			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SHUTTEROUT_UP			(4)// シャッターアウト	下から上			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SHUTTERIN_UP			(5)// シャッターイン	下から上			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SLIDEOUT				(6)// スライドアウト	右から左			ハードウェアウィンドウ使用	
#define 	WIPE_TYPE_SLIDEIN				(7)// スライドイン		右から左			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITOUT_VSIDE		(8)// スプリットアウト	縦　画面上下から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITIN_VCENTER		(9)// スプリットイン	縦　画面中央から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITOUT_VCENTER		(10)// スプリットアウト	縦	画面中央から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITIN_VSIDE			(11)// スプリットイン	縦	画面上下から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITOUT_HSIDE		(12)// スプリットアウト	横	画面左右から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITIN_HCENTER		(13)// スプリットイン	横	画面中央から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITOUT_HCENTER		(14)// スプリットアウト	横	画面中央から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SPLITIN_HSIDE			(15)// スプリットイン	横	画面左右から	ハードウェアウィンドウ使用
#define 	WIPE_TYPE_HOLEOUT				(16)// ホールアウト							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_HOLEIN				(17)// ホールイン							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_TUNNELOUT				(18)// トンネルアウト						ハードウェアウィンドウ使用
#define 	WIPE_TYPE_TUNNELIN				(19)// トンネルイン							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_CURTAINOUT			(20)// カーテンアウト						ハードウェアウィンドウ使用
#define 	WIPE_TYPE_CURTAININ				(21)// カーテンイン							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BOXOUT_OUTSIDE		(22)// ボックスアウト	外から中			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BOXIN_INSIDE			(23)// ボックスイン		中から外			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BOXOUT_INSIDE			(24)// ボックスアウト	中から外			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BOXIN_OUTSIDE			(25)// ボックスイン		外から中			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_DOOROUT				(26)// ドアアウト							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_DOORIN				(27)// ドアイン								ハードウェアウィンドウ使用
#define 	WIPE_TYPE_ALTERNATEOUT_H		(28)// オルタネートアウト	横				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_ALTERNATEIN_H			(29)// オルタネートイン		横				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BLINDOUT_H			(30)// ブラインドアウト		横				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_BLINDIN_H				(31)// ブラインドイン		横				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SCREWOUT				(32)// スクリューアウト						ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SCREWIN				(33)// スクリューイン                       ハードウェアウィンドウ使用
#define 	WIPE_TYPE_FLASHOUT_FOREWAY		(34)// フラッシュアウト	４方向				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_FLASHIN_FOREWAY		(35)// フラッシュイン	４方向              ハードウェアウィンドウ使用
#define 	WIPE_TYPE_TUNNELOUT_TOP			(36)// トンネルアウト						ハードウェアウィンドウ使用
#define 	WIPE_TYPE_TUNNELIN_TOP			(37)// トンネルイン							ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SLIDEOUT_LR			(38)// スライドアウト　左から右 			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_SLIDEIN_LR			(39)// スライドイン	　 左から右				ハードウェアウィンドウ使用
#define 	WIPE_TYPE_PESOCOMOUT			(40)// パソコンアウト 			ハードウェアウィンドウ使用
#define 	WIPE_TYPE_PESOCOMIN				(41)// パソコンイン					ハードウェアウィンドウ使用
#define 	WIPE_TYPE_MAX					(42)// 最大数

//-------------------------------------
//	
//	フェードイン・アウトカラー
//	
//=====================================
#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1つ前のフェードアウトカラーでイン・アウト

//-------------------------------------
//	
//	メイン画面か　サブ画面か
//	
//=====================================
#define 	WIPE_DISP_MAIN		(0)		// メイン面
#define 	WIPE_DISP_SUB		(1)		// サブ面

//-------------------------------------
//	基本的に使用する分割数とシンク数
//=====================================
#define WIPE_DEF_DIV	( 6 )
#define WIPE_DEF_SYNC	( 1 )


//-------------------------------------
//	TCB　タスク優先順位
//=====================================
#define WIPE_VBLANK_WND_SWAP_TCB	( 1023 )	// ウィンドウスワップ
#define WIPE_HBLANK_INIT_TCB	( 1024 )	//Hブランク初期化
#define WIPE_HBLANK_DELETE_TCB	( 1024 )	//Hブランク破棄
#define WIPE_VBLANK_WND_DELETE_TCB	( 1025 )	// Hブランクウィンドウデータ破棄
#define WIPE_VBLANK_BR_RESET_TCB	( 1024 )	// Vブランクﾌﾞﾗｲﾄﾈｽリセット
	


//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	画面切り替えワイプを開始
 *
 *@param	pattern		切り替えパターン番号
 *@param	wipe_m		ワイプ　メイン画面ワイプパターン
 *@param	wipe_s		ワイプ　サブ画面ワイプパターン
 *@param	color		ワイプの色	
 *@param	division	各ワイプ処理の分割数	(1.2.3.4.....)
 *@param	piece_sync	各ワイプの処理を分割した１片のシンク数	(1.2.3.4.....)
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *	color
 *		ワイプの色は赤5bit 緑5bit 青5bitです。
 *		フェードイン・アウト時は黒か白しかありませんので
			#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
			#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1つ前のフェードアウトカラーでイン・アウト
		を指定してください。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_Start(int pattern, int wipe_m, int wipe_s, u16 color, int division, int piece_sync, int heap);

//----------------------------------------------------------------------------
/**
 *	@brief	画面切り替えワイプメイン関数
 *
 *	＊この関数は、system/main.cで呼ばれていますので、
 *	　呼ぶ必要はありません。
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_Main( void );

//----------------------------------------------------------------------------
/**
 *	@brief	画面切り替えワイプ　終了チェック
 *
 *	@param	none
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL WIPE_SYS_EndCheck( void );

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプの強制終了
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SYS_ExeEnd( void );

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプが画面に影響を与えているかチェック
 *
 *	@retval	TRUE	ワイプ状態クリアしている
 *	@retval	FALSE	ワイプ状態クリアされていない
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL WIPE_SYS_EffectCheck( void );

//----------------------------------------------------------------------------
/**
 *
 * ●実行された瞬間反映されます。
 *
 *	@brief	ウィンドウマスク状態を解除する
 *
 *	@param	disp	解除したい画面
 *
 *	@return
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 * ＊この関数は
 *	 ハードウェアウィンドウを使用したワイプから
 * 　ブライトネスを使用したワイプに移行する時に、
 * 　ハードウェアウィンドウの設定を解除する為に使用します。
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_ResetWndMask( int disp );

//----------------------------------------------------------------------------
/**
 *
 * ●実行された瞬間反映されます。
 *
 *	@brief	ブライトネス状態を解除
 *
 *	@param	disp	解除したい画面
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 * ＊この関数は
 *	 ブライトネスを使用したワイプから
 * 　ハードウェアウィンドウを使用したワイプに移行する時に、
 * 　ブライトネスの設定を解除する為に使用します。
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_ResetBrightness( int disp );

//----------------------------------------------------------------------------
/**
 * ●実行された瞬間反映されます。
 *
 *	@brief	ワイプ状態を解除する
 *
 *	@param	disp	解除したい画面
 *	@param	heap	使用するヒープ
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 *	どうしてもフェードインにWIPEのシステムを使用できない時、
 *	ブライトネスとウィンドウマスク状態を解除する関数です。
 * 
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_Reset( int disp );

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプブライトネス状態を設定
 *
 *	@param	disp	設定する画面
 *	@param	color	ブライトネスカラー
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
			#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1つ前のフェードアウトカラーでイン・アウト
 *
 * この関数は、どうしてもWIPEのシステムを使用できない人が、
 * フェードアウト後、マスターブライトネス値を設定するための関数です。
 *
 * パレットフェードなどを使用した後に、この関数でマスター輝度を設定し、
 * パレットフェードの解除をしてください。
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SetBrightness( int disp, u16 color );

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプウィンドウマスク状態を設定
 *
 *	@param	disp		設定する画面
 *	@param	color		カラー
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
			#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1つ前のフェードアウトカラーでイン・アウト
 *
 *	この関数は、
 *		タッチペン使用画面の場合に、フェードイン前にタッチペンを
 *		出すなど、例外処理があります。そのとき用の関数です
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void WIPE_SetWndMask( int disp, u16 color );

#endif	// __ASM_NO_DEF_

#undef	GLOBAL
#endif		// __WIPE_H__
