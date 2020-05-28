//=============================================================================
/**
 * @file	comm_command_field.h
 * @brief	通信のコマンド一覧  フィールド用
 * @author	Katsumi Ohno
 * @date    2005.11.07
 */
//=============================================================================

#ifndef __COMM_COMMAND_FIELD_H__
#define __COMM_COMMAND_FIELD_H__

#include "communication/comm_command.h"






/// フィールド専用通信コマンドの定義。
enum CommCommandField_e {
  CF_PLAYER_POS = CS_COMMAND_MAX,              ///< プレーヤーの座標を送る
  CF_PLAYER_POS_ID,           ///< 指定のプレーヤーの座標を送る
  CF_NPC_TALK,                  ///<  NPCとの会話
  CF_OTHER_TALK,              ///< NPCと会話
  CF_OTHER_TALK_SERVER_SIDE,  ///< NPCと会話サーバー側
  CF_CHECK_FIELDMENU_OPEN,    ///< フィールドメニューを開いていいか問い合わせ
  CF_CHECK_ABUTTON_ACTION,    ///< Ａボタンで何が発生するのか問い合わせ
  CF_RESULT_FIELDMENU_OPEN,   ///< フィールドメニューを開いていいか結果を返す
  CF_RESULT_UGMENU_OPEN,      ///< 炭鉱メニューを開いていいか結果を返す
  CF_PLAYER_INIT_END,      ///< 初期化転送を終えた場合
  CF_TRAP_DATA,               ///< １個の罠データ設置
  CF_TRAP_DATA_DEL,           ///< 罠データの削除
  CF_TRAP_DATA_RESULT,        ///< 罠データの結果を返す
  CF_TRAP_ARRAY_DATA,         ///< 連続したデータの１個の罠データ
  CF_TRAP_ARRAY_RESULT,       ///< 罠データを受け取った結果を返す
  CF_TRAP_START,      ///< 罠にかかる。罠が起動する
  CF_TRAP_SECOND_START,      ///< 2回目のスタート  罠が実行される
  CF_TRAP_SECOND_START_RET,      ///< 2回目のスタート  罠が実行される
  CF_TRAP_PRIEND,     ///< 仮終了を子機につたえる  本当の終了はしない
  CF_TRAP_END,        ///< 子機側が罠を管理していて終了した場合親機にそれを伝える
  CF_TRAP_END_RESULT, ///< 親に来た罠解除を子機に再転送
  CF_TRAP_END_FORCE,  ///< 強制終了
  CF_TRAP_RELEASE,    ///< 罠解除
  CF_TRAP_NOWARRAY,   ///< 今罠にかかっている人を送信
  CF_TRAP_RADAR_REQ,   ///< 天然レーダー表示REQ
  CF_TRAP_RADAR_ANS,   ///< 天然レーダー表示ANS
  CF_TOUCH_GROUND,    ///< 地面をタッチする
  CF_TOUCH_RESULT1,    ///< 地面をタッチした結果を返す1
  CF_TOUCH_RESULT2,    ///< 地面をタッチした結果を返す2
  CF_TRAP_DEFUSE,     ///< 罠解除
  CF_PLAYER_DELETE,   ///< プレーヤーの消去
  CF_SECRETBASE_DATA,             ///< 秘密基地データひとつ分
  CF_SECRETBASE_DATA_SERVER,             ///< 秘密基地データひとつ分（サーバーから送信）-
  CF_SECRETBASE_POS,        ///< 秘密基地入り口位置
  CF_SECRETBASE_JUMP_END,  ///< 秘密基地移動が終了したことを返す
  CF_SECRETBASE_RETJUMP,  ///< 秘密基地から帰る移動を行う
  CF_SECRETBASE_EVENT_START,  ///< 秘密基地に入る、または抜けるイベント開始S->C
  CF_SECRETBASE_EVENT_RES,  ///< 秘密基地に入る、または抜けるイベント結果C->S
  CF_SECRETBASE_GOODS_CHECK, ///< Aボタンでグッズのチェックがあった
  CF_SECRETBASE_MOVE_FAILED,  ///< 移動に失敗した
  CF_MOVE_CONTROL,        ///< 移動コントロール状態を送信する
  CF_DIG_STONE_PICKUP,      ///< 石を拾うかもしれない（クライアントで確認してもらう為の要求コマンド）
  CF_FIND_FOSSIL,             ///< 化石発見
  CF_DIG_FOSSIL_START_REQ,       ///< 化石発掘開始リクエスト
  CF_DIG_FOSSIL_START,       ///< 化石発掘開始
  CF_DIG_FOSSIL_END_REQ,     ///< 化石発掘終了リクエスト
  CF_DIG_FOSSIL_POS,    ///< 掘った場所を親に送る
  CF_DIG_FOSSIL_POS_RETURN,    ///< 掘った場所を子に送る
  CF_DIG_FOSSIL_INIT,       ///< 化石を掘っていることを親に通知
  CF_DIG_FOSSIL_PCRADAR,      ///< パソコン化石レーダー起動
  CF_DIG_FOSSIL_PCRADAR_ANS,  ///< パソコン化石レーダーの答え
  CF_ASKSEQ_SET,           ///< 会話状態を変更する
  CF_TALKSEQ_SET,          ///< 話しかけられ状態を変更する
  CF_ASKSEQ_SET_CALL,           ///< 会話状態を変更する(SERVERから戻り)
  CF_TALKSEQ_SET_CALL,          ///< 話しかけられ状態を変更する(SERVERから戻り)
  CF_SEND_ITEM,             ///< アイテムを送る
  CF_SEND_ITEM_CALL,        ///< アイテムを送るコマンドの戻り(SERVERから戻り)
  CF_SECRET_QUESTION,       ///< 秘密の質問
  CF_SECRET_QUESTION_CALL,  ///< 秘密の質問 (SERVERから戻り)
  CF_TARGET_RECORD,         ///< 話し相手のレコード情報を送る
  CF_TARGET_RECORD_CALL,    ///< 話し相手のレコード情報を送る
  CF_PC_ACCESS,            ///< パソコンの前でAボタンを押した場合(SERVERから戻り)
  CF_FLAG_STATE,           ///< 旗状態が変化したことをサーバーに送信
  CF_FLAG_STATE_RET,       ///< 旗状態の変化をサーバーから一斉送信
  CF_DRILL_START,          ///< 秘密基地を掘る
  CF_DRILL_START_RESULT,   ///< 秘密基地をほれるかどうかを返す
  CF_TRAINER_CARD,         ///< トレーナーカードを送る
  CF_GET_FLAG,            ///< パソコンからハタが取れるかどうか再度確認
  CF_GET_FLAG_RET,        ///< パソコンからハタが取れたら返信
  CF_FLAG_NOWARRAY_REQ,   ///< 現状のハタ情報要求
  CF_FLAG_NOWARRAY,       ///< 現状のハタ情報を送る
  CF_FLAG_NOWARRAY_END,   ///< 現状のハタ情報終わり
  CF_DIRECT_START_SET,    ///< ダイレクトコーナースタート位置セット
  CF_DIRECT_STARTPOS,     ///< ダイレクトコーナースタート位置
  CF_LVUP_FLAG,           ///< パソコンLVUP
  CF_LVUP_FLAG_RET,       ///< パソコンLVUP
  
  //------------------------------------------------ここからユニオンルーム用コマンド

  CU_PLAYER_STATUS,		///< ステータスの送信
  CU_PLAYER_SELECT,		///< 選択内容の送信（こうかん・チャット・カード・たいせん・やめたい）
  CU_TALK_TALK,			///< 会話データの送信
  CU_BATTLE_PLIST_RET,	///< 戦闘前ポケモンリストの選択結果（選択した・キャンセルした）
  CU_TALK_NO,			///< いいえ
  CU_START_NEXT,		///< 交換・戦闘・チャット・カードへの移動開始
  CU_END_CONNECT_SERVER,///< 親機が通信切断を通知		
  CU_TRAINER_CARD,		///< トレーナーカードデータを受信

  //------------------------------------------------ここからミックスバトル用コマンド

  CF_MIXBATTLE,			///< ミックスバトル（相手メンバーが送られてくる）
  CF_MIXBATTLE_TRADE,	///< ミックスバトル（交換ポケモンのインデックスが送られてくる）


  //------------------------------------------------ここまで

  //------------------------------------------------ここからレコードコーナー用

  CR_RECORD_YES,							///< はい
  CR_RECORD_NO,								///< いいえ
  CR_RECORD_STOP,							///< 乱入者が来たので一旦ストップ
  CR_RECORD_RESTART,						///< 乱入者処理が終わったので再会
  CR_RECORD_END_CHILD,						///< 子機が離脱
  CR_RECORD_END,							///< 終了
  CR_RECORD_CHILD_JOIN,						///< 子機が乱入を宣言
  CR_RECORD_START,							///< 親機がレコード開始を通達
  CR_RECORD_DATA,  							///< レコードデータ送信
  CR_RECORD_BAN,							///< 離脱禁止・許可
  //------------------------------------------------ここまで

  //------------------------------------------------ここからお絵かきボード専用通信コマンド

  CO_OEKAKI_GRAPHICDATA, 					///< みんなで描いていた画像データ
  CO_OEKAKI_LINEPOS,						///< タッチパネルで取得したポジションデータ
  CO_OEKAKI_LINEPOSSERVER,					///< タッチパネルで取得したポジションデータ
  CO_OEKAKI_YES,							///< はい
  CO_OEKAKI_NO,								///< いいえ
  CO_OEKAKI_STOP,							///< 乱入者が来たので一旦ストップ
  CO_OEKAKI_RESTART,						///< 乱入者処理が終わったので再会
  CO_OEKAKI_END_QUESTION,					///< 終了
  CO_OEKAKI_END_CHILD,						///< 子機が離脱
  CO_OEKAKI_END,							///< 終了
  CO_OEKAKI_CHILD_JOIN,						///< 子機が乱入を宣言
  CO_OEKAKI_OUT_CONTROL,				    ///< 離脱禁止信号
  
  //------------------------------------------------ここまで


  CF_COMMAND_MAX   // 終端--------------これは移動させないでください
};

extern void CommCommandFieldInitialize(void* pWork);
extern int _getRecordSize(void);
extern int _getPictureSize(void);
extern int _getLinePosSize(void);
extern int _getLinePosServerSize(void);
extern void CommDummyCallBack( int netID, int size, void* pBuff, void* pWork );













#endif// __COMM_COMMAND_FIELD_H__

