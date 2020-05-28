//==============================================================================
/**
 * @file	we_tool.c
 * @brief	技エフェクト関係のツール
 * @author	matsuda
 * @date	2005.07.29(金)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "we_tool.h"
#include "we_err.h"
#include "battle/battle_common.h"
#include "include/contest/actin_ex.h"

//#include "wazaeffect/we_mana.h"

#include "we_def.h"
#include "wazatool.h"


//==============================================================================
//	グローバル変数定義
//==============================================================================
#ifdef PM_DEBUG
///技エフェクト関連のデバッグ用ワーク
WE_DEBUG_WORK WeDebugWork;
#endif


//==============================================================================
//	データ定義
//==============================================================================
static const VecFx32 EnemyEye = {
	0x1700, 0x4d00, -0x1000
};
static const VecFx32 EnemyUp = {
	0, -FX32_ONE, 0
};

//--------------------------------------------------------------
/**
 * @brief	クライアントNoから、クライアントタイプを取得
 *
 * @param	wsp	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WET_ClientTypeGet(WE_SYS_PTR wsp, int client_no)
{
	return WeSysClientTypeGet(wsp, client_no);
}


//--------------------------------------------------------------
/**
 * @brief	クライアントNOからサイドを取得する
 *
 * @param	wsp	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WET_SideCheck(WE_SYS_PTR wsp, int client_no)
{
	int type;
	int side;
	
	type = WeSysClientTypeGet(wsp, client_no);
	
	switch(type){
	case CLIENT_TYPE_AA:
	case CLIENT_TYPE_A:
	case CLIENT_TYPE_C:
		side = SIDE_MINE;
		break;
	
	case CLIENT_TYPE_BB:
	case CLIENT_TYPE_B:
	case CLIENT_TYPE_D:
		side = SIDE_ENEMY;
		break;
	}
	
	return side;
}

int WET_CheckClientNo(WE_SYS_PTR wsp, int type)
{
	int i;
	int t;
	
	for (i = 0; i < 4; i++){
		
		t = WeSysClientTypeGet(wsp, i);
		
		if (t == type){
			return i;
		}
	}
	
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief	相方のクライアント番号を取得
 *
 * @param	we_sys	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WET_AllySideClientNoGet(WE_SYS_PTR wsp, int client_no)
{
	int i;
	int type;
	int check;
	
	type = WeSysClientTypeGet(wsp, client_no);
	
	if (type == CLIENT_TYPE_AA
	||	type == CLIENT_TYPE_BB){
		return type;
	}
	
	for (i = 0; i < CLIENT_MAX; i++){
		check = WeSysClientTypeGet(wsp, i);
		
		switch(type){
		case CLIENT_TYPE_A:
			if (check == CLIENT_TYPE_C){
				return i;
			}
			break;
		case CLIENT_TYPE_C:
			if (check == CLIENT_TYPE_A){
				return i;
			}
			break;
		case CLIENT_TYPE_B:
			if (check == CLIENT_TYPE_D){
				return i;
			}
			break;
		case CLIENT_TYPE_D:
			if (check == CLIENT_TYPE_B){
				return i;
			}
			break;
		}
	}

	GF_ASSERT(0);
	
	return type;
}


//--------------------------------------------------------------
/**
 * @brief	対角線上のクライアントタイプ取得
 *
 * @param	wsp	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WET_DiagonalClientTypeGet(WE_SYS_PTR wsp, int client_no)
{
	int type;
	
	type = WeSysClientTypeGet(wsp, client_no);
	
	return WazaTool_DiagonalClientTypeGet_ClientType(type);
}

//--------------------------------------------------------------
/**
 * @brief   指定クライアントタイプと対角線上の反対側にあるクライアントタイプを取得する
 * @param   client_type		クライアントタイプ
 * @retval  対角線上にある反対側のクライアントタイプ
 */
//--------------------------------------------------------------
int WazaTool_DiagonalClientTypeGet_ClientType(int client_type)
{
	switch(client_type){
	case CLIENT_TYPE_AA:
		return CLIENT_TYPE_BB;
	case CLIENT_TYPE_BB:
		return CLIENT_TYPE_AA;
	case CLIENT_TYPE_A:
		return CLIENT_TYPE_B;
	case CLIENT_TYPE_B:
		return CLIENT_TYPE_A;
	case CLIENT_TYPE_C:
		return CLIENT_TYPE_D;
	case CLIENT_TYPE_D:
		return CLIENT_TYPE_C;
	}
	GF_ASSERT(0);
	return CLIENT_TYPE_AA;
}

void WET_PokeDefaultPosGet_ClientType(int client_type, int contest_flag, WT_POINT* p)
{
	const WT_POINT def[] = {
		{ APPEAR_X_TYPE_AA, APPEAR_Y_TYPE_AA },
		{ APPEAR_X_TYPE_BB, APPEAR_Y_TYPE_BB },
		{ APPEAR_X_TYPE_A,  APPEAR_Y_TYPE_A },
		{ APPEAR_X_TYPE_B,  APPEAR_Y_TYPE_B },
		{ APPEAR_X_TYPE_C,  APPEAR_Y_TYPE_C },
		{ APPEAR_X_TYPE_D,  APPEAR_Y_TYPE_D },
	};
	
	const WT_POINT con_p[] = { 
		{ CONTEST_ATTACK_POKE_X,  CONTEST_ATTACK_POKE_Y	 },
		{ CONTEST_DEFENCE_POKE_X, CONTEST_DEFENCE_POKE_Y },
		{ CONTEST_ATTACK_POKE_X,  CONTEST_ATTACK_POKE_Y	 },
		{ CONTEST_DEFENCE_POKE_X, CONTEST_DEFENCE_POKE_Y },
		{ CONTEST_ATTACK_POKE_X,  CONTEST_ATTACK_POKE_Y	 },
		{ CONTEST_DEFENCE_POKE_X, CONTEST_DEFENCE_POKE_Y },
	};
	
	if (contest_flag){
		*p = con_p[ client_type ];
		return;
	}
	
	*p = def[ client_type ];
}


void WET_PokeDefaultPosGet_ClientNo(WE_SYS_PTR wsp, int client_no, WT_POINT* p)
{
	int client_type, contest_flag;

	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeDefaultPosGet_ClientType(client_type, contest_flag, p);
}


//--------------------------------------------------------------
/**
 * @brief   クライアントタイプを指定してポケモンのパーティクル座標を取得する
 *
 * @param   client_type		クライアントタイプ
 * @param   ret				座標代入先
 * @param   contest_flag	TRUE=コンテスト。　FALSE:戦闘
 */
//--------------------------------------------------------------
///< 透視射影 PT座標 ()
#define PX_AA_R	(-9616)
#define PY_AA_R	(-5464)
#define PX_BB_R	(+11056)
#define PY_BB_R	(+4400)
#define PX_A_R	(-14936)
#define PY_A_R	(-5032)
#define PX_B_R	(+7368)
#define PY_B_R	(+5960)
#define PX_C_R	(-5364)
#define PY_C_R	(-6568)
#define PX_D_R	(+15184)
#define PY_D_R	(+4424)
#define PX_CON_A_R	(+7368)		//PX_B_R
#define PY_CON_A_R	(-5032)		//PY_A_R
#define PX_CON_B_R	(PX_C_R)	//PX_C_R
#define PY_CON_B_R	(PY_D_R)		//PY_B_R

#define LX_AA_R	(-3968)
#define LY_AA_R	(-3328)
#define LX_BB_R	(+9344)
#define LY_BB_R	(+2176)
#define LX_A_R	(-9856)
#define LY_A_R	(-3200)
#define LX_B_R	(+13568)
#define LY_B_R	(+2944)
#define LX_C_R	(-2308)
#define LY_C_R	(-5632)
#define LX_D_R	(+6912)
#define LY_D_R	(+4096)
#define LX_CON_A_R	(+13568)		//LX_B_R
#define LY_CON_A_R	(-3200)		//LY_A_R
#define LX_CON_B_R	(LX_C_R)		//LX_A_R
#define LY_CON_B_R	(LY_D_R)		//LY_B_R

#define LAX_AA_R	(+9080)
#define LAY_AA_R	(+5536)
#define LAX_BB_R	(-6936)
#define LAY_BB_R	(-4832)
#define LAX_A_R		(+10824)
#define LAY_A_R		(+7488)
#define LAX_B_R		(-9536)
#define LAY_B_R		(-3120)
#define LAX_C_R		(+5152)
#define LAY_C_R		(+7488)
#define LAX_D_R		(-5408)
#define LAY_D_R		(-6000)
#define LAX_CON_A_R		(-9536)		//LAX_B_R
#define LAY_CON_A_R		(+7488)		//LAY_A_R
#define LAX_CON_B_R		(LAX_C_R)		//LAX_A_R
#define LAY_CON_B_R		(LAY_D_R)		//LAY_B_R

///< 正射影 PT座標
#define PX_AA_O	(-10240)
#define PY_AA_O	(-6400)
#define PX_BB_O	(+10240)
#define PY_BB_O	(+3072)
#define PX_A_O	(-15360)
#define PY_A_O	(-6272)
#define PX_B_O	(+13568)
#define PY_B_O	(+2944)
#define PX_C_O	(-7552)
#define PY_C_O	(-6912)
#define PX_D_O	(+6912)
#define PY_D_O	(+4096)
#define PX_CON_A_O	(+13568)	//PX_B_O
#define PY_CON_A_O	(-6272)		//PY_A_O
#define PX_CON_B_O	(PX_C_O)	//PX_A_O
#define PY_CON_B_O	(PY_D_O)	//PY_B_O

///< 通常レーザー2(ハイドロポンプ)
#define L2X_AA_O	(-6720)//(-3968)
#define L2Y_AA_O	(-5792)//(-3328)
#define L2X_BB_O	(+14528)//(+13568)
#define L2Y_BB_O	(+8032)//(+2944)
#define L2X_A_O	(-9856)
#define L2Y_A_O	(-3200)
#define L2X_B_O	(+13568)
#define L2Y_B_O	(+2944)
#define L2X_C_O	(-2308)
#define L2Y_C_O	(-5632)
#define L2X_D_O	(+6912)
#define L2Y_D_O	(+4096)
#define L2X_CON_A_O	(+13568)	//L2X_B_O
#define L2Y_CON_A_O	(-3200)		//L2Y_A_O
#define L2X_CON_B_O	(L2X_C_O)		//L2X_A_O
#define L2Y_CON_B_O	(L2Y_D_O)		//L2Y_B_O


///< 通常レーザー3(サイケ光線系)
#define L3X_AA_O	(-8632)		// o
#define L3Y_AA_O	(-6936)		// o
#define L3X_BB_O	(+12904)	
#define L3Y_BB_O	(+5108)
#define L3X_A_O		(-9456)		// o
#define L3Y_A_O		(-3104)		// o
#define L3X_B_O		(+17984)	// o
#define L3Y_B_O		(+6336)		// o
#define L3X_C_O		(-2480)		// o
#define L3Y_C_O		(-5568)		// o
#define L3X_D_O		(+12816)	// o
#define L3Y_D_O		(+5600)		// o
#define L3X_CON_A_O	(+13568)	//L2X_B_O
#define L3Y_CON_A_O	(-3200)		//L2Y_A_O
#define L3X_CON_B_O	(L3X_C_O)		//L2X_A_O
#define L3Y_CON_B_O	(L3Y_D_O)		//L2Y_B_O


///< 通常レーザー095
#define L095X_AA_O		(-12544)		// o
#define L095Y_AA_O		(-3840)		// o
#define L095X_BB_O		(+5432)	
#define L095Y_BB_O		(+6680)
#define L095X_A_O		(-17856)	// o
#define L095Y_A_O		(-3624)		// o
#define L095X_B_O		(+8024)
#define L095Y_B_O		(+6008)
#define L095X_C_O		(-8200)		// o
#define L095Y_C_O		(-4776)		// o
#define L095X_D_O		(+2008)
#define L095Y_D_O		(+4696)

#define L095X_CON_A_O	(+7568)	//L2X_B_O
#define L095Y_CON_A_O	(-3200)		//L2Y_A_O
#define L095X_CON_B_O	(L095X_C_O)	//L2X_A_O
#define L095Y_CON_B_O	(L095Y_D_O)	//L2Y_B_O

///< 通常レーザー161
#define L161X_AA_O		(-9632)		// o
#define L161Y_AA_O		(-5856)		// o
#define L161X_BB_O		(+13144)	// o
#define L161Y_BB_O		(+11272)	// o
#define L161X_A_O		(-12592)	// o
#define L161Y_A_O		(-2976)		// o
#define L161X_B_O		(+13072)	// o
#define L161Y_B_O		(+6208)		// o
#define L161X_C_O		(-5600)		// o
#define L161Y_C_O		(-6480)		// o
#define L161X_D_O		(+8024)		// o
#define L161Y_D_O		(+6312)		// o
#define L161X_CON_A_O	(+13568)	//L2X_B_O
#define L161Y_CON_A_O	(-3200)		//L2Y_A_O
#define L161X_CON_B_O	(L161X_C_O)		//L2X_A_O
#define L161Y_CON_B_O	(L161Y_D_O)		//L2Y_B_O


///< 通常レーザー308
#define L308X_AA_O		(-4144)		// o
#define L308Y_AA_O		(-5200)		// o
#define L308X_BB_O		(+16592)	// o
#define L308Y_BB_O		(+5168)		// o
#define L308X_A_O		(-6366)		// o
#define L308Y_A_O		(-3776)		// o
#define L308X_B_O		(+17408)	// o
#define L308Y_B_O		(+5184)		// o
#define L308X_C_O		(-632)		// o
#define L308Y_C_O		(-5176)		// o
#define L308X_D_O		(+11784)		// o
#define L308Y_D_O		(+6152)		// o
#define L308X_CON_A_O	(+13568)	//L2X_B_O
#define L308Y_CON_A_O	(-3200)		//L2Y_A_O
#define L308X_CON_B_O	(L308X_C_O)		//L2X_A_O
#define L308Y_CON_B_O	(L308Y_D_O)		//L2Y_B_O


///< 通常レーザー304
#define L304X_AA_O		(-12480)		// o
#define L304Y_AA_O		(-4288)		// o
#define L304X_BB_O		(+13184)	// o
#define L304Y_BB_O		(+7616)		// o
#define L304X_A_O		(-14912)		// o
#define L304Y_A_O		(-2176)		// o
#define L304X_B_O		(+16128)	// o
#define L304Y_B_O		(+7360)		// o
#define L304X_C_O		(-8448)		// o
#define L304Y_C_O		(-8384)		// o
#define L304X_D_O		(+9984)		// o
#define L304Y_D_O		(+9472)		// o
#define L304X_CON_A_O	(+13568)	//L2X_B_O
#define L304Y_CON_A_O	(-3200)		//L2Y_A_O
#define L304X_CON_B_O	(L304X_C_O)		//L2X_A_O
#define L304Y_CON_B_O	(L304Y_D_O)		//L2Y_B_O


///< 通常レーザー320
#define L320X_AA_O		(-1792)	// o
#define L320Y_AA_O		(-4224)	// o
#define L320X_BB_O		(+16896)// o
#define L320Y_BB_O		(+3328)	// o
#define L320X_A_O		(-6080)		// o
#define L320Y_A_O		(-5504)		// o
#define L320X_B_O		(+20672)		// o
#define L320Y_B_O		(+3480)		// o
#define L320X_C_O		(+512)		// o
#define L320Y_C_O		(-6528)		// o
#define L320X_D_O		(+13888)		// o
#define L320Y_D_O		(+3480)		// o
#define L320X_CON_A_O	(+13568)	//L2X_B_O
#define L320Y_CON_A_O	(-3200)		//L2Y_A_O
#define L320X_CON_B_O	(L320X_C_O)		//L2X_A_O
#define L320Y_CON_B_O	(L320Y_D_O)		//L2Y_B_O



///< 通常レーザー406
#define L406X_AA_O		(-8320)	// o
#define L406Y_AA_O		(-4160)	// o
#define L406X_BB_O		(+10880)// o
#define L406Y_BB_O		(+4480)	// o
#define L406X_A_O		(-12032)		// o
#define L406Y_A_O		(-3200)		// o
#define L406X_B_O		(+13440)		// o
#define L406Y_B_O		(+5408)		// o
#define L406X_C_O		(-6848)		// o
#define L406Y_C_O		(-6144)		// o
#define L406X_D_O		(+6208)		// o
#define L406Y_D_O		(+5440)		// o
#define L406X_CON_A_O	(+13568)	//L2X_B_O
#define L406Y_CON_A_O	(-3200)		//L2Y_A_O
#define L406X_CON_B_O	(L406X_C_O)		//L2X_A_O
#define L406Y_CON_B_O	(L406Y_D_O)		//L2Y_B_O

///< 通常レーザー(今のトコハイドロポンプ以外)
#define LX_AA_O	(-6568)			///< 06.05.30
#define LY_AA_O	(-4000)
#define LX_BB_O	(+8800)			///< 06.05.30
#define LY_BB_O	(+6464)
#define LX_A_O	(-11400)		///< 06.05.30
#define LY_A_O	(-2944)
#define LX_B_O	(+12656)		///< 06.05.30
#define LY_B_O	(+5736)
#define LX_C_O	(-2984)			///< 06.05.30
#define LY_C_O	(-5272)
#define LX_D_O	(+6904)			///< 06.05.30
#define LY_D_O	(+8264)
#define LX_CON_A_O	(+12656)	//LX_B_O
#define LY_CON_A_O	(-2944)		//LY_A_O
#define LX_CON_B_O	(LX_C_O)		//LX_A_O
#define LY_CON_B_O	(LY_D_O)		//LY_B_O

#define LAX_AA_O	(+9080)
#define LAY_AA_O	(+5536)
#define LAX_BB_O	(-6936)
#define LAY_BB_O	(-4832)
#define LAX_A_O		(+10824)
#define LAY_A_O		(+7488)
#define LAX_B_O		(-9536)
#define LAY_B_O		(-3120)
#define LAX_C_O		(+5152)
#define LAY_C_O		(+7488)
#define LAX_D_O		(-5408)
#define LAY_D_O		(-6000)
#define LAX_CON_A_O		(-9536)		//LAX_B_O
#define LAY_CON_A_O		(+7488)		//LAY_A_O
#define LAX_CON_B_O		(LAX_C_O)	//LAX_A_O
#define LAY_CON_B_O		(LAX_D_O)		//LAY_B_O

///< リング用
#define RX_AA_R	(-6248)//(-3968)
#define RY_AA_R	(-2944)//(-3328)
#define RX_BB_R	(+8280)//(+9344)
#define RY_BB_R	(+5432)//(+2176)
#define RX_A_R	(-9856)
#define RY_A_R	(-3200)
#define RX_B_R	(+13568)
#define RY_B_R	(+2944)
#define RX_C_R	(-2308)
#define RY_C_R	(-5632)
#define RX_D_R	(+6912)
#define RY_D_R	(+4096)
#define RX_CON_A_R	(+13568)	//LX_B_R
#define RY_CON_A_R	(-3200)		//LY_A_R
#define RX_CON_B_R	(LX_C_R)		//LX_A_R
#define RY_CON_B_R	(LY_D_R)		//LY_B_R

#define RX_AA_O	(-6248)//(-3968)
#define RY_AA_O	(-2944)//(-3328)
#define RX_BB_O	(+8280)//(+9344)
#define RY_BB_O	(+5432)//(+2176)
#define RX_A_O	(-9856)
#define RY_A_O	(-3200)
#define RX_B_O	(+13568)
#define RY_B_O	(+2944)
#define RX_C_O	(-2308)
#define RY_C_O	(-5632)
#define RX_D_O	(+6912)
#define RY_D_O	(+4096)
#define RX_CON_A_O	(+13568)	//LX_B_O
#define RY_CON_A_O	(-2944)		//LY_A_O
#define RX_CON_B_O	(LX_C_O)		//LX_A_O
#define RY_CON_B_O	(LY_D_O)		//LY_B_O

enum {
	POS_MODE_NORMAL = 0,
	POS_MODE_LASER,
	POS_MODE_LASER_2,
	POS_MODE_LASER_3,
	POS_MODE_L095,
	POS_MODE_L161,
	POS_MODE_L308,
	POS_MODE_L304,
	POS_MODE_L320,
	POS_MODE_L406,
	POS_MODE_LOOK_AT,
	POS_MODE_RING,
	
	POS_MODE_MAX
};
#define POS_TBL_NUM		(POS_MODE_MAX * 2)
static void ParticlePosGet_Private(int client_type, VecFx32 *ret, int contest_flag, int camera_mode, int pos_mode)
{
	int tbl_id;
	const VecFx32* vec;
	const VecFx32 vec_tbl[][ POS_TBL_NUM ] = {		
		{	///< AA
			{ PX_AA_R,	PY_AA_R,	WET_PARTICLE_Z_AA },
			{ PX_AA_O,	PY_AA_O,	WET_PARTICLE_Z_AA },
			{ LX_AA_R,	LY_AA_R,	WET_PARTICLE_Z_AA },
			{ LX_AA_O,	LY_AA_O,	WET_PARTICLE_Z_AA },
			{ LX_AA_R,	LY_AA_R,	WET_PARTICLE_Z_AA }, /// 2
			{ L2X_AA_O,	L2Y_AA_O,	WET_PARTICLE_Z_AA },
			{ L3X_AA_O,	L3Y_AA_O,	0 },
			{ L3X_AA_O,	L3Y_AA_O,	0 },
			{ L095X_AA_O,	L095Y_AA_O,	0 },
			{ L095X_AA_O,	L095Y_AA_O,	0 },
			{ L161X_AA_O,	L161Y_AA_O,	0 },
			{ L161X_AA_O,	L161Y_AA_O,	0 },
			{ L308X_AA_O,	L308Y_AA_O,	0 },
			{ L308X_AA_O,	L308Y_AA_O,	0 },
			{ L304X_AA_O,	L304Y_AA_O,	0 },
			{ L304X_AA_O,	L304Y_AA_O,	0 },
			{ L320X_AA_O,	L320Y_AA_O,	0 },
			{ L320X_AA_O,	L320Y_AA_O,	0 },
			{ L406X_AA_O,	L406Y_AA_O,	0 },
			{ L406X_AA_O,	L406Y_AA_O,	0 },
			{ LAX_AA_R, LAY_AA_R,	0 },
			{ LAX_AA_O, LAY_AA_O,	0 },
			{ RX_AA_R, RY_AA_R,	0 },
			{ RX_AA_O, RY_AA_O,	0 },
		},
		{	///< BB
			{ PX_BB_R, PY_BB_R,	WET_PARTICLE_Z_BB },
			{ PX_BB_O, PY_BB_O,	WET_PARTICLE_Z_BB },
			{ LX_BB_R, LY_BB_R,	WET_PARTICLE_Z_BB },
			{ LX_BB_O, LY_BB_O,	WET_PARTICLE_Z_BB },
			{ LX_BB_R, LY_BB_R,	WET_PARTICLE_Z_BB },/// 2
			{ L2X_BB_O, L2Y_BB_O,	WET_PARTICLE_Z_BB },
			{ L3X_BB_O, L3Y_BB_O,	0 },
			{ L3X_BB_O, L3Y_BB_O,	0 },
			{ L095X_BB_O, L095Y_BB_O,	0 },
			{ L095X_BB_O, L095Y_BB_O,	0 },
			{ L161X_BB_O, L161Y_BB_O,	0 },
			{ L161X_BB_O, L161Y_BB_O,	0 },
			{ L308X_BB_O, L308Y_BB_O,	0 },
			{ L308X_BB_O, L308Y_BB_O,	0 },
			{ L304X_BB_O, L304Y_BB_O,	0 },
			{ L304X_BB_O, L304Y_BB_O,	0 },
			{ L320X_BB_O, L320Y_BB_O,	0 },
			{ L320X_BB_O, L320Y_BB_O,	0 },
			{ L406X_BB_O, L406Y_BB_O,	0 },
			{ L406X_BB_O, L406Y_BB_O,	0 },
			{ LAX_BB_R, LAY_BB_R,	0 },
			{ LAX_BB_O, LAY_BB_O,	0 },
			{ RX_BB_R, RY_BB_R,	0 },
			{ RX_BB_O, RY_BB_O,	0 },
		},
		{
			///< A
			{ PX_A_R, PY_A_R,	WET_PARTICLE_Z_A }, 
			{ PX_A_O, PY_A_O,	WET_PARTICLE_Z_A }, 
			{ LX_A_R, LY_A_R,	WET_PARTICLE_Z_A }, 
			{ LX_A_O, LY_A_O,	WET_PARTICLE_Z_A }, 
			{ LX_A_R, LY_A_R,	WET_PARTICLE_Z_A }, /// 2
			{ L2X_A_O, L2Y_A_O,	WET_PARTICLE_Z_A }, 
			{ L3X_A_O, L3Y_A_O,	0 }, 
			{ L3X_A_O, L3Y_A_O,	0 }, 
			{ L095X_A_O, L095Y_A_O,	0 }, 
			{ L095X_A_O, L095Y_A_O,	0 }, 
			{ L161X_A_O, L161Y_A_O,	0 }, 
			{ L161X_A_O, L161Y_A_O,	0 }, 
			{ L308X_A_O, L308Y_A_O,	0 }, 
			{ L308X_A_O, L308Y_A_O,	0 }, 
			{ L304X_A_O, L304Y_A_O,	0 }, 
			{ L304X_A_O, L304Y_A_O,	0 }, 
			{ L320X_A_O, L320Y_A_O,	0 }, 
			{ L320X_A_O, L320Y_A_O,	0 }, 
			{ L406X_A_O, L406Y_A_O,	0 }, 
			{ L406X_A_O, L406Y_A_O,	0 }, 
			{ LAX_A_R, LAY_A_R,	0 },
			{ LAX_A_O, LAY_A_O,	0 },
			{ RX_A_R, RY_A_R,	0 },
			{ RX_A_O, RY_A_O,	0 },
		},
		{
			///< B
			{ PX_B_R, PY_B_R,	WET_PARTICLE_Z_B }, 
			{ PX_B_O, PY_B_O,	WET_PARTICLE_Z_B }, 
			{ LX_B_R, LY_B_R,	WET_PARTICLE_Z_B }, 
			{ LX_B_O, LY_B_O,	WET_PARTICLE_Z_B }, 
			{ LX_B_R, LY_B_R,	WET_PARTICLE_Z_B }, /// 2
			{ L2X_B_O, L2Y_B_O,	WET_PARTICLE_Z_B }, 
			{ L3X_B_O, L3Y_B_O,	0 }, 
			{ L3X_B_O, L3Y_B_O,	0 }, 
			{ L095X_B_O, L095Y_B_O,	0 }, 
			{ L095X_B_O, L095Y_B_O,	0 }, 
			{ L161X_B_O, L161Y_B_O,	0 }, 
			{ L161X_B_O, L161Y_B_O,	0 }, 
			{ L308X_B_O, L308Y_B_O,	0 }, 
			{ L308X_B_O, L308Y_B_O,	0 }, 
			{ L304X_B_O, L304Y_B_O,	0 }, 
			{ L304X_B_O, L304Y_B_O,	0 }, 
			{ L320X_B_O, L320Y_B_O,	0 }, 
			{ L320X_B_O, L320Y_B_O,	0 }, 
			{ L406X_B_O, L406Y_B_O,	0 }, 
			{ L406X_B_O, L406Y_B_O,	0 }, 
			{ LAX_B_R, LAY_B_R,	2728 },
			{ LAX_B_O, LAY_B_O,	2728 },
			{ RX_B_R, RY_B_R,	0 },
			{ RX_B_O, RY_B_O,	0 },
		},		
		{
			///< C
			{ PX_C_R, PY_C_R,	WET_PARTICLE_Z_C },
			{ PX_C_O, PY_C_O,	WET_PARTICLE_Z_C },
			{ LX_C_R, LY_C_R,	WET_PARTICLE_Z_C },
			{ LX_C_O, LY_C_O,	WET_PARTICLE_Z_C },
			{ LX_C_R, LY_C_R,	WET_PARTICLE_Z_C },
			{ L2X_C_O, L2Y_C_O,	WET_PARTICLE_Z_C },
			{ L3X_C_O, L3Y_C_O,	0 },
			{ L3X_C_O, L3Y_C_O,	0 },
			{ L095X_C_O, L095Y_C_O,	0 },
			{ L095X_C_O, L095Y_C_O,	0 },
			{ L161X_C_O, L161Y_C_O,	0 },
			{ L161X_C_O, L161Y_C_O,	0 },
			{ L308X_C_O, L308Y_C_O,	0 },
			{ L308X_C_O, L308Y_C_O,	0 },
			{ L304X_C_O, L304Y_C_O,	0 },
			{ L304X_C_O, L304Y_C_O,	0 },
			{ L320X_C_O, L320Y_C_O,	0 },
			{ L320X_C_O, L320Y_C_O,	0 },
			{ L406X_C_O, L406Y_C_O,	0 },
			{ L406X_C_O, L406Y_C_O,	0 },
			{ LAX_C_R, LAY_C_R,	0 },
			{ LAX_C_O, LAY_C_O,	0 },
			{ RX_C_R, RY_C_R,	0 },
			{ RX_C_O, RY_C_O,	0 },
		},
		{
			///< D
			{ PX_D_R, PY_D_R,	WET_PARTICLE_Z_D },
			{ PX_D_O, PY_D_O,	WET_PARTICLE_Z_D },
			{ LX_D_R, LY_D_R,	WET_PARTICLE_Z_D },
			{ LX_D_O, LY_D_O,	WET_PARTICLE_Z_D },
			{ LX_D_R, LY_D_R,	WET_PARTICLE_Z_D },
			{ L2X_D_O, L2Y_D_O,	WET_PARTICLE_Z_D },
			{ L3X_D_O, L3Y_D_O,	0 },
			{ L3X_D_O, L3Y_D_O,	0 },
			{ L095X_D_O, L095Y_D_O,	0 },
			{ L095X_D_O, L095Y_D_O,	0 },
			{ L161X_D_O, L161Y_D_O,	0 },
			{ L161X_D_O, L161Y_D_O,	0 },
			{ L308X_D_O, L308Y_D_O,	0 },
			{ L308X_D_O, L308Y_D_O,	0 },
			{ L304X_D_O, L304Y_D_O,	0 },
			{ L304X_D_O, L304Y_D_O,	0 },
			{ L320X_D_O, L320Y_D_O,	0 },
			{ L320X_D_O, L320Y_D_O,	0 },
			{ L406X_D_O, L406Y_D_O,	0 },
			{ L406X_D_O, L406Y_D_O,	0 },
			{ LAX_D_R, LAY_D_R,	0 },
			{ LAX_D_O, LAY_D_O,	0 },
			{ RX_D_R, RY_D_R,	0 },
			{ RX_D_O, RY_D_O,	0 },
		},		
		{
			///< Contest A
			{ PX_CON_A_R, PY_CON_A_R,	WET_PARTICLE_Z_A }, 
			{ PX_CON_A_O, PY_CON_A_O,	WET_PARTICLE_Z_A }, 
			{ LX_CON_A_R, LY_CON_A_R,	WET_PARTICLE_Z_A }, 
			{ LX_CON_A_O, LY_CON_A_O,	WET_PARTICLE_Z_A }, 
			{ LX_CON_A_R, LY_CON_A_R,	WET_PARTICLE_Z_A }, 
			{ L2X_CON_A_O, L2Y_CON_A_O,	WET_PARTICLE_Z_A }, 
			{ L3X_CON_A_O, L3Y_CON_A_O,	0 }, 
			{ L3X_CON_A_O, L3Y_CON_A_O,	0 }, 
			{ L095X_CON_A_O, L095Y_CON_A_O,	0 }, 
			{ L095X_CON_A_O, L095Y_CON_A_O,	0 }, 
			{ L161X_CON_A_O, L161Y_CON_A_O,	0 }, 
			{ L161X_CON_A_O, L161Y_CON_A_O,	0 }, 
			{ L308X_CON_A_O, L308Y_CON_A_O,	0 }, 
			{ L308X_CON_A_O, L308Y_CON_A_O,	0 }, 
			{ L304X_CON_A_O, L304Y_CON_A_O,	0 }, 
			{ L304X_CON_A_O, L304Y_CON_A_O,	0 }, 
			{ L320X_CON_A_O, L320Y_CON_A_O,	0 }, 
			{ L320X_CON_A_O, L320Y_CON_A_O,	0 }, 
			{ L406X_CON_A_O, L406Y_CON_A_O,	0 }, 
			{ L406X_CON_A_O, L406Y_CON_A_O,	0 }, 
			{ LAX_CON_A_R, LAY_CON_A_R,	0 },
			{ LAX_CON_A_O, LAY_CON_A_O,	0 },
			{ RX_CON_A_R, RY_CON_A_R,	0 },
			{ RX_CON_A_O, RY_CON_A_O,	0 },
		},
		{
			///< Contest B
			{ PX_CON_B_R, PY_CON_B_R,	WET_PARTICLE_Z_B }, 
			{ PX_CON_B_O, PY_CON_B_O,	WET_PARTICLE_Z_B }, 
			{ LX_CON_B_R, LY_CON_B_R,	WET_PARTICLE_Z_B }, 
			{ LX_CON_B_O, LY_CON_B_O,	WET_PARTICLE_Z_B }, 
			{ LX_CON_B_R, LY_CON_B_R,	WET_PARTICLE_Z_B }, 
			{ L2X_CON_B_O, L2Y_CON_B_O,	WET_PARTICLE_Z_B },
			{ L3X_CON_B_O, L3Y_CON_B_O,	0 },
			{ L3X_CON_B_O, L3Y_CON_B_O,	0 },
			{ L095X_CON_B_O, L095Y_CON_B_O,	0 },
			{ L095X_CON_B_O, L095Y_CON_B_O,	0 }, 
			{ L161X_CON_B_O, L161Y_CON_B_O,	0 },
			{ L161X_CON_B_O, L161Y_CON_B_O,	0 }, 
			{ L308X_CON_B_O, L308Y_CON_B_O,	0 },
			{ L308X_CON_B_O, L308Y_CON_B_O,	0 }, 
			{ L304X_CON_B_O, L304Y_CON_B_O,	0 },
			{ L304X_CON_B_O, L304Y_CON_B_O,	0 }, 
			{ L320X_CON_B_O, L320Y_CON_B_O,	0 },
			{ L320X_CON_B_O, L320Y_CON_B_O,	0 }, 
			{ L406X_CON_B_O, L406Y_CON_B_O,	0 },
			{ L406X_CON_B_O, L406Y_CON_B_O,	0 }, 
			{ LAX_CON_B_R, LAY_CON_B_R,	2728 },
			{ LAX_CON_B_O, LAY_CON_B_O,	2728 },
			{ RX_CON_B_R, RY_CON_B_R,	0 },
			{ RX_CON_B_O, RY_CON_B_O,	0 },
		},		
	};

	//コンテスト
	if(contest_flag == TRUE){
		switch(client_type){
		case CLIENT_TYPE_AA:
//			VEC_Set(ret, PX_BB_R, PY_BB_R, WET_PARTICLE_Z_BB);
			client_type = CLIENT_TYPE_D + 1;
			break;
			
		case CLIENT_TYPE_BB:
//			VEC_Set(ret, PX_BB_O, PY_BB_O, WET_PARTICLE_Z_BB);
			client_type = CLIENT_TYPE_D + 2;
			break;

		default:
			GF_ASSERT(0 && "コンテストでは、ありえないクライアントタイプです\n");
			break;
		}
	}
	
	tbl_id = camera_mode + (pos_mode * 2);
	
	vec = &vec_tbl[ client_type ][ tbl_id ];
	
	VEC_Set(ret, vec->x, vec->y, vec->z);
}

///< 通常座標取得
void WET_PokeParticlePosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_NORMAL);
}

///< レーザー座標取得
void WET_PokeParticleLaserPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_LASER);
}

void WET_PokeParticleLaser2PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_LASER_2);
}

void WET_PokeParticleLaser3PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_LASER_3);
}

void WET_PokeParticleLaser095PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L095);
}

void WET_PokeParticleLaser161PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L161);
}

void WET_PokeParticleLaser308PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L308);
}

void WET_PokeParticleLaser304PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L304);
}

void WET_PokeParticleLaser320PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L320);
}

void WET_PokeParticleLaser406PosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_L406);
}
///< 注視点座標取得
void WET_PokeParticleLookAtPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_LOOK_AT);
}

///< リング用
void WET_PokeParticleRingPosGet_ClientType(int client_type, VecFx32 *ret, int contest_flag, int camera_mode)
{
	ParticlePosGet_Private(client_type, ret, contest_flag, camera_mode, POS_MODE_RING);
}


//--------------------------------------------------------------
/**
 * @brief   指定クライアントNoのポケモンのパーティクル座標を取得する
 *
 * @param   client_no		クライアントNo
 * @param   ret				座標代入先
 */
//--------------------------------------------------------------
void WET_PokeParticlePosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);
	
	WET_PokeParticlePosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

///< レーザー
void WET_PokeParticleLaserPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaserPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

/// レーザー２
void WET_PokeParticleLaser2PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser2PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleLaser3PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser3PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleLaser095PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser095PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}


void WET_PokeParticleLaser161PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser161PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleLaser308PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser308PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}


void WET_PokeParticleLaser304PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser304PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleLaser320PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser320PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleLaser406PosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLaser406PosGet_ClientType(client_type, ret, contest_flag, camera_type);
}
///< 注視点
void WET_PokeParticleLookAtPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleLookAtPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

///< rinng
void WET_PokeParticleRingPosGet(WE_SYS_PTR wsp, int client_no, VecFx32 *ret)
{
	int client_type, contest_flag;
	int camera_type;
	PTC_PTR ptc;
	
	ptc			 = WeSysPTCPointerGet(wsp);
	camera_type  = Particle_CameraTypeGet(ptc);	
	client_type  = WET_ClientTypeGet(wsp, client_no);
	contest_flag = WES_ContestFlag_Get(wsp);

	WET_PokeParticleRingPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

void WET_PokeParticleDispOutTopGet(VecFx32 *ret)
{
	ret->x = 0;
	ret->y = PT_LCD_T + (60 * PT_LCD_DOT);
	ret->z = 0;
}

//--------------------------------------------------------------
/**
 * @brief	クライアントタイプから座標を取得
 *
 * @param	client_type	
 * @param	ret	
 * @param   contest_flag	TRUE:コンテスト。　FALSE:戦闘
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WET_PokeParticlePosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type)
{
	WET_PokeParticlePosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

///< レーザー
void WET_PokeParticleLaserPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type)
{
	WET_PokeParticleLaserPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

///< 注視点
void WET_PokeParticleLookAtPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type)
{
	WET_PokeParticleLookAtPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

///< リング
void WET_PokeParticleRingPosGet_CT(int client_type, VecFx32 *ret, int contest_flag, int camera_type)
{
	WET_PokeParticleRingPosGet_ClientType(client_type, ret, contest_flag, camera_type);
}

//--------------------------------------------------------------
/**
 * @brief   攻撃側のポケモンにあったカメラベクトルを取得する
 *
 * @param   attack		アタックNo
 * @param   eye			値代入先
 */
//--------------------------------------------------------------
void WET_AttackCameraEyeGet(int attack, VecFx32 *eye)
{
	if(attack == 0){
		Particle_GetDefaultEye(eye);
	}
	else{
		*eye = EnemyEye;
	}
}

//--------------------------------------------------------------
/**
 * @brief   攻撃側のポケモンにあったカメラ上方向ベクトルを取得する
 *
 * @param   attack		アタックNo
 * @param   eye			値代入先
 */
//--------------------------------------------------------------
void WET_AttackCameraUpGet(int attack, VecFx32 *v_up)
{
	if(attack == 0){
		Particle_GetDefaultUp(v_up);
	}
	else{
		*v_up = EnemyUp;
	}
}


//--------------------------------------------------------------
/**
 * @brief	エフェクト共通で使いまわせる基本設定
 *
 * @param	we_sys	
 * @param	obj_ba	
 * @param	bg_ba	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WET_DefaultBlendSet(WE_SYS_PTR we_sys, int obj_ba, int bg_ba)
{
	int oba = obj_ba;
	int bba = bg_ba;
	
	if (obj_ba == WET_DEFAULT_BLEND){
		oba = WET_ALPHA_OAM;
	}
	if (bg_ba == WET_DEFAULT_BLEND){
		bba = WET_ALPHA_BG;
	}
	
	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) | GX_BLEND_PLANEMASK_BG0, oba, bba );	
}

//--------------------------------------------------------------
/**
 * @brief	エフェクト共通で使いまわせる基本設定
 *
 * @param	we_sys	
 * @param	bg_msk		ブレンドの第2対象面
 * @param	obj_ba	
 * @param	bg_ba	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WET_BGSelectBlendSet(WE_SYS_PTR we_sys, int bg_msk, int obj_ba, int bg_ba)
{
	int oba = obj_ba;
	int bba = bg_ba;
	
	if (obj_ba == WET_DEFAULT_BLEND){
		oba = WET_ALPHA_OAM;
	}
	if (bg_ba == WET_DEFAULT_BLEND){
		bba = WET_ALPHA_BG;
	}
	
	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE,
			bg_msk, oba, bba );	
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	エフェクトBGのデフォルトアルファブレンド
 *
 *	@param	we_sys		技エフェクトシステムワーク
 *	@param	effe_ba		エフェクトBGのアルファ値
 *	@param	bg_ba		バックグラウンドのアルファ値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WET_DefaultBGEffectBlendSet( WE_SYS_PTR we_sys, int effe_ba, int bg_ba )
{
	int oba = effe_ba;
	int bba = bg_ba;
	
	if (effe_ba == WET_DEFAULT_BLEND){
		oba = WET_ALPHA_OAM;
	}
	if (bg_ba == WET_DEFAULT_BLEND){
		bba = WET_ALPHA_BG;
	}
	
	G2_SetBlendAlpha( ( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT) ),
			( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) | GX_WND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ, oba, bba );	
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ウィンドウマスクデフォルト設定
 *
 *	@param	we_sys		技エフェクトシステム
 *	@param	wnd_no		ウィンドウナンバー
 *	@param	effect		ブレンドの有無
 *
 *	@return	none
 *
 * wnd_no
 *	WET_WNDMSK_0,
 *	WET_WNDMSK_1,
 *
 */
//-----------------------------------------------------------------------------
void WET_DefaultWndMskSet( WE_SYS_PTR we_sys, int wnd_no, BOOL effect )
{
	if( wnd_no == WET_WNDMSK_0 ){
		// 背景
		G2_SetWnd0InsidePlane( 
				( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) | (1 << BT_BGL_BGNoGet(we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT)) | GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ,
				effect );
	}else{
		// 背景
		G2_SetWnd1InsidePlane( 
				( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) | (1 << BT_BGL_BGNoGet(we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT)) | GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ,
				effect );
	}

	// 背景以外を外にする
	G2_SetWndOutsidePlane( 
			(1 << BT_BGL_BGNoGet(we_sys, WES_BF_WINDOW )) | (1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT)) | GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ,
			TRUE
			);
}

//--------------------------------------------------------------
/**
 * @brief	SSPから座標取得
 *
 * @param	ssp	
 * @param	p	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_SSP_PointGet(SOFT_SPRITE* ssp, WT_POINT* p)
{
	if (ssp == NULL){
		p->x = 0;
		p->y = 0;
		return;
	}
	else if (SoftSpriteExistCheck(ssp) == FALSE){
		p->x = 0;
		p->y = 0;
		return;
	}
	p->x = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
	p->y = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
}


//--------------------------------------------------------------
/**
 * @brief	CAPから座標取得
 *
 * @param	cap
 * @param	p	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_CAP_PointGet(CATS_ACT_PTR cap, WT_POINT* p)
{
	CATS_ObjectPosGetCap(cap, &(p->x), &(p->y));
}



//--------------------------------------------------------------
/**
 * @brief	ツール汎用構造体の初期化
 *
 * @param	we_sys	
 * @param	wts	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_ToolSysInit(WE_SYS_PTR we_sys, TWE_TOOL_SYS* wts)
{
	wts->seq	= 0;
	wts->cnt	= 0;
	wts->step	= 0;
	wts->wait	= 0;

	wts->wsp		= we_sys;
	wts->csp		= WeSysCspGet(we_sys);
	wts->poke_crp	= WeSysPokeCrpGet(we_sys);
	wts->oam_crp	= WeSysCrpGet(we_sys);
	wts->bgl		= WeSysBGLPointerGet(we_sys);
	wts->pfd		= WeSysPFDGet(we_sys);
}

//--------------------------------------------------------------
/**
 * @brief	ソフトウェアスプライトのポインタ取得
 *
 * @param	flag	
 * @param	ssp	
 * @param	num	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_SSPointerGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num)
{
	*num = 0;
	
	if (IsBitCheck(flag, WE_TOOL_STAGE) == TRUE){
		
		int at = WeSysATNoGet(wsp);
		int no;
		int type;
		
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, at);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = at;
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
		
		no = WET_AllySideClientNoGet(wsp, at);
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = no;
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
		
		type = WeSysClientTypeGet(wsp, at);
		type = WazaTool_DiagonalClientTypeGet_ClientType(type);
		no   = WET_CheckClientNo(wsp, type);
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = no;
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
		
		no = WET_AllySideClientNoGet(wsp, no);
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = no;
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
		return;
	}
	
	if (IsBitCheck(flag, WE_TOOL_OTHER) == TRUE){
		
		int at = WeSysATNoGet(wsp);
		int no;
		int type;
		
		no = WET_AllySideClientNoGet(wsp, at);
		if (no != at){
			pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
			if (pp[*num].ssp != NULL){
				pp[*num].client_no = no;
				WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
				(*num)++;
			}
		}
		
		type = WeSysClientTypeGet(wsp, at);
		type = WazaTool_DiagonalClientTypeGet_ClientType(type);
		no   = WET_CheckClientNo(wsp, type);
		if (no != at){
			pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
			if (pp[*num].ssp != NULL){
				pp[*num].client_no = no;
				WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
				(*num)++;
			}
		}
		
		no = WET_AllySideClientNoGet(wsp, no);
		if (no != at){
			pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, no);
			if (pp[*num].ssp != NULL){
				pp[*num].client_no = no;
				WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
				(*num)++;
			}		
		}
		return;
	}
	
	if (IsBitCheck(flag, WE_TOOL_M1) == TRUE){
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, WeSysATNoGet(wsp));
	//	GF_ASSERT(pp[*num].ssp != NULL);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = WeSysATNoGet(wsp);
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
	}
	
	if (IsWeSysBattleMode2vs2(wsp) == TRUE){
		if (IsBitCheck(flag, WE_TOOL_M2) == TRUE){
			pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, WET_AllySideClientNoGet(wsp, WeSysATNoGet(wsp)));
		//	GF_ASSERT(pp[*num].ssp != NULL);
			if (pp[*num].ssp != NULL){
				pp[*num].client_no = WET_AllySideClientNoGet(wsp, WeSysATNoGet(wsp));
				WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
				(*num)++;
			}
		}
	}
	
	if (IsBitCheck(flag, WE_TOOL_E1) == TRUE){
		pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, WeSysDFNoGet(wsp));
	//	GF_ASSERT(pp[*num].ssp != NULL);
		if (pp[*num].ssp != NULL){
			pp[*num].client_no = WeSysDFNoGet(wsp);
			WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
			(*num)++;
		}
	}
	
	if (IsWeSysBattleMode2vs2(wsp) == TRUE){
		if (IsBitCheck(flag, WE_TOOL_E2) == TRUE){
			pp[*num].ssp = WeSysSoftSpritePointerGet(wsp, WET_AllySideClientNoGet(wsp, WeSysDFNoGet(wsp)));
		//	GF_ASSERT(pp[*num].ssp != NULL);
			if (pp[*num].ssp != NULL){
				pp[*num].client_no = WET_AllySideClientNoGet(wsp, WeSysDFNoGet(wsp));
				WT_SSP_PointGet(pp[*num].ssp, &pp[*num].p);
				(*num)++;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	CAPのポインタ取得
 *
 * @param	wsp	
 * @param	flag	
 * @param	pp	
 * @param	num	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_CAPointerGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num)
{
	*num = 0;
	
	if (IsBitCheck(flag, WE_TOOL_C0) == TRUE){
		pp[*num].cap = WeSysPokeCapGet(wsp, *num);
		WT_CAP_PointGet(pp[*num].cap, &pp[*num].p);
		(*num)++;
	}
	if (IsBitCheck(flag, WE_TOOL_C1) == TRUE){
		pp[*num].cap = WeSysPokeCapGet(wsp, *num);
		WT_CAP_PointGet(pp[*num].cap, &pp[*num].p);
		(*num)++;
	}
	
	if (IsBitCheck(flag, WE_TOOL_C2) == TRUE){
		pp[*num].cap = WeSysPokeCapGet(wsp, *num);
		WT_CAP_PointGet(pp[*num].cap, &pp[*num].p);
		(*num)++;
	}
	
	if (IsBitCheck(flag, WE_TOOL_C3) == TRUE){
		pp[*num].cap = WeSysPokeCapGet(wsp, *num);
		WT_CAP_PointGet(pp[*num].cap, &pp[*num].p);
		(*num)++;
	}
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンの基本座標取得
 *
 * @param	wsp	
 * @param	flag	
 * @param	pp	
 * @param	num	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WT_PokeBasePointGet(WE_SYS_PTR wsp, int flag, TWE_POKE_SYS* pp, int* num)
{
	int fight_type;
	int contest_ofs = 0;
	*num = 0;
	
	if (IsWeSysBattleMode2vs2(wsp) == FALSE){
		fight_type  = 0;
		if (WES_ContestFlag_Get(wsp) == TRUE){
			contest_ofs = 2;
		}
	}
	else {
		fight_type = 1;
	}
	
	if (IsBitCheck(flag, WE_TOOL_M1) == TRUE){
		WazaEffPosGet_Type(fight_type, 0 + contest_ofs,
						   &pp[*num].base_p.x, &pp[*num].base_p.y);
		(*num)++;
	}
	
	if (IsBitCheck(flag, WE_TOOL_M2) == TRUE){
		WazaEffPosGet_Type(fight_type, 2,
						   &pp[*num].base_p.x, &pp[*num].base_p.y);
		(*num)++;
	}
	
	if (IsBitCheck(flag, WE_TOOL_E1) == TRUE){
		WazaEffPosGet_Type(fight_type, 1 + contest_ofs,
						   &pp[*num].base_p.x, &pp[*num].base_p.y);
		(*num)++;
	}
	
	if (IsBitCheck(flag, WE_TOOL_E2) == TRUE){
		WazaEffPosGet_Type(fight_type, 3,
						   &pp[*num].base_p.x, &pp[*num].base_p.y);
		(*num)++;
	}
}


//--------------------------------------------------------------
/**
 * @brief	we_sysからヒープ領域を取得するエフェクト用のメモリ確保
 *
 * @param	wsp				we_sys
 * @param	size			サイズ
 *
 * @retval	static inline void*	
 *
 */
//--------------------------------------------------------------
void* WazaEffect_AllocMemory(WE_SYS_PTR wsp, int size)
{
	int		heap_area;
	void*	wk;
	
	wk = NULL;
	
	GF_ASSERT(wsp != NULL);
	
	heap_area = WeSysHeapAreaGet(wsp);
	
	wk = sys_AllocMemory(heap_area, size);
	
	GF_ASSERT(wk != NULL);
	
	memset(wk, 0, size);
	
	return wk;
}

//--------------------------------------------------------------
/**
 * @brief	メモリ解放用
 *
 * @param	wk	
 *
 * @retval	static inline void	
 *
 */
//--------------------------------------------------------------
void WazaEffect_FreeMemory(void* wk)
{
	GF_ASSERT(wk != NULL);
	
	sys_FreeMemoryEz(wk);
}