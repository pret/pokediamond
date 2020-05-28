//==============================================================================
/**
 * @file	wpcd_field
 * @brief	�t�B�[���h����n �R�[���o�b�N�֐�
 * @author	goto
 * @date	2006.02.10(��)
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

// -----------------------------------------
//
//	�T�|�[�g�֐�
//
// -----------------------------------------
static void FOT_ExDataGet(ECB_OPERATOR_DATA* odp, int data[]);

// -----------------------------------------
//
//	�t�B�[���h����֐�
//
// -----------------------------------------
static BOOL FOT_None(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Grabity_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Random_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Random_IntVl(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Magnet_Pos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Magnet_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Spin_Rad(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Spin_AxisType(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Simple_Cls_Ypos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Simple_Cls_CoeffBounce(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Simple_Cls_EventType(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Simple_Cls_Global(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Convergence_Pos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);
static BOOL FOT_Convergence_Ratio(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);

//--------------------------------------------------------------
/**
 *
 * @brief	�t�B�[���h����֐��e�[�u��
 *
 */
//--------------------------------------------------------------
static BOOL (* const FieldOperatorTool[])(EMIT_PTR emit, ECB_OPERATOR_DATA* odp) = {
	FOT_None,
	FOT_Grabity_Mag,
	FOT_Random_Mag,
	FOT_Random_IntVl,
	FOT_Magnet_Pos,
	FOT_Magnet_Mag,
	FOT_Spin_Rad,
	FOT_Spin_AxisType,
	FOT_Simple_Cls_Ypos,
	FOT_Simple_Cls_CoeffBounce,
	FOT_Simple_Cls_EventType,
	FOT_Simple_Cls_Global,
	FOT_Convergence_Pos,
	FOT_Convergence_Ratio,
};


// =============================================================================
//
//
//	�� private
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�g���f�[�^�擾
 *
 * @param	odp	
 * @param	data[]	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void FOT_ExDataGet(ECB_OPERATOR_DATA* odp, int data[])
{
	WeSysExDataGet(odp->wsp, data, OPERATOR_FLD_EX_DATA_NUM);
}


//--------------------------------------------------------------
/**
 * @brief	�������삵�Ȃ�
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_None(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	return TRUE;
}


// =============================================================
//
//	���d�͑���
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Grabity_Mag �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Grabity_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int		data[ OPERATOR_FLD_EX_DATA_NUM ];
	VecFx16	pos = { 0,0,0 };

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_SetSPLField_GravityPos(emit, &pos);		///< �W���ʒu�擾
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			VEC_Fx16Set(&pos, data[2],data[3],data[4]);			
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
			SplSub_SetSPLField_GravityPos(emit, &pos);

			return TRUE;
		}
		break;

	case OPERATOR_FLD_AT:
	case OPERATOR_FLD_DF:
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	pos.x -= odp->pos.x;
	pos.y -= odp->pos.y;
	pos.z -= odp->pos.z;

	SplSub_SetSPLField_GravityPos(emit, &pos);

	return TRUE;
}
	

// =============================================================
//
//	�������_������
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Random_Mag �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Random_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Random_IntVl �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Random_IntVl(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	

// =============================================================
//
//	���}�O�l�b�g����
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Magnet_Pos �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Magnet_Pos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int		data[ OPERATOR_FLD_EX_DATA_NUM ];
	VecFx32	pos = { 0,0,0 };

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_MagnetPos(emit, &pos);			///< �W���ʒu�擾
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			VEC_Set(&pos, data[2],data[3],data[4]);			
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_AT:
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &pos);
		break;

	case OPERATOR_FLD_DF:
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &pos);
		break;
	
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	pos.x -= odp->pos.x;
	pos.y -= odp->pos.y;
//	pos.z -= odp->pos.z;

	SplSub_SetSPLField_MagnetPos(emit, &pos);

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Magnet_Mag �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Magnet_Mag(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int	 data[ OPERATOR_FLD_EX_DATA_NUM ];
	fx16 mag = 0;	

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_MagnetMag(emit, &mag);
			mag *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			mag = data[2];
			mag *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_AT:
	case OPERATOR_FLD_DF:
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	SplSub_SetSPLField_MagnetMag(emit, &mag);

	return TRUE;
}
	

// =============================================================
//
//	���X�s������
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Spin_Rad �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Spin_Rad(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int	data[ OPERATOR_FLD_EX_DATA_NUM ];
	u16	rad = 0;	

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_SpinRad(emit, &rad);
			rad *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			rad = data[2];
			rad *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_AT:
	case OPERATOR_FLD_DF:
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	SplSub_SetSPLField_SpinRad(emit, &rad);

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Spin_AxisType �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Spin_AxisType(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int	data[ OPERATOR_FLD_EX_DATA_NUM ];
	u16	axis = 0;	

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_SpinAxisType(emit, &axis);
		}
		break;

	case OPERATOR_FLD_SET:
		{
			axis = data[2];
		}
		break;

	case OPERATOR_FLD_AT:
	case OPERATOR_FLD_DF:
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	SplSub_SetSPLField_SpinAxisType(emit, &axis);

	return TRUE;
}
	

// =============================================================
//
//	���V���v���R���W��������
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_Ypos �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Simple_Cls_Ypos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_CoeffBounce �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Simple_Cls_CoeffBounce(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_EventType �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Simple_Cls_EventType(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_Global �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Simple_Cls_Global(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{

#ifdef WPCB_NONE_DATA_MSG

	OS_Printf("������\n");

#endif	

	return TRUE;
}
	

// =============================================================
//
//	���R���o�[�W�F���X����
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Convergence_Pos �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Convergence_Pos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int		data[ OPERATOR_FLD_EX_DATA_NUM ];
	VecFx32	pos = { 0,0,0 };

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_ConvergencePos(emit, &pos);		///< �W���ʒu�擾
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			VEC_Set(&pos, data[2],data[3],data[4]);			
			pos.x *= odp->reverce_flag;
			pos.y *= odp->reverce_flag;
			pos.z *= odp->reverce_flag;
		}
		break;
	
	case OPERATOR_FLD_SET_DF:
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &pos);
		pos.x = (pos.x * data[2]) / data[3];
		pos.y = (pos.y * data[2]) / data[3];
		pos.z = (pos.z * data[2]) / data[3];
		break;

	case OPERATOR_FLD_AT:
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &pos);
		break;

	case OPERATOR_FLD_DF:
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &pos);
		break;
	
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	pos.x -= odp->pos.x;
	pos.y -= odp->pos.y;
	pos.z -= odp->pos.z;
	SplSub_SetSPLField_ConvergencePos(emit, &pos);

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Convergence_Ratio �𑀍삷��
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL FOT_Convergence_Ratio(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int	 data[ OPERATOR_FLD_EX_DATA_NUM ];
	fx16 ratio = 0;	

	FOT_ExDataGet(odp, data);

	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);
	if (data[1] == OPERATOR_REVERCE_FLAG_OFF){
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}

	switch(data[0]){
	case OPERATOR_FLD_DEFAULT:
		{
			SplSub_GetSPLField_ConvergenceRatio(emit, &ratio);	///< �W����
			ratio *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_SET:
		{
			ratio = data[2];
			ratio *= odp->reverce_flag;
		}
		break;

	case OPERATOR_FLD_AT:
	case OPERATOR_FLD_DF:
	case OPERATOR_FLD_NO_DATA:
		break;
	}

	SplSub_SetSPLField_ConvergenceRatio(emit, &ratio);

	return TRUE;
}
	
	


// =============================================================================
//
//
//	�� public
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	�t�B�[���h�p�����[�^�[���s�֐�
 *
 * @param	no	
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void FieldOperator_Executed(int no, EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	BOOL res;
	
	res = FieldOperatorTool[ no ](emit, odp);
	
	if (res == FALSE){
		OS_Printf("field operator == false\n");
	}
}


//--------------------------------------------------------------
/**
 * @brief	BIT�擾
 *
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	FieldOperator_BitGet(int no)
{
	const int operator_field_tbl[] = {
		OPERATOR_FLD_NONE,
		OPERATOR_FLD_GRAVITY_MAG,
		OPERATOR_FLD_RANDOM_MAG,
		OPERATOR_FLD_RANDOM_INTVL,
		OPERATOR_FLD_MAGNET_POS,
		OPERATOR_FLD_MAGNET_MAG,
		OPERATOR_FLD_SPIN_RAD,
		OPERATOR_FLD_SPIN_AXIS,
		OPERATOR_FLD_SIMPLE_CLS_Y,
		OPERATOR_FLD_SIMPLE_CLS_CB,
		OPERATOR_FLD_SIMPLE_CLS_EVT,
		OPERATOR_FLD_SIMPLE_CLS_GLB,
		OPERATOR_FLD_CONVERGENCE_POS,
		OPERATOR_FLD_CONVERGENCE_RATIO,
		OPERATOR_FLD_END,
	};
	
	return operator_field_tbl[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	BIT�f�[�^�����擾
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	FieldOperator_BitDataMax(void)
{
	int i = 0;
	int check = 0;
	
	do {
		int bit;
		
		bit = FieldOperator_BitGet(i);
		i++;
		if (bit == OPERATOR_FLD_END){ break; }
		
		check++;

	} while(check < 0xFF);
	
	if (check >= 0xFF){
		return 0;
	}
	
	return i;
}

