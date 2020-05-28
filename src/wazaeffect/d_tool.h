//==============================================================================
/**
 * @file	d_tool.h
 * @brief	�퓬�p�f�o�b�O���
 * @author	goto
 * @date	2005.10.25(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef __D_TOOL_H__
#define __D_TOOL_H__

extern void DT_MenuInit(int heap, BATTLE_WORK* bw, TCB_PTR tcb, TCB_FUNC func);


extern void DT_WinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, u8 frm, u8 x, u8 y, u8 sx, u8 sy, u8 pal, u16 ofs);
extern void DT_MsgClear(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win);
extern void DT_MsgPrint(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, STRBUF* str, u16 x, u16 y, int flag);

#endif