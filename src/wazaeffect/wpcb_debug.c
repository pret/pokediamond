//==============================================================================
/**
 * @file	wpcd_debug.c
 * @brief	�f�o�b�O
 * @author	goto
 * @date	2006.03.03(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================


#include "common.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"
#include "wp_callback.h"
#include "we_tool.h"
#include "we_err.h"
#include "we_def.h"

#include "wpcb_common.h"


//--------------------------------------------------------------
/**
 * @brief	�f�o�b�O���\��
 *
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void Debug_OperatorStatusPrint(ECB_OPERATOR_DATA* odp)
{
	OS_Printf("\n----- operator ���p�� -----\n");
	OS_Printf("�J�n�N���C�A���g�@%d\n", odp->s_client);
	OS_Printf("�I���N���C�A���g�@%d\n", odp->e_client);
	OS_Printf("���]�t���O�@�@�@�@%d\n", odp->reverce_flag);
	OS_Printf("\n----- operator mode -----\n");
	OS_Printf("�^�[�Q�b�g�@�@�@�@%d\n", odp->mode[0]);
	OS_Printf("���W����@�@�@�@�@%d\n", odp->mode[1]);
	OS_Printf("��������@�@�@�@�@%d\n", odp->mode[2]);
	OS_Printf("�t�B�[���h����@�@%d\n", odp->mode[3]);
	OS_Printf("�J��������@�@�@�@%d\n", odp->mode[4]);
	
	///< �ڍ�
	if (odp->mode[ ECB_MODE_FIELD ] == OPERATOR_FLD_NONE){ return; }
	
	OS_Printf("�t�B�[���h����@�ڍ�%d\n");
	{
		int i;
		int num;
		int bit;
		
		char str_debug_msg[][255] = {
			"OPERATOR_FLD_NONE",
			"OPERATOR_FLD_GRAVITY_MAG",
			"OPERATOR_FLD_RANDOM_MAG",
			"OPERATOR_FLD_RANDOM_INTVL",
			"OPERATOR_FLD_MAGNET_POS",
			"OPERATOR_FLD_MAGNET_MAG",
			"OPERATOR_FLD_SPIN_RAD",
			"OPERATOR_FLD_SPIN_AXIS",
			"OPERATOR_FLD_SIMPLE_CLS_Y",
			"OPERATOR_FLD_SIMPLE_CLS_CB",
			"OPERATOR_FLD_SIMPLE_CLS_EVT",
			"OPERATOR_FLD_SIMPLE_CLS_GLB",
			"OPERATOR_FLD_CONVERGENCE_POS",
			"OPERATOR_FLD_CONVERGENCE_RATIO",
			"OPERATOR_FLD_END",
		};
		
		num = FieldOperator_BitDataMax();
		
		for (i = 0; i < num; i++){
			
			bit = FieldOperator_BitGet(i);

			if (IsBitCheck(odp->mode[ ECB_MODE_FIELD ], bit) == FALSE){ continue; }
			
			OS_Printf("%s\n", str_debug_msg[i]);
		}
	}
}


