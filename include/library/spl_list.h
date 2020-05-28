/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_list.h

  ���X�g����

  ���X�g�����������\���̂̐擪�ɁA�����̍\���̂������Ă���
  �L���X�g�Ń��X�g�������s���A�A�A���Ă���Ȃ�ŗǂ��̂��H
  �m�[�h���N�̏��L���A�Ƃ��A�����������Ƃ������̂ł��Ȃ�댯

  $Id: spl_list.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_list.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.2  2005/08/31 09:54:04  okane_shinji
  ���X�g�ɋ@�\�ǉ�

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_LIST_H__
#define __SPL_LIST_H__

/* �\���� ------------------------------------------------------------------ */

// ���X�g�̊e�m�[�h
typedef struct SPLNode
{
	struct SPLNode* p_next;
	struct SPLNode* p_prev;
} SPLNode;

// ���X�g�{��
typedef struct SPLList
{
	SPLNode* p_begin;
	int node_num;
	SPLNode* p_end;
} SPLList;

/* ------------------------------------------------------------------------- */


/* �e��m�[�h���� ---------------------------------------------------------- */

extern void spl_push_back(SPLList* p_list, SPLNode* p_node);
extern void spl_push_front(SPLList* p_list, SPLNode* p_node);

extern SPLNode* spl_pop_back(SPLList* p_list);
extern SPLNode* spl_pop_front(SPLList* p_list);

extern SPLNode* spl_del(SPLList* p_list, SPLNode* p_node);

/* ------------------------------------------------------------------------- */

#endif
