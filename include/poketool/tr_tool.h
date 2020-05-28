
//============================================================================================
/**
 * @file	tr_tool.h
 * @bfief	トレーナーデータツール郡
 * @author	HisashiSogabe
 * @date	05.12.14
 */
//============================================================================================

#ifndef	__TR_TOOL_H_
#define	__TR_TOOL_H_

//トレーナーメッセージの表示条件定義
#define	TRMSG_FIGHT_START				(0)		//戦闘開始前
#define	TRMSG_FIGHT_LOSE				(1)		//戦闘負け
#define	TRMSG_FIGHT_AFTER				(2)		//戦闘後
#define	TRMSG_FIGHT_START_1				(3)		//戦闘開始前（2vs2トレーナーのデータ1個目）
#define	TRMSG_FIGHT_LOSE_1				(4)		//戦闘負け（2vs2トレーナーのデータ1個目）
#define	TRMSG_FIGHT_AFTER_1				(5)		//戦闘後（2vs2トレーナーのデータ1個目）
#define	TRMSG_POKE_ONE_1				(6)		//ポケモン1体（2vs2トレーナーのデータ1個目）
#define	TRMSG_FIGHT_START_2				(7)		//戦闘開始前（2vs2トレーナーのデータ2個目）
#define	TRMSG_FIGHT_LOSE_2				(8)		//戦闘負け（2vs2トレーナーのデータ2個目）
#define	TRMSG_FIGHT_AFTER_2				(9)		//戦闘後（2vs2トレーナーのデータ2個目）
#define	TRMSG_POKE_ONE_2				(10)	//ポケモン1体（2vs2トレーナーのデータ2個目）
#define	TRMSG_FIGHT_NONE_DN				(11)	//昼夜、戦闘しない時
#define	TRMSG_FIGHT_NONE_D				(12)	//昼、戦闘しない時
#define	TRMSG_FIGHT_FIRST_DAMAGE		(13)	//戦闘中：相手ポケモンに最初のダメージを与えたとき
#define	TRMSG_FIGHT_POKE_HP_HALF		(14)	//戦闘中：相手ポケモンのＨＰ半分以下
#define	TRMSG_FIGHT_POKE_LAST			(15)	//戦闘中：相手ポケモンが残り１匹
#define	TRMSG_FIGHT_POKE_LAST_HP_HALF	(16)	//戦闘中：相手ポケモンが残り１匹でＨＰ半分以下
#define	TRMSG_REVENGE_FIGHT_START		(17)	//フィールド：再戦：対戦前
#define	TRMSG_REVENGE_FIGHT_START_1		(18)	//フィールド：再戦：対戦前：右
#define	TRMSG_REVENGE_FIGHT_START_2		(19)	//フィールド：再戦：対戦前：左

#define	TRMSG_FIGHT_WIN					(100)	//戦闘勝ち（戦闘内でのみ使用される）

//トレーナーデータを取得するときのID定義
#define	ID_TD_data_type		(0)		//データタイプ
#define	ID_TD_tr_type		(1)		//トレーナー分類
#define	ID_TD_tr_gra		(2)		//トレーナーグラフィック
#define	ID_TD_poke_count	(3)		//所持ポケモン数
#define	ID_TD_use_item1		(4)		//使用道具1
#define	ID_TD_use_item2		(5)		//使用道具2
#define	ID_TD_use_item3		(6)		//使用道具3
#define	ID_TD_use_item4		(7)		//使用道具4
#define	ID_TD_aibit			(8)		//AIパターン
#define	ID_TD_fight_type	(9)		//戦闘タイプ（1vs1or2vs2）

//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

extern	void	TT_EncountTrainerDataMake(BATTLE_PARAM *bp,const SAVEDATA * sv,int heapID);
extern	u32		TT_TrainerDataParaGet(int tr_id,int id);
extern	BOOL	TT_TrainerMessageCheck(int tr_id,int kindID,int heapID);
extern	void	TT_TrainerMessageGet(int tr_id,int msgID,STRBUF *msg,int heapID);
extern	void	TT_TrainerDataGet(int tr_id,TRAINER_DATA *td);
extern	void	TT_TrainerPokeDataGet(int tr_id,void *tpd);
extern	u8		TT_TrainerTypeSexGet(int trtype);

#endif	__ASM_NO_DEF_

#endif	__TR_TOOL_H_

