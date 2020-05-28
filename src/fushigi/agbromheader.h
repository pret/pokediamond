typedef struct {
	u8	person_name_size;	// �l���̖��O�̒����i�������܂ށj
	u8	tr_name_size;		// �g���[�i�[�̖��O�̒���
	u8	mons_name_size;		// �|�P�������̒���(�o�b�t�@�T�C�Y EOM_�܂܂�)
	u8	mons_disp_size;		// �|�P�������̒���(�\���T�C�Y EOM_�܂܂�)
	u8	waza_name_size;		// �킴���̒���
	u8	item_name_size;		// �ǂ������̒���
	u8	seed_name_size;		// �^�l�̖��O�̒���
	u8	speabi_name_size;	// �������̒���
	u8	zokusei_name_size;	// �������̒���
	u8	map_name_width;		// �n��������̕\����
	u8	mapname_max;		// �n��������̍ő咷
	u8	trtype_name_size;	// �g���[�i�[�^�C�v���̒���
	u8	goods_name_size;	// �O�b�Y���̒���
	u8	zukan_type_size;	// �}�Ӄ^�C�v���̒���
	u8	eom_size;			// �I���R�[�h�̒���
	u8	btl_tr_name_size;	// �o�g���^���[�E�g���[�i�[�̖��O�̒���
	u8	kaiwa_work_size;	// �ȈՉ�b�̂P�P��̍Œ��������iEOM_�܂܂��j
}POKE_DATALEN;

typedef struct {
	u8	normal_max;	// �ʏ�A�C�e���ۑ���
	u8	extra_max;	// �厖�A�C�e���ۑ���
	u8	ball_max;	// �{�[���A�C�e���ۑ���
	u8	skill_max;	// �Z�}�V���A�C�e���ۑ���
	u8	seed_max;	// ��A�C�e���ۑ���
	u8	pc_max;		// �o�b�A�C�e���ۑ���
}POKE_ITEMMAX;

typedef struct {
	u32	membox:1;	// �������[�{�b�N�X�g�p�\�t���O
	u32	coliseum:1;	// �|�P�����R���V�A���g�p�\�t���O
	u32	dummy:30;	// �\��
}POKESOFT_ENABLE;

typedef struct {
	///�J�Z�b�g�o�[�W����
	u32	pm_version;
	///����o�[�W����
	u32 pm_lang;

	///�Q�[���^�C�g����
	u8 rom_name[32];

	///�|�P�������ʉ摜�f�[�^�A�h���X�e�[�u��
	const void * front_cell;
	///�|�P�����w�ʉ摜�f�[�^�A�h���X�e�[�u��
	const void * back_cell;
	///�|�P�����m�[�}���J���[�f�[�^�A�h���X�e�[�u��
	const void * normal_pal;
	///�|�P�������A�J���[�f�[�^�A�h���X�e�[�u��
	const void * rare_pal;

	///�A�C�R���摜�f�[�^�A�h���X�e�[�u��
	u8* const	* icon_char;
	///�A�C�R���A�g���r���[�g�f�[�^�A�h���X�e�[�u��
	const u8 * icon_attr;
	///�|�P�����A�C�R���p���b�g�f�[�^
	const void * icon_pal;

	///�|�P�������O�f�[�^�e�[�u��
	const void *mons_name;
	///�킴���f�[�^�e�[�u��
	const void *waza_name;
	///�O�b�Y�f�[�^�e�[�u��
	const void * goods;

	///�Z�[�u�f�[�^(fld)�F�C�x���g�t���O�I�t�Z�b�g
	u32	event_flag_offset;
	///�Z�[�u�f�[�^(fld)�F�C�x���g���[�N�I�t�Z�b�g
	u32 event_work_offset;
	///�Z�[�u�f�[�^(MyData)�F�}�Ӄu���b�N�I�t�Z�b�g
	u32 zukan_work_offset;
	///�Z�[�u�f�[�^(fld):�}�Ӄf�[�^�I�t�Z�b�g�i�������t���O���̂Q�j
	u32 zukan_flag2_offset;
	///�Z�[�u�f�[�^(fld):�}�Ӄf�[�^�I�t�Z�b�g�i�������t���O���̂R�j
	u32 zukan_flag3_offset;

	///�}�ӑS�����[�h���[�N�i���o�[
	u32 zenkoku_work_no;
	///�}�ӑS�����[�h�t���O�i���o�[
	u32 zenkoku_flag_no;
	///�u�ӂ����Ȃł����Ɓv�t���O�i���o�[
	u32 husigi_flag_no;

	///�|�P�����ő吔
	u32 poke_cnt_max;

	//�f�[�^���ݒ�֘A
	POKE_DATALEN	pm_datalen;

	///�Z�[�u�f�[�^�FMyData�@�f�[�^�T�C�Y
	u32	MyData_size;
	///�Z�[�u�f�[�^�Ffld�@�f�[�^�T�C�Y
	u32	Fld_size;

	///�Z�[�u�f�[�^�F�|�P�����莝����
	u32 temoti_cnt;
	///�Z�[�u�f�[�^�F�|�P�����莝���f�[�^
	u32 temoti_dat;

	///�Z�[�u�f�[�^�F�Z�[�u��Ԕ���
	u32 pokecen_flg;
	///�Z�[�u�f�[�^�F�����̂h�c
	u32 my_id;

	///�Z�[�u�f�[�^�F�����̖��O
	u32 my_name;
	///�Z�[�u�f�[�^�F�����̐���
	u32 my_sex;

	///�Z�[�u�f�[�^�F�o�g���^���[�k�u�T�O���[�h�̃X�e�[�^�X
	u32 b_tower_stat50;
	///�Z�[�u�f�[�^�F�o�g���^���[�k�u�P�O�O���[�h�̃X�e�[�^�X
	u32 b_tower_stat100;

	///�Z�[�u�f�[�^(Fld)�F�g���C�x���g�t���O�I�t�Z�b�g
	u32	ex_event_flag_offset;
	///�Z�[�u�f�[�^(Fld)�F�g���C�x���g���[�N�I�t�Z�b�g
	u32 ex_event_work_offset;

	///�O���A���\�t�g�g�p�۔���t���O
	POKESOFT_ENABLE	expand_soft_disable_flag;

	///�|�P�����p�[�\�i���f�[�^�e�[�u��
	const void*	PokemonData;
	///�������f�[�^�e�[�u��
	const void * special_ability_msg;
	///���������f�[�^�e�[�u��
	const void * special_ability_info_msg;
	///�A�C�e���f�[�^�e�[�u��
	const void* item_data;

	///�Z�f�[�^�e�[�u��
	const void* waza_data;

	///�����X�^�[�{�[���摜�f�[�^�A�h���X�e�[�u��
	const void * monsterball_cell_tbl;
	///�����X�^�[�{�[���p���b�g�f�[�^�A�h���X�e�[�u��
	const void * monsterball_pal_tbl;

	///�|�P������������t���O
	u32		pokemon_trade_flag;				//�|�P��������Enable�t���O

	///�Q�[���N���A�t���O�i���o�[
	u32		game_clr_flag_no;

	///���{���擾���t���O�i���o�[
	u32		ribbon_enable_flag_no;

	///�A�C�e���ۑ��ő吔
	POKE_ITEMMAX	item_max_cnt;

	///�p�\�R���ۑ��A�C�e���f�[�^�\����
	u32		pc_item;

	///���{���ƃ��b�Z�[�W�̊֘A�Â��e�[�u��
	u32			ribbon_no;

	///�q�`�l�؂̎����[�N
	u32		ram_seed_data;

	///�q�`�l�؂̎����[�N�T�C�Y
	u32		ram_seed_data_size;
}POKEMON_ROM_HEADER;