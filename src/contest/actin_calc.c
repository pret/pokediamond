//==============================================================================
/**
 * @file	actin_calc.c
 * @brief	���Z�͕���F�Z���ʌv�Z�Ȃ�
 * @author	matsuda
 * @date	2005.12.07(��)
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
//	�f�[�^
//==============================================================================
///�R���e�X�g�^�C�v�ɂ��o�����Z�̃^�C�v�Ƃ̃{���e�[�W�Q�[�W�̏㉺
ALIGN4 static const s8 ConTypeVoltageTbl[][5] = {
//�����������A�������A���킢���A�����A�����܂���
	{VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0},	//����������
	{0, VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT},	//������
	{-VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT, 0, -VOLTAGE_ONE_POINT},	//���킢��
	{-VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT, 0},	//����
	{0, -VOLTAGE_ONE_POINT, -VOLTAGE_ONE_POINT, 0, VOLTAGE_ONE_POINT},	//�����܂���
};



//--------------------------------------------------------------
/**
 * @brief   �Z�ԍ������{�A�s�[���|�C���g���擾����
 * @param   wazano		�Z�ԍ�
 * @retval  ��{�A�s�[���|�C���g
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
 * @brief   �w�肵���u���[�_�[���I�񂾐R�����A���ɉ��l�w�����Ă��邩���ׂ�
 *
 * @param   a_game				���Z�̓Q�[���i�s�p�����[�^�ւ̃|�C���^
 * @param   check_breeder		���ׂ�u���[�_�[��No
 *
 * @retval  �w����������l��(���Ȃ������ꍇ��0)
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
	count--;	//�����̕�������
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   �R���w����������l���ɂ���Ĕ�������A�s�[���|�C���g���擾����
 * @param   suffer_num		������l��
 * @retval  �擾�o����A�s�[���|�C���g
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
 * @brief   �o�����Z�ɂ���ă{���e�[�W�������������邩�擾����
 *
 * @param   contest_type		���ݎQ�����̃R���e�X�g�^�C�v
 * @param   wazano				�Z�ԍ�
 * @param   judge_no			�I�񂾐R���̔ԍ�
 * @param   special_judge_no	�����R���̔ԍ�
 *
 * @retval  �{���e�[�W�����l
 */
//--------------------------------------------------------------
int ACALC_VoltageUpDownCheck(int contest_type, int wazano, int judge_no, int special_judge_no)
{
	int waza_con_type;
	int point;
	
	waza_con_type = WT_WazaDataParaGet(wazano, ID_WTD_contype);
	point = ConTypeVoltageTbl[contest_type][waza_con_type];
#if 0	//�����R���ł��{�P�̂܂܂ɂȂ��� 2006.03.11(�y)
	if(judge_no == special_judge_no){
		point *= 2;
	}
#endif
	return point;
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�\�[�g�����s
 *
 * @param   a_game		���Z�̓Q�[���i�s�p�����[�^�ւ̃|�C���^
 */
//--------------------------------------------------------------
//���ԑ����U�w�肵���ꍇ�Ƀ\�[�g����p�ɓ���鉼AP
//(�ʏ�ł͎擾������Ȃ����̒l�����鎖�Ō��ɍs���悤�ɂ��Ă���)
ALIGN4 static const s16 NextSortSpecifyEndAP[] = {29970, 29980, 29990, 30000};
//���ԑ����U�w�肵���ꍇ�Ƀ\�[�g����p�ɓ���鉼AP
//(�ʏ�ł͎擾������Ȃ����̒l�����鎖�őO�ɗ���悤�ɂ��Ă���)
ALIGN4 static const s16 NextSortSpecifyFirstAP[] = {-30000, -29990, -29980, -29970};
//���ԑ��색���_���w�肵���ꍇ�Ƀ\�[�g����p�ɓ���鉼AP
//(�ʏ�ł͎擾������Ȃ����̒l�ŁAFirst��End�̒��Ԃ��w�肷�鎖�ŁA��U�A��U�����
//�e�����Ȃ��͈͂̏ꏊ�Ń����_��������)
ALIGN4 static const s16 NextSortRandomAP[] = {-10000, -500, 500, 10000};

void ACALC_BreederSort(ACTIN_GAME_PARAM *a_game)
{
	int i, j, t;
	s16 a[BREEDER_MAX];
	u8 b[BREEDER_MAX];
	u8 before_pos[BREEDER_MAX];
	
	//�\�[�g�p�Ƀe���|�����̈��AP�l�ƃu���[�_�[�ԍ�������
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
	
	//���ԑ��삪���s����Ă���ꍇ�́A�C�ӂ̏ꏊ�ɂ��܂��\�[�g�����悤��AP�l��ύX����
	{
		for(i = 0; i < BREEDER_MAX; i++){
			switch(a_game->wazapara.personal[i].next_sort){
			case AWK_SORT_NONE:
			default:
				break;
			case AWK_SORT_SPECIFY_FIRST:
				a[i] = NextSortSpecifyFirstAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("�u���[�_�[�ԍ�%d�A���ԑ���(��U)�����^�[��%d�Ԗڂ̃A�s�[��\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			case AWK_SORT_SPECIFY_END:
				a[i] = NextSortSpecifyEndAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("�u���[�_�[�ԍ�%d�A���ԑ���(��U)�����^�[��%d�Ԗڂ̃A�s�[��\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			case AWK_SORT_RANDOM:
				a[i] = NextSortRandomAP[a_game->wazapara.personal[i].next_pos];
				OS_TPrintf("�u���[�_�[�ԍ�%d�A���ԑ���(�����_��)�����^�[��%d�Ԗڂ̃A�s�[��\n", i, 
					a_game->wazapara.personal[i].next_pos);
				break;
			}
		}
	}
	
	//AP�l���Ƀ\�[�g���s
	for(i = 0; i < BREEDER_MAX - 1; i++){
		for(j = BREEDER_MAX - 1; j > i; j--){
			if(a[j-1] > a[j] 
					|| (a[j-1] == a[j] && before_pos[j-1] < before_pos[j])){
				//AP�l����ւ�
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
				//�u���[�_�[�ԍ����ꂩ��
				t = b[j];
				b[j] = b[j-1];
				b[j-1] = t;
				//����ւ��O�̏��ԓ���ւ�
				t = before_pos[j];
				before_pos[j] = before_pos[j-1];
				before_pos[j-1] = t;
			}
		}
	}
	
	//���ёւ������ʂ��Z�b�g
	for(i = 0; i < BREEDER_MAX; i++){
		a_game->breeder_sort[i] = b[i];
		OS_TPrintf("����%d�F�u���[�_�[�ԍ�%d, �����܂ł̍��vAP�l=%d\n", 
			i, b[i], a_game->app_total[b[i]]);
	}
}

