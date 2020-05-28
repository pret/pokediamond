//==============================================================================================
/**
 * @file	savework.h
 * @brief	�Q�[�����Z�[�u���[�N��`(�X�N���v�g����̂݃A�N�Z�X����郏�[�N)
 * @author	tomo
 * @date	2005.10.22
 */
//==============================================================================================
#ifndef	__SAVEWORK_H__
#define	__SAVEWORK_H__

//----------------------------------------------------------------------------------------------
//0-31�́A���[�J�����[�N�Ƃ��Ďg�p
//MAX = evwkdef.h LOCAL_WORK_MAX
//----------------------------------------------------------------------------------------------
#define	 LOCALWORK0					(0+LOCAL_WORK_START)
#define	 LOCALWORK1					(1+LOCAL_WORK_START)
#define	 LOCALWORK2					(2+LOCAL_WORK_START)
#define	 LOCALWORK3					(3+LOCAL_WORK_START)
#define	 LOCALWORK4					(4+LOCAL_WORK_START)
#define	 LOCALWORK5					(5+LOCAL_WORK_START)
#define	 LOCALWORK6					(6+LOCAL_WORK_START)
#define	 LOCALWORK7					(7+LOCAL_WORK_START)
#define	 LOCALWORK8					(8+LOCAL_WORK_START)
#define	 LOCALWORK9					(9+LOCAL_WORK_START)
#define	 LOCALWORK10				(10+LOCAL_WORK_START)
#define	 LOCALWORK11				(11+LOCAL_WORK_START)
#define	 LOCALWORK12				(12+LOCAL_WORK_START)
#define	 LOCALWORK13				(13+LOCAL_WORK_START)
#define	 LOCALWORK14				(14+LOCAL_WORK_START)
#define	 LOCALWORK15				(15+LOCAL_WORK_START)
#define	 LOCALWORK16				(16+LOCAL_WORK_START)
#define	 LOCALWORK17				(17+LOCAL_WORK_START)
#define	 LOCALWORK18				(18+LOCAL_WORK_START)
#define	 LOCALWORK19				(19+LOCAL_WORK_START)
#define	 LOCALWORK20				(20+LOCAL_WORK_START)
#define	 LOCALWORK21				(21+LOCAL_WORK_START)
#define	 LOCALWORK22				(22+LOCAL_WORK_START)
#define	 LOCALWORK23				(23+LOCAL_WORK_START)
#define	 LOCALWORK24				(24+LOCAL_WORK_START)
#define	 LOCALWORK25				(25+LOCAL_WORK_START)
#define	 LOCALWORK26				(26+LOCAL_WORK_START)
#define	 LOCALWORK27				(27+LOCAL_WORK_START)
#define	 LOCALWORK28				(28+LOCAL_WORK_START)
#define	 LOCALWORK29				(29+LOCAL_WORK_START)
#define	 LOCALWORK30				(30+LOCAL_WORK_START)
#define	 LOCALWORK31				(31+LOCAL_WORK_START)

//----------------------------------------------------------------------------------------------
//32-47�́A�ύXOK��OBJ�L�����w��Ƃ��Ďg�p
//MAX = evwkdef.h OBJCHR_WORK_MAX
//----------------------------------------------------------------------------------------------
#define	 OBJCHRWORK0				(0+OBJCHR_WORK_START)
#define	 OBJCHRWORK1				(1+OBJCHR_WORK_START)
#define	 OBJCHRWORK2				(2+OBJCHR_WORK_START)
#define	 OBJCHRWORK3				(3+OBJCHR_WORK_START)
#define	 OBJCHRWORK4				(4+OBJCHR_WORK_START)
#define	 OBJCHRWORK5				(5+OBJCHR_WORK_START)
#define	 OBJCHRWORK6				(6+OBJCHR_WORK_START)
#define	 OBJCHRWORK7				(7+OBJCHR_WORK_START)
#define	 OBJCHRWORK8				(8+OBJCHR_WORK_START)
#define	 OBJCHRWORK9				(9+OBJCHR_WORK_START)
#define	 OBJCHRWORK10				(10+OBJCHR_WORK_START)
#define	 OBJCHRWORK11				(11+OBJCHR_WORK_START)
#define	 OBJCHRWORK12				(12+OBJCHR_WORK_START)
#define	 OBJCHRWORK13				(13+OBJCHR_WORK_START)
#define	 OBJCHRWORK14				(14+OBJCHR_WORK_START)
#define	 OBJCHRWORK15				(15+OBJCHR_WORK_START)

//------------------------------------------------------------------------
//							�t�B�[���h�^�E��
//------------------------------------------------------------------------
#define WK_SCENE_T01					(SVSCRWK_START+0)
/* �t�^�o�^�E���C�x���g
01 �Q�[���J�n������1
02 ���C�o���Ɖ�b���āAT01�̃X�g�b�p�[����
*/

#define WK_SCENE_T02					(SVSCRWK_START+1)
/* �}�T�S�^�E���C�x���g
01 �������ւ̗U���C�x���g�I��
02 �T�|�[�g�̋����C�x���g�I��
*/

#define WK_SCENE_T03					(SVSCRWK_START+2)
/* �\�m�I�^�E���C�x���g
01 �M���K�c�{�X�C�x���g�I��
*/

#define WK_SCENE_T04					(SVSCRWK_START+3)

#define WK_SCENE_T05					(SVSCRWK_START+4)
/* �J���i�M�^�E���C�x���g
01 �M���K�c�{�X��b�C�x���g�J�n
02 �M���K�c�{�X��b�C�x���g�I��
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+5)

//#define WK_SCENE_NONE					(SVSCRWK_START+6)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�t�B�[���h�V�e�B
//------------------------------------------------------------------------
#define WK_SCENE_C01					(SVSCRWK_START+7)
/* �R�g�u�L�V�e�B�C�x���g
01 �T�|�[�g�C�x���g�I��
02 �|�P�b�`���肵��
03 �M���K�c�C�x���g�J�n
04 �M���K�c�C�x���g�I��
*/

#define WK_SCENE_C02					(SVSCRWK_START+8)
/* �~�I�V�e�B�C�x���g
01 ���C�o���퓬�ɏ���
02 ���C�o���}���قֈړ��C�x���g�J�n
03 ���C�o���}���قֈړ��C�x���g�I��
04 �}���كC�x���g�I����̔��m�C�x���g�J�n
05 �}���كC�x���g�I����̔��m�C�x���g�I��
06 ���C�x���g��Ƀ}�b�v�؂�ւ��Ė߂��Ă���
*/

#define WK_SCENE_C03					(SVSCRWK_START+9)
/* �N���K�l�V�e�B�C�x���g
01 �W���U���C�x���g�I��
02 �W���N���A���ă��C�o���C�x���g�J�n
03 ���C�o���C�x���g�I��
*/

#define WK_SCENE_C04					(SVSCRWK_START+10)
/*�n�N�^�C�V�e�B
01 �`�����s�I���ɂ��������������� 
*/

#define WK_SCENE_C05					(SVSCRWK_START+11)
/*���X�K�V�e�B
01 ���C�o���C�x���g�J�n
02 ���C�o���C�x���g�I��
*/

#define WK_SCENE_C06					(SVSCRWK_START+12)
/*�m���Z�V�e�B
1 �W���N���A
*/

#define WK_SCENE_C07					(SVSCRWK_START+13)
/*�g�o���V�e�B
01 �W���N���A(�q�ɑO�C�x���g��POS�Ɏg�p)
*/

#define WK_SCENE_C08					(SVSCRWK_START+14)
/*�i�M�T�V�e�B
01 �W�����[�_�[�C�x���g�I��
02 �~�J���C�x���g�I��
*/

#define WK_SCENE_C09					(SVSCRWK_START+15)
/*�L�b�T�L�V�e�B
01 �_�a�X�g�b�p�[�I��
*/

#define WK_SCENE_C10					(SVSCRWK_START+16)

#define WK_SCENE_C11					(SVSCRWK_START+17)
/*�H�H�V�e�B
00 ���C�o���ƂT�l�O�C�x���g�J�n(c11�ɏ��߂ē�������)
01 ���C�o���ƂT�l�O�C�x���g�I��
*/

//------------------------------------------------------------------------
//							�t�B�[���h�݂�����
//------------------------------------------------------------------------
#define WK_SCENE_L01					(SVSCRWK_START+18)
/* ��
01 �΂ֈړ��C�x���g�I��
02 �΂���A���Ă��ĘA������Z�b�g
03 �΂���A���Ă��ĘA������Z�b�g�I��
04 ����֋A��C�x���g�I��(�΂Ɉ����Ԃ��Ȃ�POS�I��)
*/

#define WK_SCENE_L02					(SVSCRWK_START+19)
/* ��(���g�p)
02 �`�����s�I���C�x���g�I��
*/

#define WK_SCENE_L03					(SVSCRWK_START+20)

#define WK_SCENE_L04					(SVSCRWK_START+21)

//------------------------------------------------------------------------
//							�t�B�[���h���[�h
//------------------------------------------------------------------------
#define WK_SCENE_R201					(SVSCRWK_START+22)
/* ���C�o���o��C�x���g
01 �A������J�n
02 ���m�Ɖ�C�x���g�J�n
03 ���m�Ɖ�C�x���g�I��
*/

#define WK_SCENE_R202					(SVSCRWK_START+23)
/* �T�|�[�g�ߊl�f��
01 �C�x���g�I��
*/

#define WK_SCENE_R203					(SVSCRWK_START+24)
/* ���C�o���o��C�x���g
01 �C�x���g�I��
*/

#define WK_SCENE_R205A					(SVSCRWK_START+25)
/* �M���K�c�C�x���g
01 �����C�x���g�I��
02 �M���K�c�C�x���g�I��
*/

#define WK_SCENE_R209					(SVSCRWK_START+26)
/* �݂��܂̂Ƃ�
01 ���Ȃ߂������g����
02 �~�J�Q�Ɛ퓬��
*/

#define WK_SCENE_R227					(SVSCRWK_START+27)
/* R227�C�x���g
01 �W�����[�_�[�ƃ��C�o���C�x���g�I��
*/

#define WK_SCENE_R207					(SVSCRWK_START+28)

#define WK_SCENE_R224					(SVSCRWK_START+29)
/* R224�C�x���g
01 �G�E���X�Δ�C�x���g��
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+30)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+31)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�����̒�(�_���W����)
//------------------------------------------------------------------------
#define WK_SCENE_D09R0104				(SVSCRWK_START+32)
/* �`�����s�I�����[�h
00 �A������I��
01 �A������J�n
02 �S�[���ɂ���
*/

#define WK_SCENE_D21R0101				(SVSCRWK_START+33)
/* �����̓��A
00 �A������I��
01 �A������J�n
02 �S�[���ɂ���
*/

#define WK_SCENE_D24R0105				(SVSCRWK_START+34)
/* �|�S��
00 �A������I��
01 �A������J�n
02 �S�[���ɂ���
*/

#define WK_SCENE_D14R0101				(SVSCRWK_START+35)
/* �N���K�l�Q�[�g
01 ��`����C�x���g�J�n
02 ��`����C�x���g�I��
*/

#define WK_SCENE_D16R0102				(SVSCRWK_START+36)
/* �ΎR�Q�K
00 �A������I��
01 �A������J�n
02 �S�[���ɂ���
*/

#define WK_SCENE_D27R0101				(SVSCRWK_START+37)
/* �΃C�x���g
01 �|�P�������肵��
*/

#define WK_SCENE_D05R0101				(SVSCRWK_START+38)
/* �e���K���R�C�x���g
01 �{�X�C�x���g�I��
*/

#define WK_SCENE_D27R0102				(SVSCRWK_START+39)
/* �΃C�x���g
01 ���m���`���|�P�����������Ă��ꋭ���C�x���g�I��
*/

#define	WK_SCENE_D05R0114				(SVSCRWK_START+40)
/* �e���K���R�R���C�x���g
00	������ԁA�M���K�c�U�R�Ƒΐ�
01	POS�ŃC�A�i�G�A�j�o���
02	POS�ŃM���K�c�����ƃ}���`�o�g���J�n���f�����{�X��
03	POS�ŃC�A�i�G�A�j�ΐ�ց��T�|�[�g�����m�o��A�C�x���g�N���A
04	�C�x���g�I�����
05	�N���A��B���C�x���g�֑����c
 */

#define WK_SCENE_D11R0101				(SVSCRWK_START+41)
/* �ӂꂠ���L��
00 �A������O
01 �A�������
 */

#define WK_SCENE_D11R0101_MONSNO              (SVSCRWK_START+42)
/* �A��Ă���|�P�����i���o�[
 */

#define WK_SCENE_D11R0101_PRESENT		(SVSCRWK_START+43)
/* �Ⴆ����̂̎��
00 ���̂�
01 �A�N�Z�T���[
 */

#define WK_SCENE_D11R0101_PRESENT_ACCE_NO	(SVSCRWK_START+44)
/* �Ⴆ��A�N�Z�T���[�i���o�[
 */

#define WK_SCENE_D11R0101_TNO        (SVSCRWK_START+45)
/* �A��Ă���|�P�����̎莝���i���o�[
 */

#define WK_SCENE_D16R0103				(SVSCRWK_START+46)
/* �ΎR�R�K
01 ������̂��������C�x���g�I��
*/

#define WK_SCENE_D11R0101_PRESENT_KINOMI_NO	(SVSCRWK_START+47)
/* �Ⴆ�邫�̂݃i���o�[
 */

//#define WK_SCENE_NONE					(SVSCRWK_START+48)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+49)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�����̒�(�^�E��)
//------------------------------------------------------------------------
#define WK_SCENE_T01R0101				(SVSCRWK_START+50)

#define WK_SCENE_T01R0102				(SVSCRWK_START+51)
/* ���C�o��2�K�C�x���g
01 ���C�o���o���C�x���g�I��
*/

#define WK_SCENE_T01R0201				(SVSCRWK_START+52)
/* ����1�K�C�x���g
01 2�K����~��Ă�����b�I��
02 �O�o���悤�Ƃ��ă}�}�Ƃ̉�b�I��
03 �V���[�Y�C�x���g�J�n
04 �V���[�Y���������
05 �V���[�Y��������ĊO�ɏo��
06 �`���m�[�g����C�x���g�I��
07 �`���m�[�g����C�x���g��ɊO�ɏo�Ė߂��Ă���
*/

#define WK_SCENE_T01R0202				(SVSCRWK_START+53)
/* ����2�K�C�x���g ��060801���݁@���g�p
01 �����ݒ�I��
*/

#define WK_SCENE_T02R0101				(SVSCRWK_START+54)

#define WK_SCENE_T07R0101				(SVSCRWK_START+55)
/* 
00 ����ɂȂ�邩�`�F�b�N
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+56)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+57)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+58)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+59)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+60)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�����̒�(�V�e�B)
//------------------------------------------------------------------------
#define WK_SCENE_C01R0101				(SVSCRWK_START+61)
#define WK_SCENE_C04GYM0102				(SVSCRWK_START+62)

#define WK_SCENE_C01R0701				(SVSCRWK_START+63)
/* �g���[�i�[�X�N�[���C�x���g
01 �|�P�b�`�C�x���g�J�n
02 �|�P�b�`�C�x���g�I��
*/

#define WK_SCENE_C01R0201				(SVSCRWK_START+64)
/* TV�ǃC�x���g
*/

#define WK_SCENE_D03R0101				(SVSCRWK_START+65)
/* �n�N�^�C�̐X�����C�x���g
01 �A������J�n
02 �A������S�[���ɂ���
*/

#define WK_SCENE_C02R0103				(SVSCRWK_START+66)
/* �}���قR�K�C�x���g
01 �݂�Ȃ��낤�C�x���g�J�n
02 �݂�Ȃ��낤�C�x���g�I��
*/

#define WK_SCENE_C03R0401				(SVSCRWK_START+67)
/* ���΃C�x���g
01 ���Ηa���蒆
02 �|�P�����a���蒆
*/

#define WK_SCENE_KASEKI_MONSNO			(SVSCRWK_START+68)
/* ���΃C�x���g
xxxx �|�P�����ԍ�
*/

#define WK_SCENE_C08R0701				(SVSCRWK_START+69)
/* �|�P�b�`�}�j�A
00 ��b�O
01 ��b����
02 �|�P�b�`�A�v��1�ړ���
03 �|�P�b�`�A�v��2�ړ���
04 �|�P�b�`�A�v��3�ړ���
*/

#define WK_SCENE_C08R0401				(SVSCRWK_START+70)
/* �T�����
01 �~�b�V�����P�N���A 
02 �~�b�V�����Q�N���A 
03 �~�b�V�����R�N���A 
04 �~�b�V�����S�N���A 
05 �~�b�V�����T�N���A 
06 �~�b�V�����U�N���A 
07 �n�^�R�{�ȏ�̕\���ς�
08 �n�^�P�O�{�ȏ�̕\���ς�
09 �����}�X�^�[�i�n�^�T�O�{�ȏ�̕\���ς݁j
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+71)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+72)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+73)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+74)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+75)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+76)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+77)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+78)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+79)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�����̒�(�݂�����)
//------------------------------------------------------------------------
#define WK_SCENE_L01R0101				(SVSCRWK_START+80)

//#define WK_SCENE_NONE					(SVSCRWK_START+81)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+82)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+83)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+84)		//�����g�p���[�N

//------------------------------------------------------------------------
//							�����̒�(���[�h)
//180�`219�܂Ŏg�p
//------------------------------------------------------------------------
#define WK_SCENE_R201R0101				(SVSCRWK_START+85)

#define WK_SCENE_R221R0101				(SVSCRWK_START+86)
/*
00 �I�[�L�h���҂��Ă���
01 �I�[�L�h��������
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+87)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+88)		//�����g�p���[�N

//#define WK_SCENE_NONE					(SVSCRWK_START+89)		//�����g�p���[�N

//------------------------------------------------------------------------
//							���̑�
//------------------------------------------------------------------------
#define WK_SCENE_PAIR_R201_RIVAL		(SVSCRWK_START+90)
/* R201�A��������C�o���C�x���g
01 ��b1
02 ��b2
03 ��b3
04 ��b4
05 ��b5
*/

#define WK_SCENE_PAIR_L01_RIVAL			(SVSCRWK_START+91)
/* L01�A��������C�o���C�x���g
01 ��b1
02 ��b2
03 ��b3
*/

#define WK_SCENE_CONTEST				(SVSCRWK_START+92)
/* �R���e�X�g
00 �������Ă��Ȃ�
01 �R���e�X�g��
02 �G���f�B���O��
*/

#define WK_SCENE_D03R0101_GHOST			(SVSCRWK_START+93)
/* �n�N�^�C�̐X�̗H��C�x���g(���g�p)
01 5�l�O�Ɖ�b����
*/

#define WK_ELEVATOR_FLOOR				(SVSCRWK_START+94)
/* �G���x�[�^�t���A���[�N
*/

#define WK_SCENE_D02R0101				(SVSCRWK_START+95)
/* ���d����
01 �M���K�c�C�x���g�I��
02 �M���K�c����POS�C�x���g�I��
*/

#define WK_SCENE_UG						(SVSCRWK_START+96)
/* �n��
01 ����R�j�C�x���g�I��
*/

#define WK_SCENE_C05_MAIN				(SVSCRWK_START+97)
/* ���X�K�V�e�B�C�x���g
01 �W���N���A��̃`�����s�I���C�x���g�J�n
02 �W���N���A��̃`�����s�I���C�x���g�I��
*/

//#define WK_SCENE_PC_UG					(SVSCRWK_START+98)
/* �|�P�Z���n���C�x���g
//01 ����Ƃ������Ă��傤����C�x���g�I��
*/

#define WK_SCENE_D29R0102				(SVSCRWK_START+99)
/* �΃C�x���g
01 ���C�o����������C�x���g�J�n
02 ���C�o����������C�x���g�I��
*/

#define WK_SCENE_PC0103					(SVSCRWK_START+100)
/* �|�P�Z���n��
01 �}�~�i�C�x���g�I��(�Ƃ������Ă��傤�C�x���g)
*/

#define WK_SCENE_COMM_ID				(SVSCRWK_START+101)
/* �X�N���v�g�ʐM��tID
00 �����Ȃ�
01 �o�g��
02 ���j�I��
03 ���R�[�h
04 WiFi
*/

#define WK_SCENE_D26R0104				(SVSCRWK_START+102)
/* �M���K�c�A�W�g
01 �{�X�C�x���g�I��
*/

#define WK_SCENE_SAFARI_GATE			(SVSCRWK_START+103)
/* �T�t�@�������
*/

#define WK_SCENE_D31R0201				(SVSCRWK_START+104)
/*
00 �����Ȃ�
01 �v���C�I������t
02 ��������v���C����t
*/

#define WK_SCENE_D31R0205				(SVSCRWK_START+105)
/* �o�g���^���[�V���O���o�g���ΐ핔��
00 �ŏ��ɕ����ɓ���Ƃ�
01 �A�펞
 */

#define WK_SCENE_SAFARI_ZONE			(SVSCRWK_START+106)
/* �T�t�@������p
00:�T�t�@���ɓ���O
01:�T�t�@����
02:�T�t�@���I��
03:�{�[�����Ȃ��Ȃ��ăT�t�@���I��	�����݋��ʂ�"2"�ɂ��Ă���
*/

#define WK_SCENE_D31R0202				(SVSCRWK_START+107)
/* �o�g���^���[�G���x�[�^����
00 �Ȃɂ��Ȃ�
01 �C�x���g�N����
 */

#define WK_SCENE_D31R0203				(SVSCRWK_START+108)
/* �o�g���^���[�V���O���ʘH
00 �Ȃɂ��Ȃ�
01 �C�x���g�N����
 */

#define WK_SCENE_D31R0204				(SVSCRWK_START+109)
/* �o�g���^���[�}���`�ʘH
00 �Ȃɂ��Ȃ�
01 �C�x���g�N����
 */

#define WK_SCENE_D31R0206				(SVSCRWK_START+110)
/* �o�g���^���[�}���`�ΐ핔��
00 �Ȃɂ��Ȃ�
01 �C�x���g�N����
 */

#define WK_SCENE_D31R0207				(SVSCRWK_START+111)
/* �o�g���^���[�}���`�T����
 * 00 �Ȃɂ��Ȃ�
01 �C�x���g�N����
 */

#define WK_SCENE_POKE_PARK				(SVSCRWK_START+112)
/* 
01 �|�P�p�[�N��
*/

#define WK_SCENE_PAIR_D16R0102_SEVEN5	(SVSCRWK_START+113)
/* d16r0102�A������T�l�O�C�x���g
00 ��b0
01 ��b1
02 ��b2
03 ��b3
*/

#define WK_SCENE_PAIR_D21R0101_SEVEN2	(SVSCRWK_START+114)
/* d21r0101�A������T�l�O�C�x���g
00 ��b0
01 ��b1
02 ��b2
03 ��b3
*/

#define WK_SCENE_PAIR_D24R0105_SEVEN3	(SVSCRWK_START+115)
/* d24r0105�A������T�l�O�C�x���g
00 ��b0
01 ��b1
02 ��b2
03 ��b3
*/

#define WK_SCENE_PAIR_D09R0104_SEVEN4	(SVSCRWK_START+116)
/* d09r0104�A������T�l�O�C�x���g
00 ��b0
01 ��b1
02 ��b2
03 ��b3
*/

#define WK_SCENE_NEWS_MONSNO			(SVSCRWK_START+117)
/* �V���ЂŒT���Ă���|�P����
00 �˗��O 
01�`�@�˗���B�|�P����No
*/

#define WK_SCENE_T01_RIVAL				(SVSCRWK_START+118)
/* �t�^�o�@���C�o���C�x���g
01 ���C�o���Ƃ̑O�łԂ���C�x���g�I��
*/

#define WK_SCENE_C01_RIVAL				(SVSCRWK_START+119)
/* �R�g�u�L ���C�o���C�x���g
01 �|�P�b�`�C�x���g�J�n
02 �|�P�b�`�C�x���g�I��
*/

#define WK_SCENE_PAIR_D03R0101_SEVEN1	(SVSCRWK_START+120)
/* d03r0101�A������T�l�O�C�x���g
00 ��b0
01 ��b1
02 ��b2
*/

#define WK_SCENE_D13R0101				(SVSCRWK_START+121)
/* �\�m�I�Ԕ�
01 �M���K�c�C�x���g�I��
*/

#define WK_SCENE_C05_RIVAL				(SVSCRWK_START+122)
/* ���X�K�V�e�B�C�x���g
01 ���C�o���C�x���g�J�n
02 ���C�o���C�x���g�I��
*/

#define WK_SCENE_C05R1101				(SVSCRWK_START+123)
/* �R���e�X�g��t�C�x���g
01 �}�}�C�x���g�I��
*/

#define WK_SCENE_BICYCLE				(SVSCRWK_START+124)
/* �T�C���N�����O�Q�[�g
01 �X�g�b�p�[����
*/

#define	WK_SCENE_POSTMAN				(SVSCRWK_START+125)
/* �ӂ����z�B������p���[�N
 * �Z�[�u����K�v�͂Ȃ���FLAG_CHANGE���x���ő��삷�邽�ߊm�ۂ��Ă���
 */

#define WK_SCENE_T03_ZUKAN				(SVSCRWK_START+126)		//���ݎg�p�����iMake�̊֌W�ł܂��c���Ă��܂��j
/*�}�ӂ̃p���[�A�b�v�C�x���g(�I�X���X�ǉ��j
01�@�C�x���g�I��
*/

#define WK_SCENE_C10R0101				(SVSCRWK_START+127)
/* �|�P�������[�O
01 ���C�o���C�x���g�I��
*/

#define WK_SCENE_C01_GTC				(SVSCRWK_START+128)
/* GTC�X�g�b�p�[
01 �X�g�b�p�[�C�x���g�I��
*/

#define WK_SCENE_T05_OLDWOMAN			(SVSCRWK_START+129)
/* �J���i�M�^�E��2
01 ���V�C�x���g
*/

#define WK_SCENE_KUJI_AZUKE_ITEM		(SVSCRWK_START+130)
/* �a���Ă���܁i�P�`�S�j
00 �a���Ă��Ȃ�
01 �P��
02 �Q��
03 �R��
04 �S��
05 ����
*/

#define	WK_SCENE_D10R0101				(SVSCRWK_START+131)

#define WK_SCENE_DENDOU					(SVSCRWK_START+132)
/* ����a��
01 �a������f�[�^����
02 �N���A��̏���C�x���g�I��
*/

#define WK_SCENE_C07_SUPPORT			(SVSCRWK_START+133)
/*�g�o���V�e�B
01 �W���O�T�|�[�g�C�x���g�I�� 
*/

#define WK_SCENE_C05_JUDGE				(SVSCRWK_START+134)
/* ���X�K�V�e�B�C�x���g
01 �~�~�B�̃C�x���g�I��
*/

#define WK_SCENE_C05R1101_JUDGE			(SVSCRWK_START+135)
/* ���X�K�V�e�B�C�x���g
01 �~�~�B�̃C�x���g�I��
*/

#define WK_SCENE_C02R0401				(SVSCRWK_START+136)
/* �_�[�N�C�x���g
01 �_�[�N�C�x���g�J�n�C�x���g�F�J�n
02 �_�[�N�C�x���g�I���C�x���g�F�J�n
03 �_�[�N�C�x���g�I���C�x���g�F�I��
04 �_�[�N�C�x���g���̌�C�x���g�F�I��
*/

#define WK_SCENE_GAME_START				(SVSCRWK_START+137)
/* �Q�[���X�^�[�g�C�x���g
01 �Q�[���X�^�[�g�C�x���g�I��
*/

#define WK_SCENE_D20R0106				(SVSCRWK_START+138)
/* ���W�L���O�C�x���g
01 ���W�L���O�����
02 ���W�L���O����s��
03 ���W�L���O����I��
*/

#define WK_SCENE_L02R0101_P01			(SVSCRWK_START+139)
/* �J�b�v���P�̉�b
00 ���t
01 �I�[�h�u��
02 ���C���f�B�b�V��
03 �f�U�[�g
*/

#define WK_SCENE_L02R0101_P02			(SVSCRWK_START+140)

#define WK_SCENE_L02R0101_P03			(SVSCRWK_START+141)

#define WK_SCENE_L02R0101_P04			(SVSCRWK_START+142)

#define WK_SCENE_L02R0101_P05			(SVSCRWK_START+143)

#define WK_SCENE_L02R0101_P06			(SVSCRWK_START+144)

#define WK_SCENE_L02R0101_P07			(SVSCRWK_START+145)

#define WK_SCENE_L02R0101_P08			(SVSCRWK_START+146)

#define WK_SCENE_L02R0101_P09			(SVSCRWK_START+147)

#define WK_SCENE_L02R0101_CLOSE			(SVSCRWK_START+148)
/* ���X�g�����X�����֘A
01 �X������
*/

#define WK_SCENE_R218R0201_ZUKAN		(SVSCRWK_START+149)
/*�}�ӂ̃p���[�A�b�v�C�x���g(�I�X���X�ǉ��j
01�@�C�x���g�I��
*/

#define WK_SCENE_C02R0501				(SVSCRWK_START+150)
/** �~�I�V�e�B �D���i�~�L�̉Ƃ̃��[�o�X�C�x���g
 01	�����C�x���g�J�n
 02	�����C�x���g��
 03 �����C�x���g��������`��x�Ƃ��o��܂�
 */

#define WK_SCENE_C07R0201_GET_ACCE_NO		(SVSCRWK_START+151)
/** ������A�N�Z�T���[�ԍ�
 */

#define WK_SCENE_R221R0201_ITEM_LOOP		(SVSCRWK_START+152)
/** �i���o�[�W�W�C����A�C�e���Q�b�g(�ԍ������[�v����j
 00 ���남��
 01 ������̂���
 02 �������̃^�X�L
 */

#define WK_SCENE_C05_GOODS_EV		(SVSCRWK_START+153)
/** �O�b�Y��Ⴆ��G�`��
 01 �A�C�e����n����
 02 �S�ẴO�b�Y������
 */

#define WK_SCENE_C01R0202_GET_ACCE_NO		(SVSCRWK_START+154)
/** ������A�N�Z�T���[�ԍ�
 */

#define WK_D17SYSTEM_GET_POINT		(SVSCRWK_START+155)
/** d17�߃��Y�̓��A�@���̂��镔����ʉ߂�����
 */
#define WK_D17SYSTEM_PATH_MAP		(SVSCRWK_START+156)
/** d17�߃��Y�̓��A�@�ʉ߂��������q�א�
 */
#define WK_SCENE_D26R0107			(SVSCRWK_START+157)
/** �M���K�c�A�W�g�@���C�A�C�n�C�̕���
01 �T�^�[�����`����X�C�b�`�����܂�(��������ł�Ȃ��X�g�b�p�[�L��)
 */

#define WK_SCENE_D31					(SVSCRWK_START+158)
/* �o�g���^���[�O�C�x���g
01 �o�g���^�C�N�[���A���C�o���C�x���g�I��
*/

#define WK_SCENE_T01R0201_GAME_CLEAR	(SVSCRWK_START+159)
/* �Q�[���N���A��̃}�}�̉�b
01 �Q�[���N���A���ăC�x���g�����\���
02 �C�x���g�I��
*/

#define WK_SCENE_D25R0102		(SVSCRWK_START+160)
/*	d25r0102 �X�̗m�كS�[�X�g�C�x���g
01 �S�[�X�g�C�x���g������ 
*/

#define WK_SCENE_D25R0108		(SVSCRWK_START+161)
/*	d25r0108 �X�̗m�كS�[�X�g�C�x���g
01 �S�[�X�g�C�x���g������ 
*/

#define WK_SCENE_L02_BIGMAN		(SVSCRWK_START+162)
/*	L02�i�M�T���ʂւ̃X�g�b�p�[
00 �X�g�b�p�[�L��
01 �X�g�b�p�[����
*/

#define WK_SCENE_C11R0101		(SVSCRWK_START+163)
/*	C11R0101�@�o�g���^���[��t�Q�[�g
00 ���߂ē��B
01 ����ȊO
*/

#define WK_SCENE_C04_STOPPER	(SVSCRWK_START+164)
/*	C04�̃X�g�b�p�[
00 �X�g�b�p�[�L��
01 �X�g�b�p�[����
*/

#define WK_SCENE_PLATE_MSG		(SVSCRWK_START+165)
/*	�v���[�g���b�Z�[�W���[�N
01 - 08 ���b�Z�[�W
*/

#define WK_SCENE_R212AR0101_POLICEMAN	(SVSCRWK_START+166)
/* ���܂�肳��
00 ����
01 �L��
*/ 

#define WK_SCENE_T04R0301_RE_ITEM	(SVSCRWK_START+167)
/* �a���Ă���A�C�e���ԍ�
*/

#define WK_SCENE_D05R0116	(SVSCRWK_START+168)
/* D05R0116 �A�E�X�̏o���ꏊ
01 �A�E�X�G���J�E���g�C�x���g������
*/

#define WK_SCENE_R227_SEVEN2		(SVSCRWK_START+169)
/* R227�C�x���g
01 �T�l�O�C�x���g�I��
*/

#define WK_SCENE_C07_SUPPORT_GYM_AFTER		(SVSCRWK_START+170)
/* C07�W����̃T�|�[�g�C�x���g
01 �C�x���g�J�n
02 �C�x���g�I��
*/

#define WK_SCENE_C04_STOPPER_02	(SVSCRWK_START+171)
/*	C04�̃X�g�b�p�[ ���Ă񂵂�X�g�b�p�[
00 �X�g�b�p�[����(�܂����]�Ԃ����Ă��Ȃ�)
01 �X�g�b�p�[�L��
02 R207�T�|�[�g�C�x���g�I���i�X�g�b�p�[�����j
*/

#define WK_SCENE_CYCLINGROAD	(SVSCRWK_START+172)
/* �T�C�N�����O���[�h
01 �T�C�N�����O���[�h�ɓ������̂Ŏ��]�ԏ�Ԃɂ���(�ύX������0�ɖ߂�)
*/

//#define WK_SCENE_NONE		(SVSCRWK_START+176)			/* Max = 176 */
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//------------------------------------------------------------------------

#endif	//__SAVEWORK_H__
