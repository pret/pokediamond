//==============================================================================
/**
 * @file	wpcd_operator.c
 * @brief	コールバック統一関数
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

//#define LOOP_EMIT_DEBUG

static void ECB_Operator_Common(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);				///< 本体から直接呼ばれる
static void ECB_Operator_Position(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);			///< 座標操作
static void ECB_Operator_Axiss(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);				///< 方向操作
static void ECB_Operator_Field(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);				///< フィールド操作
static void ECB_Operator_Camera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);				///< カメラ操作
static void ECB_Operator_Priority(EMIT_PTR emit, ECB_OPERATOR_DATA* odp);			///< 優先度切り替え

static void ECB_Tool_ExDataCheckSet(ECB_OPERATOR_DATA* odp, int client_no, VecFx32* vec);
static void ECB_Tool_ExDataSet(ECB_OPERATOR_DATA* odp, VecFx32* vec);

// =============================================================================
//
//
//	■ private
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	コールバック操作関数 - Common
 *
 * @param	wsp	
 * @param	emit
 * @param	odp
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Common(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	///< 座標操作
	{
		if (odp->mode[ ECB_MODE_POS ] != OPERATOR_POS_NONE){
			
			ECB_Operator_Position(emit, odp);
			
		}
	}
	
	///< 方向操作
	{
		if (odp->mode[ ECB_MODE_AXIS ] != OPERATOR_AXIS_NONE){
		
			ECB_Operator_Axiss(emit, odp);
			
		}
	}
	
	///< フィールド操作
	{
		if (odp->mode[ ECB_MODE_FIELD ] != OPERATOR_FLD_NONE){
			
			ECB_Operator_Field(emit, odp);
			
		}		
	}
	
	///< カメラ操作
	{
	#if 1
		
		ECB_Operator_Camera(emit, odp);
	
	#else
		if (odp->mode[ ECB_MODE_CAMERA ] != OPERATOR_CAMERA_NONE){
			
			ECB_Operator_Camera(emit, odp);
			
		}
	#endif		
	}
	
	///< 優先順位操作
	{
		if (odp->mode[ ECB_MODE_PRI ] != OPERATOR_PRI_NONE){

			ECB_Operator_Priority(emit, odp);

		}
	}
#ifdef LOOP_EMIT_DEBUG
	DebugWazaEffect_LoopEmitter(odp->ptc, emit, odp->wsp);
#endif
//	DebugParticle_EmitMove2(odp->ptc, emit, odp->wsp);
}

///< 防御側の中心(BBの位置)
static void DFsidePos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp, VecFx32* vec)
{
	WE_SYS_PTR wsp;
	PTC_PTR ptc;
	int camera_type;
	int client_type;
	int client_no;
	int side;
	
	wsp			 = odp->wsp;
	ptc			 = WeSysPTCPointerGet(wsp);	
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_no	 = WeSysDFNoGet(wsp);
	
	side = WET_SideCheck(wsp, client_no);
	
	if (side == SIDE_MINE){
		client_type	 = CLIENT_TYPE_AA;
	}
	else {
		client_type	 = CLIENT_TYPE_BB;
	}
	
	WET_PokeParticlePosGet_ClientType(client_type, vec, WES_ContestFlag_Get(wsp), camera_type);
}

///< 攻撃側の中心(AAの位置)
static void ATsidePos(EMIT_PTR emit, ECB_OPERATOR_DATA* odp, VecFx32* vec)
{
	WE_SYS_PTR wsp;
	PTC_PTR ptc;
	int defence;
	int camera_type;
	int client_type;
	int client_no;
	int side;
	
	wsp			 = odp->wsp;
	ptc			 = WeSysPTCPointerGet(wsp);	
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_no	 = WeSysATNoGet(wsp);
	
	side = WET_SideCheck(wsp, client_no);
	
	if (side == SIDE_MINE){
		client_type	 = CLIENT_TYPE_AA;
	}
	else {
		client_type	 = CLIENT_TYPE_BB;
	}
	
	WET_PokeParticlePosGet_ClientType(client_type, vec, WES_ContestFlag_Get(wsp), camera_type);
}

//--------------------------------------------------------------
/**
 * @brief	座標操作関数
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Position(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	VecFx32 vec;
	
	switch(odp->mode[ ECB_MODE_POS ]){
	case OPERATOR_POS_NONE:
		///< 座標指定無し とりあえず、何もしない
		break;
	
	case OPERATOR_POS_SP:
		///< 開始側の座標を指定
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_EP:
		///< 終了側の座標を指定
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &vec);
		break;
	
	case OPERATOR_POS_LSP:
		///< 開始側のレーザー座標を指定
		WET_PokeParticleLaserPosGet(odp->wsp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_LEP:
		///< 終了側のレーザー座標を指定
		WET_PokeParticleLaserPosGet(odp->wsp, odp->e_client, &vec);
		break;
				
	case OPERATOR_POS_L2SP:
		///< 開始側のレーザー座標を指定
		WET_PokeParticleLaser2PosGet(odp->wsp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_L2EP:
		///< 終了側のレーザー座標を指定
		WET_PokeParticleLaser2PosGet(odp->wsp, odp->e_client, &vec);
		break;
				
	case OPERATOR_POS_L3SP:
		///< 開始側のレーザー座標を指定
		WET_PokeParticleLaser3PosGet(odp->wsp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_L3EP:
		///< 終了側のレーザー座標を指定
		WET_PokeParticleLaser3PosGet(odp->wsp, odp->e_client, &vec);
		break;
	
	case OPERATOR_POS_L095SP:
		WET_PokeParticleLaser095PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L095EP:
		WET_PokeParticleLaser095PosGet(odp->wsp, odp->e_client, &vec);
		break;
		
	case OPERATOR_POS_L161SP:
		WET_PokeParticleLaser161PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L161EP:
		WET_PokeParticleLaser161PosGet(odp->wsp, odp->e_client, &vec);
		break;
		
	case OPERATOR_POS_L308SP:
		WET_PokeParticleLaser308PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L308EP:
		WET_PokeParticleLaser308PosGet(odp->wsp, odp->e_client, &vec);
		break;
				
	case OPERATOR_POS_L304SP:
		WET_PokeParticleLaser304PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L304EP:
		WET_PokeParticleLaser304PosGet(odp->wsp, odp->e_client, &vec);
		break;
						
	case OPERATOR_POS_L320SP:
		WET_PokeParticleLaser320PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L320EP:
		WET_PokeParticleLaser320PosGet(odp->wsp, odp->e_client, &vec);
		break;
						
	case OPERATOR_POS_L406SP:
		WET_PokeParticleLaser406PosGet(odp->wsp, odp->s_client, &vec);
		break;

	case OPERATOR_POS_L406EP:
		WET_PokeParticleLaser406PosGet(odp->wsp, odp->e_client, &vec);
		break;
		
	case OPERATOR_POS_RSP:
		///< 開始側のリング座標を指定
		WET_PokeParticleRingPosGet(odp->wsp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_REP:
		///< 終了側のリング座標を指定
		WET_PokeParticleRingPosGet(odp->wsp, odp->e_client, &vec);
		break;
		
	case OPERATOR_POS_SET:
		///< ユーザー指定座標を設定
		{
			int pos[ OPERATOR_POS_PARAM_MAX + 1];

			WeSysExDataGet(odp->wsp, pos, OPERATOR_POS_PARAM_MAX + 1);
			odp->reverce_flag = ECB_Operator_ReverceFlag(odp);			
			VEC_Set(&vec, pos[1],pos[2],pos[3]);
			
			if (pos[0] == OPERATOR_EX_REVERCE_OFF){				///< 反転しない
				odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
			}

			vec.x *= odp->reverce_flag;
			vec.y *= odp->reverce_flag;
			//vec.z *= odp->reverce_flag;						///< 奥行きが変わるので反転無し
		}
		break;

	case OPERATOR_POS_SP_OFS:
		///< 開始側の座標を指定
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &vec);
		ECB_Tool_ExDataSet(odp, &vec);
		break;
	
	case OPERATOR_POS_EP_OFS:
		///< 終了側の座標を指定
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &vec);
		ECB_Tool_ExDataSet(odp, &vec);
		break;
	
	case OPERATOR_POS_SP_OFS_ALL:
		///< 開始側のデータ取得＋オフセット
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &vec);
		ECB_Tool_ExDataCheckSet(odp, odp->s_client, &vec);
		break;
	
	case OPERATOR_POS_EP_OFS_ALL:
		///< 終了側のデータ取得＋オフセット
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &vec);
		ECB_Tool_ExDataCheckSet(odp, odp->e_client, &vec);
		break;
		
	case OPERATOR_POS_AT_SIDE_OFS:
		///< 開始側の座標を指定
		{
		//	WET_PokeParticlePosGet(odp->wsp, odp->s_client, &vec);
			ATsidePos(emit, odp, &vec);
			ECB_Tool_ExDataSet(odp, &vec);
		}
		break;
	
	case OPERATOR_POS_DF_SIDE_OFS:
		///< 終了側の座標を指定
		{
		//	WET_PokeParticlePosGet(odp->wsp, odp->e_client, &vec);
			DFsidePos(emit, odp, &vec);
			ECB_Tool_ExDataSet(odp, &vec);
		}
		break;
		
	case OPERATOR_POS_145_CON:
		///< ユーザー指定座標を設定
		{
			VEC_Set(&vec, 11488, 0, 0);
		}
		break;
			
	case OPERATOR_POS_389_CON:
		///< ユーザー指定座標を設定
		{
			VEC_Set(&vec, -5000, -6000, 0);
		}
		break;
		
	case OPERATOR_POS_194:
		WET_PokeParticlePosGet(odp->wsp, odp->s_client, &vec);
		break;
		
	case OPERATOR_POS_145:
		{
			int type;
			int pos145[][2] = {
				{  -5760, -4352 },	///< AA
				{   9488, -1984 },	///< BB
				{ -11760,  3280 },	///< A
				{  13768, -1464 },	///< B
				{  -5376, -2808 },	///< C
				{   6984,  2056 },	///< D
			};
			
			type = WET_ClientTypeGet(odp->wsp, odp->s_client);
			
			VEC_Set(&vec, pos145[type][0], pos145[type][1], 0);
		}
		break;
	
	case OPERATOR_POS_226:
		{
			int type;
			int pos226[][2] = {
				{ -11020, -3488 },	///< AA
				{  10880,  7656 },	///< BB
				{ -15060, -3160 },	///< A
				{  15000,  7240 },	///< B
				{  -8224, -4608 },	///< C
				{   8424,  8896 },	///< D
				{  15000, -2752 },	///< CONTES
			};
			
			if(WES_ContestFlag_Get(odp->wsp) == TRUE){
				type = 6;
			}
			else {
				type = WET_ClientTypeGet(odp->wsp, odp->s_client);
			}
			
			VEC_Set(&vec, pos226[type][0], pos226[type][1], 0);
		}
		break;

	case OPERATOR_POS_225:
		{
			int type;
			int pos225[][2] = {
				{  -4608, -4480 },	///< AA
				{   7624,  2248 },	///< BB
				{  -9024, -3018 },	///< A
				{  13056,  2816 },	///< B
				{  -2432, -4800 },	///< C
				{   6208,  3840 },	///< D
				{   7072, -3648 },	///< CONTEST
			};
			
			if(WES_ContestFlag_Get(odp->wsp) == TRUE){
				type = 6;
			}
			else {
				type = WET_ClientTypeGet(odp->wsp, odp->s_client);
			}
			
			VEC_Set(&vec, pos225[type][0], pos225[type][1], 0);
		}
		break;
	}
	
	odp->pos = vec;												///< 実際の座標を保存
	SPL_SetEmitterPositionX(emit, vec.x);						///< 座標反映
	SPL_SetEmitterPositionY(emit, vec.y);
	SPL_SetEmitterPositionZ(emit, vec.z);
}

typedef struct {
	
	int	x;
	int	y;
	int z;
	
} TAXIS_DATA;

#define AXIS_NONE	(0)

static const TAXIS_DATA	AxisPosTable[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable3[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable095[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable161[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable308[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable304[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable320[ 6 ][ 6 ];
static const TAXIS_DATA	AxisPosTable406[ 6 ][ 6 ];


//--------------------------------------------------------------
/**
 * @brief	軸方向操作関数
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Axiss(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int at_type;
	int df_type;
	VecFx16 axis;
	
	at_type = WET_ClientTypeGet(odp->wsp, odp->s_client);	///< 攻撃側タイプ
	df_type = WET_ClientTypeGet(odp->wsp, odp->e_client);	///< 対象側タイプ

	switch(odp->mode[ ECB_MODE_AXIS ]){
	case OPERATOR_AXIS_NONE:
		///< 方向軸指定無し
		VEC_Fx16Set(&axis, 0, 0, 0);
		break;

	case OPERATOR_AXIS_AT:
	case OPERATOR_AXIS_DF:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			
			if (odp->mode[ ECB_MODE_TARGET ] == OPERATOR_TARGET_DF){
				VEC_Fx16Set(&axis, -3336, +1840, 736);
			}
			else {
				VEC_Fx16Set(&axis, +2336, -1440, 736);
			}
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
		}		
		break;

	case OPERATOR_AXIS_AT_SIDE:
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
		}
		else {
			if (WET_SideCheck(odp->wsp, odp->s_client) == WET_SideCheck(odp->wsp, odp->e_client)){
				VEC_Fx16Set(&axis, AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
			}
			else if (WET_SideCheck(odp->wsp, odp->s_client) == SIDE_MINE){
				VEC_Fx16Set(&axis, AxisPosTable[0][1].x, AxisPosTable[0][1].y, AxisPosTable[0][1].z/2);
			}
			else {
				VEC_Fx16Set(&axis, AxisPosTable[1][0].x, AxisPosTable[1][0].y, AxisPosTable[1][0].z/2);
			}
		}
		break;
		
	case OPERATOR_AXIS_DF_SIDE:
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
		}
		else {
			if (WET_SideCheck(odp->wsp, odp->s_client) == WET_SideCheck(odp->wsp, odp->e_client)){
				VEC_Fx16Set(&axis, AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
			}
			else if (WET_SideCheck(odp->wsp, odp->s_client) == SIDE_MINE){
				VEC_Fx16Set(&axis, AxisPosTable[0][1].x, AxisPosTable[0][1].y, AxisPosTable[0][1].z/2);
			}
			else {
				VEC_Fx16Set(&axis, AxisPosTable[1][0].x, AxisPosTable[1][0].y, AxisPosTable[1][0].z/2);
			}
			//VEC_Fx16Set(&axis, AxisPosTable[at_type][df_type].x, AxisPosTable[at_type][df_type].y, AxisPosTable[at_type][df_type].z/2);
		}
		break;
		
	case OPERATOR_AXIS_AT_3:
	case OPERATOR_AXIS_DF_3:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			
			if (odp->mode[ ECB_MODE_TARGET ] == OPERATOR_TARGET_DF){
				VEC_Fx16Set(&axis, -2336, +1440, 736);
			}
			else {
				VEC_Fx16Set(&axis, +2336, -1440, 736);
			}
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable3[at_type][df_type].x, AxisPosTable3[at_type][df_type].y, AxisPosTable3[at_type][df_type].z/2);
		}
		break;
	
	case OPERATOR_AXIS_AT_095:
	case OPERATOR_AXIS_DF_095:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -2336, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable095[at_type][df_type].x, AxisPosTable3[at_type][df_type].y, AxisPosTable3[at_type][df_type].z/2);
		}
		break;
		
	case OPERATOR_AXIS_AT_161:
	case OPERATOR_AXIS_DF_161:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -2936, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable161[at_type][df_type].x, AxisPosTable161[at_type][df_type].y, AxisPosTable161[at_type][df_type].z);
		}
		break;
		
	case OPERATOR_AXIS_AT_308:
	case OPERATOR_AXIS_DF_308:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -2336, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable308[at_type][df_type].x, AxisPosTable308[at_type][df_type].y, AxisPosTable308[at_type][df_type].z);
		}
		break;
				
	case OPERATOR_AXIS_AT_304:
	case OPERATOR_AXIS_DF_304:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -2336, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable304[at_type][df_type].x, AxisPosTable304[at_type][df_type].y, AxisPosTable304[at_type][df_type].z);
		}
		break;
		
	case OPERATOR_AXIS_AT_320:
	case OPERATOR_AXIS_DF_320:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -2336, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable320[at_type][df_type].x, AxisPosTable320[at_type][df_type].y, AxisPosTable320[at_type][df_type].z);
		}
		break;
		
	case OPERATOR_AXIS_AT_406:
	case OPERATOR_AXIS_DF_406:
		///< 攻撃、防御側基本軸設定			
		if(WES_ContestFlag_Get(odp->wsp) == TRUE){
			VEC_Fx16Set(&axis, -4336, +1440, 736);
		}
		else{
			VEC_Fx16Set(&axis, AxisPosTable406[at_type][df_type].x, AxisPosTable406[at_type][df_type].y, AxisPosTable406[at_type][df_type].z);
		}
		break;
		
	case OPERATOR_AXIS_AT_OLD:
	case OPERATOR_AXIS_DF_OLD:
		{
			int i;
			int aa_bb[ 4 ];
			int a_b[ 4 ];
			int a_c[ 4 ];
			int a_d[ 4 ];
			int c_a[ 4 ];
			int c_b[ 4 ];
			int c_d[ 4 ];
			
			int def[7][ OPERATOR_AXIS_PARAM_MAX+1 ] = {
				{ WP_AXIS_DEF_X, WP_AXIS_DEF_Y, WP_AXIS_DEF_Z, OPERATOR_EX_REVERCE_ON, },
				{ 3232, 1600, 1568, OPERATOR_EX_REVERCE_ON, },
				{ 5984, 2496, 6208, OPERATOR_EX_REVERCE_ON, },
				{ 2688, 1408, 1536, OPERATOR_EX_REVERCE_ON, },
				{ -896,  384,  800, OPERATOR_EX_REVERCE_ON, },
				{ 2336, 1440,  736, OPERATOR_EX_REVERCE_ON, },
				{ 1888, 1856, 1760, OPERATOR_EX_REVERCE_ON, },
			};
			int con_def[ OPERATOR_AXIS_PARAM_MAX+1 ] = {
				-2336, 1440, 736, OPERATOR_EX_REVERCE_ON,
			};
			for (i = 0; i < 4; i++){
				aa_bb[i] = def[0][i];
				a_b[i] = def[1][i];
				a_c[i] = def[2][i];
				a_d[i] = def[3][i];
				c_a[i] = def[4][i];
				c_b[i] = def[5][i];
				c_d[i] = def[6][i];
			}
			///< コンテスト
			if(WES_ContestFlag_Get(odp->wsp) == TRUE){
				for (i = 0; i < 4; i++){
					aa_bb[i] = con_def[i];
					a_b[i] = con_def[i];
					a_c[i] = con_def[i];
					a_d[i] = con_def[i];
					c_a[i] = con_def[i];
					c_b[i] = con_def[i];
					c_d[i] = con_def[i];
				}
			}
			switch(at_type){
			case CLIENT_TYPE_AA:
			default:
				VEC_Fx16Set(&axis, aa_bb[0], aa_bb[1], aa_bb[2]);
				break;
				
			case CLIENT_TYPE_BB:
				if (aa_bb[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
					VEC_Fx16Set(&axis, aa_bb[0], aa_bb[1], aa_bb[2]);
				}
				else {
					VEC_Fx16Set(&axis, -aa_bb[0], -aa_bb[1], -aa_bb[2]);
				}
				break;
				
			case CLIENT_TYPE_A:
				if(df_type == CLIENT_TYPE_B){
					VEC_Fx16Set(&axis, a_b[0], a_b[1], a_b[2]);
				}
				else if(df_type == CLIENT_TYPE_D){
					VEC_Fx16Set(&axis, a_d[0], a_d[1], a_d[2]);
				}
				else{	//CLIENT_TYPE_C
					VEC_Fx16Set(&axis, a_c[0], a_c[1], a_c[2]);
				}
				break;
				
			case CLIENT_TYPE_B:
				if(df_type == CLIENT_TYPE_A){
					if (a_b[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, a_b[0], a_b[1], a_b[2]);
					}
					else {
						VEC_Fx16Set(&axis, -a_b[0], -a_b[1], -a_b[2]);
					}
				}
				else if(df_type == CLIENT_TYPE_D){
					if (a_c[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, -c_a[0], -c_a[1], -c_a[2]);
					}
					else {
						VEC_Fx16Set(&axis, c_a[0], c_a[1], c_a[2]);
					}
				}
				else{	//CLIENT_TYPE_C
					if (c_b[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, c_b[0], c_b[1], c_b[2]);
					}
					else {
						VEC_Fx16Set(&axis, -c_b[0], -c_b[1], -c_b[2]);
					}
				}
				break;
				
			case CLIENT_TYPE_C:
				if(df_type == CLIENT_TYPE_B){
					VEC_Fx16Set(&axis, c_b[0], c_b[1], c_b[2]);
				}
				else if(df_type == CLIENT_TYPE_D){
					VEC_Fx16Set(&axis, c_d[0], c_d[1], c_d[2]);
				}
				else{	//CLIENT_TYPE_C
					VEC_Fx16Set(&axis, c_a[0], c_a[1], c_a[2]);
				}
				break;
				
			case CLIENT_TYPE_D:
				if(df_type == CLIENT_TYPE_B){
					if (a_b[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, c_a[0], c_a[1], c_a[2]);
					}
					else {
						VEC_Fx16Set(&axis, -c_a[0], -c_a[1], -c_a[2]);
					}
				}
				else if(df_type == CLIENT_TYPE_A){
					if (a_b[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, a_d[0], a_d[1], a_d[2]);
					}
					else {
						VEC_Fx16Set(&axis, -a_d[0], -a_d[1], -a_d[2]);
					}
				}
				else{	//CLIENT_TYPE_C
					if (a_b[3] == OPERATOR_EX_REVERCE_OFF){			///< 反転無し
						VEC_Fx16Set(&axis, c_d[0], c_d[1], c_d[2]);
					}
					else {
						VEC_Fx16Set(&axis, -c_d[0], -c_d[1], -c_d[2]);
					}
				}
				break;
			}
		}			
		break;
	
	case OPERATOR_AXIS_SET:
		///< ユーザー指定軸設定
		VEC_Fx16Set(&axis, -800, 1200, 500);
		break;
		
	case OPERATOR_AXIS_145_CON:
		///< ユーザー指定軸設定
		VEC_Fx16Set(&axis, -3410, -2644, 0);
		break;
		
	case OPERATOR_AXIS_389_CON:
		///< ユーザー指定軸設定
		VEC_Fx16Set(&axis, -3440, 1952, 0);
		break;
	
	case OPERATOR_AXIS_194:
		///< みちずれ
		if (WET_SideCheck(odp->wsp, odp->s_client) == SIDE_MINE){
			VEC_Fx16Set(&axis, 3776, 2112, 0);
		}
		else {
			VEC_Fx16Set(&axis, -6000, -2200, 0);
		}
		break;
		
	case OPERATOR_AXIS_145:
		{
			int type;
			int axis145[][2] = {
				{  2864,   3752 },	///< AA
				{ -2944,   1456 },	///< BB
				{  2840,   -854 },	///< A
				{ -3760,  -2536 },	///< B
				{  2288,   2408 },	///< C
				{ -3312,  -2776 },	///< D
			};
			
			type = WET_ClientTypeGet(odp->wsp, odp->s_client);
			
			VEC_Fx16Set(&axis, axis145[type][0], axis145[type][1], 0);
		}
		break;
	
	}
	#if 0
	{
		VecFx32 pos;
		
		WET_PokeParticlePosGet(odp->wsp, odp->e_client, &pos);
		
		axis.x = FX_FX32_TO_F32(pos.x);
		axis.y = FX_FX32_TO_F32(pos.y);
		axis.z = FX_FX32_TO_F32(pos.z);
	}
	
	DebugParticle_AxisLoop(odp->ptc, 0, 0, odp->wsp);
	#endif
	
	SPL_SetEmitterAxis(emit, &axis);
}


//--------------------------------------------------------------
/**
 * @brief	フィールド操作
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Field(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	int num;
	int i;
	int bit;
	
	num = FieldOperator_BitDataMax();
	
	for (i = 0; i < num; i++){
		
		bit = FieldOperator_BitGet(i);

		if (IsBitCheck(odp->mode[ ECB_MODE_FIELD ], bit) == FALSE){ continue; }
		
		FieldOperator_Executed(i, emit, odp);

	}
}


//--------------------------------------------------------------
/**
 * @brief	カメラ操作
 *
 * @param	emit	
 * @param	odp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Camera(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	#if 0
	/* ---
	
		引数でもらうモードがそのまま動作関数になる
		
	--- */
	#endif
	
	CameraOperator_Executed(odp->mode[ ECB_MODE_CAMERA ], emit, odp);
	
}


//--------------------------------------------------------------
/**
 * @brief	優先度切り替え
 *
 * @param	emit	
 * @param	odp	
 * @param	z	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Operator_Priority(EMIT_PTR emit, ECB_OPERATOR_DATA* odp)
{
	#if 0
	/* ---
	
		座標設定後に、Zのみ指定優先度切り替えで切り替える
		カメラは透視射影[GF_CAMERA_PERSPECTIV]のみ有効
	
	--- */
	#endif
	
	fx32 z;
	int at_type;
	int df_type;
	int fb_check = 0;
	
	at_type = WET_ClientTypeGet(odp->wsp, odp->s_client);	///< 攻撃側タイプ
	df_type = WET_ClientTypeGet(odp->wsp, odp->e_client);	///< 対象側タイプ
	
	switch(df_type){
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		fb_check = 0;
		break;
	case CLIENT_TYPE_BB:
	case CLIENT_TYPE_B:
	case CLIENT_TYPE_D:
		fb_check = 1;
		break;
	}
	
	switch (odp->mode[ECB_MODE_PRI]){
	case OPERATOR_PRI_NONE:
		break;
	
	case OPERATOR_PRI_FRONT:
		if (df_type == 0){
			z = OPERATOR_DEF_FZ_AA;
		}
		else {
			z = OPERATOR_DEF_FZ_BB;
		}
		break;
	
	case OPERATOR_PRI_BACK:
		if (df_type == 0){
			z = OPERATOR_DEF_BZ_AA;
		}
		else {
			z = OPERATOR_DEF_BZ_BB;
		}
		break;
	
	case OPERATOR_PRI_Z:
		break;
	}

	if (Particle_CameraTypeGet(odp->ptc) != GF_CAMERA_PERSPECTIV){
		OS_Printf("operator pri 正射影で優先度操作が行なわれました -- 反映されません。\n");
	}

	SPL_SetEmitterPositionZ(emit, z);
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
 * @brief	コールバック操作関数
 *
 * @param	emit	
 *
 * @retval	none	
 *
 *	関数を指定することですべての操作を引き受けることが可能
 *
 */
//--------------------------------------------------------------
void ECB_Operator(EMIT_PTR emit)
{
	WE_SYS_PTR wsp;
	ECB_OPERATOR_DATA* odp;
	
	wsp = Particle_GetTempPtr();
	odp = sys_AllocMemory(WeSysHeapAreaGet(wsp), sizeof(ECB_OPERATOR_DATA));

	odp->wsp = wsp;
	odp->ptc = WeSysPTCPointerGet(odp->wsp);

	///< 操作するモードを取得する
	WeSysExDataGet(odp->wsp, odp->mode, ECB_MODE_NUM);

	///< ターゲット取得
	{
		switch(odp->mode[ ECB_MODE_TARGET ]){
		case OPERATOR_TARGET_NONE:
		default:
			///< 対象指定が無い場合
			odp->s_client	= WeSysATNoGet(odp->wsp);
			odp->e_client	= WeSysDFNoGet(odp->wsp);
			break;

		case OPERATOR_TARGET_AT:
			///< 対象が自分の場合
			odp->s_client	= WeSysDFNoGet(odp->wsp);
			odp->e_client	= WeSysATNoGet(odp->wsp);
			break;

		case OPERATOR_TARGET_DF:
			///< 対象が相手の場合
			odp->s_client	= WeSysATNoGet(odp->wsp);
			odp->e_client	= WeSysDFNoGet(odp->wsp);
			break;
		
		case OPERATOR_TARGET_AT_SIDE:
			///< 対象が自分の場合
			odp->s_client	= WeSysDFNoGet(odp->wsp);
			odp->e_client	= WeSysATNoGet(odp->wsp);
			break;

		case OPERATOR_TARGET_DF_SIDE:
			///< 対象が相手の場合
			odp->s_client	= WeSysATNoGet(odp->wsp);
			odp->e_client	= WeSysDFNoGet(odp->wsp);
			break;
		}
	}
	
	ECB_Operator_Common(emit, odp);
	
#ifdef PM_DEBUG

//	Debug_OperatorStatusPrint(odp);
	
#endif

	sys_FreeMemoryEz(odp);
}


//--------------------------------------------------------------
/**
 * @brief	反転フラグ取得関数
 *
 * @param	we_sys	
 * @param	odp	
 *
 * @retval	static s8	
 *
 */
//--------------------------------------------------------------
s8 ECB_Operator_ReverceFlag(ECB_OPERATOR_DATA* odp)
{
	s8 flag = OPERATOR_REVERCE_FLAG_OFF;
	int at_type, df_type;
		
	at_type = WET_ClientTypeGet(odp->wsp, odp->s_client);
	df_type = WET_ClientTypeGet(odp->wsp, odp->e_client);
	
	switch(at_type){
	case CLIENT_TYPE_AA:
	default:
		break;

	case CLIENT_TYPE_BB:
		flag = OPERATOR_REVERCE_FLAG_ON;
		break;

	case CLIENT_TYPE_A:
		break;
	
	case CLIENT_TYPE_B:
		flag = OPERATOR_REVERCE_FLAG_ON;
		break;
	
	case CLIENT_TYPE_C:
		break;
	
	case CLIENT_TYPE_D:
		flag = OPERATOR_REVERCE_FLAG_ON;
		break;
	}
		
	return flag;
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	odp	
 * @param	client_no	
 * @param	vec	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ECB_Tool_ExDataCheckSet(ECB_OPERATOR_DATA* odp, int client_no, VecFx32* vec)
{
	int i;
	VecFx32 ofs = { 0,0,0 };
	int pos[ OPERATOR_POS_PARAM_MAX + 1];
	int dmy[ OPERATOR_POS_PARAM_MAX + 1];
	
	for (i = 0; i < CLIENT_TYPE_MAX; i++){
		if (i == WET_ClientTypeGet(odp->wsp, client_no)){
			WeSysExDataGet(odp->wsp, pos, OPERATOR_POS_PARAM_MAX + 1);
		}
		else {
			WeSysExDataGet(odp->wsp, dmy, OPERATOR_POS_PARAM_MAX + 1);
		}
	}
	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);			
	VEC_Set(&ofs, pos[1],pos[2],pos[3]);
	
	if (pos[0] == OPERATOR_EX_REVERCE_OFF){				///< 反転しない
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}
	ofs.x *= odp->reverce_flag;
	ofs.y *= odp->reverce_flag;
	ofs.z *= odp->reverce_flag;
	(*vec).x += ofs.x;
	(*vec).y += ofs.y;
	(*vec).z += ofs.z;
}


static void ECB_Tool_ExDataSet(ECB_OPERATOR_DATA* odp, VecFx32* vec)
{
	int pos[ OPERATOR_POS_PARAM_MAX + 1];
	VecFx32 ofs = { 0, 0, 0 };

	WeSysExDataGet(odp->wsp, pos, OPERATOR_POS_PARAM_MAX + 1);
	odp->reverce_flag = ECB_Operator_ReverceFlag(odp);			
	VEC_Set(&ofs, pos[1],pos[2],pos[3]);
	
	if (pos[0] == OPERATOR_EX_REVERCE_OFF){				///< 反転しない
		odp->reverce_flag = OPERATOR_REVERCE_FLAG_OFF;
	}
	ofs.x *= odp->reverce_flag;
	ofs.y *= odp->reverce_flag;
	ofs.z *= odp->reverce_flag;
	(*vec).x += ofs.x;
	(*vec).y += ofs.y;
	(*vec).z += ofs.z;
}


static const TAXIS_DATA	AxisPosTable[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		3776,		2112,		3064 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-4228,		-2728,		3064 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< A
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		5986,		1584,		3064 },
		{		1040,		-600,		   0 },
		{		4304,		2536,		3064 },
	},
	{	///< B
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-6480,		-2040,		3064 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-4384,		-2968,		3064 },
		{		 -832,		  224,	       0 },
	},
	{	///< C
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2008,		  376,		   0 },
		{		 4034,		 2696,		3064 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		3092,		 3036,		3064 },
	},
	{	///< D
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-4760,		-2672,		3064 },
		{		 1728,		 -400,		   0 },	///< y = 800
		{		-3472,		-4648,		3064 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};


static const TAXIS_DATA	AxisPosTable3[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		2408,		 1248,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-1544,		 -936,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< A
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		1944,		 336,		   0 },
		{		 568,		-560,		   0 },
		{		1944,	 	 928,		   0 },
	},
	{	///< B
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2424,		 -816,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2424,		-1024,		   0 },
		{		 -872,		    8,	       0 },
	},
	{	///< C
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1432,		  120,		   0 },
		{		 1496,		  776,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 1496,		 1208,		   0 },
	},
	{	///< D
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1920,		 -824,		   0 },
		{		  672,		    8,	       0 },
		{		-1920,		-1076,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};

static const TAXIS_DATA	AxisPosTable095[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		1408,		  736,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-1208,		 -784,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		2040,		 672,		   0 },
		{		 928,		-616,		   0 },
		{		1760,	 	 784,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1816,		 -664,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1440,		 -928,		   0 },
		{		 -680,		    8,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1032,		    8,		   0 },
		{		 1280,		  672,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 1080,		 1032,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1648,		 -480,		   0 },
		{		  792,		    8,	       0 },
		{		 -960,		 -928,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};


static const TAXIS_DATA	AxisPosTable161[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		2528,		 1588,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-4264,		-5056,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		3928,		1112,		   0 },
		{		 704,		-672,		   0 },
		{		2784,	 	1120,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-4152,		-1560,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-3096,		-1976,		   0 },
		{		 -692,		  -24,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 -792,		  104,		   0 },
		{		 2824,		 1616,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 2144,		 1936,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2904,		-1528,		   0 },
		{		 1128,		 -408,	       0 },
		{		-1912,		-2072,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};


static const TAXIS_DATA	AxisPosTable308[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		1952,		 1096,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-2016,		-968,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		1920,		 768,		   0 },
		{		 832,		-448,		   0 },
		{		1728,	 	 832,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2096,		-744,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2096,		-1240,		   0 },
		{		 -752,		  24,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1008,		  168,		   0 },
		{		 1744,		  872,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 1496,		 1240,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1980,		 -712,		   0 },
		{		  632,		 -200,	       0 },
		{		-1680,		-1656,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};


static const TAXIS_DATA	AxisPosTable304[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		3200,		 1720,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-3520,		-1976,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		3560,		  968,		   0 },
		{		1600,		-1472,		   0 },
		{		3264,	 	 1552,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-4000,		 -784,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-3232,		-2256,		   0 },
		{		-1248,		  560,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1080,		 1240,		   0 },
		{		 3144,		 1944,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 2120,		 2336,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2992,		-1440,		   0 },
		{		 1888,		 -592,	       0 },
		{		-2592,		-2704,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};


static const TAXIS_DATA	AxisPosTable320[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		1600,		 -64,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-1856,		-1608,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		2000,		 -192,		   0 },
		{		672,		-1328,		   0 },
		{		2000,	 	 +192,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2184,		 -1536,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2064,		-1880,		   0 },
		{		-592,		  -792,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1288,		 -128,		   0 },
		{		 1528,		 -448,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 1528,		 +296,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-1528,		-1560,		   0 },
		{		  856,		 -368,	       0 },
		{		-1384,		-2032,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};

static const TAXIS_DATA	AxisPosTable406[][ 6 ] = {
	{	///< AA
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{		3584,		 2048,			0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< BB
		{		-3392,		-1776,		    0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
	{	///< Ao
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		4992,		 +2032,		   0 },
		{		1024,		  -688,		   0 },
		{		3776,	 	 +1968,		   0 },
	},
	{	///< Bo
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-5544,		-1592,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-3752,		-2232,		   0 },
		{		-1704,		  264,	       0 },
	},
	{	///< Co
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-2008,		-64,		   0 },
		{		 4088,		 2352,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		 2644,		 2416,		   0 },
	},
	{	///< Do
		{	AXIS_NONE,	AXIS_NONE, 	AXIS_NONE },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
		{		-3784,		-1936,		   0 },
		{		1784,		-16,		   0 },
		{		-3240,		-2744,		   0 },
		{	AXIS_NONE,	AXIS_NONE,	AXIS_NONE },
	},
};