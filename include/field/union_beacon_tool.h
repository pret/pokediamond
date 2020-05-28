//=============================================================================
/**
 * @file	union_beacon_tool.H
 * @brief	���j�I�����[�������ڐݒ菈��
 * @author	Akito Mori
 * @date    	2006.03.16
 */
//=============================================================================

#ifndef __UNION_BEACON_TOOL_H__
#define __UNION_BEACON_TOOL_H__

enum UNION_VIEW_INFO {
  UNIONVIEW_ICONINDEX,	// �Q�c�摜�p(�l���n�a�i�j�̃e�[�u���̏ꏊ�i0-18)
  UNIONVIEW_TRTYPE,		// �g���[�i�[�O���t�B�b�N�̂h�c�i�o�g����J�[�h���̃O���t�B�b�N�j
  UNIONVIEW_MSGTYPE,	// �g���[�i�[�^�C�v�̃��b�Z�[�W�m�n(msg_trtype_name_dat)

};

// �g���[�i�[VIEWTYPE�Ɛ��ʂ�����������o��
extern int  UnionView_GetTrainerInfo( int view_type, int sex, int info );

extern int  UnionView_GetTrainerType( u32 id, int sex, u32 select );
extern void UnionView_SetUpTrainerTypeSelect( u32 id, int sex, WORDSET *wordset );


#endif