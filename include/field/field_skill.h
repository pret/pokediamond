//============================================================================================
/**
 * @file	field_skill.h
 * @brief	フィールド技処理（秘伝技など）
 * @author	Hiroyuki Nakamura
 * @date	2005.12.01
 */
//============================================================================================
#ifndef FIELD_SKILL_H
#define FIELD_SKILL_H
#undef GLOBAL
#ifdef FIELD_SKILL_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
// 技インデックス（ポケモンリストと同じ並びにすること！）
#define	FLD_SKILL_IAIGIRI		( 0 )		// いあいぎり
#define	FLD_SKILL_SORAWOTOBU	( 1 )		// そらをとぶ
#define	FLD_SKILL_NAMINORI		( 2 )		// なみのり
#define	FLD_SKILL_KAIRIKI		( 3 )		// かいりき
#define	FLD_SKILL_KIRIBARAI		( 4 )		// きりばらい
#define	FLD_SKILL_IWAKUDAKI		( 5 )		// いわくだき
#define	FLD_SKILL_TAKINOBORI	( 6 )		// たきのぼり
#define	FLD_SKILL_ROCKCLIMB		( 7 )		// ロッククライム
#define	FLD_SKILL_FLASH			( 8 )		// フラッシュ
#define	FLD_SKILL_TELEPORT		( 9 )		// テレポート
#define	FLD_SKILL_ANAWOHORU		( 10 )		// あなをほる
#define	FLD_SKILL_AMAIKAORI		( 11 )		// あまいかおり
#define	FLD_SKILL_OSYABERI		( 12 )		// おしゃべり

// 技使用ワークへの不完全型ポインタ
typedef struct SKILLUSE_WORK SKILLUSE_WORK;

// 技使用チェックワークへの不完全型ポインタ
typedef struct SKILLCHECK_WORK SKILLCHECK_WORK;

typedef int (*SKILLCHECK_FUNC)(const SKILLCHECK_WORK*);	// 技使用チェック関数

typedef void (*SKILLUSE_FUNC)(SKILLUSE_WORK*, const SKILLCHECK_WORK *);	// 技使用関数

// 技使用関数取得パラメータ
enum {
	FIELDSKILL_PRM_USEFUNC = 0,	// 使用関数
	FIELDSKILL_PRM_CHECKFUNC	// チェック関数
};

// 使用チェックの戻り値
enum {
	FIELDSKILL_USE_TRUE = 0,	// 使用可能
	FIELDSKILL_USE_FALSE,		// 使用不可（ここでは使えません）
	FIELDSKILL_NO_BADGE,		// 使用不可・バッジなし
	FIELDSKILL_COMPANION,		// 使用不可・連れ歩き
	FIELDSKILL_PLAYER_SWIM,		// 使用不可・なみのり中
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 使用関数取得
 *
 * @param	prm		取得パラメータ
 * @param	id		関数ID
 *
 * @return	使用関数
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 FieldSkill_FuncGet( u16 prm, u16 id );

//--------------------------------------------------------------------------------------------
/**
 * 使用チェックワーク作成
 *
 * @param	fsys	フィールドワーク
 * @param	id		チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void FieldSkill_CheckWorkMake( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk );




#undef GLOBAL
#endif	/* FIELD_SKILL_H */
