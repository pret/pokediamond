//============================================================================================
/**
 * @file	pms_input_data.h
 * @bfief	簡易会話入力画面（カテゴリ・インデックス等のデータ管理）
 * @author	taya
 * @date	06.02.03
 */
//============================================================================================
#ifndef __PMS_INPUT_DATA_H__
#define __PMS_INPUT_DATA_H__

#include "application\pms_input.h"
#include "savedata\savedata_def.h"
#include "gflib\strbuf.h"


//--------------------------------------------------------------
/**
 *	データ管理オブジェクトの抽象型
 */
//--------------------------------------------------------------
typedef struct _PMS_INPUT_DATA  PMS_INPUT_DATA;


//--------------------------------------------------------------
/**
 *	カテゴリ
 */
//--------------------------------------------------------------
enum PMSI_CATEGORY_GROUP {
	CATEGORY_GROUP_POKEMON,
	CATEGORY_GROUP_POKEMON2,
	CATEGORY_GROUP_SKILL,
	CATEGORY_GROUP_SKILL2,
	CATEGORY_GROUP_STATUS,
	CATEGORY_GROUP_TRAINER,
	CATEGORY_GROUP_PERSON,
	CATEGORY_GROUP_GREET,
	CATEGORY_GROUP_LIFE,
	CATEGORY_GROUP_MIND,
	CATEGORY_GROUP_NANKAI,
	CATEGORY_GROUP_UNION,

	CATEGORY_GROUP_MAX,
};


enum PMSI_CATEGORY_INITIAL {
	CATEGORY_INITIAL_A,
	CATEGORY_INITIAL_I,
	CATEGORY_INITIAL_U,
	CATEGORY_INITIAL_E,
	CATEGORY_INITIAL_O,
	CATEGORY_INITIAL_KA,
	CATEGORY_INITIAL_KI,
	CATEGORY_INITIAL_KU,
	CATEGORY_INITIAL_KE,
	CATEGORY_INITIAL_KO,
	CATEGORY_INITIAL_SA,
	CATEGORY_INITIAL_SI,
	CATEGORY_INITIAL_SU,
	CATEGORY_INITIAL_SE,
	CATEGORY_INITIAL_SO,
	CATEGORY_INITIAL_TA,
	CATEGORY_INITIAL_TI,
	CATEGORY_INITIAL_TU,
	CATEGORY_INITIAL_TE,
	CATEGORY_INITIAL_TO,
	CATEGORY_INITIAL_NA,
	CATEGORY_INITIAL_NI,
	CATEGORY_INITIAL_NU,
	CATEGORY_INITIAL_NE,
	CATEGORY_INITIAL_NO,
	CATEGORY_INITIAL_HA,
	CATEGORY_INITIAL_HI,
	CATEGORY_INITIAL_HU,
	CATEGORY_INITIAL_HE,
	CATEGORY_INITIAL_HO,
	CATEGORY_INITIAL_MA,
	CATEGORY_INITIAL_MI,
	CATEGORY_INITIAL_MU,
	CATEGORY_INITIAL_ME,
	CATEGORY_INITIAL_MO,
	CATEGORY_INITIAL_YA,
	CATEGORY_INITIAL_YU,
	CATEGORY_INITIAL_YO,
	CATEGORY_INITIAL_RA,
	CATEGORY_INITIAL_RI,
	CATEGORY_INITIAL_RU,
	CATEGORY_INITIAL_RE,
	CATEGORY_INITIAL_RO,
	CATEGORY_INITIAL_WA,
	CATEGORY_INITIAL_OTHER,
};

// グループ・イニシャルのどのナンバーとも重複しない値（1byte）
enum {
	CATEGORY_POS_BACK    = 0xfe,	///< 「もどる」位置データ
	CATEGORY_POS_DISABLE = 0xff,	///< 無効位置データ
};


extern PMS_INPUT_DATA* PMSI_DATA_Create( u32 heapID, const PMSI_PARAM* savedata );
extern void PMSI_DATA_Delete( PMS_INPUT_DATA* pmsi );

extern u32  PMSI_DATA_GetGroupEnableWordCount( const PMS_INPUT_DATA* pmsi, u32 group );
extern void PMSI_DATA_GetGroupEnableWord( const PMS_INPUT_DATA* pmsi, u32 group, u32 word_idx, STRBUF* buf );
extern PMS_WORD  PMSI_DATA_GetGroupEnableWordCode( const PMS_INPUT_DATA* pmsi, u32 group, u32 word_idx );

extern u32  PMSI_DATA_GetInitialEnableWordCount( const PMS_INPUT_DATA* pmsi, u32 initial );
extern void PMSI_DATA_GetInitialEnableWord( const PMS_INPUT_DATA* pmsi, u32 initial, u32 word_idx, STRBUF* buf );
extern PMS_WORD PMSI_DATA_GetInitialEnableWordCode( const PMS_INPUT_DATA* pmsi, u32 initial, u32 word_idx );





//====================================================================================
// ボックス壁紙パスワード対応処理
//====================================================================================
extern int PMSI_DAT_GetBoxPwdMax(void);
extern int PMSI_DAT_WordToBoxPwdID( PMS_WORD word );


#endif
