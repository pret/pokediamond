//=============================================================================
/**
 * @file	comm_def.h
 * @brief	通信関連でイベント等での受け渡しが必要な定義を集めたファイル
            defineしか許さないとの事
 * @author	Katsumi Ohno
 * @date    2005.11.09
 */
//=============================================================================
#ifndef _COMM_DEF_H_
#define _COMM_DEF_H_

// 無線で使用するDMA番号
#define COMM_DMA_NO                 (2)
//WMのパワーモード
#define COMM_POWERMODE       (1)
//SSL処理のスレッド優先順位
#define COMM_SSL_PRIORITY     (20)



// 親機を選択できる数。
#define  SCAN_PARENT_COUNT_MAX ( 16 )

// 子機最大数
#define  COMM_CHILD_MAX  ( 7 )

// ありえないID
#define COMM_INVALID_ID  (0xff)


// 機最大数
#define  COMM_MACHINE_MAX  (COMM_CHILD_MAX+1)

// 扱えるコマンドの受信最大サイズ
#define  COMM_COMMAND_RECV_SIZE_MAX  (256)
// 扱えるコマンドの送信最大サイズ  (ringbuffと同じ大きさ)
#define  COMM_COMMAND_SEND_SIZE_MAX  (264)



// 親のID
#define COMM_PARENT_ID    (0)

// 通信でメニューを出した場合の戻り値
#define  COMM_RETVAL_NULL    (0)     ///< 選択中
#define  COMM_RETVAL_CANCEL  (1)   ///< userキャンセル
#define  COMM_RETVAL_OK      (2)              ///< 選択完了
#define  COMM_RETVAL_ERROR   (3)              ///< 通信エラー
#define  COMM_RETVAL_DIFFER_REGULATION   (4)              ///< レギュレーションが異なる


// 通信の種類  
#define  COMM_MODE_TRADE    (0)     // 1on1 ポケモン交換
#define  COMM_MODE_BATTLE_SINGLE (1)    // 1vs1 バトル
#define  COMM_MODE_BATTLE_DOUBLE (2)    // 1vs1 ダブルバトル
#define  COMM_MODE_BATTLE_MIX_1ON1 (3)  // 1vs1 ミックスバトル
#define  COMM_MODE_BATTLE_MULTI (4)     // 2vs2 マルチバトル
#define  COMM_MODE_BATTLE_MIX_2ON2 (5)  // 2vs2 ミックスバトル
#define  COMM_MODE_NUT_CRASH (6)        // 2-5  木の実クラッシュ
#define  COMM_MODE_RECORD (7)           // 2-4  レコードコーナー
#define  COMM_MODE_CONTEST (8)           // 2-4  コンテスト
#define  COMM_MODE_UNION (9)            // ユニオンルーム
#define  COMM_MODE_UNDERGROUND (10)      // 16  地下
#define  COMM_MODE_POLLOCK4 (11)           // 4人ポロック
#define  COMM_MODE_POLLOCK16 (12)           // 16人ポロック
#define  COMM_MODE_PICTURE (13)            // ユニオンルーム->お絵かき
#define  COMM_MODE_POKETCH (14)            // ぽけっち
#define  COMM_MODE_MYSTERY (15)            // 不思議通信
#define  COMM_MODE_TOWER_MULTI (16)            // バトルタワーマルチ
#define  COMM_MODE_PARTY (17)          // パーティーゲームスキャン
#define  COMM_MODE_UNION_APP (18)            // ユニオンルームアプリケーション
#define  COMM_MODE_BATTLE_SINGLE_WIFI (19)    // 1vs1 WIFI バトル
#define  COMM_MODE_BATTLE_DOUBLE_WIFI (20)    // 1vs1 WIFI ダブル
#define  COMM_MODE_TRADE_WIFI (21)    // WIFI交換
#define  COMM_MODE_VCHAT_WIFI (22)    // WIFI VCT
#define  COMM_MODE_LOGIN_WIFI (23)    // WIFI LOGIN
#define  COMM_MODE_DPW_WIFI (24)    // DPW WIFI
#define  COMM_MODE_FUSIGI_WIFI (25)    // ふしぎ WIFI
#define  COMM_MODE_MAX (26)
#define  COMM_MODE_NONE (27)   // サービス切り替えを行わない時に使用

// 通信の種類 に対応した子機MIN数
#define  COMM_MODE_TRADE_NUM_MIN    (1)     // 1on1 ポケモン交換
#define  COMM_MODE_BATTLE_SINGLE_NUM_MIN (1)    // 1vs1 バトル
#define  COMM_MODE_BATTLE_DOUBLE_NUM_MIN (1)    // 1vs1 ダブルバトル
#define  COMM_MODE_BATTLE_MIX_1ON1_NUM_MIN (1)  // 1vs1 ミックスバトル
#define  COMM_MODE_BATTLE_MULTI_NUM_MIN (3)     // 2vs2 マルチバトル
#define  COMM_MODE_BATTLE_MIX_2ON2_NUM_MIN (3)  // 2vs2 ミックスバトル
#define  COMM_MODE_NUT_CRASH_NUM_MIN (1)        // 2-5  木の実クラッシュ
#define  COMM_MODE_RECORD_NUM_MIN (1)           // 2-4  レコードコーナー
#define  COMM_MODE_CONTEST_NUM_MIN (1)           // 2-4  コンテスト
#define  COMM_MODE_UNION_NUM_MIN (1)            // ユニオンルーム
#define  COMM_MODE_UNDERGROUND_NUM_MIN (1)      // 16  地下
#define  COMM_MODE_POLLOCK4_NUM_MIN (1)           // 4人ポロック
#define  COMM_MODE_POLLOCK16_NUM_MIN (1)           // 16人ポロック
#define  COMM_MODE_PICTURE_NUM_MIN (1)            // ユニオンルーム->お絵かき
#define  COMM_MODE_POKETCH_NUM_MIN (1)            // ぽけっち
#define  COMM_MODE_MYSTERY_NUM_MIN (1)            // 不思議通信
#define  COMM_MODE_TOWER_MULTI_NUM_MIN (1)            // バトルタワーマルチ
#define  COMM_MODE_PARTY_NUM_MIN (1)            // party
#define  COMM_MODE_UNION_APP_NUM_MIN (1)            // ユニオンルームAPP
#define  COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MIN (1)    // 1vs1 WIFIバトル
#define  COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MIN (1)    // 1vs1 WIFIバトル
#define  COMM_MODE_TRADE_WIFI_NUM_MIN (1)    // トレード
#define  COMM_MODE_VCHAT_WIFI_NUM_MIN (1)    // ボイスチャット
#define  COMM_MODE_LOGIN_WIFI_NUM_MIN (1)    // LOGINのみ
#define  COMM_MODE_DPW_WIFI_NUM_MIN (0)    // 世界交換,バトルタワー
#define  COMM_MODE_FUSIGI_WIFI_NUM_MIN (0)    // ふしぎWIFI

// 通信の種類 に対応した子機MAX数
#define  COMM_MODE_TRADE_NUM_MAX    (1)     // 1on1 ポケモン交換
#define  COMM_MODE_BATTLE_SINGLE_NUM_MAX (1)    // 1vs1 バトル
#define  COMM_MODE_BATTLE_DOUBLE_NUM_MAX (1)    // 1vs1 ダブルバトル
#define  COMM_MODE_BATTLE_MIX_1ON1_NUM_MAX (1)  // 1vs1 ミックスバトル
#define  COMM_MODE_BATTLE_MULTI_NUM_MAX (3)     // 2vs2 マルチバトル
#define  COMM_MODE_BATTLE_MIX_2ON2_NUM_MAX (3)  // 2vs2 ミックスバトル
#define  COMM_MODE_NUT_CRASH_NUM_MAX (3)        // 2-5  木の実クラッシュ
#define  COMM_MODE_RECORD_NUM_MAX (4)           // 2-4  レコードコーナー
#define  COMM_MODE_CONTEST_NUM_MAX (3)           // 2-4  コンテスト
#define  COMM_MODE_UNION_NUM_MAX (4)            // ユニオンルーム
#define  COMM_MODE_UNDERGROUND_NUM_MAX (COMM_CHILD_MAX)      // 16  地下
#define  COMM_MODE_POLLOCK4_NUM_MAX (3)           // 4人ポロック
#define  COMM_MODE_POLLOCK16_NUM_MAX (COMM_CHILD_MAX)           // 16人ポロック
#define  COMM_MODE_PICTURE_NUM_MAX (COMM_MODE_UNION_NUM_MAX)            // ユニオンルーム->お絵かき
#define  COMM_MODE_POKETCH_NUM_MAX (1)           // ぽけっち
#define  COMM_MODE_MYSTERY_NUM_MAX (4)           // 不思議通信
#define  COMM_MODE_TOWER_MULTI_NUM_MAX (1)            // バトルタワーマルチ
#define  COMM_MODE_PARTY_NUM_MAX (1)           // party
#define  COMM_MODE_UNION_APP_NUM_MAX (4)           // unionapp
#define  COMM_MODE_BATTLE_SINGLE_WIFI_NUM_MAX (1)    // 1vs1 WIFI バトル
#define  COMM_MODE_BATTLE_DOUBLE_WIFI_NUM_MAX (1)    // 1vs1 WIFI バトル
#define  COMM_MODE_TRADE_WIFI_NUM_MAX (1)    // トレード
#define  COMM_MODE_VCHAT_WIFI_NUM_MAX (1)    // ボイスチャット
#define  COMM_MODE_LOGIN_WIFI_NUM_MAX (1)    // LOGINのみ
#define  COMM_MODE_DPW_WIFI_NUM_MAX (0)    // 世界交換,バトルタワー
#define  COMM_MODE_FUSIGI_WIFI_NUM_MAX (0)    // ふしぎWIFI


// バトルレギュレーションの種類  
#define  COMM_REG_NORMAL     (0)
#define  COMM_REG_FANCY      (1)
#define  COMM_REG_YELLOW     (2)
#define  COMM_REG_PEARL      (3)
#define  COMM_REG_DIAMOND    (4)
#define  COMM_REG_ORIGINAL1  (5)
#define  COMM_REG_ORIGINAL2  (6)
#define  COMM_REG_ORIGINAL3  (7)
#define  COMM_REG_ORIGINAL4  (8)
#define  COMM_REG_ORIGINAL5  (9)
#define  COMM_REG_ORIGINAL6  (10)
#define  COMM_REG_ORIGINAL7  (11)
#define  COMM_REG_ORIGINAL8  (12)
#define  COMM_REG_ORIGINAL9  (13)
#define  COMM_REG_MAX        (14)


#define CURRENT_PLAYER_WORD_IDX    (0)    // 自分の名前を入れるバッファの場所
#define TARGET_PLAYER_WORD_IDX     (1)     // 対象となる名前を入れるバッファの場所
#define ASSAILANT_PLAYER_WORD_IDX  (2)     // 被害者となる名前を入れるバッファの場所


#define CC_NOT_FOUND_PARENT_INFO (0) // 親機情報がない場合  
#define CC_BUSY_STATE  (1)  //通信の内部状態が遷移中で、接続にいけない場合
#define CC_CONNECT_STARTING (2) // 接続関数を呼び出したら


// MYSTATUSを送るための領域
#define COMM_SEND_MYSTATUS_SIZE   (32)
#define COMM_SEND_REGULATION_SIZE (32)

#endif// _COMM_DEF_H_

