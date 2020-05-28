//=============================================================================================
/**
 * @file	fontproc.c
 * @brief	フォントデータ処理
 * @author	tetsu
 * @date	2003.03.25
 *
 *	各フォントの画像データを必要に応じてロード・アンロード出来るように修正
 *	2005.08.24	taya
 *
 *
 *	フォントタイプごとに処理関数を用意するこれまでの方法を止め、
 *	フォントデータ自体に処理に必要なパラメータを持たせて、共通の関数群で操作するようにした。
 *	2005.09.14	taya
 *
 */
//=============================================================================================
#include "common.h"

#include "gflib\msg_print.h"
#include "gflib\strbuf_family.h"
#include "system\pmfprint.h"
#include "system\fontproc.h"

#include "system\arc_util.h"
#include "system\font_arc.h"
#include "gflib\fontdata_man.h"

//---------------------------------------------------------------------------------------------
/**
 *	フォントデータロード時パラメータ（FONT_TYPEの順に並んでいる）
 */
//---------------------------------------------------------------------------------------------
//
static const struct {
	u16  arcDataIdx;	///< アーカイブ内のフォントデータインデックス
	u16  fixedFontFlag;	///< 等幅フォントフラグ
}FontDataTbl[] = {
	{ NARC_font_system_dat,  FALSE,  },
	{ NARC_font_talk_dat,    FALSE,  },
	{ NARC_font_button_dat,  FALSE,  },
	{ NARC_font_unknown_dat, FALSE,  },
};

//---------------------------------------------------------------------------------------------
/**
 *	文字作成処理データヘッダの設定（FONT_TYPEの順に並んでいる）
 */
//---------------------------------------------------------------------------------------------
static const MSG_FONT_HEADER font_header_data[] = {
	// メッセージフォント（プロポーショナル）
	{
		11, 16,			// フォントサイズ X, Y
		 0,  0, 0,		// 字間, 行間, フォントスタイル
 		 1, 15, 2		// 文字色、背景色、影色
	},
	// システムフォント（プロポーショナル）
	{
		11, 16,			// フォントサイズ X, Y
		 0,  0, 0,		// 字間, 行間, フォントスタイル
 		 1, 15, 2		// 文字色、背景色、影色
	},
	// ボタンフォント（プロポーショナル）
	{
		11, 16,			// フォントサイズ X, Y
		 0,  0, 0,		// 字間, 行間, フォントスタイル
 		 1, 15, 2		// 文字色、背景色、影色
	},
	// アンノーンフォント（プロポーショナル）
	{
		11, 16,			// フォントサイズ X, Y
		 0,  0, 0,		// 字間, 行間, フォントスタイル
 		 1, 15, 2		// 文字色、背景色、影色
	},
	{	0,0,0,0,0,0,0,0},
};


//---------------------------------------------------------------------------------------------
/**
 *	ワーク定義
 */
//---------------------------------------------------------------------------------------------
typedef struct {
	MSG_FONT_DATA     letterBitData;		///< ビットデータ１文字描画ワーク
	void*             fontData[ NELEMS(FontDataTbl) ];
	GF_FONTDATA_MAN*  fontMan[ NELEMS(FontDataTbl) ];

}FONT_PROC_WORK;

static FONT_PROC_WORK  WorkBody = {0};
static FONT_PROC_WORK* WorkPtr = NULL;

//------------------------------------------------------------------
/**
 * フォント処理モジュールの初期化
 */
//------------------------------------------------------------------
void FontProcInit( void )
{
	u32 i;

	WorkPtr = &WorkBody;

	for(i = 0; i < NELEMS(FontDataTbl); i++)
	{
		WorkPtr->fontData[i] = NULL;
		WorkPtr->fontMan[i] = NULL;
	}

	MSG_PrintSysInit(font_header_data);
}

//------------------------------------------------------------------
/**
 * フォントデータをRAM上にロードする
 *
 * @param   font		フォントタイプ
 */
//------------------------------------------------------------------
void FontProc_LoadFont( FONT_TYPE font, u32 heapID )
{
#if 0
	u32 i;
	void *fontData = NULL;

	// すでに同じフォントデータをロードしてある場合はそれを使う
	for(i = 0; i < NELEMS(FontDataTbl); i++)
	{
		if( i == font ){
			continue;
		}
		if( (FontDataTbl[i].arcDataIdx == FontDataTbl[font].arcDataIdx )
		&&	(WorkPtr->fontData[font] != NULL)
		){
			fontData = WorkPtr->fontData[font];
			break;
		}
	}

	// まだロードされていなければ新規にロード
	if( fontData == NULL )
	{
		fontData = ArcUtil_Load( ARC_FONT, FontDataTbl[font].arcDataIdx, FALSE, heapID, ALLOC_TOP );
		if(fontData != NULL)
		{
			WorkPtr->fontData[font] = fontData;
		}
		else
		{
			GF_ASSERT(0 && "フォントデータのロードに失敗\n");
			return;
		}
	}

	WorkPtr->fontMan[font] = FontDataMan_Create( fontData, FontDataTbl[font].fixedFontFlag, heapID );
#else
	WorkPtr->fontMan[font] = FontDataMan_Create( ARC_FONT, FontDataTbl[font].arcDataIdx,
								FONTDATA_LOADTYPE_READ_FILE,
//								FONTDATA_LOADTYPE_ON_MEMORY,
								FontDataTbl[font].fixedFontFlag, heapID );
#endif
}


//------------------------------------------------------------------
/**
 * フォントのビットデータをメモリに常駐させ、読み込み処理を高速化する
 *
 * @param   font			フォントID
 * @param   heapID			ビットデータ常駐用ヒープID
 *
 */
//------------------------------------------------------------------
void FontProc_LoadBitData( FONT_TYPE font, u32 heapID )
{
	GF_ASSERT( font < FONT_MAX );
	GF_ASSERT( WorkPtr->fontMan[font] );

	FontDataMan_ChangeLoadType( WorkPtr->fontMan[font], FONTDATA_LOADTYPE_ON_MEMORY, heapID );
}

//------------------------------------------------------------------
/**
 * FontProc_LoadBitData で常駐させたビットデータを破棄し、
 * 逐次ファイル読み込み方式に戻す
 *
 * @param   font			フォントID
 *
 */
//------------------------------------------------------------------
void FontProc_UnloadBitData( FONT_TYPE font )
{
	GF_ASSERT( font < FONT_MAX );
	GF_ASSERT( WorkPtr->fontMan[font] );

	FontDataMan_ChangeLoadType( WorkPtr->fontMan[font], FONTDATA_LOADTYPE_READ_FILE, 0 );
}



//------------------------------------------------------------------
/**
 * RAM上にロードされているフォントBMPをアンロードする
 *
 * @param   font		フォントタイプ
 */
//------------------------------------------------------------------
void FontProc_UnloadFont( FONT_TYPE font )
{
	GF_ASSERT( font < FONT_MAX );

	if( WorkPtr->fontData[font] != NULL )
	{
		int i;

		// 同じフォントデータを参照しているマネージャがあれば
		// 今後の管理をそいつに任せて、すぐにデータの解放はしない
		for(i = 0; i < NELEMS(FontDataTbl); i++)
		{
			if( i == font ){ continue; }
			if(	(FontDataTbl[i].arcDataIdx == FontDataTbl[font].arcDataIdx )
			&&	(WorkPtr->fontMan[i] != NULL)
			){
				WorkPtr->fontData[i] = WorkPtr->fontData[font];
				break;
			}
		}
		if( i == NELEMS(FontDataTbl) )
		{
			sys_FreeMemoryEz( WorkPtr->fontData[font] );
			WorkPtr->fontData[font] = NULL;
		}
	}

	if( WorkPtr->fontMan[font] != NULL )
	{
		FontDataMan_Delete( WorkPtr->fontMan[font] );
		WorkPtr->fontMan[font] = NULL;
	}
}
//------------------------------------------------------------------
/**
 * フォントBMPデータ１文字分をワークに読み込み、そのアドレスを渡す
 *
 * @param   font		フォントタイプ
 * @param   code		文字コード
 *
 * @retval  const MSG_FONT_DATA*		読み込み先アドレス
 */
//------------------------------------------------------------------
const MSG_FONT_DATA* FontDataGet( FONT_TYPE font, STRCODE code )
{
	FontDataMan_GetBitmap( WorkPtr->fontMan[font], code, &WorkPtr->letterBitData );
	return &(WorkPtr->letterBitData);
}
//------------------------------------------------------------------
/**
 * フォントデータをウィンドウキャラワーク領域に描画
 *
 * @param   font		フォントタイプ
 * @param   ini			BGLシステムワーク
 * @param   mdh		
 *
 */
//------------------------------------------------------------------
PRINT_RESULT FontDataPrint( FONT_TYPE font, MSG_DATA_HEADER * mdh_p )
{
	MSG_PRINT_USER * mpu_p;

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);
	if(!mpu_p->modechg_f)
	{
		mpu_p->fmode = font;
		mpu_p->modechg_f = 1;
	}
	return PokeFontPrint( mdh_p );
}

//------------------------------------------------------------------
/**
 * 文字列をビットマップ化した時の横幅取得
 *
 * @param   font		フォントタイプ
 * @param   str			文字列
 * @param   margin		字間（ドット）
 *
 * @retval  u32			横幅（ドット）
 */
//------------------------------------------------------------------
u32 FontProc_GetStrWidth( FONT_TYPE font, const STRCODE* str, u32 margin )
{
	GF_ASSERT(WorkPtr->fontMan[font] != NULL);
	return FontDataMan_GetStrWidth( WorkPtr->fontMan[font], str, margin );
}

//------------------------------------------------------------------
/**
 * 文字列をビットマップ化した時の横幅取得(STRBUF版）
 *
 * @param   font		フォントタイプ
 * @param   str			文字列
 * @param   margin		字間（ドット）
 *
 * @retval  u32			横幅（ドット）
 */
//------------------------------------------------------------------
u32 FontProc_GetPrintStrWidth( FONT_TYPE font, const STRBUF* str, u32 margin )
{
	GF_ASSERT(WorkPtr->fontMan[font] != NULL);
	return FontDataMan_GetStrWidth( WorkPtr->fontMan[font], STRBUF_GetStringCodePointer(str), margin );
}


//--------------------------------------------------------------------------------------------
/**
 * フォントデータ取得
 *
 * @param	fnt_index	フォントインデックス
 * @param	param		取得パラメータ
 *
 * @return	指定されたパラメータ
 */
//--------------------------------------------------------------------------------------------
u8 FontHeaderGet( u8 fnt_index, u8 param )
{
	u8	ret = 0;

	switch( param ){
	case FONT_HEADER_SIZE_X:	// フォントXサイズ指定
		ret = font_header_data[ fnt_index ].size_x;
		break;
	case FONT_HEADER_SIZE_Y:	// フォントYサイズ指定
		ret = font_header_data[ fnt_index ].size_y;
		break;
	case FONT_HEADER_SPACE_X:	// 文字間隔X(初期設定)
		ret = font_header_data[ fnt_index ].space_x;
		break;
	case FONT_HEADER_SPACE_Y: 	// 文字間隔Y(初期設定)
		ret = font_header_data[ fnt_index ].space_y;
		break;
	case FONT_HEADER_STYLE:		// フォントスタイル(初期設定)
		ret = font_header_data[ fnt_index ].style;
		break;
	case FONT_HEADER_F_COLOR:	// 文字色ナンバー
		ret = font_header_data[ fnt_index ].f_col;
		break;
	case FONT_HEADER_B_COLOR:	// 背景色ナンバー
		ret = font_header_data[ fnt_index ].b_col;
		break;
	case FONT_HEADER_S_COLOR:	// 影色　ナンバー
		ret = font_header_data[ fnt_index ].s_col;
		break;
	}

	return	ret;
}


//--------------------------------------------------------------------------------------------
/**
 * システムフォントパレット読み込み
 *
 * @param	type	パレット転送先タイプ
 * @param	offs	読み込みオフセット（バイト単位）
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SystemFontPaletteLoad( u32 type, u32 offs, u32 heap )
{
	ArcUtil_PalSet( ARC_FONT, NARC_font_system_ncrl, (PALTYPE)type, offs, 0x20, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 会話フォントパレット読み込み
 *
 * @param	type	パレット転送先タイプ
 * @param	offs	読み込みオフセット（バイト単位）
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkFontPaletteLoad( u32 type, u32 offs, u32 heap )
{
	ArcUtil_PalSet( ARC_FONT, NARC_font_talk_ncrl, (PALTYPE)type, offs, 0x20, heap );
}
