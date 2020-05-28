//==============================================================================
/**
 * @file	actin_ai.c
 * @brief	演技力部門：AI
 * @author	matsuda
 * @date	2006.05.20(土)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tool.h"
#include "con_tool.h"
#include "poketool/waza_tool.h"


//==============================================================================
//	定数定義
//==============================================================================
///演技力AI：審判選択タイプ
enum{
	BRD_AI_JUDGE_SELECT_NULL,		///<指定なし
	BRD_AI_JUDGE_SELECT_THIS,		///<その審査員で決定
	BRD_AI_JUDGE_SELECT_BESIDES,	///<それ以外の審査員＋１
	BRD_AI_JUDGE_SELECT_LOW,		///<低い審査員で決定
};

///演技AI：対象技
enum{
	BRD_AI_TARGET_SAMETYPE = 0xf0,			///<同じタイプ(CONTYPE_???)の技
	BRD_AI_TARGET_HART_2_UP,				///<ハート2以上の技
};


//==============================================================================
//	構造体定義
//==============================================================================
///手持ち技1つごとが持つAI用のワーク
typedef struct{
	u16 wazano;		///<技番号
	s16 point;		///<ポイント
	s16 judge_point[JUDGE_MAX];		///<審判のポイント
	u8 ap_no;		///<技効果番号
	u8 con_type;	///<技のコンテストタイプ
}ACTIN_AI_WAZA;

///ブリーダー1人が持つAI用のワーク
typedef struct{
	ACTIN_AI_WAZA ai_waza[WAZA_TEMOTI_MAX];	///<手持ち技パラメータ
	u8 character;		///<ブリーダーの性格
}ACTIN_AI_WORK;

///AIデータテーブル
typedef struct{
	u8 sort_pos;		///<順番(ブリーダーの位置と一致した時、この条件式の関数が実行される)
	u8 tbl_no;			///<条件式のテーブル番号
	u8 target_ap_no;	///<対象技(技効果番号(ap_no)で対象が設定されています)
	s8 judge_select;	///<審判選択タイプ

	s16 add_point[BRD_CHARACTER_MAX];	///<性格毎のポイント加算値
}ACTIN_AI_DATA_TBL;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void ActinAI_WazaParamSet(ACTIN_PROC_WORK *apw, ACTIN_AI_WORK *aiwork, int breeder_no);
static void ActinAI_Calc(ACTIN_PROC_WORK *apw, ACTIN_AI_WORK *aiwork, int breeder_no, 
	u16 *ret_wazano, u8 *ret_judge_no);
static int ActinAI_1(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_2(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_3(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_4(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_5(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_6(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_7(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_8(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_9(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_10(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_11(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_12(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_13(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_14(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_15(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_16(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_17(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_18(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_19(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_20(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_21(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_22(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_23(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_24(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_25(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_26(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_27(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);
static int ActinAI_28(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork,
	u8 *judge, int con_type);


//==============================================================================
//	技決定分岐条件テーブル
//==============================================================================
static int (* const ActinAI_FuncTbl[])(ACTIN_GAME_PARAM *, int, ACTIN_AI_WORK *, u8 *, int) = {
	NULL,
	ActinAI_1,
	ActinAI_2,
	ActinAI_3,
	ActinAI_4,
	ActinAI_5,
	ActinAI_6,
	ActinAI_7,
	ActinAI_8,
	ActinAI_9,
	ActinAI_10,
	ActinAI_11,
	ActinAI_12,
	ActinAI_13,
	ActinAI_14,
	ActinAI_15,
	ActinAI_16,
	ActinAI_17,
	ActinAI_18,
	ActinAI_19,
	ActinAI_20,
	ActinAI_21,
	ActinAI_22,
	ActinAI_23,
	ActinAI_24,
	ActinAI_25,
	ActinAI_26,
	ActinAI_27,
	ActinAI_28,
};


//==============================================================================
//	外部データ
//==============================================================================
#include "actin_ai_tbl.dat"


//==============================================================================
//
//	
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   CPUのAI計算を行い、繰り出す技番号と審判番号を取得する
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   answer		結果取得用ワークへのポインタ
 */
//--------------------------------------------------------------
void ActinAI_Main(ACTIN_PROC_WORK *apw, ACTIN_AI_ANSWER *answer)
{
	int i;
	ACTIN_AI_WORK *aiwork;
	
	aiwork = sys_AllocMemory(HEAPID_ACTIN, sizeof(ACTIN_AI_WORK));
	
	for(i = apw->consys->c_game.player_num; i < BREEDER_MAX; i++){
		ActinAI_WazaParamSet(apw, aiwork, i);
		ActinAI_Calc(apw, aiwork, i, &answer->wazano[i], &answer->judge_no[i]);
	}
	
	sys_FreeMemoryEz(aiwork);
}

//--------------------------------------------------------------
/**
 * @brief   技パラメータセット
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   aiwork			AIワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 */
//--------------------------------------------------------------
static void ActinAI_WazaParamSet(ACTIN_PROC_WORK *apw, ACTIN_AI_WORK *aiwork, int breeder_no)
{
	int i;
	
	MI_CpuClear8(aiwork, sizeof(ACTIN_AI_WORK));
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		aiwork->ai_waza[i].wazano = PokeParaGet(apw->consys->c_game.pp[breeder_no], 
			ID_PARA_waza1 + i, NULL);
		if(AT_WazaConsecutiveCheck(&apw->a_game, breeder_no, aiwork->ai_waza[i].wazano) == TRUE){
			aiwork->ai_waza[i].ap_no = WT_WazaDataParaGet(aiwork->ai_waza[i].wazano, ID_WTD_ap_no);
			aiwork->ai_waza[i].con_type 
				= WT_WazaDataParaGet(aiwork->ai_waza[i].wazano, ID_WTD_contype);
		}
		else{
			aiwork->ai_waza[i].wazano = 0;
		}
	}
	
	aiwork->character = apw->consys->c_game.character[breeder_no];
}

//--------------------------------------------------------------
/**
 * @brief   AI計算
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   aiwork			AIワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   ret_wazano		繰り出す技番号代入先
 * @param   ret_judge_no	指名した審判番号代入先
 */
//--------------------------------------------------------------
static void ActinAI_Calc(ACTIN_PROC_WORK *apw, ACTIN_AI_WORK *aiwork, int breeder_no, 
	u16 *ret_wazano, u8 *ret_judge_no)
{
	int pos, i, ret, s, d;
	ACTIN_GAME_PARAM *a_game;
	int add_point;
	u8 judge[JUDGE_MAX];
	
	a_game = &apw->a_game;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(a_game->breeder_sort[i] == breeder_no){
			break;
		}
	}
	pos = i;
	pos++;	//テーブルが1originなので、1足す
	
	//AI計算実行
	for(i = 0; i < ACTIN_AI_DATA_TBL_MAX; i++){
		if(ActinAIDataTbl[i].sort_pos == pos){
			for(d = 0; d < JUDGE_MAX; d++){
				judge[d] = FALSE;
			}
			
			ret = ActinAI_FuncTbl[ActinAIDataTbl[i].tbl_no](a_game, breeder_no, aiwork, 
				judge, apw->consys->c_game.type);
			if(ret == TRUE){
				//審判選択タイプに従って対象審判のフラグの操作
				switch(ActinAIDataTbl[i].judge_select){
				case BRD_AI_JUDGE_SELECT_NULL:
					for(d = 0; d < JUDGE_MAX; d++){
						judge[d] = FALSE;
					}
					break;
				case BRD_AI_JUDGE_SELECT_BESIDES:
				case BRD_AI_JUDGE_SELECT_LOW:
					for(d = 0; d < JUDGE_MAX; d++){
						judge[d] ^= 1;
					}
					break;
				}
				
				add_point = ActinAIDataTbl[i].add_point[apw->consys->c_game.character[breeder_no]];
				if(apw->consys->c_game.character[breeder_no] != BRD_CHARACTER_ELITE){
					//エリート以外は基本値としてエリート得点を加算
					add_point += ActinAIDataTbl[i].add_point[BRD_CHARACTER_ELITE];
				}
				//対象となる技にポイント加算
				switch(ActinAIDataTbl[i].target_ap_no){
				case BRD_AI_TARGET_SAMETYPE:
					for(s = 0; s < WAZA_TEMOTI_MAX; s++){
						if(apw->consys->c_game.type == aiwork->ai_waza[s].con_type){
							aiwork->ai_waza[s].point += add_point;
							for(d = 0; d < JUDGE_MAX; d++){
								if(judge[d] == TRUE){
									aiwork->ai_waza[s].judge_point[d] += add_point;
								}
							}
						}
						
					}
					break;
				case BRD_AI_TARGET_HART_2_UP:
					for(s = 0; s < WAZA_TEMOTI_MAX; s++){
						if(ConTool_GetAPWaza_App(aiwork->ai_waza[s].ap_no) 
								>= APP_APPEAL_ICON_ONE_POINT * 2){
							aiwork->ai_waza[s].point += add_point;
							for(d = 0; d < JUDGE_MAX; d++){
								if(judge[d] == TRUE){
									aiwork->ai_waza[s].judge_point[d] += add_point;
								}
							}
						}
					}
					break;
				default:
					for(s = 0; s < WAZA_TEMOTI_MAX; s++){
						if(ActinAIDataTbl[i].target_ap_no == aiwork->ai_waza[s].ap_no){
							aiwork->ai_waza[s].point += add_point;
							for(d = 0; d < JUDGE_MAX; d++){
								if(judge[d] == TRUE){
									aiwork->ai_waza[s].judge_point[d] += add_point;
								}
							}
						}
					}
					break;
				}
			}
		}
	}
	
	//-- 一番ポイントが高いものを抽出 --//
	{
		u16 waza_rnd[WAZA_TEMOTI_MAX], judge_rnd[JUDGE_MAX];
		int start_pos, max_pos, now_point, max_point, judge_pos, waza_pos;
		
		//ポイントが同じだった時の比較用のランダム値を生成
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			waza_rnd[i] = contest_rand(apw->consys);
		}
		for(i = 0; i < JUDGE_MAX; i++){
			judge_rnd[i] = contest_rand(apw->consys);
		}
		
		//技抽出
		for(start_pos = 0; aiwork->ai_waza[start_pos].wazano == 0; start_pos++){
			;
		}
		max_pos = start_pos;
		max_point = aiwork->ai_waza[start_pos].point;
		for(i = start_pos + 1; i < WAZA_TEMOTI_MAX; i++){
			if(aiwork->ai_waza[i].wazano != 0){
				now_point = aiwork->ai_waza[i].point;
				if(now_point > max_point
						|| (now_point == max_point && waza_rnd[i] > waza_rnd[max_pos])){
					max_pos = i;
					max_point = now_point;
				}
			}
		}
		waza_pos = max_pos;

		//プレイヤーと審判が被らないように一定の確率で操作
		if(apw->consys->sio_flag == FALSE){
			int count, i, hassei_rand, player_judge;
			count = 0;
			for(i = 0; i < JUDGE_MAX; i++){
				if(aiwork->ai_waza[waza_pos].judge_point[i] == 0){
					count++;
				}
			}
			if(count == JUDGE_MAX){	//審判優先技が発生していないので操作する
				const u8 JudgeControlRand[] = {
					230,	//90%	CONRANK_NORMAL
					128,	//50%	CONRANK_SUPER
					51,		//20%	CONRANK_HYPER
					0,		//0%	CONRANK_MASTER
				};

				hassei_rand = contest_rand(apw->consys) & 0xff;
				if(hassei_rand < JudgeControlRand[apw->consys->c_game.rank]){
					//プレイヤーの選んだ審判が抽出されないようにポイントをマイナスにしておく
					player_judge = apw->a_game.judge_no[apw->consys->c_game.my_breeder_no];
					aiwork->ai_waza[waza_pos].judge_point[player_judge] -= 100;
				}
			}
		}
		//審判抽出
		max_pos = 0;
		max_point = aiwork->ai_waza[waza_pos].judge_point[0];
		for(i = 1; i < JUDGE_MAX; i++){
			now_point = aiwork->ai_waza[waza_pos].judge_point[i];
			if(now_point > max_point
					|| (now_point == max_point && judge_rnd[i] > judge_rnd[max_pos])){
				max_pos = i;
				max_point = now_point;
			}
		}
		judge_pos = max_pos;
		
		*ret_wazano = aiwork->ai_waza[waza_pos].wazano;
		*ret_judge_no = judge_pos;
		GF_ASSERT((*ret_wazano) != 0);
		GF_ASSERT((*ret_judge_no) < JUDGE_MAX);
	}
}



//==============================================================================
//
//	技決定条件分岐
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   今のターンが4ターン目
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_1(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	if(a_game->turn == 4){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   今のターンが２倍状態
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_2(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	if(a_game->wazapara.save[breeder_no].twice_now_apno != 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技５を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_3(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 5){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技９をもっている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_4(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 9){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１２を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_5(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 12){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１５を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_6(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 15){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１７を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_7(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 17){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１８を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_8(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 18){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１９を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_9(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 19){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技２０を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_10(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 20){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技２１を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_11(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 21){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   自分が最下位
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_12(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int my_app, i;
	
	my_app = a_game->app_total[breeder_no];
	for(i = 0; i < BREEDER_MAX; i++){
		if(my_app > a_game->app_total[i]){
			break;
		}
	}
	if(i == BREEDER_MAX){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   今のターンが４ターン目で、自分が最下位
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_13(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int my_app, i;

	if(a_game->turn == 4){
		my_app = a_game->app_total[breeder_no];
		for(i = 0; i < BREEDER_MAX; i++){
			if(my_app > a_game->app_total[i]){
				break;
			}
		}
		if(i == BREEDER_MAX){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技４がその部門の技
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_14(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 4 
				&& aiwork->ai_waza[i].con_type == con_type){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   その部門の技を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_15(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].con_type == con_type){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ4がいるがその部門の技が無い
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_16(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].con_type == con_type){
			break;
		}
	}
	if(i == WAZA_TEMOTI_MAX){
		return FALSE;	//部門の技がなかった
	}
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 4){
			judge[i] = TRUE;
			count++;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ３がいるがその部門の技が無い
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_17(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].con_type == con_type){
			break;
		}
	}
	if(i == WAZA_TEMOTI_MAX){
		return FALSE;	//部門の技がなかった
	}
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 3){
			count++;
			judge[i] = TRUE;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技８を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_18(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 8){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   技１３を持っている
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_19(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].ap_no == 13){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員の中にボルテージ4がいる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_20(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 4){
			count++;
			judge[i] = TRUE;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員の中にボルテージ３がいる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_21(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 3){
			count++;
			judge[i] = TRUE;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員の中にボルテージ０～１がいる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_22(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] <= VOLTAGE_ONE_POINT * 1){
			count++;
			judge[i] = TRUE;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員全員がボルテージ２以上
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_23(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;
	
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] < VOLTAGE_ONE_POINT * 2){
			return FALSE;
		}
	}
	
	for(i = 0; i < JUDGE_MAX; i++){
		judge[i] = TRUE;
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員のボルテージが全員２以下
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_24(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] > VOLTAGE_ONE_POINT * 2){
			return FALSE;
		}
	}
	
	for(i = 0; i < JUDGE_MAX; i++){
		judge[i] = TRUE;
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員の中にボルテージ２以下が一人いる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_25(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] <= VOLTAGE_ONE_POINT * 2){
			judge[i] = TRUE;
			count++;
		}
	}
	if(count == 1){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   審査員の中にボルテージ4が2人いる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_26(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 4){
			judge[i] = TRUE;
			count++;
		}
	}
	if(count == 2){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ０が１人だけいる
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_27(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == 0){
			judge[i] = TRUE;
			count++;
		}
	}
	if(count == 1){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ4がいるがその部門の技が無い
 *
 * @param   a_game			演技力部門ゲームパラメータへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   aiwork			AIワークへのポインタ
 * @param   judge			対象審査員をセットするワークへのポインタ
 * @param   con_type		コンテストタイプ(CONTYPE_???)
 *
 * @retval  TRUE:条件成立、　FALSE:不成立
 */
//--------------------------------------------------------------
static int ActinAI_28(ACTIN_GAME_PARAM *a_game, int breeder_no, ACTIN_AI_WORK *aiwork, u8 *judge, int con_type)
{
	int i, count;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aiwork->ai_waza[i].con_type == con_type){
			break;
		}
	}
	if(i == WAZA_TEMOTI_MAX){
		return FALSE;	//部門の技がなかった
	}
	
	count = 0;
	for(i = 0; i < JUDGE_MAX; i++){
		if(a_game->voltage_total[i] == VOLTAGE_ONE_POINT * 4){
			judge[i] = TRUE;
			count++;
		}
	}
	if(count > 0){
		return TRUE;
	}
	return FALSE;
}

