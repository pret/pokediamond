
//============================================================================================
/**
 * @file	battle_common.h
 * @bfief	�퓬�p�\�[�X�̃w�b�_�Ŏg�p����萔��`�݂̂��`
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#ifndef __BATTLE_COMMON_H_
#define __BATTLE_COMMON_H_

#define DEBUG_WIFIHISTORY

#define	BATTLE_TOWER_TRAINER_ID	(10000)				///<�o�g���^���[�̃g���[�i�[ID

//�퓬��ʃt���O�i�퓬�V�X�e�����̔��ʂŎg�p���Ă��܂�BattleParam��fight_type�̎w��ɂ͎g��Ȃ��ł��������j
#define	FIGHT_TYPE_1vs1			(0x00000000)		///<1vs1
#define	FIGHT_TYPE_YASEI		(0x00000000)		///<�쐶��1vs1
#define	FIGHT_TYPE_TRAINER		(0x00000001)		///<�g���[�i�[��
#define	FIGHT_TYPE_2vs2			(0x00000002)		///<2vs2
#define	FIGHT_TYPE_SIO			(0x00000004)		///<�ʐM�ΐ�
#define	FIGHT_TYPE_MULTI		(0x00000008)		///<�}���`�ΐ�
#define	FIGHT_TYPE_TAG			(0x00000010)		///<�^�b�O
#define	FIGHT_TYPE_SAFARI		(0x00000020)		///<�T�t�@���]�[��
#define	FIGHT_TYPE_AI			(0x00000040)		///<AI�}���`
#define	FIGHT_TYPE_TOWER		(0x00000080)		///<�o�g���^���[
#define	FIGHT_TYPE_MOVE			(0x00000100)		///<�ړ��|�P����
#define	FIGHT_TYPE_POKE_PARK	(0x00000200)		///<�|�P�p�[�N
#define	FIGHT_TYPE_GET_DEMO		(0x00000400)		///<�ߊl�f��

#define	FIGHT_TYPE_DEBUG		(0x80000000)		///<�f�o�b�O�퓬

//�퓬��ʃt���O�i�K�v�ȃt���O��OR�ς݂̂���BattleParam��fight_type�w��ɂ͂�������g���Ă��������j
#define	FIGHT_TYPE_1vs1_YASEI				(FIGHT_TYPE_1vs1|FIGHT_TYPE_YASEI)						///<1vs1�쐶��
#define	FIGHT_TYPE_2vs2_YASEI				(FIGHT_TYPE_2vs2|FIGHT_TYPE_MULTI|FIGHT_TYPE_AI)		///<2vs2�쐶��
#define	FIGHT_TYPE_1vs1_TRAINER				(FIGHT_TYPE_1vs1|FIGHT_TYPE_TRAINER)					///<1vs1�g���[�i�[��
#define	FIGHT_TYPE_2vs2_TRAINER				(FIGHT_TYPE_2vs2|FIGHT_TYPE_TRAINER)					///<2vs2�g���[�i�[��
#define	FIGHT_TYPE_1vs1_SIO					(FIGHT_TYPE_SIO|FIGHT_TYPE_TRAINER)						///<1vs1�ʐM�g���[�i�[��
#define	FIGHT_TYPE_2vs2_SIO					(FIGHT_TYPE_1vs1_SIO|FIGHT_TYPE_2vs2)					///<2vs2�ʐM�g���[�i�[��
#define	FIGHT_TYPE_MULTI_SIO				(FIGHT_TYPE_2vs2_SIO|FIGHT_TYPE_MULTI)					///<2vs2�ʐM�g���[�i�[��
#define	FIGHT_TYPE_AI_MULTI					(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_MULTI|FIGHT_TYPE_AI)///<2vs2AI�}���`��
#define	FIGHT_TYPE_BATTLE_TOWER_1vs1		(FIGHT_TYPE_1vs1_TRAINER|FIGHT_TYPE_TOWER)				///<1vs1�o�g���^���[��
#define	FIGHT_TYPE_BATTLE_TOWER_2vs2		(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_TOWER)				///<2vs2�o�g���^���[��
#define	FIGHT_TYPE_BATTLE_TOWER_AI_MULTI	(FIGHT_TYPE_AI_MULTI|FIGHT_TYPE_TOWER)					///<�o�g���^���[AI�}���`��
#define	FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI	(FIGHT_TYPE_MULTI_SIO|FIGHT_TYPE_TOWER)					///<�o�g���^���[�ʐM�}���`��
#define	FIGHT_TYPE_TAG_BATTLE				(FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_TAG)				///<�^�b�O�o�g����

///<�o���l�����炦�Ȃ�FightType
#define	FIGHT_TYPE_NO_EXP	(FIGHT_TYPE_SIO|FIGHT_TYPE_SAFARI|FIGHT_TYPE_TOWER|FIGHT_TYPE_POKE_PARK)

///<�}�ӓo�^�����Ȃ�FightType
#define	FIGHT_TYPE_NO_ZUKAN	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<�ǂ�ڂ��ł���FightType
#define	FIGHT_TYPE_DOROBOU	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<�K���������FightType
#define	FIGHT_TYPE_ESCAPE	(FIGHT_TYPE_SIO|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_TOWER)

///<����ւ���ɂȂ�Ȃ�FightType
#define	FIGHT_TYPE_NO_IREKAE	(FIGHT_TYPE_SIO|FIGHT_TYPE_2vs2|FIGHT_TYPE_TOWER)

///<�����Â��������炦�Ȃ�FightType
#define	FIGHT_TYPE_NO_MONEY	(FIGHT_TYPE_TOWER)

///<�o�b�W�`�F�b�N�����Ȃ�FightType
#define	FIGHT_TYPE_NO_BADGE	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<�|�P�����ɃA�C�e�����������Ȃ�FightType
#define	FIGHT_TYPE_POKE_NO_HAVE_ITEM	(FIGHT_TYPE_TRAINER|FIGHT_TYPE_TOWER)

///<�t�H�����`�F���W�`�F�b�N�����Ȃ�FightType
#define	FIGHT_TYPE_NO_FORM_CHG	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER|FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<�A�C�e��AI���N�����Ȃ�FightType
#define	FIGHT_TYPE_NO_ITEM_AI	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER|FIGHT_TYPE_SAFARI|FIGHT_TYPE_AI|FIGHT_TYPE_POKE_PARK)

///<�ǂ������g���Ȃ�FightType
#define	FIGHT_TYPE_NO_ITEM_USE	(FIGHT_TYPE_SIO|FIGHT_TYPE_TOWER)

///<�Q�[�W�̖��A�j�������Ȃ�FightType
#define	FIGHT_TYPE_NO_ARROW_ANIME	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<�������Z�b�g���Ȃ�FightType
#define	FIGHT_TYPE_NO_TOKUSEI	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<�s���`SE�`�F�b�N�����Ȃ�FightType
#define	FIGHT_TYPE_NO_PINCH_SE	(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)

///<AI�v�Z������FightType
#define	FIGHT_TYPE_AI_CALC	(FIGHT_TYPE_TRAINER|FIGHT_TYPE_MOVE)

///<win_lose_flag
#define	FIGHT_WIN					(0x01)		///�퓬����
#define	FIGHT_LOSE					(0x02)		///�퓬����
#define	FIGHT_DRAW					(0x03)		///�퓬��������
#define	FIGHT_POKE_GET				(0x04)		///�|�P�����ߊl
#define	FIGHT_ESCAPE				(0x05)		///������
#define	FIGHT_ENEMY_ESCAPE			(0x06)		///���肪������
	
#define	FIGHT_ESCAPE_SELECT_PAUSE	(0x40)		///�������I��
#define	FIGHT_ESCAPE_SELECT			(0x80)		///�������I��

#define	FIGHT_ESCAPE_SELECT_OFF		(0xc0^0xff)	///�������I��

//�o�b�O��ʁA���X�g��ʂɍs�������̃t�F�[�h�X�s�[�h
#define	BATTLE_BAGLIST_FADE_SPEED	(-8)

///<�퓬�V�X�e���̃��[�h
#define	BW_PROC_MODE_FIGHT			(0)		///<�퓬��
#define	BW_PROC_MODE_NAMEIN			(1)		///<���O���͉�ʂ�
#define	BW_PROC_MODE_NAMEIN_AFTER	(2)		///<���O���͉�ʂ�
#define	BW_PROC_MODE_BAG_LIST		(3)		///<�o�b�O�����X�g���

//POKEPARTY�\���̂̔z��̓Y����
#define	POKEPARTY_MINE			(0)					///<�����̎莝��
#define	POKEPARTY_ENEMY			(1)					///<����̎莝��
#define	POKEPARTY_MINE_PAIR		(2)					///<�}���`�̎��̃p�[�g�i�[�̎莝��
#define	POKEPARTY_ENEMY_PAIR	(3)					///<�}���`�̎��̃p�[�g�i�[�̎莝��

//COMMAND_SELECT��status�p�����[�^�̈Ӗ�
#define	COMSEL_STATUS_NONE		(0)		///<�|�P���������Ȃ�
#define	COMSEL_STATUS_ALIVE		(1)		///<�|�P����������i�����Ă�j
#define	COMSEL_STATUS_DEAD		(2)		///<�|�P����������i�C��j
#define	COMSEL_STATUS_NG		(3)		///<�|�P����������i�X�e�[�^�X�ُ�j

//���b�Z�[�W�p�P��W�J�o�b�t�@��`
#define	STR_TEMP_BUF0			(0)
#define	STR_TEMP_BUF1			(1)
#define	STR_TEMP_BUF2			(2)
#define	STR_TEMP_BUF3			(3)
#define	STR_TEMP_BUF4			(4)
#define	STR_TEMP_BUF5			(5)

///<�x������N���C�A���g�w��
#define	SIDE_ALL				(0x00)	///<�N�����Ă���N���C�A���g���ׂ�	
#define	SIDE_ATTACK				(0x01)	///<�U�����N���C�A���g
#define	SIDE_DEFENCE			(0x02)	///<�h�䑤�N���C�A���g
#define	SIDE_MINE				(0x03)	///<�������N���C�A���g
#define	SIDE_ENEMY				(0x04)	///<���葤�N���C�A���g
#define	SIDE_KIZETSU			(0x05)	///<�C�₵���N���C�A���g
#define	SIDE_RESHUFFLE			(0x06)	///<����ւ���I�������N���C�A���g
#define	SIDE_TSUIKA				(0x07)	///<�ǉ����ʂ̂������N���C�A���g
#define	SIDE_TOKUSEI			(0x08)	///<�����`�F�b�N�����Ď����Ă����N���C�A���g
#define	SIDE_MINE_1				(0x09)	///<�������N���C�A���g
#define	SIDE_ENEMY_1			(0x0a)	///<���葤�N���C�A���g
#define	SIDE_MINE_2				(0x0b)	///<�������N���C�A���g�i2vs2���̃p�[�g�i�[�j
#define	SIDE_ENEMY_2			(0x0c)	///<���葤�N���C�A���g�i2vs2���̃p�[�g�i�[�j
#define	SIDE_ATTACK_WORK		(0x0e)	///<�U�����N���C�A���g���[�N(sp->attack_client_work)
#define	SIDE_DEFENCE_WORK		(0x0f)	///<�h�䑤�N���C�A���g���[�N(sp->defence_client_work)
#define	SIDE_ATTACK_PAIR		(0x10)	///<�U�����N���C�A���g�̃p�[�g�i�[
#define	SIDE_DEFENCE_PAIR		(0x11)	///<�h�䑤�N���C�A���g�̃p�[�g�i�[
#define	SIDE_HUKITOBASI			(0x12)	///<�ӂ��Ƃ΂�����
#define	SIDE_ATTACK_ENEMY		(0x13)	///<�U�����N���C�A���g�̑���
#define	SIDE_DEFENCE_ENEMY		(0x14)	///<�h�䑤�N���C�A���g�̑���
#define	SIDE_CLIENT_WORK		(0x15)	///<sp->client_work���Q��
#define	SIDE_RESHUFFLE_AFTER	(0x16)	///<����ւ���I�������N���C�A���g�ireshuffle_sel_mons_no���Q�Ƃ���j

#define	SIDE_WORK				(0xff)	///<���[�N�Ɋi�[����Ă���l���Q��

//=========================================================================
//	�|�P�����R���f�B�V�����r�b�g�iAI��IF_COND�ł��g�p����j
//=========================================================================

#define	CONDITION_NOCHECK			(0x00000000)				//�r�b�g�̃`�F�b�N�����Ȃ�
#define	CONDITION_NEMURI			(0x00000007)				//����
#define	CONDITION_DOKU				(0x00000008)				//��
#define	CONDITION_YAKEDO			(0x00000010)				//�₯��
#define	CONDITION_KOORI				(0x00000020)				//������
#define	CONDITION_MAHI				(0x00000040)				//�܂�
#define	CONDITION_DOKUDOKU			(0x00000080)				//�ǂ��ǂ�
#define	CONDITION_DOKUDOKU_CNT		(0x00000f00)				//�ǂ��ǂ��J�E���^

#define	CONDITION_SINKURO			(0x00000058)				//�V���N��
#define	CONDITION_KARAGENKI			(0x000000d8)				//���炰��
#define	CONDITION_DOKUALL			(0x00000f88)				//�ǂ��S��

#define	CONDITION_NEMURI_OFF		(0x00000007^0xffffffff)		//����
#define	CONDITION_DOKU_OFF			(0x00000008^0xffffffff)		//��
#define	CONDITION_YAKEDO_OFF		(0x00000010^0xffffffff)		//�₯��
#define	CONDITION_KOORI_OFF			(0x00000020^0xffffffff)		//������
#define	CONDITION_MAHI_OFF			(0x00000040^0xffffffff)		//�܂�
#define	CONDITION_DOKUDOKU_CNT_OFF	(0x00000f00^0xffffffff)		//�ǂ��ǂ��J�E���^
#define	CONDITION_KARAGENKI_OFF		(0x000000d8^0xffffffff)		//���炰��
#define	CONDITION_POISON_OFF		((CONDITION_DOKU|CONDITION_DOKUDOKU|CONDITION_DOKUDOKU_CNT)^0xffffffff)

#define	DOKUDOKU_COUNT				(0x00000100)

#define	CONDITION_BAD				(0x000000ff)

//=========================================================================
//	�|�P�����R���f�B�V�����r�b�g�iAI��IF_COND2�ł��g�p����j
//=========================================================================

#define	CONDITION2_NOCHECK			(0x00000000)			//�r�b�g�̃`�F�b�N�����Ȃ�
#define	CONDITION2_KONRAN			(0x00000007)			//������
#define	CONDITION2_HIRUMU			(0x00000008)			//�Ђ��
#define	CONDITION2_SAWAGU			(0x00000070)			//���킮
#define	CONDITION2_TRIATTACK		(0x00000080)			//�g���C�A�^�b�N
#define	CONDITION2_GAMAN			(0x00000300)			//���܂�
#define	CONDITION2_ABARERU			(0x00000c00)			//���΂��
#define	CONDITION2_KEEP				(0x00001000)			//����
#define	CONDITION2_SHIME			(0x0000e000)			//���߂킴
#define	CONDITION2_MEROMERO			(0x000f0000)			//���������r�b�g
#define	CONDITION2_KIAIDAME			(0x00100000)			//����������
#define	CONDITION2_HENSHIN			(0x00200000)			//�ւ񂵂�
#define	CONDITION2_HANDOU			(0x00400000)			//�͂�ǂ���
#define	CONDITION2_IKARI			(0x00800000)			//������
#define	CONDITION2_MIGAWARI			(0x01000000)			//�݂����
#define	CONDITION2_MICHIDURE		(0x02000000)			//�݂��Â�
#define	CONDITION2_KUROIMANAZASHI	(0x04000000)			//���낢�܂Ȃ���
#define	CONDITION2_AKUMU			(0x08000000)			//������
#define	CONDITION2_NOROI			(0x10000000)			//�̂낢
#define	CONDITION2_MIYABURU			(0x20000000)			//�݂�Ԃ�
#define	CONDITION2_MARUKUNARU		(0x40000000)			//�܂邭�Ȃ�
#define	CONDITION2_ICHAMON			(0x80000000)			//���������

#define	CONDITION2_KONRAN_OFF		(0x00000007^0xffffffff)	//������
#define	CONDITION2_HIRUMU_OFF		(0x00000008^0xffffffff)	//�Ђ��
#define	CONDITION2_SAWAGU_OFF		(0x00000070^0xffffffff)	//���킮
#define	CONDITION2_TRIATTACK_OFF	(0x00000080^0xffffffff)	//�g���C�A�^�b�N
#define	CONDITION2_GAMAN_OFF		(0x00000300^0xffffffff)	//���܂�
#define	CONDITION2_ABARERU_OFF		(0x00000c00^0xffffffff)	//���΂��
#define	CONDITION2_KEEP_OFF			(0x00001000^0xffffffff)	//����
#define	CONDITION2_SHIME_OFF		(0x0000e000^0xffffffff)	//���߂킴
#define	CONDITION2_MEROMERO_OFF		(0x000f0000^0xffffffff)	//���������r�b�g
#define	CONDITION2_KIAIDAME_OFF		(0x00100000^0xffffffff)	//����������
#define	CONDITION2_HENSHIN_OFF		(0x00200000^0xffffffff)	//�ւ񂵂�
#define	CONDITION2_HANDOU_OFF		(0x00400000^0xffffffff)	//�͂�ǂ���
#define	CONDITION2_IKARI_OFF		(0x00800000^0xffffffff)	//������
#define	CONDITION2_MIGAWARI_OFF		(0x01000000^0xffffffff)	//�݂����
#define	CONDITION2_MICHIDURE_OFF	(0x02000000^0xffffffff)	//�݂��Â�
#define	CONDITION2_KUROIMANAZASHI_OFF (0x04000000^0xffffffff)	//���낢�܂Ȃ���
#define	CONDITION2_AKUMU_OFF		(0x08000000^0xffffffff)	//������
#define	CONDITION2_NOROI_OFF		(0x10000000^0xffffffff)	//�̂낢
#define	CONDITION2_MIYABURU_OFF		(0x20000000^0xffffffff)	//�݂�Ԃ�
#define	CONDITION2_ICHAMON_OFF		(0x80000000^0xffffffff)	//���������

#define	CONDITION2_BATON_TOUCH_ON	(CONDITION2_KIAIDAME|CONDITION2_KUROIMANAZASHI|\
									 CONDITION2_KONRAN|CONDITION2_NOROI|CONDITION2_MIGAWARI)

#define	KONRAN_COUNT				(0x00000001)
#define	SAWAGU_COUNT				(0x00000010)
#define	GAMAN_TURN					(0x00000200)
#define	GAMAN_COUNT					(0x00000100)
#define	ABARERU_COUNT				(0x00000400)
#define	SHIME_COUNT					(0x00002000)
#define	HOROBINOUTA_COUNT			(0x40000000)

#define	KONRAN_SHIFT				(0)
#define	SAWAGU_SHIFT				(4)
#define	GAMAN_SHIFT					(8)
#define	ABARERU_SHIFT				(10)
#define	SHIME_SHIFT					(13)
#define	MEROMERO_SHIFT				(16)
#define	HOROBINOUTA_SHIFT			(30)

#define	KOBAN_MAX					(0xffff)		//�˂��ɂ��΂�ł��炦�邨����MAX

//======================================================================================================

#define	HP_KETA_MAX			(3)		///<HP�̍ő包��
#define	LEVEL_KETA_MAX		(3)		///<���x���̍ő包��

#define	BATTLE_MESSAGE_BUF_SIZE		(2*160)		///<�퓬�p���b�Z�[�W�W�J�̈�T�C�Y�i�P�U�O�������j
#define	BATTLE_STR_TEMP_BUF_SIZE	(2*20)		///<�퓬�p�^�O�W�J�̈�T�C�Y�i�Q�O�������j

#define	WAZA_TEMOTI_MAX		(4)		///<1�̂̃|�P���������Ă�Z�̍ő�l
#define	POKEMON_TEMOTI_MAX	(6)		///<�莝���Ɏ��Ă�|�P�����̍ő�l
#define	POKEMON_ABIRITY_MAX	(8)		///<�|�P�����̔\�͒l��ނ̍ő�l
#define	ID_MAX				(4)		///<�ʐMIDMAX
#define	CLIENT_MAX			(4)		///<�����ɋN������N���C�A���g�̍ő吔
#define	SERVER_QUE_MAX		(16)	///<�N���C�A���g�ւ̖��߃L���[�̍ő吔�i4�ł͐�Α���Ȃ��j
#define	BUF_SIZE			(256)	///<�T�[�o�A�N���C�A���g�̖��߁A�����i�[�o�b�t�@�̃T�C�Y

#define	NONE_CLIENT_NO		(0xff)	///<�eClientNo�i�[���[�N�̏����l

#define GROUND_MINE			(0)		///<�������n��
#define GROUND_ENEMY		(1)		///<�G���n��
#define GROUND_MAX			(2)		///<�n�ʂ̍ő吔

#define	BATTLE_ALLOC_SIZE	(0xb0000)	///<�퓬�Ŏg�p����q�[�v�T�C�Y

#define BATTLE_VRAM_TRANSFER_TASK_NUM	(64)	///<Vram�]���}�l�[�W���[�^�X�N��

#define	BATTLE_SIO_BUF_SIZE	(0x1000)	///<�퓬�ʐM�p�o�b�t�@�T�C�Y

#define	EXCHR_BUFFER_SIZE	(32*10*10)	///<�Z�G�t�F�N�g�p�L�����W�J�o�b�t�@�T�C�Y

#define BATTLE_3DBG_PRIORITY		(1)//���X(2)	///<3D�ʂ�BG�v���C�I���e�B
#define BATTLE_BGPRI_WINDOW			(0)	///<�E�B���h�E�ʂ�BG�v���C�I���e�B
#define BATTLE_BGPRI_EFFECT			(1)	///<�G�t�F�N�g�ʂ�BG�v���C�I���e�B
#define BATTLE_BGPRI_BACKGROUND		(3)	///<�w�i�ʂ�BG�v���C�I���e�B

#define BATTLE_FRAME_WINDOW			(GF_BGL_FRAME1_M)	///<�t���[���ʁF�E�B���h�E
#define BATTLE_FRAME_EFFECT			(GF_BGL_FRAME2_M)	///<�t���[���ʁF�G�t�F�N�g
#define BATTLE_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)	///<�t���[���ʁF�w�i

#define BATTLE_BGNO_WINDOW			(1)					///<BG�ԍ��F�E�B���h�E
#define BATTLE_BGNO_EFFECT			(2)					///<BG�ԍ��F�G�t�F�N�g
#define BATTLE_BGNO_BACKGROUND		(3)					///<BG�ԍ��F�w�i

//HP�Q�[�W���X���C�h�C�����Ă���܂ł̃E�G�C�g
#define	HP_GAUGE_IN_WAIT			(4)

//�Z�̕��ނɊւ����`
#define	KIND_BUTSURI	(0)			///<�����U��
#define	KIND_TOKUSYU	(1)			///<����U��
#define	KIND_HENKA		(2)			///<��ԕω�

//�Z�̌��ʔ͈͂Ɋւ����`
#define	RANGE_NORMAL		(0x0000)		//�����ȊO��3��
#define	RANGE_NONE			(0x0001)		//�I���Ȃ�
#define	RANGE_RANDOM		(0x0002)		//�����_��
#define	RANGE_DOUBLE		(0x0004)		//�Q�̂ɓ�����
#define	RANGE_TRIPLE		(0x0008)		//�����ȊO3�̂ɓ�����
#define	RANGE_MINE			(0x0010)		//�����I��
#define	RANGE_MINE_DOUBLE	(0x0020)		//�����Q�̑I��
#define	RANGE_FIELD			(0x0040)		//��ɂ�����
#define	RANGE_MAKIBISHI		(0x0080)		//�܂��т���p
#define	RANGE_TEDASUKE		(0x0100)		//�Ă�������p
#define	RANGE_TUBOWOTUKU	(0x0200)		//�ڂ�����p
#define	RANGE_SAKIDORI		(0x0400)		//�����ǂ��p

#define	RANGE_NO_DIR	(RANGE_DOUBLE|RANGE_NONE|RANGE_MINE|RANGE_RANDOM|RANGE_TRIPLE|RANGE_FIELD)

#define	RANGE_MINE_DIR	(RANGE_NONE|RANGE_MINE|RANGE_FIELD|RANGE_TUBOWOTUKU)

//�Z�o���Ɋւ����`
#define	NO_WAZA_OBOE		(0x0000)		//�Z���o���Ȃ�����
#define	NO_WAZA_SET			(0xffff)		//�Z�̃Z�b�g���ł��Ȃ������Ƃ��̕Ԃ�l
#define	SAME_WAZA_SET		(0xfffe)		//���łɊo���Ă����Z�̂Ƃ��̕Ԃ�l

//�|�P������Z�̃^�C�v��`
#define	NORMAL_TYPE			(0)
#define	BATTLE_TYPE			(1)
#define	HIKOU_TYPE			(2)
#define	POISON_TYPE			(3)
#define	JIMEN_TYPE			(4)
#define	IWA_TYPE			(5)
#define	MUSHI_TYPE			(6)
#define	GHOST_TYPE			(7)
#define	METAL_TYPE			(8)
#define	HATE_TYPE			(9)
#define	FIRE_TYPE			(10)
#define	WATER_TYPE			(11)
#define	KUSA_TYPE			(12)
#define	ELECTRIC_TYPE		(13)
#define	SP_TYPE				(14)
#define	KOORI_TYPE			(15)
#define	DRAGON_TYPE			(16)
#define	AKU_TYPE			(17)

#define	POKE_WAZA_TYPE_MAX	(17)

///<�ʐM�ΐ�ȊO�ł̋N�����ꂽ�N���C�A���g��ClientNo��`
#define	CLIENT_NO_MINE		(0)
#define	CLIENT_NO_ENEMY		(1)
#define	CLIENT_NO_MINE2		(2)
#define	CLIENT_NO_ENEMY2	(3)

//�|�P�����̗����ʒu�w��(1vs1)
//			 BB
//
//	 AA
//�|�P�����̗����ʒu�w��(2vs2)
//			D	B
//
//	A�@C
#define	CLIENT_TYPE_AA	(0)
#define	CLIENT_TYPE_BB	(1)

#define	CLIENT_TYPE_A	(2)
#define	CLIENT_TYPE_B	(3)
#define	CLIENT_TYPE_C	(4)
#define	CLIENT_TYPE_D	(5)

#define	CLIENT_ENEMY_FLAG	(0x01)	///<client_type��1bit�ڂ������Ă���ΓG�����Ɣ��f�ł���

#define	CLIENT_TYPE_MAX		(6)
#define	CLIENT_TYPE_NONE	(0xff)	///<ClientType�Ȃ�

//�g���[�i�[�̗����ʒu�i�ʐM�������j
//
//	A		B
//
//	C		D
//
#define	TRAINER_STAND_A		(0)
#define	TRAINER_STAND_B		(1)
#define	TRAINER_STAND_C		(2)
#define	TRAINER_STAND_D		(3)

//�N���C�A���g�̋N����ԃt���O
#define	CLIENT_BOOT_NORMAL	(0x00)	///<�ʏ�N��
#define	CLIENT_BOOT_AI		(0x01)	///<AI�N��
#define	CLIENT_BOOT_SIO		(0x02)	///<�ʐM�̃N���[���N��

//�G���J�E���g���̏����ʒu
#define	ENCOUNT_X_TYPE_AA	(256+80)
#define	ENCOUNT_Y_TYPE_AA	(104+8)
#define	ENCOUNT_Z_TYPE_AA	(-0x200)

#define	ENCOUNT_X_TYPE_BB	(-80)
#define	ENCOUNT_Y_TYPE_BB	(50)
#define	ENCOUNT_Z_TYPE_BB	(-0x280)

#define	ENCOUNT_X_TYPE_A	(256+60)
#define	ENCOUNT_Y_TYPE_A	(104+8)
#define	ENCOUNT_Z_TYPE_A	(ENCOUNT_Z_TYPE_AA)

#define	ENCOUNT_X_TYPE_B	(-60)
#define	ENCOUNT_Y_TYPE_B	(50)
#define	ENCOUNT_Z_TYPE_B	(-100)

#define	ENCOUNT_X_TYPE_C	(256+100)
#define	ENCOUNT_Y_TYPE_C	(ENCOUNT_Y_TYPE_A + 8)
#define	ENCOUNT_Z_TYPE_C	(0)

#define	ENCOUNT_X_TYPE_D	(-100)
#define	ENCOUNT_Y_TYPE_D	(ENCOUNT_Y_TYPE_B - 8)
#define	ENCOUNT_Z_TYPE_D	(ENCOUNT_Z_TYPE_BB)

//�o�ꎞ�̈ʒu(1vs1)
#define	APPEAR_X_TYPE_AA	(64)
#define	APPEAR_Y_TYPE_AA	(104+8)
#define	APPEAR_Z_TYPE_AA	(ENCOUNT_Z_TYPE_AA)

#define	APPEAR_X_TYPE_BB	(256-64)
#define	APPEAR_Y_TYPE_BB	(48)
#define	APPEAR_Z_TYPE_BB	(ENCOUNT_Z_TYPE_BB)

//�o�ꎞ�̈ʒu(2vs2)
#define	APPEAR_X_TYPE_A	(40)
#define	APPEAR_Y_TYPE_A	(ENCOUNT_Y_TYPE_A)
#define	APPEAR_Z_TYPE_A	(ENCOUNT_Z_TYPE_A)

#define	APPEAR_X_TYPE_B	(256-40)
#define	APPEAR_Y_TYPE_B	(ENCOUNT_Y_TYPE_B)
#define	APPEAR_Z_TYPE_B	(ENCOUNT_Z_TYPE_B)

#define	APPEAR_X_TYPE_C	(80)
#define	APPEAR_Y_TYPE_C	(ENCOUNT_Y_TYPE_C)
#define	APPEAR_Z_TYPE_C	(ENCOUNT_Z_TYPE_C)

#define	APPEAR_X_TYPE_D	(256-80)
#define	APPEAR_Y_TYPE_D	(ENCOUNT_Y_TYPE_D)
#define	APPEAR_Z_TYPE_D	(ENCOUNT_Z_TYPE_D)

//�X���C�hIN�̏����ʒu
#define	SLIDEIN_X_TYPE_AA	(-80)
#define	SLIDEIN_Y_TYPE_AA	(ENCOUNT_Y_TYPE_AA)
#define	SLIDEIN_Z_TYPE_AA	(ENCOUNT_Z_TYPE_AA)
#define	SLIDEIN_X_TYPE_BB	(256+80)
#define	SLIDEIN_Y_TYPE_BB	(ENCOUNT_Y_TYPE_BB)
#define	SLIDEIN_Z_TYPE_BB	(ENCOUNT_Z_TYPE_AA)

//�g���[�i�[���b�Z�[�W�A�N�V�������̈ʒu
#define	MSG_X_TYPE_AA	(32)
#define	MSG_X_TYPE_BB	(256-32)

//�o��G�t�F�N�g�̊g�k�l
#define	AFF_APPEAR_X_S	(0x000)		///<�������Ƃ�
#define	AFF_APPEAR_Y_S	(0x000)		///<�������Ƃ�
#define	AFF_APPEAR_X_B	(0x100)		///<���̑傫��
#define	AFF_APPEAR_Y_B	(0x100)		///<���̑傫��

//��ʊO�̈ʒu
#define	FRAME_OUT_X_L	(-40)
#define	FRAME_OUT_X_R	(256+40)

//�{�[���𓊂���ʒu
#define	BALL_THROW_X_L	(-20)
#define	BALL_THROW_X_R	(256+20)

//�|�P�����I������1�̖ڑI�����Ȃ���`
#define	NO_DOUBLE_SEL	(6)

//=========================================================================
//		HP�Q�[�W�ł̃X�e�[�^�X�\���p��`
//=========================================================================
///< �����p ___STATUS_EFFECT____
#define	STATUS_NORMAL	(0)		//��Ԉُ�Ȃ�
#define	STATUS_NEMURI	(1)		//����
#define	STATUS_DOKU		(2)		//��
#define	STATUS_YAKEDO	(3)		//�₯��
#define	STATUS_KOORI	(4)		//������
#define	STATUS_MAHI		(5)		//�܂�

// =========================================
//
// �X�e�[�^�X�G�t�F�N�g��`(�\���̘A�Ԃ������p��)
//
// =========================================
#define	STATUS_KONRAN			(6)		///< ������
#define	STATUS_MEROMERO			(7)		///< ��������

#define	STATUS_LVUP				(8)		///< LvUp
#define	STATUS_ITEM_TR			(9)		///< �g���[�i�[ �A�C�e��
#define	STATUS_ITEM_POKE		(10)	///< o�|�P���� ���̂�
#define	STATUS_REA				(11)	///< o���A�G�t�F�N�g

///< �\��
#define STATUS_EFF_UP			(12)	///< �\�͏㏸
#define STATUS_EFF_DOWN			(13)	///< �\�͉��~
#define STATUS_EFF_RECOVER		(14)	///< ��
#define STATUS_EFF_MIGAWARI_OUT	(15)	///< o��ʊO��
#define STATUS_EFF_MIGAWARI_IN	(16)	///< o��ʓ���
#define STATUS_EFF_ITEM_POUCH	(17)	///< o�G�l�R�����ۂƃs�b�s�l�`

///< �V�C�iSTART��END�́A�G�t�F�N�g�N������HP�Q�[�WON/OFF��͈͂Ŕ��肷�邽�߂ɗp���Ă���j
#define STATUS_WEATHER_START	(18)	///< �V��G�t�F�N�g�J�n�i���o�[
#define STATUS_WEATHER_MIST		(18)	///< �V�� ��
#define STATUS_WEATHER_RAIN		(19)	///< �V�� �J
#define STATUS_WEATHER_ICE		(20)	///< �V�� �����
#define STATUS_WEATHER_SAND		(21)	///< �V�� �����炵
#define STATUS_WEATHER_SUN		(22)	///< �V�� �Ђ���
#define STATUS_WEATHER_END		(22)	///< �V��G�t�F�N�g�I���i���o�[

///< ���̑�
#define STATUS_ACTION_DOLL_ON	(25)	///< o���� �݂���肨���Ă���
#define STATUS_ACTION_DOLL_OFF	(26)	///< ���� �݂����OFF
#define STATUS_ACTION_JOY		(27)	///< ���� ���傢���傢
#define STATUS_ACTION_EAT		(28)	///< ���� �p�N�p�N
#define STATUS_ACTION_ANGER		(29)	///< ���� �s�L�s�L

///< �^�[������
#define STATUS_DAMAGE_NOROI		(30)	///< �^�[�� �̂낢
#define STATUS_DAMAGE_AKUMU		(31)	///< �^�[�� ������
#define STATUS_DAMAGE_YADORIGI	(32)	///< �^�[�� ��ǂ肬
#define STATUS_DAMAGE_SIMETUKE	(33)	///< �^�[�� ���߂���
#define STATUS_DAMAGE_MAKITUKU	(34)	///< �^�[�� �܂���
#define STATUS_DAMAGE_HONOO		(35)	///< �^�[�� �ق̂��̂���
#define STATUS_DAMAGE_MAGUMA	(36)	///< �^�[�� �}�O�}�X�g�[��
#define STATUS_DAMAGE_KARA		(37)	///< �^�[�� ����ł͂���
#define STATUS_DAMAGE_UZUSIO	(38)	///< �^�[�� ��������
#define STATUS_DAMAGE_SUNA		(39)	///< �^�[�� ���Ȃ�����
#define STATUS_DAMAGE_NEWOHARU	(40)	///< �^�[�� �˂��͂�

//=========================================================================
//		CL_ACT�p�̒萔��`
//=========================================================================

///���C��	OAM�Ǘ��̈�E�J�n
#define BATTLE_OAM_START_MAIN			(0)
///���C��	OAM�Ǘ��̈�E�I��
#define BATTLE_OAM_END_MAIN				(128)
///���C��	�A�t�B���Ǘ��̈�E�J�n
#define BATTLE_OAM_AFFINE_START_MAIN	(0)
///���C��	�A�t�B���Ǘ��̈�E�I��
#define BATTLE_OAM_AFFINE_END_MAIN		(32)
///�T�u	OAM�Ǘ��̈�E�J�n
#define BATTLE_OAM_START_SUB			(0)
///�T�u	OAM�Ǘ��̈�E�I��
#define BATTLE_OAM_END_SUB				(128)
///�T�u �A�t�B���Ǘ��̈�E�J�n
#define BATTLE_OAM_AFFINE_START_SUB		(0)
///�T�u	�A�t�B���Ǘ��̈�E�I��
#define BATTLE_OAM_AFFINE_END_SUB		(32)

///�L�����}�l�[�W���F�L�����N�^ID�Ǘ���(���ʁ{�����)
#define BATTLE_CHAR_MAX					(48 + 48)
///�L�����}�l�[�W���F���C����ʃT�C�Y(byte�P��)
#define BATTLE_CHAR_VRAMSIZE_MAIN		(1024 * 0x40)	//64K
///�L�����}�l�[�W���F�T�u��ʃT�C�Y(byte�P��)
#define BATTLE_CHAR_VRAMSIZE_SUB		(512 * 0x20)	//32K

///���C����ʁ{�T�u��ʂŎg�p����A�N�^�[����
#define BATTLE_ACTOR_MAX				(64 + 64)	//���C����� + �T�u���

///�T�u�T�[�t�F�[�XY(fx32)
#define BATTLE_SUB_ACTOR_DISTANCE		((192 + 80) << FX32_SHIFT)
///�T�u�T�[�t�F�[�XY(int)
#define BATTLE_SUB_ACTOR_DISTANCE_INTEGER		(BATTLE_SUB_ACTOR_DISTANCE >> FX32_SHIFT)

///OBJ�Ŏg�p����p���b�g�{��(���ʁ{�����)
#define BATTLE_OAM_PLTT_MAX				(16 + 16)

///�]�����[�h 3D = 0 main = 1 sub = 2 main/sub = 3
#define BATTLE_OAM_VRAM_TRANS			(3)

///OAM���\�[�X�F�L�����o�^�ő吔(���C����� + �T�u���)
#define BATTLE_OAMRESOURCE_CHAR_MAX			(BATTLE_CHAR_MAX)
///OAM���\�[�X�F�p���b�g�o�^�ő吔(���C����� + �T�u���)
#define BATTLE_OAMRESOURCE_PLTT_MAX			(BATTLE_OAM_PLTT_MAX)
///OAM���\�[�X�F�Z���o�^�ő吔
#define BATTLE_OAMRESOURCE_CELL_MAX			(64)
///OAM���\�[�X�F�Z���A�j���o�^�ő吔
#define BATTLE_OAMRESOURCE_CELLANM_MAX		(64)
///OAM���\�[�X�F�}���`�Z���o�^�ő吔
#define BATTLE_OAMRESOURCE_MCELL_MAX		(8)
///OAM���\�[�X�F�}���`�Z���A�j���o�^�ő吔
#define BATTLE_OAMRESOURCE_MCELLANM_MAX		(8)

///OBJ�p���b�g�FPFD�Ǘ��{��(�p���b�g�P��)
#define BATTLE_MAIN_OBJPAL_NUM				(16 - 2)	//-2 = �ʐM�A�C�R���{���[�J���C�Y�p
///OBJ�p���b�g�FPFD�Ǘ��{��(�J���[�P��)
#define BATTLE_MAIN_OBJPAL_COLOR_NUM		(BATTLE_MAIN_OBJPAL_NUM * 16)
///OBJ�p���b�g�F�o�C�g�T�C�Y
#define BATTLE_MAIN_OBJPAL_SIZE				(BATTLE_MAIN_OBJPAL_COLOR_NUM * sizeof(u16))
///OBJ�p���b�g�F�t�F�[�hbit
#define BATTLE_MAIN_OBJPAL_FADEBIT			(0x3fff)

//==============================================================================
//	�p���b�g�W�J�ꏊ��`
//==============================================================================
///�G�t�F�N�gBG�p���b�g�O
#define BATTLE_PAL_EFF_0				(8)
///�G�t�F�N�gBG�p���b�g�P
#define BATTLE_PAL_EFF_1				(9)

//=========================================================================
//		�i��������`
//=========================================================================
//
#define	SHINKA_NONE					(0)
#define	SHINKA_FRIEND_HIGH			(1)
#define	SHINKA_FRIEND_HIGH_NOON		(2)
#define	SHINKA_FRIEND_HIGH_NIGHT	(3)
#define	SHINKA_LEVELUP				(4)
#define	SHINKA_TUUSHIN				(5)
#define	SHINKA_TUUSHIN_ITEM			(6)
#define	SHINKA_ITEM					(7)
#define	SHINKA_SPECIAL_POW			(8)
#define	SHINKA_SPECIAL_EVEN			(9)
#define	SHINKA_SPECIAL_DEF			(10)
#define	SHINKA_SPECIAL_RND_EVEN		(11)
#define	SHINKA_SPECIAL_RND_ODD		(12)
#define	SHINKA_SPECIAL_LEVELUP		(13)
#define	SHINKA_SPECIAL_NUKENIN		(14)
#define	SHINKA_SPECIAL_BEAUTIFUL	(15)
#define	SHINKA_ITEM_MALE			(16)
#define	SHINKA_ITEM_FEMALE			(17)
#define	SHINKA_SOUBI_NOON			(18)
#define	SHINKA_SOUBI_NIGHT			(19)
#define	SHINKA_WAZA					(20)
#define	SHINKA_POKEMON				(21)
#define	SHINKA_MALE					(22)
#define	SHINKA_FEMALE				(23)
#define	SHINKA_PLACE_TENGANZAN		(24)
#define	SHINKA_PLACE_KOKE			(25)
#define	SHINKA_PLACE_ICE			(26)

//=========================================================================
//		battle_status_flag
//=========================================================================

#define	BATTLE_STATUS_FLAG_FIRST_BATTLE		(0x00000001)	///<�ŏ��̃f���퓬
#define	BATTLE_STATUS_FLAG_MITSUNURI_BATTLE	(0x00000002)	///<�݂ʂ�ł̃G���J�E���g
#define	BATTLE_STATUS_FLAG_NO_ESCAPE_YASEI	(0x00000004)	///<�쐶��ł��ɂ���Ȃ�
#define	BATTLE_STATUS_FLAG_DENSETSU_BATTLE	(0x00000008)	///<�`���n�Ƃ̃G���J�E���g

#define	BATTLE_STATUS_FLAG_DEBUG_BIT		(0xf0000000)	///<�f�o�b�O�p�t���O�i�T�[�o�o�[�W�����j
#define	BATTLE_STATUS_FLAG_AUTO_BATTLE		(0x08000000)	///<�f�o�b�O�p�t���O
#define	BATTLE_STATUS_FLAG_NO_HP_DEC		(0x04000000)	///<�f�o�b�O�p�t���O
#define	BATTLE_STATUS_FLAG_NO_PP_DEC		(0x02000000)	///<�f�o�b�O�p�t���O

//=========================================================================
//		HP�񕜌n�A�C�e���p��`
//=========================================================================
#define	HP_MAX_RECOVER				(255)		//HP�S��
#define	HP_HALF_RECOVER				(254)		//HP����
#define	HP_25PER_RECOVER			(253)		//HPMAX��25%��

//=========================================================================
//		���M�����[�V�����t���O
//=========================================================================
#define	REGULATION_FLAG_LITTLE_CUP	(0x00000001)	//���g���J�b�v���M�����[�V����

//=========================================================================
//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

//CT_AppearPosGet��pos_id��`
enum{
	POS_ID_X=0,
	POS_ID_Y,
	POS_ID_Z
};

//�N���C�A���g����̕ԓ��R�[�h
enum{
	SELECT_FIGHT_COMMAND=1,
	SELECT_ITEM_COMMAND,
	SELECT_POKEMON_COMMAND,
	SELECT_ESCAPE_COMMAND,
	SELECT_DEBUG_ESCAPE_COMMAND,		//�f�o�b�O�p�ɋ����I�ɓ�����R�}���h
	SELECT_DEBUG_WIN_ESCAPE_COMMAND,	//�f�o�b�O�p�ɋ����I�ɓ�����R�}���h
	//�T�t�@���̏ꍇ
	SELECT_SAFARI_BALL = SELECT_FIGHT_COMMAND,
	SELECT_SAFARI_ESA = SELECT_ITEM_COMMAND,
	SELECT_SAFARI_DORO = SELECT_POKEMON_COMMAND,
	SELECT_SAFARI_ESCAPE = SELECT_ESCAPE_COMMAND,
	SELECT_SAFARI_YOUSUMI,
	//�|�P�p�[�N�̏ꍇ
	SELECT_POKEPARK_BALL = SELECT_FIGHT_COMMAND,
	SELECT_POKEPARK_ESCAPE = SELECT_ESCAPE_COMMAND,
	
	//�Z�I��
	SELECT_SKILL_1 = 1,
	SELECT_SKILL_2,
	SELECT_SKILL_3,
	SELECT_SKILL_4,

	//�|�P�����I��(���X�g)
	SELECT_POKE_1 = 1,
	SELECT_POKE_2,
	SELECT_POKE_3,
	SELECT_POKE_4,
	SELECT_POKE_5,
	SELECT_POKE_6,

	//�|�P�����I��(�Z�^�[�Q�b�g)	���̃A���t�@�x�b�g�̓N���C�A���g�^�C�v�̈ʒu�ɑΉ�
	SELECT_TARGET_A = 1,
	SELECT_TARGET_B,
	SELECT_TARGET_C,
	SELECT_TARGET_D,
	
	SELECT_CANCEL=0xff
};

//�i������
enum{
	LEVELUP_SHINKA=0,		//���x���A�b�v�ɂ��i��
	TUUSHIN_SHINKA,			//�ʐM�ɂ��i��
	ITEM_SHINKA,			//�A�C�e���ɂ��i��
	ITEM_SHINKA_CHECK,		//�A�C�e���ɂ��i���i����炸�̂����𑕔����Ă��Ă��`�F�b�N�͂���j
};

#define	POKE_LEVEL_MAX		(100)		//���x��MAX
#define	SHINKA_FRIEND		(220)		//�i���ɕK�v�ȂȂ��x
#define	FRIEND_MAX			(255)		//�Ȃ��xMAX�l
#define	STYLE_MAX			(255)		//�������悳MAX�l
#define	BEAUTIFUL_MAX		(255)		//��������MAX�l
#define	CUTE_MAX			(255)		//���킢��MAX�l
#define	CLEVER_MAX			(255)		//��������MAX�l
#define	STRONG_MAX			(255)		//�����܂���MAX�l
#define	FUR_MAX				(255)		//�щ�MAX�l
#define	PP_COUNT_MAX		(3)			//pp_countMAX�l
#define	POW_RND_MAX			(31)		//�p���[����MAX�l

//�G�t�F�N�g�R�[���p�̃t���O
#define	EFFTYPE_WAZA		(0)			//�Z�G�t�F�N�g
#define	EFFTYPE_STATUS		(1)			//�X�e�[�^�X�G�t�F�N�g

//============================================================================================
//	�\���̐錾
//============================================================================================

typedef struct _POKEPARTY POKEPARTY;
typedef struct _MYSTATUS MYSTATUS;
typedef struct _MYITEM MYITEM;
typedef struct _ZUKAN_WORK ZUKAN_WORK;
typedef struct _BOX_DATA BOX_DATA;
typedef struct _BAG_CURSOR	BAG_CURSOR;
typedef struct PERAPVOICE	PERAPVOICE;
typedef struct _CONFIG	CONFIG;
typedef struct _POKETCH_DATA POKETCH_DATA;

#include "poketool/poke_tool.h"
#include "field/tvtopic_battle.h"		//TVWATCH_BATTLE_WORK
#include "system/pms_data.h"
#include "system/palanm.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"

#ifndef	__ASM_NO_DEF_	// ������ȍ~�́A�A�Z���u���ł͖���
#include "savedata/wifihistory.h"
#include "savedata/friendlist.h"
#endif

//�g���[�i�[�f�[�^�p�����[�^
typedef struct{
	u8			data_type;					//�f�[�^�^�C�v
	u8			tr_type;					//�g���[�i�[����
	u8			tr_gra;						//�g���[�i�[�O���t�B�b�N
	u8			poke_count;					//�����|�P������

	u16			use_item[4];				//�g�p����

	u32			aibit;						//AI�p�^�[��
	u32			fight_type;					//�퓬�^�C�v�i1vs1or2vs2�j

	STRCODE		name[BUFLEN_PERSON_NAME];	//�g���[�i�[��
	PMS_DATA	win_word;
	PMS_DATA	lose_word;
}TRAINER_DATA;


//�g���[�i�[�����|�P�����p�����[�^
enum{
	DATATYPE_NORMAL=0,
	DATATYPE_WAZA,
	DATATYPE_ITEM,
	DATATYPE_MULTI
};

//�g���[�i�[�����|�P�����p�����[�^�i�f�[�^�^�C�v�m�[�}���j
typedef	struct
{
	u16		pow;			//�Z�b�g����p���[����(u8��OK������4�o�C�g���E�΍�j
	u16		level;			//�Z�b�g����|�P�����̃��x��
	u16		monsno;			//�Z�b�g����|�P����
}POKEDATA_TYPE_NORMAL;

//�g���[�i�[�����|�P�����p�����[�^�i�f�[�^�^�C�v�Z�j
typedef	struct
{
	u16		pow;			//�Z�b�g����p���[����(u8��OK������4�o�C�g���E�΍�j
	u16		level;			//�Z�b�g����|�P�����̃��x��
	u16		monsno;			//�Z�b�g����|�P����
	u16		waza[4];		//�����Ă�Z
}POKEDATA_TYPE_WAZA;

//�g���[�i�[�����|�P�����p�����[�^�i�f�[�^�^�C�v�A�C�e���j
typedef	struct
{
	u16		pow;			//�Z�b�g����p���[����(u8��OK������4�o�C�g���E�΍�j
	u16		level;			//�Z�b�g����|�P�����̃��x��
	u16		monsno;			//�Z�b�g����|�P����
	u16		itemno;			//�Z�b�g����A�C�e��
}POKEDATA_TYPE_ITEM;

//�g���[�i�[�����|�P�����p�����[�^�i�f�[�^�^�C�v�}���`�j
typedef	struct
{
	u16		pow;			//�Z�b�g����p���[����(u8��OK������4�o�C�g���E�΍�j
	u16		level;			//�Z�b�g����|�P�����̃��x��
	u16		monsno;			//�Z�b�g����|�P����
	u16		itemno;			//�Z�b�g����A�C�e��
	u16		waza[4];		//�����Ă�Z
}POKEDATA_TYPE_MULTI;

typedef struct
{
	int		total_turn;		//���^�[����
	int		total_hinshi;	//���m����
	int		total_damage;	//���_���[�W��
}BATTLE_TOWER_RECORD;

//�퓬�J�n�p�����[�^
typedef struct{
	u32					fight_type;					///<�퓬��ʃt���O
	POKEPARTY			*poke_party[CLIENT_MAX];	///<�莝���|�P�����f�[�^
	int					win_lose_flag;				///<���������t���O
	int					trainer_id[CLIENT_MAX];		///<�g���[�i�[��ID
	TRAINER_DATA		trainer_data[CLIENT_MAX];	///<�g���[�i�[�f�[�^
	MYSTATUS			*my_status[CLIENT_MAX];		///<���L�����f�[�^
	MYITEM				*my_item;					///<�����A�C�e���f�[�^
	BAG_CURSOR			*bag_cursor;				///<�o�b�O�̃J�[�\���f�[�^
	ZUKAN_WORK			*zw;						///<�}�Ӄ��[�N
	BOX_DATA			*box;						///<�{�b�N�X�f�[�^
	PERAPVOICE			*poke_voice[CLIENT_MAX];	///<�|�P�����̖����f�[�^
	POKETCH_DATA		*poketch_data;				///<�|�P�b�`�f�[�^
#ifdef DEBUG_WIFIHISTORY
	WIFI_HISTORY		*wifihistory;				///<���E�ʐM�����f�[�^
#endif
	CONFIG				*config;					///<�Q�[���R���t�B�O
	TVWATCH_BATTLE_WORK * TVWatchBattleWork;		///<�e���r�F�ߊl�ԑg�p
	BATTLE_TOWER_RECORD	btr;						///<�o�g���^���[���їp���[�N
	RECORD				*record;					///<�J�E���g�A�b�v���[�N
	FNOTE_DATA			*fnote_data;				///<�`���m�[�g���[�N
	FRIEND_LIST			*friendlist;				///<�Ƃ������O���[�v�|�C���^
	int					bg_id;						///<�w�iID
	int					ground_id;					///<�n�`ID
	int					place_id;					///<�n�於ID
	int					zone_id;					///<�]�[��ID
	int					time_zone;					///<���ԑђ�`
	int					shinka_place_mode;			///<�ꏊ�i�����iSHINKA_PLACE�`�j
	int					contest_see_flag;			///<�R���e�X�g���������ǂ����̃t���O
	int					mizuki_flag;				///<�~�Y�L�ɂ��������ǂ����̃t���O
//	EVENT_DATA			event_data;					///<�C�x���g�f�[�^
//	TIME				time;						///<����
	int					get_pokemon_client;			///<�ߊl�����|�P������ClientNo�iPOKEPARTY_ENEMY��POKEPARTY_ENEMY_PAIR�j
	int					weather;					///<�V��
	int					level_up_flag;				///<���x���A�b�v�����|�P�����t���O�i�i���`�F�b�N������j
	u32					server_version[CLIENT_MAX];	///<�퓬�T�[�o�v���O�����̃o�[�W�����i�ʐM�ΐ펞�Ɏg�p�j
	u32					battle_status_flag;			///<�퓬������p�t���O
	int					safari_ball;				///<�T�t�@���{�[���̐�
	u32					regulation_flag;			///<���M�����[�V�����t���O
	void				*work;						///<�ėp�I�Ɏg�p���邽�߂̃|�C���^���[�N
}BATTLE_PARAM;

typedef struct{
	BATTLE_PARAM		*bp;
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	PALETTE_FADE_PTR	pfd;									///<�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
	FRIEND_LIST			*recv_flist[4];							///<�t�����h���X�g��M�o�b�t�@�i��M��ɉ���j
	u8					sio_send_buffer[BATTLE_SIO_BUF_SIZE];	///<�ʐM���M�o�b�t�@
	u8					send_count;
	u8					seq_no;
	u16					time_out_count;							///<�ʐM�^�C���A�E�g�p�J�E���^
	void				*time_icon;								///<�ʐM�ҋ@���̎��v�A�C�R���^�X�N
}BATTLE_SIO_WORK;

///<�莝���|�P�����̃T�[�o�p�\����
typedef struct pokemon_server_param POKEMON_SERVER_PARAM;

///<�ΐ�^��p�p�����[�^�\���̐錾
typedef struct record_param RECORD_PARAM;

///<�퓬�V�X�e�����[�N�\����
typedef struct battle_work BATTLE_WORK;

///<�T�[�o�p�p�����[�^�\���̐錾
typedef struct server_param SERVER_PARAM;

///<�N���C�A���g�p�p�����[�^�\���̐錾
typedef struct client_param CLIENT_PARAM;

///<FieldCondition�p�J�E���^�\���̐錾
typedef struct field_condition_count FIELD_CONDITION_COUNT;

///<SideCondition�p�p�����[�^�\���̐錾
typedef struct side_condition_work	SIDE_CONDITION_WORK;

///<OneTurnFlag�p�p�����[�^�\���̐錾
typedef struct one_turn_flag	ONE_TURN_FLAG;

///<OneSelfTurnFlag�p�p�����[�^�\���̐錾
typedef struct one_self_turn_flag	ONE_SELF_TURN_FLAG;

///<WazaOutCheckFlag�p�p�����[�^�\���̐錾
typedef struct waza_out_check_flag	WAZA_OUT_CHECK_FLAG;

///<�Z���ʗp�p�����[�^�\���̐錾
typedef struct waza_kouka_work	WAZA_KOUKA_WORK;

///<SkillIntp�Ŏg�p�����^�X�N�p���[�N�ւ̃|�C���^
typedef	struct tcb_skill_intp_work	TCB_SKILL_INTP_WORK;

///<���b�Z�[�W�\���p���[�N�\����
typedef struct message_param_data MESSAGE_PARAM_DATA;

///<�i���f�����[�N�\����
typedef struct shinka_work SHINKA_WORK;

///<�g���[�i�[AI�\����
typedef struct ai_work_tbl AI_WORK_TBL;

//�퓬�p�֐���`
typedef	void	(*btFunc)(BATTLE_WORK *battle_work);
typedef	void	(*svFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);
typedef	void	(*clFunc)(BATTLE_WORK *battle_work,CLIENT_PARAM *cp);
typedef	BOOL	(*siFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);
typedef	void	(*aiFunc)(BATTLE_WORK *battle_work,SERVER_PARAM *sp);

//abiritycnt�ɂ��p�����[�^�����e�[�u��
extern	const	u8	CondChgTable[][2];

#endif	__ASM_NO_DEF_

#endif __BATTLE_COMMON_H_


