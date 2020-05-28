extern void agbpoke_codeConv(u8 *src, u16 *dest, int length);

extern u32 agbpoke_GetTrainerID(void);
extern u8 *agbpoke_GetTrainerName(void);

//=========================================================================
//	
// �v���C���[�V�X�e���f�[�^
//
//=========================================================================
#define AGB_PERSON_NAME_SIZE	7
#define AGB_EOM_SIZE		1

typedef struct PersonalData{
		u8 my_name[AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE];	//	�����̖��O
		u8 my_sex;					//	�����̐���
		u8 save_flag;				//	�Z�[�u�������ǂ����̃t���O
		u8 ID[4];					//	�h�c�i���o�[

		u16 playtime_h;				//	�v���C���ԁi���j
		u8 playtime_m;				//	�v���C���ԁi���j
		u8 playtime_s;				//	�v���C���ԁi�b�j
		u8 playtime_ms;				//	�v���C���ԁi1/60�b�j

		u8 key_config;				//	�I�v�V�����̃L�[�ݒ�
		u16 msg_speed:3;			//	�l�r�f����̑���
		u16 window_type:5;			//	�V�X�e���E�B���h�E�̎��
		u16 sound_mode:1;			//	�X�e���I�E���m�����؂�ւ�
		u16 btl_type:1;				//	�u�����ʂ��v�u���ꂩ���v
		u16 btl_eff_sw:1;			//	�퓬�G�t�F�N�g�̗L��
		u16 tnavi_zoom:1;			//	�g���i�r�}�b�v���[�h

  // ����ȍ~�͓���ȍ\���̂��K�v�A�܂��͌݊������ێ�����Ă��Ȃ����ڂȂ̂ŃJ�b�g
}SYS_SAVE_DATA;

/*  */
