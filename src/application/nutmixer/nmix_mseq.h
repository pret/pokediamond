/**
 *	@file	nmix_bag.c
 *	@brief	�i�b�c�~�L�T�[�@�؂̎��܎Q�� 
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#ifndef __H_NMIX_BAG_H__
#define __H_NMIX_BAG_H__

#undef GLOBAL
#ifdef	__H_NMIX_BAG_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

/**
 *	@brief	���C���R�}���h�@�؂̎��I���t���[
 */
GLOBAL int NMixMainSeq_Bag(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�R�[��
 */
GLOBAL int NMixMainSeq_GameCall(NUTMIXER_WORK* mp,int* seq);

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�I���҂�
 */
GLOBAL int NMixMainSeq_GameWait(NUTMIXER_WORK* mp,int *seq);

/**
 *	@brief	���C���R�}���h�@�Q�[�����C���v���Z�X�I������
 */
GLOBAL int NMixMainSeq_GameEnd(NUTMIXER_WORK* mp,int *seq);




#undef	GLOBAL
#endif	//__H_NMIX_BAG_H__
