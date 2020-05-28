//==============================================================================
/**
 * @file	res_tool.h
 * @brief	結果発表画面ツール類のヘッダ
 * @author	matsuda
 * @date	2006.03.17(金)
 */
//==============================================================================
#ifndef __RES_TOOL_H__
#define __RES_TOOL_H__


//==============================================================================
//	定数定義
//==============================================================================
///ダンス部門ノーマル会話メッセージのID定義
///(※DanceTalkMsgDataテーブルと並びを同じにしておく事！！)
enum{
	A_TALK_CONRES_NULL,			///<メッセージ指定なし

	A_TALK_HOST_01,
	A_TALK_HOST_02,
	A_TALK_HOST_03,
	A_TALK_HOST_04,
	A_TALK_HOST_05,
	A_TALK_HOST_06,
};

//--------------------------------------------------------------
//	RT_WndOpenEffStart関数の引数に使用
//--------------------------------------------------------------
enum{
	RT_WNDEFF_OPEN,			///<ウィンドウ開く
	RT_WNDEFF_CLOSE,		///<ウィンドウ閉じる
};

//--------------------------------------------------------------
//	PokeSlideEffectStart関数の引数に使用
//--------------------------------------------------------------
enum{
	RT_POKESLIDE_IN,		///<ポケモン登場
	RT_POKESLIDE_OUT,		///<ポケモン退場
};

//==============================================================================
//	外部関数宣言
//==============================================================================
extern void RT_SoftSpriteAddAll(CONRES_PROC_WORK *cpw);
extern void RT_SoftSpriteDelAll(CONRES_SYSTEM_PARAM *sys);
extern void RT_A_TalkMessageSet(CONRES_PROC_WORK *cpw, u32 a_talk_id, const CRTAG_PARAM *tagpara);
extern int RT_TalkMessageEndCheck(CONRES_PROC_WORK *cpw);
extern void RT_Announce_BGSet(CONRES_PROC_WORK *rpw);
extern void RT_Announce_BGDel(CONRES_PROC_WORK *rpw);
extern void RT_Announce_OBJSet(CONRES_PROC_WORK *rpw);
extern void RT_Announce_OBJDel(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGSet(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGDel(CONRES_PROC_WORK *rpw);
extern void RT_Result_OBJSet(CONRES_PROC_WORK *rpw);
extern void RT_Result_OBJDel(CONRES_PROC_WORK *rpw);
extern void RT_PokeIconSetAll(CONRES_PROC_WORK *rpw);
extern void RT_PokeIconDelAll(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiResouceLoad(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiResouceFree(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconSetAll(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconDelAll(CONRES_PROC_WORK *rpw);
extern void RT_WndOpenEffStart(CONRES_PROC_WORK *rpw, int open_close, u8 *end_flag);
extern void PokeSlideEffectStart(CONRES_PROC_WORK *rpw, int breeder_no, int in_out, u8 *end_flag);
extern void RT_ConfettiCreateTaskSet(CONRES_PROC_WORK *rpw);
extern void RT_ConfettiEndFlagSet(CONRES_PROC_WORK *rpw);
extern void RT_CalcPoint(CONRES_PROC_WORK *rpw);
extern void RT_RankingIconAppearSet(CONRES_PROC_WORK *rpw, int breeder_no, int ranking);
extern void RT_MeterResouceLoad(CONRES_PROC_WORK *rpw);
extern void RT_MeterResouceFree(CONRES_PROC_WORK *rpw);
extern void RT_MeterActorDotCreate(CONRES_PROC_WORK *rpw, int breeder_no, int con_game, 
	int dot, int breeder_pos);
extern void RT_MeterActorDeleteAll(CONRES_PROC_WORK *rpw);
extern void RT_Result_BGSet_Sub(CONRES_PROC_WORK *rpw);
extern void RT_CalcRevicePoint(CONTEST_SYSTEM *consys, int con_game, s16 ret_revise[]);


#endif	//__RES_TOOL_H__

