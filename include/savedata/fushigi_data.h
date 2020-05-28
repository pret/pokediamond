//============================================================================================
/**
 * @file	fushigi_data.h
 * @date	2006.04.28
 * @author	tamada / mitsuhara
 * @brief	�ӂ����ʐM�p�Z�[�u�f�[�^�p�w�b�_
 */
//============================================================================================

#ifndef	__FUSHIGI_DATA_H__
#define	__FUSHIGI_DATA_H__

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/regulation.h"
#include "poketool/poke_tool.h"

//============================================================================================
//
//			��`
//
//============================================================================================
//------------------------------------------------------------------
///		���蕨�f�[�^�̑傫��
//------------------------------------------------------------------
#define	GIFT_DATA_SIZE	256		// �z�B���P�̃T�C�Y

//------------------------------------------------------------------
///		���蕨�f�[�^�̌�
//------------------------------------------------------------------
#define GIFT_DELIVERY_MAX	8	// �z�B���W��
#define GIFT_CARD_MAX		3	// �J�[�h�f�[�^�R��
#define	GIFT_DATA_MAX		8	//�J�[�h�Ȃ�5���{�J�[�h����3����8����

//------------------------------------------------------------------
///		�J�[�h�֌W�̃T�C�Y��`
//------------------------------------------------------------------
#define GIFT_DATA_CARD_TITLE_MAX	36
#define GIFT_DATA_CARD_TEXT_MAX		250
#define GIFT_DATA_SCRIPT_MAX		(256+1024)


//------------------------------------------------------------------
///		���蕨�f�[�^�\����
//------------------------------------------------------------------
#define MYSTERYGIFT_TYPE_NONE		0	// ��������
#define MYSTERYGIFT_TYPE_POKEMON	1	// �|�P����
#define MYSTERYGIFT_TYPE_POKEEGG	2	// �^�}�S
#define MYSTERYGIFT_TYPE_ITEM		3	// �ǂ���
#define MYSTERYGIFT_TYPE_RULE		4	// ���[��
#define MYSTERYGIFT_TYPE_GOODS		5	// �O�b�Y
#define MYSTERYGIFT_TYPE_ACCESSORY	6	// �A�N�Z�T��
#define MYSTERYGIFT_TYPE_RANGEREGG	7	// �}�i�t�B�[�̃^�}�S
#define MYSTERYGIFT_TYPE_MEMBERSCARD	8	// �����o�[�Y�J�[�h
#define MYSTERYGIFT_TYPE_LETTER		9	// �I�[�L�h�̂Ă���
#define MYSTERYGIFT_TYPE_WHISTLE	10	// �Ă񂩂��̂ӂ�
#define MYSTERYGIFT_TYPE_POKETCH	11	// �|�P�b�`
#define MYSTERYGIFT_TYPE_CLEAR		255	// �ӂ����̈�̋����N���A

#define MYSTERYGIFT_ACCTYPE_SEAL   1  // �A�N�Z�T���[�̃V�[��
#define MYSTERYGIFT_ACCTYPE_CLIP   2  // �A�N�Z�T���[�̃N���b�v
#define MYSTERYGIFT_ACCTYPE_BG   3  // �A�N�Z�T���[�̔w�i

#define MYSTERYPOKE_PARENTNAME_THROW  0  // �e�̖��O�����̂܂�
#define MYSTERYPOKE_PARENTNAME_MY   1  // �e���������̖��O�ɕς���


//------------------------------------------------------------------
///		�m�肵�Ă���C�x���g�ԍ�
//------------------------------------------------------------------
#define MYSTERYGIFT_MANAFIEGG		1	// �}�i�t�B�̂��܂�



// �T�C�Y�Œ�p�\����
typedef struct {
  u8 data[256];
} GIFT_PRESENT_ALL;

// �|�P����
typedef struct {
  u32 parentType;
  u8 data[236];		// sizeof(POKEMON_PARAM)	#####
  u8 ribbon[10];	// ribbon data
  u8 dummy[6];
} GIFT_PRESENT_POKEMON;

// �^�}�S
typedef struct {
  u32 parentType;
  u8 data[236];		// sizeof(POKEMON_PARAM)	#####
  u8 ribbon[10];	// ribbon data
  u8 dummy[6];
} GIFT_PRESENT_POKEEGG;

// �ǂ���
typedef struct {
  int itemNo;
} GIFT_PRESENT_ITEM;

// �O�b�Y
typedef struct {
  int goodsNo;
} GIFT_PRESENT_GOODS;

// ���[��(���M�����[�V����)
typedef struct {
  REGULATION regulation;
} GIFT_PRESENT_RULE;

// �A�N�Z�T��
typedef struct {
  int accType;
  int accNo;
} GIFT_PRESENT_ACCESSORY;

// �}�i�t�B�[�̃^�}�S
typedef struct {
  int dummy;
} GIFT_PRESENT_RANGEREGG;

// �����o�[�Y�J�[�h
typedef struct {
  int itemNo;
} GIFT_PRESENT_MEMBERSCARD;

// �I�[�L�h�̂Ă���
typedef struct {
  int itemNo;
} GIFT_PRESENT_LETTER;

// �Ă񂩂��̂ӂ�
typedef struct {
  int itemNo;
} GIFT_PRESENT_WHISTLE;

// �|�P�b�`
typedef struct {
  int id;
} GIFT_PRESENT_POKETCH;

// �ӂ����Ȃ�������̋����N���A
typedef struct {
  int dummy;
} GIFT_PRESENT_REMOVE;

typedef union {
  GIFT_PRESENT_ALL 		all;
  GIFT_PRESENT_POKEMON		pokemon;
  GIFT_PRESENT_POKEEGG		egg;
  GIFT_PRESENT_ITEM		item;
  GIFT_PRESENT_GOODS		goods;
  GIFT_PRESENT_RULE		rule;
  GIFT_PRESENT_ACCESSORY	accessory;
  GIFT_PRESENT_RANGEREGG	rangeregg;
  GIFT_PRESENT_MEMBERSCARD	memberscard;
  GIFT_PRESENT_LETTER		letter;
  GIFT_PRESENT_WHISTLE		whistle;
  GIFT_PRESENT_POKETCH		poketch;
  GIFT_PRESENT_REMOVE		remove;
} GIFT_PRESENT;



#define MYSTERYGIFT_DELIVERY	0
#define MYSTERYGIFT_CARD	1

#define MYSTERYGIFT_POKEICON	3

// �ӂ����Ȃ�������́@�r�[�R���f�[�^
typedef struct {
  STRCODE event_name[GIFT_DATA_CARD_TITLE_MAX];	// �C�x���g�^�C�g��
  u32 version;					// �Ώۃo�[�W����(�O�̏ꍇ�͐��������Ŕz�z)
  u16 event_id;					// �C�x���g�h�c(�ő�2048���܂�)
  u8 only_one_flag: 1;				// �P�x������M�t���O(0..���x�ł���M�\ 1..�P��̂�)
  u8 access_point: 1;				// �A�N�Z�X�|�C���g(���������ĕK�v�Ȃ��Ȃ����H)
  u8 have_card: 1;				// �J�[�h�����܂�ł��邩(0..�܂�ł��Ȃ�  1..�܂�ł�)
  u8 delivery_flag: 1;				// �z�B������󂯎����̂��܂�ł��邩
  u8 re_deal_flag: 1;				// ���z�z���鎖���\���H(0..�o���Ȃ� 1..�o����)
  u8 groundchild_flag: 1;			// ���z�z�t���O(0..�Ⴄ 1..���z�z)
  u8 dummy: 2;
} GIFT_BEACON;

// �z�B��(�ő�W��)
typedef struct {
  u16 gift_type;
  u16 link : 2;					// �J�[�h�ւ̃����N(0: �����N�����@1 .. 3:�����N)
  u16 dummy : 14;
  GIFT_PRESENT data;
} GIFT_DELIVERY;


// �J�[�h���(�ő�R��)
typedef struct {
  u16 gift_type;
  u16 dummy;					// �z�B���ւ̃����N
  GIFT_PRESENT data;

  GIFT_BEACON beacon;				// �r�[�R�����Ɠ����̏�������

  STRCODE event_text[GIFT_DATA_CARD_TEXT_MAX];	// �����e�L�X�g
  u8 re_deal_count;				// �Ĕz�z�̉�(0�`254�A255�͖�����)
  u16 pokemon_icon[MYSTERYGIFT_POKEICON];	// �|�P�����A�C�R���R��

  // ���z�z����̂͂����܂�
  // �����̉��̓t���b�V���ɃZ�[�u���鎞�̂ݕK�v�ȃf�[�^
  
  u8 re_dealed_count;				// �z�z������
  s32 recv_date;				// ��M��������
  
} GIFT_CARD;


typedef union {
  GIFT_DELIVERY deli;
  GIFT_CARD card;
} GIFT_DATA;


// �ʐM����ۂ̃p�b�P�[�W��`
// beacon.have_card == TRUE �Ȃ�� data = card;
//                     FALSE �Ȃ�� data = deli;
typedef struct {
  GIFT_BEACON beacon;
  GIFT_DATA data;
} GIFT_COMM_PACK;


//------------------------------------------------------------------
/**
 * @brief	�ӂ����Z�[�u�f�[�^�ւ̕s���S�^��`
 */
//------------------------------------------------------------------
typedef struct FUSHIGI_DATA FUSHIGI_DATA;


//============================================================================================
//
//			�O���Q��
//
//============================================================================================
//------------------------------------------------------------------
//�f�[�^�T�C�Y�擾
//------------------------------------------------------------------
extern int FUSHIGIDATA_GetWorkSize(void);

//------------------------------------------------------------------
//����������
//------------------------------------------------------------------
extern void FUSHIGIDATA_Init(FUSHIGI_DATA * fd);

//------------------------------------------------------------------
/**
 * @brief	�ӂ����f�[�^�ւ̃|�C���^�擾
 */
//------------------------------------------------------------------
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);

//------------------------------------------------------------------
/// �z�B���f�[�^�̎擾
//------------------------------------------------------------------
extern GIFT_DELIVERY * FUSHIGIDATA_GetDeliData(FUSHIGI_DATA * fd, int index);
//------------------------------------------------------------------
/// �z�B���f�[�^���Z�[�u�f�[�^�o�^
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_SetDeliData(FUSHIGI_DATA *fd, const void *p, int link);
//------------------------------------------------------------------
/// �z�B���f�[�^�𖕏�����
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_RemoveDeliData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// �z�B���f�[�^���Z�[�u�ł��邩�`�F�b�N
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_CheckDeliDataSpace(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
/// �z�B���f�[�^�̑��݃`�F�b�N
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsDelivery(const FUSHIGI_DATA * fd, int index);


//------------------------------------------------------------------
/// �J�[�h�f�[�^�̎擾
//------------------------------------------------------------------
extern GIFT_CARD *FUSHIGIDATA_GetCardData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// �J�[�h�f�[�^���Z�[�u�f�[�^�o�^
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_SetCardData(FUSHIGI_DATA *fd, const void *p);
//------------------------------------------------------------------
/// �J�[�h�f�[�^�𖕏�����
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_RemoveCardData(FUSHIGI_DATA *fd, int index);
//------------------------------------------------------------------
/// �J�[�h�f�[�^���Z�[�u�ł��邩�`�F�b�N
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_CheckCardDataSpace(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
/// �J�[�h�f�[�^�����݂��邩�Ԃ�
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsCard(const FUSHIGI_DATA * fd, int index);
//------------------------------------------------------------------
/// �Z�[�u�f�[�^���ɃJ�[�h�f�[�^�����݂��邩�Ԃ�
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsExistsCardAll(const FUSHIGI_DATA *fd);

//------------------------------------------------------------------
///	�w��̃J�[�h�Ƀ����N����Ă���z�B�������݂��邩
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_GetCardLinkDeli(const FUSHIGI_DATA *fd, int index);

//------------------------------------------------------------------
///	�w��J�[�h�Ƀ����N����Ă���z�B�����폜
//------------------------------------------------------------------
extern void FUSHIGIDATA_RemoveCardLinkDeli(const FUSHIGI_DATA *fd, int index);

//------------------------------------------------------------------
/// �w��̃C�x���g�͂��łɂ���������Ԃ�
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsEventRecvFlag(FUSHIGI_DATA * fd, int num);
//------------------------------------------------------------------
/// �w��̃C�x���g���������t���O�𗧂Ă�
//------------------------------------------------------------------
extern void FUSHIGIDATA_SetEventRecvFlag(FUSHIGI_DATA * fd, int num);
//------------------------------------------------------------------
///	�ӂ����Ȃ�������̂�\���o���邩�H
//------------------------------------------------------------------
extern BOOL FUSHIGIDATA_IsFushigiMenu(FUSHIGI_DATA *fd);
//------------------------------------------------------------------
///	�ӂ����Ȃ�������̂̕\���t���O��ON�ɂ���
//------------------------------------------------------------------
extern void FUSHIGIDATA_SetFushigiMenu(FUSHIGI_DATA *fd);


//------------------------------------------------------------------
/// ����ȉ��̊֐����g�����߂ɕK�v�ȏ�����
//------------------------------------------------------------------
extern void FUSHIGIDATA_InitSlot(SAVEDATA * sv, int heap_id);
//------------------------------------------------------------------
/// ����ȉ��̊֐����g���I�������̌�n��
//------------------------------------------------------------------
extern void FUSHIGIDATA_FinishSlot(SAVEDATA * sv, int flag);
//------------------------------------------------------------------
/// �X���b�g�Ƀf�[�^�����邩�Ԃ��֐�
//------------------------------------------------------------------
extern int FUSHIGIDATA_CheckSlotData(void);
//------------------------------------------------------------------
/// ��ԎႢ�f�[�^�͉��Ȃ̂���Ԃ�
//------------------------------------------------------------------
extern int FUSHIGIDATA_GetSlotType(int index);
//------------------------------------------------------------------
/// ��ԎႢ�f�[�^�̍\���̂ւ̃|�C���^��Ԃ�
//------------------------------------------------------------------
extern GIFT_PRESENT *FUSHIGIDATA_GetSlotPtr(int index);
//------------------------------------------------------------------
/// �w��̃X���b�g����������
//------------------------------------------------------------------
extern void FUSHIGIDATA_RemoveSlot(int index);


//------------------------------------------------------------------
/// �f�o�b�O�p�Ƀ|�P�����f�[�^���Z�b�g����֐�
//------------------------------------------------------------------
extern void FUSHIGIDATA_DebugSetPokemon(void);

#endif	/* __FUSHIGI_DATA_H__ */
