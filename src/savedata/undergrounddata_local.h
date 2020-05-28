//============================================================================================
/**
 * @file	undergrounditem_local.h
 * @brief	�n���f�[�^�w�b�_�[(���̃f�B���N�g���݂̂ł̂ݎQ�Ɖ�)
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================

#ifndef __UNDERGROUNDDATA_LOCAL_H__
#define __UNDERGROUNDDATA_LOCAL_H__

//============================================================================================

#include "savedata/undergrounddata.h"


//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�^��`
 */
//----------------------------------------------------------

typedef struct _SB_GOODS SB_GOODS;
typedef struct _SB_LOCK SB_LOCK;
typedef struct _SECRETBASEDATA SECRETBASEDATA;

struct _SB_GOODS {
  u8 x;       // �O�b�Y�̈ʒu �Z�N�V�������P��
  u8 z;
  u8 type;    // �O�b�Y�̎��  �p�\�R���̃f�[�^�[���f�b�N�X�ɂȂ邩��
};

struct _SB_LOCK {
  u8 x;   // ��̈ʒu �Z�N�V�������P��   
  u8 z;
};

struct _SB_RECORD_DATA {
    u32 pointCount:20;        // �����|�C���g
    u32 talkCount:20;         // �ł������l�̐l��
    u32 sendItemCount:20;     // �������������
    u32 flagConquerCount:20;  // �n�^���Ƃ�����
    u32 stoneCount:20;        // �^�}���@������
    u32 fossilCount:20;       // ���΂��@������
    u32 treasureCount:20;     // ����@������
    u32 trapConquerCount:20;  // �g���b�v����������
    u32 trapTumbleCount:20;   // �g���b�v�ɂ���������
    u32 trapRescueCount:20;   // �l����������
    u32 itemRecvCount:20;     // ��������������
    u32 flagStealCount:20;    // �����Ƃ�ꂽ��
    u32 flagReverseCount:20;  // �������Ԃ�����
    u32 relocateCount:20;     // �����z��������
    u32 flagDeliveryCount:20; // ����[�i������
};

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�^��`
 */
//----------------------------------------------------------
struct _SECRETBASEDATA {
  SB_GOODS goodsPos[SECRETBASE_GOODS_NUM_MAX];
  SB_LOCK rockPos[SECRETBASE_LOCK_NUM_MAX];
  SB_RECORD_DATA recordData;
  u16 xpos;         // �h�A�̈ʒu
  u16 zpos;
  u8 dir;        // �O�ɏo�Ă�h�A�̕���
  u8 bMake;     //  ��������ǂ���
};


//----------------------------------------------------------
/**
 * @brief	�e�f�[�^�̋����͈�
 */
//----------------------------------------------------------
#define _GOODS_TYPE_NUM_MAX   (150)    // �O�b�Y�̍ő�

#define _PCPOS_X (15)
#define _PCPOS_Z (12)

#define _INVALID_POS  (0)

#define _MAX  (999999)   // ���R�[�h�l�̍ő�

#define _MAX_WALK_COUNT (100)

// �O�b�Y�̎󂯓n���ƃy�i���e�B�[�֘A
#define _GOODS_SEND_NONE  (0)
#define _GOODS_SEND_UNDERIN  (1)
#define _GOODS_SEND_NOT  (2)
#define _PENALTY_TIME (24*60)

// �n��A�C�e������ł̘A��
#define _ITEM_KONGOUDAMA_BIT (1)
#define _ITEM_SIRATAMA_BIT (2)

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�^��`
 */
//----------------------------------------------------------

struct _UNDERGROUND_DATA {
  SECRETBASEDATA base;
  u32 randSeed;                     //�O�b�Y�e���̔��蕨���藐���̎�
  s32 sendGoodsMinTimer;   // �O�b�Y�󂯓n���}���̃^�C�}�[
  u8 sendGoodsSaveInfo;   // �n���̃Z�[�u��ԃt���O
  u8 groundStoneGetBit;   //�n��ł��񂲂����܁A�܂��낾�܂���肵������BIT
  //-------------���֘A
  u32 id[UG_FLAG_NUM_MAX];						// �������ID
  STRCODE name[UG_FLAG_NUM_MAX][PERSON_NAME_SIZE + EOM_SIZE];		// ������̖��O
  u8 region_code[UG_FLAG_NUM_MAX];	      			// ���R�[�h
  u8 rom_code[UG_FLAG_NUM_MAX];	      			// ROM�R�[�h
  u8 newFlagNo;
  //--------------���֘A
  u8 groundNatureTrapType[UG_NATURETRAP_PLACE_NUM_MAX];
  u8 groundNatureTrapPos[UG_NATURETRAP_PLACE_NUM_MAX][3];
  u8 groundFossilPos[UG_FOSSIL_PLACE_NUM_MAX][3];
  u8 groundTrapType[UG_TRAP_PLACE_NUM_MAX];
  u8 groundTrapPos[UG_TRAP_PLACE_NUM_MAX][3];
  u8 groundTrapOrder[UG_TRAP_PLACE_NUM_MAX];
  u8 groundStoneType[UG_STONE_PLACE_NUM_MAX];
  u8 groundStoneCaratAdd[UG_STONE_PLACE_NUM_MAX];
  u8 groundStoneCarat[UG_STONE_PLACE_NUM_MAX];
  u8 groundStonePos[UG_STONE_PLACE_NUM_MAX][3];
  u8 groundStoneDummy[UG_STONE_PLACE_NUM_MAX-12];
  //------���Ί֘A
  u32 digBit;  // �v���[�g���@�������ǂ����̊Ǘ�
  u8 pcGoods[UG_ITEM_PC_NUM_MAX];
  u8 bagTrap[UG_ITEM_BAG_NUM_MAX];
  u8 bagGoods[UG_ITEM_BAG_NUM_MAX];
  u8 bagTreasure[UG_ITEM_BAG_NUM_MAX];
  u8 bagStone[UG_ITEM_BAG_NUM_MAX];
  u8 bagStoneCarat[UG_ITEM_BAG_NUM_MAX];
  u8 secretBasePlace[SECRETBASE_GOODS_NUM_MAX]; // �閧��n�ɔz�u�����p�\�R����GOODS�� pcGood index+1������
  u8 walk;   // ���������� 100���Ń��Z�b�g
  u8 bNewDay:4;  // ����BIT��TRUE�Ȃ牻�Δz�u������n���ɓ��������Ɏ��s
  u8 bFossilFirst:4;  // ����BIT��FALSE�Ȃ珉��
};


//============================================================================================

#endif //__UNDERGROUNDDATA_LOCAL_H__

