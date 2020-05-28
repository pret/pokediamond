//============================================================================================
/**
 * @file	undergrounddata.c
 * @brief	�n���A�C�e���f�[�^�A�N�Z�X�p�\�[�X
 * @author	k.ohno
 * @date	2006.2.21
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/undergrounddata.h"
#include "undergrounddata_local.h"

#include "field/ug_itemtype.h"
#include "../fielddata/base_goods/goods_id_def.h"
#include "itemtool/itemsym.h"
#include "system/pm_rtc.h"

//============================================================================================
//============================================================================================



u16 _convertList[] = {
    ITEM_MANMARUISI,         //�܂�܂�	KASEKI_SUN
    ITEM_KANAMEISI,         //���Ȃ�	KASEKI_SUN
    ITEM_TAIYOUNOISI,        //�����悤�̂���	KASEKI_SUN
    ITEM_HOSINOKAKERA,       //�ق��̂�����	KASEKI_STAR
    ITEM_TUKINOISI,          //���̂���	KASEKI_MOON
    ITEM_KATAIISI,           //����������	KASEKI_HARD
    ITEM_KAMINARINOISI,      //���݂Ȃ�̂���	KASEKI_KAMINARI
    ITEM_KAWARAZUNOISI,      //����炸�̂���	KASEKI_KAWARAZU
    ITEM_HONOONOISI,         //�ق̂��̂���	KASEKI_HONOO
    ITEM_MIZUNOISI,          //�݂��̂���	KASEKI_MIZU
    ITEM_RIIHUNOISI,         //���[�t�̂���	KASEKI_REAF
    ITEM_KINNOTAMA,          //����̂���	KASEKI_GOLD
    ITEM_KAINOKASEKI,        //�����̃J�Z�L	KASEKI_KAI
    ITEM_KOURANOKASEKI,      //������̃J�Z�L	KASEKI_KOURA
    ITEM_TUMENOKASEKI,       //�c���̃J�Z�L	KASEKI_TSUME
    ITEM_NEKKONOKASEKI,      //�˂����̃J�Z�L	KASEKI_NEKKO
    ITEM_HIMITUNOKOHAKU,     //�Ђ݂̃R�n�N	KASEKI_KOHAKU
    ITEM_KITYOUNAHONE,          //�����傤�ȃz�l	KASEKI_BONE
    ITEM_GENKINOKAKERA,   // ���񂫂̂�����
    ITEM_GENKINOKATAMARI,  // ���񂫂̂����܂�
    ITEM_AKAIKAKERA,				// ������������
    ITEM_AOIKAKERA,				// ������������
    ITEM_KIIROIKAKERA,			// �����낢������
    ITEM_MIDORINOKAKERA,				// �݂ǂ�̂�����
    ITEM_HAATONOUROKO,			// �n�[�g�̃E���R
    ITEM_TATENOKASEKI,				// ���ẴJ�Z�L
    ITEM_ZUGAINOKASEKI,				// �������̃J�Z�L
    ITEM_HIKARINONENDO,// �Ђ���̂˂��
    ITEM_KUROITEKKYUU,				// ���낢�Ă����イ
    ITEM_TUMETAIIWA,				// �߂�������
    ITEM_SARASARAIWA,			// ���炳�炢��
    ITEM_ATUIIWA,			// ��������
    ITEM_SIMETTAIWA,				// ���߂�������
    ITEM_HINOTAMAPUREETO,			// �Ђ̂��܃v���[�g
    ITEM_SIZUKUPUREETO,			// �������v���[�g
    ITEM_IKAZUTIPUREETO,				// ���������v���[�g
    ITEM_MIDORINOPUREETO,				// �݂ǂ�̃v���[�g
    ITEM_TURARANOPUREETO,				// ���̃v���[�g
    ITEM_KOBUSINOPUREETO,				// ���Ԃ��̃v���[�g
    ITEM_MOUDOKUPUREETO,				// �����ǂ��v���[�g
    ITEM_DAITINOPUREETO,				// �������̃v���[�g
    ITEM_AOZORAPUREETO,				// ��������v���[�g
    ITEM_HUSIGINOPUREETO,				// �ӂ����̃v���[�g
    ITEM_TAMAMUSIPUREETO,				// ���܂ނ��v���[�g
    ITEM_GANSEKIPUREETO,				// ���񂹂��v���[�g
    ITEM_MONONOKEPUREETO,				// ���̂̂��v���[�g
    ITEM_RYUUNOPUREETO,				// ��イ�̃v���[�g
    ITEM_KOWAMOTEPUREETO,				// ������ăv���[�g
    ITEM_KOUTETUPUREETO,				// �����Ăv���[�g
};

static void _addEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int add);


//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���[�N�T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int UnderGroundData_GetWorkSize(void)
{
    return sizeof(UNDERGROUNDDATA);
}

//----------------------------------------------------------
/**
 * @brief	�n���A�C�e�����[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	UNDERGROUNDDATA*	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
UNDERGROUNDDATA* UnderGroundData_AllocWork(u32 heapID)
{
	UNDERGROUNDDATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(UNDERGROUNDDATA));
	UnderGroundData_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	UNDERGROUNDDATA�̃R�s�[
 * @param	from	�R�s�[��UNDERGROUNDDATA�ւ̃|�C���^
 * @param	to		�R�s�[��UNDERGROUNDDATA�ւ̃|�C���^
 */
//----------------------------------------------------------
void UnderGroundData_Copy(const UNDERGROUNDDATA *pFrom, UNDERGROUNDDATA* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(UNDERGROUNDDATA));
}

//----------------------------------------------------------
/**
 * @brief	���[�N�T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int SecretBaseData_GetWorkSize(void)
{
	return sizeof(SECRETBASEDATA);
}

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X���[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	SECRETBASEDATA*	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
SECRETBASEDATA* SecretBaseData_AllocWork(u32 heapID)
{
	SECRETBASEDATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(SECRETBASEDATA));
	SecretBaseData_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	���R�[�h�����̃��[�N�T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int SecretBaseRecord_GetWorkSize(void)
{
	return sizeof(SB_RECORD_DATA);
}

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X���R�[�h���[�N�̊m��
 * @param	heapID		�������m�ۂ������Ȃ��q�[�v�w��
 * @return	SB_RECORD_DATA*	�擾�������[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
SB_RECORD_DATA* SecretBaseRecord_AllocWork(u32 heapID)
{
	SB_RECORD_DATA* reg;
	reg = sys_AllocMemory(heapID, sizeof(SB_RECORD_DATA));
	MI_CpuFill8(reg, 0, sizeof(SB_RECORD_DATA));
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	SECRETBASEDATA�̃R�s�[
 * @param	from	�R�s�[��SECRETBASEDATA�ւ̃|�C���^
 * @param	to		�R�s�[��SECRETBASEDATA�ւ̃|�C���^
 */
//----------------------------------------------------------
void SecretBaseData_Copy(const SECRETBASEDATA *pFrom, SECRETBASEDATA* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(SECRETBASEDATA));
}


//============================================================================================
//
//	UNDERGROUNDDATA����̂��߂̊֐�
//
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�̏�����
 * @param	pSBData		UNDERGROUNDDATA���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void UnderGroundData_Init(UNDERGROUNDDATA* pSBData)
{
    u32 randSeed = 0;
    RTCDate date;
    RTCTime time;

    GF_RTC_GetDateTime(&date, &time);
    randSeed = (((((((u32)date.year * 32ULL + date.month) * 32ULL)
                   + date.day) * 32ULL + time.hour) * 32ULL + time.minute)
                * 32ULL + (time.second + sys.vsync_counter));
    MI_CpuFill8(pSBData, 0, sizeof(UNDERGROUNDDATA));
    pSBData->randSeed = randSeed;
#ifdef DEBUG_ONLY_FOR_ohno

    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_DIAMOND, 10);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_PEARL, 10);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_RED, 20);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_BLUE, 20);
    UnderGroundAddStoneBagItem(pSBData, STONE_TYPE_GREEN, 20);

    UnderGroundAddGoodsBagItem(pSBData, GOODS_BOX01);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_TABLE02_2);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_CHAIR_L01);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_SHELF02);
    UnderGroundAddGoodsBagItem(pSBData, GOODS_UG_POKE_22);
#endif
    pSBData->bNewDay = TRUE;
}


static int _getBagTreasureItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    for(i = 0;i < SECRETBASE_GOODS_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] != GOODS_INVALID ){
            return i;
        }
    }
    return -1;
}

static int _getBagGoodsItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] != GOODS_INVALID ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

static int _getFreeBagGoodsItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] == GOODS_INVALID ){
            return i;
        }
    }
    return -1;
}

static int _getFreeBagStoneItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] == STONE_TYPE_NONE ){ // ��
            return i;
        }
    }
    return -1;
}

static int _getBagStoneItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] != STONE_TYPE_NONE ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

static int _getFreeBagTreasureItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] == STONE_TYPE_NONE ){
            return i;
        }
    }
    return -1;
}

static int _getFreeBagTrapItemIndex(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] == UG_TRAPTYPE_NONE ){ // ��
            return i;
        }
    }
    return -1;
}

static int _getBagTrapItemIndexSearch(UNDERGROUNDDATA* pUGData, int index)
{
    int i,cnt=0;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] != UG_TRAPTYPE_NONE ){
            if(index == cnt){
                return i;
            }
            cnt++;
        }
    }
    return -1;
}

//----------------------------------------------------------
/**
 * @brief	�n���f�[�^�̓����Ɋ֌W��������
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @param	diff_days    �o�ߓ���
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataDayUpdate(SAVEDATA* pSave, int diff_days)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);
    MATHRandContext16 rand;
    u8 upper[]={0,2,2,4,4,5};
    u8 add[]={0,1,1,3,3,5};
    int day,dayMax,carat,type,i;
    
    if(diff_days <= 0){  // ���̓��t�X�V�ɂǂ����邩�͕s��
        return;
    }
    dayMax = diff_days;   // �ʂ̐����͂X�X�܂ł����Ȃ��̂ł���ȏ�̓J�b�g
    if(diff_days > UG_STONE_CARAT_MAX){
        dayMax = UG_STONE_CARAT_MAX;
    }
    MATH_InitRand16(&rand, pUGData->randSeed);
    for(day = 0; day < dayMax; day++){
        for(i = 0; i < UG_STONE_PLACE_NUM_MAX; i++){
            if(pUGData->groundStoneType[i] != STONE_TYPE_NONE){
                type = pUGData->groundStoneType[i];
                carat = MATH_Rand16(&rand, upper[type]) + add[type];
                if((pUGData->groundStoneCaratAdd[i] + carat) < UG_STONE_CARAT_MAX){
                    pUGData->groundStoneCaratAdd[i] += carat;
                }
                else{
                    pUGData->groundStoneCaratAdd[i] = UG_STONE_CARAT_MAX;
                    break;
                }
            }
        }
    }
    pUGData->randSeed = gf_fix_rand(pUGData->randSeed + diff_days);
    pUGData->bNewDay = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	�n���f�[�^�̎��ԂɊ֌W��������
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @param	diff_minute    �o�ߕ�
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataMinUpdate(SAVEDATA* pSave, s32 diff_minute, BOOL bPenaltyMode)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if( (diff_minute < 0)  || (bPenaltyMode) ){  // ���ɂ͑Ή����Ȃ��y�i���e�B�[���ɂ̓J�E���g���Ȃ�
        return;
    }
    if( pUGData->sendGoodsMinTimer < diff_minute ) {
        pUGData->sendGoodsMinTimer = 0;
    }
    else{
        pUGData->sendGoodsMinTimer -= diff_minute;
    }
}

//----------------------------------------------------------
/**
 * @brief	�n���f�[�^�̃��[�h����ɌĂԏ���
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataLoadUpdate(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if((pUGData->sendGoodsMinTimer == 0) &&
       (pUGData->sendGoodsSaveInfo == _GOODS_SEND_NOT)){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NONE;
    }
    if((pUGData->sendGoodsMinTimer == 0) &&
       (pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN)){
        pUGData->sendGoodsMinTimer = _PENALTY_TIME;
    }
    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NOT;
    }
}

//----------------------------------------------------------
/**
 * @brief	�n���ɍs��SAVE�O�ɌĂԏ���
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataBeforeUGSave(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_NONE){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_UNDERIN;
    }
}

//----------------------------------------------------------
/**
 * @brief	�n�����甲���o���ꍇ�̏���
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundDataAfterUG(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_UNDERIN){
        pUGData->sendGoodsSaveInfo = _GOODS_SEND_NONE;
    }
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Y�����������Ԃ��ǂ���
 * @param   pSave        �Z�[�u�f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------

BOOL UnderGroundDataIsGoodsSend(SAVEDATA* pSave)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pSave);

    if(pUGData->sendGoodsSaveInfo == _GOODS_SEND_NOT){
        return FALSE;
    }
    return TRUE;
}


//----------------------------------------------------------
/**
 * @brief	�n��Ńf�B�A���K���p���L�A��|��������ON�ɂ���
 * @param   pUGData        �n���f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------

void UnderGroundSetDiamondPearlEvent(UNDERGROUNDDATA* pUGData)
{
    pUGData->groundStoneGetBit = TRUE;
}

BOOL UnderGroundIsDiamondPearlEvent(UNDERGROUNDDATA* pUGData)
{
    return pUGData->groundStoneGetBit;
}

//----------------------------------------------------------
/**
 * @brief	����ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	pMyStatus    �Ƃ����l��MYSTATUS
 * @return	none   �K����������
 */
//----------------------------------------------------------

void UnderGroundAddFlag(UNDERGROUNDDATA* pUGData, const MYSTATUS* pMyStatus)
{
	int i = pUGData->newFlagNo;

    GF_ASSERT_RETURN(i < UG_FLAG_NUM_MAX,);
    MI_CpuCopy8(MyStatus_GetMyName(pMyStatus), pUGData->name[i], (sizeof(STRCODE) * (PERSON_NAME_SIZE+EOM_SIZE)));
    pUGData->id[i] = MyStatus_GetID(pMyStatus);
    pUGData->region_code[i] = MyStatus_GetRegionCode(pMyStatus);
    pUGData->rom_code[i] = MyStatus_GetRomCode(pMyStatus);
    pUGData->newFlagNo++;
    if(pUGData->newFlagNo >= UG_FLAG_NUM_MAX){
        pUGData->newFlagNo = 0;
    }
}

//----------------------------------------------------------
/**
 * @brief	����ǂݍ���
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param   heapID       HEAP
 * @param	index        ���o������
 * @return	MYSTATUS*    ��̏ꍇ��NULL
 */
//----------------------------------------------------------

MYSTATUS* UnderGroundGetFlag(const UNDERGROUNDDATA* pUGData,int heapID,int index)
{
    int size = (sizeof(STRCODE) * (PERSON_NAME_SIZE+EOM_SIZE));
    int i;
    MYSTATUS* pMy;
    int no = pUGData->newFlagNo - index - 1;

    if(no < 0){
        no += UG_FLAG_NUM_MAX;
    }
    if(pUGData->name[no][0] != 0){
        pMy = MyStatus_AllocWork(heapID);
        MyStatus_SetMyName(pMy, pUGData->name[no]);
        MyStatus_SetRomCode(pMy, pUGData->rom_code[no]);
        MyStatus_SetRegionCode(pMy, pUGData->region_code[no]);
        MyStatus_SetID(pMy, pUGData->id[no]);
        return pMy;
    }
    return NULL;
}


//----------------------------------------------------------
/**
 * @brief	���ɂ���ĕς�闐���V�[�h�𓾂�
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	���ɂ���ĕς�闐���V�[�h
 */
//----------------------------------------------------------
u32 UnderGroundGetDayRandSeed(UNDERGROUNDDATA* pUGData)
{
    return pUGData->randSeed;
}

//----------------------------------------------------------
/**
 * @brief	��܂���A�C�e�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	bDelete      ���ۂɎ��o���Ă������疳���Ȃ�ꍇTRUE �ǂ݂����̏ꍇFALSE
 * @return	ITEM_TYPE ��ɂȂ����� ITEM_DUMMY_DATA
 */
//----------------------------------------------------------
int UnderGroundGetTreasureBagItem(UNDERGROUNDDATA* pUGData, BOOL bDelete)
{
    int i = _getBagTreasureItemIndex(pUGData);
    int ugitem;

    if(i == -1){
        return ITEM_DUMMY_DATA;
    }
    ugitem = pUGData->bagTreasure[i];
    GF_ASSERT_RETURN(DIG_PARTS_TREASURE_MIN <= ugitem, ITEM_HUTOIHONE);
    GF_ASSERT_RETURN(ugitem < DIG_PARTS_TREASURE_MAX, ITEM_HUTOIHONE);
    ugitem -= DIG_PARTS_TREASURE_MIN;
    if(bDelete){
        pUGData->bagTreasure[i] = DIG_PARTS_NONE;  // ����
    }
    return _convertList[ugitem];
}

//----------------------------------------------------------
/**
 * @brief	�������灄�A�C�e���ϊ�
 * @return	ITEM_TYPE ��ɂȂ����� ITEM_DUMMY_DATA
 */
//----------------------------------------------------------
int UnderGroundTreasureItem2Item(int treasureType)
{
    GF_ASSERT_RETURN(DIG_PARTS_TREASURE_MIN <= treasureType, ITEM_HUTOIHONE);
    GF_ASSERT_RETURN(treasureType < DIG_PARTS_TREASURE_MAX, ITEM_HUTOIHONE);
    treasureType -= DIG_PARTS_TREASURE_MIN;
    return _convertList[treasureType];
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���̃O�b�Y�֒ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	goodsNo      �O�b�Y�ԍ�
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo)
{
    int i;

    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            pUGData->pcGoods[i] = goodsNo;
            return TRUE;
        }
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���̃O�b�Y�֒ǉ��ł��邩�`�F�b�N
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	goodsNo      �O�b�Y�ԍ�(�_�~�[�j
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddChkGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo)
{
    int i;

    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            return TRUE;
        }
    }
    return FALSE;
}



//----------------------------------------------------------
/**
 * @brief	�p�\�R���ɃO�b�Y�����������Ă��邩�m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	�O�b�Y��
 */
//----------------------------------------------------------
int UnderGroundGetNumGoodsPCItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_PC_NUM_MAX; i++){
        if( pUGData->pcGoods[i] == GOODS_INVALID ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���̃O�b�Y���m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	�O�b�Y�ԍ� �����ꍇ�� GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundGetGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->pcGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R������O�b�Y���Ƃ肾��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @param	goodsIndex      �z�u�̏���
 * @return	�O�b�Y�ԍ� �����ꍇ�� GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundDelGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    // �����Ă�����̂������o���Ȃ��̂ł��炩���ߌ������邱��
    GF_ASSERT_RETURN(!UnderGroundIsEntryGoodsPCItem(pUGData, listIndex),);

    ix = listIndex;
    type = pUGData->pcGoods[ix];
    for(i = ix ; i < UG_ITEM_PC_NUM_MAX-1; i++){
        pUGData->pcGoods[i] = pUGData->pcGoods[i+1];
    }
    pUGData->pcGoods[UG_ITEM_PC_NUM_MAX-1] = GOODS_INVALID;

    _addEntryGoodsPCItem(pUGData, listIndex, -1); //�G���g���[���Ԃ�������
    return type;
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���̃O�b�Y�����ԕύX
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���̈ʒu
 * @param	nextIndex       ���x�̈ʒu
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeGoodsPcItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0,change = -1;
    u8 pcGoods[UG_ITEM_PC_NUM_MAX];

    MI_CpuCopy8(pUGData->pcGoods,pcGoods,UG_ITEM_PC_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_PC_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->pcGoods[j] = pcGoods[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->pcGoods[j] = pcGoods[listIndex];
            j++;
        }
    }

    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] == (listIndex+1)){
            change = i;
            break;
        }
    }
	
	_addEntryGoodsPCItem(pUGData, nextIndex, 1); //�G���g���[���Ԃ�������
    _addEntryGoodsPCItem(pUGData, listIndex, -1); //�G���g���[���Ԃ�������
    
    if(change != -1){
        if(listIndex<nextIndex){
            pUGData->secretBasePlace[ change ] = nextIndex+1;
        }
        else{
            pUGData->secretBasePlace[ change ] = nextIndex+2;
        }
    }
}


//----------------------------------------------------------
/**
 * @brief	�p�\�R������O�b�Y������ׂɂƂ肾��
 *          ���ۂɂ͎��o�����A�}�[�N�����܂�
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @param	goodsIndex      �z�u�̏���
 * @return	�O�b�Y�ԍ� �����ꍇ�� GOODS_INVALID
 */
//----------------------------------------------------------
int UnderGroundEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int goodsIndex)
{
    int i,ix;

    GF_ASSERT_RETURN(goodsIndex >= SECRETBASE_PC_NUM_MAX, GOODS_INVALID);
    GF_ASSERT_RETURN(goodsIndex <= SECRETBASE_GOODS_NUM_MAX, GOODS_INVALID);
    pUGData->secretBasePlace[goodsIndex - SECRETBASE_PC_NUM_MAX] = listIndex + 1;
    return pUGData->pcGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	���X�g�ԍ��̃A�C�e���������Ă��邩�ǂ�����Ԃ��܂�
 * @param   pUGData       �n���A�C�e���f�[�^�\����
 * @param	listIndex     ���j���[���X�g�̏��� UnderGroundEntryGoodsPCItem�œn�������̂Ɠ���
 * @return	�����Ă���ꍇTRUE
 */
//----------------------------------------------------------

BOOL UnderGroundIsEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i;
    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] == (listIndex+1)){
            return TRUE;
        }
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���֏����Ă������O�b�Y�����ǂ�
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	goodsIndex	�O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundTrashGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsIndex)
{
    if((goodsIndex - SECRETBASE_PC_NUM_MAX) >= SECRETBASE_GOODS_NUM_MAX){
        return;
    }
    pUGData->secretBasePlace[goodsIndex - SECRETBASE_PC_NUM_MAX] = 0;
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���֏����Ă������O�b�Y��S�����ǂ�
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundTrashAllGoodsPCItem(UNDERGROUNDDATA* pUGData)
{
    MI_CpuFill8(pUGData->secretBasePlace, 0, SECRETBASE_GOODS_NUM_MAX);
}

//----------------------------------------------------------
/**
 * @brief	�������Ă���f�[�^index��add���܂�
 * @param   pUGData       �n���A�C�e���f�[�^�\����
 * @param	listIndex     ���̃A�C�e���𔲂��o�����̂Ł@����ȍ~��index��ύX
 * @return	none
 */
//----------------------------------------------------------

static void _addEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int add)
{
    int i;
    for(i = 0; i < SECRETBASE_GOODS_NUM_MAX; i++){
        if(pUGData->secretBasePlace[ i ] > (listIndex+1)){
            pUGData->secretBasePlace[ i ] += add;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�ɃO�b�Y�����������Ă��邩�m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	�O�b�Y��
 */
//----------------------------------------------------------
int UnderGroundGetNumGoodsBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagGoods[i] == GOODS_INVALID ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�̃O�b�Y���m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	�O�b�Y�ԍ� �����ꍇ�� UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagGoods[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O����O�b�Y���Ƃ肾��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @return	�O�b�Y�ԍ� �����ꍇ�� UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagGoods[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagGoods[i] = pUGData->bagGoods[i+1];
    }
    pUGData->bagGoods[UG_ITEM_BAG_NUM_MAX-1] = GOODS_INVALID;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�փO�b�Y��ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	goodsType    �O�b�YType
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType)
{
    int i;

    i = _getFreeBagGoodsItemIndex(pUGData);
    if(i != -1){
        pUGData->bagGoods[i] = goodsType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�փO�b�Y��ǉ��\���`�F�b�N
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	goodsType    �O�b�YType
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddChkGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType)
{
    int i;

    i = _getFreeBagGoodsItemIndex(pUGData);
    if(i != -1){
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�̃O�b�Y�����ԕύX
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���̈ʒu
 * @param	nextIndex       ���x�̈ʒu
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagGoods[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagGoods,bagGoods,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagGoods[j] = bagGoods[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagGoods[j] = bagGoods[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	���΂�ɂ��܂����������Ă��邩�m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	���ܐ�
 */
//----------------------------------------------------------
int UnderGroundGetNumStoneBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagStone[i] == STONE_TYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	���΂�̂��܂��m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	���ܔԍ� �����ꍇ�� STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagStone[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	���΂�̂��܂̂����������m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	����Carat�ԍ� �����ꍇ��1
 */
//----------------------------------------------------------
int UnderGroundGetStoneCaratBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagStoneCarat[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	���΂񂩂炽�܂��Ƃ肾��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @param	goodsIndex      �z�u�̏���
 * @return	���ܔԍ� �����ꍇ�� STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagStone[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagStone[i] = pUGData->bagStone[i+1];
        pUGData->bagStoneCarat[i] = pUGData->bagStoneCarat[i+1];
    }
    pUGData->bagStone[UG_ITEM_BAG_NUM_MAX-1] = STONE_TYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	���΂񂽂܂���֒ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	stoneType    �^�}Type
 * @param	carat        �^�}�̑傫��
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddStoneBagItem(UNDERGROUNDDATA* pUGData, int stoneType, int carat)
{
    int i;

    i = _getFreeBagStoneItemIndex(pUGData);
    if(i != -1){
        pUGData->bagStone[i] = stoneType;
        pUGData->bagStoneCarat[i] = carat;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�̂��܂����ԕύX
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���̈ʒu
 * @param	nextIndex       ���x�̈ʒu
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagStone[UG_ITEM_BAG_NUM_MAX];
    u8 bagStoneCarat[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagStone,bagStone,UG_ITEM_BAG_NUM_MAX);
    MI_CpuCopy8(pUGData->bagStoneCarat,bagStoneCarat,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagStone[j] = bagStone[i];
            pUGData->bagStoneCarat[j] = bagStoneCarat[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagStone[j] = bagStone[listIndex];
            pUGData->bagStoneCarat[j] = bagStoneCarat[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�ɂ������炪���������Ă��邩�m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	�������琔
 */
//----------------------------------------------------------
int UnderGroundGetNumTreasureBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTreasure[i] == STONE_TYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�̂���������m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	��������ԍ� �����ꍇ�� STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetTreasureBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex)
{
    return pUGData->bagTreasure[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O���炨��������Ƃ肾��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @param	goodsIndex      �z�u�̏���
 * @return	��������ԍ� �����ꍇ�� STONE_TYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagTreasure[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagTreasure[i] = pUGData->bagTreasure[i+1];
    }
    pUGData->bagTreasure[UG_ITEM_BAG_NUM_MAX-1] = STONE_TYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�ւ��������ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	treasureType    ��������Type
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddTreasureBagItem(UNDERGROUNDDATA* pUGData, int treasureType)
{
    int i;

    i = _getFreeBagTreasureItemIndex(pUGData);
    if(i != -1){
        pUGData->bagTreasure[i] = treasureType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O�̂�����������ԕύX
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���̈ʒu
 * @param	nextIndex       ���x�̈ʒu
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagTreasure[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagTreasure,bagTreasure,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagTreasure[j] = bagTreasure[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagTreasure[j] = bagTreasure[listIndex];
            j++;
        }
    }
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O��㩂����������Ă��邩�m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	㩐�
 */
//----------------------------------------------------------
int UnderGroundGetNumTrapBagItem(UNDERGROUNDDATA* pUGData)
{
    int i;
    
    for(i = 0;i < UG_ITEM_BAG_NUM_MAX; i++){
        if( pUGData->bagTrap[i] == UG_TRAPTYPE_NONE ){
            break;
        }
    }
    return i;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O��㩂��m�F����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index      0�`�̘A��  
 * @return	㩔ԍ� �����ꍇ�� UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundGetTrapBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i;

    return pUGData->bagTrap[listIndex];
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O����㩂��Ƃ肾��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���j���[���X�g�̏���
 * @return	㩔ԍ� �����ꍇ�� UG_TRAPTYPE_NONE
 */
//----------------------------------------------------------
int UnderGroundDelTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex)
{
    int i,ix,type;

    ix = listIndex;
    type = pUGData->bagTrap[ix];
    for(i = ix ; i < UG_ITEM_BAG_NUM_MAX-1; i++){
        pUGData->bagTrap[i] = pUGData->bagTrap[i+1];
    }
    pUGData->bagTrap[UG_ITEM_BAG_NUM_MAX-1] = UG_TRAPTYPE_NONE;
    return type;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O��㩂�ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	treasureType    �Type
 * @return	����Ȃ�������FALSE
 */
//----------------------------------------------------------
BOOL UnderGroundAddTrapBagItem(UNDERGROUNDDATA* pUGData, int trapType)
{
    int i;

    i = _getFreeBagTrapItemIndex(pUGData);
    if(i != -1){
        pUGData->bagTrap[i] = trapType;
        return TRUE;
    }
    return FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�o�b�O��㩂����ԕύX
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	listIndex       ���̈ʒu
 * @param	nextIndex       ���x�̈ʒu
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundChangeTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex)
{
    int i,j=0,cnt = 0;
    u8 bagTrap[UG_ITEM_BAG_NUM_MAX];

    MI_CpuCopy8(pUGData->bagTrap,bagTrap,UG_ITEM_BAG_NUM_MAX);
    for(i = 0 ; i < UG_ITEM_BAG_NUM_MAX; i++){
        if(i != listIndex){
            pUGData->bagTrap[j] = bagTrap[i];
            j++;
        }
        if(i == nextIndex){
            pUGData->bagTrap[j] = bagTrap[listIndex];
            j++;
        }
    }
}


#define UG_TRAP_PLACE_NUM_MAX (16)  // �z�u����㩂̍ő吔
//----------------------------------------------------------
/**
 * @brief	�n�ʂ֎��R��㩂�ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	trapType    �Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,);
    pUGData->groundNatureTrapType[index]=trapType;
    pUGData->groundNatureTrapPos[index][0] = x;
    pUGData->groundNatureTrapPos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundNatureTrapPos[index][2] = z;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂւ���㩃^�C�v�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	㩃^�C�v
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    return pUGData->groundNatureTrapType[index];
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����X���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�X���W
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos;
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    pos = pUGData->groundNatureTrapPos[index][0];
    pos += (pUGData->groundNatureTrapPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����Z���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�Z���W
 */
//----------------------------------------------------------

int UnderGroundGetNatureTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos;
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,0);
    pos = pUGData->groundNatureTrapPos[index][2];
    pos += (pUGData->groundNatureTrapPos[index][1] << 4) & 0xf00;
    return pos;
}


//----------------------------------------------------------
/**
 * @brief	���R��㩂�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	trapType    �Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundDelNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int index)
{
    GF_ASSERT_RETURN(index < UG_NATURETRAP_PLACE_NUM_MAX,);
    pUGData->groundNatureTrapType[index] = UG_TRAPTYPE_NONE;
    MI_CpuClear8(pUGData->groundNatureTrapPos[index],3);
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ�㩂�ǉ�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	trapType    �Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z,int order)
{
    GF_ASSERT_RETURN(index < UG_TRAP_PLACE_NUM_MAX,);
    pUGData->groundTrapType[index]=trapType;
    pUGData->groundTrapPos[index][0] = x;
    pUGData->groundTrapPos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundTrapPos[index][2] = z;
    pUGData->groundTrapOrder[index]=order;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂւ���㩃^�C�v�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	㩃^�C�v
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundTrapType[index];
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����X���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�X���W
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundTrapPos[index][0];

    pos += (pUGData->groundTrapPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����Z���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�Z���W
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundTrapPos[index][2];

    pos += (pUGData->groundTrapPos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ��琶�����Ԃ������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	order
 */
//----------------------------------------------------------

int UnderGroundGetTrapGroundItemOrder(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundTrapOrder[index];
}


//----------------------------------------------------------
/**
 * @brief	�n�ʂ֐΂����߂�
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	stoneType    ��Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundAddStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat, int addCarat)
{
    GF_ASSERT_RETURN(index < UG_STONE_PLACE_NUM_MAX,);
    pUGData->groundStoneType[index] = stoneType;
    pUGData->groundStonePos[index][0] = x;
    pUGData->groundStonePos[index][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
    pUGData->groundStonePos[index][2] = z;
    pUGData->groundStoneCarat[index] = carat;
    pUGData->groundStoneCaratAdd[index] = addCarat;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ֐΂𖄂߂�  ���߂�Ƃ��ɂ͐������O
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	stoneType    ��Type
 * @return	none
 */
//----------------------------------------------------------
void UnderGroundBuryStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat)
{
    UnderGroundAddStoneGroundItem(pUGData, stoneType, index, x, z, carat, 0);
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂւ���΃^�C�v�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	㩃^�C�v
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemType(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneType[index];
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����X���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	��X���W
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundStonePos[index][0];

    pos += (pUGData->groundStonePos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����Z���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	��Z���W
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundStonePos[index][2];

    pos += (pUGData->groundStonePos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ���΂̑傫���������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�΂̑傫��
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCarat(UNDERGROUNDDATA* pUGData,int index)
{
    int carat = pUGData->groundStoneCarat[index]+pUGData->groundStoneCaratAdd[index];

    if(carat > UG_STONE_CARAT_MAX){
        carat = UG_STONE_CARAT_MAX;
    }
    return carat;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ���΂̃I���W�i���̑傫���������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�΂̑傫��
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCaratOrg(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneCarat[index];
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ���΂̑������������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	�΂̑傫��
 */
//----------------------------------------------------------

int UnderGroundGetStoneGroundItemCaratMul(UNDERGROUNDDATA* pUGData,int index)
{
    return pUGData->groundStoneCaratAdd[index];
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ։��΂��L�^����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	x,z  �ʒu�����L��
 * @return	index
 */
//----------------------------------------------------------
int UnderGroundAddFossilGroundItem(UNDERGROUNDDATA* pUGData, int x,int z)
{
    int i;
    
    for(i = 0;i < UG_FOSSIL_PLACE_NUM_MAX;i++){
        if((pUGData->groundFossilPos[i][0] == 0) &&
           (pUGData->groundFossilPos[i][1] == 0) &&
           (pUGData->groundFossilPos[i][2] == 0) ){
            pUGData->groundFossilPos[i][0] = x;
            pUGData->groundFossilPos[i][1] = ((x & 0xf00) >> 8) + ((z & 0xf00) >> 4);
            pUGData->groundFossilPos[i][2] = z;
            return i;
        }
    }
    return 0;
}

//----------------------------------------------------------
/**
 * @brief	���΃f�[�^������
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	x,z  �ʒu�����L��
 * @return	index
 */
//----------------------------------------------------------
void UnderGroundDelFossilGroundItem(UNDERGROUNDDATA* pUGData, int index)
{
    GF_ASSERT_RETURN(index < UG_FOSSIL_PLACE_NUM_MAX,);
    MI_CpuFill8( pUGData->groundFossilPos[index] , 0, 3);
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����X���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	��X���W
 */
//----------------------------------------------------------

int UnderGroundGetFossilGroundItemX(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundFossilPos[index][0];

    pos += (pUGData->groundFossilPos[index][1] << 8) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	�n�ʂ����Z���W�������o��
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param	index  �L���o�b�t�@�̏���
 * @return	��Z���W
 */
//----------------------------------------------------------

int UnderGroundGetFossilGroundItemZ(UNDERGROUNDDATA* pUGData,int index)
{
    int pos = pUGData->groundFossilPos[index][2];

    pos += (pUGData->groundFossilPos[index][1] << 4) & 0xf00;
    return pos;
}

//----------------------------------------------------------
/**
 * @brief	���΂��@��̂͏��߂Ă��ǂ���
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	TRUE�Ȃ牻�Δz�u
 */
//----------------------------------------------------------

BOOL UnderGroundIsFirstFossil(UNDERGROUNDDATA* pUGData)
{
    return (pUGData->bFossilFirst==FALSE);
}

//----------------------------------------------------------
/**
 * @brief	���΂��@��̂͏��߂�FLG��ON
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	TRUE�Ȃ牻�Δz�u
 */
//----------------------------------------------------------

void UnderGroundSetFirstFossil(UNDERGROUNDDATA* pUGData)
{
    pUGData->bFossilFirst = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	���΂�V�����z�u���邩�ǂ���
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	TRUE�Ȃ牻�Δz�u
 */
//----------------------------------------------------------

BOOL UnderGroundIsNewDay(UNDERGROUNDDATA* pUGData)
{
    return pUGData->bNewDay;
}

//----------------------------------------------------------
/**
 * @brief	���΂�z�u���I�������t���O������
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return  none
 */
//----------------------------------------------------------

void UnderGroundResetNewDay(UNDERGROUNDDATA* pUGData)
{
    pUGData->bNewDay = FALSE;
}

//----------------------------------------------------------
/**
 * @brief	�@�������΂��L�^ �i���A�v���[�g�����L���j
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param   type         �@�������Ύ��
 * @return  none
 */
//----------------------------------------------------------

void UnderGroundSetFossilDig(UNDERGROUNDDATA* pUGData,int type)
{
    if((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON)){
        return;
    }
    pUGData->digBit |= (0x0001 << (type - DIG_PARTS_PLATE_FIRE));
}

//----------------------------------------------------------
/**
 * @brief	���̉��΂��o���Ă悢�̂�����
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @param   type         �@�������Ύ��
 * @return  none
 */
//----------------------------------------------------------

BOOL UnderGroundIsFossilAdvent(UNDERGROUNDDATA* pUGData,int type)
{
    if((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON)){
        return TRUE;
    }
    if((pUGData->digBit & (0x0001 << (type - DIG_PARTS_PLATE_FIRE))) ){
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	�n����������������J�E���g
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	order
 */
//----------------------------------------------------------

void UnderGroundCountWalk(UNDERGROUNDDATA* pUGData)
{
    if(pUGData->walk >= (_MAX_WALK_COUNT-1)){
        pUGData->walk = 0;
    }
    else{
        pUGData->walk++;
    }
}

//----------------------------------------------------------
/**
 * @brief	�n��������������������o���i�P�O�O���Ń��Z�b�g�j
 * @param   pUGData      �n���A�C�e���f�[�^�\����
 * @return	����
 */
//----------------------------------------------------------

int UnderGroundGetWalkNum(UNDERGROUNDDATA* pUGData)
{
    return pUGData->walk;
}

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�̏�����
 * @param	pSBData		SECRETBASEDATA���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void SecretBaseData_Init(SECRETBASEDATA* pSBData)
{
	MI_CpuFill8(pSBData, 0, sizeof(SECRETBASEDATA));
}

//----------------------------------------------------------
/**
 * @brief	�n���X�e�[�^�X�f�[�^�̏�����(���R�[�h�ȊO)
 * @param	pSBData		SECRETBASEDATA���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------

void SecretBaseData_Reform(SECRETBASEDATA* pSBData)
{
    MI_CpuClear8(pSBData->goodsPos,SECRETBASE_GOODS_NUM_MAX*sizeof(SB_GOODS));
    MI_CpuClear8(pSBData->rockPos,SECRETBASE_LOCK_NUM_MAX*sizeof(SB_LOCK));
    pSBData->xpos=0;         // �h�A�̈ʒu
    pSBData->zpos=0;
    pSBData->dir=0;        // �O�ɏo�Ă�h�A�̕���
    pSBData->bMake=0;     //  ��������ǂ���
}

//----------------------------------------------------------
/**
 * @brief	�閧��n���ꎞ�I�ɏ���
 * @param	pSBData	 SECRETBASEDATA���[�N�|�C���^
 */
//----------------------------------------------------------

void SecretBaseData_SetMakeDown(SECRETBASEDATA* pSBData)
{
    pSBData->bMake = FALSE;     //  ��������ǂ���
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Y�̈ʒu��ݒ肷��  �����ꍇ�ɂ͑S���O    �p�~�\��
 * @param	pSBData	 SECRETBASEDATA���[�N�|�C���^
 * @param	goodsIndex	�O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @param   type    �O�b�Y�^�C�v
 * @param	x,z      �ʒu
 */
//----------------------------------------------------------
void SecretBaseData_SetGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int type, int x, int z)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,);
    GF_ASSERT_RETURN(x < 32,);
    GF_ASSERT_RETURN(z < 32,);
    GF_ASSERT_RETURN(pSBData,);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return;  // �p�\�R���̈ʒu�͗v��Ȃ�
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // �O�b�Y�������Ă���
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].x = x;
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].z = z;
        pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].type = type;
    }
    else{  // �c��͊�
        pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x = x;
        pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z = z;
    }
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Y�̈ʒu��ύX����  �����ꍇ�ɂ͑S���O
 * @param	pSBData	 SECRETBASEDATA���[�N�|�C���^
 * @param	goodsIndex	�O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @param	x,z      �ʒu
 */
//----------------------------------------------------------
void SecretBaseData_ChangeGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int x, int z)
{
    int type = SecretBaseData_GetGoodsType(pSBData, goodsIndex);
    SecretBaseData_SetGoodsPosition(pSBData, goodsIndex, type, x, z);
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R����type�𓾂�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @return 	�O�b�Y�^�C�v+�p�\�R���^�C�v
 */
//----------------------------------------------------------

static int _getPCType(const SECRETBASEDATA* pSBData)
{
    int num = pSBData->recordData.flagDeliveryCount;
    
    if(FLAG_PLATINA_LV_NUM <= num){
        return GOODS_FLAG_PLATINA_PC;
    }
    else if(FLAG_GOLD_LV_NUM <= num){
        return GOODS_FLAG_GOLD_PC;
    }
    else if(FLAG_SILVER_LV_NUM <= num){
        return GOODS_FLAG_SILVER_PC;
    }
    else if(FLAG_BRONZE_LV_NUM <= num){
        return GOODS_FLAG_BRONZE_PC;
    }
    return GOODS_FLAG_NORMAL_PC;
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Ytype�𓾂�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @param	goodsIndex	  �O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	�O�b�Y�^�C�v
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsType(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,GOODS_INVALID);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _getPCType(pSBData);
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // �O�b�Y�������Ă���
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].type;
    }
    else if( (pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x != _INVALID_POS)
             && (pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z != _INVALID_POS) ){
        // �c��͊�
        return GOODS_BIG_ROCK;
    }
    return GOODS_INVALID;
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Yx�ʒu�𓾂�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @param	goodsIndex	  �O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	�O�b�Yx���W
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsXPos(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,_PCPOS_X);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _PCPOS_X;
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // �O�b�Y�������Ă���
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].x;
    }
      // �c��͊�
    return pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].x;
}

//----------------------------------------------------------
/**
 * @brief	�O�b�Yz�ʒu�𓾂�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @param	goodsIndex	  �O�b�Y�̏��� 0-SECRETBASE_SETUPOBJ_NUM_MAX
 * @return 	�O�b�Yz���W
 */
//----------------------------------------------------------
int SecretBaseData_GetGoodsZPos(const SECRETBASEDATA* pSBData, int goodsIndex)
{
    GF_ASSERT_RETURN(goodsIndex < SECRETBASE_SETUPOBJ_NUM_MAX,_PCPOS_Z);

    if(SECRETBASE_PC_INDEX_NO == goodsIndex){
        return _PCPOS_Z;
    }
    else if(goodsIndex < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)) { // �O�b�Y�������Ă���
        return pSBData->goodsPos[goodsIndex - SECRETBASE_PC_NUM_MAX].z;
    }
    // �c��͊�
    return pSBData->rockPos[goodsIndex - SECRETBASE_PC_NUM_MAX - SECRETBASE_GOODS_NUM_MAX].z;
}

//----------------------------------------------------------
/**
 * @brief	����ǂ̂��炢�ێ����Ă��Ȃ��Ƃ����Ȃ�����Ԃ�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @return 	��ێ���
 */
//----------------------------------------------------------
int SecretBaseData_GetPlaceRockLimit(const SECRETBASEDATA* pSBData)
{
    if(pSBData->recordData.flagDeliveryCount >=  FLAG_PLATINA_LV_NUM){
        return 0;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_GOLD_LV_NUM){
        return 6;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_SILVER_LV_NUM){
        return 11;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_BRONZE_LV_NUM){
        return 15;
    }
    return 16;
}

//----------------------------------------------------------
/**
 * @brief	�z�u���������܂Œu���Ă����̂���Ԃ�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @return 	�u���Ă����O�b�Y�̐�
 */
//----------------------------------------------------------
int SecretBaseData_GetPlaceGoodsLimit(const SECRETBASEDATA* pSBData)
{
    if(pSBData->recordData.flagDeliveryCount >=  FLAG_PLATINA_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_GOLD_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_SILVER_LV_NUM){
        return 15;
    }
    else if(pSBData->recordData.flagDeliveryCount >= FLAG_BRONZE_LV_NUM){
        return 12;
    }
    return 10;
}

//==============================================================================
/**
 * �����|�C���g	�����Ƃ�����A㩂ɂ������Ƃ��ɂ��炦��|�C���g�B
 * @param   none
 * @retval  �����|�C���g
 */
//==============================================================================
int SecretBaseRecordGetPoint(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->pointCount;
}

//==============================================================================
/**
 * �n���̍�������
 * @param   none
 * @retval  ����RANK
 */
//==============================================================================
int SecretBaseRecordGetUGRank(const SB_RECORD_DATA* pSBRecord)
{

    if(4 == SecretBaseRecordGetFlagType(pSBRecord)){
        return UG_RANK_MASTER;
    }
    return UG_RANK_BEGINNER;
}


//==============================================================================
/**
 * �����|�C���g	�����Ƃ�����A㩂ɂ������Ƃ��ɂ��炦��|�C���g���Z
 * @param   add  ���Z  �� ���Z�|�C���g
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetPoint(SB_RECORD_DATA* pSBRecord, int add)
{
    pSBRecord->pointCount = add;
}

//==============================================================================
/**
 * �ł������l�̐l��	�ʐM����Ƙb�����񐔂ł��B�����l�ł��P�O��܂ŃJ�E���g���܂��B
 * @param   none
 * @retval  �ł������l�̐l��
 */
//==============================================================================
int SecretBaseRecordGetTalkNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->talkCount;
}

//==============================================================================
/**
 * �ł������l�̐l��	�ʐM����Ƙb�����񐔂ł��B�����l�ł��P�O��܂ŃJ�E���g���܂��B
 * @param   
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetTalkNum(SB_RECORD_DATA* pSBRecord, int meetNetID)
{
    if(pSBRecord->talkCount < _MAX){
        pSBRecord->talkCount++;
    }
}

//==============================================================================
/**
 * �������������	�N���ɓ�����グ���񐔁B�����l�ɂ����Ă��J�E���g���܂��B
 * @param   
 * @retval  none
 */
//==============================================================================
int SecretBaseRecordGetSendItemNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->sendItemCount;
}

//==============================================================================
/**
 * �������������	�N���ɓ�����グ���񐔁B�����l�ɂ����Ă��J�E���g���܂��B
 * @param   
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetSendItemNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->sendItemCount < _MAX){
        pSBRecord->sendItemCount++;
    }
}

//==============================================================================
/**
 * �n�^���Ƃ�����	����̃n�^���Ƃ����񐔂ł��B�����l�ł��J�E���g���܂��B
 * @param   none
 * @retval  �n�^���Ƃ�����
 */
//==============================================================================
int SecretBaseRecordGetFlagConquerNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagConquerCount;
}

//==============================================================================
/**
 * �n�^���Ƃ�����	����̃n�^���Ƃ����񐔂ł��B�����l�ł��J�E���g���܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFlagConquerNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagConquerCount < _MAX){
        pSBRecord->flagConquerCount++;
    }
}

//----------------------------------------------------------
/**
 * @brief	�p�\�R���̊���type�𓾂�
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @return 	�n�^�����N
 */
//----------------------------------------------------------

int SecretBaseRecordGetFlagType(const SB_RECORD_DATA* pSBRecord)
{
    int num = pSBRecord->flagDeliveryCount;
    
    if(FLAG_PLATINA_LV_NUM <= num){
        return 4;
    }
    else if(FLAG_GOLD_LV_NUM <= num){
        return 3;
    }
    else if(FLAG_SILVER_LV_NUM <= num){
        return 2;
    }
    else if(FLAG_BRONZE_LV_NUM <= num){
        return 1;
    }
    return 0;
}

//==============================================================================
/**
 * �n�^��[�i������	����̃n�^��[�i�����񐔂ł��B�����l�ł��J�E���g���܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
int SecretBaseRecordGetFlagDeliveryNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagDeliveryCount;
}

//==============================================================================
/**
 * �n�^��[�i������	����̃n�^��[�i�����񐔂ł��B�����l�ł��J�E���g���܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagDeliveryCount < _MAX){
        pSBRecord->flagDeliveryCount++;
    }
}

//==============================================================================
/**
 * �n�^��[�i������	����̃n�^��[�i�����񐔂ł��B�����l�ł��J�E���g���܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================
#ifdef PM_DEBUG
void D_SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord,int num)
{
    pSBRecord->flagDeliveryCount = num;
}
#endif

//==============================================================================
/**
 * �^�}���@������	�~�j�Q�[���ŁA�^�}���@��o�����񐔂ł��B���߂��^�}���@��o���Ă��J�E���g���܂��B
 * @param   none
 * @retval  �^�}���@������
 */
//==============================================================================
int SecretBaseRecordGetStoneNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->stoneCount;
}

//==============================================================================
/**
 * �^�}���@������	�~�j�Q�[���ŁA�^�}���@��o�����񐔂ł��B���߂��^�}���@��o���Ă��J�E���g���܂��B
 * @param   add  ������
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetStoneNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->stoneCount > (_MAX - add))){
        pSBRecord->stoneCount = _MAX;
    }
    else{
        pSBRecord->stoneCount += add;
    }
}

//==============================================================================
/**
 * ���΂��@������	���΂��@�����񐔂ł��B�~�j�Q�[���Ŏ�ɓ��ꂽ���΂̐��ł��B
 * @param   none
 * @retval  �^�}���@������
 */
//==============================================================================
int SecretBaseRecordGetFossilNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->fossilCount;
}

//==============================================================================
/**
 * ���΂��@������	���΂��@�����񐔂ł��B�~�j�Q�[���Ŏ�ɓ��ꂽ���΂̐��ł��B
 * @param   add   ������
 * @retval  none
 */
//==============================================================================
void SecretBaseRecordSetFossilNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->fossilCount > (_MAX - add))){
        pSBRecord->fossilCount = _MAX;
    }
    else{
        pSBRecord->fossilCount += add;
    }
}

//==============================================================================
/**
 * ����@������	����@�����񐔂ł��B�~�j�Q�[���Ŏ�ɓ��ꂽ��̐��ł��B
 * @param   none
 * @retval  ����@������
 */
//==============================================================================

int SecretBaseRecordGetTreasureNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->treasureCount;
}

//==============================================================================
/**
 * ����@������	����@�����񐔂ł��B�~�j�Q�[���Ŏ�ɓ��ꂽ��̐��ł��B
 * @param   add   ������
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTreasureNum(SB_RECORD_DATA* pSBRecord, int add)
{
    if((add > 0) && (pSBRecord->treasureCount > (_MAX - add))){
        pSBRecord->treasureCount = _MAX;
    }
    else{
        pSBRecord->treasureCount += add;
    }
}

//==============================================================================
/**
 * �g���b�v����������	������g���b�v�ɂ������񐔂ł��B
 * @param   none
 * @retval  �g���b�v����������
 */
//==============================================================================

int SecretBaseRecordGetTrapConquerNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapConquerCount;
}

//==============================================================================
/**
 * �g���b�v����������	������g���b�v�ɂ������񐔂ł��B
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapConquerNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapConquerCount < _MAX){
        pSBRecord->trapConquerCount++;
    }
}

//==============================================================================
/**
 * �g���b�v�ɂ���������	�������g���b�v�ɂ��������񐔂ł��B
 * @param   none
 * @retval  �g���b�v�ɂ���������
 */
//==============================================================================

int SecretBaseRecordGetTrapTumbleNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapTumbleCount;
}

//==============================================================================
/**
 * �g���b�v�ɂ���������	�������g���b�v�ɂ��������񐔂ł��B
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapTumbleNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapTumbleCount < _MAX){
        pSBRecord->trapTumbleCount++;
    }
}

//==============================================================================
/**
 * �l����������	�g���b�v�ɂ������Ă���l���������񐔂ł��B
 * @param   none
 * @retval  �l����������
 */
//==============================================================================

int SecretBaseRecordGetTrapRescueNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->trapRescueCount;
}

//==============================================================================
/**
 * �l����������	�g���b�v�ɂ������Ă���l���������񐔂ł��B
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetTrapRescueNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->trapRescueCount < _MAX){
        pSBRecord->trapRescueCount++;
    }
}

//==============================================================================
/**
 * ��������������	�N���ɓ������������񐔂ł��B�����ЂƂ��������Ă��A�J�E���g���܂��B
 * @param   none
 * @retval  ��������������
 */
//==============================================================================

int SecretBaseRecordGetItemRecvNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->itemRecvCount;
}

//==============================================================================
/**
 * ��������������	�N���ɓ������������񐔂ł��B�����ЂƂ��������Ă��A�J�E���g���܂��B
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetItemRecvNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->itemRecvCount < _MAX){
        pSBRecord->itemRecvCount++;
    }
}

//==============================================================================
/**
 * �����Ƃ�ꂽ��	�N���Ƀn�^���Ƃ�ꂽ�񐔂ł��B
 * @param   none
 * @retval  �����Ƃ�ꂽ��
 */
//==============================================================================

int SecretBaseRecordGetFlagStealNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagStealCount;
}

//==============================================================================
/**
 * �����Ƃ�ꂽ��	�N���Ƀn�^���Ƃ�ꂽ�񐔂ł��B
 * @param   none
 * @retval  none
 */
//==============================================================================

void SecretBaseRecordSetFlagStealNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagStealCount < _MAX){
        pSBRecord->flagStealCount++;
    }
}

//==============================================================================
/**
 * �������Ԃ�����	�n�^�����Ԃ����񐔂ł��B
 * @param   none
 * @retval  �����Ƃ�ꂽ��
 */
//==============================================================================

int SecretBaseRecordGetFlagReverseNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->flagReverseCount;
}

void SecretBaseRecordSetFlagReverseNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->flagReverseCount < _MAX){
        pSBRecord->flagReverseCount++;
    }
}

//==============================================================================
/**
 * �����z��������	�����z���������񐔂ł��B
 * @param   none
 * @retval  �����z��������
 */
//==============================================================================

int SecretBaseRecordGetRelocateNum(const SB_RECORD_DATA* pSBRecord)
{
    return pSBRecord->relocateCount;
}

void SecretBaseRecordSetRelocateNum(SB_RECORD_DATA* pSBRecord)
{
    if(pSBRecord->relocateCount < _MAX){
        pSBRecord->relocateCount++;
    }
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n�ʒu��ݒ肷��
 * @param	pSec			�閧��n�f�[�^
 * @param	x,z,dir			�o���̏ꏊ
 * @return	none
 */
//---------------------------------------------------------------------------
void SecretBaseSetSecretBasePosition(SECRETBASEDATA* pSec,int x,int z,int dir)
{
    pSec->xpos = x;         // �h�A�̈ʒu
    pSec->zpos = z;
    pSec->dir = dir;        // �O�ɏo�Ă�h�A�̕���
    pSec->bMake = TRUE;     //  ��������ǂ���
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n�ʒuX�𓾂邷��
 * @param	pSec			�閧��n�f�[�^
 * @param	x,z,dir			�o���̏ꏊ
 * @return	none
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionX(const SECRETBASEDATA* pSec)
{
    return pSec->xpos;         // �h�A�̈ʒu
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n�ʒuZ�𓾂邷��
 * @param	pSec			�閧��n�f�[�^
 * @return	z			�o���̏ꏊ
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionZ(const SECRETBASEDATA* pSec)
{
    return pSec->zpos;
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n�ʒu�����𓾂邷��
 * @param	pSec			�閧��n�f�[�^
 * @return	dir			�o���̏ꏊ
 */
//---------------------------------------------------------------------------
int SecretBaseGetSecretBasePositionDir(const SECRETBASEDATA* pSec)
{
    return pSec->dir;
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n��������Ƃ����邩�ǂ���
 * @param	pSec			�閧��n�f�[�^
 * @return	����Ă�����TRUE
 */
//---------------------------------------------------------------------------
BOOL SecretBaseIsSecretBaseMake(const SECRETBASEDATA* pSec)
{
    return pSec->bMake;     //  ��������ǂ���
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n�f�[�^�����o��
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	SECRETBASEDATA	�閧��n�f�[�^�|�C���^
 */
//---------------------------------------------------------------------------
SECRETBASEDATA* SaveData_GetSecretBaseData(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return &ugd->base;
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n���R�[�h�f�[�^�����o��
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	SB_RECORD_DATA	�閧��n���R�[�h�f�[�^�|�C���^
 */
//---------------------------------------------------------------------------
SB_RECORD_DATA* SaveData_GetSecretBaseRecord(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return &ugd->base.recordData;
}

//---------------------------------------------------------------------------
/**
 * @brief	�閧��n���R�[�h�f�[�^�����o��
 * @param	pSec			�閧��n�f�[�^
 * @return	SB_RECORD_DATA	�閧��n���R�[�h�f�[�^�|�C���^
 */
//---------------------------------------------------------------------------
SB_RECORD_DATA* SecretBaseGetSecretBaseRecord(SECRETBASEDATA* pSec)
{
	return &pSec->recordData;
}

//---------------------------------------------------------------------------
/**
 * @brief	�n���A�C�e���f�[�^���Z�[�u������o��
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	UNDERGROUNDDATA	�n���A�C�e���f�[�^�|�C���^
 */
//---------------------------------------------------------------------------
UNDERGROUNDDATA* SaveData_GetUnderGroundData(SAVEDATA * sv)
{
	UNDERGROUNDDATA* ugd;
	ugd = SaveData_Get(sv, GMDATA_ID_UNDERGROUNDDATA);
	return ugd;
}


#ifdef PM_DEBUG

//----------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F�n���󕨂����΂��
 * @param	pSBData	      UNDERGROUNDDATA���[�N�|�C���^
 * @param	type     �n���A�C�e���^�C�v
 */
//----------------------------------------------------------
void Debug_UnderGroundData_AddTreasure(UNDERGROUNDDATA* pUGData, int type)
{
    int i = _getFreeBagTreasureItemIndex(pUGData);
    if(i == -1){
        return;
    }
    GF_ASSERT(DIG_PARTS_TREASURE_MIN <= type);
    GF_ASSERT(type < DIG_PARTS_TREASURE_MAX);
    pUGData->bagTreasure[i] = type;
}

static SB_LOCK* _getFreeLockBuff(SECRETBASEDATA* pSBData)
{
    int i;
    for(i = 0;i < SECRETBASE_LOCK_NUM_MAX; i++){
        if( (pSBData->rockPos[i].x == _INVALID_POS) &&
            (pSBData->rockPos[i].z == _INVALID_POS) ){
            return &pSBData->rockPos[i];
        }
    }
    return NULL;
}

static SB_GOODS* _getFreeGoodsBuff(SECRETBASEDATA* pSBData)
{
    int i;
    for(i = 0;i < SECRETBASE_GOODS_NUM_MAX; i++){
        if( pSBData->goodsPos[i].type == GOODS_INVALID ){
            return &pSBData->goodsPos[i];
        }
    }
    return NULL;
}

//----------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F�O�b�Y�ݒu  (�p�\�R���ւ��o�^���܂�)
 * @param	pSBData	      SECRETBASEDATA���[�N�|�C���^
 * @param	name	���O������ւ̃|�C���^
 * @param	sex		���ʎw��
 */
//----------------------------------------------------------
void Debug_SecretBaseData_AddGoods(SECRETBASEDATA* pSBData, int goodsType, int x, int z)
{
    if(GOODS_BIG_ROCK == goodsType){
        SB_LOCK* pLock = _getFreeLockBuff(pSBData);
        if(pLock != NULL){
            pLock->x = x;
            pLock->z = z;
        }
    }
    else if(goodsType < GOODS_BIG_ROCK){  // �p�\�R���͌Œ�ʒu
    }
    else{
        SB_GOODS* pGoods = _getFreeGoodsBuff(pSBData);
        if(pGoods != NULL){
            pGoods->type = goodsType;
            pGoods->x = x;
            pGoods->z = z;
        }
    }
}


#endif //PM_DEBUG
