#ifndef	__COMM_UNION_DEF_H__
#define	__COMM_UNION_DEF_H__

//----------------------------------------------
// Union_ConnectResultGetが返す値
//----------------------------------------------
#define UNION_CONNECT_BUSY			( 0	) ///< 途中
#define UNION_CONNECT_SUCCESS   	( 1	) ///< 接続成功
#define UNION_CONNECT_FAILED		( 2	) ///< 接続失敗
#define UNION_CONNECT_PARENT		( 3 ) ///< 子機として接続しにいったのに親機になった

#define UNION_SELECT_EVENT			( 0 ) ///< ユニオンルームで行う内容
#define UNION_YESNO_RESULT			( 1 ) ///< ユニオンルームで聞いたはい・いいえの結果

// 子機の選択肢＆開始イベント処理の番号
#define UNION_CHILD_SELECT_CARD		( 1 ) ///< 接続後の選択肢で「あいさつ」
#define UNION_CHILD_SELECT_BATTLE	( 2 ) ///< 接続後の選択肢で「たいせん」
#define UNION_CHILD_SELECT_TRDE		( 3 ) ///< 接続後の選択肢で「こうかん」
#define UNION_CHILD_SELECT_OEKAKI	( 4 ) ///< 接続後の選択肢で「おえかき」
#define UNION_CHILD_SELECT_RECORD	( 5 ) ///< 接続後の選択肢で「レコード」
#define UNION_CHILD_SELECT_GURUGURU	( 6 ) ///< 接続後の選択肢で「ぐるぐる交換」
#define UNION_CHILD_SELECT_CANCEL	( 7 ) ///< 接続後の選択肢で「やめる」
#define UNION_PARENT_SELECT_CANCEL	( 8 ) ///< 親機からキャンセルが来た


// 話しかけ開始時のビーコン確認結果用定義
#define UNION_PARENT_CONNECT_OK			(  1 )	// ユニオン接続トライ開始
#define UNION_PARENT_OEKAKI_OK			(  2 )	// お絵かき乱入通信トライ開始
#define UNION_PARENT_RECORD_OK			(  3 )	// レコード乱入通信トライ開始
#define UNION_PARENT_GURUGURU_OK		(  4 )	// ぐるぐる交換乱入通信トライ開始
#define UNION_PARENT_CONNECT_NG			(  5 )	// 既に接続済みなので繋がらない → 会話へ

// トレーナー名を設定するときに使用する定義		
#define UNION_TALK_CHILD				( 0 )	// 話しかける方の名前設定（入れるのは話しかける相手の名前）
#define UNION_TALK_PARENT				( 1 )	// 話しかけられる方の名前設定（入れるのは話しかけてきた相手の名前）

// バトル開始時のポケモンリスト選択の結果を返す
#define UNION_BATTLE_POKELIST_OK		( 1 )	// ポケモンを選択した
#define UNION_BATTLE_POKELIST_NG		( 2 )	// やめるを選択した

// バトル開始時のポケモンリスト選択の結果を返す
#define UNION_BATTLE_OK					( 0 )	
#define UNION_BATTLE_MY_CANCEL			( 1 )	// 自分が戦闘をキャンセルした
#define UNION_BATTLE_PARTNER_CANCEL		( 2 )	// 相手が戦闘をキャンセルした

// 状況に応じて会話番号を取得するための状況設定定義
#define UNION_NO_CONNECT_TALK			( 0 )	// 単なる立ち話（接続できない相手の話を聞く）
#define UNION_CONNECTED_START_TALK		( 1 )	// 遊ぶ事になったので「じゃあ、はじめよう」という会話
#define UNION_CONNECT_SUCCESS_TALK		( 2 )	// 接続に成功した
#define UNION_TALK_CANCEL_CARD			( 3 )   // カードを断られた
#define UNION_TALK_CANCEL_OEKAKI		( 4 )   // おえかきを断られた
#define UNION_TALK_CANCEL_BATTLE		( 5 )   // たいせんを断られた
#define UNION_TALK_CANCEL_TRADE			( 6 )   // こうかんを断られた
#define UNION_TALK_CANCEL_GURUGURU		( 7 )   // ぐるぐるを断られた
#define UNION_TALK_CANCEL_RECORD		( 8 )   // レコードを断られた
#define UNION_CONNECT_ANSWER_WAIT		( 9 )   // 遊びを決めた後、相手の返事を待つ

#define UNION_JOIN_OEKAKI_TALK			( 10 )
#define UNION_JOIN_RECORD_TALK			( 11 )
#define UNION_JOIN_GURUGURU_TALK		( 12 )

#define UNION_SUCCESS_OEKAKI_JOIN		( 13 )
#define UNION_SUCCESS_RECORD_JOIN		( 14 )
#define UNION_SUCCESS_GURUGURU_JOIN		( 15 )

#define UNION_JOIN_OEKAKI_NO			( 16 )
#define UNION_JOIN_RECORD_NO			( 17 )
#define UNION_JOIN_GURUGURU_NO			( 18 )

#define UNION_CONNECT_BATTLE_REJECT		( 19 )
#define UNION_CONNECT_TRADE_REJECT		( 20 )
#define UNION_CONNECT_GURUGURU_REJECT	( 21 )

#define UNION_SELECT_NEXT_TALK			( 22 )
#define UNION_TALK_CONNECT_CANCEL		( 23 )	// 自分で子機が切った（話しかけた方）
#define UNION_TALK_CONNECT_CANCELED		( 24 )	// 相手に切られた（話しかけた方）

// ユニオンルームで通信で遊ぶ内容がきまった時にフェードアウトするまでの間
#define UNION_EVNET_PRE_WAIT			( 30 )  // 1秒間



// 通信開始した時の同期番号
#define UNION_SYNCHRO_CONNECTSTART		( 100 )

// 通信終了の時の同期番号
#define UNION_SYNCHRO_CONNECTEND		( 101 )

// たいせんが成立した後、ポケモンリストから戻ってくるのを待つための同期
#define UNION_SYNCHRO_POKELIST			( 102 )

// カードを見せる前の同期
#define UNION_SYNCHRO_CARDEND			( 103 )

#endif //__COMM_UNION_DEF_H__