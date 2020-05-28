/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl_list.h

  リスト処理

  リスト処理したい構造体の先頭に、ここの構造体を持ってきて
  キャストでリスト処理を行う、、、ってこんなんで良いのか？
  ノードが誰の所有か、とか、そういうことも無いのでかなり危険

  $Id: spl_list.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl_list.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPLライブラリが更新されたので更新

  Revision 1.2  2005/08/31 09:54:04  okane_shinji
  リストに機能追加

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_LIST_H__
#define __SPL_LIST_H__

/* 構造体 ------------------------------------------------------------------ */

// リストの各ノード
typedef struct SPLNode
{
	struct SPLNode* p_next;
	struct SPLNode* p_prev;
} SPLNode;

// リスト本体
typedef struct SPLList
{
	SPLNode* p_begin;
	int node_num;
	SPLNode* p_end;
} SPLList;

/* ------------------------------------------------------------------------- */


/* 各種ノード処理 ---------------------------------------------------------- */

extern void spl_push_back(SPLList* p_list, SPLNode* p_node);
extern void spl_push_front(SPLList* p_list, SPLNode* p_node);

extern SPLNode* spl_pop_back(SPLList* p_list);
extern SPLNode* spl_pop_front(SPLList* p_list);

extern SPLNode* spl_del(SPLList* p_list, SPLNode* p_node);

/* ------------------------------------------------------------------------- */

#endif
