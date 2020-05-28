//============================================================================================
/**
 *	������o�b�t�@�p�T�C�Y��`
 */
//============================================================================================
#ifndef __BUFLEN_H__
#define __BUFLEN_H__


//	������֘A�̒�����`
#define PERSON_NAME_SIZE	7	// �l���̖��O�̒����i�������܂ށj
#define	TR_NAME_SIZE		5	// �g���[�i�[�̖��O�̒���	// localspecmark (�_�~�[)
#define MONS_NAME_SIZE		10	// �|�P�������̒���(�o�b�t�@�T�C�Y EOM_�܂܂�)
#define MONS_DISP_SIZE		5	// �|�P�������̒���(�\���T�C�Y EOM_�܂܂�)
#define	WAZA_NAME_SIZE		7	// �킴���̒���
#define	ITEM_NAME_SIZE		8	// �ǂ������̒���
#define SEED_NAME_SIZE		6	// �^�l�̖��O�̒���
#define SPEABI_NAME_SIZE	7	// �������̒���		// localspecmark 
#define ZOKUSEI_NAME_SIZE	4	// �������̒���		// localspecmark 
#define MAPNAME_WIDTH		10  // �n��������̕\����	// mapname.c, townmap.h ����ړ�
#define MAPNAME_MAX			18  // �n��������̍ő咷	// mapname.c, townmap.h ����ړ�
#define TRTYPE_NAME_SIZE	10	// �g���[�i�[�^�C�v���̒���	// localspecmark murakawa
#define	GOODS_NAME_SIZE		10	// �O�b�Y���̒���
#define	ZUKAN_TYPE_SIZE		5	// �}�Ӄ^�C�v���̒���
#define	EOM_SIZE			1	// �I���R�[�h�̒���
#define	KAIWA_WORK_SIZE		7	// �ȈՉ�b�̂P�P��̍Œ��������iEOM_�܂܂��j
#define MONUMENT_NAME_SIZE	10	// �Δ�̖��O�̒���
#define	GROUP_NAME_SIZE		7	// �����_���O���[�v�̖��O�̒���


//-------------------------------------------------------------------------------
/**
 *  �����̒�`�́u�C�O�łł����ꂾ���m�ۂ���Ă���Ώ[���v�Ƃ����o�b�t�@���̒�`�ł��B
 *  �e�v�f�̕�������R�s�[����o�b�t�@�̍쐬�Ɏg�p���܂��B�]�T�������Ē�`���ĉ������B
 *  �Z�[�u�f�[�^�̂悤�ɁA�����ȍő咷���K�v�ȉӏ��ł͎g�p���Ȃ��ł��������B
 */
//-------------------------------------------------------------------------------

// �ꉞ�A�S�������ł��낦�Ă��܂�

#define BUFLEN_EOM_SIZE					(GLOBAL_MSGLEN)		// EOM�T�C�Y
#define BUFLEN_PERSON_NAME				(8)		// �l�����i�v���C���[�܂ށj�i�C�O�ł��V�����܂�+EOM�j
#define BUFLEN_POKEMON_NAME				(12)	// �|�P�������i�C�O�ł�10�����{EOM�j
#define BUFLEN_WAZA_NAME				(16)	// �Z���i���{��V�������C�O14�����z��{EOM�j
#define BUFLEN_ITEM_NAME				(18)	// �A�C�e�����i���{��W�������C�O16�����z��{EOM�j
#define BUFLEN_SEED_NAME				(14)	// �^�l���i���{��U�������C�O12�����z��{EOM�j
#define BUFLEN_POKEMON_ABILITY_NAME		(16)	// �|�P�����Ƃ��������i���{��V�������C�O14�����z��{EOM�j
#define BUFLEN_POKEMON_TYPE_NAME		(10)	// �|�P�����^�C�v���i���{��S�������C�O�W�����z��{EOM�j
#define BUFLEN_POKEMON_CHARACTER_NAME	(12)	// �|�P���������������i���{��T�������C�O10�����z��{EOM�j
#define BUFLEN_PLACE_NAME				(22)	// �n���i���{��10�������C�O20�����z�� +EOM�j
#define BUFLEN_TRAINER_TYPE_NAME		(22)	// �g���[�i�[�^�C�v���i���{��10�������C�O20�����z�� +EOM�j
#define BUFLEN_GOODS_NAME				(22)	// �O�b�Y���i���{��10�������C�O20�����z�� +EOM�j
#define BUFLEN_ZUKAN_TYPE_NAME			(12)	// �}�Ӄ^�C�v���i���{��T�������C�O10�����z��{EOM�j
#define BUFLEN_SEX						(2)		// ����(���� + EOM)
#define BUFLEN_ITEM_INFO				(114)	// �A�C�e�������i���{��57����(���s�E�I���R�[�h�܂�)���C�O114�����z��j
#define BUFLEN_WAZA_INFO				(110)	// �Z�����i���{��55����(���s�E�I���R�[�h�܂�)���C�O110�����z��j
#define BUFLEN_PMS_WORD					(32)	// �ȈՉ�b�P��i���{��͂V�����B�]�T�������Ă��ꂭ�炢�j
#define BUFLEN_PORUTO_NAME				(22)	// �|���g��(���{��10�������C�O20����+EOM_+�p�f�B���O1)

//==============================================================================
//==============================================================================
//==============================================================================


//--------------------------------------------------------------
//	�퓬���͉��	battle_input.c
//--------------------------------------------------------------
///�퓬���͉�ʁF�|�P�����I��(�Z����)�@�|�P�������{���ʁ@�����I�ɃX�y�[�X�����������ɔ����ė]����+5
#define BUFLEN_BI_POKESELENAME			(BUFLEN_POKEMON_NAME + BUFLEN_SEX + (5*GLOBAL_MSGLEN))
///�퓬���͉�ʁFPP + num + / + num
#define BUFLEN_BI_WAZAPP	((2 + 2 + 1 + 2) * GLOBAL_MSGLEN + BUFLEN_EOM_SIZE)
///�퓬���͉�ʁFPP���l(���{��2�����{EOM)
#define BUFLEN_BI_PP_NUM	(3*GLOBAL_MSGLEN)
///�퓬���͉�ʁF�u�Z���v���킷���I
#define BUFLEN_BI_WASURERU	(100)		//�K���ɑ傫��
///�퓬���͉�ʁF�u�Z���v���킷��Ȃ��I
#define BUFLEN_BI_WASURENAI	(100)
///�퓬���͉�ʁF�u���́@�|�P�������@�����v
#define BUFLEN_BI_NEXT_POKEMON	(100)
///�퓬���͉�ʁF�u�ɂ���v
#define BUFLEN_BI_NEXT_ESCAPE	(100)
///�퓬���͉�ʁF�u�|�P�������@���ꂩ����v
#define BUFLEN_BI_CHANGE_POKEMON	(100)
///�퓬���͉�ʁF�u���̂܂܁@���������v
#define BUFLEN_BI_CHANGE_NOT	(100)

//--------------------------------------------------------------
//	�퓬�Q�[�W
//--------------------------------------------------------------
///�퓬�Q�[�W�F�j�b�N�l�[���@�����I�ɃX�y�[�X�����������ɔ����ė]����+5
#define BUFLEN_GAUGE_POKESELENAME			(BUFLEN_POKEMON_NAME + (5*GLOBAL_MSGLEN))
///�퓬�Q�[�W�F�u�T�t�@���{�[���v
#define BUFLEN_GAUGE_SAFARIBALL				(30)	//�K���ɑ傫��
///�퓬�Q�[�W�F�u�̂���@�������v
#define BUFLEN_GAUGE_SAFARI_NOKORI			(30)	//�K���ɑ傫��



#endif
