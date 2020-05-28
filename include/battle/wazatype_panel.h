//==============================================================================
/**
 * @file	wazatype_panel.h
 * @brief	技タイプ毎のパネルデータの取出しなど
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#ifndef __WAZATYPE_PANEL_H__
#define __WAZATYPE_PANEL_H__


//==============================================================================
//	外部関数宣言
//==============================================================================
extern int WazaPanel_ArcIDGet(void);
extern u32 WazaPanel_CharIndexGet(int waza_type);
extern const u16 * WazaPanel_PalDataAdrsGet(int waza_type);
extern void WazaPanel_CharLoad(GF_BGL_INI *bgl, int heap_id, int frame_no, u32 trans_pos, 
	int screen_type, const u8 *charcter);
extern void WazaPanel_EasyCharLoad(GF_BGL_INI *bgl, int waza_type, int heap_id, int frame_no, 
	u32 trans_pos, int screen_type);
extern void WazaPanel_EasyPalLoad(PALETTE_FADE_PTR pfd, int waza_type, int heap_id, 
	FADEREQ req, int palette_pos);
extern void WazaPanel_EasyCharLoad_ChainSet(GF_BGL_INI *bgl, int waza_type, int heap_id, 
	int frame_no, const u16 trans_pos[], int trans_num, int screen_type);


#endif	//__WAZATYPE_PANEL_H__

