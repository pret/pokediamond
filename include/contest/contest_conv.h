//==============================================================================
/**
 * @file	contest_conv.h
 * @brief	�R���e�X�g�Ŏg����f�[�^�ނ̍\���̒�`�Ȃ�
 * @author	matsuda
 * @date	2006.05.02(��)
 * 
 * elf2bin���g�p����c�\�[�X�����include����邽�߁A���܂�O���t�@�C����include��
 * ����K�v���Ȃ��悤�ɂ��Ă�������
 */
//==============================================================================
#ifndef __CONTEST_CONV_H__
#define __CONTEST_CONV_H__


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	�o��^�C�~���O
//--------------------------------------------------------------
enum{
	HOF_BOTH,			///<����
	HOF_BEFORE,			///<�a���O�ɓo��
	HOF_AFTER,			///<�a����ɓo��
	HOF_SPECIAL,		///<�K��1�l�o��

	//�폜�\��̒�`
	PALACE_BOTH = 0,			///<����
	PALACE_BEFORE,			///<�a���O�ɓo��
	PALACE_AFTER,			///<�a����ɓo��
};

///�u���[�_�[�̐��i
enum{
	BRD_CHARACTER_ELITE,		///<�G���[�g
	BRD_CHARACTER_JACKPOT,		///<�匊
	BRD_CHARACTER_SINCERE,		///<����
	BRD_CHARACTER_WEAK,			///<�ア
	
	BRD_CHARACTER_MAX,
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�R���e�X�g�Z�f�[�^
typedef struct{
	u8 ap_no;		///<�A�s�[��No
	u8 contype;		///<�R���e�X�g�Z�^�C�v(CONTYPE_STYLE��)
	
	u16 dummy;
}CONWAZA_DATA;

///�A�s�[���Z���ʃf�[�^
typedef struct{
	u16 setumei_u_id;	///<�Z��������i�̃��b�Z�[�WID
	u16 setumei_d_id;	///<�Z���������i�̃��b�Z�[�WID
	s8 ap_point;		///<�A�s�[���|�C���g(�}�C�i�X�̎��͖W�Q�l)
	
	u16 kouka_msgid_a;	///<�Z���ʃ��b�Z�[�WID�FA
	u8 kouka_msgtag_a;	///<�Z���ʃ��b�Z�[�WID:A�̃^�O
	u16 kouka_msgid_b;	///<�Z���ʃ��b�Z�[�WID�FB
	u8 kouka_msgtag_b;	///<�Z���ʃ��b�Z�[�WID:B�̃^�O
	u16 kouka_msgid_c;	///<�Z���ʃ��b�Z�[�WID�FC
	u8 kouka_msgtag_c;	///<�Z���ʃ��b�Z�[�WID:C�̃^�O
	u16 kouka_msgid_d;	///<�Z���ʃ��b�Z�[�WID�FD
	u8 kouka_msgtag_d;	///<�Z���ʃ��b�Z�[�WID:D�̃^�O

	u16 sp_msgid;		///<���ꃁ�b�Z�[�WID
	u8 sp_msgtag;		///<���ꃁ�b�Z�[�WID�̃^�O
}APWAZA_DATA;


///�u���[�_�[�f�[�^
typedef struct{
	u32	personal_rnd;					//������
	u32 id_no;							//�|�P������ID
	
	u16 obj_code;						///<�t�B�[���h��OBJ�R�[�h
	u16 trainer_type;					///<�g���[�i�[�^�C�v
	
	u16	waza[WAZA_TEMOTI_MAX];			///<�莝���Z�ԍ�

	u16 monsno;							///<�|�P�����ԍ�(�J��NO)
	u16 nickname_id;					///<�j�b�N�l�[�����b�Z�[�WID

	u16 name_id;						///<�u���[�_�[�����b�Z�[�WID
	u8 style;							//�������悳
	u8 beautiful;						//��������

	u8 cute;							//���킢��
	u8 clever;							//��������
	u8 strong;							//�����܂���
	u8 fur;								//�щ�
	
	u16 rank:3;							///<�Q���\�����N
	u16 part_style:1;					///<�i�D�悳�R���e�X�g�Q���\
	u16 part_beautiful:1;				///<�������R���e�X�g�Q���\
	u16 part_cute:1;					///<�����R���e�X�g�Q���\
	u16 part_clever:1;					///<�����R���e�X�g�Q���\
	u16 part_strong:1;					///<痂����R���e�X�g�Q���\
	u16 part_tutorial:1;				///<�`���[�g���A���Q���\
	u16 part_practice:1;				///<���K�Q���\
	u16 appear:2;						///<�o��^�C�~���O
	u16 sex:2;							///<����
	u16 character:2;					///<���i
	u8 clip_no_flowery;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�؂₩�Ȃ���)
	u8 clip_no_simple;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�V���v���Ȃ���)

	u8 clip_no_artificial;				///<�C���[�W�N���b�v�f�[�^�ԍ�(�l�H�̂���)
	u8 clip_no_natural;					///<�C���[�W�N���b�v�f�[�^�ԍ�(���R�̂���)
	u8 clip_no_colorful;				///<�C���[�W�N���b�v�f�[�^�ԍ�(�F���̂���)
	u8 clip_no_lively;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�ɂ��₩�Ȃ���)

	u8 clip_no_refresh;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�������肵������)
	u8 clip_no_limit;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�M���M���̂���)
	u8 clip_no_softly;					///<�C���[�W�N���b�v�f�[�^�ԍ�(���₩�Ȃ���)
	u8 clip_no_gorgeous;				///<�C���[�W�N���b�v�f�[�^�ԍ�(����т₩�̂���)

	u8 clip_no_elegant;					///<�C���[�W�N���b�v�f�[�^�ԍ�(��i�Ȃ���)
	u8 clip_no_showy;					///<�C���[�W�N���b�v�f�[�^�ԍ�(�h��Ȃ���)
	u8 popularity;						///<�l�C
	u8 version;							///<�u���[�_�[�f�[�^���쐬����ROM�̃o�[�W����

//	u8 dummy[2];			///<4�o�C�g���E�_�~�[
	
}BREEDER_DATA;


///�R���f�[�^
typedef struct{
	u16 name_id;					///<���OID
	u16 obj_code;					///<�t�B�[���h��OBJ�R�[�h
	
	u16 condition_style:2;			///<�]���R���f�B�V����(�i�D�悳)
	u16 condition_beautiful:2;		///<�]���R���f�B�V����(������)
	u16 condition_cute:2;			///<�]���R���f�B�V����(����)
	u16 condition_clever:2;			///<�]���R���f�B�V����(����)
	u16 condition_strong:2;			///<�]���R���f�B�V����(痂���)
	u16 rank:2;						///<�Q���\�����N
	u16 guest:1;					///<�Q�X�g�t���O(TRUE=�Q�X�g)
	u16 	:3;
	
	u16 dummy;			///<4�o�C�g���E�_�~�[
}JUDGE_DATA;


///�R���e�X�g�F�C���[�W�N���b�v�A�N�Z�T���f�[�^�\����
typedef struct{
	u8 no;			///<�A�N�Z�T���i���o�[
	u8 x;			///<X
	u8 y;			///<Y
	s8 pri;			///<�D�揇��
}CON_IMC_ACCE_DATA;

///�R���e�X�g�F�C���[�W�N���b�v�f�[�^�\����
typedef struct{
	CON_IMC_ACCE_DATA acce[CON_IMAGE_ACCE_MAX_MASTER];
	u8 acce_data_num;	//acce�ɓ����Ă���f�[�^��
	
	s8 mons_pri;
	s8 bg;

	u8 dummy;		///<4�o�C�g���E�I�t�Z�b�g
}CON_IMC_DATA;


#endif	//__CONTEST_CONV_H__

