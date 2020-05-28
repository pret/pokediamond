//============================================================================================
/**
 * @file	poke_regulation.c
 * @bfief	���M�����[�V�����ɓK�����邩�̃c�[��
 * @author	k.ohno
 * @date	06.05.25
 */
//============================================================================================

#include "common.h"
#include "poketool/poke_regulation.h"
#include "poketool/pokeparty.h"
#include "itemtool/itemsym.h"

#include "poketool/monsno.h"
#include "savedata/regulation_data.h"

#define _POKENO_NONE  (0)          // �|�P�����ԍ��łȂ��ԍ�

#ifdef DEBUG_ONLY_FOR_ohno
static void _testRegulation(ZKN_HEIGHT_GRAM_PTR pZKN);
#endif

//------------------------------------------------------------------
/**
 * �|�P���������M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ�O�ɐ}�Ӄf�[�^���K�v
 * �Ȃ̂Ő}�Ӄf�[�^�����M�����[�V�����p�Ɋm�ۂ��܂�  ���炩���߂���ꍇ�ɂ͂���܂���
 * @param   heap_id
 * @return  ZKN_HEIGHT_GRAM_PTR*
 */
//------------------------------------------------------------------

ZKN_HEIGHT_GRAM_PTR PokeRegulationInit(int heap_id )
{
    ZKN_HEIGHT_GRAM_PTR pZKN = ZKN_HEIGHTGRAM_Alloc( heap_id );
    ZKN_HEIGHTGRAM_Load(pZKN, ZKN_HEIGHT_GRAM_TYPE_MAN, heap_id);
#ifdef DEBUG_ONLY_FOR_ohno
    //_testRegulation(pZKN);
#endif
    return pZKN;
}

//------------------------------------------------------------------
/**
 * �|�P���������M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ���A�}�ӂ�j��
 * @param   ZKN_HEIGHT_GRAM_PTR*
 * @return  none
 */
//------------------------------------------------------------------

void PokeRegulationEnd(ZKN_HEIGHT_GRAM_PTR pZKN)
{
    ZKN_HEIGHTGRAM_Release(pZKN);
    ZKN_HEIGHTGRAM_Free(pZKN);
}

//------------------------------------------------------------------
/**
 * �|�P���������M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ�
 * @param   POKEMON_PARAM
 * @param   REGULATION
 * @return  ���v������TRUE
 */
//------------------------------------------------------------------

BOOL PokeRegulationCheckPokePara(const REGULATION* pReg, POKEMON_PARAM* pp, const ZKN_HEIGHT_GRAM_PTR pZKN)
{
	u16 mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
    int ans,height,weight;

    if(pReg==NULL){
        return TRUE;
    }
    //LV
    ans = Regulation_GetParam(pReg, REGULATION_LEVEL);
    if(PokeParaGet(pp, ID_PARA_level, NULL) > ans){
        return FALSE;
    }
    //���܂��Q��s��
    if( PokeParaGet(pp, ID_PARA_tamago_flag, NULL ) != 0 ){
        return FALSE;
    }
    // �i���|�P�������ǂ���
    ans = Regulation_GetParam(pReg, REGULATION_EVOLUTION);
    if(ans==0){  // �i���|�P�������ǂ�������������΂���
        if(mons != PokeChildCheck(mons)){  // �����ȊO���A���Ă���̂͂��������̂ł͂���
            return FALSE;
        }
    }
    // ����
    ans = Regulation_GetParam(pReg, REGULATION_HEIGHT);
    if(ans != 0){
        height = ZKN_HEIGHTGRAM_GetHeight(pZKN, mons);
        if(ans > 0){
            if(height < ans){
                return FALSE;
            }
        }
        else{
            if(height > (-ans)){
                return FALSE;
            }
        }
    }
    // �d��
    ans = Regulation_GetParam(pReg, REGULATION_WEIGHT) * 10;
    if(ans != 0){
        weight = ZKN_HEIGHTGRAM_GetGram(pZKN, mons);
        if(ans > 0){
            if(weight < ans){
                return FALSE;
            }
        }
        else{
            if(weight > (-ans)){
                return FALSE;
            }
        }
    }
    // �`���|�P������
    ans = Regulation_GetParam(pReg, REGULATION_LEGEND);
    if(ans == 0){
        if(BattleTowerExPokeCheck_PokePara(pp)){
            return FALSE;
        }
    }
    return TRUE;
}

//------------------------------------------------------------------
/**
 * �|�P�p�[�e�B�����M�����[�V�����ɓK�����Ă��邩�ǂ������ׂ�
 * @param   POKEMON_PARAM
 * @param   REGULATION
 * @param   ZKN_HEIGHT_GRAM_PTR
 * @param   party��I�������z��  0�ȊO���I�����Ă���
 * @return  
 */
//------------------------------------------------------------------

int PokeRegulationMatchFullPokeParty(const REGULATION* pReg, POKEPARTY * party,
                                      const ZKN_HEIGHT_GRAM_PTR pZKN, u8* sel)
{
    POKEMON_PARAM* pp;
    int ans,cnt = 0,j,i,level = 0;
    u16 monsTbl[6],itemTbl[6];

    if(pReg==NULL){
        return POKE_REG_OK;
    }
    for(i = 0; i < 6 ;i++){
        monsTbl[i] = _POKENO_NONE;
		itemTbl[i] = ITEM_DUMMY_DATA;
        if(sel[i]){
            cnt++;
        }
    }
    OS_TPrintf("sel %d %d %d %d %d %d\n",sel[0],sel[1],sel[2],sel[3],sel[4],sel[5]);

    //�S�̐�
    ans = Regulation_GetParam(pReg, REGULATION_POKE_NUM);
    if(cnt != ans){
        return POKE_REG_NUM_FAILED;  // ���͈�v������
    }
    for(i = 0; i < 6 ;i++){
        if(sel[i]){
            int pid = sel[i]-1;
            pp = PokeParty_GetMemberPointer(party, pid);
            if(PokeRegulationCheckPokePara(pReg, pp, pZKN) == FALSE){
                return POKE_REG_ILLEGAL_POKE; // �̂�������������
            }
            monsTbl[i] = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
            itemTbl[i] = (u16)PokeParaGet( pp, ID_PARA_item, NULL );
            level += PokeParaGet(pp,ID_PARA_level,NULL);
        }
    }
    //���vLV
    ans = Regulation_GetParam(pReg, REGULATION_TOTAL_LEVEL);
    if((level > ans) && (ans != 0)){
        return POKE_REG_TOTAL_LV_FAILED;
    }
    // �����|�P����
    ans = Regulation_GetParam(pReg, REGULATION_BOTH_MONSTER);
    if((ans == 0) && (cnt > 1)){  // �����|�P�����͂��߂� ��̈ȏ�̏ꍇ
        for(i = 0; i < (6-1); i++){
            for(j = i + 1;j < 6; j++){
                if((monsTbl[i] == monsTbl[j]) && (monsTbl[i] != _POKENO_NONE)){
                    return POKE_REG_BOTH_POKE;
                }
            }
        }
    }

    // �����A�C�e��
    ans = Regulation_GetParam(pReg, REGULATION_BOTH_ITEM);
    if((ans == 0) && (cnt > 1)){  // �����A�C�e���͂��߂� ��̈ȏ�̏ꍇ
        for(i = 0; i < (6-1); i++){
            for(j = i + 1;j < 6; j++){
                if((itemTbl[i] == itemTbl[j]) && (monsTbl[i] != _POKENO_NONE) && (ITEM_DUMMY_DATA != itemTbl[i])){
                    return POKE_REG_BOTH_ITEM;
                }
            }
        }
    }
    return POKE_REG_OK;
}

//------------------------------------------------------------------
/**
 * �ċA�I��LV�������Z���ĖړI�ɒB������TRUE
 * @param   �����X�^�[�ԍ��̃e�[�u��
 * @param   ���x���������Ă�̃e�[�u��
 * @param   ���̃|�P�������������ꍇ��MARK
 * @param   totalPokeLv   �c���LV
 * @param   nowPokeIndex  ������v�Z����|�P����
 * @param   partyNum     CUP�Q���̎c��|�P������
 * @param   �|�P�p�[�e�B�[��
 * @return  ���v������TRUE
 */
//------------------------------------------------------------------

static BOOL _totalLevelCheck(u16* pMonsTbl,u16* pLevelTbl,u16* pMarkTbl,
                             int totalPokeLv,int nowPokeIndex, int partyNum, int cnt)
{
    int total = totalPokeLv;
    int i;
    int party = partyNum;
    
    if((pMonsTbl[nowPokeIndex] != _POKENO_NONE) && (pMarkTbl[nowPokeIndex] == 0)){
        total -= pLevelTbl[nowPokeIndex];
        if(total < 0){
            return FALSE;
        }
        party--;
        if(party == 0){
            return TRUE;
        }
        pMarkTbl[nowPokeIndex] = 1;  // �}�[�N����
    }
    for(i = nowPokeIndex+1;i < cnt;i++){  // �ċA������
        if(_totalLevelCheck(pMonsTbl,pLevelTbl,pMarkTbl, total, i, party, cnt)){
            return TRUE;
        }
    }
    pMarkTbl[nowPokeIndex] = 0;  // �}�[�N�͂���
    return FALSE;
}

//------------------------------------------------------------------
/**
 * �|�P�p�[�e�B���Ƀ��M�����[�V�����ɓK�����Ă���
 *   �p�[�e�B�[���g�߂邩�ǂ������ׂ� �K���O�̃|�P���������Ă����v
 *   �莝���A�C�e���͌������Ă��Ȃ�
 * @param   POKEMON_PARAM
 * @param   REGULATION
 * @param   ZKN_HEIGHT_GRAM_PTR
 * @return  _POKE_REG_NUM_FAILED �� _POKE_REG_TOTAL_FAILED �� _POKE_REG_OK
 */
//------------------------------------------------------------------

int PokeRegulationMatchPartialPokeParty(const REGULATION* pReg, POKEPARTY * party,const ZKN_HEIGHT_GRAM_PTR pZKN)
{
    POKEMON_PARAM* pp;
    int ans,cnt,j,i,level = 0;
    u16 monsTbl[6],levelTbl[6],markTbl[6];
    int partyNum;

    cnt = PokeParty_GetPokeCount(party);
    partyNum = cnt;

    MI_CpuClear8(markTbl,6*sizeof(u16));
    
    for(i = 0; i < cnt ;i++){
        pp = PokeParty_GetMemberPointer(party, i);
        monsTbl[i] = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
        levelTbl[i] = PokeParaGet(pp,ID_PARA_level,NULL);
        if(PokeRegulationCheckPokePara(pReg, pp, pZKN) == FALSE){
            monsTbl[i] = _POKENO_NONE; // �ő̂��������������̂ŏ���
            partyNum--;
        }
    }
    // �����|�P���������߂ȏꍇ
    ans = Regulation_GetParam(pReg, REGULATION_BOTH_MONSTER);
    if((ans == 0) && (cnt > 1)){  // �����|�P������LV�̒Ⴂ�����c��
        for(i = 0; i < (cnt-1); i++){
            for(j = i + 1;j < cnt; j++){
                if((monsTbl[i] == monsTbl[j]) && (monsTbl[i] != _POKENO_NONE)){
                    if(levelTbl[i] > levelTbl[j]){
                        monsTbl[i] = _POKENO_NONE; // �������̂�����
                    }
                    else{
                        monsTbl[j] = _POKENO_NONE; // �������̂�����
                    }
                    partyNum--;
                }
            }
        }
    }
    //�S�̐�
    ans = Regulation_GetParam(pReg, REGULATION_POKE_NUM);
    if(partyNum < ans){
        return POKE_REG_NUM_FAILED;  // �S�̐�������Ȃ�
    }
    partyNum = ans;

    //�c�����|�P�����̍��vLV�g�ݍ��킹����
    ans = Regulation_GetParam(pReg, REGULATION_TOTAL_LEVEL);
    if(ans == 0){
        return POKE_REG_OK;  // LV�����Ȃ�
    }
    for(i = 0;i < cnt;i++){
        if(_totalLevelCheck(monsTbl,levelTbl,markTbl, ans, i, partyNum, cnt)){
            return POKE_REG_OK;
        }
    }
    return POKE_REG_TOTAL_LV_FAILED;
}


#ifdef DEBUG_ONLY_FOR_ohno

#define _FAN    (0)
#define _YELLOW (1)

static void _testRegulation(ZKN_HEIGHT_GRAM_PTR pZKN)
{
    int ans;
    
    
    POKEMON_PARAM* pp1 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp2 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp3 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp4 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp5 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp6 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp7 = PokemonParam_AllocWork(HEAPID_FIELD);
    POKEMON_PARAM* pp8 = PokemonParam_AllocWork(HEAPID_FIELD);
    
    POKEPARTY* party = PokeParty_AllocPartyWork(HEAPID_FIELD);
    POKEPARTY* fanparty = PokeParty_AllocPartyWork(HEAPID_FIELD);

    PokeParaSetSexChr(pp1,MONSNO_POPPO,20,1,1,1,0);
    PokeParaSetSexChr(pp2,MONSNO_PIKATYUU,20,1,1,1,0);
    PokeParaSetSexChr(pp3,MONSNO_PIZYON,20,1,1,1,0);
    PokeParaSetSexChr(pp4,MONSNO_POPPO,5,1,1,1,0);
    PokeParaSetSexChr(pp5,MONSNO_PIZYOTTO,5,1,1,1,0);
    PokeParaSetSexChr(pp6,MONSNO_MYUU,5,1,1,1,0);
    PokeParaSetSexChr(pp7,MONSNO_BIIDORU,5,1,1,1,0);
    PokeParaSetSexChr(pp8,MONSNO_KOKUUN,5,1,1,1,0);

    PokeParty_Add(party,pp1);
    PokeParty_Add(party,pp2);
    PokeParty_Add(party,pp3);
    PokeParty_Add(party,pp4);
    PokeParty_Add(party,pp5);
    PokeParty_Add(party,pp6);

    PokeParty_Add(fanparty,pp1);
    PokeParty_Add(fanparty,pp7);
    PokeParty_Add(fanparty,pp8);

    
    {
        // �C�G���[�J�b�v           // ���vLV50             // 3�C            // LV20
        u8 selPoke[6]={1,2,0,0,3,0};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN, selPoke);
        if(ans != POKE_REG_OK){
            OS_TPrintf("1 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-1 �܂����� %d \n",ans);
        }
    }
    {
        u8 selPoke[6]={1,2,3,0,0,0};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        // �C�G���[�J�b�v           // ���vLV50             // 3�C            // LV20
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN, selPoke);
        if(ans != POKE_REG_TOTAL_LV_FAILED){
            OS_TPrintf("2 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-2 �܂����� %d \n",ans);
        }
    }
    {
        // �C�G���[�J�b�v           // ���vLV50             // 3�C            // LV20
        u8 selPoke[6]={1,2,0,3,0,0};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN, selPoke);
        if(ans != POKE_REG_BOTH_POKE){
            OS_TPrintf("3 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-3 �܂����� %d \n",ans);
        }
    }
    {
        // �C�G���[�J�b�v           // ���vLV50             // 3�C            // LV20
        u8 selPoke[6]={1,2,0,0,0,3};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN, selPoke);
        if(ans != POKE_REG_ILLEGAL_POKE){
            OS_TPrintf("4 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-4 �܂����� %d \n",ans);
        }
    }
    {
        // �C�G���[�J�b�v           // ���vLV50             // 3�C            // LV20
        u8 selPoke[6]={1,2,4,0,0,3};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN, selPoke);
        if(ans != POKE_REG_NUM_FAILED){  // ��������
            OS_TPrintf("5 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_YELLOW),  party, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-5 �܂����� %d \n",ans);
        }
    }

    {
        // �t�@���V�[�J�b�v           // ���vLV80             // 3�C            // LV30
        u8 selPoke[6]={1,0,2,0,3,0};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_FAN),  party, pZKN, selPoke);
        if(ans != POKE_REG_ILLEGAL_POKE){  // ��������
            OS_TPrintf("11 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_FAN),  party, pZKN);
        if(ans != POKE_REG_NUM_FAILED){
            OS_TPrintf("-11 �܂����� %d \n",ans);
        }
    }
    {
        // �t�@���V�[�J�b�v           // ���vLV80             // 3�C            // LV30
        u8 selPoke[6]={1,2,3,0,0,0};  // �I�������|�P�����̔ԍ���U��o�b�t�@
        ans = PokeRegulationMatchFullPokeParty(Data_GetRegulation(NULL,_FAN),  fanparty, pZKN, selPoke);
        if(ans != POKE_REG_OK){  // ��������
            OS_TPrintf("12 �܂����� %d \n",ans);
        }
        ans = PokeRegulationMatchPartialPokeParty(Data_GetRegulation(NULL,_FAN),  fanparty, pZKN);
        if(ans != POKE_REG_OK){
            OS_TPrintf("-12 �܂����� %d \n",ans);
        }
    }

    OS_TPrintf(" �e�X�g����\n");

    sys_FreeMemoryEz(pp1);
    sys_FreeMemoryEz(pp2);
    sys_FreeMemoryEz(pp3);
    sys_FreeMemoryEz(pp4);
    sys_FreeMemoryEz(pp5);
    sys_FreeMemoryEz(pp6);
    sys_FreeMemoryEz(pp7);
    sys_FreeMemoryEz(pp8);
    sys_FreeMemoryEz(party);
    sys_FreeMemoryEz(fanparty);
}

#endif//DEBUG_ONLY_FOR_ohno
