//==============================================================================
/**
 * @file	wazatype_panel.c
 * @brief	技タイプ毎のパネルデータの取出しなど
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/palanm.h"
#include "battle/wazatype_panel.h"
#include "graphic\batt_bg_def.h"

//==============================================================================
//	定数定義
//==============================================================================
///技タイプのCGRデータがX方向にいくつあるか
#define WAZATYPE_CGR_X_LEN	(18)
///技タイプのCGRデータに入っているアニメ数
#define WAZATYPE_CGR_ANM_NUM	(3)
///技タイプのCGRデータの1つのアニメのX方向サイズ
#define WAZATYPE_CGR_X_ONE	(WAZATYPE_CGR_X_LEN / WAZATYPE_CGR_ANM_NUM)
///技タイプのCGRデータが何段に渡ってデータが存在しているか
#define WAZATYPE_CGR_Y_LEN	(9)


//==============================================================================
//	パレットデータ
//==============================================================================
//高速化のため素データで持っています（パレットだからたいして容量ないし）
#include "graphic/battle_w_type12_ncl_txt.dat"
#include "graphic/battle_w_type04_ncl_txt.dat"
#include "graphic/battle_w_type14_ncl_txt.dat"
#include "graphic/battle_w_type10_ncl_txt.dat"
#include "graphic/battle_w_type08_ncl_txt.dat"
#include "graphic/battle_w_type02_ncl_txt.dat"
#include "graphic/battle_w_type17_ncl_txt.dat"
#include "graphic/battle_w_type06_ncl_txt.dat"
#include "graphic/battle_w_type13_ncl_txt.dat"
#include "graphic/battle_w_type18_ncl_txt.dat"
#include "graphic/battle_w_type15_ncl_txt.dat"
#include "graphic/battle_w_type16_ncl_txt.dat"
#include "graphic/battle_w_type05_ncl_txt.dat"
#include "graphic/battle_w_type09_ncl_txt.dat"
#include "graphic/battle_w_type03_ncl_txt.dat"
#include "graphic/battle_w_type07_ncl_txt.dat"
#include "graphic/battle_w_type11_ncl_txt.dat"
#include "graphic/battle_w_type01_ncl_txt.dat"
#include "graphic/battle_w_type00_ncl_txt.dat"


//==============================================================================
//	データ
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   技タイプ毎のCGRデータ
 */
//--------------------------------------------------------------
ALIGN4 static const u16 WazaTypeCgrID[] = {
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
	BATTLE_W_TYPE01_NCGR_BIN,
};

//--------------------------------------------------------------
/**
 * @brief   技タイプ毎のパレットデータ
 */
//--------------------------------------------------------------
ALIGN4 static const u16 * const WazaTypePlttAdrs[] = {
	battle_w_type12_ncl,
	battle_w_type04_ncl,
	battle_w_type14_ncl,
	battle_w_type10_ncl,
	battle_w_type08_ncl,
	battle_w_type02_ncl,
	battle_w_type17_ncl,
	battle_w_type06_ncl,
	battle_w_type13_ncl,
	battle_w_type18_ncl,
	battle_w_type15_ncl,
	battle_w_type16_ncl,
	battle_w_type05_ncl,
	battle_w_type09_ncl,
	battle_w_type03_ncl,
	battle_w_type07_ncl,
	battle_w_type11_ncl,
	battle_w_type01_ncl,
};




//--------------------------------------------------------------
/**
 * @brief   技パネルのグラフィックが入っているArcのIDを取得
 * @retval  ARC_ID
 */
//--------------------------------------------------------------
int WazaPanel_ArcIDGet(void)
{
	return ARC_BATT_BG;
}

//--------------------------------------------------------------
/**
 * @brief   技パネルのキャラクタINDEXを取得
 * @param   waza_type		技タイプ(手持ち無しの場合は-1)
 * @retval  指定した技タイプのキャラクタINDEX
 */
//--------------------------------------------------------------
u32 WazaPanel_CharIndexGet(int waza_type)
{
	u32 char_index;
	
	if(waza_type != -1){
		char_index = WazaTypeCgrID[waza_type];
	}
	else{
		char_index = BATTLE_W_TYPE00_NCGR_BIN;
	}
	return char_index;
}

//--------------------------------------------------------------
/**
 * @brief   技パネルのパレットデータアドレスを取得
 * @param   waza_type		技タイプ(手持ち無しの場合は-1)
 * @retval  指定した技タイプのパレットデータアドレス
 */
//--------------------------------------------------------------
const u16 * WazaPanel_PalDataAdrsGet(int waza_type)
{
	const u16 *pal_data;
	
	if(waza_type != -1){
		pal_data = WazaTypePlttAdrs[waza_type];
	}
	else{
		pal_data = battle_w_type00_ncl;
	}
	return pal_data;
}

//--------------------------------------------------------------
/**
 * @brief   技タイプパネルのグラフィックをロードする
 *
 * @param   bgl				BGLへのポインタ
 * @param   heap_id			テンポラリで使用するヒープのID
 * @param   frame_no		ロード先のフレーム面
 * @param   trans_pos		ロード先の転送位置(矩形の左上のキャラクタ番号)
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 等
 * @param   charcter		展開済みのキャラデータへのアドレス
 *
 * 転送先は技タイプパネルと同じ形状の領域が矩形で取られている事が前提です。
 * trans_posはそのロード先、矩形の左上のキャラクタ位置を指定します。
 */
//--------------------------------------------------------------
void WazaPanel_CharLoad(GF_BGL_INI *bgl, int heap_id, int frame_no, u32 trans_pos, 
	int screen_type, const u8 *charcter)
{
	u32 y_len;
	int y;
	
	switch(screen_type){
	case GF_BGL_SCRSIZ_256x256:
	case GF_BGL_SCRSIZ_256x512:
		y_len = 32;
		break;
	case GF_BGL_SCRSIZ_512x256:
	case GF_BGL_SCRSIZ_512x512:
		y_len = 64;
		break;
	default:
		GF_ASSERT(0 && "対応していないスクリーンタイプです\n");
		return;
	}
	
	//キャラ転送
	for(y = 0; y < WAZATYPE_CGR_Y_LEN; y++){
		GF_BGL_LoadCharacter(bgl, frame_no, 
			&charcter[WAZATYPE_CGR_X_LEN * 0x20 * y], 
			WAZATYPE_CGR_X_ONE * 0x20, trans_pos + (y_len*y));
	}
}

//--------------------------------------------------------------
/**
 * @brief   技タイプパネルのキャラ転送を使いやすいようにまとめたもの
 *
 * @param   bgl				BGLへのポインタ
 * @param   waza_type		技タイプ(手持ち無しの場合は-1)
 * @param   heap_id		テンポラリで使用するヒープID
 * @param   frame_no		ロード先のフレーム面
 * @param   trans_pos		ロード先の転送位置(矩形の左上のキャラクタ番号)
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 等
 */
//--------------------------------------------------------------
void WazaPanel_EasyCharLoad(GF_BGL_INI *bgl, int waza_type, int heap_id, int frame_no, 
	u32 trans_pos, int screen_type)
{
	u32 arc_id, char_index;
	void *arc_data;
	NNSG2dCharacterData *char_data;
	
	arc_id = WazaPanel_ArcIDGet();
	char_index = WazaPanel_CharIndexGet(waza_type);

	arc_data = ArcUtil_CharDataGet(arc_id, char_index, 1, &char_data, heap_id);

	WazaPanel_CharLoad(bgl, heap_id, frame_no, trans_pos, screen_type, char_data->pRawData);

	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプパネルのキャラ転送で、同じ技タイプのCGRを連続してセットします。
 * 			(同じ技タイプを展開する場合、WazaPanel_EasyCharLoadに比べてFileOpenが
 *			一度で済むようになります)
 *
 * @param   bgl				BGLへのポインタ
 * @param   waza_type		技タイプ(手持ち無しの場合は-1)
 * @param   heap_id			テンポラリで使用するヒープID
 * @param   frame_no		ロード先のフレーム面
 * @param   trans_pos		ロード先の転送位置(矩形の左上のキャラクタ番号)(転送技数分)
 * @param   trans_num		trans_posの配列の数
 * @param   screen_type		GF_BGL_SCRSIZ_256x256 等
 */
//--------------------------------------------------------------
void WazaPanel_EasyCharLoad_ChainSet(GF_BGL_INI *bgl, int waza_type, int heap_id, int frame_no, 
	const u16 trans_pos[], int trans_num, int screen_type)
{
	u32 arc_id, char_index;
	void *arc_data;
	NNSG2dCharacterData *char_data;
	int i;
	
	arc_id = WazaPanel_ArcIDGet();
	char_index = WazaPanel_CharIndexGet(waza_type);

	arc_data = ArcUtil_CharDataGet(arc_id, char_index, 1, &char_data, heap_id);

	for(i = 0; i < trans_num; i++){
		WazaPanel_CharLoad(bgl, heap_id, frame_no, trans_pos[i], screen_type, char_data->pRawData);
	}

	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプパネルのパレット転送を使いやすいようにまとめたもの
 *
 * @param   pfd				パレットフェードシステムへのポインタ
 * @param   waza_type		技タイプ(手持ち無しの場合は-1)
 * @param   heap_id			テンポラリで使用するヒープID
 * @param   req				リクエストデータ番号
 * @param   palette_pos		パレット転送位置(パレット番号で指定)
 */
//--------------------------------------------------------------
void WazaPanel_EasyPalLoad(PALETTE_FADE_PTR pfd, int waza_type, int heap_id, 
	FADEREQ req, int palette_pos)
{
	const u16 *pal_data;
	
	pal_data = WazaPanel_PalDataAdrsGet(waza_type);
	PaletteWorkSet(pfd, pal_data, req, palette_pos * 16, 0x20);
}

