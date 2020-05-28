//******************************************************************************
/**
 * 
 * @file	fieldobj_code.h
 * @brief	�t�B�[���hOBJ�Ŏg�p����V���{��,�R�[�h�錾 �A�Z���u���\�[�X�ǂݍ��݃A�� �̂�enum�֎~
 * @author	kagaya
 * @data	05.07.20
 */
//******************************************************************************
#ifndef FIELD_OBJ_CODE_H_FILE
#define FIELD_OBJ_CODE_H_FILE

//==============================================================================
///	����
//==============================================================================
#define DIR_NOT			(-1)								///<�������Ȃ��ꍇ
#define DIR_UP			(0)									///<�����
#define DIR_DOWN		(1)									///<������
#define DIR_LEFT		(2)									///<������
#define DIR_RIGHT		(3)									///<�E����

#define DIR_LEFTUP		(4)									///<�������
#define DIR_RIGHTUP		(5)									///<�E�����
#define DIR_LEFTDOWN	(6)									///<��������
#define DIR_RIGHTDOWN	(7)									///<�E������

#define DIR_4_MAX (DIR_LEFTUP)								///<4�����ő�

//==============================================================================
//	����ID
//==============================================================================
//--------------------------------------------------------------
//	�t�B�[���hOBJ ����ID
//--------------------------------------------------------------
#define FLDOBJ_ID_PLAYER (0xff)	///<���@��pID
#define FLDOBJ_ID_PAIR   (0xfe)	///<�A�������pID

//==============================================================================
//	�t�B�[���hOBJ ����R�[�h
//==============================================================================
//--------------------------------------------------------------
//	�t�B�[���hOBJ ����R�[�h
//--------------------------------------------------------------
#define MV_DMY			0x00		///<���얳��
#define MV_PLAYER		0x01		///<���@��p
#define MV_DIR_RND		0x02		///<�����_���ɕ����؂�ւ�
#define MV_RND			0x03		///<�����_���Ɉړ�
#define MV_RND_V		0x04		///<�����_���ɏc�ړ�
#define MV_RND_H		0x05		///<�����_���ɉ��ړ�
#define MV_RND_UL		0x06		///<�����_���ɏ㍶�����؂�ւ�
#define MV_RND_UR		0x07		///<�����_���ɏ�E�����؂�ւ�
#define MV_RND_DL		0x08		///<�����_���ɉ��������؂�ւ�
#define MV_RND_DR		0x09		///<�����_���ɉ��E�����؂�ւ�
#define MV_RND_UDL		0x0a		///<�����_���ɏ㉺�������؂�ւ�
#define MV_RND_UDR		0x0b		///<�����_���ɏ㉺�E�����؂�ւ�
#define MV_RND_ULR		0x0c		///<�����_���ɏ㍶�E�����؂�ւ�
#define MV_RND_DLR		0x0d		///<�����_���ɉ����E�����؂�ւ�
#define MV_UP			0x0e		///<��Œ�
#define MV_DOWN			0x0f		///<���Œ�
#define MV_LEFT			0x10		///<���Œ�
#define MV_RIGHT		0x11		///<�E�Œ�
#define MV_SPIN_L		0x12		///<����]
#define MV_SPIN_R		0x13		///<�E��]
#define MV_RT2			0x14		///<���[�g2
#define MV_RTURLD       0x15        ///<���[�g3 ��E����
#define MV_RTRLDU       0x16        ///<���[�g3 �E������
#define MV_RTDURL       0x17        ///<���[�g3 ����E��
#define MV_RTLDUR       0x18        ///<���[�g3 ������E
#define MV_RTULRD       0x19        ///<���[�g3 �㍶�E��
#define MV_RTLRDU       0x1a        ///<���[�g3 ���E����
#define MV_RTDULR       0x1b        ///<���[�g3 ���㍶�E
#define MV_RTRDUL       0x1c        ///<���[�g3 �E���㍶
#define MV_RTLUDR       0x1d        ///<���[�g3 ���㉺�E
#define MV_RTUDRL       0x1e        ///<���[�g3 �㉺�E��
#define MV_RTRLUD       0x1f        ///<���[�g3 �E���㉺
#define MV_RTDRLU       0x20        ///<���[�g3 ���E����
#define MV_RTRUDL       0x21        ///<���[�g3 �E�㉺��
#define MV_RTUDLR       0x22        ///<���[�g3 �㉺���E
#define MV_RTLRUD       0x23        ///<���[�g3 ���E�㉺
#define MV_RTDLRU       0x24        ///<���[�g3 �����E��
#define MV_RTUL         0x25        ///<���[�g4 �㍶
#define MV_RTDR         0x26        ///<���[�g4 ���E
#define MV_RTLD         0x27        ///<���[�g4 ����
#define MV_RTRU         0x28        ///<���[�g4 �E��
#define MV_RTUR         0x29        ///<���[�g4 ��E
#define MV_RTDL         0x2a        ///<���[�g4 ����
#define MV_RTLU         0x2b        ///<���[�g4 ����
#define MV_RTRD         0x2c        ///<���[�g4 �E��
#define MV_RND_UD		0x2d		///<�����_���ɏ㉺�؂�ւ�
#define MV_RND_LR		0x2e		///<�����_���ɍ��E�؂�ւ�
#define MV_SEED			0x2f		///<�؂̎�
#define MV_PAIR			0x30		///<�A�����
#define MV_REWAR		0x31		///<�Đ�
#define MV_TR_PAIR		0x32		///<�g���[�i�[�A�����
#define MV_HIDE_SNOW	0x33		///<�B�ꖪ�@��
#define MV_HIDE_SAND	0x34		///<�B�ꖪ�@��
#define MV_HIDE_GRND	0x35		///<�B�ꖪ�@�y
#define MV_HIDE_KUSA	0x36		///<�B�ꖪ�@��

#define MV_CODE_MAX		0x37		///<�R�[�h�ő�i�v���O���������p
#define MV_CODE_NOT		0xff		///<�񓮍�R�[�h(�v���O���������p

/*�@���Ή�
#define MV_COPYU	///<���̂܂ˏ�
#define MV_COPYD	///<���̂܂ˉ�
#define MV_COPYL	///<���̂܂ˉE
#define MV_COPYR	///<���̂܂ˍ�
#define MV_COPYGRASSD	///<���̂܂ˑ���
#define MV_COPYGRASSL	///<���̂܂ˑ���
#define MV_COPYGRASSR	///<���̂܂ˑ��E
#define MV_COPYGRASSU	///<���̂܂ˑ���
#define MV_HIDE_SKY			///<�B�ꖪ�@��
#define MV_HIDE_SWIM		///<�B�ꖪ�@�C
#define MV_HIDE_SNOWMAN		///<�B�ꖪ�@�Ⴞ���
#define MV_SLEEP	///<����@�_�b�V���ŋN����
#define MV_DIVE		///<�f����
*/

/*
 �T�u����őΉ��������
�@1:�Ƃ܂��Ă���낫��� ok
�@�@�����_���ړ�
�@�@���[�g�Q�C�R�C�S�@
�@2�F�Ƃ܂��Ă��邭�� ok
�@�@�����_���ړ�
�@�@���[�g�Q�C�R�C�S�@
	
�@3�F���邭��ړ� ok
�@�@�����_���ړ�
�@�@���[�g�Q�C�R�C�S�@
�@4�F������
�@�@���[�g�Q�C�R�C�S�@
�@5�F���j��
�@�@���[�g�Q?
 * */

//==============================================================================
//	�t�B�[���hOBJ �C�x���g�^�C�v
//==============================================================================
//--------------------------------------------------------------
//	�t�B�[���hOBJ �C�x���g�^�C�v
//--------------------------------------------------------------
#define EV_TYPE_NORMAL 				0x00	///<�ʏ�^�C�v
#define EV_TYPE_TRAINER				0x01	///<�g���[�i�[�^�C�v
#define EV_TYPE_TRAINER_EYEALL		0x02	///<�g���[�i�[�S���ʌ��m�^�C�v
#define EV_TYPE_ITEM				0x03	///<�A�C�e���^�C�v
#define EV_TYPE_TRAINER_KYORO		0x04	///<�g���[�i�[�^�C�v�@����낫���
#define EV_TYPE_TRAINER_SPIN_STOP_L	0x05	///<�g���[�i�[�^�C�v�@��~��]�@������
#define EV_TYPE_TRAINER_SPIN_STOP_R	0x06	///<�g���[�i�[�^�C�v�@��~��]�@�E���
#define EV_TYPE_TRAINER_SPIN_MOVE_L	0x07	///<�g���[�i�[�^�C�v�@�ړ���]�@������
#define EV_TYPE_TRAINER_SPIN_MOVE_R	0x08	///<�g���[�i�[�^�C�v�@�ړ���]�@�E���
#define EV_TYPE_MSG 				0x09	///<�ʏ�^�C�v ���b�Z�[�WID�w��

/*
#define EV_TYPE_TRAINER_ESCAPE		0x09	///<�g���[�i�[�^�C�v�@������
#define EV_TYPE_TRAINER_SWIM_H		0x0a	///<�g���[�i�[�^�C�v�@���j��
#define EV_TYPE_TRAINER_LIGHT			///<�g���[�i�[�^�C�v�@���C�g
#define EV_TYPE_TRAINER_LIGHT_DASH		///<�g���[�i�[�^�C�v�@���C�g�_�b�V��
*/

//==============================================================================
//	�t�B�[���hOBJ �`��X�e�[�^�X
//==============================================================================
//--------------------------------------------------------------
///	�t�B�[���hOBJ �`��X�e�[�^�X
//--------------------------------------------------------------
#define DRAW_STA_STOP		0x00		///<��~
#define DRAW_STA_WALK		0x01		///<�ړ�
#define DRAW_STA_WALK_32F	0x01		///<�ړ� 32�t���[��
#define DRAW_STA_WALK_16F	0x02		///<�ړ� 16�t���[��
#define DRAW_STA_WALK_8F	0x03		///<�ړ� 8�t���[��
#define DRAW_STA_WALK_4F	0x04		///<�ړ� 4�t���[��
#define DRAW_STA_WALK_2F	0x05		///<�ړ� 2�t���[��
#define DRAW_STA_WALK_6F	0x06		///<�ړ� 6�t���[��
#define DRAW_STA_WALK_3F	0x07		///<�ړ� 3�t���[��
#define DRAW_STA_WALK_7F	0x08		///<�ړ� 7�t���[��

#define DRAW_STA_MAX (DRAW_STA_WALK_7F+1)	///<�`��X�e�[�^�X�ő�

#define DRAW_STA_PC_BOW		0x09
#define DRAW_STA_PCWOMAN_MAX (DRAW_STA_PC_BOW+1)

//--------------------------------------------------------------
///	�t�B�[���hOBJ ���@��p�`��X�e�[�^�X
//--------------------------------------------------------------
#define DRAW_STA_DASH_4F		(DRAW_STA_MAX)					///<�ړ��@�_�b�V�� 4�t���[��
#define DRAW_STA_MAX_HERO		(DRAW_STA_DASH_4F+1)			///<�`��X�e�[�^�X�ő�@���@

#define DRAW_STA_TAKE_OFF_16F	(DRAW_STA_MAX+1)				///<���@�@�W�����v��
#define DRAW_STA_TAKE_OFF_8F	(DRAW_STA_MAX+2)				///<���@�@�W�����v��
#define DRAW_STA_MAX_CYCLEHERO	(DRAW_STA_TAKE_OFF_8F+1)		///<�`��X�e�[�^�X�ő�@���@

//--------------------------------------------------------------
///	�t�B�[���hOBJ ���@�ނ��p�`��X�e�[�^�X
//--------------------------------------------------------------
#define DRAW_STA_FISH_END	0x00
#define DRAW_STA_FISH_START	0x01
#define DRAW_STA_FISH_ON	0x02
#define DRAW_STA_FISH_HIT	0x03

#define DRAW_STA_MAX_FISH	(DRAW_STA_FISH_HIT+1)

//--------------------------------------------------------------
///	�t�B�[���hOBJ ���@���ΐ�p�`��X�e�[�^�X
//--------------------------------------------------------------
#define DRAW_STA_BANZAI 	0x00
#define DRAW_STA_BANZAI_UKE	0x01
#define DRAW_STA_MAX_BANZAI (DRAW_STA_BANZAI_UKE+1)

//==============================================================================
//	�t�B�[���hOBJ �A�j���[�V�����R�}���h�R�[�h
//==============================================================================
//--------------------------------------------------------------
//	�t�B�[���hOBJ �A�j���[�V�����R�}���h�R�[�h
//--------------------------------------------------------------
#define AC_DIR_U				0x00		///<��Ɍ���
#define AC_DIR_D				0x01		///<���Ɍ���
#define AC_DIR_L				0x02		///<���Ɍ���
#define AC_DIR_R				0x03		///<�E�Ɍ���
#define AC_WALK_U_32F			0x04		///<��Ɉړ��@32�t���[��
#define AC_WALK_D_32F			0x05		///<���Ɉړ��@32�t���[��
#define AC_WALK_L_32F			0x06		///<���Ɉړ��@32�t���[��
#define AC_WALK_R_32F			0x07		///<�E�Ɉړ��@32�t���[��
#define AC_WALK_U_16F			0x08		///<��Ɉړ��@16�t���[��
#define AC_WALK_D_16F			0x09		///<���Ɉړ��@16�t���[��
#define AC_WALK_L_16F			0x0a		///<���Ɉړ��@16�t���[��
#define AC_WALK_R_16F			0x0b		///<�E�Ɉړ��@16�t���[��
#define AC_WALK_U_8F			0x0c		///<��Ɉړ��@8�t���[��
#define AC_WALK_D_8F			0x0d		///<���Ɉړ��@8�t���[��
#define AC_WALK_L_8F			0x0e		///<���Ɉړ��@8�t���[��
#define AC_WALK_R_8F			0x0f		///<�E�Ɉړ��@8�t���[��
#define AC_WALK_U_4F			0x10		///<��Ɉړ��@4�t���[��
#define AC_WALK_D_4F			0x11		///<���Ɉړ��@4�t���[��
#define AC_WALK_L_4F			0x12		///<���Ɉړ��@4�t���[��
#define AC_WALK_R_4F			0x13		///<�E�Ɉړ��@4�t���[��
#define AC_WALK_U_2F			0x14		///<��Ɉړ��@2�t���[��
#define AC_WALK_D_2F			0x15		///<���Ɉړ��@2�t���[��
#define AC_WALK_L_2F			0x16		///<���Ɉړ��@2�t���[��
#define AC_WALK_R_2F			0x17		///<�E�Ɉړ��@2�t���[��
#define AC_STAY_WALK_U_32F		0x18		///<������ɂ��̏�����@32�t���[��
#define AC_STAY_WALK_D_32F		0x19		///<�������ɂ��̏�����@32�t���[��
#define AC_STAY_WALK_L_32F		0x1a		///<�������ɂ��̏�����@32�t���[��
#define AC_STAY_WALK_R_32F		0x1b		///<�E�����ɂ��̏�����@32�t���[��
#define AC_STAY_WALK_U_16F		0x1c		///<������ɂ��̏�����@16�t���[��
#define AC_STAY_WALK_D_16F		0x1d		///<�������ɂ��̏�����@16�t���[��
#define AC_STAY_WALK_L_16F		0x1e		///<�������ɂ��̏�����@16�t���[��
#define AC_STAY_WALK_R_16F		0x1f		///<�E�����ɂ��̏�����@16�t���[��
#define AC_STAY_WALK_U_8F		0x20		///<������ɂ��̏�����@8�t���[��
#define AC_STAY_WALK_D_8F		0x21		///<�������ɂ��̏�����@8�t���[��
#define AC_STAY_WALK_L_8F		0x22		///<�������ɂ��̏�����@8�t���[��
#define AC_STAY_WALK_R_8F		0x23		///<�E�����ɂ��̏�����@8�t���[��
#define AC_STAY_WALK_U_4F		0x24		///<������ɂ��̏�����@4�t���[��
#define AC_STAY_WALK_D_4F		0x25		///<�������ɂ��̏�����@4�t���[��
#define AC_STAY_WALK_L_4F		0x26		///<�������ɂ��̏�����@4�t���[��
#define AC_STAY_WALK_R_4F		0x27		///<�E�����ɂ��̏�����@4�t���[��
#define AC_STAY_WALK_U_2F		0x28		///<������ɂ��̏�����@2�t���[��
#define AC_STAY_WALK_D_2F		0x29		///<�������ɂ��̏�����@2�t���[��
#define AC_STAY_WALK_L_2F		0x2a		///<�������ɂ��̏�����@2�t���[��
#define AC_STAY_WALK_R_2F		0x2b		///<�E�����ɂ��̏�����@2�t���[��
#define AC_STAY_JUMP_U_16F		0x2c		///<������ɂ��̏�W�����v 16�t���[��
#define AC_STAY_JUMP_D_16F		0x2d		///<�������ɂ��̏�W�����v 16�t���[��
#define AC_STAY_JUMP_L_16F		0x2e		///<�������ɂ��̏�W�����v 16�t���[��
#define AC_STAY_JUMP_R_16F		0x2f		///<�E�����ɂ��̏�W�����v 16�t���[��
#define AC_STAY_JUMP_U_8F		0x30		///<������ɂ��̏�W�����v 8�t���[��
#define AC_STAY_JUMP_D_8F		0x31		///<�������ɂ��̏�W�����v 8�t���[��
#define AC_STAY_JUMP_L_8F		0x32		///<�������ɂ��̏�W�����v 8�t���[��
#define AC_STAY_JUMP_R_8F		0x33		///<�E�����ɂ��̏�W�����v 8�t���[��
#define AC_JUMP_U_1G_8F			0x34		///<������ɃW�����v 1�O���b�h 8�t���[��
#define AC_JUMP_D_1G_8F			0x35		///<�������ɃW�����v 1�O���b�h 8�t���[��
#define AC_JUMP_L_1G_8F			0x36		///<�������ɃW�����v 1�O���b�h 8�t���[��
#define AC_JUMP_R_1G_8F			0x37		///<�E�����ɃW�����v 1�O���b�h 8�t���[��
#define AC_JUMP_U_2G_16F		0x38		///<������ɃW�����v 2�O���b�h 16�t���[��
#define AC_JUMP_D_2G_16F		0x39		///<�������ɃW�����v 2�O���b�h 16�t���[��
#define AC_JUMP_L_2G_16F		0x3a		///<�������ɃW�����v 2�O���b�h 16�t���[��
#define AC_JUMP_R_2G_16F		0x3b		///<�E�����ɃW�����v 2�O���b�h 16�t���[��
#define AC_WAIT_1F				0x3c		///<1�t���[���҂�
#define AC_WAIT_2F				0x3d		///<2�t���[���҂�
#define AC_WAIT_4F				0x3e		///<4�t���[���҂�
#define AC_WAIT_8F				0x3f		///<8�t���[���҂�
#define AC_WAIT_15F				0x40		///<15�t���[���҂�
#define AC_WAIT_16F				0x41		///<16�t���[���҂�
#define AC_WAIT_32F				0x42		///<32�t���[���҂�
#define AC_WARP_UP				0x43		///<��Ƀ��[�v
#define AC_WARP_DOWN			0x44		///<���Ƀ��[�v
#define AC_VANISH_ON			0x45		///<��\���ɂ���
#define AC_VANISH_OFF			0x46		///<�\���ɂ���
#define AC_DIR_PAUSE_ON			0x47		///<�����Œ肷��
#define AC_DIR_PAUSE_OFF		0x48		///<�����Œ肵�Ȃ�
#define AC_ANM_PAUSE_ON			0x49		///<�A�j���|�[�Y
#define AC_ANM_PAUSE_OFF		0x4a		///<�A�j���|�[�Y������
#define AC_MARK_GYOE			0x4b		///<!�}�[�N���o��
#define AC_WALK_U_6F			0x4c		///<������Ɉړ��@6�t���[��
#define AC_WALK_D_6F			0x4d		///<�������Ɉړ��@6�t���[��
#define AC_WALK_L_6F			0x4e		///<�������Ɉړ��@6�t���[��
#define AC_WALK_R_6F			0x4f		///<�E�����Ɉړ��@6�t���[��
#define AC_WALK_U_3F			0x50		///<������Ɉړ��@3�t���[��
#define AC_WALK_D_3F			0x51		///<�������Ɉړ��@3�t���[��
#define AC_WALK_L_3F			0x52		///<�������Ɉړ��@3�t���[��
#define AC_WALK_R_3F			0x53		///<�E�����Ɉړ��@3�t���[��
#define AC_WALK_U_1F			0x54		///<������Ɉړ��@1�t���[��(�V�X�e�����Ή� �g�p�֎~
#define AC_WALK_D_1F			0x55		///<�������Ɉړ��@1�t���[��(�V�X�e�����Ή� �g�p�֎~
#define AC_WALK_L_1F			0x56		///<�������Ɉړ��@1�t���[��(�V�X�e�����Ή� �g�p�֎~
#define AC_WALK_R_1F			0x57		///<�E�����Ɉړ��@1�t���[��(�V�X�e�����Ή� �g�p�֎~
#define AC_DASH_U_4F			0x58		///<������Ɉړ��@4�t���[��(���@��p
#define AC_DASH_D_4F			0x59		///<�������Ɉړ��@4�t���[��(���@��p
#define AC_DASH_L_4F			0x5a		///<�������Ɉړ��@4�t���[��(���@��p
#define AC_DASH_R_4F			0x5b		///<�E�����Ɉړ��@4�t���[��(���@��p
#define AC_JUMPHI_L_1G_16F		0x5c	///<�������ɍ����W�����v 1�O���b�h 16�t���[��(���@��p
#define AC_JUMPHI_R_1G_16F		0x5d	///<�E�����ɍ����W�����v 1�O���b�h 16�t���[��(���@��p
#define AC_JUMPHI_L_3G_32F		0x5e	///<�������ɍ����W�����v 3�O���b�h 32�t���[��(���@��p
#define AC_JUMPHI_R_3G_32F		0x5f	///<�E�����ɍ����W�����v 3�O���b�h 32�t���[��(���@��p
#define AC_WALK_U_7F			0x60		///<������Ɉړ��@7�t���[��
#define AC_WALK_D_7F			0x61		///<�������Ɉړ��@7�t���[��
#define AC_WALK_L_7F			0x62		///<�������Ɉړ��@7�t���[��
#define AC_WALK_R_7F			0x63		///<�E�����Ɉړ��@7�t���[��
#define AC_PC_BOW				0x64		///<PC�����V(PCWOMAN1��p
#define AC_HIDE_PULLOFF			0x65		///<�B�ꖪ�E��(MV_HIDE��p
#define AC_HERO_BANZAI			0x66		///<PC���荷�o(���@��p
#define AC_MARK_SAISEN			0x67		///<�Đ�}�[�N�\��
#define AC_HERO_BANZAI_UKE		0x68		///<PC���荷�o�󂯎��(���@��p

#define ACMD_MAX				0x69		///<�A�j���[�V�����R�}���h�ő吔

#define ACMD_END				0xfe		///<�A�j���[�V�����R�}���h�I��
#define ACMD_NOT				0xff		///<��A�j���[�V�����R�}���h

//==============================================================================
//	�t�B�[���hOBJ �\���R�[�h
//==============================================================================
//--------------------------------------------------------------
//	�t�B�[���hOBJ �\���R�[�h
//--------------------------------------------------------------
#define HERO			0x0000		///<��l��
#define BABYBOY1		0x0001		///<�j�̎q
#define BABYGIRL1		0x0002		///<���̎q
#define BOY1			0x0003		///<���N
#define BOY2			0x0004		///<�������N
#define BOY3			0x0005		///<����班�N
#define GIRL1			0x0006		///<����
#define GIRL2			0x0007		///<��������
#define GIRL3			0x0008		///<����������
#define MAN1			0x0009		///<���Z����
#define MAN2			0x000a		///<�c�b�p�����Z����
#define MAN3			0x000b		///<�g���[�i�[���Z����
#define WOMAN1			0x000c		///<���o����
#define WOMAN2			0x000d		///<���������o����
#define WOMAN3			0x000e		///<�g���[�i�[���o����
#define MIDDLEMAN1		0x000f		///<��������
#define MIDDLEWOMAN1	0x0010		///<���΂���
#define OLDMAN1			0x0011		///<�a���ꂳ��
#define OLDWOMAN1		0x0012		///<�a���k����
#define BIGMAN			0x0013		///<���������Z����
#define MOUNT			0x0014		///<�R�j
#define CYCLEHERO		0x0015		///<��l�����]��
#define REPORTER		0x0016		///<
#define CAMERAMAN		0x0017		///<
#define SHOPM1			0x0018		///<
#define SHOPW1			0x0019		///<
#define PCWOMAN1		0x001a		///<
#define PCWOMAN2		0x001b		///<
#define PCWOMAN3		0x001c		///<
#define ASSISTANTM		0x001d		///<
#define ASSISTANTW		0x001e		///<
#define BADMAN			0x001f		///<
#define SKIERM			0x0020		///<
#define SKIERW			0x0021		///<
#define POLICEMAN		0x0022		///<
#define IDOL			0x0023		///<
#define GENTLEMAN		0x0024		///<
#define LADY			0x0025		///<
#define CYCLEM			0x0026		///<
#define CYCLEW			0x0027		///<
#define WORKMAN			0x0028		///<
#define FARMER			0x0029		///<
#define COWGIRL			0x002a		///<
#define CLOWN			0x002b		///<
#define ARTIST			0x002c		///<
#define SPORTSMAN		0x002d		///<
#define SWIMMERM		0x002e		///<
#define SWIMMERW		0x002f		///<
#define BEACHGIRL		0x0030		///<
#define BEACHBOY		0x0031		///<
#define EXPLORE			0x0032		///<
#define FIGHTER			0x0033		///<
#define CAMPBOY			0x0034		///<
#define PICNICGIRL		0x0035		///<
#define FISHING			0x0036		///<
#define AMBRELLA		0x0037		///<
#define SEAMAN			0x0038		///<
#define BRINGM			0x0039		///<
#define BRINGW			0x003a		///<
#define WAITER			0x003b		///<
#define WAITRESS		0x003c		///<
#define VETERAN			0x003d		///<
#define GORGGEOUSM		0x003e		///<
#define GORGGEOUSW		0x003f		///<
#define BOY4			0x0040		///<
#define GIRL4			0x0041		///<
#define MAN4			0x0042		///<
#define WOMAN4			0x0043		///<
#define MAN5			0x0044		///<
#define WOMAN5			0x0045		///<
#define MYSTERY			0x0046		///<
#define PIKACHU			0x0047		///<
#define PIPPI			0x0048		///<
#define PURIN			0x0049		///<
#define KODUCK			0x004a		///<
#define PRASLE			0x004b		///<
#define MINUN			0x004c		///<
#define MARIL			0x004d		///<
#define ACHAMO			0x004e		///<
#define ENECO			0x004f		///<
#define GONBE			0x0050		///<
#define BABY			0x0051		///<
#define MIDDLEMAN2		0x0052		///<
#define MIDDLEWOMAN2	0x0053		///<
#define ROCK			0x0054		///<
#define BREAKROCK		0x0055		///<
#define TREE			0x0056		///<
#define MONATERBALL		0x0057		///<
#define SHADOW			0x0058		///<
#define BOUGH			0x0059		///<
#define FALLTREE		0x005a		///<
#define BOARD_A			0x005b		///<�Ŕ�
#define BOARD_B			0x005c		///<�Ŕ�
#define BOARD_C			0x005d		///<�Ŕ�
#define BOARD_D			0x005e		///<�Ŕ�
#define BOARD_E			0x005f		///<�Ŕ�
#define BOARD_F			0x0060		///<�Ŕ�
#define HEROINE			0x0061		///<
#define CYCLEHEROINE	0x0062		///<
#define DOCTOR			0x0063
#define SEED			0x0064
#define WKOBJCODE00		0x0065
#define WKOBJCODE01		0x0066
#define WKOBJCODE02		0x0067
#define WKOBJCODE03		0x0068
#define WKOBJCODE04		0x0069
#define WKOBJCODE05		0x006a
#define WKOBJCODE06		0x006b
#define WKOBJCODE07		0x006c
#define WKOBJCODE08		0x006d
#define WKOBJCODE09		0x006e
#define WKOBJCODE10		0x006f
#define WKOBJCODE11		0x0071
#define WKOBJCODE12		0x0072
#define WKOBJCODE13		0x0073
#define WKOBJCODE14		0x0074
#define WKOBJCODE15		0x0075
#define SNOWBALL		0x0076
#define GINGABOSS		0x0078
#define GKANBU1			0x0079
#define GKANBU2			0x007a
#define GKANBU3			0x007b
#define GINGAM			0x007c
#define GINGAW			0x007d
#define LEADER1			0x007e
#define LEADER2			0x007f
#define LEADER3			0x0080
#define LEADER4			0x0081
#define LEADER5			0x0082
#define LEADER6			0x0083
#define LEADER7			0x0084
#define LEADER8			0x0085
#define BIGFOUR1		0x0086
#define BIGFOUR2		0x0087
#define BIGFOUR3		0x0088
#define BIGFOUR4		0x0089
#define CHAMPION		0x008a
#define PAPA			0x008b
#define MAMA			0x008c
#define SEVEN1			0x008d
#define SEVEN2			0x008e
#define SEVEN3			0x008f
#define SEVEN4			0x0090
#define SEVEN5			0x0091
#define SEVEN6			0x0092
#define SEVEN7			0x0093
#define RIVEL			0x0094
#define BOAT			0x0095
#define TRAIN			0x0096
#define SPPOKE1			0x0097
#define SPPOKE2			0x0098
#define SPPOKE3			0x0099
#define SPPOKE4			0x009a
#define SPPOKE5			0x009b
#define SPPOKE6			0x009c
#define SPPOKE7			0x009d
#define SPPOKE8			0x009e
#define SPPOKE9			0x009f
#define SPPOKE10		0x00a0
#define SPPOKE11		0x00a1
#define OBAKE			0x00a2
#define WOMAN6			0x00a3
#define OLDMAN2			0x00a4
#define OLDWOMAN2		0x00a5
#define OOKIDO			0x00a6
#define MIKAN			0x00a7
#define SUNGLASSES		0x00a8
#define TOWERBOSS		0x00a9
#define SNOWCOVER		0x00aa
#define TREECOVER		0x00ab
#define ROCKCOVER		0x00ac
#define BIRD			0x00ad
#define BAG				0x00ae
#define MAID			0x00af
#define SPHERO			0x00b0
#define SPHEROINE		0x00b1
#define	SWIMHERO		0x00b2
#define SWIMHEROINE		0x00b3
#define WATERHERO		0x00b4
#define WATERHEROINE	0x00b5
#define VENTHOLE		0x00b6
#define BOOK			0x00b7
#define SPPOKE12		0x00b8
#define BALLOON			0x00b9
#define CONTESTHERO		0x00ba
#define CONTESTHEROINE	0x00bb
#define FISHINGHERO		0x00bc
#define FISHINGHEROINE	0x00bd
#define MOSS			0x00be
#define FREEZES			0x00bf
#define POLE			0x00c0
#define DELIVERY		0x00c1
#define DSBOY			0x00c2
#define KOIKING			0x00c3
#define POKEHERO		0x00c4
#define POKEHEROINE		0x00c5
#define SAVEHERO		0x00c6
#define SAVEHEROINE		0x00c7
#define BANZAIHERO		0x00c8
#define BANZAIHEROINE	0x00c9
#define DOOR			0x00ca
#define MONUMENT		0x00cb
#define PATIRITUSU		0x00cc
#define KINOCOCO		0x00cd
#define MIMITUTO		0x00ce
#define KOLUCKY			0x00cf
#define WANRIKY			0x00d0
#define DOOR2			0x00d1

#define OBJCODEMAX		0xffff		///<OBJ�R�[�h�ő�

//--------------------------------------------------------------
///	���[�N�Q�ƌ^OBJ�R�[�h�@�`�F�b�N�V���{��
//--------------------------------------------------------------
#define WKOBJCODE_ORG	(WKOBJCODE00)
#define WKOBJCODE_END	(WKOBJCODE15)

//--------------------------------------------------------------
///	�؂̎���pOBJ�R�[�h�@�ʏ��OBJ�R�[�h�ɏd�Ȃ�Ȃ��l�A����
/// ���}�b�v�G�f�B�^�ł̔z�u�͋֎~
//--------------------------------------------------------------
#define SEEDCODEORG (0x1000)
#define SEED00				(SEEDCODEORG + 0x00)
#define SEED01A                (SEEDCODEORG + 0x01)
#define SEED01B                (SEEDCODEORG + 0x02)
#define SEED01C                (SEEDCODEORG + 0x03)
#define SEED02A                (SEEDCODEORG + 0x04)
#define SEED02B                (SEEDCODEORG + 0x05)
#define SEED02C                (SEEDCODEORG + 0x06)
#define SEED03A                (SEEDCODEORG + 0x07)
#define SEED03B                (SEEDCODEORG + 0x08)
#define SEED03C                (SEEDCODEORG + 0x09)
#define SEED04A                (SEEDCODEORG + 0x0a)
#define SEED04B                (SEEDCODEORG + 0x0b)
#define SEED04C                (SEEDCODEORG + 0x0c)
#define SEED05A                (SEEDCODEORG + 0x0d)
#define SEED05B                (SEEDCODEORG + 0x0e)
#define SEED05C                (SEEDCODEORG + 0x0f)
#define SEED06A                (SEEDCODEORG + 0x10)
#define SEED06B                (SEEDCODEORG + 0x11)
#define SEED06C                (SEEDCODEORG + 0x12)
#define SEED07A                (SEEDCODEORG + 0x13)
#define SEED07B                (SEEDCODEORG + 0x14)
#define SEED07C                (SEEDCODEORG + 0x15)
#define SEED08A                (SEEDCODEORG + 0x16)
#define SEED08B                (SEEDCODEORG + 0x17)
#define SEED08C                (SEEDCODEORG + 0x18)
#define SEED09A                (SEEDCODEORG + 0x19)
#define SEED09B                (SEEDCODEORG + 0x1a)
#define SEED09C                (SEEDCODEORG + 0x1b)
#define SEED10A                (SEEDCODEORG + 0x1c)
#define SEED10B                (SEEDCODEORG + 0x1d)
#define SEED10C                (SEEDCODEORG + 0x1e)
#define SEED11A                (SEEDCODEORG + 0x1f)
#define SEED11B                (SEEDCODEORG + 0x20)
#define SEED11C                (SEEDCODEORG + 0x21)
#define SEED12A                (SEEDCODEORG + 0x22)
#define SEED12B                (SEEDCODEORG + 0x23)
#define SEED12C                (SEEDCODEORG + 0x24)
#define SEED13A                (SEEDCODEORG + 0x25)
#define SEED13B                (SEEDCODEORG + 0x26)
#define SEED13C                (SEEDCODEORG + 0x27)
#define SEED14A                (SEEDCODEORG + 0x28)
#define SEED14B                (SEEDCODEORG + 0x29)
#define SEED14C                (SEEDCODEORG + 0x2a)
#define SEED15A                (SEEDCODEORG + 0x2b)
#define SEED15B                (SEEDCODEORG + 0x2c)
#define SEED15C                (SEEDCODEORG + 0x2d)
#define SEED16A                (SEEDCODEORG + 0x2e)
#define SEED16B                (SEEDCODEORG + 0x2f)
#define SEED16C                (SEEDCODEORG + 0x30)
#define SEED17A                (SEEDCODEORG + 0x31)
#define SEED17B                (SEEDCODEORG + 0x32)
#define SEED17C                (SEEDCODEORG + 0x33)
#define SEED18A                (SEEDCODEORG + 0x34)
#define SEED18B                (SEEDCODEORG + 0x35)
#define SEED18C                (SEEDCODEORG + 0x36)
#define SEED19A                (SEEDCODEORG + 0x37)
#define SEED19B                (SEEDCODEORG + 0x38)
#define SEED19C                (SEEDCODEORG + 0x39)
#define SEED20A                (SEEDCODEORG + 0x3a)
#define SEED20B                (SEEDCODEORG + 0x3b)
#define SEED20C                (SEEDCODEORG + 0x3c)
#define SEED21A                (SEEDCODEORG + 0x3d)
#define SEED21B                (SEEDCODEORG + 0x3e)
#define SEED21C                (SEEDCODEORG + 0x3f)
#define SEED22A                (SEEDCODEORG + 0x40)
#define SEED22B                (SEEDCODEORG + 0x41)
#define SEED22C                (SEEDCODEORG + 0x42)
#define SEED23A                (SEEDCODEORG + 0x43)
#define SEED23B                (SEEDCODEORG + 0x44)
#define SEED23C                (SEEDCODEORG + 0x45)
#define SEED24A                (SEEDCODEORG + 0x46)
#define SEED24B                (SEEDCODEORG + 0x47)
#define SEED24C                (SEEDCODEORG + 0x48)
#define SEED25A                (SEEDCODEORG + 0x49)
#define SEED25B                (SEEDCODEORG + 0x4a)
#define SEED25C                (SEEDCODEORG + 0x4b)
#define SEED26A                (SEEDCODEORG + 0x4c)
#define SEED26B                (SEEDCODEORG + 0x4d)
#define SEED26C                (SEEDCODEORG + 0x4e)
#define SEED27A                (SEEDCODEORG + 0x4f)
#define SEED27B                (SEEDCODEORG + 0x50)
#define SEED27C                (SEEDCODEORG + 0x51)
#define SEED28A                (SEEDCODEORG + 0x52)
#define SEED28B                (SEEDCODEORG + 0x53)
#define SEED28C                (SEEDCODEORG + 0x54)
#define SEED29A                (SEEDCODEORG + 0x55)
#define SEED29B                (SEEDCODEORG + 0x56)
#define SEED29C                (SEEDCODEORG + 0x57)
#define SEED30A                (SEEDCODEORG + 0x58)
#define SEED30B                (SEEDCODEORG + 0x59)
#define SEED30C                (SEEDCODEORG + 0x5a)
#define SEED31A                (SEEDCODEORG + 0x5b)
#define SEED31B                (SEEDCODEORG + 0x5c)
#define SEED31C                (SEEDCODEORG + 0x5d)
#define SEED32A                (SEEDCODEORG + 0x5e)
#define SEED32B                (SEEDCODEORG + 0x5f)
#define SEED32C                (SEEDCODEORG + 0x60)
#define SEED33A                (SEEDCODEORG + 0x61)
#define SEED33B                (SEEDCODEORG + 0x62)
#define SEED33C                (SEEDCODEORG + 0x63)
#define SEED34A                (SEEDCODEORG + 0x64)
#define SEED34B                (SEEDCODEORG + 0x65)
#define SEED34C                (SEEDCODEORG + 0x66)
#define SEED35A                (SEEDCODEORG + 0x67)
#define SEED35B                (SEEDCODEORG + 0x68)
#define SEED35C                (SEEDCODEORG + 0x69)
#define SEED36A                (SEEDCODEORG + 0x6a)
#define SEED36B                (SEEDCODEORG + 0x6b)
#define SEED36C                (SEEDCODEORG + 0x6c)
#define SEED37A                (SEEDCODEORG + 0x6d)
#define SEED37B                (SEEDCODEORG + 0x6e)
#define SEED37C                (SEEDCODEORG + 0x6f)
#define SEED38A                (SEEDCODEORG + 0x70)
#define SEED38B                (SEEDCODEORG + 0x71)
#define SEED38C                (SEEDCODEORG + 0x72)
#define SEED39A                (SEEDCODEORG + 0x73)
#define SEED39B                (SEEDCODEORG + 0x74)
#define SEED39C                (SEEDCODEORG + 0x75)
#define SEED40A                (SEEDCODEORG + 0x76)
#define SEED40B                (SEEDCODEORG + 0x77)
#define SEED40C                (SEEDCODEORG + 0x78)
#define SEED41A                (SEEDCODEORG + 0x79)
#define SEED41B                (SEEDCODEORG + 0x7a)
#define SEED41C                (SEEDCODEORG + 0x7b)
#define SEED42A                (SEEDCODEORG + 0x7c)
#define SEED42B                (SEEDCODEORG + 0x7d)
#define SEED42C                (SEEDCODEORG + 0x7e)
#define SEED43A                (SEEDCODEORG + 0x7f)
#define SEED43B                (SEEDCODEORG + 0x80)
#define SEED43C                (SEEDCODEORG + 0x81)
#define SEED44A                (SEEDCODEORG + 0x82)
#define SEED44B                (SEEDCODEORG + 0x83)
#define SEED44C                (SEEDCODEORG + 0x84)
#define SEED45A                (SEEDCODEORG + 0x85)
#define SEED45B                (SEEDCODEORG + 0x86)
#define SEED45C                (SEEDCODEORG + 0x87)
#define SEED46A                (SEEDCODEORG + 0x88)
#define SEED46B                (SEEDCODEORG + 0x89)
#define SEED46C                (SEEDCODEORG + 0x8a)
#define SEED47A                (SEEDCODEORG + 0x8b)
#define SEED47B                (SEEDCODEORG + 0x8c)
#define SEED47C                (SEEDCODEORG + 0x8d)
#define SEED48A                (SEEDCODEORG + 0x8e)
#define SEED48B                (SEEDCODEORG + 0x8f)
#define SEED48C                (SEEDCODEORG + 0x90)
#define SEED49A                (SEEDCODEORG + 0x91)
#define SEED49B                (SEEDCODEORG + 0x92)
#define SEED49C                (SEEDCODEORG + 0x93)
#define SEED50A                (SEEDCODEORG + 0x94)
#define SEED50B                (SEEDCODEORG + 0x95)
#define SEED50C                (SEEDCODEORG + 0x96)
#define SEED51A                (SEEDCODEORG + 0x97)
#define SEED51B                (SEEDCODEORG + 0x98)
#define SEED51C                (SEEDCODEORG + 0x99)
#define SEED52A                (SEEDCODEORG + 0x9a)
#define SEED52B                (SEEDCODEORG + 0x9b)
#define SEED52C                (SEEDCODEORG + 0x9c)
#define SEED53A                (SEEDCODEORG + 0x9d)
#define SEED53B                (SEEDCODEORG + 0x9e)
#define SEED53C                (SEEDCODEORG + 0x9f)
#define SEED54A                (SEEDCODEORG + 0xa0)
#define SEED54B                (SEEDCODEORG + 0xa1)
#define SEED54C                (SEEDCODEORG + 0xa2)
#define SEED55A                (SEEDCODEORG + 0xa3)
#define SEED55B                (SEEDCODEORG + 0xa4)
#define SEED55C                (SEEDCODEORG + 0xa5)
#define SEED56A                (SEEDCODEORG + 0xa6)
#define SEED56B                (SEEDCODEORG + 0xa7)
#define SEED56C                (SEEDCODEORG + 0xa8)
#define SEED57A                (SEEDCODEORG + 0xa9)
#define SEED57B                (SEEDCODEORG + 0xaa)
#define SEED57C                (SEEDCODEORG + 0xab)
#define SEED58A                (SEEDCODEORG + 0xac)
#define SEED58B                (SEEDCODEORG + 0xad)
#define SEED58C                (SEEDCODEORG + 0xae)
#define SEED59A                (SEEDCODEORG + 0xaf)
#define SEED59B                (SEEDCODEORG + 0xb0)
#define SEED59C                (SEEDCODEORG + 0xb1)
#define SEED60A                (SEEDCODEORG + 0xb2)
#define SEED60B                (SEEDCODEORG + 0xb3)
#define SEED60C                (SEEDCODEORG + 0xb4)
#define SEED61A                (SEEDCODEORG + 0xb5)
#define SEED61B                (SEEDCODEORG + 0xb6)
#define SEED61C                (SEEDCODEORG + 0xb7)
#define SEED62A                (SEEDCODEORG + 0xb8)
#define SEED62B                (SEEDCODEORG + 0xb9)
#define SEED62C                (SEEDCODEORG + 0xba)
#define SEED63A                (SEEDCODEORG + 0xbb)
#define SEED63B                (SEEDCODEORG + 0xbc)
#define SEED63C                (SEEDCODEORG + 0xbd)
#define SEED64A                (SEEDCODEORG + 0xbe)
#define SEED64B                (SEEDCODEORG + 0xbf)
#define SEED64C                (SEEDCODEORG + 0xc0)

//--------------------------------------------------------------
///	����OBJ�R�[�h
/// ���}�b�v�G�f�B�^�ł̔z�u�͋֎~
//--------------------------------------------------------------
#define NONDRAW			(0x2000)

//==============================================================================
//	�t�B�[���hOBJ ���f��ID
//==============================================================================
//--------------------------------------------------------------
//	���f��ID
//--------------------------------------------------------------
#define BLACT_MDLID_32x32		0x0000		///<32x32
#define BLACT_MDLID_16x16		0x0001		///<16x16
#define BLACT_MDLID_16x16_1		0x0002		///<16x16
#define BLACT_MDLID_SEED_ME		0x0003		///<�؂̎��@��
#define BLACT_MDLID_SEED		0x0004		///<�؂̎�
#define BLACT_MDLID_64x64		0x0005		///<64x64
#define BLACT_MDLID_FISHINGHERO	0x0006		///<�ނ莩�@
#define BLACT_MDLID_16x32		0x0007		///<16x32
#define BLACT_MDLID_64x32		0x0008		///<64x32

#define BLACT_MDLID_MAX			0xffff		///<���f��ID�ő�

//==============================================================================
//	�t�B�[���hOBJ �A�j��ID
//==============================================================================
//--------------------------------------------------------------
//	�A�j��ID
//--------------------------------------------------------------
#define BLACT_ANMID_NORMAL_0	0x0000		///<�m�[�}���A�j��
#define BLACT_ANMID_HERO_0		0x0001		///<���@�p�A�j��
#define BLACT_ANMID_SEED		0x0002		///<�؂̎��A�j��
#define BLACT_ANMID_HEROCYCLE_0	0x0003		///<���@���]�ԃA�j��
#define BLACT_ANMID_SPHERO		0x0004
#define BLACT_ANMID_WATERHERO	0x0005
#define BLACT_ANMID_SWIMHERO	0x0006
#define BLACT_ANMID_BIRD		0x0007
#define BLACT_ANMID_SPPOKE		0x0008
#define BLACT_ANMID_CONTESTHERO	0x0009
#define BLACT_ANMID_FISHINGHERO	0x000a
#define BLACT_ANMID_PCWOMAN		0x000b
#define BLACT_ANMID_KOIKING		0x000c
#define BLACT_ANMID_POKEHERO	0x000d
#define BLACT_ANMID_SAVEHERO	0x000e
#define BLACT_ANMID_BANZAIHERO	0x000f
#define BLACT_ANMID_SPPOKE6		0x0010
#define BLACT_ANMID_SPPOKE7		0x0011
#define BLACT_ANMID_SPPOKE9		0x0012
#define BLACT_ANMID_SPPOKE10	0x0013
#define BLACT_ANMID_SPPOKE11	0x0014

#define BLACT_ANMID_MAX			0xffff		///<�A�j��ID�ő�

#endif //FIELD_OBJ_CODE_H_FILE
