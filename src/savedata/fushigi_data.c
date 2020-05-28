//============================================================================================
/**
 * @file	fushigi_data.c
 * @date	2006.04.28
 * @author	tamada / mitsuhara
 * @brief	�ӂ����ʐM�p�Z�[�u�f�[�^�֘A
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/fushigi_data.h"

#include "gflib/assert.h"

//============================================================================================
//============================================================================================

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);

#define UNIQ_TYPE			0xEDB88320L
#define FUSHIGI_DATA_NO_USED		0x00000000
#define FUSHIGI_DATA_MAX_EVENT		2048

#define FUSHIGI_MENU_FLAG		(FUSHIGI_DATA_MAX_EVENT - 1)

//------------------------------------------------------------------
/**
 * @brief	�ӂ����f�[�^�̒�`
 */
//------------------------------------------------------------------
struct FUSHIGI_DATA{
  u8 recv_flag[FUSHIGI_DATA_MAX_EVENT / 8];		//256 * 8 = 2048 bit
  u32 deli_type[GIFT_DELIVERY_MAX];			// ��₃`�F�b�N�p�R�[�h
  u32 card_type[GIFT_CARD_MAX];
  GIFT_DELIVERY delivery[GIFT_DELIVERY_MAX];		// �z�B���W��
  GIFT_CARD card[GIFT_CARD_MAX];			// �J�[�h���R��
};


//============================================================================================
//
//		��ɃZ�[�u�V�X�e������Ă΂��֐�
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^�T�C�Y�̎擾
 * @return	int		�ӂ����Z�[�u�f�[�^�̃T�C�Y
 */
//------------------------------------------------------------------
int FUSHIGIDATA_GetWorkSize(void)
{
  return sizeof(FUSHIGI_DATA);
}
//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^������
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void FUSHIGIDATA_Init(FUSHIGI_DATA * fd)
{
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�ӂ����f�[�^������\n");
  // ���̏�����saveload_system.c��SVDT_Init�ōs���Ă���̂ŉ������Ȃ�
  MI_CpuClearFast(fd, sizeof(FUSHIGI_DATA));
#endif
}

//============================================================================================
//
//		���p���邽�߂ɌĂ΂��A�N�Z�X�֐�
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�z�B���f�[�^�̎擾
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	index		�z�B���f�[�^�̃C���f�b�N�X�i�O�I���W���j
 * @return	GIFT_DATA	�z�B���f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
GIFT_DELIVERY * FUSHIGIDATA_GetDeliData(FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_DELIVERY_MAX);

  if(fd->deli_type[index] == UNIQ_TYPE){
    // �f�[�^���L���Ȃ̂Ń|�C���^��Ԃ�
    return &fd->delivery[index];
  }
  // �f�[�^�����݂��Ȃ��^��ꂽ�^�������ꂽ�H�̂ŏ�������NULL��Ԃ�
  fd->deli_type[index] = FUSHIGI_DATA_NO_USED;
  return (GIFT_DELIVERY *)NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h�f�[�^�̎擾
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	index		���蕨�f�[�^�̃C���f�b�N�X�i�O�I���W���j
 * @return	GIFT_CARD	�J�[�h�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
GIFT_CARD *FUSHIGIDATA_GetCardData(FUSHIGI_DATA *fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);
  if(fd->card_type[index] != FUSHIGI_DATA_NO_USED)
    return &fd->card[index];
  return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�z�B���f�[�^���Z�[�u�f�[�^�֓o�^
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	p		�f�[�^�ւ̃|�C���^
 * @return	TRUE: �Z�[�u�ł��� : FALSE: �󂫃X���b�g����������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_SetDeliData(FUSHIGI_DATA *fd, const void *p, int link)
{
  int i;

  // �Z�[�u�ł���̈悪������΃Z�[�u���s
  if(FUSHIGIDATA_CheckDeliDataSpace(fd) == FALSE)	return FALSE;

  // ������ȍ~�͗e�ʓI�ɂ̓Z�[�u�ɐ�������͂�
  
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(fd->deli_type[i] == FUSHIGI_DATA_NO_USED){
      MI_CpuCopy8(p, &fd->delivery[i], sizeof(GIFT_DELIVERY));
      fd->deli_type[i] = UNIQ_TYPE;
      fd->delivery[i].link = link;
      return TRUE;
    }
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h�f�[�^���Z�[�u�f�[�^�֓o�^
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	p		�f�[�^�ւ̃|�C���^
 * @return	TRUE: �Z�[�u�ł��� : FALSE: �󂫃X���b�g����������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_SetCardData(FUSHIGI_DATA *fd, const void *p)
{
  int i;
  GIFT_CARD *gc = (GIFT_CARD *)p;

  // �Z�[�u�ł���̈悪������΃Z�[�u���s
  if(FUSHIGIDATA_CheckCardDataSpace(fd) == FALSE)	return FALSE;
  // �z�B�����܂ރf�[�^�̏ꍇ�͔z�B�������`�F�b�N
  if(gc->beacon.delivery_flag == TRUE &&
     FUSHIGIDATA_CheckDeliDataSpace(fd) == FALSE)	return FALSE;

  // ������ȍ~�͗e�ʓI�ɂ̓Z�[�u�ɐ�������͂�
  
  // �J�[�h���Z�[�u����
  for(i = 0; i < GIFT_CARD_MAX; i++){
    if(fd->card_type[i] == FUSHIGI_DATA_NO_USED){
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("�J�[�h���Z�[�u���܂��� [%d]\n", i);
#endif
      MI_CpuCopy8(gc, &fd->card[i], sizeof(GIFT_CARD));
      fd->card_type[i] = UNIQ_TYPE;

      // �z�B�����Z�[�u����
      if(gc->beacon.delivery_flag == TRUE)
	FUSHIGIDATA_SetDeliData(fd, (const void *)&gc->gift_type, i+1);
  
      return TRUE;
    }
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�z�B���f�[�^�𖕏�����
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	index		�z�B���f�[�^�̃C���f�b�N�X
 * @return	TRUE: �Z�[�u�ł��� : FALSE: �󂫃X���b�g����������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_RemoveDeliData(FUSHIGI_DATA *fd, int index)
{
  index--;                                         // k.ohno --�ǉ�
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  fd->deli_type[index] = FUSHIGI_DATA_NO_USED;
  fd->delivery[index].link = 0;
  return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h�f�[�^�𖕏�����
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @return	TRUE: �Z�[�u�ł��� : FALSE: �󂫃X���b�g����������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_RemoveCardData(FUSHIGI_DATA *fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);
  fd->card_type[index] = FUSHIGI_DATA_NO_USED;
  // �����N����Ă���J�[�h���ꏏ�ɖ���
  FUSHIGIDATA_RemoveCardLinkDeli(fd, index + 1);

  return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�z�B���f�[�^���Z�[�u�ł��邩�`�F�b�N
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @return	TRUE: �󂫂����� : FALSE: �󂫃X���b�g������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_CheckDeliDataSpace(FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(fd->deli_type[i] == FUSHIGI_DATA_NO_USED)
      return TRUE;
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�J�[�h�f�[�^���Z�[�u�ł��邩�`�F�b�N
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	size		�f�[�^�̃T�C�Y
 * @return	TRUE: �󂫂����� : FALSE: �󂫃X���b�g������
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_CheckCardDataSpace(FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_CARD_MAX; i++){
    if(fd->card_type[i] == FUSHIGI_DATA_NO_USED)
      return TRUE;
  }
  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	���蕨�f�[�^�̑��݃`�F�b�N
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	index		���蕨�f�[�^�̃C���f�b�N�X�i�O�I���W���j
 * @return	BOOL	TRUE�̎��A���݂���
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsDelivery(const FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  
  if(fd->deli_type[index] == FUSHIGI_DATA_NO_USED)
    return FALSE;
  // �����Ŗ{���̓f�[�^��CRC�`�F�b�N����ꂽ���������Ȃ�
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�J�[�h�f�[�^�����݂��邩�Ԃ�
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @return	BOOL	TRUE�̎��A���݂���
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsCard(const FUSHIGI_DATA * fd, int index)
{
  GF_ASSERT(index < GIFT_CARD_MAX);

  if(fd->card_type[index] == FUSHIGI_DATA_NO_USED)
    return FALSE;
  // �����Ŗ{���̓f�[�^��CRC�`�F�b�N����ꂽ���������Ȃ�
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^���ɃJ�[�h�f�[�^�����݂��邩�Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsExistsCardAll(const FUSHIGI_DATA *fd)
{
  int i;
  for(i = 0; i < GIFT_CARD_MAX; i++)
    if(FUSHIGIDATA_IsExistsCard(fd, i) == TRUE)
      return TRUE;
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�w��̃J�[�h�Ƀ����N����Ă���z�B�������݂��邩
 * @param	��index�͂P�`�R���L��
 * @return	TRUE: �z�B���͑��݂��� FALSE: ���݂��Ȃ�
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_GetCardLinkDeli(const FUSHIGI_DATA *fd, int index)
{
  int i;

#if 0
  for(i = 0; i < GIFT_DELIVERY_MAX; i++)
    OS_TPrintf("Deli[%d] : %d\n", i, fd->delivery[i].link);
#endif
  
  if(index){
    for(i = 0; i < GIFT_DELIVERY_MAX; i++){
      if(fd->delivery[i].link == index)
	return TRUE;
    }
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	�w��J�[�h�Ƀ����N����Ă���z�B�����폜
 * @param	��index�͂P�`�R���L��(������Ή������Ȃ�)
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_RemoveCardLinkDeli(const FUSHIGI_DATA *fd, int index)
{
  int i;
  if(index){
    for(i = 0; i < GIFT_DELIVERY_MAX; i++){
      if(fd->delivery[i].link == index){
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_TPrintf("�J�[�h�ƈꏏ�� %d �Ԃ̂�������̂������܂���\n", i + 1);
#endif
	FUSHIGIDATA_RemoveDeliData((FUSHIGI_DATA *)fd, i + 1);
	return;
      }
    }
  }
}

//------------------------------------------------------------------
/**
 * @brief	�w��̃C�x���g�͂��łɂ���������Ԃ�
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	num		�C�x���g�ԍ�
 * @return	BOOL	TRUE�̎��A���łɂ�����Ă���
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsEventRecvFlag(FUSHIGI_DATA * fd, int num)
{
  GF_ASSERT(num < FUSHIGI_DATA_MAX_EVENT);
  return !!(fd->recv_flag[num / 8] & (1 << (num & 7)));
}


//------------------------------------------------------------------
/**
 * @brief	�w��̃C�x���g���������t���O�𗧂Ă�
 * @param	fd		�ӂ����Z�[�u�f�[�^�ւ̃|�C���^
 * @param	num		�C�x���g�ԍ�
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_SetEventRecvFlag(FUSHIGI_DATA * fd, int num)
{
  GF_ASSERT(num < FUSHIGI_DATA_MAX_EVENT);
  fd->recv_flag[num / 8] |= (1 << (num & 7));
}


//------------------------------------------------------------------
/**
 * @brief	�ӂ����Ȃ�������̂�\���o���邩�H
 * @param	NONE
 * @return	TRUE: �\���@FALSE: �\�����Ȃ�
 */
//------------------------------------------------------------------
BOOL FUSHIGIDATA_IsFushigiMenu(FUSHIGI_DATA *fd)
{
  return FUSHIGIDATA_IsEventRecvFlag(fd, FUSHIGI_MENU_FLAG);
}


//------------------------------------------------------------------
/**
 * @brief	�ӂ����Ȃ�������̂̕\���t���O��ON�ɂ���
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_SetFushigiMenu(FUSHIGI_DATA *fd)
{
  FUSHIGIDATA_SetEventRecvFlag(fd, FUSHIGI_MENU_FLAG);
}


//============================================================================================
//
//		����ɏ�ʂ̊֐��Q�@��ɂ�������Ă�ł�������
//
//============================================================================================

static FUSHIGI_DATA *_fushigi_ptr = NULL;

//------------------------------------------------------------------
/**
 * @brief	����ȉ��̊֐����g�����߂ɕK�v�ȏ�����
 * @param	sv		�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	heap_id		���[�N���擾����q�[�v��ID
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_InitSlot(SAVEDATA * sv, int heap_id)
{
  LOAD_RESULT result;

  if(_fushigi_ptr == NULL){
    _fushigi_ptr = SaveData_GetFushigiData(sv);
  }
}

//------------------------------------------------------------------
/**
 * @brief	����ȉ��̊֐����g���I�������̌�n��
 * @param	sv		�Z�[�u�f�[�^�\���ւ̃|�C���^
 * @param	flag		TRUE: �Z�[�u���� / FALSE: �Z�[�u���Ȃ�
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_FinishSlot(SAVEDATA * sv, int flag)
{
  SAVE_RESULT result;
  if(_fushigi_ptr){
#if 0
    if(flag == TRUE)
      SaveData_Save(sv);
#endif
    _fushigi_ptr = NULL;
  }
}
     
//------------------------------------------------------------------
/**
 * @brief	�X���b�g�Ƀf�[�^�����邩�Ԃ��֐�
 * @param	NONE
 * @return	BOOL	0..�f�[�^�Ȃ�: ��0..�f�[�^����
*/
//------------------------------------------------------------------
int FUSHIGIDATA_CheckSlotData(void)
{
  int i;
  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, i) == TRUE)
      return i + 1;
  }
  return 0;
}

//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃X���b�g�f�[�^�̃^�C�v��Ԃ�
 * @param	index		�X���b�g�̃C���f�b�N�X�ԍ�
 * @return	int		MYSTERYGIFT_TYPE_xxxxx
 *
 * ���C���f�b�N�X�ԍ���FUSHIGIDATA_CheckSlotData�ŕԂ��ꂽ�l
*/
//------------------------------------------------------------------
int FUSHIGIDATA_GetSlotType(int index)
{
#if 0
  int i;
  GIFT_DELIVERY *dv;

  for(i = 0; i < GIFT_DELIVERY_MAX; i++){
    if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, i) == TRUE){
      dv = FUSHIGIDATA_GetDeliData(_fushigi_ptr, i);
      return (int)dv->gift_type;
    }
  }
  return MYSTERYGIFT_TYPE_NONE;
#else
  GIFT_DELIVERY *dv;

  if(index == 0)	return MYSTERYGIFT_TYPE_NONE;    //k.ohno --���O�ɏo����
  index--;
  GF_ASSERT(index < GIFT_DELIVERY_MAX);
  if(FUSHIGIDATA_IsExistsDelivery(_fushigi_ptr, index) == TRUE){
    dv = FUSHIGIDATA_GetDeliData(_fushigi_ptr, index);
    if(dv){                              //k.ohno �f�[�^�����Ă��NULL������
      return (int)dv->gift_type;
    }
  }
  return MYSTERYGIFT_TYPE_NONE;
#endif
}


//------------------------------------------------------------------
/**
 * @brief	�w��ԍ��̃X���b�g�\���̂ւ̃|�C���^��Ԃ�
 * @param	index		�X���b�g�̃C���f�b�N�X�ԍ�
 * @return	GIFT_PRESENT	�\���̂ւ̃|�C���^
 *
 * ���C���f�b�N�X�ԍ���FUSHIGIDATA_CheckSlotData�ŕԂ��ꂽ�l
 */
//------------------------------------------------------------------
GIFT_PRESENT *FUSHIGIDATA_GetSlotPtr(int index)
{
  if(index){
    index--;                          // k.ohno ��
    return &_fushigi_ptr->delivery[index].data;
  }
  return NULL;
}

//------------------------------------------------------------------
/**
 * @brief	�w��̃X���b�g����������
 * @param	index		�X���b�g�̃C���f�b�N�X�ԍ�
 * @return	NONE
 *
 * ���C���f�b�N�X�ԍ���FUSHIGIDATA_CheckSlotData�ŕԂ��ꂽ�l
 */
//------------------------------------------------------------------
void FUSHIGIDATA_RemoveSlot(int index)
{
  FUSHIGIDATA_RemoveDeliData(_fushigi_ptr, index);
}

//------------------------------------------------------------------


#include "system/gamedata.h"         //k.ohno �f�o�b�O�p�ɒǉ�
#include "savedata/regulation.h"      //k.ohno �f�o�b�O�p�ɒǉ�
#include "regulation_local.h"       //k.ohno �f�o�b�O�p�ɒǉ�
#include "system/msgdata.h"         //k.ohno �f�o�b�O�p�ɒǉ�
#include "msgdata/msg.naix"         //k.ohno �f�o�b�O�p�ɒǉ�
#include "msgdata/msg_debug_mitsuhara.h"  //k.ohno �f�o�b�O�p�ɒǉ�
#include "msgdata/msg_debug_ohno.h"  //k.ohno �f�o�b�O�p�ɒǉ�
#include "poketool/pokeparty.h"   //k.ohno �f�o�b�O�p�ɒǉ�

static POKEMON_PARAM* _createPokeParam(u32 heapID );

//------------------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�Ƀ|�P�����f�[�^���Z�b�g����֐�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void FUSHIGIDATA_DebugSetPokemon(void)
{
  REGULATION _dummycup = {
        {EOM_}, // gmm����Ƃ��Ă���
        80,//���x���̍��v�W�O�܂�
        3,//�R�C
        30,//�|�P�����̃��x���R�O�܂�
        -20,//�g�������Q�D�O������
        -20,// �̏d�����Q�O��������
        0,// �i���|�P�����Q���ł��Ȃ�
        0,// ���ʂȃ|�P�����Q���ł��Ȃ�
        0,// �����|�P�����Q���ł��Ȃ�
        0,// ��������������Ȃ�
        0,// �Œ�_���[�W�Z���K�����s
    };
  int no;
  GIFT_DELIVERY gd;
  GIFT_PRESENT_ACCESSORY gpacc;
  GIFT_PRESENT_POKEMON po;
  POKEMON_PARAM* pp;
    
    
  if(_fushigi_ptr == NULL)	return;
  FUSHIGIDATA_Init(_fushigi_ptr);

  gd.gift_type = MYSTERYGIFT_TYPE_MEMBERSCARD;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  gd.gift_type = MYSTERYGIFT_TYPE_LETTER;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  gd.gift_type = MYSTERYGIFT_TYPE_WHISTLE;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

  // �ۂ� �e����
  gd.gift_type = MYSTERYGIFT_TYPE_POKEMON;
  po.parentType = MYSTERYPOKE_PARENTNAME_MY;
  pp = _createPokeParam(HEAPID_FIELD);
#if 0
  MI_CpuCopy8(pp, &po.monsno, PokemonParam_GetWorkSize());
#endif
  MI_CpuCopy8(&po, &gd.data, sizeof(GIFT_PRESENT_POKEMON));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  sys_FreeMemoryEz(pp);

  // �ۂ� �e���̂܂�
  gd.gift_type = MYSTERYGIFT_TYPE_POKEMON;
#if 0
  po.parentType = MYSTERYPOKE_PARENTNAME_THROW;
#endif
  pp = _createPokeParam(HEAPID_FIELD);
#if 0
  MI_CpuCopy8(pp, &po.monsno, PokemonParam_GetWorkSize());
#endif
  MI_CpuCopy8(&po, &gd.data, sizeof(GIFT_PRESENT_POKEMON));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  sys_FreeMemoryEz(pp);

    // ���܂�
  gd.gift_type = MYSTERYGIFT_TYPE_RANGEREGG;
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

#if 0

    // SEAL
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_SEAL;
  gpacc.accNo = 79;//�����V�[��
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  // CLIP
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_CLIP;
  gpacc.accNo = 99;//�Ȃ���ڂ�
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
    // haikei
  gd.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;
  gpacc.accType = MYSTERYGIFT_ACCTYPE_BG;
  gpacc.accNo = 2;//
  MI_CpuCopy8(&gpacc, &gd.data, sizeof(GIFT_PRESENT_ACCESSORY));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

    // �ۂ�����
  gd.gift_type = MYSTERYGIFT_TYPE_POKETCH;
  no = 1; //POKETCH_APPID_STOPWATCH
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
  {  // �_�~�[���M�����[�V�����쐬
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_mitsuhara_dat, HEAPID_FIELD);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_regulation_dummy );
    gd.gift_type = MYSTERYGIFT_TYPE_RULE;
    Regulation_SetCupName(&_dummycup,pStr);
    MI_CpuCopy8(&_dummycup, &gd.data, sizeof(REGULATION));
    FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);
    MSGMAN_Delete(msgman);
    STRBUF_Delete(pStr);
  }

  gd.gift_type = MYSTERYGIFT_TYPE_ITEM;
  no = 80;
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

  gd.gift_type = MYSTERYGIFT_TYPE_GOODS;
  no = 33;
  MI_CpuCopy8(&no, &gd.data, sizeof(int));
  FUSHIGIDATA_SetDeliData(_fushigi_ptr, (const void *)&gd, 0);

#endif

    
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�o�b�O�p�Ƀ|�P���������֐�
 *	@param	heapID		    ���HEAP
 *	@return p_pp		�|�P�����p����
 */
//-----------------------------------------------------------------------------

static STRBUF* _dummyGetGmm(int heapID, int no)
{
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, heapID);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_debugohno_name01+no );
    MSGMAN_Delete(msgman);
    return pStr;
}

// �|�P����
typedef struct {
  u32 monsno;			// �����X�^�[�i���o�[
  u32 hp_rnd;			// HP����
  u32 at_rnd;			// �U������
  u32 df_rnd;			// �h�䗐��
  u32 sp_rnd;			// ��������
  u32 sa_rnd;			// ���U����
  u32 sd_rnd;			// ���h����
  u32 speabino;			// ����\��
  u32	mons_id;		// ID
  u32 style;			// �������悳
  u32 beautiful;		// ��������
  u32 cute;			// ���킢��
  u32 clever;			// ��������
  u32 strong;			// �����܂���
  u32 mons_rnd;			// �ő̗���
  u32 item;			// �A�C�e��
  u32 oya_sex;			// �e����
  u32 fur;			// �щ�
  u32 world_code;		// �e�̍��R�[�h
} _DEBUG_POKEMON;

static POKEMON_PARAM* _createPokeParam(u32 heapID )
{
	STRBUF* str;
    POKEMON_PARAM* p_pp = PokemonParam_AllocWork( heapID );
    int level = 5;
    int trade_no = 0; 
    static _DEBUG_POKEMON debug_pokemon_data = {
    63,				// �����X�^�[�i���o�[(MONSNO_KEESHI)
    15,				// HP����
    15,				// �U������
    15,				// �h�䗐��
    20,				// ��������
    25,				// ���U����
    25,				// ���h����
    28,				// ����\��(TOKUSYU_SINKURO)
    25643,			// ID
    0,				// �������悳
    0,				// ��������
    0,				// ���킢��
    0,				// ��������
    0,				// �����܂���
    117,			// �ő̗���
    155,			// �A�C�e��(�I�����̂�)
    1,				// �e����(��)
    0,				// �щ�
    1,				// �e�̍��R�[�h(LANG_JAPAN)
  };

    
//	PokeParaInit(p_pp);
	// �����X�^�[�i���o�[�@���x���@�ő̗����@ID�ݒ�
	PokeParaSet( p_pp, 
			debug_pokemon_data.monsno,
			level, POW_RND, 
			RND_SET, debug_pokemon_data.mons_rnd,
			ID_SET, debug_pokemon_data.mons_id );

	// �j�b�N�l�[��
	str = _dummyGetGmm(HEAPID_EVENT,trade_no);
	PokeParaPut( p_pp, ID_PARA_nickname_buf, str );
	STRBUF_Delete(str);

	// �e�헐���ݒ�
	PokeParaPut( p_pp, ID_PARA_hp_rnd, &debug_pokemon_data.hp_rnd );
	PokeParaPut( p_pp, ID_PARA_pow_rnd, &debug_pokemon_data.at_rnd );
	PokeParaPut( p_pp, ID_PARA_def_rnd, &debug_pokemon_data.df_rnd );
	PokeParaPut( p_pp, ID_PARA_agi_rnd, &debug_pokemon_data.sp_rnd );
	PokeParaPut( p_pp, ID_PARA_spepow_rnd, &debug_pokemon_data.sa_rnd );
	PokeParaPut( p_pp, ID_PARA_spedef_rnd, &debug_pokemon_data.sd_rnd );

	// ����
	PokeParaPut( p_pp, ID_PARA_speabino, &debug_pokemon_data.speabino );

	// �������悳�Ȃ�
	PokeParaPut( p_pp, ID_PARA_style, &debug_pokemon_data.style );
	PokeParaPut( p_pp, ID_PARA_beautiful, &debug_pokemon_data.beautiful );
	PokeParaPut( p_pp, ID_PARA_cute, &debug_pokemon_data.cute );
	PokeParaPut( p_pp, ID_PARA_clever, &debug_pokemon_data.clever );
	PokeParaPut( p_pp, ID_PARA_strong, &debug_pokemon_data.strong );
	
	// �A�C�e��
	PokeParaPut( p_pp, ID_PARA_item, &debug_pokemon_data.item );

	// �e�̖��O
 	str = _dummyGetGmm(HEAPID_EVENT,trade_no);
	PokeParaPut( p_pp, ID_PARA_oyaname_buf, str );
	STRBUF_Delete(str);

	// �e�̐���	
	PokeParaPut( p_pp, ID_PARA_oyasex, &debug_pokemon_data.oya_sex );

	// ���R�[�h
	PokeParaPut( p_pp, ID_PARA_country_code, &debug_pokemon_data.world_code );
    return p_pp;
}



/*  */
