//============================================================================================
/**
 * @file	box_reel.c
 * @brief	ボックス操作画面　サブ画面リールセレクタの動作判定
 * @author	taya
 * @date	2005.11.16
 */
//============================================================================================
#include "common.h"
#include "gflib\touchpanel.h"

#include  "box_common.h"
#include  "box_reel.h"


#define MOVEVALUE_MAX		(4)		// 最大で何段階動くか
#define REEL_ANGLE_UNIT		(3584)


#define REED_MARGIN_TIME	(4)	// タッチされてから角度を計算するまで、このフレーム分だけ余裕を見る


//==============================================================
// Prototype
//==============================================================
static void change_ctrlfunc( BOX_REEL_CTRL* ctrl, int (*func)(BOX_REEL_CTRL*,BOOL,BOOL) );
static void change_ctrlfunc_keeptime( BOX_REEL_CTRL* ctrl, int (*func)(BOX_REEL_CTRL*,BOOL,BOOL) );
static int ctrlfunc_free( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag );
static int ctrlfunc_hit( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag );
static int ctrlfunc_idle_hold( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag );
static int ctrlfunc_idle_free( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag );
static u16 calc_angle( const BOX_REEL_CTRL* ctrl, u32 px, u32 py );
static int calc_slide_value( const BOX_REEL_CTRL* ctrl, u16 start, u16 end );



//------------------------------------------------------------------
/**
 * 
 *
 * @param   ctrl		
 *
 */
//------------------------------------------------------------------
void BoxApp_ReelCtrlInit( BOX_REEL_CTRL* ctrl, int cx, int cy, int r_in, int r_out )
{
	ctrl->func = ctrlfunc_free;
	ctrl->hit_flag = FALSE;

	ctrl->center_x = cx;
	ctrl->center_y = cy;
	ctrl->last_x = cx;
	ctrl->last_y = cy;
	ctrl->touch_x = cx;
	ctrl->touch_y = cy;

	ctrl->inside.circle.code = TP_USE_CIRCLE;
	ctrl->inside.circle.x = cx;
	ctrl->inside.circle.y = cy;
	ctrl->inside.circle.r = r_in;

	ctrl->outside.circle.code = TP_USE_CIRCLE;
	ctrl->outside.circle.x = cx;
	ctrl->outside.circle.y = cy;
	ctrl->outside.circle.r = r_out;

	if( cx < 128 ){
		ctrl->sign = 1;
	}else {
		ctrl->sign = -1;
	}
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   ctrl		コントロールワークポインタ
 *
 * @retval  int			何段階スライドさせるか
 */
//------------------------------------------------------------------
int BoxApp_ReelCtrlMain( BOX_REEL_CTRL* ctrl )
{
	BOOL hit_flag, trg_flag;

	// 外側の円と内側の間ならリールに触れていると判定する
	if( ( GF_TP_SingleHitCont( &ctrl->outside ) == TRUE )
	&&	( GF_TP_SingleHitCont( &ctrl->inside ) == FALSE )
	){
		u32 x, y;

		hit_flag = TRUE;
		trg_flag = ( ctrl->hit_flag == FALSE );

		if( GF_TP_GetPointCont( &x, &y ) )
		{
			ctrl->last_x = x;
			ctrl->last_y = y;
		}
	}
	else
	{
		hit_flag = FALSE;
		trg_flag = FALSE;
	}

	ctrl->hit_flag = hit_flag;
	return ctrl->func( ctrl, hit_flag, trg_flag );

}

static void change_ctrlfunc( BOX_REEL_CTRL* ctrl, int (*func)(BOX_REEL_CTRL*,BOOL,BOOL) )
{
	ctrl->seq = 0;
	ctrl->func = func;
}

static void change_ctrlfunc_keeptime( BOX_REEL_CTRL* ctrl, int (*func)(BOX_REEL_CTRL*,BOOL,BOOL) )
{
	ctrl->func = func;
}


//------------------------------------------------------------------
/**
 * コントロール関数：タッチパネルに触れていない状態
 *
 * @param   ctrl			コントロールワークポインタ
 * @param   hit_flag		範囲内に触れているか
 * @param   trg_flag		タッチパネルトリガ入力フラグ
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ctrlfunc_free( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag )
{
	if( hit_flag && trg_flag )
	{
		ctrl->touch_x = ctrl->last_x;
		ctrl->touch_y = ctrl->last_y;
		ctrl->touch_angle = calc_angle( ctrl, ctrl->touch_x, ctrl->touch_y );
		change_ctrlfunc( ctrl, ctrlfunc_hit );
		return REEL_RESULT_START;
	}
	return REEL_RESULT_NULL;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   ctrl		
 * @param   hit_flag		
 * @param   trg_flag		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ctrlfunc_hit( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag )
{
	if( hit_flag == FALSE)
	{
		change_ctrlfunc( ctrl, ctrlfunc_free );
		return REEL_RESULT_RELEASE;
	}

/*
	if( ctrl->seq > REED_MARGIN_TIME )
	{
		ctrl->seq++;
		return REEL_RESULT_NULL;
	}
*/

	return REEL_RESULT_MOVE;
}
static int ctrlfunc_idle_hold( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag )
{
	if( hit_flag == FALSE)
	{
		change_ctrlfunc( ctrl, ctrlfunc_idle_free );
		return REEL_RESULT_MOVE;
	}
	return REEL_RESULT_NULL;
}
static int ctrlfunc_idle_free( BOX_REEL_CTRL* ctrl, BOOL hit_flag, BOOL trg_flag )
{
	return REEL_RESULT_NULL;
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   ctrl		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int BoxApp_ReelCtrlGetMoveValue( const BOX_REEL_CTRL* ctrl )
{
	int val;
	u16 angle;

//	OS_TPrintf("tx:%d ty:%d -> lx:%d ly:%d\n", ctrl->touch_x, ctrl->touch_y, ctrl->last_x, ctrl->last_y);
	angle = calc_angle( ctrl, ctrl->last_x, ctrl->last_y );
	val = calc_slide_value( ctrl, ctrl->touch_angle, angle );

	return val;
}

void BoxApp_ReelCtrlNotifyMoveStart( BOX_REEL_CTRL* ctrl )
{
	if( ctrl->func == ctrlfunc_hit )
	{
		change_ctrlfunc_keeptime( ctrl, ctrlfunc_idle_hold );
	}
	else
	{
		change_ctrlfunc( ctrl, ctrlfunc_idle_free );
	}
}

//------------------------------------------------------------------
/**
 * アイコン移動処理後に呼び出し、状態をリセットする
 *
 * @param   ctrl		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int BoxApp_ReelCtrlReset( BOX_REEL_CTRL* ctrl )
{
	if( ctrl->func == ctrlfunc_idle_hold )
	{
		change_ctrlfunc_keeptime( ctrl, ctrlfunc_hit );
		return TRUE;
	}
	else
	{
		change_ctrlfunc( ctrl, ctrlfunc_free );
		return FALSE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * 任意点と中心点との角度計算
 *
 * @param   ctrl	コントロールワークポインタ
 * @param   px		任意点X
 * @param   py		任意点Y
 *
 * @retval  fx16	角度（ラジアン）
 */
//------------------------------------------------------------------
static u16 calc_angle( const BOX_REEL_CTRL* ctrl, u32 px, u32 py )
{
	fx32  x, y;

	x = ((int)(px - ctrl->center_x)) << FX32_SHIFT;
	y = ((int)(py - ctrl->center_y)) << FX32_SHIFT;

	return FX_Atan2Idx( y, x );
}
//------------------------------------------------------------------
/**
 * スライド角度から、何段階スライドさせるか計算
 *
 * @param   ctrl		コントロールワークポインタ
 * @param   start		スライド開始角度（ラジアン）
 * @param   end			スライド終了角度（ラジアン）
 *
 * @retval  int		何段階スライドさせるか
 */
//------------------------------------------------------------------
static int calc_slide_value( const BOX_REEL_CTRL* ctrl, u16 start, u16 end )
{
	static const u16 step[] = {
		0x300, 0x1800,
	};
	int diff, val, sign, i;

	diff = end - start;
	if( diff < 0 )
	{
		sign = -1;
		diff *= -1;
	}
	else
	{
		sign = 1;
	}

	for(val=0; val<NELEMS(step); val++)
	{
		if( diff < step[val] )
		{
			break;
		}
	}

//	OS_TPrintf("  start:%d, end:%d, diff:%d, val=%d, sign=%d\n", start, end, diff, val, sign);

	val = val * sign * ctrl->sign;

	return val;
}
