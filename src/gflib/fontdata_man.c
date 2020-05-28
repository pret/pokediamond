//=============================================================================================
/**
 * @file	fontdata_man.c
 * @brief	フォントデータマネージャ
 * @author	taya
 * @date	2005.09.14
 */
//=============================================================================================
#include	"common.h"
#include	"bg_system.h"
#include	"fntsys.h"
#include	"gflib\fontdata_man.h"

#include	"system\arc_tool.h"

typedef u8 (*pWidthGetFunc)(const GF_FONTDATA_MAN*, u32);
typedef void (*pGetBitmapFunc)(const GF_FONTDATA_MAN*, STRCODE, MSG_FONT_DATA* );


enum {
	SRC_CHAR_SIZE = 0x10,
	SRC_CHAR_MAX = 4,

	SRC_CHAR_MAXSIZE = SRC_CHAR_SIZE*SRC_CHAR_MAX,
};

// １文字あたりのキャラサイズ
enum {
	LETTERSIZE_1x1 = 0,
	LETTERSIZE_1x2,
	LETTERSIZE_2x1,
	LETTERSIZE_2x2,
};

//------------------------------------------------------------------
/**
 * フォントデータヘッダ
 */
//------------------------------------------------------------------
typedef struct {
	u32		bitDataOffs;	// データ先頭からフォントデータテーブルへのバイト単位オフセット
	u32		widthTblOffs;	// データ先頭から文字幅テーブルへのバイト単位オフセット（テーブルが無ければ０）
	u32		letterMax;		// 登録文字数
	u8		maxWidth;		// 最大文字幅（ドット）
	u8		maxHeight;		// 最大文字高さ（ドット）
	u8		letterCharX;	// １文字の横キャラ数
	u8		letterCharY;	// １文字の縦キャラ数
}FONTDATA_HEADER;


typedef struct {

	ARCHANDLE*    file_handle;
	u8            read_buffer[SRC_CHAR_MAXSIZE];


}FILEREAD_TYPE_WORK;

//------------------------------------------------------------------
/**
 * マネージャワーク
 */
//------------------------------------------------------------------
struct  _GF_FONTDATA_MAN	{
	FONTDATA_LOADTYPE        loadType;
	pGetBitmapFunc           GetBitmapFunc;

	u32                      charShape;
	u32                      letterCharSize;

	u8*                      fontBitData;
	u8                       readBuffer[SRC_CHAR_MAXSIZE];

	ARCHANDLE*               fileHandle;
	u32                      fileDatID;

	FONTDATA_HEADER          fontHeader;
	BOOL                     fixedFontFlag;

	pWidthGetFunc            WidthGetFunc;
	u8*                      widthTbl;
};



//==============================================================
// Prototype
//==============================================================
static void load_font_header( GF_FONTDATA_MAN* wk, u32 arcID, u32 datID, BOOL fixedFontFlag, u32 heapID );
static void unload_font_header( GF_FONTDATA_MAN* wk );
static void setup_font_datas( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID );
static void setup_type_on_memory( GF_FONTDATA_MAN* wk, u32 heapID );
static void setup_type_read_file( GF_FONTDATA_MAN* wk, u32 heapID );
static void cleanup_font_datas( GF_FONTDATA_MAN* wk );
static void cleanup_type_on_memory( GF_FONTDATA_MAN* wk );
static void cleanup_type_read_file( GF_FONTDATA_MAN* wk );
static void GetBitmapOnMemory( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );
static void GetBitmapFileRead( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );
static u8 GetWidthProportionalFont( const GF_FONTDATA_MAN* wk, u32 bcode );
static u8 GetWidthFixedFont( const GF_FONTDATA_MAN* wk, u32 bcode );



//==============================================================================================
/**
 * フォントデータマネージャ作成
 *
 * @param   arcID			フォントデータが格納されているアーカイブID
 * @param   datID			フォントデータが格納されているアーカイブ内ファイルID
 * @param   loadType		フォントデータの読み出し方式
 * @param   fixedFontFlag	TRUEなら等幅フォントとして扱う
 * @param   heapID			マネージャ作成先ヒープID
 *
 * @retval  GF_FONTDATA_MAN*	フォントデータマネージャポインタ
 *
 * @li  loadType が FONTDATA_LOADTYPE_ON_MEMORY の場合、マネージャと同じヒープ領域にフォントデータを読み込む
 */
//==============================================================================================
GF_FONTDATA_MAN* FontDataMan_Create( u32 arcID, u32 datID, FONTDATA_LOADTYPE loadType, BOOL fixedFontFlag, u32 heapID )
{
	GF_FONTDATA_MAN* wk = sys_AllocMemory( heapID, sizeof(GF_FONTDATA_MAN) );
	if( wk )
	{
		load_font_header( wk, arcID, datID, fixedFontFlag, heapID );
		setup_font_datas( wk, loadType, heapID );
	}
	return wk;
}
//==============================================================================================
/**
 * フォントデータマネージャ削除
 *
 * @param   wk		フォントデータマネージャのポインタ
 *
 */
//==============================================================================================
void FontDataMan_Delete( GF_FONTDATA_MAN* wk )
{
	cleanup_font_datas( wk );
	unload_font_header( wk );
	sys_FreeMemoryEz( wk );
}
//==============================================================================================
/**
 * フォントビットデータの読み込みタイプを変更する
 *
 * @param   wk			フォントデータマネージャポインタ
 * @param   loadType	変更後の読み込みタイプ
 *
 */
//==============================================================================================
void FontDataMan_ChangeLoadType( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID )
{
	if( wk->loadType != loadType )
	{
		cleanup_font_datas( wk );
		setup_font_datas( wk, loadType, heapID );
	}
}




//------------------------------------------------------------------
/**
 * 両タイプで共有するヘッダデータを読み込み・構築
 *
 * @param   wk				ワークポインタ
 * @param   arcID			フォントファイルのアーカイブID
 * @param   datID			フォントファイルのデータID
 * @param   fixedFontFlag	固定フォントフラグ
 * @param   heapID			ヒープID
 *
 */
//------------------------------------------------------------------
static void load_font_header( GF_FONTDATA_MAN* wk, u32 arcID, u32 datID, BOOL fixedFontFlag, u32 heapID )
{
	wk->fileHandle = ArchiveDataHandleOpen( arcID, heapID );
	if( wk->fileHandle )
	{
		ArchiveDataLoadOfsByHandle( wk->fileHandle, datID, 0, sizeof(FONTDATA_HEADER), &(wk->fontHeader) );

		wk->fixedFontFlag = fixedFontFlag;
		if( fixedFontFlag )
		{
			wk->widthTbl = NULL;
			wk->WidthGetFunc = GetWidthFixedFont;
		}
		else
		{
			GF_ASSERT(wk->fontHeader.widthTblOffs);

			wk->widthTbl = sys_AllocMemory( heapID, wk->fontHeader.letterMax );
			wk->WidthGetFunc = GetWidthProportionalFont;

			ArchiveDataLoadOfsByHandle( wk->fileHandle, datID, wk->fontHeader.widthTblOffs,
						wk->fontHeader.letterMax, (void*)(wk->widthTbl) );
		}


		{
			static const u8 charShapeTbl[2][2] = {
				{  LETTERSIZE_1x1, LETTERSIZE_1x2 },
				{  LETTERSIZE_2x1, LETTERSIZE_2x2 },
			};

			GF_ASSERT( wk->fontHeader.letterCharX <= 2 && wk->fontHeader.letterCharY <= 2 );

			wk->charShape = charShapeTbl[ wk->fontHeader.letterCharX-1 ][ wk->fontHeader.letterCharY-1 ];
			wk->letterCharSize = SRC_CHAR_SIZE * wk->fontHeader.letterCharX * wk->fontHeader.letterCharY;
		}

		wk->fileDatID = datID;
	}
}
//------------------------------------------------------------------
/**
 * 構築したヘッダデータの解放
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void unload_font_header( GF_FONTDATA_MAN* wk )
{
	if( wk->widthTbl )
	{
		sys_FreeMemoryEz( wk->widthTbl );
	}
	if( wk->fileHandle )
	{
		ArchiveDataHandleClose( wk->fileHandle );
	}
}



//------------------------------------------------------------------
/**
 * 管理するフォントデータの読み込み処理
 *
 * @param   wk				マネージャワークポインタ
 * @param   loadType		読み込みタイプ
 * @param   heapID			常駐タイプの場合、フォントビットデータ確保用ヒープの指定。
 *							ファイルリードタイプの場合、使用しない
 *
 */
//------------------------------------------------------------------
static void setup_font_datas( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID )
{
	static void (* const setup_func[])( GF_FONTDATA_MAN*, u32 ) = {
		setup_type_on_memory,
		setup_type_read_file,
	};

	wk->loadType = loadType;

	setup_func[loadType]( wk, heapID );
}
//------------------------------------------------------------------
/**
 * 管理するフォントデータの読み込み処理（ビットデータ常駐タイプ）
 *
 * @param   wk				マネージャワークポインタ
 * @param   heapID			ビットデータ領域確保用のヒープID
 */
//------------------------------------------------------------------
static void setup_type_on_memory( GF_FONTDATA_MAN* wk, u32 heapID )
{
//	void* fontData = ArcUtil_Load( arcID, datID, FALSE, heapID, ALLOC_TOP );
	u32  bit_data_size = wk->letterCharSize * wk->fontHeader.letterMax;

	wk->fontBitData = sys_AllocMemory( heapID, bit_data_size );
	wk->GetBitmapFunc = GetBitmapOnMemory;

	ArchiveDataLoadOfsByHandle( wk->fileHandle, wk->fileDatID, wk->fontHeader.bitDataOffs,
						bit_data_size, wk->fontBitData );
}
//------------------------------------------------------------------
/**
 * 管理するフォントデータの読み込み処理（ビットデータ逐次読み出しタイプ）
 *
 * @param   wk				マネージャワークポインタ
 * @param   heapID			使用しない
 */
//------------------------------------------------------------------
static void setup_type_read_file( GF_FONTDATA_MAN* wk, u32 heapID )
{
	wk->GetBitmapFunc = GetBitmapFileRead;
}

//------------------------------------------------------------------
/**
 * 読み込んだフォントデータの破棄
 *
 * @param   wk		フォントデータマネージャポインタ
 *
 */
//------------------------------------------------------------------
static void cleanup_font_datas( GF_FONTDATA_MAN* wk )
{
	static void (* const cleanup_func[])( GF_FONTDATA_MAN* ) = {
		cleanup_type_on_memory,
		cleanup_type_read_file,
	};

	cleanup_func[ wk->loadType ]( wk );
}
//------------------------------------------------------------------
/**
 * 読み込んだフォントデータの破棄（ビットデータ常駐タイプ）
 *
 * @param   wk		フォントデータマネージャポインタ
 *
 */
//------------------------------------------------------------------
static void cleanup_type_on_memory( GF_FONTDATA_MAN* wk )
{
	sys_FreeMemoryEz( wk->fontBitData );
	wk->fontBitData = NULL;
}
//------------------------------------------------------------------
/**
 * 読み込んだフォントデータの破棄（ビットデータ逐次読み込みタイプ）
 *
 * @param   wk		フォントデータマネージャポインタ
 *
 */
//------------------------------------------------------------------
static void cleanup_type_read_file( GF_FONTDATA_MAN* wk )
{
	
}



//==============================================================================================
//==============================================================================================


//==============================================================================================
/*
 *	文字ビットマップデータ取得
 *
 * @param	wk			フォントデータマネージャ
 * @param	fcode		文字コード
 * @param	dst			取得結果ワーク
 *
 */
//==============================================================================================
void FontDataMan_GetBitmap( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	if( fcode <= wk->fontHeader.letterMax )
	{
		fcode--;
		wk->GetBitmapFunc( wk, fcode, dst );
	}
	else
	{
		dst->size_x = 0;
		dst->size_y = 0;
	}
}

//------------------------------------------------------------------
/**
 * 文字ビットマップデータ取得処理（ビットデータ常駐タイプ）
 *
 * @param   wk			ワークポインタ
 * @param   fcode		文字コード
 * @param   dst			ビットデータ読み込み先バッファ
 *
 */
//------------------------------------------------------------------
static void GetBitmapOnMemory( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	u32	fdata_adrs;

	fdata_adrs = (u32)(&wk->fontBitData[fcode * wk->letterCharSize]);

	switch( wk->charShape ){
	case LETTERSIZE_1x1:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		break;
	case LETTERSIZE_1x2:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*2);
		break;
	case LETTERSIZE_2x1:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*1);
		break;
	case LETTERSIZE_2x2:
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 0,((u32)dst->data)+0x20*0);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 1,((u32)dst->data)+0x20*1);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 2,((u32)dst->data)+0x20*2);
		FntDataSet8x8_2bit(fdata_adrs + 0x10* 3,((u32)dst->data)+0x20*3);
		break;
	}

	dst->size_x = wk->WidthGetFunc( wk, fcode );
	dst->size_y = wk->fontHeader.maxHeight;
}
//------------------------------------------------------------------
/**
 * 文字ビットマップデータ取得処理（ビットデータ逐次読み込みタイプ）
 *
 * @param   wk			ワークポインタ
 * @param   fcode		文字コード
 * @param   dst			ビットデータ読み込み先バッファ
 *
 */
//------------------------------------------------------------------
static void GetBitmapFileRead( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst )
{
	u32	fdata_adrs;

	ArchiveDataLoadOfsByHandle( wk->fileHandle, wk->fileDatID, wk->fontHeader.bitDataOffs+fcode*wk->letterCharSize,
		wk->letterCharSize, (void*)(wk->readBuffer) );

	switch( wk->charShape ){
	case LETTERSIZE_1x1:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		break;
	case LETTERSIZE_1x2:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*2 );
		break;
	case LETTERSIZE_2x1:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*1 );
		break;
	case LETTERSIZE_2x2:
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*0])), ((u32)dst->data)+0x20*0 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*1])), ((u32)dst->data)+0x20*1 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*2])), ((u32)dst->data)+0x20*2 );
		FntDataSet8x8_2bit( (u32)(&(wk->readBuffer[0x10*3])), ((u32)dst->data)+0x20*3 );
		break;
	}


	dst->size_x = wk->WidthGetFunc( wk, fcode );
	dst->size_y = wk->fontHeader.maxHeight;

}

//------------------------------------------------------------------
/**
 * 文字列をビットマップ化した時の長さ（ドット）を計算して返す
 *
 * @param   wk		フォントデータマネージャ
 * @param   str		文字列
 * @param   margin	字間（ドット）
 *
 * @retval  u32		長さ
 */
//------------------------------------------------------------------
u32 FontDataMan_GetStrWidth( const GF_FONTDATA_MAN* wk, const STRCODE* str, u32 margin )
{
	u32 len = 0;
	while( *str != EOM_ )
	{
		if (*str == _CTRL_TAG )
		{
			str = STRCODE_SkipTag(str);
			if( *str == EOM_ )
			{
				break;
			}
		}
		len += (wk->WidthGetFunc( wk, (*str)-1 ) + margin);
		str++;
	}
	return len - margin;
}


//------------------------------------------------------------------
/**
 * １文字幅取得関数（プロポーショナル）
 *
 * @param   wk		
 * @param   bcode		
 *
 * @retval  u8		
 */
//------------------------------------------------------------------
static u8 GetWidthProportionalFont( const GF_FONTDATA_MAN* wk, u32 bcode )
{
	return wk->widthTbl[ bcode ];
}
//------------------------------------------------------------------
/**
 * １文字幅取得関数（等幅）
 *
 * @param   wk		
 * @param   bcode		
 *
 * @retval  u8		
 */
//------------------------------------------------------------------
static u8 GetWidthFixedFont( const GF_FONTDATA_MAN* wk, u32 bcode )
{
	return wk->fontHeader.maxWidth;
}
