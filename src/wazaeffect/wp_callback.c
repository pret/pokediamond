//==============================================================================
/**
 * @file	wp_callback.c
 * @brief	技エフェクトエミッタ生成時に呼び出される汎用コールバック関数など
 * @author	matsuda
 * @date	2005.08.03(水)
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

//==============================================================================
//	データ定義
//==============================================================================
static const VecFx32 EnemyEye = {
	0x1700, 0x4d00, -0x1000
};
static const VecFx32 EnemyUp = {
	0, -FX32_ONE, 0
};

static inline void DEBUG_ForeverEmitterFlag(EMIT_PTR emit, VecFx32* tv){

#ifdef PM_DEBUG

	if (sys.cont & PAD_BUTTON_Y){
		SPL_SetEmitterParticleLife(emit, 30000);
		DebugParticle_EmitMove(DEBUG_PTC_PTR_Get(), emit, tv);
	}

#endif
}
	

static s8 SignCheck(WE_SYS_PTR we_sys, int start_client, int end_client);

//--------------------------------------------------------------
/**
 * @brief	クライアントタイプから、反転フラグを取得する
 *
 * @param	start_client	
 * @param	end_client	
 *
 * @retval	static void s8	
 *
 */
//--------------------------------------------------------------
static s8 SignCheck(WE_SYS_PTR we_sys, int start_client, int end_client)
{
	s8 flag = 1;
	int attack_type, defence_type;
		
	attack_type  = WET_ClientTypeGet(we_sys, start_client);
	defence_type = WET_ClientTypeGet(we_sys, end_client);
	
	switch(attack_type){
	case CLIENT_TYPE_AA:
	default:
		break;
	case CLIENT_TYPE_BB:
		flag = -1;
		break;
	case CLIENT_TYPE_A:	break;
	case CLIENT_TYPE_B:
		flag = -1;
		break;
	case CLIENT_TYPE_C:	break;
	case CLIENT_TYPE_D:
		flag = -1;
		break;
	}
		
	return flag;
}

void EmitCall_Debug(EMIT_PTR emit)
{
#ifdef PM_DEBUG
	WE_SYS_PTR	wsp;
	PTC_PTR		ptc;

	wsp = Particle_GetTempPtr();
	ptc = WeSysPTCPointerGet(wsp);

	DebugWazaEffect_LoopEmitter(ptc, emit, wsp);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：味方、敵の攻撃でカメラの上方向を逆に設定する(攻撃側に合わせる)
 * @param   emit		生成したエミッタへのポインタ
 
 使ってない
 
 */
//--------------------------------------------------------------
void EmitCall_CameraReverseAttack(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	PTC_PTR ptc;
	int attack, defence, contest_flag;
	VecFx32 vex, eye, v_up;
	
	we_sys = Particle_GetTempPtr();
	attack = WeSysATNoGet(we_sys);
	defence = WeSysDFNoGet(we_sys);
	attack = 1;
	defence = 0;
	ptc = WeSysPTCPointerGet(we_sys);

#if 0
	WET_PokeParticlePosGet(we_sys, defence, &vex);
#else
	{
		int client_type, diagonal_client_type;
		int camera_type;
		
		if(WET_SideCheck(we_sys, attack) == SIDE_MINE){
			WET_PokeParticlePosGet(we_sys, attack, &vex);
		}
		else{	//カメラをぐるっと回すので最初のオフセット座標は
				//対角線上の反対側にある座標に設定する必要がある
			client_type = WET_ClientTypeGet(we_sys, attack);
			diagonal_client_type = WazaTool_DiagonalClientTypeGet_ClientType(client_type);
			//camera_type = WeSysCameraTypeGet(we_sys);
			camera_type = Particle_CameraTypeGet(ptc);
			contest_flag = WES_ContestFlag_Get(we_sys);
			WET_PokeParticlePosGet_ClientType(diagonal_client_type, &vex, contest_flag, camera_type);
			WET_PokeParticlePosGet_ClientType(client_type, &eye, contest_flag, camera_type);
//			vex.z = eye.z;
		}
	}
#endif
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
	
//	WET_AttackCameraEyeGet(attack, &eye);
	WET_AttackCameraUpGet(attack, &v_up);
	
//	Particle_SetEye(ptc, &eye);
//	Particle_SetVup(ptc, &v_up);

	{//カメラ公転
		CAMERA_ANGLE angle;
		GF_CAMERA_PTR p_camera;
		
		p_camera = Particle_GetCameraPtr(ptc);
		switch(attack){
		case CLIENT_TYPE_A:
		default:
		#if 0
			switch(defence){
			case :
			}
		#else
			
		#endif
			angle = GFC_GetCameraAngle(p_camera);
//			angle.x += 65536 / 2;
//			angle.y += 65536 / 2;
			GFC_SetCameraAngleRev(&angle, p_camera);
			break;
		case CLIENT_TYPE_B:
			angle = GFC_GetCameraAngle(p_camera);
			angle.x += 65536 / 2;
			angle.y += 65536 / 2;
			GFC_SetCameraAngleRev(&angle, p_camera);
			break;
		}
	}
	
//	DebugParticle_CameraMove(ptc);
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：味方、敵の攻撃でカメラの上方向を逆に設定する(防御側に合わせる)
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
void EmitCall_CameraReverseDefence(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	PTC_PTR ptc;
	int defence;
	VecFx32 vex, v_up;
	
	we_sys = Particle_GetTempPtr();
	defence = WeSysDFNoGet(we_sys);
	ptc = WeSysPTCPointerGet(we_sys);

	WET_PokeParticlePosGet(we_sys, 0, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
	
	WET_AttackCameraUpGet(defence, &v_up);
	
	Particle_SetVup(ptc, &v_up);
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：エミッタの生成座標を防御側のポケモンの座標に設定する
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
void EmitCall_DefencePos(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	int attack;
	VecFx32 vex;
	
	we_sys = Particle_GetTempPtr();
	attack = WeSysDFNoGet(we_sys);

	WET_PokeParticlePosGet(we_sys, attack, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：エミッタの生成座標を攻撃側のポケモンの座標に設定する
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
void EmitCall_AttackPos(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	int defence;
	VecFx32 vex;
	
	we_sys = Particle_GetTempPtr();
	defence = WeSysATNoGet(we_sys);
	WET_PokeParticlePosGet(we_sys, defence, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
}

void EmitCall_AttackPosSet(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	int defence;
	VecFx32 vex;
	
	we_sys = Particle_GetTempPtr();
	defence = WeSysATNoGet(we_sys);
	WET_PokeParticlePosGet(we_sys, defence, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
}

///< だいもんじ専用関数。
void EmitCall_ATPosCR(EMIT_PTR emit)
{
	WE_SYS_PTR we_sys;
	int defence;
	int attack;
	VecFx32 vex;
	
	we_sys  = Particle_GetTempPtr();
	defence = WeSysATNoGet(we_sys);
	attack  = WeSysDFNoGet(we_sys);
/*	
	if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
		
		switch(attack){
		case CLIENT_TYPE_AA:
			defence = CLIENT_TYPE_BB;
			break;
		case CLIENT_TYPE_BB:
			defence = CLIENT_TYPE_AA;
			break;
		case CLIENT_TYPE_A:
			defence = CLIENT_TYPE_C;
			break;
		case CLIENT_TYPE_B:
			defence = CLIENT_TYPE_D;
			break;
		case CLIENT_TYPE_C:
			defence = CLIENT_TYPE_A;
			break;
		case CLIENT_TYPE_D:
			defence = CLIENT_TYPE_B;
			break;
		default:
			OS_Printf("例外\n");
			break;
		}
	}
	
	OS_Printf("defance = %d\n");
*/	
	WET_PokeParticlePosGet(we_sys, defence, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);	
}

///< 防御側の中心(BBの位置)
void EmitCall_DFsidePos(EMIT_PTR emit)
{
	WE_SYS_PTR wsp;
	VecFx32 vec;
	PTC_PTR ptc;
	int camera_type;
	int client_type;
	int client_no;
	int side;
	
	wsp			 = Particle_GetTempPtr();
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
	
	WET_PokeParticlePosGet_ClientType(client_type, &vec, WES_ContestFlag_Get(wsp), camera_type);
	SPL_SetEmitterPositionX(emit, vec.x);
	SPL_SetEmitterPositionY(emit, vec.y);
	SPL_SetEmitterPositionZ(emit, vec.z);
}

///< 攻撃側の中心(AAの位置)
void EmitCall_ATsidePos(EMIT_PTR emit)
{
	WE_SYS_PTR wsp;
	VecFx32 vec;
	PTC_PTR ptc;
	int defence;
	int camera_type;
	int client_type;
	int client_no;
	int side;
	
	wsp			 = Particle_GetTempPtr();
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
	
	WET_PokeParticlePosGet_ClientType(client_type, &vec, WES_ContestFlag_Get(wsp), camera_type);
	SPL_SetEmitterPositionX(emit, vec.x);
	SPL_SetEmitterPositionY(emit, vec.y);
	SPL_SetEmitterPositionZ(emit, vec.z);
}

///< パターンごとの座標補正
void EmitCall_SepPos(EMIT_PTR emit)
{
	WE_SYS_PTR wsp;
	int at_no;
	int df_no;
	int at;
	int df;
	int pos_ofs_x;
	int pos_ofs_y;
	VecFx32 vec;
//	s16 pos[ 6 ] = { 0, 0, -10, +10, +10, -10 };
	s16 pos[ 6 ] = { 0,0,0,0,0,0 };
//	s16 pos_tbl[][6] = {};

	s16 pos_tbl_x[][6] = {
	//			AA	  BB     A     B     C     D   
	/*AA*/	{    0,    0, 0xFF, 0xFF, 0xFF, 0xFF, },
	/*BB*/	{    0,    0, 0xFF, 0xFF, 0xFF, 0xFF, },
	/*A */	{ 0xFF, 0xFF, 0xFF,  -16, 0xFF,  -16, },
	/*B */	{ 0xFF, 0xFF,  +32, 0xFF,  +32, 0xFF, },
	/*C */	{ 0xFF, 0xFF, 0xFF,  +16, 0xFF,   +4, },
	/*D */	{ 0xFF, 0xFF,  -16, 0xFF,   +0, 0xFF, }, 
	};
	
	s16 pos_tbl_y[][6] = {
	//			AA	  BB     A     B     C     D   
	/*AA*/	{    0,    0, 0xFF, 0xFF, 0xFF, 0xFF, },
	/*BB*/	{    0,    0, 0xFF, 0xFF, 0xFF, 0xFF, },
	/*A */	{ 0xFF, 0xFF, 0xFF,  +16, 0xFF,  +16, },
	/*B */	{ 0xFF, 0xFF,   +0, 0xFF,    0, 0xFF, },
	/*C */	{ 0xFF, 0xFF, 0xFF,    0, 0xFF,    0, },
	/*D */	{ 0xFF, 0xFF,  +24, 0xFF,  +24, 0xFF, }, 
	};
	wsp = Particle_GetTempPtr();
	
	at_no = WeSysATNoGet(wsp);
	df_no = WeSysDFNoGet(wsp);
	at	  = WET_ClientTypeGet(wsp, at_no);
	df	  = WET_ClientTypeGet(wsp, df_no);
	
//	OS_Printf("at == %2d",at);
	
	pos_ofs_x = pos_tbl_x[ at ][ df ] * PT_LCD_DOT;
	pos_ofs_y = pos_tbl_y[ at ][ df ] * PT_LCD_DOT;
	
	VEC_Set(&vec, pos_ofs_x, pos_ofs_y, 0);
	
	SPL_SetEmitterPositionX(emit, vec.x);
	SPL_SetEmitterPositionY(emit, vec.y);
	SPL_SetEmitterPositionZ(emit, vec.z);
}

static void ExMode_PosReverse(int mode, s8 flag, VecFx32* p)
{
	fx32* x = &(p->x);
	fx32* y = &(p->y);
	fx32* z = &(p->z);
	switch(mode){
	case WP_POS_REVERSE_NONE:
		break;
	case WP_POS_REVERSE_X:
		(*x) *= flag;
		break;
	case WP_POS_REVERSE_Y:
		(*y) *= flag;
		break;
	case WP_POS_REVERSE_Z:
		(*z) *= flag;
		break;
	case WP_POS_REVERSE_XY:
		(*x) *= flag;
		(*y) *= flag;
		break;
	case WP_POS_REVERSE_XZ:
		(*x) *= flag;
		(*z) *= flag;
		break;
	case WP_POS_REVERSE_YZ:
		(*y) *= flag;
		(*z) *= flag;
		break;
	case WP_POS_REVERSE_ALL:
		(*x) *= flag;
		(*y) *= flag;
		(*z) *= flag;
		break;
	};
}

static void ExMode_Convergence(WE_SYS_PTR we_sys, EMIT_PTR emit, int start_client,int end_client, int ex_mode, s8 flag, VecFx32* epos)
{
	///< 拡張モードで集束位置を決める
	VecFx32 p = { 0,0,0 };		///< マグネット用
	
	switch(ex_mode){
	case AXIS_EX_MODE_NONE:
		OS_Printf("指定なし\n");
		break;
		
	case AXIS_EX_MODE_DEFAULT_CNV:
		SplSub_GetSPLField_ConvergencePos(emit, &p);		///< 集束位置取得
		p.x *= flag;										///< フラグで反転するかどうかを決める
		p.y *= flag;
		p.z *= flag;
		break;
		
	case AXIS_EX_MODE_CENTER_CNV:
		p.x = WP_DEF_CENTER_X * flag;						///< フラグで反転するかどうかを決める
		p.y = WP_DEF_CENTER_Y * flag;
		p.z = WP_DEF_CENTER_Z * flag;
		break;
		
	case AXIS_EX_MODE_TP_CNV:
		WET_PokeParticlePosGet(we_sys, end_client, &p);		///< 対象ポケモンの位置
		break;
		
	case AXIS_EX_MODE_PP_CNV:	
		WET_PokeParticlePosGet(we_sys, start_client, &p);	///< 基点ポケモンの位置
		break;
	case AXIS_EX_MODE_SET_CNV:
		{
			int pt[4] = { 0, 0, 0, 0 };
			WeSysExDataGet(we_sys, pt, 4);
			VEC_Set(&p, pt[0],pt[1],pt[2]);
			ExMode_PosReverse(pt[3], flag, &p);
		}
		break;
	};

	p.x -= epos->x;
	p.y -= epos->y;
	p.z -= epos->z;

	SplSub_SetSPLField_ConvergencePos(emit, &p);			///< 集束位置反映
}

static void ExMode_Magnet(WE_SYS_PTR we_sys, EMIT_PTR emit, int start_client,int end_client, int ex_mode, s8 flag, VecFx32* epos)
{
	///< 拡張モードで集束位置を決める
	VecFx32 p = { 0,0,0 };		///< マグネット用

	switch(ex_mode){
	case AXIS_EX_MODE_NONE:
		OS_Printf("指定なし\n");
		break;
	case AXIS_EX_MODE_DEFAULT_MAG:
		SplSub_GetSPLField_MagnetPos(emit, &p);				///< 集束位置取得
		p.x *= flag;										///< フラグで反転するかどうかを決める
		p.y *= flag;
		p.z *= flag;
		break;
	case AXIS_EX_MODE_CENTER_MAG:
		p.x = WP_DEF_CENTER_X * flag;						///< フラグで反転するかどうかを決める
		p.y = WP_DEF_CENTER_Y * flag;
		p.z = WP_DEF_CENTER_Z * flag;
		break;
	case AXIS_EX_MODE_TP_MAG:
		WET_PokeParticlePosGet(we_sys, end_client, &p);		///< 対象ポケモンの位置
		break;
	case AXIS_EX_MODE_PP_MAG:	
		WET_PokeParticlePosGet(we_sys, start_client, &p);	///< 基点ポケモンの位置
		break;
	case AXIS_EX_MODE_SET_MAG:
		{
			int pt[4] = { 0, 0, 0, 0 };
			WeSysExDataGet(we_sys, pt, 4);
			VEC_Set(&p, pt[0],pt[1],pt[2]);
			ExMode_PosReverse(pt[3], flag, &p);
		}
		break;
	};
	p.x -= epos->x;
	p.y -= epos->y;
	p.z -= epos->z;
	OS_Printf("マグネット位置 x = %d y = %d z = %d\n", p.x,p.y,p.z);
	SplSub_SetSPLField_MagnetPos(emit, &p);					///< 集束位置反映
}

enum {
	WP_EX_TYPE_NONE = 0,
	WP_EX_TYPE_CNV,
	WP_EX_TYPE_MAG,
};

//--------------------------------------------------------------
/**
 * @brief   AxisAttack,AxisDefence共通処理サブ関数
 *
 * @param   emit				エミッタへのポインタ
 * @param   start_client		エフェクト出現位置のクライアントNo
 * @param   end_client			エフェクト終了位置のクライアントNo
 * @param	ex_mode				拡張モード
 */
//--------------------------------------------------------------
static void Sub_AxisAttackCommon(WE_SYS_PTR we_sys, EMIT_PTR emit, int start_client,int end_client, int ex_type, int ex_mode)
{
	PTC_PTR ptc;
	VecFx32 vex;
	int attack_type, defence_type;
	VecFx16 axis;
	s8	flag = 1;	///< マグネット用
	
	ptc = WeSysPTCPointerGet(we_sys);
	
	//エミッタの方向を設定
	attack_type  = WET_ClientTypeGet(we_sys, start_client);
	defence_type = WET_ClientTypeGet(we_sys, end_client);

	//移動方向取得
	{
		int aa_bb[3], a_b[3], a_c[3], a_d[3], c_a[3], c_b[3], c_d[3];
		
		WeSysExDataGet(we_sys, aa_bb, 3);
		WeSysExDataGet(we_sys, a_b,   3);
		WeSysExDataGet(we_sys, a_d,   3);
		WeSysExDataGet(we_sys, a_c,   3);
		WeSysExDataGet(we_sys, c_b,   3);
		WeSysExDataGet(we_sys, c_d,   3);
		WeSysExDataGet(we_sys, c_a,   3);
		
		switch(attack_type){
		case CLIENT_TYPE_AA:
		default:
			VEC_Fx16Set(&axis, aa_bb[0], aa_bb[1], aa_bb[2]);
			break;
		case CLIENT_TYPE_BB:
			flag = -1;
			VEC_Fx16Set(&axis, -aa_bb[0], -aa_bb[1], -aa_bb[2]);
			break;
		case CLIENT_TYPE_A:
			if(defence_type == CLIENT_TYPE_B){
				VEC_Fx16Set(&axis, a_b[0], a_b[1], a_b[2]);
			}
			else if(defence_type == CLIENT_TYPE_D){
				VEC_Fx16Set(&axis, a_d[0], a_d[1], a_d[2]);
			}
			else{	//CLIENT_TYPE_C
				VEC_Fx16Set(&axis, a_c[0], a_c[1], a_c[2]);
			}
			break;
		case CLIENT_TYPE_B:
			flag = -1;
			if(defence_type == CLIENT_TYPE_A){
				VEC_Fx16Set(&axis, -a_b[0], -a_b[1], -a_b[2]);
			}
			else if(defence_type == CLIENT_TYPE_D){
				VEC_Fx16Set(&axis, -a_c[0], -a_c[1], -a_c[2]);
			}
			else{	//CLIENT_TYPE_C
				VEC_Fx16Set(&axis, -c_b[0], -c_b[1], -c_b[2]);
			}
			break;
		case CLIENT_TYPE_C:
			if(defence_type == CLIENT_TYPE_B){
				VEC_Fx16Set(&axis, c_b[0], c_b[1], c_b[2]);
			}
			else if(defence_type == CLIENT_TYPE_D){
				VEC_Fx16Set(&axis, c_d[0], c_d[1], c_d[2]);
			}
			else{	//CLIENT_TYPE_C
				VEC_Fx16Set(&axis, c_a[0], c_a[1], c_a[2]);
			}
			break;
		case CLIENT_TYPE_D:
			flag = -1;
			if(defence_type == CLIENT_TYPE_B){
				VEC_Fx16Set(&axis, -c_a[0], -c_a[1], -c_a[2]);
			}
			else if(defence_type == CLIENT_TYPE_A){
				VEC_Fx16Set(&axis, -a_d[0], -a_d[1], -a_d[2]);
			}
			else{	//CLIENT_TYPE_C
				VEC_Fx16Set(&axis, -c_d[0], -c_d[1], -c_d[2]);
			}
			break;
		}
	}

	flag = SignCheck(we_sys, start_client, end_client);
	{
		///< 座標設定

		int pt[3] = { 0, 0, 0 };
		VecFx32 tmp;
		WeSysExDataGet(we_sys, pt, 3);
	
		WET_PokeParticlePosGet(we_sys, start_client, &tmp);

		if (pt[0] == 0 && pt[1] == 0 && pt[2] == 0){
			vex = tmp;
			SPL_SetEmitterPositionX(emit, tmp.x);
			SPL_SetEmitterPositionY(emit, tmp.y);
			SPL_SetEmitterPositionZ(emit, tmp.z);
			OS_Printf("基本座標\n");
			OS_Printf("pos x = %d y = %d, z = %d\n", tmp.x,tmp.y,tmp.z);
		}
		else {
			VEC_Set(&vex, pt[0],pt[1],pt[2]);
			if (pt[0] == WP_DEF_CENTER_X && pt[1] == WP_DEF_CENTER_Y){		///< 中心指定なら、反転しない
				flag = 1;
			}
			vex.x *= flag;
			vex.y *= flag;
			vex.z  = tmp.z * flag;
			SPL_SetEmitterPositionX(emit, vex.x);
			SPL_SetEmitterPositionY(emit, vex.y);
			SPL_SetEmitterPositionZ(emit, vex.z);
			OS_Printf("指定座標\n");
			OS_Printf("pos x = %d y = %d, z = %d\n", vex.x,vex.y,vex.z);
		}
	}

	{
		///< 拡張モード
		switch(ex_type){
		case WP_EX_TYPE_NONE:
			OS_Printf("拡張タイプなし\n");
			break;
		
		case WP_EX_TYPE_CNV:
			OS_Printf("コンバージェンス\n");
			ExMode_Convergence(we_sys, emit, start_client, end_client, ex_mode, flag, &vex);
			break;
		
		case WP_EX_TYPE_MAG:
			OS_Printf("マグネット\n");
			ExMode_Magnet(we_sys, emit, start_client, end_client, ex_mode, flag, &vex);
			break;
		}
	}

#ifdef PM_DEBUG
	
	DEBUG_ForeverEmitterFlag(emit, &vex);

#endif
	
	SPL_SetEmitterAxis(emit, &axis);
}

// 共通初期化基本関数
static void Sub_AxisAttackCommonDefaultInit(EMIT_PTR emit, int type, int mode)
{
	int attack, defence;
	WE_SYS_PTR we_sys;
	
	we_sys = Particle_GetTempPtr();
	attack = WeSysATNoGet(we_sys);
	defence = WeSysDFNoGet(we_sys);

	Sub_AxisAttackCommon(we_sys, emit, attack, defence, type, mode);
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：味方、敵の攻撃でエミッタの方向を変更する(攻撃側＞防御側への直線を想定)
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
void EmitCall_AxisAttack(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_NONE, AXIS_EX_MODE_NONE);
}

void EmitCall_AxisAttack_DefaultCNV(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_CNV, AXIS_EX_MODE_DEFAULT_CNV);
}

void EmitCall_AxisAttack_CenterCNV(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_CNV, AXIS_EX_MODE_CENTER_CNV);
}

void EmitCall_AxisAttack_TargetPokemonCNV(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_CNV, AXIS_EX_MODE_TP_CNV);
}

void EmitCall_AxisAttack_PlayerPokemonCNV(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_CNV, AXIS_EX_MODE_PP_CNV);
}

void EmitCall_AxisAttack_PosSetCNV(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_CNV, AXIS_EX_MODE_SET_CNV);
}


/// マグネット
void EmitCall_AxisAttack_DefaultMAG(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_MAG, AXIS_EX_MODE_DEFAULT_MAG);
}

void EmitCall_AxisAttack_CenterMAG(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_MAG, AXIS_EX_MODE_CENTER_MAG);
}

void EmitCall_AxisAttack_TargetPokemonMAG(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_MAG, AXIS_EX_MODE_TP_MAG);
}

void EmitCall_AxisAttack_PlayerPokemonMAG(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_MAG, AXIS_EX_MODE_PP_MAG);
}

void EmitCall_AxisAttack_PosSetMAG(EMIT_PTR emit)
{
	Sub_AxisAttackCommonDefaultInit(emit, WP_EX_TYPE_MAG, AXIS_EX_MODE_SET_MAG);
}

//--------------------------------------------------------------
/**
 * @brief   汎用関数：味方、敵の攻撃でエミッタの方向を変更する(防御側＞攻撃側への直線を想定)
 * @param   emit		生成したエミッタへのポインタ
 */
//--------------------------------------------------------------
void EmitCall_AxisDefence(EMIT_PTR emit)
{
	int attack, defence;
	WE_SYS_PTR we_sys;
	
	we_sys = Particle_GetTempPtr();
	attack = WeSysATNoGet(we_sys);
	defence = WeSysDFNoGet(we_sys);

	Sub_AxisAttackCommon(we_sys, emit, defence, attack, WP_EX_TYPE_NONE, AXIS_EX_MODE_NONE);
}

//--------------------------------------------------------------
/**
 * @brief	パーティクルのスピードを変更する
 * @param	emit		生成したエミッタのポインタ
 */
//--------------------------------------------------------------
void EmitCall_InitSpeedSet(EMIT_PTR emit)
{
	WE_SYS_PTR ws;
	int		param;
	f32		temp;
	f32		data;
	fx16	initvelo;
	
	ws = Particle_GetTempPtr();
	
	initvelo = SplSub_GetEmitterInitVelocityPos(emit);
	param = WeSysGPWorkGet(ws, 0);
	data = (f32)(param / 100.0f);	
	temp = FX_FX16_TO_F32(initvelo);
	temp *= data;
	initvelo = FX_F32_TO_FX16(temp);
	
	SPL_SetEmitterInitVelocityPos(emit,  initvelo);
}

