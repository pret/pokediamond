//============================================================================================
/**
 * @file	ribbon.h
 * @brief	���{���f�[�^�֘A
 * @author	Hiroyuki Nakamura
 * @date	2006.04.18
 */
//============================================================================================
#ifndef RIBBON_H
#define RIBBON_H
#undef GLOBAL
#ifdef RIBBON_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	�萔��`
//============================================================================================
#define	RIBBON_MAX		( 80 )			// ���{������
#define	MSG_SP_RIBBON	( 0x8000 )		// �z�z���{���̃��b�Z�[�W��`

// ���{���f�[�^�擾ID
enum {
	RIBBON_PARA_POKEPARA = 0,	// PokeParaGet�̎擾ID
	RIBBON_PARA_GRAPHIC,		// �O���t�B�b�NID
	RIBBON_PARA_PALNUM,			// �p���b�g�ԍ�
	RIBBON_PARA_NAME,			// ���{����
	RIBBON_PARA_INFO,			// ���{������
};


//���{��ID	�菑���Ȃ̂ŁA�K�v�Ȃ��̂�����`���Ă܂�
enum{
	RIBBON_ID_COOL = 33,			//�N�[�����{��
	RIBBON_ID_COOL_SUPER,			//�N�[�����{���X�[�p�[
	RIBBON_ID_COOL_HYPER,			//�N�[�����{���n�C�o�[
	RIBBON_ID_COOL_MASTER,			//�N�[�����{���}�X�^�[
	RIBBON_ID_BEAUTY,				//�r���[�e�B���{��
	RIBBON_ID_BEAUTY_SUPER,			//�r���[�e�B���{���X�[�p�[
	RIBBON_ID_BEAUTY_HYPER,			//�r���[�e�B���{���n�C�p�[
	RIBBON_ID_BEAUTY_MASTER,		//�r���[�e�B���{���}�X�^�[
	RIBBON_ID_CUTE,					//�L���[�g���{��
	RIBBON_ID_CUTE_SUPER,			//�L���[�g���{���X�[�p�[
	RIBBON_ID_CUTE_HYPER,			//�L���[�g���{���n�C�p�[
	RIBBON_ID_CUTE_MASTER,			//�L���[�g���{���}�X�^�[
	RIBBON_ID_GENEASU,				//�W�[�j�A�X���{��
	RIBBON_ID_GENEASU_SUPER,		//�W�[�j�A�X���{���X�[�p�[
	RIBBON_ID_GENEASU_HYPER,		//�W�[�j�A�X���{���n�C�p�[
	RIBBON_ID_GENEASU_MASTER,		//�W�[�j�A�X���{���}�X�^�[
	RIBBON_ID_PAWAFURU,				//�p���t�����{��
	RIBBON_ID_PAWAFURU_SUPER,		//�p���t�����{���X�[�p�[
	RIBBON_ID_PAWAFURU_HYPER,		//�p���t�����{���n�C�p�[
	RIBBON_ID_PAWAFURU_MASTER,		//�p���t�����{���}�X�^�[

	// AGB�Ŗ��z�z�̃��{��
	RIBBON_ID_MARINE = 25,			//�}�������{��
	RIBBON_ID_LAND,					//�����h���{��
	RIBBON_ID_SKY,					//�X�J�C���{��

	// DS�̔z�z���{��
	RIBBON_ID_SINOU_RED = 73,		//�V���I�E���b�h���{��
	RIBBON_ID_SINOU_GREEN,			//�V���I�E�O���[�����{��
	RIBBON_ID_SINOU_BLUE,			//�V���I�E�u���[���{��
	RIBBON_ID_SINOU_FESTIVAL,		//�V���I�E�t�F�X�e�B�o�����{��
	RIBBON_ID_SINOU_CARNIVAL,		//�V���I�E�J�[�j�o�����{��
	RIBBON_ID_SINOU_CLASSIC,		//�V���I�E�N���V�b�N���{��
	RIBBON_ID_SINOU_PREMIERE,		//�V���I�E�v���~�A���{��
};


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���{���f�[�^�擾
 *
 * @param	dat_id		�f�[�^�ԍ�
 * @param	prm_id		�擾�p�����[�^ID
 *
 * @return	�w��p�����[�^
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 RIBBON_DataGet( u8 dat_id, u8 prm_id );

//--------------------------------------------------------------------------------------------
/**
 * ���{�������擾
 *
 * @param	sv			�Z�[�u�f�[�^
 * @param	dat_id		�f�[�^�ԍ�
 *
 * @return	���{���������b�Z�[�W�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32	RIBBON_InfoGet( u8 * sv, u8 dat_id );

//--------------------------------------------------------------------------------------------
/**
 * ���{��ID����������i�[����Ă���ʒu���擾
 *
 * @param	dat_id		�f�[�^�ԍ�
 *
 * @retval	"0xff = �z�z���{���ȊO"
 * @retval	"0xff != �i�[�ʒu"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 RIBBON_SaveIndexGet( u8 dat_id );


#undef GLOBAL
#endif	/* RIBBON_H */
