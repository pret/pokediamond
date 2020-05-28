//============================================================================================
/**
 * @file	enc_tbl_change_def.h
 * @bfief	エンカウントテーブル差し替え位置定義
 * @author	Nozomu Saito
 */
//============================================================================================
#ifndef __ENC_TBL_CHANGE_DEF_H__
#define __ENC_TBL_CHANGE_DEF_H__

typedef enum{
	GENE_ENC_1 = 0,		//大量発生
	GENE_ENC_2 = 1,		//大量発生
	TIME_ENC_1 = 2,		//時間帯
	TIME_ENC_2 = 3,		//時間帯
	SWAY_ENC_1 = 4,		//揺れ草
	SWAY_ENC_2 = 5,		//揺れ草
	SP_ENC_1 = 6,	//特殊枠（サファリ、裏山）
	SP_ENC_2 = 7,	//特殊枠（サファリ、裏山）
	AGB_ENC_1 = 8,	//ＡＢＧスロット
	AGB_ENC_2 = 9,	//ＡＧＢスロット
	SWAY_ENC_3 = 10,	//揺れ草
	SWAY_ENC_4 = 11,	//揺れ草
}ENC_TBL_POS;

#endif //__ENC_TBL_CHANGE_DEF_H__

