//============================================================================================
/**
 * @file	ribbon.h
 * @brief	リボンデータ関連
 * @author	Hiroyuki Nakamura
 * @date	2006.04.18
 */
//============================================================================================
#ifndef RIBBON_H
#define RIBBON_H
#undef GLOBAL
#ifdef RIBBON_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
#define	RIBBON_MAX		( 80 )			// リボン総数
#define	MSG_SP_RIBBON	( 0x8000 )		// 配布リボンのメッセージ定義

// リボンデータ取得ID
enum {
	RIBBON_PARA_POKEPARA = 0,	// PokeParaGetの取得ID
	RIBBON_PARA_GRAPHIC,		// グラフィックID
	RIBBON_PARA_PALNUM,			// パレット番号
	RIBBON_PARA_NAME,			// リボン名
	RIBBON_PARA_INFO,			// リボン説明
};


//リボンID	手書きなので、必要なものだけ定義してます
enum{
	RIBBON_ID_COOL = 33,			//クールリボン
	RIBBON_ID_COOL_SUPER,			//クールリボンスーパー
	RIBBON_ID_COOL_HYPER,			//クールリボンハイバー
	RIBBON_ID_COOL_MASTER,			//クールリボンマスター
	RIBBON_ID_BEAUTY,				//ビューティリボン
	RIBBON_ID_BEAUTY_SUPER,			//ビューティリボンスーパー
	RIBBON_ID_BEAUTY_HYPER,			//ビューティリボンハイパー
	RIBBON_ID_BEAUTY_MASTER,		//ビューティリボンマスター
	RIBBON_ID_CUTE,					//キュートリボン
	RIBBON_ID_CUTE_SUPER,			//キュートリボンスーパー
	RIBBON_ID_CUTE_HYPER,			//キュートリボンハイパー
	RIBBON_ID_CUTE_MASTER,			//キュートリボンマスター
	RIBBON_ID_GENEASU,				//ジーニアスリボン
	RIBBON_ID_GENEASU_SUPER,		//ジーニアスリボンスーパー
	RIBBON_ID_GENEASU_HYPER,		//ジーニアスリボンハイパー
	RIBBON_ID_GENEASU_MASTER,		//ジーニアスリボンマスター
	RIBBON_ID_PAWAFURU,				//パワフルリボン
	RIBBON_ID_PAWAFURU_SUPER,		//パワフルリボンスーパー
	RIBBON_ID_PAWAFURU_HYPER,		//パワフルリボンハイパー
	RIBBON_ID_PAWAFURU_MASTER,		//パワフルリボンマスター

	// AGBで未配布のリボン
	RIBBON_ID_MARINE = 25,			//マリンリボン
	RIBBON_ID_LAND,					//ランドリボン
	RIBBON_ID_SKY,					//スカイリボン

	// DSの配布リボン
	RIBBON_ID_SINOU_RED = 73,		//シンオウレッドリボン
	RIBBON_ID_SINOU_GREEN,			//シンオウグリーンリボン
	RIBBON_ID_SINOU_BLUE,			//シンオウブルーリボン
	RIBBON_ID_SINOU_FESTIVAL,		//シンオウフェスティバルリボン
	RIBBON_ID_SINOU_CARNIVAL,		//シンオウカーニバルリボン
	RIBBON_ID_SINOU_CLASSIC,		//シンオウクラシックリボン
	RIBBON_ID_SINOU_PREMIERE,		//シンオウプレミアリボン
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * リボンデータ取得
 *
 * @param	dat_id		データ番号
 * @param	prm_id		取得パラメータID
 *
 * @return	指定パラメータ
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 RIBBON_DataGet( u8 dat_id, u8 prm_id );

//--------------------------------------------------------------------------------------------
/**
 * リボン説明取得
 *
 * @param	sv			セーブデータ
 * @param	dat_id		データ番号
 *
 * @return	リボン説明メッセージインデックス
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32	RIBBON_InfoGet( u8 * sv, u8 dat_id );

//--------------------------------------------------------------------------------------------
/**
 * リボンIDから説明が格納されている位置を取得
 *
 * @param	dat_id		データ番号
 *
 * @retval	"0xff = 配布リボン以外"
 * @retval	"0xff != 格納位置"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 RIBBON_SaveIndexGet( u8 dat_id );


#undef GLOBAL
#endif	/* RIBBON_H */
