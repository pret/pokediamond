//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_data.c
 *	@brief		木の実ミキサー　データ管理部
 *	@author		tomoya takahashi
 *	@data		2006.05.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "include/gflib/calctool.h"
#include "include/itemtool/nuts.h"

#define __NMIX_GAME_DATA_H_GLOBAL
#include "nmix_game_data.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		汎用計算
 */
//-----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/**
 *	@brief	回転角度を計算する		スピードに変更
 *
 *	@param	x			現在ｘ座標
 *	@param	y			現在ｙ座標
 *	@param	last_x		前のｘ座標
 *	@param	last_y		前のｙ座標
 *	@param	center_x	中心ｘ座標
 *	@param	center_y	中心ｙ座標
 *
 *	@return	回転した角度
 */
//-----------------------------------------------------------------------------
s32	NMIX_DATA_CalcRota( int x, int y, int last_x, int last_y, int center_x, int center_y )
{
	int last_rota;
	int now_rota;
	s32 zettai;
	s32 rota_num;

	// 中心からの距離に変換
	x -= center_x;
	y -= center_y;
	last_x -= center_x;
	last_y -= center_y;

#if 0
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( y, x );

	rota_num = now_rota - last_rota;

	// 絶対値を求める
	if( rota_num < 0 ){
		zettai = -rota_num;
	}else{
		zettai = rota_num;
	}

	// 180以上になることは考えにくいその場合は,０を３６０として考える
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360という考えになるからベクトルを変える必要がある
	}

	// 設定
	if( rota_num < 0 ){
		rota_num = -zettai;
	}else{
		rota_num = zettai;
	}
#endif
	rota_num = CalcTool_CircleVectorDistance( last_x, last_y, x, y, 0 );
	rota_num = NMIX_SOOP_SPEED_GET( rota_num );
	return rota_num;
}




//-----------------------------------------------------------------------------
/**
 *
 *		子データ
 *
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	子データ初期化
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoInit( NMIX_DATA_KO* p_data )
{
	memset( p_data, 0, sizeof(NMIX_DATA_KO) );

	// 座標にセンター座標を入れておく
	p_data->x = 128;
	p_data->y = 96;
	p_data->last_x = 128;
	p_data->last_y = 96;
}

//----------------------------------------------------------------------------
/**
 *	@brief	子データ　収集
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoMain( NMIX_DATA_KO* p_data )
{
	s32 rota;

#ifdef DEBUG_NUTMIXER_AUTO
		sys.tp_cont = 1;	//タッチパネル押しっぱなし
		sys.tp_x = 64 + gf_mtRand() % 128;
		sys.tp_y = 64 + gf_mtRand() % 96;
#endif	// DEBUG_NUTMIXER_AUTO
	
	
	// 触っているときのみｘｙ座標を変更
	if( sys.tp_cont ){
		p_data->x = sys.tp_x;
		p_data->y = sys.tp_y;

		// 再度タッチの時は、ラストも同じ座標にする
		if( p_data->last_touch_flg == FALSE ){
			p_data->last_x = p_data->x;
			p_data->last_y = p_data->y;
		}
	}
	// 今の座標と以前の座標から回転角を求める
	p_data->rota = NMIX_DATA_CalcRota( p_data->x, p_data->y, 
			p_data->last_x, p_data->last_y,
			NMIX_SOOP_ROTA_CX, NMIX_SOOP_ROTA_CY );

	p_data->last_x = p_data->x;
	p_data->last_y = p_data->y;

	p_data->last_touch_flg = sys.tp_cont;
}

//----------------------------------------------------------------------------
/**
 *	@brief	子通信データ　作成
 *
 *	@param	p_commdata	通信データ
 *	@param	p_data		ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_KoMake( NUTMIX_ONE* p_commdata, NMIX_DATA_KO* p_data )
{
	p_commdata->x = p_data->x;
	p_commdata->y = p_data->y;
#if 0
	if( p_data->rota < 0 ){
		p_commdata->rota = (-p_data->rota) & 0xffff;
		p_commdata->rota_way = 1;
	}else{
		p_commdata->rota = p_data->rota & 0xffff;
		p_commdata->rota_way = 0;
	}
#else

	if( p_data->rota < 0 ){
		p_commdata->rota = (-p_data->rota);
		p_commdata->rota_way = 1;
	}else{
		p_commdata->rota = p_data->rota;
		p_commdata->rota_way = 0;
	}
#endif
}





//-----------------------------------------------------------------------------
/**
 *				親のみ必要なもの
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	スープタイプに対応した回転反映率
//	NMIX_DATA_SOOP_ROTA_PAR_MAXが100㌫とした値
//=====================================
//#define NMIX_DATA_SOOP_ROTA_PAR_MAX	( 512 )
#define NMIX_DATA_SOOP_ROTA_PAR_MAX	( 204 )
static const u8	NMIX_DATA_SoopRotaPar[ NMIX_SOOPTYPE_SOOP_NUM ] ={
	8,	// スープ
	7,	// クリーム
	7,	// ソボロ
};

//-------------------------------------
//	タイプ別　速度落ち度
//=====================================
static const u16 NMIX_DATA_SoopRotaSub[ NMIX_SOOPTYPE_SOOP_NUM ] = {
	64,	   // スープ
	72,	   // クリーム
	80,	   // ソボロ
};

// その座標がスープ内かチェック
#define NMIX_DEMO_SOOPIN_MIN_DIST	( 16 )	// 最低でも中心から16遠くにいる必要がある
#define NMIX_DEMO_SOOPIN_MAX_OFS	( 8 )	// 今のスープ幅＋この値分外までタッチパネル反応する
#define NMIX_DEMO_SOOPIN_DEF_SIZE	( 64 )	// 元のスープサイズ半径

#define NMIX_DEMO_SOOPIN_OK		( 0 )
#define NMIX_DEMO_SOOPIN_MIN	( 1 )	/// 中心からの距離が足りない
#define NMIX_DEMO_SOOPIN_MAX	( 2 )	/// 中心から離れすぎ


// 回転速度計算用
#define NMIX_DEMO_ROTACALC_SOOPIN_MIN_DIV	( 2 )	// 中心に近いときに回転速度から割る値

//----------------------------------------------------------------------------
/**
 *	@brief	その座標がスープ内かチェック
 *
 *	@param	p_data		ワーク
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *
 *	@retval	NMIX_DEMO_SOOPIN_OK		( 0 )
 *	@retval NMIX_DEMO_SOOPIN_MIN	( 1 )
 *  @retval	NMIX_DEMO_SOOPIN_MAX	( 2 )
 */
//-----------------------------------------------------------------------------
static u32 NMixData_SoopRota_PlayerInSoop( NMIX_DATA_SOOP* p_data, int x, int y )
{
	fx32 scale;
	u32 speed;
	u32 soop_dist;
	u32 center_dist;

	// 中心からの距離を求める
	center_dist = GetVectorDistance( 
				x, y,
				NMIX_SOOP_ROTA_CX, NMIX_SOOP_ROTA_CY );

	// スピードからスープの半径を求める
	if( p_data->sp_rota >= 0 ){
		speed = p_data->sp_rota;
	}else{
		speed = -p_data->sp_rota;
	}
	scale = NMIX_DATA_SoopSpeedGraScale( speed, p_data->soop_type );
	soop_dist = FX_Mul( scale, NMIX_DEMO_SOOPIN_DEF_SIZE * FX32_ONE ) >> FX32_SHIFT;

	soop_dist += NMIX_DEMO_SOOPIN_MAX_OFS;

	if( (center_dist < NMIX_DEMO_SOOPIN_MIN_DIST) ){
		return NMIX_DEMO_SOOPIN_MIN;
	}else if( (center_dist > soop_dist) ){
		return NMIX_DEMO_SOOPIN_MAX;
	}
	return NMIX_DEMO_SOOPIN_OK;
}
 
//----------------------------------------------------------------------------
/**
 *	@brief	スープ回転調整
 *
 *	@param	p_data			ワーク
 *	@param	cp_commdata		通信データ
 *	@param	comm_count		通信相手の数
 *	@param	rota_way		回転してほしい方向
 *
 *	@return	現在の回転角度
 */
//-----------------------------------------------------------------------------
u16 NMIX_DATA_SoopRota( NMIX_DATA_SOOP* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 rota_way )
{
	int i;
	s32 rota_ave;	// 皆の回転角度の平均
	s32 comm_count_s;
	int net_id;
	fx32 par;
	s32 last_rota;
	u16 rota;
	u32 soop_in_result;	// スープ範囲内チェック結果

	// 皆OKなえリアにいるで初期化
	p_data->ok_area = TRUE;

	// 皆の回転角度の平均を求める
	rota_ave = 0;
	for( i=0; i<comm_count; i++ ){
		net_id = cp_commdata->playno_netid[ i ];

		// そのプレイヤーは、スープ内の位置にいるかチェック
		soop_in_result = NMixData_SoopRota_PlayerInSoop( p_data, 
				cp_commdata->get_game_data[ net_id ].one.x,
				cp_commdata->get_game_data[ net_id ].one.y );

	  	
		switch( soop_in_result ){
		case NMIX_DEMO_SOOPIN_OK:
			rota = cp_commdata->get_game_data[ net_id ].one.rota;
			break;
		case NMIX_DEMO_SOOPIN_MIN:
			rota = cp_commdata->get_game_data[ net_id ].one.rota / NMIX_DEMO_ROTACALC_SOOPIN_MIN_DIV;
			p_data->ok_area = FALSE;
			break;
		case NMIX_DEMO_SOOPIN_MAX:
			rota = 0;
			p_data->ok_area = FALSE;
			break;
		}
		if( cp_commdata->get_game_data[ net_id ].one.rota_way == 0 ){
			rota_ave += rota;
		}else{
			rota_ave -= rota;
		}
	}

	comm_count_s = comm_count;
	rota_ave = rota_ave / comm_count_s;
	
	// スープタイプ反映率からスピード調整
	par = FX_Div( NMIX_DATA_SoopRotaPar[ p_data->soop_type ]*FX32_ONE, NMIX_DATA_SOOP_ROTA_PAR_MAX*FX32_ONE );
	rota_ave = FX_Mul( rota_ave*FX32_ONE, par ) >> FX32_SHIFT;

	// 皆の回転角度から回転スピードを計算
	p_data->sp_rota += rota_ave;


	// 減速値を足しこむ
	if( p_data->sp_rota > 0 ){
		p_data->sp_rota -= NMIX_DATA_SoopRotaSub[ p_data->soop_type ];
		if( p_data->sp_rota < 0 ){
			p_data->sp_rota = 0;
		}
	}else if( p_data->sp_rota < 0 ){
		p_data->sp_rota += NMIX_DATA_SoopRotaSub[ p_data->soop_type ];
		if( p_data->sp_rota > 0 ){
			p_data->sp_rota = 0;
		}
	}

	// sp_rotaの値が+- NMIX_SOOP_MAX_ROTA以内になるようにする
	if( p_data->sp_rota > NMIX_SOOP_MAX_ROTA ){
		p_data->sp_rota = NMIX_SOOP_MAX_ROTA;
	}else if( p_data->sp_rota < -NMIX_SOOP_MAX_ROTA ){
		p_data->sp_rota = -NMIX_SOOP_MAX_ROTA;
	}

	// 前の回転角度保存
	last_rota = p_data->now_rota;

	// 回転
	p_data->now_rota += CalcTool_CircleVectroDistRotaGet( NMIX_SOOP_ROTA_GET_R, NMIX_SOOP_SPEED_RESET( p_data->sp_rota ) );

	// 回転回数を設定
	// 回転方向があっているかチェック
	if( ((rota_way == 0) && (p_data->sp_rota >= 0)) ||
		((rota_way == 1) && (p_data->sp_rota < 0)) ){

		if( rota_way == 0 ){
			if( (last_rota & 0xffff) > (p_data->now_rota & 0xffff) ){
				p_data->rota_count ++;
			}
		}else{
			if( (last_rota & 0xffff) < (p_data->now_rota & 0xffff) ){
				p_data->rota_count ++;
			}
		}
	}

	return p_data->now_rota & 0xffff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	今の回転角度を取得する
 *
 *	@param	cp_data		ワーク
 *
 *	@return	回転角度
 */
//-----------------------------------------------------------------------------
u16 NMIX_DATA_SoopGetRota( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->now_rota & 0xffff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在のスープタイプで何回転したか
 *
 *	@param	cp_data		ワーク
 *
 *	@return	回転カウント
 */
//-----------------------------------------------------------------------------
u32 NMIX_DATA_SoopGetRotaCount( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->rota_count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スープタイプ設定
 *
 *	@param	p_data	ワーク
 *	@param	type	スープタイプ
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_SoopSetType( NMIX_DATA_SOOP* p_data, int type )
{
	GF_ASSERT( type < NMIX_SOOPTYPE_SOOP_NUM );
	p_data->soop_type = type;
	p_data->rota_count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在の回転スピード取得
 *
 *	@param	cp_data		ワーク
 *
 *	@return	回転スピード
 */
//-----------------------------------------------------------------------------
s32 NMIX_DATA_SoopGetRotaSpeed( const NMIX_DATA_SOOP* cp_data )
{
	return cp_data->sp_rota;
}



//----------------------------------------------------------------------------
/**
 *	@brief	スープスピードに関係するのもの計算
 *	
 *	@param	p_data		ワーク
 *	@param	speed		スピード
 *	@param	soop_type	スープタイプ
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_SoopSpeedMain( NMIX_DATA_SOOP_SPEED* p_data, s32 speed, int soop_type )
{
	p_data->kobosi_eff = FALSE;
	p_data->koge_eff = 0;

	// 回転スピードからこぼれるか、こげるかチェックする
	if( NMIX_DATA_SoopSpeedKobore( speed, soop_type ) ){
		// こぼれる
		p_data->speed_over_count ++;

		if( p_data->speed_over_count >= NMIX_SOOP_KOBORE_RETIME ){
			if( p_data->kobosi_count < NMIX_SOOP_SCORE_MAX ){
				p_data->kobosi_count ++;
			}
			p_data->kobosi_eff = TRUE;
			p_data->speed_over_count = 0;
		}

		// 次焦げたら始めてのこげ
		p_data->first_koge_eff = FALSE;
	}else if( NMIX_DATA_SoopSpeedKoge( speed, soop_type ) ){
		// こげる
		p_data->speed_none_count ++;

		if( p_data->speed_none_count >= NMIX_SOOP_KOGE_RETIME ){
			p_data->speed_none_count = 0;

			// 初めて焦げたら、煙出す
			if( p_data->first_koge_eff == FALSE ){
				p_data->koge_eff = NMIX_GAME_COMM_KOGE_KEMURI_REQ;
				p_data->first_koge_eff = TRUE;
			}else{
				p_data->koge_eff = NMIX_GAME_COMM_KOGE_KOGE_REQ;

				if( p_data->koge_count < NMIX_SOOP_SCORE_MAX ){
					p_data->koge_count ++;
				}
			}
		}
	}else{
		// 次焦げたら始めてのこげ
		p_data->first_koge_eff = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	こぼれるかチェック
 *
 *	@param	speed		スピード
 *	@param	soop_type	タイプ
 *
 *	@retval	TRUE	こぼれる
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopSpeedKobore( s32 speed, int soop_type )
{
	int zettai = MATH_IAbs( speed );

	// スープタイプ　最終形態はこぼれない
	if( soop_type == NMIX_SOOPTYPE_SOOP_2 ){
		return FALSE;
	}

	if( zettai >= NMIX_SOOP_KOBORE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	こげるかチェック
 *
 *	@param	speed		スピード
 *	@param	soop_type	タイプ
 *
 *	@retval	TRUE	こげる
 *	@retval FALSE	こげない
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopSpeedKoge( s32 speed, int soop_type )
{
	int zettai = MATH_IAbs( speed );

		
	if( zettai <= NMIX_SOOP_KOGE ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スピードから拡大率を求める
 *
 *	@param	speed		スピード
 *	@param	soop_type	タイプ
 *
 *	@retval	拡大率
 */
//-----------------------------------------------------------------------------
fx32 NMIX_DATA_SoopSpeedGraScale( u16 speed, int soop_type )
{
	fx32 work;
	fx32 scale;
	s32 speed_work;

	// スピードからこげる空いた分引いて、
	// こぼれる境界が最大拡大値になるように求める
	speed_work = speed - NMIX_SOOP_KOGE;
	if( speed_work < 0 ){
		speed_work = 0;
	}

	work = FX_Mul( NMIX_SOOP_MAX_SCALE, speed_work * FX32_ONE );
	scale = FX_Div( work, (NMIX_SOOP_MAX_ROTA - NMIX_SOOP_KOGE) * FX32_ONE );
	return scale + FX32_ONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	回転方向チェンジ　初期化
 *
 *	@param	p_work	ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_RotaWayCont_Init( NMIX_DATA_ROTA_WAY_CONT* p_work )
{
	memset( p_work, 0, sizeof(NMIX_DATA_ROTA_WAY_CONT) );
	p_work->left_par = 2;
	p_work->rota_way_count  = -1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転方向管理　メイン
 *
 *	@param	p_work		ワーク
 *	@param	soop_type	スープタイプ
 *	@param	speed		現在回転スピード
 *	@param	team_work	TEAMWORK得点計算中か
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_RotaWayCont_Main( NMIX_DATA_ROTA_WAY_CONT* p_work, int soop_type, s32 speed, BOOL team_work )
{
	int next_req;
	u32 rnd;
	u32 way_rnd;
	// 次の回転方向チェックまでのカウント値
	static u8 NextCheckCount[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		{ 30*5 },
		{ 30*4 },
		{ 30*3 },
	};

	p_work->rota_way_chg = FALSE;

	// 今変更チェックするかチェック
	// 逆方向に回っているとき
	// TEAMWORK得点計算中は変更しない
	if( (NMIX_DATA_RotaWayReverseCheck( p_work, speed ) == TRUE) ||
		(team_work == TRUE) ){
		return ;
	}
	
	// 次のチェックまでのｶｳﾝﾀが０なら方向変更
	if( p_work->rota_way_count < 0 ){
		rnd = gf_mtRand();
		way_rnd = (rnd % 5);
		if( way_rnd <= p_work->left_par ){
			// 左
			next_req = 1;
			p_work->rota_way_chg = TRUE;
		}else{
			// 右
			next_req = 0;
			p_work->rota_way_chg = TRUE;
		}

		// １つ前と一緒のとき
		if( next_req == p_work->rota_way_req ){
			// 左右チェック	
			if( p_work->rota_way_req == 1 ){
				if( (p_work->left_par - 1) >= 0 ){
					p_work->left_par --;
				}
			}else{
				if( (p_work->left_par + 1) < 5 ){
					p_work->left_par ++;
				}
			}
		}else{
			p_work->rota_way_req = next_req;
			p_work->left_par = 2;
		}

		OS_Printf( "rnd %d left_par %d\n", rnd, p_work->left_par );

		// 次のエフェクトまでの時間
		p_work->rota_way_count = NextCheckCount[ soop_type ] + (rnd % (2*30));
	}

	p_work->rota_way_count --;
}

//----------------------------------------------------------------------------
/**
 *	@brief	逆方向に進んでいるかチェック
 *
 *	@param	cp_work		ワーク
 *	@param	speed		現在スピード
 *
 *	@retval	TRUE	逆方向
 *	@retval	FALSE	良い方向
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_RotaWayReverseCheck( const NMIX_DATA_ROTA_WAY_CONT* cp_work, s32 speed )
{
	if( ((speed < 0) && (cp_work->rota_way_req == 0)) ||
		((speed > 0) && (cp_work->rota_way_req == 1)) ){
		return TRUE;
	}
	return FALSE;
}	



#define NMIX_DATA_SOOP_ALPHA_ROTA_TIMING	( 5 )	// あとこの回転というところまできたら、αを下げる
#define NMIX_DATA_SOOP_ALPHA_TIME_TIMING	( 2*30 )	// あとこの時間というところまできたらαを下げる
//----------------------------------------------------------------------------
/**
 *	@brief	スープタイプ変更管理
 *
 *	@param	p_work		ワーク
 *	@param	soop_rota_count		回転カウント]
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_SoopAdd_Main( NMIX_DATA_SOOP_ADD* p_work, NMIX_DATA_SOOP* p_soop )
{
	static const u8 SoopAddRotaCountTbl[ NMIX_SOOPTYPE_SOOP_NUM ] = {
		16, 16, 16
	};
	int time_alpha = 31;
	int count_alpha = 31;
	int soop_rota_count = NMIX_DATA_SoopGetRotaCount( p_soop );
	int last_time;
	int last_count;

	// スープタイプ変更
	if( (p_work->next_time == NMIX_DATA_SOOPADD_NEXT_TIME) || 
		(soop_rota_count >= SoopAddRotaCountTbl[ p_work->soop_type ]) ){
		p_work->soop_type ++;
		p_work->next_time = 0;
		soop_rota_count = 0;	// 下のα値求めよう

		if( p_work->soop_type >= NMIX_SOOPTYPE_SOOP_NUM ){
			return TRUE;
		}

		// スープタイプを設定
		NMIX_DATA_SoopSetType( p_soop, p_work->soop_type );
	}
	
	// α値を求める
	last_time = (NMIX_DATA_SOOPADD_NEXT_TIME - p_work->next_time);
	if( last_time <= NMIX_DATA_SOOP_ALPHA_TIME_TIMING ){
		time_alpha = 31 * last_time;
		time_alpha = time_alpha / NMIX_DATA_SOOP_ALPHA_TIME_TIMING;
	}
	last_count = (SoopAddRotaCountTbl[ p_work->soop_type ] - soop_rota_count);
	if( last_count <= NMIX_DATA_SOOP_ALPHA_ROTA_TIMING ){
		count_alpha = 31 * last_count;
		count_alpha = count_alpha / NMIX_DATA_SOOP_ALPHA_ROTA_TIMING;
	}

	// α値の小さいほうを取る
	if( time_alpha < count_alpha ){
		p_work->rota_alpha = time_alpha;
	}else{
		p_work->rota_alpha = count_alpha;
	}
	p_work->next_time ++;

	return FALSE;
}

#define NMIX_DATA_TEAMWORK_CHECK_ROTA	( 600 )
//----------------------------------------------------------------------------
/**
 *	@brief	TEAMWORK　ｶｳﾝﾀ
 *
 *	@param	p_work			ワーク
 *	@param	cp_comm_pack	通信データ
 *	@param	comm_count		ｶｳﾝﾀ
 *	@param	speed			スピード
 *	@param	soop_type		スープタイプ
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_TeamWork_Main( NMIX_DATA_TEAMWORK* p_work, const NUTMIX_GAME_COMM_PACK* cp_comm_pack, int comm_count, s32 speed, int soop_type, BOOL ok_area, BOOL reverse )
{
	u32 dist;
	const NUTMIX_OYA* cp_oya = &cp_comm_pack->get_game_data[ COMM_PARENT_ID ].oya;
	const NUTMIX_ONE* cp_oya_one;
	int i;
	int net_id;
	

	p_work->team_work_req = FALSE;

	// こげたり、こぼれたりしないかチェック
	if( (NMIX_DATA_SoopSpeedKoge( speed, soop_type ) == TRUE) ||
		(NMIX_DATA_SoopSpeedKobore( speed, soop_type ) == TRUE) ||
		(ok_area == FALSE) ){
		p_work->team_work_time_add_wait = 0;
		p_work->team_work_time_add_flg = FALSE;
		return ;
	}
	

	// 1用ならでない
	if( comm_count <= 1 ){
		p_work->team_work_time_add_wait = 0;
		p_work->team_work_time_add_flg = FALSE;
		return ;
	}

	// 逆回転していたらでない
	if( reverse == TRUE ){
		return ;
	}

	// 自分と仲間が止まっていたらでない
	for( i=0; i<comm_count; i++ ){
		net_id = cp_comm_pack->playno_netid[ i ];
		cp_oya_one = &cp_comm_pack->get_game_data[ net_id ].one;

		if( cp_oya_one->rota <= NMIX_DATA_TEAMWORK_CHECK_ROTA ){
			return ;
		}
	}

	// 皆が親のエリアに入っているかチェックする
	for( i=1; i<comm_count; i++ ){

		net_id = cp_comm_pack->playno_netid[ i ];
		
		dist = GetVectorDistance( 
				cp_oya->x[ 0 ], cp_oya->y[ 0 ],
				cp_oya->x[ net_id ], cp_oya->y[ net_id ] );

		if( dist > NMIX_DATA_TEAMWORK_AREA ){
			p_work->team_work_time_add_wait = 0;
			p_work->team_work_time_add_flg = FALSE;
			return ;	// エリア外なので抜ける
		}
	}


	// TEAMWORK得点　足し算開始ウエイト
	if( p_work->team_work_time_add_wait < NMIX_DATA_TEAMWORK_EFF_ADD_WAIT ){
		p_work->team_work_time_add_wait ++;
	}else{
		// 最初の1回目はださない
		// タイムの間隔でエフェクトを出す
		if( (p_work->team_work_time % NMIX_DATA_TEAMWORK_EFF_TIMING) == 0 ){
			p_work->team_work_req = TRUE;
		}

		// タイムカウント
		p_work->team_work_time ++;
		p_work->team_work_time_add_flg = TRUE;
	}


}

//----------------------------------------------------------------------------
/**
 *	@brief	親動さ初期化
 *	
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaInit( NMIX_DATA_OYA* p_data )
{
	memset( p_data, 0, sizeof(NMIX_DATA_OYA) );
	NMIX_DATA_RotaWayCont_Init( &p_data->rota_waycont );
	p_data->soop_add.rota_alpha = 31;
	// 回転方向変更チェックを１回実行しておく
	NMIX_DATA_RotaWayCont_Main( &p_data->rota_waycont, 0, 0, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	親メイン動さ
 *
 *	@param	p_data	ワーク
 *	@param	cp_commdata	通信データ
 *	@param	comm_count	通信相手数
 *
 *	@retval	TRUE	ゲーム終了
 *	@retval	FALSE	ゲーム途中
 */
//-----------------------------------------------------------------------------
BOOL NMIX_DATA_OyaMain( NMIX_DATA_OYA* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count )
{
	s32 speed;
	BOOL result;

	// スープタイプ変更
	result = NMIX_DATA_SoopAdd_Main( &p_data->soop_add, &p_data->soop_cont );

	// もしスープタイプ以上になったらゲーム終了
	if( result == TRUE ){
		return TRUE;
	}
	
	// スープ回転制御
	NMIX_DATA_SoopRota( &p_data->soop_cont, cp_commdata, comm_count, p_data->rota_waycont.rota_way_req );

	// スピード取得
	speed = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );

	// スープスピードによる色々なパラメータ設定
	NMIX_DATA_SoopSpeedMain( &p_data->soop_speed_data, speed, p_data->soop_add.soop_type );

	// TEAMWORKタイム設定
	NMIX_DATA_TeamWork_Main( &p_data->team_work, cp_commdata, comm_count, speed, p_data->soop_add.soop_type, p_data->soop_cont.ok_area, NMIX_DATA_RotaWayReverseCheck( &p_data->rota_waycont, speed ) );

	// 回転方向変更チェック
	NMIX_DATA_RotaWayCont_Main( &p_data->rota_waycont, p_data->soop_add.soop_type, speed, p_data->team_work.team_work_time_add_flg );
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	親通信データ作成
 *
 *	@param	p_data			ワーク
 *	@param	p_comm_pack		通信コマンドPACKAGE
 *	@param	comm_count		通信人数
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	int i;
	NUTMIX_OYA* p_oya = &p_comm_pack->send_game_data.oya;
	s32	sp_rota;
	
	// 通信データ設置
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_oya->x[ i ] = p_comm_pack->get_game_data[ i ].one.x;
		p_oya->y[ i ] = p_comm_pack->get_game_data[ i ].one.y;
	}
	
	sp_rota = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );
	if( sp_rota >= 0 ){	// ０の時は右左なしと受け取り側が解釈
		p_oya->rota_sp = sp_rota & 0xffff;
		p_oya->rota_way = 0;
	}else{
		p_oya->rota_sp = (-sp_rota) & 0xffff;
		p_oya->rota_way = 1;
	}
	p_oya->rota		= NMIX_DATA_SoopGetRota( &p_data->soop_cont );

	p_oya->koge_req = p_data->soop_speed_data.koge_eff;
	p_oya->kobore_req = p_data->soop_speed_data.kobosi_eff;

	// 回転リクエスト方向設定
	p_oya->now_rota_req = p_data->rota_waycont.rota_way_req;
	p_oya->rota_req_eff = p_data->rota_waycont.rota_way_chg;

	// 今のスープ形状とα値
	if( p_data->soop_add.soop_type < NMIX_SOOPTYPE_SOOP_NUM ){
		p_oya->mix_type = p_data->soop_add.soop_type;
	}else{
		p_oya->mix_type = NMIX_SOOPTYPE_SOOP_2;
	}

	p_oya->alpha_num = p_data->soop_add.rota_alpha;

	// キラキラエフェクト
	p_oya->kirakira_eff = p_data->team_work.team_work_req;
}

//----------------------------------------------------------------------------
/**
 *	@brief	親データ作成
 *
 *	@param	p_data			データ
 *	@param	p_oya			親データ格納先
 *	@param	comm_count		通信相手数
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake_Init( NMIX_DATA_OYA* p_data, NUTMIX_OYA* p_oya, int comm_count )
{
	int i;
	s32	sp_rota;

	// 通信データ設置
	for( i=0; i<NUTMIXER_MEMBER_MAX; i++ ){
		p_oya->x[ i ] = 128;
		p_oya->y[ i ] = 96;
	}
	
	
	sp_rota = NMIX_DATA_SoopGetRotaSpeed( &p_data->soop_cont );
	if( sp_rota >= 0 ){	// ０の時は右左なしと受け取り側が解釈
		p_oya->rota_sp = sp_rota & 0xffff;
		p_oya->rota_way = 0;
	}else{
		p_oya->rota_sp = (-sp_rota) & 0xffff;
		p_oya->rota_way = 1;
	}
	p_oya->rota		= NMIX_DATA_SoopGetRota( &p_data->soop_cont );

	p_oya->koge_req = p_data->soop_speed_data.koge_eff;
	p_oya->kobore_req = p_data->soop_speed_data.kobosi_eff;

	// 回転リクエスト方向設定
	p_oya->now_rota_req = p_data->rota_waycont.rota_way_req;
	p_oya->rota_req_eff = p_data->rota_waycont.rota_way_chg;

	// 今のスープ形状とα値
	p_oya->mix_type = p_data->soop_add.soop_type;
	p_oya->alpha_num = p_data->soop_add.rota_alpha;

	// キラキラエフェクト
	p_oya->kirakira_eff = p_data->team_work.team_work_req;
}

//----------------------------------------------------------------------------
/**
 *	@brief	調理時間計算
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCookCountAdd( NMIX_DATA_OYA* p_data )
{
	// 調理時間カウント
	p_data->cook_time ++;
}


static const u8 playnum_teamwork_score[ NUTMIXER_MEMBER_MAX ] = {	// TEAMWORKプレイ得点
	0, 1, 5, 10
};
enum{
	NMIX_PORUTO_PARA_KARAI,	// これは、木の実の方の定数にあっています
	NMIX_PORUTO_PARA_SIBUI,	// include/itemtool/nuts.h
	NMIX_PORUTO_PARA_AMAI,	// include/savedata/poruto_def.h
	NMIX_PORUTO_PARA_NIGAI,	// にはあっていません
	NMIX_PORUTO_PARA_SUPPAI,
	NMIX_PORUTO_PARA_NUM,
};

// TEAMWORK得点カウントタイミング
#define NMIX_TEAMWORK_SCORE_TIMING	( 6 )
#define NMIX_TEAMWORK_SCORE_DIV		( 10 )

#define NMIX_TEAMWORK_SCORE_SUB_MAX	( 10 )
#define NMIX_MAROYAKA_LIMIT	( 15 )

static int teamWorkScoreGet( u32 time, u32 comm_count )
{
	int score;
	score = ((time / NMIX_TEAMWORK_SCORE_TIMING)*playnum_teamwork_score[ comm_count -1 ]) / NMIX_TEAMWORK_SCORE_DIV;	// 秒単位に * (0.2)

	if( score > NMIX_SOOP_SCORE_MAX ){
		score = NMIX_SOOP_SCORE_MAX;
	}
	return score;
}
//----------------------------------------------------------------------------
/**
 *	@brief	ポルトデータ作成
 *
 *	@param	p_data			ワーク
 *	@param	p_poruto		ポルトデータ格納先
 *	@param	cp_commdata		通信データ
 *	@param	comm_count		通信相手数
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCalcPorutoData( NMIX_DATA_OYA* p_data, PORUTO_DATA* p_poruto, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 heapID )
{
	NUTSDATA* p_nut;	// 木の実データ
	int i, j;
	const NUTMIX_GAME_BGFORE* cp_before = cp_commdata->get_oya_ko_before_data.before;
	s32 param[ NMIX_PORUTO_PARA_NUM ] = {0,0,0,0,0};		// 辛　渋　甘　苦　酸
	s32 umami = 0;
	s32 param_result[ NMIX_PORUTO_PARA_NUM ];		// 辛　渋　甘　苦　酸　
	s32 umami_result;
	int equal_count;	// 木の実が同じ数
	int equal_count_max;// 同じ木の実の数最大数
	BOOL black_poru_flg;	// だめポルトフラグ
	int sub_idx;
	int sub_num;
	int minus_count;
	int cook_time_para;	// 料理時間から算出する完成値　1=100の値
	int calc_work;
	u8 poruto_param[ NMIX_PORUTO_PARA_NUM ];
	int netid, netid_j;

	// ①皆の木の実データ取得
	equal_count_max = 0;
	for( i=0; i<comm_count; i++ ){
		netid = cp_commdata->playno_netid[ i ];
		p_nut = Nuts_DataLoadItem( cp_before[ netid ].nut_type, heapID );
		// 同じ木の実数カウント
		equal_count = 0;
		for( j=0; j<comm_count; j++ ){
			netid_j = cp_commdata->playno_netid[ j ];
			if( cp_before[ netid ].nut_type == cp_before[ netid_j ].nut_type ){
				equal_count ++;
			}
		}
		if( equal_count > equal_count_max ){
			equal_count_max = equal_count;
		}
		// パラメータ足し算
		OS_Printf( "味player_%d  ", i );
		for( j=0; j<NMIX_PORUTO_PARA_NUM; j++ ){
			param[ j ] += Nuts_ParamGet( p_nut, NUTS_PRM_KARAI+j );
			OS_Printf( "%d  ", Nuts_ParamGet( p_nut, NUTS_PRM_KARAI+j ) );
		}
		umami += Nuts_ParamGet( p_nut, NUTS_PRM_UMAI );
		OS_Printf( "%d  \n", Nuts_ParamGet( p_nut, NUTS_PRM_UMAI ) );

		sys_FreeMemoryEz( p_nut );
	}

	// 人数の半数が　同じポルトのときは、だめポルト
	if( (equal_count_max >= 2) && ( comm_count > 1 ) ){
		black_poru_flg = TRUE;
	}else{
		black_poru_flg = FALSE;
	}

	// ⑦うまみは、平均 と　プレイ人数引き算
	umami_result = (umami / comm_count) - comm_count;

	
	// ②打ち消しルール計算
	// ③同時にマイナスの数を計算
	minus_count = 0;
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// 酸っぱいまで
		sub_idx = (i + 1) % NMIX_PORUTO_PARA_NUM;	// 辛味に変更
		param_result[ i ] = param[ i ] - param[ sub_idx ];
		if( param_result[i] < 0 ){
			minus_count ++;
		}
	}

	OS_Printf( "辛%d　渋%d　甘%d　苦%d　酸%d\n", param_result[0],
			param_result[1], param_result[2], param_result[3], 
			param_result[4]);

	// ④マイナス数分　みんな引く
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// 酸っぱいまで
		param_result[ i ] -= minus_count;
	}
	
	// マイナスが4つ以上ならまずいポルト
	if( minus_count >= 4 ){
		black_poru_flg = TRUE;
	}


	// 調理時間　完成値作成
	cook_time_para = (NMIX_DATA_SOOP_COOK_MAX_TIME*1000) / p_data->cook_time;
	if( (cook_time_para % 10) >= 5 ){	// 小数点第3位四捨五入
		cook_time_para += 10;
	}
	cook_time_para /= 10;	// 小数点第２位までにする

	// 調理時間完成値
	OS_Printf( "調理時間完成値 %d / 100 \n", cook_time_para );

	OS_Printf( "マイナス値引き算後　辛%d　渋%d　甘%d　苦%d　酸%d\n", param_result[0],
			param_result[1], param_result[2], param_result[3], 
			param_result[4]);

	OS_Printf( "焦がした数%d　こぼした数%d\n", p_data->soop_speed_data.koge_count, p_data->soop_speed_data.kobosi_count );
	
	// ⑤ゲームの計算結果を追加
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// 酸っぱいまで
		// 調理完成値設定
		calc_work = param_result[ i ] * cook_time_para;
		if( (calc_work % 100) >= 50 ){	// 小数点以下四捨五入
			calc_work += 100;
		}
		calc_work = calc_work / 100;	// 調理完成値を実数だけにする
		param_result[ i ] = calc_work - (p_data->soop_speed_data.koge_count + p_data->soop_speed_data.kobosi_count);	// 調理完成値からこぼした数　焦がした数を減らす

		// マイナスになったら0にする
		if( param_result[ i ] < 0 ){
			param_result[ i ] = 0;
		}
	}

	OS_Printf( "TEAMWORK %d\n", p_data->team_work.team_work_time / NMIX_TEAMWORK_SCORE_TIMING );

	// うまみから　TEAMWORKタイムを引く
	if( comm_count > 1 ){
		sub_num = teamWorkScoreGet( p_data->team_work.team_work_time, comm_count );

		if( sub_num > NMIX_TEAMWORK_SCORE_SUB_MAX ){
			sub_num = NMIX_TEAMWORK_SCORE_SUB_MAX;
		}
		umami_result -= sub_num;
	}
	if( umami_result < NMIX_MAROYAKA_LIMIT ){
		umami_result = NMIX_MAROYAKA_LIMIT;
	}

	OS_Printf( "うまみ %d  結果うまみ %d \n", (umami / comm_count), umami_result );

	// ポルト作成用配列に設定
	for( i=0; i<NMIX_PORUTO_PARA_NUM; i++ ){	// 酸っぱいまで
		poruto_param[ i ] = param_result[ i ];
	}

	OS_Printf( "辛%d　渋%d　甘%d　苦%d　酸%d\n", poruto_param[0],
			poruto_param[1], poruto_param[2], poruto_param[3], 
			poruto_param[4]);

	
	// ⑥ポルト作成
	p_data->poruto_type = PorutoData_CalcParam( p_poruto, poruto_param, umami_result, black_poru_flg );

	// ポルトのタイプとレベルと保存
	p_data->poruto_lv	= PorutoData_GetLevel( p_poruto );

	OS_Printf( "poruto_type %d\n", p_data->poruto_type);
}



//----------------------------------------------------------------------------
/**
 *	@brief	ゲーム結果通信データ送信
 *
 *	@param	p_data			データ
 *	@param	p_comm_pack		通信ワーク
 *	@param	comm_count		通信相手 
 */
//-----------------------------------------------------------------------------
void NMIX_DATA_OyaCommDataMake_Result( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	NUTMIX_COMM_RESULT* p_result = &p_comm_pack->send_oya_result_data;
	int time_set;
	
	p_result->kobore_num = p_data->soop_speed_data.kobosi_count;
	p_result->kogasi_num = p_data->soop_speed_data.koge_count;
	p_result->match_num	 = teamWorkScoreGet( p_data->team_work.team_work_time, comm_count );
	p_result->poruto_type	= p_data->poruto_type;
	p_result->poruto_lv		= p_data->poruto_lv;

	time_set = p_data->cook_time;
	p_result->min			= time_set / (60*30);	// 分
	time_set -= p_result->min * (60*30);
	p_result->second		= time_set / (30);		// 秒
	time_set -= p_result->second * 30;
	p_result->dec			= (100*time_set)/30;	// 30が100になるように値設定

	OS_Printf( "cook_time %d\n", p_data->cook_time );
}



#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
void NMIX_DATA_OyaCommDataMake_Result_MaxDebug( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count )
{
	NUTMIX_COMM_RESULT* p_result = &p_comm_pack->send_oya_result_data;
	
	p_result->kobore_num = NMIX_SOOP_SCORE_MAX;
	p_result->kogasi_num = NMIX_SOOP_SCORE_MAX;
	p_result->match_num	 = NMIX_SOOP_SCORE_MAX;
	p_result->poruto_type	= PORUTO_FLAVOR_BI_SO;
	p_result->poruto_lv		= 99;

	p_result->min			= 99;	// 分
	p_result->second		= 99;		// 秒
	p_result->dec			= 99;
}
#endif // NMIX_DEBUG_DUMMY_RESULT_ON
