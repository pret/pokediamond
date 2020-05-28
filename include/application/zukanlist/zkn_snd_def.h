//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_snd_def.h
 *	@brief		�}�Ӊ���`
 *	@author		tomoya takahashi
 *	@data		2006.02.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SND_DEF_H__
#define __ZKN_SND_DEF_H__

#include "include/system/snd_tool.h"

#undef GLOBAL
#ifdef	__ZKN_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_SND_SHUTTER				( SEQ_SE_DP_BUTTON01 )		// �V���b�^�[�J��

#define ZKN_SND_SELECT_MOVE_ONE		( SEQ_SE_DP_DENSI06 )		// �I���ړ�(����ʂɃ^�b�`���܂�)
#define ZKN_SND_SLIDE				( SEQ_SE_DP_DENSI06 )		// �X���C�h��

#define ZKN_SND_SEARCH				( SEQ_SE_DP_Z_SEARCH )		// ������

#define ZKN_SND_SWITCH				( SEQ_SE_DP_KATI )			// ������ʂ̃X�C�b�`
#define ZKN_SND_DIAL				( SEQ_SE_DP_KATI )			// �_�C�A����

#define ZKN_SND_SELECT				( SEQ_SE_DP_DECIDE )		// ���艹
#define ZKN_SND_CANCEL				( SEQ_SE_DP_DECIDE )		// �L�����Z��
#define ZKN_SND_BUTTON				( SEQ_SE_DP_DECIDE )		// �{�^���Ƀ^�b�`

#undef	GLOBAL
#endif		// __ZKN_SND_DEF_H__

