// �A�C�e���f�[�^�\����
struct _ITEM_DATA {
/*
	u16	price;					// ���l
	u8	eqp;					// ��������
	u8	atc;					// �З�

	u8	imp:2;					// �d�v
	u8	cnv_btn:2;				// �֗��{�^��
	u8	pocket:4;				// �ۑ���i�|�P�b�g�ԍ��j
	u8	field_func;				// field�@�\
	u8	battle_func;			// battle�@�\
	u8	work_type;				// ���[�N�^�C�v

	u8	work[20];				// �ėp���[�N
*/
	u16	price;				// ���l
	u8	eqp;				// ��������
	u8	atc;				// �З�

	u8	tuibamu_eff;		// ���΂ތ���
	u8	nage_eff;			// �Ȃ��������
	u8	nage_atc;			// �Ȃ�����З�
	u8	sizen_atc;			// ������̂߂��݈З�

	u16	sizen_type:5;		// ������̂߂��݃^�C�v
	u16	imp:1;				// �d�v
	u16	cnv_btn:1;			// �֗��{�^��
	u16	fld_pocket:4;		// �t�B�[���h�ۑ���i�|�P�b�g�ԍ��j
	u16	btl_pocket:5;		// �퓬�ۑ���i�|�P�b�g�ԍ��j

	u8	field_func;			// field�@�\
	u8	battle_func;		// battle�@�\
	u8	work_type;			// ���[�N�^�C�v

	u8	dmy;				// �_�~�[

	u8	work[20];			// �ėp���[�N
};

// �_�~�[���[�N
typedef struct {
	u8	work[20];
}ITEMPARAM_NONE;

// �莝���|�P�����Ɏg�p����A�C�e��
typedef struct {
	u8	sleep_rcv:1;			// �����
	u8	poison_rcv:1;			// �ŉ�
	u8	burn_rcv:1;				// �Ώ���
	u8	ice_rcv:1;				// �X��
	u8	paralyze_rcv:1;			// ��჉�
	u8	panic_rcv:1;			// ������
	u8	meromero_rcv:1;			// ����������
	u8	ability_guard:1;		// �\�̓K�[�h

	u8	death_rcv:1;			// �m����
	u8	alldeath_rcv:1;			// �S���m����
	u8	lv_up:1;				// ���x���A�b�v
	u8	evolution:1;			// �i��
	u8	atc_up:4;				// �U���̓A�b�v

	u8	def_up:4;				// �h��̓A�b�v
	u8	spa_up:4;				// ���U�A�b�v

	u8	spd_up:4;				// ���h�A�b�v
	u8	agi_up:4;				// �f�����A�b�v

	u8	hit_up:4;				// �������A�b�v
	u8	critical_up:2;			// �N���e�B�J�����A�b�v
	u8	pp_up:1;				// PP�A�b�v
	u8	pp_3up:1;				// PP�A�b�v�i�R�i�K�j

	u8	pp_rcv:1;				// PP��
	u8	allpp_rcv:1;			// PP�񕜁i�S�Ă̋Z�j
	u8	hp_rcv:1;				// HP��
	u8	hp_exp:1;				// HP�w�͒l�A�b�v
	u8	pow_exp:1;				// �U���w�͒l�A�b�v
	u8	def_exp:1;				// �h��w�͒l�A�b�v
	u8	agi_exp:1;				// �f�����w�͒l�A�b�v
	u8	spa_exp:1;				// ���U�w�͒l�A�b�v

	u8	spd_exp:1;				// ���h�w�͒l�A�b�v
	u8	friend_exp1:1;			// �Ȃ��x�P
	u8	friend_exp2:1;			// �Ȃ��x�Q
	u8	friend_exp3:1;			// �Ȃ��x�R

	u8	dmy_bit:4;				// �_�~�[�i�]��j

	s8	prm_hp_exp;				// HP�w�͒l
	s8	prm_pow_exp;			// �U���w�͒l
	s8	prm_def_exp;			// �h��w�͒l
	s8	prm_agi_exp;			// �f�����w�͒l
	s8	prm_spa_exp;			// ���U�w�͒l
	s8	prm_spd_exp;			// ���h�w�͒l
	u8	prm_hp_rcv;				// HP�񕜒l
	u8	prm_pp_rcv;				// pp�񕜒l
	s8	prm_friend1;			// �Ȃ��x1
	s8	prm_friend2;			// �Ȃ��x2
	s8	prm_friend3;			// �Ȃ��x3

	u8	dmy_buf[2];				// �_�~�[�i�]��j
}ITEMPARAM_RCV;
