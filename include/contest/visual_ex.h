//==============================================================================
/**
 * @file	visual_ex.h
 * @brief	ダンス部門：外部公開ヘッダ
 * @author	matsuda
 * @date	2006.03.09(木)
 *
 * ダンス部門で外部に公開する必要のある定義等をここに書いています
 */
//==============================================================================
#ifndef __VISUAL_EX_H__
#define __VISUAL_EX_H__


//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	座標
//--------------------------------------------------------------
///ポケモン登場座標X
#define VISUAL_APPEAR_X			(128)
///ポケモン登場座標Y
#define VISUAL_APPEAR_Y			(24)

///ポケモン到着座標X
#define VISUAL_ARRIVAL_X		(VISUAL_APPEAR_X)
///ポケモン到着座標Y
#define VISUAL_ARRIVAL_Y		(96 - 32)

///ポケモン定位置Z
#define VISUAL_POKEPOS_Z		(APPEAR_Z_TYPE_AA)


///トレーナー初期座標X
#define VISUAL_TRAINER_APPEAR_X		(320)
///トレーナー初期座標X
#define VISUAL_TRAINER_APPEAR_Y		(32)
///トレーナー初期座標X
#define VISUAL_TRAINER_APPEAR_Z		(VISUAL_POKEPOS_Z - 0x40)

///トレーナー到着座標X
#define VISUAL_TRAINER_ARRIVAL_X		(230)
///トレーナー到着座標X
#define VISUAL_TRAINER_ARRIVAL_Y		(VISUAL_TRAINER_APPEAR_Y)
///トレーナー到着座標X
#define VISUAL_TRAINER_ARRIVAL_Z		(VISUAL_POKEPOS_Z - 0x40)



#endif	//__VISUAL_EX_H__

