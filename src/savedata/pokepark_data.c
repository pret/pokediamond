//============================================================================================
/**
 * @file	pokepark_data.c
 * @date	2006.06.01
 * @author	tamada / mitsuhara
 * @brief	AGB��DS�p�Z�[�u�f�[�^�֘A
 */
//============================================================================================

#include "savedata/savedata.h"
#include "savedata/pokepark_data.h"

#include "gflib/assert.h"


//�{���͑��̃f�B���N�g���̒��Ɏ��˂�����ŃC���N���[�h����悤��
//���Ƃ͂��ׂ��łȂ����d���Ȃ��c

#include "../poketool/poke_tool_def.h"
#include "poketool/poke_tool.h"
#include "system/pm_rtc.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N�p�Z�[�u�f�[�^�̒�`
 */
//------------------------------------------------------------------
#define POKEPARK_HISTORY_SIZE		20
struct POKEPARK_DATA {
  POKEMON_PARAM mons[POKEPARK_MONS_MAX];
  u32 AgbTrainerID[POKEPARK_HISTORY_SIZE];	// �ړ������J�Z�b�g�̃g���[�i�[ID
  s64 CheckTime[POKEPARK_HISTORY_SIZE];		// �ړ���������
  s64 RTCOffset;				// ���Ԃ����炵���ݐ�(��r�p)
  u8 MacAddress[6];				// �|�P�������ړ�����DS�{�̂�Mac�A�h���X
};

//============================================================================================
//
//		��ɃZ�[�u�V�X�e������Ă΂��֐�
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^�T�C�Y�̎擾
 * @return	int		�|�P�p�[�N�p�Z�[�u�f�[�^�̃T�C�Y
 */
//------------------------------------------------------------------
int POKEPARKDATA_GetWorkSize(void)
{
	return sizeof(POKEPARK_DATA);
}

//------------------------------------------------------------------
/**
 * @brief	�Z�[�u�f�[�^������
 * @param	ppark		�|�P�p�[�N�p�Z�[�u�f�[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void POKEPARKDATA_Init(POKEPARK_DATA * ppark)
{
	int i;
	MI_CpuClearFast(ppark, sizeof(POKEPARK_DATA));
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		PokeParaInit(&ppark->mons[i]);
		GF_ASSERT(PokeParaGet(&ppark->mons[i], ID_PARA_poke_exist, NULL) == 0);
	}
}
// POKEMON_PARAM�݂̂�����������
void POKEPARKDATA_PreInit(POKEPARK_DATA * ppark)
{
  int i;
  MI_CpuClearFast(ppark->mons, sizeof(POKEMON_PARAM) * POKEPARK_MONS_MAX);
  for (i = 0; i < POKEPARK_MONS_MAX; i++) {
    PokeParaInit(&ppark->mons[i]);
    GF_ASSERT(PokeParaGet(&ppark->mons[i], ID_PARA_poke_exist, NULL) == 0);
  }
}

//============================================================================================
//
//
//				���[�J���֐�
//
//
//============================================================================================

//------------------------------------------------------------------
/**
 * @brief	�Z�[�u����Ǘ��p�C���f�b�N�X��Ԃ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int POKEPARKDATA_GetMasterIndex(POKEPARK_DATA *ppark, u32 agb_id)
{
  int i, index;
  s64 min;
  // �����g���[�i�[ID��T��
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == agb_id)
      return i;
  }
  // �󂢂Ă���ꏊ��Ԃ�
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == 0)
      return i;
  }
  // ��Ԏ��Ԃ��o�߂��Ă���ꏊ��Ԃ�
  min = 0x7FFFFFFF;	// 68years
  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->CheckTime[i] < min){
      min = ppark->CheckTime[i];
      index = i;
    }
  }
  return index;
}


//============================================================================================
//
//
//				����֐�
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^�̐ݒ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_SetData(POKEPARK_DATA *ppark, POKEMON_PASO_PARAM *ppp, int index)
{
  PokeReplace(ppp, &ppark->mons[index]);
}


//------------------------------------------------------------------
/**
 * @brief	�Ǘ��p�f�[�^���Z�b�g
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_SetMasterData(POKEPARK_DATA *ppark, u32 agb_id)
{
  int index = POKEPARKDATA_GetMasterIndex(ppark, agb_id);
  ppark->AgbTrainerID[index] = agb_id;
  ppark->CheckTime[index] = GF_RTC_GetDateTimeBySecond();
  ppark->RTCOffset = OS_GetOwnerRtcOffset();
  OS_GetMacAddress(ppark->MacAddress);
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�p�[�N�f�[�^���R�s�[�Ŏ擾����
 * @param	ppark			�|�P�p�[�N�f�[�^�ւ̃|�C���^
 * @param	index			�擾����|�P�����̃C���f�b�N�X�i���o�[
 * @param	pp				�R�s�[��̃|�P�����p�����[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void POKEPARKDATA_CopyPokemonParam(const POKEPARK_DATA * ppark, int index, POKEMON_PARAM * pp)
{
	GF_ASSERT(index < POKEPARK_MONS_MAX);
	*pp = ppark->mons[index];
}

//------------------------------------------------------------------
//------------------------------------------------------------------
int POKEPARKDATA_CountPokemon(const POKEPARK_DATA * ppark)
{
	int i,n;
	for (n = 0, i = 0; i <POKEPARK_MONS_MAX; i++) {
		if (PokeParaGet((POKEMON_PARAM *)&ppark->mons[i], ID_PARA_poke_exist, NULL)) {
			n++;
		}
	}
	return n;
}


//------------------------------------------------------------------
/**
 * @brief	�����ƈ�v����h�c�����݂��邩�Ԃ�
 * @param	ppark			�|�P�p�[�N�f�[�^�ւ̃|�C���^
 * @param	agb_id			�g���[�i�[�h�c
 * @return	0: �Ȃ������@����ȊO�͑O�񂩂�̕b��
 */
//------------------------------------------------------------------
int POKEPARKDATA_CheckHistoryID(const POKEPARK_DATA *ppark, u32 agb_id)
{
  int i;
  s64 now = GF_RTC_GetDateTimeBySecond();

  for(i = 0; i < POKEPARK_HISTORY_SIZE; i++){
    if(ppark->AgbTrainerID[i] == agb_id){
      return now - ppark->CheckTime[i];
    }
  }
  return 0;
}


//------------------------------------------------------------------
/**
 * @brief	�Z�[�u����Ă���Mac�A�h���X�Ɩ{�̂�Mac�A�h���X���r
 * @param	ppark			�|�P�p�[�N�f�[�^�ւ̃|�C���^
 * @return	TRUE: ��v�@FALSE: �s��v
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_CheckMacAddress(const POKEPARK_DATA *ppark)
{
  int i;
  u8 mac[6];
  
  // MAC�A�h���X�̃`�F�b�N
  OS_GetMacAddress(mac);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�Z�[�u����Ă���MAC�A�h���X: %02X-%02X-%02X-%02X-%02X-%02X\n",
	     ppark->MacAddress[0], ppark->MacAddress[1], ppark->MacAddress[2],
	     ppark->MacAddress[3], ppark->MacAddress[4], ppark->MacAddress[5]);
  OS_TPrintf("�@�@�@�@�@�{�̂�MAC�A�h���X: %02X-%02X-%02X-%02X-%02X-%02X\n",
	     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
#endif  
  for(i = 0; i < 6; i++){
    if(mac[i] != ppark->MacAddress[i])
      return FALSE;
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	���Ԃ����炳�ꂽ����Ԃ�
 * @param	ppark			�|�P�p�[�N�f�[�^�ւ̃|�C���^
 * @return	TRUE: ���炳��ĂȂ��@FALSE: ���炳�ꂽ
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_CheckRTCOffset(const POKEPARK_DATA *ppark)
{
  return ppark->RTCOffset == OS_GetOwnerRtcOffset();
}


//------------------------------------------------------------------
/**
 * @brief	�V�K�Z�[�u���ǂ�����Ԃ�
 * @param	ppark			�|�P�p�[�N�f�[�^�ւ̃|�C���^
 * @return	TRUE: �V�K�Z�[�u�@FALSE: ����ȊO
 */
//------------------------------------------------------------------
BOOL POKEPARKDATA_isNewSave(const POKEPARK_DATA *ppark)
{
  int i;
  u8 code;
  
  for(code = 0, i = 0; i < 6; i++)
    code |= ppark->MacAddress[i];

  if(code == 0)
    // �V�K�Z�[�u�f�[�^���쐬���ꂽ�΂����TRUE��Ԃ�
    return TRUE;
  return FALSE;
}


#ifdef	PM_DEBUG
//------------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^�̐ݒ�
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void POKEPARKDATA_Debug_SetData(POKEPARK_DATA *ppark, int index,
		int mons_no, int level, int pow, u32 rnd, u32 id)
{
  PokeParaSet(&ppark->mons[index], mons_no, level, pow, RND_SET, rnd, ID_SET, id);
}

#endif

