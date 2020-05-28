/**
 *	@file	fld_ranking.h
 *	@brief	�t�B�[���h�@�����L���O��ʕ`�揈��
 *	@author	Miyuki Iwasawa
 *	@date	06.06.06
 */

#ifndef __H_FLD_RANKING_H__
#define __H_FLD_RANKING_H__

///�Ăяo�����[�h�ݒ�
#define RANKING_GLB_BTL		(0)	///<�O���[�o���o�g��
#define RANKING_GLB_POKE	(1)	///<�O���[�o���|�P����
#define RANKING_GLB_CONTEST	(2)	///<�O���[�o���R���e�X�g
#define RANKING_GRP_BTL		(3)	///<�O���[�v�o�g��
#define RANKING_GRP_POKE	(4)	///<�O���[�v�|�P����
#define RANKING_GRP_CONTEST	(5)	///<�O���[�v�R���e�X�g



//============================================================================================
//
//	�������牺�̓v���O�����ł̂ݎQ�Ƃ����`
//
//======================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#undef	GLOBAL
#ifdef __FLD_RANKING_H_GLOBAL
#define GLOBAL /***/
#else
#define GLOBAL extern	
#endif

//--------------------------------------------------------------
/**
 * @brief	�����L���O��ʃT�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		�ړ�����
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
GLOBAL void EventCmd_RankingViewCall( GMEVENT_CONTROL *event,u16 mode);



#endif	//__ASM_NO_DEF_

#endif	//__H_FLD_RANKING_H__

