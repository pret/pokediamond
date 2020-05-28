/*---------------------------------------------------------------------------*
  Project:  simple particle library
  File:     spl.h

  �r�o�k�w�b�_

  $Id: spl.h,v 1.3 2005/11/09 09:53:26 matsuda Exp $
  $Log: spl.h,v $
  Revision 1.3  2005/11/09 09:53:26  matsuda
  SPL���C�u�������X�V���ꂽ�̂ōX�V

  Revision 1.16  2005/07/27 05:59:14  okane_shinji
  SPL_CreateWithInitializeEx��ǉ�

  Revision 1.15  2004/12/02 08:01:32  okane_shinji
  ver110�Ή�

  Revision 1.14  2004/11/26 06:07:31  okane_shinji
  �@�\�ǉ�

  Revision 1.13  2004/08/09 02:55:56  okane_shinji
  �e�N�X�`�����[�h�֐��C��

  Revision 1.12  2004/08/09 02:17:42  okane_shinji
  SPL_LoadTex SPL_LoadTexPllt�p�~

  Revision 1.11  2004/08/09 02:13:33  konoh
  EXPERIMENT_VRAM_MANAGER�u�����`�̃}�[�W

  Revision 1.10.2.2  2004/08/05 05:57:18  okane_shinji
  ���C���B

  Revision 1.10.2.1  2004/08/05 05:15:57  okane_shinji
  VRAM�}�l�[�W���Ή��̎���

  Revision 1.10  2004/07/05 07:33:02  okane_shinji
  �|���S��ID���蓖�Ă��ςɁB�֐�����ύX�B

  Revision 1.9  2004/06/14 07:01:36  okane_shinji
  ��̃G�~�b�^�𕡐��̈ʒu�Ŏg�p�ł���悤�ɏC��

  Revision 1.8  2004/06/11 02:06:37  konoh
  ���s�v�Ȋ֐��̍폜

  Revision 1.7  2004/06/09 00:45:43  konoh
  (none)

  Revision 1.6  2004/06/07 00:19:53  konoh
  ��C++�Ή�

  Revision 1.5  2004/06/02 04:52:30  konoh
  (none)

  Revision 1.4  2004/05/25 08:51:08  konoh
  ���`��E�v�Z���[�`����ʂ���������ǉ�

  Revision 1.3  2004/05/24 09:44:09  konoh
  ���������m�ۂ̕��@�����[�U�R�[���o�b�N�ōs���悤�ɕύX

  Revision 1.2  2004/05/11 04:38:18  konoh
  (none)

  Revision 1.1.2.1  2004/04/15 07:24:17  konoh
  ���G�t�F�N�g�I���֌W�̂`�o�h�ǉ�

  Revision 1.1  2004/04/08 00:23:26  konoh
  (none)

 *---------------------------------------------------------------------------*/

#ifndef __SPL_H__
#define __SPL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "spl_manager.h"
#include "spl_emitter.h"

#define SPL_ALLOC_ERROR_TEX          (u32)0x0
#define SPL_ALLOC_ERROR_PLTT         (u32)0x0


/* �֐� -------------------------------------------------------------------- */

extern SPLManager* SPL_Init(SPLAlloc alloc, u16 max_emtr_num, u16 max_ptcl_num, u16 fix_polygonID, u16 min_polygonID, u16 max_polygonID );

extern void SPL_Load(SPLManager* p_mgr, const void* p_spa);

extern BOOL SPL_LoadTexByCallbackFunction( SPLManager* p_mgr, u32 (*callbackfunc)( u32 size, BOOL is4x4comp ) ) ;
extern BOOL SPL_LoadTexPlttByCallbackFunction( SPLManager* p_mgr, u32 (*callbackfunc)( u32 size, BOOL is4pltt ) ) ;

extern BOOL SPL_LoadTexByVRAMManager( SPLManager* p_mgr ) ;
extern BOOL SPL_LoadTexPlttByVRAMManager(  SPLManager* p_mgr ) ;



extern void SPL_Calc(SPLManager* p_mgr);
extern void SPL_Draw(SPLManager* p_mgr, const MtxFx43* p_cmr);

extern SPLEmitter* SPL_Create(SPLManager* p_mgr, int res_no, const VecFx32* p_pos);
extern SPLEmitter* SPL_CreateWithInitialize( SPLManager* p_mgr, int res_no, void ( *fp_callback )( struct SPLEmitter* ) ) ;
extern SPLEmitter* SPL_CreateWithInitializeEx( SPLManager* p_mgr, int res_no, const VecFx32*p_pos, void* p_void, void ( *fp_callback )( struct SPLEmitter*, void* ) ) ;


extern void SPL_Delete(SPLManager* p_mgr, SPLEmitter* p_emtr);
extern void SPL_DeleteAll(SPLManager* p_mgr);

extern void SPL_Emit(SPLManager* p_mgr, SPLEmitter* p_emtr) ;
extern void SPL_EmitAt( SPLManager* p_mgr, SPLEmitter* p_emtr, const VecFx32* p_pos ) ;

/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif
