//==============================================================================
/**
 * @file	actin_ai.c
 * @brief	���Z�͕���FAI
 * @author	matsuda
 * @date	2006.05.20(�y)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tool.h"
#include "con_tool.h"
#include "poketool/waza_tool.h"


//==============================================================================
//	�萔��`
//==============================================================================
///���Z��AI�F�R���I���^�C�v
enum{
	BRD_AI_JUDGE_SELECT_NULL,		///<�w��Ȃ�
	BRD_AI_JUDGE_SELECT_THIS,		///<���̐R�����Ō���
	BRD_AI_JUDGE_SELECT_BESIDES,	///<����ȊO�̐R�����{�P
	BRD_AI_JUDGE_SELECT_LOW,		///<�Ⴂ�R�����Ō���
};

///���ZAI�F�ΏۋZ
enum{
	BRD_AI_TARGET_SAMETYPE = 0xf0,			///<�����^�C�v(CONTYPE_???)�̋Z
	BRD_AI_TARGET_HART_2_UP,				///<�n�[�g2�ȏ�̋Z
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�莝���Z1���Ƃ�����AI�p�̃��[�N
typedef struct{
	u16 wazano;		///<�Z�ԍ�
	s16 point;		///<�|�C���g
	s16 judge_point[JUDGE_MAX];		///<�R���̃|�C���g
	u8 ap_no;		///<�Z���ʔԍ�
	u8 con_type;	///<�Z�̃R���e�X�g�^�C�v
}ACTIN_AI_WAZA;

///�u���[�_�[1�l������AI�p�̃��[�N
typedef struct{
	ACTIN_AI_WAZA ai_waza[WAZA_TEMOTI_MAX];	///<�莝���Z�p�����[�^
	u8 character;		///<�u���[�_�[�̐��i
}ACTIN_AI_WORK;

///AI�f�[�^�e�[�u��
typedef struct{
	u8 sort_pos;		///<����(�u���[�_�[�̈ʒu�ƈ�v�������A���̏������̊֐������s�����)
	u8 tbl_no;			///<�������̃e�[�u���ԍ�
	u8 target_ap_no;	///<�ΏۋZ(�Z���ʔԍ�(ap_no)�őΏۂ��ݒ肳��Ă��܂�)
	s8 judge_select;	///<�R���I���^�C�v

	s16 add_point[BRD_CHARACTER_MAX];	///<���i���̃|�C���g���Z�l
}ACTIN_AI_DATA_TBL;


//==============================================================================
//	�v���g�^�C�v�錾
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
//	�Z���蕪������e�[�u��
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
//	�O���f�[�^
//==============================================================================
#include "actin_ai_tbl.dat"


//==============================================================================
//
//	
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   CPU��AI�v�Z���s���A�J��o���Z�ԍ��ƐR���ԍ����擾����
 *
 * @param   apw			���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   answer		���ʎ擾�p���[�N�ւ̃|�C���^
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
 * @brief   �Z�p�����[�^�Z�b�g
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
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
 * @brief   AI�v�Z
 *
 * @param   apw				���Z�͕���Ǘ����[�N�ւ̃|�C���^
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   ret_wazano		�J��o���Z�ԍ������
 * @param   ret_judge_no	�w�������R���ԍ������
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
	pos++;	//�e�[�u����1origin�Ȃ̂ŁA1����
	
	//AI�v�Z���s
	for(i = 0; i < ACTIN_AI_DATA_TBL_MAX; i++){
		if(ActinAIDataTbl[i].sort_pos == pos){
			for(d = 0; d < JUDGE_MAX; d++){
				judge[d] = FALSE;
			}
			
			ret = ActinAI_FuncTbl[ActinAIDataTbl[i].tbl_no](a_game, breeder_no, aiwork, 
				judge, apw->consys->c_game.type);
			if(ret == TRUE){
				//�R���I���^�C�v�ɏ]���đΏېR���̃t���O�̑���
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
					//�G���[�g�ȊO�͊�{�l�Ƃ��ăG���[�g���_�����Z
					add_point += ActinAIDataTbl[i].add_point[BRD_CHARACTER_ELITE];
				}
				//�ΏۂƂȂ�Z�Ƀ|�C���g���Z
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
	
	//-- ��ԃ|�C���g���������̂𒊏o --//
	{
		u16 waza_rnd[WAZA_TEMOTI_MAX], judge_rnd[JUDGE_MAX];
		int start_pos, max_pos, now_point, max_point, judge_pos, waza_pos;
		
		//�|�C���g���������������̔�r�p�̃����_���l�𐶐�
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			waza_rnd[i] = contest_rand(apw->consys);
		}
		for(i = 0; i < JUDGE_MAX; i++){
			judge_rnd[i] = contest_rand(apw->consys);
		}
		
		//�Z���o
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

		//�v���C���[�ƐR�������Ȃ��悤�Ɉ��̊m���ő���
		if(apw->consys->sio_flag == FALSE){
			int count, i, hassei_rand, player_judge;
			count = 0;
			for(i = 0; i < JUDGE_MAX; i++){
				if(aiwork->ai_waza[waza_pos].judge_point[i] == 0){
					count++;
				}
			}
			if(count == JUDGE_MAX){	//�R���D��Z���������Ă��Ȃ��̂ő��삷��
				const u8 JudgeControlRand[] = {
					230,	//90%	CONRANK_NORMAL
					128,	//50%	CONRANK_SUPER
					51,		//20%	CONRANK_HYPER
					0,		//0%	CONRANK_MASTER
				};

				hassei_rand = contest_rand(apw->consys) & 0xff;
				if(hassei_rand < JudgeControlRand[apw->consys->c_game.rank]){
					//�v���C���[�̑I�񂾐R�������o����Ȃ��悤�Ƀ|�C���g���}�C�i�X�ɂ��Ă���
					player_judge = apw->a_game.judge_no[apw->consys->c_game.my_breeder_no];
					aiwork->ai_waza[waza_pos].judge_point[player_judge] -= 100;
				}
			}
		}
		//�R�����o
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
//	�Z�����������
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ���̃^�[����4�^�[����
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   ���̃^�[�����Q�{���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�T�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�X�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�Q�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�T�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�V�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�W�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�X�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�Q�O�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�Q�P�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �������ŉ���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   ���̃^�[�����S�^�[���ڂŁA�������ŉ���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�S�����̕���̋Z
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   ���̕���̋Z�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �{���e�[�W4�����邪���̕���̋Z������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
		return FALSE;	//����̋Z���Ȃ�����
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
 * @brief   �{���e�[�W�R�����邪���̕���̋Z������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
		return FALSE;	//����̋Z���Ȃ�����
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
 * @brief   �Z�W�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �Z�P�R�������Ă���
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̒��Ƀ{���e�[�W4������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̒��Ƀ{���e�[�W�R������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̒��Ƀ{���e�[�W�O�`�P������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����S�����{���e�[�W�Q�ȏ�
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̃{���e�[�W���S���Q�ȉ�
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̒��Ƀ{���e�[�W�Q�ȉ�����l����
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �R�����̒��Ƀ{���e�[�W4��2�l����
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �{���e�[�W�O���P�l��������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
 * @brief   �{���e�[�W4�����邪���̕���̋Z������
 *
 * @param   a_game			���Z�͕���Q�[���p�����[�^�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @param   aiwork			AI���[�N�ւ̃|�C���^
 * @param   judge			�ΏېR�������Z�b�g���郏�[�N�ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v(CONTYPE_???)
 *
 * @retval  TRUE:���������A�@FALSE:�s����
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
		return FALSE;	//����̋Z���Ȃ�����
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

