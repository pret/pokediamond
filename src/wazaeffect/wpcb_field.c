//==============================================================================
/**
 * @file	wpcd_field
 * @brief	フィールド操作系 コールバック関数
 * @author	goto
 * @date	2006.02.10(金)
 *
 * ここに色々な解説等を書いてもよい
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
//	サポート関数
//
// -----------------------------------------
static void FOT_ExDataGet(ECB_OPERATOR_DATA* odp, int data[]);

// -----------------------------------------
//
//	フィールド操作関数
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
 * @brief	フィールド操作関数テーブル
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
//	■ private
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	拡張データ取得
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
 * @brief	何も操作しない
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
//	□重力操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Grabity_Mag を操作する
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
			SplSub_SetSPLField_GravityPos(emit, &pos);		///< 集束位置取得
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
//	□ランダム操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Random_Mag を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Random_IntVl を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	

// =============================================================
//
//	□マグネット操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Magnet_Pos を操作する
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
			SplSub_GetSPLField_MagnetPos(emit, &pos);			///< 集束位置取得
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
 * @brief	FOT_Magnet_Mag を操作する
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
//	□スピン操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Spin_Rad を操作する
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
 * @brief	FOT_Spin_AxisType を操作する
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
//	□シンプルコリジョン操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_Ypos を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_CoeffBounce を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_EventType を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	
	
//--------------------------------------------------------------
/**
 * @brief	FOT_Simple_Cls_Global を操作する
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

	OS_Printf("未実装\n");

#endif	

	return TRUE;
}
	

// =============================================================
//
//	□コンバージェンス操作
//
// =============================================================
//--------------------------------------------------------------
/**
 * @brief	FOT_Convergence_Pos を操作する
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
			SplSub_GetSPLField_ConvergencePos(emit, &pos);		///< 集束位置取得
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
 * @brief	FOT_Convergence_Ratio を操作する
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
			SplSub_GetSPLField_ConvergenceRatio(emit, &ratio);	///< 集束力
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
//	■ public
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	フィールドパラメーター実行関数
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
 * @brief	BIT取得
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
 * @brief	BITデータ数を取得
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

