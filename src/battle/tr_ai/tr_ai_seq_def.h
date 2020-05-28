
//=============================================================================
/**
 * @file	tr_ai_seq_def.h
 * @bfief	�g���[�i�[AI�p�̃}�N����`�t�@�C���i�A�h�o���X�ł��ڐA�j
 * @author	HisashiSogabe
 * @date	2006.03.22
 */
//=============================================================================

#define	__ASM_NO_DEF_
	.include	"..\tr_ai_def.h"
	.include	"../../../include/battle/battle_common.h"
	.include	"../../../include/battle/battle_server.h"
	.include	"../../../include/battle/wazano_def.h"
	.include	"../../../include/battle/tokusyu_def.h"
	.include	"../../../include/poketool/poke_tool.h"
	.include	"../../../include/itemtool/itemsym.h"
	.include	"../../../include/itemtool/itemequip.h"

//======================================================
//	AI�̓���V�[�P���X����macro
//======================================================

	.macro	INIT_CMD
DEF_CMD_COUNT	=	0
	.endm

	.macro	DEF_CMD	symname
\symname	=	DEF_CMD_COUNT
DEF_CMD_COUNT 	=	(DEF_CMD_COUNT + 1)
	.endm

	INIT_CMD
//�����_������
	DEF_CMD		AI_IF_RND_UNDER
	DEF_CMD		AI_IF_RND_OVER
	DEF_CMD		AI_IF_RND_EQUAL
	DEF_CMD		AI_IFN_RND_EQUAL

//�|�C���g�����Z
	DEF_CMD		AI_INCDEC

//HP�ł̕���
	DEF_CMD		AI_IF_HP_UNDER
	DEF_CMD		AI_IF_HP_OVER
	DEF_CMD		AI_IF_HP_EQUAL
	DEF_CMD		AI_IFN_HP_EQUAL

//��Ԉُ���`�F�b�N
	DEF_CMD		AI_IF_COND
	DEF_CMD		AI_IFN_COND
	DEF_CMD		AI_IF_COND2
	DEF_CMD		AI_IFN_COND2
	DEF_CMD		AI_IF_WAZAKOUKA
	DEF_CMD		AI_IFN_WAZAKOUKA
	DEF_CMD		AI_IF_SIDE_CONDITION
	DEF_CMD		AI_IFN_SIDE_CONDITION		//0x10

//�v�Z���ʂɂ�镪��
	DEF_CMD		AI_IF_UNDER
	DEF_CMD		AI_IF_OVER
	DEF_CMD		AI_IF_EQUAL
	DEF_CMD		AI_IFN_EQUAL
	DEF_CMD		AI_IF_BIT
	DEF_CMD		AI_IFN_BIT

//�Z�i���o�[�̃`�F�b�N
	DEF_CMD		AI_IF_WAZANO
	DEF_CMD		AI_IFN_WAZANO

//�e�[�u���Q�Ƃɂ�镪��
	DEF_CMD		AI_IF_TABLE_JUMP
	DEF_CMD		AI_IFN_TABLE_JUMP

//�������_���[�W�Z�������Ă��邩���f���ĕ���
	DEF_CMD		AI_IF_HAVE_DAMAGE_WAZA
	DEF_CMD		AI_IFN_HAVE_DAMAGE_WAZA

//�^�[���̃`�F�b�N
	DEF_CMD		AI_CHECK_TURN

//�^�C�v�̃`�F�b�N
	DEF_CMD		AI_CHECK_TYPE

//�U���Z���ǂ����̃`�F�b�N
	DEF_CMD		AI_CHECK_IRYOKU

//�З͂���ԍ������̃`�F�b�N
	DEF_CMD		AI_COMP_POWER

//�O�̃^�[���Ɏg�����Z�̃`�F�b�N
	DEF_CMD		AI_CHECK_LAST_WAZA

//�i�[���ꂽ�Z�̃^�C�v�`�F�b�N
	DEF_CMD		AI_IF_WAZA_TYPE			//0x20
	DEF_CMD		AI_IFN_WAZA_TYPE

//�ǂ��炪��s���̃`�F�b�N
	DEF_CMD		AI_IF_FIRST
	DEF_CMD		AI_IFN_FIRST

//�T�������̂��邩�̃`�F�b�N
	DEF_CMD		AI_CHECK_BENCH_COUNT

//���݂̋Z�i���o�[�̃`�F�b�N
	DEF_CMD		AI_CHECK_WAZANO

//���݂̋Z�i���o�[�̃V�[�P���X�i���o�[�̃`�F�b�N
	DEF_CMD		AI_CHECK_WAZASEQNO

//����\�͂̃`�F�b�N
	DEF_CMD		AI_CHECK_TOKUSEI

//�����Ƒ���̑����`�F�b�N
	DEF_CMD		AI_CHECK_AISYOU
	DEF_CMD		AI_CHECK_WAZA_AISYOU

//�T���̏�ԃ`�F�b�N
	DEF_CMD		AI_IF_BENCH_COND
	DEF_CMD		AI_IFN_BENCH_COND

//�V��`�F�b�N
	DEF_CMD		AI_CHECK_WEATHER

//�Z�̃V�[�P���X�i���o�[���`�F�b�N���āA����
	DEF_CMD		AI_IF_WAZA_SEQNO_JUMP
	DEF_CMD		AI_IFN_WAZA_SEQNO_JUMP

//�����⑊��̃p�����[�^�ω��l���Q�Ƃ��ĕ���
	DEF_CMD		AI_IF_PARA_UNDER
	DEF_CMD		AI_IF_PARA_OVER				//0x30
	DEF_CMD		AI_IF_PARA_EQUAL
	DEF_CMD		AI_IFN_PARA_EQUAL

//�Z�̃_���[�W�v�Z�����đ��肪�m���ɂȂ邩�`�F�b�N
	DEF_CMD		AI_IF_WAZA_HINSHI
	DEF_CMD		AI_IFN_WAZA_HINSHI

//����̋Z�������Ă��邩�̃`�F�b�N�����ĕ���
	DEF_CMD		AI_IF_HAVE_WAZA
	DEF_CMD		AI_IFN_HAVE_WAZA

//����̋Z�V�[�P���X�������Ă��邩�̃`�F�b�N�����ĕ���
	DEF_CMD		AI_IF_HAVE_WAZA_SEQNO
	DEF_CMD		AI_IFN_HAVE_WAZA_SEQNO

//�|�P�����̏�Ԃ��`�F�b�N�����ĕ���
	DEF_CMD		AI_IF_POKE_CHECK_STATE

//�Z�̏�Ԃ��`�F�b�N�����ĕ���
	DEF_CMD		AI_IF_WAZA_CHECK_STATE

//�ɂ�������񂽂�
	DEF_CMD		AI_ESCAPE

//�T�t�@���]�[���ł̓�����m�����v�Z���ē�����Ƃ��̃A�h���X���w��
	DEF_CMD		AI_SAFARI_ESCAPE_JUMP

//�T�t�@���]�[���ł̓���A�N�V������I��
	DEF_CMD		AI_SAFARI

//�����A�C�e���̃`�F�b�N
	DEF_CMD		AI_CHECK_ITEM

//�����A�C�e���̃`�F�b�N
	DEF_CMD		AI_CHECK_SOUBIITEM

//�|�P�����̐��ʂ̃`�F�b�N
	DEF_CMD		AI_CHECK_POKESEX

//�˂����܂��J�E���^�̃`�F�b�N
	DEF_CMD		AI_CHECK_NEKODAMASI			//0x40

//�����킦��J�E���^�̃`�F�b�N
	DEF_CMD		AI_CHECK_TAKUWAERU

//�퓬�^�C�v�̃`�F�b�N
	DEF_CMD		AI_CHECK_FIGHT_TYPE

//���T�C�N���ł���A�C�e���̃`�F�b�N
	DEF_CMD		AI_CHECK_RECYCLE_ITEM

//���[�N�ɓ����Ă���Z�i���o�[�̃^�C�v���`�F�b�N
	DEF_CMD		AI_CHECK_WORKWAZA_TYPE

//���[�N�ɓ����Ă���Z�i���o�[�̈З͂��`�F�b�N
	DEF_CMD		AI_CHECK_WORKWAZA_POW

//���[�N�ɓ����Ă���Z�i���o�[�̃V�[�P���X�i���o�[���`�F�b�N
	DEF_CMD		AI_CHECK_WORKWAZA_SEQNO

//�܂���J�E���^���`�F�b�N
	DEF_CMD		AI_CHECK_MAMORU_COUNT

//�ėp�I�Ȗ���
	DEF_CMD		AI_GOSUB
	DEF_CMD		AI_JUMP
	DEF_CMD		AI_AIEND

//���݂��̃��x�����`�F�b�N���ĕ���
	DEF_CMD		AI_IF_LEVEL

//������Ԃ��`�F�b�N���ĕ���
	DEF_CMD		AI_IF_CHOUHATSU
	DEF_CMD		AI_IFN_CHOUHATSU

//�U���Ώۂ��������ǂ����`�F�b�N
	DEF_CMD		AI_IF_MIKATA_ATTACK

//�w��^�C�v�������Ă��邩�ǂ����`�F�b�N
	DEF_CMD		AI_CHECK_HAVE_TYPE

//�w��Ƃ������������Ă��邩�ǂ����`�F�b�N
	DEF_CMD		AI_CHECK_HAVE_TOKUSEI		//0x50

//���������炢�уp���[�A�b�v��Ԃ��`�F�b�N���ĕ���
	DEF_CMD		AI_IF_ALREADY_MORAIBI

//�A�C�e���������Ă��邩�`�F�b�N���ĕ���
	DEF_CMD		AI_IF_HAVE_ITEM

//FIELD_CONDITION�`�F�b�N
	DEF_CMD		AI_FIELD_CONDITION_CHECK

//SIDE_CONDITION�̃J�E���g���擾
	DEF_CMD		AI_CHECK_SIDE_CONDITION_COUNT

//�T���|�P������HP�������`�F�b�N
	DEF_CMD		AI_IF_BENCH_HPDEC

//�T���|�P������PP�������`�F�b�N
	DEF_CMD		AI_IF_BENCH_PPDEC

//�����A�C�e���̂Ȃ�����З͂��擾
	DEF_CMD		AI_CHECK_NAGETSUKERU_IRYOKU

//PP���擾
	DEF_CMD		AI_CHECK_PP_REMAIN

//�Ƃ��Ă����`�F�b�N
	DEF_CMD		AI_IF_TOTTEOKI

//�Z�̕��ރ`�F�b�N
	DEF_CMD		AI_CHECK_WAZA_KIND

//���肪�Ō�ɏo�����Z�̕��ރ`�F�b�N
	DEF_CMD		AI_CHECK_LAST_WAZA_KIND

//�f�����Ŏw�肵���������ʂ��`�F�b�N
	DEF_CMD		AI_CHECK_AGI_RANK

//�X���[�X�^�[�g���^�[���ڂ�
	DEF_CMD		AI_CHECK_SLOWSTART_TURN

//�T���ɂ�������_���[�W��^���邩�ǂ����`�F�b�N
	DEF_CMD		AI_IF_BENCH_DAMAGE_MAX

//���Q�̋Z�������Ă��邩�`�F�b�N
	DEF_CMD		AI_IF_HAVE_BATSUGUN

//�w�肵������̍Ō�ɏo�����Z�Ǝ����̋Z�Ƃ̃_���[�W���`�F�b�N
	DEF_CMD		AI_IF_LAST_WAZA_DAMAGE_CHECK

//�w�肵������̃X�e�[�^�X�㏸���̒l���擾
	DEF_CMD		AI_CHECK_STATUS_UP

//�w�肵������Ƃ̃X�e�[�^�X�������擾
	DEF_CMD		AI_CHECK_STATUS_DIFF

//�w�肵������Ƃ̃X�e�[�^�X���`�F�b�N���ĕ���
	DEF_CMD		AI_IF_CHECK_STATUS_UNDER
	DEF_CMD		AI_IF_CHECK_STATUS_OVER
	DEF_CMD		AI_IF_CHECK_STATUS_EQUAL

//�З͂���ԍ������̃`�F�b�N�i�p�[�g�i�[���܂ށj
	DEF_CMD		AI_COMP_POWER_WITH_PARTNER

//�w�肵�����肪�m�����`�F�b�N���ĕ���
	DEF_CMD		AI_IF_HINSHI
	DEF_CMD		AI_IFN_HINSHI

//�Z���ʂ��l�����������擾�i�ړ��|�P������p����ȊO�̗p�r�Ŏg�p����̂͌��ցj
	DEF_CMD		AI_GET_TOKUSEI

//------------------------------------------------------------
//
//	�����_������
//
//	value:��r����l
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_RND_UNDER		value,adrs
	.long		AI_IF_RND_UNDER
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_RND_OVER			value,adrs
	.long		AI_IF_RND_OVER
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_RND_EQUAL		value,adrs
	.long		AI_IF_RND_EQUAL
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_RND_EQUAL		value,adrs
	.long		AI_IFN_RND_EQUAL
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�|�C���g�����Z
//
//	value:�����Z����l
//
//------------------------------------------------------------

	.macro		INCDEC				value
	.long		AI_INCDEC
	.long		\value
	.endm

//------------------------------------------------------------
//
//	HP�ł̕���
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	value:��r����l
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_HP_UNDER			side,value,adrs
	.long		AI_IF_HP_UNDER
	.long		\side
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_HP_OVER			side,value,adrs
	.long		AI_IF_HP_OVER
	.long		\side
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_HP_EQUAL			side,value,adrs
	.long		AI_IF_HP_EQUAL
	.long		\side
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_HP_EQUAL			side,value,adrs
	.long		AI_IFN_HP_EQUAL
	.long		\side
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	��Ԉُ���`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	condition:��r����l�iserver.def�ɒ�`�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

//CONDITION_�`�n�̃`�F�b�N
	.macro		IF_COND				side,condition,adrs
	.long		AI_IF_COND
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_COND			side,condition,adrs
	.long		AI_IFN_COND
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

//CONDITION2_�`�n�̃`�F�b�N
	.macro		IF_COND2			side,condition,adrs
	.long		AI_IF_COND2
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_COND2			side,condition,adrs
	.long		AI_IFN_COND2
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

//WAZAKOUKA_�`�n�̃`�F�b�N
	.macro		IF_WAZAKOUKA		side,condition,adrs
	.long		AI_IF_WAZAKOUKA
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_WAZAKOUKA		side,condition,adrs
	.long		AI_IFN_WAZAKOUKA
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

//SODE_CONDITION_�`�n�̃`�F�b�N
	.macro		IF_SIDE_CONDITION	side,condition,adrs
	.long		AI_IF_SIDE_CONDITION
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_SIDE_CONDITION	side,condition,adrs
	.long		AI_IFN_SIDE_CONDITION
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�v�Z���ʂɂ�镪��i���[�N�Ɋi�[����n�̖��߂̂��ƂɎ��s����j
//
//	value:��r����l
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_UNDER			value,adrs
	.long		AI_IF_UNDER
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_OVER				value,adrs
	.long		AI_IF_OVER
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_EQUAL			value,adrs
	.long		AI_IF_EQUAL
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_EQUAL			value,adrs
	.long		AI_IFN_EQUAL
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_BIT				value,adrs
	.long		AI_IF_BIT
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_BIT				value,adrs
	.long		AI_IFN_BIT
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�Z�i���o�[���`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_WAZANO		wazano,adrs
	.long		AI_IF_WAZANO
	.long		\wazano
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_WAZANO		wazano,adrs
	.long		AI_IF_WAZANO
	.long		\wazano
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�w�肳�ꂽ�e�[�u�����Q�Ƃ��Ĉ�v�A�s��v�ŕ���
//
//	tableadrs:�`�F�b�N����i���o�[�����񂳂ꂽ�e�[�u���̃A�h���X
//	jumpadrs:�����ɍ��v�����Ƃ��̂Ƃѐ�	
//
//	�e�[�u���̏I�[��1BYTE�̕���0xff�A2BYTE�̕���0xffff
//
//------------------------------------------------------------

	.macro		IF_TABLE_JUMP		tableadrs,jumpadrs	
	.long		AI_IF_TABLE_JUMP
	.long		(\tableadrs-.)/4-2
	.long		(\jumpadrs-.)/4-1
	.endm

	.macro		IFN_TABLE_JUMP		tableadrs,jumpadrs
	.long		AI_IFN_TABLE_JUMP
	.long		(\tableadrs-.)/4-2
	.long		(\jumpadrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�������_���[�W�Z�������Ă��邩���f���ĕ���
//
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_HAVE_DAMAGE_WAZA		adrs
	.long		AI_IF_HAVE_DAMAGE_WAZA
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_HAVE_DAMAGE_WAZA	adrs
	.long		AI_IFN_HAVE_DAMAGE_WAZA
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�^�[���̃`�F�b�N�i�����^�[���ڂ������[�N�ɓ����j
//------------------------------------------------------------

	.macro		CHECK_TURN
	.long		AI_CHECK_TURN
	.endm

//------------------------------------------------------------
//
//	�^�C�v�̃`�F�b�N(�|�P�������邢�͋Z�̃^�C�v�����[�N�ɓ����j
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_TYPE			side
	.long		AI_CHECK_TYPE
	.long		\side
	.endm

//------------------------------------------------------------
//	�U���Z���ǂ����̃`�F�b�N�i�Z�̈З͂����[�N�ɓ����)
//------------------------------------------------------------

	.macro		CHECK_IRYOKU
	.long		AI_CHECK_IRYOKU
	.endm

//------------------------------------------------------------
//	�З͂���ԍ������̃`�F�b�N
//
//	@param		flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//
//------------------------------------------------------------
	.macro		COMP_POWER		flag
	.long		AI_COMP_POWER
	.long		\flag
	.endm

//------------------------------------------------------------
//
//	�O�̃^�[���Ɏg�����Z�̃`�F�b�N�i�Z�̃i���o�[�����[�N�ɓ����j
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_LAST_WAZA		side
	.long		AI_CHECK_LAST_WAZA
	.long		\side
	.endm

//------------------------------------------------------------
//
//	�i�[���ꂽ�Z�̃^�C�v�`�F�b�N
//
//	type:�`�F�b�N����^�C�v�iagbmons.def�ɒ�`�j	
//	adrs:��ѐ�
//
//------------------------------------------------------------
	.macro		IF_WAZA_TYPE		type,adrs
	.long		AI_IF_WAZA_TYPE
	.long		\type
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_WAZA_TYPE		type,adrs
	.long		AI_IFN_WAZA_TYPE
	.long		\type
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�ǂ��炪��s���̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_FIRST			side,adrs
	.long		AI_IF_FIRST
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_FIRST			side,adrs
	.long		AI_IFN_FIRST
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�T�������̂��邩�`�F�b�N�i�������[�N�ɓ����j
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_BENCH_COUNT			side
	.long		AI_CHECK_BENCH_COUNT
	.long		\side
	.endm

//------------------------------------------------------------
//	���݂̋Z�i���o�[�̃`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_WAZANO
	.long		AI_CHECK_WAZANO
	.endm

//------------------------------------------------------------
//	���݂̋Z�i���o�[�̃V�[�P���X�i���o�[�̃`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_WAZASEQNO
	.long		AI_CHECK_WAZASEQNO
	.endm

//------------------------------------------------------------
//
//	����\�͂̃`�F�b�N�i����\�̓i���o�[�����[�N�ɓ����j
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_TOKUSEI		side
	.long		AI_CHECK_TOKUSEI
	.long		\side
	.endm

//------------------------------------------------------------
//
//	�����Ƒ���̑����`�F�b�N���Ĉ�Ԃ����{�������[�N�Ɋi�[
//
//------------------------------------------------------------

	.macro		CHECK_AISYOU
	.long		AI_CHECK_AISYOU
	.endm

//------------------------------------------------------------
//
//	�Z�Ƒ���̑������`�F�b�N���Ă��ăA�h���X�ɃW�����v
//
//	aisyou:�Z�Ƒ���̑����ɂ��{���itr_ai_def.h�ɒ�`�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		CHECK_WAZA_AISYOU		aisyou,adrs
	.long		AI_CHECK_WAZA_AISYOU
	.long		\aisyou
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�T���̏�ԃ`�F�b�N
//
//	IF_COND
//
//------------------------------------------------------------

	.macro		IF_BENCH_COND		side,condition,adrs
	.long		AI_IF_BENCH_COND
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_BENCH_COND		side,condition,adrs
	.long		AI_IFN_BENCH_COND
	.long		\side
	.long		\condition
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�V��`�F�b�N�i�V��i���o�[�����[�N�ɓ����j
//				�i�V��i���o�[��tr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_WEATHER
	.long		AI_CHECK_WEATHER
	.endm

//------------------------------------------------------------
//
//	�Z�̃V�[�P���X�i���o�[���`�F�b�N���āA����
//
//	seqno:�Z�̃V�[�P���X�i���o�[
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_WAZA_SEQNO_JUMP		seqno,adrs
	.long		AI_IF_WAZA_SEQNO_JUMP
	.long		\seqno
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_WAZA_SEQNO_JUMP		seqno,adrs
	.long		AI_IFN_WAZA_SEQNO_JUMP
	.long		\seqno
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�����⑊��̃p�����[�^�ω��l���Q�Ƃ��ĕ���
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	para:�`�F�b�N����p�����[�^�itr_ai_def.h�ɒ�`�j
//	value:��r����l�i�O�`�P�Q�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_PARA_UNDER		side,para,value,adrs
	.long		AI_IF_PARA_UNDER
	.long		\side
	.long		\para
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_PARA_OVER		side,para,value,adrs
	.long		AI_IF_PARA_OVER
	.long		\side
	.long		\para
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IF_PARA_EQUAL		side,para,value,adrs
	.long		AI_IF_PARA_EQUAL
	.long		\side
	.long		\para
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_PARA_EQUAL		side,para,value,adrs
	.long		AI_IFN_PARA_EQUAL
	.long		\side
	.long		\para
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�Z�̃_���[�W�v�Z�����đ��肪�m���ɂȂ邩�`�F�b�N���ĕ���
//
//	@param		flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//	@param		adrs	��ѐ�
//
//------------------------------------------------------------

	.macro		IF_WAZA_HINSHI		flag,adrs
	.long		AI_IF_WAZA_HINSHI
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_WAZA_HINSHI		flag,adrs
	.long		AI_IFN_WAZA_HINSHI
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	����̋Z�������Ă��邩�̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	wazano:�`�F�b�N����Z�i���o�[
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_HAVE_WAZA		side,wazano,adrs
	.long		AI_IF_HAVE_WAZA
	.long		\side
	.long		\wazano
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_HAVE_WAZA		side,wazano,adrs
	.long		AI_IFN_HAVE_WAZA
	.long		\side
	.long		\wazano
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	����̋Z�V�[�P���X�������Ă��邩�̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	seqno:�`�F�b�N����Z�V�[�P���X�i���o�[
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_HAVE_WAZA_SEQNO		side,seqno,adrs
	.long		AI_IF_HAVE_WAZA_SEQNO
	.long		\side
	.long		\seqno
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_HAVE_WAZA_SEQNO		side,seqno,adrs
	.long		AI_IFN_HAVE_WAZA_SEQNO
	.long		\side
	.long		\seqno
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�|�P�����̏�Ԃ��`�F�b�N���ĕ���i���Ȃ��΂�Ƃ��A�A���R�[���Ƃ��j
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	id:�`�F�b�N������ID(tr_ai_def.h�ɒ�`�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_POKE_CHECK_STATE		side,id,adrs
	.long		AI_IF_POKE_CHECK_STATE
	.long		\side
	.long		\id
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	���v�Z���Ă���Z�̏�Ԃ��`�F�b�N���ĕ���
//
//	id:�`�F�b�N������ID(tr_ai_def.h�ɒ�`�j
//	adrs:��ѐ�
//
//------------------------------------------------------------

	.macro		IF_WAZA_CHECK_STATE		id,adrs
	.long		AI_IF_WAZA_CHECK_STATE
	.long		\id
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�ɂ�������񂽂�
//------------------------------------------------------------

	.macro		ESCAPE
	.long		AI_ESCAPE
	.endm

//------------------------------------------------------------
//	�T�t�@���]�[���ł̓�����m�����v�Z���ē�����Ƃ��̃A�h���X���w��
//------------------------------------------------------------

	.macro		SAFARI_ESCAPE_JUMP		adrs
	.long		AI_SAFARI_ESCAPE_JUMP
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�T�t�@���]�[���ł̓���A�N�V������I��
//------------------------------------------------------------

	.macro		SAFARI
	.long		AI_SAFARI
	.endm


//------------------------------------------------------------
//
//		�����A�C�e���̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_ITEM		side
	.long		AI_CHECK_ITEM
	.long		\side
	.endm

//------------------------------------------------------------
//
//		�����A�C�e���̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_SOUBIITEM		side
	.long		AI_CHECK_SOUBIITEM
	.long		\side
	.endm

//------------------------------------------------------------
//
//		�|�P�����̐��ʂ̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_POKESEX		side
	.long		AI_CHECK_POKESEX
	.long		\side
	.endm

//------------------------------------------------------------
//
//		�˂����܂��J�E���^�̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_NEKODAMASI	side
	.long		AI_CHECK_NEKODAMASI
	.long		\side
	.endm

//------------------------------------------------------------
//
//		�����킦��J�E���^�̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_TAKUWAERU		side
	.long		AI_CHECK_TAKUWAERU
	.long		\side
	.endm

//------------------------------------------------------------
//		�퓬�^�C�v�̃`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_FIGHT_TYPE
	.long		AI_CHECK_FIGHT_TYPE
	.endm

//------------------------------------------------------------
//
//		���T�C�N���ł���A�C�e���̃`�F�b�N
//
//	side:�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------

	.macro		CHECK_RECYCLE_ITEM	side
	.long		AI_CHECK_RECYCLE_ITEM
	.long		\side
	.endm

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̃^�C�v���`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_WORKWAZA_TYPE
	.long		AI_CHECK_WORKWAZA_TYPE
	.endm

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̈З͂��`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_WORKWAZA_POW
	.long		AI_CHECK_WORKWAZA_POW
	.endm

//------------------------------------------------------------
//	���[�N�ɓ����Ă���Z�i���o�[�̃V�[�P���X�i���o�[���`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_WORKWAZA_SEQNO
	.long		AI_CHECK_WORKWAZA_SEQNO
	.endm

//------------------------------------------------------------
//	�܂���J�E���^���`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_MAMORU_COUNT		side
	.long		AI_CHECK_MAMORU_COUNT
	.long		\side
	.endm

//------------------------------------------------------------
//	�ėp�I�Ȗ��ߌQ
//------------------------------------------------------------

//�ėp�I�Ȗ���
	.macro		GOSUB		adrs
	.long		AI_GOSUB
	.long		(\adrs-.)/4-1
	.endm

	.macro		JUMP		adrs
	.long		AI_JUMP
	.long		(\adrs-.)/4-1
	.endm

	.macro		AIEND
	.long		AI_AIEND
	.endm

//------------------------------------------------------------
//	���݂��̃��x�����`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_LEVEL		value,adrs
	.long		AI_IF_LEVEL
	.long		\value
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	������Ԃ��`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_CHOUHATSU	adrs
	.long		AI_IF_CHOUHATSU
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_CHOUHATSU	adrs
	.long		AI_IFN_CHOUHATSU
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�U���Ώۂ��������ǂ����`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_MIKATA_ATTACK	adrs
	.long		AI_IF_MIKATA_ATTACK
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�w�肳�ꂽ�^�C�v�������Ă��邩�`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_HAVE_TYPE			side, type
	.long		AI_CHECK_HAVE_TYPE
	.long		\side
	.long		\type
	.endm

//------------------------------------------------------------
//	�w�肳�ꂽ�Ƃ������������Ă��邩�`�F�b�N
//------------------------------------------------------------

	.macro		CHECK_HAVE_TOKUSEI		side, abi
	.long		AI_CHECK_HAVE_TOKUSEI
	.long		\side
	.long		\abi
	.endm

//------------------------------------------------------------
//	���������炢�уp���[�A�b�v��Ԃ��`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_ALREADY_MORAIBI		side, adrs
	.long		AI_IF_ALREADY_MORAIBI
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�A�C�e���������Ă��邩�`�F�b�N���ĕ���
//------------------------------------------------------------

	.macro		IF_HAVE_ITEM		side, item, adrs
	.long		AI_IF_HAVE_ITEM
	.long		\side
	.long		\item
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	FIELD_CONDITION�`�F�b�N
//
//	@param	flag	�`�F�b�N����t�B�[���h�R���f�B�V�����ibattle_server.h�ɒ�`�j
//	@param	adrs	�`�F�b�N�����t�B�[���h�R���f�B�V���������������̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		FIELD_CONDITION_CHECK	flag,adrs
	.long		AI_FIELD_CONDITION_CHECK
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	SIDE_CONDITION�̃J�E���g���擾
//
//	@param	side	�擾���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	flag	�`�F�b�N����t�B�[���h�R���f�B�V�����ibattle_server.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_SIDE_CONDITION_COUNT	side,flag
	.long		AI_CHECK_SIDE_CONDITION_COUNT
	.long		\side
	.long		\flag
	.endm
	
//------------------------------------------------------------
//	�T���|�P������HP�������`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	adrs	HP���������|�P�������������̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_BENCH_HPDEC		side,adrs
	.long		AI_IF_BENCH_HPDEC
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�T���|�P������PP�������`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	adrs	PP���������|�P�������������̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_BENCH_PPDEC		side,adrs
	.long		AI_IF_BENCH_PPDEC
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�����A�C�e���̂Ȃ�����З͂��擾
//
//	@param	side	�擾���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_NAGETSUKERU_IRYOKU	side
	.long		AI_CHECK_NAGETSUKERU_IRYOKU
	.long		\side
	.endm

//------------------------------------------------------------
//	���݃`�F�b�N���̋Z�̎c��PP���擾
//------------------------------------------------------------
	.macro		CHECK_PP_REMAIN
	.long		AI_CHECK_PP_REMAIN
	.endm

//------------------------------------------------------------
//
//	�Ƃ��Ă����`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//	@param	adrs	�Ƃ��Ă������o���鎞�̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_TOTTEOKI		side,adrs
	.long		AI_IF_TOTTEOKI
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//	�Z�̕��ރ`�F�b�N
//------------------------------------------------------------
	.macro		CHECK_WAZA_KIND
	.long		AI_CHECK_WAZA_KIND
	.endm

//------------------------------------------------------------
//	���肪�Ō�ɏo�����Z�̕��ރ`�F�b�N
//------------------------------------------------------------
	.macro		CHECK_LAST_WAZA_KIND
	.long		AI_CHECK_LAST_WAZA_KIND
	.endm

//------------------------------------------------------------
//
//	�f�����Ŏw�肵���������ʂ��`�F�b�N
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_AGI_RANK		side
	.long		AI_CHECK_AGI_RANK
	.long		\side
	.endm

//------------------------------------------------------------
//
//	�X���[�X�^�[�g���^�[���ڂ�
//
//	@param	side	�`�F�b�N���鑤���w��itr_ai_def.h�ɒ�`�j
//
//------------------------------------------------------------
	.macro		CHECK_SLOWSTART_TURN	side
	.long		AI_CHECK_SLOWSTART_TURN
	.long		\side
	.endm

//------------------------------------------------------------
//
//	�T���ɂ�������_���[�W��^���邩�ǂ����`�F�b�N
//
//	@param	flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//	@param	adrs	�^����ꍇ�̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_BENCH_DAMAGE_MAX		flag,adrs
	.long		AI_IF_BENCH_DAMAGE_MAX
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	���Q�̋Z�������Ă��邩�`�F�b�N
//
//	@param	adrs	�����Ă����Ƃ��̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_HAVE_BATSUGUN		adrs
	.long		AI_IF_HAVE_BATSUGUN
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�w�肵������̍Ō�ɏo�����Z�Ǝ����̋Z�Ƃ̃_���[�W���`�F�b�N
//
//	@param	side	�`�F�b�N���鑤
//	@param	flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//	@param	adrs	�`�F�b�N�������̕����_���[�W���傫�����̂Ƃѐ�
//
//------------------------------------------------------------
	.macro		IF_LAST_WAZA_DAMAGE_CHECK	side,flag,adrs
	.long		AI_IF_LAST_WAZA_DAMAGE_CHECK
	.long		\side
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�w�肵������̃X�e�[�^�X�㏸���̒l���擾
//
//	@param	side	�`�F�b�N���鑤
//
//------------------------------------------------------------
	.macro		CHECK_STATUS_UP		side
	.long		AI_CHECK_STATUS_UP
	.long		\side
	.endm

//------------------------------------------------------------
//
//	�w�肵������Ƃ̃X�e�[�^�X�������擾
//
//	@param	side	�`�F�b�N���鑤
//	@param	flag	�`�F�b�N����X�e�[�^�X���
//					COND_POW:�U����
//					COND_DEF:�h���
//					COND_SPEPOW:���U
//					COND_SPEDEF:���h
//
//------------------------------------------------------------
	.macro		CHECK_STATUS_DIFF		side,flag
	.long		AI_CHECK_STATUS_DIFF
	.long		\side
	.long		\flag
	.endm

//------------------------------------------------------------
//
//	�w�肵������Ƃ̃X�e�[�^�X���`�F�b�N���ĕ���
//
//	@param	side	�`�F�b�N���鑤
//	@param	flag	�`�F�b�N����X�e�[�^�X���
//					COND_HP:HP
//					COND_POW:�U����
//					COND_DEF:�h���
//					COND_SPEPOW:���U
//					COND_SPEDEF:���h
//	@param	adrs	�����
//
//------------------------------------------------------------
//��������
	.macro		IF_CHECK_STATUS_UNDER		side,flag,adrs
	.long		AI_IF_CHECK_STATUS_UNDER
	.long		\side
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//��������
	.macro		IF_CHECK_STATUS_OVER		side,flag,adrs
	.long		AI_IF_CHECK_STATUS_OVER
	.long		\side
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//�����l
	.macro		IF_CHECK_STATUS_EQUAL		side,flag,adrs
	.long		AI_IF_CHECK_STATUS_EQUAL
	.long		\side
	.long		\flag
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�З͂���ԍ������̃`�F�b�N�i�p�[�g�i�[���܂ށj
//
//	@param		flag	�_���[�W���X�v�Z�̂Ԃꂠ��Ȃ��t���O
//
//------------------------------------------------------------
	.macro		COMP_POWER_WITH_PARTNER		flag
	.long		AI_COMP_POWER_WITH_PARTNER
	.long		\flag
	.endm

//------------------------------------------------------------
//
//	�w�肵�����肪�m�����`�F�b�N���ĕ���
//
//	@param		side	�`�F�b�N���鑊��iCHECK_ATTACK�ACHECK_DEFENCE�͎w��ł��܂���i�m�������肦�Ȃ��j�j
//	@param		adrs	�`�F�b�N���ʂł̕����iIF_HINSHI�F�m���������� IFN_HINSHI�F�m������Ȃ������Ƃ��j
//
//------------------------------------------------------------
	.macro		IF_HINSHI		side,adrs
	.long		AI_IF_HINSHI
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

	.macro		IFN_HINSHI		side,adrs
	.long		AI_IFN_HINSHI
	.long		\side
	.long		(\adrs-.)/4-1
	.endm

//------------------------------------------------------------
//
//	�Z���ʂ��l�����������擾�i�ړ��|�P������p����ȊO�̗p�r�Ŏg�p����̂͌��ցj
//
//	@param		side	�擾���鑊��
//
//------------------------------------------------------------
	.macro		GET_TOKUSEI	side
	.long		AI_GET_TOKUSEI
	.long		\side
	.endm

//------------------------------------------------------------
//�A�h���X���I�t�Z�b�g�ɕϊ�
//------------------------------------------------------------
	.macro		ADRS		dest,src
	.long		(\dest-\src)/4
	.endm

