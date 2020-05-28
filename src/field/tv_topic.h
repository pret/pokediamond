//============================================================================================
/**
 * @file	tv_topic.h
 * @brief	テレビのトピック登録用ヘッダ
 * @date	2006.05.22
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__TV_TOPIC_H__
#define	__TV_TOPIC_H__

#include "field_common.h"

#include "poketool/poke_tool.h"
#include "field/tvtopic_battle.h"
#include "system/pms_data.h"

//============================================================================================
//
//
//		個別トピック用処理
//
//
//============================================================================================
//02-01,02-02	トピック生成：捕獲成功＆失敗
//--------------------------------------------------------------------
/**
 * @brief	テレビトピック生成：捕獲
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	tvwbw			テレビトピック用情報保持ワーク
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Capture(FIELDSYS_WORK * fsys,
		const TVWATCH_BATTLE_WORK * wcw_result, int win_lose_flag);

//02-03	トピック生成：世界を釣る！
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：世界を釣る！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	success_flag	成功したかどうか
 * @param	itemno			使用したつりざおのアイテムナンバー
 * @param	pp				釣り上げたポケモンのPOKEMON_PARAMへのポインタ
 *
 * 釣り上げられなかった場合、success_flag == FALSEでPP==NULLでよい
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Fishing(FIELDSYS_WORK * fsys, BOOL success_flag,
		u16 itemno, POKEMON_PARAM * pp);

//02-04	トピック生成：グループを入れ替える
extern void TVTOPIC_Entry_Watch_ChangeGroup(FIELDSYS_WORK * fsys);

//02-06	トピック生成：隠しアイテム発見
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：隠しアイテム発見！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	item_no		見つけたアイテムのナンバー
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_HideItem(FIELDSYS_WORK * fsys, u16 item_no);

//02-08	トピック生成：タマゴが孵った！
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：タマゴが孵った！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	孵ったポケモンへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_HatchEgg(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp);

//02-10	トピック生成：姓名判断
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：姓名判断	ニックネームを変更したとき
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	pp		名前を変えたポケモンへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_ChangeName(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp);

//02-13	トピック生成：地下化石掘り
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：化石掘り	化石掘りをしたあと
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	fossil_type		化石のアイテムナンバー
 * @param	fossil_num		取れた化石の数
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_DigFossil(FIELDSYS_WORK * fsys, int fossil_type, int fossil_num);

//02-15	トピック生成：サファリゲーム
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：サファリゲーム	サファリゲームを終了させたとき
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_Safari(FIELDSYS_WORK * fsys);

//02-17	トピック生成：良薬は口に苦し！	ポケモンに漢方薬をあげたとき
//tvtopic_extern.hにあります

//02-18,02-19,03-06	トピック生成：きのみ関連
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：きのみをとったとき
 * @param	fsys			フィールド制御ワークへのポインタ
 * @param	nuts_item_no	とったきのみのアイテムナンバー
 * @param	hp				とったときのHPの値
 * @param	nuts_count		とったきのみの数
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_TakeNuts(FIELDSYS_WORK  *fsys, u16 nuts_item_no, u8 hp, u16 nuts_count);

//02-20	トピック生成：グループを作る
extern void TVTOPIC_Entry_Watch_MakeGroup(FIELDSYS_WORK * fsys);

//02-21	トピック生成：カスタムボールセット
//field/tvtopic_extern.hにあります

//02-22	トピック生成：旗を持ち帰った！
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：旗を取った！		人の旗を持ち帰った！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	rival		相手のMYSTATUSへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_GetFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival);

//02-23	トピック生成：旗を持ち帰られた！
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：旗を取られた！		自分の旗を持ち帰られた！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	rival		相手のMYSTATUSへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Watch_LoseFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival);


//--------------------------------------------------------------------
/**
 * @brief	トピック生成：バトルタワー連勝
 * @param	fsys			フィールド制御ワークへのポインタ
 * @param	renshou			連勝数
 * @param	pp				先頭のポケモンへのポインタ
 * @param	IsSingleFlag	シングル戦かどうか
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_BTower(FIELDSYS_WORK * fsys,
		u32 renshou, POKEMON_PARAM * pp, BOOL IsSingleFlag);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：大きさ測定記録更新	大きさ測定で記録を更新したとき
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	size		記録
 * @param	pp			更新したポケモンへのポインタ
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_Ookisa(FIELDSYS_WORK * fsys, u32 size, POKEMON_PARAM * pp);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：スロット達人	スロットで一定枚数以上を稼いだとき
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	start_coin		開始時のコイン枚数
 * @param	end_coin		終了時のコイン枚数
 * @param	playtime		プレイ時間（分単位）
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_Slot(FIELDSYS_WORK * fsys, u32 start_coin, u32 end_coin, u32 playtime);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：ワナ解除名人	地下に入ったとき、たくさんのワナを解除したら作成
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	trap_no			最初に解除したワナのナンバー
 * @param	remove_count	ワナを解除した回数
 *
 * 地下に入ってから出るまでの間の回数です。一度出たらリセットされます。
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_RemoveTrap(FIELDSYS_WORK * fsys, u16 trap_no, u16 remove_count);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：ハタトリ名人
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	flag_count		旗を取った回数
 *
 * 地下に入ってから出るまでの間の回数です。一度出たらリセットされます。
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_Record_GetFlag(FIELDSYS_WORK * fsys, u16 flag_count);

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	トピック生成：バトルタワーインタビュー
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_BTower(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：あなたのポケモンインタビュー
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Pokemon(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：お気に入りのポケッチ
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Poketch(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：挑戦！コンテスト
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Contest(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：ポケモンクリップ！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Clip(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：性格診断！
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Character(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：ポルト料理
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Poruto(FIELDSYS_WORK * fsys, PMS_WORD word);

//--------------------------------------------------------------------
/**
 * @brief	トピック生成：ポケモン連れ歩き
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	word		簡易会話単語ID
 */
//--------------------------------------------------------------------
extern void TVTOPIC_Entry_QandA_Park(FIELDSYS_WORK * fsys, PMS_WORD word);

#endif	//__TV_TOPIC_H__
