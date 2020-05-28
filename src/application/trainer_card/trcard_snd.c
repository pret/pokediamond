//==============================================================================================
/**
 * @file	trcard_snd.c
 * @brief	トレーナーケース　バッチ鉄琴操作
 * @author	Satoshi Nohara
 * @date	2005.12.06
 */
//==============================================================================================
#include "common.h"
#include "system/snd_tool.h"
#include "trcard_sys.h"
#include "trcard_snd.h"

/*
	//メモ

	・バッチ以外のSEが鳴る時に、バッチの音を全て止める処理が必要

	・均一にずれるので、バッチごとに多少のずれ幅をつけた方がよりずれて聞こえる
*/


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define SND_BADGE_NO_USE			(0xff)

//基本音程
enum{
	P_C = 0,					//C
	P_D = (64*2),				//D
	P_E = (64*4),				//E
	P_F = (64*5),				//F
	P_G = (64*7),				//G
	P_A = (64*9),				//A
	P_B = (64*11),				//B
	PCC = (64*12),				//C

	//P_DIFF_MAX = (64+32),		//最大音程ずれ
	P_DIFF_MAX = (64+32+512),	//最大音程ずれ(06.04.12)
	P_DIFF = (P_DIFF_MAX/TR_CARD_BADGE_LV_MAX),	//音程ずれ(レベル数で割った値)
};


//==============================================================================================
//
//	データ
//
//==============================================================================================
//音程テーブル
static const u16 basic_pitch_tbl[8] = { P_C, P_D, P_E, P_F, P_G, P_A, P_B, PCC };	//音程ずれなし


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
static void Snd_DebugBadge( SND_BADGE_WORK* wk );
static void Snd_BadgeWorkPlay_Sub1( SND_BADGE_WORK* wk );
static BOOL Snd_BadgeWorkPlay_Sub2( SND_BADGE_WORK* wk, const int no, const u8 lv );
static BOOL Snd_BadgeWorkPlay_Sub3( SND_BADGE_WORK* wk, const int no, const u8 lv );
static BOOL Snd_BadgeWorkPlay_Sub4( SND_BADGE_WORK* wk, const int no, const u8 lv );
static void Snd_BadgeWorkSort2( SND_BADGE_WORK* wk );
static void Snd_BadgeWorkSort3( SND_BADGE_WORK* wk, int num, int player, int no );
static void Snd_BadgeWorkPitch( int num, const int no, const u8 lv );


//==============================================================================================
//
//	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	トレーナーケース　バッジワーク初期化
 *
 * @param	wk		SND_BADGE_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void Snd_DebugBadge( SND_BADGE_WORK* wk )
{
	int i,j;

	OS_Printf( "============================\n" );

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){
		OS_Printf( "i=%d, 0=%d\n", i, wk->player[i][0] );
		OS_Printf( "i=%d, 1=%d\n", i, wk->player[i][1] );
	}

}

//--------------------------------------------------------------
/**
 * @brief	トレーナーケース　バッジワーク初期化
 *
 * @param	wk		SND_BADGE_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BadgeWorkInit( SND_BADGE_WORK* wk )
{
	int i,j;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){
		wk->player[i][0] = i;						//"0,1,2,3"
		wk->player[i][1] = SND_BADGE_NO_USE;		//クリア
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	トレーナーケース　バッジ鉄琴を鳴らす
 *
 * @param	wk		SND_BADGE_WORK型のポインタ
 * @param	no		バッジナンバー(0から7)
 * @param	lv		バッジレベル(0～4)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void Snd_BadgeWorkPlay( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i;

	//使用中で、すでに再生終了しているものはクリアする！
	Snd_BadgeWorkPlay_Sub1( wk );

	//debug
	//Snd_DebugBadge( wk );

	//渡されたバッチが使用中の時は、同じプレイヤーで再生する！
	if( Snd_BadgeWorkPlay_Sub2(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub2 再生!" );
		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	//渡されたバッチを新規に鳴らす時
	if( Snd_BadgeWorkPlay_Sub3(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub3 再生!" );

		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	//プレイヤーが全て埋まっている時は、一番古いデータを消して、上書きする
	if( Snd_BadgeWorkPlay_Sub4(wk,no,lv) == TRUE ){

		//OS_Printf( "Sub4 再生!" );

		//debug
		//Snd_DebugBadge( wk );
		return;
	}

	return;
}

//使用中で、すでに再生終了しているものはクリアする！
static void Snd_BadgeWorkPlay_Sub1( SND_BADGE_WORK* wk )
{
	int i;

	//プレイヤー数だけチェック
	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//使用中になっていて
		if( wk->player[i][1] != SND_BADGE_NO_USE ){
		
			//再生終了していたら
			if( Snd_PlayerCountPlayingSeq( (PLAYER_SE_1 + wk->player[i][0]) ) == 0 ){
				wk->player[i][1] = SND_BADGE_NO_USE;		//クリア
				//OS_Printf( "Sub1 クリア!" );
			}
		}
	}

	//ソート2(データを詰める)
	Snd_BadgeWorkSort2( wk );
	return;
}

//渡されたバッチが使用中の時は、同じプレイヤーで再生する！
static BOOL Snd_BadgeWorkPlay_Sub2( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//渡されたバッチが使用中の時
		if( wk->player[i][1] == no ){

			//同じハンドル、プレイヤーで鳴らす
			Snd_BadgeWorkPitch( wk->player[i][0], no, lv );

			//Snd_BadgeWorkSort( wk, i );	//ソート
			Snd_BadgeWorkSort3( wk, i, wk->player[i][0], no );	//ソート

			return TRUE;
		}
	}

	return FALSE;
}

//渡されたバッチを新規に鳴らす時
static BOOL Snd_BadgeWorkPlay_Sub3( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int i,player;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		//使用していないプレイヤーを探す
		if( wk->player[i][1] == SND_BADGE_NO_USE ){

			Snd_BadgeWorkPitch( wk->player[i][0], no, lv );

			Snd_BadgeWorkSort3( wk, i, wk->player[i][0], no );	//ソート
			return TRUE;
		}
	}

	return FALSE;
}

//プレイヤーが全て埋まっている時は、一番古いデータを消して、上書きする
static BOOL Snd_BadgeWorkPlay_Sub4( SND_BADGE_WORK* wk, const int no, const u8 lv )
{
	int num;

	num = (SND_BADGE_PLAYER_MAX-1);

	Snd_BadgeWorkPitch( wk->player[num][0], no, lv );

	Snd_BadgeWorkSort3( wk, num, wk->player[num][0], no );	//ソート

	return TRUE;
}

//ソート(渡された値を先頭にする)
static void Snd_BadgeWorkSort3( SND_BADGE_WORK* wk, int num, int player, int no )
{
	int i;

	for( i=num; i > 0 ;i-- ){
		wk->player[i][0] = wk->player[i-1][0];
		wk->player[i][1] = wk->player[i-1][1];
	}

	//先頭にセット
	wk->player[0][0] = player;
	wk->player[0][1] = no;
	return;
}

//ソート2(データを詰める)
static void Snd_BadgeWorkSort2( SND_BADGE_WORK* wk )
{
	int i;

	for( i=0; i < SND_BADGE_PLAYER_MAX ;i++ ){

		if( wk->player[i][0] == SND_BADGE_NO_USE ){
			wk->player[i][0] = wk->player[i+1][0];
			wk->player[i+1][0] = SND_BADGE_NO_USE;
		}
	}

	return;
}

//バッチにより音程を操作する
//レベルにより音程の微調整をする
static void Snd_BadgeWorkPitch( int num, const int no, const u8 lv )
{
	int diff = P_DIFF * (TR_CARD_BADGE_LV_MAX-lv);
	Snd_ArcPlayerStartSeqEx( (SND_HANDLE_SE_1+num), (PLAYER_SE_1+num), SEQ_SE_DP_BADGE_C );
	//Snd_PlayerSetTrackPitch( (SND_HANDLE_SE_1+num), 0xffff, (basic_pitch_tbl[no]+diff) );	//上ずれ
	Snd_PlayerSetTrackPitch( (SND_HANDLE_SE_1+num), 0xffff, (basic_pitch_tbl[no]-diff) );	//下ずれ
	return;
}


