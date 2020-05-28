//============================================================================================
/**
 * @file	app_tool.c
 * @brief	ツール関連
 * @author	Hiroyuki Nakamura
 * @date	05.09.28
 *
 *	適当に追加して下さい
 */
//============================================================================================
#include "common.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/brightness.h"
#include "system/wipe.h"

#define	APP_TOOL_H_GLOBAL
#include "application/app_tool.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	BRIGHT_SYNC			( COMM_BRIGHTNESS_SYNC )	// 輝度変更Sync数
#define	BRIGHT_IN_END		( 0 )						// 輝度変更終了値（暗→明）
#define	BRIGHT_IN_START		( -16 )						// 輝度変更開始値（暗→明）
#define	BRIGHT_OUT_END		( -16 )						// 輝度変更終了値（明→暗）
#define	BRIGHT_OUT_START	( 0 )						// 輝度変更開始値（明→暗）


//==============================================================================
//	データ
//==============================================================================
///OAMタイプのデータサイズテーブル
ALIGN4 static const u16 OamTypeSizeTbl[] = {
	OBJSIZE_8x8,		//OAMTYPE_8x8	
	OBJSIZE_16x16,		//OAMTYPE_16x16
	OBJSIZE_32x32,		//OAMTYPE_32x32
	OBJSIZE_64x64,		//OAMTYPE_64x64
	OBJSIZE_16x8,		//OAMTYPE_16x8
	OBJSIZE_32x8,		//OAMTYPE_32x8
	OBJSIZE_32x16,		//OAMTYPE_32x16
	OBJSIZE_64x32,		//OAMTYPE_64x32
	OBJSIZE_8x16,		//OAMTYPE_8x16
	OBJSIZE_8x32,		//OAMTYPE_8x32
	OBJSIZE_16x32,		//OAMTYPE_16x32
	OBJSIZE_32x64,		//OAMTYPE_32x64
};



//--------------------------------------------------------------
/**
 * @brief   OAMタイプからOAMのデータサイズを取得する
 * @param   oam_type		OAMタイプ
 * @retval  データサイズ(Byte単位)
 */
//--------------------------------------------------------------
int APP_OamTypeToSize(int oam_type)
{
	oam_type -= OAMTYPE_8x8;	//OAMTYPE_8x8が0で始まっていない場合を考えて一応
	return OamTypeSizeTbl[oam_type];
}


//--------------------------------------------------------------
/**
 * @brief   直線距離を求めます
 *
 * @param   x		Xの距離
 * @param   y		Yの距離
 *
 * @retval  int		直線距離
 *
 * 座標(0,0)を始点として、(x,y)までの直線距離を計算します
 */
//--------------------------------------------------------------
u32 APP_StraightDistance(u32 x, u32 y)
{
	u32 temp;
	
	temp = (x * x) + (y * y);
	temp = SVC_Sqrt(temp << 4);
	return (temp >> 2);
}



//--------------------------------------------------------------------------------------------
/**
 * 現在値のゲージドット数を取得
 *
 * @param	prm_now		現在値
 * @param	prm_max		最大値
 * @param	dot_max		最大ドット数
 *
 * @return	ドット数
 */
//--------------------------------------------------------------------------------------------
u8 GetNumDotto( u32 prm_now, u32 prm_max, u8 dot_max )
{
	u8 put_dot;
	
	put_dot = prm_now * dot_max / prm_max;
	if( put_dot == 0 && prm_now > 0 ){	// ﾄﾞｯﾄ計算では0でも実際の値が1以上なら1ﾄﾞｯﾄにする
		put_dot = 1;
	}
	return put_dot;
}

//--------------------------------------------------------------
/**
 * @brief   表示ドットと最大ドットからHPゲージの色を取得する
 *
 * @param   put_dot		表示ドット数
 * @param   max_dot		最大ドット数
 *
 * @retval  ゲージカラー
 */
//--------------------------------------------------------------
u8 GetGaugeDottoColor(u32 put_dot, u32 max_dot)
{
	put_dot <<= 8;		//割り算使用の為、小数レベルまで見れるように固定小数化
	max_dot <<= 8;
	
	if( put_dot > (max_dot/2) ){
		return HP_DOTTO_GREEN;		// 緑
	}else if( put_dot > (max_dot/5) ){
		return HP_DOTTO_YELLOW;		// 黄
	}else if( put_dot > 0 ){
		return HP_DOTTO_RED;		// 赤
	}
	return HP_DOTTO_NULL;			// HP=0
}

//--------------------------------------------------------------------------------------------
/**
 * HPゲージのカラーを取得
 *
 * @param	hp			現在のHP
 * @param	mhp			最大HP
 * @param	max_dot		最大ドット数
 *
 * @return	ゲージカラー
 */
//--------------------------------------------------------------------------------------------
u8 GetHPGaugeDottoColor( u16 hp, u16 mhp, u32 max_dot )
{
	u32 put_dot;
	
	if( hp == mhp ){ return HP_DOTTO_MAX; }
	
	put_dot = GetNumDotto( hp, mhp, max_dot );

	return GetGaugeDottoColor(put_dot, max_dot);
}



//--------------------------------------------------------------------------------------------
/**
 * 輝度変更リクエスト
 *
 * @param	req		リクエストID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void APP_BrightnessReq( u8 req )
{
	if( req == APP_BRIGHT_IN ){
		ChangeBrightnessRequest(
			BRIGHT_SYNC, BRIGHT_IN_END, BRIGHT_IN_START, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );


	}else{
		ChangeBrightnessRequest(
			BRIGHT_SYNC, BRIGHT_OUT_END, BRIGHT_OUT_START, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ワイプシステムによるフェードリクエスト
 *
 * @param	req			リクエストID
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void APP_WipeStart( u8 req, u32 heap )
{
	if( req == APP_WIPE_IN ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, heap );
	}else{
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, heap );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * 個数変更
 *
 * @param	num		個数
 * @param	max		最大値
 *
 * @retval	"APP_NUMSEL_NONE = ±０"
 * @retval	"APP_NUMSEL_UP = ＋"
 * @retval	"APP_NUMSEL_DOWN = －"
 */
//--------------------------------------------------------------------------------------------
u8 NumSelectCheck( s16 * num, u16 max )
{
	s16	tmp;

	tmp = *num;

	if( sys.repeat & PAD_KEY_UP ){
		*num += 1;
		if( *num > max ){ *num = 1; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_UP;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		*num -= 1;
		if( *num <= 0 ){ *num = max; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_DOWN;
	}
	if( sys.repeat & PAD_KEY_LEFT ){
		*num -= 10;
		if( *num <= 0 ){ *num = 1; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_DOWN;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		*num += 10;
		if( *num > max ){ *num = max; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_UP;
	}

	return APP_NUMSEL_NONE;
}


///06.03.11 add iwasawa
///////////////////////////////////////////////////////////////////////

/**
 *	@brief	アーカイブハンドル・ファイルidx等を引数に、
 *			指定フレームのデータをVRAMへ転送する
 *
 *	@param	bgl		初期済みのBGLデータ
 *	@param	heapID	テンポラリ作成に使うヒープハンドル
 *	@param	handel	オープン済みのアーカイブファイルハンドル
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	アーカイブ内データID
 *	@param	frame	データ転送GF_BGL_FRAME_***指定
 *	@param	mode	0:キャラ,1:スクリーン,2:パレット
 *	@param	size	転送サイズ指定(0を指定した場合、ファイルサイズ分)
 *	@param	ofs		転送オフセット指定
 */
void APP_ArcFileVramLoad(GF_BGL_INI* bgl,int heapID,
		ARCHANDLE* handle,int arcID,int fileID,int frame,int mode,u16 trans_siz,u16 ofs)
{
	u32	size;
	void* pSrc;
	NNSG2dCharacterData* pChar;
	NNSG2dScreenData* pScrn;	
	NNSG2dPaletteData*	pPal;
	
	size = ArchiveDataSizeGet(arcID,fileID);
	pSrc = sys_AllocMemoryLo(heapID,size);
	ArchiveDataLoadByHandle(handle,fileID,(void*)pSrc);

	switch(mode){
	case 0:	//キャラクタ
		NNS_G2dGetUnpackedCharacterData(pSrc,&pChar); 
		if(trans_siz == 0){
			trans_siz = pChar->szByte;
		}
		OS_Printf("GF_BGL_CharSet size = %08x\n",trans_siz);
		GF_BGL_LoadCharacter(bgl,frame,
				pChar->pRawData,trans_siz,ofs);
		break;
	case 1:
		NNS_G2dGetUnpackedScreenData(pSrc,&pScrn);
		if(trans_siz == 0){
			trans_siz = pScrn->szByte;
		}

		if(GF_BGL_ScreenAdrsGet( bgl,frame) != NULL){
			GF_BGL_ScreenBufSet( bgl, frame, pScrn->rawData, trans_siz );
		}
		OS_Printf("GF_BGL_ScrnSet size = %08x\n",trans_siz);
		GF_BGL_LoadScreen( bgl, frame, pScrn->rawData, trans_siz, ofs );
		break;
	case 2:
		NNS_G2dGetUnpackedPaletteData(pSrc,&pPal);
		if(trans_siz == 0){
			trans_siz = pPal->szByte;
		}
		OS_Printf("GF_BGL_PalSet size = %08x\n",trans_siz);
		GF_BGL_PaletteSet(frame,pPal->pRawData,trans_siz,ofs);
	}
	sys_FreeMemoryEz(pSrc);
}

/**
 *	@brief	オープン済みのアーカイブファイルハンドルを渡して
 *			アーカイブ内のスクリーンデータをUnpackして取得する
 *
 *	@param	handel	オープン済みのアーカイブファイルハンドル
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	アーカイブ内データID
 *	@param	heapID	メモリ確保するヒープハンドル
 *
 *	@return void*	確保したデータ領域の先頭ポインタ
 *	
 *	＊Unpackするだけなので、解放は自分でやること！
 */
void* APP_ArcScrFileUnpack(ARCHANDLE* handle,
	int arcID,int fileID,NNSG2dScreenData** pDat,int heapID)
{
	int size;
	void* pBuf;
	
	size = ArchiveDataSizeGet(arcID,fileID);
	pBuf = sys_AllocMemory(heapID,size);
	ArchiveDataLoadByHandle(handle,fileID,pBuf);
	NNS_G2dGetUnpackedScreenData(pBuf,pDat);

	return pBuf;
}

