//==============================================================================
/**
 * @file	contest_conv.h
 * @brief	コンテストで使われるデータ類の構造体定義など
 * @author	matsuda
 * @date	2006.05.02(火)
 * 
 * elf2binを使用したcソースからもincludeされるため、あまり外部ファイルのincludeを
 * する必要がないようにしておくこと
 */
//==============================================================================
#ifndef __CONTEST_CONV_H__
#define __CONTEST_CONV_H__


//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	登場タイミング
//--------------------------------------------------------------
enum{
	HOF_BOTH,			///<両方
	HOF_BEFORE,			///<殿堂前に登場
	HOF_AFTER,			///<殿堂後に登場
	HOF_SPECIAL,		///<必ず1人出場

	//削除予定の定義
	PALACE_BOTH = 0,			///<両方
	PALACE_BEFORE,			///<殿堂前に登場
	PALACE_AFTER,			///<殿堂後に登場
};

///ブリーダーの性格
enum{
	BRD_CHARACTER_ELITE,		///<エリート
	BRD_CHARACTER_JACKPOT,		///<大穴
	BRD_CHARACTER_SINCERE,		///<誠実
	BRD_CHARACTER_WEAK,			///<弱い
	
	BRD_CHARACTER_MAX,
};


//==============================================================================
//	構造体定義
//==============================================================================
///コンテスト技データ
typedef struct{
	u8 ap_no;		///<アピールNo
	u8 contype;		///<コンテスト技タイプ(CONTYPE_STYLE等)
	
	u16 dummy;
}CONWAZA_DATA;

///アピール技効果データ
typedef struct{
	u16 setumei_u_id;	///<技説明文上段のメッセージID
	u16 setumei_d_id;	///<技説明文下段のメッセージID
	s8 ap_point;		///<アピールポイント(マイナスの時は妨害値)
	
	u16 kouka_msgid_a;	///<技効果メッセージID：A
	u8 kouka_msgtag_a;	///<技効果メッセージID:Aのタグ
	u16 kouka_msgid_b;	///<技効果メッセージID：B
	u8 kouka_msgtag_b;	///<技効果メッセージID:Bのタグ
	u16 kouka_msgid_c;	///<技効果メッセージID：C
	u8 kouka_msgtag_c;	///<技効果メッセージID:Cのタグ
	u16 kouka_msgid_d;	///<技効果メッセージID：D
	u8 kouka_msgtag_d;	///<技効果メッセージID:Dのタグ

	u16 sp_msgid;		///<特殊メッセージID
	u8 sp_msgtag;		///<特殊メッセージIDのタグ
}APWAZA_DATA;


///ブリーダーデータ
typedef struct{
	u32	personal_rnd;					//個性乱数
	u32 id_no;							//ポケモンのID
	
	u16 obj_code;						///<フィールドのOBJコード
	u16 trainer_type;					///<トレーナータイプ
	
	u16	waza[WAZA_TEMOTI_MAX];			///<手持ち技番号

	u16 monsno;							///<ポケモン番号(開発NO)
	u16 nickname_id;					///<ニックネームメッセージID

	u16 name_id;						///<ブリーダー名メッセージID
	u8 style;							//かっこよさ
	u8 beautiful;						//うつくしさ

	u8 cute;							//かわいさ
	u8 clever;							//かしこさ
	u8 strong;							//たくましさ
	u8 fur;								//毛艶
	
	u16 rank:3;							///<参加可能ランク
	u16 part_style:1;					///<格好よさコンテスト参加可能
	u16 part_beautiful:1;				///<美しさコンテスト参加可能
	u16 part_cute:1;					///<可愛さコンテスト参加可能
	u16 part_clever:1;					///<賢さコンテスト参加可能
	u16 part_strong:1;					///<逞しさコンテスト参加可能
	u16 part_tutorial:1;				///<チュートリアル参加可能
	u16 part_practice:1;				///<練習参加可能
	u16 appear:2;						///<登場タイミング
	u16 sex:2;							///<性別
	u16 character:2;					///<性格
	u8 clip_no_flowery;					///<イメージクリップデータ番号(華やかなもの)
	u8 clip_no_simple;					///<イメージクリップデータ番号(シンプルなもの)

	u8 clip_no_artificial;				///<イメージクリップデータ番号(人工のもの)
	u8 clip_no_natural;					///<イメージクリップデータ番号(自然のもの)
	u8 clip_no_colorful;				///<イメージクリップデータ番号(色つきのもの)
	u8 clip_no_lively;					///<イメージクリップデータ番号(にぎやかなもの)

	u8 clip_no_refresh;					///<イメージクリップデータ番号(すっきりしたもの)
	u8 clip_no_limit;					///<イメージクリップデータ番号(ギリギリのもの)
	u8 clip_no_softly;					///<イメージクリップデータ番号(ゆるやかなもの)
	u8 clip_no_gorgeous;				///<イメージクリップデータ番号(きらびやかのもの)

	u8 clip_no_elegant;					///<イメージクリップデータ番号(上品なもの)
	u8 clip_no_showy;					///<イメージクリップデータ番号(派手なもの)
	u8 popularity;						///<人気
	u8 version;							///<ブリーダーデータを作成したROMのバージョン

//	u8 dummy[2];			///<4バイト境界ダミー
	
}BREEDER_DATA;


///審判データ
typedef struct{
	u16 name_id;					///<名前ID
	u16 obj_code;					///<フィールドのOBJコード
	
	u16 condition_style:2;			///<評価コンディション(格好よさ)
	u16 condition_beautiful:2;		///<評価コンディション(美しさ)
	u16 condition_cute:2;			///<評価コンディション(可愛さ)
	u16 condition_clever:2;			///<評価コンディション(賢さ)
	u16 condition_strong:2;			///<評価コンディション(逞しさ)
	u16 rank:2;						///<参加可能ランク
	u16 guest:1;					///<ゲストフラグ(TRUE=ゲスト)
	u16 	:3;
	
	u16 dummy;			///<4バイト境界ダミー
}JUDGE_DATA;


///コンテスト：イメージクリップアクセサリデータ構造体
typedef struct{
	u8 no;			///<アクセサリナンバー
	u8 x;			///<X
	u8 y;			///<Y
	s8 pri;			///<優先順位
}CON_IMC_ACCE_DATA;

///コンテスト：イメージクリップデータ構造体
typedef struct{
	CON_IMC_ACCE_DATA acce[CON_IMAGE_ACCE_MAX_MASTER];
	u8 acce_data_num;	//acceに入っているデータ数
	
	s8 mons_pri;
	s8 bg;

	u8 dummy;		///<4バイト境界オフセット
}CON_IMC_DATA;


#endif	//__CONTEST_CONV_H__

