//==============================================================================
/**
 * @file	dance_ai.c
 * @brief	ダンス部門AI
 * @author	matsuda
 * @date	2006.05.25(木)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "battle/battle_common.h"
#include "contest_order.h"
#include "dance.h"
#include "dance_order.h"

#include "dance_tool.h"
#include "dance_input.h"


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static int MainDancer_AlphaGet(int con_rank, int character);
static int BackDancer_AlphaGet(int con_rank, int character, int beat, int ahead_beat);
static int BackDancer_BetaGet(int con_rank, int character, int beat, int ahead_beat,
	int main_step, int ahead_step);
static void DanceAI_MainDancer(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork);
static void DanceAI_BackDancer(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork);

//==============================================================================
//	データ
//==============================================================================
///AI計算用α値：性格順
ALIGN4 static const s8 AlphaTbl[] = {
	1, 2, 3, 4,
};

///AIがメインダンサー時、続けて同じ方向にダンスする確率(100だと必ず同じ方向にダンス)
ALIGN4 static const u8 SameStepRand[] = {
	90,			//ノーマル
	40,			//スーパー
	0,			//ハイパー
	0,			//マスター
};


//==============================================================================
//
//	
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   ダンスAI初期化
 *
 * @param   aiwork			AI用ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   rotation_pos	ローテーション位置
 * @param   random_seed		ランダムの種
 */
//--------------------------------------------------------------
void DanceAI_Init(DANCE_AI_WORK *aiwork, int breeder_no, int rotation_pos, u32 random_seed, 
	int character)
{
	MI_CpuClear8(aiwork, sizeof(DANCE_AI_WORK));
	
	aiwork->breeder_no = breeder_no;
	aiwork->rotation_pos = rotation_pos;
	aiwork->random_seed = random_seed;
	aiwork->character = character;
}

//--------------------------------------------------------------
/**
 * @brief   2週目用に保持していくパラメータのみ退避させて、それ以外のパラメータはクリアする
 * @param   aiwork		AIワークへのポインタ
 */
//--------------------------------------------------------------
void DanceAI_ParamClear(DANCE_AI_WORK *aiwork)
{
	u32 random_seed;
	int breeder_no, rotation_pos, character;
	
	random_seed = aiwork->random_seed;
	breeder_no = aiwork->breeder_no;
	rotation_pos = aiwork->rotation_pos;
	character = aiwork->character;
	
	MI_CpuClear8(aiwork, sizeof(DANCE_AI_WORK));
	
	aiwork->random_seed = random_seed;
	aiwork->breeder_no = breeder_no;
	aiwork->rotation_pos = rotation_pos;
	aiwork->character = character;
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサーのAI計算
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   aiwork				AI用ワークへのポインタ
 * @param   all_tempo_frame		
 * @param   one_tempo_frame		
 *
 * メインダンサーのダンス開始前に一度だけ呼ぶ必要があります。
 */
//--------------------------------------------------------------
void DancdAI_MainDancerCalc(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, u32 all_tempo_frame, u32 one_tempo_frame)
{
	int i, timing_point, pos, count, alpha;
	u8 dance_timing[DANCE_BEAT / 2];
	u32 base_tempo;
	s32 hit_frame;
	int rinsetu_out;
	u32 beat_max_zure_frame;
	
	//そのビート範囲内に収まる最大ずれ許容フレーム(四捨五入して整数化)
	beat_max_zure_frame = 
		(one_tempo_frame / 4 + ONE_TEMPO_CALC_DECIMAL/2) / ONE_TEMPO_CALC_DECIMAL;
	
	//ダンス出来る範囲を決定
	switch(dpw->consys->c_game.rank){
	case CONRANK_NORMAL:
	case CONRANK_SUPER:
		rinsetu_out = FALSE;
		timing_point = DANCE_BEAT / 2 / 2;	//裏拍含まない
		base_tempo = one_tempo_frame;
		break;
	default:
		rinsetu_out = TRUE;		//隣接した位置は四分音符に収まっていないので配置禁止
		timing_point = DANCE_BEAT / 2;
		base_tempo = one_tempo_frame / 2;
		break;
	}
	
	for(i = 0; i < DANCE_BEAT / 2; i++){
		dance_timing[i] = FALSE;
	}
	
	//ダンスする小節の位置をランダムで決定
	count = 0;
	while(1){
		pos = contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % timing_point;
		if(pos == 0){
			continue;	//最初の小説は押させない
		}
		
		if(dance_timing[pos] == FALSE){
			//隣接した位置は四分音符に収まっていないので配置禁止
			if(rinsetu_out == TRUE){
				if((pos == timing_point - 1) && (dance_timing[pos - 1]) == TRUE){
					continue;
				}
				else if(dance_timing[pos - 1] == TRUE || dance_timing[pos + 1] == TRUE){
					continue;
				}
				//裏拍の場合はあんまり出ないように一定確率ではじく
				if((pos & 1) && (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) & 0xff) < 128){
					continue;
				}
			}

			dance_timing[pos] = TRUE;
			count++;
			if(count >= dpw->d_game.touch_count){
				break;
			}
		}
	}
	
	//ダンスする位置をフレームに変換
	count = 0;
	for(i = 0; i < DANCE_BEAT / 2; i++){
		if(dance_timing[i] == TRUE){
			aiwork->main.hit_frame[count] = (i * base_tempo + ONE_TEMPO_CALC_DECIMAL/2) / ONE_TEMPO_CALC_DECIMAL;
			count++;
		}
	}
	
	//オフセットフレーム加算
	alpha = MainDancer_AlphaGet(dpw->consys->c_game.rank, aiwork->character);
	for(i = 0; i < dpw->d_game.touch_count; i++){
		s32 check_frame;
		check_frame = aiwork->main.hit_frame[i] 
			+ (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % (2+alpha))
			- (1+alpha/2);
		if(check_frame < 0){
			check_frame = 0;
		}
		//ずれが大きすぎて隣の譜面に移動していないかチェック
		if(check_frame - aiwork->main.hit_frame[i] >= beat_max_zure_frame){
			check_frame = aiwork->main.hit_frame[i] + beat_max_zure_frame - 1;
		}
		aiwork->main.hit_frame[i] = check_frame;
		aiwork->main.occ[i] = TRUE;
		OS_TPrintf("AI メインダンス：hit_frame %d番 = %d, one_tempo=%d\n", i, aiwork->main.hit_frame[i], one_tempo_frame);
	}
	
	//踊る方向設定
	{
		int same_step_rand;
		
		same_step_rand = SameStepRand[dpw->consys->c_game.rank];
		
		aiwork->main.tp_type[0] = DANCE_TP_JUMP 
			+ (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % DANCE_TP_MAX);
		for(i = 1; i < dpw->d_game.touch_count; i++){
			if(i < dpw->d_game.touch_count - 1
					&& (same_step_rand > 
					contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % 100)){
				aiwork->main.tp_type[i] = aiwork->main.tp_type[i - 1];
			}
			else{
				aiwork->main.tp_type[i] = DANCE_TP_JUMP 
					+ (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % DANCE_TP_MAX);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサーの計算用α値取得
 *
 * @param   con_rank		コンテストランク(CONRANK_???)
 * @param   character		メインダンサーの性格
 *
 * @retval  メインダンサー用のα値
 */
//--------------------------------------------------------------
static int MainDancer_AlphaGet(int con_rank, int character)
{
	int alpha;
	
	GF_ASSERT(NELEMS(AlphaTbl) > character);
	alpha = AlphaTbl[character];
	switch(con_rank){
	case CONRANK_NORMAL:
		alpha *= 2;
		break;
	case CONRANK_SUPER:
		break;
	case CONRANK_HYPER:
		alpha /= 2;
		break;
	case CONRANK_MASTER:
	default:
		alpha /= 3;
		break;
	}
	
	return alpha;
}

//--------------------------------------------------------------
/**
 * @brief   バックダンサーの計算用α値取得
 *
 * @param   con_rank		コンテストランク(CONRANK_???)
 * @param   character		バックダンサーの性格
 * @param   beat			踊るターゲットとなるメインダンサーが踊ったビート位置
 * @param   ahead_beat		メインダンサーが前に踊っていたビート位置(最初のダンスなら-1)
 *
 * @retval  バックダンサー用のα値
 */
//--------------------------------------------------------------
static int BackDancer_AlphaGet(int con_rank, int character, int beat, int ahead_beat)
{
	int alpha = 0;
	
	GF_ASSERT(NELEMS(AlphaTbl) > character);
	
	//-- その他のずれ要素 --//
	if(ahead_beat != -1){
		//半テンポずらされる
		if((beat & 1) != (ahead_beat & 1)){
			alpha += 3;
		}
		//前の踊りから間が狭い(表拍が2つ以下)
		if(beat - ahead_beat <= 2*2){
			alpha--;
		}
		//前の踊りから間が広い(表拍が4つ以上)
		if(beat - ahead_beat >= 4*2){
			alpha += 3;
		}
	}
	
	alpha = AlphaTbl[character];
	switch(con_rank){
	case CONRANK_NORMAL:
		alpha *= 2;
		break;
	case CONRANK_SUPER:
		alpha *= 2;//+= (alpha * 80) / 100;
		break;
	case CONRANK_HYPER:
		alpha += alpha/2;
		break;
	case CONRANK_MASTER:
	default:
		break;
	}

	if(alpha < 0){
		alpha = 0;
	}
	return alpha;
}

//--------------------------------------------------------------
/**
 * @brief   バックダンサーの計算用β値を取得する
 *
 * @param   con_rank		コンテストランク(CONRANK_???)
 * @param   character		バックダンサーの性格
 * @param   beat			踊るターゲットとなるメインダンサーが踊ったビート位置
 * @param   ahead_beat		メインダンサーが前に踊っていたビート位置(最初のダンスなら-1)
 * @param   main_step		メインダンサーの踊ったダンスステップ
 * @param   ahead_step		前に踊ったメインダンサーのダンスステップ
 * 							(最初のダンスの時はDANCE_STEP_NONE)
 *
 * @retval  β値
 */
//--------------------------------------------------------------
static int BackDancer_BetaGet(int con_rank, int character, int beat, int ahead_beat,
	int main_step, int ahead_step)
{
	int beta = 0;
	
	switch(character){
	case BRD_CHARACTER_ELITE:
		if(main_step == DANCE_STEP_JUMP){
			beta += 3;
		}
		break;
	case BRD_CHARACTER_JACKPOT:
		if(main_step == DANCE_STEP_ADVANCE){
			beta += 3;
		}
		break;
	case BRD_CHARACTER_SINCERE:
		if(main_step == DANCE_STEP_RIGHT){
			beta += 3;
		}
		break;
	case BRD_CHARACTER_WEAK:
		if(main_step == DANCE_STEP_LEFT){
			beta += 3;
		}
		break;
	}
	
	//踊った方向が前と違う方向
	if(ahead_step != DANCE_STEP_NONE){
		if(main_step != ahead_step){
			beta += 8;
		}
	}

	//-- その他のずれ要素 --//
	if(ahead_beat != -1){
		//半テンポずらされる
		if((beat & 1) != (ahead_beat & 1)){
			beta += 2;
		}
		//前の踊りから間が広い(表拍が4つ以上)
		if(beat - ahead_beat >= 4*2){
			beta += 5;
		}
	}
	
	switch(con_rank){
	case CONRANK_NORMAL:
		beta *= 2;
		break;
	case CONRANK_SUPER:
		beta *= 2;//+= (beta * 80) / 100;
		break;
	case CONRANK_HYPER:
		beta += beta/2;
		break;
	case CONRANK_MASTER:
	default:
		break;
	}
	
	return beta;
}

//--------------------------------------------------------------
/**
 * @brief   ダンサーAI実行
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   aiwork				AIワークへのポインタ
 * @param   frame				現在のフレーム
 * @param   all_tempo_frame		メーターが端から端まで到達するフレーム
 * @param   one_tempo_frame		1小節進むのに必要なフレーム数
 *                              (整数部：ONE_TEMPO_CALC_DECIMAL乗算部分、以下小数)
 * @param   musicdata			曲データへのポインタ
 * @param   sendwork			ダンス実行送信タスクワークへのポインタ
 */
//--------------------------------------------------------------
void DanceAI_Main(int now_frame_dancer, DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork)
{
	if(aiwork->rotation_pos == 0 && now_frame_dancer == DANCER_MAIN){
		DanceAI_MainDancer(dpw, aiwork, frame, all_tempo_frame, one_tempo_frame, musicdata,
			sendwork);
	}
	else if(aiwork->rotation_pos != 0 && now_frame_dancer == DANCER_BACK){
		DanceAI_BackDancer(dpw, aiwork, frame, all_tempo_frame, one_tempo_frame, musicdata,
			sendwork);
	}
}

//--------------------------------------------------------------
/**
 * @brief   メインダンサーAIメイン処理
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   aiwork				AIワークへのポインタ
 * @param   frame				現在のフレーム
 * @param   all_tempo_frame		メーターが端から端まで到達するフレーム
 * @param   one_tempo_frame		1小節進むのに必要なフレーム数
 *                              (整数部：ONE_TEMPO_CALC_DECIMAL乗算部分、以下小数)
 * @param   musicdata			曲データへのポインタ
 * @param   sendwork			ダンス実行送信タスクワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceAI_MainDancer(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork)
{
	DANCING_PARAM dancing_param;
	u32 half_tempo_frame;
	
	half_tempo_frame = one_tempo_frame / 2;		//裏拍も取るように
	
	if(aiwork->rotation_pos != 0 || aiwork->touch_count >= musicdata->touch_count){
		return;
	}

	if(aiwork->touch_wait > 0){
		aiwork->touch_wait--;
		return;
	}
	
	//メインダンス実行
	{
		int pos;
		
		for(pos = 0; pos < DANCING_MAX; pos++){
			if(aiwork->main.occ[pos] == TRUE){
				break;
			}
		}
		if(pos >= DANCING_MAX){
			return;
		}
		
		if(aiwork->main.hit_frame[pos] <= frame){
			DancerReactionSet(aiwork->breeder_no, aiwork->main.tp_type[pos], 
				frame, one_tempo_frame, &musicdata->lag, &dancing_param, NULL, 
				aiwork->rotation_pos, aiwork->touch_count, musicdata->touch_count);
			DancingParamSendReqSet(sendwork, &dancing_param);
			
			aiwork->main.occ[pos] = FALSE;
			aiwork->touch_count++;
			aiwork->touch_wait = one_tempo_frame / ONE_TEMPO_CALC_DECIMAL 
				- DANCE_TOUCH_WAIT_SUB_OFFSET;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   バックダンサーAIメイン処理
 *
 * @param   dpw					ダンス部門管理ワークへのポインタ
 * @param   aiwork				AIワークへのポインタ
 * @param   frame				現在のフレーム
 * @param   all_tempo_frame		メーターが端から端まで到達するフレーム
 * @param   one_tempo_frame		1小節進むのに必要なフレーム数
 *                              (整数部：ONE_TEMPO_CALC_DECIMAL乗算部分、以下小数)
 * @param   musicdata			曲データへのポインタ
 * @param   sendwork			ダンス実行送信タスクワークへのポインタ
 */
//--------------------------------------------------------------
static void DanceAI_BackDancer(DANCE_PROC_WORK *dpw, DANCE_AI_WORK *aiwork, 
	u32 frame, u32 all_tempo_frame, u32 one_tempo_frame, const DANCE_MUSIC_DATA *musicdata,
	DANCING_SEND_WORK *sendwork)
{
	DANCING_PARAM dancing_param;
	DANCING_PARAM *main_param;
	u32 half_tempo_frame, back_frame;
	
	half_tempo_frame = one_tempo_frame / 2;		//裏拍も取るように
	
	if(aiwork->rotation_pos == 0 || aiwork->touch_count >= musicdata->touch_count
			|| dpw->maindancer_record[aiwork->touch_count].occ == FALSE){
		return;
	}

	if(aiwork->touch_wait > 0){
		aiwork->touch_wait--;
		return;
	}
	
	main_param = &dpw->maindancer_record[aiwork->touch_count];
	back_frame = frame - all_tempo_frame / 2;
	
	//次に踊るダンスの位置をまだ決めていないなら決定する
	if(aiwork->back.occ == FALSE){
		u32 hit_frame;
		s32 offset_frame;
		int alpha, beta;
		int tp_type, ahead_step, ahead_beat;
		
		if(aiwork->touch_count == 0){
			ahead_beat = -1;
			ahead_step = DANCE_STEP_NONE;
		}
		else{
			ahead_beat = dpw->maindancer_record[aiwork->touch_count - 1].hit_beat;
			ahead_step = dpw->maindancer_record[aiwork->touch_count - 1].dance_step;
		}
		
		alpha = BackDancer_AlphaGet(dpw->consys->c_game.rank, 
			aiwork->character, main_param->hit_beat, ahead_beat);
		beta = BackDancer_BetaGet(dpw->consys->c_game.rank, 
			aiwork->character, main_param->hit_beat, ahead_beat, 
			main_param->dance_step, ahead_step);
		
		hit_frame = (main_param->hit_beat * half_tempo_frame + ONE_TEMPO_CALC_DECIMAL/2) / ONE_TEMPO_CALC_DECIMAL;
		offset_frame = (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % (2+alpha)) 
			- (1+alpha/2);
		if(offset_frame + (s32)hit_frame < 0){
			hit_frame = 0;
		}
		else{
			hit_frame += offset_frame;
		}
		
		//踊る方向ミスチェック
		if((contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % 100) < (0+alpha+beta)){
			do{
				tp_type = DANCE_TP_JUMP 
					+ (contest_fix_rand(aiwork->random_seed, &aiwork->random_seed) % DANCE_TP_MAX);
			}while(DanceTP_to_DanceStep(tp_type) == main_param->dance_step);
		}
		else{
			tp_type = DanceStep_to_TP(main_param->dance_step);
		}
		aiwork->back.frame = hit_frame;
		aiwork->back.tp_type = tp_type;
		aiwork->back.occ = TRUE;
		OS_TPrintf("ローテーション位置%d のAIの次のダンスフレーム＝%d\n", aiwork->rotation_pos, aiwork->back.frame);
		OS_TPrintf("frame = %d, back_frame = %d\n", frame, back_frame);
	}
	
	//バックダンス実行
	{
		if(aiwork->back.frame <= back_frame){
			DancerReactionSet(aiwork->breeder_no, aiwork->back.tp_type, frame, one_tempo_frame, 
				&musicdata->lag, &dancing_param, dpw->maindancer_record, aiwork->rotation_pos,
				aiwork->touch_count, musicdata->touch_count);
			DancingParamSendReqSet(sendwork, &dancing_param);
			
			aiwork->back.occ = FALSE;
			aiwork->touch_count++;
			aiwork->touch_wait = one_tempo_frame / ONE_TEMPO_CALC_DECIMAL 
				- DANCE_TOUCH_WAIT_SUB_OFFSET;
		}
	}
}


