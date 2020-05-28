//==============================================================================
/**
 * @file	wp_tbl.h
 * @brief	技エフェクトパーティクルデータテーブルのヘッダ
 * @author	matsuda
 * @date	2005.07.22(金)
 */
//==============================================================================
#ifndef __WP_TBL_H__
#define __WP_TBL_H__

#include "include/system/arc_tool.h"

//==============================================================================
//	構造体定義
//==============================================================================
#if 0
typedef struct{
	const char *spa_path;	///<spaファイルへのパス
	pEmitFunc emit_func;	///<エミッタ生成時に呼び出すコールバック関数へのポインタ
	u8 res_no;				///<リソース番号
}WP_DATA;

extern const WP_DATA * Wp_DataPtrGet(int data_no);
extern void Wp_ParticleSet(PTC_PTR ptc, int data_no);
#endif


//==============================================================================
//	外部関数宣言
//==============================================================================
extern PTC_PTR Wp_Init(int heap_id, int data_no, int tex_at_once);
extern PTC_PTR Wp_InitEx_CB(int heap_id, int arc_id, int data_no, int tex_at_once);
extern void * Particle_ArcResourceLoad_AH(ARCHANDLE* ah, int index, int heap_id);
extern PTC_PTR Wp_InitEx_CBAH(ARCHANDLE* ah, int heap_id, int data_no, int tex_at_once);
extern PTC_PTR Wp_InitEx(int heap_id, int arc_id, int data_no, int tex_at_once);
extern void Wp_Exit(PTC_PTR ptc);
extern EMIT_PTR Wp_EmitterCreate(PTC_PTR ptc, int resource_no, int func_num, void *temp_ptr);
extern EMIT_PTR Wp_EmitterCreateFunc(PTC_PTR ptc, int resource_no, pEmitFunc func, void *temp_ptr);



#endif	//__WP_TBL_H__

