//============================================================================================
/**
 * @file	poketch_v_tool.c
 * @bfief	ポケッチ　描画コマンド関連の共通処理
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"
#include "field\poketch.h"

#include "poketch_prv.h"
#include "poketch_view.h"


//===========================================================
// 描画コマンドワーク（外部に構造は非公開）
//===========================================================
struct _POKETCH_CMD_WORK {
	u32       cmd;		// コマンドナンバーを保存（書き換え不可）
	u32       seq;		// コマンド内部のシーケンスとして使う
	void      *vwk;		// 描画モジュールワークへのポインタ
	void      *wk;		// 独自ワークへのポインタ
	const void *vpara;	// 描画パラメータ構造体へのポインタ
	TCB_PTR   tcb;
};
//===========================================================
// 定数
//===========================================================
#define STORE_MAGIC_NUMBER	(0x12345678)

//==============================================================
// Prototype
//==============================================================
static BOOL StoreCmd(POKETCH_CMD_STORE *store, u32 cmd);
static void DeleteCmd(POKETCH_CMD_STORE *store, u32 cmd);


//------------------------------------------------------------------
/**
 * 稼働中コマンドの保存テーブルを初期化
 *
 * @param   store		保存テーブルアドレス
 * @param   max			保存テーブル要素数（ヘッダを除く）
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_CmdStoreInit(POKETCH_CMD_STORE *store, u32 max)
{
	u32 i;

	store[CMD_STOREWK_MAX] = max;
	store[CMD_STOREWK_MAGICNUMBER] = STORE_MAGIC_NUMBER;


	for(i = 0; i < max; i++)
	{
		store[ CMD_STORE_HEADER_SIZE + i ] = CMD_NULL;
	}
}
//------------------------------------------------------------------
/**
 * 稼働中コマンドをテーブルに保存
 *
 * @param   store		保存テーブルアドレス
 * @param   cmd			コマンドナンバー
 *
 */
//------------------------------------------------------------------
static BOOL StoreCmd(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	GF_ASSERT( store[CMD_STOREWK_MAGICNUMBER] == STORE_MAGIC_NUMBER );

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == CMD_NULL)
		{
			store[ CMD_STORE_HEADER_SIZE + i] = cmd;
			return TRUE;
		}
	}
	OS_TPrintf("コマンドいっぱいよ\n");
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 稼働中コマンド削除
 *
 * @param   store		
 * @param   cmd			
 *
 */
//------------------------------------------------------------------
static void DeleteCmd(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	GF_ASSERT( store[CMD_STOREWK_MAGICNUMBER] == STORE_MAGIC_NUMBER );

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == cmd)
		{
			store[ CMD_STORE_HEADER_SIZE + i] = CMD_NULL;
			return;
		}
	}

	GF_ASSERT(0);

}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単独）
 *
 * @param   store		稼働中コマンドを保存してあるテーブル
 * @param   cmd			コマンドナンバー
 *
 * @retval  BOOL		TRUEで終了／FALSEで継続中
 */
//------------------------------------------------------------------
BOOL PoketchViewTool_WaitCommand(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == cmd)
		{
			return FALSE;
		}
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @param   store		稼働中コマンドを保存してあるテーブル
 *
 * @retval  BOOL		TRUEで終了／FALSEで継続中
 */
//------------------------------------------------------------------
BOOL PoketchViewTool_WaitCommandAll(POKETCH_CMD_STORE *store)
{
	u32 i;

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] != CMD_NULL)
		{
			return FALSE;
		}
	}
	return TRUE;
}


//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd_tbl		コマンドテーブル配列
 * @param   cmd			コマンドナンバー
 * @param   view_wk		描画モジュールのワークアドレス
 * @param   store		稼働中の描画コマンドナンバーを保存しとく配列
 * @param   taskpri		コマンドを実行するタスクプライオリティ
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetCommand(const POKETCH_VIEW_CMD *cmd_tbl, u32 cmd, void *view_wk,
		const void *vpara, POKETCH_CMD_STORE *store, u32 taskpri, u32 heapID)
{
	u32 i;

	for(i = 0; cmd_tbl[i].cmd != CMD_NULL; i++)
	{
		if(cmd_tbl[i].cmd == cmd)
		{
			POKETCH_CMD_WORK *cwk;
			u32 work_size;

			work_size = sizeof(POKETCH_CMD_WORK) + cmd_tbl[i].work_size;
			cwk = sys_AllocMemory( heapID, work_size );

			if(cwk != NULL)
			{
				// コマンド独自ワークは、必要なら共通ワークの後に続けて確保してある
				if( cmd_tbl[i].work_size != 0)
				{
					cwk->wk = ((u8*)cwk) + sizeof(POKETCH_CMD_WORK);
				}
				else
				{
					cwk->wk = NULL;
				}

				if( StoreCmd( store, cmd ) )
				{
					cwk->vwk = view_wk;
					cwk->seq = 0;
					cwk->cmd = cmd;
					cwk->vpara = vpara;

					cwk->tcb = TCB_Add( cmd_tbl[i].func, cwk, taskpri);
					if( cwk->tcb )
					{
						cmd_tbl[i].func( cwk->tcb, cwk );
					}
				}
				else
				{
					sys_FreeMemoryEz( cwk );
				}
				return;
			}
			else
			{
				GF_ASSERT(0);
				break;
			}
		}
	}

	GF_ASSERT(0);
}
//------------------------------------------------------------------
/**
 * 描画コマンド削除
 *
 * @param   store			稼働中コマンド保存テーブル
 * @param   cmd_work		コマンドワーク
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_DelCommand(POKETCH_CMD_STORE *store, POKETCH_CMD_WORK *cwk)
{
	DeleteCmd(store, cwk->cmd);
	TCB_Delete(cwk->tcb);
	sys_FreeMemoryEz( cwk );
}


//------------------------------------------------------------------
/**
 * コマンドワークから描画モジュールワークアドレスを返す
 *
 * @param   cwk			コマンドワーク
 *
 * @retval  void*		描画モジュールワークアドレス
 */
//------------------------------------------------------------------
void* PoketchViewTool_GetViewWork(POKETCH_CMD_WORK *cwk)
{
	return cwk->vwk;
}

//------------------------------------------------------------------
/**
 * コマンドワークから描画パラメータアドレスを返す
 *
 * @param   cwk				コマンドワーク
 *
 * @retval  const void*		描画パラメータアドレス
 */
//------------------------------------------------------------------
const void* PoketchViewTool_GetViewParam(POKETCH_CMD_WORK *cwk)
{
	return cwk->vpara;
}

//------------------------------------------------------------------
/**
 * コマンドワークからコマンド独自ワークアドレスを返す
 *
 * @param   cwk			コマンドワーク
 *
 * @retval  void*		コマンド独自ワークアドレス
 */
//------------------------------------------------------------------
void* PoketchViewTool_GetCmdWork(POKETCH_CMD_WORK *cwk)
{
	return cwk->wk;
}

//------------------------------------------------------------------
/**
 * コマンドワークからシーケンスナンバーを返す
 *
 * @param   cwk		コマンドワーク
 *
 * @retval  u32		シーケンスナンバー
 */
//------------------------------------------------------------------
u32 PoketchViewTool_GetSeq(POKETCH_CMD_WORK *cwk)
{
	return cwk->seq;
}

//------------------------------------------------------------------
/**
 * コマンドワークのシーケンスナンバーを進める
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_FwdSeq(POKETCH_CMD_WORK *cwk)
{
	cwk->seq++;
}

//------------------------------------------------------------------
/**
 * コマンドワークのシーケンスナンバーをセット
 *
 * @param   cwk		コマンドワーク
 * @param   seq		シーケンスナンバー
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetSeq(POKETCH_CMD_WORK* cwk, u32 seq )
{
	cwk->seq = seq;
}


//------------------------------------------------------------------
/**
 * ３ｘ３以上のウィンドウ状スクリーンデータをバッファに作成
 *
 * @param   buf		
 * @param   charno		
 * @param   width		
 * @param   height		
 * @param   chardata_width		
 * @param   palno		
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_MakeWindowScrn( u16 *buf, u32 charno, u32 width, u32 height, u32 chardata_width, u32 palno )
{
	u32 i, j, max;

	palno <<= 12;

	buf[0] = palno | charno;
	for(i = 1; i < (width - 1); i++){
		buf[ i ] = palno | (charno + 1);
	}
	buf[ i ] = palno | (charno + 2);

	buf += width;
	charno += chardata_width;
	for(j = 1; j < (height - 1); j++)
	{
		buf[ 0 ] = palno | charno;
		for(i = 1; i < (width-1); i++)
		{
			buf[ i ] = palno | (charno + 1);
		}
		buf[ i ] = palno | (charno + 2);
		buf += width;
	}

	charno += chardata_width;
	buf[0] = palno | charno;
	for(i = 1; i < (width - 1); i++){
		buf[ i ] = palno | (charno + 1);
	}
	buf[ i ] = palno | (charno + 2);


}

//------------------------------------------------------------------
/**
 * ２×２のブロック状スクリーンデータをﾊﾞｯﾌｧに作成
 *
 * @param   buf			ﾊﾞｯﾌｧ先頭ｱﾄﾞﾚｽ
 * @param   scr_x		書き出し開始X座標（ｷｬﾗ単位）
 * @param   scr_y		書き出し開始Y座標（ｷｬﾗ単位）
 * @param   scr_w		ﾊﾞｯﾌｧの横ｻｲｽﾞ（キャラ単位）
 * @param   charno		ブロック状キャラデータの先頭ナンバー
 * @param   chardata_width		キャラデータ横サイズ
 * @param   palno		パレットナンバー
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_MakeBlockScrn( u16 *buf, u32 scr_x, u32 scr_y, u32 scr_w, u32 charno, u32 chardata_width, u32 palno )
{
	palno <<= 12;

	buf += (( scr_w * scr_y ) + scr_x );

	buf[0] = palno | charno;
	buf[1] = palno | (charno + 1);
	buf[scr_w] = palno | (charno + chardata_width);
	buf[scr_w+1] = palno | (charno + chardata_width + 1);
}

//------------------------------------------------------------------
/**
 * カラーデータをポケッチ４色カラーに変換
 *
 * @param   col		カラーデータアドレス
 * @param   max		変換カラー数
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_TransformColorData( u16* col, u32 max )
{
	u16*  palDat;

	palDat = sys_AllocMemory(POKETCH_APP_VIEW_HEAPID, 0x20);
	if(palDat)
	{
		static const u8 palpos[] = {
			POKETCH_DEFAULTCOLOR_L4_POS,POKETCH_DEFAULTCOLOR_L3_POS,
			POKETCH_DEFAULTCOLOR_L2_POS,POKETCH_DEFAULTCOLOR_L1_POS
		};

		u32 i, r, g, b, l;

		PoketchView_GetColorPalette( palDat );

		for(i=0; i<max; i++)
		{
			r = (col[i] & GX_RGB_R_MASK) >> GX_RGB_R_SHIFT;
			g = (col[i] & GX_RGB_G_MASK) >> GX_RGB_G_SHIFT;
			b = (col[i] & GX_RGB_B_MASK) >> GX_RGB_B_SHIFT;

			l = ((r*299)+(g*587)+(b*114))/1000;	// 輝度計算。l = 0~31 なハズ。
			l >>= 3;	// l = 0~3 の範囲に落とす
			if(l>3){	// 念のため
				l = 3;
			}

			col[i] = palDat[palpos[l]];
		}
		sys_FreeMemoryEz(palDat);
	}
}
//------------------------------------------------------------------
/**
 * 単色カラーデータを作って指定位置に転送
 *
 * @param   colno	色番号（0~3）
 * @param   palno	転送位置(0~15）
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_TransSingleColorData( u32 colno, u32 palno )
{
	u16*  palDat;

	palDat = sys_AllocMemory(POKETCH_APP_VIEW_HEAPID, 0x20);
	if(palDat)
	{
		u16*  tmp_pal = sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, 0x20 );

		PoketchView_GetColorPalette( palDat );

		if(tmp_pal)
		{
			int i;

			for(i=0; i<16; i++)
			{
				tmp_pal[i] = palDat[ colno ];
			}

			DC_FlushRange( tmp_pal, 0x20 );
			GXS_LoadOBJPltt( tmp_pal, palno*0x20, 0x20 );
			sys_FreeMemoryEz(tmp_pal);
		}
		sys_FreeMemoryEz(palDat);
	}
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンのカラーデータをポケッチ４色カラー化して転送
 *
 * @param   palno		転送先パレットナンバ
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetupPokeIconPalette( u32 palno )
{
	void* palBuf;
	NNSG2dPaletteData* palData;

	palBuf = ArcUtil_PalDataGet(ARC_POKEICON, PokeIconPalArcIndexGet(),  &palData, HEAPID_POKETCH_APP);
	if(palBuf)
	{
		PoketchViewTool_TransformColorData( palData->pRawData, 4*0x10 );
		DC_FlushRange( palData->pRawData, 4*0x20 );
		GXS_LoadOBJPltt( palData->pRawData, palno*0x20, 4*0x20 );
		sys_FreeMemoryEz(palBuf);
	}

}

//------------------------------------------------------------------
/**
 * ポケモンアイコンのCGXデータを転送
 *
 * @param   charno		転送先キャラナンバ
 * @param   datIdx		転送するアイコンデータIDの配列
 * @param   max			何体分転送するか（datIdx配列要素数）
 * @param   anmFlag		アニメさせるか
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetupPokeIconCgx( u32 charno, const u32* datIdx, u32 max, BOOL anmFlag )
{
	enum {
		CGX_HEADER_SIZE = 0x80,
		CGX_BYTESIZE_NO_ANM = 16*0x20,
		CGX_BYTESIZE_ANM    = CGX_BYTESIZE_NO_ANM*2,
		CGX_BUFSIZE_NO_ANM  = CGX_BYTESIZE_NO_ANM  + CGX_HEADER_SIZE,
		CGX_BUFSIZE_ANM     = CGX_BYTESIZE_ANM + CGX_HEADER_SIZE,
	};

	static const u16 transSize[2] = { CGX_BYTESIZE_NO_ANM, CGX_BYTESIZE_ANM };
	static const u16 bufSize[2]   = { CGX_BUFSIZE_NO_ANM,  CGX_BUFSIZE_ANM  };

	u8 *readbuf;

	readbuf = sys_AllocMemory( HEAPID_POKETCH_APP, bufSize[anmFlag] );

	if( readbuf )
	{
		ARCHANDLE* arcHandle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_POKETCH_APP );

		if(arcHandle)
		{
			NNSG2dCharacterData* charData;
			u32 i;

			for(i=0; i<max; i++)
			{
				ArchiveDataLoadOfsByHandle( arcHandle, datIdx[i], 0, bufSize[anmFlag], readbuf );
				NNS_G2dGetUnpackedCharacterData( readbuf, &charData );
				DC_FlushRange( charData->pRawData, transSize[anmFlag] );
				GXS_LoadOBJ( charData->pRawData, (charno*0x20)+(transSize[anmFlag]*i), transSize[anmFlag] );
			}
			ArchiveDataHandleClose(arcHandle);
		}
		sys_FreeMemoryEz(readbuf);
	}

}



//------------------------------------------------------------------
/**
 * サブBG1テスト用スクリーンデータ作成（製品版には入れない）
 *
 * @param   app_no		アプリナンバー
 *
 */
//------------------------------------------------------------------
void PoketchView_TestScreenMake( GF_BGL_INI* bgl, u32  app_no, u32 bg_frame )
{
	extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

	#define SET_SCR(scrn, n)	{ 							\
									u32  base = (((n) / 4) * 16) + (((n) & 3) * 2);	\
									(scrn)[0] = base;								\
									(scrn)[1] = base + 1;							\
									(scrn)[2] = base + 8;							\
									(scrn)[3] = base + 9;							\
								}

	enum {
		WRITE_XPOS = 9,
		WRITE_YPOS = 11,
	};
	
	u16  scrn[4];
	u32  no;

	SET_SCR(scrn, 1);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+0, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, 2);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+2, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, 3);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+4, WRITE_YPOS, 2, 2 );

	no = app_no / 10;
	app_no -= (no * 10);
	no += 4;
	app_no += 4;

	SET_SCR(scrn, no);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+6, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, app_no);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+8, WRITE_YPOS, 2, 2 );


	#undef SET_SCR
}

