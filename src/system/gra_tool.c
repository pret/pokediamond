//==============================================================================
/**
 * @file	gra_tool.c
 * @brief	グラフィックツール
 * @author	goto
 * @date	2005.11.16
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"

#include "system/gra_tool.h"

#include "system/arc_tool.h"

#include "include/battle/battle_common.h"
#include "system/softsprite.h"
#include "include/poketool/monsno.h"

// =============================================================================
//
//
//	■画像変換
//
//
// =============================================================================
// 1Charを2D→1D変換
static void CharCopy1_1D_from_2D(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len);

//--------------------------------------------------------------
/**
 * @brief	2D→1Dに1キャラ変換
 *
 * @param	src			元データ
 * @param	dst			展開先
 * @param	ofs			元データのコピー開始位置
 * @param	bofs		展開先バッファの書き込み位置
 * @param	cs			コピーサイズ
 * @param	len			2Dデータの幅
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CharCopy1_1D_from_2D(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len)
{
	int i;
	u32 dat;
	
	for (i = 0; i < 8; i++){
		memcpy(&dst[ *bofs ], &src[ *ofs ], cs);
		*ofs  += len;
		*bofs += cs;
	}
}


//--------------------------------------------------------------
/**
 * @brief	素のキャラデータ取り出し
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	ch_data	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void UnpackCharData(int arc_id, int index_no, int heap_id, NNSG2dCharacterData** ch_data)
{
	BOOL  res;
	void* aw = NULL;
	
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< キャラデータの取得
	res = NNS_G2dGetUnpackedCharacterData(aw, &(*ch_data));
	
	GF_ASSERT(ch_data != NULL);
	
	GF_ASSERT(res != FALSE);
	
	sys_FreeMemoryEz(aw);
}

//--------------------------------------------------------------
/**
 * @brief	渡されたキャラデータを変換
 *
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	ch_data	
 * @param	buff	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CI_1D_from_2D(int x, int y, int w, int h, NNSG2dCharacterData* ch_data, void* buff)
{
	u8* p_data = NULL;
	u8* p_buff = NULL;
	int size;
	int cs;
	int ofs;
	int bofs;
	int len;

	GF_ASSERT(ch_data->W >= (x + w));		///< サイズチェック
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< 準備
	cs     = (sizeof(u8) * 4);				///< コピーサイズ 8dot = 4Byte
	p_data = ch_data->pRawData;				///< キャラデータ
	p_buff = (u8*)buff;						///< 展開バッファ
	
	len = (ch_data->W * cs);				///< 長さ(元画像の幅)
	ofs = (x * cs) + (y * len);				///< 開始位置
	bofs = 0;								///< バッファの書き込み位置
	
	//全体ｺﾋﾟｰ
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< 開始位置
				CharCopy1_1D_from_2D(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1キャラコピー
			}
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンが、ぶち対象かどうか
 *
 * @param	monsno	
 *
 * @retval	static BOOL	TRUE = ぶち
 *
 */
//--------------------------------------------------------------
static BOOL IsStrikeMonsNo(int monsno)
{
	int i;
	int data;
	
	const int monsno_tbl[] = {
		MONSNO_PATTIIRU,
		MONSNO_MAX,				///< おわり
	};
	
	for (i = 0; i < MONSNO_MAX; i++){
		
		data = monsno_tbl[ i ];
		
		if (data == MONSNO_MAX){ break; }
		
		if (data == monsno){			
			return TRUE;	
		}		
	}	
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	ぶちを加えた変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	buff	
 * @param	rnd	
 * @param	animeFlag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void Ex_ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	BOOL bStrike;
	NNSG2dCharacterData* ch_data = NULL;
	
	UnpackCharData(arc_id, index_no, heap_id, &ch_data);
	
	SoftSpriteChrMask(ch_data->pRawData);				///< 復号
	
	bStrike = IsStrikeMonsNo(monsno);
	
	if (dir == PARA_FRONT && bStrike == TRUE){
		
		SoftSprite_MakeStrike(ch_data->pRawData, rnd, anime);
		
	}
	
	CI_1D_from_2D(x, y, w, h, ch_data, buff);
}

///< メモリ内部取得
static void* Ex_ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, u32 rnd, BOOL anime, int dir, int monsno)
{
	
	void* buff;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	Ex_ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff, rnd, anime, dir, monsno);
		
	return buff;
}

//--------------------------------------------------------------
/**
 * @brief	2D→1Dに変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	x					変換対象矩形:x
 * @param	y					変換対象矩形:y
 * @param	w					変換対象矩形:w
 * @param	h					変換対象矩形:h
 * @param	buff				展開先バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	void* aw = NULL;
	u8* p_data = NULL;
	u8* p_buff = NULL;
	NNSG2dCharacterData* ch_data = NULL;

	int size;
	int cs;
	int ofs;
	int bofs;
	int len;
	BOOL res;
	
	///< データの展開
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< キャラデータの取得
	res = NNS_G2dGetUnpackedCharacterData(aw, &ch_data);
	
	GF_ASSERT(res != FALSE);

	GF_ASSERT(ch_data->W >= (x + w));		///< サイズチェック
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< 準備
	cs     = (sizeof(u8) * 4);				///< コピーサイズ 8dot = 4Byte
	p_data = ch_data->pRawData;				///< キャラデータ
	
	SoftSpriteChrMask(p_data);				///< 復号
	
	p_buff = (u8*)buff;						///< 展開バッファ
	
	len = (ch_data->W * cs);				///< 長さ(元画像の幅)
	ofs = (x * cs) + (y * len);				///< 開始位置
	bofs = 0;								///< バッファの書き込み位置
	
	//全体ｺﾋﾟｰ
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< 開始位置
				CharCopy1_1D_from_2D(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1キャラコピー
			}
		}
	}
	
	sys_FreeMemoryEz(aw);
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	rc					矩形
 * @param	buff				バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, rc->x, rc->y, rc->h, rc->w, buff);
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに展開バッファをAllocして変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	x					変換対象矩形:x
 * @param	y					変換対象矩形:y
 * @param	w					変換対象矩形:w
 * @param	h					変換対象矩形:h
 *
 * @retval	void*				展開したバッファのポインタ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;	
}


//--------------------------------------------------------------
/**
 * @brief	2D→1Dに展開バッファをAllocして変換する
 *
 * @param	arc_id				アーカイブインデックス
 * @param	index_no			ファイルインデックス
 * @param	heap_id				ヒープID
 * @param	rc					矩形
 *
 * @retval	void*				展開したバッファのポインタ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	1D→OAM形状に変換
 *
 * @param	sx				変換対象データのサイズ X	
 * @param	sy				変換対象データのサイズ Y
 * @param	x				切り抜き開始 X
 * @param	y				切り抜き開始 Y
 * @param	w				切り抜きサイズ W
 * @param	h				切り抜きサイズ H
 * @param	bofs			オフセット
 * @param	src				元データ
 * @param	dst				展開先
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst)
{
	int i, j;
	u8* p_data;
	u8* p_buff;
	int ofs;
	
	int lx;
	int ly;
	
	p_data = (u8*)src;
	p_buff = (u8*)dst;
	
	lx = x + w;
	ly = y + h;

	for (j = y; j < ly; j++){
		for (i = x; i < lx; i++){
			ofs = (i * CHAR_BYTE) + (j * CHAR_BYTE * sx);
			memcpy(&p_buff[ *bofs ], &p_data[ ofs ], CHAR_BYTE);
			*bofs += CHAR_BYTE;
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	1D→OAM形状に変換 矩形でサイズ指定
 *
 * @param	sx				変換対象データのサイズ X	
 * @param	sy				変換対象データのサイズ Y
 * @param	rc				矩形
 * @param	bofs			オフセット
 * @param	src				データ
 * @param	dst				展開先
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_1D_RC(int sx, int sy, const CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst)
{
	ChangesInto_OAM_from_1D(sx, sy, rc->x, rc->y, rc->w, rc->h, bofs, src, dst);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 * @param	buff			展開先バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	const CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h);		///< 1Dから2Dへ変換

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	rc				矩形
 * @param	buff			バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff = NULL;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのデータを2D→1D→OAMに変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		インデックス番号
 * @param	heap_id			ヒープID
 * @param	rc				矩形
 *
 * @retval	void*			展開されたバッファポインタ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_OAM_from_PokeTex_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンデータを戦闘用に変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		データインデックス
 * @param	heap_id			ヒープ領域
 * @param	buff			バッファ
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff)
{
	const CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H
	};
	
	ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンデータを戦闘用に変換
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		データインデックス
 * @param	heap_id			ヒープID
 *
 * @retval	void*			バッファ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff);
	
	return buff;	
}

//--------------------------------------------------------------
/**
 * @brief	素のパレットデータを取り出し
 *
 * @param	arc_id			アーカイブID
 * @param	index_no		データインデックス
 * @param	heap_id			ヒープID
 *
 * @retval	void*			バッファ
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokePalData_Alloc(int arc_id, int index_no, int heap_id)
{
	NNSG2dPaletteData	*pd;
	void*				buf;
	void*				col;
	int					i;
	BOOL				ret;

	//パレットデータ読み込み
	col=sys_AllocMemory(heap_id,0x20);
	buf=ArchiveDataLoadMalloc(arc_id,index_no,heap_id);
	ret=NNS_G2dGetUnpackedPaletteData(buf,&pd);

	GF_ASSERT(ret==TRUE);

	MI_CpuCopy16(pd->pRawData,col,0x20);

	sys_FreeMemoryEz(buf);

	return col;	
}



//--------------------------------------------------------------
/**
 * @brief	ぶちを考慮したポケモンデータ変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	buff	
 * @param	rnd				個性乱数
 * @param	anime			アニメフラグ
 * @param	dir				向き
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	const CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = Ex_ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h, rnd, anime, dir, monsno);		///< 1Dから2Dへ変換

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}

//--------------------------------------------------------------
/**
 * @brief	ぶち考慮ポケモン変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	rc	
 * @param	buff	
 * @param	rnd				個性乱数
 * @param	anime			アニメフラグ
 * @param	dir				向き
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	Ex_ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff, rnd, anime, dir, monsno);
}


//--------------------------------------------------------------
/**
 * @brief	ぶちを考慮したポケモン変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	buff	
 * @param	rnd				個性乱数
 * @param	anime			アニメフラグ
 * @param	dir				向き
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	const CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H
	};
	
	Ex_ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff, rnd, anime, dir, monsno);
}

//--------------------------------------------------------------
/**
 * @brief	ぶちを考慮したポケモン変換
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	rnd				個性乱数
 * @param	anime			アニメフラグ
 * @param	dir				向き
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* Ex_ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id, u32 rnd, BOOL anime, int dir, int monsno)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	Ex_ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff, rnd, anime, dir, monsno);
	
	return buff;		
}

