//============================================================================================
/**
 * @file	ug_itemtype.h
 * @brief	�n���A�C�e���^�C�v�p�w�b�_
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================

#ifndef __UG_ITEMTYPE_H__
#define __UG_ITEMTYPE_H__


// �ق��΂̎��

#define STONE_TYPE_NONE    (0)
#define STONE_TYPE_DIAMOND (1)    //  ���񂲂�����
#define STONE_TYPE_PEARL   (2)      //  �܂��낾��
#define STONE_TYPE_RED     (3)        //  ����������
#define STONE_TYPE_BLUE    (4)       //  ����������
#define STONE_TYPE_GREEN   (5)      //  �݂ǂ�̂���
#define STONE_TYPE_MAX     (6)

// ���߂���
#define DIG_PARTS_NONE       (STONE_TYPE_NONE)
#define DIG_PARTS_KONGOU_S   (STONE_TYPE_DIAMOND)   //���񂲂�����	KASEKI_KONGOU_S
#define DIG_PARTS_SIRATAMA_S (STONE_TYPE_PEARL) //���炽��	KASEKI_SIRATAMA_S
#define DIG_PARTS_RED_S      (STONE_TYPE_RED)        //�Ԃ��^�}
#define DIG_PARTS_BLUE_S     (STONE_TYPE_BLUE)       //���^�}
#define DIG_PARTS_GREEN_S    (STONE_TYPE_GREEN)      //�΂̃^�}
#define DIG_PARTS_KONGOU_L   (6)  //�������񂲂�����	KASEKI_KONGOU_L
#define DIG_PARTS_SIRATAMA_L (7) //�������炽��	KASEKI_SIRATAMA_L
#define DIG_PARTS_RED_L      (8)//�������񂲂�����	KASEKI_KONGOU_L
#define DIG_PARTS_BLUE_L     (9) //�������񂲂�����	KASEKI_KONGOU_L
#define DIG_PARTS_GREEN_L    (10)//�������炽��	KASEKI_SIRATAMA_L
#define DIG_PARTS_TREASURE_MIN   (11)
#define DIG_PARTS_CIRCLE   (DIG_PARTS_TREASURE_MIN)        //�܂�܂�	KASEKI_
#define DIG_PARTS_KEYSTONE   (12)        //���Ȃ�	KASEKI_
#define DIG_PARTS_SUN       (13) //�����悤�̂���	KASEKI_SUN
#define DIG_PARTS_STAR      (14) //�ق��̂�����	KASEKI_STAR
#define DIG_PARTS_MOON      (15) //���̂���	KASEKI_MOON
#define DIG_PARTS_HARD      (16) //����������	KASEKI_HARD
#define DIG_PARTS_KAMINARI  (17) //���݂Ȃ�̂���	KASEKI_KAMINARI
#define DIG_PARTS_KAWARAZU  (18) //����炸�̂���	KASEKI_KAWARAZU
#define DIG_PARTS_HONOO     (19) //�ق̂��̂���	KASEKI_HONOO
#define DIG_PARTS_MIZU      (20) //�݂��̂���	KASEKI_MIZU
#define DIG_PARTS_REAF      (21) //���[�t�̂���	KASEKI_REAF
#define DIG_PARTS_GOLD      (22) //����̂���	KASEKI_GOLD
#define DIG_PARTS_KAI       (23) //�����̃J�Z�L	KASEKI_KAI
#define DIG_PARTS_KOURA     (24) //������̃J�Z�L	KASEKI_KOURA
#define DIG_PARTS_TSUME     (25) //�c���̃J�Z�L	KASEKI_TSUME
#define DIG_PARTS_NEKKO     (26) //�˂����̃J�Z�L	KASEKI_NEKKO
#define DIG_PARTS_KOHAKU    (27) //�Ђ݂̃R�n�N	KASEKI_KOHAKU
#define DIG_PARTS_BONE      (28) //�ӂƂ��ق�	KASEKI_BONE
#define DIG_PARTS_GENKI_S   (29)// ���C�̂�����
#define DIG_PARTS_GENKI_L   (30)//���񂫂̂����܂�
#define DIG_PARTS_PLA_RED   (31) //������������
#define DIG_PARTS_PLA_BLUE  (32) //������������
#define DIG_PARTS_PLA_YELLOW (33)  //�����낢������
#define DIG_PARTS_PLA_GREEN (34) //�݂ǂ�̂�����
#define DIG_PARTS_HEART     (35) //�n�[�g�̃E���R
#define DIG_PARTS_SHIELD    (36) //���ẴJ�Z�L
#define DIG_PARTS_ZUGAI     (37) //�������̃J�Z�L
#define DIG_PARTS_CRAY      (38)  //�Ђ���̂˂��
#define DIG_PARTS_IRONBALL  (39)  //���낢�Ă����イ
#define DIG_PARTS_COLD      (40) //�߂�������
#define DIG_PARTS_SARA      (41)  //���炳�炢��
#define DIG_PARTS_HEAT      (42)  //��������
#define DIG_PARTS_WET       (43)   //���߂�������
#define DIG_PARTS_PLATE_FIRE   (44)//�Ђ̂��܃v���[�g
#define DIG_PARTS_PLATE_WATER  (45) //�������v���[�g
#define DIG_PARTS_PLATE_THUNDER (46)  //�����Â��v���[�g
#define DIG_PARTS_PLATE_GREEN  (47) //�݂ǂ�̃v���[�g
#define DIG_PARTS_PLATE_ICICLE  (48)  //���̃v���[�g
#define DIG_PARTS_PLATE_KNUCKLE (49)  //���Ԃ��̃v���[�g
#define DIG_PARTS_PLATE_POISON (50)  //�����ǂ��v���[�g
#define DIG_PARTS_PLATE_GROUND (51)  //�������̃v���[�g
#define DIG_PARTS_PLATE_SKY    (52)  //��������v���[�g
#define DIG_PARTS_PLATE_WONDER      (53)   //�ӂ����̃v���[�g
#define DIG_PARTS_PLATE_IRIDESCENCE (54)//���܂ނ��v���[�g
#define DIG_PARTS_PLATE_ROCK        (55)//���񂹂��v���[�g
#define DIG_PARTS_PLATE_GHOST       (56)//���̂̂��v���[�g
#define DIG_PARTS_PLATE_DRAGON      (57)//��イ�̃v���[�g
#define DIG_PARTS_PLATE_DARK        (58)//������ăv���[�g
#define DIG_PARTS_PLATE_IRON        (59)//�����Ăv���[�g
#define DIG_PARTS_TREASURE_MAX     (60)
#define DIG_PARTS_NODIG1    (DIG_PARTS_TREASURE_MAX)     //�@��Ȃ���	kaseki_iwa01	�ʐς��S�}�X	�_�`�̐^�����̐�
#define DIG_PARTS_NODIG2   (61)    //�@��Ȃ���	kaseki_iwa02	�ʐς��S�}�X	�l�p�^�̐^�����̐�
#define DIG_PARTS_NODIG3   (62)    //�@��Ȃ���	kaseki_iwa03	�ʐς��S�}�X	T�^�̐^�����̐�
#define DIG_PARTS_NODIG4  (63)   //�@��Ȃ���	kaseki_iwa04	�ʐς��S�}�X	Z�^�̐^�����̐�
#define DIG_PARTS_NODIG5  (64)   //�@��Ȃ���	kaseki_iwa05	�ʐς��S�}�X	S�^�̐^�����̐�
#define DIG_PARTS_NODIG6  (65)   //�@��Ȃ���	kaseki_iwa06	�ʐς��X�}�X	�l�p�^�̐^�����̐�
#define DIG_PARTS_NODIG7  (66)   //�@��Ȃ���	kaseki_iwa07	�ʐς��W�}�X	�_�`�̐^�����̐�
#define DIG_PARTS_MAX     (67)
#define DIG_PARTS_TYPE_FOSSIL_MIN (DIG_PARTS_KAI)
#define DIG_PARTS_TYPE_FOSSIL_MAX (DIG_PARTS_BONE+1)


// 㩃^�C�v
#define UG_TRAPTYPE_NONE    (0)
#define UG_TRAPTYPE_DIR_UP  (1)
#define UG_TRAPTYPE_DIR_RIGHT   (2)
#define UG_TRAPTYPE_DIR_DOWN     (3)
#define UG_TRAPTYPE_DIR_LEFT   (4)
#define UG_TRAPTYPE_BIGDIR_UP    (5)
#define UG_TRAPTYPE_BIGDIR_RIGHT (6)
#define UG_TRAPTYPE_BIGDIR_DOWN   (7)
#define UG_TRAPTYPE_BIGDIR_LEFT   (8)
#define UG_TRAPTYPE_WARP   (9)
#define UG_TRAPTYPE_TELEPORT   (10)
#define UG_TRAPTYPE_HOLE   (11)
#define UG_TRAPTYPE_BIG_HOLE   (12)
#define UG_TRAPTYPE_REVERSE   (13)
#define UG_TRAPTYPE_GIDDY      (14)          // ��   ��
#define UG_TRAPTYPE_RUNNING   (15)
#define UG_TRAPTYPE_INVISIBLE   (16)
#define UG_TRAPTYPE_SLOW   (17)
#define UG_TRAPTYPE_SMOG      (18)    //    ��ʂɖ�
#define UG_TRAPTYPE_BIG_SMOG       (19)  // ��ʂɖ�
#define UG_TRAPTYPE_ROCK   (20)
#define UG_TRAPTYPE_ROCKFALL   (21)
#define UG_TRAPTYPE_SUDS   (22)
#define UG_TRAPTYPE_BUBBLE   (23)
#define UG_TRAPTYPE_ALART1   (24)
#define UG_TRAPTYPE_ALART2   (25)
#define UG_TRAPTYPE_ALART3   (26)
#define UG_TRAPTYPE_ALART4   (27)
#define UG_TRAPTYPE_LEAF   (28)
#define UG_TRAPTYPE_DIRTY_BLOSSOMS  (29)
#define UG_TRAPTYPE_FIRE   (30)
#define UG_TRAPTYPE_BLAZE   (31)
#define UG_TRAPTYPE_RADAR   (32)
#define UG_TRAPTYPE_DRILL   (33)
#define UG_TRAPTYPE_MAX   (34)
   


#if 0
// �ق��΂̎��
typedef enum{
  STONE_TYPE_NONE,
  STONE_TYPE_DIAMOND,    //  ���񂲂�����
  STONE_TYPE_PEARL,      //  �܂��낾��
  STONE_TYPE_RED,        //  ����������
  STONE_TYPE_BLUE,       //  ����������
  STONE_TYPE_GREEN,      //  �݂ǂ�̂���
  STONE_TYPE_MAX
} StoneType_e;

// ���߂���
typedef enum {
  DIG_PARTS_NONE = STONE_TYPE_NONE,
  DIG_PARTS_KONGOU_S = STONE_TYPE_DIAMOND,   //���񂲂�����	KASEKI_KONGOU_S
  DIG_PARTS_SIRATAMA_S = STONE_TYPE_PEARL, //���炽��	KASEKI_SIRATAMA_S
  DIG_PARTS_RED_S = STONE_TYPE_RED,        //�Ԃ��^�}
  DIG_PARTS_BLUE_S = STONE_TYPE_BLUE,       //���^�}
  DIG_PARTS_GREEN_S = STONE_TYPE_GREEN,      //�΂̃^�}
  DIG_PARTS_KONGOU_L,   //�������񂲂�����	KASEKI_KONGOU_L
  DIG_PARTS_SIRATAMA_L, //�������炽��	KASEKI_SIRATAMA_L
  DIG_PARTS_RED_L,   //�������񂲂�����	KASEKI_KONGOU_L
  DIG_PARTS_BLUE_L,   //�������񂲂�����	KASEKI_KONGOU_L
  DIG_PARTS_GREEN_L, //�������炽��	KASEKI_SIRATAMA_L
  DIG_PARTS_TREASURE_MIN,
  DIG_PARTS_CIRCLE = DIG_PARTS_TREASURE_MIN,        //�܂�܂�	KASEKI_
  DIG_PARTS_KEYSTONE,        //���Ȃ�	KASEKI_
  DIG_PARTS_SUN,        //�����悤�̂���	KASEKI_SUN
  DIG_PARTS_STAR,       //�ق��̂�����	KASEKI_STAR
  DIG_PARTS_MOON,       //���̂���	KASEKI_MOON
  DIG_PARTS_HARD,       //����������	KASEKI_HARD
  DIG_PARTS_KAMINARI,   //���݂Ȃ�̂���	KASEKI_KAMINARI
  DIG_PARTS_KAWARAZU,   //����炸�̂���	KASEKI_KAWARAZU
  DIG_PARTS_HONOO,      //�ق̂��̂���	KASEKI_HONOO
  DIG_PARTS_MIZU,       //�݂��̂���	KASEKI_MIZU
  DIG_PARTS_REAF,       //���[�t�̂���	KASEKI_REAF
  DIG_PARTS_GOLD,       //����̂���	KASEKI_GOLD
  DIG_PARTS_KAI,        //�����̃J�Z�L	KASEKI_KAI
  DIG_PARTS_KOURA,      //������̃J�Z�L	KASEKI_KOURA
  DIG_PARTS_TSUME,      //�c���̃J�Z�L	KASEKI_TSUME
  DIG_PARTS_NEKKO,      //�˂����̃J�Z�L	KASEKI_NEKKO
  DIG_PARTS_KOHAKU,     //�Ђ݂̃R�n�N	KASEKI_KOHAKU
  DIG_PARTS_BONE,       //�ӂƂ��ق�	KASEKI_BONE
  DIG_PARTS_GENKI_S,   // ���C�̂�����
  DIG_PARTS_GENKI_L, //���񂫂̂����܂�
  DIG_PARTS_PLA_RED,//������������
  DIG_PARTS_PLA_BLUE,//������������
  DIG_PARTS_PLA_YELLOW,//�����낢������
  DIG_PARTS_PLA_GREEN,//�݂ǂ�̂�����
  DIG_PARTS_HEART,//�n�[�g�̃E���R
  DIG_PARTS_SHIELD,//���ẴJ�Z�L
  DIG_PARTS_ZUGAI,//�������̃J�Z�L
  DIG_PARTS_CRAY,//�Ђ���̂˂��
  DIG_PARTS_IRONBALL,//���낢�Ă����イ
  DIG_PARTS_COLD,//�߂�������
  DIG_PARTS_SARA,//���炳�炢��
  DIG_PARTS_HEAT,//��������
  DIG_PARTS_WET, //���߂�������
  DIG_PARTS_PLATE_FIRE,//�Ђ̂��܃v���[�g
  DIG_PARTS_PLATE_WATER,//�������v���[�g
  DIG_PARTS_PLATE_THUNDER,//�����Â��v���[�g
  DIG_PARTS_PLATE_GREEN, //�݂ǂ�̃v���[�g
  DIG_PARTS_PLATE_ICICLE ,//���̃v���[�g
  DIG_PARTS_PLATE_KNUCKLE ,//���Ԃ��̃v���[�g
  DIG_PARTS_PLATE_POISON,//�����ǂ��v���[�g
  DIG_PARTS_PLATE_GROUND,//�������̃v���[�g
  DIG_PARTS_PLATE_SKY,//��������v���[�g
  DIG_PARTS_PLATE_WONDER,//�ӂ����̃v���[�g
  DIG_PARTS_PLATE_IRIDESCENCE ,//���܂ނ��v���[�g
  DIG_PARTS_PLATE_ROCK,//���񂹂��v���[�g
  DIG_PARTS_PLATE_GHOST,//���̂̂��v���[�g
  DIG_PARTS_PLATE_DRAGON,//��イ�̃v���[�g
  DIG_PARTS_PLATE_DARK,//������ăv���[�g
  DIG_PARTS_PLATE_IRON,//�����Ăv���[�g
  
  DIG_PARTS_TREASURE_MAX,
  DIG_PARTS_NODIG1 = DIG_PARTS_TREASURE_MAX,     //�@��Ȃ���	kaseki_iwa01	�ʐς��S�}�X	�_�`�̐^�����̐�
  DIG_PARTS_NODIG2,     //�@��Ȃ���	kaseki_iwa02	�ʐς��S�}�X	�l�p�^�̐^�����̐�
  DIG_PARTS_NODIG3,     //�@��Ȃ���	kaseki_iwa03	�ʐς��S�}�X	T�^�̐^�����̐�
  DIG_PARTS_NODIG4,     //�@��Ȃ���	kaseki_iwa04	�ʐς��S�}�X	Z�^�̐^�����̐�
  DIG_PARTS_NODIG5,     //�@��Ȃ���	kaseki_iwa05	�ʐς��S�}�X	S�^�̐^�����̐�
  DIG_PARTS_NODIG6,     //�@��Ȃ���	kaseki_iwa06	�ʐς��X�}�X	�l�p�^�̐^�����̐�
  DIG_PARTS_NODIG7,     //�@��Ȃ���	kaseki_iwa07	�ʐς��W�}�X	�_�`�̐^�����̐�
  DIG_PARTS_MAX,
  DIG_PARTS_TYPE_FOSSIL_MIN = DIG_PARTS_KAI,
  DIG_PARTS_TYPE_FOSSIL_MAX = (DIG_PARTS_BONE+1),
} DigType_e;


// 㩃^�C�v
enum TrapType_e {
  UG_TRAPTYPE_NONE = 0,
  UG_TRAPTYPE_DIR_UP,
  UG_TRAPTYPE_DIR_RIGHT,
  UG_TRAPTYPE_DIR_DOWN,
  UG_TRAPTYPE_DIR_LEFT,
  UG_TRAPTYPE_BIGDIR_UP,
  UG_TRAPTYPE_BIGDIR_RIGHT,
  UG_TRAPTYPE_BIGDIR_DOWN,
  UG_TRAPTYPE_BIGDIR_LEFT,
  UG_TRAPTYPE_WARP,
  UG_TRAPTYPE_TELEPORT,
  UG_TRAPTYPE_HOLE,
  UG_TRAPTYPE_BIG_HOLE,
  UG_TRAPTYPE_REVERSE,
  UG_TRAPTYPE_GIDDY,  // ����
  UG_TRAPTYPE_RUNNING,
  UG_TRAPTYPE_INVISIBLE,
  UG_TRAPTYPE_SLOW,
  UG_TRAPTYPE_SMOG,  // ��ʂɖ�
  UG_TRAPTYPE_BIG_SMOG,  // ��ʂɖ�
  UG_TRAPTYPE_ROCK,
  UG_TRAPTYPE_ROCKFALL,
  UG_TRAPTYPE_SUDS,
  UG_TRAPTYPE_BUBBLE,
  UG_TRAPTYPE_ALART1,
  UG_TRAPTYPE_ALART2,
  UG_TRAPTYPE_ALART3,
  UG_TRAPTYPE_ALART4,
  UG_TRAPTYPE_LEAF,
  UG_TRAPTYPE_DIRTY_BLOSSOMS,
  UG_TRAPTYPE_FIRE,
  UG_TRAPTYPE_BLAZE,
  UG_TRAPTYPE_RADAR,
  UG_TRAPTYPE_DRILL,
  UG_TRAPTYPE_MAX,
};
#endif
/// ��΂̐���MAX�l
#define UG_STONE_CARAT_MAX  (99)

#endif //__UG_ITEMTYPE_H__
