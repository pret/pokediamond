//============================================================================================
/**
 * @file	scr_offset.h
 * @bfief	�X�N���v�gID�̃I�t�Z�b�g��`
 * @author	Satoshi Nohara
 * @date	06.05.26
 */
//============================================================================================
#ifndef SCR_OFFSET_H
#define SCR_OFFSET_H


//============================================================================================
//
//	�X�N���v�gID�I�t�Z�b�g
//
//	��`�ǉ����[��
//	#define ID_"�X�N���v�g�t�@�C����"_OFFSET
//	#define ID_"�X�N���v�g�t�@�C����"_OFFSET_END
//
//	script.c�̓ǂݍ��ރX�N���v�g�t�@�C���A���b�Z�[�W�t�@�C����Ή������ĉ������B
//
//============================================================================================
//#define	SCRID_NULL					(0)			//�_�~�[�X�N���v�gID
#define	ID_START_SCR_OFFSET				(1)			//�J�n�X�N���v�gID�̃I�t�Z�b�g
#define	ID_COMMON_SCR_OFFSET			(2000)		//���ʃX�N���v�gID�̃I�t�Z�b�g
#define	ID_COMMON_SCR_OFFSET_END		(2499)		//���ʃX�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_BG_ATTR_OFFSET				(2500)		//BG�X�N���v�gID�̃I�t�Z�b�g
#define	ID_BG_ATTR_OFFSET_END			(2799)		//BG�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_KINOMI_OFFSET				(2800)		//���̂݃X�N���v�gID�̃I�t�Z�b�g
#define	ID_KINOMI_OFFSET_END			(2999)		//���̂݃X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_TRAINER_OFFSET				(3000)		//�g���[�i�[�X�N���v�gID�̃I�t�Z�b�g
#define	ID_TRAINER_OFFSET_END			(4999)		//�g���[�i�[�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_TRAINER_2VS2_OFFSET			(5000)		//2vs2�g���[�i�[�X�N���v�gID�̃I�t�Z�b�g
#define	ID_TRAINER_2VS2_OFFSET_END		(6999)		//2vs2�g���[�i�[�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_FLD_ITEM_OFFSET				(7000)		//�t�B�[���h�A�C�e���X�N���v�gID�̃I�t�Z�b�g
#define	ID_HIDE_ITEM_OFFSET				(8000)		//�B���A�C�e���X�N���v�gID�̃I�t�Z�b�g
#define	ID_HIDE_ITEM_OFFSET_END			(8799)		//�B���A�C�e���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_SAFARI_OFFSET				(8800)		//�T�t�@���X�N���v�gID�̃I�t�Z�b�g
#define	ID_SAFARI_OFFSET_END			(8899)		//�T�t�@���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_PERAP_OFFSET					(8900)		//�y���b�v�X�N���v�gID�̃I�t�Z�b�g
#define	ID_PERAP_OFFSET_END				(8949)		//�y���b�v�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_SAISEN_OFFSET				(8950)		//�Đ�X�N���v�gID�̃I�t�Z�b�g
#define	ID_SAISEN_OFFSET_END			(8969)		//�Đ�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_POKESEARCHER_OFFSET			(8970)		//�|�P�T�[�`���[�X�N���v�gID�̃I�t�Z�b�g
#define	ID_POKESEARCHER_OFFSET_END		(8999)		//�|�P�T�[�`���[�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_CONNECT_OFFSET				(9000)		//�ʐM�X�N���v�gID�̃I�t�Z�b�g
#define	ID_CONNECT_OFFSET_END			(9099)		//�ʐM�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_BATTLE_ROOM_OFFSET			(9100)		//�R���V�A���X�N���v�gID�̃I�t�Z�b�g
#define	ID_BATTLE_ROOM_OFFSET_END		(9199)		//�R���V�A���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_PC_UG_OFFSET					(9200)		//�|�P�Z���n���X�N���v�gID�̃I�t�Z�b�g
#define	ID_PC_UG_OFFSET_END				(9299)		//�|�P�Z���n���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_GROUP_OFFSET					(9300)		//�O���[�v�X�N���v�gID�̃I�t�Z�b�g
#define	ID_GROUP_OFFSET_END				(9399)		//�O���[�v�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_PORUTO_SCR_OFFSET			(9400)		//�|���g�~�j�Q�[���X�N���v�gID�̃I�t�Z�b�g
#define	ID_PORUTO_SCR_OFFSET_END		(9499)		//�|���g�~�j�Q�[���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_SODATEYA_OFFSET				(9500)		//��ĉ��X�N���v�gID�̃I�t�Z�b�g
#define	ID_SODATEYA_OFFSET_END			(9599)		//��ĉ��X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_INIT_SCR_OFFSET				(9600)		//�Q�[���J�n�X�N���v�gID�̃I�t�Z�b�g
#define	ID_INIT_SCR_OFFSET_END			(9699)		//�Q�[���J�n�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_PAIR_SCR_OFFSET				(9700)		//�A������X�N���v�gID�̃I�t�Z�b�g
#define	ID_PAIR_SCR_OFFSET_END			(9799)		//�A������X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_CON_RECEPTION_OFFSET			(9800)		//�R���e�X�g��t�X�N���v�gID�̃I�t�Z�b�g
#define	ID_CON_RECEPTION_OFFSET_END		(9899)		//�R���e�X�g��t�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_DEBUG_SCR_OFFSET				(9900)		//�f�o�b�N�X�N���v�gID�̃I�t�Z�b�g
#define	ID_DEBUG_SCR_OFFSET_END			(9949)		//�f�o�b�N�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_HYOUKA_SCR_OFFSET			(9950)		//�]���X�N���v�gID�̃I�t�Z�b�g
#define	ID_HYOUKA_SCR_OFFSET_END		(9999)		//�]���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_HIDEN_OFFSET					(10000)		//��`�X�N���v�gID�̃I�t�Z�b�g
#define	ID_HIDEN_OFFSET_END				(10099)		//��`�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_TV_OFFSET					(10100)		//TV�X�N���v�gID�̃I�t�Z�b�g
#define	ID_TV_OFFSET_END				(10149)		//TV�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_TV_INTERVIEW_OFFSET			(10150)		//TV�C���^�r���[�X�N���v�gID�̃I�t�Z�b�g
#define	ID_TV_INTERVIEW_OFFSET_END		(10199)		//TV�C���^�r���[�X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_HAITATU_OFFSET				(10200)		//�z�B���X�N���v�gID�̃I�t�Z�b�g
#define	ID_HAITATU_OFFSET_END			(10299)		//�z�B���X�N���v�gID�̃I�t�Z�b�g�I��
#define	ID_SUPPORT_OFFSET				(10300)		//�T�|�[�g�X�N���v�gID�̃I�t�Z�b�g
#define	ID_SUPPORT_OFFSET_END			(10399)		//�T�|�[�g�X�N���v�gID�̃I�t�Z�b�g�I��


#endif	/* SCR_OFFSET_H */


