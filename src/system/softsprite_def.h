
//============================================================================================
/**
 * @file	softsprite_def.h
 * @bfief	ソフトウエアスプライトを使用した表示プログラム
 * @author	HisashiSogabe
 * @date	05.06.08
 */
//============================================================================================

#include	"system/softsprite.h"

#ifndef __SOFTSPRITE_DEF_H_
#define __SOFTSPRITE_DEF_H_

///<表示用構造体宣言
struct soft_sprite
{
	u32						exist			:1;			///<配置フラグ（0:未配置　1:配置済み）
	u32						poly_id			:6;			///<ポリゴンID
	u32						make_req		:1;			///<テクスチャMAKEリクエスト
	u32						pal_req			:1;			///<パレットMAKEリクエスト
	u32										:23;		///<あまり

	SOFT_SPRITE_ARC			ssa;						///<読み込むキャラクタ、パレットデータのアーカイバ情報格納領域
	SOFT_SPRITE_ARC			ssa_push;					///<読み込むキャラクタ、パレットデータのアーカイバ情報格納領域（スタック）
	SOFT_SPRITE_PARAM		ssp;						///<ソフトウエアスプライトのパラメータ

	u8						anm_no;						///<アニメーションナンバー
	u8						anm_seq;					///<アニメーションシーケンスナンバー
	u8						anm_wait;					///<アニメーションウエイト
	u8						anm_pat;					///<アニメーションパターンナンバー

	u8						anm_loop[SS_ANM_SEQ_MAX];	///<アニメーションループカウンタ
	u8						dummy[2];

	SOFT_SPRITE_MOVE_FUNC	*move;						///<ソフトスプライト動作関数

	SOFT_SPRITE_SHADOW		sss;						///<ソフトスプライト影構造体
	SOFT_SPRITE_SHADOW		sss_push;					///<ソフトスプライト影構造体退避領域

	SOFT_SPRITE_ANIME		ssanm[SS_ANM_SEQ_MAX];		///<アニメーションデータ
};

///<表示用マネージャ構造体宣言
struct soft_sprite_manager
{
	SOFT_SPRITE				ss[SOFT_SPRITE_MAX];	///<配置したスプライトを管理する領域
	NNSG2dImageProxy		imgp;					///<ソフトウエアスプライトのテクスチャのVRAM情報を受け取る画像プロクシ
	NNSG2dImagePaletteProxy	pltp;					///<ソフトウエアスプライトのテクスチャパレットのVRAM情報を受け取るパレットプロクシ
	int						heap_id;				///<テクスチャを展開する時にテンポラリを確保するヒープ領域のID

	u32						texture_trans_ofs;		///<テクスチャの転送先アドレスのオフセット
	u32						texture_trans_size;		///<テクスチャデータ転送サイズ
	u32						palette_trans_ofs;		///<テクスチャパレットの転送先アドレスのオフセット
	u32						palette_trans_size;		///<テクスチャパレットデータ転送サイズ

	u8						*dest_chr;				///<仮想テクスチャ展開領域
	u16						*dest_col;				///<仮想テクスチャパレット展開領域
	u16						*dest_col_temp;			///<仮想テクスチャパレット展開領域

	NNSG2dCharacterData		cd_dest;
	NNSG2dPaletteData		pd_dest;

	u8						cnt;					///<登録したソフトウエアスプライトのカウンタ
	u8						texture_trans_req;		///<テクスチャ転送リクエストフラグ
	u8						palette_trans_req;		///<パレット転送リクエストフラグ
	u8						mode;					///<ソフトウエアスプライト描画モード

	u32						ss_system_flag;			///<ソフトウエアスプライトシステムフラグ
};

#endif __POKEGRA_DEF_H_
