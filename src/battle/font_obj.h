//==============================================================================
/**
 * @file	font_obj.h
 * @brief	フォントをOBJで表示する
 * @author	matsuda
 * @date	2005.10.17(月)
 */
//==============================================================================
#ifndef __FONT_OBJ_H__
#define __FONT_OBJ_H__

#include "system/fontproc.h"
#include "system/clact_tool.h"
#include "system/fontproc.h"
#include "gflib/msg_print.h"


//==============================================================================
//	定数定義
//==============================================================================
///フォントOBJで使用出来る最大アクター数
#define FONTOBJ_ACTOR_MAX		(8)	//横幅32なら8個あれば256ドット行くので、とりあえず8個

///フォントOBJのOAMサイズ定義
enum{
	FONTOBJ_OAMSIZE_32x16,	///<32x16形状のOAMを使用
};

///X座標のセット、取得方法
enum{
	FONTOBJ_POS_LEFT,
	FONTOBJ_POS_CENTER,
	FONTOBJ_POS_RIGHT,
};


//==============================================================================
//	構造体定義
//==============================================================================
///フォントOBJ作成後、作られるパラメータ(フォントOBJ用のアクターワーク)
typedef struct{
	u8 use_oam;			///<使用しているOAM数(アクター個数)
	u8 type_dot;		///<1つのOAMの横幅ドット数
	u16 font_len;		///<文字列のドット長
	s16 x;				///<X座標(左端座標)
	s16 y;				///<Y座標(中心座標)
	CATS_ACT_PTR cap[FONTOBJ_ACTOR_MAX];

	u16 start_charid;	///<キャラマネージャー登録開始ID
	u16 start_palid;	///<パレットマネージャー登録開始ID
	u16 start_cellid;	///<セルマネージャー登録開始ID
	u16 start_anmid;	///<セルアニメマネージャー登録開始ID
}FONTOBJ_ACTWORK;

///フォントOBJ作成に必要なデータ
typedef struct{
	FONTOBJ_ACTWORK *fa;

	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	FONT_TYPE font;
	const STRBUF* str;
	u32 margin;
	GF_PRINTCOLOR print_color;

	NNS_G2D_VRAM_TYPE d_area;
	int oam_size;
	u32 max_oam;
	int oam_fix;
	int soft_pri;
	int bg_pri;
	int pal_offset;		///<パレット番号オフセット
	
	int heap_id;

	u16 start_charid;	///<キャラマネージャー登録開始ID
	u16 start_palid;	///<パレットマネージャー登録開始ID
	u16 start_cellid;	///<セルマネージャー登録開始ID
	u16 start_anmid;	///<セルアニメマネージャー登録開始ID
}FONTOBJ_CREATE_DATA;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern void FontOBJ_Create(const FONTOBJ_CREATE_DATA *fcd);
extern void FontOBJ_Delete(CATS_RES_PTR crp, FONTOBJ_ACTWORK *fa, int not_pal_free);
extern void FontOBJ_PosSet(FONTOBJ_ACTWORK *fa, int set_type, s16 x, s16 y);
extern void FontOBJ_PosGet(FONTOBJ_ACTWORK *fa, int get_type, s16 *x, s16 *y);
extern void FontOBJ_Enable(FONTOBJ_ACTWORK *fa, int enable);


//==============================================================================
//	inline定義
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   フォントOBJを作成します
 *
 * @param   fa				フォントOBJ生成時、アクター情報がここに代入されます
 * @param   bgl				BGLデータ
 * @param   csp				
 * @param   crp				
 * @param   font			フォントタイプ(FONT_SYSTEM等)
 * @param   str				文字データ
 * @param   margin			文字間隔
 * @param   print_color		文字の色情報
 * @param   d_area			Vram転送位置(NNS_G2D_VRAM_TYPE_2DMAIN or NNS_G2D_VRAM_TYPE_2DSUB)
 * @param   oam_size		フォントOBJに使用するOAM形状(FONTOBJ_OAMSIZE_32x16等)
 * @param   max_oam			フォントOBJ作成に使用していい最大OAM個数(1～FONTOBJ_ACTOR_MAX)
 * @param   oam_fix			TRUE=常に最大個数分のOAMとその分のキャラ領域を使用する
 *                          (文字が入らなかった所は全て空白で埋めます)
 *                          FALSE=max_oamの範囲の中で必要な分だけ使用します
 * @param   soft_pri		アクターソフトプライオリティ
 * @param   bg_pri			アクターBGプライオリティ
 * @param   pal_offset		パレット番号オフセット
 * @param   heap_id			ヒープID。関数内で一時的にメモリを確保する際に使用します
 *                          (関数から出る時には解放されています)
 * @param   start_charid	フォントOBJ作成時、キャラマネージャに登録する開始ID
 *                          (このID番号から、生成に必要なOAM数分、連番で登録します)
 * @param   start_palid		パレットマネージャに登録する開始ID(詳細説明はstart_charidと同じです)
 * @param   start_cellid	セルマネージャに登録する開始ID(詳細説明はstart_charidと同じです)
 * @param   start_anmid		セルアニメマネージャに登録する開始ID(詳細説明はstart_charidと同じです)
 *
 *
 *
 * 既に登録済みのパレットを共用する形でする場合は、その登録済みの管理IDを渡してください
 * 
 * 8x8フォントには未対応です。
 *
 */
//--------------------------------------------------------------
inline void FontOBJ_CreateInline(FONTOBJ_ACTWORK *fa, GF_BGL_INI *bgl, CATS_SYS_PTR csp, 
	CATS_RES_PTR crp, FONT_TYPE font, const STRBUF* str, u32 margin, GF_PRINTCOLOR print_color, 
	NNS_G2D_VRAM_TYPE d_area, int oam_size, u32 max_oam, int oam_fix,int soft_pri,int bg_pri, 
	int pal_offset, int heap_id, s32 start_charid, s32 start_palid, 
	s32 start_cellid, s32 start_anmid)
{
	FONTOBJ_CREATE_DATA fcd;
	
	fcd.fa = fa;

	fcd.bgl = bgl;
	fcd.csp = csp;
	fcd.crp = crp;

	fcd.font = font;
	fcd.str = str;
	fcd.margin = margin;
	fcd.print_color = print_color;

	fcd.d_area = d_area;
	fcd.oam_size = oam_size;
	fcd.max_oam = max_oam;
	fcd.oam_fix = oam_fix;
	fcd.soft_pri = soft_pri;
	fcd.bg_pri = bg_pri;
	fcd.pal_offset = pal_offset;
	
	fcd.heap_id = heap_id;

	fcd.start_charid = start_charid;
	fcd.start_palid = start_palid;
	fcd.start_cellid = start_cellid;
	fcd.start_anmid = start_anmid;

	FontOBJ_Create(&fcd);
}

#endif	//__FONT_OBJ_H__
