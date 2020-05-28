//==============================================================================================
/**
 * @file	snd_test.c
 * @brief	サウンドテスト(サウンドチェック)
 * @author	nohara
 * @date	2005.07.04
 *
 * ＜サウンドテストの例外処理について＞
 *
 * １）
 * サウンドヒープを使用して、データのロードを行うようにすると、
 * 曲の再生、停止ごとに、確保、開放を行わないといけなくなります。
 *
 * これだと、BGMとSEを同時に再生することが難しいので、
 *
 * ヒープを全てクリアして、
 * PLAYER_BGMにBGMのシーケンス、バンク、波形アーカイブ分のプレイヤーヒープを確保、
 *
 * BGMはPLAYER_BGMのプレイヤーヒープで再生するようにします。
 * MEもPLAYER_BGMのプレイヤーヒープで再生するようにします。
 *
 * ２）
 * SEは、再生するたびに、シーケンス、バンク、波形アーカイブを
 * サウンドヒープでロードしなおすようにします。
 *
 * ３）
 * 上記の例外処理をしているので、
 * サウンド設定が、ゲーム内とは、全く異なります。
 * そのため、通常のサウンド初期化を通した方が、
 * 安全なので、終了処理で、ソフトリセットをかけています。
 */
//==============================================================================================
#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/lib_pack.h"
#include "system/palanm.h"
#include "system/pm_str.h"
#include "system/snd_tool.h"
#include "system/bmp_menu.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/bmp_menu.h"
#include "system/arc_util.h"
#include "snd_test.h"

#include "../system/snd_system.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "msgdata/msg_snd_test_str.h"
#include "msgdata/msg_snd_test_name.h"


//==============================================================================================
//
//	定義
//
//==============================================================================================
enum{
	BUF_BGM = 0,
	BUF_SE,
	BUF_PV,

	BUF_MAX,								//バッファの最大数
};

#define SND_TEST_BUF_SIZE		(48)		//バッファのサイズ


//==============================================================================================
//
//	構造体
//
//==============================================================================================
//サウンドテスト構造体
typedef	struct {
	BOOL end_flag;
	u8	seq;							//処理ナンバー
	s8  select;							//選択対象
	u16 dmy2;

	int	old_bgm;						//古いBGMナンバー
	int	bgm;							//BGMナンバー
	int	se;								//SEナンバー
	int	pv;								//ポケモン鳴き声ナンバー

	int bgm_lv;							//階層
	int se_lv[SE_HANDLE_MAX];			//階層
	int pv_lv;							//階層

	u8  bgm_play_flag;					//一度でも再生したかフラグ
	u8  se_play_flag[SE_HANDLE_MAX];	//一度でも再生したかフラグ
	u8  pv_play_flag;					//一度でも再生したかフラグ
	u8  dmy3;
	
	int pitch;							//音程
	int tempo;							//テンポ
	int var;							//シーケンスローカルワークにセットする値

	u16* pMsg;

	GF_BGL_INI * bgl;

	GF_BGL_BMPWIN bmpwin;				//BMPウィンドウデータ

	STRBUF* msg_buf[BUF_MAX];

	MSGDATA_MANAGER* msgman;			//メッセージマネージャー

}SND_TEST_WORK;


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
static void SndTestCall(SND_TEST_WORK * wk);

static void SndTestWorkInit( SND_TEST_WORK* wk );
static void SndTestSeqNext( SND_TEST_WORK* wk );

static void SndTestSeqInit( SND_TEST_WORK* wk );
static void SndTestSeqBgmFadeWait( SND_TEST_WORK* wk );
static void SndTestSeqKeyCheck( SND_TEST_WORK* wk );
static void SndTestSeqExit( SND_TEST_WORK* wk );

static void SndTestStop( SND_TEST_WORK* wk );
static void SndTestPlay( SND_TEST_WORK* wk );

//static void (* const SndTestTable[])() = {
static void (* const SndTestTable[])(SND_TEST_WORK*) = {
	SndTestSeqInit,						//初期化
	SndTestSeqBgmFadeWait,				//BGMフェードアウト待ち
	SndTestSeqKeyCheck,					//キーチェック
	SndTestSeqExit,						//終了
};

static void SndTestNumMsgSet( GF_BGL_BMPWIN* win, int num, u8 x, u8 y );
static void SndTestNameMsgSet( GF_BGL_BMPWIN* win, const STRBUF* msg, u8 x, u8 y );
static void MsgRewrite( SND_TEST_WORK* wk, s8 select );
static void SndTestInit( SND_TEST_WORK* wk );
static void SndTestCursor( SND_TEST_WORK* wk );
static void SndTestSysMsgSet( SND_TEST_WORK* wk );
static void SndTestStrPrint( GF_BGL_BMPWIN* win, u32 fontID, u32 strID, u32 x, u32 y, u32 wait, pStrPrintCallBack callback );
static void SndTestTrackMute( SND_TEST_WORK* wk );

//BG設定
static void SetBank();
static void BgSet( SND_TEST_WORK* wk );


//==================================================================================================
//
//	データ
//
//==================================================================================================
static const BMPWIN_DAT	SndTestWinData = {
	SND_TEST_BMPWIN_FRAME,					//ウインドウ使用フレーム
	SND_TEST_BMPWIN_PX1,SND_TEST_BMPWIN_PY1,//ウインドウ領域の左上のX,Y座標（キャラ単位で指定）
	SND_TEST_BMPWIN_SX,	SND_TEST_BMPWIN_SY,	//ウインドウ領域のX,Yサイズ（キャラ単位で指定）
	SND_TEST_BMPWIN_PL,						//ウインドウ領域のパレットナンバー	
	SND_TEST_BMPWIN_CH						//ウインドウキャラ領域の開始キャラクタナンバー
};


//==================================================================================================
//
//	関数
//
//==================================================================================================

//--------------------------------------------------------------
/**
 * @brief	サウンドテスト呼び出し
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestCall(SND_TEST_WORK * wk)
{

	if( wk == NULL ){
		OS_Printf("snd_test.c Alloc ERROR!");
		return;
	}

	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_BASE_DEBUG );

	//BG設定
	GF_Disp_GX_VisibleControlInit();	//メイン画面の各面の表示コントロール初期化
	SetBank();							//VRAMバンク設定
	BgSet(wk);							//BG設定
	GF_Disp_DispOn();					//表示有効設定
	MSG_PrintInit();					//文字表示初期化関数

	OS_Printf( "\n\n//==========================================\n" );
	OS_Printf( "//\tサウンドテスト　スタート\n" );
	OS_Printf( "//==========================================\n" );

	wk->end_flag = FALSE;
	wk->seq			= 0;									//処理ナンバー
	SndTestWorkInit(wk);									//ワーク初期化

	//メッセージデータマネージャー作成
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_snd_test_name_dat, HEAPID_BASE_DEBUG );

	//app初期化(fld_debug.c)
	//FieldBitMapWinCgxSet();
	
	//SystemFontPaletteLoad( PALTYPE_MAIN_BG, 0, HEAPID_BASE_DEBUG );

	GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin, &SndTestWinData );		//ビットマップ追加
	GF_BGL_BmpWinDataFill( &wk->bmpwin, FBMP_COL_WHITE );				//塗りつぶし

	SndTestSysMsgSet( wk );									//必要な情報メッセージ
	SndTestCursor( wk );									//カーソル更新

	//曲名メッセージ表示
	MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGMナンバー
	MsgRewrite( wk, SND_TEST_TYPE_SE );						//SEナンバー
	MsgRewrite( wk, SND_TEST_TYPE_PV );						//PVナンバー

	SndTestNumMsgSet( &wk->bmpwin, wk->pitch, ST_TYPE_X+88, ST_BGM_MSG_Y );//音程
	SndTestNumMsgSet( &wk->bmpwin, wk->tempo, ST_TYPE_X+168, ST_BGM_MSG_Y );//テンポ

	GF_BGL_BmpWinOn( &wk->bmpwin );


	return;
}

//--------------------------------------------------------------
/**
 * @brief	ワーク初期化
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestWorkInit( SND_TEST_WORK* wk )
{
	int i;

	wk->select		= SND_TEST_TYPE_BGM;		//選択対象

	wk->bgm			= SND_TEST_BGM_START_NO;	//BGMスタートナンバー
	wk->se			= SND_TEST_SE_START_NO;		//SEスタートナンバー
	wk->pv			= SND_TEST_PV_START_NO;		//ポケモン鳴き声スタートナンバー

	//初期階層
	wk->bgm_lv		= 1;			
	wk->pv_lv		= 1;		

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		wk->se_lv[i] = 1;		
	}

	//一度でも再生したかフラグ
	wk->bgm_play_flag	= 0;					
	wk->pv_play_flag	= 0;

	for( i=0; i < SE_HANDLE_MAX ;i++ ){
		wk->se_play_flag[i]	= 0;
	}

	wk->pMsg = NULL;

	wk->pitch		= 0;	//音程
	wk->tempo		= 256;	//テンポ

	// バッファ作成
	for(i=0; i<BUF_MAX; i++)
	{
		wk->msg_buf[i] = STRBUF_Create(SND_TEST_BUF_SIZE*2, HEAPID_BASE_DEBUG);
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	次の処理へ
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 *
 * 必要な処理を追加していく(サブシーケンスのクリアなど)
 */
//--------------------------------------------------------------
static void SndTestSeqNext( SND_TEST_WORK* wk)
{
	wk->seq++;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	初期化
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqInit( SND_TEST_WORK* wk )
{
	//Snd_BgmFadeOut( 60 );				//BGMフェードアウト
	Snd_Stop();							//全停止
	Snd_BgmChannelSetAndReverbSet( 0 );	//使用可能チャンネル操作、リバーブ設定(クリア)
	SndTestSeqNext(wk);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BGMフェードアウト待ち
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqBgmFadeWait( SND_TEST_WORK* wk )
{
	int ret;

	if( Snd_FadeCheck() ){						//BGMフェードアウト待ち
		return;
	}

	Snd_HeapStateClear();						//何もロードしていない状態にする(常駐も消した状態)
	
	//ベーシックバンク、波形ロード
	Snd_DebugLoadBank( BANK_BASIC );
	
	//プレイヤーヒープ作成
	ret = Snd_PlayerHeapCreate( PLAYER_BGM, 70000 );
	//Snd_UseHeapSizeOsPrint();					//追加したサウンドヒープの容量を出力する
	//OS_Printf( "player_bgm heap create = %d\n", ret );

	Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE) );	//階層保存

	SndTestSeqNext(wk);
	return;
}

//--------------------------------------------------------------
/**
 * @brief	キーチェック
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqKeyCheck( SND_TEST_WORK* wk )
{
	int ret, i, spd;

	//音程変更
	if( sys.cont & PAD_BUTTON_SELECT ){
		if( sys.repeat & PAD_KEY_UP ){
			wk->pitch++;
		}else if( sys.repeat & PAD_KEY_DOWN ){
			wk->pitch--;
		}
		SndTestNumMsgSet( &wk->bmpwin, wk->pitch, ST_TYPE_X+88, ST_BGM_MSG_Y );
		Snd_PlayerSetTrackPitch( SND_HANDLE_BGM, 0xffff, (wk->pitch*64) );
		GF_BGL_BmpWinOn( &wk->bmpwin );
		return;
	}

	//シーケンスローカルワークを変更
	if( (sys.cont & PAD_BUTTON_R) && (sys.repeat & PAD_KEY_UP) ){

		wk->var++;
		if( wk->var >= 128 ){
			wk->var = 0;
		}
		return;
	}

	if( (sys.cont & PAD_BUTTON_R) && (sys.repeat & PAD_KEY_DOWN) ){

		wk->var--;
		if( wk->var < 0 ){
			wk->var = 127;
		}
		return;
	}

	//テンポ変更
	if( sys.cont & PAD_BUTTON_START ){
		if( sys.repeat & PAD_KEY_UP ){
			wk->tempo+=32;
		}else if( sys.repeat & PAD_KEY_DOWN ){
			wk->tempo-=32;
		}
		SndTestNumMsgSet( &wk->bmpwin, wk->tempo, ST_TYPE_X+168, ST_BGM_MSG_Y );
		Snd_PlayerSetTempoRatio( SND_HANDLE_BGM, wk->tempo );
		GF_BGL_BmpWinOn( &wk->bmpwin );
		return;
	}

	//対象を変更(←BGM←PV←SE←)
	if( sys.trg & PAD_KEY_DOWN ){
		wk->select++;
		if( wk->select >= SND_TEST_TYPE_MAX ){
			wk->select = SND_TEST_TYPE_BGM;
		}

		SndTestCursor( wk );					//カーソル更新
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//対象を変更(→BGM→SE→PV→)
	if( sys.trg & PAD_KEY_UP ){
		wk->select--;
		if( wk->select < SND_TEST_TYPE_BGM ){
			wk->select = (SND_TEST_TYPE_MAX-1);
		}

		SndTestCursor( wk );					//カーソル更新
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//シーケンスナンバーを進める
	if( sys.repeat & PAD_KEY_RIGHT ){

		if( (sys.cont & PAD_BUTTON_R) || (sys.cont & PAD_BUTTON_L) ){
			spd = 10;												//10ずつ
		}else{
			spd = 1;												//1ずつ
		}

		switch( wk->select ){
		case SND_TEST_TYPE_BGM:
			wk->old_bgm = wk->bgm;
			wk->bgm+=spd;
			if( wk->bgm >= SND_TEST_BGM_END_NO ){
				wk->bgm = SND_TEST_BGM_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGMナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_SE:
			wk->se+=spd;
			if( wk->se >= SND_TEST_SE_END_NO ){
				wk->se = SND_TEST_SE_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_SE );						//SEナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_PV:
			wk->pv+=spd;
			if( wk->pv >= SND_TEST_PV_END_NO ){
				wk->pv = SND_TEST_PV_START_NO;
			}

			MsgRewrite( wk, SND_TEST_TYPE_PV );						//PVナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		};
	}

	//シーケンスナンバーを戻す
	if( sys.repeat & PAD_KEY_LEFT ){

		if( (sys.cont & PAD_BUTTON_R) || (sys.cont & PAD_BUTTON_L) ){
			spd = 10;												//10ずつ
		}else{
			spd = 1;												//1ずつ
		}

		switch( wk->select ){
		case SND_TEST_TYPE_BGM:
			wk->old_bgm = wk->bgm;
			wk->bgm-=spd;
			if( wk->bgm < SND_TEST_BGM_START_NO ){
				wk->bgm = (SND_TEST_BGM_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_BGM );					//BGMナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_SE:
			wk->se-=spd;
			if( wk->se < SND_TEST_SE_START_NO ){
				wk->se = (SND_TEST_SE_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_SE );						//SEナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		case SND_TEST_TYPE_PV:
			wk->pv-=spd;
			if( wk->pv < SND_TEST_PV_START_NO ){
				wk->pv = (SND_TEST_PV_END_NO);
			}

			MsgRewrite( wk, SND_TEST_TYPE_PV );						//PVナンバー
			GF_BGL_BmpWinOn( &wk->bmpwin );
			break;
		};
	}

	//停止
	if( sys.trg & PAD_BUTTON_B ){
		SndTestStop(wk);
	}

	//再生(停止させてから再生)
	if( sys.trg & PAD_BUTTON_A ){
		SndTestStop(wk);
		SndTestPlay(wk);

#if 1
		//シーケンスローカルワーク操作
		//サウンドハンドルが関連付けられた後に操作する！
		Snd_PlayerWriteVariable( wk->var );
		SndTestNumMsgSet( &wk->bmpwin, wk->var, ST_TYPE_X+168, ST_BGM_MSG_Y+16 );
		GF_BGL_BmpWinOn( &wk->bmpwin );
#endif

	}

	//初期化
	//if( sys.cont & PAD_BUTTON_SELECT ){
	if( sys.cont & PAD_BUTTON_Y ){
		Snd_Stop();						//全て停止
		SndTestInit( wk );				//ワーク、データなどクリア
		GF_BGL_BmpWinOn( &wk->bmpwin );
	}

	//終了
	//if( sys.cont & PAD_BUTTON_START ){
	if( sys.cont & PAD_BUTTON_X ){
		Snd_Stop();						//全て停止
		SndTestSeqNext(wk);
		return;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	終了
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSeqExit( SND_TEST_WORK* wk )
{
	int i;

	//BMPウィンドウOFF
	GF_BGL_BmpWinOff( &wk->bmpwin );
	
	//BMPリスト破棄
	//BmpListExit( wp->bmplistContID,&DebugList,&DebugCursor );
	//BmpListExit( wk->blwin, NULL, NULL );

	//BMPWindow消去
	GF_BGL_BmpWinDel( &wk->bmpwin );

	MSGMAN_Delete( wk->msgman );

	//BGL開放
	GF_BGL_BGControlExit( wk->bgl, SND_TEST_BMPWIN_FRAME );

	//bgl削除
	sys_FreeMemoryEz( wk->bgl );

	//文字バッファ削除
	for(i=0; i<BUF_MAX; i++)
	{
		if(wk->msg_buf[i]){
			STRBUF_Delete(wk->msg_buf[i]);
		}
	}

	wk->end_flag = TRUE;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンド停止処理
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestStop( SND_TEST_WORK* wk )
{
	int i,type;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		//Snd_BgmStop(Snd_NowBgmNoGet(), 0);
		//Snd_BgmStop( wk->old_bgm, 0 );
		NNS_SndPlayerStopSeqBySeqNo( wk->old_bgm, 0 );
		break;
	case SND_TEST_TYPE_SE:
		//Snd_SeStopBySeqNo( wk->se, 0 );
		Snd_SeStop( SND_HANDLE_SE_1, 0 );
		break;
	case SND_TEST_TYPE_PV:
		Snd_PMVoiceStop(0);
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンド再生処理
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestPlay( SND_TEST_WORK* wk )
{
	int type,ret;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		Snd_ArcPlayerStartSeqEx( SND_HANDLE_BGM, PLAYER_BGM, wk->bgm );
		break;

	case SND_TEST_TYPE_SE:
		//シーケンス、バンク、波形アーカイブロード(ヒープレベルは適当です)
		Snd_HeapLoadState( Snd_GetHeapSaveLv(SND_HEAP_SAVE_SE) );		//開放
		Snd_ArcLoadSeq( wk->se );										//ロード
		//Snd_HeapSaveState( Snd_GetParamAdrs(SND_W_ID_HEAP_SAVE_SE) );	//階層保存
		ret = Snd_ArcPlayerStartSeqEx( SND_HANDLE_SE_1, PLAYER_SE_1, wk->se );
		//OS_Printf( "se_play = %d\n", ret );
		break;

	case SND_TEST_TYPE_PV:
		Snd_PMVoicePlay( wk->pv );
		break;
	};

	return;
}


//==============================================================================================
//
//	設定関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	VRAMバンク設定
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SetBank(void)
{
	//display.c
	
	GF_BGL_DISPVRAM vramSetTable = {	//VRAM設定構造体
		//GX_VRAM_BG_256_AB,			//メイン2DエンジンのBG
		GX_VRAM_BG_128_C,				//メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			//メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_32_H,			//サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		//サブ2DエンジンのBG拡張パレット

		//GX_VRAM_OBJ_64_E,				//メイン2DエンジンのOBJ
		GX_VRAM_OBJ_16_F,				//メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		//メイン2DエンジンのOBJ拡張パレット

		//GX_VRAM_SUB_OBJ_NONE,			//サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJ_16_I,			//サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	//サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_01_AB,			//テクスチャイメージスロット
		//GX_VRAM_TEX_0_A,				//テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			//テクスチャパレットスロット
		//GX_VRAM_TEX_NONE,				//テクスチャイメージスロット
		//GX_VRAM_TEXPLTT_NONE			//テクスチャパレットスロット
		//GX_VRAM_TEXPLTT_0123_E		//テクスチャパレットスロット
	};

	GF_Disp_SetBank( &vramSetTable );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	BG設定
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BgSet( SND_TEST_WORK* wk )
{
	//bg_system.c
	
#if 1
	{
		GF_BGL_SYS_HEADER BGsys_data = {	//BGシステム構造体
			GX_DISPMODE_GRAPHICS,			//表示モード指定 
			GX_BGMODE_0,					//ＢＧモード指定(メインスクリーン)
			GX_BGMODE_0,					//ＢＧモード指定(サブスクリーン)
			GX_BG0_AS_2D,					//ＢＧ０の２Ｄ、３Ｄモード選択
			//GX_BG0_AS_3D,					//ＢＧ０の２Ｄ、３Ｄモード選択
		};

		//メイン、サブのグラフィックスエンジンの表示モード設定
		//メイン、サブの画面の各面の表示コントロール初期化(display.c)
		//ビットマップウィンドウ設定構造体初期化
		GF_BGL_InitBG( &BGsys_data );
	}
#endif

	{	//BMPウィンドウ
		GF_BGL_BGCNT_HEADER BmpWinBgCntData = {	//BGコントロール設定構造体
			0, 0,								//初期表示ＸＹ
			0x800,								//スクリーンバッファサイズ( 0 = 使用しない )
			0,									//スクリーンバッファオフセット

			//BG設定
			GF_BGL_SCRSIZ_256x256,				//スクリーンサイズ
			GX_BG_COLORMODE_16,					//カラーモード
			GX_BG_SCRBASE_0xd000,				//スクリーンベースブロック
			GX_BG_CHARBASE_0x00000,				//キャラクタベースブロック
			GX_BG_EXTPLTT_01,					//ＢＧ拡張パレットスロット選択

			0,									//表示プライオリティー
			0, 0,								//エリアオーバーフラグ、ダミー
			FALSE								//モザイク設定
		};

		GF_BGL_BGControlSet(wk->bgl, SND_TEST_BMPWIN_FRAME, 
							&BmpWinBgCntData, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( wk->bgl, SND_TEST_BMPWIN_FRAME );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	数字メッセージ表示
 *
 * @param	win_index	ビットマップINDEX
 * @param	num			数値
 * @param	x			表示位置X
 * @param	y			表示位置Y
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestNumMsgSet( GF_BGL_BMPWIN* win, int num, u8 x, u8 y )
{
	STRBUF* buf = STRBUF_Create( 6, HEAPID_BASE_DEBUG );

	STRBUF_SetNumber( buf, num, 4, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintSimple( win, FONT_SYSTEM, buf, x, y, MSG_NO_PUT, NULL );
	STRBUF_Delete(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	サウンドネームメッセージ表示
 *
 * @param	win_index	ビットマップINDEX
 * @param	num			数値
 * @param	x			表示位置X
 * @param	y			表示位置Y
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestNameMsgSet( GF_BGL_BMPWIN* win, const STRBUF* msg, u8 x, u8 y )
{
	GF_STR_PrintSimple( win, FONT_SYSTEM, msg, x, y, MSG_NO_PUT, NULL );
	return;
}

//------------------------------------------------------------------
/**
 * 固定文字列出力
 *
 * @param   win			BitmapWindow
 * @param   fontID		フォント
 * @param   strID		文字列ＩＤ
 * @param   x			描画Ｘ座標
 * @param   y			描画Ｙ座標
 * @param   wait		ウェイト
 * @param   callback	コールバック
 *
 */
//------------------------------------------------------------------
static void SndTestStrPrint( GF_BGL_BMPWIN* win, u32 fontID, u32 strID, u32 x, u32 y, u32 wait, pStrPrintCallBack callback )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_snd_test_str_dat, HEAPID_BASE_DEBUG );

	STRBUF* str = MSGMAN_AllocString( man, strID );

	GF_STR_PrintSimple( win, fontID, str, x, y, wait, callback );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//--------------------------------------------------------------
/**
 * @brief	BGMメッセージ再表示
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 * @param	select	選択対象
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void MsgRewrite( SND_TEST_WORK* wk, s8 select )
{
	int type;
	u32 msg_h_id;

	switch( select ){
	case SND_TEST_TYPE_BGM:
		//wk->bgm,se,pvには、シーケンスナンバーが入っているので、
		//スタートナンバーを引き、選択している値にして、
		//メッセージIDのスタートナンバーを足しメッセージを表示する
		msg_h_id = wk->bgm - SND_TEST_BGM_START_NO + msg_seq_pv_end + 1;

		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_BGM_MSG_Y+16, 8*24, 16*1 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_BGM, 
						ST_TYPE_X, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, wk->bgm, ST_TYPE_X, ST_BGM_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_BGM] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_BGM], ST_NAME_X, ST_BGM_MSG_Y+16 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_ME, 
						ST_TYPE_X+32, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_KEY, 
						ST_TYPE_X+56, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_TMP, 
						ST_TYPE_X+136, ST_BGM_MSG_Y, MSG_NO_PUT, NULL );

		break;

	case SND_TEST_TYPE_SE:
		msg_h_id = wk->se - SND_TEST_SE_START_NO + msg_seq_bgm_end + 1;

		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_SE_MSG_Y+16, 8*24, 16*1 );

		//シーケンスナンバーから、SEのプレイヤーナンバーを取得
		type = Snd_GetPlayerNo(wk->se);
		type -= PLAYER_SE_1;

		//SEのみプレイヤーナンバー表示
		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_PLAYER, 
						ST_TYPE_X+32, ST_SE_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, type, ST_TYPE_X+32+56, ST_SE_MSG_Y );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_SE, 
						ST_TYPE_X, ST_SE_MSG_Y, MSG_NO_PUT, NULL );

		SndTestNumMsgSet( &wk->bmpwin, wk->se, ST_TYPE_X, ST_SE_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_SE] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_SE], ST_NAME_X, ST_SE_MSG_Y+16 );
		break;

	case SND_TEST_TYPE_PV:
		msg_h_id = wk->pv - SND_TEST_PV_START_NO + msg_seq_pv001;

		//指定範囲を塗りつぶし
		GF_BGL_BmpWinFill( &wk->bmpwin, 
							FBMP_COL_WHITE, ST_TYPE_X, ST_PV_MSG_Y+16, 8*24, 16*1 );

		SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_PV, 
						ST_TYPE_X, ST_PV_MSG_Y, MSG_NO_PUT, NULL );
		SndTestNumMsgSet( &wk->bmpwin, wk->pv, ST_TYPE_X, ST_PV_MSG_Y+16 );

		MSGMAN_GetString( wk->msgman, msg_h_id, wk->msg_buf[BUF_PV] );
		SndTestNameMsgSet( &wk->bmpwin, wk->msg_buf[BUF_PV], ST_NAME_X, ST_PV_MSG_Y+16 );
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	初期状態にする(X_BUTTONを押した時の初期化！)
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestInit( SND_TEST_WORK* wk )
{
	//ワーク初期化
	SndTestWorkInit( wk );

	//書き直し
	MsgRewrite( wk, SND_TEST_TYPE_BGM );		//BGMナンバー
	MsgRewrite( wk, SND_TEST_TYPE_SE );			//SEナンバー
	MsgRewrite( wk, SND_TEST_TYPE_PV );			//PVナンバー

	SndTestCursor( wk );						//カーソル更新

	return;
}

//--------------------------------------------------------------
/**
 * @brief	カーソル
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestCursor( SND_TEST_WORK* wk )
{
	u16 y;

	switch( wk->select ){
	case SND_TEST_TYPE_BGM:
		y = ST_BGM_MSG_Y;
		break;
	case SND_TEST_TYPE_SE:
		y = ST_SE_MSG_Y;
		break;
	case SND_TEST_TYPE_PV:
		y = ST_PV_MSG_Y;
		break;
	};

	//指定範囲を塗りつぶし
	GF_BGL_BmpWinFill( &wk->bmpwin, 
						FBMP_COL_WHITE, ST_CURSOR_X, ST_BGM_MSG_Y, 8*1, 16*8 );
	GF_BGL_BmpWinFill( &wk->bmpwin, 
						FBMP_COL_RED, ST_CURSOR_X, y, 8*1, 16*1 );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	システムメッセージ
 *
 * @param	wk		SND_TEST_WORKへのポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void SndTestSysMsgSet( SND_TEST_WORK* wk )
{
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_SOUND_TEST, 
				ST_TITLE_X, ST_TITLE_Y, MSG_NO_PUT, NULL );			//SOUND TEST
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_A_PLAY, 
				ST_KEY_X, ST_KEY_Y, MSG_NO_PUT, NULL );				//A PLAY
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_B_STOP, 
				ST_KEY_X+64, ST_KEY_Y, MSG_NO_PUT, NULL );			//B STOP
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_X_END, 
				ST_KEY_X, ST_KEY_Y+16, MSG_NO_PUT, NULL );			//X END
	SndTestStrPrint( &wk->bmpwin, FONT_SYSTEM, msg_Y_INIT, 
				ST_KEY_X+64, ST_KEY_Y+16, MSG_NO_PUT, NULL );		//Y INIT

	return;
}


//==============================================================================================
//
//	PROC関連
//
//==============================================================================================

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_Init(PROC * proc, int * seq)
{
	SND_TEST_WORK* wk = NULL;

	wk = PROC_AllocWork(proc, sizeof(SND_TEST_WORK), HEAPID_BASE_DEBUG);
	memset( wk, 0, sizeof(SND_TEST_WORK) );

	SndTestCall(wk);
	return PROC_RES_FINISH;
		
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_Main(PROC * proc, int * seq)
{
	SND_TEST_WORK *swk;
	swk = PROC_GetWork(proc);

	SndTestTable[swk->seq](swk);

	if (swk->end_flag) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT SoundTestProc_End(PROC * proc, int * seq)
{
	PROC_FreeWork(proc);
	//Main_SetNextProc(NO_OVERLAY_ID, &TitleProcData);

	//ソフトリセット
	//詳細はソース先頭の「サウンドテストの例外処理について」を参照して下さい
	//OS_InitReset();
	OS_ResetSystem(0);									//ソフトリセット
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
const PROC_DATA SoundTestProcData = {
	SoundTestProc_Init,
	SoundTestProc_Main,
	SoundTestProc_End,
	NO_OVERLAY_ID
};


