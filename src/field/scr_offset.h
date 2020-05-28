//============================================================================================
/**
 * @file	scr_offset.h
 * @bfief	スクリプトIDのオフセット定義
 * @author	Satoshi Nohara
 * @date	06.05.26
 */
//============================================================================================
#ifndef SCR_OFFSET_H
#define SCR_OFFSET_H


//============================================================================================
//
//	スクリプトIDオフセット
//
//	定義追加ルール
//	#define ID_"スクリプトファイル名"_OFFSET
//	#define ID_"スクリプトファイル名"_OFFSET_END
//
//	script.cの読み込むスクリプトファイル、メッセージファイルを対応させて下さい。
//
//============================================================================================
//#define	SCRID_NULL					(0)			//ダミースクリプトID
#define	ID_START_SCR_OFFSET				(1)			//開始スクリプトIDのオフセット
#define	ID_COMMON_SCR_OFFSET			(2000)		//共通スクリプトIDのオフセット
#define	ID_COMMON_SCR_OFFSET_END		(2499)		//共通スクリプトIDのオフセット終了
#define	ID_BG_ATTR_OFFSET				(2500)		//BGスクリプトIDのオフセット
#define	ID_BG_ATTR_OFFSET_END			(2799)		//BGスクリプトIDのオフセット終了
#define	ID_KINOMI_OFFSET				(2800)		//きのみスクリプトIDのオフセット
#define	ID_KINOMI_OFFSET_END			(2999)		//きのみスクリプトIDのオフセット終了
#define	ID_TRAINER_OFFSET				(3000)		//トレーナースクリプトIDのオフセット
#define	ID_TRAINER_OFFSET_END			(4999)		//トレーナースクリプトIDのオフセット終了
#define	ID_TRAINER_2VS2_OFFSET			(5000)		//2vs2トレーナースクリプトIDのオフセット
#define	ID_TRAINER_2VS2_OFFSET_END		(6999)		//2vs2トレーナースクリプトIDのオフセット終了
#define	ID_FLD_ITEM_OFFSET				(7000)		//フィールドアイテムスクリプトIDのオフセット
#define	ID_HIDE_ITEM_OFFSET				(8000)		//隠しアイテムスクリプトIDのオフセット
#define	ID_HIDE_ITEM_OFFSET_END			(8799)		//隠しアイテムスクリプトIDのオフセット終了
#define	ID_SAFARI_OFFSET				(8800)		//サファリスクリプトIDのオフセット
#define	ID_SAFARI_OFFSET_END			(8899)		//サファリスクリプトIDのオフセット終了
#define	ID_PERAP_OFFSET					(8900)		//ペラップスクリプトIDのオフセット
#define	ID_PERAP_OFFSET_END				(8949)		//ペラップスクリプトIDのオフセット終了
#define	ID_SAISEN_OFFSET				(8950)		//再戦スクリプトIDのオフセット
#define	ID_SAISEN_OFFSET_END			(8969)		//再戦スクリプトIDのオフセット終了
#define	ID_POKESEARCHER_OFFSET			(8970)		//ポケサーチャースクリプトIDのオフセット
#define	ID_POKESEARCHER_OFFSET_END		(8999)		//ポケサーチャースクリプトIDのオフセット終了
#define	ID_CONNECT_OFFSET				(9000)		//通信スクリプトIDのオフセット
#define	ID_CONNECT_OFFSET_END			(9099)		//通信スクリプトIDのオフセット終了
#define	ID_BATTLE_ROOM_OFFSET			(9100)		//コロシアムスクリプトIDのオフセット
#define	ID_BATTLE_ROOM_OFFSET_END		(9199)		//コロシアムスクリプトIDのオフセット終了
#define	ID_PC_UG_OFFSET					(9200)		//ポケセン地下スクリプトIDのオフセット
#define	ID_PC_UG_OFFSET_END				(9299)		//ポケセン地下スクリプトIDのオフセット終了
#define	ID_GROUP_OFFSET					(9300)		//グループスクリプトIDのオフセット
#define	ID_GROUP_OFFSET_END				(9399)		//グループスクリプトIDのオフセット終了
#define	ID_PORUTO_SCR_OFFSET			(9400)		//ポルトミニゲームスクリプトIDのオフセット
#define	ID_PORUTO_SCR_OFFSET_END		(9499)		//ポルトミニゲームスクリプトIDのオフセット終了
#define	ID_SODATEYA_OFFSET				(9500)		//育て屋スクリプトIDのオフセット
#define	ID_SODATEYA_OFFSET_END			(9599)		//育て屋スクリプトIDのオフセット終了
#define	ID_INIT_SCR_OFFSET				(9600)		//ゲーム開始スクリプトIDのオフセット
#define	ID_INIT_SCR_OFFSET_END			(9699)		//ゲーム開始スクリプトIDのオフセット終了
#define	ID_PAIR_SCR_OFFSET				(9700)		//連れ歩きスクリプトIDのオフセット
#define	ID_PAIR_SCR_OFFSET_END			(9799)		//連れ歩きスクリプトIDのオフセット終了
#define	ID_CON_RECEPTION_OFFSET			(9800)		//コンテスト受付スクリプトIDのオフセット
#define	ID_CON_RECEPTION_OFFSET_END		(9899)		//コンテスト受付スクリプトIDのオフセット終了
#define	ID_DEBUG_SCR_OFFSET				(9900)		//デバックスクリプトIDのオフセット
#define	ID_DEBUG_SCR_OFFSET_END			(9949)		//デバックスクリプトIDのオフセット終了
#define	ID_HYOUKA_SCR_OFFSET			(9950)		//評価スクリプトIDのオフセット
#define	ID_HYOUKA_SCR_OFFSET_END		(9999)		//評価スクリプトIDのオフセット終了
#define	ID_HIDEN_OFFSET					(10000)		//秘伝スクリプトIDのオフセット
#define	ID_HIDEN_OFFSET_END				(10099)		//秘伝スクリプトIDのオフセット終了
#define	ID_TV_OFFSET					(10100)		//TVスクリプトIDのオフセット
#define	ID_TV_OFFSET_END				(10149)		//TVスクリプトIDのオフセット終了
#define	ID_TV_INTERVIEW_OFFSET			(10150)		//TVインタビュースクリプトIDのオフセット
#define	ID_TV_INTERVIEW_OFFSET_END		(10199)		//TVインタビュースクリプトIDのオフセット終了
#define	ID_HAITATU_OFFSET				(10200)		//配達員スクリプトIDのオフセット
#define	ID_HAITATU_OFFSET_END			(10299)		//配達員スクリプトIDのオフセット終了
#define	ID_SUPPORT_OFFSET				(10300)		//サポートスクリプトIDのオフセット
#define	ID_SUPPORT_OFFSET_END			(10399)		//サポートスクリプトIDのオフセット終了


#endif	/* SCR_OFFSET_H */


