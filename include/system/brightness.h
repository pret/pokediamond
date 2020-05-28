#ifndef _BRIGHTNESS_H_
#define _BRIGHTNESS_H_
//#undef GLOBAL

//#ifdef BRIGHTNESS_H_GLOBAL
//#define GLOBAL	/*	*/
//#else
//#define GLOBAL	extern
//#endif	//BRIGHTNESS_H_GLOBAL

// フェードに指定する輝度
#define BRIGHTNESS_WHITE	(  16 )		// 真っ白
#define BRIGHTNESS_NORMAL	(   0 )		// 通常パレット反映状態
#define BRIGHTNESS_BLACK	( -16 )		// 真っ暗

#define	COMM_BRIGHTNESS_SYNC	( 6 )	// 基本の輝度変更Sync数


//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

// フェードにかかるLCDの設定
typedef enum{
	MASK_MAIN_DISPLAY	= 0x1,									// メイン
	MASK_SUB_DISPLAY	= 0x02,									// サブ
	MASK_DOUBLE_DISPLAY = MASK_MAIN_DISPLAY|MASK_SUB_DISPLAY,	// 両方
}BRIGHT_DISPMASK;

// フェードがかかるBG面の指定
typedef enum{
	PLANEMASK_NONE	= GX_BLEND_PLANEMASK_NONE,
	PLANEMASK_BG0	= GX_BLEND_PLANEMASK_BG0,
	PLANEMASK_BG1	= GX_BLEND_PLANEMASK_BG1,
	PLANEMASK_BG2	= GX_BLEND_PLANEMASK_BG2,
	PLANEMASK_BG3	= GX_BLEND_PLANEMASK_BG3,
	PLANEMASK_OBJ	= GX_BLEND_PLANEMASK_OBJ,
	PLANEMASK_BD	= GX_BLEND_PLANEMASK_BD,
	PLANEMASK_ALL	= GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD
}BRIGHT_PLANEMASK;

//輝度変更パラメータ
typedef struct BrightParam_tag{
	BRIGHT_PLANEMASK PlaneMask;
	BRIGHT_DISPMASK DisplayMask;
	u16 Sync;
	s16 Dst;
	s16 Src;
//	BOOL *IsFinished;
}BRIGHT_PARAM;

#if 0
//--------------------------------------------------------------------------------------------
/**
 * 輝度変更パラメータ設定
 *
 * @param	mode		メモリ取得モード
 * @param	sync		何シンクで色を変えるか
 * @param	dst			変更後の輝度
 * @param	src			初期輝度
 * @param	plane		輝度変更面マスク
 * @param	display		反映表示画面マスク
 *
 * @return	設定したデータのポインタ
 *
 * @li	AllocMemory使用
 */
//--------------------------------------------------------------------------------------------
GLOBAL BRIGHTNESS_CHG * BrightnessChgParamSet(
			int mode, const u8 sync, const s16 dst, const s16 src,
			const BRIGHT_PLANEMASK plane, const BRIGHT_DISPMASK display );

//--------------------------------------------------------------------------------------------
/**
 * 輝度変更メイン処理
 *
 * @param	dat		変更データ
 *
 * @retval	"0 = 終了"
 * @retval	"1 = 処理中"
 *
 * @li	FreeMemoryはしていない
 *
 *	BrightnessChgParamSet()を使用した場合、開放を忘れないように！
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BrightnessChgMain( BRIGHTNESS_CHG * dat );
#endif



//==============================================================================
/**
 * 輝度変更フェードリクエスト
 *
 * @param   inSync			フェードするのにかかるSync数
 * @param   inDstBright		フェード終了時の輝度（上にdefineあり)	←  こっちが終了時
 * @param   inSrcBright		フェード開始時の輝度（上にdefineあり)
 * @param   inPlaneMask		フェードが反映されるBG面（上にenumあり)
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 * @param   outFnishFlg		ポインタを指定する事でフェード終了を検知できる
 *
 * @retval  なし
 */
//==============================================================================
extern  void ChangeBrightnessRequest(
				const u8 inSync, const s16 inDstBright, const s16 inSrcBright,
				const BRIGHT_PLANEMASK inPlaneMask, const BRIGHT_DISPMASK inDisplayMask );

//==============================================================================
/**
 * 輝度変更
 *
 * @param   inDstBright		輝度（上にdefineあり)
 * @param   inPlaneMask		フェードが反映されるBG面（上にenumあり)
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
extern  void SetBrightness(	const s16 inDstBright,
					const BRIGHT_PLANEMASK inPlaneMask,
					const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * 輝度変更構造体初期化
 *
 * @param	なし
 *
 * @retval  なし
 */
//==============================================================================
extern  void BrightnessChgInit(void);

//==============================================================================
/**
 * 輝度変更構造体のリセット
 *
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
extern void BrightnessChgReset(const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * 輝度変更メイン
 *
 * @param	なし
 *
 * @retval  なし
 */
//==============================================================================
extern  void BrightnessChgMain(void);

//==============================================================================
/**
 * 輝度変更終了終了チェック
 *
 * @param	flg 調べるＬＣＤＣ
 *
 * @retval  終了有無
 */
//==============================================================================

extern  BOOL IsFinishedBrightnessChg(BRIGHT_DISPMASK flg);

#endif	__ASM_NO_DEF_

#undef GLOBAL
#endif //_BRIGHTNESS_H_
