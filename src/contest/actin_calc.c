//==============================================================================
/**
 * @file	actin_calc.c
 * @brief	演技力部門：技効果計算など
 * @author	matsuda
 * @date	2005.12.07(水)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "actin_order.h"
#include "actin_id.h"
#include "actin_input.h"
#include "actin_calc.h"
#include "con_tool.h"

#include "poketool/waza_tool.h"



//==============================================================================
//	データ
//==============================================================================
///コンテストタイプによる出した技のタイプとのボルテージゲージの上下
ALIGN4 static const s8 ConTypeVoltageTbl[][5] = {
//かっこいい、美しい、かわいい、賢い、たくましい
	{VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0},	//かっこいい
	{0, VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT},	//美しい
	{-VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT},	//かわいい
	{-VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT, 0},	//賢い
	{0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT},	//たくましい
};



//--------------------------------------------------------------
/**
 * @brief   技番号から基本アピールポイントを取得する
 * @param   wazano		技番号
 * @retval  基本アピールポイント
 */
//--------------------------------------------------------------
int ACALC_BaseAppealGet(int wazano)
{
	int appeal_no, ap_point;
	
	appeal_no = WT_WazaDataParaGet(wazano, ID_WTD_ap_no);
	ap_point = ConTool_GetAPWaza_App(appeal_no);
	return ap_point;
}

//--------------------------------------------------------------
/**
 * @brief   指定したブリーダーが選んだ審判を、他に何人指名しているか調べる
 *
 * @param   a_game				演技力ゲーム進行パラメータへのポインタ
 * @param   check_breeder		調べるブリーダーのNo
 *
 * @retval  指名が被った人数(被らなかった場合は0)
 */
//--------------------------------------------------------------
int ACALC_JudgeSufferCheck(ACTIN_GAME_PARAM *a_game, int check_breeder)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < BREEDER_MAX; i++){
		if(a_game->judge_no[i] == a_game->judge_no[check_breeder]){
			count++;
		}
	}
	count--;	//自分の分を引く
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   審判指名が被った人数によって発生するアピールポイントを取得する
 * @param   suffer_num		被った人数
 * @retval  取得出来るアピールポイント
 */
//--------------------------------------------------------------
int ACALC_JudgeSufferPointCheck(int suffer_num)
{
	static const u8 JudgeSufferAddPoint[] = {
		3 * APPEAL_ICON_ONE_POINT,
		2 * APPEAL_ICON_ONE_POINT,
		1 * APPEAL_ICON_ONE_POINT,
		0 * APPEAL_ICON_ONE_POINT,
	};
	
	return JudgeSufferAddPoint[suffer_num];
}

//--------------------------------------------------------------
/**
 * @brief   出した技によってボルテージがいくつ増減するか取得する
 *
 * @param   contest_type		現在参加中のコンテストタイプ
 * @param   wazano				技番号
 * @param   judge_no			選んだ審判の番号
 * @param   special_judge_no	凄い審判の番号
 *
 * @retval  ボルテージ増減値
 */
//--------------------------------------------------------------
int ACALC_VoltageUpDownCheck(int contest_type, int wazano, int judge_no, int special_judge_no)
{
	int waza_con_type;
	int point;
	
	waza_con_type = WT_WazaDataParaGet(wazano, ID_WTD_contype);
	point = ConTypeVoltageTbl[contest_type][waza_con_type];
#if 0	//凄い審判でも＋１のままになった 2006.03.11(土)
	if(judge_no == special_judge_no){
		point *= 2;
	}
#endif
	return point;
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーソートを実行
 *
 * @param   a_game		演技力ゲーム進行パラメータへのポインタ
 */
//--------------------------------------------------------------
//順番操作後攻指定した場合にソート操作用に入れる仮AP
//(通常では取得しきれない程の値を入れる事で後ろに行くようにしている)
ALIGN4 static const s16 NextSortSpecifyEndAP[] = {29970, 29980, 29990, 30000};
//順番操作先攻指定した場合にソート操作用に入れる仮AP
//(通常では取得しきれない程の値を入れる事で前に来るようにしている)
ALIGN4 static const s16 NextSortSpecifyFirstAP[] = {-30000, -29990, -29980, -29970};
//順番操作ランダム指定した場合にソート操作用に入れる仮AP
//(通常では取得しきれない程の値で、FirstとEndの中間を指定する事で、先攻、後攻操作に
//影響しない範囲の場所でランダムさせる)
ALIGN4 static const s16 NextSortRandomAP[] = {-10000, -500, 500, 10000};

void ACALC_BreederSort(ACTIN_GAME_PARAM *a_game)
{
	int i, j, t;
	s16 a[BREEDER_MAX];
	u8 b[BREEDER_MAX];
	u8 before_pos[BREEDER_MAX];
	
	//ソート用にテンポラリ領域にAP値とブリーダー番号を入れる
	for(i = 0; i < BREEDER_MAX; i++){
		a[i] = a_game->app_turn[i];
		b[i] = i;
		for(j = 0; j < BREEDER_MAX; j++){
			if(i == a_game->breeder_sort[j]){
				before_pos[i] = j;
				break;
			}
		}
	}
	
	//順番操作が実行されている場合は、任意の場所にうまくソートされるようにAP値を変更する
	{
		for(i = 0; i < BREEDER_MAX; i++){
			switch(a_game->wazapara.personal[i].next_sort){
			case AWK_SORT_NONE:
			default:
				break;
			case AWK_SORT_SPECIFY_FIRST:
				a[i] = NextSortSpecifyFirstAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("ブリーダー番号%d、順番操作(先攻)＝次ターン%d番目のアピール\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			case AWK_SORT_SPECIFY_END:
				a[i] = NextSortSpecifyEndAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("ブリーダー番号%d、順番操作(後攻)＝次ターン%d番目のアピール\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			case AWK_SORT_RANDOM:
				a[i] = NextSortRandomAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("ブリーダー番号%d、順番操作(ランダム)＝次ターン%d番目のアピール\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			}
		}
	}
	
	//AP値順にソート実行
	for(i = 0; i < BREEDER_MAX - 1; i++){
		for(j = BREEDER_MAX - 1; j > i; j--){
			if(a[j-1] > a[j] 
					|| (a[j-1] == a[j] && before_pos[j-1] < before_pos[j])){
				//AP値入れ替え
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
				//ブリーダー番号入れかえ
				t = b[j];
				b[j] = b[j-1];
				b[j-1] = t;
				//入れ替え前の順番入れ替え
				t = before_pos[j];
				before_pos[j] = before_pos[j-1];
				before_pos[j-1] = t;
			}
		}
	}
	
	//並び替えた結果をセット
	for(i = 0; i < BREEDER_MAX; i++){
		a_game->breeder_sort[i] = b[i];
		OS_TPrintf("順番%d：ブリーダー番号%d, ここまでの合計AP値=%d\n", 
			i, b[i], a_game->app_total[b[i]]);
	}
}

