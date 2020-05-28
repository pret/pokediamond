//==============================================================================
/**
 * @file	wp_tbl.h
 * @brief	�Z�G�t�F�N�g�p�[�e�B�N���f�[�^�e�[�u���̃w�b�_
 * @author	matsuda
 * @date	2005.07.22(��)
 */
//==============================================================================
#ifndef __WP_TBL_H__
#define __WP_TBL_H__

#include "include/system/arc_tool.h"

//==============================================================================
//	�\���̒�`
//==============================================================================
#if 0
typedef struct{
	const char *spa_path;	///<spa�t�@�C���ւ̃p�X
	pEmitFunc emit_func;	///<�G�~�b�^�������ɌĂяo���R�[���o�b�N�֐��ւ̃|�C���^
	u8 res_no;				///<���\�[�X�ԍ�
}WP_DATA;

extern const WP_DATA * Wp_DataPtrGet(int data_no);
extern void Wp_ParticleSet(PTC_PTR ptc, int data_no);
#endif


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PTC_PTR Wp_Init(int heap_id, int data_no, int tex_at_once);
extern PTC_PTR Wp_InitEx_CB(int heap_id, int arc_id, int data_no, int tex_at_once);
extern void * Particle_ArcResourceLoad_AH(ARCHANDLE* ah, int index, int heap_id);
extern PTC_PTR Wp_InitEx_CBAH(ARCHANDLE* ah, int heap_id, int data_no, int tex_at_once);
extern PTC_PTR Wp_InitEx(int heap_id, int arc_id, int data_no, int tex_at_once);
extern void Wp_Exit(PTC_PTR ptc);
extern EMIT_PTR Wp_EmitterCreate(PTC_PTR ptc, int resource_no, int func_num, void *temp_ptr);
extern EMIT_PTR Wp_EmitterCreateFunc(PTC_PTR ptc, int resource_no, pEmitFunc func, void *temp_ptr);



#endif	//__WP_TBL_H__

