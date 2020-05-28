//============================================================================================
/**
 * @file	randomgroup_local.h
 * @brief	ランダムグループ構造体定義
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================
#ifndef __RANDOMGROUP_LOCAL_H__
#define __RANDOMGROUP_LOCAL_H__

typedef struct{

	/// グループ名
	STRCODE 		group_name[GROUP_NAME_SIZE + EOM_SIZE];		// 16

	/// リーダー名
	STRCODE 		name[PERSON_NAME_SIZE + EOM_SIZE];			// 32

	///	リーダーの性別
	u8 sex;														// 33

	///	リーダーの言語コード
	u8 region_code;												// 34

	///	pudding
	u16 dummy;													// 36

	/// 乱数の種（新規登録時に作成）
	u32				seed;										// 40

	/// 乱数(1日1回更新）
	u32				random;										// 44

}RANDOM_SEED;

struct _RANDOM_GROUP{

	RANDOM_SEED	group[RANDOMGROUP_MAX];

};


extern BOOL RandomGroup_IsNullData(const RANDOM_SEED * rs);
extern BOOL RandomGroup_Compare(const RANDOM_SEED * s1, const RANDOM_SEED * s2);

#endif
