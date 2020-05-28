//============================================================================================
/**
 * @file	randomgroup.c
 * @brief	乱数の種グループソース
 * @author	mori GAME FREAK inc.
 * @date	2006.03.22
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/randomgroup.h"
#include "randomgroup_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"

//============================================================================================
//============================================================================================


RANDOM_GROUP * DebugRandomGroupPtr;


//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態保持ワークのサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int RandomGroup_GetWorkSize(void)
{
	return sizeof(RANDOM_GROUP);
}

//==============================================================================
/**
 * $brief   ランダムグループ内でのコピー（データ全体のコピーではない）
 *
 * @param   randomgroup		
 * @param   from		
 * @param   to		
 *
 * @retval  none		
 */
//==============================================================================
void RandomGroup_Copy( RANDOM_GROUP *randomgroup, int from, int to )
{
	randomgroup->group[to] = randomgroup->group[from];
}


//==============================================================================
/**
 * $brief   ランダムグループ初期化
 *
 * @param   randomgroup		
 *
 * @retval  none		
 */
//==============================================================================
void RandomGroup_Init(RANDOM_GROUP * randomgroup )
{
	int i;
	
	MI_CpuClearFast(randomgroup, sizeof(RANDOM_GROUP));

	for(i=0;i<RANDOMGROUP_MAX;i++){
		randomgroup->group[i].group_name[0] = EOM_;
		randomgroup->group[i].name[0]       = EOM_;
	}

	DebugRandomGroupPtr = randomgroup;
	
}

//==============================================================================
/**
 * @brief	乱数の種更新処理
 *
 * @param	randomgroup
 * @param	days			日数経過
 *
 * 日数経過の回数だけランダムのタネを更新する。
 */
//==============================================================================
void RandomGroup_Update(RANDOM_GROUP * randomgroup, u32 days)
{
	u32 no, times;
	for (no = 0; no < RANDOMGROUP_MAX; no++) {
		for (times = 0; times < days; times++) {
			//RandomGroup_SetRandom(randomgroup, no);
			randomgroup->group[no].random = gf_fix_rand( randomgroup->group[no].random );
		}
	}
}

//==============================================================================
/**
 * $brief   乱数の種取得(ほとんど呼ばないだろう）
 *
 * @param   randomgroup		
 * @param   no		
 *
 * @retval  u32		
 */
//==============================================================================
u32  RandomGroup_GetRandomSeed( RANDOM_GROUP* randomgroup, int no )
{
	return randomgroup->group[no].seed;
}

//==============================================================================
/**
 * $brief   乱数の種の設定（乱数グループを作成した時に一回だけ呼ぶ）
 *
 * @param   randomgroup		乱数グループ構造体
 * @param   no				何番目か
 * @param   seed			初期値
 *
 * @retval  u32		
 */
//==============================================================================
void  RandomGroup_SetRandomSeed( RANDOM_GROUP* randomgroup, int no, u32 seed )
{
	// 乱数の種を格納（２度と更新しない）
	randomgroup->group[no].seed = seed;

	// 乱数を格納しておく
	randomgroup->group[no].random = gf_fix_rand( seed );

}

//==============================================================================
/**
 * $brief   一日一回変わる乱数値を取得
 *
 * @param   randomgroup		
 * @param   no				
 *
 * @retval  u32		
 */
//==============================================================================
u32  RandomGroup_GetRandom( RANDOM_GROUP* randomgroup, int no )
{
	return randomgroup->group[no].random;
}

//==============================================================================
/**
 * @brief   一日一回変わる乱数値を取得（デフォルト）
 *
 * @param	randomgroup
 *
 * @return	u32
 *
 * 基本的にゲーム内で参照する「乱数のタネ」はこの関数によって取得する。
 */
//==============================================================================
u32  RandomGroup_GetDefaultRandom( RANDOM_GROUP* randomgroup )
{
	return randomgroup->group[RANDOMGROUP_MYUSE].random;
}

//==============================================================================
/**
 * $brief   乱数更新(１日１回更新する）
 *          現在保持している乱数の値が新しい乱数の種なので外からパラメータは貰わない
 *
 * @param   randomgroup		
 * @param   no				
 *
 * @retval  none			
 */
//==============================================================================
void RandomGroup_SetRandom( RANDOM_GROUP* randomgroup, int no )
{
	u32 temp = randomgroup->group[no].random;
	randomgroup->group[no].random = gf_fix_rand( randomgroup->group[no].random );

	OS_TPrintf("乱数更新 no=%d from=%08x, to=%08x\n",no,temp,randomgroup->group[no].random);
}


//==============================================================================
/**
 * $brief   グループ名・もしくはリーダー名のポインタ取得
 *
 * @param   randomgroup		
 * @param   no		
 * @param   type		
 *
 * @retval  const STRCODE *		
 */
//==============================================================================
const STRCODE *RandomGroup_GetNamePtr( const RANDOM_GROUP *randomgroup, int no, int type )
{
	if(type==RANDOMGROUP_NAME_GROUP){
		return randomgroup->group[no].group_name;
	}
	return randomgroup->group[no].name;

}

//==============================================================================
/**
 * $brief   グループ名・またはリーダー名のセット
 *
 * @param   randomgroup		
 * @param   no		
 * @param   type		
 * @param   str		
 *
 * @retval  none		
 */
//==============================================================================
void  RandomGroup_SetName( RANDOM_GROUP *randomgroup, int no, int type, STRBUF *str )
{
	STRCODE *name;

	if(type==RANDOMGROUP_NAME_GROUP){
		name = randomgroup->group[no].group_name;
		STRBUF_GetStringCode( str, name, GROUP_NAME_SIZE + EOM_SIZE );
	}else{
		name = randomgroup->group[no].name;
		STRBUF_GetStringCode( str, name, PERSON_NAME_SIZE + EOM_SIZE );
	}
	
}

//==============================================================================
/**
 * @brief	性別をセットする
 *
 * @param   randomgroup		
 * @param   no		
 */
//==============================================================================
void RandomGroup_SetSex( RANDOM_GROUP *randomgroup, int no, int sex)
{
	randomgroup->group[no].sex = sex;
}

//==============================================================================
/**
 * @brief	性別を取得する
 *
 * @param   randomgroup		
 * @param   no		
 * @return	int		性別コード
 */
//==============================================================================
int RandomGroup_GetSex( const RANDOM_GROUP *randomgroup, int no)
{
	return randomgroup->group[no].sex;
}

//==============================================================================
/**
 * @brief	リージョンコードを取得する
 *
 * @param   randomgroup		
 * @param   no		
 * @return	int		リージョンコード
 */
//==============================================================================
int RandomGroup_GetRegionCode( const RANDOM_GROUP *randomgroup, int no)
{
	return randomgroup->group[no].region_code;
}

//==============================================================================
/**
 * @brief	リージョンコードをセットする
 *
 * @param   randomgroup		
 * @param   no		
 */
//==============================================================================
void RandomGroup_SetRegionCode( RANDOM_GROUP *randomgroup, int no, int region_code )
{
	randomgroup->group[no].region_code = region_code;
}

//==============================================================================
/**
 * $brief   乱数の種グループのポインタを返す
 *
 * @param   sv		
 *
 * @retval  RANDOM_GROUP *		
 */
//==============================================================================
RANDOM_GROUP *SaveData_GetRandomGroup(SAVEDATA * sv)
{
	return (RANDOM_GROUP *)SaveData_Get(sv, GMDATA_ID_RANDOMGROUP);
}


//==============================================================================
/**
 * @brief	グループデータの存在チェック
 *
 * @param   randomgroup		
 * @param   no				チェックするデータのID
 * @retval	TRUE			存在する
 * @retval	FALSE			存在しない
 */
//==============================================================================
BOOL RandomGroup_ExistCheck(const RANDOM_GROUP * rg, int no)
{
	const RANDOM_SEED * rs = &rg->group[no];
	return !(RandomGroup_IsNullData(rs));
}

//==============================================================================
/**
 * @brief	グループデータが自分の登録しているデータかどうかのチェック
 *
 * @param   randomgroup		
 * @param   no				比較するデータのID
 * @retval	TRUE			一致した
 * @retval	FALSE			一致しない
 */
//==============================================================================
BOOL RandomGroup_EntryCheck(const RANDOM_GROUP * rg, int no)
{
	const RANDOM_SEED * rs1, * rs2;
	rs1 = &rg->group[RANDOMGROUP_MYUSE];
	rs2 = &rg->group[no];
	return RandomGroup_Compare(rs1, rs2);
}

//==============================================================================
/**
 * @brief	指定したグループ名が存在するかどうかのチェック
 * @param	rg
 * @param	group_name
 * @return	BOOL	TRUEのとき、一致する名前がある
 */
//==============================================================================
BOOL RandomGroup_SameGroupNameCheck(const RANDOM_GROUP * rg, const STRCODE * group_name)
{
	int index;
	const RANDOM_SEED * rs;

	if (*group_name == EOM_) {
		//名前が存在しない
		return FALSE;
	}
	for (index = 0; index < RANDOMGROUP_MAX; index ++ ) {
		rs = &rg->group[index];
		if (!PM_strncmp(group_name, rs->group_name, GROUP_NAME_SIZE + EOM_SIZE)) {
			return TRUE;
		}
	}
	return FALSE;
}

//============================================================================================
//
//		ランダムグループ内部でのみ使用する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	データが存在するかどうかのチェック
 * @param	rs
 * @retval	TRUE	存在しない
 * @retval	FALSE	存在する
 */
//----------------------------------------------------------
BOOL RandomGroup_IsNullData(const RANDOM_SEED * rs)
{
	if (rs->group_name[0] == EOM_) {
		return TRUE;
	}
	if (rs->name[0] == EOM_) {
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	ランダムのタネが同じかどうかをチェック
 * @param	s1			ランダムのタネその１
 * @param	s2			ランダムのタネその２
 * @retval	TRUE		一致した
 * @retval	FALSE		違うデータだった
 */
//----------------------------------------------------------
BOOL RandomGroup_Compare(const RANDOM_SEED * s1, const RANDOM_SEED * s2)
{
	int i;
	if (PM_strncmp(s1->name, s2->name, PERSON_NAME_SIZE + EOM_SIZE)) {
		return FALSE;
	}
	if (PM_strncmp(s1->group_name, s2->group_name, GROUP_NAME_SIZE + EOM_SIZE)) {
		return FALSE;
	}
	if (s1->sex != s2->sex) {
		return FALSE;
	}
	if (s1->region_code != s2->region_code) {
		return FALSE;
	}
	if (s1->seed != s2->seed) {
		return FALSE;
	}
	/*
	 * if (s1->random != s2->random) {
	 *		ここはどうしよう…
	 * }
	 */
	return TRUE;
}

