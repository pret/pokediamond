//==============================================================================
/**
 * @file	battle_input_type.h
 * @brief	戦闘入力画面の外側で使用される構造体の定義など
 * @author	matsuda
 * @date	2006.05.11(木)
 */
//==============================================================================
#ifndef __BATTLE_INPUT_TYPE_H__
#define __BATTLE_INPUT_TYPE_H__


//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
//	SCENEワーク
//--------------------------------------------------------------
///コマンド選択画面構成用のSceneワーク
typedef struct{
	u8 client_type;
	u8 client_no;
	u8 sel_mons_no;
	u8		icon_status;

	s16		icon_hp;				//現在のHP
	u16		icon_hpmax;				//現在のHPMAX
}BINPUT_SCENE_COMMAND;

///技選択画面構成用のSceneワーク
typedef struct{
	u16			wazano[WAZA_TEMOTI_MAX];		//wazano
	u8			pp[WAZA_TEMOTI_MAX];			//pp
	u8			ppmax[WAZA_TEMOTI_MAX];			//ppmax
	u8			client_type;					//
}BINPUT_SCENE_WAZA;

///ポケモン選択画面構成用のSceneワーク
typedef struct{
	DIR_SELECT_POKE_PARAM	dspp[CLIENT_MAX];
	u8			client_type;
	u8			pokesele_type;	///<対象選択タイプ
}BINPUT_SCENE_POKE;

///「はい・いいえ」選択画面構成用のSceneワーク
typedef struct{
	u16 waza_no;
	
	u16 dummy;		///<4バイト境界ダミー
}BINPUT_SCENE_YESNO;



#endif	//__BATTLE_INPUT_TYPE_H__

