//==============================================================================
/**
 * @file	wazatool.c
 * @brief	技エフェクト関連の汎用ツールのヘッダ
 * @author	matsuda
 * @date	2005.09.02(金)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "spl.h"
#include "battle_particle.h"
#include "we_err.h"
#include "we_tool.h"
#include "wazatool.h"

#include "contest/contest.h"



//==============================================================================
//	構造体定義
//==============================================================================
typedef struct{
	s16 x;
	s16 y;
}POINT;



//--------------------------------------------------------------
/**
 * @brief   技エフェクト動作タスクで使うメモリの確保
 *
 * @param   heap_area		使用するヒープエリア
 * @param   size			確保するサイズ
 *
 * @retval  確保したメモリの先頭アドレス
 *
 * 確保したメモリは0クリアされています
 */
//--------------------------------------------------------------
void * WazaTool_AllocClearMemory(int heap_area, u32 size)
{
	void *work;
	
	work = sys_AllocMemory(heap_area, size);
	MI_CpuClear8(work, size);
	return work;
}

///技エフェクト用 始点・終点座標データ
static const POINT WazaEffPos[][ 6 ] = 
{
	{	//FightType	1vs1
		//ClientNo
		{ APPEAR_X_TYPE_AA, APPEAR_Y_TYPE_AA },				//味方1
		{ APPEAR_X_TYPE_BB, APPEAR_Y_TYPE_BB },				//敵1
		{ CONTEST_ATTACK_POKE_X,  CONTEST_ATTACK_POKE_Y },	//コンテスト攻撃用
		{ CONTEST_DEFENCE_POKE_X, CONTEST_DEFENCE_POKE_Y },	//コンテスト防御用
		{ 0,0 },
		{ 0,0 },
	},
	{	//FightType 2vs2
		{ APPEAR_X_TYPE_AA, APPEAR_Y_TYPE_AA },		//味方1
		{ APPEAR_X_TYPE_BB, APPEAR_Y_TYPE_BB },		//敵1
		{ APPEAR_X_TYPE_A, APPEAR_Y_TYPE_A },		//味方1
		{ APPEAR_X_TYPE_B, APPEAR_Y_TYPE_B },		//敵1
		{ APPEAR_X_TYPE_C, APPEAR_Y_TYPE_C },		//味方2
		{ APPEAR_X_TYPE_D, APPEAR_Y_TYPE_D },		//敵2
	},
};

void WazaEffPosGet_Type(int fight_type, int type, s16* x, s16* y)
{
	if (x != NULL){
		*x = WazaEffPos[ fight_type ][ type ].x;
	}
	if (y != NULL){
		*y = WazaEffPos[ fight_type ][ type ].y;
	}
}

void WazaEffPosGet_ClientType(WE_SYS_PTR wsp, int client_no, s16*x, s16* y)
{
	if (WES_ContestFlag_Get(wsp) == TRUE){
		WazaEffPosGet_Type(0, client_no + 2, x, y);	
	}
	else {
		if (IsWeSysBattleMode2vs2(wsp) == TRUE){
			WazaEffPosGet_Type(1, client_no - 2, x, y);	
		}
		else {
			WazaEffPosGet_Type(0, client_no, x, y);	
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   技エフェクト始点、終点座標取得
 *
 * @param   we_sys		
 * @param   client_no	クライアントNo
 * @param   get_pos		PM_??? or EFF_???
 *
 * @retval  
 *
 * POKE_* = 個々のポケモンの大きさによって座標が変わり、絵の大きさが違っても常に
 *          その絵にあったポケモンの中心の座標を取れる。
 *
 * EFF_* =  ポケモンのオフセットは関係なしで常に共通の中心座標を取得する
 */
//--------------------------------------------------------------
s16 GetWazaEffPos(WE_SYS_PTR we_sys, int client_no, int get_pos)
{
	int client_type, fight_type;
	
	client_type = WET_ClientTypeGet(we_sys, client_no);
	
	if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
		fight_type = 1;
	}
	else {
		fight_type = 0;
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		client_type += 2;
	}
	
	switch(get_pos){
	case PM_X:
	case EFF_X:
		return WazaEffPos[fight_type][client_type].x;
	case PM_Y:
	case EFF_Y:
		return WazaEffPos[fight_type][client_type].y;
	}
	
	GF_ASSERT(0);
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   指定クライアントNoのポケモンアクターのデフォルトソフトプライオリティを取得する
 * @param   client_no		クライアントNO
 * @retval  ソフトプライオリティ
 * 
 * DPではポケモンはソフトウェアスプライトなので意味はないけど旧エフェクトソースを持ってくる為の
 * 互換用として用意した
 */
//--------------------------------------------------------------
u32 GetPokeSoftPri(u8 client_no)
{
	return WAZAEFF_ACT_SOFTPRI;
}



//-------------------------------------
//	
//	CATS_ACT_PTRのパレットNO取得関数
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	capの参照しているパレットナンバーを取得する
 *
 *	@param	cap	アクターデータ
 *
 *	@return	パレットNO	0～15
 *
 *
 */
//-----------------------------------------------------------------------------
u8 WazaTool_CapPlttNoGet( CATS_ACT_PTR cap )
{
	return GetPlttProxyOffset( CLACT_PaletteProxyGet(cap->act), NNS_G2D_VRAM_TYPE_2DMAIN );
}


//-------------------------------------
//	
//	Hブランク関数をパックした関数
//
//	後々拡張するとこもあるかも知れないため作成
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク関数設定をパックした関数
 *
 *	@param	func		設定するHブランク動作関数
 *	@param	work		ワーク
 *
 *	@retval	WAZATOOL_HBLANK_FALSE	失敗
 *	@retval	WAZATOOL_HBLANK_TRUE	成功
 */
//-----------------------------------------------------------------------------
int WazaTool_HBlankSet( INTR_FUNC func, void * work )
{
	GF_ASSERT( work );
	
	if( sys_HBlankIntrSet( func, work ) ){
		return WAZATOOL_HBLANK_TRUE;
	}

	return WAZATOOL_HBLANK_FALSE;
}

//-------------------------------------
//	●エフェクト方向チェンジ
//	　横と縦のベクトル方向を返します。
//	　戻り値を掛けることで、その方向のベクトルになります。
//	　
//	　回転は始点と終点を渡してもらい、
//	　回転方向が逆になる値を再設定します。
//	　場合によっては始点の値が変わるときもあります。
//	　例）変更前　始0 終15 変更後　始360 終わり345
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	クライアントナンバーからX方向ベクトルを取得する
 *
 *	@param	we_sys			技エフェクトシステムワーク
 *	@param	client_no		クライアントナンバー
 *
 *	@retval	1				その方向でOK
 *	@retval	-1				逆方向のベクトル
 *
 * ●戦闘時の自分サイドを基準とした方向です。
 *
 * ●回転方向もこの関数で変更できます。
 *
 */
//-----------------------------------------------------------------------------
int WazaTool_VecChangeX( WE_SYS_PTR we_sys, int client_no )
{
	int side;
	int out_put = 1;

	// 再度取得
	side = WET_SideCheck( we_sys, client_no );
		
	// コンテストかチェック
	if( WES_ContestFlag_Get( we_sys ) ){
		// コンテストのとき
		//	自分サイドはX方向逆ベクトル
		//	相手サイドはX方向そのまま
		if( side == SIDE_MINE ){
			out_put = -1;
		}
	}else{
		// 戦闘のとき
		//	自分サイドはX方向そのまま
		//	相手サイドはX方向逆ベクトル
		if( side == SIDE_ENEMY ){
			out_put = -1;
		}
	}

	return out_put;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	クライアントナンバーからY方向ベクトルを取得する
 *
 *	@param	we_sys			技エフェクトシステムワーク
 *	@param	client_no		クライアントナンバー
 *
 *	@retval	1				その方向でOK
 *	@retval	-1				逆方向のベクトル
 *
 * ●戦闘時の自分サイドを基準とした方向です。
 *
 */
//-----------------------------------------------------------------------------
int WazaTool_VecChangeY( WE_SYS_PTR we_sys, int client_no )
{
	int side;
	int out_put = 1;

	// 再度取得
	side = WET_SideCheck( we_sys, client_no );
		
	//	自分サイドはY方向そのまま
	//	相手サイドはY方向逆ベクトル
	if( side == SIDE_ENEMY ){
		out_put = -1;
	}
	

	return out_put;
}

//-----------------------------------------------------------------------------
/**
 *		等差　計算
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	等差を求める
 *
 *	@param	a		始点
 *	@param	an		終点
 *	@param	n		シンク数
 *
 *	@return	等差
 *
 *
 */
//-----------------------------------------------------------------------------
fx32 WazaTool_GetDiff( fx32 a, fx32 an, u32 n )
{
	fx32 ans;
	
	ans = FX_Div( (an - a), n << FX32_SHIFT );

	return ans;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	等差diffでa～anになるために必要なシンク数
 *	
 *	@param	a		始点
 *	@param	an		終点
 *	@param	diff	等差
 *
 *	@return	必要シンク数	(絶対値）
 *
 * 小数点以下切り上げ
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetDiffSync( fx32 a, fx32 an, fx32 diff )
{
	fx32 ans;
	fx32 smal;		// 小数部

	ans = FX_Div( (an - a), diff );

	// 小数点以下切り上げ
	smal = FX_Modf( ans, &ans );
	if( smal ){
		ans += FX32_ONE;
	}

	ans = MATH_ABS( ans );
	
	return ans >> FX32_SHIFT;
}



//----------------------------------------------------------------------------
/**
 *	@brief	座標反映関数
 *
 *	@param	p_wtc	データ
 *	@param	cap		アクター
 *	@param	c_x		中心座標
 *	@param	c_y		中心座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetCapMatrix( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap, s16 c_x, s16 c_y )
{
	CATS_ObjectPosSetCap( cap, c_x + p_wtc->x, c_y + p_wtc->y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡大値反映関数
 *
 *	@param	p_wtc	データ
 *	@param	cap		アクター
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetCapScale( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	f32 s_x, s_y;
	WazaTool_CalcScaleRateToClactScale( p_wtc, &s_x, &s_y );
	CATS_ObjectScaleSetCap( cap, s_x, s_y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標反映関数
 *
 *	@param	p_wtc	データ
 *	@param	ssp		ソフトウェアスプライト
 *	@param	c_x		中心ｘ座標
 *	@param	c_y		中心ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetSspMatrix( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp, s16 c_x, s16 c_y )
{
	SoftSpriteParaSet( ssp, SS_PARA_POS_X, c_x + p_wtc->x );
	SoftSpriteParaSet( ssp, SS_PARA_POS_Y, c_y + p_wtc->y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡大値反映関数
 *
 *	@param	p_wtc	データ
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_SetSspScale( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	SoftSpriteParaSet( ssp, SS_PARA_AFF_X, p_wtc->x );
	SoftSpriteParaSet( ssp, SS_PARA_AFF_Y, p_wtc->y );
}

//-----------------------------------------------------------------------------
/**
 *		回転
 *
 *		角度は
 *			0度  ->0
 *			360度->65535(0xffff)
 *		です。
 *		FX_GET_ROTA_NUM(x)	( (x*0xffff) / 360 )
 *		このマクロを使用すれば、取得できます。
 *		例）
 *			FX_GET_ROTA_NUM(360) == 0xffff
 *
 *	2005/11/18 tomoya takahashi
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転計算初期化
 *
 *	@param	p_wtc	動作計算ワーク
 *	@param	r_sx	開始ｘ角度	(0～65535) 65535で360度です。
 *	@param	r_ex	終了ｘ角度	(0～65535) 65535で360度です。
 *	@param	r_sy	開始ｙ角度	(0～65535) 65535で360度です。
 *	@param	r_ey	終了ｙ角度	(0～65535) 65535で360度です。
 *	@param	wx		ｘ方向幅
 *	@param	wy		ｙ方向幅
 *	@param	sync	シンク数
 *
 *	@return	none
 *
 * X方向	sinカーブ
 * Y方向	cosカーブ
 *
 *			1回転分しか設定できません。
 *			この関数で設定した後work[0]を回転したい回数倍
 *			してください
 */
//-----------------------------------------------------------------------------
void WazaTool_InitRotaFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, int sync )
{
	p_wtc->work[0] = sync;
	p_wtc->work[1] = r_sx;
	p_wtc->work[2] = wx;
	p_wtc->work[3] = r_sy;
	p_wtc->work[4] = wy;
	p_wtc->work[5] = (r_ex - r_sx) / sync;
	p_wtc->work[6] = (r_ey - r_sy) / sync;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転計算初期化　回転速度から求める
 *
 *	@param	p_wtc
 *	@param	r_sx
 *	@param	r_ex
 *	@param	r_sy
 *	@param	r_ey
 *	@param	wx
 *	@param	wy
 *	@param	speed_x 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitRotaSpeedFx( WAZATOOL_CALCMOVE* p_wtc, u16 r_sx, u16 r_ex, u16 r_sy, u16 r_ey, fx32 wx, fx32 wy, u16 speed_x )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// 移動方向を設定
	if( r_sx > r_ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	//回転移動データを設定
	p_wtc->work[0] = WazaTool_GetDiffSync( r_sx*FX32_ONE, r_ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = r_sx;
	p_wtc->work[2] = wx;
	p_wtc->work[3] = r_sy;
	p_wtc->work[4] = wy;
	p_wtc->work[5] = sp_x;
	p_wtc->work[6] = (r_ey - r_sy) / p_wtc->work[0];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転計算
 *
 *	@param	p_wtc	動作計算ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	work[0]		計算回数
 *	work[1]		ｘ方向回転角度		(0～65535) 65535で360度です。
 *	work[2]		ｘ方向振れ幅		fx32型
 *	work[3]		ｙ方向回転角度		(0～65535) 65535で360度です。
 *	work[4]		ｙ方向振れ幅		fx32型
 *	work[5]		ｘ方向回転変化量	(0～65535) 65535で360度です。
 *	work[6]		ｙ方向回転変化量	(0～65535) 65535で360度です。
 *
 * X方向	sinカーブ
 * Y方向	cosカーブ
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcRotaFx( WAZATOOL_CALCMOVE* p_wtc )
{
	fx32 x, y;
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//角度変化
		p_wtc->work[1] += p_wtc->work[5];
		p_wtc->work[3] += p_wtc->work[6];

		// 0～65535をループ
		p_wtc->work[1] &= 0xffff;
		p_wtc->work[3] &= 0xffff;

		p_wtc->work[0]--;

		//円を描く
		p_wtc->x = FX_Mul( FX_SinIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;
		p_wtc->y = FX_Mul( FX_CosIdx(p_wtc->work[3]), p_wtc->work[4] ) >> FX32_SHIFT;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映関数
 *
 *	@param	p_wtc	計算データ
 *	@param	c_x		中心ｘ座標
 *	@param	c_y		中心ｙ座標
 *	@param	cap		アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectRotaFxCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcRotaFx( p_wtc ) ){
		WazaTool_SetCapMatrix( p_wtc, cap, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映関数
 *
 *	@param	p_wtc	計算データ
 *	@param	c_x		中心ｘ座標
 *	@param	c_y		中心ｙ座標
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectRotaFxSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcRotaFx( p_wtc ) ){
		WazaTool_SetSspMatrix( p_wtc, ssp, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		平行移動
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 * ●移動スピードで初期化
 *	@brief	平行移動計算初期化関数
 *
 *	@param	p_wtc	データ設定先
 *	@param	sx		移動開始ｘ座標
 *	@param	ex		移動終了ｘ座標
 *	@param	sy		移動開始ｙ座標
 *	@param	ey		移動終了ｙ座標
 *	@param	speed_x	ｘ方向スピード	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSpeed( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// 移動方向を設定
	if( sx > ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	// 直線移動データを設定
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = WazaTool_GetDiffSync( sx*FX32_ONE, ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = sp_x;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, p_wtc->work[0] ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 * ●移動スピードで初期化
 *	@brief	平行移動計算初期化関数	（固定少数使用）
 *
 *	@param	p_wtc	データ設定先
 *	@param	sx		移動開始ｘ座標
 *	@param	ex		移動終了ｘ座標
 *	@param	sy		移動開始ｙ座標
 *	@param	ey		移動終了ｙ座標
 *	@param	speed_x	ｘ方向スピード	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSpeedFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 speed_x  )
{
	s16 sp_x;

	GF_ASSERT(p_wtc);

	// 移動方向を設定
	if( sx > ex ){
		speed_x = -speed_x;
	}
	sp_x = speed_x;

	// 直線移動データを設定
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = WazaTool_GetDiffSync( sx*FX32_ONE, ex*FX32_ONE, sp_x*FX32_ONE );
	p_wtc->work[1] = sp_x << FX32_SHIFT;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, p_wtc->work[0] );
	p_wtc->work[3] = sx * FX32_ONE;
	p_wtc->work[4] = sy * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 * ●Sync数で初期化
 *	@brief	平行移動計算初期化関数
 *
 *	@param	p_wtc	データ設定先
 *	@param	sx		移動開始ｘ座標
 *	@param	ex		移動終了ｘ座標
 *	@param	sy		移動開始ｙ座標
 *	@param	ey		移動終了ｙ座標
 *	@param	sync	使用するシンク数	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSync( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync  )
{
	GF_ASSERT(p_wtc);

	// 直線移動データを設定
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( sx*FX32_ONE, ex*FX32_ONE, sync ) >> FX32_SHIFT;
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, sync ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 * ●Sync数で初期化
 *	@brief	平行移動計算初期化関数	（固定少数使用）
 *
 *	@param	p_wtc	データ設定先
 *	@param	sx		移動開始ｘ座標
 *	@param	ex		移動終了ｘ座標
 *	@param	sy		移動開始ｙ座標
 *	@param	ey		移動終了ｙ座標
 *	@param	sync	使用するsync数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_InitStraightSyncFx( WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync )
{

	GF_ASSERT(p_wtc);

	// 直線移動データを設定
	p_wtc->x = sx;
	p_wtc->y = sy;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( sx*FX32_ONE, ex*FX32_ONE, sync );
	p_wtc->work[2] = WazaTool_GetDiff( sy*FX32_ONE, ey*FX32_ONE, sync );
	p_wtc->work[3] = sx*FX32_ONE;
	p_wtc->work[4] = sy*FX32_ONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	平行移動計算
 *
 *	@param	p_wtc	動作計算ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	work[0]		計算回数
 *	work[1]		x変化量
 *	work[2]		y変化量
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcStraight( WAZATOOL_CALCMOVE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		
		p_wtc->x += p_wtc->work[1];
		p_wtc->y += p_wtc->work[2];
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	平行移動計算	（固定少数使用）
 *
 *	@param	p_wtc	動作計算ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	work[0]		計算回数
 *	work[1]		ｘ変化量		fx32型
 *	work[2]		ｙ変化量		fx32型
 *	work[3]		変化した値		fx32型	初期値は０
 *	work[4]		変化した値		fx32型	初期値は０
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcStraightFx( WAZATOOL_CALCMOVE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		
		p_wtc->work[3] += p_wtc->work[1];
		p_wtc->work[4] += p_wtc->work[2];
		p_wtc->x	= p_wtc->work[3] >> FX32_SHIFT;
		p_wtc->y	= p_wtc->work[4] >> FX32_SHIFT;
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	計算データ
 *	@param	cap		アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectStraightFxCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcStraightFx( p_wtc ) ){

		WazaTool_SetCapMatrix( p_wtc, cap, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	計算データ
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectStraightFxSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcStraightFx( p_wtc ) ){

		WazaTool_SetSspMatrix( p_wtc, ssp, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		山なり移動
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	山なり移動初期化　Y方向		(固定少数使用)
 *
 *	@param	p_wtc_st		平行移動パラメータ設定先
 *	@param	p_wtc_rt		回転パラメータ設定先
 *	@param	sx				始点ｘ座標
 *	@param	ex				終点ｘ座標
 *	@param	sy				始点ｙ座標
 *	@param	ey				終点ｙ座標
 *	@param	sync			計算シンク数
 *	@param	width			やまなりの幅	Y方向
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitCurveYFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width )
{
	// 平行移動設定
	WazaTool_InitStraightSyncFx( p_wtc_st, sx, ex, sy, ey, sync );
	
	// 回転設定
	p_wtc_rt->x = 0;
	p_wtc_rt->y	= 0;
	WazaTool_InitRotaFx( p_wtc_rt, 
			0, 0,
			FX_GET_ROTA_NUM(90), FX_GET_ROTA_NUM(270),
			0, width, sync );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	山なり移動初期化　ｘ方向		(固定少数使用)
 *
 *	@param	p_wtc_st		平行移動パラメータ設定先
 *	@param	p_wtc_rt		回転パラメータ設定先
 *	@param	sx				始点ｘ座標
 *	@param	ex				終点ｘ座標
 *	@param	sy				始点ｙ座標
 *	@param	ey				終点ｙ座標
 *	@param	sync			計算シンク数
 *	@param	width			やまなりの幅	X方向
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitCurveXFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, s16 sx, s16 ex, s16 sy, s16 ey, u16 sync, fx32 width )
{
	// 平行移動設定
	WazaTool_InitStraightSyncFx( p_wtc_st, sx, ex, sy, ey, sync );
	
	// 回転設定
	p_wtc_rt->x = 0;
	p_wtc_rt->y	= 0;
	WazaTool_InitRotaFx( p_wtc_rt, 
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(180),
			0, 0,
			width, 0, sync );
}

//----------------------------------------------------------------------------
/**
 * ●平行移動と回転のあわせ技
 *	@brief	山なり移動計算	（固定少数使用）
 *
 *	@param	p_wtc_st	平行移動計算ワーク	(メイン)
 *	@param	p_wtc_rt	回転計算ワーク		(サブ)
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	＊p_wtc_stのx,y座標が計算結果になります。
 *	＊初期化時にp_wtc_rtのx,yは0で初期化してください。
 *
 * p_wtc_st	平行移動用
 *	x			全体のｘ座標計算結果
 *	y			全体のｙ座標計算結果
 *	work[0]		計算回数
 *	work[1]		ｘ変化量		fx32型
 *	work[2]		ｙ変化量		fx32型
 *	work[3]		変化した値		fx32型	初期値は０
 *	work[4]		変化した値		fx32型	初期値は０
 *
 * p_wtc_rt	回転用
 *	x			回転のみの計算結果
 *	y			回転のみの計算結果
 *	work[0]		計算回数
 *	work[1]		ｘ方向回転角度		(0～65535) 65535で360度です。
 *	work[2]		ｘ方向振れ幅		fx32型
 *	work[3]		ｙ方向回転角度		(0～65535) 65535で360度です。
 *	work[4]		ｙ方向振れ幅		fx32型
 *	work[5]		ｘ方向回転変化量	(0～65535) 65535で360度です。
 *	work[6]		ｙ方向回転変化量	(0～65535) 65535で360度です。
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcCurveFx( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt )
{
	BOOL st_end, rt_end;
	
	GF_ASSERT(p_wtc_st);
	GF_ASSERT(p_wtc_rt);

	// 平行移動計算
	st_end = WazaTool_CalcStraightFx( p_wtc_st );
	// 山なり計算
	rt_end = WazaTool_CalcRotaFx( p_wtc_rt );

	// 平行移動と回転の加算
	p_wtc_st->x += p_wtc_rt->x;
	p_wtc_st->y += p_wtc_rt->y;

	// 計算終了チェック
	if( (st_end == rt_end) && (st_end == FALSE) ){
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc_st	直線移動用
 *	@param	p_wtc_rt	回転用
 *	@param	cap			アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectCurveFxCap( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcCurveFx( p_wtc_st, p_wtc_rt ) ){

		WazaTool_SetCapMatrix( p_wtc_st, cap, 0, 0 );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc_st	直線移動データ
 *	@param	p_wtc_rt	回転データ
 *	@param	ssp			ソフトウェアスプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectCurveFxSsp( WAZATOOL_CALCMOVE* p_wtc_st, WAZATOOL_CALCMOVE* p_wtc_rt, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcCurveFx( p_wtc_st, p_wtc_rt ) ){
		WazaTool_SetSspMatrix( p_wtc_st, ssp, 0, 0 );
		return TRUE;
	}

	return FALSE;
}


//WAZATOOL_CALCMOVE_ONE構造体用関数郡
//----------------------------------------------------------------------------
/**
 *●実数
 *	@brief	１つの値を等差で動かす初期化関数　（シンク数指定）
 *
 *	@param	p_wtc	データ設定先
 *	@param	a		開始値
 *	@param	an		終了値
 *	@param	sync	シンク数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSync( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, u32 sync )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( a*FX32_ONE, an*FX32_ONE, sync ) >> FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *●実数
 *	@brief	１つの値を等差で動かす初期化関数　（スピード指定）
 *
 *	@param	p_wtc	データ設定先
 *	@param	a		開始値
 *	@param	an		終了値
 *	@param	speed	スピード
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSpeed( WAZATOOL_CALCMOVE_ONE* p_wtc, s32 a, s32 an, s16 speed )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = WazaTool_GetDiffSync( a*FX32_ONE, an*FX32_ONE, speed * FX32_ONE );
	p_wtc->work[1] = speed;
}

//----------------------------------------------------------------------------
/**
 *●固定少数
 *	@brief	１つの値を等差で動かす初期化関数　（シンク数指定）
 *
 *	@param	p_wtc	データ設定先
 *	@param	a		開始値
 *	@param	an		終了値
 *	@param	sync	シンク数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, u32 sync )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = sync;
	p_wtc->work[1] = WazaTool_GetDiff( a*FX32_ONE, an*FX32_ONE, sync );
	p_wtc->work[2] = a * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *●固定少数
 *	@brief	１つの値を等差で動かす初期化関数　（スピード指定）
 *
 *	@param	p_wtc	データ設定先
 *	@param	a		開始値
 *	@param	an		終了値
 *	@param	speed	スピード
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitMoveOneSpeedFx( WAZATOOL_CALCMOVE_ONE* p_wtc, s16 a, s16 an, fx32 speed )
{
	GF_ASSERT( p_wtc );
	
	p_wtc->num = a;
	p_wtc->work[0] = WazaTool_GetDiffSync( a*FX32_ONE, an*FX32_ONE, speed * FX32_ONE );
	p_wtc->work[1] = speed * FX32_ONE;
	p_wtc->work[2] = a * FX32_ONE;
}

//----------------------------------------------------------------------------
/**
 *●実数
 *	@brief	1つの値の等差計算
 *
 *	@param	p_wtc	ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	work[0]		計算回数
 *	work[1]		変化量	
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcMoveOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		p_wtc->num	+= p_wtc->work[1];
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *●固定少数
 *	@brief	1つの値の等差計算
 *
 *	@param	p_wtc	ワーク
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *	work[0]		計算回数
 *	work[1]		変化量	
 *	work[2]		今までに変化した量
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcMoveOneFx( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);

	if( p_wtc->work[0] ){
		p_wtc->work[2] += p_wtc->work[1];
		p_wtc->num	= p_wtc->work[2] >> FX32_SHIFT;
		p_wtc->work[0] --;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サイン波計算初期化関数
 *
 *	@param	p_wtc		計算パラメータ格納先
 *	@param	s_r			開始回転角
 *	@param	e_r			終了回転角
 *	@param	w			最大ふり幅
 *	@param	sync		シンク数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_InitSinCosOneSyncFx( WAZATOOL_CALCMOVE_ONE* p_wtc, u16 s_r, u16 e_r, fx32 w, u32 sync )
{
	p_wtc->work[0] = sync;
	p_wtc->work[1] = s_r;
	p_wtc->work[2] = w;
	p_wtc->work[3] = (e_r - s_r) / sync;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	sin波計算
 *
 *	@param	p_wtc	計算データ
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcSinOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//角度変化
		p_wtc->work[1] += p_wtc->work[3];

		// 0～65535をループ
		p_wtc->work[1] &= 0xffff;

		p_wtc->work[0]--;

		//円を描く
		p_wtc->num = FX_Mul( FX_SinIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;

		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	cos波計算
 *
 *	@param	p_wtc	計算データ
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcCosOne( WAZATOOL_CALCMOVE_ONE* p_wtc )
{
	GF_ASSERT(p_wtc);
	
	if( p_wtc->work[0] ){
		//角度変化
		p_wtc->work[1] += p_wtc->work[3];

		// 0～65535をループ
		p_wtc->work[1] &= 0xffff;

		p_wtc->work[0]--;

		//円を描く
		p_wtc->num = FX_Mul( FX_CosIdx(p_wtc->work[1]), p_wtc->work[2] ) >> FX32_SHIFT;

		return TRUE;
	}

	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	拡縮初期化
 *
 * @param	p_wtc	
 * @param	ss				開始スケール
 * @param	ds				通常スケール
 * @param	es				終了スケール
 * @param	sync			フレーム数
 *
 * @retval	none	
 *
 *		0x100(256) = 100%
 *
 */
//--------------------------------------------------------------
#define SCALE_RATE_PER(p1, p2)	( ((p1) * 0x100) / p2 )
void WazaTool_InitScaleRate(WAZATOOL_CALCMOVE* p_wtc, s16 ss, s16 ds, s16 es, u32 sync)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;			///< かかる時間
	
	///< 拡大率
	wk->work[1] = WazaTool_GetDiff(SCALE_RATE_PER(ss, ds) * FX32_ONE,
								   SCALE_RATE_PER(es, ds) * FX32_ONE, sync);

	///< 現在の拡大率x,y
	wk->x = SCALE_RATE_PER(ss, ds);
	wk->y = SCALE_RATE_PER(ss, ds);
	wk->work[3] = wk->x * FX32_ONE;
	wk->work[4] = wk->y * FX32_ONE;
}


//--------------------------------------------------------------
/**
 * @brief	拡縮実行
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcScaleRate(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;

	if (wk->work[0]){
		wk->work[0]--;
		wk->work[3] += wk->work[1];
		wk->work[4] += wk->work[1];
		wk->x = (wk->work[3] >> FX32_SHIFT);
		wk->y = (wk->work[4] >> FX32_SHIFT);
		
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	拡縮XY反映
 *
 * @param	p_wtc		汎用
 * @param	sx			開始スケールX
 * @param	ex			終了スケールX
 * @param	sy			開始スケールY
 * @param	ey			終了スケールY
 * @param	ds			基本値
 * @param	sync		シンク数
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_InitScaleRateEx(WAZATOOL_CALCMOVE* p_wtc, s16 sx, s16 ex, s16 sy, s16 ey, s16 ds, u32 sync)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;			///< かかる時間
	
	///< 拡大率
	wk->work[1] = WazaTool_GetDiff(SCALE_RATE_PER(sx, ds) * FX32_ONE,
								   SCALE_RATE_PER(ex, ds) * FX32_ONE, sync);
	
	wk->work[2] = WazaTool_GetDiff(SCALE_RATE_PER(sy, ds) * FX32_ONE,
								   SCALE_RATE_PER(ey, ds) * FX32_ONE, sync);

	///< 現在の拡大率x,y
	wk->x = SCALE_RATE_PER(sx, ds);
	wk->y = SCALE_RATE_PER(sy, ds);
	wk->work[3] = wk->x * FX32_ONE;
	wk->work[4] = wk->y * FX32_ONE;
}


//--------------------------------------------------------------
/**
 * @brief	拡縮、XY反映
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcScaleRateEx(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;

	if (wk->work[0]){
		wk->work[0]--;
		wk->work[3] += wk->work[1];
		wk->work[4] += wk->work[2];
		wk->x = (wk->work[3] >> FX32_SHIFT);
		wk->y = (wk->work[4] >> FX32_SHIFT);
		return TRUE;
	}
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	拡縮パラメーターを変換
 *
 * @param	p_wtc	
 * @param	x	
 * @param	y	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_CalcScaleRateToClactScale(WAZATOOL_CALCMOVE* p_wtc, f32* x, f32* y)
{
	*x = (1.0f * p_wtc->x) / 0x0100;
	*y = (1.0f * p_wtc->y) / 0x0100;
}


//--------------------------------------------------------------
/**
 * @brief	基本座標、高さ、スケールから補正座標を求める
 *
 * @param	def_y		基本座標
 * @param	poke_h		高さ
 * @param	sy			スケール値
 *
 * @retval	s16	
 *
 */
//--------------------------------------------------------------
s16 WazaTool_CalcScaleRateToYPos(s16 def_y, int poke_h, u32 sy)
{
	fx32 pos = (80 - (poke_h * 2)) * FX32_ONE;
	fx32 tmp;
	s16  ofs;
	
	tmp = (pos - ((pos * sy) / 0x100)) / 2;
	ofs = tmp >> FX32_SHIFT;

	return ofs;
}


//--------------------------------------------------------------
/**
 * @brief	基本座標、高さ、スケールから補正座標を求める
 *
 * @param	def_y		基本座標
 * @param	poke_h		高さ
 * @param	sy			スケール値
 *
 * @retval	s16
 *
 */
//--------------------------------------------------------------
s16	WazaTool_CalcScaleRateToYPosFX(s16 def_y, int poke_h, fx32 sy)
{
	fx32 pos = (80 - (poke_h * 2)) * FX32_ONE;
	fx32 def = 0x0100 * FX32_ONE;
	fx32 tmp;
	fx32 mul;
	fx32 div;
	s16  ofs;
	
	mul = FX_Mul(pos, sy);
	div = FX_Div(mul, def);
	tmp = (pos - div);
#if 1
	{
		fx32 integer;
		fx32 decimal;
		decimal = FX_Modf(tmp, &integer);
		if (decimal){
			decimal += FX32_HALF;
		}
		tmp = integer + decimal;
	}
#endif
	
	ofs = (tmp >> FX32_SHIFT) / 2;
	
	return ofs;
}

//--------------------------------------------------------------
/**
 * @brief	ソフトウェアスプライトに補正地を反映する
 *
 * @param	ssp	
 * @param	def_y	
 * @param	poke_height	
 * @param	scale	
 * @param	mode			モード	EOFS_MODE 参照
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_PokeOffsetSet(SOFT_SPRITE* ssp, s16 def_y, s16 poke_height, fx32 scale, int mode)
{
	s16 ofs_y;
	s16 def;
	
	def   = def_y;
	ofs_y = WazaTool_CalcScaleRateToYPosFX(def_y, poke_height, scale);
	
	if (mode == WAZAEFF_OFS_MODE_TOP){
		ofs_y *= -1;
		def = def_y - poke_height;
	}
	
	SoftSpriteParaSet(ssp, SS_PARA_POS_Y, def + ofs_y);
}

void WazaTool_PokeOffsetSetOAM(CATS_ACT_PTR cap, s16 def_y, s16 poke_height, fx32 scale, int mode)
{
	s16 ofs_y;
	s16 def;
	s16 dx;
	s16 dy;
	
	def   = def_y;
	ofs_y = WazaTool_CalcScaleRateToYPosFX(def_y, poke_height, scale);
	
	if (mode == WAZAEFF_OFS_MODE_TOP){
		ofs_y *= -1;
		def = def_y - poke_height;
	}

	CATS_ObjectPosGetCap(cap, &dx, &dy);
	CATS_ObjectPosSetCap(cap, dx,  def + ofs_y);
}


//----------------------------------------------------------------------------
/**
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	データ
 *	@param	cap		アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcScaleRate( p_wtc ) ){
		WazaTool_SetCapScale( p_wtc, cap );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	データ
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcScaleRate( p_wtc ) ){
		WazaTool_SetSspScale( p_wtc, ssp );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	データ
 *	@param	cap		アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateExCap( WAZATOOL_CALCMOVE* p_wtc, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcScaleRateEx( p_wtc ) ){
		WazaTool_SetCapScale( p_wtc, cap );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	データ
 *	@param	ssp		ソフトウェアスプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectScaleRateExSsp( WAZATOOL_CALCMOVE* p_wtc, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcScaleRateEx( p_wtc ) ){
		WazaTool_SetSspScale( p_wtc, ssp );
		return TRUE;
	}

	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	現在状況と、1個前の状況から振り位置を決める関数
 *
 * @param	now			今
 * @param	befor		1個前
 * @param	p			ふり幅
 *
 * @retval	static inline void	
 *
 */
//--------------------------------------------------------------
static inline void WazaTool_ShakeTool(s16* now, s32* befor, s32 p)
{
	s32 temp = *befor;
	*befor = *now;
	
	if (temp == 0){
		*now = 0;
	}
	else {
		*now = temp *= -1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	簡易シェイク
 *
 * @param	p_wtc	
 * @param	x			xのふり幅
 * @param	y			yのふり幅
 * @param	sync		揺らすタイミング
 * @param	num			揺らす回数
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_InitShake(WAZATOOL_CALCMOVE* p_wtc, s16 x, s16 y, u32 sync, u32 num)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	wk->work[0] = sync;
	wk->work[1] = sync;
	wk->work[2] = num;
	
	wk->work[3] = 0;			///< ←・→・ で1セット
	
	wk->work[4] = x;
	wk->work[5] = y;
	
	wk->work[6] = x * -1;		///< 1個前の状態
	wk->work[7] = y * -1;		///< 1個前の状態

	wk->x = 0;
	wk->y = 0;	
}


//--------------------------------------------------------------
/**
 * @brief	揺らし
 *
 * @param	p_wtc	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_CalcShake(WAZATOOL_CALCMOVE* p_wtc)
{
	WAZATOOL_CALCMOVE* wk; 
	
	GF_ASSERT(p_wtc);
	
	wk = p_wtc;
	
	if (wk->work[2]){
		
		wk->work[0]++;
		if (wk->work[0] >= wk->work[1]){
			wk->work[0] = 0;
			WazaTool_ShakeTool(&wk->x, &wk->work[6], wk->work[4]);
			WazaTool_ShakeTool(&wk->y, &wk->work[7], wk->work[5]);
			if ((++wk->work[3]) >= 4){
				wk->work[3] = 0;
				wk->work[2]--;
			}
		}
		
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	計算データ
 *	@param	c_x		中心座標
 *	@param	c_y		中心座標
 *	@param	cap		アクター
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectShakeCap( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, CATS_ACT_PTR cap )
{
	if( WazaTool_CalcShake( p_wtc ) ){
		WazaTool_SetCapMatrix( p_wtc, cap, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	計算＆反映
 *
 *	@param	p_wtc	計算データ
 *	@param	c_x		中心ｘ座標
 *	@param	c_y		中心ｙ座標
 *	@param	ssp		スプライト
 *
 *	@retval	TRUE	途中
 *	@retval	FALSE	完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcAndReflectShakeSsp( WAZATOOL_CALCMOVE* p_wtc, s16 c_x, s16 c_y, SOFT_SPRITE* ssp )
{
	if( WazaTool_CalcShake( p_wtc ) ){
		WazaTool_SetSspMatrix( p_wtc, ssp, c_x, c_y );
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	残像データをp_wtzに設定します。
 *
 *	@param	p_wtz		残像データ格納先
 *	@param	p_wtc		動作データ（各WazaTool_Init～関数で初期化したもの）
 *	@param	p_func		動作関数
 *	@param	x			移動の基準となるｘ座標
 *	@param	y			移動の基準となるｙ座標
 *	@param	wait		残像を表示していくタイミング
 *	@param	zanzou_num	残像の数		１以上
 *	@param	type		座標に反映させるか拡大縮小に反映させるか
 *	@param	cap_00		残像のOAM０
 *	@param	cap_01		残像のOAM１		残像の数が１以下の時　NULL
 *	@param	cap_02		残像のOAM２		残像の数が２以下の時　NULL
 *	@param	cap_03		残像のOAM３		残像の数が３以下の時　NULL
 *
 *	@return	none
 *
 * type		残像反映タイプ
	WAZATOOL_ZANZOU_TYPE_MATRIX,	// タイプ	座標
	WAZATOOL_ZANZOU_TYPE_SCALE,		// タイプ	拡大縮小
 * 
 */
//-----------------------------------------------------------------------------
void WazaTool_InitZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func, s16 x, s16 y, u16 wait, u8 zanzou_num, u8 type, CATS_ACT_PTR cap_00, CATS_ACT_PTR cap_01, CATS_ACT_PTR cap_02, CATS_ACT_PTR cap_03 )
{
	int i;		// ループ用
	
	// データ設定
	p_wtz->x = x;
	p_wtz->y = y;
	p_wtz->move_func	= p_func;
	p_wtz->wait			= wait;
	p_wtz->count		= 0;
	p_wtz->zanzou_num	= zanzou_num;
	p_wtz->zanzou_move	= 0;
	p_wtz->type			= type;
	for( i=0; i<zanzou_num; i++ ){
		p_wtz->move_param[ i ] = *p_wtc;
	}
	p_wtz->cap[ WAZATOOL_ZANZOU_0 ] = cap_00;
	p_wtz->cap[ WAZATOOL_ZANZOU_1 ] = cap_01;
	p_wtz->cap[ WAZATOOL_ZANZOU_2 ] = cap_02;
	p_wtz->cap[ WAZATOOL_ZANZOU_3 ] = cap_03;

	// 残像の表示OFF
	for( i=0; i<p_wtz->zanzou_num; i++ ){
		CATS_ObjectEnableCap( p_wtz->cap[i], FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	残像の動作パラメータを変更する
 *
 *	@param	p_wtz		残像データ
 *	@param	p_wtc		設定動作データ
 *	@param	p_func		設定動作関数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_ChangeMoveZanzou( WAZATOOL_ZANZOU* p_wtz, WAZATOOL_CALCMOVE* p_wtc, WAZATOOL_CALCFUNC p_func )
{
	int i;

	p_wtz->move_func	= p_func;
	for( i=0; i<p_wtz->zanzou_num; i++ ){
		p_wtz->move_param[ i ] = *p_wtc;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	残像を動作させる
 *
 *	@param	p_wtz		残像動作データ
 *
 *	@retval	TRUE		途中
 *	@retval	FALSE		完了
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_CalcZanzou( WAZATOOL_ZANZOU* p_wtz )
{
	int i;
	BOOL ret[WAZATOOL_ZANZOU_MAX];
	f32 s_x, s_y;

	// 変数初期化
	for( i=0; i<WAZATOOL_ZANZOU_MAX; i++ ){
		ret[i] = TRUE;
	}
	
	// 登録処理
	if( p_wtz->wait <= p_wtz->count ){

		// １体動作開始
		CATS_ObjectEnableCap( p_wtz->cap[ p_wtz->zanzou_move ], TRUE );
		p_wtz->zanzou_move++;
		p_wtz->count = 0;
	}

	// 登録タイミングカウント処理
	if( p_wtz->zanzou_move < p_wtz->zanzou_num ){
		p_wtz->count++;
	}
	
	// 動作処理
	for( i=0; i<p_wtz->zanzou_move; i++ ){
		
		// 計算	
		ret[ i ] = p_wtz->move_func( &p_wtz->move_param[ i ] );

		// 反映
		if( ret[ i ] ){
			// 動作中は値の更新
			if( p_wtz->type == WAZATOOL_ZANZOU_TYPE_MATRIX ){
				CATS_ObjectPosSetCap( p_wtz->cap[ i ], p_wtz->x + p_wtz->move_param[ i ].x, p_wtz->y + p_wtz->move_param[ i ].y );
			}else{

				// CalcScaleRateを使用しているとする
				WazaTool_CalcScaleRateToClactScale( &p_wtz->move_param[ i ], &s_x, &s_y );
				CATS_ObjectScaleSetCap( p_wtz->cap[ i ],
						s_x, s_y);
			}
		}else{
			// 動作完了したら表示OFF
			CATS_ObjectEnableCap( p_wtz->cap[ i ], FALSE );
		}
	}

	// 終了チェック
	for( i=0; i<p_wtz->zanzou_num; i++ ){

		// まだ計算途中のオブジェクトがあるかチェック
		if( ret[i] == TRUE ){	
			return TRUE;
		}
	}
		
	// ret[]の中身が全部FALSEなら全計算完了
	return FALSE;
}


//-------------------------------------
//	
//	汎用的に使える動作ワークを
//	作成する関数郡
//
//	回転移動などは共通の動作をすることが多いため作成
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	回転移動のデフォルト設定
 *
 *	@param	p_wtc		動作計算データ格納先
 *	@param	rota_num	回転数
 *	@param	sync		1回転シンク数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WazaTool_MakeDefRota( WAZATOOL_CALCMOVE* p_wtc, int rota_num, int rota_one_sync )
{
	int vec_x;
	
	WazaTool_InitRotaFx( p_wtc,
			0, FX_GET_ROTA_NUM(360),
			0, FX_GET_ROTA_NUM(360),
			WAZATOOL_DEF_ROTA_W_X,
			WAZATOOL_DEF_ROTA_W_Y,
			rota_one_sync);

	p_wtc->work[0] *= rota_num;
}


//-------------------------------------
//	
//	alphaフェードタスク
//	
//=====================================
//フェードタスク
static void WazaTool_TskAlphaFade( TCB_PTR tcb, void* work )
{
	BOOL check;
	WAZATOOL_ALPHA_FADE* wk = work;

	// 計算部
	check = WazaTool_CalcStraightFx( &wk->wtc );

	// 終了チェック
	if( check == FALSE ){

		wk->end_flag = TRUE;
		TCB_Delete( tcb );
	}else{

		// マイナスは０に
		if( wk->wtc.x < 0 ){
			wk->wtc.x = 0;
		}
		if( wk->wtc.y < 0 ){
			wk->wtc.y = 0;
		}
		
		// 反映部
		G2_ChangeBlendAlpha( wk->wtc.x, wk->wtc.y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アルファフェードタスク開始
 *
 *	@param	p_alfd	データ格納先
 *	@param	sev1	対称面１の開始係数
 *	@param	eev1	対称面１の終了係数
 *	@param	sev2	対称面２の開始係数
 *	@param	eev2	対称面２の終了係数
 *	@param	sync	使用シンク数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartAlphaFade( WAZATOOL_ALPHA_FADE* p_alfd, s16 sev1, s16 eev1, s16 sev2, s16 eev2, int sync )
{
	// 変化パラメータ設定
	WazaTool_InitStraightSyncFx( &p_alfd->wtc, sev1, eev1, sev2, eev2, sync );

	// 終了フラグ初期化
	p_alfd->end_flag = FALSE;

	// タスク生成
	TCB_Add( WazaTool_TskAlphaFade, p_alfd, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アルファフェードタスク終了チェック
 *
 *	@param	p_alfd	アルファフェードタスクワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WazaTool_EndCheckAlphaFade( const WAZATOOL_ALPHA_FADE* p_alfd )
{
	return p_alfd->end_flag;
}

//-----------------------------------------------------------------------------
/**
 *		ラスター用システム
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	HDMAコントロール
//	
//=====================================
typedef void (*pWazaTool_LSVBCFunc)( void* work );
// 1/30 をカバーするシステム
typedef struct _WAZATOOL_LASTER_VBLANK_CONT{
	TCB_PTR		vdma_tcb;
	TCB_PTR		vbuff_tcb;
	BOOL vblank_lst_flg;// VBlankで行う処理を行うかのフラグ
	BOOL dma_set_flg;	//メインループ中のVブランかをチェックするフラグ
	
	pWazaTool_LSVBCFunc	vblank1;	// ３０フレームの通常のVブランク用処理
	pWazaTool_LSVBCFunc	vblank2;	// 途中のVブランク用処理
	void * work;
} WAZATOOL_LSVBC;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	通常Vブランク
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_VBlank1( TCB_PTR tcb, void* work )
{
	WAZATOOL_LSVBC* wk = work;
	
	if( wk->vblank_lst_flg ){
		// 次のVブランク期間中にDMA設定を行う
		// ２回目はここで行うので１回目だけメインループ
		// ないでくるVブランク期間中にやってもらう
		wk->dma_set_flg = TRUE;

		// 通常のVブランク処理
		wk->vblank1( wk->work );

	}else{
		LASTER_DmaStop();
	}
}
//----------------------------------------------------------------------------
/**
 *
 *	@brief	途中に入るVブランク期間用関数
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_VBlank2( TCB_PTR tcb, void* work )
{
	WAZATOOL_LSVBC* wk = work;
	
	if( wk->vblank_lst_flg && wk->dma_set_flg ){

		// 途中のVブランク処理
		wk->vblank2( wk->work );
		
		wk->dma_set_flg = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスターVブランクシステム
 *
 *	@param	p_lsvbc		ラスターVブランクシステムワーク
 *	@param	work		引数に渡すワーク
 *	@param	pfunc1		通常のVブランク
 *	@param	pfunc2		途中のVブランク
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Init( WAZATOOL_LSVBC* p_lsvbc, void* work, pWazaTool_LSVBCFunc pfunc1, pWazaTool_LSVBCFunc pfunc2 )
{
	GF_ASSERT( p_lsvbc );

	p_lsvbc->vblank_lst_flg	= TRUE;
	p_lsvbc->dma_set_flg	= FALSE;
	p_lsvbc->work			= work;
	p_lsvbc->vblank1		= pfunc1;
	p_lsvbc->vblank2		= pfunc2;

	// タスク登録
	p_lsvbc->vbuff_tcb = VWaitTCB_Add( WazaTool_LSVBC_VBlank1, p_lsvbc, 0 );
	p_lsvbc->vdma_tcb = VIntrTCB_Add( WazaTool_LSVBC_VBlank2, p_lsvbc, 0 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター用Vブランク管理システム破棄
 *
 *	@param	p_lsvbc		破棄するラスターVブランク管理システム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Delete( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );

	// VBlank関数破棄
	if( p_lsvbc->vbuff_tcb != NULL ){
		TCB_Delete( p_lsvbc->vbuff_tcb );
	}
	if( p_lsvbc->vdma_tcb != NULL ){
		TCB_Delete( p_lsvbc->vdma_tcb );
	}
	LASTER_DmaStop();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vブランクシステムの１じ停止
 *
 *	@param	p_lsvbc		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Stop( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );
	p_lsvbc->vblank_lst_flg = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vブランクシステムの再開
 *
 *	@param	p_lsvbc		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_LSVBC_Start( WAZATOOL_LSVBC* p_lsvbc )
{
	GF_ASSERT( p_lsvbc );
	p_lsvbc->vblank_lst_flg = TRUE;
}


//-------------------------------------
//	
//	バッファ内を何も操作しない
//	
//=====================================
typedef struct _WAZATOOL_DEFLASTER{
	WAZATOOL_LSVBC vblank;

	// ラスターデータ
	LASTER_SYS_PTR lst;	// ラスターシステム
	u32	buff1[ WAZATOOL_DEFLASTER_BUFF_SIZE ];	// ダブルバッファ
	u32	buff2[ WAZATOOL_DEFLASTER_BUFF_SIZE ];	// ダブルバッファ
	u32	addr;	// DMA転送先
} WAZATOOL_DEFLASTER;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	DMA転送設定
 *
 *	@param	p_lst	デフォルトラスターシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterDmaTransSet( WAZATOOL_DEFLASTER* wk )
{
	const void* buff;

	// 参照用バッファ取得
	buff = LASTER_GetReadBuff( wk->lst );

	LASTER_DmaStop();
	
	// HBlankDmaTransに設定
	LASTER_DmaSet( buff, (void*)wk->addr, 4, LASTER_DMA_TYPE32 );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター用Vブランク管理システムに渡す通常Vブランク関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterNormVblank( void* work )
{
	WAZATOOL_DEFLASTER* wk = work;

	// バッファスイッチ
	LASTER_VBlank( wk->lst );

	// HDMA登録
	WazaTool_DefLasterDmaTransSet( wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief ラスター用Vブランク管理システムに渡す途中に呼ばれるVブランク用処理
 *
 *	@param		work	ワーク
 *	
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_DefLasterCenterVblank( void* work )
{
	WAZATOOL_DEFLASTER* wk = work;

	// HDMA登録
	WazaTool_DefLasterDmaTransSet( wk );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	デフォルトラスター処理初期化
 *
 *	@param	addr		転送先レジスタアドレス
 *	@param	init_num	バッファの初期値
 *	@param	heap		ヒープID
 *
 *	@return	作成したラスター処理データ
 *
 *
 */
//-----------------------------------------------------------------------------
WAZATOOL_DEFLASTER_PTR WazaTool_InitDefLaster( u32 addr, u32 init_num, int heap )
{
	WAZATOOL_DEFLASTER_PTR p_lst;
	
	p_lst = sys_AllocMemory( heap, sizeof(WAZATOOL_DEFLASTER) );
	memset( p_lst, 0, sizeof(WAZATOOL_DEFLASTER) );
	GF_ASSERT( p_lst );


	p_lst->lst			= LASTER_Init( heap, p_lst->buff1, p_lst->buff2 );
	GF_ASSERT( p_lst->lst );
	p_lst->addr			= addr;

	// バッファの初期化
	MI_CpuFill32( p_lst->buff1, init_num, sizeof(u32) * WAZATOOL_DEFLASTER_BUFF_SIZE );
	MI_CpuFill32( p_lst->buff2, init_num, sizeof(u32) * WAZATOOL_DEFLASTER_BUFF_SIZE );

	// Vブランク管理システムを初期化
	WazaTool_LSVBC_Init( &p_lst->vblank, p_lst, WazaTool_DefLasterNormVblank, WazaTool_DefLasterCenterVblank );

	return p_lst;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター処理の終了
 *
 *	@param	p_lst	デフォルトラスターシステムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_DeleteDefLaster( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	// Vblank管理システム破棄
	WazaTool_LSVBC_Delete( &p_lst->vblank );
	
	// ラスターシステム破棄
	if( p_lst->lst != NULL ){
		LASTER_Delete( p_lst->lst );
	}

	sys_FreeMemoryEz( p_lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	書き込み用バッファの取得
 *
 *	@param	cp_lst	デフォルトラスターシステム
 *
 *	@return	書き込み用バッファ
 *
 *
 */
//-----------------------------------------------------------------------------
void* WazaTool_GetDefLasterWriteBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );

	return LASTER_GetWriteBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	参照用バッファを取得
 *
 *	@param	cp_lst	デフォルトラスターシステム
 *
 *	@return	参照用バッファ
 *
 *
 */
//-----------------------------------------------------------------------------
const void* WazaTool_GetDefLasterReadBuff( CONST_WAZATOOL_DEFLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );

	return LASTER_GetReadBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター処理の停止
 *
 *	@param	p_lst	デフォルトラスターワーク
 *
 *	@return	none
 *
 * Vブランク関数が機能しなくなるので、
 * 画面にラスターが反映されなくなります。
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StopDefLaster( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Stop( &p_lst->vblank );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター処理スタート
 *
 *	@param	p_lst	デフォルトラスターシステム
 *
 *	@return	none
 *
 * 画面にラスターが反映されるようになります。
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartDefLaster( WAZATOOL_DEFLASTER* p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Start( &p_lst->vblank );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	データ転送先アドレスを再設定
 *
 *	@param	p_lst	デフォルトラスターシステム
 *	@param	addr	転送先アドレス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_SetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst, u32 addr )
{
	GF_ASSERT( p_lst );

	p_lst->addr = addr;
}


//--------------------------------------------------------------
/**
 * @brief	データ転送先アドレスを取得
 *
 * @param	p_lst	デフォルトラスターシステム
 *
 * @retval	u32		転送先アドレス
 *
 */
//--------------------------------------------------------------
u32 WazaTool_GetDefLasterTransAddr( WAZATOOL_DEFLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	return p_lst->addr;
}

//-------------------------------------
//	
//	1/30フレーム対応
//	
// ラスタースクロールラップ関数
// SINカーブスクロールさせます
//	
//	
//=====================================
typedef struct _WAZATOOL_SCRLASTER{
	WAZATOOL_LSVBC vblank;

	// ラスターデータ
	LASTER_SCROLL_PTR lst;	// ラスタースクロールシステム
} WAZATOOL_SCRLASTER;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター用Vブランク管理システムに渡す通常Vブランク関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_ScrLasterNormVblank( void* work )
{
	WAZATOOL_SCRLASTER* wk = work;
	
	LASTER_ScrollVBuffSwitch( wk->lst );

	LASTER_ScrollVDma( wk->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief ラスター用Vブランク管理システムに渡す途中に呼ばれるVブランク用処理
 *
 *	@param		work	ワーク
 *	
 *	@return		none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WazaTool_ScrLasterCenterVblank( void* work )
{
	WAZATOOL_SCRLASTER* wk = work;
	
	LASTER_ScrollVDma( wk->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロールシステム生成
 *
 *	@param	start		スクロール開始ｙ座標
 *	@param	end			スクロール終了ｙ座標
 *	@param	add_r		sinカーブテーブル作成時の角度を足していく値(0～65535)
 *	@param	r_w			sinカーブの半径
 *	@param	scr_sp		ラスタースクロールスピード	整数*100した値	マイナス有効
 *	@param	bg_no		ラスターをかけるBGの番号
 *	@param	tsk_pri		タスク優先順位
 *	@param	init_num	バッファを初期化する値
 *	@param	heap		使用するヒープ
 *
 *	@return	作成したラスターデータ
 * 
 * start <= スクロール範囲 <= end
 *
 * bg_no = 0～3	メイン画面固定
 *
 */
//-----------------------------------------------------------------------------
WAZATOOL_SCRLASTER_PTR WazaTool_InitScrLaster( u8 start, u8 end, u16 add_r, fx32 r_w, s16 scr_sp, u32 bg_no, u32 tsk_pri, u32 init_num, int heap )
{
	WAZATOOL_SCRLASTER_PTR p_lst;
	u32 addr;
	void* buff;
	const void* cbuff;
		
	p_lst = sys_AllocMemory( heap, sizeof(WAZATOOL_SCRLASTER) );
	GF_ASSERT( p_lst );
	memset( p_lst, 0, sizeof(WAZATOOL_SCRLASTER) );

	// bg_noからレジスタのアドレスを取得
	addr = WazaTool_GetLasterBGDestAddr( bg_no );

	// ラスタースクロールシステム作成
	p_lst->lst = LASTER_ScrollInit( heap );
	LASTER_ScrollStart( p_lst->lst, start, end, add_r, r_w, scr_sp, addr, init_num, tsk_pri );
	
	// VBlank管理システム作成
	WazaTool_LSVBC_Init( &p_lst->vblank, p_lst, WazaTool_ScrLasterNormVblank, WazaTool_ScrLasterCenterVblank );

	return p_lst;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスタースクロール破棄
 *
 *	@param	p_lst	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_DeleteScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );
	

	// Vブランク管理システム破棄
	WazaTool_LSVBC_Delete( &p_lst->vblank );

	// ラスタースクロール破棄
	if( p_lst->lst ){
		LASTER_ScrollDelete( p_lst->lst );
	}

	sys_FreeMemoryEz( p_lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	書き込み用バッファ収録
 *
 *	@param	cp_lst	ワーク
 *
 *	@return	バッファ
 *
 *
 */
//-----------------------------------------------------------------------------
void* WazaTool_GetScrLasterWriteBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );
	return LASTER_GetScrollWriteBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	参照用バッファを取得
 *
 *	@param	cp_lst	ワーク
 *
 *	@return	バッファ
 *
 *
 */
//-----------------------------------------------------------------------------
const void* WazaTool_GetScrLasterReadBuff( CONST_WAZATOOL_SCRLASTER_PTR cp_lst )
{
	GF_ASSERT( cp_lst );
	return LASTER_GetScrollReadBuff( cp_lst->lst );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター反映の停止
 *
 *	@param	p_lst	ワーク
 *
 *	@return	none
 *
 * Vブランク関数が機能しなくなるので、
 * 画面にラスターが反映されなくなります。
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StopScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Stop( &p_lst->vblank );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスター反映の開始
 *
 *	@param	p_lst	ワーク
 *
 *	@return	none
 *
 * 画面にラスターが反映されるようになります。
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_StartScrLaster( WAZATOOL_SCRLASTER_PTR p_lst )
{
	GF_ASSERT( p_lst );

	WazaTool_LSVBC_Start( &p_lst->vblank );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	ラスターのバッファに設定する座標データを作成
 *
 *	@param	x	設定ｘ座標
 *	@param	y	設定ｙ座標
 *
 *	@return	バッファに設定する値
 *
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetLasterBuffMatrixData( u16 x, u16 y )
{
	return ( (y << 16) | x );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGナンバーに対応したアドレスを返す
 *
 *	@param	bg_no	BGナンバー
 *
 *	@return	アドレス
 *
 *
 */
//-----------------------------------------------------------------------------
u32 WazaTool_GetLasterBGDestAddr( int bg_no )
{
	u32 addr;
	switch( bg_no ){
	case 0:
		addr	= LASTER_SCROLL_MBG0;
		break;
	case 1:
		addr	= LASTER_SCROLL_MBG1;
		break;
	case 2:
		addr	= LASTER_SCROLL_MBG2;
		break;
	case 3:
		addr	= LASTER_SCROLL_MBG3;
		break;
	}

	return addr;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	エフェクトのBGに優先順位を設定
 *
 *	@param	we_sys		技エフェクトシステム
 *	@param	pri			優先順位 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WazaTool_SetEffectBGPriority( WE_SYS_PTR we_sys, int pri )
{
	int eff_bg;
	
	eff_bg = BT_BGL_BGNoGet( we_sys, WES_BF_EFFECT );
	switch( eff_bg ){
	case 0:
		G2_SetBG0Priority( pri );
		break;

	case 1:
		G2_SetBG1Priority( pri );
		break;

	case 2:
		G2_SetBG2Priority( pri );
		break;

	case 3:
		G2_SetBG3Priority( pri );
		break;
	}
}


// =============================================================================
//
//
//	■ツール？とか？
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	2点の中点を求める
 *
 * @param	x1				点1のx
 * @param	y1				点1のy
 * @param	x2				点2のx
 * @param	y2				点2のy
 * @param	mx				中点x
 * @param	my				中点y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_MiddlePointGet(s16 px1, s16 py1, s16 px2, s16 py2, s16* mx, s16* my)
{
	*mx = (px1 + px2) / 2;
	*my = (py1 + py2) / 2;
}


//--------------------------------------------------------------
/**
 * @brief	2点の中点を求める
 *
 * @param	x1				点1のx
 * @param	y1				点1のy
 * @param	x2				点2のx
 * @param	y2				点2のy
 * @param	mx				中点x
 * @param	my				中点y
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_MiddlePointGetFx(s16 px1, s16 py1, s16 px2, s16 py2, fx32* mx, fx32* my)
{
	*mx = ((px1 + px2) * FX32_ONE) / 2;
	*my = ((py1 + py2) * FX32_ONE) / 2;
}


//--------------------------------------------------------------
/**
 * @brief	2点の距離を求める
 *
 * @param	x1				点1のx
 * @param	y1				点1のy
 * @param	x2				点2のx
 * @param	y2				点2のy
 * @param	range			距離
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_RangeGetFx(s16 x1, s16 y1, s16 x2, s16 y2, fx32* range)
{
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	*range = FX_Sqrt( ((py*py)+(px*px)) * FX32_ONE );
}


//--------------------------------------------------------------
/**
 * @brief	点と点から角度を求める
 *
 * @param	x1				点1のx
 * @param	y1				点1のy
 * @param	x2				点2のx
 * @param	y2				点2のy
 * @param	angle			角度
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WazaTool_PointToPointAngleGet(s16 x1, s16 y1, s16 x2, s16 y2, u16* angle)
{
	s16 px = (x1 - x2);
	s16 py = (y1 - y2) * -1;
	s16 tmp;
	
	*angle = FX_Atan2Idx((py * FX32_ONE), px * FX32_ONE);
	if (*angle > 0 && py < 0){
		*angle = (*angle -FX_GET_ROTA_NUM(180)) * 0xffff;
	}
	else if (*angle < 0 && py > 0){
		*angle += +FX_GET_ROTA_NUM(180);					
	}
}


//--------------------------------------------------------------
/**
 * @brief	パラメータの増減管理
 *
 * @param	p			対象
 * @param	ep			限界
 * @param	cp			増減値
 *
 * @retval	BOOL		TRUE = 限界に到達した
 *
 */
//--------------------------------------------------------------
BOOL WazaTool_ParamCalc(int* p, int ep, s32 cp)
{
	if (cp < 0){
		if (*p + cp > ep){
			*p += cp;
			return FALSE;
		}
		else {
			*p = ep;
			return TRUE;
		}			
	}
	else {
		if (*p + cp < ep){
			*p += cp;
			return FALSE;
		}
		else {
			*p = ep;
			return TRUE;
		}			
	}
	return TRUE;
}



// ----------------------------------------------------------------------------
//
//
//	■ソフトフェード関数郡
//
//
// ----------------------------------------------------------------------------
// -----------------------------------------
//
//	■ ソフトフェード操作構造体
//
// -----------------------------------------
typedef struct _TPAL_SOFT_FADE_SYS {
	
	BOOL	active;				///< TRUE = 動作中
	TCB_PTR	tcb;
	
	FADEREQ req;
	u16		start_pos;
	u16		col_num;
	u16		next_rgb;
	u8		start_evy;
	u8		end_evy;
	u8		evy;
	s8		param;
	s8		wait;
	s8		timer;
	
	PALETTE_FADE_PTR	pfd;	///< pfd
	
} TPAL_SOFT_FADE_SYS;


//--------------------------------------------------------------
/**
 * @brief	動作TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void PSF_Tcb(TCB_PTR tcb, void* work)
{
	PAL_SFS_PTR wk = (PAL_SFS_PTR)work;
	
	if (wk->active == FALSE){ return; }
	
	if ((++wk->timer) >= wk->wait){
		wk->timer = 0;

		SoftFadePfd(wk->pfd,
					wk->req,
					wk->start_pos,
					wk->col_num,
					wk->evy,
					wk->next_rgb);
	
		if (wk->evy == wk->end_evy){
			wk->active = FALSE;
		}
		else {
			s8 temp = wk->evy + wk->param;
			
			if (wk->param > 0){
				if (temp > wk->end_evy){
					wk->evy = wk->end_evy;
				}
				else {
					wk->evy += wk->param;
				}
			}
			else {
				if (temp < wk->end_evy){
					wk->evy = wk->end_evy;
				}
				else {
					wk->evy += wk->param;
				}
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	状態チェック
 *
 * @param	psp			PAL_SFS_PTR
 *
 * @retval	BOOL		TRUE = 実行中
 *
 */
//--------------------------------------------------------------
BOOL IsPaletteSoftFade(PAL_SFS_PTR psp)
{
	GF_ASSERT(psp != NULL);
	
	return psp->active;
}


//--------------------------------------------------------------
/**
 * @brief	終了処理
 *
 * @param	psp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PaletteSoftFadeDelete(PAL_SFS_PTR psp)
{
	GF_ASSERT(psp != NULL);
	
	TCB_Delete(psp->tcb);
	sys_FreeMemoryEz(psp);
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	pfd				pfd
 * @param	heap_area		ヒープ
 * @param	req				データ番号
 * @param	start_pos		開始位置
 * @param	col_num			終了位置
 * @param	wait			ウェイト
 * @param	param			evy 計算値 (start endで符号を付加するので整数で渡してください)
 * @param	start_evy		開始濃度
 * @param	end_evy			終了濃度
 * @param	next_rgb		変更後の色
 * @param	tcb_pri			TCB優先度
 *
 * @retval	PAL_SFS_PTR	
 *
 */
//--------------------------------------------------------------
PAL_SFS_PTR PaletteSoftFade(PALETTE_FADE_PTR pfd, int heap_area, FADEREQ req,
							u16 start_pos, u16 col_num,
							s8 wait, s8 param,
							u8 start_evy, u8 end_evy, 
							u16 next_rgb, int tcb_pri)
{
	PAL_SFS_PTR wk = NULL;
	
	wk = sys_AllocMemory(heap_area, sizeof(TPAL_SOFT_FADE_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->pfd			= pfd;
	
	wk->req			= req;
	wk->start_pos	= start_pos;
	wk->col_num		= col_num;
	wk->next_rgb	= next_rgb;
	wk->start_evy	= start_evy;
	wk->end_evy		= end_evy;
	wk->evy			= start_evy;
	wk->wait		= wait;
	wk->timer		= wait;
	
	if (wk->start_evy < wk->end_evy){
		wk->param	= param;
	}
	else {
		wk->param	= param * -1;
	}
	
	wk->active		= TRUE;
	
	wk->tcb = TCB_Add(PSF_Tcb, wk, tcb_pri);
	
	return wk;
} 

static void PalGrayScale(u16 *pal, u16 pal_size);

static void PalGrayScale(u16 *pal, u16 pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}

void WeTool_PalGrayScale(WE_SYS_PTR wsp)
{
	PALETTE_FADE_PTR pfd;
	u16* pal;
	
	pfd = WeSysPFDGet(wsp);
	
	pal = PaletteWorkTransWorkGet(pfd, FADE_MAIN_BG);
	
	if (WES_ContestFlag_Get(wsp) == TRUE){
		PalGrayScale(pal, 16 * ACTIN_HAIKEI_PAL_NUM);
	}
	else {
		PalGrayScale(pal, 16 * 8);
	}
}

void WeTool_PalNormal(WE_SYS_PTR wsp)
{
	PALETTE_FADE_PTR pfd;
	
	pfd = WeSysPFDGet(wsp);
	
	if (WES_ContestFlag_Get(wsp) == TRUE){
		PaletteWorkCopy(pfd, FADE_MAIN_BG, 0, FADE_MAIN_BG, 0, 16 * ACTIN_HAIKEI_PAL_NUM * 2);
	}
	else {
		PaletteWorkCopy(pfd, FADE_MAIN_BG, 0, FADE_MAIN_BG, 0, 16 * 8 * 2);
	}
}
