//==============================================================================================
/**
 * @file	saveflag.h
 * @brief	�Q�[�����Z�[�u�t���O��`(�X�N���v�g����̂݃A�N�Z�X�����t���O)
 * @author	Satoshi Nohara
 * @date	05.10.22
 *
 * 05.11.10 Tomomichi Ohta
 */
//==============================================================================================
#ifndef	__SAVEFLAG_H__
#define	__SAVEFLAG_H__


//----------------------------------------------------------------------
//	�ėp�t���O
//	(    1         -     99        )
//----------------------------------------------------------------------
//#define FH_00							(0)	//�����i���o�[�Ȃ̂Ŏg�p�s��
#define FH_01							(1)
#define FH_02							(2)
#define FH_03							(3)
#define FH_04							(4)
#define FH_05							(5)
#define FH_06							(6)
#define FH_07							(7)
#define FH_08							(8)
#define FH_09							(9)
#define FH_10							(10)
#define FH_11							(11)
#define FH_12							(12)
#define FH_13							(13)
#define FH_14							(14)
#define FH_15							(15)
#define FH_16							(16)
#define FH_17							(17)
#define FH_18							(18)
#define FH_19							(19)
#define FH_20							(20)
#define FH_21							(21)
#define FH_22							(22)
#define FH_23							(23)
#define FH_24							(24)
#define FH_25							(25)
#define FH_26							(26)
#define FH_27							(27)
#define FH_28							(28)
#define FH_29							(29)
#define FH_30							(30)
#define FH_31							(31)

#define FH_OBJ00						(32)
#define FH_OBJ01						(33)
#define FH_OBJ02						(34)
#define FH_OBJ03						(35)
#define FH_OBJ04						(36)
#define FH_OBJ05						(37)
#define FH_OBJ06						(38)
#define FH_OBJ07						(39)
#define FH_OBJ08						(40)
#define FH_OBJ09						(41)
#define FH_OBJ10						(42)
#define FH_OBJ11						(43)
#define FH_OBJ12						(44)
#define FH_OBJ13						(45)
#define FH_OBJ14						(46)
#define FH_OBJ15						(47)
#define FH_OBJ16						(48)
#define FH_OBJ17						(49)
#define FH_OBJ18						(50)
#define FH_OBJ19						(51)
#define FH_OBJ20						(52)
#define FH_OBJ21						(53)
#define FH_OBJ22						(54)
#define FH_OBJ23						(55)
#define FH_OBJ24						(56)
#define FH_OBJ25						(57)
#define FH_OBJ26						(58)
#define FH_OBJ27						(59)
#define FH_OBJ28						(60)
#define FH_OBJ29						(61)
#define FH_OBJ30						(62)
#define FH_OBJ31						(63)
//MAX = evwkdef.h LOCAL_FLAG_MAX

//----------------------------------------------------------------------
//	�C�x���g�i�s����t���O
//
//	(FE_FLAG_START - FV_FLAG_START)
//	(    100       -    399        )
//----------------------------------------------------------------------
#define FE_TEST_01						(FE_FLAG_START+0)
#define FE_TEST_02						(FE_FLAG_START+1)
#define FE_TEST_03						(FE_FLAG_START+2)
#define FE_TEST_04						(FE_FLAG_START+3)
#define FE_TANE_GET						(FE_FLAG_START+4)
#define FE_PC_GOLD						(FE_FLAG_START+5)
#define FE_PC_POKERUS					(FE_FLAG_START+6)
#define FE_SUGOITURIZAO_GET				(FE_FLAG_START+7)
#define FE_R201_KIZUGUSURI_GET			(FE_FLAG_START+8)
#define FE_R201_TALK_PAPA				(FE_FLAG_START+9)
#define FE_T01R0101_RIVALMAMA_TALK		(FE_FLAG_START+10)	//���C�o���}�}�Ɖ�b����
#define FE_SHOES_GET					(FE_FLAG_START+11)
#define FE_UNION_CHARACTER_SELECT		(FE_FLAG_START+12)
#define FE_C01_SUPPORT_GUIDE			(FE_FLAG_START+13)	//�T�|�[�g�̈ē�
#define FE_C01R0101_TRAINER_WIN			(FE_FLAG_START+14)	//�J���p�j�[�Ńg���[�i�[�ɏ���
#define FE_SODATE_TAMAGO				(FE_FLAG_START+15)	//�����Ă�̂��܂�
#define FE_C04_GYM_ITEM_GET				(FE_FLAG_START+16)	//C04�W���̋Z�}�V������t���O
#define FE_C03_GYM_ITEM_GET				(FE_FLAG_START+17)	//C03�W���̋Z�}�V������t���O
#define FE_C04R0304_ITEM_GET			(FE_FLAG_START+18)	//���U04����
#define FE_C03R0204_ITEM_GET			(FE_FLAG_START+19)	//���U01����
//#define FE_HIDEN_01_GET					(FE_FLAG_START+20)
#define FE_TANKENSETTO_GET				(FE_FLAG_START+21)	//���񂯂�Z�b�g����
#define FE_D01R0102_LEADER_TALK			(FE_FLAG_START+22)	//���[�_�[�Ɖ�b����
//#define FE_D01R0102_LEADER_YES			(FE_FLAG_START+23)
#define FE_C03R0103_ITEM_GET			(FE_FLAG_START+24)	//�������Γ���
#define FE_C05_GYM_ITEM_GET				(FE_FLAG_START+25)	//C05�W���̋Z�}�V������t���O
#define FE_C01R0504_ITEM_GET			(FE_FLAG_START+26)	//�h�������̂͂��܂��h����
#define FE_R205A_GINGAM_TALK			(FE_FLAG_START+27)	//�M���K�c�Ɖ�b����
#define FE_FLOWER_ITEM_GET				(FE_FLAG_START+28)	//���傤�����
#define FE_C04R0204_WIN					(FE_FLAG_START+29)	//�A�W�g�C�x���g�I��
#define FE_CYCLE_GET					(FE_FLAG_START+30)	//���]�ԓ���
#define FE_T03R0301_ITEM_GET			(FE_FLAG_START+31)	//���U�Q����
#define FE_BORONOTURIZAO_GET			(FE_FLAG_START+32)	//�{���̂肴��
#define FE_C03R0201_POKE_CHG			(FE_FLAG_START+33)	//�|�P��������������
#define FE_C04R0301_POKE_CHG			(FE_FLAG_START+34)	//�|�P��������������
#define FE_T01R0201_MAMA_TALK			(FE_FLAG_START+35)	//�}�}�Ɖ�b����
#define FE_IMAGE_CLIP					(FE_FLAG_START+36)	//�C���[�W�N���b�v�V��
#define FE_C01R0202_ITEM_GET			(FE_FLAG_START+37)	//�X�[�p�[�{�[������
#define FE_C03_RIVAL_TALK				(FE_FLAG_START+38)	//���C�o���Ɖ�b����
#define FE_D03R0101_SEVEN1_TALK			(FE_FLAG_START+39)	//5�l�O�Ɖ�b����
#define FE_C05R0102_ITEM_GET			(FE_FLAG_START+40)	//���U�}�V���S�T����
#define FE_C05R0201_ITEM_GET			(FE_FLAG_START+41)	//�|���g�P�[�X����
#define FE_INIT_CHANGE_OBJ_DEL			(FE_FLAG_START+42)	//INIT_CHANGE��OBJ������
#define FE_BOUKENNOOTO_GET				(FE_FLAG_START+43)	//�`���m�[�g�Q�b�g
#define FE_ZUKAN_GET					(FE_FLAG_START+44)	//�}�ӃQ�b�g(�C�x���g�p)
#define FE_R205A_BABYGIRL1_TALK			(FE_FLAG_START+45)	//��b����
#define FE_C02_GYM_ITEM_GET				(FE_FLAG_START+46)	//C02�W���̋Z�}�V������t���O
#define FE_HIDEN_01_GET					(FE_FLAG_START+47)	//�Ђł񃏃U01����
#define FE_HIDEN_02_GET					(FE_FLAG_START+48)	//�Ђł񃏃U02����
#define FE_HIDEN_03_GET					(FE_FLAG_START+49)	//�Ђł񃏃U03����
#define FE_HIDEN_04_GET					(FE_FLAG_START+50)	//�Ђł񃏃U04����
#define FE_HIDEN_05_GET					(FE_FLAG_START+51)	//�Ђł񃏃U05����
#define FE_HIDEN_06_GET					(FE_FLAG_START+52)	//�Ђł񃏃U06����
#define FE_HIDEN_07_GET					(FE_FLAG_START+53)	//�Ђł񃏃U07����
#define FE_HIDEN_08_GET					(FE_FLAG_START+54)	//�Ђł񃏃U08����
#define FE_C02R0301_WASURE				(FE_FLAG_START+55)	//�Z�Y��I���W�Ƙb����
#define FE_C06_GYM_ITEM_GET				(FE_FLAG_START+56)	//C06�W���̋Z�}�V������t���O
#define FE_C07_GYM_ITEM_GET				(FE_FLAG_START+57)	//C07�W���̋Z�}�V������t���O
#define FE_C09_GYM_ITEM_GET				(FE_FLAG_START+58)	//C09�W���̋Z�}�V������t���O
#define FE_D13R0101_ITEM				(FE_FLAG_START+59)	//���d���̃J�M
#define FE_D13R0101_AMAIMITU_GET		(FE_FLAG_START+60)	//���܂��݂���
#define FE_C02R0501_ITEM_GET			(FE_FLAG_START+61)	//�A�C�e������
#define FE_IITURIZAO_GET				(FE_FLAG_START+62)	//�����肴������
#define FE_C05GYM0101_SUNGLASSES_TALK	(FE_FLAG_START+63)	//��b����
#define FE_ABC_CLEAR					(FE_FLAG_START+64)	//3�̃C�x���g�N���A����
#define FE_T05_GINGABOSS_TALK			(FE_FLAG_START+65)	//�{�X�Ɖ�b����
#define FE_T05_OLDWOMAN_TALK			(FE_FLAG_START+66)	//���V�Ɖ�b����
#define FE_FRESCO_SEE					(FE_FLAG_START+67)	//�ǉ挩��
#define FE_L02_NEWS						(FE_FLAG_START+68)	//L02�̎������t���O(reset����̂Œ��ӁI)
#define FE_D29R0101_RIVAL_TALK			(FE_FLAG_START+69)	//���C�o���Ɖ�b����
#define FE_CONNECT_TSIGN_TALK			(FE_FLAG_START+70)	//�T�C����t�Ɖ�b����
#define FE_RECONGNIZE_SHINOU			(FE_FLAG_START+71)	//�V���I�E�}�Ӂh�Ђ傤���傤�h�ς�
#define FE_RECONGNIZE_NATIONAL			(FE_FLAG_START+72)	//�S���}�Ӂh�Ђ傤���傤�h�ς�
#define FE_D26R0107_GKANBU_WIN			(FE_FLAG_START+73)	//�����ɏ���
#define FE_D26R0107_MACHINE				(FE_FLAG_START+74)	//�@�B�̊J��
#define FE_C10R0101_VETERAN				(FE_FLAG_START+75)	//��Ԃǂ���
#define FE_BIGFOUR1_WIN					(FE_FLAG_START+76)	//�l�V���ɏ���
#define FE_BIGFOUR2_WIN					(FE_FLAG_START+77)	//�l�V���ɏ���
#define FE_BIGFOUR3_WIN					(FE_FLAG_START+78)	//�l�V���ɏ���
#define FE_BIGFOUR4_WIN					(FE_FLAG_START+79)	//�l�V���ɏ���
#define FE_C10R0111_CHAMP_WIN			(FE_FLAG_START+80)	//�`�����s�I���ɏ���
#define FE_C08_MIKAN_TALK				(FE_FLAG_START+81)	//�~�J���Ƙb����
#define FE_C08_GYM_ITEM_GET				(FE_FLAG_START+82)	//C08�W���̋Z�}�V������t���O
#define FE_L02_CHAMP					(FE_FLAG_START+83)	//L02�`�����s�I���C�x���g
#define FE_D27R0101_DOCTOR_TALK			(FE_FLAG_START+84)	//���m�Ɖ�b����
#define FE_D27R0101_SUPPORT_TALK		(FE_FLAG_START+85)	//�T�|�[�g�Ɖ�b����
#define FE_D27R0102_GKANBU_WIN			(FE_FLAG_START+86)	//�����ɏ���
#define FE_CONNECT_UNION_GUIDE_TALK		(FE_FLAG_START+87)	//���j�I���K�C�h�Ɖ�b����
#define FE_COIN_CASE_GET				(FE_FLAG_START+88)	//�R�C���P�[�X�����
#define FE_C04R0801_ASSISTANTM_TALK		(FE_FLAG_START+89)	//�A�V�X�^���g��b������
#define	FE_D05R0114_BLACKRING			(FE_FLAG_START+90)	//�C�A������o��
#define FE_C01R0501_ITEM_GET			(FE_FLAG_START+91)	//���񂹂��̃c������
#define FE_C03R0102_ITEM_GET			(FE_FLAG_START+92)	//��������̂�������
#define FE_C03R0202_ITEM_GET			(FE_FLAG_START+93)	//�q�[�g�{�[������
#define FE_C04R0302_ITEM_GET			(FE_FLAG_START+94)	//�킴�܂���U�V����
#define FE_GTC_GUIDE_TALK				(FE_FLAG_START+95)	//��t�̐����󂯂�
#define FE_WAZAMASIN64_GET				(FE_FLAG_START+96)	//�Z�}�V������
#define FE_WAZAMASIN78_GET				(FE_FLAG_START+97)	//�Z�}�V������
#define FE_WAZAMASIN77_GET				(FE_FLAG_START+98)	//�Z�}�V������
#define FE_WAZAMASIN51_GET				(FE_FLAG_START+99)	//�Z�}�V������
#define FE_WAZAMASIN88_GET				(FE_FLAG_START+100)	//�Z�}�V������
#define FE_WAZAMASIN48_GET				(FE_FLAG_START+101)	//�Z�}�V������
#define FE_WAZAMASIN92_GET				(FE_FLAG_START+102)	//�Z�}�V������
#define FE_WAZAMASIN42_GET				(FE_FLAG_START+103)	//�Z�}�V������
#define FE_WAZAMASIN63_GET				(FE_FLAG_START+104)	//�Z�}�V������
#define FE_WAZAMASIN66_GET				(FE_FLAG_START+105)	//�Z�}�V������
#define FE_WAZAMASIN56_GET				(FE_FLAG_START+106)	//�Z�}�V������
#define FE_WAZAMASIN11_GET				(FE_FLAG_START+107)	//�Z�}�V������
#define FE_WAZAMASIN18_GET				(FE_FLAG_START+108)	//�Z�}�V������
#define FE_WAZAMASIN37_GET				(FE_FLAG_START+109)	//�Z�}�V������
#define FE_WAZAMASIN07_GET				(FE_FLAG_START+110)	//�Z�}�V������
#define FE_P_PARK_ADMIN					(FE_FLAG_START+111)	//�|�P�p�[�N��t�Ɖ�b������
#define FE_HIIDORAN_EVENT				(FE_FLAG_START+112)	//�q�[�h�����C�x���g���t���O
#define FE_C11FS0101_ITEM_GET			(FE_FLAG_START+113)	//�s���g�����Y����
#define FE_KAZANNOOKIISI_GET			(FE_FLAG_START+114)	//������̂�����������
#define FE_HIIDORAN_SEE					(FE_FLAG_START+115)	//�q�[�h�����Ƒ������Ă��邩
#define FE_T04R0301_SUNGLASSES_TALK		(FE_FLAG_START+116)	//�ҏW���̉�b����
#define FE_R225R0101_ITEM_GET			(FE_FLAG_START+117)	//���������݂�����
#define FE_R229_ITEM_GET				(FE_FLAG_START+118)	//����̂��ܓ���
#define FE_D16R0101_RIVAL_TALK			(FE_FLAG_START+119)	//���C�o���Ɖ�b����
#define FE_T04R0301_ITEM_DEPOSIT		(FE_FLAG_START+120)	//�ҏW���ɃA�C�e����a���Ă���
#define FE_D16R0102_SEVEN5_TALK			(FE_FLAG_START+121)	//�T�l�O�Ɖ�b����
#define FE_R217R0101_ITEM_GET			(FE_FLAG_START+122)	//���̃v���[�g����
#define FE_D09R0104_SEVEN4_TALK			(FE_FLAG_START+123)	//�T�l�O�Ɖ�b����
#define FE_D21R0101_SEVEN2_TALK			(FE_FLAG_START+124)	//�T�l�O�Ɖ�b����
#define FE_D24R0105_SEVEN3_TALK			(FE_FLAG_START+125)	//�T�l�O�Ɖ�b����
#define FE_D24R0105_SEVEN3_POKE_MAX		(FE_FLAG_START+126)	//���J�����炦�Ȃ�����
#define FE_SEVEN1_CLEAR					(FE_FLAG_START+127)	//�T�l�O�C�x���g���N���A�[����
#define FE_SEVEN2_CLEAR					(FE_FLAG_START+128)	//�T�l�O�C�x���g���N���A�[����
#define FE_SEVEN3_CLEAR					(FE_FLAG_START+129)	//�T�l�O�C�x���g���N���A�[����
#define FE_SEVEN4_CLEAR					(FE_FLAG_START+130)	//�T�l�O�C�x���g���N���A�[����
#define FE_SEVEN5_CLEAR					(FE_FLAG_START+131)	//�T�l�O�C�x���g���N���A�[����
#define FE_C07R0601_WOMAN3_TALK			(FE_FLAG_START+132)	//���ɘb���Ă��邩
#define FE_C06R0401_BIGMAN_TALK			(FE_FLAG_START+133)	//���ɘb���Ă��邩
#define FE_T01R0102_RIVAL_TALK			(FE_FLAG_START+134)	//�Q�K�̃��C�o���Ɖ�b����
#define FE_C09_GYMLEADER_DEL			(FE_FLAG_START+135)	//�W�����[�_�[�������t���O
//#define FE_GTC_OPEN					(FE_FLAG_START+136)	//GTC�I�[�v��
#define FE_C01_CROWN1_TICKET			(FE_FLAG_START+137)	//�Ђ���������P
#define FE_C01_CROWN2_TICKET			(FE_FLAG_START+138)	//�Ђ���������Q
#define FE_C01_CROWN3_TICKET			(FE_FLAG_START+139)	//�Ђ���������R
#define FE_GENERATE_START				(FE_FLAG_START+140)	//��ʔ����J�n���Ă���
#define FE_TOWNMAP_GET					(FE_FLAG_START+141)	//�^�E���}�b�v����
#define FE_ACCE_CASE_GET				(FE_FLAG_START+142)	//�A�N�Z�T���[�P�[�X����
#define FE_POKETCH_GET					(FE_FLAG_START+143)	//�|�P�b�`����
#define FE_C09R0101_POKE_CHG			(FE_FLAG_START+144)	//�|�P��������������
#define FE_W226R0101_POKE_CHG			(FE_FLAG_START+145)	//�|�P��������������
#define FE_W226R0101_ZUKAN				(FE_FLAG_START+146)	//�}�Ӄp���[�A�b�v�i�C�O�e�L�X�g�j
#define FE_C08R0201_WEEK_TALK			(FE_FLAG_START+147)	//�������o����Ɖ�b����
#define FE_T01R0201_MAMA_TALK2			(FE_FLAG_START+148)	//�}�}�Ɖ�b����2
#define FE_R213R0201_FOOTMARK			(FE_FLAG_START+149)	//�t�g�}�L�Ɖ�b����
#define FE_T07R0101_MEMBER				(FE_FLAG_START+150)	//������̌����̉��
#define FE_C05_EGG						(FE_FLAG_START+151)	//�^�}�S����
#define FE_C08R0401_GOODS				(FE_FLAG_START+152)	//�n����������ɃA�C�e���a����
//#define FE_CON_CHALLENGE				(FE_FLAG_START+153)	//�R���e�X�g���킵��
#define FE_SODATEYA_AZUKE				(FE_FLAG_START+154)	//��ĉ��ɗa�������Ƃ�����
//#define	FE_D02_FUUSEN					(FE_FLAG_START+155)	//�t�[�Z���C�x���g
#define	FE_R210BR0101_DRAGON_TALK		(FE_FLAG_START+156)	//�ŋ����U����
#define	FE_C07_SUPPORT					(FE_FLAG_START+157)	//�T�|�[�g�C�x���g�I��
#define	FE_C06_GINGAM					(FE_FLAG_START+158)	//�M���K�c��񓦂���
#define	FE_C06_GINGAM_2					(FE_FLAG_START+159)	//�M���K�c��񓦂���
#define	FE_R213_GINGAM					(FE_FLAG_START+160)	//�M���K�c������
#define	FE_C07R0205_ITEM_GET			(FE_FLAG_START+161)	//�������o������
#define	FE_L02_GINGAM					(FE_FLAG_START+162)	//�M���K�c
#define	FE_R210A_CLEAR					(FE_FLAG_START+163)	//�X�g�b�p�[�C�x���g�N���A
#define	FE_R228R0201_OLDMAN1_TALK		(FE_FLAG_START+164)	//���ɂ킴������������
#define	FE_C03_ITEM_GET					(FE_FLAG_START+165)	//�A�C�e������
#define	FE_C03R0602_ITEM_GET			(FE_FLAG_START+166)	//�A�C�e������
#define	FE_GAKUSYUUSOUCHI_GET			(FE_FLAG_START+167)	//�w�K���u����
#define	FE_C01R0701_BOY_WIN				(FE_FLAG_START+168)	//��������
#define	FE_C01R0701_GIRL_WIN			(FE_FLAG_START+169)	//��������
#define	FE_C07R0301_OPEN				(FE_FLAG_START+170)	//�������̃J�M�g���Ĕ��J����
#define	FE_D02_OPEN						(FE_FLAG_START+171)	//�͂ł񂵂�L�[�g���Ĕ��J����
#define	FE_PC_SHINOU_ZUKAN_COMP			(FE_FLAG_START+172)	//PC�Ŋ������b�Z�[�W��������
#define	FE_UG_MISSION_TALK				(FE_FLAG_START+173)	//�e�~�b�V�����̐����𕷂���
#define	FE_C01R0701_ITEM_GET			(FE_FLAG_START+174)	//�Z�}�V�����肵����
#define	FE_UG_MISSION_OK				(FE_FLAG_START+175)	//�~�b�V�����ւ̃`�������W����
#define	FE_KUJI_ACCE_GET				(FE_FLAG_START+176)	//�|�P���������ŃA�N�Z�T���[������
#define	FE_R202_SUPPORT_TALK			(FE_FLAG_START+177)	//�T�|�[�g�Ɖ�b����
#define	FE_R209R0105_ITEM_GET			(FE_FLAG_START+178)	//�A�C�e�����肵����
#define	FE_SIIRUIRE_GET					(FE_FLAG_START+179)	//�V�[���������
#define	FE_R205A_BOY2_TALK				(FE_FLAG_START+180)	//��b����
#define	FE_C04R0601_ITEM_GET			(FE_FLAG_START+181)	//�A�C�e�����肵��
#define	FE_D20R0106_LEGEND_UNSEAL		(FE_FLAG_START+182)	//���W�L���O����ς�
#define	FE_D20R0106_LEGEND_CLEAR		(FE_FLAG_START+183)	//���W�L���O����
#define	FE_C06R0301_ITEM_GET			(FE_FLAG_START+184)	//�~�m���b�`�̃A�C�e������
#define	FE_D24R0201_ITEM_GET			(FE_FLAG_START+185)	//�A�C�e������
#define	FE_D05R0116_LEGEND_CLEAR		(FE_FLAG_START+186)	//�A�E�X����
#define	FE_D15R0101_LEGEND_CLEAR		(FE_FLAG_START+187)	//���[�o�X����
#define	FE_D16R0103_LEGEND_CLEAR		(FE_FLAG_START+188)	//�q�[�h��������
#define	FE_D17R0104_LEGEND_CLEAR		(FE_FLAG_START+189)	//�L�}�C��������
#define	FE_D18_LEGEND_CLEAR				(FE_FLAG_START+191)	//�G�E���X����
#define	FE_D27R0103_LEGEND_CLEAR		(FE_FLAG_START+192)	//�A�C����C�x���g�N���A
#define	FE_D16R0103_LEGEND_UNSEAL		(FE_FLAG_START+193)	//�q�[�h��������ς�
#define	FE_D28R0103_LEGEND_CLEAR		(FE_FLAG_START+194)	//�n�C����
#define	FE_D29R0103_LEGEND_CLEAR		(FE_FLAG_START+195)	//���C����
#define	FE_C06_ACCE_GET					(FE_FLAG_START+196)	//�A�N�Z�T���[����
#define	FE_C07R0201_ACCE_GET			(FE_FLAG_START+197)	//�A�N�Z�T���[����
#define	FE_D03_ACCE_GET					(FE_FLAG_START+198)	//�A�N�Z�T���[����
#define	FE_R206R0101_ACCE_GET			(FE_FLAG_START+199)	//�A�N�Z�T���[����
#define	FE_C02R0501_EVENT_CLEAR			(FE_FLAG_START+200)	//�N���Z���A(���[�o�X)���N������
#define	FE_R224_EVENT_CLEAR				(FE_FLAG_START+201)	//�Δ薼���̓C�x���g�N���A
#define	FE_C07R0101_MIDDLEMAN1_COIN_GET	(FE_FLAG_START+202)	//�R�C��
#define	FE_C07R0101_BIGMAN1_COIN_GET	(FE_FLAG_START+203)	//�R�C��
#define	FE_C07R0101_ITEM_GET			(FE_FLAG_START+204)	//�P�O�����`�������ق���
#define	FE_C05R0901_POKEMON_GET			(FE_FLAG_START+205)	//�|�P����������
#define	FE_C05R0901_TALK				(FE_FLAG_START+206)	//�~�Y�L�Ƙb����
#define	FE_D15_UNSEAL					(FE_FLAG_START+207)	//�N���Z���A(���[�o�X)���N�C�x���g�J�n==D15����
#define	FE_T05R0201_MEGANE_01_GET		(FE_FLAG_START+208)	//���K�l1�Q�b�g
#define	FE_T05R0201_MEGANE_02_GET		(FE_FLAG_START+209)	//���K�l2�Q�b�g
#define	FE_T05R0201_MEGANE_03_GET		(FE_FLAG_START+210)	//���K�l3�Q�b�g
#define	FE_R221R0201_ITEM_KEEP			(FE_FLAG_START+211)	//�A�C�e����a�����Ă�����
#define	FE_D04R0101_ITEM_GET			(FE_FLAG_START+212)	//�A�C�e������
#define	FE_R212AR0102_ITEM_GET			(FE_FLAG_START+213)	//�A�C�e������
#define	FE_L02R0201_ITEM_GET			(FE_FLAG_START+214)	//�A�C�e������
#define	FE_R217R0201_ITEM_GET			(FE_FLAG_START+215)	//�A�C�e������
#define	FE_C02R0401_START				(FE_FLAG_START+216)	//�_�[�N�C�x���g�n�߂�
#define	FE_C01R0202_ACCE_GET			(FE_FLAG_START+217)	//�A�N�Z�T���[����
#define	FE_L02_GINGA_WIN				(FE_FLAG_START+218)	//L02�M���K�c�ɏ���
#define FE_R208_ITEM_GET				(FE_FLAG_START+219)	//�A�C�e������
#define FE_C06R0601_ITEM_GET_STYLE		(FE_FLAG_START+220)	//�A�C�e������
#define FE_C06R0601_ITEM_GET_BEAUTIFUL	(FE_FLAG_START+221)	//�A�C�e������
#define FE_C06R0601_ITEM_GET_CUTE		(FE_FLAG_START+222)	//�A�C�e������
#define FE_C06R0601_ITEM_GET_CLEVER		(FE_FLAG_START+223)	//�A�C�e������
#define FE_C06R0601_ITEM_GET_STRONG		(FE_FLAG_START+224)	//�A�C�e������
#define	FE_T05R0101_OLDWOMAN1			(FE_FLAG_START+225)	//�J���i�M���V�C�x���g�I��
#define	FE_SUPPORT_POKETORE_1			(FE_FLAG_START+226)	//�T�|�[�g�̃|�P�g����b
#define	FE_SUPPORT_POKETORE_2			(FE_FLAG_START+227)	//�T�|�[�g�̃|�P�g����b
#define	FE_SUPPORT_POKETORE_3			(FE_FLAG_START+228)	//�T�|�[�g�̃|�P�g����b
#define FE_D25R0106_SPPOKE_CLEAR		(FE_FLAG_START+229)	//d25r0106�v���Y�}�ߊl
#define	FE_C05_GOODS_01					(FE_FLAG_START+230)	//�O�b�Y1����ς�
#define	FE_C05_GOODS_02					(FE_FLAG_START+231)	//�O�b�Y2����ς�
#define	FE_C05_GOODS_03					(FE_FLAG_START+232)	//�O�b�Y3����ς�
#define	FE_C05_GOODS_04					(FE_FLAG_START+233)	//�O�b�Y4����ς�
#define	FE_C05_GOODS_05					(FE_FLAG_START+234)	//�O�b�Y5����ς�
#define	FE_C05_GOODS_06					(FE_FLAG_START+235)	//�O�b�Y6����ς�
#define	FE_C05_GOODS_07					(FE_FLAG_START+236)	//�O�b�Y7����ς�
#define	FE_C05_GOODS_08					(FE_FLAG_START+237)	//�O�b�Y8����ς�
#define	FE_C05_GOODS_09					(FE_FLAG_START+238)	//�O�b�Y9����ς�
#define	FE_C05_GOODS_10					(FE_FLAG_START+239)	//�O�b�Y10����ς�
#define	FE_C05_GOODS_11					(FE_FLAG_START+240)	//�O�b�Y11����ς�
#define	FE_C05_GOODS_12					(FE_FLAG_START+241)	//�O�b�Y12����ς�
#define	FE_C05_GOODS_13					(FE_FLAG_START+242)	//�O�b�Y13����ς�
#define	FE_C05_GOODS_14					(FE_FLAG_START+243)	//�O�b�Y14����ς�
#define FE_D30R0101_LEGEND_CLEAR		(FE_FLAG_START+244)	//d30r0101�_�[�N�ߊl
#define FE_C05R1101_POFIN_INFOMATION	(FE_FLAG_START+245)	//�|�t�B������F��t�O�̉�b
#define FE_C05R1101_POFIN_GET			(FE_FLAG_START+246)	//�|�t�B������F�|�t�B������ς�
#define	FE_C05_ALL_GOODS_GET			(FE_FLAG_START+247)	//�����ł̑S�ẴO�b�Y����ς�
#define FE_T01R0201_GAMECLEAR_KISSAKI	(FE_FLAG_START+248)	//�Q�[���N���A��̃}�}�Ƃ̉�b
#define FE_T01R0201_GAMECLEAR_ZUKAN		(FE_FLAG_START+249)	//�Q�[���N���A��̃}�}�Ƃ̉�b
#define	FE_D05R0114_CLEAR				(FE_FLAG_START+250)	//�e���K���U���R���N���A
#define	FE_D05R0114_SPPOKE_GET			(FE_FLAG_START+251)	//�C�A�i�G�A�j�ߊl����
#define	FE_D06R0206_ITEM_GET			(FE_FLAG_START+252)	//�A�C�e������
#define	FE_R213R0501_MYSTERY_TALK		(FE_FLAG_START+253)	//�~�X�e���[�Ɖ�b
#define	FE_C08R0801_TALK				(FE_FLAG_START+254)	//����ŃW�����[�_�[�Ɖ�b����
#define	FE_R212AR0103_RICH_TALK			(FE_FLAG_START+255)	//��������������Ɖ�b�i����j
#define	FE_R212AR0103_BUTLER_TALK		(FE_FLAG_START+256)	//�����Ɖ�b�i����j

//----------------------------------------------------------------------
//	�o�j�b�V���t���O
//
//	(FV_FLAG_START - FH_FLAG_START)
//	(    400       -    729      )
//----------------------------------------------------------------------
#define FV_R201_RIVAL					(FV_FLAG_START+0)		//���C�o��
#define FV_T02_DOCTOR					(FV_FLAG_START+1)		//���m
#define FV_T01_RIVAL					(FV_FLAG_START+2)		//���C�o��
#define FV_D27R0101_DOCTOR				(FV_FLAG_START+3)		//���m
#define FV_D27R0101_KABAN				(FV_FLAG_START+4)		//�J�o��
#define FV_T02_SUPPORT					(FV_FLAG_START+5)		//�T�|�[�g
#define FV_R201_DOCTOR					(FV_FLAG_START+6)		//���m
#define FV_R201_SUPPORT					(FV_FLAG_START+7)		//�T�|�[�g
#define FV_C01_SUPPORT					(FV_FLAG_START+8)		//�T�|�[�g(�R�g�u�L)
#define FV_R203_RIVAL					(FV_FLAG_START+9)		//���C�o��(r203)
#define FV_C03_RIVAL					(FV_FLAG_START+10)		//���C�o��(�N���K�l)
//#define FV_T03_GINGA_BOSS				(FV_FLAG_START+11)		//�M���K�c�{�X(T03)
#define	FV_C05R0701_STOPPER				(FV_FLAG_START+12)		//�X�g�b�p�[
#define FV_HATSUDEN_GINGA				(FV_FLAG_START+13)		//�M���K�c(���d��)
#define FV_C04_CHAMP					(FV_FLAG_START+14)		//�`�����s�I��(�n�N�^�C)
#define FV_C04_GINGA_KANBU				(FV_FLAG_START+15)		//�M���K�c����(�n�N�^�C)
#define FV_C04_DOCTOR					(FV_FLAG_START+16)		//�|�P�������m(�n�N�^�C)
#define FV_C04_GYM_TRAINER1				(FV_FLAG_START+17)		//C04�W���̃g���[�i�[1
#define FV_C04_GYM_TRAINER2				(FV_FLAG_START+18)		//C04�W���̃g���[�i�[2
#define FV_C04_GYM_TRAINER3				(FV_FLAG_START+19)		//C04�W���̃g���[�i�[3
#define FV_C04_GYM_TRAINER4				(FV_FLAG_START+20)		//C04�W���̃g���[�i�[4
#define FV_C04_GYM_LEADER				(FV_FLAG_START+21)		//C04�W���̃��[�_�[
#define FV_R202_SUPPORT					(FV_FLAG_START+22)		//�T�|�[�g
#define FV_C01R0201_SUPPORT				(FV_FLAG_START+23)		//�T�|�[�g
#define FV_D01R0102_LEADER				(FV_FLAG_START+24)		//�W�����[�_�[
#define FV_C01_SUNGLASSES				(FV_FLAG_START+25)		//�T���O���X(�A�N�Z�T���P�[�X)
#define FV_C01_ASSISTANTM				(FV_FLAG_START+26)		//����
#define FV_T01_MAMA						(FV_FLAG_START+27)		//�}�}
#define FV_D02_GINGAM_A					(FV_FLAG_START+28)		//�M���K�c(d02)
#define FV_D27R0101_POKE				(FV_FLAG_START+29)		//�|�P����
#define FV_C04_GINGAM					(FV_FLAG_START+30)		//�M���K�c
#define FV_C04R0204_GKANBU				(FV_FLAG_START+31)		//�M���K�c����
#define FV_C04R0101_MIDDLEM				(FV_FLAG_START+32)		//���]�Ԃ̐l
#define FV_C04R0101_POKE				(FV_FLAG_START+33)		//���]�Ԃ̃|�P����
#define FV_D27R0101_SUPPORT				(FV_FLAG_START+34)		//�T�|�[�g
#define FV_L01_RIVAL					(FV_FLAG_START+35)		//���C�o��
#define FV_D27R0101_RIVAL				(FV_FLAG_START+36)		//���C�o��
#define FV_T02_RIVAL					(FV_FLAG_START+37)		//���C�o��
#define FV_T02R0101_DOCTOR				(FV_FLAG_START+38)		//���m
#define FV_T02R0101_SUPPORT				(FV_FLAG_START+39)		//�T�|�[�g
#define FV_C03_BOY1						(FV_FLAG_START+40)		//�V���[�Y���N
#define FV_D03R0101_SEVEN1				(FV_FLAG_START+41)		//5�l�O
#define FV_C01_GINGA					(FV_FLAG_START+42)		//�M���K�c
#define FV_C01_DOCTOR					(FV_FLAG_START+43)		//���m
#define FV_D13R0101_ITEM				(FV_FLAG_START+44)		//���d���̌�
#define FV_D13R0101_GINGAM_A			(FV_FLAG_START+45)		//�M���K�c
#define FV_D13R0101_GINGAM_B			(FV_FLAG_START+46)		//�M���K�c
#define FV_T03_GINGAM					(FV_FLAG_START+47)		//�M���K�c
#define FV_R205A_GINGAM					(FV_FLAG_START+48)		//�M���K�c
#define FV_T03_GINGABOSS				(FV_FLAG_START+49)		//�M���K�c�{�X
#define FV_D02R0101_GINGAM				(FV_FLAG_START+50)		//�M���K�c(POS)
#define FV_D02R0101_GINGALEADER1		(FV_FLAG_START+51)		//�M���K�c���[�_�[
#define FV_D02R0101_GINGA_ALL			(FV_FLAG_START+52)		//�M���K�c�S��
#define FV_UG_MOUNT						(FV_FLAG_START+53)		//�n���R�j
#define FV_C07_SUPPORT					(FV_FLAG_START+54)		//�T�|�[�g
#define FV_C06_RIVAL					(FV_FLAG_START+55)		//���C�o��
#define FV_C05_CHAMP					(FV_FLAG_START+56)		//�`�����s�I��
#define FV_D05R0101_GINGABOSS			(FV_FLAG_START+57)		//�M���K�c�{�X
#define FV_T05_OLDWOMAN					(FV_FLAG_START+58)		//���V
#define FV_L02_CHAMP					(FV_FLAG_START+59)		//�`�����s�I��
#define FV_L02_GINGAM					(FV_FLAG_START+60)		//�M���K�c
#define FV_T05_GINGAM					(FV_FLAG_START+61)		//�M���K�c
#define FV_R210A_POKE					(FV_FLAG_START+62)		//�X�g�b�p�[
#define FV_R210A_CHAMP					(FV_FLAG_START+63)		//�`�����s�I��
#define FV_C02_RIVAL					(FV_FLAG_START+64)		//���C�o��
#define FV_C02_DOCTOR					(FV_FLAG_START+65)		//���m
#define FV_C02_SEAMAN					(FV_FLAG_START+66)		//��ʎs��
#define FV_C02_SUPPORT					(FV_FLAG_START+67)		//�T�|�[�g
#define FV_C02R0103_SUPPORT				(FV_FLAG_START+68)		//�T�|�[�g
#define FV_C02R0103_DOCTOR				(FV_FLAG_START+69)		//���m
#define FV_C02R0103_RIVAL				(FV_FLAG_START+70)		//���C�o��
#define FV_D29R0102_RIVAL				(FV_FLAG_START+71)		//���C�o��
#define FV_D29R0102_GKANBU2				(FV_FLAG_START+72)		//�M���K�c����
//#define FV_D27R0101_GKANBU1			(FV_FLAG_START+73)		//�M���K�c����
#define FV_D28R0101_GINGA				(FV_FLAG_START+74)		//�M���K�c
#define FV_T05_GINGABOSS				(FV_FLAG_START+75)		//�M���K�{�X
#define FV_D26R0104_GINGABOSS			(FV_FLAG_START+76)		//�M���K�{�X
#define FV_C07_GINGAM					(FV_FLAG_START+77)		//�M���K�c
#define FV_D27R0102_GKANBU				(FV_FLAG_START+78)		//�M���K�c����
#define FV_D28R0101_KOIKING				(FV_FLAG_START+79)		//�R�C�L���O
//#define FV_D27R0101_DOCTOR			(FV_FLAG_START+80)		//���m
#define FV_T05R0101_OLDWOMAN			(FV_FLAG_START+81)		//���V
#define	FV_D05R0114_SPPOKE_01			(FV_FLAG_START+82)		//�e���K���U���R���F�C�A�i�G�A�j
#define	FV_D05R0114_RIVAL				(FV_FLAG_START+83)		//�e���K���U���R���F���C�o��
#define FV_D05R0114_SUPPORT				(FV_FLAG_START+84)		//�e���K���U���R���F�T�|�[�g
#define FV_D05R0114_DOCTOR				(FV_FLAG_START+85)		//�e���K���U���R���F���m
#define	FV_D05R0114_GINGAM				(FV_FLAG_START+86)		//�e���K���U���R���F�M���K�c�U�R
#define	FV_D05R0114_GINGAKANBU			(FV_FLAG_START+87)		//�e���K���U���R���F�M���K�c����
#define	FV_D05R0114_GINGABOSS			(FV_FLAG_START+88)		//�e���K���U���R���F�M���K�c�{�X
#define	FV_D31R0205_TRAINER				(FV_FLAG_START+89)		//�^���[�V���O���ΐ푊��
#define	FV_R207_SUPPORT					(FV_FLAG_START+90)		//�T�|�[�g
#define	FV_R222_WORKMAN					(FV_FLAG_START+91)		//�X�g�b�p�[
#define	FV_D05R0114_POKE_L01			(FV_FLAG_START+92)		//�e���K���U���R���F���C
#define	FV_D05R0114_POKE_L02			(FV_FLAG_START+93)		//�e���K���U���R���F�A�C
#define	FV_D05R0114_POKE_L03			(FV_FLAG_START+94)		//�e���K���U���R���F�n�C
#define	FV_T04R0101_SUNGLASSES			(FV_FLAG_START+95)		//�����Ă�̃T���O���X
#define	FV_R221R0101_OOKIDO				(FV_FLAG_START+96)		//�I�[�L�h
#define	FV_C11_RIVAL					(FV_FLAG_START+97)		//���C�o��
#define	FV_C11_SEVEN2					(FV_FLAG_START+98)		//�T�l�O
#define	FV_T06_SEVEN2					(FV_FLAG_START+99)		//�T�l�O
#define	FV_T06R0101_SEVEN2				(FV_FLAG_START+100)		//�T�l�O
#define	FV_R227_RIVAL					(FV_FLAG_START+101)		//���C�o��
#define	FV_R227_GYMLEADER				(FV_FLAG_START+102)		//�W�����[�_�[
#define	FV_D16R0101_RIVAL				(FV_FLAG_START+103)		//���C�o��
#define	FV_D16R0102_SEVEN5				(FV_FLAG_START+104)		//�T�l�O
#define	FV_D16R0103_SEVEN2				(FV_FLAG_START+105)		//�T�l�O
#define	FV_D16R0103_RIVAL				(FV_FLAG_START+106)		//���C�o��
#define	FV_D16R0103_HIIDORAN			(FV_FLAG_START+107)		//�q�[�h����
#define	FV_D16R0103_KAZANNOOKIISI		(FV_FLAG_START+108)		//������̂�������
#define	FV_D27R0103_AI					(FV_FLAG_START+109)		//�A�C
#define	FV_D28R0103_HAI					(FV_FLAG_START+110)		//�n�C
#define	FV_D29R0103_REI					(FV_FLAG_START+111)		//���C
#define	FV_D11R0101_PIKACHU				(FV_FLAG_START+112)		//�s�J�`���E
#define	FV_D11R0101_ATYAMO				(FV_FLAG_START+113)		//�A�`����
#define	FV_D21R0101_SEVEN2				(FV_FLAG_START+114)		//�T�l�O
#define	FV_D24R0105_SEVEN3				(FV_FLAG_START+115)		//�T�l�O
#define	FV_D09R0104_SEVEN4				(FV_FLAG_START+116)		//�T�l�O
#define	FV_D24R0105_GINGAM				(FV_FLAG_START+117)		//�|�S���M���K�c
#define	FV_D09R0101_STOPPER				(FV_FLAG_START+118)		//�`�����s�I�����[�h�X�g�b�p�[
#define	FV_D31R0201_PRIZEMAN			(FV_FLAG_START+119)		//�^���[��t�ܕi�������l
#define	FV_D31R0206_TRAINER01			(FV_FLAG_START+120)		//�^���[�}���`�ΐ핔���g���[�i�[1
#define	FV_D31R0206_TRAINER02			(FV_FLAG_START+121)		//�^���[�}���`�ΐ핔���g���[�i�[2
#define	FV_D31R0207_SEVEN1				(FV_FLAG_START+122)		//�^���[�T�����ܐl�O1
#define	FV_D31R0207_SEVEN2				(FV_FLAG_START+123)		//�^���[�T�����ܐl�O2
#define	FV_D31R0207_SEVEN3				(FV_FLAG_START+124)		//�^���[�T�����ܐl�O3
#define	FV_D31R0207_SEVEN4				(FV_FLAG_START+125)		//�^���[�T�����ܐl�O4
#define	FV_D31R0207_SEVEN5				(FV_FLAG_START+126)		//�^���[�T�����ܐl�O5
#define	FV_T01R0201_RIVALMAMA			(FV_FLAG_START+127)		//���C�o���}�}
#define	FV_T01R0102_RIVAL				(FV_FLAG_START+128)		//���C�o��
#define	FV_C09_GYMLEADER				(FV_FLAG_START+129)		//�W�����[�_�[
#define	FV_C01R0701_RIVAL				(FV_FLAG_START+130)		//���C�o��
#define	FV_C01_CROWN					(FV_FLAG_START+131)		//�s�G��
#define	FV_C01_POKETCH					(FV_FLAG_START+132)		//�|�P�b�`�����l
#define	FV_C01R0101_POKETCH				(FV_FLAG_START+133)		//�|�P�b�`�����l
#define	FV_R205A_BABYGIRL1				(FV_FLAG_START+134)		//���d���t�߂̏���
#define	FV_D02R0101_BABYGIRL1			(FV_FLAG_START+135)		//���d���t�߂̏���
#define	FV_C08R0101_SEAMAN				(FV_FLAG_START+136)		//�D���
#define	FV_C08R0101_SUNGLASSES			(FV_FLAG_START+137)		//�T���O���X
#define	FV_D03R0101_LEADER				(FV_FLAG_START+138)		//�i�^�l
#define	FV_C04_GINGA					(FV_FLAG_START+139)		//�M���K�c
#define	FV_C04PC0101_GONBE				(FV_FLAG_START+140)		//�S���x
#define	FV_C04R0204_MIDDLEM				(FV_FLAG_START+141)		//�A�W�g�ɂ��邨������
#define	FV_C04R0101_PIPPI				(FV_FLAG_START+142)		//�҂���
#define	FV_C05R1102_CON1				(FV_FLAG_START+143)		//�R���e�X�g�Q����
#define	FV_C05R1102_CON2				(FV_FLAG_START+144)		//�R���e�X�g�Q����
#define	FV_C05R1102_CON3				(FV_FLAG_START+145)		//�R���e�X�g�Q����
#define	FV_C05R1102_CON4				(FV_FLAG_START+146)		//�R���e�X�g�Q����
#define	FV_C05R1102_CON5				(FV_FLAG_START+147)		//�R���e�X�g�Q����
#define	FV_C05_STOPPER					(FV_FLAG_START+148)		//�R���e�X�g�X�g�b�p�[
#define	FV_C05_RIVAL					(FV_FLAG_START+149)		//���C�o��
#define	FV_C05R1101_MAMA				(FV_FLAG_START+150)		//�}�}
#define	FV_C05R1101_JUDGE				(FV_FLAG_START+151)		//�~�~�B
#define	FV_MYSTERY_POSTMAN				(FV_FLAG_START+152)		//�ӂ����z�B��
#define	FV_D02_FUUSEN					(FV_FLAG_START+153)		//�t�[�Z��
#define FV_C06_GINGAM					(FV_FLAG_START+154)		//�M���K�c
#define FV_TV_INTERVIEW_01				(FV_FLAG_START+155)		//TV(�C���^�r���[)�W��
#define FV_TV_INTERVIEW_02				(FV_FLAG_START+156)		//TV(�C���^�r���[)�o�g���^���[
#define FV_TV_INTERVIEW_03				(FV_FLAG_START+157)		//TV(�C���^�r���[)�t�@�N�g���[
#define FV_TV_INTERVIEW_04				(FV_FLAG_START+158)		//TV(�C���^�r���[)���Ȃ��̃|�P����
#define FV_TV_INTERVIEW_05				(FV_FLAG_START+159)		//TV(�C���^�r���[)�������߂ǂ���
#define FV_TV_INTERVIEW_06				(FV_FLAG_START+160)		//TV(�C���^�r���[)�|�P�b�`
#define FV_TV_INTERVIEW_07				(FV_FLAG_START+161)		//TV(�C���^�r���[)�R���e�X�g
#define FV_TV_INTERVIEW_08				(FV_FLAG_START+162)		//TV(�C���^�r���[)���Ƃ�����
#define FV_TV_INTERVIEW_09				(FV_FLAG_START+163)		//TV(�C���^�r���[)�N���b�v
#define FV_TV_INTERVIEW_10				(FV_FLAG_START+164)		//TV(�C���^�r���[)���i�f�f
#define FV_TV_INTERVIEW_11				(FV_FLAG_START+165)		//TV(�C���^�r���[)�|���g
#define FV_TV_INTERVIEW_12				(FV_FLAG_START+166)		//TV(�C���^�r���[)����
#define FV_TV_INTERVIEW_13				(FV_FLAG_START+167)		//TV(�C���^�r���[)�A�����
#define FV_R213_GINGAM					(FV_FLAG_START+168)		//�M���K�c
#define FV_L02_GINGAM_1					(FV_FLAG_START+169)		//������M���K�c
#define FV_R218R0201_ASSISTANTM			(FV_FLAG_START+170)		//����i�T�|�[�^�[�̐e�H�j
#define FV_C10R0101_RIVAL				(FV_FLAG_START+171)		//���C�o��
#define FV_T04R0501_BABYBOY1			(FV_FLAG_START+172)		//�V�[�����N
#define FV_D07R0105_BABYBOY1			(FV_FLAG_START+173)		//�V�[�����N
#define FV_C05_EGG						(FV_FLAG_START+174)		//�^�}�S�����l
#define FV_C04GYM0101_LEADER			(FV_FLAG_START+175)		//�W�����[�_�[
#define FV_C04R0401_ASSISTANTM			(FV_FLAG_START+176)		//����
#define FV_C07_GINGAM_3					(FV_FLAG_START+177)		//�M���K�c
#define FV_D26R0101_DOOR				(FV_FLAG_START+178)		//�h�A
#define FV_D26R0103_DOOR				(FV_FLAG_START+179)		//�h�A
#define FV_D26R0104_DOOR				(FV_FLAG_START+180)		//�h�A
#define FV_D26R0106_DOOR				(FV_FLAG_START+181)		//�h�A
#define FV_C07R0301_BAR					(FV_FLAG_START+182)		//�o�[
#define FV_T05R0501_OLDWOMAN			(FV_FLAG_START+183)		//���V
#define FV_T02R0101_OOKIDO				(FV_FLAG_START+184)		//�I�[�L�h���m
#define	FV_D11R0101_PIPPI				(FV_FLAG_START+185)		//�s�b�s
#define	FV_D11R0101_KODAKKU				(FV_FLAG_START+186)		//�R�_�b�N
#define	FV_D11R0101_PATIRISSU			(FV_FLAG_START+187)		//�p�`���X
#define	FV_D11R0101_HUUSEN				(FV_FLAG_START+188)		//�t�[�Z��
#define	FV_D11R0101_MIMITTO				(FV_FLAG_START+189)		//�~�~�b�g
#define	FV_D11R0101_KORAKII				(FV_FLAG_START+190)		//�R���b�L�[
#define	FV_D11R0101_PURIN				(FV_FLAG_START+191)		//�v����
#define	FV_D11R0101_ENEKO				(FV_FLAG_START+192)		//�G�l�R
#define	FV_D11R0101_KINOKOKO			(FV_FLAG_START+193)		//�L�m�R�R
#define	FV_L03_GINGAM					(FV_FLAG_START+194)		//�M���K�c
#define	FV_D05R0102_STOPPER				(FV_FLAG_START+195)		//�e���K���R�X�g�b�p�[
#define	FV_D26R0107_POKE				(FV_FLAG_START+196)		//���C�A�C�n�C
#define	FV_D26R0107_GKANBU				(FV_FLAG_START+197)		//����
#define	FV_C01_CROWN3					(FV_FLAG_START+198)		//�s�G��(TV�ǑO)
#define	FV_C08_LEADER					(FV_FLAG_START+199)		//�l�V��
#define	FV_C10R0112_CHAMP				(FV_FLAG_START+200)		//�`�����s�I��
#define	FV_C10R0112_DOCTOR				(FV_FLAG_START+201)		//�i�i�J�}�h
#define FV_C05_JUDGE					(FV_FLAG_START+202)		//�~�~�B
#define FV_C05_POKE						(FV_FLAG_START+203)		//�~�~�b�g
#define FV_C05_LEADER					(FV_FLAG_START+204)		//�W�����[�_�[
#define FV_STOPPER_FRIENDBOOK			(FV_FLAG_START+205)		//�Ƃ������蒠�X�g�b�p�[
#define FV_D30R0101_SPPOKE7				(FV_FLAG_START+206)		//�_�[�N
#define FV_C02R0401_EVENT				(FV_FLAG_START+207)		//�_�[�N�̃T���O���X
#define FV_C04R0601_OOKIDO				(FV_FLAG_START+208)		//�I�[�L�h���m
#define FV_D20R0106_LEGEND				(FV_FLAG_START+209)		//���W�L���O
#define FV_L02R0101_COUPLE1				(FV_FLAG_START+210)		//���X�g�����@�J�b�v���P
#define FV_L02R0101_COUPLE2				(FV_FLAG_START+211)		//���X�g�����@�J�b�v���Q
#define FV_L02R0101_COUPLE3				(FV_FLAG_START+212)		//���X�g�����@�J�b�v���R
#define FV_L02R0101_COUPLE4				(FV_FLAG_START+213)		//���X�g�����@�J�b�v���S
#define FV_L02R0101_COUPLE5				(FV_FLAG_START+214)		//���X�g�����@�J�b�v���T
#define FV_L02R0101_COUPLE6				(FV_FLAG_START+215)		//���X�g�����@�J�b�v���U
#define FV_L02R0101_COUPLE7				(FV_FLAG_START+216)		//���X�g�����@�J�b�v���V
#define FV_L02R0101_COUPLE8				(FV_FLAG_START+217)		//���X�g�����@�J�b�v���W
#define FV_L02R0101_COUPLE9				(FV_FLAG_START+218)		//���X�g�����@�J�b�v���X
#define FV_D24R0201_LEADER				(FV_FLAG_START+219)		//�W�����[�_�[�@�g�E�K��
#define	FV_D05R0116_LEGEND				(FV_FLAG_START+220)	//�A�E�X
#define	FV_D15R0101_LEGEND				(FV_FLAG_START+221)	//���[�o�X
#define	FV_D17R0104_LEGEND				(FV_FLAG_START+222)	//�L�}�C����
#define	FV_D18_LEGEND					(FV_FLAG_START+223)	//�G�E���X
#define	FV_R224_OOKIDO					(FV_FLAG_START+224)	//r224�I�[�L�h
#define	FV_C01R0201_SUNDAY				(FV_FLAG_START+225)	//���j�g���[�i�[
#define	FV_C01R0201_MONDAY				(FV_FLAG_START+226)	//���j�g���[�i�[
#define	FV_C01R0201_TUESDAY				(FV_FLAG_START+227)	//�Ηj�g���[�i�[
#define	FV_C01R0201_WEDNESDAY			(FV_FLAG_START+228)	//���j�g���[�i�[
#define	FV_C01R0201_THURSDAY			(FV_FLAG_START+229)	//�ؗj�g���[�i�[
#define	FV_C01R0201_THURSDAY2			(FV_FLAG_START+230)	//�ؗj�g���[�i�[(����)
#define	FV_C01R0201_FRIDAY				(FV_FLAG_START+231)	//���j�g���[�i�[
#define	FV_C01R0201_SATURDAY			(FV_FLAG_START+232)	//�y�j�g���[�i�[
#define	FV_C02R0501_SEAMAN				(FV_FLAG_START+233)	//c02r0501�D���
#define	FV_R224_LEGEND					(FV_FLAG_START+234)	//r224�G�E���X
#define	FV_L02_WOMAN2					(FV_FLAG_START+235)	//���������o����
#define	FV_L02R0201_WOMAN2				(FV_FLAG_START+236)	//���������o����
#define	FV_R217R0201_WOMAN1				(FV_FLAG_START+237)	//�o����
#define FV_R212A_POLICE1_NPC			(FV_FLAG_START+238)		//�����肳��(�ʏ�NPC)
#define FV_R212A_POLICE1_TR				(FV_FLAG_START+239)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R212A_POLICE2_NPC			(FV_FLAG_START+240)		//�����肳��(�ʏ�NPC)
#define FV_R212A_POLICE2_TR				(FV_FLAG_START+241)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R212A_POLICE3_NPC			(FV_FLAG_START+242)		//�����肳��(�ʏ�NPC)
#define FV_R212A_POLICE3_TR				(FV_FLAG_START+243)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R212A_POLICE4_NPC			(FV_FLAG_START+244)		//�����肳��(�ʏ�NPC)
#define FV_R212A_POLICE4_TR				(FV_FLAG_START+245)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R212B_POLICE5_NPC			(FV_FLAG_START+246)		//�����肳��(�ʏ�NPC)
#define FV_R212B_POLICE5_TR				(FV_FLAG_START+247)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R222_POLICE6_NPC				(FV_FLAG_START+248)		//�����肳��(�ʏ�NPC)
#define FV_R222_POLICE6_TR				(FV_FLAG_START+249)		//�����肳��(�ΐ�g���[�i�[)
#define FV_R209_JOGGER1_NPC				(FV_FLAG_START+250)		//�W���M���O(�ʏ�NPC)
#define FV_R209_JOGGER1_TR				(FV_FLAG_START+251)		//�W���M���O(�ΐ�g���[�i�[)
#define FV_R209_JOGGER6_NPC				(FV_FLAG_START+252)		//�W���M���O(�ʏ�NPC)
#define FV_R209_JOGGER6_TR				(FV_FLAG_START+253)		//�W���M���O(�ΐ�g���[�i�[)
#define FV_R210A_JOGGER4_NPC			(FV_FLAG_START+254)		//�W���M���O(�ʏ�NPC)
#define FV_R210A_JOGGER4_TR				(FV_FLAG_START+255)		//�W���M���O(�ΐ�g���[�i�[)
#define FV_R215_JOGGER3_NPC				(FV_FLAG_START+256)		//�W���M���O(�ʏ�NPC)
#define FV_R215_JOGGER3_TR				(FV_FLAG_START+257)		//�W���M���O(�ΐ�g���[�i�[)
#define FV_R215_JOGGER5_NPC				(FV_FLAG_START+258)		//�W���M���O(�ʏ�NPC)
#define FV_R215_JOGGER5_TR				(FV_FLAG_START+259)		//�W���M���O(�ΐ�g���[�i�[)
#define FV_D31_TOWERBOSS				(FV_FLAG_START+260)		//�^���[�^�C�N�[��
#define FV_D31_RIVAL					(FV_FLAG_START+261)		//���C�o��
#define	FV_D17R0104_ITEM				(FV_FLAG_START+262)		//d17r0104�A�C�e���{�[��
#define	FV_D30_SEAMAN					(FV_FLAG_START+263)		//d30�D��
#define	FV_C09_SEAMAN					(FV_FLAG_START+264)		//c09�D��
#define	FV_D25R0102_OLDMAN2				(FV_FLAG_START+265)		//d25r0102�H�삶�������
#define	FV_D25R0108_BABYGIRL1			(FV_FLAG_START+266)		//d25r0108�H�쏗�̎q
#define	FV_L02_BIGMAN					(FV_FLAG_START+267)		//l02�X�g�b�p�[
#define	FV_D09R0101_BIGMAN				(FV_FLAG_START+268)		//d09r0101�X�g�b�p�[
#define	FV_R221_STOPPER1				(FV_FLAG_START+269)		//R221�X�g�b�p�[1
#define	FV_R221_STOPPER2				(FV_FLAG_START+270)		//R221�X�g�b�p�[2
#define	FV_C08R0801_LEADER				(FV_FLAG_START+271)		//�W�����[�_�[
#define	FV_C10R0103_DOOR_01				(FV_FLAG_START+272)		//�h�A(��O)
#define	FV_C10R0105_DOOR_01				(FV_FLAG_START+273)		//�h�A
#define	FV_C10R0107_DOOR_01				(FV_FLAG_START+274)		//�h�A
#define	FV_C10R0109_DOOR_01				(FV_FLAG_START+275)		//�h�A
#define	FV_C10R0103_DOOR_02				(FV_FLAG_START+276)		//�h�A(��)
#define	FV_C10R0105_DOOR_02				(FV_FLAG_START+277)		//�h�A
#define	FV_C10R0107_DOOR_02				(FV_FLAG_START+278)		//�h�A
#define	FV_C10R0109_DOOR_02				(FV_FLAG_START+279)		//�h�A
//#define	FV_C08_LEADER					(FV_FLAG_START+280)		//�h�A
#define	FV_R212AR0103_POLICEMAN			(FV_FLAG_START+281)		//�x����
#define FV_D27R0102_DOCTOR				(FV_FLAG_START+282)		//���m
#define FV_D27R0102_SUPPORT				(FV_FLAG_START+283)		//�T�|�[�g
#define FV_R227_SEVEN2					(FV_FLAG_START+284)		//�T�l�O
#define FV_D05R0110_GINGAM				(FV_FLAG_START+285)		//�M���K�c�������σX�g�b�p�[
#define FV_C01R0206_STOP				(FV_FLAG_START+286)		//������������X�g�b�p�[
#define FV_C01R0207_STOP				(FV_FLAG_START+287)		//������������X�g�b�p�[
#define FV_D26R0101_GKANBU				(FV_FLAG_START+288)		//����
#define FV_D29R0101_RIVAL				(FV_FLAG_START+289)		//���C�o��
#define FV_C11_STOP						(FV_FLAG_START+290)		//�X�g�b�p�[(c11,w230�Ŏg�p)
#define FV_D05R0112_GINGAW				(FV_FLAG_START+291)		//�M���K�c
#define FV_D27R0103_DOCTOR				(FV_FLAG_START+292)		//���m


//----------------------------------------------------------------------
//	�B���A�C�e���̃t���O(256��)
//
//	(FH_FLAG_START - FB_FLAG_START)
//	(    730      -    986      )
//----------------------------------------------------------------------
//
//

//----------------------------------------------------------------------
//	�t�B�[���h��̃A�C�e���̃t���O(256��)
//
//	(FB_FLAG_START - ??_FLAG_START)
//	(    986      -    1242      )
//----------------------------------------------------------------------
#define FV_FLD_ITEM_0					(FB_FLAG_START+0)
#define FV_FLD_ITEM_1					(FB_FLAG_START+1)
#define FV_FLD_ITEM_2					(FB_FLAG_START+2)
#define FV_FLD_ITEM_3					(FB_FLAG_START+3)
#define FV_FLD_ITEM_4					(FB_FLAG_START+4)
#define FV_FLD_ITEM_5					(FB_FLAG_START+5)
#define FV_FLD_ITEM_6					(FB_FLAG_START+6)
#define FV_FLD_ITEM_7					(FB_FLAG_START+7)
#define FV_FLD_ITEM_8					(FB_FLAG_START+8)
#define FV_FLD_ITEM_9					(FB_FLAG_START+9)
#define FV_FLD_ITEM_10					(FB_FLAG_START+10)
#define FV_FLD_ITEM_11					(FB_FLAG_START+11)
#define FV_FLD_ITEM_12					(FB_FLAG_START+12)
#define FV_FLD_ITEM_13					(FB_FLAG_START+13)
#define FV_FLD_ITEM_14					(FB_FLAG_START+14)
#define FV_FLD_ITEM_15					(FB_FLAG_START+15)
#define FV_FLD_ITEM_16					(FB_FLAG_START+16)
#define FV_FLD_ITEM_17					(FB_FLAG_START+17)
#define FV_FLD_ITEM_18					(FB_FLAG_START+18)
#define FV_FLD_ITEM_19					(FB_FLAG_START+19)
#define FV_FLD_ITEM_20					(FB_FLAG_START+20)
#define FV_FLD_ITEM_21					(FB_FLAG_START+21)
#define FV_FLD_ITEM_22					(FB_FLAG_START+22)
#define FV_FLD_ITEM_23					(FB_FLAG_START+23)
#define FV_FLD_ITEM_24					(FB_FLAG_START+24)
#define FV_FLD_ITEM_25					(FB_FLAG_START+25)
#define FV_FLD_ITEM_26					(FB_FLAG_START+26)
#define FV_FLD_ITEM_27					(FB_FLAG_START+27)
#define FV_FLD_ITEM_28					(FB_FLAG_START+28)
#define FV_FLD_ITEM_29					(FB_FLAG_START+29)
#define FV_FLD_ITEM_30					(FB_FLAG_START+30)
#define FV_FLD_ITEM_31					(FB_FLAG_START+31)
#define FV_FLD_ITEM_32					(FB_FLAG_START+32)
#define FV_FLD_ITEM_33					(FB_FLAG_START+33)
#define FV_FLD_ITEM_34					(FB_FLAG_START+34)
#define FV_FLD_ITEM_35					(FB_FLAG_START+35)
#define FV_FLD_ITEM_36					(FB_FLAG_START+36)
#define FV_FLD_ITEM_37					(FB_FLAG_START+37)
#define FV_FLD_ITEM_38					(FB_FLAG_START+38)
#define FV_FLD_ITEM_39					(FB_FLAG_START+39)
#define FV_FLD_ITEM_40					(FB_FLAG_START+40)
#define FV_FLD_ITEM_41					(FB_FLAG_START+41)
#define FV_FLD_ITEM_42					(FB_FLAG_START+42)
#define FV_FLD_ITEM_43					(FB_FLAG_START+43)
#define FV_FLD_ITEM_44					(FB_FLAG_START+44)
#define FV_FLD_ITEM_45					(FB_FLAG_START+45)
#define FV_FLD_ITEM_46					(FB_FLAG_START+46)
#define FV_FLD_ITEM_47					(FB_FLAG_START+47)
#define FV_FLD_ITEM_48					(FB_FLAG_START+48)
#define FV_FLD_ITEM_49					(FB_FLAG_START+49)
#define FV_FLD_ITEM_50					(FB_FLAG_START+50)
#define FV_FLD_ITEM_51					(FB_FLAG_START+51)
#define FV_FLD_ITEM_52					(FB_FLAG_START+52)
#define FV_FLD_ITEM_53					(FB_FLAG_START+53)
#define FV_FLD_ITEM_54					(FB_FLAG_START+54)
#define FV_FLD_ITEM_55					(FB_FLAG_START+55)
#define FV_FLD_ITEM_56					(FB_FLAG_START+56)
#define FV_FLD_ITEM_57					(FB_FLAG_START+57)
#define FV_FLD_ITEM_58					(FB_FLAG_START+58)
#define FV_FLD_ITEM_59					(FB_FLAG_START+59)
#define FV_FLD_ITEM_60					(FB_FLAG_START+60)
#define FV_FLD_ITEM_61					(FB_FLAG_START+61)
#define FV_FLD_ITEM_62					(FB_FLAG_START+62)
#define FV_FLD_ITEM_63					(FB_FLAG_START+63)
#define FV_FLD_ITEM_64					(FB_FLAG_START+64)
#define FV_FLD_ITEM_65					(FB_FLAG_START+65)
#define FV_FLD_ITEM_66					(FB_FLAG_START+66)
#define FV_FLD_ITEM_67					(FB_FLAG_START+67)
#define FV_FLD_ITEM_68					(FB_FLAG_START+68)
#define FV_FLD_ITEM_69					(FB_FLAG_START+69)
#define FV_FLD_ITEM_70					(FB_FLAG_START+70)
#define FV_FLD_ITEM_71					(FB_FLAG_START+71)
#define FV_FLD_ITEM_72					(FB_FLAG_START+72)
#define FV_FLD_ITEM_73					(FB_FLAG_START+73)
#define FV_FLD_ITEM_74					(FB_FLAG_START+74)
#define FV_FLD_ITEM_75					(FB_FLAG_START+75)
#define FV_FLD_ITEM_76					(FB_FLAG_START+76)
#define FV_FLD_ITEM_77					(FB_FLAG_START+77)
#define FV_FLD_ITEM_78					(FB_FLAG_START+78)
#define FV_FLD_ITEM_79					(FB_FLAG_START+79)
#define FV_FLD_ITEM_80					(FB_FLAG_START+80)
#define FV_FLD_ITEM_81					(FB_FLAG_START+81)
#define FV_FLD_ITEM_82					(FB_FLAG_START+82)
#define FV_FLD_ITEM_83					(FB_FLAG_START+83)
#define FV_FLD_ITEM_84					(FB_FLAG_START+84)
#define FV_FLD_ITEM_85					(FB_FLAG_START+85)
#define FV_FLD_ITEM_86					(FB_FLAG_START+86)
#define FV_FLD_ITEM_87					(FB_FLAG_START+87)
#define FV_FLD_ITEM_88					(FB_FLAG_START+88)
#define FV_FLD_ITEM_89					(FB_FLAG_START+89)
#define FV_FLD_ITEM_90					(FB_FLAG_START+90)
#define FV_FLD_ITEM_91					(FB_FLAG_START+91)
#define FV_FLD_ITEM_92					(FB_FLAG_START+92)
#define FV_FLD_ITEM_93					(FB_FLAG_START+93)
#define FV_FLD_ITEM_94					(FB_FLAG_START+94)
#define FV_FLD_ITEM_95					(FB_FLAG_START+95)
#define FV_FLD_ITEM_96					(FB_FLAG_START+96)
#define FV_FLD_ITEM_97					(FB_FLAG_START+97)
#define FV_FLD_ITEM_98					(FB_FLAG_START+98)
#define FV_FLD_ITEM_99					(FB_FLAG_START+99)
#define FV_FLD_ITEM_100					(FB_FLAG_START+100)
#define FV_FLD_ITEM_101					(FB_FLAG_START+101)
#define FV_FLD_ITEM_102					(FB_FLAG_START+102)
#define FV_FLD_ITEM_103					(FB_FLAG_START+103)
#define FV_FLD_ITEM_104					(FB_FLAG_START+104)
#define FV_FLD_ITEM_105					(FB_FLAG_START+105)
#define FV_FLD_ITEM_106					(FB_FLAG_START+106)
#define FV_FLD_ITEM_107					(FB_FLAG_START+107)
#define FV_FLD_ITEM_108					(FB_FLAG_START+108)
#define FV_FLD_ITEM_109					(FB_FLAG_START+109)
#define FV_FLD_ITEM_110					(FB_FLAG_START+110)
#define FV_FLD_ITEM_111					(FB_FLAG_START+111)
#define FV_FLD_ITEM_112					(FB_FLAG_START+112)
#define FV_FLD_ITEM_113					(FB_FLAG_START+113)
#define FV_FLD_ITEM_114					(FB_FLAG_START+114)
#define FV_FLD_ITEM_115					(FB_FLAG_START+115)
#define FV_FLD_ITEM_116					(FB_FLAG_START+116)
#define FV_FLD_ITEM_117					(FB_FLAG_START+117)
#define FV_FLD_ITEM_118					(FB_FLAG_START+118)
#define FV_FLD_ITEM_119					(FB_FLAG_START+119)
#define FV_FLD_ITEM_120					(FB_FLAG_START+120)
#define FV_FLD_ITEM_121					(FB_FLAG_START+121)
#define FV_FLD_ITEM_122					(FB_FLAG_START+122)
#define FV_FLD_ITEM_123					(FB_FLAG_START+123)
#define FV_FLD_ITEM_124					(FB_FLAG_START+124)
#define FV_FLD_ITEM_125					(FB_FLAG_START+125)
#define FV_FLD_ITEM_126					(FB_FLAG_START+126)
#define FV_FLD_ITEM_127					(FB_FLAG_START+127)
#define FV_FLD_ITEM_128					(FB_FLAG_START+128)
#define FV_FLD_ITEM_129					(FB_FLAG_START+129)
#define FV_FLD_ITEM_130					(FB_FLAG_START+130)
#define FV_FLD_ITEM_131					(FB_FLAG_START+131)
#define FV_FLD_ITEM_132					(FB_FLAG_START+132)
#define FV_FLD_ITEM_133					(FB_FLAG_START+133)
#define FV_FLD_ITEM_134					(FB_FLAG_START+134)
#define FV_FLD_ITEM_135					(FB_FLAG_START+135)
#define FV_FLD_ITEM_136					(FB_FLAG_START+136)
#define FV_FLD_ITEM_137					(FB_FLAG_START+137)
#define FV_FLD_ITEM_138					(FB_FLAG_START+138)
#define FV_FLD_ITEM_139					(FB_FLAG_START+139)
#define FV_FLD_ITEM_140					(FB_FLAG_START+140)
#define FV_FLD_ITEM_141					(FB_FLAG_START+141)
#define FV_FLD_ITEM_142					(FB_FLAG_START+142)
#define FV_FLD_ITEM_143					(FB_FLAG_START+143)
#define FV_FLD_ITEM_144					(FB_FLAG_START+144)
#define FV_FLD_ITEM_145					(FB_FLAG_START+145)
#define FV_FLD_ITEM_146					(FB_FLAG_START+146)
#define FV_FLD_ITEM_147					(FB_FLAG_START+147)
#define FV_FLD_ITEM_148					(FB_FLAG_START+148)
#define FV_FLD_ITEM_149					(FB_FLAG_START+149)
#define FV_FLD_ITEM_150					(FB_FLAG_START+150)
#define FV_FLD_ITEM_151					(FB_FLAG_START+151)
#define FV_FLD_ITEM_152					(FB_FLAG_START+152)
#define FV_FLD_ITEM_153					(FB_FLAG_START+153)
#define FV_FLD_ITEM_154					(FB_FLAG_START+154)
#define FV_FLD_ITEM_155					(FB_FLAG_START+155)
#define FV_FLD_ITEM_156					(FB_FLAG_START+156)
#define FV_FLD_ITEM_157					(FB_FLAG_START+157)
#define FV_FLD_ITEM_158					(FB_FLAG_START+158)
#define FV_FLD_ITEM_159					(FB_FLAG_START+159)
#define FV_FLD_ITEM_160					(FB_FLAG_START+160)
#define FV_FLD_ITEM_161					(FB_FLAG_START+161)
#define FV_FLD_ITEM_162					(FB_FLAG_START+162)
#define FV_FLD_ITEM_163					(FB_FLAG_START+163)
#define FV_FLD_ITEM_164					(FB_FLAG_START+164)
#define FV_FLD_ITEM_165					(FB_FLAG_START+165)
#define FV_FLD_ITEM_166					(FB_FLAG_START+166)
#define FV_FLD_ITEM_167					(FB_FLAG_START+167)
#define FV_FLD_ITEM_168					(FB_FLAG_START+168)
#define FV_FLD_ITEM_169					(FB_FLAG_START+169)
#define FV_FLD_ITEM_170					(FB_FLAG_START+170)
#define FV_FLD_ITEM_171					(FB_FLAG_START+171)
#define FV_FLD_ITEM_172					(FB_FLAG_START+172)
#define FV_FLD_ITEM_173					(FB_FLAG_START+173)
#define FV_FLD_ITEM_174					(FB_FLAG_START+174)
#define FV_FLD_ITEM_175					(FB_FLAG_START+175)
#define FV_FLD_ITEM_176					(FB_FLAG_START+176)
#define FV_FLD_ITEM_177					(FB_FLAG_START+177)
#define FV_FLD_ITEM_178					(FB_FLAG_START+178)
#define FV_FLD_ITEM_179					(FB_FLAG_START+179)
#define FV_FLD_ITEM_180					(FB_FLAG_START+180)
#define FV_FLD_ITEM_181					(FB_FLAG_START+181)
#define FV_FLD_ITEM_182					(FB_FLAG_START+182)
#define FV_FLD_ITEM_183					(FB_FLAG_START+183)
#define FV_FLD_ITEM_184					(FB_FLAG_START+184)
#define FV_FLD_ITEM_185					(FB_FLAG_START+185)
#define FV_FLD_ITEM_186					(FB_FLAG_START+186)
#define FV_FLD_ITEM_187					(FB_FLAG_START+187)
#define FV_FLD_ITEM_188					(FB_FLAG_START+188)
#define FV_FLD_ITEM_189					(FB_FLAG_START+189)
#define FV_FLD_ITEM_190					(FB_FLAG_START+190)
#define FV_FLD_ITEM_191					(FB_FLAG_START+191)
#define FV_FLD_ITEM_192					(FB_FLAG_START+192)
#define FV_FLD_ITEM_193					(FB_FLAG_START+193)
#define FV_FLD_ITEM_194					(FB_FLAG_START+194)
#define FV_FLD_ITEM_195					(FB_FLAG_START+195)
#define FV_FLD_ITEM_196					(FB_FLAG_START+196)
#define FV_FLD_ITEM_197					(FB_FLAG_START+197)
#define FV_FLD_ITEM_198					(FB_FLAG_START+198)
#define FV_FLD_ITEM_199					(FB_FLAG_START+199)
#define FV_FLD_ITEM_200					(FB_FLAG_START+200)
#define FV_FLD_ITEM_201					(FB_FLAG_START+201)
#define FV_FLD_ITEM_202					(FB_FLAG_START+202)
#define FV_FLD_ITEM_203					(FB_FLAG_START+203)
#define FV_FLD_ITEM_204					(FB_FLAG_START+204)
#define FV_FLD_ITEM_205					(FB_FLAG_START+205)
#define FV_FLD_ITEM_206					(FB_FLAG_START+206)
#define FV_FLD_ITEM_207					(FB_FLAG_START+207)
#define FV_FLD_ITEM_208					(FB_FLAG_START+208)
#define FV_FLD_ITEM_209					(FB_FLAG_START+209)
#define FV_FLD_ITEM_210					(FB_FLAG_START+210)
#define FV_FLD_ITEM_211					(FB_FLAG_START+211)
#define FV_FLD_ITEM_212					(FB_FLAG_START+212)
#define FV_FLD_ITEM_213					(FB_FLAG_START+213)
#define FV_FLD_ITEM_214					(FB_FLAG_START+214)
#define FV_FLD_ITEM_215					(FB_FLAG_START+215)
#define FV_FLD_ITEM_216					(FB_FLAG_START+216)
#define FV_FLD_ITEM_217					(FB_FLAG_START+217)
#define FV_FLD_ITEM_218					(FB_FLAG_START+218)
#define FV_FLD_ITEM_219					(FB_FLAG_START+219)
#define FV_FLD_ITEM_220					(FB_FLAG_START+220)
#define FV_FLD_ITEM_221					(FB_FLAG_START+221)
#define FV_FLD_ITEM_222					(FB_FLAG_START+222)
#define FV_FLD_ITEM_223					(FB_FLAG_START+223)
#define FV_FLD_ITEM_224					(FB_FLAG_START+224)
#define FV_FLD_ITEM_225					(FB_FLAG_START+225)
#define FV_FLD_ITEM_226					(FB_FLAG_START+226)
#define FV_FLD_ITEM_227					(FB_FLAG_START+227)
#define FV_FLD_ITEM_228					(FB_FLAG_START+228)
#define FV_FLD_ITEM_229					(FB_FLAG_START+229)
#define FV_FLD_ITEM_230					(FB_FLAG_START+230)
#define FV_FLD_ITEM_231					(FB_FLAG_START+231)
#define FV_FLD_ITEM_232					(FB_FLAG_START+232)
#define FV_FLD_ITEM_233					(FB_FLAG_START+233)
#define FV_FLD_ITEM_234					(FB_FLAG_START+234)
#define FV_FLD_ITEM_235					(FB_FLAG_START+235)
#define FV_FLD_ITEM_236					(FB_FLAG_START+236)
#define FV_FLD_ITEM_237					(FB_FLAG_START+237)
#define FV_FLD_ITEM_238					(FB_FLAG_START+238)
#define FV_FLD_ITEM_239					(FB_FLAG_START+239)
#define FV_FLD_ITEM_240					(FB_FLAG_START+240)
#define FV_FLD_ITEM_241					(FB_FLAG_START+241)
#define FV_FLD_ITEM_242					(FB_FLAG_START+242)
#define FV_FLD_ITEM_243					(FB_FLAG_START+243)
#define FV_FLD_ITEM_244					(FB_FLAG_START+244)
#define FV_FLD_ITEM_245					(FB_FLAG_START+245)
#define FV_FLD_ITEM_246					(FB_FLAG_START+246)
#define FV_FLD_ITEM_247					(FB_FLAG_START+247)
#define FV_FLD_ITEM_248					(FB_FLAG_START+248)
#define FV_FLD_ITEM_249					(FB_FLAG_START+249)
#define FV_FLD_ITEM_250					(FB_FLAG_START+250)
#define FV_FLD_ITEM_251					(FB_FLAG_START+251)
#define FV_FLD_ITEM_252					(FB_FLAG_START+252)
#define FV_FLD_ITEM_253					(FB_FLAG_START+253)
#define FV_FLD_ITEM_254					(FB_FLAG_START+254)
#define FV_FLD_ITEM_255					(FB_FLAG_START+255)



//----------------------------------------------------------------------
//	�P���P��N���A�����t���O(192��)
//
//	���X�N���v�g�݂̂ŃZ�b�g���違�������Ȃ��̂�saveflag.h�œ���
// 	(TIMEFLAG_START - )
//----------------------------------------------------------------------
// TIMEFLAG_START ��evwkdef.h�Œ�`
#define TMFLG_SEED_PRESENT			(TIMEFLAG_START+0)		/* �^�l�̃v���[���g */
#define TMFLG_T05PC0101_ITEM_GET	(TIMEFLAG_START+1)		/* �A�C�e���v���[���g */
#define TMFLG_URANIWA_ENCOUNT		(TIMEFLAG_START+2)		/* ����G���J�E���g�p */
#define TMFLG_C06R0201_SEED_PRESENT	(TIMEFLAG_START+3)		/* �^�l�̃v���[���g */
#define TMFLG_C08R0201_RIBBON_GET	(TIMEFLAG_START+4)		/* ���{�����Q�b�g */
#define TMFLG_T07R0101_ESTHTIQUE	(TIMEFLAG_START+5)		/* �G�X�e���󂯂� */
#define TMFLG_C08R0201_WEEK_TALK	(TIMEFLAG_START+6)		/* ���˂���Ɖ�b���� */
#define TMFLG_C08R0201_FIRST_DAY	(TIMEFLAG_START+7)		/* ���˂���Ɖ�b����1���� */
#define TMFLG_D02_FUUSEN			(TIMEFLAG_START+8)		/* �t�[�Z�� */
#define TMFLG_KUJI_DAY				(TIMEFLAG_START+9)		/* �����������͂���� */
#define TMFLG_T03R0101_SEED_PRESENT	(TIMEFLAG_START+10)		/* �^�l�̃v���[���g */
#define TMFLG_L02R0101_INIT			(TIMEFLAG_START+11)		/* ���X�g�����������p */
#define TMFLG_C07R0801_DRESSING		(TIMEFLAG_START+12)		/* ���������o���� */
#define TMFLG_C09R0201_NANKAI		(TIMEFLAG_START+13)		/* �ȈՉ�b�F������t���� */
#define TMFLG_R221R0201_ITEM_GET	(TIMEFLAG_START+14)		/* �A�C�e������ */
#define TMFLG_C01R0201_BATTLE_END	(TIMEFLAG_START+15)		/* �j�����ɕς��g���[�i�[�Ƃ̑ΐ�I�� */
#define TMFLG_D25R0106_SPPOKE_END	(TIMEFLAG_START+16)		/* d25r0106�v���Y�}����I�� */
#define TMFLG_T04R0301_NEWS_END		(TIMEFLAG_START+17)		/* �����̈˗��I�� */
#define TMFLG_C11_RIVAL_BTL			(TIMEFLAG_START+18)		/* c11���C�o���퓬 */


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
#endif	//__SAVEFLAG_H__

