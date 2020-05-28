//==============================================================================
/**
 * @file	con_tool.h
 * @brief	コンテスト全体で使用する汎用的なツール
 * @author	matsuda
 * @date	2005.11.22(火)
 */
//==============================================================================
#ifndef __CON_TOOL_H__
#define __CON_TOOL_H__

#include "contest/contest.h"
#include "system/gra_tool.h"


//==============================================================================
//	外部関数宣言
//==============================================================================
extern int ConTool_ContestSioFlagCheck(CONTEST_SYSTEM *consys);
extern void ConTool_JudgeEntry(CONTEST_SYSTEM *consys, int heap_id, int sp_no, int type, int rank);
extern void ConTool_CpuBreederEntry(CONTEST_SYSTEM *consys, int heap_id, int entry_num, int type, int rank, int mode, int hof_flag, int zenkoku_zukan_flag);
extern SOFT_SPRITE * ConTool_BreederPokemonAdd(SOFT_SPRITE_MANAGER *ssm_p, int poly_id, 
	POKEMON_PARAM *pp, int dir, EXCHR_PARAM *ep, int heap_id, int x, int y, int z);
extern void ConTool_BreederPokeParaCreate(const BREEDER_DATA *bd, POKEMON_PARAM *pp, int heap_id);
extern s8 ConTool_GetAPWaza_App(int appeal_no);
extern void ConTool_GetAPSetumeiMsgID(int appeal_no, u32 *u_id, u32 *d_id);
extern int ConTool_ServerMineCheck(CONTEST_SYSTEM *consys);
extern void ConTool_GetKoukaMsgID(int appeal_no, int msg_type, u32 *msg_id, u32 *msg_tag);
extern u32 ConTool_GetRankMsgID(int con_rank, int mode, int sio_flag);
extern u32 ConTool_IMCGetRankMsgID(int con_rank);
extern u32 ConTool_IMCGetTypeMsgID(int con_type);
extern u32 ConTool_GetTypeMsgID(int con_type, int con_mode);
extern int ConTool_EntryNoGet(int breeder_no);
extern void ConTool_CpuBreederImcSet(CONTEST_SYSTEM *consys, int heap_id);
extern int ConTool_BreederNoGet(int entry_no);
extern u32 ConTool_GetListAPSetumeiMsgID(int appeal_no);
extern BOOL ConTool_PracticeModeCheck(CONTEST_SYSTEM *consys);
extern BOOL ConTool_TutorialModeCheck(CONTEST_SYSTEM *consys);
extern int ConTool_HeartNumGet_BP(CONTEST_SYSTEM *consys, int breeder_no);
extern int ConTool_HeartNumGet_Clip(CONTEST_SYSTEM *consys, int breeder_no);
extern u32 ConTool_RibbonIDGet(int rank, int type);
extern u32 ConTool_ThemeRandomSelect(int rank, int sio_flag);
extern void ConTool_PracticeDanceImcSet(CONTEST_SYSTEM *consys);


#endif	//__CON_TOOL_H__

