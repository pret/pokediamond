//
//============================================================================================
/**
 * @file	tr_ai_def.h
 * @bfief	�g���[�i�[AI�v���O�����p��`�t�@�C��
 * @author	HisashiSogabe
 * @date	06.04.25
 */
//============================================================================================

//#define	AIWT				((AIWorkTbl *)&UserWork[0x16800])
//#define	AIWT2				((AIWorkTbl2 *)&UserWork[0x16a00])
//#define	AI_PUSH_ADRS		((PushAdrs *)&UserWork[0x16c00])	//4�o�C�g*8+1

#define	LOSS_CALC_OFF	(0)		//�_���[�W���X�v�Z�̂Ԃ�Ȃ�
#define	LOSS_CALC_ON	(1)		//�_���[�W���X�v�Z�̂Ԃꂠ��

//=========================================================================
//	AI_STATUSFLAG�錾
//=========================================================================

#define	AI_STATUSFLAG_END		0x01			//AI�V�[�P���X�̏I��
#define	AI_STATUSFLAG_ESCAPE	0x02			//�ɂ����I��
#define	AI_STATUSFLAG_SAFARI	0x04			//�T�t�@���]�[�����L�̃A�N�V����
#define	AI_STATUSFLAG_FINISH	0x08			//�`�F�b�N����Z���c���Ă��Ă��I��
#define	AI_STATUSFLAG_CONTINUE	0x10			//AI�v�Z�p��

#define	AI_STATUSFLAG_END_OFF		(0x01^0xff)
#define	AI_STATUSFLAG_ESCAPE_OFF	(0x01^0xff)
#define	AI_STATUSFLAG_SAFARI_OFF	(0x04^0xff)
#define	AI_STATUSFLAG_CONTINUE_OFF	(0x10^0xff)			//AI�v�Z�p��

#define	AI_ENEMY_ESCAPE		4
#define	AI_ENEMY_SAFARI		5
#define	AI_ENEMY_RESHUFFLE	6

//=========================================================================
//	AI_THINK_BIT�錾
//=========================================================================

#define	AI_THINK_BIT_BASIC		(0x00000001)			//��{AI
#define	AI_THINK_BIT_ATTACK		(0x00000002)			//�U���^AI
#define	AI_THINK_BIT_EXPERT		(0x00000004)			//�G�L�X�p�[�gAI
#define	AI_THINK_BIT_HOJO		(0x00000008)			//�⏕�ZAI
#define	AI_THINK_BIT_GAMBLE		(0x00000010)			//�M�����u��AI
#define	AI_THINK_BIT_DAMAGE		(0x00000020)			//�_���[�W�d��AI
#define	AI_THINK_BIT_RILAY		(0x00000040)			//�����[�^AI
#define	AI_THINK_BIT_DOUBLE		(0x00000080)			//�_�u���o�g��AI
#define	AI_THINK_BIT_HP_CHECK	(0x00000100)			//HP�Ŕ��fAI
#define	AI_THINK_BIT_WEATHER	(0x00000200)			//�V��ZAI
#define	AI_THINK_BIT_HARASS		(0x00000400)			//���₪�点AI
#define	AI_THINK_BIT_MV_POKE	(0x20000000)			//�ړ��|�P����
#define	AI_THINK_BIT_SAFARI		(0x40000000)			//�T�t�@���]�[��
#define	AI_THINK_BIT_GUIDE		(0x80000000)			//�K�C�h�o�g��

//tr_ai.s waza_ai.c�Ŏg�p�i�}�N����side�Ɏw�肷��l�j
#define	CHECK_DEFENCE			(0)
#define	CHECK_ATTACK			(1)
#define	CHECK_DEFENCE_FRIEND	(2)
#define	CHECK_ATTACK_FRIEND		(3)

#define	CHECK_DEFENCE_TYPE1			(0)
#define	CHECK_ATTACK_TYPE1			(1)
#define	CHECK_DEFENCE_TYPE2			(2)
#define	CHECK_ATTACK_TYPE2			(3)
#define	CHECK_WAZA					(4)
#define	CHECK_DEFENCE_FRIEND_TYPE1	(5)
#define	CHECK_ATTACK_FRIEND_TYPE1	(6)
#define	CHECK_DEFENCE_FRIEND_TYPE2	(7)
#define	CHECK_ATTACK_FRIEND_TYPE2	(8)


//COMP_POWER�Ŏg�p
#define	COMP_POWER_NONE		(0)		//�З͌v�Z���Ȃ��Z
#define	COMP_POWER_NOTOP	(1)		//�_���[�W�ʂ��g�b�v����Ȃ�
#define	COMP_POWER_TOP		(2)		//�_���[�W�ʂ��g�b�v

//IF_FIRST�Ŏg�p
#define	IF_FIRST_ATTACK		(0)		//����������
#define	IF_FIRST_DEFENCE	(1)		//���肪����
#define	IF_FIRST_EQUAL		(2)		//����

//AI_CHECK_AISYOU�Ŏg�p
//AI_CHECK_WAZA_AISYOU�Ŏg�p
#define	AISYOU_4BAI			(160)	//4�{����
#define	AISYOU_2BAI			(80)	//2�{����
#define	AISYOU_15BAI		(60)	//1.5�{����
#define	AISYOU_1BAI			(40)	//1�{����
#define	AISYOU_1_2BAI		(20)	//1/2�{����
#define	AISYOU_1_4BAI		(10)	//1/4�{����
#define	AISYOU_0BAI			(0)		//���ʂȂ�

//AI_IF_PARA_UNDER�Ŏg�p
//AI_IF_PARA_OVER�Ŏg�p
//AI_IF_PARA_EQUAL�Ŏg�p
//AI_IFN_PARA_EQUAL�Ŏg�p
#define	PARA_HP					0x00			//�̗�
#define	PARA_POW				0x01			//�U����
#define	PARA_DEF				0x02			//�h���
#define	PARA_AGI				0x03			//�f����
#define	PARA_SPEPOW				0x04			//���U
#define	PARA_SPEDEF				0x05			//���h
#define	PARA_HIT				0x06			//������
#define	PARA_AVOID				0x07			//���

//AI_IF_POKE_CHECK_STATE,AI_IF_WAZA_CHECK_STATE�Ŏg�p
#define	STATE_KANASIBARI		0x00			//���Ȃ��΂�
#define	STATE_ENCORE			0x01			//�A���R�[��

//AI_CHECK_WEATHER�Ŏg�p
#define	WEATHER_NONE			0x00			//�V��ω��Ȃ�
#define	WEATHER_HARE			0x01			//�ɂق�΂���
#define	WEATHER_AME				0x02			//���܂������
#define	WEATHER_SUNAARASHI		0x03			//���Ȃ��炵���
#define	WEATHER_ARARE			0x04			//�������
#define	WEATHER_HUKAIKIRI		0x05			//�ӂ���������

//AI_IF_LEVEL�Ŏg�p
#define	LEVEL_ATTACK			0x00			//�A�^�b�N�̃��x��������
#define	LEVEL_DEFENCE			0x01			//�f�B�t�F���X�̃��x��������
#define	LEVEL_EQUAL				0x02			//���x�����ꏏ

// AI_HAVE_TOKUSEI, AI_HAVE_WAZA ���Ŏg�p
#define HAVE_NO			0
#define HAVE_YES		1
#define HAVE_UNKNOWN	2

